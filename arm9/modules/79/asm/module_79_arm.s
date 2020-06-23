	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD79_0221248C
MOD79_0221248C: ; 0x0221248C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	movs r7, r0
	mov r6, r1
	mov r5, r2
	bne _022124B8
	ldr r0, _02212544 ; =0x02216858
	ldr r1, _02212548 ; =0x0221686C
	ldr r3, _0221254C ; =0x000001B7
	mov r2, #0
	bl __msl_assertion_failed
_022124B8:
	cmp r5, #0
	bne _022124D4
	ldr r0, _02212550 ; =0x0221687C
	ldr r1, _02212548 ; =0x0221686C
	mov r2, #0
	mov r3, #0x1b8
	bl __msl_assertion_failed
_022124D4:
	ldr r4, [r5]
	cmp r4, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r3, [r7, #0x10]
	ldr r0, [r7, #0xc]
	sub r0, r0, r3
	cmp r0, #0
	addle sp, sp, #4
	movle r0, #0
	ldmleia sp!, {r4, r5, r6, r7, pc}
	ldr r1, [r7, #4]
	cmp r4, r0
	movge r4, r0
	mov r0, r6
	mov r2, r4
	add r1, r1, r3
	bl memcpy
	mov r0, #0
	strb r0, [r6, r4]
	str r4, [r5]
	ldr r1, [r7, #0x10]
	mov r0, #1
	add r1, r1, r4
	str r1, [r7, #0x10]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02212544: .word 0x02216858
_02212548: .word MOD79_0221686C
_0221254C: .word 0x000001B7
_02212550: .word MOD79_0221687C
	arm_func_end MOD79_0221248C

	arm_func_start MOD79_02212554
MOD79_02212554: ; 0x02212554
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0xc
	mov r8, r0
	add r6, sp, #0
	add r5, sp, #4
	add r4, r8, #0x60
	mov r7, #0
	mvn sb, #0
_02212574:
	ldr r0, [r8, #0x48]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl MOD04_021EFF5C
	cmp r0, sb
	beq _0221259C
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _022125C4
_0221259C:
	mov r0, #1
	str r0, [r8, #0xfc]
	mov r0, #5
	str r0, [r8, #0x38]
	ldr r0, [r8, #0x48]
	bl MOD04_021EFB28
	str r0, [r8, #0x4c]
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_022125C4:
	ldr r0, [sp]
	cmp r0, #0
	addeq sp, sp, #0xc
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	ldr r3, [r8, #0x60]
	ldr r1, [r8, #0x54]
	ldr r2, [r8, #0x5c]
	mov r0, r8
	add r1, r1, r3
	sub r2, r2, r3
	bl MOD79_02212F68
	cmp r0, sb
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	ldr r1, [r4]
	add r0, r1, r0
	str r0, [r4]
	ldr r1, [r8, #0x60]
	ldr r0, [r8, #0x5c]
	cmp r1, r0
	blt _02212574
	mov r0, #1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	arm_func_end MOD79_02212554

	arm_func_start MOD79_0221262C
MOD79_0221262C: ; 0x0221262C
	stmdb sp!, {r4, lr}
	movs r4, r0
	bne _0221264C
	ldr r0, _02212664 ; =0x02216888
	ldr r1, _02212668 ; =0x0221686C
	mov r2, #0
	mov r3, #0x16c
	bl __msl_assertion_failed
_0221264C:
	mov r1, #0
	str r1, [r4, #0xc]
	str r1, [r4, #0x10]
	ldr r0, [r4, #4]
	strb r1, [r0]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02212664: .word MOD79_02216888
_02212668: .word MOD79_0221686C
	arm_func_end MOD79_0221262C

	arm_func_start MOD79_0221266C
MOD79_0221266C: ; 0x0221266C
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x10
	mov r2, r1
	mov r4, r0
	ldr r1, _022126A0 ; =0x02216890
	add r0, sp, #0
	bl sprintf
	add r1, sp, #0
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
	add sp, sp, #0x10
	ldmia sp!, {r4, pc}
	.align 2, 0
_022126A0: .word MOD79_02216890
	arm_func_end MOD79_0221266C

	arm_func_start MOD79_022126A4
MOD79_022126A4: ; 0x022126A4
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	movs r4, r0
	strb r1, [sp]
	bne _022126CC
	ldr r0, _022126F4 ; =0x02216888
	ldr r1, _022126F8 ; =0x0221686C
	ldr r3, _022126FC ; =0x00000131
	mov r2, #0
	bl __msl_assertion_failed
_022126CC:
	cmp r4, #0
	addeq sp, sp, #8
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	add r1, sp, #0
	mov r0, r4
	mov r2, #1
	bl MOD79_02212794
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022126F4: .word MOD79_02216888
_022126F8: .word MOD79_0221686C
_022126FC: .word 0x00000131
	arm_func_end MOD79_022126A4

	arm_func_start MOD79_02212700
MOD79_02212700: ; 0x02212700
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r2
	mov r2, #0
	mov r5, r0
	bl MOD79_02212794
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _0221278C ; =0x02216894
	mov r0, r5
	mov r2, #2
	bl MOD79_02212794
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	mov r0, r5
	mov r1, r4
	mov r2, #0
	bl MOD79_02212794
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _02212790 ; =0x02216898
	mov r0, r5
	mov r2, #2
	bl MOD79_02212794
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_0221278C: .word MOD79_02216894
_02212790: .word MOD79_02216898
	arm_func_end MOD79_02212700

	arm_func_start MOD79_02212794
MOD79_02212794: ; 0x02212794
	stmdb sp!, {r0, r1, r2, r3}
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	movs r7, r0
	mov r6, r1
	ldr r5, [r7]
	bne _022127C4
	ldr r0, _02212A40 ; =0x02216888
	ldr r1, _02212A44 ; =0x0221686C
	mov r2, #0
	mov r3, #0xb7
	bl __msl_assertion_failed
_022127C4:
	cmp r6, #0
	bne _022127E0
	ldr r0, _02212A48 ; =0x0221689C
	ldr r1, _02212A44 ; =0x0221686C
	mov r2, #0
	mov r3, #0xb8
	bl __msl_assertion_failed
_022127E0:
	ldr r0, [sp, #0x28]
	cmp r0, #0
	bge _02212800
	ldr r0, _02212A4C ; =0x022168A4
	ldr r1, _02212A44 ; =0x0221686C
	mov r2, #0
	mov r3, #0xb9
	bl __msl_assertion_failed
_02212800:
	cmp r7, #0
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	addeq sp, sp, #0x10
	bxeq lr
	cmp r6, #0
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x28]
	cmp r0, #0
	addlt sp, sp, #0xc
	movlt r0, #0
	ldmltia sp!, {r4, r5, r6, r7, lr}
	addlt sp, sp, #0x10
	bxlt lr
	cmp r0, #0
	bne _02212860
	mov r0, r6
	bl strlen
	str r0, [sp, #0x28]
_02212860:
	ldr r0, [r7, #0x20]
	cmp r0, #1
	bne _02212968
	ldr r0, [r5, #0x168]
	cmp r0, #0
	bne _0221288C
	ldr r0, _02212A50 ; =0x022168B4
	ldr r1, _02212A44 ; =0x0221686C
	mov r2, #0
	mov r3, #0xce
	bl __msl_assertion_failed
_0221288C:
	ldr r2, [r7, #8]
	ldr r1, [r7, #0xc]
	add r0, sp, #8
	sub r1, r2, r1
	str r1, [sp, #8]
	ldr r2, [r7, #4]
	ldr r1, [r7, #0xc]
	add r3, sp, #0x28
	add r1, r2, r1
	str r1, [sp]
	str r0, [sp, #4]
	ldr r4, [r5, #0x17c]
	mov r0, r5
	mov r2, r6
	add r1, r5, #0x164
	.word 0xE12FFF34
	mov r4, r0
	cmp r4, #2
	bne _0221294C
	ldr r0, [r7, #0x18]
	cmp r0, #0
	beq _02212910
	ldr r0, [r7]
	mov r1, #1
	str r1, [r0, #0xfc]
	ldr r0, [r7]
	mov r1, #2
	str r1, [r0, #0x38]
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, lr}
	add sp, sp, #0x10
	bx lr
_02212910:
	ldr r1, [r7, #0x14]
	mov r0, r7
	bl MOD79_02212CF0
	cmp r0, #0
	beq _0221295C
	ldr r0, [r7]
	mov r2, #1
	str r2, [r0, #0xfc]
	ldr r1, [r7]
	add sp, sp, #0xc
	str r2, [r1, #0x38]
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, lr}
	add sp, sp, #0x10
	bx lr
_0221294C:
	ldr r1, [r7, #0xc]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r7, #0xc]
_0221295C:
	cmp r4, #2
	beq _0221288C
	b _02212A2C
_02212968:
	ldr r2, [r7, #0xc]
	ldr r1, [sp, #0x28]
	ldr r0, [r7, #8]
	add r4, r2, r1
	cmp r4, r0
	blt _02212A00
_02212980:
	ldr r0, [r7, #0x18]
	cmp r0, #0
	beq _022129B8
	ldr r0, [r7]
	mov r1, #1
	str r1, [r0, #0xfc]
	ldr r0, [r7]
	mov r1, #2
	str r1, [r0, #0x38]
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, lr}
	add sp, sp, #0x10
	bx lr
_022129B8:
	ldr r1, [r7, #0x14]
	mov r0, r7
	bl MOD79_02212CF0
	cmp r0, #0
	bne _022129F4
	ldr r0, [r7]
	mov r2, #1
	str r2, [r0, #0xfc]
	ldr r1, [r7]
	add sp, sp, #0xc
	str r2, [r1, #0x38]
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, lr}
	add sp, sp, #0x10
	bx lr
_022129F4:
	ldr r0, [r7, #8]
	cmp r4, r0
	bge _02212980
_02212A00:
	ldr r3, [r7, #4]
	ldr r0, [r7, #0xc]
	ldr r2, [sp, #0x28]
	mov r1, r6
	add r0, r3, r0
	bl memcpy
	str r4, [r7, #0xc]
	ldr r1, [r7, #4]
	ldr r0, [r7, #0xc]
	mov r2, #0
	strb r2, [r1, r0]
_02212A2C:
	mov r0, #1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, lr}
	add sp, sp, #0x10
	bx lr
	.align 2, 0
_02212A40: .word MOD79_02216888
_02212A44: .word MOD79_0221686C
_02212A48: .word MOD79_0221689C
_02212A4C: .word MOD79_022168A4
_02212A50: .word MOD79_022168B4
	arm_func_end MOD79_02212794

	arm_func_start MOD79_02212A54
MOD79_02212A54: ; 0x02212A54
	stmdb sp!, {r4, lr}
	movs r4, r0
	bne _02212A74
	ldr r0, _02212AAC ; =0x02216888
	ldr r1, _02212AB0 ; =0x0221686C
	mov r2, #0
	mov r3, #0x9b
	bl __msl_assertion_failed
_02212A74:
	cmp r4, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #4]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, [r4, #0x1c]
	cmp r1, #0
	bne _02212A98
	bl MOD04_021DD82C
_02212A98:
	mov r0, r4
	mov r1, #0
	mov r2, #0x24
	bl memset
	ldmia sp!, {r4, pc}
	.align 2, 0
_02212AAC: .word MOD79_02216888
_02212AB0: .word MOD79_0221686C
	arm_func_end MOD79_02212A54

	arm_func_start MOD79_02212AB4
MOD79_02212AB4: ; 0x02212AB4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	movs r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bne _02212AE4
	ldr r0, _02212BB0 ; =0x022168F0
	ldr r1, _02212BB4 ; =0x0221686C
	mov r2, #0
	mov r3, #0x74
	bl __msl_assertion_failed
_02212AE4:
	cmp r6, #0
	bne _02212B00
	ldr r0, _02212BB8 ; =0x02216888
	ldr r1, _02212BB4 ; =0x0221686C
	mov r2, #0
	mov r3, #0x75
	bl __msl_assertion_failed
_02212B00:
	cmp r5, #0
	bne _02212B1C
	ldr r0, _02212BBC ; =0x022168FC
	ldr r1, _02212BB4 ; =0x0221686C
	mov r2, #0
	mov r3, #0x76
	bl __msl_assertion_failed
_02212B1C:
	cmp r4, #0
	bgt _02212B38
	ldr r0, _02212BC0 ; =0x02216908
	ldr r1, _02212BB4 ; =0x0221686C
	mov r2, #0
	mov r3, #0x77
	bl __msl_assertion_failed
_02212B38:
	cmp r7, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r6, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r5, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r4, #0
	addle sp, sp, #4
	movle r0, #0
	ldmleia sp!, {r4, r5, r6, r7, pc}
	str r7, [r6]
	str r5, [r6, #4]
	str r4, [r6, #8]
	mov r2, #0
	str r2, [r6, #0xc]
	str r2, [r6, #0x14]
	mov r0, #1
	str r0, [r6, #0x18]
	str r0, [r6, #0x1c]
	str r2, [r6, #0x20]
	ldr r1, [r6, #4]
	strb r2, [r1]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02212BB0: .word MOD79_022168F0
_02212BB4: .word MOD79_0221686C
_02212BB8: .word MOD79_02216888
_02212BBC: .word MOD79_022168FC
_02212BC0: .word MOD79_02216908
	arm_func_end MOD79_02212AB4

	arm_func_start MOD79_02212BC4
MOD79_02212BC4: ; 0x02212BC4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	movs r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bne _02212BF4
	ldr r0, _02212CDC ; =0x022168F0
	ldr r1, _02212CE0 ; =0x0221686C
	mov r2, #0
	mov r3, #0x43
	bl __msl_assertion_failed
_02212BF4:
	cmp r6, #0
	bne _02212C10
	ldr r0, _02212CE4 ; =0x02216888
	ldr r1, _02212CE0 ; =0x0221686C
	mov r2, #0
	mov r3, #0x44
	bl __msl_assertion_failed
_02212C10:
	cmp r5, #0
	bgt _02212C2C
	ldr r0, _02212CE8 ; =0x02216914
	ldr r1, _02212CE0 ; =0x0221686C
	mov r2, #0
	mov r3, #0x45
	bl __msl_assertion_failed
_02212C2C:
	cmp r4, #0
	bgt _02212C48
	ldr r0, _02212CEC ; =0x02216924
	ldr r1, _02212CE0 ; =0x0221686C
	mov r2, #0
	mov r3, #0x46
	bl __msl_assertion_failed
_02212C48:
	cmp r7, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r6, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r5, #0
	addle sp, sp, #4
	movle r0, #0
	ldmleia sp!, {r4, r5, r6, r7, pc}
	cmp r4, #0
	addle sp, sp, #4
	movle r0, #0
	ldmleia sp!, {r4, r5, r6, r7, pc}
	str r7, [r6]
	mov r2, #0
	str r2, [r6, #4]
	str r2, [r6, #8]
	str r2, [r6, #0xc]
	str r2, [r6, #0x10]
	str r4, [r6, #0x14]
	str r2, [r6, #0x18]
	str r2, [r6, #0x1c]
	mov r0, r6
	mov r1, r5
	str r2, [r6, #0x20]
	bl MOD79_02212CF0
	cmp r0, #0
	moveq r0, #0
	ldrne r0, [r6, #4]
	movne r1, #0
	strneb r1, [r0]
	movne r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02212CDC: .word MOD79_022168F0
_02212CE0: .word MOD79_0221686C
_02212CE4: .word MOD79_02216888
_02212CE8: .word MOD79_02216914
_02212CEC: .word MOD79_02216924
	arm_func_end MOD79_02212BC4

	arm_func_start MOD79_02212CF0
MOD79_02212CF0: ; 0x02212CF0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	movs r5, r0
	mov r4, r1
	bne _02212D18
	ldr r0, _02212D84 ; =0x02216888
	ldr r1, _02212D88 ; =0x0221686C
	mov r2, #0
	mov r3, #0x20
	bl __msl_assertion_failed
_02212D18:
	cmp r4, #0
	bgt _02212D34
	ldr r0, _02212D8C ; =0x02216924
	ldr r1, _02212D88 ; =0x0221686C
	mov r2, #0
	mov r3, #0x21
	bl __msl_assertion_failed
_02212D34:
	cmp r5, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	cmp r4, #0
	addle sp, sp, #4
	movle r0, #0
	ldmleia sp!, {r4, r5, pc}
	ldr r1, [r5, #8]
	ldr r0, [r5, #4]
	add r4, r1, r4
	mov r1, r4
	bl MOD04_021DD844
	cmp r0, #0
	moveq r0, #0
	strne r0, [r5, #4]
	strne r4, [r5, #8]
	movne r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02212D84: .word MOD79_02216888
_02212D88: .word MOD79_0221686C
_02212D8C: .word MOD79_02216924
	arm_func_end MOD79_02212CF0

	arm_func_start MOD79_02212D90
MOD79_02212D90: ; 0x02212D90
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	movs r4, r0
	bne _02212DB4
	ldr r0, _02212DF8 ; =0x02216938
	ldr r1, _02212DFC ; =0x02216944
	mov r2, #0
	mov r3, #0x5e
	bl __msl_assertion_failed
_02212DB4:
	ldr r0, [r4, #0x150]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #0x140]
	bl MOD04_021EF06C
	str r0, [sp]
	ldr r0, [r4, #0x44]
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x148]
	ldr r2, [r4, #0x14c]
	ldr r3, [r4, #0x144]
	ldr ip, [r4, #0x150]
	.word 0xE12FFF3C
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_02212DF8: .word MOD79_02216938
_02212DFC: .word MOD79_02216944
	arm_func_end MOD79_02212D90

	arm_func_start MOD79_02212E00
MOD79_02212E00: ; 0x02212E00
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	movs r6, r0
	mov r5, r1
	mov r4, r2
	bne _02212E2C
	ldr r0, _02212E70 ; =0x02216938
	ldr r1, _02212E74 ; =0x02216944
	mov r2, #0
	mov r3, #0x45
	bl __msl_assertion_failed
_02212E2C:
	ldr ip, [r6, #0x3c]
	cmp ip, #0
	addeq sp, sp, #0x10
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, [r6, #0x100]
	mov r2, r5
	str r0, [sp]
	ldr r0, [r6, #0x104]
	mov r3, r4
	str r0, [sp, #4]
	ldr r0, [r6, #0x44]
	str r0, [sp, #8]
	ldr r0, [r6, #4]
	ldr r1, [r6, #0x10]
	.word 0xE12FFF3C
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02212E70: .word MOD79_02216938
_02212E74: .word MOD79_02216944
	arm_func_end MOD79_02212E00

	arm_func_start MOD79_02212E78
MOD79_02212E78: ; 0x02212E78
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	movs r5, r0
	bne _02212E9C
	ldr r0, _02212EFC ; =0x02216938
	ldr r1, _02212F00 ; =0x02216944
	mov r2, #0
	mov r3, #0x1b
	bl __msl_assertion_failed
_02212E9C:
	ldr ip, [r5, #0x40]
	cmp ip, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, [r5, #0xc]
	cmp r0, #0
	movne r4, #0
	movne r3, r4
	ldreq r4, [r5, #0xc0]
	ldreq r3, [r5, #0x100]
	ldr r0, [r5, #0x44]
	mov r2, r4
	str r0, [sp]
	ldr r0, [r5, #4]
	ldr r1, [r5, #0x38]
	.word 0xE12FFF3C
	cmp r4, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	cmp r0, #0
	moveq r0, #1
	streq r0, [r5, #0xd8]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02212EFC: .word MOD79_02216938
_02212F00: .word MOD79_02216944
	arm_func_end MOD79_02212E78

	arm_func_start MOD79_02212F04
MOD79_02212F04: ; 0x02212F04
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	ldr r3, [r6, #0x5c]
	mov r5, r1
	mov r4, r2
	cmp r3, #0
	mov r3, #0
	bne _02212F48
	bl MOD79_02212F68
	mov r3, r0
	mvn r0, #0
	cmp r3, r0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r3, r4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, pc}
_02212F48:
	add r0, r6, #0x50
	add r1, r5, r3
	sub r2, r4, r3
	bl MOD79_02212794
	cmp r0, #0
	moveq r0, #0
	movne r0, #2
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD79_02212F04

	arm_func_start MOD79_02212F68
MOD79_02212F68: ; 0x02212F68
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #0x48]
	mov r3, #0
	bl MOD04_021EFC24
	mvn r1, #0
	cmp r0, r1
	bne _02212FD8
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	mvn r1, #5
	cmp r0, r1
	beq _02212FB4
	mvn r1, #0x19
	cmp r0, r1
	beq _02212FB4
	mvn r1, #0x4b
	cmp r0, r1
	bne _02212FBC
_02212FB4:
	mov r0, #0
	ldmia sp!, {r4, pc}
_02212FBC:
	mov r1, #1
	str r1, [r4, #0xfc]
	mov r1, #5
	str r1, [r4, #0x38]
	str r0, [r4, #0x4c]
	mvn r0, #0
	ldmia sp!, {r4, pc}
_02212FD8:
	ldr r1, [r4, #0x10]
	cmp r1, #4
	ldreq r1, [r4, #0x148]
	addeq r1, r1, r0
	streq r1, [r4, #0x148]
	ldmia sp!, {r4, pc}
	arm_func_end MOD79_02212F68

	arm_func_start MOD79_02212FF0
MOD79_02212FF0: ; 0x02212FF0
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r7, r0
	mov r5, r2
	ldr r2, [r5]
	ldr r0, [r7, #0x134]
	mov r6, r1
	cmp r0, #0
	sub r4, r2, #1
	beq _02213050
	bl MOD04_021F025C
	ldr r1, _02213230 ; =0x02216958
	ldr r2, [r7, #0x138]
	ldr r1, [r1]
	add r1, r2, r1
	cmp r0, r1
	addlo sp, sp, #4
	movlo r0, #1
	ldmloia sp!, {r4, r5, r6, r7, pc}
	ldr r1, _02213234 ; =0x0221695C
	str r0, [r7, #0x138]
	ldr r0, [r1]
	cmp r4, r0
	movge r4, r0
_02213050:
	ldr r1, [r7, #0x84]
	ldr r0, [r7, #0x80]
	cmp r1, r0
	bge _02213098
	mov r1, r6
	mov r2, r5
	add r0, r7, #0x74
	bl MOD79_0221248C
	ldr r1, [r7, #0x84]
	ldr r0, [r7, #0x80]
	add sp, sp, #4
	cmp r1, r0
	ldreq r0, [r7, #0xf8]
	streq r0, [r7, #0x80]
	ldreq r0, [r7, #0xf8]
	streq r0, [r7, #0x84]
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_02213098:
	ldr r0, [r7, #0x48]
	mov r1, r6
	mov r2, r4
	mov r3, #0
	bl MOD04_021EFC78
	mov r2, r0
	mvn r0, #0
	str r2, [sp]
	cmp r2, r0
	bne _0221311C
	ldr r0, [r7, #0x48]
	bl MOD04_021EFB28
	mvn r1, #5
	cmp r0, r1
	beq _022130EC
	mvn r1, #0x19
	cmp r0, r1
	beq _022130EC
	mvn r1, #0x4b
	cmp r0, r1
	bne _022130F8
_022130EC:
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, pc}
_022130F8:
	mov r2, #1
	str r2, [r7, #0xfc]
	mov r1, #5
	str r1, [r7, #0x38]
	str r0, [r7, #0x4c]
	add sp, sp, #4
	str r2, [r7, #0x130]
	mov r0, #3
	ldmia sp!, {r4, r5, r6, r7, pc}
_0221311C:
	cmp r2, #0
	moveq r0, #1
	streq r0, [r7, #0x130]
	addeq sp, sp, #4
	moveq r0, #2
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [r7, #0x168]
	cmp r0, #0
	beq _0221320C
	mov r1, r6
	add r0, r7, #0x98
	bl MOD79_02212794
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #3
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	mov r0, r7
	bl MOD79_02213238
	cmp r0, #0
	bne _02213188
	mov r0, #1
	str r0, [r7, #0xfc]
	mov r0, #0x11
	str r0, [r7, #0x38]
	add sp, sp, #4
	mov r0, #3
	ldmia sp!, {r4, r5, r6, r7, pc}
_02213188:
	ldr r1, [r7, #0x80]
	ldr r0, [r7, #0x84]
	sub r0, r1, r0
	cmp r0, #0
	movle r0, #0
	strleb r0, [r6]
	strle r0, [r5]
	addle sp, sp, #4
	movle r0, #1
	ldmleia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [r5]
	add r2, sp, #0
	sub r3, r0, #1
	mov r1, r6
	add r0, r7, #0x74
	str r3, [sp]
	bl MOD79_0221248C
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #3
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r1, [r7, #0x84]
	ldr r0, [r7, #0x80]
	cmp r1, r0
	ldreq r0, [r7, #0xf8]
	streq r0, [r7, #0x80]
	ldreq r0, [r7, #0xf8]
	streq r0, [r7, #0x84]
	ldr r2, [sp]
	cmp r2, #0
	addle sp, sp, #4
	movle r0, #1
	ldmleia sp!, {r4, r5, r6, r7, pc}
_0221320C:
	mov r0, #0
	strb r0, [r6, r2]
	ldr r1, [sp]
	str r1, [r5]
	ldr r1, [sp]
	cmp r1, #0
	movle r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02213230: .word MOD79_02216958
_02213234: .word MOD79_0221695C
	arm_func_end MOD79_02212FF0

	arm_func_start MOD79_02213238
MOD79_02213238: ; 0x02213238
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x14
	mov r1, #0
	mov r4, r0
	str r1, [sp, #8]
	str r1, [sp, #0xc]
	add r8, sp, #0xc
	add r6, sp, #8
	add r5, r4, #0x74
	add r7, r4, #0x164
_02213260:
	ldr ip, [r4, #0xa8]
	ldr r0, [r4, #0xa4]
	ldr r2, [r4, #0x9c]
	sub r0, r0, ip
	str r0, [sp, #8]
	ldr r3, [r4, #0x80]
	ldr r0, [r4, #0x7c]
	ldr r1, [r4, #0x78]
	sub r0, r0, r3
	str r0, [sp, #0xc]
	add r0, r1, r3
	str r0, [sp]
	str r8, [sp, #4]
	ldr sb, [r4, #0x180]
	mov r0, r4
	mov r1, r7
	mov r3, r6
	add r2, r2, ip
	.word 0xE12FFF39
	mov sb, r0
	cmp sb, #2
	bne _022132D4
	ldr r1, [r4, #0x88]
	mov r0, r5
	bl MOD79_02212CF0
	cmp r0, #0
	addeq sp, sp, #0x14
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
_022132D4:
	cmp sb, #2
	bne _022132E8
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _02213260
_022132E8:
	ldr r1, [r4, #0xa8]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r4, #0xa8]
	ldr r1, [r4, #0x80]
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x80]
	ldr r1, [r4, #0xa8]
	cmp r1, #0xff
	ble _02213348
	ldr r0, [r4, #0xa4]
	subs r5, r0, r1
	bne _0221332C
	add r0, r4, #0x98
	bl MOD79_0221262C
	b _02213348
_0221332C:
	ldr r0, [r4, #0x9c]
	mov r2, r5
	add r1, r0, r1
	bl memmove
	mov r0, #0
	str r0, [r4, #0xa8]
	str r5, [r4, #0xa4]
_02213348:
	cmp sb, #3
	addne sp, sp, #0x14
	movne r0, #1
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, pc}
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #0x11
	str r0, [r4, #0x38]
	mov r0, #0
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	arm_func_end MOD79_02213238

	arm_func_start MOD79_02213374
MOD79_02213374: ; 0x02213374
	bx lr
	arm_func_end MOD79_02213374

	arm_func_start MOD79_02213378
MOD79_02213378: ; 0x02213378
	bx lr
	arm_func_end MOD79_02213378

	arm_func_start MOD79_0221337C
MOD79_0221337C: ; 0x0221337C
	bx lr
	arm_func_end MOD79_0221337C

	arm_func_start MOD79_02213380
MOD79_02213380: ; 0x02213380
	bx lr
	arm_func_end MOD79_02213380

	arm_func_start MOD79_02213384
MOD79_02213384: ; 0x02213384
	stmdb sp!, {r4, r5, r6, lr}
	ldr r0, _02213400 ; =0x02217138
	ldr r0, [r0]
	cmp r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, _02213404 ; =MOD79_02213638
	bl MOD79_02213510
	ldr r5, _02213408 ; =0x0221712C
	mov r6, #0
	ldr r0, [r5]
	cmp r0, #0
	ble _022133D4
	ldr r4, _02213400 ; =0x02217138
_022133B8:
	ldr r0, [r4]
	ldr r0, [r0, r6, lsl #2]
	bl MOD04_021DD82C
	ldr r0, [r5]
	add r6, r6, #1
	cmp r6, r0
	blt _022133B8
_022133D4:
	ldr r0, _02213400 ; =0x02217138
	ldr r0, [r0]
	bl MOD04_021DD82C
	ldr r2, _02213400 ; =0x02217138
	mov r3, #0
	ldr r1, _02213408 ; =0x0221712C
	ldr r0, _0221340C ; =0x02217130
	str r3, [r2]
	str r3, [r1]
	str r3, [r0]
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02213400: .word 0x02217138
_02213404: .word MOD79_02213638
_02213408: .word 0x0221712C
_0221340C: .word 0x02217130
	arm_func_end MOD79_02213384

	arm_func_start MOD79_02213410
MOD79_02213410: ; 0x02213410
	stmdb sp!, {r4, lr}
	movs r4, r0
	bne _02213430
	ldr r0, _022134FC ; =0x02216960
	ldr r1, _02213500 ; =0x0221696C
	ldr r3, _02213504 ; =0x00000132
	mov r2, #0
	bl __msl_assertion_failed
_02213430:
	ldr r0, [r4, #0x108]
	cmp r0, #0
	bne _02213450
	ldr r0, _02213508 ; =0x02216980
	ldr r1, _02213500 ; =0x0221696C
	ldr r3, _0221350C ; =0x00000133
	mov r2, #0
	bl __msl_assertion_failed
_02213450:
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	bl MOD04_021DD82C
	ldr r1, [r4, #0x108]
	mov r0, #0
	str r1, [r4, #0x14]
	str r0, [r4, #0x108]
	ldr r0, [r4, #0x18]
	bl MOD04_021DD82C
	mov r0, #0
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	strh r0, [r4, #0x20]
	ldr r0, [r4, #0x24]
	bl MOD04_021DD82C
	mov r0, #0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD04_021EFD80
	ldr r0, [r4, #0x48]
	bl MOD04_021EFD9C
	mvn r1, #0
	add r0, r4, #0x50
	str r1, [r4, #0x48]
	bl MOD79_0221262C
	add r0, r4, #0x74
	bl MOD79_0221262C
	add r0, r4, #0x98
	bl MOD79_0221262C
	mov r0, #0
	str r0, [r4, #0xe4]
	str r0, [r4, #0xe8]
	str r0, [r4, #0xec]
	str r0, [r4, #0xf0]
	str r0, [r4, #0xf4]
	str r0, [r4, #0xf8]
	str r0, [r4, #0x130]
	ldr r0, [r4, #0x10c]
	add r0, r0, #1
	str r0, [r4, #0x10c]
	ldmia sp!, {r4, pc}
	.align 2, 0
_022134FC: .word MOD79_02216960
_02213500: .word MOD79_0221696C
_02213504: .word 0x00000132
_02213508: .word MOD79_02216980
_0221350C: .word 0x00000133
	arm_func_end MOD79_02213410

	arm_func_start MOD79_02213510
MOD79_02213510: ; 0x02213510
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r1, _02213580 ; =0x02217130
	mov r5, r0
	ldr r0, [r1]
	cmp r0, #0
	addle sp, sp, #4
	ldmleia sp!, {r4, r5, r6, r7, pc}
	bl MOD79_02213378
	ldr r7, _02213584 ; =0x0221712C
	mov r4, #0
	ldr r0, [r7]
	cmp r0, #0
	ble _02213574
	ldr r6, _02213588 ; =0x02217138
_0221354C:
	ldr r0, [r6]
	ldr r0, [r0, r4, lsl #2]
	ldr r1, [r0]
	cmp r1, #0
	beq _02213564
	.word 0xE12FFF35
_02213564:
	ldr r0, [r7]
	add r4, r4, #1
	cmp r4, r0
	blt _0221354C
_02213574:
	bl MOD79_02213374
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_02213580: .word 0x02217130
_02213584: .word 0x0221712C
_02213588: .word 0x02217138
	arm_func_end MOD79_02213510

	arm_func_start MOD79_0221358C
MOD79_0221358C: ; 0x0221358C
	stmdb sp!, {r4, lr}
	movs r4, r0
	bpl _022135AC
	ldr r0, _0221361C ; =0x02216998
	ldr r1, _02213620 ; =0x0221696C
	ldr r3, _02213624 ; =0x00000101
	mov r2, #0
	bl __msl_assertion_failed
_022135AC:
	ldr r0, _02213628 ; =0x0221712C
	ldr r0, [r0]
	cmp r4, r0
	blt _022135D0
	ldr r0, _0221362C ; =0x022169A8
	ldr r1, _02213620 ; =0x0221696C
	ldr r3, _02213630 ; =0x00000102
	mov r2, #0
	bl __msl_assertion_failed
_022135D0:
	bl MOD79_02213378
	cmp r4, #0
	blt _022135EC
	ldr r0, _02213628 ; =0x0221712C
	ldr r0, [r0]
	cmp r4, r0
	blt _022135F8
_022135EC:
	bl MOD79_02213374
	mov r0, #0
	ldmia sp!, {r4, pc}
_022135F8:
	ldr r0, _02213634 ; =0x02217138
	ldr r0, [r0]
	ldr r4, [r0, r4, lsl #2]
	ldr r0, [r4]
	cmp r0, #0
	moveq r4, #0
	bl MOD79_02213374
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221361C: .word MOD79_02216998
_02213620: .word MOD79_0221696C
_02213624: .word 0x00000101
_02213628: .word 0x0221712C
_0221362C: .word MOD79_022169A8
_02213630: .word 0x00000102
_02213634: .word 0x02217138
	arm_func_end MOD79_0221358C

	arm_func_start MOD79_02213638
MOD79_02213638: ; 0x02213638
	stmdb sp!, {r4, lr}
	movs r4, r0
	bne _02213658
	ldr r0, _02213800 ; =0x02216960
	ldr r1, _02213804 ; =0x0221696C
	mov r2, #0
	mov r3, #0xb3
	bl __msl_assertion_failed
_02213658:
	ldr r0, [r4, #4]
	cmp r0, #0
	bge _02213678
	ldr r0, _02213808 ; =0x022169C4
	ldr r1, _02213804 ; =0x0221696C
	mov r2, #0
	mov r3, #0xb4
	bl __msl_assertion_failed
_02213678:
	ldr r0, _0221380C ; =0x0221712C
	ldr r1, [r4, #4]
	ldr r0, [r0]
	cmp r1, r0
	blt _022136A0
	ldr r0, _02213810 ; =0x022169E0
	ldr r1, _02213804 ; =0x0221696C
	mov r2, #0
	mov r3, #0xb5
	bl __msl_assertion_failed
_022136A0:
	ldr r0, [r4]
	cmp r0, #0
	bne _022136C0
	ldr r0, _02213814 ; =0x02216A08
	ldr r1, _02213804 ; =0x0221696C
	mov r2, #0
	mov r3, #0xb6
	bl __msl_assertion_failed
_022136C0:
	cmp r4, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4]
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, [r4, #4]
	cmp r1, #0
	movlt r0, #0
	ldmltia sp!, {r4, pc}
	ldr r0, _0221380C ; =0x0221712C
	ldr r0, [r0]
	cmp r1, r0
	movge r0, #0
	ldmgeia sp!, {r4, pc}
	bl MOD79_02213378
	ldr r0, [r4, #0x14]
	bl MOD04_021DD82C
	ldr r0, [r4, #0x18]
	bl MOD04_021DD82C
	ldr r0, [r4, #0x24]
	bl MOD04_021DD82C
	ldr r0, [r4, #0x28]
	bl MOD04_021DD82C
	ldr r0, [r4, #0x108]
	bl MOD04_021DD82C
	ldr r0, [r4, #0x15c]
	bl MOD04_021DD82C
	ldr r0, [r4, #0x48]
	mvn r1, #0
	cmp r0, r1
	beq _02213754
	mov r1, #2
	bl MOD04_021EFD80
	ldr r0, [r4, #0x48]
	bl MOD04_021EFD9C
_02213754:
	add r0, r4, #0x50
	bl MOD79_02212A54
	add r0, r4, #0x74
	bl MOD79_02212A54
	add r0, r4, #0x98
	bl MOD79_02212A54
	add r0, r4, #0xbc
	bl MOD79_02212A54
	ldr r0, [r4, #0x140]
	cmp r0, #0
	beq _02213788
	mov r0, r4
	bl MOD79_022149E4
_02213788:
	ldr r0, [r4, #0x13c]
	cmp r0, #0
	beq _022137B0
	bl MOD79_02215074
	cmp r0, #0
	beq _022137B0
	ldr r0, [r4, #0x13c]
	bl MOD79_02215058
	mov r0, #0
	str r0, [r4, #0x13c]
_022137B0:
	ldr r0, [r4, #0x16c]
	cmp r0, #0
	beq _022137DC
	ldr r2, [r4, #0x178]
	cmp r2, #0
	beq _022137D4
	mov r0, r4
	add r1, r4, #0x164
	.word 0xE12FFF32
_022137D4:
	mov r0, #0
	str r0, [r4, #0x16c]
_022137DC:
	mov r1, #0
	ldr r0, _02213818 ; =0x02217130
	str r1, [r4]
	ldr r1, [r0]
	sub r1, r1, #1
	str r1, [r0]
	bl MOD79_02213374
	mov r0, #1
	ldmia sp!, {r4, pc}
	.align 2, 0
_02213800: .word MOD79_02216960
_02213804: .word MOD79_0221696C
_02213808: .word MOD79_022169C4
_0221380C: .word 0x0221712C
_02213810: .word MOD79_022169E0
_02213814: .word MOD79_02216A08
_02213818: .word 0x02217130
	arm_func_end MOD79_02213638

	arm_func_start MOD79_0221381C
MOD79_0221381C: ; 0x0221381C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	bl MOD79_02213378
	bl MOD79_022139CC
	mov r5, r0
	mvn r0, #0
	cmp r5, r0
	bne _0221384C
	bl MOD79_02213374
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_0221384C:
	ldr r0, _022139C0 ; =0x02217138
	mov r1, #0
	ldr r0, [r0]
	mov r2, #0x184
	ldr r4, [r0, r5, lsl #2]
	mov r0, r4
	bl memset
	mov r0, #1
	str r0, [r4]
	ldr r0, _022139C4 ; =0x02217134
	str r5, [r4, #4]
	ldr r2, [r0]
	mov ip, #0
	add r1, r2, #1
	str r1, [r0]
	str r2, [r4, #8]
	str ip, [r4, #0xc]
	str ip, [r4, #0x10]
	str ip, [r4, #0x14]
	str ip, [r4, #0x18]
	str ip, [r4, #0x1c]
	strh ip, [r4, #0x20]
	str ip, [r4, #0x24]
	str ip, [r4, #0x28]
	str ip, [r4, #0x2c]
	str ip, [r4, #0x30]
	str ip, [r4, #0x34]
	str ip, [r4, #0x38]
	str ip, [r4, #0x3c]
	str ip, [r4, #0x40]
	str ip, [r4, #0x44]
	mvn r0, #0
	str r0, [r4, #0x48]
	str ip, [r4, #0x4c]
	str ip, [r4, #0xe0]
	str ip, [r4, #0xe4]
	str ip, [r4, #0xe8]
	str ip, [r4, #0xec]
	str ip, [r4, #0xf0]
	str ip, [r4, #0xf4]
	str ip, [r4, #0xf8]
	str ip, [r4, #0xfc]
	str ip, [r4, #0x100]
	str r0, [r4, #0x104]
	str ip, [r4, #0x108]
	str ip, [r4, #0x10c]
	str ip, [r4, #0x110]
	str ip, [r4, #0x12c]
	str ip, [r4, #0x134]
	str ip, [r4, #0x138]
	str ip, [r4, #0x13c]
	mov r0, #0x1f4
	str r0, [r4, #0x158]
	add r0, r4, #0x100
	mov r1, #0x50
	strh r1, [r0, #0x60]
	str ip, [r4, #0x15c]
	mov r0, r4
	add r1, r4, #0x50
	mov r2, #0x800
	mov r3, #0x1000
	str ip, [r4, #0x164]
	bl MOD79_02212BC4
	cmp r0, #0
	beq _02213964
	mov r2, #0x800
	mov r0, r4
	mov r3, r2
	add r1, r4, #0x74
	bl MOD79_02212BC4
_02213964:
	cmp r0, #0
	beq _02213980
	mov r0, r4
	add r1, r4, #0x98
	mov r2, #0x800
	mov r3, #0x400
	bl MOD79_02212BC4
_02213980:
	cmp r0, #0
	bne _022139A0
	mov r0, r4
	bl MOD79_02213638
	bl MOD79_02213374
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_022139A0:
	ldr r0, _022139C8 ; =0x02217130
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	bl MOD79_02213374
	mov r0, r4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022139C0: .word 0x02217138
_022139C4: .word 0x02217134
_022139C8: .word 0x02217130
	arm_func_end MOD79_0221381C

	arm_func_start MOD79_022139CC
MOD79_022139CC: ; 0x022139CC
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	ldr r1, _02213AF4 ; =0x0221712C
	mov r0, #0
	ldr r2, [r1]
	cmp r2, #0
	ble _02213A10
	ldr r1, _02213AF8 ; =0x02217138
	ldr r3, [r1]
_022139F0:
	ldr r1, [r3, r0, lsl #2]
	ldr r1, [r1]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	add r0, r0, #1
	cmp r0, r2
	blt _022139F0
_02213A10:
	ldr r0, _02213AFC ; =0x02217130
	ldr r0, [r0]
	cmp r0, r2
	beq _02213A34
	ldr r0, _02213B00 ; =0x02216A1C
	ldr r1, _02213B04 ; =0x0221696C
	mov r2, #0
	mov r3, #0x33
	bl __msl_assertion_failed
_02213A34:
	ldr r1, _02213AF4 ; =0x0221712C
	ldr r0, _02213AF8 ; =0x02217138
	ldr r7, [r1]
	ldr r0, [r0]
	add r6, r7, #4
	mov r1, r6, lsl #2
	bl MOD04_021DD844
	cmp r0, #0
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	ldr r8, _02213AF8 ; =0x02217138
	mov r5, r7
	str r0, [r8]
	cmp r7, r6
	bge _02213AE0
	mov sb, #0
	mov r4, #0x184
_02213A7C:
	mov r0, r4
	bl MOD04_021DD860
	ldr r1, [r8]
	str r0, [r1, r5, lsl #2]
	ldr r0, [r8]
	ldr r0, [r0, r5, lsl #2]
	cmp r0, #0
	bne _02213AD0
	sub r5, r5, #1
	cmp r5, r7
	blt _02213AC4
	ldr r4, _02213AF8 ; =0x02217138
_02213AAC:
	ldr r0, [r4]
	ldr r0, [r0, r5, lsl #2]
	bl MOD04_021DD82C
	sub r5, r5, #1
	cmp r5, r7
	bge _02213AAC
_02213AC4:
	add sp, sp, #4
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_02213AD0:
	add r5, r5, #1
	str sb, [r0]
	cmp r5, r6
	blt _02213A7C
_02213AE0:
	ldr r1, _02213AF4 ; =0x0221712C
	mov r0, r7
	str r6, [r1]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_02213AF4: .word 0x0221712C
_02213AF8: .word 0x02217138
_02213AFC: .word 0x02217130
_02213B00: .word MOD79_02216A1C
_02213B04: .word MOD79_0221696C
	arm_func_end MOD79_022139CC

	arm_func_start MOD79_02213B08
MOD79_02213B08: ; 0x02213B08
	ldr ip, _02213B14 ; =MOD79_02213510
	ldr r0, _02213B18 ; =MOD79_02213E84
	bx ip
	.align 2, 0
_02213B14: .word MOD79_02213510
_02213B18: .word MOD79_02213E84
	arm_func_end MOD79_02213B08

	arm_func_start MOD79_02213B1C
MOD79_02213B1C: ; 0x02213B1C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	movs r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	beq _02213B40
	ldrsb r0, [r8]
	cmp r0, #0
	bne _02213B54
_02213B40:
	ldr r0, _02213D64 ; =0x02216A50
	ldr r1, _02213D68 ; =0x02216A44
	mov r2, #0
	mov r3, #0x128
	bl __msl_assertion_failed
_02213B54:
	cmp r5, #0
	bge _02213B70
	ldr r0, _02213D6C ; =0x02216A60
	ldr r1, _02213D68 ; =0x02216A44
	ldr r3, _02213D70 ; =0x00000129
	mov r2, #0
	bl __msl_assertion_failed
_02213B70:
	cmp r6, #0
	beq _02213B94
	cmp r5, #0
	bne _02213B94
	ldr r0, _02213D74 ; =0x02216A70
	ldr r1, _02213D68 ; =0x02216A44
	ldr r3, _02213D78 ; =0x0000012A
	mov r2, #0
	bl __msl_assertion_failed
_02213B94:
	cmp r8, #0
	beq _02213BA8
	ldrsb r0, [r8]
	cmp r0, #0
	bne _02213BB0
_02213BA8:
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02213BB0:
	cmp r5, #0
	mvnlt r0, #0
	ldmltia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r6, #0
	beq _02213BD0
	cmp r5, #0
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
_02213BD0:
	ldr r0, _02213D7C ; =0x0221713C
	ldr r0, [r0]
	cmp r0, #0
	bne _02213BE4
	bl MOD79_02213E24
_02213BE4:
	bl MOD79_0221381C
	movs r4, r0
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	mov r1, #0
	mov r0, r8
	str r1, [r4, #0xc]
	bl MOD04_021F0208
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _02213C24
	mov r0, r4
	bl MOD79_02213638
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02213C24:
	cmp r7, #0
	beq _02213C60
	ldrsb r0, [r7]
	cmp r0, #0
	beq _02213C60
	mov r0, r7
	bl MOD04_021F0208
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x28]
	cmp r0, #0
	bne _02213C60
	mov r0, r4
	bl MOD79_02213638
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02213C60:
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x20]
	str r1, [r4, #0x13c]
	str r0, [r4, #0x30]
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x28]
	str r1, [r4, #0x3c]
	str r0, [r4, #0x40]
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1c]
	str r1, [r4, #0x44]
	str r0, [r4, #0x134]
	cmp r6, #0
	movne r0, #1
	moveq r0, #0
	str r0, [r4, #0xe0]
	ldr r0, [r4, #0xe0]
	cmp r0, #0
	beq _02213CC4
	mov r0, r4
	mov r2, r6
	mov r3, r5
	add r1, r4, #0xbc
	bl MOD79_02212AB4
	b _02213CD8
_02213CC4:
	mov r2, #0x800
	mov r0, r4
	mov r3, r2
	add r1, r4, #0xbc
	bl MOD79_02212BC4
_02213CD8:
	cmp r0, #0
	bne _02213CF0
	mov r0, r4
	bl MOD79_02213638
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02213CF0:
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _02213D1C
	mov r0, r4
	bl MOD79_02214A60
	cmp r0, #0
	bne _02213D1C
	mov r0, r4
	bl MOD79_02213638
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02213D1C:
	ldr r0, [sp, #0x20]
	cmp r0, #0
	beq _02213D5C
	mov r0, r4
	bl MOD79_02213E84
	cmp r0, #0
	bne _02213D54
	mov r5, #0xa
_02213D3C:
	mov r0, r5
	bl MOD04_021F0250
	mov r0, r4
	bl MOD79_02213E84
	cmp r0, #0
	beq _02213D3C
_02213D54:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02213D5C:
	ldr r0, [r4, #4]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02213D64: .word MOD79_02216A50
_02213D68: .word MOD79_02216A44
_02213D6C: .word MOD79_02216A60
_02213D70: .word 0x00000129
_02213D74: .word MOD79_02216A70
_02213D78: .word 0x0000012A
_02213D7C: .word 0x0221713C
	arm_func_end MOD79_02213B1C

	arm_func_start MOD79_02213D80
MOD79_02213D80: ; 0x02213D80
	stmdb sp!, {lr}
	sub sp, sp, #0x1c
	mov ip, #0
	str ip, [sp]
	str ip, [sp, #4]
	str r1, [sp, #8]
	str ip, [sp, #0xc]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	mov r1, ip
	mov r2, ip
	mov r3, ip
	bl MOD79_02213B1C
	add sp, sp, #0x1c
	ldmia sp!, {pc}
	arm_func_end MOD79_02213D80

	arm_func_start MOD79_02213DBC
MOD79_02213DBC: ; 0x02213DBC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD79_02213378
	ldr r0, _02213E1C ; =0x0221713C
	ldr r1, [r0]
	subs r1, r1, #1
	str r1, [r0]
	bne _02213E10
	bl MOD79_02213384
	ldr r0, _02213E20 ; =0x02217128
	ldr r0, [r0]
	cmp r0, #0
	beq _02213E00
	bl MOD04_021DD82C
	ldr r0, _02213E20 ; =0x02217128
	mov r1, #0
	str r1, [r0]
_02213E00:
	bl MOD79_02213374
	bl MOD79_0221337C
	add sp, sp, #4
	ldmia sp!, {pc}
_02213E10:
	bl MOD79_02213374
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02213E1C: .word 0x0221713C
_02213E20: .word 0x02217128
	arm_func_end MOD79_02213DBC

	arm_func_start MOD79_02213E24
MOD79_02213E24: ; 0x02213E24
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD79_02213378
	ldr r0, _02213E78 ; =0x0221713C
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	cmp r1, #1
	bne _02213E6C
	bl MOD79_02213380
	ldr r1, _02213E7C ; =0x0221695C
	mov r3, #0x7d
	ldr r0, _02213E80 ; =0x02216958
	mov r2, #0xfa
	str r3, [r1]
	str r2, [r0]
	add sp, sp, #4
	ldmia sp!, {pc}
_02213E6C:
	bl MOD79_02213374
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_02213E78: .word 0x0221713C
_02213E7C: .word MOD79_0221695C
_02213E80: .word MOD79_02216958
	arm_func_end MOD79_02213E24

	arm_func_start MOD79_02213E84
MOD79_02213E84: ; 0x02213E84
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	movs r4, r0
	bne _02213EA8
	ldr r0, _02213FE8 ; =0x02216A88
	ldr r1, _02213FEC ; =0x02216A44
	mov r2, #0
	mov r3, #0x5b
	bl __msl_assertion_failed
_02213EA8:
	ldr r0, [r4, #4]
	bl MOD79_0221358C
	cmp r0, r4
	beq _02213ECC
	ldr r0, _02213FF0 ; =0x02216A94
	ldr r1, _02213FEC ; =0x02216A44
	mov r2, #0
	mov r3, #0x5c
	bl __msl_assertion_failed
_02213ECC:
	ldr r0, [r4, #0x12c]
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
	mov r0, #1
	str r0, [r4, #0x12c]
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _02213EFC
	mov r0, r4
	bl MOD79_02216478
_02213EFC:
	ldr r0, [r4, #0x10]
	cmp r0, #1
	bne _02213F10
	mov r0, r4
	bl MOD79_0221621C
_02213F10:
	ldr r0, [r4, #0x10]
	cmp r0, #2
	bne _02213F24
	mov r0, r4
	bl MOD79_022160C0
_02213F24:
	ldr r0, [r4, #0x10]
	cmp r0, #3
	bne _02213F38
	mov r0, r4
	bl MOD79_02215E40
_02213F38:
	ldr r0, [r4, #0x10]
	cmp r0, #4
	bne _02213F4C
	mov r0, r4
	bl MOD79_02215DA8
_02213F4C:
	ldr r0, [r4, #0x10]
	cmp r0, #5
	bne _02213F60
	mov r0, r4
	bl MOD79_02215D28
_02213F60:
	ldr r0, [r4, #0x10]
	cmp r0, #6
	bne _02213F74
	mov r0, r4
	bl MOD79_02215AA8
_02213F74:
	ldr r0, [r4, #0x10]
	cmp r0, #7
	bne _02213F88
	mov r0, r4
	bl MOD79_02215174
_02213F88:
	ldr r0, [r4, #0x10]
	cmp r0, #8
	bne _02213F9C
	mov r0, r4
	bl MOD79_0221507C
_02213F9C:
	ldr r0, [r4, #0x108]
	cmp r0, #0
	beq _02213FB0
	mov r0, r4
	bl MOD79_02213410
_02213FB0:
	ldr r5, [r4, #0xfc]
	cmp r5, #0
	moveq r0, #0
	streq r0, [r4, #0x12c]
	beq _02213FDC
	mov r0, r4
	bl MOD79_02213FF4
	mov r0, r4
	bl MOD79_02212E78
	mov r0, r4
	bl MOD79_02213638
_02213FDC:
	mov r0, r5
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02213FE8: .word MOD79_02216A88
_02213FEC: .word MOD79_02216A44
_02213FF0: .word MOD79_02216A94
	arm_func_end MOD79_02213E84

	arm_func_start MOD79_02213FF4
MOD79_02213FF4: ; 0x02213FF4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr lr, [r0, #0xec]
	ldr r3, _022140CC ; =0x51EB851F
	mov r1, lr, lsr #0x1f
	smull r2, ip, r3, lr
	mov ip, ip, asr #5
	add ip, r1, ip
	cmp ip, #5
	addls pc, pc, ip, lsl #2
	b _022140C4
_02214020: ; jump table
	b _022140C4 ; case 0
	b _02214038 ; case 1
	b _02214038 ; case 2
	b _02214038 ; case 3
	b _02214040 ; case 4
	b _022140BC ; case 5
_02214038:
	add sp, sp, #4
	ldmia sp!, {pc}
_02214040:
	ldr r1, _022140D0 ; =0x00000191
	sub r1, lr, r1
	cmp r1, #9
	addls pc, pc, r1, lsl #2
	b _022140AC
_02214054: ; jump table
	b _0221407C ; case 0
	b _022140AC ; case 1
	b _0221408C ; case 2
	b _0221409C ; case 3
	b _022140AC ; case 4
	b _022140AC ; case 5
	b _022140AC ; case 6
	b _022140AC ; case 7
	b _022140AC ; case 8
	b _0221409C ; case 9
_0221407C:
	mov r1, #9
	str r1, [r0, #0x38]
	add sp, sp, #4
	ldmia sp!, {pc}
_0221408C:
	mov r1, #0xa
	str r1, [r0, #0x38]
	add sp, sp, #4
	ldmia sp!, {pc}
_0221409C:
	mov r1, #0xb
	str r1, [r0, #0x38]
	add sp, sp, #4
	ldmia sp!, {pc}
_022140AC:
	mov r1, #8
	str r1, [r0, #0x38]
	add sp, sp, #4
	ldmia sp!, {pc}
_022140BC:
	mov r1, #0xc
	str r1, [r0, #0x38]
_022140C4:
	add sp, sp, #4
	ldmia sp!, {pc}
	.align 2, 0
_022140CC: .word 0x51EB851F
_022140D0: .word 0x00000191
	arm_func_end MOD79_02213FF4

	arm_func_start MOD79_022140D4
MOD79_022140D4: ; 0x022140D4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	movs sl, r0
	bne _022140F8
	ldr r0, _02214330 ; =0x02216AD0
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214338 ; =0x00000404
	mov r2, #0
	bl __msl_assertion_failed
_022140F8:
	ldr r0, [sl, #0x13c]
	cmp r0, #0
	bne _02214118
	ldr r0, _0221433C ; =0x02216AE8
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214340 ; =0x00000405
	mov r2, #0
	bl __msl_assertion_failed
_02214118:
	ldr r0, [sl, #0x140]
	cmp r0, #0
	bne _02214138
	ldr r0, _02214344 ; =0x02216AFC
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214348 ; =0x00000406
	mov r2, #0
	bl __msl_assertion_failed
_02214138:
	ldr r0, [sl, #0x13c]
	ldr r0, [r0]
	bl MOD04_021EF06C
	mov r4, r0
	ldr r0, [sl, #0x140]
	bl MOD04_021EF06C
	cmp r4, r0
	beq _0221416C
	ldr r0, _0221434C ; =0x02216B1C
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214350 ; =0x00000407
	mov r2, #0
	bl __msl_assertion_failed
_0221416C:
	ldr r0, [sl, #0x144]
	cmp r0, #0
	bge _0221418C
	ldr r0, _02214354 ; =0x02216B70
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214358 ; =0x00000408
	mov r2, #0
	bl __msl_assertion_failed
_0221418C:
	ldr r0, [sl, #0x140]
	bl MOD04_021EF06C
	ldr r1, [sl, #0x144]
	cmp r1, r0
	ble _022141B4
	ldr r0, _0221435C ; =0x02216B94
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214360 ; =0x00000409
	mov r2, #0
	bl __msl_assertion_failed
_022141B4:
	ldr r0, [sl, #0x140]
	add sb, sl, #0x140
	bl MOD04_021EF06C
	ldr r1, [sl, #0x5c]
	mov r7, r0
	cmp r1, #0
	beq _0221421C
	mov r0, sl
	bl MOD79_02212554
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r1, [sl, #0x60]
	ldr r0, [sl, #0x5c]
	cmp r1, r0
	addlt sp, sp, #4
	movlt r0, #2
	ldmltia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add r0, sl, #0x50
	bl MOD79_0221262C
	ldr r0, [sl, #0x144]
	cmp r0, r7
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_0221421C:
	ldr r1, [sb, #4]
	cmp r1, r7
	bge _022142E0
	ldr r6, _02214364 ; =0x02216BE4
	ldr fp, _02214334 ; =0x02216ADC
	mov r5, #0
	mov r4, #1
_02214238:
	ldr r0, [sb]
	bl MOD04_021EEFFC
	movs r8, r0
	bne _0221425C
	ldr r3, _02214368 ; =0x0000042F
	mov r0, r6
	mov r1, fp
	mov r2, r5
	bl __msl_assertion_failed
_0221425C:
	ldr r0, [sb, #4]
	mov r1, sl
	cmp r0, #0
	moveq r2, r4
	movne r2, r5
	mov r0, r8
	bl MOD79_02214378
	cmp r0, #0
	bne _022142B8
	ldr r0, [sl, #0xfc]
	cmp r0, #0
	beq _02214298
	ldr r0, [sl, #0x38]
	cmp r0, #0
	bne _022142AC
_02214298:
	ldr r0, _0221436C ; =0x02216BF0
	ldr r1, _02214334 ; =0x02216ADC
	ldr r3, _02214370 ; =0x0000043B
	mov r2, #0
	bl __msl_assertion_failed
_022142AC:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_022142B8:
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #2
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, [sb, #4]
	add r0, r0, #1
	str r0, [sb, #4]
	ldr r1, [sb, #4]
	cmp r1, r7
	blt _02214238
_022142E0:
	ldr r0, [sl, #0x13c]
	ldr r0, [r0, #0xc]
	cmp r0, #0
	beq _02214318
	ldr r0, _02214374 ; =0x02216C1C
	bl strlen
	mov r2, r0
	ldr r1, _02214374 ; =0x02216C1C
	mov r0, sl
	bl MOD79_02212F04
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02214318:
	ldr r0, [sl, #0x5c]
	cmp r0, #0
	movne r0, #2
	moveq r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02214330: .word MOD79_02216AD0
_02214334: .word MOD79_02216ADC
_02214338: .word 0x00000404
_0221433C: .word MOD79_02216AE8
_02214340: .word 0x00000405
_02214344: .word MOD79_02216AFC
_02214348: .word 0x00000406
_0221434C: .word MOD79_02216B1C
_02214350: .word 0x00000407
_02214354: .word MOD79_02216B70
_02214358: .word 0x00000408
_0221435C: .word MOD79_02216B94
_02214360: .word 0x00000409
_02214364: .word MOD79_02216BE4
_02214368: .word 0x0000042F
_0221436C: .word MOD79_02216BF0
_02214370: .word 0x0000043B
_02214374: .word MOD79_02216C1C
	arm_func_end MOD79_022140D4

	arm_func_start MOD79_02214378
MOD79_02214378: ; 0x02214378
	stmdb sp!, {r4, r5, r6, lr}
	ldr ip, _02214554 ; =0x00000808
	sub sp, sp, ip
	mov r6, r0
	ldr r3, [r6, #4]
	mvn r0, #0
	mov r5, r1
	mov r4, r2
	cmp r3, r0
	bne _022144D8
	mov r2, #0
	str r2, [r6, #4]
	ldr r0, [r5, #0x13c]
	ldr r0, [r0, #0xc]
	cmp r0, #0
	bne _02214410
	ldr r0, [r6]
	ldr r0, [r0]
	cmp r0, #0
	beq _022143D8
	ldr r0, _02214558 ; =0x02216C48
	ldr r1, _0221455C ; =0x02216ADC
	ldr r3, _02214560 ; =0x000003A9
	bl __msl_assertion_failed
_022143D8:
	cmp r4, #0
	beq _022143F8
	ldr r1, [r6]
	add r0, sp, #8
	ldr r2, [r1, #4]
	ldr r1, _02214564 ; =0x02216C68
	bl sprintf
	b _02214498
_022143F8:
	ldr r1, [r6]
	add r0, sp, #8
	ldr r2, [r1, #4]
	ldr r1, _02214568 ; =0x02216C6C
	bl sprintf
	b _02214498
_02214410:
	ldr r3, [r6]
	ldr r1, [r3]
	cmp r1, #0
	bne _02214440
	cmp r4, #0
	ldrne r2, _0221456C ; =0x02216C74
	ldr r3, [r3, #4]
	ldreq r2, _02214570 ; =0x02216C9C
	ldr r1, _02214574 ; =0x02216CC8
	add r0, sp, #8
	bl sprintf
	b _02214498
_02214440:
	sub r0, r1, #1
	cmp r0, #1
	bhi _02214488
	cmp r1, #1
	ldreq r1, [r3, #0xc]
	ldreq r0, [r3, #0x10]
	ldrne r1, [r3, #0x10]
	ldrne r0, [r3, #0x14]
	cmp r4, #0
	str r1, [sp]
	str r0, [sp, #4]
	ldrne r2, _0221456C ; =0x02216C74
	ldr r3, [r3, #4]
	ldreq r2, _02214570 ; =0x02216C9C
	ldr r1, _02214578 ; =0x02216CF8
	add r0, sp, #8
	bl sprintf
	b _02214498
_02214488:
	ldr r0, _0221457C ; =0x02216D4C
	ldr r1, _0221455C ; =0x02216ADC
	mov r3, #0x3dc
	bl __msl_assertion_failed
_02214498:
	add r0, sp, #8
	bl strlen
	mov r2, r0
	add r1, sp, #8
	mov r0, r5
	bl MOD79_02212F04
	cmp r0, #0
	ldreq ip, _02214554 ; =0x00000808
	moveq r0, #0
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r0, #2
	ldreq ip, _02214554 ; =0x00000808
	moveq r0, #2
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, pc}
_022144D8:
	ldr r0, [r6]
	ldr r0, [r0]
	cmp r0, #0
	bne _02214500
	mov r0, r6
	mov r1, r5
	bl MOD79_022147E8
	ldr ip, _02214554 ; =0x00000808
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, pc}
_02214500:
	cmp r0, #1
	bne _02214520
	mov r0, r6
	mov r1, r5
	bl MOD79_0221467C
	ldr ip, _02214554 ; =0x00000808
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, pc}
_02214520:
	cmp r0, #2
	beq _0221453C
	ldr r0, _02214580 ; =0x02216D50
	ldr r1, _0221455C ; =0x02216ADC
	ldr r3, _02214584 ; =0x000003F5
	mov r2, #0
	bl __msl_assertion_failed
_0221453C:
	mov r0, r6
	mov r1, r5
	bl MOD79_02214588
	ldr ip, _02214554 ; =0x00000808
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02214554: .word 0x00000808
_02214558: .word MOD79_02216C48
_0221455C: .word MOD79_02216ADC
_02214560: .word 0x000003A9
_02214564: .word MOD79_02216C68
_02214568: .word MOD79_02216C6C
_0221456C: .word MOD79_02216C74
_02214570: .word MOD79_02216C9C
_02214574: .word MOD79_02216CC8
_02214578: .word MOD79_02216CF8
_0221457C: .word MOD79_02216D4C
_02214580: .word MOD79_02216D50
_02214584: .word 0x000003F5
	arm_func_end MOD79_02214378

	arm_func_start MOD79_02214588
MOD79_02214588: ; 0x02214588
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	ldr r0, [r5, #4]
	mov r4, r1
	cmp r0, #0
	bge _022145B8
	ldr r0, _02214668 ; =0x02216D74
	ldr r1, _0221466C ; =0x02216ADC
	ldr r3, _02214670 ; =0x0000036E
	mov r2, #0
	bl __msl_assertion_failed
_022145B8:
	ldr r0, [r5]
	ldr r1, [r0, #0xc]
	cmp r1, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, [r5, #4]
	cmp r0, r1
	blt _022145F0
	ldr r0, _02214674 ; =0x02216D84
	ldr r1, _0221466C ; =0x02216ADC
	ldr r3, _02214678 ; =0x00000375
	mov r2, #0
	bl __msl_assertion_failed
_022145F0:
	ldr r1, [r5]
	ldr r3, [r5, #4]
	ldr r0, [r1, #0xc]
	ldr r1, [r1, #8]
	sub r2, r0, r3
	cmp r2, #0x8000
	movge r2, #0x8000
	mov r0, r4
	add r1, r1, r3
	bl MOD79_02212F68
	mvn r1, #0
	cmp r0, r1
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, [r5, #4]
	add r1, r1, r0
	str r1, [r5, #4]
	ldr r2, [r5]
	ldr r1, [r5, #4]
	ldr r2, [r2, #0xc]
	cmp r2, r1
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, pc}
	cmp r0, #0
	bne _022145F0
	mov r0, #2
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02214668: .word MOD79_02216D74
_0221466C: .word MOD79_02216ADC
_02214670: .word 0x0000036E
_02214674: .word MOD79_02216D84
_02214678: .word 0x00000375
	arm_func_end MOD79_02214588

	arm_func_start MOD79_0221467C
MOD79_0221467C: ; 0x0221467C
	stmdb sp!, {r4, r5, lr}
	ldr ip, _022147CC ; =0x00001004
	sub sp, sp, ip
	mov r5, r0
	ldr r0, [r5, #4]
	mov r4, r1
	cmp r0, #0
	bge _022146B0
	ldr r0, _022147D0 ; =0x02216D74
	ldr r1, _022147D4 ; =0x02216ADC
	ldr r3, _022147D8 ; =0x00000336
	mov r2, #0
	bl __msl_assertion_failed
_022146B0:
	ldr r1, [r5, #4]
	ldr r0, [r5, #0xc]
	cmp r1, r0
	blt _022146D4
	ldr r0, _022147DC ; =0x02216DB4
	ldr r1, _022147D4 ; =0x02216ADC
	ldr r3, _022147E0 ; =0x00000337
	mov r2, #0
	bl __msl_assertion_failed
_022146D4:
	ldr r0, [r5, #8]
	bl ftell
	ldr r1, [r5, #4]
	cmp r1, r0
	beq _022146FC
	ldr r0, _022147E4 ; =0x02216DDC
	ldr r1, _022147D4 ; =0x02216ADC
	mov r2, #0
	mov r3, #0x338
	bl __msl_assertion_failed
_022146FC:
	ldr r3, [r5, #8]
	add r0, sp, #0
	mov r1, #1
	mov r2, #0x1000
	bl fread
	mov r2, r0
	cmp r2, #0
	bgt _0221473C
	ldr ip, _022147CC ; =0x00001004
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #0xe
	str r0, [r4, #0x38]
	add sp, sp, ip
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_0221473C:
	ldr r0, [r5, #4]
	add r0, r0, r2
	str r0, [r5, #4]
	ldr r1, [r5, #4]
	ldr r0, [r5, #0xc]
	cmp r1, r0
	ble _02214778
	ldr ip, _022147CC ; =0x00001004
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #0xe
	str r0, [r4, #0x38]
	add sp, sp, ip
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_02214778:
	add r1, sp, #0
	mov r0, r4
	bl MOD79_02212F04
	cmp r0, #0
	ldreq ip, _022147CC ; =0x00001004
	moveq r0, #0
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, pc}
	ldr r2, [r5, #4]
	ldr r1, [r5, #0xc]
	cmp r2, r1
	ldreq ip, _022147CC ; =0x00001004
	moveq r0, #1
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, pc}
	cmp r0, #1
	beq _022146FC
	mov r0, #2
	ldr ip, _022147CC ; =0x00001004
	add sp, sp, ip
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_022147CC: .word 0x00001004
_022147D0: .word MOD79_02216D74
_022147D4: .word MOD79_02216ADC
_022147D8: .word 0x00000336
_022147DC: .word MOD79_02216DB4
_022147E0: .word 0x00000337
_022147E4: .word MOD79_02216DDC
	arm_func_end MOD79_0221467C

	arm_func_start MOD79_022147E8
MOD79_022147E8: ; 0x022147E8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov r4, r0
	ldr r0, [r4, #4]
	mov sl, r1
	cmp r0, #0
	bge _02214818
	ldr r0, _022149BC ; =0x02216D74
	ldr r1, _022149C0 ; =0x02216ADC
	ldr r3, _022149C4 ; =0x000002E7
	mov r2, #0
	bl __msl_assertion_failed
_02214818:
	ldr r0, [r4]
	ldr r1, [r0, #0xc]
	cmp r1, #0
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, [r4, #4]
	cmp r0, r1
	blt _02214850
	ldr r0, _022149C8 ; =0x02216E14
	ldr r1, _022149C0 ; =0x02216ADC
	ldr r3, _022149CC ; =0x000002EE
	mov r2, #0
	bl __msl_assertion_failed
_02214850:
	ldr r0, [sl, #0x13c]
	ldr r0, [r0, #0xc]
	cmp r0, #0
	bne _02214968
	ldr r1, [r4]
	ldr r0, [r1, #0x10]
	cmp r0, #0
	beq _02214968
	ldr r0, _022149D0 ; =0x02216738
	ldr r7, [r1, #8]
	ldrb r3, [r0]
	ldrb r2, [r0, #1]
	ldrb r1, [r0, #2]
	ldrb r0, [r0, #3]
	strb r3, [sp]
	strb r2, [sp, #1]
	strb r1, [sp, #2]
	strb r0, [sp, #3]
	ldrsb r8, [r7]
	mov sb, #0
	cmp r8, #0
	beq _0221495C
	mov fp, sb
	mov r4, #3
	mov r5, #0x2b
_022148B4:
	ldr r0, _022149D4 ; =0x02216E40
	mov r1, r8
	bl strchr
	cmp r0, #0
	beq _022148D8
	mov r1, r8
	add r0, sl, #0x50
	bl MOD79_022126A4
	b _0221494C
_022148D8:
	cmp r8, #0x20
	bne _022148F0
	mov r1, r5
	add r0, sl, #0x50
	bl MOD79_022126A4
	b _0221494C
_022148F0:
	mov r0, r8, asr #3
	add r0, r8, r0, lsr #28
	mov r6, r0, asr #4
	cmp r6, #0x10
	blt _02214918
	ldr r0, _022149D8 ; =0x02216E84
	ldr r1, _022149C0 ; =0x02216ADC
	ldr r3, _022149DC ; =0x0000030D
	mov r2, fp
	bl __msl_assertion_failed
_02214918:
	ldr r0, _022149E0 ; =0x02216E94
	mov r1, r8, lsr #0x1f
	ldrsb r2, [r0, r6]
	rsb r0, r1, r8, lsl #28
	add r1, r1, r0, ror #28
	ldr r0, _022149E0 ; =0x02216E94
	strb r2, [sp, #1]
	ldrsb r2, [r0, r1]
	add r1, sp, #0
	add r0, sl, #0x50
	strb r2, [sp, #2]
	mov r2, r4
	bl MOD79_02212794
_0221494C:
	add sb, sb, #1
	ldrsb r8, [r7, sb]
	cmp r8, #0
	bne _022148B4
_0221495C:
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02214968:
	ldr r1, [r4]
	ldr r0, [r4, #4]
	ldr r2, [r1, #0xc]
	ldr r1, [r1, #8]
	sub r5, r2, r0
	mov r0, sl
	mov r2, r5
	bl MOD79_02212F68
	mvn r1, #0
	cmp r0, r1
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r1, [r4, #4]
	cmp r0, r5
	add r0, r1, r0
	str r0, [r4, #4]
	moveq r0, #1
	movne r0, #2
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_022149BC: .word MOD79_02216D74
_022149C0: .word MOD79_02216ADC
_022149C4: .word 0x000002E7
_022149C8: .word MOD79_02216E14
_022149CC: .word 0x000002EE
_022149D0: .word MOD79_02216738
_022149D4: .word MOD79_02216E40
_022149D8: .word MOD79_02216E84
_022149DC: .word 0x0000030D
_022149E0: .word MOD79_02216E94
	arm_func_end MOD79_022147E8

	arm_func_start MOD79_022149E4
MOD79_022149E4: ; 0x022149E4
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	ldr r0, [r6, #0x140]
	cmp r0, #0
	beq _02214A38
	bl MOD04_021EF06C
	mov r4, r0
	cmp r4, #0
	mov r5, #0
	ble _02214A28
_02214A0C:
	ldr r0, [r6, #0x140]
	mov r1, r5
	bl MOD04_021EEFFC
	bl MOD79_02214BF4
	add r5, r5, #1
	cmp r5, r4
	blt _02214A0C
_02214A28:
	ldr r0, [r6, #0x140]
	bl MOD04_021EF074
	mov r0, #0
	str r0, [r6, #0x140]
_02214A38:
	ldr r0, [r6, #0x13c]
	cmp r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r1, [r0, #0x10]
	cmp r1, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	bl MOD79_02215058
	mov r0, #0
	str r0, [r6, #0x13c]
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD79_022149E4

	arm_func_start MOD79_02214A60
MOD79_02214A60: ; 0x02214A60
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x10
	mov r4, r0
	ldr r0, [r4, #0x13c]
	cmp r0, #0
	bne _02214A8C
	ldr r0, _02214BE4 ; =0x02216AE8
	ldr r1, _02214BE8 ; =0x02216ADC
	mov r2, #0
	mov r3, #0x278
	bl __msl_assertion_failed
_02214A8C:
	ldr r0, [r4, #0x13c]
	cmp r0, #0
	addeq sp, sp, #0x10
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	mov r0, #0
	str r0, [r4, #0x144]
	str r0, [r4, #0x148]
	str r0, [r4, #0x14c]
	ldr r0, [r4, #0x13c]
	ldr r0, [r0, #4]
	str r0, [r4, #0x150]
	ldr r0, [r4, #0x13c]
	ldr r0, [r0, #8]
	str r0, [r4, #0x154]
	ldr r0, [r4, #0x13c]
	ldr r0, [r0]
	bl MOD04_021EF06C
	mov r7, r0
	mov r1, r7
	mov r0, #0x10
	mov r2, #0
	bl MOD04_021EF0E4
	str r0, [r4, #0x140]
	ldr r0, [r4, #0x140]
	cmp r0, #0
	addeq sp, sp, #0x10
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r7, #0
	mov r8, #0
	ble _02214B98
	add r6, sp, #0
	mov r5, r8
_02214B14:
	ldr r0, [r4, #0x13c]
	mov r1, r8
	ldr r0, [r0]
	bl MOD04_021EEFFC
	str r5, [r6]
	str r5, [r6, #4]
	str r5, [r6, #8]
	str r5, [r6, #0xc]
	str r0, [sp]
	mov r0, r6
	bl MOD79_02214C5C
	cmp r0, #0
	bne _02214B80
	subs r8, r8, #1
	bmi _02214B68
_02214B50:
	ldr r0, [r4, #0x140]
	mov r1, r8
	bl MOD04_021EEFFC
	bl MOD79_02214BF4
	subs r8, r8, #1
	bpl _02214B50
_02214B68:
	ldr r0, [r4, #0x140]
	bl MOD04_021EF074
	mov r0, #0
	add sp, sp, #0x10
	str r0, [r4, #0x140]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02214B80:
	ldr r0, [r4, #0x140]
	mov r1, r6
	bl MOD04_021EEFA8
	add r8, r8, #1
	cmp r8, r7
	blt _02214B14
_02214B98:
	ldr r0, [r4, #0x13c]
	ldr r0, [r0]
	bl MOD04_021EF06C
	mov r5, r0
	ldr r0, [r4, #0x140]
	bl MOD04_021EF06C
	cmp r5, r0
	beq _02214BCC
	ldr r0, _02214BEC ; =0x02216B1C
	ldr r1, _02214BE8 ; =0x02216ADC
	ldr r3, _02214BF0 ; =0x000002B1
	mov r2, #0
	bl __msl_assertion_failed
_02214BCC:
	mov r0, r4
	bl MOD79_02214D0C
	str r0, [r4, #0x14c]
	mov r0, #1
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02214BE4: .word MOD79_02216AE8
_02214BE8: .word MOD79_02216ADC
_02214BEC: .word MOD79_02216B1C
_02214BF0: .word 0x000002B1
	arm_func_end MOD79_02214A60

	arm_func_start MOD79_02214BF4
MOD79_02214BF4: ; 0x02214BF4
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4]
	ldr r0, [r0]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r0, #1
	bne _02214C30
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02214C24
	bl fclose
_02214C24:
	mov r0, #0
	str r0, [r4, #8]
	ldmia sp!, {r4, pc}
_02214C30:
	cmp r0, #2
	ldmeqia sp!, {r4, pc}
	ldr r0, _02214C50 ; =0x02216D4C
	ldr r1, _02214C54 ; =0x02216ADC
	ldr r3, _02214C58 ; =0x00000269
	mov r2, #0
	bl __msl_assertion_failed
	ldmia sp!, {r4, pc}
	.align 2, 0
_02214C50: .word MOD79_02216D4C
_02214C54: .word MOD79_02216ADC
_02214C58: .word 0x00000269
	arm_func_end MOD79_02214BF4

	arm_func_start MOD79_02214C5C
MOD79_02214C5C: ; 0x02214C5C
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4]
	mvn r0, #0
	ldr r1, [r1]
	str r0, [r4, #4]
	cmp r1, #0
	beq _02214CFC
	cmp r1, #1
	bne _02214CD8
	ldr r0, [r4, #8]
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	mov r1, #0
	mov r2, #2
	bl fseek
	cmp r0, #0
	movne r0, #0
	ldmneia sp!, {r4, pc}
	ldr r0, [r4, #8]
	bl ftell
	str r0, [r4, #0xc]
	ldr r1, [r4, #0xc]
	mvn r0, #0
	cmp r1, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #8]
	bl rewind
	b _02214CFC
_02214CD8:
	cmp r1, #2
	beq _02214CFC
	ldr r0, _02214D04 ; =0x02216D4C
	ldr r1, _02214D08 ; =0x02216ADC
	mov r2, #0
	mov r3, #0x244
	bl __msl_assertion_failed
	mov r0, #0
	ldmia sp!, {r4, pc}
_02214CFC:
	mov r0, #1
	ldmia sp!, {r4, pc}
	.align 2, 0
_02214D04: .word MOD79_02216D4C
_02214D08: .word MOD79_02216ADC
	arm_func_end MOD79_02214C5C

	arm_func_start MOD79_02214D0C
MOD79_02214D0C: ; 0x02214D0C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	ldr r4, [r5, #0x13c]
	cmp r4, #0
	bne _02214D38
	ldr r0, _02214D74 ; =0x02216EA8
	ldr r1, _02214D78 ; =0x02216ADC
	mov r2, #0
	mov r3, #0x20c
	bl __msl_assertion_failed
_02214D38:
	cmp r4, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02214D64
	mov r0, r5
	bl MOD79_02214D7C
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_02214D64:
	mov r0, r5
	bl MOD79_02214F48
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02214D74: .word MOD79_02216EA8
_02214D78: .word MOD79_02216ADC
	arm_func_end MOD79_02214D0C

	arm_func_start MOD79_02214D7C
MOD79_02214D7C: ; 0x02214D7C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	ldr r1, _02214F24 ; =0x0221714C
	mov r8, r0
	ldr r0, [r1]
	ldr r7, [r8, #0x13c]
	cmp r0, #0
	mov r4, #0
	bne _02214DD4
	ldr r0, _02214F28 ; =0x02216EB0
	bl strlen
	ldr r5, _02214F24 ; =0x0221714C
	ldr r3, _02214F2C ; =0x02217148
	add sl, r0, #0x2f
	ldr r2, _02214F30 ; =0x02217144
	add sb, r0, #0x4c
	ldr r1, _02214F34 ; =0x02217140
	add r6, r0, #4
	str r0, [r5]
	str sl, [r3]
	str sb, [r2]
	str r6, [r1]
_02214DD4:
	ldr r0, [r7]
	bl MOD04_021EF06C
	mov r5, r0
	cmp r5, #0
	mov r6, #0
	ble _02214F10
	mov fp, r6
	mov sb, #0x1ec
_02214DF4:
	ldr r0, [r7]
	mov r1, r6
	bl MOD04_021EEFFC
	mov sl, r0
	ldr r0, [sl]
	cmp r0, #0
	bne _02214E34
	ldr r0, _02214F2C ; =0x02217148
	ldr r1, [r0]
	ldr r0, [sl, #4]
	add r4, r4, r1
	bl strlen
	add r1, r4, r0
	ldr r0, [sl, #0xc]
	add r4, r1, r0
	b _02214F04
_02214E34:
	cmp r0, #1
	bne _02214EA0
	ldr r0, _02214F30 ; =0x02217144
	ldr r1, [r0]
	ldr r0, [sl, #4]
	add r4, r4, r1
	bl strlen
	add r4, r4, r0
	ldr r0, [sl, #0xc]
	bl strlen
	add r4, r4, r0
	ldr r0, [sl, #0x10]
	bl strlen
	add r4, r4, r0
	ldr r0, [r8, #0x140]
	mov r1, r6
	bl MOD04_021EEFFC
	movs sl, r0
	bne _02214E94
	ldr r0, _02214F38 ; =0x02216ED8
	ldr r1, _02214F3C ; =0x02216ADC
	mov r2, fp
	mov r3, sb
	bl __msl_assertion_failed
_02214E94:
	ldr r0, [sl, #0xc]
	add r4, r4, r0
	b _02214F04
_02214EA0:
	cmp r0, #2
	bne _02214EE4
	ldr r0, _02214F30 ; =0x02217144
	ldr r1, [r0]
	ldr r0, [sl, #4]
	add r4, r4, r1
	bl strlen
	add r4, r4, r0
	ldr r0, [sl, #0x10]
	bl strlen
	add r4, r4, r0
	ldr r0, [sl, #0x14]
	bl strlen
	add r1, r4, r0
	ldr r0, [sl, #0xc]
	add r4, r1, r0
	b _02214F04
_02214EE4:
	ldr r0, _02214F40 ; =0x02216D4C
	ldr r1, _02214F3C ; =0x02216ADC
	ldr r3, _02214F44 ; =0x000001F9
	mov r2, #0
	bl __msl_assertion_failed
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02214F04:
	add r6, r6, #1
	cmp r6, r5
	blt _02214DF4
_02214F10:
	ldr r0, _02214F34 ; =0x02217140
	ldr r0, [r0]
	add r0, r4, r0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02214F24: .word 0x0221714C
_02214F28: .word MOD79_02216EB0
_02214F2C: .word 0x02217148
_02214F30: .word 0x02217144
_02214F34: .word 0x02217140
_02214F38: .word MOD79_02216ED8
_02214F3C: .word MOD79_02216ADC
_02214F40: .word MOD79_02216D4C
_02214F44: .word 0x000001F9
	arm_func_end MOD79_02214D7C

	arm_func_start MOD79_02214F48
MOD79_02214F48: ; 0x02214F48
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	ldr sl, [r0, #0x13c]
	mov r6, #0
	ldr r0, [sl]
	bl MOD04_021EF06C
	movs r7, r0
	addeq sp, sp, #4
	moveq r0, r6
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	cmp r7, #0
	mov r8, r6
	ble _02214FE4
	ldr fp, _02214FF4 ; =0x02216EE0
	mov r5, r8
	mov r4, #0x1b0
_02214F88:
	ldr r0, [sl]
	mov r1, r8
	bl MOD04_021EEFFC
	mov sb, r0
	ldr r0, [sb]
	cmp r0, #0
	beq _02214FB8
	ldr r1, _02214FF8 ; =0x02216ADC
	mov r0, fp
	mov r2, r5
	mov r3, r4
	bl __msl_assertion_failed
_02214FB8:
	ldr r0, [sb, #4]
	bl strlen
	add r8, r8, #1
	ldr r1, [sb, #0xc]
	add r2, r6, r0
	ldr r0, [sb, #0x14]
	add r1, r2, r1
	add r0, r1, r0, lsl #1
	cmp r8, r7
	add r6, r0, #1
	blt _02214F88
_02214FE4:
	sub r0, r7, #1
	add r0, r6, r0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02214FF4: .word MOD79_02216EE0
_02214FF8: .word MOD79_02216ADC
	arm_func_end MOD79_02214F48

	arm_func_start MOD79_02214FFC
MOD79_02214FFC: ; 0x02214FFC
	stmdb sp!, {r4, lr}
	ldr r4, [r0, #0x13c]
	cmp r4, #0
	bne _02215020
	ldr r0, _02215040 ; =0x02216EA8
	ldr r1, _02215044 ; =0x02216ADC
	ldr r3, _02215048 ; =0x00000192
	mov r2, #0
	bl __msl_assertion_failed
_02215020:
	cmp r4, #0
	ldreq r0, _0221504C ; =0x02216EF8
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #0xc]
	cmp r0, #0
	ldrne r0, _02215050 ; =0x02216EFC
	ldreq r0, _02215054 ; =0x02216F40
	ldmia sp!, {r4, pc}
	.align 2, 0
_02215040: .word MOD79_02216EA8
_02215044: .word MOD79_02216ADC
_02215048: .word 0x00000192
_0221504C: .word MOD79_02216EF8
_02215050: .word MOD79_02216EFC
_02215054: .word MOD79_02216F40
	arm_func_end MOD79_02214FFC

	arm_func_start MOD79_02215058
MOD79_02215058: ; 0x02215058
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4]
	bl MOD04_021EF074
	mov r0, r4
	bl MOD04_021DD82C
	ldmia sp!, {r4, pc}
	arm_func_end MOD79_02215058

	arm_func_start MOD79_02215074
MOD79_02215074: ; 0x02215074
	ldr r0, [r0, #0x10]
	bx lr
	arm_func_end MOD79_02215074

	arm_func_start MOD79_0221507C
MOD79_0221507C: ; 0x0221507C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr ip, _02215170 ; =0x00002008
	sub sp, sp, ip
	mov r5, r0
	bl MOD04_021F025C
	mov r4, r0
	mov r1, #0
	mov r8, #0x2000
	add r7, sp, #4
	add r6, sp, #0
	b _02215144
_022150A8:
	mov r0, r5
	mov r1, r7
	mov r2, r6
	str r8, [sp]
	bl MOD79_02212FF0
	cmp r0, #3
	ldreq ip, _02215170 ; =0x00002008
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r0, #1
	ldreq ip, _02215170 ; =0x00002008
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r0, #2
	bne _0221511C
	mov r0, #1
	str r0, [r5, #0xfc]
	ldr r1, [r5, #0x104]
	cmp r1, #0
	ldrle ip, _02215170 ; =0x00002008
	addle sp, sp, ip
	ldmleia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r0, [r5, #0x100]
	ldr ip, _02215170 ; =0x00002008
	cmp r0, r1
	movlt r0, #0xf
	add sp, sp, ip
	strlt r0, [r5, #0x38]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_0221511C:
	ldr r2, [sp]
	mov r0, r5
	mov r1, r7
	bl MOD79_02215640
	cmp r0, #0
	ldreq ip, _02215170 ; =0x00002008
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	bl MOD04_021F025C
	sub r1, r0, r4
_02215144:
	ldr r0, [r5, #0xfc]
	cmp r0, #0
	ldrne ip, _02215170 ; =0x00002008
	addne sp, sp, ip
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r0, [r5, #0x158]
	cmp r1, r0
	blo _022150A8
	ldr ip, _02215170 ; =0x00002008
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_02215170: .word 0x00002008
	arm_func_end MOD79_0221507C

	arm_func_start MOD79_02215174
MOD79_02215174: ; 0x02215174
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	ldr ip, _02215618 ; =0x00001018
	sub sp, sp, ip
	mov r3, #0x1000
	add r1, sp, #0x13
	add r2, sp, #4
	mov r6, r0
	str r3, [sp, #4]
	bl MOD79_02212FF0
	mov r4, r0
	cmp r4, #3
	ldreq ip, _02215618 ; =0x00001018
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	cmp r4, #1
	bne _022151CC
	ldr r1, [r6, #0x84]
	ldr r0, [r6, #0x80]
	cmp r1, r0
	ldreq ip, _02215618 ; =0x00001018
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_022151CC:
	cmp r4, #0
	bne _022151F4
	ldr r2, [sp, #4]
	add r1, sp, #0x13
	add r0, r6, #0x74
	bl MOD79_02212794
	cmp r0, #0
	ldreq ip, _02215618 ; =0x00001018
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_022151F4:
	ldr r2, [r6, #0x84]
	ldr r0, [r6, #0x78]
	ldr r1, _0221561C ; =0x02216F64
	add r5, r0, r2
	mov r0, r5
	str r2, [r6, #0xf4]
	bl strstr
	cmp r0, #0
	bne _02215224
	ldr r1, _02215620 ; =0x02216F6C
	mov r0, r5
	bl strstr
_02215224:
	cmp r0, #0
	beq _022155E0
	mov r1, #0
	strb r1, [r0, #2]
	ldr r7, [r6, #0x78]
	add r3, r0, #2
	ldr r1, [r6, #0x80]
	sub r2, r3, r7
	str r2, [r6, #0x80]
	ldr r2, [r6, #0x78]
	add r4, r0, #4
	sub r0, r3, r2
	str r0, [r6, #0xf8]
	ldr r0, [r6, #0xf8]
	sub r8, r4, r7
	str r0, [r6, #0x84]
	ldr r2, [r6, #0xec]
	ldr r3, _02215624 ; =0x51EB851F
	mov r0, r2, lsr #0x1f
	smull r2, r7, r3, r2
	mov r7, r7, asr #5
	add r7, r0, r7
	cmp r7, #1
	sub sl, r1, r8
	bne _022152DC
	cmp sl, #0
	beq _022152B0
	ldr r0, [r6, #0x78]
	mov r1, r4
	add r2, sl, #1
	bl memmove
	str sl, [r6, #0x80]
	mov r0, #0
	str r0, [r6, #0x84]
	b _022152B8
_022152B0:
	add r0, r6, #0x74
	bl MOD79_0221262C
_022152B8:
	mov r1, #0
	mov r3, #6
	mov r0, r6
	mov r2, r1
	str r3, [r6, #0x10]
	bl MOD79_02212E00
	ldr ip, _02215618 ; =0x00001018
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_022152DC:
	cmp r7, #3
	bne _02215448
	ldr r0, [r6, #0x10c]
	cmp r0, #0xa
	ldrgt ip, _02215618 ; =0x00001018
	movgt r0, #1
	strgt r0, [r6, #0xfc]
	movgt r0, #0xb
	addgt sp, sp, ip
	strgt r0, [r6, #0x38]
	ldmgtia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldr r1, _02215628 ; =0x02216F70
	mov r0, r5
	bl strstr
	cmp r0, #0
	beq _02215448
	add r4, r0, #9
	ldr r1, _0221562C ; =0x0210430C
	mov r2, #0
	b _02215330
_0221532C:
	add r4, r4, #1
_02215330:
	ldrsb r0, [r4]
	cmp r0, #0
	blt _02215344
	cmp r0, #0x80
	blt _0221534C
_02215344:
	mov r0, r2
	b _02215358
_0221534C:
	mov r0, r0, lsl #1
	ldrh r0, [r1, r0]
	and r0, r0, #0x100
_02215358:
	cmp r0, #0
	bne _0221532C
	mov r3, r4
	ldr r1, _0221562C ; =0x0210430C
	mov r2, #0
	b _02215374
_02215370:
	add r3, r3, #1
_02215374:
	ldrsb r0, [r3]
	cmp r0, #0
	beq _022153AC
	cmp r0, #0
	blt _02215390
	cmp r0, #0x80
	blt _02215398
_02215390:
	mov r0, r2
	b _022153A4
_02215398:
	mov r0, r0, lsl #1
	ldrh r0, [r1, r0]
	and r0, r0, #0x100
_022153A4:
	cmp r0, #0
	beq _02215370
_022153AC:
	mov r0, #0
	strb r0, [r3]
	ldrsb r0, [r4]
	cmp r0, #0x2f
	bne _0221541C
	ldr r0, [r6, #0x18]
	bl strlen
	mov r5, r0
	mov r0, r4
	bl strlen
	add r1, r5, #0xe
	add r0, r1, r0
	bl MOD04_021DD860
	str r0, [r6, #0x108]
	ldr r0, [r6, #0x108]
	ldr r1, _02215630 ; =0x02216F7C
	cmp r0, #0
	moveq r0, #1
	streq r0, [r6, #0xfc]
	streq r0, [r6, #0x38]
	str r4, [sp]
	ldrh r3, [r6, #0x20]
	ldr r0, [r6, #0x108]
	ldr r2, [r6, #0x18]
	bl sprintf
	ldr ip, _02215618 ; =0x00001018
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_0221541C:
	mov r0, r4
	bl MOD04_021F0208
	str r0, [r6, #0x108]
	ldr r0, [r6, #0x108]
	ldr ip, _02215618 ; =0x00001018
	cmp r0, #0
	moveq r0, #1
	streq r0, [r6, #0xfc]
	add sp, sp, ip
	streq r0, [r6, #0x38]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_02215448:
	ldr r1, _02215634 ; =0x02216F8C
	mov r0, r5
	bl strstr
	movs sb, r0
	beq _02215530
	ldr r7, _02215638 ; =0x0221673C
	add r3, sp, #8
	mov r2, #5
_02215468:
	ldrb r1, [r7], #1
	ldrb r0, [r7], #1
	subs r2, r2, #1
	strb r1, [r3], #1
	strb r0, [r3], #1
	bne _02215468
	ldrb r1, [r7]
	add r8, sb, #0x10
	add r0, sp, #8
	mov r7, r8
	strb r1, [r3]
	bl strlen
	b _022154A0
_0221549C:
	add r7, r7, #1
_022154A0:
	cmp r7, #0
	beq _022154CC
	ldrsb r1, [r7]
	cmp r1, #0
	beq _022154CC
	cmp r1, #0xa
	beq _022154CC
	cmp r1, #0xd
	beq _022154CC
	cmp r1, #0x20
	bne _0221549C
_022154CC:
	sub r2, r7, r8
	cmp r2, r0
	ldrgt ip, _02215618 ; =0x00001018
	movgt r0, #1
	strgt r0, [r6, #0xfc]
	movgt r0, #0x10
	addgt sp, sp, ip
	strgt r0, [r6, #0x38]
	ldmgtia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	cmp r0, r2
	bne _02215524
	add r1, sp, #8
	mov r0, r8
	bl strncmp
	cmp r0, #0
	ldrge ip, _02215618 ; =0x00001018
	movge r0, #1
	strge r0, [r6, #0xfc]
	movge r0, #0x10
	addge sp, sp, ip
	strge r0, [r6, #0x38]
	ldmgeia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_02215524:
	mov r0, r8
	bl atol
	str r0, [r6, #0x104]
_02215530:
	ldr r1, _0221563C ; =0x02216F9C
	mov r0, r5
	bl strstr
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	str r0, [r6, #0x110]
	ldr r0, [r6, #0x110]
	cmp r0, #0
	movne r0, #0
	strneb r0, [r6, #0x114]
	strne r0, [r6, #0x120]
	strne r0, [r6, #0x124]
	strne r0, [r6, #0x128]
	ldr r0, [r6, #0xc]
	sub r0, r0, #3
	cmp r0, #1
	ldrls ip, _02215618 ; =0x00001018
	movls r0, #1
	addls sp, sp, ip
	strls r0, [r6, #0xfc]
	ldmlsia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	mov r0, #8
	str r0, [r6, #0x10]
	cmp sb, #0
	beq _022155B4
	ldr r0, [r6, #0x104]
	cmp r0, #0
	ldreq ip, _02215618 ; =0x00001018
	moveq r0, #1
	addeq sp, sp, ip
	streq r0, [r6, #0xfc]
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_022155B4:
	cmp sl, #0
	ldrle ip, _02215618 ; =0x00001018
	addle sp, sp, ip
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	mov r0, r6
	mov r1, r4
	mov r2, sl
	bl MOD79_02215640
	ldr ip, _02215618 ; =0x00001018
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_022155E0:
	cmp r4, #2
	ldrne ip, _02215618 ; =0x00001018
	addne sp, sp, ip
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	mov r0, #1
	str r0, [r6, #0xfc]
	mov r0, #7
	str r0, [r6, #0x38]
	ldr r0, [r6, #0x48]
	bl MOD04_021EFB28
	str r0, [r6, #0x4c]
	ldr ip, _02215618 ; =0x00001018
	add sp, sp, ip
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_02215618: .word 0x00001018
_0221561C: .word MOD79_02216F64
_02215620: .word MOD79_02216F6C
_02215624: .word 0x51EB851F
_02215628: .word MOD79_02216F70
_0221562C: .word 0x0210430C
_02215630: .word MOD79_02216F7C
_02215634: .word MOD79_02216F8C
_02215638: .word MOD79_0221673C
_0221563C: .word MOD79_02216F9C
	arm_func_end MOD79_02215174

	arm_func_start MOD79_02215640
MOD79_02215640: ; 0x02215640
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	movs r6, r0
	mov r5, r1
	mov r4, r2
	bne _0221566C
	ldr r0, _02215884 ; =0x02216FB8
	ldr r1, _02215888 ; =0x02216FC4
	ldr r3, _0221588C ; =0x0000035D
	mov r2, #0
	bl __msl_assertion_failed
_0221566C:
	cmp r5, #0
	bne _02215688
	ldr r0, _02215890 ; =0x02216FD4
	ldr r1, _02215888 ; =0x02216FC4
	ldr r3, _02215894 ; =0x0000035E
	mov r2, #0
	bl __msl_assertion_failed
_02215688:
	cmp r4, #0
	bgt _022156A4
	ldr r0, _02215898 ; =0x02216FDC
	ldr r1, _02215888 ; =0x02216FC4
	ldr r3, _0221589C ; =0x0000035F
	mov r2, #0
	bl __msl_assertion_failed
_022156A4:
	ldr r0, [r6, #0x110]
	cmp r0, #0
	beq _0221586C
	cmp r4, #0
	ble _02215860
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #1
	add r8, r6, #0x124
	mov sl, #0xa
	mov r7, #0
	str r0, [sp]
	mov fp, #3
_022156D8:
	ldr r0, [r6, #0x128]
	cmp r0, #0
	bne _02215780
	mov r0, r5
	mov r1, sl
	bl strchr
	movs sb, r0
	beq _02215764
	mov r0, r6
	mov r1, r5
	sub r2, sb, r5
	bl MOD79_022158A8
	add r1, sb, #1
	sub r2, r1, r5
	mov r0, r6
	mov r5, r1
	sub r4, r4, r2
	bl MOD79_02215984
	str r0, [r6, #0x124]
	ldr r1, [r6, #0x124]
	mvn r0, #0
	cmp r1, r0
	bne _02215750
	mov r0, #1
	str r0, [r6, #0xfc]
	mov r0, #7
	str r0, [r6, #0x38]
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02215750:
	cmp r1, #0
	ldrne r0, [sp]
	streq fp, [r6, #0x128]
	strne r0, [r6, #0x128]
	b _02215858
_02215764:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD79_022158A8
	add sp, sp, #0xc
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02215780:
	cmp r0, #1
	bne _022157DC
	ldr sb, [r6, #0x124]
	mov r0, r6
	cmp sb, r4
	movge sb, r4
	mov r1, r5
	mov r2, sb
	bl MOD79_022159E4
	cmp r0, #0
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, [r8]
	add r5, r5, sb
	sub r0, r0, sb
	str r0, [r8]
	ldr r0, [r6, #0x124]
	sub r4, r4, sb
	cmp r0, #0
	ldreq r0, [sp, #4]
	streq r0, [r6, #0x128]
	b _02215858
_022157DC:
	cmp r0, #2
	bne _02215824
	mov r0, r5
	mov r1, sl
	bl strchr
	cmp r0, #0
	addeq sp, sp, #0xc
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	strb r7, [r6, #0x114]
	str r7, [r6, #0x120]
	add r0, r0, #1
	sub r1, r0, r5
	str r7, [r6, #0x124]
	mov r5, r0
	str r7, [r6, #0x128]
	sub r4, r4, r1
	b _02215858
_02215824:
	cmp r0, #3
	moveq r0, #1
	addeq sp, sp, #0xc
	streq r0, [r6, #0xfc]
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, _022158A0 ; =0x02216FE4
	ldr r1, _02215888 ; =0x02216FC4
	ldr r3, _022158A4 ; =0x000003E3
	mov r2, #0
	bl __msl_assertion_failed
	add sp, sp, #0xc
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_02215858:
	cmp r4, #0
	bgt _022156D8
_02215860:
	add sp, sp, #0xc
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_0221586C:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD79_022159E4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_02215884: .word MOD79_02216FB8
_02215888: .word MOD79_02216FC4
_0221588C: .word 0x0000035D
_02215890: .word MOD79_02216FD4
_02215894: .word 0x0000035E
_02215898: .word MOD79_02216FDC
_0221589C: .word 0x0000035F
_022158A0: .word MOD79_02216FE4
_022158A4: .word 0x000003E3
	arm_func_end MOD79_02215640

	arm_func_start MOD79_022158A8
MOD79_022158A8: ; 0x022158A8
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	movs r4, r0
	mov r7, r1
	mov r6, r2
	bne _022158D4
	ldr r0, _0221596C ; =0x02216FB8
	ldr r1, _02215970 ; =0x02216FC4
	ldr r3, _02215974 ; =0x00000333
	mov r2, #0
	bl __msl_assertion_failed
_022158D4:
	cmp r7, #0
	bne _022158F0
	ldr r0, _02215978 ; =0x02216FD4
	ldr r1, _02215970 ; =0x02216FC4
	mov r2, #0
	mov r3, #0x334
	bl __msl_assertion_failed
_022158F0:
	cmp r6, #0
	bge _0221590C
	ldr r0, _0221597C ; =0x02216FE8
	ldr r1, _02215970 ; =0x02216FC4
	ldr r3, _02215980 ; =0x00000335
	mov r2, #0
	bl __msl_assertion_failed
_0221590C:
	cmp r6, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	ldr r3, [r4, #0x120]
	cmp r3, #0xa
	addge sp, sp, #4
	ldmgeia sp!, {r4, r5, r6, r7, pc}
	rsb r5, r3, #0xa
	cmp r5, r6
	movge r5, r6
	add r0, r4, #0x114
	mov r1, r7
	mov r2, r5
	add r0, r0, r3
	bl memcpy
	ldr r0, [r4, #0x120]
	mov r1, #0
	add r0, r0, r5
	str r0, [r4, #0x120]
	ldr r0, [r4, #0x120]
	add r0, r4, r0
	strb r1, [r0, #0x114]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_0221596C: .word MOD79_02216FB8
_02215970: .word MOD79_02216FC4
_02215974: .word 0x00000333
_02215978: .word MOD79_02216FD4
_0221597C: .word MOD79_02216FE8
_02215980: .word 0x00000335
	arm_func_end MOD79_022158A8

	arm_func_start MOD79_02215984
MOD79_02215984: ; 0x02215984
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r1, [r0, #0x120]
	add r4, r0, #0x114
	cmp r1, #0
	bne _022159B0
	ldr r0, _022159D4 ; =0x02216FF4
	ldr r1, _022159D8 ; =0x02216FC4
	ldr r3, _022159DC ; =0x00000321
	mov r2, #0
	bl __msl_assertion_failed
_022159B0:
	ldr r1, _022159E0 ; =0x02216FF8
	add r2, sp, #0
	mov r0, r4
	bl sscanf
	cmp r0, #1
	mvnne r0, #0
	ldreq r0, [sp]
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_022159D4: .word MOD79_02216FF4
_022159D8: .word MOD79_02216FC4
_022159DC: .word 0x00000321
_022159E0: .word MOD79_02216FF8
	arm_func_end MOD79_02215984

	arm_func_start MOD79_022159E4
MOD79_022159E4: ; 0x022159E4
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #0x100]
	mov lr, #0
	add r0, r0, r2
	str r0, [r4, #0x100]
	ldr r3, [r4, #0x100]
	ldr r0, [r4, #0x104]
	mov ip, lr
	cmp r3, r0
	beq _02215A1C
	ldr r0, [r4, #0x130]
	cmp r0, #0
	beq _02215A24
_02215A1C:
	mov r0, #1
	str r0, [r4, #0xfc]
_02215A24:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _02215A50
	add r0, r4, #0xbc
	bl MOD79_02212794
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr lr, [r4, #0xc0]
	ldr ip, [r4, #0xc8]
	b _02215A90
_02215A50:
	cmp r0, #1
	bne _02215A84
	cmp r2, #0
	beq _02215A78
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #0xd
	str r0, [r4, #0x38]
	mov r0, #0
	ldmia sp!, {r4, pc}
_02215A78:
	mov lr, r1
	mov ip, r2
	b _02215A90
_02215A84:
	cmp r0, #2
	moveq lr, r1
	moveq ip, r2
_02215A90:
	mov r0, r4
	mov r1, lr
	mov r2, ip
	bl MOD79_02212E00
	mov r0, #1
	ldmia sp!, {r4, pc}
	arm_func_end MOD79_022159E4

	arm_func_start MOD79_02215AA8
MOD79_02215AA8: ; 0x02215AA8
	stmdb sp!, {r4, r5, lr}
	ldr ip, _02215BD0 ; =0x00000404
	sub sp, sp, ip
	mov r3, #0x400
	add r1, sp, #4
	add r2, sp, #0
	mov r4, r0
	str r3, [sp]
	bl MOD79_02212FF0
	mov r5, r0
	cmp r5, #3
	ldreq ip, _02215BD0 ; =0x00000404
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, pc}
	cmp r5, #1
	bne _02215B00
	ldr r1, [r4, #0x84]
	ldr r0, [r4, #0x80]
	cmp r1, r0
	ldreq ip, _02215BD0 ; =0x00000404
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, pc}
_02215B00:
	cmp r5, #0
	bne _02215B28
	ldr r2, [sp]
	add r1, sp, #4
	add r0, r4, #0x74
	bl MOD79_02212794
	cmp r0, #0
	ldreq ip, _02215BD0 ; =0x00000404
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, pc}
_02215B28:
	ldr r0, [r4, #0x78]
	ldr r1, _02215BD4 ; =0x02216FFC
	bl strstr
	cmp r0, #0
	beq _02215B98
	mov r1, #0
	strb r1, [r0]
	ldr r1, [r4, #0x78]
	sub r5, r0, r1
	add r1, r5, #1
	mov r0, r4
	str r1, [r4, #0xf8]
	bl MOD79_02215BD8
	cmp r0, #0
	ldreq ip, _02215BD0 ; =0x00000404
	addeq sp, sp, ip
	ldmeqia sp!, {r4, r5, pc}
	add r3, r5, #2
	mov r1, #0
	str r3, [r4, #0x84]
	mov r3, #7
	mov r0, r4
	mov r2, r1
	str r3, [r4, #0x10]
	bl MOD79_02212E00
	ldr ip, _02215BD0 ; =0x00000404
	add sp, sp, ip
	ldmia sp!, {r4, r5, pc}
_02215B98:
	cmp r5, #2
	ldrne ip, _02215BD0 ; =0x00000404
	addne sp, sp, ip
	ldmneia sp!, {r4, r5, pc}
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #7
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	str r0, [r4, #0x4c]
	ldr ip, _02215BD0 ; =0x00000404
	add sp, sp, ip
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02215BD0: .word 0x00000404
_02215BD4: .word MOD79_02216FFC
	arm_func_end MOD79_02215AA8

	arm_func_start MOD79_02215BD8
MOD79_02215BD8: ; 0x02215BD8
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x18
	movs r4, r0
	bne _02215BFC
	ldr r0, _02215D0C ; =0x02216FB8
	ldr r1, _02215D10 ; =0x02216FC4
	ldr r3, _02215D14 ; =0x0000024E
	mov r2, #0
	bl __msl_assertion_failed
_02215BFC:
	ldr r0, [r4, #0x80]
	cmp r0, #0
	bgt _02215C1C
	ldr r0, _02215D18 ; =0x02217000
	ldr r1, _02215D10 ; =0x02216FC4
	ldr r3, _02215D1C ; =0x0000024F
	mov r2, #0
	bl __msl_assertion_failed
_02215C1C:
	add r1, sp, #0x10
	str r1, [sp]
	add r0, sp, #0x14
	str r0, [sp, #4]
	ldr r0, [r4, #0x78]
	ldr r1, _02215D20 ; =0x02217020
	add r2, sp, #8
	add r3, sp, #0xc
	bl sscanf
	mov r3, #0
	mov ip, #1
	ldr r2, _02215D24 ; =0x0210430C
	b _02215C5C
_02215C50:
	ldr r1, [sp, #0x14]
	add r1, r1, #1
	str r1, [sp, #0x14]
_02215C5C:
	ldr lr, [r4, #0x78]
	ldr r1, [sp, #0x14]
	ldrsb lr, [lr, r1]
	cmp lr, #0
	beq _02215CA0
	mov r1, ip
	cmp lr, #0
	blt _02215C84
	cmp lr, #0x80
	movlt r1, r3
_02215C84:
	cmp r1, #0
	movne r1, r3
	moveq r1, lr, lsl #1
	ldreqh r1, [r2, r1]
	andeq r1, r1, #0x100
	cmp r1, #0
	bne _02215C50
_02215CA0:
	cmp r0, #3
	bne _02215CC8
	ldr r1, [sp, #8]
	cmp r1, #1
	blt _02215CC8
	ldr r0, [sp, #0x10]
	cmp r0, #0x64
	blt _02215CC8
	cmp r0, #0x258
	blt _02215CE4
_02215CC8:
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #7
	str r0, [r4, #0x38]
	add sp, sp, #0x18
	mov r0, #0
	ldmia sp!, {r4, pc}
_02215CE4:
	str r1, [r4, #0xe4]
	ldr r1, [sp, #0xc]
	mov r0, #1
	str r1, [r4, #0xe8]
	ldr r1, [sp, #0x10]
	str r1, [r4, #0xec]
	ldr r1, [sp, #0x14]
	str r1, [r4, #0xf0]
	add sp, sp, #0x18
	ldmia sp!, {r4, pc}
	.align 2, 0
_02215D0C: .word MOD79_02216FB8
_02215D10: .word MOD79_02216FC4
_02215D14: .word 0x0000024E
_02215D18: .word MOD79_02217000
_02215D1C: .word 0x0000024F
_02215D20: .word MOD79_02217020
_02215D24: .word 0x0210430C
	arm_func_end MOD79_02215BD8

	arm_func_start MOD79_02215D28
MOD79_02215D28: ; 0x02215D28
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	mov r2, #0
	ldr r0, [r4, #0x48]
	add r1, sp, #0
	mov r3, r2
	bl MOD04_021EFF5C
	mvn r1, #0
	cmp r0, r1
	bne _02215D78
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #5
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	add sp, sp, #8
	str r0, [r4, #0x4c]
	ldmia sp!, {r4, pc}
_02215D78:
	ldr r0, [sp]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r1, #0
	mov r3, #6
	mov r0, r4
	mov r2, r1
	str r3, [r4, #0x10]
	bl MOD79_02212E00
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	arm_func_end MOD79_02215D28

	arm_func_start MOD79_02215DA8
MOD79_02215DA8: ; 0x02215DA8
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	ldr r4, [r6, #0x148]
	bl MOD79_022140D4
	movs r5, r0
	bne _02215DF8
	ldr r0, [r6, #0xfc]
	cmp r0, #0
	beq _02215DD8
	ldr r0, [r6, #0x38]
	cmp r0, #0
	bne _02215DEC
_02215DD8:
	ldr r0, _02215E38 ; =0x02217030
	ldr r1, _02215E3C ; =0x02216FC4
	mov r2, #0
	mov r3, #0x200
	bl __msl_assertion_failed
_02215DEC:
	mov r0, r6
	bl MOD79_022149E4
	ldmia sp!, {r4, r5, r6, pc}
_02215DF8:
	ldr r0, [r6, #0x148]
	cmp r4, r0
	beq _02215E0C
	mov r0, r6
	bl MOD79_02212D90
_02215E0C:
	cmp r5, #1
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, r6
	bl MOD79_022149E4
	mov r1, #0
	mov r3, #5
	mov r0, r6
	mov r2, r1
	str r3, [r6, #0x10]
	bl MOD79_02212E00
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_02215E38: .word MOD79_02217030
_02215E3C: .word MOD79_02216FC4
	arm_func_end MOD79_02215DA8

	arm_func_start MOD79_02215E40
MOD79_02215E40: ; 0x02215E40
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x14
	mov r5, r0
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	bne _02216020
	ldr r0, [r5, #0x13c]
	add r4, r5, #0x50
	cmp r0, #0
	ldrne r1, _02216080 ; =0x0221705C
	bne _02215E7C
	ldr r0, [r5, #0xc]
	cmp r0, #3
	ldreq r1, _02216084 ; =0x02217064
	ldrne r1, _02216088 ; =0x0221706C
_02215E7C:
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
	ldr r0, [r5, #0x15c]
	cmp r0, #0
	bne _02215EA4
	ldr r0, _0221608C ; =0x02217128
	ldr r0, [r0]
	cmp r0, #0
	beq _02215EB8
_02215EA4:
	ldr r1, [r5, #0x14]
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
	b _02215EC8
_02215EB8:
	ldr r1, [r5, #0x24]
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
_02215EC8:
	ldr r1, _02216090 ; =0x02217074
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
	ldrh r0, [r5, #0x20]
	cmp r0, #0x50
	bne _02215EF8
	ldr r2, [r5, #0x18]
	ldr r1, _02216094 ; =0x02217080
	mov r0, r4
	bl MOD79_02212700
	b _02215F40
_02215EF8:
	ldr r1, _02216098 ; =0x02217088
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
	ldr r1, [r5, #0x18]
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
	mov r0, r4
	mov r1, #0x3a
	bl MOD79_022126A4
	ldrh r1, [r5, #0x20]
	mov r0, r4
	bl MOD79_0221266C
	mov r0, r4
	ldr r1, _0221609C ; =0x02216FFC
	mov r2, #2
	bl MOD79_02212794
_02215F40:
	ldr r0, [r5, #0x28]
	cmp r0, #0
	beq _02215F5C
	ldr r1, _022160A0 ; =0x02217090
	bl strstr
	cmp r0, #0
	bne _02215F6C
_02215F5C:
	ldr r1, _022160A0 ; =0x02217090
	ldr r2, _022160A4 ; =0x0221709C
	mov r0, r4
	bl MOD79_02212700
_02215F6C:
	ldr r0, [r5, #0x34]
	cmp r0, #0
	beq _02215F8C
	ldr r1, _022160A8 ; =0x022170AC
	ldr r2, _022160AC ; =0x022170B8
	mov r0, r4
	bl MOD79_02212700
	b _02215F9C
_02215F8C:
	ldr r1, _022160A8 ; =0x022170AC
	ldr r2, _022160B0 ; =0x022170C4
	mov r0, r4
	bl MOD79_02212700
_02215F9C:
	ldr r0, [r5, #0x13c]
	cmp r0, #0
	beq _02215FE0
	ldr r2, [r5, #0x14c]
	ldr r1, _022160B4 ; =0x022170CC
	add r0, sp, #0
	bl sprintf
	ldr r1, _022160B8 ; =0x022170D0
	add r2, sp, #0
	mov r0, r4
	bl MOD79_02212700
	mov r0, r5
	bl MOD79_02214FFC
	mov r2, r0
	ldr r1, _022160BC ; =0x022170E0
	mov r0, r4
	bl MOD79_02212700
_02215FE0:
	ldr r1, [r5, #0x28]
	cmp r1, #0
	beq _02215FF8
	mov r0, r4
	mov r2, #0
	bl MOD79_02212794
_02215FF8:
	ldr r1, _0221609C ; =0x02216FFC
	mov r0, r4
	mov r2, #2
	bl MOD79_02212794
	add r0, r5, #0x50
	cmp r4, r0
	beq _02216020
	ldr r1, [r4, #4]
	ldr r2, [r4, #0xc]
	bl MOD79_02212794
_02216020:
	mov r0, r5
	bl MOD79_02212554
	cmp r0, #0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, [r5, #0x60]
	ldr r0, [r5, #0x5c]
	cmp r1, r0
	addlt sp, sp, #0x14
	ldmltia sp!, {r4, r5, pc}
	add r0, r5, #0x50
	bl MOD79_0221262C
	ldr r0, [r5, #0x13c]
	mov r1, #0
	cmp r0, #0
	movne r0, #4
	strne r0, [r5, #0x10]
	moveq r0, #5
	streq r0, [r5, #0x10]
	mov r0, r5
	mov r2, r1
	bl MOD79_02212E00
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02216080: .word MOD79_0221705C
_02216084: .word MOD79_02217064
_02216088: .word MOD79_0221706C
_0221608C: .word 0x02217128
_02216090: .word MOD79_02217074
_02216094: .word MOD79_02217080
_02216098: .word MOD79_02217088
_0221609C: .word MOD79_02216FFC
_022160A0: .word MOD79_02217090
_022160A4: .word MOD79_0221709C
_022160A8: .word MOD79_022170AC
_022160AC: .word MOD79_022170B8
_022160B0: .word MOD79_022170C4
_022160B4: .word MOD79_022170CC
_022160B8: .word MOD79_022170D0
_022160BC: .word MOD79_022170E0
	arm_func_end MOD79_02215E40

	arm_func_start MOD79_022160C0
MOD79_022160C0: ; 0x022160C0
	stmdb sp!, {r4, lr}
	ldr ip, _02216208 ; =0x00000408
	sub sp, sp, ip
	mov r4, r0
	ldr r1, [r4, #0x168]
	cmp r1, #0
	bne _02216130
	ldr r0, [r4, #0x14]
	ldr r1, _0221620C ; =0x022170F0
	mov r2, #8
	bl strncmp
	cmp r0, #0
	ldreq ip, _02216208 ; =0x00000408
	moveq r0, #1
	streq r0, [r4, #0xfc]
	moveq r0, #0x11
	addeq sp, sp, ip
	streq r0, [r4, #0x38]
	ldmeqia sp!, {r4, pc}
	mov r1, #0
	mov r3, #3
	mov r0, r4
	mov r2, r1
	str r3, [r4, #0x10]
	bl MOD79_02212E00
	ldr ip, _02216208 ; =0x00000408
	add sp, sp, ip
	ldmia sp!, {r4, pc}
_02216130:
	ldr r1, [r4, #0x170]
	cmp r1, #0
	beq _0221615C
	mov r1, #0
	mov r3, #3
	mov r2, r1
	str r3, [r4, #0x10]
	bl MOD79_02212E00
	ldr ip, _02216208 ; =0x00000408
	add sp, sp, ip
	ldmia sp!, {r4, pc}
_0221615C:
	ldr r1, [r4, #0x16c]
	cmp r1, #0
	bne _0221619C
	ldr r2, [r4, #0x174]
	add r1, r4, #0x164
	.word 0xE12FFF32
	cmp r0, #3
	bne _0221619C
	ldr r0, _02216210 ; =0x02216FE4
	ldr r1, _02216214 ; =0x02216FC4
	ldr r3, _02216218 ; =0x00000146
	mov r2, #0
	bl __msl_assertion_failed
	ldr ip, _02216208 ; =0x00000408
	add sp, sp, ip
	ldmia sp!, {r4, pc}
_0221619C:
	ldr r1, [r4, #0x60]
	ldr r0, [r4, #0x5c]
	cmp r1, r0
	bge _022161E4
	mov r0, r4
	bl MOD79_02212554
	cmp r0, #0
	ldreq ip, _02216208 ; =0x00000408
	addeq sp, sp, ip
	ldmeqia sp!, {r4, pc}
	ldr r1, [r4, #0x60]
	ldr r0, [r4, #0x5c]
	cmp r1, r0
	ldrlt ip, _02216208 ; =0x00000408
	addlt sp, sp, ip
	ldmltia sp!, {r4, pc}
	add r0, r4, #0x50
	bl MOD79_0221262C
_022161E4:
	mov r3, #0x400
	add r1, sp, #4
	add r2, sp, #0
	mov r0, r4
	str r3, [sp]
	bl MOD79_02212FF0
	ldr ip, _02216208 ; =0x00000408
	add sp, sp, ip
	ldmia sp!, {r4, pc}
	.align 2, 0
_02216208: .word 0x00000408
_0221620C: .word MOD79_022170F0
_02216210: .word MOD79_02216FE4
_02216214: .word MOD79_02216FC4
_02216218: .word 0x00000146
	arm_func_end MOD79_022160C0

	arm_func_start MOD79_0221621C
MOD79_0221621C: ; 0x0221621C
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x10
	mov r4, r0
	ldr r1, [r4, #0x48]
	mvn r0, #0
	cmp r1, r0
	bne _022163D4
	mov r0, #2
	mov r1, #1
	mov r2, #0
	bl MOD04_021EFDB8
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x48]
	mvn r1, #0
	cmp r0, r1
	bne _02216280
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #5
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	add sp, sp, #0x10
	str r0, [r4, #0x4c]
	ldmia sp!, {r4, pc}
_02216280:
	mov r1, #0
	bl MOD04_021F017C
	cmp r0, #0
	bne _022162B4
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #5
	str r0, [r4, #0x38]
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	add sp, sp, #0x10
	str r0, [r4, #0x4c]
	ldmia sp!, {r4, pc}
_022162B4:
	ldr r0, [r4, #0x134]
	cmp r0, #0
	beq _022162D0
	ldr r1, _0221646C ; =0x0221695C
	ldr r0, [r4, #0x48]
	ldr r1, [r1]
	bl MOD04_021F0130
_022162D0:
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	mov r0, #2
	strb r0, [sp, #1]
	ldr r0, [r4, #0x15c]
	cmp r0, #0
	beq _02216318
	add r0, r4, #0x100
	ldrh r0, [r0, #0x60]
	mov r1, r0, asr #8
	mov r0, r0, lsl #8
	and r1, r1, #0xff
	and r0, r0, #0xff00
	orr r0, r1, r0
	strh r0, [sp, #2]
	b _02216368
_02216318:
	ldr r0, _02216470 ; =0x02217128
	ldr r0, [r0]
	cmp r0, #0
	beq _0221634C
	ldr r0, _02216474 ; =0x02217124
	ldrh r0, [r0]
	mov r1, r0, asr #8
	mov r0, r0, lsl #8
	and r1, r1, #0xff
	and r0, r0, #0xff00
	orr r0, r1, r0
	strh r0, [sp, #2]
	b _02216368
_0221634C:
	ldrh r0, [r4, #0x20]
	mov r1, r0, asr #8
	mov r0, r0, lsl #8
	and r1, r1, #0xff
	and r0, r0, #0xff00
	orr r0, r1, r0
	strh r0, [sp, #2]
_02216368:
	ldr r0, [r4, #0x1c]
	add r1, sp, #0
	str r0, [sp, #4]
	ldr r0, [r4, #0x48]
	mov r2, #8
	bl MOD04_021EFCE4
	mvn r1, #0
	cmp r0, r1
	bne _022163D4
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	mvn r1, #5
	cmp r0, r1
	beq _022163D4
	mvn r1, #0x19
	cmp r0, r1
	beq _022163D4
	mvn r1, #0x4b
	cmp r0, r1
	beq _022163D4
	mov r1, #1
	str r1, [r4, #0xfc]
	mov r1, #6
	str r1, [r4, #0x38]
	add sp, sp, #0x10
	str r0, [r4, #0x4c]
	ldmia sp!, {r4, pc}
_022163D4:
	ldr r0, [r4, #0x48]
	add r2, sp, #8
	add r3, sp, #0xc
	mov r1, #0
	bl MOD04_021EFF5C
	cmp r0, #0
	movgt r1, #1
	movle r1, #0
	mvn r0, #0
	cmp r1, r0
	beq _0221640C
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _0221643C
_0221640C:
	mov r0, #1
	str r0, [r4, #0xfc]
	mov r0, #6
	cmp r1, #0
	addne sp, sp, #0x10
	str r0, [r4, #0x38]
	ldmneia sp!, {r4, pc}
	ldr r0, [r4, #0x48]
	bl MOD04_021EFB28
	add sp, sp, #0x10
	str r0, [r4, #0x4c]
	ldmia sp!, {r4, pc}
_0221643C:
	ldr r0, [sp, #8]
	cmp r0, #0
	addeq sp, sp, #0x10
	ldmeqia sp!, {r4, pc}
	mov r1, #0
	mov r3, #2
	mov r0, r4
	mov r2, r1
	str r3, [r4, #0x10]
	bl MOD79_02212E00
	add sp, sp, #0x10
	ldmia sp!, {r4, pc}
	.align 2, 0
_0221646C: .word MOD79_0221695C
_02216470: .word 0x02217128
_02216474: .word 0x02217124
	arm_func_end MOD79_0221621C

	arm_func_start MOD79_02216478
MOD79_02216478: ; 0x02216478
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r1, #0
	mov r4, r0
	mov r2, r1
	bl MOD79_02212E00
	bl MOD04_021F024C
	mov r0, r4
	bl MOD79_02216548
	cmp r0, #0
	moveq r0, #1
	streq r0, [r4, #0xfc]
	moveq r0, #3
	addeq sp, sp, #4
	streq r0, [r4, #0x38]
	ldmeqia sp!, {r4, r5, pc}
	ldr r5, [r4, #0x15c]
	cmp r5, #0
	bne _022164D4
	ldr r0, _02216544 ; =0x02217128
	ldr r5, [r0]
	cmp r5, #0
	ldreq r5, [r4, #0x18]
_022164D4:
	mov r0, r5
	bl MOD04_021EFB38
	str r0, [r4, #0x1c]
	ldr r1, [r4, #0x1c]
	mvn r0, #0
	cmp r1, r0
	bne _02216524
	mov r0, r5
	bl SOC_GetHostByAddr
	cmp r0, #0
	moveq r0, #1
	streq r0, [r4, #0xfc]
	moveq r0, #4
	addeq sp, sp, #4
	streq r0, [r4, #0x38]
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, [r0, #0xc]
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x1c]
_02216524:
	mov r1, #0
	mov r3, #1
	mov r0, r4
	mov r2, r1
	str r3, [r4, #0x10]
	bl MOD79_02212E00
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_02216544: .word 0x02217128
	arm_func_end MOD79_02216478

	arm_func_start MOD79_02216548
MOD79_02216548: ; 0x02216548
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	movs r7, r0
	bne _0221656C
	ldr r0, _02216704 ; =0x02216FB8
	ldr r1, _02216708 ; =0x02216FC4
	mov r2, #0
	mov r3, #0x25
	bl __msl_assertion_failed
_0221656C:
	cmp r7, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	ldr r0, [r7, #0x14]
	cmp r0, #0
	bne _0221659C
	ldr r0, _0221670C ; =0x022170FC
	ldr r1, _02216708 ; =0x02216FC4
	mov r2, #0
	mov r3, #0x2b
	bl __msl_assertion_failed
_0221659C:
	ldr r6, [r7, #0x14]
	cmp r6, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	ldr r1, _02216710 ; =0x0221710C
	mov r0, r6
	mov r2, #7
	bl strncmp
	cmp r0, #0
	addeq r6, r6, #7
	moveq r4, #0
	beq _022165FC
	ldr r1, _02216714 ; =0x022170F0
	mov r0, r6
	mov r2, #8
	bl strncmp
	cmp r0, #0
	addeq r6, r6, #8
	moveq r4, #1
	beq _022165FC
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_022165FC:
	ldr r1, _02216718 ; =0x02217114
	mov r0, r6
	bl strspn
	mov r8, r0
	ldrsb r5, [r6, r8]
	mov r1, #0
	mov r0, r6
	strb r1, [r6, r8]
	add sb, r6, r8
	bl MOD04_021F0208
	str r0, [r7, #0x18]
	ldr r0, [r7, #0x18]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	strb r5, [sb]
	ldrsb r0, [r6, r8]!
	cmp r0, #0x3a
	bne _02216688
	add r6, r6, #1
	mov r0, r6
	bl atol
	strh r0, [r7, #0x20]
	ldrh r0, [r7, #0x20]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
_02216670:
	ldrsb r0, [r6, #1]!
	cmp r0, #0
	beq _0221669C
	cmp r0, #0x2f
	bne _02216670
	b _0221669C
_02216688:
	cmp r4, #0
	ldrne r0, _0221671C ; =0x000001BB
	strneh r0, [r7, #0x20]
	moveq r0, #0x50
	streqh r0, [r7, #0x20]
_0221669C:
	ldrsb r0, [r6]
	cmp r0, #0
	ldreq r6, _02216720 ; =0x02217118
	mov r0, r6
	bl MOD04_021F0208
	str r0, [r7, #0x24]
	ldr r6, [r7, #0x24]
	mov r1, #0x20
	mov r0, r6
	bl strchr
	cmp r0, #0
	beq _022166F0
	mov r5, #0x2b
	mov r4, #0x20
_022166D4:
	strb r5, [r0]
	ldr r6, [r7, #0x24]
	mov r1, r4
	mov r0, r6
	bl strchr
	cmp r0, #0
	bne _022166D4
_022166F0:
	cmp r6, #0
	movne r0, #1
	moveq r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_02216704: .word MOD79_02216FB8
_02216708: .word MOD79_02216FC4
_0221670C: .word MOD79_022170FC
_02216710: .word MOD79_0221710C
_02216714: .word MOD79_022170F0
_02216718: .word MOD79_02217114
_0221671C: .word 0x000001BB
_02216720: .word MOD79_02217118
	arm_func_end MOD79_02216548
	; 0x02216724

	.rodata
	.global MOD79_02216738
MOD79_02216738: ; 0x02216738
	.byte 0x25, 0x30, 0x30, 0x00

	.global MOD79_0221673C
MOD79_0221673C: ; 0x0221673C
	.byte 0x32, 0x31, 0x34, 0x37, 0x34, 0x38, 0x33, 0x36, 0x34, 0x37, 0x00, 0x00

	.data
	.global MOD79_0221686C
MOD79_0221686C: ; 0x0221686C
	.byte 0x67, 0x68, 0x74, 0x74, 0x70, 0x42, 0x75, 0x66, 0x66, 0x65, 0x72, 0x2E, 0x63, 0x00, 0x00, 0x00

	.global MOD79_0221687C
MOD79_0221687C: ; 0x0221687C
	.byte 0x6C, 0x65, 0x6E, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00

	.global MOD79_02216888
MOD79_02216888: ; 0x02216888
	.byte 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x00, 0x00

	.global MOD79_02216890
MOD79_02216890: ; 0x02216890
	.byte 0x25, 0x64, 0x00, 0x00

	.global MOD79_02216894
MOD79_02216894: ; 0x02216894
	.byte 0x3A, 0x20, 0x00, 0x00

	.global MOD79_02216898
MOD79_02216898: ; 0x02216898
	.byte 0x0D, 0x0A, 0x00, 0x00

	.global MOD79_0221689C
MOD79_0221689C: ; 0x0221689C
	.byte 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x00, 0x00

	.global MOD79_022168A4
MOD79_022168A4: ; 0x022168A4
	.byte 0x64, 0x61, 0x74, 0x61, 0x4C, 0x65, 0x6E, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00

	.global MOD79_022168B4
MOD79_022168B4: ; 0x022168B4
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x65, 0x6E, 0x63, 0x72
	.byte 0x79, 0x70, 0x74, 0x6F, 0x72, 0x2E, 0x6D, 0x45, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x20, 0x21, 0x3D
	.byte 0x20, 0x47, 0x48, 0x54, 0x54, 0x50, 0x45, 0x6E, 0x63, 0x72, 0x79, 0x70, 0x74, 0x69, 0x6F, 0x6E
	.byte 0x45, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x5F, 0x4E, 0x6F, 0x6E, 0x65, 0x00

	.global MOD79_022168F0
MOD79_022168F0: ; 0x022168F0
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_022168FC
MOD79_022168FC: ; 0x022168FC
	.byte 0x75, 0x73, 0x65, 0x72, 0x42, 0x75, 0x66, 0x66, 0x65, 0x72, 0x00, 0x00

	.global MOD79_02216908
MOD79_02216908: ; 0x02216908
	.byte 0x73, 0x69, 0x7A, 0x65, 0x20, 0x3E, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216914
MOD79_02216914: ; 0x02216914
	.byte 0x69, 0x6E, 0x69, 0x74, 0x69, 0x61, 0x6C, 0x53, 0x69, 0x7A, 0x65, 0x20, 0x3E, 0x20, 0x30, 0x00

	.global MOD79_02216924
MOD79_02216924: ; 0x02216924
	.byte 0x73, 0x69, 0x7A, 0x65, 0x49, 0x6E, 0x63, 0x72, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x20, 0x3E, 0x20
	.byte 0x30, 0x00, 0x00, 0x00

	.global MOD79_02216938
MOD79_02216938: ; 0x02216938
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_02216944
MOD79_02216944: ; 0x02216944
	.byte 0x67, 0x68, 0x74, 0x74, 0x70, 0x43, 0x61, 0x6C, 0x6C, 0x62, 0x61, 0x63, 0x6B, 0x73, 0x2E, 0x63
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216958
MOD79_02216958: ; 0x02216958
	.byte 0xFA, 0x00, 0x00, 0x00

	.global MOD79_0221695C
MOD79_0221695C: ; 0x0221695C
	.byte 0x7D, 0x00, 0x00, 0x00

	.global MOD79_02216960
MOD79_02216960: ; 0x02216960
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_0221696C
MOD79_0221696C: ; 0x0221696C
	.byte 0x67, 0x68, 0x74, 0x74, 0x70, 0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2E
	.byte 0x63, 0x00, 0x00, 0x00

	.global MOD79_02216980
MOD79_02216980: ; 0x02216980
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x64, 0x69
	.byte 0x72, 0x65, 0x63, 0x74, 0x55, 0x52, 0x4C, 0x00

	.global MOD79_02216998
MOD79_02216998: ; 0x02216998
	.byte 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00

	.global MOD79_022169A8
MOD79_022169A8: ; 0x022169A8
	.byte 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x20, 0x3C, 0x20, 0x67, 0x68, 0x69, 0x43, 0x6F, 0x6E
	.byte 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x73, 0x4C, 0x65, 0x6E, 0x00

	.global MOD79_022169C4
MOD79_022169C4: ; 0x022169C4
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x71, 0x75
	.byte 0x65, 0x73, 0x74, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00

	.global MOD79_022169E0
MOD79_022169E0: ; 0x022169E0
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x71, 0x75
	.byte 0x65, 0x73, 0x74, 0x20, 0x3C, 0x20, 0x67, 0x68, 0x69, 0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74
	.byte 0x69, 0x6F, 0x6E, 0x73, 0x4C, 0x65, 0x6E, 0x00

	.global MOD79_02216A08
MOD79_02216A08: ; 0x02216A08
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x69, 0x6E, 0x55, 0x73
	.byte 0x65, 0x00, 0x00, 0x00

	.global MOD79_02216A1C
MOD79_02216A1C: ; 0x02216A1C
	.byte 0x67, 0x68, 0x69, 0x4E, 0x75, 0x6D, 0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E
	.byte 0x73, 0x20, 0x3D, 0x3D, 0x20, 0x67, 0x68, 0x69, 0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69
	.byte 0x6F, 0x6E, 0x73, 0x4C, 0x65, 0x6E, 0x00, 0x00

	.global MOD79_02216A44
MOD79_02216A44: ; 0x02216A44
	.byte 0x67, 0x68, 0x74, 0x74, 0x70, 0x4D, 0x61, 0x69, 0x6E, 0x2E, 0x63, 0x00

	.global MOD79_02216A50
MOD79_02216A50: ; 0x02216A50
	.byte 0x55, 0x52, 0x4C, 0x20, 0x26, 0x26, 0x20, 0x55, 0x52, 0x4C, 0x5B, 0x30, 0x5D, 0x00, 0x00, 0x00

	.global MOD79_02216A60
MOD79_02216A60: ; 0x02216A60
	.byte 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x53, 0x69, 0x7A, 0x65, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x00

	.global MOD79_02216A70
MOD79_02216A70: ; 0x02216A70
	.byte 0x21, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x20, 0x7C, 0x7C, 0x20, 0x62, 0x75, 0x66, 0x66, 0x65
	.byte 0x72, 0x53, 0x69, 0x7A, 0x65, 0x00, 0x00, 0x00

	.global MOD79_02216A88
MOD79_02216A88: ; 0x02216A88
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_02216A94
MOD79_02216A94: ; 0x02216A94
	.byte 0x67, 0x68, 0x69, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x54, 0x6F, 0x43, 0x6F, 0x6E, 0x6E
	.byte 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x28, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F
	.byte 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x29, 0x20, 0x3D, 0x3D, 0x20, 0x63
	.byte 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00, 0x00

	.global MOD79_02216AD0
MOD79_02216AD0: ; 0x02216AD0
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_02216ADC
MOD79_02216ADC: ; 0x02216ADC
	.byte 0x67, 0x68, 0x74, 0x74, 0x70, 0x50, 0x6F, 0x73, 0x74, 0x2E, 0x63, 0x00

	.global MOD79_02216AE8
MOD79_02216AE8: ; 0x02216AE8
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x74
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216AFC
MOD79_02216AFC: ; 0x02216AFC
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x74
	.byte 0x69, 0x6E, 0x67, 0x53, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x73, 0x74, 0x61, 0x74, 0x65, 0x73, 0x00

	.global MOD79_02216B1C
MOD79_02216B1C: ; 0x02216B1C
	.byte 0x41, 0x72, 0x72, 0x61, 0x79, 0x4C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x28, 0x63, 0x6F, 0x6E, 0x6E
	.byte 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x74, 0x2D, 0x3E, 0x64, 0x61
	.byte 0x74, 0x61, 0x29, 0x20, 0x3D, 0x3D, 0x20, 0x41, 0x72, 0x72, 0x61, 0x79, 0x4C, 0x65, 0x6E, 0x67
	.byte 0x74, 0x68, 0x28, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70
	.byte 0x6F, 0x73, 0x74, 0x69, 0x6E, 0x67, 0x53, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x73, 0x74, 0x61, 0x74
	.byte 0x65, 0x73, 0x29, 0x00

	.global MOD79_02216B70
MOD79_02216B70: ; 0x02216B70
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x74
	.byte 0x69, 0x6E, 0x67, 0x53, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x20, 0x3E
	.byte 0x3D, 0x20, 0x30, 0x00

	.global MOD79_02216B94
MOD79_02216B94: ; 0x02216B94
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x74
	.byte 0x69, 0x6E, 0x67, 0x53, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x20, 0x3C
	.byte 0x3D, 0x20, 0x41, 0x72, 0x72, 0x61, 0x79, 0x4C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x28, 0x63, 0x6F
	.byte 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x74, 0x69, 0x6E
	.byte 0x67, 0x53, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x73, 0x74, 0x61, 0x74, 0x65, 0x73, 0x29, 0x00, 0x00

	.global MOD79_02216BE4
MOD79_02216BE4: ; 0x02216BE4
	.byte 0x70, 0x6F, 0x73, 0x74, 0x53, 0x74, 0x61, 0x74, 0x65, 0x00, 0x00, 0x00

	.global MOD79_02216BF0
MOD79_02216BF0: ; 0x02216BF0
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x63, 0x6F, 0x6D, 0x70
	.byte 0x6C, 0x65, 0x74, 0x65, 0x64, 0x20, 0x26, 0x26, 0x20, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74
	.byte 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x00

	.global MOD79_02216C1C
MOD79_02216C1C: ; 0x02216C1C
	.byte 0x0D, 0x0A, 0x2D, 0x2D, 0x51, 0x72, 0x34, 0x47, 0x38, 0x32, 0x33, 0x73, 0x32, 0x33, 0x64, 0x2D
	.byte 0x2D, 0x2D, 0x3C, 0x3C, 0x3E, 0x3C, 0x3E, 0x3C, 0x3C, 0x3C, 0x3E, 0x2D, 0x2D, 0x37, 0x64, 0x31
	.byte 0x31, 0x38, 0x65, 0x30, 0x35, 0x33, 0x36, 0x2D, 0x2D, 0x0D, 0x0A, 0x00

	.global MOD79_02216C48
MOD79_02216C48: ; 0x02216C48
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x64, 0x61, 0x74, 0x61, 0x2D, 0x3E, 0x74, 0x79, 0x70
	.byte 0x65, 0x20, 0x3D, 0x3D, 0x20, 0x47, 0x48, 0x49, 0x53, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x00, 0x00

	.global MOD79_02216C68
MOD79_02216C68: ; 0x02216C68
	.byte 0x25, 0x73, 0x3D, 0x00

	.global MOD79_02216C6C
MOD79_02216C6C: ; 0x02216C6C
	.byte 0x26, 0x25, 0x73, 0x3D, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216C74
MOD79_02216C74: ; 0x02216C74
	.byte 0x2D, 0x2D, 0x51, 0x72, 0x34, 0x47, 0x38, 0x32, 0x33, 0x73, 0x32, 0x33, 0x64, 0x2D, 0x2D, 0x2D
	.byte 0x3C, 0x3C, 0x3E, 0x3C, 0x3E, 0x3C, 0x3C, 0x3C, 0x3E, 0x2D, 0x2D, 0x37, 0x64, 0x31, 0x31, 0x38
	.byte 0x65, 0x30, 0x35, 0x33, 0x36, 0x0D, 0x0A, 0x00

	.global MOD79_02216C9C
MOD79_02216C9C: ; 0x02216C9C
	.byte 0x0D, 0x0A, 0x2D, 0x2D, 0x51, 0x72, 0x34, 0x47, 0x38, 0x32, 0x33, 0x73, 0x32, 0x33, 0x64, 0x2D
	.byte 0x2D, 0x2D, 0x3C, 0x3C, 0x3E, 0x3C, 0x3E, 0x3C, 0x3C, 0x3C, 0x3E, 0x2D, 0x2D, 0x37, 0x64, 0x31
	.byte 0x31, 0x38, 0x65, 0x30, 0x35, 0x33, 0x36, 0x0D, 0x0A, 0x00, 0x00, 0x00

	.global MOD79_02216CC8
MOD79_02216CC8: ; 0x02216CC8
	.byte 0x25, 0x73, 0x43, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x44, 0x69, 0x73, 0x70, 0x6F, 0x73
	.byte 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x3A, 0x20, 0x66, 0x6F, 0x72, 0x6D, 0x2D, 0x64, 0x61, 0x74, 0x61
	.byte 0x3B, 0x20, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x25, 0x73, 0x22, 0x0D, 0x0A, 0x0D, 0x0A, 0x00

	.global MOD79_02216CF8
MOD79_02216CF8: ; 0x02216CF8
	.byte 0x25, 0x73, 0x43, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x44, 0x69, 0x73, 0x70, 0x6F, 0x73
	.byte 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x3A, 0x20, 0x66, 0x6F, 0x72, 0x6D, 0x2D, 0x64, 0x61, 0x74, 0x61
	.byte 0x3B, 0x20, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x25, 0x73, 0x22, 0x3B, 0x20, 0x66, 0x69, 0x6C
	.byte 0x65, 0x6E, 0x61, 0x6D, 0x65, 0x3D, 0x22, 0x25, 0x73, 0x22, 0x0D, 0x0A, 0x43, 0x6F, 0x6E, 0x74
	.byte 0x65, 0x6E, 0x74, 0x2D, 0x54, 0x79, 0x70, 0x65, 0x3A, 0x20, 0x25, 0x73, 0x0D, 0x0A, 0x0D, 0x0A
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216D4C
MOD79_02216D4C: ; 0x02216D4C
	.byte 0x30, 0x00, 0x00, 0x00

	.global MOD79_02216D50
MOD79_02216D50: ; 0x02216D50
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x64, 0x61, 0x74, 0x61, 0x2D, 0x3E, 0x74, 0x79, 0x70
	.byte 0x65, 0x20, 0x3D, 0x3D, 0x20, 0x47, 0x48, 0x49, 0x46, 0x69, 0x6C, 0x65, 0x4D, 0x65, 0x6D, 0x6F
	.byte 0x72, 0x79, 0x00, 0x00

	.global MOD79_02216D74
MOD79_02216D74: ; 0x02216D74
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x00

	.global MOD79_02216D84
MOD79_02216D84: ; 0x02216D84
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x20, 0x3C, 0x20, 0x73, 0x74, 0x61
	.byte 0x74, 0x65, 0x2D, 0x3E, 0x64, 0x61, 0x74, 0x61, 0x2D, 0x3E, 0x64, 0x61, 0x74, 0x61, 0x2E, 0x66
	.byte 0x69, 0x6C, 0x65, 0x4D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x2E, 0x6C, 0x65, 0x6E, 0x00, 0x00, 0x00

	.global MOD79_02216DB4
MOD79_02216DB4: ; 0x02216DB4
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x20, 0x3C, 0x20, 0x73, 0x74, 0x61
	.byte 0x74, 0x65, 0x2D, 0x3E, 0x73, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x66, 0x69, 0x6C, 0x65, 0x44, 0x69
	.byte 0x73, 0x6B, 0x2E, 0x6C, 0x65, 0x6E, 0x00, 0x00

	.global MOD79_02216DDC
MOD79_02216DDC: ; 0x02216DDC
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x20, 0x3D, 0x3D, 0x20, 0x28, 0x69
	.byte 0x6E, 0x74, 0x29, 0x66, 0x74, 0x65, 0x6C, 0x6C, 0x28, 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2E, 0x66, 0x69, 0x6C, 0x65, 0x44, 0x69, 0x73, 0x6B, 0x2E, 0x66
	.byte 0x69, 0x6C, 0x65, 0x29, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216E14
MOD79_02216E14: ; 0x02216E14
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x2D, 0x3E, 0x70, 0x6F, 0x73, 0x20, 0x3C, 0x20, 0x73, 0x74, 0x61
	.byte 0x74, 0x65, 0x2D, 0x3E, 0x64, 0x61, 0x74, 0x61, 0x2D, 0x3E, 0x64, 0x61, 0x74, 0x61, 0x2E, 0x73
	.byte 0x74, 0x72, 0x69, 0x6E, 0x67, 0x2E, 0x6C, 0x65, 0x6E, 0x00, 0x00, 0x00

	.global MOD79_02216E40
MOD79_02216E40: ; 0x02216E40
	.byte 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70
	.byte 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46
	.byte 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56
	.byte 0x57, 0x58, 0x59, 0x5A, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x5F, 0x40
	.byte 0x2D, 0x2E, 0x2A, 0x00

	.global MOD79_02216E84
MOD79_02216E84: ; 0x02216E84
	.byte 0x28, 0x63, 0x20, 0x2F, 0x20, 0x31, 0x36, 0x29, 0x20, 0x3C, 0x20, 0x31, 0x36, 0x00, 0x00, 0x00

	.global MOD79_02216E94
MOD79_02216E94: ; 0x02216E94
	.byte 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216EA8
MOD79_02216EA8: ; 0x02216EA8
	.byte 0x70, 0x6F, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216EB0
MOD79_02216EB0: ; 0x02216EB0
	.byte 0x2D, 0x2D, 0x51, 0x72, 0x34, 0x47, 0x38, 0x32, 0x33, 0x73, 0x32, 0x33, 0x64, 0x2D, 0x2D, 0x2D
	.byte 0x3C, 0x3C, 0x3E, 0x3C, 0x3E, 0x3C, 0x3C, 0x3C, 0x3E, 0x2D, 0x2D, 0x37, 0x64, 0x31, 0x31, 0x38
	.byte 0x65, 0x30, 0x35, 0x33, 0x36, 0x00, 0x00, 0x00

	.global MOD79_02216ED8
MOD79_02216ED8: ; 0x02216ED8
	.byte 0x73, 0x74, 0x61, 0x74, 0x65, 0x00, 0x00, 0x00

	.global MOD79_02216EE0
MOD79_02216EE0: ; 0x02216EE0
	.byte 0x64, 0x61, 0x74, 0x61, 0x2D, 0x3E, 0x74, 0x79, 0x70, 0x65, 0x20, 0x3D, 0x3D, 0x20, 0x47, 0x48
	.byte 0x49, 0x53, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x00

	.global MOD79_02216EF8
MOD79_02216EF8: ; 0x02216EF8
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216EFC
MOD79_02216EFC: ; 0x02216EFC
	.byte 0x6D, 0x75, 0x6C, 0x74, 0x69, 0x70, 0x61, 0x72, 0x74, 0x2F, 0x66, 0x6F, 0x72, 0x6D, 0x2D, 0x64
	.byte 0x61, 0x74, 0x61, 0x3B, 0x20, 0x62, 0x6F, 0x75, 0x6E, 0x64, 0x61, 0x72, 0x79, 0x3D, 0x51, 0x72
	.byte 0x34, 0x47, 0x38, 0x32, 0x33, 0x73, 0x32, 0x33, 0x64, 0x2D, 0x2D, 0x2D, 0x3C, 0x3C, 0x3E, 0x3C
	.byte 0x3E, 0x3C, 0x3C, 0x3C, 0x3E, 0x2D, 0x2D, 0x37, 0x64, 0x31, 0x31, 0x38, 0x65, 0x30, 0x35, 0x33
	.byte 0x36, 0x00, 0x00, 0x00

	.global MOD79_02216F40
MOD79_02216F40: ; 0x02216F40
	.byte 0x61, 0x70, 0x70, 0x6C, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x2F, 0x78, 0x2D, 0x77, 0x77
	.byte 0x77, 0x2D, 0x66, 0x6F, 0x72, 0x6D, 0x2D, 0x75, 0x72, 0x6C, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x65
	.byte 0x64, 0x00, 0x00, 0x00

	.global MOD79_02216F64
MOD79_02216F64: ; 0x02216F64
	.byte 0x0D, 0x0A, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216F6C
MOD79_02216F6C: ; 0x02216F6C
	.byte 0x0A, 0x0A, 0x00, 0x00

	.global MOD79_02216F70
MOD79_02216F70: ; 0x02216F70
	.byte 0x4C, 0x6F, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x3A, 0x00, 0x00, 0x00

	.global MOD79_02216F7C
MOD79_02216F7C: ; 0x02216F7C
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x25, 0x73, 0x3A, 0x25, 0x64, 0x25, 0x73, 0x00, 0x00

	.global MOD79_02216F8C
MOD79_02216F8C: ; 0x02216F8C
	.byte 0x43, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x4C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x3A, 0x00

	.global MOD79_02216F9C
MOD79_02216F9C: ; 0x02216F9C
	.byte 0x54, 0x72, 0x61, 0x6E, 0x73, 0x66, 0x65, 0x72, 0x2D, 0x45, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E
	.byte 0x67, 0x3A, 0x20, 0x63, 0x68, 0x75, 0x6E, 0x6B, 0x65, 0x64, 0x00, 0x00

	.global MOD79_02216FB8
MOD79_02216FB8: ; 0x02216FB8
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_02216FC4
MOD79_02216FC4: ; 0x02216FC4
	.byte 0x67, 0x68, 0x74, 0x74, 0x70, 0x50, 0x72, 0x6F, 0x63, 0x65, 0x73, 0x73, 0x2E, 0x63, 0x00, 0x00

	.global MOD79_02216FD4
MOD79_02216FD4: ; 0x02216FD4
	.byte 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216FDC
MOD79_02216FDC: ; 0x02216FDC
	.byte 0x6C, 0x65, 0x6E, 0x20, 0x3E, 0x20, 0x30, 0x00

	.global MOD79_02216FE4
MOD79_02216FE4: ; 0x02216FE4
	.byte 0x30, 0x00, 0x00, 0x00

	.global MOD79_02216FE8
MOD79_02216FE8: ; 0x02216FE8
	.byte 0x6C, 0x65, 0x6E, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02216FF4
MOD79_02216FF4: ; 0x02216FF4
	.byte 0x6C, 0x65, 0x6E, 0x00

	.global MOD79_02216FF8
MOD79_02216FF8: ; 0x02216FF8
	.byte 0x25, 0x78, 0x00, 0x00

	.global MOD79_02216FFC
MOD79_02216FFC: ; 0x02216FFC
	.byte 0x0D, 0x0A, 0x00, 0x00

	.global MOD79_02217000
MOD79_02217000: ; 0x02217000
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x63, 0x76
	.byte 0x42, 0x75, 0x66, 0x66, 0x65, 0x72, 0x2E, 0x6C, 0x65, 0x6E, 0x20, 0x3E, 0x20, 0x30, 0x00, 0x00

	.global MOD79_02217020
MOD79_02217020: ; 0x02217020
	.byte 0x48, 0x54, 0x54, 0x50, 0x2F, 0x25, 0x64, 0x2E, 0x25, 0x64, 0x20, 0x25, 0x64, 0x25, 0x6E, 0x00

	.global MOD79_02217030
MOD79_02217030: ; 0x02217030
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x63, 0x6F, 0x6D, 0x70
	.byte 0x6C, 0x65, 0x74, 0x65, 0x64, 0x20, 0x26, 0x26, 0x20, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74
	.byte 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x00

	.global MOD79_0221705C
MOD79_0221705C: ; 0x0221705C
	.byte 0x50, 0x4F, 0x53, 0x54, 0x20, 0x00, 0x00, 0x00

	.global MOD79_02217064
MOD79_02217064: ; 0x02217064
	.byte 0x48, 0x45, 0x41, 0x44, 0x20, 0x00, 0x00, 0x00

	.global MOD79_0221706C
MOD79_0221706C: ; 0x0221706C
	.byte 0x47, 0x45, 0x54, 0x20, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02217074
MOD79_02217074: ; 0x02217074
	.byte 0x20, 0x48, 0x54, 0x54, 0x50, 0x2F, 0x31, 0x2E, 0x31, 0x0D, 0x0A, 0x00

	.global MOD79_02217080
MOD79_02217080: ; 0x02217080
	.byte 0x48, 0x6F, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00

	.global MOD79_02217088
MOD79_02217088: ; 0x02217088
	.byte 0x48, 0x6F, 0x73, 0x74, 0x3A, 0x20, 0x00, 0x00

	.global MOD79_02217090
MOD79_02217090: ; 0x02217090
	.byte 0x55, 0x73, 0x65, 0x72, 0x2D, 0x41, 0x67, 0x65, 0x6E, 0x74, 0x00, 0x00

	.global MOD79_0221709C
MOD79_0221709C: ; 0x0221709C
	.byte 0x47, 0x61, 0x6D, 0x65, 0x53, 0x70, 0x79, 0x48, 0x54, 0x54, 0x50, 0x2F, 0x31, 0x2E, 0x30, 0x00

	.global MOD79_022170AC
MOD79_022170AC: ; 0x022170AC
	.byte 0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00

	.global MOD79_022170B8
MOD79_022170B8: ; 0x022170B8
	.byte 0x4B, 0x65, 0x65, 0x70, 0x2D, 0x41, 0x6C, 0x69, 0x76, 0x65, 0x00, 0x00

	.global MOD79_022170C4
MOD79_022170C4: ; 0x022170C4
	.byte 0x63, 0x6C, 0x6F, 0x73, 0x65, 0x00, 0x00, 0x00

	.global MOD79_022170CC
MOD79_022170CC: ; 0x022170CC
	.byte 0x25, 0x64, 0x00, 0x00

	.global MOD79_022170D0
MOD79_022170D0: ; 0x022170D0
	.byte 0x43, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x4C, 0x65, 0x6E, 0x67, 0x74, 0x68, 0x00, 0x00

	.global MOD79_022170E0
MOD79_022170E0: ; 0x022170E0
	.byte 0x43, 0x6F, 0x6E, 0x74, 0x65, 0x6E, 0x74, 0x2D, 0x54, 0x79, 0x70, 0x65, 0x00, 0x00, 0x00, 0x00

	.global MOD79_022170F0
MOD79_022170F0: ; 0x022170F0
	.byte 0x68, 0x74, 0x74, 0x70, 0x73, 0x3A, 0x2F, 0x2F, 0x00, 0x00, 0x00, 0x00

	.global MOD79_022170FC
MOD79_022170FC: ; 0x022170FC
	.byte 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x2D, 0x3E, 0x55, 0x52, 0x4C, 0x00

	.global MOD79_0221710C
MOD79_0221710C: ; 0x0221710C
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x00

	.global MOD79_02217114
MOD79_02217114: ; 0x02217114
	.byte 0x3A, 0x2F, 0x00, 0x00

	.global MOD79_02217118
MOD79_02217118: ; 0x02217118
	.byte 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
