	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E8310
MOD05_021E8310: ; 0x021E8310
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [r1, #0xc]
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_02034E30
	bl FUN_02034DC0
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Pokedex_get
	add r7, r0, #0
	ldr r0, [r6]
	bl MapHeader_GetMapSec
	str r0, [r5, #4]
	add r0, r7, #0
	bl Pokedex_GetSinnohDexFlag
	cmp r0, #0
	beq _021E8344
	add r0, r7, #0
	bl Pokedex_CountSeenMons
	b _021E8346
_021E8344:
	mov r0, #0
_021E8346:
	str r0, [r5]
	add r0, r4, #0
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r5, #8]
	add r0, r4, #0
	bl Sav2_PlayerData_GetIGTAddr
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E835C
MOD05_021E835C: ; 0x021E835C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r2, [r4, #4]
	mov r1, #0
	add r5, r0, #0
	bl BufferLandmarkName
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl BufferPlayersName
	ldr r0, [r4, #8]
	bl PlayerProfile_CountBadges
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	add r0, r5, #0
	mov r1, #2
	bl BufferIntegerAsString
	ldr r2, [r4]
	cmp r2, #0x64
	blt _021E839A
	mov r3, #3
	mov r0, #0
	b _021E83A8
_021E839A:
	cmp r2, #0xa
	blt _021E83A4
	mov r3, #3
	mov r0, #1
	b _021E83A8
_021E83A4:
	mov r3, #2
	mov r0, #1
_021E83A8:
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #3
	bl BufferIntegerAsString
	ldr r0, [r4, #0xc]
	bl GetIGTHours
	add r2, r0, #0
	cmp r2, #0x64
	blt _021E83C8
	mov r3, #3
	mov r0, #0
	b _021E83D6
_021E83C8:
	cmp r2, #0xa
	blt _021E83D2
	mov r3, #3
	mov r0, #1
	b _021E83D6
_021E83D2:
	mov r3, #2
	mov r0, #1
_021E83D6:
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #4
	bl BufferIntegerAsString
	ldr r0, [r4, #0xc]
	bl GetIGTMinutes
	mov r3, #2
	add r2, r0, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #5
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start MOD05_021E8400
MOD05_021E8400: ; 0x021E8400
	ldr r0, [r0]
	cmp r0, #0
	beq _021E840A
	mov r0, #0xa
	bx lr
_021E840A:
	mov r0, #8
	bx lr
	.balign 4, 0

	thumb_func_start MOD05_021E8410
MOD05_021E8410: ; 0x021E8410
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0
	mov r1, #1
	bl GetFontAttribute
	add r4, r0, #0
	mov r0, #0
	mov r1, #3
	bl GetFontAttribute
	add r0, r4, r0
	str r0, [sp, #0x14]
	mov r4, #0
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r3, [r5, #4]
	add r2, r4, #0
	bl ReadMsgData_ExpandPlaceholders
	add r1, r4, #0
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r5, #0x10]
	add r2, r6, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	mov r0, #1
	str r0, [sp, #0x10]
	ldr r0, _021E84EC ; =UNK05_021F78D4
	ldr r7, _021E84F0 ; =UNK05_021F78C4
	str r0, [sp, #0xc]
_021E8460:
	ldr r0, [sp, #0xc]
	ldr r1, [r0]
	cmp r1, #3
	bne _021E846E
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021E84D6
_021E846E:
	ldr r0, [sp, #0x14]
	add r4, r4, r0
	ldr r0, [r5, #0x18]
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r1, #0
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r5, #0x10]
	add r2, r6, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	sub r2, r7, #4
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	ldr r2, [r2]
	ldr r3, [r5, #4]
	bl ReadMsgData_ExpandPlaceholders
	add r6, r0, #0
	mov r0, #0
	mov r1, #2
	bl GetFontAttribute
	add r2, r0, #0
	mov r0, #0
	add r1, r6, #0
	bl FUN_02002E14
	mov r1, #0x68
	sub r3, r1, r0
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r5, #0x10]
	mov r1, #0
	add r2, r6, #0
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
_021E84D6:
	ldr r0, [sp, #0xc]
	add r7, r7, #4
	add r0, r0, #4
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #5
	blo _021E8460
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E84EC: .word UNK05_021F78D4
_021E84F0: .word UNK05_021F78C4

	thumb_func_start MOD05_021E84F4
MOD05_021E84F4: ; 0x021E84F4
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0x10]
	mov r3, #1
	str r3, [sp]
	ldr r0, [r4, #0x2c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _021E8564 ; =0x0000027F
	str r0, [sp, #0x10]
	ldrb r2, [r4, #8]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	bl AddWindowParameterized
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r2, _021E8568 ; =0x000003D9
	str r0, [sp, #4]
	ldrb r1, [r4, #8]
	ldr r0, [r4, #0xc]
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	mov r1, #6
	bl GetFontAttribute
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	bl FillWindowPixelBuffer
	add r0, r4, #0
	bl MOD05_021E8410
	ldr r0, [r4, #0x10]
	ldr r2, _021E8568 ; =0x000003D9
	mov r1, #0
	mov r3, #0xb
	bl DrawFrameAndWindow1
	add sp, #0x14
	pop {r3, r4, pc}
	.balign 4, 0
_021E8564: .word 0x0000027F
_021E8568: .word 0x000003D9

	thumb_func_start MOD05_021E856C
MOD05_021E856C: ; 0x021E856C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl ClearFrameAndWindow1
	ldr r0, [r4, #0x10]
	bl RemoveWindow
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8588
MOD05_021E8588: ; 0x021E8588
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0x34
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r6, [r4]
	str r5, [r4, #4]
	strb r7, [r4, #8]
	ldr r0, [r6, #8]
	str r0, [r4, #0xc]
	add r0, r5, #0
	bl ScrStrBufs_new
	str r0, [r4, #0x14]
	ldr r2, _021E85E0 ; =0x000001E3
	mov r0, #1
	mov r1, #0x1a
	add r3, r5, #0
	bl NewMsgDataFromNarc
	str r0, [r4, #0x18]
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x1c
	bl MOD05_021E8310
	add r1, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x1c
	bl MOD05_021E835C
	mov r0, #0xd
	str r0, [r4, #0x2c]
	add r0, r4, #0
	add r0, #0x1c
	bl MOD05_021E8400
	str r0, [r4, #0x30]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E85E0: .word 0x000001E3

	thumb_func_start MOD05_021E85E4
MOD05_021E85E4: ; 0x021E85E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	bl DestroyMsgData
	ldr r0, [r4, #0x14]
	bl ScrStrBufs_delete
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start MOD05_021E85FC
MOD05_021E85FC: ; 0x021E85FC
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02034E48
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl MOD05_021EFA9C
	ldr r0, [r4, #0x38]
	bl FUN_02055320
	ldr r1, [r4, #0x1c]
	str r0, [r1, #8]
	ldr r0, [r4, #0x38]
	bl FUN_0205532C
	ldr r1, [r4, #0x1c]
	str r0, [r1, #0xc]
	mov r1, #0
	ldr r0, [r4, #0x1c]
	mvn r1, r1
	str r1, [r0, #4]
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	ldr r1, [r4, #0x1c]
	str r0, [r1, #0x10]
	ldr r0, [r4, #0xc]
	bl FUN_02022720
	cmp r0, #2
	bne _021E8642
	mov r0, #1
	pop {r4, pc}
_021E8642:
	mov r0, #0
	pop {r4, pc}
	.balign 4, 0

	.section .rodata

	.global UNK05_021F78C4
UNK05_021F78C4: ; 0x021F78C4
	.word 0x00000006, 0x00000007, 0x00000008, 0x00000000

	.global UNK05_021F78D4
UNK05_021F78D4: ; 0x021F78D4
	.word 0x00000001, 0x00000002, 0x00000003, 0x00000004
