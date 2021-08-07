	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F3C98
MOD05_021F3C98: ; 0x021F3C98
	push {r4, r5, r6, r7}
	add r4, r0, #0
	add r3, r2, #0
	mov r5, #0xc
	add r2, r1, #0
	ldr r0, [r4, #4]
	mul r2, r5
	ldrh r0, [r0, r2]
	ldr r6, [r4, #0x10]
	add r1, r0, #0
	mul r1, r5
	add r7, r6, r1
	ldmia r7!, {r0, r1}
	add r6, r3, #0
	stmia r6!, {r0, r1}
	ldr r0, [r7]
	str r0, [r6]
	ldr r1, [r4, #4]
	ldr r0, [r4, #0x10]
	add r1, r1, r2
	ldrh r1, [r1, #2]
	add r6, r1, #0
	mul r6, r5
	add r7, r0, r6
	add r6, r3, #0
	ldmia r7!, {r0, r1}
	add r6, #0xc
	stmia r6!, {r0, r1}
	ldr r0, [r7]
	add r3, #0x18
	str r0, [r6]
	ldr r1, [r4, #4]
	ldr r0, [r4, #0x10]
	add r1, r1, r2
	ldrh r1, [r1, #4]
	add r2, r1, #0
	mul r2, r5
	add r2, r0, r2
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	pop {r4, r5, r6, r7}
	bx lr

	thumb_func_start MOD05_021F3CF0
MOD05_021F3CF0: ; 0x021F3CF0
	push {r4, r5}
	ldr r3, [r0, #0x14]
	ldr r5, [r0, #4]
	mov r0, #0xc
	add r4, r1, #0
	mul r4, r0
	add r1, r5, r4
	ldrh r1, [r1, #6]
	mul r0, r1
	add r3, r3, r0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	pop {r4, r5}
	bx lr

	thumb_func_start MOD05_021F3D10
MOD05_021F3D10: ; 0x021F3D10
	mov r3, #0
	add r2, r3, #0
	sub r1, r3, #1
_021F3D16:
	str r2, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	add r3, r3, #1
	add r0, #0xc
	cmp r3, #0xa
	blt _021F3D16
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3D28
MOD05_021F3D28: ; 0x021F3D28
	push {r4, r5, r6, r7}
	add r4, r0, #0
	add r0, r2, #0
	mov ip, r3
	cmp r1, #0
	bne _021F3D3A
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
_021F3D3A:
	cmp r1, #1
	bne _021F3D4A
	mov r1, #0
	mov r0, ip
	strh r1, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_021F3D4A:
	sub r5, r1, #1
	lsr r1, r5, #0x1f
	add r1, r5, r1
	mov r3, #0
	asr r6, r1, #1
	mov r7, #0xa
_021F3D56:
	add r1, r6, #0
	mul r1, r7
	add r2, r4, r1
	ldrh r1, [r2, #4]
	ldrh r2, [r2, #2]
	lsl r1, r1, #0x10
	orr r1, r2
	cmp r1, r0
	ble _021F3D84
	sub r1, r5, #1
	cmp r1, r3
	ble _021F3D7A
	add r2, r3, r6
	lsr r1, r2, #0x1f
	add r1, r2, r1
	add r5, r6, #0
	asr r6, r1, #1
	b _021F3D56
_021F3D7A:
	mov r0, ip
	strh r6, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_021F3D84:
	add r1, r3, #1
	cmp r1, r5
	bge _021F3D96
	add r2, r6, r5
	lsr r1, r2, #0x1f
	add r1, r2, r1
	add r3, r6, #0
	asr r6, r1, #1
	b _021F3D56
_021F3D96:
	add r1, r6, #1
	mov r0, ip
	strh r1, [r0]
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021F3DA4
MOD05_021F3DA4: ; 0x021F3DA4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x110
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x128]
	add r4, r3, #0
	str r0, [sp, #0x128]
	ldr r0, [r4, #0x1c]
	add r6, r1, #0
	add r7, r2, #0
	cmp r0, #0
	bne _021F3DC0
	add sp, #0x110
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3DC0:
	mov r5, #0
	add r0, sp, #0x98
	str r6, [sp, #0x68]
	str r5, [sp, #0x6c]
	str r7, [sp, #0x70]
	bl MOD05_021F3D10
	ldr r1, [r4]
	ldr r0, [r1, #4]
	sub r0, r6, r0
	bpl _021F3DD8
	add r0, r5, #0
_021F3DD8:
	ldr r2, [r1, #8]
	sub r7, r7, r2
	bpl _021F3DE0
	mov r7, #0
_021F3DE0:
	ldr r1, [r1, #0x14]
	bl FX_Div
	ldr r1, [r4]
	asr r6, r0, #0xc
	ldrh r0, [r1]
	cmp r6, r0
	blo _021F3DF2
	sub r6, r0, #1
_021F3DF2:
	ldr r1, [r1, #0x18]
	add r0, r7, #0
	bl FX_Div
	asr r1, r0, #0xc
	ldr r0, [r4]
	ldrh r0, [r0, #2]
	cmp r1, r0
	blo _021F3E06
	sub r1, r0, #1
_021F3E06:
	mul r0, r1
	add r0, r6, r0
	lsl r2, r0, #2
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r3, r1, r2
	ldrh r6, [r3, #2]
	ldrh r1, [r1, r2]
	lsl r3, r6, #2
	add r3, r6, r3
	lsl r3, r3, #1
	add r6, r0, r3
	ldr r0, [sp, #0x70]
	add r3, sp, #0x58
	str r0, [sp, #0x28]
	ldr r2, [sp, #0x28]
	add r0, r6, #0
	bl MOD05_021F3D28
	cmp r0, #0
	bne _021F3E36
	add sp, #0x110
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3E36:
	add r0, sp, #0x58
	ldrh r1, [r0]
	lsl r0, r1, #2
	add r1, r1, r0
	lsl r0, r1, #1
	ldrh r0, [r6, r0]
	str r0, [sp, #0x44]
	add r0, r1, #4
	lsl r0, r0, #1
	add r1, r1, #3
	ldrh r0, [r6, r0]
	lsl r1, r1, #1
	ldrh r1, [r6, r1]
	lsl r0, r0, #0x10
	orr r1, r0
	mov r0, #0
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x44]
	cmp r0, #0
	bls _021F3F50
	add r0, sp, #0x98
	str r0, [sp, #0x40]
	lsl r0, r1, #1
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x28]
	asr r0, r0, #0x1f
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x68]
	str r0, [sp, #0x2c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x30]
	mov r0, sp
	str r0, [sp, #0x4c]
	sub r0, r0, #4
	str r0, [sp, #0x4c]
_021F3E7C:
	ldr r0, [sp, #0x48]
	ldr r2, [r4, #0x18]
	lsl r1, r0, #1
	ldr r0, [sp, #0x3c]
	add r0, r0, r2
	ldrh r7, [r1, r0]
	add r0, r4, #0
	add r2, sp, #0x74
	add r1, r7, #0
	bl MOD05_021F3C98
	mov r0, #0
	add r3, sp, #0x80
	str r0, [sp, #0x78]
	str r0, [sp, #0x84]
	str r0, [sp, #0x90]
	ldmia r3!, {r0, r1}
	add r2, sp, #8
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #0x8c
	str r0, [r2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x14
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r3, sp, #0x74
	str r0, [r2]
	ldr r2, [sp, #0x4c]
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r6, sp, #0x68
	str r0, [r2]
	ldr r0, [sp, #0x4c]
	ldr r3, [r0]
	ldmia r6!, {r0, r1, r2}
	bl FUN_0201C878
	cmp r0, #1
	bne _021F3F40
	add r0, r4, #0
	add r1, r7, #0
	add r2, sp, #0x5c
	bl MOD05_021F3CF0
	ldr r0, [sp, #0x5c]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	asr r1, r0, #0x1f
	bl _ll_mul
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x64]
	add r6, r1, #0
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x38]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov ip, r0
	mov r2, #0xc
	ldr r0, [r4, #4]
	mul r2, r7
	add r0, r0, r2
	mov r2, #2
	ldr r3, [sp, #0x50]
	lsl r2, r2, #0xa
	add r3, r3, r2
	ldr r2, _021F3FDC ; =0x00000000
	ldr r0, [r0, #8]
	adc r6, r2
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #2
	lsl r2, r2, #0xa
	mov r6, ip
	add r2, r6, r2
	ldr r6, _021F3FDC ; =0x00000000
	adc r1, r6
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	add r1, r3, r2
	add r0, r0, r1
	ldr r1, [sp, #0x60]
	neg r0, r0
	bl FX_Div
	ldr r1, [sp, #0x40]
	add r5, r5, #1
	str r0, [r1]
	add r0, r1, #0
	add r0, #0xc
	str r0, [sp, #0x40]
	cmp r5, #0xa
	bge _021F3F50
_021F3F40:
	ldr r0, [sp, #0x48]
	add r0, r0, #1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	str r1, [sp, #0x48]
	ldr r0, [sp, #0x44]
	cmp r1, r0
	blo _021F3E7C
_021F3F50:
	cmp r5, #1
	ble _021F3FB8
	mov r0, #0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x98]
	bl FUN_0201C7A8
	add r4, r0, #0
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x98]
	bl FUN_0201C7A0
	sub r6, r4, r0
	mov r4, #1
	cmp r5, #1
	ble _021F3FA4
_021F3F72:
	mov r0, #0xc
	add r7, r4, #0
	mul r7, r0
	add r1, sp, #0x98
	ldr r0, [sp, #0x20]
	ldr r1, [r1, r7]
	bl FUN_0201C7A8
	add r1, sp, #0x98
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x20]
	ldr r1, [r1, r7]
	bl FUN_0201C7A0
	ldr r1, [sp, #0x54]
	sub r0, r1, r0
	cmp r6, r0
	ble _021F3F9A
	add r6, r0, #0
	str r4, [sp, #0x24]
_021F3F9A:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r5
	blt _021F3F72
_021F3FA4:
	ldr r0, [sp, #0x24]
	mov r1, #0xc
	mul r1, r0
	add r0, sp, #0x98
	ldr r1, [r0, r1]
	ldr r0, [sp, #0x128]
	add sp, #0x110
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3FB8:
	bne _021F3FC6
	ldr r1, [sp, #0x98]
	ldr r0, [sp, #0x128]
	add sp, #0x110
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3FC6:
	cmp r5, #0
	beq _021F3FD6
	ldr r1, [sp, #0x98]
	ldr r0, [sp, #0x128]
	add sp, #0x110
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F3FD6:
	mov r0, #0
	add sp, #0x110
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F3FDC: .word 0x00000000
