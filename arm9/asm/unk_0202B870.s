	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020EEAC8
UNK_020EEAC8: ; 0x020EEAC8
	.byte 0x06

	.global UNK_020EEAC9
UNK_020EEAC9: ; 0x020EEAC9
	.byte 0x00, 0x04, 0x06, 0x03, 0x0A, 0x00, 0x00

	.global UNK_020EEAD0
UNK_020EEAD0: ; 0x020EEAD0
	.byte 0x35, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x3B, 0x00, 0x00, 0x00
	.byte 0x3D, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00
	.byte 0x43, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_0202B870
FUN_0202B870: ; 0x0202B870
	lsl r1, r0, #0x1
	ldr r0, _0202B878 ; =UNK_020EEAC8
	ldrb r0, [r0, r1]
	bx lr
	.balign 4
_0202B878: .word UNK_020EEAC8

	thumb_func_start FUN_0202B87C
FUN_0202B87C: ; 0x0202B87C
	lsl r1, r0, #0x1
	ldr r0, _0202B884 ; =UNK_020EEAC9
	ldrb r0, [r0, r1]
	bx lr
	.balign 4
_0202B884: .word UNK_020EEAC9

	thumb_func_start FUN_0202B888
FUN_0202B888: ; 0x0202B888
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	ldr r3, _0202B898 ; =StringFillEOS
	add r0, #0x8
	mov r1, #0x8
	bx r3
	nop
_0202B898: .word StringFillEOS

	thumb_func_start FUN_0202B89C
FUN_0202B89C: ; 0x0202B89C
	push {r3, lr}
	add r0, #0x8
	bl StringLength
	cmp r0, #0x0
	beq _0202B8AC
	mov r0, #0x1
	pop {r3, pc}
_0202B8AC:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0202B8B0
FUN_0202B8B0: ; 0x0202B8B0
	mov r0, #0xea
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_0202B8B8
FUN_0202B8B8: ; 0x0202B8B8
	push {r3-r7, lr}
	mov r2, #0xea
	mov r1, #0x0
	lsl r2, r2, #0x4
	add r6, r0, #0x0
	bl MI_CpuFill8
	mov r7, #0x0
_0202B8C8:
	mov r4, #0x0
	add r5, r6, #0x0
_0202B8CC:
	add r0, r5, #0x0
	bl FUN_0202B888
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, #0x6
	blt _0202B8CC
	add r7, r7, #0x1
	add r6, #0x90
	cmp r7, #0x1a
	blt _0202B8C8
	pop {r3-r7, pc}

	thumb_func_start FUN_0202B8E4
FUN_0202B8E4: ; 0x0202B8E4
	ldr r3, _0202B8EC ; =SavArray_get
	mov r1, #0x1c
	bx r3
	nop
_0202B8EC: .word SavArray_get

	thumb_func_start FUN_0202B8F0
FUN_0202B8F0: ; 0x0202B8F0
	push {r4-r6, lr}
	cmp r2, #0x6
	blo _0202B8FE
	blo _0202B930
	bl GF_AssertFail
	pop {r4-r6, pc}
_0202B8FE:
	mov r3, #0x90
	mul r3, r1
	add r3, r0, r3
	cmp r2, #0x5
	bge _0202B928
	mov r0, #0x18
	mul r0, r2
	add r6, r3, r0
_0202B90E:
	add r5, r6, #0x0
	add r5, #0x18
	add r4, r6, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	add r2, r2, #0x1
	add r6, #0x18
	stmia r4!, {r0-r1}
	cmp r2, #0x5
	blt _0202B90E
_0202B928:
	add r3, #0x78
	add r0, r3, #0x0
	bl FUN_0202B888
