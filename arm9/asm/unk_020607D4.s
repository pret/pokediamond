	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7640
UNK_020F7640: ; 0x020F7640
	.byte 0x1F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_020607D4
FUN_020607D4: ; 0x020607D4
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x80
	add r7, r2, #0x0
	str r3, [sp, #0xc]
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	strb r6, [r4, #0x1]
	strb r7, [r4, #0x4]
	ldr r0, [sp, #0xc]
	add r2, r4, #0x0
	str r0, [r4, #0x18]
	ldr r0, [sp, #0x40]
	add r2, #0x34
	str r0, [r4, #0x1c]
	ldr r0, [sp, #0x44]
	mov r7, #0x9
	str r0, [r4, #0x20]
	ldr r3, [r5, #0x40]
_02060802:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r7, r7, #0x1
	bne _02060802
	mov r7, #0x0
	sub r0, r7, #0x1
	str r0, [r4, #0x10]
	strb r7, [r4, #0x5]
	mov r0, #0x40
	add r1, r7, #0x0
	add r2, r7, #0x0
	str r7, [r4, #0x8]
	bl FUN_0200433C
	cmp r6, #0x3
	bne _0206085C
	mov r0, #0x22
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r1, r0, #0x0
	mov r0, #0x3
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	add r0, sp, #0x18
	mov r2, #0x1
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	sub r3, r2, #0x4
	bl FUN_0204A840
	mov r0, #0x19
	lsl r0, r0, #0x10
	str r0, [sp, #0x10]
	mov r0, #0xe
	lsl r0, r0, #0x10
	mov r7, #0x1
	str r0, [r4, #0x10]
	b _02060892
_0206085C:
	cmp r6, #0x2
	bne _02060892
	ldr r0, _02060918 ; =0x000001C1
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0x0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r1, r0, #0x0
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r2, #0x3
	str r2, [sp, #0x4]
	add r0, sp, #0x18
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	sub r2, r2, #0x5
	mov r3, #0x2
	bl FUN_0204A840
	mov r0, #0x3
	lsl r0, r0, #0x12
	mov r7, #0x1
	str r0, [sp, #0x10]
_02060892:
	cmp r7, #0x0
	beq _02060906
	add r3, r4, #0x0
	ldr r1, [sp, #0x14]
	add r0, r5, #0x0
	add r2, sp, #0x18
	add r3, #0x30
	bl FUN_0204A8C4
	cmp r0, #0x0
	beq _020608F8
	ldr r0, [sp, #0x10]
	add r1, r4, #0x0
	str r0, [r4, #0xc]
	mov r0, #0x0
	str r0, [r4, #0x14]
	strb r0, [r4, #0x3]
	mov r0, #0x1
	lsl r0, r0, #0xa
	str r0, [r4, #0x7c]
	ldr r0, [r5, #0x38]
	add r1, #0x24
	bl FUN_02055350
	ldr r0, [r5, #0x20]
	bl Camera_ClearFixedTarget
	add r0, r4, #0x0
	ldr r1, [r5, #0x20]
	add r0, #0x24
	bl Camera_SetFixedTarget
	mov r0, #0x0
	ldr r1, [r4, #0x10]
	mvn r0, r0
	cmp r1, r0
	beq _020608EC
	mov r0, #0x0
	strb r0, [r4, #0x2]
	mov r0, #0x1
	strb r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02060BDC
	b _020608F0
_020608EC:
	mov r0, #0x0
	strb r0, [r4, #0x0]
_020608F0:
	ldr r0, _0206091C ; =0x000006DD
	bl PlaySE
	b _0206090A
_020608F8:
	bl GF_AssertFail
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x28
	pop {r3-r7, pc}
_02060906:
	mov r0, #0x2
	strb r0, [r4, #0x0]
_0206090A:
	ldr r0, [r5, #0x10]
	ldr r1, _02060920 ; =FUN_020609A0
	add r2, r4, #0x0
	bl FUN_0204640C
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_02060918: .word 0x000001C1
_0206091C: .word 0x000006DD
_02060920: .word FUN_020609A0

	thumb_func_start FUN_02060924
FUN_02060924: ; 0x02060924
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xb
	mov r1, #0x8
	add r6, r2, #0x0
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	str r6, [r2, #0x4]
	strb r4, [r2, #0x0]
	ldr r0, [r5, #0x10]
	ldr r1, _02060944 ; =FUN_02060948
	bl FUN_0204640C
	pop {r4-r6, pc}
	.balign 4
_02060944: .word FUN_02060948

	thumb_func_start FUN_02060948
FUN_02060948: ; 0x02060948
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046530
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02060972
	cmp r0, #0x1
	beq _0206097C
	cmp r0, #0x2
	beq _0206098A
	b _02060994
_02060972:
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0203888C
	b _02060994
_0206097C:
	add r0, r4, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _02060994
	mov r0, #0x0
	pop {r4-r6, pc}
_0206098A:
	add r0, r6, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r4-r6, pc}
_02060994:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020609A0
FUN_020609A0: ; 0x020609A0
	push {r3-r6, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldrb r1, [r4, #0x0]
	cmp r1, #0x7
	bhi _020609E4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020609C6: ; jump table (using 16-bit offset)
	.short _020609D6 - _020609C6 - 2; case 0
	.short _020609EC - _020609C6 - 2; case 1
	.short _02060A4E - _020609C6 - 2; case 2
	.short _02060A74 - _020609C6 - 2; case 3
	.short _02060AB4 - _020609C6 - 2; case 4
	.short _02060AC6 - _020609C6 - 2; case 5
	.short _02060AE2 - _020609C6 - 2; case 6
	.short _02060AF6 - _020609C6 - 2; case 7
_020609D6:
	bl FUN_02060C80
	add r0, r4, #0x0
	bl FUN_02060B0C
	cmp r0, #0x0
	bne _020609E6
_020609E4:
	b _02060B00
_020609E6:
	mov r0, #0x2
	strb r0, [r4, #0x0]
	b _02060B00
_020609EC:
	bl FUN_02060C80
	add r0, r4, #0x0
	bl FUN_02060B0C
	add r6, r0, #0x0
	ldrb r0, [r4, #0x2]
	cmp r0, #0x0
	bne _02060A2C
	add r0, r4, #0x0
	add r1, r4, #0x0
	add r0, #0x10
	add r1, #0x14
	add r2, r4, #0x2
	bl FUN_02060BC8
	cmp r0, #0x0
	beq _02060B00
	ldr r0, [r5, #0x50]
	mov r1, #0x1
	mov r2, #0x0
	bl MOD05_021DA4EC
	ldr r0, [r5, #0x50]
	mov r1, #0x2
	mov r2, #0x0
	bl MOD05_021DA4EC
	ldr r0, _02060B08 ; =0x000006DE
	bl PlaySE
	b _02060B00
_02060A2C:
	ldr r0, [r5, #0x50]
	mov r1, #0x1
	bl MOD05_021DA58C
	cmp r0, #0x0
	beq _02060B00
	ldr r0, [r5, #0x50]
	mov r1, #0x2
	bl MOD05_021DA58C
	cmp r0, #0x0
	beq _02060B00
	cmp r6, #0x0
	beq _02060B00
	mov r0, #0x2
	strb r0, [r4, #0x0]
	b _02060B00
_02060A4E:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0xb
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl BeginNormalPaletteFade
	mov r0, #0x0
	mov r1, #0x6
	bl FUN_020053CC
	mov r0, #0x3
	strb r0, [r4, #0x0]
	b _02060B00
_02060A74:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02060A84
	bl FUN_02005404
	cmp r0, #0x0
	beq _02060A8A
_02060A84:
	add sp, #0xc
	mov r0, #0x0
	pop {r3-r6, pc}
_02060A8A:
	mov r0, #0x0
	ldr r1, [r4, #0x10]
	mvn r0, r0
	cmp r1, r0
	beq _02060AA8
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x1
	bl MOD05_021DA54C
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	mov r2, #0x2
	bl MOD05_021DA54C
_02060AA8:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	mov r0, #0x4
	strb r0, [r4, #0x0]
	b _02060B00
_02060AB4:
	ldrb r1, [r4, #0x1]
	add r2, r4, #0x0
	add r0, r5, #0x0
	add r2, #0x34
	bl FUN_02060924
	mov r0, #0x5
	strb r0, [r4, #0x0]
	b _02060B00
_02060AC6:
	ldr r0, [r4, #0x20]
	mov r2, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	mvn r2, r2
	str r0, [sp, #0x4]
	ldr r1, [r4, #0x18]
	ldr r3, [r4, #0x1c]
	add r0, r6, #0x0
	bl FUN_020491A8
	mov r0, #0x6
	strb r0, [r4, #0x0]
	b _02060B00
_02060AE2:
	ldr r1, [r4, #0x18]
	add r0, r5, #0x0
	bl FUN_0204AD8C
	add r0, r6, #0x0
	bl FUN_0204B0E8
	mov r0, #0x7
	strb r0, [r4, #0x0]
	b _02060B00
_02060AF6:
	bl FreeToHeap
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r6, pc}
_02060B00:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r6, pc}
	nop
_02060B08: .word 0x000006DE

	thumb_func_start FUN_02060B0C
FUN_02060B0C: ; 0x02060B0C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0x30]
	add r0, sp, #0x0
	bl MOD05_021E7EA0
	ldrb r0, [r4, #0x1]
	cmp r0, #0x3
	bhi _02060B7C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02060B2C: ; jump table (using 16-bit offset)
	.short _02060B34 - _02060B2C - 2; case 0
	.short _02060B6A - _02060B2C - 2; case 1
	.short _02060B58 - _02060B2C - 2; case 2
	.short _02060B46 - _02060B2C - 2; case 3
_02060B34:
	ldr r1, [sp, #0x8]
	ldr r0, [r4, #0x7c]
	add r0, r1, r0
	str r0, [sp, #0x8]
	ldr r1, [r4, #0x2c]
	ldr r0, [r4, #0x7c]
	add r0, r1, r0
	str r0, [r4, #0x2c]
	b _02060B86
_02060B46:
	ldr r1, [sp, #0x8]
	ldr r0, [r4, #0x7c]
	sub r0, r1, r0
	str r0, [sp, #0x8]
	ldr r1, [r4, #0x2c]
	ldr r0, [r4, #0x7c]
	sub r0, r1, r0
	str r0, [r4, #0x2c]
	b _02060B86
_02060B58:
	ldr r1, [sp, #0x0]
	ldr r0, [r4, #0x7c]
	add r0, r1, r0
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x24]
	ldr r0, [r4, #0x7c]
	add r0, r1, r0
	str r0, [r4, #0x24]
	b _02060B86
_02060B6A:
	ldr r1, [sp, #0x0]
	ldr r0, [r4, #0x7c]
	sub r0, r1, r0
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x24]
	ldr r0, [r4, #0x7c]
	sub r0, r1, r0
	str r0, [r4, #0x24]
	b _02060B86
_02060B7C:
	bl GF_AssertFail
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r4, pc}
_02060B86:
	mov r0, #0x1
	ldr r1, [r4, #0x7c]
	lsl r0, r0, #0xc
	cmp r1, r0
	bge _02060BA6
	ldrb r1, [r4, #0x3]
	add r1, r1, #0x1
	strb r1, [r4, #0x3]
	ldrb r1, [r4, #0x3]
	cmp r1, #0x18
	blo _02060BA6
	ldr r1, [r4, #0x7c]
	add r0, r1, r0
	str r0, [r4, #0x7c]
	mov r0, #0x0
	strb r0, [r4, #0x3]
_02060BA6:
	ldr r0, [r4, #0x30]
	add r1, sp, #0x0
	bl MOD05_021E7EB0
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #0x7c]
	add r1, r1, r0
	str r1, [r4, #0x14]
	ldr r0, [r4, #0xc]
	cmp r0, r1
	bgt _02060BC2
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r4, pc}
_02060BC2:
	mov r0, #0x0
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_02060BC8
FUN_02060BC8: ; 0x02060BC8
	ldr r3, [r0, #0x0]
	ldr r0, [r1, #0x0]
	cmp r3, r0
	bgt _02060BD6
	mov r0, #0x1
	strb r0, [r2, #0x0]
	bx lr
_02060BD6:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02060BDC
FUN_02060BDC: ; 0x02060BDC
	push {r4-r7, lr}
	sub sp, #0x34
	add r5, r0, #0x0
	ldr r0, _02060C7C ; =UNK_020F7640
	mov r6, #0x0
	ldr r2, [r0, #0x0]
	ldr r1, [r0, #0x4]
	str r2, [sp, #0x2c]
	str r1, [sp, #0x30]
	ldr r1, [r0, #0x8]
	ldr r0, [r0, #0xc]
	str r1, [sp, #0x24]
	str r0, [sp, #0x28]
_02060BF6:
	lsl r7, r6, #0x2
	add r0, sp, #0x2c
	ldr r4, [r0, r7]
	mov r2, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r3, r2, #0x0
	bl FUN_0204A9F0
	cmp r0, #0x0
	beq _02060C6A
	ldr r1, [r5, #0x2c]
	add r0, r4, #0x0
	bl MOD05_021F4BD0
	ldr r0, [r0, #0x0]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r2, sp, #0x20
	mov r3, #0x0
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204A9F0
	cmp r0, #0x0
	bne _02060C38
	bl GF_AssertFail
_02060C38:
	ldr r0, [sp, #0x20]
	bl MOD05_021E7EC8
	str r0, [sp, #0x1c]
	ldr r0, [r5, #0x2c]
	bl MOD05_021F4C88
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x24
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x18]
	ldr r2, [r2, r7]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4c]
	ldr r1, [r5, #0x50]
	add r3, r4, #0x0
	bl MOD05_021DA464
	b _02060C6E
_02060C6A:
	bl GF_AssertFail
_02060C6E:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x2
	blo _02060BF6
	add sp, #0x34
	pop {r4-r7, pc}
	.balign 4
_02060C7C: .word UNK_020F7640

	thumb_func_start FUN_02060C80
FUN_02060C80: ; 0x02060C80
	push {r3, lr}
	ldrb r1, [r0, #0x1]
	cmp r1, #0x2
	beq _02060CA8
	cmp r1, #0x3
	bne _02060CC4
	mov r2, #0x2
	ldr r1, [r0, #0x8]
	lsl r2, r2, #0x10
	cmp r1, r2
	bge _02060CC8
	ldr r3, [r0, #0x24]
	lsr r1, r2, #0x5
	add r1, r3, r1
	str r1, [r0, #0x24]
	ldr r3, [r0, #0x8]
	lsr r1, r2, #0x5
	add r1, r3, r1
	str r1, [r0, #0x8]
	pop {r3, pc}
_02060CA8:
	mov r1, #0x3
	ldr r2, [r0, #0x8]
	lsl r1, r1, #0x10
	cmp r2, r1
	bge _02060CC8
	mov r1, #0x2
	ldr r2, [r0, #0x2c]
	lsl r1, r1, #0xa
	add r2, r2, r1
	str r2, [r0, #0x2c]
	ldr r2, [r0, #0x8]
	add r1, r2, r1
	str r1, [r0, #0x8]
	pop {r3, pc}
_02060CC4:
	bl GF_AssertFail
_02060CC8:
	pop {r3, pc}
	.balign 4
