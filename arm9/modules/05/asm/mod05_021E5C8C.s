	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E5C8C
MOD05_021E5C8C: ; 0x021E5C8C
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x3c
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4, #4]
	bl MOD05_021E5CB8
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5CA8
MOD05_021E5CA8: ; 0x021E5CA8
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021E5CF4
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5CB8
MOD05_021E5CB8: ; 0x021E5CB8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x2c
	bl MOD05_021E5294
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #8
	mov r2, #0x5c
	mov r3, #0
	bl MOD05_021E5224
	mov r0, #0x73
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	add r1, r4, #0
	add r2, r4, #0
	ldr r0, [r4, #4]
	add r4, #0x2c
	add r1, #0x18
	add r2, #8
	add r3, r4, #0
	bl MOD05_021E5260
	add sp, #8
	pop {r4, pc}

	thumb_func_start MOD05_021E5CF4
MOD05_021E5CF4: ; 0x021E5CF4
	push {r4, lr}
	add r4, r0, #0
	add r0, #8
	bl MOD05_021F52C8
	add r0, r4, #0
	add r4, #0x2c
	add r0, #0x18
	add r1, r4, #0
	bl MOD05_021F5358
	pop {r4, pc}

	thumb_func_start MOD05_021E5D0C
MOD05_021E5D0C: ; 0x021E5D0C
	push {r4, r5, lr}
	sub sp, #0x1c
	ldr r0, [r0, #0x3c]
	add r5, r1, #0
	mov r1, #9
	add r4, r2, #0
	str r0, [sp, #8]
	bl MOD05_021E4C08
	str r0, [sp, #0xc]
	mov r0, #2
	mov r3, #0
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r1, r1, r0
	str r1, [sp, #0x10]
	lsl r1, r4, #0x10
	add r0, r1, r0
	str r0, [sp, #0x18]
	str r3, [sp, #0x14]
	add r0, sp, #8
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, _021E5D4C ; =UNK05_021F76C4
	add r2, sp, #0x10
	bl MOD05_021E4DC4
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_021E5D4C: .word UNK05_021F76C4

	thumb_func_start MOD05_021E5D50
MOD05_021E5D50: ; 0x021E5D50
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
	ldr r1, [r2, #0x1c]
	ldr r2, [r2, #0x10]
	bl FUN_020BB8D0
	str r0, [r4]
	ldr r3, [r5, #8]
	ldr r1, [r3, #0x1c]
	ldr r2, [r3, #0x10]
	ldr r3, [r3, #0x14]
	bl FUN_020B8110
	ldr r1, [r5, #8]
	add r0, r4, #0
	add r0, #0x18
	add r1, #8
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

	thumb_func_start MOD05_021E5DC8
MOD05_021E5DC8: ; 0x021E5DC8
	push {r4, lr}
	ldr r4, [r1]
	ldr r1, [r4]
	add r0, r4, #4
	bl thunk_FUN_020ae84c
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021E5DDC
MOD05_021E5DDC: ; 0x021E5DDC
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
	ble _021E5DFC
	bl MOD05_021E4DE4
	pop {r4, pc}
_021E5DFC:
	ldr r0, [r1]
	str r2, [r0]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E5E04
MOD05_021E5E04: ; 0x021E5E04
	ldr r0, [r1]
	ldr r3, _021E5E0C ; =MOD05_021F5430
	add r0, #0x18
	bx r3
	.balign 4, 0
_021E5E0C: .word MOD05_021F5430

	.section .rodata

	.global UNK05_021F76C4
UNK05_021F76C4: ; 0x021F76C4
	.word 0x0000000C, MOD05_021E5D50, MOD05_021E5DC8, MOD05_021E5DDC
	.word MOD05_021E5E04
