	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F5990
ov05_021F5990: ; 0x021F5990
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r2, #0
	lsl r2, r3, #3
	add r6, r5, r2
	add r6, #0x18
	str r2, [sp, #8]
	add r2, r6, #0
	str r0, [sp]
	add r7, r1, #0
	str r3, [sp, #4]
	bl CreateHeap
	cmp r0, #1
	beq _021F59B2
	bl GF_AssertFail
_021F59B2:
	sub r5, r6, r5
	add r0, r7, #0
	add r1, r5, #0
	bl AllocFromHeap
	add r4, r0, #0
	bne _021F59C4
	bl GF_AssertFail
_021F59C4:
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl memset
	ldr r0, [sp]
	str r0, [r4]
	ldr r0, [sp, #4]
	str r7, [r4, #4]
	str r0, [r4, #8]
	ldr r0, [sp, #8]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x18
	str r0, [r4, #0x14]
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F59EC
ov05_021F59EC: ; 0x021F59EC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r4, [r6, #8]
	ldr r5, [r6, #0x14]
	cmp r4, #0
	beq _021F5A0E
_021F59F8:
	ldr r0, [r5]
	cmp r0, #0
	beq _021F5A06
	ldr r1, [r5, #4]
	add r0, r6, #0
	bl ov05_021F5A74
_021F5A06:
	sub r4, r4, #1
	add r5, #8
	cmp r4, #0
	bne _021F59F8
_021F5A0E:
	ldr r4, [r6, #4]
	add r0, r6, #0
	bl FreeToHeap
	add r0, r4, #0
	bl DestroyHeap
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F5A20
ov05_021F5A20: ; 0x021F5A20
	ldr r3, _021F5A24 ; =ov05_021F5B14
	bx r3
	.balign 4, 0
_021F5A24: .word ov05_021F5B14

	thumb_func_start ov05_021F5A28
ov05_021F5A28: ; 0x021F5A28
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl ov05_021F5B5C
	str r0, [sp]
	cmp r0, #0
	bne _021F5A40
	bl GF_AssertFail
_021F5A40:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl ov05_021F5B14
	add r5, r0, #0
	ldr r0, [sp]
	add r1, r4, #0
	add r2, r5, #0
	bl ov05_021F5B8C
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F5A5C
ov05_021F5A5C: ; 0x021F5A5C
	push {r4, lr}
	add r4, r1, #0
	bl ov05_021F5B74
	cmp r0, #0
	beq _021F5A6C
	bl ov05_021F5B94
_021F5A6C:
	add r0, r4, #0
	bl ov05_021F5B34
	pop {r4, pc}

	thumb_func_start ov05_021F5A74
ov05_021F5A74: ; 0x021F5A74
	push {r4, lr}
	bl ov05_021F5B3C
	add r4, r0, #0
	bne _021F5A82
	bl GF_AssertFail
_021F5A82:
	ldr r0, [r4]
	bl ov05_021F5B34
	add r0, r4, #0
	bl ov05_021F5B94
	pop {r4, pc}

	thumb_func_start ov05_021F5A90
ov05_021F5A90: ; 0x021F5A90
	push {r4, lr}
	bl ov05_021F5B3C
	add r4, r0, #0
	bne _021F5A9E
	bl GF_AssertFail
_021F5A9E:
	ldr r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F5AA4
ov05_021F5AA4: ; 0x021F5AA4
	push {r3, lr}
	bl ov05_021F5B3C
	cmp r0, #0
	beq _021F5AB2
	mov r0, #1
	pop {r3, pc}
_021F5AB2:
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F5AB8
ov05_021F5AB8: ; 0x021F5AB8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r0, #0
	add r7, r3, #0
	add r0, r5, #0
	add r1, r4, #0
	bl NARC_GetMemberSize
	add r1, r0, #0
	add r0, r6, #0
	add r2, r7, #0
	bl ov05_021F5A20
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl NARC_ReadWholeMember
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F5AE4
ov05_021F5AE4: ; 0x021F5AE4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r7, r3, #0
	add r6, r1, #0
	add r0, r4, #0
	add r1, r7, #0
	bl NARC_GetMemberSize
	add r2, r0, #0
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021F5A28
	add r5, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl NARC_ReadWholeMember
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F5B14
ov05_021F5B14: ; 0x021F5B14
	push {r4, lr}
	cmp r2, #0
	ldr r0, [r0, #4]
	bne _021F5B22
	bl AllocFromHeap
	b _021F5B26
_021F5B22:
	bl AllocFromHeapAtEnd
_021F5B26:
	add r4, r0, #0
	cmp r4, #0
	bne _021F5B30
	bl GF_AssertFail
_021F5B30:
	add r0, r4, #0
	pop {r4, pc}

	thumb_func_start ov05_021F5B34
ov05_021F5B34: ; 0x021F5B34
	ldr r3, _021F5B38 ; =FreeToHeap
	bx r3
	.balign 4, 0
_021F5B38: .word FreeToHeap

	thumb_func_start ov05_021F5B3C
ov05_021F5B3C: ; 0x021F5B3C
	ldr r3, [r0, #8]
	ldr r0, [r0, #0x14]
	cmp r3, #0
	beq _021F5B56
_021F5B44:
	ldr r2, [r0]
	cmp r2, #0
	beq _021F5B50
	ldr r2, [r0, #4]
	cmp r2, r1
	beq _021F5B58
_021F5B50:
	add r0, #8
	sub r3, r3, #1
	bne _021F5B44
_021F5B56:
	mov r0, #0
_021F5B58:
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F5B5C
ov05_021F5B5C: ; 0x021F5B5C
	ldr r2, [r0, #8]
	ldr r0, [r0, #0x14]
	cmp r2, #0
	beq _021F5B70
_021F5B64:
	ldr r1, [r0]
	cmp r1, #0
	beq _021F5B72
	add r0, #8
	sub r2, r2, #1
	bne _021F5B64
_021F5B70:
	mov r0, #0
_021F5B72:
	bx lr

	thumb_func_start ov05_021F5B74
ov05_021F5B74: ; 0x021F5B74
	ldr r3, [r0, #8]
	ldr r0, [r0, #0x14]
	cmp r3, #0
	beq _021F5B88
_021F5B7C:
	ldr r2, [r0]
	cmp r2, r1
	beq _021F5B8A
	add r0, #8
	sub r3, r3, #1
	bne _021F5B7C
_021F5B88:
	mov r0, #0
_021F5B8A:
	bx lr

	thumb_func_start ov05_021F5B8C
ov05_021F5B8C: ; 0x021F5B8C
	str r2, [r0]
	str r1, [r0, #4]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F5B94
ov05_021F5B94: ; 0x021F5B94
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	bx lr
