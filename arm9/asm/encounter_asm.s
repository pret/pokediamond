	.include "asm/macros.inc"
	.include "global.inc"

	.extern Encounter_New
	.extern sub_02046758
	.extern sub_020467FC

	.text

	thumb_func_start sub_02047174
sub_02047174: ; 0x02047174
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r7, r0, #0x0
	add r4, r1, #0x0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	mov r0, #0xb
	add r1, r5, #0x0
	bl BattleSetup_New
	add r5, r0, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl sub_02047F1C
	add r0, r5, #0x0
	bl sub_020475A0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_020475B0
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl Encounter_New
	add r2, r0, #0x0
	ldr r1, _020471BC ; =sub_02046758
	add r0, r7, #0x0
	bl TaskManager_Call
	pop {r3-r7, pc}
	nop
_020471BC: .word sub_02046758

	thumb_func_start sub_020471C0
sub_020471C0: ; 0x020471C0
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	bl TaskManager_GetFieldSystem
	add r7, r0, #0x0
	cmp r4, #0x0
	beq _020471DE
	mov r0, #0xb
	mov r1, #0x5
	bl BattleSetup_New
	b _020471E6
_020471DE:
	mov r0, #0xb
	mov r1, #0x7
	bl BattleSetup_New
_020471E6:
	add r4, r0, #0x0
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl sub_02047BC0
	add r0, r4, #0x0
	bl sub_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl sub_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl Encounter_New
	add r2, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, _0204721C ; =sub_020467FC
	str r5, [r2, #0xc]
	bl TaskManager_Call
	pop {r3-r7, pc}
	nop
_0204721C: .word sub_020467FC

	thumb_func_start sub_02047220
sub_02047220: ; 0x02047220
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl TaskManager_GetEnvironment
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl TaskManager_GetStatePtr
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02047246
	cmp r0, #0x1
	beq _02047258
	b _02047262
_02047246:
	ldr r1, _02047268 ; =sub_02046758
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl TaskManager_Call
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02047262
_02047258:
	add r0, r6, #0x0
	bl sub_0204FF5C
	mov r0, #0x1
	pop {r3-r7, pc}
_02047262:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02047268: .word sub_02046758

	thumb_func_start sub_0204726C
sub_0204726C: ; 0x0204726C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	add r1, r2, #0x0
	bl BattleSetup_New
	add r4, r0, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl sub_02047F1C
	add r0, r4, #0x0
	bl sub_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl sub_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl Encounter_New
	add r2, r0, #0x0
	ldr r1, _020472AC ; =sub_02047220
	add r0, r5, #0x0
	bl FieldSystem_CreateTask
	pop {r4-r6, pc}
	nop
_020472AC: .word sub_02047220

	thumb_func_start sub_020472B0
sub_020472B0: ; 0x020472B0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	add r1, r2, #0x0
	bl BattleSetup_New
	add r4, r0, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	bl sub_02047D48
	add r0, r4, #0x0
	bl sub_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl sub_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl Encounter_New
	add r2, r0, #0x0
	ldr r1, _020472F0 ; =sub_02047220
	add r0, r5, #0x0
	bl FieldSystem_CreateTask
	pop {r4-r6, pc}
	.balign 4
_020472F0: .word sub_02047220

	thumb_func_start sub_020472F4
sub_020472F4: ; 0x020472F4
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r1, #0x0]
	mov r3, #0x4
	ldr r2, [r1, #0x14]
	tst r3, r0
	bne _020473C8
	mov r3, #0x80
	add r5, r0, #0x0
	tst r5, r3
	bne _020473C8
	cmp r0, #0x0
	beq _02047318
	add r3, #0x80
	cmp r0, r3
	beq _02047318
	cmp r0, #0x4a
	bne _02047364
_02047318:
	cmp r2, #0x1
	bne _0204732A
	ldr r0, [r4, #0xc]
	bl Save_GameStats_Get
	mov r1, #0x8
	bl GameStats_AddSpecial
	pop {r3-r5, pc}
_0204732A:
	cmp r2, #0x4
	bne _020473C8
	ldr r0, [r1, #0x8]
	mov r1, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r1, r0, #0x0
	mov r0, #0x0
	bl sub_0206BB48
	cmp r0, #0x0
	ldr r0, [r4, #0xc]
	beq _02047358
	bl Save_GameStats_Get
	mov r1, #0x9
	bl GameStats_AddSpecial
	pop {r3-r5, pc}
_02047358:
	bl Save_GameStats_Get
	mov r1, #0xa
	bl GameStats_AddSpecial
	pop {r3-r5, pc}
_02047364:
	mov r3, #0x1
	tst r3, r0
	bne _02047370
	mov r3, #0x10
	tst r3, r0
	beq _02047382
_02047370:
	cmp r2, #0x1
	bne _020473C8
	ldr r0, [r4, #0xc]
	bl Save_GameStats_Get
	mov r1, #0xb
	bl GameStats_AddSpecial
	pop {r3-r5, pc}
_02047382:
	mov r3, #0x20
	add r5, r0, #0x0
	tst r5, r3
	bne _02047390
	lsl r3, r3, #0x4
	tst r0, r3
	beq _020473C8
_02047390:
	cmp r2, #0x4
	bne _020473C8
	ldr r0, [r1, #0x8]
	mov r1, #0x0
	bl GetPartyMonByIndex
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r1, r0, #0x0
	mov r0, #0x0
	bl sub_0206BB48
	cmp r0, #0x0
	ldr r0, [r4, #0xc]
	beq _020473BE
	bl Save_GameStats_Get
	mov r1, #0x9
	bl GameStats_AddSpecial
	pop {r3-r5, pc}
_020473BE:
	bl Save_GameStats_Get
	mov r1, #0xa
	bl GameStats_AddSpecial
_020473C8:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020473CC
sub_020473CC: ; 0x020473CC
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x4
	ldr r1, [r4, #0x14]
	tst r2, r0
	bne _020473EC
	mov r3, #0x80
	add r2, r0, #0x0
	tst r2, r3
	bne _020473EC
	lsl r2, r3, #0x2
	tst r2, r0
	beq _020473EE
_020473EC:
	b _020474FC
_020473EE:
	cmp r0, #0x0
	beq _02047400
	add r3, #0x80
	cmp r0, r3
	beq _02047400
	cmp r0, #0x4a
	beq _02047400
	cmp r0, #0x20
	bne _020474D2
_02047400:
	cmp r1, #0x1
	bne _02047470
	add r0, r5, #0x0
	add r0, #0x76
	ldrh r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r5, #0x0
	add r0, #0x76
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x76
	ldrh r0, [r0, #0x0]
	cmp r0, #0x5
	blo _020474FC
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetIGTAddr
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r3, #0xb
	str r3, [sp, #0x0]
	lsl r3, r3, #0x5
	ldr r3, [r4, r3]
	lsl r1, r7, #0x10
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x4]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl sub_0202920C
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x2
	bl sub_02028AD4
	add sp, #0xc
	pop {r4-r7, pc}
_02047470:
	cmp r1, #0x4
	bne _020474FC
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x4]
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetIGTAddr
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r3, #0xb
	str r3, [sp, #0x0]
	lsl r3, r3, #0x5
	ldr r3, [r4, r3]
	lsl r1, r7, #0x10
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x8]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl sub_0202918C
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x2
	bl sub_02028AD4
	add sp, #0xc
	pop {r4-r7, pc}
_020474D2:
	mov r2, #0x1
	tst r2, r0
	bne _020474DE
	mov r2, #0x10
	tst r0, r2
	beq _020474FC
_020474DE:
	cmp r1, #0x1
	bne _020474FC
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	ldr r2, [r4, #0x1c]
	add r0, #0x98
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #0xb
	bl sub_020299DC
_020474FC:
	add sp, #0xc
	pop {r4-r7, pc}
