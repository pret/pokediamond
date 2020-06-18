	.include "asm/macros.inc"
	.include "global.inc"

    .section .data

	.global _03807704
_03807704:
	.word	0x00000001

	.global _03807708
_03807708:
	.word	0xFFFFFFFF

    .section .bss

	.global _03809FBC
_03809FBC: ;0x03809FBC
	.space 0x03809FC0 - 0x03809FBC

	.global current_vib
current_vib: ;0x03809FC0
	.space 0x03809FC4 - 0x03809FC0

	.global _03809FC4
_03809FC4: ;0x03809FC4
	.space 0x03809FC8 - 0x03809FC4

	.global _03809FC8
_03809FC8: ;0x03809FC8
	.space 0x03809FCC - 0x03809FC8

	.global _03809FCC
_03809FCC: ;0x03809FCC
	.space 0x03809FD0 - 0x03809FCC

	.global _03809FD0
_03809FD0: ;0x03809FD0
	.space 0x03809FD4 - 0x03809FD0

	.global _03809FD4
_03809FD4: ;0x03809FD4
	.space 0x03809FEC - 0x03809FD4

	.global _03809FEC
_03809FEC: ;0x03809FEC
	.space 0x0380A018 - 0x03809FEC

    .section .text

	arm_func_start FUN_03803BD4
FUN_03803BD4: ;@ 0x03803BD4
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	and	r0, r1, #63	;@ 0x3f
	cmp	r0, #3
	bne	_03803C40
	ldr	r0, _03803C50	;@ =0x01FFFFC0
	and	r0, r1, r0
	mov	r2, r0, lsr #6
	ldr	r1, _03803C54	;@ =0x04000204
	ldrh	r0, [r1]
	bic	r0, r0, #96	;@ 0x60
	orr	r0, r0, r2, lsl #5
	strh	r0, [r1]
	mov	r7, #1
	mov	r6, #17
	mov	r5, #18
	mov	r4, #0
	b	_03803C24
_03803C1C:
	mov	r0, r7
	bl	FUN_037F8CB4
_03803C24:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r4
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03803C1C
	b	_03803C44
_03803C40:
	bl	OS_Terminate
_03803C44:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03803C50:	.word	0x01FFFFC0
_03803C54:	.word	0x04000204

	arm_func_start CTRDGi_TerminateARM7
CTRDGi_TerminateARM7: ;@ 0x03803C58
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	mov	r0, #0
	bl	CTRDG_VibPulseEdgeUpdate
	bl	SND_BeginSleep
	bl	WVR_Shutdown
	bl	OS_Terminate
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start CTRDG_CheckPullOut_Polling
CTRDG_CheckPullOut_Polling: ;@ 0x03803C80
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r1, _03803D80	;@ =_03807708
	ldr	r3, [r1]
	mvn	r0, #0
	cmp	r3, r0
	ldreq	r0, _03803D84	;@ =0x027FFC3C
	ldreq	r0, [r0]
	addeq	r0, r0, #10
	streq	r0, [r1]
	beq	_03803D74
	ldr	r0, _03803D88	;@ =_03809FCC
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03803D74
	ldr	r0, _03803D8C	;@ =_03809FC8
	ldr	r0, [r0]
	cmp	r0, #0
	bne	_03803D74
	ldr	r2, _03803D84	;@ =0x027FFC3C
	ldr	r0, [r2]
	cmp	r0, r3
	bcc	_03803D74
	ldr	r0, [r2]
	add	r0, r0, #10
	str	r0, [r1]
	bl	CTRDG_IsPulledOut
	ldr	r1, _03803D8C	;@ =_03809FC8
	str	r0, [r1]
	bl	CTRDG_IsExisting
	cmp	r0, #0
	bne	_03803D28
	ldr	r0, _03803D90	;@ =_03807704
	ldr	r0, [r0]
	cmp	r0, #0
	movne	r1, #1
	ldrne	r0, _03803D88	;@ =_03809FCC
	strne	r1, [r0]
	bne	_03803D74
	mov	r1, #1
	ldr	r0, _03803D8C	;@ =_03809FC8
	str	r1, [r0]
