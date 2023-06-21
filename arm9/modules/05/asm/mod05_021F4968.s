	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021F4968
MOD05_021F4968: ; 0x021F4968
	ldr r2, [r1, #0x14]
	ldr r3, _021F4974 ; =sub_02016B44
	add r1, r1, r2
	sub r1, r1, r0
	bx r3
	nop
_021F4974: .word ReallocFromHeap

	thumb_func_start MOD05_021F4978
MOD05_021F4978: ; 0x021F4978
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x23
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #6
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	ldr r1, _021F49A8 ; =0x000008B8
	mov r2, #0
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	str r5, [r0]
	ldr r0, [r4, r1]
	str r6, [r0, #4]
	ldr r0, [r4, r1]
	str r2, [r0, #0xc]
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F49A8: .word 0x000008B8

	thumb_func_start MOD05_021F49AC
MOD05_021F49AC: ; 0x021F49AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x110
	add r5, r0, #0
	ldr r0, _021F4B9C ; =0x000008B8
	mov r1, #0x2a
	ldr r7, [r5, r0]
	sub r0, #8
	ldr r2, [r7]
	add r0, r5, r0
	bl ReadWholeNarcMemberByIdPair
	mov r1, #0x8b
	lsl r1, r1, #4
	ldrh r1, [r5, r1]
	mov r0, #0x2b
	mov r2, #4
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r1, _021F4BA0 ; =0x000008BC
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	ldrh r1, [r0]
	ldr r0, _021F4BA4 ; =0x00000226
	strh r1, [r7, #8]
	cmp r1, r0
	blo _021F49E4
	bl GF_AssertFail
_021F49E4:
	ldr r1, _021F4BA8 ; =0x000008A4
	mov r0, #0
	str r0, [r5, r1]
	add r1, #0xe
	ldrh r1, [r5, r1]
	mov r0, #0x2c
	mov r2, #4
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r1, _021F4BAC ; =0x0000089C
	mov r2, #4
	str r0, [r5, r1]
	add r1, #0x14
	ldrh r1, [r5, r1]
	mov r0, #0x47
	bl AllocAndReadWholeNarcMemberByIdPair
	mov r1, #0x8a
	lsl r1, r1, #4
	str r0, [r5, r1]
	sub r0, r1, #4
	ldr r0, [r5, r0]
	bl NNS_G3dGetTex
	ldr r1, _021F4BA8 ; =0x000008A4
	str r0, [r5, r1]
	ldrh r0, [r7, #8]
	cmp r0, #0
	beq _021F4A2C
	sub r0, r1, #4
	ldr r0, [r5, r0]
	bl NNS_G3dGetTex
	ldr r1, _021F4BB0 ; =0x000008A8
	str r0, [r5, r1]
	b _021F4A32
_021F4A2C:
	mov r2, #0
	add r0, r1, #4
	str r2, [r5, r0]
_021F4A32:
	ldr r0, _021F4BA8 ; =0x000008A4
	ldr r0, [r5, r0]
	bl sub_0201B3C4
	cmp r0, #0
	bne _021F4A42
	bl GF_AssertFail
_021F4A42:
	ldr r1, _021F4BAC ; =0x0000089C
	ldr r0, [r5, r1]
	add r1, #8
	ldr r1, [r5, r1]
	bl MOD05_021F4968
	ldr r0, _021F4BB0 ; =0x000008A8
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021F4A70
	bl sub_0201B3C4
	cmp r0, #0
	bne _021F4A62
	bl GF_AssertFail
_021F4A62:
	mov r1, #0x8a
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #8
	ldr r1, [r5, r1]
	bl MOD05_021F4968
_021F4A70:
	mov r2, #0
	ldr r0, _021F4BA4 ; =0x00000226
	add r3, r5, #0
	add r1, r2, #0
_021F4A78:
	add r2, r2, #1
	str r1, [r3, #4]
	add r3, r3, #4
	cmp r2, r0
	blt _021F4A78
	ldr r0, _021F4BB4 ; =0x000008AC
	str r1, [r5, r0]
	mov r0, #0x28
	mov r1, #4
	bl NARC_New
	str r0, [sp, #0xc]
	ldr r0, [r7, #4]
	bl MOD05_021DA220
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldrh r0, [r7, #8]
	cmp r0, #0
	ble _021F4B10
	ldr r0, [sp, #8]
	str r0, [sp]
_021F4AA6:
	ldr r0, _021F4BA0 ; =0x000008BC
	ldr r1, [r5, r0]
	ldr r0, [sp]
	add r0, r1, r0
	ldrh r6, [r0, #2]
	lsl r0, r6, #2
	add r4, r5, r0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F4ABE
	bl GF_AssertFail
_021F4ABE:
	ldr r0, [sp, #0xc]
	add r1, r6, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	str r0, [r4, #4]
	ldr r0, [sp, #4]
	cmp r6, r0
	bge _021F4AEC
	ldr r0, [r4, #4]
	bl NNS_G3dGetMdlSet
	add r1, r0, #0
	ldrh r2, [r1, #0xe]
	ldr r3, [r7, #4]
	add r0, r6, #0
	add r2, r1, r2
	ldr r2, [r2, #0xc]
	add r1, r1, r2
	ldr r2, _021F4BB0 ; =0x000008A8
	ldr r2, [r5, r2]
	bl MOD05_021D9CEC
_021F4AEC:
	ldr r1, _021F4BB0 ; =0x000008A8
	ldr r0, [r4, #4]
	ldr r1, [r5, r1]
	bl sub_0201B3A8
	cmp r0, #0
	bne _021F4AFE
	bl GF_AssertFail
_021F4AFE:
	ldr r0, [sp]
	ldrh r1, [r7, #8]
	add r0, r0, #2
	str r0, [sp]
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, r1
	blt _021F4AA6
_021F4B10:
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _021F4B46
	ldr r0, [sp, #0xc]
	mov r1, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	str r0, [r5, #4]
	bl NNS_G3dGetTex
	add r4, r0, #0
	beq _021F4B46
	bl sub_0201B3C4
	cmp r0, #0
	bne _021F4B36
	bl GF_AssertFail
_021F4B36:
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl sub_0201B3A8
	cmp r0, #0
	bne _021F4B46
	bl GF_AssertFail
_021F4B46:
	ldr r0, [sp, #0xc]
	bl NARC_Delete
	ldr r2, _021F4BB8 ; =0x04000060
	ldr r0, _021F4BBC ; =0xFFFFCFFF
	ldrh r1, [r2]
	and r1, r0
	mov r0, #0x20
	orr r0, r1
	strh r0, [r2]
	ldr r0, _021F4BC0 ; =0x000008B6
	ldrh r0, [r5, r0]
	cmp r0, #0
	bne _021F4B6A
	ldr r0, _021F4BC4 ; =UNK05_021FC624
	bl G3X_SetEdgeColorTable
	b _021F4B70
_021F4B6A:
	ldr r0, _021F4BC8 ; =UNK05_021FC634
	bl G3X_SetEdgeColorTable
_021F4B70:
	bl MOD05_021DB900
	ldr r1, _021F4BB4 ; =0x000008AC
	str r0, [r5, r1]
	ldr r1, _021F4BCC ; =UNK05_021FD648
	add r0, sp, #0x10
	bl sprintf
	ldr r1, _021F4BB4 ; =0x000008AC
	add r0, sp, #0x10
	ldr r1, [r5, r1]
	bl MOD05_021DB918
	ldr r0, _021F4B9C ; =0x000008B8
	ldr r0, [r5, r0]
	bl FreeToHeap
	ldr r0, _021F4B9C ; =0x000008B8
	mov r1, #0
	str r1, [r5, r0]
	add sp, #0x110
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F4B9C: .word 0x000008B8
_021F4BA0: .word 0x000008BC
_021F4BA4: .word 0x00000226
_021F4BA8: .word 0x000008A4
_021F4BAC: .word 0x0000089C
_021F4BB0: .word 0x000008A8
_021F4BB4: .word 0x000008AC
_021F4BB8: .word 0x04000060
_021F4BBC: .word 0xFFFFCFFF
_021F4BC0: .word 0x000008B6
_021F4BC4: .word UNK05_021FC624
_021F4BC8: .word UNK05_021FC634
_021F4BCC: .word UNK05_021FD648

	thumb_func_start MOD05_021F4BD0
MOD05_021F4BD0: ; 0x021F4BD0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _021F4BDC
	bl GF_AssertFail
_021F4BDC:
	add r2, r4, #4
	lsl r1, r5, #2
	ldr r0, [r2, r1]
	cmp r0, #0
	bne _021F4BF4
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021F4BF0
	bl GF_AssertFail
_021F4BF0:
	add r0, r4, #4
	pop {r3, r4, r5, pc}
_021F4BF4:
	add r0, r2, r1
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F4BF8
MOD05_021F4BF8: ; 0x021F4BF8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r1, [r5]
	ldr r0, _021F4C64 ; =0x000008AC
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021F4C0A
	bl MOD05_021DB9BC
_021F4C0A:
	mov r6, #0
	ldr r7, _021F4C68 ; =0x00000226
	add r4, r6, #0
_021F4C10:
	ldr r0, [r5]
	add r0, r0, r4
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021F4C1E
	bl FreeToHeap
_021F4C1E:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, r7
	blt _021F4C10
	ldr r1, [r5]
	ldr r0, _021F4C6C ; =0x000008BC
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, [r5]
	ldr r0, _021F4C70 ; =0x0000089C
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, [r5]
	ldr r0, _021F4C70 ; =0x0000089C
	mov r2, #0
	str r2, [r1, r0]
	ldr r1, [r5]
	add r0, r0, #4
	ldr r0, [r1, r0]
	bl FreeToHeap
	mov r0, #0x8a
	ldr r1, [r5]
	mov r2, #0
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r0, [r5]
	bl FreeToHeap
	mov r0, #0
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F4C64: .word 0x000008AC
_021F4C68: .word 0x00000226
_021F4C6C: .word 0x000008BC
_021F4C70: .word 0x0000089C

	thumb_func_start MOD05_021F4C74
MOD05_021F4C74: ; 0x021F4C74
	push {r4, lr}
	add r4, r0, #0
	bne _021F4C7E
	bl GF_AssertFail
_021F4C7E:
	ldr r0, _021F4C84 ; =0x000008A4
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4, 0
_021F4C84: .word 0x000008A4

	thumb_func_start MOD05_021F4C88
MOD05_021F4C88: ; 0x021F4C88
	push {r4, lr}
	add r4, r0, #0
	bne _021F4C92
	bl GF_AssertFail
_021F4C92:
	ldr r0, _021F4C98 ; =0x000008A8
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4, 0
_021F4C98: .word 0x000008A8

	thumb_func_start MOD05_021F4C9C
MOD05_021F4C9C: ; 0x021F4C9C
	ldr r1, _021F4CA4 ; =0x000008AC
	ldr r0, [r0, r1]
	bx lr
	nop
_021F4CA4: .word 0x000008AC

	thumb_func_start MOD05_021F4CA8
MOD05_021F4CA8: ; 0x021F4CA8
	ldr r1, _021F4CB8 ; =0x000008B6
	ldrh r0, [r0, r1]
	cmp r0, #0
	beq _021F4CB4
	mov r0, #1
	bx lr
_021F4CB4:
	mov r0, #0
	bx lr
	.balign 4, 0
_021F4CB8: .word 0x000008B6

	thumb_func_start MOD05_021F4CBC
MOD05_021F4CBC: ; 0x021F4CBC
	ldr r1, _021F4CD0 ; =0x000008B6
	ldrh r0, [r0, r1]
	cmp r0, #0
	bne _021F4CC8
	mov r0, #1
	b _021F4CCA
_021F4CC8:
	mov r0, #0
_021F4CCA:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4, 0
_021F4CD0: .word 0x000008B6

	thumb_func_start MOD05_021F4CD4
MOD05_021F4CD4: ; 0x021F4CD4
	ldr r2, _021F4CE0 ; =0x000008BC
	ldr r2, [r0, r2]
	lsl r0, r1, #1
	ldrh r0, [r2, r0]
	bx lr
	nop
_021F4CE0: .word 0x000008BC

	thumb_func_start MOD05_021F4CE4
MOD05_021F4CE4: ; 0x021F4CE4
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021F4CF2
	mov r0, #1
	bx lr
_021F4CF2:
	mov r0, #0
	bx lr
	.balign 4, 0

	.section .rodata

	.global UNK05_021FC624
UNK05_021FC624: ; 0x021FC624
	.byte 0x00, 0x00, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.global UNK05_021FC634
UNK05_021FC634: ; 0x021FC634
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10
	.byte 0x84, 0x10, 0x84, 0x10, 0x84, 0x10, 0x84, 0x10

	.section .data

	.balign 4
	.global UNK05_021FD648
UNK05_021FD648: ; 0x021FD648
	.asciz "fielddata/build_model/build_model_matshp.dat"
