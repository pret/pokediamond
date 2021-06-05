	.include "asm/macros.inc"
	.include "global.inc"

	.text

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