_03803D28:
	mov	r7, #0
	ldr	r0, _03803D90	;@ =_03807704
	str	r7, [r0]
	ldr	r0, _03803D8C	;@ =_03809FC8
	ldr	r0, [r0]
	cmp	r0, #0
	beq	_03803D74
	mov	r6, #100	;@ 0x64
	mov	r5, #13
	mov	r4, #17
	b	_03803D5C
_03803D54:
	mov	r0, r6
	bl	OS_Sleep
_03803D5C:
	mov	r0, r5
	mov	r1, r4
	mov	r2, r7
	bl	PXI_SendWordByFifo
	cmp	r0, #0
	bne	_03803D54
_03803D74:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_03803D80:	.word	_03807708
_03803D84:	.word	0x027FFC3C
_03803D88:	.word	_03809FCC
_03803D8C:	.word	_03809FC8
_03803D90:	.word	_03807704

	arm_func_start CTRDGi_IsNinLogoOfAgb
CTRDGi_IsNinLogoOfAgb: ;@ 0x03803D94
	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r7, r0
	mov	r0, #134217728	;@ 0x8000000
	add	r6, r0, #4
	mov	r4, #1
	bl	OS_GetLockID
	mov	r0, r0, lsl #16
	mov	r5, r0, lsr #16
	mov	r0, r5
	bl	OS_LockCartridge
	mov	r1, #0
	ldr	r0, _03803E3C	;@ =0x0000FFFF
	eor	r2, r0, #3
	mov	r2, r2, lsl #16
	mov	lr, r2, lsr #16
	eor	r2, r0, #132	;@ 0x84
	mov	r2, r2, lsl #16
	mov	r8, r2, lsr #16
	b	_03803E18
_03803DE0:
	mov	ip, r0
	cmp	r1, #76	;@ 0x4c
	moveq	ip, r8
	beq	_03803DF8
	cmp	r1, #77	;@ 0x4d
	moveq	ip, lr
_03803DF8:
	mov	r3, r1, lsl #1
	ldrh	r2, [r7, r3]
	and	ip, ip, r2
	ldrh	r2, [r6, r3]
	cmp	ip, r2
	movne	r4, #0
	bne	_03803E20
	add	r1, r1, #1
_03803E18:
	cmp	r1, #78	;@ 0x4e
	blt	_03803DE0
_03803E20:
	mov	r0, r5
	bl	OS_UnLockCartridge
	mov	r0, r5
	bl	OS_ReleaseLockID
	mov	r0, r4
	ldmia	sp!, {r4, r5, r6, r7, r8, lr}
	bx	lr
_03803E3C:	.word	0x0000FFFF

	arm_func_start FUN_03803E40
FUN_03803E40: ;@ 0x03803E40
	ldr	r1, _03803E54	;@ =current_vib
	str	r0, [r1]
	ldr	r1, _03803E58	;@ =0x08001000
	strh	r0, [r1]
	bx	lr
_03803E54:	.word	current_vib
_03803E58:	.word	0x08001000

	arm_func_start CTRDG_VibPulseEdgeUpdate
