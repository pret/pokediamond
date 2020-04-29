    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_ResetSystem
OS_ResetSystem: ; 0x020CD3B4
	stmdb sp!, {r4,lr}
	ldr r1, _020CD42C ; =0x027FFC40
	mov r4, r0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x2
	bne _020CD3D0
	bl OS_Terminate
_020CD3D0:
	bl OS_GetLockID
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl CARD_LockRom
_020CD3E0:
	mov r0, #0x0
	bl MI_StopDma
	mov r0, #0x1
	bl MI_StopDma
	mov r0, #0x2
	bl MI_StopDma
	mov r0, #0x3
	bl MI_StopDma
	mov r0, #0x40000
	bl OS_SetIrqMask
	mvn r0, #0x0
	bl OS_ResetRequestIrqMask
	ldr r1, _020CD430
	mov r0, #0x10
	str r4, [r1]
	bl OSi_SendToPxi
	bl OSi_DoResetSystem
	ldmia sp!, {r4, lr}
	bx lr
_020CD42C: .word 0x027FFC40
_020CD430: .word 0x027FFC20

	arm_func_start OSi_SendToPxi
OSi_SendToPxi: ; 0x020CD434
	stmdb sp!, {r4-r6,lr}
	mov r6, r0, lsl #0x8
	mov r5, #0xc
	mov r4, #0x0
_020CD444:
	mov r0, r5
	mov r1, r6
	mov r2, r4
	bl PXI_SendWordByFifo
_020CD454:
	cmp r0, #0x0
	bne _020CD444
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start OSi_CommonCallback
OSi_CommonCallback: ; OSi_CommonCallback
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x7f00
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	cmp r0, #0x10
	ldreq r0, _020CD4A4 ; =OSi_IsResetOccurred
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
_020CD4A4: .word OSi_IsResetOccurred

	arm_func_start OS_InitReset
OS_InitReset: ; 0x020CD4A8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020CD508 ; =0x021D37DC
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, #0x1
	strh r1, [r0, #0x0]
	bl PXI_Init
	mov r5, #0xc
	mov r4, #0x1
_020CD4DC:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020CD4E8:
	cmp r0, #0x0
	beq _020CD4DC
	ldr r1, _020CD50C
	mov r0, #0xC
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr
_020CD508: .word OSi_IsInitReset
_020CD50C: .word OSi_CommonCallback
