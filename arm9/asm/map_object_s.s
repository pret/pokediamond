	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F6364
	.extern sub_02057EE0
	.extern sub_0205815C
	.extern MapObjectManager_GetObjectCount
	.extern MapObjectManager_GetObjects
	.extern MapObject_SetMovement
	.extern sub_02058660

	.text

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
	bl MapObject_GetCurrentZ
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
	bl MapObject_SetCurrentY
	ldr r1, [r4, #0x8]
	add r0, r5, #0x0
	asr r2, r1, #0x4
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	bl MapObject_SetCurrentZ
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
	bl MapObject_SetCurrentY
	mov r0, #0x2
	lsl r1, r6, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl MapObject_SetCurrentZ
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
	bl MapObject_SetFlag2
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
