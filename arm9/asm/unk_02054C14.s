	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F5D14
UNK_020F5D14: ; 0x020F5D14
	.short 0x0179, 0x017A, 0x017B

	.text

	thumb_func_start sub_02054C14
sub_02054C14: ; 0x02054C14
	push {r4, lr}
	mov r1, #0xa
	add r4, r0, #0x0
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C26
	mov r0, #0x1
	pop {r4, pc}
_02054C26:
	add r0, r4, #0x0
	mov r1, #0x64
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C36
	mov r0, #0x2
	pop {r4, pc}
_02054C36:
	mov r1, #0xfa
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C48
	mov r0, #0x3
	pop {r4, pc}
_02054C48:
	ldr r1, _02054C9C ; =0x00002710
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C58
	mov r0, #0x4
	pop {r4, pc}
_02054C58:
	ldr r1, _02054CA0 ; =0x000186A0
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C68
	mov r0, #0x5
	pop {r4, pc}
_02054C68:
	ldr r1, _02054CA4 ; =0x000F4240
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C78
	mov r0, #0x6
	pop {r4, pc}
_02054C78:
	ldr r1, _02054CA8 ; =0x00989680
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C88
	mov r0, #0x7
	pop {r4, pc}
_02054C88:
	ldr r1, _02054CAC ; =0x05F5E100
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r0, #0x0
	bne _02054C98
	mov r0, #0x8
	pop {r4, pc}
_02054C98:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02054C9C: .word 0x00002710
_02054CA0: .word 0x000186A0
_02054CA4: .word 0x000F4240
_02054CA8: .word 0x00989680
_02054CAC: .word 0x05F5E100

	thumb_func_start sub_02054CB0
sub_02054CB0: ; 0x02054CB0
	mov r1, #0x52
	lsl r1, r1, #0x2
	cmp r0, r1
	blo _02054CC2
	add r1, #0x63
	cmp r0, r1
	bhi _02054CC2
	mov r0, #0x1
	bx lr
_02054CC2:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02054CC8
sub_02054CC8: ; 0x02054CC8
	cmp r0, #0xe
	bhi _02054CD0
	mov r0, #0x6
	bx lr
_02054CD0:
	cmp r0, #0x18
	bhi _02054CD8
	mov r0, #0x7
	bx lr
_02054CD8:
	cmp r0, #0x27
	bhi _02054CE0
	mov r0, #0x8
	bx lr
_02054CE0:
	cmp r0, #0x3b
	bhi _02054CE8
	mov r0, #0x9
	bx lr
_02054CE8:
	cmp r0, #0x59
	bhi _02054CF0
	mov r0, #0xa
	bx lr
_02054CF0:
	cmp r0, #0x72
	bhi _02054CF8
	mov r0, #0xb
	bx lr
_02054CF8:
	cmp r0, #0x86
	bhi _02054D00
	mov r0, #0xc
	bx lr
_02054D00:
	cmp r0, #0x90
	bhi _02054D08
	mov r0, #0xd
	bx lr
_02054D08:
	cmp r0, #0x95
	bhi _02054D10
	mov r0, #0xe
	bx lr
_02054D10:
	cmp r1, #0x0
	beq _02054D18
	mov r0, #0x4
	bx lr
_02054D18:
	mov r0, #0x5
	bx lr

	thumb_func_start sub_02054D1C
sub_02054D1C: ; 0x02054D1C
	cmp r0, #0x27
	bhi _02054D24
	mov r0, #0x13
	bx lr
_02054D24:
	cmp r0, #0x3b
	bhi _02054D2C
	mov r0, #0x14
	bx lr
_02054D2C:
	cmp r0, #0x59
	bhi _02054D34
	mov r0, #0x15
	bx lr
_02054D34:
	cmp r0, #0x77
	bhi _02054D3C
	mov r0, #0x16
	bx lr
_02054D3C:
	cmp r0, #0x95
	bhi _02054D44
	mov r0, #0x17
	bx lr
_02054D44:
	cmp r0, #0xbd
	bhi _02054D4C
	mov r0, #0x18
	bx lr
_02054D4C:
	cmp r0, #0xe5
	bhi _02054D54
	mov r0, #0x19
	bx lr
