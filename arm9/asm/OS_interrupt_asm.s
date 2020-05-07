	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start OS_SetIrqStackChecker
OS_SetIrqStackChecker: ; 0x020C9DAC
	ldr ip, _020C9DD0 ; =0x027E0000
	ldr r3, _020C9DD4 ; =0xFDDB597D
	add r0, r12, #0x3000
	ldr r2, _020C9DD8 ; =0x7BF9DD5B
	ldr r1, _020C9DDC ; =0x00000400
	str r3, [r0, #0xf7c]
	add r0, r12, #0x3f80
	str r2, [r0, -r1]
	bx lr
	.balign 4
_020C9DD0: .word 0x027E0000
_020C9DD4: .word 0xFDDB597D
_020C9DD8: .word 0x7BF9DD5B
_020C9DDC: .word 0x00000400

	arm_func_start OS_ResetRequestIrqMask
OS_ResetRequestIrqMask: ; 0x020C9DE0
	ldr ip, _020C9E0C ; =0x04000208
	mov r1, #0x0
	ldrh r3, [r12, #0x0]
	ldr r2, _020C9E10 ; =0x04000214
	strh r1, [r12, #0x0]
	ldr r1, [r2, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r12, #0x0]
	mov r0, r1
	strh r3, [r12, #0x0]
	bx lr
	.balign 4
_020C9E0C: .word 0x04000208
_020C9E10: .word 0x04000214

	arm_func_start OS_DisableIrqMask
OS_DisableIrqMask: ; 0x020C9E14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, _020C9E54 ; =0x04000208
	mov r3, #0x0
	ldrh r12, [lr, #0x0]
	ldr r2, _020C9E58 ; =0x04000210
	mvn r1, r0
	strh r3, [lr, #0x0]
	ldr r0, [r2, #0x0]
	and r1, r0, r1
	str r1, [r2, #0x0]
	ldrh r1, [lr, #0x0]
	strh r12, [lr, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C9E54: .word 0x04000208
_020C9E58: .word 0x04000210

	arm_func_start OS_EnableIrqMask
OS_EnableIrqMask: ; 0x020C9E5C
	ldr ip, _020C9E8C ; =0x04000208
	mov r1, #0x0
	ldrh r3, [r12, #0x0]
	ldr r2, _020C9E90 ; =0x04000210
	strh r1, [r12, #0x0]
	ldr r1, [r2, #0x0]
	orr r0, r1, r0
	str r0, [r2, #0x0]
	ldrh r0, [r12, #0x0]
	mov r0, r1
	strh r3, [r12, #0x0]
	bx lr
	.balign 4
_020C9E8C: .word 0x04000208
_020C9E90: .word 0x04000210

	arm_func_start OS_SetIrqMask
OS_SetIrqMask: ; 0x020C9E94
	ldr ip, _020C9EC0 ; =0x04000208
	mov r1, #0x0
	ldrh r3, [r12, #0x0]
	ldr r2, _020C9EC4 ; =0x04000210
	strh r1, [r12, #0x0]
	ldr r1, [r2, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r12, #0x0]
	mov r0, r1
	strh r3, [r12, #0x0]
	bx lr
	.balign 4
_020C9EC0: .word 0x04000208
_020C9EC4: .word 0x04000210

	arm_func_start OSi_EnterTimerCallback
OSi_EnterTimerCallback: ; 0x020C9EC8
	stmdb sp!, {r4,lr}
	mov r3, #0xc
	mul r4, r0, r3
	ldr ip, _020C9F08 ; =0x021D344C
	add r0, r0, #0x3
	mov r3, #0x1
	mov r0, r3, lsl r0
	ldr r3, _020C9F0C ; =0x021D3454
	str r1, [r12, r4]
	str r2, [r3, r4]
	bl OS_EnableIrqMask
	ldr r0, _020C9F10 ; =0x021D3450
	mov r1, #0x1
	str r1, [r0, r4]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9F08: .word OSi_IrqCallbackInfo+0x30
_020C9F0C: .word OSi_IrqCallbackInfo+0x38
_020C9F10: .word OSi_IrqCallbackInfo+0x34

	arm_func_start OSi_EnterDmaCallback
OSi_EnterDmaCallback: ; 0x020C9F14
	stmdb sp!, {r4-r6,lr}
	mov r3, #0xc
	mul r6, r0, r3
	ldr ip, _020C9F54 ; =OSi_IrqCallbackInfo
	add r4, r0, #0x8
	mov r5, #0x1
	mov r0, r5, lsl r4
	ldr r3, _020C9F58 ; =0x021D3424
	str r1, [r12, r6]
	str r2, [r3, r6]
	bl OS_EnableIrqMask
	and r1, r0, r5, lsl r4
	ldr r0, _020C9F5C ; =0x021D3420
	str r1, [r0, r6]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9F54: .word OSi_IrqCallbackInfo
_020C9F58: .word OSi_IrqCallbackInfo + 8
_020C9F5C: .word OSi_IrqCallbackInfo + 4
