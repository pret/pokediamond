	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021D5E28
UNK_021D5E28: ; 0x021D5E28
	.space 0x4

	.global UNK_021D5E2C
UNK_021D5E2C: ; 0x021D5E2C
	.space 0x4

	.global UNK_021D5E30
UNK_021D5E30: ; 0x021D5E30
	.space 0x20

	.global UNK_021D5E50
UNK_021D5E50: ; 0x021D5E50
	.space 0x28

	.global UNK_021D5E78
UNK_021D5E78: ; 0x021D5E78
	.space 0x14

	.global UNK_021D5E8C
UNK_021D5E8C: ; 0x021D5E8C
	.space 0x10

	.global UNK_021D5E9C
UNK_021D5E9C: ; 0x021D5E9C
	.space 0x24

	.global UNK_021D5EC0
UNK_021D5EC0: ; 0x021D5EC0
	.space 0xa00

    .text

	arm_func_start WMi_GetMPReadyAIDs
WMi_GetMPReadyAIDs: ; 0x020D7DE0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020D7E30 ; =UNK_021D5E2C
	mov r4, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	moveq r5, #0x0
	beq _020D7E18
	ldr r5, [r0, #0x4]
	mov r1, #0x2
	add r0, r5, #0x86
	bl DC_InvalidateRange
	ldrh r5, [r5, #0x86]
_020D7E18:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D7E30: .word UNK_021D5E2C

	arm_func_start WM_GetConnectedAIDs
WM_GetConnectedAIDs: ; 0x020D7E34
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020D7E64 ; =UNK_021D5E2C
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	ldrne r4, [r1, #0x14c]
	moveq r4, #0x0
	bl OS_RestoreInterrupts
	mov r0, r4, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D7E64: .word UNK_021D5E2C

	arm_func_start WM_GetAID
WM_GetAID: ; 0x020D7E68
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020D7E98 ; =UNK_021D5E2C
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	addne r1, r1, #0x100
	ldrneh r4, [r1, #0x50]
	moveq r4, #0x0
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D7E98: .word UNK_021D5E2C

	arm_func_start WMi_GetStatusAddress
WMi_GetStatusAddress: ; 0x020D7E9C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WMi_CheckInitialized
_020D7EA8: ; 0x020D7EA8
	cmp r0, #0x0
	movne r0, #0x0
	ldreq r0, _020D7EC8 ; =UNK_021D5E2C
	ldreq r0, [r0, #0x0]
	ldreq r0, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7EC8: .word UNK_021D5E2C

	arm_func_start WmClearFifoRecvFlag
WmClearFifoRecvFlag: ; 0x020D7ECC
	ldr r1, _020D7EE4 ; =0x027FFF96
	ldrh r0, [r1, #0x0]
	ands r2, r0, #0x1
	bicne r0, r0, #0x1
	strneh r0, [r1, #0x0]
	bx lr
	.balign 4
_020D7EE4: .word 0x027FFF96

	arm_func_start WmReceiveFifo
WmReceiveFifo: ; 0x020D7EE8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r0, _020D82B0 ; =UNK_021D5E2C
	cmp r2, #0x0
	ldr r8, [r0, #0x0]
	mov r10, r1
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [r8, #0x10]
	mov r1, #0x100
	bl DC_InvalidateRange
	ldrh r0, [r8, #0x16]
	cmp r0, #0x0
	bne _020D7F30
	ldr r0, [r8, #0x4]
	mov r1, #0x800
	bl DC_InvalidateRange
_020D7F30:
	ldr r0, [r8, #0x10]
	cmp r10, r0
	beq _020D7F48
	mov r0, r10
	mov r1, #0x100
	bl DC_InvalidateRange
_020D7F48:
	ldrh r0, [r10, #0x0]
	cmp r0, #0x2c
	blo _020D8000
	cmp r0, #0x80
	bne _020D7F84
	ldrh r0, [r10, #0x2]
	cmp r0, #0x13
	bne _020D7F6C
	bl OS_Terminate
_020D7F6C:
	ldr r1, [r8, #0xc8]
	cmp r1, #0x0
	beq _020D8268
	mov r0, r10
	blx r1
	b _020D8268
_020D7F84:
	cmp r0, #0x82
	bne _020D7FD8
	ldrh r0, [r10, #0x6]
	add r1, r8, r0, lsl #0x2
	ldr r0, [r1, #0xcc]
	cmp r0, #0x0
	beq _020D8268
	ldr r0, [r1, #0x10c]
	str r0, [r10, #0x1c]
	ldr r0, [r8, #0x14c]
	strh r0, [r10, #0x22]
	ldr r1, [r8, #0x4]
	ldr r0, [r10, #0x8]
	ldrh r1, [r1, #0x72]
	bl DC_InvalidateRange
	ldrh r1, [r10, #0x6]
	mov r0, r10
	add r1, r8, r1, lsl #0x2
	ldr r1, [r1, #0xcc]
	blx r1
	b _020D8268
_020D7FD8:
	cmp r0, #0x81
	bne _020D8268
	mov r0, #0xf
	strh r0, [r10, #0x0]
	ldr r1, [r10, #0x1c]
	cmp r1, #0x0
	beq _020D8268
	mov r0, r10
	blx r1
	b _020D8268
_020D8000:
	cmp r0, #0xe
	bne _020D8040
	ldrh r1, [r10, #0x4]
	ldr r0, _020D82B4 ; =0x0000FFF5
	add r0, r1, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, #0x1
	bhi _020D8040
	ldrh r0, [r10, #0x2]
	cmp r0, #0x0
	bne _020D8040
	ldr r1, [r8, #0x4]
	ldr r0, [r10, #0x8]
	ldrh r1, [r1, #0x72]
	bl DC_InvalidateRange
_020D8040:
	ldrh r1, [r10, #0x0]
	cmp r1, #0x2
	bne _020D8088
	ldrh r0, [r10, #0x2]
	cmp r0, #0x0
	bne _020D8088
	add r0, r8, r1, lsl #0x2
	ldr r4, [r0, #0x18]
	bl WM_Finish
_020D8064: ; 0x020D8064
	cmp r4, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	mov r0, r10
	blx r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D8088:
	add r0, r8, r1, lsl #0x2
	ldr r1, [r0, #0x18]
	cmp r1, #0x0
	beq _020D80B8
	mov r0, r10
	blx r1
	ldr r0, _020D82B8 ; =UNK_021D5E28
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
_020D80B8:
	ldrh r0, [r10, #0x0]
	cmp r0, #0x8
	beq _020D80CC
	cmp r0, #0xc
	bne _020D8268
_020D80CC:
	cmp r0, #0x8
	bne _020D8100
	add r0, r10, #0xa
	str r0, [sp, #0x0]
	ldrh r0, [r10, #0x2c]
	add r11, r10, #0x14
	ldrh r7, [r10, #0x8]
	ldrh r6, [r10, #0x10]
	ldrh r4, [r10, #0x12]
	str r0, [sp, #0x4]
	ldrh r9, [r10, #0x2e]
	mov r5, #0x0
	b _020D8130
_020D8100:
	cmp r0, #0xc
	bne _020D8130
	ldrh r0, [r10, #0x16]
	mov r6, #0x0
	ldrh r7, [r10, #0x8]
	str r0, [sp, #0x4]
	add r0, r10, #0x10
	ldrh r5, [r10, #0xa]
	ldrh r4, [r10, #0xc]
	ldrh r9, [r10, #0x18]
	mov r11, r6
	str r0, [sp, #0x0]
_020D8130:
	cmp r7, #0x7
	beq _020D8148
	cmp r7, #0x9
	beq _020D8148
	cmp r7, #0x1a
	bne _020D8268
_020D8148:
	cmp r7, #0x7
	ldreq r1, [r8, #0x14c]
	moveq r0, #0x1
	orreq r0, r1, r0, lsl r6
	streq r0, [r8, #0x14c]
	movne r0, #0x1
	mvnne r0, r0, lsl r6
	ldrne r1, [r8, #0x14c]
	add r3, r8, #0x100
	andne r0, r1, r0
	strne r0, [r8, #0x14c]
	ldr r0, _020D82BC ; =UNK_021D5E78
	mov r1, #0x0
	mov r2, #0x44
	strh r5, [r3, #0x50]
	bl MI_CpuFill8
	ldr r3, _020D82BC ; =UNK_021D5E78
	mov r1, #0x0
	mov r2, #0x82
	strh r2, [r3, #0x0]
	strh r7, [r3, #0x4]
	strh r6, [r3, #0x12]
	strh r5, [r3, #0x20]
	strh r1, [r3, #0x2]
	str r1, [r3, #0x8]
	str r1, [r3, #0xc]
	strh r1, [r3, #0x10]
	ldr r1, [r8, #0x14c]
	ldr r2, _020D82C0 ; =0x0000FFFF
	strh r1, [r3, #0x22]
	strh r2, [r3, #0x1a]
	ldr r0, [sp, #0x0]
	ldr r1, _020D82C4 ; =UNK_021D5E8C
	mov r2, #0x6
	strh r4, [r3, #0x3c]
	bl MI_CpuCopy8
_020D81D8: ; 0x020D81D8
	cmp r11, #0x0
	beq _020D81F4
	ldr r1, _020D82C8 ; =UNK_021D5E9C
	mov r0, r11
	mov r2, #0x18
	bl MIi_CpuCopy16
	b _020D8204
_020D81F4:
	ldr r1, _020D82C8 ; =UNK_021D5E9C
	mov r0, #0x0
	mov r2, #0x18
	bl MIi_CpuClear16
_020D8204:
	cmp r5, #0x0
	ldreq r1, [sp, #0x4]
	ldr r0, _020D82BC ; =UNK_021D5E78
	movne r1, r9
	cmp r5, #0x0
	ldrne r9, [sp, #0x4]
	ldr r5, _020D82BC ; =UNK_021D5E78
	strh r1, [r0, #0x40]
	mov r4, #0x0
	strh r9, [r5, #0x42]
_020D822C:
	strh r4, [r5, #0x6]
	add r2, r8, r4, lsl #0x2
	ldr r0, [r2, #0xcc]
	cmp r0, #0x0
	beq _020D8254
	ldr r1, [r2, #0x10c]
	mov r0, r5
	str r1, [r5, #0x1c]
	ldr r1, [r2, #0xcc]
	blx r1
_020D8254:
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	cmp r4, #0x10
	blo _020D822C
_020D8268:
	ldr r0, [r8, #0x10]
	mov r1, #0x100
	bl DC_InvalidateRange
	bl WmClearFifoRecvFlag
	ldr r0, [r8, #0x10]
	cmp r10, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r2, [r10, #0x0]
	mov r0, r10
	mov r1, #0x100
	orr r2, r2, #0x8000
	strh r2, [r10, #0x0]
	bl DC_StoreRange
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D82B0: .word UNK_021D5E2C
_020D82B4: .word 0x0000FFF5
_020D82B8: .word UNK_021D5E28
_020D82BC: .word UNK_021D5E78
_020D82C0: .word 0x0000FFFF
_020D82C4: .word UNK_021D5E8C
_020D82C8: .word UNK_021D5E9C

	arm_func_start WMi_CheckStateEx
WMi_CheckStateEx:
	stmdb sp!, {r0-r3}
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WMi_CheckInitialized
_020D82DC: ; 0x020D82DC
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	addne sp, sp, #0x10
	bxne lr
	ldr r0, _020D8370 ; =UNK_021D5E2C
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl DC_InvalidateRange
	ldr r0, _020D8370 ; =UNK_021D5E2C
	add r1, sp, #0x8
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x8]
	ldr r2, [r2, #0x4]
	cmp r0, #0x0
	bic r1, r1, #0x3
	addeq sp, sp, #0x4
	add r12, r1, #0x4
	ldrh r3, [r2, #0x0]
	mov r0, #0x3
	ldmeqia sp!, {lr}
	addeq sp, sp, #0x10
	bxeq lr
	mov r2, #0x0
_020D8340:
	add r12, r12, #0x4
	ldr r1, [r12, #-0x4]
	cmp r1, r3
	ldr r1, [sp, #0x8]
	moveq r0, r2
	subs r1, r1, #0x1
	str r1, [sp, #0x8]
	bne _020D8340
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020D8370: .word UNK_021D5E2C

	arm_func_start WMi_CheckIdle
WMi_CheckIdle:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WMi_CheckInitialized
_020D8380: ; 0x020D8380
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020D83CC ; =UNK_021D5E2C
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl DC_InvalidateRange
	ldr r0, _020D83CC ; =UNK_021D5E2C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x1
	movls r0, #0x3
	movhi r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D83CC: .word UNK_021D5E2C

	arm_func_start WMi_CheckInitialized
WMi_CheckInitialized:
	ldr r0, _020D83E8 ; =UNK_021D5E28
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	bx lr
	.balign 4
_020D83E8: .word UNK_021D5E28

	arm_func_start WMi_GetSystemWork
WMi_GetSystemWork: ; 0x020D83EC
	ldr r0, _020D83F8 ; =UNK_021D5E2C
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D83F8: .word UNK_021D5E2C

	arm_func_start WMi_SendCommandDirect
WMi_SendCommandDirect:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r4, r1
	bl WmGetCommandBuffer4Arm7
	movs r5, r0
	moveq r0, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MI_CpuCopy8
	mov r0, r5
	mov r1, r4
	bl DC_StoreRange
	mov r1, r5
	mov r0, #0xa
	mov r2, #0x0
	bl PXI_SendWordByFifo
	mov r4, r0
	ldr r0, _020D8470 ; =UNK_021D5E30
	mov r1, r5
	mov r2, #0x1
	bl OS_SendMessage
_020D845C: ; 0x020D845C
	cmp r4, #0x0
	movlt r0, #0x8
	movge r0, #0x2
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D8470: .word UNK_021D5E30

	arm_func_start WMi_SendCommand
WMi_SendCommand:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl WmGetCommandBuffer4Arm7
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x8
	ldmeqia sp!, {r4-r5,lr}
	addeq sp, sp, #0x10
	bxeq lr
	strh r4, [r5, #0x0]
	ldrh r2, [sp, #0x14]
	add r0, sp, #0x14
	bic r0, r0, #0x3
	mov r3, #0x0
	cmp r2, #0x0
	add r4, r0, #0x4
	ble _020D84DC
_020D84C0:
	add r4, r4, #0x4
	ldr r1, [r4, #-0x4]
	add r0, r5, r3, lsl #0x2
	add r3, r3, #0x1
	str r1, [r0, #0x4]
	cmp r3, r2
	blt _020D84C0
_020D84DC:
	mov r0, r5
	mov r1, #0x100
	bl DC_StoreRange
	mov r1, r5
	mov r0, #0xa
	mov r2, #0x0
	bl PXI_SendWordByFifo
	mov r4, r0
	ldr r0, _020D8528 ; =UNK_021D5E30
	mov r1, r5
	mov r2, #0x1
	bl OS_SendMessage
_020D850C: ; 0x020D850C
	cmp r4, #0x0
	movlt r0, #0x8
	movge r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020D8528: .word UNK_021D5E30

	arm_func_start WmGetCommandBuffer4Arm7
WmGetCommandBuffer4Arm7: ; 0x020D852C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020D859C ; =UNK_021D5E30
	add r1, sp, #0x0
	mov r2, #0x0
	bl OS_ReceiveMessage
_020D8544: ; 0x020D8544
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	bl DC_InvalidateRange
	ldr r1, [sp, #0x0]
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x8000
	addne sp, sp, #0x4
	movne r0, r1
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020D859C ; =UNK_021D5E30
	mov r2, #0x1
	bl OS_JamMessage
_020D858C: ; 0x020D858C
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D859C: .word UNK_021D5E30

	arm_func_start WMi_SetCallbackTable
WMi_SetCallbackTable: ; 0x020D85A0
	ldr r2, _020D85B4 ; =UNK_021D5E2C
	ldr r2, [r2, #0x0]
	add r0, r2, r0, lsl #0x2
	str r1, [r0, #0x18]
	bx lr
	.balign 4
_020D85B4: .word UNK_021D5E2C

	arm_func_start WM_Finish
WM_Finish:
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	bl WMi_CheckInitialized
_020D85C8: ; 0x020D85C8
	cmp r0, #0x0
	beq _020D85E4
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
_020D85E4:
	mov r0, #0x1
	mov r1, #0x0
	bl WMi_CheckStateEx
_020D85F0: ; 0x020D85F0
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	bl WmClearFifoRecvFlag
	mov r0, #0xa
	mov r1, #0x0
	bl PXI_SetFifoRecvCallback
	ldr r2, _020D8634 ; =UNK_021D5E2C
	mov r3, #0x0
	ldr r1, _020D8638 ; =UNK_021D5E28
	mov r0, r4
	str r3, [r2, #0x0]
	strh r3, [r1, #0x0]
	bl OS_RestoreInterrupts
_020D8628: ; 0x020D8628
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D8634: .word UNK_021D5E2C
_020D8638: .word UNK_021D5E28

	arm_func_start WmInitCore
WmInitCore:
	stmdb sp!, {r4-r10,lr}
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, _020D881C ; =UNK_021D5E28
	mov r4, r0
	ldrh r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020D8674
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4-r10,lr}
	bx lr
_020D8674:
	cmp r6, #0x0
	bne _020D868C
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r10,lr}
	bx lr
_020D868C:
	cmp r5, #0x3
	bls _020D86A4
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r10,lr}
	bx lr
_020D86A4:
	ands r1, r6, #0x1f
	beq _020D86BC
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r10,lr}
	bx lr
_020D86BC:
	bl PXI_Init
	mov r0, #0xa
	mov r1, #0x1
	bl PXI_IsCallbackReady
_020D86CC: ; 0x020D86CC
	cmp r0, #0x0
	bne _020D86E8
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4-r10,lr}
	bx lr
_020D86E8:
	mov r0, r6
	mov r1, r7
	bl DC_InvalidateRange
	mov r0, r5
	mov r1, r6
	mov r3, r7
	mov r2, #0x0
	bl MI_DmaFill32
	ldr r0, _020D8820 ; =UNK_021D5E2C
	add r1, r6, #0x200
	str r6, [r0, #0x0]
	str r1, [r6, #0x0]
	ldr r2, [r0, #0x0]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x300
	str r1, [r2, #0x4]
	ldr r2, [r0, #0x0]
	ldr r1, [r2, #0x4]
	add r1, r1, #0x800
	str r1, [r2, #0xc]
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0xc]
	add r0, r0, #0x100
	str r0, [r1, #0x10]
	bl WmClearFifoRecvFlag
	ldr r1, _020D8820 ; =UNK_021D5E2C
	mov r3, #0x0
	ldr r0, [r1, #0x0]
	strh r5, [r0, #0x14]
	ldr r0, [r1, #0x0]
	str r3, [r0, #0x14c]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x100
	strh r3, [r0, #0x50]
	mov r2, r3
_020D8774:
	ldr r0, [r1, #0x0]
	add r0, r0, r3, lsl #0x2
	str r2, [r0, #0xcc]
	ldr r0, [r1, #0x0]
	add r0, r0, r3, lsl #0x2
	add r3, r3, #0x1
	str r2, [r0, #0x10c]
	cmp r3, #0x10
	blt _020D8774
	ldr r0, _020D8824 ; =UNK_021D5E30
	ldr r1, _020D8828 ; =UNK_021D5E50
	mov r2, #0xa
	bl OS_InitMessageQueue
	ldr sb, _020D882C ; =UNK_021D5EC0
	mov r10, #0x0
	ldr r6, _020D8824 ; =UNK_021D5E30
	mov r8, #0x8000
	mov r7, #0x2
	mov r5, #0x1
_020D87C0:
	mov r0, r9
	mov r1, r7
	strh r8, [r9, #0x0]
	bl DC_StoreRange
	mov r0, r6
	mov r1, r9
	mov r2, r5
	bl OS_SendMessage
	add r10, r10, #0x1
	cmp r10, #0xa
	add r9, r9, #0x100
	blt _020D87C0
	ldr r1, _020D8830 ; =WmReceiveFifo
	mov r0, #0xa
	bl PXI_SetFifoRecvCallback
	ldr r1, _020D881C ; =UNK_021D5E28
	mov r2, #0x1
	mov r0, r4
	strh r2, [r1, #0x0]
	bl OS_RestoreInterrupts
_020D8810: ; 0x020D8810
	mov r0, #0x0
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020D881C: .word UNK_021D5E28
_020D8820: .word UNK_021D5E2C
_020D8824: .word UNK_021D5E30
_020D8828: .word UNK_021D5E50
_020D882C: .word UNK_021D5EC0
_020D8830: .word WmReceiveFifo

	arm_func_start WM_Init
WM_Init:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0xf00
	bl WmInitCore
_020D8844: ; 0x020D8844
	cmp r0, #0x0
	ldreq r1, _020D8864 ; =UNK_021D5E2C
	moveq r2, #0x0
	ldreq r1, [r1, #0x0]
	streqh r2, [r1, #0x16]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D8864: .word UNK_021D5E2C
