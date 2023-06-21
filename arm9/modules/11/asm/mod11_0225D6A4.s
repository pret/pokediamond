	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_0225D6A4
MOD11_0225D6A4: ; 0x0225D6A4
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x52
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #2
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x28]
	add r4, r1, #0
	add r6, r3, #0
	str r0, [sp, #0x14]
	add r0, r2, #0
	mov r1, #3
	add r2, r5, #0
	add r3, r4, #0
	bl sub_0200C0DC
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x52
	mov r3, #0xa
	str r6, [sp, #8]
	bl sub_0200C00C
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x52
	mov r3, #0xc
	bl sub_0200C124
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x30]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x52
	mov r3, #0xd
	bl sub_0200C13C
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_0225D714
MOD11_0225D714: ; 0x0225D714
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	bl sub_0200C358
	add r0, r5, #0
	add r1, r4, #0
	bl sub_0200C368
	add r0, r5, #0
	add r1, r6, #0
	bl sub_0200C378
	ldr r1, [sp, #0x10]
	add r0, r5, #0
	bl sub_0200C388
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start MOD11_0225D73C
MOD11_0225D73C: ; 0x0225D73C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	ldr r5, _0225D7AC ; =MOD11_0225FEE4
	add r6, r3, #0
	add r7, r0, #0
	str r1, [sp]
	add r4, sp, #4
	mov r3, #6
_0225D74C:
	ldmia r5!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _0225D74C
	ldr r0, [r5]
	mov r1, #0x20
	str r0, [r4]
	ldr r0, [sp, #0x50]
	str r6, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x60]
	str r0, [sp, #0x30]
	add r0, r2, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x20
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r1, [sp]
	add r0, r7, #0
	add r2, sp, #4
	bl sub_0200C154
	mov r1, #0
	str r0, [r4]
	bl sub_0200C644
	mov r0, #3
	lsl r0, r0, #0x12
	str r0, [r4, #0x14]
	ldr r0, _0225D7B0 ; =MOD11_0225D828
	ldr r2, _0225D7B4 ; =0x000003E7
	add r1, r4, #0
	bl sub_0200CA44
	str r0, [r4, #4]
	add r0, r4, #0
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225D7AC: .word MOD11_0225FEE4
_0225D7B0: .word MOD11_0225D828
_0225D7B4: .word 0x000003E7

	thumb_func_start MOD11_0225D7B8
MOD11_0225D7B8: ; 0x0225D7B8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl sub_0200C3DC
	ldr r0, [r4, #4]
	bl sub_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD11_0225D7D0
MOD11_0225D7D0: ; 0x0225D7D0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl MOD11_0225D98C
	str r7, [r5, #8]
	str r4, [r5, #0xc]
	str r6, [r5, #0x14]
	lsl r1, r7, #0x10
	lsl r2, r4, #0x10
	ldr r0, [r5]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r6, #0
	bl sub_0200C750
	ldr r0, [r5]
	mov r1, #1
	bl sub_0200C644
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0225D800
MOD11_0225D800: ; 0x0225D800
	push {r3, lr}
	mov r3, #3
	lsl r3, r3, #0x12
	bl MOD11_0225D7D0
	pop {r3, pc}

	thumb_func_start MOD11_0225D80C
MOD11_0225D80C: ; 0x0225D80C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #0
	bl sub_0200C644
	add r0, r4, #0
	bl MOD11_0225D98C
	pop {r4, pc}

	thumb_func_start MOD11_0225D820
MOD11_0225D820: ; 0x0225D820
	strh r1, [r0, #0x18]
	bx lr

	thumb_func_start MOD11_0225D824
MOD11_0225D824: ; 0x0225D824
	ldrb r0, [r0, #0x1b]
	bx lr

	thumb_func_start MOD11_0225D828
MOD11_0225D828: ; 0x0225D828
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldrb r0, [r4, #0x1b]
	cmp r0, #1
	bne _0225D836
	mov r0, #0
	strb r0, [r4, #0x1b]
_0225D836:
	mov r0, #0x18
	ldrsh r1, [r4, r0]
	cmp r1, #0
	ble _0225D84C
	sub r1, r1, #1
	strh r1, [r4, #0x18]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bne _0225D84C
	mov r0, #1
	strb r0, [r4, #0x1a]
_0225D84C:
	ldr r0, [r4]
	bl sub_0200C658
	cmp r0, #0
	bne _0225D858
	b _0225D984
_0225D858:
	ldrb r0, [r4, #0x1c]
	cmp r0, #0
	bne _0225D8DA
	mov r1, #0xfa
	ldr r2, [r4, #0x10]
	lsl r1, r1, #2
	add r2, r2, r1
	add r0, r4, #0
	ldr r1, _0225D988 ; =0x00004650
	add r0, #0x10
	str r2, [r4, #0x10]
	cmp r2, r1
	blt _0225D886
	ldr r2, [r0]
	sub r1, r2, r1
	str r1, [r0]
	ldrb r0, [r4, #0x1a]
	cmp r0, #1
	bne _0225D886
	mov r0, #1
	strb r0, [r4, #0x1c]
	mov r0, #0
	strb r0, [r4, #0x1a]
_0225D886:
	ldrb r0, [r4, #0x1c]
	cmp r0, #0
	bne _0225D8DA
	ldr r0, [r4, #0x10]
	mov r1, #0x64
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl Sin
	mov r2, #0xe
	asr r1, r0, #0x1f
	lsl r2, r2, #0xc
	mov r3, #0
	bl _ll_mul
	add r5, r1, #0
	ldr r1, [r4, #8]
	mov r2, #2
	add r6, r0, #0
	lsl r1, r1, #0x10
	mov r7, #0
	lsl r2, r2, #0xa
	asr r1, r1, #0x10
	add r2, r6, r2
	adc r5, r7
	lsl r5, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r5
	asr r5, r2, #0xb
	lsr r5, r5, #0x14
	add r5, r2, r5
	ldr r3, [r4, #0xc]
	asr r2, r5, #0xc
	sub r2, r3, r2
	lsl r2, r2, #0x10
	ldr r0, [r4]
	ldr r3, [r4, #0x14]
	asr r2, r2, #0x10
	bl sub_0200C750
_0225D8DA:
	ldrb r0, [r4, #0x1c]
	cmp r0, #1
	bne _0225D97E
	ldrb r0, [r4, #0x1d]
	cmp r0, #3
	bhi _0225D97E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225D8F2: ; jump table
	.short _0225D8FA - _0225D8F2 - 2 ; case 0
	.short _0225D912 - _0225D8F2 - 2 ; case 1
	.short _0225D934 - _0225D8F2 - 2 ; case 2
	.short _0225D962 - _0225D8F2 - 2 ; case 3
_0225D8FA:
	ldrb r0, [r4, #0x1e]
	add r0, r0, #1
	strb r0, [r4, #0x1e]
	ldrb r0, [r4, #0x1e]
	cmp r0, #3
	bls _0225D97E
	mov r0, #0
	strb r0, [r4, #0x1e]
	ldrb r0, [r4, #0x1d]
	add r0, r0, #1
	strb r0, [r4, #0x1d]
	b _0225D97E
_0225D912:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #8]
	add r2, #8
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4]
	ldr r3, [r4, #0x14]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl sub_0200C750
	mov r0, #1
	strb r0, [r4, #0x1b]
	ldrb r0, [r4, #0x1d]
	add r0, r0, #1
	strb r0, [r4, #0x1d]
	b _0225D97E
_0225D934:
	ldrb r0, [r4, #0x1e]
	add r0, r0, #1
	strb r0, [r4, #0x1e]
	ldrb r0, [r4, #0x1e]
	cmp r0, #2
	bls _0225D97E
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #8]
	add r2, r2, #2
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4]
	ldr r3, [r4, #0x14]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl sub_0200C750
	mov r0, #0
	strb r0, [r4, #0x1e]
	ldrb r0, [r4, #0x1d]
	add r0, r0, #1
	strb r0, [r4, #0x1d]
	b _0225D97E
_0225D962:
	ldrb r0, [r4, #0x1e]
	add r0, r0, #1
	strb r0, [r4, #0x1e]
	ldrb r0, [r4, #0x1e]
	cmp r0, #2
	bls _0225D97E
	add r0, r4, #0
	bl MOD11_0225D80C
	mov r0, #0
	strb r0, [r4, #0x1e]
	ldrb r0, [r4, #0x1d]
	add r0, r0, #1
	strb r0, [r4, #0x1d]
_0225D97E:
	ldr r0, [r4]
	bl sub_0200C5A8
_0225D984:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225D988: .word 0x00004650

	thumb_func_start MOD11_0225D98C
MOD11_0225D98C: ; 0x0225D98C
	mov r1, #0
	str r1, [r0, #0x10]
	strb r1, [r0, #0x1c]
	strb r1, [r0, #0x1d]
	strb r1, [r0, #0x1e]
	bx lr

	.section .rodata

	.global MOD11_0225FEE4
MOD11_0225FEE4: ; 0x0225FEE4
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
