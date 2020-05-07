	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD13_0221E560
MOD13_0221E560: ; 0x0221E560
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _0221E640 ; =0x02242FE4
	mov r1, #0x28
	ldr r0, [r0]
	ldrb r0, [r0, #9]
	add r0, r0, #1
	bl FX_ModS32
	ldr r2, _0221E640 ; =0x02242FE4
	mov r1, #5
	ldr r3, [r2]
	strb r0, [r3, #9]
	ldr r0, [r2]
	ldrb r0, [r0, #9]
	bl FX_DivS32
	ldr r2, _0221E640 ; =0x02242FE4
	add r1, r0, #0x47
	ldr r2, [r2]
	mov r0, #0
	ldr r2, [r2, #4]
	bl MOD13_02239E8C
	ldr r3, _0221E640 ; =0x02242FE4
	ldr lr, _0221E644 ; =0x0223EC6C
	ldr r0, [r3]
	ldr r2, _0221E648 ; =0x0223EC70
	ldr r5, [r0, #4]
	ldr r1, _0221E64C ; =0xFE00FF00
	ldrh r4, [r5, #4]
	ldr r0, _0221E650 ; =0x000001FF
	bic r4, r4, #0xc00
	orr r4, r4, #0x400
	strh r4, [r5, #4]
	ldr r4, [r3]
	ldrb r5, [r4, #8]
	ldr ip, [r4, #4]
	ldr r4, [ip]
	ldrb lr, [lr, r5]
	bic r4, r4, #0xc00
	str r4, [ip]
	ldrh r4, [ip, #4]
	bic r4, r4, #0xf000
	orr r4, r4, lr, lsl #12
	strh r4, [ip, #4]
	ldr r4, [r3]
	ldrh r3, [r2, #2]
	ldr r4, [r4, #4]
	ldrh lr, [r2]
	ldr ip, [r4]
	and r2, r3, #0xff
	and r1, ip, r1
	and r3, lr, r0
	orr r0, r1, r2
	orr r0, r0, r3, lsl #16
	str r0, [r4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0221E640: .word 0x02242FE4
_0221E644: .word 0x0223EC6C
_0221E648: .word 0x0223EC70
_0221E64C: .word 0xFE00FF00
_0221E650: .word 0x000001FF

	arm_func_start MOD13_0221E654
MOD13_0221E654: ; 0x0221E654
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0221E690 ; =0x02242FE4
	mov r0, #1
	ldr r1, [r1]
	ldr r1, [r1]
	bl MOD13_0223C104
	ldr r0, _0221E690 ; =0x02242FE4
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD13_0223B974
	ldr r0, _0221E690 ; =0x02242FE4
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221E690: .word 0x02242FE4

	arm_func_start MOD13_0221E694
MOD13_0221E694: ; 0x0221E694
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov r4, r0
	mov r0, #0xc
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r2, _0221E774 ; =0x02242FE4
	mov r1, #0x47
	str r0, [r2]
	strb r4, [r0, #8]
	mov r0, #0
	bl MOD13_02239E54
	ldr r7, _0221E774 ; =0x02242FE4
	ldr r8, _0221E778 ; =0x0223EC6C
	ldr r1, [r7]
	ldr r6, _0221E77C ; =0x0223EC70
	str r0, [r1, #4]
	ldr r0, [r7]
	ldr lr, _0221E780 ; =0x000001FF
	ldr r3, [r0, #4]
	ldr r5, _0221E784 ; =0xFE00FF00
	ldrh r2, [r3, #4]
	mov r0, #1
	ldr r1, _0221E788 ; =MOD13_0221E560
	bic r2, r2, #0xc00
	orr r2, r2, #0x400
	strh r2, [r3, #4]
	ldr r3, [r7]
	mov r2, #0
	ldr ip, [r3, #4]
	mov r3, #0x78
	ldr sb, [ip]
	bic sb, sb, #0xc00
	str sb, [ip]
	ldrb r4, [r8, r4]
	ldrh r8, [ip, #4]
	bic r8, r8, #0xf000
	orr r4, r8, r4, lsl #12
	strh r4, [ip, #4]
	ldr r4, [r7]
	ldrh r7, [r6]
	ldr ip, [r4, #4]
	ldrh r4, [r6, #2]
	and r7, r7, lr
	ldr r6, [ip]
	and r4, r4, #0xff
	and r5, r6, r5
	orr r4, r5, r4
	orr r4, r4, r7, lsl #16
	str r4, [ip]
	bl MOD13_0223C1C4
	ldr r1, _0221E774 ; =0x02242FE4
	ldr r1, [r1]
	str r0, [r1]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_0221E774: .word 0x02242FE4
_0221E778: .word 0x0223EC6C
_0221E77C: .word 0x0223EC70
_0221E780: .word 0x000001FF
_0221E784: .word 0xFE00FF00
_0221E788: .word MOD13_0221E560

	arm_func_start MOD13_0221E78C
MOD13_0221E78C: ; 0x0221E78C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	ldr r4, _0221E888 ; =0x02242FE8
	str r0, [sp]
	ldr r1, [r4]
	ldrh r0, [r1, #0x14]
	add r0, r0, #1
	strh r0, [r1, #0x14]
	ldr r1, [r4]
	ldrh r0, [r1, #0x14]
	cmp r0, #0x10
	addlo sp, sp, #4
	ldmloia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldrb r1, [r1, #0x17]
	ldr r0, _0221E88C ; =0x0223EC7C
	mov sb, #0
	ldrb sl, [r0, r1]
	cmp sl, #0
	ble _0221E838
	mov r7, sb
	mov fp, sb
	mvn r6, #0
	mov r5, #1
_0221E7E8:
	ldr r0, [r4]
	ldr r2, _0221E890 ; =0x0223EC8C
	ldrb r3, [r0, #0x17]
	ldr r0, [r0, sb, lsl #2]
	mov r1, r7
	add r2, r2, r3, lsl #1
	ldrb r8, [sb, r2]
	bl MOD13_02239ADC
	mov r2, r0
	mov r1, r8
	mov r0, fp
	bl MOD13_02239E8C
	ldr r0, [r4]
	mov r1, r6
	ldr r0, [r0, sb, lsl #2]
	mov r2, r5
	bl MOD13_02239814
	add sb, sb, #1
	cmp sb, sl
	blt _0221E7E8
_0221E838:
	ldr r0, _0221E894 ; =0x0223EC74
	ldrh r0, [r0, #2]
	bl MOD13_0221EBD8
	ldr r1, _0221E888 ; =0x02242FE8
	mov r0, #0
	ldr r2, [r1]
	mvn r3, #0
	strh r0, [r2, #0x14]
	ldr r2, [r1]
	strb r3, [r2, #0x16]
	ldr r2, [r1]
	ldr r1, [r2, #0x10]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r1, [sp]
	str r0, [r2, #0x10]
	bl MOD13_0223C110
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_0221E888: .word 0x02242FE8
_0221E88C: .word 0x0223EC7C
_0221E890: .word 0x0223EC8C
_0221E894: .word 0x0223EC74

	arm_func_start MOD13_0221E898
MOD13_0221E898: ; 0x0221E898
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r1, r0
	mov r0, #0
	bl MOD13_0223C110
	ldr r0, _0221E910 ; =0x02242FE8
	ldr r0, [r0]
	ldr r1, [r0, #0x10]
	cmp r1, #0
	beq _0221E8C8
	mov r0, #0
	bl MOD13_0223C110
_0221E8C8:
	ldr r4, _0221E910 ; =0x02242FE8
	mov r5, #0
_0221E8D0:
	ldr r0, [r4]
	ldr r0, [r0, r5, lsl #2]
	cmp r0, #0
	beq _0221E8E4
	bl MOD13_02239AE8
_0221E8E4:
	add r5, r5, #1
	cmp r5, #2
	blt _0221E8D0
	ldr r0, _0221E910 ; =0x02242FE8
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl MOD13_02239AE8
	ldr r0, _0221E910 ; =0x02242FE8
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0221E910: .word 0x02242FE8

	arm_func_start MOD13_0221E914
MOD13_0221E914: ; 0x0221E914
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221E970 ; =0x02242FE8
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #8]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, [sp, #4]
	add r0, r0, #4
	str r0, [sp, #4]
	bl MOD13_0221EBD8
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0221E974 ; =MOD13_0221E898
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221E970: .word 0x02242FE8
_0221E974: .word MOD13_0221E898

	arm_func_start MOD13_0221E978
MOD13_0221E978: ; 0x0221E978
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #8
	ldr r8, _0221EAE8 ; =0x02242FE8
	ldr r1, _0221EAEC ; =0x0223EC7C
	ldr r3, [r8]
	ldrb r2, [r3, #0x17]
	ldrb r0, [r3, #0x18]
	ldrb r7, [r1, r2]
	cmp r0, #0
	bne _0221EAD0
	ldrsb r1, [r3, #0x16]
	mvn r0, #0
	cmp r1, r0
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	cmp r7, #0
	mov r6, #0
	ble _0221EAD0
	ldr r5, _0221EAF0 ; =0x0223EC84
	ldr r4, _0221EAF4 ; =0x0223EC9C
	ldr sl, _0221EAF8 ; =0x0223EC78
	add sb, sp, #0
_0221E9D0:
	ldr r0, [r8]
	mov r1, sl
	ldrb r0, [r0, #0x17]
	mov r2, sb
	add r0, r4, r0, lsl #1
	ldrb r0, [r6, r0]
	add r0, r5, r0, lsl #2
	bl MOD13_0223AB74
	mov r0, sb
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _0221EAC4
	ldr r0, _0221EAE8 ; =0x02242FE8
	ldr r3, [r0]
	ldr r0, [r3, #0x10]
	cmp r0, #0
	bne _0221EAD0
	ldrb r2, [r3, #0x17]
	ldr r1, _0221EAFC ; =0x0223EC8C
	ldr r0, [r3, r6, lsl #2]
	add r1, r1, r2, lsl #1
	ldrb r2, [r6, r1]
	mov r1, #0
	add r4, r2, #1
	bl MOD13_02239ADC
	mov r2, r0
	mov r1, r4
	mov r0, #0
	bl MOD13_02239E8C
	ldr r0, _0221EAE8 ; =0x02242FE8
	ldr r1, _0221EAF4 ; =0x0223EC9C
	ldr r0, [r0]
	ldr r2, _0221EAF0 ; =0x0223EC84
	ldrb r4, [r0, #0x17]
	ldr r3, _0221EB00 ; =0x0223EC86
	ldr r0, [r0, r6, lsl #2]
	add r1, r1, r4, lsl #1
	ldrb r4, [r6, r1]
	mvn r1, #0
	mov r4, r4, lsl #2
	ldrh r2, [r2, r4]
	ldrh r3, [r3, r4]
	bl MOD13_02239888
	ldr r0, _0221EAE8 ; =0x02242FE8
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #1
	ldr r0, [r0, r6, lsl #2]
	bl MOD13_02239814
	mov r0, #0
	ldr r1, _0221EB04 ; =MOD13_0221E78C
	mov r2, r0
	mov r3, #0x6e
	bl MOD13_0223C1C4
	ldr r1, _0221EAE8 ; =0x02242FE8
	add sp, sp, #8
	ldr r2, [r1]
	str r0, [r2, #0x10]
	ldr r0, [r1]
	strb r6, [r0, #0x16]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_0221EAC4:
	add r6, r6, #1
	cmp r6, r7
	blt _0221E9D0
_0221EAD0:
	ldr r0, _0221EAE8 ; =0x02242FE8
	mvn r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x16]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_0221EAE8: .word 0x02242FE8
_0221EAEC: .word 0x0223EC7C
_0221EAF0: .word 0x0223EC84
_0221EAF4: .word 0x0223EC9C
_0221EAF8: .word 0x0223EC78
_0221EAFC: .word 0x0223EC8C
_0221EB00: .word 0x0223EC86
_0221EB04: .word MOD13_0221E78C

	arm_func_start MOD13_0221EB08
MOD13_0221EB08: ; 0x0221EB08
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0221EB5C ; =0x02242FE8
	mvn r3, #0
	ldr r2, [r1]
	strb r3, [r2, #0x16]
	ldr r3, [r1]
	ldrh r2, [r3, #0x14]
	add r2, r2, #1
	strh r2, [r3, #0x14]
	ldr r3, [r1]
	ldrh r1, [r3, #0x14]
	cmp r1, #4
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	ldr r1, _0221EB60 ; =MOD13_0221E978
	mov r2, #0
	strh r2, [r3, #0x14]
	bl MOD13_0223C130
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221EB5C: .word 0x02242FE8
_0221EB60: .word MOD13_0221E978

	arm_func_start MOD13_0221EB64
MOD13_0221EB64: ; 0x0221EB64
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221EBCC ; =0x02242FE8
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #8]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, [sp, #4]
	sub r0, r0, #4
	str r0, [sp, #4]
	bl MOD13_0221EBD8
	ldr r0, _0221EBD0 ; =0x0223EC74
	ldr r1, [sp, #4]
	ldrh r0, [r0, #2]
	cmp r1, r0
	addgt sp, sp, #8
	ldmgtia sp!, {r4, pc}
	bl MOD13_0221EBD8
	ldr r1, _0221EBD4 ; =MOD13_0221EB08
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221EBCC: .word 0x02242FE8
_0221EBD0: .word 0x0223EC74
_0221EBD4: .word MOD13_0221EB08

	arm_func_start MOD13_0221EBD8
MOD13_0221EBD8: ; 0x0221EBD8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	ldr r2, _0221EC70 ; =0x02242FE8
	ldr r3, _0221EC74 ; =0x0223EC7C
	ldr r6, [r2]
	ldr r2, _0221EC78 ; =0x0223EC84
	ldrb r4, [r6, #0x17]
	ldrh r2, [r2, #2]
	ldr r1, _0221EC7C ; =0x0223EC74
	ldrb r8, [r3, r4]
	mov r3, r0
	add r5, r3, r2
	ldrh r4, [r1, #2]
	ldrh r2, [r1]
	ldr r0, [r6, #8]
	mvn r1, #0
	sub r7, r5, r4
	bl MOD13_02239888
	mov r6, #0
	cmp r8, #0
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldr sb, _0221EC70 ; =0x02242FE8
	ldr r4, _0221EC80 ; =0x0223EC9C
	ldr sl, _0221EC78 ; =0x0223EC84
	mvn r5, #0
_0221EC38:
	ldr r0, [sb]
	mov r1, r5
	ldrb r2, [r0, #0x17]
	ldr r0, [r0, r6, lsl #2]
	mov r3, r7
	add r2, r4, r2, lsl #1
	ldrb r2, [r6, r2]
	mov r2, r2, lsl #2
	ldrh r2, [sl, r2]
	bl MOD13_02239888
	add r6, r6, #1
	cmp r6, r8
	blt _0221EC38
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_0221EC70: .word 0x02242FE8
_0221EC74: .word 0x0223EC7C
_0221EC78: .word 0x0223EC84
_0221EC7C: .word 0x0223EC74
_0221EC80: .word 0x0223EC9C

	arm_func_start MOD13_0221EC84
MOD13_0221EC84: ; 0x0221EC84
	ldr r0, _0221EC98 ; =0x02242FE8
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x18]
	bx lr
	.align 2, 0
_0221EC98: .word 0x02242FE8

	arm_func_start MOD13_0221EC9C
MOD13_0221EC9C: ; 0x0221EC9C
	ldr r0, _0221ECB0 ; =0x02242FE8
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x18]
	bx lr
	.align 2, 0
_0221ECB0: .word 0x02242FE8

	arm_func_start MOD13_0221ECB4
MOD13_0221ECB4: ; 0x0221ECB4
	ldr r0, _0221ECDC ; =0x02242FE8
	ldr r0, [r0]
	cmp r0, #0
	moveq r0, #1
	bxeq lr
	ldrb r0, [r0, #0x19]
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_0221ECDC: .word 0x02242FE8

	arm_func_start MOD13_0221ECE0
MOD13_0221ECE0: ; 0x0221ECE0
	ldr r1, _0221ECF0 ; =0x02242FE8
	ldr r1, [r1]
	strb r0, [r1, #0x16]
	bx lr
	.align 2, 0
_0221ECF0: .word 0x02242FE8

	arm_func_start MOD13_0221ECF4
MOD13_0221ECF4: ; 0x0221ECF4
	ldr r2, _0221ED10 ; =0x02242FE8
	mvn r1, #0
	ldr r3, [r2]
	ldrsb r2, [r3, #0x16]
	cmp r2, r1
	streqb r0, [r3, #0x16]
	bx lr
	.align 2, 0
_0221ED10: .word 0x02242FE8

	arm_func_start MOD13_0221ED14
MOD13_0221ED14: ; 0x0221ED14
	ldr r0, _0221ED24 ; =0x02242FE8
	ldr r0, [r0]
	ldrsb r0, [r0, #0x16]
	bx lr
	.align 2, 0
_0221ED24: .word 0x02242FE8

	arm_func_start MOD13_0221ED28
MOD13_0221ED28: ; 0x0221ED28
	ldr r0, _0221ED4C ; =0x02242FE8
	mov r3, #1
	ldr r2, [r0]
	ldr ip, _0221ED50 ; =MOD13_0223C130
	strb r3, [r2, #0x19]
	ldr r0, [r0]
	ldr r1, _0221ED54 ; =MOD13_0221E914
	ldr r0, [r0, #0xc]
	bx ip
	.align 2, 0
_0221ED4C: .word 0x02242FE8
_0221ED50: .word MOD13_0223C130
_0221ED54: .word MOD13_0221E914

	arm_func_start MOD13_0221ED58
MOD13_0221ED58: ; 0x0221ED58
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	ldr r2, _0221EE44 ; =0x0223EC7C
	mov r4, r0
	mov r0, #0x1c
	mov r1, #4
	ldrb r8, [r2, r4]
	bl MOD13_0223AFE0
	ldr sb, _0221EE48 ; =0x02242FE8
	mvn r1, #1
	str r0, [sb]
	strb r1, [r0, #0x16]
	ldr r0, [sb]
	cmp r8, #0
	strb r4, [r0, #0x17]
	mov r7, #0
	ble _0221EDE8
	ldr r0, _0221EE4C ; =0x0223EC8C
	add r6, r0, r4, lsl #1
	mov r5, r7
	mov r4, #1
	mvn sl, #0
_0221EDAC:
	ldrb r1, [r6]
	mov r0, r5
	mov r2, r4
	bl MOD13_02239E0C
	ldr r2, [sb]
	mov r1, sl
	str r0, [r2, r7, lsl #2]
	ldr r0, [sb]
	mov r2, r4
	ldr r0, [r0, r7, lsl #2]
	bl MOD13_02239814
	add r7, r7, #1
	cmp r7, r8
	add r6, r6, #1
	blt _0221EDAC
_0221EDE8:
	mov r1, #1
	mov r2, r1
	mov r0, #0
	bl MOD13_02239E0C
	ldr r3, _0221EE48 ; =0x02242FE8
	mvn r1, #0
	ldr r4, [r3]
	mov r2, #1
	str r0, [r4, #8]
	ldr r0, [r3]
	ldr r0, [r0, #8]
	bl MOD13_02239814
	mov r0, #0xc0
	bl MOD13_0221EBD8
	mov r0, #0
	ldr r1, _0221EE50 ; =MOD13_0221EB64
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0221EE48 ; =0x02242FE8
	ldr r1, [r1]
	str r0, [r1, #0xc]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_0221EE44: .word 0x0223EC7C
_0221EE48: .word 0x02242FE8
_0221EE4C: .word 0x0223EC8C
_0221EE50: .word MOD13_0221EB64

	arm_func_start MOD13_0221EE54
MOD13_0221EE54: ; 0x0221EE54
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0221EE94 ; =0x02242FEC
	ldrb r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	mov r0, #1
	bl MOD13_0223A65C
	ldr r0, _0221EE94 ; =0x02242FEC
	mov r1, #0
	strb r1, [r0]
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221EE94: .word 0x02242FEC

	arm_func_start MOD13_0221EE98
MOD13_0221EE98: ; 0x0221EE98
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x14
	ldr r3, _0221EF58 ; =0x02242FEC
	mov r7, r0
	ldrb r0, [r3]
	mov r6, r1
	mov r5, r2
	cmp r0, #0
	addne sp, sp, #0x14
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _0221EF5C ; =0x0223F934
	ldr r1, _0221EF60 ; =0x020C91C4
	bl MOD13_0221F174
	ldr r3, _0221EF64 ; =0x01920000
	ldr r2, _0221EF68 ; =0x04001010
	mov r0, #1
	mov r1, #0
	str r3, [r2]
	bl MOD13_0223A7F0
	ldr r1, _0221EF6C ; =0x0224307C
	mov r4, r0
	ldr r0, [r1]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl MOD13_0222352C
	mov r5, r0
	bl MOD13_0221EF88
	ldr r3, _0221EF70 ; =0x0223ECAC
	mov r1, #2
	ldrh r2, [r3, #6]
	str r2, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	mov r0, r4
	ldrh r1, [r3]
	ldrh r2, [r3, #2]
	ldrh r3, [r3, #4]
	bl MOD13_0223A4F0
	mov r0, r4
	bl MOD13_0223A410
	mov r0, #1
	ldr r1, _0221EF58 ; =0x02242FEC
	strb r0, [r1]
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0221EF58: .word 0x02242FEC
_0221EF5C: .word 0x0223F934
_0221EF60: .word 0x020C91C4
_0221EF64: .word 0x01920000
_0221EF68: .word 0x04001010
_0221EF6C: .word 0x0224307C
_0221EF70: .word 0x0223ECAC

	arm_func_start MOD13_0221EF74
MOD13_0221EF74: ; 0x0221EF74
	ldr r0, _0221EF84 ; =0x02242FEC
	mov r1, #0
	strb r1, [r0]
	bx lr
	.align 2, 0
_0221EF84: .word 0x02242FEC

	arm_func_start MOD13_0221EF88
MOD13_0221EF88: ; 0x0221EF88
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02222F34
	ldr r1, _0221EFA4 ; =0x0223ECCC
	ldr r0, [r1, r0, lsl #2]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221EFA4: .word 0x0223ECCC

	arm_func_start MOD13_0221EFA8
MOD13_0221EFA8: ; 0x0221EFA8
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	mov r5, r0
	mov r0, #0
	mov r6, r1
	mov r1, r0
	bl MOD13_0223A7F0
	ldr r1, _0221F05C ; =0x0224307C
	mov r4, r0
	ldr r0, [r1]
	mov r1, r6
	bl MOD13_02223568
	mov r6, r0
	bl MOD13_0221EF88
	ldr r3, _0221F060 ; =0x0223ECC4
	mov r1, #2
	ldrh r2, [r3, #6]
	str r2, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r6, [sp, #0xc]
	ldrh r1, [r3]
	ldrh r2, [r3, #2]
	ldrh r3, [r3, #4]
	mov r0, r4
	bl MOD13_0223A4F0
	bl MOD13_02222F34
	mov r6, r0
	bl MOD13_02222F34
	ldr r1, _0221F064 ; =0x00000209
	mov r3, r0, lsl #2
	str r1, [sp]
	ldr r1, _0221F068 ; =0x0223ECE4
	ldr r2, _0221F06C ; =0x0223ECE6
	str r5, [sp, #4]
	mov ip, r6, lsl #2
	ldrh r2, [r2, r3]
	ldrh r1, [r1, ip]
	mov r0, r4
	mov r3, #2
	bl MOD13_0223A634
	mov r0, r4
	bl MOD13_0223A410
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0221F05C: .word 0x0224307C
_0221F060: .word 0x0223ECC4
_0221F064: .word 0x00000209
_0221F068: .word 0x0223ECE4
_0221F06C: .word 0x0223ECE6

	arm_func_start MOD13_0221F070
MOD13_0221F070: ; 0x0221F070
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x14
	mov r4, r0
	mov r0, #0
	mov r1, r0
	bl MOD13_0223A7F0
	ldr r1, _0221F0E4 ; =0x0224307C
	mov r5, r0
	ldr r0, [r1]
	mov r1, r4
	bl MOD13_02223568
	mov r4, r0
	bl MOD13_0221EF88
	ldr r3, _0221F0E8 ; =0x0223ECBC
	mov r1, #2
	ldrh r2, [r3, #6]
	str r2, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r4, [sp, #0xc]
	mov r0, r5
	ldrh r1, [r3]
	ldrh r2, [r3, #2]
	ldrh r3, [r3, #4]
	bl MOD13_0223A4F0
	mov r0, r5
	bl MOD13_0223A410
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0221F0E4: .word 0x0224307C
_0221F0E8: .word 0x0223ECBC

	arm_func_start MOD13_0221F0EC
MOD13_0221F0EC: ; 0x0221F0EC
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F80
	ldr r0, [sp]
	cmp r0, #1
	addne sp, sp, #8
	ldmneia sp!, {r4, pc}
	mov r0, r4
	bl MOD13_0221ED58
	add sp, sp, #8
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0221F124
MOD13_0221F124: ; 0x0221F124
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	add r0, sp, #0
	mov r1, #0
	bl MOD13_02222F80
	ldr r0, [sp]
	cmp r0, #1
	bne _0221F158
	mov r0, r4
	bl MOD13_02234DC0
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0221F158:
	cmp r0, #2
	addne sp, sp, #8
	ldmneia sp!, {r4, pc}
	mov r0, r4
	bl MOD13_02234820
	add sp, sp, #8
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0221F174
MOD13_0221F174: ; 0x0221F174
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r1
	bl MOD13_0221F1BC
	add r1, sp, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, [sp]
	mov r4, r0
	bl DC_FlushRange
	ldr r2, [sp]
	mov r0, r4
	mov r1, #0
	blx r5
	mov r0, r4
	bl MOD13_0223939C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}

	arm_func_start MOD13_0221F1BC
MOD13_0221F1BC: ; 0x0221F1BC
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, _0221F214 ; =0x02242FF0
	mov r1, r4
	mov r2, #0x3f
	bl strncpy
	ldrb r0, [r4, #5]
	cmp r0, #0x78
	ldreq r0, _0221F214 ; =0x02242FF0
	ldmeqia sp!, {r4, pc}
	bl MOD13_02222F34
	ldrb r1, [r4, #5]
	cmp r1, #0x79
	bne _0221F200
	cmp r0, #0
	ldrne r0, _0221F214 ; =0x02242FF0
	ldmneia sp!, {r4, pc}
_0221F200:
	ldr r1, _0221F218 ; =0x0223ECB4
	ldrb r1, [r1, r0]
	ldr r0, _0221F214 ; =0x02242FF0
	strb r1, [r0, #5]
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221F214: .word 0x02242FF0
_0221F218: .word 0x0223ECB4

	arm_func_start MOD13_0221F21C
MOD13_0221F21C: ; 0x0221F21C
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, #0
	ldr r4, _0221F258 ; =0x02243030
	mov r5, r6
_0221F22C:
	ldr r0, [r4]
	ldr r0, [r0, r6, lsl #2]
	cmp r0, #0
	beq _0221F248
	bl MOD13_02239AE8
	ldr r0, [r4]
	str r5, [r0, r6, lsl #2]
_0221F248:
	add r6, r6, #1
	cmp r6, #4
	blt _0221F22C
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0221F258: .word 0x02243030

	arm_func_start MOD13_0221F25C
MOD13_0221F25C: ; 0x0221F25C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov sl, r0
	mov fp, r1
	str r2, [sp]
	str r3, [sp, #4]
	mov sb, #6
	bl MOD13_0221F21C
	mov r8, #0
	ldr r4, _0221F344 ; =0x02243030
	mov r7, r8
	mov r6, #1
	mvn r5, #0
_0221F290:
	mov r0, r7
	mov r1, sb
	mov r2, r6
	bl MOD13_02239E0C
	ldr r2, [r4]
	mov r1, r5
	str r0, [r2, r8, lsl #2]
	ldr r0, [r4]
	mov r2, r6
	ldr r0, [r0, r8, lsl #2]
	bl MOD13_02239814
	add r8, r8, #1
	cmp r8, #4
	add sb, sb, #1
	blt _0221F290
	ldr r0, _0221F344 ; =0x02243030
	ldr r3, [sp]
	ldr r0, [r0]
	mov r2, sl
	ldr r0, [r0]
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _0221F344 ; =0x02243030
	ldr r3, [sp]
	ldr r0, [r0]
	mov r2, fp
	ldr r0, [r0, #4]
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _0221F344 ; =0x02243030
	ldr r3, [sp, #4]
	ldr r0, [r0]
	mov r2, sl
	ldr r0, [r0, #8]
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _0221F344 ; =0x02243030
	ldr r3, [sp, #4]
	ldr r0, [r0]
	mov r2, fp
	ldr r0, [r0, #0xc]
	mvn r1, #0
	bl MOD13_02239888
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_0221F344: .word 0x02243030

	arm_func_start MOD13_0221F348
MOD13_0221F348: ; 0x0221F348
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov r4, r0
	mov fp, r1
	str r2, [sp]
	mov sl, r3
	bl MOD13_0221F21C
	ldr r0, _0221F3FC ; =0x0223ECFC
	mov sb, #0
	add r8, r0, r4, lsl #1
	ldr r4, _0221F400 ; =0x02243030
	mov r7, sb
	mov r6, #1
	mvn r5, #0
_0221F380:
	ldrb r1, [r8]
	mov r0, r7
	mov r2, r6
	bl MOD13_02239E0C
	ldr r2, [r4]
	mov r1, r5
	str r0, [r2, sb, lsl #2]
	ldr r0, [r4]
	mov r2, r6
	ldr r0, [r0, sb, lsl #2]
	bl MOD13_02239814
	add sb, sb, #1
	cmp sb, #2
	add r8, r8, #1
	blt _0221F380
	ldr r0, _0221F400 ; =0x02243030
	mov r2, fp
	ldr r0, [r0]
	mov r3, sl
	ldr r0, [r0]
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _0221F400 ; =0x02243030
	ldr r2, [sp]
	ldr r0, [r0]
	mov r3, sl
	ldr r0, [r0, #4]
	mvn r1, #0
	bl MOD13_02239888
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_0221F3FC: .word 0x0223ECFC
_0221F400: .word 0x02243030

	arm_func_start MOD13_0221F404
MOD13_0221F404: ; 0x0221F404
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221F21C
	ldr r0, _0221F420 ; =0x02243030
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221F420: .word 0x02243030

	arm_func_start MOD13_0221F424
MOD13_0221F424: ; 0x0221F424
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x10
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, _0221F448 ; =0x02243030
	str r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221F448: .word 0x02243030

	arm_func_start MOD13_0221F44C
MOD13_0221F44C: ; 0x0221F44C
	stmdb sp!, {r4, lr}
	ldr r1, _0221F488 ; =0x02243034
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0xc0
	bl DC_FlushRange
	ldr r0, _0221F488 ; =0x02243034
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0xc0
	bl GX_LoadBG1Scr
	mov r1, r4
	mov r0, #1
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221F488: .word 0x02243034

	arm_func_start MOD13_0221F48C
MOD13_0221F48C: ; 0x0221F48C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02234164
	ldrb r0, [r0, #0xf4]
	add r0, r0, #2
	bl MOD13_0221F4CC
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0221F4AC
MOD13_0221F4AC: ; 0x0221F4AC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02234164
	ldrb r0, [r0, #0xf4]
	add r0, r0, #5
	bl MOD13_0221F4CC
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0221F4CC
MOD13_0221F4CC: ; 0x0221F4CC
	stmdb sp!, {r4, lr}
	ldr r1, _0221F51C ; =0x0223FB18
	ldr r0, [r1, r0, lsl #2]
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _0221F520 ; =0x02243034
	mov r4, r0
	ldr r1, [r1]
	mov r2, #0xc0
	bl MIi_CpuCopyFast
	mov r0, r4
	bl MOD13_0223939C
	mov r0, #1
	ldr r1, _0221F524 ; =MOD13_0221F44C
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221F51C: .word 0x0223FB18
_0221F520: .word 0x02243034
_0221F524: .word MOD13_0221F44C

	arm_func_start MOD13_0221F528
MOD13_0221F528: ; 0x0221F528
	ldr ip, _0221F534 ; =MOD13_0223AF90
	ldr r0, _0221F538 ; =0x02243034
	bx ip
	.align 2, 0
_0221F534: .word MOD13_0223AF90
_0221F538: .word 0x02243034

	arm_func_start MOD13_0221F53C
MOD13_0221F53C: ; 0x0221F53C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0xc0
	mov r1, #4
	bl MOD13_0223B004
	ldr r2, _0221F5B0 ; =0x02243034
	ldr r1, _0221F5B4 ; =0x020C8E1C
	str r0, [r2]
	ldr r0, _0221F5B8 ; =0x0223FB68
	bl MOD13_0221F174
	bl MOD13_02222F1C
	cmp r0, #0
	beq _0221F580
	cmp r0, #1
	beq _0221F598
	add sp, sp, #4
	ldmia sp!, {pc}
_0221F580:
	ldr r0, _0221F5BC ; =0x0223FB18
	ldr r1, _0221F5C0 ; =0x020C915C
	ldr r0, [r0]
	bl MOD13_0221F174
	add sp, sp, #4
	ldmia sp!, {pc}
_0221F598:
	ldr r0, _0221F5BC ; =0x0223FB18
	ldr r1, _0221F5C0 ; =0x020C915C
	ldr r0, [r0, #4]
	bl MOD13_0221F174
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221F5B0: .word 0x02243034
_0221F5B4: .word 0x020C8E1C
_0221F5B8: .word 0x0223FB68
_0221F5BC: .word 0x0223FB18
_0221F5C0: .word 0x020C915C

	arm_func_start MOD13_0221F5C4
MOD13_0221F5C4: ; 0x0221F5C4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _0221F67C ; =0x04000208
	mov r4, #0
	ldrh r5, [r0]
	strh r4, [r0]
	bl WM_GetAllowedChannel
	cmp r0, #0x8000
	beq _0221F5F0
	bl WM_GetLinkLevel
	mov r4, r0
_0221F5F0:
	ldr r2, _0221F67C ; =0x04000208
	ldr r1, _0221F680 ; =0x02243038
	ldrh r0, [r2]
	ldr r3, _0221F684 ; =0x0223ED08
	mov r0, #0
	strh r5, [r2]
	ldr r2, [r1]
	ldrsb r1, [r2, #8]
	ldr r2, [r2]
	add r1, r3, r1, lsl #2
	ldrb r1, [r4, r1]
	bl MOD13_02239E8C
	ldr r0, _0221F688 ; =0x0223ED04
	ldr r2, _0221F680 ; =0x02243038
	ldrh r3, [r0, #2]
	ldr r1, [r2]
	ldrh ip, [r0]
	ldr lr, [r1]
	ldr r0, _0221F68C ; =0x000001FF
	ldr r4, [lr]
	ldr r1, _0221F690 ; =0xFE00FF00
	and r3, r3, #0xff
	and r1, r4, r1
	and r4, ip, r0
	orr r0, r1, r3
	orr r0, r0, r4, lsl #16
	str r0, [lr]
	ldr r0, [r2]
	ldr r1, [r0]
	ldrh r0, [r1, #4]
	bic r0, r0, #0xc00
	orr r0, r0, #0x800
	strh r0, [r1, #4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0221F67C: .word 0x04000208
_0221F680: .word 0x02243038
_0221F684: .word 0x0223ED08
_0221F688: .word 0x0223ED04
_0221F68C: .word 0x000001FF
_0221F690: .word 0xFE00FF00

	arm_func_start MOD13_0221F694
MOD13_0221F694: ; 0x0221F694
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0221F6DC ; =0x02243038
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r1, [r0, #4]
	mov r0, #0
	bl MOD13_0223C104
	ldr r0, _0221F6DC ; =0x02243038
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD13_0223B974
	ldr r0, _0221F6DC ; =0x02243038
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221F6DC: .word 0x02243038

	arm_func_start MOD13_0221F6E0
MOD13_0221F6E0: ; 0x0221F6E0
	stmdb sp!, {r4, lr}
	ldr r1, _0221F7A0 ; =0x02243038
	mov r4, r0
	ldr r0, [r1]
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	mov r0, #0xc
	mov r1, #4
	bl MOD13_0223B004
	ldr r1, _0221F7A0 ; =0x02243038
	ldr r2, _0221F7A4 ; =0x0223ED08
	str r0, [r1]
	strb r4, [r0, #8]
	ldrb r1, [r2, r4, lsl #2]
	mov r0, #0
	bl MOD13_02239E54
	ldr r3, _0221F7A0 ; =0x02243038
	ldr r2, _0221F7A8 ; =0x0223ED04
	ldr r4, [r3]
	ldr r1, _0221F7AC ; =0xFE00FF00
	str r0, [r4]
	ldr r4, [r3]
	ldrh r0, [r2, #2]
	ldr r4, [r4]
	ldrh lr, [r2]
	ldr ip, [r4]
	and r2, r0, #0xff
	and r1, ip, r1
	ldr r0, _0221F7B0 ; =0x000001FF
	orr r1, r1, r2
	and r0, lr, r0
	orr r0, r1, r0, lsl #16
	str r0, [r4]
	ldr r1, [r3]
	mov r0, #0
	ldr lr, [r1]
	ldr r1, _0221F7B4 ; =MOD13_0221F5C4
	ldrh ip, [lr, #4]
	mov r2, r0
	mov r3, #0x78
	bic ip, ip, #0xc00
	orr ip, ip, #0x800
	strh ip, [lr, #4]
	bl MOD13_0223C1C4
	ldr r1, _0221F7A0 ; =0x02243038
	ldr r1, [r1]
	str r0, [r1, #4]
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221F7A0: .word 0x02243038
_0221F7A4: .word 0x0223ED08
_0221F7A8: .word 0x0223ED04
_0221F7AC: .word 0xFE00FF00
_0221F7B0: .word 0x000001FF
_0221F7B4: .word MOD13_0221F5C4

	arm_func_start MOD13_0221F7B8
MOD13_0221F7B8: ; 0x0221F7B8
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r1, r0
	mov r0, #0
	bl MOD13_0223C110
	mov r7, #0
	ldr r8, _0221F894 ; =0x0224303C
	mov r5, r7
_0221F7D4:
	mov r6, r5
	mov r4, r7, lsl #4
_0221F7DC:
	ldr r0, [r8]
	add r0, r4, r0
	ldr r0, [r0, r6, lsl #2]
	bl MOD13_0223A978
	cmp r7, #0
	bne _0221F804
	ldr r0, [r8]
	add r0, r0, r6, lsl #2
	ldr r0, [r0, #0x104]
	bl MOD13_02239AE8
_0221F804:
	add r6, r6, #1
	cmp r6, #4
	blt _0221F7DC
	add r7, r7, #1
	cmp r7, #3
	blt _0221F7D4
	ldr r4, _0221F894 ; =0x0224303C
	mov r5, #0
_0221F824:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xfc]
	bl MOD13_02239AE8
	add r5, r5, #1
	cmp r5, #2
	blt _0221F824
	ldr r4, _0221F894 ; =0x0224303C
	mov r5, #0
_0221F848:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xec]
	bl MOD13_0223B974
	add r5, r5, #1
	cmp r5, #4
	blt _0221F848
	ldr r4, _0221F894 ; =0x0224303C
	mov r5, #0
_0221F86C:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x30]
	bl MOD13_0223B974
	add r5, r5, #1
	cmp r5, #0x2f
	blt _0221F86C
	ldr r0, _0221F894 ; =0x0224303C
	bl MOD13_0223AF90
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0221F894: .word 0x0224303C

	arm_func_start MOD13_0221F898
MOD13_0221F898: ; 0x0221F898
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221F908 ; =0x0224303C
	ldr r2, _0221F90C ; =0x01FF0000
	ldr ip, [r1]
	mov r4, r0
	ldr r3, [ip, #0x30]
	mov r1, #0
	ldr r0, [r3]
	and r0, r0, r2
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [r3]
	and r0, r0, #0xff
	str r0, [sp, #4]
	add r2, r0, #0xc
	str r2, [sp, #4]
	ldrb r0, [ip, #0x11d]
	bl MOD13_022201DC
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0221F910 ; =MOD13_0221F7B8
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221F908: .word 0x0224303C
_0221F90C: .word 0x01FF0000
_0221F910: .word MOD13_0221F7B8

	arm_func_start MOD13_0221F914
MOD13_0221F914: ; 0x0221F914
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221F984 ; =0x0224303C
	ldr r2, _0221F988 ; =0x01FF0000
	ldr ip, [r1]
	mov r4, r0
	ldr r3, [ip, #0x60]
	mov r1, #1
	ldr r0, [r3]
	and r0, r0, r2
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [r3]
	and r0, r0, #0xff
	str r0, [sp, #4]
	add r2, r0, #0xc
	str r2, [sp, #4]
	ldrb r0, [ip, #0x11d]
	bl MOD13_022201DC
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0221F98C ; =MOD13_0221F898
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221F984: .word 0x0224303C
_0221F988: .word 0x01FF0000
_0221F98C: .word MOD13_0221F898

	arm_func_start MOD13_0221F990
MOD13_0221F990: ; 0x0221F990
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221FA00 ; =0x0224303C
	ldr r2, _0221FA04 ; =0x01FF0000
	ldr ip, [r1]
	mov r4, r0
	ldr r3, [ip, #0x90]
	mov r1, #2
	ldr r0, [r3]
	and r0, r0, r2
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [r3]
	and r0, r0, #0xff
	str r0, [sp, #4]
	add r2, r0, #0xc
	str r2, [sp, #4]
	ldrb r0, [ip, #0x11d]
	bl MOD13_022201DC
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0221FA08 ; =MOD13_0221F914
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221FA00: .word 0x0224303C
_0221FA04: .word 0x01FF0000
_0221FA08: .word MOD13_0221F914

	arm_func_start MOD13_0221FA0C
MOD13_0221FA0C: ; 0x0221FA0C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221FA7C ; =0x0224303C
	ldr r2, _0221FA80 ; =0x01FF0000
	ldr ip, [r1]
	mov r4, r0
	ldr r3, [ip, #0xc0]
	mov r1, #3
	ldr r0, [r3]
	and r0, r0, r2
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [r3]
	and r0, r0, #0xff
	str r0, [sp, #4]
	add r2, r0, #0xc
	str r2, [sp, #4]
	ldrb r0, [ip, #0x11d]
	bl MOD13_022201DC
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0221FA84 ; =MOD13_0221F990
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221FA7C: .word 0x0224303C
_0221FA80: .word 0x01FF0000
_0221FA84: .word MOD13_0221F990

	arm_func_start MOD13_0221FA88
MOD13_0221FA88: ; 0x0221FA88
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0221FB08 ; =0x0224303C
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0
	ldr r0, [r0, #0xfc]
	bl MOD13_02239ADC
	ldr r3, [r0]
	ldr r1, _0221FB0C ; =0x01FF0000
	ldr r2, _0221FB08 ; =0x0224303C
	and r1, r3, r1
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [r0]
	ldr r0, [r2]
	and r1, r1, #0xff
	str r1, [sp, #4]
	add r2, r1, #0xc
	str r2, [sp, #4]
	ldrb r0, [r0, #0x11d]
	mov r1, #4
	bl MOD13_022201DC
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0221FB10 ; =MOD13_0221FA0C
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221FB08: .word 0x0224303C
_0221FB0C: .word 0x01FF0000
_0221FB10: .word MOD13_0221FA0C

	arm_func_start MOD13_0221FB14
MOD13_0221FB14: ; 0x0221FB14
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _0221FF90 ; =0x0224303C
	ldr r3, _0221FF94 ; =0x0223EF08
	ldr ip, [r2]
	add r1, ip, #0x100
	ldrsb lr, [r1, #0x21]
	add r1, r3, lr, lsl #2
	ldrsb r1, [r0, r1]
	strb r1, [ip, #0x121]
	ldr r1, [r2]
	add r2, r1, #0x100
	ldrsb r2, [r2, #0x21]
	cmp r2, #0x2e
	bne _0221FB5C
	cmp r0, #3
	streqb lr, [r1, #0x120]
	beq _0221FF7C
_0221FB5C:
	cmp r2, #0x33
	bne _0221FB7C
	cmp r0, #1
	beq _0221FB74
	cmp r0, #3
	bne _0221FB7C
_0221FB74:
	strb lr, [r1, #0x120]
	b _0221FF7C
_0221FB7C:
	cmp r2, #0x34
	bne _0221FBA0
	cmp r0, #1
	beq _0221FB94
	cmp r0, #3
	bne _0221FBA0
_0221FB94:
	cmp lr, #0x2e
	strneb lr, [r1, #0x120]
	b _0221FF7C
_0221FBA0:
	mvn r0, #0
	cmp r2, r0
	bne _0221FBDC
	add r0, r1, #0x100
	ldrsb r0, [r0, #0x20]
	cmp r0, #0x23
	beq _0221FBC4
	cmp r0, #0x32
	bne _0221FBD0
_0221FBC4:
	mov r0, #0x23
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FBD0:
	mov r0, #0x22
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FBDC:
	mvn r0, #1
	cmp r2, r0
	bne _0221FCA4
	add r0, r1, #0x100
	ldrsb r0, [r0, #0x20]
	cmp r0, #0x26
	bgt _0221FC38
	cmp r0, #0x26
	bge _0221FC74
	cmp r0, #5
	bgt _0221FC2C
	cmp r0, #0
	addge pc, pc, r0, lsl #2
	b _0221FC98
_0221FC14: ; jump table
	b _0221FC5C ; case 0
	b _0221FC68 ; case 1
	b _0221FC98 ; case 2
	b _0221FC74 ; case 3
	b _0221FC80 ; case 4
	b _0221FC8C ; case 5
_0221FC2C:
	cmp r0, #0x24
	beq _0221FC68
	b _0221FC98
_0221FC38:
	cmp r0, #0x28
	bgt _0221FC54
	cmp r0, #0x28
	bge _0221FC8C
	cmp r0, #0x27
	beq _0221FC80
	b _0221FC98
_0221FC54:
	cmp r0, #0x31
	bne _0221FC98
_0221FC5C:
	mov r0, #0x31
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FC68:
	mov r0, #0x24
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FC74:
	mov r0, #0x26
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FC80:
	mov r0, #0x27
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FC8C:
	mov r0, #0x28
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FC98:
	mov r0, #0x25
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FCA4:
	mvn r0, #2
	cmp r2, r0
	bne _0221FDA8
	add r0, r1, #0x100
	ldrsb r0, [r0, #0x20]
	cmp r0, #0x23
	bgt _0221FD18
	cmp r0, #0x23
	bge _0221FD90
	cmp r0, #0xb
	bgt _0221FD0C
	cmp r0, #0
	addge pc, pc, r0, lsl #2
	b _0221FD9C
_0221FCDC: ; jump table
	b _0221FD9C ; case 0
	b _0221FD9C ; case 1
	b _0221FD9C ; case 2
	b _0221FD9C ; case 3
	b _0221FD9C ; case 4
	b _0221FD9C ; case 5
	b _0221FD60 ; case 6
	b _0221FD6C ; case 7
	b _0221FD9C ; case 8
	b _0221FD78 ; case 9
	b _0221FD84 ; case 10
	b _0221FD90 ; case 11
_0221FD0C:
	cmp r0, #0x22
	beq _0221FD90
	b _0221FD9C
_0221FD18:
	cmp r0, #0x2a
	bgt _0221FD34
	cmp r0, #0x2a
	bge _0221FD6C
	cmp r0, #0x29
	beq _0221FD60
	b _0221FD9C
_0221FD34:
	cmp r0, #0x32
	bgt _0221FD9C
	cmp r0, #0x2c
	blt _0221FD9C
	cmp r0, #0x2c
	beq _0221FD78
	cmp r0, #0x2d
	beq _0221FD84
	cmp r0, #0x32
	beq _0221FD90
	b _0221FD9C
_0221FD60:
	mov r0, #0x29
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FD6C:
	mov r0, #0x2a
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FD78:
	mov r0, #0x2c
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FD84:
	mov r0, #0x2d
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FD90:
	mov r0, #0x2e
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FD9C:
	mov r0, #0x2b
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FDA8:
	mvn r0, #3
	cmp r2, r0
	bne _0221FE70
	add r0, r1, #0x100
	ldrsb r0, [r0, #0x20]
	cmp r0, #0x26
	bgt _0221FE04
	cmp r0, #0x26
	bge _0221FE40
	cmp r0, #5
	bgt _0221FDF8
	cmp r0, #0
	addge pc, pc, r0, lsl #2
	b _0221FE64
_0221FDE0: ; jump table
	b _0221FE28 ; case 0
	b _0221FE34 ; case 1
	b _0221FE64 ; case 2
	b _0221FE40 ; case 3
	b _0221FE4C ; case 4
	b _0221FE58 ; case 5
_0221FDF8:
	cmp r0, #0x24
	beq _0221FE34
	b _0221FE64
_0221FE04:
	cmp r0, #0x28
	bgt _0221FE20
	cmp r0, #0x28
	bge _0221FE58
	cmp r0, #0x27
	beq _0221FE4C
	b _0221FE64
_0221FE20:
	cmp r0, #0x31
	bne _0221FE64
_0221FE28:
	mov r0, #0
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FE34:
	mov r0, #1
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FE40:
	mov r0, #3
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FE4C:
	mov r0, #4
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FE58:
	mov r0, #5
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FE64:
	mov r0, #2
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FE70:
	mvn r0, #4
	cmp r2, r0
	bne _0221FF7C
	add r0, r1, #0x100
	ldrsb r0, [r0, #0x20]
	cmp r0, #0x23
	bgt _0221FEE4
	cmp r0, #0x23
	bge _0221FF68
	cmp r0, #0xb
	bgt _0221FED8
	cmp r0, #0
	addge pc, pc, r0, lsl #2
	b _0221FF74
_0221FEA8: ; jump table
	b _0221FF74 ; case 0
	b _0221FF74 ; case 1
	b _0221FF74 ; case 2
	b _0221FF74 ; case 3
	b _0221FF74 ; case 4
	b _0221FF74 ; case 5
	b _0221FF2C ; case 6
	b _0221FF38 ; case 7
	b _0221FF74 ; case 8
	b _0221FF44 ; case 9
	b _0221FF50 ; case 10
	b _0221FF5C ; case 11
_0221FED8:
	cmp r0, #0x22
	beq _0221FF5C
	b _0221FF74
_0221FEE4:
	cmp r0, #0x2a
	bgt _0221FF00
	cmp r0, #0x2a
	bge _0221FF38
	cmp r0, #0x29
	beq _0221FF2C
	b _0221FF74
_0221FF00:
	cmp r0, #0x32
	bgt _0221FF74
	cmp r0, #0x2c
	blt _0221FF74
	cmp r0, #0x2c
	beq _0221FF44
	cmp r0, #0x2d
	beq _0221FF50
	cmp r0, #0x32
	beq _0221FF68
	b _0221FF74
_0221FF2C:
	mov r0, #6
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FF38:
	mov r0, #7
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FF44:
	mov r0, #9
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FF50:
	mov r0, #0xa
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FF5C:
	mov r0, #0xb
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FF68:
	mov r0, #0x32
	strb r0, [r1, #0x121]
	b _0221FF7C
_0221FF74:
	mov r0, #8
	strb r0, [r1, #0x121]
_0221FF7C:
	bl MOD13_0221FF98
	mov r0, #8
	bl MOD13_0223424C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0221FF90: .word 0x0224303C
_0221FF94: .word 0x0223EF08

	arm_func_start MOD13_0221FF98
MOD13_0221FF98: ; 0x0221FF98
	stmdb sp!, {r4, lr}
	ldr r0, _02220068 ; =0x0224303C
	ldr r1, [r0]
	add r0, r1, #0x100
	ldrsb r0, [r0, #0x21]
	sub r0, r0, #0x2f
	cmp r0, #5
	addls pc, pc, r0, lsl #2
	b _0221FFFC
_0221FFBC: ; jump table
	b _0221FFD4 ; case 0
	b _0221FFDC ; case 1
	b _0221FFE4 ; case 2
	b _0221FFEC ; case 3
	b _0221FFF4 ; case 4
	b _0221FFF4 ; case 5
_0221FFD4:
	mov r4, #0x42
	b _02220000
_0221FFDC:
	mov r4, #0x41
	b _02220000
_0221FFE4:
	mov r4, #0x43
	b _02220000
_0221FFEC:
	mov r4, #0x41
	b _02220000
_0221FFF4:
	mov r4, #0x45
	b _02220000
_0221FFFC:
	mov r4, #0x40
_02220000:
	ldr r0, [r1, #0x114]
	mov r1, #0
	bl MOD13_02239ADC
	mov r2, r0
	mov r1, r4
	mov r0, #0
	bl MOD13_02239E8C
	ldr r0, _02220068 ; =0x0224303C
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #2
	ldr r0, [r0, #0x114]
	bl MOD13_02239814
	ldr r0, _02220068 ; =0x0224303C
	ldr r2, _0222006C ; =0x0223EE34
	ldr r3, [r0]
	mvn r1, #0
	add r0, r3, #0x100
	ldrsb ip, [r0, #0x21]
	ldr r0, [r3, #0x114]
	ldr r3, _02220070 ; =0x0223EE36
	mov ip, ip, lsl #2
	ldrh r2, [r2, ip]
	ldrh r3, [r3, ip]
	bl MOD13_02239888
	ldmia sp!, {r4, pc}
	.align 2, 0
_02220068: .word 0x0224303C
_0222006C: .word 0x0223EE34
_02220070: .word 0x0223EE36

	arm_func_start MOD13_02220074
MOD13_02220074: ; 0x02220074
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #0
	addlt sp, sp, #4
	ldmltia sp!, {pc}
	cmp r0, #0x2f
	bge _022200CC
	ldr r2, _02220144 ; =0x0224303C
	ldr r3, _02220148 ; =0x0223ED10
	ldr r2, [r2]
	add sp, sp, #4
	add r0, r2, r0, lsl #2
	ldr ip, [r0, #0x30]
	ldr r0, [ip]
	bic r0, r0, #0xc00
	str r0, [ip]
	ldrh r2, [ip, #4]
	ldrb r0, [r3, r1]
	bic r1, r2, #0xf000
	orr r0, r1, r0, lsl #12
	strh r0, [ip, #4]
	ldmia sp!, {pc}
_022200CC:
	sub r3, r0, #0x2f
	cmp r3, #4
	bge _02220114
	ldr r0, _02220144 ; =0x0224303C
	ldr r2, _02220148 ; =0x0223ED10
	ldr r0, [r0]
	add sp, sp, #4
	add r0, r0, r3, lsl #2
	ldr ip, [r0, #0xec]
	ldr r0, [ip]
	bic r0, r0, #0xc00
	str r0, [ip]
	ldrh r3, [ip, #4]
	ldrb r0, [r2, r1]
	bic r1, r3, #0xf000
	orr r0, r1, r0, lsl #12
	strh r0, [ip, #4]
	ldmia sp!, {pc}
_02220114:
	ldr r2, _02220144 ; =0x0224303C
	ldr r3, _0222014C ; =0x0223ED14
	ldr r2, [r2]
	sub r0, r0, #0x33
	add r0, r2, r0, lsl #2
	ldrb r3, [r3, r1]
	ldr r0, [r0, #0xfc]
	mvn r1, #0
	mov r2, #0
	bl MOD13_02239994
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02220144: .word 0x0224303C
_02220148: .word 0x0223ED10
_0222014C: .word 0x0223ED14

	arm_func_start MOD13_02220150
MOD13_02220150: ; 0x02220150
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	ldr r1, _022201D4 ; =0x0224303C
	mov r6, #0
	ldr r1, [r1]
	mov r8, r0
	mov r5, r6
	mov r7, r6
	mov r4, r6
	strb r8, [r1, #0x11d]
	ldr sb, _022201D8 ; =0x0223ED78
_0222017C:
	add r0, sb, r4, lsl #2
	ldrh r2, [r0, #2]
	mov r0, r8
	mov r1, r7
	bl MOD13_022201DC
	add r7, r7, #1
	cmp r7, #4
	add r4, r4, #0xc
	blt _0222017C
	cmp r8, #2
	moveq r6, #1
	beq _022201B4
	cmp r8, #1
	moveq r5, #1
_022201B4:
	mov r1, r6
	mov r0, #0x2f
	bl MOD13_02220074
	mov r1, r5
	mov r0, #0x30
	bl MOD13_02220074
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_022201D4: .word 0x0224303C
_022201D8: .word 0x0223ED78

	arm_func_start MOD13_022201DC
MOD13_022201DC: ; 0x022201DC
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x1c
	ldr r4, _02220460 ; =0x0223ED38
	ldr lr, _02220464 ; =0x0223ED40
	ldrb r5, [r4, #4]
	ldrb sb, [r4]
	ldrb r8, [r4, #1]
	strb r5, [sp, #0xc]
	mov r5, r1
	mov r1, #0xc
	mul r1, r5, r1
	ldrb r7, [r4, #2]
	ldrb r6, [r4, #3]
	strb sb, [sp, #8]
	str r1, [sp, #4]
	ldrb ip, [lr]
	ldrb sl, [lr, #1]
	ldrb r4, [lr, #2]
	ldrb fp, [lr, #3]
	ldrb sb, [lr, #4]
	ldr r3, _02220468 ; =0x0223ED30
	strb r8, [sp, #9]
	strb r7, [sp, #0xa]
	strb r6, [sp, #0xb]
	add r1, sp, #8
	ldrb lr, [r3]
	ldrb r8, [r3, #1]
	ldrb r7, [r3, #2]
	ldrb r6, [r3, #3]
	ldrb r3, [r3, #4]
	ldrb r1, [r1, r5]
	strb sl, [sp, #0xe]
	strb r4, [sp, #0xf]
	strb sb, [sp, #0x11]
	strb ip, [sp, #0xd]
	mov r4, r2
	ldr sl, [sp, #4]
	strb fp, [sp, #0x10]
	strb lr, [sp, #0x12]
	strb r8, [sp, #0x13]
	strb r7, [sp, #0x14]
	strb r6, [sp, #0x15]
	strb r3, [sp, #0x16]
	cmp r1, #0
	mov sb, #0
	ble _0222030C
	add r1, sp, #8
	ldr r2, _0222046C ; =0x0224303C
	ldr r3, _02220470 ; =0x0223ED78
	ldr fp, _02220474 ; =0xFE00FF00
	and r8, r4, #0xff
	add r7, r1, r5
_022202AC:
	ldr r1, [r2]
	mov r6, sl, lsl #2
	add r1, r1, sl, lsl #2
	ldr lr, [r1, #0x30]
	ldr r1, _02220478 ; =0xC1FFFCFF
	ldr ip, [lr]
	add sb, sb, #1
	and r1, ip, r1
	str r1, [lr]
	ldr r1, [r2]
	ldrh ip, [r3, r6]
	add r1, r1, sl, lsl #2
	ldr r6, [r1, #0x30]
	ldr r1, _0222047C ; =0x000001FF
	add sl, sl, #1
	and r1, ip, r1
	ldr ip, [r6]
	and ip, ip, fp
	orr ip, ip, r8
	orr r1, ip, r1, lsl #16
	str r1, [r6]
	ldrb r1, [r7]
	cmp sb, r1
	blt _022202AC
_0222030C:
	cmp r5, #4
	bge _0222034C
	ldr r1, _0222046C ; =0x0224303C
	mov r2, #2
	ldr r6, [r1]
	ldr r1, [sp, #4]
	str r2, [sp]
	add r0, r6, r0, lsl #4
	ldr r3, _02220470 ; =0x0223ED78
	mov r1, r1, lsl #2
	add r2, r6, r5, lsl #2
	ldrh r1, [r3, r1]
	ldr r3, [r2, #0x104]
	ldr r0, [r0, r5, lsl #2]
	mov r2, r4
	bl MOD13_0223A440
_0222034C:
	add r0, r5, #3
	mov r1, #4
	bl FX_ModS32
	add r8, sp, #0xd
	ldrb r1, [r8, r5]
	mov r2, #0
	cmp r1, #0
	ble _022203E0
	ldr r3, _02220480 ; =0x0223ED58
	mov r1, r0, lsl #2
	ldrh r3, [r3, r1]
	ldr r0, _0222047C ; =0x000001FF
	and r7, r4, #0xff
	and r0, r3, r0
	mov r6, r0, lsl #0x10
	add r3, r8, r5
	ldr sl, _0222046C ; =0x0224303C
	ldr r8, _02220478 ; =0xC1FFFCFF
	ldr sb, _02220474 ; =0xFE00FF00
_02220398:
	ldr r0, [sl]
	add r2, r2, #1
	add r0, r1, r0
	ldr fp, [r0, #0xec]
	ldr r0, [fp]
	and r0, r0, r8
	str r0, [fp]
	ldr r0, [sl]
	add r0, r1, r0
	ldr r0, [r0, #0xec]
	ldr fp, [r0]
	and fp, fp, sb
	orr fp, fp, r7
	orr fp, r6, fp
	str fp, [r0]
	ldrb r0, [r3]
	cmp r2, r0
	blt _02220398
_022203E0:
	add r1, sp, #0x12
	ldrb r0, [r1, r5]
	mov r8, #0
	cmp r0, #0
	addle sp, sp, #0x1c
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add sb, r1, r5
	ldr sl, _0222046C ; =0x0224303C
	ldr r5, _02220484 ; =0x0223ED50
	mov r6, r8
	mvn r7, #0
_0222040C:
	ldr r0, [sl]
	mov r1, r7
	add r0, r0, r8, lsl #2
	ldr r0, [r0, #0xfc]
	mov r2, r6
	mov r3, r6
	bl MOD13_02239A1C
	ldr r0, [sl]
	mov r1, r8, lsl #2
	add r0, r0, r8, lsl #2
	ldrh r2, [r5, r1]
	ldr r0, [r0, #0xfc]
	mov r1, r7
	mov r3, r4
	bl MOD13_02239888
	ldrb r0, [sb]
	add r8, r8, #1
	cmp r8, r0
	blt _0222040C
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02220460: .word 0x0223ED38
_02220464: .word 0x0223ED40
_02220468: .word 0x0223ED30
_0222046C: .word 0x0224303C
_02220470: .word 0x0223ED78
_02220474: .word 0xFE00FF00
_02220478: .word 0xC1FFFCFF
_0222047C: .word 0x000001FF
_02220480: .word 0x0223ED58
_02220484: .word 0x0223ED50

	arm_func_start MOD13_02220488
MOD13_02220488: ; 0x02220488
	stmdb sp!, {r4, lr}
	mov r0, #0x20
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022204A4
	mov r0, #0
	bl MOD13_0221FB14
_022204A4:
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022204BC
	mov r0, #1
	bl MOD13_0221FB14
_022204BC:
	mov r0, #0x10
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022204D4
	mov r0, #2
	bl MOD13_0221FB14
_022204D4:
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022204EC
	mov r0, #3
	bl MOD13_0221FB14
_022204EC:
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02220604
	ldr r2, _022206A4 ; =0x0224303C
	ldr r0, [r2]
	add r1, r0, #0x100
	ldrsb r4, [r1, #0x21]
	cmp r4, #0x2f
	bge _0222055C
	ldrb r1, [r0, #0x124]
	cmp r1, #0
	bne _0222052C
	mov r0, #9
	bl MOD13_0223424C
	ldmia sp!, {r4, pc}
_0222052C:
	ldrb r3, [r0, #0x11d]
	ldr r1, _022206A8 ; =0x0223FB7C
	ldr r1, [r1, r3, lsl #2]
	ldrb r1, [r1, r4]
	strb r1, [r0, #0x11c]
	ldr r0, [r2]
	ldrb r0, [r0, #0x11d]
	cmp r0, #1
	ldmneia sp!, {r4, pc}
	mov r0, #0
	bl MOD13_02220150
	ldmia sp!, {r4, pc}
_0222055C:
	sub r1, r4, #0x2f
	cmp r1, #4
	bge _022205F4
	cmp r1, #3
	addls pc, pc, r1, lsl #2
	b _022205C4
_02220574: ; jump table
	b _02220584 ; case 0
	b _0222058C ; case 1
	b _02220594 ; case 2
	b _022205AC ; case 3
_02220584:
	bl MOD13_02220944
	ldmia sp!, {r4, pc}
_0222058C:
	bl MOD13_0222090C
	ldmia sp!, {r4, pc}
_02220594:
	ldrb r1, [r0, #0x124]
	cmp r1, #0
	bne _022205C4
	mov r0, #9
	bl MOD13_0223424C
	ldmia sp!, {r4, pc}
_022205AC:
	ldrb r1, [r0, #0x123]
	cmp r1, #0
	bne _022205C4
	mov r0, #9
	bl MOD13_0223424C
	ldmia sp!, {r4, pc}
_022205C4:
	ldrb r0, [r0, #0x11d]
	cmp r0, #1
	bne _022205D8
	mov r0, #0
	bl MOD13_02220150
_022205D8:
	ldr r1, _022206AC ; =0x0223ED48
	sub r2, r4, #0x2f
	ldr r0, _022206A4 ; =0x0224303C
	ldrb r1, [r1, r2]
	ldr r0, [r0]
	strb r1, [r0, #0x11c]
	ldmia sp!, {r4, pc}
_022205F4:
	ldr r1, _022206B0 ; =0x0223ED1C
	sub r2, r4, #0x33
	ldrb r1, [r1, r2]
	strb r1, [r0, #0x11c]
_02220604:
	mov r0, #2
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222065C
	ldr r0, _022206A4 ; =0x0224303C
	ldr r1, [r0]
	ldrb r0, [r1, #0x123]
	cmp r0, #0
	bne _02220650
	ldrb r0, [r1, #0x125]
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _022206A4 ; =0x0224303C
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x125]
	ldmia sp!, {r4, pc}
_02220650:
	mov r0, #0x80
	strb r0, [r1, #0x11c]
	b _02220678
_0222065C:
	mov r0, #2
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _022206A4 ; =0x0224303C
	movne r1, #0
	ldrne r0, [r0]
	strneb r1, [r0, #0x125]
_02220678:
	mov r0, #0x400
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222068C
	bl MOD13_02220944
_0222068C:
	mov r0, #0x800
	bl MOD13_0223B3D4
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	bl MOD13_0222090C
	ldmia sp!, {r4, pc}
	.align 2, 0
_022206A4: .word 0x0224303C
_022206A8: .word 0x0223FB7C
_022206AC: .word 0x0223ED48
_022206B0: .word 0x0223ED1C

	arm_func_start MOD13_022206B4
MOD13_022206B4: ; 0x022206B4
	stmdb sp!, {r4, lr}
	ldr r1, _02220704 ; =0x0224303C
	mov r4, r0
	ldr r1, [r1]
	add r1, r1, #0x100
	ldrsb r1, [r1, #0x1f]
	cmp r4, r1
	ldmeqia sp!, {r4, pc}
	mov r1, #1
	bl MOD13_02220074
	ldr r0, _02220704 ; =0x0224303C
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, #0x100
	ldrsb r0, [r0, #0x1f]
	bl MOD13_02220074
	ldr r0, _02220704 ; =0x0224303C
	ldr r0, [r0]
	strb r4, [r0, #0x11f]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02220704: .word 0x0224303C

	arm_func_start MOD13_02220708
MOD13_02220708: ; 0x02220708
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r0, _022208EC ; =0x0223F75C
	bl MOD13_0223B320
	cmp r0, #0
	beq _022208CC
	ldr r7, _022208F0 ; =0x0223ED78
	mov r4, #0
	ldr r6, _022208F4 ; =0x0223ED2C
	add r5, sp, #0
_02220730:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B320
	cmp r0, #0
	beq _02220774
	ldr r0, _022208F8 ; =0x0224303C
	ldr r0, [r0]
	add r0, r0, #0x100
	ldrsb r0, [r0, #0x1e]
	cmp r0, r4
	bne _022208CC
	mov r0, r4
	bl MOD13_022206B4
	b _022208D4
_02220774:
	add r4, r4, #1
	cmp r4, #0x2f
	add r7, r7, #4
	blt _02220730
	ldr r7, _022208FC ; =0x0223ED70
	ldr r6, _02220900 ; =0x0223ED60
	mov r5, #2
	add r4, sp, #0
_02220794:
	mov r0, r6
	mov r1, r7
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B320
	cmp r0, #0
	beq _02220854
	ldr r1, _022208F8 ; =0x0224303C
	add r0, r5, #0x2f
	ldr r1, [r1]
	add r1, r1, #0x100
	ldrsb r1, [r1, #0x1e]
	cmp r1, r0
	bne _022208CC
	bl MOD13_022206B4
	cmp r5, #3
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _022208F8 ; =0x0224303C
	ldr r2, [r0]
	ldrb r1, [r2, #0x122]
	add r1, r1, #1
	strb r1, [r2, #0x122]
	ldr r2, [r0]
	ldrb r1, [r2, #0x122]
	cmp r1, #0x28
	addlo sp, sp, #0xc
	ldmloia sp!, {r4, r5, r6, r7, pc}
	ldrb r1, [r2, #0x123]
	cmp r1, #0
	bne _02220834
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _022208F8 ; =0x0224303C
	mvn r1, #0
	ldr r0, [r0]
	add sp, sp, #0xc
	strb r1, [r0, #0x11e]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220834:
	mov r1, #0x80
	strb r1, [r2, #0x11c]
	ldr r1, [r0]
	add sp, sp, #0xc
	ldrb r0, [r1, #0x122]
	sub r0, r0, #7
	strb r0, [r1, #0x122]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220854:
	add r5, r5, #1
	cmp r5, #4
	add r7, r7, #4
	add r6, r6, #4
	blt _02220794
	ldr r7, _02220904 ; =0x0223ED50
	mov r6, #0
	ldr r5, _02220908 ; =0x0223ED28
	add r4, sp, #0
_02220878:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B320
	cmp r0, #0
	beq _022208BC
	ldr r1, _022208F8 ; =0x0224303C
	add r0, r6, #0x33
	ldr r1, [r1]
	add r1, r1, #0x100
	ldrsb r1, [r1, #0x1e]
	cmp r1, r0
	bne _022208CC
	bl MOD13_022206B4
	b _022208D4
_022208BC:
	add r6, r6, #1
	cmp r6, #2
	add r7, r7, #4
	blt _02220878
_022208CC:
	mvn r0, #0
	bl MOD13_022206B4
_022208D4:
	ldr r0, _022208F8 ; =0x0224303C
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x122]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_022208EC: .word 0x0223F75C
_022208F0: .word 0x0223ED78
_022208F4: .word 0x0223ED2C
_022208F8: .word 0x0224303C
_022208FC: .word 0x0223ED70
_02220900: .word 0x0223ED60
_02220904: .word 0x0223ED50
_02220908: .word 0x0223ED28

	arm_func_start MOD13_0222090C
MOD13_0222090C: ; 0x0222090C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02220940 ; =0x0224303C
	ldr r0, [r0]
	ldrb r0, [r0, #0x11d]
	cmp r0, #1
	movne r0, #1
	moveq r0, #0
	bl MOD13_02220150
	mov r0, #1
	bl MOD13_0223424C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02220940: .word 0x0224303C

	arm_func_start MOD13_02220944
MOD13_02220944: ; 0x02220944
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02220978 ; =0x0224303C
	ldr r0, [r0]
	ldrb r0, [r0, #0x11d]
	cmp r0, #2
	moveq r0, #0
	movne r0, #2
	bl MOD13_02220150
	mov r0, #1
	bl MOD13_0223424C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02220978: .word 0x0224303C

	arm_func_start MOD13_0222097C
MOD13_0222097C: ; 0x0222097C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r1, _02220C28 ; =0x0224303C
	ldr r0, _02220C2C ; =0x0223F75C
	ldr r1, [r1]
	mov r2, #0
	strb r2, [r1, #0x11c]
	bl MOD13_0223B1DC
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r7, _02220C30 ; =0x0223ED78
	mov r4, #0
	ldr r6, _02220C34 ; =0x0223ED2C
	add r5, sp, #0
_022209B8:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02220A38
	ldr r1, _02220C28 ; =0x0224303C
	ldr r3, [r1]
	add r0, r3, #0x100
	ldrsb r0, [r0, #0x1e]
	cmp r0, r4
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldrb r2, [r3, #0x11d]
	ldr r0, _02220C38 ; =0x0223FB7C
	ldr r0, [r0, r2, lsl #2]
	ldrb r0, [r0, r4]
	strb r0, [r3, #0x11c]
	ldr r0, [r1]
	ldrb r0, [r0, #0x11d]
	cmp r0, #1
	bne _02220A20
	mov r0, #0
	bl MOD13_02220150
_02220A20:
	ldr r0, _02220C28 ; =0x0224303C
	ldr r0, [r0]
	strb r4, [r0, #0x121]
	bl MOD13_0221FF98
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220A38:
	add r4, r4, #1
	cmp r4, #0x2f
	add r7, r7, #4
	blt _022209B8
	ldr r7, _02220C3C ; =0x0223ED70
	ldr r6, _02220C40 ; =0x0223ED60
	mov r4, #2
	add r5, sp, #0
_02220A58:
	mov r0, r6
	mov r1, r7
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02220AD8
	ldr r1, _02220C28 ; =0x0224303C
	add r2, r4, #0x2f
	ldr r3, [r1]
	add r0, r3, #0x100
	ldrsb r0, [r0, #0x1e]
	cmp r0, r2
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _02220C44 ; =0x0223ED48
	ldrb r0, [r0, r4]
	strb r0, [r3, #0x11c]
	ldr r0, [r1]
	ldrb r0, [r0, #0x11d]
	cmp r0, #1
	bne _02220ABC
	mov r0, #0
	bl MOD13_02220150
_02220ABC:
	ldr r0, _02220C28 ; =0x0224303C
	add r1, r4, #0x2f
	ldr r0, [r0]
	strb r1, [r0, #0x121]
	bl MOD13_0221FF98
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220AD8:
	add r4, r4, #1
	cmp r4, #4
	add r7, r7, #4
	add r6, r6, #4
	blt _02220A58
	ldr r7, _02220C48 ; =0x0223ED50
	mov r4, #0
	ldr r6, _02220C4C ; =0x0223ED28
	add r5, sp, #0
_02220AFC:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02220B5C
	ldr r1, _02220C28 ; =0x0224303C
	add r2, r4, #0x33
	ldr r3, [r1]
	add r0, r3, #0x100
	ldrsb r0, [r0, #0x1e]
	cmp r0, r2
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _02220C50 ; =0x0223ED1C
	ldrb r0, [r0, r4]
	strb r0, [r3, #0x11c]
	ldr r0, [r1]
	strb r2, [r0, #0x121]
	bl MOD13_0221FF98
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220B5C:
	add r4, r4, #1
	cmp r4, #2
	add r7, r7, #4
	blt _02220AFC
	ldr r0, _02220C54 ; =0x0223ED58
	ldr r1, _02220C58 ; =0x0223ED68
	add r2, sp, #0
	bl MOD13_0223AB74
	add r0, sp, #0
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02220BC8
	ldr r0, _02220C28 ; =0x0224303C
	ldr r0, [r0]
	add r0, r0, #0x100
	ldrsb r0, [r0, #0x1e]
	cmp r0, #0x2f
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	bl MOD13_02220944
	ldr r0, _02220C28 ; =0x0224303C
	mov r1, #0x2f
	ldr r0, [r0]
	strb r1, [r0, #0x121]
	bl MOD13_0221FF98
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220BC8:
	ldr r0, _02220C5C ; =0x0223ED5C
	ldr r1, _02220C60 ; =0x0223ED6C
	add r2, sp, #0
	bl MOD13_0223AB74
	add r0, sp, #0
	bl MOD13_0223B1DC
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _02220C28 ; =0x0224303C
	ldr r0, [r0]
	add r0, r0, #0x100
	ldrsb r0, [r0, #0x1e]
	cmp r0, #0x30
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	bl MOD13_0222090C
	ldr r0, _02220C28 ; =0x0224303C
	mov r1, #0x30
	ldr r0, [r0]
	strb r1, [r0, #0x121]
	bl MOD13_0221FF98
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02220C28: .word 0x0224303C
_02220C2C: .word 0x0223F75C
_02220C30: .word 0x0223ED78
_02220C34: .word 0x0223ED2C
_02220C38: .word 0x0223FB7C
_02220C3C: .word 0x0223ED70
_02220C40: .word 0x0223ED60
_02220C44: .word 0x0223ED48
_02220C48: .word 0x0223ED50
_02220C4C: .word 0x0223ED28
_02220C50: .word 0x0223ED1C
_02220C54: .word 0x0223ED58
_02220C58: .word 0x0223ED68
_02220C5C: .word 0x0223ED5C
_02220C60: .word 0x0223ED6C

	arm_func_start MOD13_02220C64
MOD13_02220C64: ; 0x02220C64
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r0, _02220E28 ; =0x0223F75C
	bl MOD13_0223B2B4
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _02220E2C ; =0x0224303C
	mvn r1, #0
	ldr r0, [r0]
	ldr r7, _02220E30 ; =0x0223ED78
	strb r1, [r0, #0x11e]
	mov r4, #0
	ldr r6, _02220E34 ; =0x0223ED2C
	add r5, sp, #0
_02220CA0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02220D00
	ldr r0, _02220E2C ; =0x0224303C
	ldr r0, [r0]
	ldrb r0, [r0, #0x124]
	cmp r0, #0
	bne _02220CE4
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220CE4:
	mov r0, #0
	bl MOD13_0223424C
	ldr r0, _02220E2C ; =0x0224303C
	add sp, sp, #0xc
	ldr r0, [r0]
	strb r4, [r0, #0x11e]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220D00:
	add r4, r4, #1
	cmp r4, #0x2f
	add r7, r7, #4
	blt _02220CA0
	ldr r7, _02220E38 ; =0x0223ED68
	ldr r6, _02220E3C ; =0x0223ED58
	mov r4, #0
	add r5, sp, #0
_02220D20:
	mov r0, r6
	mov r1, r7
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02220DAC
	cmp r4, #3
	bne _02220D5C
	ldr r0, _02220E2C ; =0x0224303C
	ldr r0, [r0]
	ldrb r0, [r0, #0x123]
	cmp r0, #0
	beq _02220D78
_02220D5C:
	cmp r4, #2
	bne _02220D88
	ldr r0, _02220E2C ; =0x0224303C
	ldr r0, [r0]
	ldrb r0, [r0, #0x124]
	cmp r0, #0
	bne _02220D88
_02220D78:
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220D88:
	ldr r0, _02220E40 ; =0x0223FB94
	ldr r0, [r0, r4, lsl #2]
	bl MOD13_0223424C
	ldr r0, _02220E2C ; =0x0224303C
	add r1, r4, #0x2f
	ldr r0, [r0]
	add sp, sp, #0xc
	strb r1, [r0, #0x11e]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220DAC:
	add r4, r4, #1
	cmp r4, #4
	add r7, r7, #4
	add r6, r6, #4
	blt _02220D20
	ldr r7, _02220E44 ; =0x0223ED50
	mov r6, #0
	ldr r5, _02220E48 ; =0x0223ED28
	add r4, sp, #0
_02220DD0:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02220E10
	mov r0, #0
	bl MOD13_0223424C
	ldr r0, _02220E2C ; =0x0224303C
	add r1, r6, #0x33
	ldr r0, [r0]
	add sp, sp, #0xc
	strb r1, [r0, #0x11e]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02220E10:
	add r6, r6, #1
	cmp r6, #2
	add r7, r7, #4
	blt _02220DD0
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02220E28: .word 0x0223F75C
_02220E2C: .word 0x0224303C
_02220E30: .word 0x0223ED78
_02220E34: .word 0x0223ED2C
_02220E38: .word 0x0223ED68
_02220E3C: .word 0x0223ED58
_02220E40: .word 0x0223FB94
_02220E44: .word 0x0223ED50
_02220E48: .word 0x0223ED28

	arm_func_start MOD13_02220E4C
MOD13_02220E4C: ; 0x02220E4C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02220C64
	bl MOD13_0222097C
	bl MOD13_02220708
	bl MOD13_02220488
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02220EFC ; =0x0224303C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #0xfc]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, _02220F00 ; =0x0223ED50
	ldr r2, [sp, #4]
	ldrh r1, [r0, #2]
	sub r2, r2, #0xc
	str r2, [sp, #4]
	cmp r2, r1
	ble _02220ECC
	ldr r0, _02220EFC ; =0x0224303C
	mov r1, #4
	ldr r0, [r0]
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02220ECC:
	ldr r0, _02220EFC ; =0x0224303C
	mov r2, r1
	ldr r0, [r0]
	mov r1, #4
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	bl MOD13_0221FF98
	ldr r1, _02220F04 ; =MOD13_02220E4C
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02220EFC: .word 0x0224303C
_02220F00: .word 0x0223ED50
_02220F04: .word MOD13_02220E4C

	arm_func_start MOD13_02220F08
MOD13_02220F08: ; 0x02220F08
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02220FA8 ; =0x0224303C
	ldr r2, _02220FAC ; =0x0223ED78
	ldr lr, [r1]
	ldr r1, _02220FB0 ; =0x01FF0000
	ldr ip, [lr, #0xc0]
	ldrh r3, [r2, #0x92]
	ldr r2, [ip]
	mov r4, r0
	and r0, r2, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r2, r0, #0xc
	str r0, [sp, #4]
	str r2, [sp, #4]
	cmp r2, r3
	ble _02220F6C
	ldrb r0, [lr, #0x11d]
	mov r1, #3
	bl MOD13_022201DC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02220F6C:
	ldrb r0, [lr, #0x11d]
	mov r2, r3
	mov r1, #3
	bl MOD13_022201DC
	ldr r0, _02220FA8 ; =0x0224303C
	mov r1, #4
	ldr r0, [r0]
	mov r2, #0xc0
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	ldr r1, _02220FB4 ; =0x02220E6C
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02220FA8: .word 0x0224303C
_02220FAC: .word 0x0223ED78
_02220FB0: .word 0x01FF0000
_02220FB4: .word 0x02220E6C

	arm_func_start MOD13_02220FB8
MOD13_02220FB8: ; 0x02220FB8
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02221058 ; =0x0224303C
	ldr r2, _0222105C ; =0x0223ED78
	ldr lr, [r1]
	ldr r1, _02221060 ; =0x01FF0000
	ldr ip, [lr, #0x90]
	ldrh r3, [r2, #0x62]
	ldr r2, [ip]
	mov r4, r0
	and r0, r2, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r2, r0, #0xc
	str r0, [sp, #4]
	str r2, [sp, #4]
	cmp r2, r3
	ble _0222101C
	ldrb r0, [lr, #0x11d]
	mov r1, #2
	bl MOD13_022201DC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222101C:
	ldrb r0, [lr, #0x11d]
	mov r2, r3
	mov r1, #2
	bl MOD13_022201DC
	ldr r0, _02221058 ; =0x0224303C
	mov r1, #3
	ldr r0, [r0]
	mov r2, #0xc0
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	ldr r1, _02221064 ; =MOD13_02220F08
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02221058: .word 0x0224303C
_0222105C: .word 0x0223ED78
_02221060: .word 0x01FF0000
_02221064: .word MOD13_02220F08

	arm_func_start MOD13_02221068
MOD13_02221068: ; 0x02221068
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02221108 ; =0x0224303C
	ldr r2, _0222110C ; =0x0223ED78
	ldr lr, [r1]
	ldr r1, _02221110 ; =0x01FF0000
	ldr ip, [lr, #0x60]
	ldrh r3, [r2, #0x32]
	ldr r2, [ip]
	mov r4, r0
	and r0, r2, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r2, r0, #0xc
	str r0, [sp, #4]
	str r2, [sp, #4]
	cmp r2, r3
	ble _022210CC
	ldrb r0, [lr, #0x11d]
	mov r1, #1
	bl MOD13_022201DC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022210CC:
	ldrb r0, [lr, #0x11d]
	mov r2, r3
	mov r1, #1
	bl MOD13_022201DC
	ldr r0, _02221108 ; =0x0224303C
	mov r1, #2
	ldr r0, [r0]
	mov r2, #0xc0
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	ldr r1, _02221114 ; =MOD13_02220FB8
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02221108: .word 0x0224303C
_0222110C: .word 0x0223ED78
_02221110: .word 0x01FF0000
_02221114: .word MOD13_02220FB8

	arm_func_start MOD13_02221118
MOD13_02221118: ; 0x02221118
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _022211B8 ; =0x0224303C
	ldr r2, _022211BC ; =0x0223ED78
	ldr lr, [r1]
	ldr r1, _022211C0 ; =0x01FF0000
	ldr ip, [lr, #0x30]
	ldrh r3, [r2, #2]
	ldr r2, [ip]
	mov r4, r0
	and r0, r2, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r2, r0, #0xc
	str r0, [sp, #4]
	str r2, [sp, #4]
	cmp r2, r3
	ble _0222117C
	ldrb r0, [lr, #0x11d]
	mov r1, #0
	bl MOD13_022201DC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222117C:
	ldrb r0, [lr, #0x11d]
	mov r2, r3
	mov r1, #0
	bl MOD13_022201DC
	ldr r0, _022211B8 ; =0x0224303C
	mov r1, #1
	ldr r0, [r0]
	mov r2, #0xc0
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	ldr r1, _022211C4 ; =MOD13_02221068
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022211B8: .word 0x0224303C
_022211BC: .word 0x0223ED78
_022211C0: .word 0x01FF0000
_022211C4: .word MOD13_02221068

	arm_func_start MOD13_022211C8
MOD13_022211C8: ; 0x022211C8
	ldr r0, _022211E0 ; =0x0224303C
	ldr r0, [r0]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_022211E0: .word 0x0224303C

	arm_func_start MOD13_022211E4
MOD13_022211E4: ; 0x022211E4
	ldr r1, _022211F4 ; =0x0224303C
	ldr r1, [r1]
	strb r0, [r1, #0x124]
	bx lr
	.align 2, 0
_022211F4: .word 0x0224303C

	arm_func_start MOD13_022211F8
MOD13_022211F8: ; 0x022211F8
	ldr r1, _02221208 ; =0x0224303C
	ldr r1, [r1]
	strb r0, [r1, #0x123]
	bx lr
	.align 2, 0
_02221208: .word 0x0224303C

	arm_func_start MOD13_0222120C
MOD13_0222120C: ; 0x0222120C
	ldr r0, _0222121C ; =0x0224303C
	ldr r0, [r0]
	ldrb r0, [r0, #0x11c]
	bx lr
	.align 2, 0
_0222121C: .word 0x0224303C

	arm_func_start MOD13_02221220
MOD13_02221220: ; 0x02221220
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02221254 ; =0x0224303C
	ldr r0, [r0]
	ldr r0, [r0, #0x114]
	bl MOD13_02239AE8
	ldr r0, _02221254 ; =0x0224303C
	ldr r1, _02221258 ; =MOD13_0221FA88
	ldr r0, [r0]
	ldr r0, [r0, #0x118]
	bl MOD13_0223C130
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02221254: .word 0x0224303C
_02221258: .word MOD13_0221FA88

	arm_func_start MOD13_0222125C
MOD13_0222125C: ; 0x0222125C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x44
	add r2, sp, #0x34
	mov r1, #0
	strh r1, [r2]
	strh r1, [r2, #2]
	strh r1, [r2, #4]
	strh r1, [r2, #6]
	ldr r0, _022215EC ; =0x0223ED2C
	mov r1, #4
	ldrh r3, [r0]
	ldrh r2, [r0, #2]
	mov r0, #0x128
	strh r3, [sp, #0x38]
	strh r2, [sp, #0x3a]
	bl MOD13_0223AFE0
	ldr r8, _022215F0 ; =0x0224303C
	mov r6, #0
	mov r1, #0xff
	str r0, [r8]
	strb r1, [r0, #0x11c]
	ldr r0, [r8]
	mov r1, #1
	strb r6, [r0, #0x121]
	ldr r0, [r8]
	ldr r7, _022215F4 ; =0xC1FFFCFF
	strb r1, [r0, #0x123]
	ldr r0, [r8]
	mov r5, r6
	strb r1, [r0, #0x124]
	mov r4, #0x34
_022212D8:
	mov r0, r5
	mov r1, r4
	bl MOD13_02239E54
	ldr r1, [r8]
	add r1, r1, r6, lsl #2
	str r0, [r1, #0x30]
	ldr r0, [r8]
	add r0, r0, r6, lsl #2
	ldr r1, [r0, #0x30]
	ldr r0, [r1]
	and r0, r0, r7
	orr r0, r0, #0x200
	str r0, [r1]
	ldr r0, [r8]
	add r0, r0, r6, lsl #2
	ldr r1, [r0, #0x30]
	add r6, r6, #1
	ldrh r0, [r1, #4]
	cmp r6, #0x2f
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	blt _022212D8
	ldr r6, _022215F8 ; =0x0223ED20
	mov r5, #0
	ldr r8, _022215F0 ; =0x0224303C
	mov r4, r5
	ldr r7, _022215F4 ; =0xC1FFFCFF
_02221348:
	ldrb r1, [r6]
	mov r0, r4
	bl MOD13_02239E54
	ldr r1, [r8]
	add r6, r6, #1
	add r1, r1, r5, lsl #2
	str r0, [r1, #0xec]
	ldr r0, [r8]
	add r0, r0, r5, lsl #2
	ldr r1, [r0, #0xec]
	ldr r0, [r1]
	and r0, r0, r7
	orr r0, r0, #0x200
	str r0, [r1]
	ldr r0, [r8]
	add r0, r0, r5, lsl #2
	ldr r1, [r0, #0xec]
	add r5, r5, #1
	ldrh r0, [r1, #4]
	cmp r5, #4
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	blt _02221348
	ldr sl, _022215FC ; =0x0223ED18
	mov sb, #0
	ldr r4, _022215F0 ; =0x0224303C
	mov fp, sb
	str sb, [sp, #0x1c]
	mov r8, #1
	mvn r7, #0
	mov r6, #0x200
	mov r5, #3
_022213CC:
	ldrb r1, [sl]
	mov r0, fp
	mov r2, r8
	bl MOD13_02239E0C
	ldr r2, [r4]
	ldr r3, [sp, #0x1c]
	add r2, r2, sb, lsl #2
	str r0, [r2, #0xfc]
	ldr r0, [r4]
	mov r1, r7
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #0xfc]
	mov r2, r6
	bl MOD13_02239A1C
	ldr r0, [r4]
	mov r1, r7
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #0xfc]
	mov r2, r5
	bl MOD13_02239814
	add sb, sb, #1
	add sl, sl, #1
	cmp sb, #2
	blt _022213CC
	ldr r1, _02221600 ; =0x0223ED24
	mov r7, #0
	ldrh r0, [r1, #2]
	ldr fp, _02221604 ; =0x0223FB88
	ldr r4, _022215F0 ; =0x0224303C
	str r0, [sp, #0x10]
	ldrh r0, [r1]
	strh r7, [sp, #0x42]
	str r7, [sp, #0x2c]
	str r0, [sp, #0x14]
	mov r0, #1
	str r7, [sp, #0x24]
	str r7, [sp, #0x28]
	str r7, [sp, #0x20]
	mov r6, #2
	mov r5, #0x480
	str r0, [sp, #0x30]
_02221470:
	ldr sb, [sp, #0x20]
	mov r0, sb
	str r0, [sp, #0x18]
_0222147C:
	add r0, sp, #0x3c
	str r0, [sp]
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	str r0, [sp, #4]
	mov r3, r0
	bl MOD13_0223A9A4
	ldr r1, [r4]
	ldr sl, [sp, #0x18]
	add r1, r1, r7, lsl #4
	str r0, [r1, sb, lsl #2]
	ldr r0, [sp, #0x28]
	strh r0, [sp, #0x34]
	mov r8, r0
_022214B8:
	ldr r1, [fp, r7, lsl #2]
	mov r0, sl, lsl #1
	ldrh r2, [r1, r0]
	ldrh r1, [sp, #0x3a]
	mov r0, r7, lsl #4
	strh r2, [sp, #0x40]
	str r1, [sp]
	str r6, [sp, #4]
	add r2, r0, sb, lsl #2
	str r5, [sp, #8]
	add r0, sp, #0x40
	str r0, [sp, #0xc]
	ldr r0, [r4]
	ldrh r1, [sp, #0x34]
	ldr r0, [r0, r2]
	ldrh r2, [sp, #0x36]
	ldrh r3, [sp, #0x38]
	bl MOD13_0223A4F0
	ldrh r0, [sp, #0x34]
	add r8, r8, #1
	cmp r8, #0xc
	add r0, r0, #0x12
	add sl, sl, #1
	strh r0, [sp, #0x34]
	blt _022214B8
	cmp r7, #0
	bne _02221540
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x3c]
	ldr r2, [sp, #0x30]
	bl MOD13_02239B74
	ldr r1, [r4]
	add r1, r1, sb, lsl #2
	str r0, [r1, #0x104]
_02221540:
	ldr r0, [sp, #0x18]
	add sb, sb, #1
	add r0, r0, #0xc
	str r0, [sp, #0x18]
	cmp sb, #4
	blt _0222147C
	add r7, r7, #1
	cmp r7, #3
	blt _02221470
	mov r0, #0
	mov r1, #0x40
	mov r2, #1
	bl MOD13_02239E0C
	ldr r3, _022215F0 ; =0x0224303C
	mvn r1, #0
	ldr r4, [r3]
	mov r2, #0x200
	str r0, [r4, #0x114]
	ldr r0, [r3]
	mov r3, #0
	ldr r0, [r0, #0x114]
	bl MOD13_02239A1C
	ldr r0, _022215F0 ; =0x0224303C
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #2
	ldr r0, [r0, #0x114]
	bl MOD13_02239814
	mov r0, #0
	ldr r1, _02221608 ; =MOD13_02221118
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r3, _022215F0 ; =0x0224303C
	mov r1, #0
	ldr r4, [r3]
	mov r2, #0xc0
	str r0, [r4, #0x118]
	ldr r0, [r3]
	ldrb r0, [r0, #0x11d]
	bl MOD13_022201DC
	add sp, sp, #0x44
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022215EC: .word 0x0223ED2C
_022215F0: .word 0x0224303C
_022215F4: .word 0xC1FFFCFF
_022215F8: .word 0x0223ED20
_022215FC: .word 0x0223ED18
_02221600: .word 0x0223ED24
_02221604: .word 0x0223FB88
_02221608: .word MOD13_02221118

	arm_func_start MOD13_0222160C
MOD13_0222160C: ; 0x0222160C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r1, r0
	mov r0, #0
	bl MOD13_0223C110
	mov r5, #0
	ldr r4, _022216CC ; =0x02243040
_02221628:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x48]
	bl MOD13_02239AE8
	ldr r0, [r4]
	ldr r0, [r0, r5, lsl #2]
	bl MOD13_0223A978
	add r5, r5, #1
	cmp r5, #4
	blt _02221628
	ldr r4, _022216CC ; =0x02243040
	mov r5, #0
_02221658:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x40]
	bl MOD13_02239AE8
	add r5, r5, #1
	cmp r5, #2
	blt _02221658
	ldr r4, _022216CC ; =0x02243040
	mov r5, #0
_0222167C:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x38]
	bl MOD13_0223B974
	add r5, r5, #1
	cmp r5, #2
	blt _0222167C
	ldr r4, _022216CC ; =0x02243040
	mov r5, #0
_022216A0:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x10]
	bl MOD13_0223B974
	add r5, r5, #1
	cmp r5, #0xa
	blt _022216A0
	ldr r0, _022216CC ; =0x02243040
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022216CC: .word 0x02243040

	arm_func_start MOD13_022216D0
MOD13_022216D0: ; 0x022216D0
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0222173C ; =0x02243040
	mov r4, r0
	ldr r0, [r1]
	ldr r1, _02221740 ; =0x01FF0000
	ldr r3, [r0, #0x10]
	mov r0, #0
	ldr r2, [r3]
	and r1, r2, r1
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [r3]
	and r1, r1, #0xff
	str r1, [sp, #4]
	add r1, r1, #0xc
	str r1, [sp, #4]
	bl MOD13_02221B6C
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _02221744 ; =MOD13_0222160C
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222173C: .word 0x02243040
_02221740: .word 0x01FF0000
_02221744: .word MOD13_0222160C

	arm_func_start MOD13_02221748
MOD13_02221748: ; 0x02221748
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _022217B4 ; =0x02243040
	mov r4, r0
	ldr r0, [r1]
	ldr r1, _022217B8 ; =0x01FF0000
	ldr r3, [r0, #0x1c]
	mov r0, #1
	ldr r2, [r3]
	and r1, r2, r1
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [r3]
	and r1, r1, #0xff
	str r1, [sp, #4]
	add r1, r1, #0xc
	str r1, [sp, #4]
	bl MOD13_02221B6C
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _022217BC ; =MOD13_022216D0
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022217B4: .word 0x02243040
_022217B8: .word 0x01FF0000
_022217BC: .word MOD13_022216D0

	arm_func_start MOD13_022217C0
MOD13_022217C0: ; 0x022217C0
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0222182C ; =0x02243040
	mov r4, r0
	ldr r0, [r1]
	ldr r1, _02221830 ; =0x01FF0000
	ldr r3, [r0, #0x28]
	mov r0, #2
	ldr r2, [r3]
	and r1, r2, r1
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [r3]
	and r1, r1, #0xff
	str r1, [sp, #4]
	add r1, r1, #0xc
	str r1, [sp, #4]
	bl MOD13_02221B6C
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _02221834 ; =MOD13_02221748
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222182C: .word 0x02243040
_02221830: .word 0x01FF0000
_02221834: .word MOD13_02221748

	arm_func_start MOD13_02221838
MOD13_02221838: ; 0x02221838
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _022218A4 ; =0x02243040
	mov r4, r0
	ldr r0, [r1]
	ldr r1, _022218A8 ; =0x01FF0000
	ldr r3, [r0, #0x34]
	mov r0, #3
	ldr r2, [r3]
	and r1, r2, r1
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [r3]
	and r1, r1, #0xff
	str r1, [sp, #4]
	add r1, r1, #0xc
	str r1, [sp, #4]
	bl MOD13_02221B6C
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _022218AC ; =MOD13_022217C0
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022218A4: .word 0x02243040
_022218A8: .word 0x01FF0000
_022218AC: .word MOD13_022217C0

	arm_func_start MOD13_022218B0
MOD13_022218B0: ; 0x022218B0
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02221924 ; =0x02243040
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0
	ldr r0, [r0, #0x40]
	bl MOD13_02239ADC
	ldr r2, [r0]
	ldr r1, _02221928 ; =0x01FF0000
	and r1, r2, r1
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [r0]
	mov r0, #4
	and r1, r1, #0xff
	str r1, [sp, #4]
	add r1, r1, #0xc
	str r1, [sp, #4]
	bl MOD13_02221B6C
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r1, _0222192C ; =MOD13_02221838
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02221924: .word 0x02243040
_02221928: .word 0x01FF0000
_0222192C: .word MOD13_02221838

	arm_func_start MOD13_02221930
MOD13_02221930: ; 0x02221930
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _022219FC ; =0x02243040
	ldr r2, _02221A00 ; =0x0223F0BC
	ldr r3, [r1]
	ldrsb ip, [r3, #0x63]
	add r2, r2, ip, lsl #2
	ldrsb r2, [r0, r2]
	strb r2, [r3, #0x63]
	ldr r1, [r1]
	ldrsb r2, [r1, #0x63]
	cmp r2, #0xd
	bne _0222197C
	cmp r0, #1
	beq _02221974
	cmp r0, #3
	bne _0222197C
_02221974:
	strb ip, [r1, #0x64]
	b _022219E8
_0222197C:
	mvn r0, #0
	cmp r2, r0
	bne _022219B4
	ldrsb r0, [r1, #0x64]
	cmp r0, #1
	beq _0222199C
	cmp r0, #0xa
	bne _022219A8
_0222199C:
	mov r0, #0xa
	strb r0, [r1, #0x63]
	b _022219E8
_022219A8:
	mov r0, #0xb
	strb r0, [r1, #0x63]
	b _022219E8
_022219B4:
	mvn r0, #1
	cmp r2, r0
	bne _022219E8
	ldrsb r0, [r1, #0x64]
	cmp r0, #1
	beq _022219D4
	cmp r0, #0xa
	bne _022219E0
_022219D4:
	mov r0, #1
	strb r0, [r1, #0x63]
	b _022219E8
_022219E0:
	mov r0, #2
	strb r0, [r1, #0x63]
_022219E8:
	bl MOD13_02221A04
	mov r0, #8
	bl MOD13_0223424C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022219FC: .word 0x02243040
_02221A00: .word 0x0223F0BC

	arm_func_start MOD13_02221A04
MOD13_02221A04: ; 0x02221A04
	stmdb sp!, {r4, lr}
	ldr r0, _02221A84 ; =0x02243040
	ldr r1, [r0]
	ldrsb r0, [r1, #0x63]
	cmp r0, #0xb
	movle r4, #0x44
	ldr r0, [r1, #0x58]
	movgt r4, #0x45
	mov r1, #0
	bl MOD13_02239ADC
	mov r2, r0
	mov r1, r4
	mov r0, #0
	bl MOD13_02239E8C
	ldr r0, _02221A84 ; =0x02243040
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #2
	ldr r0, [r0, #0x58]
	bl MOD13_02239814
	ldr r0, _02221A84 ; =0x02243040
	ldr r2, _02221A88 ; =0x0223F084
	ldr r0, [r0]
	ldr r3, _02221A8C ; =0x0223F086
	ldrsb ip, [r0, #0x63]
	ldr r0, [r0, #0x58]
	mvn r1, #0
	mov ip, ip, lsl #2
	ldrh r2, [r2, ip]
	ldrh r3, [r3, ip]
	bl MOD13_02239888
	ldmia sp!, {r4, pc}
	.align 2, 0
_02221A84: .word 0x02243040
_02221A88: .word 0x0223F084
_02221A8C: .word 0x0223F086

	arm_func_start MOD13_02221A90
MOD13_02221A90: ; 0x02221A90
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #0
	addlt sp, sp, #4
	ldmltia sp!, {pc}
	cmp r0, #0xa
	bge _02221AE8
	ldr r2, _02221B60 ; =0x02243040
	ldr r3, _02221B64 ; =0x0223EFE8
	ldr r2, [r2]
	add sp, sp, #4
	add r0, r2, r0, lsl #2
	ldr ip, [r0, #0x10]
	ldr r0, [ip]
	bic r0, r0, #0xc00
	str r0, [ip]
	ldrh r2, [ip, #4]
	ldrb r0, [r3, r1]
	bic r1, r2, #0xf000
	orr r0, r1, r0, lsl #12
	strh r0, [ip, #4]
	ldmia sp!, {pc}
_02221AE8:
	sub r3, r0, #0xa
	cmp r3, #2
	bge _02221B30
	ldr r0, _02221B60 ; =0x02243040
	ldr r2, _02221B64 ; =0x0223EFE8
	ldr r0, [r0]
	add sp, sp, #4
	add r0, r0, r3, lsl #2
	ldr ip, [r0, #0x38]
	ldr r0, [ip]
	bic r0, r0, #0xc00
	str r0, [ip]
	ldrh r3, [ip, #4]
	ldrb r0, [r2, r1]
	bic r1, r3, #0xf000
	orr r0, r1, r0, lsl #12
	strh r0, [ip, #4]
	ldmia sp!, {pc}
_02221B30:
	ldr r2, _02221B60 ; =0x02243040
	ldr r3, _02221B68 ; =0x0223EFDC
	ldr r2, [r2]
	sub r0, r0, #0xc
	add r0, r2, r0, lsl #2
	ldrb r3, [r3, r1]
	ldr r0, [r0, #0x40]
	mvn r1, #0
	mov r2, #0
	bl MOD13_02239994
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02221B60: .word 0x02243040
_02221B64: .word 0x0223EFE8
_02221B68: .word 0x0223EFDC

	arm_func_start MOD13_02221B6C
MOD13_02221B6C: ; 0x02221B6C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x1c
	ldr r3, _02221DD8 ; =0x0223F00C
	ldr sb, _02221DDC ; =0x0223F014
	ldrb r5, [r3, #3]
	ldrb r8, [r3]
	ldrb r7, [r3, #1]
	strb r5, [sp, #0xb]
	mov r5, r0
	mov r0, #3
	mul r0, r5, r0
	ldrb r6, [r3, #2]
	ldrb ip, [r3, #4]
	ldr r2, _02221DE0 ; =0x0223F004
	strb r8, [sp, #8]
	strb r7, [sp, #9]
	strb r6, [sp, #0xa]
	strb ip, [sp, #0xc]
	ldrb r4, [sb]
	ldrb r3, [sb, #1]
	ldrb fp, [sb, #2]
	ldrb sl, [sb, #3]
	ldrb sb, [sb, #4]
	ldrb lr, [r2]
	ldrb r8, [r2, #1]
	ldrb r7, [r2, #2]
	ldrb r6, [r2, #3]
	ldrb r2, [r2, #4]
	strb r4, [sp, #0xd]
	add ip, sp, #8
	str r0, [sp, #4]
	ldrb r0, [ip, r5]
	strb r3, [sp, #0xe]
	strb r2, [sp, #0x16]
	mov r4, r1
	ldr r3, [sp, #4]
	strb fp, [sp, #0xf]
	strb sl, [sp, #0x10]
	strb sb, [sp, #0x11]
	strb lr, [sp, #0x12]
	strb r8, [sp, #0x13]
	strb r7, [sp, #0x14]
	strb r6, [sp, #0x15]
	cmp r0, #0
	mov r2, #0
	ble _02221C98
	and r1, r4, #0xff
	add r0, ip, r5
	ldr r6, _02221DE4 ; =0x02243040
	ldr r7, _02221DE8 ; =0x0223F05C
	ldr fp, _02221DEC ; =0xC1FFFCFF
	ldr ip, _02221DF0 ; =0x000001FF
	ldr lr, _02221DF4 ; =0xFE00FF00
_02221C40:
	ldr r8, [r6]
	mov sb, r3, lsl #2
	add r8, r8, r3, lsl #2
	ldr r8, [r8, #0x10]
	add r2, r2, #1
	ldr sl, [r8]
	and sl, sl, fp
	str sl, [r8]
	ldrh r8, [r7, sb]
	ldr sb, [r6]
	add sb, sb, r3, lsl #2
	ldr sb, [sb, #0x10]
	and r8, r8, ip
	ldr sl, [sb]
	add r3, r3, #1
	and sl, sl, lr
	orr sl, sl, r1
	orr r8, sl, r8, lsl #16
	str r8, [sb]
	ldrb r8, [r0]
	cmp r2, r8
	blt _02221C40
_02221C98:
	cmp r5, #4
	bge _02221CD4
	ldr r0, _02221DE4 ; =0x02243040
	mov r2, #2
	ldr r3, [r0]
	ldr r0, [sp, #4]
	str r2, [sp]
	ldr r1, _02221DE8 ; =0x0223F05C
	mov r0, r0, lsl #2
	ldrh r1, [r1, r0]
	add r2, r3, r5, lsl #2
	ldr r0, [r3, r5, lsl #2]
	ldr r3, [r2, #0x48]
	mov r2, r4
	bl MOD13_0223A440
_02221CD4:
	add r3, sp, #0xd
	ldrb r1, [r3, r5]
	mov r0, #0
	cmp r1, #0
	ble _02221D58
	and r2, r4, #0xff
	add r1, r3, r5
	ldr r8, _02221DE4 ; =0x02243040
	ldr sb, _02221DF8 ; =0x0223F024
	ldr r3, _02221DEC ; =0xC1FFFCFF
	ldr r6, _02221DF0 ; =0x000001FF
	ldr r7, _02221DF4 ; =0xFE00FF00
_02221D04:
	ldr sl, [r8]
	mov fp, r0, lsl #2
	add sl, sl, r0, lsl #2
	ldr sl, [sl, #0x38]
	ldr ip, [sl]
	and ip, ip, r3
	str ip, [sl]
	ldr ip, [r8]
	ldrh sl, [sb, fp]
	add fp, ip, r0, lsl #2
	ldr fp, [fp, #0x38]
	and sl, sl, r6
	ldr ip, [fp]
	add r0, r0, #1
	and ip, ip, r7
	orr ip, ip, r2
	orr sl, ip, sl, lsl #16
	str sl, [fp]
	ldrb sl, [r1]
	cmp r0, sl
	blt _02221D04
_02221D58:
	add r1, sp, #0x12
	ldrb r0, [r1, r5]
	mov r8, #0
	cmp r0, #0
	addle sp, sp, #0x1c
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add sb, r1, r5
	ldr sl, _02221DE4 ; =0x02243040
	ldr r5, _02221DFC ; =0x0223F02C
	mov r6, r8
	mvn r7, #0
_02221D84:
	ldr r0, [sl]
	mov r1, r7
	add r0, r0, r8, lsl #2
	ldr r0, [r0, #0x40]
	mov r2, r6
	mov r3, r6
	bl MOD13_02239A1C
	ldr r0, [sl]
	mov r1, r8, lsl #2
	add r0, r0, r8, lsl #2
	ldrh r2, [r5, r1]
	ldr r0, [r0, #0x40]
	mov r1, r7
	mov r3, r4
	bl MOD13_02239888
	ldrb r0, [sb]
	add r8, r8, #1
	cmp r8, r0
	blt _02221D84
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02221DD8: .word 0x0223F00C
_02221DDC: .word 0x0223F014
_02221DE0: .word 0x0223F004
_02221DE4: .word 0x02243040
_02221DE8: .word 0x0223F05C
_02221DEC: .word 0xC1FFFCFF
_02221DF0: .word 0x000001FF
_02221DF4: .word 0xFE00FF00
_02221DF8: .word 0x0223F024
_02221DFC: .word 0x0223F02C

	arm_func_start MOD13_02221E00
MOD13_02221E00: ; 0x02221E00
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x20
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02221E20
	mov r0, #0
	bl MOD13_02221930
_02221E20:
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02221E38
	mov r0, #1
	bl MOD13_02221930
_02221E38:
	mov r0, #0x10
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02221E50
	mov r0, #2
	bl MOD13_02221930
_02221E50:
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02221E68
	mov r0, #3
	bl MOD13_02221930
_02221E68:
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02221F28
	ldr r0, _02221FB0 ; =0x02243040
	ldr r0, [r0]
	ldrsb r2, [r0, #0x63]
	cmp r2, #0xa
	bge _02221EB8
	ldrb r1, [r0, #0x67]
	cmp r1, #0
	ldrne r1, _02221FB4 ; =0x0223F034
	addne sp, sp, #4
	ldrneb r1, [r1, r2]
	strneb r1, [r0, #0x60]
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #4
	ldmia sp!, {pc}
_02221EB8:
	sub r1, r2, #0xa
	cmp r1, #2
	bge _02221F18
	cmp r1, #0
	bne _02221ED8
	ldrb r1, [r0, #0x66]
	cmp r1, #0
	beq _02221EF0
_02221ED8:
	sub r1, r2, #0xa
	cmp r1, #1
	bne _02221F00
	ldrb r1, [r0, #0x68]
	cmp r1, #0
	bne _02221F00
_02221EF0:
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #4
	ldmia sp!, {pc}
_02221F00:
	ldr r1, _02221FB8 ; =0x0223EFF0
	sub r2, r2, #0xa
	ldrb r1, [r1, r2]
	add sp, sp, #4
	strb r1, [r0, #0x60]
	ldmia sp!, {pc}
_02221F18:
	ldr r1, _02221FBC ; =0x0223EFEC
	sub r2, r2, #0xc
	ldrb r1, [r1, r2]
	strb r1, [r0, #0x60]
_02221F28:
	mov r0, #2
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02221F8C
	ldr r0, _02221FB0 ; =0x02243040
	ldr r1, [r0]
	ldrb r0, [r1, #0x66]
	cmp r0, #0
	bne _02221F7C
	ldrb r0, [r1, #0x69]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _02221FB0 ; =0x02243040
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x69]
	ldmia sp!, {pc}
_02221F7C:
	mov r0, #0x10
	strb r0, [r1, #0x60]
	add sp, sp, #4
	ldmia sp!, {pc}
_02221F8C:
	mov r0, #2
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _02221FB0 ; =0x02243040
	movne r1, #0
	ldrne r0, [r0]
	strneb r1, [r0, #0x69]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02221FB0: .word 0x02243040
_02221FB4: .word 0x0223F034
_02221FB8: .word 0x0223EFF0
_02221FBC: .word 0x0223EFEC

	arm_func_start MOD13_02221FC0
MOD13_02221FC0: ; 0x02221FC0
	stmdb sp!, {r4, lr}
	ldr r1, _02222008 ; =0x02243040
	mov r4, r0
	ldr r1, [r1]
	ldrsb r1, [r1, #0x62]
	cmp r4, r1
	ldmeqia sp!, {r4, pc}
	mov r1, #1
	bl MOD13_02221A90
	ldr r0, _02222008 ; =0x02243040
	mov r1, #0
	ldr r0, [r0]
	ldrsb r0, [r0, #0x62]
	bl MOD13_02221A90
	ldr r0, _02222008 ; =0x02243040
	ldr r0, [r0]
	strb r4, [r0, #0x62]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02222008: .word 0x02243040

	arm_func_start MOD13_0222200C
MOD13_0222200C: ; 0x0222200C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r0, _022221DC ; =0x0223F75C
	bl MOD13_0223B320
	cmp r0, #0
	beq _022221BC
	ldr r6, _022221E0 ; =0x0223F05C
	mov r7, #0
	ldr r5, _022221E4 ; =0x0223EFF4
	add r4, sp, #0
_02222034:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B320
	cmp r0, #0
	beq _02222074
	ldr r0, _022221E8 ; =0x02243040
	ldr r0, [r0]
	ldrsb r0, [r0, #0x61]
	cmp r0, r7
	bne _022221BC
	mov r0, r7
	bl MOD13_02221FC0
	b _022221C4
_02222074:
	add r7, r7, #1
	cmp r7, #0xa
	add r6, r6, #4
	blt _02222034
	ldr r7, _022221EC ; =0x0223F024
	mov r6, #0
	ldr r5, _022221F0 ; =0x0223EFFC
	add r4, sp, #0
_02222094:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B320
	cmp r0, #0
	beq _0222214C
	ldr r1, _022221E8 ; =0x02243040
	add r0, r6, #0xa
	ldr r1, [r1]
	ldrsb r1, [r1, #0x61]
	cmp r1, r0
	bne _022221BC
	bl MOD13_02221FC0
	cmp r6, #0
	bne _022221C4
	ldr r0, _022221E8 ; =0x02243040
	ldr r2, [r0]
	ldrb r1, [r2, #0x65]
	add r1, r1, #1
	strb r1, [r2, #0x65]
	ldr r2, [r0]
	ldrb r1, [r2, #0x65]
	cmp r1, #0x28
	addlo sp, sp, #0xc
	ldmloia sp!, {r4, r5, r6, r7, pc}
	ldrb r1, [r2, #0x66]
	cmp r1, #0
	bne _0222212C
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _022221E8 ; =0x02243040
	mvn r1, #0
	ldr r0, [r0]
	add sp, sp, #0xc
	strb r1, [r0, #0x61]
	ldmia sp!, {r4, r5, r6, r7, pc}
_0222212C:
	mov r1, #0x10
	strb r1, [r2, #0x60]
	ldr r1, [r0]
	add sp, sp, #0xc
	ldrb r0, [r1, #0x65]
	sub r0, r0, #7
	strb r0, [r1, #0x65]
	ldmia sp!, {r4, r5, r6, r7, pc}
_0222214C:
	add r6, r6, #1
	cmp r6, #2
	add r7, r7, #4
	blt _02222094
	ldr r7, _022221F4 ; =0x0223F02C
	mov r6, #0
	ldr r5, _022221F8 ; =0x0223F000
	add r4, sp, #0
_0222216C:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B320
	cmp r0, #0
	beq _022221AC
	ldr r1, _022221E8 ; =0x02243040
	add r0, r6, #0xc
	ldr r1, [r1]
	ldrsb r1, [r1, #0x61]
	cmp r1, r0
	bne _022221BC
	bl MOD13_02221FC0
	b _022221C4
_022221AC:
	add r6, r6, #1
	cmp r6, #2
	add r7, r7, #4
	blt _0222216C
_022221BC:
	mvn r0, #0
	bl MOD13_02221FC0
_022221C4:
	ldr r0, _022221E8 ; =0x02243040
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x65]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_022221DC: .word 0x0223F75C
_022221E0: .word 0x0223F05C
_022221E4: .word 0x0223EFF4
_022221E8: .word 0x02243040
_022221EC: .word 0x0223F024
_022221F0: .word 0x0223EFFC
_022221F4: .word 0x0223F02C
_022221F8: .word 0x0223F000

	arm_func_start MOD13_022221FC
MOD13_022221FC: ; 0x022221FC
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r1, _022223A0 ; =0x02243040
	ldr r0, _022223A4 ; =0x0223F75C
	ldr r1, [r1]
	mov r2, #0
	strb r2, [r1, #0x60]
	bl MOD13_0223B1DC
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r7, _022223A8 ; =0x0223F05C
	mov r4, #0
	ldr r6, _022223AC ; =0x0223EFF4
	add r5, sp, #0
_02222238:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02222290
	ldr r0, _022223A0 ; =0x02243040
	ldr r2, [r0]
	ldrsb r1, [r2, #0x61]
	cmp r1, r4
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r1, _022223B0 ; =0x0223F034
	ldrb r1, [r1, r4]
	strb r1, [r2, #0x60]
	ldr r0, [r0]
	strb r4, [r0, #0x63]
	bl MOD13_02221A04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02222290:
	add r4, r4, #1
	cmp r4, #0xa
	add r7, r7, #4
	blt _02222238
	ldr r7, _022223B4 ; =0x0223F024
	mov r4, #0
	ldr r6, _022223B8 ; =0x0223EFFC
	add r5, sp, #0
_022222B0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _0222230C
	ldr r0, _022223A0 ; =0x02243040
	add r2, r4, #0xa
	ldr r3, [r0]
	ldrsb r1, [r3, #0x61]
	cmp r1, r2
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r1, _022223BC ; =0x0223EFF0
	ldrb r1, [r1, r4]
	strb r1, [r3, #0x60]
	ldr r0, [r0]
	strb r2, [r0, #0x63]
	bl MOD13_02221A04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_0222230C:
	add r4, r4, #1
	cmp r4, #2
	add r7, r7, #4
	blt _022222B0
	ldr r7, _022223C0 ; =0x0223F02C
	mov r4, #0
	ldr r6, _022223C4 ; =0x0223F000
	add r5, sp, #0
_0222232C:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02222388
	ldr r0, _022223A0 ; =0x02243040
	add r2, r4, #0xc
	ldr r3, [r0]
	ldrsb r1, [r3, #0x61]
	cmp r1, r2
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r1, _022223C8 ; =0x0223EFEC
	ldrb r1, [r1, r4]
	strb r1, [r3, #0x60]
	ldr r0, [r0]
	strb r2, [r0, #0x63]
	bl MOD13_02221A04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_02222388:
	add r4, r4, #1
	cmp r4, #2
	add r7, r7, #4
	blt _0222232C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_022223A0: .word 0x02243040
_022223A4: .word 0x0223F75C
_022223A8: .word 0x0223F05C
_022223AC: .word 0x0223EFF4
_022223B0: .word 0x0223F034
_022223B4: .word 0x0223F024
_022223B8: .word 0x0223EFFC
_022223BC: .word 0x0223EFF0
_022223C0: .word 0x0223F02C
_022223C4: .word 0x0223F000
_022223C8: .word 0x0223EFEC

	arm_func_start MOD13_022223CC
MOD13_022223CC: ; 0x022223CC
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r0, _02222588 ; =0x0223F75C
	bl MOD13_0223B2B4
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _0222258C ; =0x02243040
	mvn r1, #0
	ldr r0, [r0]
	ldr r7, _02222590 ; =0x0223F05C
	strb r1, [r0, #0x61]
	mov r4, #0
	ldr r6, _02222594 ; =0x0223EFF4
	add r5, sp, #0
_02222408:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02222468
	ldr r0, _0222258C ; =0x02243040
	ldr r0, [r0]
	ldrb r0, [r0, #0x67]
	cmp r0, #0
	bne _0222244C
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_0222244C:
	mov r0, #0
	bl MOD13_0223424C
	ldr r0, _0222258C ; =0x02243040
	add sp, sp, #0xc
	ldr r0, [r0]
	strb r4, [r0, #0x61]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02222468:
	add r4, r4, #1
	cmp r4, #0xa
	add r7, r7, #4
	blt _02222408
	ldr r7, _02222598 ; =0x0223F024
	mov r4, #0
	ldr r6, _0222259C ; =0x0223EFFC
	add r5, sp, #0
_02222488:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_0223AB74
	mov r0, r5
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02222510
	cmp r4, #0
	bne _022224C4
	ldr r0, _0222258C ; =0x02243040
	ldr r0, [r0]
	ldrb r0, [r0, #0x66]
	cmp r0, #0
	beq _022224E0
_022224C4:
	cmp r4, #1
	bne _022224F0
	ldr r0, _0222258C ; =0x02243040
	ldr r0, [r0]
	ldrb r0, [r0, #0x68]
	cmp r0, #0
	bne _022224F0
_022224E0:
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_022224F0:
	mov r0, #0
	bl MOD13_0223424C
	ldr r0, _0222258C ; =0x02243040
	add r1, r4, #0xa
	ldr r0, [r0]
	add sp, sp, #0xc
	strb r1, [r0, #0x61]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02222510:
	add r4, r4, #1
	cmp r4, #2
	add r7, r7, #4
	blt _02222488
	ldr r7, _022225A0 ; =0x0223F02C
	mov r6, #0
	ldr r5, _022225A4 ; =0x0223F000
	add r4, sp, #0
_02222530:
	mov r0, r7
	mov r1, r5
	mov r2, r4
	bl MOD13_0223AB74
	mov r0, r4
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02222570
	mov r0, #0
	bl MOD13_0223424C
	ldr r0, _0222258C ; =0x02243040
	add r1, r6, #0xc
	ldr r0, [r0]
	add sp, sp, #0xc
	strb r1, [r0, #0x61]
	ldmia sp!, {r4, r5, r6, r7, pc}
_02222570:
	add r6, r6, #1
	cmp r6, #2
	add r7, r7, #4
	blt _02222530
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02222588: .word 0x0223F75C
_0222258C: .word 0x02243040
_02222590: .word 0x0223F05C
_02222594: .word 0x0223EFF4
_02222598: .word 0x0223F024
_0222259C: .word 0x0223EFFC
_022225A0: .word 0x0223F02C
_022225A4: .word 0x0223F000

	arm_func_start MOD13_022225A8
MOD13_022225A8: ; 0x022225A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022223CC
	bl MOD13_022221FC
	bl MOD13_0222200C
	bl MOD13_02221E00
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02222640 ; =0x02243040
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #0x40]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, _02222644 ; =0x0223F02C
	ldr r1, [sp, #4]
	ldrh r0, [r0, #2]
	sub r1, r1, #0xc
	str r1, [sp, #4]
	cmp r1, r0
	ble _0222261C
	mov r0, #4
	bl MOD13_02221B6C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222261C:
	mov r1, r0
	mov r0, #4
	bl MOD13_02221B6C
	bl MOD13_02221A04
	ldr r1, _02222648 ; =MOD13_022225A8
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02222640: .word 0x02243040
_02222644: .word 0x0223F02C
_02222648: .word MOD13_022225A8

	arm_func_start MOD13_0222264C
MOD13_0222264C: ; 0x0222264C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _022226D8 ; =0x02243040
	ldr r2, _022226DC ; =0x0223F05C
	ldr r3, [r1]
	ldr r1, _022226E0 ; =0x01FF0000
	ldr ip, [r3, #0x34]
	ldrh r2, [r2, #0x26]
	ldr r3, [ip]
	mov r4, r0
	and r0, r3, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r1, r0, #0xc
	str r0, [sp, #4]
	str r1, [sp, #4]
	cmp r1, r2
	ble _022226AC
	mov r0, #3
	bl MOD13_02221B6C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022226AC:
	mov r1, r2
	mov r0, #3
	bl MOD13_02221B6C
	mov r0, #4
	mov r1, #0xc0
	bl MOD13_02221B6C
	ldr r1, _022226E4 ; =0x022225C8
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022226D8: .word 0x02243040
_022226DC: .word 0x0223F05C
_022226E0: .word 0x01FF0000
_022226E4: .word 0x022225C8

	arm_func_start MOD13_022226E8
MOD13_022226E8: ; 0x022226E8
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02222774 ; =0x02243040
	ldr r2, _02222778 ; =0x0223F05C
	ldr r3, [r1]
	ldr r1, _0222277C ; =0x01FF0000
	ldr ip, [r3, #0x28]
	ldrh r2, [r2, #0x1a]
	ldr r3, [ip]
	mov r4, r0
	and r0, r3, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r1, r0, #0xc
	str r0, [sp, #4]
	str r1, [sp, #4]
	cmp r1, r2
	ble _02222748
	mov r0, #2
	bl MOD13_02221B6C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02222748:
	mov r1, r2
	mov r0, #2
	bl MOD13_02221B6C
	mov r0, #3
	mov r1, #0xc0
	bl MOD13_02221B6C
	ldr r1, _02222780 ; =MOD13_0222264C
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02222774: .word 0x02243040
_02222778: .word 0x0223F05C
_0222277C: .word 0x01FF0000
_02222780: .word MOD13_0222264C

	arm_func_start MOD13_02222784
MOD13_02222784: ; 0x02222784
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02222810 ; =0x02243040
	ldr r2, _02222814 ; =0x0223F05C
	ldr r3, [r1]
	ldr r1, _02222818 ; =0x01FF0000
	ldr ip, [r3, #0x1c]
	ldrh r2, [r2, #0xe]
	ldr r3, [ip]
	mov r4, r0
	and r0, r3, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r1, r0, #0xc
	str r0, [sp, #4]
	str r1, [sp, #4]
	cmp r1, r2
	ble _022227E4
	mov r0, #1
	bl MOD13_02221B6C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022227E4:
	mov r1, r2
	mov r0, #1
	bl MOD13_02221B6C
	mov r0, #2
	mov r1, #0xc0
	bl MOD13_02221B6C
	ldr r1, _0222281C ; =MOD13_022226E8
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02222810: .word 0x02243040
_02222814: .word 0x0223F05C
_02222818: .word 0x01FF0000
_0222281C: .word MOD13_022226E8

	arm_func_start MOD13_02222820
MOD13_02222820: ; 0x02222820
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _022228AC ; =0x02243040
	ldr r2, _022228B0 ; =0x0223F05C
	ldr r3, [r1]
	ldr r1, _022228B4 ; =0x01FF0000
	ldr ip, [r3, #0x10]
	ldrh r2, [r2, #2]
	ldr r3, [ip]
	mov r4, r0
	and r0, r3, r1
	mov r0, r0, lsr #0x10
	str r0, [sp]
	ldr r0, [ip]
	and r0, r0, #0xff
	sub r1, r0, #0xc
	str r0, [sp, #4]
	str r1, [sp, #4]
	cmp r1, r2
	ble _02222880
	mov r0, #0
	bl MOD13_02221B6C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02222880:
	mov r1, r2
	mov r0, #0
	bl MOD13_02221B6C
	mov r0, #1
	mov r1, #0xc0
	bl MOD13_02221B6C
	ldr r1, _022228B8 ; =MOD13_02222784
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022228AC: .word 0x02243040
_022228B0: .word 0x0223F05C
_022228B4: .word 0x01FF0000
_022228B8: .word MOD13_02222784

	arm_func_start MOD13_022228BC
MOD13_022228BC: ; 0x022228BC
	ldr r0, _022228D4 ; =0x02243040
	ldr r0, [r0]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_022228D4: .word 0x02243040

	arm_func_start MOD13_022228D8
MOD13_022228D8: ; 0x022228D8
	ldr r1, _022228E8 ; =0x02243040
	ldr r1, [r1]
	strb r0, [r1, #0x68]
	bx lr
	.align 2, 0
_022228E8: .word 0x02243040

	arm_func_start MOD13_022228EC
MOD13_022228EC: ; 0x022228EC
	ldr r1, _022228FC ; =0x02243040
	ldr r1, [r1]
	strb r0, [r1, #0x67]
	bx lr
	.align 2, 0
_022228FC: .word 0x02243040

	arm_func_start MOD13_02222900
MOD13_02222900: ; 0x02222900
	ldr r1, _02222910 ; =0x02243040
	ldr r1, [r1]
	strb r0, [r1, #0x66]
	bx lr
	.align 2, 0
_02222910: .word 0x02243040

	arm_func_start MOD13_02222914
MOD13_02222914: ; 0x02222914
	ldr r0, _02222924 ; =0x02243040
	ldr r0, [r0]
	ldrb r0, [r0, #0x60]
	bx lr
	.align 2, 0
_02222924: .word 0x02243040

	arm_func_start MOD13_02222928
MOD13_02222928: ; 0x02222928
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222295C ; =0x02243040
	ldr r0, [r0]
	ldr r0, [r0, #0x58]
	bl MOD13_02239AE8
	ldr r0, _0222295C ; =0x02243040
	ldr r1, _02222960 ; =MOD13_022218B0
	ldr r0, [r0]
	ldr r0, [r0, #0x5c]
	bl MOD13_0223C130
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222295C: .word 0x02243040
_02222960: .word MOD13_022218B0

	arm_func_start MOD13_02222964
MOD13_02222964: ; 0x02222964
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x3c
	ldr r1, _02222CCC ; =0x0223F01C
	ldr r0, _02222CD0 ; =0x0223EFF4
	ldrh r2, [r1, #4]
	ldrh r4, [r1, #6]
	ldrh r6, [r1]
	ldrh r5, [r1, #2]
	ldrh r3, [r0]
	strh r2, [sp, #0x30]
	ldrh r2, [r0, #2]
	strh r4, [sp, #0x32]
	mov r0, #0x6c
	mov r1, #4
	strh r6, [sp, #0x2c]
	strh r5, [sp, #0x2e]
	strh r3, [sp, #0x30]
	strh r2, [sp, #0x32]
	bl MOD13_0223AFE0
	ldr r8, _02222CD4 ; =0x02243040
	mov r1, #0x1f
	str r0, [r8]
	strb r1, [r0, #0x60]
	ldr r0, [r8]
	mov r6, #0
	strb r6, [r0, #0x63]
	ldr r0, [r8]
	mov r1, #1
	strb r1, [r0, #0x66]
	ldr r0, [r8]
	strb r1, [r0, #0x67]
	ldr r0, [r8]
	strb r1, [r0, #0x68]
	mov r5, r6
	mov r4, #0x36
	ldr r7, _02222CD8 ; =0xC1FFFCFF
_022229F4:
	mov r0, r5
	mov r1, r4
	bl MOD13_02239E54
	ldr r1, [r8]
	add r1, r1, r6, lsl #2
	str r0, [r1, #0x10]
	ldr r0, [r8]
	add r0, r0, r6, lsl #2
	ldr r1, [r0, #0x10]
	ldr r0, [r1]
	and r0, r0, r7
	orr r0, r0, #0x200
	str r0, [r1]
	ldr r0, [r8]
	add r0, r0, r6, lsl #2
	ldr r1, [r0, #0x10]
	add r6, r6, #1
	ldrh r0, [r1, #4]
	cmp r6, #0xa
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	blt _022229F4
	ldr r6, _02222CDC ; =0x0223EFE0
	mov r5, #0
	ldr r8, _02222CD4 ; =0x02243040
	mov r4, r5
	ldr r7, _02222CD8 ; =0xC1FFFCFF
_02222A64:
	ldrb r1, [r6]
	mov r0, r4
	bl MOD13_02239E54
	ldr r1, [r8]
	add r6, r6, #1
	add r1, r1, r5, lsl #2
	str r0, [r1, #0x38]
	ldr r0, [r8]
	add r0, r0, r5, lsl #2
	ldr r1, [r0, #0x38]
	ldr r0, [r1]
	and r0, r0, r7
	orr r0, r0, #0x200
	str r0, [r1]
	ldr r0, [r8]
	add r0, r0, r5, lsl #2
	ldr r1, [r0, #0x38]
	add r5, r5, #1
	ldrh r0, [r1, #4]
	cmp r5, #2
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	blt _02222A64
	ldr sl, _02222CE0 ; =0x0223EFE4
	mov sb, #0
	ldr r4, _02222CD4 ; =0x02243040
	mov fp, sb
	str sb, [sp, #0x1c]
	mov r8, #1
	mvn r7, #0
	mov r6, #0x200
	mov r5, #3
_02222AE8:
	ldrb r1, [sl]
	mov r0, fp
	mov r2, r8
	bl MOD13_02239E0C
	ldr r2, [r4]
	ldr r3, [sp, #0x1c]
	add r2, r2, sb, lsl #2
	str r0, [r2, #0x40]
	ldr r0, [r4]
	mov r1, r7
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #0x40]
	mov r2, r6
	bl MOD13_02239A1C
	ldr r0, [r4]
	mov r1, r7
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #0x40]
	mov r2, r5
	bl MOD13_02239814
	add sb, sb, #1
	add sl, sl, #1
	cmp sb, #2
	blt _02222AE8
	ldr r1, _02222CE4 ; =0x0223EFF8
	mov r8, #0
	ldrh r0, [r1, #2]
	ldr r7, _02222CE8 ; =0x0223F040
	ldr r4, _02222CD4 ; =0x02243040
	str r0, [sp, #0x14]
	ldrh r0, [r1]
	str r8, [sp, #0x10]
	strh r8, [sp, #0x3a]
	str r0, [sp, #0x18]
	add fp, sp, #0x38
	str r8, [sp, #0x28]
	str r8, [sp, #0x20]
	str r8, [sp, #0x24]
	mov r6, #2
	mov r5, #0x480
_02222B88:
	add r0, sp, #0x34
	str r0, [sp]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x14]
	mov r1, r0
	str r1, [sp, #4]
	ldr r1, [sp, #0x18]
	mov r3, r0
	bl MOD13_0223A9A4
	ldr r1, [r4]
	ldr sl, [sp, #0x10]
	str r0, [r1, r8, lsl #2]
	ldr r0, [sp, #0x24]
	strh r0, [sp, #0x2c]
	mov sb, r0
_02222BC4:
	mov r0, sl, lsl #1
	ldrh r1, [r7, r0]
	ldrh r0, [sp, #0x32]
	strh r1, [sp, #0x38]
	str r0, [sp]
	str r6, [sp, #4]
	str r5, [sp, #8]
	str fp, [sp, #0xc]
	ldr r0, [r4]
	ldrh r1, [sp, #0x2c]
	ldr r0, [r0, r8, lsl #2]
	ldrh r2, [sp, #0x2e]
	ldrh r3, [sp, #0x30]
	bl MOD13_0223A4F0
	add sb, sb, #1
	cmp sb, #3
	add sl, sl, #1
	ldrh r0, [sp, #0x2c]
	add r0, r0, #0x20
	strh r0, [sp, #0x2c]
	blt _02222BC4
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x34]
	mov r2, r0
	bl MOD13_02239B74
	ldr r1, [sp, #0x10]
	ldr r2, [r4]
	add r1, r1, #3
	str r1, [sp, #0x10]
	add r1, r2, r8, lsl #2
	add r8, r8, #1
	str r0, [r1, #0x48]
	cmp r8, #4
	blt _02222B88
	mov r0, #0
	mov r1, #0x44
	mov r2, #1
	bl MOD13_02239E0C
	ldr r3, _02222CD4 ; =0x02243040
	mvn r1, #0
	ldr r4, [r3]
	mov r2, #0x200
	str r0, [r4, #0x58]
	ldr r0, [r3]
	mov r3, #0
	ldr r0, [r0, #0x58]
	bl MOD13_02239A1C
	ldr r0, _02222CD4 ; =0x02243040
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #2
	ldr r0, [r0, #0x58]
	bl MOD13_02239814
	mov r0, #0
	ldr r1, _02222CEC ; =MOD13_02222820
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r2, _02222CD4 ; =0x02243040
	mov r1, #0xc0
	ldr r2, [r2]
	str r0, [r2, #0x5c]
	mov r0, #0
	bl MOD13_02221B6C
	add sp, sp, #0x3c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02222CCC: .word 0x0223F01C
_02222CD0: .word 0x0223EFF4
_02222CD4: .word 0x02243040
_02222CD8: .word 0xC1FFFCFF
_02222CDC: .word 0x0223EFE0
_02222CE0: .word 0x0223EFE4
_02222CE4: .word 0x0223EFF8
_02222CE8: .word 0x0223F040
_02222CEC: .word MOD13_02222820

	arm_func_start MOD13_02222CF0
MOD13_02222CF0: ; 0x02222CF0
	ldr ip, _02222CF8 ; =MOD13_0223AF48
	bx ip
	.align 2, 0
_02222CF8: .word MOD13_0223AF48

	arm_func_start MOD13_02222CFC
MOD13_02222CFC: ; 0x02222CFC
	ldr ip, _02222D08 ; =MOD13_0223B004
	mov r1, #0x20
	bx ip
	.align 2, 0
_02222D08: .word MOD13_0223B004

	arm_func_start MOD13_02222D0C
MOD13_02222D0C: ; 0x02222D0C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02222D74 ; =0x02243048
	ldr r0, [r0]
	blx MOD13_02219798
	cmp r0, #0
	ldreq r1, _02222D78 ; =0x02243044
	moveq r0, #1
	streqb r0, [r1]
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _02222D74 ; =0x02243048
	ldr r0, [r0]
	ldrb r0, [r0, #0x116]
	cmp r0, #1
	beq _02222D5C
	add r0, r0, #0xfd
	and r0, r0, #0xff
	cmp r0, #2
	bhi _02222D68
_02222D5C:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {pc}
_02222D68:
	mov r0, #2
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02222D74: .word 0x02243048
_02222D78: .word 0x02243044

	arm_func_start MOD13_02222D7C
MOD13_02222D7C: ; 0x02222D7C
	stmdb sp!, {r4, lr}
	mov r4, r0
	blx MOD13_02219C9C
	cmp r4, #0
	beq _02222DC0
	ldr r0, _02222DCC ; =0x02243048
	ldr r1, [r0]
	ldrb r0, [r1, #0x116]
	cmp r0, #0
	bne _02222DC0
	ldr r0, _02222DD0 ; =0x02243044
	ldrb r0, [r0]
	cmp r0, #1
	bne _02222DC0
	ldr r0, _02222DD4 ; =0x00000117
	add r0, r1, r0
	bl MOD13_0223390C
_02222DC0:
	ldr r0, _02222DCC ; =0x02243048
	bl MOD13_0223AF90
	ldmia sp!, {r4, pc}
	.align 2, 0
_02222DCC: .word 0x02243048
_02222DD0: .word 0x02243044
_02222DD4: .word 0x00000117

	arm_func_start MOD13_02222DD8
MOD13_02222DD8: ; 0x02222DD8
	stmdb sp!, {lr}
	sub sp, sp, #0x104
	mov r0, #0x26c
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, _02222ED4 ; =0x02243048
	ldr r3, _02222ED8 ; =0x02243044
	str r0, [r1]
	mov r0, #0
	add r1, sp, #0
	mov r2, #0x104
	strb r0, [r3]
	bl MIi_CpuClear16
	mov r3, #0x50
	mov r2, #0xc
	ldr r0, _02222EDC ; =0x0223F0F4
	add r1, sp, #4
	strb r3, [sp]
	strh r2, [sp, #2]
	bl MI_CpuCopy8
	ldr r0, _02222ED4 ; =0x02243048
	mov r2, #3
	ldr r1, [r0]
	add ip, sp, #0
	strh r2, [r1]
	ldr lr, [r0]
	mov r2, #0x41
	add r3, lr, #2
_02222E48:
	ldrh r1, [ip], #2
	ldrh r0, [ip], #2
	subs r2, r2, #1
	strh r1, [r3], #2
	strh r0, [r3], #2
	bne _02222E48
	ldr r1, _02222ED4 ; =0x02243048
	add r0, lr, #0x100
	mov r3, #1
	strh r3, [r0, #6]
	ldr r0, [r1]
	mvn r2, #0
	add r0, r0, #0x100
	strh r2, [r0, #8]
	ldr r0, [r1]
	add r0, r0, #0x100
	strh r3, [r0, #0xa]
	ldr r0, [r1]
	add r0, r0, #0x100
	strh r2, [r0, #0xc]
	ldr r0, [r1]
	add r0, r0, #0x100
	strh r2, [r0, #0xe]
	ldr r0, [r1]
	add r0, r0, #0x110
	bl OS_GetMacAddress
	ldr r0, _02222EE0 ; =MOD13_02222CFC
	ldr r1, _02222EE4 ; =MOD13_02222CF0
	blx MOD13_02219D58
	cmp r0, #0
	addeq sp, sp, #0x104
	ldmeqia sp!, {pc}
	bl OS_Terminate
	add sp, sp, #0x104
	ldmia sp!, {pc}
	.align 2, 0
_02222ED4: .word 0x02243048
_02222ED8: .word 0x02243044
_02222EDC: .word 0x0223F0F4
_02222EE0: .word MOD13_02222CFC
_02222EE4: .word MOD13_02222CF0

	arm_func_start MOD13_02222EE8
MOD13_02222EE8: ; 0x02222EE8
	ldr r0, _02222EF8 ; =0x02243050
	mov r1, #1
	strb r1, [r0]
	bx lr
	.align 2, 0
_02222EF8: .word 0x02243050

	arm_func_start MOD13_02222EFC
MOD13_02222EFC: ; 0x02222EFC
	ldr r1, _02222F18 ; =0x02243058
	ldr r1, [r1]
	mov r1, r1, lsr #4
	ands r0, r1, r0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_02222F18: .word 0x02243058

	arm_func_start MOD13_02222F1C
MOD13_02222F1C: ; 0x02222F1C
	ldr r0, _02222F30 ; =0x02243058
	ldr r0, [r0]
	mov r0, r0, lsl #0x1c
	mov r0, r0, lsr #0x1c
	bx lr
	.align 2, 0
_02222F30: .word 0x02243058

	arm_func_start MOD13_02222F34
MOD13_02222F34: ; 0x02222F34
	ldr r0, _02222F40 ; =0x0224304C
	ldrb r0, [r0]
	bx lr
	.align 2, 0
_02222F40: .word 0x0224304C

	arm_func_start MOD13_02222F44
MOD13_02222F44: ; 0x02222F44
	cmp r0, #0
	ldrne r2, _02222F68 ; =0x02243060
	ldrne r2, [r2, #8]
	strne r2, [r0]
	cmp r1, #0
	ldrne r0, _02222F68 ; =0x02243060
	ldrne r0, [r0, #0xc]
	strne r0, [r1]
	bx lr
	.align 2, 0
_02222F68: .word 0x02243060

	arm_func_start MOD13_02222F6C
MOD13_02222F6C: ; 0x02222F6C
	ldr r2, _02222F7C ; =0x02243060
	str r0, [r2, #8]
	str r1, [r2, #0xc]
	bx lr
	.align 2, 0
_02222F7C: .word 0x02243060

	arm_func_start MOD13_02222F80
MOD13_02222F80: ; 0x02222F80
	cmp r0, #0
	ldrne r2, _02222FA4 ; =0x02243060
	ldrne r2, [r2]
	strne r2, [r0]
	cmp r1, #0
	ldrne r0, _02222FA4 ; =0x02243060
	ldrne r0, [r0, #4]
	strne r0, [r1]
	bx lr
	.align 2, 0
_02222FA4: .word 0x02243060

	arm_func_start MOD13_02222FA8
MOD13_02222FA8: ; 0x02222FA8
	ldr r2, _02222FB8 ; =0x02243060
	str r0, [r2]
	str r1, [r2, #4]
	bx lr
	.align 2, 0
_02222FB8: .word 0x02243060

	arm_func_start MOD13_02222FBC
MOD13_02222FBC: ; 0x02222FBC
	ldr r1, _02222FC8 ; =0x0224305C
	str r0, [r1]
	bx lr
	.align 2, 0
_02222FC8: .word 0x0224305C

	arm_func_start MOD13_02222FCC
MOD13_02222FCC: ; 0x02222FCC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl GX_DispOff
	ldr r1, _02223020 ; =0x04001000
	ldr r0, [r1]
	bic r0, r0, #0x10000
	str r0, [r1]
	bl MOD13_0223BDD0
	bl MOD13_0223B6C0
	bl MOD13_0223B7A0
	bl MOD13_02234270
	bl MOD13_02239CE8
	bl MOD13_0223BA04
	bl MOD13_0223AA80
	bl MOD13_0223A3AC
	bl MOD13_022395A0
	bl MOD13_0223C2A8
	bl MOD13_0223B050
	bl MOD13_0223BEA8
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223020: .word 0x04001000

	arm_func_start MOD13_02223024
MOD13_02223024: ; 0x02223024
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r0, #0
	bl GX_VBlankIntr
	mov r0, #1
	bl GX_SetBankForBG
	mov r0, #2
	bl GX_SetBankForOBJ
	mov r1, #0
	mov r2, r1
	mov r0, #1
	bl GX_SetGraphicsMode
	mov r3, #0x4000000
	ldr r1, [r3]
	ldr r0, _022232DC ; =0x0400006C
	bic r1, r1, #0x1f00
	str r1, [r3]
	ldr r2, [r3]
	mov r1, #0
	bic r2, r2, #0xe000
	str r2, [r3]
	bl GXx_SetMasterBrightness_
	mov r3, #0x4000000
	ldr r2, [r3]
	ldr r0, _022232E0 ; =0xFFCFFFEF
	ldr r1, _022232E4 ; =0x00200010
	and r0, r2, r0
	orr r0, r0, r1
	str r0, [r3]
	ldr r3, _022232E8 ; =0x04000008
	ldr r2, _022232EC ; =0x0400000A
	ldrh r0, [r3]
	ldr r1, _022232F0 ; =0x0400000C
	ldr r5, _022232F4 ; =0x0400000E
	bic r0, r0, #0x40
	strh r0, [r3]
	ldrh r0, [r2]
	mov ip, #0
	ldr r4, _022232F8 ; =0x04000010
	bic r0, r0, #0x40
	strh r0, [r2]
	ldrh r0, [r1]
	ldr r3, _022232FC ; =0x04000014
	ldr r2, _02223300 ; =0x04000018
	bic r0, r0, #0x40
	strh r0, [r1]
	ldrh lr, [r5]
	ldr r1, _02223304 ; =0x0400001C
	ldr r0, _02223308 ; =0x04000050
	bic lr, lr, #0x40
	strh lr, [r5]
	str ip, [r4]
	str ip, [r3]
	str ip, [r2]
	str ip, [r1]
	mov r1, #0x3f
	mov r2, #0x10
	bl G2x_SetBlendBrightness_
	mov r0, #0x80
	bl GX_SetBankForSubBG
	mov r0, #0x100
	bl GX_SetBankForSubOBJ
	mov r0, #0
	bl GXS_SetGraphicsMode
	ldr r1, _0222330C ; =0x04001000
	ldr r0, [r1]
	bic r0, r0, #0x1f00
	str r0, [r1]
	ldr r0, [r1]
	bic r0, r0, #0xe000
	str r0, [r1]
	ldr r0, _02223310 ; =0x0400106C
	mov r1, #0
	bl GXx_SetMasterBrightness_
	ldr r3, _0222330C ; =0x04001000
	ldr r0, _022232E0 ; =0xFFCFFFEF
	ldr r1, [r3]
	ldr r2, _02223314 ; =0x04001008
	and r0, r1, r0
	orr r0, r0, #0x10
	str r0, [r3]
	ldrh r0, [r2]
	ldr r1, _02223318 ; =0x0400100A
	ldr r3, _0222331C ; =0x0400100C
	bic r0, r0, #0x40
	strh r0, [r2]
	ldrh r0, [r1]
	ldr r4, _02223320 ; =0x0400100E
	ldr r2, _02223324 ; =0x04001010
	bic r0, r0, #0x40
	strh r0, [r1]
	ldrh r0, [r3]
	mov ip, #0
	ldr r1, _02223328 ; =0x04001014
	bic r0, r0, #0x40
	strh r0, [r3]
	ldrh lr, [r4]
	ldr r0, _0222332C ; =0x04001018
	ldr r3, _02223330 ; =0x0400101C
	bic lr, lr, #0x40
	strh lr, [r4]
	str ip, [r2]
	str ip, [r1]
	str ip, [r0]
	ldr r0, _02223334 ; =0x04001050
	mov r1, #0x3f
	mov r2, #0x10
	str ip, [r3]
	bl G2x_SetBlendBrightness_
	ldr r3, _022232E8 ; =0x04000008
	ldr r2, _022232EC ; =0x0400000A
	ldrh r1, [r3]
	ldr r0, _02223338 ; =0x00000D08
	ldr lr, _022232F0 ; =0x0400000C
	and r1, r1, #0x43
	orr r1, r1, #0xc00
	strh r1, [r3]
	ldrh r1, [r2]
	mov ip, r5
	ldr r3, _02223314 ; =0x04001008
	and r1, r1, #0x43
	orr r0, r1, r0
	strh r0, [r2]
	ldrh r0, [lr]
	ldr r2, _02223318 ; =0x0400100A
	ldr r1, _0222331C ; =0x0400100C
	and r0, r0, #0x43
	orr r0, r0, #0xe10
	strh r0, [lr]
	ldrh r0, [ip]
	and r0, r0, #0x43
	orr r0, r0, #0xf10
	strh r0, [ip]
	ldrh r0, [r3]
	and r0, r0, #0x43
	orr r0, r0, #0xc00
	strh r0, [r3]
	ldrh r0, [r2]
	and r0, r0, #0x43
	orr r0, r0, #0xd00
	strh r0, [r2]
	ldrh r0, [r1]
	and r0, r0, #0x43
	orr r0, r0, #0xe00
	strh r0, [r1]
	mov r3, r4
	ldrh r0, [r3]
	mov r2, #0x4000000
	ldr r1, _0222333C ; =0x04000304
	and r0, r0, #0x43
	orr r0, r0, #0xf00
	strh r0, [r3]
	ldr r0, [r2]
	bic r0, r0, #0x38000000
	str r0, [r2]
	ldr r0, [r2]
	bic r0, r0, #0x7000000
	str r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #0x8000
	strh r0, [r1]
	bl MOD13_0223AAD0
	bl MOD13_0223BA84
	bl MOD13_0223BCE4
	bl MOD13_02239D38
	bl GX_DispOn
	ldr r2, _0222330C ; =0x04001000
	mov r0, #1
	ldr r1, [r2]
	orr r1, r1, #0x10000
	str r1, [r2]
	bl GX_VBlankIntr
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022232DC: .word 0x0400006C
_022232E0: .word 0xFFCFFFEF
_022232E4: .word 0x00200010
_022232E8: .word 0x04000008
_022232EC: .word 0x0400000A
_022232F0: .word 0x0400000C
_022232F4: .word 0x0400000E
_022232F8: .word 0x04000010
_022232FC: .word 0x04000014
_02223300: .word 0x04000018
_02223304: .word 0x0400001C
_02223308: .word 0x04000050
_0222330C: .word 0x04001000
_02223310: .word 0x0400106C
_02223314: .word 0x04001008
_02223318: .word 0x0400100A
_0222331C: .word 0x0400100C
_02223320: .word 0x0400100E
_02223324: .word 0x04001010
_02223328: .word 0x04001014
_0222332C: .word 0x04001018
_02223330: .word 0x0400101C
_02223334: .word 0x04001050
_02223338: .word 0x00000D08
_0222333C: .word 0x04000304

	arm_func_start MOD13_02223340
MOD13_02223340: ; 0x02223340
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _02223404 ; =0x04000208
	mov r0, #0
	ldrh r1, [r2]
	strh r0, [r2]
	bl GX_DispOff
	ldr r1, _02223408 ; =0x04001000
	ldr r0, [r1]
	bic r0, r0, #0x10000
	str r0, [r1]
	bl OS_IsTickAvailable
	cmp r0, #0
	bne _0222337C
	bl OS_Terminate
_0222337C:
	bl OS_IsAlarmAvailable
	cmp r0, #0
	bne _0222338C
	bl OS_Terminate
_0222338C:
	mov r0, #0
	bl GX_VBlankIntr
	bl FX_Init
	mvn r0, #0
	bl FS_Init
	bl TP_Init
	bl RTC_Init
	bl GX_DispOff
	ldr r1, _02223408 ; =0x04001000
	ldr r0, [r1]
	bic r0, r0, #0x10000
	str r0, [r1]
	bl MOD13_0223BFE4
	ldr r0, _0222340C ; =0x02243054
	ldr r0, [r0]
	bl MOD13_0223B07C
	bl MOD13_0223B7E8
	bl MOD13_0223C2F4
	bl MOD13_0223962C
	bl MOD13_0223B6F4
	bl MOD13_0223A3C0
	mov r0, #0x700
	mov r1, #0x20
	bl MOD13_0223B004
	str r0, [sp]
	bl FUN_02096190
	add r0, sp, #0
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223404: .word 0x04000208
_02223408: .word 0x04001000
_0222340C: .word 0x02243054

	arm_func_start MOD13_02223410
MOD13_02223410: ; 0x02223410
	ldr r3, _0222348C ; =0x0224304C
	ldr r2, _02223490 ; =0x02243058
	strb r0, [r3]
	str r1, [r2]
	cmp r0, #0
	blt _02223430
	cmp r0, #5
	ble _02223438
_02223430:
	mov r0, #0
	bx lr
_02223438:
	mov r2, r1, lsl #0x1c
	mov r2, r2, lsr #0x1c
	cmp r2, #1
	movhi r0, #0
	bxhi lr
	cmp r0, #0
	beq _02223464
	mov r1, r1, lsr #4
	ands r1, r1, #1
	movne r0, #0
	bxne lr
_02223464:
	cmp r0, #0
	bne _02223484
	ldr r0, _02223490 ; =0x02243058
	ldr r0, [r0]
	mov r0, r0, lsr #4
	ands r0, r0, #1
	moveq r0, #0
	bxeq lr
_02223484:
	mov r0, #1
	bx lr
	.align 2, 0
_0222348C: .word 0x0224304C
_02223490: .word 0x02243058

	arm_func_start MOD13_02223494
MOD13_02223494: ; 0x02223494
	stmdb sp!, {r4, r5, r6, lr}
	ldr r3, _0222351C ; =0x02243054
	str r0, [r3]
	mov r0, r1
	mov r1, r2
	bl MOD13_02223410
	cmp r0, #0
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, _02223520 ; =0x02243050
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02223340
	bl MOD13_02223024
	bl MOD13_022342A0
	ldr r0, _02223524 ; =MOD13_02223E10
	bl MOD13_02222FBC
	ldr r5, _02223528 ; =0x0224305C
	ldr r4, _02223520 ; =0x02243050
	mov r6, #0
_022234E4:
	bl MOD13_0223B6A8
	ldr r0, [r5]
	blx r0
	mov r0, r6
	bl MOD13_0223C1E0
	bl MOD13_0223B0BC
	bl MOD13_0223BDE0
	bl OS_WaitVBlankIntr
	ldrb r0, [r4]
	cmp r0, #0
	beq _022234E4
	bl MOD13_02222FCC
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222351C: .word 0x02243054
_02223520: .word 0x02243050
_02223524: .word MOD13_02223E10
_02223528: .word 0x0224305C

	arm_func_start MOD13_0222352C
MOD13_0222352C: ; 0x0222352C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr ip, _02223564 ; =0x0000FFFF
	ldr lr, [r0]
	and r1, r1, ip
	ldr ip, [r0, #4]
	ldr r0, [lr, r1, lsl #2]
	cmp r2, #0
	add r0, ip, r0
	addge r3, r3, #0x30
	movge r1, r2, lsl #1
	strgeh r3, [r0, r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223564: .word 0x0000FFFF

	arm_func_start MOD13_02223568
MOD13_02223568: ; 0x02223568
	ldr r2, _02223584 ; =0x0000FFFF
	ldr r3, [r0]
	and r1, r1, r2
	ldr r2, [r0, #4]
	ldr r0, [r3, r1, lsl #2]
	add r0, r2, r0
	bx lr
	.align 2, 0
_02223584: .word 0x0000FFFF

	arm_func_start MOD13_02223588
MOD13_02223588: ; 0x02223588
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #8]
	bl MOD13_0223939C
	ldr r0, _022235B0 ; =0x02243070
	mov r1, r4
	ldr r0, [r0]
	ldr r0, [r0, #0x60]
	bl MOD13_02239FD0
	ldmia sp!, {r4, pc}
	.align 2, 0
_022235B0: .word 0x02243070

	arm_func_start MOD13_022235B4
MOD13_022235B4: ; 0x022235B4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _02223614 ; =0x02243070
	mov r5, r0
	ldr r0, [r1]
	ldr r0, [r0, #0x60]
	bl MOD13_02239F78
	mov r4, r0
	add r1, sp, #0
	mov r0, r5
	mov r2, #4
	bl MOD13_022393D8
	str r0, [r4, #8]
	ldr r1, [r4, #8]
	mov r0, r4
	add r2, r1, #0x20
	add r1, r2, #0x10
	str r1, [r4]
	ldr r1, [r2, #4]
	add r1, r2, r1
	add r1, r1, #8
	str r1, [r4, #4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02223614: .word 0x02243070

	arm_func_start MOD13_02223618
MOD13_02223618: ; 0x02223618
	ldr ip, _02223624 ; =MOD13_0223AF90
	ldr r0, _02223628 ; =0x02243070
	bx ip
	.align 2, 0
_02223624: .word MOD13_0223AF90
_02223628: .word 0x02243070

	arm_func_start MOD13_0222362C
MOD13_0222362C: ; 0x0222362C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x64
	mov r1, #4
	bl MOD13_0223B004
	mov r1, r0
	ldr r3, _0222366C ; =0x02243070
	mov r0, #8
	mov r2, #0xc
	str r1, [r3]
	bl MOD13_0223A054
	ldr r1, _0222366C ; =0x02243070
	ldr r1, [r1]
	str r0, [r1, #0x60]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222366C: .word 0x02243070

	arm_func_start MOD13_02223670
MOD13_02223670: ; 0x02223670
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	bl MOD13_02238BE0
	ldr r0, _02223914 ; =0x02243074
	ldr r0, [r0]
	add r0, r0, #0x1e000
	ldrb r1, [r0, #0x2a0]
	cmp r1, #0
	beq _022236C4
	ldrb r1, [r0, #0x2a1]
	cmp r1, #0
	bne _022236C4
	ldr r1, [r0, #0x298]
	cmp r1, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #0
	blx r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022236C4:
	add r0, sp, #0
	add r1, sp, #1
	bl MOD13_02238B98
	ldrb r0, [sp]
	cmp r0, #0x1a
	bgt _0222375C
	cmp r0, #0x1a
	bge _02223870
	cmp r0, #0x14
	bgt _0222374C
	cmp r0, #0
	addge pc, pc, r0, lsl #2
	b _0222390C
_022236F8: ; jump table
	b _0222390C ; case 0
	b _0222390C ; case 1
	b _0222390C ; case 2
	b _0222390C ; case 3
	b _0222390C ; case 4
	b MOD13_02223784 ; case 5
	b _0222390C ; case 6
	b _0222390C ; case 7
	b _0222390C ; case 8
	b _0222390C ; case 9
	b _0222390C ; case 10
	b _0222390C ; case 11
	b MOD13_022238B4 ; case 12
	b MOD13_022237E8 ; case 13
	b _0222390C ; case 14
	b _0222390C ; case 15
	b _0222390C ; case 16
	b _0222390C ; case 17
	b _0222390C ; case 18
	b _0222390C ; case 19
	b _0222382C ; case 20
_0222374C:
	cmp r0, #0x17
	beq _0222382C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222375C:
	cmp r0, #0x1d
	bgt _02223774
	cmp r0, #0x1d
	beq _02223870
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02223774:
	cmp r0, #0x22
	beq _022238F8
	add sp, sp, #8
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_02223784
MOD13_02223784: ; 0x02223784
	ldrb r0, [sp, #1]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r1, _02223914 ; =0x02243074
	ldr r0, _02223918 ; =0x0001E280
	ldr r1, [r1]
	add r4, r1, r0
	bl MOD13_02238B88
	mov r1, r4
	mov r2, #0x16
	bl MIi_CpuCopy16
	ldr r0, _02223914 ; =0x02243074
	ldr r0, [r0]
	add r0, r0, #0x1e000
	ldr r1, [r0, #0x298]
	cmp r1, #0
	moveq r1, #1
	streqb r1, [r0, #0x2a0]
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #0
	blx r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_022237E8
MOD13_022237E8: ; 0x022237E8
	ldrb r0, [sp, #1]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r0, _02223914 ; =0x02243074
	ldr r0, [r0]
	add r0, r0, #0x1e000
	ldr r1, [r0, #0x298]
	cmp r1, #0
	moveq r1, #1
	streqb r1, [r0, #0x2a0]
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #1
	blx r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222382C:
	ldrb r0, [sp, #1]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r0, _02223914 ; =0x02243074
	ldr r0, [r0]
	add r0, r0, #0x1e000
	ldr r1, [r0, #0x298]
	cmp r1, #0
	moveq r1, #1
	streqb r1, [r0, #0x2a0]
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #3
	blx r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02223870:
	ldrb r0, [sp, #1]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r0, _02223914 ; =0x02243074
	ldr r0, [r0]
	add r0, r0, #0x1e000
	ldr r1, [r0, #0x298]
	cmp r1, #0
	moveq r1, #1
	streqb r1, [r0, #0x2a0]
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #4
	blx r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_022238B4
MOD13_022238B4: ; 0x022238B4
	ldrb r0, [sp, #1]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r0, _02223914 ; =0x02243074
	ldr r0, [r0]
	add r0, r0, #0x1e000
	ldr r1, [r0, #0x298]
	cmp r1, #0
	moveq r1, #1
	streqb r1, [r0, #0x2a0]
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #2
	blx r1
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022238F8:
	mov r1, r4
	mov r0, #0
	bl MOD13_0223C110
	ldr r0, _02223914 ; =0x02243074
	bl MOD13_0223AF90
_0222390C:
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02223914: .word 0x02243074
_02223918: .word 0x0001E280

	arm_func_start MOD13_0222391C
MOD13_0222391C: ; 0x0222391C
	ldr r1, _02223930 ; =0x02243074
	ldr r0, _02223934 ; =0x0001E280
	ldr r1, [r1]
	add r0, r1, r0
	bx lr
	.align 2, 0
_02223930: .word 0x02243074
_02223934: .word 0x0001E280

	arm_func_start MOD13_02223938
MOD13_02223938: ; 0x02223938
	ldr ip, _02223940 ; =MOD13_02238FFC
	bx ip
	.align 2, 0
_02223940: .word MOD13_02238FFC

	arm_func_start MOD13_02223944
MOD13_02223944: ; 0x02223944
	ldr r1, _02223958 ; =0x02243074
	ldr r1, [r1]
	add r1, r1, #0x1e000
	str r0, [r1, #0x298]
	bx lr
	.align 2, 0
_02223958: .word 0x02243074

	arm_func_start MOD13_0222395C
MOD13_0222395C: ; 0x0222395C
	ldr r0, _02223974 ; =0x02243074
	ldr r0, [r0]
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_02223974: .word 0x02243074

	arm_func_start MOD13_02223978
MOD13_02223978: ; 0x02223978
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_02239124
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, _022239B0 ; =0x02243074
	mov r1, r4
	ldr r0, [r0]
	mov r3, #1
	add r2, r0, #0x1e000
	mov r0, #0
	strb r3, [r2, #0x2a1]
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_022239B0: .word 0x02243074

	arm_func_start MOD13_022239B4
MOD13_022239B4: ; 0x022239B4
	ldr ip, _022239CC ; =MOD13_0223C1C4
	mov r0, #0
	ldr r1, _022239D0 ; =MOD13_02223978
	mov r2, r0
	mov r3, #0x78
	bx ip
	.align 2, 0
_022239CC: .word MOD13_0223C1C4
_022239D0: .word MOD13_02223978

	arm_func_start MOD13_022239D4
MOD13_022239D4: ; 0x022239D4
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x20
	mov r4, r0
	ldr r0, _02223AB0 ; =0x0001E2A4
	mov r1, #0x20
	bl MOD13_0223B004
	ldr r2, _02223AB4 ; =0x02243074
	add r1, r0, #0x1e000
	str r0, [r2]
	str r4, [r1, #0x298]
	ldr r0, [r2]
	mov r4, #0
	add r0, r0, #0x1e000
	strb r4, [r0, #0x2a0]
	ldr r0, [r2]
	ldr lr, _02223AB8 ; =0x0223FDA4
	add r0, r0, #0x1e000
	strb r4, [r0, #0x2a1]
	add ip, sp, #0
	ldmia lr!, {r0, r1, r2, r3}
	stmia ip!, {r0, r1, r2, r3}
	ldmia lr, {r0, r1, r2}
	stmia ip, {r0, r1, r2}
	ldr r0, _02223ABC ; =0x0224307C
	mov r1, r4
	ldr r0, [r0]
	bl MOD13_02223568
	ldr r1, _02223ABC ; =0x0224307C
	str r0, [sp, #4]
	ldr r0, [r1]
	mov r1, #1
	bl MOD13_02223568
	str r0, [sp, #8]
	bl MOD13_02222F34
	add r0, r0, #0x31
	strb r0, [sp, #0x18]
	ldr r0, _02223AB4 ; =0x02243074
	add r1, sp, #0
	ldr r0, [r0]
	bl MOD13_0223923C
	bl MOD13_0223903C
	cmp r0, #0
	bne _02223A84
	bl OS_Terminate
_02223A84:
	mov r0, #0
	ldr r1, _02223AC0 ; =MOD13_02223670
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02223AB4 ; =0x02243074
	ldr r1, [r1]
	add r1, r1, #0x1e000
	str r0, [r1, #0x29c]
	add sp, sp, #0x20
	ldmia sp!, {r4, pc}
	.align 2, 0
_02223AB0: .word 0x0001E2A4
_02223AB4: .word 0x02243074
_02223AB8: .word 0x0223FDA4
_02223ABC: .word 0x0224307C
_02223AC0: .word MOD13_02223670

	arm_func_start MOD13_02223AC4
MOD13_02223AC4: ; 0x02223AC4
	ldr ip, _02223ACC ; =MOD13_0223AF48
	bx ip
	.align 2, 0
_02223ACC: .word MOD13_0223AF48

	arm_func_start MOD13_02223AD0
MOD13_02223AD0: ; 0x02223AD0
	ldr ip, _02223ADC ; =MOD13_0223B004
	mov r1, #0x20
	bx ip
	.align 2, 0
_02223ADC: .word MOD13_0223B004

	arm_func_start MOD13_02223AE0
MOD13_02223AE0: ; 0x02223AE0
	ldr r3, _02223AF4 ; =0x02243078
	ldmia r0, {r0, r1, r2}
	ldr r3, [r3]
	stmia r3, {r0, r1, r2}
	bx lr
	.align 2, 0
_02223AF4: .word 0x02243078

	arm_func_start MOD13_02223AF8
MOD13_02223AF8: ; 0x02223AF8
	stmdb sp!, {lr}
	sub sp, sp, #0xec
	add r0, sp, #0
	blx MOD13_0221A794
	cmp r0, #1
	beq _02223B14
	bl OS_Terminate
_02223B14:
	add r0, sp, #0
	bl MOD13_02233A24
	add sp, sp, #0xec
	ldmia sp!, {pc}

	arm_func_start MOD13_02223B24
MOD13_02223B24: ; 0x02223B24
	stmdb sp!, {lr}
	sub sp, sp, #0xec
	ldr r1, _02223BDC ; =0x02243078
	ldr r1, [r1]
	ldr r1, [r1]
	cmp r1, #7
	addls pc, pc, r1, lsl #2
	b _02223BD4
_02223B44: ; jump table
	b _02223B64 ; case 0
	b _02223B64 ; case 1
	b _02223B70 ; case 2
	b _02223B64 ; case 3
	b _02223B7C ; case 4
	b _02223B64 ; case 5
	b _02223B88 ; case 6
	b _02223BD0 ; case 7
_02223B64:
	add sp, sp, #0xec
	mov r0, #0
	ldmia sp!, {pc}
_02223B70:
	add sp, sp, #0xec
	mov r0, #1
	ldmia sp!, {pc}
_02223B7C:
	add sp, sp, #0xec
	mov r0, #2
	ldmia sp!, {pc}
_02223B88:
	add r0, sp, #0
	blx MOD13_0221A794
	cmp r0, #1
	beq _02223B9C
	bl OS_Terminate
_02223B9C:
	ldr r0, [sp, #0x20]
	cmp r0, #0
	blt _02223BC4
	cmp r0, #3
	bgt _02223BC4
	ldr r0, [sp, #0x24]
	cmp r0, #1
	addeq sp, sp, #0xec
	moveq r0, #3
	ldmeqia sp!, {pc}
_02223BC4:
	add sp, sp, #0xec
	mov r0, #5
	ldmia sp!, {pc}
_02223BD0:
	mov r0, #4
_02223BD4:
	add sp, sp, #0xec
	ldmia sp!, {pc}
	.align 2, 0
_02223BDC: .word 0x02243078

	arm_func_start MOD13_02223BE0
MOD13_02223BE0: ; 0x02223BE0
	stmdb sp!, {lr}
	sub sp, sp, #4
	blx MOD13_0221A7EC
	cmp r0, #1
	beq _02223BF8
	bl OS_Terminate
_02223BF8:
	ldr r0, _02223C08 ; =0x02243078
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223C08: .word 0x02243078

	arm_func_start MOD13_02223C0C
MOD13_02223C0C: ; 0x02223C0C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r0, #0xc
	mvn r1, #3
	bl MOD13_0223AFE0
	ldr r1, _02223C68 ; =0x02243078
	ldr ip, _02223C6C ; =MOD13_02223AC4
	str r0, [r1]
	ldr r2, _02223C70 ; =MOD13_02223AE0
	ldr r3, _02223C74 ; =MOD13_02223AD0
	str ip, [sp]
	mov ip, #0x800
	mov r0, #0xf
	mov r1, #0x40
	str ip, [sp, #4]
	blx MOD13_0221A8A4
	cmp r0, #1
	beq _02223C58
	bl OS_Terminate
_02223C58:
	mov r0, #0xa
	bl OS_Sleep
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02223C68: .word 0x02243078
_02223C6C: .word MOD13_02223AC4
_02223C70: .word MOD13_02223AE0
_02223C74: .word MOD13_02223AD0

	arm_func_start MOD13_02223C78
MOD13_02223C78: ; 0x02223C78
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	mov r1, r0
	bl MOD13_0223C0A0
	mov r0, #1
	mov r1, #0
	bl MOD13_0223C0A0
	mov r0, #1
	bl MOD13_02239F20
	mov r0, #0
	bl MOD13_02239F20
	bl MOD13_0221F528
	bl MOD13_0221F404
	ldr r0, _02223CF8 ; =0x0224307C
	ldr r0, [r0]
	bl MOD13_02223588
	bl MOD13_02223618
	bl MOD13_02234178
	bl MOD13_02222EE8
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223CF8: .word 0x0224307C

	arm_func_start MOD13_02223CFC
MOD13_02223CFC: ; 0x02223CFC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	mov r1, #1
	mov r2, #0x3f
	mov r3, #0x14
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x3f
	mov r3, #0x14
	bl MOD13_0223A2A8
	ldr r0, _02223D3C ; =MOD13_02223C78
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223D3C: .word MOD13_02223C78

	arm_func_start MOD13_02223D40
MOD13_02223D40: ; 0x02223D40
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02222F1C
	cmp r0, #0
	beq _02223D8C
	cmp r0, #1
	beq _02223DA8
	add sp, sp, #4
	ldmia sp!, {pc}
_02223D8C:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02223DC4 ; =MOD13_022245B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02223DA8:
	mov r0, #1
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _02223DC8 ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223DC4: .word MOD13_022245B4
_02223DC8: .word MOD13_02230714

	arm_func_start MOD13_02223DCC
MOD13_02223DCC: ; 0x02223DCC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r2, r0
	mov r1, #1
	mov r3, #0x14
	bl MOD13_0223A2A8
	mov r0, #2
	mov r2, r0
	mov r1, #0
	mov r3, #0x14
	bl MOD13_0223A2A8
	ldr r0, _02223E0C ; =MOD13_02223D40
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223E0C: .word MOD13_02223D40

	arm_func_start MOD13_02223E10
MOD13_02223E10: ; 0x02223E10
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0223418C
	bl MOD13_0222362C
	bl MOD13_0221F424
	bl MOD13_0221F53C
	bl MOD13_0221EF74
	bl MOD13_02222F34
	cmp r0, #1
	bne _02223E5C
	mov r0, #2
	bl MOD13_02222EFC
	cmp r0, #0
	beq _02223E5C
	ldr r0, _02223F90 ; =0x0223FE38
	bl MOD13_022235B4
	ldr r1, _02223F94 ; =0x0224307C
	str r0, [r1]
	b _02223E74
_02223E5C:
	bl MOD13_02222F34
	ldr r1, _02223F98 ; =0x0223FE20
	ldr r0, [r1, r0, lsl #2]
	bl MOD13_022235B4
	ldr r1, _02223F94 ; =0x0224307C
	str r0, [r1]
_02223E74:
	ldr r0, _02223F9C ; =0x0223FE48
	bl MOD13_0221F1BC
	mov r1, r0
	mov r0, #1
	bl MOD13_02239F48
	ldr r0, _02223FA0 ; =0x0223FE5C
	bl MOD13_0221F1BC
	mov r1, r0
	mov r0, #0
	bl MOD13_02239F48
	ldr r0, _02223FA4 ; =0x0223FE70
	ldr r1, _02223FA8 ; =0x020C8DB4
	bl MOD13_0221F174
	ldr r0, _02223FAC ; =0x0223FE84
	ldr r1, _02223FB0 ; =0x020C94E8
	bl MOD13_0221F174
	ldr r0, _02223FB4 ; =0x0223FE98
	ldr r1, _02223FB8 ; =0x020C9294
	bl MOD13_0221F174
	ldr r0, _02223FBC ; =0x0223FEB0
	ldr r1, _02223FC0 ; =0x020C9418
	bl MOD13_0221F174
	ldr r0, _02223FC4 ; =0x0223FEC8
	ldr r1, _02223FC8 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _02223FCC ; =0x0223FEE0
	ldr r1, _02223FD0 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _02223FD4 ; =0x0223FEF8
	ldr r1, _02223FD8 ; =0x020C92F4
	bl MOD13_0221F174
	ldr r0, _02223FDC ; =0x0223FF10
	ldr r1, _02223FE0 ; =0x020C9480
	bl MOD13_0221F174
	bl MOD13_02222F1C
	cmp r0, #0
	beq _02223F14
	cmp r0, #1
	beq _02223F24
	b _02223F30
_02223F14:
	ldr r0, _02223FE4 ; =0x0223FF28
	ldr r1, _02223FE8 ; =0x020C90F4
	bl MOD13_0221F174
	b _02223F30
_02223F24:
	ldr r0, _02223FEC ; =0x0223FF3C
	ldr r1, _02223FE8 ; =0x020C90F4
	bl MOD13_0221F174
_02223F30:
	ldr ip, _02223FF0 ; =0x0400100A
	ldr r3, _02223FF4 ; =0x0400000A
	ldrh r2, [ip]
	mov r0, #1
	mov r1, #2
	bic r2, r2, #3
	orr r2, r2, #3
	strh r2, [ip]
	ldrh r2, [r3]
	bic r2, r2, #3
	orr r2, r2, #3
	strh r2, [r3]
	ldrh r2, [r3]
	bic r2, r2, #3
	orr r2, r2, #3
	strh r2, [r3]
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #2
	bl MOD13_0223AEF4
	ldr r0, _02223FF8 ; =MOD13_02223DCC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02223F90: .word 0x0223FE38
_02223F94: .word 0x0224307C
_02223F98: .word 0x0223FE20
_02223F9C: .word 0x0223FE48
_02223FA0: .word 0x0223FE5C
_02223FA4: .word 0x0223FE70
_02223FA8: .word 0x020C8DB4
_02223FAC: .word 0x0223FE84
_02223FB0: .word 0x020C94E8
_02223FB4: .word 0x0223FE98
_02223FB8: .word 0x020C9294
_02223FBC: .word 0x0223FEB0
_02223FC0: .word 0x020C9418
_02223FC4: .word 0x0223FEC8
_02223FC8: .word 0x020C8D4C
_02223FCC: .word 0x0223FEE0
_02223FD0: .word 0x020C9550
_02223FD4: .word 0x0223FEF8
_02223FD8: .word 0x020C92F4
_02223FDC: .word 0x0223FF10
_02223FE0: .word 0x020C9480
_02223FE4: .word 0x0223FF28
_02223FE8: .word 0x020C90F4
_02223FEC: .word 0x0223FF3C
_02223FF0: .word 0x0400100A
_02223FF4: .word 0x0400000A
_02223FF8: .word MOD13_02223DCC

	arm_func_start MOD13_02223FFC
MOD13_02223FFC: ; 0x02223FFC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02224040 ; =0x0223F100
	ldr r0, _02224044 ; =0x02243080
	ldrb r3, [r1]
	ldrb r2, [r1, #1]
	ldrb r1, [r0]
	add ip, sp, #0
	ldr r0, _02224048 ; =0x02243084
	strb r3, [sp]
	strb r2, [sp, #1]
	ldrb r1, [ip, r1]
	ldr r0, [r0]
	mov r2, r1
	bl MOD13_022327DC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224040: .word 0x0223F100
_02224044: .word 0x02243080
_02224048: .word 0x02243084

	arm_func_start MOD13_0222404C
MOD13_0222404C: ; 0x0222404C
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	cmp r0, #3
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r1, _022240BC ; =0x02243080
	mov r0, #8
	ldrb r2, [r1]
	eor r2, r2, #1
	strb r2, [r1]
	bl MOD13_0223424C
	ldr r0, _022240BC ; =0x02243080
	ldr ip, _022240C0 ; =0x0223F114
	ldrb r0, [r0]
	ldr r1, _022240C4 ; =0x0223F118
	ldr r2, _022240C8 ; =0x0223F116
	mov lr, r0, lsl #3
	ldr r3, _022240CC ; =0x0223F11A
	ldrh r0, [ip, lr]
	ldrh r1, [r1, lr]
	ldrh r2, [r2, lr]
	ldrh r3, [r3, lr]
	bl MOD13_0221F25C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022240BC: .word 0x02243080
_022240C0: .word 0x0223F114
_022240C4: .word 0x0223F118
_022240C8: .word 0x0223F116
_022240CC: .word 0x0223F11A

	arm_func_start MOD13_022240D0
MOD13_022240D0: ; 0x022240D0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221F21C
	bl MOD13_0221EE54
	ldr r0, _02224184 ; =0x02243084
	ldr r0, [r0]
	bl MOD13_0223939C
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AE98
	ldr r0, _02224188 ; =0x02243080
	ldrb r0, [r0]
	cmp r0, #0
	beq _0222414C
	cmp r0, #1
	beq _02224168
	add sp, sp, #4
	ldmia sp!, {pc}
_0222414C:
	mov r0, #1
	mov r1, #0
	bl MOD13_02222FA8
	ldr r0, _0222418C ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02224168:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _02224190 ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224184: .word 0x02243084
_02224188: .word 0x02243080
_0222418C: .word MOD13_02230714
_02224190: .word MOD13_022259A8

	arm_func_start MOD13_02224194
MOD13_02224194: ; 0x02224194
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _022241E8 ; =MOD13_022240D0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022241E8: .word MOD13_022240D0

	arm_func_start MOD13_022241EC
MOD13_022241EC: ; 0x022241EC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02224210 ; =MOD13_02224194
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224210: .word MOD13_02224194

	arm_func_start MOD13_02224214
MOD13_02224214: ; 0x02224214
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02224238
	cmp r0, #1
	beq _02224250
	add sp, sp, #4
	ldmia sp!, {pc}
_02224238:
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _0222426C ; =MOD13_02223CFC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02224250:
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02223FFC
	ldr r0, _02224270 ; =MOD13_022241EC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222426C: .word MOD13_02223CFC
_02224270: .word MOD13_022241EC

	arm_func_start MOD13_02224274
MOD13_02224274: ; 0x02224274
	bx lr

	arm_func_start MOD13_02224278
MOD13_02224278: ; 0x02224278
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r4, _022243B0 ; =0x0223F104
	mov r5, #0
_02224288:
	mov r0, r4
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _022242DC
	mov r0, #1
	bl MOD13_0221ECF4
	ldr r0, _022243B4 ; =0x02243080
	ldr ip, _022243B8 ; =0x0223F114
	strb r5, [r0]
	ldrb r0, [r0]
	ldr r1, _022243BC ; =0x0223F118
	ldr r2, _022243C0 ; =0x0223F116
	mov lr, r0, lsl #3
	ldr r3, _022243C4 ; =0x0223F11A
	ldrh r0, [ip, lr]
	ldrh r1, [r1, lr]
	ldrh r2, [r2, lr]
	ldrh r3, [r3, lr]
	bl MOD13_0221F25C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_022242DC:
	add r5, r5, #1
	cmp r5, #2
	add r4, r4, #8
	blo _02224288
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222430C
	mov r0, #1
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222430C:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222432C
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222432C:
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222434C
	mov r0, #1
	bl MOD13_0222404C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222434C:
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222436C
	mov r0, #3
	bl MOD13_0222404C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222436C:
	mov r0, #0x20
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222438C
	mov r0, #0
	bl MOD13_0222404C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222438C:
	mov r0, #0x10
	bl MOD13_0223B3B0
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	mov r0, #2
	bl MOD13_0222404C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022243B0: .word 0x0223F104
_022243B4: .word 0x02243080
_022243B8: .word 0x0223F114
_022243BC: .word 0x0223F118
_022243C0: .word 0x0223F116
_022243C4: .word 0x0223F11A

	arm_func_start MOD13_022243C8
MOD13_022243C8: ; 0x022243C8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02224278
	bl MOD13_02224274
	bl MOD13_02224214
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02224414 ; =MOD13_022243C8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224414: .word MOD13_022243C8

	arm_func_start MOD13_02224418
MOD13_02224418: ; 0x02224418
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0221F0EC
	ldr r0, _02224460 ; =0x022243E4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224460: .word 0x022243E4

	arm_func_start MOD13_02224464
MOD13_02224464: ; 0x02224464
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AEF4
	ldr r0, _022244BC ; =MOD13_02224418
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022244BC: .word MOD13_02224418

	arm_func_start MOD13_022244C0
MOD13_022244C0: ; 0x022244C0
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr ip, _02224584 ; =0x0223F124
	add r3, sp, #0
	mov r2, #0xb
_022244D4:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _022244D4
	ldr r0, _02224588 ; =0x0223FF50
	ldr r1, _0222458C ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _02224590 ; =0x0223FF68
	ldr r1, _02224594 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _02224598 ; =0x0223FF80
	ldr r1, _0222459C ; =0x020C908C
	bl MOD13_0221F174
	add r0, sp, #0
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _022245A0 ; =0x02243084
	ldr ip, _022245A4 ; =0x04001008
	str r0, [r1]
	ldrh r0, [ip]
	ldr r3, _022245A8 ; =0x0400100A
	ldr r2, _022245AC ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	ldr r1, _022245B0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.align 2, 0
_02224584: .word 0x0223F124
_02224588: .word 0x0223FF50
_0222458C: .word 0x020C8D4C
_02224590: .word 0x0223FF68
_02224594: .word 0x020C9550
_02224598: .word 0x0223FF80
_0222459C: .word 0x020C908C
_022245A0: .word 0x02243084
_022245A4: .word 0x04001008
_022245A8: .word 0x0400100A
_022245AC: .word 0x0400000A
_022245B0: .word 0x0400000C

	arm_func_start MOD13_022245B4
MOD13_022245B4: ; 0x022245B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022244C0
	mov r0, #0
	bl MOD13_0221F4CC
	mov r0, #0x2e
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #4
	bl MOD13_02234384
	ldr r0, _02224620 ; =0x02243080
	ldr r3, _02224624 ; =0x0223F114
	ldrb r0, [r0]
	ldr r1, _02224628 ; =0x0223F118
	ldr r2, _0222462C ; =0x0223F116
	mov ip, r0, lsl #3
	ldrh r0, [r3, ip]
	ldrh r1, [r1, ip]
	ldrh r2, [r2, ip]
	ldr r3, _02224630 ; =0x0223F11A
	ldrh r3, [r3, ip]
	bl MOD13_0221F25C
	ldr r0, _02224634 ; =MOD13_02224464
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224620: .word 0x02243080
_02224624: .word 0x0223F114
_02224628: .word 0x0223F118
_0222462C: .word 0x0223F116
_02224630: .word 0x0223F11A
_02224634: .word MOD13_02224464

	arm_func_start MOD13_02224638
MOD13_02224638: ; 0x02224638
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02224660 ; =MOD13_02224808
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224660: .word MOD13_02224808

	arm_func_start MOD13_02224664
MOD13_02224664: ; 0x02224664
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	beq _0222469C
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0xe
	bl MOD13_0223424C
	ldr r0, _022246B8 ; =0x02243088
	mov r1, #1
	strb r1, [r0]
	b _022246A4
_0222469C:
	mov r0, #7
	bl MOD13_0223424C
_022246A4:
	bl MOD13_02235EB0
	ldr r0, _022246BC ; =MOD13_02224638
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022246B8: .word 0x02243088
_022246BC: .word MOD13_02224638

	arm_func_start MOD13_022246C0
MOD13_022246C0: ; 0x022246C0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222478C ; =0x02243088
	ldrb r0, [r0]
	cmp r0, #0
	bne _02224700
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_02224700:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _0222478C ; =0x02243088
	ldrb r0, [r0]
	cmp r0, #0
	bne _02224738
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_02224738:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _0222478C ; =0x02243088
	ldrb r0, [r0]
	cmp r0, #0
	bne _02224770
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02224790 ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02224770:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02224794 ; =MOD13_02224D5C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222478C: .word 0x02243088
_02224790: .word MOD13_022259A8
_02224794: .word MOD13_02224D5C

	arm_func_start MOD13_02224798
MOD13_02224798: ; 0x02224798
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _02224800 ; =0x02243088
	ldrb r0, [r0]
	cmp r0, #0
	bne _022247DC
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_022247DC:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02224804 ; =MOD13_022246C0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224800: .word 0x02243088
_02224804: .word MOD13_022246C0

	arm_func_start MOD13_02224808
MOD13_02224808: ; 0x02224808
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222482C ; =MOD13_02224798
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222482C: .word MOD13_02224798

	arm_func_start MOD13_02224830
MOD13_02224830: ; 0x02224830
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02224854
	cmp r0, #1
	beq _0222486C
	add sp, sp, #4
	ldmia sp!, {pc}
_02224854:
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _022248A0 ; =MOD13_02224808
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222486C:
	mov r0, #6
	bl MOD13_0223424C
	mov r1, #0
	mov r0, #0x18
	mov r2, #1
	mvn r3, #0
	str r1, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _022248A4 ; =MOD13_02224664
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022248A0: .word MOD13_02224808
_022248A4: .word MOD13_02224664

	arm_func_start MOD13_022248A8
MOD13_022248A8: ; 0x022248A8
	bx lr

	arm_func_start MOD13_022248AC
MOD13_022248AC: ; 0x022248AC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _022248CC
	mov r0, #1
	bl MOD13_0221ECF4
_022248CC:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022248AC
	bl MOD13_022248A8
	bl MOD13_02224830
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222493C ; =0x022248F0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222493C: .word 0x022248F0

	arm_func_start MOD13_02224940
MOD13_02224940: ; 0x02224940
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	bl MOD13_0221F0EC
	ldr r0, _02224988 ; =0x0222490C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224988: .word 0x0222490C

	arm_func_start MOD13_0222498C
MOD13_0222498C: ; 0x0222498C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _022249E4 ; =MOD13_02224940
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022249E4: .word MOD13_02224940

	arm_func_start MOD13_022249E8
MOD13_022249E8: ; 0x022249E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02224A68 ; =0x0223FF94
	ldr r1, _02224A6C ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02224A70 ; =0x04001008
	ldr ip, _02224A74 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02224A78 ; =0x04000008
	ldr r2, _02224A7C ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02224A80 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224A68: .word 0x0223FF94
_02224A6C: .word 0x020C908C
_02224A70: .word 0x04001008
_02224A74: .word 0x0400100A
_02224A78: .word 0x04000008
_02224A7C: .word 0x0400000A
_02224A80: .word 0x0400000C

	arm_func_start MOD13_02224A84
MOD13_02224A84: ; 0x02224A84
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02224ACC ; =0x02243088
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022249E8
	mov r0, #0x12
	bl MOD13_0221F4CC
	mov r0, #0x3b
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #0x17
	bl MOD13_0221F070
	ldr r0, _02224AD0 ; =MOD13_0222498C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224ACC: .word 0x02243088
_02224AD0: .word MOD13_0222498C

	arm_func_start MOD13_02224AD4
MOD13_02224AD4: ; 0x02224AD4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0x1000000
	bl OS_SpinWait
	bl PM_ForceToPowerOff
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	mov r1, #1
	mov r2, #0x3f
	mov r3, #0x40
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x3f
	mov r3, #0x40
	bl MOD13_0223A2A8
	ldr r0, _02224B6C ; =MOD13_02224AD4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224B6C: .word MOD13_02224AD4

	arm_func_start MOD13_02224B70
MOD13_02224B70: ; 0x02224B70
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02224B94 ; =0x02224B18
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224B94: .word 0x02224B18

	arm_func_start MOD13_02224B98
MOD13_02224B98: ; 0x02224B98
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _02224BC8 ; =MOD13_02224B70
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224BC8: .word MOD13_02224B70

	arm_func_start MOD13_02224BCC
MOD13_02224BCC: ; 0x02224BCC
	bx lr

	arm_func_start MOD13_02224BD0
MOD13_02224BD0: ; 0x02224BD0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02224BD0
	bl MOD13_02224BCC
	bl MOD13_02224B98
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02224C48 ; =0x02224BFC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224C48: .word 0x02224BFC

	arm_func_start MOD13_02224C4C
MOD13_02224C4C: ; 0x02224C4C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #5
	bl MOD13_0221F0EC
	ldr r0, _02224C80 ; =0x02224C18
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224C80: .word 0x02224C18

	arm_func_start MOD13_02224C84
MOD13_02224C84: ; 0x02224C84
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02224CBC ; =MOD13_02224C4C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224CBC: .word MOD13_02224C4C

	arm_func_start MOD13_02224CC0
MOD13_02224CC0: ; 0x02224CC0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02224D40 ; =0x0223FFA8
	ldr r1, _02224D44 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02224D48 ; =0x04001008
	ldr ip, _02224D4C ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02224D50 ; =0x04000008
	ldr r2, _02224D54 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02224D58 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224D40: .word 0x0223FFA8
_02224D44: .word 0x020C908C
_02224D48: .word 0x04001008
_02224D4C: .word 0x0400100A
_02224D50: .word 0x04000008
_02224D54: .word 0x0400000A
_02224D58: .word 0x0400000C

	arm_func_start MOD13_02224D5C
MOD13_02224D5C: ; 0x02224D5C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02224CC0
	mov r0, #0x19
	bl MOD13_0221F070
	bl MOD13_02233808
	ldr r0, _02224D84 ; =MOD13_02224C84
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224D84: .word MOD13_02224C84

	arm_func_start MOD13_02224D88
MOD13_02224D88: ; 0x02224D88
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02224E08 ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224E08: .word MOD13_022259A8

	arm_func_start MOD13_02224E0C
MOD13_02224E0C: ; 0x02224E0C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02224E64 ; =MOD13_02224D88
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224E64: .word MOD13_02224D88

	arm_func_start MOD13_02224E68
MOD13_02224E68: ; 0x02224E68
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02224E8C ; =MOD13_02224E0C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224E8C: .word MOD13_02224E0C

	arm_func_start MOD13_02224E90
MOD13_02224E90: ; 0x02224E90
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _02224EC0 ; =MOD13_02224E68
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224EC0: .word MOD13_02224E68

	arm_func_start MOD13_02224EC4
MOD13_02224EC4: ; 0x02224EC4
	bx lr

	arm_func_start MOD13_02224EC8
MOD13_02224EC8: ; 0x02224EC8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02224EC8
	bl MOD13_02224EC4
	bl MOD13_02224E90
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02224F40 ; =0x02224EF4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224F40: .word 0x02224EF4

	arm_func_start MOD13_02224F44
MOD13_02224F44: ; 0x02224F44
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #2
	bl MOD13_0221F0EC
	ldr r0, _02224F8C ; =0x02224F10
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224F8C: .word 0x02224F10

	arm_func_start MOD13_02224F90
MOD13_02224F90: ; 0x02224F90
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02224FE8 ; =MOD13_02224F44
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02224FE8: .word MOD13_02224F44

	arm_func_start MOD13_02224FEC
MOD13_02224FEC: ; 0x02224FEC
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x6c
	mov r0, #0
	mov r1, r0
	bl MOD13_0223A7F0
	mov fp, r0
	add r0, sp, #0x14
	bl OS_GetMacAddress
	ldrb r1, [sp, #0x15]
	ldr r2, _022251B8 ; =0x0223FFBC
	add r0, sp, #0x40
	str r1, [sp]
	ldrb r3, [sp, #0x16]
	mov r1, #0x14
	str r3, [sp, #4]
	ldrb r3, [sp, #0x17]
	str r3, [sp, #8]
	ldrb r3, [sp, #0x18]
	str r3, [sp, #0xc]
	ldrb r3, [sp, #0x19]
	str r3, [sp, #0x10]
	ldrb r3, [sp, #0x14]
	bl swprintf
	ldr r3, _022251BC ; =0x0223F13C
	mov r2, #2
	ldrh r4, [r3, #6]
	mov r1, #0x480
	add r0, sp, #0x40
	str r4, [sp]
	str r2, [sp, #4]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldrh r1, [r3]
	ldrh r2, [r3, #2]
	ldrh r3, [r3, #4]
	mov r0, fp
	bl MOD13_0223A4F0
	add r0, sp, #0x1c
	bl FUN_02095EC8
	ldr sb, [sp, #0x1c]
	ldr sl, [sp, #0x20]
	mov r3, #0
	cmp sl, r3
	cmpeq sb, r3
	beq _02225160
	mov r0, sb
	mov r1, sl
	mov r2, #0xa
	bl _ull_mod
	mov r1, #0x3e8
	umull r4, r1, r0, r1
	mov r0, sb
	mov r1, sl
	mov r3, #0
	mov r2, #0xa
	str r4, [sp, #0x3c]
	bl _ll_udiv
	mov sb, r0
	mov sl, r1
	mov r8, #0
	ldr r7, _022251C0 ; =0x00002710
	add r5, sp, #0x30
	mov r6, r8
	mov r4, r8
_022250EC:
	mov r0, sb
	mov r1, sl
	mov r2, r7
	mov r3, r6
	bl _ull_mod
	rsb r1, r8, #2
	str r0, [r5, r1, lsl #2]
	mov r0, sb
	mov r1, sl
	mov r2, r7
	mov r3, r4
	bl _ll_udiv
	mov sb, r0
	mov sl, r1
	add r8, r8, #1
	cmp r8, #3
	blt _022250EC
	ldr r1, [sp, #0x34]
	ldr r2, _022251C4 ; =0x0223FFF8
	str r1, [sp]
	ldr r1, [sp, #0x38]
	add r0, sp, #0x40
	str r1, [sp, #4]
	ldr r3, [sp, #0x3c]
	mov r1, #0x14
	str r3, [sp, #8]
	ldr r3, [sp, #0x30]
	bl swprintf
	b _02225170
_02225160:
	ldr r2, _022251C8 ; =0x02240020
	add r0, sp, #0x40
	mov r1, #0x14
	bl swprintf
_02225170:
	ldr r0, _022251CC ; =0x0223F144
	mov r3, #2
	ldrh r4, [r0, #6]
	mov r2, #0x480
	add r1, sp, #0x40
	str r4, [sp]
	str r3, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	ldrh r1, [r0]
	ldrh r2, [r0, #2]
	ldrh r3, [r0, #4]
	mov r0, fp
	bl MOD13_0223A4F0
	mov r0, fp
	bl MOD13_0223A410
	add sp, sp, #0x6c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022251B8: .word 0x0223FFBC
_022251BC: .word 0x0223F13C
_022251C0: .word 0x00002710
_022251C4: .word 0x0223FFF8
_022251C8: .word 0x02240020
_022251CC: .word 0x0223F144

	arm_func_start MOD13_022251D0
MOD13_022251D0: ; 0x022251D0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02225250 ; =0x02240048
	ldr r1, _02225254 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02225258 ; =0x04001008
	ldr ip, _0222525C ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02225260 ; =0x04000008
	ldr r2, _02225264 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02225268 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225250: .word 0x02240048
_02225254: .word 0x020C908C
_02225258: .word 0x04001008
_0222525C: .word 0x0400100A
_02225260: .word 0x04000008
_02225264: .word 0x0400000A
_02225268: .word 0x0400000C

	arm_func_start MOD13_0222526C
MOD13_0222526C: ; 0x0222526C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022251D0
	mov r0, #0x11
	bl MOD13_0221F4CC
	mov r0, #0x3a
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	bl MOD13_02224FEC
	ldr r0, _022252A4 ; =MOD13_02224F90
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022252A4: .word MOD13_02224F90

	arm_func_start MOD13_022252A8
MOD13_022252A8: ; 0x022252A8
	ldr r1, _022252CC ; =0x0224308C
	ldr r0, _022252D0 ; =0x02243094
	ldrb r2, [r1]
	ldr r1, _022252D4 ; =0x0223F14C
	ldr ip, _022252D8 ; =MOD13_022327DC
	ldrb r1, [r1, r2]
	ldr r0, [r0]
	mov r2, r1
	bx ip
	.align 2, 0
_022252CC: .word 0x0224308C
_022252D0: .word 0x02243094
_022252D4: .word 0x0223F14C
_022252D8: .word MOD13_022327DC

	arm_func_start MOD13_022252DC
MOD13_022252DC: ; 0x022252DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #1
	bne _0222530C
	ldr r0, _02225368 ; =0x0224308C
	mov r1, #3
	ldrb r0, [r0]
	add r0, r0, #2
	bl FX_ModS32
	ldr r1, _02225368 ; =0x0224308C
	strb r0, [r1]
	b _02225328
_0222530C:
	ldr r0, _02225368 ; =0x0224308C
	mov r1, #3
	ldrb r0, [r0]
	add r0, r0, #1
	bl FX_ModS32
	ldr r1, _02225368 ; =0x0224308C
	strb r0, [r1]
_02225328:
	mov r0, #8
	bl MOD13_0223424C
	ldr r0, _02225368 ; =0x0224308C
	ldr ip, _0222536C ; =0x0223F19C
	ldrb r0, [r0]
	ldr r1, _02225370 ; =0x0223F1A0
	ldr r2, _02225374 ; =0x0223F19E
	mov lr, r0, lsl #3
	ldr r3, _02225378 ; =0x0223F1A2
	ldrh r0, [ip, lr]
	ldrh r1, [r1, lr]
	ldrh r2, [r2, lr]
	ldrh r3, [r3, lr]
	bl MOD13_0221F25C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225368: .word 0x0224308C
_0222536C: .word 0x0223F19C
_02225370: .word 0x0223F1A0
_02225374: .word 0x0223F19E
_02225378: .word 0x0223F1A2

	arm_func_start MOD13_0222537C
MOD13_0222537C: ; 0x0222537C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _0222549C ; =0x02243098
	ldr r0, [r0]
	bl MOD13_0223B974
	bl MOD13_0221F21C
	bl MOD13_0221EE54
	ldr r0, _022254A0 ; =0x02243094
	ldr r0, [r0]
	bl MOD13_0223939C
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AE98
	ldr r0, _022254A4 ; =0x02243090
	ldrb r0, [r0]
	cmp r0, #0
	bne _02225420
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _022254A8 ; =MOD13_022245B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02225420:
	ldr r0, _022254AC ; =0x0224308C
	ldrb r0, [r0]
	cmp r0, #0
	beq _02225448
	cmp r0, #1
	beq _02225464
	cmp r0, #2
	beq _02225480
	add sp, sp, #4
	ldmia sp!, {pc}
_02225448:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022254B0 ; =MOD13_0222526C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02225464:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022254B4 ; =MOD13_02224A84
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02225480:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022254B8 ; =MOD13_02226650
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222549C: .word 0x02243098
_022254A0: .word 0x02243094
_022254A4: .word 0x02243090
_022254A8: .word MOD13_022245B4
_022254AC: .word 0x0224308C
_022254B0: .word MOD13_0222526C
_022254B4: .word MOD13_02224A84
_022254B8: .word MOD13_02226650

	arm_func_start MOD13_022254BC
MOD13_022254BC: ; 0x022254BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02225524 ; =0x02243090
	ldrb r0, [r0]
	cmp r0, #0
	beq _022254EC
	bl MOD13_0221ED28
_022254EC:
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02225528 ; =MOD13_0222537C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225524: .word 0x02243090
_02225528: .word MOD13_0222537C

	arm_func_start MOD13_0222552C
MOD13_0222552C: ; 0x0222552C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02225550 ; =MOD13_022254BC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225550: .word MOD13_022254BC

	arm_func_start MOD13_02225554
MOD13_02225554: ; 0x02225554
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02225578
	cmp r0, #1
	beq _02225584
	add sp, sp, #0x14
	ldmia sp!, {pc}
_02225578:
	mov r0, #7
	bl MOD13_0223424C
	b _022255E4
_02225584:
	add r0, sp, #0
	bl FUN_02095EC8
	ldr r0, _022255F4 ; =0x0224308C
	ldrb r0, [r0]
	cmp r0, #0
	beq _022255CC
	ldr r2, [sp]
	ldr r1, [sp, #4]
	mov r0, #0
	cmp r1, r0
	cmpeq r2, r0
	bne _022255CC
	mov r0, #9
	bl MOD13_0223424C
	mvn r0, #0
	bl MOD13_0221ECE0
	add sp, sp, #0x14
	ldmia sp!, {pc}
_022255CC:
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_022252A8
	ldr r0, _022255F8 ; =0x02243090
	mov r1, #1
	strb r1, [r0]
_022255E4:
	ldr r0, _022255FC ; =MOD13_0222552C
	bl MOD13_02222FBC
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.align 2, 0
_022255F4: .word 0x0224308C
_022255F8: .word 0x02243090
_022255FC: .word MOD13_0222552C

	arm_func_start MOD13_02225600
MOD13_02225600: ; 0x02225600
	bx lr

	arm_func_start MOD13_02225604
MOD13_02225604: ; 0x02225604
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r4, _022256FC ; =0x0223F184
	mov r5, #0
_02225614:
	mov r0, r4
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02225668
	mov r0, #1
	bl MOD13_0221ECF4
	ldr r0, _02225700 ; =0x0224308C
	ldr ip, _02225704 ; =0x0223F19C
	strb r5, [r0]
	ldrb r0, [r0]
	ldr r1, _02225708 ; =0x0223F1A0
	ldr r2, _0222570C ; =0x0223F19E
	mov lr, r0, lsl #3
	ldr r3, _02225710 ; =0x0223F1A2
	ldrh r0, [ip, lr]
	ldrh r1, [r1, lr]
	ldrh r2, [r2, lr]
	ldrh r3, [r3, lr]
	bl MOD13_0221F25C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02225668:
	add r5, r5, #1
	cmp r5, #3
	add r4, r4, #8
	blo _02225614
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02225698
	mov r0, #1
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02225698:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _022256B8
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_022256B8:
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022256D8
	mov r0, #1
	bl MOD13_022252DC
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_022256D8:
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	mov r0, #3
	bl MOD13_022252DC
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022256FC: .word 0x0223F184
_02225700: .word 0x0224308C
_02225704: .word 0x0223F19C
_02225708: .word 0x0223F1A0
_0222570C: .word 0x0223F19E
_02225710: .word 0x0223F1A2

	arm_func_start MOD13_02225714
MOD13_02225714: ; 0x02225714
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02225604
	bl MOD13_02225600
	bl MOD13_02225554
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02225760 ; =MOD13_02225714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225760: .word MOD13_02225714

	arm_func_start MOD13_02225764
MOD13_02225764: ; 0x02225764
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0221F0EC
	ldr r0, _022257AC ; =0x02225730
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022257AC: .word 0x02225730

	arm_func_start MOD13_022257B0
MOD13_022257B0: ; 0x022257B0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AEF4
	ldr r0, _02225808 ; =MOD13_02225764
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225808: .word MOD13_02225764

	arm_func_start MOD13_0222580C
MOD13_0222580C: ; 0x0222580C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x48
	ldr r4, _0222597C ; =0x0223F154
	add r3, sp, #0
	mov r2, #0xb
_02225820:
	ldrb r1, [r4], #1
	ldrb r0, [r4], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _02225820
	ldr r4, _02225980 ; =0x0223F16C
	add r3, sp, #0x16
	mov r2, #0xb
_02225844:
	ldrb r1, [r4], #1
	ldrb r0, [r4], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _02225844
	ldrb r2, [r4]
	ldr r0, _02225984 ; =0x0224005C
	ldr r1, _02225988 ; =0x020C8D4C
	strb r2, [r3]
	bl MOD13_0221F174
	ldr r0, _0222598C ; =0x02240074
	ldr r1, _02225990 ; =0x020C908C
	bl MOD13_0221F174
	add r0, sp, #0x16
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _02225994 ; =0x02243094
	str r0, [r1]
	add r0, sp, #0
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	mov r5, r0
	add r0, sp, #0x30
	bl FUN_02095EC8
	ldr r1, [sp, #0x30]
	ldr r0, [sp, #0x34]
	mov r6, #0
	cmp r0, r6
	cmpeq r1, r6
	bne _02225900
	add r8, r5, #0xc0
	add r7, r5, #0x40
	mov r4, #0x20
_022258DC:
	mov r0, r8
	mov r1, r7
	mov r2, r4
	bl MI_CpuCopy8
	add r6, r6, #1
	cmp r6, #2
	add r8, r8, #0x20
	add r7, r7, #0x20
	blt _022258DC
_02225900:
	mov r0, r5
	mov r1, #0x200
	bl DC_FlushRange
	mov r0, r5
	mov r1, #0
	mov r2, #0x200
	bl GX_LoadBGPltt
	mov r0, r5
	bl MOD13_0223939C
	ldr ip, _02225998 ; =0x04001008
	ldr r3, _0222599C ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _022259A0 ; =0x0400000A
	ldr r1, _022259A4 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #0x48
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0222597C: .word 0x0223F154
_02225980: .word 0x0223F16C
_02225984: .word 0x0224005C
_02225988: .word 0x020C8D4C
_0222598C: .word 0x02240074
_02225990: .word 0x020C908C
_02225994: .word 0x02243094
_02225998: .word 0x04001008
_0222599C: .word 0x0400100A
_022259A0: .word 0x0400000A
_022259A4: .word 0x0400000C

	arm_func_start MOD13_022259A8
MOD13_022259A8: ; 0x022259A8
	stmdb sp!, {r4, lr}
	ldr r0, _02225A70 ; =0x02243090
	mov r1, #0
	strb r1, [r0]
	bl MOD13_0222580C
	mov r0, #0x10
	bl MOD13_0221F4CC
	mov r0, #3
	bl MOD13_02234384
	mov r0, #0x39
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #0
	mov r1, #0x5b
	bl MOD13_02239E54
	ldr r3, _02225A74 ; =0x02243098
	ldr r1, _02225A78 ; =0x0223F150
	str r0, [r3]
	ldrh ip, [r1]
	ldrh r2, [r1, #2]
	ldr r1, _02225A7C ; =0x000001FF
	ldr lr, [r0]
	and r4, ip, r1
	and ip, r2, #0xff
	ldr r1, _02225A80 ; =0xFE00FF00
	ldr r2, _02225A84 ; =0x0224308C
	and r1, lr, r1
	orr r1, r1, ip
	orr r1, r1, r4, lsl #16
	str r1, [r0]
	ldr lr, [r3]
	ldr r0, _02225A88 ; =0x0223F19C
	ldrh r3, [lr, #4]
	ldr r1, _02225A8C ; =0x0223F1A0
	ldr ip, _02225A90 ; =0x0223F19E
	bic r3, r3, #0xc00
	orr r3, r3, #0xc00
	strh r3, [lr, #4]
	ldrb r2, [r2]
	ldr r3, _02225A94 ; =0x0223F1A2
	mov lr, r2, lsl #3
	ldrh r0, [r0, lr]
	ldrh r1, [r1, lr]
	ldrh r2, [ip, lr]
	ldrh r3, [r3, lr]
	bl MOD13_0221F25C
	ldr r0, _02225A98 ; =MOD13_022257B0
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
	.align 2, 0
_02225A70: .word 0x02243090
_02225A74: .word 0x02243098
_02225A78: .word 0x0223F150
_02225A7C: .word 0x000001FF
_02225A80: .word 0xFE00FF00
_02225A84: .word 0x0224308C
_02225A88: .word 0x0223F19C
_02225A8C: .word 0x0223F1A0
_02225A90: .word 0x0223F19E
_02225A94: .word 0x0223F1A2
_02225A98: .word MOD13_022257B0

	arm_func_start MOD13_02225A9C
MOD13_02225A9C: ; 0x02225A9C
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #2
	bne _02225ACC
	bl MOD13_02233808
	ldr r0, _02225B24 ; =0x0224309C
	mov r1, #1
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #0x10
	bl MOD13_0223424C
	b _02225B08
_02225ACC:
	cmp r0, #3
	bne _02225AF0
	ldr r0, _02225B24 ; =0x0224309C
	mov r1, #2
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #0x12
	bl MOD13_0223424C
	b _02225B08
_02225AF0:
	ldr r0, _02225B24 ; =0x0224309C
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #0x12
	bl MOD13_0223424C
_02225B08:
	mov r0, #0
	bl MOD13_02223944
	bl MOD13_022239B4
	ldr r0, _02225B28 ; =MOD13_02225BD8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225B24: .word 0x0224309C
_02225B28: .word MOD13_02225BD8

	arm_func_start MOD13_02225B2C
MOD13_02225B2C: ; 0x02225B2C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0222395C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221F694
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02225BC8 ; =0x0224309C
	ldrb r0, [r0]
	cmp r0, #0
	bne _02225BA0
	ldr r0, _02225BCC ; =MOD13_02226CB0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02225BA0:
	cmp r0, #2
	bne _02225BB8
	ldr r0, _02225BD0 ; =MOD13_022268B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02225BB8:
	ldr r0, _02225BD4 ; =MOD13_02225FE4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225BC8: .word 0x0224309C
_02225BCC: .word MOD13_02226CB0
_02225BD0: .word MOD13_022268B4
_02225BD4: .word MOD13_02225FE4

	arm_func_start MOD13_02225BD8
MOD13_02225BD8: ; 0x02225BD8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02225C04 ; =MOD13_02225B2C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225C04: .word MOD13_02225B2C

	arm_func_start MOD13_02225C08
MOD13_02225C08: ; 0x02225C08
	bx lr

	arm_func_start MOD13_02225C0C
MOD13_02225C0C: ; 0x02225C0C
	bx lr

	arm_func_start MOD13_02225C10
MOD13_02225C10: ; 0x02225C10
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02225C0C
	bl MOD13_02225C08
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02225C5C ; =MOD13_02225A9C
	bl MOD13_02223944
	ldr r0, _02225C60 ; =MOD13_02225C10
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225C5C: .word MOD13_02225A9C
_02225C60: .word MOD13_02225C10

	arm_func_start MOD13_02225C64
MOD13_02225C64: ; 0x02225C64
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02225C9C ; =0x02225C28
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225C9C: .word 0x02225C28

	arm_func_start MOD13_02225CA0
MOD13_02225CA0: ; 0x02225CA0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02225D20 ; =0x0224008C
	ldr r1, _02225D24 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02225D28 ; =0x04001008
	ldr ip, _02225D2C ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02225D30 ; =0x04000008
	ldr r2, _02225D34 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02225D38 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225D20: .word 0x0224008C
_02225D24: .word 0x020C908C
_02225D28: .word 0x04001008
_02225D2C: .word 0x0400100A
_02225D30: .word 0x04000008
_02225D34: .word 0x0400000A
_02225D38: .word 0x0400000C

	arm_func_start MOD13_02225D3C
MOD13_02225D3C: ; 0x02225D3C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02225CA0
	mov r0, #0x1e
	bl MOD13_0221F070
	mov r0, #0
	bl MOD13_0221E694
	mov r0, #1
	bl MOD13_0221F6E0
	mov r0, #0xb
	bl MOD13_0223424C
	ldr r0, _02225D78 ; =MOD13_02225C64
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225D78: .word MOD13_02225C64

	arm_func_start MOD13_02225D7C
MOD13_02225D7C: ; 0x02225D7C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0x1000000
	bl OS_SpinWait
	bl PM_ForceToPowerOff
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	mov r1, #1
	mov r2, #0x3f
	mov r3, #0x40
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x3f
	mov r3, #0x40
	bl MOD13_0223A2A8
	ldr r0, _02225E14 ; =MOD13_02225D7C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225E14: .word MOD13_02225D7C

	arm_func_start MOD13_02225E18
MOD13_02225E18: ; 0x02225E18
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02225E3C ; =0x02225DC0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225E3C: .word 0x02225DC0

	arm_func_start MOD13_02225E40
MOD13_02225E40: ; 0x02225E40
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _02225E70 ; =MOD13_02225E18
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225E70: .word MOD13_02225E18

	arm_func_start MOD13_02225E74
MOD13_02225E74: ; 0x02225E74
	bx lr

	arm_func_start MOD13_02225E78
MOD13_02225E78: ; 0x02225E78
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02225E78
	bl MOD13_02225E74
	bl MOD13_02225E40
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02225EF0 ; =0x02225EA4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225EF0: .word 0x02225EA4

	arm_func_start MOD13_02225EF4
MOD13_02225EF4: ; 0x02225EF4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #5
	bl MOD13_0221F0EC
	ldr r0, _02225F28 ; =0x02225EC0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225F28: .word 0x02225EC0

	arm_func_start MOD13_02225F2C
MOD13_02225F2C: ; 0x02225F2C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02225F64 ; =MOD13_02225EF4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02225F64: .word MOD13_02225EF4

	arm_func_start MOD13_02225F68
MOD13_02225F68: ; 0x02225F68
	ldr r1, _02225FD0 ; =0x04001008
	ldr ip, _02225FD4 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02225FD8 ; =0x04000008
	ldr r2, _02225FDC ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02225FE0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	bx lr
	.align 2, 0
_02225FD0: .word 0x04001008
_02225FD4: .word 0x0400100A
_02225FD8: .word 0x04000008
_02225FDC: .word 0x0400000A
_02225FE0: .word 0x0400000C

	arm_func_start MOD13_02225FE4
MOD13_02225FE4: ; 0x02225FE4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02225F68
	mov r0, #0x1f
	bl MOD13_0221F070
	ldr r0, _02226008 ; =MOD13_02225F2C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226008: .word MOD13_02225F2C

	arm_func_start MOD13_0222600C
MOD13_0222600C: ; 0x0222600C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02226068 ; =MOD13_022275A4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226068: .word MOD13_022275A4

	arm_func_start MOD13_0222606C
MOD13_0222606C: ; 0x0222606C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _022260B0 ; =MOD13_0222600C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022260B0: .word MOD13_0222600C

	arm_func_start MOD13_022260B4
MOD13_022260B4: ; 0x022260B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _022260D8 ; =MOD13_0222606C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022260D8: .word MOD13_0222606C

	arm_func_start MOD13_022260DC
MOD13_022260DC: ; 0x022260DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _0222610C ; =MOD13_022260B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222610C: .word MOD13_022260B4

	arm_func_start MOD13_02226110
MOD13_02226110: ; 0x02226110
	bx lr

	arm_func_start MOD13_02226114
MOD13_02226114: ; 0x02226114
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02226114
	bl MOD13_02226110
	bl MOD13_022260DC
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222618C ; =0x02226140
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222618C: .word 0x02226140

	arm_func_start MOD13_02226190
MOD13_02226190: ; 0x02226190
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #4
	bl MOD13_0221F0EC
	ldr r0, _022261D8 ; =0x0222615C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022261D8: .word 0x0222615C

	arm_func_start MOD13_022261DC
MOD13_022261DC: ; 0x022261DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02226214 ; =MOD13_02226190
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226214: .word MOD13_02226190

	arm_func_start MOD13_02226218
MOD13_02226218: ; 0x02226218
	ldr r1, _02226280 ; =0x04001008
	ldr ip, _02226284 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02226288 ; =0x04000008
	ldr r2, _0222628C ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02226290 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	bx lr
	.align 2, 0
_02226280: .word 0x04001008
_02226284: .word 0x0400100A
_02226288: .word 0x04000008
_0222628C: .word 0x0400000A
_02226290: .word 0x0400000C

	arm_func_start MOD13_02226294
MOD13_02226294: ; 0x02226294
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02226218
	mov r0, #0x1a
	bl MOD13_0221F070
	ldr r0, _022262B8 ; =MOD13_022261DC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022262B8: .word MOD13_022261DC

	arm_func_start MOD13_022262BC
MOD13_022262BC: ; 0x022262BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02226388 ; =0x022430A0
	ldrb r0, [r0]
	cmp r0, #0
	bne _022262FC
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_022262FC:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _02226388 ; =0x022430A0
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226334
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_02226334:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _02226388 ; =0x022430A0
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222636C
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222638C ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222636C:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02226390 ; =MOD13_02226294
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226388: .word 0x022430A0
_0222638C: .word MOD13_022259A8
_02226390: .word MOD13_02226294

	arm_func_start MOD13_02226394
MOD13_02226394: ; 0x02226394
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _022263FC ; =0x022430A0
	ldrb r0, [r0]
	cmp r0, #0
	bne _022263D8
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_022263D8:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02226400 ; =MOD13_022262BC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022263FC: .word 0x022430A0
_02226400: .word MOD13_022262BC

	arm_func_start MOD13_02226404
MOD13_02226404: ; 0x02226404
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02226428 ; =MOD13_02226394
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226428: .word MOD13_02226394

	arm_func_start MOD13_0222642C
MOD13_0222642C: ; 0x0222642C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02226450
	cmp r0, #1
	beq _0222645C
	add sp, sp, #4
	ldmia sp!, {pc}
_02226450:
	mov r0, #7
	bl MOD13_0223424C
	b _02226470
_0222645C:
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _02226480 ; =0x022430A0
	mov r1, #1
	strb r1, [r0]
_02226470:
	ldr r0, _02226484 ; =MOD13_02226404
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226480: .word 0x022430A0
_02226484: .word MOD13_02226404

	arm_func_start MOD13_02226488
MOD13_02226488: ; 0x02226488
	bx lr

	arm_func_start MOD13_0222648C
MOD13_0222648C: ; 0x0222648C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _022264AC
	mov r0, #1
	bl MOD13_0221ECF4
_022264AC:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222648C
	bl MOD13_02226488
	bl MOD13_0222642C
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222651C ; =0x022264D0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222651C: .word 0x022264D0

	arm_func_start MOD13_02226520
MOD13_02226520: ; 0x02226520
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	bl MOD13_0221F0EC
	ldr r0, _02226554 ; =0x022264EC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226554: .word 0x022264EC

	arm_func_start MOD13_02226558
MOD13_02226558: ; 0x02226558
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _022265B0 ; =MOD13_02226520
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022265B0: .word MOD13_02226520

	arm_func_start MOD13_022265B4
MOD13_022265B4: ; 0x022265B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02226634 ; =0x022400A0
	ldr r1, _02226638 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222663C ; =0x04001008
	ldr ip, _02226640 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02226644 ; =0x04000008
	ldr r2, _02226648 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222664C ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226634: .word 0x022400A0
_02226638: .word 0x020C908C
_0222663C: .word 0x04001008
_02226640: .word 0x0400100A
_02226644: .word 0x04000008
_02226648: .word 0x0400000A
_0222664C: .word 0x0400000C

	arm_func_start MOD13_02226650
MOD13_02226650: ; 0x02226650
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02226698 ; =0x022430A0
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022265B4
	mov r0, #0x13
	bl MOD13_0221F4CC
	mov r0, #0x3c
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #0x1b
	bl MOD13_0221F070
	ldr r0, _0222669C ; =MOD13_02226558
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226698: .word 0x022430A0
_0222669C: .word MOD13_02226558

	arm_func_start MOD13_022266A0
MOD13_022266A0: ; 0x022266A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022266D8 ; =0x022430A4
	ldrb r1, [r0]
	add r1, r1, #1
	strb r1, [r0]
	ldrb r0, [r0]
	cmp r0, #0x78
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	ldr r0, _022266DC ; =MOD13_02226754
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022266D8: .word 0x022430A4
_022266DC: .word MOD13_02226754

	arm_func_start MOD13_022266E0
MOD13_022266E0: ; 0x022266E0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02226750 ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226750: .word MOD13_022259A8

	arm_func_start MOD13_02226754
MOD13_02226754: ; 0x02226754
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02226794 ; =MOD13_022266E0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226794: .word MOD13_022266E0

	arm_func_start MOD13_02226798
MOD13_02226798: ; 0x02226798
	bx lr

	arm_func_start MOD13_0222679C
MOD13_0222679C: ; 0x0222679C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022266A0
	bl MOD13_02226798
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0222395C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _022267F0 ; =MOD13_0222679C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022267F0: .word MOD13_0222679C

	arm_func_start MOD13_022267F4
MOD13_022267F4: ; 0x022267F4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222682C ; =0x022267B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222682C: .word 0x022267B4

	arm_func_start MOD13_02226830
MOD13_02226830: ; 0x02226830
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222689C ; =0x022400B4
	ldr r1, _022268A0 ; =0x020C908C
	bl MOD13_0221F174
	ldr ip, _022268A4 ; =0x04001008
	ldr r3, _022268A8 ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _022268AC ; =0x0400000A
	ldr r1, _022268B0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222689C: .word 0x022400B4
_022268A0: .word 0x020C908C
_022268A4: .word 0x04001008
_022268A8: .word 0x0400100A
_022268AC: .word 0x0400000A
_022268B0: .word 0x0400000C

	arm_func_start MOD13_022268B4
MOD13_022268B4: ; 0x022268B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022268E4 ; =0x022430A4
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02226830
	mov r0, #0x21
	bl MOD13_0221F070
	ldr r0, _022268E8 ; =MOD13_022267F4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022268E4: .word 0x022430A4
_022268E8: .word MOD13_022267F4

	arm_func_start MOD13_022268EC
MOD13_022268EC: ; 0x022268EC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _022269A8 ; =0x022430AC
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226954
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_02226954:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _022269A8 ; =0x022430AC
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222698C
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022269AC ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222698C:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022269B0 ; =MOD13_022275A4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022269A8: .word 0x022430AC
_022269AC: .word MOD13_022259A8
_022269B0: .word MOD13_022275A4

	arm_func_start MOD13_022269B4
MOD13_022269B4: ; 0x022269B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _02226A1C ; =0x022430AC
	ldrb r0, [r0]
	cmp r0, #0
	bne _022269F8
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_022269F8:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02226A20 ; =MOD13_022268EC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226A1C: .word 0x022430AC
_02226A20: .word MOD13_022268EC

	arm_func_start MOD13_02226A24
MOD13_02226A24: ; 0x02226A24
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02226A48 ; =MOD13_022269B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226A48: .word MOD13_022269B4

	arm_func_start MOD13_02226A4C
MOD13_02226A4C: ; 0x02226A4C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02226A84
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r1, _02226AA8 ; =0x022430AC
	mov r2, #1
	mov r0, #6
	strb r2, [r1]
	bl MOD13_0223424C
	b _02226A98
_02226A84:
	ldr r1, _02226AA8 ; =0x022430AC
	mov r2, #0
	mov r0, #7
	strb r2, [r1]
	bl MOD13_0223424C
_02226A98:
	ldr r0, _02226AAC ; =MOD13_02226A24
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226AA8: .word 0x022430AC
_02226AAC: .word MOD13_02226A24

	arm_func_start MOD13_02226AB0
MOD13_02226AB0: ; 0x02226AB0
	bx lr

	arm_func_start MOD13_02226AB4
MOD13_02226AB4: ; 0x02226AB4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02226AD4
	mov r0, #1
	bl MOD13_0221ECF4
_02226AD4:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02226AB4
	bl MOD13_02226AB0
	bl MOD13_02226A4C
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0222395C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02226B54 ; =0x02226AF8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226B54: .word 0x02226AF8

	arm_func_start MOD13_02226B58
MOD13_02226B58: ; 0x02226B58
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	bl MOD13_0221F0EC
	ldr r0, _02226BA0 ; =0x02226B14
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226BA0: .word 0x02226B14

	arm_func_start MOD13_02226BA4
MOD13_02226BA4: ; 0x02226BA4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02226C0C ; =0x022430A8
	ldrb r0, [r0]
	cmp r0, #0
	beq _02226BFC
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
_02226BFC:
	ldr r0, _02226C10 ; =MOD13_02226B58
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226C0C: .word 0x022430A8
_02226C10: .word MOD13_02226B58

	arm_func_start MOD13_02226C14
MOD13_02226C14: ; 0x02226C14
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02226C94 ; =0x022400C8
	ldr r1, _02226C98 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02226C9C ; =0x04001008
	ldr ip, _02226CA0 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02226CA4 ; =0x04000008
	ldr r2, _02226CA8 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02226CAC ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226C94: .word 0x022400C8
_02226C98: .word 0x020C908C
_02226C9C: .word 0x04001008
_02226CA0: .word 0x0400100A
_02226CA4: .word 0x04000008
_02226CA8: .word 0x0400000A
_02226CAC: .word 0x0400000C

	arm_func_start MOD13_02226CB0
MOD13_02226CB0: ; 0x02226CB0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02226C14
	mov r0, #0x20
	bl MOD13_0221F070
	mov r0, #0x3c
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	ldr r1, _02226CEC ; =0x022430A8
	strb r0, [r1]
	ldr r0, _02226CF0 ; =MOD13_02226BA4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226CEC: .word 0x022430A8
_02226CF0: .word MOD13_02226BA4

	arm_func_start MOD13_02226CF4
MOD13_02226CF4: ; 0x02226CF4
	ldr r0, _02226D04 ; =0x022430B0
	mov r1, #1
	strb r1, [r0]
	bx lr
	.align 2, 0
_02226D04: .word 0x022430B0

	arm_func_start MOD13_02226D08
MOD13_02226D08: ; 0x02226D08
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02226DDC ; =0x022430B0
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226D30
	ldr r0, _02226DE0 ; =0x022430B4
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226D40
_02226D30:
	bl MOD13_0222395C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
_02226D40:
	mov r0, #0
	bl MOD13_0223A65C
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _02226DE0 ; =0x022430B4
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226D74
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_02226D74:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02226DDC ; =0x022430B0
	ldrb r0, [r0]
	cmp r0, #0
	beq _02226DA0
	ldr r0, _02226DE4 ; =MOD13_02226CB0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02226DA0:
	ldr r0, _02226DE0 ; =0x022430B4
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226DCC
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	ldr r0, _02226DE8 ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02226DCC:
	ldr r0, _02226DEC ; =MOD13_02225D3C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226DDC: .word 0x022430B0
_02226DE0: .word 0x022430B4
_02226DE4: .word MOD13_02226CB0
_02226DE8: .word MOD13_022259A8
_02226DEC: .word MOD13_02225D3C

	arm_func_start MOD13_02226DF0
MOD13_02226DF0: ; 0x02226DF0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02226E5C ; =0x022430B0
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226E48
	ldr r0, _02226E60 ; =0x022430B4
	ldrb r0, [r0]
	cmp r0, #1
	bne _02226E48
	bl MOD13_02223938
	b _02226E4C
_02226E48:
	bl MOD13_022239B4
_02226E4C:
	ldr r0, _02226E64 ; =MOD13_02226D08
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226E5C: .word 0x022430B0
_02226E60: .word 0x022430B4
_02226E64: .word MOD13_02226D08

	arm_func_start MOD13_02226E68
MOD13_02226E68: ; 0x02226E68
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02226EC8 ; =0x022430B4
	ldrb r0, [r0]
	cmp r0, #0
	bne _02226EA4
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_02226EA4:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02226ECC ; =MOD13_02226DF0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226EC8: .word 0x022430B4
_02226ECC: .word MOD13_02226DF0

	arm_func_start MOD13_02226ED0
MOD13_02226ED0: ; 0x02226ED0
	bx lr

	arm_func_start MOD13_02226ED4
MOD13_02226ED4: ; 0x02226ED4
	bx lr

	arm_func_start MOD13_02226ED8
MOD13_02226ED8: ; 0x02226ED8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02226ED4
	bl MOD13_02226ED0
	bl MOD13_02235E9C
	cmp r0, #0
	beq _02226F04
	cmp r0, #1
	beq _02226F1C
	add sp, sp, #4
	ldmia sp!, {pc}
_02226F04:
	ldr r1, _02226F4C ; =0x022430B4
	mov r2, #0
	mov r0, #7
	strb r2, [r1]
	bl MOD13_0223424C
	b _02226F30
_02226F1C:
	ldr r1, _02226F4C ; =0x022430B4
	mov r2, #1
	mov r0, #0xe
	strb r2, [r1]
	bl MOD13_0223424C
_02226F30:
	mov r0, #0
	bl MOD13_02223944
	bl MOD13_02235EB0
	ldr r0, _02226F50 ; =MOD13_02226E68
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226F4C: .word 0x022430B4
_02226F50: .word MOD13_02226E68

	arm_func_start MOD13_02226F54
MOD13_02226F54: ; 0x02226F54
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _02226F80 ; =MOD13_02226ED8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226F80: .word MOD13_02226ED8

	arm_func_start MOD13_02226F84
MOD13_02226F84: ; 0x02226F84
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r2, #0
	mov r0, #0x1d
	mov r1, #4
	mvn r3, #0
	str r2, [sp]
	bl MOD13_02235EFC
	ldr r0, _02226FC8 ; =MOD13_02226F54
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02226FC8: .word MOD13_02226F54

	arm_func_start MOD13_02226FCC
MOD13_02226FCC: ; 0x02226FCC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02227004 ; =MOD13_02226F84
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227004: .word MOD13_02226F84

	arm_func_start MOD13_02227008
MOD13_02227008: ; 0x02227008
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227088 ; =0x022400DC
	ldr r1, _0222708C ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02227090 ; =0x04001008
	ldr ip, _02227094 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02227098 ; =0x04000008
	ldr r2, _0222709C ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _022270A0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227088: .word 0x022400DC
_0222708C: .word 0x020C908C
_02227090: .word 0x04001008
_02227094: .word 0x0400100A
_02227098: .word 0x04000008
_0222709C: .word 0x0400000A
_022270A0: .word 0x0400000C

	arm_func_start MOD13_022270A4
MOD13_022270A4: ; 0x022270A4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x2c
	bl MOD13_0222391C
	mov r5, r0
	mov r0, #0
	mov r1, r0
	bl MOD13_0223A7F0
	ldr r2, _02227160 ; =0x022430B4
	mov r3, #0
	ldr r1, _02227164 ; =0x022430B0
	mov r4, r0
	strb r3, [r2]
	strb r3, [r1]
	bl MOD13_02227008
	mov r0, #0
	add r1, sp, #0x10
	mov r2, #0x16
	bl MIi_CpuClear16
	ldrb r2, [r5, #1]
	add r0, r5, #2
	add r1, sp, #0x10
	mov r2, r2, lsl #1
	bl MIi_CpuCopy16
	ldr r0, _02227168 ; =0x0223F1B4
	mov lr, #2
	ldrh r2, [r0, #2]
	ldrh r5, [r0, #6]
	ldrh r1, [r0]
	mov ip, #0x480
	sub r5, r5, r2
	str r5, [sp]
	str lr, [sp, #4]
	add r3, sp, #0x10
	str ip, [sp, #8]
	str r3, [sp, #0xc]
	ldrh r3, [r0, #4]
	mov r0, r4
	sub r3, r3, r1
	bl MOD13_0223A4F0
	mov r0, r4
	bl MOD13_0223A410
	ldr r0, _0222716C ; =MOD13_02226CF4
	bl MOD13_02223944
	ldr r0, _02227170 ; =MOD13_02226FCC
	bl MOD13_02222FBC
	add sp, sp, #0x2c
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02227160: .word 0x022430B4
_02227164: .word 0x022430B0
_02227168: .word 0x0223F1B4
_0222716C: .word MOD13_02226CF4
_02227170: .word MOD13_02226FCC

	arm_func_start MOD13_02227174
MOD13_02227174: ; 0x02227174
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_022341E8
	cmp r4, #0
	bne _022271A0
	ldr r1, _022271C8 ; =0x022430B8
	mov r2, #1
	mov r0, #0x10
	strb r2, [r1]
	bl MOD13_0223424C
	b _022271B4
_022271A0:
	ldr r1, _022271C8 ; =0x022430B8
	mov r2, #2
	mov r0, #0x12
	strb r2, [r1]
	bl MOD13_0223424C
_022271B4:
	mov r0, #0
	bl MOD13_02223944
	ldr r0, _022271CC ; =MOD13_02227384
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
	.align 2, 0
_022271C8: .word 0x022430B8
_022271CC: .word MOD13_02227384

	arm_func_start MOD13_022271D0
MOD13_022271D0: ; 0x022271D0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022272E4 ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _02227210
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_02227210:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _022272E4 ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _02227240
	bl MOD13_0222395C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
_02227240:
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _022272E4 ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222726C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_0222726C:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _022272E4 ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _022272A4
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022272E8 ; =MOD13_022259A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022272A4:
	cmp r0, #2
	bne _022272C8
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022272EC ; =MOD13_02226CB0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022272C8:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022272F0 ; =MOD13_022270A4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022272E4: .word 0x022430B8
_022272E8: .word MOD13_022259A8
_022272EC: .word MOD13_02226CB0
_022272F0: .word MOD13_022270A4

	arm_func_start MOD13_022272F4
MOD13_022272F4: ; 0x022272F4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222737C ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _02227330
	bl MOD13_0222395C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
_02227330:
	bl MOD13_0221ED28
	ldr r0, _0222737C ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _02227358
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_02227358:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02227380 ; =MOD13_022271D0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222737C: .word 0x022430B8
_02227380: .word MOD13_022271D0

	arm_func_start MOD13_02227384
MOD13_02227384: ; 0x02227384
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022273BC ; =0x022430B8
	ldrb r0, [r0]
	cmp r0, #0
	bne _022273A0
	bl MOD13_022239B4
_022273A0:
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _022273C0 ; =MOD13_022272F4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022273BC: .word 0x022430B8
_022273C0: .word MOD13_022272F4

	arm_func_start MOD13_022273C4
MOD13_022273C4: ; 0x022273C4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _022273F8 ; =MOD13_02227384
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022273F8: .word MOD13_02227384

	arm_func_start MOD13_022273FC
MOD13_022273FC: ; 0x022273FC
	bx lr

	arm_func_start MOD13_02227400
MOD13_02227400: ; 0x02227400
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02227428
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
_02227428:
	bl MOD13_022275F8
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02227400
	bl MOD13_022273FC
	bl MOD13_022273C4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _02227490 ; =0x02227448
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227490: .word 0x02227448

	arm_func_start MOD13_02227494
MOD13_02227494: ; 0x02227494
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl MOD13_0221F0EC
	ldr r0, _022274C8 ; =0x02227464
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022274C8: .word 0x02227464

	arm_func_start MOD13_022274CC
MOD13_022274CC: ; 0x022274CC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02227504 ; =MOD13_02227494
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227504: .word MOD13_02227494

	arm_func_start MOD13_02227508
MOD13_02227508: ; 0x02227508
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227588 ; =0x022400F0
	ldr r1, _0222758C ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02227590 ; =0x04001008
	ldr ip, _02227594 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02227598 ; =0x04000008
	ldr r2, _0222759C ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _022275A0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227588: .word 0x022400F0
_0222758C: .word 0x020C908C
_02227590: .word 0x04001008
_02227594: .word 0x0400100A
_02227598: .word 0x04000008
_0222759C: .word 0x0400000A
_022275A0: .word 0x0400000C

	arm_func_start MOD13_022275A4
MOD13_022275A4: ; 0x022275A4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022275EC ; =MOD13_02227174
	bl MOD13_022239D4
	ldr r0, _022275F0 ; =0x022430B8
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02227508
	mov r0, #0x1c
	bl MOD13_0221F070
	mov r0, #0
	bl MOD13_0221E694
	mov r0, #0xb
	bl MOD13_0223424C
	ldr r0, _022275F4 ; =MOD13_022274CC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022275EC: .word MOD13_02227174
_022275F0: .word 0x022430B8
_022275F4: .word MOD13_022274CC

	arm_func_start MOD13_022275F8
MOD13_022275F8: ; 0x022275F8
	ldr r0, _02227614 ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_02227614: .word 0x027FFFA8

	arm_func_start MOD13_02227618
MOD13_02227618: ; 0x02227618
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r1, _02227648 ; =0x022430BC
	mov r2, #0
	ldr r0, _0222764C ; =MOD13_02227894
	strb r2, [r1]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227648: .word 0x022430BC
_0222764C: .word MOD13_02227894

	arm_func_start MOD13_02227650
MOD13_02227650: ; 0x02227650
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02227938
	bl MOD13_02227934
	bl MOD13_022278D8
	ldr r1, _0222769C ; =0x022430C0
	ldr r0, _022276A0 ; =0x00000438
	ldrh r2, [r1]
	add r2, r2, #1
	strh r2, [r1]
	ldrh r1, [r1]
	cmp r1, r0
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	bl MOD13_022341E8
	ldr r0, _022276A4 ; =MOD13_02227894
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222769C: .word 0x022430C0
_022276A0: .word 0x00000438
_022276A4: .word MOD13_02227894

	arm_func_start MOD13_022276A8
MOD13_022276A8: ; 0x022276A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022276D0 ; =MOD13_02227894
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022276D0: .word MOD13_02227894

	arm_func_start MOD13_022276D4
MOD13_022276D4: ; 0x022276D4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _02227708 ; =MOD13_022276A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227708: .word MOD13_022276A8

	arm_func_start MOD13_0222770C
MOD13_0222770C: ; 0x0222770C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0223B6A8
	mov r0, #0
	bl MOD13_0223C1E0
	bl MOD13_02227938
	bl MOD13_022278D8
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02227818 ; =0x022430BC
	ldrb r0, [r0]
	cmp r0, #0
	bne _02227770
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_02227770:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _02227818 ; =0x022430BC
	ldrb r0, [r0]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bl MOD13_02222D7C
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _02227818 ; =0x022430BC
	ldrb r0, [r0]
	cmp r0, #0
	bne _022277C4
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_022277C4:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _02227818 ; =0x022430BC
	ldrb r0, [r0]
	cmp r0, #0
	bne _022277FC
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222781C ; =MOD13_02230EC4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022277FC:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _02227820 ; =MOD13_02227ED0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227818: .word 0x022430BC
_0222781C: .word MOD13_02230EC4
_02227820: .word MOD13_02227ED0

	arm_func_start MOD13_02227824
MOD13_02227824: ; 0x02227824
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _0222788C ; =0x022430BC
	ldrb r0, [r0]
	cmp r0, #0
	bne _02227868
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_02227868:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02227890 ; =0x02227730
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222788C: .word 0x022430BC
_02227890: .word 0x02227730

	arm_func_start MOD13_02227894
MOD13_02227894: ; 0x02227894
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	ldr r0, _022278D0 ; =0x022430C4
	ldr r1, [r0]
	cmp r1, #0
	beq _022278B8
	mov r0, #1
	bl MOD13_0223C104
_022278B8:
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _022278D4 ; =MOD13_02227824
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022278D0: .word 0x022430C4
_022278D4: .word MOD13_02227824

	arm_func_start MOD13_022278D8
MOD13_022278D8: ; 0x022278D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222792C ; =0x022430C4
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #1
	bl MOD13_0223C110
	ldr r0, _0222792C ; =0x022430C4
	mov r1, #0
	str r1, [r0]
	bl MOD13_0221EC84
	ldr r0, _02227930 ; =MOD13_02227618
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222792C: .word 0x022430C4
_02227930: .word MOD13_02227618

	arm_func_start MOD13_02227934
MOD13_02227934: ; 0x02227934
	bx lr

	arm_func_start MOD13_02227938
MOD13_02227938: ; 0x02227938
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02227960
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
_02227960:
	bl MOD13_02227CA0
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02227938
	bl MOD13_02227934
	bl MOD13_022278D8
	bl MOD13_02222D0C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	cmp r0, #1
	beq _022279BC
	cmp r0, #2
	beq _022279FC
	add sp, sp, #4
	ldmia sp!, {pc}
_022279BC:
	ldr r0, _02227A68 ; =0x022430C4
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r2, _02227A6C ; =0x022430BC
	mov r0, #1
	strb r0, [r2]
	bl MOD13_0223C104
	ldr r1, _02227A68 ; =0x022430C4
	mov r2, #0
	ldr r0, _02227A70 ; =MOD13_02227650
	str r2, [r1]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022279FC:
	ldr r0, _02227A68 ; =0x022430C4
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_022341E8
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xc
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	mov r0, #9
	bl MOD13_0223424C
	bl MOD13_0221EC84
	ldr r1, _02227A68 ; =0x022430C4
	mov r0, #1
	ldr r1, [r1]
	bl MOD13_0223C104
	ldr r1, _02227A68 ; =0x022430C4
	mov r2, #0
	ldr r0, _02227A74 ; =MOD13_022276D4
	str r2, [r1]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227A68: .word 0x022430C4
_02227A6C: .word 0x022430BC
_02227A70: .word MOD13_02227650
_02227A74: .word MOD13_022276D4

	arm_func_start MOD13_02227A78
MOD13_02227A78: ; 0x02227A78
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r1, _02227AC0 ; =MOD13_0222770C
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02227AC4 ; =0x022430C4
	str r0, [r1]
	ldr r0, _02227AC8 ; =0x02227980
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227AC0: .word MOD13_0222770C
_02227AC4: .word 0x022430C4
_02227AC8: .word 0x02227980

	arm_func_start MOD13_02227ACC
MOD13_02227ACC: ; 0x02227ACC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl MOD13_0221F0EC
	ldr r0, _02227B14 ; =MOD13_02227A78
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227B14: .word MOD13_02227A78

	arm_func_start MOD13_02227B18
MOD13_02227B18: ; 0x02227B18
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02227B70 ; =MOD13_02227ACC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227B70: .word MOD13_02227ACC

	arm_func_start MOD13_02227B74
MOD13_02227B74: ; 0x02227B74
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227C0C ; =0x02240104
	ldr r1, _02227C10 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _02227C14 ; =0x0224011C
	ldr r1, _02227C18 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _02227C1C ; =0x02240134
	ldr r1, _02227C20 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02227C24 ; =0x04001008
	ldr ip, _02227C28 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02227C2C ; =0x04000008
	ldr r2, _02227C30 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02227C34 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227C0C: .word 0x02240104
_02227C10: .word 0x020C8D4C
_02227C14: .word 0x0224011C
_02227C18: .word 0x020C9550
_02227C1C: .word 0x02240134
_02227C20: .word 0x020C908C
_02227C24: .word 0x04001008
_02227C28: .word 0x0400100A
_02227C2C: .word 0x04000008
_02227C30: .word 0x0400000A
_02227C34: .word 0x0400000C

	arm_func_start MOD13_02227C38
MOD13_02227C38: ; 0x02227C38
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227C98 ; =0x022430C0
	mov r1, #0
	strh r1, [r0]
	bl MOD13_02227B74
	bl MOD13_0221F4AC
	mov r0, #0x36
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #2
	bl MOD13_0221F124
	mov r0, #0x22
	bl MOD13_0221F070
	mov r0, #0
	bl MOD13_0221E694
	bl MOD13_02222DD8
	mov r0, #0xb
	bl MOD13_0223424C
	ldr r0, _02227C9C ; =MOD13_02227B18
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227C98: .word 0x022430C0
_02227C9C: .word MOD13_02227B18

	arm_func_start MOD13_02227CA0
MOD13_02227CA0: ; 0x02227CA0
	ldr r0, _02227CBC ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_02227CBC: .word 0x027FFFA8

	arm_func_start MOD13_02227CC0
MOD13_02227CC0: ; 0x02227CC0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227CF8 ; =0x022430C8
	ldrb r1, [r0]
	add r1, r1, #1
	strb r1, [r0]
	ldrb r0, [r0]
	cmp r0, #0x78
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	ldr r0, _02227CFC ; =MOD13_02227D80
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227CF8: .word 0x022430C8
_02227CFC: .word MOD13_02227D80

	arm_func_start MOD13_02227D00
MOD13_02227D00: ; 0x02227D00
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, #1
	bl MOD13_02222F6C
	ldr r0, _02227D7C ; =MOD13_0223197C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227D7C: .word MOD13_0223197C

	arm_func_start MOD13_02227D80
MOD13_02227D80: ; 0x02227D80
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02227DC0 ; =MOD13_02227D00
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227DC0: .word MOD13_02227D00

	arm_func_start MOD13_02227DC4
MOD13_02227DC4: ; 0x02227DC4
	bx lr

	arm_func_start MOD13_02227DC8
MOD13_02227DC8: ; 0x02227DC8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02227CC0
	bl MOD13_02227DC4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02227E0C ; =MOD13_02227DC8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227E0C: .word MOD13_02227DC8

	arm_func_start MOD13_02227E10
MOD13_02227E10: ; 0x02227E10
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02227E48 ; =0x02227DE0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227E48: .word 0x02227DE0

	arm_func_start MOD13_02227E4C
MOD13_02227E4C: ; 0x02227E4C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227EB8 ; =0x02240148
	ldr r1, _02227EBC ; =0x020C908C
	bl MOD13_0221F174
	ldr ip, _02227EC0 ; =0x04001008
	ldr r3, _02227EC4 ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _02227EC8 ; =0x0400000A
	ldr r1, _02227ECC ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227EB8: .word 0x02240148
_02227EBC: .word 0x020C908C
_02227EC0: .word 0x04001008
_02227EC4: .word 0x0400100A
_02227EC8: .word 0x0400000A
_02227ECC: .word 0x0400000C

	arm_func_start MOD13_02227ED0
MOD13_02227ED0: ; 0x02227ED0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02227F0C ; =0x022430C8
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02227E4C
	bl MOD13_0221F4AC
	mov r0, #0x23
	bl MOD13_0221F070
	mov r0, #0x10
	bl MOD13_0223424C
	ldr r0, _02227F10 ; =MOD13_02227E10
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227F0C: .word 0x022430C8
_02227F10: .word MOD13_02227E10

	arm_func_start MOD13_02227F14
MOD13_02227F14: ; 0x02227F14
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221EC9C
	bl MOD13_02232F2C
	ldr r0, _02227F44 ; =MOD13_02229150
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227F44: .word MOD13_02229150

	arm_func_start MOD13_02227F48
MOD13_02227F48: ; 0x02227F48
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _02227F7C ; =MOD13_02227F14
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227F7C: .word MOD13_02227F14

	arm_func_start MOD13_02227F80
MOD13_02227F80: ; 0x02227F80
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02227FB4 ; =0x0223F1BC
	ldr r0, _02227FB8 ; =0x022430D4
	ldrb r1, [r1]
	ldr r0, [r0]
	strb r1, [sp]
	ldrb r1, [sp]
	ldr r0, [r0, #8]
	mov r2, r1
	bl MOD13_022327DC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02227FB4: .word 0x0223F1BC
_02227FB8: .word 0x022430D4

	arm_func_start MOD13_02227FBC
MOD13_02227FBC: ; 0x02227FBC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0222804C ; =0x022430D4
	ldr r0, _02228050 ; =0x022430D0
	ldr r2, [r1]
	ldrh r1, [r0]
	ldrh r0, [r2, #0x40]
	cmp r1, r0
	beq _02227FEC
	ldrb r0, [r2, #0x51]
	cmp r0, #4
	bhi _0222801C
_02227FEC:
	ldrb r0, [r2, #0x59]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222804C ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x59]
	ldmia sp!, {pc}
_0222801C:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _02228054 ; =MOD13_02228314
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222804C ; =0x022430D4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222804C: .word 0x022430D4
_02228050: .word 0x022430D0
_02228054: .word MOD13_02228314

	arm_func_start MOD13_02228058
MOD13_02228058: ; 0x02228058
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022280D8 ; =0x022430D0
	ldrh r0, [r0]
	cmp r0, #0
	bne _022280A8
	ldr r0, _022280DC ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x59]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _022280DC ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x59]
	ldmia sp!, {pc}
_022280A8:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _022280E0 ; =MOD13_022283B4
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _022280DC ; =0x022430D4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022280D8: .word 0x022430D0
_022280DC: .word 0x022430D4
_022280E0: .word MOD13_022283B4

	arm_func_start MOD13_022280E4
MOD13_022280E4: ; 0x022280E4
	stmdb sp!, {r4, lr}
	ldr r1, _02228238 ; =0x022430CC
	mov r4, #1
	ldrb r2, [r1]
	cmp r2, #4
	addls pc, pc, r2, lsl #2
	b _022281F0
_02228100: ; jump table
	b _02228114 ; case 0
	b _02228180 ; case 1
	b _02228180 ; case 2
	b _022281B0 ; case 3
	b _022281C8 ; case 4
_02228114:
	cmp r0, #1
	bne _02228160
	ldr r0, _0222823C ; =0x022430D0
	ldrh r0, [r0]
	cmp r0, #0
	moveq r0, #4
	streqb r0, [r1]
	beq _022281F0
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _02228240 ; =MOD13_022283B4
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02228244 ; =0x022430D4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {r4, pc}
_02228160:
	ldr r0, _02228244 ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x51]
	cmp r0, #1
	addhi r0, r2, #1
	strhib r0, [r1]
	movls r4, #0
	b _022281F0
_02228180:
	cmp r0, #1
	subeq r0, r2, #1
	streqb r0, [r1]
	beq _022281F0
	ldr r0, _02228244 ; =0x022430D4
	add r2, r2, #1
	ldr r0, [r0]
	ldrb r0, [r0, #0x51]
	cmp r0, r2
	strgtb r2, [r1]
	movle r4, #0
	b _022281F0
_022281B0:
	cmp r0, #1
	subeq r0, r2, #1
	streqb r0, [r1]
	beq _022281F0
	bl MOD13_02227FBC
	ldmia sp!, {r4, pc}
_022281C8:
	cmp r0, #1
	moveq r4, #0
	beq _022281F0
	ldr r0, _0222823C ; =0x022430D0
	mov r2, #0
	strh r2, [r0]
	strb r2, [r1]
	bl MOD13_02228754
	mov r0, #0
	bl MOD13_02232F44
_022281F0:
	cmp r4, #0
	bne _02228228
	ldr r0, _02228244 ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x59]
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _02228244 ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x59]
	ldmia sp!, {r4, pc}
_02228228:
	mov r0, #8
	bl MOD13_0223424C
	bl MOD13_02228248
	ldmia sp!, {r4, pc}
	.align 2, 0
_02228238: .word 0x022430CC
_0222823C: .word 0x022430D0
_02228240: .word MOD13_022283B4
_02228244: .word 0x022430D4

	arm_func_start MOD13_02228248
MOD13_02228248: ; 0x02228248
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222828C ; =0x022430CC
	ldr r1, _02228290 ; =0x0223F224
	ldrb r2, [r0]
	ldr r3, _02228294 ; =0x0223F226
	mov ip, r2, lsl #3
	cmp r2, #4
	ldr r2, _02228298 ; =0x0223F228
	movlo r0, #2
	ldrh r1, [r1, ip]
	ldrh r2, [r2, ip]
	ldrh r3, [r3, ip]
	movhs r0, #3
	bl MOD13_0221F348
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222828C: .word 0x022430CC
_02228290: .word 0x0223F224
_02228294: .word 0x0223F226
_02228298: .word 0x0223F228

	arm_func_start MOD13_0222829C
MOD13_0222829C: ; 0x0222829C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02228300 ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x56]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _02228304 ; =0x022430D0
	mov r1, #0x1c
	ldrh r0, [r0]
	bl FX_ModS32
	ldr r1, _02228308 ; =0x01FF0000
	sub r2, r0, #0x32
	ldr r0, _0222830C ; =0x04000010
	and r2, r1, r2, lsl #16
	ldr r1, _02228310 ; =0x04000018
	str r2, [r0]
	ldr r0, _02228300 ; =0x022430D4
	str r2, [r1]
	ldr r0, [r0]
	mov r1, #0
	strb r1, [r0, #0x56]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02228300: .word 0x022430D4
_02228304: .word 0x022430D0
_02228308: .word 0x01FF0000
_0222830C: .word 0x04000010
_02228310: .word 0x04000018

	arm_func_start MOD13_02228314
MOD13_02228314: ; 0x02228314
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_02232F14
	bl MOD13_0221F21C
	ldr r0, _022283AC ; =0x022430D0
	mov r1, #0x1c
	ldrh r2, [r0]
	add r2, r2, #4
	strh r2, [r0]
	ldrh r0, [r0]
	bl FX_ModS32
	cmp r0, #4
	blt _02228350
	bl MOD13_02228490
	ldmia sp!, {r4, pc}
_02228350:
	ldr r1, _022283AC ; =0x022430D0
	ldrh r2, [r1]
	sub r0, r2, r0
	strh r0, [r1]
	bl MOD13_02228754
	ldr r1, _022283B0 ; =0x022430D4
	ldr r0, _022283AC ; =0x022430D0
	ldr r1, [r1]
	ldrh r2, [r0]
	ldrb r0, [r1, #0x53]
	ldrh r1, [r1, #0x40]
	mul r0, r2, r0
	bl FX_DivS32
	bl MOD13_02232F44
	bl MOD13_02232F2C
	bl MOD13_02228248
	ldr r0, _022283B0 ; =0x022430D4
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0
	str r0, [r2, #0x38]
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_022283AC: .word 0x022430D0
_022283B0: .word 0x022430D4

	arm_func_start MOD13_022283B4
MOD13_022283B4: ; 0x022283B4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r0
	bl MOD13_02232F14
	bl MOD13_0221F21C
	ldr r0, _02228488 ; =0x022430D0
	ldrh r1, [r0]
	cmp r1, #4
	subhi r1, r1, #4
	strhih r1, [r0]
	movls r1, #0
	strlsh r1, [r0]
	ldr r0, _02228488 ; =0x022430D0
	mov r1, #0x1c
	ldrh r0, [r0]
	bl FX_ModS32
	mov r5, r0
	cmp r5, #0x18
	bne _0222840C
	bl MOD13_02228754
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222840C:
	cmp r5, #0x18
	ble _0222842C
	ldr r0, _02228488 ; =0x022430D0
	rsb r1, r5, #0x1c
	ldrh r2, [r0]
	mov r5, #0
	add r1, r2, r1
	strh r1, [r0]
_0222842C:
	bl MOD13_02228490
	cmp r5, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r1, _0222848C ; =0x022430D4
	ldr r0, _02228488 ; =0x022430D0
	ldr r1, [r1]
	ldrh r2, [r0]
	ldrb r0, [r1, #0x53]
	ldrh r1, [r1, #0x40]
	mul r0, r2, r0
	bl FX_DivS32
	bl MOD13_02232F44
	bl MOD13_02232F2C
	bl MOD13_02228248
	ldr r0, _0222848C ; =0x022430D4
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0
	str r0, [r2, #0x38]
	bl MOD13_0223C110
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02228488: .word 0x022430D0
_0222848C: .word 0x022430D4

	arm_func_start MOD13_02228490
MOD13_02228490: ; 0x02228490
	stmdb sp!, {r4, r5, r6, lr}
	ldr r0, _02228544 ; =0x022430D0
	mov r1, #0x1c
	ldrh r0, [r0]
	bl FX_ModS32
	ldr r1, _02228548 ; =0x022430D4
	rsb r2, r0, #0x36
	ldr r0, [r1]
	ldrb r1, [r0, #0x51]
	mov r0, #0
	cmp r1, #5
	movgt r1, #5
	cmp r1, #0
	ble _02228530
	ldr ip, _02228548 ; =0x022430D4
	ldr r3, _0222854C ; =0xFE00FF00
_022284D0:
	ldr r5, [ip]
	sub r4, r2, #2
	add r5, r5, r0, lsl #2
	ldr r6, [r5, #0x10]
	add lr, r2, #1
	ldr r5, [r6]
	and r4, r4, #0xff
	and r5, r5, r3
	orr r4, r5, r4
	orr r4, r4, #0xb30000
	str r4, [r6]
	ldr r4, [ip]
	and lr, lr, #0xff
	add r4, r4, r0, lsl #2
	ldr r5, [r4, #0x24]
	add r0, r0, #1
	ldr r4, [r5]
	cmp r0, r1
	and r4, r4, r3
	orr r4, r4, lr
	orr r4, r4, #0xd20000
	str r4, [r5]
	add r2, r2, #0x1c
	blt _022284D0
_02228530:
	ldr r0, _02228548 ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x56]
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02228544: .word 0x022430D0
_02228548: .word 0x022430D4
_0222854C: .word 0xFE00FF00

	arm_func_start MOD13_02228550
MOD13_02228550: ; 0x02228550
	stmdb sp!, {r4, lr}
	ldr r3, _022285D8 ; =0x022430D4
	ldr lr, [r3]
	ldrb r2, [lr, #0x51]
	cmp r0, r2
	ldmgeia sp!, {r4, pc}
	mov r2, #0x2a
	mul r2, r0, r2
	ldr r0, [lr]
	add r4, lr, r1, lsl #2
	add r0, r0, r2
	ldrb ip, [r0, #0x28]
	ldr r4, [r4, #0x10]
	mov r0, #0x400
	add ip, lr, ip, lsl #1
	ldrh lr, [r4, #4]
	rsb r0, r0, #0
	ldrh ip, [ip, #0x42]
	and lr, lr, r0
	orr ip, lr, ip
	strh ip, [r4, #4]
	ldr lr, [r3]
	ldr r3, [lr]
	add ip, lr, r1, lsl #2
	add r1, r3, r2
	ldrh r1, [r1, #0x26]
	ldr r3, [ip, #0x24]
	add r1, lr, r1, lsl #1
	ldrh r2, [r3, #4]
	ldrh r1, [r1, #0x48]
	and r0, r2, r0
	orr r0, r0, r1
	strh r0, [r3, #4]
	ldmia sp!, {r4, pc}
	.align 2, 0
_022285D8: .word 0x022430D4

	arm_func_start MOD13_022285DC
MOD13_022285DC: ; 0x022285DC
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x34
	mov r7, r0
	mov r0, #0x2a
	ldr r2, _02228750 ; =0x022430D4
	mul r4, r7, r0
	ldr r0, [r2]
	mov r6, r1
	ldr r0, [r0]
	mov r1, #0x20
	add r0, r0, r4
	bl MOD13_0223BDA4
	ldr r2, _02228750 ; =0x022430D4
	mov r1, #0x1c
	mul r5, r6, r1
	ldr r2, [r2]
	mov r6, r0
	ldrb r1, [r2, #0x51]
	cmp r7, r1
	addge sp, sp, #0x34
	ldmgeia sp!, {r4, r5, r6, r7, pc}
	add r0, sp, #0xc
	cmp r6, #0x10
	mov r1, #0
	mov r2, #0x22
	addle r5, r5, #6
	bl MI_CpuFill8
	cmp r6, #0x10
	movle ip, r6
	movgt ip, #0x10
	cmp ip, #0
	mov r7, #0
	ble _0222868C
	ldr r0, _02228750 ; =0x022430D4
	ldr r3, [r0]
	add r0, sp, #0xc
_0222866C:
	ldr r2, [r3]
	mov r1, r7, lsl #1
	add r2, r4, r2
	ldrb r2, [r7, r2]
	add r7, r7, #1
	cmp r7, ip
	strh r2, [r0, r1]
	blt _0222866C
_0222868C:
	mov r1, #0xa
	add r0, sp, #0xc
	str r1, [sp]
	str r0, [sp, #4]
	mov r2, #1
	str r2, [sp, #8]
	ldr r0, _02228750 ; =0x022430D4
	mov r2, r5
	ldr r0, [r0]
	mov r3, #2
	ldr r0, [r0, #0xc]
	bl MOD13_0223A528
	cmp r6, #0x10
	addle sp, sp, #0x34
	ldmleia sp!, {r4, r5, r6, r7, pc}
	add r0, sp, #0xc
	mov r1, #0
	mov r2, #0x22
	bl MI_CpuFill8
	sub r6, r6, #0x10
	cmp r6, #0
	mov r3, #0
	ble _02228718
	ldr r0, _02228750 ; =0x022430D4
	ldr r7, [r0]
	add r0, sp, #0xc
_022286F4:
	ldr r1, [r7]
	add r2, r3, #0x10
	add r1, r4, r1
	ldrb r2, [r2, r1]
	mov r1, r3, lsl #1
	add r3, r3, #1
	strh r2, [r0, r1]
	cmp r3, r6
	blt _022286F4
_02228718:
	mov r1, #0xa
	add r0, sp, #0xc
	str r1, [sp]
	str r0, [sp, #4]
	mov r2, #1
	str r2, [sp, #8]
	ldr r0, _02228750 ; =0x022430D4
	add r2, r5, #0xc
	ldr r0, [r0]
	mov r3, #2
	ldr r0, [r0, #0xc]
	bl MOD13_0223A528
	add sp, sp, #0x34
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02228750: .word 0x022430D4

	arm_func_start MOD13_02228754
MOD13_02228754: ; 0x02228754
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r0, _02228800 ; =0x022430D0
	mov r1, #0x1c
	ldrh r0, [r0]
	bl FX_DivS32
	ldr r1, _02228804 ; =0x022430D4
	mov r7, r0
	ldr r0, [r1]
	mov r1, #0
	ldrb r6, [r0, #0x51]
	ldr r0, [r0, #0xc]
	bl MOD13_0223A4D8
	cmp r6, #5
	movgt r6, #5
	mov r5, r7
	cmp r6, #0
	mov r4, #0
	ble _022287BC
_022287A0:
	mov r0, r5
	mov r1, r4
	bl MOD13_022285DC
	add r4, r4, #1
	cmp r4, r6
	add r5, r5, #1
	blt _022287A0
_022287BC:
	cmp r6, #0
	mov r4, #0
	ble _022287E4
_022287C8:
	mov r0, r7
	mov r1, r4
	bl MOD13_02228550
	add r4, r4, #1
	cmp r4, r6
	add r7, r7, #1
	blt _022287C8
_022287E4:
	ldr r0, _02228804 ; =0x022430D4
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl MOD13_0223A410
	bl MOD13_02228490
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02228800: .word 0x022430D0
_02228804: .word 0x022430D4

	arm_func_start MOD13_02228808
MOD13_02228808: ; 0x02228808
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _02228A0C ; =0x022430D4
	mov r0, #1
	ldr r1, [r1]
	ldr r1, [r1, #0x3c]
	bl MOD13_0223C104
	mov r5, #0
	ldr r4, _02228A0C ; =0x022430D4
_02228864:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _0222887C
	bl MOD13_0223B974
_0222887C:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x24]
	cmp r0, #0
	beq _02228894
	bl MOD13_0223B974
_02228894:
	add r5, r5, #1
	cmp r5, #5
	blt _02228864
	ldr r0, _02228A0C ; =0x022430D4
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl MOD13_0223A688
	bl MOD13_02232F78
	bl MOD13_0221F21C
	bl MOD13_0221EE54
	bl MOD13_022328E8
	ldr r0, _02228A0C ; =0x022430D4
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD13_0223939C
	ldr r0, _02228A0C ; =0x022430D4
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl MOD13_0223939C
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x1d
	bl MOD13_0223AE98
	mov r2, #0
	ldr r1, _02228A10 ; =0x04000010
	ldr r0, _02228A14 ; =0x04000018
	str r2, [r1]
	str r2, [r0]
	ldr r0, _02228A0C ; =0x022430D4
	ldr r2, [r0]
	ldrb r0, [r2, #0x54]
	cmp r0, #0
	bne _02228948
	bl MOD13_02233570
	bl MOD13_02234164
	ldrb r0, [r0, #0xf4]
	bl MOD13_02233C24
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	ldr r0, _02228A18 ; =MOD13_02230EC4
	bl MOD13_02222FBC
	b _022289FC
_02228948:
	ldr r0, _02228A1C ; =0x022430CC
	ldrb r0, [r0]
	cmp r0, #4
	bne _02228974
	bl MOD13_02233570
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02228A20 ; =MOD13_0222F8A0
	bl MOD13_02222FBC
	b _022289FC
_02228974:
	ldrb r1, [r2, #0x52]
	ldr r2, [r2]
	mov r0, #0x2a
	mla r0, r1, r0, r2
	bl MOD13_02234104
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r1, _02228A0C ; =0x022430D4
	mov r0, #0x2a
	ldr r2, [r1]
	ldrb r1, [r2, #0x52]
	ldr r2, [r2]
	mla r0, r1, r0, r2
	ldrb r0, [r0, #0x28]
	cmp r0, #0
	beq _022289DC
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	mov r0, #1
	mov r1, r0
	bl MOD13_02222F6C
	ldr r0, _02228A24 ; =MOD13_0222A190
	bl MOD13_02222FBC
	b _022289FC
_022289DC:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, #1
	bl MOD13_02222F6C
	ldr r0, _02228A28 ; =MOD13_0223197C
	bl MOD13_02222FBC
_022289FC:
	ldr r0, _02228A0C ; =0x022430D4
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02228A0C: .word 0x022430D4
_02228A10: .word 0x04000010
_02228A14: .word 0x04000018
_02228A18: .word MOD13_02230EC4
_02228A1C: .word 0x022430CC
_02228A20: .word MOD13_0222F8A0
_02228A24: .word MOD13_0222A190
_02228A28: .word MOD13_0223197C

	arm_func_start MOD13_02228A2C
MOD13_02228A2C: ; 0x02228A2C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02228AA0 ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x54]
	cmp r0, #0
	beq _02228A64
	bl MOD13_0221ED28
	b _02228A68
_02228A64:
	bl MOD13_0221EC84
_02228A68:
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x1d
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02228AA4 ; =MOD13_02228808
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02228AA0: .word 0x022430D4
_02228AA4: .word MOD13_02228808

	arm_func_start MOD13_02228AA8
MOD13_02228AA8: ; 0x02228AA8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02228ACC ; =MOD13_02228A2C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02228ACC: .word MOD13_02228A2C

	arm_func_start MOD13_02228AD0
MOD13_02228AD0: ; 0x02228AD0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02228BF8 ; =0x022430D4
	ldr r1, [r0]
	ldr r0, [r1, #0x38]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrb r0, [r1, #0x57]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02228B1C
	cmp r0, #1
	beq _02228B28
	add sp, sp, #4
	ldmia sp!, {pc}
_02228B1C:
	mov r0, #7
	bl MOD13_0223424C
	b _02228BE8
_02228B28:
	ldr r0, _02228BFC ; =0x022430CC
	ldrb r0, [r0]
	cmp r0, #4
	bne _02228B58
	ldr r0, _02228BF8 ; =0x022430D4
	mov r2, #1
	ldr r1, [r0]
	mov r0, #6
	strb r2, [r1, #0x54]
	bl MOD13_0223424C
	bl MOD13_02227F80
	b _02228BE8
_02228B58:
	ldr r0, _02228C00 ; =0x022430D0
	mov r1, #0x1c
	ldrh r0, [r0]
	bl FX_DivS32
	ldr r1, _02228BFC ; =0x022430CC
	ldr r2, _02228BF8 ; =0x022430D4
	ldrb lr, [r1]
	ldr ip, [r2]
	mov r1, #0x2a
	ldr r3, [ip]
	add lr, lr, r0
	mla r0, lr, r1, r3
	ldrb r0, [r0, #0x28]
	cmp r0, #2
	bne _02228BD0
	mov r0, #9
	bl MOD13_0223424C
	bl MOD13_02232F14
	bl MOD13_0221EC84
	mov r1, #1
	mov r0, #0
	str r0, [sp]
	mov r2, r1
	mov r0, #0xe
	mvn r3, #0
	bl MOD13_02235EFC
	ldr r0, _02228C04 ; =MOD13_02227F48
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02228BD0:
	mov r0, #1
	strb r0, [ip, #0x54]
	ldr r1, [r2]
	mov r0, #6
	strb lr, [r1, #0x52]
	bl MOD13_0223424C
_02228BE8:
	ldr r0, _02228C08 ; =MOD13_02228AA8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02228BF8: .word 0x022430D4
_02228BFC: .word 0x022430CC
_02228C00: .word 0x022430D0
_02228C04: .word MOD13_02227F48
_02228C08: .word MOD13_02228AA8

	arm_func_start MOD13_02228C0C
MOD13_02228C0C: ; 0x02228C0C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02228EBC ; =0x022430D4
	ldr r1, [r0]
	ldr r0, [r1, #0x38]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrb r0, [r1, #0x55]
	cmp r0, #0
	subne r0, r0, #1
	strneb r0, [r1, #0x55]
	bl MOD13_02232F50
	cmp r0, #7
	addls pc, pc, r0, lsl #2
	b _02228EB4
_02228C4C: ; jump table
	b _02228EB4 ; case 0
	b _02228C6C ; case 1
	b _02228C88 ; case 2
	b _02228CE4 ; case 3
	b _02228DA4 ; case 4
	b _02228EA4 ; case 5
	b _02228E1C ; case 6
	b _02228EA4 ; case 7
_02228C6C:
	ldr r0, _02228EBC ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x57]
	bl MOD13_0221EC84
	add sp, sp, #4
	ldmia sp!, {pc}
_02228C88:
	ldr r0, _02228EBC ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x55]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221F21C
	bl MOD13_02232F64
	ldr r1, _02228EBC ; =0x022430D4
	ldr r1, [r1]
	ldrh r2, [r1, #0x40]
	ldrb r1, [r1, #0x53]
	mul r0, r2, r0
	bl FX_DivS32
	ldr r1, _02228EC0 ; =0x022430D0
	strh r0, [r1]
	bl MOD13_02228754
	ldr r0, _02228EBC ; =0x022430D4
	mov r1, #4
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x55]
	ldmia sp!, {pc}
_02228CE4:
	ldr r0, _02228EBC ; =0x022430D4
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x57]
	bl MOD13_0221EC9C
	bl MOD13_02232F64
	ldr r1, _02228EBC ; =0x022430D4
	ldr r1, [r1]
	ldrh r2, [r1, #0x40]
	ldrb r1, [r1, #0x53]
	mul r0, r2, r0
	bl FX_DivS32
	ldr r1, _02228EC0 ; =0x022430D0
	strh r0, [r1]
	mov r0, #0x13
	bl MOD13_0223424C
	bl MOD13_02228754
	ldr r0, _02228EC0 ; =0x022430D0
	mov r1, #0x1c
	ldrh r0, [r0]
	bl FX_ModS32
	cmp r0, #0
	bne _02228D4C
	bl MOD13_02228248
	add sp, sp, #4
	ldmia sp!, {pc}
_02228D4C:
	cmp r0, #0xe
	bge _02228D7C
	mov r0, #0
	ldr r1, _02228EC4 ; =MOD13_022283B4
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02228EBC ; =0x022430D4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_02228D7C:
	mov r0, #0
	ldr r1, _02228EC8 ; =MOD13_02228314
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02228EBC ; =0x022430D4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_02228DA4:
	ldr r0, _02228EC0 ; =0x022430D0
	ldrh r0, [r0]
	cmp r0, #0
	bne _02228DEC
	ldr r0, _02228EBC ; =0x022430D4
	ldr r0, [r0]
	ldrb r0, [r0, #0x58]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _02228EBC ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x58]
	ldmia sp!, {pc}
_02228DEC:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _02228EC4 ; =MOD13_022283B4
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02228EBC ; =0x022430D4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_02228E1C:
	ldr r0, _02228EBC ; =0x022430D4
	ldr r2, [r0]
	ldrb r0, [r2, #0x51]
	cmp r0, #4
	bls _02228E44
	ldr r0, _02228EC0 ; =0x022430D0
	ldrh r1, [r2, #0x40]
	ldrh r0, [r0]
	cmp r0, r1
	bne _02228E74
_02228E44:
	ldrb r0, [r2, #0x58]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _02228EBC ; =0x022430D4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x58]
	ldmia sp!, {pc}
_02228E74:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _02228EC8 ; =MOD13_02228314
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02228EBC ; =0x022430D4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_02228EA4:
	ldr r0, _02228EBC ; =0x022430D4
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x58]
_02228EB4:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02228EBC: .word 0x022430D4
_02228EC0: .word 0x022430D0
_02228EC4: .word MOD13_022283B4
_02228EC8: .word MOD13_02228314

	arm_func_start MOD13_02228ECC
MOD13_02228ECC: ; 0x02228ECC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _02229140 ; =0x022430D4
	ldr r1, [r0]
	ldr r0, [r1, #0x38]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	ldrb r0, [r1, #0x57]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _02229144 ; =0x0223F75C
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02228F74
	ldr r0, _02229140 ; =0x022430D4
	mvn r1, #0
	ldr r0, [r0]
	ldr r4, _02229148 ; =0x0223F1FC
	strb r1, [r0, #0x50]
	mov r5, #0
_02228F24:
	mov r0, r4
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02228F64
	cmp r5, #4
	ldrlt r0, _02229140 ; =0x022430D4
	ldrlt r0, [r0]
	strltb r5, [r0, #0x50]
	blt _02228F74
	mov r0, #1
	bl MOD13_0221ECF4
	ldr r0, _0222914C ; =0x022430CC
	strb r5, [r0]
	bl MOD13_02228248
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02228F64:
	add r5, r5, #1
	cmp r5, #5
	add r4, r4, #8
	blo _02228F24
_02228F74:
	ldr r0, _02229144 ; =0x0223F75C
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02228FF4
	ldr r5, _02229148 ; =0x0223F1FC
	mov r4, #0
_02228F8C:
	mov r0, r5
	bl MOD13_0223B1DC
	cmp r0, #0
	beq _02228FE4
	ldr r0, _02229140 ; =0x022430D4
	ldr r1, [r0]
	ldrsb r0, [r1, #0x50]
	cmp r0, r4
	bne _02228FF4
	ldrb r0, [r1, #0x51]
	cmp r4, r0
	blt _02228FC8
	mov r0, #9
	bl MOD13_0223424C
	b _02228FF4
_02228FC8:
	mov r0, #1
	bl MOD13_0221ECF4
	ldr r0, _0222914C ; =0x022430CC
	strb r4, [r0]
	bl MOD13_02228248
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02228FE4:
	add r4, r4, #1
	cmp r4, #4
	add r5, r5, #8
	blt _02228F8C
_02228FF4:
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02229018
	mov r0, #1
	bl MOD13_0221ECF4
	bl MOD13_02232F14
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02229018:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02229038
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02229038:
	mov r0, #0x200
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02229054
	bl MOD13_02227FBC
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02229054:
	mov r0, #0x200
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _02229140 ; =0x022430D4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x59]
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0x100
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02229094
	bl MOD13_02228058
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02229094:
	mov r0, #0x100
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _02229140 ; =0x022430D4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x59]
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022290D8
	mov r0, #1
	bl MOD13_022280E4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_022290D8:
	mov r0, #0x40
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _02229140 ; =0x022430D4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x59]
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222911C
	mov r0, #3
	bl MOD13_022280E4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222911C:
	mov r0, #0x80
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _02229140 ; =0x022430D4
	movne r1, #0
	ldrne r0, [r0]
	strneb r1, [r0, #0x59]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02229140: .word 0x022430D4
_02229144: .word 0x0223F75C
_02229148: .word 0x0223F1FC
_0222914C: .word 0x022430CC

	arm_func_start MOD13_02229150
MOD13_02229150: ; 0x02229150
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02228ECC
	bl MOD13_02228C0C
	bl MOD13_02228AD0
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222919C ; =MOD13_02229150
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222919C: .word MOD13_02229150

	arm_func_start MOD13_022291A0
MOD13_022291A0: ; 0x022291A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0221F0EC
	ldr r0, _022291E8 ; =0x0222916C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022291E8: .word 0x0222916C

	arm_func_start MOD13_022291EC
MOD13_022291EC: ; 0x022291EC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x1d
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x1d
	bl MOD13_0223AEF4
	ldr r0, _02229244 ; =MOD13_022291A0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229244: .word MOD13_022291A0

	arm_func_start MOD13_02229248
MOD13_02229248: ; 0x02229248
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	ldr r0, _022293BC ; =0x022430D4
	mov sb, #0
	ldr r0, [r0]
	ldrb r4, [r0, #0x51]
	cmp r4, #5
	movgt r4, #5
	cmp r4, #0
	ble _022292C4
	ldr r1, _022293C0 ; =0x0223F1C0
	ldr r0, _022293C4 ; =0x0223F1C4
	ldrb r8, [r1]
	ldrb r7, [r0]
	ldr sl, _022293BC ; =0x022430D4
	mov r6, sb
	mov r5, sb
_02229288:
	mov r0, r6
	mov r1, r8
	bl MOD13_02239E54
	ldr r2, [sl]
	mov r1, r7
	add r2, r2, sb, lsl #2
	str r0, [r2, #0x10]
	mov r0, r5
	bl MOD13_02239E54
	ldr r1, [sl]
	add r1, r1, sb, lsl #2
	add sb, sb, #1
	str r0, [r1, #0x24]
	cmp sb, r4
	blt _02229288
_022292C4:
	ldr r7, _022293C0 ; =0x0223F1C0
	mov r6, #0
	ldr sb, _022293BC ; =0x022430D4
	mov r5, r6
	ldr r8, _022293C8 ; =0x000003FF
_022292D8:
	ldr r0, [sb]
	ldrb r1, [r7]
	ldr r2, [r0, #0x10]
	mov r0, r5
	bl MOD13_02239E8C
	ldr r0, [sb]
	add r7, r7, #1
	ldr r1, [r0, #0x10]
	add r0, r0, r6, lsl #1
	ldrh r1, [r1, #4]
	add r6, r6, #1
	cmp r6, #3
	and r1, r1, r8
	strh r1, [r0, #0x42]
	blo _022292D8
	ldr r7, _022293C4 ; =0x0223F1C4
	mov r6, #0
	ldr sb, _022293BC ; =0x022430D4
	mov r5, r6
	ldr r8, _022293C8 ; =0x000003FF
_02229328:
	ldr r0, [sb]
	ldrb r1, [r7]
	ldr r2, [r0, #0x24]
	mov r0, r5
	bl MOD13_02239E8C
	ldr r0, [sb]
	add r7, r7, #1
	ldr r1, [r0, #0x24]
	add r0, r0, r6, lsl #1
	ldrh r1, [r1, #4]
	add r6, r6, #1
	cmp r6, #4
	and r1, r1, r8
	strh r1, [r0, #0x48]
	blo _02229328
	cmp r4, #0
	mov r0, #0
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldr r1, _022293BC ; =0x022430D4
_02229374:
	ldr r2, [r1]
	add r2, r2, r0, lsl #2
	ldr r3, [r2, #0x10]
	ldrh r2, [r3, #4]
	bic r2, r2, #0xc00
	orr r2, r2, #0xc00
	strh r2, [r3, #4]
	ldr r2, [r1]
	add r2, r2, r0, lsl #2
	ldr r3, [r2, #0x24]
	add r0, r0, #1
	ldrh r2, [r3, #4]
	cmp r0, r4
	bic r2, r2, #0xc00
	orr r2, r2, #0xc00
	strh r2, [r3, #4]
	blt _02229374
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_022293BC: .word 0x022430D4
_022293C0: .word 0x0223F1C0
_022293C4: .word 0x0223F1C4
_022293C8: .word 0x000003FF

	arm_func_start MOD13_022293CC
MOD13_022293CC: ; 0x022293CC
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r2, _02229470 ; =0x022430D4
	mov r1, #0x1c
	ldr ip, [r2]
	mov r0, #0
	ldrb r3, [ip, #0x51]
	sub r3, r3, #4
	mul r1, r3, r1
	strh r1, [ip, #0x40]
	ldr r2, [r2]
	ldrb r1, [r2, #0x51]
	cmp r1, #4
	movls r4, r0
	strlsb r0, [r2, #0x53]
	bls _02229428
	cmp r1, #8
	movls r1, #0x1f
	strlsb r1, [r2, #0x53]
	movls r4, #1
	movhi r1, #0x37
	strhib r1, [r2, #0x53]
	movhi r4, #2
_02229428:
	cmp r4, #0
	beq _02229450
	ldr r1, _02229470 ; =0x022430D4
	ldr r0, _02229474 ; =0x022430D0
	ldr r1, [r1]
	ldrh r2, [r0]
	ldrb r0, [r1, #0x53]
	ldrh r1, [r1, #0x40]
	mul r0, r2, r0
	bl FX_DivS32
_02229450:
	str r0, [sp]
	mov r0, r4
	mov r1, #0x55
	mov r2, #0xec
	mov r3, #0x3f
	bl MOD13_02232FB8
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02229470: .word 0x022430D4
_02229474: .word 0x022430D0

	arm_func_start MOD13_02229478
MOD13_02229478: ; 0x02229478
	stmdb sp!, {lr}
	sub sp, sp, #0x34
	ldr r3, _022295AC ; =0x0223F1E0
	add lr, sp, #0
	mov r2, #0xc
_0222948C:
	ldrb r1, [r3], #1
	ldrb r0, [r3], #1
	subs r2, r2, #1
	strb r1, [lr], #1
	strb r0, [lr], #1
	bne _0222948C
	ldrb r0, [r3]
	ldr ip, _022295B0 ; =0x0223F1C8
	add r3, sp, #0x19
	strb r0, [lr]
	mov r2, #0xb
_022294B8:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _022294B8
	ldr r0, _022295B4 ; =0x0224015C
	ldr r1, _022295B8 ; =0x020C8FBC
	bl MOD13_0221F174
	add r0, sp, #0
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _022295BC ; =0x022430D4
	ldr r2, [r1]
	str r0, [r2, #4]
	ldr r0, [r1]
	ldr r0, [r0, #4]
	bl MOD13_02232918
	bl MOD13_022328D0
	add r0, sp, #0x19
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _022295BC ; =0x022430D4
	ldr r2, _022295C0 ; =0x04001008
	ldr r1, [r1]
	ldr lr, _022295C4 ; =0x0400100A
	str r0, [r1, #8]
	ldrh r0, [r2]
	ldr ip, _022295C8 ; =0x04000008
	ldr r3, _022295CC ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [lr]
	ldr r2, _022295D0 ; =0x0400000C
	ldr r1, _022295D4 ; =0x0400000E
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [lr]
	ldrh r0, [ip]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #2
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #2
	strh r0, [r1]
	add sp, sp, #0x34
	ldmia sp!, {pc}
	.align 2, 0
_022295AC: .word 0x0223F1E0
_022295B0: .word 0x0223F1C8
_022295B4: .word 0x0224015C
_022295B8: .word 0x020C8FBC
_022295BC: .word 0x022430D4
_022295C0: .word 0x04001008
_022295C4: .word 0x0400100A
_022295C8: .word 0x04000008
_022295CC: .word 0x0400000A
_022295D0: .word 0x0400000C
_022295D4: .word 0x0400000E

	arm_func_start MOD13_022295D8
MOD13_022295D8: ; 0x022295D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x5c
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r2, _022296AC ; =0x022430D4
	mov r1, #0
	str r0, [r2]
	add r0, sp, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	ldreq r0, _022296B0 ; =0x022430D0
	moveq r2, #0
	streqh r2, [r0]
	ldr r0, _022296AC ; =0x022430D4
	ldreq r1, _022296B4 ; =0x022430CC
	ldr r0, [r0]
	streqb r2, [r1]
	bl MOD13_0223333C
	ldr r1, _022296AC ; =0x022430D4
	ldr r1, [r1]
	strb r0, [r1, #0x51]
	bl MOD13_02229478
	bl MOD13_0221F4AC
	mov r0, #0x34
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #2
	bl MOD13_0221F124
	bl MOD13_022293CC
	bl MOD13_02229248
	mov r0, #0
	mov r1, r0
	bl MOD13_0223A7F0
	ldr r2, _022296AC ; =0x022430D4
	ldr r1, _022296B8 ; =MOD13_0222829C
	ldr r3, [r2]
	mov r2, #0
	str r0, [r3, #0xc]
	mov r0, #1
	mov r3, #0x6e
	bl MOD13_0223C1C4
	ldr r1, _022296AC ; =0x022430D4
	ldr r1, [r1]
	str r0, [r1, #0x3c]
	bl MOD13_02228754
	bl MOD13_02228248
	ldr r0, _022296BC ; =MOD13_022291EC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022296AC: .word 0x022430D4
_022296B0: .word 0x022430D0
_022296B4: .word 0x022430CC
_022296B8: .word MOD13_0222829C
_022296BC: .word MOD13_022291EC

	arm_func_start MOD13_022296C0
MOD13_022296C0: ; 0x022296C0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02229704 ; =0x022430D8
	ldr r1, _02229708 ; =0xC1FFFCFF
	ldr r2, [r0]
	ldr r0, _0222970C ; =MOD13_02229FD0
	ldr r3, [r2, #4]
	ldr r2, [r3]
	and r1, r2, r1
	str r1, [r3]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229704: .word 0x022430D8
_02229708: .word 0xC1FFFCFF
_0222970C: .word MOD13_02229FD0

	arm_func_start MOD13_02229710
MOD13_02229710: ; 0x02229710
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _02229744 ; =MOD13_022296C0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229744: .word MOD13_022296C0

	arm_func_start MOD13_02229748
MOD13_02229748: ; 0x02229748
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	add r0, sp, #0
	add r1, sp, #4
	bl MOD13_02222F44
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _02229778
	mov r0, #0x35
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
_02229778:
	add r0, sp, #0
	add r1, sp, #4
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	bne _022297B0
	ldr r0, _022298E0 ; =0x022430D8
	add sp, sp, #0xc
	ldr r0, [r0]
	ldrb r0, [r0, #8]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	ldmia sp!, {pc}
_022297B0:
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _022297D8
	ldr r0, _022298E0 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #8]
	cmp r0, #0
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {pc}
_022297D8:
	ldr r0, _022298E0 ; =0x022430D8
	mov r1, #0x20
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD13_0223BDA4
	cmp r0, #0x10
	bgt _02229838
	cmp r0, #0xa
	blt _02229818
	cmp r0, #0xa
	beq _02229864
	cmp r0, #0xd
	beq _02229858
	cmp r0, #0x10
	beq _02229858
	b _022298D4
_02229818:
	cmp r0, #0
	bgt _0222982C
	cmp r0, #0
	beq _02229858
	b _022298D4
_0222982C:
	cmp r0, #5
	beq _02229858
	b _022298D4
_02229838:
	cmp r0, #0x1a
	bgt _0222984C
	cmp r0, #0x1a
	beq _02229864
	b _022298D4
_0222984C:
	cmp r0, #0x20
	beq _02229864
	b _022298D4
_02229858:
	add sp, sp, #0xc
	mov r0, #1
	ldmia sp!, {pc}
_02229864:
	cmp r0, #0
	mov r3, #0
	ble _022298C8
	ldr r1, _022298E0 ; =0x022430D8
	ldr r1, [r1]
_02229878:
	ldrb r2, [r1, #8]
	cmp r2, #0x30
	blo _0222988C
	cmp r2, #0x39
	bls _022298B8
_0222988C:
	cmp r2, #0x41
	blo _0222989C
	cmp r2, #0x46
	bls _022298B8
_0222989C:
	cmp r2, #0x61
	blo _022298AC
	cmp r2, #0x66
	bls _022298B8
_022298AC:
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {pc}
_022298B8:
	add r3, r3, #1
	cmp r3, r0
	add r1, r1, #1
	blt _02229878
_022298C8:
	add sp, sp, #0xc
	mov r0, #1
	ldmia sp!, {pc}
_022298D4:
	mov r0, #0
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_022298E0: .word 0x022430D8

	arm_func_start MOD13_022298E4
MOD13_022298E4: ; 0x022298E4
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _02229980 ; =0x0223F260
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [sp]
	str r0, [sp, #4]
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {pc}
	ldr r0, _02229984 ; =0x022430D8
	ldr r1, [r0]
	ldrb r0, [r1, #0x2a]
	cmp r0, #0
	bne _02229948
	ldr r3, [r1, #4]
	ldr r1, _02229988 ; =0xC1FFFCFF
	ldr r2, [r3]
	ldr r0, _0222998C ; =MOD13_02229FD0
	and r1, r2, r1
	str r1, [r3]
	bl MOD13_02222FBC
	add sp, sp, #0xc
	ldmia sp!, {pc}
_02229948:
	add r0, sp, #8
	mov r1, #0
	bl MOD13_02222F44
	ldr r0, _02229984 ; =0x022430D8
	ldr r2, [sp, #8]
	add r1, sp, #0
	ldr r0, [r0]
	ldr r1, [r1, r2, lsl #2]
	add r0, r0, #8
	blx r1
	ldr r0, _02229990 ; =MOD13_02229B88
	bl MOD13_02222FBC
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02229980: .word 0x0223F260
_02229984: .word 0x022430D8
_02229988: .word 0xC1FFFCFF
_0222998C: .word MOD13_02229FD0
_02229990: .word MOD13_02229B88

	arm_func_start MOD13_02229994
MOD13_02229994: ; 0x02229994
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	ldr r1, _022299F4 ; =0x022430D8
	ldr r2, [r1]
	strb r0, [r2, #0x2a]
	ldr r0, [r1]
	ldrb r0, [r0, #0x2a]
	cmp r0, #0
	beq _022299CC
	cmp r0, #1
	beq _022299D8
	add sp, sp, #4
	ldmia sp!, {pc}
_022299CC:
	mov r0, #7
	bl MOD13_0223424C
	b _022299E0
_022299D8:
	mov r0, #0xe
	bl MOD13_0223424C
_022299E0:
	bl MOD13_02235EB0
	ldr r0, _022299F8 ; =MOD13_022298E4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022299F4: .word 0x022430D8
_022299F8: .word MOD13_022298E4

	arm_func_start MOD13_022299FC
MOD13_022299FC: ; 0x022299FC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02229A64 ; =0x022430D8
	ldr r1, [r0]
	ldrb r0, [r1, #0x29]
	ldr lr, [r1, #4]
	ldr r1, _02229A68 ; =0x0223F268
	cmp r0, #0x20
	and r3, r0, #0xf
	mov r2, r0, asr #4
	movhs r3, #0xf
	ldrb ip, [r1, r3]
	ldr r0, _02229A6C ; =0x0223F250
	movhs r2, #1
	ldrb r2, [r0, r2]
	ldr r3, [lr]
	ldr r1, _02229A70 ; =0xFE00FF00
	ldr r0, _02229A74 ; =0x000001FF
	and r1, r3, r1
	and r2, r2, #0xff
	and r3, ip, r0
	orr r0, r1, r2
	orr r0, r0, r3, lsl #16
	str r0, [lr]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229A64: .word 0x022430D8
_02229A68: .word 0x0223F268
_02229A6C: .word 0x0223F250
_02229A70: .word 0xFE00FF00
_02229A74: .word 0x000001FF

	arm_func_start MOD13_02229A78
MOD13_02229A78: ; 0x02229A78
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x1c
	add r0, sp, #0x10
	mov r1, #0
	strh r1, [r0]
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	strh r1, [r0, #6]
	ldr r2, _02229B74 ; =0x0223F250
	ldr r0, _02229B78 ; =0x0223F254
	ldrb r4, [r2]
	ldrh r3, [r0]
	ldrh r2, [r0, #2]
	ldr r0, _02229B7C ; =0x022430D8
	strh r4, [sp, #0x12]
	ldr r0, [r0]
	strh r3, [sp, #0x14]
	strh r2, [sp, #0x16]
	ldr r0, [r0]
	bl MOD13_0223A4D8
	mov sb, #0
	ldr r0, _02229B74 ; =0x0223F250
	ldr r6, _02229B80 ; =0x0000E01D
	ldrb r8, [r0, #1]
	ldr fp, _02229B84 ; =0x0223F268
	mov sl, sb
	strh sb, [sp, #0x1a]
	mov r7, sb
	mov r5, #2
	mov r4, #0x480
_02229AF0:
	ldr r0, _02229B7C ; =0x022430D8
	cmp sb, #0x10
	ldr r0, [r0]
	moveq sl, r7
	streqh r8, [sp, #0x12]
	add r1, r0, sb
	ldrb r1, [r1, #8]
	ldrb r2, [fp, sl]
	cmp r1, #0x20
	streqh r6, [sp, #0x18]
	strneh r1, [sp, #0x18]
	ldrh r1, [sp, #0x16]
	strh r2, [sp, #0x10]
	str r1, [sp]
	str r5, [sp, #4]
	str r4, [sp, #8]
	add r1, sp, #0x18
	str r1, [sp, #0xc]
	ldrh r1, [sp, #0x10]
	ldrh r2, [sp, #0x12]
	ldrh r3, [sp, #0x14]
	ldr r0, [r0]
	bl MOD13_0223A4F0
	add sb, sb, #1
	cmp sb, #0x20
	add sl, sl, #1
	blt _02229AF0
	ldr r0, _02229B7C ; =0x022430D8
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD13_0223A410
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02229B74: .word 0x0223F250
_02229B78: .word 0x0223F254
_02229B7C: .word 0x022430D8
_02229B80: .word 0x0000E01D
_02229B84: .word 0x0223F268

	arm_func_start MOD13_02229B88
MOD13_02229B88: ; 0x02229B88
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	bl MOD13_0221EE54
	ldr r0, _02229C74 ; =0x022430D8
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD13_0223B974
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _02229C78 ; =0x02240174
	ldr r1, _02229C7C ; =0x020C9480
	bl MOD13_0221F174
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	add r0, sp, #0
	add r1, sp, #4
	bl MOD13_02222F44
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _02229C0C
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r1, [sp]
	mov r0, #0
	bl MOD13_02222F6C
	ldr r0, _02229C80 ; =MOD13_0222DD4C
	bl MOD13_02222FBC
	b _02229C64
_02229C0C:
	ldr r0, _02229C74 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x2a]
	cmp r0, #0
	bne _02229C44
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	mov r0, #1
	mov r1, #0
	bl MOD13_02222F6C
	ldr r0, _02229C84 ; =MOD13_022295D8
	bl MOD13_02222FBC
	b _02229C64
_02229C44:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, #1
	bl MOD13_02222F6C
	ldr r0, _02229C88 ; =MOD13_0223197C
	bl MOD13_02222FBC
_02229C64:
	ldr r0, _02229C74 ; =0x022430D8
	bl MOD13_0223AF90
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02229C74: .word 0x022430D8
_02229C78: .word 0x02240174
_02229C7C: .word 0x020C9480
_02229C80: .word MOD13_0222DD4C
_02229C84: .word MOD13_022295D8
_02229C88: .word MOD13_0223197C

	arm_func_start MOD13_02229C8C
MOD13_02229C8C: ; 0x02229C8C
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr r0, _02229D50 ; =0x0223F258
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [sp, #4]
	str r0, [sp, #8]
	bl MOD13_022211C8
	cmp r0, #0
	addne sp, sp, #0x14
	ldmneia sp!, {pc}
	ldr r0, _02229D54 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x2a]
	cmp r0, #0
	bne _02229CDC
	ldr r0, _02229D58 ; =MOD13_02229B88
	bl MOD13_02222FBC
	add sp, sp, #0x14
	ldmia sp!, {pc}
_02229CDC:
	cmp r0, #2
	bne _02229D10
	mov ip, #0
	mov r0, #6
	mov r1, #3
	mov r2, #1
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	ldr r0, _02229D5C ; =MOD13_02229710
	bl MOD13_02222FBC
	add sp, sp, #0x14
	ldmia sp!, {pc}
_02229D10:
	add r1, sp, #0xc
	mov r0, #0
	bl MOD13_02222F44
	mov r0, #0
	str r0, [sp]
	ldr r2, [sp, #0xc]
	add r0, sp, #4
	ldr r0, [r0, r2, lsl #2]
	mov r1, #2
	mov r2, #1
	mvn r3, #0
	bl MOD13_02235EFC
	ldr r0, _02229D60 ; =MOD13_02229994
	bl MOD13_02222FBC
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.align 2, 0
_02229D50: .word 0x0223F258
_02229D54: .word 0x022430D8
_02229D58: .word MOD13_02229B88
_02229D5C: .word MOD13_02229710
_02229D60: .word MOD13_02229994

	arm_func_start MOD13_02229D64
MOD13_02229D64: ; 0x02229D64
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02221220
	mov r0, #0x15
	bl MOD13_0223424C
	ldr r0, _02229D9C ; =MOD13_02229C8C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229D9C: .word MOD13_02229C8C

	arm_func_start MOD13_02229DA0
MOD13_02229DA0: ; 0x02229DA0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02229DC0 ; =MOD13_02229D64
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229DC0: .word MOD13_02229D64

	arm_func_start MOD13_02229DC4
MOD13_02229DC4: ; 0x02229DC4
	bx lr

	arm_func_start MOD13_02229DC8
MOD13_02229DC8: ; 0x02229DC8
	stmdb sp!, {r4, lr}
	bl MOD13_0222120C
	mov r4, r0
	cmp r4, #0x83
	bgt _02229E0C
	cmp r4, #0x80
	blt _02229E00
	cmp r4, #0x80
	beq _02229E18
	cmp r4, #0x82
	beq _02229E7C
	cmp r4, #0x83
	beq _02229EA0
	b _02229F0C
_02229E00:
	cmp r4, #0
	beq _02229F70
	b _02229F0C
_02229E0C:
	ldr r0, _02229F7C ; =0x0000E01D
	cmp r4, r0
	b _02229F0C
_02229E18:
	ldr r0, _02229F80 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x29]
	cmp r0, #0
	beq _02229F70
	mov r0, #3
	bl MOD13_0223424C
	ldr r1, _02229F80 ; =0x022430D8
	mov r0, #0
	ldr r3, [r1]
	ldrb r2, [r3, #0x29]
	sub r2, r2, #1
	strb r2, [r3, #0x29]
	ldr r3, [r1]
	ldrb r2, [r3, #0x29]
	add r2, r3, r2
	strb r0, [r2, #8]
	ldr r1, [r1]
	ldrb r1, [r1, #0x29]
	cmp r1, #0
	bne _02229E70
	bl MOD13_022211F8
_02229E70:
	mov r0, #1
	bl MOD13_022211E4
	b _02229F70
_02229E7C:
	mov r0, #7
	bl MOD13_0223424C
	ldr r1, _02229F80 ; =0x022430D8
	ldr r0, _02229F84 ; =MOD13_02229DA0
	ldr r1, [r1]
	mov r2, #0
	strb r2, [r1, #0x2a]
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
_02229EA0:
	bl MOD13_02229748
	cmp r0, #0
	beq _02229EC8
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _02229F80 ; =0x022430D8
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x2a]
	b _02229EE0
_02229EC8:
	ldr r0, _02229F80 ; =0x022430D8
	mov r2, #2
	ldr r1, [r0]
	mov r0, #9
	strb r2, [r1, #0x2a]
	bl MOD13_0223424C
_02229EE0:
	ldr r0, _02229F80 ; =0x022430D8
	ldr r1, _02229F88 ; =0xC1FFFCFF
	ldr r2, [r0]
	ldr r0, _02229F84 ; =MOD13_02229DA0
	ldr r3, [r2, #4]
	ldr r2, [r3]
	and r1, r2, r1
	orr r1, r1, #0x200
	str r1, [r3]
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
_02229F0C:
	ldr r0, _02229F80 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x29]
	cmp r0, #0x20
	beq _02229F70
	mov r0, #1
	bl MOD13_0223424C
	ldr r1, _02229F80 ; =0x022430D8
	mov r0, #1
	ldr r3, [r1]
	ldrb r2, [r3, #0x29]
	add r2, r3, r2
	strb r4, [r2, #8]
	ldr r2, [r1]
	ldrb r1, [r2, #0x29]
	add r1, r1, #1
	strb r1, [r2, #0x29]
	bl MOD13_022211F8
	ldr r0, _02229F80 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x29]
	cmp r0, #0x20
	bne _02229F70
	mov r0, #0
	bl MOD13_022211E4
_02229F70:
	bl MOD13_02229A78
	bl MOD13_022299FC
	ldmia sp!, {r4, pc}
	.align 2, 0
_02229F7C: .word 0x0000E01D
_02229F80: .word 0x022430D8
_02229F84: .word MOD13_02229DA0
_02229F88: .word 0xC1FFFCFF

	arm_func_start MOD13_02229F8C
MOD13_02229F8C: ; 0x02229F8C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02229DC8
	bl MOD13_02229DC4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222120C
	cmp r0, #0xff
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _02229FCC ; =MOD13_02229F8C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02229FCC: .word MOD13_02229F8C

	arm_func_start MOD13_02229FD0
MOD13_02229FD0: ; 0x02229FD0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0222125C
	mov r0, #0x14
	bl MOD13_0223424C
	ldr r0, _0222A054 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x29]
	cmp r0, #0
	bne _0222A028
	mov r0, #0
	bl MOD13_022211F8
_0222A028:
	ldr r0, _0222A054 ; =0x022430D8
	ldr r0, [r0]
	ldrb r0, [r0, #0x29]
	cmp r0, #0x20
	bne _0222A044
	mov r0, #0
	bl MOD13_022211E4
_0222A044:
	ldr r0, _0222A058 ; =0x02229FA4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A054: .word 0x022430D8
_0222A058: .word 0x02229FA4

	arm_func_start MOD13_0222A05C
MOD13_0222A05C: ; 0x0222A05C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222A0B4 ; =MOD13_02229FD0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A0B4: .word MOD13_02229FD0

	arm_func_start MOD13_0222A0B8
MOD13_0222A0B8: ; 0x0222A0B8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222A15C ; =0x0224018C
	ldr r1, _0222A160 ; =0x020C9480
	bl MOD13_0221F174
	ldr r0, _0222A164 ; =0x022401A0
	ldr r1, _0222A168 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _0222A16C ; =0x022401B8
	ldr r1, _0222A170 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _0222A174 ; =0x022401D0
	ldr r1, _0222A178 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222A17C ; =0x04001008
	ldr ip, _0222A180 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222A184 ; =0x04000008
	ldr r2, _0222A188 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222A18C ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #2
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A15C: .word 0x0224018C
_0222A160: .word 0x020C9480
_0222A164: .word 0x022401A0
_0222A168: .word 0x020C8D4C
_0222A16C: .word 0x022401B8
_0222A170: .word 0x020C9550
_0222A174: .word 0x022401D0
_0222A178: .word 0x020C908C
_0222A17C: .word 0x04001008
_0222A180: .word 0x0400100A
_0222A184: .word 0x04000008
_0222A188: .word 0x0400000A
_0222A18C: .word 0x0400000C

	arm_func_start MOD13_0222A190
MOD13_0222A190: ; 0x0222A190
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r1, _0222A2B8 ; =0x0223F24C
	mov r0, #0x2c
	ldrb r3, [r1]
	ldrb r2, [r1, #1]
	mov r1, #4
	strb r3, [sp]
	strb r2, [sp, #1]
	bl MOD13_0223AFE0
	ldr r2, _0222A2BC ; =0x022430D8
	add r1, sp, #8
	str r0, [r2]
	add r0, sp, #4
	bl MOD13_02222F44
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0222A208
	ldr r0, _0222A2BC ; =0x022430D8
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD13_02233E90
	ldr r0, _0222A2BC ; =0x022430D8
	mov r1, #0x20
	ldr r0, [r0]
	add r0, r0, #8
	bl MOD13_0223BDA4
	ldr r1, _0222A2BC ; =0x022430D8
	ldr r1, [r1]
	strb r0, [r1, #0x29]
_0222A208:
	bl MOD13_0222A0B8
	ldr r0, [sp, #4]
	add r0, r0, #9
	bl MOD13_0221F4CC
	ldr r0, [sp, #8]
	cmp r0, #1
	bne _0222A238
	mov r0, #0x35
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	b _0222A250
_0222A238:
	ldr r2, [sp, #4]
	add r0, sp, #0
	ldrb r0, [r0, r2]
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
_0222A250:
	mov r0, #2
	bl MOD13_0221F124
	mov r0, #0
	mov r1, r0
	bl MOD13_0223A7F0
	ldr r2, _0222A2BC ; =0x022430D8
	mov r1, #0x3e
	ldr r2, [r2]
	str r0, [r2]
	mov r0, #0
	bl MOD13_02239E54
	ldr r1, _0222A2BC ; =0x022430D8
	ldr r2, [r1]
	str r0, [r2, #4]
	ldr r0, [r1]
	ldr r1, [r0, #4]
	ldrh r0, [r1, #4]
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	bl MOD13_022299FC
	bl MOD13_02229A78
	ldr r0, _0222A2C0 ; =MOD13_0222A05C
	bl MOD13_02222FBC
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_0222A2B8: .word 0x0223F24C
_0222A2BC: .word 0x022430D8
_0222A2C0: .word MOD13_0222A05C

	arm_func_start MOD13_0222A2C4
MOD13_0222A2C4: ; 0x0222A2C4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222A308 ; =0x022430DC
	ldr r1, _0222A30C ; =0xC1FFFCFF
	ldr r2, [r0]
	ldr r0, _0222A310 ; =MOD13_0222AD78
	ldr r3, [r2, #4]
	ldr r2, [r3]
	and r1, r2, r1
	str r1, [r3]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A308: .word 0x022430DC
_0222A30C: .word 0xC1FFFCFF
_0222A310: .word MOD13_0222AD78

	arm_func_start MOD13_0222A314
MOD13_0222A314: ; 0x0222A314
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _0222A348 ; =MOD13_0222A2C4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A348: .word MOD13_0222A2C4

	arm_func_start MOD13_0222A34C
MOD13_0222A34C: ; 0x0222A34C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x10
	ldr r1, _0222A4A8 ; =0x0223F278
	ldr r0, _0222A4AC ; =0x022430DC
	ldrb lr, [r1]
	ldrb ip, [r1, #1]
	ldrb r4, [r1, #2]
	ldrb r3, [r1, #3]
	mov r2, #0
	strb lr, [sp]
	ldr r0, [r0]
	strb r4, [sp, #2]
	add r5, sp, #0
	mov r1, r2
	strb ip, [sp, #1]
	strb r3, [sp, #3]
	mov lr, r2
	add r4, r0, #8
_0222A394:
	ldrb r3, [r4, r1]
	add r8, r4, r1
	cmp r3, #0x20
	beq _0222A3DC
	mov r7, lr
	mov r6, r5
_0222A3AC:
	ldrb ip, [r8, r7]
	ldrb r3, [r6]
	cmp ip, r3
	addhi sp, sp, #0x10
	movhi r0, #0
	ldmhiia sp!, {r4, r5, r6, r7, r8, pc}
	cmp ip, r3
	blo _0222A3DC
	add r7, r7, #1
	cmp r7, #3
	add r6, r6, #1
	blt _0222A3AC
_0222A3DC:
	add r2, r2, #1
	cmp r2, #4
	add r1, r1, #3
	blt _0222A394
	add r1, sp, #8
	add r0, r0, #8
	bl MOD13_02233608
	add r0, sp, #4
	mov r1, #0
	bl MOD13_02222F44
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _0222A48C
	mov ip, #0
	add r6, sp, #8
	mov r5, ip
	mov r3, ip
	mov r2, #1
_0222A424:
	mov r4, r3
_0222A428:
	cmp ip, #0
	beq _0222A450
	rsb r0, r4, #7
	ldrb r1, [r6]
	mov r0, r2, lsl r0
	ands r0, r1, r0
	beq _0222A464
	add sp, sp, #0x10
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_0222A450:
	rsb r0, r4, #7
	ldrb r1, [r6]
	mov r0, r2, lsl r0
	ands r0, r1, r0
	moveq ip, r2
_0222A464:
	add r4, r4, #1
	cmp r4, #8
	blt _0222A428
	add r5, r5, #1
	cmp r5, #4
	add r6, r6, #1
	blt _0222A424
	add sp, sp, #0x10
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_0222A48C:
	add r0, sp, #8
	bl FUN_02095AE0
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0222A4A8: .word 0x0223F278
_0222A4AC: .word 0x022430DC

	arm_func_start MOD13_0222A4B0
MOD13_0222A4B0: ; 0x0222A4B0
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r6, #0
	mov r4, r6
	ldr r0, _0222A538 ; =0x022430DC
	mov ip, r6
	mov r1, #0x20
	mov r2, #0x30
_0222A4D0:
	ldr r3, [r0]
	mov r5, ip
	add r3, r3, #8
	add r7, r3, r4
_0222A4E0:
	ldrb r3, [r7, r5]
	add lr, r7, r5
	cmp r3, #0x30
	beq _0222A500
	cmp r3, #0x20
	beq _0222A500
	cmp r3, #0
	bne _0222A51C
_0222A500:
	cmp r5, #2
	moveq r3, r2
	movne r3, r1
	add r5, r5, #1
	strb r3, [lr]
	cmp r5, #3
	blt _0222A4E0
_0222A51C:
	add r6, r6, #1
	cmp r6, #4
	add r4, r4, #3
	blt _0222A4D0
	bl MOD13_0222A6B8
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0222A538: .word 0x022430DC

	arm_func_start MOD13_0222A53C
MOD13_0222A53C: ; 0x0222A53C
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr lr, _0222A5DC ; =0x0223F2B0
	add ip, sp, #4
	ldmia lr!, {r0, r1, r2, r3}
	stmia ip!, {r0, r1, r2, r3}
	ldr r0, [lr]
	str r0, [ip]
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #0x1c
	ldmneia sp!, {pc}
	ldr r0, _0222A5E0 ; =0x022430DC
	ldr r1, [r0]
	ldrb r0, [r1, #0x15]
	cmp r0, #0
	bne _0222A5A4
	ldr r3, [r1, #4]
	ldr r1, _0222A5E4 ; =0xC1FFFCFF
	ldr r2, [r3]
	ldr r0, _0222A5E8 ; =MOD13_0222AD78
	and r1, r2, r1
	str r1, [r3]
	bl MOD13_02222FBC
	add sp, sp, #0x1c
	ldmia sp!, {pc}
_0222A5A4:
	add r0, sp, #0
	mov r1, #0
	bl MOD13_02222F44
	ldr r0, _0222A5E0 ; =0x022430DC
	ldr r2, [sp]
	add r1, sp, #4
	ldr r0, [r0]
	ldr r1, [r1, r2, lsl #2]
	add r0, r0, #8
	blx r1
	ldr r0, _0222A5EC ; =MOD13_0222A79C
	bl MOD13_02222FBC
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.align 2, 0
_0222A5DC: .word 0x0223F2B0
_0222A5E0: .word 0x022430DC
_0222A5E4: .word 0xC1FFFCFF
_0222A5E8: .word MOD13_0222AD78
_0222A5EC: .word MOD13_0222A79C

	arm_func_start MOD13_0222A5F0
MOD13_0222A5F0: ; 0x0222A5F0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	ldr r1, _0222A650 ; =0x022430DC
	ldr r2, [r1]
	strb r0, [r2, #0x15]
	ldr r0, [r1]
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _0222A628
	cmp r0, #1
	beq _0222A634
	add sp, sp, #4
	ldmia sp!, {pc}
_0222A628:
	mov r0, #7
	bl MOD13_0223424C
	b _0222A63C
_0222A634:
	mov r0, #0xe
	bl MOD13_0223424C
_0222A63C:
	bl MOD13_02235EB0
	ldr r0, _0222A654 ; =MOD13_0222A53C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A650: .word 0x022430DC
_0222A654: .word MOD13_0222A53C

	arm_func_start MOD13_0222A658
MOD13_0222A658: ; 0x0222A658
	ldr r0, _0222A6A8 ; =0x022430DC
	ldr r2, [r0]
	mov r0, #3
	ldrb r3, [r2, #0x14]
	ldr ip, [r2, #4]
	cmp r3, #3
	movgt r3, #3
	mul r1, r3, r0
	ldr r0, _0222A6AC ; =0x0223F290
	add r1, r1, #2
	ldrb r3, [r0, r1]
	ldr r0, _0222A6B0 ; =0x000001FF
	ldr r2, [ip]
	ldr r1, _0222A6B4 ; =0xFE00FF00
	and r3, r3, r0
	and r0, r2, r1
	orr r0, r0, #0x28
	orr r0, r0, r3, lsl #16
	str r0, [ip]
	bx lr
	.align 2, 0
_0222A6A8: .word 0x022430DC
_0222A6AC: .word 0x0223F290
_0222A6B0: .word 0x000001FF
_0222A6B4: .word 0xFE00FF00

	arm_func_start MOD13_0222A6B8
MOD13_0222A6B8: ; 0x0222A6B8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x1c
	ldr r0, _0222A78C ; =0x0223F288
	ldr r1, _0222A790 ; =0x0223F27C
	ldrh r4, [r0, #4]
	ldrh r3, [r0, #6]
	ldrh r6, [r0]
	ldrh r5, [r0, #2]
	ldr r0, _0222A794 ; =0x022430DC
	ldrh r2, [r1]
	strh r4, [sp, #0x14]
	ldrh r1, [r1, #2]
	strh r3, [sp, #0x16]
	ldr r0, [r0]
	strh r6, [sp, #0x10]
	strh r5, [sp, #0x12]
	strh r2, [sp, #0x14]
	strh r1, [sp, #0x16]
	ldr r0, [r0]
	mov r1, #0
	bl MOD13_0223A4D8
	mov r5, #0
	ldr r4, _0222A798 ; =0x0223F290
	strh r5, [sp, #0x1a]
	ldr r6, _0222A794 ; =0x022430DC
	add r7, sp, #0x18
	mov sb, #2
	mov r8, #0x480
_0222A728:
	ldr ip, [r6]
	ldrh r0, [sp, #0x16]
	add r1, ip, r5
	ldrb r1, [r1, #8]
	strh r1, [sp, #0x18]
	ldrb r1, [r4]
	strh r1, [sp, #0x10]
	str r0, [sp]
	str sb, [sp, #4]
	str r8, [sp, #8]
	str r7, [sp, #0xc]
	ldrh r2, [sp, #0x12]
	ldrh r3, [sp, #0x14]
	ldr r0, [ip]
	bl MOD13_0223A4F0
	add r5, r5, #1
	cmp r5, #0xc
	add r4, r4, #1
	blt _0222A728
	ldr r0, _0222A794 ; =0x022430DC
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD13_0223A410
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_0222A78C: .word 0x0223F288
_0222A790: .word 0x0223F27C
_0222A794: .word 0x022430DC
_0222A798: .word 0x0223F290

	arm_func_start MOD13_0222A79C
MOD13_0222A79C: ; 0x0222A79C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EE54
	ldr r0, _0222A834 ; =0x022430DC
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD13_0223B974
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _0222A838 ; =0x022401E4
	ldr r1, _0222A83C ; =0x020C9480
	bl MOD13_0221F174
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	add r0, sp, #0
	mov r1, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	mov r1, #1
	cmp r0, #3
	addge r0, r0, #1
	strge r0, [sp]
	mov r0, #2
	bl MOD13_02222FA8
	ldr r1, [sp]
	mov r0, #0
	add r1, r1, #3
	bl MOD13_02222F6C
	ldr r0, _0222A840 ; =MOD13_0222DD4C
	bl MOD13_02222FBC
	ldr r0, _0222A834 ; =0x022430DC
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A834: .word 0x022430DC
_0222A838: .word 0x022401E4
_0222A83C: .word 0x020C9480
_0222A840: .word MOD13_0222DD4C

	arm_func_start MOD13_0222A844
MOD13_0222A844: ; 0x0222A844
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022228BC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222A8E0 ; =0x022430DC
	ldr r0, [r0]
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _0222A880
	ldr r0, _0222A8E4 ; =MOD13_0222A79C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222A880:
	cmp r0, #2
	bne _0222A8B4
	mov ip, #0
	mov r0, #6
	mov r1, #3
	mov r2, #1
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	ldr r0, _0222A8E8 ; =MOD13_0222A314
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222A8B4:
	mov ip, #0
	mov r0, #0x47
	mov r1, #2
	mov r2, #1
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	ldr r0, _0222A8EC ; =MOD13_0222A5F0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A8E0: .word 0x022430DC
_0222A8E4: .word MOD13_0222A79C
_0222A8E8: .word MOD13_0222A314
_0222A8EC: .word MOD13_0222A5F0

	arm_func_start MOD13_0222A8F0
MOD13_0222A8F0: ; 0x0222A8F0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02222928
	mov r0, #0x15
	bl MOD13_0223424C
	ldr r0, _0222A928 ; =MOD13_0222A844
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A928: .word MOD13_0222A844

	arm_func_start MOD13_0222A92C
MOD13_0222A92C: ; 0x0222A92C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222A94C ; =MOD13_0222A8F0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222A94C: .word MOD13_0222A8F0

	arm_func_start MOD13_0222A950
MOD13_0222A950: ; 0x0222A950
	bx lr

	arm_func_start MOD13_0222A954
MOD13_0222A954: ; 0x0222A954
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r2, _0222A9EC ; =0x022430DC
	mov r1, #3
	ldr r2, [r2]
	mov r4, r0
	ldrb r0, [r2, #0x14]
	add r3, r2, #8
	mul r2, r0, r1
	ldrb r1, [r3, r2]
	add r0, r3, r2
	cmp r1, #0
	beq _0222A998
	cmp r1, #0x20
	addne sp, sp, #8
	movne r0, #1
	ldmneia sp!, {r4, pc}
_0222A998:
	add r1, sp, #0
	mov r2, #3
	bl MI_CpuCopy8
	mov r3, #0
	add r2, sp, #0
	strb r3, [sp, #3]
	mov r0, #0x20
_0222A9B4:
	ldrb r1, [r2]
	cmp r1, #0
	bne _0222A9D0
	add r3, r3, #1
	cmp r3, #3
	strb r0, [r2], #1
	blt _0222A9B4
_0222A9D0:
	add r0, sp, #0
	bl atol
	cmp r0, r4
	movge r0, #1
	movlt r0, #0
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222A9EC: .word 0x022430DC

	arm_func_start MOD13_0222A9F0
MOD13_0222A9F0: ; 0x0222A9F0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	bl MOD13_02222914
	mov r4, r0
	cmp r4, #0
	bgt _0222AA18
	cmp r4, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	b _0222ABF4
_0222AA18:
	sub r0, r4, #0x10
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _0222ABF4
_0222AA28: ; jump table
	b _0222AA40 ; case 0
	b _0222AAF0 ; case 1
	b _0222AB48 ; case 2
	b _0222AB70 ; case 3
	add sp, sp, #4 ; case 4
	ldmia sp!, {r4, r5, pc} ; case 5
_0222AA40:
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r1, [r0]
	ldrb r0, [r1, #0x14]
	cmp r0, #0
	bne _0222AA60
	ldrb r0, [r1, #0xa]
	cmp r0, #0
	beq _0222AD18
_0222AA60:
	mov r0, #3
	bl MOD13_0223424C
	ldr r1, _0222AD28 ; =0x022430DC
	mov r0, #3
	ldr r2, [r1]
	ldrb r1, [r2, #0x14]
	mul r0, r1, r0
	add r0, r0, #2
	add r0, r2, r0
	ldrb r0, [r0, #8]
	cmp r0, #0
	subeq r0, r1, #1
	streqb r0, [r2, #0x14]
	ldr r0, _0222AD28 ; =0x022430DC
	mov r2, #3
	ldr r0, [r0]
	mov r1, #0
	ldrb r3, [r0, #0x14]
	add r0, r0, #8
	mla r0, r3, r2, r0
	bl MI_CpuFill8
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r1, [r0]
	ldrb r0, [r1, #0x14]
	cmp r0, #0
	bne _0222AADC
	ldrb r0, [r1, #0xa]
	cmp r0, #0
	bne _0222AADC
	mov r0, #0
	bl MOD13_02222900
_0222AADC:
	mov r0, #1
	bl MOD13_022228EC
	mov r0, #0
	bl MOD13_022228D8
	b _0222AD18
_0222AAF0:
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r2, [r0]
	ldrb r1, [r2, #0x14]
	cmp r1, #3
	bhs _0222AD18
	mov r0, #3
	mul r0, r1, r0
	add r0, r0, #2
	add r0, r2, r0
	ldrb r0, [r0, #8]
	cmp r0, #0
	beq _0222AD18
	mov r0, #1
	bl MOD13_0223424C
	ldr r1, _0222AD28 ; =0x022430DC
	mov r0, #0
	ldr r2, [r1]
	ldrb r1, [r2, #0x14]
	add r1, r1, #1
	strb r1, [r2, #0x14]
	bl MOD13_022228D8
	b _0222AD18
_0222AB48:
	ldr r0, _0222AD28 ; =0x022430DC
	mov r2, #0
	ldr r1, [r0]
	mov r0, #7
	strb r2, [r1, #0x15]
	bl MOD13_0223424C
	ldr r0, _0222AD2C ; =MOD13_0222A92C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222AB70:
	bl MOD13_0222A34C
	cmp r0, #0
	beq _0222AB98
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _0222AD28 ; =0x022430DC
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x15]
	b _0222ABB0
_0222AB98:
	ldr r0, _0222AD28 ; =0x022430DC
	mov r2, #2
	ldr r1, [r0]
	mov r0, #9
	strb r2, [r1, #0x15]
	bl MOD13_0223424C
_0222ABB0:
	ldr r1, _0222AD28 ; =0x022430DC
	mov r3, #3
	ldr r2, [r1]
	ldr r0, _0222AD30 ; =0xC1FFFCFF
	strb r3, [r2, #0x14]
	ldr r1, [r1]
	ldr r2, [r1, #4]
	ldr r1, [r2]
	and r0, r1, r0
	orr r0, r0, #0x200
	str r0, [r2]
	bl MOD13_0222A658
	bl MOD13_0222A4B0
	ldr r0, _0222AD2C ; =MOD13_0222A92C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222ABF4:
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r0, [r0]
	ldrb r0, [r0, #0x14]
	cmp r0, #3
	bne _0222AC18
	mov r0, #0x1a
	bl MOD13_0222A954
	cmp r0, #0
	bne _0222AD18
_0222AC18:
	mov r0, #1
	bl MOD13_0223424C
	ldr r1, _0222AD28 ; =0x022430DC
	mov r0, #3
	ldr r3, [r1]
	ldrb r2, [r3, #0x14]
	add r5, r3, #8
	mul lr, r2, r0
	add r0, lr, #2
	ldrb r3, [r5, r0]
	add ip, r5, r0
	cmp r3, #0
	streqb r4, [ip]
	beq _0222ACBC
	add r2, lr, #1
	ldrb r0, [r5, r2]
	add r2, r5, r2
	cmp r0, #0
	bne _0222AC98
	strb r3, [r2]
	mov r0, #0x1a
	strb r4, [ip]
	bl MOD13_0222A954
	cmp r0, #0
	beq _0222ACBC
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r1, [r0]
	ldrb r0, [r1, #0x14]
	cmp r0, #3
	addlo r0, r0, #1
	strlob r0, [r1, #0x14]
	b _0222ACBC
_0222AC98:
	strb r0, [r5, lr]
	ldrb r0, [ip]
	strb r0, [r2]
	strb r4, [ip]
	ldr r1, [r1]
	ldrb r0, [r1, #0x14]
	cmp r0, #3
	addlo r0, r0, #1
	strlob r0, [r1, #0x14]
_0222ACBC:
	mov r0, #1
	bl MOD13_02222900
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r0, [r0]
	ldrb r0, [r0, #0x14]
	cmp r0, #3
	bhs _0222ACE4
	mov r0, #1
	bl MOD13_022228D8
	b _0222ACEC
_0222ACE4:
	mov r0, #0
	bl MOD13_022228D8
_0222ACEC:
	ldr r0, _0222AD28 ; =0x022430DC
	ldr r0, [r0]
	ldrb r0, [r0, #0x14]
	cmp r0, #3
	bne _0222AD18
	mov r0, #0x1a
	bl MOD13_0222A954
	cmp r0, #0
	beq _0222AD18
	mov r0, #0
	bl MOD13_022228EC
_0222AD18:
	bl MOD13_0222A6B8
	bl MOD13_0222A658
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0222AD28: .word 0x022430DC
_0222AD2C: .word MOD13_0222A92C
_0222AD30: .word 0xC1FFFCFF

	arm_func_start MOD13_0222AD34
MOD13_0222AD34: ; 0x0222AD34
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222A9F0
	bl MOD13_0222A950
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02222914
	cmp r0, #0x1f
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _0222AD74 ; =MOD13_0222AD34
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222AD74: .word MOD13_0222AD34

	arm_func_start MOD13_0222AD78
MOD13_0222AD78: ; 0x0222AD78
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02222964
	mov r0, #0x14
	bl MOD13_0223424C
	ldr r0, _0222AE0C ; =0x022430DC
	ldr r0, [r0]
	ldrb r0, [r0, #0x14]
	cmp r0, #0
	bne _0222ADDC
	mov r0, #0
	bl MOD13_02222900
	mov r0, #0
	bl MOD13_022228D8
	b _0222ADFC
_0222ADDC:
	mov r0, #0x1a
	bl MOD13_0222A954
	cmp r0, #0
	beq _0222ADF4
	mov r0, #0
	bl MOD13_022228EC
_0222ADF4:
	mov r0, #0
	bl MOD13_022228D8
_0222ADFC:
	ldr r0, _0222AE10 ; =0x0222AD4C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222AE0C: .word 0x022430DC
_0222AE10: .word 0x0222AD4C

	arm_func_start MOD13_0222AE14
MOD13_0222AE14: ; 0x0222AE14
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222AE6C ; =MOD13_0222AD78
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222AE6C: .word MOD13_0222AD78

	arm_func_start MOD13_0222AE70
MOD13_0222AE70: ; 0x0222AE70
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222AF14 ; =0x022401FC
	ldr r1, _0222AF18 ; =0x020C9480
	bl MOD13_0221F174
	ldr r0, _0222AF1C ; =0x02240210
	ldr r1, _0222AF20 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _0222AF24 ; =0x02240228
	ldr r1, _0222AF28 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _0222AF2C ; =0x02240240
	ldr r1, _0222AF30 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222AF34 ; =0x04001008
	ldr ip, _0222AF38 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222AF3C ; =0x04000008
	ldr r2, _0222AF40 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222AF44 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #2
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222AF14: .word 0x022401FC
_0222AF18: .word 0x020C9480
_0222AF1C: .word 0x02240210
_0222AF20: .word 0x020C8D4C
_0222AF24: .word 0x02240228
_0222AF28: .word 0x020C9550
_0222AF2C: .word 0x02240240
_0222AF30: .word 0x020C908C
_0222AF34: .word 0x04001008
_0222AF38: .word 0x0400100A
_0222AF3C: .word 0x04000008
_0222AF40: .word 0x0400000A
_0222AF44: .word 0x0400000C

	arm_func_start MOD13_0222AF48
MOD13_0222AF48: ; 0x0222AF48
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x24
	ldr r7, _0222B0A8 ; =0x0223F29C
	ldr ip, _0222B0AC ; =0x0223F280
	ldmia r7!, {r0, r1, r2, r3}
	add r6, sp, #0xc
	stmia r6!, {r0, r1, r2, r3}
	ldrb r5, [ip]
	ldrb r4, [ip, #1]
	ldrb lr, [ip, #2]
	ldrb r3, [ip, #3]
	ldrb r2, [ip, #4]
	ldr ip, [r7]
	mov r0, #0x18
	mov r1, #4
	str ip, [r6]
	strb r5, [sp]
	strb r4, [sp, #1]
	strb lr, [sp, #2]
	strb r3, [sp, #3]
	strb r2, [sp, #4]
	bl MOD13_0223AFE0
	ldr r2, _0222B0B0 ; =0x022430DC
	mov r1, #0
	str r0, [r2]
	add r0, sp, #8
	bl MOD13_02222F44
	ldr r0, _0222B0B0 ; =0x022430DC
	ldr r2, [sp, #8]
	add r1, sp, #0xc
	ldr r0, [r0]
	ldr r1, [r1, r2, lsl #2]
	add r0, r0, #8
	blx r1
	ldr r0, _0222B0B0 ; =0x022430DC
	ldr r1, _0222B0B4 ; =0x02240258
	ldr r4, [r0]
	mov r2, #3
	add r0, r4, #8
	bl memcmp
	cmp r0, #0
	movne r0, #3
	strneb r0, [r4, #0x14]
	bne _0222B018
	add r0, r4, #8
	mov r1, #0
	mov r2, #0xc
	bl MI_CpuFill8
	ldr r0, _0222B0B0 ; =0x022430DC
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x14]
_0222B018:
	bl MOD13_0222AE70
	ldr r0, [sp, #8]
	add r0, r0, #0xb
	bl MOD13_0221F4CC
	ldr r2, [sp, #8]
	add r0, sp, #0
	ldrb r0, [r0, r2]
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #2
	bl MOD13_0221F124
	mov r0, #0
	mov r1, r0
	bl MOD13_0223A7F0
	ldr r2, _0222B0B0 ; =0x022430DC
	mov r1, #0x3f
	ldr r2, [r2]
	str r0, [r2]
	mov r0, #0
	bl MOD13_02239E54
	ldr r1, _0222B0B0 ; =0x022430DC
	ldr r2, [r1]
	str r0, [r2, #4]
	ldr r0, [r1]
	ldr r1, [r0, #4]
	ldrh r0, [r1, #4]
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	bl MOD13_0222A658
	bl MOD13_0222A6B8
	ldr r0, _0222B0B8 ; =MOD13_0222AE14
	bl MOD13_02222FBC
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0222B0A8: .word 0x0223F29C
_0222B0AC: .word 0x0223F280
_0222B0B0: .word 0x022430DC
_0222B0B4: .word 0x02240258
_0222B0B8: .word MOD13_0222AE14

	arm_func_start MOD13_0222B0BC
MOD13_0222B0BC: ; 0x0222B0BC
	ldr r1, _0222B0C8 ; =0x022430E0
	str r0, [r1]
	bx lr
	.align 2, 0
_0222B0C8: .word 0x022430E0

	arm_func_start MOD13_0222B0CC
MOD13_0222B0CC: ; 0x0222B0CC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	beq _0222B164
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222B194 ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222B164:
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, r0
	bl MOD13_02222F6C
	mov r0, #0
	bl MOD13_0222B7F4
	ldr r0, _0222B198 ; =MOD13_0222DD4C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B194: .word MOD13_02230714
_0222B198: .word MOD13_0222DD4C

	arm_func_start MOD13_0222B19C
MOD13_0222B19C: ; 0x0222B19C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222B1F4 ; =MOD13_0222B0CC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B1F4: .word MOD13_0222B0CC

	arm_func_start MOD13_0222B1F8
MOD13_0222B1F8: ; 0x0222B1F8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222B21C ; =MOD13_0222B19C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B21C: .word MOD13_0222B19C

	arm_func_start MOD13_0222B220
MOD13_0222B220: ; 0x0222B220
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _0222B250 ; =MOD13_0222B1F8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B250: .word MOD13_0222B1F8

	arm_func_start MOD13_0222B254
MOD13_0222B254: ; 0x0222B254
	bx lr

	arm_func_start MOD13_0222B258
MOD13_0222B258: ; 0x0222B258
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222B258
	bl MOD13_0222B254
	bl MOD13_0222B220
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222B2D0 ; =0x0222B284
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B2D0: .word 0x0222B284

	arm_func_start MOD13_0222B2D4
MOD13_0222B2D4: ; 0x0222B2D4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #4
	bl MOD13_0221F0EC
	ldr r0, _0222B31C ; =0x0222B2A0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B31C: .word 0x0222B2A0

	arm_func_start MOD13_0222B320
MOD13_0222B320: ; 0x0222B320
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222B358 ; =MOD13_0222B2D4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B358: .word MOD13_0222B2D4

	arm_func_start MOD13_0222B35C
MOD13_0222B35C: ; 0x0222B35C
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x28
	add r1, sp, #0x10
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, _0222B690 ; =0x022430E0
	ldr r1, _0222B694 ; =0xFFFFB17D
	ldr r0, [r0]
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B698 ; =0xFFFFB17C
	cmp r0, r1
	movge r4, #2
	bge _0222B5B8
	ldr r1, _0222B69C ; =0xFFFFB17B
	cmp r0, r1
	movge r4, #0x13
	bge _0222B5B8
	ldr r1, _0222B6A0 ; =0xFFFFB175
	cmp r0, r1
	movge r4, #2
	bge _0222B5B8
	ldr r1, _0222B6A4 ; =0xFFFFB174
	cmp r0, r1
	movge r4, #0x12
	bge _0222B5B8
	ldr r1, _0222B6A8 ; =0xFFFFB173
	cmp r0, r1
	movge r4, #2
	bge _0222B5B8
	ldr r1, _0222B6AC ; =0xFFFFB172
	cmp r0, r1
	movge r4, #3
	bge _0222B5B8
	ldr r1, _0222B6B0 ; =0xFFFFADF9
	cmp r0, r1
	movge r4, #2
	bge _0222B5B8
	ldr r1, _0222B6B4 ; =0xFFFFA629
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B6B8 ; =0xFFFFA241
	cmp r0, r1
	movge r4, #0x13
	bge _0222B5B8
	ldr r1, _0222B6BC ; =0xFFFF3CB1
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B6C0 ; =0xFFFF3CAE
	cmp r0, r1
	movge r4, #7
	bge _0222B5B8
	ldr r1, _0222B6C4 ; =0xFFFF3CAD
	cmp r0, r1
	movge r4, #5
	bge _0222B5B8
	ldr r1, _0222B6C8 ; =0xFFFF3C4E
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B6CC ; =0xFFFF3C4D
	cmp r0, r1
	blt _0222B478
	ldr r0, [sp, #0x10]
	cmp r0, #2
	moveq r4, #5
	movne r4, #7
	b _0222B5B8
_0222B478:
	ldr r1, _0222B6D0 ; =0xFFFF3866
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B6D4 ; =0xFFFF3865
	cmp r0, r1
	blt _0222B4A8
	ldr r0, [sp, #0x10]
	cmp r0, #2
	moveq r4, #5
	movne r4, #8
	b _0222B5B8
_0222B4A8:
	ldr r1, _0222B6D8 ; =0xFFFF3862
	cmp r0, r1
	movge r4, #9
	bge _0222B5B8
	ldr r1, _0222B6DC ; =0xFFFF3861
	cmp r0, r1
	movge r4, #5
	bge _0222B5B8
	ldr r1, _0222B6E0 ; =0xFFFF3801
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B6E4 ; =0xFFFF379D
	cmp r0, r1
	movge r4, #0x14
	bge _0222B5B8
	ldr r1, _0222B6E8 ; =0xFFFF379A
	cmp r0, r1
	movge r4, #0x15
	bge _0222B5B8
	ldr r1, _0222B6EC ; =0xFFFF3799
	cmp r0, r1
	movge r4, #4
	bge _0222B5B8
	ldr r1, _0222B6F0 ; =0xFFFF34E1
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B6F4 ; =0xFFFF34DE
	cmp r0, r1
	movge r4, #0xa
	bge _0222B5B8
	ldr r1, _0222B6F8 ; =0xFFFF34DD
	cmp r0, r1
	movge r4, #0x16
	bge _0222B5B8
	ldr r1, _0222B6FC ; =0xFFFF347D
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B700 ; =0xFFFF3479
	cmp r0, r1
	movge r4, #0xb
	bge _0222B5B8
	ldr r1, _0222B704 ; =0xFFFF3419
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B708 ; =0xFFFF3415
	cmp r0, r1
	movge r4, #0xb
	bge _0222B5B8
	ldr r1, _0222B70C ; =0xFFFF33B5
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B710 ; =0xFFFF3351
	cmp r0, r1
	movge r4, #2
	bge _0222B5B8
	ldr r1, _0222B714 ; =0xFFFF30F9
	cmp r0, r1
	movge r4, #0
	bge _0222B5B8
	ldr r1, _0222B718 ; =0xFFFF2FCD
	cmp r0, r1
	movge r4, #2
	movlt r4, #0
_0222B5B8:
	bl MOD13_02222F34
	mov r2, r0
	ldr r1, _0222B71C ; =0x0223F2C4
	mov r0, #0
	ldrb r1, [r1, r2]
	bl MOD13_0223A7F0
	ldr r1, _0222B720 ; =0x0224307C
	mov r5, r0
	ldr r0, [r1]
	mov r1, r4
	bl MOD13_02223568
	ldr r1, _0222B690 ; =0x022430E0
	mov r4, r0
	ldr r1, [r1]
	ldr r2, _0222B724 ; =0x0224025C
	rsb r3, r1, #0
	add r0, sp, #0x14
	mov r1, #8
	bl swprintf
	bl MOD13_02222F34
	mov r1, r0, lsl #2
	ldr r0, _0222B728 ; =0x0223F2D6
	ldrh r6, [r0, r1]
	bl MOD13_02222F34
	mov r1, r0, lsl #2
	ldr r0, _0222B72C ; =0x0223F2D4
	mov ip, #0xa
	ldrh r1, [r0, r1]
	add r3, sp, #0x14
	mov r0, #0
	str ip, [sp]
	str r3, [sp, #4]
	str r0, [sp, #8]
	mov r2, r6
	mov r0, r5
	mov r3, #2
	bl MOD13_0223A528
	bl MOD13_0221EF88
	ldr r3, _0222B730 ; =0x0223F2CC
	mov r1, #2
	ldrh r2, [r3, #6]
	str r2, [sp]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r4, [sp, #0xc]
	ldrh r1, [r3]
	ldrh r2, [r3, #2]
	ldrh r3, [r3, #4]
	mov r0, r5
	bl MOD13_0223A4F0
	mov r0, r5
	bl MOD13_0223A410
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222B690: .word 0x022430E0
_0222B694: .word 0xFFFFB17D
_0222B698: .word 0xFFFFB17C
_0222B69C: .word 0xFFFFB17B
_0222B6A0: .word 0xFFFFB175
_0222B6A4: .word 0xFFFFB174
_0222B6A8: .word 0xFFFFB173
_0222B6AC: .word 0xFFFFB172
_0222B6B0: .word 0xFFFFADF9
_0222B6B4: .word 0xFFFFA629
_0222B6B8: .word 0xFFFFA241
_0222B6BC: .word 0xFFFF3CB1
_0222B6C0: .word 0xFFFF3CAE
_0222B6C4: .word 0xFFFF3CAD
_0222B6C8: .word 0xFFFF3C4E
_0222B6CC: .word 0xFFFF3C4D
_0222B6D0: .word 0xFFFF3866
_0222B6D4: .word 0xFFFF3865
_0222B6D8: .word 0xFFFF3862
_0222B6DC: .word 0xFFFF3861
_0222B6E0: .word 0xFFFF3801
_0222B6E4: .word 0xFFFF379D
_0222B6E8: .word 0xFFFF379A
_0222B6EC: .word 0xFFFF3799
_0222B6F0: .word 0xFFFF34E1
_0222B6F4: .word 0xFFFF34DE
_0222B6F8: .word 0xFFFF34DD
_0222B6FC: .word 0xFFFF347D
_0222B700: .word 0xFFFF3479
_0222B704: .word 0xFFFF3419
_0222B708: .word 0xFFFF3415
_0222B70C: .word 0xFFFF33B5
_0222B710: .word 0xFFFF3351
_0222B714: .word 0xFFFF30F9
_0222B718: .word 0xFFFF2FCD
_0222B71C: .word 0x0223F2C4
_0222B720: .word 0x0224307C
_0222B724: .word 0x0224025C
_0222B728: .word 0x0223F2D6
_0222B72C: .word 0x0223F2D4
_0222B730: .word 0x0223F2CC

	arm_func_start MOD13_0222B734
MOD13_0222B734: ; 0x0222B734
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222B7B4 ; =0x02240264
	ldr r1, _0222B7B8 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222B7BC ; =0x04001008
	ldr ip, _0222B7C0 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222B7C4 ; =0x04000008
	ldr r2, _0222B7C8 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222B7CC ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B7B4: .word 0x02240264
_0222B7B8: .word 0x020C908C
_0222B7BC: .word 0x04001008
_0222B7C0: .word 0x0400100A
_0222B7C4: .word 0x04000008
_0222B7C8: .word 0x0400000A
_0222B7CC: .word 0x0400000C

	arm_func_start MOD13_0222B7D0
MOD13_0222B7D0: ; 0x0222B7D0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222B734
	bl MOD13_0222B35C
	ldr r0, _0222B7F0 ; =MOD13_0222B320
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B7F0: .word MOD13_0222B320

	arm_func_start MOD13_0222B7F4
MOD13_0222B7F4: ; 0x0222B7F4
	ldr r1, _0222B800 ; =0x022430E8
	strb r0, [r1]
	bx lr
	.align 2, 0
_0222B800: .word 0x022430E8

	arm_func_start MOD13_0222B804
MOD13_0222B804: ; 0x0222B804
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222B82C ; =MOD13_0222DA24
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B82C: .word MOD13_0222DA24

	arm_func_start MOD13_0222B830
MOD13_0222B830: ; 0x0222B830
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _0222B874 ; =0x022430F4
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl MOD13_02232780
	ldr r0, _0222B878 ; =MOD13_0222B804
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222B874: .word 0x022430F4
_0222B878: .word MOD13_0222B804

	arm_func_start MOD13_0222B87C
MOD13_0222B87C: ; 0x0222B87C
	stmdb sp!, {r4, lr}
	bl MOD13_02234164
	mov r4, r0
	ldrb r0, [r4, #0x40]
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldrb r0, [r4, #0xf6]
	cmp r0, #0
	bne _0222B8C8
	add r0, r4, #0xc8
	bl FUN_02095AE0
	cmp r0, #0
	bne _0222B8C8
	add r0, r4, #0xcc
	bl FUN_02095AE0
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
_0222B8C8:
	ldrb r0, [r4, #0xf5]
	cmp r0, #0
	bne _0222B914
	add r0, r4, #0xc0
	bl FUN_02095AE0
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	add r0, r4, #0xc4
	bl FUN_02095AE0
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	add r0, r4, #0xc0
	add r1, r4, #0xf0
	bl FUN_02095B0C
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
_0222B914:
	mov r0, #1
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0222B91C
MOD13_0222B91C: ; 0x0222B91C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _0222B9D0 ; =0x0223F2F0
	ldr r0, _0222B9D4 ; =0x022430E4
	ldrb ip, [r1]
	ldrb r3, [r1, #1]
	ldrb r2, [r1, #2]
	ldrb r1, [r1, #3]
	strb ip, [sp]
	ldrb lr, [r0]
	add r4, sp, #0
	strb r3, [sp, #1]
	strb r2, [sp, #2]
	strb r1, [sp, #3]
	mov ip, #0
_0222B958:
	ldrb r0, [r4]
	cmp lr, r0
	bne _0222B9B8
	ldr r0, _0222B9D8 ; =0x022430F4
	mov r3, #0x14
	ldr r2, [r0]
	ands r1, ip, #1
	add r1, r2, ip
	strb r3, [r1, #4]
	beq _0222B99C
	ldr r1, [r0]
	sub r0, ip, #1
	add r0, r1, r0
	mov r1, #0
	strb r1, [r0, #4]
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222B99C:
	ldr r1, [r0]
	add r0, ip, #1
	add r0, r1, r0
	mov r1, #0
	strb r1, [r0, #4]
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222B9B8:
	add ip, ip, #1
	cmp ip, #4
	add r4, r4, #1
	blt _0222B958
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222B9D0: .word 0x0223F2F0
_0222B9D4: .word 0x022430E4
_0222B9D8: .word 0x022430F4

	arm_func_start MOD13_0222B9DC
MOD13_0222B9DC: ; 0x0222B9DC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r5, _0222BA34 ; =0x022430F4
	mov r4, #0
_0222B9EC:
	ldr r0, [r5]
	add r1, r0, r4
	ldrb r0, [r1, #4]
	cmp r0, #0
	beq _0222BA20
	sub r0, r0, #1
	strb r0, [r1, #4]
	ldr r0, [r5]
	add r0, r0, r4
	ldrb r0, [r0, #4]
	cmp r0, #0
	bne _0222BA20
	bl MOD13_0222CD8C
_0222BA20:
	add r4, r4, #1
	cmp r4, #4
	blt _0222B9EC
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0222BA34: .word 0x022430F4

	arm_func_start MOD13_0222BA38
MOD13_0222BA38: ; 0x0222BA38
	ldr r1, _0222BA64 ; =0x022430E4
	ldr r0, _0222BA68 ; =0x022430F4
	ldrb r2, [r1]
	ldr r0, [r0]
	ldr r1, _0222BA6C ; =0x0223F2EC
	sub r2, r2, #0xb
	ldrb r1, [r1, r2]
	ldr ip, _0222BA70 ; =MOD13_022327DC
	ldr r0, [r0, #0x10]
	mov r2, r1
	bx ip
	.align 2, 0
_0222BA64: .word 0x022430E4
_0222BA68: .word 0x022430F4
_0222BA6C: .word 0x0223F2EC
_0222BA70: .word MOD13_022327DC

	arm_func_start MOD13_0222BA74
MOD13_0222BA74: ; 0x0222BA74
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl MOD13_02234164
	ldr r1, _0222BDA0 ; =0x022430E4
	mov r4, #0
	ldrb r2, [r1]
	cmp r2, #8
	bne _0222BABC
	ldrb r0, [r0, #0xf5]
	cmp r0, #0
	bne _0222BABC
	cmp r5, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	cmp r5, #2
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
_0222BABC:
	cmp r2, #0
	bgt _0222BAD0
	cmp r2, #0
	beq _0222BAF0
	b _0222BC78
_0222BAD0:
	sub r0, r2, #0xa
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _0222BC78
_0222BAE0: ; jump table
	b _0222BB20 ; case 0
	b _0222BB5C ; case 1
	b _0222BBD4 ; case 2
	b _0222BBD4 ; case 3
_0222BAF0:
	cmp r5, #1
	ldreq r0, _0222BDA0 ; =0x022430E4
	moveq r1, #0xb
	streqb r1, [r0]
	beq _0222BD74
	cmp r5, #3
	ldreq r0, _0222BDA4 ; =0x022430EC
	movne r4, #2
	ldreqb r1, [r0]
	addeq r1, r1, #1
	streqb r1, [r0]
	b _0222BD74
_0222BB20:
	cmp r5, #1
	ldreq r0, _0222BDA4 ; =0x022430EC
	ldreqb r1, [r0]
	subeq r1, r1, #1
	streqb r1, [r0]
	beq _0222BD74
	cmp r5, #3
	movne r4, #2
	bne _0222BD74
	ldr r1, _0222BDA8 ; =0x022430F4
	ldr r0, _0222BDA0 ; =0x022430E4
	ldr r1, [r1]
	ldrb r1, [r1, #0x42]
	strb r1, [r0]
	b _0222BD74
_0222BB5C:
	cmp r5, #1
	bne _0222BB9C
	ldr r0, _0222BDA8 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x47]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222BDA8 ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x47]
	ldmia sp!, {r4, r5, pc}
_0222BB9C:
	cmp r5, #3
	movne r4, #2
	bne _0222BD74
	ldr r2, _0222BDA0 ; =0x022430E4
	mov r3, #0
	ldr r1, _0222BDA4 ; =0x022430EC
	ldr r0, _0222BDAC ; =0x022430F0
	strb r3, [r2]
	strb r3, [r1]
	strh r3, [r0]
	bl MOD13_0222CD8C
	mov r0, #0
	bl MOD13_02232F44
	b _0222BD74
_0222BBD4:
	ldr r0, _0222BDA8 ; =0x022430F4
	cmp r5, #1
	ldr r1, [r0]
	strb r2, [r1, #0x42]
	bne _0222BC1C
	ldr r2, _0222BDA0 ; =0x022430E4
	mov ip, #0xa
	ldr r1, _0222BDA4 ; =0x022430EC
	mov r5, #3
	ldr r0, _0222BDAC ; =0x022430F0
	mov r3, #0x91
	strb ip, [r2]
	strb r5, [r1]
	strh r3, [r0]
	bl MOD13_0222CD8C
	mov r0, #0x37
	bl MOD13_02232F44
	b _0222BD74
_0222BC1C:
	cmp r5, #3
	bne _0222BC58
	ldr r0, [r0]
	ldrb r0, [r0, #0x47]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222BDA8 ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x47]
	ldmia sp!, {r4, r5, pc}
_0222BC58:
	cmp r2, #0xc
	ldreq r0, _0222BDA0 ; =0x022430E4
	moveq r1, #0xd
	streqb r1, [r0]
	ldrne r0, _0222BDA0 ; =0x022430E4
	movne r1, #0xc
	strneb r1, [r0]
	b _0222BD74
_0222BC78:
	cmp r5, #1
	bne _0222BCC8
	ldr r0, _0222BDA4 ; =0x022430EC
	ldrb r1, [r0]
	cmp r1, #0
	subne r1, r1, #1
	strneb r1, [r0]
	bne _0222BD74
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _0222BDB0 ; =MOD13_0222C0E8
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222BDA8 ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {r4, r5, pc}
_0222BCC8:
	cmp r5, #3
	bne _0222BD18
	ldr r0, _0222BDA4 ; =0x022430EC
	ldrb r1, [r0]
	cmp r1, #3
	addlo r1, r1, #1
	strlob r1, [r0]
	blo _0222BD74
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _0222BDB4 ; =MOD13_0222C03C
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222BDA8 ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {r4, r5, pc}
_0222BD18:
	cmp r2, #2
	ldreq r0, _0222BDA0 ; =0x022430E4
	moveq r1, #3
	mov r4, #2
	streqb r1, [r0]
	beq _0222BD68
	cmp r2, #3
	ldreq r0, _0222BDA0 ; =0x022430E4
	streqb r4, [r0]
	beq _0222BD68
	cmp r2, #7
	ldreq r0, _0222BDA0 ; =0x022430E4
	moveq r1, #8
	streqb r1, [r0]
	beq _0222BD68
	cmp r2, #8
	bne _0222BD74
	ldr r0, _0222BDA0 ; =0x022430E4
	mov r1, #7
	strb r1, [r0]
_0222BD68:
	mov r0, #8
	bl MOD13_0223424C
	bl MOD13_0222BEC0
_0222BD74:
	cmp r4, #2
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	mov r0, #8
	bl MOD13_0223424C
	cmp r4, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	bl MOD13_0222BDF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0222BDA0: .word 0x022430E4
_0222BDA4: .word 0x022430EC
_0222BDA8: .word 0x022430F4
_0222BDAC: .word 0x022430F0
_0222BDB0: .word MOD13_0222C0E8
_0222BDB4: .word MOD13_0222C03C

	arm_func_start MOD13_0222BDB8
MOD13_0222BDB8: ; 0x0222BDB8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0222BDE8 ; =0x022430E4
	ldr r2, _0222BDEC ; =0x0223F32C
	strb r0, [r1]
	ldrb r0, [r2, r0]
	bl MOD13_0222C1F4
	ldr r1, _0222BDF0 ; =0x022430EC
	strb r0, [r1]
	bl MOD13_0222BEC0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222BDE8: .word 0x022430E4
_0222BDEC: .word 0x0223F32C
_0222BDF0: .word 0x022430EC

	arm_func_start MOD13_0222BDF4
MOD13_0222BDF4: ; 0x0222BDF4
	stmdb sp!, {r4, lr}
	ldr r0, _0222BEB0 ; =0x022430E4
	ldrb r0, [r0]
	add r0, r0, #0xf5
	and r0, r0, #0xff
	cmp r0, #2
	bhi _0222BE18
	bl MOD13_0222BEC0
	ldmia sp!, {r4, pc}
_0222BE18:
	bl MOD13_02234164
	ldr r1, _0222BEB4 ; =0x022430F0
	mov r4, r0
	ldrh r0, [r1]
	mov r1, #0x1d
	bl FX_DivS32
	ldr r1, _0222BEB8 ; =0x022430EC
	ldrb r1, [r1]
	add r2, r1, r0
	cmp r2, #2
	beq _0222BE50
	cmp r2, #6
	beq _0222BE74
	b _0222BE98
_0222BE50:
	ldrb r0, [r4, #0xf5]
	cmp r0, #0
	ldrne r0, _0222BEB0 ; =0x022430E4
	movne r1, #2
	strneb r1, [r0]
	ldreq r0, _0222BEB0 ; =0x022430E4
	moveq r1, #3
	streqb r1, [r0]
	b _0222BEA8
_0222BE74:
	ldrb r0, [r4, #0xf6]
	cmp r0, #0
	ldrne r0, _0222BEB0 ; =0x022430E4
	movne r1, #7
	strneb r1, [r0]
	ldreq r0, _0222BEB0 ; =0x022430E4
	moveq r1, #8
	streqb r1, [r0]
	b _0222BEA8
_0222BE98:
	ldr r1, _0222BEBC ; =0x0223F314
	ldr r0, _0222BEB0 ; =0x022430E4
	ldrb r1, [r1, r2]
	strb r1, [r0]
_0222BEA8:
	bl MOD13_0222BEC0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222BEB0: .word 0x022430E4
_0222BEB4: .word 0x022430F0
_0222BEB8: .word 0x022430EC
_0222BEBC: .word 0x0223F314

	arm_func_start MOD13_0222BEC0
MOD13_0222BEC0: ; 0x0222BEC0
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr ip, _0222BF90 ; =0x0223F338
	add r3, sp, #8
	mov r2, #7
_0222BED4:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _0222BED4
	ldr r0, _0222BF94 ; =0x022430E4
	add r1, sp, #8
	ldrb r0, [r0]
	ldrb r2, [r1, r0]
	cmp r2, #3
	blt _0222BF30
	mov r3, r2, lsl #3
	ldr r1, _0222BF98 ; =0x0223F3CC
	ldr r2, _0222BF9C ; =0x0223F3D0
	ldr r0, _0222BFA0 ; =0x0223F3CE
	ldrh r1, [r1, r3]
	ldrh r2, [r2, r3]
	ldrh r3, [r0, r3]
	mov r0, #3
	bl MOD13_0221F348
	add sp, sp, #0x1c
	ldmia sp!, {pc}
_0222BF30:
	ldr r0, _0222BF98 ; =0x0223F3CC
	mov r1, r2, lsl #3
	add lr, r0, r2, lsl #3
	ldrh ip, [r0, r1]
	ldrh r1, [lr, #2]
	ldr r0, _0222BFA4 ; =0x022430EC
	ldrh r3, [lr, #4]
	strh r1, [sp, #2]
	ldrh r2, [sp, #2]
	ldrb r1, [r0]
	mov r0, #0x1d
	strh ip, [sp]
	mla r0, r1, r0, r2
	strh r3, [sp, #4]
	strh r0, [sp, #2]
	ldrh ip, [lr, #6]
	ldrh r1, [sp]
	ldrh r2, [sp, #4]
	ldrh r3, [sp, #2]
	mov r0, #1
	strh ip, [sp, #6]
	bl MOD13_0221F348
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.align 2, 0
_0222BF90: .word 0x0223F338
_0222BF94: .word 0x022430E4
_0222BF98: .word 0x0223F3CC
_0222BF9C: .word 0x0223F3D0
_0222BFA0: .word 0x0223F3CE
_0222BFA4: .word 0x022430EC

	arm_func_start MOD13_0222BFA8
MOD13_0222BFA8: ; 0x0222BFA8
	stmdb sp!, {r4, lr}
	ldr r0, _0222C024 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x44]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, _0222C028 ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_DivS32
	ldr r1, _0222C028 ; =0x022430F0
	mov r4, r0
	ldrh r0, [r1]
	mov r1, #0x1d
	bl FX_ModS32
	ldr r1, _0222C02C ; =0x01FF0000
	sub ip, r0, #0x33
	ldr r2, _0222C030 ; =0x04000010
	and r3, r1, ip, lsl #16
	ldr r0, _0222C034 ; =0x0223F320
	str r3, [r2]
	ldrb r3, [r0, r4]
	ldr r2, _0222C038 ; =0x04000018
	ldr r0, _0222C024 ; =0x022430F4
	add r3, ip, r3
	and r1, r1, r3, lsl #16
	str r1, [r2]
	ldr r0, [r0]
	mov r1, #0
	strb r1, [r0, #0x44]
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222C024: .word 0x022430F4
_0222C028: .word 0x022430F0
_0222C02C: .word 0x01FF0000
_0222C030: .word 0x04000010
_0222C034: .word 0x0223F320
_0222C038: .word 0x04000018

	arm_func_start MOD13_0222C03C
MOD13_0222C03C: ; 0x0222C03C
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_02232F14
	bl MOD13_0221F21C
	ldr r0, _0222C0DC ; =0x022430F0
	mov r1, #0x1d
	ldrh r2, [r0]
	add r2, r2, #6
	strh r2, [r0]
	ldrh r0, [r0]
	bl FX_ModS32
	cmp r0, #6
	blt _0222C078
	bl MOD13_0222C4C8
	ldmia sp!, {r4, pc}
_0222C078:
	ldr r1, _0222C0DC ; =0x022430F0
	ldrh r2, [r1]
	sub r0, r2, r0
	strh r0, [r1]
	bl MOD13_0222CD8C
	ldr r1, _0222C0DC ; =0x022430F0
	mov r0, #0x37
	ldrh r1, [r1]
	ldr r2, _0222C0E0 ; =0xE1FC780F
	mul r3, r1, r0
	smull r1, r0, r2, r3
	add r0, r3, r0
	mov r0, r0, asr #7
	mov r1, r3, lsr #0x1f
	add r0, r1, r0
	bl MOD13_02232F44
	bl MOD13_02232F2C
	bl MOD13_0222BDF4
	ldr r0, _0222C0E4 ; =0x022430F4
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0
	str r0, [r2, #0x38]
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222C0DC: .word 0x022430F0
_0222C0E0: .word 0xE1FC780F
_0222C0E4: .word 0x022430F4

	arm_func_start MOD13_0222C0E8
MOD13_0222C0E8: ; 0x0222C0E8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r0
	bl MOD13_02232F14
	bl MOD13_0221F21C
	ldr r0, _0222C1C4 ; =0x022430F0
	ldrh r1, [r0]
	cmp r1, #6
	subhi r1, r1, #6
	strhih r1, [r0]
	movls r1, #0
	strlsh r1, [r0]
	ldr r0, _0222C1C4 ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_ModS32
	mov r5, r0
	cmp r5, #0x17
	bne _0222C140
	bl MOD13_0222CD8C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0222C140:
	cmp r5, #0x17
	ble _0222C160
	ldr r0, _0222C1C4 ; =0x022430F0
	rsb r1, r5, #0x1d
	ldrh r2, [r0]
	mov r5, #0
	add r1, r2, r1
	strh r1, [r0]
_0222C160:
	bl MOD13_0222C4C8
	cmp r5, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r1, _0222C1C4 ; =0x022430F0
	mov r0, #0x37
	ldrh r1, [r1]
	ldr r2, _0222C1C8 ; =0xE1FC780F
	mul r3, r1, r0
	smull r1, r0, r2, r3
	add r0, r3, r0
	mov r0, r0, asr #7
	mov r1, r3, lsr #0x1f
	add r0, r1, r0
	bl MOD13_02232F44
	bl MOD13_02232F2C
	bl MOD13_0222BDF4
	ldr r0, _0222C1CC ; =0x022430F4
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0
	str r0, [r2, #0x38]
	bl MOD13_0223C110
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0222C1C4: .word 0x022430F0
_0222C1C8: .word 0xE1FC780F
_0222C1CC: .word 0x022430F4

	arm_func_start MOD13_0222C1D0
MOD13_0222C1D0: ; 0x0222C1D0
	stmdb sp!, {r4, lr}
	ldr r1, _0222C1F0 ; =0x022430F0
	mov r4, r0
	ldrh r0, [r1]
	mov r1, #0x1d
	bl FX_DivS32
	add r0, r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222C1F0: .word 0x022430F0

	arm_func_start MOD13_0222C1F4
MOD13_0222C1F4: ; 0x0222C1F4
	stmdb sp!, {r4, lr}
	ldr r1, _0222C234 ; =0x022430F0
	mov r4, r0
	ldrh r0, [r1]
	mov r1, #0x1d
	bl FX_DivS32
	mov r1, #0
_0222C210:
	cmp r0, r4
	moveq r0, r1
	ldmeqia sp!, {r4, pc}
	add r1, r1, #1
	cmp r1, #4
	add r0, r0, #1
	blt _0222C210
	mvn r0, #0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222C234: .word 0x022430F0

	arm_func_start MOD13_0222C238
MOD13_0222C238: ; 0x0222C238
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	ldr r0, _0222C4AC ; =0x0223F75C
	bl MOD13_0223B2B4
	cmp r0, #0
	addeq sp, sp, #8
	moveq r0, #0xe
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, _0222C4B0 ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_DivS32
	ldr r1, _0222C4B4 ; =0x0223F2FC
	add r4, sp, #0
	ldrh ip, [r1]
	ldrh r3, [r1, #2]
	ldrh r2, [r1, #4]
	ldrh r1, [r1, #6]
	mov r5, r0
	strh ip, [sp]
	strh r3, [sp, #2]
	strh r2, [sp, #4]
	strh r1, [sp, #6]
	mov r6, #0
_0222C298:
	cmp r5, #2
	beq _0222C2C4
	cmp r5, #6
	beq _0222C2C4
	mov r0, r4
	bl MOD13_0223B194
	cmp r0, #0
	ldrne r0, _0222C4B8 ; =0x0223F314
	addne sp, sp, #8
	ldrneb r0, [r0, r5]
	ldmneia sp!, {r4, r5, r6, pc}
_0222C2C4:
	ldrh r0, [sp, #2]
	add r6, r6, #1
	cmp r6, #4
	add r0, r0, #0x1d
	strh r0, [sp, #2]
	add r5, r5, #1
	blt _0222C298
	ldr r0, _0222C4B0 ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_DivS32
	mov r3, #0
_0222C2F4:
	cmp r0, #2
	bne _0222C398
	ldr r1, _0222C4BC ; =0x0223F30C
	mov r0, #0x1d
	ldrh r2, [r1, #2]
	mul r4, r3, r0
	strh r2, [sp, #2]
	ldrh r5, [r1]
	ldrh r3, [r1, #4]
	ldrh r2, [r1, #6]
	ldrh r0, [sp, #2]
	strh r5, [sp]
	strh r3, [sp, #4]
	add r1, r0, r4
	add r0, sp, #0
	strh r2, [sp, #6]
	strh r1, [sp, #2]
	bl MOD13_0223B194
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #2
	ldmneia sp!, {r4, r5, r6, pc}
	ldr r1, _0222C4C0 ; =0x0223F304
	add r0, sp, #0
	ldrh r2, [r1, #2]
	ldrh ip, [r1]
	ldrh r5, [r1, #4]
	strh r2, [sp, #2]
	ldrh r3, [r1, #6]
	ldrh r2, [sp, #2]
	strh ip, [sp]
	strh r5, [sp, #4]
	add r1, r2, r4
	strh r3, [sp, #6]
	strh r1, [sp, #2]
	bl MOD13_0223B194
	cmp r0, #0
	beq _0222C3A8
	add sp, sp, #8
	mov r0, #3
	ldmia sp!, {r4, r5, r6, pc}
_0222C398:
	add r3, r3, #1
	cmp r3, #4
	add r0, r0, #1
	blt _0222C2F4
_0222C3A8:
	ldr r0, _0222C4B0 ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_DivS32
	mov r3, #0
_0222C3BC:
	cmp r0, #6
	bne _0222C460
	ldr r1, _0222C4BC ; =0x0223F30C
	mov r0, #0x1d
	ldrh r2, [r1, #2]
	mul r4, r3, r0
	strh r2, [sp, #2]
	ldrh r5, [r1]
	ldrh r3, [r1, #4]
	ldrh r2, [r1, #6]
	ldrh r0, [sp, #2]
	strh r5, [sp]
	strh r3, [sp, #4]
	add r1, r0, r4
	add r0, sp, #0
	strh r2, [sp, #6]
	strh r1, [sp, #2]
	bl MOD13_0223B194
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #7
	ldmneia sp!, {r4, r5, r6, pc}
	ldr r1, _0222C4C0 ; =0x0223F304
	add r0, sp, #0
	ldrh r2, [r1, #2]
	ldrh ip, [r1]
	ldrh r5, [r1, #4]
	strh r2, [sp, #2]
	ldrh r3, [r1, #6]
	ldrh r2, [sp, #2]
	strh ip, [sp]
	strh r5, [sp, #4]
	add r1, r2, r4
	strh r3, [sp, #6]
	strh r1, [sp, #2]
	bl MOD13_0223B194
	cmp r0, #0
	beq _0222C470
	add sp, sp, #8
	mov r0, #8
	ldmia sp!, {r4, r5, r6, pc}
_0222C460:
	add r3, r3, #1
	cmp r3, #4
	add r0, r0, #1
	blt _0222C3BC
_0222C470:
	ldr r5, _0222C4C4 ; =0x0223F3B4
	mov r4, #0
_0222C478:
	mov r0, r5
	bl MOD13_0223B2B4
	cmp r0, #0
	addne sp, sp, #8
	addne r0, r4, #0xb
	ldmneia sp!, {r4, r5, r6, pc}
	add r4, r4, #1
	cmp r4, #3
	add r5, r5, #8
	blt _0222C478
	mov r0, #0xe
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222C4AC: .word 0x0223F75C
_0222C4B0: .word 0x022430F0
_0222C4B4: .word 0x0223F2FC
_0222C4B8: .word 0x0223F314
_0222C4BC: .word 0x0223F30C
_0222C4C0: .word 0x0223F304
_0222C4C4: .word 0x0223F3B4

	arm_func_start MOD13_0222C4C8
MOD13_0222C4C8: ; 0x0222C4C8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #8
	ldr r0, _0222C6EC ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_DivS32
	ldr r1, _0222C6EC ; =0x022430F0
	mov r4, r0
	ldrh r0, [r1]
	mov r1, #0x1d
	bl FX_ModS32
	ldr r1, _0222C6F0 ; =0x022430F4
	rsb ip, r0, #0x34
	ldr r1, [r1]
	ldr r0, [r1, #0x34]
	cmp r0, #0
	beq _0222C54C
	cmp r4, #0
	moveq r0, #0x26
	streq r0, [sp]
	movne r0, #0x100
	strne r0, [sp]
	ldr r5, [r1, #0x34]
	ldr r1, _0222C6F4 ; =0xFE00FF00
	ldr r2, [r5]
	ldr r3, [sp]
	ldr r0, _0222C6F8 ; =0x000001FF
	and r2, r2, r1
	and r1, ip, #0xff
	and r3, r3, r0
	orr r0, r2, r1
	orr r0, r0, r3, lsl #16
	str r0, [r5]
_0222C54C:
	mov r3, ip
	mov r2, #0
	ldr r7, _0222C6F0 ; =0x022430F4
	ldr lr, _0222C6FC ; =0x01FF0000
	ldr r5, _0222C6F8 ; =0x000001FF
	ldr r6, _0222C6F4 ; =0xFE00FF00
_0222C564:
	ldr r0, [r7]
	and r8, r3, #0xff
	add r1, r0, r2, lsl #2
	ldr r0, [r1, #0x18]
	add r2, r2, #1
	ldr sb, [r0]
	cmp r2, #5
	and sl, sb, lr
	mov sb, sl, lsr #0x10
	str sb, [sp]
	ldr sb, [r0]
	and r0, r5, sl, lsr #16
	and sb, sb, #0xff
	str sb, [sp, #4]
	ldr r1, [r1, #0x18]
	add r3, r3, #0x1d
	ldr sb, [r1]
	and sb, sb, r6
	orr r8, sb, r8
	orr r0, r8, r0, lsl #16
	str r0, [r1]
	blt _0222C564
	cmp r4, #2
	bgt _0222C624
	ldr r6, [r7]
	ldr r0, _0222C6FC ; =0x01FF0000
	ldr r5, [r6, #0x2c]
	rsb r2, r4, #2
	ldr r3, [r5]
	mov r1, #0x1d
	and r0, r3, r0
	mov r3, r0, lsr #0x10
	str r3, [sp]
	ldr r5, [r5]
	mla r3, r2, r1, ip
	and r1, r5, #0xff
	str r1, [sp, #4]
	ldr r6, [r6, #0x2c]
	ldr r1, _0222C6F8 ; =0x000001FF
	ldr r5, [r6]
	ldr r2, _0222C6F4 ; =0xFE00FF00
	and r3, r3, #0xff
	and r2, r5, r2
	and r1, r1, r0, lsr #16
	orr r0, r2, r3
	orr r0, r0, r1, lsl #16
	str r0, [r6]
	b _0222C640
_0222C624:
	ldr r1, [r7]
	ldr r0, _0222C6F4 ; =0xFE00FF00
	ldr r2, [r1, #0x2c]
	ldr r1, [r2]
	and r0, r1, r0
	orr r0, r0, #0x1000000
	str r0, [r2]
_0222C640:
	cmp r4, #2
	blt _0222C6B4
	cmp r4, #6
	bgt _0222C6B4
	ldr r0, _0222C6F0 ; =0x022430F4
	ldr r1, _0222C6FC ; =0x01FF0000
	ldr r0, [r0]
	rsb r3, r4, #6
	ldr r6, [r0, #0x30]
	mov r2, #0x1d
	ldr r4, [r6]
	mla r2, r3, r2, ip
	and r5, r4, r1
	mov r1, r5, lsr #0x10
	str r1, [sp]
	ldr r3, [r6]
	ldr r1, _0222C6F4 ; =0xFE00FF00
	and r3, r3, #0xff
	str r3, [sp, #4]
	ldr r4, [r0, #0x30]
	ldr r0, _0222C6F8 ; =0x000001FF
	ldr r3, [r4]
	and r2, r2, #0xff
	and r1, r3, r1
	and r3, r0, r5, lsr #16
	orr r0, r1, r2
	orr r0, r0, r3, lsl #16
	str r0, [r4]
	b _0222C6D4
_0222C6B4:
	ldr r1, _0222C6F0 ; =0x022430F4
	ldr r0, _0222C6F4 ; =0xFE00FF00
	ldr r1, [r1]
	ldr r2, [r1, #0x30]
	ldr r1, [r2]
	and r0, r1, r0
	orr r0, r0, #0x1000000
	str r0, [r2]
_0222C6D4:
	ldr r0, _0222C6F0 ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x44]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_0222C6EC: .word 0x022430F0
_0222C6F0: .word 0x022430F4
_0222C6F4: .word 0xFE00FF00
_0222C6F8: .word 0x000001FF
_0222C6FC: .word 0x01FF0000

	arm_func_start MOD13_0222C700
MOD13_0222C700: ; 0x0222C700
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x30
	mov ip, r0
	ldrb r2, [ip, #1]
	mov r4, r1
	add r0, sp, #0xc
	str r2, [sp]
	ldrb r3, [ip, #2]
	ldr r2, _0222C780 ; =0x02240278
	mov r1, #0x10
	str r3, [sp, #4]
	ldrb r3, [ip, #3]
	str r3, [sp, #8]
	ldrb r3, [ip]
	bl swprintf
	mov r2, #7
	mov r0, #0x1d
	mul r1, r4, r0
	str r2, [sp]
	add r0, sp, #0xc
	str r0, [sp, #4]
	mov r2, #1
	str r2, [sp, #8]
	ldr r0, _0222C784 ; =0x022430F4
	add r2, r1, #8
	ldr r0, [r0]
	mov r1, #0x5f
	ldr r0, [r0, #0x14]
	mov r3, #2
	bl MOD13_0223A528
	add sp, sp, #0x30
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222C780: .word 0x02240278
_0222C784: .word 0x022430F4

	arm_func_start MOD13_0222C788
MOD13_0222C788: ; 0x0222C788
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x30
	mov r6, r0
	mov r4, r1
	add r0, sp, #0xc
	mov r1, #0
	mov r2, #0x22
	bl MI_CpuFill8
	mov r0, r6
	mov r1, #0x20
	bl MOD13_0223BDA4
	mov r5, r0
	cmp r5, #0x10
	movle lr, r5
	movgt lr, #0x10
	cmp lr, #0
	mov ip, #0
	ble _0222C7FC
	ldr r2, _0222C8DC ; =0x0000E01D
	add r1, sp, #0xc
_0222C7D8:
	ldrb r3, [r6, ip]
	cmp r3, #0x20
	moveq r0, ip, lsl #1
	streqh r2, [r1, r0]
	movne r0, ip, lsl #1
	add ip, ip, #1
	strneh r3, [r1, r0]
	cmp ip, lr
	blt _0222C7D8
_0222C7FC:
	mov r0, #0x1d
	mul r0, r4, r0
	mov r1, #8
	add r4, r0, #2
	str r1, [sp]
	add r0, sp, #0xc
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	ldr r0, _0222C8E0 ; =0x022430F4
	cmp r5, #0x10
	ldr r0, [r0]
	addle r4, r4, #5
	ldr r0, [r0, #0x14]
	mov r2, r4
	mov r1, #0x48
	mov r3, #2
	bl MOD13_0223A528
	cmp r5, #0x10
	addle sp, sp, #0x30
	ldmleia sp!, {r4, r5, r6, pc}
	add r0, sp, #0xc
	mov r1, #0
	mov r2, #0x22
	bl MI_CpuFill8
	sub ip, r5, #0x10
	cmp ip, #0
	mov r5, #0
	ble _0222C8A0
	ldr r2, _0222C8DC ; =0x0000E01D
	add r1, sp, #0xc
_0222C878:
	add r0, r5, #0x10
	ldrb r3, [r6, r0]
	cmp r3, #0x20
	moveq r0, r5, lsl #1
	streqh r2, [r1, r0]
	movne r0, r5, lsl #1
	add r5, r5, #1
	strneh r3, [r1, r0]
	cmp r5, ip
	blt _0222C878
_0222C8A0:
	mov r1, #8
	str r1, [sp]
	add r0, sp, #0xc
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	ldr r0, _0222C8E0 ; =0x022430F4
	add r2, r4, #0xc
	ldr r0, [r0]
	mov r1, #0x48
	ldr r0, [r0, #0x14]
	mov r3, #2
	bl MOD13_0223A528
	add sp, sp, #0x30
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222C8DC: .word 0x0000E01D
_0222C8E0: .word 0x022430F4

	arm_func_start MOD13_0222C8E4
MOD13_0222C8E4: ; 0x0222C8E4
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	ldr r5, _0222C9EC ; =0x0223F2FC
	ldr r4, _0222C9F0 ; =0x0223F30C
	ldr r3, _0222C9F4 ; =0x0223F304
	ldrh ip, [r4]
	ldrh r4, [r3]
	ldr r3, _0222C9F8 ; =0x022430F4
	ldrh lr, [r5]
	ldr r3, [r3]
	mov r6, r0
	add r3, r3, #0x18
	sub r0, r6, #1
	mov r5, r1
	strh lr, [sp]
	strh ip, [sp, #2]
	strh ip, [sp, #4]
	strh r4, [sp, #6]
	strh r4, [sp, #8]
	cmp r0, #1
	add r4, r3, r2, lsl #2
	bhi _0222C960
	mov r0, r2
	bl MOD13_0222C1D0
	cmp r0, #2
	ldreq r0, _0222C9F8 ; =0x022430F4
	ldreq r0, [r0]
	addeq r4, r0, #0x2c
	ldrne r0, _0222C9F8 ; =0x022430F4
	ldrne r0, [r0]
	addne r4, r0, #0x30
_0222C960:
	ldr r1, _0222C9FC ; =0x0223F348
	mov r0, #3
	mla r0, r6, r0, r1
	ldrb r1, [r5, r0]
	cmp r1, #0
	beq _0222C9CC
	ldr r2, [r4]
	mov r0, #0
	bl MOD13_02239E8C
	ldr r5, [r4]
	add r0, sp, #0
	mov r1, r6, lsl #1
	ldrh r3, [r0, r1]
	ldr r0, _0222CA00 ; =0x000001FF
	ldr r2, [r5]
	ldr r1, _0222CA04 ; =0xFE00FF00
	and r3, r3, r0
	and r0, r2, r1
	orr r0, r0, r3, lsl #16
	str r0, [r5]
	ldr r1, [r4]
	add sp, sp, #0x10
	ldrh r0, [r1, #4]
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	ldmia sp!, {r4, r5, r6, pc}
_0222C9CC:
	ldr r2, [r4]
	ldr r0, _0222CA04 ; =0xFE00FF00
	ldr r1, [r2]
	and r0, r1, r0
	orr r0, r0, #0x1000000
	str r0, [r2]
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222C9EC: .word 0x0223F2FC
_0222C9F0: .word 0x0223F30C
_0222C9F4: .word 0x0223F304
_0222C9F8: .word 0x022430F4
_0222C9FC: .word 0x0223F348
_0222CA00: .word 0x000001FF
_0222CA04: .word 0xFE00FF00

	arm_func_start MOD13_0222CA08
MOD13_0222CA08: ; 0x0222CA08
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_02234164
	cmp r4, #0xa
	mov r1, #1
	addls pc, pc, r4, lsl #2
	b _0222CA94
_0222CA24: ; jump table
	b _0222CA60 ; case 0
	b _0222CA60 ; case 1
	b _0222CA94 ; case 2
	b _0222CA94 ; case 3
	b _0222CA78 ; case 4
	b _0222CA78 ; case 5
	b _0222CA78 ; case 6
	b _0222CA50 ; case 7
	b _0222CA94 ; case 8
	b _0222CA88 ; case 9
	b _0222CA88 ; case 10
_0222CA50:
	ldrb r0, [r0, #0xf5]
	cmp r0, #0
	moveq r1, #0
	b _0222CA94
_0222CA60:
	ldrb r0, [r0, #0xe7]
	add r0, r0, #0xff
	and r0, r0, #0xff
	cmp r0, #1
	movls r1, #0
	b _0222CA94
_0222CA78:
	ldrb r0, [r0, #0xf5]
	cmp r0, #0
	movne r1, #0
	b _0222CA94
_0222CA88:
	ldrb r0, [r0, #0xf6]
	cmp r0, #0
	movne r1, #0
_0222CA94:
	mov r0, r1
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0222CA9C
MOD13_0222CA9C: ; 0x0222CA9C
	stmdb sp!, {r4, r5, r6, lr}
	mov r4, r0
	mov r6, r1
	bl MOD13_02234164
	cmp r4, #8
	addls pc, pc, r4, lsl #2
	b _0222CBD0
_0222CAB8: ; jump table
	b _0222CADC ; case 0
	b _0222CADC ; case 1
	b _0222CAF8 ; case 2
	b _0222CB44 ; case 3
	b _0222CB44 ; case 4
	b _0222CB44 ; case 5
	b _0222CB5C ; case 6
	b _0222CBB8 ; case 7
	b _0222CBB8 ; case 8
_0222CADC:
	mov r5, #0
	mov r0, r5
	mov r4, r5
	bl MOD13_0222CA08
	cmp r0, #0
	moveq r4, #2
	b _0222CBD8
_0222CAF8:
	ldr r2, _0222CBEC ; =0x022430F4
	ldrb r0, [r0, #0xf5]
	ldr r3, [r2]
	mov r1, #0
	ldrb r2, [r3, #4]
	cmp r0, #0
	movne r5, #1
	movne r0, #4
	moveq r5, #2
	moveq r0, #3
	cmp r2, #0
	mov r4, r1
	ldrb r2, [r3, #5]
	movne r4, #1
	cmp r2, #0
	movne r1, #1
	mov r2, r6
	bl MOD13_0222C8E4
	b _0222CBD8
_0222CB44:
	ldrb r0, [r0, #0xf5]
	mov r5, #0
	cmp r0, #0
	movne r4, #2
	moveq r4, r5
	b _0222CBD8
_0222CB5C:
	ldrb r2, [r0, #0xf6]
	mov r1, #0
	mov r4, r1
	cmp r2, #0
	movne r5, #1
	movne r0, #4
	bne _0222CB8C
	ldrb r0, [r0, #0xf5]
	mov r5, #2
	cmp r0, #0
	moveq r4, #2
	mov r0, #3
_0222CB8C:
	ldr r2, _0222CBEC ; =0x022430F4
	ldr r3, [r2]
	ldrb r2, [r3, #6]
	cmp r2, #0
	ldrb r2, [r3, #7]
	movne r4, #1
	cmp r2, #0
	movne r1, #1
	mov r2, r6
	bl MOD13_0222C8E4
	b _0222CBD8
_0222CBB8:
	ldrb r0, [r0, #0xf6]
	mov r5, #0
	cmp r0, #0
	movne r4, #2
	moveq r4, r5
	b _0222CBD8
_0222CBD0:
	mov r5, #0
	mov r4, #2
_0222CBD8:
	mov r0, r5
	mov r1, r4
	mov r2, r6
	bl MOD13_0222C8E4
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222CBEC: .word 0x022430F4

	arm_func_start MOD13_0222CBF0
MOD13_0222CBF0: ; 0x0222CBF0
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x28
	mov r6, r0
	mov r5, r1
	bl MOD13_02234164
	cmp r6, #8
	addls pc, pc, r6, lsl #2
	b _0222CD84
_0222CC10: ; jump table
	b _0222CC34 ; case 0
	b _0222CC48 ; case 1
	b _0222CD84 ; case 2
	b _0222CCD8 ; case 3
	b _0222CCFC ; case 4
	b _0222CD20 ; case 5
	b _0222CD84 ; case 6
	b _0222CD44 ; case 7
	b _0222CD68 ; case 8
_0222CC34:
	mov r1, r5
	add r0, r0, #0x40
	bl MOD13_0222C788
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CC48:
	ldrb r1, [r0, #0xe6]
	mov r1, r1, lsl #0x1e
	mov r1, r1, lsr #0x1e
	cmp r1, #3
	addls pc, pc, r1, lsl #2
	b _0222CC8C
_0222CC60: ; jump table
	b _0222CC70 ; case 0
	b _0222CC78 ; case 1
	b _0222CC80 ; case 2
	b _0222CC88 ; case 3
_0222CC70:
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CC78:
	mov r4, #0xa
	b _0222CC8C
_0222CC80:
	mov r4, #0x1a
	b _0222CC8C
_0222CC88:
	mov r4, #0x20
_0222CC8C:
	ldrb r0, [r0, #0xe6]
	mov r1, #0
	mov r2, #0x21
	mov r0, r0, lsl #0x18
	mov r0, r0, lsr #0x1a
	cmp r0, #1
	addeq r0, r4, r4, lsr #31
	moveq r4, r0, asr #1
	add r0, sp, #0
	bl MI_CpuFill8
	add r0, sp, #0
	mov r2, r4
	mov r1, #0x2a
	bl Call_FillMemWithValue
	add r0, sp, #0
	mov r1, r5
	bl MOD13_0222C788
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CCD8:
	ldrb r1, [r0, #0xf5]
	cmp r1, #0
	addne sp, sp, #0x28
	ldmneia sp!, {r4, r5, r6, pc}
	mov r1, r5
	add r0, r0, #0xc0
	bl MOD13_0222C700
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CCFC:
	ldrb r1, [r0, #0xf5]
	cmp r1, #0
	addne sp, sp, #0x28
	ldmneia sp!, {r4, r5, r6, pc}
	mov r1, r5
	add r0, r0, #0xf0
	bl MOD13_0222C700
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CD20:
	ldrb r1, [r0, #0xf5]
	cmp r1, #0
	addne sp, sp, #0x28
	ldmneia sp!, {r4, r5, r6, pc}
	mov r1, r5
	add r0, r0, #0xc4
	bl MOD13_0222C700
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CD44:
	ldrb r1, [r0, #0xf6]
	cmp r1, #0
	addne sp, sp, #0x28
	ldmneia sp!, {r4, r5, r6, pc}
	mov r1, r5
	add r0, r0, #0xc8
	bl MOD13_0222C700
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
_0222CD68:
	ldrb r1, [r0, #0xf6]
	cmp r1, #0
	addne sp, sp, #0x28
	ldmneia sp!, {r4, r5, r6, pc}
	mov r1, r5
	add r0, r0, #0xcc
	bl MOD13_0222C700
_0222CD84:
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}

	arm_func_start MOD13_0222CD8C
MOD13_0222CD8C: ; 0x0222CD8C
	stmdb sp!, {r4, r5, r6, lr}
	ldr r0, _0222CE44 ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_DivS32
	ldr r1, _0222CE48 ; =0x022430F4
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0
	ldr r0, [r0, #0x14]
	bl MOD13_0223A4D8
	mov r6, r4
	mov r5, #0
_0222CDC0:
	mov r0, r6
	mov r1, r5
	bl MOD13_0222CBF0
	add r5, r5, #1
	cmp r5, #5
	add r6, r6, #1
	blt _0222CDC0
	ldr r0, _0222CE48 ; =0x022430F4
	ldr r1, _0222CE4C ; =0x0223F358
	mov r2, r4, lsl #1
	ldr r3, [r0]
	ldrh r0, [r1, r2]
	ldr r2, [r3, #8]
	mov r1, #0
	add r0, r2, r0, lsl #1
	mov r2, #0x1e
	mov r3, #0x13
	bl MOD13_02232878
	mov r5, #0
_0222CE0C:
	mov r0, r4
	mov r1, r5
	bl MOD13_0222CA9C
	add r5, r5, #1
	cmp r5, #5
	add r4, r4, #1
	blt _0222CE0C
	bl MOD13_022328D0
	ldr r0, _0222CE48 ; =0x022430F4
	ldr r0, [r0]
	ldr r0, [r0, #0x14]
	bl MOD13_0223A410
	bl MOD13_0222C4C8
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0222CE44: .word 0x022430F0
_0222CE48: .word 0x022430F4
_0222CE4C: .word 0x0223F358

	arm_func_start MOD13_0222CE50
MOD13_0222CE50: ; 0x0222CE50
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r1, _0222D130 ; =0x022430F4
	mov r0, #0
	ldr r1, [r1]
	ldr r1, [r1]
	bl MOD13_0223C104
	ldr r1, _0222D130 ; =0x022430F4
	mov r0, #1
	ldr r1, [r1]
	ldr r1, [r1, #0x3c]
	bl MOD13_0223C104
	mov r5, #0
	ldr r4, _0222D130 ; =0x022430F4
_0222CEB0:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x18]
	bl MOD13_0223B974
	add r5, r5, #1
	cmp r5, #7
	blt _0222CEB0
	ldr r0, _0222D130 ; =0x022430F4
	ldr r0, [r0]
	ldr r0, [r0, #0x34]
	cmp r0, #0
	beq _0222CEE4
	bl MOD13_0223B974
_0222CEE4:
	bl MOD13_02232F78
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221F21C
	ldr r0, _0222D130 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x40]
	cmp r0, #0xc
	beq _0222CF0C
	bl MOD13_0221EE54
_0222CF0C:
	bl MOD13_022328E8
	ldr r0, _0222D130 ; =0x022430F4
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl MOD13_0223939C
	mov r5, #0
	ldr r4, _0222D130 ; =0x022430F4
_0222CF28:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xc]
	bl MOD13_0223939C
	add r5, r5, #1
	cmp r5, #2
	blt _0222CF28
	ldr r0, _0222D134 ; =0x02240298
	ldr r1, _0222D138 ; =0x020C9480
	bl MOD13_0221F174
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x1d
	bl MOD13_0223AE98
	ldr r2, _0222D13C ; =0x04000010
	mov r1, #0
	ldr r0, _0222D140 ; =0x04000018
	str r1, [r2]
	str r1, [r0]
	ldr r3, _0222D144 ; =0x0400000C
	ldr r0, _0222D130 ; =0x022430F4
	ldrh r2, [r3]
	and r2, r2, #0x43
	orr r2, r2, #0xe10
	strh r2, [r3]
	ldr r0, [r0]
	ldrb r0, [r0, #0x40]
	cmp r0, #0xd
	addls pc, pc, r0, lsl #2
	b _0222D120
_0222CFA8: ; jump table
	b _0222CFE0 ; case 0
	b _0222CFE0 ; case 1
	b _0222D120 ; case 2
	b _0222D120 ; case 3
	b _0222CFFC ; case 4
	b _0222CFFC ; case 5
	b _0222CFFC ; case 6
	b _0222D120 ; case 7
	b _0222D120 ; case 8
	b _0222CFFC ; case 9
	b _0222CFFC ; case 10
	b _0222D02C ; case 11
	b _0222D0C4 ; case 12
	b _0222D0D8 ; case 13
_0222CFE0:
	bl MOD13_02222F6C
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	ldr r0, _0222D148 ; =MOD13_0222A190
	bl MOD13_02222FBC
	b _0222D120
_0222CFFC:
	sub r4, r0, #4
	cmp r0, #9
	subhs r4, r4, #2
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	mov r0, r4
	mov r1, #0
	bl MOD13_02222F6C
	ldr r0, _0222D14C ; =MOD13_0222AF48
	bl MOD13_02222FBC
	b _0222D120
_0222D02C:
	bl MOD13_02234164
	mov r4, r0
	add r0, r4, #0xf0
	bl FUN_02095BE0
	strb r0, [r4, #0xd0]
	ldrb r0, [r4, #0xf5]
	cmp r0, #0
	beq _0222D084
	add r0, r4, #0xc0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	add r0, r4, #0xc4
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	add r0, r4, #0xf0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r0, #0
	strb r0, [r4, #0xd0]
_0222D084:
	ldrb r0, [r4, #0xf6]
	cmp r0, #0
	beq _0222D0A0
	add r0, r4, #0xc8
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
_0222D0A0:
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, r0
	bl MOD13_02222F6C
	ldr r0, _0222D150 ; =MOD13_022313C8
	bl MOD13_02222FBC
	b _0222D120
_0222D0C4:
	mov r0, r1
	bl MOD13_02222FA8
	ldr r0, _0222D154 ; =MOD13_0222E1B0
	bl MOD13_02222FBC
	b _0222D120
_0222D0D8:
	ldr r0, _0222D158 ; =0x022430E8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222D100
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222D15C ; =MOD13_02230714
	bl MOD13_02222FBC
	b _0222D120
_0222D100:
	bl MOD13_02234164
	ldrb r0, [r0, #0xf4]
	bl MOD13_02233C24
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222D160 ; =MOD13_02230EC4
	bl MOD13_02222FBC
_0222D120:
	ldr r0, _0222D130 ; =0x022430F4
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0222D130: .word 0x022430F4
_0222D134: .word 0x02240298
_0222D138: .word 0x020C9480
_0222D13C: .word 0x04000010
_0222D140: .word 0x04000018
_0222D144: .word 0x0400000C
_0222D148: .word MOD13_0222A190
_0222D14C: .word MOD13_0222AF48
_0222D150: .word MOD13_022313C8
_0222D154: .word MOD13_0222E1B0
_0222D158: .word 0x022430E8
_0222D15C: .word MOD13_02230714
_0222D160: .word MOD13_02230EC4

	arm_func_start MOD13_0222D164
MOD13_0222D164: ; 0x0222D164
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x1d
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222D1B8 ; =MOD13_0222CE50
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222D1B8: .word MOD13_0222CE50

	arm_func_start MOD13_0222D1BC
MOD13_0222D1BC: ; 0x0222D1BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02232F14
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222D1E0 ; =MOD13_0222D164
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222D1E0: .word MOD13_0222D164

	arm_func_start MOD13_0222D1E4
MOD13_0222D1E4: ; 0x0222D1E4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222D484 ; =0x022430F4
	ldr r1, [r0]
	ldr r0, [r1, #0x38]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrb r0, [r1, #0x41]
	cmp r0, #0
	subne r0, r0, #1
	strneb r0, [r1, #0x41]
	bl MOD13_02232F50
	cmp r0, #7
	addls pc, pc, r0, lsl #2
	b _0222D47C
_0222D224: ; jump table
	b _0222D47C ; case 0
	b _0222D244 ; case 1
	b _0222D25C ; case 2
	b _0222D2BC ; case 3
	b _0222D37C ; case 4
	b _0222D46C ; case 5
	b _0222D3F4 ; case 6
	b _0222D46C ; case 7
_0222D244:
	ldr r0, _0222D484 ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x45]
	ldmia sp!, {pc}
_0222D25C:
	ldr r0, _0222D484 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x41]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221F21C
	bl MOD13_02232F64
	mov r1, #0x91
	mul r1, r0, r1
	ldr r2, _0222D488 ; =0x094F2095
	mov r0, r1, lsr #0x1f
	smull r1, r3, r2, r1
	mov r3, r3, asr #1
	ldr r1, _0222D48C ; =0x022430F0
	add r3, r0, r3
	strh r3, [r1]
	bl MOD13_0222CD8C
	ldr r0, _0222D484 ; =0x022430F4
	mov r1, #4
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x41]
	ldmia sp!, {pc}
_0222D2BC:
	ldr r0, _0222D484 ; =0x022430F4
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x45]
	bl MOD13_02232F64
	mov r1, #0x91
	mul r1, r0, r1
	ldr r2, _0222D488 ; =0x094F2095
	mov r0, r1, lsr #0x1f
	smull r1, r3, r2, r1
	mov r3, r3, asr #1
	ldr r1, _0222D48C ; =0x022430F0
	add r3, r0, r3
	mov r0, #0x13
	strh r3, [r1]
	bl MOD13_0223424C
	bl MOD13_0222CD8C
	ldr r0, _0222D48C ; =0x022430F0
	mov r1, #0x1d
	ldrh r0, [r0]
	bl FX_ModS32
	cmp r0, #0
	bne _0222D324
	bl MOD13_0222BDF4
	add sp, sp, #4
	ldmia sp!, {pc}
_0222D324:
	cmp r0, #0x10
	bge _0222D354
	mov r0, #0
	ldr r1, _0222D490 ; =MOD13_0222C0E8
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222D484 ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_0222D354:
	mov r0, #0
	ldr r1, _0222D494 ; =MOD13_0222C03C
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222D484 ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_0222D37C:
	ldr r0, _0222D48C ; =0x022430F0
	ldrh r0, [r0]
	cmp r0, #0
	bne _0222D3C4
	ldr r0, _0222D484 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x46]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222D484 ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x46]
	ldmia sp!, {pc}
_0222D3C4:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _0222D490 ; =MOD13_0222C0E8
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222D484 ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_0222D3F4:
	ldr r0, _0222D48C ; =0x022430F0
	ldrh r0, [r0]
	cmp r0, #0x91
	bne _0222D43C
	ldr r0, _0222D484 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x46]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222D484 ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x46]
	ldmia sp!, {pc}
_0222D43C:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _0222D494 ; =MOD13_0222C03C
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222D484 ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_0222D46C:
	ldr r0, _0222D484 ; =0x022430F4
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x46]
_0222D47C:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222D484: .word 0x022430F4
_0222D488: .word 0x094F2095
_0222D48C: .word 0x022430F0
_0222D490: .word MOD13_0222C0E8
_0222D494: .word MOD13_0222C03C

	arm_func_start MOD13_0222D498
MOD13_0222D498: ; 0x0222D498
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_02234164
	ldrb r0, [r0, #0xf6]
	cmp r0, r4
	ldmeqia sp!, {r4, pc}
	ldr r1, _0222D4CC ; =0x022430F4
	mov r0, r4
	ldr r1, [r1]
	strb r4, [r1, #0x43]
	bl MOD13_0223413C
	bl MOD13_0222CD8C
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222D4CC: .word 0x022430F4

	arm_func_start MOD13_0222D4D0
MOD13_0222D4D0: ; 0x0222D4D0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r0
	bl MOD13_02234164
	ldrb r1, [r0, #0xf5]
	cmp r1, r4
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	cmp r4, #0
	beq _0222D514
	ldr r0, _0222D544 ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x43]
	cmp r0, #0
	movne r5, #1
	moveq r5, #0
	b _0222D528
_0222D514:
	ldr r1, _0222D544 ; =0x022430F4
	ldrb r2, [r0, #0xf6]
	ldr r0, [r1]
	mov r5, #0
	strb r2, [r0, #0x43]
_0222D528:
	mov r0, r4
	bl MOD13_02234150
	mov r0, r5
	bl MOD13_0223413C
	bl MOD13_0222CD8C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0222D544: .word 0x022430F4

	arm_func_start MOD13_0222D548
MOD13_0222D548: ; 0x0222D548
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	bl MOD13_0222CA08
	cmp r0, #0
	bne _0222D570
	mov r0, #9
	bl MOD13_0223424C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222D570:
	cmp r4, #8
	addls pc, pc, r4, lsl #2
	b _0222D5E8
_0222D57C: ; jump table
	b _0222D5E8 ; case 0
	b _0222D5E8 ; case 1
	b _0222D5A0 ; case 2
	b _0222D5A0 ; case 3
	b _0222D5E8 ; case 4
	b _0222D5E8 ; case 5
	b _0222D5E8 ; case 6
	b _0222D5C4 ; case 7
	b _0222D5C4 ; case 8
_0222D5A0:
	mov r0, #6
	bl MOD13_0223424C
	sub r0, r4, #2
	eors r0, r0, #1
	movne r0, #1
	moveq r0, #0
	bl MOD13_0222D4D0
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222D5C4:
	mov r0, #6
	bl MOD13_0223424C
	sub r0, r4, #7
	eors r0, r0, #1
	movne r0, #1
	moveq r0, #0
	bl MOD13_0222D498
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222D5E8:
	ldr r0, _0222D6B8 ; =0x022430F4
	sub r1, r4, #0xb
	ldr r0, [r0]
	cmp r1, #1
	strb r4, [r0, #0x40]
	bhi _0222D664
	bl MOD13_0222BA38
	bl MOD13_0222B87C
	cmp r0, #0
	bne _0222D644
	mov r0, #9
	bl MOD13_0223424C
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #6
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	ldr r0, _0222D6BC ; =MOD13_0222B830
	bl MOD13_02222FBC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0222D644:
	cmp r4, #0xb
	bne _0222D658
	mov r0, #6
	bl MOD13_0223424C
	b _0222D6A4
_0222D658:
	mov r0, #0xe
	bl MOD13_0223424C
	b _0222D6A4
_0222D664:
	cmp r4, #0xd
	bne _0222D67C
	bl MOD13_0222BA38
	mov r0, #7
	bl MOD13_0223424C
	b _0222D6A4
_0222D67C:
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _0222D6C0 ; =0x0223F32C
	ldrb r0, [r0, r4]
	bl MOD13_0222C1F4
	mov r2, r0
	mov r0, #0
	mov r1, #1
	bl MOD13_0222C8E4
	bl MOD13_0222C4C8
_0222D6A4:
	bl MOD13_02232F14
	ldr r0, _0222D6C4 ; =MOD13_0222D1BC
	bl MOD13_02222FBC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222D6B8: .word 0x022430F4
_0222D6BC: .word MOD13_0222B830
_0222D6C0: .word 0x0223F32C
_0222D6C4: .word MOD13_0222D1BC

	arm_func_start MOD13_0222D6C8
MOD13_0222D6C8: ; 0x0222D6C8
	stmdb sp!, {r4, lr}
	bl MOD13_02234164
	bl MOD13_0222C238
	mov r4, r0
	cmp r4, #0xe
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	bl MOD13_0222CA08
	cmp r0, #0
	bne _0222D700
	mov r0, #9
	bl MOD13_0223424C
	mov r0, #1
	ldmia sp!, {r4, pc}
_0222D700:
	mov r0, r4
	bl MOD13_0222BDB8
	cmp r4, #8
	addls pc, pc, r4, lsl #2
	b _0222D73C
_0222D714: ; jump table
	b _0222D73C ; case 0
	b _0222D73C ; case 1
	b _0222D738 ; case 2
	b _0222D738 ; case 3
	b _0222D73C ; case 4
	b _0222D73C ; case 5
	b _0222D73C ; case 6
	b _0222D738 ; case 7
	b _0222D738 ; case 8
_0222D738:
	bl MOD13_0222B91C
_0222D73C:
	mov r0, r4
	bl MOD13_0222D548
	mov r0, #1
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0222D74C
MOD13_0222D74C: ; 0x0222D74C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222DA0C ; =0x022430F4
	ldr r1, [r0]
	ldr r0, [r1, #0x38]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrb r0, [r1, #0x45]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0222D6C8
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222D7B0
	ldr r0, _0222DA10 ; =0x022430E4
	ldrb r0, [r0]
	bl MOD13_0222D548
	add sp, sp, #4
	ldmia sp!, {pc}
_0222D7B0:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222D7E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r1, _0222DA0C ; =0x022430F4
	ldr r0, _0222DA14 ; =MOD13_0222D1BC
	ldr r1, [r1]
	mov r2, #0xd
	strb r2, [r1, #0x40]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222D7E8:
	mov r0, #0x200
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222D870
	ldr r0, _0222DA18 ; =0x022430F0
	ldrh r0, [r0]
	cmp r0, #0x91
	bne _0222D840
	ldr r0, _0222DA0C ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x47]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222DA0C ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x47]
	ldmia sp!, {pc}
_0222D840:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _0222DA1C ; =MOD13_0222C03C
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222DA0C ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_0222D870:
	mov r0, #0x200
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _0222DA0C ; =0x022430F4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x47]
	ldmneia sp!, {pc}
	mov r0, #0x100
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222D91C
	ldr r0, _0222DA18 ; =0x022430F0
	ldrh r0, [r0]
	cmp r0, #0
	bne _0222D8EC
	ldr r0, _0222DA0C ; =0x022430F4
	ldr r0, [r0]
	ldrb r0, [r0, #0x47]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _0222DA0C ; =0x022430F4
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x47]
	ldmia sp!, {pc}
_0222D8EC:
	mov r0, #0x13
	bl MOD13_0223424C
	mov r0, #0
	ldr r1, _0222DA20 ; =MOD13_0222C0E8
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0222DA0C ; =0x022430F4
	add sp, sp, #4
	ldr r1, [r1]
	str r0, [r1, #0x38]
	ldmia sp!, {pc}
_0222D91C:
	mov r0, #0x100
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _0222DA0C ; =0x022430F4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x47]
	ldmneia sp!, {pc}
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222D960
	mov r0, #1
	bl MOD13_0222BA74
	add sp, sp, #4
	ldmia sp!, {pc}
_0222D960:
	mov r0, #0x40
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _0222DA0C ; =0x022430F4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x47]
	ldmneia sp!, {pc}
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222D9A4
	mov r0, #3
	bl MOD13_0222BA74
	add sp, sp, #4
	ldmia sp!, {pc}
_0222D9A4:
	mov r0, #0x80
	bl MOD13_0223B38C
	cmp r0, #0
	ldrne r0, _0222DA0C ; =0x022430F4
	movne r1, #0
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0x47]
	ldmneia sp!, {pc}
	mov r0, #0x20
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0222D9E8
	mov r0, #0
	bl MOD13_0222BA74
	add sp, sp, #4
	ldmia sp!, {pc}
_0222D9E8:
	mov r0, #0x10
	bl MOD13_0223B3B0
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #2
	bl MOD13_0222BA74
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222DA0C: .word 0x022430F4
_0222DA10: .word 0x022430E4
_0222DA14: .word MOD13_0222D1BC
_0222DA18: .word 0x022430F0
_0222DA1C: .word MOD13_0222C03C
_0222DA20: .word MOD13_0222C0E8

	arm_func_start MOD13_0222DA24
MOD13_0222DA24: ; 0x0222DA24
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222D74C
	bl MOD13_0222D1E4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222DA7C ; =MOD13_0222DA24
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222DA7C: .word MOD13_0222DA24

	arm_func_start MOD13_0222DA80
MOD13_0222DA80: ; 0x0222DA80
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x1d
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x1d
	bl MOD13_0223AEF4
	ldr r0, _0222DAD8 ; =0x0222DA3C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222DAD8: .word 0x0222DA3C

	arm_func_start MOD13_0222DADC
MOD13_0222DADC: ; 0x0222DADC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02234164
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r2, _0222DB28 ; =0x022430F0
	mov r3, #0
	ldr r1, _0222DB2C ; =0x022430E4
	ldr r0, _0222DB30 ; =0x022430EC
	strh r3, [r2]
	strb r3, [r1]
	strb r3, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222DB28: .word 0x022430F0
_0222DB2C: .word 0x022430E4
_0222DB30: .word 0x022430EC

	arm_func_start MOD13_0222DB34
MOD13_0222DB34: ; 0x0222DB34
	stmdb sp!, {lr}
	sub sp, sp, #0x44
	ldr r3, _0222DCFC ; =0x0223F39C
	add ip, sp, #0
	mov r2, #0xb
_0222DB48:
	ldrb r1, [r3], #1
	ldrb r0, [r3], #1
	subs r2, r2, #1
	strb r1, [ip], #1
	strb r0, [ip], #1
	bne _0222DB48
	ldrb r0, [r3]
	ldr r3, _0222DD00 ; =0x0223F36C
	add lr, sp, #0x17
	strb r0, [ip]
	mov r2, #0xa
_0222DB74:
	ldrb r1, [r3], #1
	ldrb r0, [r3], #1
	subs r2, r2, #1
	strb r1, [lr], #1
	strb r0, [lr], #1
	bne _0222DB74
	ldrb r0, [r3]
	ldr ip, _0222DD04 ; =0x0223F384
	add r3, sp, #0x2c
	strb r0, [lr]
	mov r2, #0xb
_0222DBA0:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _0222DBA0
	ldr ip, _0222DD08 ; =0x0400000C
	ldr r2, _0222DD0C ; =0x00000E18
	ldrh r3, [ip]
	ldr r0, _0222DD10 ; =0x022402B0
	ldr r1, _0222DD14 ; =0x020C9480
	and r3, r3, #0x43
	orr r2, r3, r2
	strh r2, [ip]
	bl MOD13_0221F174
	ldr r0, _0222DD18 ; =0x022402C4
	ldr r1, _0222DD1C ; =0x020C8C7C
	bl MOD13_0221F174
	ldr r0, _0222DD20 ; =0x022402DC
	ldr r1, _0222DD24 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r1, _0222DD28 ; =0x020C9550
	add r0, sp, #0x17
	bl MOD13_0221F174
	ldr r0, _0222DD2C ; =0x022402F4
	ldr r1, _0222DD30 ; =0x020C8FBC
	bl MOD13_0221F174
	add r0, sp, #0
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _0222DD34 ; =0x022430F4
	ldr r2, [r1]
	str r0, [r2, #8]
	ldr r0, [r1]
	ldr r0, [r0, #8]
	bl MOD13_02232918
	bl MOD13_022328D0
	add r0, sp, #0x17
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _0222DD34 ; =0x022430F4
	ldr r1, [r1]
	str r0, [r1, #0xc]
	add r0, sp, #0x2c
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _0222DD34 ; =0x022430F4
	ldr r2, _0222DD38 ; =0x04001008
	ldr r3, [r1]
	ldr r1, _0222DD3C ; =0x0400100A
	str r0, [r3, #0x10]
	ldrh r0, [r2]
	ldr ip, _0222DD40 ; =0x04000008
	ldr r3, _0222DD44 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	ldr r2, _0222DD08 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222DD48 ; =0x0400000E
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #2
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #2
	strh r0, [r1]
	add sp, sp, #0x44
	ldmia sp!, {pc}
	.align 2, 0
_0222DCFC: .word 0x0223F39C
_0222DD00: .word 0x0223F36C
_0222DD04: .word 0x0223F384
_0222DD08: .word 0x0400000C
_0222DD0C: .word 0x00000E18
_0222DD10: .word 0x022402B0
_0222DD14: .word 0x020C9480
_0222DD18: .word 0x022402C4
_0222DD1C: .word 0x020C8C7C
_0222DD20: .word 0x022402DC
_0222DD24: .word 0x020C8D4C
_0222DD28: .word 0x020C9550
_0222DD2C: .word 0x022402F4
_0222DD30: .word 0x020C8FBC
_0222DD34: .word 0x022430F4
_0222DD38: .word 0x04001008
_0222DD3C: .word 0x0400100A
_0222DD40: .word 0x04000008
_0222DD44: .word 0x0400000A
_0222DD48: .word 0x0400000E

	arm_func_start MOD13_0222DD4C
MOD13_0222DD4C: ; 0x0222DD4C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	bl MOD13_02234164
	mov r5, r0
	mov r0, #0x48
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, _0222DF38 ; =0x022430F4
	mov r2, #0xc
	str r0, [r1]
	ldrb r3, [r5, #0xf6]
	strb r3, [r0, #0x43]
	ldr r0, [r1]
	strb r2, [r0, #0x42]
	bl MOD13_0222DADC
	bl MOD13_0222DB34
	ldr r0, _0222DF3C ; =0x022430E8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222DDBC
	bl MOD13_02222F34
	ldr r1, _0222DF40 ; =0x0223F2F4
	ldrb r2, [r5, #0xf4]
	ldrsb r1, [r1, r0]
	mov r0, #0x30
	add r2, r2, #1
	bl MOD13_0221EE98
	b _0222DDCC
_0222DDBC:
	mov r0, #0x45
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
_0222DDCC:
	mov r0, #1
	bl MOD13_0221F124
	bl MOD13_0221F48C
	ldr r0, _0222DF44 ; =0x022430F0
	mov r1, #0x37
	ldrh r3, [r0]
	ldr r2, _0222DF48 ; =0xE1FC780F
	mov r0, #2
	mul r4, r3, r1
	smull r1, r3, r2, r4
	add r3, r4, r3
	mov r3, r3, asr #7
	mov r1, r4, lsr #0x1f
	add r3, r1, r3
	str r3, [sp]
	mov r1, #0x55
	mov r2, #0xf1
	mov r3, #0x41
	bl MOD13_02232FB8
	mov r0, #0
	mov r1, #1
	bl MOD13_0223A7F0
	ldr r6, _0222DF38 ; =0x022430F4
	mov r4, #0
	ldr r2, [r6]
	ldr r1, _0222DF4C ; =0x0223F348
	str r0, [r2, #0x14]
	ldrb r8, [r1, #1]
	mov r7, r4
_0222DE40:
	mov r0, r7
	mov r1, r8
	bl MOD13_02239E54
	ldr r1, [r6]
	add r1, r1, r4, lsl #2
	add r4, r4, #1
	str r0, [r1, #0x18]
	cmp r4, #7
	blt _0222DE40
	ldrb r0, [r5, #0xe7]
	cmp r0, #1
	beq _0222DE7C
	cmp r0, #2
	beq _0222DEB0
	b _0222DEE0
_0222DE7C:
	mov r0, #0
	mov r1, #0x50
	bl MOD13_02239E54
	ldr r1, _0222DF38 ; =0x022430F4
	ldr r2, [r1]
	str r0, [r2, #0x34]
	ldr r0, [r1]
	ldr r1, [r0, #0x34]
	ldrh r0, [r1, #4]
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
	b _0222DEE0
_0222DEB0:
	mov r0, #0
	mov r1, #0x51
	bl MOD13_02239E54
	ldr r1, _0222DF38 ; =0x022430F4
	ldr r2, [r1]
	str r0, [r2, #0x34]
	ldr r0, [r1]
	ldr r1, [r0, #0x34]
	ldrh r0, [r1, #4]
	bic r0, r0, #0xc00
	orr r0, r0, #0xc00
	strh r0, [r1, #4]
_0222DEE0:
	ldr r1, _0222DF50 ; =MOD13_0222BFA8
	mov r0, #1
	mov r2, #0
	mov r3, #0x6e
	bl MOD13_0223C1C4
	ldr r2, _0222DF38 ; =0x022430F4
	ldr r1, _0222DF54 ; =MOD13_0222B9DC
	ldr r2, [r2]
	mov r3, #0x78
	str r0, [r2, #0x3c]
	mov r0, #0
	mov r2, r0
	bl MOD13_0223C1C4
	ldr r1, _0222DF38 ; =0x022430F4
	ldr r1, [r1]
	str r0, [r1]
	bl MOD13_0222CD8C
	bl MOD13_0222BEC0
	ldr r0, _0222DF58 ; =MOD13_0222DA80
	bl MOD13_02222FBC
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0222DF38: .word 0x022430F4
_0222DF3C: .word 0x022430E8
_0222DF40: .word 0x0223F2F4
_0222DF44: .word 0x022430F0
_0222DF48: .word 0xE1FC780F
_0222DF4C: .word 0x0223F348
_0222DF50: .word MOD13_0222BFA8
_0222DF54: .word MOD13_0222B9DC
_0222DF58: .word MOD13_0222DA80

	arm_func_start MOD13_0222DF5C
MOD13_0222DF5C: ; 0x0222DF5C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AE98
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222DFC4 ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222DFC4: .word MOD13_02230714

	arm_func_start MOD13_0222DFC8
MOD13_0222DFC8: ; 0x0222DFC8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222E008 ; =MOD13_0222DF5C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E008: .word MOD13_0222DF5C

	arm_func_start MOD13_0222E00C
MOD13_0222E00C: ; 0x0222E00C
	bx lr

	arm_func_start MOD13_0222E010
MOD13_0222E010: ; 0x0222E010
	bx lr

	arm_func_start MOD13_0222E014
MOD13_0222E014: ; 0x0222E014
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222E010
	bl MOD13_0222E00C
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222E044 ; =MOD13_0222DFC8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E044: .word MOD13_0222DFC8

	arm_func_start MOD13_0222E048
MOD13_0222E048: ; 0x0222E048
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov ip, #0
	mov r0, #0x44
	mov r1, #5
	mov r2, #1
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	ldr r0, _0222E0A4 ; =MOD13_0222E014
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E0A4: .word MOD13_0222E014

	arm_func_start MOD13_0222E0A8
MOD13_0222E0A8: ; 0x0222E0A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AEF4
	ldr r0, _0222E100 ; =MOD13_0222E048
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E100: .word MOD13_0222E048

	arm_func_start MOD13_0222E104
MOD13_0222E104: ; 0x0222E104
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222E188 ; =0x02240308
	ldr r1, _0222E18C ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _0222E190 ; =0x02240320
	ldr r1, _0222E194 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _0222E198 ; =0x02240338
	ldr r1, _0222E19C ; =0x020C908C
	bl MOD13_0221F174
	ldr ip, _0222E1A0 ; =0x04001008
	ldr r3, _0222E1A4 ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _0222E1A8 ; =0x0400000A
	ldr r1, _0222E1AC ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E188: .word 0x02240308
_0222E18C: .word 0x020C8D4C
_0222E190: .word 0x02240320
_0222E194: .word 0x020C9550
_0222E198: .word 0x02240338
_0222E19C: .word 0x020C908C
_0222E1A0: .word 0x04001008
_0222E1A4: .word 0x0400100A
_0222E1A8: .word 0x0400000A
_0222E1AC: .word 0x0400000C

	arm_func_start MOD13_0222E1B0
MOD13_0222E1B0: ; 0x0222E1B0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222E104
	bl MOD13_0221F4AC
	bl MOD13_02233B3C
	ldr r0, _0222E1D4 ; =MOD13_0222E0A8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E1D4: .word MOD13_0222E0A8

	arm_func_start MOD13_0222E1D8
MOD13_0222E1D8: ; 0x0222E1D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222E200 ; =MOD13_0222E430
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E200: .word MOD13_0222E430

	arm_func_start MOD13_0222E204
MOD13_0222E204: ; 0x0222E204
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _0222E238 ; =MOD13_0222E1D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E238: .word MOD13_0222E1D8

	arm_func_start MOD13_0222E23C
MOD13_0222E23C: ; 0x0222E23C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02223B24
	cmp r0, #2
	beq _0222E260
	cmp r0, #4
	beq _0222E27C
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E260:
	ldr r1, _0222E2C4 ; =0x022430F8
	mov r2, #1
	ldr r0, _0222E2C8 ; =MOD13_0222E430
	strb r2, [r1]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E27C:
	ldr r0, _0222E2C4 ; =0x022430F8
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #9
	bl MOD13_0223424C
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xd
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _0222E2CC ; =MOD13_0222E204
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E2C4: .word 0x022430F8
_0222E2C8: .word MOD13_0222E430
_0222E2CC: .word MOD13_0222E204

	arm_func_start MOD13_0222E2D0
MOD13_0222E2D0: ; 0x0222E2D0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222E3A4 ; =0x022430F8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E310
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_0222E310:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _0222E3A4 ; =0x022430F8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E34C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_0222E34C:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _0222E3A4 ; =0x022430F8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E388
	bl MOD13_02223BE0
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222E3A8 ; =MOD13_02230EC4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E388:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _0222E3AC ; =MOD13_0222EB58
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E3A4: .word 0x022430F8
_0222E3A8: .word MOD13_02230EC4
_0222E3AC: .word MOD13_0222EB58

	arm_func_start MOD13_0222E3B0
MOD13_0222E3B0: ; 0x0222E3B0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222E428 ; =0x022430F8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E3E0
	bl MOD13_0221ED28
_0222E3E0:
	ldr r0, _0222E428 ; =0x022430F8
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E404
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_0222E404:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222E42C ; =MOD13_0222E2D0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E428: .word 0x022430F8
_0222E42C: .word MOD13_0222E2D0

	arm_func_start MOD13_0222E430
MOD13_0222E430: ; 0x0222E430
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222E454 ; =MOD13_0222E3B0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E454: .word MOD13_0222E3B0

	arm_func_start MOD13_0222E458
MOD13_0222E458: ; 0x0222E458
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _0222E48C ; =MOD13_0222E430
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E48C: .word MOD13_0222E430

	arm_func_start MOD13_0222E490
MOD13_0222E490: ; 0x0222E490
	bx lr

	arm_func_start MOD13_0222E494
MOD13_0222E494: ; 0x0222E494
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222E4BC
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E4BC:
	bl MOD13_0222E68C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0xa
	bl OS_Sleep
	bl MOD13_0222E23C
	bl MOD13_0222E494
	bl MOD13_0222E490
	bl MOD13_0222E458
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222E534 ; =0x0222E4DC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E534: .word 0x0222E4DC

	arm_func_start MOD13_0222E538
MOD13_0222E538: ; 0x0222E538
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl MOD13_0221F0EC
	ldr r0, _0222E56C ; =0x0222E504
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E56C: .word 0x0222E504

	arm_func_start MOD13_0222E570
MOD13_0222E570: ; 0x0222E570
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222E5A8 ; =MOD13_0222E538
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E5A8: .word MOD13_0222E538

	arm_func_start MOD13_0222E5AC
MOD13_0222E5AC: ; 0x0222E5AC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222E62C ; =0x0224034C
	ldr r1, _0222E630 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222E634 ; =0x04001008
	ldr ip, _0222E638 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222E63C ; =0x04000008
	ldr r2, _0222E640 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222E644 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E62C: .word 0x0224034C
_0222E630: .word 0x020C908C
_0222E634: .word 0x04001008
_0222E638: .word 0x0400100A
_0222E63C: .word 0x04000008
_0222E640: .word 0x0400000A
_0222E644: .word 0x0400000C

	arm_func_start MOD13_0222E648
MOD13_0222E648: ; 0x0222E648
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222E684 ; =0x022430F8
	mov r1, #0
	strb r1, [r0]
	bl MOD13_0222E5AC
	bl MOD13_0221F4AC
	mov r0, #0x25
	bl MOD13_0221F070
	mov r0, #1
	bl MOD13_0221E694
	ldr r0, _0222E688 ; =MOD13_0222E570
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E684: .word 0x022430F8
_0222E688: .word MOD13_0222E570

	arm_func_start MOD13_0222E68C
MOD13_0222E68C: ; 0x0222E68C
	ldr r0, _0222E6A8 ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_0222E6A8: .word 0x027FFFA8

	arm_func_start MOD13_0222E6AC
MOD13_0222E6AC: ; 0x0222E6AC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222E6D4 ; =MOD13_0222E940
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E6D4: .word MOD13_0222E940

	arm_func_start MOD13_0222E6D8
MOD13_0222E6D8: ; 0x0222E6D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _0222E70C ; =MOD13_0222E6AC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E70C: .word MOD13_0222E6AC

	arm_func_start MOD13_0222E710
MOD13_0222E710: ; 0x0222E710
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02223B24
	cmp r0, #3
	beq _0222E73C
	cmp r0, #4
	beq _0222E760
	cmp r0, #5
	beq _0222E7A8
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E73C:
	ldr r0, _0222E7F0 ; =0x022430FC
	mov r1, #1
	strb r1, [r0]
	bl MOD13_022341E8
	bl MOD13_02223AF8
	ldr r0, _0222E7F4 ; =MOD13_0222E940
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E760:
	ldr r0, _0222E7F0 ; =0x022430FC
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #9
	bl MOD13_0223424C
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xd
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _0222E7F8 ; =MOD13_0222E6D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E7A8:
	ldr r0, _0222E7F0 ; =0x022430FC
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #0x12
	bl MOD13_0223424C
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xe
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _0222E7F8 ; =MOD13_0222E6D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E7F0: .word 0x022430FC
_0222E7F4: .word MOD13_0222E940
_0222E7F8: .word MOD13_0222E6D8

	arm_func_start MOD13_0222E7FC
MOD13_0222E7FC: ; 0x0222E7FC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222E8C4 ; =0x022430FC
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E83C
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_0222E83C:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _0222E8C4 ; =0x022430FC
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E878
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_0222E878:
	bl MOD13_02223BE0
	ldr r0, _0222E8C4 ; =0x022430FC
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E8A8
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222E8C8 ; =MOD13_02230EC4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E8A8:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _0222E8CC ; =MOD13_0222EDE4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E8C4: .word 0x022430FC
_0222E8C8: .word MOD13_02230EC4
_0222E8CC: .word MOD13_0222EDE4

	arm_func_start MOD13_0222E8D0
MOD13_0222E8D0: ; 0x0222E8D0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _0222E938 ; =0x022430FC
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222E914
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_0222E914:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222E93C ; =MOD13_0222E7FC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E938: .word 0x022430FC
_0222E93C: .word MOD13_0222E7FC

	arm_func_start MOD13_0222E940
MOD13_0222E940: ; 0x0222E940
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222E964 ; =MOD13_0222E8D0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E964: .word MOD13_0222E8D0

	arm_func_start MOD13_0222E968
MOD13_0222E968: ; 0x0222E968
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _0222E99C ; =MOD13_0222E940
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222E99C: .word MOD13_0222E940

	arm_func_start MOD13_0222E9A0
MOD13_0222E9A0: ; 0x0222E9A0
	bx lr

	arm_func_start MOD13_0222E9A4
MOD13_0222E9A4: ; 0x0222E9A4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222E9CC
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
_0222E9CC:
	bl MOD13_0222EB9C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0xa
	bl OS_Sleep
	bl MOD13_0222E710
	bl MOD13_0222E9A4
	bl MOD13_0222E9A0
	bl MOD13_0222E968
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222EA44 ; =0x0222E9EC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EA44: .word 0x0222E9EC

	arm_func_start MOD13_0222EA48
MOD13_0222EA48: ; 0x0222EA48
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl MOD13_0221F0EC
	ldr r0, _0222EA7C ; =0x0222EA14
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EA7C: .word 0x0222EA14

	arm_func_start MOD13_0222EA80
MOD13_0222EA80: ; 0x0222EA80
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222EAB8 ; =MOD13_0222EA48
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EAB8: .word MOD13_0222EA48

	arm_func_start MOD13_0222EABC
MOD13_0222EABC: ; 0x0222EABC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222EB3C ; =0x02240360
	ldr r1, _0222EB40 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222EB44 ; =0x04001008
	ldr ip, _0222EB48 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222EB4C ; =0x04000008
	ldr r2, _0222EB50 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222EB54 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EB3C: .word 0x02240360
_0222EB40: .word 0x020C908C
_0222EB44: .word 0x04001008
_0222EB48: .word 0x0400100A
_0222EB4C: .word 0x04000008
_0222EB50: .word 0x0400000A
_0222EB54: .word 0x0400000C

	arm_func_start MOD13_0222EB58
MOD13_0222EB58: ; 0x0222EB58
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222EB94 ; =0x022430FC
	mov r1, #0
	strb r1, [r0]
	bl MOD13_0222EABC
	bl MOD13_0221F4AC
	mov r0, #0x2a
	bl MOD13_0221F070
	mov r0, #2
	bl MOD13_0221E694
	ldr r0, _0222EB98 ; =MOD13_0222EA80
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EB94: .word 0x022430FC
_0222EB98: .word MOD13_0222EA80

	arm_func_start MOD13_0222EB9C
MOD13_0222EB9C: ; 0x0222EB9C
	ldr r0, _0222EBB8 ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_0222EBB8: .word 0x027FFFA8

	arm_func_start MOD13_0222EBBC
MOD13_0222EBBC: ; 0x0222EBBC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222EBF4 ; =0x02243100
	ldrb r1, [r0]
	add r1, r1, #1
	strb r1, [r0]
	ldrb r0, [r0]
	cmp r0, #0x78
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	ldr r0, _0222EBF8 ; =MOD13_0222EC7C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EBF4: .word 0x02243100
_0222EBF8: .word MOD13_0222EC7C

	arm_func_start MOD13_0222EBFC
MOD13_0222EBFC: ; 0x0222EBFC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, #1
	bl MOD13_02222F6C
	ldr r0, _0222EC78 ; =MOD13_0223197C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EC78: .word MOD13_0223197C

	arm_func_start MOD13_0222EC7C
MOD13_0222EC7C: ; 0x0222EC7C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222ECBC ; =MOD13_0222EBFC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222ECBC: .word MOD13_0222EBFC

	arm_func_start MOD13_0222ECC0
MOD13_0222ECC0: ; 0x0222ECC0
	bx lr

	arm_func_start MOD13_0222ECC4
MOD13_0222ECC4: ; 0x0222ECC4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222EBBC
	bl MOD13_0222ECC0
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222ED08 ; =MOD13_0222ECC4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222ED08: .word MOD13_0222ECC4

	arm_func_start MOD13_0222ED0C
MOD13_0222ED0C: ; 0x0222ED0C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222ED44 ; =0x0222ECDC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222ED44: .word 0x0222ECDC

	arm_func_start MOD13_0222ED48
MOD13_0222ED48: ; 0x0222ED48
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222EDC8 ; =0x02240374
	ldr r1, _0222EDCC ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222EDD0 ; =0x04001008
	ldr ip, _0222EDD4 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222EDD8 ; =0x04000008
	ldr r2, _0222EDDC ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222EDE0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EDC8: .word 0x02240374
_0222EDCC: .word 0x020C908C
_0222EDD0: .word 0x04001008
_0222EDD4: .word 0x0400100A
_0222EDD8: .word 0x04000008
_0222EDDC: .word 0x0400000A
_0222EDE0: .word 0x0400000C

	arm_func_start MOD13_0222EDE4
MOD13_0222EDE4: ; 0x0222EDE4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222EE20 ; =0x02243100
	mov r1, #0
	strb r1, [r0]
	bl MOD13_0222ED48
	bl MOD13_0221F4AC
	mov r0, #0x26
	bl MOD13_0221F070
	mov r0, #0x10
	bl MOD13_0223424C
	ldr r0, _0222EE24 ; =MOD13_0222ED0C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EE20: .word 0x02243100
_0222EE24: .word MOD13_0222ED0C

	arm_func_start MOD13_0222EE28
MOD13_0222EE28: ; 0x0222EE28
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222EE50 ; =MOD13_0222F080
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EE50: .word MOD13_0222F080

	arm_func_start MOD13_0222EE54
MOD13_0222EE54: ; 0x0222EE54
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _0222EE88 ; =MOD13_0222EE28
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EE88: .word MOD13_0222EE28

	arm_func_start MOD13_0222EE8C
MOD13_0222EE8C: ; 0x0222EE8C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02223B24
	cmp r0, #1
	beq _0222EEB0
	cmp r0, #4
	beq _0222EECC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222EEB0:
	ldr r1, _0222EF14 ; =0x02243104
	mov r2, #1
	ldr r0, _0222EF18 ; =MOD13_0222F080
	strb r2, [r1]
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222EECC:
	ldr r0, _0222EF14 ; =0x02243104
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #9
	bl MOD13_0223424C
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xd
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _0222EF1C ; =MOD13_0222EE54
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EF14: .word 0x02243104
_0222EF18: .word MOD13_0222F080
_0222EF1C: .word MOD13_0222EE54

	arm_func_start MOD13_0222EF20
MOD13_0222EF20: ; 0x0222EF20
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222EFF4 ; =0x02243104
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222EF60
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_0222EF60:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _0222EFF4 ; =0x02243104
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222EF9C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_0222EF9C:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _0222EFF4 ; =0x02243104
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222EFD8
	bl MOD13_02223BE0
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222EFF8 ; =MOD13_02230EC4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222EFD8:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _0222EFFC ; =MOD13_0222E648
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222EFF4: .word 0x02243104
_0222EFF8: .word MOD13_02230EC4
_0222EFFC: .word MOD13_0222E648

	arm_func_start MOD13_0222F000
MOD13_0222F000: ; 0x0222F000
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222F078 ; =0x02243104
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222F030
	bl MOD13_0221ED28
_0222F030:
	ldr r0, _0222F078 ; =0x02243104
	ldrb r0, [r0]
	cmp r0, #0
	bne _0222F054
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_0222F054:
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222F07C ; =MOD13_0222EF20
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F078: .word 0x02243104
_0222F07C: .word MOD13_0222EF20

	arm_func_start MOD13_0222F080
MOD13_0222F080: ; 0x0222F080
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222F0A4 ; =MOD13_0222F000
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F0A4: .word MOD13_0222F000

	arm_func_start MOD13_0222F0A8
MOD13_0222F0A8: ; 0x0222F0A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _0222F0DC ; =MOD13_0222F080
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F0DC: .word MOD13_0222F080

	arm_func_start MOD13_0222F0E0
MOD13_0222F0E0: ; 0x0222F0E0
	bx lr

	arm_func_start MOD13_0222F0E4
MOD13_0222F0E4: ; 0x0222F0E4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0222F10C
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
_0222F10C:
	bl MOD13_0222F35C
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0xa
	bl OS_Sleep
	bl MOD13_0222EE8C
	bl MOD13_0222F0E4
	bl MOD13_0222F0E0
	bl MOD13_0222F0A8
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222F184 ; =0x0222F12C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F184: .word 0x0222F12C

	arm_func_start MOD13_0222F188
MOD13_0222F188: ; 0x0222F188
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02223C0C
	mov r0, #1
	bl MOD13_0221F0EC
	ldr r0, _0222F1D4 ; =0x0222F154
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F1D4: .word 0x0222F154

	arm_func_start MOD13_0222F1D8
MOD13_0222F1D8: ; 0x0222F1D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222F230 ; =MOD13_0222F188
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F230: .word MOD13_0222F188

	arm_func_start MOD13_0222F234
MOD13_0222F234: ; 0x0222F234
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222F2CC ; =0x02240388
	ldr r1, _0222F2D0 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _0222F2D4 ; =0x022403A0
	ldr r1, _0222F2D8 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _0222F2DC ; =0x022403B8
	ldr r1, _0222F2E0 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222F2E4 ; =0x04001008
	ldr ip, _0222F2E8 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222F2EC ; =0x04000008
	ldr r2, _0222F2F0 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222F2F4 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F2CC: .word 0x02240388
_0222F2D0: .word 0x020C8D4C
_0222F2D4: .word 0x022403A0
_0222F2D8: .word 0x020C9550
_0222F2DC: .word 0x022403B8
_0222F2E0: .word 0x020C908C
_0222F2E4: .word 0x04001008
_0222F2E8: .word 0x0400100A
_0222F2EC: .word 0x04000008
_0222F2F0: .word 0x0400000A
_0222F2F4: .word 0x0400000C

	arm_func_start MOD13_0222F2F8
MOD13_0222F2F8: ; 0x0222F2F8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222F354 ; =0x02243104
	mov r1, #0
	strb r1, [r0]
	bl MOD13_0222F234
	bl MOD13_0221F4AC
	mov r0, #0x37
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #2
	bl MOD13_0221F124
	mov r0, #0x24
	bl MOD13_0221F070
	mov r0, #0
	bl MOD13_0221E694
	mov r0, #0xb
	bl MOD13_0223424C
	ldr r0, _0222F358 ; =MOD13_0222F1D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F354: .word 0x02243104
_0222F358: .word MOD13_0222F1D8

	arm_func_start MOD13_0222F35C
MOD13_0222F35C: ; 0x0222F35C
	ldr r0, _0222F378 ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_0222F378: .word 0x027FFFA8

	arm_func_start MOD13_0222F37C
MOD13_0222F37C: ; 0x0222F37C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0222F3A4 ; =MOD13_0222F520
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F3A4: .word MOD13_0222F520

	arm_func_start MOD13_0222F3A8
MOD13_0222F3A8: ; 0x0222F3A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _0222F3DC ; =MOD13_0222F37C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F3DC: .word MOD13_0222F37C

	arm_func_start MOD13_0222F3E0
MOD13_0222F3E0: ; 0x0222F3E0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
_0222F420:
	bl MOD13_0223339C
	cmp r0, #0
	beq _0222F420
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _0222F4B8 ; =0x02243108
	ldrb r0, [r0]
	cmp r0, #1
	beq _0222F490
	bl MOD13_02233570
	bl MOD13_02234164
	ldrb r0, [r0, #0xf4]
	bl MOD13_02233C24
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _0222F4BC ; =MOD13_02230EC4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0222F490:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, r0
	bl MOD13_02222F6C
	ldr r0, _0222F4C0 ; =MOD13_022295D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F4B8: .word 0x02243108
_0222F4BC: .word MOD13_02230EC4
_0222F4C0: .word MOD13_022295D8

	arm_func_start MOD13_0222F4C4
MOD13_0222F4C4: ; 0x0222F4C4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _0222F51C ; =MOD13_0222F3E0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F51C: .word MOD13_0222F3E0

	arm_func_start MOD13_0222F520
MOD13_0222F520: ; 0x0222F520
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0222F544 ; =MOD13_0222F4C4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F544: .word MOD13_0222F4C4

	arm_func_start MOD13_0222F548
MOD13_0222F548: ; 0x0222F548
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _0222F57C ; =MOD13_0222F520
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F57C: .word MOD13_0222F520

	arm_func_start MOD13_0222F580
MOD13_0222F580: ; 0x0222F580
	bx lr

	arm_func_start MOD13_0222F584
MOD13_0222F584: ; 0x0222F584
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_022341E8
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0222F5B4
MOD13_0222F5B4: ; 0x0222F5B4
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _0222F6D0 ; =0x0224310C
	ldrh r1, [r0]
	add r1, r1, #1
	strh r1, [r0]
	ldrh r0, [r0]
	cmp r0, #0x12c
	addlo sp, sp, #0xc
	ldmloia sp!, {pc}
	bl MOD13_022341E8
	add r0, sp, #4
	bl MOD13_0223333C
	cmp r0, #0
	bne _0222F634
	ldr r0, _0222F6D4 ; =0x02243108
	mov r3, #2
	strb r3, [r0]
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xf
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	mov r0, #0x12
	bl MOD13_0223424C
	bl MOD13_0221EC84
	ldr r0, _0222F6D8 ; =MOD13_0222F3A8
	bl MOD13_02222FBC
	add sp, sp, #0xc
	ldmia sp!, {pc}
_0222F634:
	cmp r0, #0
	mov r3, #0
	ble _0222F660
	ldr r2, [sp, #4]
_0222F644:
	ldrb r1, [r2, #0x28]
	cmp r1, #2
	bne _0222F660
	add r3, r3, #1
	cmp r3, r0
	add r2, r2, #0x2a
	blt _0222F644
_0222F660:
	cmp r3, r0
	bne _0222F6AC
	ldr r0, _0222F6D4 ; =0x02243108
	mov r3, #3
	strb r3, [r0]
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0xe
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	mov r0, #0x12
	bl MOD13_0223424C
	bl MOD13_0221EC84
	ldr r0, _0222F6D8 ; =MOD13_0222F3A8
	bl MOD13_02222FBC
	add sp, sp, #0xc
	ldmia sp!, {pc}
_0222F6AC:
	ldr r1, _0222F6D4 ; =0x02243108
	mov r2, #1
	mov r0, #0xf
	strb r2, [r1]
	bl MOD13_0223424C
	ldr r0, _0222F6DC ; =MOD13_0222F520
	bl MOD13_02222FBC
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_0222F6D0: .word 0x0224310C
_0222F6D4: .word 0x02243108
_0222F6D8: .word MOD13_0222F3A8
_0222F6DC: .word MOD13_0222F520

	arm_func_start MOD13_0222F6E0
MOD13_0222F6E0: ; 0x0222F6E0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0222F584
	bl MOD13_0222F580
	bl MOD13_0222F548
	bl MOD13_0222F5B4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222F730 ; =MOD13_0222F6E0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F730: .word MOD13_0222F6E0

	arm_func_start MOD13_0222F734
MOD13_0222F734: ; 0x0222F734
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl MOD13_0221F0EC
	ldr r0, _0222F77C ; =0x0222F700
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F77C: .word 0x0222F700

	arm_func_start MOD13_0222F780
MOD13_0222F780: ; 0x0222F780
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0222F7D8 ; =MOD13_0222F734
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F7D8: .word MOD13_0222F734

	arm_func_start MOD13_0222F7DC
MOD13_0222F7DC: ; 0x0222F7DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222F874 ; =0x022403CC
	ldr r1, _0222F878 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _0222F87C ; =0x022403E4
	ldr r1, _0222F880 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _0222F884 ; =0x022403FC
	ldr r1, _0222F888 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _0222F88C ; =0x04001008
	ldr ip, _0222F890 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _0222F894 ; =0x04000008
	ldr r2, _0222F898 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _0222F89C ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F874: .word 0x022403CC
_0222F878: .word 0x020C8D4C
_0222F87C: .word 0x022403E4
_0222F880: .word 0x020C9550
_0222F884: .word 0x022403FC
_0222F888: .word 0x020C908C
_0222F88C: .word 0x04001008
_0222F890: .word 0x0400100A
_0222F894: .word 0x04000008
_0222F898: .word 0x0400000A
_0222F89C: .word 0x0400000C

	arm_func_start MOD13_0222F8A0
MOD13_0222F8A0: ; 0x0222F8A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0222F90C ; =0x0224310C
	mov r2, #0
	ldr r0, _0222F910 ; =0x02243108
	strh r2, [r1]
	strb r2, [r0]
	bl MOD13_0222F7DC
	mov r0, #0x33
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	bl MOD13_0221F4AC
	mov r0, #2
	bl MOD13_0221F124
	mov r0, #0x33
	bl MOD13_0221F070
	mov r0, #0
	bl MOD13_0221E694
	bl MOD13_022335AC
	bl MOD13_0223348C
	mov r0, #0xa
	bl MOD13_0223424C
	ldr r0, _0222F914 ; =MOD13_0222F780
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222F90C: .word 0x0224310C
_0222F910: .word 0x02243108
_0222F914: .word MOD13_0222F780

	arm_func_start MOD13_0222F918
MOD13_0222F918: ; 0x0222F918
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r2, _0222F9EC ; =0x0223F400
	ldr r1, _0222F9F0 ; =0x0223F404
	ldrb r7, [r2]
	ldrb r6, [r2, #1]
	ldrb r5, [r2, #2]
	ldrb r4, [r2, #3]
	ldrb lr, [r1]
	ldrb ip, [r1, #1]
	ldrb r3, [r1, #2]
	ldrb r2, [r1, #3]
	ldr r0, _0222F9F4 ; =0x02243110
	strb r7, [sp]
	ldrb r1, [r0]
	strb r2, [sp, #7]
	strb r6, [sp, #1]
	strb r5, [sp, #2]
	strb r4, [sp, #3]
	strb lr, [sp, #4]
	strb ip, [sp, #5]
	strb r3, [sp, #6]
	cmp r1, #3
	add r2, sp, #0
	addhi sp, sp, #0xc
	ldmhiia sp!, {r4, r5, r6, r7, pc}
	ldr r0, _0222F9F8 ; =0x02243114
	ldrb r1, [r2, r1]
	ldr r0, [r0]
	ldr r0, [r0]
	mov r2, r1
	bl MOD13_022327DC
	ldr r0, _0222F9F4 ; =0x02243110
	ldrb r0, [r0]
	cmp r0, #3
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD13_02233D0C
	ldr r1, _0222F9F4 ; =0x02243110
	ldr r2, _0222F9F8 ; =0x02243114
	ldrb r3, [r1]
	ldr r2, [r2]
	cmp r0, #2
	movgt r0, #3
	add r1, sp, #4
	add r2, r2, r3, lsl #2
	ldrb r3, [r1, r0]
	ldr r0, [r2, #4]
	mvn r1, #0
	mov r2, #0
	bl MOD13_02239994
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0222F9EC: .word 0x0223F400
_0222F9F0: .word 0x0223F404
_0222F9F4: .word 0x02243110
_0222F9F8: .word 0x02243114

	arm_func_start MOD13_0222F9FC
MOD13_0222F9FC: ; 0x0222F9FC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _0222FA28 ; =MOD13_022303D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222FA28: .word MOD13_022303D8

	arm_func_start MOD13_0222FA2C
MOD13_0222FA2C: ; 0x0222FA2C
	stmdb sp!, {r4, lr}
	ldr r0, _0222FB8C ; =0x02243110
	ldrb r0, [r0]
	sub r4, r0, #4
	bl MOD13_02235E9C
	cmp r0, #0
	beq _0222FB00
	cmp r0, #1
	ldmneia sp!, {r4, pc}
	mov r0, #0xe
	bl MOD13_0223424C
	mov r0, r4
	bl MOD13_022338B8
	ldr r0, _0222FB90 ; =0x02243114
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #4]
	bl MOD13_02239ADC
	ldr r1, _0222FB94 ; =0x0223F3FC
	mov r2, r0
	ldrb r1, [r1, #3]
	mov r0, #0
	bl MOD13_02239E8C
	ldr r0, _0222FB90 ; =0x02243114
	mov ip, r4, lsl #2
	ldr r0, [r0]
	mvn r1, #0
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #4]
	ldr r2, _0222FB98 ; =0x0223F428
	ldr r3, _0222FB9C ; =0x0223F42A
	ldrh r2, [r2, ip]
	ldrh r3, [r3, ip]
	bl MOD13_02239888
	ldr r0, _0222FB90 ; =0x02243114
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #3
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #4]
	bl MOD13_02239814
	ldr r0, _0222FB90 ; =0x02243114
	ldr r0, [r0]
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0x10]
	bl MOD13_02239AE8
	mov r1, #0
	ldr r0, _0222FB90 ; =0x02243114
	ldr r0, [r0]
	add r0, r0, r4, lsl #2
	str r1, [r0, #0x10]
	b _0222FB7C
_0222FB00:
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _0222FB90 ; =0x02243114
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0x10]
	bl MOD13_02239ADC
	mov r2, r0
	mov r0, #0
	mov r1, #0x11
	bl MOD13_02239E8C
	ldr r0, _0222FB90 ; =0x02243114
	add r1, r4, #3
	ldr r0, [r0]
	mov ip, r1, lsl #2
	ldr r2, _0222FB98 ; =0x0223F428
	ldr r3, _0222FB9C ; =0x0223F42A
	add r0, r0, r4, lsl #2
	ldrh r2, [r2, ip]
	ldrh r3, [r3, ip]
	ldr r0, [r0, #0x10]
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _0222FB90 ; =0x02243114
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #3
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0x10]
	bl MOD13_02239814
_0222FB7C:
	bl MOD13_02235EB0
	ldr r0, _0222FBA0 ; =MOD13_0222F9FC
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222FB8C: .word 0x02243110
_0222FB90: .word 0x02243114
_0222FB94: .word 0x0223F3FC
_0222FB98: .word 0x0223F428
_0222FB9C: .word 0x0223F42A
_0222FBA0: .word MOD13_0222F9FC

	arm_func_start MOD13_0222FBA4
MOD13_0222FBA4: ; 0x0222FBA4
	stmdb sp!, {r4, lr}
	ldr r1, _0222FC2C ; =0x02243110
	ldr r0, _0222FC30 ; =0x02243114
	ldrb r2, [r1]
	ldr r0, [r0]
	mov r1, #0
	sub r4, r2, #4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0x10]
	bl MOD13_02239ADC
	mov r2, r0
	mov r0, #0
	mov r1, #0x32
	bl MOD13_02239E8C
	ldr r0, _0222FC30 ; =0x02243114
	add r3, r4, #3
	ldr r2, [r0]
	ldr r1, _0222FC34 ; =0x0223F428
	mov r3, r3, lsl #2
	ldr r0, _0222FC38 ; =0x0223F42A
	add ip, r2, r4, lsl #2
	ldrh r2, [r1, r3]
	ldrh r3, [r0, r3]
	ldr r0, [ip, #0x10]
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _0222FC30 ; =0x02243114
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #3
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0x10]
	bl MOD13_02239814
	ldmia sp!, {r4, pc}
	.align 2, 0
_0222FC2C: .word 0x02243110
_0222FC30: .word 0x02243114
_0222FC34: .word 0x0223F428
_0222FC38: .word 0x0223F42A

	arm_func_start MOD13_0222FC3C
MOD13_0222FC3C: ; 0x0222FC3C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _0222FE54 ; =0x02243110
	mov r1, #1
	ldrb r2, [r3]
	cmp r2, #6
	addls pc, pc, r2, lsl #2
	b _0222FE34
_0222FC5C: ; jump table
	b _0222FC78 ; case 0
	b _0222FCBC ; case 1
	b _0222FD00 ; case 2
	b _0222FD44 ; case 3
	b _0222FD70 ; case 4
	b _0222FDB4 ; case 5
	b _0222FDF4 ; case 6
_0222FC78:
	ldr r2, _0222FE58 ; =0x02243114
	cmp r0, #0
	ldr r2, [r2]
	mov ip, #0
	strb ip, [r2, #0x1c]
	moveq r0, #2
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #2
	streqb r1, [r3]
	beq _0222FE34
	cmp r0, #1
	moveq r0, #3
	streqb r0, [r3]
	movne r0, #4
	strneb r0, [r3]
	b _0222FE34
_0222FCBC:
	ldr r2, _0222FE58 ; =0x02243114
	cmp r0, #0
	ldr r2, [r2]
	moveq r0, #0
	strb r1, [r2, #0x1c]
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #2
	moveq r0, #2
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #1
	moveq r0, #3
	streqb r0, [r3]
	movne r0, #5
	strneb r0, [r3]
	b _0222FE34
_0222FD00:
	ldr r2, _0222FE58 ; =0x02243114
	mov ip, #2
	ldr r2, [r2]
	cmp r0, #0
	strb ip, [r2, #0x1c]
	streqb r1, [r3]
	beq _0222FE34
	cmp r0, #2
	moveq r0, #0
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #1
	moveq r0, #3
	streqb r0, [r3]
	movne r0, #6
	strneb r0, [r3]
	b _0222FE34
_0222FD44:
	ldr r2, _0222FE58 ; =0x02243114
	cmp r0, #1
	ldr r2, [r2]
	ldrb ip, [r2, #0x1c]
	add r2, ip, #4
	streqb r2, [r3]
	beq _0222FE34
	cmp r0, #3
	streqb ip, [r3]
	movne r1, #0
	b _0222FE34
_0222FD70:
	ldr r2, _0222FE58 ; =0x02243114
	cmp r0, #0
	ldr r2, [r2]
	mov ip, #0
	strb ip, [r2, #0x1c]
	moveq r0, #6
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #2
	moveq r0, #5
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #1
	streqb ip, [r3]
	movne r0, #3
	strneb r0, [r3]
	b _0222FE34
_0222FDB4:
	ldr r2, _0222FE58 ; =0x02243114
	cmp r0, #0
	ldr r2, [r2]
	moveq r0, #4
	strb r1, [r2, #0x1c]
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #2
	moveq r0, #6
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #1
	streqb r1, [r3]
	movne r0, #3
	strneb r0, [r3]
	b _0222FE34
_0222FDF4:
	ldr r2, _0222FE58 ; =0x02243114
	cmp r0, #0
	ldr r2, [r2]
	mov ip, #2
	strb ip, [r2, #0x1c]
	moveq r0, #5
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #2
	moveq r0, #4
	streqb r0, [r3]
	beq _0222FE34
	cmp r0, #1
	streqb ip, [r3]
	movne r0, #3
	strneb r0, [r3]
_0222FE34:
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #8
	bl MOD13_0223424C
	bl MOD13_0222FE5C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222FE54: .word 0x02243110
_0222FE58: .word 0x02243114

	arm_func_start MOD13_0222FE5C
MOD13_0222FE5C: ; 0x0222FE5C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0222FED0 ; =0x02243110
	ldrb r2, [r0]
	cmp r2, #4
	bhs _0222FEA4
	mov ip, r2, lsl #3
	ldr r0, _0222FED4 ; =0x0223F478
	ldr r1, _0222FED8 ; =0x0223F47C
	ldr r2, _0222FEDC ; =0x0223F47A
	ldr r3, _0222FEE0 ; =0x0223F47E
	ldrh r0, [r0, ip]
	ldrh r1, [r1, ip]
	ldrh r2, [r2, ip]
	ldrh r3, [r3, ip]
	bl MOD13_0221F25C
	add sp, sp, #4
	ldmia sp!, {pc}
_0222FEA4:
	ldr r1, _0222FED4 ; =0x0223F478
	mov r3, r2, lsl #3
	ldr r2, _0222FED8 ; =0x0223F47C
	ldr r0, _0222FEDC ; =0x0223F47A
	ldrh r1, [r1, r3]
	ldrh r2, [r2, r3]
	ldrh r3, [r0, r3]
	mov r0, #0
	bl MOD13_0221F348
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0222FED0: .word 0x02243110
_0222FED4: .word 0x0223F478
_0222FED8: .word 0x0223F47C
_0222FEDC: .word 0x0223F47A
_0222FEE0: .word 0x0223F47E

	arm_func_start MOD13_0222FEE4
MOD13_0222FEE4: ; 0x0222FEE4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	bl MOD13_022343D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r4, _02230084 ; =0x02243114
	mov r5, #0
_0222FF3C:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _0222FF54
	bl MOD13_02239AE8
_0222FF54:
	add r5, r5, #1
	cmp r5, #3
	blo _0222FF3C
	ldr r4, _02230084 ; =0x02243114
	mov r5, #0
_0222FF68:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _0222FF80
	bl MOD13_02239AE8
_0222FF80:
	add r5, r5, #1
	cmp r5, #3
	blo _0222FF68
	bl MOD13_0221F21C
	bl MOD13_0221EE54
	ldr r0, _02230084 ; =0x02243114
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD13_0223939C
	ldr r0, _02230088 ; =0x02240410
	ldr r1, _0223008C ; =0x020C9480
	bl MOD13_0221F174
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AE98
	ldr r0, _02230084 ; =0x02243114
	ldr r0, [r0]
	ldrb r0, [r0, #0x1d]
	cmp r0, #2
	bne _0222FFF4
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _02230090 ; =MOD13_022245B4
	bl MOD13_02222FBC
	b _02230074
_0222FFF4:
	ldr r0, _02230094 ; =0x02243110
	ldrb r0, [r0]
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _02230074
_02230008: ; jump table
	b _02230018 ; case 0
	b _02230018 ; case 1
	b _02230018 ; case 2
	b _02230060 ; case 3
_02230018:
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	bl MOD13_02234164
	ldrb r0, [r0, #0xe7]
	cmp r0, #0xff
	bne _02230040
	ldr r0, _02230098 ; =MOD13_02230EC4
	bl MOD13_02222FBC
	b _02230074
_02230040:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222F6C
	mov r0, #0
	bl MOD13_0222B7F4
	ldr r0, _0223009C ; =MOD13_0222DD4C
	bl MOD13_02222FBC
	b _02230074
_02230060:
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022300A0 ; =MOD13_0223201C
	bl MOD13_02222FBC
_02230074:
	ldr r0, _02230084 ; =0x02243114
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02230084: .word 0x02243114
_02230088: .word 0x02240410
_0223008C: .word 0x020C9480
_02230090: .word MOD13_022245B4
_02230094: .word 0x02243110
_02230098: .word MOD13_02230EC4
_0223009C: .word MOD13_0222DD4C
_022300A0: .word MOD13_0223201C

	arm_func_start MOD13_022300A4
MOD13_022300A4: ; 0x022300A4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02230130 ; =0x02243114
	ldr r0, [r0]
	ldrb r0, [r0, #0x1d]
	cmp r0, #1
	bne _022300F8
	ldr r0, _02230134 ; =0x02243110
	ldrb r0, [r0]
	cmp r0, #3
	beq _022300F4
	bl MOD13_02234164
	ldrb r0, [r0, #0xe7]
	cmp r0, #0xff
	beq _022300F8
_022300F4:
	bl MOD13_0221ED28
_022300F8:
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02230138 ; =MOD13_0222FEE4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230130: .word 0x02243114
_02230134: .word 0x02243110
_02230138: .word MOD13_0222FEE4

	arm_func_start MOD13_0223013C
MOD13_0223013C: ; 0x0223013C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02230178 ; =0x02243114
	ldr r0, [r0]
	ldrb r0, [r0, #0x1d]
	cmp r0, #2
	bne _0223015C
	bl MOD13_02234908
_0223015C:
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _0223017C ; =MOD13_022300A4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230178: .word 0x02243114
_0223017C: .word MOD13_022300A4

	arm_func_start MOD13_02230180
MOD13_02230180: ; 0x02230180
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	bl MOD13_0221ED14
	cmp r0, #0
	beq _022301A4
	cmp r0, #1
	beq _022301EC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022301A4:
	bl MOD13_02222F1C
	cmp r0, #0
	beq _022301BC
	cmp r0, #1
	beq _022301D8
	b _02230294
_022301BC:
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _022302A4 ; =0x02243114
	mov r1, #2
	ldr r0, [r0]
	strb r1, [r0, #0x1d]
	b _02230294
_022301D8:
	bl MOD13_0221EC84
	ldr r0, _022302A8 ; =MOD13_02223CFC
	bl MOD13_02222FBC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022301EC:
	ldr r0, _022302A4 ; =0x02243114
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _022302AC ; =0x02243110
	strb r2, [r1, #0x1d]
	ldrb r0, [r0]
	cmp r0, #4
	blo _0223027C
	sub r4, r0, #4
	mov r0, r4
	bl MOD13_02233D0C
	cmp r0, #0xff
	bne _02230238
	mov r0, #9
	bl MOD13_0223424C
	mvn r0, #0
	bl MOD13_0221ECE0
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02230238:
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02222F34
	add r2, r4, #1
	str r2, [sp]
	ldr r1, _022302B0 ; =0x0223F408
	mov r2, #1
	ldrsb r3, [r1, r0]
	mov r0, #0x46
	mov r1, #0
	bl MOD13_02235EFC
	bl MOD13_0222FBA4
	bl MOD13_0221EC84
	ldr r0, _022302B4 ; =MOD13_0222FA2C
	bl MOD13_02222FBC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0223027C:
	cmp r0, #2
	bhi _02230288
	bl MOD13_02233C24
_02230288:
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_0222F918
_02230294:
	ldr r0, _022302B8 ; =MOD13_0223013C
	bl MOD13_02222FBC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022302A4: .word 0x02243114
_022302A8: .word MOD13_02223CFC
_022302AC: .word 0x02243110
_022302B0: .word 0x0223F408
_022302B4: .word MOD13_0222FA2C
_022302B8: .word MOD13_0223013C

	arm_func_start MOD13_022302BC
MOD13_022302BC: ; 0x022302BC
	bx lr

	arm_func_start MOD13_022302C0
MOD13_022302C0: ; 0x022302C0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r4, _022303D0 ; =0x0223F440
	mov r5, #0
_022302D0:
	mov r0, r4
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _022302FC
	mov r0, #1
	bl MOD13_0221ECF4
	ldr r0, _022303D4 ; =0x02243110
	strb r5, [r0]
	bl MOD13_0222FE5C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_022302FC:
	add r5, r5, #1
	cmp r5, #7
	add r4, r4, #8
	blo _022302D0
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0223032C
	mov r0, #1
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0223032C:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _0223034C
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0223034C:
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0223036C
	mov r0, #1
	bl MOD13_0222FC3C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0223036C:
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _0223038C
	mov r0, #3
	bl MOD13_0222FC3C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_0223038C:
	mov r0, #0x20
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _022303AC
	mov r0, #0
	bl MOD13_0222FC3C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_022303AC:
	mov r0, #0x10
	bl MOD13_0223B3B0
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	mov r0, #2
	bl MOD13_0222FC3C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022303D0: .word 0x0223F440
_022303D4: .word 0x02243110

	arm_func_start MOD13_022303D8
MOD13_022303D8: ; 0x022303D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022302C0
	bl MOD13_022302BC
	bl MOD13_02230180
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_02234800
	cmp r0, #1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02230434 ; =MOD13_022303D8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230434: .word MOD13_022303D8

	arm_func_start MOD13_02230438
MOD13_02230438: ; 0x02230438
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0221F0EC
	ldr r0, _02230480 ; =0x022303F4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230480: .word 0x022303F4

	arm_func_start MOD13_02230484
MOD13_02230484: ; 0x02230484
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AEF4
	ldr r0, _022304DC ; =MOD13_02230438
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022304DC: .word MOD13_02230438

	arm_func_start MOD13_022304E0
MOD13_022304E0: ; 0x022304E0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov sb, #0
	ldr r4, _022305F0 ; =0x02243114
	ldr r5, _022305F4 ; =0x0223F428
	str sb, [sp]
	str sb, [sp, #4]
	mov fp, #0x11
	mov r7, #1
	mvn r6, #0
	mov r8, #3
_0223050C:
	mov r0, sb
	bl MOD13_02233D0C
	mov sl, r0
	cmp sl, #0xff
	moveq sl, r8
	beq _02230580
	ldr r0, [sp]
	mov r1, fp
	mov r2, r7
	bl MOD13_02239E0C
	ldr r1, [r4]
	add r3, sb, #3
	add r1, r1, sb, lsl #2
	str r0, [r1, #0x10]
	mov r2, r3, lsl #2
	ldr r0, [r4]
	add r3, r5, r3, lsl #2
	add r0, r0, sb, lsl #2
	ldrh r2, [r5, r2]
	ldrh r3, [r3, #2]
	ldr r0, [r0, #0x10]
	mov r1, r6
	bl MOD13_02239888
	ldr r0, [r4]
	mov r1, r6
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #0x10]
	mov r2, r8
	bl MOD13_02239814
_02230580:
	ldr r0, _022305F8 ; =0x0223F3FC
	mov r2, r7
	ldrb r1, [r0, sl]
	ldr r0, [sp, #4]
	bl MOD13_02239E0C
	ldr r1, [r4]
	mov r2, sb, lsl #2
	add r1, r1, sb, lsl #2
	str r0, [r1, #4]
	ldr r0, [r4]
	add r3, r5, sb, lsl #2
	add r0, r0, sb, lsl #2
	ldrh r2, [r5, r2]
	ldrh r3, [r3, #2]
	ldr r0, [r0, #4]
	mov r1, r6
	bl MOD13_02239888
	ldr r0, [r4]
	mov r1, r6
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #4]
	mov r2, r8
	bl MOD13_02239814
	add sb, sb, #1
	cmp sb, #3
	blt _0223050C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022305F0: .word 0x02243114
_022305F4: .word 0x0223F428
_022305F8: .word 0x0223F3FC

	arm_func_start MOD13_022305FC
MOD13_022305FC: ; 0x022305FC
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr ip, _022306DC ; =0x0223F410
	add r3, sp, #0
	mov r2, #0xb
_02230610:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _02230610
	ldr r0, _022306E0 ; =0x02240428
	ldr r1, _022306E4 ; =0x020C9480
	bl MOD13_0221F174
	ldr r0, _022306E8 ; =0x0224043C
	ldr r1, _022306EC ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _022306F0 ; =0x02240454
	ldr r1, _022306F4 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _022306F8 ; =0x0224046C
	ldr r1, _022306FC ; =0x020C908C
	bl MOD13_0221F174
	add r0, sp, #0
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r2, _02230700 ; =0x02243114
	mov r1, #0x10
	ldr r2, [r2]
	str r0, [r2]
	mov r0, #1
	bl MOD13_0223AEF4
	ldr ip, _02230704 ; =0x04001008
	ldr r3, _02230708 ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _0223070C ; =0x0400000A
	ldr r1, _02230710 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.align 2, 0
_022306DC: .word 0x0223F410
_022306E0: .word 0x02240428
_022306E4: .word 0x020C9480
_022306E8: .word 0x0224043C
_022306EC: .word 0x020C8D4C
_022306F0: .word 0x02240454
_022306F4: .word 0x020C9550
_022306F8: .word 0x0224046C
_022306FC: .word 0x020C908C
_02230700: .word 0x02243114
_02230704: .word 0x04001008
_02230708: .word 0x0400100A
_0223070C: .word 0x0400000A
_02230710: .word 0x0400000C

	arm_func_start MOD13_02230714
MOD13_02230714: ; 0x02230714
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x20
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, _02230774 ; =0x02243114
	mov r2, #0
	str r0, [r1]
	strb r2, [r0, #0x1d]
	bl MOD13_022305FC
	mov r0, #1
	bl MOD13_0221F4CC
	mov r0, #0x2f
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #0
	bl MOD13_0221F124
	bl MOD13_022304E0
	bl MOD13_0222FE5C
	ldr r0, _02230778 ; =MOD13_02230484
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230774: .word 0x02243114
_02230778: .word MOD13_02230484

	arm_func_start MOD13_0223077C
MOD13_0223077C: ; 0x0223077C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r0, _022307D0 ; =0x0223F4B0
	ldr r1, _022307D4 ; =0x0224311C
	ldrb lr, [r0]
	ldrb ip, [r0, #1]
	ldrb r3, [r0, #2]
	ldrb r2, [r0, #3]
	ldr r0, _022307D8 ; =0x02243124
	ldrsb r1, [r1]
	add r4, sp, #0
	strb lr, [sp]
	strb ip, [sp, #1]
	strb r3, [sp, #2]
	strb r2, [sp, #3]
	ldrb r1, [r4, r1]
	ldr r0, [r0]
	mov r2, r1
	bl MOD13_022327DC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022307D0: .word 0x0223F4B0
_022307D4: .word 0x0224311C
_022307D8: .word 0x02243124

	arm_func_start MOD13_022307DC
MOD13_022307DC: ; 0x022307DC
	stmdb sp!, {r4, r5, r6, lr}
	ldr r1, _022308B8 ; =0x0224311C
	mov r5, r0
	mov r0, #1
	ldrsb r4, [r1]
	bl MOD13_02222EFC
	ldr r2, _022308BC ; =0x0223F4D4
	mvn r1, #0
	add r0, r2, r0, lsl #4
	add r0, r0, r4, lsl #2
	ldrsb r2, [r5, r0]
	cmp r2, r1
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r2, #0
	ldreq r0, _022308C0 ; =0x02243118
	streqb r4, [r0]
	mvn r0, #1
	cmp r2, r0
	ldreq r1, _022308C0 ; =0x02243118
	ldreq r0, _022308B8 ; =0x0224311C
	ldreqsb r1, [r1]
	streqb r1, [r0]
	ldrne r0, _022308B8 ; =0x0224311C
	strneb r2, [r0]
	mov r0, #8
	bl MOD13_0223424C
	mov r0, #1
	bl MOD13_02222EFC
	mov r6, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r5, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r4, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r3, r0
	ldr r0, _022308B8 ; =0x0224311C
	ldr r1, _022308C4 ; =0x0223F534
	ldrsb lr, [r0]
	ldr r0, _022308C8 ; =0x0223F536
	add ip, r1, r6, lsl #5
	ldr r1, _022308CC ; =0x0223F538
	add r2, r0, r4, lsl #5
	ldr r4, _022308D0 ; =0x0223F53A
	add r1, r1, r5, lsl #5
	mov r5, lr, lsl #3
	add r3, r4, r3, lsl #5
	ldrh r0, [r5, ip]
	ldrh r1, [r5, r1]
	ldrh r2, [r5, r2]
	ldrh r3, [r5, r3]
	bl MOD13_0221F25C
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_022308B8: .word 0x0224311C
_022308BC: .word 0x0223F4D4
_022308C0: .word 0x02243118
_022308C4: .word 0x0223F534
_022308C8: .word 0x0223F536
_022308CC: .word 0x0223F538
_022308D0: .word 0x0223F53A

	arm_func_start MOD13_022308D4
MOD13_022308D4: ; 0x022308D4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221F21C
	bl MOD13_0221EE54
	ldr r0, _02230A14 ; =0x02243124
	ldr r0, [r0]
	bl MOD13_0223939C
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AE98
	ldr r0, _02230A18 ; =0x02243120
	ldrb r0, [r0]
	cmp r0, #0
	bne _0223096C
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	ldr r0, _02230A1C ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0223096C:
	ldr r0, _02230A20 ; =0x0224311C
	ldrsb r0, [r0]
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _02230A0C
_02230980: ; jump table
	b _02230990 ; case 0
	b _022309AC ; case 1
	b _022309C8 ; case 2
	b _022309E4 ; case 3
_02230990:
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02230A24 ; =MOD13_0222F8A0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022309AC:
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02230A28 ; =MOD13_02227C38
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022309C8:
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02230A2C ; =MOD13_0222F2F8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022309E4:
	mov r0, #2
	mov r1, #0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, r0
	bl MOD13_02222F6C
	mov r0, #1
	bl MOD13_0222B7F4
	ldr r0, _02230A30 ; =MOD13_0222DD4C
	bl MOD13_02222FBC
_02230A0C:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230A14: .word 0x02243124
_02230A18: .word 0x02243120
_02230A1C: .word MOD13_02230714
_02230A20: .word 0x0224311C
_02230A24: .word MOD13_0222F8A0
_02230A28: .word MOD13_02227C38
_02230A2C: .word MOD13_0222F2F8
_02230A30: .word MOD13_0222DD4C

	arm_func_start MOD13_02230A34
MOD13_02230A34: ; 0x02230A34
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02230A9C ; =0x02243120
	ldrb r0, [r0]
	cmp r0, #0
	beq _02230A64
	bl MOD13_0221ED28
_02230A64:
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02230AA0 ; =MOD13_022308D4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230A9C: .word 0x02243120
_02230AA0: .word MOD13_022308D4

	arm_func_start MOD13_02230AA4
MOD13_02230AA4: ; 0x02230AA4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02230AC8 ; =MOD13_02230A34
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230AC8: .word MOD13_02230A34

	arm_func_start MOD13_02230ACC
MOD13_02230ACC: ; 0x02230ACC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02230AF0
	cmp r0, #1
	beq _02230AFC
	add sp, sp, #4
	ldmia sp!, {pc}
_02230AF0:
	mov r0, #7
	bl MOD13_0223424C
	b _02230B14
_02230AFC:
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_0223077C
	ldr r0, _02230B24 ; =0x02243120
	mov r1, #1
	strb r1, [r0]
_02230B14:
	ldr r0, _02230B28 ; =MOD13_02230AA4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230B24: .word 0x02243120
_02230B28: .word MOD13_02230AA4

	arm_func_start MOD13_02230B2C
MOD13_02230B2C: ; 0x02230B2C
	bx lr

	arm_func_start MOD13_02230B30
MOD13_02230B30: ; 0x02230B30
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r7, #0
	mov r6, r7
	ldr r4, _02230CC0 ; =0x0223F4F4
	mov r5, #1
_02230B48:
	mov r0, r5
	bl MOD13_02222EFC
	add r0, r4, r0, lsl #5
	add r0, r0, r6
	bl MOD13_0223B2B4
	cmp r0, #0
	beq _02230BEC
	mov r0, #1
	bl MOD13_0221ECF4
	ldr r1, _02230CC4 ; =0x0224311C
	mov r0, #1
	strb r7, [r1]
	bl MOD13_02222EFC
	mov r6, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r5, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r4, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r3, r0
	ldr r0, _02230CC4 ; =0x0224311C
	ldr r1, _02230CC8 ; =0x0223F534
	ldrsb lr, [r0]
	ldr r0, _02230CCC ; =0x0223F536
	add ip, r1, r6, lsl #5
	ldr r1, _02230CD0 ; =0x0223F538
	add r2, r0, r4, lsl #5
	ldr r4, _02230CD4 ; =0x0223F53A
	add r1, r1, r5, lsl #5
	mov r5, lr, lsl #3
	add r3, r4, r3, lsl #5
	ldrh r0, [r5, ip]
	ldrh r1, [r5, r1]
	ldrh r2, [r5, r2]
	ldrh r3, [r5, r3]
	bl MOD13_0221F25C
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_02230BEC:
	add r7, r7, #1
	cmp r7, #4
	add r6, r6, #8
	blo _02230B48
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02230C1C
	mov r0, #1
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_02230C1C:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02230C3C
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_02230C3C:
	mov r0, #0x40
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02230C5C
	mov r0, #1
	bl MOD13_022307DC
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_02230C5C:
	mov r0, #0x80
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02230C7C
	mov r0, #3
	bl MOD13_022307DC
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_02230C7C:
	mov r0, #0x20
	bl MOD13_0223B3B0
	cmp r0, #0
	beq _02230C9C
	mov r0, #0
	bl MOD13_022307DC
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_02230C9C:
	mov r0, #0x10
	bl MOD13_0223B3B0
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	mov r0, #2
	bl MOD13_022307DC
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02230CC0: .word 0x0223F4F4
_02230CC4: .word 0x0224311C
_02230CC8: .word 0x0223F534
_02230CCC: .word 0x0223F536
_02230CD0: .word 0x0223F538
_02230CD4: .word 0x0223F53A

	arm_func_start MOD13_02230CD8
MOD13_02230CD8: ; 0x02230CD8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02230B30
	bl MOD13_02230B2C
	bl MOD13_02230ACC
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02230D24 ; =MOD13_02230CD8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230D24: .word MOD13_02230CD8

	arm_func_start MOD13_02230D28
MOD13_02230D28: ; 0x02230D28
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0221F0EC
	ldr r0, _02230D70 ; =0x02230CF4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230D70: .word 0x02230CF4

	arm_func_start MOD13_02230D74
MOD13_02230D74: ; 0x02230D74
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AEF4
	ldr r0, _02230DCC ; =MOD13_02230D28
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02230DCC: .word MOD13_02230D28

	arm_func_start MOD13_02230DD0
MOD13_02230DD0: ; 0x02230DD0
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	ldr ip, _02230E94 ; =0x0223F4BC
	add r3, sp, #0
	mov r2, #0xb
_02230DE4:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _02230DE4
	ldr r0, _02230E98 ; =0x02240480
	ldr r1, _02230E9C ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _02230EA0 ; =0x02240498
	ldr r1, _02230EA4 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _02230EA8 ; =0x022404B0
	ldr r1, _02230EAC ; =0x020C908C
	bl MOD13_0221F174
	add r0, sp, #0
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _02230EB0 ; =0x02243124
	ldr ip, _02230EB4 ; =0x04001008
	str r0, [r1]
	ldrh r0, [ip]
	ldr r3, _02230EB8 ; =0x0400100A
	ldr r2, _02230EBC ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	ldr r1, _02230EC0 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	.align 2, 0
_02230E94: .word 0x0223F4BC
_02230E98: .word 0x02240480
_02230E9C: .word 0x020C8D4C
_02230EA0: .word 0x02240498
_02230EA4: .word 0x020C9550
_02230EA8: .word 0x022404B0
_02230EAC: .word 0x020C908C
_02230EB0: .word 0x02243124
_02230EB4: .word 0x04001008
_02230EB8: .word 0x0400100A
_02230EBC: .word 0x0400000A
_02230EC0: .word 0x0400000C

	arm_func_start MOD13_02230EC4
MOD13_02230EC4: ; 0x02230EC4
	stmdb sp!, {r4, r5, r6, lr}
	bl MOD13_02234164
	ldr r1, _02230FD0 ; =0x02243118
	ldr r2, _02230FD4 ; =0x02243120
	ldrsb r3, [r1]
	mov r5, #0
	mov r4, r0
	cmp r3, #0
	moveq r0, #1
	strb r5, [r2]
	streqb r0, [r1]
	bl MOD13_02222F34
	cmp r0, #0
	beq _02230F24
	ldr r0, _02230FD8 ; =0x0224311C
	ldrsb r1, [r0]
	cmp r1, #2
	moveq r1, #0
	streqb r1, [r0]
	ldr r0, _02230FD0 ; =0x02243118
	ldrsb r1, [r0]
	cmp r1, #2
	moveq r1, #1
	streqb r1, [r0]
_02230F24:
	bl MOD13_02230DD0
	bl MOD13_0221F4AC
	bl MOD13_02222F34
	mov r5, r0
	ldrb r1, [r4, #0xf4]
	mov r0, #0x32
	ldr r3, _02230FDC ; =0x0223F4B4
	add r2, r1, #1
	ldrsb r1, [r3, r5]
	bl MOD13_0221EE98
	mov r0, #1
	bl MOD13_0221F124
	mov r0, #1
	bl MOD13_02222EFC
	mov r6, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r5, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r4, r0
	mov r0, #1
	bl MOD13_02222EFC
	mov r3, r0
	ldr r1, _02230FE0 ; =0x0223F534
	ldr r0, _02230FD8 ; =0x0224311C
	add ip, r1, r6, lsl #5
	ldrsb lr, [r0]
	ldr r1, _02230FE4 ; =0x0223F538
	ldr r0, _02230FE8 ; =0x0223F536
	add r1, r1, r5, lsl #5
	add r2, r0, r4, lsl #5
	mov r5, lr, lsl #3
	ldrh r0, [r5, ip]
	ldrh r1, [r5, r1]
	ldrh r2, [r5, r2]
	ldr r4, _02230FEC ; =0x0223F53A
	add r3, r4, r3, lsl #5
	ldrh r3, [r5, r3]
	bl MOD13_0221F25C
	ldr r0, _02230FF0 ; =MOD13_02230D74
	bl MOD13_02222FBC
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02230FD0: .word 0x02243118
_02230FD4: .word 0x02243120
_02230FD8: .word 0x0224311C
_02230FDC: .word 0x0223F4B4
_02230FE0: .word 0x0223F534
_02230FE4: .word 0x0223F538
_02230FE8: .word 0x0223F536
_02230FEC: .word 0x0223F53A
_02230FF0: .word MOD13_02230D74

	arm_func_start MOD13_02230FF4
MOD13_02230FF4: ; 0x02230FF4
	ldr ip, _02231000 ; =MOD13_0223AF48
	mov r0, r1
	bx ip
	.align 2, 0
_02231000: .word MOD13_0223AF48

	arm_func_start MOD13_02231004
MOD13_02231004: ; 0x02231004
	ldr ip, _02231014 ; =MOD13_0223B004
	mov r0, r1
	mov r1, #0x20
	bx ip
	.align 2, 0
_02231014: .word MOD13_0223B004

	arm_func_start MOD13_02231018
MOD13_02231018: ; 0x02231018
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl FUN_021EBB80
	movs r4, r0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	bl MOD13_0221F694
	bl MOD13_022341E8
	cmp r4, #0
	ble _0223105C
	ldr r1, _02231088 ; =0x02243128
	mov r2, #1
	mov r0, #0x11
	strb r2, [r1]
	bl MOD13_0223424C
	b _0223106C
_0223105C:
	bl FUN_021EBAE8
	bl MOD13_0222B0BC
	mov r0, #0x12
	bl MOD13_0223424C
_0223106C:
	ldr r0, _0223108C ; =MOD13_0223115C
	bl MOD13_02222FBC
	mov r1, r5
	mov r0, #0
	bl MOD13_0223C110
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02231088: .word 0x02243128
_0223108C: .word MOD13_0223115C

	arm_func_start MOD13_02231090
MOD13_02231090: ; 0x02231090
	stmdb sp!, {r4, lr}
	bl MOD13_022338FC
	mov r4, r0
	bl FUN_021EB9D8
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	bl FUN_02095324
	add r1, r4, #0xf0
	mov r2, #0xe
	bl MI_CpuCopy8
	bl FUN_02095324
	add r1, r4, #0x1f0
	mov r2, #0xe
	bl MI_CpuCopy8
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _02231120 ; =0x02243128
	ldrb r0, [r0]
	cmp r0, #0
	bne _02231108
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02231124 ; =MOD13_0222B7D0
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
_02231108:
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02231128 ; =MOD13_02231704
	bl MOD13_02222FBC
	ldmia sp!, {r4, pc}
	.align 2, 0
_02231120: .word 0x02243128
_02231124: .word MOD13_0222B7D0
_02231128: .word MOD13_02231704

	arm_func_start MOD13_0223112C
MOD13_0223112C: ; 0x0223112C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02231158 ; =MOD13_02231090
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231158: .word MOD13_02231090

	arm_func_start MOD13_0223115C
MOD13_0223115C: ; 0x0223115C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02231188 ; =MOD13_0223112C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231188: .word MOD13_0223112C

	arm_func_start MOD13_0223118C
MOD13_0223118C: ; 0x0223118C
	bx lr

	arm_func_start MOD13_02231190
MOD13_02231190: ; 0x02231190
	bx lr

	arm_func_start MOD13_02231194
MOD13_02231194: ; 0x02231194
	bx lr

	arm_func_start MOD13_02231198
MOD13_02231198: ; 0x02231198
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02231194
	bl MOD13_02231190
	bl MOD13_0223118C
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022311F4 ; =MOD13_02231198
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022311F4: .word MOD13_02231198

	arm_func_start MOD13_022311F8
MOD13_022311F8: ; 0x022311F8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	bne _02231258
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
_02231258:
	ldr r0, _02231268 ; =0x022311B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231268: .word 0x022311B4

	arm_func_start MOD13_0223126C
MOD13_0223126C: ; 0x0223126C
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x10
	bl MOD13_02234164
	mov r4, r0
	ldr r0, _022312FC ; =0x0223F574
	add r1, sp, #4
	mov r2, #0xc
	bl MIi_CpuCopy32
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #2
	moveq r0, #4
	streqb r0, [sp, #0xe]
	ldrneb r0, [r4, #0xf4]
	addne r0, r0, #1
	strneb r0, [sp, #0xe]
	add r0, sp, #4
	bl FUN_021EBC60
	cmp r0, #0
	bne _022312C8
	bl OS_Terminate
_022312C8:
	ldr r0, [sp]
	cmp r0, #0
	bne _022312E0
	ldrb r0, [r4, #0xf4]
	mov r1, r4
	bl FUN_021EB9A4
_022312E0:
	mov r0, #0
	ldr r1, _02231300 ; =MOD13_02231018
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	add sp, sp, #0x10
	ldmia sp!, {r4, pc}
	.align 2, 0
_022312FC: .word 0x0223F574
_02231300: .word MOD13_02231018

	arm_func_start MOD13_02231304
MOD13_02231304: ; 0x02231304
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223139C ; =0x022404C4
	ldr r1, _022313A0 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _022313A4 ; =0x022404DC
	ldr r1, _022313A8 ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _022313AC ; =0x022404F4
	ldr r1, _022313B0 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _022313B4 ; =0x04001008
	ldr ip, _022313B8 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _022313BC ; =0x04000008
	ldr r2, _022313C0 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _022313C4 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223139C: .word 0x022404C4
_022313A0: .word 0x020C8D4C
_022313A4: .word 0x022404DC
_022313A8: .word 0x020C9550
_022313AC: .word 0x022404F4
_022313B0: .word 0x020C908C
_022313B4: .word 0x04001008
_022313B8: .word 0x0400100A
_022313BC: .word 0x04000008
_022313C0: .word 0x0400000A
_022313C4: .word 0x0400000C

	arm_func_start MOD13_022313C8
MOD13_022313C8: ; 0x022313C8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231454 ; =0x02243128
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02231304
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	bne _02231408
	mov r0, #0x31
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
_02231408:
	mov r0, #2
	bl MOD13_0221F124
	ldr r0, [sp]
	cmp r0, #0
	bne _02231420
	bl MOD13_0221F4AC
_02231420:
	mov r0, #0x2c
	bl MOD13_0221F070
	mov r0, #0
	bl MOD13_0221E694
	bl MOD13_0223126C
	mov r0, #0
	bl MOD13_0221F6E0
	mov r0, #0xc
	bl MOD13_0223424C
	ldr r0, _02231458 ; =MOD13_022311F8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231454: .word 0x02243128
_02231458: .word MOD13_022311F8

	arm_func_start MOD13_0223145C
MOD13_0223145C: ; 0x0223145C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022314D0 ; =0x0224312C
	ldrb r1, [r0]
	add r1, r1, #1
	strb r1, [r0]
	ldrb r0, [r0]
	cmp r0, #0xb4
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	bl MOD13_02222F1C
	cmp r0, #0
	beq _022314C0
	cmp r0, #1
	bne _022314C0
	ldr r0, [sp]
	cmp r0, #0
	beq _022314C0
	ldr r0, _022314D4 ; =MOD13_02223CFC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022314C0:
	ldr r0, _022314D8 ; =MOD13_02231598
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022314D0: .word 0x0224312C
_022314D4: .word MOD13_02223CFC
_022314D8: .word MOD13_02231598

	arm_func_start MOD13_022314DC
MOD13_022314DC: ; 0x022314DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_022343D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	bne _02231580
	mov r0, #0
	mov r1, r0
	bl MOD13_02222F6C
	ldr r0, _02231590 ; =MOD13_0222DD4C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02231580:
	ldr r0, _02231594 ; =MOD13_022245B4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231590: .word MOD13_0222DD4C
_02231594: .word MOD13_022245B4

	arm_func_start MOD13_02231598
MOD13_02231598: ; 0x02231598
	stmdb sp!, {lr}
	sub sp, sp, #4
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	ldr r0, [sp]
	cmp r0, #0
	beq _022315BC
	bl MOD13_02234908
_022315BC:
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _022315F4 ; =MOD13_022314DC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022315F4: .word MOD13_022314DC

	arm_func_start MOD13_022315F8
MOD13_022315F8: ; 0x022315F8
	bx lr

	arm_func_start MOD13_022315FC
MOD13_022315FC: ; 0x022315FC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0223145C
	bl MOD13_022315F8
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02231640 ; =MOD13_022315FC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231640: .word MOD13_022315FC

	arm_func_start MOD13_02231644
MOD13_02231644: ; 0x02231644
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _0223167C ; =0x02231614
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223167C: .word 0x02231614

	arm_func_start MOD13_02231680
MOD13_02231680: ; 0x02231680
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022316EC ; =0x02240508
	ldr r1, _022316F0 ; =0x020C908C
	bl MOD13_0221F174
	ldr ip, _022316F4 ; =0x04001008
	ldr r3, _022316F8 ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _022316FC ; =0x0400000A
	ldr r1, _02231700 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022316EC: .word 0x02240508
_022316F0: .word 0x020C908C
_022316F4: .word 0x04001008
_022316F8: .word 0x0400100A
_022316FC: .word 0x0400000A
_02231700: .word 0x0400000C

	arm_func_start MOD13_02231704
MOD13_02231704: ; 0x02231704
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231734 ; =0x0224312C
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02231680
	mov r0, #0x2d
	bl MOD13_0221F070
	ldr r0, _02231738 ; =MOD13_02231644
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231734: .word 0x0224312C
_02231738: .word MOD13_02231644

	arm_func_start MOD13_0223173C
MOD13_0223173C: ; 0x0223173C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02231780 ; =MOD13_022313C8
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231780: .word MOD13_022313C8

	arm_func_start MOD13_02231784
MOD13_02231784: ; 0x02231784
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _022317C0 ; =MOD13_0223173C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022317C0: .word MOD13_0223173C

	arm_func_start MOD13_022317C4
MOD13_022317C4: ; 0x022317C4
	bx lr

	arm_func_start MOD13_022317C8
MOD13_022317C8: ; 0x022317C8
	bx lr

	arm_func_start MOD13_022317CC
MOD13_022317CC: ; 0x022317CC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022317C8
	bl MOD13_022317C4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _02231810 ; =MOD13_02231784
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231810: .word MOD13_02231784

	arm_func_start MOD13_02231814
MOD13_02231814: ; 0x02231814
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr r0, _02231894 ; =0x0223F580
	add r3, sp, #8
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #0x14
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #0x14
	ldmneia sp!, {pc}
	add r1, sp, #4
	mov r0, #0
	bl MOD13_02222F44
	mov r0, #0
	str r0, [sp]
	mov r1, #1
	ldr r3, [sp, #4]
	add r0, sp, #8
	ldr r0, [r0, r3, lsl #2]
	mov r2, r1
	mvn r3, #0
	bl MOD13_02235EFC
	ldr r0, _02231898 ; =MOD13_022317CC
	bl MOD13_02222FBC
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.align 2, 0
_02231894: .word 0x0223F580
_02231898: .word MOD13_022317CC

	arm_func_start MOD13_0223189C
MOD13_0223189C: ; 0x0223189C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x14
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x14
	bl MOD13_0223AEF4
	ldr r0, _022318F4 ; =MOD13_02231814
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022318F4: .word MOD13_02231814

	arm_func_start MOD13_022318F8
MOD13_022318F8: ; 0x022318F8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231964 ; =0x0224051C
	ldr r1, _02231968 ; =0x020C908C
	bl MOD13_0221F174
	ldr ip, _0223196C ; =0x04001008
	ldr r3, _02231970 ; =0x0400100A
	ldrh r0, [ip]
	ldr r2, _02231974 ; =0x0400000A
	ldr r1, _02231978 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231964: .word 0x0224051C
_02231968: .word 0x020C908C
_0223196C: .word 0x04001008
_02231970: .word 0x0400100A
_02231974: .word 0x0400000A
_02231978: .word 0x0400000C

	arm_func_start MOD13_0223197C
MOD13_0223197C: ; 0x0223197C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02233570
	add r1, sp, #0
	mov r0, #0
	bl MOD13_02222F44
	bl MOD13_022318F8
	mov r0, #0x31
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	ldr r0, [sp]
	cmp r0, #2
	beq _022319B8
	bl MOD13_0221F4AC
_022319B8:
	ldr r0, [sp]
	cmp r0, #1
	bne _022319C8
	bl MOD13_02233B3C
_022319C8:
	ldr r0, _022319D8 ; =MOD13_0223189C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022319D8: .word MOD13_0223189C

	arm_func_start MOD13_022319DC
MOD13_022319DC: ; 0x022319DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231A14 ; =0x02243130
	ldrb r1, [r0]
	add r1, r1, #1
	strb r1, [r0]
	ldrb r0, [r0]
	cmp r0, #0x78
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	ldr r0, _02231A18 ; =MOD13_02231A9C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231A14: .word 0x02243130
_02231A18: .word MOD13_02231A9C

	arm_func_start MOD13_02231A1C
MOD13_02231A1C: ; 0x02231A1C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	mov r0, #0
	mov r1, #2
	bl MOD13_02222F6C
	ldr r0, _02231A98 ; =MOD13_0223197C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231A98: .word MOD13_0223197C

	arm_func_start MOD13_02231A9C
MOD13_02231A9C: ; 0x02231A9C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02231ADC ; =MOD13_02231A1C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231ADC: .word MOD13_02231A1C

	arm_func_start MOD13_02231AE0
MOD13_02231AE0: ; 0x02231AE0
	bx lr

	arm_func_start MOD13_02231AE4
MOD13_02231AE4: ; 0x02231AE4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022319DC
	bl MOD13_02231AE0
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02231B28 ; =MOD13_02231AE4
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231B28: .word MOD13_02231AE4

	arm_func_start MOD13_02231B2C
MOD13_02231B2C: ; 0x02231B2C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02231B64 ; =0x02231AFC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231B64: .word 0x02231AFC

	arm_func_start MOD13_02231B68
MOD13_02231B68: ; 0x02231B68
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231BE8 ; =0x02240530
	ldr r1, _02231BEC ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02231BF0 ; =0x04001008
	ldr ip, _02231BF4 ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02231BF8 ; =0x04000008
	ldr r2, _02231BFC ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02231C00 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231BE8: .word 0x02240530
_02231BEC: .word 0x020C908C
_02231BF0: .word 0x04001008
_02231BF4: .word 0x0400100A
_02231BF8: .word 0x04000008
_02231BFC: .word 0x0400000A
_02231C00: .word 0x0400000C

	arm_func_start MOD13_02231C04
MOD13_02231C04: ; 0x02231C04
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231C44 ; =0x02243130
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02231B68
	mov r0, #8
	bl MOD13_0221F4CC
	mov r0, #0x29
	bl MOD13_0221F070
	mov r0, #0x10
	bl MOD13_0223424C
	ldr r0, _02231C48 ; =MOD13_02231B2C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231C44: .word 0x02243130
_02231C48: .word MOD13_02231B2C

	arm_func_start MOD13_02231C4C
MOD13_02231C4C: ; 0x02231C4C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02231D18 ; =0x02243134
	ldrb r0, [r0]
	cmp r0, #0
	bne _02231C8C
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_02231C8C:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _02231D18 ; =0x02243134
	ldrb r0, [r0]
	cmp r0, #0
	bne _02231CC4
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_02231CC4:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _02231D18 ; =0x02243134
	ldrb r0, [r0]
	cmp r0, #0
	bne _02231CFC
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02231D1C ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02231CFC:
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _02231D20 ; =MOD13_0223269C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231D18: .word 0x02243134
_02231D1C: .word MOD13_02230714
_02231D20: .word MOD13_0223269C

	arm_func_start MOD13_02231D24
MOD13_02231D24: ; 0x02231D24
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _02231D8C ; =0x02243134
	ldrb r0, [r0]
	cmp r0, #0
	bne _02231D68
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_02231D68:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02231D90 ; =MOD13_02231C4C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231D8C: .word 0x02243134
_02231D90: .word MOD13_02231C4C

	arm_func_start MOD13_02231D94
MOD13_02231D94: ; 0x02231D94
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02231DB8 ; =MOD13_02231D24
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231DB8: .word MOD13_02231D24

	arm_func_start MOD13_02231DBC
MOD13_02231DBC: ; 0x02231DBC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	cmp r0, #0
	beq _02231DE0
	cmp r0, #1
	beq _02231DEC
	add sp, sp, #4
	ldmia sp!, {pc}
_02231DE0:
	mov r0, #7
	bl MOD13_0223424C
	b _02231E00
_02231DEC:
	mov r0, #6
	bl MOD13_0223424C
	ldr r0, _02231E10 ; =0x02243134
	mov r1, #1
	strb r1, [r0]
_02231E00:
	ldr r0, _02231E14 ; =MOD13_02231D94
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231E10: .word 0x02243134
_02231E14: .word MOD13_02231D94

	arm_func_start MOD13_02231E18
MOD13_02231E18: ; 0x02231E18
	bx lr

	arm_func_start MOD13_02231E1C
MOD13_02231E1C: ; 0x02231E1C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02231E3C
	mov r0, #1
	bl MOD13_0221ECF4
_02231E3C:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02231E1C
	bl MOD13_02231E18
	bl MOD13_02231DBC
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02231EAC ; =0x02231E60
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231EAC: .word 0x02231E60

	arm_func_start MOD13_02231EB0
MOD13_02231EB0: ; 0x02231EB0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0221F0EC
	ldr r0, _02231EF8 ; =0x02231E7C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231EF8: .word 0x02231E7C

	arm_func_start MOD13_02231EFC
MOD13_02231EFC: ; 0x02231EFC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, #1
	mov r2, r1
	mov r0, #2
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AEF4
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _02231F54 ; =MOD13_02231EB0
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231F54: .word MOD13_02231EB0

	arm_func_start MOD13_02231F58
MOD13_02231F58: ; 0x02231F58
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02231FF0 ; =0x02240544
	ldr r1, _02231FF4 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _02231FF8 ; =0x0224055C
	ldr r1, _02231FFC ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _02232000 ; =0x02240574
	ldr r1, _02232004 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02232008 ; =0x04001008
	ldr ip, _0223200C ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02232010 ; =0x04000008
	ldr r2, _02232014 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02232018 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02231FF0: .word 0x02240544
_02231FF4: .word 0x020C8D4C
_02231FF8: .word 0x0224055C
_02231FFC: .word 0x020C9550
_02232000: .word 0x02240574
_02232004: .word 0x020C908C
_02232008: .word 0x04001008
_0223200C: .word 0x0400100A
_02232010: .word 0x04000008
_02232014: .word 0x0400000A
_02232018: .word 0x0400000C

	arm_func_start MOD13_0223201C
MOD13_0223201C: ; 0x0223201C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223206C ; =0x02243134
	mov r1, #0
	strb r1, [r0]
	bl MOD13_02231F58
	mov r0, #8
	bl MOD13_0221F4CC
	mov r0, #0x38
	mvn r1, #0
	mov r2, #0
	bl MOD13_0221EE98
	mov r0, #1
	bl MOD13_0221F124
	mov r0, #0x27
	bl MOD13_0221F070
	ldr r0, _02232070 ; =MOD13_02231EFC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223206C: .word 0x02243134
_02232070: .word MOD13_02231EFC

	arm_func_start MOD13_02232074
MOD13_02232074: ; 0x02232074
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022320DC ; =0x02243138
	ldrb r0, [r0]
	cmp r0, #1
	bne _022320AC
	ldr r0, _022320E0 ; =MOD13_02232444
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022320AC:
	mov r0, #0xb
	bl MOD13_0223424C
	bl MOD13_0221EC9C
	ldr r1, _022320DC ; =0x02243138
	mov r2, #0
	ldr r0, _022320E4 ; =MOD13_022321B8
	strb r2, [r1]
	bl MOD13_022353A4
	ldr r0, _022320E8 ; =0x02232514
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022320DC: .word 0x02243138
_022320E0: .word MOD13_02232444
_022320E4: .word MOD13_022321B8
_022320E8: .word 0x02232514

	arm_func_start MOD13_022320EC
MOD13_022320EC: ; 0x022320EC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	beq _02232124
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r1, _0223214C ; =0x02243138
	mov r2, #3
	mov r0, #6
	strb r2, [r1]
	bl MOD13_0223424C
	b _02232138
_02232124:
	ldr r1, _0223214C ; =0x02243138
	mov r2, #1
	mov r0, #7
	strb r2, [r1]
	bl MOD13_0223424C
_02232138:
	bl MOD13_02235EB0
	ldr r0, _02232150 ; =MOD13_02232074
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223214C: .word 0x02243138
_02232150: .word MOD13_02232074

	arm_func_start MOD13_02232154
MOD13_02232154: ; 0x02232154
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E80
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _0223217C ; =MOD13_02232444
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223217C: .word MOD13_02232444

	arm_func_start MOD13_02232180
MOD13_02232180: ; 0x02232180
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02235E9C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #6
	bl MOD13_0223424C
	bl MOD13_02235EB0
	ldr r0, _022321B4 ; =MOD13_02232154
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022321B4: .word MOD13_02232154

	arm_func_start MOD13_022321B8
MOD13_022321B8: ; 0x022321B8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _022322AC ; =0x02243138
	ldrb r2, [r1]
	cmp r2, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _022322A4
_022321E0: ; jump table
	b _022321F0 ; case 0
	b _02232234 ; case 1
	b _02232250 ; case 2
	b _02232288 ; case 3
_022321F0:
	mov r0, #3
	strb r0, [r1]
	bl MOD13_022341E8
	mov r0, #0x12
	bl MOD13_0223424C
	mov r1, #1
	mov ip, #0
	mov r2, r1
	mov r0, #0x10
	mvn r3, #0
	str ip, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _022322B0 ; =MOD13_02232180
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02232234:
	mov r0, #1
	strb r0, [r1]
	bl MOD13_022341E8
	ldr r0, _022322B4 ; =MOD13_02232444
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02232250:
	bl MOD13_022341E8
	mov r0, #0
	bl MOD13_022353A4
	mov r1, #0
	mov r0, #0x11
	mov r2, #1
	mvn r3, #0
	str r1, [sp]
	bl MOD13_02235EFC
	bl MOD13_0221EC84
	ldr r0, _022322B8 ; =MOD13_022320EC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_02232288:
	mov r0, #2
	strb r0, [r1]
	bl MOD13_022341E8
	mov r0, #9
	bl MOD13_0223424C
	ldr r0, _022322B4 ; =MOD13_02232444
	bl MOD13_02222FBC
_022322A4:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022322AC: .word 0x02243138
_022322B0: .word MOD13_02232180
_022322B4: .word MOD13_02232444
_022322B8: .word MOD13_022320EC

	arm_func_start MOD13_022322BC
MOD13_022322BC: ; 0x022322BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022323BC ; =0x02243138
	ldrb r0, [r0]
	cmp r0, #2
	bne _022322FC
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_022322FC:
	bl MOD13_0221ECB4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_022353BC
	bl MOD13_0221E654
	mov r0, #0
	bl MOD13_0223A65C
	ldr r0, _022323BC ; =0x02243138
	ldrb r0, [r0]
	add r0, r0, #0xfe
	and r0, r0, #0xff
	cmp r0, #1
	bhi _02232344
	bl MOD13_0221EE54
	mov r0, #1
	mov r1, r0
	bl MOD13_0223AE98
_02232344:
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AE98
	ldr r0, _022323BC ; =0x02243138
	ldrb r0, [r0]
	cmp r0, #2
	bne _0223237C
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022323C0 ; =MOD13_02230714
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_0223237C:
	cmp r0, #3
	bne _022323A0
	mov r0, #2
	mov r1, #1
	bl MOD13_02222FA8
	ldr r0, _022323C4 ; =MOD13_0223201C
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
_022323A0:
	mov r0, #0
	mov r1, r0
	bl MOD13_02222FA8
	ldr r0, _022323C8 ; =MOD13_02231C04
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022323BC: .word 0x02243138
_022323C0: .word MOD13_02230714
_022323C4: .word MOD13_0223201C
_022323C8: .word MOD13_02231C04

	arm_func_start MOD13_022323CC
MOD13_022323CC: ; 0x022323CC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED28
	ldr r0, _0223243C ; =0x02243138
	ldrb r0, [r0]
	add r0, r0, #0xfe
	and r0, r0, #0xff
	cmp r0, #1
	bhi _02232418
	mov r1, #1
	mov r2, r1
	mov r0, #3
	mov r3, #8
	bl MOD13_0223A2A8
_02232418:
	mov r0, #3
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	ldr r0, _02232440 ; =MOD13_022322BC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223243C: .word 0x02243138
_02232440: .word MOD13_022322BC

	arm_func_start MOD13_02232444
MOD13_02232444: ; 0x02232444
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221EC84
	mov r0, #8
	bl MOD13_0223A10C
	ldr r0, _02232468 ; =MOD13_022323CC
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232468: .word MOD13_022323CC

	arm_func_start MOD13_0223246C
MOD13_0223246C: ; 0x0223246C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022324C0 ; =0x02243138
	ldrb r0, [r0]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_0221ED14
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022324C0 ; =0x02243138
	mov r1, #2
	strb r1, [r0]
	bl MOD13_022341E8
	mov r0, #7
	bl MOD13_0223424C
	ldr r0, _022324C4 ; =MOD13_02232444
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022324C0: .word 0x02243138
_022324C4: .word MOD13_02232444

	arm_func_start MOD13_022324C8
MOD13_022324C8: ; 0x022324C8
	bx lr

	arm_func_start MOD13_022324CC
MOD13_022324CC: ; 0x022324CC
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _022324F4
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
_022324F4:
	bl MOD13_02232730
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl MOD13_0221ECF4
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022324CC
	bl MOD13_022324C8
	bl MOD13_0223246C
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0221ED14
	mvn r1, #1
	cmp r0, r1
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD13_0221EC9C
	ldr r0, _02232560 ; =0x02232514
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232560: .word 0x02232514

	arm_func_start MOD13_02232564
MOD13_02232564: ; 0x02232564
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD13_0223A388
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #2
	bl MOD13_0221F0EC
	ldr r0, _02232598 ; =0x02232530
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232598: .word 0x02232530

	arm_func_start MOD13_0223259C
MOD13_0223259C: ; 0x0223259C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #2
	mov r1, #0
	mov r2, #0x15
	mov r3, #8
	bl MOD13_0223A2A8
	mov r0, #0
	mov r1, #0x15
	bl MOD13_0223AEF4
	ldr r0, _022325D4 ; =MOD13_02232564
	bl MOD13_02222FBC
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022325D4: .word MOD13_02232564

	arm_func_start MOD13_022325D8
MOD13_022325D8: ; 0x022325D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02232670 ; =0x02240588
	ldr r1, _02232674 ; =0x020C8D4C
	bl MOD13_0221F174
	ldr r0, _02232678 ; =0x022405A0
	ldr r1, _0223267C ; =0x020C9550
	bl MOD13_0221F174
	ldr r0, _02232680 ; =0x022405B8
	ldr r1, _02232684 ; =0x020C908C
	bl MOD13_0221F174
	ldr r1, _02232688 ; =0x04001008
	ldr ip, _0223268C ; =0x0400100A
	ldrh r0, [r1]
	ldr r3, _02232690 ; =0x04000008
	ldr r2, _02232694 ; =0x0400000A
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	ldrh r0, [ip]
	ldr r1, _02232698 ; =0x0400000C
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [ip]
	ldrh r0, [r3]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r3]
	ldrh r0, [r2]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r2]
	ldrh r0, [r1]
	bic r0, r0, #3
	orr r0, r0, #3
	strh r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232670: .word 0x02240588
_02232674: .word 0x020C8D4C
_02232678: .word 0x022405A0
_0223267C: .word 0x020C9550
_02232680: .word 0x022405B8
_02232684: .word 0x020C908C
_02232688: .word 0x04001008
_0223268C: .word 0x0400100A
_02232690: .word 0x04000008
_02232694: .word 0x0400000A
_02232698: .word 0x0400000C

	arm_func_start MOD13_0223269C
MOD13_0223269C: ; 0x0223269C
	stmdb sp!, {lr}
	sub sp, sp, #0x6c
	ldr r0, _02232724 ; =0x02243138
	mov r1, #0
	strb r1, [r0]
	bl MOD13_022325D8
	mov r0, #8
	bl MOD13_0221F4CC
	mov r0, #2
	bl MOD13_0221F124
	add r0, sp, #0x16
	bl OS_GetOwnerInfo
	add r1, sp, #0
	mov r0, #0
	mov r2, #0x16
	bl MIi_CpuClear16
	ldrh r2, [sp, #0x2e]
	add r0, sp, #0x1a
	add r1, sp, #0
	mov r2, r2, lsl #1
	bl MIi_CpuCopy16
	add r0, sp, #0
	mov r1, #0x28
	bl MOD13_0221EFA8
	mov r0, #0
	bl MOD13_0221E694
	ldr r0, _02232728 ; =MOD13_022321B8
	bl MOD13_022354F4
	mov r0, #0xb
	bl MOD13_0223424C
	ldr r0, _0223272C ; =MOD13_0223259C
	bl MOD13_02222FBC
	add sp, sp, #0x6c
	ldmia sp!, {pc}
	.align 2, 0
_02232724: .word 0x02243138
_02232728: .word MOD13_022321B8
_0223272C: .word MOD13_0223259C

	arm_func_start MOD13_02232730
MOD13_02232730: ; 0x02232730
	ldr r0, _0223274C ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_0223274C: .word 0x027FFFA8

	arm_func_start MOD13_02232750
MOD13_02232750: ; 0x02232750
	stmdb sp!, {r4, lr}
	ldr r1, _0223277C ; =0x02243140
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0x5000000
	mov r2, #0x200
	bl MIi_CpuCopy16
	mov r1, r4
	mov r0, #1
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223277C: .word 0x02243140

	arm_func_start MOD13_02232780
MOD13_02232780: ; 0x02232780
	ldr r2, _022327A0 ; =0x02243140
	ldr ip, _022327A4 ; =MOD13_0223C1C4
	str r0, [r2]
	ldr r1, _022327A8 ; =MOD13_02232750
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bx ip
	.align 2, 0
_022327A0: .word 0x02243140
_022327A4: .word MOD13_0223C1C4
_022327A8: .word MOD13_02232750

	arm_func_start MOD13_022327AC
MOD13_022327AC: ; 0x022327AC
	stmdb sp!, {r4, lr}
	ldr r1, _022327D8 ; =0x02243140
	mov r4, r0
	ldr r0, [r1]
	ldr r1, [r1, #4]
	mov r2, #0x20
	bl MIi_CpuCopy16
	mov r1, r4
	mov r0, #1
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_022327D8: .word 0x02243140

	arm_func_start MOD13_022327DC
MOD13_022327DC: ; 0x022327DC
	stmdb sp!, {r4, lr}
	add r4, r0, r1, lsl #5
	mov r0, r2, lsl #5
	ldr ip, _02232810 ; =0x02243140
	add lr, r0, #0x5000000
	ldr r1, _02232814 ; =MOD13_022327AC
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	str r4, [ip]
	str lr, [ip, #4]
	bl MOD13_0223C1C4
	ldmia sp!, {r4, pc}
	.align 2, 0
_02232810: .word 0x02243140
_02232814: .word MOD13_022327AC

	arm_func_start MOD13_02232818
MOD13_02232818: ; 0x02232818
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02232874 ; =0x0224313C
	ldr r1, [r0]
	ldrb r0, [r1, #0x604]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	add r0, r1, #4
	mov r1, #0x600
	bl DC_FlushRange
	ldr r0, _02232874 ; =0x0224313C
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x600
	add r0, r0, #4
	bl GX_LoadBG2Scr
	ldr r0, _02232874 ; =0x0224313C
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x604]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232874: .word 0x0224313C

	arm_func_start MOD13_02232878
MOD13_02232878: ; 0x02232878
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr ip, _022328CC ; =0x0224313C
	mov r7, r3
	ldr r3, [ip]
	mov r8, r0
	add r0, r3, #4
	add r6, r0, r1, lsl #1
	mov r5, #0
	cmp r7, #0
	ldmleia sp!, {r4, r5, r6, r7, r8, pc}
	mov r4, r2, lsl #1
_022328A4:
	mov r0, r8
	mov r1, r6
	mov r2, r4
	bl MIi_CpuCopy16
	add r5, r5, #1
	cmp r5, r7
	add r8, r8, #0x40
	add r6, r6, #0x40
	blt _022328A4
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_022328CC: .word 0x0224313C

	arm_func_start MOD13_022328D0
MOD13_022328D0: ; 0x022328D0
	ldr r0, _022328E4 ; =0x0224313C
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x604]
	bx lr
	.align 2, 0
_022328E4: .word 0x0224313C

	arm_func_start MOD13_022328E8
MOD13_022328E8: ; 0x022328E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02232914 ; =0x0224313C
	mov r0, #1
	ldr r1, [r1]
	ldr r1, [r1]
	bl MOD13_0223C104
	ldr r0, _02232914 ; =0x0224313C
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232914: .word 0x0224313C

	arm_func_start MOD13_02232918
MOD13_02232918: ; 0x02232918
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, _0223296C ; =0x00000608
	mov r1, #4
	bl MOD13_0223AFE0
	mov ip, r0
	ldr r3, _02232970 ; =0x0224313C
	mov r0, r4
	add r1, ip, #4
	mov r2, #0x600
	str ip, [r3]
	bl MIi_CpuCopyFast
	ldr r1, _02232974 ; =MOD13_02232818
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02232970 ; =0x0224313C
	ldr r1, [r1]
	str r0, [r1]
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223296C: .word 0x00000608
_02232970: .word 0x0224313C
_02232974: .word MOD13_02232818

	arm_func_start MOD13_02232978
MOD13_02232978: ; 0x02232978
	stmdb sp!, {r4, lr}
	ldr r1, _022329B0 ; =0x02243148
	mov r4, r0
	ldr r0, [r1]
	mvn r1, #0
	ldrh r3, [r0, #0x12]
	ldrh r2, [r0, #0x10]
	ldr r0, [r0]
	add r3, r4, r3
	bl MOD13_02239888
	ldr r0, _022329B0 ; =0x02243148
	ldr r0, [r0]
	strb r4, [r0, #0x1a]
	ldmia sp!, {r4, pc}
	.align 2, 0
_022329B0: .word 0x02243148

	arm_func_start MOD13_022329B4
MOD13_022329B4: ; 0x022329B4
	ldr r2, _02232A8C ; =0x02243148
	cmp r0, #4
	ldr r3, [r2]
	ldrh r3, [r3, #0x10]
	strh r3, [r1]
	ldrh r3, [r1]
	add r3, r3, #0xc
	strh r3, [r1, #4]
	addls pc, pc, r0, lsl #2
	bx lr
_022329DC: ; jump table
	bx lr ; case 0
	b _022329F0 ; case 1
	b _02232A24 ; case 2
	b _02232A44 ; case 3
	b _02232A68 ; case 4
_022329F0:
	ldr r3, [r2]
	ldr r0, _02232A90 ; =0x0223F590
	ldrh ip, [r3, #0x12]
	ldrb r3, [r3, #0x1a]
	add r3, ip, r3
	strh r3, [r1, #2]
	ldr r2, [r2]
	ldrh r3, [r1, #2]
	ldrb r2, [r2, #0x1b]
	ldrb r0, [r0, r2]
	add r0, r3, r0
	strh r0, [r1, #6]
	bx lr
_02232A24:
	ldr r0, [r2]
	ldrh r0, [r0, #0x12]
	sub r0, r0, #0xd
	strh r0, [r1, #2]
	ldr r0, [r2]
	ldrh r0, [r0, #0x12]
	strh r0, [r1, #6]
	bx lr
_02232A44:
	ldr r0, [r2]
	ldrh r2, [r0, #0x12]
	ldrb r0, [r0, #0x19]
	add r0, r2, r0
	strh r0, [r1, #2]
	ldrh r0, [r1, #2]
	add r0, r0, #0xd
	strh r0, [r1, #6]
	bx lr
_02232A68:
	ldr r0, [r2]
	ldrh r0, [r0, #0x12]
	strh r0, [r1, #2]
	ldr r0, [r2]
	ldrh r2, [r1, #2]
	ldrb r0, [r0, #0x19]
	add r0, r2, r0
	strh r0, [r1, #6]
	bx lr
	.align 2, 0
_02232A8C: .word 0x02243148
_02232A90: .word 0x0223F590

	arm_func_start MOD13_02232A94
MOD13_02232A94: ; 0x02232A94
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	mov r5, #2
	add r4, sp, #0
_02232AA4:
	mov r0, r5
	mov r1, r4
	bl MOD13_022329B4
	mov r0, r4
	bl MOD13_0223B320
	cmp r0, #0
	addne sp, sp, #0xc
	movne r0, r5
	ldmneia sp!, {r4, r5, pc}
	add r5, r5, #1
	cmp r5, #3
	ble _02232AA4
	mov r0, #0
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}

	arm_func_start MOD13_02232AE0
MOD13_02232AE0: ; 0x02232AE0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	add r1, sp, #0
	mov r0, #1
	bl MOD13_022329B4
	add r0, sp, #0
	bl MOD13_0223B248
	cmp r0, #0
	addne sp, sp, #0xc
	movne r0, #1
	ldmneia sp!, {r4, r5, pc}
	mov r5, #2
	add r4, sp, #0
_02232B14:
	mov r0, r5
	mov r1, r4
	bl MOD13_022329B4
	mov r0, r4
	bl MOD13_0223B248
	cmp r0, #0
	addne sp, sp, #0xc
	movne r0, r5
	ldmneia sp!, {r4, r5, pc}
	add r5, r5, #1
	cmp r5, #3
	ble _02232B14
	add r1, sp, #0
	mov r0, #4
	bl MOD13_022329B4
	add r0, sp, #0
	bl MOD13_0223B2B4
	cmp r0, #0
	movne r0, #4
	moveq r0, #0
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}

	arm_func_start MOD13_02232B6C
MOD13_02232B6C: ; 0x02232B6C
	stmdb sp!, {lr}
	sub sp, sp, #4
	add r0, sp, #0
	bl MOD13_0223B14C
	ldr r0, _02232BD8 ; =0x02243148
	ldr r2, _02232BDC ; =0x0223F590
	ldr ip, [r0]
	ldrh r1, [sp, #2]
	ldrb r3, [ip, #0x1b]
	ldrh r0, [ip, #0x12]
	ldrb r2, [r2, r3]
	sub r1, r1, r0
	mov r0, r2, lsr #1
	subs r0, r1, r0
	movmi r0, #0
	bmi _02232BBC
	ldrb r1, [ip, #0x19]
	sub r1, r1, r2
	cmp r0, r1
	movge r0, r1
_02232BBC:
	bl MOD13_02232978
	ldr r0, _02232BD8 ; =0x02243148
	mov r1, #3
	ldr r0, [r0]
	strb r1, [r0, #0x1d]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232BD8: .word 0x02243148
_02232BDC: .word 0x0223F590

	arm_func_start MOD13_02232BE0
MOD13_02232BE0: ; 0x02232BE0
	ldr r1, _02232C08 ; =0x02243148
	cmp r0, #2
	ldr r1, [r1]
	strb r0, [r1, #0x1c]
	ldr r0, _02232C08 ; =0x02243148
	moveq r1, #4
	ldr r0, [r0]
	movne r1, #6
	strb r1, [r0, #0x1d]
	bx lr
	.align 2, 0
_02232C08: .word 0x02243148

	arm_func_start MOD13_02232C0C
MOD13_02232C0C: ; 0x02232C0C
	stmdb sp!, {r4, lr}
	ldr r1, _02232C80 ; =0x02243148
	ldr r1, [r1]
	ldrb r1, [r1, #0x1a]
	subs r4, r1, r0
	rsbmi r4, r4, #0
	cmp r4, #2
	movlt r0, #0
	blt _02232C48
	cmp r4, #6
	movge r0, #0x7f
	bge _02232C48
	rsb r1, r4, #6
	mov r0, #0x7f
	bl FX_DivS32
_02232C48:
	bl MOD13_0223422C
	cmp r4, #2
	mvnlt r1, #0xff
	blt _02232C74
	cmp r4, #6
	movge r1, #0x100
	bge _02232C74
	rsb r1, r4, #6
	mov r0, #0x200
	bl FX_DivS32
	sub r1, r0, #0x100
_02232C74:
	ldr r0, _02232C84 ; =0x0000FFFF
	bl MOD13_02234208
	ldmia sp!, {r4, pc}
	.align 2, 0
_02232C80: .word 0x02243148
_02232C84: .word 0x0000FFFF

	arm_func_start MOD13_02232C88
MOD13_02232C88: ; 0x02232C88
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r0, _02232D4C ; =0x0223F75C
	bl MOD13_0223B320
	cmp r0, #0
	beq _02232D24
	add r0, sp, #0
	bl MOD13_0223B14C
	ldr r0, _02232D50 ; =0x02243148
	ldrh r1, [sp]
	ldr r3, [r0]
	ldrh r0, [r3, #0x10]
	sub r0, r0, #0x1e
	cmp r1, r0
	blt _02232D24
	ldrh r1, [sp, #2]
	ldrh r0, [r3, #0x16]
	ldrb r2, [r3, #0x18]
	sub r0, r1, r0
	adds r4, r2, r0
	movmi r4, #0
	bmi _02232CFC
	ldrb r1, [r3, #0x1b]
	ldr r0, _02232D54 ; =0x0223F590
	ldrb r2, [r3, #0x19]
	ldrb r0, [r0, r1]
	sub r0, r2, r0
	cmp r4, r0
	movge r4, r0
_02232CFC:
	mov r0, r4
	bl MOD13_02232C0C
	mov r0, r4
	bl MOD13_02232978
	ldr r0, _02232D50 ; =0x02243148
	mov r1, #2
	ldr r0, [r0]
	add sp, sp, #8
	strb r1, [r0, #0x1d]
	ldmia sp!, {r4, pc}
_02232D24:
	bl MOD13_022341E8
	ldr r0, _02232D50 ; =0x02243148
	mov r3, #0
	ldr r2, [r0]
	mov r1, #3
	strb r3, [r2, #0x1c]
	ldr r0, [r0]
	strb r1, [r0, #0x1d]
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02232D4C: .word 0x0223F75C
_02232D50: .word 0x02243148
_02232D54: .word 0x0223F590

	arm_func_start MOD13_02232D58
MOD13_02232D58: ; 0x02232D58
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02232F10 ; =0x02243148
	mov r2, #0
	ldr r1, [r0]
	strb r2, [r1, #0x1d]
	ldr r1, [r0]
	ldrb r0, [r1, #0x1c]
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _02232F08
_02232D84: ; jump table
	b _02232D94 ; case 0
	b _02232E5C ; case 1
	b _02232E68 ; case 2
	b _02232EBC ; case 3
_02232D94:
	ldrb r0, [r1, #0x1e]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02232AE0
	cmp r0, #4
	addls pc, pc, r0, lsl #2
	b _02232F08
_02232DB4: ; jump table
	b _02232F08 ; case 0
	b _02232DC8 ; case 1
	b _02232E30 ; case 2
	b _02232E40 ; case 3
	b _02232E50 ; case 4
_02232DC8:
	ldr r0, _02232F10 ; =0x02243148
	ldr r0, [r0]
	ldrb r0, [r0, #0x1b]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0x16
	bl MOD13_0223424C
	mov r0, #0
	bl MOD13_0223422C
	ldr r0, _02232F10 ; =0x02243148
	mov r2, #1
	ldr r1, [r0]
	strb r2, [r1, #0x1d]
	ldr r0, [r0]
	add r0, r0, #0x14
	bl MOD13_0223B14C
	ldr r0, _02232F10 ; =0x02243148
	mov r1, #1
	ldr r3, [r0]
	add sp, sp, #4
	ldrb r2, [r3, #0x1a]
	strb r2, [r3, #0x18]
	ldr r0, [r0]
	strb r1, [r0, #0x1c]
	ldmia sp!, {pc}
_02232E30:
	mov r0, #2
	bl MOD13_02232BE0
	add sp, sp, #4
	ldmia sp!, {pc}
_02232E40:
	mov r0, #3
	bl MOD13_02232BE0
	add sp, sp, #4
	ldmia sp!, {pc}
_02232E50:
	bl MOD13_02232B6C
	add sp, sp, #4
	ldmia sp!, {pc}
_02232E5C:
	bl MOD13_02232C88
	add sp, sp, #4
	ldmia sp!, {pc}
_02232E68:
	mov r0, #2
	bl MOD13_02232A94
	cmp r0, #2
	beq _02232E9C
	ldr r0, _02232F10 ; =0x02243148
	mov r3, #5
	ldr r2, [r0]
	mov r1, #0
	strb r3, [r2, #0x1d]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x1c]
	ldmia sp!, {pc}
_02232E9C:
	bl MOD13_02232AE0
	cmp r0, #2
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #2
	bl MOD13_02232BE0
	add sp, sp, #4
	ldmia sp!, {pc}
_02232EBC:
	mov r0, #3
	bl MOD13_02232A94
	cmp r0, #3
	beq _02232EF0
	ldr r0, _02232F10 ; =0x02243148
	mov r3, #7
	ldr r2, [r0]
	mov r1, #0
	strb r3, [r2, #0x1d]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0x1c]
	ldmia sp!, {pc}
_02232EF0:
	bl MOD13_02232AE0
	cmp r0, #3
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #3
	bl MOD13_02232BE0
_02232F08:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232F10: .word 0x02243148

	arm_func_start MOD13_02232F14
MOD13_02232F14: ; 0x02232F14
	ldr r0, _02232F28 ; =0x02243148
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x1e]
	bx lr
	.align 2, 0
_02232F28: .word 0x02243148

	arm_func_start MOD13_02232F2C
MOD13_02232F2C: ; 0x02232F2C
	ldr r0, _02232F40 ; =0x02243148
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x1e]
	bx lr
	.align 2, 0
_02232F40: .word 0x02243148

	arm_func_start MOD13_02232F44
MOD13_02232F44: ; 0x02232F44
	ldr ip, _02232F4C ; =MOD13_02232978
	bx ip
	.align 2, 0
_02232F4C: .word MOD13_02232978

	arm_func_start MOD13_02232F50
MOD13_02232F50: ; 0x02232F50
	ldr r0, _02232F60 ; =0x02243148
	ldr r0, [r0]
	ldrb r0, [r0, #0x1d]
	bx lr
	.align 2, 0
_02232F60: .word 0x02243148

	arm_func_start MOD13_02232F64
MOD13_02232F64: ; 0x02232F64
	ldr r0, _02232F74 ; =0x02243148
	ldr r0, [r0]
	ldrb r0, [r0, #0x1a]
	bx lr
	.align 2, 0
_02232F74: .word 0x02243148

	arm_func_start MOD13_02232F78
MOD13_02232F78: ; 0x02232F78
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02232FB4 ; =0x02243148
	mov r0, #0
	ldr r1, [r1]
	ldr r1, [r1, #0xc]
	bl MOD13_0223C104
	ldr r0, _02232FB4 ; =0x02243148
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD13_02239AE8
	ldr r0, _02232FB4 ; =0x02243148
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02232FB4: .word 0x02243148

	arm_func_start MOD13_02232FB8
MOD13_02232FB8: ; 0x02232FB8
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r6, r0
	mov r7, r1
	mov r0, #0x20
	mov r1, #4
	mov r5, r2
	mov r4, r3
	bl MOD13_0223AFE0
	ldr r2, _0223308C ; =0x02243148
	ldr ip, [sp, #0x18]
	str r0, [r2]
	strb r6, [r0, #0x1b]
	ldr r1, [r2]
	mov r0, r5
	strb r7, [r1, #0x19]
	ldr r3, [r2]
	mov r1, r4
	strb ip, [r3, #0x1a]
	ldr r2, [r2]
	add r2, r2, #0x10
	bl MOD13_0223ABC0
	ldr r1, _02233090 ; =0x0223F58C
	mov r0, #0
	ldrb r1, [r1, r6]
	mov r2, #1
	bl MOD13_02239E0C
	mov r2, r5
	ldr r5, _0223308C ; =0x02243148
	ldr r3, [sp, #0x18]
	ldr r6, [r5]
	mvn r1, #0
	str r0, [r6]
	ldr r0, [r5]
	add r3, r4, r3
	ldr r0, [r0]
	bl MOD13_02239888
	mov r0, r5
	ldr r0, [r0]
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #1
	bl MOD13_02239814
	mov r0, #0
	ldr r1, _02233094 ; =MOD13_02232D58
	mov r2, r0
	mov r3, #0x80
	bl MOD13_0223C1C4
	mov r1, r5
	ldr r1, [r1]
	str r0, [r1, #0xc]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0223308C: .word 0x02243148
_02233090: .word 0x0223F58C
_02233094: .word MOD13_02232D58

	arm_func_start MOD13_02233098
MOD13_02233098: ; 0x02233098
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xac
	ldr r1, _022332AC ; =0x0224314C
	str r0, [sp]
	ldr r2, [r1]
	mov r1, #0x400
	add r0, r2, #0xf00
	add r2, r2, #0x1300
	str r2, [sp, #4]
	bl DC_InvalidateRange
	ldr r0, [sp]
	ldrh r1, [r0, #0xe]
	mov r0, #0
	str r0, [sp, #8]
	cmp r1, #0
	addle sp, sp, #0xac
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x20]
	str r0, [sp, #0x18]
	mov r0, #0x20
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0x24]
	mov r0, #1
	ldr fp, _022332B0 ; =0x0223F598
	add r5, sp, #0x28
	mov r6, #6
	mov r4, #4
	str r0, [sp, #0x1c]
_02233114:
	ldr r1, [sp]
	ldr r0, [sp, #8]
	add r0, r1, r0, lsl #2
	ldr sl, [r0, #0x10]
	ldrb r0, [sl, #0xc]
	cmp r0, #0
	beq _02233284
	ldrh r0, [sl, #0x3c]
	cmp r0, #0
	bne _02233284
	ldr sb, [sp, #0xc]
	ldr r8, [sp, #4]
	add r7, sl, #4
_02233148:
	mov r0, r7
	add r1, r8, #0x20
	mov r2, r6
	bl memcmp
	cmp r0, #0
	beq _02233170
	add r8, r8, #0x2a
	add sb, sb, #1
	cmp sb, #0x14
	blt _02233148
_02233170:
	cmp sb, #0x14
	bne _022331B4
	ldr sb, [sp, #0x10]
	ldr r7, [sp, #4]
_02233180:
	add r0, r7, #0x20
	mov r1, fp
	mov r2, r6
	bl memcmp
	cmp r0, #0
	beq _022331A8
	add r7, r7, #0x2a
	add sb, sb, #1
	cmp sb, #0x14
	blt _02233180
_022331A8:
	cmp sb, #0x14
	addeq sp, sp, #0xac
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_022331B4:
	ldr r0, [sp, #4]
	mov r1, #0x2a
	mla r7, sb, r1, r0
	add r0, sl, #4
	add r1, r7, #0x20
	mov r2, r6
	bl MI_CpuCopy8
	ldr r2, [sp, #0x14]
	add r0, sl, #0xc
	mov r1, r7
	bl MI_CpuCopy8
	ldr r1, [sp]
	ldr r0, [sp, #8]
	add r0, r1, r0, lsl #1
	ldrh r0, [r0, #0x50]
	strh r0, [r7, #0x26]
	ldrh r0, [sl, #0x2c]
	ands r0, r0, #0x10
	ldreq r0, [sp, #0x18]
	streqb r0, [r7, #0x28]
	beq _02233284
	ldr r0, [sp, #0x1c]
	mov r1, sl
	strb r0, [r7, #0x28]
	mov r0, r5
	bl WM_GetOtherElements
	ldrb r8, [sp, #0x28]
	ldr sb, [sp, #0x20]
	cmp r8, #0
	ble _02233284
_0223322C:
	add r1, r5, sb, lsl #3
	ldrb r0, [r1, #4]
	cmp r0, #0x30
	ldreq r0, [sp, #0x24]
	streqb r0, [r7, #0x28]
	beq _02233284
	cmp r0, #0xdd
	bne _02233278
	ldrb r0, [r1, #5]
	cmp r0, #4
	blo _02233278
	ldr r0, [r1, #8]
	ldr r1, _022332B4 ; =0x0223F594
	mov r2, r4
	bl memcmp
	cmp r0, #0
	ldreq r0, [sp, #0x24]
	streqb r0, [r7, #0x28]
	beq _02233284
_02233278:
	add sb, sb, #1
	cmp sb, r8
	blt _0223322C
_02233284:
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	ldr r0, [sp]
	ldrh r1, [r0, #0xe]
	ldr r0, [sp, #8]
	cmp r0, r1
	blt _02233114
	add sp, sp, #0xac
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022332AC: .word 0x0224314C
_022332B0: .word 0x0223F598
_022332B4: .word 0x0223F594

	arm_func_start MOD13_022332B8
MOD13_022332B8: ; 0x022332B8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r1, [r0, #2]
	cmp r1, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r1, _02233338 ; =0x0224314C
	ldr r1, [r1]
	add r1, r1, #0x1000
	ldrb r1, [r1, #0xe4c]
	cmp r1, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrh r1, [r0]
	cmp r1, #0x26
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrh r1, [r0, #8]
	cmp r1, #4
	beq _02233320
	cmp r1, #5
	bne _0223332C
	bl MOD13_02233098
	bl MOD13_0223344C
	add sp, sp, #4
	ldmia sp!, {pc}
_02233320:
	bl MOD13_0223344C
	add sp, sp, #4
	ldmia sp!, {pc}
_0223332C:
	bl OS_Terminate
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02233338: .word 0x0224314C

	arm_func_start MOD13_0223333C
MOD13_0223333C: ; 0x0223333C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r1, _02233394 ; =0x0224314C
	mov r4, #0
	ldr r1, [r1]
	mov r8, r4
	add r1, r1, #0x1300
	str r1, [r0]
	ldr r7, [r0]
	ldr r6, _02233398 ; =0x0223F598
	mov r5, #6
_02233364:
	mov r1, r6
	mov r2, r5
	add r0, r7, #0x20
	bl memcmp
	cmp r0, #0
	add r8, r8, #1
	addne r4, r4, #1
	cmp r8, #0x14
	add r7, r7, #0x2a
	blt _02233364
	mov r0, r4
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02233394: .word 0x0224314C
_02233398: .word 0x0223F598

	arm_func_start MOD13_0223339C
MOD13_0223339C: ; 0x0223339C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _02233440 ; =0x0224314C
	mov r3, #1
	ldr r0, [r2]
	ldr r1, _02233444 ; =0x0000168C
	add r0, r0, #0x1000
	strb r3, [r0, #0xe4c]
	ldr r0, [r2]
	add r0, r0, r1
	bl WM_ReadStatus
	ldr r0, _02233440 ; =0x0224314C
	ldr r0, [r0]
	add r0, r0, #0x1600
	ldrh r0, [r0, #0x8c]
	cmp r0, #2
	beq _02233424
	ldr r0, _02233448 ; =MOD13_022332B8
	bl WM_Reset
	cmp r0, #2
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
_022333F8:
	ldr r1, _02233440 ; =0x0224314C
	ldr r0, _02233444 ; =0x0000168C
	ldr r1, [r1]
	add r0, r1, r0
	bl WM_ReadStatus
	ldr r0, _02233440 ; =0x0224314C
	ldr r0, [r0]
	add r0, r0, #0x1600
	ldrh r0, [r0, #0x8c]
	cmp r0, #2
	bne _022333F8
_02233424:
	ldr r0, _02233448 ; =MOD13_022332B8
	bl WM_End
	cmp r0, #2
	movne r0, #0
	moveq r0, #1
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02233440: .word 0x0224314C
_02233444: .word 0x0000168C
_02233448: .word MOD13_022332B8

	arm_func_start MOD13_0223344C
MOD13_0223344C: ; 0x0223344C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02233480 ; =0x0224314C
	ldr r1, _02233484 ; =0x00001648
	ldr r2, [r0]
	ldr r0, _02233488 ; =MOD13_022332B8
	add r1, r2, r1
	bl WM_StartScanEx
	cmp r0, #2
	moveq r0, #1
	movne r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02233480: .word 0x0224314C
_02233484: .word 0x00001648
_02233488: .word MOD13_022332B8

	arm_func_start MOD13_0223348C
MOD13_0223348C: ; 0x0223348C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _0223355C ; =0x0224314C
	mov r0, #0
	ldr r1, [r1]
	mov r2, #0x348
	add r1, r1, #0x1300
	bl MIi_CpuClear16
	ldr r0, _0223355C ; =0x0224314C
	ldr r1, _02233560 ; =MOD13_022332B8
	ldr r0, [r0]
	mov r2, #3
	bl WM_Initialize
	cmp r0, #2
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
_022334D0:
	ldr r1, _0223355C ; =0x0224314C
	ldr r0, _02233564 ; =0x0000168C
	ldr r1, [r1]
	add r0, r1, r0
	bl WM_ReadStatus
	ldr r0, _0223355C ; =0x0224314C
	ldr r5, [r0]
	add r0, r5, #0x1600
	ldrh r0, [r0, #0x8c]
	cmp r0, #2
	bne _022334D0
	ldr r0, _02233568 ; =0x00001648
	ldr r4, _0223356C ; =0x0223F5A0
	add lr, r5, r0
	mov ip, #4
_0223350C:
	ldmia r4!, {r0, r1, r2, r3}
	stmia lr!, {r0, r1, r2, r3}
	subs ip, ip, #1
	bne _0223350C
	ldr r0, [r4]
	add r1, r5, #0xf00
	str r0, [lr]
	add r0, r5, #0x1000
	str r1, [r0, #0x648]
	bl WM_GetDispersionScanPeriod
	ldr r1, _0223355C ; =0x0224314C
	ldr r1, [r1]
	add r1, r1, #0x1600
	strh r0, [r1, #0x50]
	bl MOD13_0223344C
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223355C: .word 0x0224314C
_02233560: .word MOD13_022332B8
_02233564: .word 0x0000168C
_02233568: .word 0x00001648
_0223356C: .word 0x0223F5A0

	arm_func_start MOD13_02233570
MOD13_02233570: ; 0x02233570
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022335A8 ; =0x0224314C
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
_0223358C:
	bl WM_GetAllowedChannel
	cmp r0, #0x8000
	bne _0223358C
	ldr r0, _022335A8 ; =0x0224314C
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022335A8: .word 0x0224314C

	arm_func_start MOD13_022335AC
MOD13_022335AC: ; 0x022335AC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022335E4 ; =0x0224314C
	ldr r0, [r0]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _022335E8 ; =0x00001E60
	mov r1, #0x20
	bl MOD13_0223AFE0
	ldr r1, _022335E4 ; =0x0224314C
	str r0, [r1]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022335E4: .word 0x0224314C
_022335E8: .word 0x00001E60

	arm_func_start MOD13_022335EC
MOD13_022335EC: ; 0x022335EC
	cmp r0, #0x39
	subls r0, r0, #0x30
	bxls lr
	cmp r0, #0x46
	subls r0, r0, #0x37
	subhi r0, r0, #0x57
	bx lr

	arm_func_start MOD13_02233608
MOD13_02233608: ; 0x02233608
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov sl, r0
	mov sb, r1
	add r0, sp, #0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r8, #0
	mov r7, r8
	add r6, sp, #0
	mov fp, r8
	mov r4, #0x20
	mov r5, #3
_02233640:
	mov r1, r6
	mov r2, r5
	add r0, sl, r7
	bl MI_CpuCopy8
	mov r2, fp
	mov r1, r6
_02233658:
	ldrb r0, [r1]
	cmp r0, #0
	bne _02233674
	add r2, r2, #1
	cmp r2, #3
	strb r4, [r1], #1
	blt _02233658
_02233674:
	mov r0, r6
	bl atol
	strb r0, [sb, r8]
	add r8, r8, #1
	cmp r8, #4
	add r7, r7, #3
	blt _02233640
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}

	arm_func_start MOD13_02233698
MOD13_02233698: ; 0x02233698
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x14
	ldr r1, _02233800 ; =0x02243150
	mov r7, r0
	ldr r0, [r1]
	mov r4, #0
	add r2, r0, r7, lsl #8
	ldrb r6, [r2, #0xe7]
	mov r3, #1
	add r0, sp, #4
	mov r1, r4
	mov r2, #0x10
	mov r5, r3, lsl r7
	bl MI_CpuFill8
	add r0, sp, #4
	mov r2, #1
	str r2, [r0, r7, lsl #2]
	cmp r7, #2
	bgt _02233778
	ldr r0, _02233800 ; =0x02243150
	ldr r0, [r0]
	ldrb r1, [r0, #0xef]
	ands r1, r1, r5
	movne r4, r2
	cmp r6, #0xff
	bne _0223373C
	cmp r4, #0
	beq _0223373C
	ldrb r2, [r0, #0xef]
	mvn r3, r5
	ldr r1, _02233800 ; =0x02243150
	and r2, r2, r3
	strb r2, [r0, #0xef]
	ldr r2, [r1]
	mov r0, #1
	ldrb r1, [r2, #0x1ef]
	and r1, r1, r3
	strb r1, [r2, #0x1ef]
	str r0, [sp, #8]
	str r0, [sp, #4]
	b _02233778
_0223373C:
	cmp r6, #0xff
	beq _02233778
	cmp r4, #0
	bne _02233778
	ldrb r3, [r0, #0xef]
	ldr r1, _02233800 ; =0x02243150
	mov r2, #1
	orr r3, r3, r5
	strb r3, [r0, #0xef]
	ldr r1, [r1]
	ldrb r0, [r1, #0x1ef]
	orr r0, r0, r5
	strb r0, [r1, #0x1ef]
	str r2, [sp, #8]
	str r2, [sp, #4]
_02233778:
	mov r7, #0
	mov r6, r7
	ldr sb, _02233800 ; =0x02243150
	add r5, sp, #4
	mov r4, #0xfe
	ldr r8, _02233804 ; =0x000004F8
_02233790:
	ldr r0, [r5, r7, lsl #2]
	cmp r0, #0
	beq _022337BC
	ldr r1, [sb]
	mov r2, r4
	add r0, r1, r8
	add r1, r1, r6
	bl MATH_CalcCRC16
	ldr r1, [sb]
	add r1, r1, r7, lsl #8
	strh r0, [r1, #0xfe]
_022337BC:
	add r7, r7, #1
	cmp r7, #4
	add r6, r6, #0x100
	blt _02233790
	mov r0, #0x100
	mov r1, #0x20
	bl MOD13_0223B004
	mov r2, r0
	ldr r0, _02233800 ; =0x02243150
	add r1, sp, #4
	ldr r0, [r0]
	str r2, [sp]
	bl FUN_02095CDC
	add r0, sp, #0
	bl MOD13_0223AF90
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_02233800: .word 0x02243150
_02233804: .word 0x000004F8

	arm_func_start MOD13_02233808
MOD13_02233808: ; 0x02233808
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x18
	ldr r1, _022338B4 ; =0x02243150
	mov r0, #0
	ldr r1, [r1]
	mov r2, #0x400
	bl MIi_CpuClear16
	mov r3, #0
	ldr r0, _022338B4 ; =0x02243150
	mov r2, #0xff
_02233830:
	ldr r1, [r0]
	add r1, r1, r3, lsl #8
	add r3, r3, #1
	strb r2, [r1, #0xe7]
	cmp r3, #3
	blt _02233830
	add r0, sp, #0
	bl FUN_020967A4
	add r0, sp, #0
	bl FUN_02095330
	mov r6, #0
	ldr r4, _022338B4 ; =0x02243150
	mov r8, r0
	mov r7, r6
	mov r5, #0xe
_0223386C:
	ldr r1, [r4]
	mov r0, r8
	add r1, r1, r7
	mov r2, r5
	add r1, r1, #0xf0
	bl MI_CpuCopy8
	add r6, r6, #1
	cmp r6, #2
	add r7, r7, #0x100
	blt _0223386C
	mov r4, #0
_02233898:
	mov r0, r4
	bl MOD13_02233698
	add r4, r4, #1
	cmp r4, #4
	blt _02233898
	add sp, sp, #0x18
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_022338B4: .word 0x02243150

	arm_func_start MOD13_022338B8
MOD13_022338B8: ; 0x022338B8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _022338F8 ; =0x02243150
	mov r5, r0
	ldr r0, [r1]
	mov r1, #0
	add r4, r0, r5, lsl #8
	mov r0, r4
	mov r2, #0xef
	bl MI_CpuFill8
	mov r1, #0xff
	mov r0, r5
	strb r1, [r4, #0xe7]
	bl MOD13_02233698
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022338F8: .word 0x02243150

	arm_func_start MOD13_022338FC
MOD13_022338FC: ; 0x022338FC
	ldr r0, _02233908 ; =0x02243150
	ldr r0, [r0]
	bx lr
	.align 2, 0
_02233908: .word 0x02243150

	arm_func_start MOD13_0223390C
MOD13_0223390C: ; 0x0223390C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _02233A20 ; =0x02243150
	mov r5, r0
	ldr r0, [r1]
	mov r1, #0
	add r4, r0, #0x400
	mov r0, r4
	mov r2, #0xef
	bl MI_CpuFill8
	mov r0, r5
	add r1, r4, #0xd1
	mov r2, #5
	bl MI_CpuCopy8
	add r0, r5, #6
	add r1, r4, #0xd6
	mov r2, #5
	bl MI_CpuCopy8
	add r0, r5, #0xc
	add r1, r4, #0xdb
	mov r2, #5
	bl MI_CpuCopy8
	add r0, r5, #0x12
	add r1, r4, #0xe0
	mov r2, #5
	bl MI_CpuCopy8
	add r0, r5, #0x18
	add r1, r4, #0x60
	mov r2, #0x20
	bl MI_CpuCopy8
	add r0, r5, #0x39
	add r1, r4, #0x80
	mov r2, #0xd
	bl MI_CpuCopy8
	add r0, r5, #0x47
	add r1, r4, #0x90
	mov r2, #0xd
	bl MI_CpuCopy8
	add r0, r5, #0x55
	add r1, r4, #0xa0
	mov r2, #0xd
	bl MI_CpuCopy8
	add r0, r5, #0x63
	add r1, r4, #0xb0
	mov r2, #0xd
	bl MI_CpuCopy8
	add r0, r5, #0x71
	add r1, r4, #0x40
	mov r2, #0x20
	bl MI_CpuCopy8
	ldrb r1, [r4, #0xe6]
	mov r3, #1
	add r0, r4, #0xf0
	bic r1, r1, #3
	orr r1, r1, #2
	strb r1, [r4, #0xe6]
	ldrb ip, [r4, #0xe6]
	mov r1, #0
	mov r2, #4
	bic ip, ip, #0xfc
	strb ip, [r4, #0xe6]
	strb r3, [r4, #0xe7]
	bl MI_CpuFill8
	mov r0, #1
	strb r0, [r4, #0xf5]
	strb r0, [r4, #0xf6]
	bl MOD13_02233B3C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02233A20: .word 0x02243150

	arm_func_start MOD13_02233A24
MOD13_02233A24: ; 0x02233A24
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r1, _02233B38 ; =0x02243150
	mov r6, r0
	ldr r0, [r1]
	mov r1, #0
	add r5, r0, #0x400
	mov r0, r5
	mov r2, #0xef
	bl MI_CpuFill8
	mov r0, r6
	add r1, r5, #0x40
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [r6, #0x20]
	cmp r0, #1
	beq _02233A78
	cmp r0, #2
	beq _02233A90
	cmp r0, #3
	beq _02233AA8
	b _02233AC0
_02233A78:
	ldrb r0, [r5, #0xe6]
	mov r4, #5
	bic r0, r0, #3
	orr r0, r0, #1
	strb r0, [r5, #0xe6]
	b _02233AD0
_02233A90:
	ldrb r0, [r5, #0xe6]
	mov r4, #0xd
	bic r0, r0, #3
	orr r0, r0, #2
	strb r0, [r5, #0xe6]
	b _02233AD0
_02233AA8:
	ldrb r0, [r5, #0xe6]
	mov r4, #0x10
	bic r0, r0, #3
	orr r0, r0, #3
	strb r0, [r5, #0xe6]
	b _02233AD0
_02233AC0:
	ldrb r0, [r5, #0xe6]
	mov r4, #0
	bic r0, r0, #3
	strb r0, [r5, #0xe6]
_02233AD0:
	ldrb r0, [r5, #0xe6]
	add r7, r5, #0x80
	add r6, r6, #0x28
	bic r0, r0, #0xfc
	strb r0, [r5, #0xe6]
	mov r8, #0
_02233AE8:
	mov r0, r6
	mov r1, r7
	mov r2, r4
	bl MI_CpuCopy8
	add r8, r8, #1
	cmp r8, #4
	add r7, r7, #0x10
	add r6, r6, #0x20
	blt _02233AE8
	mov r3, #2
	add r0, r5, #0xf0
	mov r1, #0
	mov r2, #4
	strb r3, [r5, #0xe7]
	bl MI_CpuFill8
	mov r0, #1
	strb r0, [r5, #0xf5]
	strb r0, [r5, #0xf6]
	bl MOD13_02233B3C
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02233B38: .word 0x02243150

	arm_func_start MOD13_02233B3C
MOD13_02233B3C: ; 0x02233B3C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _02233C20 ; =0x02243150
	mov r2, #0x78
	ldr r1, [r0]
	add r5, r1, #0x400
	ldrb r0, [r5, #0xf4]
	mov ip, r5
	add r4, r1, r0, lsl #8
	mov r3, r4
_02233B64:
	ldrb r1, [ip], #1
	ldrb r0, [ip], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _02233B64
	ldrb r0, [r5, #0xf5]
	cmp r0, #0
	beq _02233BB4
	add r0, r4, #0xc0
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	add r0, r4, #0xc4
	mov r1, #0
	mov r2, #4
	bl MI_CpuFill8
	mov r0, #0
	strb r0, [r4, #0xd0]
	b _02233BE0
_02233BB4:
	add r0, r5, #0xc0
	add r1, r4, #0xc0
	mov r2, #4
	bl MI_CpuCopy8
	add r0, r5, #0xc4
	add r1, r4, #0xc4
	mov r2, #4
	bl MI_CpuCopy8
	add r0, r5, #0xf0
	bl FUN_02095BE0
	strb r0, [r4, #0xd0]
_02233BE0:
	ldrb r0, [r5, #0xf6]
	cmp r0, #0
	beq _02233C00
	add r0, r4, #0xc8
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	b _02233C10
_02233C00:
	add r0, r5, #0xc8
	add r1, r4, #0xc8
	mov r2, #8
	bl MI_CpuCopy8
_02233C10:
	ldrb r0, [r5, #0xf4]
	bl MOD13_02233698
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02233C20: .word 0x02243150

	arm_func_start MOD13_02233C24
MOD13_02233C24: ; 0x02233C24
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _02233D04 ; =0x02243150
	mov r3, #0x78
	ldr r5, [r1]
	add r4, r5, r0, lsl #8
	mov lr, r4
	add ip, r5, #0x400
_02233C44:
	ldrb r2, [lr], #1
	ldrb r1, [lr], #1
	subs r3, r3, #1
	strb r2, [ip], #1
	strb r1, [ip], #1
	bne _02233C44
	ldr r1, _02233D08 ; =0x0223F5E4
	strb r0, [r5, #0x4f4]
	add r0, r4, #0xc0
	mov r2, #4
	bl memcmp
	cmp r0, #0
	ldrne r0, _02233D04 ; =0x02243150
	movne r1, #0
	ldrne r0, [r0]
	mov r2, #4
	strneb r1, [r0, #0x4f5]
	ldreq r0, _02233D04 ; =0x02243150
	moveq r1, #1
	ldreq r0, [r0]
	streqb r1, [r0, #0x4f5]
	ldr r1, _02233D08 ; =0x0223F5E4
	add r0, r4, #0xc8
	bl memcmp
	cmp r0, #0
	bne _02233CC4
	ldr r1, _02233D08 ; =0x0223F5E4
	add r0, r4, #0xcc
	mov r2, #4
	bl memcmp
	cmp r0, #0
	beq _02233CD8
_02233CC4:
	ldr r0, _02233D04 ; =0x02243150
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x4f6]
	b _02233CE8
_02233CD8:
	ldr r0, _02233D04 ; =0x02243150
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x4f6]
_02233CE8:
	ldr r1, _02233D04 ; =0x02243150
	ldrb r0, [r4, #0xd0]
	ldr r1, [r1]
	add r1, r1, #0x4f0
	bl FUN_02095BB0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02233D04: .word 0x02243150
_02233D08: .word 0x0223F5E4

	arm_func_start MOD13_02233D0C
MOD13_02233D0C: ; 0x02233D0C
	ldr r1, _02233D20 ; =0x02243150
	ldr r1, [r1]
	add r0, r1, r0, lsl #8
	ldrb r0, [r0, #0xe7]
	bx lr
	.align 2, 0
_02233D20: .word 0x02243150

	arm_func_start MOD13_02233D24
MOD13_02233D24: ; 0x02233D24
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r1, _02233D64 ; =0x02243150
	ldr r2, _02233D68 ; =0x000004CC
	ldr r3, [r1]
	ldr r1, _02233D6C ; =0x022405CC
	add ip, r3, r2
	ldrb r2, [ip, #2]
	str r2, [sp]
	ldrb r2, [ip, #3]
	str r2, [sp, #4]
	ldrb r2, [r3, #0x4cc]
	ldrb r3, [ip, #1]
	bl OS_SPrintf
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02233D64: .word 0x02243150
_02233D68: .word 0x000004CC
_02233D6C: .word 0x022405CC

	arm_func_start MOD13_02233D70
MOD13_02233D70: ; 0x02233D70
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r1, _02233DB0 ; =0x02243150
	ldr r2, _02233DB4 ; =0x000004C8
	ldr r3, [r1]
	ldr r1, _02233DB8 ; =0x022405CC
	add ip, r3, r2
	ldrb r2, [ip, #2]
	str r2, [sp]
	ldrb r2, [ip, #3]
	str r2, [sp, #4]
	ldrb r2, [r3, #0x4c8]
	ldrb r3, [ip, #1]
	bl OS_SPrintf
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02233DB0: .word 0x02243150
_02233DB4: .word 0x000004C8
_02233DB8: .word 0x022405CC

	arm_func_start MOD13_02233DBC
MOD13_02233DBC: ; 0x02233DBC
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r1, _02233DFC ; =0x02243150
	ldr r2, _02233E00 ; =0x000004C4
	ldr r3, [r1]
	ldr r1, _02233E04 ; =0x022405CC
	add ip, r3, r2
	ldrb r2, [ip, #2]
	str r2, [sp]
	ldrb r2, [ip, #3]
	str r2, [sp, #4]
	ldrb r2, [r3, #0x4c4]
	ldrb r3, [ip, #1]
	bl OS_SPrintf
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02233DFC: .word 0x02243150
_02233E00: .word 0x000004C4
_02233E04: .word 0x022405CC

	arm_func_start MOD13_02233E08
MOD13_02233E08: ; 0x02233E08
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r2, _02233E44 ; =0x02243150
	ldr r1, _02233E48 ; =0x022405CC
	ldr r3, [r2]
	add ip, r3, #0x4f0
	ldrb r2, [ip, #2]
	str r2, [sp]
	ldrb r2, [ip, #3]
	str r2, [sp, #4]
	ldrb r2, [r3, #0x4f0]
	ldrb r3, [ip, #1]
	bl OS_SPrintf
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02233E44: .word 0x02243150
_02233E48: .word 0x022405CC

	arm_func_start MOD13_02233E4C
MOD13_02233E4C: ; 0x02233E4C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r2, _02233E88 ; =0x02243150
	ldr r1, _02233E8C ; =0x022405CC
	ldr r3, [r2]
	add ip, r3, #0x4c0
	ldrb r2, [ip, #2]
	str r2, [sp]
	ldrb r2, [ip, #3]
	str r2, [sp, #4]
	ldrb r2, [r3, #0x4c0]
	ldrb r3, [ip, #1]
	bl OS_SPrintf
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02233E88: .word 0x02243150
_02233E8C: .word 0x022405CC

	arm_func_start MOD13_02233E90
MOD13_02233E90: ; 0x02233E90
	ldr r2, _02233EAC ; =0x02243150
	mov r1, r0
	ldr r0, [r2]
	ldr ip, _02233EB0 ; =0x020CE3E0
	mov r2, #0x20
	add r0, r0, #0x440
	bx ip
	.align 2, 0
_02233EAC: .word 0x02243150
_02233EB0: .word 0x020CE3E0

	arm_func_start MOD13_02233EB4
MOD13_02233EB4: ; 0x02233EB4
	ldr r2, _02233ECC ; =0x02243150
	ldr r1, _02233ED0 ; =0x000004CC
	ldr r2, [r2]
	ldr ip, _02233ED4 ; =MOD13_02233608
	add r1, r2, r1
	bx ip
	.align 2, 0
_02233ECC: .word 0x02243150
_02233ED0: .word 0x000004CC
_02233ED4: .word MOD13_02233608

	arm_func_start MOD13_02233ED8
MOD13_02233ED8: ; 0x02233ED8
	ldr r2, _02233EF0 ; =0x02243150
	ldr r1, _02233EF4 ; =0x000004C8
	ldr r2, [r2]
	ldr ip, _02233EF8 ; =MOD13_02233608
	add r1, r2, r1
	bx ip
	.align 2, 0
_02233EF0: .word 0x02243150
_02233EF4: .word 0x000004C8
_02233EF8: .word MOD13_02233608

	arm_func_start MOD13_02233EFC
MOD13_02233EFC: ; 0x02233EFC
	ldr r2, _02233F14 ; =0x02243150
	ldr r1, _02233F18 ; =0x000004C4
	ldr r2, [r2]
	ldr ip, _02233F1C ; =MOD13_02233608
	add r1, r2, r1
	bx ip
	.align 2, 0
_02233F14: .word 0x02243150
_02233F18: .word 0x000004C4
_02233F1C: .word MOD13_02233608

	arm_func_start MOD13_02233F20
MOD13_02233F20: ; 0x02233F20
	ldr r1, _02233F34 ; =0x02243150
	ldr ip, _02233F38 ; =MOD13_02233608
	ldr r1, [r1]
	add r1, r1, #0x4f0
	bx ip
	.align 2, 0
_02233F34: .word 0x02243150
_02233F38: .word MOD13_02233608

	arm_func_start MOD13_02233F3C
MOD13_02233F3C: ; 0x02233F3C
	ldr r1, _02233F50 ; =0x02243150
	ldr ip, _02233F54 ; =MOD13_02233608
	ldr r1, [r1]
	add r1, r1, #0x4c0
	bx ip
	.align 2, 0
_02233F50: .word 0x02243150
_02233F54: .word MOD13_02233608

	arm_func_start MOD13_02233F58
MOD13_02233F58: ; 0x02233F58
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r1, _02234100 ; =0x02243150
	mov r6, r0
	ldr r0, [r1]
	mov r1, #0
	add r0, r0, #0x480
	mov r2, #0x10
	bl MI_CpuFill8
	mov r0, r6
	mov r1, #0x20
	bl MOD13_0223BDA4
	mov r4, r0
	cmp r4, #0xa
	bgt _02233FA4
	cmp r4, #0xa
	bge _02233FC0
	cmp r4, #0
	beq _02233FC0
	b _0223401C
_02233FA4:
	cmp r4, #0x1a
	bgt _02233FB8
	cmp r4, #0x1a
	beq _02233FC0
	b _0223401C
_02233FB8:
	cmp r4, #0x20
	bne _0223401C
_02233FC0:
	ldr r0, _02234100 ; =0x02243150
	cmp r4, #0
	ldr r2, [r0]
	mov r5, #0
	ldrb r1, [r2, #0x4e6]
	bic r1, r1, #0xfc
	strb r1, [r2, #0x4e6]
	ldr r0, [r0]
	add r8, r0, #0x480
	ble _02234048
_02233FE8:
	ldrb r0, [r6, r5]
	bl MOD13_022335EC
	add r1, r5, #1
	mov r7, r0
	ldrb r0, [r6, r1]
	bl MOD13_022335EC
	add r0, r0, r7, lsl #4
	add r5, r5, #2
	strb r0, [r8]
	cmp r5, r4
	add r8, r8, #1
	blt _02233FE8
	b _02234048
_0223401C:
	ldr r1, _02234100 ; =0x02243150
	mov r0, r6
	ldr r5, [r1]
	mov r2, #0x10
	ldrb r3, [r5, #0x4e6]
	bic r3, r3, #0xfc
	orr r3, r3, #4
	strb r3, [r5, #0x4e6]
	ldr r1, [r1]
	add r1, r1, #0x480
	bl MI_CpuCopy8
_02234048:
	cmp r4, #5
	bgt _02234064
	cmp r4, #5
	bge _022340AC
	cmp r4, #0
	beq _02234094
	b _022340E4
_02234064:
	cmp r4, #0xd
	bgt _02234088
	cmp r4, #0xa
	blt _022340E4
	cmp r4, #0xa
	beq _022340AC
	cmp r4, #0xd
	beq _022340C8
	b _022340E4
_02234088:
	cmp r4, #0x1a
	beq _022340C8
	b _022340E4
_02234094:
	ldr r0, _02234100 ; =0x02243150
	ldr r1, [r0]
	ldrb r0, [r1, #0x4e6]
	bic r0, r0, #3
	strb r0, [r1, #0x4e6]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_022340AC:
	ldr r0, _02234100 ; =0x02243150
	ldr r1, [r0]
	ldrb r0, [r1, #0x4e6]
	bic r0, r0, #3
	orr r0, r0, #1
	strb r0, [r1, #0x4e6]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_022340C8:
	ldr r0, _02234100 ; =0x02243150
	ldr r1, [r0]
	ldrb r0, [r1, #0x4e6]
	bic r0, r0, #3
	orr r0, r0, #2
	strb r0, [r1, #0x4e6]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_022340E4:
	ldr r0, _02234100 ; =0x02243150
	ldr r1, [r0]
	ldrb r0, [r1, #0x4e6]
	bic r0, r0, #3
	orr r0, r0, #3
	strb r0, [r1, #0x4e6]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234100: .word 0x02243150

	arm_func_start MOD13_02234104
MOD13_02234104: ; 0x02234104
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02234138 ; =0x02243150
	mov r2, #0x20
	ldr r1, [r1]
	add r1, r1, #0x440
	bl MI_CpuCopy8
	ldr r0, _02234138 ; =0x02243150
	mov r1, #0
	ldr r0, [r0]
	strb r1, [r0, #0x4e7]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02234138: .word 0x02243150

	arm_func_start MOD13_0223413C
MOD13_0223413C: ; 0x0223413C
	ldr r1, _0223414C ; =0x02243150
	ldr r1, [r1]
	strb r0, [r1, #0x4f6]
	bx lr
	.align 2, 0
_0223414C: .word 0x02243150

	arm_func_start MOD13_02234150
MOD13_02234150: ; 0x02234150
	ldr r1, _02234160 ; =0x02243150
	ldr r1, [r1]
	strb r0, [r1, #0x4f5]
	bx lr
	.align 2, 0
_02234160: .word 0x02243150

	arm_func_start MOD13_02234164
MOD13_02234164: ; 0x02234164
	ldr r0, _02234174 ; =0x02243150
	ldr r0, [r0]
	add r0, r0, #0x400
	bx lr
	.align 2, 0
_02234174: .word 0x02243150

	arm_func_start MOD13_02234178
MOD13_02234178: ; 0x02234178
	ldr ip, _02234184 ; =MOD13_0223AF90
	ldr r0, _02234188 ; =0x02243150
	bx ip
	.align 2, 0
_02234184: .word MOD13_0223AF90
_02234188: .word 0x02243150

	arm_func_start MOD13_0223418C
MOD13_0223418C: ; 0x0223418C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022341CC ; =0x000006F8
	mov r1, #0x20
	bl MOD13_0223B004
	ldr r1, _022341D0 ; =0x02243150
	ldr r2, _022341D4 ; =0x000004F8
	str r0, [r1]
	ldr r1, _022341D8 ; =0x0000A001
	add r0, r0, r2
	bl MATHi_CRC16InitTableRev
	ldr r0, _022341D0 ; =0x02243150
	ldr r0, [r0]
	bl FUN_02095D68
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022341CC: .word 0x000006F8
_022341D0: .word 0x02243150
_022341D4: .word 0x000004F8
_022341D8: .word 0x0000A001

	arm_func_start MOD13_022341DC
MOD13_022341DC: ; 0x022341DC
	ldr ip, _022341E4 ; =0x020C01A0
	bx ip
	.align 2, 0
_022341E4: .word 0x020C01A0

	arm_func_start MOD13_022341E8
MOD13_022341E8: ; 0x022341E8
	ldr r0, _02234200 ; =0x02243154
	ldr ip, _02234204 ; =0x020C10A4
	ldr r0, [r0]
	mov r1, #0
	add r0, r0, #0x90
	bx ip
	.align 2, 0
_02234200: .word 0x02243154
_02234204: .word 0x020C10A4

	arm_func_start MOD13_02234208
MOD13_02234208: ; 0x02234208
	ldr r2, _02234224 ; =0x02243154
	ldr ip, _02234228 ; =0x020C0EA4
	ldr r3, [r2]
	mov r2, r1
	mov r1, r0
	add r0, r3, #0x90
	bx ip
	.align 2, 0
_02234224: .word 0x02243154
_02234228: .word 0x020C0EA4

	arm_func_start MOD13_0223422C
MOD13_0223422C: ; 0x0223422C
	ldr r2, _02234244 ; =0x02243154
	mov r1, r0
	ldr r0, [r2]
	ldr ip, _02234248 ; =0x020C0F40
	add r0, r0, #0x90
	bx ip
	.align 2, 0
_02234244: .word 0x02243154
_02234248: .word 0x020C0F40

	arm_func_start MOD13_0223424C
MOD13_0223424C: ; 0x0223424C
	ldr r1, _02234268 ; =0x02243154
	mov r2, r0
	ldr r0, [r1]
	ldr ip, _0223426C ; =0x020C3888
	mov r1, #0
	add r0, r0, #0x90
	bx ip
	.align 2, 0
_02234268: .word 0x02243154
_0223426C: .word 0x020C3888

	arm_func_start MOD13_02234270
MOD13_02234270: ; 0x02234270
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0223429C ; =0x02243154
	mov r0, #0
	ldr r1, [r1]
	ldr r1, [r1, #0x98]
	bl MOD13_0223C110
	ldr r0, _0223429C ; =0x02243154
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223429C: .word 0x02243154

	arm_func_start MOD13_022342A0
MOD13_022342A0: ; 0x022342A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x9c
	mov r1, #4
	bl MOD13_0223B004
	ldr r2, _0223432C ; =0x02243154
	add r1, sp, #0
	str r0, [r2]
	ldr r0, _02234330 ; =0x022405DC
	mov r2, #0x20
	bl MOD13_022393D8
	ldr r1, _0223432C ; =0x02243154
	ldr r1, [r1]
	str r0, [r1, #0x94]
	bl FUN_020C01D0
	ldr r0, _0223432C ; =0x02243154
	ldr r0, [r0]
	ldr r1, [r0, #0x94]
	bl FUN_020C2444
	mov r0, #0
	bl FUN_020C39CC
	ldr r0, _0223432C ; =0x02243154
	ldr r0, [r0]
	add r0, r0, #0x90
	bl FUN_020C0F80
	mov r0, #0
	ldr r1, _02234334 ; =MOD13_022341DC
	mov r2, r0
	mov r3, #0xc8
	bl MOD13_0223C1C4
	ldr r1, _0223432C ; =0x02243154
	ldr r1, [r1]
	str r0, [r1, #0x98]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223432C: .word 0x02243154
_02234330: .word 0x022405DC
_02234334: .word MOD13_022341DC

	arm_func_start MOD13_02234338
MOD13_02234338: ; 0x02234338
	stmdb sp!, {r4, lr}
	ldr r1, _02234380 ; =0x02243158
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0x600
	bl DC_FlushRange
	ldr r0, _02234380 ; =0x02243158
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x600
	bl GXS_LoadBG1Scr
	ldr r0, _02234380 ; =0x02243158
	ldr r0, [r0]
	bl MOD13_0223939C
	mov r1, r4
	mov r0, #1
	bl MOD13_0223C110
	ldmia sp!, {r4, pc}
	.align 2, 0
_02234380: .word 0x02243158

	arm_func_start MOD13_02234384
MOD13_02234384: ; 0x02234384
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _022343C8 ; =0x02240658
	ldr r0, [r1, r0, lsl #2]
	bl MOD13_0221F1BC
	mov r1, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r2, _022343CC ; =0x02243158
	ldr r1, _022343D0 ; =MOD13_02234338
	str r0, [r2]
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022343C8: .word 0x02240658
_022343CC: .word 0x02243158
_022343D0: .word MOD13_02234338

	arm_func_start MOD13_022343D4
MOD13_022343D4: ; 0x022343D4
	ldr r0, _022343FC ; =0x0224315C
	ldr r0, [r0]
	cmp r0, #0
	moveq r0, #1
	bxeq lr
	ldrb r0, [r0, #0x18]
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_022343FC: .word 0x0224315C

	arm_func_start MOD13_02234400
MOD13_02234400: ; 0x02234400
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _022344C8 ; =0x0224315C
	mov r5, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, [sp]
	ldr r6, _022344C8 ; =0x0224315C
	sub r0, r0, #8
	ldr r7, _022344CC ; =0x0223F608
	mov r4, #0
	str r0, [sp]
	mvn r8, #0
_02234444:
	add r0, r7, r4, lsl #2
	ldr r1, [r6]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r4, lsl #2]
	ldr r2, [sp]
	mov r1, r8
	bl MOD13_02239888
	add r4, r4, #1
	cmp r4, #5
	blt _02234444
	ldr r1, [sp]
	ldr r0, _022344D0 ; =0x000001D6
	cmp r1, r0
	addgt sp, sp, #8
	ldmgtia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r1, #0x100
	addlt sp, sp, #8
	ldmltia sp!, {r4, r5, r6, r7, r8, pc}
	mov r1, r5
	mov r0, #0
	bl MOD13_0223C110
	mov r5, #0
	ldr r4, _022344C8 ; =0x0224315C
_022344A0:
	ldr r0, [r4]
	ldr r0, [r0, r5, lsl #2]
	bl MOD13_02239AE8
	add r5, r5, #1
	cmp r5, #5
	blt _022344A0
	ldr r0, _022344C8 ; =0x0224315C
	bl MOD13_0223AF90
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_022344C8: .word 0x0224315C
_022344CC: .word 0x0223F608
_022344D0: .word 0x000001D6

	arm_func_start MOD13_022344D4
MOD13_022344D4: ; 0x022344D4
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _022345A0 ; =0x0224315C
	mov r5, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #4]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r4, _022345A4 ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r4]
	sub r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	ble _02234554
	ldr r5, _022345A0 ; =0x0224315C
	mov r7, #1
	mvn r6, #0
_02234524:
	add r0, r4, r7, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _02234524
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02234554:
	str r0, [sp]
	mov r8, #1
	ldr r6, _022345A0 ; =0x0224315C
	mvn r7, #0
_02234564:
	add r0, r4, r8, lsl #2
	ldr r1, [r6]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _02234564
	ldr r1, _022345A8 ; =MOD13_02234400
	mov r0, r5
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_022345A0: .word 0x0224315C
_022345A4: .word 0x0223F608
_022345A8: .word MOD13_02234400

	arm_func_start MOD13_022345AC
MOD13_022345AC: ; 0x022345AC
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _02234678 ; =0x0224315C
	mov r5, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #8]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r4, _0223467C ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r4, #4]
	sub r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	ble _0223462C
	ldr r5, _02234678 ; =0x0224315C
	mov r7, #2
	mvn r6, #0
_022345FC:
	add r0, r4, r7, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _022345FC
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_0223462C:
	str r0, [sp]
	mov r8, #2
	ldr r6, _02234678 ; =0x0224315C
	mvn r7, #0
_0223463C:
	add r0, r4, r8, lsl #2
	ldr r1, [r6]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _0223463C
	ldr r1, _02234680 ; =MOD13_022344D4
	mov r0, r5
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234678: .word 0x0224315C
_0223467C: .word 0x0223F608
_02234680: .word MOD13_022344D4

	arm_func_start MOD13_02234684
MOD13_02234684: ; 0x02234684
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _02234750 ; =0x0224315C
	mov r5, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #0xc]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r4, _02234754 ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r4, #8]
	sub r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	ble _02234704
	ldr r5, _02234750 ; =0x0224315C
	mov r7, #3
	mvn r6, #0
_022346D4:
	add r0, r4, r7, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _022346D4
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02234704:
	str r0, [sp]
	mov r8, #3
	ldr r6, _02234750 ; =0x0224315C
	mvn r7, #0
_02234714:
	add r0, r4, r8, lsl #2
	ldr r1, [r6]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _02234714
	ldr r1, _02234758 ; =MOD13_022345AC
	mov r0, r5
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234750: .word 0x0224315C
_02234754: .word 0x0223F608
_02234758: .word MOD13_022345AC

	arm_func_start MOD13_0223475C
MOD13_0223475C: ; 0x0223475C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _022347F4 ; =0x0224315C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #0x10]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r1, _022347F8 ; =0x0223F608
	ldr r0, [sp]
	ldrh ip, [r1, #0xc]
	sub r2, r0, #8
	str r2, [sp]
	cmp r2, ip
	ble _022347C0
	ldr r0, _022347F4 ; =0x0224315C
	ldrh r3, [r1, #0x12]
	ldr r0, [r0]
	mvn r1, #0
	ldr r0, [r0, #0x10]
	bl MOD13_02239888
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022347C0:
	ldr r0, _022347F4 ; =0x0224315C
	str ip, [sp]
	ldr r0, [r0]
	ldrh r3, [r1, #0x12]
	ldr r0, [r0, #0x10]
	mov r2, ip
	mvn r1, #0
	bl MOD13_02239888
	ldr r1, _022347FC ; =MOD13_02234684
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022347F4: .word 0x0224315C
_022347F8: .word 0x0223F608
_022347FC: .word MOD13_02234684

	arm_func_start MOD13_02234800
MOD13_02234800: ; 0x02234800
	ldr r0, _0223481C ; =0x0224315C
	ldr r0, [r0]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_0223481C: .word 0x0224315C

	arm_func_start MOD13_02234820
MOD13_02234820: ; 0x02234820
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov r1, #5
	mul r2, r0, r1
	mov sl, #0
	str r0, [sp]
	ldr r1, _022348F8 ; =0x0223F5E8
	ldr r0, _022348FC ; =0x0223F5F8
	ldr r4, _02234900 ; =0x0224315C
	add sb, r1, r2
	add r8, r0, r2
	mov r7, sl
	mov fp, sl
	str sl, [sp, #4]
	mov r6, #1
	mvn r5, #0
_02234860:
	ldr r0, [r4]
	mov r1, r7
	ldr r0, [r0, sl, lsl #2]
	bl MOD13_02239ADC
	mov r2, r0
	ldrb r1, [sb]
	mov r0, r6
	bl MOD13_02239E8C
	ldr r0, [r4]
	mov r1, r5
	ldr r0, [r0, sl, lsl #2]
	mov r2, fp
	bl MOD13_02239814
	ldr r3, _02234904 ; =0x0223F608
	ldr r0, [r4]
	add r3, r3, sl, lsl #2
	ldr r1, _02234904 ; =0x0223F608
	mov r2, sl, lsl #2
	ldrh r2, [r1, r2]
	ldrh r3, [r3, #2]
	ldr r0, [r0, sl, lsl #2]
	mov r1, r5
	bl MOD13_02239888
	ldr r0, [r4]
	ldrb r3, [r8]
	ldr r0, [r0, sl, lsl #2]
	ldr r2, [sp, #4]
	mov r1, r5
	bl MOD13_02239994
	add sl, sl, #2
	add sb, sb, #2
	add r8, r8, #2
	cmp sl, #5
	blt _02234860
	ldr r0, [sp]
	bl MOD13_02234384
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022348F8: .word 0x0223F5E8
_022348FC: .word 0x0223F5F8
_02234900: .word 0x0224315C
_02234904: .word 0x0223F608

	arm_func_start MOD13_02234908
MOD13_02234908: ; 0x02234908
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02234948 ; =0x0224315C
	mov r0, #0
	ldr ip, [r1]
	mov lr, #1
	ldr r1, _0223494C ; =MOD13_0223475C
	mov r2, r0
	mov r3, #0x78
	strb lr, [ip, #0x18]
	bl MOD13_0223C1C4
	ldr r1, _02234948 ; =0x0224315C
	ldr r1, [r1]
	str r0, [r1, #0x14]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02234948: .word 0x0224315C
_0223494C: .word MOD13_0223475C

	arm_func_start MOD13_02234950
MOD13_02234950: ; 0x02234950
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, r0
	mov r0, #0
	bl MOD13_0223C110
	ldr r0, _0223497C ; =0x0224315C
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x14]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223497C: .word 0x0224315C

	arm_func_start MOD13_02234980
MOD13_02234980: ; 0x02234980
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02234A24 ; =0x0224315C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #0x10]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r1, _02234A28 ; =0x0223F608
	ldr r0, [sp]
	ldrh ip, [r1, #0x10]
	add r2, r0, #8
	str r2, [sp]
	cmp r2, ip
	blt _022349CC
	cmp r2, #0x100
	ble _022349F0
_022349CC:
	ldr r1, _02234A24 ; =0x0224315C
	ldr r0, _02234A28 ; =0x0223F608
	ldr r1, [r1]
	ldrh r3, [r0, #0x12]
	ldr r0, [r1, #0x10]
	mvn r1, #0
	bl MOD13_02239888
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_022349F0:
	ldr r0, _02234A24 ; =0x0224315C
	str ip, [sp]
	ldr r0, [r0]
	ldrh r3, [r1, #0x12]
	ldr r0, [r0, #0x10]
	mov r2, ip
	mvn r1, #0
	bl MOD13_02239888
	ldr r1, _02234A2C ; =MOD13_02234950
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02234A24: .word 0x0224315C
_02234A28: .word 0x0223F608
_02234A2C: .word MOD13_02234950

	arm_func_start MOD13_02234A30
MOD13_02234A30: ; 0x02234A30
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _02234B08 ; =0x0224315C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #0xc]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r6, _02234B0C ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r6, #0xc]
	add r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	blt _02234A7C
	cmp r1, #0x100
	ble _02234ABC
_02234A7C:
	ldr r4, _02234B08 ; =0x0224315C
	ldr r5, _02234B0C ; =0x0223F608
	mov r7, #3
	mvn r6, #0
_02234A8C:
	add r0, r5, r7, lsl #2
	ldr r1, [r4]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _02234A8C
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02234ABC:
	str r0, [sp]
	mov r8, #3
	ldr r5, _02234B08 ; =0x0224315C
	mvn r7, #0
_02234ACC:
	add r0, r6, r8, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _02234ACC
	ldr r1, _02234B10 ; =MOD13_02234980
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234B08: .word 0x0224315C
_02234B0C: .word 0x0223F608
_02234B10: .word MOD13_02234980

	arm_func_start MOD13_02234B14
MOD13_02234B14: ; 0x02234B14
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _02234BEC ; =0x0224315C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #8]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r6, _02234BF0 ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r6, #8]
	add r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	blt _02234B60
	cmp r1, #0x100
	ble _02234BA0
_02234B60:
	ldr r4, _02234BEC ; =0x0224315C
	ldr r5, _02234BF0 ; =0x0223F608
	mov r7, #2
	mvn r6, #0
_02234B70:
	add r0, r5, r7, lsl #2
	ldr r1, [r4]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _02234B70
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02234BA0:
	str r0, [sp]
	mov r8, #2
	ldr r5, _02234BEC ; =0x0224315C
	mvn r7, #0
_02234BB0:
	add r0, r6, r8, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _02234BB0
	ldr r1, _02234BF4 ; =MOD13_02234A30
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234BEC: .word 0x0224315C
_02234BF0: .word 0x0223F608
_02234BF4: .word MOD13_02234A30

	arm_func_start MOD13_02234BF8
MOD13_02234BF8: ; 0x02234BF8
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _02234CD0 ; =0x0224315C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0, #4]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r6, _02234CD4 ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r6, #4]
	add r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	blt _02234C44
	cmp r1, #0x100
	ble _02234C84
_02234C44:
	ldr r4, _02234CD0 ; =0x0224315C
	ldr r5, _02234CD4 ; =0x0223F608
	mov r7, #1
	mvn r6, #0
_02234C54:
	add r0, r5, r7, lsl #2
	ldr r1, [r4]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _02234C54
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02234C84:
	str r0, [sp]
	mov r8, #1
	ldr r5, _02234CD0 ; =0x0224315C
	mvn r7, #0
_02234C94:
	add r0, r6, r8, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _02234C94
	ldr r1, _02234CD8 ; =MOD13_02234B14
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234CD0: .word 0x0224315C
_02234CD4: .word 0x0223F608
_02234CD8: .word MOD13_02234B14

	arm_func_start MOD13_02234CDC
MOD13_02234CDC: ; 0x02234CDC
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r1, _02234DB4 ; =0x0224315C
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r6, _02234DB8 ; =0x0223F608
	ldr r1, [sp]
	ldrh r0, [r6]
	add r1, r1, #8
	str r1, [sp]
	cmp r1, r0
	blt _02234D28
	cmp r1, #0x100
	ble _02234D68
_02234D28:
	ldr r4, _02234DB4 ; =0x0224315C
	ldr r5, _02234DB8 ; =0x0223F608
	mov r7, #0
	mvn r6, #0
_02234D38:
	add r0, r5, r7, lsl #2
	ldr r1, [r4]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r7, lsl #2]
	ldr r2, [sp]
	mov r1, r6
	bl MOD13_02239888
	add r7, r7, #1
	cmp r7, #5
	blt _02234D38
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02234D68:
	str r0, [sp]
	mov r8, #0
	ldr r5, _02234DB4 ; =0x0224315C
	mvn r7, #0
_02234D78:
	add r0, r6, r8, lsl #2
	ldr r1, [r5]
	ldrh r3, [r0, #2]
	ldr r0, [r1, r8, lsl #2]
	ldr r2, [sp]
	mov r1, r7
	bl MOD13_02239888
	add r8, r8, #1
	cmp r8, #5
	blt _02234D78
	ldr r1, _02234DBC ; =MOD13_02234BF8
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02234DB4: .word 0x0224315C
_02234DB8: .word 0x0223F608
_02234DBC: .word MOD13_02234BF8

	arm_func_start MOD13_02234DC0
MOD13_02234DC0: ; 0x02234DC0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	str r0, [sp]
	mov r0, #0x1c
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, [sp]
	mov r2, #5
	mul r3, r1, r2
	mov sl, #0
	ldr r4, _02234EC4 ; =0x0224315C
	ldr r2, _02234EC8 ; =0x0223F5E8
	ldr r1, _02234ECC ; =0x0223F5F8
	str r0, [r4]
	add sb, r2, r3
	add r8, r1, r3
	mov fp, sl
	str sl, [sp, #4]
	mov r7, #1
	mvn r6, #0
	mvn r5, #0x29
_02234E14:
	ldrb r1, [sb]
	mov r0, r7
	mov r2, r7
	bl MOD13_02239E0C
	ldr r2, [r4]
	mov r1, r6
	str r0, [r2, sl, lsl #2]
	ldr r0, [r4]
	mov r2, fp
	ldr r0, [r0, sl, lsl #2]
	bl MOD13_02239814
	ldr r3, _02234ED0 ; =0x0223F608
	ldr r0, [r4]
	add r3, r3, sl, lsl #2
	ldrh r3, [r3, #2]
	ldr r0, [r0, sl, lsl #2]
	mov r1, r6
	mov r2, r5
	bl MOD13_02239888
	ldr r0, [r4]
	ldrb r3, [r8]
	ldr r0, [r0, sl, lsl #2]
	ldr r2, [sp, #4]
	mov r1, r6
	bl MOD13_02239994
	add sl, sl, #1
	add sb, sb, #1
	add r8, r8, #1
	cmp sl, #5
	blt _02234E14
	mov r0, #0
	ldr r1, _02234ED4 ; =MOD13_02234CDC
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02234EC4 ; =0x0224315C
	ldr r1, [r1]
	str r0, [r1, #0x14]
	ldr r0, [sp]
	bl MOD13_02234384
	mov r0, #0xd
	bl MOD13_0223424C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02234EC4: .word 0x0224315C
_02234EC8: .word 0x0223F5E8
_02234ECC: .word 0x0223F5F8
_02234ED0: .word 0x0223F608
_02234ED4: .word MOD13_02234CDC

	arm_func_start MOD13_02234ED8
MOD13_02234ED8: ; 0x02234ED8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	str r0, [sp]
	bl OS_GetTick
	ldr r2, _02235018 ; =0x02243160
	ldr r3, _0223501C ; =0x0017F898
	ldr fp, [r2]
	mov r8, #0
	add r2, fp, #0x1000
	ldr r4, [r2, #0xb78]
	ldr r2, [r2, #0xb7c]
	adds r3, r4, r3
	adc r2, r2, #0
	cmp r1, r2
	cmpeq r0, r3
	addlo sp, sp, #4
	ldmloia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov sb, r8
	mov sl, r8
	mov r6, fp
	add r7, fp, #0x1300
	mov r4, #1
	mov r5, #6
_02234F34:
	ldr r1, _02235020 ; =0x0223F61C
	mov r0, r7
	mov r2, r5
	bl memcmp
	cmp r0, #0
	beq _02234F60
	add r0, r6, #0x1000
	ldrb r0, [r0, #0x306]
	cmp r0, #0
	movne sb, r4
	moveq r8, r4
_02234F60:
	add sl, sl, #1
	cmp sl, #0x10
	add r7, r7, #7
	add r6, r6, #7
	blt _02234F34
	cmp sb, #0
	beq _02234FA0
	cmp r8, #0
	beq _02234FA0
	add r0, fp, #0x1000
	ldr r1, [r0, #0x370]
	cmp r1, #0
	beq _02234FE4
	mov r0, #2
	blx r1
	b _02234FE4
_02234FA0:
	cmp sb, #0
	beq _02234FC4
	add r0, fp, #0x1000
	ldr r1, [r0, #0x370]
	cmp r1, #0
	beq _02234FE4
	mov r0, #1
	blx r1
	b _02234FE4
_02234FC4:
	cmp r8, #0
	bne _02234FE4
	add r0, fp, #0x1000
	ldr r1, [r0, #0x370]
	cmp r1, #0
	beq _02234FE4
	mov r0, #0
	blx r1
_02234FE4:
	ldr r3, _02235018 ; =0x02243160
	mov r0, #0
	ldr r2, [r3]
	ldr r1, [sp]
	add r2, r2, #0x1000
	str r0, [r2, #0xb80]
	ldr r2, [r3]
	mov r3, #1
	add r2, r2, #0x1000
	strb r3, [r2, #0xb86]
	bl MOD13_0223C110
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02235018: .word 0x02243160
_0223501C: .word 0x0017F898
_02235020: .word 0x0223F61C

	arm_func_start MOD13_02235024
MOD13_02235024: ; 0x02235024
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	ldr r1, _02235154 ; =0x02243160
	mov r4, r0
	ldr r2, [r1]
	add r1, r2, #0x1000
	ldrb r0, [r1, #0xb85]
	cmp r0, #0
	beq _02235064
	ldr r1, [r1, #0x370]
	cmp r1, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02235064:
	add r0, r2, #0xf00
	mov r1, #0x400
	bl DC_InvalidateRange
	ldrh fp, [r4, #0xe]
	mov sl, #0
	cmp fp, #0
	addle sp, sp, #0xc
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, _02235154 ; =0x02243160
	ldr r7, [r0]
	str sl, [sp, #4]
	mov r5, #6
	mov r0, #8
	str r0, [sp]
_0223509C:
	add r0, r4, sl, lsl #2
	ldr r6, [r0, #0x10]
	ldr r1, _02235158 ; =0x0223F624
	ldr r2, [sp]
	add r0, r6, #0xc
	bl memcmp
	cmp r0, #0
	bne _02235140
	ldrb r0, [r6, #0x15]
	ands r0, r0, #1
	beq _02235140
	ldr sb, [sp, #4]
	add r8, r7, #0x1300
	add r6, r6, #4
_022350D4:
	mov r0, r6
	mov r1, r8
	mov r2, r5
	bl memcmp
	cmp r0, #0
	bne _02235130
	mov r0, #7
	mla r0, sb, r0, r7
	add r0, r0, #0x1000
	ldrb r0, [r0, #0x306]
	cmp r0, #0
	bne _02235140
	add r0, r7, #0x1000
	ldr r1, [r0, #0x370]
	cmp r1, #0
	moveq r1, #1
	streqb r1, [r0, #0xb85]
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r0, #1
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02235130:
	add sb, sb, #1
	cmp sb, #0x10
	add r8, r8, #7
	blt _022350D4
_02235140:
	add sl, sl, #1
	cmp sl, fp
	blt _0223509C
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02235154: .word 0x02243160
_02235158: .word 0x0223F624

	arm_func_start MOD13_0223515C
MOD13_0223515C: ; 0x0223515C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x1c
	str r0, [sp]
	ldrh r0, [r0, #0xe]
	mov fp, #0
	cmp r0, #0
	addle sp, sp, #0x1c
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r0, #1
	str r0, [sp, #0x14]
	mov r0, #0xc0
	str r0, [sp, #4]
	mov r0, #8
	ldr r4, _022352EC ; =0x0223F61C
	str fp, [sp, #0x18]
	str fp, [sp, #0xc]
	str fp, [sp, #0x10]
	mov r5, #6
	str r0, [sp, #8]
_022351A8:
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r0, r0, fp, lsl #2
	ldr sl, [r0, #0x10]
	mov r0, sl
	bl DC_InvalidateRange
	ldr r1, _022352F0 ; =0x0223F624
	ldr r2, [sp, #8]
	add r0, sl, #0xc
	bl memcmp
	cmp r0, #0
	bne _022352D0
	ldr r0, _022352F4 ; =0x02243160
	ldr sb, [sp, #0xc]
	ldr r7, [r0]
	add r6, sl, #4
	add r8, r7, #0x1300
_022351EC:
	mov r0, r6
	mov r1, r8
	mov r2, r5
	bl memcmp
	cmp r0, #0
	bne _0223524C
	mov r0, #7
	mla r0, sb, r0, r7
	add r0, r0, #0x1000
	ldrb r0, [r0, #0x306]
	cmp r0, #0
	bne _022352D0
	ldrb r0, [sl, #0x15]
	ands r0, r0, #1
	beq _022352D0
	add r0, r7, #0x1000
	ldr r1, [r0, #0x370]
	cmp r1, #0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r0, #1
	blx r1
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_0223524C:
	add r8, r8, #7
	add sb, sb, #1
	cmp sb, #0x10
	blt _022351EC
	ldr r6, [sp, #0x10]
	add r8, r7, #0x1300
_02235264:
	mov r0, r8
	mov r1, r4
	mov r2, r5
	bl memcmp
	cmp r0, #0
	bne _022352C0
	mov r0, #7
	add r1, r7, #0x1300
	mul r7, r6, r0
	add r1, r1, r7
	add r0, sl, #4
	mov r2, r5
	bl MI_CpuCopy8
	ldrb r0, [sl, #0x15]
	ands r0, r0, #1
	ldr r0, _022352F4 ; =0x02243160
	ldrne r1, [sp, #0x14]
	ldr r0, [r0]
	ldreq r1, [sp, #0x18]
	add r0, r0, r7
	add r0, r0, #0x1000
	strb r1, [r0, #0x306]
	b _022352D0
_022352C0:
	add r8, r8, #7
	add r6, r6, #1
	cmp r6, #0x10
	blt _02235264
_022352D0:
	ldr r0, [sp]
	add fp, fp, #1
	ldrh r0, [r0, #0xe]
	cmp fp, r0
	blt _022351A8
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022352EC: .word 0x0223F61C
_022352F0: .word 0x0223F624
_022352F4: .word 0x02243160

	arm_func_start MOD13_022352F8
MOD13_022352F8: ; 0x022352F8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r1, [r0, #2]
	cmp r1, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r1, _022353A0 ; =0x02243160
	ldr r1, [r1]
	add r1, r1, #0x1000
	ldrb r2, [r1, #0xb84]
	cmp r2, #0
	beq _02235340
	ldrh r0, [r0]
	add sp, sp, #4
	cmp r0, #2
	moveq r0, #2
	streqb r0, [r1, #0xb84]
	ldmia sp!, {pc}
_02235340:
	ldrh r2, [r0]
	cmp r2, #0x26
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldrh r2, [r0, #8]
	cmp r2, #4
	beq _02235388
	cmp r2, #5
	bne _02235394
	ldrb r1, [r1, #0xb86]
	cmp r1, #0
	beq _02235378
	bl MOD13_02235024
	b _0223537C
_02235378:
	bl MOD13_0223515C
_0223537C:
	bl MOD13_022354B4
	add sp, sp, #4
	ldmia sp!, {pc}
_02235388:
	bl MOD13_022354B4
	add sp, sp, #4
	ldmia sp!, {pc}
_02235394:
	bl OS_Terminate
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022353A0: .word 0x02243160

	arm_func_start MOD13_022353A4
MOD13_022353A4: ; 0x022353A4
	ldr r1, _022353B8 ; =0x02243160
	ldr r1, [r1]
	add r1, r1, #0x1000
	str r0, [r1, #0x370]
	bx lr
	.align 2, 0
_022353B8: .word 0x02243160

	arm_func_start MOD13_022353BC
MOD13_022353BC: ; 0x022353BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _022354A8 ; =0x02243160
	mov r3, #1
	ldr r0, [r2]
	ldr r1, _022354AC ; =0x000013B8
	add r0, r0, #0x1000
	strb r3, [r0, #0xb84]
	ldr r0, [r2]
	add r0, r0, r1
	bl WM_ReadStatus
	ldr r0, _022354A8 ; =0x02243160
	ldr r0, [r0]
	add r0, r0, #0x1300
	ldrh r0, [r0, #0xb8]
	cmp r0, #2
	beq _02235444
	ldr r0, _022354B0 ; =MOD13_022352F8
	bl WM_Reset
	cmp r0, #2
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
_02235418:
	ldr r1, _022354A8 ; =0x02243160
	ldr r0, _022354AC ; =0x000013B8
	ldr r1, [r1]
	add r0, r1, r0
	bl WM_ReadStatus
	ldr r0, _022354A8 ; =0x02243160
	ldr r0, [r0]
	add r0, r0, #0x1300
	ldrh r0, [r0, #0xb8]
	cmp r0, #2
	bne _02235418
_02235444:
	ldr r0, _022354B0 ; =MOD13_022352F8
	bl WM_End
	cmp r0, #2
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
	ldr r0, _022354A8 ; =0x02243160
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r1, [r0, #0xb80]
	cmp r1, #0
	beq _0223547C
	mov r0, #0
	bl MOD13_0223C104
_0223547C:
	ldr r0, _022354A8 ; =0x02243160
	ldr r0, [r0]
	add r0, r0, #0x1000
_02235488:
	ldrb r1, [r0, #0xb84]
	cmp r1, #2
	bne _02235488
	ldr r0, _022354A8 ; =0x02243160
	bl MOD13_0223AF90
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022354A8: .word 0x02243160
_022354AC: .word 0x000013B8
_022354B0: .word MOD13_022352F8

	arm_func_start MOD13_022354B4
MOD13_022354B4: ; 0x022354B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022354E8 ; =0x02243160
	ldr r1, _022354EC ; =0x00001374
	ldr r2, [r0]
	ldr r0, _022354F0 ; =MOD13_022352F8
	add r1, r2, r1
	bl WM_StartScanEx
	cmp r0, #2
	moveq r0, #1
	movne r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022354E8: .word 0x02243160
_022354EC: .word 0x00001374
_022354F0: .word MOD13_022352F8

	arm_func_start MOD13_022354F4
MOD13_022354F4: ; 0x022354F4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x54
	mov r4, r0
	ldr r0, _0223565C ; =0x00001BA0
	mov r1, #0x20
	bl MOD13_0223AFE0
	ldr r2, _02235660 ; =0x02243160
	add r1, r0, #0x1000
	str r0, [r2]
	str r4, [r1, #0x370]
	ldr r4, [r2]
	bl OS_GetTick
	add r2, r4, #0x1000
	str r0, [r2, #0xb78]
	str r1, [r2, #0xb7c]
	ldr r1, _02235664 ; =MOD13_022352F8
	mov r0, r4
	mov r2, #3
	bl WM_Initialize
	cmp r0, #2
	bne _02235648
	ldr r5, _02235660 ; =0x02243160
	ldr r4, _02235668 ; =0x000013B8
_02235550:
	ldr r0, [r5]
	add r0, r0, r4
	bl WM_ReadStatus
	ldr ip, [r5]
	add r0, ip, #0x1300
	ldrh r0, [r0, #0xb8]
	cmp r0, #2
	bne _02235550
	ldr r0, _0223566C ; =0x00001374
	ldr lr, _02235670 ; =0x0223F630
	add r5, ip, r0
	mov r4, #4
_02235580:
	ldmia lr!, {r0, r1, r2, r3}
	stmia r5!, {r0, r1, r2, r3}
	subs r4, r4, #1
	bne _02235580
	ldr r0, [lr]
	add r1, ip, #0xf00
	str r0, [r5]
	add r0, ip, #0x1000
	str r1, [r0, #0x374]
	bl WM_GetDispersionScanPeriod
	ldr r1, _02235660 ; =0x02243160
	ldr r1, [r1]
	add r1, r1, #0x1300
	strh r0, [r1, #0x7c]
	add r0, sp, #0
	bl OS_GetOwnerInfo
	ldr r0, _02235660 ; =0x02243160
	ldr r1, _02235674 ; =0x00001388
	ldr r2, [r0]
	ldr r0, _02235678 ; =0x0223F624
	add r1, r2, r1
	mov r2, #8
	bl MI_CpuCopy8
	ldr r2, _02235660 ; =0x02243160
	mov r3, #1
	ldr r0, [r2]
	ldr r1, _0223567C ; =0x00001394
	add r0, r0, #0x1000
	strb r3, [r0, #0x391]
	ldr r2, [r2]
	ldrh r3, [sp, #0x18]
	add r1, r2, r1
	add r0, sp, #4
	mov r2, r3, lsl #1
	bl MI_CpuCopy8
	bl MOD13_022354B4
	cmp r0, #0
	beq _02235648
	mov r0, #0
	ldr r1, _02235680 ; =MOD13_02234ED8
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02235660 ; =0x02243160
	add sp, sp, #0x54
	ldr r1, [r1]
	add r1, r1, #0x1000
	str r0, [r1, #0xb80]
	mov r0, #1
	ldmia sp!, {r4, r5, pc}
_02235648:
	ldr r0, _02235660 ; =0x02243160
	bl MOD13_0223AF90
	mov r0, #0
	add sp, sp, #0x54
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223565C: .word 0x00001BA0
_02235660: .word 0x02243160
_02235664: .word MOD13_022352F8
_02235668: .word 0x000013B8
_0223566C: .word 0x00001374
_02235670: .word 0x0223F630
_02235674: .word 0x00001388
_02235678: .word 0x0223F624
_0223567C: .word 0x00001394
_02235680: .word MOD13_02234ED8

	arm_func_start MOD13_02235684
MOD13_02235684: ; 0x02235684
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r3, #0x4000000
	ldr r2, [r3]
	ldr r1, _02235730 ; =0x02243164
	bic r2, r2, #0xe000
	str r2, [r3]
	ldr r1, [r1]
	mov r6, r0
	ldr r0, [r1]
	bl MOD13_02239AE8
	ldr r0, _02235730 ; =0x02243164
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD13_02239AE8
	ldr r7, _02235730 ; =0x02243164
	ldr r4, _02235734 ; =0x0223F680
	ldr r1, [r7]
	mov r5, #0
	ldrb r0, [r1, #0x1c]
	ldrb r0, [r4, r0]
	cmp r0, #0
	ble _0223570C
_022356E0:
	add r0, r1, r5, lsl #2
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _022356F4
	bl MOD13_02239AE8
_022356F4:
	ldr r1, [r7]
	add r5, r5, #1
	ldrb r0, [r1, #0x1c]
	ldrb r0, [r4, r0]
	cmp r5, r0
	blt _022356E0
_0223570C:
	ldr r0, [r1, #0x10]
	bl MOD13_0223A978
	mov r1, r6
	mov r0, #1
	bl MOD13_0223C110
	ldr r0, _02235730 ; =0x02243164
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02235730: .word 0x02243164
_02235734: .word 0x0223F680

	arm_func_start MOD13_02235738
MOD13_02235738: ; 0x02235738
	stmdb sp!, {r4, lr}
	ldr r1, _02235788 ; =0x02243164
	mov r4, r0
	ldr r3, [r1]
	ldr r0, _0223578C ; =0x04000050
	ldrsb r2, [r3, #0x1a]
	add r2, r2, #1
	strb r2, [r3, #0x1a]
	ldr r1, [r1]
	ldrsb r1, [r1, #0x1a]
	bl G2x_ChangeBlendBrightness_
	ldr r0, _02235788 ; =0x02243164
	ldr r0, [r0]
	ldrsb r0, [r0, #0x1a]
	cmp r0, #0
	ldmltia sp!, {r4, pc}
	ldr r1, _02235790 ; =MOD13_02235684
	mov r0, r4
	bl MOD13_0223C130
	ldmia sp!, {r4, pc}
	.align 2, 0
_02235788: .word 0x02243164
_0223578C: .word 0x04000050
_02235790: .word MOD13_02235684

	arm_func_start MOD13_02235794
MOD13_02235794: ; 0x02235794
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02235818 ; =0x02243164
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, [sp, #4]
	add r0, r0, #0xc
	str r0, [sp, #4]
	bl MOD13_022359B8
	ldr r0, [sp, #4]
	cmp r0, #0xc0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	ldr r0, _02235818 ; =0x02243164
	ldr r0, [r0]
	ldrb r0, [r0, #0x1e]
	cmp r0, #0
	beq _02235804
	ldr r1, _0223581C ; =MOD13_02235738
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02235804:
	ldr r1, _02235820 ; =MOD13_02235684
	mov r0, r4
	bl MOD13_0223C130
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02235818: .word 0x02243164
_0223581C: .word MOD13_02235738
_02235820: .word MOD13_02235684

	arm_func_start MOD13_02235824
MOD13_02235824: ; 0x02235824
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02235864 ; =0x02243164
	ldr r3, [r1]
	ldrb r2, [r3, #0x1d]
	add r2, r2, #1
	strb r2, [r3, #0x1d]
	ldr r1, [r1]
	ldrb r1, [r1, #0x1d]
	cmp r1, #8
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	ldr r1, _02235868 ; =MOD13_02235794
	bl MOD13_0223C130
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02235864: .word 0x02243164
_02235868: .word MOD13_02235794

	arm_func_start MOD13_0223586C
MOD13_0223586C: ; 0x0223586C
	stmdb sp!, {r4, lr}
	ldr r1, _02235918 ; =0x02243164
	mov r4, r0
	ldr r0, [r1]
	mov r1, #0
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #8]
	bl MOD13_02239ADC
	ldr r1, _02235918 ; =0x02243164
	mov r2, r0
	ldr r0, [r1]
	ldr r1, _0223591C ; =0x0223F6B0
	ldrb r3, [r0, #0x1c]
	mov r0, #0
	add r1, r1, r3, lsl #1
	ldrb r1, [r4, r1]
	add r1, r1, #1
	bl MOD13_02239E8C
	ldr r0, _02235918 ; =0x02243164
	ldr r2, _02235920 ; =0x0223F698
	ldr r0, [r0]
	ldr r1, _02235924 ; =0x0223F718
	ldrb lr, [r0, #0x1c]
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #8]
	add r2, r2, lr, lsl #1
	ldrb r3, [r4, r2]
	add r2, r1, lr, lsl #3
	mvn r1, #0
	mov ip, r3, lsl #2
	ldrh r2, [ip, r2]
	ldr r3, _02235928 ; =0x0223F71A
	add r3, r3, lr, lsl #3
	ldrh r3, [ip, r3]
	bl MOD13_02239888
	ldr r0, _02235918 ; =0x02243164
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #0
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #8]
	bl MOD13_02239814
	ldmia sp!, {r4, pc}
	.align 2, 0
_02235918: .word 0x02243164
_0223591C: .word 0x0223F6B0
_02235920: .word 0x0223F698
_02235924: .word 0x0223F718
_02235928: .word 0x0223F71A

	arm_func_start MOD13_0223592C
MOD13_0223592C: ; 0x0223592C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov sl, r0
	mov sb, r1
	bl MOD13_02239AD4
	mov r8, r0
	cmp r8, #0
	mov r7, #0
	addle sp, sp, #0xc
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add fp, sp, #0
	mov r6, r7
	mov r4, r7
	mov r5, #0x200
_02235964:
	mov r0, sl
	mov r1, r7
	mov r2, fp
	add r3, sp, #4
	bl MOD13_022397DC
	ldr r0, [sp, #4]
	cmp r0, sb
	blt _02235990
	cmp r0, #0xc0
	movlt r2, r6
	blt _02235994
_02235990:
	mov r2, r5
_02235994:
	mov r0, sl
	mov r1, r7
	mov r3, r4
	bl MOD13_02239A1C
	add r7, r7, #1
	cmp r7, r8
	blt _02235964
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}

	arm_func_start MOD13_022359B8
MOD13_022359B8: ; 0x022359B8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	ldr r1, _02235B4C ; =0x02243164
	mov sl, r0
	ldr r0, [r1]
	ldr r1, _02235B50 ; =0x0223F6E8
	ldrb r2, [r0, #0x1c]
	ldr r0, [r0]
	mov r3, sl
	mov r2, r2, lsl #2
	ldrh r2, [r1, r2]
	mvn r1, #0
	bl MOD13_02239888
	ldr r1, _02235B4C ; =0x02243164
	ldr r0, _02235B54 ; =0x0223F674
	ldr r5, [r1]
	ldr r2, _02235B50 ; =0x0223F6E8
	ldrb r3, [r5, #0x1c]
	ldrh r1, [r0, #2]
	ldrh r4, [r0]
	mov r0, r3, lsl #2
	ldrh r2, [r2, r0]
	ldr r0, [r5, #4]
	add r3, sl, r1
	add r2, r4, r2
	mvn r1, #0
	bl MOD13_02239888
	ldr r0, _02235B4C ; =0x02243164
	mov r1, sl
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD13_0223592C
	ldr r0, _02235B4C ; =0x02243164
	mov r1, sl
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD13_0223592C
	ldr r4, _02235B4C ; =0x02243164
	ldr r8, _02235B58 ; =0x0223F680
	ldr r0, [r4]
	mov sb, #0
	ldrb r0, [r0, #0x1c]
	ldrb r1, [r8, r0]
	cmp r1, #0
	ble _02235AE8
	ldr r7, _02235B5C ; =0x0223F698
	ldr r5, _02235B60 ; =0x0223F718
	ldr fp, _02235B50 ; =0x0223F6E8
	mvn r6, #0
_02235A7C:
	add r1, r7, r0, lsl #1
	ldrb ip, [sb, r1]
	add r2, r5, r0, lsl #3
	add r3, fp, r0, lsl #2
	add r0, r2, ip, lsl #2
	ldr r1, [r4]
	mov ip, ip, lsl #2
	ldrh r2, [ip, r2]
	ldrh r0, [r0, #2]
	add r1, r1, sb, lsl #2
	ldrh r3, [r3, #2]
	add ip, sl, r0
	ldr r0, [r1, #8]
	mov r1, r6
	sub r3, ip, r3
	bl MOD13_02239888
	ldr r0, [r4]
	mov r1, sl
	add r0, r0, sb, lsl #2
	ldr r0, [r0, #8]
	bl MOD13_0223592C
	ldr r0, [r4]
	add sb, sb, #1
	ldrb r0, [r0, #0x1c]
	ldrb r1, [r8, r0]
	cmp sb, r1
	blt _02235A7C
_02235AE8:
	and r1, sl, #0xff
	cmp r1, #0xc0
	movge r3, #0
	movge r1, r3
	ldrlt r2, _02235B64 ; =0x0223F702
	movlt r3, r0, lsl #2
	ldrlth r2, [r2, r3]
	mov r5, r0, lsl #2
	add r4, sp, #4
	addlt r3, r1, r2
	ldr r2, _02235B50 ; =0x0223F6E8
	cmp r3, #0xc0
	ldrh r0, [r2, r5]
	ldr r2, _02235B68 ; =0x0223F700
	movgt r3, #0xc0
	str r4, [sp]
	ldrh r2, [r2, r5]
	add r2, r0, r2
	bl MOD13_0223ABA8
	mov r0, #0
	mov r2, r4
	mov r1, r0
	bl MOD13_0223AD38
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02235B4C: .word 0x02243164
_02235B50: .word 0x0223F6E8
_02235B54: .word 0x0223F674
_02235B58: .word 0x0223F680
_02235B5C: .word 0x0223F698
_02235B60: .word 0x0223F718
_02235B64: .word 0x0223F702
_02235B68: .word 0x0223F700

	arm_func_start MOD13_02235B6C
MOD13_02235B6C: ; 0x02235B6C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _02235BDC ; =0x02243164
	mvn ip, #0
	ldr r3, [r2]
	mov r1, r0
	strb ip, [r3, #0x1b]
	ldr r3, [r2]
	ldrh r0, [r3, #0x18]
	add r0, r0, #1
	strh r0, [r3, #0x18]
	ldr r0, [r2]
	ldrh r0, [r0, #0x18]
	cmp r0, #0x78
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	mov r0, #0
	bl MOD13_0223C110
	ldr r1, _02235BE0 ; =MOD13_02235824
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02235BDC ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #0x14]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02235BDC: .word 0x02243164
_02235BE0: .word MOD13_02235824

	arm_func_start MOD13_02235BE4
MOD13_02235BE4: ; 0x02235BE4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #8
	ldr r5, _02235D20 ; =0x02243164
	ldr sl, _02235D24 ; =0x0223F680
	ldr r0, [r5]
	mov r4, #0
	ldrb r1, [r0, #0x1c]
	ldrb r0, [sl, r1]
	cmp r0, #0
	ble _02235C6C
	ldr sb, _02235D28 ; =0x0223F718
	ldr r8, _02235D2C ; =0x0223F698
	ldr r7, _02235D30 ; =0x0223F6BC
	add r6, sp, #0
_02235C1C:
	add r0, r8, r1, lsl #1
	ldrb r0, [r4, r0]
	add r3, sb, r1, lsl #3
	mov r2, r6
	add r0, r3, r0, lsl #2
	add r1, r7, r1, lsl #2
	bl MOD13_0223AB74
	mov r0, r6
	bl MOD13_0223B2B4
	cmp r0, #0
	ldrne r0, _02235D20 ; =0x02243164
	ldrne r0, [r0]
	strneb r4, [r0, #0x1b]
	bne _02235C6C
	ldr r0, [r5]
	add r4, r4, #1
	ldrb r1, [r0, #0x1c]
	ldrb r0, [sl, r1]
	cmp r4, r0
	blt _02235C1C
_02235C6C:
	mov r0, #1
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02235C98
	ldr r0, _02235D20 ; =0x02243164
	ldr r1, _02235D34 ; =0x0223F6A4
	ldr r2, [r0]
	ldrb r0, [r2, #0x1c]
	mov r0, r0, lsl #1
	ldrsb r0, [r1, r0]
	strb r0, [r2, #0x1b]
_02235C98:
	mov r0, #2
	bl MOD13_0223B3D4
	cmp r0, #0
	beq _02235CC4
	ldr r0, _02235D20 ; =0x02243164
	ldr r1, _02235D38 ; =0x0223F6A5
	ldr r2, [r0]
	ldrb r0, [r2, #0x1c]
	mov r0, r0, lsl #1
	ldrsb r0, [r1, r0]
	strb r0, [r2, #0x1b]
_02235CC4:
	ldr r0, _02235D20 ; =0x02243164
	ldr r2, _02235D24 ; =0x0223F680
	ldr r4, [r0]
	mov r0, #0
	ldrb r1, [r4, #0x1c]
	ldrb r1, [r2, r1]
	cmp r1, #0
	ble _02235D10
	ldrsb r3, [r4, #0x1b]
_02235CE8:
	cmp r0, r3
	bne _02235CFC
	bl MOD13_0223586C
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_02235CFC:
	ldrb r1, [r4, #0x1c]
	add r0, r0, #1
	ldrb r1, [r2, r1]
	cmp r0, r1
	blt _02235CE8
_02235D10:
	mvn r0, #0
	strb r0, [r4, #0x1b]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_02235D20: .word 0x02243164
_02235D24: .word 0x0223F680
_02235D28: .word 0x0223F718
_02235D2C: .word 0x0223F698
_02235D30: .word 0x0223F6BC
_02235D34: .word 0x0223F6A4
_02235D38: .word 0x0223F6A5

	arm_func_start MOD13_02235D3C
MOD13_02235D3C: ; 0x02235D3C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, _02235E10 ; =0x02243164
	mov r4, r0
	ldr r0, [r1]
	add r2, sp, #0
	ldr r0, [r0]
	add r3, sp, #4
	mov r1, #0
	bl MOD13_022397DC
	ldr r0, [sp, #4]
	ldr r1, _02235E10 ; =0x02243164
	sub r0, r0, #0xc
	ldr r1, [r1]
	str r0, [sp, #4]
	ldrb r2, [r1, #0x1c]
	ldr r1, _02235E14 ; =0x0223F6EA
	mov r2, r2, lsl #2
	ldrh r1, [r1, r2]
	cmp r0, r1
	ble _02235D9C
	bl MOD13_022359B8
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02235D9C:
	mov r0, r1
	bl MOD13_022359B8
	ldr r0, _02235E10 ; =0x02243164
	ldr r0, [r0]
	ldrb r0, [r0, #0x1c]
	cmp r0, #5
	bne _02235DDC
	mov r0, #0
	ldr r1, _02235E18 ; =MOD13_02235B6C
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02235E10 ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #0x14]
	b _02235DFC
_02235DDC:
	mov r0, #0
	ldr r1, _02235E1C ; =MOD13_02235BE4
	mov r2, r0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02235E10 ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #0x14]
_02235DFC:
	mov r1, r4
	mov r0, #1
	bl MOD13_0223C110
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02235E10: .word 0x02243164
_02235E14: .word 0x0223F6EA
_02235E18: .word MOD13_02235B6C
_02235E1C: .word MOD13_02235BE4

	arm_func_start MOD13_02235E20
MOD13_02235E20: ; 0x02235E20
	stmdb sp!, {r4, lr}
	ldr r1, _02235E74 ; =0x02243164
	mov r4, r0
	ldr r3, [r1]
	ldr r0, _02235E78 ; =0x04000050
	ldrsb r2, [r3, #0x1a]
	sub r2, r2, #1
	strb r2, [r3, #0x1a]
	ldr r1, [r1]
	ldrsb r1, [r1, #0x1a]
	bl G2x_ChangeBlendBrightness_
	ldr r1, _02235E74 ; =0x02243164
	mvn r0, #0xb
	ldr r1, [r1]
	ldrsb r1, [r1, #0x1a]
	cmp r1, r0
	ldmgtia sp!, {r4, pc}
	ldr r1, _02235E7C ; =MOD13_02235D3C
	mov r0, r4
	bl MOD13_0223C130
	ldmia sp!, {r4, pc}
	.align 2, 0
_02235E74: .word 0x02243164
_02235E78: .word 0x04000050
_02235E7C: .word MOD13_02235D3C

	arm_func_start MOD13_02235E80
MOD13_02235E80: ; 0x02235E80
	ldr r0, _02235E98 ; =0x02243164
	ldr r0, [r0]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_02235E98: .word 0x02243164

	arm_func_start MOD13_02235E9C
MOD13_02235E9C: ; 0x02235E9C
	ldr r0, _02235EAC ; =0x02243164
	ldr r0, [r0]
	ldrsb r0, [r0, #0x1b]
	bx lr
	.align 2, 0
_02235EAC: .word 0x02243164

	arm_func_start MOD13_02235EB0
MOD13_02235EB0: ; 0x02235EB0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02235EF4 ; =0x02243164
	mov r0, #0
	ldr r1, [r1]
	ldr r1, [r1, #0x14]
	bl MOD13_0223C110
	ldr r1, _02235EF8 ; =MOD13_02235824
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _02235EF4 ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #0x14]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02235EF4: .word 0x02243164
_02235EF8: .word MOD13_02235824

	arm_func_start MOD13_02235EFC
MOD13_02235EFC: ; 0x02235EFC
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x2c
	ldr r5, _02236224 ; =0x0223F688
	ldr r4, _02236228 ; =0x0224307C
	ldrb sl, [r5]
	ldrb sb, [r5, #1]
	ldrb r8, [r5, #2]
	ldrb r7, [r5, #3]
	ldrb r6, [r5, #4]
	ldrb r5, [r5, #5]
	mov fp, r0
	str r2, [sp, #0x14]
	mov r2, r3
	str r1, [sp, #0x10]
	ldr r0, [r4]
	ldr r3, [sp, #0x50]
	mov r1, fp
	strb sl, [sp, #0x20]
	strb sb, [sp, #0x21]
	strb r8, [sp, #0x22]
	strb r7, [sp, #0x23]
	strb r6, [sp, #0x24]
	strb r5, [sp, #0x25]
	bl MOD13_0222352C
	str r0, [sp, #0x18]
	mov r0, #0x20
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r2, _0223622C ; =0x02243164
	ldr r1, [sp, #0x10]
	str r0, [r2]
	strb r1, [r0, #0x1c]
	ldr r1, [r2]
	mvn r3, #1
	strb r3, [r1, #0x1b]
	ldr r3, [r2]
	ldr r2, [sp, #0x14]
	ldr r0, _02236230 ; =0x04000050
	strb r2, [r3, #0x1e]
	mov r1, #0x1f
	mov r2, #0
	bl G2x_SetBlendBrightness_
	mov r0, #0
	ldr r3, _02236234 ; =0x0223F678
	ldr r1, [sp, #0x10]
	mov r2, r0
	ldrb r1, [r3, r1]
	bl MOD13_02239E0C
	ldr r3, _0223622C ; =0x02243164
	mvn r1, #0
	ldr r4, [r3]
	mov r2, #0x100
	str r0, [r4]
	ldr r0, [r3]
	mov r3, #0
	ldr r0, [r0]
	bl MOD13_02239888
	ldr r0, _0223622C ; =0x02243164
	mvn r1, #0
	ldr r0, [r0]
	mov r2, #0
	ldr r0, [r0]
	bl MOD13_02239814
	ldr r2, _02236238 ; =0x0223F680
	ldr r0, [sp, #0x10]
	mov sl, #0
	ldrb r0, [r2, r0]
	cmp r0, #0
	ble _0223609C
	ldr r0, [sp, #0x10]
	ldr r1, _0223623C ; =0x0223F6B0
	ldr r4, _0223622C ; =0x02243164
	add r8, r2, r0
	add sb, r1, r0, lsl #1
	str sl, [sp, #0x1c]
	mov r5, sl
	mov fp, sl
	mvn r7, #0
	mov r6, #0x100
_02236038:
	ldr r0, [sp, #0x1c]
	ldrb r1, [sb]
	mov r2, r0
	bl MOD13_02239E0C
	ldr r2, [r4]
	mov r1, r7
	add r2, r2, sl, lsl #2
	str r0, [r2, #8]
	ldr r0, [r4]
	mov r2, r6
	add r0, r0, sl, lsl #2
	ldr r0, [r0, #8]
	mov r3, r5
	bl MOD13_02239888
	ldr r0, [r4]
	mov r1, r7
	add r0, r0, sl, lsl #2
	ldr r0, [r0, #8]
	mov r2, fp
	bl MOD13_02239814
	ldrb r0, [r8]
	add sl, sl, #1
	add sb, sb, #1
	cmp sl, r0
	blt _02236038
_0223609C:
	add r1, sp, #0x28
	str r1, [sp]
	mov r0, #0
	mov r1, #0x20
	mov r2, #0xc
	mov r3, #1
	str r0, [sp, #4]
	bl MOD13_0223A9A4
	ldr r1, _0223622C ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #0x10]
	mov r0, #0
	ldr r1, [sp, #0x28]
	mov r2, r0
	bl MOD13_02239B74
	ldr r1, _0223622C ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #4]
	bl MOD13_0221EF88
	ldr r1, [sp, #0x10]
	mov r3, #2
	mov r5, r1, lsl #2
	ldr r1, _02236240 ; =0x0223F6D2
	ldr r2, _0223622C ; =0x02243164
	ldrh r4, [r1, r5]
	mov r1, #0
	str r4, [sp]
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	ldr r3, _02236244 ; =0x0223F6D0
	str r0, [sp, #0xc]
	ldr r0, [r2]
	ldrh r3, [r3, r5]
	ldr r0, [r0, #0x10]
	mov r2, r1
	bl MOD13_0223A4F0
	ldr r0, _0223622C ; =0x02243164
	mov r2, #0
	ldr r3, [r0]
	mov r1, #0x100
	str r2, [sp]
	ldr r0, [r3, #0x10]
	ldr r3, [r3, #4]
	bl MOD13_0223A440
	mov r0, #0
	mov r1, r0
	mov r2, #0x1f
	mov r3, r0
	bl MOD13_0223ABCC
	ldr r3, _0223622C ; =0x02243164
	add r4, sp, #0x20
	ldr r3, [r3]
	mov r0, #0
	ldrb r3, [r3, #0x1c]
	mov r1, #1
	mov r2, #0x1f
	ldrb r3, [r4, r3]
	bl MOD13_0223ABCC
	mov r0, #0
	mov r1, #3
	mov r2, #0x1f
	mov r3, #1
	bl MOD13_0223ABCC
	ldr r2, _02236248 ; =0x0223F690
	mov r0, #0
	mov r1, #1
	bl MOD13_0223AD38
	mov r0, #0xc0
	bl MOD13_022359B8
	mov r2, #0x4000000
	ldr r0, [sp, #0x14]
	ldr r1, [r2]
	cmp r0, #0
	bic r0, r1, #0xe000
	orr r0, r0, #0x6000
	str r0, [r2]
	beq _022361FC
	ldr r1, _0223624C ; =MOD13_02235E20
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0223622C ; =0x02243164
	add sp, sp, #0x2c
	ldr r1, [r1]
	str r0, [r1, #0x14]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_022361FC:
	ldr r1, _02236250 ; =MOD13_02235D3C
	mov r0, #1
	mov r2, #0
	mov r3, #0x78
	bl MOD13_0223C1C4
	ldr r1, _0223622C ; =0x02243164
	ldr r1, [r1]
	str r0, [r1, #0x14]
	add sp, sp, #0x2c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02236224: .word 0x0223F688
_02236228: .word 0x0224307C
_0223622C: .word 0x02243164
_02236230: .word 0x04000050
_02236234: .word 0x0223F678
_02236238: .word 0x0223F680
_0223623C: .word 0x0223F6B0
_02236240: .word 0x0223F6D2
_02236244: .word 0x0223F6D0
_02236248: .word 0x0223F690
_0223624C: .word MOD13_02235E20
_02236250: .word MOD13_02235D3C

	arm_func_start MOD13_02236254
MOD13_02236254: ; 0x02236254
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r1, _02236310 ; =0x02243168
	mov r5, #1
	ldr lr, [r1]
	ldrh r4, [lr, #2]
	mov ip, r5
	add r1, lr, #0x24
	mov r6, #0x1e
_02236274:
	mov r2, ip, lsl r5
	ands r2, r4, r2
	beq _022362F4
	sub r2, r5, #1
	mul r3, r2, r6
	ldrb r8, [r0]
	ldrb r7, [r1, r3]
	add r2, r1, r3
	cmp r8, r7
	bne _022362F4
	ldrb r8, [r0, #1]
	ldrb r7, [r2, #1]
	cmp r8, r7
	bne _022362F4
	ldrb r8, [r0, #2]
	ldrb r7, [r2, #2]
	cmp r8, r7
	bne _022362F4
	ldrb r8, [r0, #3]
	ldrb r7, [r2, #3]
	cmp r8, r7
	bne _022362F4
	ldrb r8, [r0, #4]
	ldrb r7, [r2, #4]
	cmp r8, r7
	bne _022362F4
	ldrb r7, [r0, #5]
	ldrb r2, [r2, #5]
	cmp r7, r2
	addeq r0, lr, r3
	ldreqh r0, [r0, #0x2a]
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
_022362F4:
	add r2, r5, #1
	mov r2, r2, lsl #0x10
	mov r5, r2, lsr #0x10
	cmp r5, #2
	blo _02236274
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02236310: .word 0x02243168

	arm_func_start MOD13_02236314
MOD13_02236314: ; 0x02236314
	ldr r1, _02236344 ; =0x02243168
	mov r2, #1
	ldr r3, [r1]
	mov r1, r2, lsl r0
	ldrh r2, [r3, #2]
	ands r1, r2, r1
	subne r1, r0, #1
	addne r2, r3, #0xe
	movne r0, #0x1e
	mlane r0, r1, r0, r2
	moveq r0, #0
	bx lr
	.align 2, 0
_02236344: .word 0x02243168

	arm_func_start MOD13_02236348
MOD13_02236348: ; 0x02236348
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x14
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02236410 ; =0x02243168
	mov r2, #1
	ldr r3, [r1]
	mov r1, r2, lsl r4
	mov r1, r1, lsl #0x10
	ldrh r2, [r3, #2]
	mov r4, r1, lsr #0x10
	mov r5, r0
	ands r1, r2, r4
	bne _02236390
	bl OS_RestoreInterrupts
	add sp, sp, #0x14
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_02236390:
	add r1, sp, #0
	mov r0, r3
	mov r2, #0xe
	bl MI_CpuCopy8
	mov r0, r5
	bl OS_RestoreInterrupts
	ldrh r0, [sp, #4]
	ands r0, r0, r4
	addne sp, sp, #0x14
	movne r0, #2
	ldmneia sp!, {r4, r5, pc}
	ldrh r0, [sp, #6]
	ands r0, r0, r4
	addne sp, sp, #0x14
	movne r0, #3
	ldmneia sp!, {r4, r5, pc}
	ldrh r0, [sp, #8]
	ands r0, r0, r4
	addne sp, sp, #0x14
	movne r0, #4
	ldmneia sp!, {r4, r5, pc}
	ldrh r0, [sp, #0xa]
	ands r0, r0, r4
	addne sp, sp, #0x14
	movne r0, #5
	ldmneia sp!, {r4, r5, pc}
	ldrh r0, [sp, #0xc]
	ands r0, r0, r4
	movne r0, #6
	moveq r0, #1
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02236410: .word 0x02243168

	arm_func_start MOD13_02236414
MOD13_02236414: ; 0x02236414
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _02236468 ; =0x02243168
	ldr r1, _0223646C ; =0x0224316C
	ldr r2, [r2]
	add r5, r2, #2
	add r4, r2, #4
	add lr, r2, #6
	add ip, r2, #8
	add r3, r2, #0xa
	add r2, r2, #0xc
	str r5, [r1]
	str r4, [r1, #4]
	str lr, [r1, #8]
	str ip, [r1, #0xc]
	str r3, [r1, #0x10]
	str r2, [r1, #0x14]
	ldr r0, [r1, r0, lsl #2]
	ldrh r0, [r0]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02236468: .word 0x02243168
_0223646C: .word 0x0224316C

	arm_func_start MOD13_02236470
MOD13_02236470: ; 0x02236470
	ldr r0, _02236480 ; =0x02243168
	ldr r0, [r0]
	ldrh r0, [r0]
	bx lr
	.align 2, 0
_02236480: .word 0x02243168

	arm_func_start MOD13_02236484
MOD13_02236484: ; 0x02236484
	ldr r1, _02236494 ; =0x02243168
	ldr r1, [r1]
	strh r0, [r1]
	bx lr
	.align 2, 0
_02236494: .word 0x02243168

	arm_func_start MOD13_02236498
MOD13_02236498: ; 0x02236498
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	mov r4, r2
	cmp r1, #0xe
	addls pc, pc, r1, lsl #2
	b _022367CC
_022364B0: ; jump table
	b _022367CC ; case 0
	ldmia sp!, {r4, r5, r6, pc} ; case 1
	b _022364EC ; case 2
	b _02236574 ; case 3
	ldmia sp!, {r4, r5, r6, pc} ; case 4
	ldmia sp!, {r4, r5, r6, pc} ; case 5
	ldmia sp!, {r4, r5, r6, pc} ; case 6
	b _022366AC ; case 7
	ldmia sp!, {r4, r5, r6, pc} ; case 8
	b _022366DC ; case 9
	b _022365FC ; case 10
	ldmia sp!, {r4, r5, r6, pc} ; case 11
	b _02236724 ; case 12
	b _02236780 ; case 13
	b _02236668 ; case 14
_022364EC:
	bl MOD13_02236470
	cmp r0, #2
	ldmneia sp!, {r4, r5, r6, pc}
	ldr r0, _022367D4 ; =0x02243168
	ldr r6, [r0]
	bl OS_DisableInterrupts
	ldrh r2, [r6, #2]
	mov r1, #1
	orr r1, r2, r1, lsl r5
	strh r1, [r6, #2]
	bl OS_RestoreInterrupts
	ldr r1, _022367D4 ; =0x02243168
	sub r3, r5, #1
	mov r0, #0x1e
	mul r0, r3, r0
	ldr r2, [r1]
	add r3, r2, #0x24
	ldrb r2, [r4, #0xa]
	add ip, r3, r0
	strb r2, [r3, r0]
	ldrb r2, [r4, #0xb]
	strb r2, [ip, #1]
	ldrb r2, [r4, #0xc]
	strb r2, [ip, #2]
	ldrb r2, [r4, #0xd]
	strb r2, [ip, #3]
	ldrb r2, [r4, #0xe]
	strb r2, [ip, #4]
	ldrb r2, [r4, #0xf]
	strb r2, [ip, #5]
	ldr r1, [r1]
	add r0, r1, r0
	strh r5, [r0, #0x2a]
	ldmia sp!, {r4, r5, r6, pc}
_02236574:
	bl MOD13_02236348
	cmp r0, #6
	ldmeqia sp!, {r4, r5, r6, pc}
	mov r0, #1
	mvn r0, r0, lsl r5
	mov r4, r0, lsl #0x10
	bl OS_DisableInterrupts
	ldr r1, _022367D4 ; =0x02243168
	ldr r3, [r1]
	ldrh r2, [r3, #2]
	and r2, r2, r4, lsr #16
	strh r2, [r3, #2]
	ldr r3, [r1]
	ldrh r2, [r3, #4]
	and r2, r2, r4, lsr #16
	strh r2, [r3, #4]
	ldr r3, [r1]
	ldrh r2, [r3, #6]
	and r2, r2, r4, lsr #16
	strh r2, [r3, #6]
	ldr r3, [r1]
	ldrh r2, [r3, #8]
	and r2, r2, r4, lsr #16
	strh r2, [r3, #8]
	ldr r3, [r1]
	ldrh r2, [r3, #0xa]
	and r2, r2, r4, lsr #16
	strh r2, [r3, #0xa]
	ldr r2, [r1]
	ldrh r1, [r2, #0xc]
	and r1, r1, r4, lsr #16
	strh r1, [r2, #0xc]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, r5, r6, pc}
_022365FC:
	bl MOD13_02236470
	cmp r0, #2
	beq _02236614
	mov r0, r5
	bl MOD13_02236B38
	ldmia sp!, {r4, r5, r6, pc}
_02236614:
	ldr r0, _022367D4 ; =0x02243168
	mov r1, #1
	ldr r3, [r0]
	mov r0, r5
	ldrh r2, [r3, #4]
	orr r1, r2, r1, lsl r5
	strh r1, [r3, #4]
	bl MOD13_02236C1C
	mov r0, r5
	bl MOD13_022132CC
	cmp r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r1, _022367D4 ; =0x02243168
	sub r2, r5, #1
	ldr r3, [r1]
	mov r1, #0x1e
	add r3, r3, #0xe
	mla r1, r2, r1, r3
	mov r2, #0x16
	bl MI_CpuCopy8
	ldmia sp!, {r4, r5, r6, pc}
_02236668:
	ldr r0, _022367D4 ; =0x02243168
	mov r4, #1
	ldr r3, [r0]
	mvn r1, r4, lsl r5
	ldrh r2, [r3, #4]
	and r1, r2, r1
	strh r1, [r3, #4]
	ldr r1, [r0]
	ldrh r0, [r1, #6]
	orr r0, r0, r4, lsl r5
	strh r0, [r1, #6]
	bl MOD13_02236470
	cmp r0, #3
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, r5
	bl MOD13_02236A54
	ldmia sp!, {r4, r5, r6, pc}
_022366AC:
	ldr r0, _022367D4 ; =0x02243168
	mov r4, #1
	ldr r3, [r0]
	mvn r1, r4, lsl r5
	ldrh r2, [r3, #8]
	and r1, r2, r1
	strh r1, [r3, #8]
	ldr r1, [r0]
	ldrh r0, [r1, #0xa]
	orr r0, r0, r4, lsl r5
	strh r0, [r1, #0xa]
	ldmia sp!, {r4, r5, r6, pc}
_022366DC:
	ldr r0, _022367D4 ; =0x02243168
	mov r4, #1
	ldr r3, [r0]
	mvn r1, r4, lsl r5
	ldrh r2, [r3, #0xa]
	and r1, r2, r1
	strh r1, [r3, #0xa]
	ldr r2, [r0]
	ldrh r1, [r2, #0xc]
	orr r1, r1, r4, lsl r5
	strh r1, [r2, #0xc]
	ldr r0, [r0]
	ldrh r1, [r0, #2]
	ldrh r0, [r0, #0xc]
	cmp r1, r0
	ldmneia sp!, {r4, r5, r6, pc}
	bl MOD13_02214F18
	ldmia sp!, {r4, r5, r6, pc}
_02236724:
	bl MOD13_02236470
	cmp r0, #4
	bne _0223673C
	mov r0, #5
	bl MOD13_02236484
	b _02236744
_0223673C:
	mov r0, #0
	bl MOD13_02236484
_02236744:
	ldr r0, _022367D4 ; =0x02243168
	ldr r0, [r0]
	add r0, r0, #0x1b000
	ldr r1, [r0, #0x144]
	cmp r1, #0
	movne r1, #0
	strne r1, [r0, #0x144]
	ldr r0, _022367D4 ; =0x02243168
	ldr r0, [r0]
	add r0, r0, #0x1b000
	ldr r1, [r0, #0x140]
	cmp r1, #0
	movne r1, #0
	strne r1, [r0, #0x140]
	ldmia sp!, {r4, r5, r6, pc}
_02236780:
	ldrh r0, [r4]
	cmp r0, #8
	bgt _022367B8
	cmp r0, #8
	ldmgeia sp!, {r4, r5, r6, pc}
	cmp r0, #2
	ldmgtia sp!, {r4, r5, r6, pc}
	cmp r0, #1
	ldmltia sp!, {r4, r5, r6, pc}
	cmp r0, #1
	beq _022367C0
	cmp r0, #2
	beq _022367C0
	ldmia sp!, {r4, r5, r6, pc}
_022367B8:
	cmp r0, #9
	ldmneia sp!, {r4, r5, r6, pc}
_022367C0:
	mov r0, #7
	bl MOD13_02236484
	ldmia sp!, {r4, r5, r6, pc}
_022367CC:
	bl OS_Terminate
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_022367D4: .word 0x02243168

	arm_func_start MOD13_022367D8
MOD13_022367D8: ; 0x022367D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #6
	bl MOD13_02236484
	bl MOD13_02214F18
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_022367F4
MOD13_022367F4: ; 0x022367F4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov r8, #0
	mov sb, #1
	ldr r4, _022368F8 ; =0x02243168
	mov r6, sb
	mov r5, #3
_02236810:
	ldr r0, [r4]
	mov r7, r6, lsl sb
	ldrh r0, [r0, #0xa]
	ands r0, r0, r7
	beq _022368BC
	mov r0, sb
	mov r1, r5
	bl MOD13_02213174
	cmp r0, #0
	orrne r0, r8, r7
	movne r0, r0, lsl #0x10
	movne r8, r0, lsr #0x10
	bne _022368BC
	mvn r0, r7
	mov r7, r0, lsl #0x10
	bl OS_DisableInterrupts
	ldr r2, [r4]
	ldrh r1, [r2, #2]
	and r1, r1, r7, lsr #16
	strh r1, [r2, #2]
	ldr r2, [r4]
	ldrh r1, [r2, #4]
	and r1, r1, r7, lsr #16
	strh r1, [r2, #4]
	ldr r2, [r4]
	ldrh r1, [r2, #6]
	and r1, r1, r7, lsr #16
	strh r1, [r2, #6]
	ldr r2, [r4]
	ldrh r1, [r2, #8]
	and r1, r1, r7, lsr #16
	strh r1, [r2, #8]
	ldr r2, [r4]
	ldrh r1, [r2, #0xa]
	and r1, r1, r7, lsr #16
	strh r1, [r2, #0xa]
	ldr r2, [r4]
	ldrh r1, [r2, #0xc]
	and r1, r1, r7, lsr #16
	strh r1, [r2, #0xc]
	bl OS_RestoreInterrupts
	mov r0, sb
	bl MOD13_02214D6C
_022368BC:
	add r0, sb, #1
	mov r0, r0, lsl #0x10
	mov sb, r0, lsr #0x10
	cmp sb, #0x10
	blo _02236810
	cmp r8, #0
	bne _022368E8
	mov r0, #7
	bl MOD13_02236484
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_022368E8:
	mov r0, #4
	bl MOD13_02236484
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_022368F8: .word 0x02243168

	arm_func_start MOD13_022368FC
MOD13_022368FC: ; 0x022368FC
	stmdb sp!, {r4, r5, r6, lr}
	ldr r4, _02236964 ; =0x02243168
	ldr r0, [r4]
	ldrh r0, [r0, #2]
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	mov r6, #1
	mov r5, r6
_02236920:
	ldr r1, [r4]
	mov r0, r5, lsl r6
	ldrh r1, [r1, #2]
	ands r0, r1, r0
	beq _02236948
	mov r0, r6
	bl MOD13_02213270
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
_02236948:
	add r0, r6, #1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, #0x10
	blo _02236920
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02236964: .word 0x02243168

	arm_func_start MOD13_02236968
MOD13_02236968: ; 0x02236968
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02236484
	mov r5, #1
	ldr r7, _02236A50 ; =0x02243168
	mov r4, r5
_02236984:
	ldr r1, [r7]
	mov r2, r4, lsl r5
	ldrh r0, [r1, #2]
	ands r0, r0, r2
	beq _02236A34
	ldrh r0, [r1, #4]
	ands r0, r0, r2
	bne _02236A34
	ldrh r0, [r1, #6]
	ands r0, r0, r2
	bne _02236A2C
	mvn r0, r2
	mov r6, r0, lsl #0x10
	bl OS_DisableInterrupts
	ldr r2, [r7]
	ldrh r1, [r2, #2]
	and r1, r1, r6, lsr #16
	strh r1, [r2, #2]
	ldr r2, [r7]
	ldrh r1, [r2, #4]
	and r1, r1, r6, lsr #16
	strh r1, [r2, #4]
	ldr r2, [r7]
	ldrh r1, [r2, #6]
	and r1, r1, r6, lsr #16
	strh r1, [r2, #6]
	ldr r2, [r7]
	ldrh r1, [r2, #8]
	and r1, r1, r6, lsr #16
	strh r1, [r2, #8]
	ldr r2, [r7]
	ldrh r1, [r2, #0xa]
	and r1, r1, r6, lsr #16
	strh r1, [r2, #0xa]
	ldr r2, [r7]
	ldrh r1, [r2, #0xc]
	and r1, r1, r6, lsr #16
	strh r1, [r2, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r5
	bl MOD13_02214D6C
	b _02236A34
_02236A2C:
	mov r0, r5
	bl MOD13_02236A54
_02236A34:
	add r0, r5, #1
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	cmp r5, #0x10
	blo _02236984
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02236A50: .word 0x02243168

	arm_func_start MOD13_02236A54
MOD13_02236A54: ; 0x02236A54
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r1, #2
	mov r4, r0
	bl MOD13_02213174
	cmp r0, #0
	bne _02236AF8
	mov r0, #1
	mvn r0, r0, lsl r4
	mov r5, r0, lsl #0x10
	bl OS_DisableInterrupts
	ldr r1, _02236B34 ; =0x02243168
	ldr r3, [r1]
	ldrh r2, [r3, #2]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #2]
	ldr r3, [r1]
	ldrh r2, [r3, #4]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #4]
	ldr r3, [r1]
	ldrh r2, [r3, #6]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #6]
	ldr r3, [r1]
	ldrh r2, [r3, #8]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #8]
	ldr r3, [r1]
	ldrh r2, [r3, #0xa]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #0xa]
	ldr r2, [r1]
	ldrh r1, [r2, #0xc]
	and r1, r1, r5, lsr #16
	strh r1, [r2, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r4
	bl MOD13_02214D6C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02236AF8:
	bl OS_DisableInterrupts
	ldr r1, _02236B34 ; =0x02243168
	mov ip, #1
	ldr r5, [r1]
	mvn r2, ip, lsl r4
	ldrh r3, [r5, #6]
	and r2, r3, r2
	strh r2, [r5, #6]
	ldr r2, [r1]
	ldrh r1, [r2, #8]
	orr r1, r1, ip, lsl r4
	strh r1, [r2, #8]
	bl OS_RestoreInterrupts
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02236B34: .word 0x02243168

	arm_func_start MOD13_02236B38
MOD13_02236B38: ; 0x02236B38
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r1, #0
	mov r4, r0
	bl MOD13_02213174
	cmp r0, #0
	bne _02236BDC
	mov r0, #1
	mvn r0, r0, lsl r4
	mov r5, r0, lsl #0x10
	bl OS_DisableInterrupts
	ldr r1, _02236C18 ; =0x02243168
	ldr r3, [r1]
	ldrh r2, [r3, #2]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #2]
	ldr r3, [r1]
	ldrh r2, [r3, #4]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #4]
	ldr r3, [r1]
	ldrh r2, [r3, #6]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #6]
	ldr r3, [r1]
	ldrh r2, [r3, #8]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #8]
	ldr r3, [r1]
	ldrh r2, [r3, #0xa]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #0xa]
	ldr r2, [r1]
	ldrh r1, [r2, #0xc]
	and r1, r1, r5, lsr #16
	strh r1, [r2, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r4
	bl MOD13_02214D6C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02236BDC:
	bl OS_DisableInterrupts
	ldr r1, _02236C18 ; =0x02243168
	mov r2, #1
	ldr r3, [r1]
	mvn r4, r2, lsl r4
	ldrh r2, [r3, #4]
	and r2, r2, r4
	strh r2, [r3, #4]
	ldr r2, [r1]
	ldrh r1, [r2, #2]
	and r1, r1, r4
	strh r1, [r2, #2]
	bl OS_RestoreInterrupts
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02236C18: .word 0x02243168

	arm_func_start MOD13_02236C1C
MOD13_02236C1C: ; 0x02236C1C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r1, #1
	mov r4, r0
	bl MOD13_02213174
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #1
	mvn r0, r0, lsl r4
	mov r5, r0, lsl #0x10
	bl OS_DisableInterrupts
	ldr r1, _02236CC4 ; =0x02243168
	ldr r3, [r1]
	ldrh r2, [r3, #2]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #2]
	ldr r3, [r1]
	ldrh r2, [r3, #4]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #4]
	ldr r3, [r1]
	ldrh r2, [r3, #6]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #6]
	ldr r3, [r1]
	ldrh r2, [r3, #8]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #8]
	ldr r3, [r1]
	ldrh r2, [r3, #0xa]
	and r2, r2, r5, lsr #16
	strh r2, [r3, #0xa]
	ldr r2, [r1]
	ldrh r1, [r2, #0xc]
	and r1, r1, r5, lsr #16
	strh r1, [r2, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r4
	bl MOD13_02214D6C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02236CC4: .word 0x02243168

	arm_func_start MOD13_02236CC8
MOD13_02236CC8: ; 0x02236CC8
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x48
	mov r6, r0
	ldr r0, [r6]
	mov r4, #0
	cmp r0, #0
	moveq r5, r4
	beq _02236D10
	add r0, sp, #0
	bl FS_InitFile
	ldr r1, [r6]
	add r0, sp, #0
	bl FS_OpenFile
	cmp r0, #0
	addeq sp, sp, #0x48
	moveq r0, r4
	ldmeqia sp!, {r4, r5, r6, pc}
	add r5, sp, #0
_02236D10:
	mov r0, r5
	bl MOD13_0221411C
	cmp r0, #0
	beq _02236D7C
	ldr r1, _02236D98 ; =0x02243168
	ldr r0, [r1]
	add r2, r0, #0x2c
	add r0, r0, #0x1b000
	str r2, [r0, #0x144]
	ldr r0, [r1]
	add r0, r0, #0x1b000
	ldr r1, [r0, #0x144]
	cmp r1, #0
	beq _02236D7C
	mov r0, r5
	mov r2, #0x10000
	bl MOD13_02213CB0
	cmp r0, #0
	beq _02236D7C
	ldr r1, _02236D98 ; =0x02243168
	mov r0, r6
	ldr r1, [r1]
	add r1, r1, #0x1b000
	ldr r1, [r1, #0x144]
	bl MOD13_02213944
	cmp r0, #0
	movne r4, #1
_02236D7C:
	add r0, sp, #0
	cmp r5, r0
	bne _02236D8C
	bl FS_CloseFile
_02236D8C:
	mov r0, r4
	add sp, sp, #0x48
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02236D98: .word 0x02243168

	arm_func_start MOD13_02236D9C
MOD13_02236D9C: ; 0x02236D9C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r4, r1
	mov r0, #2
	bl MOD13_02236484
	mov r0, r4
	bl MOD13_02215028
	cmp r0, #0
	beq _02236DD4
	mov r0, #7
	bl MOD13_02236484
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02236DD4:
	mov r0, r5
	bl MOD13_02236CC8
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	bl OS_Terminate
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}

	arm_func_start MOD13_02236DF4
MOD13_02236DF4: ; 0x02236DF4
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x7c
	mov r5, r0
	add r0, sp, #0x28
	mov r4, r1
	bl OS_GetOwnerInfo
	ldrb r2, [sp, #4]
	ldrb r1, [sp, #0x29]
	ldrh r3, [sp, #0x40]
	bic r2, r2, #0xf
	and r1, r1, #0xf
	orr r2, r2, r1
	strb r2, [sp, #4]
	add r0, sp, #0x2c
	add r1, sp, #6
	mov r2, r3, lsl #1
	strb r3, [sp, #5]
	bl MI_CpuCopy8
	ldrb r0, [sp, #4]
	add ip, sp, #0x1a
	mov r1, #0
	bic r0, r0, #0xf0
	strb r0, [sp, #4]
	strh r1, [ip]
	strh r1, [ip, #2]
	strh r1, [ip, #4]
	strh r1, [ip, #6]
	strh r1, [ip, #8]
	strh r1, [ip, #0xa]
	ldr r0, _02236F04 ; =0x02243168
	strh r1, [ip, #0xc]
	ldr lr, [r0]
	mov r2, #3
	mov r3, lr
_02236E7C:
	ldrh r1, [ip], #2
	ldrh r0, [ip], #2
	subs r2, r2, #1
	strh r1, [r3], #2
	strh r0, [r3], #2
	bne _02236E7C
	ldrh r2, [ip]
	ldr r0, _02236F08 ; =0x00010040
	add r1, lr, #0x1b000
	strh r2, [r3]
	add r0, lr, r0
	str r0, [r1, #0x140]
	mov r1, #2
	str r1, [sp]
	ldr r0, _02236F04 ; =0x02243168
	add r1, sp, #4
	ldr r0, [r0]
	mov r2, r5
	add r0, r0, #0x1b000
	ldr r0, [r0, #0x140]
	mov r3, r4
	bl MOD13_02215474
	cmp r0, #0
	beq _02236EE0
	bl OS_Terminate
_02236EE0:
	mov r0, #0x100
	mov r1, #1
	bl MOD13_02215360
	ldr r0, _02236F0C ; =MOD13_02236498
	bl MOD13_02213368
	mov r0, #1
	bl MOD13_02236484
	add sp, sp, #0x7c
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02236F04: .word 0x02243168
_02236F08: .word 0x00010040
_02236F0C: .word MOD13_02236498

	arm_func_start MOD13_02236F10
MOD13_02236F10: ; 0x02236F10
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _02236F54 ; =0x02243168
	ldr r1, _02236F58 ; =0x0001B160
	str r0, [r2]
	add r0, r0, r1
	bl MOD13_0223831C
	ldr r1, _02236F54 ; =0x02243168
	mov r2, #0
	ldr r0, [r1]
	add r0, r0, #0x1b000
	str r2, [r0, #0x140]
	ldr r0, [r1]
	add r0, r0, #0x1b000
	str r2, [r0, #0x144]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02236F54: .word 0x02243168
_02236F58: .word 0x0001B160

	arm_func_start MOD13_02236F5C
MOD13_02236F5C: ; 0x02236F5C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02236FB0 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	cmp r0, #1
	beq _02236F7C
	bl OS_Terminate
_02236F7C:
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _02236FB4 ; =MOD13_0223794C
	bl WM_End
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	mov r0, #9
	bl MOD13_02238294
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02236FB0: .word 0x02243188
_02236FB4: .word MOD13_0223794C

	arm_func_start MOD13_02236FB8
MOD13_02236FB8: ; 0x02236FB8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022370F8 ; =0x02243188
	ldr r0, [r0]
	ldr r2, [r0, #0x40]
	cmp r2, #1
	bne _02236FFC
	ldr r0, _022370FC ; =0x02243184
	ldr r2, [r0]
	cmp r2, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r1, _02237100 ; =0x022407D0
	mov r0, #0x8000000
	blx r2
	add sp, sp, #4
	ldmia sp!, {pc}
_02236FFC:
	ldr r0, _022370FC ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	beq _02237018
	ldr r1, _02237104 ; =0x022407F4
	mov r0, #0x8000000
	blx r3
_02237018:
	ldr r0, _022370F8 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	cmp r0, #6
	beq _02237050
	cmp r0, #5
	beq _02237050
	cmp r0, #4
	beq _02237050
	mov r0, #3
	bl MOD13_02238294
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
_02237050:
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _022370F8 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x44]
	cmp r0, #5
	addls pc, pc, r0, lsl #2
	b _022370F0
_02237070: ; jump table
	b _022370DC ; case 0
	b _022370A4 ; case 1
	b _022370C0 ; case 2
	b _02237088 ; case 3
	b _022370DC ; case 4
	b _022370A4 ; case 5
_02237088:
	bl MOD13_02237AE4
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
_022370A4:
	bl MOD13_02237AA8
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
_022370C0:
	bl MOD13_02237C48
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
_022370DC:
	bl MOD13_02237C0C
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02237108
_022370F0:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022370F8: .word 0x02243188
_022370FC: .word 0x02243184
_02237100: .word 0x022407D0
_02237104: .word 0x022407F4

	arm_func_start MOD13_02237108
MOD13_02237108: ; 0x02237108
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022379B4
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #0xa
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02237130
MOD13_02237130: ; 0x02237130
	stmdb sp!, {r4, lr}
	ldr r1, _022371CC ; =0x02243188
	ldr r2, _022371D0 ; =0x000013E0
	ldr r3, [r1]
	mov r1, r0
	add r0, r3, r2
	add r2, r3, #0x1c00
	bl WM_StepDataSharing
	mov r4, r0
	cmp r4, #7
	bne _02237180
	ldr r0, _022371D4 ; =0x02243184
	ldr r2, [r0]
	cmp r2, #0
	beq _02237178
	ldr r1, _022371D8 ; =0x02240818
	mov r0, #0x8000000
	blx r2
_02237178:
	mov r0, #0
	ldmia sp!, {r4, pc}
_02237180:
	cmp r4, #5
	bne _022371B4
	ldr r0, _022371D4 ; =0x02243184
	ldr r2, [r0]
	cmp r2, #0
	beq _022371A4
	ldr r1, _022371DC ; =0x02240848
	mov r0, #0x8000000
	blx r2
_022371A4:
	mov r0, r4
	bl MOD13_02238274
	mov r0, #0
	ldmia sp!, {r4, pc}
_022371B4:
	cmp r4, #0
	moveq r0, #1
	ldmeqia sp!, {r4, pc}
	bl MOD13_02238274
	mov r0, #0
	ldmia sp!, {r4, pc}
	.align 2, 0
_022371CC: .word 0x02243188
_022371D0: .word 0x000013E0
_022371D4: .word 0x02243184
_022371D8: .word 0x02240818
_022371DC: .word 0x02240848

	arm_func_start MOD13_022371E0
MOD13_022371E0: ; 0x022371E0
	ldr r2, _02237200 ; =0x02243188
	ldr r1, _02237204 ; =0x000013E0
	ldr r3, [r2]
	ldr ip, _02237208 ; =0x020DA048
	mov r2, r0
	add r0, r3, r1
	add r1, r3, #0x1c00
	bx ip
	.align 2, 0
_02237200: .word 0x02243188
_02237204: .word 0x000013E0
_02237208: .word 0x020DA048

	arm_func_start MOD13_0223720C
MOD13_0223720C: ; 0x0223720C
	ldr r1, _0223721C ; =0x02243188
	ldr r1, [r1]
	str r0, [r1, #0x4c]
	bx lr
	.align 2, 0
_0223721C: .word 0x02243188

	arm_func_start MOD13_02237220
MOD13_02237220: ; 0x02237220
	stmdb sp!, {r4, r5, r6, lr}
	ldr r3, _02237398 ; =0x02243188
	mov r6, r0
	ldr r0, [r3]
	mov r5, r1
	ldr r0, [r0, #0x40]
	mov r4, r2
	cmp r0, #1
	beq _02237248
	bl OS_Terminate
_02237248:
	ldr r2, _02237398 ; =0x02243188
	mov r1, #0x180
	ldr r0, [r2]
	mov r3, #0xe0
	add r0, r0, #0x1000
	str r1, [r0, #0x2a4]
	ldr r0, [r2]
	ldr r1, _0223739C ; =0x02243184
	add r0, r0, #0x1000
	str r3, [r0, #0x2a0]
	ldr r3, [r1]
	cmp r3, #0
	beq _02237294
	ldr r0, [r2]
	ldr r1, _022373A0 ; =0x0224087C
	add r0, r0, #0x1000
	ldr r2, [r0, #0x2a4]
	mov r0, #0x8000000
	blx r3
_02237294:
	ldr r0, _0223739C ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	beq _022372C0
	ldr r0, _02237398 ; =0x02243188
	ldr r1, _022373A4 ; =0x02240894
	ldr r2, [r0]
	mov r0, #0x8000000
	add r2, r2, #0x1000
	ldr r2, [r2, #0x2a0]
	blx r3
_022372C0:
	ldr r1, _02237398 ; =0x02243188
	mov r0, #3
	ldr r1, [r1]
	str r6, [r1, #0x44]
	bl MOD13_02238294
	ldr r0, _02237398 ; =0x02243188
	ldr r1, [r0]
	strh r5, [r1, #0xc]
	ldr r0, [r0]
	strh r4, [r0, #0x32]
	bl WM_GetDispersionBeaconPeriod
	ldr r1, _02237398 ; =0x02243188
	mov r2, #0xd0
	ldr r3, [r1]
	mov r4, #0x44
	strh r0, [r3, #0x18]
	ldr r0, [r1]
	mov r3, #2
	strh r2, [r0, #0x34]
	ldr r0, [r1]
	mov r2, #0
	strh r4, [r0, #0x36]
	ldr r0, [r1]
	mov r4, #1
	strh r3, [r0, #0x10]
	ldr r0, [r1]
	cmp r6, #2
	strh r2, [r0, #0x16]
	ldr r0, [r1]
	strh r2, [r0, #0x12]
	ldr r0, [r1]
	strh r4, [r0, #0xe]
	ldr r0, _02237398 ; =0x02243188
	movne r4, r2
	ldr r0, [r0]
	cmp r6, #0
	strh r4, [r0, #0x14]
	beq _02237368
	cmp r6, #2
	beq _02237368
	cmp r6, #4
	bne _02237370
_02237368:
	bl MOD13_02238224
	ldmia sp!, {r4, r5, r6, pc}
_02237370:
	ldr r0, _0223739C ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	beq _02237390
	ldr r1, _022373A8 ; =0x022408AC
	mov r2, r6
	mov r0, #0x8000000
	blx r3
_02237390:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02237398: .word 0x02243188
_0223739C: .word 0x02243184
_022373A0: .word 0x0224087C
_022373A4: .word 0x02240894
_022373A8: .word 0x022408AC

	arm_func_start MOD13_022373AC
MOD13_022373AC: ; 0x022373AC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _022373D4
	bl MOD13_02238274
	mov r0, #0xa
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_022373D4:
	ldr r0, _02237408 ; =MOD13_02237464
	bl WM_SetIndCallback
	cmp r0, #0
	beq _022373F8
	bl MOD13_02238274
	mov r0, #0xa
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_022373F8:
	mov r0, #1
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237408: .word MOD13_02237464

	arm_func_start MOD13_0223740C
MOD13_0223740C: ; 0x0223740C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _0223745C ; =0x02243188
	ldr r1, _02237460 ; =MOD13_022373AC
	ldr r0, [r0]
	mov r2, #2
	add r0, r0, #0x80
	bl WM_Initialize
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0xa
	bl MOD13_02238294
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223745C: .word 0x02243188
_02237460: .word MOD13_022373AC

	arm_func_start MOD13_02237464
MOD13_02237464: ; 0x02237464
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #8
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_02238294
	bl OS_Terminate
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02237490
MOD13_02237490: ; 0x02237490
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _0223750C ; =0x02243188
	mov r0, #0
	ldr r1, [r2]
	mov r3, #1
	add r1, r1, #0x1000
	str r0, [r1, #0x2a4]
	ldr r1, [r2]
	add r1, r1, #0x1000
	str r0, [r1, #0x2a0]
	ldr r1, [r2]
	str r0, [r1, #0x48]
	ldr r1, [r2]
	strh r0, [r1, #0x50]
	ldr r1, [r2]
	strh r3, [r1, #0x52]
	ldr r1, [r2]
	str r0, [r1, #0x54]
	ldr r1, [r2]
	str r0, [r1]
	ldr r1, [r2]
	strh r0, [r1, #4]
	ldr r1, [r2]
	str r0, [r1, #0x4c]
	bl MOD13_0223740C
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223750C: .word 0x02243188

	arm_func_start MOD13_02237510
MOD13_02237510: ; 0x02237510
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, #0
	mov r2, r4
	mov r5, r4
	mov r3, #1
_02237528:
	mov r1, r3, lsl r5
	ands r1, r0, r1
	beq _0223754C
	add r1, r5, #1
	add r2, r2, #1
	mov r1, r1, lsl #0x10
	mov r2, r2, lsl #0x10
	mov r4, r1, asr #0x10
	mov r2, r2, lsr #0x10
_0223754C:
	add r1, r5, #1
	mov r1, r1, lsl #0x10
	mov r5, r1, asr #0x10
	cmp r5, #0x10
	blt _02237528
	cmp r2, #1
	addls sp, sp, #4
	movls r0, r4
	ldmlsia sp!, {r4, r5, pc}
	ldr lr, _022375FC ; =0x02243188
	ldr r3, _02237600 ; =0x00010DCD
	ldr r5, [lr]
	ldr ip, _02237604 ; =0x00003039
	ldr r4, [r5, #0x58]
	mov r1, #0
	mla r3, r4, r3, ip
	str r3, [r5, #0x58]
	ldr r3, [lr]
	ldr r3, [r3, #0x58]
	and r3, r3, #0xff
	mul r3, r2, r3
	mov r2, r3, lsl #8
	mov r3, r2, lsr #0x10
_022375A8:
	ands r2, r0, #1
	beq _022375D4
	cmp r3, #0
	addeq r0, r1, #1
	moveq r0, r0, lsl #0x10
	addeq sp, sp, #4
	moveq r0, r0, asr #0x10
	ldmeqia sp!, {r4, r5, pc}
	sub r2, r3, #1
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
_022375D4:
	add r1, r1, #1
	mov r1, r1, lsl #0x10
	mov r0, r0, lsl #0xf
	mov r1, r1, asr #0x10
	cmp r1, #0x10
	mov r0, r0, lsr #0x10
	blt _022375A8
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022375FC: .word 0x02243188
_02237600: .word 0x00010DCD
_02237604: .word 0x00003039

	arm_func_start MOD13_02237608
MOD13_02237608: ; 0x02237608
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02237684 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	cmp r0, #7
	beq _02237628
	bl OS_Terminate
_02237628:
	mov r0, #1
	bl MOD13_02238294
	ldr r0, _02237684 ; =0x02243188
	ldr r0, [r0]
	ldrh r0, [r0, #0x60]
	bl MOD13_02237510
	ldr r2, _02237684 ; =0x02243188
	ldr r1, _02237688 ; =0x02243184
	ldr r3, [r2]
	strh r0, [r3, #0x5c]
	ldr r3, [r1]
	cmp r3, #0
	beq _02237670
	ldr r0, [r2]
	ldr r1, _0223768C ; =0x022408C8
	ldrh r2, [r0, #0x5c]
	mov r0, #0x8000000
	blx r3
_02237670:
	ldr r0, _02237684 ; =0x02243188
	ldr r0, [r0]
	ldrh r0, [r0, #0x5c]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237684: .word 0x02243188
_02237688: .word 0x02243184
_0223768C: .word 0x022408C8

	arm_func_start MOD13_02237690
MOD13_02237690: ; 0x02237690
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r3, r1
	mov ip, #0x1e
	mov r1, #3
	mov r2, #0x11
	str ip, [sp]
	bl WM_MeasureChannel
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _022376DC
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	ldmia sp!, {r4, pc}
_022376DC:
	ldr r0, _02237788 ; =0x02243184
	ldr ip, [r0]
	cmp ip, #0
	beq _02237700
	ldrh r2, [r4, #8]
	ldrh r3, [r4, #0xa]
	ldr r1, _0223778C ; =0x022408E0
	mov r0, #0x8000000
	blx ip
_02237700:
	ldr r0, _02237790 ; =0x02243188
	ldrh r2, [r4, #0xa]
	ldr r3, [r0]
	ldrh ip, [r4, #8]
	ldrh r1, [r3, #0x5e]
	cmp r1, r2
	bls _02237738
	strh r2, [r3, #0x5e]
	sub r1, ip, #1
	mov r2, #1
	mov r1, r2, lsl r1
	ldr r0, [r0]
	strh r1, [r0, #0x60]
	b _02237750
_02237738:
	cmp r1, r2
	ldreqh r2, [r3, #0x60]
	subeq r0, ip, #1
	moveq r1, #1
	orreq r0, r2, r1, lsl r0
	streqh r0, [r3, #0x60]
_02237750:
	add r0, ip, #1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl MOD13_02237794
	cmp r0, #0x18
	bne _02237774
	mov r0, #7
	bl MOD13_02238294
	ldmia sp!, {r4, pc}
_02237774:
	cmp r0, #2
	ldmeqia sp!, {r4, pc}
	mov r0, #9
	bl MOD13_02238294
	ldmia sp!, {r4, pc}
	.align 2, 0
_02237788: .word 0x02243184
_0223778C: .word 0x022408E0
_02237790: .word 0x02243188

	arm_func_start MOD13_02237794
MOD13_02237794: ; 0x02237794
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl WM_GetAllowedChannel
	cmp r0, #0x8000
	bne _022377C0
	mov r0, #3
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	mov r0, #3
	ldmia sp!, {r4, pc}
_022377C0:
	cmp r0, #0
	bne _022377E0
	mov r0, #0x16
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	mov r0, #0x18
	ldmia sp!, {r4, pc}
_022377E0:
	sub r1, r4, #1
	mov r2, #1
	mov r1, r2, lsl r1
	ands r1, r1, r0
	bne _0223781C
_022377F4:
	add r1, r4, #1
	mov r1, r1, lsl #0x10
	mov r4, r1, lsr #0x10
	cmp r4, #0x10
	movhi r0, #0x18
	ldmhiia sp!, {r4, pc}
	sub r1, r4, #1
	mov r1, r2, lsl r1
	ands r1, r1, r0
	beq _022377F4
_0223781C:
	ldr r0, _02237834 ; =0x022376B8
	mov r1, r4
	bl MOD13_02237690
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4, pc}
	.align 2, 0
_02237834: .word 0x022376B8

	arm_func_start MOD13_02237838
MOD13_02237838: ; 0x02237838
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	add r0, sp, #0
	bl OS_GetMacAddress
	ldr r1, _02237900 ; =0x027FFC3C
	ldrh r0, [sp]
	ldr r3, [r1]
	ldrh r1, [sp, #2]
	add r0, r0, r3
	ldr r2, _02237904 ; =0x02243188
	add r1, r1, r0
	ldrh r3, [sp, #4]
	ldr r0, [r2]
	mov ip, #0
	add r1, r3, r1
	str r1, [r0, #0x58]
	ldr lr, [r2]
	ldr r0, _02237908 ; =0x00010DCD
	ldr r3, [lr, #0x58]
	ldr r1, _0223790C ; =0x00003039
	mla r0, r3, r0, r1
	str r0, [lr, #0x58]
	ldr r0, [r2]
	mov r3, #0x65
	strh ip, [r0, #0x5c]
	ldr r1, [r2]
	mov r0, #3
	strh r3, [r1, #0x5e]
	bl MOD13_02238294
	mov r0, #1
	bl MOD13_02237794
	cmp r0, #0x18
	bne _022378D8
	mov r0, #0x18
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {pc}
_022378D8:
	cmp r0, #2
	addeq sp, sp, #0xc
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	mov r0, #0
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02237900: .word 0x027FFC3C
_02237904: .word 0x02243188
_02237908: .word 0x00010DCD
_0223790C: .word 0x00003039

	arm_func_start MOD13_02237910
MOD13_02237910: ; 0x02237910
	ldr r0, _02237920 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	bx lr
	.align 2, 0
_02237920: .word 0x02243188

	arm_func_start MOD13_02237924
MOD13_02237924: ; 0x02237924
	ldr r0, _02237934 ; =0x02243188
	ldr r0, [r0]
	ldrh r0, [r0, #0x52]
	bx lr
	.align 2, 0
_02237934: .word 0x02243188

	arm_func_start MOD13_02237938
MOD13_02237938: ; 0x02237938
	ldr r1, _02237948 ; =0x02243188
	ldr r1, [r1]
	str r0, [r1, #8]
	bx lr
	.align 2, 0
_02237948: .word 0x02243188

	arm_func_start MOD13_0223794C
MOD13_0223794C: ; 0x0223794C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02237970
	mov r0, #0xa
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02237970:
	mov r0, #0
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _022379A8
	mov r0, #9
	bl MOD13_02238294
	ldrh r0, [r4, #2]
	bl MOD13_02238274
	ldmia sp!, {r4, pc}
_022379A8:
	mov r0, #1
	bl MOD13_02238294
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_022379B4
MOD13_022379B4: ; 0x022379B4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _022379EC ; =0x02237980
	bl WM_Reset
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022379EC: .word 0x02237980

	arm_func_start MOD13_022379F0
MOD13_022379F0: ; 0x022379F0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02237A10
	bl MOD13_02238274
	add sp, sp, #4
	ldmia sp!, {pc}
_02237A10:
	mov r0, #1
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02237A20
MOD13_02237A20: ; 0x02237A20
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _02237A60 ; =MOD13_022379F0
	mov r1, #0
	bl WM_Disconnect
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	bl MOD13_02237108
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237A60: .word MOD13_022379F0

	arm_func_start MOD13_02237A64
MOD13_02237A64: ; 0x02237A64
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02237A88
	bl MOD13_02238274
	bl MOD13_02236FB8
	add sp, sp, #4
	ldmia sp!, {pc}
_02237A88:
	bl MOD13_02237A20
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02237AA8
MOD13_02237AA8: ; 0x02237AA8
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _02237AE0 ; =MOD13_02237A64
	bl WM_EndMP
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237AE0: .word MOD13_02237A64

	arm_func_start MOD13_02237AE4
MOD13_02237AE4: ; 0x02237AE4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02237B40 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	cmp r0, #6
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _02237B40 ; =0x02243188
	ldr r0, [r0]
	add r0, r0, #0x1e00
	bl WM_EndKeySharing
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237B40: .word 0x02243188

	arm_func_start MOD13_02237B44
MOD13_02237B44: ; 0x02237B44
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02237B64
	bl MOD13_02238274
	add sp, sp, #4
	ldmia sp!, {pc}
_02237B64:
	mov r0, #1
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02237B74
MOD13_02237B74: ; 0x02237B74
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02237BA4 ; =MOD13_02237B44
	bl WM_EndParent
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237BA4: .word MOD13_02237B44

	arm_func_start MOD13_02237BA8
MOD13_02237BA8: ; 0x02237BA8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02237BCC
	bl MOD13_02238274
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
_02237BCC:
	bl MOD13_02237B74
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02237C04 ; =0x02243184
	ldr r2, [r0]
	cmp r2, #0
	beq _02237BF8
	ldr r1, _02237C08 ; =0x02240918
	mov r0, #0x8000000
	blx r2
_02237BF8:
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237C04: .word 0x02243184
_02237C08: .word 0x02240918

	arm_func_start MOD13_02237C0C
MOD13_02237C0C: ; 0x02237C0C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _02237C44 ; =MOD13_02237BA8
	bl WM_EndMP
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237C44: .word MOD13_02237BA8

	arm_func_start MOD13_02237C48
MOD13_02237C48: ; 0x02237C48
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02237C80 ; =0x02243188
	ldr r0, [r0]
	add r0, r0, #0x1e00
	bl WM_EndKeySharing
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237C80: .word 0x02243188

	arm_func_start MOD13_02237C84
MOD13_02237C84: ; 0x02237C84
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #6
	bl MOD13_02238294
	ldr r0, _02237CC8 ; =0x02243188
	mov r1, #0xd
	ldr r0, [r0]
	add r0, r0, #0x1e00
	bl WM_StartKeySharing
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237CC8: .word 0x02243188

	arm_func_start MOD13_02237CCC
MOD13_02237CCC: ; 0x02237CCC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r1, [r0, #2]
	cmp r1, #0
	beq _02237CF8
	mov r0, r1
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02237CF8:
	ldrh r2, [r0, #4]
	sub r0, r2, #0xa
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _02237DEC
_02237D0C: ; jump table
	b _02237D1C ; case 0
	b _02237E0C ; case 1
	b _02237DEC ; case 2
	b _02237DEC ; case 3
_02237D1C:
	ldr r0, _02237E14 ; =0x02243188
	ldr r1, [r0]
	ldr r0, [r1, #0x44]
	cmp r0, #2
	bne _02237D88
	ldr r0, [r1, #0x40]
	cmp r0, #4
	bne _02237D78
	bl MOD13_02237C84
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _02237E18 ; =0x02243184
	ldr r2, [r0]
	cmp r2, #0
	beq _02237D68
	ldr r1, _02237E1C ; =0x02240940
	mov r0, #0x8000000
	blx r2
_02237D68:
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02237D78:
	cmp r0, #6
	bne _02237DDC
	add sp, sp, #4
	ldmia sp!, {pc}
_02237D88:
	cmp r0, #4
	bne _02237DDC
	ldr r0, _02237E20 ; =0x000013E0
	mov ip, #1
	add r0, r1, r0
	mov r1, #0xd
	mov r2, #7
	mov r3, #0x44
	str ip, [sp]
	bl WM_StartDataSharing
	cmp r0, #0
	beq _02237DCC
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02237DCC:
	mov r0, #5
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02237DDC:
	mov r0, #4
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02237DEC:
	ldr r0, _02237E18 ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r1, _02237E24 ; =0x022408F8
	mov r0, #0x8000000
	blx r3
_02237E0C:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02237E14: .word 0x02243188
_02237E18: .word 0x02243184
_02237E1C: .word 0x02240940
_02237E20: .word 0x000013E0
_02237E24: .word 0x022408F8

	arm_func_start MOD13_02237E28
MOD13_02237E28: ; 0x02237E28
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _02237EBC ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	sub r0, r0, #4
	cmp r0, #2
	addls sp, sp, #0xc
	movls r0, #1
	ldmlsia sp!, {pc}
	mov r0, #4
	bl MOD13_02238294
	ldr r0, _02237EBC ; =0x02243188
	mov ip, #1
	ldr lr, [r0]
	ldr r2, _02237EC0 ; =0x00001060
	add r3, lr, #0x1000
	ldr r1, [r3, #0x2a0]
	ldr r0, _02237EC4 ; =MOD13_02237CCC
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [sp]
	str ip, [sp, #4]
	ldr r3, [r3, #0x2a4]
	add r1, lr, r2
	mov r2, r3, lsl #0x10
	mov r2, r2, lsr #0x10
	add r3, lr, #0xf80
	bl WM_StartMP
	cmp r0, #2
	addeq sp, sp, #0xc
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #0
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02237EBC: .word 0x02243188
_02237EC0: .word 0x00001060
_02237EC4: .word MOD13_02237CCC

	arm_func_start MOD13_02237EC8
MOD13_02237EC8: ; 0x02237EC8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	ldrh r2, [r5, #0x10]
	mov r1, #1
	ldrh r0, [r5, #2]
	mov r1, r1, lsl r2
	mov r1, r1, lsl #0x10
	cmp r0, #0
	mov r4, r1, lsr #0x10
	beq _02237F08
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02237F08:
	ldrh ip, [r5, #8]
	cmp ip, #7
	bgt _02237F44
	cmp ip, #7
	bge _02237F50
	cmp ip, #2
	bgt _02238034
	cmp ip, #0
	blt _02238034
	cmp ip, #0
	beq _02238014
	cmp ip, #2
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	b _02238034
_02237F44:
	cmp ip, #9
	beq _02237FD8
	b _02238034
_02237F50:
	ldr r0, _02238060 ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	beq _02237F6C
	ldr r1, _02238064 ; =0x02240970
	mov r0, #0x8000000
	blx r3
_02237F6C:
	ldr r0, _02238068 ; =0x02243188
	ldr r0, [r0]
	ldr r1, [r0, #0x4c]
	cmp r1, #0
	beq _02237FBC
	mov r0, r5
	blx r1
	cmp r0, #0
	bne _02237FBC
	ldrh r1, [r5, #0x10]
	mov r0, #0
	bl WM_Disconnect
	cmp r0, #2
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02237FBC:
	ldr r0, _02238068 ; =0x02243188
	add sp, sp, #4
	ldr r1, [r0]
	ldrh r0, [r1, #0x52]
	orr r0, r0, r4
	strh r0, [r1, #0x52]
	ldmia sp!, {r4, r5, pc}
_02237FD8:
	ldr r0, _02238060 ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	beq _02237FF4
	ldr r1, _0223806C ; =0x0224099C
	mov r0, #0x8000000
	blx r3
_02237FF4:
	ldr r0, _02238068 ; =0x02243188
	mvn r1, r4
	ldr r2, [r0]
	add sp, sp, #4
	ldrh r0, [r2, #0x52]
	and r0, r0, r1
	strh r0, [r2, #0x52]
	ldmia sp!, {r4, r5, pc}
_02238014:
	bl MOD13_02237E28
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02238034:
	ldr r0, _02238060 ; =0x02243184
	ldr r3, [r0]
	cmp r3, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _02238070 ; =0x022408F8
	mov r2, ip
	mov r0, #0x8000000
	blx r3
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02238060: .word 0x02243184
_02238064: .word 0x02240970
_02238068: .word 0x02243188
_0223806C: .word 0x0224099C
_02238070: .word 0x022408F8

	arm_func_start MOD13_02238074
MOD13_02238074: ; 0x02238074
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _022380E0 ; =0x02243188
	ldr r0, [r0]
	ldr r0, [r0, #0x40]
	sub r0, r0, #4
	cmp r0, #2
	addls sp, sp, #4
	movls r0, #1
	ldmlsia sp!, {pc}
	ldr r0, _022380E4 ; =MOD13_02237EC8
	bl WM_StartParent
	cmp r0, #2
	beq _022380BC
	bl MOD13_02238274
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {pc}
_022380BC:
	ldr r1, _022380E0 ; =0x02243188
	mov r3, #0
	ldr r2, [r1]
	mov r0, #1
	strh r3, [r2, #0x50]
	ldr r1, [r1]
	strh r0, [r1, #0x52]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022380E0: .word 0x02243188
_022380E4: .word MOD13_02237EC8

	arm_func_start MOD13_022380E8
MOD13_022380E8: ; 0x022380E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _02238110
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02238110:
	bl MOD13_02238074
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02238130
MOD13_02238130: ; 0x02238130
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r0, _02238198 ; =0x02243188
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r2, [r0, #0x3ac]
	add r0, r1, #0x13c0
	blx r2
	ldr r2, _02238198 ; =0x02243188
	mov r1, r0
	ldr r2, [r2]
	ldr r0, _0223819C ; =MOD13_022380E8
	add r2, r2, #0x13c0
	bl WM_SetWEPKeyEx2
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238198: .word 0x02243188
_0223819C: .word MOD13_022380E8

	arm_func_start MOD13_022381A0
MOD13_022381A0: ; 0x022381A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _022381C8
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_022381C8:
	ldr r0, _02238220 ; =0x02243188
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x3ac]
	cmp r0, #0
	beq _02238200
	bl MOD13_02238130
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
_02238200:
	bl MOD13_02238074
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #9
	bl MOD13_02238294
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238220: .word 0x02243188

	arm_func_start MOD13_02238224
MOD13_02238224: ; 0x02238224
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #3
	bl MOD13_02238294
	ldr r1, _0223826C ; =0x02243188
	ldr r0, _02238270 ; =MOD13_022381A0
	ldr r1, [r1]
	bl WM_SetParentParameter
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	bl MOD13_02238274
	mov r0, #9
	bl MOD13_02238294
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223826C: .word 0x02243188
_02238270: .word MOD13_022381A0

	arm_func_start MOD13_02238274
MOD13_02238274: ; 0x02238274
	ldr r1, _02238290 ; =0x02243188
	ldr r2, [r1]
	ldr r1, [r2, #0x40]
	sub r1, r1, #9
	cmp r1, #1
	strhi r0, [r2, #0x54]
	bx lr
	.align 2, 0
_02238290: .word 0x02243188

	arm_func_start MOD13_02238294
MOD13_02238294: ; 0x02238294
	stmdb sp!, {r4, lr}
	ldr r1, _02238308 ; =0x02243184
	mov r4, r0
	ldr ip, [r1]
	cmp ip, #0
	beq _022382CC
	ldr r0, _0223830C ; =0x02243188
	ldr r2, _02238310 ; =0x022407A8
	ldr r0, [r0]
	ldr r1, _02238314 ; =0x022409C8
	ldr r3, [r0, #0x40]
	mov r0, #0x8000000
	ldr r2, [r2, r3, lsl #2]
	blx ip
_022382CC:
	ldr r1, _0223830C ; =0x02243188
	ldr r0, _02238308 ; =0x02243184
	ldr r2, [r1]
	str r4, [r2, #0x40]
	ldr r3, [r0]
	cmp r3, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, [r1]
	ldr r0, _02238310 ; =0x022407A8
	ldr r2, [r1, #0x40]
	ldr r1, _02238318 ; =0x022409D0
	ldr r2, [r0, r2, lsl #2]
	mov r0, #0x8000000
	blx r3
	ldmia sp!, {r4, pc}
	.align 2, 0
_02238308: .word 0x02243184
_0223830C: .word 0x02243188
_02238310: .word 0x022407A8
_02238314: .word 0x022409C8
_02238318: .word 0x022409D0

	arm_func_start MOD13_0223831C
MOD13_0223831C: ; 0x0223831C
	ldr r1, _02238354 ; =0x02243188
	mov r2, #0
	str r0, [r1]
	str r2, [r0, #0x40]
	ldr r0, [r1]
	add r0, r0, #0x1000
	str r2, [r0, #0x3a8]
	ldr r0, [r1]
	add r0, r0, #0x1000
	str r2, [r0, #0x3ac]
	ldr r0, [r1]
	add r0, r0, #0x1000
	str r2, [r0, #0x3b0]
	bx lr
	.align 2, 0
_02238354: .word 0x02243188

	arm_func_start MOD13_02238358
MOD13_02238358: ; 0x02238358
	ldr r0, _0223836C ; =0x0224318C
	ldr r0, [r0]
	add r0, r0, #0x100
	ldrh r0, [r0, #0x44]
	bx lr
	.align 2, 0
_0223836C: .word 0x0224318C

	arm_func_start MOD13_02238370
MOD13_02238370: ; 0x02238370
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov ip, #0
	ldr r4, _0223845C ; =0x0224318C
	mov r5, ip
	mov r2, ip
	mov r0, #1
	mov r1, #0xbc
	mov lr, #0x44
_02238394:
	ldr r3, [r4]
	add r6, r3, ip, lsl #2
	ldr r6, [r6, #0x208]
	cmp r6, #0
	beq _02238448
	add r6, r3, #0x100
	mla r7, ip, lr, r6
	cmp ip, #1
	bne _02238448
	ldrb r6, [r3, #0xa93]
	cmp r6, #1
	bne _02238418
	ldrh r6, [r7]
	cmp r6, #0x10
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r6, [r3, #0xa94]
	add r6, r6, #1
	str r6, [r3, #0xa94]
	ldr r6, [r4]
	ldr r3, [r6, #0xa94]
	ands r3, r3, #1
	bne _02238448
	add r3, r6, #0x200
	ldrh r6, [r3]
	add r6, r6, #1
	strh r6, [r3]
	ldr r3, [r4]
	add r3, r3, #0x200
	ldrh r6, [r3]
	cmp r6, #0x24
	strhsh r2, [r3]
	b _02238448
_02238418:
	add r3, r3, #0x200
	strh r1, [r3, #2]
	ldrh r3, [r7]
	cmp r3, #0xbd
	bne _02238448
	ldr r3, [r4]
	strb r0, [r3, #0xa93]
	ldr r3, [r4]
	add r3, r3, #0x200
	strh r5, [r3]
	ldr r3, [r4]
	str r5, [r3, #0xa94]
_02238448:
	add ip, ip, #1
	cmp ip, #0x10
	blt _02238394
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0223845C: .word 0x0224318C

	arm_func_start MOD13_02238460
MOD13_02238460: ; 0x02238460
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r3, _022385B8 ; =0x0224318C
	ldr r5, [r3]
	ldrb r4, [r5, #0xa93]
	cmp r4, #1
	bne _022384A8
	ldr r4, [r5, #0xab0]
	strh r0, [r4]
	ldr r4, [r3]
	mov r0, r2
	ldr r4, [r4, #0xab0]
	mov r2, #0x40
	strh r1, [r4, #2]
	ldr r1, [r3]
	ldr r1, [r1, #0xab0]
	add r1, r1, #4
	bl MI_CpuCopy8
	b _022384D4
_022384A8:
	ldr r0, [r5, #0x204]
	mov r1, #0xbc
	add r0, r0, #1
	str r0, [r5, #0x204]
	ldr r0, [r3]
	ldr r0, [r0, #0xab0]
	strh r1, [r0]
	ldr r0, [r3]
	ldrb r1, [r0, #0xa92]
	ldr r0, [r0, #0xab0]
	strb r1, [r0, #4]
_022384D4:
	bl MOD13_02237910
	cmp r0, #5
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r0, _022385B8 ; =0x0224318C
	ldr r0, [r0]
	bl MOD13_02237130
	cmp r0, #0
	bne _0223850C
	ldr r0, _022385B8 ; =0x0224318C
	ldr r1, [r0]
	ldr r0, [r1, #0x204]
	add r0, r0, #4
	str r0, [r1, #0x204]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_0223850C:
	ldr r0, _022385B8 ; =0x0224318C
	ldr r1, [r0]
	ldrb r0, [r1, #0xa93]
	cmp r0, #0
	ldreq r0, [r1, #0x204]
	addeq r0, r0, #1
	streq r0, [r1, #0x204]
	beq _02238550
	mov r0, #0
	str r0, [r1, #0x204]
	bl MOD13_02237924
	cmp r0, #3
	ldrne r0, _022385B8 ; =0x0224318C
	movne r1, #0x1b
	ldrne r0, [r0]
	strneb r1, [r0, #0xa90]
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
_02238550:
	mov r7, #0
	ldr r8, _022385B8 ; =0x0224318C
	mov r4, r7
	mov r6, #0x44
	mov r5, #1
_02238564:
	mov r0, r7
	bl MOD13_022371E0
	cmp r0, #0
	ldreq r0, [r8]
	addeq r0, r0, r7, lsl #2
	streq r4, [r0, #0x208]
	beq _022385A0
	ldr r1, [r8]
	mov r2, r6
	add r1, r1, #0x100
	mla r1, r7, r6, r1
	bl MI_CpuCopy8
	ldr r0, [r8]
	add r0, r0, r7, lsl #2
	str r5, [r0, #0x208]
_022385A0:
	add r0, r7, #1
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	cmp r7, #2
	blo _02238564
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_022385B8: .word 0x0224318C

	arm_func_start MOD13_022385BC
MOD13_022385BC: ; 0x022385BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02238604 ; =0x0224318C
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x100
	add r0, r0, #0x100
	bl MI_CpuFill8
	ldr r0, _02238604 ; =0x0224318C
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x100
	bl MI_CpuFill8
	ldr r0, _02238604 ; =0x0224318C
	ldr r0, [r0]
	str r0, [r0, #0xab0]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238604: .word 0x0224318C

	arm_func_start MOD13_02238608
MOD13_02238608: ; 0x02238608
	stmdb sp!, {r4, lr}
	add r0, r0, #0xa
	bl MOD13_02236254
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	bl MOD13_02236314
	ldr r1, _02238640 ; =0x0224318C
	sub r2, r4, #1
	ldr r1, [r1]
	add r1, r1, r2, lsl #2
	str r0, [r1, #0xaa0]
	mov r0, #1
	ldmia sp!, {r4, pc}
	.align 2, 0
_02238640: .word 0x0224318C

	arm_func_start MOD13_02238644
MOD13_02238644: ; 0x02238644
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02237910
	cmp r0, #1
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
	bl MOD13_02236F5C
	ldr r1, _0223867C ; =0x0224318C
	mov r0, #1
	ldr r1, [r1]
	strb r0, [r1, #0xa90]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223867C: .word 0x0224318C

	arm_func_start MOD13_02238680
MOD13_02238680: ; 0x02238680
	ldr r0, _02238694 ; =0x0224318C
	mov r1, #0xc
	ldr r0, [r0]
	strb r1, [r0, #0xa90]
	bx lr
	.align 2, 0
_02238694: .word 0x0224318C

	arm_func_start MOD13_02238698
MOD13_02238698: ; 0x02238698
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02237910
	cmp r0, #6
	addls pc, pc, r0, lsl #2
	b _02238878
_022386B0: ; jump table
	b _02238878 ; case 0
	b _022386CC ; case 1
	b _02238878 ; case 2
	b _02238878 ; case 3
	b _022386FC ; case 4
	b _022386FC ; case 5
	b _022386FC ; case 6
_022386CC:
	ldr r1, _02238880 ; =0x0224318C
	mov r0, #4
	ldr r1, [r1]
	add r1, r1, #0x600
	ldrh r3, [r1, #0x48]
	ldrh r2, [r1, #0x4a]
	add r1, r3, #1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl MOD13_02237220
	add sp, sp, #4
	ldmia sp!, {pc}
_022386FC:
	ldr r1, _02238880 ; =0x0224318C
	mov r0, #0
	ldr r2, [r1]
	add r1, r2, #0x200
	ldrh r1, [r1]
	ldr ip, [r2, #0xaa4]
	mov r3, r1, lsr #0x1f
	rsb r2, r3, r1, lsl #28
	add r2, r3, r2, ror #28
	add r2, ip, r2, lsl #6
	bl MOD13_02238460
	bl MOD13_02238370
	ldr r0, _02238880 ; =0x0224318C
	ldr r1, [r0]
	ldrb r0, [r1, #0xa90]
	cmp r0, #0x1b
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, [r1, #0x204]
	cmp r0, #0x1e0
	movhi r0, #0x1b
	strhib r0, [r1, #0xa90]
	addhi sp, sp, #4
	ldmhiia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0x10
	beq _02238774
	bl MOD13_02238358
	cmp r0, #0x20
	bne _02238790
_02238774:
	bl MOD13_02238358
	ldr r0, _02238880 ; =0x0224318C
	mov r1, #0xa
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238790:
	bl MOD13_02238358
	cmp r0, #0x40
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #0xb
	ldreq r0, [r0]
	addeq sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmeqia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0xff
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #0x1b
	ldreq r0, [r0]
	addeq sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmeqia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0x50
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #0x15
	ldreq r0, [r0]
	addeq sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmeqia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0x60
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #0x18
	ldreq r0, [r0]
	addeq sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmeqia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0x70
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #0x1b
	ldreq r0, [r0]
	addeq sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmeqia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #8
	ldreq r0, [r0]
	addeq sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmeqia sp!, {pc}
	bl MOD13_02238358
	cmp r0, #0xbd
	ldreq r0, _02238880 ; =0x0224318C
	moveq r1, #9
	ldreq r0, [r0]
	streqb r1, [r0, #0xa90]
	ldrne r0, _02238880 ; =0x0224318C
	movne r1, #0x1f
	ldrne r0, [r0]
	strneb r1, [r0, #0xa90]
_02238878:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238880: .word 0x0224318C

	arm_func_start MOD13_02238884
MOD13_02238884: ; 0x02238884
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_022385BC
	ldr r0, _022388B0 ; =MOD13_02238608
	bl MOD13_0223720C
	ldr r0, _022388B4 ; =0x0224318C
	mov r1, #8
	ldr r0, [r0]
	strb r1, [r0, #0xa90]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022388B0: .word MOD13_02238608
_022388B4: .word 0x0224318C

	arm_func_start MOD13_022388B8
MOD13_022388B8: ; 0x022388B8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02236470
	cmp r0, #7
	addls pc, pc, r0, lsl #2
	b _02238A94
_022388D0: ; jump table
	b _02238A3C ; case 0
	b _022388F0 ; case 1
	b _02238914 ; case 2
	b _022389AC ; case 3
	b _02238A94 ; case 4
	b _02238A08 ; case 5
	b _02238A94 ; case 6
	b _02238A20 ; case 7
_022388F0:
	ldr r1, _02238A9C ; =0x0224318C
	ldr r0, _02238AA0 ; =0x00000AB4
	ldr r2, [r1]
	add r1, r2, #0x600
	ldrh r1, [r1, #0x4a]
	add r0, r2, r0
	bl MOD13_02236D9C
	add sp, sp, #4
	ldmia sp!, {pc}
_02238914:
	mov r0, #2
	bl MOD13_02236414
	cmp r0, #0
	ldrne r0, _02238A9C ; =0x0224318C
	movne r1, #5
	ldrne r0, [r0]
	addne sp, sp, #4
	strneb r1, [r0, #0xa90]
	ldmneia sp!, {pc}
	mov r0, #3
	bl MOD13_02236414
	cmp r0, #0
	bne _02238958
	mov r0, #4
	bl MOD13_02236414
	cmp r0, #0
	beq _02238970
_02238958:
	ldr r0, _02238A9C ; =0x0224318C
	mov r1, #6
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238970:
	ldr r0, _02238A9C ; =0x0224318C
	ldr r0, [r0]
	ldrb r0, [r0, #0xa90]
	cmp r0, #5
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #2
	bl MOD13_02236414
	cmp r0, #0
	ldreq r0, _02238A9C ; =0x0224318C
	moveq r1, #0xd
	ldreq r0, [r0]
	add sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_022389AC:
	bl MOD13_022368FC
	cmp r0, #0
	beq _022389C4
	bl MOD13_022367F4
	add sp, sp, #4
	ldmia sp!, {pc}
_022389C4:
	ldr r0, _02238A9C ; =0x0224318C
	ldr r0, [r0]
	ldrb r0, [r0, #0xa90]
	add r0, r0, #0xfa
	and r0, r0, #0xff
	cmp r0, #1
	addhi sp, sp, #4
	ldmhiia sp!, {pc}
	mov r0, #3
	bl MOD13_02236414
	cmp r0, #0
	ldreq r0, _02238A9C ; =0x0224318C
	moveq r1, #0x12
	ldreq r0, [r0]
	add sp, sp, #4
	streqb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238A08:
	ldr r0, _02238A9C ; =0x0224318C
	mov r1, #7
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238A20:
	bl MOD13_022367D8
	ldr r0, _02238A9C ; =0x0224318C
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238A3C:
	bl MOD13_02237910
	cmp r0, #0
	beq _02238A6C
	cmp r0, #1
	beq _02238A60
	cmp r0, #3
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	b _02238A84
_02238A60:
	bl MOD13_02236F5C
	add sp, sp, #4
	ldmia sp!, {pc}
_02238A6C:
	ldr r0, _02238A9C ; =0x0224318C
	mov r1, #0x1f
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238A84:
	ldr r0, _02238A9C ; =0x0224318C
	mov r1, #0x1f
	ldr r0, [r0]
	strb r1, [r0, #0xa90]
_02238A94:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238A9C: .word 0x0224318C
_02238AA0: .word 0x00000AB4

	arm_func_start MOD13_02238AA4
MOD13_02238AA4: ; 0x02238AA4
	ldr r0, _02238AC0 ; =0x0224318C
	ldr ip, _02238AC4 ; =MOD13_02236DF4
	ldr r2, [r0]
	add r0, r2, #0x600
	ldrh r1, [r0, #0x48]
	ldr r0, [r2, #0xac8]
	bx ip
	.align 2, 0
_02238AC0: .word 0x0224318C
_02238AC4: .word MOD13_02236DF4

	arm_func_start MOD13_02238AC8
MOD13_02238AC8: ; 0x02238AC8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_02237910
	cmp r0, #9
	addls pc, pc, r0, lsl #2
	b _02238B78
_02238AE0: ; jump table
	b _02238B48 ; case 0
	b _02238B08 ; case 1
	b _02238B78 ; case 2
	b _02238B7C ; case 3
	b _02238B78 ; case 4
	b _02238B78 ; case 5
	b _02238B78 ; case 6
	b _02238B14 ; case 7
	b _02238B78 ; case 8
	b _02238B6C ; case 9
_02238B08:
	bl MOD13_02237838
	add sp, sp, #4
	ldmia sp!, {pc}
_02238B14:
	bl MOD13_02237608
	ldr r2, _02238B84 ; =0x0224318C
	mov ip, #0
	ldr r1, [r2]
	mov r3, #3
	add r1, r1, #0x600
	strh r0, [r1, #0x4a]
	ldr r0, [r2]
	add sp, sp, #4
	str ip, [r0, #0xa98]
	ldr r0, [r2]
	strb r3, [r0, #0xa90]
	ldmia sp!, {pc}
_02238B48:
	ldr r0, _02238B84 ; =0x0224318C
	mov r3, #0
	ldr r2, [r0]
	mov r1, #3
	str r3, [r2, #0xa98]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238B6C:
	bl MOD13_02237108
	add sp, sp, #4
	ldmia sp!, {pc}
_02238B78:
	bl OS_Terminate
_02238B7C:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238B84: .word 0x0224318C

	arm_func_start MOD13_02238B88
MOD13_02238B88: ; 0x02238B88
	ldr ip, _02238B94 ; =MOD13_022132CC
	mov r0, #1
	bx ip
	.align 2, 0
_02238B94: .word MOD13_022132CC

	arm_func_start MOD13_02238B98
MOD13_02238B98: ; 0x02238B98
	ldr r2, _02238BDC ; =0x0224318C
	ldr r3, [r2]
	ldrb r3, [r3, #0xa90]
	strb r3, [r0]
	ldr r0, [r2]
	ldrb r2, [r0, #0xa90]
	ldrb r0, [r0, #0xa91]
	cmp r2, r0
	movne r0, #1
	strneb r0, [r1]
	moveq r0, #0
	streqb r0, [r1]
	ldr r0, _02238BDC ; =0x0224318C
	ldr r1, [r0]
	ldrb r0, [r1, #0xa90]
	strb r0, [r1, #0xa91]
	bx lr
	.align 2, 0
_02238BDC: .word 0x0224318C

	arm_func_start MOD13_02238BE0
MOD13_02238BE0: ; 0x02238BE0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _02238FF0 ; =0x0224318C
	ldr r0, [r1]
	ldrb r2, [r0, #0xa90]
	cmp r2, #0x22
	addls pc, pc, r2, lsl #2
	b _02238FE8
_02238C00: ; jump table
	b _02238FE8 ; case 0
	b _02238C8C ; case 1
	b _02238CD4 ; case 2
	b _02238CE0 ; case 3
	b _02238CFC ; case 4
	b _02238D14 ; case 5
	b _02238D14 ; case 6
	b _02238D20 ; case 7
	b _02238D2C ; case 8
	b _02238D2C ; case 9
	b _02238D2C ; case 10
	b _02238D38 ; case 11
	b _02238FE8 ; case 12
	b _02238FE8 ; case 13
	b _02238FE8 ; case 14
	b _02238FE8 ; case 15
	b _02238D44 ; case 16
	b _02238D60 ; case 17
	b _02238D84 ; case 18
	b _02238DAC ; case 19
	b _02238FE8 ; case 20
	b _02238DF0 ; case 21
	b _02238E18 ; case 22
	b _02238FE8 ; case 23
	b _02238E5C ; case 24
	b _02238E84 ; case 25
	b _02238FE8 ; case 26
	b _02238EC8 ; case 27
	b _02238EF0 ; case 28
	b _02238FE8 ; case 29
	b _02238FE4 ; case 30
	b _02238FE8 ; case 31
	b _02238F78 ; case 32
	b _02238FA0 ; case 33
	b _02238FE8 ; case 34
_02238C8C:
	ldrb r2, [r0, #0xaac]
	cmp r2, #1
	bne _02238CAC
	mov r1, #0
	strb r1, [r0, #0xaac]
	bl MOD13_0223903C
	add sp, sp, #4
	ldmia sp!, {pc}
_02238CAC:
	cmp r2, #2
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r2, #0
	strb r2, [r0, #0xaac]
	ldr r0, [r1]
	mov r1, #0x22
	strb r1, [r0, #0xa90]
	add sp, sp, #4
	ldmia sp!, {pc}
_02238CD4:
	bl MOD13_02238AC8
	add sp, sp, #4
	ldmia sp!, {pc}
_02238CE0:
	bl MOD13_02238AA4
	ldr r0, _02238FF0 ; =0x0224318C
	mov r1, #4
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238CFC:
	ldr r1, [r0, #0xa98]
	add r1, r1, #1
	str r1, [r0, #0xa98]
	bl MOD13_022388B8
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D14:
	bl MOD13_022388B8
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D20:
	bl MOD13_02238884
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D2C:
	bl MOD13_02238698
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D38:
	bl MOD13_02238680
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D44:
	mov r2, #0
	str r2, [r0, #0xa9c]
	ldr r0, [r1]
	mov r1, #0x11
	strb r1, [r0, #0xa90]
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D60:
	ldr r2, [r0, #0xa9c]
	add r1, r2, #1
	cmp r2, #0x1e
	str r1, [r0, #0xa9c]
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02238644
	add sp, sp, #4
	ldmia sp!, {pc}
_02238D84:
	bl MOD13_02214F18
	ldr r0, _02238FF0 ; =0x0224318C
	mov r3, #0
	ldr r2, [r0]
	mov r1, #0x16
	str r3, [r2, #0xa9c]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238DAC:
	ldr r2, [r0, #0xa9c]
	add r1, r2, #1
	cmp r2, #0x1e
	str r1, [r0, #0xa9c]
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02237910
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02236F5C
	ldr r0, _02238FF0 ; =0x0224318C
	mov r1, #0x14
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238DF0:
	bl MOD13_02236FB8
	ldr r0, _02238FF0 ; =0x0224318C
	mov r3, #0
	ldr r2, [r0]
	mov r1, #0x16
	str r3, [r2, #0xa9c]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238E18:
	ldr r2, [r0, #0xa9c]
	add r1, r2, #1
	cmp r2, #0x1e
	str r1, [r0, #0xa9c]
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02237910
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02236F5C
	ldr r0, _02238FF0 ; =0x0224318C
	mov r1, #0x17
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238E5C:
	bl MOD13_02236FB8
	ldr r0, _02238FF0 ; =0x0224318C
	mov r3, #0
	ldr r2, [r0]
	mov r1, #0x19
	str r3, [r2, #0xa9c]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238E84:
	ldr r2, [r0, #0xa9c]
	add r1, r2, #1
	cmp r2, #0x1e
	str r1, [r0, #0xa9c]
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02237910
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02236F5C
	ldr r0, _02238FF0 ; =0x0224318C
	mov r1, #0x1a
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238EC8:
	bl MOD13_02236FB8
	ldr r0, _02238FF0 ; =0x0224318C
	mov r3, #0
	ldr r2, [r0]
	mov r1, #0x1c
	str r3, [r2, #0xa9c]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238EF0:
	ldr r2, [r0, #0xa9c]
	add r1, r2, #1
	cmp r2, #0x1e
	str r1, [r0, #0xa9c]
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02237910
	cmp r0, #1
	bne _02238F30
	bl MOD13_02236F5C
	ldr r0, _02238FF0 ; =0x0224318C
	mov r1, #0x1d
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238F30:
	ldr r1, _02238FF0 ; =0x0224318C
	ldr r0, _02238FF4 ; =0x88888889
	ldr r1, [r1]
	ldr r2, _02238FF8 ; =0x0000001E
	ldr r3, [r1, #0xa9c]
	umull r0, r1, r3, r0
	mov r1, r1, lsr #4
	umull r0, r1, r2, r1
	sub r1, r3, r0
	cmp r1, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	cmp r3, #0x37
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02236FB8
	add sp, sp, #4
	ldmia sp!, {pc}
_02238F78:
	bl MOD13_02236FB8
	ldr r0, _02238FF0 ; =0x0224318C
	mov r3, #0
	ldr r2, [r0]
	mov r1, #0x21
	str r3, [r2, #0xa9c]
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238FA0:
	ldr r2, [r0, #0xa9c]
	add r1, r2, #1
	cmp r2, #0x1e
	str r1, [r0, #0xa9c]
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	bl MOD13_02237910
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl MOD13_02236F5C
	ldr r0, _02238FF0 ; =0x0224318C
	mov r1, #0x22
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xa90]
	ldmia sp!, {pc}
_02238FE4:
	bl MOD13_02236FB8
_02238FE8:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02238FF0: .word 0x0224318C
_02238FF4: .word 0x88888889
_02238FF8: .word 0x0000001E

	arm_func_start MOD13_02238FFC
MOD13_02238FFC: ; 0x02238FFC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02239038 ; =0x0224318C
	ldr r1, [r0]
	ldrb r0, [r1, #0xa90]
	cmp r0, #5
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
	mov r0, #6
	strb r0, [r1, #0xa90]
	bl MOD13_02236968
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02239038: .word 0x0224318C

	arm_func_start MOD13_0223903C
MOD13_0223903C: ; 0x0223903C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02239098 ; =0x0224318C
	ldr r0, [r0]
	ldrb r0, [r0, #0xa90]
	cmp r0, #1
	beq _02239068
	cmp r0, #0x1a
	beq _02239068
	cmp r0, #0x1d
	bne _0223908C
_02239068:
	bl MOD13_0223909C
	bl MOD13_02237490
	ldr r0, _02239098 ; =0x0224318C
	mov r2, #2
	ldr r1, [r0]
	add sp, sp, #4
	strb r2, [r1, #0xa90]
	mov r0, #1
	ldmia sp!, {pc}
_0223908C:
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02239098: .word 0x0224318C

	arm_func_start MOD13_0223909C
MOD13_0223909C: ; 0x0223909C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02239120 ; =0x0224318C
	ldr r0, [r0]
	ldr r0, [r0, #0xac8]
	bl MOD13_02237938
	ldr r0, _02239120 ; =0x0224318C
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0xa90]
	bl WM_GetNextTgid
	ldr r3, _02239120 ; =0x0224318C
	mov r2, #0x40
	ldr r1, [r3]
	add r1, r1, #0x600
	strh r0, [r1, #0x48]
	ldr r1, [r3]
	ldr r0, [r1, #0xaa4]
	add r1, r1, #0xa50
	bl MI_CpuCopy8
	ldr r0, _02239120 ; =0x0224318C
	mov r2, #0
	ldr r1, [r0]
	strb r2, [r1, #0xa93]
	ldr r1, [r0]
	str r2, [r1, #0x204]
	ldr r0, [r0]
	add r0, r0, #0x600
	ldrh r1, [r0, #0x48]
	add r1, r1, #1
	strh r1, [r0, #0x48]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02239120: .word 0x0224318C

	arm_func_start MOD13_02239124
MOD13_02239124: ; 0x02239124
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02239238 ; =0x0224318C
	ldr r2, [r0]
	ldrb r1, [r2, #0xa90]
	cmp r1, #1
	beq _02239160
	cmp r1, #0x14
	beq _02239160
	cmp r1, #0x17
	beq _02239160
	cmp r1, #0x1a
	beq _02239160
	cmp r1, #0x1d
	bne _02239184
_02239160:
	mov r1, #0x22
	strb r1, [r2, #0xa90]
	ldr r0, _02239238 ; =0x0224318C
	mov r1, #0
	ldr r0, [r0]
	add sp, sp, #4
	strb r1, [r0, #0xaac]
	mov r0, #1
	ldmia sp!, {pc}
_02239184:
	cmp r1, #4
	beq _022391A4
	cmp r1, #5
	beq _022391A4
	cmp r1, #6
	beq _022391A4
	cmp r1, #0xd
	bne _022391EC
_022391A4:
	cmp r1, #4
	bne _022391C0
	ldr r0, [r2, #0xa98]
	cmp r0, #6
	addlo sp, sp, #4
	movlo r0, #0
	ldmloia sp!, {pc}
_022391C0:
	bl MOD13_02214F18
	ldr r0, _02239238 ; =0x0224318C
	mov r3, #0x10
	ldr r1, [r0]
	mov r2, #2
	strb r3, [r1, #0xa90]
	ldr r1, [r0]
	add sp, sp, #4
	strb r2, [r1, #0xaac]
	mov r0, #1
	ldmia sp!, {pc}
_022391EC:
	add r0, r1, #0xf7
	and r0, r0, #0xff
	cmp r0, #1
	movls r0, #0x20
	strlsb r0, [r2, #0xa90]
	addls sp, sp, #4
	movls r0, #1
	ldmlsia sp!, {pc}
	cmp r1, #0xc
	moveq r0, #0x22
	streqb r0, [r2, #0xa90]
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {pc}
	cmp r1, #2
	moveq r0, #0
	movne r0, #0
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02239238: .word 0x0224318C

	arm_func_start MOD13_0223923C
MOD13_0223923C: ; 0x0223923C
	stmdb sp!, {r4, lr}
	ldr r2, _02239328 ; =0x0224318C
	mov r4, r1
	str r0, [r2]
	add r0, r0, #0xb00
	bl MOD13_02236F10
	ldr r1, _02239328 ; =0x0224318C
	mov r3, #0
	ldr r0, [r1]
	mov r2, #1
	add r0, r0, #0x600
	strh r3, [r0, #0x48]
	ldr r0, [r1]
	add r0, r0, #0x600
	strh r3, [r0, #0x4a]
	ldr r0, [r1]
	strb r2, [r0, #0xa90]
	ldr r0, [r1]
	strb r2, [r0, #0xa91]
	ldr r0, [r1]
	str r3, [r0, #0xa9c]
	bl MOD13_022385BC
	ldr r0, _02239328 ; =0x0224318C
	ldr r3, [r4]
	ldr r2, [r0]
	mov r1, #2
	str r3, [r2, #0xab4]
	ldr r3, [r4, #4]
	ldr r2, [r0]
	str r3, [r2, #0xab8]
	ldr r3, [r4, #8]
	ldr r2, [r0]
	str r3, [r2, #0xabc]
	ldr r3, [r4, #0xc]
	ldr r2, [r0]
	str r3, [r2, #0xac0]
	ldr r3, [r4, #0x10]
	ldr r2, [r0]
	str r3, [r2, #0xac4]
	ldr r3, [r4, #0x14]
	ldr r2, [r0]
	str r3, [r2, #0xac8]
	ldrb r3, [r4, #0x18]
	ldr r2, [r0]
	strb r3, [r2, #0xa92]
	ldr r0, [r0]
	strb r1, [r0, #0xacc]
	bl OS_GetTick
	ldr r1, _02239328 ; =0x0224318C
	ldr r0, _0223932C ; =0x0000064C
	ldr r1, [r1]
	add r0, r1, r0
	bl FUN_02095D68
	bl OS_GetTick
	bl MOD13_022338FC
	ldr r1, _02239328 ; =0x0224318C
	ldr r1, [r1]
	str r0, [r1, #0xaa4]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02239328: .word 0x0224318C
_0223932C: .word 0x0000064C

	arm_func_start MOD13_02239330
MOD13_02239330: ; 0x02239330
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r6, r1
	mov r7, r0
	mov r5, r2
	bl strlen
	mov r4, r0
	mov r0, r6
	bl strlen
	cmp r4, r5
	blt _02239364
	cmp r0, r5
	bge _02239370
_02239364:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_02239370:
	sub r1, r0, r5
	sub r3, r4, r5
	mov r2, r5
	add r0, r7, r3
	add r1, r6, r1
	bl memcmp
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}

	arm_func_start MOD13_0223939C
MOD13_0223939C: ; 0x0223939C
	stmdb sp!, {r0, r1, r2, r3}
	stmdb sp!, {lr}
	sub sp, sp, #4
	add r0, sp, #8
	bl MOD13_0223AF90
	ldr r0, _022393D4 ; =0x02243190
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r0, [r0, #0x84]
	bl MOD13_02239FD0
	add sp, sp, #4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr
	.align 2, 0
_022393D4: .word 0x02243190

	arm_func_start MOD13_022393D8
MOD13_022393D8: ; 0x022393D8
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x4c
	ldr r3, _022394C4 ; =0x02243190
	mov r6, r0
	ldr r0, [r3]
	mov r5, r1
	ldr r0, [r0, #0x84]
	mov r4, r2
	bl MOD13_02239F78
	add r0, sp, #4
	bl FS_InitFile
	add r0, sp, #4
	mov r1, r6
	bl FS_OpenFile
	cmp r0, #0
	bne _0223941C
	bl OS_Terminate
_0223941C:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x28]
	mov r2, #2
	sub r7, r1, r0
	cmp r5, #0
	ldr r1, _022394C8 ; =0x022409D4
	mov r0, r6
	strne r7, [r5]
	bl MOD13_02239330
	cmp r0, #0
	mvnne r6, #3
	moveq r6, r4
	mov r0, r7
	mov r1, r6
	bl MOD13_0223B004
	mov r1, r0
	add r0, sp, #4
	mov r2, r7
	str r1, [sp]
	bl FS_ReadFile
	add r0, sp, #4
	bl FS_CloseFile
	cmp r6, #0
	ldrgt r0, [sp]
	addgt sp, sp, #0x4c
	ldmgtia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [sp]
	cmp r5, #0
	ldr r0, [r0]
	mov r1, r4
	mov r0, r0, lsr #8
	strne r0, [r5]
	bl MOD13_0223B004
	mov r4, r0
	ldr r0, [sp]
	mov r1, r4
	bl MI_UncompressLZ8
	add r0, sp, #0
	bl MOD13_0223AF90
	mov r0, r4
	add sp, sp, #0x4c
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_022394C4: .word 0x02243190
_022394C8: .word 0x022409D4

	arm_func_start MOD13_022394CC
MOD13_022394CC: ; 0x022394CC
	mov r0, #1
	bx lr

	arm_func_start MOD13_022394D4
MOD13_022394D4: ; 0x022394D4
	ldr ip, _022394E0 ; =0x020D0B40
	mov r1, #0
	bx ip
	.align 2, 0
_022394E0: .word 0x020D0B40

	arm_func_start MOD13_022394E4
MOD13_022394E4: ; 0x022394E4
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr ip, _02239524 ; =MOD13_022394D4
	str ip, [sp]
	str r0, [sp, #4]
	mov ip, #1
	str ip, [sp, #8]
	ldr r0, [r0, #0x28]
	mov ip, r1
	add r1, r2, r0
	mov r2, ip
	mvn r0, #0
	bl CARDi_ReadRom
	mov r0, #6
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_02239524: .word MOD13_022394D4

	arm_func_start MOD13_02239528
MOD13_02239528: ; 0x02239528
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r1, #1
	beq _02239584
	cmp r1, #9
	beq _0223954C
	cmp r1, #0xa
	beq _02239568
	b _02239590
_0223954C:
	ldr r0, _0223959C ; =0x02243190
	ldr r0, [r0]
	ldrh r0, [r0, #0xe4]
	bl CARD_LockRom
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {pc}
_02239568:
	ldr r0, _0223959C ; =0x02243190
	ldr r0, [r0]
	ldrh r0, [r0, #0xe4]
	bl CARD_UnlockRom
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {pc}
_02239584:
	add sp, sp, #4
	mov r0, #4
	ldmia sp!, {pc}
_02239590:
	mov r0, #8
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223959C: .word 0x02243190

	arm_func_start MOD13_022395A0
MOD13_022395A0: ; 0x022395A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02239624 ; =0x022409D8
	bl FS_ChangeDir
	ldr r0, _02239628 ; =0x02243190
	ldr r0, [r0]
	add r0, r0, #0x88
	bl FS_UnloadArchiveTables
	ldr r0, _02239628 ; =0x02243190
	ldr r0, [r0]
	add r0, r0, #0x88
	bl FUN_020D0EB0
	ldr r0, _02239628 ; =0x02243190
	ldr r0, [r0]
	add r0, r0, #0x88
	bl FS_ReleaseArchiveName
	ldr r0, _02239628 ; =0x02243190
	ldr r0, [r0]
	ldrh r0, [r0, #0xe4]
	bl OS_ReleaseLockID
	ldr r0, _02239628 ; =0x02243190
	mov r2, #0
	ldr r1, [r0]
	strh r2, [r1, #0xe4]
	ldr r0, [r0]
	bl MOD13_0223AF90
	ldr r0, _02239628 ; =0x02243190
	mov r2, #0
	ldr r1, [r0]
	str r2, [r1]
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02239624: .word 0x022409D8
_02239628: .word 0x02243190

	arm_func_start MOD13_0223962C
MOD13_0223962C: ; 0x0223962C
	stmdb sp!, {r4, lr}
	sub sp, sp, #0xe8
	mov r0, #0xe8
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, _022397BC ; =0x02243190
	str r0, [r1]
	add r0, sp, #0x20
	bl FS_InitFile
	ldr r1, _022397C0 ; =0x022409E0
	add r0, sp, #0x20
	bl FS_OpenFile
	cmp r0, #0
	bne _02239668
	bl OS_Terminate
_02239668:
	bl OS_GetLockID
	ldr r2, _022397BC ; =0x02243190
	add r1, sp, #0x10
	ldr r3, [r2]
	mov r2, #8
	strh r0, [r3, #0xe4]
	add r0, sp, #0x20
	ldr r4, [sp, #0x44]
	bl FS_ReadFile
	add r0, sp, #0x20
	add r1, sp, #0x18
	mov r2, #8
	bl FS_ReadFile
	add r0, sp, #0x20
	bl FS_CloseFile
	ldr r0, _022397BC ; =0x02243190
	ldr r0, [r0]
	add r0, r0, #0x88
	bl FS_InitArchive
	ldr r0, _022397BC ; =0x02243190
	ldr r1, _022397C4 ; =0x0223F740
	ldr r0, [r0]
	mov r2, #3
	add r0, r0, #0x88
	bl FS_RegisterArchiveName
	cmp r0, #0
	bne _022396D8
	bl OS_Terminate
_022396D8:
	ldr r0, _022397BC ; =0x02243190
	ldr r1, _022397C8 ; =MOD13_02239528
	ldr r0, [r0]
	ldr r2, _022397CC ; =0x00000602
	add r0, r0, #0x88
	bl FS_SetArchiveProc
	ldr r0, [sp, #0x10]
	ldr r1, _022397D0 ; =MOD13_022394E4
	str r0, [sp]
	ldr r2, [sp, #0x14]
	ldr r0, _022397D4 ; =MOD13_022394CC
	str r2, [sp, #4]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _022397BC ; =0x02243190
	ldr r2, [sp, #0x18]
	ldr r0, [r0]
	ldr r3, [sp, #0x1c]
	mov r1, r4
	add r0, r0, #0x88
	bl FS_LoadArchive
	cmp r0, #0
	bne _02239738
	bl OS_Terminate
_02239738:
	ldr r0, _022397BC ; =0x02243190
	mov r1, #0
	ldr r0, [r0]
	mov r2, r1
	add r0, r0, #0x88
	bl FUN_020D0D84
	mov r1, #4
	mov r4, r0
	bl MOD13_0223B004
	ldr r1, _022397BC ; =0x02243190
	mov r2, r4
	ldr r3, [r1]
	str r0, [r3]
	ldr r0, [r1]
	ldr r1, [r0], #0x88
	bl FUN_020D0D84
	ldr r1, _022397BC ; =0x02243190
	mov r0, #0x20
	ldr r1, [r1]
	mov r2, #4
	add r1, r1, #4
	bl MOD13_0223A054
	ldr r2, _022397BC ; =0x02243190
	ldr r1, _022397D8 ; =0x022409F8
	ldr r3, [r2]
	ldr r2, _022397C4 ; =0x0223F740
	str r0, [r3, #0x84]
	add r0, sp, #0x68
	bl OS_SPrintf
	add r0, sp, #0x68
	bl FS_ChangeDir
	add sp, sp, #0xe8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022397BC: .word 0x02243190
_022397C0: .word 0x022409E0
_022397C4: .word 0x0223F740
_022397C8: .word MOD13_02239528
_022397CC: .word 0x00000602
_022397D0: .word MOD13_022394E4
_022397D4: .word MOD13_022394CC
_022397D8: .word 0x022409F8

	arm_func_start MOD13_022397DC
MOD13_022397DC: ; 0x022397DC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr lr, [r0, #8]
	ldr r0, _02239810 ; =0x01FF0000
	ldr ip, [lr, r1, lsl #3]
	and r0, ip, r0
	mov r0, r0, lsr #0x10
	str r0, [r2]
	ldr r0, [lr, r1, lsl #3]
	and r0, r0, #0xff
	str r0, [r3]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02239810: .word 0x01FF0000

	arm_func_start MOD13_02239814
MOD13_02239814: ; 0x02239814
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r1, #0
	ldr lr, [r0, #8]
	blt _02239844
	add r1, lr, r1, lsl #3
	ldrh r0, [r1, #4]
	add sp, sp, #4
	bic r0, r0, #0xc00
	orr r0, r0, r2, lsl #10
	strh r0, [r1, #4]
	ldmia sp!, {pc}
_02239844:
	ldrb r1, [r0, #0xc]
	mov ip, #0
	cmp r1, #0
	addle sp, sp, #4
	ldmleia sp!, {pc}
	mov r3, r2, lsl #0xa
_0223985C:
	add r2, lr, ip, lsl #3
	ldrh r1, [r2, #4]
	add ip, ip, #1
	bic r1, r1, #0xc00
	orr r1, r1, r3
	strh r1, [r2, #4]
	ldrb r1, [r0, #0xc]
	cmp ip, r1
	blt _0223985C
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_02239888
MOD13_02239888: ; 0x02239888
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x10
	cmp r1, #0
	ldr ip, [r0, #8]
	blt _022398C8
	ldr r5, [ip, r1, lsl #3]
	ldr r4, _02239988 ; =0xFE00FF00
	ldr r0, _0223998C ; =0x000001FF
	and r4, r5, r4
	and r3, r3, #0xff
	and r2, r2, r0
	orr r0, r4, r3
	orr r0, r0, r2, lsl #16
	str r0, [ip, r1, lsl #3]
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_022398C8:
	ldr r1, [ip]
	ldr lr, _02239990 ; =0x01FF0000
	ldr r4, _0223998C ; =0x000001FF
	and r1, r1, lr
	mov r1, r1, lsr #0x10
	str r1, [sp]
	ldr r1, [ip]
	ldr r5, _02239988 ; =0xFE00FF00
	and r1, r1, #0xff
	str r1, [sp, #4]
	ldr r6, [ip]
	and r1, r3, #0xff
	and r6, r6, r5
	and r7, r2, r4
	orr r1, r6, r1
	orr r1, r1, r7, lsl #16
	str r1, [ip]
	ldrb r1, [r0, #0xc]
	ldr r7, [sp]
	ldr r6, [sp, #4]
	cmp r1, #1
	sub r1, r3, r6
	addle sp, sp, #0x10
	sub r2, r2, r7
	mov r3, #1
	ldmleia sp!, {r4, r5, r6, r7, r8, pc}
_02239930:
	ldr r6, [ip, r3, lsl #3]
	and r7, r6, lr
	mov r6, r7, lsr #0x10
	str r6, [sp, #8]
	ldr r6, [ip, r3, lsl #3]
	add r8, r2, r7, lsr #16
	and r6, r6, #0xff
	str r6, [sp, #0xc]
	ldr r7, [ip, r3, lsl #3]
	add r6, r6, r1
	and r7, r7, r5
	and r6, r6, #0xff
	and r8, r8, r4
	orr r6, r7, r6
	orr r6, r6, r8, lsl #16
	str r6, [ip, r3, lsl #3]
	ldrb r6, [r0, #0xc]
	add r3, r3, #1
	cmp r3, r6
	blt _02239930
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02239988: .word 0xFE00FF00
_0223998C: .word 0x000001FF
_02239990: .word 0x01FF0000

	arm_func_start MOD13_02239994
MOD13_02239994: ; 0x02239994
	stmdb sp!, {r4, lr}
	cmp r1, #0
	ldr ip, [r0, #8]
	blt _022399CC
	ldr r0, [ip, r1, lsl #3]
	add lr, ip, r1, lsl #3
	bic r0, r0, #0xc00
	orr r0, r0, r2, lsl #10
	str r0, [ip, r1, lsl #3]
	ldrh r0, [lr, #4]
	bic r0, r0, #0xf000
	orr r0, r0, r3, lsl #12
	strh r0, [lr, #4]
	ldmia sp!, {r4, pc}
_022399CC:
	ldrb lr, [r0, #0xc]
	mov r1, #0
	cmp lr, #0
	ldmleia sp!, {r4, pc}
	mov r4, r2, lsl #0xa
	mov lr, r3, lsl #0xc
_022399E4:
	ldr r2, [ip, r1, lsl #3]
	add r3, ip, r1, lsl #3
	bic r2, r2, #0xc00
	orr r2, r2, r4
	str r2, [ip, r1, lsl #3]
	ldrh r2, [r3, #4]
	add r1, r1, #1
	bic r2, r2, #0xf000
	orr r2, r2, lr
	strh r2, [r3, #4]
	ldrb r2, [r0, #0xc]
	cmp r1, r2
	blt _022399E4
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_02239A1C
MOD13_02239A1C: ; 0x02239A1C
	stmdb sp!, {r4, lr}
	cmp r1, #0
	ldr ip, [r0, #8]
	blt _02239A70
	cmp r2, #0x100
	beq _02239A54
	cmp r2, #0x300
	beq _02239A54
	ldr r3, [ip, r1, lsl #3]
	ldr r0, _02239AD0 ; =0xC1FFFCFF
	and r0, r3, r0
	orr r0, r0, r2
	str r0, [ip, r1, lsl #3]
	ldmia sp!, {r4, pc}
_02239A54:
	ldr lr, [ip, r1, lsl #3]
	ldr r0, _02239AD0 ; =0xC1FFFCFF
	and r0, lr, r0
	orr r0, r0, r2
	orr r0, r0, r3, lsl #25
	str r0, [ip, r1, lsl #3]
	ldmia sp!, {r4, pc}
_02239A70:
	ldrb lr, [r0, #0xc]
	mov r1, #0
	cmp lr, #0
	ldmleia sp!, {r4, pc}
	mov r4, r3, lsl #0x19
	ldr r3, _02239AD0 ; =0xC1FFFCFF
_02239A88:
	cmp r2, #0x100
	beq _02239AA8
	cmp r2, #0x300
	ldrne lr, [ip, r1, lsl #3]
	andne lr, lr, r3
	orrne lr, lr, r2
	strne lr, [ip, r1, lsl #3]
	bne _02239ABC
_02239AA8:
	ldr lr, [ip, r1, lsl #3]
	and lr, lr, r3
	orr lr, lr, r2
	orr lr, r4, lr
	str lr, [ip, r1, lsl #3]
_02239ABC:
	ldrb lr, [r0, #0xc]
	add r1, r1, #1
	cmp r1, lr
	blt _02239A88
	ldmia sp!, {r4, pc}
	.align 2, 0
_02239AD0: .word 0xC1FFFCFF

	arm_func_start MOD13_02239AD4
MOD13_02239AD4: ; 0x02239AD4
	ldrb r0, [r0, #0xc]
	bx lr

	arm_func_start MOD13_02239ADC
MOD13_02239ADC: ; 0x02239ADC
	ldr r0, [r0, #8]
	add r0, r0, r1, lsl #3
	bx lr

	arm_func_start MOD13_02239AE8
MOD13_02239AE8: ; 0x02239AE8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	ldrb r0, [r5, #0xc]
	mov r4, #0
	mov r2, r4
	cmp r0, #0
	ldr r3, [r5, #8]
	ble _02239B34
	ldr r0, _02239B6C ; =0xC1FFFCFF
_02239B10:
	ldr r1, [r3]
	add r2, r2, #1
	and r1, r1, r0
	orr r1, r1, #0x200
	str r1, [r3]
	ldrb r1, [r5, #0xc]
	add r3, r3, #8
	cmp r2, r1
	blt _02239B10
_02239B34:
	mov r0, r5
	bl MOD13_0223B8C4
	ldr r0, _02239B70 ; =0x02243194
	ldr r1, [r0]
	add r0, r1, #0x228
	cmp r5, r0
	movhs r4, #1
	mov r0, #0x228
	mla r0, r4, r0, r1
	ldr r0, [r0, #0x224]
	mov r1, r5
	bl MOD13_02239FD0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02239B6C: .word 0xC1FFFCFF
_02239B70: .word 0x02243194

	arm_func_start MOD13_02239B74
MOD13_02239B74: ; 0x02239B74
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov sb, r0
	mov r0, #0x228
	mul r7, sb, r0
	ldr r0, _02239CE4 ; =0x02243194
	mov r5, r1
	ldr r0, [r0]
	mov r6, r2
	add r0, r0, r7
	ldr r0, [r0, #0x224]
	bl MOD13_02239F78
	mov r4, r0
	mov r0, #1
	bl OS_DisableIrqMask
	mov r8, r0
	cmp r6, #0
	beq _02239C44
	ldr r1, _02239CE4 ; =0x02243194
	mov r0, #0x228
	ldr r2, [r1]
	mla r0, sb, r0, r2
	add r6, r0, #0x200
	add r0, r0, #0x210
	cmp r6, r0
	beq _02239C24
	mov r1, r5, lsl #3
	add r0, r2, r7
	add r2, r0, #0x210
_02239BE8:
	ldrb sb, [r6, #0xc]
	ldr r0, [r6, #4]
	ldr ip, [r6, #8]
	ldr r3, [r0, #8]
	add ip, ip, sb, lsl #3
	add sb, ip, r1
	cmp sb, r3
	bhi _02239C18
	mov r1, r4
	str ip, [r4, #8]
	bl MOD13_0223B888
	b _02239C24
_02239C18:
	mov r6, r0
	cmp r0, r2
	bne _02239BE8
_02239C24:
	ldr r0, _02239CE4 ; =0x02243194
	ldr r0, [r0]
	add r0, r0, r7
	add r0, r0, #0x210
	cmp r6, r0
	bne _02239CCC
	bl OS_Terminate
	b _02239CCC
_02239C44:
	ldr r1, _02239CE4 ; =0x02243194
	mov r0, #0x228
	ldr r1, [r1]
	mla r0, sb, r0, r1
	add r6, r0, #0x210
	add r0, r0, #0x200
	cmp r6, r0
	beq _02239CB0
	mov r0, r5, lsl #3
	add r1, r1, r7
	add r1, r1, #0x200
_02239C70:
	ldr ip, [r6]
	ldr sb, [r6, #8]
	ldrb r2, [ip, #0xc]
	ldr r3, [ip, #8]
	sub sb, sb, r0
	add r2, r3, r2, lsl #3
	cmp sb, r2
	blo _02239CA4
	mov r0, r6
	mov r1, r4
	str sb, [r4, #8]
	bl MOD13_0223B888
	b _02239CB0
_02239CA4:
	mov r6, ip
	cmp ip, r1
	bne _02239C70
_02239CB0:
	ldr r0, _02239CE4 ; =0x02243194
	ldr r0, [r0]
	add r0, r0, r7
	add r0, r0, #0x200
	cmp r6, r0
	bne _02239CCC
	bl OS_Terminate
_02239CCC:
	mov r0, r8
	bl OS_EnableIrqMask
	mov r0, r4
	strb r5, [r4, #0xc]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_02239CE4: .word 0x02243194

	arm_func_start MOD13_02239CE8
MOD13_02239CE8: ; 0x02239CE8
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, #0
	mov r5, r6
	ldr r4, _02239D34 ; =0x02243194
_02239CF8:
	ldr r0, [r4]
	add r0, r0, r5
	ldr r0, [r0, #0x220]
	bl MOD13_0223B904
	ldr r0, [r4]
	add r0, r0, r5
	ldr r0, [r0, #0x224]
	bl MOD13_0223A030
	add r6, r6, #1
	cmp r6, #2
	add r5, r5, #0x228
	blt _02239CF8
	ldr r0, _02239D34 ; =0x02243194
	bl MOD13_0223AF90
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02239D34: .word 0x02243194

	arm_func_start MOD13_02239D38
MOD13_02239D38: ; 0x02239D38
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	mov r0, #0x450
	mov r1, #4
	bl MOD13_0223AFE0
	ldr sl, _02239E08 ; =0x02243194
	mov sb, #0
	mov r8, sb
	str r0, [sl]
	mov r7, #0x20
	mov r6, #0x10
	mov r5, #0x40
	mov r4, #0x7f
_02239D68:
	ldr r1, [sl]
	mov r0, r7
	mov r2, r6
	add r1, r1, r8
	bl MOD13_0223A054
	ldr r1, [sl]
	add r1, r1, r8
	str r0, [r1, #0x224]
	bl MOD13_0223B928
	ldr r2, [sl]
	mov r1, r5
	add r2, r2, r8
	str r0, [r2, #0x220]
	mov r0, sb
	bl MOD13_0223B95C
	ldr r2, [sl]
	mov r1, r4
	add r2, r2, r8
	str r0, [r2, #0x208]
	mov r0, sb
	bl MOD13_0223B95C
	add r1, r0, #8
	ldr r0, [sl]
	add r0, r0, r8
	str r1, [r0, #0x218]
	ldr r0, [sl]
	add r1, r0, r8
	ldr r0, [r1, #0x220]
	add r1, r1, #0x200
	bl MOD13_0223B868
	ldr r0, [sl]
	add r1, r0, r8
	ldr r0, [r1, #0x220]
	add r1, r1, #0x210
	bl MOD13_0223B878
	add r8, r8, #0x228
	add sb, sb, #1
	cmp sb, #2
	blt _02239D68
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_02239E08: .word 0x02243194

	arm_func_start MOD13_02239E0C
MOD13_02239E0C: ; 0x02239E0C
	stmdb sp!, {r4, r5, r6, lr}
	ldr r3, _02239E50 ; =0x02243198
	mov r6, r0
	mov r5, r1
	ldr r3, [r3, r6, lsl #2]
	mov r1, r5, lsl #3
	ldrh r1, [r3, r1]
	bl MOD13_02239B74
	mov r1, #0
	mov r4, r0
	bl MOD13_02239ADC
	mov r2, r0
	mov r0, r6
	mov r1, r5
	bl MOD13_02239E8C
	mov r0, r4
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02239E50: .word 0x02243198

	arm_func_start MOD13_02239E54
MOD13_02239E54: ; 0x02239E54
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r5, r1
	add r1, sp, #0
	mov r6, r0
	bl MOD13_0223B9C0
	mov r4, r0
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD13_02239E8C
	mov r0, r4
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}

	arm_func_start MOD13_02239E8C
MOD13_02239E8C: ; 0x02239E8C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #8
	ldr r3, _02239F1C ; =0x02243198
	mov r5, r2
	ldr r6, [r3, r0, lsl #2]
	mov r2, r1, lsl #3
	add r0, r6, r1, lsl #3
	ldr r3, [r0, #4]
	ldrh r4, [r6, r2]
	add r1, sp, #0
	mov r0, #0
	mov r2, #8
	add sl, r6, r3
	bl MIi_CpuClear32
	cmp r4, #0
	mov sb, #0
	addle sp, sp, #8
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	add r8, sp, #0
	mov r7, #6
	mov r6, #8
_02239EE0:
	mov r0, sl
	mov r1, r8
	mov r2, r7
	bl MIi_CpuCopy16
	mov r0, r8
	mov r1, r5
	mov r2, r6
	bl MIi_CpuCopy32
	add sb, sb, #1
	cmp sb, r4
	add sl, sl, #6
	add r5, r5, #8
	blt _02239EE0
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_02239F1C: .word 0x02243198

	arm_func_start MOD13_02239F20
MOD13_02239F20: ; 0x02239F20
	stmdb sp!, {r4, lr}
	ldr r1, _02239F44 ; =0x02243198
	mov r4, r0
	ldr r0, [r1, r4, lsl #2]
	bl MOD13_0223939C
	ldr r0, _02239F44 ; =0x02243198
	mov r1, #0
	str r1, [r0, r4, lsl #2]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02239F44: .word 0x02243198

	arm_func_start MOD13_02239F48
MOD13_02239F48: ; 0x02239F48
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	mov r0, r1
	add r1, sp, #0
	mov r2, #4
	bl MOD13_022393D8
	ldr r1, _02239F74 ; =0x02243198
	str r0, [r1, r4, lsl #2]
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02239F74: .word 0x02243198

	arm_func_start MOD13_02239F78
MOD13_02239F78: ; 0x02239F78
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r0, #1
	mov r5, #0
	bl OS_DisableIrqMask
	ldrb r2, [r6, #3]
	ldrb r1, [r6, #2]
	mov r4, r0
	cmp r1, r2
	beq _02239FC0
	ldrh r1, [r6]
	add r0, r2, r1
	sub r0, r0, #1
	bl FX_ModS32
	strb r0, [r6, #3]
	ldrb r0, [r6, #3]
	add r0, r6, r0, lsl #2
	ldr r5, [r0, #4]
_02239FC0:
	mov r0, r4
	bl OS_EnableIrqMask
	mov r0, r5
	ldmia sp!, {r4, r5, r6, pc}

	arm_func_start MOD13_02239FD0
MOD13_02239FD0: ; 0x02239FD0
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r0, #1
	mov r4, r1
	bl OS_DisableIrqMask
	ldrb r2, [r5, #3]
	mov r7, r0
	ldrh r1, [r5]
	add r0, r2, #1
	bl FX_ModS32
	ldrb r1, [r5, #2]
	mov r6, r0
	cmp r6, r1
	bne _0223A010
	bl OS_Terminate
_0223A010:
	ldrb r1, [r5, #3]
	mov r0, r7
	add r1, r5, r1, lsl #2
	str r4, [r1, #4]
	strb r6, [r5, #3]
	bl OS_EnableIrqMask
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}

	arm_func_start MOD13_0223A030
MOD13_0223A030: ; 0x0223A030
	stmdb sp!, {r0, r1, r2, r3}
	stmdb sp!, {lr}
	sub sp, sp, #4
	add r0, sp, #8
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start MOD13_0223A054
MOD13_0223A054: ; 0x0223A054
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD13_0223A094
	cmp r6, #0
	mov r2, #0
	ble _0223A08C
_0223A074:
	add r1, r0, r2, lsl #2
	add r2, r2, #1
	str r5, [r1, #4]
	cmp r2, r6
	add r5, r5, r4
	blt _0223A074
_0223A08C:
	strb r6, [r0, #3]
	ldmia sp!, {r4, r5, r6, pc}

	arm_func_start MOD13_0223A094
MOD13_0223A094: ; 0x0223A094
	stmdb sp!, {r4, lr}
	mov r4, r0
	add r0, r4, #1
	mov r0, r0, lsl #2
	add r0, r0, #8
	mov r1, #4
	bl MOD13_0223B004
	add r1, r4, #1
	strh r1, [r0]
	mov r1, #0
	strb r1, [r0, #2]
	strb r1, [r0, #3]
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0223A0C8
MOD13_0223A0C8: ; 0x0223A0C8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldrsh r2, [r1, #4]
	add r2, r2, #1
	strh r2, [r1, #4]
	ldrsh r3, [r1, #4]
	ldrh r2, [r1, #6]
	cmp r3, r2
	addlt sp, sp, #4
	ldmltia sp!, {pc}
	mov r2, #0
	strb r2, [r1, #9]
	mov r1, r0
	mov r0, #1
	bl MOD13_0223C110
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0223A10C
MOD13_0223A10C: ; 0x0223A10C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _0223A168 ; =0x022431A0
	mov r5, r0
	ldr r4, [r1]
	ldrb r0, [r4, #9]
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
	ldr r1, _0223A16C ; =MOD13_0223A0C8
	mov r2, r4
	mov r0, #1
	mov r3, #0xc8
	bl MOD13_0223C1C4
	str r0, [r4]
	mov r0, #0
	strh r0, [r4, #4]
	strh r5, [r4, #6]
	mov r0, #1
	strb r0, [r4, #9]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223A168: .word 0x022431A0
_0223A16C: .word MOD13_0223A0C8

	arm_func_start MOD13_0223A170
MOD13_0223A170: ; 0x0223A170
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r3, _0223A294 ; =0x0223F748
	ldr r2, _0223A298 ; =0x0223F744
	ldrb r8, [r3]
	ldrb r7, [r3, #1]
	ldrb r6, [r3, #2]
	ldrb lr, [r3, #3]
	ldrb ip, [r2]
	ldrb r5, [r2, #1]
	ldrb r3, [r2, #2]
	ldrb r2, [r2, #3]
	strb r5, [sp, #5]
	mov r4, r1
	strb r8, [sp]
	strb r7, [sp, #1]
	strb r6, [sp, #2]
	strb lr, [sp, #3]
	strb ip, [sp, #4]
	strb r3, [sp, #6]
	strb r2, [sp, #7]
	ldrsh r1, [r4, #4]
	mov r5, r0
	add r0, r1, #1
	strh r0, [r4, #4]
	ldrsh r0, [r4, #4]
	ldrh r1, [r4, #6]
	mov r0, r0, lsl #4
	bl FX_DivS32
	ldrb r3, [r4, #8]
	add r2, sp, #0
	mov r1, r0
	ldrb r2, [r2, r3]
	ands r0, r2, #1
	rsbne r1, r1, #0x10
	ands r0, r2, #0x10
	ldr r0, _0223A29C ; =0x022431A0
	rsbne r1, r1, #0
	ldr r0, [r0]
	cmp r4, r0
	bne _0223A220
	ldr r0, _0223A2A0 ; =0x04001050
	bl G2x_ChangeBlendBrightness_
	b _0223A228
_0223A220:
	ldr r0, _0223A2A4 ; =0x04000050
	bl G2x_ChangeBlendBrightness_
_0223A228:
	ldrsh r1, [r4, #4]
	ldrh r0, [r4, #6]
	cmp r1, r0
	addlt sp, sp, #8
	ldmltia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r0, _0223A29C ; =0x022431A0
	ldr r0, [r0]
	cmp r4, r0
	bne _0223A264
	ldrb r2, [r4, #8]
	add r1, sp, #4
	ldr r0, _0223A2A0 ; =0x04001050
	ldrsb r1, [r1, r2]
	bl G2x_ChangeBlendBrightness_
	b _0223A278
_0223A264:
	ldrb r2, [r4, #8]
	add r1, sp, #4
	ldr r0, _0223A2A4 ; =0x04000050
	ldrsb r1, [r1, r2]
	bl G2x_ChangeBlendBrightness_
_0223A278:
	mov r2, #0
	mov r1, r5
	mov r0, #1
	strb r2, [r4, #9]
	bl MOD13_0223C110
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0223A294: .word 0x0223F748
_0223A298: .word 0x0223F744
_0223A29C: .word 0x022431A0
_0223A2A0: .word 0x04001050
_0223A2A4: .word 0x04000050

	arm_func_start MOD13_0223A2A8
MOD13_0223A2A8: ; 0x0223A2A8
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	ldr r4, _0223A374 ; =0x0223F74C
	mov r5, r0
	ldrb r0, [r4, #3]
	ldrb r6, [r4]
	ldrb lr, [r4, #1]
	strb r0, [sp, #3]
	cmp r1, #1
	ldreq r0, _0223A378 ; =0x022431A0
	ldrb ip, [r4, #2]
	strb r6, [sp]
	ldreq r6, [r0]
	ldrne r0, _0223A378 ; =0x022431A0
	strb lr, [sp, #1]
	ldrne r0, [r0]
	strb ip, [sp, #2]
	addne r6, r0, #0xc
	ldrb r0, [r6, #9]
	mov r4, r3
	cmp r0, #0
	addne sp, sp, #8
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	cmp r1, #1
	bne _0223A328
	add r0, sp, #0
	mov r1, r2
	ldrsb r2, [r0, r5]
	ldr r0, _0223A37C ; =0x04001050
	bl G2x_SetBlendBrightness_
	b _0223A33C
_0223A328:
	add r0, sp, #0
	mov r1, r2
	ldrsb r2, [r0, r5]
	ldr r0, _0223A380 ; =0x04000050
	bl G2x_SetBlendBrightness_
_0223A33C:
	ldr r1, _0223A384 ; =MOD13_0223A170
	mov r2, r6
	mov r0, #1
	mov r3, #0xc8
	bl MOD13_0223C1C4
	str r0, [r6]
	mov r0, #0
	strh r0, [r6, #4]
	strb r5, [r6, #8]
	strh r4, [r6, #6]
	mov r0, #1
	strb r0, [r6, #9]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0223A374: .word 0x0223F74C
_0223A378: .word 0x022431A0
_0223A37C: .word 0x04001050
_0223A380: .word 0x04000050
_0223A384: .word MOD13_0223A170

	arm_func_start MOD13_0223A388
MOD13_0223A388: ; 0x0223A388
	cmp r0, #1
	ldreq r0, _0223A3A8 ; =0x022431A0
	ldreq r0, [r0]
	ldrne r0, _0223A3A8 ; =0x022431A0
	ldrne r0, [r0]
	addne r0, r0, #0xc
	ldrb r0, [r0, #9]
	bx lr
	.align 2, 0
_0223A3A8: .word 0x022431A0

	arm_func_start MOD13_0223A3AC
MOD13_0223A3AC: ; 0x0223A3AC
	ldr ip, _0223A3B8 ; =MOD13_0223AF90
	ldr r0, _0223A3BC ; =0x022431A0
	bx ip
	.align 2, 0
_0223A3B8: .word MOD13_0223AF90
_0223A3BC: .word 0x022431A0

	arm_func_start MOD13_0223A3C0
MOD13_0223A3C0: ; 0x0223A3C0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x18
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r2, _0223A404 ; =0x022431A0
	mov r1, #0x3f
	str r0, [r2]
	ldr r0, _0223A408 ; =0x04000050
	mov r2, #0x10
	bl G2x_SetBlendBrightness_
	ldr r0, _0223A40C ; =0x04001050
	mov r1, #0x3f
	mov r2, #0x10
	bl G2x_SetBlendBrightness_
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223A404: .word 0x022431A0
_0223A408: .word 0x04000050
_0223A40C: .word 0x04001050

	arm_func_start MOD13_0223A410
MOD13_0223A410: ; 0x0223A410
	ldr r2, _0223A438 ; =0x022431A4
	ldr r1, _0223A43C ; =0x00000718
	ldr r2, [r2]
	add r1, r2, r1
	cmp r0, r1
	moveq r0, #1
	streqb r0, [r2, #0x794]
	movne r0, #1
	strneb r0, [r2, #0x795]
	bx lr
	.align 2, 0
_0223A438: .word 0x022431A4
_0223A43C: .word 0x00000718

	arm_func_start MOD13_0223A440
MOD13_0223A440: ; 0x0223A440
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x10
	mov r6, r3
	mov r4, r0
	mov r8, r1
	mov r0, r6
	mov r1, #0
	mov r7, r2
	bl MOD13_02239ADC
	mov r2, #0
	mov r5, r0
	mov r0, r6
	mvn r1, #0
	mov r3, r2
	bl MOD13_02239A1C
	mov r0, r6
	mvn r1, #0
	mov r2, #0
	mov r3, #0xf
	bl MOD13_02239994
	mov r0, r6
	mvn r1, #0
	ldr r2, [sp, #0x28]
	bl MOD13_02239814
	str r7, [sp]
	mov r0, r5
	mov r3, r8
	mov r1, #0
	str r1, [sp, #4]
	ldrh r2, [r4, #0x34]
	mov r1, #2
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	ldrb r1, [r4, #0x36]
	ldrb r2, [r4, #0x37]
	bl FUN_020B5E50
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

	arm_func_start MOD13_0223A4D8
MOD13_0223A4D8: ; 0x0223A4D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, [r0, #0x18]
	blx r2
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0223A4F0
MOD13_0223A4F0: ; 0x0223A4F0
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr lr, [sp, #0x18]
	ldr ip, [sp, #0x1c]
	str lr, [sp]
	ldr lr, [sp, #0x20]
	str ip, [sp, #4]
	ldr ip, [sp, #0x24]
	str lr, [sp, #8]
	add r0, r0, #0x20
	str ip, [sp, #0xc]
	bl FUN_020B7168
	add sp, sp, #0x14
	ldmia sp!, {pc}

	arm_func_start MOD13_0223A528
MOD13_0223A528: ; 0x0223A528
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	ldr r7, [sp, #0x34]
	mov sb, r1
	ldrh r1, [r7]
	ldr r8, [sp, #0x30]
	ldr r6, [sp, #0x38]
	mov sl, r0
	mov fp, r2
	str r3, [sp, #8]
	cmp r1, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r0, #0xc
	mul r4, r6, r0
_0223A564:
	ldr r0, _0223A5E8 ; =0x022431A4
	ldr r0, [r0]
	add r5, r0, r4
	mov r0, r5
	bl FUN_020B5CE4
	mov r1, r0
	ldr r0, _0223A5EC ; =0x0000FFFF
	cmp r1, r0
	ldreq r0, [r5]
	ldreqh r1, [r0, #2]
	mov r0, r5
	bl FUN_020B5C88
	ldrh r1, [r5, #8]
	ldrh r2, [r7]
	ldr r3, [sp, #8]
	cmp r1, #0
	ldrnesb r1, [r0]
	ldrneb r0, [r0, #1]
	addne r0, r1, r0
	ldreqsb r0, [r0, #2]
	sub r1, r8, r0
	str r2, [sp]
	mov r0, sl
	mov r2, fp
	add r1, sb, r1, asr #1
	str r6, [sp, #4]
	bl MOD13_0223A5F0
	ldrh r1, [r7, #2]!
	add sb, sb, r8
	cmp r1, #0
	bne _0223A564
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_0223A5E8: .word 0x022431A4
_0223A5EC: .word 0x0000FFFF

	arm_func_start MOD13_0223A5F0
MOD13_0223A5F0: ; 0x0223A5F0
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldrh ip, [sp, #0x10]
	str r3, [sp]
	ldr r3, _0223A630 ; =0x022431A4
	str ip, [sp, #4]
	ldr lr, [r3]
	ldr ip, [sp, #0x14]
	mov r3, #0xc
	mov r4, r1
	mla r1, ip, r3, lr
	mov r3, r2
	mov r2, r4
	bl FUN_020B63CC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223A630: .word 0x022431A4

	arm_func_start MOD13_0223A634
MOD13_0223A634: ; 0x0223A634
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr lr, [sp, #0x10]
	ldr ip, [sp, #0x14]
	str lr, [sp]
	add r0, r0, #0x20
	str ip, [sp, #4]
	bl FUN_020B7218
	add sp, sp, #0xc
	ldmia sp!, {pc}

	arm_func_start MOD13_0223A65C
MOD13_0223A65C: ; 0x0223A65C
	ldr r2, _0223A67C ; =0x022431A4
	ldr r1, _0223A680 ; =0x00000718
	ldr r3, [r2]
	mov r2, #0x38
	add r1, r3, r1
	mla r0, r2, r0, r1
	ldr ip, _0223A684 ; =MOD13_0223A688
	bx ip
	.align 2, 0
_0223A67C: .word 0x022431A4
_0223A680: .word 0x00000718
_0223A684: .word MOD13_0223A688

	arm_func_start MOD13_0223A688
MOD13_0223A688: ; 0x0223A688
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0x34]
	mov r0, #1
	bl MOD13_0223C104
	ldr r1, _0223A70C ; =0x022431A4
	ldr r0, _0223A710 ; =0x00000718
	ldr r1, [r1]
	add r0, r1, r0
	cmp r4, r0
	bne _0223A6DC
	bl G2_GetBG0CharPtr
	ldr r2, _0223A714 ; =0x0223F754
	mov r1, r0
	ldrh r3, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0
	mul r2, r3, r2
	mov r2, r2, lsl #5
	bl MIi_CpuClear16
	b _0223A700
_0223A6DC:
	bl G2_GetBG0CharPtr
	ldr r2, _0223A714 ; =0x0223F754
	mov r1, r0
	ldrh r3, [r2, #4]
	ldrh r2, [r2, #6]
	mov r0, #0
	mul r2, r3, r2
	mov r2, r2, lsl #5
	bl MIi_CpuClear16
_0223A700:
	add r0, r4, #0x30
	bl MOD13_0223AF90
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223A70C: .word 0x022431A4
_0223A710: .word 0x00000718
_0223A714: .word 0x0223F754

	arm_func_start MOD13_0223A718
MOD13_0223A718: ; 0x0223A718
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r1
	ldrb r0, [r4]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _0223A7E0 ; =0x022431A4
	ldr r0, _0223A7E4 ; =0x00000794
	ldr r2, [r1]
	add r0, r2, r0
	cmp r4, r0
	bne _0223A790
	ldr r1, _0223A7E8 ; =0x0223F754
	ldr r0, [r2, #0x748]
	ldrh r2, [r1]
	ldrh r1, [r1, #2]
	mul r1, r2, r1
	mov r5, r1, lsl #5
	mov r1, r5
	bl DC_FlushRange
	ldr r1, _0223A7E0 ; =0x022431A4
	ldr r0, _0223A7EC ; =0x0223F750
	ldr r2, [r1]
	ldrh r1, [r0]
	ldr r0, [r2, #0x748]
	mov r2, r5
	mov r1, r1, lsl #5
	bl GX_LoadBG0Char
	b _0223A7D0
_0223A790:
	ldr r1, _0223A7E8 ; =0x0223F754
	ldr r0, [r2, #0x780]
	ldrh r2, [r1, #4]
	ldrh r1, [r1, #6]
	mul r1, r2, r1
	mov r5, r1, lsl #5
	mov r1, r5
	bl DC_FlushRange
	ldr r1, _0223A7E0 ; =0x022431A4
	ldr r0, _0223A7EC ; =0x0223F750
	ldr r2, [r1]
	ldrh r1, [r0, #2]
	ldr r0, [r2, #0x780]
	mov r2, r5
	mov r1, r1, lsl #5
	bl GXS_LoadBG0Char
_0223A7D0:
	mov r0, #0
	strb r0, [r4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223A7E0: .word 0x022431A4
_0223A7E4: .word 0x00000794
_0223A7E8: .word 0x0223F754
_0223A7EC: .word 0x0223F750

	arm_func_start MOD13_0223A7F0
MOD13_0223A7F0: ; 0x0223A7F0
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x10
	mov r8, r0
	ldr r0, _0223A954 ; =0x022431A4
	ldr r3, _0223A958 ; =0x0223F756
	mov r4, r8, lsl #2
	ldr r2, _0223A95C ; =0x0223F754
	ldrh r5, [r3, r4]
	ldrh r4, [r2, r4]
	ldr r3, [r0]
	ldr r0, _0223A960 ; =0x00000718
	mul r2, r4, r5
	mov r7, r1
	add r1, r3, r0
	mov r0, #0x38
	mla r6, r8, r0, r1
	mov r0, r2, lsl #5
	mov r1, #0x20
	bl MOD13_0223B004
	str r0, [r6, #0x30]
	cmp r8, #1
	bne _0223A86C
	ldr r1, _0223A964 ; =0x04001008
	ldrh r0, [r1]
	bic r0, r0, #0x40
	strh r0, [r1]
	ldrh r0, [r1]
	and r0, r0, #0x43
	orr r0, r0, #0xc00
	strh r0, [r1]
	b _0223A88C
_0223A86C:
	ldr r1, _0223A968 ; =0x04000008
	ldrh r0, [r1]
	bic r0, r0, #0x40
	strh r0, [r1]
	ldrh r0, [r1]
	and r0, r0, #0x43
	orr r0, r0, #0xc00
	strh r0, [r1]
_0223A88C:
	mov r0, #4
	str r0, [sp]
	ldr r1, [r6, #0x30]
	mov r0, r6
	mov r2, r4
	mov r3, r5
	bl FUN_020B6388
	ldr r1, _0223A954 ; =0x022431A4
	mov r0, #0xc
	ldr r2, [r1]
	mov r1, #1
	mla r0, r7, r0, r2
	str r6, [r6, #0x20]
	str r0, [r6, #0x24]
	str r1, [r6, #0x28]
	str r1, [r6, #0x2c]
	cmp r8, #1
	bne _0223A8DC
	bl G2S_GetBG0ScrPtr
	b _0223A8E0
_0223A8DC:
	bl G2_GetBG0ScrPtr
_0223A8E0:
	mov r3, #0
	str r3, [sp]
	mov r2, #0x20
	ldr r1, _0223A96C ; =0x0223F750
	str r2, [sp, #4]
	mov r2, r8, lsl #1
	ldrh r7, [r1, r2]
	mov r1, r4
	mov r2, r5
	str r7, [sp, #8]
	mov r4, #0xf
	str r4, [sp, #0xc]
	bl FUN_020B6240
	mov r0, r6
	mov r1, #0
	bl MOD13_0223A4D8
	ldr r1, _0223A954 ; =0x022431A4
	ldr r0, _0223A970 ; =0x00000794
	ldr r2, [r1]
	ldr r1, _0223A974 ; =MOD13_0223A718
	add r0, r2, r0
	add r2, r0, r8
	mov r0, #1
	mov r3, #0xc8
	bl MOD13_0223C1C4
	str r0, [r6, #0x34]
	mov r0, r6
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0223A954: .word 0x022431A4
_0223A958: .word 0x0223F756
_0223A95C: .word 0x0223F754
_0223A960: .word 0x00000718
_0223A964: .word 0x04001008
_0223A968: .word 0x04000008
_0223A96C: .word 0x0223F750
_0223A970: .word 0x00000794
_0223A974: .word MOD13_0223A718

	arm_func_start MOD13_0223A978
MOD13_0223A978: ; 0x0223A978
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #0x30]
	bl MOD13_0223BB20
	ldr r0, _0223A9A0 ; =0x022431A4
	mov r1, r4
	ldr r0, [r0]
	ldr r0, [r0, #0x788]
	bl MOD13_02239FD0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223A9A0: .word 0x022431A4

	arm_func_start MOD13_0223A9A4
MOD13_0223A9A4: ; 0x0223A9A4
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r4, _0223AA7C ; =0x022431A4
	mov r7, r0
	ldr r0, [r4]
	mov r6, r1
	ldr r0, [r0, #0x788]
	mov r5, r2
	mov r8, r3
	bl MOD13_02239F78
	mov r4, r0
	strb r6, [r4, #0x36]
	mul r1, r6, r5
	mov r2, r8
	strb r5, [r4, #0x37]
	mov r0, r7
	add r3, sp, #4
	bl MOD13_0223BB68
	str r0, [r4, #0x30]
	ldr r1, [sp, #4]
	mov r0, r6
	strh r1, [r4, #0x34]
	mov r1, r5
	bl FUN_020B6180
	ldr r1, [sp, #0x20]
	cmp r7, #1
	str r0, [r1]
	moveq ip, #0x6600000
	ldr r7, [sp, #4]
	mov r1, #4
	movne ip, #0x6400000
	str r1, [sp]
	mov r0, r4
	mov r2, r6
	mov r3, r5
	add r1, ip, r7, lsl #7
	bl FUN_020B62F8
	ldr r2, [r4, #0x18]
	mov r0, r4
	mov r1, #0
	blx r2
	ldr r0, _0223AA7C ; =0x022431A4
	ldr r1, [sp, #0x24]
	ldr r2, [r0]
	mov r0, #0xc
	mla r0, r1, r0, r2
	str r4, [r4, #0x20]
	str r0, [r4, #0x24]
	mov r1, #1
	str r1, [r4, #0x28]
	mov r0, r4
	str r1, [r4, #0x2c]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0223AA7C: .word 0x022431A4

	arm_func_start MOD13_0223AA80
MOD13_0223AA80: ; 0x0223AA80
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r4, _0223AACC ; =0x022431A4
	mov r5, #0
_0223AA90:
	ldr r0, [r4]
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x78c]
	bl MOD13_0223939C
	add r5, r5, #1
	cmp r5, #2
	blt _0223AA90
	ldr r0, _0223AACC ; =0x022431A4
	ldr r0, [r0]
	ldr r0, [r0, #0x788]
	bl MOD13_0223A030
	ldr r0, _0223AACC ; =0x022431A4
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223AACC: .word 0x022431A4

	arm_func_start MOD13_0223AAD0
MOD13_0223AAD0: ; 0x0223AAD0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	ldr r0, _0223AB68 ; =0x00000798
	mov r1, #4
	bl MOD13_0223B004
	mov r4, r0
	ldr r3, _0223AB6C ; =0x022431A4
	add r1, r4, #0x18
	mov r0, #0x20
	mov r2, #0x38
	str r4, [r3]
	bl MOD13_0223A054
	ldr sb, _0223AB6C ; =0x022431A4
	mov r8, #0
	ldr r1, [sb]
	mov r7, r8
	str r0, [r1, #0x788]
	ldr r6, _0223AB70 ; =0x02240A00
	mov r5, r8
	mov r4, #4
_0223AB20:
	ldr r0, [r6, r8, lsl #2]
	mov r1, r5
	mov r2, r4
	bl MOD13_022393D8
	ldr r1, [sb]
	add r1, r1, r8, lsl #2
	str r0, [r1, #0x78c]
	ldr r2, [sb]
	add r0, r2, r8, lsl #2
	ldr r1, [r0, #0x78c]
	add r0, r2, r7
	bl FUN_020B5D3C
	add r8, r8, #1
	cmp r8, #2
	add r7, r7, #0xc
	blt _0223AB20
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_0223AB68: .word 0x00000798
_0223AB6C: .word 0x022431A4
_0223AB70: .word 0x02240A00

	arm_func_start MOD13_0223AB74
MOD13_0223AB74: ; 0x0223AB74
	ldrh r3, [r0]
	strh r3, [r2]
	ldrh r3, [r0, #2]
	strh r3, [r2, #2]
	ldrh ip, [r0]
	ldrh r3, [r1]
	add r3, ip, r3
	strh r3, [r2, #4]
	ldrh r3, [r0, #2]
	ldrh r0, [r1, #2]
	add r0, r3, r0
	strh r0, [r2, #6]
	bx lr

	arm_func_start MOD13_0223ABA8
MOD13_0223ABA8: ; 0x0223ABA8
	ldr ip, [sp]
	strh r0, [ip]
	strh r1, [ip, #2]
	strh r2, [ip, #4]
	strh r3, [ip, #6]
	bx lr

	arm_func_start MOD13_0223ABC0
MOD13_0223ABC0: ; 0x0223ABC0
	strh r0, [r2]
	strh r1, [r2, #2]
	bx lr

	arm_func_start MOD13_0223ABCC
MOD13_0223ABCC: ; 0x0223ABCC
	cmp r1, #3
	addls pc, pc, r1, lsl #2
	bx lr
_0223ABD8: ; jump table
	b _0223ABE8 ; case 0
	b _0223AC38 ; case 1
	b _0223AC88 ; case 2
	b _0223ACD8 ; case 3
_0223ABE8:
	cmp r0, #1
	bne _0223AC14
	ldr r0, _0223AD28 ; =0x04001048
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f
	orr r1, r0, r2
	ldr r0, _0223AD28 ; =0x04001048
	orrne r1, r1, #0x20
	strh r1, [r0]
	bx lr
_0223AC14:
	ldr r0, _0223AD2C ; =0x04000048
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f
	orr r1, r0, r2
	ldr r0, _0223AD2C ; =0x04000048
	orrne r1, r1, #0x20
	strh r1, [r0]
	bx lr
_0223AC38:
	cmp r0, #1
	bne _0223AC64
	ldr r0, _0223AD28 ; =0x04001048
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f00
	orr r1, r0, r2, lsl #8
	ldr r0, _0223AD28 ; =0x04001048
	orrne r1, r1, #0x2000
	strh r1, [r0]
	bx lr
_0223AC64:
	ldr r0, _0223AD2C ; =0x04000048
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f00
	orr r1, r0, r2, lsl #8
	ldr r0, _0223AD2C ; =0x04000048
	orrne r1, r1, #0x2000
	strh r1, [r0]
	bx lr
_0223AC88:
	cmp r0, #1
	bne _0223ACB4
	ldr r0, _0223AD30 ; =0x0400104A
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f00
	orr r1, r0, r2, lsl #8
	ldr r0, _0223AD30 ; =0x0400104A
	orrne r1, r1, #0x2000
	strh r1, [r0]
	bx lr
_0223ACB4:
	ldr r0, _0223AD34 ; =0x0400004A
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f00
	orr r1, r0, r2, lsl #8
	ldr r0, _0223AD34 ; =0x0400004A
	orrne r1, r1, #0x2000
	strh r1, [r0]
	bx lr
_0223ACD8:
	cmp r0, #1
	bne _0223AD04
	ldr r0, _0223AD30 ; =0x0400104A
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f
	orr r1, r0, r2
	ldr r0, _0223AD30 ; =0x0400104A
	orrne r1, r1, #0x20
	strh r1, [r0]
	bx lr
_0223AD04:
	ldr r0, _0223AD34 ; =0x0400004A
	cmp r3, #0
	ldrh r0, [r0]
	bic r0, r0, #0x3f
	orr r1, r0, r2
	ldr r0, _0223AD34 ; =0x0400004A
	orrne r1, r1, #0x20
	strh r1, [r0]
	bx lr
	.align 2, 0
_0223AD28: .word 0x04001048
_0223AD2C: .word 0x04000048
_0223AD30: .word 0x0400104A
_0223AD34: .word 0x0400004A

	arm_func_start MOD13_0223AD38
MOD13_0223AD38: ; 0x0223AD38
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #1
	bne _0223ADE0
	cmp r1, #0
	bne _0223AD98
	ldrh r0, [r2]
	ldrh r1, [r2, #4]
	ldrh r3, [r2, #2]
	ldrh lr, [r2, #6]
	mov r2, r0, lsl #8
	mov r0, r3, lsl #8
	and r2, r2, #0xff00
	and r1, r1, #0xff
	orr ip, r2, r1
	ldr r3, _0223AE78 ; =0x04001040
	and r2, r0, #0xff00
	and r1, lr, #0xff
	ldr r0, _0223AE7C ; =0x04001044
	strh ip, [r3]
	orr r1, r2, r1
	strh r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
_0223AD98:
	ldrh r0, [r2]
	ldrh r1, [r2, #4]
	ldrh r3, [r2, #2]
	ldrh lr, [r2, #6]
	mov r2, r0, lsl #8
	mov r0, r3, lsl #8
	and r2, r2, #0xff00
	and r1, r1, #0xff
	orr ip, r2, r1
	ldr r3, _0223AE80 ; =0x04001042
	and r2, r0, #0xff00
	and r1, lr, #0xff
	ldr r0, _0223AE84 ; =0x04001046
	strh ip, [r3]
	orr r1, r2, r1
	strh r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
_0223ADE0:
	cmp r1, #0
	bne _0223AE30
	ldrh r0, [r2]
	ldrh r1, [r2, #4]
	ldrh r3, [r2, #2]
	ldrh lr, [r2, #6]
	mov r2, r0, lsl #8
	mov r0, r3, lsl #8
	and r2, r2, #0xff00
	and r1, r1, #0xff
	orr ip, r2, r1
	ldr r3, _0223AE88 ; =0x04000040
	and r2, r0, #0xff00
	and r1, lr, #0xff
	ldr r0, _0223AE8C ; =0x04000044
	strh ip, [r3]
	orr r1, r2, r1
	strh r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
_0223AE30:
	ldrh r0, [r2]
	ldrh r3, [r2, #2]
	ldrh r1, [r2, #4]
	ldrh lr, [r2, #6]
	mov r2, r0, lsl #8
	mov r0, r3, lsl #8
	and r2, r2, #0xff00
	and r1, r1, #0xff
	ldr r3, _0223AE90 ; =0x04000042
	orr ip, r2, r1
	and r2, r0, #0xff00
	and r1, lr, #0xff
	ldr r0, _0223AE94 ; =0x04000046
	strh ip, [r3]
	orr r1, r2, r1
	strh r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223AE78: .word 0x04001040
_0223AE7C: .word 0x04001044
_0223AE80: .word 0x04001042
_0223AE84: .word 0x04001046
_0223AE88: .word 0x04000040
_0223AE8C: .word 0x04000044
_0223AE90: .word 0x04000042
_0223AE94: .word 0x04000046

	arm_func_start MOD13_0223AE98
MOD13_0223AE98: ; 0x0223AE98
	cmp r0, #1
	bne _0223AEC8
	ldr r3, _0223AEF0 ; =0x04001000
	mvn r0, r1
	ldr r2, [r3]
	ldr r1, [r3]
	and r2, r2, #0x1f00
	bic r1, r1, #0x1f00
	and r0, r0, r2, lsr #8
	orr r0, r1, r0, lsl #8
	str r0, [r3]
	bx lr
_0223AEC8:
	mov r3, #0x4000000
	ldr r0, [r3]
	ldr r2, [r3]
	and ip, r0, #0x1f00
	mvn r0, r1
	bic r1, r2, #0x1f00
	and r0, r0, ip, lsr #8
	orr r0, r1, r0, lsl #8
	str r0, [r3]
	bx lr
	.align 2, 0
_0223AEF0: .word 0x04001000

	arm_func_start MOD13_0223AEF4
MOD13_0223AEF4: ; 0x0223AEF4
	cmp r0, #1
	bne _0223AF20
	ldr r3, _0223AF44 ; =0x04001000
	ldr r2, [r3]
	ldr r0, [r3]
	and ip, r2, #0x1f00
	bic r2, r0, #0x1f00
	orr r0, r1, ip, lsr #8
	orr r0, r2, r0, lsl #8
	str r0, [r3]
	bx lr
_0223AF20:
	mov r3, #0x4000000
	ldr r2, [r3]
	ldr r0, [r3]
	and ip, r2, #0x1f00
	bic r2, r0, #0x1f00
	orr r0, r1, ip, lsr #8
	orr r0, r2, r0, lsl #8
	str r0, [r3]
	bx lr
	.align 2, 0
_0223AF44: .word 0x04001000

	arm_func_start MOD13_0223AF48
MOD13_0223AF48: ; 0x0223AF48
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r0, #1
	bl OS_DisableIrqMask
	cmp r5, #0
	mov r4, r0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, _0223AF8C ; =0x022431A8
	mov r1, r5
	ldr r0, [r0]
	bl FUN_020ADDF0
	mov r0, r4
	bl OS_EnableIrqMask
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223AF8C: .word 0x022431A8

	arm_func_start MOD13_0223AF90
MOD13_0223AF90: ; 0x0223AF90
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r0, #1
	bl OS_DisableIrqMask
	ldr r1, [r5]
	mov r4, r0
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, _0223AFDC ; =0x022431A8
	ldr r0, [r0]
	bl FUN_020ADDF0
	mov r0, r4
	bl OS_EnableIrqMask
	mov r0, #0
	str r0, [r5]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223AFDC: .word 0x022431A8

	arm_func_start MOD13_0223AFE0
MOD13_0223AFE0: ; 0x0223AFE0
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD13_0223B004
	mov r2, r4
	mov r1, #0
	mov r4, r0
	bl MI_CpuFill8
	mov r0, r4
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0223B004
MOD13_0223B004: ; 0x0223B004
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r0, #1
	mov r5, r1
	bl OS_DisableIrqMask
	ldr r1, _0223B04C ; =0x022431A8
	mov r4, r0
	ldr r0, [r1]
	mov r1, r6
	mov r2, r5
	bl tempName_NNS_FndAllocFromExpHeapEx
	movs r5, r0
	bne _0223B03C
	bl OS_Terminate
_0223B03C:
	mov r0, r4
	bl OS_EnableIrqMask
	mov r0, r5
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0223B04C: .word 0x022431A8

	arm_func_start MOD13_0223B050
MOD13_0223B050: ; 0x0223B050
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223B078 ; =0x022431A8
	ldr r0, [r0]
	bl thunk_FUN_020adc8c
	ldr r0, _0223B078 ; =0x022431A8
	mov r1, #0
	str r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223B078: .word 0x022431A8

	arm_func_start MOD13_0223B07C
MOD13_0223B07C: ; 0x0223B07C
	stmdb sp!, {r4, lr}
	mov r4, r0
	mov r1, #0
	mov r2, #0x40000
	bl MI_CpuFill8
	mov r0, r4
	mov r1, #0x40000
	mov r2, #0
	bl tempName_NNS_FndCreateExpHeapEx
	ldr r1, _0223B0B8 ; =0x022431A8
	cmp r0, #0
	str r0, [r1]
	ldmneia sp!, {r4, pc}
	bl OS_Terminate
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223B0B8: .word 0x022431A8

	arm_func_start MOD13_0223B0BC
MOD13_0223B0BC: ; 0x0223B0BC
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223B144 ; =0x022431AC
	ldrb r0, [r0]
	cmp r0, #0
	beq _0223B10C
	ldr r0, _0223B148 ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	addne sp, sp, #4
	ldmneia sp!, {pc}
	mov r0, #1
	bl PM_SetLCDPower
	cmp r0, #0
	ldrne r0, _0223B144 ; =0x022431AC
	movne r1, #0
	strneb r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
_0223B10C:
	ldr r0, _0223B148 ; =0x027FFFA8
	ldrh r0, [r0]
	and r0, r0, #0x8000
	movs r0, r0, asr #0xf
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	bl PM_SetLCDPower
	cmp r0, #0
	ldrne r0, _0223B144 ; =0x022431AC
	movne r1, #1
	strneb r1, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223B144: .word 0x022431AC
_0223B148: .word 0x027FFFA8

	arm_func_start MOD13_0223B14C
MOD13_0223B14C: ; 0x0223B14C
	ldr r1, _0223B190 ; =0x022431B4
	ldr r3, [r1]
	ldrb r1, [r3, #0x38]
	mov r1, r1, lsl #0x1f
	movs r1, r1, lsr #0x1f
	ldrneh r2, [r3, #0x28]
	ldrneh r1, [r3, #0x2a]
	strneh r2, [r0]
	strneh r1, [r0, #2]
	movne r0, #1
	bxne lr
	ldrh r2, [r3, #0x2c]
	ldrh r1, [r3, #0x2e]
	strh r2, [r0]
	strh r1, [r0, #2]
	mov r0, #0
	bx lr
	.align 2, 0
_0223B190: .word 0x022431B4

	arm_func_start MOD13_0223B194
MOD13_0223B194: ; 0x0223B194
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldrh r1, [r0]
	strh r1, [sp]
	ldrh r1, [r0, #2]
	strh r1, [sp, #2]
	ldrh r2, [r0]
	ldrh r1, [r0, #4]
	add r1, r2, r1
	strh r1, [sp, #4]
	ldrh r2, [r0, #2]
	ldrh r1, [r0, #6]
	add r0, sp, #0
	add r1, r2, r1
	strh r1, [sp, #6]
	bl MOD13_0223B2B4
	add sp, sp, #0xc
	ldmia sp!, {pc}

	arm_func_start MOD13_0223B1DC
MOD13_0223B1DC: ; 0x0223B1DC
	ldr r1, _0223B244 ; =0x022431B4
	ldr r3, [r1]
	ldrb r1, [r3, #0x38]
	mov r1, r1, lsl #0x1c
	movs r1, r1, lsr #0x1f
	moveq r0, #0
	bxeq lr
	ldrh r2, [r3, #0x28]
	ldrh r1, [r0]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r1, [r0, #4]
	cmp r1, r2
	movlo r0, #0
	bxlo lr
	ldrh r2, [r3, #0x2a]
	ldrh r1, [r0, #2]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r0, [r0, #6]
	cmp r0, r2
	movhs r0, #1
	movlo r0, #0
	bx lr
	.align 2, 0
_0223B244: .word 0x022431B4

	arm_func_start MOD13_0223B248
MOD13_0223B248: ; 0x0223B248
	ldr r1, _0223B2B0 ; =0x022431B4
	ldr r3, [r1]
	ldrb r1, [r3, #0x38]
	mov r1, r1, lsl #0x1d
	movs r1, r1, lsr #0x1f
	moveq r0, #0
	bxeq lr
	ldrh r2, [r3, #0x28]
	ldrh r1, [r0]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r1, [r0, #4]
	cmp r1, r2
	movlo r0, #0
	bxlo lr
	ldrh r2, [r3, #0x2a]
	ldrh r1, [r0, #2]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r0, [r0, #6]
	cmp r0, r2
	movhs r0, #1
	movlo r0, #0
	bx lr
	.align 2, 0
_0223B2B0: .word 0x022431B4

	arm_func_start MOD13_0223B2B4
MOD13_0223B2B4: ; 0x0223B2B4
	ldr r1, _0223B31C ; =0x022431B4
	ldr r3, [r1]
	ldrb r1, [r3, #0x38]
	mov r1, r1, lsl #0x1e
	movs r1, r1, lsr #0x1f
	moveq r0, #0
	bxeq lr
	ldrh r2, [r3, #0x28]
	ldrh r1, [r0]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r1, [r0, #4]
	cmp r1, r2
	movlo r0, #0
	bxlo lr
	ldrh r2, [r3, #0x2a]
	ldrh r1, [r0, #2]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r0, [r0, #6]
	cmp r0, r2
	movhs r0, #1
	movlo r0, #0
	bx lr
	.align 2, 0
_0223B31C: .word 0x022431B4

	arm_func_start MOD13_0223B320
MOD13_0223B320: ; 0x0223B320
	ldr r1, _0223B388 ; =0x022431B4
	ldr r3, [r1]
	ldrb r1, [r3, #0x38]
	mov r1, r1, lsl #0x1f
	movs r1, r1, lsr #0x1f
	moveq r0, #0
	bxeq lr
	ldrh r2, [r3, #0x28]
	ldrh r1, [r0]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r1, [r0, #4]
	cmp r1, r2
	movlo r0, #0
	bxlo lr
	ldrh r2, [r3, #0x2a]
	ldrh r1, [r0, #2]
	cmp r1, r2
	movhi r0, #0
	bxhi lr
	ldrh r0, [r0, #6]
	cmp r0, r2
	movhs r0, #1
	movlo r0, #0
	bx lr
	.align 2, 0
_0223B388: .word 0x022431B4

	arm_func_start MOD13_0223B38C
MOD13_0223B38C: ; 0x0223B38C
	ldr r1, _0223B3AC ; =0x022431B4
	ldr r1, [r1]
	ldrh r1, [r1, #0x36]
	and r1, r0, r1
	cmp r0, r1
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_0223B3AC: .word 0x022431B4

	arm_func_start MOD13_0223B3B0
MOD13_0223B3B0: ; 0x0223B3B0
	ldr r1, _0223B3D0 ; =0x022431B4
	ldr r1, [r1]
	ldrh r1, [r1, #0x34]
	and r1, r0, r1
	cmp r0, r1
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_0223B3D0: .word 0x022431B4

	arm_func_start MOD13_0223B3D4
MOD13_0223B3D4: ; 0x0223B3D4
	ldr r1, _0223B3F4 ; =0x022431B4
	ldr r1, [r1]
	ldrh r1, [r1, #0x32]
	and r1, r0, r1
	cmp r0, r1
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_0223B3F4: .word 0x022431B4

	arm_func_start MOD13_0223B3F8
MOD13_0223B3F8: ; 0x0223B3F8
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r0, _0223B598 ; =0x022431B4
	mov r4, #0
	ldr r0, [r0]
	ldrb r0, [r0, #0x38]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	movne r6, #1
	moveq r6, #0
	bl TP_GetLatestIndexInAuto
	ldr r7, _0223B598 ; =0x022431B4
	mov r5, r4
	ldr r3, [r7]
	mov r8, #5
	ldrh r2, [r3, #0x28]
	ldrh r1, [r3, #0x2a]
	strh r2, [r3, #0x2c]
	strh r1, [r3, #0x2e]
_0223B444:
	ldr r1, [r7]
	add r1, r1, r0, lsl #3
	ldrh r2, [r1, #4]
	cmp r2, #1
	bne _0223B48C
	ldrh r2, [r1, #6]
	cmp r2, #0
	bne _0223B48C
	add r0, sp, #0
	mov r4, #1
	bl TP_GetCalibratedPoint
	ldr r1, _0223B598 ; =0x022431B4
	ldrh r0, [sp]
	ldr r2, [r1]
	ldrh r1, [sp, #2]
	add r2, r2, #0x28
	bl MOD13_0223ABC0
	b _0223B4A4
_0223B48C:
	mov r1, r8
	add r5, r5, #1
	add r0, r0, #4
	bl FX_ModS32
	cmp r5, #4
	blt _0223B444
_0223B4A4:
	ldr r1, _0223B598 ; =0x022431B4
	eor r7, r4, r6
	ldr r5, [r1]
	and r0, r4, r7
	ldrb r3, [r5, #0x38]
	and r2, r0, #0xff
	and r0, r6, r7
	bic r3, r3, #2
	and r2, r2, #1
	orr r2, r3, r2, lsl #1
	strb r2, [r5, #0x38]
	ldr r5, [r1]
	and r0, r0, #0xff
	ldrb r3, [r5, #0x38]
	and r2, r0, #1
	cmp r4, #0
	bic r3, r3, #8
	orr r2, r3, r2, lsl #3
	strb r2, [r5, #0x38]
	ldr r3, [r1]
	and r0, r4, #1
	ldrb r2, [r3, #0x38]
	addeq sp, sp, #8
	bic r2, r2, #1
	orr r0, r2, r0
	strb r0, [r3, #0x38]
	ldr r3, [r1]
	moveq r1, #0
	ldrb r2, [r3, #0x38]
	mov r0, r2, lsl #0x1e
	mov r0, r0, lsr #0x1f
	bic r2, r2, #4
	and r0, r0, #1
	orr r0, r2, r0, lsl #2
	strb r0, [r3, #0x38]
	ldreq r0, _0223B59C ; =0x022431B0
	streqb r1, [r0]
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r0, _0223B59C ; =0x022431B0
	ldrb r2, [r0]
	add r2, r2, #1
	strb r2, [r0]
	ldrb r2, [r0]
	cmp r2, #0x28
	ldreq r1, [r1]
	addeq sp, sp, #8
	ldreqb r0, [r1, #0x38]
	orreq r0, r0, #4
	streqb r0, [r1, #0x38]
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r2, #0x2f
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r3, [r1]
	mov r1, #0x28
	ldrb r2, [r3, #0x38]
	orr r2, r2, #4
	strb r2, [r3, #0x38]
	strb r1, [r0]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0223B598: .word 0x022431B4
_0223B59C: .word 0x022431B0

	arm_func_start MOD13_0223B5A0
MOD13_0223B5A0: ; 0x0223B5A0
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r1, _0223B694 ; =0x04000130
	ldr r0, _0223B698 ; =0x027FFFA8
	ldrh r2, [r1]
	ldrh r1, [r0]
	ldr r4, _0223B69C ; =0x022431B4
	ldr r0, _0223B6A0 ; =0x00002FFF
	ldr r5, [r4]
	orr r1, r2, r1
	eor r1, r1, r0
	and r0, r1, r0
	mov r0, r0, lsl #0x10
	ldrh r1, [r5, #0x30]
	mov r3, r0, lsr #0x10
	ldr ip, _0223B6A4 ; =0x022431B8
	eor r1, r1, r0, lsr #16
	and r1, r1, r0, lsr #16
	strh r1, [r5, #0x32]
	ldrh r2, [r5, #0x30]
	ldr r1, [r4]
	mov lr, #0
	eor r0, r2, r0, lsr #16
	and r0, r2, r0
	strh r0, [r1, #0x36]
	ldr r0, [r4]
	strh r3, [r0, #0x30]
	ldr r1, [r4]
	ldrh r0, [r1, #0x32]
	strh r0, [r1, #0x34]
	mov r0, lr
	mov r5, #0x28
	mov r2, #1
_0223B624:
	mov r1, r2, lsl lr
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	ands r6, r3, r1
	streqb r0, [ip]
	beq _0223B67C
	ldrb r6, [ip]
	add r6, r6, #1
	strb r6, [ip]
	ldrb r6, [ip]
	cmp r6, #0x28
	ldreq r7, [r4]
	ldreqh r6, [r7, #0x34]
	orreq r1, r6, r1
	streqh r1, [r7, #0x34]
	beq _0223B67C
	cmp r6, #0x2f
	ldreq r7, [r4]
	ldreqh r6, [r7, #0x34]
	orreq r1, r6, r1
	streqh r1, [r7, #0x34]
	streqb r5, [ip]
_0223B67C:
	add lr, lr, #1
	cmp lr, #0xe
	add ip, ip, #1
	blt _0223B624
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0223B694: .word 0x04000130
_0223B698: .word 0x027FFFA8
_0223B69C: .word 0x022431B4
_0223B6A0: .word 0x00002FFF
_0223B6A4: .word 0x022431B8

	arm_func_start MOD13_0223B6A8
MOD13_0223B6A8: ; 0x0223B6A8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD13_0223B5A0
	bl MOD13_0223B3F8
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0223B6C0
MOD13_0223B6C0: ; 0x0223B6C0
	stmdb sp!, {r4, lr}
	mov r4, #4
_0223B6C8:
	bl TP_RequestAutoSamplingStopAsync
	mov r0, r4
	bl TP_WaitBusy
	mov r0, r4
	bl TP_CheckError
	cmp r0, #0
	bne _0223B6C8
	ldr r0, _0223B6F0 ; =0x022431B4
	bl MOD13_0223AF90
	ldmia sp!, {r4, pc}
	.align 2, 0
_0223B6F0: .word 0x022431B4

	arm_func_start MOD13_0223B6F4
MOD13_0223B6F4: ; 0x0223B6F4
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r0, #0x3a
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r1, _0223B76C ; =0x022431B4
	str r0, [r1]
	add r0, sp, #0
	bl TP_GetUserInfo
	cmp r0, #0
	bne _0223B724
	bl OS_Terminate
_0223B724:
	add r0, sp, #0
	bl TP_SetCalibrateParam
	ldr r1, _0223B76C ; =0x022431B4
	mov r0, #0
	ldr r2, [r1]
	mov r1, #4
	mov r3, #5
	bl TP_RequestAutoSamplingStartAsync
	mov r0, #2
	bl TP_WaitBusy
	mov r0, #2
	bl TP_CheckError
	cmp r0, #0
	beq _0223B760
	bl OS_Terminate
_0223B760:
	bl MOD13_0223B6A8
	add sp, sp, #0xc
	ldmia sp!, {pc}
	.align 2, 0
_0223B76C: .word 0x022431B4

	arm_func_start MOD13_0223B770
MOD13_0223B770: ; 0x0223B770
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #1
	bl MOD13_0223C1E0
	ldr r0, _0223B79C ; =0x027E0000
	add r0, r0, #0x3000
	ldr r1, [r0, #0xff8]
	orr r1, r1, #1
	str r1, [r0, #0xff8]
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223B79C: .word 0x027E0000

	arm_func_start MOD13_0223B7A0
MOD13_0223B7A0: ; 0x0223B7A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _0223B7DC ; =0x04000208
	mov r1, #0
	ldrh r0, [r2]
	ldr r0, _0223B7E0 ; =0x022431CC
	strh r1, [r2]
	ldr r0, [r0]
	bl OS_SetIrqMask
	ldr r1, _0223B7E4 ; =0x022431C8
	mov r0, #1
	ldr r1, [r1]
	bl OS_SetIrqFunction
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223B7DC: .word 0x04000208
_0223B7E0: .word 0x022431CC
_0223B7E4: .word 0x022431C8

	arm_func_start MOD13_0223B7E8
MOD13_0223B7E8: ; 0x0223B7E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223B850 ; =0x04000210
	ldr r1, _0223B854 ; =0x022431CC
	ldr r2, [r0]
	ldr r0, _0223B858 ; =0x00040018
	str r2, [r1]
	bl OS_SetIrqMask
	mov r0, #1
	bl OS_EnableIrqMask
	mov r0, #1
	bl OS_GetIrqFunction
	ldr r2, _0223B85C ; =0x022431C8
	ldr r1, _0223B860 ; =MOD13_0223B770
	str r0, [r2]
	mov r0, #1
	bl OS_SetIrqFunction
	mov r0, #1
	bl OS_ResetRequestIrqMask
	ldr r2, _0223B864 ; =0x04000208
	mov r0, #1
	ldrh r1, [r2]
	strh r0, [r2]
	bl OS_EnableInterrupts
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223B850: .word 0x04000210
_0223B854: .word 0x022431CC
_0223B858: .word 0x00040018
_0223B85C: .word 0x022431C8
_0223B860: .word MOD13_0223B770
_0223B864: .word 0x04000208

	arm_func_start MOD13_0223B868
MOD13_0223B868: ; 0x0223B868
	ldr ip, _0223B874 ; =MOD13_0223B888
	ldr r0, [r0, #4]
	bx ip
	.align 2, 0
_0223B874: .word MOD13_0223B888

	arm_func_start MOD13_0223B878
MOD13_0223B878: ; 0x0223B878
	ldr ip, _0223B884 ; =MOD13_0223B888
	add r0, r0, #8
	bx ip
	.align 2, 0
_0223B884: .word MOD13_0223B888

	arm_func_start MOD13_0223B888
MOD13_0223B888: ; 0x0223B888
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r0, #1
	mov r4, r1
	bl OS_DisableIrqMask
	ldr r1, [r5]
	str r4, [r1, #4]
	ldr r1, [r5]
	str r1, [r4]
	str r5, [r4, #4]
	str r4, [r5]
	bl OS_EnableIrqMask
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}

	arm_func_start MOD13_0223B8C4
MOD13_0223B8C4: ; 0x0223B8C4
	stmdb sp!, {r4, lr}
	mov r4, r0
	mov r0, #1
	bl OS_DisableIrqMask
	ldr r3, [r4, #4]
	ldr r2, [r4]
	mov r1, #0
	str r3, [r2, #4]
	ldr r3, [r4]
	ldr r2, [r4, #4]
	str r3, [r2]
	str r1, [r4, #4]
	ldr r1, [r4, #4]
	str r1, [r4]
	bl OS_EnableIrqMask
	ldmia sp!, {r4, pc}

	arm_func_start MOD13_0223B904
MOD13_0223B904: ; 0x0223B904
	stmdb sp!, {r0, r1, r2, r3}
	stmdb sp!, {lr}
	sub sp, sp, #4
	add r0, sp, #8
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start MOD13_0223B928
MOD13_0223B928: ; 0x0223B928
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0x10
	mov r1, #4
	bl MOD13_0223B004
	mov r2, #0
	str r2, [r0]
	add r1, r0, #8
	str r1, [r0, #4]
	str r0, [r0, #8]
	str r2, [r0, #0xc]
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0223B95C
MOD13_0223B95C: ; 0x0223B95C
	ldr r2, _0223B970 ; =0x022431D0
	ldr r2, [r2]
	add r0, r2, r0, lsl #10
	add r0, r0, r1, lsl #3
	bx lr
	.align 2, 0
_0223B970: .word 0x022431D0

	arm_func_start MOD13_0223B974
MOD13_0223B974: ; 0x0223B974
	mov r1, r0
	ldr r3, [r1]
	ldr r0, _0223B9B4 ; =0xC1FFFCFF
	ldr r2, _0223B9B8 ; =0x022431D0
	and r0, r3, r0
	orr r0, r0, #0x200
	str r0, [r1]
	ldr r2, [r2]
	mov r3, #0
	add r0, r2, #0x400
	cmp r1, r0
	movhs r3, #1
	add r0, r2, r3, lsl #2
	ldr ip, _0223B9BC ; =MOD13_02239FD0
	ldr r0, [r0, #0x800]
	bx ip
	.align 2, 0
_0223B9B4: .word 0xC1FFFCFF
_0223B9B8: .word 0x022431D0
_0223B9BC: .word MOD13_02239FD0

	arm_func_start MOD13_0223B9C0
MOD13_0223B9C0: ; 0x0223B9C0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _0223BA00 ; =0x022431D0
	mov r5, r1
	ldr r1, [r2]
	add r0, r1, r0, lsl #2
	ldr r0, [r0, #0x800]
	bl MOD13_02239F78
	mov r4, r0
	mov r0, r5
	mov r1, r4
	mov r2, #8
	bl MIi_CpuCopy32
	mov r0, r4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223BA00: .word 0x022431D0

	arm_func_start MOD13_0223BA04
MOD13_0223BA04: ; 0x0223BA04
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _0223BA30 ; =0x022431D0
	mov r0, #1
	ldr r1, [r1]
	ldr r1, [r1, #0x808]
	bl MOD13_0223C104
	ldr r0, _0223BA30 ; =0x022431D0
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223BA30: .word 0x022431D0

	arm_func_start MOD13_0223BA34
MOD13_0223BA34: ; 0x0223BA34
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223BA80 ; =0x022431D0
	mov r1, #0x800
	ldr r0, [r0]
	bl DC_FlushRange
	ldr r0, _0223BA80 ; =0x022431D0
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x400
	bl GX_LoadOAM
	ldr r0, _0223BA80 ; =0x022431D0
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x400
	add r0, r0, #0x400
	bl GXS_LoadOAM
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223BA80: .word 0x022431D0

	arm_func_start MOD13_0223BA84
MOD13_0223BA84: ; 0x0223BA84
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r0, _0223BB14 ; =0x0000080C
	mov r1, #4
	bl MOD13_0223B004
	mov r1, r0
	ldr r3, _0223BB18 ; =0x022431D0
	mov r0, #0x200
	mov r2, #0x800
	str r1, [r3]
	bl MIi_CpuClearFast
	mov r6, #0
	mov r5, r6
	ldr r7, _0223BB18 ; =0x022431D0
	mov r4, #0x40
	mov r8, #8
_0223BAC0:
	ldr r1, [r7]
	mov r0, r4
	mov r2, r8
	add r1, r1, r5
	bl MOD13_0223A054
	ldr r1, [r7]
	add r5, r5, #0x400
	add r1, r1, r6, lsl #2
	add r6, r6, #1
	str r0, [r1, #0x800]
	cmp r6, #2
	blt _0223BAC0
	ldr r1, _0223BB1C ; =MOD13_0223BA34
	mov r0, #1
	mov r2, #0
	mov r3, #0xc8
	bl MOD13_0223C1C4
	ldr r1, _0223BB18 ; =0x022431D0
	ldr r1, [r1]
	str r0, [r1, #0x808]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0223BB14: .word 0x0000080C
_0223BB18: .word 0x022431D0
_0223BB1C: .word MOD13_0223BA34

	arm_func_start MOD13_0223BB20
MOD13_0223BB20: ; 0x0223BB20
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r4, #0
	bl MOD13_0223B8C4
	ldr r0, _0223BB64 ; =0x022431D4
	ldr r1, [r0]
	add r0, r1, #0x1a0
	cmp r5, r0
	movhs r4, #1
	mov r0, #0x1a0
	mla r0, r4, r0, r1
	ldr r0, [r0, #0x19c]
	mov r1, r5
	bl MOD13_02239FD0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223BB64: .word 0x022431D4

	arm_func_start MOD13_0223BB68
MOD13_0223BB68: ; 0x0223BB68
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	mov r6, r0
	mov r0, #0x1a0
	mul r7, r6, r0
	ldr r0, _0223BCE0 ; =0x022431D4
	mov r4, r1
	ldr r0, [r0]
	mov sl, r2
	add r0, r0, r7
	ldr r0, [r0, #0x19c]
	mov r5, r3
	bl MOD13_02239F78
	add r1, r4, #3
	bic r1, r1, #3
	mov r4, r0
	mov r8, r1, asr #2
	mov r0, #1
	strh r8, [r4, #0xa]
	bl OS_DisableIrqMask
	mov sb, r0
	cmp sl, #0
	beq _0223BC44
	ldr r1, _0223BCE0 ; =0x022431D4
	mov r0, #0x1a0
	ldr r1, [r1]
	mla r0, r6, r0, r1
	add r6, r0, #0x180
	add r0, r0, #0x18c
	cmp r6, r0
	beq _0223BC24
	add r0, r1, r7
	add r1, r0, #0x18c
_0223BBE8:
	ldr r0, [r6, #4]
	ldrh sl, [r6, #8]
	ldrh r3, [r6, #0xa]
	ldrh r2, [r0, #8]
	add sl, sl, r3
	add r3, sl, r8
	cmp r3, r2
	bgt _0223BC18
	mov r1, r4
	strh sl, [r4, #8]
	bl MOD13_0223B888
	b _0223BC24
_0223BC18:
	mov r6, r0
	cmp r0, r1
	bne _0223BBE8
_0223BC24:
	ldr r0, _0223BCE0 ; =0x022431D4
	ldr r0, [r0]
	add r0, r0, r7
	add r0, r0, #0x18c
	cmp r6, r0
	bne _0223BCC8
	bl OS_Terminate
	b _0223BCC8
_0223BC44:
	ldr r1, _0223BCE0 ; =0x022431D4
	mov r0, #0x1a0
	ldr r1, [r1]
	mla r0, r6, r0, r1
	add r6, r0, #0x18c
	add r0, r0, #0x180
	cmp r6, r0
	beq _0223BCAC
	add r0, r1, r7
	add r0, r0, #0x180
_0223BC6C:
	ldr sl, [r6]
	ldrh r3, [r6, #8]
	ldrh r2, [sl, #8]
	ldrh r1, [sl, #0xa]
	sub r3, r3, r8
	add r1, r2, r1
	cmp r3, r1
	blt _0223BCA0
	mov r0, r6
	mov r1, r4
	strh r3, [r4, #8]
	bl MOD13_0223B888
	b _0223BCAC
_0223BCA0:
	mov r6, sl
	cmp sl, r0
	bne _0223BC6C
_0223BCAC:
	ldr r0, _0223BCE0 ; =0x022431D4
	ldr r0, [r0]
	add r0, r0, r7
	add r0, r0, #0x180
	cmp r6, r0
	bne _0223BCC8
	bl OS_Terminate
_0223BCC8:
	ldrh r1, [r4, #8]
	mov r0, sb
	str r1, [r5]
	bl OS_EnableIrqMask
	mov r0, r4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_0223BCE0: .word 0x022431D4

	arm_func_start MOD13_0223BCE4
MOD13_0223BCE4: ; 0x0223BCE4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	mov r0, #0x340
	mov r1, #4
	bl MOD13_0223AFE0
	ldr r4, _0223BDA0 ; =0x022431D4
	mov sl, #0
	mov sb, sl
	str r0, [r4]
	mov r8, #0x20
	mov r7, #0xc
	mov r6, #0x300
	mov r5, #0x400
_0223BD14:
	ldr r1, [r4]
	mov r0, r8
	mov r2, r7
	add r1, r1, sb
	bl MOD13_0223A054
	ldr r1, [r4]
	add r1, r1, sb
	str r0, [r1, #0x19c]
	bl MOD13_0223B928
	ldr r1, [r4]
	add r1, r1, sb
	str r0, [r1, #0x198]
	ldr r0, [r4]
	add r0, r0, sb
	add r0, r0, #0x100
	strh r6, [r0, #0x88]
	ldr r0, [r4]
	add r0, r0, sb
	add r0, r0, #0x100
	strh r5, [r0, #0x94]
	ldr r0, [r4]
	add r1, r0, sb
	ldr r0, [r1, #0x198]
	add r1, r1, #0x180
	bl MOD13_0223B868
	ldr r0, [r4]
	add r1, r0, sb
	ldr r0, [r1, #0x198]
	add r1, r1, #0x18c
	bl MOD13_0223B878
	add sl, sl, #1
	cmp sl, #2
	add sb, sb, #0x1a0
	blt _0223BD14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_0223BDA0: .word 0x022431D4

	arm_func_start MOD13_0223BDA4
MOD13_0223BDA4: ; 0x0223BDA4
	cmp r1, #0
	mov r3, #0
	ble _0223BDC8
_0223BDB0:
	ldrb r2, [r0, r3]
	cmp r2, #0
	beq _0223BDC8
	add r3, r3, #1
	cmp r3, r1
	blt _0223BDB0
_0223BDC8:
	mov r0, r3
	bx lr

	arm_func_start MOD13_0223BDD0
MOD13_0223BDD0: ; 0x0223BDD0
	ldr ip, _0223BDDC ; =0x020D4CAC
	mov r0, #1
	bx ip
	.align 2, 0
_0223BDDC: .word 0x020D4CAC

	arm_func_start MOD13_0223BDE0
MOD13_0223BDE0: ; 0x0223BDE0
	stmdb sp!, {lr}
	sub sp, sp, #4
	add r0, sp, #0
	bl PM_GetLEDPattern
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, [sp]
	cmp r0, #0xf
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0xf
	bl PMi_SendLEDPatternCommand
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0223BE1C
MOD13_0223BE1C: ; 0x0223BE1C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _0223BE98 ; =0x000001F3
	bl GX_SetBankForLCDC
	mov r0, #0
	mov r1, #0x6800000
	mov r2, #0x40000
	bl MIi_CpuClearFast
	ldr r1, _0223BE9C ; =0x06880000
	mov r0, #0
	mov r2, #0x24000
	bl MIi_CpuClearFast
	bl GX_DisableBankForLCDC
	mov r0, #0x200
	mov r1, #0x7000000
	mov r2, #0x400
	bl MIi_CpuClearFast
	mov r0, #0
	mov r1, #0x5000000
	mov r2, #0x400
	bl MIi_CpuClearFast
	mov r0, #0x200
	ldr r1, _0223BEA0 ; =0x07000400
	mov r2, #0x400
	bl MIi_CpuClearFast
	mov r0, #0
	ldr r1, _0223BEA4 ; =0x05000400
	mov r2, #0x400
	bl MIi_CpuClearFast
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223BE98: .word 0x000001F3
_0223BE9C: .word 0x06880000
_0223BEA0: .word 0x07000400
_0223BEA4: .word 0x05000400

	arm_func_start MOD13_0223BEA8
MOD13_0223BEA8: ; 0x0223BEA8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl disableBankForX_
	bl GX_DisableBankForOBJExtPltt_2
	bl GX_DisableBankForSubBGExtPltt
	bl GX_DisableBankForSubOBJExtPltt_2
	bl MOD13_0223BE1C
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0]
	bl GX_SetBankForBG
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #4]
	bl GX_SetBankForOBJ
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #8]
	bl GX_SetBankForBGExtPltt
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0xc]
	bl GX_SetBankForOBJExtPltt
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x10]
	bl GX_SetBankForTex
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x14]
	bl GX_SetBankForTexPltt
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x18]
	bl GX_SetBankForClearImage
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x1c]
	bl GX_SetBankForSubBG
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x20]
	bl GX_SetBankForSubOBJ
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x24]
	bl GX_SetBankForSubBGExtPltt
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x28]
	bl GX_SetBankForSubOBJExtPltt
	ldr r0, _0223BFB8 ; =0x022431D8
	ldr r0, [r0, #0x30]
	bl GX_SetBankForLCDC
	mov r2, #0
	ldr r1, _0223BFBC ; =0x04000050
	ldr r0, _0223BFC0 ; =0x04001050
	strh r2, [r1]
	strh r2, [r0]
	ldr r1, _0223BFC4 ; =0x04000010
	ldr r0, _0223BFC8 ; =0x04000014
	str r2, [r1]
	str r2, [r0]
	ldr r1, _0223BFCC ; =0x04000018
	ldr r0, _0223BFD0 ; =0x0400001C
	str r2, [r1]
	str r2, [r0]
	ldr r1, _0223BFD4 ; =0x04001010
	ldr r0, _0223BFD8 ; =0x04001014
	str r2, [r1]
	str r2, [r0]
	ldr r1, _0223BFDC ; =0x04001018
	ldr r0, _0223BFE0 ; =0x0400101C
	str r2, [r1]
	str r2, [r0]
	mov r0, #1
	bl PM_SetLCDPower
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223BFB8: .word 0x022431D8
_0223BFBC: .word 0x04000050
_0223BFC0: .word 0x04001050
_0223BFC4: .word 0x04000010
_0223BFC8: .word 0x04000014
_0223BFCC: .word 0x04000018
_0223BFD0: .word 0x0400001C
_0223BFD4: .word 0x04001010
_0223BFD8: .word 0x04001014
_0223BFDC: .word 0x04001018
_0223BFE0: .word 0x0400101C

	arm_func_start MOD13_0223BFE4
MOD13_0223BFE4: ; 0x0223BFE4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl disableBankForX_
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1]
	bl GX_DisableBankForOBJExtPltt_2
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #4]
	bl GX_DisableBankForBGExtPltt
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #8]
	bl GX_DisableBankForOBJExtPltt
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0xc]
	bl GX_DisableBankForTexPltt_2
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x10]
	bl GX_DisableBankForTexPltt
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x14]
	bl GX_DisableBankForClearImage
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x18]
	bl GX_DisableBankForSubBGExtPltt
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x1c]
	bl GX_DisableBankForSubOBJExtPltt_2
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x20]
	bl FUN_020C5E04
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x24]
	bl GX_DisableBankForSubOBJExtPltt
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x28]
	bl GX_DisableBankForARM7
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x2c]
	bl GX_DisableBankForLCDC
	ldr r1, _0223C09C ; =0x022431D8
	str r0, [r1, #0x30]
	ldr r0, [r1, #0x2c]
	bl GX_SetBankForARM7
	bl MOD13_0223BE1C
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_0223C09C: .word 0x022431D8

	arm_func_start MOD13_0223C0A0
MOD13_0223C0A0: ; 0x0223C0A0
	ldr r2, _0223C0B4 ; =0x0224320C
	ldr r2, [r2]
	add r0, r2, r0, lsl #6
	strb r1, [r0, #0x38]
	bx lr
	.align 2, 0
_0223C0B4: .word 0x0224320C

	arm_func_start MOD13_0223C0B8
MOD13_0223C0B8: ; 0x0223C0B8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r1
	ldrb r1, [r4, #0x11]
	mov r5, r0
	cmp r1, #0
	beq _0223C0DC
	add r0, r4, #0xc
	bl MOD13_0223AF90
_0223C0DC:
	mov r0, r4
	bl MOD13_0223B8C4
	ldr r0, _0223C100 ; =0x0224320C
	mov r1, r4
	ldr r0, [r0]
	ldr r0, [r0, r5, lsl #6]
	bl MOD13_02239FD0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223C100: .word 0x0224320C

	arm_func_start MOD13_0223C104
MOD13_0223C104: ; 0x0223C104
	ldr ip, _0223C10C ; =MOD13_0223C0B8
	bx ip
	.align 2, 0
_0223C10C: .word MOD13_0223C0B8

	arm_func_start MOD13_0223C110
MOD13_0223C110: ; 0x0223C110
	ldr r2, _0223C128 ; =0x0224320C
	ldr ip, _0223C12C ; =MOD13_02239FD0
	ldr r2, [r2]
	add r0, r2, r0, lsl #6
	ldr r0, [r0, #4]
	bx ip
	.align 2, 0
_0223C128: .word 0x0224320C
_0223C12C: .word MOD13_02239FD0

	arm_func_start MOD13_0223C130
MOD13_0223C130: ; 0x0223C130
	str r1, [r0, #8]
	bx lr

	arm_func_start MOD13_0223C138
MOD13_0223C138: ; 0x0223C138
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r4, _0223C1C0 ; =0x0224320C
	mov r7, r0
	ldr r0, [r4]
	mov r8, r1
	ldr r0, [r0, r7, lsl #6]
	mov r4, r2
	mov r6, r3
	bl MOD13_02239F78
	mov r5, r0
	str r8, [r5, #8]
	str r4, [r5, #0xc]
	ldrb r1, [sp, #0x18]
	strb r6, [r5, #0x10]
	mov r0, #1
	strb r1, [r5, #0x11]
	bl OS_DisableIrqMask
	ldr r1, _0223C1C0 ; =0x0224320C
	mov r4, r0
	ldr r0, [r1]
	add r0, r0, r7, lsl #6
	ldr r0, [r0, #0x10]
_0223C190:
	ldrb r1, [r0, #0x10]
	cmp r6, r1
	bhs _0223C1A8
	mov r1, r5
	bl MOD13_0223B888
	b _0223C1B0
_0223C1A8:
	ldr r0, [r0, #4]
	b _0223C190
_0223C1B0:
	mov r0, r4
	bl OS_EnableIrqMask
	mov r0, r5
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0223C1C0: .word 0x0224320C

	arm_func_start MOD13_0223C1C4
MOD13_0223C1C4: ; 0x0223C1C4
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov ip, #0
	str ip, [sp]
	bl MOD13_0223C138
	add sp, sp, #4
	ldmia sp!, {pc}

	arm_func_start MOD13_0223C1E0
MOD13_0223C1E0: ; 0x0223C1E0
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r7, _0223C2A4 ; =0x0224320C
	mov r6, r0
	ldr r0, [r7]
	mov r4, r6, lsl #6
	add r2, r0, r6, lsl #6
	ldrb r1, [r2, #0x38]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r5, [r2, #0x10]
	add r1, r2, #0x20
	cmp r5, r1
	beq _0223C244
_0223C21C:
	ldr r1, [r5, #0xc]
	ldr r2, [r5, #8]
	mov r0, r5
	blx r2
	ldr r0, [r7]
	ldr r5, [r5, #4]
	add r1, r0, r4
	add r1, r1, #0x20
	cmp r5, r1
	bne _0223C21C
_0223C244:
	add r1, r0, r6, lsl #6
	ldr r1, [r1, #0x34]
	mov r4, r6, lsl #6
	cmp r1, #0
	mov r5, #0
	addle sp, sp, #4
	ldmleia sp!, {r4, r5, r6, r7, pc}
	ldr r7, _0223C2A4 ; =0x0224320C
_0223C264:
	add r0, r4, r0
	ldr r0, [r0, #4]
	bl MOD13_02239F78
	movs r1, r0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	mov r0, r6
	bl MOD13_0223C0B8
	ldr r0, [r7]
	add r5, r5, #1
	add r1, r4, r0
	ldr r1, [r1, #0x34]
	cmp r5, r1
	blt _0223C264
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0223C2A4: .word 0x0224320C

	arm_func_start MOD13_0223C2A8
MOD13_0223C2A8: ; 0x0223C2A8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r4, _0223C2F0 ; =0x0224320C
	mov r5, #0
_0223C2B8:
	ldr r0, [r4]
	add r0, r0, r5, lsl #6
	ldr r0, [r0, #8]
	bl MOD13_0223B904
	ldr r0, [r4]
	ldr r0, [r0, r5, lsl #6]
	bl MOD13_0223A030
	add r5, r5, #1
	cmp r5, #2
	blt _0223C2B8
	ldr r0, _0223C2F0 ; =0x0224320C
	bl MOD13_0223AF90
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0223C2F0: .word 0x0224320C

	arm_func_start MOD13_0223C2F4
MOD13_0223C2F4: ; 0x0223C2F4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov r0, #0x80
	mov r1, #4
	bl MOD13_0223B004
	ldr r4, _0223C418 ; =0x0224320C
	mov sl, #0
	ldr sb, _0223C41C ; =0x0223F764
	mov r8, sl
	str r0, [r4]
	str sl, [sp]
	mov r7, #4
	mov fp, #0x14
	mov r6, #0xff
	mov r5, #1
_0223C330:
	ldr r0, [r4]
	ldrb r2, [sb]
	add r1, r0, sl, lsl #6
	mov r0, #0x14
	str r2, [r1, #0x34]
	ldrb r2, [sb]
	mov r1, r7
	mul r0, r2, r0
	bl MOD13_0223B004
	ldr r1, [r4]
	mov r2, fp
	add r1, r1, sl, lsl #6
	str r0, [r1, #0x3c]
	ldr r1, [r4]
	ldrb r0, [sb]
	add r1, r1, sl, lsl #6
	ldr r1, [r1, #0x3c]
	bl MOD13_0223A054
	ldr r1, [r4]
	str r0, [r1, sl, lsl #6]
	ldrb r0, [sb]
	bl MOD13_0223A094
	ldr r1, [r4]
	add r1, r1, sl, lsl #6
	str r0, [r1, #4]
	bl MOD13_0223B928
	ldr r1, [r4]
	add r1, r1, sl, lsl #6
	str r0, [r1, #8]
	ldr r0, [r4]
	add r1, r0, sl, lsl #6
	ldr r0, [sp]
	strb r0, [r1, #0x1c]
	ldr r0, [r4]
	add r0, r0, sl, lsl #6
	strb r6, [r0, #0x30]
	ldr r1, [r4]
	add r0, r1, sl, lsl #6
	add r1, r1, r8
	ldr r0, [r0, #8]
	add r1, r1, #0xc
	bl MOD13_0223B868
	ldr r1, [r4]
	add r0, r1, sl, lsl #6
	add r1, r1, r8
	ldr r0, [r0, #8]
	add r1, r1, #0x20
	bl MOD13_0223B878
	ldr r0, [r4]
	add sb, sb, #1
	add r0, r0, sl, lsl #6
	add sl, sl, #1
	strb r5, [r0, #0x38]
	add r8, r8, #0x40
	cmp sl, #2
	blt _0223C330
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_0223C418: .word 0x0224320C
_0223C41C: .word 0x0223F764

	.section .data
	; 0x0223C420
	.incbin "baserom.nds", 0x2237C0, 0x4620

	.section .bss
	; 0x02240A40
	.space 0x27E0
