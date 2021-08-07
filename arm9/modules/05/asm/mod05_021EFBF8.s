	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021EFBF8
MOD05_021EFBF8: ; 0x021EFBF8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	bl FUN_020286EC
	mov r1, #0
	bl FUN_0202838C
	add r1, r4, #0
	ldr r0, [r4, #0x34]
	add r1, #0x4c
	mov r2, #4
	bl FUN_020339B4
	cmp r0, #0
	bne _021EFC20
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_021EFC20:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x8c
	str r1, [r0]
	ldr r0, [r4, #0x34]
	bl Sav2_PlayerData_GetOptionsAddr
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	ldr r2, _021EFC6C ; =0x000001E2
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xa
	bl FUN_0200CD68
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	ldr r2, _021EFC70 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #1
	str r0, [r4, #0x48]
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	nop
_021EFC6C: .word 0x000001E2
_021EFC70: .word 0x000003D9

	thumb_func_start MOD05_021EFC74
MOD05_021EFC74: ; 0x021EFC74
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r1, #0
	add r6, r0, #0
	mvn r1, r1
	add r0, #0x8c
	str r1, [r0]
	mov r4, #0
	bl FUN_02030F20
	cmp r0, #0
	ble _021EFCB0
	add r5, r6, #0
_021EFC8E:
	ldr r0, [r5, #0x4c]
	cmp r0, #2
	bne _021EFCA4
	add r0, r6, #0
	add r0, #0x8c
	str r4, [r0]
	lsl r0, r4, #2
	mov r1, #0
	add r0, r6, r0
	str r1, [r0, #0x4c]
	b _021EFCB0
_021EFCA4:
	add r5, r5, #4
	add r4, r4, #1
	bl FUN_02030F20
	cmp r4, r0
	blt _021EFC8E
_021EFCB0:
	add r0, r6, #0
	add r0, #0x8c
	ldr r1, [r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _021EFCC4
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021EFCC4:
	ldr r0, [r6, #0x34]
	bl Sav2_Bag_get
	ldr r1, _021EFD3C ; =0x000001B5
	mov r2, #1
	mov r3, #4
	bl Bag_HasItem
	cmp r0, #1
	bne _021EFCFE
	add r0, r6, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r6, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r6, #0
	mov r1, #0x21
	bl MOD05_021F01EC
	mov r0, #2
	str r0, [r6, #0x48]
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EFCFE:
	ldr r0, [r6, #0x34]
	bl FUN_020286EC
	add r4, r0, #0
	mov r5, #0
_021EFD08:
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _021EFD2A
	mov r0, #0
	add r1, r6, #0
	str r0, [sp]
	add r1, #0x8c
	ldr r0, [r6, #0x34]
	ldr r1, [r1]
	add r2, r5, #0
	mov r3, #4
	bl FUN_02033A70
	b _021EFD30
_021EFD2A:
	add r5, r5, #1
	cmp r5, #0x20
	blt _021EFD08
_021EFD30:
	mov r0, #1
	str r0, [r6, #0x48]
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021EFD3C: .word 0x000001B5

	thumb_func_start MOD05_021EFD40
MOD05_021EFD40: ; 0x021EFD40
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021EFD6C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021EFD74 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021EFD78 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #3
	str r0, [r4, #0x48]
_021EFD6C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EFD74: .word UNK05_021F8B44
_021EFD78: .word 0x000003D9

	thumb_func_start MOD05_021EFD7C
MOD05_021EFD7C: ; 0x021EFD7C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021EFD98
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EFD98:
	cmp r0, #0
	bne _021EFDE4
	ldr r0, [r6, #0x34]
	bl FUN_020286EC
	add r5, r0, #0
	mov r4, #0
_021EFDA6:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	bne _021EFDC8
	mov r0, #0
	add r1, r6, #0
	str r0, [sp]
	add r1, #0x8c
	ldr r0, [r6, #0x34]
	ldr r1, [r1]
	add r2, r4, #0
	mov r3, #4
	bl FUN_02033A70
	b _021EFDCE
_021EFDC8:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021EFDA6
_021EFDCE:
	cmp r4, #0x20
	bne _021EFDE4
	add r0, r6, #0
	mov r1, #0x22
	bl MOD05_021F01EC
	mov r0, #4
	str r0, [r6, #0x48]
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_021EFDE4:
	mov r0, #1
	str r0, [r6, #0x48]
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EFDF0
MOD05_021EFDF0: ; 0x021EFDF0
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021EFE1C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021EFE24 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021EFE28 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #5
	str r0, [r4, #0x48]
_021EFE1C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EFE24: .word UNK05_021F8B44
_021EFE28: .word 0x000003D9

	thumb_func_start MOD05_021EFE2C
MOD05_021EFE2C: ; 0x021EFE2C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021EFE44
	mov r0, #0
	pop {r4, pc}
_021EFE44:
	cmp r0, #0
	bne _021EFE4C
	mov r0, #8
	b _021EFE6A
_021EFE4C:
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r4, #0
	mov r1, #0x23
	bl MOD05_021F01EC
	mov r0, #6
_021EFE6A:
	str r0, [r4, #0x48]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021EFE70
MOD05_021EFE70: ; 0x021EFE70
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021EFE9C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021EFEA4 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021EFEA8 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #7
	str r0, [r4, #0x48]
_021EFE9C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021EFEA4: .word UNK05_021F8B44
_021EFEA8: .word 0x000003D9

	thumb_func_start MOD05_021EFEAC
MOD05_021EFEAC: ; 0x021EFEAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021EFEC4
	mov r0, #0
	pop {r4, pc}
_021EFEC4:
	cmp r0, #0
	bne _021EFECC
	mov r0, #0xc
	b _021EFED6
_021EFECC:
	add r0, r4, #0
	mov r1, #0x22
	bl MOD05_021F01EC
	mov r0, #4
_021EFED6:
	str r0, [r4, #0x48]
	mov r0, #0
	pop {r4, pc}

	thumb_func_start MOD05_021EFEDC
MOD05_021EFEDC: ; 0x021EFEDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	bl FUN_020286EC
	add r6, r0, #0
	bl FUN_02028448
	add r7, r0, #0
	add r0, r7, #1
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5]
	mov r0, #1
	str r0, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021EFFB8 ; =0x000002A1
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x30]
	add r1, #0x20
	ldr r0, [r0, #8]
	mov r2, #3
	mov r3, #0x13
	bl AddWindowParameterized
	add r0, r5, #0
	ldr r2, _021EFFBC ; =0x000003D9
	add r0, #0x20
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r4, #0
_021EFF2E:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0202842C
	cmp r0, #0
	beq _021EFF54
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_020283A4
	add r1, r0, #0
	ldr r0, [r5, #8]
	bl CopyU16ArrayToString
	ldr r0, [r5]
	ldr r1, [r5, #8]
	add r2, r4, #0
	bl ListMenuItems_AddItem
_021EFF54:
	add r4, r4, #1
	cmp r4, #0x20
	blt _021EFF2E
	mov r2, #0xb
	add r3, r2, #0
	ldr r0, [r5]
	ldr r1, [r5, #0x3c]
	sub r3, #0xd
	bl ListMenuItems_AppendFromMsgData
	ldr r4, _021EFFC0 ; =UNK05_021F8B4C
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r1, r7, #1
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	mov r1, #5
	strh r1, [r0, #0x12]
	ldr r0, [r5]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x20
	str r0, [sp, #0x20]
	ldr r0, _021EFFC4 ; =MOD05_021F0304
	str r5, [sp, #0x30]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r2, r1, #0
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #4]
	add r0, r5, #0
	add r0, #0x20
	bl CopyWindowToVram
	mov r0, #9
	str r0, [r5, #0x48]
	mov r0, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021EFFB8: .word 0x000002A1
_021EFFBC: .word 0x000003D9
_021EFFC0: .word UNK05_021F8B4C
_021EFFC4: .word MOD05_021F0304

	thumb_func_start MOD05_021EFFC8
MOD05_021EFFC8: ; 0x021EFFC8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _021EFFE6
	add r0, r0, #1
	cmp r4, r0
	bne _021F000E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EFFE6:
	ldr r0, _021F007C ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0x23
	bl MOD05_021F01EC
	mov r0, #6
	str r0, [r5, #0x48]
	b _021F0056
_021F000E:
	ldr r0, _021F007C ; =0x000005DC
	bl PlaySE
	add r0, r5, #0
	add r0, #0x90
	str r4, [r0]
	ldr r0, [r5, #0x34]
	bl FUN_020286EC
	add r7, r0, #0
	mov r0, #4
	bl PlayerProfile_new
	add r6, r0, #0
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_020283A4
	add r1, r0, #0
	add r0, r6, #0
	bl CopyPlayerName
	ldr r0, [r5, #0x38]
	mov r1, #0
	add r2, r6, #0
	bl BufferPlayersName
	add r0, r6, #0
	bl FreeToHeap
	add r0, r5, #0
	mov r1, #0x24
	bl MOD05_021F01EC
	mov r0, #0xa
	str r0, [r5, #0x48]
_021F0056:
	add r0, r5, #0
	add r0, #0x20
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r5, #0
	add r0, #0x20
	bl RemoveWindow
	mov r1, #0
	ldr r0, [r5, #4]
	add r2, r1, #0
	bl DestroyListMenu
	ldr r0, [r5]
	bl ListMenuItems_dtor
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F007C: .word 0x000005DC

	thumb_func_start MOD05_021F0080
MOD05_021F0080: ; 0x021F0080
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021F00AC
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0x30]
	ldr r1, _021F00B4 ; =UNK05_021F8B44
	ldr r0, [r0, #8]
	ldr r2, _021F00B8 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x44]
	mov r0, #0xb
	str r0, [r4, #0x48]
_021F00AC:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_021F00B4: .word UNK05_021F8B44
_021F00B8: .word 0x000003D9

	thumb_func_start MOD05_021F00BC
MOD05_021F00BC: ; 0x021F00BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	bl FUN_020286EC
	add r4, r0, #0
	ldr r0, [r5, #0x44]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _021F00DC
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F00DC:
	cmp r0, #0
	bne _021F0104
	add r1, r5, #0
	add r1, #0x90
	ldr r1, [r1]
	add r0, r4, #0
	bl FUN_02028468
	mov r0, #0
	add r1, r5, #0
	str r0, [sp]
	add r1, #0x8c
	ldr r0, [r5, #0x34]
	ldr r1, [r1]
	mov r2, #0x1f
	mov r3, #4
	bl FUN_02033A70
	mov r0, #1
	b _021F0122
_021F0104:
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r2, r0, #0
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl BufferPlayersName
	add r0, r5, #0
	mov r1, #0x23
	bl MOD05_021F01EC
	mov r0, #6
_021F0122:
	str r0, [r5, #0x48]
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F0128
MOD05_021F0128: ; 0x021F0128
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_0204652C

	thumb_func_start MOD05_021F0130
MOD05_021F0130: ; 0x021F0130
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_02046528
	ldr r0, [r4, #0x48]
	cmp r0, #0xc
	bhi _021F01E8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021F014A: ; jump table
	.short _021F0164 - _021F014A - 2 ; case 0
	.short _021F0174 - _021F014A - 2 ; case 1
	.short _021F0184 - _021F014A - 2 ; case 2
	.short _021F018C - _021F014A - 2 ; case 3
	.short _021F0194 - _021F014A - 2 ; case 4
	.short _021F019C - _021F014A - 2 ; case 5
	.short _021F01A4 - _021F014A - 2 ; case 6
	.short _021F01AC - _021F014A - 2 ; case 7
	.short _021F01B4 - _021F014A - 2 ; case 8
	.short _021F01BC - _021F014A - 2 ; case 9
	.short _021F01C4 - _021F014A - 2 ; case 10
	.short _021F01CC - _021F014A - 2 ; case 11
	.short _021F01D4 - _021F014A - 2 ; case 12
_021F0164:
	add r0, r4, #0
	bl MOD05_021EFBF8
	cmp r0, #0
	beq _021F01E8
	mov r0, #0xc
	str r0, [r4, #0x48]
	b _021F01E8
_021F0174:
	add r0, r4, #0
	bl MOD05_021EFC74
	cmp r0, #0
	beq _021F01E8
	mov r0, #0xc
	str r0, [r4, #0x48]
	b _021F01E8
_021F0184:
	add r0, r4, #0
	bl MOD05_021EFD40
	b _021F01E8
_021F018C:
	add r0, r4, #0
	bl MOD05_021EFD7C
	b _021F01E8
_021F0194:
	add r0, r4, #0
	bl MOD05_021EFDF0
	b _021F01E8
_021F019C:
	add r0, r4, #0
	bl MOD05_021EFE2C
	b _021F01E8
_021F01A4:
	add r0, r4, #0
	bl MOD05_021EFE70
	b _021F01E8
_021F01AC:
	add r0, r4, #0
	bl MOD05_021EFEAC
	b _021F01E8
_021F01B4:
	add r0, r4, #0
	bl MOD05_021EFEDC
	b _021F01E8
_021F01BC:
	add r0, r4, #0
	bl MOD05_021EFFC8
	b _021F01E8
_021F01C4:
	add r0, r4, #0
	bl MOD05_021F0080
	b _021F01E8
_021F01CC:
	add r0, r4, #0
	bl MOD05_021F00BC
	b _021F01E8
_021F01D4:
	add r0, r4, #0
	bl MOD05_021F0290
	add r0, r4, #0
	bl FreeToHeap
	bl FUN_02037778
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F01E8:
	mov r0, #0
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021F01EC
MOD05_021F01EC: ; 0x021F01EC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	add r0, #0x10
	add r5, r1, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _021F0204
	add r0, r4, #0
	add r0, #0x10
	bl RemoveWindow
_021F0204:
	ldr r0, [r4, #0x3c]
	ldr r2, [r4, #8]
	add r1, r5, #0
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #8]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0x30]
	add r1, r4, #0
	ldr r0, [r0, #8]
	add r1, #0x10
	mov r2, #3
	bl FUN_020545B8
	ldr r0, [r4, #0x30]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02054608
	ldr r0, [r4, #0x30]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0
	add r0, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x10
	mov r3, #1
	bl FUN_02054658
	str r0, [r4, #0x40]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F0254
MOD05_021F0254: ; 0x021F0254
	push {r4, lr}
	mov r1, #0
	mov r2, #0x94
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r4, #0x38]
	ldr r2, _021F028C ; =0x00000251
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x3c]
	mov r0, #0x6e
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0xc]
	mov r0, #0x6e
	mov r1, #4
	bl String_ctor
	str r0, [r4, #8]
	pop {r4, pc}
	.balign 4, 0
_021F028C: .word 0x00000251

	thumb_func_start MOD05_021F0290
MOD05_021F0290: ; 0x021F0290
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	bl DestroyMsgData
	ldr r0, [r4, #0x38]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0xc]
	bl String_dtor
	ldr r0, [r4, #8]
	bl String_dtor
	add r0, r4, #0
	add r0, #0x10
	bl WindowIsInUse
	cmp r0, #0
	beq _021F02C0
	add r4, #0x10
	add r0, r4, #0
	bl RemoveWindow
_021F02C0:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021F02C4
MOD05_021F02C4: ; 0x021F02C4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r5, [r6, #0x10]
	mov r0, #0xb
	mov r1, #0x94
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	bl MOD05_021F0254
	str r6, [r4, #0x30]
	ldr r0, [r6, #0xc]
	str r0, [r4, #0x34]
	mov r0, #0
	str r0, [r4, #0x48]
	cmp r5, #0
	bne _021F02F2
	ldr r1, _021F0300 ; =MOD05_021F0128
	add r0, r6, #0
	add r2, r4, #0
	bl FUN_020463CC
	pop {r4, r5, r6, pc}
_021F02F2:
	ldr r1, _021F0300 ; =MOD05_021F0128
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	pop {r4, r5, r6, pc}
	nop
_021F0300: .word MOD05_021F0128

	thumb_func_start MOD05_021F0304
MOD05_021F0304: ; 0x021F0304
	push {r3, lr}
	cmp r2, #0
	bne _021F0310
	ldr r0, _021F0314 ; =0x000005DC
	bl PlaySE
_021F0310:
	pop {r3, pc}
	nop
_021F0314: .word 0x000005DC

	.section .rodata

	.global UNK05_021F8B44
UNK05_021F8B44: ; 0x021F8B44
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global UNK05_021F8B4C
UNK05_021F8B4C: ; 0x021F8B4C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
