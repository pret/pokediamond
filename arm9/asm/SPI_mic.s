	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021D54AC
UNK_021D54AC: ; 0x021D54AC
	.space 0x4

	.global UNK_021D54B0
UNK_021D54B0: ; 0x021D54B0
	.space 0x1c

	.text

	arm_func_start MicWaitBusy
MicWaitBusy: ; 0x020D4408
	ldr ip, _020D441C ; =UNK_021D54B0
_020D440C:
	ldr r0, [r12, #0x0]
	cmp r0, #0x1
	beq _020D440C
	bx lr
	.balign 4
_020D441C: .word UNK_021D54B0

	arm_func_start MicGetResultCallback
MicGetResultCallback: ; 0x020D4420
	ldr r1, _020D442C ; =UNK_021D54B0
	str r0, [r1, #0xc]
	bx lr
	.balign 4
_020D442C: .word UNK_021D54B0

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
	ldr r0, _020D4700 ; =UNK_021D54B0
	ldr r2, _020D4700 ; =UNK_021D54B0
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
	ldr r1, _020D4700 ; =UNK_021D54B0
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
	ldr r1, _020D4700 ; =UNK_021D54B0
	ldr r2, [r1, #0x18]
	cmp r2, #0x0
	ldrne r1, _020D4704 ; =0x027FFF94
	ldrneh r1, [r1, #0x0]
	strneh r1, [r2, #0x0]
_020D46C0:
	ldr r1, _020D4700 ; =UNK_021D54B0
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	movne r2, #0x0
	strne r2, [r1, #0x0]
	ldr r2, _020D4700 ; =UNK_021D54B0
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
_020D4700: .word UNK_021D54B0
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
	ldr r1, _020D4758 ; =UNK_021D54B0
	cmp r0, #0x0
	str r0, [r1, #0xc]
	bne _020D4740
	bl MicWaitBusy
_020D4740:
	ldr r0, _020D4758 ; =UNK_021D54B0
	ldr r0, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4754: .word MicGetResultCallback
_020D4758: .word UNK_021D54B0

	arm_func_start MIC_StopAutoSamplingAsync
MIC_StopAutoSamplingAsync: ; 0x020D475C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl OS_DisableInterrupts
	ldr r1, _020D47C8 ; =UNK_021D54B0
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
	ldr r0, _020D47C8 ; =UNK_021D54B0
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
_020D47C8: .word UNK_021D54B0

	arm_func_start MIC_StartAutoSampling
MIC_StartAutoSampling: ; 0x020D47CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4808 ; =MicGetResultCallback
	mov r2, #0x0
	bl MIC_StartAutoSamplingAsync
	ldr r1, _020D480C ; =UNK_021D54B0
	cmp r0, #0x0
	str r0, [r1, #0xc]
	bne _020D47F4
	bl MicWaitBusy
_020D47F4:
	ldr r0, _020D480C ; =UNK_021D54B0
	ldr r0, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4808: .word MicGetResultCallback
_020D480C: .word UNK_021D54B0

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
_020D497C: .word UNK_021D54B0

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
_020D4A58: .word UNK_021D54B0

	arm_func_start MIC_Init
MIC_Init: ; 0x020D4A5C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D4AD8 ; =UNK_021D54AC
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, _020D4ADC ; =UNK_021D54B0
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
_020D4AD8: .word UNK_021D54AC
_020D4ADC: .word UNK_021D54B0
_020D4AE0: .word 0x027FFF90
_020D4AE4: .word MicCommonCallback
