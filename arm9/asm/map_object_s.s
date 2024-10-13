	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F6364
	.extern sub_02057EE0
	.extern sub_0205815C
	.extern MapObjectManager_Get
	.extern MapObjectManager_GetObjectCount
	.extern MapObjectManager_SetFlagsBits
	.extern MapObjectManager_ClearFlagsBits
	.extern MapObjectManager_GetFlagsBitsMask
	.extern MapObjectManager_GetObjects
	.extern MapObjectManager_GetFieldSystem
	.extern MapObject_SetMovement
	.extern MapObject_GetEventFlag
	.extern sub_0205855C

	.text

	thumb_func_start sub_02058580
sub_02058580: ; 0x02058580
	ldr r3, _02058588 ; =MapObjectManager_Get
	add r0, #0xb4
	ldr r0, [r0, #0x0]
	bx r3
	.balign 4
_02058588: .word MapObjectManager_Get

	thumb_func_start sub_0205858C
sub_0205858C: ; 0x0205858C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x10
	ble _0205859A
	bl GF_AssertFail
_0205859A:
	add r0, r4, #0x0
	bl sub_020585B0
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020585B0
sub_020585B0: ; 0x020585B0
	add r0, #0xd8
	bx lr

	thumb_func_start sub_020585B4
sub_020585B4: ; 0x020585B4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x10
	ble _020585C2
	bl GF_AssertFail
_020585C2:
	add r0, r4, #0x0
	bl sub_020585D8
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020585D8
sub_020585D8: ; 0x020585D8
	add r0, #0xe8
	bx lr

	thumb_func_start sub_020585DC
sub_020585DC: ; 0x020585DC
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x10
	ble _020585EA
	bl GF_AssertFail
_020585EA:
	add r0, r4, #0x0
	bl sub_02058600
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02058600
sub_02058600: ; 0x02058600
	add r0, #0xf8
	bx lr

	thumb_func_start sub_02058604
sub_02058604: ; 0x02058604
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	ble _02058612
	bl GF_AssertFail
_02058612:
	add r0, r4, #0x0
	bl sub_02058628
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02058628
sub_02058628: ; 0x02058628
	mov r1, #0x42
	lsl r1, r1, #0x2
	add r0, r0, r1
	bx lr

	thumb_func_start sub_02058630
sub_02058630: ; 0x02058630
	add r0, #0xb8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058638
sub_02058638: ; 0x02058638
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xb8
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_02058644
sub_02058644: ; 0x02058644
	add r0, #0xbc
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0205864C
sub_0205864C: ; 0x0205864C
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xbc
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_02058658
sub_02058658: ; 0x02058658
	add r0, #0xc0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058660
sub_02058660: ; 0x02058660
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xc0
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_0205866C
sub_0205866C: ; 0x0205866C
	push {r4, lr}
	add r4, r0, #0x0
	bl MapObject_GetMovement
	bl sub_02058D14
	add r1, r0, #0x0
	ldr r1, [r1, #0x10]
	add r0, r4, #0x0
	blx r1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02058684
sub_02058684: ; 0x02058684
	add r0, #0xc4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0205868C
sub_0205868C: ; 0x0205868C
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xc4
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_02058698
sub_02058698: ; 0x02058698
	add r0, #0xc8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020586A0
sub_020586A0: ; 0x020586A0
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xc8
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_020586AC
sub_020586AC: ; 0x020586AC
	add r0, #0xcc
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020586B4
sub_020586B4: ; 0x020586B4
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xcc
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_020586C0
sub_020586C0: ; 0x020586C0
	add r0, #0xd0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020586C8
sub_020586C8: ; 0x020586C8
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xd0
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_020586D4
sub_020586D4: ; 0x020586D4
	add r0, #0xd4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020586DC
sub_020586DC: ; 0x020586DC
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0xd4
	ldr r1, [r1, #0x0]
	blx r1
	pop {r3, pc}

	thumb_func_start sub_020586E8
sub_020586E8: ; 0x020586E8
	add r0, #0xa4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020586F0
sub_020586F0: ; 0x020586F0
	add r0, #0xa4
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020586F8
sub_020586F8: ; 0x020586F8
	add r0, #0xa8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058700
sub_02058700: ; 0x02058700
	add r1, r0, #0x0
	add r1, #0xa8
	ldr r1, [r1, #0x0]
	add r0, #0xa8
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058710
sub_02058710: ; 0x02058710
	add r0, #0xa8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058718
sub_02058718: ; 0x02058718
	add r0, #0xac
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058720
sub_02058720: ; 0x02058720
	add r0, #0xac
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058728
sub_02058728: ; 0x02058728
	add r0, #0xae
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058730
sub_02058730: ; 0x02058730
	add r0, #0xae
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start MapObject_GetFieldSystem
MapObject_GetFieldSystem: ; 0x02058738
	push {r3, lr}
	bl sub_02058580
	bl MapObjectManager_GetFieldSystem
	pop {r3, pc}

	thumb_func_start sub_02058744
sub_02058744: ; 0x02058744
	push {r3, lr}
	bl MapObject_GetManager
	bl MapObjectManager_GetPriority
	pop {r3, pc}

	thumb_func_start sub_02058750
sub_02058750: ; 0x02058750
	push {r4, lr}
	add r4, r0, #0x0
	bl MapObject_CheckFlag25
	cmp r0, #0x1
	beq _02058760
	bl GF_AssertFail
_02058760:
	add r0, r4, #0x0
	bl MapObject_GetEventFlag
	pop {r4, pc}

	thumb_func_start sub_02058768
sub_02058768: ; 0x02058768
	ldr r3, _02058770 ; =MapObjectManager_SetFlagsBits
	mov r1, #0x6
	bx r3
	nop
_02058770: .word MapObjectManager_SetFlagsBits

	thumb_func_start sub_02058774
sub_02058774: ; 0x02058774
	ldr r3, _0205877C ; =MapObjectManager_ClearFlagsBits
	mov r1, #0x6
	bx r3
	nop
_0205877C: .word MapObjectManager_ClearFlagsBits

	thumb_func_start MapObjectManager_PauseAllMovement
MapObjectManager_PauseAllMovement: ; 0x02058780
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl MapObjectManager_GetObjectCount
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MapObjectManager_GetObjects
	mov r6, #0x4a
	add r5, r0, #0x0
	lsl r6, r6, #0x2
_02058796:
	add r0, r5, #0x0
	bl MapObject_IsInUse
	cmp r0, #0x0
	beq _020587A6
	add r0, r5, #0x0
	bl sub_02058908
_020587A6:
	add r5, r5, r6
	sub r4, r4, #0x1
	bne _02058796
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start MapObjectManager_UnpauseAllMovement
MapObjectManager_UnpauseAllMovement: ; 0x020587B0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl MapObjectManager_GetObjectCount
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MapObjectManager_GetObjects
	mov r6, #0x4a
	add r5, r0, #0x0
	lsl r6, r6, #0x2
_020587C6:
	add r0, r5, #0x0
	bl MapObject_IsInUse
	cmp r0, #0x0
	beq _020587D6
	add r0, r5, #0x0
	bl sub_02058914
_020587D6:
	add r5, r5, r6
	sub r4, r4, #0x1
	bne _020587C6
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_020587E0
sub_020587E0: ; 0x020587E0
	push {r3, lr}
	mov r1, #0x1
	bl MapObjectManager_GetFlagsBitsMask
	cmp r0, #0x0
	beq _020587F0
	mov r0, #0x1
	pop {r3, pc}
_020587F0:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_020587F4
sub_020587F4: ; 0x020587F4
	push {r4, lr}
	add r4, r1, #0x0
	bl MapObject_GetManager
	add r1, r4, #0x0
	bl MapObjectManager_GetFlagsBitsMask
	pop {r4, pc}

	thumb_func_start sub_02058804
sub_02058804: ; 0x02058804
	push {r3, lr}
	cmp r1, #0x0
	bne _02058812
	mov r1, #0x8
	bl MapObjectManager_SetFlagsBits
	pop {r3, pc}
_02058812:
	mov r1, #0x8
	bl MapObjectManager_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205881C
sub_0205881C: ; 0x0205881C
	push {r3, lr}
	mov r1, #0x8
	bl MapObjectManager_GetFlagsBitsMask
	cmp r0, #0x0
	bne _0205882C
	mov r0, #0x1
	pop {r3, pc}
_0205882C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start MapObject_IsInUse
MapObject_IsInUse: ; 0x02058830
	ldr r3, _02058838 ; =MapObject_TestFlagsBits
	mov r1, #0x1
	bx r3
	nop
_02058838: .word MapObject_TestFlagsBits

	thumb_func_start sub_0205883C
sub_0205883C: ; 0x0205883C
	ldr r3, _02058844 ; =MapObject_SetFlagsBits
	mov r1, #0x2
	bx r3
	nop
_02058844: .word MapObject_SetFlagsBits

	thumb_func_start sub_02058848
sub_02058848: ; 0x02058848
	ldr r3, _02058850 ; =MapObject_ClearFlagsBits
	mov r1, #0x2
	bx r3
	nop
_02058850: .word MapObject_ClearFlagsBits

	thumb_func_start sub_02058854
sub_02058854: ; 0x02058854
	ldr r3, _0205885C ; =MapObject_TestFlagsBits
	mov r1, #0x2
	bx r3
	nop
_0205885C: .word MapObject_TestFlagsBits

	thumb_func_start sub_02058860
sub_02058860: ; 0x02058860
	ldr r3, _02058868 ; =MapObject_SetFlagsBits
	mov r1, #0x4
	bx r3
	nop
_02058868: .word MapObject_SetFlagsBits

	thumb_func_start sub_0205886C
sub_0205886C: ; 0x0205886C
	ldr r3, _02058874 ; =MapObject_ClearFlagsBits
	mov r1, #0x8
	bx r3
	nop
_02058874: .word MapObject_ClearFlagsBits

	thumb_func_start MapObject_SetFlag14
MapObject_SetFlag14: ; 0x02058878
	ldr r3, _02058880 ; =MapObject_SetFlagsBits
	mov r1, #0x1
	lsl r1, r1, #0xe
	bx r3
	.balign 4
_02058880: .word MapObject_SetFlagsBits

	thumb_func_start MapObject_CheckFlag14
MapObject_CheckFlag14: ; 0x02058884
	ldr r3, _0205888C ; =MapObject_TestFlagsBits
	mov r1, #0x1
	lsl r1, r1, #0xe
	bx r3
	.balign 4
_0205888C: .word MapObject_TestFlagsBits

	thumb_func_start sub_02058890
sub_02058890: ; 0x02058890
	ldr r3, _02058898 ; =MapObject_TestFlagsBits
	mov r1, #0x2
	lsl r1, r1, #0x8
	bx r3
	.balign 4
_02058898: .word MapObject_TestFlagsBits

	thumb_func_start MapObject_SetVisible
MapObject_SetVisible: ; 0x0205889C
	push {r3, lr}
	cmp r1, #0x1
	bne _020588AC
	mov r1, #0x2
	lsl r1, r1, #0x8
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_020588AC:
	mov r1, #0x2
	lsl r1, r1, #0x8
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020588B8
sub_020588B8: ; 0x020588B8
	push {r3, lr}
	cmp r1, #0x1
	bne _020588C8
	mov r1, #0x1
	lsl r1, r1, #0x12
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
_020588C8:
	mov r1, #0x1
	lsl r1, r1, #0x12
	bl MapObject_SetFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020588D4
sub_020588D4: ; 0x020588D4
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x12
	bl MapObject_TestFlagsBits
	cmp r0, #0x1
	beq _020588E6
	mov r0, #0x1
	pop {r3, pc}
_020588E6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020588EC
sub_020588EC: ; 0x020588EC
	push {r3, lr}
	cmp r1, #0x1
	bne _020588FC
	mov r1, #0x2
	lsl r1, r1, #0x12
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_020588FC:
	mov r1, #0x2
	lsl r1, r1, #0x12
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058908
sub_02058908: ; 0x02058908
	ldr r3, _02058910 ; =MapObject_SetFlagsBits
	mov r1, #0x40
	bx r3
	nop
_02058910: .word MapObject_SetFlagsBits

	thumb_func_start sub_02058914
sub_02058914: ; 0x02058914
	ldr r3, _0205891C ; =MapObject_ClearFlagsBits
	mov r1, #0x40
	bx r3
	nop
_0205891C: .word MapObject_ClearFlagsBits

	thumb_func_start sub_02058920
sub_02058920: ; 0x02058920
	push {r3, lr}
	mov r1, #0x40
	bl MapObject_TestFlagsBits
	cmp r0, #0x1
	bne _02058930
	mov r0, #0x1
	pop {r3, pc}
_02058930:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_02058934
sub_02058934: ; 0x02058934
	push {r4, lr}
	add r4, r0, #0x0
	bl MapObject_GetManager
	bl sub_020587E0
	cmp r0, #0x0
	bne _02058948
	mov r0, #0x0
	pop {r4, pc}
_02058948:
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xe
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _0205895A
	mov r0, #0x1
	pop {r4, pc}
_0205895A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02058960
sub_02058960: ; 0x02058960
	push {r3, lr}
	cmp r1, #0x1
	bne _02058970
	mov r1, #0x2
	lsl r1, r1, #0x16
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_02058970:
	mov r1, #0x2
	lsl r1, r1, #0x16
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205897C
sub_0205897C: ; 0x0205897C
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x16
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _0205898E
	mov r0, #0x1
	pop {r3, pc}
_0205898E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058994
sub_02058994: ; 0x02058994
	push {r3, lr}
	cmp r1, #0x1
	bne _020589A4
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_020589A4:
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start MapObject_SetFlag25
MapObject_SetFlag25: ; 0x020589B0
	push {r3, lr}
	cmp r1, #0x1
	bne _020589C0
	mov r1, #0x2
	lsl r1, r1, #0x18
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_020589C0:
	mov r1, #0x2
	lsl r1, r1, #0x18
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start MapObject_CheckFlag25
MapObject_CheckFlag25: ; 0x020589CC
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x18
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _020589DE
	mov r0, #0x1
	pop {r3, pc}
_020589DE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_020589E4
sub_020589E4: ; 0x020589E4
	push {r3, lr}
	cmp r1, #0x1
	bne _020589F4
	mov r1, #0x1
	lsl r1, r1, #0x1a
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_020589F4:
	mov r1, #0x1
	lsl r1, r1, #0x1a
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A00
sub_02058A00: ; 0x02058A00
	push {r3, lr}
	mov r1, #0x1
	lsl r1, r1, #0x1a
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058A12
	mov r0, #0x1
	pop {r3, pc}
_02058A12:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A18
sub_02058A18: ; 0x02058A18
	push {r3, lr}
	cmp r1, #0x1
	bne _02058A28
	mov r1, #0x2
	lsl r1, r1, #0x1a
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_02058A28:
	mov r1, #0x2
	lsl r1, r1, #0x1a
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A34
sub_02058A34: ; 0x02058A34
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x1a
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058A46
	mov r0, #0x1
	pop {r3, pc}
_02058A46:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A4C
sub_02058A4C: ; 0x02058A4C
	push {r3, lr}
	cmp r1, #0x1
	bne _02058A5C
	mov r1, #0x1
	lsl r1, r1, #0x1c
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_02058A5C:
	mov r1, #0x1
	lsl r1, r1, #0x1c
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A68
sub_02058A68: ; 0x02058A68
	push {r3, lr}
	mov r1, #0x1
	lsl r1, r1, #0x1c
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058A7A
	mov r0, #0x1
	pop {r3, pc}
_02058A7A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A80
sub_02058A80: ; 0x02058A80
	push {r3, lr}
	cmp r1, #0x1
	bne _02058A90
	mov r1, #0x1
	lsl r1, r1, #0x18
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_02058A90:
	mov r1, #0x1
	lsl r1, r1, #0x18
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058A9C
sub_02058A9C: ; 0x02058A9C
	push {r3, lr}
	mov r1, #0x1
	lsl r1, r1, #0x18
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058AAE
	mov r0, #0x1
	pop {r3, pc}
_02058AAE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02058AB4
sub_02058AB4: ; 0x02058AB4
	push {r3, lr}
	mov r1, #0x10
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058AC4
	mov r0, #0x1
	pop {r3, pc}
_02058AC4:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start sub_02058AC8
sub_02058AC8: ; 0x02058AC8
	push {r3, lr}
	cmp r1, #0x1
	bne _02058AD8
	mov r1, #0x2
	lsl r1, r1, #0x1c
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_02058AD8:
	mov r1, #0x2
	lsl r1, r1, #0x1c
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4

	thumb_func_start MapObject_CheckFlag29
MapObject_CheckFlag29: ; 0x02058AE4
	push {r3, lr}
	mov r1, #0x2
	lsl r1, r1, #0x1c
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058AF6
	mov r0, #0x1
	pop {r3, pc}
_02058AF6:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start MapObject_GetInitialX
MapObject_GetInitialX: ; 0x02058AFC
	ldr r0, [r0, #0x4c]
	bx lr

	thumb_func_start MapObject_SetInitialX
MapObject_SetInitialX: ; 0x02058B00
	str r1, [r0, #0x4c]
	bx lr

	thumb_func_start MapObject_GetInitialHeight
MapObject_GetInitialHeight: ; 0x02058B04
	ldr r0, [r0, #0x50]
	bx lr

	thumb_func_start MapObject_SetInitialHeight
MapObject_SetInitialHeight: ; 0x02058B08
	str r1, [r0, #0x50]
	bx lr

	thumb_func_start MapObject_GetInitialY
MapObject_GetInitialY: ; 0x02058B0C
	ldr r0, [r0, #0x54]
	bx lr

	thumb_func_start MapObject_SetInitialY
MapObject_SetInitialY: ; 0x02058B10
	str r1, [r0, #0x54]
	bx lr

	thumb_func_start sub_02058B14
sub_02058B14: ; 0x02058B14
	ldr r0, [r0, #0x58]
	bx lr

	thumb_func_start MapObject_SetPreviousX
MapObject_SetPreviousX: ; 0x02058B18
	str r1, [r0, #0x58]
	bx lr

	thumb_func_start sub_02058B1C
sub_02058B1C: ; 0x02058B1C
	ldr r0, [r0, #0x5c]
	bx lr

	thumb_func_start MapObject_SetPreviousHeight
MapObject_SetPreviousHeight: ; 0x02058B20
	str r1, [r0, #0x5c]
	bx lr

	thumb_func_start sub_02058B24
sub_02058B24: ; 0x02058B24
	ldr r0, [r0, #0x60]
	bx lr

	thumb_func_start MapObject_SetPreviousY
MapObject_SetPreviousY: ; 0x02058B28
	str r1, [r0, #0x60]
	bx lr

	thumb_func_start MapObject_GetCurrentX
MapObject_GetCurrentX: ; 0x02058B2C
	ldr r0, [r0, #0x64]
	bx lr

	thumb_func_start MapObject_SetCurrentX
MapObject_SetCurrentX: ; 0x02058B30
	str r1, [r0, #0x64]
	bx lr

	thumb_func_start sub_02058B34
sub_02058B34: ; 0x02058B34
	ldr r2, [r0, #0x64]
	add r1, r2, r1
	str r1, [r0, #0x64]
	bx lr

	thumb_func_start MapObject_GetCurrentHeight
MapObject_GetCurrentHeight: ; 0x02058B3C
	ldr r0, [r0, #0x68]
	bx lr

	thumb_func_start MapObject_SetCurrentHeight
MapObject_SetCurrentHeight: ; 0x02058B40
	str r1, [r0, #0x68]
	bx lr

	thumb_func_start sub_02058B44
sub_02058B44: ; 0x02058B44
	ldr r2, [r0, #0x68]
	add r1, r2, r1
	str r1, [r0, #0x68]
	bx lr

	thumb_func_start MapObject_GetCurrentY
MapObject_GetCurrentY: ; 0x02058B4C
	ldr r0, [r0, #0x6c]
	bx lr

	thumb_func_start MapObject_SetCurrentY
MapObject_SetCurrentY: ; 0x02058B50
	str r1, [r0, #0x6c]
	bx lr

	thumb_func_start sub_02058B54
sub_02058B54: ; 0x02058B54
	ldr r2, [r0, #0x6c]
	add r1, r2, r1
	str r1, [r0, #0x6c]
	bx lr

	thumb_func_start MapObject_GetPositionVec
MapObject_GetPositionVec: ; 0x02058B5C
	add r2, r0, #0x0
	add r2, #0x70
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start MapObject_SetPositionVec
MapObject_SetPositionVec: ; 0x02058B6C
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x70
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02058B7C
sub_02058B7C: ; 0x02058B7C
	add r0, #0x70
	bx lr

	thumb_func_start MapObject_GetPosVecYCoord
MapObject_GetPosVecYCoord: ; 0x02058B80
	ldr r0, [r0, #0x74]
	bx lr

	thumb_func_start sub_02058B84
sub_02058B84: ; 0x02058B84
	add r2, r0, #0x0
	add r2, #0x7c
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start sub_02058B94
sub_02058B94: ; 0x02058B94
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x7c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02058BA4
sub_02058BA4: ; 0x02058BA4
	add r2, r0, #0x0
	add r2, #0x88
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start sub_02058BB4
sub_02058BB4: ; 0x02058BB4
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x88
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02058BC4
sub_02058BC4: ; 0x02058BC4
	add r2, r0, #0x0
	add r2, #0x94
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start sub_02058BD4
sub_02058BD4: ; 0x02058BD4
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x94
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02058BE4
sub_02058BE4: ; 0x02058BE4
	push {r3, lr}
	bl MapObject_GetPosVecYCoord
	asr r1, r0, #0x3
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r0, r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start ObjectEvent_SetId
ObjectEvent_SetId: ; 0x02058BF8
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start ObjectEvent_GetID
ObjectEvent_GetID: ; 0x02058BFC
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start ObjectEvent_SetSprite
ObjectEvent_SetSprite: ; 0x02058C00
	strh r1, [r0, #0x2]
	bx lr

	thumb_func_start ObjectEvent_GetSpriteID
ObjectEvent_GetSpriteID: ; 0x02058C04
	ldrh r0, [r0, #0x2]
	bx lr

	thumb_func_start ObjectEvent_SetMovement
ObjectEvent_SetMovement: ; 0x02058C08
	strh r1, [r0, #0x4]
	bx lr

	thumb_func_start ObjectEvent_GetMovement
ObjectEvent_GetMovement: ; 0x02058C0C
	ldrh r0, [r0, #0x4]
	bx lr

	thumb_func_start ObjectEvent_SetType
ObjectEvent_SetType: ; 0x02058C10
	strh r1, [r0, #0x6]
	bx lr

	thumb_func_start ObjectEvent_GetType
ObjectEvent_GetType: ; 0x02058C14
	ldrh r0, [r0, #0x6]
	bx lr

	thumb_func_start ObjectEvent_SetFlagId
ObjectEvent_SetFlagId: ; 0x02058C18
	strh r1, [r0, #0x8]
	bx lr

	thumb_func_start ObjectEvent_GetFlagID
ObjectEvent_GetFlagID: ; 0x02058C1C
	ldrh r0, [r0, #0x8]
	bx lr

	thumb_func_start ObjectEvent_SetScript
ObjectEvent_SetScript: ; 0x02058C20
	strh r1, [r0, #0xa]
	bx lr

	thumb_func_start ObjectEvent_GetScriptID
ObjectEvent_GetScriptID: ; 0x02058C24
	ldrh r0, [r0, #0xa]
	bx lr

	thumb_func_start ObjectEvent_SetFacing
ObjectEvent_SetFacing: ; 0x02058C28
	strh r1, [r0, #0xc]
	bx lr

	thumb_func_start ObjectEvent_GetInitialFacingDirection
ObjectEvent_GetInitialFacingDirection: ; 0x02058C2C
	mov r1, #0xc
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start ObjectEvent_SetParam
ObjectEvent_SetParam: ; 0x02058C34
	push {r3, lr}
	cmp r2, #0x0
	beq _02058C44
	cmp r2, #0x1
	beq _02058C48
	cmp r2, #0x2
	beq _02058C4C
	b _02058C50
_02058C44:
	strh r1, [r0, #0xe]
	pop {r3, pc}
_02058C48:
	strh r1, [r0, #0x10]
	pop {r3, pc}
_02058C4C:
	strh r1, [r0, #0x12]
	pop {r3, pc}
_02058C50:
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4

	thumb_func_start ObjectEvent_GetParam
ObjectEvent_GetParam: ; 0x02058C58
	push {r3, lr}
	cmp r1, #0x0
	beq _02058C68
	cmp r1, #0x1
	beq _02058C6C
	cmp r1, #0x2
	beq _02058C70
	b _02058C74
_02058C68:
	ldrh r0, [r0, #0xe]
	pop {r3, pc}
_02058C6C:
	ldrh r0, [r0, #0x10]
	pop {r3, pc}
_02058C70:
	ldrh r0, [r0, #0x12]
	pop {r3, pc}
_02058C74:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ObjectEvent_SetXRange
ObjectEvent_SetXRange: ; 0x02058C7C
	strh r1, [r0, #0x14]
	bx lr

	thumb_func_start ObjectEvent_GetXRange
ObjectEvent_GetXRange: ; 0x02058C80
	mov r1, #0x14
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start ObjectEvent_SetYRange
ObjectEvent_SetYRange: ; 0x02058C88
	strh r1, [r0, #0x16]
	bx lr

	thumb_func_start ObjectEvent_GetYRange
ObjectEvent_GetYRange: ; 0x02058C8C
	mov r1, #0x16
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start ObjectEvent_SetXCoord
ObjectEvent_SetXCoord: ; 0x02058C94
	strh r1, [r0, #0x18]
	bx lr

	thumb_func_start ObjectEvent_GetXCoord
ObjectEvent_GetXCoord: ; 0x02058C98
	ldrh r0, [r0, #0x18]
	bx lr

	thumb_func_start ObjectEvent_SetHeight
ObjectEvent_SetHeight: ; 0x02058C9C
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start ObjectEvent_GetHeight
ObjectEvent_GetHeight: ; 0x02058CA0
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start ObjectEvent_SetYCoord
ObjectEvent_SetYCoord: ; 0x02058CA4
	strh r1, [r0, #0x1a]
	bx lr

	thumb_func_start ObjectEvent_GetYCoord
ObjectEvent_GetYCoord: ; 0x02058CA8
	ldrh r0, [r0, #0x1a]
	bx lr

	thumb_func_start ObjectEvent_GetById
ObjectEvent_GetById: ; 0x02058CAC
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	str r2, [sp, #0x0]
	mov r4, #0x0
	add r5, r2, #0x0
_02058CB8:
	add r0, r5, #0x0
	bl ObjectEvent_ScriptIDIsUnset
	cmp r0, #0x0
	bne _02058CD4
	add r0, r5, #0x0
	bl ObjectEvent_GetID
	cmp r6, r0
	bne _02058CD4
	ldr r0, [sp, #0x0]
	lsl r1, r4, #0x5
	add r0, r0, r1
	pop {r3-r7, pc}
_02058CD4:
	add r4, r4, #0x1
	add r5, #0x20
	cmp r4, r7
	blt _02058CB8
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ObjectEvent_ScriptIDIsUnset
ObjectEvent_ScriptIDIsUnset: ; 0x02058CE0
	push {r3, lr}
	bl ObjectEvent_GetScriptID
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _02058CF8 ; =0x0000FFFF
	cmp r1, r0
	bne _02058CF4
	mov r0, #0x1
	pop {r3, pc}
_02058CF4:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02058CF8: .word 0x0000FFFF

	thumb_func_start ObjectEvent_GetFlagID_AssertScriptIDIsUnset
ObjectEvent_GetFlagID_AssertScriptIDIsUnset: ; 0x02058CFC
	push {r4, lr}
	add r4, r0, #0x0
	bl ObjectEvent_ScriptIDIsUnset
	cmp r0, #0x1
	beq _02058D0C
	bl GF_AssertFail
_02058D0C:
	add r0, r4, #0x0
	bl ObjectEvent_GetFlagID
	pop {r4, pc}

	thumb_func_start sub_02058D14
sub_02058D14: ; 0x02058D14
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x37
	blo _02058D20
	bl GF_AssertFail
_02058D20:
	ldr r0, _02058D28 ; =UNK_020F6364
	lsl r1, r4, #0x2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02058D28: .word UNK_020F6364

	thumb_func_start sub_02058D2C
sub_02058D2C: ; 0x02058D2C
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start sub_02058D30
sub_02058D30: ; 0x02058D30
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start sub_02058D34
sub_02058D34: ; 0x02058D34
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start sub_02058D38
sub_02058D38: ; 0x02058D38
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start sub_02058D3C
sub_02058D3C: ; 0x02058D3C
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start sub_02058D40
sub_02058D40: ; 0x02058D40
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start sub_02058D44
sub_02058D44: ; 0x02058D44
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start sub_02058D48
sub_02058D48: ; 0x02058D48
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start sub_02058D4C
sub_02058D4C: ; 0x02058D4C
	push {r3, lr}
	ldr r3, _02058D6C ; =ov05_021F9494
	ldr r1, _02058D70 ; =0x0000FFFF
_02058D52:
	ldr r2, [r3, #0x0]
	cmp r2, r0
	bne _02058D5C
	ldr r0, [r3, #0x4]
	pop {r3, pc}
_02058D5C:
	add r3, #0x8
	ldr r2, [r3, #0x0]
	cmp r2, r1
	bne _02058D52
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02058D6C: .word ov05_021F9494
_02058D70: .word 0x0000FFFF

	thumb_func_start sub_02058D74
sub_02058D74: ; 0x02058D74
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl MapObjectManager_GetObjectCount
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MapObjectManager_GetObjects
	add r5, r0, #0x0
_02058D8A:
	add r0, r5, #0x0
	mov r1, #0x1
	bl MapObject_GetFlagsBitsMask
	cmp r0, #0x0
	beq _02058DAE
	add r0, r5, #0x0
	bl MapObject_GetCurrentX
	cmp r6, r0
	bne _02058DAE
	add r0, r5, #0x0
	bl MapObject_GetCurrentY
	cmp r7, r0
	bne _02058DAE
	add r0, r5, #0x0
	pop {r3-r7, pc}
_02058DAE:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	add r5, r5, r0
	sub r4, r4, #0x1
	bne _02058D8A
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_02058DBC
sub_02058DBC: ; 0x02058DBC
	push {r4-r6, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	add r6, r2, #0x0
	asr r2, r1, #0x4
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	add r5, r0, #0x0
	bl MapObject_SetCurrentX
	ldr r1, [r4, #0x4]
	add r0, r5, #0x0
	asr r2, r1, #0x3
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	bl MapObject_SetCurrentHeight
	ldr r1, [r4, #0x8]
	add r0, r5, #0x0
	asr r2, r1, #0x4
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	bl MapObject_SetCurrentY
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MapObject_SetPositionVec
	add r0, r5, #0x0
	bl sub_02059C60
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl MapObject_SetFacingDirectionDirect
	add r0, r5, #0x0
	bl MapObject_ClearHeldMovement
	add r0, r5, #0x0
	mov r1, #0x4
	bl MapObject_SetFlagsBits
	add r0, r5, #0x0
	mov r1, #0xa
	bl MapObject_ClearFlagsBits
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02058E28
sub_02058E28: ; 0x02058E28
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	mov r2, #0x2
	add r6, r3, #0x0
	lsl r3, r1, #0x10
	lsl r2, r2, #0xe
	add r2, r3, r2
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	bl MapObject_SetCurrentX
	lsl r0, r4, #0xf
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MapObject_SetCurrentHeight
	mov r0, #0x2
	lsl r1, r6, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl MapObject_SetCurrentY
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl MapObject_SetPositionVec
	add r0, r5, #0x0
	bl sub_02059C60
	ldr r1, [sp, #0x20]
	add r0, r5, #0x0
	bl MapObject_SetFacingDirectionDirect
	add r0, r5, #0x0
	mov r1, #0x4
	bl MapObject_SetFlagsBits
	add r0, r5, #0x0
	mov r1, #0xa
	bl MapObject_ClearFlagsBits
	add r0, r5, #0x0
	bl MapObject_ClearHeldMovement
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start sub_02058E90
sub_02058E90: ; 0x02058E90
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_02058660
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MapObject_SetMovement
	add r0, r5, #0x0
	bl sub_02057EE0
	add r0, r5, #0x0
	bl sub_02058EE8
	pop {r3-r5, pc}

	thumb_func_start sub_02058EB0
sub_02058EB0: ; 0x02058EB0
	push {r4, lr}
	add r4, r0, #0x0
	bl MapObject_SetID
	add r0, r4, #0x0
	bl sub_02058860
	add r0, r4, #0x0
	bl sub_0205815C
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02058EC8
sub_02058EC8: ; 0x02058EC8
	bx lr
	.balign 4

	thumb_func_start sub_02058ECC
sub_02058ECC: ; 0x02058ECC
	bx lr
	.balign 4

	thumb_func_start sub_02058ED0
sub_02058ED0: ; 0x02058ED0
	bx lr
	.balign 4

	thumb_func_start sub_02058ED4
sub_02058ED4: ; 0x02058ED4
	bx lr
	.balign 4

	thumb_func_start sub_02058ED8
sub_02058ED8: ; 0x02058ED8
	bx lr
	.balign 4

	thumb_func_start sub_02058EDC
sub_02058EDC: ; 0x02058EDC
	bx lr
	.balign 4

	thumb_func_start sub_02058EE0
sub_02058EE0: ; 0x02058EE0
	bx lr
	.balign 4

	thumb_func_start sub_02058EE4
sub_02058EE4: ; 0x02058EE4
	bx lr
	.balign 4
