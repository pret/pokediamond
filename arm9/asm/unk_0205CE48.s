	.include "asm/macros.inc"
	.include "global.inc"

	.extern gSystem
	.extern UNK_020F96DC

	.section .rodata

	.global UNK_020F7260
UNK_020F7260: ; 0x020F7260
	.word 0x00000000, sub_0205D8B8, 0x00000000
	.word sub_0205D024, 0x00000000, 0x00000000
	.word sub_0205D0BC, sub_0205D0EC, 0x00000000
	.word sub_0205D104, sub_0205D144, sub_0205D170
	.word sub_0205D21C, sub_0205D250, sub_0205D328
	.word sub_0205D3B8, sub_0205D3E4, 0x00000000
	.word sub_0205D400, 0x00000000, 0x00000000
	.word sub_0205D498, 0x00000000, 0x00000000
	.word sub_0205D4E8, 0x00000000, sub_0205D4E4
	.word sub_0205D528, sub_0205D558, 0x00000000
	.word sub_0205D574, sub_0205D5A8, 0x00000000
	.word sub_0205D5C4, sub_0205D604, sub_0205D628
	.word sub_0205D660, sub_0205D670, sub_0205D680
	.word sub_0205D69C, 0x00000000, sub_0205D6AC
	.word sub_0205D6BC, 0x00000000, 0x00000000
	.word sub_0205D714, sub_0205D724, sub_0205D734
	.word sub_0205D74C, sub_0205D788, sub_0205D860
	.word sub_0205D7A8, sub_0205D7E4, sub_0205D860
	.word sub_0205D804, sub_0205D840, sub_0205D860
	.word 0x00000000, sub_0205D8B8, 0x00000000
	.word sub_0205D9A8, 0x00000000, 0x00000000
	.word sub_0205DA3C, 0x00000000, sub_0205DA80
	.word sub_0205DACC, sub_0205DADC, sub_0205DAEC

	.text

	thumb_func_start sub_0205CE48
sub_0205CE48: ; 0x0205CE48
	cmp r0, #0x0
	bne _0205CE58
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, _0205CE74 ; =UNK_020F7260
	ldr r0, [r0, r2]
	bx lr
_0205CE58:
	cmp r0, #0x1
	bne _0205CE68
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, _0205CE78 ; =UNK_020F7260 + 4
	ldr r0, [r0, r2]
	bx lr
_0205CE68:
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, _0205CE7C ; =UNK_020F7260 + 8
	ldr r0, [r0, r2]
	bx lr
	.balign 4
_0205CE74: .word UNK_020F7260
_0205CE78: .word UNK_020F7260 + 4
_0205CE7C: .word UNK_020F7260 + 8

	thumb_func_start sub_0205CE80
