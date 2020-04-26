	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	arm_func_start TP_CheckError
TP_CheckError: ; 0x020D36C4
	ldr r1, _020D36D4 ; =0x021D5474
	ldrh r1, [r1, #0x34]
	and r0, r1, r0
	bx lr
	.balign 4
_020D36D4: .word 0x021D5474

	arm_func_start TP_WaitBusy
TP_WaitBusy: ; 0x020D36D8
	ldr r1, _020D36EC ; =0x021D5474
_020D36DC:
	ldrh r2, [r1, #0x36]
	ands r2, r2, r0
	bne _020D36DC
	bx lr
	.balign 4
_020D36EC: .word 0x021D5474

	arm_func_start TP_GetCalibratedPoint
TP_GetCalibratedPoint: ; 0x020D36F0
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020D3818 ; =0x021D5474
	ldrh r2, [r2, #0x30]
	cmp r2, #0x0
	bne _020D372C
	ldrh r3, [r1, #0x0]
	ldrh r2, [r1, #0x2]
	strh r3, [r0, #0x0]
	strh r2, [r0, #0x2]
	ldrh r2, [r1, #0x4]
	ldrh r1, [r1, #0x6]
	strh r2, [r0, #0x4]
	strh r1, [r0, #0x6]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D372C:
	ldrh r3, [r1, #0x4]
	ldr r2, _020D381C ; =0x021D548C
	strh r3, [r0, #0x4]
	ldrh r3, [r1, #0x6]
	strh r3, [r0, #0x6]
	ldrh r3, [r1, #0x4]
	cmp r3, #0x0
	moveq r1, #0x0
	streqh r1, [r0, #0x0]
	streqh r1, [r0, #0x2]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r4, [r1, #0x0]
	ldr r3, [r2, #0x0]
	ldr lr, [r2, #0x8]
	mov r12, r4, lsl #0x2
	mov r4, r12, asr #0x1f
	subs r12, r12, r3
	sbc r3, r4, r3, asr #0x1f
	umull r6, r5, lr, r12
	mla r5, lr, r3, r5
	mov r3, lr, asr #0x1f
	mla r5, r3, r12, r5
	mov r3, r6, lsr #0x16
	orr r3, r3, r5, lsl #0xa
	strh r3, [r0, #0x0]
	ldrsh r3, [r0, #0x0]
	cmp r3, #0x0
	movlt r3, #0x0
	strlth r3, [r0, #0x0]
	blt _020D37B4
	cmp r3, #0xff
	movgt r3, #0xff
	strgth r3, [r0, #0x0]
_020D37B4:
	ldrh r3, [r1, #0x2]
	ldr r1, [r2, #0xc]
	ldr r12, [r2, #0x14]
	mov r3, r3, lsl #0x2
	mov r2, r3, asr #0x1f
	subs r3, r3, r1
	sbc r1, r2, r1, asr #0x1f
	umull r4, lr, r12, r3
	mla lr, r12, r1, lr
	mov r1, r12, asr #0x1f
	mla lr, r1, r3, lr
	mov r1, r4, lsr #0x16
	orr r1, r1, lr, lsl #0xa
	strh r1, [r0, #0x2]
	ldrsh r1, [r0, #0x2]
	cmp r1, #0x0
	movlt r1, #0x0
	strlth r1, [r0, #0x2]
	ldmltia sp!, {r4-r6,lr}
	bxlt lr
	cmp r1, #0xbf
	movgt r1, #0xbf
	strgth r1, [r0, #0x2]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D3818: .word 0x021D5474
_020D381C: .word 0x021D548C

	arm_func_start TP_CalcCalibrateParam
TP_CalcCalibrateParam:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r5, r2
	mov r4, r3
	cmp r6, #0x1000
	bhs _020D3860
	cmp r5, #0x1000
	bhs _020D3860
	ldrh r8, [sp, #0x2c]
	cmp r8, #0x1000
	bhs _020D3860
	ldrh r3, [sp, #0x30]
	cmp r3, #0x1000
	blo _020D3870
_020D3860:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3870:
	cmp r4, #0x100
	bhs _020D389C
	ldrh r2, [sp, #0x34]
	cmp r2, #0x100
	bhs _020D389C
	ldrh r1, [sp, #0x28]
	cmp r1, #0xc0
	bhs _020D389C
	ldrh r0, [sp, #0x38]
	cmp r0, #0xc0
	blo _020D38AC
_020D389C:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D38AC:
	cmp r4, r2
	beq _020D38CC
	cmp r1, r0
	beq _020D38CC
	cmp r6, r8
	beq _020D38CC
	cmp r5, r3
	bne _020D38DC
_020D38CC:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D38DC:
	bl OS_DisableInterrupts
	ldrh r1, [sp, #0x2c]
	ldr r3, _020D3A80 ; =0x04000280
	ldr fp, _020D3A84 ; =0x04000290
	str r1, [sp, #0x0]
	ldr r2, [sp, #0x0]
	ldrh r1, [sp, #0x34]
	sub r9, r6, r2
	mov r2, #0x0
	mov r12, r9, lsl #0x8
	strh r2, [r3, #0x0]
	str r12, [r11, #0x0]
	ldrh r8, [sp, #0x30]
	ldrh r10, [sp, #0x38]
	ldrh r9, [sp, #0x28]
	ldr fp, _020D3A88 ; =0x04000298
	sub r12, r4, r1
	str r12, [r11, #0x0]
	str r2, [r11, #0x4]
	sub r11, r5, r8
	sub r2, r9, r10
_020D3930:
	ldrh r12, [r3, #0x0]
	ands r12, r12, #0x8000
	bne _020D3930
	ldr ip, _020D3A8C ; =0x040002A0
	mov r11, r11, lsl #0x8
	ldr lr, [r12, #0x0]
	mov r12, #0x0
	strh r12, [r3, #0x0]
	ldr r3, _020D3A84 ; =0x04000290
	cmp lr, #0x8000
	str r11, [r3, #0x0]
	ldr r3, _020D3A88 ; =0x04000298
	str r2, [r3, #0x0]
	mov r2, r3
	str r12, [r2, #0x4]
	bge _020D3980
	mov r2, #0x8000
	rsb r2, r2, #0x0
	cmp lr, r2
	bge _020D3994
_020D3980:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3994:
	strh lr, [r7, #0x4]
	ldrsh r11, [r7, #0x4]
	add r3, r4, r1
	ldr r1, [sp, #0x0]
	add r4, r6, r1
	mul r1, r11, r3
	mov r3, r4, lsl #0x8
	sub r1, r3, r1
	mov r1, r1, lsl #0x9
	mov r1, r1, asr #0x10
	cmp r1, #0x8000
	bge _020D39CC
	cmp r1, r2
	bge _020D39E0
_020D39CC:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D39E0:
	ldr r2, _020D3A80 ; =0x04000280
	strh r1, [r7, #0x0]
_020D39E8:
	ldrh r1, [r2, #0x0]
	ands r1, r1, #0x8000
	bne _020D39E8
	ldr r1, _020D3A8C ; =0x040002A0
	ldr r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	cmp r4, #0x8000
	bge _020D3A18
	mov r0, #0x8000
	rsb r1, r0, #0x0
	cmp r4, r1
	bge _020D3A28
_020D3A18:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3A28:
	strh r4, [r7, #0x6]
	ldrsh r2, [r7, #0x6]
	add r0, r9, r10
	add r3, r5, r8
	mul r0, r2, r0
	mov r2, r3, lsl #0x8
	sub r0, r2, r0
	mov r0, r0, lsl #0x9
	mov r0, r0, asr #0x10
	cmp r0, #0x8000
	bge _020D3A5C
	cmp r0, r1
	bge _020D3A6C
_020D3A5C:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3A6C:
	strh r0, [r7, #0x2]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D3A80: .word 0x04000280
_020D3A84: .word 0x04000290
_020D3A88: .word 0x04000298
_020D3A8C: .word 0x040002A0

	arm_func_start TP_GetLatestIndexInAuto
TP_GetLatestIndexInAuto: ; 0x020D3A90
	ldr r0, _020D3A9C ; =0x021D5474
	ldrh r0, [r0, #0xc]
	bx lr
	.balign 4
_020D3A9C: .word 0x021D5474

	arm_func_start TP_GetLatestRawPointInAuto
TP_GetLatestRawPointInAuto: ; 0x020D3AA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r1, #0x3
	ldr lr, _020D3C10 ; =0x021D5474
	strh r1, [r0, #0x6]
	ldrh r1, [lr, #0xe]
	ldrh r3, [lr, #0xc]
	cmp r1, #0x1
	beq _020D3AD0
	ldrh r1, [lr, #0x14]
	cmp r1, #0x1
	bne _020D3B0C
_020D3AD0:
	ldr r1, _020D3C10 ; =0x021D5474
	mov r2, r3, lsl #0x3
	ldr r1, [r1, #0x10]
	add sp, sp, #0x4
	add r3, r1, r3, lsl #0x3
	ldrh r2, [r1, r2]
	ldrh r1, [r3, #0x2]
	strh r2, [r0, #0x0]
	strh r1, [r0, #0x2]
	ldrh r2, [r3, #0x4]
	ldrh r1, [r3, #0x6]
	strh r2, [r0, #0x4]
	strh r1, [r0, #0x6]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D3B0C:
	add r1, r0, #0x6
	mov r12, #0x0
	b _020D3BE0
_020D3B18:
	subs r5, r3, r12
	ldr r2, [lr, #0x10]
	addmi r5, r5, r4
	add r2, r2, r5, lsl #0x3
	ldrh r4, [r2, #0x4]
	cmp r4, #0x0
	bne _020D3B60
	ldrh r3, [r2, #0x0]
	ldrh r1, [r2, #0x2]
	add sp, sp, #0x4
	strh r3, [r0, #0x0]
	strh r1, [r0, #0x2]
	ldrh r3, [r2, #0x4]
	ldrh r1, [r2, #0x6]
	strh r3, [r0, #0x4]
	strh r1, [r0, #0x6]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D3B60:
	ldrh r4, [r0, #0x6]
	ands r4, r4, #0x1
	beq _020D3B90
	ldrh r4, [r2, #0x6]
	ands r4, r4, #0x1
	bne _020D3B90
	ldrh r4, [r2, #0x0]
	cmp r12, #0x0
	strh r4, [r0, #0x0]
	ldrneh r4, [r1, #0x0]
	bicne r4, r4, #0x1
	strneh r4, [r1, #0x0]
_020D3B90:
	ldrh r4, [r0, #0x6]
	ands r4, r4, #0x2
	beq _020D3BC0
	ldrh r4, [r2, #0x6]
	ands r4, r4, #0x2
	bne _020D3BC0
	ldrh r2, [r2, #0x2]
	cmp r12, #0x0
	strh r2, [r0, #0x2]
	ldrneh r2, [r1, #0x0]
	bicne r2, r2, #0x2
	strneh r2, [r1, #0x0]
_020D3BC0:
	ldrh r2, [r0, #0x6]
	cmp r2, #0x0
	moveq r1, #0x1
	streqh r1, [r0, #0x4]
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	add r12, r12, #0x1
_020D3BE0:
	ldrh r2, [lr, #0xe]
	cmp r12, r2
	bge _020D3BFC
	ldrh r4, [lr, #0x14]
	sub r2, r4, #0x1
	cmp r12, r2
	blt _020D3B18
_020D3BFC:
	mov r1, #0x1
	strh r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D3C10: .word 0x021D5474

	arm_func_start TP_RequestAutoSamplingStopAsync
TP_RequestAutoSamplingStopAsync: ; 0x020D3C14
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r1, _020D3CB0 ; =0x03000200
	mov r0, #0x6
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D3C30:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	cmp r0, #0x0
	bne _020D3C84
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _020D3CB4
	ldrh r1, [r0, #0x34]
	ldr r3, [r0]
	orr r1, r1, #0x4
	strh r1, [r0, #0x34]
	cmp r3, #0x0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	mov r0, #0x2
	mov r1, #0x4
	mov r2, #0x0
	blx r3
	ldmia sp!, {r4, lr}
	bx lr
_020D3C84:
	ldr r1, _020D3CB4
	mov r0, r4
	ldrh r2, [r1, #0x36]
	orr r2, r2, #0x4
	strh r2, [r1, #0x36]
	ldrh r2, [r1, #0x34]
	bic r2, r2, #0x4
	strh r2, [r1, #0x34]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, lr}
	bx lr
_020D3CB0: .word 0x03000200
_020D3CB4: .word 0x021D5474

	arm_func_start TP_RequestAutoSamplingStartAsync
TP_RequestAutoSamplingStartAsync: ; 0x020D3CB8
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020D3DC0 ; =0x021D5474
	mov r5, r1
	mov r12, #0x0
	mov r6, r0
	str r2, [r4, #0x10]
	strh r12, [r4, #0xc]
	strh r5, [r4, #0xe]
	strh r3, [r4, #0x14]
	cmp r3, #0x0
	bls _020D3D00
	mov r1, r12
_020D3CE8:
	ldr r0, [r4, #0x10]
	add r0, r0, r12, lsl #0x3
	add r12, r12, #0x1
	strh r1, [r0, #0x4]
	cmp r12, r3
	blo _020D3CE8
_020D3D00:
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _020D3DC4 ; =0x02000100
	and r1, r5, #0xff
	orr r1, r1, r0
	mov r0, #0x6
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D3D20:
	cmp r0, #0x0
	movlt r0, #0x0
	blt _020D3D4C
	ldr r1, _020D3DC8
	mov r0, #0x6
	orr r1, r6, r1
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	movge r0, #0x1
_020D3D4C:
	ands r0, r0, #0xFF
	bne _020D3D94
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _020D3DC0
	ldrh r1, [r0, #0x34]
	ldr r3, [r0]
	orr r1, r1, #0x2
	strh r1, [r0, #0x34]
	cmp r3, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, #0x1
	mov r1, #0x4
	mov r2, #0x0
	blx r3
	ldmia sp!, {r4-r6, lr}
	bx lr
_020D3D94:
	ldr r1, _020D3DC0
	mov r0, r4
	ldrh r2, [r1, #0x36]
	orr r2, r2, #0x2
	strh r2, [r1, #0x36]
	ldrh r2, [r1, #0x34]
	bic r2, r2, #0x2
	strh r2, [r1, #0x34]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6, lr}
	bx lr
_020D3DC0: .word 0x021D5474
_020D3DC4: .word 0x02000100
_020D3DC8: .word 0x01010000

	arm_func_start TP_WaitRawResult
TP_WaitRawResult: ; 0x020D3DCC
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	bl TP_WaitBusy
	ldr r1, _020D3E20 ; =0x021D5474
	ldrh r0, [r1, #0x34]
	ands r0, r0, #0x1
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrh r3, [r1, #0x4]
	ldrh r2, [r1, #0x6]
	mov r0, #0x0
	strh r3, [r4, #0x0]
	strh r2, [r4, #0x2]
	ldrh r2, [r1, #0x8]
	ldrh r1, [r1, #0xa]
	strh r2, [r4, #0x4]
	strh r1, [r4, #0x6]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D3E20: .word 0x021D5474

	arm_func_start TP_RequestSamplingAsync
TP_RequestSamplingAsync: ; 0x020D3E24
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, #0x6
	mov r1, #0x3000000
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D3E40:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	cmp r0, #0x0
	bne _020D3E94
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _20D3EC0
	ldrh r1, [r0, #0x34]
	ldr r3, [r0]
	orr r1, r1, #0x1
	strh r1, [r0, #0x34]
	cmp r3, #0x0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	mov r0, #0x0
	mov r2, r0
	mov r1, #0x4
	blx r3
	ldmia sp!, {r4, lr}
	bx lr
_020D3E94:
	ldr r1, _20D3EC0
	mov r0, r4
	ldrh r2, [r1, #0x36]
	orr r2, r2, #0x1
	strh r2, [r1, #0x36]
	ldrh r2, [r1, #0x34]
	bic r2, r2, #0x1
	strh r2, [r1, #0x34]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, lr}
	bx lr
_20D3EC0: .word 0x021D5474

	arm_func_start TP_SetCalibrateParam
TP_SetCalibrateParam: ; 0x020D3EC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r0
	ldreq r0, _020D3FF8 ; =0x021D5474
	moveq r1, #0x0
	streqh r1, [r0, #0x30]
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldrsh lr, [r4, #0x4]
	cmp lr, #0x0
	beq _020D3F50
	ldr r5, _020D3FFC ; =0x04000280
	mov r12, #0x0
	ldr r2, _020D4000 ; =0x04000290
	strh r12, [r5, #0x0]
	mov r3, #0x10000000
	ldr r1, _020D4004 ; =0x04000298
	str r3, [r2, #0x0]
	str lr, [r1, #0x0]
	str r12, [r1, #0x4]
	ldrsh r2, [r4, #0x0]
	ldr r1, _020D3FF8 ; =0x021D5474
	str r2, [r1, #0x18]
	ldrsh r2, [r4, #0x4]
	str r2, [r1, #0x1c]
_020D3F30:
	ldrh r1, [r5, #0x0]
	ands r1, r1, #0x8000
	bne _020D3F30
	ldr r2, _020D4008 ; =0x040002A0
	ldr r1, _020D3FF8 ; =0x021D5474
	ldr r2, [r2, #0x0]
	str r2, [r1, #0x20]
	b _020D3F64
_020D3F50:
	ldr r1, _020D3FF8 ; =0x021D5474
	mov r2, #0x0
	str r2, [r1, #0x18]
	str r2, [r1, #0x1c]
	str r2, [r1, #0x20]
_020D3F64:
	ldrsh r5, [r4, #0x6]
	cmp r5, #0x0
	beq _020D3FC8
	ldr ip, _020D3FFC ; =0x04000280
	mov lr, #0x0
	ldr r2, _020D4000 ; =0x04000290
	strh lr, [r12, #0x0]
	mov r3, #0x10000000
	ldr r1, _020D4004 ; =0x04000298
	str r3, [r2, #0x0]
	str r5, [r1, #0x0]
	str lr, [r1, #0x4]
	ldrsh r2, [r4, #0x2]
	ldr r1, _020D3FF8 ; =0x021D5474
	str r2, [r1, #0x24]
	ldrsh r2, [r4, #0x6]
	str r2, [r1, #0x28]
_020D3FA8:
	ldrh r1, [r12, #0x0]
	ands r1, r1, #0x8000
	bne _020D3FA8
	ldr r2, _020D4008 ; =0x040002A0
	ldr r1, _020D3FF8 ; =0x021D5474
	ldr r2, [r2, #0x0]
	str r2, [r1, #0x2c]
	b _020D3FDC
_020D3FC8:
	ldr r1, _020D3FF8 ; =0x021D5474
	mov r2, #0x0
	str r2, [r1, #0x24]
	str r2, [r1, #0x28]
	str r2, [r1, #0x2c]
_020D3FDC:
	bl OS_RestoreInterrupts
	ldr r0, _020D3FF8 ; =0x021D5474
	mov r1, #0x1
	strh r1, [r0, #0x30]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D3FF8: .word 0x021D5474
_020D3FFC: .word 0x04000280
_020D4000: .word 0x04000290
_020D4004: .word 0x04000298
_020D4008: .word 0x040002A0

	arm_func_start TP_GetUserInfo
TP_GetUserInfo: ; 0x020D400C
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x18
	ldr ip, _020D40B4 ; =0x027FFC80
	mov r4, r0
	ldrh r1, [r12, #0x58]
	ldrh r2, [r12, #0x5a]
	ldrb r3, [r12, #0x5c]
	cmp r1, #0x0
	ldrb lr, [r12, #0x5d]
	ldrh r6, [r12, #0x5e]
	ldrh r5, [r12, #0x60]
	ldrb r0, [r12, #0x62]
	ldrb r12, [r12, #0x63]
	bne _020D405C
	cmp r6, #0x0
	bne _020D405C
	cmp r2, #0x0
	bne _020D405C
	cmp r5, #0x0
	beq _020D4080
_020D405C:
	str lr, [sp, #0x0]
	str r6, [sp, #0x4]
	str r5, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, r4
	str r12, [sp, #0x10]
	bl TP_CalcCalibrateParam
_020D4078:
	cmp r0, #0
	beq _020D40A4
_020D4080:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	strh r0, [r4, #0x2]
	strh r0, [r4, #0x4]
	strh r0, [r4, #0x6]
	add sp, sp, #0x18
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D40A4:
	mov r0, #0x1
	add sp, sp, #0x18
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D40B4: .word 0x027FFC80

	arm_func_start TP_Init
TP_Init: ; 0x020D40B8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020D413C ; =0x021D5470
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, #0x1
	strh r1, [r0, #0x0]
	bl PXI_Init
	ldr r0, _020D4140 ; =0x021D5474
	mov r1, #0x0
	strh r1, [r0, #0x32]
	strh r1, [r0, #0x36]
	strh r1, [r0, #0xc]
	str r1, [r0, #0x0]
	str r1, [r0, #0x10]
	strh r1, [r0, #0x30]
	strh r1, [r0, #0x34]
	mov r5, #0x6
	mov r4, #0x1
_020D4110:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020D411C:
	cmp r0, #0x0
	beq _020D4110
	ldr r1, _020D4144
	mov r0, #0x6
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D413C: .word 0x021D5470 ; initial$7594
_020D4140: .word 0x021D5474 ; tpState
_020D4144: .word TPi_TpCallback

	arm_func_start TPi_TpCallback
TPi_TpCallback: ; 0x020D4148
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r0, r1, lsl #0x10
	mov r3, r0, lsr #0x10
	and r0, r3, #0x7f00
	mov r0, r0, lsl #0x8
	cmp r2, #0x0
	mov r0, r0, lsr #0x10
	beq _020D41AC
	ldr r1, _020D43FC ; =0x021D5474
	mov r2, #0x1
	ldrh r4, [r1, #0x34]
	ldr r3, [r1, #0x0]
	orr r2, r4, r2, lsl r0
	cmp r3, #0x0
	strh r2, [r1, #0x34]
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r1, #0x4
	mov r2, #0x0
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020D41AC:
	cmp r0, #0x10
	bne _020D427C
	ldr r1, _020D43FC ; =0x021D5474
	ldrh r3, [r1, #0xc]
	ldrh r2, [r1, #0x14]
	add r3, r3, #0x1
	strh r3, [r1, #0xc]
	ldrh r3, [r1, #0xc]
	cmp r3, r2
	movcs r2, #0x0
	strcsh r2, [r1, #0xc]
	ldr r1, _020D4400 ; =0x027FFFAA
	ldr r2, _020D43FC ; =0x021D5474
	ldrh r3, [r1, #0x0]
	ldr r1, _020D4404 ; =0x027FFFAC
	ldrh r12, [r2, #0xc]
	strh r3, [sp, #0x0]
	ldrh r1, [r1, #0x0]
	ldr r4, [r2, #0x10]
	mov lr, r12, lsl #0x3
	strh r1, [sp, #0x2]
	ldr r3, [sp, #0x0]
	add r1, r4, r12, lsl #0x3
	mov r3, r3, lsl #0x14
	mov r3, r3, lsr #0x14
	strh r3, [r4, lr]
	ldr r3, [sp, #0x0]
	mov r3, r3, lsl #0x8
	mov r3, r3, lsr #0x14
	strh r3, [r1, #0x2]
	ldr r3, [sp, #0x0]
	mov r3, r3, lsl #0x7
	mov r3, r3, lsr #0x1f
	and r3, r3, #0xff
	strh r3, [r1, #0x4]
	ldr r3, [sp, #0x0]
	mov r3, r3, lsl #0x5
	mov r3, r3, lsr #0x1e
	and r3, r3, #0xff
	strh r3, [r1, #0x6]
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrh r2, [r2, #0xc]
	mov r1, #0x0
	and r2, r2, #0xff
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020D427C:
	ands r1, r1, #0x1000000
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	and r1, r3, #0xff
	cmp r1, #0x4
	addls pc, pc, r1, lsl #0x2
	b _020D43EC
_020D429C:
	b _020D42B0
	b _020D43EC
	b _020D4390
	b _020D4398
	b _020D4388
_020D42B0:
	cmp r0, #0x0
	beq _020D42D4
	cmp r0, #0x1
	beq _020D4338
	cmp r0, #0x2
	ldreq r1, _020D43FC
	moveq r2, #0x0
	streqh r2, [r1, #0x32]
	b _020D4344
_020D42D4:
	ldr r1, _020D4400
	ldr r3, _020D4404
	ldrh ip, [r1]
	ldr r1, _020D43FC
	mov r2, #0x0
	strh ip, [sp, #0x4]
	ldrh r3, [r3]
	strh r3, [sp, #0x6]
	ldr ip, [sp, #0x4]
	strh r2, [r1, #0x32]
	mov r3, ip, lsl #0x7
	mov r2, ip, lsl #0x5
	mov lr, ip, lsl #0x14
	mov ip, ip, lsl #0x8
	mov r3, r3, lsr #0x1F
	mov r2, r2, lsr #0x1E
	mov lr, lr, lsr #0x14
	mov ip, ip, lsr #0x14
	and r3, r3, #0xFF
	and r2, r2, #0xFF
	strh lr, [r1, #0x4]
	strh ip, [r1, #0x6]
	strh r3, [r1, #0x8]
	strh r2, [r1, #0xA]
	b _020D4344
_020D4338:
	ldr r1, _020D43FC
	mov r2, #0x2
	strh r2, [r1, #0x32]
_020D4344:
	ldr r1, _020D43FC
	mov r2, #0x1
	ldrh ip, [r1, #0x36]
	mvn r2, r2, lsl r0
	ldr r3, [r1]
	and r2, ip, r2
	cmp r3, #0x0
	strh r2, [r1, #0x36]
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4, lr}
	bxeq lr
	mov r1, #0x0
	mov r2, r1
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4, lr}
	bx lr
_020D4388:
	mov r4, #0x3
	b _020D439C
_020D4390:
	mov r4, #0x1
	b _020D439C
_020D4398:
	mov r4, #0x2
_020D439C:
	ldr r1, _020D43FC
	mov lr, #0x1
	ldrh ip, [r1, #0x34]
	ldr r3, [r1]
	mvn r2, lr, lsl r0
	orr ip, ip, lr, lsl r0
	strh ip, [r1, #0x34]
	ldrh ip, [r1, #0x36]
	cmp r3, #0x0
	addeq sp, sp, #0x8
	and r2, ip, r2
	strh r2, [r1, #0x36]
	ldmeqia sp!, {r4, lr}
	bxeq lr
	and r1, r4, #0xff
	mov r2, #0x0
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4, lr}
	bx lr
_020D43EC:
	bl OS_Terminate
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D43FC: .word 0x021D5474
_020D4400: .word 0x027FFFAA
_020D4404: .word 0x027FFFAC

	arm_func_start MicWaitBusy
MicWaitBusy: ; 0x020D4408
	ldr ip, _020D441C ; =0x021D54B0
_020D440C:
	ldr r0, [r12, #0x0]
	cmp r0, #0x1
	beq _020D440C
	bx lr
	.balign 4
_020D441C: .word 0x021D54B0

	arm_func_start MicGetResultCallback
MicGetResultCallback: ; 0x020D4420
	ldr r1, _020D442C ; =0x021D54B0
	str r0, [r1, #0xc]
	bx lr
	.balign 4
_020D442C: .word 0x021D54B0

	arm_func_start MicStopAutoSampling
MicStopAutoSampling:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4460 ; =0x03004200
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D4448:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	add sp, sp, #4
	ldmfd sp!, {lr}
	bx lr
_020D4460: .word 0x03004200

	arm_func_start MicStartAutoSampling
MicStartAutoSampling: ; 0x020D4464
	stmdb sp!, {r4-r6,lr}
	ldr ip, _020D4584 ; =0x02004100
	mov r6, r0
	mov r5, r1
	mov r4, r2
	orr r1, r3, r12
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D4488:
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	mov r0, r6, lsr #0x10
	orr r1, r0, #0x10000
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	ldr r1, _020D4588
	mov r0, #0x9
	and r1, r6, r1
	orr r1, r1, #0x20000
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	mov r0, r5, lsr #0x10
	orr r1, r0, #0x30000
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	ldr r1, _020D4588
	mov r0, #0x9
	and r1, r5, r1
	orr r1, r1, #0x40000
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	mov r0, r4, lsr #0x10
	orr r1, r0, #0x50000
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	ldr r0, _020D4588
	ldr r1, _020D458C
	and r0, r4, r0
	orr r1, r0, r1
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	ldmia sp!, {r4-r6, lr}
	bx lr
_020D4584: .word 0x02004100
_020D4588: .word 0x0000FFFF
_020D458C: .word 0x01060000

	arm_func_start MicDoSampling
MicDoSampling: ; 0x020D4590
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D45C4 ; =0x03004000
	mov r2, #0x0
	orr r1, r0, r1
	mov r0, #0x9
	bl PXI_SendWordByFifo
_020D45AC:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020D45C4: .word 0x03004000

	arm_func_start MicCommonCallback
MicCommonCallback: ; 0x020D45C8
	stmdb sp!, {r4,lr}
	mov r4, r1
	cmp r2, #0x0
	beq _020D4610
	ldr r0, _020D4700 ; =0x021D54B0
	ldr r2, _020D4700 ; =0x021D54B0
	ldr r1, [r0, #0x0]
	ldr r12, [r2, #0x4]
	cmp r1, #0x0
	movne r1, #0x0
	strne r1, [r0, #0x0]
	cmp r12, #0x0
	beq _020D4610
	ldr r1, [r2, #0x8]
	mov r3, #0x0
	mov r0, #0x6
	str r3, [r2, #0x4]
	blx r12
_020D4610:
	and r0, r4, #0xff
	mov r1, r0, lsl #0x10
	and r2, r4, #0x7f00
	mov r0, r2, lsl #0x8
	mov r1, r1, lsr #0x10
	cmp r1, #0x4
	mov r2, r0, lsr #0x10
	addls pc, pc, r1, lsl #0x2
	b _020D4670
_020D4634:
	b _020D4648
	b _020D4650
	b _020D4658
	b _020D4660
	b _020D4668
_020D4648:
	mov r0, #0x0
	b _020D4674
_020D4650:
	mov r0, #0x4
	b _020D4674
_020D4658:
	mov r0, #0x2
	b _020D4674
_020D4660:
	mov r0, #0x5
	b _020D4674
_020D4668:
	mov r0, #0x1
	b _020D4674
_020D4670:
	mov r0, #0x6
_020D4674:
	cmp r2, #0x51
	bne _020D46A0
	ldr r1, _020D4700 ; =0x021D54B0
	ldr r2, [r1, #0x10]
	cmp r2, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x14]
	blx r2
	ldmia sp!, {r4,lr}
	bx lr
_020D46A0:
	cmp r2, #0x40
	bne _020D46C0
	ldr r1, _020D4700 ; =0x021D54B0
	ldr r2, [r1, #0x18]
	cmp r2, #0x0
	ldrne r1, _020D4704 ; =0x027FFF94
	ldrneh r1, [r1, #0x0]
	strneh r1, [r2, #0x0]
_020D46C0:
	ldr r1, _020D4700 ; =0x021D54B0
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	movne r2, #0x0
	strne r2, [r1, #0x0]
	ldr r2, _020D4700 ; =0x021D54B0
	ldr r4, [r2, #0x4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r2, #0x8]
	mov r3, #0x0
	str r3, [r2, #0x4]
	blx r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D4700: .word 0x021D54B0
_020D4704: .word 0x027FFF94

	arm_func_start MIC_GetLastSamplingAddress
MIC_GetLastSamplingAddress: ; 0x020D4708
	ldr r0, _020D4714 ; =0x027FFF90
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D4714: .word 0x027FFF90

	arm_func_start MIC_StopAutoSampling
MIC_StopAutoSampling: ; 0x020D4718
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020D4754 ; =MicGetResultCallback
	mov r1, #0x0
	bl MIC_StopAutoSamplingAsync
	ldr r1, _020D4758 ; =0x021D54B0
	cmp r0, #0x0
	str r0, [r1, #0xc]
	bne _020D4740
	bl MicWaitBusy
_020D4740:
	ldr r0, _020D4758 ; =0x021D54B0
	ldr r0, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4754: .word MicGetResultCallback
_020D4758: .word 0x021D54B0

	arm_func_start MIC_StopAutoSamplingAsync
MIC_StopAutoSamplingAsync: ; 0x020D475C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl OS_DisableInterrupts
	ldr r1, _020D47C8 ; =0x021D54B0
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020D4794
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D4794:
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020D47C8 ; =0x021D54B0
	str r5, [r0, #0x4]
	str r4, [r0, #0x8]
	bl MicStopAutoSampling
_020D47B0:
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr
_020D47C8: .word 0x021D54B0

	arm_func_start MIC_StartAutoSampling
MIC_StartAutoSampling: ; 0x020D47CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4808 ; =MicGetResultCallback
	mov r2, #0x0
	bl MIC_StartAutoSamplingAsync
	ldr r1, _020D480C ; =0x021D54B0
	cmp r0, #0x0
	str r0, [r1, #0xc]
	bne _020D47F4
	bl MicWaitBusy
_020D47F4:
	ldr r0, _020D480C ; =0x021D54B0
	ldr r0, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4808: .word MicGetResultCallback
_020D480C: .word 0x021D54B0

	arm_func_start MIC_StartAutoSamplingAsync
MIC_StartAutoSamplingAsync: ; 0x020D4810
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r0, [r7, #0x4]
	mov r6, r1
	ands r0, r0, #0x1f
	mov r5, r2
	addne sp, sp, #0x4
	movne r0, #0x2
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, [r7, #0x8]
	ands r0, r1, #0x1f
	addne sp, sp, #0x4
	movne r0, #0x2
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x2
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r7, #0xc]
	cmp r0, #0x400
	addcc sp, sp, #0x4
	movcc r0, #0x2
	ldmccia sp!, {r4-r7,lr}
	bxcc lr
	ldr r0, [r7, #0x0]
	cmp r0, #0x5
	addls pc, pc, r0, lsl #0x2
	b _020D48D8
_020D4890:
	b _020D48A8
	b _020D48B0
	b _020D48B8
	b _020D48C0
	b _020D48C8
	b _020D48D0
_020D48A8:
	mov r1, #0x0
	b _020D48E8
_020D48B0:
	mov r1, #0x1
	b _020D48E8
_020D48B8:
	mov r1, #0x2
	b _020D48E8
_020D48C0:
	mov r1, #0x3
	b _020D48E8
_020D48C8:
	mov r1, #0x5
	b _020D48E8
_020D48D0:
	mov r1, #0x7
	b _020D48E8
_020D48D8:
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D48E8:
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	orrne r0, r1, #0x10
	andne r0, r0, #0xff
	andeq r0, r1, #0xff
	and r4, r0, #0xff
	bl OS_DisableInterrupts
	ldr r1, _020D497C
	ldr r2, [r1]
	cmp r2, #0x0
	beq _020D4928
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D4928:
	mov r2, #0x1
	str r2, [r1]
	bl OS_RestoreInterrupts
	ldr r0, _020D497C
	mov r3, r4
	str r6, [r0, #0x4]
	str r5, [r0, #0x8]
	ldr r1, [r7, #0x14]
	str r1, [r0, #0x10]
	ldr r1, [r7, #0x18]
	str r1, [r0, #0x14]
	ldr r0, [r7, #0x4]
	ldr r1, [r7, #0x8]
	ldr r2, [r7, #0xC]
	bl MicStartAutoSampling
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D497C: .word 0x021D54B0

	arm_func_start MIC_DoSamplingAsync
MIC_DoSamplingAsync: ; 0x020D4980
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	mov r7, r1
	mov r6, r2
	mov r5, r3
	addge sp, sp, #0x4
	movge r0, #0x2
	ldmgeia sp!, {r4-r7,lr}
	bxge lr
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020D49E4
_020D49B4:
	b _020D49C4
	b _020D49CC
	b _020D49D4
	b _020D49DC
_020D49C4:
	mov r4, #0x0
	b _020D49F4
_020D49CC:
	mov r4, #0x1
	b _020D49F4
_020D49D4:
	mov r4, #0x2
	b _020D49F4
_020D49DC:
	mov r4, #0x3
	b _020D49F4
_020D49E4:
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D49F4:
	bl OS_DisableInterrupts
	ldr r1, _020D4A58
	ldr r2, [r1]
	cmp r2, #0x0
	beq _020D4A1C
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D4A1C:
	mov r2, #0x1
	str r2, [r1]
	bl OS_RestoreInterrupts
	ldr r1, _020D4A58
	mov r0, r4
	str r6, [r1, #0x4]
	str r5, [r1, #0x8]
	str r7, [r1, #0x18]
	bl MicDoSampling
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D4A58: .word 0x021D54B0

	arm_func_start MIC_Init
MIC_Init: ; 0x020D4A5C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D4AD8 ; =0x021D54AC
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, _020D4ADC ; =0x021D54B0
	mov r2, #0x0
	mov r3, #0x1
	strh r3, [r1, #0x0]
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	bl PXI_Init
	mov r5, #0x9
	mov r4, #0x1
_020D4AA0:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020D4AAC:
	cmp r0, #0x0
	beq _020D4AA0
	ldr r2, _020D4AE0
	mov r3, #0x0
	ldr r1, _020D4AE4
	mov r0, #0x9
	str r3, [r2]
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr
_020D4AD8: .word 0x021D54AC
_020D4ADC: .word 0x021D54B0
_020D4AE0: .word 0x027FFF90
_020D4AE4: .word MicCommonCallback
