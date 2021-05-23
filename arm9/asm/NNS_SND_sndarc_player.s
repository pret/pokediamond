	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	; _end
	arm_func_start FUN_020C36C8
FUN_020C36C8: ; 0x020C36C8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r2
	mov r2, r3
	ldr r6, [sp, #0x20]
	mov r4, r0
	mov r8, r1
	bl FUN_020C0AF4
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r8
	mov r1, r5
	bl FUN_020C09B0
	add r12, sp, #0x4
	mov r2, r0
	mov r0, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C3270
	cmp r0, #0x0
	beq _020C373C
	mov r0, r5
	bl thunk_FUN_020c077c
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C373C:
	ldr r12, [sp, #0x24]
	ldr r2, [r6, #0x0]
	ldr r1, [r12, #0x18]
	ldr r3, [sp, #0x4]
	mov r0, r5
	add r1, r12, r1
	bl FUN_020C0A90
	ldrb r1, [r6, #0x6]
	mov r0, r4
	bl FUN_020C0F30
	ldrb r1, [r6, #0x7]
	mov r0, r4
	bl FUN_020C0ECC
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	mov r0, r4
	bl FUN_020C0E38
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	; _end
	arm_func_start FUN_020C378C
FUN_020C378C: ; 0x020C378C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r8, r2
	mov r2, r3
	ldr r5, [sp, #0x28]
	mov r6, r0
	mov r7, r1
	bl FUN_020C0AF4
	movs r4, r0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r7
	mov r1, r4
	bl FUN_020C09B0
	mov r7, r0
	add r12, sp, #0x8
	mov r0, r8
	mov r2, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C3270
	cmp r0, #0x0
	beq _020C3804
	mov r0, r4
	bl thunk_FUN_020c077c
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C3804:
	ldr r0, [sp, #0x2c]
	add r12, sp, #0x4
	mov r2, r7
	mov r1, #0x1
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl FUN_020C341C
	cmp r0, #0x0
	beq _020C383C
	mov r0, r4
	bl thunk_FUN_020c077c
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C383C:
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [r2, #0x18]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x0
	bl FUN_020C0A90
	ldrb r1, [r5, #0x6]
	mov r0, r6
	bl FUN_020C0F30
	ldrb r1, [r5, #0x7]
	mov r0, r6
	bl FUN_020C0ECC
	ldr r1, [sp, #0x2c]
	mov r0, r6
	bl FUN_020C0E60
	mov r0, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}

	; _end
	arm_func_start FUN_020C3888
FUN_020C3888: ; 0x020C3888
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r6, r1
	mov r7, r0
	mov r0, r6
	mov r5, r2
	bl FUN_020C2334
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldr r0, [r0, #0x0]
	bl FUN_020C20DC
	movs r4, r0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	mov r1, r5
	bl FUN_020C3D9C
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r7
	bl FUN_020C36C8
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	; _end
	arm_func_start FUN_020C3910
FUN_020C3910: ; 0x020C3910
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldr r0, [sp, #0x20]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl FUN_020C2398
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	cmp r4, #0x0
	ldrltb r4, [r0, #0x8]
	cmp r5, #0x0
	ldrlth r5, [r0, #0x4]
	cmp r6, #0x0
	ldrltb r6, [r0, #0x9]
	ldr r12, [sp, #0x20]
	mov r2, r5
	str r0, [sp, #0x0]
	mov r0, r7
	mov r1, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl FUN_020C378C
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,pc}

	; _end
	arm_func_start FUN_020C3980
FUN_020C3980: ; 0x020C3980
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r4, r1
	mov r5, r0
	mov r0, r4
	bl FUN_020C2398
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r5
	bl FUN_020C378C
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	; _end
	arm_func_start FUN_020C39CC
FUN_020C39CC: ; 0x020C39CC
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	bl FUN_020C241C
	mov r5, #0x0
	mov r7, r5
_020C39E0:
	mov r0, r5
	bl FUN_020C2208
	movs r4, r0
	beq _020C3A58
	ldrb r1, [r4, #0x0]
	mov r0, r5
	bl FUN_020C1160
	ldrh r1, [r4, #0x2]
	mov r0, r5
	bl FUN_020C1148
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020C3A58
	cmp r6, #0x0
	beq _020C3A58
	ldrb r0, [r4, #0x0]
	mov r8, r7
	cmp r0, #0x0
	ble _020C3A58
_020C3A2C:
	ldr r2, [r4, #0x4]
	mov r0, r5
	mov r1, r6
	bl FUN_020C10B4
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	ldrb r0, [r4, #0x0]
	add r8, r8, #0x1
	cmp r8, r0
	blt _020C3A2C
_020C3A58:
	add r5, r5, #0x1
	cmp r5, #0x20
	blt _020C39E0
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}

