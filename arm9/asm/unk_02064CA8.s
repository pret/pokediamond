	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7E48
UNK_020F7E48: ; 0x020F7E48
	.byte 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01

	.global UNK_020F7E54
UNK_020F7E54: ; 0x020F7E54
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x01

	.text

	thumb_func_start InitPastoriaGym
InitPastoriaGym: ; 0x02064CA8
	push {r4, lr}
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	add r4, r0, #0x0
	mov r1, #0x1
	bl sub_02025490
	add r0, r4, #0x0
	mov r1, #0x1
	bl sub_020254A0
	mov r1, #0x1
	strb r1, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start InitHearthomeGym
InitHearthomeGym: ; 0x02064CC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	add r4, r0, #0x0
	mov r1, #0x2
	bl sub_02025490
	add r0, r4, #0x0
	mov r1, #0x2
	bl sub_020254A0
	add r4, r0, #0x0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0xc]
	cmp r0, #0x16
	bne _02064D08
	ldr r0, [r5, #0xc]
	bl Save_VarsFlags_Get
	bl sub_0205ECEC
	cmp r0, #0x0
	beq _02064D02
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_02064D02:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_02064D08:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start InitCanalaveGym
InitCanalaveGym: ; 0x02064D10
	push {r4-r6, lr}
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	add r4, r0, #0x0
	mov r1, #0x3
	bl sub_02025490
	add r0, r4, #0x0
	mov r1, #0x3
	bl sub_020254A0
	ldr r5, _02064D48 ; =UNK_020F7E54
	add r6, r0, #0x0
	mov r4, #0x0
_02064D30:
	ldrb r1, [r5, #0x0]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r2, r6, #0x0
	bl sub_02064DEC
	add r4, r4, #0x1
	add r5, r5, #0x1
	cmp r4, #0x18
	blt _02064D30
	pop {r4-r6, pc}
	nop
_02064D48: .word UNK_020F7E54

	thumb_func_start InitVeilstoneGym
InitVeilstoneGym: ; 0x02064D4C
	push {r4-r6, lr}
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	add r4, r0, #0x0
	mov r1, #0x4
	bl sub_02025490
	add r0, r4, #0x0
	mov r1, #0x4
	bl sub_020254A0
	ldr r5, _02064D84 ; =UNK_020F7E48
	add r6, r0, #0x0
	mov r4, #0x0
_02064D6C:
	ldrb r1, [r5, #0x0]
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r2, r6, #0x0
	bl sub_02064DEC
	add r4, r4, #0x1
	add r5, r5, #0x1
	cmp r4, #0xc
	blt _02064D6C
	pop {r4-r6, pc}
	nop
_02064D84: .word UNK_020F7E48

	thumb_func_start InitSunyshoreGym
InitSunyshoreGym: ; 0x02064D88
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	cmp r5, #0x3
	blo _02064D96
	bl GF_AssertFail
_02064D96:
	add r0, r7, #0x0
	bl FieldSystem_GetSaveData
	bl sub_02024ED8
	add r4, r0, #0x0
	mov r1, #0x5
	bl sub_02025490
	add r0, r4, #0x0
	mov r1, #0x5
	bl sub_020254A0
	add r4, r0, #0x0
	str r5, [r4, #0x4]
	cmp r5, #0x0
	beq _02064DC2
	cmp r5, #0x1
	beq _02064DCA
	cmp r5, #0x2
	beq _02064DD2
	b _02064DDA
_02064DC2:
	mov r0, #0x2
	str r0, [r4, #0x0]
	mov r6, #0xe
	b _02064DDE
_02064DCA:
	mov r0, #0x1
	str r0, [r4, #0x0]
	mov r6, #0x15
	b _02064DDE
_02064DD2:
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r6, #0x19
	b _02064DDE
_02064DDA:
	bl GF_AssertFail
_02064DDE:
	ldr r0, [r7, #0x1c]
	ldr r0, [r0, #0xc]
	cmp r0, r6
	bne _02064DEA
	mov r0, #0x0
	str r0, [r4, #0x0]
_02064DEA:
	pop {r3-r7, pc}

	thumb_func_start sub_02064DEC
sub_02064DEC: ; 0x02064DEC
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x1
	bls _02064DFC
	bl GF_AssertFail
_02064DFC:
	mov r0, #0x0
	mvn r0, r0
	mov r1, #0x20
	ldr r2, [r6, #0x0]
	sub r1, r1, r5
	add r3, r0, #0x0
	lsr r3, r1
	add r1, r2, #0x0
	and r1, r3
	add r3, r5, #0x1
	lsl r0, r3
	and r2, r0
	add r0, r4, #0x0
	lsl r0, r5
	orr r0, r2
	orr r0, r1
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
