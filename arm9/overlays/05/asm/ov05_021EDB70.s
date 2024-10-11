	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021EDB70
ov05_021EDB70: ; 0x021EDB70
	push {r3, r4, r5, lr}
	mov r2, #0
	mov r1, #0x60
	add r3, r2, #0
	add r5, r0, #0
	bl ov05_021E4BE8
	add r4, r0, #0
	str r5, [r4]
	bl ov05_021EDB9C
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021EDB8C
ov05_021EDB8C: ; 0x021EDB8C
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021EDBBC
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov05_021EDB9C
ov05_021EDB9C: ; 0x021EDB9C
	push {r3, lr}
	sub sp, #8
	add r3, r0, #0
	add r0, #0x58
	str r0, [sp]
	add r0, r3, #0
	add r0, #0x5c
	str r0, [sp, #4]
	ldr r0, [r3]
	mov r1, #0x50
	mov r2, #0
	add r3, r3, #4
	bl ov05_021E51EC
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov05_021EDBBC
ov05_021EDBBC: ; 0x021EDBBC
	ldr r3, _021EDBC4 ; =ov05_021E4C00
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_021EDBC4: .word ov05_021E4C00

	thumb_func_start ov05_021EDBC8
ov05_021EDBC8: ; 0x021EDBC8
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r2, sp, #8
	mov r1, #0
	str r1, [r2]
	str r1, [r2, #4]
	add r5, r0, #0
	str r1, [r2, #8]
	bl PlayerAvatar_GetMapObject
	add r4, r0, #0
	bl ov05_021E4C24
	add r6, r0, #0
	mov r1, #0x10
	str r6, [sp, #0x14]
	bl ov05_021E4C08
	str r0, [sp, #0x18]
	add r0, r4, #0
	mov r1, #2
	str r5, [sp, #0x1c]
	bl sub_0205829C
	add r1, sp, #0x14
	str r1, [sp]
	str r0, [sp, #4]
	ldr r1, _021EDC10 ; =ov05_021F8A6C
	add r0, r6, #0
	add r2, sp, #8
	mov r3, #0
	bl ov05_021E4DC4
	add sp, #0x20
	pop {r4, r5, r6, pc}
	nop
_021EDC10: .word ov05_021F8A6C

	thumb_func_start ov05_021EDC14
ov05_021EDC14: ; 0x021EDC14
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl sub_0206475C
	add r4, r0, #0
	add r3, r4, #0
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x24
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #8]
	bl PlayerAvatar_GetMapObject
	mov r1, #0
	mvn r1, r1
	add r4, r0, #0
	str r1, [r5, #4]
	bl MapObject_GetID
	str r0, [r5, #0x14]
	add r0, r4, #0
	bl MapObject_GetMapID
	str r0, [r5, #0x18]
	mov r0, #1
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021EDC4C
ov05_021EDC4C: ; 0x021EDC4C
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EDC50
ov05_021EDC50: ; 0x021EDC50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	str r0, [sp]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #4]
	bl PlayerAvatar_GetMapObject
	ldr r1, [r5, #0x14]
	ldr r2, [r5, #0x18]
	add r6, r0, #0
	bl sub_020582A8
	cmp r0, #0
	bne _021EDC78
	ldr r0, [sp]
	bl ov05_021E4DE4
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_021EDC78:
	ldr r7, [r5, #4]
	add r0, r6, #0
	bl sub_02058720
	strb r0, [r5, #8]
	ldrb r0, [r5, #8]
	bl ov05_021EDDF4
	str r0, [r5, #4]
	mov r0, #0
	str r0, [r5]
	ldr r4, [r5, #4]
	sub r0, r0, #1
	cmp r4, r0
	beq _021EDCA0
	ldr r0, [sp, #4]
	bl PlayerAvatar_GetFacingDirection
	cmp r4, r0
	beq _021EDCAE
_021EDCA0:
	mov r0, #0
	str r0, [r5, #0x1c]
	str r0, [r5, #0x20]
	mov r0, #1
	add sp, #0x24
	str r0, [r5]
	pop {r4, r5, r6, r7, pc}
_021EDCAE:
	cmp r7, r4
	beq _021EDCB8
	mov r0, #0
	str r0, [r5, #0x1c]
	str r0, [r5, #0x20]
_021EDCB8:
	add r0, r6, #0
	bl MapObject_GetCurrentX
	add r4, r0, #0
	ldr r0, [r5, #4]
	bl sub_02059BF4
	add r7, r0, #0
	add r0, r6, #0
	bl MapObject_GetCurrentY
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl sub_02059C00
	add r2, r0, #0
	ldr r1, [sp, #8]
	add r0, r4, r7
	add r1, r1, r2
	add r2, sp, #0xc
	bl sub_02059E60
	add r0, r6, #0
	add r1, sp, #0x18
	bl MapObject_GetPositionVec
	ldr r0, [sp, #0x1c]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	ldr r0, [sp]
	bl sub_0206476C
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EDCFC
ov05_021EDCFC: ; 0x021EDCFC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	beq _021EDDE2
	mov r0, #0
	ldr r1, [r4, #4]
	mvn r0, r0
	cmp r1, r0
	beq _021EDDE2
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0xf
	ble _021EDD34
	mov r0, #0
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, #0x20]
_021EDD34:
	ldr r3, _021EDDE8 ; =ov05_021F8A60
	add r2, sp, #0x24
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r5, _021EDDEC ; =ov05_021F8A80
	str r0, [r2]
	add r3, sp, #0
	mov r2, #4
_021EDD46:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021EDD46
	ldr r0, [r5]
	mov r2, #0x18
	str r0, [r3]
	ldr r1, [r4, #4]
	ldr r3, _021EDDF0 ; =ov05_021F8AA4
	add r0, r1, #0
	mul r0, r2
	add r0, r3, r0
	ldr r5, [r4, #0x20]
	mov r3, #0xc
	mul r3, r5
	add r5, r0, r3
	cmp r1, #3
	bhi _021EDDB4
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EDD76: ; jump table
	.short _021EDD7E - _021EDD76 - 2 ; case 0
	.short _021EDD8C - _021EDD76 - 2 ; case 1
	.short _021EDD9A - _021EDD76 - 2 ; case 2
	.short _021EDDA8 - _021EDD76 - 2 ; case 3
_021EDD7E:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0xb4
	add r3, r1, #0
	bl sub_0201CB20
	b _021EDDB4
_021EDD8C:
	mov r1, #0
	add r0, sp, #0
	add r2, r1, #0
	add r3, r1, #0
	bl sub_0201CB20
	b _021EDDB4
_021EDD9A:
	mov r1, #0
	add r0, sp, #0
	add r2, #0xf6
	add r3, r1, #0
	bl sub_0201CB20
	b _021EDDB4
_021EDDA8:
	mov r1, #0
	add r0, sp, #0
	mov r2, #0x5a
	add r3, r1, #0
	bl sub_0201CB20
_021EDDB4:
	add r0, r6, #0
	add r1, sp, #0x30
	bl sub_0206477C
	ldr r1, [sp, #0x30]
	ldr r0, [r5]
	add r2, sp, #0
	add r0, r1, r0
	str r0, [sp, #0x30]
	ldr r1, [sp, #0x34]
	ldr r0, [r5, #4]
	add r3, sp, #0x24
	add r0, r1, r0
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x38]
	ldr r0, [r5, #8]
	add r0, r1, r0
	str r0, [sp, #0x38]
	ldr r0, [r4, #0x28]
	add r1, sp, #0x30
	add r0, r0, #4
	bl sub_0201B26C
_021EDDE2:
	add sp, #0x3c
	pop {r3, r4, r5, r6, pc}
	nop
_021EDDE8: .word ov05_021F8A60
_021EDDEC: .word ov05_021F8A80
_021EDDF0: .word ov05_021F8AA4

	thumb_func_start ov05_021EDDF4
ov05_021EDDF4: ; 0x021EDDF4
	push {r4, lr}
	add r4, r0, #0
	bl sub_020547D4
	cmp r0, #0
	beq _021EDE04
	mov r0, #0
	pop {r4, pc}
_021EDE04:
	add r0, r4, #0
	bl sub_020547E0
	cmp r0, #0
	beq _021EDE12
	mov r0, #1
	pop {r4, pc}
_021EDE12:
	add r0, r4, #0
	bl sub_020547C8
	cmp r0, #0
	beq _021EDE20
	mov r0, #2
	pop {r4, pc}
_021EDE20:
	add r0, r4, #0
	bl sub_020547BC
	cmp r0, #0
	beq _021EDE2E
	mov r0, #3
	pop {r4, pc}
_021EDE2E:
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}

	.section .rodata

	.global ov05_021F8A60
ov05_021F8A60: ; 0x021F8A60
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov05_021F8A6C
ov05_021F8A6C: ; 0x021F8A6C
	.word 0x00000030, ov05_021EDC14, ov05_021EDC4C, ov05_021EDC50
	.word ov05_021EDCFC

	.global ov05_021F8A80
ov05_021F8A80: ; 0x021F8A80
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov05_021F8AA4
ov05_021F8AA4: ; 0x021F8AA4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
