	.include "asm/macros.inc"
	.include "global.inc"

	.text

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

	arm_func_start WM_SetWEPKey
WM_SetWEPKey: ; 0x020DB098
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