_02054D54:
	ldr r2, _02054DE8 ; =0x0000010D
	cmp r0, r2
	bhi _02054D5E
	mov r0, #0x1a
	bx lr
_02054D5E:
	add r3, r2, #0x0
	add r3, #0x28
	cmp r0, r3
	bhi _02054D6A
	mov r0, #0x1b
	bx lr
_02054D6A:
	add r3, r2, #0x0
	add r3, #0x50
	cmp r0, r3
	bhi _02054D76
	mov r0, #0x1c
	bx lr
_02054D76:
	add r3, r2, #0x0
	add r3, #0x6e
	cmp r0, r3
	bhi _02054D82
	mov r0, #0x1d
	bx lr
_02054D82:
	add r3, r2, #0x0
	add r3, #0x8c
	cmp r0, r3
	bhi _02054D8E
	mov r0, #0x1e
	bx lr
_02054D8E:
	add r3, r2, #0x0
	add r3, #0xa0
	cmp r0, r3
	bhi _02054DA2
	cmp r1, #0x0
	beq _02054D9E
	mov r0, #0x20
	bx lr
_02054D9E:
	mov r0, #0x1f
	bx lr
_02054DA2:
	add r3, r2, #0x0
	add r3, #0xb4
	cmp r0, r3
	bhi _02054DAE
	mov r0, #0x21
	bx lr
_02054DAE:
	add r3, r2, #0x0
	add r3, #0xbe
	cmp r0, r3
	bhi _02054DBA
	mov r0, #0x22
	bx lr
_02054DBA:
	add r3, r2, #0x0
	add r3, #0xc8
	cmp r0, r3
	bhi _02054DC6
	mov r0, #0x23
	bx lr
_02054DC6:
	add r3, r2, #0x0
	add r3, #0xce
	cmp r0, r3
	bhi _02054DD2
	mov r0, #0x24
	bx lr
_02054DD2:
	add r2, #0xd4
	cmp r0, r2
	bhi _02054DDC
	mov r0, #0x25
	bx lr
_02054DDC:
	cmp r1, #0x0
	beq _02054DE4
	mov r0, #0x27
	bx lr
_02054DE4:
	mov r0, #0x26
	bx lr
	.balign 4
_02054DE8: .word 0x0000010D

	thumb_func_start sub_02054DEC
sub_02054DEC: ; 0x02054DEC
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl SaveArray_Party_Get
	bl GetPartyCount
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	ldr r4, _02054E2C ; =0x00000000
	beq _02054E28
	mov r7, #0x4c
_02054E02:
	add r0, r6, #0x0
	bl SaveArray_Party_Get
	add r1, r4, #0x0
	bl Party_GetMonByIndex
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02054E1E
	add r0, r4, #0x0
	pop {r3-r7, pc}
_02054E1E:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r5
	blo _02054E02
_02054E28:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02054E2C: .word 0x00000000

	thumb_func_start Save_PlayerHasAllRegisInParty
Save_PlayerHasAllRegisInParty: ; 0x02054E30
	push {r3-r7, lr}
	sub sp, #0x10
	mov r7, #0x0
	bl SaveArray_Party_Get
	str r0, [sp, #0x0]
	bl GetPartyCount
	add r4, r0, #0x0
	add r6, r7, #0x0
	cmp r4, #0x0
	ble _02054E64
	add r5, sp, #0x4
_02054E4A:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl Party_GetMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x0]
	add r6, r6, #0x1
	add r5, r5, #0x2
	cmp r6, r4
	blt _02054E4A
_02054E64:
	ldr r2, _02054E9C ; =UNK_020F5D14
	mov r6, #0x0
