	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F3FE0
MOD05_021F3FE0: ; 0x021F3FE0
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	mov r2, #0x1c
	add r4, r1, #0
	bl MIi_CpuClear32
	add r0, r5, #0
	mov r1, #8
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #4
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #2
	add r2, #8
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #2
	add r2, #0xc
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #2
	add r2, #0x18
	bl NARC_ReadFile
	add r0, r5, #0
	mov r1, #2
	add r2, sp, #0
	bl NARC_ReadFile
	add r2, r4, #0
	add r0, r5, #0
	mov r1, #4
	add r2, #0x14
	bl NARC_ReadFile
	add r4, #0x10
	add r0, r5, #0
	mov r1, #4
	add r2, r4, #0
	bl NARC_ReadFile
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4094
MOD05_021F4094: ; 0x021F4094
	push {r4, r5, r6, lr}
	ldr r4, [r2]
	mov r3, #0
	str r4, [r1, #0x10]
	ldr r5, [r0]
	mov r4, #0xc
	mul r4, r5
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F40B8
	add r3, r3, r4
_021F40B8:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #0x14]
	ldr r5, [r0, #4]
	mov r4, #0xc
	mul r4, r5
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F40DA
	add r3, r3, r4
_021F40DA:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #4]
	ldr r5, [r0, #8]
	mov r4, #0xc
	mul r4, r5
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F40FC
	add r3, r3, r4
_021F40FC:
	ldr r4, [r2]
	add r4, r4, r3
	add r3, #0x1c
	str r4, [r1]
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F4118
	add r3, r3, r4
_021F4118:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #8]
	ldr r4, [r0, #0xc]
	lsl r4, r4, #2
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F4138
	add r3, r3, r4
_021F4138:
	ldr r4, [r2]
	add r4, r4, r3
	str r4, [r1, #0xc]
	ldr r4, [r0, #0x14]
	add r3, r3, r4
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1e
	sub r5, r5, r6
	mov r4, #0x1e
	ror r5, r4
	add r4, r6, r5
	lsl r4, r4, #0x18
	lsr r4, r4, #0x18
	beq _021F4156
	add r3, r3, r4
_021F4156:
	ldr r2, [r2]
	add r2, r2, r3
	str r2, [r1, #0x18]
	ldr r0, [r0, #0x10]
	add r3, r3, r0
	lsr r2, r3, #0x1f
	lsl r1, r3, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _021F4174
	add r3, r3, r0
_021F4174:
	mov r0, #9
	lsl r0, r0, #0xc
	cmp r3, r0
	ble _021F4180
	bl GF_AssertFail
_021F4180:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4184
MOD05_021F4184: ; 0x021F4184
	ldr r3, _021F4190 ; =NARC_ReadFile
	add r2, r1, #0
	mov r1, #0x1c
	ldr r2, [r2]
	bx r3
	nop
_021F4190: .word NARC_ReadFile

	thumb_func_start MOD05_021F4194
MOD05_021F4194: ; 0x021F4194
	ldr r2, [r2]
	add r3, r1, #0
	mov r1, #0xc
	mul r1, r2
	ldr r2, [r3, #0x10]
	ldr r3, _021F41A4 ; =NARC_ReadFile
	bx r3
	nop
_021F41A4: .word NARC_ReadFile

	thumb_func_start MOD05_021F41A8
MOD05_021F41A8: ; 0x021F41A8
	ldr r2, [r2, #4]
	add r3, r1, #0
	mov r1, #0xc
	mul r1, r2
	ldr r2, [r3, #0x14]
	ldr r3, _021F41B8 ; =NARC_ReadFile
	bx r3
	nop
_021F41B8: .word NARC_ReadFile

	thumb_func_start MOD05_021F41BC
MOD05_021F41BC: ; 0x021F41BC
	ldr r2, [r2, #8]
	add r3, r1, #0
	mov r1, #0xc
	mul r1, r2
	ldr r2, [r3, #4]
	ldr r3, _021F41CC ; =NARC_ReadFile
	bx r3
	nop
_021F41CC: .word NARC_ReadFile

	thumb_func_start MOD05_021F41D0
MOD05_021F41D0: ; 0x021F41D0
	add r3, r1, #0
	ldr r1, [r2, #0xc]
	ldr r2, [r3, #8]
	ldr r3, _021F41DC ; =NARC_ReadFile
	lsl r1, r1, #2
	bx r3
	.balign 4, 0
_021F41DC: .word NARC_ReadFile

	thumb_func_start MOD05_021F41E0
MOD05_021F41E0: ; 0x021F41E0
	add r3, r1, #0
	ldr r1, [r2, #0x14]
	ldr r2, [r3, #0xc]
	ldr r3, _021F41EC ; =NARC_ReadFile
	bx r3
	nop
_021F41EC: .word NARC_ReadFile

	thumb_func_start MOD05_021F41F0
MOD05_021F41F0: ; 0x021F41F0
	add r3, r1, #0
	ldr r1, [r2, #0x10]
	ldr r2, [r3, #0x18]
	ldr r3, _021F41FC ; =NARC_ReadFile
	bx r3
	nop
_021F41FC: .word NARC_ReadFile

	thumb_func_start MOD05_021F4200
MOD05_021F4200: ; 0x021F4200
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r1, #0xa0
	ldr r1, [r1]
	add r5, r0, #0
	cmp r1, #1
	bne _021F4216
	add r1, r4, #0
	mov r2, #2
	add r1, #0x6c
	strb r2, [r1]
_021F4216:
	add r1, r4, #0
	add r1, #0x6c
	ldrb r1, [r1]
	cmp r1, #0
	beq _021F422A
	cmp r1, #1
	beq _021F425E
	cmp r1, #2
	beq _021F42EA
	b _021F4302
_021F422A:
	add r0, r4, #0
	add r0, #0xb0
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #0
	beq _021F423A
	mov r0, #0
	b _021F4302
_021F423A:
	add r0, r4, #0
	add r0, #0xa8
	add r1, r4, #0
	ldr r0, [r0]
	add r1, #0x4c
	bl MOD05_021F3FE0
	add r1, r4, #0
	add r1, #0x9c
	add r0, r4, #0
	add r2, r4, #0
	ldr r1, [r1]
	add r0, #0x4c
	add r2, #0x98
	bl MOD05_021F4094
	mov r0, #1
	b _021F4302
_021F425E:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD05_021F4184
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F4194
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41A8
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41BC
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41D0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41E0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0x9c
	add r2, r4, #0
	ldr r0, [r0]
	ldr r1, [r1]
	add r2, #0x4c
	bl MOD05_021F41F0
	mov r0, #1
	b _021F4302
_021F42EA:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
_021F4302:
	cmp r0, #1
	bne _021F4326
	add r0, r4, #0
	add r0, #0x6c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x6c
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x6c
	ldrb r0, [r0]
	cmp r0, #2
	bne _021F4326
	add r4, #0x9c
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, #0x1c]
_021F4326:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4328
MOD05_021F4328: ; 0x021F4328
	push {r3, lr}
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	mov r1, #0
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #4]
	str r1, [r0]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x18]
	pop {r3, pc}

	thumb_func_start MOD05_021F4344
MOD05_021F4344: ; 0x021F4344
	push {r0, r1, r2, r3}
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x1c
	add r4, r2, #0
	bl AllocFromHeapAtEnd
	add r6, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD05_021F3FE0
	add r0, r6, #0
	add r1, r4, #0
	add r2, sp, #0x1c
	bl MOD05_021F4094
	add r0, r5, #0
	add r1, r4, #0
	bl MOD05_021F4184
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F4194
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41A8
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41BC
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41D0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41E0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD05_021F41F0
	add r0, r6, #0
	bl FreeToHeap
	mov r0, #1
	str r0, [r4, #0x1c]
	pop {r4, r5, r6}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4, 0

	thumb_func_start MOD05_021F43C0
MOD05_021F43C0: ; 0x021F43C0
	push {r3, lr}
	cmp r0, #0
	beq _021F43CA
	bl FreeToHeap
_021F43CA:
	pop {r3, pc}

	thumb_func_start MOD05_021F43CC
MOD05_021F43CC: ; 0x021F43CC
	cmp r0, #0
	beq _021F43E2
	mov r1, #0
	str r1, [r0, #0x1c]
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #4]
	str r1, [r0]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x18]
_021F43E2:
	bx lr

	thumb_func_start MOD05_021F43E4
MOD05_021F43E4: ; 0x021F43E4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #4
	mov r1, #0xb4
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	add r2, r1, #0
	mov r0, #0
	add r2, #0x6c
	strb r0, [r2]
	add r2, r1, #0
	add r2, #0xa8
	str r5, [r2]
	add r2, r1, #0
	add r2, #0xac
	str r4, [r2]
	add r2, r1, #0
	add r2, #0x9c
	str r6, [r2]
	add r2, r1, #0
	add r2, #0xa4
	str r7, [r2]
	add r2, r1, #0
	add r2, #0xa0
	str r0, [r2]
	str r0, [r1, #0x68]
	str r0, [r1, #0x48]
	ldr r0, [sp, #0x18]
	ldr r2, [r0]
	add r0, r1, #0
	add r0, #0x98
	str r2, [r0]
	add r0, r1, #0
	ldr r2, [sp, #0x1c]
	add r0, #0xb0
	str r2, [r0]
	ldr r0, _021F4440 ; =MOD05_021F4200
	mov r2, #1
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F4440: .word MOD05_021F4200

	thumb_func_start MOD05_021F4444
MOD05_021F4444: ; 0x021F4444
	push {r3, lr}
	bl sub_0201B6C8
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F4454
MOD05_021F4454: ; 0x021F4454
	mov r1, #0
	str r1, [r0, #0x1c]
	bx lr
	.balign 4, 0
