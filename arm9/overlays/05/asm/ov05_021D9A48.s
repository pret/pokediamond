	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021D9A48
ov05_021D9A48: ; 0x021D9A48
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #0
	ldr r1, [r7, #0x18]
	mvn r0, r0
	add r4, r3, #0
	cmp r1, r0
	bne _021D9A60
	bl GF_AssertFail
_021D9A60:
	mov r0, #0
	add r1, r6, #0
_021D9A64:
	ldr r2, [r1]
	cmp r2, #0
	beq _021D9A7A
	ldr r2, [r1, #0xc]
	cmp r4, r2
	bne _021D9A7A
	ldr r2, [r1, #4]
	cmp r2, r5
	bne _021D9A7A
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9A7A:
	add r0, r0, #1
	add r1, #0x10
	cmp r0, #2
	blt _021D9A64
	mov r2, #0
	add r1, r6, #0
_021D9A86:
	ldr r0, [r1]
	cmp r0, #0
	bne _021D9A9C
	lsl r1, r2, #4
	mov r0, #1
	str r0, [r6, r1]
	add r0, r6, r1
	str r4, [r0, #0xc]
	str r7, [r0, #8]
	str r5, [r0, #4]
	b _021D9AA4
_021D9A9C:
	add r2, r2, #1
	add r1, #0x10
	cmp r2, #2
	blt _021D9A86
_021D9AA4:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D9AA8
ov05_021D9AA8: ; 0x021D9AA8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0
	add r4, r1, #0
	mvn r0, r0
	add r7, r2, #0
	add r5, r3, #0
	cmp r4, r0
	bne _021D9ABE
	bl GF_AssertFail
_021D9ABE:
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #4
	bl NARC_AllocAndReadWholeMember
	add r4, r0, #0
	bne _021D9AD0
	bl GF_AssertFail
_021D9AD0:
	add r0, r4, #0
	mov r1, #0
	bl NNS_G3dGetAnmByIdx
	add r6, r0, #0
	bne _021D9AE0
	bl GF_AssertFail
_021D9AE0:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	add r2, r7, #0
	bl NNS_G3dAllocAnmObj
	str r0, [r5]
	cmp r5, #0
	bne _021D9AF4
	bl GF_AssertFail
_021D9AF4:
	ldr r0, [r5]
	ldr r3, [sp, #0x18]
	add r1, r6, #0
	add r2, r7, #0
	bl NNS_G3dAnmObjInit
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D9B04
ov05_021D9B04: ; 0x021D9B04
	push {r3, lr}
	cmp r1, #0
	bne _021D9B0E
	mov r0, #0
	pop {r3, pc}
_021D9B0E:
	cmp r0, #0
	bne _021D9B16
	mov r0, #0
	pop {r3, pc}
_021D9B16:
	bl NNS_G3dRenderObjRemoveAnmObj
	mov r0, #1
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9B20
ov05_021D9B20: ; 0x021D9B20
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r4, #0
_021D9B28:
	ldr r0, [r5]
	cmp r0, #0
	beq _021D9B4A
	ldr r0, [r5, #8]
	bl ov05_021DA20C
	cmp r0, #0
	beq _021D9B4A
	ldr r1, [r5, #8]
	ldr r0, [r5, #4]
	ldr r1, [r1]
	bl ov05_021D9B04
	str r6, [r5]
	str r6, [r5, #0xc]
	str r6, [r5, #8]
	str r6, [r5, #4]
_021D9B4A:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #2
	blt _021D9B28
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021D9B54
ov05_021D9B54: ; 0x021D9B54
	push {r3, r4, r5, r6, r7, lr}
	mov r1, #0xae
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	add r7, r0, #0
	mov r1, #0
	add r2, r7, #0
	add r6, r1, #0
	sub r0, r1, #1
_021D9B6A:
	str r6, [r2, #0x14]
	str r6, [r2, #0x20]
	str r6, [r2, #0x10]
	str r6, [r2, #0x18]
	str r6, [r2, #0x1c]
	str r6, [r2, #0x24]
	str r0, [r2, #0x28]
	str r6, [r2, #0x2c]
	str r6, [r2, #0x30]
	str r6, [r2, #0x34]
	add r1, r1, #1
	add r2, #0x28
	cmp r1, #0x10
	blt _021D9B6A
	mov r0, #0x29
	lsl r0, r0, #4
	add r2, r0, #0
	add r3, r0, #0
	add r5, r7, #0
	mov r4, #0
	add r1, r0, #4
	add r2, #8
	add r3, #0xc
_021D9B98:
	str r4, [r5, r0]
	str r4, [r5, r1]
	str r4, [r5, r2]
	str r4, [r5, r3]
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #2
	blt _021D9B98
	mov r1, #4
	add r0, r7, #0
	add r2, r1, #0
	bl GF_ExpHeap_FndInitAllocator
	mov r0, #0x6e
	mov r1, #4
	bl NARC_New
	mov r1, #0x2b
	lsl r1, r1, #4
	str r0, [r7, r1]
	mov r0, #0x6f
	mov r1, #4
	bl NARC_New
	mov r1, #0xad
	lsl r1, r1, #2
	str r0, [r7, r1]
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9BD4
ov05_021D9BD4: ; 0x021D9BD4
	cmp r0, #0
	bne _021D9BDC
	mov r0, #0
	bx lr
_021D9BDC:
	ldr r0, [r0]
	bx lr

	thumb_func_start ov05_021D9BE0
ov05_021D9BE0: ; 0x021D9BE0
	mov r1, #1
	and r0, r1
	cmp r0, #1
	beq _021D9BEA
	mov r1, #0
_021D9BEA:
	add r0, r1, #0
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021D9BF0
ov05_021D9BF0: ; 0x021D9BF0
	asr r1, r0, #1
	mov r0, #1
	and r1, r0
	cmp r1, #1
	beq _021D9BFC
	mov r0, #0
_021D9BFC:
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021D9C00
ov05_021D9C00: ; 0x021D9C00
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #1
	beq _021D9C0E
	bl GF_AssertFail
_021D9C0E:
	ldr r0, [r4, #0x1c]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9C14
ov05_021D9C14: ; 0x021D9C14
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r0, #0
	mov r0, #0xad
	ldr r7, [sp, #0x4c]
	lsl r0, r0, #2
	add r4, r1, #0
	str r2, [sp, #8]
	ldr r0, [r7, r0]
	add r1, r6, #0
	add r2, sp, #0x10
	add r5, r3, #0
	bl NARC_ReadWholeMember
	cmp r4, #4
	blt _021D9C38
	bl GF_AssertFail
_021D9C38:
	lsl r1, r4, #2
	add r0, sp, #0x14
	ldr r0, [r0, r1]
	mov r1, #0
	mvn r1, r1
	str r0, [sp, #0xc]
	cmp r0, r1
	bne _021D9C4E
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D9C4E:
	add r0, sp, #0x10
	ldrb r0, [r0, #1]
	bl ov05_021D9BE0
	ldr r1, [sp, #0x40]
	cmp r1, r0
	beq _021D9C62
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D9C62:
	mov r6, #0
	add r4, r7, #0
_021D9C66:
	cmp r5, #0
	beq _021D9C74
	ldr r0, [r4, #0x34]
	cmp r5, r0
	bne _021D9C74
	bl GF_AssertFail
_021D9C74:
	add r6, r6, #1
	add r4, #0x28
	cmp r6, #0x10
	blt _021D9C66
	mov r2, #0
	add r1, r7, #0
_021D9C80:
	ldr r0, [r1, #0x14]
	cmp r0, #0
	bne _021D9CD8
	add r4, r2, #0
	mov r0, #0x28
	mul r4, r0
	mov r1, #1
	add r0, r7, r4
	str r1, [r0, #0x14]
	ldr r1, [sp, #0x3c]
	add r6, r7, #0
	str r1, [r0, #0x20]
	add r6, #0x10
	mov r1, #0
	str r1, [r6, r4]
	str r1, [r0, #0x18]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x44]
	str r1, [r0, #0x1c]
	ldr r1, [sp, #0x38]
	add r3, r6, r4
	str r1, [r0, #0x30]
	str r5, [r0, #0x34]
	ldr r0, [sp, #0x48]
	ldr r1, [sp, #0xc]
	str r0, [sp]
	mov r0, #0x2b
	str r7, [sp, #4]
	lsl r0, r0, #4
	ldr r0, [r7, r0]
	bl ov05_021D9AA8
	add r1, r7, r4
	str r0, [r1, #0x24]
	ldr r0, [sp, #8]
	str r0, [r1, #0x28]
	mov r0, #1
	str r0, [r1, #0x2c]
	add r0, r6, r4
	bl ov05_021DA118
	add sp, #0x24
	add r0, r6, r4
	pop {r4, r5, r6, r7, pc}
_021D9CD8:
	add r2, r2, #1
	add r1, #0x28
	cmp r2, #0x10
	blt _021D9C80
	bl GF_AssertFail
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9CEC
ov05_021D9CEC: ; 0x021D9CEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r4, r0, #0
	mov r0, #0xad
	add r6, r3, #0
	lsl r0, r0, #2
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r6, r0]
	add r1, r4, #0
	add r2, sp, #0x20
	bl NARC_ReadWholeMember
	add r0, sp, #0x20
	ldrb r0, [r0]
	cmp r0, #0
	beq _021D9DBC
	mov r0, #0
	str r0, [sp, #0x14]
	add r0, sp, #0x20
	str r0, [sp, #0x10]
_021D9D16:
	ldr r0, [sp, #0x10]
	mov r1, #0
	ldr r0, [r0, #4]
	mvn r1, r1
	str r0, [sp, #0x18]
	cmp r0, r1
	beq _021D9DBC
	add r0, sp, #0x20
	ldrb r0, [r0, #1]
	bl ov05_021D9BE0
	cmp r0, #0
	bne _021D9DBC
	mov r4, #0
	add r1, r6, #0
_021D9D34:
	ldr r0, [r1, #0x14]
	cmp r0, #0
	bne _021D9D9C
	mov r0, #0x28
	add r7, r4, #0
	mul r7, r0
	add r5, r6, r7
	mov r0, #1
	str r0, [r5, #0x14]
	mov r1, #0
	str r1, [r5, #0x20]
	str r1, [r5, #0x10]
	ldr r0, [sp, #0x18]
	str r1, [r5, #0x18]
	str r0, [r5, #0x1c]
	add r0, r6, #0
	str r0, [sp, #0x1c]
	add r0, #0x10
	str r0, [sp, #0x1c]
	str r1, [r5, #0x30]
	str r1, [r5, #0x34]
	ldr r0, [sp, #0xc]
	ldr r3, [sp, #0x1c]
	str r0, [sp]
	mov r0, #0x2b
	str r6, [sp, #4]
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #8]
	add r3, r3, r7
	bl ov05_021D9AA8
	str r0, [r5, #0x24]
	mov r0, #0
	mvn r0, r0
	str r0, [r5, #0x28]
	mov r0, #1
	str r0, [r5, #0x2c]
	ldr r0, [sp, #0x1c]
	add r0, r0, r7
	bl ov05_021DA118
	add r0, sp, #0x20
	ldrb r0, [r0, #2]
	cmp r0, #0
	beq _021D9DA4
	add r1, r5, #0
	mov r0, #1
	str r0, [r1, #0x20]
	str r0, [r1, #0x28]
	b _021D9DA4
_021D9D9C:
	add r4, r4, #1
	add r1, #0x28
	cmp r4, #0x10
	blt _021D9D34
_021D9DA4:
	cmp r4, #0x10
	bne _021D9DAC
	bl GF_AssertFail
_021D9DAC:
	ldr r0, [sp, #0x10]
	add r0, r0, #4
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, #4
	blt _021D9D16
_021D9DBC:
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D9DC0
ov05_021D9DC0: ; 0x021D9DC0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r6, [sp, #0x30]
	add r5, r0, #0
	add r4, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r6, #0
	bne _021D9DDC
	bl GF_AssertFail
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9DDC:
	add r0, r6, #0
	bl ov05_021DA220
	cmp r5, r0
	blt _021D9DEC
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9DEC:
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	add r1, r5, #0
	add r2, sp, #4
	bl NARC_ReadWholeMember
	cmp r4, #4
	blt _021D9E02
	bl GF_AssertFail
_021D9E02:
	lsl r1, r4, #2
	add r0, sp, #8
	ldr r5, [r0, r1]
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _021D9E16
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9E16:
	add r0, sp, #4
	ldrb r0, [r0, #1]
	bl ov05_021D9BF0
	cmp r7, r0
	beq _021D9E28
	add sp, #0x18
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021D9E28:
	mov r4, #0
	add r1, r6, #0
_021D9E2C:
	ldr r0, [r1, #0x1c]
	cmp r5, r0
	bne _021D9E70
	add r0, sp, #4
	ldrb r0, [r0, #2]
	cmp r0, #0
	beq _021D9E56
	add r2, r6, #0
	mov r3, #0x28
	mov r0, #0x29
	lsl r0, r0, #4
	add r2, #0x10
	mul r3, r4
	add r2, r2, r3
	lsl r3, r5, #0x18
	ldr r1, [sp]
	add r0, r6, r0
	lsr r3, r3, #0x18
	bl ov05_021D9A48
	b _021D9E58
_021D9E56:
	mov r0, #1
_021D9E58:
	cmp r0, #0
	beq _021D9E6A
	mov r1, #0x28
	mul r1, r4
	add r1, r6, r1
	ldr r0, [sp]
	ldr r1, [r1, #0x10]
	bl NNS_G3dRenderObjAddAnmObj
_021D9E6A:
	add sp, #0x18
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9E70:
	add r4, r4, #1
	add r1, #0x28
	cmp r4, #0x10
	blt _021D9E2C
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9E80
ov05_021D9E80: ; 0x021D9E80
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, _021D9F44 ; =0x00000000
	str r1, [sp, #0xc]
	add r4, r2, #0
	str r0, [sp]
	bne _021D9E94
	bl GF_AssertFail
_021D9E94:
	add r0, r4, #0
	bl ov05_021DA220
	cmp r5, r0
	blt _021D9EA4
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D9EA4:
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r5, #0
	add r2, sp, #0x10
	bl NARC_ReadWholeMember
	add r0, sp, #0x10
	ldrb r0, [r0, #1]
	bl ov05_021D9BF0
	cmp r0, #0
	beq _021D9EC4
	add sp, #0x24
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_021D9EC4:
	mov r0, #0
	str r0, [sp, #4]
	add r0, r4, #0
	str r0, [sp, #8]
	add r0, #0x10
	add r7, sp, #0x10
	str r0, [sp, #8]
_021D9ED2:
	mov r0, #0
	ldr r3, [r7, #4]
	mvn r0, r0
	cmp r3, r0
	bne _021D9EE2
	ldr r0, [sp]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_021D9EE2:
	mov r5, #0
	add r1, r4, #0
_021D9EE6:
	ldr r0, [r1, #0x1c]
	cmp r3, r0
	bne _021D9F2A
	add r0, sp, #0x10
	ldrb r0, [r0, #2]
	cmp r0, #0
	beq _021D9F10
	mov r2, #0x28
	add r6, r5, #0
	mov r0, #0x29
	mul r6, r2
	ldr r2, [sp, #8]
	lsl r0, r0, #4
	lsl r3, r3, #0x18
	ldr r1, [sp, #0xc]
	add r0, r4, r0
	add r2, r2, r6
	lsr r3, r3, #0x18
	bl ov05_021D9A48
	b _021D9F12
_021D9F10:
	mov r0, #1
_021D9F12:
	cmp r0, #0
	beq _021D9F32
	mov r1, #0x28
	mul r1, r5
	add r1, r4, r1
	ldr r0, [sp, #0xc]
	ldr r1, [r1, #0x10]
	bl NNS_G3dRenderObjAddAnmObj
	mov r0, #1
	str r0, [sp]
	b _021D9F32
_021D9F2A:
	add r5, r5, #1
	add r1, #0x28
	cmp r5, #0x10
	blt _021D9EE6
_021D9F32:
	ldr r0, [sp, #4]
	add r7, r7, #4
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #4
	blt _021D9ED2
	ldr r0, [sp]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021D9F44: .word 0x00000000

	thumb_func_start ov05_021D9F48
ov05_021D9F48: ; 0x021D9F48
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	beq _021D9F7C
	mov r4, #0
	add r5, r6, #0
	add r7, r4, #0
_021D9F54:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021D9F74
	cmp r0, #1
	bne _021D9F6E
	ldr r1, [r5, #0x10]
	add r0, r6, #0
	bl NNS_G3dFreeAnmObj
	str r7, [r5, #0x10]
	ldr r0, [r5, #0x24]
	bl FreeToHeap
_021D9F6E:
	mov r0, #0
	str r0, [r5, #0x14]
	str r0, [r5, #0x34]
_021D9F74:
	add r4, r4, #1
	add r5, #0x28
	cmp r4, #0x10
	blt _021D9F54
_021D9F7C:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021D9F80
ov05_021D9F80: ; 0x021D9F80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	beq _021D9FB2
	cmp r5, #0
	bne _021D9F90
	bl GF_AssertFail
_021D9F90:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021D9FB2
	cmp r0, #1
	bne _021D9FAC
	ldr r1, [r5]
	add r0, r4, #0
	bl NNS_G3dFreeAnmObj
	mov r0, #0
	str r0, [r5]
	ldr r0, [r5, #0x14]
	bl FreeToHeap
_021D9FAC:
	mov r0, #0
	str r0, [r5, #4]
	str r0, [r5, #0x24]
_021D9FB2:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021D9FB4
ov05_021D9FB4: ; 0x021D9FB4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0xad
	lsl r0, r0, #2
	add r6, r1, #0
	add r1, r2, #0
	ldr r0, [r4, r0]
	add r2, sp, #0
	add r5, r3, #0
	bl NARC_ReadWholeMember
	cmp r5, #4
	blt _021D9FD4
	bl GF_AssertFail
_021D9FD4:
	lsl r1, r5, #2
	add r0, sp, #4
	ldr r5, [r0, r1]
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _021D9FE6
	bl GF_AssertFail
_021D9FE6:
	mov r0, #0
	mov r2, #0x28
_021D9FEA:
	add r1, r0, #0
	mul r1, r2
	add r1, r4, r1
	ldr r3, [r1, #0x14]
	cmp r3, #1
	bne _021DA008
	ldr r3, [r1, #0x1c]
	cmp r5, r3
	bne _021DA008
	ldr r1, [r1, #0x10]
	add r0, r6, #0
	bl ov05_021D9B04
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
_021DA008:
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x10
	blo _021D9FEA
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA018
ov05_021DA018: ; 0x021DA018
	push {r4, lr}
	add r4, r0, #0
	beq _021DA038
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl NARC_Delete
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl NARC_Delete
	add r0, r4, #0
	bl FreeToHeap
_021DA038:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA03C
ov05_021DA03C: ; 0x021DA03C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0
	bne _021DA04A
	bl GF_AssertFail
_021DA04A:
	mov r6, #0
	add r1, r6, #0
	add r2, r4, #0
_021DA050:
	ldr r0, [r2, #0x34]
	cmp r5, r0
	bne _021DA06A
	mov r0, #0x28
	add r4, #0x10
	mul r0, r1
	add r6, r4, r0
	ldr r0, [r6, #4]
	cmp r0, #0
	bne _021DA072
	bl GF_AssertFail
	b _021DA072
_021DA06A:
	add r1, r1, #1
	add r2, #0x28
	cmp r1, #0x10
	blt _021DA050
_021DA072:
	cmp r6, #0
	bne _021DA07A
	bl GF_AssertFail
_021DA07A:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA080
ov05_021DA080: ; 0x021DA080
	push {r4, r5, lr}
	sub sp, #0x14
	add r3, r0, #0
	mov r0, #0xad
	add r5, r2, #0
	lsl r0, r0, #2
	add r4, r1, #0
	ldr r0, [r5, r0]
	add r1, r3, #0
	add r2, sp, #0
	bl NARC_ReadWholeMember
	cmp r4, #4
	blt _021DA0A0
	bl GF_AssertFail
_021DA0A0:
	lsl r1, r4, #2
	add r0, sp, #4
	mov r4, #0
	ldr r1, [r0, r1]
	add r2, r4, #0
	add r3, r5, #0
_021DA0AC:
	ldr r0, [r3, #0x1c]
	cmp r1, r0
	bne _021DA0C6
	mov r0, #0x28
	add r5, #0x10
	mul r0, r2
	add r4, r5, r0
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021DA0CE
	bl GF_AssertFail
	b _021DA0CE
_021DA0C6:
	add r2, r2, #1
	add r3, #0x28
	cmp r2, #0x10
	blt _021DA0AC
_021DA0CE:
	cmp r4, #0
	bne _021DA0D6
	bl GF_AssertFail
_021DA0D6:
	add r0, r4, #0
	add sp, #0x14
	pop {r4, r5, pc}

	thumb_func_start ov05_021DA0DC
ov05_021DA0DC: ; 0x021DA0DC
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start ov05_021DA0E0
ov05_021DA0E0: ; 0x021DA0E0
	mov r1, #1
	str r1, [r0, #0x1c]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DA0E8
ov05_021DA0E8: ; 0x021DA0E8
	ldr r1, [r0, #0x20]
	ldr r0, [r0]
	cmp r1, #0
	bne _021DA10A
	ldr r2, [r0]
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	lsl r1, r0, #0xc
	mov r0, #1
	lsl r0, r0, #0xc
	sub r0, r1, r0
	cmp r2, r0
	blt _021DA106
	mov r0, #1
	bx lr
_021DA106:
	mov r0, #0
	bx lr
_021DA10A:
	ldr r0, [r0]
	cmp r0, #0
	bne _021DA114
	mov r0, #1
	bx lr
_021DA114:
	mov r0, #0
	bx lr

	thumb_func_start ov05_021DA118
ov05_021DA118: ; 0x021DA118
	ldr r1, [r0, #0x20]
	cmp r1, #0
	bne _021DA126
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	bx lr
_021DA126:
	ldr r2, [r0]
	ldr r0, [r2, #8]
	ldrh r0, [r0, #4]
	lsl r1, r0, #0xc
	mov r0, #1
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [r2]
	bx lr

	thumb_func_start ov05_021DA138
ov05_021DA138: ; 0x021DA138
	ldr r1, [r0, #0x20]
	cmp r1, #0
	bne _021DA150
	ldr r2, [r0]
	ldr r0, [r2, #8]
	ldrh r0, [r0, #4]
	lsl r1, r0, #0xc
	mov r0, #1
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [r2]
	bx lr
_021DA150:
	ldr r0, [r0]
	mov r1, #0
	str r1, [r0]
	bx lr

	thumb_func_start ov05_021DA158
ov05_021DA158: ; 0x021DA158
	ldr r1, [r0, #0x20]
	cmp r1, #0
	bne _021DA17E
	ldr r3, [r0]
	mov r1, #1
	ldr r2, [r3]
	lsl r1, r1, #0xc
	add r1, r2, r1
	str r1, [r3]
	ldr r2, [r0]
	ldr r0, [r2, #8]
	ldr r1, [r2]
	ldrh r0, [r0, #4]
	lsl r0, r0, #0xc
	cmp r1, r0
	bne _021DA19E
	mov r0, #0
	str r0, [r2]
	bx lr
_021DA17E:
	ldr r0, [r0]
	ldr r2, [r0]
	cmp r2, #0
	bgt _021DA196
	ldr r1, [r0, #8]
	ldrh r1, [r1, #4]
	lsl r2, r1, #0xc
	mov r1, #1
	lsl r1, r1, #0xc
	sub r1, r2, r1
	str r1, [r0]
	bx lr
_021DA196:
	mov r1, #1
	lsl r1, r1, #0xc
	sub r1, r2, r1
	str r1, [r0]
_021DA19E:
	bx lr

	thumb_func_start ov05_021DA1A0
ov05_021DA1A0: ; 0x021DA1A0
	str r1, [r0, #0x20]
	bx lr

	thumb_func_start ov05_021DA1A4
ov05_021DA1A4: ; 0x021DA1A4
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start ov05_021DA1A8
ov05_021DA1A8: ; 0x021DA1A8
	str r1, [r0, #0x24]
	bx lr

	thumb_func_start ov05_021DA1AC
ov05_021DA1AC: ; 0x021DA1AC
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	cmp r0, #0
	beq _021DA20A
	mov r4, #0
	add r5, r0, #0
	add r5, #0x10
	add r6, r4, #0
	sub r7, r4, #1
_021DA1BE:
	ldr r0, [r5, #4]
	cmp r0, #1
	bne _021DA1F6
	ldr r0, [r5, #0x10]
	cmp r0, #1
	beq _021DA1F6
	ldr r0, [r5, #0x1c]
	cmp r0, #0
	beq _021DA1F6
	add r0, r5, #0
	bl ov05_021DA158
	ldr r0, [r5, #0x18]
	cmp r0, r7
	beq _021DA1F6
	add r0, r5, #0
	bl ov05_021DA0E8
	cmp r0, #0
	beq _021DA1F6
	ldr r0, [r5, #8]
	add r1, r0, #1
	ldr r0, [r5, #0x18]
	cmp r1, r0
	blt _021DA1F4
	str r6, [r5, #0x1c]
	b _021DA1F6
_021DA1F4:
	str r1, [r5, #8]
_021DA1F6:
	add r4, r4, #1
	add r5, #0x28
	cmp r4, #0x10
	blt _021DA1BE
	mov r1, #0x29
	ldr r0, [sp]
	lsl r1, r1, #4
	add r0, r0, r1
	bl ov05_021D9B20
_021DA20A:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DA20C
ov05_021DA20C: ; 0x021DA20C
	push {r3, lr}
	bl ov05_021D9C00
	cmp r0, #0
	bne _021DA21A
	mov r0, #1
	pop {r3, pc}
_021DA21A:
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA220
ov05_021DA220: ; 0x021DA220
	mov r1, #0xad
	lsl r1, r1, #2
	ldr r3, _021DA22C ; =NARC_GetFileCount
	ldr r0, [r0, r1]
	bx r3
	nop
_021DA22C: .word NARC_GetFileCount

	thumb_func_start ov05_021DA230
ov05_021DA230: ; 0x021DA230
	push {lr}
	sub sp, #0x14
	mov r2, #0xad
	lsl r2, r2, #2
	ldr r0, [r0, r2]
	add r2, sp, #0
	bl NARC_ReadWholeMember
	add r0, sp, #0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021DA24E
	add sp, #0x14
	mov r0, #0
	pop {pc}
_021DA24E:
	mov r0, #0
	add r3, sp, #0
	sub r1, r0, #1
_021DA254:
	lsl r2, r0, #2
	add r2, r3, r2
	ldr r2, [r2, #4]
	cmp r2, r1
	beq _021DA268
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #4
	blo _021DA254
_021DA268:
	add sp, #0x14
	pop {pc}

	thumb_func_start ov05_021DA26C
ov05_021DA26C: ; 0x021DA26C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _021DA278
	bl GF_AssertFail
_021DA278:
	mov r1, #0x10
	mov r0, #0
	mov r2, #0x38
_021DA27E:
	cmp r1, #0x10
	bne _021DA292
	add r3, r0, #0
	mul r3, r2
	add r3, r5, r3
	add r3, #0x34
	ldrb r3, [r3]
	cmp r3, #0
	bne _021DA292
	add r1, r0, #0
_021DA292:
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x10
	blo _021DA27E
	cmp r1, #0x10
	beq _021DA2AE
	mov r0, #0x38
	add r2, r1, #0
	mul r2, r0
	add r0, r5, r2
	add r0, #0x34
	strb r4, [r0]
	b _021DA2B6
_021DA2AE:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, r4, r5, pc}
_021DA2B6:
	add r0, r5, r2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA2BC
ov05_021DA2BC: ; 0x021DA2BC
	add r1, r0, #0
	mov r3, #0
	add r1, #0x34
	strb r3, [r1]
	str r3, [r0, #0x30]
	str r3, [r0, #0x2c]
	add r2, r3, #0
_021DA2CA:
	lsl r1, r3, #2
	add r1, r0, r1
	str r2, [r1, #0x14]
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #6
	blo _021DA2CA
	bx lr

	thumb_func_start ov05_021DA2DC
ov05_021DA2DC: ; 0x021DA2DC
	push {r4, r5}
	mov r4, #0
	add r3, r4, #0
	add r5, r0, #0
_021DA2E4:
	add r2, r5, #0
	add r2, #0x34
	ldrb r2, [r2]
	cmp r1, r2
	bne _021DA2F6
	mov r1, #0x38
	mul r1, r3
	add r4, r0, r1
	b _021DA2FE
_021DA2F6:
	add r3, r3, #1
	add r5, #0x38
	cmp r3, #0x10
	blt _021DA2E4
_021DA2FE:
	add r0, r4, #0
	pop {r4, r5}
	bx lr

	thumb_func_start ov05_021DA304
ov05_021DA304: ; 0x021DA304
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #4
	ble _021DA314
	bl GF_AssertFail
_021DA314:
	cmp r5, #0
	beq _021DA31A
	str r5, [r6, #0x14]
_021DA31A:
	str r4, [r6, #0x10]
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA320
ov05_021DA320: ; 0x021DA320
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r4, r1, #0
	add r6, r2, #0
	cmp r4, r0
	blt _021DA332
	bl GF_AssertFail
_021DA332:
	lsl r0, r4, #2
	str r6, [r5, r0]
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DA338
ov05_021DA338: ; 0x021DA338
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r4, r1, #0
	cmp r4, r0
	blt _021DA34A
	bl GF_AssertFail
_021DA34A:
	lsl r0, r4, #2
	ldr r0, [r5, r0]
	str r0, [sp, #4]
	bl ov05_021D9BD4
	str r0, [sp]
	ldr r0, [r5, #0x2c]
	bl ov05_021D9BD4
	add r7, r0, #0
	mov r4, #0
_021DA360:
	lsl r0, r4, #2
	add r6, r5, r0
	ldr r0, [r6, #0x14]
	cmp r0, #0
	beq _021DA378
	add r1, r7, #0
	bl ov05_021D9B04
	ldr r0, [r6, #0x14]
	ldr r1, [sp]
	bl NNS_G3dRenderObjAddAnmObj
_021DA378:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #6
	blo _021DA360
	ldr r0, [sp, #4]
	str r0, [r5, #0x2c]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA38C
ov05_021DA38C: ; 0x021DA38C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x40]
	str r1, [sp, #0x1c]
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x4c]
	str r2, [sp, #0x20]
	str r0, [sp, #0x4c]
	add r0, r3, #0
	mov r5, #0
	str r3, [sp, #0x24]
	ldr r6, [sp, #0x44]
	ldr r7, [sp, #0x48]
	cmp r0, #0
	ble _021DA3E4
_021DA3AC:
	str r6, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x40]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	mov r3, #0
	str r7, [sp, #0x14]
	bl ov05_021D9C14
	add r4, r0, #0
	bne _021DA3D2
	bl GF_AssertFail
_021DA3D2:
	ldr r0, [sp, #0x4c]
	add r1, r5, #0
	add r2, r4, #0
	bl ov05_021DA320
	ldr r0, [sp, #0x24]
	add r5, r5, #1
	cmp r5, r0
	blt _021DA3AC
_021DA3E4:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DA3E8
ov05_021DA3E8: ; 0x021DA3E8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	str r0, [sp]
	ldr r0, [r6, #0x2c]
	bl ov05_021D9BD4
	add r7, r0, #0
	mov r4, #0
	add r5, r6, #0
_021DA3FA:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _021DA406
	add r1, r7, #0
	bl ov05_021D9B04
_021DA406:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021DA3FA
	ldr r0, [r6, #0x10]
	mov r5, #0
	cmp r0, #0
	ble _021DA42C
	add r4, r6, #0
	add r7, r5, #0
_021DA41A:
	ldr r0, [r4]
	ldr r1, [sp]
	bl ov05_021D9F80
	stmia r4!, {r7}
	ldr r0, [r6, #0x10]
	add r5, r5, #1
	cmp r5, r0
	blt _021DA41A
_021DA42C:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA430
ov05_021DA430: ; 0x021DA430
	push {r4, lr}
	mov r1, #0xe
	mov r0, #4
	lsl r1, r1, #6
	bl AllocFromHeap
	add r4, r0, #0
	mov r2, #0xe
	mov r0, #0
	add r1, r4, #0
	lsl r2, r2, #6
	bl MIi_CpuClearFast
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA450
ov05_021DA450: ; 0x021DA450
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DA462
	bl FreeToHeap
	mov r0, #0
	str r0, [r4]
_021DA462:
	pop {r4, pc}

	thumb_func_start ov05_021DA464
ov05_021DA464: ; 0x021DA464
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	add r0, r1, #0
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	add r6, r3, #0
	bl ov05_021DA26C
	add r5, r0, #0
	bne _021DA482
	bl GF_AssertFail
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_021DA482:
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x34]
	add r2, r5, #0
	bl ov05_021DA304
	add r0, sp, #0x38
	ldrb r4, [r0]
	cmp r4, #0
	bne _021DA498
	bl GF_AssertFail
_021DA498:
	cmp r4, #0
	bne _021DA49E
	mov r4, #1
_021DA49E:
	ldr r0, [sp, #0x3c]
	str r4, [sp]
	str r0, [sp, #4]
	str r7, [sp, #8]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	ldr r3, [sp, #0x34]
	add r0, r6, #0
	str r5, [sp, #0xc]
	bl ov05_021DA38C
	str r6, [r5, #0x30]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA4BC
ov05_021DA4BC: ; 0x021DA4BC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r7, r1, #0
	add r6, r3, #0
	cmp r4, #6
	blo _021DA4CE
	bl GF_AssertFail
_021DA4CE:
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021DA2DC
	add r5, r0, #0
	add r5, #0x14
	lsl r4, r4, #2
	ldr r0, [r5, r4]
	cmp r0, #0
	beq _021DA4E6
	bl GF_AssertFail
_021DA4E6:
	str r6, [r5, r4]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA4EC
ov05_021DA4EC: ; 0x021DA4EC
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #0
	bne _021DA4FC
	bl GF_AssertFail
_021DA4FC:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DA2DC
	add r1, r6, #0
	bl ov05_021DA338
	mov r1, #0
	bl ov05_021DA0DC
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021DA514
ov05_021DA514: ; 0x021DA514
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r7, r2, #0
	add r4, r3, #0
	cmp r5, #0
	bne _021DA526
	bl GF_AssertFail
_021DA526:
	add r0, r6, #0
	add r1, r5, #0
	bl ov05_021DA2DC
	add r1, r7, #0
	bl ov05_021DA338
	add r5, r0, #0
	cmp r4, #0
	beq _021DA542
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl PlaySE
_021DA542:
	add r0, r5, #0
	mov r1, #0
	bl ov05_021DA0DC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021DA54C
ov05_021DA54C: ; 0x021DA54C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bne _021DA55A
	bl GF_AssertFail
_021DA55A:
	add r0, r4, #0
	add r1, r6, #0
	bl ov05_021DA2DC
	add r4, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DA3E8
	add r0, r4, #0
	bl ov05_021DA2BC
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DA574
ov05_021DA574: ; 0x021DA574
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _021DA580
	bl GF_AssertFail
_021DA580:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DA2DC
	ldr r0, [r0, #0x2c]
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DA58C
ov05_021DA58C: ; 0x021DA58C
	push {r4, lr}
	bl ov05_021DA574
	add r4, r0, #0
	bne _021DA59A
	bl GF_AssertFail
_021DA59A:
	add r0, r4, #0
	bl ov05_021DA20C
	cmp r0, #0
	beq _021DA5A8
	mov r0, #1
	pop {r4, pc}
_021DA5A8:
	mov r0, #0
	pop {r4, pc}

	thumb_func_start ov05_021DA5AC
ov05_021DA5AC: ; 0x021DA5AC
	push {r3, lr}
	bl ov05_021DA2DC
	ldr r0, [r0, #0x30]
	pop {r3, pc}
	.balign 4, 0
