    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020FBB48
UNK_020FBB48: ; 0x020FBB48
	.byte 0x46, 0x00, 0x41, 0x00, 0x42, 0x00, 0x43, 0x00, 0x44, 0x00, 0x45, 0x00

	.global UNK_020FBB54
UNK_020FBB54: ; 0x020FBB54
	.byte 0x47, 0x00, 0x48, 0x00, 0x49, 0x00, 0x4A, 0x00, 0x4B, 0x00, 0x4C, 0x00, 0x4D, 0x00, 0x4E, 0x00
	.byte 0x4F, 0x00, 0x50, 0x00, 0x51, 0x00, 0x52, 0x00, 0x53, 0x00, 0x54, 0x00, 0x55, 0x00, 0x56, 0x00
	.byte 0x57, 0x00, 0x58, 0x00, 0x59, 0x00, 0x5A, 0x00, 0x5B, 0x00, 0x5C, 0x00, 0x5D, 0x00, 0x5E, 0x00
	.byte 0x5F, 0x00, 0x60, 0x00, 0x61, 0x00, 0x62, 0x00, 0x63, 0x00, 0x64, 0x00

	.text

	thumb_func_start FUN_0207FD00
FUN_0207FD00: ; 0x0207FD00
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x3c
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r2, #0x65
	str r7, [r4, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	add r3, r7, #0x0
	bl NewMsgDataFromNarc
	str r0, [r4, #0x4]
	ldr r2, [r4, #0x0]
	mov r0, #0x9
	mov r1, #0x20
	bl FUN_0200AA90
	str r0, [r4, #0x8]
	str r5, [r4, #0xc]
	str r6, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	str r0, [r4, #0x38]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x0]
	bl FUN_020806F4
	cmp r0, #0x14
	bls _0207FD5A
	b _02080090
_0207FD5A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207FD66: ; jump table (using 16-bit offset)
	.short _0207FD90 - _0207FD66 - 2; case 0
	.short _0207FDBC - _0207FD66 - 2; case 1
	.short _0207FDE8 - _0207FD66 - 2; case 2
	.short _0207FE14 - _0207FD66 - 2; case 3
	.short _0207FE40 - _0207FD66 - 2; case 4
	.short _0207FE6C - _0207FD66 - 2; case 5
	.short _0207FE98 - _0207FD66 - 2; case 6
	.short _0207FEC4 - _0207FD66 - 2; case 7
	.short _0207FEF0 - _0207FD66 - 2; case 8
	.short _0207FF1C - _0207FD66 - 2; case 9
	.short _0207FF3E - _0207FD66 - 2; case 10
	.short _0207FF60 - _0207FD66 - 2; case 11
	.short _0207FF82 - _0207FD66 - 2; case 12
	.short _0207FFA4 - _0207FD66 - 2; case 13
	.short _0207FFC6 - _0207FD66 - 2; case 14
	.short _0207FFE8 - _0207FD66 - 2; case 15
	.short _02080014 - _0207FD66 - 2; case 16
	.short _0208002E - _0207FD66 - 2; case 17
	.short _02080046 - _0207FD66 - 2; case 18
	.short _02080060 - _0207FD66 - 2; case 19
	.short _02080078 - _0207FD66 - 2; case 20
_0207FD90:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_02080108
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FDBC:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_02080108
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FDE8:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_02080108
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE14:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE40:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE6C:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x36
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE98:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x37
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FEC4:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x38
	bl FUN_02080108
	mov r0, #0x7
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x8
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FEF0:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x39
	bl FUN_02080108
	mov r0, #0x7
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x8
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FF1C:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3a
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FF3E:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3b
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FF60:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3c
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FF82:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3d
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FFA4:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3e
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FFC6:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3f
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FFE8:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x40
	bl FUN_02080228
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_02080014:
	mov r0, #0x1
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x65
	mov r2, #0x0
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_0208002E:
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x66
	str r2, [r4, #0x1c]
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_02080046:
	mov r0, #0x1
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x67
	mov r2, #0x0
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_02080060:
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x67
	str r2, [r4, #0x1c]
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_02080078:
	mov r0, #0x1
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x68
	mov r2, #0x0
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
_02080090:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02080094
FUN_02080094: ; 0x02080094
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _020800A2
	bl FreeToHeap
_020800A2:
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _020800AC
	bl FreeToHeap
_020800AC:
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	beq _020800B6
	bl FreeToHeap
_020800B6:
	ldr r0, [r4, #0x30]
	cmp r0, #0x0
	beq _020800C0
	bl FreeToHeap
_020800C0:
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020800CA
	bl FreeToHeap
_020800CA:
	ldr r0, [r4, #0x8]
	bl FUN_0200AB18
	ldr r0, [r4, #0x4]
	bl DestroyMsgData
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020800E0
FUN_020800E0: ; 0x020800E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl GetMonNature
	add r4, r0, #0x0
	cmp r4, #0x18
	bgt _02080106
	ldr r1, [r5, #0x0]
	mov r0, #0x48
	bl String_ctor
	str r0, [r5, #0x18]
	add r4, #0x18
	ldr r0, [r5, #0x4]
	ldr r2, [r5, #0x18]
	add r1, r4, #0x0
	bl ReadMsgDataIntoString
_02080106:
	pop {r3-r5, pc}

	thumb_func_start FUN_02080108
FUN_02080108: ; 0x02080108
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x9
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x6
	bl String_ctor
	add r4, r0, #0x0
	mov r0, #0x9
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x6
	bl String_ctor
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x4]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0xc]
	mov r1, #0x94
	mov r2, #0x0
	bl GetMonData
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x95
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x1
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x96
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x2
	ldr r0, [r5, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x9b
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x3
	ldr r0, [r5, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x98
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	ldr r0, [r5, #0xc]
	mov r1, #0x91
	mov r2, #0x0
	bl GetMonData
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x5
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x92
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x93
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x7
	mov r3, #0x2
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x8
	bl FUN_0200B59C
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0x20]
	add r2, r4, #0x0
	bl StringExpandPlaceholders
	add r0, r4, #0x0
	bl String_dtor
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02080228
FUN_02080228: ; 0x02080228
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x12
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	bl String_ctor
	add r5, r0, #0x0
	mov r0, #0x12
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	bl String_ctor
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0xc]
	mov r1, #0x94
	mov r2, #0x0
	bl GetMonData
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	mov r1, #0x95
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_0200B764
	ldr r0, [r4, #0xc]
	mov r1, #0x96
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x2
	ldr r0, [r4, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	mov r1, #0x9b
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x3
	ldr r0, [r4, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	mov r1, #0x79
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0xf
	bhi _020802F8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020802D8: ; jump table (using 16-bit offset)
	.short _020802F8 - _020802D8 - 2; case 0
	.short _02080334 - _020802D8 - 2; case 1
	.short _02080334 - _020802D8 - 2; case 2
	.short _02080334 - _020802D8 - 2; case 3
	.short _0208030C - _020802D8 - 2; case 4
	.short _0208030C - _020802D8 - 2; case 5
	.short _020802F8 - _020802D8 - 2; case 6
	.short _02080320 - _020802D8 - 2; case 7
	.short _02080320 - _020802D8 - 2; case 8
	.short _020802F8 - _020802D8 - 2; case 9
	.short _0208035C - _020802D8 - 2; case 10
	.short _0208035C - _020802D8 - 2; case 11
	.short _020802F8 - _020802D8 - 2; case 12
	.short _020802F8 - _020802D8 - 2; case 13
	.short _020802F8 - _020802D8 - 2; case 14
	.short _02080348 - _020802D8 - 2; case 15
_020802F8:
	mov r0, #0x1
	mov r1, #0x7
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_0208030C:
	mov r0, #0x1
	mov r1, #0x3
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_02080320:
	mov r0, #0x1
	mov r1, #0x4
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_02080334:
	mov r0, #0x1
	mov r1, #0x5
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_02080348:
	mov r0, #0x1
	mov r1, #0x8
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_0208035C:
	mov r0, #0x1
	mov r1, #0x7
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
_0208036E:
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x20]
	add r2, r5, #0x0
	bl StringExpandPlaceholders
	add r0, r5, #0x0
	bl String_dtor
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02080384
FUN_02080384: ; 0x02080384
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	mov r0, #0x5a
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	add r6, r2, #0x0
	bl String_ctor
	add r4, r0, #0x0
	mov r0, #0x5a
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	bl String_ctor
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x4]
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl ReadMsgDataIntoString
	cmp r6, #0x0
	ldr r0, [r5, #0xc]
	bne _02080418
	mov r1, #0x91
	mov r2, #0x0
	bl GetMonData
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x5
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x92
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x93
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x7
	mov r3, #0x2
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x8
	bl FUN_0200B59C
	b _02080478
_02080418:
	mov r1, #0x94
	mov r2, #0x0
	bl GetMonData
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x5
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x95
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x96
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x7
	mov r3, #0x2
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x98
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x8
	bl FUN_0200B59C
_02080478:
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0x20]
	add r2, r4, #0x0
	bl StringExpandPlaceholders
	add r0, r4, #0x0
	bl String_dtor
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0208048C
FUN_0208048C: ; 0x0208048C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	mov r0, #0x48
	bl String_ctor
	str r0, [r4, #0x28]
	ldr r0, [r4, #0xc]
	mov r1, #0x46
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #0x47
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x8]
	ldr r0, [r4, #0xc]
	mov r1, #0x48
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	mov r1, #0x49
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x4a
	mov r2, #0x0
	bl GetMonData
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x4b
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	add r2, r1, #0x0
	bl GetMonData
	mov r1, #0x6
	bl _u32_div_f
	cmp r1, #0x5
	bhi _02080510
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02080504: ; jump table (using 16-bit offset)
	.short _02080510 - _02080504 - 2; case 0
	.short _02080548 - _02080504 - 2; case 1
	.short _0208057E - _02080504 - 2; case 2
	.short _020805B4 - _02080504 - 2; case 3
	.short _020805EA - _02080504 - 2; case 4
	.short _02080620 - _02080504 - 2; case 5
_02080510:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x8]
	add r2, r0, #0x0
	mov r5, #0x0
	cmp r2, r1
	bge _02080520
	mov r5, #0x1
	add r0, r1, #0x0
_02080520:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _0208052A
	mov r5, #0x2
	add r0, r1, #0x0
_0208052A:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _02080534
	mov r5, #0x3
	add r0, r1, #0x0
_02080534:
	cmp r0, r7
	bge _0208053C
	mov r5, #0x4
	add r0, r7, #0x0
_0208053C:
	cmp r0, r6
	blt _02080542
	b _02080654
_02080542:
	mov r5, #0x5
	add r0, r6, #0x0
	b _02080654
_02080548:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	add r2, r0, #0x0
	mov r5, #0x1
	cmp r2, r1
	bge _02080558
	mov r5, #0x2
	add r0, r1, #0x0
_02080558:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _02080562
	mov r5, #0x3
	add r0, r1, #0x0
_02080562:
	cmp r0, r7
	bge _0208056A
	mov r5, #0x4
	add r0, r7, #0x0
_0208056A:
	cmp r0, r6
	bge _02080572
	mov r5, #0x5
	add r0, r6, #0x0
_02080572:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _02080654
	mov r5, #0x0
	add r0, r1, #0x0
	b _02080654
_0208057E:
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	add r2, r0, #0x0
	mov r5, #0x2
	cmp r2, r1
	bge _0208058E
	mov r5, #0x3
	add r0, r1, #0x0
_0208058E:
	cmp r0, r7
	bge _02080596
	mov r5, #0x4
	add r0, r7, #0x0
_02080596:
	cmp r0, r6
	bge _0208059E
	mov r5, #0x5
	add r0, r6, #0x0
_0208059E:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _020805A8
	mov r5, #0x0
	add r0, r1, #0x0
_020805A8:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _02080654
	mov r5, #0x1
	add r0, r1, #0x0
	b _02080654
_020805B4:
	ldr r0, [sp, #0x0]
	mov r5, #0x3
	add r1, r0, #0x0
	cmp r1, r7
	bge _020805C2
	mov r5, #0x4
	add r0, r7, #0x0
_020805C2:
	cmp r0, r6
	bge _020805CA
	mov r5, #0x5
	add r0, r6, #0x0
_020805CA:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _020805D4
	mov r5, #0x0
	add r0, r1, #0x0
_020805D4:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _020805DE
	mov r5, #0x1
	add r0, r1, #0x0
_020805DE:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _02080654
	mov r5, #0x2
	add r0, r1, #0x0
	b _02080654
_020805EA:
	mov r5, #0x4
	add r0, r7, #0x0
	cmp r7, r6
	bge _020805F6
	mov r5, #0x5
	add r0, r6, #0x0
_020805F6:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _02080600
	mov r5, #0x0
	add r0, r1, #0x0
_02080600:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _0208060A
	mov r5, #0x1
	add r0, r1, #0x0
_0208060A:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _02080614
	mov r5, #0x2
	add r0, r1, #0x0
_02080614:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _02080654
	mov r5, #0x3
	add r0, r1, #0x0
	b _02080654
_02080620:
	ldr r1, [sp, #0xc]
	mov r5, #0x5
	add r0, r6, #0x0
	cmp r6, r1
	bge _0208062E
	mov r5, #0x0
	add r0, r1, #0x0
_0208062E:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _02080638
	mov r5, #0x1
	add r0, r1, #0x0
_02080638:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _02080642
	mov r5, #0x2
	add r0, r1, #0x0
_02080642:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _0208064C
	mov r5, #0x3
	add r0, r1, #0x0
_0208064C:
	cmp r0, r7
	bge _02080654
	mov r5, #0x4
	add r0, r7, #0x0
_02080654:
	mov r1, #0x5
	bl _s32_div_f
	mov r2, #0xa
	add r6, r5, #0x0
	mul r6, r2
	ldr r3, _02080674 ; =UNK_020FBB54
	lsl r2, r1, #0x1
	add r1, r3, r6
	ldrh r1, [r2, r1]
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x28]
	bl ReadMsgDataIntoString
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02080674: .word UNK_020FBB54

	thumb_func_start FUN_02080678
FUN_02080678: ; 0x02080678
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x0]
	mov r0, #0x48
	bl String_ctor
	mov r6, #0x0
	str r0, [r5, #0x30]
	add r4, r6, #0x0
_0208068A:
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	bl FUN_02069BC8
	cmp r0, #0x1
	bne _02080698
	add r6, r4, #0x1
_02080698:
	add r4, r4, #0x1
	cmp r4, #0x5
	blt _0208068A
	ldr r1, _020806B0 ; =UNK_020FBB48
	lsl r2, r6, #0x1
	ldrh r1, [r1, r2]
	ldr r0, [r5, #0x4]
	ldr r2, [r5, #0x30]
	bl ReadMsgDataIntoString
	pop {r4-r6, pc}
	nop
_020806B0: .word UNK_020FBB48

	thumb_func_start FUN_020806B4
FUN_020806B4: ; 0x020806B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x9
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	mov r0, #0x12
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x4
	bl String_ctor
	str r0, [r5, #0x38]
	cmp r4, #0x5
	bgt _020806D8
	mov r1, #0x69
	b _020806EA
_020806D8:
	cmp r4, #0xa
	bgt _020806E0
	mov r1, #0x6a
	b _020806EA
_020806E0:
	cmp r4, #0x28
	bgt _020806E8
	mov r1, #0x6b
	b _020806EA
_020806E8:
	mov r1, #0x6c
_020806EA:
	ldr r0, [r5, #0x4]
	ldr r2, [r5, #0x38]
	bl ReadMsgDataIntoString
	pop {r3-r5, pc}

	thumb_func_start FUN_020806F4
FUN_020806F4: ; 0x020806F4
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _02080708
	b _0208084E
_02080708:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02080774
	add r0, r5, #0x0
	mov r1, #0x98
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	mov r0, #0x0
	mov r1, #0x37
	bl FUN_02015CF8
	cmp r6, r0
	bne _02080732
	mov r0, #0xf
	pop {r4-r6, pc}
_02080732:
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	bne _0208074C
	cmp r4, #0x1
	bne _02080748
	mov r0, #0x7
	pop {r4-r6, pc}
_02080748:
	mov r0, #0x8
	pop {r4-r6, pc}
_0208074C:
	add r0, r5, #0x0
	mov r1, #0x98
	mov r2, #0x0
	bl GetMonData
	add r5, r0, #0x0
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	cmp r5, r0
	bne _02080768
	mov r0, #0x2
	pop {r4-r6, pc}
_02080768:
	cmp r4, #0x1
	bne _02080770
	mov r0, #0x0
	pop {r4-r6, pc}
_02080770:
	mov r0, #0x1
	pop {r4-r6, pc}
_02080774:
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	bne _020807D6
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x2
	bl FUN_02015CF8
	cmp r6, r0
	bne _020807A6
	cmp r4, #0x1
	bne _020807A2
	mov r0, #0xd
	pop {r4-r6, pc}
_020807A2:
	mov r0, #0xe
	pop {r4-r6, pc}
_020807A6:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r5, r0, #0x0
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_02015CF8
	cmp r5, r0
	bne _020807CA
	cmp r4, #0x1
	bne _020807C6
	mov r0, #0xb
	pop {r4-r6, pc}
_020807C6:
	mov r0, #0xc
	pop {r4-r6, pc}
_020807CA:
	cmp r4, #0x1
	bne _020807D2
	mov r0, #0x9
	pop {r4-r6, pc}
_020807D2:
	mov r0, #0xa
	pop {r4-r6, pc}
_020807D6:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	cmp r6, r0
	beq _02080836
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02015CF8
	cmp r6, r0
	beq _02080836
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x9
	bl FUN_02015CF8
	cmp r6, r0
	beq _02080836
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r5, r0, #0x0
	mov r0, #0x1
	mov r1, #0xa
	bl FUN_02015CF8
	cmp r5, r0
	bne _02080842
_02080836:
	cmp r4, #0x1
	bne _0208083E
	mov r0, #0x5
	pop {r4-r6, pc}
_0208083E:
	mov r0, #0x6
	pop {r4-r6, pc}
_02080842:
	cmp r4, #0x1
	bne _0208084A
	mov r0, #0x3
	pop {r4-r6, pc}
_0208084A:
	mov r0, #0x4
	pop {r4-r6, pc}
_0208084E:
	cmp r4, #0x1
	bne _02080884
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	bne _02080880
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	add r4, r0, #0x0
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_02015CF8
	cmp r4, r0
	bne _0208087C
	mov r0, #0x14
	pop {r4-r6, pc}
_0208087C:
	mov r0, #0x12
	pop {r4-r6, pc}
_02080880:
	mov r0, #0x10
	pop {r4-r6, pc}
_02080884:
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x1
	bne _02080896
	mov r0, #0x13
	pop {r4-r6, pc}
_02080896:
	mov r0, #0x11
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0208089C
FUN_0208089C: ; 0x0208089C
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	bl FUN_020808AC
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020808AC
FUN_020808AC: ; 0x020808AC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, r3, #0x0
	ldr r6, [sp, #0x18]
	cmp r2, #0x6
	bls _020808BC
	b _02080AE0
_020808BC:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_020808C8: ; jump table (using 16-bit offset)
	.short _020808D6 - _020808C8 - 2; case 0
	.short _0208092A - _020808C8 - 2; case 1
	.short _02080974 - _020808C8 - 2; case 2
	.short _02080994 - _020808C8 - 2; case 3
	.short _020809B0 - _020808C8 - 2; case 4
	.short _02080A38 - _020808C8 - 2; case 5
	.short _02080A58 - _020808C8 - 2; case 6
_020808D6:
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02015CF8
	cmp r5, r0
	ble _020808E4
	mov r5, #0x0
_020808E4:
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	bne _0208090C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	b _0208091E
_0208090C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_02080B30
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02080BA8
_0208091E:
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02080AE4
	pop {r3-r7, pc}
_0208092A:
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	bne _02080958
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	pop {r3-r7, pc}
_02080958:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	pop {r3-r7, pc}
_02080974:
	mov r1, #0x0
	bl FUN_02080BA8
	mov r0, #0x0
	mov r1, #0x37
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	pop {r3-r7, pc}
_02080994:
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_02080B30
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02080AE4
	pop {r3-r7, pc}
_020809B0:
	add r2, r6, #0x0
	bl FUN_0206A9AC
	cmp r0, #0x1
	bne _020809F6
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	bne _020809E2
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	b _02080A30
_020809E2:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_02080B30
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02080BA8
	b _02080A30
_020809F6:
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	bne _02080A1E
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	b _02080A30
_02080A1E:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
_02080A30:
	add r0, r4, #0x0
	bl FUN_02080C28
	pop {r3-r7, pc}
_02080A38:
	mov r1, #0x4c
	mov r2, #0x0
	bl GetBoxMonData
	cmp r0, #0x0
	beq _02080AE0
	mov r0, #0x1
	mov r1, #0x2
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	pop {r3-r7, pc}
_02080A58:
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02015CF8
	cmp r5, r0
	ble _02080A66
	mov r5, #0x0
_02080A66:
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_0206A9AC
	cmp r0, #0x0
	bne _02080ACC
	add r0, r4, #0x0
	mov r1, #0x98
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x97
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x94
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x91
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x95
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x92
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x96
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x93
	add r2, sp, #0x0
	bl SetBoxMonData
_02080ACC:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02080AE4
_02080AE0:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02080AE4
FUN_02080AE4: ; 0x02080AE4
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl PlayerProfile_GetTrainerID
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerGender
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl PlayerProfile_GetPlayerName_NewString
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x7
	add r2, sp, #0x4
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x9c
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x90
	add r2, r4, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	bl String_dtor
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02080B30
FUN_02080B30: ; 0x02080B30
	push {r0-r3}
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, sp, #0x0
	add r4, r2, #0x0
	bl FUN_020126B4
	cmp r4, #0x0
	add r2, sp, #0x24
	bne _02080B76
	add r0, r5, #0x0
	mov r1, #0x97
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x91
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x92
	add r2, sp, #0x4
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x93
	add r2, sp, #0x8
	bl SetBoxMonData
	add sp, #0x10
	pop {r3-r5}
	pop {r3}
	add sp, #0x10
	bx r3
_02080B76:
	add r0, r5, #0x0
	mov r1, #0x98
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x94
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x95
	add r2, sp, #0x4
	bl SetBoxMonData
	add r0, r5, #0x0
	mov r1, #0x96
	add r2, sp, #0x8
	bl SetBoxMonData
	add sp, #0x10
	pop {r3-r5}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4

	thumb_func_start FUN_02080BA8
FUN_02080BA8: ; 0x02080BA8
	push {r3-r4, lr}
	sub sp, #0x4
	mov r2, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	cmp r1, #0x0
	add r2, sp, #0x0
	bne _02080BE0
	mov r1, #0x97
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x91
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x92
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x93
	add r2, sp, #0x0
	bl SetBoxMonData
	add sp, #0x4
	pop {r3-r4, pc}
_02080BE0:
	mov r1, #0x98
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x94
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x95
	add r2, sp, #0x0
	bl SetBoxMonData
	add r0, r4, #0x0
	mov r1, #0x96
	add r2, sp, #0x0
	bl SetBoxMonData
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02080C08
FUN_02080C08: ; 0x02080C08
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetBoxMonData
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x9b
	add r2, sp, #0x0
	bl SetBoxMonData
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02080C28
FUN_02080C28: ; 0x02080C28
	push {r3, lr}
	mov r1, #0x1
	str r1, [sp, #0x0]
	mov r1, #0x6e
	add r2, sp, #0x0
	bl SetBoxMonData
	pop {r3, pc}