_02054E68:
	mov r1, #0x0
	cmp r4, #0x0
	ble _02054E84
	ldrh r5, [r2, #0x0]
	add r3, sp, #0x4
_02054E72:
	ldrh r0, [r3, #0x0]
	cmp r0, r5
	bne _02054E7C
	add r7, r7, #0x1
	b _02054E84
_02054E7C:
	add r1, r1, #0x1
	add r3, r3, #0x2
	cmp r1, r4
	blt _02054E72
_02054E84:
	add r6, r6, #0x1
	add r2, r2, #0x2
	cmp r6, #0x3
	blt _02054E68
	cmp r7, #0x3
	bne _02054E96
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_02054E96:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02054E9C: .word UNK_020F5D14

	thumb_func_start sub_02054EA0
sub_02054EA0: ; 0x02054EA0
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r0, r4, #0x0
	bl TaskManager_GetEnvironment
	add r4, r0, #0x0
	mov r0, #0x2
	lsl r0, r0, #0xe
	str r0, [sp, #0x0]
	str r0, [sp, #0x8]
	ldrh r0, [r4, #0xe]
	ldr r5, [r4, #0x4]
	bl Sin
	asr r1, r0, #0x1f
	asr r3, r5, #0x1f
	add r2, r5, #0x0
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [sp, #0x0]
	ldrh r0, [r4, #0xe]
	ldr r5, [r4, #0x8]
	bl Sin
	asr r1, r0, #0x1f
	asr r3, r5, #0x1f
	add r2, r5, #0x0
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [sp, #0x8]
	str r3, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r1, sp, #0x0
	bl sub_02058BB4
	ldrh r1, [r4, #0xe]
	ldrh r0, [r4, #0x10]
	add r0, r1, r0
	strh r0, [r4, #0xe]
	mov r0, #0x5a
	ldrh r1, [r4, #0xe]
	lsl r0, r0, #0x2
	cmp r1, r0
	blo _02054F28
	mov r0, #0x0
	strh r0, [r4, #0xe]
	ldrh r0, [r4, #0xc]
	sub r0, r0, #0x1
	strh r0, [r4, #0xc]
_02054F28:
	ldrh r0, [r4, #0xc]
	cmp r0, #0x0
	bne _02054F4A
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0x4]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	add r1, sp, #0x0
	bl sub_02058BB4
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r5, pc}
_02054F4A:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start sub_02054F50
sub_02054F50: ; 0x02054F50
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl TaskManager_GetFieldSystem
	str r0, [sp, #0x0]
	mov r0, #0xb
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x14
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, sp, #0x8
	ldrh r0, [r0, #0x10]
	cmp r0, #0x0
	beq _02054F8A
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _02054F98
_02054F8A:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_02054F98:
	bl _ffix
	str r0, [r4, #0x4]
	add r0, sp, #0x8
	ldrh r0, [r0, #0x14]
	cmp r0, #0x0
	beq _02054FB8
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _02054FC6
_02054FB8:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_02054FC6:
	bl _ffix
	str r0, [r4, #0x8]
	strh r6, [r4, #0xc]
	strh r7, [r4, #0x10]
	ldr r0, [sp, #0x0]
	str r5, [r4, #0x0]
	ldr r0, [r0, #0x10]
	ldr r1, _02054FE0 ; =sub_02054EA0
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r3-r7, pc}
	.balign 4
_02054FE0: .word sub_02054EA0

	thumb_func_start sub_02054FE4
sub_02054FE4: ; 0x02054FE4
	push {r4, lr}
	add r4, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r0, r4, #0x0
	bl TaskManager_GetEnvironment
	add r4, r0, #0x0
	ldrb r1, [r4, #0x9]
	ldr r0, [r4, #0x0]
	bl MapObject_SetVisible
	ldrb r1, [r4, #0x8]
	add r0, r1, #0x1
	strb r0, [r4, #0x8]
	ldrh r0, [r4, #0x6]
	cmp r1, r0
	blt _02055028
	ldrb r1, [r4, #0x9]
	mov r0, #0x1
	eor r0, r1
	strb r0, [r4, #0x9]
	mov r0, #0x0
	strb r0, [r4, #0x8]
	ldrh r1, [r4, #0x4]
	sub r0, r1, #0x1
	strh r0, [r4, #0x4]
	cmp r1, #0x0
	bne _02055028
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r4, pc}
_02055028:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start sub_0205502C
sub_0205502C: ; 0x0205502C
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl TaskManager_GetFieldSystem
	str r0, [sp, #0x0]
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	strh r6, [r4, #0x4]
	strh r7, [r4, #0x6]
	str r5, [r4, #0x0]
	mov r0, #0x0
	strb r0, [r4, #0x9]
	ldr r0, [sp, #0x0]
	ldr r1, _02055064 ; =sub_02054FE4
	ldr r0, [r0, #0x10]
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r3-r7, pc}
	.balign 4
_02055064: .word sub_02054FE4
