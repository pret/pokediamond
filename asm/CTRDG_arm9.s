	.include "asm/macros.inc"
	.include "global.inc"

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
	ldr r1, _020DB1AC ; =0x021D6940
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
_020DB1AC: .word 0x021D6940

	arm_func_start CTRDG_IsEnabled
CTRDG_IsEnabled:
	ldr r0, _020DB1BC ; =0x021D6940
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020DB1BC: .word 0x021D6940

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
	ldr r0, _020DB2BC ; =0x021D6944
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
	ldr r0, _020DB2BC ; =0x021D6944
	ldrh r0, [r0, #0x2]
	bl OS_UnlockCartridge
	bl CTRDG_IsExisting
_020DB2A4: ; 0x020DB2A4
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DB2BC: .word 0x021D6944

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
	ldr r0, _020DB42C ; =0x021D6944
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
	ldr r0, _020DB42C ; =0x021D6944
	ldrh r0, [r0, #0x2]
	bl OS_UnlockCartridge
	bl CTRDG_IsExisting
_020DB414: ; 0x020DB414
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DB42C: .word 0x021D6944

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
	blx SVC_WaitByLoop
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
	bl OS_UnlockCartridge
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
	blx SVC_WaitByLoop
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
	ldr r0, _020DB7A0 ; =0x021D6944
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
	ldr r0, _020DB7A0 ; =0x021D6944
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
_020DB7A0: .word 0x021D6944
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
	ldr r1, _020DB970 ; =0x021D6944
	mov r3, #0x0
	ldr r2, _020DB974 ; =0x05000001
	add r0, sp, #0x0
	str r3, [sp, #0x0]
	blx FUN_020002FE
	bl OS_GetLockID
	ldr r1, _020DB970 ; =0x021D6944
	strh r0, [r1, #0x2]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DB970: .word 0x021D6944
_020DB974: .word 0x05000001

	arm_func_start CTRDGi_CallbackForSetPhi
CTRDGi_CallbackForSetPhi: ; 0x020DB978
	ldr r0, _020DB988 ; =0x021D694C
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020DB988: .word 0x021D694C

	arm_func_start CTRDG_TerminateForPulledOut
CTRDG_TerminateForPulledOut: ; 0x020DB98C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x2
	bl CTRDGi_SendtoPxi
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_PulledOutCallback
CTRDGi_PulledOutCallback: ; 0x020DB9AC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x3f
	cmp r0, #0x11
	bne _020DBA14
	ldr r0, _020DBA24 ; =0x021D6954
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, _020DBA28 ; =0x021D6958
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020DB9F0
	blx r1
_020DB9F0:
	cmp r0, #0x0
	beq _020DB9FC
	bl CTRDG_TerminateForPulledOut
_020DB9FC:
	ldr r0, _020DBA24 ; =0x021D6954
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020DBA14:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBA24: .word 0x021D6954
_020DBA28: .word 0x021D6958

	arm_func_start CTRDGi_CallbackForInitModuleInfo
CTRDGi_CallbackForInitModuleInfo: ; 0x020DBA2C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x3f
	cmp r0, #0x1
	ldreq r0, _020DBA64 ; =0x021D6944
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
_020DBA64: .word 0x021D6944

	arm_func_start CTRDGi_InitModuleInfo
CTRDGi_InitModuleInfo: ; 0x020DBA68
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	ldr r0, _020DBC50 ; =0x021D6948
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x14
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, _020DBC54 ; =0x04000300
	mov r2, #0x1
	str r2, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	ands r0, r0, #0x1
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, #0x40000
	bl OS_SetIrqMask
	ldr r3, _020DBC58 ; =0x04000208
	mov r2, #0x1
	ldrh r4, [r3, #0x0]
	ldr r1, _020DBC5C ; =0x021D6944
	mov r6, r0
	strh r2, [r3, #0x0]
	ldrh r0, [r1, #0x2]
	add r1, sp, #0x0
	bl CTRDGi_LockByProcessor
	ldr r1, _020DBC60 ; =0x04000204
	add r0, sp, #0x8
	ldrh r1, [r1, #0x0]
	and r1, r1, #0x8000
	mov r5, r1, asr #0xf
	bl CTRDGi_ChangeLatestAccessCycle
	ldr r3, _020DBC60 ; =0x04000204
	ldr r0, _020DBC64 ; =0x021D6960
	ldrh r2, [r3, #0x0]
	add r0, r0, #0x80
	mov r1, #0x40
	bic r2, r2, #0x8000
	strh r2, [r3, #0x0]
	bl DC_InvalidateRange
	ldr r2, _020DBC64 ; =0x021D6960
	ldr r1, _020DBC68 ; =0x08000080
	mov r0, #0x1
	mov r3, #0x40
	add r2, r2, #0x80
	bl MI_DmaCopy16
	ldr r2, _020DBC60 ; =0x04000204
	add r0, sp, #0x8
	ldrh r1, [r2, #0x0]
	bic r1, r1, #0x8000
	orr r1, r1, r5, lsl #0xf
	strh r1, [r2, #0x0]
	bl CTRDGi_RestoreAccessCycle
	ldr r0, _020DBC5C ; =0x021D6944
	add r1, sp, #0x0
	ldrh r0, [r0, #0x2]
	bl CTRDGi_UnlockByProcessor
	ldr r0, _020DBC6C ; =0x027FFF9B
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020DBB70
	ldr r0, _020DBC70 ; =0x027FFF9A
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020DBBDC
_020DBB70:
	ldr r2, _020DBC64 ; =0x021D6960
	ldr r0, _020DBC74 ; =0x027FFC30
	ldrh r1, [r2, #0xbe]
	mov r3, #0x0
	strh r1, [r0, #0x0]
_020DBB84:
	add r0, r2, r3
	ldrb r1, [r0, #0xb5]
	add r0, r3, #0x2700000
	add r0, r0, #0xff000
	add r3, r3, #0x1
	strb r1, [r0, #0xC32]
	cmp r3, #0x3
	blt _020DBB84
	ldrh r0, [r2, #0xb0]
	ldr r1, _020DBC74 ; =0x027FFC30
	strh r0, [r1, #0x6]
	ldr r0, [r2, #0xac]
	str r0, [r1, #0x8]
	bl CTRDG_IsExisting
_020DBBBC: ; 0x020DBBBC
	cmp r0, #0x0
	movne r2, #0x1
	ldr r1, _020DBC6C ; =0x027FFF9B
	moveq r2, #0x0
	strb r2, [r1, #0x0]
	ldr r0, _020DBC70 ; =0x027FFF9A
	mov r1, #0x1
	strb r1, [r0, #0x0]
_020DBBDC:
	ldr r0, _020DBC78 ; =0xFFFF0020
	ldr r1, _020DBC7C ; =0x021D6964
	mov r2, #0x9c
	bl MIi_CpuCopy32
	bl DC_FlushAll
	ldr r0, _020DBC64 ; =0x021D6960
	add r0, r0, #0xfe000000
	mov r0, r0, lsr #0x5
	mov r0, r0, lsl #0x6
	orr r0, r0, #0x1
	bl CTRDGi_SendtoPxi
	ldr r5, _020DBC5C ; =0x021D6944
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	beq _020DBC30
	mov r7, #0x1
_020DBC1C:
	mov r0, r7
	blx SVC_WaitByLoop
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _020DBC1C
_020DBC30:
	ldr r2, _020DBC58 ; =0x04000208
	mov r0, r6
	ldrh r1, [r2, #0x0]
	strh r4, [r2, #0x0]
	bl OS_SetIrqMask
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DBC50: .word 0x021D6948
_020DBC54: .word 0x04000300
_020DBC58: .word 0x04000208
_020DBC5C: .word 0x021D6944
_020DBC60: .word 0x04000204
_020DBC64: .word 0x021D6960
_020DBC68: .word 0x08000080
_020DBC6C: .word 0x027FFF9B
_020DBC70: .word 0x027FFF9A
_020DBC74: .word 0x027FFC30
_020DBC78: .word 0xFFFF0020
_020DBC7C: .word 0x021D6964

	arm_func_start CTRDG_Init
CTRDG_Init: ; 0x020DBC80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DBD34 ; =0x021D6950
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl CTRDGi_InitCommon
	ldr r0, _020DBD38 ; =0x021D6954
	mov r1, #0x0
	str r1, [r0, #0x0]
	bl PXI_Init
	mov r5, #0xd
	mov r4, #0x1
_020DBCC4:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020DBCD0: ; 0x020DBCD0
	cmp r0, #0x0
	beq _020DBCC4
	ldr r1, _020DBD3C ; =CTRDGi_CallbackForInitModuleInfo
	mov r0, #0xd
	bl PXI_SetFifoRecvCallback
	bl CTRDGi_InitModuleInfo
	mov r0, #0xd
	mov r1, #0x0
	bl PXI_SetFifoRecvCallback
	ldr r1, _020DBD40 ; =CTRDGi_PulledOutCallback
	mov r0, #0xd
	bl PXI_SetFifoRecvCallback
	ldr r1, _020DBD44 ; =0x021D6958
	mov r2, #0x0
	ldr r0, _020DBD48 ; =0x021D6A20
	str r2, [r1, #0x0]
	bl CTRDGi_InitTaskThread
	ldr r1, _020DBD4C ; =CTRDGi_CallbackForSetPhi
	mov r0, #0x11
	bl PXI_SetFifoRecvCallback
_020DBD20: ; 0x020DBD20
	mov r0, #0x0
	bl CTRDG_Enable
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DBD34: .word 0x021D6950
_020DBD38: .word 0x021D6954
_020DBD3C: .word CTRDGi_CallbackForInitModuleInfo
_020DBD40: .word CTRDGi_PulledOutCallback
_020DBD44: .word 0x021D6958
_020DBD48: .word 0x021D6A20
_020DBD4C: .word CTRDGi_CallbackForSetPhi

	arm_func_start CTRDG_IdentifyAgbBackup
CTRDG_IdentifyAgbBackup: ; 0x020DBD50
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	cmp r7, #0x1
	mov r0, #0x1
	bhi _020DBEAC
	bl OS_GetLockID
	ldr r1, _020DBED8 ; =0x021D6B0C
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_LockCartridge
	ldr r6, _020DBEDC ; =0x04000204
	ldr r1, _020DBEE0 ; =0x02103FE4
	ldrh r3, [r6, #0x0]
	ldrh r2, [r6, #0x0]
	ldr r0, _020DBEE4 ; =0x021D6B28
	and r4, r3, #0x3
	bic r2, r2, #0x3
	orr r2, r2, #0x3
	strh r2, [r6, #0x0]
	str r1, [r0, #0x0]
	bl CTRDGi_ReadFlashID
	ldr r2, _020DBEDC ; =0x04000204
	mov r6, r0
	ldrh r1, [r2, #0x0]
	cmp r7, #0x0
	ldreq r5, _020DBEE8 ; =0x02103FF4
	bic r1, r1, #0x3
	orr r1, r1, r4
	cmp r7, #0x1
	ldr r0, _020DBED8 ; =0x021D6B0C
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	ldreq r5, _020DBEEC ; =0x02103FE8
	bl OS_UnlockCartridge2
	ldr r2, [r5, #0x0]
	mov r0, #0x1
	ldrh r1, [r2, #0x38]
	cmp r1, #0x0
	beq _020DBE14
	and r3, r6, #0xff
_020DBDF4:
	ldrh r1, [r2, #0x38]
	cmp r3, r1
	moveq r0, #0x0
	beq _020DBE14
	ldr r2, [r5, #0x4]!
	ldrh r1, [r2, #0x38]
	cmp r1, #0x0
	bne _020DBDF4
_020DBE14:
	ldr r2, [r2, #0x0]
	ldr r1, _020DBEF0 ; =0x021D6B14
	ldr r3, _020DBEF4 ; =0x021D6B34
	str r2, [r1, #0x0]
	ldr r1, [r5, #0x0]
	ldr r2, _020DBEF8 ; =0x021D6B2C
	ldr r4, [r1, #0x4]
	ldr r1, _020DBEFC ; =0x021D6B18
	str r4, [r3, #0x0]
	ldr r3, [r5, #0x0]
	ldr r6, _020DBF00 ; =0x021D6B1C
	ldr r3, [r3, #0x8]
	ldr r4, _020DBF04 ; =0x021D6B30
	str r3, [r2, #0x0]
	ldr r2, [r5, #0x0]
	ldr r3, _020DBF08 ; =0x021D6B24
	ldr r7, [r2, #0xc]
	ldr r2, _020DBEE4 ; =0x021D6B28
	str r7, [r1, #0x0]
	ldr r7, [r5, #0x0]
	ldr r1, _020DBF0C ; =0x021D6B20
	ldr r7, [r7, #0x10]
	add sp, sp, #0x4
	str r7, [r6, #0x0]
	ldr r6, [r5, #0x0]
	ldr r6, [r6, #0x14]
	str r6, [r4, #0x0]
	ldr r4, [r5, #0x0]
	ldr r4, [r4, #0x18]
	str r4, [r3, #0x0]
	ldr r3, [r5, #0x0]
	ldr r3, [r3, #0x1c]
	str r3, [r2, #0x0]
	ldr r2, [r5, #0x0]
	add r2, r2, #0x20
	str r2, [r1, #0x0]
	ldmia sp!, {r4-r7,lr}
	bx lr
_020DBEAC:
	cmp r7, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	bl OS_GetLockID
	ldr r1, _020DBF10 ; =0x021D6B4C
	strh r0, [r1, #0x0]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DBED8: .word 0x021D6B0C
_020DBEDC: .word 0x04000204
_020DBEE0: .word 0x02103FE4
_020DBEE4: .word 0x021D6B28
_020DBEE8: .word 0x02103FF4
_020DBEEC: .word 0x02103FE8
_020DBEF0: .word 0x021D6B14
_020DBEF4: .word 0x021D6B34
_020DBEF8: .word 0x021D6B2C
_020DBEFC: .word 0x021D6B18
_020DBF00: .word 0x021D6B1C
_020DBF04: .word 0x021D6B30
_020DBF08: .word 0x021D6B24
_020DBF0C: .word 0x021D6B20
_020DBF10: .word 0x021D6B4C

	arm_func_start CTRDG_WriteAndVerifyAgbFlashAsync
CTRDG_WriteAndVerifyAgbFlashAsync: ; 0x020DBF14
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	str r2, [sp, #0x18]
	ldr r1, _020DBF44 ; =CTRDGi_WriteAndVerifyAgbFlashSectorCore
	add r0, sp, #0x0
	mov r2, r3
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBF44: .word CTRDGi_WriteAndVerifyAgbFlashSectorCore

	arm_func_start CTRDG_VerifyAgbFlash
CTRDG_VerifyAgbFlash:
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	str r2, [sp, #0x18]
	bl CTRDGi_VerifyAgbFlashCore
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDG_WriteAgbFlashSector
CTRDG_WriteAgbFlashSector:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020DBF90 ; =0x021D6B14
	ldr r2, [r2, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBF90: .word 0x021D6B14

	arm_func_start CTRDG_ReadAgbFlash
CTRDG_ReadAgbFlash: ; 0x020DBF94
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0x14]
	str r2, [sp, #0x1c]
	str r3, [sp, #0x18]
	bl CTRDGi_ReadAgbFlashCore
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteAndVerifyAgbFlashSectorCore
CTRDGi_WriteAndVerifyAgbFlashSectorCore: ; 0x020DBFC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r4, r0
	ldmia r4!, {r0-r3}
	add r12, sp, #0x0
	stmia r12!, {r0-r3}
	ldmia r4!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r0, [r4, #0x0]
	mov r7, #0x0
	str r0, [r12, #0x0]
	ldrh r6, [sp, #0x20]
	ldr r5, [sp, #0xc]
	ldr r4, [sp, #0x18]
_020DBFF8:
	mov r0, r6
	mov r1, r5
	bl CTRDG_WriteAgbFlashSector
_020DC004: ; 0x020DC004
	cmp r0, #0x0
	bne _020DC02C
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl CTRDG_VerifyAgbFlash
_020DC01C: ; 0x020DC01C
	cmp r0, #0x0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_020DC02C:
	add r1, r7, #0x1
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	cmp r7, #0x3
	blo _020DBFF8
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CTRDGi_VerifyAgbFlashCore
CTRDGi_VerifyAgbFlashCore: ; 0x020DC04C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DC128 ; =0x021D6B0C
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r6, [sp, #0x20]
	ldr r5, [sp, #0xc]
	ldr r4, [sp, #0x18]
	bl OS_LockCartridge
	ldr r3, _020DC12C ; =0x04000204
	ldr r0, _020DC130 ; =0x021D6B20
	ldrh r2, [r3, #0x0]
	ldrh r1, [r3, #0x0]
	and r7, r2, #0x3
	bic r1, r1, #0x3
	orr r1, r1, #0x3
	strh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x20000
	bne _020DC0D4
	mov r0, r6, lsl #0xc
	mov r0, r0, lsr #0x10
	bl CTRDGi_SetFlashBankMx
	and r0, r6, #0xf
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
_020DC0D4:
	ldr r1, _020DC130 ; =0x021D6B20
	mov r0, r5
	ldr r1, [r1, #0x0]
	mov r2, r4
	ldrh r1, [r1, #0x8]
	mov r1, r6, lsl r1
	add r1, r1, #0xa000000
	bl CTRDGi_VerifyFlashSectorCore
	ldr r3, _020DC12C ; =0x04000204
	ldr r1, _020DC128 ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r7
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DC128: .word 0x021D6B0C
_020DC12C: .word 0x04000204
_020DC130: .word 0x021D6B20

	arm_func_start CTRDGi_VerifyFlashSectorCore
CTRDGi_VerifyFlashSectorCore: ; 0x020DC134
	cmp r2, #0x0
	sub r2, r2, #0x1
	beq _020DC160
_020DC140:
	ldrb r12, [r1], #0x1
	ldrb r3, [r0], #0x1
	cmp r12, r3
	subne r0, r1, #0x1
	bxne lr
	cmp r2, #0x0
	sub r2, r2, #0x1
	bne _020DC140
_020DC160:
	mov r0, #0x0
	bx lr

	arm_func_start CTRDGi_ReadAgbFlashCore
CTRDGi_ReadAgbFlashCore: ; 0x020DC168
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DC25C ; =0x021D6B0C
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r7, [sp, #0x20]
	ldr r6, [sp, #0x14]
	ldr r5, [sp, #0x1c]
	ldr r4, [sp, #0x18]
	bl OS_LockCartridge
	ldr r3, _020DC260 ; =0x04000204
	ldr r0, _020DC264 ; =0x021D6B20
	ldrh r2, [r3, #0x0]
	ldrh r1, [r3, #0x0]
	and r8, r2, #0x3
	bic r1, r1, #0x3
	orr r1, r1, #0x3
	strh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x20000
	bne _020DC1F4
	mov r0, r7, lsl #0xc
	mov r0, r0, lsr #0x10
	bl CTRDGi_SetFlashBankMx
	and r0, r7, #0xf
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
_020DC1F4:
	ldr r0, _020DC264 ; =0x021D6B20
	cmp r4, #0x0
	ldr r0, [r0, #0x0]
	sub r4, r4, #0x1
	ldrh r0, [r0, #0x8]
	mov r0, r7, lsl r0
	add r0, r0, #0xa000000
	add r1, r6, r0
	beq _020DC22C
_020DC218:
	ldrb r0, [r1], #0x1
	cmp r4, #0x0
	sub r4, r4, #0x1
	strb r0, [r5], #0x1
	bne _020DC218
_020DC22C:
	ldr r2, _020DC260 ; =0x04000204
	ldr r0, _020DC25C ; =0x021D6B0C
	ldrh r1, [r2, #0x0]
	bic r1, r1, #0x3
	orr r1, r1, r8
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, #0x0
	add sp, sp, #0x28
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DC25C: .word 0x021D6B0C
_020DC260: .word 0x04000204
_020DC264: .word 0x021D6B20

	arm_func_start CTRDGi_PollingSR1MCOMMON
CTRDGi_PollingSR1MCOMMON: ; 0x020DC268
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x0
	bl StartFlashTimer
	ldr r4, _020DC318 ; =0x021D6B10
_020DC284:
	bl CheckFlashTimer
	mov r0, r7
	bl CTRDGi_ReadSrFunc
	cmp r0, r6
	beq _020DC300
	ands r0, r0, #0x20
	beq _020DC2CC
	mov r0, r7
	bl CTRDGi_ReadSrFunc
_020DC2A8: ; 0x020DC2A8
	cmp r6, r0
	beq _020DC300
	orr r0, r8, #0xa000
	mov r0, r0, lsl #0x10
	ldr r1, _020DC31C ; =0x0A005555
	mov r2, #0xf0
	strb r2, [r1, #0x0]
	mov r5, r0, lsr #0x10
	b _020DC300
_020DC2CC:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC284
	mov r0, r7
	bl CTRDGi_ReadSrFunc
_020DC2E0: ; 0x020DC2E0
	cmp r6, r0
	beq _020DC300
	orr r0, r8, #0xc000
	mov r0, r0, lsl #0x10
	ldr r1, _020DC31C ; =0x0A005555
	mov r2, #0xf0
	strb r2, [r1, #0x0]
	mov r5, r0, lsr #0x10
_020DC300:
	bl CTRDG_IsExisting
_020DC304: ; 0x020DC304
	cmp r0, #0x0
	moveq r5, #0x1000
	mov r0, r5
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DC318: .word 0x021D6B10
_020DC31C: .word 0x0A005555

	arm_func_start CTRDGi_PollingSR512kCOMMON
CTRDGi_PollingSR512kCOMMON: ; 0x020DC320
	stmdb sp!, {r4-r8,lr}
	mov r4, r0
	mov r8, r1
	mov r7, r2
	mov r6, #0x0
	bl StartFlashTimer
	ldr r5, _020DC3A8 ; =0x021D6B10
_020DC33C:
	mov r0, r8
	bl CTRDGi_ReadSrFunc
	cmp r0, r7
	beq _020DC390
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020DC33C
	mov r0, r8
	bl CTRDGi_ReadSrFunc
_020DC360: ; 0x020DC360
	cmp r7, r0
	beq _020DC390
	ldr r0, _020DC3AC ; =0x021D6B20
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x18]
	cmp r0, #0xc2
	ldreq r0, _020DC3B0 ; =0x0A005555
	moveq r1, #0xf0
	streqb r1, [r0, #0x0]
	orr r0, r4, #0xc000
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
_020DC390:
	bl CTRDG_IsExisting
_020DC394: ; 0x020DC394
	cmp r0, #0x0
	moveq r6, #0x1000
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DC3A8: .word 0x021D6B10
_020DC3AC: .word 0x021D6B20
_020DC3B0: .word 0x0A005555

	arm_func_start CTRDGi_ReadSrFunc
CTRDGi_ReadSrFunc:
	ldrb r0, [r0, #0x0]
	bx lr

	arm_func_start CheckFlashTimer
CheckFlashTimer: ; 0x020DC3BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_GetTick
	ldr r3, _020DC420 ; =0x021D6B44
	ldr r2, _020DC424 ; =0x000082EA
	ldr r12, [r3, #0x0]
	ldr r3, [r3, #0x4]
	subs r12, r0, r12
	sbc r0, r1, r3
	mov r1, r0, lsl #0x6
	orr r1, r1, r12, lsr #0x1a
	mov r0, r12, lsl #0x6
	mov r3, #0x0
	bl _ll_udiv
	ldr r2, _020DC428 ; =0x021D6B3C
	ldr r3, [r2, #0x4]
	ldr r2, [r2, #0x0]
	cmp r3, r1
	cmpeq r2, r0
	ldrls r0, _020DC42C ; =0x021D6B10
	movls r1, #0x1
	strlsh r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC420: .word 0x021D6B44
_020DC424: .word 0x000082EA
_020DC428: .word 0x021D6B3C
_020DC42C: .word 0x021D6B10

	arm_func_start StartFlashTimer
StartFlashTimer: ; 0x020DC430
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020DC47C ; =0x021D6B28
	ldr r2, _020DC480 ; =0x021D6B10
	mov r3, #0x0
	ldr r1, [r1, #0x0]
	strh r3, [r2, #0x0]
	mov r0, r0, lsl #0x1
	ldrh r1, [r1, r0]
	ldr r0, _020DC484 ; =0x021D6B3C
	str r1, [r0, #0x0]
	str r3, [r0, #0x4]
	bl OS_GetTick
	ldr r2, _020DC488 ; =0x021D6B44
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC47C: .word 0x021D6B28
_020DC480: .word 0x021D6B10
_020DC484: .word 0x021D6B3C
_020DC488: .word 0x021D6B44

	arm_func_start CTRDGi_ReadFlashID
CTRDGi_ReadFlashID: ; 0x020DC48C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020DC590 ; =0x04000208
	mov r0, #0x0
	ldrh r2, [r5, #0x0]
	ldr r1, _020DC594 ; =0x021D6B38
	ldr r4, _020DC598 ; =0x0A005555
	strh r0, [r5, #0x0]
	str r2, [r1, #0x0]
	mov r3, #0xaa
	ldr r2, _020DC59C ; =0x0A002AAA
	strb r3, [r4, #0x0]
	mov r3, #0x55
	strb r3, [r2, #0x0]
	mov r2, #0x90
	strb r2, [r4, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r1, [r1, #0x0]
	strh r1, [r5, #0x0]
	bl StartFlashTimer
	ldr r4, _020DC5A0 ; =0x021D6B10
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020DC4FC
_020DC4EC:
	bl CheckFlashTimer
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC4EC
_020DC4FC:
	ldr r0, _020DC5A4 ; =0x0A000001
	bl CTRDGi_ReadSrFunc
	mov r4, r0, lsl #0x18
	mov r0, #0xa000000
	bl CTRDGi_ReadSrFunc
	ldr ip, _020DC590 ; =0x04000208
	orr r4, r0, r4, lsr #0x10
	ldrh r2, [r12, #0x0]
	mov r0, #0x0
	ldr r1, _020DC594 ; =0x021D6B38
	strh r0, [r12, #0x0]
	ldr r5, _020DC598 ; =0x0A005555
	str r2, [r1, #0x0]
	mov r3, #0xaa
	ldr r2, _020DC59C ; =0x0A002AAA
	strb r3, [r5, #0x0]
	mov r3, #0x55
	strb r3, [r2, #0x0]
	mov r2, #0xf0
	strb r2, [r5, #0x0]
	strb r2, [r5, #0x0]
	ldrh r2, [r12, #0x0]
	ldr r1, [r1, #0x0]
	strh r1, [r12, #0x0]
	bl StartFlashTimer
	ldr r5, _020DC5A0 ; =0x021D6B10
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020DC580
_020DC570:
	bl CheckFlashTimer
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020DC570
_020DC580:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DC590: .word 0x04000208
_020DC594: .word 0x021D6B38
_020DC598: .word 0x0A005555
_020DC59C: .word 0x0A002AAA
_020DC5A0: .word 0x021D6B10
_020DC5A4: .word 0x0A000001

	arm_func_start CTRDGi_SetFlashBankMx
CTRDGi_SetFlashBankMx: ; 0x020DC5A8
	ldr r3, _020DC5D4 ; =0x0A005555
	mov r2, #0xaa
	ldr r1, _020DC5D8 ; =0x0A002AAA
	strb r2, [r3, #0x0]
	mov r2, #0x55
	strb r2, [r1, #0x0]
	mov r1, #0xb0
	strb r1, [r3, #0x0]
	mov r1, #0xa000000
	strb r0, [r1, #0x0]
	bx lr
	.balign 4
_020DC5D4: .word 0x0A005555
_020DC5D8: .word 0x0A002AAA

	arm_func_start CTRDGi_WriteFlashSectorAsyncAT
CTRDGi_WriteFlashSectorAsyncAT: ; 0x020DC5DC
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DC604 ; =CTRDGi_WriteFlashSectorCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC604: .word CTRDGi_WriteFlashSectorCoreAT

	arm_func_start CTRDGi_EraseFlashSectorAsyncAT
CTRDGi_EraseFlashSectorAsyncAT: ; 0x020DC608
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DC630 ; =CTRDGi_EraseFlashSectorCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC630: .word CTRDGi_EraseFlashSectorCoreAT

	arm_func_start CTRDGi_WriteFlashSectorAT
CTRDGi_WriteFlashSectorAT: ; 0x020DC634
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashSectorAT
CTRDGi_EraseFlashSectorAT:
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashSectorCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlash4KBAsyncAT
CTRDGi_WriteFlash4KBAsyncAT: ; 0x020DC688
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DC6B0 ; =CTRDGi_WriteFlash4KBCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC6B0: .word CTRDGi_WriteFlash4KBCoreAT

	arm_func_start CTRDGi_EraseFlash4KBAsyncAT
CTRDGi_EraseFlash4KBAsyncAT: ; 0x020DC6B4
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DC6DC ; =CTRDGi_EraseFlash4KBCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC6DC: .word CTRDGi_EraseFlash4KBCoreAT

	arm_func_start CTRDGi_EraseFlashChipAsyncAT
CTRDGi_EraseFlashChipAsyncAT: ; 0x020DC6E0
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	ldr r1, _020DC704 ; =CTRDGi_EraseFlashChipCoreAT
	mov r2, r0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC704: .word CTRDGi_EraseFlashChipCoreAT

	arm_func_start CTRDGi_WriteFlash4KBAT
CTRDGi_WriteFlash4KBAT: ; 0x020DC708
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlash4KBCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlash4KBAT
CTRDGi_EraseFlash4KBAT: ; 0x020DC734
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlash4KBCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashChipAT
CTRDGi_EraseFlashChipAT: ; 0x020DC75C
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashChipCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlash4KBCoreAT
CTRDGi_WriteFlash4KBCoreAT: ; 0x020DC780
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r0, [sp, #0x20]
	ldr r7, [sp, #0xc]
	cmp r0, #0x10
	addcs sp, sp, #0x24
	ldrhs r0, _020DC85C ; =0x000080FF
	ldmcsia sp!, {r4-r9,lr}
	bxcs lr
	ldr r1, _020DC860 ; =0x0210400C
	mov r0, r0, lsl #0x15
	ldr r1, [r1, #0x24]
	ldr r4, _020DC864 ; =0x021D6B08
	mov r8, r0, lsr #0x10
	strh r1, [r4, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC84C
	ldr r0, _020DC868 ; =0x02104048
	ldr r6, [r0, #0x24]
	mov r5, #0x2
_020DC7F4:
	mov r9, r5
_020DC7F8:
	mov r0, r8
	mov r1, r7
	bl CTRDGi_WriteFlashSectorAT
	movs r12, r0
	beq _020DC81C
	sub r0, r9, #0x1
	mov r0, r0, lsl #0x10
	movs r9, r0, lsr #0x10
	bne _020DC7F8
_020DC81C:
	cmp r12, #0x0
	bne _020DC84C
	ldrh r1, [r4, #0x0]
	add r0, r8, #0x1
	mov r0, r0, lsl #0x10
	sub r1, r1, r6
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	add r7, r7, r6
	mov r8, r0, lsr #0x10
	cmp r1, #0x0
	bne _020DC7F4
_020DC84C:
	mov r0, r12
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020DC85C: .word 0x000080FF
_020DC860: .word 0x0210400C
_020DC864: .word 0x021D6B08
_020DC868: .word 0x02104048

	arm_func_start CTRDGi_WriteFlashSectorCoreAT
CTRDGi_WriteFlashSectorCoreAT: ; 0x020DC86C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x24
	mov r5, r0
	add r4, sp, #0x0
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DC984 ; =0x021D6B0C
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldr r4, [sp, #0xc]
	bl OS_LockCartridge
	ldr r5, _020DC988 ; =0x04000204
	ldr r1, _020DC98C ; =0x021D6B20
	ldrh r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r3, [r1, #0x10]
	ldr r1, _020DC990 ; =0x02104048
	bic r2, r2, #0x3
	orr r2, r2, r3
	strh r2, [r5, #0x0]
	ldr r5, _020DC994 ; =0x04000208
	ldrh lr, [sp, #0x20]
	ldrh r12, [r1, #0x28]
	ldrh r2, [r5, #0x0]
	mov r3, #0x0
	mov lr, lr, lsl r12
	strh r3, [r5, #0x0]
	ldr ip, _020DC998 ; =0x0A005555
	mov r5, #0xaa
	strb r5, [r12, #0x0]
	ldr r3, _020DC99C ; =0x0A002AAA
	mov r5, #0x55
	strb r5, [r3, #0x0]
	mov r3, #0xa0
	strb r3, [r12, #0x0]
	ldr r3, [r1, #0x24]
	and r5, r0, #0x3
	cmp r3, #0x0
	add r1, lr, #0xa000000
	beq _020DC92C
_020DC91C:
	ldrb r0, [r4], #0x1
	subs r3, r3, #0x1
	strb r0, [r1], #0x1
	bne _020DC91C
_020DC92C:
	ldr ip, _020DC994 ; =0x04000208
	ldr r3, _020DC9A0 ; =0x021D6B24
	ldrh r0, [r12, #0x0]
	sub r1, r1, #0x1
	mov r0, #0x1
	strh r2, [r12, #0x0]
	ldrb r2, [r4, #-0x1]
	ldr r3, [r3, #0x0]
	blx r3
	ldr r3, _020DC988 ; =0x04000204
	ldr r1, _020DC984 ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x24
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DC984: .word 0x021D6B0C
_020DC988: .word 0x04000204
_020DC98C: .word 0x021D6B20
_020DC990: .word 0x02104048
_020DC994: .word 0x04000208
_020DC998: .word 0x0A005555
_020DC99C: .word 0x0A002AAA
_020DC9A0: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlash4KBCoreAT
CTRDGi_EraseFlash4KBCoreAT: ; 0x020DC9A4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r0, [sp, #0x20]
	cmp r0, #0x10
	addcs sp, sp, #0x24
	ldrhs r0, _020DCA54 ; =0x000080FF
	ldmcsia sp!, {r4-r7,lr}
	bxcs lr
	mov r0, r0, lsl #0x15
	mov r5, r0, lsr #0x10
	mov r6, #0x0
	mov r4, #0x2
_020DC9F4:
	mov r7, r4
_020DC9F8:
	mov r0, r5
	bl CTRDGi_EraseFlashSectorAT
_020DCA00: ; 0x020DCA00
	cmp r0, #0x0
	beq _020DCA18
	sub r1, r7, #0x1
	mov r1, r1, lsl #0x10
	movs r7, r1, lsr #0x10
	bne _020DC9F8
_020DCA18:
	add r1, r5, #0x1
	mov r1, r1, lsl #0x10
	cmp r0, #0x0
	mov r5, r1, lsr #0x10
	addne sp, sp, #0x24
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	add r1, r6, #0x1
	mov r1, r1, lsl #0x10
	mov r6, r1, lsr #0x10
	cmp r6, #0x20
	blo _020DC9F4
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DCA54: .word 0x000080FF

	arm_func_start CTRDGi_EraseFlashSectorCoreAT
CTRDGi_EraseFlashSectorCoreAT: ; 0x020DCA58
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	ldr r1, _020DCB80 ; =0x02104048
	str r0, [r4, #0x0]
	ldr r0, _020DCB84 ; =0x021D6B0C
	ldrh r2, [sp, #0x20]
	ldrh r1, [r1, #0x28]
	ldrh r0, [r0, #0x0]
	mov r1, r2, lsl r1
	add r5, r1, #0xa000000
	bl OS_LockCartridge
	ldr r4, _020DCB88 ; =0x04000204
	ldr r1, _020DCB8C ; =0x021D6B20
	ldrh r0, [r4, #0x0]
	ldr r2, [r1, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r2, #0x10]
	ldr r3, _020DCB90 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r2, [r3, #0x0]
	mov r1, #0x0
	ldr r4, _020DCB94 ; =0x0A005555
	strh r1, [r3, #0x0]
	mov r3, #0xaa
	strb r3, [r4, #0x0]
	ldr r1, _020DCB98 ; =0x0A002AAA
	mov r3, #0x55
	strb r3, [r1, #0x0]
	mov r3, #0xa0
	strb r3, [r4, #0x0]
	ldr r1, _020DCB80 ; =0x02104048
	and r4, r0, #0x3
	ldr r1, [r1, #0x24]
	cmp r1, #0x0
	beq _020DCB18
	mov r0, #0xff
_020DCB0C:
	strb r0, [r5], #0x1
	subs r1, r1, #0x1
	bne _020DCB0C
_020DCB18:
	ldr ip, _020DCB90 ; =0x04000208
	ldr r3, _020DCB9C ; =0x021D6B24
	ldrh r0, [r12, #0x0]
	sub r1, r5, #0x1
	strh r2, [r12, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x1
	mov r2, #0xff
	blx r3
	ldr r2, _020DCB88 ; =0x04000204
	movs r5, r0
	ldrh r1, [r2, #0x0]
	andne r0, r5, #0xff00
	orrne r0, r0, #0x2
	movne r0, r0, lsl #0x10
	bic r1, r1, #0x3
	movne r5, r0, lsr #0x10
	orr r1, r1, r4
	ldr r0, _020DCB84 ; =0x021D6B0C
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r5
	add sp, sp, #0x24
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DCB80: .word 0x02104048
_020DCB84: .word 0x021D6B0C
_020DCB88: .word 0x04000204
_020DCB8C: .word 0x021D6B20
_020DCB90: .word 0x04000208
_020DCB94: .word 0x0A005555
_020DCB98: .word 0x0A002AAA
_020DCB9C: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashChipCoreAT
CTRDGi_EraseFlashChipCoreAT: ; 0x020DCBA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DCC7C ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r4, _020DCC80 ; =0x04000204
	ldr r0, _020DCC84 ; =0x021D6B20
	ldrh r3, [r4, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r0, #0x10]
	ldr r0, _020DCC88 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020DCC8C ; =0x021D6B38
	strh r2, [r0, #0x0]
	ldr lr, _020DCC90 ; =0x0A005555
	str r4, [r1, #0x0]
	mov r5, #0xaa
	ldr r4, _020DCC94 ; =0x0A002AAA
	strb r5, [lr, #0x0]
	mov r12, #0x55
	strb r12, [r4, #0x0]
	mov r2, #0x80
	strb r2, [lr, #0x0]
	strb r5, [lr, #0x0]
	strb r12, [r4, #0x0]
	mov r2, #0x10
	strb r2, [lr, #0x0]
	ldrh r2, [r0, #0x0]
	ldr r2, [r1, #0x0]
	ldr r1, _020DCC98 ; =0x021D6B24
	strh r2, [r0, #0x0]
	ldr r4, [r1, #0x0]
	mov r0, #0x3
	mov r1, #0xa000000
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DCC80 ; =0x04000204
	ldr r1, _020DCC7C ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DCC7C: .word 0x021D6B0C
_020DCC80: .word 0x04000204
_020DCC84: .word 0x021D6B20
_020DCC88: .word 0x04000208
_020DCC8C: .word 0x021D6B38
_020DCC90: .word 0x0A005555
_020DCC94: .word 0x0A002AAA
_020DCC98: .word 0x021D6B24

	arm_func_start CTRDGi_WriteFlashSectorAsyncLE
CTRDGi_WriteFlashSectorAsyncLE: ; 0x020DCC9C
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DCCC4 ; =CTRDGi_WriteFlashSectorCoreLE
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DCCC4: .word CTRDGi_WriteFlashSectorCoreLE

	arm_func_start CTRDGi_EraseFlashSectorAsyncLE
CTRDGi_EraseFlashSectorAsyncLE: ; 0x020DCCC8
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DCCF0 ; =CTRDGi_EraseFlashSectorCoreLE
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DCCF0: .word CTRDGi_EraseFlashSectorCoreLE

	arm_func_start CTRDGi_EraseFlashChipAsyncLE
CTRDGi_EraseFlashChipAsyncLE: ; 0x020DCCF4
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	ldr r1, _020DCD18 ; =CTRDGi_EraseFlashChipCoreLE
	mov r2, r0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DCD18: .word CTRDGi_EraseFlashChipCoreLE

	arm_func_start CTRDGi_WriteFlashSectorLE
CTRDGi_WriteFlashSectorLE: ; 0x020DCD1C
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreLE
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashSectorLE
CTRDGi_EraseFlashSectorLE: ; 0x020DCD48
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashSectorCoreLE
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashChipLE
CTRDGi_EraseFlashChipLE: ; 0x020DCD70
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashChipCoreLE
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_VerifyFlashErase
CTRDGi_VerifyFlashErase: ; 0x020DCD94
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020DCE14 ; =0x021D6B0C
	mov r4, r0
	ldrh r0, [r2, #0x0]
	mov r5, r1
	bl OS_LockCartridge
	ldr ip, _020DCE18 ; =0x04000204
	ldr r0, _020DCE1C ; =0x021D6B20
	ldrh r3, [r12, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r12, #0x0]
	ldr r2, [r0, #0x10]
	mov r0, r4
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r12, #0x0]
	and r6, r3, #0x3
	mov r4, #0x0
	blx r5
	cmp r0, #0x0
	ldr r2, _020DCE18 ; =0x04000204
	ldr r0, _020DCE14 ; =0x021D6B0C
	ldrh r1, [r2, #0x0]
	ldrne r4, _020DCE20 ; =0x00008004
	bic r1, r1, #0x3
	orr r1, r1, r6
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020DCE14: .word 0x021D6B0C
_020DCE18: .word 0x04000204
_020DCE1C: .word 0x021D6B20
_020DCE20: .word 0x00008004

	arm_func_start CTRDGi_VerifyFlashCoreFF
CTRDGi_VerifyFlashCoreFF: ; 0x020DCE24
	ldr r1, _020DCE54 ; =0x021D6B20
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _020DCE4C
_020DCE38:
	ldrb r1, [r0], #0x1
	cmp r1, #0xff
	bne _020DCE4C
	subs r2, r2, #0x1
	bne _020DCE38
_020DCE4C:
	mov r0, r2
	bx lr
	.balign 4
_020DCE54: .word 0x021D6B20

	arm_func_start CTRDGi_WriteFlashSectorCoreLE
CTRDGi_WriteFlashSectorCoreLE: ; 0x020DCE58
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r7, [sp, #0x20]
	ldr r6, [sp, #0xc]
	cmp r7, #0x10
	addcs sp, sp, #0x24
	ldrhs r0, _020DD018 ; =0x000080FF
	ldmcsia sp!, {r4-r9,lr}
	bxcs lr
	ldr r0, _020DD01C ; =0x021D6B20
	mov r9, #0x0
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x8]
	mov r0, r7, lsl r0
	add r4, r0, #0xa000000
	ldr r5, _020DD020 ; =CTRDGi_VerifyFlashCoreFF
_020DCEB8:
	mov r0, r7
	bl CTRDGi_EraseFlashSectorLE
	movs r8, r0
	bne _020DCEE0
	mov r0, r4
	mov r1, r5
	bl CTRDGi_VerifyFlashErase
	mov r0, r0, lsl #0x10
	movs r8, r0, lsr #0x10
	beq _020DCF04
_020DCEE0:
	add r0, r9, #0x1
	mov r0, r0, lsl #0x10
	cmp r9, #0x50
	mov r9, r0, lsr #0x10
	bne _020DCEB8
	add sp, sp, #0x24
	mov r0, r8
	ldmia sp!, {r4-r9,lr}
	bx lr
_020DCF04:
	mov r5, #0x1
	cmp r9, #0x0
	movne r5, #0x6
	cmp r5, #0x1
	mov r9, #0x1
	blo _020DCF38
_020DCF1C:
	mov r0, r7
	bl CTRDGi_EraseFlashSectorLE
	add r0, r9, #0x1
	mov r0, r0, lsl #0x10
	mov r9, r0, lsr #0x10
	cmp r9, r5
	bls _020DCF1C
_020DCF38:
	ldr r0, _020DD024 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r5, _020DD028 ; =0x04000204
	ldr r1, _020DD01C ; =0x021D6B20
	ldrh r0, [r5, #0x0]
	ldr r3, [r1, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r3, [r3, #0x10]
	ldr r7, _020DD02C ; =0x021D6B08
	bic r2, r2, #0x3
	orr r2, r2, r3
	strh r2, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldr sb, _020DD030 ; =0x04000208
	ldr r1, [r1, #0x4]
	mov r2, #0x0
	strh r1, [r7, #0x0]
	ldrh r3, [r9, #0x0]
	ldr r1, _020DD034 ; =0x021D6B38
	and r5, r0, #0x3
	strh r2, [r9, #0x0]
	ldrh r0, [r7, #0x0]
	str r3, [r1, #0x0]
	cmp r0, #0x0
	beq _020DCFD4
_020DCFA0:
	mov r0, r6
	mov r1, r4
	bl CTRDGi_ProgramFlashByteLE
	movs r8, r0
	bne _020DCFD4
	ldrh r0, [r7, #0x0]
	add r6, r6, #0x1
	add r4, r4, #0x1
	sub r0, r0, #0x1
	strh r0, [r7, #0x0]
	ldrh r0, [r7, #0x0]
	cmp r0, #0x0
	bne _020DCFA0
_020DCFD4:
	ldr r3, _020DD030 ; =0x04000208
	ldr r0, _020DD034 ; =0x021D6B38
	ldrh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, _020DD028 ; =0x04000204
	strh r0, [r3, #0x0]
	ldrh r1, [r2, #0x0]
	ldr r0, _020DD024 ; =0x021D6B0C
	bic r1, r1, #0x3
	orr r1, r1, r5
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r8
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020DD018: .word 0x000080FF
_020DD01C: .word 0x021D6B20
_020DD020: .word CTRDGi_VerifyFlashCoreFF
_020DD024: .word 0x021D6B0C
_020DD028: .word 0x04000204
_020DD02C: .word 0x021D6B08
_020DD030: .word 0x04000208
_020DD034: .word 0x021D6B38

	arm_func_start CTRDGi_ProgramFlashByteLE
CTRDGi_ProgramFlashByteLE: ; 0x020DD038
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020DD08C ; =0x0A005555
	mov r3, #0xaa
	ldr r2, _020DD090 ; =0x0A002AAA
	strb r3, [r12, #0x0]
	mov r3, #0x55
	mov lr, r0
	strb r3, [r2, #0x0]
	mov r0, #0xa0
	strb r0, [r12, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, _020DD094 ; =0x021D6B24
	mov r0, #0x1
	strb r2, [r1, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, [r3, #0x0]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD08C: .word 0x0A005555
_020DD090: .word 0x0A002AAA
_020DD094: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashSectorCoreLE
CTRDGi_EraseFlashSectorCoreLE: ; 0x020DD098
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r4, [sp, #0x20]
	cmp r4, #0x10
	addcs sp, sp, #0x28
	ldrhs r0, _020DD1B8 ; =0x000080FF
	ldmcsia sp!, {r4-r6,lr}
	bxcs lr
	ldr r0, _020DD1BC ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r6, _020DD1C0 ; =0x04000204
	ldr r1, _020DD1C4 ; =0x021D6B20
	ldrh r3, [r6, #0x0]
	ldr r0, [r1, #0x0]
	ldrh r2, [r6, #0x0]
	ldr r5, [r0, #0x10]
	ldr r0, _020DD1C8 ; =0x04000208
	bic r2, r2, #0x3
	orr r2, r2, r5
	strh r2, [r6, #0x0]
	ldr r1, [r1, #0x0]
	ldrh r5, [r0, #0x0]
	ldrh r12, [r1, #0x8]
	mov r1, #0x0
	ldr r2, _020DD1CC ; =0x021D6B38
	strh r1, [r0, #0x0]
	mov r6, r4, lsl r12
	ldr lr, _020DD1D0 ; =0x0A005555
	str r5, [r2, #0x0]
	mov r5, #0xaa
	ldr r4, _020DD1D4 ; =0x0A002AAA
	strb r5, [lr, #0x0]
	mov r12, #0x55
	strb r12, [r4, #0x0]
	mov r1, #0x80
	strb r1, [lr, #0x0]
	strb r5, [lr, #0x0]
	strb r12, [r4, #0x0]
	add r1, r6, #0xa000000
	mov r4, #0x30
	strb r4, [r1, #0x0]
	ldrh r4, [r0, #0x0]
	ldr r4, [r2, #0x0]
	ldr r2, _020DD1D8 ; =0x021D6B24
	strh r4, [r0, #0x0]
	ldr r4, [r2, #0x0]
	mov r0, #0x2
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DD1C0 ; =0x04000204
	ldr r1, _020DD1BC ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x28
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020DD1B8: .word 0x000080FF
_020DD1BC: .word 0x021D6B0C
_020DD1C0: .word 0x04000204
_020DD1C4: .word 0x021D6B20
_020DD1C8: .word 0x04000208
_020DD1CC: .word 0x021D6B38
_020DD1D0: .word 0x0A005555
_020DD1D4: .word 0x0A002AAA
_020DD1D8: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashChipCoreLE
CTRDGi_EraseFlashChipCoreLE: ; 0x020DD1DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DD2B8 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r4, _020DD2BC ; =0x04000204
	ldr r0, _020DD2C0 ; =0x021D6B20
	ldrh r3, [r4, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r0, #0x10]
	ldr r0, _020DD2C4 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020DD2C8 ; =0x021D6B38
	strh r2, [r0, #0x0]
	ldr lr, _020DD2CC ; =0x0A005555
	str r4, [r1, #0x0]
	mov r5, #0xaa
	ldr r4, _020DD2D0 ; =0x0A002AAA
	strb r5, [lr, #0x0]
	mov r12, #0x55
	strb r12, [r4, #0x0]
	mov r2, #0x80
	strb r2, [lr, #0x0]
	strb r5, [lr, #0x0]
	strb r12, [r4, #0x0]
	mov r2, #0x10
	strb r2, [lr, #0x0]
	ldrh r2, [r0, #0x0]
	ldr r2, [r1, #0x0]
	ldr r1, _020DD2D4 ; =0x021D6B24
	strh r2, [r0, #0x0]
	ldr r4, [r1, #0x0]
	mov r0, #0x3
	mov r1, #0xa000000
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DD2BC ; =0x04000204
	ldr r1, _020DD2B8 ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DD2B8: .word 0x021D6B0C
_020DD2BC: .word 0x04000204
_020DD2C0: .word 0x021D6B20
_020DD2C4: .word 0x04000208
_020DD2C8: .word 0x021D6B38
_020DD2CC: .word 0x0A005555
_020DD2D0: .word 0x0A002AAA
_020DD2D4: .word 0x021D6B24

	arm_func_start CTRDGi_WriteFlashSectorAsyncMX
CTRDGi_WriteFlashSectorAsyncMX: ; 0x020DD2D8
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DD300 ; =CTRDGi_WriteFlashSectorCoreMX
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD300: .word CTRDGi_WriteFlashSectorCoreMX

	arm_func_start CTRDGi_EraseFlashSectorAsyncMX
CTRDGi_EraseFlashSectorAsyncMX: ; 0x020DD304
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DD32C ; =CTRDGi_EraseFlashSectorCoreMX
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD32C: .word CTRDGi_EraseFlashSectorCoreMX

	arm_func_start CTRDGi_EraseFlashChipAsyncMX
CTRDGi_EraseFlashChipAsyncMX: ; 0x020DD330
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	ldr r1, _020DD354 ; =CTRDGi_EraseFlashChipCoreMX
	mov r2, r0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD354: .word CTRDGi_EraseFlashChipCoreMX

	arm_func_start CTRDGi_WriteFlashSectorMX
CTRDGi_WriteFlashSectorMX: ; 0x020DD358
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreMX
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashSectorMX
CTRDGi_EraseFlashSectorMX: ; 0x020DD384
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashSectorCoreMX
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashChipMX
CTRDGi_EraseFlashChipMX: ; 0x020DD3AC
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashChipCoreMX
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlashSectorCoreMX
CTRDGi_WriteFlashSectorCoreMX: ; 0x020DD3D0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DD540 ; =0x021D6B20
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r5, [sp, #0x20]
	ldrh r0, [r0, #0xa]
	ldr r4, [sp, #0xc]
	cmp r5, r0
	addcs sp, sp, #0x28
	ldrhs r0, _020DD544 ; =0x000080FF
	ldmcsia sp!, {r4-r8,lr}
	bxcs lr
	mov r0, r5
	bl CTRDGi_EraseFlashSectorMX
	movs r6, r0
	addne sp, sp, #0x28
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r0, _020DD548 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r7, _020DD54C ; =0x04000204
	ldr r0, _020DD540 ; =0x021D6B20
	ldrh r3, [r7, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r1, [r7, #0x0]
	mov r0, r5, lsl #0xc
	ldr r2, [r2, #0x10]
	bic r1, r1, #0x3
	orr r1, r1, r2
	mov r0, r0, lsr #0x10
	strh r1, [r7, #0x0]
	and r7, r3, #0x3
	bl CTRDGi_SetFlashBankMx
	ldr r0, _020DD540 ; =0x021D6B20
	and r1, r5, #0xf
	ldr r3, [r0, #0x0]
	mov r0, r1, lsl #0x10
	ldr r2, [r3, #0x4]
	ldr r8, _020DD550 ; =0x021D6B08
	ldr r1, _020DD554 ; =0x04000208
	strh r2, [r8, #0x0]
	ldrh r3, [r3, #0x8]
	mov r5, r0, lsr #0x10
	ldrh r2, [r1, #0x0]
	mov r0, #0x0
	mov r3, r5, lsl r3
	strh r0, [r1, #0x0]
	ldrh r1, [r8, #0x0]
	ldr r0, _020DD558 ; =0x021D6B38
	add r5, r3, #0xa000000
	str r2, [r0, #0x0]
	cmp r1, #0x0
	beq _020DD4FC
_020DD4C8:
	mov r0, r4
	mov r1, r5
	bl CTRDGi_ProgramFlashByteMX
	movs r6, r0
	bne _020DD4FC
	ldrh r0, [r8, #0x0]
	add r4, r4, #0x1
	add r5, r5, #0x1
	sub r0, r0, #0x1
	strh r0, [r8, #0x0]
	ldrh r0, [r8, #0x0]
	cmp r0, #0x0
	bne _020DD4C8
_020DD4FC:
	ldr r3, _020DD554 ; =0x04000208
	ldr r0, _020DD558 ; =0x021D6B38
	ldrh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, _020DD54C ; =0x04000204
	strh r0, [r3, #0x0]
	ldrh r1, [r2, #0x0]
	ldr r0, _020DD548 ; =0x021D6B0C
	bic r1, r1, #0x3
	orr r1, r1, r7
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r6
	add sp, sp, #0x28
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DD540: .word 0x021D6B20
_020DD544: .word 0x000080FF
_020DD548: .word 0x021D6B0C
_020DD54C: .word 0x04000204
_020DD550: .word 0x021D6B08
_020DD554: .word 0x04000208
_020DD558: .word 0x021D6B38

	arm_func_start CTRDGi_ProgramFlashByteMX
CTRDGi_ProgramFlashByteMX: ; 0x020DD55C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020DD5B0 ; =0x0A005555
	mov r3, #0xaa
	ldr r2, _020DD5B4 ; =0x0A002AAA
	strb r3, [r12, #0x0]
	mov r3, #0x55
	mov lr, r0
	strb r3, [r2, #0x0]
	mov r0, #0xa0
	strb r0, [r12, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, _020DD5B8 ; =0x021D6B24
	mov r0, #0x1
	strb r2, [r1, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, [r3, #0x0]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD5B0: .word 0x0A005555
_020DD5B4: .word 0x0A002AAA
_020DD5B8: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashSectorCoreMX
CTRDGi_EraseFlashSectorCoreMX: ; 0x020DD5BC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x10
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DD748 ; =0x021D6B20
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r4, [sp, #0x30]
	ldrh r0, [r0, #0xa]
	cmp r4, r0
	addcs sp, sp, #0x34
	ldrhs r0, _020DD74C ; =0x000080FF
	ldmcsia sp!, {r4-r11,lr}
	bxcs lr
	ldr r0, _020DD750 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r5, _020DD754 ; =0x04000204
	ldr r0, _020DD748 ; =0x021D6B20
	ldrh r3, [r5, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r1, [r5, #0x0]
	mov r0, r4, lsl #0xc
	ldr r2, [r2, #0x10]
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r5, #0x0]
	and r1, r3, #0x3
	mov r0, r0, lsr #0x10
	str r1, [sp, #0x0]
	bl CTRDGi_SetFlashBankMx
	and r0, r4, #0xf
	mov r0, r0, lsl #0x10
	mov r9, r0, lsr #0x10
	mov r0, #0x2
	mov r10, #0x0
	str r0, [sp, #0x8]
	mov r0, #0xff
	ldr r8, _020DD758 ; =0x04000208
	mov r11, r10
	mov r7, #0xaa
	mov r6, #0x55
	mov r5, #0x80
	mov r4, #0x30
	str r0, [sp, #0xc]
_020DD684:
	ldr r0, _020DD748 ; =0x021D6B20
	ldrh r12, [r8, #0x0]
	ldr r0, [r0, #0x0]
	ldr r3, _020DD75C ; =0x021D6B38
	ldrh r1, [r0, #0x8]
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	strh r11, [r8, #0x0]
	str r12, [r3, #0x0]
	ldr r3, _020DD760 ; =0x0A005555
	mov r1, r9, lsl r1
	strb r7, [r3, #0x0]
	ldr r3, _020DD764 ; =0x0A002AAA
	add r1, r1, #0xa000000
	strb r6, [r3, #0x0]
	ldr r3, _020DD760 ; =0x0A005555
	strb r5, [r3, #0x0]
	strb r7, [r3, #0x0]
	ldr r3, _020DD764 ; =0x0A002AAA
	strb r6, [r3, #0x0]
	strb r4, [r1, #0x0]
	ldrh r3, [r8, #0x0]
	ldr r3, _020DD75C ; =0x021D6B38
	ldr r3, [r3, #0x0]
	strh r3, [r8, #0x0]
	ldr r3, _020DD768 ; =0x021D6B24
	ldr r3, [r3, #0x0]
	blx r3
	str r0, [sp, #0x4]
	ands r0, r0, #0xa000
	beq _020DD714
	cmp r10, #0x0
	addeq r0, r10, #0x1
	moveq r0, r0, lsl #0x10
	moveq r10, r0, lsr #0x10
	beq _020DD684
_020DD714:
	ldr r2, _020DD754 ; =0x04000204
	ldr r1, _020DD750 ; =0x021D6B0C
	ldrh r0, [r2, #0x0]
	bic r3, r0, #0x3
	ldr r0, [sp, #0x0]
	orr r0, r3, r0
	strh r0, [r2, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	ldr r0, [sp, #0x4]
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020DD748: .word 0x021D6B20
_020DD74C: .word 0x000080FF
_020DD750: .word 0x021D6B0C
_020DD754: .word 0x04000204
_020DD758: .word 0x04000208
_020DD75C: .word 0x021D6B38
_020DD760: .word 0x0A005555
_020DD764: .word 0x0A002AAA
_020DD768: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashChipCoreMX
CTRDGi_EraseFlashChipCoreMX: ; 0x020DD76C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DD848 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r4, _020DD84C ; =0x04000204
	ldr r0, _020DD850 ; =0x021D6B20
	ldrh r3, [r4, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r0, #0x10]
	ldr r0, _020DD854 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020DD858 ; =0x021D6B38
	strh r2, [r0, #0x0]
	ldr lr, _020DD85C ; =0x0A005555
	str r4, [r1, #0x0]
	mov r5, #0xaa
	ldr r4, _020DD860 ; =0x0A002AAA
	strb r5, [lr, #0x0]
	mov r12, #0x55
	strb r12, [r4, #0x0]
	mov r2, #0x80
	strb r2, [lr, #0x0]
	strb r5, [lr, #0x0]
	strb r12, [r4, #0x0]
	mov r2, #0x10
	strb r2, [lr, #0x0]
	ldrh r2, [r0, #0x0]
	ldr r2, [r1, #0x0]
	ldr r1, _020DD864 ; =0x021D6B24
	strh r2, [r0, #0x0]
	ldr r4, [r1, #0x0]
	mov r0, #0x3
	mov r1, #0xa000000
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DD84C ; =0x04000204
	ldr r1, _020DD848 ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DD848: .word 0x021D6B0C
_020DD84C: .word 0x04000204
_020DD850: .word 0x021D6B20
_020DD854: .word 0x04000208
_020DD858: .word 0x021D6B38
_020DD85C: .word 0x0A005555
_020DD860: .word 0x0A002AAA
_020DD864: .word 0x021D6B24

	arm_func_start FUN_020DD868
FUN_020DD868: ; 0x020DD868
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DD890 ; =FUN_020DD8C0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD890: .word FUN_020DD8C0

	arm_func_start FUN_020DD894
FUN_020DD894: ; 0x020DD894
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl FUN_020DD8C0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020DD8C0
FUN_020DD8C0: ; 0x020DD8C0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DD9E8 ; =0x021D6B20
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r5, [sp, #0x20]
	ldrh r0, [r0, #0xa]
	ldr r4, [sp, #0xc]
	cmp r5, r0
	addcs sp, sp, #0x28
	ldrhs r0, _020DD9EC ; =0x000080FF
	ldmcsia sp!, {r4-r8,lr}
	bxcs lr
	mov r0, r5
	bl CTRDGi_EraseFlashSectorLE
	movs r6, r0
	addne sp, sp, #0x28
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r0, _020DD9F0 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r7, _020DD9F4 ; =0x04000204
	ldr r0, _020DD9E8 ; =0x021D6B20
	ldrh r3, [r7, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r1, [r7, #0x0]
	ldr r2, [r2, #0x10]
	ldr r8, _020DD9F8 ; =0x021D6B08
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r7, #0x0]
	ldr r1, [r0, #0x0]
	and r7, r3, #0x3
	ldr r0, [r1, #0x4]
	strh r0, [r8, #0x0]
	ldrh r1, [r1, #0x8]
	ldrh r0, [r8, #0x0]
	mov r1, r5, lsl r1
	cmp r0, #0x0
	add r5, r1, #0xa000000
	beq _020DD9B8
_020DD984:
	mov r0, r4
	mov r1, r5
	bl CTRDGi_ProgramFlashByteLE
	movs r6, r0
	bne _020DD9B8
	ldrh r0, [r8, #0x0]
	add r4, r4, #0x1
	add r5, r5, #0x1
	sub r0, r0, #0x1
	strh r0, [r8, #0x0]
	ldrh r0, [r8, #0x0]
	cmp r0, #0x0
	bne _020DD984
_020DD9B8:
	ldr r2, _020DD9F4 ; =0x04000204
	ldr r0, _020DD9F0 ; =0x021D6B0C
	ldrh r1, [r2, #0x0]
	bic r1, r1, #0x3
	orr r1, r1, r7
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r6
	add sp, sp, #0x28
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DD9E8: .word 0x021D6B20
_020DD9EC: .word 0x000080FF
_020DD9F0: .word 0x021D6B0C
_020DD9F4: .word 0x04000204
_020DD9F8: .word 0x021D6B08

	arm_func_start CTRDGi_SetTask
CTRDGi_SetTask: ; 0x020DD9FC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _020DDAA8 ; =0x021D6B50
	mov r7, r0
	mov r4, r1
	mov r6, r2
	ldr r5, [r3, #0x0]
	bl CTRDGi_IsTaskAvailable
_020DDA1C: ; 0x020DDA1C
	cmp r0, #0x0
	bne _020DDA28
	bl OS_Terminate
_020DDA28:
	ldr r0, _020DDAAC ; =0x021D6B54
	ldrb r0, [r0, #0x22]
	cmp r0, #0x0
	beq _020DDA3C
	bl OS_Terminate
_020DDA3C:
	bl OS_DisableInterrupts
	mov r1, #0x1
	strb r1, [r7, #0x22]
	str r4, [r7, #0x0]
	add r1, r5, #0xc4
	cmp r7, r1
	mov r4, r0
	ldreq r0, _020DDAA8 ; =0x021D6B50
	str r6, [r7, #0x4]
	moveq r1, #0x0
	streq r1, [r0, #0x0]
	ldr ip, _020DDAAC ; =0x021D6B54
	ldmia r7!, {r0-r3}
	mov r6, r12
	stmia r12!, {r0-r3}
	ldmia r7!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r1, [r7, #0x0]
	mov r0, r5
	str r1, [r12, #0x0]
	str r6, [r5, #0xc0]
	bl OS_WakeupThreadDirect
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DDAA8: .word 0x021D6B50
_020DDAAC: .word 0x021D6B54

	arm_func_start CTRDGi_TaskThread
CTRDGi_TaskThread: ; 0x020DDAB0
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x28
	ldr r6, _020DDB94 ; =0x021D6B54
	ldr r5, _020DDB98 ; =0x021D6B50
	mov r4, r0
	add r9, sp, #0x0
	mov r8, #0x0
	mov r7, #0x24
_020DDAD0:
	mov r0, r9
	mov r1, r8
	mov r2, r7
	bl MI_CpuFill8
	bl OS_DisableInterrupts
	ldr r1, [r4, #0xc0]
	mov r10, r0
	cmp r1, #0x0
	bne _020DDB08
_020DDAF4:
	mov r0, r8
	bl OS_SleepThread
	ldr r0, [r4, #0xc0]
	cmp r0, #0x0
	beq _020DDAF4
_020DDB08:
	ldr lr, [r4, #0xc0]
	add r12, sp, #0x0
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r1, [lr, #0x0]
	mov r0, r10
	str r1, [r12, #0x0]
	bl OS_RestoreInterrupts
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	beq _020DDB48
	mov r0, r9
	blx r1
	str r0, [sp, #0x8]
_020DDB48:
	bl OS_DisableInterrupts
	ldr r1, [sp, #0x4]
	mov r10, r0
	strb r8, [r6, #0x22]
	cmp r1, #0x0
	beq _020DDB68
	mov r0, r9
	blx r1
_020DDB68:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020DDB84
	mov r0, r10
	str r8, [r4, #0xc0]
	bl OS_RestoreInterrupts
	b _020DDAD0
_020DDB84:
	bl OS_ExitThread
	add sp, sp, #0x28
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020DDB94: .word 0x021D6B54
_020DDB98: .word 0x021D6B50

	arm_func_start CTRDGi_InitTaskInfo
CTRDGi_InitTaskInfo:
	ldr ip, _020DDBAC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x24
	bx r12
	.balign 4
_020DDBAC: .word MI_CpuFill8

	arm_func_start CTRDGi_IsTaskAvailable
CTRDGi_IsTaskAvailable:
	ldr r0, _020DDBC8 ; =0x021D6B50
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	.balign 4
_020DDBC8: .word 0x021D6B50

	arm_func_start CTRDGi_InitTaskThread
CTRDGi_InitTaskThread: ; 0x020DDBCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020DDC4C ; =0x021D6B50
	mov r4, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020DDC38
	add r0, r5, #0xc4
	str r5, [r1, #0x0]
	bl CTRDGi_InitTaskInfo
	ldr r0, _020DDC50 ; =0x021D6B54
	bl CTRDGi_InitTaskInfo
_020DDC04: ; 0x020DDC04
	mov r0, #0x0
	str r0, [r5, #0xc0]
	mov r2, #0x400
	ldr r1, _020DDC54 ; =CTRDGi_TaskThread
	ldr r3, _020DDC58 ; =0x021D6F78
	mov r0, r5
	str r2, [sp, #0x0]
	mov r2, #0x14
	str r2, [sp, #0x4]
	mov r2, r5
	bl OS_CreateThread
	mov r0, r5
	bl OS_WakeupThreadDirect
_020DDC38:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DDC4C: .word 0x021D6B50
_020DDC50: .word 0x021D6B54
_020DDC54: .word CTRDGi_TaskThread
_020DDC58: .word 0x021D6F78
