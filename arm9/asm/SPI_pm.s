	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_021D54DC
	.extern UNK_021D54E0
	.extern UNK_021D54D0
	.extern UNK_021D54D4
	.extern UNK_021D54F4
	.extern UNK_021D54CC
	.extern UNK_021D5510
	.extern UNK_021D54E4
	.extern UNK_021D54D8
	.extern UNK_021D550C

	.text

	arm_func_start PM_DeletePostSleepCallback
PM_DeletePostSleepCallback: ; 0x020D4AE8
	ldr ip, _020D4AF8 ; =0x020D4B78
	mov r1, r0
	ldr r0, _020D4AFC ; =UNK_021D54E0
	bx r12
	.balign 4
_020D4AF8: .word 0x020D4B78
_020D4AFC: .word UNK_021D54E0

	arm_func_start PM_DeletePreSleepCallback
PM_DeletePreSleepCallback: ; 0x020D4B00
	ldr ip, _020D4B10 ; =0x020D4B78
	mov r1, r0
	ldr r0, _020D4B14 ; =UNK_021D54D8
	bx r12
	.balign 4
_020D4B10: .word 0x020D4B78
_020D4B14: .word UNK_021D54D8

	arm_func_start PM_AppendPostSleepCallback
PM_AppendPostSleepCallback: ; 0x020D4B18
	ldr ip, _020D4B28 ; =PMi_AppendList
	mov r1, r0
	ldr r0, _020D4B2C ; =UNK_021D54E0
	bx r12
	.balign 4
_020D4B28: .word PMi_AppendList
_020D4B2C: .word UNK_021D54E0

	arm_func_start PM_PrependPreSleepCallback
PM_PrependPreSleepCallback: ; 0x020D4B30
	ldr ip, _020D4B40 ; =PMi_PrependList
	mov r1, r0
	ldr r0, _020D4B44 ; =UNK_021D54D8
	bx r12
	.balign 4
_020D4B40: .word PMi_PrependList
_020D4B44: .word UNK_021D54D8

	arm_func_start PMi_ExecuteList
