	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020BE62C
FUN_020BE62C: ; 0x020BE62C
	ands r2, r3, #0x4
	ldrne r1, [r0, #0x0]
	orrne r1, r1, #0x1
	strne r1, [r0, #0x0]
	bne _020BE658
	ldr r2, [r1, #0x0]
	str r2, [r0, #0x4]
	ldr r2, [r1, #0x4]
	str r2, [r0, #0x8]
	ldr r1, [r1, #0x8]
	str r1, [r0, #0xc]
_020BE658:
	ldr r1, [r0, #0x0]
	orr r1, r1, #0x18
	str r1, [r0, #0x0]
	bx lr
	arm_func_end FUN_020BE62C

	; _end
	arm_func_start FUN_020BE668
FUN_020BE668: ; 0x020BE668
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x0]
	ands r0, r1, #0x4
	bne _020BE6AC
	ands r0, r1, #0x2
	bne _020BE698
	add r1, r4, #0x28
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020BE6C4
_020BE698:
	add r1, r4, #0x4c
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
	b _020BE6C4
_020BE6AC:
	ands r0, r1, #0x2
	bne _020BE6C4
	add r1, r4, #0x28
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
_020BE6C4:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x1
	ldmneia sp!, {r4,pc}
	add r1, r4, #0x4
	mov r0, #0x1b
	mov r2, #0x3
	bl FUN_020BB1C0
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020BE668