CTRDG_VibPulseEdgeUpdate: ;@ 0x03803E5C
	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #4
	movs	r5, r0
	beq	_03803E9C
	ldr	r0, [r5]
	cmp	r0, #0
	bne	_03803E9C
	ldr	r0, [r5, #68]	;@ 0x44
	add	r0, r0, #1
	str	r0, [r5, #68]	;@ 0x44
	ldr	r1, [r5, #64]	;@ 0x40
	cmp	r1, #0
	beq	_03803E9C
	ldr	r0, [r5, #68]	;@ 0x44
	cmp	r0, r1
	movhi	r5, #0
_03803E9C:
	cmp	r5, #0
	beq	_03803EB0
	ldr	r0, [r5, #60]	;@ 0x3c
	cmp	r0, #0
	bne	_03803F48
_03803EB0:
	bl	OS_DisableInterrupts
	mov	r9, r0
	ldr	r0, _03804068	;@ =current_vib
	ldr	r0, [r0]
	cmp	r0, #2
	bne	_03803F34
	mov	r8, #0
	ldr	r7, _0380406C	;@ =0x027FFFE8
	ldr	r4, _03804070	;@ =_03809FBC
	ldr	fp, _03804074	;@ =0x000080E8
	mov	r6, r8
	mov	r5, #1
	b	_03803F2C
_03803EE4:
	mov	r0, r7
	bl	OS_ReadOwnerOfLockWord
	ands	sl, r0, #128	;@ 0x80
	bne	_03803F04
	ldrh	r0, [r4]
	bl	OS_TryLockCartridge
	cmp	r0, #0
	bne	_03803F24
_03803F04:
	mov	r0, r6
	bl	FUN_03803E40
	mov	r8, r5
	cmp	sl, #0
	bne	_03803F2C
	ldrh	r0, [r4]
	bl	OS_UnlockCartridge
	b	_03803F2C
_03803F24:
	mov	r0, fp
	bl	OS_SpinWait
_03803F2C:
	cmp	r8, #0
	beq	_03803EE4
_03803F34:
	ldr	r0, _03804078	;@ =_03809FEC
	bl	OS_CancelAlarm
	mov	r0, r9
	bl	OS_RestoreInterrupts
	b	_0380405C
_03803F48:
	cmp	r5, #0
	beq	_0380405C
	ldr	r0, _0380406C	;@ =0x027FFFE8
	bl	OS_ReadOwnerOfLockWord
	ands	r4, r0, #128	;@ 0x80
	bne	_03803F74
	ldr	r0, _03804070	;@ =_03809FBC
	ldrh	r0, [r0]
	bl	OS_TryLockCartridge
	cmp	r0, #0
	bne	_03804044
_03803F74:
	ldr	r1, [r5]
	ldr	r0, [r5, #4]
	cmp	r1, r0
	bne	_03803FB0
	mov	r0, #0
	bl	FUN_03803E40
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, [r5, #8]
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
	mov	r0, #0
	str	r0, [r5]
	b	_0380402C
_03803FB0:
	ands	r0, r1, #1
	beq	_03803FF4
	mov	r0, #0
	bl	FUN_03803E40
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, [r5]
	mov	r1, r1, lsr #1
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #36]	;@ 0x24
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
	ldr	r0, [r5]
	add	r0, r0, #1
	str	r0, [r5]
	b	_0380402C
_03803FF4:
	mov	r0, #2
	bl	FUN_03803E40
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, [r5]
	mov	r1, r1, lsr #1
	add	r1, r5, r1, lsl #2
	ldr	r1, [r1, #12]
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
	ldr	r0, [r5]
	add	r0, r0, #1
	str	r0, [r5]
_0380402C:
	cmp	r4, #0
	bne	_0380405C
	ldr	r0, _03804070	;@ =_03809FBC
	ldrh	r0, [r0]
	bl	OS_UnlockCartridge
	b	_0380405C
_03804044:
	str	r5, [sp]
	ldr	r0, _03804078	;@ =_03809FEC
	ldr	r1, _03804080	;@ =0x0000020B
	mov	r2, #0
	ldr	r3, _0380407C	;@ =CTRDG_VibPulseEdgeUpdate
	bl	OS_SetAlarm
_0380405C:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	bx	lr
_03804068:	.word	current_vib
_0380406C:	.word	0x027FFFE8
_03804070:	.word	_03809FBC
_03804074:	.word	0x000080E8
_03804078:	.word	_03809FEC
_0380407C:	.word	CTRDG_VibPulseEdgeUpdate
_03804080:	.word	0x0000020B
_03804084:
	mov	r0, r1
	ldr	ip, _03804090	;@ =CTRDG_VibPulseEdgeUpdate
	bx	ip
_03804090:	.word	CTRDG_VibPulseEdgeUpdate

	arm_func_start CTRDGi_CallbackForPulledOut
CTRDGi_CallbackForPulledOut: ;@ 0x03804094
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #63	;@ 0x3ff
	cmp	r0, #2
	bne	_038040B0
	bl	CTRDGi_TerminateARM7
	b	_038040B4
_038040B0:
	bl	OS_Terminate
_038040B4:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr

	arm_func_start CTRDGi_CallbackForInitModuleInfo
CTRDGi_CallbackForInitModuleInfo: ;@ 0x038040C0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	and	r0, r1, #63	;@ 0x3f
	cmp	r0, #1
	ldreq	r0, _038040F4	;@ =_03809FD4
	streq	r1, [r0]
	moveq	r1, #1
	streq	r1, [r0, #16]
	beq	_038040E8
	bl	OS_Terminate
_038040E8:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_038040F4:	.word	_03809FD4

	arm_func_start CTRDGi_InitModuleInfo
CTRDGi_InitModuleInfo: ;@ 0x038040F8
	stmdb	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #4
	ldr	r0, _038041C8	;@ =_03809FC4
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_038041BC
	mov	r1, #1
	str	r1, [r0]
	ldr	r0, _038041CC	;@ =0x04000300
	ldrh	r0, [r0]
	ands	r0, r0, #1
	beq	_038041BC
	mov	r0, #262144	;@ 0x40000
	bl	OS_SetIrqMask
	mov	r5, r0
	ldr	r1, _038041D0	;@ =0x04000208
	ldrh	r4, [r1]
	mov	r0, #1
	strh	r0, [r1]
	mov	r7, #256	;@ 0x100
	ldr	r6, _038041D4	;@ =_03809FD4
	b	_03804158
_03804150:
	mov	r0, r7
	bl	FUN_037F8CB4
_03804158:
	ldr	r0, [r6, #16]
	cmp	r0, #1
	bne	_03804150
	ldr	r1, [r6]
	ldr	r0, _038041D8	;@ =0x01FFFFC0
	and	r0, r1, r0
	mov	r0, r0, lsr #6
	mov	r0, r0, lsl #5
	add	r0, r0, #33554432	;@ 0x2000000
	add	r0, r0, #4
	bl	CTRDGi_IsNinLogoOfAgb
	ldr	r2, _038041DC	;@ =0x027FFC30
	ldrb	r1, [r2, #5]
	bic	r1, r1, #1
	and	r0, r0, #255	;@ 0xff
	and	r0, r0, #1
	orr	r0, r1, r0
	strb	r0, [r2, #5]
	mov	r0, #1
	bl	CTRDGi_SendtoPxi
	ldr	r1, _038041D0	;@ =0x04000208
	ldrh	r0, [r1]
	strh	r4, [r1]
	mov	r0, r5
	bl	OS_SetIrqMask
_038041BC:
	add	sp, sp, #4
	ldmia	sp!, {r4, r5, r6, r7, lr}
	bx	lr
_038041C8:	.word	_03809FC4
_038041CC:	.word	0x04000300
_038041D0:	.word	0x04000208
_038041D4:	.word	_03809FD4
_038041D8:	.word	0x01FFFFC0
_038041DC:	.word	0x027FFC30

	arm_func_start CTRDG_Init
CTRDG_Init: ;@ 0x038041E0
	stmfd	sp!, {lr}
	sub	sp, sp, #4
	bl	OS_InitTick
	bl	OS_InitAlarm
	ldr	r0, _03804270	;@ =_03809FEC
	bl	OS_CreateAlarm
	ldr	r0, _03804274	;@ =_03809FD0
	ldr	r1, [r0]
	cmp	r1, #0
	bne	_03804264
	mov	r1, #1
	str	r1, [r0]
	bl	CTRDGi_InitCommon
	bl	OS_GetLockID
	mvn	r1, #2
	cmp	r0, r1
	beq	_03804264
	ldr	r1, _03804278	;@ =_03809FBC
	strh	r0, [r1]
	bl	PXI_Init
	mov	r0, #13
	ldr	r1, _0380427C	;@ =CTRDGi_CallbackForInitModuleInfo
	bl	PXI_SetFifoRecvCallback
	bl	CTRDGi_InitModuleInfo
	mov	r0, #13
	ldr	r1, _03804280	;@ =CTRDGi_CallbackForPulledOut
	bl	PXI_SetFifoRecvCallback
	mov	r0, #16
	ldr	r1, _03804284	;@ =_03804084
	bl	PXI_SetFifoRecvCallback
	mov	r0, #17
	ldr	r1, _03804288	;@ =FUN_03803BD4
	bl	PXI_SetFifoRecvCallback
_03804264:
	add	sp, sp, #4
	ldmia	sp!, {lr}
	bx	lr
_03804270:	.word	_03809FEC
_03804274:	.word	_03809FD0
_03804278:	.word	_03809FBC
_0380427C:	.word	CTRDGi_CallbackForInitModuleInfo
_03804280:	.word	CTRDGi_CallbackForPulledOut
_03804284:	.word	_03804084
_03804288:	.word	FUN_03803BD4