sub_0205CE80: ; 0x0205CE80
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	str r4, [r5, #0x18]
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x0]
	ldr r0, [r4, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205ED3C
	str r0, [r5, #0x4]
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetState
	str r0, [r5, #0x8]
	ldr r0, [r4, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0x0
	ldr r0, [r4, #0x38]
	bl GetPlayerYCoord
	add r7, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl sub_0204A6E0
	strh r0, [r5, #0xe]
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0x3
	bhi _0205CEEA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205CED4: ; jump table (using 16-bit offset)
	.short _0205CEDC - _0205CED4 - 2; case 0
	.short _0205CEE0 - _0205CED4 - 2; case 1
	.short _0205CEE8 - _0205CED4 - 2; case 2
	.short _0205CEE4 - _0205CED4 - 2; case 3
_0205CEDC:
	sub r7, r7, #0x1
	b _0205CEEA
_0205CEE0:
	add r7, r7, #0x1
	b _0205CEEA
_0205CEE4:
	add r6, r6, #0x1
	b _0205CEEA
_0205CEE8:
	sub r6, r6, #0x1
_0205CEEA:
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl sub_0204A6E0
	strh r0, [r5, #0xc]
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl sub_02037024
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl sub_0204B6C4
	strh r0, [r5, #0x10]
	ldr r0, [r4, #0x38]
	str r0, [r5, #0x14]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205CF10
sub_0205CF10: ; 0x0205CF10
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x20
	mov r1, #0xc
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl AllocFromHeap
	str r5, [r0, #0x0]
	strh r4, [r0, #0x4]
	strh r6, [r0, #0x6]
	strh r7, [r0, #0x8]
	add r1, sp, #0x8
	ldrh r1, [r1, #0x10]
	strh r1, [r0, #0xa]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205CF34
sub_0205CF34: ; 0x0205CF34
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r6, r2, #0x0
	bl TaskManager_GetFieldSystem
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl sub_0204649C
	mov r0, #0x72
	mov r2, #0x0
	ldr r1, _0205CF74 ; =sub_0205CFA0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	str r2, [sp, #0x0]
	ldrh r1, [r5, #0x4]
	add r0, r6, #0x0
	add r3, r2, #0x0
	bl sub_0205CF10
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r3-r7, pc}
	nop
_0205CF74: .word sub_0205CFA0

	thumb_func_start sub_0205CF78
sub_0205CF78: ; 0x0205CF78
	push {r3-r4, lr}
	sub sp, #0x4
	mov r2, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	add r0, r1, #0x0
	ldrh r1, [r4, #0x28]
	add r3, r2, #0x0
	bl sub_0205CF10
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, _0205CF9C ; =sub_0205CFA0
	bl sub_020463CC
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_0205CF9C: .word sub_0205CFA0

	thumb_func_start sub_0205CFA0
sub_0205CFA0: ; 0x0205CFA0
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl sub_02046530
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0205CFC6
	cmp r0, #0x1
	beq _0205D016
	b _0205D020
_0205CFC6:
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl sub_02037024
	ldr r1, [r4, #0x0]
	ldr r2, [sp, #0x0]
	lsl r1, r1, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	mov r3, #0x0
	bl sub_02038CD8
	add r0, r5, #0x0
	mov r1, #0x29
	bl FieldSysGetAttrAddr
	ldrh r1, [r4, #0x4]
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2a
	bl FieldSysGetAttrAddr
	ldrh r1, [r4, #0x6]
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2b
	bl FieldSysGetAttrAddr
	ldrh r1, [r4, #0x8]
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2c
	bl FieldSysGetAttrAddr
	ldrh r1, [r4, #0xa]
	strh r1, [r0, #0x0]
	ldr r0, [r6, #0x0]
	add r0, r0, #0x1
	str r0, [r6, #0x0]
	b _0205D020
_0205D016:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_0205D020:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_0205D024
sub_0205D024: ; 0x0205D024
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r6, #0x0]
	bl sub_0204652C
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_Mailbox_Get
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl Save_SafariZone_Get
	str r0, [r4, #0x10]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r7, r0
	str r0, [r4, #0x18]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x5
	add r0, #0x20
	strb r1, [r0, #0x0]
	str r5, [r4, #0x1c]
	ldrh r0, [r6, #0x4]
	add r2, r4, #0x0
	strh r0, [r4, #0x24]
	add r0, r4, #0x0
	ldrb r1, [r6, #0x6]
	add r0, #0x22
	strb r1, [r0, #0x0]
	ldr r1, _0205D0B4 ; =UNK_020F96DC
	add r0, r5, #0x0
	bl sub_020373D4
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r4, [r7, r0]
	ldr r1, _0205D0B8 ; =sub_02035E50
	add r0, r7, #0x0
	bl sub_02035D04
	pop {r3-r7, pc}
	nop
_0205D0B4: .word UNK_020F96DC
_0205D0B8: .word sub_02035E50

	thumb_func_start sub_0205D0BC
sub_0205D0BC: ; 0x0205D0BC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02037EB8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _0205D0E8 ; =sub_02036A78
	add r0, r4, #0x0
	bl sub_02035D04
	pop {r3-r5, pc}
	nop
_0205D0E8: .word sub_02036A78

	thumb_func_start sub_0205D0EC
sub_0205D0EC: ; 0x0205D0EC
	push {r3, lr}
	ldr r1, _0205D0F8 ; =sub_0205D0FC
	bl sub_0205DD04
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0205D0F8: .word sub_0205D0FC

	thumb_func_start sub_0205D0FC
sub_0205D0FC: ; 0x0205D0FC
	ldr r3, _0205D100 ; =sub_02037EB8
	bx r3
	.balign 4
_0205D100: .word sub_02037EB8

	thumb_func_start sub_0205D104
sub_0205D104: ; 0x0205D104
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205D140 ; =sub_02049844
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r5, #0x0
	bl sub_0204976C
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	mov r0, #0x0
	add r5, #0x8c
	str r0, [r5, #0x0]
	pop {r3-r5, pc}
	nop
_0205D140: .word sub_02049844

	thumb_func_start sub_0205D144
sub_0205D144: ; 0x0205D144
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204976C
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x34]
	bl sub_02058780
	ldr r0, [r5, #0x0]
	ldr r1, _0205D16C ; =sub_02049844
	add r2, r4, #0x0
	bl sub_020463CC
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	add r1, #0x8c
	str r0, [r1, #0x0]
	pop {r3-r5, pc}
	.balign 4
_0205D16C: .word sub_02049844

	thumb_func_start sub_0205D170
sub_0205D170: ; 0x0205D170
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl MapHeader_GetMapSec
	cmp r0, #0x0
	bne _0205D184
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D184:
	ldr r0, [r5, #0x0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0x0
	bne _0205D194
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D194:
	ldr r0, [r5, #0x14]
	bl sub_02055738
	cmp r0, #0x1
	bne _0205D1A4
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D1A4:
	ldr r0, [r5, #0x18]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F214
	cmp r0, #0x1
	beq _0205D1C4
	ldr r0, [r5, #0x18]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F244
	cmp r0, #0x1
	bne _0205D1CA
_0205D1C4:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D1CA:
	ldr r0, [r5, #0x14]
	bl PlayerAvatar_GetState
	cmp r0, #0x2
	bne _0205D1DA
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D1DA:
	ldrh r0, [r5, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02054B78
	cmp r0, #0x1
	bne _0205D1EE
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D1EE:
	ldr r0, [r5, #0x18]
	ldr r0, [r0, #0x38]
	bl GetPlayerXCoord
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, #0x18]
	ldr r0, [r0, #0x38]
	bl GetPlayerYCoord
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	ldr r0, [r5, #0x18]
	add r1, r4, #0x0
	bl sub_02034D44
	cmp r0, #0x0
	bne _0205D218
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D218:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0205D21C
sub_0205D21C: ; 0x0205D21C
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205D24C ; =sub_0205D264
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	str r1, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r3-r5, pc}
	nop
_0205D24C: .word sub_0205D264

	thumb_func_start sub_0205D250
sub_0205D250: ; 0x0205D250
	push {r3, lr}
	ldr r0, [r0, #0x0]
	ldr r1, _0205D260 ; =sub_0205D264
	mov r2, #0x0
	bl sub_020463CC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205D260: .word sub_0205D264

	thumb_func_start sub_0205D264
sub_0205D264: ; 0x0205D264
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046530
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x3
	bhi _0205D324
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0205D288: ; jump table (using 16-bit offset)
	.short _0205D290 - _0205D288 - 2; case 0
	.short _0205D296 - _0205D288 - 2; case 1
	.short _0205D314 - _0205D288 - 2; case 2
	.short _0205D31A - _0205D288 - 2; case 3
_0205D290:
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _0205D324
_0205D296:
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetState
	cmp r0, #0x1
	bne _0205D2D6
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetMapObject
	bl sub_02058914
	ldr r0, [r4, #0x38]
	mov r1, #0x1
	bl Field_PlayerAvatar_OrrTransitionFlags
	ldr r0, [r4, #0x38]
	bl Field_PlayerAvatar_ApplyTransitionFlags
	add r0, r4, #0x0
	mov r1, #0x0
	bl FieldSystem_SetSavedMusicId
	ldr r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	bl FieldSystem_GetOverriddenMusicId
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FieldSystem_PlayOrFadeToNewMusicId
	b _0205D30C
_0205D2D6:
	mov r1, #0x12
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	bl FieldSystem_SetSavedMusicId
	mov r1, #0x12
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	mov r2, #0x1
	bl FieldSystem_PlayOrFadeToNewMusicId
	ldr r0, [r4, #0x38]
	bl PlayerAvatar_GetMapObject
	bl sub_02058914
	ldr r0, [r4, #0x38]
	mov r1, #0x2
	bl Field_PlayerAvatar_OrrTransitionFlags
	ldr r0, [r4, #0x38]
	bl Field_PlayerAvatar_ApplyTransitionFlags
	add r4, #0x90
	ldr r0, [r4, #0x0]
	bl sub_0205DD40
_0205D30C:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _0205D324
_0205D314:
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _0205D324
_0205D31A:
	ldr r0, [r4, #0x34]
	bl sub_020587B0
	mov r0, #0x1
	pop {r3-r5, pc}
_0205D324:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0205D328
sub_0205D328: ; 0x0205D328
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0205D336
	mov r0, #0x2
	pop {r3-r5, pc}
_0205D336:
	ldr r0, [r4, #0x14]
	bl sub_02055738
	cmp r0, #0x1
	bne _0205D344
	mov r0, #0x1
	pop {r3-r5, pc}
_0205D344:
	ldr r0, [r4, #0x14]
	bl PlayerAvatar_GetMapObject
	ldrh r1, [r4, #0xe]
	add r5, r0, #0x0
	bl sub_02059BB4
	cmp r0, #0x1
	beq _0205D362
	ldrh r1, [r4, #0xe]
	add r0, r5, #0x0
	bl sub_02059BD4
	cmp r0, #0x1
	bne _0205D366
_0205D362:
	mov r0, #0x1
	pop {r3-r5, pc}
_0205D366:
	ldrh r0, [r4, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02054798
	cmp r0, #0x1
	beq _0205D390
	ldrh r0, [r4, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02054974
	cmp r0, #0x1
	beq _0205D390
	ldrh r0, [r4, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02054990
	cmp r0, #0x1
	bne _0205D396
_0205D390:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D396:
	ldr r0, [r4, #0x0]
	bl MapHeader_IsBikeAllowed
	cmp r0, #0x0
	bne _0205D3A6
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D3A6:
	ldr r0, [r4, #0x8]
	cmp r0, #0x2
	bne _0205D3B2
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205D3B2:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0205D3B8
sub_0205D3B8: ; 0x0205D3B8
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl sub_02037944
	ldr r1, _0205D3E0 ; =sub_02036B90
	add r0, r4, #0x0
	bl sub_02035D04
	pop {r3-r5, pc}
	nop
_0205D3E0: .word sub_02036B90

	thumb_func_start sub_0205D3E4
sub_0205D3E4: ; 0x0205D3E4
	push {r3, lr}
	ldr r1, _0205D3F0 ; =sub_0205D3F4
	bl sub_0205DD04
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0205D3F0: .word sub_0205D3F4

	thumb_func_start sub_0205D3F4
sub_0205D3F4: ; 0x0205D3F4
	push {r3, lr}
	mov r1, #0x0
	bl sub_02037944
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_0205D400
sub_0205D400: ; 0x0205D400
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r6, #0x0]
	bl sub_0204652C
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_Mailbox_Get
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r7, r0
	str r0, [r4, #0x18]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x6
	add r0, #0x20
	strb r1, [r0, #0x0]
	str r5, [r4, #0x1c]
	ldrh r0, [r6, #0x4]
	strh r0, [r4, #0x24]
	add r0, r4, #0x0
	ldrb r1, [r6, #0x6]
	add r0, #0x22
	strb r1, [r0, #0x0]
	ldrh r0, [r6, #0x4]
	bl TMHMGetMove
	strh r0, [r4, #0x26]
	ldr r1, _0205D490 ; =UNK_020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r4, [r7, r0]
	ldr r1, _0205D494 ; =sub_02035E50
	add r0, r7, #0x0
	bl sub_02035D04
	pop {r3-r7, pc}
	nop
_0205D490: .word UNK_020F96DC
_0205D494: .word sub_02035E50

	thumb_func_start sub_0205D498
sub_0205D498: ; 0x0205D498
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	ldrh r0, [r5, #0x4]
	bl ItemToMailId
	add r2, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x3
	mov r3, #0xb
	bl sub_02037F58
	add r6, r0, #0x0
	ldrh r0, [r5, #0x4]
	mov r1, #0x3
	mov r2, #0x0
	bl sub_02036BC4
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	sub r0, r1, #0x4
	str r6, [r4, r0]
	ldr r1, _0205D4E0 ; =sub_02036BDC
	add r0, r4, #0x0
	bl sub_02035D04
	pop {r4-r6, pc}
	nop
_0205D4E0: .word sub_02036BDC

	thumb_func_start sub_0205D4E4
sub_0205D4E4: ; 0x0205D4E4
	mov r0, #0x0
	bx lr

	thumb_func_start sub_0205D4E8
sub_0205D4E8: ; 0x0205D4E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	bl TaskManager_GetFieldSystem
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	ldrh r1, [r4, #0x10]
	mov r0, #0x1
	tst r0, r1
	beq _0205D50E
	ldr r2, _0205D518 ; =0x00000AF1
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205CF34
	pop {r3-r5, pc}
_0205D50E:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205D024
	pop {r3-r5, pc}
	.balign 4
_0205D518: .word 0x00000AF1

	thumb_func_start sub_0205D51C
sub_0205D51C: ; 0x0205D51C
	ldrh r1, [r0, #0x10]
	mov r0, #0x1
	tst r1, r0
	bne _0205D526
	mov r0, #0x0
_0205D526:
	bx lr

	thumb_func_start sub_0205D528
sub_0205D528: ; 0x0205D528
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xb
	bl sub_02037FC4
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _0205D554 ; =sub_02036D94
	add r0, r4, #0x0
	bl sub_02035D04
	pop {r3-r5, pc}
	.balign 4
_0205D554: .word sub_02036D94

	thumb_func_start sub_0205D558
sub_0205D558: ; 0x0205D558
	push {r3, lr}
	ldr r1, _0205D564 ; =sub_0205D568
	bl sub_0205DD04
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0205D564: .word sub_0205D568

	thumb_func_start sub_0205D568
sub_0205D568: ; 0x0205D568
	ldr r3, _0205D570 ; =sub_02037FC4
	mov r1, #0xb
	bx r3
	nop
_0205D570: .word sub_02037FC4

	thumb_func_start sub_0205D574
sub_0205D574: ; 0x0205D574
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r1, [r5, #0xc]
	add r0, r5, #0x0
	bl sub_0203846C
	mov r0, #0x7e
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	ldr r1, _0205D5A4 ; =sub_02036DD4
	add r0, r4, #0x0
	bl sub_02035D04
	pop {r3-r5, pc}
	nop
_0205D5A4: .word sub_02036DD4

	thumb_func_start sub_0205D5A8
sub_0205D5A8: ; 0x0205D5A8
	push {r3, lr}
	ldr r1, _0205D5B4 ; =sub_0205D5B8
	bl sub_0205DD04
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0205D5B4: .word sub_0205D5B8

	thumb_func_start sub_0205D5B8
sub_0205D5B8: ; 0x0205D5B8
	push {r3, lr}
	ldr r1, [r0, #0xc]
	bl sub_0203846C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_0205D5C4
sub_0205D5C4: ; 0x0205D5C4
	push {r4-r6, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	add r0, r6, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205D600 ; =sub_0205E30C
	lsl r0, r0, #0x2
	str r1, [r5, r0]
	add r0, #0x30
	str r4, [r5, r0]
	mov r0, #0xa
	strh r0, [r5, #0x2a]
	pop {r4-r6, pc}
	nop
_0205D600: .word sub_0205E30C

	thumb_func_start sub_0205D604
sub_0205D604: ; 0x0205D604
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, _0205D624 ; =sub_0205E30C
	bl sub_020463CC
	mov r0, #0x0
	pop {r4, pc}
	nop
_0205D624: .word sub_0205E30C

	thumb_func_start sub_0205D628
sub_0205D628: ; 0x0205D628
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0205D636
	mov r0, #0x2
	pop {r4, pc}
_0205D636:
	ldr r0, [r4, #0x18]
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetState
	cmp r0, #0x1
	bne _0205D648
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_0205D648:
	ldrh r0, [r4, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0205478C
	cmp r0, #0x0
	beq _0205D65A
	mov r0, #0x0
	pop {r4, pc}
_0205D65A:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}

	thumb_func_start sub_0205D660
sub_0205D660: ; 0x0205D660
	ldr r3, _0205D668 ; =sub_0205CF34
	ldr r2, _0205D66C ; =0x00000AF2
	bx r3
	nop
_0205D668: .word sub_0205CF34
_0205D66C: .word 0x00000AF2

	thumb_func_start sub_0205D670
sub_0205D670: ; 0x0205D670
	push {r3, lr}
	ldr r1, _0205D67C ; =0x00000AF2
	bl sub_0205CF78
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205D67C: .word 0x00000AF2

	thumb_func_start sub_0205D680
sub_0205D680: ; 0x0205D680
	ldr r1, [r0, #0x4]
	cmp r1, #0x1
	bne _0205D68A
	mov r0, #0x2
	bx lr
_0205D68A:
	ldrh r1, [r0, #0x10]
	mov r0, #0x4
	tst r1, r0
	beq _0205D696
	mov r0, #0x0
	bx lr
_0205D696:
	sub r0, r0, #0x5
	bx lr
	.balign 4

	thumb_func_start sub_0205D69C
sub_0205D69C: ; 0x0205D69C
	ldr r3, _0205D6A4 ; =sub_0205CF34
	ldr r2, _0205D6A8 ; =0x00000AF3
	bx r3
	nop
_0205D6A4: .word sub_0205CF34
_0205D6A8: .word 0x00000AF3

	thumb_func_start sub_0205D6AC
sub_0205D6AC: ; 0x0205D6AC
	ldrh r1, [r0, #0x10]
	mov r0, #0x2
	tst r1, r0
	beq _0205D6B8
	mov r0, #0x0
	bx lr
_0205D6B8:
	sub r0, r0, #0x3
	bx lr

	thumb_func_start sub_0205D6BC
sub_0205D6BC: ; 0x0205D6BC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204649C
	bl ov05_021F57EC
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	mov r0, #0xb
	bl AllocFromHeapAtEnd
	ldr r2, [sp, #0x0]
	mov r1, #0x0
	add r7, r0, #0x0
	bl memset
	mov r0, #0x72
	ldr r1, _0205D710 ; =ov05_021F57F0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r7, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	ldr r0, [r6, #0xc]
	bl Save_Bag_Get
	ldrh r1, [r5, #0x4]
	mov r2, #0x1
	mov r3, #0xb
	bl Bag_TakeItem
	pop {r3-r7, pc}
	.balign 4
_0205D710: .word ov05_021F57F0

	thumb_func_start sub_0205D714
sub_0205D714: ; 0x0205D714
	ldr r3, _0205D71C ; =sub_0205CF34
	ldr r2, _0205D720 ; =0x000022F6
	bx r3
	nop
_0205D71C: .word sub_0205CF34
_0205D720: .word 0x000022F6

	thumb_func_start sub_0205D724
sub_0205D724: ; 0x0205D724
	push {r3, lr}
	ldr r1, _0205D730 ; =0x000022F6
	bl sub_0205CF78
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205D730: .word 0x000022F6

	thumb_func_start sub_0205D734
sub_0205D734: ; 0x0205D734
	push {r3, lr}
	ldr r0, [r0, #0x0]
	bl MapHeader_MapIsOnMainMatrix
	cmp r0, #0x0
	beq _0205D744
	mov r0, #0x0
	pop {r3, pc}
_0205D744:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205D74C
sub_0205D74C: ; 0x0205D74C
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205D784 ; =ov05_021F5C70
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r5, #0x0
	mov r1, #0xb
	mov r2, #0x0
	bl ov05_021F5C44
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r3-r5, pc}
	.balign 4
_0205D784: .word ov05_021F5C70

	thumb_func_start sub_0205D788
sub_0205D788: ; 0x0205D788
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	mov r2, #0x0
	bl ov05_021F5C44
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, _0205D7A4 ; =ov05_021F5C70
	bl sub_020463CC
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0205D7A4: .word ov05_021F5C70

	thumb_func_start sub_0205D7A8
sub_0205D7A8: ; 0x0205D7A8
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205D7E0 ; =ov05_021F5C70
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r5, #0x0
	mov r1, #0xb
	mov r2, #0x1
	bl ov05_021F5C44
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r3-r5, pc}
	.balign 4
_0205D7E0: .word ov05_021F5C70

	thumb_func_start sub_0205D7E4
sub_0205D7E4: ; 0x0205D7E4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	mov r2, #0x1
	bl ov05_021F5C44
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, _0205D800 ; =ov05_021F5C70
	bl sub_020463CC
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0205D800: .word ov05_021F5C70

	thumb_func_start sub_0205D804
sub_0205D804: ; 0x0205D804
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205D83C ; =ov05_021F5C70
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r5, #0x0
	mov r1, #0xb
	mov r2, #0x2
	bl ov05_021F5C44
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	pop {r3-r5, pc}
	.balign 4
_0205D83C: .word ov05_021F5C70

	thumb_func_start sub_0205D840
sub_0205D840: ; 0x0205D840
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	mov r2, #0x2
	bl ov05_021F5C44
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, _0205D85C ; =ov05_021F5C70
	bl sub_020463CC
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0205D85C: .word ov05_021F5C70

	thumb_func_start sub_0205D860
sub_0205D860: ; 0x0205D860
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0205D86E
	mov r0, #0x2
	pop {r4, pc}
_0205D86E:
	ldrh r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0205481C
	cmp r0, #0x1
	bne _0205D8B0
	ldrh r0, [r4, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02054B78
	cmp r0, #0x1
	beq _0205D898
	ldrh r0, [r4, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_02054B6C
	cmp r0, #0x1
	bne _0205D8AC
_0205D898:
	ldr r0, [r4, #0x14]
	bl PlayerAvatar_GetMapObject
	bl sub_02058A68
	cmp r0, #0x1
	bne _0205D8AC
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_0205D8AC:
	mov r0, #0x0
	pop {r4, pc}
_0205D8B0:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0205D8B8
sub_0205D8B8: ; 0x0205D8B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x16]
	mov r0, #0x80
	mov r1, #0xb
	bl String_New
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_Bag_Get
	bl Bag_GetRegisteredItem
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	lsl r2, r2, #0x10
	ldr r0, [r0, #0xc]
	ldr r1, [r4, #0x10]
	lsr r2, r2, #0x10
	mov r3, #0xb
	bl TryFormatRegisteredKeyItemUseMessage
	ldr r0, [r5, #0x0]
	ldr r1, _0205D900 ; =sub_0205D904
	add r2, r4, #0x0
	bl sub_020463CC
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0205D900: .word sub_0205D904

	thumb_func_start sub_0205D904
sub_0205D904: ; 0x0205D904
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldrh r0, [r4, #0x16]
	cmp r0, #0x0
	beq _0205D926
	cmp r0, #0x1
	beq _0205D95C
	cmp r0, #0x2
	beq _0205D984
	b _0205D9A0
_0205D926:
	ldr r0, [r5, #0x34]
	bl sub_02058780
	ldr r0, [r5, #0x8]
	add r1, r4, #0x0
	mov r2, #0x3
	bl sub_020545B8
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_02054608
	ldr r1, [r4, #0x10]
	add r0, r4, #0x0
	add r2, r5, #0x0
	mov r3, #0x1
	bl sub_02054658
	strh r0, [r4, #0x14]
	ldrh r0, [r4, #0x16]
	add r0, r0, #0x1
	strh r0, [r4, #0x16]
	b _0205D9A0
_0205D95C:
	ldrh r0, [r4, #0x14]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_020546C8
	cmp r0, #0x1
	bne _0205D9A0
	ldr r0, _0205D9A4 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #0xf3
	tst r0, r1
	beq _0205D9A0
	add r0, r4, #0x0
	mov r1, #0x0
	bl ClearFrameAndWindow2
	ldrh r0, [r4, #0x16]
	add r0, r0, #0x1
	strh r0, [r4, #0x16]
	b _0205D9A0
_0205D984:
	ldr r0, [r5, #0x34]
	bl sub_020587B0
	add r0, r4, #0x0
	bl RemoveWindow
	ldr r0, [r4, #0x10]
	bl String_Delete
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0205D9A0:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0205D9A4: .word gSystem

	thumb_func_start sub_0205D9A8
sub_0205D9A8: ; 0x0205D9A8
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	ldr r0, [r6, #0x0]
	bl sub_0204652C
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_Mailbox_Get
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl Save_SafariZone_Get
	str r0, [r4, #0x10]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r7, r0
	str r0, [r4, #0x18]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x10
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldrh r0, [r6, #0x4]
	add r2, r4, #0x0
	strh r0, [r4, #0x24]
	add r0, r4, #0x0
	ldrb r1, [r6, #0x6]
	add r0, #0x22
	strb r1, [r0, #0x0]
	ldr r1, _0205DA34 ; =UNK_020F96DC
	add r0, r5, #0x0
	bl sub_020373D4
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r4, [r7, r0]
	ldr r1, _0205DA38 ; =sub_02035E50
	add r0, r7, #0x0
	bl sub_02035D04
	pop {r3-r7, pc}
	.balign 4
_0205DA34: .word UNK_020F96DC
_0205DA38: .word sub_02035E50

	thumb_func_start sub_0205DA3C
sub_0205DA3C: ; 0x0205DA3C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204649C
	mov r0, #0x72
	ldr r1, _0205DA7C ; =sub_0205DAAC
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	str r1, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
	ldr r0, [r6, #0xc]
	bl Save_Bag_Get
	ldrh r1, [r5, #0x4]
	mov r2, #0x1
	mov r3, #0xb
	bl Bag_TakeItem
	pop {r4-r6, pc}
	nop
_0205DA7C: .word sub_0205DAAC

	thumb_func_start sub_0205DA80
sub_0205DA80: ; 0x0205DA80
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0205DA8E
	mov r0, #0x2
	pop {r4, pc}
_0205DA8E:
	ldr r0, [r4, #0x0]
	bl MapHeader_IsCave
	cmp r0, #0x1
	bne _0205DAA6
	ldr r0, [r4, #0x0]
	bl MapHeader_IsEscapeRopeAllowed
	cmp r0, #0x1
	bne _0205DAA6
	mov r0, #0x0
	pop {r4, pc}
_0205DAA6:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}

	thumb_func_start sub_0205DAAC
sub_0205DAAC: ; 0x0205DAAC
	push {r4, lr}
	add r4, r0, #0x0
	bl TaskManager_GetFieldSystem
	mov r1, #0xb
	bl ov06_0224C700
	add r2, r0, #0x0
	ldr r1, _0205DAC8 ; =0x0224C721
	add r0, r4, #0x0
	bl sub_020463EC
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0205DAC8: .word ov06_0224C720

	thumb_func_start sub_0205DACC
sub_0205DACC: ; 0x0205DACC
	ldr r3, _0205DAD4 ; =sub_0205CF34
	ldr r2, _0205DAD8 ; =0x000007F7
	bx r3
	nop
_0205DAD4: .word sub_0205CF34
_0205DAD8: .word 0x000007F7

	thumb_func_start sub_0205DADC
sub_0205DADC: ; 0x0205DADC
	push {r3, lr}
	ldr r1, _0205DAE8 ; =0x000007F7
	bl sub_0205CF78
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0205DAE8: .word 0x000007F7

	thumb_func_start sub_0205DAEC
sub_0205DAEC: ; 0x0205DAEC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x18]
	ldr r0, [r0, #0xc]
	bl Save_VarsFlags_Get
	add r5, r0, #0x0
	bl sub_0205ED0C
	cmp r0, #0x0
	bne _0205DB08
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205DB08:
	add r0, r5, #0x0
	mov r1, #0x2
	bl sub_0205F4A0
	cmp r0, #0x0
	bne _0205DB1A
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205DB1A:
	ldr r0, [r4, #0x18]
	ldr r0, [r0, #0xc]
	bl Save_Pokedex_Get
	bl Pokedex_GetNatDexFlag
	cmp r0, #0x0
	bne _0205DB30
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_0205DB30:
	ldr r0, [r4, #0x0]
	bl MapHeader_MapIsSpearPillar
	cmp r0, #0x0
	beq _0205DB3E
	mov r0, #0x0
	pop {r3-r5, pc}
_0205DB3E:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}

	thumb_func_start sub_0205DB44
sub_0205DB44: ; 0x0205DB44
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl sub_02060144
	cmp r0, #0x1
	bne _0205DB54
	mov r0, #0x0
	pop {r3-r7, pc}
_0205DB54:
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205F244
	cmp r0, #0x1
	bne _0205DB66
	mov r0, #0x0
	pop {r3-r7, pc}
_0205DB66:
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	bl Bag_GetRegisteredItem
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x6
	mov r2, #0xb
	str r0, [sp, #0x0]
	bl GetItemAttr
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	mov r0, #0x2
	add r1, r4, #0x0
	bl sub_0205CE48
	add r6, r0, #0x0
	mov r0, #0x1
	add r1, r4, #0x0
	bl sub_0205CE48
	add r7, r0, #0x0
	bne _0205DB9C
	mov r0, #0x0
	pop {r3-r7, pc}
_0205DB9C:
	mov r0, #0xb
	mov r1, #0x2c
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x2c
	bl memset
	str r5, [r4, #0x0]
	ldr r0, [sp, #0x0]
	add r1, r4, #0x4
	strh r0, [r4, #0x28]
	add r0, r5, #0x0
	bl sub_0205CE80
	mov r5, #0x0
	cmp r6, #0x0
	bne _0205DBCA
	add r0, r4, #0x0
	blx r7
	add r5, r0, #0x0
	b _0205DBE0
_0205DBCA:
	add r0, r4, #0x4
	blx r6
	add r1, r0, #0x0
	bne _0205DBDA
	add r0, r4, #0x0
	blx r7
	add r5, r0, #0x0
	b _0205DBE0
_0205DBDA:
	add r0, r4, #0x0
	bl sub_0205DBF0
_0205DBE0:
	cmp r5, #0x0
	bne _0205DBEA
	add r0, r4, #0x0
	bl FreeToHeap
_0205DBEA:
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205DBF0
sub_0205DBF0: ; 0x0205DBF0
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x16]
	mov r0, #0x80
	mov r1, #0xb
	bl String_New
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetProfileAddr
	mov r1, #0xb
	str r1, [sp, #0x0]
	ldrh r2, [r5, #0x28]
	ldr r1, [r4, #0x10]
	add r3, r6, #0x0
	bl sub_0206E51C
	ldr r0, [r5, #0x0]
	ldr r1, _0205DC34 ; =sub_0205D904
	add r2, r4, #0x0
	bl sub_020463CC
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_0205DC34: .word sub_0205D904

	thumb_func_start sub_0205DC38
sub_0205DC38: ; 0x0205DC38
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, #0x2a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4
	bhi _0205DCFA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0205DC5E: ; jump table (using 16-bit offset)
	.short _0205DC68 - _0205DC5E - 2; case 0
	.short _0205DC7C - _0205DC5E - 2; case 1
	.short _0205DC94 - _0205DC5E - 2; case 2
	.short _0205DCC4 - _0205DC5E - 2; case 3
	.short _0205DCE2 - _0205DC5E - 2; case 4
_0205DC68:
	ldr r0, [r5, #0x34]
	bl sub_02058780
	mov r0, #0x0
	bl ov05_021D7CA4
	mov r0, #0x1
	add r4, #0x2a
	strb r0, [r4, #0x0]
	b _0205DCFA
_0205DC7C:
	bl IsPaletteFadeFinished
	cmp r0, #0x0
	beq _0205DCFA
	ldr r1, [r4, #0x20]
	add r0, r5, #0x0
	blx r1
	str r0, [r4, #0x24]
	mov r0, #0x2
	add r4, #0x2a
	strb r0, [r4, #0x0]
	b _0205DCFA
_0205DC94:
	add r0, r5, #0x0
	bl sub_0204647C
	cmp r0, #0x0
	bne _0205DCFA
	ldr r0, [r4, #0x24]
	cmp r0, #0x0
	beq _0205DCB6
	ldr r2, [r4, #0x20]
	ldr r1, _0205DD00 ; =sub_0205D568
	cmp r2, r1
	bne _0205DCB2
	bl sub_02087E14
	b _0205DCB6
_0205DCB2:
	bl FreeToHeap
_0205DCB6:
	add r0, r5, #0x0
	bl sub_0204649C
	mov r0, #0x3
	add r4, #0x2a
	strb r0, [r4, #0x0]
	b _0205DCFA
_0205DCC4:
	add r0, r5, #0x0
	bl sub_020464A4
	cmp r0, #0x0
	beq _0205DCFA
	ldr r0, [r5, #0x34]
	bl sub_02058780
	mov r0, #0x1
	bl ov05_021D7CA4
	mov r0, #0x4
	add r4, #0x2a
	strb r0, [r4, #0x0]
	b _0205DCFA
_0205DCE2:
	bl IsPaletteFadeFinished
	cmp r0, #0x0
	beq _0205DCFA
	ldr r0, [r5, #0x34]
	bl sub_020587B0
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0205DCFA:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0205DD00: .word sub_0205D568

	thumb_func_start sub_0205DD04
sub_0205DD04: ; 0x0205DD04
	add r2, r0, #0x0
	str r1, [r2, #0x20]
	ldr r3, _0205DD10 ; =sub_020463CC
	ldr r0, [r2, #0x0]
	ldr r1, _0205DD14 ; =sub_0205DC38
	bx r3
	.balign 4
_0205DD10: .word sub_020463CC
_0205DD14: .word sub_0205DC38
