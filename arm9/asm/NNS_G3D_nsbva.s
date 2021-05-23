	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020BE5A0
FUN_020BE5A0: ; 0x020BE5A0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, [r1, #0x8]
	ldr r3, [r1, #0x0]
	ldrh r1, [lr, #0x6]
	mov r12, r3, asr #0xc
	mov r3, #0x1
	mla r2, r12, r1, r2
	mov r1, r2, lsr #0x5
	add r1, lr, r1, lsl #0x2
	ldr r1, [r1, #0xc]
	and r2, r2, #0x1f
	and r1, r1, r3, lsl r2
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end FUN_020BE5A0

	; NNSi_G3dAnmObjInitNsBva
	arm_func_start FUN_020BE5E0
FUN_020BE5E0: ; 0x020BE5E0
	ldr r3, _020BE628 ; =UNK_02106598
	mov r12, #0x0
	ldr r3, [r3, #0x0]
	str r3, [r0, #0xc]
	ldrb r2, [r2, #0x17]
	strb r2, [r0, #0x19]
	str r1, [r0, #0x8]
	ldrb r1, [r0, #0x19]
	cmp r1, #0x0
	bxls lr
_020BE608:
	orr r2, r12, #0x100
	add r1, r0, r12, lsl #0x1
	strh r2, [r1, #0x1a]
	ldrb r1, [r0, #0x19]
	add r12, r12, #0x1
	cmp r12, r1
	blo _020BE608
	bx lr
	.balign 4
_020BE628: .word UNK_02106598
	arm_func_end FUN_020BE5E0

