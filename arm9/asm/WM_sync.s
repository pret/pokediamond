	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global UNK_02106A54
UNK_02106A54: ; 0x02106A54
	.word 0x00010000

	.text

	arm_func_start WM_GetNextTgid
WM_GetNextTgid: ; 0x020D8868
	stmdb sp!, {lr}
	sub sp, sp, #0xc

	arm_func_start sub_020D8870
sub_020D8870: ; 0x020D8870
	ldr r0, _020D88DC ; =UNK_02106A54
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
	ldr r1, _020D88DC ; =UNK_02106A54
	add r0, r2, r0, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r1, #0x0]
_020D88B0:
	ldr r1, _020D88DC ; =UNK_02106A54
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
_020D88DC: .word UNK_02106A54

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
