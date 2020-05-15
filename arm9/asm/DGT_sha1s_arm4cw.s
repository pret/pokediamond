	.include "asm/macros.inc"
	.include "global.inc"

	.text

_020D33B4: .word 0x00FF00FF
_020D33B8: .word 0x5A827999
_020D33BC: .word 0x6ED9EBA1
_020D33C0: .word 0x8F1BBCDC
_020D33C4: .word 0xCA62C1D6

	arm_func_start DGTi_hash2_arm4_small
DGTi_hash2_arm4_small: ; 0x020D33C8
	stmdb sp!, {r4-r12,lr}
	ldmia r0, {r3,r9-r12}
	sub sp, sp, #0x84
	str r2, [sp, #0x80]
_020D33D8:
	ldr r8, _020D33B8 ; =0x5A827999
	ldr r7, _020D33B4 ; =0x00FF00FF
	mov r6, sp
	mov r5, #0x0
_020D33E8:
	ldr r4, [r1], #0x4
	add r2, r8, r12
	add r2, r2, r3, ror #0x1B
	and lr, r4, r7
	and r4, r7, r4, ror #0x18
	orr r4, r4, lr, ror #0x8
	str r4, [r6, #0x40]
	str r4, [r6], #0x4
	add r2, r2, r4
	eor r4, r10, r11
	and r4, r4, r9
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r5, r5, #0x4
	cmp r5, #0x40
	blt _020D33E8
	mov r7, #0x0
	mov r6, sp
_020D3448:
	ldr r2, [r6, #0x0]
	ldr r5, [r6, #0x8]
	ldr r4, [r6, #0x20]
	ldr lr, [r6, #0x34]
	eor r2, r2, r5
	eor r4, r4, lr
	eor r2, r2, r4
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor r4, r10, r11
	and r4, r4, r9
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x4
	cmp r7, #0x10
	blt _020D3448
	ldr r8, _020D33BC ; =0x6ED9EBA1
	mov r7, #0x0
_020D34B8:
	ldr r2, [r6, #0x0]
	ldr r4, [r6, #0x8]
	ldr lr, [r6, #0x20]
	ldr r5, [r6, #0x34]
	eor r2, r2, r4
	eor lr, lr, r5
	eor r2, r2, lr
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor lr, r9, r10
	eor lr, lr, r11
	add r2, r2, lr
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0xc
	moveq r6, sp
	cmp r7, #0x14
	blt _020D34B8
	ldr r8, _020D33C0 ; =0x8F1BBCDC
	mov r7, #0x0
_020D352C:
	ldr r2, [r6, #0x0]
	ldr lr, [r6, #0x8]
	ldr r5, [r6, #0x20]
	ldr r4, [r6, #0x34]
	eor r2, r2, lr
	eor r5, r5, r4
	eor r2, r2, r5
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	orr r5, r9, r10
	and r5, r5, r11
	and r4, r9, r10
	orr r5, r5, r4
	add r2, r2, r5
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0x8
	moveq r6, sp
	cmp r7, #0x14
	blt _020D352C
	ldr r8, _020D33C4 ; =0xCA62C1D6
	mov r7, #0x0
_020D35A8:
	ldr r2, [r6, #0x0]
	ldr r5, [r6, #0x8]
	ldr r4, [r6, #0x20]
	ldr lr, [r6, #0x34]
	eor r2, r2, r5
	eor r4, r4, lr
	eor r2, r2, r4
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor r4, r9, r10
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0x4
	moveq r6, sp
	cmp r7, #0x14
	blt _020D35A8
	ldmia r0, {r2,r4,r6-r7,lr}
	add r3, r3, r2
	add r9, r9, r4
	add r10, r10, r6
	add r11, r11, r7
	add r12, r12, lr
	stmia r0, {r3,r9-r12}
	ldr lr, [sp, #0x80]
	subs lr, lr, #0x40
	str lr, [sp, #0x80]
	bgt _020D33D8
	add sp, sp, #0x84
	ldmia sp!, {r4-r12,pc}
