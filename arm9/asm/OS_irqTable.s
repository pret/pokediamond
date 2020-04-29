	.include "asm/macros.inc"
	.include "global.inc"

    .section .dtcm
	.balign 16, 0
	.global OS_IRQTable
OS_IRQTable: ; 027E0000 ;10b6a0
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OSi_IrqTimer0
	.word OSi_IrqTimer1
	.word OSi_IrqTimer2
	.word OSi_IrqTimer3
	.word OS_IrqDummy
	.word OSi_IrqDma0
	.word OSi_IrqDma1
	.word OSi_IrqDma2
	.word OSi_IrqDma3
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy
	.word OS_IrqDummy

    .section .text

	arm_func_start OSi_IrqTimer3
OSi_IrqTimer3: ; 0x020C9C8C
	ldr ip, _020C9C98 ; =OSi_IrqCallback
	mov r0, #0x7
	bx r12
	.balign 4
_020C9C98: .word OSi_IrqCallback

	arm_func_start OSi_IrqTimer2
OSi_IrqTimer2: ; 0x020C9C9C
	ldr ip, _020C9CA8 ; =OSi_IrqCallback
	mov r0, #0x6
	bx r12
	.balign 4
_020C9CA8: .word OSi_IrqCallback

	arm_func_start OSi_IrqTimer1
OSi_IrqTimer1: ; 0x020C9CAC
	ldr ip, _020C9CB8 ; =OSi_IrqCallback
	mov r0, #0x5
	bx r12
	.balign 4
_020C9CB8: .word OSi_IrqCallback

	arm_func_start OSi_IrqTimer0
OSi_IrqTimer0: ; 0x020C9CBC
	ldr ip, _020C9CC8 ; =OSi_IrqCallback
	mov r0, #0x4
	bx r12
	.balign 4
_020C9CC8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma3
OSi_IrqDma3: ; 0x020C9CCC
	ldr ip, _020C9CD8 ; =OSi_IrqCallback
	mov r0, #0x3
	bx r12
	.balign 4
_020C9CD8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma2
OSi_IrqDma2: ; 0x020C9CDC
	ldr ip, _020C9CE8 ; =OSi_IrqCallback
	mov r0, #0x2
	bx r12
	.balign 4
_020C9CE8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma1
OSi_IrqDma1: ; 0x020C9CEC
	ldr ip, _020C9CF8 ; =OSi_IrqCallback
	mov r0, #0x1
	bx r12
	.balign 4
_020C9CF8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma0
OSi_IrqDma0: ; 0x020C9CFC
	ldr ip, _020C9D08 ; =OSi_IrqCallback
	mov r0, #0x0
	bx r12
	.balign 4
_020C9D08: .word OSi_IrqCallback

	arm_func_start OSi_IrqCallback
OSi_IrqCallback: ; 0x020C9D0C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r1, #0xc
	mul r4, r0, r1
	ldr r2, _020C9D94 ; =OSi_IrqCallbackInfo
	ldr r3, _020C9D98 ; =0x02106818
	mov r0, r0, lsl #0x1
	ldr r1, [r2, r4]
	ldrh r3, [r3, r0]
	mov r5, #0x1
	mov r0, #0x0
	str r0, [r2, r4]
	cmp r1, #0x0
	mov r5, r5, lsl r3
	beq _020C9D54
	ldr r0, _020C9D9C ; =0x021D3424
	ldr r0, [r0, r4]
	blx r1
_020C9D54:
	ldr r0, _020C9DA0 ; =0x027E0000
	ldr r1, _020C9DA4 ; =0x021D3420
	add r0, r0, #0x3000
	ldr r2, [r0, #0xff8]
	orr r2, r2, r5
	str r2, [r0, #0xff8]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	bl OS_DisableIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C9D94: .word OSi_IrqCallbackInfo
_020C9D98: .word OSi_IrqCallbackInfoIndex
_020C9D9C: .word OSi_IrqCallbackInfo + 8
_020C9DA0: .word SDK_AUTOLOAD_DTCM_START
_020C9DA4: .word OSi_IrqCallbackInfo + 4

	arm_func_start OS_IrqDummy
OS_IrqDummy: ; 0x020C9DA8
	bx lr