PMi_ExecuteList: ; 0x020D4B48
	stmdb sp!, {r4,lr}
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020D4B58:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x0]
	blx r1
	ldr r4, [r4, #0x8]
	cmp r4, #0x0
	bne _020D4B58
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start PMi_DeleteList
PMi_DeleteList:
	cmp r0, #0x0
	bxeq lr
	ldr r3, [r0]
	mov r2, r3
	cmp r3, #0x0
	bxeq lr
_020D4B90:
	cmp r3, r1
	bne _020D4BB0
	cmp r3, r2
	ldreq r1, [r3, #0x8]
	streq r1, [r0]
	ldrne r0, [r3, #0x8]
	strne r0, [r2, #0x8]
	bx lr
_020D4BB0:
	mov r2, r3
	ldr r3, [r3, #0x8]
	cmp r3, #0x0
	bne _020D4B90
	bx lr

	arm_func_start PMi_AppendList
PMi_AppendList: ; 0x020D4BC4
	cmp r0, #0x0
	bxeq lr
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	moveq r2, #0x0
	streq r2, [r1, #0x8]
	streq r1, [r0, #0x0]
	bxeq lr
	ldr r0, [r2, #0x8]
	cmp r0, #0x0
	beq _020D4C00
_020D4BF0:
	mov r2, r0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _020D4BF0
_020D4C00:
	str r0, [r1, #0x8]
	str r1, [r2, #0x8]
	bx lr

	arm_func_start PMi_PrependList
PMi_PrependList: ; 0x020D4C0C
	cmp r0, #0x0
	ldrne r2, [r0, #0x0]
	strne r2, [r1, #0x8]
	strne r1, [r0, #0x0]
	bx lr

	arm_func_start PM_GetLEDPattern
PM_GetLEDPattern: ; 0x020D4C20
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4C58 ; =0x020D587C
	add r2, sp, #0x0
	bl PM_GetLEDPatternAsync
_020D4C34:
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmnefd sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
	ldr r0, [sp]
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020D4C58: .word 0x020D587C

	arm_func_start PM_GetLEDPatternAsync
PM_GetLEDPatternAsync:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl PMi_Lock
_020D4C70:
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, _020D4CA4
	ldr r0, _020D4CA8
	str r5, [r1, #0x4]
	str r4, [r1, #0x8]
	str r6, [r1, #0xC]
	bl PMi_SendPxiData
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D4CA4: .word UNK_021D54E4
_020D4CA8: .word 0x03006700

	arm_func_start PMi_SendLEDPatternCommand
PMi_SendLEDPatternCommand: ; 0x020D4CAC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4CE4 ; =0x020D587C
	add r2, sp, #0x0
	bl PMi_SendLEDPatternCommandAsync
_020D4CC0:
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmnefd sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
	ldr r0, [sp]
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020D4CE4: .word 0x020D587C

	arm_func_start PMi_SendLEDPatternCommandAsync
PMi_SendLEDPatternCommandAsync:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl PMi_Lock
_020D4CFC:
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, _020D4D34
	ldr r1, _020D4D38
	and r2, r6, #0xff
	orr r0, r2, r0
	str r5, [r1, #0x4]
	str r4, [r1, #0x8]
	bl PMi_SendPxiData
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D4D34: .word 0x03006600
_020D4D38: .word UNK_021D54E4

	arm_func_start PM_GetLCDPower
PM_GetLCDPower: ; 0x020D4D3C
	ldr r0, _020D4D54 ; =0x04000304
	ldrh r0, [r0, #0x0]
	ands r0, r0, #0x1
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
	.balign 4
_020D4D54: .word 0x04000304

	arm_func_start PM_SetLCDPower
PM_SetLCDPower: ; 0x020D4D58
	ldr ip, _020D4D74 ; =PMi_SetLCDPower
	mov r1, #0x0
	cmp r0, #0x1
	movne r0, #0x0
	mov r2, r1
	mov r3, #0x1
	bx r12
	.balign 4
_020D4D74: .word PMi_SetLCDPower

	arm_func_start PMi_SetLCDPower
PMi_SetLCDPower: ; 0x020D4D78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	beq _020D4E00
	cmp r0, #0x1
	bne _020D4E4C
	cmp r2, #0x0
	bne _020D4DC0
	ldr r2, _020D4E5C ; =0x027FFC3C
	ldr r0, _020D4E60 ; =UNK_021D54DC
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	sub r0, r2, r0
	cmp r0, #0x7
	addls sp, sp, #0x4
	movls r0, #0x0
	ldmlsia sp!, {lr}
	bxls lr
_020D4DC0:
	cmp r1, #0x0
	beq _020D4DEC
	cmp r3, #0x0
	beq _020D4DDC
	mov r0, r1
	bl PMi_SetLED
	b _020D4DEC
_020D4DDC:
	mov r0, r1
	mov r1, #0x0
	mov r2, r1
	bl PMi_SetLEDAsync
_020D4DEC:
	ldr r1, _020D4E64 ; =0x04000304
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x1
	strh r0, [r1, #0x0]
	b _020D4E4C
_020D4E00:
	ldr lr, _020D4E64 ; =0x04000304
	ldr r2, _020D4E5C ; =0x027FFC3C
	ldrh r12, [lr, #0x0]
	ldr r0, _020D4E60 ; =UNK_021D54DC
	cmp r1, #0x0
	bic r12, r12, #0x1
	strh r12, [lr, #0x0]
	ldr r2, [r2, #0x0]
	str r2, [r0, #0x0]
	beq _020D4E4C
	cmp r3, #0x0
	beq _020D4E3C
	mov r0, r1
	bl PMi_SetLED
	b _020D4E4C
_020D4E3C:
	mov r0, r1
	mov r1, #0x0
	mov r2, r1
	bl PMi_SetLEDAsync
_020D4E4C:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4E5C: .word 0x027FFC3C
_020D4E60: .word UNK_021D54DC
_020D4E64: .word 0x04000304

	arm_func_start PM_GoSleepMode
PM_GoSleepMode: ; 0x020D4E68
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	ldr r3, _020D5084 ; =UNK_021D54D8
	mov r10, r0
	ldr r0, [r3, #0x0]
	mov r9, r1
	mov r11, r2
	mov r8, #0x0
	bl PMi_ExecuteList
	ldr r1, _020D5088 ; =0x04000208
	mov r0, r8
	ldrh r4, [r1, #0x0]
	strh r0, [r1, #0x0]
	bl OS_DisableInterrupts
_020D4EA0:
	str r0, [sp]
	ldr r0, _020D508C
	bl OS_DisableIrqMask
	str r0, [sp, #0x4]
	mov r0, #0x40000
	bl OS_SetIrqMask
	ldr r0, [sp]
	bl OS_RestoreInterrupts
	ldr r2, _020D5088
	mov r1, #0x1
	ldrh r0, [r2]
	ands r0, sl, #0x8
	strh r1, [r2]
	beq _020D4EE8
	ldr r0, _020D5090
	ldrh r0, [r0]
	cmp r0, #0x2
	biceq sl, sl, #0x8
_020D4EE8:
	ands r0, sl, #0x10
	beq _020D4EFC
	bl CTRDG_IsExisting
	cmp r0, #0x0
	biceq sl, sl, #0x10
_020D4EFC:
	ldr r0, _020D5094
	mov r1, #0x4000000
	ldr r7, [r1]
	ldr r6, [r0]
	bl PM_GetLCDPower
	str r0, [sp, #0x8]
	add r0, sp, #0xC
	add r1, sp, #0x10
	bl PM_GetBackLight
	mov r0, #0x2
	mov r1, #0x0
	bl PM_SetBackLight
	ldr r2, _020D5098
	ldr r0, [r2]
	str r0, [sp, #0x14]
_020D4F38:
	ldr r1, [r2]
	ldr r0, [sp, #0x14]
	cmp r0, r1
	beq _020D4F38
	ldr r0, [r2]
	mov r2, #0x4000000
	str r0, [sp, #0x14]
	ldr r0, [r2]
	ldr r1, _020D5094
	bic r0, r0, #0x30000
	str r0, [r2]
	ldr r0, [r1]
	bic r0, r0, #0x10000
	str r0, [r1]
	ldr r2, _020D5098
_020D4F74:
	ldr r1, [r2]
	ldr r0, [sp, #0x14]
	cmp r0, r1
	beq _020D4F74
	ldr r0, [r2]
	str r0, [sp, #0x14]
	ldr r2, _020D5098
_020D4F90:
	ldr r1, [r2]
	ldr r0, [sp, #0x14]
	cmp r0, r1
	beq _020D4F90
	ldr r0, [sp, #0xC]
	ldr r1, [sp, #0x10]
	orr r0, sl, r0, lsl #0x5
	orr r0, r0, r1, lsl #0x6
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	orr r0, r9, fp
	mov r0, r0, lsl #0x10
	mov r9, r0, lsr #0x10
_020D4FC4:
	mov r0, r5
	mov r1, r9
	bl PMi_SendSleepStart
	cmp r0, #0x0
	bne _020D4FC4
	bl OS_Halt
	ldr r0, _020D509C
	bl OS_SpinWait
	ands r0, sl, #0x8
	beq _020D4FFC
	ldr r0, _020D50A0
	ldr r0, [r0]
	ands r0, r0, #0x100000
	movne r8, #0x1
_020D4FFC:
	cmp r8, #0x0
	bne _020D5040
	ldr r0, [sp, #0x8]
	cmp r0, #0x1
	bne _020D5028
	mov r0, #0x1
	mov r1, r0
	mov r2, r0
	mov r3, #0x0
	bl PMi_SetLCDPower
	b _020D5030
_020D5028:
	mov r0, #0x1
	bl PMi_SetLED
_020D5030:
	mov r1, #0x4000000
	ldr r0, _020D5094
	str r7, [r1]
	str r6, [r0]
_020D5040:
	bl OS_DisableInterrupts
	ldr r0, [sp, #0x4]
	bl OS_SetIrqMask
	ldr r0, [sp]
	bl OS_RestoreInterrupts
	ldr r1, _020D5088
	cmp r8, #0x0
	ldrh r0, [r1]
	strh r4, [r1]
	beq _020D506C
	bl PM_ForceToPowerOff
_020D506C:
	ldr r0, _020D50A4
	ldr r0, [r0]
	bl PMi_ExecuteList
	add sp, sp, #0x1C
	ldmia sp!, {r4-r11, lr}
	bx lr
_020D5084: .word UNK_021D54D8
_020D5088: .word 0x04000208
_020D508C: .word 0x003FFFFF
_020D5090: .word 0x027FFC40
_020D5094: .word 0x04001000
_020D5098: .word 0x027FFC3C
_020D509C: .word 0x00996A00
_020D50A0: .word 0x04000214
_020D50A4: .word UNK_021D54E0


	arm_func_start PMi_SendPxiData
PMi_SendPxiData: ; 0x020D50A8
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, #0x8
	mov r4, #0x0
_020D50B8:
	mov r0, r5
	mov r1, r6
	mov r2, r4
	bl PXI_SendWordByFifo
_020D50C8:
	cmp r0, #0
	bne _020D50B8
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start PM_GetBackLight
PM_GetBackLight: ; 0x020D50D8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	add r1, sp, #0x0
	mov r0, #0x0
	bl PMi_ReadRegister
_020D50F4:
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r5, #0x0
	beq _020D5120
	ldrh r1, [sp]
	ands r1, r1, #0x8
	movne r1, #0x1
	moveq r1, #0x0
	str r1, [r5]
_020D5120:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrh r1, [sp]
	ands r1, r1, #0x4
	movne r1, #0x1
	moveq r1, #0x0
	str r1, [r4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start PM_SetAmpGain
PM_SetAmpGain: ; 0x020D5150
	ldr ip, _020D5164 ; =PMi_WriteRegister
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, #0x3
	bx r12
	.balign 4
_020D5164: .word PMi_WriteRegister

	arm_func_start PM_SetAmp
PM_SetAmp: ; 0x020D5168
	ldr ip, _020D517C ; =PMi_WriteRegister
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, #0x2
	bx r12
	.balign 4
_020D517C: .word PMi_WriteRegister

	arm_func_start PM_ForceToPowerOff
PM_ForceToPowerOff: ; 0x020D5180
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020D51B8 ; =PMi_DummyCallback
	add r1, sp, #0x0
	bl PM_ForceToPowerOffAsync
_020D5194: ; 0x020D5194
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
_020D51A8: ; 0x020D51A8
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D51B8: .word PMi_DummyCallback

	arm_func_start PM_ForceToPowerOffAsync
PM_ForceToPowerOffAsync:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldr r0, _020D5268 ; =0x00996A00
	mov r6, r1
	bl OS_SpinWait
	bl PM_GetLCDPower
	cmp r0, #0x1
	beq _020D524C
	add r0, sp, #0x0
	add r1, sp, #0x4
	bl PM_GetBackLight
_020D51EC: ; 0x020D51EC
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020D5204
	mov r0, #0x0
	mov r1, r0
	bl PM_SetBackLight
_020D5204:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020D521C
	mov r0, #0x1
	mov r1, #0x0
	bl PM_SetBackLight
_020D521C:
	mov r0, #0x1
	bl PM_SetLCDPower
_020D5224: ; 0x020D5224
	cmp r0, #0x0
	bne _020D524C
	ldr r5, _020D5268 ; =0x00996A00
	mov r4, #0x1
_020D5234:
	mov r0, r5
	bl OS_SpinWait
	mov r0, r4
	bl PM_SetLCDPower
_020D5244: ; 0x020D5244
	cmp r0, #0x0
	beq _020D5234
_020D524C:
	mov r1, r7
	mov r2, r6
	mov r0, #0xe
	bl PM_SendUtilityCommandAsync
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D5268: .word 0x00996A00

	arm_func_start PM_SetBackLight
PM_SetBackLight: ; 0x020D526C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020D52A4 ; =PMi_DummyCallback
	add r3, sp, #0x0
	bl PM_SetBackLightAsync
_020D5280: ; 0x020D5280
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
_020D5294: ; 0x020D5294
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D52A4: .word PMi_DummyCallback

	arm_func_start PM_SetBackLightAsync
PM_SetBackLightAsync:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	mov r12, #0x0
	bne _020D52D0
	cmp r1, #0x1
	moveq r12, #0x6
	cmp r1, #0x0
	moveq r12, #0x7
	b _020D5304
_020D52D0:
	cmp r0, #0x1
	bne _020D52EC
	cmp r1, #0x1
	moveq r12, #0x4
	cmp r1, #0x0
	moveq r12, #0x5
	b _020D5304
_020D52EC:
	cmp r0, #0x2
	bne _020D5304
	cmp r1, #0x1
	moveq r12, #0x8
	cmp r1, #0x0
	moveq r12, #0x9
_020D5304:
	cmp r12, #0x0
	addeq sp, sp, #0x4
	ldreq r0, _020D5334 ; =0x0000FFFF
	ldmeqia sp!, {lr}
	bxeq lr
	mov r1, r2
	mov r0, r12
	mov r2, r3
	bl PM_SendUtilityCommandAsync
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D5334: .word 0x0000FFFF

	arm_func_start PMi_SetLED
PMi_SetLED: ; 0x020D5338
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D5370 ; =PMi_DummyCallback
	add r2, sp, #0x0
	bl PMi_SetLEDAsync
_020D534C: ; 0x020D534C
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
_020D5360: ; 0x020D5360
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D5370: .word PMi_DummyCallback

	arm_func_start PMi_SetLEDAsync
PMi_SetLEDAsync:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x1
	beq _020D5398
	cmp r0, #0x2
	beq _020D53A8
	cmp r0, #0x3
	beq _020D53A0
	b _020D53B0
_020D5398:
	mov r0, #0x1
	b _020D53B4
_020D53A0:
	mov r0, #0x2
	b _020D53B4
_020D53A8:
	mov r0, #0x3
	b _020D53B4
_020D53B0:
	mov r0, #0x0
_020D53B4:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldreq r0, _020D53D8 ; =0x0000FFFF
	ldmeqia sp!, {lr}
	bxeq lr
	bl PM_SendUtilityCommandAsync
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D53D8: .word 0x0000FFFF

	arm_func_start PMi_WriteRegister
PMi_WriteRegister: ; 0x020D53DC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020D5414 ; =PMi_DummyCallback
	add r3, sp, #0x0
	bl PMi_WriteRegisterAsync
_020D53F0: ; 0x020D53F0
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
_020D5404: ; 0x020D5404
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D5414: .word PMi_DummyCallback

	arm_func_start PMi_WriteRegisterAsync
PMi_WriteRegisterAsync:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r4, r1
	mov r6, r2
	mov r5, r3
	bl PMi_Lock
_020D5434: ; 0x020D5434
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _020D5488 ; =0x02006400
	ldr r1, _020D548C ; =UNK_021D54E4
	and r2, r7, #0xff
	orr r0, r2, r0
	str r6, [r1, #0x4]
	str r5, [r1, #0x8]
	bl PMi_SendPxiData
	ldr r0, _020D5490 ; =0x0000FFFF
	ldr r1, _020D5494 ; =0x01010000
	and r0, r4, r0
	orr r0, r0, r1
	bl PMi_SendPxiData
_020D5478: ; 0x020D5478
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D5488: .word 0x02006400
_020D548C: .word UNK_021D54E4
_020D5490: .word 0x0000FFFF
_020D5494: .word 0x01010000

	arm_func_start PMi_ReadRegister
PMi_ReadRegister:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020D54D0 ; =PMi_DummyCallback
	add r3, sp, #0x0
	bl PMi_ReadRegisterAsync
_020D54AC: ; 0x020D54AC
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	bl PMi_WaitBusy
_020D54C0: ; 0x020D54C0
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D54D0: .word PMi_DummyCallback

	arm_func_start PMi_ReadRegisterAsync
PMi_ReadRegisterAsync:
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl PMi_Lock
_020D54EC: ; 0x020D54EC
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr ip, _020D553C ; =UNK_021D550C
	ldr r1, _020D5540 ; =UNK_021D54E4
	ldr r0, _020D5544 ; =0x03006500
	and r2, r7, #0xff
	mov lr, r7, lsl #0x3
	mov r8, #0x0
	ldr r3, _020D5548 ; =UNK_021D5510
	strh r8, [r12, lr]
	orr r0, r2, r0
	str r5, [r1, #0x4]
	str r4, [r1, #0x8]
	str r6, [r3, r7, lsl #0x3]
	bl PMi_SendPxiData
	mov r0, r8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D553C: .word UNK_021D550C
_020D5540: .word UNK_021D54E4
_020D5544: .word 0x03006500
_020D5548: .word UNK_021D5510

	arm_func_start PM_SendUtilityCommandAsync
PM_SendUtilityCommandAsync: ; 0x020D554C
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	mov r6, r1
	mov r5, r2
	bl PMi_Lock
_020D5560: ; 0x020D5560
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	mov r2, r4, lsr #0x10
	ldr r1, _020D55B0 ; =UNK_021D54E4
	ldr r0, _020D55B4 ; =0x02006300
	and r2, r2, #0xff
	orr r0, r2, r0
	str r6, [r1, #0x4]
	str r5, [r1, #0x8]
	bl PMi_SendPxiData
	ldr r0, _020D55B8 ; =0x0000FFFF
	ldr r1, _020D55BC ; =0x01010000
	and r0, r4, r0
	orr r0, r0, r1
	bl PMi_SendPxiData
_020D55A4: ; 0x020D55A4
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D55B0: .word UNK_021D54E4
_020D55B4: .word 0x02006300
_020D55B8: .word 0x0000FFFF
_020D55BC: .word 0x01010000

	arm_func_start PMi_SendSleepStart
PMi_SendSleepStart: ; 0x020D55C0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl PMi_Lock
_020D55D4: ; 0x020D55D4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, _020D5660 ; =UNK_021D54D0
	mov r2, #0x0
	ldr r0, _020D5664 ; =0x03006000
	str r2, [r1, #0x0]
	bl PMi_SendPxiData
	ldr r1, _020D5660 ; =UNK_021D54D0
_020D5600:
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _020D5600
	mov r0, #0x0
	ldr ip, _020D5668 ; =UNK_021D54D4
	str r0, [r1, #0x0]
	mov r2, r0
	mov r3, r0
	mov r1, #0x2
	str r0, [r12, #0x0]
	bl PMi_SetLCDPower
	ldr r0, _020D566C ; =0x02006100
	and r1, r5, #0xff
	orr r0, r1, r0
	bl PMi_SendPxiData
	ldr r0, _020D5670 ; =0x0000FFFF
	ldr r1, _020D5674 ; =0x01010000
	and r0, r4, r0
	orr r0, r0, r1
	bl PMi_SendPxiData
_020D5650: ; 0x020D5650
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D5660: .word UNK_021D54D0
_020D5664: .word 0x03006000
_020D5668: .word UNK_021D54D4
_020D566C: .word 0x02006100
_020D5670: .word 0x0000FFFF
_020D5674: .word 0x01010000

	arm_func_start PMi_CommonCallback
PMi_CommonCallback: ; 0x020D5678
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	beq _020D569C
	mov r0, #0x2
	bl PMi_CallCallbackAndUnlock
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020D569C:
	and r0, r1, #0x7f00
	mov r0, r0, lsl #0x8
	and r1, r1, #0xff
	mov r2, r0, lsr #0x10
	mov r0, r1, lsl #0x10
	cmp r2, #0x70
	mov r0, r0, lsr #0x10
	blo _020D56FC
	cmp r2, #0x74
	bhi _020D56FC
	ldr r1, _020D5750 ; =UNK_021D5510
	sub r2, r2, #0x70
	and r0, r0, #0xff
	ldr r1, [r1, r2, lsl #0x3]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r1, #0x0
	strneh r0, [r1, #0x0]
	mov r1, r2, lsl #0x3
	ldr r0, _020D5754 ; =UNK_021D550C
	mov r2, #0x1
	strh r2, [r0, r1]
	mov r0, #0x0
	b _020D5740
_020D56FC:
	cmp r2, #0x60
	ldreq r1, _020D5758 ; =UNK_021D54D0
	moveq r2, #0x1
	streq r2, [r1, #0x0]
	beq _020D5740
	cmp r2, #0x62
	ldreq r1, _020D575C ; =UNK_021D54D4
	moveq r2, #0x1
	streq r2, [r1, #0x0]
	beq _020D5740
	cmp r2, #0x67
	bne _020D5740
	ldr r1, _020D5760 ; =UNK_021D54E4
	ldr r1, [r1, #0xc]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
_020D5740:
	bl PMi_CallCallbackAndUnlock
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D5750: .word UNK_021D5510
_020D5754: .word UNK_021D550C
_020D5758: .word UNK_021D54D0
_020D575C: .word UNK_021D54D4
_020D5760: .word UNK_021D54E4

	arm_func_start PM_Init
PM_Init: ; 0x020D5764
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D580C ; =UNK_021D54CC
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, _020D5810 ; =UNK_021D54E4
	mov r2, #0x0
	mov r3, #0x1
	strh r3, [r1, #0x0]
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	bl PXI_Init
	mov r5, #0x8
	mov r4, #0x1
_020D57A8:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020D57B4: ; 0x020D57B4
	cmp r0, #0x0
	beq _020D57A8
	ldr r1, _020D5814 ; =PMi_CommonCallback
	mov r0, #0x8
	bl PXI_SetFifoRecvCallback
	mov r3, #0x0
	ldr r0, _020D5818 ; =UNK_021D550C
	mov r2, r3
_020D57D4:
	mov r1, r3, lsl #0x3
	add r3, r3, #0x1
	strh r2, [r0, r1]
	cmp r3, #0x5
	blt _020D57D4
	ldr r0, _020D581C ; =UNK_021D54F4
	bl OS_InitMutex
	ldr r1, _020D5820 ; =0x027FFC3C
	ldr r0, _020D5824 ; =UNK_021D54DC
	ldr r1, [r1, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D580C: .word UNK_021D54CC
_020D5810: .word UNK_021D54E4
_020D5814: .word PMi_CommonCallback
_020D5818: .word UNK_021D550C
_020D581C: .word UNK_021D54F4
_020D5820: .word 0x027FFC3C
_020D5824: .word UNK_021D54DC

	arm_func_start PMi_CallCallbackAndUnlock
PMi_CallCallbackAndUnlock: ; 0x020D5828
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020D5878 ; =UNK_021D54E4
	ldr r1, [r2, #0x0]
	ldr r12, [r2, #0x4]
	cmp r1, #0x0
	movne r3, #0x0
	strne r3, [r2, #0x0]
	cmp r12, #0x0
	addeq sp, sp, #0x4
	ldr r1, [r2, #0x8]
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r2, _020D5878 ; =UNK_021D54E4
	mov r3, #0x0
	str r3, [r2, #0x4]
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D5878: .word UNK_021D54E4

	arm_func_start PMi_DummyCallback
PMi_DummyCallback: ; 0x020D587C
	str r0, [r1, #0x0]
	bx lr

	arm_func_start PMi_WaitBusy
PMi_WaitBusy:
	stmdb sp!, {r4,lr}
	ldr r4, _020D58C0 ; =UNK_021D54E4
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020D589C:
	bl OS_GetCpsrIrq
	cmp r0, #0x80
	bne _020D58AC
	bl PXIi_HandlerRecvFifoNotEmpty
_020D58AC:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020D589C
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D58C0: .word UNK_021D54E4

	arm_func_start PMi_Lock
PMi_Lock:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020D5910 ; =UNK_021D54E4
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020D58F4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020D58F4:
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D5910: .word UNK_021D54E4
