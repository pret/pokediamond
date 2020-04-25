	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	.section .itcm
	; Used in autoload
	arm_func_start OS_IrqHandler
OS_IrqHandler:
	stmfd sp!, {lr}
	mov ip, #0x04000000
	add ip, ip, #0x210
	ldr r1, [ip, #-8]
	cmp r1, #0
	ldmeqfd sp!, {pc}
	ldmia ip, {r1, r2}
	ands r1, r1, r2
	ldmeqfd sp!, {pc}
	mov r3, #0x80000000
_02106FC8:
	clz r0, r1
	bics r1, r1, r3, lsr r0
	bne _02106FC8
	mov r1, r3, lsr r0
	str r1, [ip, #0x4]
	rsbs r0, r0, #0x1f
	ldr r1, _02106FF0 ; =0x027E0000
	ldr r0, [r1, r0, lsl #2]
	ldr lr, _02106FF4 ; =0x01FF8058
	bx r0
_02106FF0: .word OS_IRQTable
_02106FF4: .word OS_IrqHandler_ThreadSwitch

	arm_func_start OS_IrqHandler_ThreadSwitch
OS_IrqHandler_ThreadSwitch: ;
	ldr ip, _02107144
	mov r3, #0x0
	ldr ip, [ip]
	mov r2, #0x1
	cmp ip, #0x0
	beq _02107048
_02107010:
	str r2, [ip, #0x64]
	str r3, [ip, #0x78]
	str r3, [ip, #0x7c]
	ldr r0, [ip, #0x80]
	str r3, [ip, #0x80]
	mov ip, r0
	cmp ip, #0x0
	bne _02107010
	ldr ip, _02107144
	str r3, [ip]
	str r3, [ip, #0x4]
	ldr ip, _02107148
	mov r1, #0x1
	strh r1, [ip]
_02107048:
	ldr ip, _02107148
	ldrh r1, [ip]
	cmp r1, #0x0
	ldreq pc, [sp], #0x4
	mov r1, #0x0
	strh r1, [ip]
	mov r3, #0xd2
	msr CPSR_c, r3
	add r2, ip, #0x8
	ldr r1, [r2]
_02107070:
	cmp r1, #0x0
	ldrneh r0, [r1, #0x64]
	cmpne r0, #0x1
	ldrne r1, [r1, #0x68]
	bne _02107070
	cmp r1, #0x0
	bne _02107098
_0210708C:
	mov r3, #0x92
	msr CPSR_c, r3
	ldr pc, [sp], #0x4
_02107098:
	ldr r0, [ip, #0x4]
	cmp r1, r0
	beq _0210708C
	ldr r3, [ip, #0xC]
	cmp r3, #0x0
	beq _021070C0
	stmdb sp!, {r0, r1, ip}
	mov lr, pc
	bx r3
	ldmia sp!, {r0, r1, ip}
_021070C0:
	str r1, [ip, #0x4]
	mrs r2, SPSR
	str r2, [r0, #0x0]!
	stmdb sp!, {r0, r1}
	add r0, r0, #0x0
	add r0, r0, #0x48
	ldr r1, _0210714C
	blx r1
	ldmia sp!, {r0, r1}
	ldmib sp!, {r2, r3}
	stmib r0!, {r2, r3}
	ldmib sp!, {r2, r3, ip, lr}
	stmib r0!, {r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	stmib r0!, {lr}
	mov r3, #0xd3
	msr CPSR_c, r3
	stmib r0!, {sp}
	stmfd sp!, {r1}
	add r0, r1, #0x0
	add r0, r0, #0x48
	ldr r1, _02107150
	blx r1
	ldmfd sp!, {r1}
	ldr sp, [r1, #0x44]
	mov r3, #0xd2
	msr CPSR_c, r3
	ldr r2, [r1, #0x0]!
	msr SPSR_fc, r2
	ldr lr, [r1, #0x40]
	ldmib r1!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, lr}^
	nop
	stmda sp!, {r0, r1, r2, r3, ip, lr}
	ldmfd sp!, {pc}
_02107144: .word OSi_IrqThreadQueue
_02107148: .word OSi_ThreadInfo
_0210714C: .word CP_SaveContext
_02107150: .word CP_RestoreContext

	.section .itcm
	arm_func_start OSi_DoBoot
OSi_DoBoot: ; 02107154
	mov ip, #0x04000000
	str ip, [ip, #0x208]
	ldr r1, _02107200
	add r1, r1, #0x3fc0
	add r1, r1, #0x3c
	mov r0, #0x0
	str r0, [r1]
	ldr r1, _02107204
_02107174:
	ldrh r0, [r1]
	and r0, r0, #0xf
	cmp r0, #0x1
	bne _02107174
	mov r0, #0x100
	strh r0, [r1]
	mov r0, #0x0
	ldr r3, _02107208
	ldr r4, [r3]
	ldr r1, _0210720C
	mov r2, #0x80
	bl OSi_CpuClear32
	str r4, [r3]
	ldr r1, _02107210
	mov r2, #0x18
	bl OSi_CpuClear32
	ldr r1, _02107214
	strh r0, [r1]
	ldr r1, _02107218
	mov r2, #0x64
	bl OSi_CpuClear32
	ldr r1, _02107204
_021071CC:
	ldrh r0, [r1]
	and r0, r0, #0xf
	cmp r0, #0x1
	beq _021071CC
	mov r0, #0x0
	strh r0, [r1]
	ldr r3, _0210721C
	ldr ip, [r3, #0x24]
	mov lr, ip
	ldr fp, _02107210
	ldmia fp, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl}
	mov fp, #0x0
	bx ip
_02107200: .word SDK_AUTOLOAD_DTCM_START
_02107204: .word 0x04000180
_02107208: .word 0x027FFD9C
_0210720C: .word 0x027FFD80
_02107210: .word 0x027FFF80
_02107214: .word 0x027FFF98
_02107218: .word 0x027FFF9C
_0210721C: .word 0x027FFE00

	arm_func_start OSi_CpuClear32
OSi_CpuClear32:
	.incbin "baserom.nds", 0x10B220, 0x480

	.section .dtcm
	.global OS_IRQTable
OS_IRQTable: ; 10b6a0
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OSi_IrqTimer0 ; 020c9cbc
	.word OSi_IrqTimer1 ; 020c9cac
	.word OSi_IrqTimer2 ; 020c9c9c
	.word OSi_IrqTimer3 ; 020c9c8c
	.word OS_IrqDummy ; 020c9da8
	.word OSi_IrqDma0 ; 020c9cfc
	.word OSi_IrqDma1 ; 020c9cec
	.word OSi_IrqDma2 ; 020c9cdc
	.word OSi_IrqDma3 ; 020c9ccc
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.balign 16, 0
OSi_IrqThreadQueue:
