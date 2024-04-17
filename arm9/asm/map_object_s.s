	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F6364

	.text

	thumb_func_start sub_02057CF0
sub_02057CF0: ; 0x02057CF0
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl MapObjectManager_GetPriority
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl MapObject_GetMovement
	cmp r0, #0x30
	beq _02057D08
	cmp r0, #0x32
	bne _02057D0A
_02057D08:
	add r5, r5, #0x2
_02057D0A:
	ldr r0, _02057D28 ; =sub_0205832C
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl SysTask_CreateOnMainQueue
	add r5, r0, #0x0
	bne _02057D1C
	bl GF_AssertFail
_02057D1C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_02058554
	pop {r3-r5, pc}
	nop
_02057D28: .word sub_0205832C

	thumb_func_start MapObject_InitFromObjectEvent
MapObject_InitFromObjectEvent: ; 0x02057D2C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl ObjectEvent_GetID
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetID
	add r0, r4, #0x0
	bl sub_02058C04
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl sub_02058170
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetGfxID
	add r0, r4, #0x0
	bl sub_02058C0C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetMovement
	add r0, r4, #0x0
	bl sub_02058C14
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetType
	add r0, r4, #0x0
	bl ObjectEvent_GetFlagId
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetFlagID
	add r0, r4, #0x0
	bl sub_02058C24
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetScript
	add r0, r4, #0x0
	bl sub_02058C2C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetInitialFacingDirection
	add r0, r4, #0x0
	mov r1, #0x0
	bl sub_02058C58
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	bl MapObject_SetParam
	add r0, r4, #0x0
	mov r1, #0x1
	bl sub_02058C58
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl MapObject_SetParam
	add r0, r4, #0x0
	mov r1, #0x2
	bl sub_02058C58
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x2
	bl MapObject_SetParam
	add r0, r4, #0x0
	bl sub_02058C80
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetXRange
	add r0, r4, #0x0
	bl sub_02058C8C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetYRange
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02057DFC
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02057DFC
sub_02057DFC: ; 0x02057DFC
	push {r3-r6, lr}
	sub sp, #0xc
	add r6, r1, #0x0
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl sub_02058C98
	add r5, r0, #0x0
	mov r0, #0x2
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetInitialX
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetPreviousX
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetCurrentX
	add r0, r6, #0x0
	bl sub_02058CA0
	asr r1, r0, #0x3
	str r0, [sp, #0x4]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r5, r0, #0xc
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetInitialHeight
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetPreviousHeight
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetCurrentHeight
	add r0, r6, #0x0
	bl sub_02058CA8
	add r5, r0, #0x0
	mov r0, #0x2
	lsl r1, r5, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetInitialY
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetPreviousY
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MapObject_SetCurrentY
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl MapObject_SetPositionVec
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start sub_02057E90
sub_02057E90: ; 0x02057E90
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _02057EDC ; =0x00001801
	add r5, r0, #0x0
	bl MapObject_SetFlagsBits
	add r0, r5, #0x0
	bl sub_020581F8
	cmp r0, #0x1
	bne _02057EAE
	add r0, r5, #0x0
	mov r1, #0x1
	bl sub_020589B0
_02057EAE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02058570
	add r0, r5, #0x0
	bl MapObject_GetInitialFacingDirection
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetFacingDirectionDirect
	add r0, r5, #0x0
	bl MapObject_GetInitialFacingDirection
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetNextFacingDirection
	add r0, r5, #0x0
	bl MapObject_ClearHeldMovement
	pop {r3-r5, pc}
	nop
_02057EDC: .word 0x00001801

	thumb_func_start sub_02057EE0
sub_02057EE0: ; 0x02057EE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl MapObject_GetMovement
	bl sub_02058D14
	add r4, r0, #0x0
	bl sub_02058D2C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_02058630
	add r0, r4, #0x0
	bl sub_02058D30
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_02058644
	add r0, r4, #0x0
	bl sub_02058D34
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_02058658
	pop {r3-r5, pc}

	thumb_func_start sub_02057F18
sub_02057F18: ; 0x02057F18
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl MapObject_GetGfxID
	mov r1, #0x2
	lsl r1, r1, #0xc
	cmp r0, r1
	bne _02057F2C
	ldr r5, _02057F7C ; =ov05_021F9080
	b _02057F32
_02057F2C:
	bl sub_02058D4C
	add r5, r0, #0x0
_02057F32:
	add r0, r5, #0x0
	bl sub_02058D38
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_02058684
	add r0, r5, #0x0
	bl sub_02058D3C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_02058698
	add r0, r5, #0x0
	bl sub_02058D40
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_020586AC
	add r0, r5, #0x0
	bl sub_02058D44
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_020586C0
	add r0, r5, #0x0
	bl sub_02058D48
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_020586D4
	pop {r3-r5, pc}
	nop
_02057F7C: .word ov05_021F9080

	thumb_func_start sub_02057F80
sub_02057F80: ; 0x02057F80
	ldr r3, _02057F8C ; =memset
	mov r2, #0x4a
	mov r1, #0x0
	lsl r2, r2, #0x2
	bx r3
	nop
_02057F8C: .word memset

	thumb_func_start sub_02057F90
sub_02057F90: ; 0x02057F90
	push {r3-r7, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r3, #0x0
	str r1, [sp, #0x0]
	cmp r6, #0x0
	beq _0205800A
_02057F9E:
	add r0, r4, #0x0
	bl ObjectEvent_GetID
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_GetID
	cmp r7, r0
	bne _02058002
	add r0, r4, #0x0
	bl ObjectEvent_ScriptIdIsUnset
	cmp r0, #0x1
	bne _02057FE8
	add r0, r4, #0x0
	bl ObjectEvent_GetFlagID_AssertScriptIdIsUnset
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_CheckFlag25
	cmp r0, #0x1
	bne _02057FDA
	add r0, r5, #0x0
	bl sub_02058750
	cmp r7, r0
	bne _02058002
	mov r0, #0x1
	pop {r3-r7, pc}
_02057FDA:
	add r0, r5, #0x0
	bl sub_02058450
	cmp r7, r0
	bne _02058002
	mov r0, #0x2
	pop {r3-r7, pc}
_02057FE8:
	add r0, r5, #0x0
	bl MapObject_CheckFlag25
	cmp r0, #0x1
	bne _02058002
	add r0, r5, #0x0
	bl sub_02058750
	ldr r1, [sp, #0x0]
	cmp r1, r0
	bne _02058002
	mov r0, #0x2
	pop {r3-r7, pc}
_02058002:
	sub r6, r6, #0x1
	add r4, #0x20
	cmp r6, #0x0
	bne _02057F9E
_0205800A:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_02058010
sub_02058010: ; 0x02058010
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	mov r1, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0x4]
	add r1, sp, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	add r6, r0, #0x0
	bl sub_020580F4
	cmp r0, #0x1
	bne _02058058
	add r7, sp, #0x0
_0205802E:
	ldr r0, [sp, #0x0]
	bl MapObject_GetID
	cmp r5, r0
	bne _02058048
	ldr r0, [sp, #0x0]
	bl sub_02058450
	cmp r4, r0
	bne _02058048
	ldr r0, [sp, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
_02058048:
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x4
	mov r3, #0x1
	bl sub_020580F4
	cmp r0, #0x1
	beq _0205802E
_02058058:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start GetMapObjectByID
GetMapObjectByID: ; 0x02058060
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	cmp r5, #0x0
	bne _0205806E
	bl GF_AssertFail
_0205806E:
	add r0, r5, #0x0
	bl MapObjectManager_GetObjectCount
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_020583C4
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_02058082:
	add r0, r5, #0x0
	mov r1, #0x1
	bl MapObject_TestFlagsBits
	cmp r0, #0x1
	bne _020580A6
	add r0, r5, #0x0
	bl MapObject_CheckFlag25
	cmp r0, #0x0
	bne _020580A6
	add r0, r5, #0x0
	bl MapObject_GetID
	cmp r6, r0
	bne _020580A6
	add r0, r5, #0x0
	pop {r3-r7, pc}
_020580A6:
	sub r4, r4, #0x1
	add r5, r5, r7
	cmp r4, #0x0
	bgt _02058082
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_020580B4
sub_020580B4: ; 0x020580B4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl MapObjectManager_GetObjectCount
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_020583C4
	mov r7, #0x4a
	add r5, r0, #0x0
	lsl r7, r7, #0x2
_020580CC:
	add r0, r5, #0x0
	mov r1, #0x1
	bl MapObject_TestFlagsBits
	cmp r0, #0x1
	bne _020580E6
	add r0, r5, #0x0
	bl MapObject_GetMovement
	cmp r6, r0
	bne _020580E6
	add r0, r5, #0x0
	pop {r3-r7, pc}
_020580E6:
	sub r4, r4, #0x1
	add r5, r5, r7
	cmp r4, #0x0
	bgt _020580CC
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_020580F4
sub_020580F4: ; 0x020580F4
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	add r6, r3, #0x0
	bl MapObjectManager_GetObjectCount
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, r7
	blt _0205810E
	mov r0, #0x0
	pop {r3-r7, pc}
_0205810E:
	add r0, r4, #0x0
	bl sub_020583C4
	mov r1, #0x4a
	ldr r2, [r5, #0x0]
	lsl r1, r1, #0x2
	mul r1, r2
	add r4, r0, r1
_0205811E:
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	bl MapObject_GetFlagsBits
	cmp r6, r0
	bne _02058138
	ldr r0, [sp, #0x0]
	str r4, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_02058138:
	mov r0, #0x4a
	lsl r0, r0, #0x2
	add r4, r4, r0
	ldr r0, [r5, #0x0]
	cmp r0, r7
	blt _0205811E
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_02058148
sub_02058148: ; 0x02058148
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x4
	bl MapObject_SetFlagsBits
	add r0, r4, #0x0
	bl sub_0205815C
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0205815C
sub_0205815C: ; 0x0205815C
	ldr r3, _02058164 ; =MapObject_ClearFlagsBits
	ldr r1, _02058168 ; =0x05108000
	bx r3
	nop
_02058164: .word MapObject_ClearFlagsBits
_02058168: .word 0x05108000

	thumb_func_start sub_0205816C
sub_0205816C: ; 0x0205816C
	bx lr
	.balign 4

	thumb_func_start sub_02058170
sub_02058170: ; 0x02058170
	push {r3, lr}
	cmp r1, #0x65
	blt _02058186
	cmp r1, #0x75
	bgt _02058186
	sub r1, #0x65
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl sub_02039504
	add r1, r0, #0x0
_02058186:
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205818C
sub_0205818C: ; 0x0205818C
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xc
	add r4, r0, #0x0
	bl MapObject_GetFlagsBits
	cmp r0, #0x0
	beq _020581A2
	add r0, r4, #0x0
	bl sub_02059D1C
_020581A2:
	pop {r4, pc}

	thumb_func_start sub_020581A4
sub_020581A4: ; 0x020581A4
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02057EE0
	add r0, r4, #0x0
	bl sub_02058EE8
	pop {r4, pc}

	thumb_func_start sub_020581B4
sub_020581B4: ; 0x020581B4
	push {r4, lr}
	add r4, r0, #0x0
	bl MapObject_GetManager
	bl sub_020587E0
	cmp r0, #0x0
	beq _020581F6
	add r0, r4, #0x0
	bl sub_0205818C
	add r0, r4, #0x0
	mov r1, #0x0
	bl sub_02058544
	add r0, r4, #0x0
	mov r1, #0x0
	bl ov05_021F2E0C
	add r0, r4, #0x0
	bl MapObject_CheckFlag14
	cmp r0, #0x0
	bne _020581F6
	add r0, r4, #0x0
	bl sub_02057F18
	add r0, r4, #0x0
	bl sub_0205868C
	add r0, r4, #0x0
	bl sub_02058878
_020581F6:
	pop {r4, pc}

	thumb_func_start sub_020581F8
sub_020581F8: ; 0x020581F8
	push {r3, lr}
	bl MapObject_GetScript
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _02058210 ; =0x0000FFFF
	cmp r1, r0
	bne _0205820C
	mov r0, #0x1
	pop {r3, pc}
_0205820C:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02058210: .word 0x0000FFFF

	thumb_func_start sub_02058214
sub_02058214: ; 0x02058214
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl MapObject_CheckFlag25
	cmp r0, #0x1
	beq _02058228
	bl GF_AssertFail
_02058228:
	add r0, r5, #0x0
	mov r1, #0x0
	bl sub_020589B0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_0205844C
	add r0, r4, #0x0
	bl sub_02058C24
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetScript
	add r0, r4, #0x0
	bl ObjectEvent_GetFlagId
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetFlagID
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02058258
sub_02058258: ; 0x02058258
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	add r4, r1, #0x0
	bl ObjectEvent_ScriptIdIsUnset
	cmp r0, #0x1
	beq _0205826E
	bl GF_AssertFail
_0205826E:
	add r0, r5, #0x0
	mov r1, #0x1
	bl sub_020589B0
	add r0, r6, #0x0
	bl sub_02058C24
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetScript
	add r0, r6, #0x0
	bl ObjectEvent_GetFlagID_AssertScriptIdIsUnset
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MapObject_SetFlagID
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0205844C
	pop {r4-r6, pc}

	thumb_func_start sub_0205829C
sub_0205829C: ; 0x0205829C
	push {r4, lr}
	add r4, r1, #0x0
	bl sub_02058744
	add r0, r0, r4
	pop {r4, pc}

	thumb_func_start sub_020582A8
sub_020582A8: ; 0x020582A8
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl MapObject_TestFlagsBits
	cmp r0, #0x0
	bne _020582BE
	mov r0, #0x0
	pop {r4-r6, pc}
_020582BE:
	add r0, r5, #0x0
	bl MapObject_GetID
	cmp r6, r0
	beq _020582CC
	mov r0, #0x0
	pop {r4-r6, pc}
_020582CC:
	add r0, r5, #0x0
	bl sub_02058450
	cmp r4, r0
	beq _020582F2
	add r0, r5, #0x0
	bl MapObject_CheckFlag25
	cmp r0, #0x0
	bne _020582E4
	mov r0, #0x0
	pop {r4-r6, pc}
_020582E4:
	add r0, r5, #0x0
	bl sub_02058750
	cmp r4, r0
	beq _020582F2
	mov r0, #0x0
	pop {r4-r6, pc}
_020582F2:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_020582F8
sub_020582F8: ; 0x020582F8
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl MapObject_TestFlagsBits
	cmp r0, #0x0
	bne _02058310
	mov r0, #0x0
	pop {r3-r7, pc}
_02058310:
	add r0, r5, #0x0
	bl sub_0205845C
	cmp r0, r4
	beq _0205831E
	mov r0, #0x0
	pop {r3-r7, pc}
_0205831E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl sub_020582A8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0205832C
sub_0205832C: ; 0x0205832C
	push {r4, lr}
	add r4, r1, #0x0
	add r0, r4, #0x0
	bl sub_02058EF8
	add r0, r4, #0x0
	bl MapObject_IsInUse
	cmp r0, #0x0
	beq _02058346
	add r0, r4, #0x0
	bl sub_02058348
_02058346:
	pop {r4, pc}

	thumb_func_start sub_02058348
sub_02058348: ; 0x02058348
	push {r4, lr}
	add r4, r0, #0x0
	bl MapObject_GetManager
	bl sub_020587E0
	cmp r0, #0x1
	bne _0205835E
	add r0, r4, #0x0
	bl ov05_021F1D8C
_0205835E:
	pop {r4, pc}

	thumb_func_start MapObjectManager_GetMapObjectManager
MapObjectManager_GetMapObjectManager: ; 0x02058360
	bx lr
	.balign 4

	thumb_func_start MapObjectManager_SetObjectCount
MapObjectManager_SetObjectCount: ; 0x02058364
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start MapObjectManager_GetObjectCount
MapObjectManager_GetObjectCount: ; 0x02058368
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start sub_0205836C
sub_0205836C: ; 0x0205836C
	ldr r1, [r0, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start sub_02058374
sub_02058374: ; 0x02058374
	ldr r1, [r0, #0x8]
	sub r1, r1, #0x1
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start sub_0205837C
sub_0205837C: ; 0x0205837C
	ldr r2, [r0, #0x0]
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start sub_02058384
sub_02058384: ; 0x02058384
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058390
sub_02058390: ; 0x02058390
	ldr r0, [r0, #0x0]
	and r0, r1
	bx lr
	.balign 4

	thumb_func_start MapObjectManager_SetPriority
MapObjectManager_SetPriority: ; 0x02058398
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start MapObjectManager_GetPriority
MapObjectManager_GetPriority: ; 0x0205839C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start sub_020583A0
sub_020583A0: ; 0x020583A0
	add r0, #0x18
	bx lr

	thumb_func_start sub_020583A4
sub_020583A4: ; 0x020583A4
	mov r2, #0x12
	lsl r2, r2, #0x4
	str r1, [r0, r2]
	bx lr

	thumb_func_start sub_020583AC
sub_020583AC: ; 0x020583AC
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MapObjectManager_SetObjects
MapObjectManager_SetObjects: ; 0x020583B4
	mov r2, #0x49
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start sub_020583BC
sub_020583BC: ; 0x020583BC
	mov r1, #0x49
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start sub_020583C4
sub_020583C4: ; 0x020583C4
	mov r1, #0x49
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MapObjectManager_GetObjects
MapObjectManager_GetObjects: ; 0x020583CC
	mov r1, #0x49
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start sub_020583D4
sub_020583D4: ; 0x020583D4
	mov r1, #0x4a
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x2
	add r1, r2, r1
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start MapObjectManager_SetFieldSystemPtr
MapObjectManager_SetFieldSystemPtr: ; 0x020583E0
	mov r2, #0x4a
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start MapObjectManager_GetFieldSystemPtr
MapObjectManager_GetFieldSystemPtr: ; 0x020583E8
	mov r1, #0x4a
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start sub_020583F0
sub_020583F0: ; 0x020583F0
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start sub_020583F4
sub_020583F4: ; 0x020583F4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02058402
	bl GF_AssertFail
_02058402:
	ldr r0, [r4, #0x14]
	pop {r4, pc}
	.balign 4

	thumb_func_start MapObject_SetFlagsWord
MapObject_SetFlagsWord: ; 0x02058408
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start MapObject_GetFlagsWord
MapObject_GetFlagsWord: ; 0x0205840C
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start MapObject_SetFlagsBits
MapObject_SetFlagsBits: ; 0x02058410
	ldr r2, [r0, #0x0]
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start MapObject_ClearFlagsBits
MapObject_ClearFlagsBits: ; 0x02058418
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start MapObject_GetFlagsBits
MapObject_GetFlagsBits: ; 0x02058424
	ldr r0, [r0, #0x0]
	and r0, r1
	bx lr
	.balign 4

	thumb_func_start MapObject_TestFlagsBits
MapObject_TestFlagsBits: ; 0x0205842C
	ldr r0, [r0, #0x0]
	tst r0, r1
	beq _02058436
	mov r0, #0x1
	bx lr
_02058436:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start MapObject_SetFlags2Word
MapObject_SetFlags2Word: ; 0x0205843C
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start MapObject_GetFlags2Word
MapObject_GetFlags2Word: ; 0x02058440
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start MapObject_SetID
MapObject_SetID: ; 0x02058444
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start MapObject_GetID
MapObject_GetID: ; 0x02058448
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start sub_0205844C
sub_0205844C: ; 0x0205844C
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start sub_02058450
sub_02058450: ; 0x02058450
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start MapObject_SetGfxID
MapObject_SetGfxID: ; 0x02058454
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start MapObject_GetGfxID
MapObject_GetGfxID: ; 0x02058458
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start sub_0205845C
sub_0205845C: ; 0x0205845C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl MapObject_GetGfxID
	add r4, r0, #0x0
	bl sub_0205C334
	cmp r0, #0x1
	bne _02058476
	add r0, r5, #0x0
	bl sub_0205C340
	add r4, r0, #0x0
_02058476:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start MapObject_SetMovement
MapObject_SetMovement: ; 0x0205847C
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start MapObject_GetMovement
MapObject_GetMovement: ; 0x02058480
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start MapObject_SetType
MapObject_SetType: ; 0x02058484
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start MapObject_GetType
MapObject_GetType: ; 0x02058488
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start MapObject_SetFlagID
MapObject_SetFlagID: ; 0x0205848C
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start MapObject_GetFlagID
MapObject_GetFlagID: ; 0x02058490
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start MapObject_SetScript
MapObject_SetScript: ; 0x02058494
	str r1, [r0, #0x20]
	bx lr

	thumb_func_start MapObject_GetScript
MapObject_GetScript: ; 0x02058498
	ldr r0, [r0, #0x20]
	bx lr

	thumb_func_start MapObject_SetInitialFacingDirection
MapObject_SetInitialFacingDirection: ; 0x0205849C
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start MapObject_GetInitialFacingDirection
MapObject_GetInitialFacingDirection: ; 0x020584A0
	ldr r0, [r0, #0x24]
	bx lr

	thumb_func_start MapObject_SetFacingDirectionDirect
MapObject_SetFacingDirectionDirect: ; 0x020584A4
	ldr r2, [r0, #0x28]
	str r2, [r0, #0x30]
	str r1, [r0, #0x28]
	bx lr

	thumb_func_start sub_020584AC
sub_020584AC: ; 0x020584AC
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x80
	add r5, r0, #0x0
	bl MapObject_GetFlagsBits
	cmp r0, #0x0
	bne _020584C2
	ldr r0, [r5, #0x28]
	str r0, [r5, #0x30]
	str r4, [r5, #0x28]
_020584C2:
	pop {r3-r5, pc}

	thumb_func_start MapObject_GetFacingDirection
MapObject_GetFacingDirection: ; 0x020584C4
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start sub_020584C8
sub_020584C8: ; 0x020584C8
	ldr r0, [r0, #0x30]
	bx lr

	thumb_func_start MapObject_SetNextFacingDirection
MapObject_SetNextFacingDirection: ; 0x020584CC
	ldr r2, [r0, #0x2c]
	str r2, [r0, #0x34]
	str r1, [r0, #0x2c]
	bx lr

	thumb_func_start MapObject_GetNextFacingDirection
MapObject_GetNextFacingDirection: ; 0x020584D4
	ldr r0, [r0, #0x2c]
	bx lr

	thumb_func_start sub_020584D8
sub_020584D8: ; 0x020584D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_020584AC
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MapObject_SetNextFacingDirection
	pop {r3-r5, pc}

	thumb_func_start MapObject_SetParam
MapObject_SetParam: ; 0x020584EC
	push {r3, lr}
	cmp r2, #0x0
	beq _020584FC
	cmp r2, #0x1
	beq _02058500
	cmp r2, #0x2
	beq _02058504
	b _02058508
_020584FC:
	str r1, [r0, #0x38]
	pop {r3, pc}
_02058500:
	str r1, [r0, #0x3c]
	pop {r3, pc}
_02058504:
	str r1, [r0, #0x40]
	pop {r3, pc}
_02058508:
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4

	thumb_func_start MapObject_GetParam
MapObject_GetParam: ; 0x02058510
	push {r3, lr}
	cmp r1, #0x0
	beq _02058520
	cmp r1, #0x1
	beq _02058524
	cmp r1, #0x2
	beq _02058528
	b _0205852C
_02058520:
	ldr r0, [r0, #0x38]
	pop {r3, pc}
_02058524:
	ldr r0, [r0, #0x3c]
	pop {r3, pc}
_02058528:
	ldr r0, [r0, #0x40]
	pop {r3, pc}
_0205852C:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start MapObject_SetXRange
MapObject_SetXRange: ; 0x02058534
	str r1, [r0, #0x44]
	bx lr

	thumb_func_start MapObject_GetXRange
MapObject_GetXRange: ; 0x02058538
	ldr r0, [r0, #0x44]
	bx lr

	thumb_func_start MapObject_SetYRange
MapObject_SetYRange: ; 0x0205853C
	str r1, [r0, #0x48]
	bx lr

	thumb_func_start MapObject_GetYRange
MapObject_GetYRange: ; 0x02058540
	ldr r0, [r0, #0x48]
	bx lr

	thumb_func_start sub_02058544
sub_02058544: ; 0x02058544
	add r0, #0xa0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0205854C
sub_0205854C: ; 0x0205854C
	add r0, #0xa0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058554
sub_02058554: ; 0x02058554
	add r0, #0xb0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0205855C
sub_0205855C: ; 0x0205855C
	add r0, #0xb0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058564
sub_02058564: ; 0x02058564
	push {r3, lr}
	bl sub_0205855C
	bl sub_0200CAB4
	pop {r3, pc}

	thumb_func_start sub_02058570
sub_02058570: ; 0x02058570
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start MapObject_GetManager
MapObject_GetManager: ; 0x02058578
	add r0, #0xb4
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02058580
sub_02058580: ; 0x02058580
	ldr r3, _02058588 ; =MapObjectManager_GetMapObjectManager
	add r0, #0xb4
	ldr r0, [r0, #0x0]
	bx r3
	.balign 4
_02058588: .word MapObjectManager_GetMapObjectManager

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

	thumb_func_start MapObject_GetFieldSystemPtr
MapObject_GetFieldSystemPtr: ; 0x02058738
	push {r3, lr}
	bl sub_02058580
	bl MapObjectManager_GetFieldSystemPtr
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
	bl MapObject_GetFlagID
	pop {r4, pc}

	thumb_func_start sub_02058768
sub_02058768: ; 0x02058768
	ldr r3, _02058770 ; =sub_0205837C
	mov r1, #0x6
	bx r3
	nop
_02058770: .word sub_0205837C

	thumb_func_start sub_02058774
sub_02058774: ; 0x02058774
	ldr r3, _0205877C ; =sub_02058384
	mov r1, #0x6
	bx r3
	nop
_0205877C: .word sub_02058384

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
	bl sub_02058390
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
	bl sub_02058390
	pop {r4, pc}

	thumb_func_start sub_02058804
sub_02058804: ; 0x02058804
	push {r3, lr}
	cmp r1, #0x0
	bne _02058812
	mov r1, #0x8
	bl sub_0205837C
	pop {r3, pc}
_02058812:
	mov r1, #0x8
	bl sub_02058384
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0205881C
sub_0205881C: ; 0x0205881C
	push {r3, lr}
	mov r1, #0x8
	bl sub_02058390
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

	thumb_func_start sub_02058878
sub_02058878: ; 0x02058878
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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

	thumb_func_start sub_020589B0
sub_020589B0: ; 0x020589B0
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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
	bl MapObject_GetFlagsBits
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

	thumb_func_start sub_02058C04
sub_02058C04: ; 0x02058C04
	ldrh r0, [r0, #0x2]
	bx lr

	thumb_func_start ObjectEvent_SetMovement
ObjectEvent_SetMovement: ; 0x02058C08
	strh r1, [r0, #0x4]
	bx lr

	thumb_func_start sub_02058C0C
sub_02058C0C: ; 0x02058C0C
	ldrh r0, [r0, #0x4]
	bx lr

	thumb_func_start ObjectEvent_SetType
ObjectEvent_SetType: ; 0x02058C10
	strh r1, [r0, #0x6]
	bx lr

	thumb_func_start sub_02058C14
sub_02058C14: ; 0x02058C14
	ldrh r0, [r0, #0x6]
	bx lr

	thumb_func_start ObjectEvent_SetFlagId
ObjectEvent_SetFlagId: ; 0x02058C18
	strh r1, [r0, #0x8]
	bx lr

	thumb_func_start ObjectEvent_GetFlagId
ObjectEvent_GetFlagId: ; 0x02058C1C
	ldrh r0, [r0, #0x8]
	bx lr

	thumb_func_start ObjectEvent_SetScript
ObjectEvent_SetScript: ; 0x02058C20
	strh r1, [r0, #0xa]
	bx lr

	thumb_func_start sub_02058C24
sub_02058C24: ; 0x02058C24
	ldrh r0, [r0, #0xa]
	bx lr

	thumb_func_start ObjectEvent_SetFacing
ObjectEvent_SetFacing: ; 0x02058C28
	strh r1, [r0, #0xc]
	bx lr

	thumb_func_start sub_02058C2C
sub_02058C2C: ; 0x02058C2C
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

	thumb_func_start sub_02058C58
sub_02058C58: ; 0x02058C58
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

	thumb_func_start sub_02058C80
sub_02058C80: ; 0x02058C80
	mov r1, #0x14
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start ObjectEvent_SetYRange
ObjectEvent_SetYRange: ; 0x02058C88
	strh r1, [r0, #0x16]
	bx lr

	thumb_func_start sub_02058C8C
sub_02058C8C: ; 0x02058C8C
	mov r1, #0x16
	ldrsh r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start ObjectEvent_SetXCoord
ObjectEvent_SetXCoord: ; 0x02058C94
	strh r1, [r0, #0x18]
	bx lr

	thumb_func_start sub_02058C98
sub_02058C98: ; 0x02058C98
	ldrh r0, [r0, #0x18]
	bx lr

	thumb_func_start ObjectEvent_SetHeight
ObjectEvent_SetHeight: ; 0x02058C9C
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start sub_02058CA0
sub_02058CA0: ; 0x02058CA0
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start ObjectEvent_SetYCoord
ObjectEvent_SetYCoord: ; 0x02058CA4
	strh r1, [r0, #0x1a]
	bx lr

	thumb_func_start sub_02058CA8
sub_02058CA8: ; 0x02058CA8
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
	bl ObjectEvent_ScriptIdIsUnset
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

	thumb_func_start ObjectEvent_ScriptIdIsUnset
ObjectEvent_ScriptIdIsUnset: ; 0x02058CE0
	push {r3, lr}
	bl sub_02058C24
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

	thumb_func_start ObjectEvent_GetFlagID_AssertScriptIdIsUnset
ObjectEvent_GetFlagID_AssertScriptIdIsUnset: ; 0x02058CFC
	push {r4, lr}
	add r4, r0, #0x0
	bl ObjectEvent_ScriptIdIsUnset
	cmp r0, #0x1
	beq _02058D0C
	bl GF_AssertFail
_02058D0C:
	add r0, r4, #0x0
	bl ObjectEvent_GetFlagId
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
	bl MapObject_GetFlagsBits
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
