	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	; matColorMask_$8998
	.global UNK_020FF9D0
UNK_020FF9D0: ; 0x020FF9D0
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F
	.byte 0x00, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F

	; static const in function
	; pivotUtil_$9100
	.global UNK_020FF9F0
UNK_020FF9F0: ; 0x020FF9F0
	.byte 0x04, 0x05, 0x07, 0x08
	.byte 0x03, 0x05, 0x06, 0x08
	.byte 0x03, 0x04, 0x06, 0x07
	.byte 0x01, 0x02, 0x07, 0x08
	.byte 0x00, 0x02, 0x06, 0x08
	.byte 0x00, 0x01, 0x06, 0x07
	.byte 0x01, 0x02, 0x04, 0x05
	.byte 0x00, 0x02, 0x03, 0x05
	.byte 0x00, 0x01, 0x03, 0x04

	; static const in function
	.section .data

	; cmd$9407
	.global UNK_02106630
UNK_02106630: ; 0x02106630
	.byte 0x2A, 0x00, 0x00, 0x00

	; cmd$9407 + 0x4
	.global UNK_02106634
UNK_02106634: ; 0x02106634
	.byte 0x00, 0x00, 0x00, 0x00

	; cmd$9366
	.global UNK_02106638
UNK_02106638: ; 0x02106638
	.byte 0x2A, 0x00, 0x00, 0x00

	; cmd$9366 + 0x4
	.global UNK_0210663C
UNK_0210663C: ; 0x0210663C
	.byte 0x00, 0x00, 0x00, 0x00

	; NNS_G3dFuncSbcMatTable
	.global UNK_02106640
UNK_02106640: ; 0x02106640
	.word FUN_020BA58C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; NNS_G3dFuncSbcShpTable
	.global UNK_02106650
UNK_02106650: ; 0x02106650
	.word FUN_020BA438
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; mtx$9412
	.global UNK_02106660
UNK_02106660: ; 0x02106660
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00

	; bbcmd1$9173
	.global UNK_021066A0
UNK_021066A0: ; 0x021066A0
	.byte 0x12, 0x10, 0x17, 0x1B

	; bbcmd1$9173 + 0x4
	.global UNK_021066A4
UNK_021066A4: ; 0x021066A4
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	; bbcmd1$9173 + 0xC
	.global UNK_021066AC
UNK_021066AC: ; 0x021066AC
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	; bbcmd1$9173 + 0x30
	.global UNK_021066D0
UNK_021066D0: ; 0x021066D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; bbcmd1$9173 + 0x3C
	.global UNK_021066DC
UNK_021066DC: ; 0x021066DC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; bbcmd1$9234
	.global UNK_021066E8
UNK_021066E8: ; 0x021066E8
	.byte 0x12, 0x10, 0x17, 0x1B

	; bbcmd1$9234 + 0x4
	.global UNK_021066EC
UNK_021066EC: ; 0x021066EC
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	; bbcmd1$9234 + 0xC
	.global UNK_021066F4
UNK_021066F4: ; 0x021066F4
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	; bbcmd1$9234 + 0x30
	.global UNK_02106718
UNK_02106718: ; 0x02106718
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; bbcmd1$9234 + 0x3C
	.global UNK_02106724
UNK_02106724: ; 0x02106724
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; NNS_G3dFuncSbcTable
	.global UNK_02106730
UNK_02106730: ; 0x02106730
	.word FUN_020BAC70
	.word FUN_020BAC48
	.word FUN_020BAAC0
	.word FUN_020BA9EC
	.word FUN_020BA50C
	.word FUN_020BA3C4
	.word FUN_020B9F84
	.word FUN_020B9C54
	.word FUN_020B98C4
	.word FUN_020B9258
	.word FUN_020B9178
	.word FUN_020B9110
	.word FUN_020B8DF0
	.word FUN_020B8A60
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

	; NNS_G3dRS
	.global UNK_021CEF7C
UNK_021CEF7C: ; 0x021CEF7C
	.space 0x4

	; NNS_G3dRSOnGlb
	.global UNK_021CEF80
UNK_021CEF80: ; 0x021CEF80
	.space 0xe00

	; NNS_G3dRSOnGlb + 0xE00
	.global UNK_021CFD80
UNK_021CFD80: ; 0x021CFD80
	.space 0x4

	; NNS_G3dRSOnGlb + 0xE04
	.global UNK_021CFD84
UNK_021CFD84: ; 0x021CFD84
	.space 0x4

	; NNS_G3dRSOnGlb + 0xE08
	.global UNK_021CFD88
UNK_021CFD88: ; 0x021CFD88
	.space 0x4

	; NNS_G3dRSOnGlb + 0xE0C
	.global UNK_021CFD8C
UNK_021CFD8C: ; 0x021CFD8C
	.space 0x4

	; NNS_G3dRSOnGlb + 0xE10
	.global UNK_021CFD90
UNK_021CFD90: ; 0x021CFD90
	.space 0x4

	; NNS_G3dRSOnGlb + 0xE14
	.global UNK_021CFD94
UNK_021CFD94: ; 0x021CFD94
	.space 0x2ba

	; NNS_G3dRSOnGlb + 0x10CE
	.global UNK_021D004E
UNK_021D004E: ; 0x021D004E
	.space 0x332

	; NNS_G3dRSOnGlb + 0x1400
	.global UNK_021D0380
UNK_021D0380: ; 0x021D0380
	.space 0x40

	; NNS_G3dRSOnGlb + 0x1440
	.global UNK_021D03C0
UNK_021D03C0: ; 0x021D03C0
	.space 0xb42

	; NNS_G3dRSOnGlb + 0x1F82
	.global UNK_021D0F02
UNK_021D0F02: ; 0x021D0F02
	.space 0xd7e

	.section .text

	; NNSi_G3dFuncSbc_PRJMAP
	arm_func_start FUN_020B8A60
