	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD58_021D9A20
MOD58_021D9A20: ; 0x021D9A20
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _021D9A36
	cmp r1, #1
	bne _021D9A34
	b _021D9B56
_021D9A34:
	b _021D9B64
_021D9A36:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D9B6C ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D9B70 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #3
	mov r1, #0x27
	lsl r2, r2, #6
	bl FUN_0201681C
	ldr r1, _021D9B74 ; =0x00005CB0
	add r0, r6, #0
	mov r2, #0x27
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D9B74 ; =0x00005CB0
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x27
	bl FUN_02016B94
	str r0, [r4]
	mov r0, #0x27
	bl ScrStrBufs_new
	str r0, [r4, #0x10]
	ldr r2, _021D9B78 ; =0x00000176
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x27
	bl NewMsgDataFromNarc
	str r0, [r4, #0x14]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	bl MOD58_021D9CDC
	ldr r0, [r4]
	bl MOD58_021D9CFC
	mov r0, #0x10
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add r0, r6, #0
	bl OverlayManager_GetField18
	bl FUN_02029ABC
	bl FUN_02029AC8
	ldr r1, _021D9B7C ; =0x00005B98
	str r0, [r4, r1]
	add r0, r6, #0
	bl OverlayManager_GetField18
	bl FUN_02029FC8
	str r0, [r4, #8]
	add r0, r6, #0
	bl OverlayManager_GetField18
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	add r0, r4, #0
	bl MOD58_021D9F14
	bl FUN_0201CC08
	mov r0, #1
	bl FUN_0201CC24
	ldr r0, _021D9B80 ; =MOD58_021D9CB4
	ldr r1, [r4]
	bl Main_SetVBlankIntrCB
	mov r0, #2
	mov r1, #0x27
	bl FUN_02002C50
	add r0, r4, #0
	bl MOD58_021D9E04
	bl MOD58_021DA014
	add r0, r4, #0
	bl MOD58_021DA044
	add r0, r4, #0
	bl MOD58_021DA1C4
	add r0, r4, #0
	add r1, r6, #0
	bl MOD58_021DA30C
	mov r1, #0
	mov r0, #0x38
	add r2, r1, #0
	bl FUN_0200433C
	ldr r2, _021D9B84 ; =0x04000304
	ldr r0, _021D9B88 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D9B64
_021D9B56:
	bl OverlayManager_GetData
	mov r0, #0
	str r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D9B64:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D9B6C: .word 0xFFFFE0FF
_021D9B70: .word 0x04001000
_021D9B74: .word 0x00005CB0
_021D9B78: .word 0x00000176
_021D9B7C: .word 0x00005B98
_021D9B80: .word MOD58_021D9CB4
_021D9B84: .word 0x04000304
_021D9B88: .word 0xFFFF7FFF
	thumb_func_end MOD58_021D9A20

	thumb_func_start MOD58_021D9B8C
MOD58_021D9B8C: ; 0x021D9B8C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0
	beq _021D9BA6
	cmp r1, #1
	beq _021D9BB4
	cmp r1, #2
	beq _021D9BD2
	b _021D9BDE
_021D9BA6:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9BDE
	mov r0, #1
	str r0, [r5]
	b _021D9BDE
_021D9BB4:
	mov r2, #0xc3
	lsl r2, r2, #2
	ldr r2, [r4, r2]
	lsl r3, r2, #2
	ldr r2, _021D9BE8 ; =0x021DAFA0
	ldr r2, [r2, r3]
	cmp r2, #0
	beq _021D9BC8
	blx r2
	str r0, [r5]
_021D9BC8:
	ldr r0, _021D9BEC ; =0x00004318
	add r0, r4, r0
	bl MOD58_021DAB34
	b _021D9BDE
_021D9BD2:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D9BDE
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D9BDE:
	ldr r0, [r4, #0x3c]
	bl FUN_0201FDEC
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D9BE8: .word MOD58_021DAFA0
_021D9BEC: .word 0x00004318
	thumb_func_end MOD58_021D9B8C

	thumb_func_start MOD58_021D9BF0
MOD58_021D9BF0: ; 0x021D9BF0
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	bl OverlayManager_GetData
	add r6, r0, #0
	ldr r0, _021D9CAC ; =0x00005B98
	mov r1, #0x2d
	lsl r1, r1, #4
	ldr r0, [r6, r0]
	ldr r1, [r6, r1]
	bl MOD58_021DAC18
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x62
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0x5a
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_021D9C40:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D9C40
	ldr r0, [r6, #0x3c]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	add r0, r6, #0
	bl MOD58_021DA4CC
	mov r0, #2
	bl FUN_02002CF8
	ldr r0, [r6]
	bl MOD58_021D9ED8
	bl FUN_0201CD04
	ldr r0, [r6, #0x14]
	bl DestroyMsgData
	ldr r0, [r6, #0x10]
	bl ScrStrBufs_delete
	add r0, r6, #0
	bl MOD58_021D9EA0
	ldr r0, [sp]
	bl OverlayManager_FreeData
	ldr r2, _021D9CB0 ; =0x04000304
	ldrh r1, [r2]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2]
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x27
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9CAC: .word 0x00005B98
_021D9CB0: .word 0x04000304
	thumb_func_end MOD58_021D9BF0

	thumb_func_start MOD58_021D9CB4
MOD58_021D9CB4: ; 0x021D9CB4
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201C30C
	bl FUN_02009F80
	add r0, r4, #0
	bl FUN_0201AB60
	ldr r3, _021D9CD4 ; =0x027E0000
	ldr r1, _021D9CD8 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_021D9CD4: .word 0x027E0000
_021D9CD8: .word 0x00003FF8
	thumb_func_end MOD58_021D9CB4

	thumb_func_start MOD58_021D9CDC
MOD58_021D9CDC: ; 0x021D9CDC
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D9CF8 ; =0x021DAE6C
	add r3, sp, #0
	mov r2, #5
_021D9CE6:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D9CE6
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D9CF8: .word MOD58_021DAE6C
	thumb_func_end MOD58_021D9CDC

	thumb_func_start MOD58_021D9CFC
MOD58_021D9CFC: ; 0x021D9CFC
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _021D9DEC ; =0x021DADC0
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D9DF0 ; =0x021DAE18
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _021D9DF4 ; =0x021DAE34
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _021D9DF8 ; =0x021DAE50
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _021D9DFC ; =0x021DADE0
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _021D9E00 ; =0x021DADFC
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x27
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x27
	bl FUN_02017F18
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_021D9DEC: .word MOD58_021DADC0
_021D9DF0: .word MOD58_021DAE18
_021D9DF4: .word MOD58_021DAE34
_021D9DF8: .word MOD58_021DAE50
_021D9DFC: .word MOD58_021DADE0
_021D9E00: .word MOD58_021DADFC
	thumb_func_end MOD58_021D9CFC

	thumb_func_start MOD58_021D9E04
MOD58_021D9E04: ; 0x021D9E04
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, _021D9E90 ; =0x0000433D
	mov r6, #0
	add r5, r7, r0
	mov r0, #0xf0
	add r4, r7, #0
	str r0, [sp]
_021D9E14:
	mov r0, #8
	mov r1, #0x27
	bl String_ctor
	str r0, [r4, #0x18]
	ldrb r1, [r5]
	ldr r0, [sp]
	add r6, r6, #1
	bic r1, r0
	strb r1, [r5]
	ldr r0, _021D9E94 ; =0x00004384
	mov r1, #0
	strh r1, [r4, r0]
	add r4, r4, #4
	add r5, #0x11
	cmp r6, #5
	blt _021D9E14
	mov r0, #0x14
	mov r1, #0x27
	bl String_ctor
	str r0, [r7, #0x2c]
	mov r0, #0x28
	mov r1, #0x27
	bl String_ctor
	str r0, [r7, #0x30]
	mov r0, #0x50
	mov r1, #0x27
	bl String_ctor
	str r0, [r7, #0x34]
	ldr r0, _021D9E98 ; =0x0000431A
	mov r1, #0
	strb r1, [r7, r0]
	mov r0, #0xc3
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r7, r0]
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x2c]
	mov r1, #0xc
	bl ReadMsgDataIntoString
	ldr r0, [r7, #0x14]
	ldr r2, [r7, #0x30]
	mov r1, #9
	bl ReadMsgDataIntoString
	mov r0, #0x27
	bl FUN_02014590
	ldr r1, _021D9E9C ; =0x00005C9C
	mov r2, #5
	str r0, [r7, r1]
	add r1, r1, #4
	mov r0, #0
	add r1, r7, r1
	bl MIi_CpuClearFast
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9E90: .word 0x0000433D
_021D9E94: .word 0x00004384
_021D9E98: .word 0x0000431A
_021D9E9C: .word 0x00005C9C
	thumb_func_end MOD58_021D9E04

	thumb_func_start MOD58_021D9EA0
MOD58_021D9EA0: ; 0x021D9EA0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _021D9ED4 ; =0x00005C9C
	ldr r0, [r6, r0]
	bl FUN_020145A8
	mov r4, #0
	add r5, r6, #0
_021D9EB0:
	ldr r0, [r5, #0x18]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _021D9EB0
	ldr r0, [r6, #0x34]
	bl String_dtor
	ldr r0, [r6, #0x30]
	bl String_dtor
	ldr r0, [r6, #0x2c]
	bl String_dtor
	pop {r4, r5, r6, pc}
	nop
_021D9ED4: .word 0x00005C9C
	thumb_func_end MOD58_021D9EA0

	thumb_func_start MOD58_021D9ED8
MOD58_021D9ED8: ; 0x021D9ED8
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD58_021D9ED8

	thumb_func_start MOD58_021D9F14
MOD58_021D9F14: ; 0x021D9F14
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5]
	mov r0, #0x60
	mov r1, #0
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	mov r0, #0x5f
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02006930
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	mov r0, #0x5f
	mov r1, #2
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x27
	bl FUN_02002EEC
	mov r1, #0x1a
	mov r0, #4
	lsl r1, r1, #4
	mov r2, #0x27
	bl FUN_02002EEC
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x27
	bl FUN_02017F18
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	str r0, [sp, #0xc]
	mov r0, #0x5f
	mov r1, #3
	add r2, r4, #0
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	str r0, [sp, #0xc]
	mov r0, #0x5f
	mov r1, #5
	add r2, r4, #0
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	str r0, [sp, #0xc]
	mov r0, #0x5f
	mov r1, #4
	add r2, r4, #0
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x27
	str r0, [sp, #0xc]
	mov r0, #0x5f
	mov r1, #6
	add r2, r4, #0
	mov r3, #5
	bl FUN_020068C8
	ldr r0, [r5, #0xc]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x27
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD58_021D9F14

	thumb_func_start MOD58_021DA014
MOD58_021DA014: ; 0x021DA014
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021DA040 ; =0x021DADD0
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x27
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DA040: .word MOD58_021DADD0
	thumb_func_end MOD58_021DA014

	thumb_func_start MOD58_021DA044
MOD58_021DA044: ; 0x021DA044
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x27
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r5, #0
	mov r0, #0x32
	add r1, #0x40
	mov r2, #0x27
	bl FUN_02008C9C
	str r0, [r5, #0x3c]
	add r0, r5, #0
	mov r2, #1
	add r0, #0x40
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0x5a
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #2
_021DA08A:
	mov r0, #2
	add r1, r6, #0
	mov r2, #0x27
	bl FUN_02008DEC
	str r0, [r4, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _021DA08A
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x5f
	mov r2, #7
	bl FUN_02008F34
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0x27
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	bl FUN_02008FEC
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	mov r2, #8
	mov r3, #1
	bl FUN_020090AC
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	mov r2, #9
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x61
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	mov r2, #7
	bl FUN_02008F34
	mov r1, #0x62
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r2, #1
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x63
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	mov r2, #8
	bl FUN_020090AC
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r3, #1
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x27
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x5f
	mov r2, #9
	bl FUN_020090AC
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r5, r1]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	bl FUN_02009A50
	mov r0, #0x62
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009A50
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD58_021DA044

	thumb_func_start MOD58_021DA1C4
MOD58_021DA1C4: ; 0x021DA1C4
	push {r3, r4, lr}
	sub sp, #0x5c
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r2, #0x5a
	str r1, [sp, #0x10]
	lsl r2, r2, #2
	ldr r0, [r4, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r4, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r4, r0]
	str r0, [sp, #0x1c]
	add r0, r2, #0
	add r0, #0xc
	ldr r0, [r4, r0]
	add r2, #0x30
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r4, r2
	add r2, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	mov r1, #1
	mov r3, #0x5a
	str r1, [sp]
	sub r0, r1, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #2
	ldr r2, [r4, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r4, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r4, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r4, r2]
	add r3, #0x54
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r4, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	ldr r0, [r4, #0x3c]
	mov r2, #0
	str r0, [sp, #0x2c]
	mov r0, #0x66
	lsl r0, r0, #2
	add r1, r4, r0
	str r1, [sp, #0x30]
	mov r1, #1
	lsl r1, r1, #0xc
	add r0, #0x24
	str r2, [sp, #0x3c]
	str r1, [sp, #0x40]
	str r1, [sp, #0x44]
	str r1, [sp, #0x48]
	add r1, sp, #0x2c
	strh r2, [r1, #0x20]
	mov r1, #1
	add r0, r4, r0
	str r0, [sp, #0x30]
	mov r0, #0xe
	lsl r0, r0, #0x10
	str r0, [sp, #0x34]
	mov r0, #0xaf
	lsl r0, r0, #0xc
	str r0, [sp, #0x38]
	str r1, [sp, #0x50]
	str r1, [sp, #0x54]
	mov r1, #0x27
	add r0, sp, #0x2c
	str r1, [sp, #0x58]
	bl FUN_0201FE94
	mov r1, #0x25
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x25
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020130
	mov r0, #0x25
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020248
	mov r0, #0x25
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_02020238
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x5c
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD58_021DA1C4

	thumb_func_start MOD58_021DA2CC
MOD58_021DA2CC: ; 0x021DA2CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r4, r2, #0
	mov r0, #2
	mov r2, #0
	add r6, r1, #0
	add r7, r3, #0
	bl FUN_02002E14
	add r3, r0, #0
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	add r1, r7, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r4, [r5, #7]
	add r0, r5, #0
	add r2, r6, #0
	lsl r4, r4, #3
	sub r4, r4, r3
	lsr r3, r4, #0x1f
	add r3, r4, r3
	asr r3, r3, #1
	bl AddTextPrinterParameterized2
	ldr r0, [r5, #0xc]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD58_021DA2CC

	thumb_func_start MOD58_021DA30C
MOD58_021DA30C: ; 0x021DA30C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	mov r1, #0xb5
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5]
	add r1, r5, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	mov r0, #0xb5
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #9
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #8
	mov r1, #0xb1
	lsl r1, r1, #2
	str r0, [sp, #8]
	mov r2, #1
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	ldr r0, [r5]
	add r1, r5, r1
	mov r3, #4
	bl FUN_02019064
	mov r0, #0xb1
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #2
	bl FUN_02019620
	mov r0, #0x15
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #0xc1
	mov r1, #0xb9
	str r0, [sp, #0x10]
	lsl r1, r1, #2
	ldr r0, [r5]
	add r1, r5, r1
	mov r2, #1
	mov r3, #0x1a
	bl FUN_02019064
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	ldr r0, _021DA4BC ; =0x000E0702
	mov r2, #1
	str r0, [sp]
	mov r0, #0xb9
	lsl r0, r0, #2
	ldr r1, [r5, #0x2c]
	add r0, r5, r0
	mov r3, #2
	bl MOD58_021DA2CC
	mov r1, #2
	lsl r1, r1, #8
	bl DC_FlushRange
	mov r4, #0
	ldr r0, _021DA4C0 ; =0x00005B9C
	str r4, [sp, #0x18]
	add r7, r4, #0
	add r6, r5, r0
_021DA3C2:
	mov r0, #0
	str r0, [sp]
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #4
	mov r2, #2
	add r3, r4, #0
	str r6, [sp, #4]
	bl FUN_02011B20
	mov r1, #1
	add r0, r6, #0
	lsl r1, r1, #8
	bl DC_FlushRange
	mov r2, #1
	add r0, r6, #0
	add r1, r7, #0
	lsl r2, r2, #8
	bl GX_LoadOBJ
	mov r0, #1
	lsl r0, r0, #8
	add r7, r7, r0
	ldr r0, [sp, #0x18]
	add r4, r4, #4
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #2
	blt _021DA3C2
	mov r3, #2
	str r3, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r1, #0xbd
	lsl r1, r1, #2
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0xd1
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, r5, r1
	mov r2, #1
	bl FUN_02019064
	ldr r1, [r5, #0x30]
	mov r0, #1
	mov r2, #0
	bl FUN_02002E14
	add r4, r0, #0
	mov r0, #0xbd
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r3, #0xe0
	sub r4, r3, r4
	lsr r3, r4, #0x1f
	add r3, r4, r3
	ldr r0, _021DA4C4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #0xbd
	lsl r0, r0, #2
	ldr r2, [r5, #0x30]
	add r0, r5, r0
	mov r1, #1
	asr r3, r3, #1
	bl AddTextPrinterParameterized2
	mov r0, #0
	str r0, [sp, #0x14]
	mov r0, #0x9d
	lsl r0, r0, #2
	mov r7, #1
	mov r6, #3
	add r4, r5, r0
_021DA46A:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #4
	mov r3, #5
	bl FUN_02019064
	add r0, r4, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [sp, #0x14]
	add r7, #0x14
	add r0, r0, #1
	add r6, r6, #4
	add r4, #0x10
	str r0, [sp, #0x14]
	cmp r0, #5
	blt _021DA46A
	mov r0, #0x9d
	lsl r0, r0, #2
	ldr r2, _021DA4C8 ; =0x000E0D0F
	add r0, r5, r0
	mov r1, #0
	add r3, r5, #0
	bl MOD58_021DAB74
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021DA4BC: .word 0x000E0702
_021DA4C0: .word 0x00005B9C
_021DA4C4: .word 0x00010200
_021DA4C8: .word 0x000E0D0F
	thumb_func_end MOD58_021DA30C

	thumb_func_start MOD58_021DA4CC
MOD58_021DA4CC: ; 0x021DA4CC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r0, #0x9d
	lsl r0, r0, #2
	mov r4, #0
	add r5, r6, r0
_021DA4D8:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #5
	blt _021DA4D8
	mov r0, #0xbd
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	mov r0, #0xb1
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	mov r0, #0xb5
	lsl r0, r0, #2
	add r0, r6, r0
	bl FUN_02019178
	pop {r4, r5, r6, pc}
	thumb_func_end MOD58_021DA4CC

	thumb_func_start MOD58_021DA510
MOD58_021DA510: ; 0x021DA510
	bx lr
	.align 2, 0
	thumb_func_end MOD58_021DA510

	thumb_func_start MOD58_021DA514
MOD58_021DA514: ; 0x021DA514
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r4, r0, #0
	ldr r0, _021DA5DC ; =0x021DADAE
	bl FUN_02020988
	add r1, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _021DA568
	cmp r1, #0
	bne _021DA55A
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021DA568
	add r0, r4, #0
	mov r1, #0xa
	bl MOD58_021DAB94
	mov r0, #0xc3
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r4, r0]
	sub r0, #0xbc
	add r0, r4, r0
	mov r1, #1
	bl MOD58_021DA614
	ldr r0, _021DA5E0 ; =0x000005DD
	bl FUN_020054C8
	b _021DA568
_021DA55A:
	ldr r0, _021DA5E4 ; =0x0000431A
	strb r1, [r4, r0]
	mov r0, #0x25
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD58_021DA5F4
_021DA568:
	ldr r0, _021DA5E8 ; =0x021DADA6
	bl FUN_02020968
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _021DA57C
	add r0, r4, #0
	bl MOD58_021DAC7C
_021DA57C:
	add r0, sp, #0
	mov r1, #4
	mov r2, #1
	bl FUN_0201CD38
	cmp r0, #1
	bne _021DA5D8
	add r7, sp, #0
	ldrh r3, [r7]
	mov r1, #0
	cmp r3, #0
	ble _021DA5B0
	ldr r5, _021DA5EC ; =0x0000431C
	add r2, sp, #0
	add r6, r5, #0
	add r6, #8
_021DA59C:
	ldrh r3, [r2, #2]
	add r0, r4, r1
	add r1, r1, #1
	strb r3, [r0, r5]
	ldrh r3, [r2, #4]
	add r2, #8
	strb r3, [r0, r6]
	ldrh r3, [r7]
	cmp r1, r3
	blt _021DA59C
_021DA5B0:
	ldr r0, _021DA5F0 ; =0x0000432C
	mov r2, #0xf0
	ldrb r1, [r4, r0]
	bic r1, r2
	lsl r2, r3, #0x18
	lsr r2, r2, #0x18
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x18
	orr r1, r2
	strb r1, [r4, r0]
	ldrb r3, [r4, r0]
	mov r1, #0xf
	bic r3, r1
	add r1, r0, #0
	sub r1, #0x12
	ldrb r2, [r4, r1]
	mov r1, #0xf
	and r1, r2
	orr r1, r3
	strb r1, [r4, r0]
_021DA5D8:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DA5DC: .word MOD58_021DADAE
_021DA5E0: .word 0x000005DD
_021DA5E4: .word 0x0000431A
_021DA5E8: .word MOD58_021DADA6
_021DA5EC: .word 0x0000431C
_021DA5F0: .word 0x0000432C
	thumb_func_end MOD58_021DA514

	thumb_func_start MOD58_021DA5F4
MOD58_021DA5F4: ; 0x021DA5F4
	push {r3, lr}
	ldr r2, _021DA610 ; =0x021DADA0
	cmp r1, #0
	ldr r0, [r0]
	bne _021DA608
	ldrh r1, [r2, #4]
	add r1, r1, #1
	bl FUN_02020130
	pop {r3, pc}
_021DA608:
	ldrh r1, [r2, #4]
	bl FUN_02020130
	pop {r3, pc}
	.align 2, 0
_021DA610: .word MOD58_021DADA0
	thumb_func_end MOD58_021DA5F4

	thumb_func_start MOD58_021DA614
MOD58_021DA614: ; 0x021DA614
	push {r3, lr}
	cmp r1, #1
	ldr r0, [r0]
	bne _021DA624
	mov r1, #1
	bl FUN_02020130
	pop {r3, pc}
_021DA624:
	mov r1, #0
	bl FUN_02020130
	pop {r3, pc}
	thumb_func_end MOD58_021DA614

	thumb_func_start MOD58_021DA62C
MOD58_021DA62C: ; 0x021DA62C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD58_021DA514
	mov r0, #0x9d
	lsl r0, r0, #2
	ldr r2, _021DA66C ; =0x000E0C0F
	add r0, r5, r0
	mov r1, #0
	add r3, r5, #0
	bl MOD58_021DAB74
	add r0, r5, #0
	bl MOD58_021DAB78
	add r0, r5, #0
	bl MOD58_021DAB30
	ldr r2, _021DA670 ; =0x0000432D
	mov r0, #0xb1
	lsl r0, r0, #2
	add r1, r5, r2
	add r2, #0x55
	add r0, r5, r0
	add r2, r5, r2
	mov r3, #1
	bl MOD58_021DAA70
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	nop
_021DA66C: .word 0x000E0C0F
_021DA670: .word 0x0000432D
	thumb_func_end MOD58_021DA62C

	thumb_func_start MOD58_021DA674
MOD58_021DA674: ; 0x021DA674
	push {r4, lr}
	add r4, r0, #0
	bl MOD58_021DA510
	add r0, r4, #0
	bl MOD58_021DAB30
	ldr r2, _021DA698 ; =0x0000432D
	mov r0, #0xb1
	lsl r0, r0, #2
	add r1, r4, r2
	add r2, #0x55
	add r0, r4, r0
	add r2, r4, r2
	mov r3, #0
	bl MOD58_021DAA70
	pop {r4, pc}
	.align 2, 0
_021DA698: .word 0x0000432D
	thumb_func_end MOD58_021DA674

	thumb_func_start MOD58_021DA69C
MOD58_021DA69C: ; 0x021DA69C
	push {lr}
	sub sp, #0x14
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0xb4
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	mov r2, #0x19
	add r0, sp, #0
	strb r2, [r0, #0x10]
	mov r2, #6
	strb r2, [r0, #0x11]
	add r0, r1, #0
	add r1, sp, #0
	bl FUN_020145C8
	add sp, #0x14
	pop {pc}
	thumb_func_end MOD58_021DA69C

	thumb_func_start MOD58_021DA6C4
MOD58_021DA6C4: ; 0x021DA6C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	add r4, r1, #0
	bl MOD58_021DAC00
	cmp r0, #0
	beq _021DA6E6
	ldr r1, _021DA6F0 ; =0x00005C9C
	ldr r0, [r5]
	ldr r1, [r5, r1]
	bl MOD58_021DA69C
	mov r0, #0xc3
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r5, r0]
_021DA6E6:
	add r0, r5, #0
	bl MOD58_021DA674
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA6F0: .word 0x00005C9C
	thumb_func_end MOD58_021DA6C4

	thumb_func_start MOD58_021DA6F4
MOD58_021DA6F4: ; 0x021DA6F4
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _021DA784 ; =0x00005C9C
	add r4, r1, #0
	ldr r0, [r5, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _021DA70E
	cmp r0, #2
	beq _021DA748
	b _021DA76E
_021DA70E:
	ldr r0, [r5, #8]
	mov r1, #4
	bl FUN_0202A170
	mov r0, #0xb5
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #1
	bl FUN_0200D0E0
	ldr r0, _021DA784 ; =0x00005C9C
	ldr r0, [r5, r0]
	bl FUN_020146C4
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x27
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	add sp, #0xc
	mov r0, #2
	pop {r4, r5, pc}
_021DA748:
	mov r0, #0xc3
	mov r1, #4
	lsl r0, r0, #2
	str r1, [r5, r0]
	sub r0, #0xbc
	add r0, r5, r0
	mov r1, #0
	bl MOD58_021DA614
	mov r0, #0xb5
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #1
	bl FUN_0200D0E0
	ldr r0, _021DA784 ; =0x00005C9C
	ldr r0, [r5, r0]
	bl FUN_020146C4
_021DA76E:
	ldr r1, _021DA788 ; =0x0000432C
	mov r0, #0xf0
	ldrb r2, [r5, r1]
	bic r2, r0
	add r0, r5, #0
	strb r2, [r5, r1]
	bl MOD58_021DA674
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021DA784: .word 0x00005C9C
_021DA788: .word 0x0000432C
	thumb_func_end MOD58_021DA6F4

	thumb_func_start MOD58_021DA78C
MOD58_021DA78C: ; 0x021DA78C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021DA7F0 ; =0x00005C9C
	add r4, r1, #0
	ldr r0, [r5, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _021DA7A4
	cmp r0, #2
	beq _021DA7D4
	b _021DA7EC
_021DA7A4:
	mov r0, #0xc3
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
	sub r0, #0x38
	add r0, r5, r0
	bl FUN_0200D0E0
	ldr r0, _021DA7F0 ; =0x00005C9C
	ldr r0, [r5, r0]
	bl FUN_020146C4
	mov r0, #0xb1
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #2
	bl FUN_02019620
	mov r0, #0xb1
	lsl r0, r0, #2
	add r0, r5, r0
	bl CopyWindowToVram
	b _021DA7EC
_021DA7D4:
	mov r0, #0xc3
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
	sub r0, #0x38
	add r0, r5, r0
	bl FUN_0200D0E0
	ldr r0, _021DA7F0 ; =0x00005C9C
	ldr r0, [r5, r0]
	bl FUN_020146C4
_021DA7EC:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA7F0: .word 0x00005C9C
	thumb_func_end MOD58_021DA78C

	thumb_func_start MOD58_021DA7F4
MOD58_021DA7F4: ; 0x021DA7F4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0xb
	add r5, r0, #0
	bl MOD58_021DAB94
	mov r0, #0xc3
	mov r1, #5
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD58_021DA674
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD58_021DA7F4

	thumb_func_start MOD58_021DA814
MOD58_021DA814: ; 0x021DA814
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x38]
	add r4, r1, #0
	bl MOD58_021DAC00
	cmp r0, #0
	beq _021DA836
	mov r0, #0xc3
	mov r1, #6
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldr r1, _021DA840 ; =0x00005C9C
	ldr r0, [r5]
	ldr r1, [r5, r1]
	bl MOD58_021DA69C
_021DA836:
	add r0, r5, #0
	bl MOD58_021DA674
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021DA840: .word 0x00005C9C
	thumb_func_end MOD58_021DA814

	thumb_func_start MOD58_021DA844
MOD58_021DA844: ; 0x021DA844
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r4, [sp, #0x38]
	mov ip, r1
	add r6, r2, #0
	add r7, r3, #0
	str r0, [sp, #0x18]
	ldr r3, [sp, #0x3c]
	ldr r2, [sp, #0x40]
	ldr r1, [sp, #0x44]
	cmp r4, #0
	bge _021DA870
	neg r0, r4
	cmp r0, r2
	ble _021DA864
	add r0, r2, #0
_021DA864:
	ldr r5, [sp, #0x30]
	mov r4, #0
	sub r5, r5, r0
	add r6, r6, r0
	str r5, [sp, #0x30]
	sub r2, r2, r0
_021DA870:
	cmp r3, #0
	bge _021DA888
	neg r0, r3
	cmp r0, r1
	ble _021DA87C
	add r0, r1, #0
_021DA87C:
	ldr r5, [sp, #0x34]
	mov r3, #0
	sub r5, r5, r0
	add r7, r7, r0
	str r5, [sp, #0x34]
	sub r1, r1, r0
_021DA888:
	ldr r0, [sp, #0x30]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x34]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	lsl r0, r3, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	lsl r2, r6, #0x10
	lsl r3, r7, #0x10
	ldr r0, [sp, #0x18]
	mov r1, ip
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_02019658
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD58_021DA844

	thumb_func_start MOD58_021DA8C4
MOD58_021DA8C4: ; 0x021DA8C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x50]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x50]
	ldr r0, [sp, #0x54]
	str r2, [sp, #0x20]
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x50]
	str r3, [sp, #0x24]
	ldr r4, [r0]
	ldr r0, [sp, #0x54]
	ldr r5, [r0]
	add r0, r2, #0
	str r0, [sp, #0x38]
	add r0, r3, #0
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x58]
	cmp r0, #0
	bne _021DA904
	ldr r0, [sp, #0x5c]
	cmp r0, #0
	bne _021DA904
	ldr r0, [sp, #0x50]
	add r1, r2, #0
	str r1, [r0]
	ldr r0, [sp, #0x54]
	add r1, r3, #0
	str r1, [r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
_021DA904:
	ldr r0, [sp, #0x20]
	sub r0, r0, r4
	str r0, [sp, #0x34]
	bpl _021DA910
	neg r0, r0
	str r0, [sp, #0x34]
_021DA910:
	ldr r0, [sp, #0x24]
	sub r7, r0, r5
	bpl _021DA918
	neg r7, r7
_021DA918:
	ldr r0, [sp, #0x34]
	cmp r0, r7
	ble _021DA9A6
	ldr r0, [sp, #0x20]
	cmp r4, r0
	ble _021DA93E
	ldr r0, [sp, #0x24]
	cmp r5, r0
	ble _021DA930
	mov r0, #1
	str r0, [sp, #0x2c]
	b _021DA936
_021DA930:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x2c]
_021DA936:
	str r4, [sp, #0x38]
	ldr r4, [sp, #0x20]
	ldr r5, [sp, #0x24]
	b _021DA950
_021DA93E:
	ldr r0, [sp, #0x24]
	cmp r5, r0
	bge _021DA94A
	mov r0, #1
	str r0, [sp, #0x2c]
	b _021DA950
_021DA94A:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x2c]
_021DA950:
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD58_021DA844
	ldr r0, [sp, #0x34]
	add r4, r4, #1
	asr r6, r0, #1
	ldr r0, [sp, #0x38]
	cmp r4, r0
	bgt _021DAA2A
_021DA976:
	sub r6, r6, r7
	bpl _021DA982
	ldr r0, [sp, #0x34]
	add r6, r6, r0
	ldr r0, [sp, #0x2c]
	add r5, r5, r0
_021DA982:
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD58_021DA844
	ldr r0, [sp, #0x38]
	add r4, r4, #1
	cmp r4, r0
	ble _021DA976
	b _021DAA2A
_021DA9A6:
	ldr r0, [sp, #0x24]
	cmp r5, r0
	ble _021DA9C6
	ldr r0, [sp, #0x20]
	cmp r4, r0
	ble _021DA9B8
	mov r0, #1
	str r0, [sp, #0x28]
	b _021DA9BE
_021DA9B8:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x28]
_021DA9BE:
	str r5, [sp, #0x30]
	ldr r5, [sp, #0x24]
	ldr r4, [sp, #0x20]
	b _021DA9D8
_021DA9C6:
	ldr r0, [sp, #0x20]
	cmp r4, r0
	bge _021DA9D2
	mov r0, #1
	str r0, [sp, #0x28]
	b _021DA9D8
_021DA9D2:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x28]
_021DA9D8:
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD58_021DA844
	ldr r0, [sp, #0x30]
	add r5, r5, #1
	asr r6, r7, #1
	cmp r5, r0
	bgt _021DAA2A
_021DA9FC:
	ldr r0, [sp, #0x34]
	sub r6, r6, r0
	bpl _021DAA08
	ldr r0, [sp, #0x28]
	add r6, r6, r7
	add r4, r4, r0
_021DAA08:
	mov r0, #4
	str r0, [sp]
	str r0, [sp, #4]
	str r4, [sp, #8]
	str r5, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r3, r2, #0
	bl MOD58_021DA844
	ldr r0, [sp, #0x30]
	add r5, r5, #1
	cmp r5, r0
	ble _021DA9FC
_021DAA2A:
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x50]
	str r1, [r0]
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x54]
	str r1, [r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD58_021DA8C4

	thumb_func_start MOD58_021DAA3C
MOD58_021DAA3C: ; 0x021DAA3C
	mov r2, #0
_021DAA3E:
	ldrb r3, [r0, #0x10]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	strh r3, [r1, #2]
	ldrb r3, [r0, #0x10]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	beq _021DAA62
	add r3, r0, r3
	sub r3, r3, #1
	ldrb r3, [r3]
	strb r3, [r1]
	ldrb r3, [r0, #0x10]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	add r3, r0, r3
	ldrb r3, [r3, #7]
	strb r3, [r1, #1]
_021DAA62:
	add r2, r2, #1
	add r0, #0x11
	add r1, r1, #4
	cmp r2, #5
	blt _021DAA3E
	bx lr
	.align 2, 0
	thumb_func_end MOD58_021DAA3C

	thumb_func_start MOD58_021DAA70
MOD58_021DAA70: ; 0x021DAA70
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r7, r0, #0
	mov r0, #0
	str r1, [sp, #0x10]
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	add r5, r1, #0
	add r6, r2, #0
_021DAA86:
	ldrb r0, [r5, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	beq _021DAAEA
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _021DAAA0
	ldrb r0, [r6]
	sub r0, #0x20
	str r0, [sp, #0x28]
	ldrb r0, [r6, #1]
	sub r0, #0x48
	str r0, [sp, #0x24]
_021DAAA0:
	ldrb r0, [r5, #0x10]
	mov r4, #0
	lsl r0, r0, #0x18
	lsr r1, r0, #0x1c
	cmp r1, #0
	ble _021DAAEA
	mov r0, #1
	str r0, [sp, #0x1c]
	cmp r1, #0
	ble _021DAAEA
_021DAAB4:
	add r0, sp, #0x28
	str r0, [sp]
	add r0, sp, #0x24
	str r0, [sp, #4]
	str r4, [sp, #8]
	ldrh r0, [r6, #2]
	add r3, r5, r4
	str r0, [sp, #0xc]
	ldrb r1, [r5, #0x10]
	ldrb r3, [r3, #8]
	add r0, r7, #0
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	lsl r2, r1, #4
	ldr r1, _021DAB2C ; =0x021DAE94
	sub r3, #0x48
	add r1, r1, r2
	ldrb r2, [r5, r4]
	sub r2, #0x20
	bl MOD58_021DA8C4
	ldrb r0, [r5, #0x10]
	add r4, r4, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r4, r0
	blt _021DAAB4
_021DAAEA:
	ldr r0, [sp, #0x20]
	add r5, #0x11
	add r0, r0, #1
	add r6, r6, #4
	str r0, [sp, #0x20]
	cmp r0, #5
	blt _021DAA86
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _021DAB0A
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _021DAB0A
	add r0, r7, #0
	bl CopyWindowToVram
_021DAB0A:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	bl MOD58_021DAA3C
	mov r3, #0
	mov r1, #0xf0
_021DAB16:
	ldr r0, [sp, #0x10]
	add r3, r3, #1
	ldrb r2, [r0, #0x10]
	bic r2, r1
	strb r2, [r0, #0x10]
	add r0, #0x11
	str r0, [sp, #0x10]
	cmp r3, #5
	blt _021DAB16
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DAB2C: .word MOD58_021DAE94
	thumb_func_end MOD58_021DAA70

	thumb_func_start MOD58_021DAB30
MOD58_021DAB30: ; 0x021DAB30
	bx lr
	.align 2, 0
	thumb_func_end MOD58_021DAB30

	thumb_func_start MOD58_021DAB34
MOD58_021DAB34: ; 0x021DAB34
	push {r3, lr}
	ldrh r1, [r0]
	add r1, #0x14
	strh r1, [r0]
	ldrh r2, [r0]
	mov r1, #0x5a
	lsl r1, r1, #2
	cmp r2, r1
	bls _021DAB4A
	mov r1, #0
	strh r1, [r0]
_021DAB4A:
	ldrh r0, [r0]
	bl Sin_Wrap
	mov r1, #0xa
	mul r1, r0
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	add r0, #0xf
	lsl r1, r0, #5
	mov r0, #0x1d
	orr r1, r0
	add r0, sp, #0
	strh r1, [r0]
	add r0, sp, #0
	mov r1, #0x18
	mov r2, #2
	bl GX_LoadOBJPltt
	pop {r3, pc}
	thumb_func_end MOD58_021DAB34

	thumb_func_start MOD58_021DAB74
MOD58_021DAB74: ; 0x021DAB74
	bx lr
	.align 2, 0
	thumb_func_end MOD58_021DAB74

	thumb_func_start MOD58_021DAB78
MOD58_021DAB78: ; 0x021DAB78
	ldr r1, _021DAB90 ; =0x0000431C
	add r3, r0, r1
	add r1, #0x11
	add r2, r0, r1
	mov r1, #0x11
_021DAB82:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021DAB82
	bx lr
	.align 2, 0
_021DAB90: .word 0x0000431C
	thumb_func_end MOD58_021DAB78

	thumb_func_start MOD58_021DAB94
MOD58_021DAB94: ; 0x021DAB94
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x50
	mov r1, #0x27
	bl String_ctor
	add r4, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r6, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x34]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_dtor
	mov r0, #0xb5
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0xf
	bl FUN_02019620
	mov r0, #0xb5
	lsl r0, r0, #2
	add r0, r5, r0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	ldr r0, [r5, #0xc]
	bl Options_GetTextFrameDelay
	mov r3, #0
	str r3, [sp]
	str r0, [sp, #4]
	str r3, [sp, #8]
	mov r0, #0xb5
	lsl r0, r0, #2
	ldr r2, [r5, #0x34]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	str r0, [r5, #0x38]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD58_021DAB94

	thumb_func_start MOD58_021DAC00
MOD58_021DAC00: ; 0x021DAC00
	push {r3, lr}
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021DAC12
	mov r0, #1
	pop {r3, pc}
_021DAC12:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD58_021DAC00

	thumb_func_start MOD58_021DAC18
MOD58_021DAC18: ; 0x021DAC18
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0
	add r5, r0, #0
	str r1, [sp]
	add r4, r7, #0
	strb r7, [r5]
	add r6, r7, #0
_021DAC26:
	ldr r0, [sp]
	ldrb r1, [r0, r6]
	mov r0, #0xf
	and r0, r1
	cmp r0, #1
	bne _021DAC3C
	mov r0, #1
	ldrb r1, [r5]
	lsl r0, r4
	orr r0, r1
	strb r0, [r5]
_021DAC3C:
	ldr r0, [sp]
	ldrb r0, [r0, r6]
	asr r0, r0, #4
	cmp r0, #1
	bne _021DAC52
	ldrb r0, [r5]
	add r2, r4, #1
	mov r1, #1
	lsl r1, r2
	orr r0, r1
	strb r0, [r5]
_021DAC52:
	add r4, r4, #2
	cmp r4, #8
	bne _021DAC62
	mov r0, #0
	add r5, r5, #1
	add r7, r7, #1
	strb r0, [r5]
	add r4, r0, #0
_021DAC62:
	mov r0, #6
	lsl r0, r0, #0xa
	cmp r7, r0
	blt _021DAC6E
	bl ErrorHandling
_021DAC6E:
	mov r0, #6
	add r6, r6, #1
	lsl r0, r0, #0xa
	cmp r6, r0
	blt _021DAC26
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD58_021DAC18

	thumb_func_start MOD58_021DAC7C
MOD58_021DAC7C: ; 0x021DAC7C
	push {r3, r4, r5, lr}
	ldr r1, _021DAD28 ; =gMain + 0x40
	add r4, r0, #0
	ldrh r0, [r1, #0x1c]
	ldr r3, _021DAD2C ; =0x0000FFFF
	cmp r0, r3
	beq _021DAD16
	ldrh r1, [r1, #0x1e]
	cmp r1, r3
	beq _021DAD16
	ldr r2, _021DAD30 ; =0x00005CA8
	ldr r5, [r4, r2]
	cmp r5, r3
	beq _021DAD16
	add r1, r2, #4
	ldr r1, [r4, r1]
	cmp r1, r3
	beq _021DAD16
	cmp r5, r0
	ble _021DACAC
	mov r1, #0
	sub r3, r5, r0
	mvn r1, r1
	b _021DACB0
_021DACAC:
	sub r3, r0, r5
	mov r1, #1
_021DACB0:
	sub r0, r2, #6
	strb r1, [r4, r0]
	cmp r3, #3
	blt _021DACE6
	cmp r3, #0x28
	bgt _021DACE6
	ldr r0, _021DAD28 ; =gMain + 0x40
	ldrh r2, [r0, #0x1e]
	ldr r0, _021DAD34 ; =0x00005CAC
	ldr r1, [r4, r0]
	cmp r1, r2
	ble _021DACD0
	sub r2, r1, r2
	mov r1, #0
	mvn r1, r1
	b _021DACD4
_021DACD0:
	sub r2, r2, r1
	mov r1, #1
_021DACD4:
	sub r0, #9
	strb r1, [r4, r0]
	cmp r2, #0x28
	bgt _021DAD16
	ldr r0, _021DAD38 ; =0x00005CA0
	add r0, r4, r0
	bl MOD58_021DAD3C
	b _021DAD16
_021DACE6:
	cmp r3, #0x28
	bgt _021DAD16
	ldr r0, _021DAD28 ; =gMain + 0x40
	ldrh r2, [r0, #0x1e]
	ldr r0, _021DAD34 ; =0x00005CAC
	ldr r1, [r4, r0]
	cmp r1, r2
	ble _021DACFE
	sub r2, r1, r2
	mov r1, #0
	mvn r1, r1
	b _021DAD02
_021DACFE:
	sub r2, r2, r1
	mov r1, #1
_021DAD02:
	sub r0, #9
	strb r1, [r4, r0]
	cmp r2, #3
	blt _021DAD16
	cmp r2, #0x28
	bgt _021DAD16
	ldr r0, _021DAD38 ; =0x00005CA0
	add r0, r4, r0
	bl MOD58_021DAD3C
_021DAD16:
	ldr r1, _021DAD28 ; =gMain + 0x40
	ldr r0, _021DAD30 ; =0x00005CA8
	ldrh r2, [r1, #0x1c]
	str r2, [r4, r0]
	ldrh r1, [r1, #0x1e]
	add r0, r0, #4
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
	nop
_021DAD28: .word gMain + 0x40
_021DAD2C: .word 0x0000FFFF
_021DAD30: .word 0x00005CA8
_021DAD34: .word 0x00005CAC
_021DAD38: .word 0x00005CA0
	thumb_func_end MOD58_021DAC7C

	thumb_func_start MOD58_021DAD3C
MOD58_021DAD3C: ; 0x021DAD3C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bne _021DAD60
	mov r0, #1
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bne _021DAD60
	ldr r0, _021DAD9C ; =0x0000069A
	bl FUN_02005508
	cmp r0, #0
	bne _021DAD60
	ldr r0, _021DAD9C ; =0x0000069A
	bl FUN_020054C8
_021DAD60:
	mov r0, #0
	ldrsb r1, [r4, r0]
	mov r0, #2
	ldrsb r0, [r4, r0]
	mul r0, r1
	bmi _021DAD78
	mov r0, #1
	ldrsb r1, [r4, r0]
	mov r0, #3
	ldrsb r0, [r4, r0]
	mul r0, r1
	bpl _021DAD88
_021DAD78:
	ldr r0, _021DAD9C ; =0x0000069A
	bl FUN_02005508
	cmp r0, #0
	bne _021DAD88
	ldr r0, _021DAD9C ; =0x0000069A
	bl FUN_020054C8
_021DAD88:
	mov r0, #2
	ldrsb r0, [r4, r0]
	strb r0, [r4]
	mov r0, #3
	ldrsb r0, [r4, r0]
	strb r0, [r4, #1]
	mov r0, #0
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	pop {r4, pc}
	.align 2, 0
_021DAD9C: .word 0x0000069A
	thumb_func_end MOD58_021DAD3C

	.rodata
	.global MOD58_021DADA0
MOD58_021DADA0: ; 0x021DADA0
	.byte 0xE0, 0x00, 0xAF, 0x00, 0x00, 0x00

	.global MOD58_021DADA6
MOD58_021DADA6: ; 0x021DADA6
	.byte 0x48, 0x88, 0x20, 0xE0, 0xFF, 0x00, 0x00, 0x00

	.global MOD58_021DADAE
MOD58_021DADAE: ; 0x021DADAE
	.byte 0x96, 0xBD, 0xC0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x96, 0xBD, 0x00, 0x5F, 0x96, 0xBD, 0x60, 0xBF
	.byte 0x00, 0x00

	.global MOD58_021DADC0
MOD58_021DADC0: ; 0x021DADC0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DADD0
MOD58_021DADD0: ; 0x021DADD0
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00

	.global MOD58_021DADE0
MOD58_021DADE0: ; 0x021DADE0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DADFC
MOD58_021DADFC: ; 0x021DADFC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DAE18
MOD58_021DAE18: ; 0x021DAE18
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DAE34
MOD58_021DAE34: ; 0x021DAE34
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DAE50
MOD58_021DAE50: ; 0x021DAE50
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DAE6C
MOD58_021DAE6C: ; 0x021DAE6C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD58_021DAE94
MOD58_021DAE94: ; 0x021DAE94
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x11, 0x11, 0x10, 0x01, 0x10, 0x11, 0x10, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x22, 0x22, 0x20, 0x02, 0x22, 0x22, 0x20, 0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.global MOD58_021DAFA0
MOD58_021DAFA0: ; 0x021DAFA0
	.word 0x00000000, MOD58_021DA62C, MOD58_021DA6C4, MOD58_021DA6F4
	.word MOD58_021DA7F4, MOD58_021DA814, MOD58_021DA78C, 0x00000000

	.bss
