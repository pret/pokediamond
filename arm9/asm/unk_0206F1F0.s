	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F943C
UNK_020F943C: ; 0x020F943C
	.word ov56_02212084, ov56_02212164, ov56_02212240, SDK_OVERLAY_OVERLAY_56_ID

	.text

	thumb_func_start sub_0206F1F0
sub_0206F1F0: ; 0x0206F1F0
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0xb
	bls _0206F20A
	b _0206F37C
_0206F20A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206F216: ; jump table (using 16-bit offset)
	.short _0206F22E - _0206F216 - 2; case 0
	.short _0206F234 - _0206F216 - 2; case 1
	.short _0206F25A - _0206F216 - 2; case 2
	.short _0206F26C - _0206F216 - 2; case 3
	.short _0206F31A - _0206F216 - 2; case 4
	.short _0206F330 - _0206F216 - 2; case 5
	.short _0206F336 - _0206F216 - 2; case 6
	.short _0206F344 - _0206F216 - 2; case 7
	.short _0206F34A - _0206F216 - 2; case 8
	.short _0206F366 - _0206F216 - 2; case 9
	.short _0206F366 - _0206F216 - 2; case 10
	.short _0206F366 - _0206F216 - 2; case 11
_0206F22E:
	ldr r1, [r5, #0xc]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x0]
_0206F234:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x1
	bne _0206F24C
	ldr r0, [r5, #0xc]
	bl sub_0203384C
	cmp r0, #0x0
	bne _0206F24E
_0206F24C:
	b _0206F380
_0206F24E:
	mov r0, #0xa
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _0206F380
_0206F25A:
	ldr r1, _0206F384 ; =UNK_020F943C
	ldr r2, [r4, #0x0]
	add r0, r6, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206F380
_0206F26C:
	ldr r0, [r5, #0xc]
	bl sub_0203384C
	cmp r0, #0x0
	beq _0206F280
	ldr r0, [r5, #0xc]
	bl SaveArray_Flags_Get
	bl sub_0205F304
_0206F280:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0xa
	bhi _0206F380
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206F294: ; jump table (using 16-bit offset)
	.short _0206F380 - _0206F294 - 2; case 0
	.short _0206F2B8 - _0206F294 - 2; case 1
	.short _0206F2C6 - _0206F294 - 2; case 2
	.short _0206F2AA - _0206F294 - 2; case 3
	.short _0206F2E0 - _0206F294 - 2; case 4
	.short _0206F2EE - _0206F294 - 2; case 5
	.short _0206F2D4 - _0206F294 - 2; case 6
	.short _0206F2FC - _0206F294 - 2; case 7
	.short _0206F30E - _0206F294 - 2; case 8
	.short _0206F314 - _0206F294 - 2; case 9
	.short _0206F302 - _0206F294 - 2; case 10
_0206F2AA:
	mov r0, #0x0
	strb r0, [r4, #0xc]
	mov r0, #0x1
	strb r0, [r4, #0xd]
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _0206F380
_0206F2B8:
	mov r0, #0x32
	strb r0, [r4, #0xc]
	mov r0, #0x1
	strb r0, [r4, #0xd]
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _0206F380
_0206F2C6:
	mov r0, #0x64
	strb r0, [r4, #0xc]
	mov r0, #0x1
	strb r0, [r4, #0xd]
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _0206F380
_0206F2D4:
	mov r0, #0x0
	strb r0, [r4, #0xc]
	strb r0, [r4, #0xd]
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _0206F380
_0206F2E0:
	mov r0, #0x32
	strb r0, [r4, #0xc]
	mov r0, #0x0
	strb r0, [r4, #0xd]
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _0206F380
_0206F2EE:
	mov r0, #0x64
	strb r0, [r4, #0xc]
	mov r0, #0x0
	strb r0, [r4, #0xd]
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _0206F380
_0206F2FC:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _0206F380
_0206F302:
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	mov r0, #0xb
	str r0, [r4, #0x4]
	b _0206F380
_0206F30E:
	mov r0, #0x9
	str r0, [r4, #0x4]
	b _0206F380
_0206F314:
	mov r0, #0x8
	str r0, [r4, #0x4]
	b _0206F380
_0206F31A:
	ldr r1, [r4, #0x0]
	ldrb r2, [r4, #0xc]
	ldrb r3, [r4, #0xd]
	ldr r1, [r1, #0x8]
	add r0, r6, #0x0
	bl sub_020471C0
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206F380
_0206F330:
	mov r0, #0x2
	str r0, [r4, #0x4]
	b _0206F380
_0206F336:
	add r0, r6, #0x0
	bl sub_020383D8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206F380
_0206F344:
	mov r0, #0x2
	str r0, [r4, #0x4]
	b _0206F380
_0206F34A:
	ldr r2, _0206F388 ; =0x00040100
	mov r0, #0x3
	mov r1, #0x36
	bl CreateHeap
	bl sub_02088878 ; Loads overlay 13
	mov r0, #0x36
	bl ov13_02211E60
	mov r0, #0x0
	bl OS_ResetSystem
	b _0206F380
_0206F366:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r4-r6, pc}
_0206F37C:
	mov r0, #0x1
	pop {r4-r6, pc}
_0206F380:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0206F384: .word UNK_020F943C
_0206F388: .word 0x00040100

	thumb_func_start sub_0206F38C
sub_0206F38C: ; 0x0206F38C
	push {r4, lr}
	mov r0, #0xb
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x10
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0xc
	str r0, [r4, #0x0]
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0206F3B8
sub_0206F3B8: ; 0x0206F3B8
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_0206F38C
	add r2, r0, #0x0
	ldr r0, [r2, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x4]
	ldr r1, _0206F3D4 ; =sub_0206F1F0
	add r0, r4, #0x0
	bl TaskManager_Call
	pop {r4, pc}
	nop
_0206F3D4: .word sub_0206F1F0

	thumb_func_start sub_0206F3D8
sub_0206F3D8: ; 0x0206F3D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_0206F38C
	add r2, r0, #0x0
	ldr r0, [r2, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x4]
	ldr r1, _0206F3F8 ; =sub_0206F1F0
	add r0, r5, #0x0
	str r4, [r2, #0x8]
	bl TaskManager_Call
	pop {r3-r5, pc}
	nop
_0206F3F8: .word sub_0206F1F0
