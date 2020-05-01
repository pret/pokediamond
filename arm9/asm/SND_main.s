	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start SNDi_UnlockMutex
SNDi_UnlockMutex: ; 0x020CEC18
	ldr ip, _020CEC24 ; =OS_UnlockMutex
	ldr r0, _020CEC28 ; =0x021D3820
	bx r12
	.balign 4
_020CEC24: .word OS_UnlockMutex
_020CEC28: .word 0x021D3820

	arm_func_start SNDi_LockMutex
SNDi_LockMutex: ; 0x020CEC2C
	ldr ip, _020CEC38 ; =OS_LockMutex
	ldr r0, _020CEC3C ; =0x021D3820
	bx r12
	.balign 4
_020CEC38: .word OS_LockMutex
_020CEC3C: .word 0x021D3820

	arm_func_start SND_Init
SND_Init: ; 0x020CEC40
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CEC84 ; =0x021D381C
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020CEC88 ; =0x021D3820
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_InitMutex
	bl SND_CommandInit
	bl SND_AlarmInit
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CEC84: .word 0x021D381C
_020CEC88: .word 0x021D3820
