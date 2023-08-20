	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_0224CA64
ov11_0224CA64: ; 0x0224CA64
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x69
	mov r0, #5
	lsl r1, r1, #2
	bl AllocFromHeap
	add r4, r0, #0
	mov r2, #0x69
	mov r0, #0
	add r1, r4, #0
	lsl r2, r2, #2
	bl MIi_CpuClearFast
	mov r0, #0x65
	ldrb r1, [r5]
	lsl r0, r0, #2
	strb r1, [r4, r0]
	ldrb r1, [r5, #1]
	add r0, r0, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0224CA94
ov11_0224CA94: ; 0x0224CA94
	push {r4, r5, r6, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl ov11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	bne _0224CB2C
	sub r1, #0x8b
	ldrb r1, [r4, r1]
	mov r0, #1
	tst r0, r1
	beq _0224CAC0
	add r0, r5, #0
	bl ov11_0222FF74
	mov r1, #1
	tst r0, r1
	beq _0224CB2C
_0224CAC0:
	ldr r0, _0224CB30 ; =0x00000195
	ldr r1, _0224CB34 ; =ov11_0225E818
	ldrb r2, [r4, r0]
	sub r0, r0, #1
	ldrb r1, [r1, r2]
	str r1, [sp]
	mov r1, #5
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	ldrb r0, [r4, r0]
	str r0, [sp, #0xc]
	add r0, r5, #0
	str r6, [sp, #0x10]
	bl ov11_02230078
	str r0, [sp, #0x1c]
	add r0, r5, #0
	bl ov11_022300CC
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x18]
	mov r0, #1
	str r0, [sp, #0x14]
	add r0, sp, #0
	bl ov08_02229918
	add r1, r4, #0
	add r1, #0x88
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0x64
	bl ov08_0222A00C
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #2
	bl ov08_0222A018
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0
	bl ov08_02229FE4
	add r4, #0x88
	ldr r0, [r4]
	mov r1, #0
	bl ov08_0222A008
_0224CB2C:
	add sp, #0x28
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224CB30: .word 0x00000195
_0224CB34: .word ov11_0225E818

	thumb_func_start ov11_0224CB38
ov11_0224CB38: ; 0x0224CB38
	push {r3, lr}
	add r2, r1, #0
	add r2, #0x94
	ldrb r2, [r2]
	cmp r2, #0
	beq _0224CB4C
	lsl r3, r2, #2
	ldr r2, _0224CB50 ; =ov11_0225E70C
	ldr r2, [r2, r3]
	blx r2
_0224CB4C:
	pop {r3, pc}
	nop
_0224CB50: .word ov11_0225E70C

	thumb_func_start ov11_0224CB54
ov11_0224CB54: ; 0x0224CB54
	push {r4, lr}
	add r4, r1, #0
	cmp r2, #2
	beq _0224CB64
	add r0, r4, #0
	add r0, #0x28
	bl ov11_02257030
_0224CB64:
	add r0, r4, #0
	bl ov11_0225468C
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_0224CB74
ov11_0224CB74: ; 0x0224CB74
	bx lr
	.align 2, 0

	thumb_func_start ov11_0224CB78
ov11_0224CB78: ; 0x0224CB78
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_0224D550
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #1
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0224CB98
ov11_0224CB98: ; 0x0224CB98
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224D574
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CBAC
ov11_0224CBAC: ; 0x0224CBAC
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224D738
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CBC0
ov11_0224CBC0: ; 0x0224CBC0
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224D87C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CBD4
ov11_0224CBD4: ; 0x0224CBD4
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224DA2C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CBE8
ov11_0224CBE8: ; 0x0224CBE8
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224DAE8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CBFC
ov11_0224CBFC: ; 0x0224CBFC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x20]
	bl sub_02007534
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #7
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0224CC20
ov11_0224CC20: ; 0x0224CC20
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224DB4C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CC34
ov11_0224CC34: ; 0x0224CC34
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224DCE4
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CC48
ov11_0224CC48: ; 0x0224CC48
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224DD44
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CC58
ov11_0224CC58: ; 0x0224CC58
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224DD8C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CC6C
ov11_0224CC6C: ; 0x0224CC6C
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224DE50
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CC80
ov11_0224CC80: ; 0x0224CC80
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224DF18
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CC90
ov11_0224CC90: ; 0x0224CC90
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r4, #0
	add r6, #0x94
	add r1, r6, #0
	add r1, #0x29
	ldrb r1, [r1]
	add r5, r0, #0
	bl ov11_022312B8
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0224DF60
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224CCB8
ov11_0224CCB8: ; 0x0224CCB8
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E034
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CCCC
ov11_0224CCCC: ; 0x0224CCCC
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E0A4
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CCE0
ov11_0224CCE0: ; 0x0224CCE0
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E130
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CCF4
ov11_0224CCF4: ; 0x0224CCF4
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E1DC
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CD08
ov11_0224CD08: ; 0x0224CD08
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E248
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CD1C
ov11_0224CD1C: ; 0x0224CD1C
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E28C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CD30
ov11_0224CD30: ; 0x0224CD30
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E2F4
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CD44
ov11_0224CD44: ; 0x0224CD44
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E344
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CD58
ov11_0224CD58: ; 0x0224CD58
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x20]
	mov r1, #6
	bl sub_0200782C
	cmp r0, #1
	bne _0224CD7A
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x17
	bl ov11_022567B8
	b _0224CD82
_0224CD7A:
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_0224E3E0
_0224CD82:
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0224CD8C
ov11_0224CD8C: ; 0x0224CD8C
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E410
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CDA0
ov11_0224CDA0: ; 0x0224CDA0
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E49C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CDB4
ov11_0224CDB4: ; 0x0224CDB4
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E510
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CDC8
ov11_0224CDC8: ; 0x0224CDC8
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E5F8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CDDC
ov11_0224CDDC: ; 0x0224CDDC
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224E628
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CDEC
ov11_0224CDEC: ; 0x0224CDEC
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E65C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE00
ov11_0224CE00: ; 0x0224CE00
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E6FC
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE14
ov11_0224CE14: ; 0x0224CE14
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E734
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE28
ov11_0224CE28: ; 0x0224CE28
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E790
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE3C
ov11_0224CE3C: ; 0x0224CE3C
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E7E8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE50
ov11_0224CE50: ; 0x0224CE50
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224E840
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE60
ov11_0224CE60: ; 0x0224CE60
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E894
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE74
ov11_0224CE74: ; 0x0224CE74
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224E8EC
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE84
ov11_0224CE84: ; 0x0224CE84
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E924
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CE98
ov11_0224CE98: ; 0x0224CE98
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224E9C0
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224CEAC
ov11_0224CEAC: ; 0x0224CEAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	mov r2, #0x65
	add r6, #0x94
	lsl r2, r2, #2
	str r1, [sp, #4]
	ldrb r1, [r1, r2]
	ldrb r2, [r6, #1]
	str r0, [sp]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	bl ov11_02230014
	add r7, r0, #0
	mov r0, #2
	ldr r1, [r6, #0x1c]
	lsl r0, r0, #0x14
	tst r0, r1
	bne _0224CF14
	add r0, r6, #0
	add r5, r6, #0
	str r0, [sp, #8]
	add r0, #0x16
	mov r4, #0
	add r5, #0xe
	str r0, [sp, #8]
_0224CEE2:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldrb r1, [r6, #1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	tst r0, r1
	bne _0224CF0C
	add r1, r4, #0
	add r0, r7, #0
	add r1, #0x36
	add r2, r5, #0
	bl SetMonData
	ldr r2, [sp, #8]
	add r1, r4, #0
	add r0, r7, #0
	add r1, #0x3a
	add r2, r2, r4
	bl SetMonData
_0224CF0C:
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _0224CEE2
_0224CF14:
	ldrb r0, [r6, #1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bl MaskOfFlagNo
	ldr r1, [r6, #8]
	tst r0, r1
	bne _0224CF30
	add r2, r6, #0
	add r0, r7, #0
	mov r1, #6
	add r2, #0xc
	bl SetMonData
_0224CF30:
	add r0, r7, #0
	mov r1, #0xa2
	add r2, r6, #2
	bl SetMonData
	add r0, r7, #0
	mov r1, #0x9f
	add r2, r6, #4
	bl SetMonData
	mov r2, #0x65
	ldr r1, [sp, #4]
	lsl r2, r2, #2
	ldrb r1, [r1, r2]
	ldrb r2, [r6]
	ldr r0, [sp]
	bl ov11_022567B8
	ldr r0, [sp, #4]
	bl ov11_0224D548
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224CF60
ov11_0224CF60: ; 0x0224CF60
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_0222FF74
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_02230094
	ldr r2, _0224CFB0 ; =0x00000196
	ldrb r1, [r4, r2]
	cmp r1, #0
	bne _0224CF94
	mov r1, #8
	and r1, r6
	bne _0224CF8C
	cmp r1, #0
	bne _0224CF94
	sub r1, r2, #1
	ldrb r1, [r4, r1]
	cmp r1, #4
	beq _0224CF94
_0224CF8C:
	ldr r1, _0224CFB4 ; =0xFFFFF300
	mov r2, #0
	bl ov11_02259098
_0224CF94:
	mov r1, #0x65
	add r2, r4, #0
	lsl r1, r1, #2
	add r2, #0x94
	ldrb r1, [r4, r1]
	ldrb r2, [r2]
	add r0, r5, #0
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}
	nop
_0224CFB0: .word 0x00000196
_0224CFB4: .word 0xFFFFF300

	thumb_func_start ov11_0224CFB8
ov11_0224CFB8: ; 0x0224CFB8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x28
	bl ov11_02257238
	add r0, r4, #0
	bl ov11_0225468C
	mov r1, #0x65
	add r2, r4, #0
	lsl r1, r1, #2
	add r2, #0x94
	ldrb r1, [r4, r1]
	ldrb r2, [r2]
	add r0, r5, #0
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0224CFE8
ov11_0224CFE8: ; 0x0224CFE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r1, #0
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #0x65
	lsl r1, r1, #2
	add r4, r7, #0
	ldrb r1, [r7, r1]
	str r0, [sp]
	add r4, #0x94
	bl ov11_0222FFC8
	mov r5, #0
	str r0, [sp, #4]
	cmp r0, #0
	ble _0224D04A
_0224D00A:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r7, r1]
	ldr r0, [sp]
	add r2, r5, #0
	bl ov11_02230014
	ldrb r1, [r4, #1]
	add r6, r0, #0
	cmp r1, #0x68
	bne _0224D024
	mov r0, #0
	b _0224D02C
_0224D024:
	mov r1, #0xa
	mov r2, #0
	bl GetMonData
_0224D02C:
	ldrh r1, [r4, #2]
	cmp r1, #0xd7
	bne _0224D038
	bne _0224D042
	cmp r0, #0x2b
	beq _0224D042
_0224D038:
	add r0, r6, #0
	mov r1, #0x9f
	add r2, sp, #8
	bl SetMonData
_0224D042:
	ldr r0, [sp, #4]
	add r5, r5, #1
	cmp r5, r0
	blt _0224D00A
_0224D04A:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r7, r1]
	ldrb r2, [r4]
	ldr r0, [sp]
	bl ov11_022567B8
	add r0, r7, #0
	bl ov11_0224D548
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224D064
ov11_0224D064: ; 0x0224D064
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EA74
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D078
ov11_0224D078: ; 0x0224D078
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EAAC
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D08C
ov11_0224D08C: ; 0x0224D08C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x10]
	add r5, r1, #0
	ldr r0, _0224D180 ; =0x00000195
	add r4, r5, #0
	ldrb r1, [r5, r0]
	mov r0, #1
	add r4, #0x94
	tst r0, r1
	beq _0224D0A6
	mov r6, #2
	b _0224D0A8
_0224D0A6:
	mov r6, #0
_0224D0A8:
	ldrb r0, [r4, #5]
	lsl r3, r6, #0x18
	lsr r3, r3, #0x18
	str r0, [sp]
	ldrb r0, [r4, #1]
	str r0, [sp, #4]
	ldr r0, [r4, #8]
	str r0, [sp, #8]
	ldrh r1, [r4, #2]
	ldrb r2, [r4, #4]
	add r0, sp, #0x14
	bl sub_02068C00
	ldr r0, [r5, #0x20]
	bl sub_020081C0
	add r7, r0, #0
	add r3, sp, #0x14
	add r2, r7, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5, #0x20]
	bl sub_020080D0
	ldr r0, [sp, #0x10]
	bl ov11_02230130
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	bl ov11_022312DC
	add r3, r0, #0
	ldr r0, [r4, #8]
	mov r2, #5
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldrh r0, [r7, #6]
	str r0, [sp, #0xc]
	ldrh r0, [r7]
	ldrh r1, [r7, #2]
	bl sub_02012560
	ldr r0, [sp, #0x10]
	bl ov11_02230130
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrh r2, [r7]
	bl ov11_022312F0
	ldr r0, [sp, #0x10]
	bl ov11_02230130
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrh r2, [r7, #4]
	bl ov11_02231308
	ldr r0, [r4, #8]
	lsl r2, r6, #0x18
	str r0, [sp]
	ldrh r0, [r4, #2]
	ldrb r1, [r4, #4]
	ldrb r3, [r4, #1]
	lsr r2, r2, #0x18
	bl sub_02068E88
	add r6, r0, #0
	ldr r0, [sp, #0x10]
	bl ov11_02230130
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r2, r6, #0
	bl ov11_02231320
	ldr r0, _0224D180 ; =0x00000195
	mov r1, #1
	ldrb r0, [r5, r0]
	bl ov08_0222A6A4
	add r2, r0, #0
	ldr r0, [r5, #0x20]
	mov r1, #1
	add r2, r6, r2
	bl sub_02007558
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	ldr r0, [sp, #0x10]
	bl ov11_022567B8
	add r0, r5, #0
	bl ov11_0224D548
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0224D180: .word 0x00000195

	thumb_func_start ov11_0224D184
ov11_0224D184: ; 0x0224D184
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_02230FCC
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x2e
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0224D1A4
ov11_0224D1A4: ; 0x0224D1A4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	ldr r1, _0224D218 ; =0x00000196
	add r5, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _0224D200
	bl ov11_02230094
	mov r1, #0
	add r6, r0, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov11_02258820
	add r0, r6, #0
	mov r1, #0
	bl ov11_0225B77C
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	bl ov11_022302BC
	add r1, r0, #0
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0224D1EC
	add r0, r5, #0
	bl ov11_02231380
	bl ov11_02258184
_0224D1EC:
	add r0, r4, #0
	add r0, #0x28
	bl ov11_02257238
	add r0, r6, #0
	bl ov11_02258E30
	add r0, r4, #0
	bl ov11_0225468C
_0224D200:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x2f
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}
	nop
_0224D218: .word 0x00000196

	thumb_func_start ov11_0224D21C
ov11_0224D21C: ; 0x0224D21C
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EAEC
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D230
ov11_0224D230: ; 0x0224D230
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EB34
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D244
ov11_0224D244: ; 0x0224D244
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r6, r4, #0
	add r5, r0, #0
	add r6, #0x94
	bl ov11_02230270
	cmp r0, #0
	beq _0224D268
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0224EB6C
	b _0224D276
_0224D268:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x32
	bl ov11_022567B8
_0224D276:
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224D280
ov11_0224D280: ; 0x0224D280
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r6, r4, #0
	add r5, r0, #0
	add r6, #0x94
	bl ov11_02230270
	cmp r0, #0
	beq _0224D2A4
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov11_0224EBB8
	b _0224D2B2
_0224D2A4:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x33
	bl ov11_022567B8
_0224D2B2:
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224D2BC
ov11_0224D2BC: ; 0x0224D2BC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_02230078
	add r6, r0, #0
	add r0, r5, #0
	bl ov11_02230080
	add r7, r0, #0
	add r0, r5, #0
	bl ov11_022300CC
	add r2, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	bl ov11_0225C91C
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x34
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224D2F8
ov11_0224D2F8: ; 0x0224D2F8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_02230080
	bl ov11_0225C9A0
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x35
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0224D31C
ov11_0224D31C: ; 0x0224D31C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r5, #0
	add r4, #0x94
	ldrb r1, [r4, #1]
	add r6, r0, #0
	cmp r1, #0
	ldr r1, _0224D360 ; =0x00000196
	bne _0224D33C
	ldrb r1, [r5, r1]
	cmp r1, #0
	bne _0224D348
	ldrh r1, [r4, #2]
	bl ov11_0223128C
	b _0224D348
_0224D33C:
	ldrb r1, [r5, r1]
	cmp r1, #0
	beq _0224D348
	ldrh r1, [r4, #2]
	bl ov11_0223128C
_0224D348:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	add r0, r6, #0
	bl ov11_022567B8
	add r0, r5, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}
	nop
_0224D360: .word 0x00000196

	thumb_func_start ov11_0224D364
ov11_0224D364: ; 0x0224D364
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224EBF4
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D374
ov11_0224D374: ; 0x0224D374
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EC4C
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D388
ov11_0224D388: ; 0x0224D388
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224EC80
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D398
ov11_0224D398: ; 0x0224D398
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224ECB8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D3A8
ov11_0224D3A8: ; 0x0224D3A8
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224ECF0
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D3B8
ov11_0224D3B8: ; 0x0224D3B8
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224ED44
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D3CC
ov11_0224D3CC: ; 0x0224D3CC
	push {r4, lr}
	add r4, r1, #0
	bl ov11_0224ED98
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D3DC
ov11_0224D3DC: ; 0x0224D3DC
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EDEC
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D3F0
ov11_0224D3F0: ; 0x0224D3F0
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EE20
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D404
ov11_0224D404: ; 0x0224D404
	push {r4, lr}
	add r4, r1, #0
	add r2, r4, #0
	add r2, #0x94
	bl ov11_0224EE80
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, pc}

	thumb_func_start ov11_0224D418
ov11_0224D418: ; 0x0224D418
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r7, #0
	str r1, [sp, #4]
	str r1, [sp, #0x10]
	add r1, #0x94
	str r0, [sp]
	str r1, [sp, #0x10]
	str r7, [sp, #8]
	bl ov11_0222FF74
	mov r1, #0x80
	tst r0, r1
	beq _0224D444
	ldr r1, [sp, #0x10]
	ldr r0, [sp]
	ldr r1, [r1, #4]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl ov11_02231468
	b _0224D4FC
_0224D444:
	add r0, r7, #0
	str r0, [sp, #0xc]
	ldr r0, [sp]
	bl ov11_0222FF84
	cmp r0, #0
	ble _0224D4D2
_0224D452:
	ldr r0, [sp]
	ldr r1, [sp, #0xc]
	bl ov11_0222FF88
	add r6, r0, #0
	mov r5, #0
	bl Party_GetCount
	cmp r0, #0
	ble _0224D4C0
_0224D466:
	add r0, r6, #0
	add r1, r5, #0
	bl Party_GetMonByIndex
	mov r1, #5
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _0224D4B4
	add r0, r4, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _0224D4B4
	ldr r0, [sp]
	ldr r1, [sp, #0xc]
	bl ov11_02230270
	cmp r0, #0
	beq _0224D4A8
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	ldr r1, [sp, #8]
	add r0, r1, r0
	str r0, [sp, #8]
	b _0224D4B4
_0224D4A8:
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r7, r7, r0
_0224D4B4:
	add r0, r6, #0
	add r5, r5, #1
	bl Party_GetCount
	cmp r5, r0
	blt _0224D466
_0224D4C0:
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	ldr r0, [sp]
	bl ov11_0222FF84
	ldr r1, [sp, #0xc]
	cmp r1, r0
	blt _0224D452
_0224D4D2:
	cmp r7, #0
	bne _0224D4E6
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _0224D4E6
	ldr r0, [sp]
	mov r1, #3
	bl ov11_02231468
	b _0224D4FC
_0224D4E6:
	cmp r7, #0
	bne _0224D4F4
	ldr r0, [sp]
	mov r1, #2
	bl ov11_02231468
	b _0224D4FC
_0224D4F4:
	ldr r0, [sp]
	mov r1, #1
	bl ov11_02231468
_0224D4FC:
	mov r2, #0x65
	ldr r1, [sp, #4]
	lsl r2, r2, #2
	ldrb r1, [r1, r2]
	ldr r2, [sp, #0x10]
	ldr r0, [sp]
	ldrb r2, [r2]
	bl ov11_022567B8
	ldr r0, [sp, #4]
	bl ov11_0224D548
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_0224D518
ov11_0224D518: ; 0x0224D518
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	bl ov11_0222FF6C
	add r6, r0, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add r0, r6, #0
	bl CopyWindowPixelsToVram_TextMode
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x42
	bl ov11_022567B8
	add r0, r4, #0
	bl ov11_0224D548
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0224D548
ov11_0224D548: ; 0x0224D548
	mov r1, #0
	add r0, #0x94
	strb r1, [r0]
	bx lr

	.section .rodata

	.global ov11_0225E70C
ov11_0225E70C: ; 0x0225E70C
	.word ov11_0224CB74, ov11_0224CB78, ov11_0224CB98
	.word ov11_0224CBAC, ov11_0224CBC0, ov11_0224CBD4, ov11_0224CBE8
	.word ov11_0224CBFC, ov11_0224CC20, ov11_0224CC34, ov11_0224CC48
	.word ov11_0224CC58, ov11_0224CC6C, ov11_0224CC80, ov11_0224CC90
	.word ov11_0224CCB8, ov11_0224CCCC, ov11_0224CCE0, ov11_0224CCF4
	.word ov11_0224CD08, ov11_0224CD1C, ov11_0224CD30, ov11_0224CD44
	.word ov11_0224CD58, ov11_0224CD8C, ov11_0224CDA0, ov11_0224CDB4
	.word ov11_0224CDC8, ov11_0224CDDC, ov11_0224CDEC, ov11_0224CE00
	.word ov11_0224CE14, ov11_0224CE28, ov11_0224CE3C, ov11_0224CE50
	.word ov11_0224CE60, ov11_0224CE74, ov11_0224CE84, ov11_0224CE98
	.word ov11_0224CEAC, ov11_0224CF60, ov11_0224CFB8, ov11_0224CFE8
	.word ov11_0224D064, ov11_0224D078, ov11_0224D08C, ov11_0224D184
	.word ov11_0224D1A4, ov11_0224D21C, ov11_0224D230, ov11_0224D244
	.word ov11_0224D280, ov11_0224D2BC, ov11_0224D2F8, ov11_0224D31C
	.word ov11_0224D364, ov11_0224D374, ov11_0224D388, ov11_0224D398
	.word ov11_0224D3A8, ov11_0224D3B8, ov11_0224D3CC, ov11_0224D3DC
	.word ov11_0224D3F0, ov11_0224D404, ov11_0224D418, ov11_0224D518
