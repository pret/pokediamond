	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start WMi_GetMPReadyAIDs
WMi_GetMPReadyAIDs: ; 0x020D7DE0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020D7E30 ; =0x021D5E2C
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
_020D7E30: .word 0x021D5E2C

	arm_func_start WM_GetConnectedAIDs
WM_GetConnectedAIDs: ; 0x020D7E34
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020D7E64 ; =0x021D5E2C
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
_020D7E64: .word 0x021D5E2C

	arm_func_start WM_GetAID
WM_GetAID: ; 0x020D7E68
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020D7E98 ; =0x021D5E2C
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
_020D7E98: .word 0x021D5E2C

	arm_func_start WMi_GetStatusAddress
WMi_GetStatusAddress: ; 0x020D7E9C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WMi_CheckInitialized
_020D7EA8: ; 0x020D7EA8
	cmp r0, #0x0
	movne r0, #0x0
	ldreq r0, _020D7EC8 ; =0x021D5E2C
	ldreq r0, [r0, #0x0]
	ldreq r0, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D7EC8: .word 0x021D5E2C

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
	ldr r0, _020D82B0 ; =0x021D5E2C
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
	ldr r0, _020D82B8 ; =0x021D5E28
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
	ldr r0, _020D82BC ; =0x021D5E78
	mov r1, #0x0
	mov r2, #0x44
	strh r5, [r3, #0x50]
	bl MI_CpuFill8
	ldr r3, _020D82BC ; =0x021D5E78
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
	ldr r1, _020D82C4 ; =0x021D5E8C
	mov r2, #0x6
	strh r4, [r3, #0x3c]
	bl MI_CpuCopy8
_020D81D8: ; 0x020D81D8
	cmp r11, #0x0
	beq _020D81F4
	ldr r1, _020D82C8 ; =0x021D5E9C
	mov r0, r11
	mov r2, #0x18
	bl MIi_CpuCopy16
	b _020D8204
_020D81F4:
	ldr r1, _020D82C8 ; =0x021D5E9C
	mov r0, #0x0
	mov r2, #0x18
	bl MIi_CpuClear16
_020D8204:
	cmp r5, #0x0
	ldreq r1, [sp, #0x4]
	ldr r0, _020D82BC ; =0x021D5E78
	movne r1, r9
	cmp r5, #0x0
	ldrne r9, [sp, #0x4]
	ldr r5, _020D82BC ; =0x021D5E78
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
_020D82B0: .word 0x021D5E2C
_020D82B4: .word 0x0000FFF5
_020D82B8: .word 0x021D5E28
_020D82BC: .word 0x021D5E78
_020D82C0: .word 0x0000FFFF
_020D82C4: .word 0x021D5E8C
_020D82C8: .word 0x021D5E9C

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
	ldr r0, _020D8370 ; =0x021D5E2C
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl DC_InvalidateRange
	ldr r0, _020D8370 ; =0x021D5E2C
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
_020D8370: .word 0x021D5E2C

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
	ldr r0, _020D83CC ; =0x021D5E2C
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl DC_InvalidateRange
	ldr r0, _020D83CC ; =0x021D5E2C
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
_020D83CC: .word 0x021D5E2C

	arm_func_start WMi_CheckInitialized
WMi_CheckInitialized:
	ldr r0, _020D83E8 ; =0x021D5E28
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	bx lr
	.balign 4
_020D83E8: .word 0x021D5E28

	arm_func_start WMi_GetSystemWork
WMi_GetSystemWork: ; 0x020D83EC
	ldr r0, _020D83F8 ; =0x021D5E2C
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D83F8: .word 0x021D5E2C

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
	ldr r0, _020D8470 ; =0x021D5E30
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
_020D8470: .word 0x021D5E30

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
	ldr r0, _020D8528 ; =0x021D5E30
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
_020D8528: .word 0x021D5E30

	arm_func_start WmGetCommandBuffer4Arm7
WmGetCommandBuffer4Arm7: ; 0x020D852C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020D859C ; =0x021D5E30
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
	ldr r0, _020D859C ; =0x021D5E30
	mov r2, #0x1
	bl OS_JamMessage
_020D858C: ; 0x020D858C
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D859C: .word 0x021D5E30

	arm_func_start WMi_SetCallbackTable
WMi_SetCallbackTable: ; 0x020D85A0
	ldr r2, _020D85B4 ; =0x021D5E2C
	ldr r2, [r2, #0x0]
	add r0, r2, r0, lsl #0x2
	str r1, [r0, #0x18]
	bx lr
	.balign 4
_020D85B4: .word 0x021D5E2C

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
	ldr r2, _020D8634 ; =0x021D5E2C
	mov r3, #0x0
	ldr r1, _020D8638 ; =0x021D5E28
	mov r0, r4
	str r3, [r2, #0x0]
	strh r3, [r1, #0x0]
	bl OS_RestoreInterrupts
_020D8628: ; 0x020D8628
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D8634: .word 0x021D5E2C
_020D8638: .word 0x021D5E28

	arm_func_start WmInitCore
WmInitCore:
	stmdb sp!, {r4-r10,lr}
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, _020D881C ; =0x021D5E28
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
	ldr r0, _020D8820 ; =0x021D5E2C
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
	ldr r1, _020D8820 ; =0x021D5E2C
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
	ldr r0, _020D8824 ; =0x021D5E30
	ldr r1, _020D8828 ; =0x021D5E50
	mov r2, #0xa
	bl OS_InitMessageQueue
	ldr sb, _020D882C ; =0x021D5EC0
	mov r10, #0x0
	ldr r6, _020D8824 ; =0x021D5E30
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
	ldr r1, _020D881C ; =0x021D5E28
	mov r2, #0x1
	mov r0, r4
	strh r2, [r1, #0x0]
	bl OS_RestoreInterrupts
_020D8810: ; 0x020D8810
	mov r0, #0x0
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020D881C: .word 0x021D5E28
_020D8820: .word 0x021D5E2C
_020D8824: .word 0x021D5E30
_020D8828: .word 0x021D5E50
_020D882C: .word 0x021D5EC0
_020D8830: .word WmReceiveFifo

	arm_func_start WM_Init
WM_Init:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0xf00
	bl WmInitCore
_020D8844: ; 0x020D8844
	cmp r0, #0x0
	ldreq r1, _020D8864 ; =0x021D5E2C
	moveq r2, #0x0
	ldreq r1, [r1, #0x0]
	streqh r2, [r1, #0x16]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D8864: .word 0x021D5E2C

	arm_func_start WM_GetNextTgid
WM_GetNextTgid: ; 0x020D8868
	stmdb sp!, {lr}
	sub sp, sp, #0xc

	arm_func_start FUN_020D8870
FUN_020D8870: ; 0x020D8870
	ldr r0, _020D88DC ; =0x02106A54
	ldr r0, [r0, #0x0]
	cmp r0, #0x10000
	bne _020D88B0
	bl RTC_Init
_020D8884: ; 0x020D8884
	add r0, sp, #0x0
	bl RTC_GetTime
_020D888C: ; 0x020D888C
	cmp r0, #0x0
	bne _020D88B0
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x4]
	ldr r1, _020D88DC ; =0x02106A54
	add r0, r2, r0, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
_020D88B0:
	ldr r1, _020D88DC ; =0x02106A54
	ldr r0, [r1, #0x0]
	add r0, r0, #0x1
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, lsl #0x10
	str r2, [r1, #0x0]
	mov r0, r0, lsr #0x10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D88DC: .word 0x02106A54

	arm_func_start WM_GetOtherElements
WM_GetOtherElements: ; 0x020D88E0
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x88
	ldrh r2, [r1, #0x3c]
	mov lr, r0
	cmp r2, #0x0
	beq _020D892C
	mov r0, #0x0
	add r5, sp, #0x0
	strb r0, [sp, #0x0]
	mov r4, #0x8
_020D8908:
	ldmia r5!, {r0-r3}
	stmia lr!, {r0-r3}
	subs r4, r4, #0x1
	bne _020D8908
	ldr r0, [r5, #0x0]
	add sp, sp, #0x88
	str r0, [lr, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D892C:
	ldrh r0, [r1, #0x3e]
	strb r0, [sp, #0x0]
	ldrb r0, [sp, #0x0]
	cmp r0, #0x0
	bne _020D896C
	add r5, sp, #0x0
	mov r4, #0x8
_020D8948:
	ldmia r5!, {r0-r3}
	stmia lr!, {r0-r3}
	subs r4, r4, #0x1
	bne _020D8948
	ldr r0, [r5, #0x0]
	add sp, sp, #0x88
	str r0, [lr, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D896C:
	cmp r0, #0x10
	movhi r0, #0x10
	strhib r0, [sp, #0x0]
	ldrh r2, [r1, #0x0]
	ldrb r3, [sp, #0x0]
	mov r0, #0x0
	mov r2, r2, lsl #0x1
	sub r4, r2, #0x40
	cmp r3, #0x0
	add r3, r1, #0x40
	mov r2, r0
	and r1, r4, #0xff
	ble _020D8A20
	add r12, sp, #0x0
_020D89A4:
	ldrb r5, [r3, #0x0]
	add r6, r12, r2, lsl #0x3
	add r4, r3, #0x2
	strb r5, [r6, #0x4]
	ldrb r5, [r3, #0x1]
	strb r5, [r6, #0x5]
	str r4, [r6, #0x8]
	ldrb r4, [r6, #0x5]
	add r4, r4, #0x2
	and r5, r4, #0xff
	add r0, r0, r5
	and r0, r0, #0xff
	cmp r0, r1
	bls _020D8A0C
	mov r0, #0x0
	strb r0, [sp, #0x0]
	mov r4, #0x8
_020D89E8:
	ldmia r12!, {r0-r3}
	stmia lr!, {r0-r3}
	subs r4, r4, #0x1
	bne _020D89E8
	ldr r0, [r12, #0x0]
	add sp, sp, #0x88
	str r0, [lr, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D8A0C:
	ldrb r4, [sp, #0x0]
	add r2, r2, #0x1
	add r3, r3, r5
	cmp r2, r4
	blt _020D89A4
_020D8A20:
	add r4, sp, #0x0
	mov r12, #0x8
_020D8A28:
	ldmia r4!, {r0-r3}
	stmia lr!, {r0-r3}
	subs r12, r12, #0x1
	bne _020D8A28
	ldr r0, [r4, #0x0]
	str r0, [lr, #0x0]
	add sp, sp, #0x88
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start WM_GetDispersionScanPeriod
WM_GetDispersionScanPeriod: ; 0x020D8A4C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	add r0, sp, #0x0
	bl OS_GetMacAddress
	mov r2, #0x0
	add r1, sp, #0x0
	mov r3, r2
_020D8A68:
	ldrb r0, [r1, #0x0]
	add r2, r2, #0x1
	cmp r2, #0x6
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	add r1, r1, #0x1
	blt _020D8A68
	ldr r0, _020D8AE4 ; =0x027FFC3C
	mov r1, #0xd
	ldr r0, [r0, #0x0]
	ldr r2, _020D8AE8 ; =0x66666667
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mul r0, r3, r1
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	smull r0, r1, r2, r3
	mov r1, r1, asr #0x2
	mov r0, r3, lsr #0x1f
	ldr r2, _020D8AEC ; =0x0000000A
	add r1, r0, r1
	smull r0, r1, r2, r1
	sub r1, r3, r0
	add r0, r1, #0x1e
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D8AE4: .word 0x027FFC3C
_020D8AE8: .word 0x66666667
_020D8AEC: .word 0x0000000A

	arm_func_start WM_GetDispersionBeaconPeriod
WM_GetDispersionBeaconPeriod: ; 0x020D8AF0
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	add r0, sp, #0x0
	bl OS_GetMacAddress
	mov r2, #0x0
	add r1, sp, #0x0
	mov r3, r2
_020D8B0C:
	ldrb r0, [r1, #0x0]
	add r2, r2, #0x1
	cmp r2, #0x6
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	add r1, r1, #0x1
	blt _020D8B0C
	ldr r0, _020D8B88 ; =0x027FFC3C
	mov r1, #0x7
	ldr r0, [r0, #0x0]
	ldr r2, _020D8B8C ; =0x66666667
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mul r0, r3, r1
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	smull r0, r1, r2, r3
	mov r1, r1, asr #0x3
	mov r0, r3, lsr #0x1f
	ldr r2, _020D8B90 ; =0x00000014
	add r1, r0, r1
	smull r0, r1, r2, r1
	sub r1, r3, r0
	add r0, r1, #0xc8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D8B88: .word 0x027FFC3C
_020D8B8C: .word 0x66666667
_020D8B90: .word 0x00000014

	arm_func_start WM_GetLinkLevel
WM_GetLinkLevel: ; 0x020D8B94
	stmdb sp!, {r4,lr}
	bl WMi_GetSystemWork
	mov r4, r0
	bl WMi_CheckInitialized
_020D8BA4: ; 0x020D8BA4
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ldr r0, [r4, #0x4]
	mov r1, #0x2
	bl DC_InvalidateRange
	ldr r2, [r4, #0x4]
	ldrh r0, [r2, #0x0]
	cmp r0, #0x9
	beq _020D8BE4
	cmp r0, #0xa
	beq _020D8C10
	cmp r0, #0xb
	beq _020D8C10
	b _020D8C2C
_020D8BE4:
	ldr r0, _020D8C38 ; =0x00000182
	mov r1, #0x2
	add r0, r2, r0
	bl DC_InvalidateRange
	ldr r2, [r4, #0x4]
	add r0, r2, #0x100
	ldrh r0, [r0, #0x82]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020D8C10:
	add r0, r2, #0xbc
	mov r1, #0x2
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	ldrh r0, [r0, #0xbc]
	ldmia sp!, {r4,lr}
	bx lr
_020D8C2C:
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D8C38: .word 0x00000182

	arm_func_start WM_GetAllowedChannel
WM_GetAllowedChannel: ; 0x020D8C3C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WMi_CheckInitialized
_020D8C48: ; 0x020D8C48
	cmp r0, #0x0
	movne r0, #0x8000
	ldreq r0, _020D8C64 ; =0x027FFCFA
	ldreqh r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D8C64: .word 0x027FFCFA

	arm_func_start WM_ReadMPData
WM_ReadMPData: ; 0x020D8C68
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x40
	mov r5, r0
	mov r4, r1
	bl WMi_GetSystemWork
	mov r6, r0
	bl WMi_CheckInitialized
_020D8C84: ; 0x020D8C84
	cmp r0, #0x0
	addne sp, sp, #0x40
	movne r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r4, #0x1
	blo _020D8CA8
	cmp r4, #0xf
	bls _020D8CB8
_020D8CA8:
	add sp, sp, #0x40
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D8CB8:
	ldr r2, [r6, #0x4]
	ldr r0, _020D8D68 ; =0x00000182
	mov r1, #0x2
	add r0, r2, r0
	bl DC_InvalidateRange
	ldr r0, [r6, #0x4]
	mov r1, #0x1
	add r0, r0, #0x100
	ldrh r2, [r0, #0x82]
	mov r0, r1, lsl r4
	ands r0, r2, r0
	addeq sp, sp, #0x40
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r0, [r5, #0x4]
	cmp r0, #0x0
	addeq sp, sp, #0x40
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	add r0, r5, #0xa
	str r0, [sp, #0x0]
	mov r3, #0x0
	add r2, sp, #0x0
_020D8D1C:
	ldr r0, [r2, r3, lsl #0x2]
	ldrh r1, [r0, #0x4]
	cmp r4, r1
	addeq sp, sp, #0x40
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	add r3, r3, #0x1
	sub r0, r3, #0x1
	ldrh r1, [r5, #0x6]
	ldr r0, [r2, r0, lsl #0x2]
	add r0, r1, r0
	str r0, [r2, r3, lsl #0x2]
	ldrh r0, [r5, #0x4]
	cmp r3, r0
	blt _020D8D1C
	mov r0, #0x0
	add sp, sp, #0x40
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D8D68: .word 0x00000182

	arm_func_start WM_GetMPReceiveBufferSize
WM_GetMPReceiveBufferSize:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl WMi_GetSystemWork
	mov r4, r0
	mov r0, #0x2
	mov r1, #0x7
	mov r2, #0x8
	bl WMi_CheckStateEx
_020D8D8C: ; 0x020D8D8C
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	add r0, r0, #0xc
	bl DC_InvalidateRange
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0xc]
	cmp r0, #0x1
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	add r0, r1, #0x188
	mov r1, #0x2
	bl DC_InvalidateRange
	ldr r1, [r4, #0x4]
	add r0, r1, #0x100
	ldrh r0, [r0, #0x88]
	cmp r0, #0x0
	moveq r5, #0x1
	add r0, r1, #0x3e
	mov r1, #0x2
	movne r5, #0x0
	bl DC_InvalidateRange
	cmp r5, #0x1
	ldr r0, [r4, #0x4]
	addne sp, sp, #0x4
	ldrh r5, [r0, #0x3e]
	addne r0, r5, #0x51
	bicne r0, r0, #0x1f
	movne r0, r0, lsl #0x1
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	add r0, r0, #0xf8
	mov r1, #0x2
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	add r1, r5, #0xc
	ldrh r0, [r0, #0xf8]
	mul r0, r1, r0
	add r0, r0, #0x29
	bic r0, r0, #0x1f
	mov r0, r0, lsl #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_GetMPSendBufferSize
WM_GetMPSendBufferSize:
	stmdb sp!, {r4,lr}
	bl WMi_GetSystemWork
	mov r4, r0
	mov r0, #0x2
	mov r1, #0x7
	mov r2, #0x8
	bl WMi_CheckStateEx
_020D8E70: ; 0x020D8E70
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	add r0, r0, #0xc
	bl DC_InvalidateRange
	ldr r1, [r4, #0x4]
	ldr r0, [r1, #0xc]
	cmp r0, #0x1
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r0, r1, #0x3c
	mov r1, #0x4
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	ldrh r0, [r0, #0x3c]
	add r0, r0, #0x1f
	bic r0, r0, #0x1f
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_ReadStatus
WM_ReadStatus: ; 0x020D8ECC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl WMi_GetSystemWork
	mov r4, r0
	bl WMi_CheckInitialized
_020D8EE4: ; 0x020D8EE4
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r5, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r4, #0x4]
	mov r1, #0x7c0
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	mov r1, r5
	mov r2, #0x7c0
	bl MIi_CpuCopyFast
_020D8F24: ; 0x020D8F24
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_SetPortCallback
WM_SetPortCallback:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x48
	movs r5, r1
	mov r6, r0
	mov r4, r2
	beq _020D8F9C
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x44
	bl MI_CpuFill8
	mov r3, #0x0
	ldr r1, _020D9010 ; =0x0000FFFF
	mov r7, #0x82
	mov r2, #0x19
	add r0, sp, #0x14
	strh r7, [sp, #0x0]
	strh r3, [sp, #0x2]
	strh r2, [sp, #0x4]
	strh r6, [sp, #0x6]
	str r3, [sp, #0x8]
	str r3, [sp, #0xc]
	strh r3, [sp, #0x10]
	strh r1, [sp, #0x1a]
	str r4, [sp, #0x1c]
	strh r3, [sp, #0x12]
	bl OS_GetMacAddress
_020D8F9C:
	bl OS_DisableInterrupts
	mov r8, r0
	bl WMi_CheckInitialized
	movs r7, r0
	beq _020D8FC8
	mov r0, r8
	bl OS_RestoreInterrupts
	add sp, sp, #0x48
	mov r0, r7
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D8FC8:
	bl WMi_GetSystemWork
	add r0, r0, r6, lsl #0x2
	str r5, [r0, #0xcc]
	str r4, [r0, #0x10c]
	cmp r5, #0x0
	beq _020D8FF8
	bl WM_GetConnectedAIDs
	strh r0, [sp, #0x22]
	bl WM_GetAID
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	blx r5
_020D8FF8:
	mov r0, r8
	bl OS_RestoreInterrupts
_020D9000: ; 0x020D9000
	mov r0, #0x0
	add sp, sp, #0x48
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D9010: .word 0x0000FFFF

	arm_func_start WM_SetIndCallback
WM_SetIndCallback: ; 0x020D9014
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	mov r5, r0
	bl WMi_CheckInitialized
	movs r4, r0
	beq _020D9044
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D9044:
	bl WMi_GetSystemWork
	str r6, [r0, #0xc8]
	mov r0, r5
	bl OS_RestoreInterrupts
_020D9054: ; 0x020D9054
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start WM_Disconnect
WM_Disconnect: ; 0x020D9060
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	mov r5, r1
	bl WMi_GetSystemWork
	mov r1, #0xa
	mov r4, r0
	str r1, [sp, #0x0]
	mov r12, #0xb
	mov r0, #0x5
	mov r1, #0x7
	mov r2, #0x9
	mov r3, #0x8
	str r12, [sp, #0x4]
	bl WMi_CheckStateEx
_020D909C: ; 0x020D909C
	cmp r0, #0x0
	addne sp, sp, #0x8
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr r2, [r4, #0x4]
	ldrh r0, [r2, #0x0]
	cmp r0, #0x7
	beq _020D90C4
	cmp r0, #0x9
	bne _020D9120
_020D90C4:
	cmp r5, #0x1
	blo _020D90D4
	cmp r5, #0xf
	bls _020D90E4
_020D90D4:
	add sp, sp, #0x8
	mov r0, #0x6
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D90E4:
	ldr r0, _020D9164 ; =0x00000182
	mov r1, #0x2
	add r0, r2, r0
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	add r0, r0, #0x100
	ldrh r2, [r0, #0x82]
	mov r0, r1, lsl r5
	ands r0, r2, r0
	bne _020D9134
	add sp, sp, #0x8
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D9120:
	cmp r5, #0x0
	addne sp, sp, #0x8
	movne r0, #0x6
	ldmneia sp!, {r4-r6,lr}
	bxne lr
_020D9134:
	mov r1, r6
	mov r0, #0xd
	bl WMi_SetCallbackTable
	mov r1, #0x1
	mov r2, r1, lsl r5
	mov r0, #0xd
	bl WMi_SendCommand
_020D9150: ; 0x020D9150
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D9164: .word 0x00000182

	arm_func_start WM_StartConnectEx
WM_StartConnectEx: ; 0x020D9168
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x2c
	mov r7, r0
	mov r6, r1
	mov r0, #0x1
	mov r1, #0x2
	mov r5, r2
	mov r4, r3
	bl WMi_CheckStateEx
_020D918C: ; 0x020D918C
	cmp r0, #0x0
	addne sp, sp, #0x2c
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r6, #0x0
	addeq sp, sp, #0x2c
	moveq r0, #0x6
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrh r1, [r6, #0x0]
	mov r0, r6
	mov r1, r1, lsl #0x1
	bl DC_StoreRange
	bl WMi_GetSystemWork
	add r1, r0, #0x100
	mov r2, #0x0
	strh r2, [r1, #0x50]
	str r2, [r0, #0x14c]
	mov r1, r7
	mov r0, #0xc
	bl WMi_SetCallbackTable
	mov r0, #0xc
	strh r0, [sp, #0x0]
	str r6, [sp, #0x4]
	cmp r5, #0x0
	beq _020D9208
	add r1, sp, #0x8
	mov r0, r5
	mov r2, #0x18
	bl MI_CpuCopy8
	b _020D9218
_020D9208:
	add r0, sp, #0x8
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
_020D9218:
	ldrh r2, [sp, #0x40]
	add r0, sp, #0x0
	mov r1, #0x28
	str r4, [sp, #0x20]
	strh r2, [sp, #0x26]
	bl WMi_SendCommandDirect
_020D9230: ; 0x020D9230
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x2c
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WM_EndScan
WM_EndScan: ; 0x020D9244
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r1, #0x5
	bl WMi_CheckStateEx
_020D9258: ; 0x020D9258
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0xb
	bl WMi_SetCallbackTable
	mov r0, #0xb
	mov r1, #0x0
	bl WMi_SendCommand
_020D927C: ; 0x020D927C
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_StartScanEx
WM_StartScanEx: ; 0x020D928C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x3c
	mov r5, r0
	mov r0, #0x3
	mov r4, r1
	mov r2, r0
	mov r1, #0x2
	mov r3, #0x5
	bl WMi_CheckStateEx
_020D92B0: ; 0x020D92B0
	cmp r0, #0x0
	addne sp, sp, #0x3c
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	addeq sp, sp, #0x3c
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x3c
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrh r0, [r4, #0x4]
	cmp r0, #0x400
	addhi sp, sp, #0x3c
	movhi r0, #0x6
	ldmhiia sp!, {r4-r5,lr}
	bxhi lr
	ldrh r0, [r4, #0x12]
	cmp r0, #0x20
	addhi sp, sp, #0x3c
	movhi r0, #0x6
	ldmhiia sp!, {r4-r5,lr}
	bxhi lr
	ldrh r1, [r4, #0x10]
	cmp r1, #0x0
	beq _020D934C
	cmp r1, #0x1
	beq _020D934C
	cmp r1, #0x2
	beq _020D934C
	cmp r1, #0x3
	addne sp, sp, #0x3c
	movne r0, #0x6
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020D934C:
	ldr r0, _020D9408 ; =0x0000FFFE
	add r0, r1, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, #0x1
	bhi _020D937C
	ldrh r0, [r4, #0x34]
	cmp r0, #0x20
	addhi sp, sp, #0x3c
	movhi r0, #0x6
	ldmhiia sp!, {r4-r5,lr}
	bxhi lr
_020D937C:
	mov r1, r5
	mov r0, #0x26
	bl WMi_SetCallbackTable
	mov r0, #0x26
	strh r0, [sp, #0x0]
	ldrh r2, [r4, #0x6]
	add r1, sp, #0xc
	add r0, r4, #0xa
	strh r2, [sp, #0x2]
	ldr r3, [r4, #0x0]
	mov r2, #0x6
	str r3, [sp, #0x4]
	ldrh r3, [r4, #0x4]
	strh r3, [sp, #0x8]
	ldrh r3, [r4, #0x8]
	strh r3, [sp, #0xa]
	bl MI_CpuCopy8
	ldrh r2, [r4, #0x10]
	add r1, sp, #0x16
	add r0, r4, #0x14
	strh r2, [sp, #0x12]
	ldrh r3, [r4, #0x34]
	mov r2, #0x20
	strh r3, [sp, #0x36]
	ldrh r3, [r4, #0x12]
	strh r3, [sp, #0x14]
	bl MI_CpuCopy8
_020D93E8: ; 0x020D93E8
	add r0, sp, #0x0
	mov r1, #0x3c
	bl WMi_SendCommandDirect
_020D93F4: ; 0x020D93F4
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x3c
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D9408: .word 0x0000FFFE

	arm_func_start WM_StartScan
WM_StartScan: ; 0x020D940C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	mov r0, #0x3
	mov r4, r1
	mov r2, r0
	mov r1, #0x2
	mov r3, #0x5
	bl WMi_CheckStateEx
_020D9430: ; 0x020D9430
	cmp r0, #0x0
	addne sp, sp, #0x14
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrh r0, [r4, #0x4]
	cmp r0, #0x1
	blo _020D9480
	cmp r0, #0xe
	bls _020D9490
_020D9480:
	add sp, sp, #0x14
	mov r0, #0x6
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D9490:
	mov r1, r5
	mov r0, #0xa
	bl WMi_SetCallbackTable
	mov r0, #0xa
	strh r0, [sp, #0x0]
	ldrh r2, [r4, #0x4]
	add r0, sp, #0x0
	mov r1, #0x10
	strh r2, [sp, #0x2]
	ldr r2, [r4, #0x0]
	str r2, [sp, #0x4]
	ldrh r2, [r4, #0x6]
	strh r2, [sp, #0x8]
	ldrb r2, [r4, #0x8]
	strb r2, [sp, #0xa]
	ldrb r2, [r4, #0x9]
	strb r2, [sp, #0xb]
	ldrb r2, [r4, #0xa]
	strb r2, [sp, #0xc]
	ldrb r2, [r4, #0xb]
	strb r2, [sp, #0xd]
	ldrb r2, [r4, #0xc]
	strb r2, [sp, #0xe]
	ldrb r2, [r4, #0xd]
	strb r2, [sp, #0xf]
	bl WMi_SendCommandDirect
_020D94F8: ; 0x020D94F8
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_EndParent
WM_EndParent: ; 0x020D950C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r1, #0x7
	bl WMi_CheckStateEx
_020D9520: ; 0x020D9520
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x9
	bl WMi_SetCallbackTable
	mov r0, #0x9
	mov r1, #0x0
	bl WMi_SendCommand
_020D9544: ; 0x020D9544
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_StartParent
WM_StartParent: ; 0x020D9554
	ldr ip, _020D9560 ; =FUN_020D9564
	mov r1, #0x1
	bx r12
	.balign 4
_020D9560: .word FUN_020D9564

	arm_func_start FUN_020D9564
FUN_020D9564: ; 0x020D9564
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, #0x1
	mov r1, #0x2
	bl WMi_CheckStateEx
_020D9580: ; 0x020D9580
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	bl WMi_GetSystemWork
	add r1, r0, #0x100
	mov r2, #0x0
	strh r2, [r1, #0x50]
	str r2, [r0, #0x14c]
	mov r1, r5
	mov r0, #0x8
	bl WMi_SetCallbackTable
	mov r2, r4
	mov r0, #0x8
	mov r1, #0x1
	bl WMi_SendCommand
_020D95C0: ; 0x020D95C0
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WmCheckParentParameter
WmCheckParentParameter: ; 0x020D95D4
	ldrh r1, [r0, #0x4]
	cmp r1, #0x70
	movhi r0, #0x0
	bxhi lr
	ldrh r1, [r0, #0x18]
	cmp r1, #0xa
	blo _020D95F8
	cmp r1, #0x3e8
	bls _020D9600
_020D95F8:
	mov r0, #0x0
	bx lr
_020D9600:
	ldrh r0, [r0, #0x32]
	cmp r0, #0x1
	blo _020D9614
	cmp r0, #0xe
	bls _020D961C
_020D9614:
	mov r0, #0x0
	bx lr
_020D961C:
	mov r0, #0x1
	bx lr

	arm_func_start WM_SetParentParameter
WM_SetParentParameter: ; 0x020D9624
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, #0x1
	mov r1, #0x2
	bl WMi_CheckStateEx
_020D9640: ; 0x020D9640
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrh r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020D9688
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x6
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
_020D9688:
	ldrh r1, [r4, #0x14]
	ldrh r0, [r4, #0x34]
	cmp r1, #0x0
	movne r2, #0x2a
	moveq r2, #0x0
	add r0, r0, r2
	cmp r0, #0x200
	bgt _020D96C4
	ldrh r0, [r4, #0x36]
	cmp r1, #0x0
	movne r1, #0x6
	moveq r1, #0x0
	add r0, r0, r1
	cmp r0, #0x200
	ble _020D96D4
_020D96C4:
	add sp, sp, #0x4
	mov r0, #0x6
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D96D4:
	mov r0, r4
	bl WmCheckParentParameter
	mov r1, r5
	mov r0, #0x7
	bl WMi_SetCallbackTable
	mov r0, r4
	mov r1, #0x40
	bl DC_StoreRange
	ldrh r1, [r4, #0x4]
	cmp r1, #0x0
	beq _020D9708
	ldr r0, [r4, #0x0]
	bl DC_StoreRange
_020D9708:
	mov r2, r4
	mov r0, #0x7
	mov r1, #0x1
	bl WMi_SendCommand
_020D9718: ; 0x020D9718
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_End
WM_End: ; 0x020D972C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r1, #0x2
	bl WMi_CheckStateEx
_020D9740: ; 0x020D9740
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x2
	bl WMi_SetCallbackTable
	mov r0, #0x2
	mov r1, #0x0
	bl WMi_SendCommand
_020D9764: ; 0x020D9764
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_Reset
WM_Reset: ; 0x020D9774
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl WMi_CheckIdle
_020D9780: ; 0x020D9780
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x1
	bl WMi_SetCallbackTable
	mov r0, #0x1
	mov r1, #0x0
	bl WMi_SendCommand
_020D97A4: ; 0x020D97A4
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_Initialize
WM_Initialize: ; 0x020D97B4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r1
	mov r1, r2
	bl WM_Init
_020D97C8: ; 0x020D97C8
	cmp r0, #0x0
	addne sp, sp, #0x8
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x0
	bl WMi_SetCallbackTable
	bl WMi_GetSystemWork
	mov r3, r0
	ldr r1, [r3, #0x10]
	mov r0, #0x0
	str r1, [sp, #0x0]
	ldr r2, [r3, #0x0]
	ldr r3, [r3, #0x4]
	mov r1, #0x3
	bl WMi_SendCommand
_020D9808: ; 0x020D9808
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_PowerOff
WM_PowerOff: ; 0x020D981C
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r1, #0x2
	bl WMi_CheckStateEx
_020D9830: ; 0x020D9830
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x6
	bl WMi_SetCallbackTable
	mov r0, #0x6
	mov r1, #0x0
	bl WMi_SendCommand
_020D9854: ; 0x020D9854
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_PowerOn
WM_PowerOn: ; 0x020D9864
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r1, r0
	bl WMi_CheckStateEx
_020D9878: ; 0x020D9878
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x5
	bl WMi_SetCallbackTable
	mov r0, #0x5
	mov r1, #0x0
	bl WMi_SendCommand
_020D989C: ; 0x020D989C
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_Disable
WM_Disable: ; 0x020D98AC
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r1, r0
	bl WMi_CheckStateEx
_020D98C0: ; 0x020D98C0
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x4
	bl WMi_SetCallbackTable
	mov r0, #0x4
	mov r1, #0x0
	bl WMi_SendCommand
_020D98E4: ; 0x020D98E4
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_Enable
WM_Enable: ; 0x020D98F4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	mov r0, #0x1
	mov r1, #0x0
	bl WMi_CheckStateEx
_020D990C: ; 0x020D990C
	cmp r0, #0x0
	addne sp, sp, #0x8
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x3
	bl WMi_SetCallbackTable
	bl WMi_GetSystemWork
	mov r3, r0
	ldr r1, [r3, #0x10]
	mov r0, #0x3
	str r1, [sp, #0x0]
	ldr r2, [r3, #0x0]
	ldr r3, [r3, #0x4]
	mov r1, r0
	bl WMi_SendCommand
_020D994C: ; 0x020D994C
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_EndMP
WM_EndMP: ; 0x020D9960
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl WMi_GetSystemWork
	mov r4, r0
	mov r0, #0x2
	mov r1, #0x9
	mov r2, #0xa
	bl WMi_CheckStateEx
_020D9984: ; 0x020D9984
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	add r0, r0, #0xc
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x3
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r1, r5
	mov r0, #0x10
	bl WMi_SetCallbackTable
	mov r0, #0x10
	mov r1, #0x0
	bl WMi_SendCommand
_020D99D8: ; 0x020D99D8
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_SetMPDataToPortEx
WM_SetMPDataToPortEx: ; 0x020D99EC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x14
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	mov r5, #0x1
	bl WMi_GetSystemWork
	ldr r4, [r0, #0x4]
	mov r0, #0x2
	mov r1, #0x9
	mov r2, #0xa
	bl WMi_CheckStateEx
_020D9A20: ; 0x020D9A20
	cmp r0, #0x0
	addne sp, sp, #0x14
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	add r0, r4, #0x3c
	mov r1, #0x2
	bl DC_InvalidateRange
	add r0, r4, #0x188
	mov r1, #0x2
	bl DC_InvalidateRange
	add r0, r4, #0x100
	ldrh r0, [r0, #0x88]
	cmp r0, #0x0
	bne _020D9A7C
	ldr r0, _020D9B44 ; =0x00000182
	mov r1, #0x2
	add r0, r4, r0
	bl DC_InvalidateRange
	add r2, r4, #0x100
	add r0, r4, #0x86
	mov r1, #0x2
	ldrh r5, [r2, #0x82]
	bl DC_InvalidateRange
_020D9A7C:
	cmp r7, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x6
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r5, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x7
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	add r0, r4, #0x7c
	mov r1, #0x2
	bl DC_InvalidateRange
	ldr r0, [r4, #0x7c]
	cmp r7, r0
	addeq sp, sp, #0x14
	moveq r0, #0x6
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r6, #0x200
	addhi sp, sp, #0x14
	movhi r0, #0x6
	ldmhiia sp!, {r4-r9,lr}
	bxhi lr
	cmp r6, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x6
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r7
	mov r1, r6
	bl DC_StoreRange
	ldrh r2, [sp, #0x30]
	ldrh r1, [sp, #0x34]
	ldrh r0, [sp, #0x38]
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	str r9, [sp, #0xc]
	mov r2, r7
	mov r3, r6
	mov r0, #0xf
	mov r1, #0x7
	str r8, [sp, #0x10]
	bl WMi_SendCommand
_020D9B30: ; 0x020D9B30
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x14
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020D9B44: .word 0x00000182

	arm_func_start WM_StartMP
WM_StartMP: ; 0x020D9B48
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r6, r1
	mov r7, r0
	mov r5, r2
	add r1, sp, #0x8
	mov r0, #0x0
	mov r2, #0x1c
	mov r4, r3
	bl MIi_CpuClear32
	ldrh r12, [sp, #0x3c]
	mov r0, #0x3
	str r0, [sp, #0x8]
	ldrh lr, [sp, #0x38]
	strh r12, [sp, #0xc]
	strh r12, [sp, #0xe]
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	add r12, sp, #0x8
	str lr, [sp, #0x0]
	str r12, [sp, #0x4]
	bl WMi_StartMP
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WM_StartMPEx
WM_StartMPEx: ; 0x020D9BB4
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r6, r1
	mov r7, r0
	mov r5, r2
	add r1, sp, #0x8
	mov r0, #0x0
	mov r2, #0x1c
	mov r4, r3
	bl MIi_CpuClear32
	ldrh lr, [sp, #0x44]
	ldr r1, [sp, #0x58]
	ldrh r12, [sp, #0x48]
	ldr r0, [sp, #0x54]
	ldr r8, _020D9C54 ; =0x00001E03
	cmp r0, #0x0
	ldr r3, [sp, #0x4c]
	ldr r2, [sp, #0x50]
	strb r1, [sp, #0x22]
	strh r12, [sp, #0x1e]
	strb r3, [sp, #0x20]
	strb r2, [sp, #0x21]
	ldrh r1, [sp, #0x40]
	str r8, [sp, #0x8]
	orrne r0, r8, #0x4
	strne r0, [sp, #0x8]
	strh lr, [sp, #0xc]
	strh lr, [sp, #0xe]
	strneh lr, [sp, #0x10]
	str r1, [sp, #0x0]
	add r12, sp, #0x8
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	str r12, [sp, #0x4]
	bl WMi_StartMP
	add sp, sp, #0x28
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D9C54: .word 0x00001E03

	arm_func_start WMi_StartMP
WMi_StartMP: ; 0x020D9C58
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x34
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl WMi_GetSystemWork
	ldr r5, [r0, #0x4]
	mov r0, #0x2
	mov r1, #0x7
	mov r2, #0x8
	bl WMi_CheckStateEx
_020D9C88: ; 0x020D9C88
	cmp r0, #0x0
	addne sp, sp, #0x34
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	add r0, r5, #0x188
	mov r1, #0x2
	bl DC_InvalidateRange
	add r0, r5, #0xc6
	mov r1, #0x2
	bl DC_InvalidateRange
	add r0, r5, #0x100
	ldrh r0, [r0, #0x88]
	cmp r0, #0x0
	beq _020D9CD8
	ldrh r0, [r5, #0xc6]
	cmp r0, #0x1
	addne sp, sp, #0x34
	movne r0, #0x3
	ldmneia sp!, {r4-r9,lr}
	bxne lr
_020D9CD8:
	add r0, r5, #0xc
	mov r1, #0x4
	bl DC_InvalidateRange
	ldr r0, [r5, #0xc]
	cmp r0, #0x1
	addeq sp, sp, #0x34
	moveq r0, #0x3
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ands r0, r7, #0x3f
	addne sp, sp, #0x34
	movne r0, #0x6
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	ldrh r4, [sp, #0x50]
	ands r0, r4, #0x1f
	addne sp, sp, #0x34
	movne r0, #0x6
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	add r0, r5, #0x9c
	mov r1, #0x2
	bl DC_InvalidateRange
	ldrh r0, [r5, #0x9c]
	cmp r0, #0x0
	bne _020D9D70
	bl WM_GetMPReceiveBufferSize
_020D9D44: ; 0x020D9D44
	cmp r7, r0
	addlt sp, sp, #0x34
	movlt r0, #0x6
	ldmltia sp!, {r4-r9,lr}
	bxlt lr
	bl WM_GetMPSendBufferSize
_020D9D5C: ; 0x020D9D5C
	cmp r4, r0
	addlt sp, sp, #0x34
	movlt r0, #0x6
	ldmltia sp!, {r4-r9,lr}
	bxlt lr
_020D9D70:
	mov r1, r9
	mov r0, #0xe
	bl WMi_SetCallbackTable
	add r1, sp, #0x0
	mov r0, #0x0
	mov r2, #0x30
	bl MIi_CpuClear32
	ldrh r3, [sp, #0x50]
	mov r4, r7, lsr #0x1
	mov r5, #0xe
	ldr r0, [sp, #0x54]
	add r1, sp, #0x14
	mov r2, #0x1c
	strh r5, [sp, #0x0]
	str r8, [sp, #0x4]
	str r4, [sp, #0x8]
	str r6, [sp, #0xc]
	str r3, [sp, #0x10]
	bl MIi_CpuCopy32
_020D9DBC: ; 0x020D9DBC
	add r0, sp, #0x0
	mov r1, #0x30
	bl WMi_SendCommandDirect
_020D9DC8: ; 0x020D9DC8
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x34
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start WM_EndDCF
WM_EndDCF: ; 0x020D9DDC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl WMi_GetSystemWork
	mov r4, r0
	mov r0, #0x1
	mov r1, #0xb
	bl WMi_CheckStateEx
_020D9DFC: ; 0x020D9DFC
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	add r0, r0, #0x10
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x3
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r1, r5
	mov r0, #0x13
	bl WMi_SetCallbackTable
	mov r0, #0x13
	mov r1, #0x0
	bl WMi_SendCommand
_020D9E50: ; 0x020D9E50
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_SetDCFData
WM_SetDCFData: ; 0x020D9E64
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl WMi_GetSystemWork
	mov r8, r0
	mov r0, #0x1
	mov r1, #0xb
	bl WMi_CheckStateEx
_020D9E90: ; 0x020D9E90
	cmp r0, #0x0
	addne sp, sp, #0x10
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r0, [r8, #0x4]
	mov r1, #0x4
	add r0, r0, #0x10
	bl DC_InvalidateRange
	ldr r0, [r8, #0x4]
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x3
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, _020D9F3C ; =0x000005E4
	cmp r4, r0
	addhi sp, sp, #0x10
	movhi r0, #0x6
	ldmhiia sp!, {r4-r8,lr}
	bxhi lr
	mov r0, r5
	mov r1, r4
	bl DC_StoreRange
	mov r1, r7
	mov r0, #0x12
	bl WMi_SetCallbackTable
	add r1, sp, #0x8
	mov r0, r6
	mov r2, #0x6
	bl MI_CpuCopy8
	str r5, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r0, #0x12
	mov r1, #0x4
	bl WMi_SendCommand
_020D9F28: ; 0x020D9F28
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D9F3C: .word 0x000005E4

	arm_func_start WM_StartDCF
WM_StartDCF: ; 0x020D9F40
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl WMi_GetSystemWork
	mov r4, r0
	mov r0, #0x1
	mov r1, #0x8
	bl WMi_CheckStateEx
_020D9F68: ; 0x020D9F68
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	add r0, r0, #0x10
	bl DC_InvalidateRange
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	addeq sp, sp, #0x4
	moveq r0, #0x3
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r5, #0x10
	addcc sp, sp, #0x4
	movcc r0, #0x6
	ldmccia sp!, {r4-r7,lr}
	bxcc lr
	cmp r6, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x6
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	mov r1, r5
	bl DC_StoreRange
	mov r1, r7
	mov r0, #0x11
	bl WMi_SetCallbackTable
	mov r2, r6
	mov r3, r5
	mov r0, #0x11
	mov r1, #0x2
	bl WMi_SendCommand
_020D9FF8: ; 0x020D9FF8
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WmGetSharedDataAddress
WmGetSharedDataAddress: ; 0x020DA00C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, #0x1
	mov r3, r12, lsl r3
	sub r3, r3, #0x1
	mov r5, r0
	and r0, r1, r3
	mov r4, r2
	bl FUN_020DDC5C
	add r1, r5, #0x800
	ldrh r1, [r1, #0x10]
	mla r0, r1, r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_GetSharedDataAddress
WM_GetSharedDataAddress: ; 0x020DA048
	stmdb sp!, {r4,lr}
	mov r4, r1
	ldrh lr, [r4, #0x2]
	cmp r0, #0x0
	mov r3, r2
	mov r1, #0x1
	mov r12, r1, lsl r3
	ldrh r1, [r4, #0x0]
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r4, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ands r2, r1, r12
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ands r2, lr, r12
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r2, r4, #0x4
	bl WmGetSharedDataAddress
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WmDataSharingSendDataSet
WmDataSharingSendDataSet:
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x10
	mov r10, r0
	mov r9, r1
	bl OS_DisableInterrupts
	add r1, r10, #0x800
	ldrh r1, [r1, #0x8]
	mov r7, r0
	mov r1, r1, lsl #0x9
	ldrh r1, [r10, r1]
	cmp r1, #0x0
	bne _020DA210
	bl WMi_GetMPReadyAIDs
	add r1, r10, #0x800
	ldrh r6, [r1, #0x8]
	mov r5, r0
	ldrh r1, [r1, #0x18]
	add r0, r6, #0x1
	and r0, r0, #0x3
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	cmp r1, #0x1
	addeq r0, r4, #0x1
	andeq r0, r0, #0x3
	moveq r0, r0, lsl #0x10
	moveq r8, r0, lsr #0x10
	movne r8, r4
	add r1, r10, r8, lsl #0x9
	mov r0, #0x0
	mov r2, #0x200
	bl MIi_CpuClear16
	add r0, r10, #0x800
	ldrh r3, [r0, #0xe]
	orr r2, r5, #0x1
	mov r1, r8, lsl #0x9
	and r2, r3, r2
	strh r2, [r10, r1]
	strh r4, [r0, #0x8]
	ldrh r0, [r0, #0xe]
	mov r1, r6, lsl #0x9
	cmp r9, #0x1
	strh r0, [r10, r1]
	ldreqh r0, [r10, r1]
	biceq r0, r0, #0x1
	streqh r0, [r10, r1]
	mov r0, r7
	bl OS_RestoreInterrupts
	add r3, r10, #0x800
	ldrh r1, [r3, #0xe]
	mov r4, #0x1
	ldr r0, _020DA220 ; =WmDataSharingSetDataCallback
	and r1, r1, r5
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [sp, #0x0]
	ldrh r5, [r3, #0x16]
	mov r1, r10
	add r2, r10, r6, lsl #0x9
	str r5, [sp, #0x4]
	str r4, [sp, #0x8]
	ldrh r3, [r3, #0x14]
	bl WM_SetMPDataToPortEx
	cmp r0, #0x7
	bne _020DA1E4
	add r0, r10, r6, lsl #0x1
	ldr r1, _020DA224 ; =0x0000FFFF
	add r0, r0, #0x800
	strh r1, [r0, #0x0]
	add r0, r10, #0x800
	ldrh r1, [r0, #0xa]
	add sp, sp, #0x10
	add r1, r1, #0x1
	and r1, r1, #0x3
	strh r1, [r0, #0xa]
	ldmia sp!, {r4-r10,lr}
	bx lr
_020DA1E4:
	cmp r0, #0x0
	addeq sp, sp, #0x10
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	cmp r0, #0x2
	addne r0, r10, #0x800
	movne r1, #0x5
	strneh r1, [r0, #0x1c]
	add sp, sp, #0x10
	ldmia sp!, {r4-r10,lr}
	bx lr
_020DA210:
	bl OS_RestoreInterrupts
	add sp, sp, #0x10
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020DA220: .word WmDataSharingSetDataCallback
_020DA224: .word 0x0000FFFF

	arm_func_start WmDataSharingReceiveData
WmDataSharingReceiveData: ; 0x020DA228
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r3, r1
	mov r0, #0x1
	mov r0, r0, lsl r3
	add r12, r7, #0x800
	mov r0, r0, lsl #0x10
	ldrh r1, [r12, #0xe]
	mov r5, r0, lsr #0x10
	mov r6, r2
	ands r0, r1, r5
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrh r4, [r12, #0x8]
	mov r0, r4, lsl #0x9
	ldrh r0, [r7, r0]
	ands r0, r5, r0
	bne _020DA2B4
	ldrh r0, [r12, #0x18]
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	add r0, r4, #0x1
	and r0, r0, #0x3
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	mov r0, r4, lsl #0x9
	ldrh r0, [r7, r0]
	ands r0, r5, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_020DA2B4:
	add r2, r7, r4, lsl #0x9
	mov r0, r7
	add r2, r2, #0x4
	bl WmGetSharedDataAddress
	mov r1, r0
	cmp r6, #0x0
	beq _020DA2E4
	add r0, r7, #0x800
	ldrh r2, [r0, #0x10]
	mov r0, r6
	bl MIi_CpuCopy16
	b _020DA2F4
_020DA2E4:
	add r0, r7, #0x800
	ldrh r2, [r0, #0x10]
	mov r0, #0x0
	bl MIi_CpuClear16
_020DA2F4:
	bl OS_DisableInterrupts
	mov r4, r4, lsl #0x9
	ldrh r3, [r7, r4]
	mvn r1, r5
	add r2, r7, #0x2
	and r1, r3, r1
	strh r1, [r7, r4]
	ldrh r1, [r2, r4]
	orr r1, r1, r5
	strh r1, [r2, r4]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WmDataSharingReceiveCallback_Child
WmDataSharingReceiveCallback_Child: ; 0x020DA32C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r7, [r8, #0x1c]
	cmp r7, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldrh r0, [r8, #0x2]
	cmp r0, #0x0
	bne _020DA458
	ldrh r0, [r8, #0x4]
	cmp r0, #0x15
	bgt _020DA394
	cmp r0, #0x15
	bge _020DA3C4
	cmp r0, #0x9
	ldmgtia sp!, {r4-r8,lr}
	bxgt lr
	cmp r0, #0x7
	ldmltia sp!, {r4-r8,lr}
	bxlt lr
	cmp r0, #0x7
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r0, #0x9
	ldmia sp!, {r4-r8,lr}
	bx lr
_020DA394:
	cmp r0, #0x1a
	ldmgtia sp!, {r4-r8,lr}
	bxgt lr
	cmp r0, #0x19
	ldmltia sp!, {r4-r8,lr}
	bxlt lr
	cmp r0, #0x19
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r0, #0x1a
	ldmia sp!, {r4-r8,lr}
	bx lr
_020DA3C4:
	ldr r4, [r8, #0xc]
	ldrh r6, [r8, #0x10]
	ldrh r5, [r4, #0x0]
	bl WM_GetAID
	add r1, r7, #0x800
	ldrh r1, [r1, #0x14]
	cmp r6, r1
	beq _020DA3EC
	cmp r6, #0x200
	movhi r6, #0x200
_020DA3EC:
	cmp r6, #0x4
	ldmccia sp!, {r4-r8,lr}
	bxcc lr
	mov r1, #0x1
	mov r0, r1, lsl r0
	ands r0, r5, r0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	add r0, r7, #0x800
	ldrh r1, [r0, #0x8]
	mov r0, r4
	mov r2, r6
	add r1, r7, r1, lsl #0x9
	bl MIi_CpuCopy16
	add r1, r7, #0x800
	ldrh r0, [r1, #0x8]
	ldrh r2, [r8, #0x1a]
	add r0, r7, r0, lsl #0x1
	mov r2, r2, asr #0x1
	add r0, r0, #0x800
	strh r2, [r0, #0x0]
	ldrh r0, [r1, #0x8]
	add r0, r0, #0x1
	and r0, r0, #0x3
	strh r0, [r1, #0x8]
	ldmia sp!, {r4-r8,lr}
	bx lr
_020DA458:
	add r0, r7, #0x800
	mov r1, #0x5
	strh r1, [r0, #0x1c]
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start WmDataSharingReceiveCallback_Parent
WmDataSharingReceiveCallback_Parent: ; 0x020DA46C
	stmdb sp!, {r4-r6,lr}
	ldr r4, [r0, #0x1c]
	cmp r4, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	bne _020DA5C4
	ldrh r1, [r0, #0x4]
	cmp r1, #0x15
	bgt _020DA4D0
	cmp r1, #0x15
	bge _020DA504
	cmp r1, #0x9
	ldmgtia sp!, {r4-r6,lr}
	bxgt lr
	cmp r1, #0x7
	ldmltia sp!, {r4-r6,lr}
	bxlt lr
	cmp r1, #0x7
	beq _020DA528
	cmp r1, #0x9
	beq _020DA53C
	ldmia sp!, {r4-r6,lr}
	bx lr
_020DA4D0:
	cmp r1, #0x1a
	ldmgtia sp!, {r4-r6,lr}
	bxgt lr
	cmp r1, #0x19
	ldmltia sp!, {r4-r6,lr}
	bxlt lr
	cmp r1, #0x19
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	cmp r1, #0x1a
	beq _020DA53C
	ldmia sp!, {r4-r6,lr}
	bx lr
_020DA504:
	ldrh r1, [r0, #0x12]
	ldr r2, [r0, #0xc]
	mov r0, r4
	bl WmDataSharingReceiveData
	mov r0, r4
	mov r1, #0x0
	bl WmDataSharingSendDataSet
	ldmia sp!, {r4-r6,lr}
	bx lr
_020DA528:
	mov r0, r4
	mov r1, #0x0
	bl WmDataSharingSendDataSet
	ldmia sp!, {r4-r6,lr}
	bx lr
_020DA53C:
	ldrh r5, [r0, #0x12]
	mov r6, #0x1
	bl OS_DisableInterrupts
	add r1, r4, #0x800
	ldrh lr, [r1, #0x8]
	mvn r12, r6, lsl r5
	mov r3, lr, lsl #0x9
	ldrh r2, [r4, r3]
	and r2, r2, r12
	strh r2, [r4, r3]
	ldrh r1, [r1, #0x18]
	cmp r1, #0x1
	bne _020DA58C
	add r1, lr, #0x1
	and r1, r1, #0x3
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x7
	ldrh r1, [r4, r2]
	and r1, r1, r12
	strh r1, [r4, r2]
_020DA58C:
	bl OS_RestoreInterrupts
	mov r0, r4
	mov r1, #0x0
	bl WmDataSharingSendDataSet
	add r0, r4, #0x800
	ldrh r0, [r0, #0x18]
	cmp r0, #0x1
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r4
	mov r1, #0x0
	bl WmDataSharingSendDataSet
	ldmia sp!, {r4-r6,lr}
	bx lr
_020DA5C4:
	add r0, r4, #0x800
	mov r1, #0x5
	strh r1, [r0, #0x1c]
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start WmDataSharingSetDataCallback
WmDataSharingSetDataCallback: ; 0x020DA5D8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl WMi_GetSystemWork
	ldrh r2, [r5, #0xa]
	ldr r1, _020DA6E4 ; =WmDataSharingReceiveCallback_Parent
	add r0, r0, r2, lsl #0x2
	ldr r2, [r0, #0xcc]
	ldr r4, [r0, #0x10c]
	cmp r2, r1
	beq _020DA618
	ldr r0, _020DA6E8 ; =WmDataSharingReceiveCallback_Child
	cmp r2, r0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020DA618:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r5, #0x20]
	cmp r4, r0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	bl WM_GetAID
	ldrh r1, [r5, #0x2]
	cmp r1, #0x0
	bne _020DA694
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	add r1, r4, #0x800
	ldrh r0, [r1, #0xa]
	ldrh r2, [r5, #0x1a]
	add sp, sp, #0x4
	add r0, r4, r0, lsl #0x1
	mov r2, r2, asr #0x1
	add r0, r0, #0x800
	strh r2, [r0, #0x0]
	ldrh r0, [r1, #0xa]
	add r0, r0, #0x1
	and r0, r0, #0x3
	strh r0, [r1, #0xa]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020DA694:
	cmp r1, #0xa
	bne _020DA6CC
	cmp r0, #0x0
	addne r0, r4, #0x800
	ldrneh r1, [r0, #0xa]
	add sp, sp, #0x4
	addne r1, r1, #0x3
	andne r1, r1, #0x3
	strneh r1, [r0, #0xa]
	add r0, r4, #0x800
	mov r1, #0x4
	strh r1, [r0, #0x1c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020DA6CC:
	add r0, r4, #0x800
	mov r1, #0x5
	strh r1, [r0, #0x1c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DA6E4: .word WmDataSharingReceiveCallback_Parent
_020DA6E8: .word WmDataSharingReceiveCallback_Child

	arm_func_start WM_StepDataSharing
WM_StepDataSharing: ; 0x020DA6EC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	mov r9, r1
	mov r8, r2
	mov r0, #0x2
	mov r1, #0x9
	mov r2, #0xa
	bl WMi_CheckStateEx
_020DA710: ; 0x020DA710
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	cmp r10, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x6
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	cmp r9, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x6
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	cmp r8, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x6
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	bl WM_GetAID
	movs r4, r0
	bne _020DA770
	bl WMi_GetMPReadyAIDs
	mov r7, r0
_020DA770:
	add r0, r10, #0x800
	ldrh r0, [r0, #0x1c]
	cmp r0, #0x5
	addeq sp, sp, #0xc
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	cmp r0, #0x1
	beq _020DA7A8
	cmp r0, #0x4
	addne sp, sp, #0xc
	movne r0, #0x3
	ldmneia sp!, {r4-r11,lr}
	bxne lr
_020DA7A8:
	cmp r4, #0x0
	mov r4, #0x5
	bne _020DA94C
	mov r6, #0x0
	mov r11, r6
	cmp r0, #0x4
	bne _020DA870
	add r1, r10, #0x800
	mov r3, #0x1
	strh r3, [r1, #0x1c]
	ldrh r5, [r1, #0xe]
	ldrh r2, [r1, #0x8]
	ldr r0, _020DAA64 ; =WmDataSharingSetDataCallback
	and r5, r5, r7
	mov r5, r5, lsl #0x10
	mov r5, r5, lsr #0x10
	str r5, [sp, #0x0]
	ldrh r5, [r1, #0x16]
	add r2, r2, #0x3
	and r2, r2, #0x3
	str r5, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r2, r2, lsl #0x10
	mov r5, r2, lsr #0x10
	ldrh r3, [r1, #0x14]
	mov r1, r10
	add r2, r10, r5, lsl #0x9
	bl WM_SetMPDataToPortEx
	cmp r0, #0x7
	bne _020DA848
	add r0, r10, r5, lsl #0x1
	ldr r1, _020DAA68 ; =0x0000FFFF
	add r0, r0, #0x800
	strh r1, [r0, #0x0]
	add r0, r10, #0x800
	ldrh r1, [r0, #0xa]
	add r1, r1, #0x1
	and r1, r1, #0x3
	strh r1, [r0, #0xa]
	b _020DA870
_020DA848:
	cmp r0, #0x0
	beq _020DA870
	cmp r0, #0x2
	addne r0, r10, #0x800
	movne r1, r4
	strneh r1, [r0, #0x1c]
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
_020DA870:
	add r0, r10, #0x800
	ldrh r2, [r0, #0xc]
	ldrh r1, [r0, #0xa]
	cmp r2, r1
	beq _020DA908
	mov r4, r2, lsl #0x9
	ldrh r3, [r10, r4]
	mov r1, r8
	mov r2, #0x200
	orr r3, r3, #0x1
	strh r3, [r10, r4]
	ldrh r0, [r0, #0xc]
	add r0, r10, r0, lsl #0x9
	bl MIi_CpuCopy16
	add r1, r10, #0x800
	ldrh r0, [r1, #0xc]
	mov r6, #0x1
	mov r4, #0x0
	add r0, r10, r0, lsl #0x1
	add r0, r0, #0x800
	ldrh r0, [r0, #0x0]
	strh r0, [r1, #0x1a]
	ldrh r0, [r1, #0xc]
	add r0, r0, #0x1
	and r0, r0, #0x3
	strh r0, [r1, #0xc]
	ldrh r0, [r1, #0x18]
	cmp r0, #0x0
	bne _020DA904
	cmp r7, #0x0
	beq _020DA904
	ldrh r0, [r1, #0x8]
	mov r0, r0, lsl #0x9
	ldrh r0, [r10, r0]
	cmp r0, #0x1
	moveq r11, r6
	beq _020DA908
_020DA904:
	mov r11, #0x0
_020DA908:
	mov r0, r10
	mov r1, #0x0
	bl WmDataSharingSendDataSet
_020DA914: ; 0x020DA914
	cmp r6, #0x0
	beq _020DAA54
	mov r0, r10
	mov r2, r9
	mov r1, #0x0
	bl WmDataSharingReceiveData
	add r0, r10, #0x800
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	bne _020DAA54
	mov r0, r10
	mov r1, r11
	bl WmDataSharingSendDataSet
	b _020DAA54
_020DA94C:
	cmp r0, #0x4
	mov r0, #0x0
	addeq r1, r10, #0x800
	moveq r0, #0x1
	streqh r0, [r1, #0x1c]
	beq _020DA9D0
	add r1, r10, #0x800
	ldrh r2, [r1, #0xc]
	ldrh r1, [r1, #0x8]
	cmp r2, r1
	beq _020DA9D0
	mov r2, r2, lsl #0x9
	ldrh r1, [r10, r2]
	ands r3, r1, #0x1
	orreq r1, r1, #0x1
	streqh r1, [r10, r2]
	beq _020DA9D0
	mov r1, r8
	add r0, r10, r2
	mov r2, #0x200
	bl MIi_CpuCopy16
	add r2, r10, #0x800
	ldrh r1, [r2, #0xc]
	mov r0, #0x1
	mov r4, #0x0
	add r1, r10, r1, lsl #0x1
	add r1, r1, #0x800
	ldrh r1, [r1, #0x0]
	strh r1, [r2, #0x1a]
	ldrh r1, [r2, #0xc]
	add r1, r1, #0x1
	and r1, r1, #0x3
	strh r1, [r2, #0xc]
_020DA9D0:
	cmp r0, #0x0
	beq _020DAA54
	add r0, r10, #0x800
	ldrh r1, [r0, #0xa]
	ldrh r2, [r0, #0x10]
	mov r0, r9
	add r1, r10, r1, lsl #0x9
	add r7, r1, #0x20
	mov r1, r7
	bl MIi_CpuCopy16
	add r3, r10, #0x800
	ldrh r1, [r3, #0xe]
	mov r5, #0x1
	ldr r0, _020DAA64 ; =WmDataSharingSetDataCallback
	str r1, [sp, #0x0]
	ldrh r6, [r3, #0x16]
	mov r1, r10
	mov r2, r7
	str r6, [sp, #0x4]
	str r5, [sp, #0x8]
	ldrh r3, [r3, #0x10]
	bl WM_SetMPDataToPortEx
	add r1, r10, #0x800
	ldrh r2, [r1, #0xa]
	cmp r0, #0x2
	add r2, r2, #0x1
	and r2, r2, #0x3
	strh r2, [r1, #0xa]
	beq _020DAA54
	cmp r0, #0x0
	movne r0, #0x5
	strneh r0, [r1, #0x1c]
	movne r4, r5
_020DAA54:
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020DAA64: .word WmDataSharingSetDataCallback
_020DAA68: .word 0x0000FFFF

	arm_func_start WM_EndDataSharing
WM_EndDataSharing: ; 0x020DAA6C
	stmdb sp!, {r4,lr}
	movs r4, r0
	moveq r0, #0x6
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r0, r4, #0x800
	ldrh r1, [r0, #0xe]
	cmp r1, #0x0
	moveq r0, #0x3
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrh r0, [r0, #0x16]
	mov r1, #0x0
	mov r2, r1
	bl WM_SetPortCallback
	add r1, r4, #0x800
	mov r0, #0x0
	strh r0, [r1, #0xe]
	strh r0, [r1, #0x1c]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_StartDataSharing
WM_StartDataSharing: ; 0x020DAAC0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	mov r7, r1
	mov r6, r2
	mov r0, #0x2
	mov r1, #0x9
	mov r2, #0xa
	mov r5, r3
	mov r9, #0x1
	bl WMi_CheckStateEx
_020DAAEC: ; 0x020DAAEC
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	cmp r10, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x6
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	cmp r7, #0x10
	addcs sp, sp, #0xc
	movcs r0, #0x6
	ldmcsia sp!, {r4-r11,lr}
	bxcs lr
	cmp r6, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x6
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	bl WM_GetAID
	movs r4, r0
	bne _020DAB4C
	bl WMi_GetMPReadyAIDs
	mov r9, r0
_020DAB4C:
	mov r1, r10
	mov r0, #0x0
	mov r2, #0x820
	bl MIi_CpuClearFast
	add r0, r10, #0x800
	mov r2, #0x0
	strh r2, [r0, #0x8]
	strh r2, [r0, #0xa]
	strh r2, [r0, #0xc]
	strh r5, [r0, #0x10]
	strh r7, [r0, #0x16]
	strh r2, [r0, #0xe]
	mov r0, #0x1
	ldr r1, [sp, #0x30]
	orr r0, r6, r0, lsl r4
	cmp r1, #0x0
	mov r0, r0, lsl #0x10
	movne r2, #0x1
	add r1, r10, #0x800
	strh r2, [r1, #0x18]
	mov r0, r0, lsr #0x10
	strh r0, [r1, #0xe]
	bl FUN_020DDC5C
	add r3, r10, #0x800
	mul r1, r5, r0
	strh r0, [r3, #0x12]
	strh r1, [r3, #0x14]
	ldrh r0, [r3, #0x14]
	cmp r0, #0x1fc
	movhi r0, #0x0
	strhih r0, [r3, #0xe]
	addhi sp, sp, #0xc
	movhi r0, #0x6
	ldmhiia sp!, {r4-r11,lr}
	bxhi lr
	add r0, r0, #0x4
	strh r0, [r3, #0x14]
	mov r0, #0x1
	strh r0, [r3, #0x1c]
	cmp r4, #0x0
	bne _020DAD04
	orr r2, r9, #0x1
	mov r4, #0x0
_020DABF8:
	ldrh r1, [r3, #0xe]
	mov r0, r4, lsl #0x9
	add r4, r4, #0x1
	and r1, r1, r2
	strh r1, [r10, r0]
	cmp r4, #0x4
	blt _020DABF8
	ldr r1, _020DAD2C ; =WmDataSharingReceiveCallback_Parent
	mov r0, r7
	mov r2, r10
	bl WM_SetPortCallback
	mov r8, r10
	mov r7, #0x0
	mov r4, #0x2
	mov r6, #0x1
	ldr fp, _020DAD30 ; =WmDataSharingSetDataCallback
	ldr r5, _020DAD34 ; =0x0000FFFF
	b _020DACE4
_020DAC40:
	add r12, r10, #0x800
	ldrh r2, [r12, #0x8]
	mov r0, r11
	mov r1, r10
	add r2, r2, #0x1
	and r2, r2, #0x3
	strh r2, [r12, #0x8]
	ldrh r3, [r12, #0xe]
	mov r2, r8
	and r3, r3, r9
	mov r3, r3, lsl #0x10
	mov r3, r3, lsr #0x10
	str r3, [sp, #0x0]
	ldrh r3, [r12, #0x16]
	str r3, [sp, #0x4]
	str r6, [sp, #0x8]
	ldrh r3, [r12, #0x14]
	bl WM_SetMPDataToPortEx
	cmp r0, #0x7
	bne _020DACB4
	add r0, r10, r7, lsl #0x1
	add r0, r0, #0x800
	strh r5, [r0, #0x0]
	add r0, r10, #0x800
	ldrh r1, [r0, #0xa]
	add r1, r1, #0x1
	and r1, r1, #0x3
	strh r1, [r0, #0xa]
	b _020DACDC
_020DACB4:
	cmp r0, #0x0
	beq _020DACDC
	cmp r0, #0x2
	addne r0, r10, #0x800
	movne r1, #0x5
	strneh r1, [r0, #0x1c]
	addne sp, sp, #0xc
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
_020DACDC:
	add r8, r8, #0x200
	add r7, r7, #0x1
_020DACE4:
	add r0, r10, #0x800
	ldrh r0, [r0, #0x18]
	cmp r0, #0x1
	movne r0, r6
	moveq r0, r4
	cmp r7, r0
	blt _020DAC40
	b _020DAD1C
_020DAD04:
	ldr r1, _020DAD38 ; =WmDataSharingReceiveCallback_Child
	mov r4, #0x3
	mov r0, r7
	mov r2, r10
	strh r4, [r3, #0xa]
	bl WM_SetPortCallback
_020DAD1C:
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020DAD2C: .word WmDataSharingReceiveCallback_Parent
_020DAD30: .word WmDataSharingSetDataCallback
_020DAD34: .word 0x0000FFFF
_020DAD38: .word WmDataSharingReceiveCallback_Child

	arm_func_start WM_EndKeySharing
WM_EndKeySharing: ; 0x020DAD3C
	ldr ip, _020DAD44 ; =WM_EndDataSharing
	bx r12
	.balign 4
_020DAD44: .word WM_EndDataSharing

	arm_func_start WM_StartKeySharing
WM_StartKeySharing: ; 0x020DAD48
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020DAD70 ; =0x0000FFFF
	mov r12, #0x1
	mov r3, #0x2
	str r12, [sp, #0x0]
	bl WM_StartDataSharing
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DAD70: .word 0x0000FFFF

	arm_func_start WM_SetEntry
WM_SetEntry: ; 0x020DAD74
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, #0x2
	mov r1, #0x7
	mov r2, #0x9
	bl WMi_CheckStateEx
_020DAD94: ; 0x020DAD94
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, r5
	mov r0, #0x21
	bl WMi_SetCallbackTable
	mov r2, r4
	mov r0, #0x21
	mov r1, #0x1
	bl WMi_SendCommand
_020DADC0: ; 0x020DADC0
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_MeasureChannel
WM_MeasureChannel: ; 0x020DADD4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl WMi_GetSystemWork
	mov r0, #0x1
	mov r1, #0x2
	bl WMi_CheckStateEx
_020DADFC: ; 0x020DADFC
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r1, r7
	mov r0, #0x1e
	bl WMi_SetCallbackTable
	ldrh r2, [sp, #0x20]
	mov r3, #0x1e
	add r0, sp, #0x0
	mov r1, #0xa
	strh r3, [sp, #0x0]
	strh r6, [sp, #0x2]
	strh r5, [sp, #0x4]
	strh r4, [sp, #0x6]
	strh r2, [sp, #0x8]
	bl WMi_SendCommandDirect
_020DAE40: ; 0x020DAE40
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WM_SetLifeTime
WM_SetLifeTime: ; 0x020DAE54
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl WMi_CheckIdle
_020DAE70: ; 0x020DAE70
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r1, r7
	mov r0, #0x1d
	bl WMi_SetCallbackTable
	ldrh r12, [sp, #0x20]
	str r4, [sp, #0x0]
	mov r2, r6
	mov r3, r5
	mov r0, #0x1d
	mov r1, #0x4
	str r12, [sp, #0x4]
	bl WMi_SendCommand
_020DAEAC: ; 0x020DAEAC
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WM_SetBeaconIndication
WM_SetBeaconIndication: ; 0x020DAEC0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
_020DAECC: ; 0x020DAECC
	mov r4, r1
	bl WMi_CheckIdle
_020DAED4: ; 0x020DAED4
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	beq _020DAF00
	cmp r4, #0x1
	addne sp, sp, #0x4
	movne r0, #0x6
	ldmneia sp!, {r4-r5,lr}
	bxne lr
_020DAF00:
	mov r1, r5
	mov r0, #0x19
	bl WMi_SetCallbackTable
	mov r2, r4
	mov r0, #0x19
	mov r1, #0x1
	bl WMi_SendCommand
_020DAF1C: ; 0x020DAF1C
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WM_SetGameInfo
WM_SetGameInfo: ; 0x020DAF30
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r0, #0x2
	mov r1, #0x7
	mov r2, #0x9
	mov r4, r3
	bl WMi_CheckStateEx
_020DAF58: ; 0x020DAF58
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r6, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x6
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r5, #0x70
	addhi sp, sp, #0xc
	movhi r0, #0x6
	ldmhiia sp!, {r4-r7,lr}
	bxhi lr
	ldr r1, _020DAFF4 ; =0x021D68C0
	mov r0, r6
	mov r2, r5
	bl MIi_CpuCopy16
	ldr r0, _020DAFF4 ; =0x021D68C0
	mov r1, r5
	bl DC_StoreRange
	mov r1, r7
	mov r0, #0x18
	bl WMi_SetCallbackTable
	ldrh r0, [sp, #0x20]
	str r4, [sp, #0x0]
	ldrb r1, [sp, #0x24]
	str r0, [sp, #0x4]
	ldr r2, _020DAFF4 ; =0x021D68C0
	str r1, [sp, #0x8]
	mov r3, r5
	mov r0, #0x18
	mov r1, #0x5
	bl WMi_SendCommand
_020DAFE0: ; 0x020DAFE0
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DAFF4: .word 0x021D68C0

	arm_func_start WM_SetWEPKeyEx
WM_SetWEPKeyEx: ; 0x020DAFF8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl WMi_CheckIdle
_020DB014: ; 0x020DB014
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r6, #0x3
	addhi sp, sp, #0x4
	movhi r0, #0x6
	ldmhiia sp!, {r4-r7,lr}
	bxhi lr
	cmp r6, #0x0
	beq _020DB060
	cmp r4, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x6
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x50
	bl DC_StoreRange
_020DB060:
	mov r1, r7
	mov r0, #0x27
	bl WMi_SetCallbackTable
	mov r2, r6
	mov r3, r4
	mov r0, #0x27
	mov r1, #0x3
	str r5, [sp, #0x0]
	bl WMi_SendCommand
_020DB084: ; 0x020DB084
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WM_SetWEPKeyEx2
WM_SetWEPKeyEx2: ; 0x020DB098
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl WMi_CheckIdle
_020DB0AC: ; 0x020DB0AC
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	cmp r5, #0x3
	movhi r0, #0x6
	ldmhiia sp!, {r4-r6,lr}
	bxhi lr
	cmp r5, #0x0
	beq _020DB0EC
	cmp r4, #0x0
	moveq r0, #0x6
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x50
	bl DC_StoreRange
_020DB0EC:
	mov r1, r6
	mov r0, #0x14
	bl WMi_SetCallbackTable
	mov r2, r5
	mov r3, r4
	mov r0, #0x14
	mov r1, #0x2
	bl WMi_SendCommand
_020DB10C: ; 0x020DB10C
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4-r6,lr}
	bx lr
