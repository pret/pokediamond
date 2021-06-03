	.include "asm/macros.inc"
	.include "global.inc"

	.text

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
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0xb
	bl WMi_SetCallbackTable
	mov r0, #0xb
	mov r1, #0x0
	bl WMi_SendCommand
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
	add r0, sp, #0x0
	mov r1, #0x3c
	bl WMi_SendCommandDirect
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
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x9
	bl WMi_SetCallbackTable
	mov r0, #0x9
	mov r1, #0x0
	bl WMi_SendCommand
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_StartParent
WM_StartParent: ; 0x020D9554
	ldr ip, _020D9560 ; =WMi_StartParentEx
	mov r1, #0x1
	bx r12
	.balign 4
_020D9560: .word WMi_StartParentEx

	arm_func_start WMi_StartParentEx
WMi_StartParentEx: ; 0x020D9564
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r0, #0x1
	mov r1, #0x2
	bl WMi_CheckStateEx
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
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x2
	bl WMi_SetCallbackTable
	mov r0, #0x2
	mov r1, #0x0
	bl WMi_SendCommand
	cmp r0, #0x0
	moveq r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WM_Reset
WM_Reset: ; 0x020D9774
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl WMi_CheckIdle
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x1
	bl WMi_SetCallbackTable
	mov r0, #0x1
	mov r1, #0x0
	bl WMi_SendCommand
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
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x6
	bl WMi_SetCallbackTable
	mov r0, #0x6
	mov r1, #0x0
	bl WMi_SendCommand
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
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x5
	bl WMi_SetCallbackTable
	mov r0, #0x5
	mov r1, #0x0
	bl WMi_SendCommand
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
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	mov r1, r4
	mov r0, #0x4
	bl WMi_SetCallbackTable
	mov r0, #0x4
	mov r1, #0x0
	bl WMi_SendCommand
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
	cmp r0, #0x0
	moveq r0, #0x2
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
