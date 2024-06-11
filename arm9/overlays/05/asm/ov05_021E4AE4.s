	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E4AE4
ov05_021E4AE4: ; 0x021E4AE4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	str r2, [sp]
	add r0, r2, #0
	add r2, r3, #0
	mov r1, #0x42
	mov r3, #0
	bl ov05_021F5990
	mov r1, #0x2c
	mov r2, #0
	add r6, r0, #0
	bl ov05_021F5A20
	mov r1, #0
	mov r2, #0x2c
	add r4, r0, #0
	bl memset
	ldr r0, [sp]
	lsl r1, r5, #3
	str r0, [r4]
	mov r0, #0x42
	str r0, [r4, #4]
	str r5, [r4, #8]
	str r6, [r4, #0x14]
	str r7, [r4, #0x18]
	add r0, r6, #0
	mov r2, #0
	bl ov05_021F5A20
	str r0, [r4, #0x1c]
	add r0, r4, #0
	bl ov05_021E4C80
	add r0, r4, #0
	bl ov05_021E4C34
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4B38
ov05_021E4B38: ; 0x021E4B38
	ldr r3, _021E4B40 ; =ov05_021E4D90
	str r1, [r0, #0xc]
	bx r3
	nop
_021E4B40: .word ov05_021E4D90

	thumb_func_start ov05_021E4B44
ov05_021E4B44: ; 0x021E4B44
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r4, [sp, #0x20]
	str r4, [sp]
	ldr r4, [sp, #0x24]
	str r4, [sp, #4]
	ldr r4, [sp, #0x28]
	str r4, [sp, #8]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x10]
	bl ov05_021E4DEC
	add sp, #0x14
	pop {r3, r4, pc}

	thumb_func_start ov05_021E4B64
ov05_021E4B64: ; 0x021E4B64
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021E4D2C
	cmp r0, #0
	beq _021E4B78
	bl GF_AssertFail
	pop {r3, r4, r5, pc}
_021E4B78:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021E4C98
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4B84
ov05_021E4B84: ; 0x021E4B84
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	cmp r1, #0x20
	beq _021E4B9E
_021E4B90:
	add r0, r5, #0
	bl ov05_021E4B64
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, #0x20
	bne _021E4B90
_021E4B9E:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4BA0
ov05_021E4BA0: ; 0x021E4BA0
	ldr r3, _021E4BA4 ; =ov05_021E4DB4
	bx r3
	.balign 4, 0
_021E4BA4: .word ov05_021E4DB4

	thumb_func_start ov05_021E4BA8
ov05_021E4BA8: ; 0x021E4BA8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x14]
	bl ov05_021E4DA0
	add r0, r5, #0
	bl ov05_021E4CDC
	add r0, r5, #0
	bl ov05_021E4E5C
	add r0, r5, #0
	bl ov05_021E4C48
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl ov05_021F5A5C
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F5A5C
	add r0, r4, #0
	bl ov05_021F59EC
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4BDC
ov05_021E4BDC: ; 0x021E4BDC
	ldr r3, _021E4BE4 ; =ov05_021F5A20
	ldr r0, [r0, #0x14]
	bx r3
	nop
_021E4BE4: .word ov05_021F5A20

	thumb_func_start ov05_021E4BE8
ov05_021E4BE8: ; 0x021E4BE8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r3, #0
	bl ov05_021E4BDC
	add r1, r4, #0
	add r2, r5, #0
	add r6, r0, #0
	bl memset
	add r0, r6, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021E4C00
ov05_021E4C00: ; 0x021E4C00
	ldr r3, _021E4C04 ; =FreeToHeap
	bx r3
	.balign 4, 0
_021E4C04: .word FreeToHeap

	thumb_func_start ov05_021E4C08
ov05_021E4C08: ; 0x021E4C08
	push {r3, lr}
	bl ov05_021E4D2C
	cmp r0, #0
	bne _021E4C1A
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
_021E4C1A:
	ldr r0, [r0, #4]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4C20
ov05_021E4C20: ; 0x021E4C20
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start ov05_021E4C24
ov05_021E4C24: ; 0x021E4C24
	push {r3, lr}
	bl MapObject_GetFieldSystem
	ldr r0, [r0, #0x3c]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4C30
ov05_021E4C30: ; 0x021E4C30
	ldr r0, [r0, #4]
	bx lr

	thumb_func_start ov05_021E4C34
ov05_021E4C34: ; 0x021E4C34
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021E4C30
	add r1, r0, #0
	mov r0, #0x6b
	bl NARC_New
	str r0, [r4, #0x20]
	pop {r4, pc}

	thumb_func_start ov05_021E4C48
ov05_021E4C48: ; 0x021E4C48
	ldr r3, _021E4C50 ; =NARC_Delete
	ldr r0, [r0, #0x20]
	bx r3
	nop
_021E4C50: .word NARC_Delete

	thumb_func_start ov05_021E4C54
ov05_021E4C54: ; 0x021E4C54
	ldr r3, _021E4C5C ; =NARC_GetMemberSize
	ldr r0, [r0, #0x20]
	bx r3
	nop
_021E4C5C: .word NARC_GetMemberSize

	thumb_func_start ov05_021E4C60
ov05_021E4C60: ; 0x021E4C60
	ldr r3, _021E4C68 ; =NARC_ReadWholeMember
	ldr r0, [r0, #0x20]
	bx r3
	nop
_021E4C68: .word NARC_ReadWholeMember

	thumb_func_start ov05_021E4C6C
ov05_021E4C6C: ; 0x021E4C6C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r3, r2, #0
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x20]
	add r2, r4, #0
	bl ov05_021F5AB8
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4C80
ov05_021E4C80: ; 0x021E4C80
	push {r3, r4, r5, lr}
	ldr r4, [r0, #8]
	ldr r5, [r0, #0x1c]
	cmp r4, #0
	beq _021E4C96
_021E4C8A:
	add r0, r5, #0
	bl ov05_021E4D44
	add r5, #8
	sub r4, r4, #1
	bne _021E4C8A
_021E4C96:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4C98
ov05_021E4C98: ; 0x021E4C98
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	bl ov05_021E4D68
	add r1, r0, #0
	ldr r1, [r1, #4]
	add r0, r5, #0
	blx r1
	add r4, r0, #0
	add r0, r5, #0
	bl ov05_021E4D04
	add r1, r6, #0
	add r2, r4, #0
	bl ov05_021E4D50
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4CC0
ov05_021E4CC0: ; 0x021E4CC0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	bl ov05_021E4D68
	add r1, r0, #0
	ldr r0, [r4, #4]
	ldr r1, [r1, #8]
	blx r1
	add r0, r4, #0
	bl ov05_021E4D44
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4CDC
ov05_021E4CDC: ; 0x021E4CDC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r4, [r6, #8]
	ldr r5, [r6, #0x1c]
	cmp r4, #0
	beq _021E4D00
_021E4CE8:
	add r0, r5, #0
	bl ov05_021E4D58
	cmp r0, #0
	bne _021E4CFA
	add r0, r6, #0
	add r1, r5, #0
	bl ov05_021E4CC0
_021E4CFA:
	add r5, #8
	sub r4, r4, #1
	bne _021E4CE8
_021E4D00:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4D04
ov05_021E4D04: ; 0x021E4D04
	push {r3, r4, r5, lr}
	ldr r4, [r0, #8]
	ldr r5, [r0, #0x1c]
	cmp r4, #0
	beq _021E4D22
_021E4D0E:
	add r0, r5, #0
	bl ov05_021E4D58
	cmp r0, #1
	bne _021E4D1C
	add r0, r5, #0
	pop {r3, r4, r5, pc}
_021E4D1C:
	add r5, #8
	sub r4, r4, #1
	bne _021E4D0E
_021E4D22:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4D2C
ov05_021E4D2C: ; 0x021E4D2C
	ldr r3, [r0, #8]
	ldr r0, [r0, #0x1c]
	cmp r3, #0
	beq _021E4D40
_021E4D34:
	ldr r2, [r0]
	cmp r2, r1
	beq _021E4D42
	add r0, #8
	sub r3, r3, #1
	bne _021E4D34
_021E4D40:
	mov r0, #0
_021E4D42:
	bx lr

	thumb_func_start ov05_021E4D44
ov05_021E4D44: ; 0x021E4D44
	mov r1, #0x20
	str r1, [r0]
	mov r1, #0
	str r1, [r0, #4]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021E4D50
ov05_021E4D50: ; 0x021E4D50
	str r1, [r0]
	str r2, [r0, #4]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021E4D58
ov05_021E4D58: ; 0x021E4D58
	ldr r0, [r0]
	cmp r0, #0x20
	bne _021E4D62
	mov r0, #1
	bx lr
_021E4D62:
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021E4D68
ov05_021E4D68: ; 0x021E4D68
	push {r3, lr}
	ldr r1, _021E4D8C ; =ov05_021FC820
	ldr r2, [r1]
	cmp r2, #0x20
	beq _021E4D82
_021E4D72:
	cmp r2, r0
	bne _021E4D7A
	add r0, r1, #0
	pop {r3, pc}
_021E4D7A:
	add r1, #0xc
	ldr r2, [r1]
	cmp r2, #0x20
	bne _021E4D72
_021E4D82:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	nop
_021E4D8C: .word ov05_021FC820

	thumb_func_start ov05_021E4D90
ov05_021E4D90: ; 0x021E4D90
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r1, [r4, #0xc]
	bl sub_020643C0
	str r0, [r4, #0x24]
	pop {r4, pc}

	thumb_func_start ov05_021E4DA0
ov05_021E4DA0: ; 0x021E4DA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _021E4DB2
	bl sub_020643F0
	mov r0, #0
	str r0, [r4, #0x24]
_021E4DB2:
	pop {r4, pc}

	thumb_func_start ov05_021E4DB4
ov05_021E4DB4: ; 0x021E4DB4
	push {r3, lr}
	ldr r0, [r0, #0x24]
	cmp r0, #0
	beq _021E4DC0
	bl sub_02064584
_021E4DC0:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4DC4
ov05_021E4DC4: ; 0x021E4DC4
	push {r4, lr}
	sub sp, #8
	ldr r4, [sp, #0x10]
	str r4, [sp]
	ldr r4, [sp, #0x14]
	str r4, [sp, #4]
	ldr r0, [r0, #0x24]
	bl sub_020644E4
	add r4, r0, #0
	bne _021E4DDE
	bl GF_AssertFail
_021E4DDE:
	add r0, r4, #0
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov05_021E4DE4
ov05_021E4DE4: ; 0x021E4DE4
	ldr r3, _021E4DE8 ; =sub_02064520
	bx r3
	.balign 4, 0
_021E4DE8: .word sub_02064520

	thumb_func_start ov05_021E4DEC
ov05_021E4DEC: ; 0x021E4DEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r2, #0
	add r5, r1, #0
	mov r2, #0
	str r3, [sp]
	mov r1, #0x24
	add r3, r2, #0
	add r7, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r4, [r7, #0x28]
	str r5, [r4]
	ldr r0, [sp]
	strh r6, [r4, #4]
	strh r0, [r4, #6]
	ldr r0, [sp, #0x20]
	ldr r2, [sp, #0x28]
	strh r0, [r4, #8]
	ldr r0, [sp, #0x24]
	ldr r3, [sp]
	strh r0, [r4, #0xa]
	add r0, r5, #0
	mov r1, #0x45
	bl ov05_021F5990
	str r0, [r4, #0x10]
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x20]
	add r0, r5, #0
	mov r1, #0x46
	bl ov05_021F5990
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x24]
	add r1, r5, #0
	bl sub_02020E90
	str r0, [r4, #0x18]
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021E4F60
	add r0, r7, #0
	str r6, [sp, #4]
	bl ov05_021E4C30
	str r0, [sp, #8]
	add r0, sp, #4
	bl sub_0201F1B4
	str r0, [r4, #0xc]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E4E5C
ov05_021E4E5C: ; 0x021E4E5C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r5, [r4, #0x28]
	cmp r5, #0
	beq _021E4E8E
	ldr r0, [r5, #0xc]
	bl sub_0201F23C
	add r0, r5, #0
	bl ov05_021E4F94
	ldr r0, [r5, #0x10]
	bl ov05_021F59EC
	ldr r0, [r5, #0x14]
	bl ov05_021F59EC
	ldr r0, [r5, #0x18]
	bl sub_02020ED4
	add r0, r5, #0
	bl ov05_021E4C00
	mov r0, #0
	str r0, [r4, #0x28]
_021E4E8E:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4E90
ov05_021E4E90: ; 0x021E4E90
	push {r4, lr}
	sub sp, #0x20
	ldr r0, [r0, #0x28]
	add r3, sp, #8
	ldr r0, [r0, #0xc]
	str r0, [sp]
	str r1, [sp, #4]
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	add r2, sp, #0x14
	str r0, [r3]
	ldr r3, _021E4EE0 ; =ov05_021F7564
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, sp, #0
	bl sub_0201F6E8
	add r4, r0, #0
	bne _021E4EC0
	bl GF_AssertFail
_021E4EC0:
	cmp r4, #0
	beq _021E4EDA
	add r0, r4, #0
	bl sub_0201F8E0
	mov r1, #1
	bl NNS_G3dMdlSetMdlFogEnableFlagAll
	add r0, r4, #0
	bl sub_0201F8E0
	bl ov05_021DB5EC
_021E4EDA:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	.balign 4, 0
_021E4EE0: .word ov05_021F7564

	thumb_func_start ov05_021E4EE4
ov05_021E4EE4: ; 0x021E4EE4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x28]
	add r4, r2, #0
	bl ov05_021E504C
	add r1, r0, #0
	add r0, r5, #0
	add r2, r4, #0
	bl ov05_021E4E90
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E4EFC
ov05_021E4EFC: ; 0x021E4EFC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r5, [r0, #0x28]
	add r6, r1, #0
	ldr r0, [r5, #0x10]
	add r1, r2, #0
	add r4, r3, #0
	bl ov05_021F5A90
	add r7, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl ov05_021F5A90
	add r1, sp, #0xc
	bl sub_0202227C
	ldr r0, [r5, #0x18]
	ldr r1, [sp, #0x30]
	bl sub_02021050
	add r4, r0, #0
	bne _021E4F2E
	bl GF_AssertFail
_021E4F2E:
	add r0, r4, #0
	bl sub_020210AC
	ldr r1, [sp, #0x34]
	cmp r1, #1
	bne _021E4F3C
	mov r4, #0
_021E4F3C:
	str r0, [sp]
	ldr r0, [sp, #0x38]
	str r4, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	add r3, sp, #0xc
	bl ov05_021E4FC8
	add r4, r0, #0
	bne _021E4F58
	bl GF_AssertFail
_021E4F58:
	add r0, r4, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4F60
ov05_021E4F60: ; 0x021E4F60
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r5, r2, #0
	mov r1, #0x28
	add r7, r0, #0
	mul r1, r5
	mov r2, #0
	bl ov05_021E4BDC
	add r4, r0, #0
	add r0, r7, #0
	lsl r1, r5, #3
	mov r2, #0
	str r4, [r6, #0x20]
	bl ov05_021E4BDC
	str r0, [r6, #0x1c]
	mov r1, #0xe
_021E4F84:
	str r1, [r0]
	str r4, [r0, #4]
	add r0, #8
	add r4, #0x28
	sub r5, r5, #1
	bne _021E4F84
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4F94
ov05_021E4F94: ; 0x021E4F94
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	bl ov05_021E4C00
	ldr r0, [r4, #0x20]
	bl ov05_021E4C00
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4FA8
ov05_021E4FA8: ; 0x021E4FA8
	push {r3, lr}
	ldrh r2, [r0, #4]
	ldr r3, [r0, #0x1c]
_021E4FAE:
	ldr r0, [r3]
	cmp r0, r1
	bne _021E4FBA
	mov r0, #0xe
	str r0, [r3]
	pop {r3, pc}
_021E4FBA:
	add r3, #8
	sub r2, r2, #1
	bne _021E4FAE
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E4FC8
ov05_021E4FC8: ; 0x021E4FC8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldrh r5, [r6, #4]
	add r0, r1, #0
	ldr r1, [sp, #0x1c]
	str r2, [sp]
	ldr r6, [r6, #0x1c]
	add r7, r3, #0
	str r1, [sp, #0x1c]
	mov r4, #0
	add r2, r5, #0
	add r3, r6, #0
_021E4FE0:
	ldr r1, [r3]
	cmp r1, r0
	bne _021E4FEA
	ldr r0, [r3, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021E4FEA:
	add r3, #8
	sub r2, r2, #1
	bne _021E4FE0
_021E4FF0:
	ldr r1, [r6]
	cmp r1, #0xe
	bne _021E4FFC
	str r0, [r6]
	ldr r4, [r6, #4]
	b _021E5002
_021E4FFC:
	add r6, #8
	sub r5, r5, #1
	bne _021E4FF0
_021E5002:
	cmp r4, #0
	bne _021E500A
	bl GF_AssertFail
_021E500A:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x28
	bl memset
	ldr r0, [sp]
	add r2, r4, #0
	str r0, [r4]
	add r2, #0xc
	ldmia r7!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r7!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [sp, #0x18]
	str r0, [r4, #4]
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _021E5044
	bl sub_020211AC
	str r0, [r4, #0x1c]
	ldr r0, [sp, #0x1c]
	bl sub_020211BC
	str r0, [r4, #0x20]
	ldr r0, [sp, #0x1c]
	bl sub_020211CC
	str r0, [r4, #0x24]
_021E5044:
	ldr r0, [sp, #0x20]
	str r0, [r4, #8]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E504C
ov05_021E504C: ; 0x021E504C
	push {r3, lr}
	ldrh r2, [r0, #4]
	ldr r3, [r0, #0x1c]
_021E5052:
	ldr r0, [r3]
	cmp r0, r1
	bne _021E505C
	ldr r0, [r3, #4]
	pop {r3, pc}
_021E505C:
	add r3, #8
	sub r2, r2, #1
	bne _021E5052
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E506C
ov05_021E506C: ; 0x021E506C
	ldr r3, _021E5074 ; =ov05_021E4FA8
	ldr r0, [r0, #0x28]
	bx r3
	nop
_021E5074: .word ov05_021E4FA8

	thumb_func_start ov05_021E5078
ov05_021E5078: ; 0x021E5078
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #0x28]
	add r3, r2, #0
	ldr r0, [r0, #0x10]
	ldr r2, [r4, #0x20]
	bl ov05_021F5AE4
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5094
ov05_021E5094: ; 0x021E5094
	ldr r0, [r0, #0x28]
	ldr r3, _021E509C ; =ov05_021F5A90
	ldr r0, [r0, #0x10]
	bx r3
	.balign 4, 0
_021E509C: .word ov05_021F5A90

	thumb_func_start ov05_021E50A0
ov05_021E50A0: ; 0x021E50A0
	ldr r0, [r0, #0x28]
	ldr r3, _021E50A8 ; =ov05_021F5A74
	ldr r0, [r0, #0x10]
	bx r3
	.balign 4, 0
_021E50A8: .word ov05_021F5A74

	thumb_func_start ov05_021E50AC
ov05_021E50AC: ; 0x021E50AC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #0x28]
	add r3, r2, #0
	ldr r0, [r0, #0x14]
	ldr r2, [r4, #0x20]
	bl ov05_021F5AE4
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E50C8
ov05_021E50C8: ; 0x021E50C8
	ldr r0, [r0, #0x28]
	ldr r3, _021E50D0 ; =ov05_021F5A74
	ldr r0, [r0, #0x14]
	bx r3
	.balign 4, 0
_021E50D0: .word ov05_021F5A74

	thumb_func_start ov05_021E50D4
ov05_021E50D4: ; 0x021E50D4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r1, r2, #0
	ldr r4, [r5, #0x28]
	mov r2, #1
	add r7, r3, #0
	bl ov05_021E4C6C
	str r0, [sp, #4]
	add r0, r5, #0
	bl ov05_021E4C30
	str r0, [sp]
	ldr r0, [r4, #0x18]
	ldr r1, [sp, #4]
	add r2, r6, #0
	add r3, r7, #0
	bl sub_02020F54
	cmp r0, #0
	bne _021E5106
	bl GF_AssertFail
_021E5106:
	ldr r2, [r4, #0x18]
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021E5120
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021E5114
ov05_021E5114: ; 0x021E5114
	ldr r0, [r0, #0x28]
	ldr r3, _021E511C ; =sub_02020FF0
	ldr r0, [r0, #0x18]
	bx r3
	.balign 4, 0
_021E511C: .word sub_02020FF0

	thumb_func_start ov05_021E5120
ov05_021E5120: ; 0x021E5120
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	mov r1, #0xc
	mov r2, #1
	bl ov05_021E4BDC
	add r4, r0, #0
	mov r0, #1
	str r0, [r4]
	str r5, [r4, #4]
	ldr r0, _021E5150 ; =ov05_021E5158
	add r1, r4, #0
	mov r2, #0xff
	str r6, [r4, #8]
	bl sub_0200CA60
	ldr r0, _021E5154 ; =ov05_021E5174
	add r1, r4, #0
	mov r2, #0xff
	bl sub_0200CA98
	pop {r4, r5, r6, pc}
	nop
_021E5150: .word ov05_021E5158
_021E5154: .word ov05_021E5174

	thumb_func_start ov05_021E5158
ov05_021E5158: ; 0x021E5158
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	bl sub_020210F0
	mov r0, #1
	str r0, [r4]
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5174
ov05_021E5174: ; 0x021E5174
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	bne _021E5194
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	bl sub_02021158
	add r0, r4, #0
	bl ov05_021E4C00
	add r0, r5, #0
	bl sub_0200CAB4
_021E5194:
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5198
ov05_021E5198: ; 0x021E5198
	push {r4, r5, r6, lr}
	add r4, r3, #0
	ldr r0, [r4]
	add r6, r1, #0
	add r5, r2, #0
	bl NNS_G3dGetTex
	cmp r0, #0
	beq _021E51C8
	bl sub_0201B254
	cmp r0, #0
	bne _021E51C8
	ldr r0, [r4]
	ldr r1, [r0, #8]
	bl DC_FlushRange
	ldr r0, [r4]
	bl NNS_G3dResDefaultSetup
	cmp r0, #0
	bne _021E51C8
	bl GF_AssertFail
_021E51C8:
	ldr r0, [r4]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r5]
	cmp r5, #0
	bne _021E51E0
	bl GF_AssertFail
_021E51E0:
	ldr r1, [r5]
	add r0, r6, #0
	bl NNS_G3dRenderObjInit
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E51EC
ov05_021E51EC: ; 0x021E51EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r3, #0
	bl ov05_021E4C6C
	ldr r3, [sp, #0x14]
	ldr r2, [sp, #0x10]
	str r0, [r3]
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021E5198
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5208
ov05_021E5208: ; 0x021E5208
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl sub_0201B3C4
	ldr r0, [r4]
	ldr r1, [r4, #0xc]
	bl sub_0201B3A8
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021E5224
ov05_021E5224: ; 0x021E5224
	push {r4, lr}
	add r4, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	bl ov05_021E4C6C
	str r0, [r4]
	bl NNS_G3dGetMdlSet
	str r0, [r4, #4]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #8]
	ldr r0, [r4]
	bl NNS_G3dGetTex
	str r0, [r4, #0xc]
	cmp r0, #0
	beq _021E525A
	mov r2, #1
	ldr r0, _021E525C ; =ov05_021E5208
	add r1, r4, #0
	lsl r2, r2, #0xa
	bl sub_0200CA60
_021E525A:
	pop {r4, pc}
	.balign 4, 0
_021E525C: .word ov05_021E5208

	thumb_func_start ov05_021E5260
ov05_021E5260: ; 0x021E5260
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	add r6, r3, #0
	bl ov05_021E4C6C
	str r0, [r5]
	mov r1, #0
	bl NNS_G3dGetAnmByIdx
	str r0, [r5, #4]
	ldr r1, [r5, #4]
	ldr r2, [r4, #8]
	add r0, r6, #0
	bl NNS_G3dAllocAnmObj
	str r0, [r5, #8]
	ldr r1, [r5, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl NNS_G3dAnmObjInit
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021E5294
ov05_021E5294: ; 0x021E5294
	push {r4, lr}
	add r4, r1, #0
	bl ov05_021E4C30
	add r1, r0, #0
	add r0, r4, #0
	mov r2, #0x20
	bl GF_ExpHeap_FndInitAllocator
	pop {r4, pc}

	.section .rodata

	.global ov05_021F7564
ov05_021F7564: ; 0x021F7564
	.word 0x00001000, 0x00001000, 0x00001000