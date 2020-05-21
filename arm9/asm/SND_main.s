	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_021D3820
	.extern UNK_021D381C

    .text

	arm_func_start SNDi_UnlockMutex
SNDi_UnlockMutex: ; 0x020CEC18
	ldr ip, _020CEC24 ; =OS_UnlockMutex
	ldr r0, _020CEC28 ; =UNK_021D3820
	bx r12
	.balign 4
_020CEC24: .word OS_UnlockMutex
_020CEC28: .word UNK_021D3820

	arm_func_start SNDi_LockMutex
SNDi_LockMutex: ; 0x020CEC2C
	ldr ip, _020CEC38 ; =OS_LockMutex
	ldr r0, _020CEC3C ; =UNK_021D3820
	bx r12
	.balign 4
_020CEC38: .word OS_LockMutex
_020CEC3C: .word UNK_021D3820

	arm_func_start SND_Init
SND_Init: ; 0x020CEC40
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CEC84 ; =UNK_021D381C
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020CEC88 ; =UNK_021D3820
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_InitMutex
	bl SND_CommandInit
	bl SND_AlarmInit
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CEC84: .word UNK_021D381C
_020CEC88: .word UNK_021D3820