_0202B930:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202B934
FUN_0202B934: ; 0x0202B934
	mov r0, #0x4e
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0202B93C
FUN_0202B93C: ; 0x0202B93C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	bl Sav2_GameStats_get
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x34
	bl AllocFromHeapAtEnd
	str r0, [sp, #0x4]
	add r5, r0, #0x0
	ldr r0, _0202B9E8 ; =UNK_020EEAD0
	mov r6, #0x0
	str r0, [sp, #0x0]
_0202B95A:
	cmp r6, #0x5
	beq _0202B968
	cmp r6, #0xa
	beq _0202B988
	cmp r6, #0xb
	beq _0202B9A0
	b _0202B9C8
_0202B968:
	add r0, r4, #0x0
	mov r1, #0xf
	bl GameStats_GetCapped
	add r7, r0, #0x0
	beq _0202B984
	add r0, r4, #0x0
	mov r1, #0x1d
	bl GameStats_GetCapped
	add r1, r7, #0x0
	bl _u32_div_f
	add r7, r0, #0x0
_0202B984:
	str r7, [r5, #0x0]
	b _0202B9D4
_0202B988:
	add r0, r4, #0x0
	mov r1, #0x41
	bl GameStats_GetCapped
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x42
	bl GameStats_GetCapped
	add r0, r7, r0
	str r0, [r5, #0x0]
	b _0202B9D4
_0202B9A0:
	add r0, r4, #0x0
	mov r1, #0x3f
	bl GameStats_GetCapped
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x40
	bl GameStats_GetCapped
	add r1, r7, r0
	beq _0202B9C4
	ldr r0, [sp, #0x4]
	ldr r2, [r0, #0x28]
	mov r0, #0x64
	mul r0, r2
	bl _u32_div_f
	add r1, r0, #0x0
_0202B9C4:
	str r1, [r5, #0x0]
	b _0202B9D4
_0202B9C8:
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	bl GameStats_GetCapped
	str r0, [r5, #0x0]
_0202B9D4:
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r0, #0x4
	add r5, r5, #0x4
	str r0, [sp, #0x0]
	cmp r6, #0xd
	blt _0202B95A
	ldr r0, [sp, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0202B9E8: .word UNK_020EEAD0

	thumb_func_start FUN_0202B9EC
FUN_0202B9EC: ; 0x0202B9EC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl Sav2_PlayerData_GetProfileAddr
	mov r1, #0x4e
	add r6, r0, #0x0
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl AllocFromHeapAtEnd
	mov r2, #0x4e
	mov r1, #0x0
	lsl r2, r2, #0x2
	str r0, [sp, #0x4]
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl FUN_0202881C
	mov r1, #0x1
	bl FUN_0202877C
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl PlayerProfile_GetPlayerName_NewString
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202B93C
	ldr r4, [sp, #0x4]
	str r0, [sp, #0x0]
	mov r6, #0x0
	add r5, r0, #0x0
_0202BA38:
	ldr r0, [sp, #0x8]
	add r1, r4, #0x0
	str r0, [r4, #0x0]
	add r0, r7, #0x0
	add r1, #0x8
	mov r2, #0x8
	bl CopyStringToU16Array
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	str r0, [r4, #0x4]
	add r4, #0x18
	add r5, r5, #0x4
	cmp r6, #0xd
	blt _0202BA38
	ldr r0, [sp, #0x0]
	bl FreeToHeap
	add r0, r7, #0x0
	bl String_dtor
	ldr r0, [sp, #0x4]
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BA68
FUN_0202BA68: ; 0x0202BA68
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_0202BA6E:
	add r0, r5, #0x0
	bl FUN_0202B888
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, #0x6
	blt _0202BA6E
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202BA80
FUN_0202BA80: ; 0x0202BA80
	push {r3, lr}
	ldr r3, [r0, #0x0]
	ldr r2, [r1, #0x0]
	cmp r3, r2
	beq _0202BA8E
	mov r0, #0x0
	pop {r3, pc}
_0202BA8E:
	add r0, #0x8
	add r1, #0x8
	bl StringNotEqual
	cmp r0, #0x0
	bne _0202BA9E
	mov r0, #0x1
	pop {r3, pc}
_0202BA9E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202BAA4
FUN_0202BAA4: ; 0x0202BAA4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x4]
	add r7, r1, #0x0
	mov r4, #0x0
	cmp r0, #0x0
	ble _0202BACE
	add r5, r6, #0x0
_0202BAB4:
	ldr r0, [r5, #0xc]
	add r1, r7, #0x0
	bl FUN_0202BA80
	cmp r0, #0x0
	beq _0202BAC4
	mov r0, #0x1
	pop {r3-r7, pc}
_0202BAC4:
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r0
	blt _0202BAB4
_0202BACE:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202BAD4
FUN_0202BAD4: ; 0x0202BAD4
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r1, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0xe0
	add r4, r3, #0x0
	bl MI_CpuFill8
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	cmp r0, #0x0
	bne _0202BB64
	mov r2, #0x90
	add r0, r4, #0x0
	mul r0, r2
	add r1, r6, #0x0
	add r0, r5, r0
	add r1, #0x50
	str r0, [sp, #0x8]
	bl MI_CpuCopy8
	add r1, sp, #0x10
	ldrb r3, [r1, #0x18]
	mov r0, #0x0
	cmp r3, #0x0
	ble _0202BB2E
	mov r2, #0x18
	ldr r1, [sp, #0x24]
	mul r2, r4
_0202BB14:
	ldr r5, [r6, #0x4]
	add r0, r0, #0x1
	add r4, r5, #0x0
	add r4, r4, #0x1
	str r4, [r6, #0x4]
	ldr r4, [r1, #0x0]
	lsl r5, r5, #0x2
	add r4, r4, r2
	add r5, r6, r5
	str r4, [r5, #0xc]
	add r1, r1, #0x4
	cmp r0, r3
	blt _0202BB14
_0202BB2E:
	add r4, r6, #0x0
	add r4, #0x50
	mov r7, #0x0
	add r5, r4, #0x0
_0202BB36:
	add r0, r4, #0x0
	bl FUN_0202B89C
	cmp r0, #0x0
	beq _0202BB58
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0202BAA4
	cmp r0, #0x0
	bne _0202BB58
	ldr r1, [r6, #0x0]
	add r0, r1, #0x1
	str r0, [r6, #0x0]
	lsl r0, r1, #0x2
	add r0, r6, r0
	str r4, [r0, #0x38]
_0202BB58:
	add r7, r7, #0x1
	add r4, #0x18
	add r5, #0x18
	cmp r7, #0x6
	blt _0202BB36
	b _0202BBF8
_0202BB64:
	add r0, r4, #0x0
	add r0, #0xd
	mov r2, #0x90
	add r1, r0, #0x0
	mul r1, r2
	add r0, r5, r1
	add r1, r6, #0x0
	add r1, #0x50
	str r0, [sp, #0x8]
	bl MI_CpuCopy8
	add r0, sp, #0x10
	ldrb r2, [r0, #0x18]
	mov r3, #0x0
	cmp r2, #0x0
	ble _0202BBB2
	mov r1, #0x18
	ldr r0, [sp, #0x24]
	mul r1, r4
_0202BB8A:
	ldr r4, [r0, #0x0]
	ldr r5, [r1, r4]
	cmp r5, #0x0
	beq _0202BBAA
	ldr r4, [sp, #0x0]
	cmp r4, r5
	bne _0202BBAA
	ldr r5, [r6, #0x4]
	add r4, r5, #0x0
	add r4, r4, #0x1
	str r4, [r6, #0x4]
	ldr r4, [r0, #0x0]
	lsl r5, r5, #0x2
	add r4, r4, r1
	add r5, r6, r5
	str r4, [r5, #0xc]
_0202BBAA:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, r2
	blt _0202BB8A
_0202BBB2:
	add r4, r6, #0x0
	mov r0, #0x0
	add r4, #0x50
	str r0, [sp, #0x4]
	add r5, r6, #0x0
	add r7, r4, #0x0
_0202BBBE:
	add r0, r4, #0x0
	bl FUN_0202B89C
	cmp r0, #0x0
	beq _0202BBE8
	ldr r1, [r5, #0x50]
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _0202BBE8
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_0202BAA4
	cmp r0, #0x0
	bne _0202BBE8
	ldr r1, [r6, #0x0]
	add r0, r1, #0x1
	str r0, [r6, #0x0]
	lsl r0, r1, #0x2
	add r0, r6, r0
	str r4, [r0, #0x38]
_0202BBE8:
	ldr r0, [sp, #0x4]
	add r4, #0x18
	add r0, r0, #0x1
	add r5, #0x18
	add r7, #0x18
	str r0, [sp, #0x4]
	cmp r0, #0x6
	blt _0202BBBE
_0202BBF8:
	ldr r1, [r6, #0x4]
	ldr r0, [r6, #0x0]
	mov r2, #0x0
	add r0, r1, r0
	str r0, [r6, #0x8]
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	ble _0202BC20
	add r1, r6, #0x0
_0202BC0A:
	ldr r3, [r6, #0x4]
	ldr r0, [r1, #0x38]
	add r3, r2, r3
	lsl r3, r3, #0x2
	add r3, r6, r3
	str r0, [r3, #0xc]
	ldr r0, [r6, #0x0]
	add r2, r2, #0x1
	add r1, r1, #0x4
	cmp r2, r0
	blt _0202BC0A
_0202BC20:
	mov r0, #0x0
	mov r12, r0
	ldr r0, [r6, #0x8]
	sub r5, r0, #0x1
	cmp r5, #0x0
	ble _0202BC64
	add r3, r6, #0x0
_0202BC2E:
	mov r0, r12
	cmp r5, r0
	ble _0202BC52
	lsl r0, r5, #0x2
	add r4, r6, r0
_0202BC38:
	ldr r2, [r4, #0xc]
	ldr r7, [r3, #0xc]
	ldr r0, [r2, #0x4]
	ldr r1, [r7, #0x4]
	cmp r1, r0
	bhs _0202BC48
	str r2, [r3, #0xc]
	str r7, [r4, #0xc]
_0202BC48:
	sub r5, r5, #0x1
	mov r0, r12
	sub r4, r4, #0x4
	cmp r5, r0
	bgt _0202BC38
_0202BC52:
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	ldr r0, [r6, #0x8]
	add r3, r3, #0x4
	sub r5, r0, #0x1
	mov r0, r12
	cmp r0, r5
	blt _0202BC2E
_0202BC64:
	ldr r0, [sp, #0x8]
	bl FUN_0202BA68
	mov r3, #0x0
	add r2, r6, #0x0
	b _0202BC8A
_0202BC70:
	ldr r5, [r2, #0xc]
	ldr r4, [sp, #0x8]
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [sp, #0x8]
	add r2, r2, #0x4
	add r0, #0x18
	str r0, [sp, #0x8]
	add r3, r3, #0x1
_0202BC8A:
	cmp r3, #0x6
	bge _0202BC94
	ldr r0, [r6, #0x8]
	cmp r3, r0
	blt _0202BC70
_0202BC94:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BC98
FUN_0202BC98: ; 0x0202BC98
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r0, #0x0
	add r5, r1, #0x0
	ldr r0, [sp, #0x2c]
	mov r1, #0xe0
	str r2, [sp, #0x10]
	add r4, r3, #0x0
	bl AllocFromHeapAtEnd
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	add r0, sp, #0x18
	ldrb r0, [r0, #0x10]
	add r1, r6, #0x0
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_0202BAD4
	cmp r5, #0x0
	beq _0202BCEA
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	add r0, sp, #0x18
	ldrb r0, [r0, #0x10]
	add r1, r6, #0x0
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_0202BAD4
_0202BCEA:
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BCF4
FUN_0202BCF4: ; 0x0202BCF4
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r1, #0x0
	ldr r1, [sp, #0x38]
	add r4, r0, #0x0
	add r5, r2, #0x0
	add r7, r3, #0x0
	str r1, [sp, #0x38]
	bl FUN_0202B8E4
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_0202881C
	mov r1, #0x1
	bl FUN_0202877C
	mov r4, #0x0
	add r3, r4, #0x0
	str r0, [sp, #0xc]
	cmp r5, #0x0
	bls _0202BD44
_0202BD20:
	cmp r3, r6
	beq _0202BD3A
	lsl r0, r3, #0x2
	ldr r2, [r7, r0]
	cmp r2, #0x0
	beq _0202BD3A
	add r1, r4, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	lsl r1, r0, #0x2
	add r0, sp, #0x10
	str r2, [r0, r1]
_0202BD3A:
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, r5
	blo _0202BD20
_0202BD44:
	cmp r4, #0x0
	beq _0202BD68
	mov r5, #0x0
	add r6, sp, #0x10
_0202BD4C:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add r2, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0202BC98
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0xd
	blo _0202BD4C
_0202BD68:
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BD6C
FUN_0202BD6C: ; 0x0202BD6C
	push {r3-r7, lr}
	sub sp, #0x10
	str r2, [sp, #0x0]
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r1, #0x4c
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x4c
	add r7, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl FUN_0202881C
	mov r1, #0x1
	bl FUN_0202877C
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_0202B93C
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0202B870
	str r0, [r7, #0x0]
	add r0, r5, #0x0
	bl FUN_0202B87C
	ldr r1, [r7, #0x0]
	mov r6, #0x0
	cmp r1, #0x0
	ble _0202BDE2
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x8]
	add r4, r7, #0x0
	add r5, r0, r1
_0202BDC4:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	bl PlayerProfile_GetPlayerName_NewString
	str r0, [r4, #0xc]
	ldr r0, [r7, #0x0]
	add r6, r6, #0x1
	add r4, #0xc
	add r5, r5, #0x4
	cmp r6, r0
	blt _0202BDC4
_0202BDE2:
	ldr r0, [sp, #0x8]
	bl FreeToHeap
	add r0, r7, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202BDF0
FUN_0202BDF0: ; 0x0202BDF0
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r0, r7, #0x0
	mov r1, #0x4c
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x4c
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	mov r1, #0x90
	mul r1, r0
	mov r6, #0x0
	add r5, r5, r1
_0202BE14:
	add r0, r5, #0x0
	bl FUN_0202B89C
	cmp r0, #0x0
	beq _0202BE60
	ldr r2, [r4, #0x0]
	mov r1, #0xc
	mul r1, r2
	ldr r0, [r5, #0x0]
	add r1, r4, r1
	str r0, [r1, #0x4]
	ldr r2, [r4, #0x0]
	mov r1, #0xc
	mul r1, r2
	ldr r0, [r5, #0x4]
	add r1, r4, r1
	str r0, [r1, #0x8]
	mov r0, #0x8
	add r1, r7, #0x0
	bl String_ctor
	ldr r2, [r4, #0x0]
	mov r1, #0xc
	mul r1, r2
	add r1, r4, r1
	str r0, [r1, #0xc]
	ldr r1, [r4, #0x0]
	mov r0, #0xc
	mul r0, r1
	add r0, r4, r0
	add r1, r5, #0x0
	ldr r0, [r0, #0xc]
	add r1, #0x8
	bl CopyU16ArrayToString
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_0202BE60:
	add r6, r6, #0x1
	add r5, #0x18
	cmp r6, #0x6
	blt _0202BE14
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0202BE6C
FUN_0202BE6C: ; 0x0202BE6C
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
_0202BE74:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	beq _0202BE7E
	bl String_dtor
_0202BE7E:
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, #0x6
	blt _0202BE74
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0x4c
	bl MI_CpuFill8
	add r0, r6, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
