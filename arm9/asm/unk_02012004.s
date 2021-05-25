    .include "asm/macros.inc"
    .include "global.inc"

	.rodata

	.global UNK_020ED3B0
UNK_020ED3B0: ; 0x020ED3B0
	.word 0x00000147
	.word 0x000001EF

	.global UNK_020ED3B8
UNK_020ED3B8: ; 0x020ED3B8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global UNK_020ED3C8
UNK_020ED3C8: ; 0x020ED3C8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global UNK_020ED3D8
UNK_020ED3D8: ; 0x020ED3D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global UNK_020ED438
UNK_020ED438: ; 0x020ED438
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02012004
FUN_02012004: ; 0x02012004
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r6, [sp, #0x20]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0x24]
	mov r7, #0x0
_02012018:
	ldr r1, [r4, #0x0]
	ldr r0, [sp, #0x4]
	ldr r2, [r5, #0x0]
	add r0, r0, r1
	ldr r1, [sp, #0x0]
	add r1, r1, r2
	add r2, r6, #0x0
	bl memcpy
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x24]
	add r7, r7, #0x1
	add r0, r1, r0
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, r6
	str r0, [r4, #0x0]
	cmp r7, #0x8
	blt _02012018
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02012044
FUN_02012044: ; 0x02012044
	push {r4-r6, lr}
	add r5, r3, #0x0
	bl AllocAndReadWholeNarcMemberByIdPair
	add r4, r0, #0x0
	bne _02012054
	bl GF_AssertFail
_02012054:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl NNS_G2dGetUnpackedCharacterData
	add r6, r0, #0x0
	cmp r5, #0x0
	bne _02012066
	bl GF_AssertFail
_02012066:
	cmp r6, #0x0
	bne _0201206E
	bl GF_AssertFail
_0201206E:
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02012078
FUN_02012078: ; 0x02012078
	push {r4-r7, lr}
	sub sp, #0x2c
	ldr r4, [sp, #0x40]
	str r0, [sp, #0x8]
	add r6, r0, r2
	ldrh r0, [r4, #0x2]
	str r1, [sp, #0xc]
	add r5, r3, #0x0
	cmp r0, r6
	bge _02012090
	bl GF_AssertFail
_02012090:
	ldr r0, [sp, #0xc]
	ldrh r1, [r4, #0x0]
	add r0, r0, r5
	str r0, [sp, #0x14]
	cmp r1, r0
	bge _020120A0
	bl GF_AssertFail
_020120A0:
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x1c]
	ldrh r0, [r4, #0x2]
	lsl r7, r0, #0x2
	ldr r0, [sp, #0xc]
	add r1, r0, #0x0
	mul r1, r7
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x18]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bge _0201210A
_020120CC:
	ldr r4, [sp, #0x8]
	add r0, r4, #0x0
	cmp r0, r6
	bge _020120F8
	ldr r0, [sp, #0x18]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x10]
	add r5, r0, r1
_020120DC:
	str r5, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x28
	add r3, sp, #0x24
	str r7, [sp, #0x4]
	bl FUN_02012004
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _020120DC
_020120F8:
	ldr r0, [sp, #0x18]
	add r0, r0, r7
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	add r1, r0, #0x1
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _020120CC
_0201210A:
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02012110
FUN_02012110: ; 0x02012110
	push {r4-r5}
	sub sp, #0x8
	ldr r2, _02012148 ; =UNK_020ED3B0
	add r1, sp, #0x0
	ldr r3, [r2, #0x0]
	ldr r2, [r2, #0x4]
	str r3, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r2, _0201214C ; =0x000001EF
	mov r5, #0x0
	add r3, r2, #0x0
_02012126:
	ldr r4, [r1, #0x0]
	cmp r4, r3
	beq _02012140
	cmp r4, r0
	bne _02012138
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02012138:
	add r5, r5, #0x1
	add r1, r1, #0x4
	cmp r5, r2
	blt _02012126
_02012140:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r5}
	bx lr
	.balign 4
_02012148: .word UNK_020ED3B0
_0201214C: .word 0x000001EF

	thumb_func_start FUN_02012150
FUN_02012150: ; 0x02012150
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x8]
	add r3, sp, #0x8
	bl FUN_02012044
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x14]
	bl FUN_02008A74
	ldr r0, [sp, #0x34]
	bl FUN_02012110
	ldr r1, [sp, #0x30]
	cmp r1, #0x2
	bne _02012184
	cmp r0, #0x1
	bne _02012184
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x28]
	ldr r0, [r0, #0x14]
	ldr r2, [sp, #0x2c]
	bl FUN_02008904
_02012184:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x18]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x1c]
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x20]
	add r0, r4, #0x0
	bl FUN_02012078
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0201219C
FUN_0201219C: ; 0x0201219C
	push {r4-r7, lr}
	sub sp, #0x24
	add r7, r1, #0x0
	add r5, r2, #0x0
	ldr r2, [sp, #0x3c]
	ldr r1, [sp, #0x40]
	add r6, r0, #0x0
	mul r1, r2
	add r0, r5, #0x0
	lsl r1, r1, #0x5
	str r3, [sp, #0x20]
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [sp, #0x38]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x3c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x40]
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x44]
	str r4, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x50]
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	bl FUN_02012150
	add r0, r4, #0x0
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_020121E8
FUN_020121E8: ; 0x020121E8
	push {r3-r7, lr}
	sub sp, #0x30
	str r3, [sp, #0x8]
	ldr r3, [sp, #0x48]
	str r3, [sp, #0x48]
	mov r3, #0x0
	str r3, [sp, #0x2c]
	bl AllocAndReadWholeNarcMemberByIdPair
	str r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02012204
	bl GF_AssertFail
_02012204:
	ldr r0, [sp, #0x20]
	add r1, sp, #0x2c
	bl NNS_G2dGetUnpackedCharacterData
	cmp r0, #0x0
	bne _02012214
	bl GF_AssertFail
_02012214:
	ldr r1, [sp, #0x4c]
	ldr r0, [sp, #0x8]
	add r6, r0, r1
	ldr r0, [sp, #0x2c]
	ldrh r0, [r0, #0x2]
	cmp r0, r6
	bge _02012226
	bl GF_AssertFail
_02012226:
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x48]
	add r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	ldrh r1, [r0, #0x0]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bge _0201223C
	bl GF_AssertFail
_0201223C:
	ldr r0, [sp, #0x2c]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x1c]
	bl FUN_02008A74
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x2c]
	ldrh r0, [r0, #0x2]
	lsl r7, r0, #0x2
	ldr r0, [sp, #0x48]
	add r1, r0, #0x0
	mul r1, r7
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x14]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	add r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bge _020122AE
_02012270:
	ldr r4, [sp, #0x8]
	add r0, r4, #0x0
	cmp r0, r6
	bge _0201229C
	ldr r0, [sp, #0x14]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0xc]
	add r5, r0, r1
_02012280:
	str r5, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, sp, #0x28
	add r3, sp, #0x24
	str r7, [sp, #0x4]
	bl FUN_02012004
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _02012280
_0201229C:
	ldr r0, [sp, #0x14]
	add r0, r0, r7
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x48]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x48]
	cmp r1, r0
	blt _02012270
_020122AE:
	ldr r0, [sp, #0x20]
	bl FreeToHeap
	add sp, #0x30
	pop {r3-r7, pc}

	thumb_func_start FUN_020122B8
FUN_020122B8: ; 0x020122B8
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r1, #0x0
	add r5, r2, #0x0
	ldr r2, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	add r6, r0, #0x0
	mul r1, r2
	add r0, r5, #0x0
	lsl r1, r1, #0x5
	str r3, [sp, #0x10]
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x30]
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	str r4, [sp, #0xc]
	bl FUN_020121E8
	add r0, r4, #0x0
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_020122F4
FUN_020122F4: ; 0x020122F4
	push {r3-r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x38]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x4]
	str r0, [sp, #0x14]
	add r0, r2, #0x0
	add r7, r0, r1
	ldr r1, [sp, #0x3c]
	add r0, r3, #0x0
	add r0, r0, r1
	add r1, r3, #0x0
	str r3, [sp, #0x8]
	ldr r5, [sp, #0x40]
	str r0, [sp, #0x10]
	cmp r1, r0
	bge _0201236C
	add r0, r3, #0x0
	lsl r0, r0, #0x5
	str r0, [sp, #0xc]
	add r0, r2, #0x0
	lsl r0, r0, #0x5
	str r0, [sp, #0x1c]
_02012328:
	ldr r6, [sp, #0x4]
	add r0, r6, #0x0
	cmp r0, r7
	bge _0201235A
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x1c]
	add r4, r0, r2
_0201233C:
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x14]
	mov r2, #0x20
	add r0, r0, r1
	ldr r1, [sp, #0x18]
	add r1, r1, r4
	bl memcpy
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r0, #0x20
	str r0, [r5, #0x0]
	add r4, #0x20
	cmp r6, r7
	blt _0201233C
_0201235A:
	ldr r0, [sp, #0xc]
	add r0, #0x20
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _02012328
_0201236C:
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02012370
FUN_02012370: ; 0x02012370
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r2, #0x0
	ldr r2, [r4, #0x8]
	str r2, [sp, #0x0]
	ldr r2, [r4, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [sp, #0x20]
	str r3, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r2, [sp, #0x24]
	str r2, [sp, #0x10]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x4]
	bl FUN_020122F4
	add sp, #0x14
	pop {r3-r4, pc}

	thumb_func_start FUN_02012394
FUN_02012394: ; 0x02012394
	push {r4-r7, lr}
	sub sp, #0x7c
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x9c]
	mov r12, r3
	add r5, r2, #0x0
	ldr r6, [sp, #0x94]
	ldr r7, [sp, #0x98]
	ldr r3, _020123FC ; =UNK_020ED3D8
	str r1, [sp, #0x10]
	str r0, [sp, #0x9c]
	add r2, sp, #0x1c
	mov r4, #0xc
_020123AE:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r4, r4, #0x1
	bne _020123AE
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xc]
	add r2, r5, #0x0
	mov r3, r12
	str r7, [sp, #0x8]
	bl FUN_020122B8
	str r0, [sp, #0x14]
	mov r4, #0x0
	add r5, sp, #0x1c
_020123D4:
	ldr r0, [sp, #0x14]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x9c]
	add r2, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r3, sp, #0x18
	bl FUN_02012370
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x6
	blt _020123D4
	ldr r0, [sp, #0x14]
	bl FreeToHeap
	add sp, #0x7c
	pop {r4-r7, pc}
	nop
_020123FC: .word UNK_020ED3D8

	thumb_func_start FUN_02012400
FUN_02012400: ; 0x02012400
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [r3, #0x4]
	str r4, [sp, #0x0]
	ldr r4, [r3, #0x8]
	str r4, [sp, #0x4]
	ldr r4, [r3, #0xc]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x18]
	str r4, [sp, #0xc]
	ldr r3, [r3, #0x0]
	bl FUN_02012394
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012420
FUN_02012420: ; 0x02012420
	push {r4-r7, lr}
	sub sp, #0x14
	ldr r4, _02012448 ; =UNK_020ED3B8
	add r5, r3, #0x0
	add r3, sp, #0x4
	add r7, r0, #0x0
	mov r12, r1
	add r6, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r7, #0x0
	mov r1, r12
	add r3, r6, #0x0
	str r5, [sp, #0x0]
	bl FUN_02012400
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02012448: .word UNK_020ED3B8

	thumb_func_start FUN_0201244C
FUN_0201244C: ; 0x0201244C
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x32
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r0, r7, #0x0
	lsl r1, r1, #0x6
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl FUN_02012420
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02012470
FUN_02012470: ; 0x02012470
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x0
	add r5, r0, #0x0
	bl NNS_G2dGetUnpackedPaletteData
	cmp r0, #0x1
	beq _0201249C
	bl GF_AssertFail
_0201249C:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl MIi_CpuCopy16
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020124B4
FUN_020124B4: ; 0x020124B4
	push {r4-r7, lr}
	sub sp, #0x8c
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xac]
	mov r12, r3
	add r5, r2, #0x0
	ldr r6, [sp, #0xa4]
	ldr r7, [sp, #0xa8]
	ldr r3, _0201252C ; =UNK_020ED438
	str r1, [sp, #0x20]
	str r0, [sp, #0xac]
	add r2, sp, #0x2c
	mov r4, #0xc
_020124CE:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r4, r4, #0x1
	bne _020124CE
	mov r0, #0x0
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xa0]
	ldr r1, [sp, #0x20]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xb0]
	str r7, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0xb4]
	add r2, r5, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xb8]
	mov r3, r12
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xbc]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	bl FUN_0201219C
	str r0, [sp, #0x24]
	mov r4, #0x0
	add r5, sp, #0x2c
_02012504:
	ldr r0, [sp, #0x24]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xac]
	add r2, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r3, sp, #0x28
	bl FUN_02012370
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x6
	blt _02012504
	ldr r0, [sp, #0x24]
	bl FreeToHeap
	add sp, #0x8c
	pop {r4-r7, pc}
	nop
_0201252C: .word UNK_020ED438

	thumb_func_start FUN_02012530
FUN_02012530: ; 0x02012530
	push {r4, lr}
	sub sp, #0x20
	ldr r4, [r3, #0x4]
	str r4, [sp, #0x0]
	ldr r4, [r3, #0x8]
	str r4, [sp, #0x4]
	ldr r4, [r3, #0xc]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x28]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0x10]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x14]
	ldr r4, [sp, #0x34]
	str r4, [sp, #0x18]
	ldr r4, [sp, #0x38]
	str r4, [sp, #0x1c]
	ldr r3, [r3, #0x0]
	bl FUN_020124B4
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012560
FUN_02012560: ; 0x02012560
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r4, _02012598 ; =UNK_020ED3C8
	add r5, r3, #0x0
	add r3, sp, #0x14
	add r7, r0, #0x0
	mov r12, r1
	add r6, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [sp, #0x38]
	str r5, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	mov r1, r12
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r3, r6, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_02012530
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02012598: .word UNK_020ED3C8
