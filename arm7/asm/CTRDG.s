	.include "asm/macros.inc"
	.include "global.inc"

    .section .bss

	.global CTRDGi_Work
CTRDGi_Work: ;0x03809FB8
	.space 0x03809FBC - 0x03809FB8

    .section .text

	arm_func_start CTRDGi_SendtoPxi
CTRDGi_SendtoPxi: ;@ 0x038038C0
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	mov	r7, r0
	mov	r6, #1
	mov	r5, #13
	mov	r4, #0
	b	_038038E4
_038038DC:
	mov	r0, r6
	bl	FUN_037F8CB4
_038038E4:
	mov	r0, r5
	mov	r1, r7
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_038038DC
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr

	arm_func_start CTRDGi_UnlockByProcessor
CTRDGi_UnlockByProcessor: ;@ 0x03803908
	stmdb	sp!, {r4, lr}
	mov	r4, r1
	ldr	r1, [r4]
	cmp	r1, #0
	bne	_03803920
	bl	OS_UnLockCartridge
_03803920:
	ldr	r0, [r4, #4]
	bl	OS_RestoreInterrupts
	ldmia	sp!, {r4, lr}
	bx	lr

	arm_func_start CTRDGi_LockByProcessor
CTRDGi_LockByProcessor: ;@ 0x03803930
	stmdb	sp!, {r4, r5, lr}
	sub	sp, sp, #4
	mov	r5, r0
	mov	r4, r1
	bl	OS_DisableInterrupts
	str	r0, [r4, #4]
	ldr	r0, _0380398C	;@ =0x027FFFE8
	bl	OS_ReadOwnerOfLockWord
	and	r0, r0, #128	;@ 0x80
	str	r0, [r4]
	ldr	r0, [r4]
	cmp	r0, #0
	bne	_03803974
	mov	r0, r5
	bl	OS_TryLockCartridge
	cmp	r0, #0
	bne	_0380397C
_03803974:
	mov	r0, #1
	b	_03803980
_0380397C:
	mov	r0, #0
_03803980:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, lr}
	bx	lr
_0380398C:	.word	0x027FFFE8

	arm_func_start CTRDGi_RestoreAccessCycle
CTRDGi_RestoreAccessCycle: ;@ 0x03803990
	ldr	r3, [r0]
	ldr	r2, _038039C0	;@ =0x04000204
	ldrh	r1, [r2]
	bic	r1, r1, #12
	orr	r1, r1, r3, lsl #2
	strh	r1, [r2]
	ldr	r1, [r0, #4]
	ldrh	r0, [r2]
	bic	r0, r0, #16
	orr	r0, r0, r1, lsl #4
	strh	r0, [r2]
	bx	lr
_038039C0:	.word	0x04000204

	arm_func_start CTRDGi_ChangeLatestAccessCycle
CTRDGi_ChangeLatestAccessCycle: ;@ 0x038039C4
	ldr	r2, _03803A08	;@ =0x04000204
	ldrh	r1, [r2]
	and	r1, r1, #12
	mov	r1, r1, asr #2
	str	r1, [r0]
	ldrh	r1, [r2]
	and	r1, r1, #16
	mov	r1, r1, asr #4
	str	r1, [r0, #4]
	ldrh	r0, [r2]
	bic	r0, r0, #12
	orr	r0, r0, #12
	strh	r0, [r2]
	ldrh	r0, [r2]
	bic	r0, r0, #16
	strh	r0, [r2]
	bx	lr
_03803A08:	.word	0x04000204

	arm_func_start CTRDG_IsExisting
CTRDG_IsExisting: ;@ 0x03803A0C
	stmdb	sp!, {r4, lr}
	sub	sp, sp, #16
	mov	r4, #1
	ldr	r2, _03803B20	;@ =0x027FFC30
	ldrh	r1, [r2]
	ldr	r0, _03803B24	;@ =0x0000FFFF
	cmp	r1, r0
	moveq	r0, #0
	beq	_03803B14
	ldrb	r0, [r2, #5]
	mov	r0, r0, lsl #30
	mov	r0, r0, lsr #31
	cmp	r0, #1
	moveq	r0, #0
	beq	_03803B14
	ldr	r0, _03803B28	;@ =CTRDGi_Work
	ldrh	r0, [r0, #2]
	add	r1, sp, #0
	bl	CTRDGi_LockByProcessor
	cmp	r0, #0
	bne	_03803A70
	ldr	r0, [sp, #4]
	bl	OS_RestoreInterrupts
	mov	r0, r4
	b	_03803B14
_03803A70:
	add	r0, sp, #8
	bl	CTRDGi_ChangeLatestAccessCycle
	mov	r2, #134217728	;@ 0x8000000
	ldrb	r3, [r2, #178]	;@ 0xb2
	cmp	r3, #150	;@ 0x96
	bne	_03803A9C
	ldr	r0, _03803B20	;@ =0x027FFC30
	ldrh	r1, [r0]
	ldrh	r0, [r2, #190]	;@ 0xbe
	cmp	r1, r0
	bne	_03803AE4
_03803A9C:
	cmp	r3, #150	;@ 0x96
	beq	_03803ABC
	ldr	r0, _03803B20	;@ =0x027FFC30
	ldrh	r1, [r0]
	ldr	r0, _03803B2C	;@ =0x0801FFFE
	ldrh	r0, [r0]
	cmp	r1, r0
	bne	_03803AE4
_03803ABC:
	ldr	r2, _03803B20	;@ =0x027FFC30
	ldr	r1, [r2, #8]
	mov	r0, #134217728	;@ 0x8000000
	ldr	r0, [r0, #172]	;@ 0xac
	cmp	r1, r0
	beq	_03803AF8
	ldrb	r0, [r2, #5]
	mov	r0, r0, lsl #31
	movs	r0, r0, lsr #31
	beq	_03803AF8
_03803AE4:
	ldr	r1, _03803B20	;@ =0x027FFC30
	ldrb	r0, [r1, #5]
	orr	r0, r0, #2
	strb	r0, [r1, #5]
	mov	r4, #0
_03803AF8:
	add	r0, sp, #8
	bl	CTRDGi_RestoreAccessCycle
	ldr	r0, _03803B28	;@ =CTRDGi_Work
	ldrh	r0, [r0, #2]
	add	r1, sp, #0
	bl	CTRDGi_UnlockByProcessor
	mov	r0, r4
_03803B14:
	add	sp, sp, #16
	ldmia	sp!, {r4, lr}
	bx	lr
_03803B20:	.word	0x027FFC30
_03803B24:	.word	0x0000FFFF
_03803B28:	.word	CTRDGi_Work
_03803B2C:	.word	0x0801FFFE

	arm_func_start CTRDG_IsPulledOut
CTRDG_IsPulledOut: ;@ 0x03803B30
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	ldr	r2, _03803B80	;@ =0x027FFC30
	ldrh	r1, [r2]
	ldr	r0, _03803B84	;@ =0x0000FFFF
	cmp	r1, r0
	moveq	r0, #0
	beq	_03803B74
	ldrb	r0, [r2, #5]
	mov	r0, r0, lsl #30
	movs	r0, r0, lsr #31
	bne	_03803B64
	bl	CTRDG_IsExisting
_03803B64:
	ldr	r0, _03803B80	;@ =0x027FFC30
	ldrb	r0, [r0, #5]
	mov	r0, r0, lsl #30
	mov	r0, r0, lsr #31
_03803B74:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03803B80:	.word	0x027FFC30
_03803B84:	.word	0x0000FFFF

	arm_func_start CTRDGi_InitCommon
CTRDGi_InitCommon: ;@ 0x03803B88
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	str	r0, [sp]
	add	r0, sp, #0
	ldr	r1, _03803BC0	;@ =CTRDGi_Work
	ldr	r2, _03803BC4	;@ =0x05000001
	bl	FUN_03803BC8
	bl	OS_GetLockID
	ldr	r1, _03803BC0	;@ =CTRDGi_Work
	strh	r0, [r1, #2]
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03803BC0:	.word	CTRDGi_Work
_03803BC4:	.word	0x05000001

	arm_func_start FUN_03803BC8
FUN_03803BC8: ;@ 0x03803BC8
	ldr	ip, _03803BD0	;@ =SVC_CpuSet
	bx	ip
_03803BD0:	.word	SVC_CpuSet
