	.include "asm/macros.inc"
	.include "global.inc"

	.text

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
	bl MATH_CountPopulation
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
	bl MATH_CountPopulation
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
