	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021DBABC
MOD05_021DBABC: ; 0x021DBABC
	push {r4, lr}
	mov r0, #4
	mov r1, #0x48
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #0x48
	bl MIi_CpuClear32
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBAD8
MOD05_021DBAD8: ; 0x021DBAD8
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #4
	bl FUN_02016A8C
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBAEC
MOD05_021DBAEC: ; 0x021DBAEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp, #8]
	add r7, r1, #0
	mov r4, #0
	add r5, r0, #0
	add r6, r0, #0
_021DBAFA:
	mov r0, #1
	lsl r0, r4
	tst r0, r7
	beq _021DBB14
	mov r1, #0
	mov r2, #2
	mov r3, #4
	ldrsh r1, [r5, r1]
	ldrsh r2, [r5, r2]
	ldrsh r3, [r5, r3]
	add r0, r4, #0
	bl FUN_020B8418
_021DBB14:
	add r1, r4, #4
	mov r0, #1
	lsl r0, r1
	tst r0, r7
	beq _021DBB26
	ldrh r1, [r6, #0x18]
	add r0, r4, #0
	bl FUN_020B8404
_021DBB26:
	add r4, r4, #1
	add r5, r5, #6
	add r6, r6, #2
	cmp r4, #4
	blt _021DBAFA
	mov r0, #3
	lsl r0, r0, #8
	tst r0, r7
	beq _021DBB48
	ldr r0, [sp, #8]
	ldr r1, [sp, #8]
	ldr r2, [sp, #8]
	ldrh r0, [r0, #0x20]
	ldrh r1, [r1, #0x22]
	ldr r2, [r2, #0x28]
	bl FUN_020B83E0
_021DBB48:
	mov r0, #3
	lsl r0, r0, #0xa
	tst r0, r7
	beq _021DBB60
	ldr r0, [sp, #8]
	ldr r1, [sp, #8]
	ldr r2, [sp, #8]
	ldrh r0, [r0, #0x24]
	ldrh r1, [r1, #0x26]
	ldr r2, [r2, #0x2c]
	bl FUN_020B83BC
_021DBB60:
	mov r0, #1
	lsl r0, r0, #0xc
	cmp r7, r0
	blt _021DBB88
	ldr r0, [sp, #8]
	ldr r1, [sp, #8]
	ldr r0, [r0, #0x40]
	ldr r2, [sp, #8]
	str r0, [sp]
	ldr r0, [sp, #8]
	ldr r3, [sp, #8]
	ldr r0, [r0, #0x44]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [r1, #0x34]
	ldr r0, [r0, #0x30]
	ldr r2, [r2, #0x38]
	ldr r3, [r3, #0x3c]
	bl FUN_020B8390
_021DBB88:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021DBB8C
MOD05_021DBB8C: ; 0x021DBB8C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #1
	add r4, r2, #0
	lsl r0, r0, #8
	add r6, r1, #0
	tst r0, r4
	beq _021DBBA4
	ldrh r1, [r5, #0x20]
	add r0, r6, #0
	bl FUN_020BBC34
_021DBBA4:
	mov r0, #2
	lsl r0, r0, #8
	tst r0, r4
	beq _021DBBB4
	ldrh r1, [r5, #0x22]
	add r0, r6, #0
	bl FUN_020BBBF4
_021DBBB4:
	mov r0, #1
	lsl r0, r0, #0xa
	tst r0, r4
	beq _021DBBC4
	ldrh r1, [r5, #0x24]
	add r0, r6, #0
	bl FUN_020BBBB4
_021DBBC4:
	mov r0, #2
	lsl r0, r0, #0xa
	tst r0, r4
	beq _021DBBD4
	ldrh r1, [r5, #0x26]
	add r0, r6, #0
	bl FUN_020BBB74
_021DBBD4:
	mov r0, #1
	lsl r0, r0, #0xc
	tst r0, r4
	beq _021DBBE4
	ldr r1, [r5, #0x30]
	add r0, r6, #0
	bl FUN_020BBB34
_021DBBE4:
	mov r0, #2
	lsl r0, r0, #0xc
	tst r0, r4
	beq _021DBBF4
	ldr r1, [r5, #0x34]
	add r0, r6, #0
	bl FUN_020BBAF4
_021DBBF4:
	mov r0, #1
	lsl r0, r0, #0xe
	tst r0, r4
	beq _021DBC04
	ldr r1, [r5, #0x38]
	add r0, r6, #0
	bl FUN_020BBAB4
_021DBC04:
	mov r0, #2
	lsl r0, r0, #0xe
	tst r0, r4
	beq _021DBC14
	ldr r1, [r5, #0x3c]
	add r0, r6, #0
	bl FUN_020BBA74
_021DBC14:
	mov r0, #1
	lsl r0, r0, #0x10
	tst r0, r4
	beq _021DBC24
	ldr r1, [r5, #0x40]
	add r0, r6, #0
	bl FUN_020BBA34
_021DBC24:
	mov r1, #2
	lsl r1, r1, #0x10
	add r0, r4, #0
	tst r0, r1
	beq _021DBC3A
	ldr r2, [r5, #0x44]
	lsr r1, r1, #2
	add r0, r6, #0
	and r1, r2
	bl FUN_020BB9F4
_021DBC3A:
	mov r1, #1
	lsl r1, r1, #0x12
	add r0, r4, #0
	tst r0, r1
	beq _021DBC50
	ldr r2, [r5, #0x44]
	lsr r1, r1, #4
	add r0, r6, #0
	and r1, r2
	bl FUN_020BB9B4
_021DBC50:
	mov r1, #2
	lsl r1, r1, #0x12
	add r0, r4, #0
	tst r0, r1
	beq _021DBC66
	ldr r2, [r5, #0x44]
	lsr r1, r1, #6
	add r0, r6, #0
	and r1, r2
	bl FUN_020BB974
_021DBC66:
	mov r1, #1
	lsl r1, r1, #0x14
	add r0, r4, #0
	tst r0, r1
	beq _021DBC7C
	ldr r2, [r5, #0x44]
	lsr r1, r1, #8
	add r0, r6, #0
	and r1, r2
	bl FUN_020BB934
_021DBC7C:
	mov r1, #2
	lsl r1, r1, #0x14
	add r0, r4, #0
	tst r0, r1
	beq _021DBC92
	ldr r2, [r5, #0x44]
	lsr r1, r1, #0xa
	add r0, r6, #0
	and r1, r2
	bl FUN_020BB8F4
_021DBC92:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021DBC94
MOD05_021DBC94: ; 0x021DBC94
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #6
	add r4, r1, #0
	mul r4, r0
	strh r2, [r5, r4]
	add r2, r5, #2
	strh r3, [r2, r4]
	add r6, sp, #0
	mov r0, #0x10
	ldrsh r0, [r6, r0]
	add r3, r5, #4
	strh r0, [r3, r4]
	add r0, r1, #0
	ldrsh r1, [r5, r4]
	ldrsh r2, [r2, r4]
	ldrsh r3, [r3, r4]
	bl FUN_020B8418
	pop {r4, r5, r6, pc}

	thumb_func_start MOD05_021DBCBC
MOD05_021DBCBC: ; 0x021DBCBC
	push {r4, lr}
	add r4, r0, #0
	add r4, #0x18
	lsl r3, r1, #1
	strh r2, [r4, r3]
	add r0, r1, #0
	ldrh r1, [r4, r3]
	bl FUN_020B8404
	pop {r4, pc}

	thumb_func_start MOD05_021DBCD0
MOD05_021DBCD0: ; 0x021DBCD0
	push {r3, lr}
	strh r1, [r0, #0x20]
	str r2, [r0, #0x28]
	cmp r3, #1
	bne _021DBCE2
	mov r1, #1
	lsl r1, r1, #8
	bl MOD05_021DBAEC
_021DBCE2:
	pop {r3, pc}

	thumb_func_start MOD05_021DBCE4
MOD05_021DBCE4: ; 0x021DBCE4
	push {r3, lr}
	strh r1, [r0, #0x22]
	cmp r2, #1
	bne _021DBCF4
	mov r1, #2
	lsl r1, r1, #8
	bl MOD05_021DBAEC
_021DBCF4:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBCF8
MOD05_021DBCF8: ; 0x021DBCF8
	push {r3, lr}
	strh r1, [r0, #0x24]
	str r2, [r0, #0x2c]
	cmp r3, #1
	bne _021DBD0A
	mov r1, #1
	lsl r1, r1, #0xa
	bl MOD05_021DBAEC
_021DBD0A:
	pop {r3, pc}

	thumb_func_start MOD05_021DBD0C
MOD05_021DBD0C: ; 0x021DBD0C
	push {r3, lr}
	strh r1, [r0, #0x26]
	cmp r2, #1
	bne _021DBD1C
	mov r1, #2
	lsl r1, r1, #0xa
	bl MOD05_021DBAEC
_021DBD1C:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBD20
MOD05_021DBD20: ; 0x021DBD20
	push {r3, lr}
	str r1, [r0, #0x34]
	cmp r2, #1
	bne _021DBD30
	mov r1, #2
	lsl r1, r1, #0xc
	bl MOD05_021DBAEC
_021DBD30:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBD34
MOD05_021DBD34: ; 0x021DBD34
	push {r3, lr}
	str r1, [r0, #0x38]
	cmp r2, #1
	bne _021DBD44
	mov r1, #1
	lsl r1, r1, #0xe
	bl MOD05_021DBAEC
_021DBD44:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBD48
MOD05_021DBD48: ; 0x021DBD48
	push {r3, lr}
	str r1, [r0, #0x40]
	cmp r2, #1
	bne _021DBD58
	mov r1, #1
	lsl r1, r1, #0x10
	bl MOD05_021DBAEC
_021DBD58:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021DBD5C
MOD05_021DBD5C: ; 0x021DBD5C
	push {r3, lr}
	cmp r2, #1
	ldr r2, [r0, #0x44]
	bne _021DBD6A
	tst r2, r1
	beq _021DBD6E
	pop {r3, pc}
_021DBD6A:
	tst r2, r1
	beq _021DBD80
_021DBD6E:
	ldr r2, [r0, #0x44]
	eor r1, r2
	str r1, [r0, #0x44]
	cmp r3, #1
	bne _021DBD80
	mov r1, #1
	lsl r1, r1, #0xc
	bl MOD05_021DBAEC
_021DBD80:
	pop {r3, pc}
	.balign 4, 0
