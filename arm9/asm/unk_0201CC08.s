	.include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .bss

	.global UNK_021C5938
UNK_021C5938: ; 0x021C5938
	.space 0xc

	.global UNK_021C5944
UNK_021C5944: ; 0x021C5944
	.space 0x34

	.global UNK_021C5978
UNK_021C5978: ; 0x021C5978
	.space 0x1c

	.text

	thumb_func_start FUN_0201CC08
FUN_0201CC08: ; 0x0201CC08
	push {r3, lr}
	ldr r0, _0201CC20 ; =UNK_021C5978
	ldrh r0, [r0, #0x1a]
	cmp r0, #0x0
	beq _0201CC16
	bl GF_AssertFail
_0201CC16:
	ldr r0, _0201CC20 ; =UNK_021C5978
	mov r1, #0x0
	strh r1, [r0, #0x18]
	strh r1, [r0, #0x1a]
	pop {r3, pc}
	.balign 4
_0201CC20: .word UNK_021C5978

	thumb_func_start FUN_0201CC24
FUN_0201CC24: ; 0x0201CC24
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r0, _0201CC74 ; =UNK_021C5978
	ldrh r0, [r0, #0x1a]
	cmp r0, #0x0
	beq _0201CC36
	bl GF_AssertFail
_0201CC36:
	cmp r4, #0x5
	bhs _0201CC3E
	cmp r4, #0x0
	bne _0201CC44
_0201CC3E:
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0201CC44:
	ldr r0, _0201CC74 ; =UNK_021C5978
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CC52
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0201CC52:
	add r0, r4, #0x0
	bl FUN_0201CE2C
	cmp r0, #0x1
	bne _0201CC70
	mov r2, #0x0
	str r2, [sp, #0x0]
	lsl r0, r4, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x2
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_0201CC78
	mov r0, #0x1
_0201CC70:
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0201CC74: .word UNK_021C5978

	thumb_func_start FUN_0201CC78
FUN_0201CC78: ; 0x0201CC78
	push {r4, lr}
	ldr r4, _0201CC9C ; =UNK_021C5978
	strh r0, [r4, #0x18]
	ldr r0, _0201CCA0 ; =gMain + 0x60
	strb r1, [r0, #0x4]
	ldr r0, _0201CCA4 ; =UNK_021C5938
	ldr r1, [sp, #0xc]
	str r2, [r0, #0x0]
	str r3, [r0, #0x4]
	str r1, [r0, #0x8]
	ldr r1, [sp, #0x8]
	str r1, [r0, #0x54]
	ldr r0, _0201CCA8 ; =UNK_021C5944
	mov r1, #0x9
	bl FUN_0201CCAC
	pop {r4, pc}
	nop
_0201CC9C: .word UNK_021C5978
_0201CCA0: .word gMain + 0x60
_0201CCA4: .word UNK_021C5938
_0201CCA8: .word UNK_021C5944

	thumb_func_start FUN_0201CCAC
FUN_0201CCAC: ; 0x0201CCAC
	mov r3, #0x0
	cmp r1, #0x0
	ble _0201CCBE
	add r2, r3, #0x0
_0201CCB4:
	add r3, r3, #0x1
	strh r2, [r0, #0x4]
	add r0, #0x8
	cmp r3, r1
	blt _0201CCB4
_0201CCBE:
	bx lr

	thumb_func_start FUN_0201CCC0
FUN_0201CCC0: ; 0x0201CCC0
	push {r4-r6, lr}
	ldr r0, _0201CD00 ; =UNK_021C5978
	mov r5, #0x0
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	bne _0201CCD0
	mov r0, #0x1
	pop {r4-r6, pc}
_0201CCD0:
	mov r4, #0x4
	add r6, r4, #0x0
_0201CCD4:
	bl TP_RequestAutoSamplingStopAsync
	add r0, r4, #0x0
	bl TP_WaitBusy
	add r0, r6, #0x0
	bl TP_CheckError
	cmp r0, #0x0
	beq _0201CCEA
	add r5, r5, #0x1
_0201CCEA:
	cmp r0, #0x0
	beq _0201CCF2
	cmp r5, #0x5
	bls _0201CCD4
_0201CCF2:
	cmp r5, #0x5
	bls _0201CCFA
	mov r0, #0x2
	pop {r4-r6, pc}
_0201CCFA:
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0201CD00: .word UNK_021C5978

	thumb_func_start FUN_0201CD04
FUN_0201CD04: ; 0x0201CD04
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _0201CD34 ; =UNK_021C5978
	ldrh r0, [r0, #0x1a]
	cmp r0, #0x0
	beq _0201CD14
	bl GF_AssertFail
_0201CD14:
	bl FUN_0201CCC0
	add r4, r0, #0x0
	cmp r4, #0x1
	bne _0201CD2E
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	str r0, [sp, #0x4]
	bl FUN_0201CC78
_0201CD2E:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0201CD34: .word UNK_021C5978

	thumb_func_start FUN_0201CD38
FUN_0201CD38: ; 0x0201CD38
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r0, _0201CD8C ; =UNK_021C5978
	add r6, r1, #0x0
	ldrh r0, [r0, #0x1a]
	add r7, r2, #0x0
	mov r5, #0x3
	cmp r0, #0x0
	beq _0201CD4E
	bl GF_AssertFail
_0201CD4E:
	ldr r0, _0201CD8C ; =UNK_021C5978
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CD88
	bl TP_GetLatestIndexInAuto
	add r5, r0, #0x0
	ldr r0, _0201CD90 ; =UNK_021C5944
	mov r1, #0x9
	bl FUN_0201CD94
	cmp r4, #0x0
	beq _0201CD70
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0201CFD0
_0201CD70:
	ldr r0, _0201CD8C ; =UNK_021C5978
	ldrh r0, [r0, #0x18]
	cmp r0, #0x1
	bne _0201CD86
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl FUN_0201CE70
	add r5, r0, #0x0
	b _0201CD88
_0201CD86:
	mov r5, #0x1
_0201CD88:
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_0201CD8C: .word UNK_021C5978
_0201CD90: .word UNK_021C5944

	thumb_func_start FUN_0201CD94
FUN_0201CD94: ; 0x0201CD94
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r7, #0x0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	beq _0201CDCA
	add r4, r5, #0x0
	add r6, sp, #0x4
_0201CDA6:
	add r0, sp, #0x4
	add r1, r5, #0x0
	bl TP_GetCalibratedPoint
	ldrh r0, [r6, #0x0]
	add r7, r7, #0x1
	add r5, #0x8
	strh r0, [r4, #0x0]
	ldrh r0, [r6, #0x2]
	strh r0, [r4, #0x2]
	ldrh r0, [r6, #0x4]
	strh r0, [r4, #0x4]
	ldrh r0, [r6, #0x6]
	strh r0, [r4, #0x6]
	ldr r0, [sp, #0x0]
	add r4, #0x8
	cmp r7, r0
	blo _0201CDA6
_0201CDCA:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0201CDD0
FUN_0201CDD0: ; 0x0201CDD0
	push {r3, lr}
	ldr r0, _0201CDFC ; =UNK_021C5978
	ldrh r1, [r0, #0x1a]
	cmp r1, #0x0
	beq _0201CDF8
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CDF8
	ldr r0, _0201CE00 ; =UNK_021C5938
	ldr r0, [r0, #0x8]
	lsr r0, r0, #0x1
	bl FUN_0201CE2C
	cmp r0, #0x1
	beq _0201CDF2
	bl GF_AssertFail
_0201CDF2:
	ldr r0, _0201CDFC ; =UNK_021C5978
	mov r1, #0x0
	strh r1, [r0, #0x1a]
_0201CDF8:
	pop {r3, pc}
	nop
_0201CDFC: .word UNK_021C5978
_0201CE00: .word UNK_021C5938

	thumb_func_start FUN_0201CE04
FUN_0201CE04: ; 0x0201CE04
	push {r3, lr}
	ldr r0, _0201CE28 ; =UNK_021C5978
	ldrh r1, [r0, #0x1a]
	cmp r1, #0x1
	beq _0201CE26
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0201CE26
	bl FUN_0201CCC0
	cmp r0, #0x1
	beq _0201CE20
	bl GF_AssertFail
_0201CE20:
	ldr r0, _0201CE28 ; =UNK_021C5978
	mov r1, #0x1
	strh r1, [r0, #0x1a]
_0201CE26:
	pop {r3, pc}
	.balign 4
_0201CE28: .word UNK_021C5978

	thumb_func_start FUN_0201CE2C
FUN_0201CE2C: ; 0x0201CE2C
	push {r3-r7, lr}
	mov r5, #0x0
	lsl r0, r0, #0x10
	ldr r7, _0201CE6C ; =UNK_021C5944
	add r6, r5, #0x0
	lsr r4, r0, #0x10
_0201CE38:
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	mov r3, #0x9
	bl TP_RequestAutoSamplingStartAsync
	mov r0, #0x2
	bl TP_WaitBusy
	mov r0, #0x2
	bl TP_CheckError
	cmp r0, #0x0
	beq _0201CE56
	add r5, r5, #0x1
_0201CE56:
	cmp r0, #0x0
	beq _0201CE5E
	cmp r5, #0x5
	ble _0201CE38
_0201CE5E:
	cmp r5, #0x5
	ble _0201CE66
	mov r0, #0x2
	pop {r3-r7, pc}
_0201CE66:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0201CE6C: .word UNK_021C5944

	thumb_func_start FUN_0201CE70
FUN_0201CE70: ; 0x0201CE70
	push {r3, lr}
	cmp r0, #0x5
	bhi _0201CE9A
	add r3, r0, r0
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0201CE82: ; jump table (using 16-bit offset)
	.short _0201CE9A - _0201CE82 - 2; case 0
	.short _0201CE8E - _0201CE82 - 2; case 1
	.short _0201CE9A - _0201CE82 - 2; case 2
	.short _0201CE8E - _0201CE82 - 2; case 3
	.short _0201CE94 - _0201CE82 - 2; case 4
	.short _0201CE94 - _0201CE82 - 2; case 5
_0201CE8E:
	bl FUN_0201CEA0
	pop {r3, pc}
_0201CE94:
	bl FUN_0201CF58
	pop {r3, pc}
_0201CE9A:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201CEA0
FUN_0201CEA0: ; 0x0201CEA0
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r5, _0201CF50 ; =UNK_021C5938
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x0]
	add r7, r2, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	bls _0201CF46
_0201CEB4:
	ldr r0, [sp, #0x4]
	sub r0, r0, r1
	add r0, r4, r0
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	bpl _0201CEC8
	add r0, #0x9
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
_0201CEC8:
	lsl r1, r0, #0x3
	ldr r0, _0201CF54 ; =UNK_021C5938
	add r1, r0, r1
	ldrh r0, [r1, #0x10]
	cmp r0, #0x1
	bne _0201CF3E
	ldrh r0, [r1, #0x12]
	cmp r0, #0x0
	bne _0201CF3E
	ldr r2, [r5, #0x54]
	ldr r0, [r5, #0x0]
	lsl r2, r2, #0x3
	add r2, r0, r2
	add r0, r2, #0x0
	sub r0, #0x8
	ldrh r3, [r1, #0xc]
	ldrh r0, [r0, #0x0]
	cmp r0, r3
	blt _0201CEF2
	sub r3, r0, r3
	b _0201CEF4
_0201CEF2:
	sub r3, r3, r0
_0201CEF4:
	sub r6, r2, #0x6
	ldrh r0, [r1, #0xe]
	ldrh r6, [r6, #0x0]
	cmp r6, r0
	blt _0201CF02
	sub r0, r6, r0
	b _0201CF04
_0201CF02:
	sub r0, r0, r6
_0201CF04:
	cmp r3, r7
	bhs _0201CF0C
	cmp r0, r7
	blo _0201CF3E
_0201CF0C:
	ldrh r0, [r1, #0xc]
	strh r0, [r2, #0x0]
	ldrh r0, [r1, #0xe]
	strh r0, [r2, #0x2]
	ldrh r0, [r1, #0x10]
	strh r0, [r2, #0x4]
	ldrh r0, [r1, #0x12]
	strh r0, [r2, #0x6]
	ldr r0, [r5, #0x54]
	add r0, r0, #0x1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x4]
	cmp r0, r1
	blo _0201CF3E
	ldr r2, [sp, #0x0]
	cmp r2, #0x1
	bne _0201CF36
	bl _u32_div_f
	str r1, [r5, #0x54]
	b _0201CF3E
_0201CF36:
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r7, pc}
_0201CF3E:
	ldr r1, [r5, #0x8]
	add r4, r4, #0x1
	cmp r4, r1
	blo _0201CEB4
_0201CF46:
	ldr r0, _0201CF50 ; =UNK_021C5938
	ldr r0, [r0, #0x54]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0201CF50: .word UNK_021C5938
_0201CF54: .word UNK_021C5938

	thumb_func_start FUN_0201CF58
FUN_0201CF58: ; 0x0201CF58
	push {r3-r7, lr}
	ldr r5, _0201CFC8 ; =UNK_021C5938
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x8]
	add r7, r0, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	bls _0201CFC0
_0201CF68:
	ldr r0, [sp, #0x0]
	sub r0, r0, r1
	add r0, r4, r0
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	asr r1, r0, #0x10
	bpl _0201CF7C
	add r1, #0x9
	lsl r0, r1, #0x10
	asr r1, r0, #0x10
_0201CF7C:
	ldr r0, [r5, #0x54]
	lsl r1, r1, #0x3
	lsl r3, r0, #0x3
	ldr r0, _0201CFCC ; =UNK_021C5938
	ldr r6, [r5, #0x0]
	add r2, r0, r1
	ldrh r0, [r2, #0xc]
	add r1, r6, r3
	strh r0, [r6, r3]
	ldrh r0, [r2, #0xe]
	strh r0, [r1, #0x2]
	ldrh r0, [r2, #0x10]
	strh r0, [r1, #0x4]
	ldrh r0, [r2, #0x12]
	strh r0, [r1, #0x6]
	ldr r0, [r5, #0x54]
	add r0, r0, #0x1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x4]
	cmp r0, r1
	blo _0201CFB8
	cmp r7, #0x4
	bne _0201CFB2
	bl _u32_div_f
	str r1, [r5, #0x54]
	b _0201CFB8
_0201CFB2:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0201CFB8:
	ldr r1, [r5, #0x8]
	add r4, r4, #0x1
	cmp r4, r1
	blo _0201CF68
_0201CFC0:
	ldr r0, _0201CFC8 ; =UNK_021C5938
	ldr r0, [r0, #0x54]
	pop {r3-r7, pc}
	nop
_0201CFC8: .word UNK_021C5938
_0201CFCC: .word UNK_021C5938

	thumb_func_start FUN_0201CFD0
FUN_0201CFD0: ; 0x0201CFD0
	push {r4-r7}
	mov r2, #0x0
	strh r2, [r0, #0x0]
	add r3, r0, #0x0
	add r6, r2, #0x0
_0201CFDA:
	strh r6, [r3, #0x8]
	strh r6, [r3, #0x6]
	strh r6, [r3, #0x2]
	strh r6, [r3, #0x4]
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x8
	blt _0201CFDA
	ldr r2, _0201D038 ; =UNK_021C5938
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	bls _0201D034
	ldr r4, _0201D03C ; =UNK_021C5938
_0201CFF4:
	sub r3, r1, r3
	add r3, r6, r3
	add r3, r3, #0x1
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	bpl _0201D006
	add r3, #0x9
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
_0201D006:
	lsl r3, r3, #0x3
	add r5, r4, r3
	ldrh r3, [r5, #0x12]
	cmp r3, #0x0
	bne _0201D02C
	ldrh r3, [r0, #0x0]
	ldrh r7, [r5, #0xc]
	lsl r3, r3, #0x3
	add r3, r0, r3
	strh r7, [r3, #0x2]
	ldrh r7, [r5, #0xe]
	strh r7, [r3, #0x4]
	ldrh r7, [r5, #0x10]
	strh r7, [r3, #0x6]
	ldrh r5, [r5, #0x12]
	strh r5, [r3, #0x8]
	ldrh r3, [r0, #0x0]
	add r3, r3, #0x1
	strh r3, [r0, #0x0]
_0201D02C:
	ldr r3, [r2, #0x8]
	add r6, r6, #0x1
	cmp r6, r3
	blo _0201CFF4
_0201D034:
	pop {r4-r7}
	bx lr
	.balign 4
_0201D038: .word UNK_021C5938
_0201D03C: .word UNK_021C5938
