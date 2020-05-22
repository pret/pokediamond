	.include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C59E4
UNK_021C59E4: ; 0x021C59E4
	.space 0x4

	.text

	thumb_func_start FUN_0202DB14
FUN_0202DB14: ; 0x0202DB14
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	bl FUN_020238F4
	str r0, [sp, #0x8]
	ldr r0, _0202DBA0 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202DB9A
	mov r1, #0xe9
	mov r0, #0xf
	lsl r1, r1, #0x2
	bl FUN_02016998
	ldr r1, _0202DBA0 ; =UNK_021C59E4
	mov r2, #0xe9
	str r0, [r1, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	mov r6, #0x0
	ldr r7, _0202DBA0 ; =UNK_021C59E4
	add r4, r6, #0x0
	add r5, r6, #0x0
_0202DB4A:
	ldr r1, [r7, #0x0]
	add r0, r1, #0x0
	add r0, #0x28
	add r2, r0, r4
	mov r0, #0xd2
	add r1, r1, r5
	lsl r0, r0, #0x2
	str r2, [r1, r0]
	add r0, r6, #0x0
	bl FUN_0202DE78
	add r6, r6, #0x1
	add r4, #0x68
	add r5, r5, #0x4
	cmp r6, #0x8
	blt _0202DB4A
	ldr r2, _0202DBA0 ; =UNK_021C59E4
	mov r1, #0x3a
	ldr r3, [r2, #0x0]
	mov r0, #0x0
	lsl r1, r1, #0x4
	strb r0, [r3, r1]
	ldr r4, [r2, #0x0]
	add r3, r1, #0x1
	strb r0, [r4, r3]
	add r3, r1, #0x2
	ldr r4, [r2, #0x0]
	sub r1, #0x58
	strb r0, [r4, r3]
	ldr r3, [r2, #0x0]
	ldr r0, [sp, #0x0]
	str r0, [r3, #0x4]
	ldr r3, [r2, #0x0]
	ldr r0, [sp, #0x4]
	str r0, [r3, #0x0]
	ldr r2, [r2, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [r2, r1]
	bl FUN_0202393C
_0202DB9A:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0202DBA0: .word UNK_021C59E4

	thumb_func_start FUN_0202DBA4
FUN_0202DBA4: ; 0x0202DBA4
	push {r3-r5, lr}
	ldr r1, _0202DBDC ; =UNK_021C59E4
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0202DBD8
	mov r4, #0x0
	mov r0, #0xd2
	add r5, r4, #0x0
	add r3, r4, #0x0
	lsl r0, r0, #0x2
_0202DBB8:
	ldr r2, [r1, #0x0]
	add r4, r4, #0x1
	add r2, r2, r5
	add r5, r5, #0x4
	str r3, [r2, r0]
	cmp r4, #0x8
	blt _0202DBB8
	ldr r0, _0202DBDC ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202DBD2
	bl FUN_02016A18
_0202DBD2:
	ldr r0, _0202DBDC ; =UNK_021C59E4
	mov r1, #0x0
	str r1, [r0, #0x0]
_0202DBD8:
	pop {r3-r5, pc}
	nop
_0202DBDC: .word UNK_021C59E4

	thumb_func_start FUN_0202DBE0
FUN_0202DBE0: ; 0x0202DBE0
	push {r3-r7, lr}
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_0202881C
	add r7, r0, #0x0
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_020286EC
	str r0, [sp, #0x0]
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_02029AFC
	add r6, r0, #0x0
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_020238F4
	ldr r1, _0202DCD8 ; =UNK_021C59E4
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x2
	add r2, r2, r1
	mov r1, #0xd2
	lsl r1, r1, #0x2
	ldr r1, [r2, r1]
	bl FUN_0202393C
	mov r0, #0x68
	add r5, r4, #0x0
	mul r5, r0
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	add r0, #0x64
	add r0, r0, r5
	bl OS_GetMacAddress
	add r0, r7, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_020287A8
	ldr r1, _0202DCD8 ; =UNK_021C59E4
	mov r2, #0x10
	ldr r1, [r1, #0x0]
	add r1, #0x54
	add r1, r1, r5
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl FUN_02029B38
	ldr r1, _0202DCD8 ; =UNK_021C59E4
	ldr r1, [r1, #0x0]
	add r1, r1, r5
	add r1, #0x6b
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02029B3C
	ldr r2, _0202DCD8 ; =UNK_021C59E4
	ldr r1, [r2, #0x0]
	add r1, r1, r5
	add r1, #0x6c
	strb r0, [r1, #0x0]
	ldr r0, [r2, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_02025C18
	ldr r2, _0202DCD8 ; =UNK_021C59E4
	ldr r1, [r2, #0x0]
	add r1, r1, r5
	add r1, #0x6d
	strb r0, [r1, #0x0]
	ldr r2, [r2, #0x0]
	mov r0, #0x1
	add r2, #0x6d
	ldrb r1, [r2, r5]
	sub r0, r0, r1
	strb r0, [r2, r5]
	ldr r0, [sp, #0x0]
	bl FUN_02028228
	ldr r1, _0202DCD8 ; =UNK_021C59E4
	ldr r1, [r1, #0x0]
	add r1, #0x48
	add r1, r1, r5
	bl FUN_02096CCC
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	mov r2, #0x20
	add r0, #0x8
	add r0, r0, r5
	bl MI_CpuFill8
	ldr r0, _0202DCD8 ; =UNK_021C59E4
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0202DCC4
	add r1, #0x8
	add r1, r1, r5
	bl FUN_02023ACC
_0202DCC4:
	ldr r1, _0202DCD8 ; =UNK_021C59E4
	mov r0, #0x3
	ldr r1, [r1, #0x0]
	mov r2, #0x68
	add r1, #0x8
	add r1, r1, r5
	bl FUN_02030ADC
	pop {r3-r7, pc}
	nop
_0202DCD8: .word UNK_021C59E4

	thumb_func_start FUN_0202DCDC
FUN_0202DCDC: ; 0x0202DCDC
	mov r0, #0x68
	bx lr

	thumb_func_start FUN_0202DCE0
FUN_0202DCE0: ; 0x0202DCE0
	ldr r0, _0202DCF4 ; =UNK_021C59E4
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0202DCF0
	mov r0, #0x3a
	mov r1, #0x1
	lsl r0, r0, #0x4
	strb r1, [r2, r0]
_0202DCF0:
	bx lr
	nop
_0202DCF4: .word UNK_021C59E4

	thumb_func_start FUN_0202DCF8
FUN_0202DCF8: ; 0x0202DCF8
	ldr r0, _0202DD04 ; =UNK_021C59E4
	ldr r1, [r0, #0x0]
	mov r0, #0x3a
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202DD04: .word UNK_021C59E4

	thumb_func_start FUN_0202DD08
FUN_0202DD08: ; 0x0202DD08
	push {r3-r5, lr}
	ldr r1, _0202DD78 ; =UNK_021C59E4
	add r4, r2, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0202DD74
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202DD74
	ldr r1, _0202DD78 ; =UNK_021C59E4
	mov r2, #0x68
	ldr r5, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x62
	ldrb r1, [r1, #0x0]
	add r5, #0x8
	add r0, r4, #0x0
	add r3, r1, #0x0
	mul r3, r2
	add r1, r5, r3
	bl MI_CpuCopy8
	add r4, #0x62
	ldr r2, _0202DD78 ; =UNK_021C59E4
	ldrb r3, [r4, #0x0]
	ldr r0, [r2, #0x0]
	ldr r1, _0202DD7C ; =0x000003A2
	strb r3, [r0, r1]
	add r0, r1, #0x0
	ldr r3, [r2, #0x0]
	sub r0, #0xa
	add r4, r3, r0
	ldrb r3, [r3, r1]
	ldrb r0, [r4, r3]
	cmp r0, #0x2
	bhs _0202DD74
	mov r0, #0x1
	strb r0, [r4, r3]
	ldr r0, [r2, #0x0]
	ldrb r4, [r0, r1]
	bl FUN_02031190
	cmp r4, r0
	bne _0202DD74
	ldr r0, _0202DD78 ; =UNK_021C59E4
	mov r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
_0202DD74:
	pop {r3-r5, pc}
	nop
_0202DD78: .word UNK_021C59E4
_0202DD7C: .word 0x000003A2

	thumb_func_start FUN_0202DD80
FUN_0202DD80: ; 0x0202DD80
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202DDE0 ; =UNK_021C59E4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202DDDC
	mov r3, #0x68
	add r4, r5, #0x0
	add r0, r2, #0x0
	mul r4, r3
	add r1, #0x8
	add r1, r1, r4
	add r2, r3, #0x0
	bl MI_CpuCopy8
	ldr r0, _0202DDE0 ; =UNK_021C59E4
	add r1, r5, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x64
	add r0, r0, r4
	bl FUN_0202EFAC
	ldr r0, _0202DDE0 ; =UNK_021C59E4
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bl FUN_02031190
	cmp r5, r0
	bne _0202DDD2
	ldr r0, _0202DDE0 ; =UNK_021C59E4
	mov r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	pop {r3-r5, pc}
_0202DDD2:
	ldr r0, _0202DDE0 ; =UNK_021C59E4
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0202DDE4 ; =0x000003A1
	strb r2, [r1, r0]
_0202DDDC:
	pop {r3-r5, pc}
	nop
_0202DDE0: .word UNK_021C59E4
_0202DDE4: .word 0x000003A1

	thumb_func_start FUN_0202DDE8
FUN_0202DDE8: ; 0x0202DDE8
	push {r3-r7, lr}
	ldr r0, _0202DE70 ; =UNK_021C59E4
	ldr r1, [r0, #0x0]
	ldr r0, _0202DE74 ; =0x000003A1
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0202DDFA
	mov r0, #0x0
	pop {r3-r7, pc}
_0202DDFA:
	mov r0, #0x5
	bl FUN_02031354
	cmp r0, #0x0
	bne _0202DE6C
	mov r4, #0x0
	add r5, r4, #0x0
	add r7, r4, #0x0
_0202DE0A:
	ldr r0, _0202DE70 ; =UNK_021C59E4
	ldr r2, [r0, #0x0]
	mov r0, #0xe6
	add r1, r2, r4
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202DE4A
	add r0, r2, r5
	add r0, #0x6a
	strb r4, [r0, #0x0]
	ldr r0, _0202DE70 ; =UNK_021C59E4
	ldr r6, [r0, #0x0]
	bl FUN_02023924
	add r2, r0, #0x0
	mov r0, #0xd2
	add r1, r6, r7
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r6, #0x28
	add r1, r6, r5
	bl MI_CpuCopy8
	ldr r1, _0202DE70 ; =UNK_021C59E4
	mov r0, #0x4
	ldr r1, [r1, #0x0]
	mov r2, #0x68
	add r1, #0x8
	add r1, r1, r5
	bl FUN_02031000
_0202DE4A:
	add r4, r4, #0x1
	add r5, #0x68
	add r7, r7, #0x4
	cmp r4, #0x8
	blt _0202DE0A
	mov r1, #0x0
	mov r0, #0x5
	add r2, r1, #0x0
	bl FUN_02031000
	ldr r0, _0202DE70 ; =UNK_021C59E4
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0202DE74 ; =0x000003A1
	strb r2, [r1, r0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0202DE6C:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0202DE70: .word UNK_021C59E4
_0202DE74: .word 0x000003A1

	thumb_func_start FUN_0202DE78
FUN_0202DE78: ; 0x0202DE78
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0202DEA0 ; =UNK_021C59E4
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r1, r1, r0
	mov r0, #0xd2
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_02023948
	ldr r0, _0202DEA0 ; =UNK_021C59E4
	mov r2, #0x0
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	pop {r4, pc}
	nop
_0202DEA0: .word UNK_021C59E4

	thumb_func_start FUN_0202DEA4
FUN_0202DEA4: ; 0x0202DEA4
	ldr r1, _0202DEBC ; =UNK_021C59E4
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _0202DEB8
	mov r0, #0x1
	bx lr
_0202DEB8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202DEBC: .word UNK_021C59E4

	thumb_func_start FUN_0202DEC0
FUN_0202DEC0: ; 0x0202DEC0
	ldr r1, _0202DEDC ; =UNK_021C59E4
	mov r2, #0x1
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x2
	beq _0202DED8
	cmp r0, #0x1
	beq _0202DED8
	mov r2, #0x0
_0202DED8:
	add r0, r2, #0x0
	bx lr
	.balign 4
_0202DEDC: .word UNK_021C59E4

	thumb_func_start FUN_0202DEE0
FUN_0202DEE0: ; 0x0202DEE0
	ldr r1, _0202DEF0 ; =UNK_021C59E4
	mov r2, #0x2
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202DEF0: .word UNK_021C59E4

	thumb_func_start FUN_0202DEF4
FUN_0202DEF4: ; 0x0202DEF4
	ldr r1, _0202DF04 ; =UNK_021C59E4
	mov r2, #0x3
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202DF04: .word UNK_021C59E4

	thumb_func_start FUN_0202DF08
FUN_0202DF08: ; 0x0202DF08
	ldr r1, _0202DF24 ; =UNK_021C59E4
	mov r0, #0x0
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	lsl r1, r1, #0x2
_0202DF12:
	ldrb r2, [r3, r1]
	cmp r2, #0x1
	beq _0202DF22
	add r0, r0, #0x1
	add r3, r3, #0x1
	cmp r0, #0x8
	blt _0202DF12
	mov r0, #0xff
_0202DF22:
	bx lr
	.balign 4
_0202DF24: .word UNK_021C59E4

	thumb_func_start FUN_0202DF28
FUN_0202DF28: ; 0x0202DF28
	push {r3-r4}
	ldr r1, _0202DF50 ; =UNK_021C59E4
	mov r0, #0x0
	ldr r4, [r1, #0x0]
	mov r1, #0xe6
	add r3, r0, #0x0
	lsl r1, r1, #0x2
_0202DF36:
	ldrb r2, [r4, r1]
	cmp r2, #0x2
	beq _0202DF40
	cmp r2, #0x3
	bne _0202DF42
_0202DF40:
	add r0, r0, #0x1
_0202DF42:
	add r3, r3, #0x1
	add r4, r4, #0x1
	cmp r3, #0x8
	blt _0202DF36
	pop {r3-r4}
	bx lr
	nop
_0202DF50: .word UNK_021C59E4

	thumb_func_start FUN_0202DF54
FUN_0202DF54: ; 0x0202DF54
	push {r4-r6, lr}
	ldr r0, _0202DFA0 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202DF9C
	bl FUN_02030F20
	cmp r0, #0x0
	beq _0202DF9C
	mov r6, #0xe6
	ldr r4, _0202DFA0 ; =UNK_021C59E4
	mov r5, #0x0
	lsl r6, r6, #0x2
_0202DF6E:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202DF96
	cmp r5, #0x0
	bne _0202DF86
	bl FUN_02031280
	cmp r0, #0x0
	bne _0202DF96
_0202DF86:
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	ldrb r0, [r0, r6]
	cmp r0, #0x0
	beq _0202DF96
	add r0, r5, #0x0
	bl FUN_0202DE78
_0202DF96:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202DF6E
_0202DF9C:
	pop {r4-r6, pc}
	nop
_0202DFA0: .word UNK_021C59E4

	thumb_func_start FUN_0202DFA4
FUN_0202DFA4: ; 0x0202DFA4
	ldr r1, _0202DFD4 ; =UNK_021C59E4
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	bne _0202DFB0
	mov r0, #0x0
	bx lr
_0202DFB0:
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x1
	beq _0202DFC4
	cmp r1, #0x2
	beq _0202DFC4
	cmp r1, #0x3
	bne _0202DFD0
_0202DFC4:
	lsl r0, r0, #0x2
	add r1, r3, r0
	mov r0, #0xd2
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bx lr
_0202DFD0:
	mov r0, #0x0
	bx lr
	.balign 4
_0202DFD4: .word UNK_021C59E4

	thumb_func_start FUN_0202DFD8
FUN_0202DFD8: ; 0x0202DFD8
	ldr r1, _0202DFF8 ; =UNK_021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202DFF2
	mov r1, #0x68
	add r3, #0x48
	mul r1, r0
	add r0, r3, r1
	bx lr
_0202DFF2:
	mov r0, #0x0
	bx lr
	nop
_0202DFF8: .word UNK_021C59E4

	thumb_func_start FUN_0202DFFC
FUN_0202DFFC: ; 0x0202DFFC
	ldr r1, _0202E01C ; =UNK_021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E016
	mov r1, #0x68
	add r3, #0x54
	mul r1, r0
	add r0, r3, r1
	bx lr
_0202E016:
	mov r0, #0x0
	bx lr
	nop
_0202E01C: .word UNK_021C59E4

	thumb_func_start FUN_0202E020
FUN_0202E020: ; 0x0202E020
	ldr r1, _0202E040 ; =UNK_021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E03C
	mov r1, #0x68
	mul r1, r0
	add r0, r3, r1
	add r0, #0x6b
	ldrb r0, [r0, #0x0]
	bx lr
_0202E03C:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E040: .word UNK_021C59E4

	thumb_func_start FUN_0202E044
FUN_0202E044: ; 0x0202E044
	ldr r1, _0202E064 ; =UNK_021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E060
	mov r1, #0x68
	mul r1, r0
	add r0, r3, r1
	add r0, #0x6c
	ldrb r0, [r0, #0x0]
	bx lr
_0202E060:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E064: .word UNK_021C59E4

	thumb_func_start FUN_0202E068
FUN_0202E068: ; 0x0202E068
	ldr r1, _0202E088 ; =UNK_021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E084
	mov r1, #0x68
	mul r1, r0
	add r0, r3, r1
	add r0, #0x6d
	ldrb r0, [r0, #0x0]
	bx lr
_0202E084:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E088: .word UNK_021C59E4

	thumb_func_start FUN_0202E08C
FUN_0202E08C: ; 0x0202E08C
	push {r4-r6, lr}
	mov r4, #0x0
	add r5, r4, #0x0
	add r6, r4, #0x0
_0202E094:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202E0E8
	ldr r0, _0202E0F4 ; =UNK_021C59E4
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xe6
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202E0E8
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202E0E8
	ldr r0, _0202E0F4 ; =UNK_021C59E4
	ldr r1, _0202E0F8 ; =0x00000399
	ldr r0, [r0, #0x0]
	add r2, r0, r4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E0E8
	add r1, r6, #0x0
	add r2, r0, r5
_0202E0D0:
	add r3, r2, #0x0
	add r3, #0x70
	ldrb r0, [r2, #0x8]
	ldrb r3, [r3, #0x0]
	cmp r0, r3
	beq _0202E0E0
	mov r0, #0x0
	pop {r4-r6, pc}
_0202E0E0:
	add r1, r1, #0x1
	add r2, r2, #0x1
	cmp r1, #0x20
	blt _0202E0D0
_0202E0E8:
	add r4, r4, #0x1
	add r5, #0x68
	cmp r4, #0x7
	blt _0202E094
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0202E0F4: .word UNK_021C59E4
_0202E0F8: .word 0x00000399

	thumb_func_start FUN_0202E0FC
FUN_0202E0FC: ; 0x0202E0FC
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0202E1B4 ; =UNK_021C59E4
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202E1B0
	cmp r7, #0x2
	beq _0202E11C
	bl FUN_02031190
	bl FUN_020313CC
	mov r1, #0x1
	and r0, r1
	str r0, [sp, #0x0]
_0202E11C:
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _0202E1B0
	add r5, r4, #0x0
_0202E128:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202E1A4
	ldr r0, _0202E1B4 ; =UNK_021C59E4
	mov r1, #0xe6
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x2
	add r2, r0, r4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E1A4
	cmp r7, #0x0
	bne _0202E16E
	add r0, r4, #0x0
	bl FUN_020313CC
	mov r1, #0x1
	and r1, r0
	ldr r0, [sp, #0x0]
	cmp r0, r1
	beq _0202E1A4
	ldr r0, _0202E1B4 ; =UNK_021C59E4
	mov r1, #0xda
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x2
	add r0, r0, r5
	ldrh r1, [r0, r1]
	add r2, r1, r6
	mov r1, #0xda
	lsl r1, r1, #0x2
	strh r2, [r0, r1]
	b _0202E1A4
_0202E16E:
	cmp r7, #0x1
	bne _0202E194
	add r0, r4, #0x0
	bl FUN_020313CC
	mov r1, #0x1
	and r1, r0
	ldr r0, [sp, #0x0]
	cmp r0, r1
	beq _0202E1A4
	ldr r0, _0202E1B4 ; =UNK_021C59E4
	ldr r1, _0202E1B8 ; =0x0000036A
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	ldrh r1, [r0, r1]
	add r2, r1, r6
	ldr r1, _0202E1B8 ; =0x0000036A
	strh r2, [r0, r1]
	b _0202E1A4
_0202E194:
	mov r1, #0xdb
	add r0, r0, r5
	lsl r1, r1, #0x2
	ldrh r1, [r0, r1]
	add r2, r1, r6
	mov r1, #0xdb
	lsl r1, r1, #0x2
	strh r2, [r0, r1]
_0202E1A4:
	add r5, r5, #0x6
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _0202E128
_0202E1B0:
	pop {r3-r7, pc}
	nop
_0202E1B4: .word UNK_021C59E4
_0202E1B8: .word 0x0000036A

	thumb_func_start FUN_0202E1BC
FUN_0202E1BC: ; 0x0202E1BC
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	bl FUN_020286EC
	str r0, [sp, #0x4]
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _0202E224
	add r5, r4, #0x0
_0202E1D4:
	add r0, r4, #0x0
	bl FUN_0202DFD8
	add r1, r0, #0x0
	beq _0202E218
	add r0, r7, #0x0
	add r2, sp, #0x8
	bl FUN_02033874
	cmp r0, #0x0
	beq _0202E1EE
	cmp r0, #0x1
	bne _0202E218
_0202E1EE:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bge _0202E1F8
	bl ErrorHandling
_0202E1F8:
	ldr r0, _0202E254 ; =UNK_021C59E4
	mov r2, #0xda
	ldr r0, [r0, #0x0]
	ldr r3, _0202E258 ; =0x0000036A
	add r6, r0, r5
	mov r0, #0xdb
	lsl r0, r0, #0x2
	ldrh r0, [r6, r0]
	lsl r2, r2, #0x2
	str r0, [sp, #0x0]
	ldrh r2, [r6, r2]
	ldrh r3, [r6, r3]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	bl FUN_02028608
_0202E218:
	add r5, r5, #0x6
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _0202E1D4
_0202E224:
	mov r3, #0xda
	mov r2, #0x0
	lsl r3, r3, #0x2
	ldr r6, _0202E254 ; =UNK_021C59E4
	add r1, r2, #0x0
	add r0, r2, #0x0
	add r4, r3, #0x2
	add r5, r3, #0x4
_0202E234:
	ldr r7, [r6, #0x0]
	add r2, r2, #0x1
	add r7, r7, r1
	strh r0, [r7, r3]
	ldr r7, [r6, #0x0]
	add r7, r7, r1
	strh r0, [r7, r4]
	ldr r7, [r6, #0x0]
	add r7, r7, r1
	add r1, r1, #0x6
	strh r0, [r7, r5]
	cmp r2, #0x8
	blt _0202E234
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0202E254: .word UNK_021C59E4
_0202E258: .word 0x0000036A

	thumb_func_start FUN_0202E25C
FUN_0202E25C: ; 0x0202E25C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x1
	bne _0202E26E
	mov r0, #0x0
	mov r1, #0x1
	bl FUN_0202E0FC
	b _0202E27E
_0202E26E:
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0202E27E
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0202E0FC
_0202E27E:
	add r0, r4, #0x0
	bl FUN_0202E1BC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202E288
FUN_0202E288: ; 0x0202E288
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_0202E0FC
	add r0, r4, #0x0
	bl FUN_0202E1BC
	pop {r4, pc}
	.balign 4
