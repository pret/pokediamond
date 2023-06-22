	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02034A28
sub_02034A28: ; 0x02034A28
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	add r4, r1, #0x0
	cmp r0, #0x0
	beq _02034A38
	bl GF_AssertFail
_02034A38:
	ldr r1, _02034A44 ; =0x00000AC8
	add r0, r4, #0x0
	bl AllocFromHeap
	str r0, [r5, #0x14]
	pop {r3-r5, pc}
	.balign 4
_02034A44: .word 0x00000AC8

	thumb_func_start sub_02034A48
sub_02034A48: ; 0x02034A48
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02034A56
	bl GF_AssertFail
_02034A56:
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02034A60
sub_02034A60: ; 0x02034A60
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	add r4, r1, #0x0
	cmp r0, #0x0
	bne _02034A70
	bl GF_AssertFail
_02034A70:
	ldr r0, [r5, #0x14]
	add r1, r4, #0x0
	bl sub_02034A98
	ldr r0, [r5, #0x14]
	bl sub_02034C50
	mov r0, #0x92
	ldr r1, [r5, #0x14]
	lsl r0, r0, #0x4
	add r0, r1, r0
	add r1, r4, #0x0
	bl sub_02034CB4
	ldr r0, [r5, #0x14]
	add r1, r4, #0x0
	bl sub_02034CEC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02034A98
sub_02034A98: ; 0x02034A98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MapHeader_GetEventsBank
	add r4, r0, #0x0
	mov r0, #0x20
	add r1, r4, #0x0
	bl GetNarcMemberSizeByIdPair
	mov r1, #0x2
	lsl r1, r1, #0xa
	cmp r0, r1
	blo _02034AB8
	bl GF_AssertFail
_02034AB8:
	add r5, #0x20
	add r0, r5, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl ReadWholeNarcMemberByIdPair
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02034AC8
sub_02034AC8: ; 0x02034AC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	ldr r4, [r0, #0x4]
	cmp r0, #0x0
	bne _02034AD8
	bl GF_AssertFail
_02034AD8:
	cmp r4, #0x0
	beq _02034AEC
	ldr r1, [r5, #0x1c]
	ldr r3, [r5, #0x14]
	ldr r0, [r5, #0x34]
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x14]
	add r2, r4, #0x0
	bl sub_02057BAC
_02034AEC:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02034AF0
sub_02034AF0: ; 0x02034AF0
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x10]
	bx lr
	.balign 4

	thumb_func_start sub_02034AF8
sub_02034AF8: ; 0x02034AF8
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02034B00
sub_02034B00: ; 0x02034B00
	ldr r2, [r0, #0x14]
	ldr r0, [r2, #0x8]
	cmp r1, r0
	blo _02034B0C
	mov r0, #0x0
	bx lr
_02034B0C:
	mov r0, #0xc
	ldr r2, [r2, #0x18]
	mul r0, r1
	add r0, r2, r0
	bx lr
	.balign 4

	thumb_func_start sub_02034B18
sub_02034B18: ; 0x02034B18
	push {r4-r7}
	ldr r5, [r0, #0x14]
	mov r3, #0x0
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bls _02034B4A
	ldr r6, [r5, #0x18]
	add r4, r3, #0x0
	add r0, r6, #0x0
_02034B2A:
	ldrh r7, [r0, #0x0]
	cmp r1, r7
	bne _02034B3E
	add r7, r6, r4
	ldrh r7, [r7, #0x2]
	cmp r2, r7
	bne _02034B3E
	add r0, r3, #0x0
	pop {r4-r7}
	bx lr
_02034B3E:
	ldr r7, [r5, #0x8]
	add r3, r3, #0x1
	add r0, #0xc
	add r4, #0xc
	cmp r3, r7
	blo _02034B2A
_02034B4A:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start sub_02034B54
sub_02034B54: ; 0x02034B54
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start sub_02034B5C
sub_02034B5C: ; 0x02034B5C
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x1c]
	bx lr
	.balign 4

	thumb_func_start sub_02034B64
sub_02034B64: ; 0x02034B64
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start sub_02034B6C
sub_02034B6C: ; 0x02034B6C
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start SetEventDefaultXYPos
SetEventDefaultXYPos: ; 0x02034B74
	push {r3-r7, lr}
	ldr r0, [r0, #0x14]
	add r4, r1, #0x0
	ldr r5, [r0, #0x4]
	add r7, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x0
	ldr r3, [r0, #0x14]
	cmp r5, #0x0
	bls _02034BA4
	add r6, r3, #0x0
_02034B8A:
	ldrh r0, [r6, #0x0]
	cmp r4, r0
	bne _02034B9C
	lsl r0, r2, #0x5
	add r0, r3, r0
	strh r7, [r0, #0x18]
	strh r1, [r0, #0x1a]
	mov r0, #0x1
	pop {r3-r7, pc}
_02034B9C:
	add r2, r2, #0x1
	add r6, #0x20
	cmp r2, r5
	blo _02034B8A
_02034BA4:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start SetEventDefaultDirection
SetEventDefaultDirection: ; 0x02034BAC
	push {r4-r6, lr}
	ldr r0, [r0, #0x14]
	mov r3, #0x0
	ldr r5, [r0, #0x4]
	ldr r4, [r0, #0x14]
	cmp r5, #0x0
	bls _02034BD4
	add r6, r4, #0x0
_02034BBC:
	ldrh r0, [r6, #0x0]
	cmp r1, r0
	bne _02034BCC
	lsl r0, r3, #0x5
	add r0, r4, r0
	strh r2, [r0, #0xc]
	mov r0, #0x1
	pop {r4-r6, pc}
_02034BCC:
	add r3, r3, #0x1
	add r6, #0x20
	cmp r3, r5
	blo _02034BBC
_02034BD4:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start SetEventDefaultMovement
SetEventDefaultMovement: ; 0x02034BDC
	push {r4-r6, lr}
	ldr r0, [r0, #0x14]
	mov r3, #0x0
	ldr r5, [r0, #0x4]
	ldr r4, [r0, #0x14]
	cmp r5, #0x0
	bls _02034C04
	add r6, r4, #0x0
_02034BEC:
	ldrh r0, [r6, #0x0]
	cmp r1, r0
	bne _02034BFC
	lsl r0, r3, #0x5
	add r0, r4, r0
	strh r2, [r0, #0x4]
	mov r0, #0x1
	pop {r4-r6, pc}
_02034BFC:
	add r3, r3, #0x1
	add r6, #0x20
	cmp r3, r5
	blo _02034BEC
_02034C04:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start SetWarpXYPos
SetWarpXYPos: ; 0x02034C0C
	push {r3-r4}
	ldr r0, [r0, #0x14]
	ldr r4, [r0, #0x18]
	mov r0, #0xc
	mul r0, r1
	strh r2, [r4, r0]
	add r0, r4, r0
	strh r3, [r0, #0x2]
	mov r0, #0x1
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start sub_02034C24
sub_02034C24: ; 0x02034C24
	ldr r0, [r0, #0x14]
	ldr r3, [r0, #0x18]
	mov r0, #0xc
	mul r0, r1
	add r0, r3, r0
	strh r2, [r0, #0x4]
	mov r0, #0x1
	bx lr

	thumb_func_start SetBgEventXYPos
SetBgEventXYPos: ; 0x02034C34
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl sub_02034AF0
	mov r1, #0x14
	mul r1, r5
	add r0, r0, r1
	str r4, [r0, #0x4]
	str r6, [r0, #0x8]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02034C50
sub_02034C50: ; 0x02034C50
	add r1, r0, #0x0
	ldr r2, [r0, #0x20]
	add r1, #0x20
	add r1, r1, #0x4
	str r2, [r0, #0x0]
	cmp r2, #0x0
	beq _02034C62
	str r1, [r0, #0x10]
	b _02034C66
_02034C62:
	mov r2, #0x0
	str r2, [r0, #0x10]
_02034C66:
	ldr r3, [r0, #0x0]
	mov r2, #0x14
	mul r2, r3
	add r3, r1, r2
	ldr r2, [r1, r2]
	add r1, r3, #0x4
	str r2, [r0, #0x4]
	cmp r2, #0x0
	beq _02034C7C
	str r1, [r0, #0x14]
	b _02034C80
_02034C7C:
	mov r2, #0x0
	str r2, [r0, #0x14]
_02034C80:
	ldr r2, [r0, #0x4]
	lsl r2, r2, #0x5
	add r3, r1, r2
	ldr r2, [r1, r2]
	add r1, r3, #0x4
	str r2, [r0, #0x8]
	cmp r2, #0x0
	beq _02034C94
	str r1, [r0, #0x18]
	b _02034C98
_02034C94:
	mov r2, #0x0
	str r2, [r0, #0x18]
_02034C98:
	ldr r3, [r0, #0x8]
	mov r2, #0xc
	mul r2, r3
	add r3, r1, r2
	ldr r1, [r1, r2]
	str r1, [r0, #0xc]
	cmp r1, #0x0
	beq _02034CAE
	add r1, r3, #0x4
	str r1, [r0, #0x1c]
	bx lr
_02034CAE:
	mov r1, #0x0
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start sub_02034CB4
sub_02034CB4: ; 0x02034CB4
	push {r3-r5, lr}
	mov r2, #0x6a
	add r4, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r5, r0, #0x0
	bl memset
	add r0, r4, #0x0
	bl MapHeader_HasWildEncounters
	cmp r0, #0x0
	beq _02034CDE
	add r0, r4, #0x0
	bl MapHeader_GetWildEncounterBank
	add r2, r0, #0x0
	add r0, r5, #0x0
	.ifdef DIAMOND
	mov r1, #0x25
	.else
	mov r1, #0x8f
	.endif
	bl ReadWholeNarcMemberByIdPair
_02034CDE:
	pop {r3-r5, pc}

	thumb_func_start sub_02034CE0
sub_02034CE0: ; 0x02034CE0
	ldr r1, [r0, #0x14]
	mov r0, #0x92
	lsl r0, r0, #0x4
	add r0, r1, r0
	bx lr
	.balign 4

	thumb_func_start sub_02034CEC
sub_02034CEC: ; 0x02034CEC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MapHeader_GetLevelScriptsBank
	mov r1, #0x82
	lsl r1, r1, #0x4
	mov r2, #0x1
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r5, r1
	lsl r2, r2, #0x8
	bl MIi_CpuClearFast
	mov r0, #0xa
	add r1, r4, #0x0
	bl GetNarcMemberSizeByIdPair
	mov r1, #0x1
	lsl r1, r1, #0x8
	cmp r0, r1
	blo _02034D1C
	bl GF_AssertFail
_02034D1C:
	mov r0, #0x82
	lsl r0, r0, #0x4
	add r0, r5, r0
	mov r1, #0xa
	add r2, r4, #0x0
	bl ReadWholeNarcMemberByIdPair
	pop {r3-r5, pc}

	thumb_func_start sub_02034D2C
sub_02034D2C: ; 0x02034D2C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02034D3A
	bl GF_AssertFail
_02034D3A:
	mov r0, #0x82
	ldr r1, [r4, #0x14]
	lsl r0, r0, #0x4
	add r0, r1, r0
	pop {r4, pc}

	thumb_func_start sub_02034D44
sub_02034D44: ; 0x02034D44
	push {r4-r7}
	ldr r0, [r0, #0x14]
	mov r3, #0x0
	ldr r4, [r0, #0x4]
	cmp r4, #0x0
	bls _02034D76
	ldr r6, [r0, #0x14]
	add r5, r3, #0x0
	add r4, r6, #0x0
_02034D56:
	ldrh r7, [r4, #0x18]
	cmp r1, r7
	bne _02034D6A
	add r7, r6, r5
	ldrh r7, [r7, #0x1a]
	cmp r2, r7
	bne _02034D6A
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_02034D6A:
	ldr r7, [r0, #0x4]
	add r3, r3, #0x1
	add r4, #0x20
	add r5, #0x20
	cmp r3, r7
	blo _02034D56
_02034D76:
	mov r0, #0x1
	pop {r4-r7}
	bx lr
