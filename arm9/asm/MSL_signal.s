	.include "asm/macros.inc"
	.include "global.inc"
	.extern OSi_ThreadInfo
    .extern __cs_id
    .extern __cs_ref
    .extern __cs

    .bss

	.global signal_funcs
signal_funcs: ; 0x021D74AC
	.space 0x1c
	.size signal_funcs,.-signal_funcs

    .text

	arm_func_start raise
raise: ; 0x020E2D7C
	stmdb sp!, {r3-r5,lr}
	mov r5, r0
	cmp r5, #0x1
	blt _020E2D94
	cmp r5, #0x7
	ble _020E2D9C
_020E2D94:
	mvn r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E2D9C:
	ldr r0, _020E2E98 ; =__cs + 0xA8
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _020E2DD0
	ldr r0, _020E2E9C ; =OSi_ThreadInfo
	ldr r1, _020E2EA0 ; =__cs_id
	ldr r2, [r0, #0x4]
	ldr r0, _020E2EA4 ; =__cs_ref
	ldr r3, [r2, #0x6c]
	mov r2, #0x1
	str r3, [r1, #0x1c]
	str r2, [r0, #0x1c]
	b _020E2E28
_020E2DD0:
	ldr r0, _020E2E9C ; =OSi_ThreadInfo
	ldr r1, _020E2EA0 ; =__cs_id
	ldr r0, [r0, #0x4]
	ldr r1, [r1, #0x1c]
	ldr r0, [r0, #0x6c]
	cmp r1, r0
	bne _020E2E00
	ldr r0, _020E2EA4 ; =__cs_ref
	ldr r1, [r0, #0x1c]
	add r1, r1, #0x1
	str r1, [r0, #0x1c]
	b _020E2E28
_020E2E00:
	ldr r0, _020E2E98 ; =__cs + 0xA8
	bl OS_LockMutex
	ldr r0, _020E2E9C ; =OSi_ThreadInfo
	ldr r1, _020E2EA0 ; =__cs_id
	ldr r2, [r0, #0x4]
	ldr r0, _020E2EA4 ; =__cs_ref
	ldr r3, [r2, #0x6c]
	mov r2, #0x1
	str r3, [r1, #0x1c]
	str r2, [r0, #0x1c]
_020E2E28:
	ldr r1, _020E2EA8 ; =signal_funcs
	sub r2, r5, #0x1
	ldr r4, [r1, r2, lsl #0x2]
	cmp r4, #0x1
	movne r0, #0x0
	strne r0, [r1, r2, lsl #0x2]
	ldr r0, _020E2EA4 ; =__cs_ref
	ldr r1, [r0, #0x1c]
	subs r1, r1, #0x1
	str r1, [r0, #0x1c]
	bne _020E2E5C
	ldr r0, _020E2E98 ; =__cs + 0xA8
	bl OS_UnlockMutex
_020E2E5C:
	cmp r4, #0x1
	beq _020E2E70
	cmp r4, #0x0
	cmpeq r5, #0x1
	bne _020E2E78
_020E2E70:
	mov r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E2E78:
	cmp r4, #0x0
	bne _020E2E88
	mov r0, #0x0
	bl exit
_020E2E88:
	mov r0, r5
	blx r4
	mov r0, #0x0
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020E2E98: .word __cs + 0xA8
_020E2E9C: .word OSi_ThreadInfo
_020E2EA0: .word __cs_id
_020E2EA4: .word __cs_ref
_020E2EA8: .word signal_funcs
    arm_func_end raise

    .section .exceptix,4

	.word raise
	.short 305
	.word 0x00200300
