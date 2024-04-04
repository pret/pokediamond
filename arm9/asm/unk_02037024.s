	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02037024
sub_02037024: ; 0x02037024
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	add r5, r0, #0x0
	bl sub_02036FA4
	add r4, r0, #0x0
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl sub_0204A6E0
	bl sub_020547A4
	cmp r0, #0x1
	bne _0203707E
	cmp r4, #0x3
	bhi _0203707E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02037058: ; jump table (using 16-bit offset)
	.short _02037060 - _02037058 - 2; case 0
	.short _02037068 - _02037058 - 2; case 1
	.short _02037070 - _02037058 - 2; case 2
	.short _02037078 - _02037058 - 2; case 3
_02037060:
	ldr r0, [sp, #0x0]
	sub r0, r0, #0x1
	str r0, [sp, #0x0]
	b _0203707E
_02037068:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	b _0203707E
_02037070:
	ldr r0, [sp, #0x4]
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
	b _0203707E
_02037078:
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0203707E:
	ldr r0, [r5, #0x34]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	bl sub_02058D74
	str r0, [r6, #0x0]
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02037090
sub_02037090: ; 0x02037090
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl sub_02037024
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020370B8
	bl sub_020588D4
	cmp r0, #0x1
	bne _020370B8
	ldr r0, [r5, #0x38]
	ldr r1, [r4, #0x0]
	bl sub_02037000
	cmp r0, #0x1
	bne _020370B8
	mov r0, #0x1
	pop {r3-r5, pc}
_020370B8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_020370BC
sub_020370BC: ; 0x020370BC
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r1, sp, #0xc
	add r2, sp, #0x8
	add r6, r0, #0x0
	bl sub_02036FA4
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	cmp r0, #0x0
	ble _02037130
	ldr r4, [sp, #0x0]
	add r5, r4, #0x0
_020370DA:
	ldr r1, [sp, #0xc]
	ldr r0, [r4, #0x4]
	cmp r1, r0
	bne _02037124
	ldr r1, [sp, #0x8]
	ldr r0, [r4, #0x8]
	cmp r1, r0
	bne _02037124
	ldrh r0, [r4, #0x2]
	cmp r0, #0x2
	bne _0203710A
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_0203713C
	cmp r0, #0x1
	bne _02037124
	mov r0, #0x14
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x10
	ldrh r0, [r0, r1]
	pop {r3-r7, pc}
_0203710A:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_02037168
	cmp r0, #0x1
	bne _02037124
	mov r0, #0x14
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x10
	ldrh r0, [r0, r1]
	pop {r3-r7, pc}
_02037124:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r4, #0x14
	add r5, #0x14
	cmp r7, r0
	blt _020370DA
_02037130:
	ldr r0, _02037138 ; =0x0000FFFF
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02037138: .word 0x0000FFFF

	thumb_func_start sub_0203713C
sub_0203713C: ; 0x0203713C
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r1, #0x2]
	cmp r0, #0x2
	beq _0203714A
	mov r0, #0x0
	pop {r4, pc}
_0203714A:
	ldrh r0, [r1, #0x0]
	bl sub_02039694
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FieldSystem_FlagCheck
	cmp r0, #0x1
	beq _02037160
	mov r0, #0x1
	b _02037162
_02037160:
	mov r0, #0x0
_02037162:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}

	thumb_func_start sub_02037168
sub_02037168: ; 0x02037168
	push {r4, lr}
	add r4, r1, #0x0
	ldrh r1, [r4, #0x10]
	cmp r1, #0x4
	bne _02037176
	mov r0, #0x1
	pop {r4, pc}
_02037176:
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0x3
	bhi _020371CC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203718C: ; jump table (using 16-bit offset)
	.short _02037194 - _0203718C - 2; case 0
	.short _020371A2 - _0203718C - 2; case 1
	.short _020371B0 - _0203718C - 2; case 2
	.short _020371BE - _0203718C - 2; case 3
_02037194:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0203719E
	cmp r0, #0x6
	bne _020371CC
_0203719E:
	mov r0, #0x1
	pop {r4, pc}
_020371A2:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x3
	beq _020371AC
	cmp r0, #0x6
	bne _020371CC
_020371AC:
	mov r0, #0x1
	pop {r4, pc}
_020371B0:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x2
	beq _020371BA
	cmp r0, #0x5
	bne _020371CC
_020371BA:
	mov r0, #0x1
	pop {r4, pc}
_020371BE:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x1
	beq _020371C8
	cmp r0, #0x5
	bne _020371CC
_020371C8:
	mov r0, #0x1
	pop {r4, pc}
_020371CC:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start sub_020371D0
sub_020371D0: ; 0x020371D0
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0x0
	beq _020371EA
	add sp, #0x8
	ldr r0, _0203722C ; =0x0000FFFF
	pop {r4-r6, pc}
_020371EA:
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl sub_02036FA4
	mov r0, #0x0
	cmp r4, #0x0
	ble _02037224
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	add r1, r6, #0x0
_02037200:
	ldr r5, [r1, #0x4]
	cmp r2, r5
	bne _0203721C
	ldr r5, [r1, #0x8]
	cmp r3, r5
	bne _0203721C
	ldrh r5, [r1, #0x2]
	cmp r5, #0x1
	bne _0203721C
	mov r1, #0x14
	mul r1, r0
	add sp, #0x8
	ldrh r0, [r6, r1]
	pop {r4-r6, pc}
_0203721C:
	add r0, r0, #0x1
	add r1, #0x14
	cmp r0, r4
	blt _02037200
_02037224:
	ldr r0, _0203722C ; =0x0000FFFF
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0203722C: .word 0x0000FFFF

	thumb_func_start sub_02037230
sub_02037230: ; 0x02037230
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	add r4, r1, #0x0
	bl PlayerAvatar_GetFacingDirection
	cmp r0, #0x0
	beq _02037244
	mov r0, #0x0
	pop {r3-r5, pc}
_02037244:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02037090
	cmp r0, #0x1
	bne _02037260
	ldr r0, [r4, #0x0]
	bl MapObject_GetGfxID
	sub r0, #0x5b
	cmp r0, #0x5
	bhi _02037260
	mov r0, #0x1
	pop {r3-r5, pc}
_02037260:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_02037264
sub_02037264: ; 0x02037264
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x38]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	bl GetPlayerXCoord
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x38]
	bl GetPlayerYCoord
	add r4, r0, #0x0
	ldr r0, [sp, #0x8]
	mov r7, #0x0
	cmp r0, #0x0
	ble _020372C8
	ldr r5, [sp, #0x4]
_0203728A:
	ldrh r1, [r5, #0x2]
	cmp r6, r1
	blt _020372BE
	ldrh r0, [r5, #0x6]
	add r0, r1, r0
	cmp r6, r0
	bge _020372BE
	ldrh r1, [r5, #0x4]
	cmp r4, r1
	blt _020372BE
	ldrh r0, [r5, #0x8]
	add r0, r1, r0
	cmp r4, r0
	bge _020372BE
	ldrh r1, [r5, #0xe]
	ldr r0, [sp, #0x0]
	bl FieldSystem_VarGet
	ldrh r1, [r5, #0xc]
	cmp r1, r0
	bne _020372BE
	ldr r0, [sp, #0x4]
	lsl r1, r7, #0x4
	add sp, #0xc
	ldrh r0, [r0, r1]
	pop {r4-r7, pc}
_020372BE:
	ldr r0, [sp, #0x8]
	add r7, r7, #0x1
	add r5, #0x10
	cmp r7, r0
	blt _0203728A
_020372C8:
	ldr r0, _020372D0 ; =0x0000FFFF
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_020372D0: .word 0x0000FFFF
