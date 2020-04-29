    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_EnableInterrupts
OS_EnableInterrupts: ; 0x020CD2FC
	mrs r0, cpsr
	bic r1, r0, #0x80
	msr cpsr_c, r1
	and r0, r0, #0x80
	bx lr

	arm_func_start OS_DisableInterrupts
OS_DisableInterrupts:
	mrs r0, cpsr
	orr r1, r0, #0x80
	msr cpsr_c, r1
	and r0, r0, #0x80
	bx lr

	arm_func_start OS_RestoreInterrupts
OS_RestoreInterrupts:
	mrs r1, cpsr
	bic r2, r1, #0x80
	orr r2, r2, r0
	msr cpsr_c, r2
	and r0, r1, #0x80
	bx lr

	arm_func_start OS_DisableInterrupts_IrqAndFiq
OS_DisableInterrupts_IrqAndFiq: ; 0x020CD33C
	mrs r0, cpsr
	orr r1, r0, #0xc0
	msr cpsr_c, r1
	and r0, r0, #0xc0
	bx lr

	arm_func_start OS_RestoreInterrupts_IrqAndFiq
OS_RestoreInterrupts_IrqAndFiq: ; 0x020CD350
	mrs r1, cpsr
	bic r2, r1, #0xc0
	orr r2, r2, r0
	msr cpsr_c, r2
	and r0, r1, #0xc0
	bx lr

	arm_func_start OS_GetCpsrIrq
OS_GetCpsrIrq: ; 0x020CD368
	mrs r0, cpsr
	and r0, r0, #0x80
	bx lr

	arm_func_start OS_GetProcMode
OS_GetProcMode: ; 0x020CD374
	mrs r0, cpsr
	and r0, r0, #0x1f
	bx lr

	arm_func_start OS_SpinWait
OS_SpinWait:
	subs r0, r0, #0x4
	bhs OS_SpinWait
	bx lr

	arm_func_start OS_WaitVBlankIntr
OS_WaitVBlankIntr: ; 0x020CD38C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x1
	blx SVC_WaitByLoop
	mov r0, #0x1
	mov r1, r0
	bl OS_WaitIrq
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
