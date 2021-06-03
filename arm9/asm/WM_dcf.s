	.include "asm/macros.inc"
	.include "global.inc"

	.text

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
