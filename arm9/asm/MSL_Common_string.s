	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start strlen
strlen: ; 0x020E2EAC
	mvn r2, #0x0
_020E2EB0:
	ldrsb r1, [r0], #0x1
	add r2, r2, #0x1
	cmp r1, #0x0
	bne _020E2EB0
	mov r0, r2
	bx lr
	arm_func_end strlen

	arm_func_start strcpy
strcpy: ; 0x020E2EC8
	stmdb sp!, {r3-r5,lr}
	and r4, r1, #0x3
	and r3, r0, #0x3
	mov r2, r0
	cmp r3, r4
	bne _020E2F64
	cmp r4, #0x0
	beq _020E2F20
	ldrb r3, [r1, #0x0]
	strb r3, [r0, #0x0]
	cmp r3, #0x0
	ldmeqia sp!, {r3-r5,pc}
	rsbs r4, r4, #0x3
	beq _020E2F18
_020E2F00:
	ldrb r3, [r1, #0x1]!
	cmp r3, #0x0
	strb r3, [r2, #0x1]!
	ldmeqia sp!, {r3-r5,pc}
	subs r4, r4, #0x1
	bne _020E2F00
_020E2F18:
	add r2, r2, #0x1
	add r1, r1, #0x1
_020E2F20:
	ldr r5, [r1, #0x0]
	ldr r3, _020E2F88 ; =0xFEFEFEFF
	mvn r4, r5
	add lr, r5, r3
	ldr ip, _020E2F8C ; =0x80808080
	and r4, lr, r4
	tst r4, r12
	bne _020E2F64
	sub r2, r2, #0x4
_020E2F44:
	str r5, [r2, #0x4]!
	ldr r5, [r1, #0x4]!
	add r4, r5, r3
	mvn lr, r5
	and lr, r4, lr
	tst lr, r12
	beq _020E2F44
	add r2, r2, #0x4
_020E2F64:
	ldrb r3, [r1, #0x0]
	strb r3, [r2, #0x0]
	cmp r3, #0x0
	ldmeqia sp!, {r3-r5,pc}
_020E2F74:
	ldrb r3, [r1, #0x1]!
	cmp r3, #0x0
	strb r3, [r2, #0x1]!
	bne _020E2F74
	ldmia sp!, {r3-r5,pc}
	.balign 4
_020E2F88: .word 0xFEFEFEFF
_020E2F8C: .word 0x80808080
	arm_func_end strcpy

	arm_func_start strncpy
strncpy: ; 0x020E2F90
	stmdb sp!, {r3,lr}
	mov lr, r0
	cmp r2, #0x0
	ldmeqia sp!, {r3,pc}
_020E2FA0:
	ldrsb r3, [r1], #0x1
	mov r12, lr
	strb r3, [lr], #0x1
	ldrsb r3, [r12, #0x0]
	cmp r3, #0x0
	bne _020E2FD4
	subs r2, r2, #0x1
	ldmeqia sp!, {r3,pc}
	mov r1, #0x0
_020E2FC4:
	strb r1, [lr], #0x1
	subs r2, r2, #0x1
	bne _020E2FC4
	ldmia sp!, {r3,pc}
_020E2FD4:
	subs r2, r2, #0x1
	bne _020E2FA0
	ldmia sp!, {r3,pc}
	arm_func_end strncpy

	arm_func_start strcat
strcat: ; 0x020E2FE0
	mov r3, r0
_020E2FE4:
	ldrsb r2, [r3], #0x1
	cmp r2, #0x0
	bne _020E2FE4
	sub r3, r3, #0x1
_020E2FF4:
	ldrsb r2, [r1], #0x1
	mov r12, r3
	strb r2, [r3], #0x1
	ldrsb r2, [r12, #0x0]
	cmp r2, #0x0
	bne _020E2FF4
	bx lr
	arm_func_end strcat

	arm_func_start strncat
strncat: ; 0x020E3010
	stmdb sp!, {r3,lr}
	mov r12, r0
_020E3018:
	ldrsb r3, [r12], #0x1
	cmp r3, #0x0
	bne _020E3018
	cmp r2, #0x0
	sub r12, r12, #0x1
	beq _020E3054
_020E3030:
	ldrsb r3, [r1], #0x1
	mov lr, r12
	strb r3, [r12], #0x1
	ldrsb r3, [lr, #0x0]
	cmp r3, #0x0
	subeq r12, r12, #0x1
	beq _020E3054
	subs r2, r2, #0x1
	bne _020E3030
_020E3054:
	mov r1, #0x0
	strb r1, [r12, #0x0]
	ldmia sp!, {r3,pc}
	arm_func_end strncat

	arm_func_start strcmp
strcmp: ; 0x020E3060
	stmdb sp!, {r4,lr}
	ldrb r2, [r0, #0x0]
	ldrb r3, [r1, #0x0]
	subs r3, r2, r3
	movne r0, r3
	ldmneia sp!, {r4,pc}
	and r4, r0, #0x3
	and r3, r1, #0x3
	cmp r3, r4
	bne _020E313C
	cmp r4, #0x0
	beq _020E30D4
	cmp r2, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	rsbs r4, r4, #0x3
	beq _020E30CC
_020E30A4:
	ldrb r3, [r0, #0x1]!
	ldrb r2, [r1, #0x1]!
	subs r2, r3, r2
	movne r0, r2
	ldmneia sp!, {r4,pc}
	cmp r3, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	subs r4, r4, #0x1
	bne _020E30A4
_020E30CC:
	add r0, r0, #0x1
	add r1, r1, #0x1
_020E30D4:
	ldr r2, [r0, #0x0]
	ldr r3, _020E316C ; =0xFEFEFEFF
	mvn r4, r2
	add lr, r2, r3
	ldr ip, _020E3170 ; =0x80808080
	and r4, lr, r4
	tst r4, r12
	ldr r4, [r1, #0x0]
	bne _020E3128
	cmp r2, r4
	bne _020E311C
_020E3100:
	ldr r2, [r0, #0x4]!
	ldr r4, [r1, #0x4]!
	add lr, r2, r3
	tst lr, r12
	bne _020E3128
	cmp r2, r4
	beq _020E3100
_020E311C:
	sub r0, r0, #0x1
	sub r1, r1, #0x1
	b _020E313C
_020E3128:
	ldrb r2, [r0, #0x0]
	ldrb r3, [r1, #0x0]
	subs r3, r2, r3
	movne r0, r3
	ldmneia sp!, {r4,pc}
_020E313C:
	cmp r2, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_020E3148:
	ldrb r3, [r0, #0x1]!
	ldrb r2, [r1, #0x1]!
	subs r2, r3, r2
	movne r0, r2
	ldmneia sp!, {r4,pc}
	cmp r3, #0x0
	bne _020E3148
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020E316C: .word 0xFEFEFEFF
_020E3170: .word 0x80808080
	arm_func_end strcmp

	arm_func_start strncmp
strncmp: ; 0x020E3174
	cmp r2, #0x0
	beq _020E31A0
_020E317C:
	ldrb r12, [r1], #0x1
	ldrb r3, [r0], #0x1
	cmp r3, r12
	subne r0, r3, r12
	bxne lr
	cmp r3, #0x0
	beq _020E31A0
	subs r2, r2, #0x1
	bne _020E317C
_020E31A0:
	mov r0, #0x0
	bx lr
	arm_func_end strncmp

	arm_func_start strchr
strchr: ; 0x020E31A8
	ldrsb r2, [r0], #0x1
	mov r1, r1, lsl #0x18
	mov r1, r1, asr #0x18
	cmp r2, #0x0
	beq _020E31D4
_020E31BC:
	cmp r2, r1
	subeq r0, r0, #0x1
	bxeq lr
	ldrsb r2, [r0], #0x1
	cmp r2, #0x0
	bne _020E31BC
_020E31D4:
	cmp r1, #0x0
	movne r0, #0x0
	subeq r0, r0, #0x1
	bx lr
	arm_func_end strchr

	arm_func_start strspn
strspn: ; 0x020E31E4
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x20
	add r12, sp, #0x0
	mov r3, #0x8
	mov r2, #0x0
_020E31F8:
	strb r2, [r12, #0x0]
	strb r2, [r12, #0x1]
	strb r2, [r12, #0x2]
	strb r2, [r12, #0x3]
	add r12, r12, #0x4
	subs r3, r3, #0x1
	bne _020E31F8
	ldrb r3, [r1, #0x0]
	add r4, r1, #0x1
	cmp r3, #0x0
	beq _020E3254
	add lr, sp, #0x0
	mov r2, #0x1
_020E322C:
	and r12, r3, #0xff
	and r1, r3, #0x7
	mov r1, r2, lsl r1
	ldrb r3, [lr, r12, asr #0x3]
	and r1, r1, #0xff
	orr r1, r3, r1
	strb r1, [lr, r12, asr #0x3]
	ldrb r3, [r4], #0x1
	cmp r3, #0x0
	bne _020E322C
_020E3254:
	ldrb r1, [r0, #0x0]
	add r4, r0, #0x1
	cmp r1, #0x0
	beq _020E3294
	add r12, sp, #0x0
	mov r2, #0x1
_020E326C:
	and r3, r1, #0xff
	and r1, r1, #0x7
	mov r1, r2, lsl r1
	ldrb r3, [r12, r3, asr #0x3]
	and r1, r1, #0xff
	tst r3, r1
	bne _020E3294
	ldrb r1, [r4], #0x1
	cmp r1, #0x0
	bne _020E326C
_020E3294:
	sub r0, r4, r0
	sub r0, r0, #0x1
	add sp, sp, #0x20
	ldmia sp!, {r4,pc}
	arm_func_end strspn

	arm_func_start strstr
strstr: ; 0x020E32A4
	stmdb sp!, {r4,lr}
	cmp r1, #0x0
	ldrneb r2, [r1, #0x0]
	cmpne r2, #0x0
	ldmeqia sp!, {r4,pc}
	ldrb r3, [r0, #0x0]
	add r4, r0, #0x1
	cmp r3, #0x0
	beq _020E3308
_020E32C8:
	cmp r3, r2
	bne _020E32FC
	mov lr, r4
	add r12, r1, #0x1
_020E32D8:
	ldrb r3, [r12], #0x1
	ldrb r0, [lr], #0x1
	cmp r0, r3
	bne _020E32F0
	cmp r0, #0x0
	bne _020E32D8
_020E32F0:
	cmp r3, #0x0
	subeq r0, r4, #0x1
	ldmeqia sp!, {r4,pc}
_020E32FC:
	ldrb r3, [r4], #0x1
	cmp r3, #0x0
	bne _020E32C8
_020E3308:
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	arm_func_end strstr
