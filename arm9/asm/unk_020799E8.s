    .include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020FA60C
UNK_020FA60C: ; 0x020FA60C
	.byte 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x40, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x04
	.byte 0x40, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x04

	.text

	thumb_func_start FUN_020799E8
FUN_020799E8: ; 0x020799E8
	lsl r1, r0, #0x1
	ldr r0, _020799F0 ; =UNK_020FA60C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_020799F0: .word UNK_020FA60C

	thumb_func_start FUN_020799F4
FUN_020799F4: ; 0x020799F4
	push {r3, lr}
	add r2, r0, #0x0
	mul r2, r0
	add r0, r1, #0x0
	mul r0, r1
	add r0, r2, r0
	lsl r0, r0, #0x4
	bl SVC_Sqrt
	lsr r0, r0, #0x2
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02079A0C
FUN_02079A0C: ; 0x02079A0C
	push {r4, lr}
	add r4, r0, #0x0
	mul r0, r2
	bl _u32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _02079A22
	cmp r4, #0x0
	beq _02079A22
	mov r0, #0x1
_02079A22:
	pop {r4, pc}

	thumb_func_start FUN_02079A24
FUN_02079A24: ; 0x02079A24
	push {r4, lr}
	add r4, r0, #0x0
	lsl r0, r1, #0x8
	lsl r4, r4, #0x8
	lsr r1, r0, #0x1
	cmp r4, r1
	bls _02079A36
	mov r0, #0x3
	pop {r4, pc}
_02079A36:
	mov r1, #0x5
	bl _u32_div_f
	cmp r4, r0
	bls _02079A44
	mov r0, #0x2
	pop {r4, pc}
_02079A44:
	cmp r4, #0x0
	beq _02079A4C
	mov r0, #0x1
	b _02079A4E
_02079A4C:
	mov r0, #0x0
_02079A4E:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}

	thumb_func_start FUN_02079A54
FUN_02079A54: ; 0x02079A54
	push {r4, lr}
	add r4, r2, #0x0
	cmp r0, r1
	bne _02079A60
	mov r0, #0x4
	pop {r4, pc}
_02079A60:
	lsl r2, r4, #0x18
	lsr r2, r2, #0x18
	bl FUN_02079A0C
	add r1, r4, #0x0
	bl FUN_02079A24
	pop {r4, pc}

	thumb_func_start FUN_02079A70
FUN_02079A70: ; 0x02079A70
	push {lr}
	sub sp, #0xc
	cmp r0, #0x0
	bne _02079A90
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	mov r0, #0x0
	str r1, [sp, #0x8]
	add r1, r2, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
_02079A90:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r1, [sp, #0x8]
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_02079AAC
FUN_02079AAC: ; 0x02079AAC
	push {r4-r5}
	ldr r3, _02079B5C ; =gMain
	mov r2, #0x0
	ldr r3, [r3, #0x4c]
	mov r5, #0x40
	ldrsh r4, [r0, r2]
	tst r5, r3
	beq _02079ADE
	add r3, r4, #0x1
	strh r3, [r0, #0x0]
	ldrsh r2, [r0, r2]
	cmp r2, r1
	ble _02079ACA
	mov r1, #0x1
	strh r1, [r0, #0x0]
_02079ACA:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079AD8
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079AD8:
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02079ADE:
	mov r5, #0x80
	tst r5, r3
	beq _02079B04
	sub r3, r4, #0x1
	strh r3, [r0, #0x0]
	ldrsh r2, [r0, r2]
	cmp r2, #0x0
	bgt _02079AF0
	strh r1, [r0, #0x0]
_02079AF0:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079AFE
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079AFE:
	mov r0, #0x2
	pop {r4-r5}
	bx lr
_02079B04:
	mov r5, #0x20
	tst r5, r3
	beq _02079B2E
	add r1, r4, #0x0
	sub r1, #0xa
	strh r1, [r0, #0x0]
	ldrsh r1, [r0, r2]
	cmp r1, #0x0
	bgt _02079B1A
	mov r1, #0x1
	strh r1, [r0, #0x0]
_02079B1A:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079B28
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079B28:
	mov r0, #0x2
	pop {r4-r5}
	bx lr
_02079B2E:
	mov r5, #0x10
	tst r3, r5
	beq _02079B56
	add r3, r4, #0x0
	add r3, #0xa
	strh r3, [r0, #0x0]
	ldrsh r2, [r0, r2]
	cmp r2, r1
	ble _02079B42
	strh r1, [r0, #0x0]
_02079B42:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079B50
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079B50:
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02079B56:
	add r0, r2, #0x0
	pop {r4-r5}
	bx lr
	.balign 4
_02079B5C: .word gMain

	thumb_func_start FUN_02079B60
FUN_02079B60: ; 0x02079B60
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r1, #0x0
	add r6, r0, #0x0
	ldr r1, [sp, #0x28]
	add r0, r3, #0x0
	str r2, [sp, #0x4]
	ldr r5, [sp, #0x2c]
	ldr r4, [sp, #0x34]
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl AllocFromHeapAtEnd
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x28]
	add r2, r7, #0x0
	bl NARC_ReadWholeMember
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _02079B9A
	cmp r0, #0x1
	beq _02079BC6
	cmp r0, #0x2
	beq _02079C10
	b _02079C36
_02079B9A:
	add r0, r7, #0x0
	add r1, sp, #0x10
	bl FUN_020B0088
	cmp r4, #0x0
	bne _02079BAE
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02079BAE:
	add r0, sp, #0x18
	ldrh r0, [r0, #0x20]
	lsl r1, r5, #0x18
	lsr r1, r1, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	add r0, r6, #0x0
	ldr r2, [r2, #0x14]
	add r3, r4, #0x0
	bl FUN_02017E14
	b _02079C36
_02079BC6:
	add r0, r7, #0x0
	add r1, sp, #0xc
	bl FUN_020B0180
	cmp r4, #0x0
	bne _02079BDA
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02079BDA:
	lsl r1, r5, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	bl FUN_0201886C
	cmp r0, #0x0
	beq _02079BF8
	ldr r2, [sp, #0xc]
	lsl r1, r5, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	add r2, #0xc
	add r3, r4, #0x0
	bl FUN_02017DFC
_02079BF8:
	add r0, sp, #0x18
	ldrh r0, [r0, #0x20]
	lsl r1, r5, #0x18
	lsr r1, r1, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0xc]
	add r0, r6, #0x0
	add r2, #0xc
	add r3, r4, #0x0
	bl FUN_02017CE8
	b _02079C36
_02079C10:
	add r0, r7, #0x0
	add r1, sp, #0x8
	bl FUN_020B0138
	cmp r4, #0x0
	bne _02079C24
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02079C24:
	ldr r1, [sp, #0x8]
	add r3, sp, #0x18
	lsl r0, r5, #0x18
	ldrh r3, [r3, #0x20]
	ldr r1, [r1, #0xc]
	lsr r0, r0, #0x18
	add r2, r4, #0x0
	bl FUN_02017FB4
_02079C36:
	add r0, r7, #0x0
	bl FreeToHeap
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_02079C40
FUN_02079C40: ; 0x02079C40
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r6, r0, #0x0
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r7, r3, #0x0
	bl GetNarcMemberSizeByIdPair
	add r1, r0, #0x0
	ldr r0, [sp, #0x18]
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl NARC_ReadWholeMember
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_020B0180
	add r0, r4, #0x0
	pop {r3-r7, pc}
