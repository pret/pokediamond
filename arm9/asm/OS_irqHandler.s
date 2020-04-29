	.include "asm/macros.inc"
	.include "global.inc"

    .section .dtcm
    .balign 16, 0
    .global OSi_IrqThreadQueue
OSi_IrqThreadQueue: ; 027E0060

	.section .text

	arm_func_start OS_WaitIrq
OS_WaitIrq:
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	mov r4, r1
	bl OS_DisableInterrupts
	cmp r5, #0x0
	beq _020C9C3C
	ldr r1, _020C9C80 ; =0x027E0000
	mvn r2, r4
	add r1, r1, #0x3000
	ldr r3, [r1, #0xff8]
	and r2, r3, r2
	str r2, [r1, #0xff8]
_020C9C3C:
	bl OS_RestoreInterrupts
	ldr r1, _020C9C80 ; =0x027E0000
	add r0, r1, #0x3000
	ldr r0, [r0, #0xff8]
	ands r0, r4, r0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr r0, _020C9C84 ; =0x00003FF8
	add r6, r1, r0
	ldr r5, _020C9C88 ; =0x027E0060
_020C9C64:
	mov r0, r5
	bl OS_SleepThread
	ldr r0, [r6, #0x0]
	ands r0, r4, r0
	beq _020C9C64
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9C80: .word 0x027E0000
_020C9C84: .word 0x00003FF8
_020C9C88: .word 0x027E0060
