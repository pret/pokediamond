	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_0225D3EC
ov11_0225D3EC: ; 0x0225D3EC
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x1b
	str r0, [sp]
	mov r0, #0x2c
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
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x1b
	mov r3, #0xba
	str r6, [sp, #8]
	bl sub_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x2c]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0xbb
	bl sub_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, [sp, #0x30]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r5, #0
	mov r2, #0x1b
	mov r3, #0xbc
	bl sub_0200C13C
	add sp, #0x18
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0225D45C
ov11_0225D45C: ; 0x0225D45C
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

	thumb_func_start ov11_0225D484
ov11_0225D484: ; 0x0225D484
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r3, #0
	mov ip, r2
	ldr r3, _0225D4FC ; =ov11_0225FEB0
	add r6, r0, #0
	add r7, r1, #0
	add r2, sp, #4
	mov r4, #6
_0225D496:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r4, r4, #1
	bne _0225D496
	ldr r0, [r3]
	mov r1, #0x18
	str r0, [r2]
	ldr r0, [sp, #0x50]
	str r5, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x60]
	str r0, [sp, #0x30]
	mov r0, ip
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x18
	str r0, [sp]
	bl MI_CpuFill8
	ldr r5, [sp]
	mov r4, #0
_0225D4CE:
	add r0, r6, #0
	add r1, r7, #0
	add r2, sp, #4
	bl sub_0200C154
	mov r1, #0
	stmia r5!, {r0}
	bl sub_0200C644
	add r4, r4, #1
	cmp r4, #5
	blt _0225D4CE
	ldr r0, _0225D500 ; =ov11_0225D670
	ldr r1, [sp]
	ldr r2, _0225D504 ; =0x00009C40
	bl sub_0200CA44
	ldr r1, [sp]
	str r0, [r1, #0x14]
	add r0, r1, #0
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225D4FC: .word ov11_0225FEB0
_0225D500: .word ov11_0225D670
_0225D504: .word 0x00009C40

	thumb_func_start ov11_0225D508
ov11_0225D508: ; 0x0225D508
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_0225D510:
	ldr r0, [r5]
	bl sub_0200C3DC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _0225D510
	ldr r0, [r6, #0x14]
	bl sub_0200CAB4
	add r0, r6, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0225D52C
ov11_0225D52C: ; 0x0225D52C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r4, [sp, #0x24]
	add r6, r3, #0
	ldr r0, [r5]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl sub_0200C750
	ldr r2, [sp, #0x10]
	lsl r1, r6, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #4]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl sub_0200C750
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #8]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl sub_0200C750
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #0xc]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	add r3, r4, #0
	bl sub_0200C750
	ldr r0, [r5]
	mov r1, #0
	bl sub_0200C5C0
	ldr r0, [r5, #4]
	mov r1, #1
	bl sub_0200C5C0
	ldr r0, [r5, #8]
	mov r1, #2
	bl sub_0200C5C0
	ldr r0, [r5, #0xc]
	mov r1, #3
	bl sub_0200C5C0
	mov r4, #0
	mov r6, #1
_0225D5A2:
	ldr r0, [r5]
	add r1, r6, #0
	bl sub_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0225D5A2
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0225D5B4
ov11_0225D5B4: ; 0x0225D5B4
	push {r4, lr}
	sub sp, #0x18
	ldr r4, [sp, #0x20]
	str r4, [sp]
	ldr r4, [sp, #0x24]
	str r4, [sp, #4]
	ldr r4, [sp, #0x28]
	str r4, [sp, #8]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x10]
	mov r4, #3
	lsl r4, r4, #0x12
	str r4, [sp, #0x14]
	bl ov11_0225D52C
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_0225D5DC
ov11_0225D5DC: ; 0x0225D5DC
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r2, #0
	str r3, [sp]
	ldr r2, [sp, #0x20]
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r4, [sp, #0xc]
	str r2, [sp, #0x10]
	add r2, r3, #0
	add r3, r4, #0
	bl ov11_0225D5B4
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov11_0225D5FC
ov11_0225D5FC: ; 0x0225D5FC
	push {r4, lr}
	sub sp, #0x18
	add r4, r2, #0
	str r3, [sp]
	ldr r2, [sp, #0x20]
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r4, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r2, [sp, #0x24]
	str r2, [sp, #0x14]
	add r2, r3, #0
	add r3, r4, #0
	bl ov11_0225D52C
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_0225D620
ov11_0225D620: ; 0x0225D620
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r3, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r5, #0x10]
	ldr r3, [sp, #0x10]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl sub_0200C750
	ldr r0, [r5, #0x10]
	add r1, r4, #0
	bl sub_0200C5C0
	ldr r0, [r5, #0x10]
	mov r1, #1
	bl sub_0200C644
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0225D648
ov11_0225D648: ; 0x0225D648
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_0225D650:
	ldr r0, [r5]
	add r1, r6, #0
	bl sub_0200C644
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _0225D650
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0225D664
ov11_0225D664: ; 0x0225D664
	ldr r3, _0225D66C ; =sub_0200C644
	ldr r0, [r0, #0x10]
	mov r1, #0
	bx r3
	.align 2, 0
_0225D66C: .word sub_0200C644

	thumb_func_start ov11_0225D670
ov11_0225D670: ; 0x0225D670
	push {r4, r5, r6, lr}
	add r6, r1, #0
	ldr r0, [r6]
	bl sub_0200C658
	cmp r0, #0
	beq _0225D6A0
	mov r4, #0
	add r5, r6, #0
_0225D682:
	ldr r0, [r5]
	bl sub_0200C5A8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0225D682
	ldr r0, [r6, #0x10]
	bl sub_0200C658
	cmp r0, #1
	bne _0225D6A0
	ldr r0, [r6, #0x10]
	bl sub_0200C5A8
_0225D6A0:
	pop {r4, r5, r6, pc}
	.align 2, 0

	.section .rodata

	.global ov11_0225FEB0
ov11_0225FEB0: ; 0x0225FEB0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
