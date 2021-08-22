	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0


	thumb_func_start MOD05_021ED9C0
MOD05_021ED9C0: ; 0x021ED9C0
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #4
	add r3, r2, #0
	add r5, r0, #0
	bl MOD05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl MOD05_021ED9EC
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021ED9DC
MOD05_021ED9DC: ; 0x021ED9DC
	push {r4, lr}
	add r4, r0, #0
	bl MOD05_021EDA28
	add r0, r4, #0
	bl MOD05_021E4C00
	pop {r4, pc}

	thumb_func_start MOD05_021ED9EC
MOD05_021ED9EC: ; 0x021ED9EC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #4
	mov r2, #0x57
	bl MOD05_021E5078
	ldr r0, [r4]
	mov r1, #3
	mov r2, #6
	mov r3, #1
	bl MOD05_021E50D4
	mov r0, #3
	str r0, [sp]
	mov r3, #0
	mov r1, #4
	ldr r0, _021EDA24 ; =UNK05_021F8A48
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r4]
	add r2, r1, #0
	bl MOD05_021E4EFC
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_021EDA24: .word UNK05_021F8A48

	thumb_func_start MOD05_021EDA28
MOD05_021EDA28: ; 0x021EDA28
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #4
	bl MOD05_021E50A0
	ldr r0, [r4]
	mov r1, #3
	bl MOD05_021E5114
	ldr r0, [r4]
	mov r1, #4
	bl MOD05_021E506C
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDA48
MOD05_021EDA48: ; 0x021EDA48
	push {r4, r5, lr}
	sub sp, #0x24
	add r5, r0, #0
	bl MOD05_021E4C24
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_02058738
	str r0, [sp, #0x14]
	add r0, r4, #0
	mov r1, #0x18
	str r4, [sp, #0x18]
	bl MOD05_021E4C08
	str r0, [sp, #0x1c]
	add r1, sp, #8
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r5, #0
	mov r1, #2
	str r5, [sp, #0x20]
	bl FUN_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _021EDA94 ; =UNK05_021F8A34
	add r0, r4, #0
	add r2, sp, #8
	mov r3, #0
	bl MOD05_021E4DC4
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021EDA94: .word UNK05_021F8A34

	thumb_func_start MOD05_021EDA98
MOD05_021EDA98: ; 0x021EDA98
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r2, sp, #0
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r5, r0, #0
	str r1, [r2, #8]
	bl FUN_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x10
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x1c]
	bl FUN_02058448
	str r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	bl FUN_02058450
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_0206476C
	ldr r0, [r4, #0x14]
	mov r1, #4
	add r2, sp, #0
	bl MOD05_021E4EE4
	str r0, [r4, #0x20]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EDAE8
MOD05_021EDAE8: ; 0x021EDAE8
	ldr r3, _021EDAF0 ; =FUN_0201F744
	ldr r0, [r1, #0x20]
	bx r3
	nop
_021EDAF0: .word FUN_0201F744

	thumb_func_start MOD05_021EDAF4
MOD05_021EDAF4: ; 0x021EDAF4
	push {r4, lr}
	add r2, r1, #0
	add r4, r0, #0
	ldr r0, [r2, #0x1c]
	ldr r1, [r2, #4]
	ldr r2, [r2, #8]
	bl FUN_020582A8
	cmp r0, #0
	bne _021EDB0E
	add r0, r4, #0
	bl MOD05_021E4DE4
_021EDB0E:
	pop {r4, pc}

	thumb_func_start MOD05_021EDB10
MOD05_021EDB10: ; 0x021EDB10
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r4, [r5, #0x1c]
	ldr r1, [r5, #4]
	add r6, r0, #0
	ldr r2, [r5, #8]
	add r0, r4, #0
	bl FUN_020582A8
	cmp r0, #0
	bne _021EDB32
	add r0, r6, #0
	bl MOD05_021E4DE4
	add sp, #0x18
	pop {r4, r5, r6, pc}
_021EDB32:
	add r0, r4, #0
	add r1, sp, #0xc
	bl FUN_02058B5C
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02058B84
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #8]
	add r1, r1, r0
	mov r0, #3
	lsl r0, r0, #0xe
	str r1, [sp, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x20]
	add r1, sp, #0xc
	bl FUN_0201F7C8
	add sp, #0x18
	pop {r4, r5, r6, pc}
	.balign 4, 0

	.section .rodata

	.global UNK05_021F8A34
UNK05_021F8A34: ; 0x021F8A34
	.word 0x00000024, MOD05_021EDA98, MOD05_021EDAE8, MOD05_021EDAF4
	.word MOD05_021EDB10

	.global UNK05_021F8A48
UNK05_021F8A48: ; 0x021F8A48
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00
