	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start WcmAppendApList
WcmAppendApList: ; 0x020A7FB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl WCMi_GetSystemWork
	add r1, r0, #0x2000
	cmp r4, #0x0
	ldr r0, [r1, #0x270]
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x274]
	cmp r1, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	beq _020A8040
_020A7FF8:
	cmp r3, r4
	bne _020A8034
	ldr r2, [r3, #0x8]
	cmp r2, #0x0
	ldrne r1, [r3, #0xc]
	strne r1, [r2, #0xc]
	ldreq r1, [r3, #0xc]
	streq r1, [r0, #0x4]
	ldr r2, [r3, #0xc]
	cmp r2, #0x0
	ldrne r1, [r3, #0x8]
	strne r1, [r2, #0x8]
	ldreq r1, [r3, #0x8]
	streq r1, [r0, #0x8]
	b _020A8040
_020A8034:
	ldr r3, [r3, #0xc]
	cmp r3, #0x0
	bne _020A7FF8
_020A8040:
	mov r1, #0x0
	str r1, [r4, #0xc]
	ldr r1, [r0, #0x8]
	str r1, [r4, #0x8]
	str r4, [r0, #0x8]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	strne r4, [r1, #0xc]
	streq r4, [r0, #0x4]
	cmp r3, #0x0
	ldreq r1, [r0, #0x0]
	streq r1, [r4, #0x4]
	ldreq r1, [r0, #0x0]
	addeq r1, r1, #0x1
	streq r1, [r0, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WcmSearchIndexedApList
WcmSearchIndexedApList: ; 0x020A8084
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl WCMi_GetSystemWork
	add r1, r0, #0x2000
	ldr r2, [r1, #0x270]
	mov r0, #0x0
	cmp r2, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x274]
	cmp r1, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020A80C8:
	ldr r1, [r0, #0x4]
	cmp r1, r4
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	bne _020A80C8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start WcmSearchApList
WcmSearchApList: ; 0x020A80EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl WCMi_GetSystemWork
	add r0, r0, #0x2000
	cmp r5, #0x0
	mov r4, #0x0
	ldr r1, [r0, #0x270]
	addeq sp, sp, #0x4
	moveq r0, r4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r1, #0x0
	beq _020A8160
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	bls _020A8160
	ldr r4, [r1, #0x4]
	cmp r4, #0x0
	beq _020A8160
_020A813C:
	add r0, r4, #0x10
	mov r1, r5
	add r0, r0, #0x4
	bl WCM_CompareBssID
	cmp r0, #0x0
	bne _020A8160
	ldr r4, [r4, #0xc]
	cmp r4, #0x0
	bne _020A813C
_020A8160:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WcmGetLastApList
WcmGetLastApList: ; 0x020A8170
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WCMi_GetSystemWork
	add r0, r0, #0x2000
	ldr r1, [r0, #0x270]
	cmp r1, #0x0
	beq _020A81A4
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	addhi sp, sp, #0x4
	ldrhi r0, [r1, #0x4]
	ldmhiia sp!, {lr}
	bxhi lr
_020A81A4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start WcmAllocApList
WcmAllocApList: ; 0x020A81B4
	stmdb sp!, {r4,lr}
	bl WCMi_GetSystemWork
	add r2, r0, #0x2000
	ldr r1, [r2, #0x270]
	mov r0, #0x0
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r3, [r2, #0x274]
	cmp r3, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r2, _020A8294 ; =0x4EC4EC4F
	sub r3, r3, #0xc
	umull r2, r4, r3, r2
	movs r4, r4, lsr #0x6
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r2, [r1, #0x0]
	cmp r4, r2
	ldmlsia sp!, {r4,lr}
	bxls lr
	mov lr, r0
	cmp r4, #0x0
	bls _020A8240
	add r12, r1, #0xc
	mov r2, #0xd0
_020A8220:
	mul r0, lr, r2
	ldrb r3, [r12, r0]
	add r0, r12, r0
	cmp r3, #0x0
	beq _020A8240
	add lr, lr, #0x1
	cmp lr, r4
	blo _020A8220
_020A8240:
	cmp lr, r4
	ldmcsia sp!, {r4,lr}
	bxcs lr
	mov r2, #0x1
	strb r2, [r0, #0x0]
	ldr r3, [r1, #0x0]
	mov r2, #0x0
	str r3, [r0, #0x4]
	str r2, [r0, #0xc]
	ldr r2, [r1, #0x8]
	str r2, [r0, #0x8]
	str r0, [r1, #0x8]
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	strne r0, [r2, #0xc]
	streq r0, [r1, #0x4]
	ldr r2, [r1, #0x0]
	add r2, r2, #0x1
	str r2, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A8294: .word 0x4EC4EC4F

	arm_func_start WCMi_EntryApList
WCMi_EntryApList: ; 0x020A8298
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl WCMi_GetSystemWork
	movs r7, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r7, #0x2000
	ldrb r0, [r0, #0x26a]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r0, [r5, #0x3c]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	add r0, r5, #0x4
	bl WcmSearchApList
	movs r6, r0
	bne _020A8300
	bl WcmAllocApList
	mov r6, r0
_020A8300:
	cmp r6, #0x0
	bne _020A8320
	add r0, r7, #0x2000
	ldr r0, [r0, #0x278]
	cmp r0, #0x1
	bne _020A8320
	bl WcmGetLastApList
	mov r6, r0
_020A8320:
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	add r1, r6, #0x10
	mov r2, #0xc0
	strh r4, [r6, #0x2]
	bl MIi_CpuCopyFast
	mov r0, r6
	bl WcmAppendApList
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start WCM_PointApList
WCM_PointApList: ; 0x020A8358
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_DisableInterrupts
	mov r5, r0
	bl WCMi_GetSystemWork
	cmp r0, #0x0
	bne _020A8390
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A8390:
	mov r0, r4
	bl WcmSearchIndexedApList
	movs r4, r0
	bne _020A83B8
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A83B8:
	mov r0, r5
	bl OS_RestoreInterrupts
	add r0, r4, #0x10
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WCM_LockApList
WCM_LockApList: ; 0x020A83D0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	bl WCMi_GetSystemWork
	cmp r0, #0x0
	bne _020A8408
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A8408:
	cmp r5, #0x0
	beq _020A8434
	add r1, r0, #0x2000
	ldrb r1, [r1, #0x26a]
	add r0, r0, #0x2000
	cmp r1, #0x0
	movne r5, #0x1
	mov r1, #0x1
	moveq r5, #0x0
	strb r1, [r0, #0x26a]
	b _020A8454
_020A8434:
	add r1, r0, #0x2000
	ldrb r1, [r1, #0x26a]
	add r0, r0, #0x2000
	cmp r1, #0x0
	movne r5, #0x1
	mov r1, #0x0
	moveq r5, #0x0
	strb r1, [r0, #0x26a]
_020A8454:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WCM_CountApList
WCM_CountApList: ; 0x020A846C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	bl WCMi_GetSystemWork
	cmp r0, #0x0
	mov r4, #0x0
	bne _020A84A4
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, r4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A84A4:
	add r0, r0, #0x2000
	ldr r1, [r0, #0x270]
	cmp r1, #0x0
	beq _020A84C0
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	ldrhi r4, [r1, #0x0]
_020A84C0:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start WCM_ClearApList
WCM_ClearApList: ; 0x020A84D8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	bl WCMi_GetSystemWork
	cmp r0, #0x0
	bne _020A8500
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
_020A8500:
	add r1, r0, #0x2000
	ldr r0, [r1, #0x270]
	cmp r0, #0x0
	beq _020A8524
	ldr r2, [r1, #0x274]
	cmp r2, #0x0
	ble _020A8524
	mov r1, #0x0
	bl MI_CpuFill8
_020A8524:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
