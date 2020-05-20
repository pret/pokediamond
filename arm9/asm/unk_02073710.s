    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F998C
	.extern UNK_020F9C84
	.extern UNK_020F9964
	.extern UNK_020F98D8
	.extern UNK_020F993C
	.extern UNK_020F98F4
	.extern UNK_020F98C4
	.extern UNK_020F9914

	.text

	thumb_func_start FUN_02073710
FUN_02073710: ; 0x02073710
	push {r3-r7, lr}
	sub sp, #0x50
	add r4, r0, #0x0
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E74C
	mov r0, #0x20
	mov r1, #0xc
	bl FUN_0201C24C
	mov r0, #0xc
	bl FUN_0200BB14
	ldr r1, _020737BC ; =0x000005A8
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl FUN_0200BB34
	ldr r7, _020737C0 ; =0x000005AC
	add r2, sp, #0x30
	ldr r3, _020737C4 ; =UNK_020F98F4
	str r0, [r4, r7]
	ldmia r3!, {r0-r1}
	add r6, r2, #0x0
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	ldr r5, _020737C8 ; =UNK_020F98C4
	stmia r2!, {r0-r1}
	add r3, sp, #0x1c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [r3, #0x0]
	sub r0, r7, #0x4
	ldr r0, [r4, r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	sub r1, r7, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	mov r2, #0x23
	bl FUN_0200BBF0
	sub r0, r7, #0x4
	ldr r0, [r4, r0]
	bl FUN_0200BB68
	mov r2, #0x1
	mov r1, #0x0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	ldr r5, _020737CC ; =UNK_020F98D8
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	sub r1, r7, #0x4
	str r0, [r3, #0x0]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	bl FUN_0200BD20
	add sp, #0x50
	pop {r3-r7, pc}
	.balign 4
_020737BC: .word 0x000005A8
_020737C0: .word 0x000005AC
_020737C4: .word UNK_020F98F4
_020737C8: .word UNK_020F98C4
_020737CC: .word UNK_020F98D8

	thumb_func_start FUN_020737D0
FUN_020737D0: ; 0x020737D0
	push {r4-r7, lr}
	sub sp, #0x3c
	add r5, r0, #0x0
	ldr r0, _02073878 ; =0x000005A4
	str r3, [sp, #0x8]
	ldr r0, [r5, r0]
	add r4, r2, #0x0
	ldr r0, [r0, #0x0]
	add r7, r1, #0x0
	bl FUN_0206B9B0
	lsl r1, r4, #0x10
	asr r6, r1, #0x10
	mov r1, #0x2c
	mul r1, r7
	str r1, [sp, #0xc]
	add r2, r5, r1
	ldr r1, _0207387C ; =0x00000716
	str r0, [sp, #0x10]
	strh r6, [r2, r1]
	ldr r3, [sp, #0x8]
	add r1, r1, #0x2
	lsl r3, r3, #0x10
	asr r4, r3, #0x10
	strh r4, [r2, r1]
	add r7, r7, #0x4
	bl FUN_0206B6C8
	add r3, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, _02073880 ; =0x000005A8
	str r7, [sp, #0x4]
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	mov r2, #0x13
	bl FUN_0200C9D8
	ldr r0, [sp, #0x10]
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	str r7, [sp, #0x14]
	add r0, sp, #0x14
	strh r6, [r0, #0x4]
	strh r4, [r0, #0x6]
	mov r1, #0x0
	strh r1, [r0, #0x8]
	strh r1, [r0, #0xa]
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x20]
	ldr r1, _02073884 ; =0x00000704
	add r3, r5, r0
	ldrh r0, [r3, r1]
	add r1, #0xd
	ldrb r1, [r3, r1]
	bl FUN_0206B7BC
	add r0, r0, #0x3
	str r0, [sp, #0x24]
	mov r0, #0x1
	str r0, [sp, #0x28]
	mov r0, #0x0
	ldr r1, _02073880 ; =0x000005A8
	str r0, [sp, #0x2c]
	str r0, [sp, #0x30]
	str r0, [sp, #0x34]
	str r0, [sp, #0x38]
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, sp, #0x14
	bl FUN_0200BE38
	ldr r1, [sp, #0xc]
	add r2, r5, r1
	ldr r1, _02073888 ; =0x00000724
	str r0, [r2, r1]
	add sp, #0x3c
	pop {r4-r7, pc}
	nop
_02073878: .word 0x000005A4
_0207387C: .word 0x00000716
_02073880: .word 0x000005A8
_02073884: .word 0x00000704
_02073888: .word 0x00000724

	thumb_func_start FUN_0207388C
FUN_0207388C: ; 0x0207388C
	push {r4-r7, lr}
	sub sp, #0x14
	ldr r1, _020739AC ; =0x000005A8
	add r5, r0, #0x0
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	ldr r2, _020739B0 ; =UNK_020F9914
	bl FUN_0200BE38
	ldr r1, _020739B4 ; =0x000005C8
	ldr r2, _020739B8 ; =UNK_020F993C
	str r0, [r5, r1]
	add r0, r1, #0x0
	sub r0, #0x20
	sub r1, #0x1c
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	bl FUN_0200BE38
	ldr r1, _020739BC ; =0x000005CC
	ldr r2, _020739C0 ; =UNK_020F9964
	str r0, [r5, r1]
	add r0, r1, #0x0
	sub r0, #0x24
	sub r1, #0x20
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	bl FUN_0200BE38
	mov r1, #0x5d
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	add r0, r1, #0x0
	sub r0, #0x28
	sub r1, #0x24
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, _020739C4 ; =UNK_020F998C
	bl FUN_0200BE38
	ldr r1, _020739C8 ; =0x000005D4
	ldr r2, _020739CC ; =UNK_020F9C84
	str r0, [r5, r1]
	add r0, r1, #0x0
	sub r0, #0x2c
	sub r1, #0x28
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	bl FUN_0200BE38
	mov r1, #0x62
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	ldr r0, _020739B0 ; =UNK_020F9914
	mov r4, #0x0
	str r4, [sp, #0x4]
	add r6, r5, #0x0
	str r0, [sp, #0x0]
	add r7, r5, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
_0207390A:
	ldr r0, _020739AC ; =0x000005A8
	ldr r1, _020739D0 ; =0x000005AC
	add r3, r4, #0x0
	ldr r2, [sp, #0x8]
	add r3, #0xa0
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r2, r3
	bl FUN_0200BE38
	ldr r1, _020739D4 ; =0x000005D8
	str r0, [r6, r1]
	ldr r1, [sp, #0x0]
	mov r0, #0xa4
	ldrsh r1, [r1, r0]
	ldr r0, _020739D8 ; =0x0000071A
	strh r1, [r7, r0]
	ldr r1, [sp, #0x0]
	mov r0, #0xa6
	ldrsh r1, [r1, r0]
	ldr r0, _020739DC ; =0x0000071C
	strh r1, [r7, r0]
	ldr r0, _020739D4 ; =0x000005D8
	mov r1, #0x0
	ldr r0, [r6, r0]
	bl FUN_020200A0
	mov r2, #0x19
	ldr r0, _020739AC ; =0x000005A8
	ldr r1, _020739D0 ; =0x000005AC
	lsl r2, r2, #0x4
	add r3, r4, r2
	ldr r2, [sp, #0xc]
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r2, r3
	bl FUN_0200BE38
	mov r1, #0x5f
	lsl r1, r1, #0x4
	mov r2, #0xa
	str r0, [r6, r1]
	add r0, r1, #0x0
	lsl r2, r2, #0x6
	sub r0, #0x48
	sub r1, #0x44
	add r3, r4, r2
	ldr r2, [sp, #0x10]
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r2, r3
	bl FUN_0200BE38
	ldr r1, _020739E0 ; =0x00000608
	add r4, #0x28
	str r0, [r6, r1]
	ldr r0, [sp, #0x0]
	add r6, r6, #0x4
	add r0, #0x28
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r7, #0x2c
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	cmp r0, #0x6
	blo _0207390A
	add r0, r1, #0x0
	sub r0, #0x3c
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_020739AC: .word 0x000005A8
_020739B0: .word UNK_020F9914
_020739B4: .word 0x000005C8
_020739B8: .word UNK_020F993C
_020739BC: .word 0x000005CC
_020739C0: .word UNK_020F9964
_020739C4: .word UNK_020F998C
_020739C8: .word 0x000005D4
_020739CC: .word UNK_020F9C84
_020739D0: .word 0x000005AC
_020739D4: .word 0x000005D8
_020739D8: .word 0x0000071A
_020739DC: .word 0x0000071C
_020739E0: .word 0x00000608

	thumb_func_start FUN_020739E4
FUN_020739E4: ; 0x020739E4
	push {r3-r5, lr}
	sub sp, #0x28
	add r4, r1, #0x0
	mov r1, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r0, sp, #0x0
	strh r2, [r0, #0x4]
	strh r3, [r0, #0x6]
	strh r1, [r0, #0x8]
	strh r1, [r0, #0xa]
	mov r0, #0x1
	str r1, [sp, #0x10]
	str r1, [sp, #0x18]
	str r1, [sp, #0x1c]
	str r1, [sp, #0x20]
	str r1, [sp, #0x24]
	ldr r1, _02073A28 ; =0x000005A8
	str r0, [sp, #0xc]
	str r0, [sp, #0x14]
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, sp, #0x0
	bl FUN_0200BE38
	lsl r1, r4, #0x2
	add r2, r5, r1
	mov r1, #0x5b
	lsl r1, r1, #0x4
	str r0, [r2, r1]
	add sp, #0x28
	pop {r3-r5, pc}
	nop
_02073A28: .word 0x000005A8

	thumb_func_start FUN_02073A2C
FUN_02073A2C: ; 0x02073A2C
	push {r4, lr}
	ldr r1, _02073A48 ; =0x000005A8
	add r4, r0, #0x0
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	bl FUN_0200BCE0
	ldr r0, _02073A48 ; =0x000005A8
	ldr r0, [r4, r0]
	bl FUN_0200BD04
	pop {r4, pc}
	nop
_02073A48: .word 0x000005A8

	thumb_func_start FUN_02073A4C
FUN_02073A4C: ; 0x02073A4C
	push {r3-r5, lr}
	mov r3, #0x5b
	lsl r3, r3, #0x4
	add r1, #0xa
	add r5, r0, r3
	lsl r4, r1, #0x2
	cmp r2, #0x7
	ldr r0, [r5, r4]
	bne _02073A66
	mov r1, #0x0
	bl FUN_020200A0
	pop {r3-r5, pc}
_02073A66:
	add r1, r2, #0x0
	bl FUN_02020130
	ldr r0, [r5, r4]
	mov r1, #0x1
	bl FUN_020200A0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02073A78
FUN_02073A78: ; 0x02073A78
	push {r3-r5, lr}
	mov r3, #0x5b
	lsl r3, r3, #0x4
	add r1, #0x10
	add r5, r0, r3
	lsl r4, r1, #0x2
	cmp r2, #0x0
	bne _02073A92
	ldr r0, [r5, r4]
	mov r1, #0x0
	bl FUN_020200A0
	pop {r3-r5, pc}
_02073A92:
	add r0, r2, #0x0
	bl FUN_0206EA98
	cmp r0, #0x1
	ldr r0, [r5, r4]
	bne _02073AA6
	mov r1, #0x1
	bl FUN_02020130
	b _02073AAC
_02073AA6:
	mov r1, #0x0
	bl FUN_02020130
_02073AAC:
	ldr r0, [r5, r4]
	mov r1, #0x1
	bl FUN_020200A0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02073AB8
FUN_02073AB8: ; 0x02073AB8
	push {r3-r5, lr}
	mov r2, #0x5b
	lsl r2, r2, #0x4
	add r1, #0x10
	lsl r4, r1, #0x2
	add r5, r0, r2
	ldr r0, [r5, r4]
	mov r1, #0x1
	bl FUN_02020130
	ldr r0, [r5, r4]
	mov r1, #0x1
	bl FUN_020200A0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02073AD8
FUN_02073AD8: ; 0x02073AD8
	push {r4-r6, lr}
	ldr r6, _02073B08 ; =0x0000071E
	add r5, r1, #0x0
	mov r4, #0x2c
	mul r5, r4
	add r1, #0x10
	lsl r1, r1, #0x2
	add r4, r0, r6
	add r2, #0x8
	strh r2, [r4, r5]
	add r2, r6, #0x2
	add r2, r0, r2
	add r3, #0x8
	add r1, r0, r1
	mov r0, #0x5b
	strh r3, [r2, r5]
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	ldrsh r1, [r4, r5]
	ldrsh r2, [r2, r5]
	bl FUN_0200C6E4
	pop {r4-r6, pc}
	nop
_02073B08: .word 0x0000071E

	thumb_func_start FUN_02073B0C
FUN_02073B0C: ; 0x02073B0C
	add r2, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x2c
	mul r3, r0
	add r1, #0x16
	lsl r0, r1, #0x2
	add r1, r2, r0
	mov r0, #0x5b
	add r3, r2, r3
	lsl r0, r0, #0x4
	ldr r2, _02073B34 ; =0x0000071E
	ldr r0, [r1, r0]
	ldrsh r1, [r3, r2]
	add r2, r2, #0x2
	ldrsh r2, [r3, r2]
	add r1, #0x8
	lsl r1, r1, #0x10
	ldr r3, _02073B38 ; =FUN_0200C6E4
	asr r1, r1, #0x10
	bx r3
	.balign 4
_02073B34: .word 0x0000071E
_02073B38: .word FUN_0200C6E4

	thumb_func_start FUN_02073B3C
FUN_02073B3C: ; 0x02073B3C
	push {r4, lr}
	mov r2, #0x5b
	mov r4, #0x2c
	lsl r2, r2, #0x4
	add r3, r0, r2
	add r2, r1, #0x0
	mul r4, r1
	add r1, r0, r4
	ldr r0, _02073B6C ; =0x00000712
	add r2, #0x16
	ldrh r0, [r1, r0]
	lsl r2, r2, #0x2
	cmp r0, #0x0
	ldr r0, [r3, r2]
	bne _02073B62
	mov r1, #0x0
	bl FUN_020200A0
	pop {r4, pc}
_02073B62:
	mov r1, #0x1
	bl FUN_020200A0
	pop {r4, pc}
	nop
_02073B6C: .word 0x00000712

	thumb_func_start FUN_02073B70
FUN_02073B70: ; 0x02073B70
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020201DC
	cmp r4, r0
	beq _02073B8E
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02020208
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02020130
_02073B8E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02073B90
FUN_02073B90: ; 0x02073B90
	push {r3, lr}
	add r2, r0, #0x0
	ldrh r0, [r2, #0x6]
	cmp r0, #0x0
	bne _02073B9E
	mov r0, #0x0
	pop {r3, pc}
_02073B9E:
	ldrh r1, [r2, #0xe]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x14
	cmp r1, #0x7
	beq _02073BB4
	cmp r1, #0x0
	beq _02073BB4
	cmp r1, #0x6
	beq _02073BB4
	mov r0, #0x5
	pop {r3, pc}
_02073BB4:
	ldrh r1, [r2, #0x8]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #0x4
	bhi _02073BE6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02073BCC: ; jump table (using 16-bit offset)
	.short _02073BE6 - _02073BCC - 2; case 0
	.short _02073BE2 - _02073BCC - 2; case 1
	.short _02073BDE - _02073BCC - 2; case 2
	.short _02073BDA - _02073BCC - 2; case 3
	.short _02073BD6 - _02073BCC - 2; case 4
_02073BD6:
	mov r0, #0x1
	pop {r3, pc}
_02073BDA:
	mov r0, #0x2
	pop {r3, pc}
_02073BDE:
	mov r0, #0x3
	pop {r3, pc}
_02073BE2:
	mov r0, #0x4
	pop {r3, pc}
_02073BE6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02073BEC
FUN_02073BEC: ; 0x02073BEC
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x7
	lsl r0, r0, #0x8
	add r0, r6, r0
	mov r5, #0x0
	str r0, [sp, #0x0]
_02073BFA:
	mov r0, #0x2c
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	add r4, r0, r1
	add r0, r4, #0x0
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02073C9A
	mov r0, #0xb1
	lsl r0, r0, #0x4
	ldrb r0, [r6, r0]
	cmp r0, #0x1
	bne _02073C2C
	ldr r0, _02073CA8 ; =0x00000B0C
	ldrb r0, [r6, r0]
	cmp r0, r5
	beq _02073C28
	ldr r0, _02073CAC ; =0x00000B0D
	ldrb r0, [r6, r0]
	cmp r0, r5
	bne _02073C2C
_02073C28:
	mov r7, #0x0
	b _02073C34
_02073C2C:
	add r0, r4, #0x0
	bl FUN_02073B90
	add r7, r0, #0x0
_02073C34:
	lsl r1, r7, #0x18
	ldr r0, [r4, #0x24]
	lsr r1, r1, #0x18
	bl FUN_02073B70
	mov r1, #0x1
	ldr r0, [r4, #0x24]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, _02073CB0 ; =0x00000B25
	ldrb r0, [r6, r0]
	cmp r0, r5
	bne _02073C8C
	cmp r7, #0x0
	beq _02073C8C
	cmp r7, #0x5
	beq _02073C8C
	ldr r0, [r4, #0x24]
	bl FUN_0202022C
	cmp r0, #0x0
	ldr r0, [r4, #0x24]
	bne _02073C78
	mov r2, #0x18
	ldrsh r2, [r4, r2]
	mov r1, #0x16
	ldrsh r1, [r4, r1]
	sub r2, r2, #0x3
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	b _02073C9A
_02073C78:
	mov r2, #0x18
	ldrsh r2, [r4, r2]
	mov r1, #0x16
	ldrsh r1, [r4, r1]
	add r2, r2, #0x1
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	b _02073C9A
_02073C8C:
	mov r1, #0x16
	mov r2, #0x18
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #0x24]
	bl FUN_0200C6E4
_02073C9A:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x6
	blo _02073BFA
	pop {r3-r7, pc}
	nop
_02073CA8: .word 0x00000B0C
_02073CAC: .word 0x00000B0D
_02073CB0: .word 0x00000B25

	thumb_func_start FUN_02073CB4
FUN_02073CB4: ; 0x02073CB4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	ldr r0, _02073D10 ; =0x00000808
	add r4, r1, #0x0
	ldr r1, [r5, r0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r1, sp, #0x0
	add r6, r2, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_0201C620
	ldr r0, _02073D14 ; =0x000005A4
	add r1, r4, #0x0
	ldr r0, [r5, r0]
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bl FUN_020714BC
	add r1, r0, #0x0
	ldr r0, _02073D18 ; =0x000005C8
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02073D18 ; =0x000005C8
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _02073D18 ; =0x000005C8
	add r2, sp, #0x0
	ldrb r1, [r2, #0x1]
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, r0]
	bl FUN_0200C6E4
	ldr r0, _02073D18 ; =0x000005C8
	add r1, r6, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200C664
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_02073D10: .word 0x00000808
_02073D14: .word 0x000005A4
_02073D18: .word 0x000005C8

	thumb_func_start FUN_02073D1C
FUN_02073D1C: ; 0x02073D1C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	lsl r0, r1, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r1, r2, #0xc
	lsl r0, r0, #0x14
	str r1, [sp, #0x4]
	add r0, r1, r0
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	add r1, sp, #0x0
	bl FUN_02020044
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_020200A0
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02020208
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02020130
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02073D6C
FUN_02073D6C: ; 0x02073D6C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02020128
	cmp r0, #0x1
	bne _02073DA6
	mov r0, #0x62
	lsl r0, r0, #0x4
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_0202022C
	cmp r0, #0x2
	bne _02073DA6
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
_02073DA6:
	pop {r4, pc}
