	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F0318
MOD05_021F0318: ; 0x021F0318
	push {r4, r5, r6, r7, lr}
	sub sp, #0x6c
	add r4, r3, #0
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #0
	str r0, [sp, #0x58]
	ldr r1, [r4, #0x50]
	add r0, sp, #0x60
	add r6, r2, #0
	bl Camera_GetLookAtCamTarget
	ldr r3, _021F0434 ; =UNK05_021F8B6C
	add r2, sp, #0xc
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	cmp r6, #0x60
	str r0, [r2]
	bhs _021F0352
	mov r1, #0x60
	sub r0, r1, r6
	lsl r0, r0, #0x18
	ldrh r2, [r4]
	lsr r0, r0, #0x18
	mul r0, r2
	bl _s32_div_f
	b _021F036C
_021F0352:
	sub r6, #0x60
	lsl r0, r6, #0x18
	ldrh r1, [r4]
	lsr r0, r0, #0x18
	mul r0, r1
	mov r1, #0x60
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0
	mvn r0, r0
	mul r0, r1
_021F036C:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	cmp r5, #0x80
	bhs _021F038A
	mov r2, #0x80
	sub r2, r2, r5
	lsl r2, r2, #0x18
	ldrh r0, [r4, #2]
	lsr r2, r2, #0x18
	mul r2, r0
	asr r0, r2, #6
	lsr r0, r0, #0x19
	add r0, r2, r0
	lsl r0, r0, #9
	b _021F03A8
_021F038A:
	ldrh r2, [r4, #2]
	sub r5, #0x80
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	add r3, r2, #0
	mul r3, r0
	asr r0, r3, #6
	lsr r0, r0, #0x19
	add r0, r3, r0
	lsl r0, r0, #9
	lsr r2, r0, #0x10
	mov r0, #0
	mvn r0, r0
	mul r0, r2
	lsl r0, r0, #0x10
_021F03A8:
	lsr r5, r0, #0x10
	asr r0, r1, #4
	lsl r3, r0, #1
	lsl r1, r3, #1
	ldr r2, _021F0438 ; =FX_SinCosTable_
	add r3, r3, #1
	lsl r3, r3, #1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r3]
	add r0, sp, #0x24
	bl MTX_RotX43_
	add r0, sp, #0xc
	add r1, sp, #0x24
	add r2, sp, #0x18
	bl MTX_MultVec43
	asr r0, r5, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	ldr r3, _021F0438 ; =FX_SinCosTable_
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0x24
	bl MTX_RotY43_
	add r0, sp, #0x18
	add r1, sp, #0x24
	add r2, r0, #0
	bl MTX_MultVec43
	add r0, sp, #0x18
	add r1, r4, #0
	add r1, #0x20
	add r2, r0, #0
	bl MTX_MultVec43
	add r0, r4, #0
	add r0, #0x10
	add r1, sp, #0x18
	bl VEC_DotProduct
	add r1, r0, #0
	ldr r0, [r4, #0x1c]
	bl FX_Div
	neg r0, r0
	add r1, sp, #0x18
	add r2, r4, #4
	add r3, sp, #0
	bl VEC_MultAdd
	ldr r1, [sp, #0x60]
	ldr r0, [sp]
	add r2, sp, #0x54
	add r0, r1, r0
	str r0, [sp, #0x54]
	ldr r1, [sp, #0x68]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #0x5c]
	ldmia r2!, {r0, r1}
	stmia r7!, {r0, r1}
	ldr r0, [r2]
	str r0, [r7]
	add sp, #0x6c
	pop {r4, r5, r6, r7, pc}
	nop
_021F0434: .word UNK05_021F8B6C
_021F0438: .word FX_SinCosTable_

	thumb_func_start MOD05_021F043C
MOD05_021F043C: ; 0x021F043C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x60
	bl AllocFromHeap
	add r1, r5, #0
	add r4, r0, #0
	bl MOD05_021F0454
	add r0, r4, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0454
MOD05_021F0454: ; 0x021F0454
	push {r4, r5, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	bl Camera_GetAngle
	add r0, r4, #0
	bl Camera_GetPerspectiveAngle
	strh r0, [r5]
	ldrh r0, [r5]
	ldr r2, _021F04F0 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r1, r0, #1
	lsl r0, r1, #1
	add r1, r1, #1
	lsl r1, r1, #1
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bl FX_Div
	lsl r0, r0, #2
	mov r1, #3
	bl _s32_div_f
	bl FX_Atan
	ldr r3, _021F04F4 ; =UNK05_021F8B78
	strh r0, [r5, #2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x20
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r4, #0
	str r0, [r2]
	add r0, sp, #0x14
	bl Camera_GetLookAtCamPos
	add r0, sp, #8
	add r1, r4, #0
	bl Camera_GetLookAtCamTarget
	add r0, sp, #0x14
	add r1, sp, #8
	add r2, r5, #4
	bl VEC_Subtract
	add r3, sp, #0x20
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r5, #4
	str r0, [r2]
	add r0, sp, #0x20
	bl VEC_DotProduct
	str r0, [r5, #0x1c]
	add r0, sp, #0
	ldrh r0, [r0]
	ldr r3, _021F04F0 ; =FX_SinCosTable_
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	add r0, r5, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, #0x20
	bl MTX_RotX43_
	str r4, [r5, #0x50]
	add sp, #0x2c
	pop {r4, r5, pc}
	nop
_021F04F0: .word FX_SinCosTable_
_021F04F4: .word UNK05_021F8B78

	thumb_func_start MOD05_021F04F8
MOD05_021F04F8: ; 0x021F04F8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F0512
	bne _021F0508
	bl GF_AssertFail
_021F0508:
	ldr r0, [r4]
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
_021F0512:
	pop {r4, pc}

	.section .rodata

	.global UNK05_021F8B6C
UNK05_021F8B6C: ; 0x021F8B6C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF

	.global UNK05_021F8B78
UNK05_021F8B78: ; 0x021F8B78
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
