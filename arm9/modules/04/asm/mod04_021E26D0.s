	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021E26D0
MOD04_021E26D0: ; 0x021E26D0
	ldr r1, _021E26E0 ; =UNK04_022106D8
	ldr r1, [r1]
	str r0, [r1, #0x1a0]
	bx lr
	.align 2, 0
_021E26E0: .word UNK04_022106D8
	arm_func_end MOD04_021E26D0

	arm_func_start MOD04_021E26E4
MOD04_021E26E4: ; 0x021E26E4
	ldr r0, _021E26F0 ; =UNK04_022106D8
	ldr r0, [r0]
	bx lr
	.align 2, 0
_021E26F0: .word UNK04_022106D8
	arm_func_end MOD04_021E26E4

	arm_func_start MOD04_021E26F4
MOD04_021E26F4: ; 0x021E26F4
	ldr r1, _021E2700 ; =UNK04_022106D8
	str r0, [r1]
	bx lr
	.align 2, 0
_021E2700: .word UNK04_022106D8
	arm_func_end MOD04_021E26F4

	arm_func_start MOD04_021E2704
MOD04_021E2704: ; 0x021E2704
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #1
	ldmneia sp!, {pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	beq _021E273C
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x17d]
	add r1, r1, #1
	strb r1, [r0, #0x17d]
_021E273C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	beq _021E275C
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17d]
	cmp r0, #5
	blo _021E2774
_021E275C:
	ldr r1, _021E2780 ; =0xFFFEAE6C
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #4
	mov r0, #0
	ldmfd sp!, {pc}
_021E2774:
	mov r0, #1
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E2780: .word 0xFFFEAE6C
	arm_func_end MOD04_021E2704

	arm_func_start MOD04_021E2784
MOD04_021E2784: ; 0x021E2784
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x20
	mov r5, r0
	mov r6, r2
	mov r4, r3
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #6
	beq _021E27BC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	addne sp, sp, #0x20
	ldmneia sp!, {r4, r5, r6, pc}
_021E27BC:
	cmp r4, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r5, #0
	bne _021E29B8
	mov r0, #0
	str r0, [r4, #8]
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x14]
	add r1, r1, #1
	strb r1, [r0, #0x14]
	bl MOD04_021E26E4
	ldrb r1, [r4]
	ldrb r5, [r0, #0x14]
	cmp r1, #0
	beq _021E2950
	bl MOD04_021E26E4
	ldr r1, [r6, #4]
	add r0, r0, r5, lsl #2
	str r1, [r0, #0x210]
	ldrh r4, [r6, #2]
	bl MOD04_021E26E4
	mov r2, r4, asr #8
	mov r1, r4, lsl #8
	add r0, r0, r5, lsl #1
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	add r0, r0, #0x200
	strh r1, [r0, #0x90]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17c]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x180]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x184]
	str r1, [r0, #0x188]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	bne _021E2878
	mov r0, #0xc
	bl MOD04_021E26D0
	b _021E2880
_021E2878:
	mov r0, #7
	bl MOD04_021E26D0
_021E2880:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xc]
	bl MOD04_021E26E4
	ldr r3, [r0, #0x200]
	ldr r2, _021E2B58 ; =UNK04_0220D394
	add r0, sp, #0x10
	mov r1, #0xc
	bl OS_SNPrintf
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	add r1, r6, r5, lsl #2
	mov r2, r0
	ldr r0, [r1, #0x210]
	add r1, r2, r5, lsl #1
	add r1, r1, #0x200
	ldrh r1, [r1, #0x90]
	mov r2, #0
	bl MOD04_021FFEB0
	mov r6, r0
	bl MOD04_021E26E4
	mvn r1, #0
	str r1, [sp]
	ldr r3, _021E2B5C ; =0x00001388
	mov r1, #0
	str r3, [sp, #4]
	ldr r0, [r0, #8]
	mov r2, r6
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #4]
	add r3, sp, #0x10
	ldr r0, [r0]
	bl MOD04_021FD52C
	cmp r0, #1
	bne _021E2928
	bl MOD04_021E36B0
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, pc}
_021E2928:
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, pc}
	bl MOD04_021E26E4
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	add sp, sp, #0x20
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E2950:
	cmp r6, #0
	beq _021E2994
	sub r4, r5, #1
	bl MOD04_021E26E4
	ldr r1, [r6, #4]
	add r0, r0, r4, lsl #2
	str r1, [r0, #0x210]
	ldrh r5, [r6, #2]
	bl MOD04_021E26E4
	mov r2, r5, asr #8
	mov r1, r5, lsl #8
	add r0, r0, r4, lsl #1
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	add r0, r0, #0x200
	strh r1, [r0, #0x90]
_021E2994:
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x18c]
	mov r0, #7
	str r1, [r4, #0x190]
	bl MOD04_021E26D0
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, pc}
_021E29B8:
	ldr r0, [r4, #8]
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, pc}
	mov r0, r5
	bl MOD04_021E3754
	mov r6, r0
	cmp r6, #2
	beq _021E29E8
	cmp r6, #1
	addne sp, sp, #0x20
	ldmneia sp!, {r4, r5, r6, pc}
_021E29E8:
	ldrb r0, [r4]
	cmp r0, #0
	bne _021E2A74
	cmp r6, #1
	beq _021E2A10
	cmp r6, #2
	bne _021E2A50
	ldrb r0, [r4, #1]
	cmp r0, #1
	blo _021E2A50
_021E2A10:
	mov r0, #0
	str r0, [r4, #8]
	bl MOD04_021E2704
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, pc}
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5908
	add sp, sp, #0x20
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E2A50:
	ldrb r1, [r4, #1]
	mov r0, r4
	add r1, r1, #1
	strb r1, [r4, #1]
	bl MOD04_021E7A44
	bl MOD04_021E37A4
	add sp, sp, #0x20
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E2A74:
	bl MOD04_021E26E4
	mov r5, r0
	bl OS_GetTick
	str r0, [r5, #0x184]
	str r1, [r5, #0x188]
	cmp r6, #1
	beq _021E2AB0
	cmp r6, #2
	addne sp, sp, #0x20
	ldmneia sp!, {r4, r5, r6, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17c]
	cmp r0, #1
	addlo sp, sp, #0x20
	ldmloia sp!, {r4, r5, r6, pc}
_021E2AB0:
	mov r0, #0
	str r0, [r4, #8]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	beq _021E2AD8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E2AF0
_021E2AD8:
	mov r0, #1
	bl MOD04_021E2704
	cmp r0, #0
	bne _021E2B04
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, pc}
_021E2AF0:
	mov r0, #0
	bl MOD04_021E2704
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, pc}
_021E2B04:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17c]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x180]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x184]
	str r1, [r0, #0x188]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r0, #1
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	cmp r0, #0
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E2B58: .word UNK04_0220D394
_021E2B5C: .word 0x00001388
	arm_func_end MOD04_021E2784

	arm_func_start MOD04_021E2B60
MOD04_021E2B60: ; 0x021E2B60
	bx lr
	arm_func_end MOD04_021E2B60

	arm_func_start MOD04_021E2B64
MOD04_021E2B64: ; 0x021E2B64
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x9c
	mov sl, r0
	mov sb, r1
	mov r8, #0
	bl MOD04_021DF88C
	cmp r0, #5
	beq _021E2BB8
	bl MOD04_021DF88C
	cmp r0, #6
	addne sp, sp, #0x9c
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	beq _021E2BB8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	addne sp, sp, #0x9c
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E2BB8:
	cmp sb, #0x14
	addlo sp, sp, #0x9c
	ldmloia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add r4, sp, #0x1c
	add fp, sp, #8
	add r5, sl, #0x14
	mov r7, #0x14
	mov r6, #4
_021E2BD8:
	mov r0, sl
	mov r1, fp
	mov r2, r7
	bl MI_CpuCopy8
	ldr r1, _021E2C74 ; =UNK04_0220D398
	mov r0, fp
	mov r2, r6
	bl strncmp
	cmp r0, #0
	addne sp, sp, #0x9c
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, [sp, #0xc]
	cmp r0, #3
	addne sp, sp, #0x9c
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldrb r2, [sp, #0x11]
	mov r0, r5
	mov r1, r4
	bl MI_CpuCopy8
	str r4, [sp]
	ldrb r0, [sp, #0x11]
	mov r0, r0, asr #2
	str r0, [sp, #4]
	ldrb r0, [sp, #0x10]
	ldrh r3, [sp, #0x12]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	bl MOD04_021E6730
	cmp r0, #0
	addeq sp, sp, #0x9c
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldrb r0, [sp, #0x11]
	add r0, r0, #0x14
	add r8, r8, r0
	add r0, r8, #0x14
	cmp r0, sb
	bls _021E2BD8
	add sp, sp, #0x9c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E2C74: .word UNK04_0220D398
	arm_func_end MOD04_021E2B64

	arm_func_start MOD04_021E2C78
MOD04_021E2C78: ; 0x021E2C78
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E2C9C
	mov r0, #6
	bl MOD04_021E26D0
	b _021E2CBC
_021E2C9C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #6
	beq _021E2CBC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	ldmneia sp!, {r4, pc}
_021E2CBC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x180]
	cmp r4, r0
	bne _021E2CE0
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x17c]
	add r1, r1, #1
	strb r1, [r0, #0x17c]
	b _021E2CF4
_021E2CE0:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17c]
	bl MOD04_021E26E4
	str r4, [r0, #0x180]
_021E2CF4:
	bl MOD04_021E26E4
	mov r2, #0
	str r2, [r0, #0x184]
	str r2, [r0, #0x188]
	mov r1, r4
	mov r0, #1
	bl MOD04_021E7B04
	bl MOD04_021E37A4
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	bl MOD04_021E26E4
	mov r1, #0xff
	strb r1, [r0, #0x3cc]
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E2C78

	arm_func_start MOD04_021E2D2C
MOD04_021E2D2C: ; 0x021E2D2C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r4, r1
	bl MOD04_021E26E4
	str r5, [r0, #0x1c]
	bl MOD04_021E26E4
	strh r4, [r0, #0x1a]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021E2D2C

	arm_func_start MOD04_021E2D54
MOD04_021E2D54: ; 0x021E2D54
	ldr ip, _021E2D5C ; =MOD04_021E3800
	bx ip
	.align 2, 0
_021E2D5C: .word MOD04_021E3800
	arm_func_end MOD04_021E2D54

	arm_func_start MOD04_021E2D60
MOD04_021E2D60: ; 0x021E2D60
	mov r0, #0
	bx lr
	arm_func_end MOD04_021E2D60

	arm_func_start MOD04_021E2D68
MOD04_021E2D68: ; 0x021E2D68
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r1
	cmp r0, #0
	beq _021E2D88
	cmp r0, #1
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r0, #2
	ldmia sp!, {r4, r5, r6, pc}
_021E2D88:
	mov r0, r6
	mov r1, #8
	bl MOD04_02202254
	mov r0, r6
	mov r1, #0xa
	bl MOD04_02202254
	mov r0, r6
	mov r1, #0x32
	bl MOD04_02202254
	mov r0, r6
	mov r1, #0x33
	bl MOD04_02202254
	mov r0, r6
	mov r1, #0x34
	bl MOD04_02202254
	mov r0, r6
	mov r1, #0x35
	bl MOD04_02202254
	mov r0, r6
	mov r1, #0x36
	bl MOD04_02202254
	ldr r4, _021E2E0C ; =UNK04_02210704
	mov r5, #0
_021E2DE4:
	ldrb r1, [r4]
	cmp r1, #0
	beq _021E2DF8
	mov r0, r6
	bl MOD04_02202254
_021E2DF8:
	add r5, r5, #1
	cmp r5, #0x9a
	add r4, r4, #0xc
	blt _021E2DE4
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E2E0C: .word UNK04_02210704
	arm_func_end MOD04_021E2D68

	arm_func_start MOD04_021E2E10
MOD04_021E2E10: ; 0x021E2E10
	bx lr
	arm_func_end MOD04_021E2E10

	arm_func_start MOD04_021E2E14
MOD04_021E2E14: ; 0x021E2E14
	bx lr
	arm_func_end MOD04_021E2E14

	arm_func_start MOD04_021E2E18
MOD04_021E2E18: ; 0x021E2E18
	stmdb sp!, {r4, lr}
	mov r4, r1
	cmp r0, #0x32
	bgt _021E2E54
	cmp r0, #0x32
	bge _021E2E9C
	cmp r0, #0xa
	bgt _021E2EF8
	cmp r0, #8
	blt _021E2EF8
	cmp r0, #8
	beq _021E2E74
	cmp r0, #0xa
	beq _021E2E88
	b _021E2EF8
_021E2E54:
	sub r1, r0, #0x33
	cmp r1, #3
	addls pc, pc, r1, lsl #2
	b _021E2EF8
_021E2E64: ; jump table
	b _021E2EB0 ; case 0
	b _021E2EC4 ; case 1
	b _021E2ED8 ; case 2
	b _021E2EE8 ; case 3
_021E2E74:
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x14]
	mov r0, r4
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2E88:
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x16]
	mov r0, r4
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2E9C:
	bl MOD04_021E26E4
	ldr r1, [r0, #0x200]
	mov r0, r4
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2EB0:
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x15]
	mov r0, r4
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2EC4:
	bl MOD04_021E26E4
	ldr r1, [r0, #0x20]
	mov r0, r4
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2ED8:
	mov r0, r4
	mov r1, #3
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2EE8:
	mov r0, r4
	mov r1, #1
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
_021E2EF8:
	subs r1, r0, #0x64
	ldmmiia sp!, {r4, pc}
	cmp r1, #0x9a
	ldmgeia sp!, {r4, pc}
	mov r0, #0xc
	mul r2, r1, r0
	ldr r0, _021E2F5C ; =UNK04_02210704
	ldrb r0, [r0, r2]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, _021E2F60 ; =UNK04_02210705
	ldrb r0, [r0, r2]
	cmp r0, #0
	beq _021E2F44
	ldr r1, _021E2F64 ; =UNK04_0221070C
	mov r0, r4
	ldr r1, [r1, r2]
	bl MOD04_022021C0
	ldmia sp!, {r4, pc}
_021E2F44:
	ldr r1, _021E2F64 ; =UNK04_0221070C
	mov r0, r4
	ldr r1, [r1, r2]
	ldr r1, [r1]
	bl MOD04_02202220
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E2F5C: .word UNK04_02210704
_021E2F60: .word UNK04_02210705
_021E2F64: .word UNK04_0221070C
	arm_func_end MOD04_021E2E18

	arm_func_start MOD04_021E2F68
MOD04_021E2F68: ; 0x021E2F68
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x1c
	mov r8, #0
	mov r7, r8
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r0, #1
	addle sp, sp, #0x1c
	ldmleia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov sb, r8
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r0, #0
	ble _021E2FF8
	ldr r4, _021E30D8 ; =UNK04_0220BAC4
	ldr r6, _021E30DC ; =UNK04_0220D3A0
	mvn r5, #0
_021E2FB4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, sb
	bl MOD04_02203BF4
	mov r1, r6
	mov r2, r5
	bl MOD04_0220394C
	cmp r0, r8
	movgt r8, r0
	ldr r0, [r4, sb, lsl #2]
	add sb, sb, #1
	add r7, r7, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp sb, r0
	blt _021E2FB4
_021E2FF8:
	mov r0, #0x64
	bl MOD04_021DE8C8
	mov sb, r0
	mov r6, #0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r0, #0
	ble _021E3090
	add r5, sp, #0
	mov fp, r6
	mov r4, #0x64
_021E3028:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	sub r0, r0, #1
	cmp r6, r0
	beq _021E3090
	cmp r6, #0
	subgt r0, r6, #1
	ldrgt sl, [r5, r0, lsl #2]
	ldr r0, _021E30D8 ; =UNK04_0220BAC4
	movle sl, fp
	ldr r2, [r0, r6, lsl #2]
	mov r1, r7
	mul r0, r2, r4
	bl _s32_div_f
	add r0, r0, sl
	str r0, [r5, r6, lsl #2]
	ldr r0, [r5, r6, lsl #2]
	cmp sb, r0
	blo _021E3090
	add r6, r6, #1
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r6, r0
	blt _021E3028
_021E3090:
	mvn r0, #0x80000000
	cmp r8, r0
	addlt r8, r8, #1
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, r6
	bl MOD04_02203BF4
	ldr r1, _021E30DC ; =UNK04_0220D3A0
	mov r2, r8
	bl MOD04_02203A48
	bl MOD04_021E26E4
	mov r1, #0
	ldr r0, [r0, #0xe4]
	ldr r2, _021E30DC ; =UNK04_0220D3A0
	mov r3, r1
	bl MOD04_02203BD4
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E30D8: .word UNK04_0220BAC4
_021E30DC: .word UNK04_0220D3A0
	arm_func_end MOD04_021E2F68

	arm_func_start MOD04_021E30E0
MOD04_021E30E0: ; 0x021E30E0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov r1, #0
	str r1, [sp, #4]
	str r0, [sp]
	mov r8, r1
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r0, #0
	ble _021E3268
	mov r0, #0x80
	mov r4, #1
	mov r5, r8
	str r0, [sp, #8]
	mov fp, #0x100
_021E3120:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, r8
	bl MOD04_02203BF4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E31BC
	ldr r1, _021E32D4 ; =UNK04_0220D3AC
	mov r0, r6
	mov r2, r5
	bl MOD04_0220394C
	mov sb, r0
	mov sl, r5
	mov r7, r4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E31B4
_021E3170:
	bl MOD04_021E26E4
	add r0, r0, r7, lsl #2
	ldr r0, [r0, #0xf4]
	cmp sb, r0
	bne _021E31A0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, r6
	bl MOD04_02203C50
	mov sl, r4
	sub r8, r8, #1
	b _021E31B4
_021E31A0:
	add r7, r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r7, r0
	ble _021E3170
_021E31B4:
	cmp sl, #0
	bne _021E3250
_021E31BC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x474]
	cmp r0, #0
	beq _021E3238
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	ldr r1, [r0, #0x478]
	ldr r2, [r7, #0x474]
	mov r0, r8
	blx r2
	mov r7, r0
	cmp r7, #0
	ble _021E321C
	ldr r0, _021E32D8 ; =0x007FFFFF
	cmp r7, r0
	movgt r7, r0
	mov r0, fp
	bl MOD04_021DE8C8
	orr r2, r0, r7, lsl #8
	ldr r1, _021E32DC ; =UNK04_0220D3A0
	mov r0, r6
	bl MOD04_02203A48
	b _021E3250
_021E321C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, r6
	bl MOD04_02203C50
	str r4, [sp, #4]
	sub r8, r8, #1
	b _021E3250
_021E3238:
	ldr r0, [sp, #8]
	bl MOD04_021DE8C8
	mov r2, r0
	ldr r1, _021E32DC ; =UNK04_0220D3A0
	mov r0, r6
	bl MOD04_02203A48
_021E3250:
	add r8, r8, #1
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r8, r0
	blt _021E3120
_021E3268:
	ldr r0, [sp]
	cmp r0, #0
	beq _021E32A0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r0, #0
	beq _021E32A0
	bl MOD04_021E26E4
	mov r1, #0
	ldr r0, [r0, #0xe4]
	ldr r2, _021E32DC ; =UNK04_0220D3A0
	mov r3, r1
	bl MOD04_02203BD4
_021E32A0:
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _021E32C8
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BE4
	cmp r0, #0
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E32C8:
	mov r0, #1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E32D4: .word UNK04_0220D3AC
_021E32D8: .word 0x007FFFFF
_021E32DC: .word UNK04_0220D3A0
	arm_func_end MOD04_021E30E0

	arm_func_start MOD04_021E32E0
MOD04_021E32E0: ; 0x021E32E0
	bx lr
	arm_func_end MOD04_021E32E0

	arm_func_start MOD04_021E32E4
MOD04_021E32E4: ; 0x021E32E4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r6, r0
	cmp r1, #0
	beq _021E330C
	cmp r1, #4
	beq _021E331C
	add sp, sp, #4
	cmp r1, #5
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E330C:
	mov r0, r2
	bl MOD04_021E32E0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E331C:
	mov r5, #0
	bl MOD04_02203BE4
	cmp r0, #0
	ble _021E336C
_021E332C:
	mov r0, r6
	mov r1, r5
	bl MOD04_02203BF4
	mov r4, r0
	bl MOD04_021E3F98
	cmp r0, #0
	bne _021E3358
	mov r0, r6
	mov r1, r4
	bl MOD04_02203C50
	sub r5, r5, #1
_021E3358:
	mov r0, r6
	add r5, r5, #1
	bl MOD04_02203BE4
	cmp r5, r0
	blt _021E332C
_021E336C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #2
	beq _021E3394
	cmp r0, #3
	beq _021E348C
	cmp r0, #5
	beq _021E3508
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E3394:
	mov r0, r6
	mov r5, #0
	bl MOD04_02203BE4
	cmp r0, #0
	ble _021E3424
_021E33A8:
	mov r0, r6
	mov r1, r5
	bl MOD04_02203BF4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	beq _021E3410
	bl MOD04_021E26E4
	mov r7, r0
	mov r0, r4
	bl MOD04_02203908
	ldr r1, [r7, #0x1c]
	cmp r1, r0
	bne _021E3410
	bl MOD04_021E26E4
	ldrh r0, [r0, #0x1a]
	cmp r0, #0
	beq _021E3410
	bl MOD04_021E26E4
	mov r7, r0
	mov r0, r4
	bl MOD04_022038E4
	ldrh r1, [r7, #0x1a]
	cmp r1, r0
	beq _021E3424
_021E3410:
	mov r0, r6
	add r5, r5, #1
	bl MOD04_02203BE4
	cmp r5, r0
	blt _021E33A8
_021E3424:
	mov r0, r6
	bl MOD04_02203BE4
	cmp r5, r0
	bge _021E3464
	mov r0, #3
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x204]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	bl MOD04_021E7E5C
	bl MOD04_021E38E8
	add sp, sp, #4
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E3464:
	bl MOD04_021E26E4
	mov r1, #2
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0xec]
	add sp, sp, #4
	str r1, [r4, #0xf0]
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E348C:
	mov r0, #1
	bl MOD04_021E30E0
	bl MOD04_021E2F68
	mov r0, r6
	bl MOD04_02203BE4
	cmp r0, #0
	beq _021E34E0
	mov r0, #0
	mov r1, r0
	bl MOD04_021E6038
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, r6, r7, pc}
	mov r0, #4
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0xe8]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E34E0:
	bl MOD04_021E26E4
	mov r1, #2
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0xec]
	add sp, sp, #4
	str r1, [r4, #0xf0]
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E3508:
	mov r0, r6
	bl MOD04_02203BE4
	cmp r0, #0
	beq _021E3580
	mov r4, #0
_021E351C:
	mov r0, r6
	mov r1, r4
	bl MOD04_02203BF4
	mov r5, r0
	bl MOD04_02203908
	mov r7, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1b8]
	cmp r7, r0
	bne _021E3564
	mov r0, r5
	bl MOD04_022038E4
	mov r7, r0
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb4]
	cmp r7, r0
	beq _021E3580
_021E3564:
	mov r0, r6
	mov r1, r5
	bl MOD04_02203C50
	mov r0, r6
	bl MOD04_02203BE4
	cmp r0, #0
	bne _021E351C
_021E3580:
	mov r0, r6
	bl MOD04_02203BE4
	cmp r0, #0
	beq _021E3684
	mov r0, r6
	mov r1, #0
	bl MOD04_02203BF4
	ldr r1, _021E36AC ; =UNK04_0220D3AC
	mov r2, #0
	bl MOD04_0220394C
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E3650
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	cmp r4, r0
	bne _021E3650
	mov r0, #0
	bl MOD04_021E30E0
	cmp r0, #0
	beq _021E3604
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E3650
	bl MOD04_021E5824
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E3650
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E3604:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5BF0
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, r6, r7, pc}
	mov r0, #4
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, r0
	mov r0, #0
	ldr r2, [r1, #0xf4]
	mov r1, r0
	bl MOD04_021E5D30
	bl MOD04_021E61EC
	add sp, sp, #4
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E3650:
	mov r0, #6
	bl MOD04_021E26D0
	mov r0, r6
	mov r1, #0
	bl MOD04_02203BF4
	mov r2, r0
	mov r0, #0
	mov r1, r0
	bl MOD04_021E7B04
	bl MOD04_021E37A4
	add sp, sp, #4
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E3684:
	bl MOD04_021E26E4
	mov r1, #2
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0xec]
	str r1, [r4, #0xf0]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E36AC: .word UNK04_0220D3AC
	arm_func_end MOD04_021E32E4

	arm_func_start MOD04_021E36B0
MOD04_021E36B0: ; 0x021E36B0
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #7
	addls pc, pc, r4, lsl #2
	b _021E3734
_021E36CC: ; jump table
	b _021E3734 ; case 0
	b _021E36EC ; case 1
	b _021E36F8 ; case 2
	b _021E3708 ; case 3
	b _021E3714 ; case 4
	b _021E36F8 ; case 5
	b _021E3720 ; case 6
	b _021E372C ; case 7
_021E36EC:
	mov r0, #9
	mvn r2, #0
	b _021E3734
_021E36F8:
	mov r0, #0
	mov r2, r0
	mov r4, r0
	b _021E3734
_021E3708:
	mov r0, #6
	mvn r2, #9
	b _021E3734
_021E3714:
	mov r0, #6
	mvn r2, #0x1d
	b _021E3734
_021E3720:
	mov r0, #6
	mvn r2, #0x45
	b _021E3734
_021E372C:
	mov r0, #6
	mvn r2, #0x4f
_021E3734:
	cmp r0, #0
	beq _021E3748
	ldr r1, _021E3750 ; =0xFFFEAC28
	add r1, r2, r1
	bl MOD04_021E8E08
_021E3748:
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E3750: .word 0xFFFEAC28
	arm_func_end MOD04_021E36B0

	arm_func_start MOD04_021E3754
MOD04_021E3754: ; 0x021E3754
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #1
	beq _021E3778
	cmp r4, #2
	beq _021E3780
	b _021E3788
_021E3778:
	mov r0, #1
	ldmia sp!, {r4, pc}
_021E3780:
	mov r0, #2
	ldmia sp!, {r4, pc}
_021E3788:
	movs r0, #6
	beq _021E3798
	ldr r1, _021E37A0 ; =0xFFFEB007
	bl MOD04_021E8E08
_021E3798:
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E37A0: .word 0xFFFEB007
	arm_func_end MOD04_021E3754

	arm_func_start MOD04_021E37A4
MOD04_021E37A4: ; 0x021E37A4
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #1
	beq _021E37D4
	cmp r4, #2
	beq _021E37E0
	cmp r4, #3
	moveq r0, #6
	mvneq r2, #0x1d
	b _021E37E8
_021E37D4:
	mov r0, #9
	mvn r2, #0
	b _021E37E8
_021E37E0:
	mov r0, #6
	mvn r2, #0x31
_021E37E8:
	ldr r1, _021E37FC ; =0xFFFEB010
	add r1, r2, r1
	bl MOD04_021E8E08
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E37FC: .word 0xFFFEB010
	arm_func_end MOD04_021E37A4

	arm_func_start MOD04_021E3800
MOD04_021E3800: ; 0x021E3800
	stmdb sp!, {r4, r5, r6, lr}
	movs r6, r0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r6, #5
	addls pc, pc, r6, lsl #2
	b _021E386C
_021E381C: ; jump table
	b _021E386C ; case 0
	b _021E3834 ; case 1
	b _021E3840 ; case 2
	b _021E384C ; case 3
	b _021E3858 ; case 4
	b _021E3864 ; case 5
_021E3834:
	mov r4, #6
	mvn r5, #0x31
	b _021E386C
_021E3840:
	mov r4, #6
	mvn r5, #0x3b
	b _021E386C
_021E384C:
	mov r4, #6
	mvn r5, #0x1d
	b _021E386C
_021E3858:
	mov r4, #6
	mvn r5, #0x4f
	b _021E386C
_021E3864:
	mov r4, #6
	mvn r5, #0x13
_021E386C:
	bl MOD04_021DF88C
	cmp r0, #2
	beq _021E388C
	cmp r0, #4
	beq _021E389C
	cmp r0, #5
	beq _021E38B0
	b _021E38C4
_021E388C:
	mov r0, r4
	sub r1, r5, #0xfa00
	bl MOD04_021E0EAC
	b _021E38D4
_021E389C:
	ldr r1, _021E38DC ; =0xFFFEDEF0
	mov r0, r4
	add r1, r5, r1
	bl MOD04_021E2114
	b _021E38D4
_021E38B0:
	ldr r1, _021E38E0 ; =0xFFFEB7E0
	mov r0, r4
	add r1, r5, r1
	bl MOD04_021E8E08
	b _021E38D4
_021E38C4:
	ldr r1, _021E38E4 ; =0xFFFE90D0
	mov r0, r4
	add r1, r5, r1
	bl MOD04_021DD6B0
_021E38D4:
	mov r0, r6
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E38DC: .word 0xFFFEDEF0
_021E38E0: .word 0xFFFEB7E0
_021E38E4: .word 0xFFFE90D0
	arm_func_end MOD04_021E3800

	arm_func_start MOD04_021E38E8
MOD04_021E38E8: ; 0x021E38E8
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #6
	addls pc, pc, r4, lsl #2
	b _021E3964
_021E3904: ; jump table
	b _021E3964 ; case 0
	b _021E3920 ; case 1
	b _021E392C ; case 2
	b _021E3938 ; case 3
	b _021E3944 ; case 4
	b _021E3950 ; case 5
	b _021E395C ; case 6
_021E3920:
	mov r0, #6
	mvn r2, #0x31
	b _021E3964
_021E392C:
	mov r0, #6
	mvn r2, #0x1d
	b _021E3964
_021E3938:
	mov r0, #6
	mvn r2, #0x13
	b _021E3964
_021E3944:
	mov r0, #6
	mvn r2, #0x27
	b _021E3964
_021E3950:
	mov r0, #9
	mvn r2, #0
	b _021E3964
_021E395C:
	mov r0, #9
	mvn r2, #1
_021E3964:
	ldr r1, _021E3978 ; =0xFFFEB3F8
	add r1, r2, r1
	bl MOD04_021E8E08
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E3978: .word 0xFFFEB3F8
	arm_func_end MOD04_021E38E8

	arm_func_start MOD04_021E397C
MOD04_021E397C: ; 0x021E397C
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #4
	addls pc, pc, r4, lsl #2
	b _021E39D8
_021E3998: ; jump table
	b _021E39D8 ; case 0
	b _021E39AC ; case 1
	b _021E39B8 ; case 2
	b _021E39C4 ; case 3
	b _021E39D0 ; case 4
_021E39AC:
	mov r0, #9
	mvn r2, #0
	b _021E39D8
_021E39B8:
	mov r0, #9
	mvn r2, #1
	b _021E39D8
_021E39C4:
	mov r0, #6
	mvn r2, #9
	b _021E39D8
_021E39D0:
	mov r0, #6
	mvn r2, #0x13
_021E39D8:
	ldr r1, _021E39EC ; =0xFFFEC398
	add r1, r2, r1
	bl MOD04_021E8E08
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E39EC: .word 0xFFFEC398
	arm_func_end MOD04_021E397C

	arm_func_start MOD04_021E39F0
MOD04_021E39F0: ; 0x021E39F0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #8
	ldr r0, _021E3E1C ; =UNK04_022106D4
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldrb r0, [r0]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x13
	bne _021E3C58
	mov r0, #0
	bl MOD04_021E3EC4
	ldr r1, _021E3E1C ; =UNK04_022106D4
	ldr r5, [r1]
	ldr r1, [r5, #8]
	cmp r1, r0
	bne _021E3B2C
	ldr r1, [r5, #0xc]
	cmp r1, r0
	bne _021E3AB8
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	strb r0, [r4, #0x16]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	mov r0, #0
	sub r1, r1, #1
	strb r1, [r4, #0x1a4]
	bl MOD04_021E51C0
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3AB8:
	bl OS_GetTick
	str r0, [r5, #0x18]
	str r1, [r5, #0x1c]
	mov r0, #0
	str r0, [r5, #8]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E3B0C
	mov r0, #3
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #2
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0xec]
	add sp, sp, #8
	str r1, [r4, #0xf0]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3B0C:
	mov r0, #4
	bl MOD04_021E26D0
	mov r1, #0
	mov r2, r1
	mov r0, #1
	bl MOD04_021E5D30
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3B2C:
	ldrb r4, [r5, #2]
	bl OS_GetTick
	ldr r3, [r5, #0x18]
	ldr r2, [r5, #0x1c]
	subs r3, r0, r3
	sbc r0, r1, r2
	mov r1, r0, lsl #6
	ldr r2, _021E3E20 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E3E24 ; =0x00001770
	mul r2, r4, r2
	cmp r1, r2, asr #31
	cmpeq r0, r2
	addlo sp, sp, #8
	ldmloia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	cmp r4, #5
	bls _021E3B98
	mov r0, #1
	bl MOD04_021E3E28
	bl MOD04_021E4B40
	mov r0, #1
	bl MOD04_021E4CF8
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3B98:
	mov r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E3C3C
	ldr r8, _021E3E1C ; =UNK04_022106D4
	mov r5, #0
	mov r4, #0x11
	mov r6, r7
_021E3BBC:
	bl MOD04_021E26E4
	add r0, r0, r7
	ldrb r0, [r0, #0x2d0]
	ldr r1, [r8]
	mov r0, r6,lsl  r0
	ldr r1, [r1, #8]
	ands r0, r1, r0
	bne _021E3C28
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	mov sb, r0
	bl MOD04_021E26E4
	str r5, [sp]
	str r5, [sp, #4]
	add r0, r0, r7, lsl #1
	add r1, sl, r7, lsl #2
	add r2, sb, r7, lsl #2
	ldrh r3, [r0, #0xa4]
	ldr r1, [r1, #0xf4]
	ldr r2, [r2, #0x24]
	mov r0, r4
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3C28:
	add r7, r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r7, r0
	ble _021E3BBC
_021E3C3C:
	ldr r0, _021E3E1C ; =UNK04_022106D4
	add sp, sp, #8
	ldr r1, [r0]
	ldrb r0, [r1, #2]
	add r0, r0, #1
	strb r0, [r1, #2]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3C58:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	beq _021E3C7C
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #3
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3C7C:
	ldr r0, _021E3E1C ; =UNK04_022106D4
	ldr r4, [r0]
	bl MOD04_021E26E4
	ldrb r1, [r4, #1]
	ldrb r2, [r0, #0xd]
	sub r0, r1, #1
	cmp r2, r0
	addlt sp, sp, #8
	ldmltia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldrb r0, [r4, #2]
	cmp r0, #0
	bne _021E3CF0
	ldr r0, _021E3E1C ; =UNK04_022106D4
	ldr r4, [r0]
	bl OS_GetTick
	ldr r3, [r4, #0x10]
	ldr r2, [r4, #0x14]
	subs r3, r0, r3
	sbc r0, r1, r2
	mov r1, r0, lsl #6
	ldr r2, _021E3E20 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, [r4, #4]
	cmp r1, #0
	cmpeq r0, r2
	bhs _021E3D48
_021E3CF0:
	ldrb r0, [r4, #2]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldr r0, _021E3E1C ; =UNK04_022106D4
	ldr r4, [r0]
	bl OS_GetTick
	ldr r3, [r4, #0x18]
	ldr r2, [r4, #0x1c]
	subs r3, r0, r3
	sbc r0, r1, r2
	mov r1, r0, lsl #6
	ldr r2, _021E3E20 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, [r4, #4]
	cmp r1, #0
	cmpeq r0, r2, lsr #2
	addlo sp, sp, #8
	ldmloia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3D48:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r0, #0
	beq _021E3D74
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	bl MOD04_021E5BF0
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E3D74:
	mov r0, #0x13
	bl MOD04_021E26D0
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E3DF8
	mov r6, #0
	mov r5, #0x11
_021E3D98:
	bl MOD04_021E26E4
	mov r8, r0
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	str r6, [sp]
	str r6, [sp, #4]
	add r0, r0, r4, lsl #1
	add r1, r8, r4, lsl #2
	add r2, r7, r4, lsl #2
	ldrh r3, [r0, #0xa4]
	ldr r1, [r1, #0xf4]
	ldr r2, [r2, #0x24]
	mov r0, r5
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E3D98
_021E3DF8:
	ldr r0, _021E3E1C ; =UNK04_022106D4
	ldr r4, [r0]
	bl OS_GetTick
	str r0, [r4, #0x18]
	str r1, [r4, #0x1c]
	mov r0, #1
	strb r0, [r4, #2]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_021E3E1C: .word UNK04_022106D4
_021E3E20: .word 0x000082EA
_021E3E24: .word 0x00001770
	arm_func_end MOD04_021E39F0

	arm_func_start MOD04_021E3E28
MOD04_021E3E28: ; 0x021E3E28
	stmdb sp!, {r4, lr}
	ldr r1, _021E3E98 ; =UNK04_022106D4
	mov r4, r0
	ldr r3, [r1]
	cmp r3, #0
	ldmeqia sp!, {r4, pc}
	ldrb r0, [r3]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	mov r2, #0
	str r2, [r3, #8]
	ldr r0, [r1]
	str r2, [r0, #0xc]
	ldr r0, [r1]
	strb r2, [r0, #2]
	bl OS_GetTick
	ldr r2, _021E3E98 ; =UNK04_022106D4
	cmp r4, #0
	ldr r2, [r2]
	str r0, [r2, #0x18]
	str r1, [r2, #0x1c]
	ldmneia sp!, {r4, pc}
	bl OS_GetTick
	ldr r2, _021E3E98 ; =UNK04_022106D4
	ldr r2, [r2]
	str r0, [r2, #0x10]
	str r1, [r2, #0x14]
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E3E98: .word UNK04_022106D4
	arm_func_end MOD04_021E3E28

	arm_func_start MOD04_021E3E9C
MOD04_021E3E9C: ; 0x021E3E9C
	stmdb sp!, {r4, lr}
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ad]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1f8]
	str r1, [r4, #0x1fc]
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E3E9C

	arm_func_start MOD04_021E3EC4
MOD04_021E3EC4: ; 0x021E3EC4
	stmdb sp!, {r4, r5, r6, lr}
	cmp r0, #0
	mov r6, #0
	beq _021E3EE4
	bl MOD04_021E26E4
	ldr r0, [r0, #0x2f0]
	bic r0, r0, #1
	ldmia sp!, {r4, r5, r6, pc}
_021E3EE4:
	mov r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E3F20
	mov r4, r5
_021E3EFC:
	bl MOD04_021E26E4
	add r0, r0, r5
	ldrb r0, [r0, #0x2d0]
	add r5, r5, #1
	orr r6, r6, r4, lsl r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r5, r0
	ble _021E3EFC
_021E3F20:
	mov r0, r6
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E3EC4

	arm_func_start MOD04_021E3F28
MOD04_021E3F28: ; 0x021E3F28
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	cmp r1, #0
	moveq r4, #1
	mov r5, r0
	movne r4, #0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	bgt _021E3F8C
_021E3F50:
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r5, r0
	bne _021E3F78
	bl MOD04_021E26E4
	add r0, r0, r4
	add sp, sp, #4
	ldrb r0, [r0, #0x2d0]
	ldmia sp!, {r4, r5, pc}
_021E3F78:
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E3F50
_021E3F8C:
	mov r0, #0xff
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021E3F28

	arm_func_start MOD04_021E3F98
MOD04_021E3F98: ; 0x021E3F98
	stmdb sp!, {r4, lr}
	ldr r1, _021E405C ; =UNK04_0220D3B4
	mvn r2, #0
	mov r4, r0
	bl MOD04_0220394C
	mvn r2, #0
	cmp r0, r2
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, _021E4060 ; =UNK04_0220D3C0
	mov r0, r4
	bl MOD04_0220394C
	mvn r2, #0
	cmp r0, r2
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, _021E4064 ; =UNK04_0220D3CC
	mov r0, r4
	bl MOD04_0220394C
	mvn r2, #0
	cmp r0, r2
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, _021E4068 ; =UNK04_0220D3D8
	mov r0, r4
	bl MOD04_0220394C
	mvn r1, #0
	cmp r0, r1
	bne _021E4028
	ldr r1, _021E4068 ; =UNK04_0220D3D8
	mov r0, r4
	mov r2, #0
	bl MOD04_0220394C
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
_021E4028:
	ldr r1, _021E406C ; =UNK04_0220D3E4
	mov r0, r4
	mvn r2, #0
	bl MOD04_0220394C
	mvn r1, #0
	cmp r0, r1
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r1, _021E4070 ; =UNK04_0220D3AC
	mov r0, r4
	mov r2, #0
	bl MOD04_0220394C
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E405C: .word UNK04_0220D3B4
_021E4060: .word UNK04_0220D3C0
_021E4064: .word UNK04_0220D3CC
_021E4068: .word UNK04_0220D3D8
_021E406C: .word UNK04_0220D3E4
_021E4070: .word UNK04_0220D3AC
	arm_func_end MOD04_021E3F98

	arm_func_start MOD04_021E4074
MOD04_021E4074: ; 0x021E4074
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x2fc]
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	mov r4, #0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x344]
	cmp r0, #0
	ble _021E40E8
_021E40AC:
	bl MOD04_021E26E4
	add r0, r0, r4
	ldrb r0, [r0, #0x304]
	bl MOD04_021E1F84
	cmp r0, #0
	ble _021E40D4
	cmp r0, r5
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, pc}
_021E40D4:
	add r4, r4, #1
	bl MOD04_021E26E4
	ldr r0, [r0, #0x344]
	cmp r4, r0
	blt _021E40AC
_021E40E8:
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021E4074

	arm_func_start MOD04_021E40F4
MOD04_021E40F4: ; 0x021E40F4
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, #0
	mov r4, r6
_021E4100:
	mov r5, r4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r0, #0
	blt _021E413C
_021E4114:
	bl MOD04_021E26E4
	add r0, r0, r5
	ldrb r0, [r0, #0x2d0]
	cmp r6, r0
	beq _021E413C
	add r5, r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r5, r0
	ble _021E4114
_021E413C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r5, r0
	bgt _021E415C
	add r0, r6, #1
	and r6, r0, #0xff
	cmp r6, #0x20
	blo _021E4100
_021E415C:
	mov r0, r6
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E40F4

	arm_func_start MOD04_021E4164
MOD04_021E4164: ; 0x021E4164
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r6, _021E41BC ; =UNK04_02210704
	mov r7, #0
	mov r4, r7
	mov r5, #4
_021E417C:
	ldr r1, [r6, #4]
	cmp r1, #0
	beq _021E4194
	mov r0, r5
	mov r2, r4
	bl MOD04_021DD904
_021E4194:
	add r7, r7, #1
	cmp r7, #0x9a
	add r6, r6, #0xc
	blt _021E417C
	ldr r1, _021E41BC ; =UNK04_02210704
	ldr r2, _021E41C0 ; =0x00000738
	mov r0, #0
	bl MIi_CpuClear32
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E41BC: .word UNK04_02210704
_021E41C0: .word 0x00000738
	arm_func_end MOD04_021E4164

	arm_func_start MOD04_021E41C4
MOD04_021E41C4: ; 0x021E41C4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #8
	beq _021E41FC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xe
	beq _021E41FC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xf
	bne _021E4240
_021E41FC:
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1e8]
	ldr r0, [r0, #0x1ec]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E43D8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	mov r4, r0
	mov r5, r1
	b _021E424C
_021E4240:
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E424C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #8
	beq _021E4270
	cmp r0, #0xe
	beq _021E42A4
	cmp r0, #0xf
	beq _021E43AC
	b _021E43CC
_021E4270:
	ldr r0, _021E43DC ; =0x00001770
	cmp r5, #0
	cmpeq r4, r0
	bls _021E43CC
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	mov r1, #0xe
	bl MOD04_021E4604
	cmp r0, #0
	bne _021E43CC
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E42A4:
	ldr r0, _021E43DC ; =0x00001770
	cmp r5, #0
	cmpeq r4, r0
	bls _021E43CC
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1ac]
	add r1, r1, #1
	strb r1, [r0, #0x1ac]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1ac]
	cmp r0, #5
	bls _021E4330
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1d8]
	bl MOD04_021E4A00
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E4324
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ac]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1e8]
	str r1, [r4, #0x1ec]
	b _021E43CC
_021E4324:
	mov r0, #2
	bl MOD04_021E4CF8
	b _021E43CC
_021E4330:
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E43CC
	mov r5, #0xd
	mov r6, r4
_021E434C:
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	add r0, r0, r4
	ldrb r0, [r0, #0x2d0]
	ldr r1, [r7, #0x1d8]
	mov r0, r6,lsl  r0
	ands r0, r1, r0
	bne _021E4394
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0xf4]
	mov r1, r5
	bl MOD04_021E4604
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
_021E4394:
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E434C
	b _021E43CC
_021E43AC:
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb2]
	cmp r5, r0, asr #31
	cmpeq r4, r0
	bls _021E43CC
	mov r0, #2
	bl MOD04_021E4CF8
_021E43CC:
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E43D8: .word 0x000082EA
_021E43DC: .word 0x00001770
	arm_func_end MOD04_021E41C4

	arm_func_start MOD04_021E43E0
MOD04_021E43E0: ; 0x021E43E0
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD04_021DF88C
	cmp r0, #6
	movne r0, #1
	ldmneia sp!, {r4, r5, r6, pc}
	cmp r5, #0xd
	beq _021E441C
	cmp r5, #0xe
	beq _021E4458
	cmp r5, #0xf
	beq _021E45E0
	b _021E45F8
_021E441C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #8
	beq _021E443C
	mov r0, #8
	bl MOD04_021E26D0
	mov r0, r4
	bl MOD04_021E4B78
_021E443C:
	mov r0, r6
	mov r1, #0xe
	bl MOD04_021E4604
	cmp r0, #0
	bne _021E45F8
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E4458:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xe
	bne _021E45C4
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1e8]
	ldr r0, [r0, #0x1ec]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E4600 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	mov r2, r0, lsr #1
	mov r0, r1, lsr #1
	cmp r0, #0
	orr r2, r2, r1, lsl #31
	cmpeq r2, #0x12c
	bls _021E4524
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1e8]
	ldr r0, [r0, #0x1ec]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E4600 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	mov r3, r0, lsr #1
	mov r0, #0x12c
	orr r3, r3, r1, lsl #31
	rsb r0, r0, #0
	mvn r2, #0
	adds r5, r3, r0
	adc r4, r2, r1, lsr #1
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb2]
	cmp r4, r0, asr #31
	cmpeq r5, r0
	bls _021E4524
	bl MOD04_021E26E4
	add r0, r0, #0x100
	strh r5, [r0, #0xb2]
_021E4524:
	mov r0, r6
	mov r1, #0
	bl MOD04_021E3F28
	mov r4, r0
	cmp r4, #0xff
	beq _021E4550
	bl MOD04_021E26E4
	ldr r2, [r0, #0x1d8]
	mov r1, #1
	orr r1, r2, r1, lsl r4
	str r1, [r0, #0x1d8]
_021E4550:
	mov r0, #1
	bl MOD04_021E3EC4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1d8]
	cmp r4, r0
	bne _021E45F8
	mov r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E45B8
	mov r4, #0xf
_021E4584:
	bl MOD04_021E26E4
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xf4]
	mov r1, r4
	bl MOD04_021E4604
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	add r5, r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r5, r0
	ble _021E4584
_021E45B8:
	mov r0, #0xf
	bl MOD04_021E26D0
	b _021E45F8
_021E45C4:
	mov r0, r6
	mov r1, #0xf
	bl MOD04_021E4604
	cmp r0, #0
	bne _021E45F8
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E45E0:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #8
	bne _021E45F8
	mov r0, #2
	bl MOD04_021E4CF8
_021E45F8:
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E4600: .word 0x000082EA
	arm_func_end MOD04_021E43E0

	arm_func_start MOD04_021E4604
MOD04_021E4604: ; 0x021E4604
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	mov r5, r1
	cmp r5, #0xd
	mov r6, r0
	movne r4, #0
	bne _021E4630
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	mov r4, #1
	str r0, [sp, #8]
_021E4630:
	add r0, sp, #8
	str r0, [sp]
	mov r2, #0
	mov r0, r5
	mov r1, r6
	mov r3, r2
	str r4, [sp, #4]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x10
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1e8]
	str r1, [r4, #0x1ec]
	mov r0, #1
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E4604

	arm_func_start MOD04_021E4684
MOD04_021E4684: ; 0x021E4684
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #9
	beq _021E46BC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x10
	beq _021E46BC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x11
	bne _021E4700
_021E46BC:
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1e0]
	ldr r0, [r0, #0x1e4]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E4908 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	mov r4, r0
	mov r5, r1
	b _021E470C
_021E4700:
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E470C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #9
	beq _021E4730
	cmp r0, #0x10
	beq _021E47A0
	cmp r0, #0x11
	beq _021E48DC
	b _021E48FC
_021E4730:
	ldr r0, _021E490C ; =0x00001770
	cmp r5, #0
	cmpeq r4, r0
	bls _021E48FC
	bl MOD04_021DF88C
	cmp r0, #5
	bne _021E477C
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1ad]
	cmp r0, #5
	blo _021E477C
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5908
	cmp r0, #0
	bne _021E48FC
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E477C:
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1ad]
	add r1, r1, #1
	strb r1, [r0, #0x1ad]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x2d0]
	mov r1, #3
	bl MOD04_021E4910
	b _021E48FC
_021E47A0:
	ldr r0, _021E490C ; =0x00001770
	cmp r5, #0
	cmpeq r4, r0
	bls _021E48FC
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1ab]
	add r1, r1, #1
	strb r1, [r0, #0x1ab]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1ab]
	cmp r0, #5
	bls _021E4870
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E47F0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E4800
_021E47F0:
	bl MOD04_021E4B40
	mov r0, #1
	bl MOD04_021E4CF8
	b _021E48FC
_021E4800:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1d4]
	bl MOD04_021E4A00
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E4850
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ab]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1e0]
	str r1, [r4, #0x1e4]
	b _021E48FC
_021E4850:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	bl MOD04_021E59D4
	cmp r0, #0
	bne _021E48FC
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E4870:
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E48FC
	mov r5, #2
	mov r6, r4
_021E488C:
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	add r0, r0, r4
	ldrb r0, [r0, #0x2d0]
	ldr r1, [r7, #0x1d4]
	mov r0, r6,lsl  r0
	ands r0, r1, r0
	bne _021E48C4
	bl MOD04_021E26E4
	add r0, r0, r4
	ldrb r0, [r0, #0x2d0]
	mov r1, r5
	bl MOD04_021E4910
_021E48C4:
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E488C
	b _021E48FC
_021E48DC:
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb0]
	cmp r5, r0, asr #31
	cmpeq r4, r0
	bls _021E48FC
	mov r0, #4
	bl MOD04_021E51C0
_021E48FC:
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E4908: .word 0x000082EA
_021E490C: .word 0x00001770
	arm_func_end MOD04_021E4684

	arm_func_start MOD04_021E4910
MOD04_021E4910: ; 0x021E4910
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r4, r1
	mov r5, r0
	cmp r4, #2
	beq _021E4934
	cmp r4, #3
	beq _021E49AC
	b _021E49D0
_021E4934:
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r6, r0
	ldrb r0, [r0, #0x2d0]
	mov r6, #1
	cmp r5, r0
	moveq r0, #1
	streqb r0, [sp]
	movne r0, #0
	strneb r0, [sp]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blo _021E49D0
_021E4974:
	bl MOD04_021E26E4
	add r0, r0, r6
	ldrb r0, [r0, #0x2d0]
	cmp r5, r0
	streqb r6, [sp, #1]
	streqb r5, [sp, #2]
	beq _021E49D0
	add r0, r6, #1
	and r6, r0, #0xff
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r6, r0
	bls _021E4974
	b _021E49D0
_021E49AC:
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb0]
	strb r0, [sp]
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb0]
	mov r0, r0, asr #8
	strb r0, [sp, #1]
_021E49D0:
	add r2, sp, #0
	mov r0, r4
	mov r1, r5
	mov r3, #4
	bl MOD04_021EAF20
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1e0]
	str r1, [r4, #0x1e4]
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E4910

	arm_func_start MOD04_021E4A00
MOD04_021E4A00: ; 0x021E4A00
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #0x108
	mov sb, #0
	mov sl, r0
	mov r8, sb
	mov r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E4A8C
	add r4, sp, #8
	add r5, sp, #0x88
	mov r6, r7
_021E4A34:
	bl MOD04_021E26E4
	add r0, r0, r7
	ldrb r0, [r0, #0x2d0]
	mov r0, r6,lsl  r0
	ands r0, sl, r0
	beq _021E4A64
	bl MOD04_021E26E4
	add r0, r0, r7, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [r5, r8, lsl #2]
	add r8, r8, #1
	b _021E4A78
_021E4A64:
	bl MOD04_021E26E4
	add r0, r0, r7, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [r4, sb, lsl #2]
	add sb, sb, #1
_021E4A78:
	add r7, r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r7, r0
	ble _021E4A34
_021E4A8C:
	cmp r8, #0
	mov sl, #0
	ble _021E4AE4
	add r7, sp, #8
	add r5, sp, #0x88
	mov r4, sl
	mov r6, #0x10
_021E4AA8:
	str r7, [sp]
	str sb, [sp, #4]
	ldr r1, [r5, sl, lsl #2]
	mov r0, r6
	mov r2, r4
	mov r3, r4
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x108
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	add sl, sl, #1
	cmp sl, r8
	blt _021E4AA8
_021E4AE4:
	bl MOD04_021E26E4
	mov r1, #2
	strb r1, [r0, #0x1a8]
	cmp sb, #0
	mov r6, #0
	ble _021E4B28
	add r5, sp, #8
	mov r4, r6
_021E4B04:
	ldr r0, [r5, r6, lsl #2]
	mov r1, r4
	bl MOD04_021E3F28
	cmp r0, #0xff
	beq _021E4B1C
	bl MOD04_021DF9D4
_021E4B1C:
	add r6, r6, #1
	cmp r6, sb
	blt _021E4B04
_021E4B28:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a8]
	mov r0, #1
	add sp, sp, #0x108
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	arm_func_end MOD04_021E4A00

	arm_func_start MOD04_021E4B40
MOD04_021E4B40: ; 0x021E4B40
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	mov r1, #2
	strb r1, [r0, #0x1a8]
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a8]
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E4B40

	arm_func_start MOD04_021E4B78
MOD04_021E4B78: ; 0x021E4B78
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl MOD04_021E26E4
	str r5, [r0, #0x20c]
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	mov r0, r5
	add r1, r1, #1
	bl MOD04_021DF648
	movs r4, r0
	beq _021E4BD4
	bl MOD04_021E26E4
	mov r1, #2
	strb r1, [r0, #0x1a8]
	ldr r0, [r4]
	bl MOD04_021FD488
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a8]
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, pc}
_021E4BD4:
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	mov r0, r5
	add r1, r1, #1
	bl MOD04_021E89EC
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021E4B78

	arm_func_start MOD04_021E4BF4
MOD04_021E4BF4: ; 0x021E4BF4
	stmdb sp!, {r4, lr}
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a8]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r0, #0
	beq _021E4CA4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E4C64
	mov r0, #3
	bl MOD04_021E26D0
	mov r0, #0
	bl MOD04_021E7E5C
	mov r4, r0
	bl MOD04_021E38E8
	cmp r0, #0
	beq _021E4CAC
	mov r0, r4
	ldmia sp!, {r4, pc}
_021E4C64:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E4CAC
	mov r0, #4
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	mov r1, #0
	bl MOD04_021E6038
	mov r4, r0
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E4CAC
	mov r0, r4
	ldmia sp!, {r4, pc}
_021E4CA4:
	mov r0, #1
	bl MOD04_021E4CF8
_021E4CAC:
	mov r0, #0
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E4BF4

	arm_func_start MOD04_021E4CB4
MOD04_021E4CB4: ; 0x021E4CB4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD04_021E4B40
	mov r0, #1
	bl MOD04_021E4CF8
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E4CB4

	arm_func_start MOD04_021E4CF8
MOD04_021E4CF8: ; 0x021E4CF8
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	movs r4, r0
	bne _021E4D14
	bl MOD04_021E4ED4
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
_021E4D14:
	bl MOD04_021E8174
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	beq _021E4D38
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E4D94
_021E4D38:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	cmp r0, #0
	moveq r6, #1
	movne r6, #0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	bl MOD04_021E1F18
	mov r4, r0
	bl MOD04_021E26E4
	str r4, [sp]
	ldr r1, [r0, #0x468]
	mov r0, #0
	str r1, [sp, #4]
	ldr ip, [r5, #0x464]
	mov r2, r6
	mov r1, #1
	mov r3, r0
	blx ip
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
_021E4D94:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E4DC8
	cmp r4, #1
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, #0
	bl MOD04_021E7E5C
	bl MOD04_021E38E8
	add sp, sp, #8
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E4DC8:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, pc}
	cmp r4, #1
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, #0
	mov r1, r0
	mov r2, r0
	bl MOD04_021E5D30
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E4CF8

	arm_func_start MOD04_021E4E00
MOD04_021E4E00: ; 0x021E4E00
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r4, #0
	str r4, [sp, #8]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17]
	cmp r0, #0
	beq _021E4EC8
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20]
	cmp r0, #0
	beq _021E4EC8
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r1, [r5, #0x20]
	ldr r0, [r0, #0x200]
	cmp r1, r0
	beq _021E4EC8
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	add r2, sp, #8
	mov r1, #1
	str r2, [sp]
	str r1, [sp, #4]
	ldrb r3, [r0, #0xd]
	ldrb r2, [r6, #0xd]
	ldr r1, [r7, #0x20]
	add r3, r3, #1
	add r2, r2, #1
	add r3, r4, r3, lsl #1
	add r2, r5, r2, lsl #2
	ldrh r3, [r3, #0xa4]
	ldr r2, [r2, #0x24]
	mov r0, #0xc
	bl MOD04_021E7884
	mov r4, r0
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20]
_021E4EC8:
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	arm_func_end MOD04_021E4E00

	arm_func_start MOD04_021E4ED4
MOD04_021E4ED4: ; 0x021E4ED4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	ldr r1, _021E4F90 ; =UNK04_0220D3F0
	mov r0, #1
	mov r2, #0
	bl MOD04_021E1E30
	bl MOD04_021E397C
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E8034
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	cmp r0, #0
	movne r6, #1
	bne _021E4F28
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	moveq r6, #1
	movne r6, #0
_021E4F28:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	cmp r0, #0
	moveq r7, #1
	movne r7, #0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	bl MOD04_021E1F18
	mov r4, r0
	bl MOD04_021E26E4
	str r4, [sp]
	ldr r1, [r0, #0x468]
	mov r2, r7
	str r1, [sp, #4]
	ldr ip, [r5, #0x464]
	mov r3, r6
	mov r0, #0
	mov r1, #1
	blx ip
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a9]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E4F90: .word UNK04_0220D3F0
	arm_func_end MOD04_021E4ED4

	arm_func_start MOD04_021E4F94
MOD04_021E4F94: ; 0x021E4F94
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20c]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #2
	bne _021E4FC4
	bl MOD04_021E4ED4
	add sp, sp, #4
	ldmfd sp!, {pc}
_021E4FC4:
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x1a9]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E5038
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x1a9]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E5010
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
	b _021E502C
_021E5010:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5BF0
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_021E502C:
	bl MOD04_021E4ED4
	add sp, sp, #4
	ldmfd sp!, {pc}
_021E5038:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	beq _021E5098
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #5
	beq _021E5098
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #6
	beq _021E5098
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #7
	beq _021E5098
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	beq _021E5098
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xc
	bne _021E50D8
_021E5098:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r0, #0
	beq _021E50C4
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5BF0
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_021E50C4:
	bl MOD04_021E4E00
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
_021E50D8:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	cmp r0, #0
	beq _021E5100
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	bl MOD04_022006B4
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x19c]
_021E5100:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E512C
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x1a9]
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
_021E512C:
	bl MOD04_021E4ED4
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E4F94

	arm_func_start MOD04_021E5138
MOD04_021E5138: ; 0x021E5138
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a6]
	cmp r0, #0
	beq _021E5168
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, pc}
_021E5168:
	cmp r5, #0
	mov r4, #0
	bls _021E51B8
_021E5174:
	ldr r0, [r6, r4, lsl #2]
	bl MOD04_021E4074
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a6]
	cmp r0, #0
	beq _021E51AC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	moveq r0, #1
	ldmeqia sp!, {r4, r5, r6, pc}
_021E51AC:
	add r4, r4, #1
	cmp r4, r5
	blo _021E5174
_021E51B8:
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E5138

	arm_func_start MOD04_021E51C0
MOD04_021E51C0: ; 0x021E51C0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #0x20
	cmp r0, #4
	mov r5, #3
	mov r4, #0
	addls pc, pc, r0, lsl #2
	b _021E57E8
_021E51DC: ; jump table
	b _021E51F0 ; case 0
	b _021E5594 ; case 1
	b _021E55D8 ; case 2
	b _021E569C ; case 3
	b _021E56BC ; case 4
_021E51F0:
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	ldrb r1, [r6, #0x1a4]
	sub r0, r0, #1
	cmp r1, r0
	bge _021E52B0
	mov r0, #0xd
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a4]
	add r0, r0, #1
	add r0, r5, r0, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [sp, #8]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a4]
	add r0, r0, #1
	str r0, [sp, #0xc]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a4]
	add r0, r0, #1
	add r0, r5, r0
	ldrb r0, [r0, #0x2d0]
	str r0, [sp, #0x10]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a4]
	add r0, r0, #1
	add r0, r5, r0, lsl #2
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x14]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a4]
	mov r5, #5
	add r0, r0, #1
	add r0, r6, r0, lsl #1
	ldrh r0, [r0, #0xa4]
	str r0, [sp, #0x18]
	b _021E54FC
_021E52B0:
	bl MOD04_021E26E4
	mov r1, r4
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r1, r4
	str r1, [r0, #0x20]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E52F0
	mov r0, r5
	bl MOD04_021E26D0
	b _021E5314
_021E52F0:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E530C
	mov r0, #4
	bl MOD04_021E26D0
	b _021E5314
_021E530C:
	mov r0, #0xa
	bl MOD04_021E26D0
_021E5314:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a4]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	beq _021E534C
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r1, [r6, #0xd]
	ldrb r0, [r0, #0x16]
	cmp r1, r0
	bne _021E53FC
_021E534C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E5384
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r6, r0, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [r7, #0x20c]
	b _021E53A4
_021E5384:
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20c]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	str r0, [r6, #0xf4]
_021E53A4:
	mov r0, #0x10
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1d4]
	mov r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E54EC
	mov r6, #2
_021E53D0:
	bl MOD04_021E26E4
	add r0, r0, r7
	ldrb r0, [r0, #0x2d0]
	mov r1, r6
	bl MOD04_021E4910
	add r7, r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r7, r0
	ble _021E53D0
	b _021E54EC
_021E53FC:
	mov r0, #0
	str r0, [sp, #8]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	str r0, [sp, #0xc]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r6, r0
	ldrb r0, [r0, #0x2d0]
	str r0, [sp, #0x10]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E5460
	bl MOD04_021E26E4
	mov r1, #2
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r6, r0
	bl OS_GetTick
	str r0, [r6, #0xec]
	str r1, [r6, #0xf0]
	b _021E54EC
_021E5460:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E54EC
	mov r1, #0
	mov r2, r1
	mov r0, #1
	bl MOD04_021E5D30
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a6]
	cmp r0, #0
	bne _021E54EC
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #2
	blo _021E54EC
	bl MOD04_021E26E4
	mov r8, r0
	mov r0, #0
	bl MOD04_021E3EC4
	mov r6, r0
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	mov r1, #1
	ldr r2, [r8, #0x1dc]
	add r0, r7, r0
	ldrb r0, [r0, #0x2d0]
	mvn r0, r1, lsl r0
	and r0, r6, r0
	cmp r2, r0
	beq _021E54EC
	bl MOD04_021E4CB4
	b _021E57E8
_021E54EC:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	movne r4, #1
_021E54FC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x10
	beq _021E57E8
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	mov sb, r0
	bl MOD04_021E26E4
	mov r8, r0
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	add r1, sp, #8
	str r1, [sp]
	str r5, [sp, #4]
	mov ip, r0
	ldrb r3, [sb, #0xd]
	ldrb r2, [r7, #0xd]
	ldrb r1, [ip, #0xd]
	add r5, sl, r3, lsl #2
	add r2, r8, r2, lsl #2
	add r3, r6, r1, lsl #1
	ldrh r3, [r3, #0xa4]
	ldr r1, [r5, #0xf4]
	ldr r2, [r2, #0x24]
	mov r0, #8
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x20
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x3cd]
	b _021E57E8
_021E5594:
	mov r0, #1
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E55D0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [r5, #0x20c]
_021E55D0:
	mov r4, #1
	b _021E57E8
_021E55D8:
	mov r0, #1
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E5600
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E5620
_021E5600:
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	str r0, [r5, #0x20]
_021E5620:
	bl MOD04_021E3E9C
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	bls _021E57E8
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r8, r0
	bl MOD04_021E26E4
	add r3, r8, #0xf4
	ldrb r2, [r0, #0xd]
	mov r1, #1
	mov r0, #9
	sub r2, r2, #1
	add r2, r3, r2, lsl #2
	str r2, [sp]
	str r1, [sp, #4]
	ldr r1, [r7, #0xf4]
	ldr r2, [r6, #0x24]
	ldrh r3, [r5, #0xa4]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E57E8
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E569C:
	mov r0, #1
	bl MOD04_021E26D0
	bl MOD04_021E3E9C
	bl MOD04_021E26E4
	mov r1, r4
	str r1, [r0, #0x20c]
	mov r4, #1
	b _021E57E8
_021E56BC:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	beq _021E56DC
	ldr r1, _021E581C ; =UNK04_0220D3F0
	mov r0, #2
	mov r2, r4
	bl MOD04_021E1E30
_021E56DC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	cmp r0, #0
	moveq r7, #1
	movne r7, #0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	bl MOD04_021E1F18
	mov r5, r0
	bl MOD04_021E26E4
	str r5, [sp]
	ldr r1, [r0, #0x468]
	mov r0, #0
	str r1, [sp, #4]
	ldr r5, [r6, #0x464]
	mov r2, r7
	mov r1, r0
	mov r3, r0
	blx r5
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E5750
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E5758
_021E5750:
	bl MOD04_021E8034
	b _021E57DC
_021E5758:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	cmp r0, #0
	beq _021E5780
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203E80
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0xe4]
_021E5780:
	bl MOD04_02200D6C
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E57C8
	bl MOD04_021E85D4
	bl MOD04_021E397C
	cmp r0, #0
	addne sp, sp, #0x20
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	ldr r0, _021E5820 ; =UNK04_022106DC
	ldrb r1, [r0]
	cmp r1, #1
	moveq r1, #1
	streqb r1, [r0, #1]
	mov r0, #0xa
	bl MOD04_021E26D0
	b _021E57D0
_021E57C8:
	mov r0, #1
	bl MOD04_021E26D0
_021E57D0:
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20c]
_021E57DC:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a9]
_021E57E8:
	cmp r4, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203C04
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_021E581C: .word UNK04_0220D3F0
_021E5820: .word UNK04_022106DC
	arm_func_end MOD04_021E51C0

	arm_func_start MOD04_021E5824
MOD04_021E5824: ; 0x021E5824
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0xc
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E58BC
	mov r5, #0xa
_021E5844:
	bl MOD04_021E26E4
	mov sb, r0
	bl MOD04_021E26E4
	mov r8, r0
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	add r1, r6, #0x348
	str r1, [sp]
	ldr ip, [r0, #0x348]
	add r3, r7, r4, lsl #1
	add ip, ip, #1
	str ip, [sp, #4]
	add r1, sb, r4, lsl #2
	add r2, r8, r4, lsl #2
	ldrh r3, [r3, #0xa4]
	ldr r1, [r1, #0xf4]
	ldr r2, [r2, #0x24]
	mov r0, r5
	bl MOD04_021E7884
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, pc}
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E5844
_021E58BC:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20]
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x1a8]
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a8]
	mov r0, r1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	arm_func_end MOD04_021E5824

	arm_func_start MOD04_021E5908
MOD04_021E5908: ; 0x021E5908
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E5950
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E5938
	bl MOD04_021E4B40
_021E5938:
	ldr r1, _021E59D0 ; =0xFFFEC5D2
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E5950:
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	strb r0, [r5, #0x14]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x208]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	cmp r0, #0
	beq _021E5998
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	bl MOD04_022006B4
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x19c]
_021E5998:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E59B0
	bl MOD04_021E4CB4
	b _021E59C4
_021E59B0:
	mov r0, #4
	bl MOD04_021E26D0
	mov r0, #0
	bl MOD04_021E5C44
	mov r4, r0
_021E59C4:
	mov r0, r4
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E59D0: .word 0xFFFEC5D2
	arm_func_end MOD04_021E5908

	arm_func_start MOD04_021E59D4
MOD04_021E59D4: ; 0x021E59D4
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17]
	cmp r0, #0
	beq _021E5A0C
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r1, [r4, #0x20]
	ldr r0, [r0, #0x200]
	cmp r1, r0
	moveq r4, #0
	beq _021E5A10
_021E5A0C:
	mov r4, #1
_021E5A10:
	cmp r4, #0
	beq _021E5A3C
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
_021E5A3C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0x1f
	bhs _021E5A6C
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	mov r1, #0
	add r0, r0, #1
	add r0, r6, r0, lsl #2
	str r1, [r0, #0xf4]
_021E5A6C:
	bl MOD04_021E26E4
	mov r1, #0xff
	strb r1, [r0, #0x3cc]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	cmp r0, #0
	beq _021E5AA0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	bl MOD04_022006B4
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x19c]
_021E5AA0:
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	strb r0, [r6, #0x14]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x204]
	cmp r4, #0
	bne _021E5AE0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	beq _021E5BE8
	bl MOD04_021E4CB4
	b _021E5BE8
_021E5AE0:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E5B1C
	mov r0, #3
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #2
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0xec]
	str r1, [r4, #0xf0]
	b _021E5BE8
_021E5B1C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E5B48
	mov r0, #4
	bl MOD04_021E26D0
	mov r1, #0
	mov r2, r1
	mov r0, #1
	bl MOD04_021E5D30
	b _021E5BE8
_021E5B48:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E5BE8
	mov r0, #0xe
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1d8]
	bl MOD04_021E26E4
	add r1, r0, #0x100
	mov r2, #0
	mov r0, r5
	strh r2, [r1, #0xb2]
	bl MOD04_021E4B78
	mov r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E5BD0
	mov r4, #0xd
_021E5B9C:
	bl MOD04_021E26E4
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xf4]
	mov r1, r4
	bl MOD04_021E4604
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	add r5, r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r5, r0
	ble _021E5B9C
_021E5BD0:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	bne _021E5BE8
	mov r0, #2
	bl MOD04_021E4CF8
_021E5BE8:
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E59D4

	arm_func_start MOD04_021E5BF0
MOD04_021E5BF0: ; 0x021E5BF0
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldrh r3, [r0, #0xa4]
	ldr r2, [r4, #0x24]
	mov r1, r5
	mov r0, #5
	bl MOD04_021E7884
	mov r4, r0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x204]
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021E5BF0

	arm_func_start MOD04_021E5C44
MOD04_021E5C44: ; 0x021E5C44
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x208]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x204]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a7]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1cc]
	str r1, [r4, #0x1d0]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E5CC0
	mov r0, #3
	bl MOD04_021E26D0
	mov r0, #0
	bl MOD04_021E7E5C
	bl MOD04_021E38E8
	cmp r0, #0
	beq _021E5D20
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E5CC0:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E5CF8
	mov r0, #0
	mov r1, r0
	mov r2, r5
	bl MOD04_021E5D30
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E5D20
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E5CF8:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E5D20
	ldr r1, _021E5D2C ; =0xFFFEC5E6
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E5D20:
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E5D2C: .word 0xFFFEC5E6
	arm_func_end MOD04_021E5C44

	arm_func_start MOD04_021E5D30
MOD04_021E5D30: ; 0x021E5D30
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x23c
	movs r4, r1
	str r0, [sp]
	str r2, [sp, #4]
	beq _021E5D58
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a5]
	str r0, [sp, #0xc]
	b _021E5D90
_021E5D58:
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x344]
	ldrb r1, [r5, #0x1a5]
	sub r0, r0, #1
	cmp r1, r0
	movge r0, #0
	strge r0, [sp, #0xc]
	bge _021E5D90
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a5]
	add r0, r0, #1
	str r0, [sp, #0xc]
_021E5D90:
	cmp r4, #0
	moveq r0, #1
	mov sb, #0
	streq r0, [sp, #8]
	strne sb, [sp, #8]
	mov r7, #1
	mov r8, #0
	mov r5, #0x2f
	mov r4, #0xa
_021E5DB4:
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _021E5DC8
	cmp sb, #0
	beq _021E5DFC
_021E5DC8:
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1a5]
	add r1, r1, #1
	strb r1, [r0, #0x1a5]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r1, [r6, #0x1a5]
	ldr r0, [r0, #0x344]
	cmp r1, r0
	blt _021E5DFC
	bl MOD04_021E26E4
	strb r8, [r0, #0x1a5]
_021E5DFC:
	cmp sb, #0
	beq _021E5E50
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1a5]
	ldr r0, [sp, #0xc]
	cmp r0, r1
	bne _021E5E50
	bl MOD04_021E26E4
	ldr r1, _021E6028 ; =0x00000BB8
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1cc]
	str r1, [r4, #0x1d0]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1bc]
	add sp, sp, #0x23c
	mov r0, r1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E5E50:
	mov sb, r7
	bl MOD04_021E0F00
	mov fp, r0
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r1, r0
	ldrb r2, [r1, #0x1a5]
	ldr r3, [sl, #0x2fc]
	mov r1, #0xc
	add r2, r6, r2
	ldrb r2, [r2, #0x304]
	mov r0, fp
	mla r1, r2, r1, r3
	bl DWC_GetGsProfileId
	movs sl, r0
	beq _021E5DB4
	mvn r0, #0
	cmp sl, r0
	beq _021E5DB4
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov fp, r0
	bl MOD04_021E26E4
	ldr r2, [r6, #0x2fc]
	ldrb r1, [r0, #0x1a5]
	mov r0, #0xc
	add r1, fp, r1
	ldrb r1, [r1, #0x304]
	mla r0, r1, r0, r2
	bl DWCi_Acc_IsValidFriendData
	cmp r0, #0
	beq _021E5DB4
	mov r6, r7
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E5F1C
_021E5EF4:
	bl MOD04_021E26E4
	add r0, r0, r6, lsl #2
	ldr r0, [r0, #0xf4]
	cmp sl, r0
	beq _021E5F1C
	add r6, r6, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r6, r0
	ble _021E5EF4
_021E5F1C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r6, r0
	ble _021E5DB4
	bl MOD04_021E26E4
	ldr r0, [r0]
	mov r1, sl
	add r2, sp, #0x18
	bl MOD04_021F0664
	mov r6, r0
	bl MOD04_021E26E4
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	add r2, sp, #0x28
	bl MOD04_021F06E4
	orrs r0, r6, r0
	bne _021E5DB4
	ldr r0, [sp, #0x2c]
	cmp r0, #4
	bne _021E5DB4
	ldr r0, _021E602C ; =UNK04_0220D3F4
	add r1, sp, #0x1c
	add r2, sp, #0x30
	mov r3, r5
	bl MOD04_021DE9F4
	mov r6, r0
	ldr r0, _021E6030 ; =UNK04_0220D3F8
	add r1, sp, #0x12
	add r2, sp, #0x30
	mov r3, r5
	bl MOD04_021DE9F4
	mov fp, r0
	ldr r0, _021E6034 ; =UNK04_0220D3FC
	add r1, sp, #0x10
	add r2, sp, #0x30
	mov r3, r5
	bl MOD04_021DE9F4
	cmp r6, #0
	ble _021E5DB4
	cmp fp, #0
	ble _021E5DB4
	cmp r0, #0
	ble _021E5DB4
	add r0, sp, #0x1c
	mov r1, r8
	mov r2, r4
	bl strtoul
	cmp r0, #3
	bne _021E5DB4
	add r0, sp, #0x12
	mov r1, r8
	mov r2, r4
	bl strtoul
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x16]
	cmp r6, r0
	bne _021E5DB4
	ldr r0, [sp, #4]
	cmp sl, r0
	moveq r0, #1
	streq r0, [sp]
	ldr r1, [sp]
	mov r0, sl
	bl MOD04_021E6038
	add sp, sp, #0x23c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E6028: .word 0x00000BB8
_021E602C: .word UNK04_0220D3F4
_021E6030: .word UNK04_0220D3F8
_021E6034: .word UNK04_0220D3FC
	arm_func_end MOD04_021E5D30

	arm_func_start MOD04_021E6038
MOD04_021E6038: ; 0x021E6038
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x14
	mov r5, r0
	cmp r1, #0
	bne _021E606C
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	bne _021E60A0
	bl MOD04_021E26E4
	ldrh r0, [r0, #0x1a]
	cmp r0, #0
	bne _021E60A0
_021E606C:
	bl MOD04_021E26E4
	mov r1, #1
	str r1, [r0, #0x1bc]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1c0]
	str r1, [r4, #0x1c4]
	bl MOD04_021E26E4
	str r5, [r0, #0xf4]
	add sp, sp, #0x14
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E60A0:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E6124
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, #0
	bl MOD04_02203BF4
	mov r6, r0
	bl MOD04_021E26E4
	mov r4, r0
	ldr r1, _021E61E4 ; =UNK04_0220D3AC
	mov r0, r6
	mov r2, #0
	bl MOD04_0220394C
	str r0, [r4, #0xf4]
	bl MOD04_021E26E4
	mov r4, r0
	mov r0, r6
	bl MOD04_02203908
	str r0, [r4, #0x24]
	bl MOD04_021E26E4
	mov r4, r0
	mov r0, r6
	bl MOD04_022038E4
	strh r0, [r4, #0xa4]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	mov r4, #1
	str r0, [r6, #0x204]
	b _021E6160
_021E6124:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E613C
	bl MOD04_021E26E4
	str r5, [r0, #0xf4]
_021E613C:
	bl MOD04_021E26E4
	str r5, [r0, #0x204]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c]
	str r0, [sp, #0xc]
	bl MOD04_021E26E4
	ldrh r0, [r0, #0x1a]
	mov r4, #3
	str r0, [sp, #0x10]
_021E6160:
	bl MOD04_021E26E4
	ldr r1, _021E61E8 ; =0x00001770
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	mov r6, r0
	bl OS_GetTick
	str r0, [r6, #0x1cc]
	str r1, [r6, #0x1d0]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1bc]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r0, #0
	movne r7, #0xb
	moveq r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	str r0, [sp, #8]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	add r2, sp, #8
	str r2, [sp]
	mov r3, r0
	str r4, [sp, #4]
	ldrh r3, [r3, #0xa4]
	ldr r2, [r6, #0x24]
	mov r1, r5
	mov r0, r7
	bl MOD04_021E7884
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E61E4: .word UNK04_0220D3AC
_021E61E8: .word 0x00001770
	arm_func_end MOD04_021E6038

	arm_func_start MOD04_021E61EC
MOD04_021E61EC: ; 0x021E61EC
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E6210
	mov r0, r4
	bl MOD04_021E38E8
	ldmia sp!, {r4, pc}
_021E6210:
	mov r0, r4
	bl MOD04_021E397C
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E61EC

	arm_func_start MOD04_021E621C
MOD04_021E621C: ; 0x021E621C
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r1
	ldr r1, [r5]
	mov r6, r0
	add r4, r1, #2
	cmp r4, #2
	bls _021E6250
	bl MOD04_021E26E4
	sub r2, r4, #2
	add r1, r0, #0x350
	add r0, r5, #4
	mov r2, r2, lsl #2
	bl MIi_CpuCopy32
_021E6250:
	bl MOD04_021E26E4
	sub r1, r4, #1
	str r1, [r0, #0x348]
	bl MOD04_021E26E4
	str r6, [r0, #0x34c]
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E621C

	arm_func_start MOD04_021E6268
MOD04_021E6268: ; 0x021E6268
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x14
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17]
	cmp r0, #0
	beq _021E62A4
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20]
	cmp r6, r0
	addeq sp, sp, #0x14
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021E62A4:
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	str r6, [r0, #0x20]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1bc]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x204]
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	add r0, r0, #1
	add r0, r7, r0, lsl #2
	str r6, [r0, #0xf4]
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	add r0, r0, #1
	add r0, r7, r0, lsl #2
	str r5, [r0, #0x24]
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	add r0, r0, #1
	add r0, r7, r0, lsl #1
	strh r4, [r0, #0xa4]
	bl MOD04_021E26E4
	str r5, [r0, #0x1b8]
	bl MOD04_021E26E4
	add r0, r0, #0x100
	strh r4, [r0, #0xb4]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E40F4
	ldrb r1, [r4, #0x14]
	add r1, r1, #1
	add r1, r5, r1
	strb r0, [r1, #0x2d0]
	str r6, [sp, #8]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	mov r7, #1
	add r0, r0, #1
	add r0, r4, r0
	ldrb r0, [r0, #0x2d0]
	str r0, [sp, #0xc]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r0, #1
	blt _021E6414
	add r6, sp, #8
	mov r5, #2
	mov r4, #7
_021E63B8:
	bl MOD04_021E26E4
	mov sb, r0
	bl MOD04_021E26E4
	mov r8, r0
	bl MOD04_021E26E4
	str r6, [sp]
	str r5, [sp, #4]
	add r0, r0, r7, lsl #1
	add r1, sb, r7, lsl #2
	add r2, r8, r7, lsl #2
	ldrh r3, [r0, #0xa4]
	ldr r1, [r1, #0xf4]
	ldr r2, [r2, #0x24]
	mov r0, r4
	bl MOD04_021E7884
	cmp r0, #0
	addne sp, sp, #0x14
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, pc}
	add r7, r7, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r7, r0
	ble _021E63B8
_021E6414:
	mov r0, #1
	bl MOD04_021E3E28
	mov r0, #0
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	arm_func_end MOD04_021E6268

	arm_func_start MOD04_021E6428
MOD04_021E6428: ; 0x021E6428
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r8, r3
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E6490
	cmp r0, #1
	beq _021E6460
	cmp r0, #2
	beq _021E6670
	b _021E6724
_021E6460:
	bl MOD04_021E26E4
	ldr r0, [r0]
	mov r1, r7
	bl MOD04_021F05F4
	cmp r0, #0
	moveq r4, #0xff
	beq _021E6724
	mov r0, r7
	bl MOD04_021E4074
	cmp r0, #0
	moveq r4, #3
	beq _021E6724
_021E6490:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r8, r0
	bne _021E64F8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a9]
	cmp r0, #0
	bne _021E64F8
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r1, [r4, #0x14]
	ldrb r0, [r0, #0x16]
	cmp r1, r0
	beq _021E64F8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17]
	cmp r0, #0
	beq _021E655C
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r1, [r4, #0x20]
	ldr r0, [r0, #0x200]
	cmp r1, r0
	bne _021E655C
_021E64F8:
	mov r4, #3
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E6724
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #0xb4]
	cmp r0, #0
	bne _021E6724
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17]
	cmp r0, #0
	beq _021E6724
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r1, [r5, #0x20]
	ldr r0, [r0, #0x200]
	cmp r1, r0
	bne _021E6724
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	b _021E6724
_021E655C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #3
	beq _021E657C
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	bne _021E65AC
_021E657C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	bne _021E659C
	bl MOD04_021E26E4
	ldrh r0, [r0, #0x1a]
	cmp r0, #0
	beq _021E65AC
_021E659C:
	cmp r6, #0
	bne _021E65B4
	cmp r5, #0
	bne _021E65B4
_021E65AC:
	mov r4, #4
	b _021E6724
_021E65B4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r0, #0
	beq _021E6668
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r7, r0
	bne _021E6610
	ldr r0, [sp, #0x18]
	cmp r0, #0
	bne _021E6600
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	cmp r0, r7
	bge _021E6608
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r7, r0
	beq _021E6608
_021E6600:
	mov r4, #2
	b _021E6724
_021E6608:
	mov r4, #0xff
	b _021E6724
_021E6610:
	ldr r0, [sp, #0x18]
	cmp r0, #0
	bne _021E663C
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	cmp r0, r7
	bge _021E6660
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r0, #0
	bne _021E6660
_021E663C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	bl MOD04_021E5BF0
	bl MOD04_021E61EC
	cmp r0, #0
	movne r0, #0xff
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	mov r4, #2
	b _021E6724
_021E6660:
	mov r4, #3
	b _021E6724
_021E6668:
	mov r4, #2
	b _021E6724
_021E6670:
	bl MOD04_021E26E4
	ldr r0, [r0]
	mov r1, r7
	bl MOD04_021F05F4
	cmp r0, #0
	moveq r4, #0xff
	beq _021E6724
	cmp r8, #3
	bne _021E66B0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r1, [r4, #0x14]
	ldrb r0, [r0, #0x16]
	cmp r1, r0
	bne _021E66B8
_021E66B0:
	mov r4, #3
	b _021E6724
_021E66B8:
	ldr r0, _021E672C ; =UNK04_022106DC
	ldrb r1, [r0]
	cmp r1, #1
	bne _021E66D8
	ldrb r0, [r0, #1]
	cmp r0, #1
	moveq r4, #0x13
	beq _021E6724
_021E66D8:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xa
	bne _021E6718
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	bne _021E6708
	bl MOD04_021E26E4
	ldrh r0, [r0, #0x1a]
	cmp r0, #0
	beq _021E6718
_021E6708:
	cmp r6, #0
	bne _021E6720
	cmp r5, #0
	bne _021E6720
_021E6718:
	mov r4, #4
	b _021E6724
_021E6720:
	mov r4, #2
_021E6724:
	mov r0, r4
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021E672C: .word UNK04_022106DC
	arm_func_end MOD04_021E6428

	arm_func_start MOD04_021E6730
MOD04_021E6730: ; 0x021E6730
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #0x118
	mov sb, r0
	mov r8, r1
	mov r7, r2
	mov sl, r3
	ldr r6, [sp, #0x138]
	ldr r5, [sp, #0x13c]
	mov r4, #0
	bl MOD04_021E26E4
	cmp r0, #0
	beq _021E6770
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0
	bne _021E677C
_021E6770:
	add sp, sp, #0x118
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E677C:
	bl MOD04_021DF88C
	cmp r0, #5
	bne _021E67AC
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E67AC
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	bne _021E67AC
	bl MOD04_021E3E9C
_021E67AC:
	cmp sb, #0x40
	bgt _021E684C
	cmp sb, #0x40
	bge _021E7594
	cmp sb, #0x20
	addls pc, pc, sb, lsl #2
	b _021E7608
_021E67C8: ; jump table
	b _021E7608 ; case 0
	b _021E6854 ; case 1
	b _021E6A20 ; case 2
	b _021E6BF8 ; case 3
	b _021E6C58 ; case 4
	b _021E6D78 ; case 5
	b _021E6DF4 ; case 6
	b _021E6F04 ; case 7
	b _021E701C ; case 8
	b _021E719C ; case 9
	b _021E71F0 ; case 10
	b _021E6854 ; case 11
	b _021E7298 ; case 12
	b _021E730C ; case 13
	b _021E730C ; case 14
	b _021E730C ; case 15
	b _021E7330 ; case 16
	b _021E7380 ; case 17
	b _021E7424 ; case 18
	b _021E7480 ; case 19
	b _021E7608 ; case 20
	b _021E7608 ; case 21
	b _021E7608 ; case 22
	b _021E7608 ; case 23
	b _021E7608 ; case 24
	b _021E7608 ; case 25
	b _021E7608 ; case 26
	b _021E7608 ; case 27
	b _021E7608 ; case 28
	b _021E7608 ; case 29
	b _021E7608 ; case 30
	b _021E7608 ; case 31
	b _021E7498 ; case 32
_021E684C:
	cmp sb, #0x41
	b _021E7608
_021E6854:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	ldrne r0, [r6, #8]
	ldrne r7, [r6, #4]
	movne r0, r0, lsl #0x10
	movne sl, r0, lsr #0x10
	cmp sb, #0xb
	moveq r0, #1
	movne r0, #0
	str r0, [sp]
	ldr r3, [r6]
	mov r0, r8
	mov r1, r7
	mov r2, sl
	bl MOD04_021E6428
	mov r5, r0
	cmp r5, #2
	bne _021E6994
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1dc]
	mov r0, r8
	mov r1, r7
	mov r2, sl
	bl MOD04_021E6268
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x118
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E6918
	bl MOD04_021E26E4
	ldr r0, [r0, #0x46c]
	cmp r0, #0
	beq _021E6918
	bl MOD04_021E26E4
	mov r6, r0
	mov r0, r8
	bl MOD04_021E1F18
	mov r4, r0
	bl MOD04_021E26E4
	ldr r1, [r0, #0x470]
	ldr r2, [r6, #0x46c]
	mov r0, r4
	blx r2
_021E6918:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	mov r4, #1
	str r0, [sp, #0x14]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r0, #1
	blt _021E6960
	add r6, sp, #0x14
_021E693C:
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [r6, r4, lsl #2]
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	cmp r4, r0
	ble _021E693C
_021E6960:
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1c]
	add r0, sp, #0x14
	str r1, [r0, r4, lsl #2]
	bl MOD04_021E26E4
	ldrh r2, [r0, #0x1a]
	add r3, r4, #1
	add r1, sp, #0x14
	mov r0, #0xb
	str r2, [r1, r3, lsl #2]
	add r4, r4, #2
	bl MOD04_021E26D0
	b _021E69E0
_021E6994:
	cmp r5, #3
	bne _021E69E0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x16]
	cmp r0, #0
	beq _021E69E0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r1, [r6, #0x14]
	ldrb r0, [r0, #0x16]
	cmp r1, r0
	bne _021E69E0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	moveq r0, #0x10
	streq r0, [sp, #0x14]
	moveq r4, #1
_021E69E0:
	cmp r5, #0xff
	beq _021E7608
	add r1, sp, #0x14
	str r1, [sp]
	mov r0, r5
	mov r1, r8
	mov r2, r7
	mov r3, sl
	str r4, [sp, #4]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6A20:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	bne _021E7608
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r8, r0
	bne _021E7608
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x208]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a7]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1bc]
	bl MOD04_021E26E4
	ldr r1, [r6]
	add r1, r6, r1, lsl #2
	ldr r1, [r1, #4]
	str r1, [r0, #0x24]
	bl MOD04_021E26E4
	ldr r1, [r6]
	add r1, r6, r1, lsl #2
	ldr r1, [r1, #8]
	strh r1, [r0, #0xa4]
	bl MOD04_021E26E4
	ldr r1, [r6]
	add r1, r6, r1, lsl #2
	ldr r1, [r1, #4]
	str r1, [r0, #0x1b8]
	bl MOD04_021E26E4
	ldr r1, [r6]
	add r0, r0, #0x100
	add r1, r6, r1, lsl #2
	ldr r1, [r1, #8]
	strh r1, [r0, #0xb4]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E6B4C
	ldr r1, [r6]
	add r0, r6, #4
	bl MOD04_021E5138
	cmp r0, #0
	beq _021E6B08
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E6B4C
	mov r0, r8
	mov r1, r6
	bl MOD04_021E621C
	b _021E6B4C
_021E6B08:
	mov r0, r8
	bl MOD04_021E5BF0
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x118
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	mov r0, #0
	mov r1, r0
	mov r2, r8
	bl MOD04_021E5D30
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6B4C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E6BD0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E6B90
	mov r0, r8
	mov r1, r6
	bl MOD04_021E621C
	bl MOD04_021E5824
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x118
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6B90:
	mov r0, #6
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	mov r1, #0
	bl MOD04_02203BF4
	mov r2, r0
	mov r0, #0
	mov r1, r0
	bl MOD04_021E7B04
	bl MOD04_021E37A4
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6BD0:
	mov r0, #5
	bl MOD04_021E26D0
	mov r0, r8
	bl MOD04_021E7E5C
	bl MOD04_021E38E8
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6BF8:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	bne _021E7608
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r8, r0
	bne _021E7608
	cmp r5, #0
	ble _021E6C44
	ldr r0, [r6]
	cmp r0, #0x10
	bne _021E6C44
	mov r0, #0xd
	mov r1, #0
	bl MOD04_021E8E08
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6C44:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	bl MOD04_021E5C44
	add sp, sp, #0x118
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6C58:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #4
	bne _021E7608
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	cmp r8, r0
	bne _021E7608
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1cc]
	str r1, [r4, #0x1d0]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r0, #0
	beq _021E6CAC
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a7]
	cmp r0, #0x10
	blo _021E6CBC
_021E6CAC:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E6D00
_021E6CBC:
	bl MOD04_021E26E4
	mov r1, #1
	str r1, [r0, #0x1bc]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1c0]
	str r1, [r4, #0x1c4]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	beq _021E7608
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1a7]
	add r1, r1, #1
	strb r1, [r0, #0x1a7]
	b _021E7608
_021E6D00:
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x208]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a7]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E6D54
	mov r0, #3
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #1
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0xec]
	str r1, [r4, #0xf0]
	b _021E7608
_021E6D54:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E7608
	mov r1, #0
	mov r2, r1
	mov r0, #1
	bl MOD04_021E5D30
	b _021E7608
_021E6D78:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x17]
	cmp r0, #0
	beq _021E7608
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20]
	cmp r8, r0
	bne _021E7608
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E6DD8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	bne _021E6DD8
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf8]
	cmp r8, r0
	bne _021E6DD8
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
_021E6DD8:
	mov r0, r8
	bl MOD04_021E59D4
	cmp r0, #0
	bne _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6DF4:
	ldr r0, [r6, #4]
	ldr r4, [r6]
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E6E20
	mov r0, #6
	bl MOD04_021E26D0
	b _021E6E50
_021E6E20:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #6
	beq _021E6E40
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	bne _021E7608
_021E6E40:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20]
	cmp r8, r0
	bne _021E7608
_021E6E50:
	bl MOD04_021E26E4
	mov r1, #0xff
	strb r1, [r0, #0x3cc]
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r0, #1
	add r0, r6, r0, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	beq _021E6E9C
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r0, #1
	add r0, r6, r0, lsl #2
	str r8, [r0, #0xf4]
_021E6E9C:
	mov r1, r5, asr #8
	mov r0, r5, lsl #8
	and r1, r1, #0xff
	and r0, r0, #0xff00
	orr r0, r1, r0
	str r4, [sp, #0x10]
	strh r0, [sp, #0xe]
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x194]
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD43C
	mov r4, r0
	bl MOD04_021E26E4
	add r3, r0, #0x194
	mov r1, r4
	mov r0, #0
	add r2, sp, #0xc
	bl MOD04_021E2784
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x18c]
	str r1, [r0, #0x190]
	b _021E7608
_021E6F04:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E7608
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	bne _021E7608
	ldr r0, [r6]
	str r0, [sp, #8]
	ldr r0, [r6, #4]
	and r4, r0, #0xff
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E6F98
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a6]
	cmp r0, #0
	bne _021E6F98
	ldr r0, [sp, #8]
	bl MOD04_021E4074
	str r0, [sp, #0x14]
	add r0, sp, #0x14
	str r0, [sp]
	mov r5, #1
	mov r1, r8
	mov r2, r7
	mov r3, sl
	mov r0, #0x20
	str r5, [sp, #4]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x118
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E6F98:
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	ldr r1, [sp, #8]
	add r0, r0, #1
	add r0, r5, r0, lsl #2
	str r1, [r0, #0xf4]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	add r0, r0, #1
	add r0, r5, r0
	strb r4, [r0, #0x2d0]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	bl MOD04_021E26E4
	ldr r0, [r0, #0x46c]
	cmp r0, #0
	beq _021E7608
	bl MOD04_021E26E4
	mov r5, r0
	ldr r0, [sp, #8]
	bl MOD04_021E1F18
	mov r4, r0
	bl MOD04_021E26E4
	ldr r1, [r0, #0x470]
	ldr r2, [r5, #0x46c]
	mov r0, r4
	blx r2
	b _021E7608
_021E701C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E7608
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	bne _021E7608
	ldr r0, [r6]
	str r0, [sp, #8]
	cmp r0, #0
	bne _021E7084
	ldr r5, [r6, #4]
	ldr r4, [r6, #8]
	bl MOD04_021E26E4
	add r0, r5, r0
	strb r4, [r0, #0x2d0]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r2, [r0, #0x200]
	add r1, r4, r5, lsl #2
	mov r0, #3
	str r2, [r1, #0xf4]
	bl MOD04_021E51C0
	b _021E7608
_021E7084:
	ldr r0, [r6, #8]
	ldr r4, [r6, #4]
	and r5, r0, #0xff
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r1, [sp, #8]
	ldr r0, [r0, #0xf4]
	cmp r1, r0
	bne _021E7104
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	sub r0, r0, #1
	cmp r4, r0
	bne _021E7104
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	add r1, sp, #8
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldrh r3, [r0, #0xa4]
	ldr r2, [r4, #0x24]
	mov r1, r8
	mov r0, #9
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E7104:
	bl MOD04_021E26E4
	ldr r1, [sp, #8]
	add r0, r0, r4, lsl #2
	str r1, [r0, #0xf4]
	bl MOD04_021E26E4
	add r0, r4, r0
	strb r5, [r0, #0x2d0]
	bl MOD04_021E26E4
	ldr r1, [r6, #0xc]
	add r0, r0, r4, lsl #2
	str r1, [r0, #0x24]
	bl MOD04_021E26E4
	ldr r1, [r6, #0x10]
	add r0, r0, r4, lsl #1
	strh r1, [r0, #0xa4]
	bl MOD04_021E26E4
	ldr r1, [r6, #0xc]
	str r1, [r0, #0x1b8]
	bl MOD04_021E26E4
	add r1, r0, #0x100
	ldr r2, [r6, #0x10]
	mov r0, #5
	strh r2, [r1, #0xb4]
	bl MOD04_021E26D0
	ldr r0, [sp, #8]
	bl MOD04_021E7E5C
	bl MOD04_021E38E8
	cmp r0, #0
	addne sp, sp, #0x118
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1bc]
	b _021E7608
_021E719C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xd
	bne _021E7608
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a4]
	ldr r1, [r6]
	add r0, r0, #1
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r1, r0
	bne _021E7608
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1a4]
	add r1, r1, #1
	strb r1, [r0, #0x1a4]
	mov r0, #0
	bl MOD04_021E51C0
	b _021E7608
_021E71F0:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	beq _021E7210
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x12
	bne _021E7608
_021E7210:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E7234
	ldr r1, [r6]
	add r0, r6, #4
	bl MOD04_021E5138
	cmp r0, #0
	beq _021E7250
_021E7234:
	bl MOD04_021E26E4
	ldr r1, [r6, #4]
	str r1, [r0, #0x208]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a7]
	b _021E725C
_021E7250:
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x208]
_021E725C:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E7280
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
	b _021E7608
_021E7280:
	bl MOD04_021E4BF4
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E7298:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	bne _021E7608
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E72C8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E72E4
_021E72C8:
	mov r0, r8
	bl MOD04_021E5908
	cmp r0, #0
	bne _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E72E4:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E7608
	bl MOD04_021E26E4
	str r8, [r0, #0x20c]
	bl MOD04_021E4B40
	mov r0, #0
	bl MOD04_021E4CF8
	b _021E7608
_021E730C:
	ldr r2, [r6]
	mov r0, r8
	mov r1, sb
	bl MOD04_021E43E0
	cmp r0, #0
	bne _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E7330:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	addne sp, sp, #0x118
	movne r0, #1
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	cmp r5, #0
	mov r7, #0
	ble _021E7608
	mov r4, r7
_021E7358:
	ldr r0, [r6, r7, lsl #2]
	mov r1, r4
	bl MOD04_021E3F28
	cmp r0, #0xff
	beq _021E7370
	bl MOD04_021DF9D4
_021E7370:
	add r7, r7, #1
	cmp r7, r5
	blt _021E7358
	b _021E7608
_021E7380:
	ldr r0, _021E7614 ; =UNK04_022106D4
	ldr r4, [r0]
	cmp r4, #0
	beq _021E73E0
	ldrb r0, [r4]
	cmp r0, #0
	beq _021E73E0
	bl OS_GetTick
	ldr r3, [r4, #0x10]
	ldr r2, [r4, #0x14]
	subs r3, r0, r3
	sbc r0, r1, r2
	mov r1, r0, lsl #6
	ldr r2, _021E7618 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, [r4, #4]
	cmp r1, #0
	cmpeq r0, r2
	movhs r0, #1
	strhs r0, [sp, #0x14]
	bhs _021E73E8
_021E73E0:
	mov r0, #0
	str r0, [sp, #0x14]
_021E73E8:
	add r0, sp, #0x14
	str r0, [sp]
	mov r4, #1
	mov r1, r8
	mov r2, r7
	mov r3, sl
	mov r0, #0x12
	str r4, [sp, #4]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E7424:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x13
	bne _021E7608
	mov r0, r8
	mov r1, #0
	bl MOD04_021E3F28
	cmp r0, #0xff
	beq _021E7608
	ldr r1, _021E7614 ; =UNK04_022106D4
	mov r4, #1
	ldr r3, [r1]
	mov r5, r4,lsl  r0
	ldr r2, [r3, #8]
	orr r0, r2, r4, lsl r0
	str r0, [r3, #8]
	ldr r0, [r6]
	cmp r0, #0
	ldrne r1, [r1]
	ldrne r0, [r1, #0xc]
	orrne r0, r0, r5
	strne r0, [r1, #0xc]
	b _021E7608
_021E7480:
	mov r0, #0xc
	mov r1, #0
	bl MOD04_021E8E08
	add sp, sp, #0x118
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E7498:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E7608
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a6]
	cmp r0, #0
	bne _021E7608
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E7608
_021E74CC:
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	bne _021E757C
	ldr r0, [r6]
	cmp r0, #0
	bne _021E7554
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	beq _021E750C
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xc
	bne _021E7524
_021E750C:
	bl MOD04_021E4E00
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0x118
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E7524:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	cmp r0, #0
	beq _021E754C
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	bl MOD04_022006B4
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x19c]
_021E754C:
	bl MOD04_021E4CB4
	b _021E7608
_021E7554:
	bl MOD04_021E26E4
	mov r4, r0
	mov r0, r8
	mov r1, #0
	bl MOD04_021E3F28
	ldr r2, [r4, #0x1dc]
	mov r1, #1
	orr r0, r2, r1, lsl r0
	str r0, [r4, #0x1dc]
	b _021E7608
_021E757C:
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E74CC
	b _021E7608
_021E7594:
	mov r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E7608
_021E75A8:
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r8, r0
	bne _021E75F4
	mov r4, #0
	str r4, [sp]
	mov r1, r8
	mov r2, r7
	mov r3, sl
	mov r0, #0x41
	str r4, [sp, #4]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E7608
	add sp, sp, #0x118
	mov r0, r4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
_021E75F4:
	add r4, r4, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r4, r0
	ble _021E75A8
_021E7608:
	mov r0, #1
	add sp, sp, #0x118
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_021E7614: .word UNK04_022106D4
_021E7618: .word 0x000082EA
	arm_func_end MOD04_021E6730

	arm_func_start MOD04_021E761C
MOD04_021E761C: ; 0x021E761C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov sb, r1
	mov r4, r0
	mov r8, r2
	mov r0, sb
	mov r1, #0
	bl strchr
	mov r7, r0
	cmp r8, #0
	mov r6, #0
	ble _021E767C
	mov r5, #0x2f
_021E7650:
	mov r0, sb
	mov r1, r5
	bl strchr
	cmp r0, #0
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	add r6, r6, #1
	cmp r6, r8
	add sb, r0, #1
	blt _021E7650
_021E767C:
	mov r0, sb
	mov r1, #0x2f
	bl strchr
	cmp r0, #0
	moveq r0, r7
	cmp sb, r0
	addeq sp, sp, #4
	mvneq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	sub r5, r0, sb
	mov r0, sb
	mov r1, r4
	mov r2, r5
	bl MI_CpuCopy8
	mov r1, #0
	mov r0, r5
	strb r1, [r4, r5]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	arm_func_end MOD04_021E761C

	arm_func_start MOD04_021E76C8
MOD04_021E76C8: ; 0x021E76C8
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x208
	mov r7, r0
	mov r5, r2
	mov r4, r3
	mov r0, #3
	mov r6, r1
	str r0, [sp]
	ldr ip, _021E7760 ; =UNK04_0220D410
	ldr r2, _021E7764 ; =UNK04_0220D400
	ldr r3, _021E7768 ; =UNK04_0220D408
	add r0, sp, #8
	mov r1, #0x200
	str ip, [sp, #4]
	bl OS_SNPrintf
	add r1, sp, #8
	add r2, sp, #9
	strb r6, [r1, r0]
	mov r1, #0
	strb r1, [r2, r0]
	cmp r4, #0
	add r8, r2, r0
	beq _021E7748
	mov r0, r4
	bl strlen
	mov r6, r0
	mov r0, r4
	mov r1, r8
	mov r2, r6
	bl MI_CpuCopy8
	mov r0, #0
	strb r0, [r8, r6]
_021E7748:
	add r2, sp, #8
	mov r0, r7
	mov r1, r5
	bl MOD04_021F02B8
	add sp, sp, #0x208
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021E7760: .word UNK04_0220D410
_021E7764: .word UNK04_0220D400
_021E7768: .word UNK04_0220D408
	arm_func_end MOD04_021E76C8

	arm_func_start MOD04_021E776C
MOD04_021E776C: ; 0x021E776C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x9c
	mov r5, r0
	mov r8, r1
	mov r7, r2
	cmp r3, #0
	ldr r4, [sp, #0xb8]
	beq _021E77A8
	cmp r4, #0
	beq _021E77A8
	add r1, sp, #0x18
	mov r0, r3
	mov r2, r4, lsl #2
	bl MIi_CpuCopy32
	b _021E77AC
_021E77A8:
	mov r4, #0
_021E77AC:
	ldr r6, _021E7880 ; =UNK04_0220D398
	add sb, sp, #4
	ldrb r3, [r6]
	ldrb r2, [r6, #1]
	mov r0, r4, lsl #2
	mov r1, #3
	strb r3, [sb]
	strb r2, [sb, #1]
	ldrb r3, [r6, #2]
	ldrb r2, [r6, #3]
	strb r3, [sb, #2]
	strb r2, [sb, #3]
	ldrb r2, [r6, #4]
	strb r2, [sb, #4]
	str r1, [sp, #8]
	strb r5, [sp, #0xc]
	strb r0, [sp, #0xd]
	bl MOD04_021E26E4
	ldrh r0, [r0, #0x1a]
	strh r0, [sp, #0xe]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c]
	str r0, [sp, #0x10]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	mov r6, #0
	str r0, [sp, #0x14]
	mov r4, r6
_021E781C:
	bl MOD04_021E26E4
	mov r5, r0
	mov r0, r8
	mov r1, r4
	mov r2, r4
	bl MOD04_021FFEB0
	mov r1, r0
	ldrb r0, [sp, #0xd]
	mov r2, r7
	mov r3, sb
	add r0, r0, #0x14
	str r0, [sp]
	ldr r0, [r5, #0xe4]
	bl MOD04_02203CC4
	cmp r0, #0
	addeq sp, sp, #0x9c
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, pc}
	cmp r0, #2
	addne sp, sp, #0x9c
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, pc}
	add r6, r6, #1
	cmp r6, #5
	blt _021E781C
	add sp, sp, #0x9c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_021E7880: .word UNK04_0220D398
	arm_func_end MOD04_021E776C

	arm_func_start MOD04_021E7884
MOD04_021E7884: ; 0x021E7884
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x224
	mov fp, r0
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	ldr sl, [sp, #0x248]
	ldr sb, [sp, #0x24c]
	mov r8, #0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E78E0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	beq _021E78D8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a6]
	cmp r0, #0
	beq _021E7900
_021E78D8:
	cmp fp, #6
	bne _021E7900
_021E78E0:
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	mov r0, fp
	mov r3, sl
	str sb, [sp]
	bl MOD04_021E776C
	mov r4, r0
	b _021E79A0
_021E7900:
	cmp sl, #0
	beq _021E7978
	cmp sb, #0
	beq _021E7978
	ldr r3, [sl]
	ldr r2, _021E7A3C ; =UNK04_0220D394
	add r0, sp, #0x20
	mov r1, #0x200
	bl OS_SNPrintf
	mov r8, r0
	cmp sb, #1
	mov r7, #1
	ble _021E7978
	add r6, sp, #0x10
	mov r5, #0x10
_021E793C:
	ldr r3, [sl, r7, lsl #2]
	ldr r2, _021E7A40 ; =UNK04_0220D414
	mov r0, r6
	mov r1, r5
	bl OS_SNPrintf
	mov r4, r0
	add r1, sp, #0x20
	mov r0, r6
	add r1, r1, r8
	mov r2, r4
	bl MI_CpuCopy8
	add r7, r7, #1
	add r8, r8, r4
	cmp r7, sb
	blt _021E793C
_021E7978:
	add r0, sp, #0x20
	mov r1, #0
	strb r1, [r0, r8]
	bl MOD04_021E26E4
	ldr r0, [r0]
	ldr r2, [sp, #4]
	add r3, sp, #0x20
	mov r1, fp
	bl MOD04_021E76C8
	mov r4, r0
_021E79A0:
	cmp fp, #2
	beq _021E79C0
	cmp fp, #6
	beq _021E79C0
	add r0, fp, #0xf8
	and r0, r0, #0xff
	cmp r0, #1
	bhi _021E7A30
_021E79C0:
	bl MOD04_021E26E4
	strb fp, [r0, #0x3cc]
	bl MOD04_021E26E4
	add r1, r0, #0x300
	ldr r0, [sp, #0xc]
	strh r0, [r1, #0xce]
	bl MOD04_021E26E4
	ldr r1, [sp, #8]
	str r1, [r0, #0x3d0]
	bl MOD04_021E26E4
	ldr r1, [sp, #4]
	str r1, [r0, #0x454]
	bl MOD04_021E26E4
	str sb, [r0, #0x458]
	bl MOD04_021E26E4
	mov r5, r0
	bl OS_GetTick
	str r0, [r5, #0x45c]
	str r1, [r5, #0x460]
	cmp sl, #0
	beq _021E7A30
	cmp sb, #0
	beq _021E7A30
	bl MOD04_021E26E4
	add r1, r0, #0x3d4
	mov r0, sl
	mov r2, sb, lsl #2
	bl MIi_CpuCopy32
_021E7A30:
	mov r0, r4
	add sp, sp, #0x224
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E7A3C: .word UNK04_0220D394
_021E7A40: .word UNK04_0220D414
	arm_func_end MOD04_021E7884

	arm_func_start MOD04_021E7A44
MOD04_021E7A44: ; 0x021E7A44
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldrb r0, [r7]
	cmp r0, #0
	bne _021E7A9C
	bl MOD04_021E26E4
	mov r4, r0
	mov r1, #0
	ldr r0, [r7, #4]
	mov r2, r1
	bl MOD04_021FFEB0
	mov r1, r0
	ldrh r2, [r7, #2]
	ldr r0, [r4, #0xe4]
	ldr r3, [r7, #8]
	bl MOD04_02203C7C
	bl MOD04_021E38E8
	cmp r0, #0
	addne sp, sp, #0xc
	movne r0, #2
	ldmneia sp!, {r4, r5, r6, r7, pc}
_021E7A9C:
	ldr r5, _021E7AFC ; =MOD04_021E2784
	ldr r4, _021E7B00 ; =MOD04_021E2B60
	mov r6, #0
_021E7AA8:
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD43C
	str r5, [sp]
	str r7, [sp, #4]
	ldrb r2, [r7]
	ldr r1, [r7, #8]
	mov r3, r4
	bl MOD04_022006EC
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r0, #3
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	add r6, r6, #1
	cmp r6, #5
	blt _021E7AA8
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E7AFC: .word MOD04_021E2784
_021E7B00: .word MOD04_021E2B60
	arm_func_end MOD04_021E7A44

	arm_func_start MOD04_021E7B04
MOD04_021E7B04: ; 0x021E7B04
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x14
	mov r4, r0
	mov r8, r1
	mov r7, r2
	bl MOD04_021E26E4
	cmp r4, #0
	ldrb r6, [r0, #0x14]
	mov r4, #0
	bne _021E7D48
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	add r1, r0, #0x100
	ldr r2, [r5, #0x200]
	ldr r0, _021E7DEC ; =0x0000FFFF
	ldrh r1, [r1, #0x7e]
	and r2, r2, r0
	mov r0, r7
	orr r8, r2, r1, lsl #16
	bl MOD04_022038C4
	cmp r0, #0
	beq _021E7BC0
	mov r0, r7
	bl MOD04_02203908
	mov r5, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203BCC
	cmp r5, r0
	movne r5, #1
	bne _021E7C48
	bl MOD04_021E26E4
	mov r5, r0
	mov r0, r7
	bl MOD04_022038BC
	add r1, r5, r6, lsl #2
	str r0, [r1, #0x210]
	bl MOD04_021E26E4
	mov r5, r0
	mov r0, r7
	bl MOD04_02203898
	add r1, r5, r6, lsl #1
	add r1, r1, #0x200
	strh r0, [r1, #0x90]
	mov r5, r4
	b _021E7C48
_021E7BC0:
	bl SOC_GetHostID
	mov r0, r0, lsl #0x10
	ldr r1, _021E7DEC ; =0x0000FFFF
	ldr r2, _021E7DF0 ; =0x0000A8C0
	and r1, r1, r0, lsr #16
	cmp r1, r2
	mov r0, r0, lsr #0x10
	beq _021E7C08
	and r1, r0, #0xff
	cmp r1, #0xac
	bne _021E7C00
	and r0, r0, #0xff00
	cmp r0, #0x1000
	blo _021E7C00
	cmp r0, #0x1f00
	bls _021E7C08
_021E7C00:
	cmp r1, #0x10
	bne _021E7C10
_021E7C08:
	mov r5, #1
	b _021E7C48
_021E7C10:
	bl MOD04_021E26E4
	mov r5, r0
	mov r0, r7
	bl MOD04_02203908
	add r1, r5, r6, lsl #2
	str r0, [r1, #0x210]
	bl MOD04_021E26E4
	mov r5, r0
	mov r0, r7
	bl MOD04_022038E4
	add r1, r5, r6, lsl #1
	add r1, r1, #0x200
	strh r0, [r1, #0x90]
	mov r5, #0
_021E7C48:
	cmp r5, #0
	beq _021E7C74
	bl MOD04_021E26E4
	mov r6, r0
	mov r0, #0x10000
	bl MOD04_021DE8C8
	add r1, r6, #0x100
	strh r0, [r1, #0x7e]
	bl MOD04_021E26E4
	str r8, [r0, #0x19c]
	b _021E7D00
_021E7C74:
	bl SOC_GetHostID
	str r0, [sp, #8]
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD454
	str r0, [sp, #0xc]
	bl MOD04_021E26E4
	mov sb, r0
	mov r0, r7
	bl MOD04_02203908
	mov r8, r0
	mov r0, r7
	bl MOD04_022038E4
	add r1, sb, r6, lsl #2
	add r6, sp, #8
	mov r3, r0
	mov r0, #2
	str r6, [sp]
	str r0, [sp, #4]
	ldr r1, [r1, #0xf4]
	mov r2, r8
	mov r0, #6
	bl MOD04_021E7884
	mov r6, r0
	bl MOD04_021E26E4
	mov r1, #0
	cmp r6, #0
	strb r1, [r0, #0x3cd]
	addne sp, sp, #0x14
	movne r0, #2
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, pc}
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x19c]
_021E7D00:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x194]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x195]
	bl MOD04_021E26E4
	mov r6, r0
	mov r0, r7
	bl MOD04_022038E4
	add r1, r6, #0x100
	strh r0, [r1, #0x96]
	bl MOD04_021E26E4
	mov r6, r0
	mov r0, r7
	bl MOD04_02203908
	str r0, [r6, #0x198]
	b _021E7D88
_021E7D48:
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x194]
	bl MOD04_021E26E4
	mov r1, r4
	strb r1, [r0, #0x195]
	bl MOD04_021E26E4
	add r0, r0, #0x100
	mov r1, r4
	strh r1, [r0, #0x96]
	bl MOD04_021E26E4
	mov r1, r4
	str r1, [r0, #0x198]
	bl MOD04_021E26E4
	str r8, [r0, #0x19c]
	mov r5, #1
_021E7D88:
	cmp r5, #0
	beq _021E7DA4
	bl MOD04_021E26E4
	add r0, r0, #0x194
	bl MOD04_021E7A44
	mov r4, r0
	b _021E7DE0
_021E7DA4:
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD43C
	mov r5, r0
	bl MOD04_021E26E4
	add r3, r0, #0x194
	mov r0, #0
	mov r1, r5
	mov r2, r0
	bl MOD04_021E2784
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x18c]
	str r1, [r0, #0x190]
_021E7DE0:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_021E7DEC: .word 0x0000FFFF
_021E7DF0: .word 0x0000A8C0
	arm_func_end MOD04_021E7B04

	arm_func_start MOD04_021E7DF4
MOD04_021E7DF4: ; 0x021E7DF4
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov lr, #3
	ldr ip, _021E7E48 ; =UNK04_0220D3AC
	str lr, [sp]
	str ip, [sp, #4]
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r2, _021E7E4C ; =UNK04_0220D3CC
	ldr r1, _021E7E50 ; =UNK04_0220D3D8
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	str r1, [sp, #0x1c]
	ldr r2, _021E7E54 ; =UNK04_0220D418
	ldr r3, _021E7E58 ; =UNK04_0220D3E4
	mov r1, #0x100
	str ip, [sp, #0x20]
	bl OS_SNPrintf
	add sp, sp, #0x24
	ldmfd sp!, {pc}
	.align 2, 0
_021E7E48: .word UNK04_0220D3AC
_021E7E4C: .word UNK04_0220D3CC
_021E7E50: .word UNK04_0220D3D8
_021E7E54: .word UNK04_0220D418
_021E7E58: .word UNK04_0220D3E4
	arm_func_end MOD04_021E7DF4

	arm_func_start MOD04_021E7E5C
MOD04_021E7E5C: ; 0x021E7E5C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #0x1b0
	mov r7, #8
	mov r6, #0xa
	mov r5, #0x32
	mov r4, #0x33
	mov r3, #0x34
	mov r2, #0x35
	mov r1, #0x36
	strb r7, [sp, #0x10c]
	strb r6, [sp, #0x10d]
	strb r5, [sp, #0x10e]
	strb r4, [sp, #0x10f]
	strb r3, [sp, #0x110]
	strb r2, [sp, #0x111]
	strb r1, [sp, #0x112]
	mov r5, r0
	mov r4, #7
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E7EC4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E7EF4
_021E7EC4:
	add r1, sp, #0x100
	ldr r2, _021E8020 ; =UNK04_02210704
	add r1, r1, #0x13
	mov r3, #0
_021E7ED4:
	ldrb r0, [r2]
	add r3, r3, #1
	add r2, r2, #0xc
	cmp r0, #0
	strneb r0, [r1], #1
	addne r4, r4, #1
	cmp r3, #0x9a
	blt _021E7ED4
_021E7EF4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #5
	addls pc, pc, r0, lsl #2
	b _021E7FAC
_021E7F08: ; jump table
	b _021E7FAC ; case 0
	b _021E7FAC ; case 1
	b _021E7F8C ; case 2
	b _021E7F20 ; case 3
	b _021E7F8C ; case 4
	b _021E7F8C ; case 5
_021E7F20:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r0, #0
	bne _021E7F84
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldr r1, [r6, #0x200]
	ldrb r2, [r5, #0x16]
	ldrb r3, [r0, #0x15]
	add r0, sp, #0xc
	bl MOD04_021E7DF4
	ldr r0, _021E8024 ; =UNK04_022106E0
	ldr r5, [r0]
	cmp r5, #0
	beq _021E7FAC
	add r0, sp, #0xc
	ldr r2, _021E8028 ; =UNK04_0220D470
	mov r3, r0
	mov r1, #0x100
	str r5, [sp]
	bl OS_SNPrintf
	b _021E7FAC
_021E7F84:
	bl MOD04_021E26E4
	ldr r5, [r0, #0x208]
_021E7F8C:
	ldr r2, _021E802C ; =UNK04_0220D47C
	ldr r3, _021E8030 ; =UNK04_0220D3AC
	add r0, sp, #0xc
	mov r1, #0x100
	str r5, [sp]
	bl OS_SNPrintf
	bl MOD04_021E26E4
	str r5, [r0, #0x204]
_021E7FAC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203C04
	mov sl, #0
	add sb, sp, #0xc
	add r5, sp, #0x10c
	mov r6, sl
	mov r8, #6
	mov r7, #1
_021E7FD0:
	bl MOD04_021E26E4
	str r4, [sp]
	str sb, [sp, #4]
	str r8, [sp, #8]
	ldr r0, [r0, #0xe4]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl MOD04_02203D1C
	cmp r0, #0
	addeq sp, sp, #0x1b0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	cmp r0, #2
	addne sp, sp, #0x1b0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	add sl, sl, #1
	cmp sl, #5
	blt _021E7FD0
	add sp, sp, #0x1b0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, pc}
	.align 2, 0
_021E8020: .word UNK04_02210704
_021E8024: .word UNK04_022106E0
_021E8028: .word UNK04_0220D470
_021E802C: .word UNK04_0220D47C
_021E8030: .word UNK04_0220D3AC
	arm_func_end MOD04_021E7E5C

	arm_func_start MOD04_021E8034
MOD04_021E8034: ; 0x021E8034
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	cmp r0, #0
	beq _021E8074
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203E80
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0xe4]
_021E8074:
	bl MOD04_02200D6C
	mov r0, #0
	bl MOD04_021E26D0
	ldr r0, _021E80C0 ; =UNK04_022106E0
	ldr r1, [r0]
	cmp r1, #0
	beq _021E80A8
	mov r0, #4
	mov r2, #0
	bl MOD04_021DD904
	ldr r0, _021E80C0 ; =UNK04_022106E0
	mov r1, #0
	str r1, [r0]
_021E80A8:
	bl MOD04_021E4164
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x18]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E80C0: .word UNK04_022106E0
	arm_func_end MOD04_021E8034

	arm_func_start MOD04_021E80C4
MOD04_021E80C4: ; 0x021E80C4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r7, r0
	mov r0, #0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl MOD04_021E8174
	bl MOD04_021E26E4
	strb r7, [r0, #0x15]
	bl MOD04_021E26E4
	strb r6, [r0, #0x16]
	bl MOD04_021E26E4
	str r5, [r0, #0x464]
	bl MOD04_021E26E4
	str r4, [r0, #0x468]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17d]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x2d0]
	mov r0, #0x32
	ldr r1, _021E8160 ; =UNK04_0220D3AC
	bl MOD04_0220277C
	mov r0, #0x33
	ldr r1, _021E8164 ; =UNK04_0220D3CC
	bl MOD04_0220277C
	mov r0, #0x34
	ldr r1, _021E8168 ; =UNK04_0220D3D8
	bl MOD04_0220277C
	mov r0, #0x35
	ldr r1, _021E816C ; =UNK04_0220D3E4
	bl MOD04_0220277C
	mov r0, #0x36
	ldr r1, _021E8170 ; =UNK04_0220D3A0
	bl MOD04_0220277C
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E8160: .word UNK04_0220D3AC
_021E8164: .word UNK04_0220D3CC
_021E8168: .word UNK04_0220D3D8
_021E816C: .word UNK04_0220D3E4
_021E8170: .word UNK04_0220D3A0
	arm_func_end MOD04_021E80C4

	arm_func_start MOD04_021E8174
MOD04_021E8174: ; 0x021E8174
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r0
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xc]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17c]
	bl MOD04_021E26E4
	mov r5, r0
	mov r0, #0x10000
	bl MOD04_021DE8C8
	add r1, r5, #0x100
	strh r0, [r1, #0x7e]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x180]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x184]
	str r1, [r0, #0x188]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x18c]
	str r1, [r0, #0x190]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a4]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a9]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1aa]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ab]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ac]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a7]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a8]
	bl MOD04_021E26E4
	mov r1, #0
	add r0, r0, #0x100
	strh r1, [r0, #0xb2]
	bl MOD04_021E26E4
	mov r1, #0
	add r0, r0, #0x100
	strh r1, [r0, #0xb4]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1b8]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1e0]
	str r1, [r0, #0x1e4]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1f0]
	str r1, [r0, #0x1f4]
	bl MOD04_021E26E4
	add r1, r0, #0x3cc
	mov r0, #0
	mov r2, #0x98
	bl MIi_CpuClear32
	cmp r4, #2
	bne _021E82F0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	strb r0, [r4, #0x14]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E82CC
	mov r0, #1
	bl MOD04_021E26D0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_021E82CC:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #0xa
	bl MOD04_021E26D0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_021E82F0:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xd]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xe]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x14]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0xe8]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a5]
	bl MOD04_021E26E4
	mov r1, #0
	add r0, r0, #0x100
	strh r1, [r0, #0xb0]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1bc]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c0]
	str r1, [r0, #0x1c4]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1cc]
	str r1, [r0, #0x1d0]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1d4]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x204]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x208]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x2f0]
	bl MOD04_021E26E4
	add r1, r0, #0x24
	mov r0, #0
	mov r2, #0x80
	bl MIi_CpuClear32
	bl MOD04_021E26E4
	add r1, r0, #0xa4
	mov r0, #0
	mov r2, #0x40
	bl MIi_CpuClear16
	bl MOD04_021E26E4
	add r1, r0, #0xf4
	mov r0, #0
	mov r2, #0x80
	bl MIi_CpuClear32
	bl MOD04_021E26E4
	add r1, r0, #0x194
	mov r0, #0
	mov r2, #0xc
	bl MIi_CpuClear32
	bl MOD04_021E26E4
	add r1, r0, #0x210
	mov r0, #0
	mov r2, #0x80
	bl MIi_CpuClear32
	bl MOD04_021E26E4
	add r1, r0, #0x290
	mov r0, #0
	mov r2, #0x40
	bl MIi_CpuClear16
	bl MOD04_021E26E4
	add r0, r0, #0x2d0
	mov r1, #0
	mov r2, #0x20
	bl MI_CpuFill8
	bl MOD04_021E26E4
	add r1, r0, #0x348
	mov r0, #0
	mov r2, #0x84
	bl MIi_CpuClear32
	cmp r4, #1
	bne _021E84A8
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E8484
	mov r0, #3
	bl MOD04_021E26D0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_021E8484:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
	mov r0, #4
	bl MOD04_021E26D0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
_021E84A8:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x15]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x16]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x18]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20c]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1a6]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ae]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ad]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1f8]
	str r1, [r0, #0x1fc]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x46c]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x470]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	arm_func_end MOD04_021E8174

	arm_func_start MOD04_021E852C
MOD04_021E852C: ; 0x021E852C
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E852C

	arm_func_start MOD04_021E854C
MOD04_021E854C: ; 0x021E854C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r0, #0
	bl MOD04_021E26F4
	ldr r0, _021E85C8 ; =UNK04_022106E0
	ldr r1, [r0]
	cmp r1, #0
	beq _021E8584
	mov r0, #4
	mov r2, #0
	bl MOD04_021DD904
	ldr r0, _021E85C8 ; =UNK04_022106E0
	mov r1, #0
	str r1, [r0]
_021E8584:
	bl MOD04_021E4164
	ldr r0, _021E85CC ; =UNK04_022106D4
	ldr r1, [r0]
	cmp r1, #0
	beq _021E85B0
	mov r0, #4
	mov r2, #0
	bl MOD04_021DD904
	ldr r0, _021E85CC ; =UNK04_022106D4
	mov r1, #0
	str r1, [r0]
_021E85B0:
	ldr r0, _021E85D0 ; =UNK04_022106DC
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #1]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E85C8: .word UNK04_022106E0
_021E85CC: .word UNK04_022106D4
_021E85D0: .word UNK04_022106DC
	arm_func_end MOD04_021E854C

	arm_func_start MOD04_021E85D4
MOD04_021E85D4: ; 0x021E85D4
	stmdb sp!, {lr}
	sub sp, sp, #0x2c
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	addne sp, sp, #0x2c
	movne r0, #0
	ldmneia sp!, {pc}
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x16]
	ldr r2, _021E8694 ; =UNK04_0220D394
	add r0, sp, #0
	add r3, r1, #1
	mov r1, #0xc
	bl OS_SNPrintf
	ldr r0, _021E8698 ; =UNK04_0220D484
	add r1, sp, #0
	add r2, sp, #0xc
	mov r3, #0x2f
	bl MOD04_021DEB54
	bl MOD04_021E26E4
	ldrb r2, [r0, #0xd]
	add r0, sp, #0
	mov r1, #0xc
	add r3, r2, #1
	ldr r2, _021E8694 ; =UNK04_0220D394
	bl OS_SNPrintf
	ldr r0, _021E869C ; =UNK04_0220D488
	add r1, sp, #0
	add r2, sp, #0xc
	mov r3, #0x2f
	bl MOD04_021DEB0C
	ldr r2, _021E8694 ; =UNK04_0220D394
	add r0, sp, #0
	mov r1, #0xc
	mov r3, #3
	bl OS_SNPrintf
	ldr r0, _021E86A0 ; =UNK04_0220D3F4
	add r1, sp, #0
	add r2, sp, #0xc
	mov r3, #0x2f
	bl MOD04_021DEB0C
	mov r0, #6
	add r1, sp, #0xc
	mov r2, #0
	bl MOD04_021E1E30
	add sp, sp, #0x2c
	ldmfd sp!, {pc}
	.align 2, 0
_021E8694: .word UNK04_0220D394
_021E8698: .word UNK04_0220D484
_021E869C: .word UNK04_0220D488
_021E86A0: .word UNK04_0220D3F4
	arm_func_end MOD04_021E85D4

	arm_func_start MOD04_021E86A4
MOD04_021E86A4: ; 0x021E86A4
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r7, r0
	bl MOD04_021E26E4
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	ldr r0, _021E8748 ; =UNK04_022106E4
	mov r1, #0
	mov r2, #0x20
	bl MI_CpuFill8
	mov r6, #0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xe]
	cmp r0, #0
	blt _021E8730
	ldr r5, _021E8748 ; =UNK04_022106E4
	mov r4, #1
_021E86E8:
	bl MOD04_021E26E4
	mov r8, r0
	bl MOD04_021E26E4
	add r0, r0, r6
	ldrb r0, [r0, #0x2d0]
	ldr r1, [r8, #0x2f0]
	mov r0, r4,lsl  r0
	ands r0, r1, r0
	beq _021E8730
	bl MOD04_021E26E4
	add r0, r0, r6
	ldrb r0, [r0, #0x2d0]
	add r6, r6, #1
	strb r0, [r5], #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xe]
	cmp r6, r0
	ble _021E86E8
_021E8730:
	ldr r0, _021E8748 ; =UNK04_022106E4
	str r0, [r7]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xe]
	add r0, r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021E8748: .word UNK04_022106E4
	arm_func_end MOD04_021E86A4

	arm_func_start MOD04_021E874C
MOD04_021E874C: ; 0x021E874C
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD04_021E26E4
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	bl MOD04_021E26E4
	add r0, r0, #0x2d0
	str r0, [r4]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r0, #1
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E874C

	arm_func_start MOD04_021E8780
MOD04_021E8780: ; 0x021E8780
	stmdb sp!, {r4, r5, r6, lr}
	mvn r6, #0
	mov r5, #0
	mov r4, #1
_021E8790:
	bl MOD04_021E26E4
	mov r1, r4,lsl  r5
	ldr r0, [r0, #0x2f0]
	add r5, r5, #1
	ands r0, r1, r0
	addne r6, r6, #1
	cmp r5, #0x20
	blt _021E8790
	mvn r0, #0
	cmp r6, r0
	bne _021E87CC
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xe]
	ldmia sp!, {r4, r5, r6, pc}
_021E87CC:
	bl MOD04_021E26E4
	strb r6, [r0, #0xe]
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E8780

	arm_func_start MOD04_021E87D8
MOD04_021E87D8: ; 0x021E87D8
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xe]
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E87D8

	arm_func_start MOD04_021E8804
MOD04_021E8804: ; 0x021E8804
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E8804

	arm_func_start MOD04_021E8830
MOD04_021E8830: ; 0x021E8830
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov sb, r0
	mov r8, r1
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	bl MOD04_021E26E4
	add r0, r0, sb, lsl #2
	ldr fp, [r0, #0xf4]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	add r0, r0, sb
	ldrb r0, [r0, #0x2d0]
	mov r1, #1
	ldr r2, [r4, #0x2f0]
	mvn r0, r1, lsl r0
	and r0, r2, r0
	str r0, [r4, #0x2f0]
	bl MOD04_021E8780
	sub r0, r8, #1
	cmp sb, r0
	bge _021E8970
	sub r0, r8, sb
	sub r6, r0, #1
	cmp r6, #0
	mov r7, #0
	ble _021E8970
_021E88AC:
	add r4, sb, r7
	add r5, r4, #1
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	add r0, r0, r5, lsl #2
	ldr r1, [r0, #0x24]
	add r0, sl, r4, lsl #2
	str r1, [r0, #0x24]
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	add r0, r0, r5, lsl #1
	ldrh r1, [r0, #0xa4]
	add r0, sl, r4, lsl #1
	strh r1, [r0, #0xa4]
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	add r1, sl, r4, lsl #2
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0xf4]
	str r0, [r1, #0xf4]
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	add r1, sl, r4, lsl #2
	add r0, r0, r5, lsl #2
	ldr r0, [r0, #0x210]
	str r0, [r1, #0x210]
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	add r1, sl, r4, lsl #1
	add r1, r1, #0x200
	add r0, r0, r5, lsl #1
	add r0, r0, #0x200
	ldrh r0, [r0, #0x90]
	strh r0, [r1, #0x90]
	bl MOD04_021E26E4
	mov sl, r0
	bl MOD04_021E26E4
	add r1, r0, r5
	add r0, sl, r4
	ldrb r1, [r1, #0x2d0]
	add r7, r7, #1
	cmp r7, r6
	strb r1, [r0, #0x2d0]
	blt _021E88AC
_021E8970:
	cmp r8, #0
	ble _021E89E0
	sub r4, r8, #1
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	mov r1, #0
	str r1, [r0, #0x24]
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #1
	mov r1, #0
	strh r1, [r0, #0xa4]
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	mov r1, #0
	str r1, [r0, #0xf4]
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	mov r1, #0
	str r1, [r0, #0x210]
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #1
	add r0, r0, #0x200
	mov r1, #0
	strh r1, [r0, #0x90]
	bl MOD04_021E26E4
	add r0, r0, r4
	mov r1, #0
	strb r1, [r0, #0x2d0]
_021E89E0:
	mov r0, fp
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	arm_func_end MOD04_021E8830

	arm_func_start MOD04_021E89EC
MOD04_021E89EC: ; 0x021E89EC
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	bl MOD04_021E26E4
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, pc}
	cmp r5, #0
	mov r4, #0
	ble _021E8A48
_021E8A14:
	bl MOD04_021E26E4
	add r0, r0, r4, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r6, r0
	bne _021E8A3C
	mov r0, r4
	mov r1, r5
	bl MOD04_021E8830
	mov r0, #1
	ldmia sp!, {r4, r5, r6, pc}
_021E8A3C:
	add r4, r4, #1
	cmp r4, r5
	blt _021E8A14
_021E8A48:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E89EC

	arm_func_start MOD04_021E8A50
MOD04_021E8A50: ; 0x021E8A50
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a8]
	cmp r0, #2
	ldmeqia sp!, {r4, pc}
	mov r0, r4
	bl MOD04_021E59D4
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E8A50

	arm_func_start MOD04_021E8A74
MOD04_021E8A74: ; 0x021E8A74
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	mov r4, r1
	bl MOD04_021DF88C
	cmp r0, #5
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	addeq sp, sp, #4
	moveq r0, #1
	ldmeqia sp!, {r4, r5, pc}
	cmp r5, #0
	beq _021E8AD4
	ldr r1, _021E8C00 ; =0xFFFEC780
	mov r0, r5
	add r1, r4, r1
	bl MOD04_021E8E08
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, pc}
_021E8AD4:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x2d0]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a9]
	cmp r0, #1
	beq _021E8B10
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a8]
	cmp r0, #1
	beq _021E8B10
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a8]
	cmp r0, #2
	bne _021E8B1C
_021E8B10:
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, pc}
_021E8B1C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	cmp r0, #0
	beq _021E8B44
	bl MOD04_021E26E4
	ldr r0, [r0, #0x19c]
	bl MOD04_022006B4
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x19c]
_021E8B44:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	beq _021E8B84
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a8]
	cmp r0, #0
	bne _021E8BF4
	bl MOD04_021E26E4
	mov r1, #3
	strb r1, [r0, #0x1a8]
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD45C
	b _021E8BF4
_021E8B84:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E8BA4
	ldr r1, _021E8C04 ; =0xFFFEC5D2
	mov r0, #6
	bl MOD04_021E8E08
	b _021E8BF4
_021E8BA4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x208]
	cmp r0, #0
	beq _021E8BBC
	bl MOD04_021E4BF4
	b _021E8BF4
_021E8BBC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E8BEC
	mov r0, #0x12
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	str r0, [r4, #0x1f0]
	str r1, [r4, #0x1f4]
	b _021E8BF4
_021E8BEC:
	mov r0, #1
	bl MOD04_021E4CF8
_021E8BF4:
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E8C00: .word 0xFFFEC780
_021E8C04: .word 0xFFFEC5D2
	arm_func_end MOD04_021E8A74

	arm_func_start MOD04_021E8C08
MOD04_021E8C08: ; 0x021E8C08
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	mov r4, r2
	cmp r1, #2
	beq _021E8C30
	cmp r1, #3
	beq _021E8CDC
	cmp r1, #4
	beq _021E8DA4
	ldmia sp!, {r4, r5, r6, pc}
_021E8C30:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #1
	bne _021E8CCC
	ldrb r0, [r4]
	cmp r0, #1
	bne _021E8C58
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x20c]
_021E8C58:
	ldrb r6, [r4, #1]
	bl MOD04_021E26E4
	ldrb r1, [r4, #2]
	add r0, r0, r6
	strb r1, [r0, #0x2d0]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r1, [r0, #0x200]
	add r0, r4, r6, lsl #2
	str r1, [r0, #0xf4]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E8CA4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #1
	bne _021E8CB8
_021E8CA4:
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	strb r0, [r4, #0x16]
_021E8CB8:
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ad]
	mov r0, #9
	bl MOD04_021E26D0
_021E8CCC:
	mov r0, r5
	mov r1, #3
	bl MOD04_021E4910
	ldmia sp!, {r4, r5, r6, pc}
_021E8CDC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x10
	bne _021E8D94
	bl MOD04_021E26E4
	ldr r2, [r0, #0x1d4]
	mov r1, #1
	orr r1, r2, r1, lsl r5
	str r1, [r0, #0x1d4]
	ldrb r1, [r4]
	ldrb r0, [r4, #1]
	orr r4, r1, r0, lsl #8
	bl MOD04_021E26E4
	add r0, r0, #0x100
	ldrh r0, [r0, #0xb0]
	cmp r4, r0
	ble _021E8D2C
	bl MOD04_021E26E4
	add r0, r0, #0x100
	strh r4, [r0, #0xb0]
_021E8D2C:
	mov r0, #0
	bl MOD04_021E3EC4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1d4]
	cmp r4, r0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	blt _021E8D88
	mov r4, #4
_021E8D60:
	bl MOD04_021E26E4
	add r0, r0, r5
	ldrb r0, [r0, #0x2d0]
	mov r1, r4
	bl MOD04_021E4910
	add r5, r5, #1
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r5, r0
	ble _021E8D60
_021E8D88:
	mov r0, #0x11
	bl MOD04_021E26D0
	ldmia sp!, {r4, r5, r6, pc}
_021E8D94:
	mov r0, r5
	mov r1, #4
	bl MOD04_021E4910
	ldmia sp!, {r4, r5, r6, pc}
_021E8DA4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #9
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, #4
	bl MOD04_021E51C0
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end MOD04_021E8C08

	arm_func_start MOD04_021E8DC0
MOD04_021E8DC0: ; 0x021E8DC0
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x14]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x16]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E8DC0

	arm_func_start MOD04_021E8E08
MOD04_021E8E08: ; 0x021E8E08
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r4, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
	bl MOD04_021E4B40
	mov r0, r4
	mov r1, r5
	bl MOD04_021DD6B0
	ldr r1, _021E8EC8 ; =UNK04_0220D3F0
	mov r0, #1
	mov r2, #0
	bl MOD04_021E1E30
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	moveq r7, #1
	movne r7, #0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	cmp r0, #0
	moveq r8, #1
	movne r8, #0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x20c]
	bl MOD04_021E1F18
	mov r5, r0
	bl MOD04_021E26E4
	str r5, [sp]
	ldr r1, [r0, #0x468]
	mov r0, r4
	str r1, [sp, #4]
	ldr r4, [r6, #0x464]
	mov r2, r8
	mov r3, r7
	mov r1, #0
	blx r4
	bl MOD04_021E8034
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021E8EC8: .word UNK04_0220D3F0
	arm_func_end MOD04_021E8E08

	arm_func_start MOD04_021E8ECC
MOD04_021E8ECC: ; 0x021E8ECC
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021E26E4
	mov r1, #0xff
	strb r1, [r0, #0x3cc]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x3cd]
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021E8ECC

	arm_func_start MOD04_021E8EF4
MOD04_021E8EF4: ; 0x021E8EF4
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x21c
	mov fp, r2
	mov sl, #0
	str r1, [sp, #8]
	add sb, sp, #0xc
	add r5, sp, #0x1c
	mov r7, sl
	add r8, fp, #1
	mov r6, #0xa
	mvn r4, #0
_021E8F20:
	mov r0, sb
	mov r1, r8
	mov r2, sl
	bl MOD04_021E761C
	cmp r0, r4
	beq _021E8F58
	mov r0, sb
	mov r1, r7
	mov r2, r6
	bl strtoul
	str r0, [r5, sl, lsl #2]
	add sl, sl, #1
	cmp sl, #0x80
	blt _021E8F20
_021E8F58:
	add r0, sp, #0x1c
	str r0, [sp]
	str sl, [sp, #4]
	ldrb r0, [fp]
	mov r2, #0
	ldr r1, [sp, #8]
	mov r3, r2
	bl MOD04_021E6730
	add sp, sp, #0x21c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	arm_func_end MOD04_021E8EF4

	arm_func_start MOD04_021E8F80
MOD04_021E8F80: ; 0x021E8F80
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x1c
	mov r6, r0
	mov r4, r1
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #7
	beq _021E8FC4
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xc
	addne sp, sp, #0x1c
	ldmneia sp!, {r4, r5, r6, r7, pc}
_021E8FC4:
	cmp r4, #0
	beq _021E9140
	cmp r4, #5
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	cmp r4, #6
	bne _021E9114
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xc]
	add r1, r1, #1
	strb r1, [r0, #0xc]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xc]
	cmp r0, #5
	bls _021E9030
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xc]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9030:
	bl MOD04_021E26E4
	ldr r3, [r0, #0x200]
	ldr r2, _021E91F8 ; =UNK04_0220D394
	add r0, sp, #0x10
	mov r1, #0xc
	bl OS_SNPrintf
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r2, [r6, #0x14]
	ldrb r1, [r0, #0x14]
	add r0, r7, r2, lsl #2
	add r1, r5, r1, lsl #1
	add r1, r1, #0x200
	ldrh r1, [r1, #0x90]
	ldr r0, [r0, #0x210]
	mov r2, #0
	bl MOD04_021FFEB0
	mov r5, r0
	bl MOD04_021E26E4
	mvn r1, #0
	str r1, [sp]
	ldr r3, _021E91FC ; =0x00001388
	mov r1, #0
	str r3, [sp, #4]
	ldr r0, [r0, #8]
	mov r2, r5
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4, #4]
	add r3, sp, #0x10
	ldr r0, [r0]
	bl MOD04_021FD52C
	cmp r0, #1
	bne _021E90E0
	bl MOD04_021E36B0
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E90E0:
	cmp r0, #0
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x14]
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	add sp, sp, #0x1c
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9114:
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r0, #1
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	add sp, sp, #0x1c
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9140:
	bl MOD04_021DF704
	mov r5, r0
	mvn r1, #0
	cmp r5, r1
	bne _021E9168
	ldr r1, _021E9200 ; =0xFFFEABC4
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9168:
	bl MOD04_021DF6BC
	mov r4, r0
	mov r0, r5
	bl MOD04_021DF638
	str r6, [r4]
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r2, [r0, #0xd]
	mov r1, #0
	add r2, r2, #1
	strb r2, [r0, #0xd]
	strb r5, [r4]
	strh r1, [r4, #2]
	str r1, [r4, #4]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r2, [r0, #0xd]
	mov r0, r6
	mov r1, r4
	add r2, r5, r2
	ldrb r2, [r2, #0x2d0]
	strb r2, [r4, #1]
	bl MOD04_021FD3F8
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xc
	bne _021E91E8
	mov r0, #0
	bl MOD04_021E51C0
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E91E8:
	mov r0, #1
	bl MOD04_021E51C0
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E91F8: .word UNK04_0220D394
_021E91FC: .word 0x00001388
_021E9200: .word 0xFFFEABC4
	arm_func_end MOD04_021E8F80

	arm_func_start MOD04_021E9204
MOD04_021E9204: ; 0x021E9204
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl MOD04_021E26E4
	cmp r0, #0
	beq _021E9244
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #7
	bne _021E9244
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a9]
	cmp r0, #0
	beq _021E925C
_021E9244:
	ldr r1, _021E944C ; =UNK04_0220D48C
	mov r0, r8
	mvn r2, #0
	bl MOD04_021FD6B0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021E925C:
	bl MOD04_021DF704
	mov r5, r0
	mvn r2, #0
	cmp r5, r2
	bne _021E9290
	ldr r1, _021E9450 ; =UNK04_0220D498
	mov r0, r8
	bl MOD04_021FD6B0
	ldr r1, _021E9454 ; =0xFFFEABC4
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021E9290:
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0x210]
	cmp r7, r0
	bne _021E92D4
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #1
	add r0, r0, #0x200
	ldrh r0, [r0, #0x90]
	cmp r6, r0
	beq _021E9364
_021E92D4:
	ldr r0, [sp, #0x24]
	ldrb r1, [r0]
	cmp r1, #0
	beq _021E934C
	mov r1, #0
	mov r2, #0xa
	bl strtoul
	mov r4, r0
	bl MOD04_021E26E4
	mov sb, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, sb, r0, lsl #2
	ldr r0, [r0, #0xf4]
	cmp r4, r0
	bne _021E934C
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #2
	str r7, [r0, #0x210]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #1
	add r0, r0, #0x200
	strh r6, [r0, #0x90]
	b _021E9364
_021E934C:
	ldr r1, _021E9458 ; =UNK04_0220D4A4
	mov r0, r8
	mvn r2, #0
	bl MOD04_021FD6B0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021E9364:
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x18c]
	str r1, [r0, #0x190]
	bl MOD04_021E26E4
	ldr r1, [r0, #8]
	mov r0, r8
	bl MOD04_021FD6BC
	cmp r0, #0
	bne _021E93A0
	ldr r1, _021E945C ; =0xFFFEC5E6
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021E93A0:
	bl MOD04_021E8ECC
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	cmp r0, #0
	bne _021E93D4
	ldr r1, [sp, #0x20]
	ldr r0, _021E9460 ; =0x0000FFFF
	mov r4, r1, asr #1
	cmp r4, r0
	movge r4, r0
	bl MOD04_021E26E4
	add r0, r0, #0x100
	strh r4, [r0, #0xb0]
_021E93D4:
	mov r0, r5
	bl MOD04_021DF6BC
	mov r4, r0
	mov r0, r5
	bl MOD04_021DF638
	str r8, [r4]
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	add r1, r1, #1
	strb r1, [r0, #0xd]
	strb r5, [r4]
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	mov r0, r8
	mov r2, #0
	sub r1, r1, #1
	add r1, r5, r1
	ldrb r3, [r1, #0x2d0]
	mov r1, r4
	strb r3, [r4, #1]
	strh r2, [r4, #2]
	str r2, [r4, #4]
	bl MOD04_021FD3F8
	mov r0, #2
	bl MOD04_021E51C0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_021E944C: .word UNK04_0220D48C
_021E9450: .word UNK04_0220D498
_021E9454: .word 0xFFFEABC4
_021E9458: .word UNK04_0220D4A4
_021E945C: .word 0xFFFEC5E6
_021E9460: .word 0x0000FFFF
	arm_func_end MOD04_021E9204

	arm_func_start MOD04_021E9464
MOD04_021E9464: ; 0x021E9464
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	ldr r0, [sp, #0x18]
	mov r5, r1
	mov r6, r2
	mov r4, r3
	cmp r0, #0
	beq _021E948C
	cmp r4, #0
	bne _021E9498
_021E948C:
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E9498:
	add r1, sp, #0
	mov r0, #0
	mov r2, #8
	bl MIi_CpuClear32
	mov r1, r6, asr #8
	mov r0, r6, lsl #8
	mov r2, #2
	and r1, r1, #0xff
	and r0, r0, #0xff00
	orr r0, r1, r0
	strb r2, [sp, #1]
	strh r0, [sp, #2]
	str r5, [sp, #4]
	ldrb r5, [r4]
	cmp r5, #0xfe
	bne _021E94E4
	ldrb r0, [r4, #1]
	cmp r0, #0xfd
	beq _021E94EC
_021E94E4:
	cmp r5, #0x5c
	bne _021E9518
_021E94EC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _021E9558
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	ldr r2, [sp, #0x18]
	add r3, sp, #0
	mov r1, r4
	bl MOD04_022011A8
	b _021E9558
_021E9518:
	ldr r1, _021E9564 ; =UNK04_0220F018
	mov r0, r4
	mov r2, #6
	bl memcmp
	cmp r0, #0
	bne _021E9544
	ldr r1, [sp, #0x18]
	add r2, sp, #0
	mov r0, r4
	bl MOD04_021FFF78
	b _021E9558
_021E9544:
	cmp r5, #0xfe
	moveq r0, #0
	add sp, sp, #8
	movne r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E9558:
	mov r0, #1
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E9564: .word UNK04_0220F018
	arm_func_end MOD04_021E9464

	arm_func_start MOD04_021E9568
MOD04_021E9568: ; 0x021E9568
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r4, r0
	bl MOD04_021E26E4
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021DD6D4
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	cmp r4, #0
	bne _021E95E4
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	cmp r0, #0
	beq _021E95B8
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202534
_021E95B8:
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD6D4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E95E4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xd
	addls pc, pc, r0, lsl #2
	b _021E9D04
_021E960C: ; jump table
	b _021E9D04 ; case 0
	b _021E9C0C ; case 1
	b _021E97B8 ; case 2
	b _021E97B8 ; case 3
	b _021E9644 ; case 4
	b _021E97B8 ; case 5
	b _021E9D04 ; case 6
	b _021E9870 ; case 7
	b _021E9D04 ; case 8
	b _021E9D04 ; case 9
	b _021E9D04 ; case 10
	b _021E99F8 ; case 11
	b _021E9D04 ; case 12
	b _021E9AEC ; case 13
_021E9644:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1c8]
	cmp r0, #0
	beq _021E9730
	bl OS_GetTick
	mov r6, r0
	mov r7, r1
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	ldr r1, [r5, #0x1cc]
	ldr r0, [r5, #0x1d0]
	subs r2, r6, r1
	sbc r0, r7, r0
	mov r1, r0, lsl #6
	orr r1, r1, r2, lsr #26
	mov r0, r2, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	mov r3, #0
	bl _ll_udiv
	cmp r1, #0
	ldr r1, [r4, #0x1c8]
	cmpeq r0, r1
	bls _021E9730
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c8]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #3
	bne _021E971C
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1aa]
	add r1, r1, #1
	strb r1, [r0, #0x1aa]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1aa]
	cmp r0, #5
	bls _021E96F8
	ldr r1, _021E9EFC ; =0xFFFEC5D2
	mov r0, #6
	bl MOD04_021E8E08
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E96F8:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	mov r1, #0
	bl MOD04_021E6038
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E9730
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E971C:
	mov r0, #0
	bl MOD04_021E5C44
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
_021E9730:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1bc]
	cmp r0, #0
	beq _021E9D04
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	ldr r0, _021E9F00 ; =0x00000BB8
	mla r5, r1, r0, r0
	bl OS_GetTick
	mov r4, r0
	mov r6, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1c0]
	ldr r0, [r0, #0x1c4]
	subs r2, r4, r1
	sbc r0, r6, r0
	mov r1, r0, lsl #6
	orr r1, r1, r2, lsr #26
	mov r0, r2, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	mov r3, #0
	bl _ll_udiv
	cmp r1, #0
	cmpeq r0, r5
	blo _021E9D04
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	mov r1, #0
	bl MOD04_021E6038
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E97B8:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe8]
	cmp r0, #0
	ble _021E9D04
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #3
	bne _021E97EC
	bl MOD04_021E26E4
	ldrb r1, [r0, #0xd]
	ldr r0, _021E9F00 ; =0x00000BB8
	mla r5, r1, r0, r0
	b _021E9800
_021E97EC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe8]
	cmp r0, #1
	moveq r5, #0x3e8
	ldrne r5, _021E9F00 ; =0x00000BB8
_021E9800:
	bl OS_GetTick
	mov r4, r0
	mov r6, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0xec]
	ldr r0, [r0, #0xf0]
	subs r3, r4, r1
	sbc r0, r6, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	cmp r1, #0
	cmpeq r0, r5
	bls _021E9D04
	bl MOD04_021E26E4
	ldr r0, [r0, #0x204]
	bl MOD04_021E7E5C
	bl MOD04_021E38E8
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0xe8]
	b _021E9D04
_021E9870:
	bl MOD04_021E26E4
	ldr r2, [r0, #0x18c]
	ldr r1, [r0, #0x190]
	mov r0, #0
	cmp r1, r0
	cmpeq r2, r0
	beq _021E9900
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x18c]
	ldr r0, [r0, #0x190]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F04 ; =0x000061A8
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9D04
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x18c]
	str r1, [r0, #0x190]
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5908
	cmp r0, #0
	bne _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9900:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x3cc]
	cmp r0, #6
	bne _021E9D04
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x45c]
	ldr r0, [r0, #0x460]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F08 ; =0x00001770
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9D04
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x3cd]
	add r1, r1, #1
	strb r1, [r0, #0x3cd]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x3cd]
	cmp r0, #5
	bls _021E9998
	bl MOD04_021E8ECC
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5908
	cmp r0, #0
	bne _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9998:
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	add r1, r4, #0x3d4
	str r1, [sp]
	add r3, r5, #0x300
	ldr r1, [r0, #0x458]
	mov r0, #6
	str r1, [sp, #4]
	ldr r1, [r7, #0x454]
	ldr r2, [r6, #0x3d0]
	ldrh r3, [r3, #0xce]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E99F8:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x3cc]
	cmp r0, #2
	bne _021E9D04
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _021E9A60
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x45c]
	ldr r0, [r0, #0x460]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F08 ; =0x00001770
	cmp r1, #0
	cmpeq r0, r2
	bhi _021E9AB8
_021E9A60:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E9D04
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x45c]
	ldr r0, [r0, #0x460]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F0C ; =0x00004A38
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9D04
_021E9AB8:
	bl MOD04_021E8ECC
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r0, #1
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	cmp r0, #0
	bne _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9AEC:
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x3cc]
	cmp r0, #8
	bne _021E9D04
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x45c]
	ldr r0, [r0, #0x460]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F10 ; =0x00007530
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9D04
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x3cd]
	add r1, r1, #1
	strb r1, [r0, #0x3cd]
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x3cd]
	cmp r0, #0
	beq _021E9BAC
	bl MOD04_021E8ECC
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #2
	bne _021E9BA4
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	add r0, r4, r0, lsl #2
	ldr r0, [r0, #0xf4]
	bl MOD04_021E59D4
	cmp r0, #0
	bne _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9BA4:
	bl MOD04_021E4CB4
	b _021E9D04
_021E9BAC:
	bl MOD04_021E26E4
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	add r1, r4, #0x3d4
	str r1, [sp]
	add r3, r5, #0x300
	ldr r1, [r0, #0x458]
	mov r0, #8
	str r1, [sp, #4]
	ldr r1, [r7, #0x454]
	ldr r2, [r6, #0x3d0]
	ldrh r3, [r3, #0xce]
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	beq _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9C0C:
	bl MOD04_021DF88C
	cmp r0, #5
	bne _021E9D04
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1f8]
	ldr r0, [r0, #0x1fc]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F10 ; =0x00007530
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9D04
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1ad]
	cmp r0, #5
	blo _021E9C8C
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	bl MOD04_021E5908
	cmp r0, #0
	bne _021E9D04
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E9C8C:
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	ldrh r3, [r0, #0xa4]
	ldr r1, [r5, #0xf4]
	ldr r2, [r4, #0x24]
	mov r0, #0x40
	bl MOD04_021E7884
	bl MOD04_021E61EC
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldrb r1, [r0, #0x1ad]
	add r1, r1, #1
	strb r1, [r0, #0x1ad]
	bl MOD04_021E26E4
	mov r4, r0
	bl OS_GetTick
	ldr r2, _021E9F14 ; =0xFF403B3A
	mvn r3, #0
	adds r0, r0, r2
	str r0, [r4, #0x1f8]
	adc r0, r1, r3
	str r0, [r4, #0x1fc]
_021E9D04:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	beq _021E9D24
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #6
	bne _021E9DA0
_021E9D24:
	bl MOD04_021E26E4
	ldr r2, [r0, #0x184]
	ldr r1, [r0, #0x188]
	mov r0, #0
	cmp r1, r0
	cmpeq r2, r0
	beq _021E9DA0
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x184]
	ldr r0, [r0, #0x188]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F18 ; =0x00002710
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9DA0
	bl MOD04_021E26E4
	mov r1, #0
	add r3, r0, #0x194
	mov r2, r1
	mov r0, #1
	bl MOD04_021E2784
_021E9DA0:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	cmp r0, #0
	beq _021E9DBC
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	bl MOD04_02203C38
_021E9DBC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_021E9F1C
	bl MOD04_02200468
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021E9DEC
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD6D4
_021E9DEC:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0x12
	bne _021E9E54
	bl OS_GetTick
	mov r4, r0
	mov r5, r1
	bl MOD04_021E26E4
	ldr r1, [r0, #0x1f0]
	ldr r0, [r0, #0x1f4]
	subs r3, r4, r1
	sbc r0, r5, r0
	mov r1, r0, lsl #6
	ldr r2, _021E9EF8 ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, #0
	bl _ll_udiv
	ldr r2, _021E9F00 ; =0x00000BB8
	cmp r1, #0
	cmpeq r0, r2
	bls _021E9E54
	bl MOD04_021E4BF4
	cmp r0, #0
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
_021E9E54:
	bl MOD04_021E4684
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E41C4
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E39F0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1ae]
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xa
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldrb r0, [r0, #0xd]
	strb r0, [r4, #0x16]
	bl MOD04_021E85D4
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1ae]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x47c]
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x480]
	ldr r1, [r4, #0x47c]
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E9EF8: .word 0x000082EA
_021E9EFC: .word 0xFFFEC5D2
_021E9F00: .word 0x00000BB8
_021E9F04: .word 0x000061A8
_021E9F08: .word 0x00001770
_021E9F0C: .word 0x00004A38
_021E9F10: .word 0x00007530
_021E9F14: .word 0xFF403B3A
_021E9F18: .word 0x00002710
	arm_func_end MOD04_021E9568

	arm_func_start MOD04_021E9F1C
MOD04_021E9F1C: ; 0x021E9F1C
	stmdb sp!, {r4, lr}
	movs r4, r0
	ldmeqia sp!, {r4, pc}
	bl MOD04_02202534
	ldr r0, [r4, #0xb4]
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	beq _021E9F5C
	cmp r0, #1
	beq _021E9F5C
	cmp r0, #2
	beq _021E9FB0
	ldmia sp!, {r4, pc}
_021E9F5C:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	addls pc, pc, r0, lsl #2
	ldmia sp!, {r4, pc}
_021E9F70: ; jump table
	ldmia sp!, {r4, pc} ; case 0
	b _021E9FA0 ; case 1
	b _021E9FA0 ; case 2
	b _021E9FA0 ; case 3
	b _021E9FA0 ; case 4
	ldmia sp!, {r4, pc} ; case 5
	b _021E9FA0 ; case 6
	ldmia sp!, {r4, pc} ; case 7
	ldmia sp!, {r4, pc} ; case 8
	ldmia sp!, {r4, pc} ; case 9
	ldmia sp!, {r4, pc} ; case 10
	b _021E9FA0 ; case 11
_021E9FA0:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	ldmia sp!, {r4, pc}
_021E9FB0:
	bl MOD04_021E26E4
	ldr r0, [r0, #0x1a0]
	cmp r0, #0xb
	ldmneia sp!, {r4, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021E9F1C

	arm_func_start MOD04_021E9FD0
MOD04_021E9FD0: ; 0x021E9FD0
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x18
	mov r5, r2
	mov r6, r0
	mov r4, r3
	mov r2, r1
	mov r3, r5
	mov r0, #3
	mov r1, #0
	bl MOD04_021E80C4
	bl MOD04_021E26E4
	str r4, [r0, #0x46c]
	bl MOD04_021E26E4
	ldr r1, [sp, #0x28]
	str r1, [r0, #0x470]
	bl MOD04_021E26E4
	mov r1, #1
	strb r1, [r0, #0x17]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	str r0, [r4, #0x20]
	bl MOD04_021E26E4
	str r6, [r0, #0xf4]
	mov r0, #4
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	cmp r0, #0
	bne _021EA0A4
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	mov r5, r0
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	mov r2, r0
	mov r0, #0x14
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r3, #0
	str r3, [sp, #8]
	ldr r0, _021EA130 ; =MOD04_021E32E4
	str r0, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [r5, #0x2f4]
	ldr r1, [r4, #0x2f4]
	ldr r2, [r2, #0x2f8]
	bl MOD04_02203EA4
	str r0, [r6, #0xe4]
_021EA0A4:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xe4]
	cmp r0, #0
	bne _021EA0C8
	mov r0, #5
	bl MOD04_021E38E8
	cmp r0, #0
	addne sp, sp, #0x18
	ldmneia sp!, {r4, r5, r6, pc}
_021EA0C8:
	ldr r1, _021EA134 ; =UNK04_0220D3F0
	mov r0, #5
	mov r2, #0
	bl MOD04_021E1E30
	bl MOD04_021E397C
	cmp r0, #0
	addne sp, sp, #0x18
	ldmneia sp!, {r4, r5, r6, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	cmp r0, #0
	bne _021EA110
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	bl MOD04_021EA1E0
	cmp r0, #0
	addne sp, sp, #0x18
	ldmneia sp!, {r4, r5, r6, pc}
_021EA110:
	bl MOD04_021E26E4
	ldr r0, [r0, #0xf4]
	mov r1, #0
	bl MOD04_021E6038
	bl MOD04_021E61EC
	cmp r0, #0
	add sp, sp, #0x18
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021EA130: .word MOD04_021E32E4
_021EA134: .word UNK04_0220D3F0
	arm_func_end MOD04_021E9FD0

	arm_func_start MOD04_021EA138
MOD04_021EA138: ; 0x021EA138
	stmdb sp!, {r4, lr}
	mov lr, r1
	mov ip, r2
	mov r4, r3
	mov r1, r0
	mov r2, lr
	mov r3, ip
	mov r0, #2
	bl MOD04_021E80C4
	bl MOD04_021E26E4
	str r4, [r0, #0x46c]
	bl MOD04_021E26E4
	ldr r1, [sp, #8]
	str r1, [r0, #0x470]
	bl MOD04_021E26E4
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	str r0, [r4, #0xf4]
	bl MOD04_021E26E4
	mov r1, #1
	str r1, [r0, #0x2f0]
	bl MOD04_021E26E4
	mov r2, #0
	strb r2, [r0, #0xe]
	ldr r1, _021EA1DC ; =UNK04_022106DC
	mov r0, #0xa
	strb r2, [r1, #1]
	bl MOD04_021E26D0
	bl MOD04_021E85D4
	bl MOD04_021E397C
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	cmp r0, #0
	ldmneia sp!, {r4, pc}
	bl MOD04_021E26E4
	ldr r0, [r0, #0x200]
	bl MOD04_021EA1E0
	ldmia sp!, {r4, pc}
	.align 2, 0
_021EA1DC: .word UNK04_022106DC
	arm_func_end MOD04_021EA138

	arm_func_start MOD04_021EA1E0
MOD04_021EA1E0: ; 0x021EA1E0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x2c
	mov r4, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	cmp r0, #0
	addne sp, sp, #0x2c
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	bl MOD04_021E26E4
	str r4, [r0, #0x200]
	mov sl, #0
	ldr fp, _021EA344 ; =MOD04_021E2E18
	mov r4, sl
	mov r5, #1
_021EA21C:
	bl MOD04_021E26E4
	mov sb, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD43C
	mov r8, r0
	bl MOD04_021E26E4
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl MOD04_021FD454
	mov r7, r0
	bl MOD04_021E26E4
	mov r6, r0
	bl MOD04_021E26E4
	ldr r3, [r0, #0x2f8]
	mov r1, r8
	str r3, [sp]
	str r5, [sp, #4]
	str r5, [sp, #8]
	ldr r3, _021EA348 ; =MOD04_021E2E14
	str fp, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r3, _021EA34C ; =MOD04_021E2E10
	mov r2, r7
	str r3, [sp, #0x14]
	ldr r3, _021EA350 ; =MOD04_021E2D68
	add r0, sb, #0x10
	str r3, [sp, #0x18]
	ldr r3, _021EA354 ; =MOD04_021E2D60
	str r3, [sp, #0x1c]
	ldr r3, _021EA358 ; =MOD04_021E2D54
	str r3, [sp, #0x20]
	str r4, [sp, #0x24]
	ldr r3, [r6, #0x2f4]
	bl MOD04_022025B0
	movs r6, r0
	beq _021EA2E4
	cmp r6, #3
	bne _021EA2C4
	cmp sl, #4
	bne _021EA2D8
_021EA2C4:
	mov r0, r6
	bl MOD04_021E3800
	add sp, sp, #0x2c
	mov r0, r6
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021EA2D8:
	add sl, sl, #1
	cmp sl, #5
	blt _021EA21C
_021EA2E4:
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c]
	bl MOD04_021E26E4
	mov r1, #0
	strh r1, [r0, #0x1a]
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	ldr r1, _021EA35C ; =MOD04_021E2D2C
	bl MOD04_02202568
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	ldr r1, _021EA360 ; =MOD04_021E2C78
	bl MOD04_02202598
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	ldr r1, _021EA364 ; =MOD04_021E2B64
	bl MOD04_02202580
	bl MOD04_021E26E4
	ldr r0, [r0, #0x10]
	bl MOD04_02202308
	mov r0, r6
	add sp, sp, #0x2c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021EA344: .word MOD04_021E2E18
_021EA348: .word MOD04_021E2E14
_021EA34C: .word MOD04_021E2E10
_021EA350: .word MOD04_021E2D68
_021EA354: .word MOD04_021E2D60
_021EA358: .word MOD04_021E2D54
_021EA35C: .word MOD04_021E2D2C
_021EA360: .word MOD04_021E2C78
_021EA364: .word MOD04_021E2B64
	arm_func_end MOD04_021EA1E0

	arm_func_start MOD04_021EA368
MOD04_021EA368: ; 0x021EA368
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl MOD04_021E26F4
	bl MOD04_021E26E4
	str r6, [r0]
	bl MOD04_021E26E4
	str r5, [r0, #4]
	bl MOD04_021E26E4
	str r4, [r0, #8]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x10]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1c]
	bl MOD04_021E26E4
	mov r1, #0
	strh r1, [r0, #0x1a]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0xe4]
	mov r0, r1
	bl MOD04_021E26D0
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0xf]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x19]
	bl MOD04_021E26E4
	mov r1, #0
	strb r1, [r0, #0x1af]
	bl MOD04_021E26E4
	mov r1, #0
	add r0, r0, #0x100
	strh r1, [r0, #0xb6]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x1dc]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x200]
	bl MOD04_021E26E4
	ldr r1, [sp, #0x10]
	str r1, [r0, #0x2f4]
	bl MOD04_021E26E4
	ldr r1, [sp, #0x14]
	str r1, [r0, #0x2f8]
	bl MOD04_021E26E4
	ldr r1, [sp, #0x18]
	str r1, [r0, #0x2fc]
	bl MOD04_021E26E4
	ldr r1, [sp, #0x1c]
	str r1, [r0, #0x300]
	bl MOD04_021E26E4
	add r0, r0, #0x304
	mov r1, #0
	mov r2, #0x40
	bl MI_CpuFill8
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x344]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x464]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x468]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x474]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x478]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x47c]
	bl MOD04_021E26E4
	mov r1, #0
	str r1, [r0, #0x480]
	bl MOD04_021E4164
	ldr r1, _021EA4D0 ; =UNK04_022106DC
	mov r0, #0
	strb r0, [r1]
	strb r0, [r1, #1]
	strh r0, [r1, #2]
	bl MOD04_021E8174
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021EA4D0: .word UNK04_022106DC
	arm_func_end MOD04_021EA368

	arm_func_start MOD04_021EA4D4
MOD04_021EA4D4: ; 0x021EA4D4
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021DD6D4
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {pc}
	bl MOD04_021E26E4
	cmp r0, #0
	beq _021EA518
	bl MOD04_021DF88C
	cmp r0, #5
	bne _021EA518
	bl MOD04_021E26E4
	ldrb r0, [r0, #0x1a9]
	cmp r0, #0
	beq _021EA524
_021EA518:
	add sp, sp, #4
	mov r0, #0
	ldmfd sp!, {pc}
_021EA524:
	mov r0, #1
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021EA4D4

	arm_func_start MOD04_021EA530
MOD04_021EA530: ; 0x021EA530
	stmdb sp!, {lr}
	sub sp, sp, #4
	bl MOD04_021EA4D4
	cmp r0, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {pc}
	bl MOD04_021E4F94
	mov r0, #1
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end MOD04_021EA530

	.section .rodata

	.global UNK04_0220BAC4
UNK04_0220BAC4: ; 0x0220BAC4
	.word 0x00000003, 0x00000003, 0x00000002, 0x00000002
	.word 0x00000001, 0x00000001

	.section .data

	.global UNK04_0220D394
UNK04_0220D394: ; 0x0220D394
	.asciz "%u"

	.balign 4, 0
	.global UNK04_0220D398
UNK04_0220D398: ; 0x0220D398
	.asciz "SBCM"

	.balign 4, 0
	.global UNK04_0220D3A0
UNK04_0220D3A0: ; 0x0220D3A0
	.asciz "dwc_eval"

	.balign 4, 0
	.global UNK04_0220D3AC
UNK04_0220D3AC: ; 0x0220D3AC
	.asciz "dwc_pid"

	.balign 4, 0
	.global UNK04_0220D3B4
UNK04_0220D3B4: ; 0x0220D3B4
	.asciz "numplayers"

	.balign 4, 0
	.global UNK04_0220D3C0
UNK04_0220D3C0: ; 0x0220D3C0
	.asciz "maxplayers"

	.balign 4, 0
	.global UNK04_0220D3CC
UNK04_0220D3CC: ; 0x0220D3CC
	.asciz "dwc_mtype"

	.balign 4, 0
	.global UNK04_0220D3D8
UNK04_0220D3D8: ; 0x0220D3D8
	.asciz "dwc_mresv"

	.balign 4, 0
	.global UNK04_0220D3E4
UNK04_0220D3E4: ; 0x0220D3E4
	.asciz "dwc_mver"

	.balign 4, 0
	.global UNK04_0220D3F0
UNK04_0220D3F0: ; 0x0220D3F0
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK04_0220D3F4
UNK04_0220D3F4: ; 0x0220D3F4
	.asciz "VER"

	.balign 4, 0
	.global UNK04_0220D3F8
UNK04_0220D3F8: ; 0x0220D3F8
	.asciz "FME"

	.balign 4, 0
	.global UNK04_0220D3FC
UNK04_0220D3FC: ; 0x0220D3FC
	.asciz "MDF"

	.balign 4, 0
	.global UNK04_0220D400
UNK04_0220D400: ; 0x0220D400
	.asciz "%s%dv%s"

	.balign 4, 0
	.global UNK04_0220D408
UNK04_0220D408: ; 0x0220D408
	.asciz "GPCM"

	.balign 4, 0
	.global UNK04_0220D410
UNK04_0220D410: ; 0x0220D410
	.asciz "MAT"

	.balign 4, 0
	.global UNK04_0220D414
UNK04_0220D414: ; 0x0220D414
	.asciz "/%u"

	.balign 4, 0
	.global UNK04_0220D418
UNK04_0220D418: ; 0x0220D418
	.asciz "%s = %d and %s != %u and maxplayers = %d and numplayers < %d and %s = %d and %s != %s"

	.balign 4, 0
	.global UNK04_0220D470
UNK04_0220D470: ; 0x0220D470
	.asciz "%s and (%s)"

	.balign 4, 0
	.global UNK04_0220D47C
UNK04_0220D47C: ; 0x0220D47C
	.asciz "%s = %u"

	.balign 4, 0
	.global UNK04_0220D484
UNK04_0220D484: ; 0x0220D484
	.asciz "SCM"

	.balign 4, 0
	.global UNK04_0220D488
UNK04_0220D488: ; 0x0220D488
	.asciz "SCN"

	.balign 4, 0
	.global UNK04_0220D48C
UNK04_0220D48C: ; 0x0220D48C
	.asciz "Init state"

	.balign 4, 0
	.global UNK04_0220D498
UNK04_0220D498: ; 0x0220D498
	.asciz "Server full"

	.balign 4, 0
	.global UNK04_0220D4A4
UNK04_0220D4A4: ; 0x0220D4A4
	.asciz "Unknown connect attempt"

	.balign 4, 0
	.section .bss

	.global UNK04_022106D4
UNK04_022106D4: ; 0x022106D4
	.space 0x4

	.global UNK04_022106D8
UNK04_022106D8: ; 0x022106D8
	.space 0x4

	.global UNK04_022106DC
UNK04_022106DC: ; 0x022106DC
	.space 0x4

	.global UNK04_022106E0
UNK04_022106E0: ; 0x022106E0
	.space 0x4

	.global UNK04_022106E4
UNK04_022106E4: ; 0x022106E4
	.space 0x20

	.global UNK04_02210704
UNK04_02210704: ; 0x02210704
	.space 0x1

	.global UNK04_02210705
UNK04_02210705: ; 0x02210705
	.space 0x7

	.global UNK04_0221070C
UNK04_0221070C: ; 0x0221070C
	.space 0x730
