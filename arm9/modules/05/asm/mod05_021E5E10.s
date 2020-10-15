	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E5E10
MOD05_021E5E10: ; 0x021E5E10
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x38
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl MOD05_021E5E3C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5E2C
MOD05_021E5E2C: ; 0x021E5E2C
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021E5E74
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5E3C
MOD05_021E5E3C: ; 0x021E5E3C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x28
	bl MOD05_021E5294
	ldr r0, [r4]
	add r1, r4, #4
	mov r2, #0x5b
	mov r3, #0
	bl MOD05_021E5224
	mov r0, #0x72
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r1, r4, #0
	ldr r0, [r4]
	add r2, r4, #4
	add r4, #0x28
	add r1, #0x14
	add r3, r4, #0
	bl MOD05_021E5260
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD05_021E5E74
MOD05_021E5E74: ; 0x021E5E74
	push {r4, lr}
	add r4, r0, #0
	add r0, r4, #4
	bl MOD05_021F52C8
	add r0, r4, #0
	add r4, #0x28
	add r0, #0x14
	add r1, r4, #0
	bl MOD05_021F5358
	pop {r4, pc}

	thumb_func_start MOD05_021E5E8C
MOD05_021E5E8C: ; 0x021E5E8C
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	bl MOD05_021E4C24
	mov r1, #0xa
	str r0, [sp, #8]
	bl MOD05_021E4C08
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, sp, #0x10
	bl FUN_02058B5C
	add r0, r4, #0
	bl FUN_020584C4
	cmp r0, #3
	bhi _021E5EF4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E5EBE: ; jump table
	.short _021E5EC6 - _021E5EBE - 2 ; case 0
	.short _021E5ED2 - _021E5EBE - 2 ; case 1
	.short _021E5EEA - _021E5EBE - 2 ; case 2
	.short _021E5EDE - _021E5EBE - 2 ; case 3
_021E5EC6:
	mov r0, #1
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x18]
	b _021E5EF4
_021E5ED2:
	mov r0, #1
	ldr r1, [sp, #0x18]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x18]
	b _021E5EF4
_021E5EDE:
	mov r0, #1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x10]
	b _021E5EF4
_021E5EEA:
	mov r0, #1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x10]
_021E5EF4:
	add r0, r4, #0
	mov r1, #2
	bl FUN_0205829C
	add r1, sp, #8
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, _021E5F14 ; =UNK05_021F76D8
	add r2, sp, #0x10
	mov r3, #0
	bl MOD05_021E4DC4
	add sp, #0x1c
	pop {r3, r4, pc}
	nop
_021E5F14: .word UNK05_021F76D8

	thumb_func_start MOD05_021E5F18
MOD05_021E5F18: ; 0x021E5F18
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	bl FUN_0206475C
	ldr r1, [r0]
	ldr r0, [r0, #4]
	mov r2, #1
	str r1, [r5, #4]
	str r0, [r5, #8]
	ldr r0, [r5, #4]
	mov r1, #0x90
	mov r3, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r4, [r5]
	ldr r0, [r5, #4]
	add r1, r4, #4
	bl MOD05_021E5294
	ldr r2, [r5, #8]
	add r0, r4, #4
	ldr r1, [r2, #0x18]
	ldr r2, [r2, #0xc]
	bl FUN_020BB8D0
	str r0, [r4]
	ldr r3, [r5, #8]
	ldr r1, [r3, #0x18]
	ldr r2, [r3, #0xc]
	ldr r3, [r3, #0x10]
	bl FUN_020B8110
	ldr r1, [r5, #8]
	add r0, r4, #0
	add r0, #0x18
	add r1, r1, #4
	bl MOD05_021F5400
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x18
	bl FUN_020B7EFC
	add r0, r6, #0
	add r1, sp, #0
	bl FUN_0206477C
	add r4, #0x18
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl MOD05_021F54D0
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	thumb_func_start MOD05_021E5F90
MOD05_021E5F90: ; 0x021E5F90
	push {r4, lr}
	ldr r4, [r1]
	ldr r1, [r4]
	add r0, r4, #4
	bl thunk_FUN_020ae84c
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5FA4
MOD05_021E5FA4: ; 0x021E5FA4
	push {r4, lr}
	ldr r1, [r1]
	ldr r2, [r1]
	ldr r3, [r1, #0x14]
	ldr r2, [r2, #8]
	ldrh r2, [r2, #4]
	lsl r4, r2, #0xc
	mov r2, #1
	lsl r2, r2, #0xc
	add r2, r3, r2
	str r2, [r1, #0x14]
	cmp r2, r4
	ble _021E5FC4
	bl MOD05_021E4DE4
	pop {r4, pc}
_021E5FC4:
	ldr r0, [r1]
	str r2, [r0]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5FCC
MOD05_021E5FCC: ; 0x021E5FCC
	ldr r0, [r1]
	ldr r3, _021E5FD4 ; =MOD05_021F5430
	add r0, #0x18
	bx r3
	.balign 4, 0
_021E5FD4: .word MOD05_021F5430

	.section .rodata

	.global UNK05_021F76D8
UNK05_021F76D8: ; 0x021F76D8
	.word 0x0000000C, MOD05_021E5F18, MOD05_021E5F90, MOD05_021E5FA4
	.word MOD05_021E5FCC
