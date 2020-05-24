	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021D6940
UNK_021D6940: ; 0x021D6940
	.space 0x4

	.global UNK_021D6944
UNK_021D6944: ; 0x021D6944
	.space 0x4

    .text

	arm_func_start CTRDG_CheckEnabled
CTRDG_CheckEnabled:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl CTRDG_IsOptionCartridge
_020DB128: ; 0x020DB128
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl CTRDG_IsEnabled
_020DB13C: ; 0x020DB13C
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDG_Enable
CTRDG_Enable: ; 0x020DB15C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020DB1AC ; =UNK_021D6940
	mov r4, r0
	str r5, [r1, #0x0]
	bl CTRDG_IsOptionCartridge
_020DB17C: ; 0x020DB17C
	cmp r0, #0x0
	bne _020DB198
	cmp r5, #0x0
	movne r1, #0x1000
	moveq r1, #0x5000
	mov r0, #0xf000
	bl OS_SetDPermissionsForProtectionRegion
_020DB198:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DB1AC: .word UNK_021D6940

	arm_func_start CTRDG_IsEnabled
CTRDG_IsEnabled:
	ldr r0, _020DB1BC ; =UNK_021D6940
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020DB1BC: .word UNK_021D6940

	arm_func_start CTRDGi_AccessCommon
CTRDGi_AccessCommon: ; 0x020DB1C0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl CTRDG_IsExisting
_020DB1DC: ; 0x020DB1DC
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl CTRDG_CheckEnabled
	ldr r0, _020DB2BC ; =UNK_021D6944
	ldrh r0, [r0, #0x2]
	bl OS_LockCartridge
	cmp r4, #0x21
	bhi _020DB240
	cmp r4, #0x21
	bhs _020DB270
	cmp r4, #0x11
	bhi _020DB234
	cmp r4, #0x10
	blo _020DB294
	cmp r4, #0x10
	beq _020DB290
	cmp r4, #0x11
	beq _020DB260
	b _020DB294
_020DB234:
	cmp r4, #0x20
	streqh r6, [r7, #0x0]
	b _020DB294
_020DB240:
	cmp r4, #0x40
	bhi _020DB254
	cmp r4, #0x40
	streq r6, [r7, #0x0]
	b _020DB294
_020DB254:
	cmp r4, #0x41
	beq _020DB280
	b _020DB294
_020DB260:
	cmp r5, #0x0
	ldrneb r0, [r7, #0x0]
	strneb r0, [r5, #0x0]
	b _020DB294
_020DB270:
	cmp r5, #0x0
	ldrneh r0, [r7, #0x0]
	strneh r0, [r5, #0x0]
	b _020DB294
_020DB280:
	cmp r5, #0x0
	ldrne r0, [r7, #0x0]
	strne r0, [r5, #0x0]
	b _020DB294
_020DB290:
	strb r6, [r7, #0x0]
_020DB294:
	ldr r0, _020DB2BC ; =UNK_021D6944
	ldrh r0, [r0, #0x2]
	bl OS_UnLockCartridge
	bl CTRDG_IsExisting
_020DB2A4: ; 0x020DB2A4
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DB2BC: .word UNK_021D6944

	arm_func_start CTRDG_Read32
CTRDG_Read32: ; 0x020DB2C0
	ldr ip, _020DB2D4 ; =CTRDGi_AccessCommon
	mov r2, r1
	mov r1, #0x0
	mov r3, #0x41
	bx r12
	.balign 4
_020DB2D4: .word CTRDGi_AccessCommon

	arm_func_start CTRDGi_CopyCommon
CTRDGi_CopyCommon: ; 0x020DB2D8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl CTRDG_IsExisting
_020DB2F4: ; 0x020DB2F4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl CTRDG_CheckEnabled
	ldr r0, _020DB42C ; =UNK_021D6944
	ldrh r0, [r0, #0x2]
	bl OS_LockCartridge
	ldr r0, [sp, #0x18]
	ands r0, r0, #0x1
	bne _020DB338
	mov r0, r7
	bl MI_StopDma
	mov r0, r5
	mov r1, r4
	bl DC_FlushRange
_020DB338:
	ldr r0, [sp, #0x18]
	cmp r0, #0x11
	bhi _020DB36C
	cmp r0, #0x10
	blo _020DB360
	cmp r0, #0x10
	beq _020DB38C
	cmp r0, #0x11
	beq _020DB3BC
	b _020DB404
_020DB360:
	cmp r0, #0x1
	beq _020DB3E4
	b _020DB404
_020DB36C:
	cmp r0, #0x20
	bhi _020DB380
	cmp r0, #0x20
	beq _020DB3A4
	b _020DB404
_020DB380:
	cmp r0, #0x21
	beq _020DB3D0
	b _020DB404
_020DB38C:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	bl MI_DmaCopy16
	b _020DB404
_020DB3A4:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	bl MI_DmaCopy32
	b _020DB404
_020DB3BC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MIi_CpuCopy16
	b _020DB404
_020DB3D0:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MIi_CpuCopy32
	b _020DB404
_020DB3E4:
	cmp r4, #0x0
	mov r1, #0x0
	bls _020DB404
_020DB3F0:
	ldrb r0, [r6], #0x1
	add r1, r1, #0x1
	cmp r1, r4
	strb r0, [r5], #0x1
	blo _020DB3F0
_020DB404:
	ldr r0, _020DB42C ; =UNK_021D6944
	ldrh r0, [r0, #0x2]
	bl OS_UnLockCartridge
	bl CTRDG_IsExisting
_020DB414: ; 0x020DB414
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DB42C: .word UNK_021D6944

	arm_func_start CTRDG_CpuCopy32
CTRDG_CpuCopy32: ; 0x020DB430
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	mov r12, #0x21
	mov r1, r0
	mov r2, lr
	mov r0, #0x0
	str r12, [sp, #0x0]
	bl CTRDGi_CopyCommon
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDG_CpuCopy16
CTRDG_CpuCopy16: ; 0x020DB464
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	mov r12, #0x11
	mov r1, r0
	mov r2, lr
	mov r0, #0x0
	str r12, [sp, #0x0]
	bl CTRDGi_CopyCommon
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDG_CpuCopy8
CTRDG_CpuCopy8: ; 0x020DB498
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	cmp lr, #0x8000000
	blo _020DB4DC
	ldr r2, _020DB500 ; =0x0A010000
	cmp lr, r2
	bhs _020DB4DC
	mov r12, #0x1
	mov r2, r0
	mov r0, #0x0
	str r12, [sp, #0x0]
	bl CTRDGi_CopyCommon
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020DB4DC:
	mov r12, #0x1
	mov r1, r0
	mov r2, lr
	mov r0, #0x0
	str r12, [sp, #0x0]
	bl CTRDGi_CopyCommon
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DB500: .word 0x0A010000

	arm_func_start CTRDGi_SendtoPxi
CTRDGi_SendtoPxi: ; 0x020DB504
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r1, r7
	mov r0, #0xd
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020DB520: ; 0x020DB520
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r6, #0x1
	mov r5, #0xd
	mov r4, #0x0
_020DB53C:
	mov r0, r6
	bl SVC_WaitByLoop
	mov r0, r5
	mov r1, r7
	mov r2, r4
	bl PXI_SendWordByFifo
_020DB554: ; 0x020DB554
	cmp r0, #0x0
	bne _020DB53C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CTRDGi_UnlockByProcessor
CTRDGi_UnlockByProcessor: ; 0x020DB568
	stmdb sp!, {r4,lr}
	mov r4, r1
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bne _020DB580
	bl OS_UnLockCartridge
_020DB580:
	ldr r0, [r4, #0x4]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start CTRDGi_LockByProcessor
CTRDGi_LockByProcessor: ; 0x020DB590
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	ldr r5, _020DB60C ; =0x027FFFE8
	mov r4, #0x1
_020DB5A8:
	bl OS_DisableInterrupts
	str r0, [r6, #0x4]
	mov r0, r5
	bl OS_ReadOwnerOfLockWord
	and r0, r0, #0x40
	str r0, [r6, #0x0]
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, r7
	bl OS_TryLockCartridge
_020DB5DC: ; 0x020DB5DC
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r6, #0x4]
	bl OS_RestoreInterrupts
	mov r0, r4
	bl SVC_WaitByLoop
	b _020DB5A8
_020DB600: ; 0x020DB600
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DB60C: .word 0x027FFFE8

	arm_func_start CTRDGi_RestoreAccessCycle
CTRDGi_RestoreAccessCycle: ; 0x020DB610
	ldr r3, _020DB640 ; =0x04000204
	ldr r2, [r0, #0x0]
	ldrh r1, [r3, #0x0]
	bic r1, r1, #0xc
	orr r1, r1, r2, lsl #0x2
	strh r1, [r3, #0x0]
	ldrh r1, [r3, #0x0]
	ldr r2, [r0, #0x4]
	bic r0, r1, #0x10
	orr r0, r0, r2, lsl #0x4
	strh r0, [r3, #0x0]
	bx lr
	.balign 4
_020DB640: .word 0x04000204

	arm_func_start CTRDGi_ChangeLatestAccessCycle
CTRDGi_ChangeLatestAccessCycle: ; 0x020DB644
	ldr r2, _020DB688 ; =0x04000204
	ldrh r1, [r2, #0x0]
	and r1, r1, #0xc
	mov r1, r1, asr #0x2
	str r1, [r0, #0x0]
	ldrh r1, [r2, #0x0]
	and r1, r1, #0x10
	mov r1, r1, asr #0x4
	str r1, [r0, #0x4]
	ldrh r0, [r2, #0x0]
	bic r0, r0, #0xc
	orr r0, r0, #0xc
	strh r0, [r2, #0x0]
	ldrh r0, [r2, #0x0]
	bic r0, r0, #0x10
	strh r0, [r2, #0x0]
	bx lr
	.balign 4
_020DB688: .word 0x04000204

	arm_func_start CTRDG_IsExisting
CTRDG_IsExisting:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	ldr r2, _020DB798 ; =0x027FFC30
	ldr r0, _020DB79C ; =0x0000FFFF
	ldrh r1, [r2, #0x0]
	mov r4, #0x1
	cmp r1, r0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrb r0, [r2, #0x5]
	mov r0, r0, lsl #0x1e
	mov r0, r0, lsr #0x1f
	cmp r0, #0x1
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020DB7A0 ; =UNK_021D6944
	add r1, sp, #0x0
	ldrh r0, [r0, #0x2]
	bl CTRDGi_LockByProcessor
	add r0, sp, #0x8
	bl CTRDGi_ChangeLatestAccessCycle
	mov r0, #0x8000000
	ldrb r2, [r0, #0xb2]
	cmp r2, #0x96
	bne _020DB714
	ldr r1, _020DB798 ; =0x027FFC30
	ldrh r0, [r0, #0xbe]
	ldrh r1, [r1, #0x0]
	cmp r1, r0
	bne _020DB75C
_020DB714:
	cmp r2, #0x96
	beq _020DB734
	ldr r1, _020DB798 ; =0x027FFC30
	ldr r0, _020DB7A4 ; =0x0801FFFE
	ldrh r1, [r1, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r1, r0
	bne _020DB75C
_020DB734:
	ldr r2, _020DB798 ; =0x027FFC30
	mov r0, #0x8000000
	ldr r1, [r2, #0x8]
	ldr r0, [r0, #0xac]
	cmp r1, r0
	beq _020DB770
	ldrb r0, [r2, #0x5]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	beq _020DB770
_020DB75C:
	ldr r1, _020DB798 ; =0x027FFC30
	mov r4, #0x0
	ldrb r0, [r1, #0x5]
	orr r0, r0, #0x2
	strb r0, [r1, #0x5]
_020DB770:
	add r0, sp, #0x8
	bl CTRDGi_RestoreAccessCycle
	ldr r0, _020DB7A0 ; =UNK_021D6944
	add r1, sp, #0x0
	ldrh r0, [r0, #0x2]
	bl CTRDGi_UnlockByProcessor
	mov r0, r4
	add sp, sp, #0x10
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020DB798: .word 0x027FFC30
_020DB79C: .word 0x0000FFFF
_020DB7A0: .word UNK_021D6944
_020DB7A4: .word 0x0801FFFE

	arm_func_start CTRDG_IsPulledOut
CTRDG_IsPulledOut: ; 0x020DB7A8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020DB800 ; =0x027FFC30
	ldr r0, _020DB804 ; =0x0000FFFF
	ldrh r1, [r2, #0x0]
	cmp r1, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r0, [r2, #0x5]
	mov r0, r0, lsl #0x1e
	movs r0, r0, lsr #0x1f
	bne _020DB7E4
	bl CTRDG_IsExisting
_020DB7E4:
	ldr r0, _020DB800 ; =0x027FFC30
	ldrb r0, [r0, #0x5]
	mov r0, r0, lsl #0x1e
	mov r0, r0, lsr #0x1f
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DB800: .word 0x027FFC30
_020DB804: .word 0x0000FFFF

	arm_func_start CTRDGi_GetAgbMakerCodeAtInit
CTRDGi_GetAgbMakerCodeAtInit: ; 0x020DB808
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	bl CTRDGi_IsAgbCartridgeAtInit
_020DB814: ; 0x020DB814
	cmp r0, #0x0
	ldrne r0, _020DB82C ; =0x027FFC30
	ldrneh r4, [r0, #0x6]
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020DB82C: .word 0x027FFC30

	arm_func_start CTRDG_GetAgbMakerCode
CTRDG_GetAgbMakerCode: ; 0x020DB830
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	bl CTRDG_IsExisting
_020DB83C: ; 0x020DB83C
	cmp r0, #0x0
	beq _020DB84C
	bl CTRDGi_GetAgbMakerCodeAtInit
	mov r4, r0
_020DB84C:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start CTRDGi_GetAgbGameCodeAtInit
CTRDGi_GetAgbGameCodeAtInit: ; 0x020DB858
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	bl CTRDGi_IsAgbCartridgeAtInit
_020DB864: ; 0x020DB864
	cmp r0, #0x0
	ldrne r0, _020DB87C ; =0x027FFC30
	ldrne r4, [r0, #0x8]
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020DB87C: .word 0x027FFC30

	arm_func_start CTRDG_GetAgbGameCode
CTRDG_GetAgbGameCode: ; 0x020DB880
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	bl CTRDG_IsExisting
_020DB88C: ; 0x020DB88C
	cmp r0, #0x0
	beq _020DB89C
	bl CTRDGi_GetAgbGameCodeAtInit
	mov r4, r0
_020DB89C:
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start CTRDGi_IsAgbCartridgeAtInit
CTRDGi_IsAgbCartridgeAtInit:
	ldr r0, _020DB8BC ; =0x027FFC30
	ldrb r0, [r0, #0x5]
	mov r0, r0, lsl #0x1f
	mov r0, r0, lsr #0x1f
	bx lr
	.balign 4
_020DB8BC: .word 0x027FFC30

	arm_func_start CTRDG_IsOptionCartridge
CTRDG_IsOptionCartridge:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl CTRDG_IsExisting
_020DB8CC: ; 0x020DB8CC
	cmp r0, #0x0
	beq _020DB8EC
	bl CTRDGi_IsAgbCartridgeAtInit
_020DB8D8: ; 0x020DB8D8
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {lr}
	bxeq lr
_020DB8EC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDG_IsAgbCartridge
CTRDG_IsAgbCartridge: ; 0x020DB8FC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl CTRDG_IsExisting
_020DB908: ; 0x020DB908
	cmp r0, #0x0
	beq _020DB928
	bl CTRDGi_IsAgbCartridgeAtInit
_020DB914: ; 0x020DB914
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {lr}
	bxne lr
_020DB928:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_InitCommon
CTRDGi_InitCommon: ; 0x020DB938
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020DB970 ; =UNK_021D6944
	mov r3, #0x0
	ldr r2, _020DB974 ; =0x05000001
	add r0, sp, #0x0
	str r3, [sp, #0x0]
	bl FUN_020002FE
	bl OS_GetLockID
	ldr r1, _020DB970 ; =UNK_021D6944
	strh r0, [r1, #0x2]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DB970: .word UNK_021D6944
_020DB974: .word 0x05000001