FUN_020B8A60: ; 0x020B8A60
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x80
	mov r5, r0
	ldr r1, [r5, #0x8]
	ands r0, r1, #0x200
	bne _020B8DB4
	ands r0, r1, #0x1
	beq _020B8DB4
	add r0, sp, #0x10
	mov r1, #0x0
	bl FUN_020BB824
	mov r0, #0x1e
	str r0, [sp, #0x0]
	add r1, sp, #0x0
	mov r0, #0x13
	mov r2, #0x1
	bl FUN_020BB1C0
	ldr r2, [r5, #0xb0]
	ldr r0, [r2, #0x10]
	and r1, r0, #0xc0000000
	cmp r1, #0xc0000000
	beq _020B8AF0
	bic r0, r0, #0xc0000000
	str r0, [r2, #0x10]
	ldr r2, [r5, #0xb0]
	ldr r3, _020B8DC8 ; =UNK_02106630
	ldr r0, [r2, #0x10]
	ldr r1, _020B8DCC ; =UNK_02106634
	orr r0, r0, #0xc0000000
	str r0, [r2, #0x10]
	ldr r2, [r5, #0xb0]
	ldr r0, [r3, #0x0]
	ldr r4, [r2, #0x10]
	mov r2, #0x1
	str r4, [r3, #0x4]
	bl FUN_020BB1C0
_020B8AF0:
	ldr r0, [r5, #0x40]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x99]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020B8B3C
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x40]
	blx r1
	ldr r0, [r5, #0x40]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x99]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020B8B40
_020B8B3C:
	mov r0, #0x0
_020B8B40:
	cmp r0, #0x0
	bne _020B8B84
	ldr r0, [r5, #0xb0]
	ldr r1, _020B8DD0 ; =UNK_02106660
	ldrh r6, [r0, #0x2e]
	ldrh r3, [r0, #0x2c]
	mov r0, #0x16
	rsb r2, r6, #0x0
	mov lr, r3, lsl #0xf
	mov r12, r2, lsl #0xf
	mov r3, r6, lsl #0xf
	mov r2, #0x10
	str lr, [r1, #0x0]
	str r12, [r1, #0x14]
	str lr, [r1, #0x30]
	str r3, [r1, #0x34]
	bl FUN_020BB1C0
_020B8B84:
	cmp r4, #0x2
	bne _020B8BC0
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x40]
	blx r1
	ldr r0, [r5, #0x40]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x99]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020B8BC4
_020B8BC0:
	mov r0, #0x0
_020B8BC4:
	cmp r0, #0x0
	bne _020B8C28
	ldr r12, [r5, #0xd8]
	ldr r0, [r5, #0x0]
	ldrh r2, [r12, #0xa]
	add r3, r12, #0x4
	ldrb r0, [r0, #0x1]
	ldrh r1, [r3, r2]
	add r2, r3, r2
	mla r0, r1, r0, r2
	ldr r0, [r0, #0x4]
	add r1, r12, r0
	ldrh r2, [r1, #0x1e]
	ands r0, r2, #0x2000
	beq _020B8C28
	add r1, r1, #0x2c
	ands r0, r2, #0x2
	addeq r1, r1, #0x8
	ands r0, r2, #0x4
	addeq r1, r1, #0x4
	ands r0, r2, #0x8
	addeq r1, r1, #0x8
	mov r0, #0x18
	mov r2, #0x10
	bl FUN_020BB1C0
_020B8C28:
	cmp r4, #0x3
	movne r0, #0x0
	bne _020B8C54
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x40]
	blx r1
	ldr r0, [r5, #0x8]
	and r0, r0, #0x40
_020B8C54:
	cmp r0, #0x0
	bne _020B8D84
	ldr r0, _020B8DD4 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B8CA0
	ldr r1, _020B8DD8 ; =UNK_021CEDF8
	mov r0, #0x1c
	mov r2, #0x3
	bl FUN_020BB1C0
	ldr r1, _020B8DDC ; =UNK_021CEDD4
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	add r1, sp, #0x10
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020B8CE0
_020B8CA0:
	ands r0, r1, #0x2
	beq _020B8CBC
	add r1, sp, #0x10
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	b _020B8CE0
_020B8CBC:
	bl FUN_020B8344
	mov r1, r0
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
	add r1, sp, #0x10
	mov r0, #0x19
	mov r2, #0xc
	bl FUN_020BB1C0
_020B8CE0:
	bl FUN_020BB394
	ldr r0, _020B8DE0 ; =0x04000440
	mov r2, #0x0
	ldr r1, _020B8DE4 ; =0x04000444
	str r2, [r0, #0x0]
	ldr r0, _020B8DE8 ; =0x04000454
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add r4, sp, #0x40
_020B8D04:
	mov r0, r4
	bl G3X_GetClipMtx
	cmp r0, #0x0
	bne _020B8D04
	ldr r1, _020B8DEC ; =0x04000448
	mov r2, #0x1
	str r2, [r1, #0x0]
	ldr r0, _020B8DE0 ; =0x04000440
	mov r2, #0x3
	str r2, [r0, #0x0]
	add r1, sp, #0x40
	mov r0, #0x16
	mov r2, #0x10
	bl FUN_020BB1C0
	ldr r1, [sp, #0x70]
	ldr r0, [sp, #0x74]
	mov r2, r1, asr #0x4
	mov r1, r0, asr #0x4
	mov r0, r2, lsl #0x8
	mov r1, r1, lsl #0x8
	mov r0, r0, asr #0x10
	mov r1, r1, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r1, lsr #0x10
	orr r3, r2, r0, lsl #0x10
	add r1, sp, #0x4
	mov r0, #0x22
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B8D84:
	mov r3, #0x2
	add r1, sp, #0x8
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FUN_020BB1C0
	mov r3, #0x1e
	add r1, sp, #0xc
	mov r0, #0x14
	mov r2, #0x1
	str r3, [sp, #0xc]
	bl FUN_020BB1C0
_020B8DB4:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x3
	str r0, [r5, #0x0]
	add sp, sp, #0x80
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B8DC8: .word UNK_02106630
_020B8DCC: .word UNK_02106634
_020B8DD0: .word UNK_02106660
_020B8DD4: .word UNK_021CED18
_020B8DD8: .word UNK_021CEDF8
_020B8DDC: .word UNK_021CEDD4
_020B8DE0: .word 0x04000440
_020B8DE4: .word 0x04000444
_020B8DE8: .word 0x04000454
_020B8DEC: .word 0x04000448
	arm_func_end FUN_020B8A60

	; NNSi_G3dFuncSbc_ENVMAP
	arm_func_start FUN_020B8DF0
FUN_020B8DF0: ; 0x020B8DF0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x44
	mov r7, r0
	ldr r1, [r7, #0x8]
	ands r0, r1, #0x200
	bne _020B90E8
	ands r0, r1, #0x1
	beq _020B90E8
	ldr r2, [r7, #0xb0]
	ldr r0, [r2, #0x10]
	and r1, r0, #0xc0000000
	cmp r1, #0x80000000
	beq _020B8E5C
	bic r0, r0, #0xc0000000
	str r0, [r2, #0x10]
	ldr r2, [r7, #0xb0]
	ldr r3, _020B90FC ; =UNK_02106638
	ldr r0, [r2, #0x10]
	ldr r1, _020B9100 ; =UNK_0210663C
	orr r0, r0, #0x80000000
	str r0, [r2, #0x10]
	ldr r2, [r7, #0xb0]
	ldr r0, [r3, #0x0]
	ldr r4, [r2, #0x10]
	mov r2, #0x1
	str r4, [r3, #0x4]
	bl FUN_020BB1C0
_020B8E5C:
	mov r0, #0x3
	str r0, [sp, #0x0]
	add r1, sp, #0x0
	mov r0, #0x10
	mov r2, #0x1
	bl FUN_020BB1C0
	ldr r0, [r7, #0x3c]
	cmp r0, #0x0
	ldrneb r6, [r7, #0x98]
	moveq r6, #0x0
	cmp r6, #0x1
	bne _020B8EC0
	ldr r1, [r7, #0x8]
	mov r0, r7
	bic r1, r1, #0x40
	str r1, [r7, #0x8]
	ldr r1, [r7, #0x3c]
	blx r1
	ldr r0, [r7, #0x3c]
	cmp r0, #0x0
	ldrneb r6, [r7, #0x98]
	ldr r0, [r7, #0x8]
	moveq r6, #0x0
	and r0, r0, #0x40
	b _020B8EC4
_020B8EC0:
	mov r0, #0x0
_020B8EC4:
	cmp r0, #0x0
	bne _020B8F3C
	ldr r0, [r7, #0xb0]
	add r1, sp, #0x38
	ldrh r4, [r0, #0x2e]
	ldrh r5, [r0, #0x2c]
	mov r3, #0x10000
	rsb r0, r4, #0x0
	mov r12, r0, lsl #0xf
	mov lr, r5, lsl #0xf
	mov r0, #0x1b
	mov r2, #0x3
	str lr, [sp, #0x38]
	str r12, [sp, #0x3c]
	str r3, [sp, #0x40]
	bl FUN_020BB1C0
	mov r0, r5, lsl #0x13
	mov r1, r4, lsl #0x13
	mov r0, r0, asr #0x10
	mov r1, r1, asr #0x10
	mov r0, r0, lsl #0x10
	mov r1, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r1, lsr #0x10
	orr r3, r2, r0, lsl #0x10
	add r1, sp, #0x4
	mov r0, #0x22
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B8F3C:
	cmp r6, #0x2
	bne _020B8F78
	ldr r1, [r7, #0x8]
	mov r0, r7
	bic r1, r1, #0x40
	str r1, [r7, #0x8]
	ldr r1, [r7, #0x3c]
	blx r1
	ldr r0, [r7, #0x3c]
	cmp r0, #0x0
	ldrneb r6, [r7, #0x98]
	ldr r0, [r7, #0x8]
	moveq r6, #0x0
	and r0, r0, #0x40
	b _020B8F7C
_020B8F78:
	mov r0, #0x0
_020B8F7C:
	cmp r0, #0x0
	bne _020B8FE0
	ldr r4, [r7, #0xd8]
	ldr r0, [r7, #0x0]
	ldrh r2, [r4, #0xa]
	add r3, r4, #0x4
	ldrb r0, [r0, #0x1]
	ldrh r1, [r3, r2]
	add r2, r3, r2
	mla r0, r1, r0, r2
	ldr r0, [r0, #0x4]
	add r1, r4, r0
	ldrh r2, [r1, #0x1e]
	ands r0, r2, #0x2000
	beq _020B8FE0
	add r1, r1, #0x2c
	ands r0, r2, #0x2
	addeq r1, r1, #0x8
	ands r0, r2, #0x4
	addeq r1, r1, #0x4
	ands r0, r2, #0x8
	addeq r1, r1, #0x8
	mov r0, #0x18
	mov r2, #0x10
	bl FUN_020BB1C0
_020B8FE0:
	cmp r6, #0x3
	movne r0, #0x0
	bne _020B900C
	ldr r1, [r7, #0x8]
	mov r0, r7
	bic r1, r1, #0x40
	str r1, [r7, #0x8]
	ldr r1, [r7, #0x3c]
	blx r1
	ldr r0, [r7, #0x8]
	and r0, r0, #0x40
_020B900C:
	cmp r0, #0x0
	bne _020B90D0
	mov r3, #0x2
	add r1, sp, #0x8
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FUN_020BB1C0
	add r1, sp, #0x14
	mov r0, #0x0
	bl FUN_020BB824
	mov r3, #0x3
	add r1, sp, #0xc
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0xc]
	bl FUN_020BB1C0
	ldr r0, _020B9104 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9094
	ldr r1, _020B9108 ; =UNK_021CED64
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	ldr r1, _020B910C ; =UNK_021CEDD4
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	add r1, sp, #0x14
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020B90D0
_020B9094:
	ands r0, r1, #0x2
	beq _020B90C0
	ldr r1, _020B9108 ; =UNK_021CED64
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	add r1, sp, #0x14
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
	b _020B90D0
_020B90C0:
	add r1, sp, #0x14
	mov r0, #0x1a
	mov r2, #0x9
	bl FUN_020BB1C0
_020B90D0:
	mov r3, #0x2
	add r1, sp, #0x10
	mov r0, #0x10
	mov r2, #0x1
	str r3, [sp, #0x10]
	bl FUN_020BB1C0
_020B90E8:
	ldr r0, [r7, #0x0]
	add r0, r0, #0x3
	str r0, [r7, #0x0]
	add sp, sp, #0x44
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020B90FC: .word UNK_02106638
_020B9100: .word UNK_0210663C
_020B9104: .word UNK_021CED18
_020B9108: .word UNK_021CED64
_020B910C: .word UNK_021CEDD4
	arm_func_end FUN_020B8DF0

	; _end
	arm_func_start FUN_020B9110
FUN_020B9110: ; 0x020B9110
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	mov r4, r0
	ldr r2, [r4, #0x8]
	ands r0, r2, #0x100
	bne _020B9164
	ands r0, r2, #0x200
	bne _020B9164
	cmp r1, #0x0
	ldreq r0, [r4, #0xe0]
	add r1, sp, #0x0
	streq r0, [sp, #0x8]
	streq r0, [sp, #0x4]
	streq r0, [sp, #0x0]
	ldrne r0, [r4, #0xe4]
	mov r2, #0x3
	strne r0, [sp, #0x8]
	strne r0, [sp, #0x4]
	strne r0, [sp, #0x0]
	mov r0, #0x1b
	bl FUN_020BB1C0
_020B9164:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020B9110

	; _end
	arm_func_start FUN_020B9178
FUN_020B9178: ; 0x020B9178
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x96]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020B91CC
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x34]
	blx r1
	ldr r0, [r5, #0x34]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x96]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r1, r0, #0x40
	b _020B91D0
_020B91CC:
	mov r1, #0x0
_020B91D0:
	ldr r0, [r5, #0x8]
	ands r0, r0, #0x100
	bne _020B9228
	cmp r1, #0x0
	bne _020B9228
	ldr r0, [r5, #0x0]
	ldrb r12, [r0, #0x1]
	ldrb r3, [r0, #0x2]
	ldrb lr, [r0, #0x3]
	ldrb r2, [r0, #0x5]
	ldrb r1, [r0, #0x6]
	orr r3, r12, r3, lsl #0x8
	ldrb r6, [r0, #0x4]
	orr r12, r3, lr, lsl #0x10
	ldrb r3, [r0, #0x7]
	orr r1, r2, r1, lsl #0x8
	orr r6, r12, r6, lsl #0x18
	ldrb r2, [r0, #0x8]
	orr r1, r1, r3, lsl #0x10
	add r0, r0, r6
	orr r1, r1, r2, lsl #0x18
	bl FUN_020BB2B0
_020B9228:
	cmp r4, #0x3
	bne _020B9248
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x34]
	blx r1
_020B9248:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x9
	str r0, [r5, #0x0]
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020B9178

	; NNSi_G3dFuncSbc_NODEMIX
	arm_func_start FUN_020B9258
FUN_020B9258: ; 0x020B9258
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x8c
	ldr r1, [r0, #0x4]
	ldr r4, [r0, #0x0]
	ldr r6, [r1, #0x4]
	ldrb r2, [r4, #0x2]
	ldr r3, [r6, #0x10]
	mov r10, #0x0
	str r0, [sp, #0x0]
	str r2, [sp, #0x8]
	add r3, r6, r3
	add r1, sp, #0x34
	mov r0, r10
	mov r2, #0x54
	mov r9, r10
	str r3, [sp, #0x4]
	add r8, r4, #0x3
	bl MIi_CpuClearFast
	bl FUN_020BB394
	ldr r0, _020B98AC ; =0x04000440
	mov r7, r10
	str r7, [r0, #0x0]
	mov r0, #0x1
	ldr r2, _020B98B0 ; =0x0400044C
	ldr r1, _020B98B4 ; =0x04000454
	str r0, [r2, #0x0]
	str r0, [sp, #0x10]
	str r7, [r1, #0x0]
	mov r1, #0x2
	ldr r0, _020B98AC ; =0x04000440
	str r1, [sp, #0x14]
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bls _020B96CC
_020B92E4:
	ldrb r4, [r8, #0x1]
	mov r0, #0x64
	ldr r3, _020B98B8 ; =UNK_021D0380
	mul r0, r4, r0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x0]
	mov r1, r4, lsr #0x5
	add r0, r0, r1, lsl #0x2
	ldr r1, [sp, #0x10]
	and r2, r4, #0x1f
	mov r1, r1, lsl r2
	ldr r11, [r0, #0xcc]
	ldr r2, [sp, #0xc]
	ands r11, r1, r11
	add r6, r3, r2
	bne _020B9358
	ldr r3, [r0, #0xcc]
	mov r2, #0x54
	orr r1, r3, r1
	str r1, [r0, #0xcc]
	ldr r0, [sp, #0x4]
	ldr r1, _020B98BC ; =0x04000450
	mla r0, r4, r2, r0
	ldrb r2, [r8, #0x0]
	str r2, [r1, #0x0]
	ldr r2, [sp, #0x10]
	ldr r1, _020B98AC ; =0x04000440
	str r2, [r1, #0x0]
	bl G3_MultMtx43
_020B9358:
	cmp r7, #0x0
	beq _020B9500
	ldr r2, [sp, #0x6c]
	ldr r1, [r5, #0x0]
	str r2, [sp, #0x18]
	ldr r2, [sp, #0x70]
	mov r0, r1, asr #0x1f
	str r2, [sp, #0x1c]
	ldr r2, [sp, #0x74]
	ldr r12, [sp, #0x64]
	str r2, [sp, #0x20]
	ldr r2, [sp, #0x78]
	ldr lr, [sp, #0x68]
	str r2, [sp, #0x24]
	ldr r2, [sp, #0x7c]
	str r2, [sp, #0x28]
	ldr r2, [sp, #0x80]
	str r2, [sp, #0x2c]
	ldr r2, [sp, #0x84]
	str r2, [sp, #0x30]
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, r12, r0
	str r0, [sp, #0x64]
	ldr r1, [r5, #0x4]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, lr, r0
	str r0, [sp, #0x68]
	ldr r1, [r5, #0x8]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x18]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x6c]
	ldr r1, [r5, #0xc]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x1c]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x70]
	ldr r1, [r5, #0x10]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x20]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x74]
	ldr r1, [r5, #0x14]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x24]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x78]
	ldr r1, [r5, #0x18]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x28]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x7c]
	ldr r1, [r5, #0x1c]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x2c]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x80]
	ldr r1, [r5, #0x20]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r1, r3, lsr #0xc
	ldr r0, [sp, #0x30]
	orr r1, r1, r2, lsl #0x14
	adds r0, r0, r1
	str r0, [sp, #0x84]
_020B9500:
	cmp r11, #0x0
	bne _020B9538
_020B9508:
	mov r0, r6
	bl G3X_GetClipMtx
	cmp r0, #0x0
	bne _020B9508
	ldr r1, [sp, #0x14]
	ldr r0, _020B98AC ; =0x04000440
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	mov r1, #0x54
	mla r0, r4, r1, r0
	add r0, r0, #0x30
	bl G3_MultMtx33
_020B9538:
	ldrb r1, [r8, #0x2]
	ldr r2, [sp, #0x34]
	ldr r0, [r6, #0x0]
	mov r10, r1, lsl #0x4
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x34]
	mov r9, r10, asr #0x1f
	ldr r2, [sp, #0x38]
	ldr r0, [r6, #0x4]
	ldr r3, [sp, #0x3c]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x38]
	ldr r0, [r6, #0x8]
	ldr r2, [sp, #0x40]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x3c]
	ldr r0, [r6, #0x10]
	ldr r3, [sp, #0x44]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x40]
	ldr r0, [r6, #0x14]
	ldr r2, [sp, #0x48]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x44]
	ldr r0, [r6, #0x18]
	ldr r3, [sp, #0x4c]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x48]
	ldr r0, [r6, #0x20]
	ldr r2, [sp, #0x50]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x4c]
	ldr r0, [r6, #0x24]
	ldr r3, [sp, #0x54]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x50]
	ldr r0, [r6, #0x28]
	ldr r2, [sp, #0x58]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x54]
	ldr r0, [r6, #0x30]
	ldr r3, [sp, #0x5c]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x58]
	ldr r0, [r6, #0x34]
	ldr r2, [sp, #0x60]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r3, r1
	str r0, [sp, #0x5c]
	ldr r0, [r6, #0x38]
	smull r1, r0, r10, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	adds r0, r2, r1
	str r0, [sp, #0x60]
	cmp r11, #0x0
	ldr r1, _020B98C0 ; =UNK_021D03C0
	ldr r0, [sp, #0xc]
	add r5, r1, r0
	add r8, r8, #0x3
	bne _020B96BC
_020B96AC:
	mov r0, r5
	bl G3X_GetVectorMtx
	cmp r0, #0x0
	bne _020B96AC
_020B96BC:
	ldr r0, [sp, #0x8]
	add r7, r7, #0x1
	cmp r7, r0
	blo _020B92E4
_020B96CC:
	ldr r1, [r5, #0x0]
	ldr r4, [sp, #0x64]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, r4, r0
	str r0, [sp, #0x64]
	ldr r1, [r5, #0x4]
	ldr r4, [sp, #0x68]
	mov r0, r1, asr #0x1f
	umull r3, r2, r10, r1
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	mov r0, r3, lsr #0xc
	orr r0, r0, r2, lsl #0x14
	adds r0, r4, r0
	str r0, [sp, #0x68]
	ldr r1, [r5, #0x8]
	ldr r4, [sp, #0x6c]
	umull r0, r2, r10, r1
	mov r3, r0, lsr #0xc
	mov r0, r1, asr #0x1f
	mla r2, r10, r0, r2
	mla r2, r9, r1, r2
	orr r3, r3, r2, lsl #0x14
	adds r0, r4, r3
	str r0, [sp, #0x6c]
	ldr r7, [r5, #0xc]
	ldr r12, [sp, #0x70]
	mov r6, r7, asr #0x1f
	umull r11, r8, r10, r7
	mla r8, r10, r6, r8
	mla r8, r9, r7, r8
	mov r6, r11, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	adds r6, r12, r6
	str r6, [sp, #0x70]
	ldr r7, [r5, #0x10]
	ldr r4, [sp, #0x74]
	mov r6, r7, asr #0x1f
	umull r11, r8, r10, r7
	mla r8, r10, r6, r8
	mla r8, r9, r7, r8
	mov r6, r11, lsr #0xc
	orr r6, r6, r8, lsl #0x14
	adds r4, r4, r6
	str r4, [sp, #0x74]
	ldr r6, [r5, #0x14]
	ldr r3, [sp, #0x78]
	mov r4, r6, asr #0x1f
	umull r8, r7, r10, r6
	mla r7, r10, r4, r7
	mla r7, r9, r6, r7
	mov r4, r8, lsr #0xc
	orr r4, r4, r7, lsl #0x14
	adds r3, r3, r4
	str r3, [sp, #0x78]
	ldr r4, [r5, #0x18]
	ldr r2, [sp, #0x7c]
	mov r3, r4, asr #0x1f
	umull r7, r6, r10, r4
	mla r6, r10, r3, r6
	mla r6, r9, r4, r6
	mov r3, r7, lsr #0xc
	orr r3, r3, r6, lsl #0x14
	adds r2, r2, r3
	str r2, [sp, #0x7c]
	ldr r3, [r5, #0x1c]
	ldr r1, [sp, #0x80]
	mov r2, r3, asr #0x1f
	umull r6, r4, r10, r3
	mla r4, r10, r2, r4
	mla r4, r9, r3, r4
	mov r2, r6, lsr #0xc
	orr r2, r2, r4, lsl #0x14
	adds r1, r1, r2
	str r1, [sp, #0x80]
	ldr r2, [r5, #0x20]
	ldr lr, [sp, #0x84]
	mov r1, r2, asr #0x1f
	umull r4, r3, r10, r2
	mla r3, r10, r1, r3
	mla r3, r9, r2, r3
	mov r1, r4, lsr #0xc
	orr r1, r1, r3, lsl #0x14
	adds r1, lr, r1
	add r0, sp, #0x64
	str r1, [sp, #0x84]
	bl G3_LoadMtx43
	ldr r1, _020B98AC ; =0x04000440
	mov r2, #0x1
	add r0, sp, #0x34
	str r2, [r1, #0x0]
	bl G3_LoadMtx43
	ldr r3, _020B98AC ; =0x04000440
	mov r0, #0x0
	str r0, [r3, #0x0]
	ldr r1, _020B98BC ; =0x04000450
	mov r2, #0x1
	mov r0, #0x2
	str r2, [r1, #0x0]
	str r0, [r3, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, _020B98B0 ; =0x0400044C
	ldrb r2, [r1, #0x1]
	mov r1, #0x3
	str r2, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldr r2, [r0, #0x0]
	ldrb r0, [r2, #0x2]
	add r0, r0, #0x1
	mla r1, r0, r1, r2
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x8c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B98AC: .word 0x04000440
_020B98B0: .word 0x0400044C
_020B98B4: .word 0x04000454
_020B98B8: .word UNK_021D0380
_020B98BC: .word 0x04000450
_020B98C0: .word UNK_021D03C0
	arm_func_end FUN_020B9258

	; NNSi_G3dFuncSbc_BBY
	arm_func_start FUN_020B98C4
FUN_020B98C4: ; 0x020B98C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xcc
	mov r10, r0
	ldr r2, [r10, #0x8]
	mov r9, r1
	ands r0, r2, #0x200
	mov r7, #0x2
	ldr r6, _020B9C28 ; =UNK_02106718
	ldr fp, _020B9C2C ; =UNK_02106724
	ldr r5, _020B9C30 ; =UNK_021066F4
	beq _020B992C
	cmp r9, #0x40
	beq _020B9900
	cmp r9, #0x60
	bne _020B9904
_020B9900:
	add r7, r7, #0x1
_020B9904:
	cmp r9, #0x20
	beq _020B9914
	cmp r9, #0x60
	bne _020B9918
_020B9914:
	add r7, r7, #0x1
_020B9918:
	ldr r0, [r10, #0x0]
	add sp, sp, #0xcc
	add r0, r0, r7
	str r0, [r10, #0x0]
	ldmia sp!, {r4-r11,pc}
_020B992C:
	cmp r9, #0x40
	beq _020B993C
	cmp r9, #0x60
	bne _020B9974
_020B993C:
	add r7, r7, #0x1
	ands r0, r2, #0x100
	bne _020B9974
	cmp r9, #0x40
	ldreq r0, [r10, #0x0]
	add r1, sp, #0x0
	ldreqb r0, [r0, #0x2]
	mov r2, #0x1
	streq r0, [sp, #0x0]
	ldrne r0, [r10, #0x0]
	ldrneb r0, [r0, #0x3]
	strne r0, [sp, #0x0]
	mov r0, #0x14
	bl FUN_020BB1C0
_020B9974:
	ldr r0, [r10, #0x2c]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x94]
	moveq r8, #0x0
	cmp r8, #0x1
	bne _020B99C0
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x2c]
	blx r1
	ldr r0, [r10, #0x2c]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x94]
	ldr r0, [r10, #0x8]
	moveq r8, #0x0
	and r1, r0, #0x40
	b _020B99C4
_020B99C0:
	mov r1, #0x0
_020B99C4:
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020B9BA4
	cmp r1, #0x0
	bne _020B9BA4
	bl FUN_020BB394
	ldr r2, _020B9C34 ; =0x00151110
	ldr r1, _020B9C38 ; =0x04000400
	mov r0, #0x0
	str r2, [r1, #0x0]
	str r0, [r1, #0x0]
	str r0, [r1, #0x0]
	add r4, sp, #0x8
_020B99F8:
	mov r0, r4
	bl G3X_GetClipMtx
	cmp r0, #0x0
	bne _020B99F8
	ldr r0, _020B9C3C ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9A38
	bl FUN_020B82A4
	add r1, sp, #0x48
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x48
	mov r2, r0
	bl MTX_Concat44
	b _020B9A5C
_020B9A38:
	ands r0, r1, #0x2
	beq _020B9A5C
	ldr r0, _020B9C40 ; =UNK_021CED64
	add r1, sp, #0x88
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x88
	mov r2, r0
	bl MTX_Concat44
_020B9A5C:
	ldr r1, [sp, #0x38]
	add r0, sp, #0x8
	str r1, [r6, #0x0]
	ldr r1, [sp, #0x3c]
	str r1, [r6, #0x4]
	ldr r1, [sp, #0x40]
	str r1, [r6, #0x8]
	bl VEC_Mag
	str r0, [r11, #0x0]
	add r0, sp, #0x18
	bl VEC_Mag
	str r0, [r11, #0x4]
	add r0, sp, #0x28
	bl VEC_Mag
	str r0, [r11, #0x8]
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _020B9AB0
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	beq _020B9AD4
_020B9AB0:
	add r0, sp, #0x18
	add r1, r5, #0xc
	bl VEC_Normalize
	ldr r0, [r5, #0x14]
	rsb r0, r0, #0x0
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x10]
	str r0, [r5, #0x20]
	b _020B9AF4
_020B9AD4:
	add r0, sp, #0x28
	add r1, r5, #0x18
	bl VEC_Normalize
	ldr r0, [r5, #0x1c]
	rsb r0, r0, #0x0
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x20]
	str r0, [r5, #0x10]
_020B9AF4:
	ldr r0, _020B9C3C ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9B48
	ldr r3, _020B9C44 ; =0x00171012
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C48 ; =UNK_021066EC
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8264
	ldr r1, _020B9C38 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9C4C ; =0x00001B19
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C30 ; =UNK_021066F4
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9BA4
_020B9B48:
	ands r0, r1, #0x2
	beq _020B9B94
	ldr r3, _020B9C44 ; =0x00171012
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C48 ; =UNK_021066EC
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8344
	ldr r1, _020B9C38 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9C4C ; =0x00001B19
	ldr r1, _020B9C38 ; =0x04000400
	ldr r0, _020B9C30 ; =UNK_021066F4
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9BA4
_020B9B94:
	ldr r0, _020B9C50 ; =UNK_021066E8
	ldr r1, _020B9C38 ; =0x04000400
	mov r2, #0x48
	bl MIi_CpuSend32
_020B9BA4:
	cmp r8, #0x3
	movne r0, #0x0
	bne _020B9BD0
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x2c]
	blx r1
	ldr r0, [r10, #0x8]
	and r0, r0, #0x40
_020B9BD0:
	cmp r9, #0x20
	beq _020B9BE0
	cmp r9, #0x60
	bne _020B9C14
_020B9BE0:
	cmp r0, #0x0
	add r7, r7, #0x1
	bne _020B9C14
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020B9C14
	ldr r0, [r10, #0x0]
	add r1, sp, #0x4
	ldrb r3, [r0, #0x2]
	mov r0, #0x13
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B9C14:
	ldr r0, [r10, #0x0]
	add r0, r0, r7
	str r0, [r10, #0x0]
	add sp, sp, #0xcc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020B9C28: .word UNK_02106718
_020B9C2C: .word UNK_02106724
_020B9C30: .word UNK_021066F4
_020B9C34: .word 0x00151110
_020B9C38: .word 0x04000400
_020B9C3C: .word UNK_021CED18
_020B9C40: .word UNK_021CED64
_020B9C44: .word 0x00171012
_020B9C48: .word UNK_021066EC
_020B9C4C: .word 0x00001B19
_020B9C50: .word UNK_021066E8
	arm_func_end FUN_020B98C4

	; NNSi_G3dFuncSbc_BB
	arm_func_start FUN_020B9C54
FUN_020B9C54: ; 0x020B9C54
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0xc8
	mov r9, r0
	ldr r2, [r9, #0x8]
	mov r8, r1
	ands r0, r2, #0x200
	mov r6, #0x2
	ldr r5, _020B9F58 ; =UNK_021066D0
	ldr r4, _020B9F5C ; =UNK_021066DC
	beq _020B9CB8
	cmp r8, #0x40
	beq _020B9C8C
	cmp r8, #0x60
	bne _020B9C90
_020B9C8C:
	add r6, r6, #0x1
_020B9C90:
	cmp r8, #0x20
	beq _020B9CA0
	cmp r8, #0x60
	bne _020B9CA4
_020B9CA0:
	add r6, r6, #0x1
_020B9CA4:
	ldr r0, [r9, #0x0]
	add sp, sp, #0xc8
	add r0, r0, r6
	str r0, [r9, #0x0]
	ldmia sp!, {r4-r10,pc}
_020B9CB8:
	cmp r8, #0x40
	beq _020B9CC8
	cmp r8, #0x60
	bne _020B9D00
_020B9CC8:
	add r6, r6, #0x1
	ands r0, r2, #0x100
	bne _020B9D00
	cmp r8, #0x40
	ldreq r0, [r9, #0x0]
	add r1, sp, #0x0
	ldreqb r0, [r0, #0x2]
	mov r2, #0x1
	streq r0, [sp, #0x0]
	ldrne r0, [r9, #0x0]
	ldrneb r0, [r0, #0x3]
	strne r0, [sp, #0x0]
	mov r0, #0x14
	bl FUN_020BB1C0
_020B9D00:
	ldr r0, [r9, #0x28]
	cmp r0, #0x0
	ldrneb r7, [r9, #0x93]
	moveq r7, #0x0
	cmp r7, #0x1
	bne _020B9D4C
	ldr r1, [r9, #0x8]
	mov r0, r9
	bic r1, r1, #0x40
	str r1, [r9, #0x8]
	ldr r1, [r9, #0x28]
	blx r1
	ldr r0, [r9, #0x28]
	cmp r0, #0x0
	ldrneb r7, [r9, #0x93]
	ldr r0, [r9, #0x8]
	moveq r7, #0x0
	and r1, r0, #0x40
	b _020B9D50
_020B9D4C:
	mov r1, #0x0
_020B9D50:
	ldr r0, [r9, #0x8]
	ands r0, r0, #0x100
	bne _020B9ED4
	cmp r1, #0x0
	bne _020B9ED4
	bl FUN_020BB394
	ldr r2, _020B9F60 ; =0x00151110
	ldr r1, _020B9F64 ; =0x04000400
	mov r0, #0x0
	str r2, [r1, #0x0]
	str r0, [r1, #0x0]
	str r0, [r1, #0x0]
	add r10, sp, #0x8
_020B9D84:
	mov r0, r10
	bl G3X_GetClipMtx
	cmp r0, #0x0
	bne _020B9D84
	ldr r0, _020B9F68 ; =UNK_021CED18
	ldr r1, [r0, #0xfc]
	ands r0, r1, #0x1
	beq _020B9DC4
	bl FUN_020B82A4
	add r1, sp, #0x48
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x48
	mov r2, r0
	bl MTX_Concat44
	b _020B9DE8
_020B9DC4:
	ands r0, r1, #0x2
	beq _020B9DE8
	ldr r0, _020B9F6C ; =UNK_021CED64
	add r1, sp, #0x88
	bl MTX_Copy43To44_
	add r0, sp, #0x8
	add r1, sp, #0x88
	mov r2, r0
	bl MTX_Concat44
_020B9DE8:
	ldr r1, [sp, #0x38]
	add r0, sp, #0x8
	str r1, [r5, #0x0]
	ldr r1, [sp, #0x3c]
	str r1, [r5, #0x4]
	ldr r1, [sp, #0x40]
	str r1, [r5, #0x8]
	bl VEC_Mag
	str r0, [r4, #0x0]
	add r0, sp, #0x18
	bl VEC_Mag
	str r0, [r4, #0x4]
	add r0, sp, #0x28
	bl VEC_Mag
	ldr r1, _020B9F68 ; =UNK_021CED18
	str r0, [r4, #0x8]
	ldr r1, [r1, #0xfc]
	ands r0, r1, #0x1
	beq _020B9E78
	ldr r3, _020B9F70 ; =0x00171012
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F74 ; =UNK_021066A4
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8264
	ldr r1, _020B9F64 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9F78 ; =0x00001B19
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F7C ; =UNK_021066AC
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9ED4
_020B9E78:
	ands r0, r1, #0x2
	beq _020B9EC4
	ldr r3, _020B9F70 ; =0x00171012
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F74 ; =UNK_021066A4
	mov r2, #0x8
	str r3, [r1, #0x0]
	bl MIi_CpuSend32
	bl FUN_020B8344
	ldr r1, _020B9F64 ; =0x04000400
	mov r2, #0x30
	bl MIi_CpuSend32
	ldr r2, _020B9F78 ; =0x00001B19
	ldr r1, _020B9F64 ; =0x04000400
	ldr r0, _020B9F7C ; =UNK_021066AC
	str r2, [r1, #0x0]
	mov r2, #0x3c
	bl MIi_CpuSend32
	b _020B9ED4
_020B9EC4:
	ldr r0, _020B9F80 ; =UNK_021066A0
	ldr r1, _020B9F64 ; =0x04000400
	mov r2, #0x48
	bl MIi_CpuSend32
_020B9ED4:
	cmp r7, #0x3
	movne r0, #0x0
	bne _020B9F00
	ldr r1, [r9, #0x8]
	mov r0, r9
	bic r1, r1, #0x40
	str r1, [r9, #0x8]
	ldr r1, [r9, #0x28]
	blx r1
	ldr r0, [r9, #0x8]
	and r0, r0, #0x40
_020B9F00:
	cmp r8, #0x20
	beq _020B9F10
	cmp r8, #0x60
	bne _020B9F44
_020B9F10:
	cmp r0, #0x0
	add r6, r6, #0x1
	bne _020B9F44
	ldr r0, [r9, #0x8]
	ands r0, r0, #0x100
	bne _020B9F44
	ldr r0, [r9, #0x0]
	add r1, sp, #0x4
	ldrb r3, [r0, #0x2]
	mov r0, #0x13
	mov r2, #0x1
	str r3, [sp, #0x4]
	bl FUN_020BB1C0
_020B9F44:
	ldr r0, [r9, #0x0]
	add r0, r0, r6
	str r0, [r9, #0x0]
	add sp, sp, #0xc8
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020B9F58: .word UNK_021066D0
_020B9F5C: .word UNK_021066DC
_020B9F60: .word 0x00151110
_020B9F64: .word 0x04000400
_020B9F68: .word UNK_021CED18
_020B9F6C: .word UNK_021CED64
_020B9F70: .word 0x00171012
_020B9F74: .word UNK_021066A4
_020B9F78: .word 0x00001B19
_020B9F7C: .word UNK_021066AC
_020B9F80: .word UNK_021066A0
	arm_func_end FUN_020B9C54

	; NNSi_G3dFuncSbc_NODEDESC
	arm_func_start FUN_020B9F84
FUN_020B9F84: ; 0x020B9F84
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r0, [r10, #0x0]
	mov r9, r1
	ldrb r4, [r0, #0x1]
	mov r7, #0x4
	strb r4, [r10, #0xae]
	ldr r0, [r10, #0x8]
	orr r0, r0, #0x10
	str r0, [r10, #0x8]
	ldr r1, [r10, #0x8]
	ands r0, r1, #0x400
	beq _020BA01C
	cmp r9, #0x40
	beq _020B9FCC
	cmp r9, #0x60
	bne _020B9FD0
_020B9FCC:
	add r7, r7, #0x1
_020B9FD0:
	cmp r9, #0x20
	beq _020B9FE0
	cmp r9, #0x60
	bne _020BA008
_020B9FE0:
	add r7, r7, #0x1
	ands r0, r1, #0x100
	bne _020BA008
	ldr r0, [r10, #0x0]
	add r1, sp, #0x8
	ldrb r3, [r0, #0x4]
	mov r0, #0x14
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FUN_020BB1C0
_020BA008:
	ldr r0, [r10, #0x0]
	add sp, sp, #0x14
	add r0, r0, r7
	str r0, [r10, #0x0]
	ldmia sp!, {r4-r11,pc}
_020BA01C:
	cmp r9, #0x40
	beq _020BA02C
	cmp r9, #0x60
	bne _020BA068
_020BA02C:
	cmp r9, #0x40
	ldreq r0, [r10, #0x0]
	add r7, r7, #0x1
	ldreqb r0, [r0, #0x4]
	streq r0, [sp, #0xc]
	ldrne r0, [r10, #0x0]
	ldrneb r0, [r0, #0x5]
	strne r0, [sp, #0xc]
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020BA068
	add r1, sp, #0xc
	mov r0, #0x14
	mov r2, #0x1
	bl FUN_020BB1C0
_020BA068:
	add r0, r10, #0x12c
	str r0, [r10, #0xb4]
	ldr r0, [r10, #0x24]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x92]
	moveq r8, #0x0
	cmp r8, #0x1
	bne _020BA0BC
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x24]
	blx r1
	ldr r0, [r10, #0x24]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x92]
	ldr r0, [r10, #0x8]
	moveq r8, #0x0
	and r0, r0, #0x40
	b _020BA0C0
_020BA0BC:
	mov r0, #0x0
_020BA0C0:
	cmp r0, #0x0
	bne _020BA2CC
	ldr r0, [r10, #0x4]
	ldr r1, [r0, #0x34]
	cmp r1, #0x0
	beq _020BA0F4
	mov r0, #0x58
	mla r6, r4, r0, r1
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x80
	moveq r0, #0x1
	movne r0, #0x0
	b _020BA0FC
_020BA0F4:
	add r6, r10, #0x12c
	mov r0, #0x0
_020BA0FC:
	cmp r0, #0x0
	bne _020BA2C8
	mov r0, #0x0
	str r0, [r6, #0x0]
	ldr r0, [r10, #0x4]
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	beq _020BA134
	ldr r3, [r0, #0x14]
	mov r0, r6
	mov r2, r4
	blx r3
	cmp r0, #0x0
	bne _020BA2C8
_020BA134:
	ldr r2, [r10, #0xd4]
	ldrh r0, [r2, #0x6]
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r4, r0
	ldr r1, [r0, #0x4]
	ldrh r0, [r2, r1]
	add r4, r2, r1
	add r5, r4, #0x4
	ands r0, r0, #0x1
	ldrne r0, [r6, #0x0]
	orrne r0, r0, #0x4
	strne r0, [r6, #0x0]
	bne _020BA188
	ldr r0, [r5, #0x0]
	str r0, [r6, #0x4c]
	ldr r0, [r5, #0x4]
	str r0, [r6, #0x50]
	ldr r0, [r5, #0x8]
	add r5, r5, #0xc
	str r0, [r6, #0x54]
_020BA188:
	ldrh r1, [r4, #0x0]
	ands r0, r1, #0x2
	ldrne r0, [r6, #0x0]
	orrne r0, r0, #0x2
	strne r0, [r6, #0x0]
	bne _020BA2B0
	ands r0, r1, #0x8
	beq _020BA264
	and r1, r1, #0xf0
	mov r11, r1, asr #0x4
	ldrsh r1, [r5, #0x0]
	add r0, r6, #0x28
	str r1, [sp, #0x0]
	ldrsh r1, [r5, #0x2]
	str r1, [sp, #0x4]
	bl MI_Zero36B
	ldrh r0, [r4, #0x0]
	add r1, r6, r11, lsl #0x2
	add r5, r5, #0x4
	ands r0, r0, #0x100
	movne r0, #0x1000
	rsbne r2, r0, #0x0
	moveq r2, #0x1000
	str r2, [r1, #0x28]
	ldr r0, _020BA3B4 ; =UNK_020FF9F0
	ldr r1, _020BA3B8 ; =UNK_020FF9F0 + 1
	ldrb r0, [r0, r11, lsl #0x2]
	add r2, r6, r0, lsl #0x2
	ldr r0, [sp, #0x0]
	str r0, [r2, #0x28]
	ldrb r0, [r1, r11, lsl #0x2]
	add r1, r6, r0, lsl #0x2
	ldr r0, [sp, #0x4]
	str r0, [r1, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x200
	ldrne r0, [sp, #0x4]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x4]
	ldr r0, _020BA3BC ; =UNK_020FF9F0 + 2
	ldrb r0, [r0, r11, lsl #0x2]
	add r1, r6, r0, lsl #0x2
	ldr r0, [sp, #0x4]
	str r0, [r1, #0x28]
	ldrh r0, [r4, #0x0]
	ands r0, r0, #0x400
	ldrne r0, [sp, #0x0]
	rsbne r0, r0, #0x0
	strne r0, [sp, #0x0]
	ldr r0, _020BA3C0 ; =UNK_020FF9F0 + 3
	ldrb r0, [r0, r11, lsl #0x2]
	add r1, r6, r0, lsl #0x2
	ldr r0, [sp, #0x0]
	str r0, [r1, #0x28]
	b _020BA2B0
_020BA264:
	ldrsh r0, [r4, #0x2]
	str r0, [r6, #0x28]
	ldrsh r0, [r5, #0x0]
	str r0, [r6, #0x2c]
	ldrsh r0, [r5, #0x2]
	str r0, [r6, #0x30]
	ldrsh r0, [r5, #0x4]
	str r0, [r6, #0x34]
	ldrsh r0, [r5, #0x6]
	str r0, [r6, #0x38]
	ldrsh r0, [r5, #0x8]
	str r0, [r6, #0x3c]
	ldrsh r0, [r5, #0xa]
	str r0, [r6, #0x40]
	ldrsh r0, [r5, #0xc]
	str r0, [r6, #0x44]
	ldrsh r0, [r5, #0xe]
	add r5, r5, #0x10
	str r0, [r6, #0x48]
_020BA2B0:
	ldrh r3, [r4, #0x0]
	ldr r2, [r10, #0x0]
	ldr r4, [r10, #0xe8]
	mov r0, r6
	mov r1, r5
	blx r4
_020BA2C8:
	str r6, [r10, #0xb4]
_020BA2CC:
	cmp r8, #0x2
	bne _020BA308
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x24]
	blx r1
	ldr r0, [r10, #0x24]
	cmp r0, #0x0
	ldrneb r8, [r10, #0x92]
	ldr r0, [r10, #0x8]
	moveq r8, #0x0
	and r0, r0, #0x40
	b _020BA30C
_020BA308:
	mov r0, #0x0
_020BA30C:
	cmp r0, #0x0
	bne _020BA32C
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020BA32C
	ldr r0, [r10, #0xb4]
	ldr r1, [r10, #0xec]
	blx r1
_020BA32C:
	mov r0, #0x0
	str r0, [r10, #0xb4]
	cmp r8, #0x3
	bne _020BA35C
	ldr r1, [r10, #0x8]
	mov r0, r10
	bic r1, r1, #0x40
	str r1, [r10, #0x8]
	ldr r1, [r10, #0x24]
	blx r1
	ldr r0, [r10, #0x8]
	and r0, r0, #0x40
_020BA35C:
	cmp r9, #0x20
	beq _020BA36C
	cmp r9, #0x60
	bne _020BA3A0
_020BA36C:
	cmp r0, #0x0
	add r7, r7, #0x1
	bne _020BA3A0
	ldr r0, [r10, #0x8]
	ands r0, r0, #0x100
	bne _020BA3A0
	ldr r0, [r10, #0x0]
	add r1, sp, #0x10
	ldrb r3, [r0, #0x4]
	mov r0, #0x13
	mov r2, #0x1
	str r3, [sp, #0x10]
	bl FUN_020BB1C0
_020BA3A0:
	ldr r0, [r10, #0x0]
	add r0, r0, r7
	str r0, [r10, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020BA3B4: .word UNK_020FF9F0
_020BA3B8: .word UNK_020FF9F0 + 1
_020BA3BC: .word UNK_020FF9F0 + 2
_020BA3C0: .word UNK_020FF9F0 + 3
	arm_func_end FUN_020B9F84

	; NNSi_G3dFuncSbc_SHP
	arm_func_start FUN_020BA3C4
FUN_020BA3C4: ; 0x020BA3C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r3, [r4, #0x8]
	ands r2, r3, #0x200
	bne _020BA420
	ands r2, r3, #0x1
	beq _020BA420
	ands r2, r3, #0x2
	bne _020BA420
	ldr r5, [r4, #0xdc]
	ldr r3, [r4, #0x0]
	ldrh r2, [r5, #0x6]
	ldrb r3, [r3, #0x1]
	ldr ip, _020BA434 ; =UNK_02106650
	ldrh lr, [r5, r2]
	add r2, r5, r2
	mla r2, lr, r3, r2
	ldr r2, [r2, #0x4]
	ldrh lr, [r5, r2]
	add r2, r5, r2
	ldr r12, [r12, lr, lsl #0x2]
	blx r12
_020BA420:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BA434: .word UNK_02106650
	arm_func_end FUN_020BA3C4

	; _end
	arm_func_start FUN_020BA438
FUN_020BA438: ; 0x020BA438
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x20]
	mov r5, r2
	cmp r0, #0x0
	ldrneb r4, [r6, #0x91]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020BA490
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x20]
	blx r1
	ldr r0, [r6, #0x20]
	cmp r0, #0x0
	ldrneb r4, [r6, #0x91]
	ldr r0, [r6, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020BA494
_020BA490:
	mov r0, #0x0
_020BA494:
	cmp r0, #0x0
	bne _020BA4B8
	ldr r0, [r6, #0x8]
	ands r0, r0, #0x100
	bne _020BA4B8
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	add r0, r5, r0
	bl FUN_020BB2B0
_020BA4B8:
	cmp r4, #0x2
	bne _020BA4E8
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x20]
	blx r1
	ldr r0, [r6, #0x20]
	cmp r0, #0x0
	ldrneb r4, [r6, #0x91]
	moveq r4, #0x0
_020BA4E8:
	cmp r4, #0x3
	ldmneia sp!, {r4-r6,pc}
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x20]
	blx r1
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020BA438

	; NNSi_G3dFuncSbc_MAT
	arm_func_start FUN_020BA50C
FUN_020BA50C: ; 0x020BA50C
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldr r5, [r4, #0x8]
	ands r0, r5, #0x200
	bne _020BA578
	ldr r2, [r4, #0x0]
	ands r0, r5, #0x1
	ldrb r3, [r2, #0x1]
	bne _020BA544
	ands r0, r5, #0x8
	beq _020BA544
	ldrb r0, [r4, #0xad]
	cmp r3, r0
	beq _020BA578
_020BA544:
	ldr r6, [r4, #0xd8]
	ldr ip, _020BA588 ; =UNK_02106640
	ldrh r2, [r6, #0xa]
	add r5, r6, #0x4
	mov r0, r4
	ldrh lr, [r5, r2]
	add r2, r5, r2
	mla r2, lr, r3, r2
	ldr r2, [r2, #0x4]
	ldrh lr, [r6, r2]
	add r2, r6, r2
	ldr r12, [r12, lr, lsl #0x2]
	blx r12
_020BA578:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BA588: .word UNK_02106640
	arm_func_end FUN_020BA50C

	; NNSi_G3dFuncSbc_MAT_InternalDefault
	arm_func_start FUN_020BA58C
FUN_020BA58C: ; 0x020BA58C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x20
	mov r8, r0
	mov r6, r3
	strb r6, [r8, #0xad]
	ldr r3, [r8, #0x8]
	add r0, r8, #0xf4
	orr r3, r3, #0x8
	str r3, [r8, #0x8]
	str r0, [r8, #0xb0]
	ldr r0, [r8, #0x1c]
	mov r4, r1
	cmp r0, #0x0
	ldrneb r5, [r8, #0x90]
	mov r7, r2
	moveq r5, #0x0
	cmp r5, #0x1
	bne _020BA608
	ldr r1, [r8, #0x8]
	mov r0, r8
	bic r1, r1, #0x40
	str r1, [r8, #0x8]
	ldr r1, [r8, #0x1c]
	blx r1
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	ldrneb r5, [r8, #0x90]
	ldr r0, [r8, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BA60C
_020BA608:
	mov r0, #0x0
_020BA60C:
	cmp r0, #0x0
	bne _020BA8C0
	ldr r0, [r8, #0x4]
	ldr r0, [r0, #0x38]
	cmp r0, #0x0
	beq _020BA638
	ldr r1, [r8, #0x8]
	ands r1, r1, #0x80
	moveq r1, #0x38
	mlaeq r4, r6, r1, r0
	beq _020BA8BC
_020BA638:
	cmp r4, #0x20
	beq _020BA648
	cmp r4, #0x40
	bne _020BA684
_020BA648:
	mov r1, r6, lsr #0x5
	add r1, r8, r1, lsl #0x2
	and r2, r6, #0x1f
	mov r3, #0x1
	mov r2, r3, lsl r2
	ldr r1, [r1, #0xbc]
	ands r1, r2, r1
	beq _020BA684
	cmp r0, #0x0
	movne r1, #0x38
	mlane r4, r6, r1, r0
	ldreq r1, _020BA9D8 ; =UNK_021CEF80
	moveq r0, #0x38
	mlaeq r4, r6, r0, r1
	b _020BA8BC
_020BA684:
	cmp r0, #0x0
	beq _020BA6BC
	add r4, r8, #0xbc
	mov r3, r6, lsr #0x5
	ldr r2, [r4, r3, lsl #0x2]
	and r0, r6, #0x1f
	mov r1, #0x1
	orr r0, r2, r1, lsl r0
	str r0, [r4, r3, lsl #0x2]
	ldr r1, [r8, #0x4]
	mov r0, #0x38
	ldr r1, [r1, #0x38]
	mla r4, r6, r0, r1
	b _020BA6F0
_020BA6BC:
	cmp r4, #0x40
	addne r4, r8, #0xf4
	bne _020BA6F0
	add lr, r8, #0xbc
	mov r12, r6, lsr #0x5
	ldr r1, _020BA9D8 ; =UNK_021CEF80
	ldr r4, [lr, r12, lsl #0x2]
	mov r0, #0x38
	and r2, r6, #0x1f
	mov r3, #0x1
	orr r2, r4, r3, lsl r2
	mla r4, r6, r0, r1
	str r2, [lr, r12, lsl #0x2]
_020BA6F0:
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r3, [r8, #0xd8]
	ldrh r0, [r3, #0xa]
	add r2, r3, #0x4
	ldrh r1, [r2, r0]
	add r0, r2, r0
	mla r0, r1, r6, r0
	ldr r0, [r0, #0x4]
	ldr r1, _020BA9DC ; =UNK_021CED18
	add r0, r3, r0
	ldrh r0, [r0, #0x1e]
	ands r0, r0, #0x20
	ldrne r0, [r4, #0x0]
	orrne r0, r0, #0x20
	strne r0, [r4, #0x0]
	ldrh r2, [r7, #0x1e]
	ldr r0, _020BA9E0 ; =UNK_020FF9D0
	ldr r12, [r1, #0x94]
	mov r2, r2, asr #0x6
	and r2, r2, #0x7
	ldr lr, [r0, r2, lsl #0x2]
	ldr r2, [r7, #0x4]
	mvn r3, lr
	and r3, r12, r3
	and r2, r2, lr
	orr r2, r3, r2
	str r2, [r4, #0x4]
	ldrh r12, [r7, #0x1e]
	ldr r3, [r1, #0x98]
	ldr r2, [r7, #0x8]
	mov r12, r12, asr #0x9
	and r12, r12, #0x7
	ldr r12, [r0, r12, lsl #0x2]
	mvn r0, r12
	and r3, r3, r0
	and r0, r2, r12
	orr r0, r3, r0
	str r0, [r4, #0x8]
	ldr r3, [r7, #0x10]
	ldr r0, [r7, #0xc]
	ldr r2, [r1, #0x9c]
	mvn r1, r3
	and r1, r2, r1
	and r0, r0, r3
	orr r0, r1, r0
	str r0, [r4, #0xc]
	ldr r0, [r7, #0x14]
	str r0, [r4, #0x10]
	ldrh r0, [r7, #0x1c]
	str r0, [r4, #0x14]
	ldrh r1, [r7, #0x1e]
	ands r0, r1, #0x1
	beq _020BA850
	ands r1, r1, #0x2
	ldrne r1, [r4, #0x0]
	add r0, r7, #0x2c
	orrne r1, r1, #0x1
	strne r1, [r4, #0x0]
	bne _020BA7F4
	ldr r1, [r0, #0x0]
	str r1, [r4, #0x18]
	ldr r1, [r0, #0x4]
	add r0, r0, #0x8
	str r1, [r4, #0x1c]
_020BA7F4:
	ldrh r1, [r7, #0x1e]
	ands r1, r1, #0x4
	ldrne r1, [r4, #0x0]
	orrne r1, r1, #0x2
	strne r1, [r4, #0x0]
	bne _020BA820
	ldrsh r1, [r0, #0x0]
	strh r1, [r4, #0x20]
	ldrsh r1, [r0, #0x2]
	add r0, r0, #0x4
	strh r1, [r4, #0x22]
_020BA820:
	ldrh r1, [r7, #0x1e]
	ands r1, r1, #0x8
	ldreq r1, [r0, #0x0]
	streq r1, [r4, #0x24]
	ldreq r0, [r0, #0x4]
	streq r0, [r4, #0x28]
	ldrne r0, [r4, #0x0]
	orrne r0, r0, #0x4
	strne r0, [r4, #0x0]
	ldr r0, [r4, #0x0]
	orr r0, r0, #0x8
	str r0, [r4, #0x0]
_020BA850:
	ldr r0, [r8, #0x4]
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _020BA890
	mov r2, r6, lsr #0x5
	add r2, r0, r2, lsl #0x2
	and r3, r6, #0x1f
	mov r12, #0x1
	mov r3, r12, lsl r3
	ldr r2, [r2, #0x3c]
	ands r2, r3, r2
	beq _020BA890
	ldr r3, [r0, #0xc]
	mov r0, r4
	mov r2, r6
	blx r3
_020BA890:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x18
	beq _020BA8BC
	ldrh r0, [r7, #0x20]
	strh r0, [r4, #0x2c]
	ldrh r0, [r7, #0x22]
	strh r0, [r4, #0x2e]
	ldr r0, [r7, #0x24]
	str r0, [r4, #0x30]
	ldr r0, [r7, #0x28]
	str r0, [r4, #0x34]
_020BA8BC:
	str r4, [r8, #0xb0]
_020BA8C0:
	cmp r5, #0x2
	bne _020BA8FC
	ldr r1, [r8, #0x8]
	mov r0, r8
	bic r1, r1, #0x40
	str r1, [r8, #0x8]
	ldr r1, [r8, #0x1c]
	blx r1
	ldr r0, [r8, #0x1c]
	cmp r0, #0x0
	ldrneb r5, [r8, #0x90]
	ldr r0, [r8, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BA900
_020BA8FC:
	mov r0, #0x0
_020BA900:
	cmp r0, #0x0
	bne _020BA9AC
	ldr r4, [r8, #0xb0]
	ldr r1, [r4, #0xc]
	ands r0, r1, #0x1f0000
	beq _020BA9A0
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x20
	bicne r0, r1, #0x1f0000
	strne r0, [r4, #0xc]
	ldr r0, [r8, #0x8]
	bic r0, r0, #0x2
	str r0, [r8, #0x8]
	ldr r0, [r8, #0x8]
	ands r0, r0, #0x100
	bne _020BA9AC
	ldr r0, _020BA9E4 ; =0x00293130
	ldr r3, _020BA9E8 ; =0x00002B2A
	str r0, [sp, #0x0]
	ldr r2, [r4, #0x4]
	add r1, sp, #0x4
	str r2, [sp, #0x4]
	ldr r6, [r4, #0x8]
	mov r2, #0x6
	str r6, [sp, #0x8]
	ldr r6, [r4, #0xc]
	str r6, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r3, [r4, #0x10]
	str r3, [sp, #0x14]
	ldr r3, [r4, #0x14]
	str r3, [sp, #0x18]
	bl FUN_020BB1C0
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x18
	beq _020BA9AC
	ldr r1, [r8, #0xf0]
	mov r0, r4
	blx r1
	b _020BA9AC
_020BA9A0:
	ldr r0, [r8, #0x8]
	orr r0, r0, #0x2
	str r0, [r8, #0x8]
_020BA9AC:
	cmp r5, #0x3
	addne sp, sp, #0x20
	ldmneia sp!, {r4-r8,pc}
	ldr r1, [r8, #0x8]
	mov r0, r8
	bic r1, r1, #0x40
	str r1, [r8, #0x8]
	ldr r1, [r8, #0x1c]
	blx r1
	add sp, sp, #0x20
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020BA9D8: .word UNK_021CEF80
_020BA9DC: .word UNK_021CED18
_020BA9E0: .word UNK_020FF9D0
_020BA9E4: .word 0x00293130
_020BA9E8: .word 0x00002B2A
	arm_func_end FUN_020BA58C

	; _end
	arm_func_start FUN_020BA9EC
FUN_020BA9EC: ; 0x020BA9EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r1, [r5, #0x8]
	ands r0, r1, #0x200
	bne _020BAAAC
	ands r0, r1, #0x1
	beq _020BAAAC
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x8f]
	moveq r4, #0x0
	cmp r4, #0x1
	bne _020BAA58
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x18]
	blx r1
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	ldrneb r4, [r5, #0x8f]
	ldr r0, [r5, #0x8]
	moveq r4, #0x0
	and r0, r0, #0x40
	b _020BAA5C
_020BAA58:
	mov r0, #0x0
_020BAA5C:
	cmp r0, #0x0
	bne _020BAA8C
	ldr r0, [r5, #0x0]
	ldrb r0, [r0, #0x1]
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x8]
	ands r0, r0, #0x100
	bne _020BAA8C
	add r1, sp, #0x0
	mov r0, #0x14
	mov r2, #0x1
	bl FUN_020BB1C0
_020BAA8C:
	cmp r4, #0x3
	bne _020BAAAC
	ldr r1, [r5, #0x8]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r5, #0x8]
	ldr r1, [r5, #0x18]
	blx r1
_020BAAAC:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x2
	str r0, [r5, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020BA9EC

	; _end
	arm_func_start FUN_020BAAC0
FUN_020BAAC0: ; 0x020BAAC0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x8]
	ands r0, r0, #0x200
	bne _020BAC38
	ldr r1, [r6, #0x0]
	add r0, r6, #0x184
	ldrb r1, [r1, #0x1]
	strb r1, [r6, #0xac]
	ldr r1, [r6, #0x8]
	ldrb r4, [r6, #0xac]
	orr r1, r1, #0x4
	str r1, [r6, #0x8]
	str r0, [r6, #0xb8]
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	ldrneb r5, [r6, #0x8e]
	moveq r5, #0x0
	cmp r5, #0x1
	bne _020BAB44
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x14]
	blx r1
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	ldrneb r5, [r6, #0x8e]
	ldr r0, [r6, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BAB48
_020BAB44:
	mov r0, #0x0
_020BAB48:
	cmp r0, #0x0
	bne _020BABAC
	ldr r12, [r6, #0x4]
	ldr r1, [r12, #0x18]
	cmp r1, #0x0
	beq _020BAB98
	mov r0, r4, lsr #0x5
	add r0, r12, r0, lsl #0x2
	and r2, r4, #0x1f
	mov r3, #0x1
	mov r2, r3, lsl r2
	ldr r0, [r0, #0x4c]
	ands r0, r2, r0
	beq _020BAB98
	ldr r0, [r6, #0xb8]
	ldr r3, [r12, #0x1c]
	mov r2, r4
	blx r3
	cmp r0, #0x0
	bne _020BABAC
_020BAB98:
	ldr r1, [r6, #0x0]
	ldr r0, [r6, #0xb8]
	ldrb r1, [r1, #0x2]
	and r1, r1, #0x1
	str r1, [r0, #0x0]
_020BABAC:
	cmp r5, #0x2
	bne _020BABE8
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x14]
	blx r1
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	ldrneb r5, [r6, #0x8e]
	ldr r0, [r6, #0x8]
	moveq r5, #0x0
	and r0, r0, #0x40
	b _020BABEC
_020BABE8:
	mov r0, #0x0
_020BABEC:
	cmp r0, #0x0
	bne _020BAC18
	ldr r0, [r6, #0xb8]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldrne r0, [r6, #0x8]
	orrne r0, r0, #0x1
	strne r0, [r6, #0x8]
	ldreq r0, [r6, #0x8]
	biceq r0, r0, #0x1
	streq r0, [r6, #0x8]
_020BAC18:
	cmp r5, #0x3
	bne _020BAC38
	ldr r1, [r6, #0x8]
	mov r0, r6
	bic r1, r1, #0x40
	str r1, [r6, #0x8]
	ldr r1, [r6, #0x14]
	blx r1
_020BAC38:
	ldr r0, [r6, #0x0]
	add r0, r0, #0x3
	str r0, [r6, #0x0]
	ldmia sp!, {r4-r6,pc}
	arm_func_end FUN_020BAAC0

	; _end
	arm_func_start FUN_020BAC48
FUN_020BAC48: ; 0x020BAC48
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	beq _020BAC60
	blx r1
_020BAC60:
	ldr r0, [r4, #0x8]
	orr r0, r0, #0x20
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020BAC48

	; _end
	arm_func_start FUN_020BAC70
FUN_020BAC70: ; 0x020BAC70
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	beq _020BAC88
	blx r1
_020BAC88:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	ldmia sp!, {r4,pc}
	arm_func_end FUN_020BAC70

	; NNS_G3dDraw
	arm_func_start FUN_020BAC98
FUN_020BAC98: ; 0x020BAC98
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x188
	mov r4, r0
	ldr r0, [r4, #0x0]
	and r0, r0, #0x10
	cmp r0, #0x10
	bne _020BAD2C
	add r1, r4, #0x3c
	mov r0, #0x0
	mov r2, #0x8
	bl MIi_CpuClear32
	add r1, r4, #0x44
	mov r0, #0x0
	mov r2, #0x8
	bl MIi_CpuClear32
	add r1, r4, #0x4c
	mov r0, #0x0
	mov r2, #0x8
	bl MIi_CpuClear32
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020BACF8
	add r0, r4, #0x3c
	bl FUN_020BAD74
_020BACF8:
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	beq _020BAD0C
	add r0, r4, #0x44
	bl FUN_020BAD74
_020BAD0C:
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _020BAD20
	add r0, r4, #0x4c
	bl FUN_020BAD74
_020BAD20:
	ldr r0, [r4, #0x0]
	bic r0, r0, #0x10
	str r0, [r4, #0x0]
_020BAD2C:
	ldr r2, _020BAD70 ; =UNK_021CEF7C
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	beq _020BAD4C
	mov r1, r4
	bl FUN_020BADE4
	add sp, sp, #0x188
	ldmia sp!, {r4,pc}
_020BAD4C:
	add r0, sp, #0x0
	mov r1, r4
	str r0, [r2, #0x0]
	bl FUN_020BADE4
	ldr r0, _020BAD70 ; =UNK_021CEF7C
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x188
	ldmia sp!, {r4,pc}
	.balign 4
_020BAD70: .word UNK_021CEF7C
	arm_func_end FUN_020BAC98

	; _end
	arm_func_start FUN_020BAD74
FUN_020BAD74: ; 0x020BAD74
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	mov r3, #0x1
	mov r4, #0x0
_020BAD90:
	ldrb r2, [r1, #0x19]
	mov r5, r4
	cmp r2, #0x0
	ble _020BADD0
_020BADA0:
	add r2, r1, r5, lsl #0x1
	ldrh r2, [r2, #0x1a]
	ands r2, r2, #0x100
	movne lr, r5, asr #0x5
	andne r2, r5, #0x1f
	ldrne r12, [r0, lr, lsl #0x2]
	add r5, r5, #0x1
	orrne r2, r12, r3, lsl r2
	strne r2, [r0, lr, lsl #0x2]
	ldrb r2, [r1, #0x19]
	cmp r5, r2
	blt _020BADA0
_020BADD0:
	ldr r1, [r1, #0x10]
	cmp r1, #0x0
	bne _020BAD90
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	arm_func_end FUN_020BAD74

	; G3dDrawInternal_
	arm_func_start FUN_020BADE4
FUN_020BADE4: ; 0x020BADE4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	mov r1, r5
	mov r0, #0x0
	mov r2, #0x188
	bl MIi_CpuClearFast
	mov r0, #0x1
	str r0, [r5, #0xc4]
	str r0, [r5, #0x8]
	ldr r0, [r4, #0x30]
	ldr r2, _020BAF60 ; =UNK_02106614
	cmp r0, #0x0
	strne r0, [r5, #0x0]
	ldreq r1, [r4, #0x4]
	ldreq r0, [r1, #0x4]
	addeq r0, r1, r0
	streq r0, [r5, #0x0]
	str r4, [r5, #0x4]
	ldr r0, [r4, #0x4]
	ldr r1, _020BAF64 ; =UNK_02106608
	add r0, r0, #0x40
	str r0, [r5, #0xd4]
	ldr r12, [r4, #0x4]
	ldr r0, _020BAF68 ; =UNK_02106620
	ldr r3, [r12, #0x8]
	add r3, r12, r3
	str r3, [r5, #0xd8]
	ldr r12, [r4, #0x4]
	ldr r3, [r12, #0xc]
	add r3, r12, r3
	str r3, [r5, #0xdc]
	ldr r3, [r4, #0x4]
	ldrb r3, [r3, #0x15]
	ldr r2, [r2, r3, lsl #0x2]
	str r2, [r5, #0xe8]
	ldr r2, [r4, #0x4]
	ldrb r2, [r2, #0x15]
	ldr r1, [r1, r2, lsl #0x2]
	str r1, [r5, #0xec]
	ldr r1, [r4, #0x4]
	ldrb r1, [r1, #0x16]
	ldr r0, [r0, r1, lsl #0x2]
	str r0, [r5, #0xf0]
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x1c]
	str r0, [r5, #0xe0]
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x20]
	str r0, [r5, #0xe4]
	ldr r1, [r4, #0x20]
	cmp r1, #0x0
	beq _020BAEE0
	ldrb r0, [r4, #0x24]
	cmp r0, #0x20
	bhs _020BAEE0
	add r0, r5, r0, lsl #0x2
	str r1, [r0, #0xc]
	ldrb r0, [r4, #0x24]
	ldrb r1, [r4, #0x25]
	add r0, r5, r0
	strb r1, [r0, #0x8c]
_020BAEE0:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x1
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x80
	strne r0, [r5, #0x8]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x2
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x100
	strne r0, [r5, #0x8]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x4
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x200
	strne r0, [r5, #0x8]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x8
	ldrne r0, [r5, #0x8]
	orrne r0, r0, #0x400
	strne r0, [r5, #0x8]
	ldr r1, [r4, #0x28]
	cmp r1, #0x0
	beq _020BAF44
	mov r0, r5
	blx r1
_020BAF44:
	mov r0, r5
	bl FUN_020BAF6C
	ldr r0, [r4, #0x0]
	bic r0, r0, #0x1
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020BAF60: .word UNK_02106614
_020BAF64: .word UNK_02106608
_020BAF68: .word UNK_02106620
	arm_func_end FUN_020BADE4

	; G3dDrawInternal_Loop_
	arm_func_start FUN_020BAF6C
FUN_020BAF6C: ; 0x020BAF6C
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	ldr r6, _020BAFB4 ; =UNK_02106730
	add r4, r5, #0x8
_020BAF7C:
	ldr r1, [r4, #0x0]
	mov r0, r5
	bic r1, r1, #0x40
	str r1, [r4, #0x0]
	ldr r1, [r5, #0x0]
	ldrb r3, [r1, #0x0]
	and r1, r3, #0x1f
	ldr r2, [r6, r1, lsl #0x2]
	and r1, r3, #0xe0
	blx r2
	ldr r0, [r5, #0x8]
	ands r0, r0, #0x20
	beq _020BAF7C
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020BAFB4: .word UNK_02106730
	arm_func_end FUN_020BAF6C

