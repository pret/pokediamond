	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	arm_func_start FSi_TranslateCommand
FSi_TranslateCommand:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r0, [r8, #0xc]
	mov r7, r1
	mov r1, #0x1
	ldr r5, [r8, #0x8]
	mov r4, r1, lsl r7
	ands r0, r0, #0x4
	moveq r1, #0x0
	cmp r1, #0x0
	ldrne r0, [r5, #0x1c]
	orrne r0, r0, #0x200
	strne r0, [r5, #0x1c]
	ldreq r0, [r5, #0x1c]
	orreq r0, r0, #0x100
	streq r0, [r5, #0x1c]
	ldr r0, [r5, #0x58]
	ands r0, r0, r4
	beq _020CFFE4
	ldr r2, [r5, #0x54]
	mov r0, r8
	mov r1, r7
	blx r2
	mov r6, r0
	cmp r6, #0x8
	addls pc, pc, r6, lsl #0x2
	b _020CFFE8
_020CFFA0:
	b _020CFFC4
	b _020CFFC4
	b _020CFFE8
	b _020CFFE8
	b _020CFFC4
	b _020CFFE8
	b _020CFFE8
	b _020CFFE8
	b _020CFFCC
_020CFFC4:
	str r6, [r8, #0x14]
	b _020CFFE8
_020CFFCC:
	ldr r1, [r5, #0x58]
	mvn r0, r4
	and r0, r1, r0
	str r0, [r5, #0x58]
	mov r6, #0x7
	b _020CFFE8
_020CFFE4:
	mov r6, #0x7
_020CFFE8:
	cmp r6, #0x7
	bne _020D0004
	ldr r1, _020D00AC ; =0x02103F80
	mov r0, r8
	ldr r1, [r1, r7, lsl #0x2]
	blx r1
	mov r6, r0
_020D0004:
	cmp r6, #0x6
	bne _020D0060
	ldr r0, [r8, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D00A0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x200
	beq _020D0050
	add r6, r5, #0xc
_020D003C:
	mov r0, r6
	bl OS_SleepThread
	ldr r0, [r5, #0x1c]
	ands r0, r0, #0x200
	bne _020D003C
_020D0050:
	mov r0, r4
	ldr r6, [r8, #0x14]
	bl OS_RestoreInterrupts
	b _020D00A0
_020D0060:
	ldr r0, [r8, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	ldrne r0, [r5, #0x1c]
	bicne r0, r0, #0x200
	strne r0, [r5, #0x1c]
	strne r6, [r8, #0x14]
	bne _020D00A0
	ldr r1, [r5, #0x1c]
	mov r0, r8
	bic r2, r1, #0x100
	mov r1, r6
	str r2, [r5, #0x1c]
	bl FSi_ReleaseCommand
_020D00A0:
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D00AC: .word 0x02103F80

	arm_func_start FSi_ReleaseCommand
FSi_ReleaseCommand:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x0]
	mov r4, r0
	ldr r0, [r6, #0x4]
	cmp r1, #0x0
	strne r0, [r1, #0x4]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r6, #0x0]
	ldr r1, [r6, #0x0]
	add r0, r6, #0x18
	str r1, [r6, #0x4]
	ldr r1, [r6, #0xc]
	bic r1, r1, #0x4f
	str r1, [r6, #0xc]
	str r5, [r6, #0x14]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr
