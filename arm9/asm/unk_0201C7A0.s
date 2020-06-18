	.include "asm/macros.inc"
    .include "global.inc"

	.extern gSineTable
	.extern UNK_020FFA38

	.text

	thumb_func_start FUN_0201C7A0
FUN_0201C7A0: ; 0x0201C7A0
	cmp r0, r1
	blt _0201C7A6
	add r0, r1, #0x0
_0201C7A6:
	bx lr

	thumb_func_start FUN_0201C7A8
FUN_0201C7A8: ; 0x0201C7A8
	cmp r0, r1
	bgt _0201C7AE
	add r0, r1, #0x0
_0201C7AE:
	bx lr

	thumb_func_start FUN_0201C7B0
FUN_0201C7B0: ; 0x0201C7B0
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r1, #0x0
	add r1, sp, #0x24
	bl VEC_Normalize
	add r0, r4, #0x0
	add r1, sp, #0x18
	bl VEC_Normalize
	ldr r0, [sp, #0x24]
	ldr r4, [sp, #0x18]
	str r0, [sp, #0x0]
	asr r0, r0, #0x1f
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	asr r6, r4, #0x1f
	str r0, [sp, #0x8]
	asr r0, r0, #0x1f
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x8]
	asr r7, r0, #0x1f
	ldr r3, [sp, #0xc]
	add r1, r7, #0x0
	str r0, [sp, #0x10]
	bl _ll_mul
	str r0, [sp, #0x14]
	add r5, r1, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl _ll_mul
	mov r2, #0x2
	ldr r3, [sp, #0x14]
	lsl r2, r2, #0xa
	add r3, r3, r2
	ldr r2, _0201C874 ; =0x00000000
	adc r5, r2
	lsl r2, r5, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _0201C874 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	add r5, r3, r0
	ldr r0, [sp, #0x10]
	add r1, r7, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl _ll_mul
	add r6, r0, #0x0
	add r4, r1, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r6, r6, r2
	adc r4, r3
	lsl r4, r4, #0x14
	lsr r6, r6, #0xc
	orr r6, r4
	add r4, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r4, #0xc
	orr r1, r0
	sub r0, r6, r1
	cmp r5, #0x0
	bne _0201C86A
	cmp r0, #0x0
	ble _0201C862
	add sp, #0x30
	lsl r0, r2, #0x3
	pop {r3-r7, pc}
_0201C862:
	mov r0, #0x3
	add sp, #0x30
	lsl r0, r0, #0xe
	pop {r3-r7, pc}
_0201C86A:
	add r1, r5, #0x0
	bl FX_Atan2
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0201C874: .word 0x00000000

	thumb_func_start FUN_0201C878
FUN_0201C878: ; 0x0201C878
	push {r0-r3}
	push {r4-r7, lr}
	sub sp, #0x54
	ldr r0, [sp, #0x7c]
	ldr r2, [sp, #0x80]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x94]
	ldr r1, [sp, #0x8c]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x88]
	ldr r4, [sp, #0x70]
	str r0, [sp, #0x10]
	sub r0, r2, r1
	str r0, [sp, #0x14]
	asr r0, r0, #0x1f
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x8]
	asr r0, r0, #0x1f
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x74]
	sub r3, r0, r2
	sub r0, r1, r0
	str r3, [sp, #0x20]
	asr r3, r3, #0x1f
	str r3, [sp, #0x24]
	ldr r3, [sp, #0xc]
	str r0, [sp, #0x2c]
	asr r0, r0, #0x1f
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x10]
	asr r3, r3, #0x1f
	str r3, [sp, #0x28]
	asr r0, r0, #0x1f
	ldr r3, [sp, #0x68]
	str r0, [sp, #0x34]
	asr r0, r4, #0x1f
	str r0, [sp, #0x38]
	sub r2, r2, r3
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r3, [sp, #0x68]
	ldr r2, [sp, #0x74]
	ldr r0, [sp, #0x10]
	sub r2, r3, r2
	ldr r1, [sp, #0x34]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r5, r1, #0x0
	str r0, [sp, #0x3c]
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	add r0, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	str r0, [sp, #0x4c]
	add r0, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	add r3, r7, r2
	adc r6, r1
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	ldr r6, [sp, #0x3c]
	lsl r2, r2, #0xa
	add r2, r6, r2
	adc r5, r1
	mov r6, #0x2
	lsl r5, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r5
	ldr r5, [sp, #0x4c]
	lsl r6, r6, #0xa
	add r5, r5, r6
	adc r0, r1
	lsl r0, r0, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	add r0, r2, r1
	add r0, r3, r0
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x8c]
	ldr r2, [sp, #0x68]
	ldr r0, [sp, #0x10]
	sub r2, r3, r2
	ldr r1, [sp, #0x34]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r3, [sp, #0x68]
	ldr r2, [sp, #0x80]
	ldr r0, [sp, #0xc]
	sub r2, r3, r2
	ldr r1, [sp, #0x28]
	asr r3, r2, #0x1f
	bl _ll_mul
	str r0, [sp, #0x40]
	add r5, r1, #0x0
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	add r0, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	str r0, [sp, #0x50]
	add r0, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	add r3, r7, r2
	adc r6, r1
	lsl r2, r6, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	ldr r6, [sp, #0x40]
	lsl r2, r2, #0xa
	add r2, r6, r2
	adc r5, r1
	mov r6, #0x2
	lsl r5, r5, #0x14
	lsr r2, r2, #0xc
	orr r2, r5
	ldr r5, [sp, #0x50]
	lsl r6, r6, #0xa
	add r5, r5, r6
	adc r0, r1
	lsl r0, r0, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	add r0, r2, r1
	add r0, r3, r0
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x74]
	ldr r2, [sp, #0x68]
	ldr r0, [sp, #0xc]
	sub r2, r3, r2
	ldr r1, [sp, #0x28]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r3, [sp, #0x68]
	ldr r2, [sp, #0x8c]
	ldr r0, [sp, #0x8]
	sub r2, r3, r2
	ldr r1, [sp, #0x1c]
	asr r3, r2, #0x1f
	bl _ll_mul
	add r5, r1, #0x0
	str r0, [sp, #0x44]
	ldr r1, [sp, #0x38]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	add r0, r4, #0x0
	bl _ll_mul
	mov r3, #0x2
	mov r2, #0x0
	lsl r3, r3, #0xa
	add r4, r7, r3
	adc r6, r2
	lsl r3, r6, #0x14
	lsr r4, r4, #0xc
	orr r4, r3
	mov r3, #0x2
	ldr r6, [sp, #0x44]
	lsl r3, r3, #0xa
	add r3, r6, r3
	adc r5, r2
	lsl r5, r5, #0x14
	lsr r3, r3, #0xc
	orr r3, r5
	mov r5, #0x2
	lsl r5, r5, #0xa
	add r5, r0, r5
	adc r1, r2
	lsl r0, r1, #0x14
	lsr r1, r5, #0xc
	orr r1, r0
	add r0, r3, r1
	add r6, r4, r0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x34]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x30]
	bl _ll_mul
	add r7, r0, #0x0
	add r5, r1, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	bl _ll_mul
	str r0, [sp, #0x48]
	add r4, r1, #0x0
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	bl _ll_mul
	mov r12, r0
	mov r0, #0x2
	add r2, r1, #0x0
	mov r1, #0x0
	lsl r0, r0, #0xa
	add r0, r7, r0
	adc r5, r1
	lsl r3, r5, #0x14
	lsr r0, r0, #0xc
	orr r0, r3
	mov r3, #0x2
	ldr r5, [sp, #0x48]
	lsl r3, r3, #0xa
	add r3, r5, r3
	adc r4, r1
	lsl r4, r4, #0x14
	lsr r3, r3, #0xc
	orr r3, r4
	mov r4, #0x2
	lsl r4, r4, #0xa
	mov r5, r12
	add r4, r5, r4
	adc r2, r1
	lsl r2, r2, #0x14
	lsr r4, r4, #0xc
	orr r4, r2
	add r2, r3, r4
	add r0, r0, r2
	bpl _0201CA72
	add sp, #0x54
	add r0, r1, #0x0
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
_0201CA72:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bge _0201CA84
	add sp, #0x54
	add r0, r1, #0x0
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
_0201CA84:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bge _0201CA96
	add sp, #0x54
	add r0, r1, #0x0
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3
_0201CA96:
	cmp r6, #0x0
	blt _0201CA9C
	mov r1, #0x1
_0201CA9C:
	add r0, r1, #0x0
	add sp, #0x54
	pop {r4-r7}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_0201CAA8
FUN_0201CAA8: ; 0x0201CAA8
	push {r4-r5, lr}
	sub sp, #0x24
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	ldr r3, _0201CB1C ; =UNK_020FFA38
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	asr r1, r1, #0x4
	lsl r2, r1, #0x1
	lsl r1, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r5, r0, #0x0
	bl MTX_RotX33_
	ldr r0, [r4, #0x4]
	ldr r3, _0201CB1C ; =UNK_020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #0x4
	lsl r2, r0, #0x1
	lsl r1, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotY33_
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r5, #0x0
	bl MTX_Concat33
	ldr r0, [r4, #0x8]
	ldr r3, _0201CB1C ; =UNK_020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #0x4
	lsl r2, r0, #0x1
	lsl r1, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotZ33_
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r5, #0x0
	bl MTX_Concat33
	add sp, #0x24
	pop {r4-r5, pc}
	nop
_0201CB1C: .word UNK_020FFA38

	thumb_func_start FUN_0201CB20
FUN_0201CB20: ; 0x0201CB20
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r1, #0x0
	add r5, r2, #0x0
	lsl r1, r6, #0x2
	ldr r2, _0201CB78 ; =gSineTable
	add r6, #0x5a
	add r4, r3, #0x0
	lsl r3, r6, #0x2
	ldr r1, [r2, r1]
	ldr r2, [r2, r3]
	add r7, r0, #0x0
	bl MTX_RotX33_
	lsl r1, r5, #0x2
	ldr r3, _0201CB78 ; =gSineTable
	add r5, #0x5a
	lsl r2, r5, #0x2
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotY33_
	add r0, r7, #0x0
	add r1, sp, #0x0
	add r2, r7, #0x0
	bl MTX_Concat33
	lsl r1, r4, #0x2
	ldr r3, _0201CB78 ; =gSineTable
	add r4, #0x5a
	lsl r2, r4, #0x2
	ldr r1, [r3, r1]
	ldr r2, [r3, r2]
	add r0, sp, #0x0
	bl MTX_RotZ33_
	add r0, r7, #0x0
	add r1, sp, #0x0
	add r2, r7, #0x0
	bl MTX_Concat33
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_0201CB78: .word gSineTable

	thumb_func_start FUN_0201CB7C
FUN_0201CB7C: ; 0x0201CB7C
	push {r3-r7, lr}
	asr r0, r0, #0x4
	add r7, r2, #0x0
	lsl r2, r0, #0x1
	add r6, r1, #0x0
	lsl r0, r2, #0x1
	ldr r1, _0201CBE8 ; =UNK_020FFA38
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r1, r0]
	ldrsh r1, [r1, r2]
	add r5, r3, #0x0
	ldr r4, [sp, #0x18]
	bl FX_Div
	add r2, r0, #0x0
	asr r1, r6, #0x1f
	add r0, r6, #0x0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r6, #0x2
	mov r2, #0x0
	lsl r6, r6, #0xa
	add r0, r0, r6
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r3, r0, #0x1f
	lsr r1, r0, #0x13
	lsl r3, r3, #0xd
	orr r3, r1
	lsl r0, r0, #0xd
	add r0, r0, r6
	adc r3, r2
	lsl r1, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0x1f
	asr r3, r7, #0x1f
	add r2, r7, #0x0
	str r0, [r4, #0x0]
	bl _ll_mul
	mov r3, #0x0
	add r2, r6, #0x0
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r5, #0x0]
	pop {r3-r7, pc}
	.balign 4
_0201CBE8: .word UNK_020FFA38
