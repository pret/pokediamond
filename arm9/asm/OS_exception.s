    .include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global OSi_UserExceptionHandler
OSi_UserExceptionHandler: ; 0x021D371C
	.space 0x4

	.global OSi_UserExceptionHandlerArg
OSi_UserExceptionHandlerArg: ; 0x021D3720
	.space 0x4

	.global OSi_DebuggerHandler
OSi_DebuggerHandler: ; 0x021D3724
	.space 0x4

	.global OSi_ExContext
OSi_ExContext: ; 0x021D3728
	.space 0x80

    .text

	arm_func_start OSi_ExceptionHandler
OSi_ExceptionHandler: ; 0x020CC9FC
	ldr ip, _020CCA68 ; =OSi_DebuggerHandler
	ldr r12, [r12, #0x0]
	cmp r12, #0x0
	movne lr, pc
	bxne r12
	ldr ip, _020CCA6C ; =0x02000000
	stmdb r12!, {r0-r3,sp-lr}
	and r0, sp, #0x1
	mov sp, r12
	mrs r1, cpsr
	and r1, r1, #0x1f
	teq r1, #0x17
	bne _020CCA38
	bl OSi_GetAndDisplayContext
	b _020CCA44
_020CCA38:
	teq r1, #0x1b
	bne _020CCA44
	bl OSi_GetAndDisplayContext
_020CCA44:
	ldr ip, _020CCA68 ; =OSi_DebuggerHandler
	ldr r12, [r12, #0x0]
	cmp r12, #0x0
_020CCA50:
	beq _020CCA50
_020CCA54:
	mov r0, r0
	b _020CCA54
_020CCA5C:
	ldmia sp!, {r0-r3,ip,lr}
	mov sp, ip
	bx lr
_020CCA68: .word OSi_DebuggerHandler
_020CCA6C: .word 0x02000000

	arm_func_start OSi_GetAndDisplayContext
OSi_GetAndDisplayContext: ; 0x020CCA70
	stmdb sp!, {r0,lr}
	bl OSi_SetExContext
	bl OSi_DisplayExContext
	ldmia sp!, {r0,lr}
	bx lr

	arm_func_start OSi_SetExContext
OSi_SetExContext: ; 0x020CCA84
	ldr r1, _020CCB10 ; =OSi_ExContext
	mrs r2, cpsr
	str r2, [r1, #0x74]
	str r0, [r1, #0x6c]
	ldr r0, [r12, #0x0]
	str r0, [r1, #0x4]
	ldr r0, [r12, #0x4]
	str r0, [r1, #0x8]
	ldr r0, [r12, #0x8]
	str r0, [r1, #0xc]
	ldr r0, [r12, #0xc]
	str r0, [r1, #0x10]
	ldr r2, [r12, #0x10]
	bic r2, r2, #0x1
	add r0, r1, #0x14
	stmia r0, {r4-r11}
	str r12, [r1, #0x70]
	ldr r0, [r2, #0x0]
	str r0, [r1, #0x64]
	ldr r3, [r2, #0x4]
	str r3, [r1, #0x0]
	ldr r0, [r2, #0x8]
	str r0, [r1, #0x34]
	ldr r0, [r2, #0xc]
	str r0, [r1, #0x40]
	mrs r0, cpsr
	orr r3, r3, #0x80
	bic r3, r3, #0x20
	msr cpsr_fsxc, r3
	str sp, [r1, #0x38]
	str lr, [r1, #0x3c]
	mrs r2, spsr
	str r2, [r1, #0x7c]
	msr cpsr_fsxc, r0
	bx lr
	.balign 4
_020CCB10: .word OSi_ExContext

	arm_func_start OSi_DisplayExContext
OSi_DisplayExContext: ; 0x020CCB14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CCB70 ; =OSi_UserExceptionHandler
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	mov r0, sp
	ldr r1, _020CCB74 ; =0x0000009F
	msr cpsr_fsxc, r1
	mov sp, r0
	bl OS_EnableProtectionUnit
	ldr r1, _020CCB78 ; =OSi_UserExceptionHandlerArg
	ldr r0, _020CCB70 ; =OSi_UserExceptionHandler
	ldr r1, [r1, #0x0]
	ldr r2, [r0, #0x0]
	ldr r0, _020CCB7C ; =OSi_ExContext
	blx r2
	bl OS_DisableProtectionUnit
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCB70: .word OSi_UserExceptionHandler
_020CCB74: .word 0x0000009F
_020CCB78: .word OSi_UserExceptionHandlerArg
_020CCB7C: .word OSi_ExContext

	arm_func_start OS_InitException
OS_InitException: ; 0x020CCB80
	ldr r0, _020CCBDC ; =0x027FFD9C
	ldr r1, [r0, #0x0]
	cmp r1, #0x2600000
	blo _020CCBA0
	cmp r1, #0x2800000
	ldrlo r0, _020CCBE0 ; =OSi_DebuggerHandler
	strcc r1, [r0, #0x0]
	blo _020CCBAC
_020CCBA0:
	ldr r0, _020CCBE0 ; =OSi_DebuggerHandler
	mov r1, #0x0
	str r1, [r0, #0x0]
_020CCBAC:
	ldr r0, _020CCBE0 ; =OSi_DebuggerHandler
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r2, _020CCBE4 ; =OSi_ExceptionHandler
	ldreq r1, _020CCBDC ; =0x027FFD9C
	ldreq r0, _020CCBE8 ; =0x027E3000
	streq r2, [r1, #0x0]
	streq r2, [r0, #0xfdc]
	ldr r0, _020CCBEC ; =OSi_UserExceptionHandler
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020CCBDC: .word 0x027FFD9C
_020CCBE0: .word OSi_DebuggerHandler
_020CCBE4: .word OSi_ExceptionHandler
_020CCBE8: .word 0x027E3000
_020CCBEC: .word OSi_UserExceptionHandler
