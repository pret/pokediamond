	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_0224D550
ov11_0224D550: ; 0x0224D550
	push {r4, lr}
	add r4, r0, #0
	mov r0, #5
	mov r1, #0x18
	bl AllocFromHeap
	add r1, r0, #0
	str r4, [r1]
	mov r2, #0
	strb r2, [r1, #0x14]
	ldr r0, _0224D570 ; =ov11_022530A0
	strb r2, [r1, #0x15]
	bl sub_0200CA44
	pop {r4, pc}
	nop
_0224D570: .word ov11_022530A0

	thumb_func_start ov11_0224D574
ov11_0224D574: ; 0x0224D574
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	str r0, [sp, #0x24]
	add r6, r1, #0
	add r5, r2, #0
	bl ov11_02230068
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	bl ov11_0222FF74
	mov r0, #5
	mov r1, #0x2c
	bl AllocFromHeap
	add r4, r0, #0
	mov r2, #0
	ldr r0, _0224D720 ; =0x00000195
	strb r2, [r4, #0x12]
	ldrb r0, [r6, r0]
	mov r1, #1
	tst r0, r1
	beq _0224D5CA
	mov r0, #2
	strb r0, [r4, #0x13]
	ldr r0, [sp, #0x24]
	bl ov11_02230088
	str r0, [r4, #0xc]
	ldr r1, _0224D720 ; =0x00000195
	ldr r0, [r0]
	ldrb r2, [r6, r1]
	mov r1, #1
	and r2, r1
	add r3, r2, #0
	mov r1, #6
	mul r3, r1
	ldr r1, _0224D724 ; =ov08_0222D550
	mov r2, #0x58
	ldrsh r1, [r1, r3]
	bl sub_0200C714
	b _0224D5F0
_0224D5CA:
	ldr r0, [sp, #0x24]
	add r1, r2, #0
	strb r2, [r4, #0x13]
	bl ov11_02230088
	str r0, [r4, #0xc]
	ldr r1, _0224D720 ; =0x00000195
	ldr r0, [r0]
	ldrb r2, [r6, r1]
	mov r1, #1
	and r2, r1
	add r3, r2, #0
	mov r1, #6
	mul r3, r1
	ldr r1, _0224D724 ; =ov08_0222D550
	mov r2, #0x88
	ldrsh r1, [r1, r3]
	bl sub_0200C714
_0224D5F0:
	ldrb r0, [r5, #1]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _0224D5FC
	mov r0, #1
	b _0224D5FE
_0224D5FC:
	mov r0, #0
_0224D5FE:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrb r0, [r5, #1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1b
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	str r0, [sp, #8]
	ldrb r2, [r5, #1]
	ldrh r1, [r5, #2]
	ldrb r3, [r4, #0x13]
	lsl r2, r2, #0x1e
	add r0, sp, #0x48
	lsr r2, r2, #0x1e
	bl sub_02068C00
	ldr r0, [r5, #4]
	str r0, [sp]
	ldrb r3, [r5, #1]
	ldrh r0, [r5, #2]
	ldrb r2, [r4, #0x13]
	lsl r1, r3, #0x1e
	lsl r3, r3, #0x18
	lsr r1, r1, #0x1e
	lsr r3, r3, #0x1b
	bl sub_02068E88
	str r0, [sp, #0x2c]
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x30
	ldrh r3, [r5, #2]
	add r0, #2
	mov r1, #0x8a
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, sp, #0x30
	ldrh r3, [r5, #2]
	add r0, #1
	mov r1, #0x90
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	ldrh r3, [r5, #2]
	add r0, sp, #0x30
	mov r1, #0x8e
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #0x30
	ldrh r1, [r5, #2]
	add r0, #3
	bl sub_02069010
	ldr r1, _0224D720 ; =0x00000195
	mov r0, #6
	ldrb r2, [r6, r1]
	ldr r3, _0224D724 ; =ov08_0222D550
	add r7, r2, #0
	mul r7, r0
	ldr r0, _0224D728 ; =ov08_0222D552
	mov r2, #2
	ldrsh r0, [r0, r7]
	ldrsh r3, [r3, r7]
	str r0, [sp]
	ldr r0, _0224D72C ; =ov08_0222D554
	ldrsh r0, [r0, r7]
	str r0, [sp, #4]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #8]
	add r0, sp, #0x30
	ldrsb r2, [r0, r2]
	str r2, [sp, #0xc]
	mov r2, #1
	ldrsb r2, [r0, r2]
	str r2, [sp, #0x10]
	ldrb r0, [r0]
	add r2, sp, #0x48
	str r0, [sp, #0x14]
	sub r0, r1, #1
	ldrb r0, [r6, r0]
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x18]
	add r0, sp, #0x30
	add r0, #3
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	bl ov11_02253A88
	str r0, [r6, #0x20]
	str r0, [r4, #8]
	ldrb r0, [r4, #0x13]
	cmp r0, #2
	bne _0224D6D8
	mov r3, #0
	str r3, [sp]
	mov r1, #8
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl sub_02007E68
_0224D6D8:
	ldr r1, _0224D720 ; =0x00000195
	ldrb r0, [r6, r1]
	lsl r2, r0, #2
	ldr r0, _0224D730 ; =ov08_0222D538
	ldrsh r0, [r0, r2]
	strh r0, [r4, #0x14]
	ldr r0, [sp, #0x24]
	str r0, [r4]
	str r6, [r4, #4]
	ldrb r0, [r5]
	strb r0, [r4, #0x10]
	sub r0, r1, #1
	ldrb r0, [r6, r0]
	strb r0, [r4, #0x11]
	ldrh r0, [r5, #2]
	strh r0, [r4, #0x16]
	ldr r0, [r5, #8]
	str r0, [r4, #0x18]
	ldrb r0, [r6, r1]
	str r0, [r4, #0x1c]
	ldr r0, [r5, #4]
	bl GetNatureFromPersonality
	str r0, [r4, #0x24]
	ldrb r0, [r5, #1]
	add r1, r4, #0
	mov r2, #0
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	str r0, [r4, #0x28]
	ldr r0, _0224D734 ; =ov11_0224EEA0
	bl sub_0200CA44
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224D720: .word 0x00000195
_0224D724: .word ov08_0222D550
_0224D728: .word ov08_0222D552
_0224D72C: .word ov08_0222D554
_0224D730: .word ov08_0222D538
_0224D734: .word ov11_0224EEA0

	thumb_func_start ov11_0224D738
ov11_0224D738: ; 0x0224D738
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	add r6, r1, #0
	add r5, r2, #0
	bl ov11_0222FF74
	mov r0, #5
	mov r1, #0x9c
	bl AllocFromHeap
	add r4, r0, #0
	ldr r0, _0224D874 ; =0x00000195
	ldrb r1, [r6, r0]
	mov r0, #1
	tst r0, r1
	beq _0224D75E
	mov r1, #2
	b _0224D760
_0224D75E:
	mov r1, #0
_0224D760:
	add r0, r4, #0
	add r0, #0x84
	strb r1, [r0]
	ldrb r0, [r5, #1]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _0224D772
	mov r0, #1
	b _0224D774
_0224D772:
	mov r0, #0
_0224D774:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrb r0, [r5, #1]
	add r3, r4, #0
	add r3, #0x84
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1b
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	str r0, [sp, #8]
	ldrb r2, [r5, #1]
	add r0, r4, #0
	ldrh r1, [r5, #2]
	lsl r2, r2, #0x1e
	ldrb r3, [r3]
	add r0, #0x14
	lsr r2, r2, #0x1e
	bl sub_02068C00
	ldr r0, [r5, #4]
	add r2, r4, #0
	str r0, [sp]
	ldrb r3, [r5, #1]
	add r2, #0x84
	ldrh r0, [r5, #2]
	lsl r1, r3, #0x1e
	lsl r3, r3, #0x18
	ldrb r2, [r2]
	lsr r1, r1, #0x1e
	lsr r3, r3, #0x1b
	bl sub_02068E88
	add r1, r4, #0
	add r1, #0x85
	strb r0, [r1]
	mov r0, #1
	str r0, [sp]
	add r0, r4, #0
	ldrh r3, [r5, #2]
	add r0, #0x90
	mov r1, #0x8a
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, r4, #0
	ldrh r3, [r5, #2]
	add r0, #0x91
	mov r1, #0x90
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, r4, #0
	ldrh r3, [r5, #2]
	add r0, #0x93
	mov r1, #0x8e
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	add r0, r6, #0
	bl ov11_02253A78
	str r7, [r4]
	add r0, r4, #0
	str r6, [r4, #4]
	mov r1, #0
	add r0, #0x83
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x96
	strb r1, [r0]
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x80
	strb r1, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r2, [r6, r0]
	add r1, r4, #0
	add r1, #0x81
	strb r2, [r1]
	add r1, r4, #0
	ldrh r2, [r5, #2]
	add r1, #0x86
	add r0, r0, #1
	strh r2, [r1]
	ldrb r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x82
	strb r1, [r0]
	add r0, r4, #0
	ldr r1, [r5, #8]
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	ldr r1, [r5, #0xc]
	add r0, #0x8c
	strb r1, [r0]
	ldr r0, [r5, #4]
	bl GetNatureFromPersonality
	add r1, r4, #0
	add r1, #0x8d
	strb r0, [r1]
	add r0, r4, #0
	ldr r1, [r5, #0x10]
	add r0, #0x8e
	strh r1, [r0]
	ldrb r0, [r5, #1]
	lsl r0, r0, #0x1d
	lsr r1, r0, #0x1f
	add r0, r4, #0
	add r0, #0x92
	strb r1, [r0]
	add r0, r4, #0
	mov r2, #0
	add r0, #0x94
	strh r2, [r0]
	ldr r0, _0224D878 ; =ov11_0224F2DC
	add r1, r4, #0
	bl sub_0200CA44
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224D874: .word 0x00000195
_0224D878: .word ov11_0224F2DC

	thumb_func_start ov11_0224D87C
ov11_0224D87C: ; 0x0224D87C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r7, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bl ov11_0222FF74
	mov r0, #5
	mov r1, #0x9c
	bl AllocFromHeap
	add r5, r0, #0
	add r1, r5, #0
	mov r0, #0
	add r1, #0x83
	strb r0, [r1]
	ldr r1, _0224DA24 ; =0x00000195
	ldrb r2, [r6, r1]
	mov r1, #1
	tst r1, r2
	beq _0224D8B0
	add r0, r5, #0
	mov r1, #2
	add r0, #0x84
	strb r1, [r0]
	b _0224D8B6
_0224D8B0:
	add r1, r5, #0
	add r1, #0x84
	strb r0, [r1]
_0224D8B6:
	ldrb r0, [r4, #1]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _0224D8C2
	mov r0, #1
	b _0224D8C4
_0224D8C2:
	mov r0, #0
_0224D8C4:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrb r0, [r4, #1]
	add r3, r5, #0
	add r3, #0x84
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1b
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	str r0, [sp, #8]
	ldrb r2, [r4, #1]
	add r0, r5, #0
	ldrh r1, [r4, #2]
	lsl r2, r2, #0x1e
	ldrb r3, [r3]
	add r0, #0x14
	lsr r2, r2, #0x1e
	bl sub_02068C00
	ldr r0, [r4, #4]
	add r2, r5, #0
	str r0, [sp]
	ldrb r3, [r4, #1]
	add r2, #0x84
	ldrh r0, [r4, #2]
	lsl r1, r3, #0x1e
	lsl r3, r3, #0x18
	ldrb r2, [r2]
	lsr r1, r1, #0x1e
	lsr r3, r3, #0x1b
	bl sub_02068E88
	add r1, r5, #0
	add r1, #0x85
	strb r0, [r1]
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	ldrh r3, [r4, #2]
	add r0, #0x90
	mov r1, #0x8a
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	ldrh r3, [r4, #2]
	add r0, #0x91
	mov r1, #0x90
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	ldrh r3, [r4, #2]
	add r0, #0x93
	mov r1, #0x8e
	mov r2, #0
	bl ReadFromNarcMemberByIdPair
	add r0, r6, #0
	bl ov11_02253A78
	str r7, [r5]
	str r6, [r5, #4]
	add r0, r5, #0
	ldrb r1, [r4]
	add r0, #0x80
	strb r1, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r2, [r6, r0]
	add r1, r5, #0
	add r1, #0x81
	strb r2, [r1]
	add r1, r5, #0
	ldrh r2, [r4, #2]
	add r1, #0x86
	add r0, r0, #1
	strh r2, [r1]
	ldrb r1, [r6, r0]
	add r0, r5, #0
	add r0, #0x82
	strb r1, [r0]
	add r0, r5, #0
	ldr r1, [r4, #8]
	add r0, #0x88
	str r1, [r0]
	add r0, r5, #0
	ldr r1, [r4, #0xc]
	add r0, #0x8c
	strb r1, [r0]
	ldr r0, [r4, #4]
	bl GetNatureFromPersonality
	add r1, r5, #0
	add r1, #0x8d
	strb r0, [r1]
	add r0, r5, #0
	ldr r1, [r4, #0x10]
	add r0, #0x8e
	strh r1, [r0]
	ldrb r0, [r4, #1]
	lsl r0, r0, #0x1d
	lsr r1, r0, #0x1f
	add r0, r5, #0
	add r0, #0x92
	strb r1, [r0]
	add r0, r5, #0
	ldr r1, [r4, #0x14]
	add r0, #0x94
	strh r1, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0x96
	strb r1, [r0]
	add r0, r5, #0
	ldr r2, [r4, #0x4c]
	add r0, #0x98
	str r2, [r0]
	str r4, [sp, #0x18]
	add r7, r5, #0
	add r2, r4, #0
	add r3, r5, #0
_0224D9C2:
	ldr r0, [sp, #0x18]
	add r0, #0x50
	ldrh r6, [r0]
	add r0, r7, #0
	add r0, #0x40
	strh r6, [r0]
	add r0, r4, r1
	add r0, #0x58
	ldrb r6, [r0]
	add r0, r5, r1
	str r0, [sp, #0x14]
	add r0, #0x48
	str r0, [sp, #0x14]
	strb r6, [r0]
	add r0, r4, r1
	add r0, #0x5c
	ldrb r6, [r0]
	add r0, r5, r1
	str r0, [sp, #0x10]
	add r0, #0x4c
	str r0, [sp, #0x10]
	strb r6, [r0]
	add r0, r4, r1
	add r0, #0x60
	ldrb r6, [r0]
	add r0, r5, r1
	str r0, [sp, #0xc]
	add r0, #0x50
	str r0, [sp, #0xc]
	strb r6, [r0]
	ldr r0, [r2, #0x64]
	add r1, r1, #1
	str r0, [r3, #0x54]
	ldr r0, [sp, #0x18]
	add r7, r7, #2
	add r0, r0, #2
	str r0, [sp, #0x18]
	add r2, r2, #4
	add r3, r3, #4
	cmp r1, #4
	blt _0224D9C2
	ldr r0, _0224DA28 ; =ov11_0224F7C4
	add r1, r5, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0224DA24: .word 0x00000195
_0224DA28: .word ov11_0224F7C4

	thumb_func_start ov11_0224DA2C
ov11_0224DA2C: ; 0x0224DA2C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x74
	str r2, [sp]
	bl AllocFromHeap
	add r2, r0, #0
	str r5, [r2]
	str r4, [r2, #4]
	ldr r0, [r4, #0x20]
	add r7, r2, #0
	str r0, [r2, #8]
	ldr r0, [sp]
	add r5, r2, #0
	ldrb r1, [r0]
	add r0, r2, #0
	add r0, #0x68
	strb r1, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r3, [r4, r0]
	add r1, r2, #0
	add r1, #0x69
	add r0, r0, #1
	strb r3, [r1]
	ldrb r1, [r4, r0]
	add r0, r2, #0
	add r0, #0x6a
	strb r1, [r0]
	add r0, r2, #0
	mov r1, #0
	add r0, #0x6b
	strb r1, [r0]
	ldr r0, [sp]
	ldrb r3, [r0, #1]
	add r0, r2, #0
	add r0, #0x6c
	strb r3, [r0]
	ldr r0, [sp]
	ldrh r3, [r0, #2]
	add r0, r2, #0
	add r0, #0x6e
	strh r3, [r0]
	ldr r0, [sp]
	ldr r3, [sp]
	ldr r0, [r0, #4]
	add r4, r3, #0
	str r0, [r2, #0x70]
_0224DA92:
	ldrh r0, [r3, #8]
	add r3, r3, #2
	strh r0, [r7, #0x28]
	ldr r0, [sp]
	add r7, r7, #2
	add r0, r0, r1
	str r0, [sp, #0x10]
	ldrb r0, [r0, #0x10]
	str r0, [sp, #8]
	add r0, r2, r1
	ldr r6, [sp, #8]
	add r0, #0x30
	strb r6, [r0]
	ldr r0, [sp, #0x10]
	add r6, r2, r1
	ldrb r0, [r0, #0x14]
	str r6, [sp, #4]
	add r6, #0x34
	str r0, [sp, #0xc]
	strb r0, [r6]
	ldr r0, [sp, #0x10]
	str r6, [sp, #4]
	add r6, r2, r1
	ldrb r0, [r0, #0x18]
	add r6, #0x38
	add r1, r1, #1
	strb r0, [r6]
	ldr r0, [r4, #0x1c]
	add r4, r4, #4
	str r0, [r5, #0x3c]
	add r5, r5, #4
	cmp r1, #4
	blt _0224DA92
	ldr r0, _0224DAE4 ; =ov11_0224FD90
	add r1, r2, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0224DAE4: .word ov11_0224FD90

	thumb_func_start ov11_0224DAE8
ov11_0224DAE8: ; 0x0224DAE8
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r6, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r7, [r4]
	ldr r0, [r5, #0x20]
	str r0, [r4, #4]
	ldrb r0, [r6]
	strb r0, [r4, #8]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	add r0, r0, #1
	strb r1, [r4, #9]
	ldrb r0, [r5, r0]
	mov r1, #0
	add r3, r1, #0
	strb r0, [r4, #0xa]
	strb r1, [r4, #0xb]
	ldrb r0, [r6, #1]
	strb r0, [r4, #0xc]
	ldrh r0, [r6, #2]
	lsl r2, r0, #1
	ldr r0, _0224DB44 ; =ov11_0225E84A
	ldrh r0, [r0, r2]
	mov r2, #0x10
	str r0, [sp]
	ldr r0, [r4, #4]
	bl sub_02007E68
	ldr r0, [r4, #4]
	mov r1, #0x2d
	mov r2, #1
	bl sub_02007558
	ldr r0, _0224DB48 ; =ov11_0224FFF0
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224DB44: .word ov11_0225E84A
_0224DB48: .word ov11_0224FFF0

	thumb_func_start ov11_0224DB4C
ov11_0224DB4C: ; 0x0224DB4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r6, r0, #0
	add r5, r1, #0
	str r2, [sp, #0x24]
	bl ov11_02230068
	str r0, [sp, #0x2c]
	mov r0, #5
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0
	mov r2, #0
	ldr r0, _0224DCCC ; =0x00000195
	strb r2, [r4, #0x12]
	ldrb r0, [r5, r0]
	mov r1, #1
	tst r0, r1
	beq _0224DB9C
	mov r0, #2
	strb r0, [r4, #0x13]
	add r0, r6, #0
	bl ov11_02230088
	str r0, [r4, #8]
	ldr r1, _0224DCCC ; =0x00000195
	ldr r0, [r0]
	ldrb r2, [r5, r1]
	mov r1, #1
	and r2, r1
	add r3, r2, #0
	mov r1, #6
	mul r3, r1
	ldr r1, _0224DCD0 ; =ov08_0222D550
	mov r2, #0x58
	ldrsh r1, [r1, r3]
	bl sub_0200C714
	b _0224DBC2
_0224DB9C:
	add r0, r6, #0
	add r1, r2, #0
	strb r2, [r4, #0x13]
	bl ov11_02230088
	str r0, [r4, #8]
	ldr r1, _0224DCCC ; =0x00000195
	ldr r0, [r0]
	ldrb r2, [r5, r1]
	mov r1, #1
	and r2, r1
	add r3, r2, #0
	mov r1, #6
	mul r3, r1
	ldr r1, _0224DCD0 ; =ov08_0222D550
	mov r2, #0x88
	ldrsh r1, [r1, r3]
	bl sub_0200C714
_0224DBC2:
	add r0, r6, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _0224DBE4
	add r0, r6, #0
	bl ov11_0222FF74
	mov r1, #0x10
	tst r0, r1
	beq _0224DBEC
	ldr r0, _0224DCCC ; =0x00000195
	ldrb r1, [r5, r0]
	mov r0, #1
	tst r0, r1
	beq _0224DBEC
_0224DBE4:
	ldr r0, _0224DCCC ; =0x00000195
	ldrb r0, [r5, r0]
	str r0, [sp, #0x28]
	b _0224DBF6
_0224DBEC:
	ldr r0, _0224DCCC ; =0x00000195
	ldrb r1, [r5, r0]
	mov r0, #1
	and r0, r1
	str r0, [sp, #0x28]
_0224DBF6:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r0, r6, #0
	bl ov11_0223021C
	add r3, r0, #0
	ldr r1, [sp, #0x24]
	lsl r3, r3, #0x18
	ldrh r1, [r1, #2]
	ldrb r2, [r4, #0x13]
	add r0, sp, #0x30
	lsr r3, r3, #0x18
	bl sub_02068FE0
	ldr r0, [sp, #0x28]
	mov r1, #6
	add r7, r0, #0
	mul r7, r1
	ldr r0, _0224DCD4 ; =ov08_0222D552
	mov r1, #0
	ldrsh r0, [r0, r7]
	ldr r3, _0224DCD0 ; =ov08_0222D550
	add r2, sp, #0x30
	str r0, [sp]
	ldr r0, _0224DCD8 ; =ov08_0222D554
	ldrsh r3, [r3, r7]
	ldrsh r0, [r0, r7]
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	mov r0, #0x65
	str r1, [sp, #0x14]
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	str r0, [sp, #0x18]
	str r1, [sp, #0x1c]
	str r1, [sp, #0x20]
	ldr r1, [sp, #0x2c]
	add r0, r6, #0
	bl ov11_02253A88
	str r0, [r5, #0x1c]
	str r0, [r4, #4]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _0224DC80
	add r0, r6, #0
	bl ov11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	bne _0224DC80
	ldr r0, [sp, #0x24]
	ldrh r0, [r0, #2]
	bl sub_0206AA30
	ldr r3, _0224DCCC ; =0x00000195
	add r2, r0, #0
	ldrb r3, [r5, r3]
	ldr r1, [sp, #0x28]
	add r0, r6, #0
	asr r3, r3, #1
	bl ov11_02254308
	str r0, [r5, #0x18]
	str r0, [r4, #0xc]
_0224DC80:
	ldr r0, [sp, #0x28]
	lsl r1, r0, #2
	ldr r0, _0224DCDC ; =ov08_0222D538
	ldrsh r0, [r0, r1]
	strh r0, [r4, #0x14]
	ldr r0, [sp, #0x24]
	str r6, [r4]
	ldrb r0, [r0]
	strb r0, [r4, #0x10]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	add r0, r0, #1
	strb r1, [r4, #0x11]
	ldrb r0, [r5, r0]
	str r0, [r4, #0x18]
	mov r0, #0
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _0224DCAE
	cmp r0, #2
	bne _0224DCBE
_0224DCAE:
	add r0, r6, #0
	bl ov11_0222FF68
	mov r1, #3
	mov r2, #2
	mov r3, #0x84
	bl BgSetPosTextAndCommit
_0224DCBE:
	ldr r0, _0224DCE0 ; =ov11_02250060
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224DCCC: .word 0x00000195
_0224DCD0: .word ov08_0222D550
_0224DCD4: .word ov08_0222D552
_0224DCD8: .word ov08_0222D554
_0224DCDC: .word ov08_0222D538
_0224DCE0: .word ov11_02250060

	thumb_func_start ov11_0224DCE4
ov11_0224DCE4: ; 0x0224DCE4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #5
	mov r1, #0x1c
	add r6, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4, #0xa]
	str r7, [r4]
	ldrb r1, [r6]
	strb r1, [r4, #8]
	ldrb r1, [r6, #1]
	str r1, [r4, #0x10]
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r2, [r5, r1]
	strb r2, [r4, #9]
	str r5, [r4, #4]
	add r2, r1, #1
	ldrb r3, [r5, r2]
	mov r2, #1
	tst r2, r3
	beq _0224DD1E
	mov r1, #2
	strb r1, [r4, #0xb]
	b _0224DD30
_0224DD1E:
	ldrb r1, [r5, r1]
	add r0, r7, #0
	bl ov11_02230188
	mov r1, #0
	strb r1, [r4, #0xb]
	ldrb r0, [r0, #1]
	bl sub_0206AA30
_0224DD30:
	str r0, [r4, #0xc]
	ldr r0, _0224DD40 ; =ov11_02250338
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224DD40: .word ov11_02250338

	thumb_func_start ov11_0224DD44
ov11_0224DD44: ; 0x0224DD44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x10
	bl AllocFromHeap
	add r1, r0, #0
	mov r0, #0
	strb r0, [r1, #0xa]
	add r2, r4, #0
	str r5, [r1]
	add r2, #0x94
	ldrb r2, [r2]
	strb r2, [r1, #8]
	mov r2, #0x65
	lsl r2, r2, #2
	ldrb r3, [r4, r2]
	add r2, r2, #1
	strb r3, [r1, #9]
	str r4, [r1, #4]
	ldrb r3, [r4, r2]
	mov r2, #1
	tst r2, r3
	beq _0224DD7A
	mov r0, #2
	b _0224DD7A
_0224DD7A:
	strb r0, [r1, #0xb]
	ldr r0, _0224DD88 ; =ov11_022508A4
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	nop
_0224DD88: .word ov11_022508A4

	thumb_func_start ov11_0224DD8C
ov11_0224DD8C: ; 0x0224DD8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x10]
	add r5, r1, #0
	add r7, r2, #0
	bl ov11_02230068
	str r0, [sp, #0x14]
	mov r0, #5
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	ldr r1, _0224DE38 ; =0x00000195
	strb r0, [r4, #0xa]
	ldrb r2, [r5, r1]
	mov r1, #1
	tst r1, r2
	beq _0224DDB8
	mov r0, #2
	b _0224DDB8
_0224DDB8:
	mov r1, #0x65
	strb r0, [r4, #0xb]
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldr r0, [sp, #0x10]
	bl ov11_0223021C
	add r3, r0, #0
	lsl r3, r3, #0x18
	ldrh r1, [r7, #2]
	ldrb r2, [r4, #0xb]
	add r0, sp, #0x18
	lsr r3, r3, #0x18
	bl sub_02068FE0
	ldr r0, _0224DE38 ; =0x00000195
	mov r1, #6
	ldrb r2, [r5, r0]
	sub r0, r0, #1
	ldr r3, _0224DE3C ; =ov08_0222D576
	add r6, r2, #0
	mul r6, r1
	ldr r1, _0224DE40 ; =ov08_0222D578
	ldr r2, _0224DE44 ; =ov08_0222D574
	ldrsh r1, [r1, r6]
	ldrsh r2, [r2, r6]
	ldrsh r3, [r3, r6]
	str r1, [sp]
	ldrb r0, [r5, r0]
	add r1, sp, #0x18
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	bl sub_020073A0
	str r0, [r5, #0x1c]
	str r0, [r4, #4]
	ldr r0, _0224DE38 ; =0x00000195
	ldr r2, _0224DE48 ; =ov08_0222D538
	ldrb r1, [r5, r0]
	sub r0, r0, #1
	lsl r1, r1, #0x1f
	lsr r3, r1, #0x1d
	ldr r1, [r7, #4]
	add r2, r2, r3
	lsl r1, r1, #1
	ldrsh r1, [r1, r2]
	mov r2, #0
	strh r1, [r4, #0xc]
	ldr r1, [sp, #0x10]
	str r1, [r4]
	ldrb r1, [r7]
	strb r1, [r4, #8]
	ldrb r0, [r5, r0]
	add r1, r4, #0
	strb r0, [r4, #9]
	ldr r0, _0224DE4C ; =ov11_0225092C
	bl sub_0200CA44
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224DE38: .word 0x00000195
_0224DE3C: .word ov08_0222D576
_0224DE40: .word ov08_0222D578
_0224DE44: .word ov08_0222D574
_0224DE48: .word ov08_0222D538
_0224DE4C: .word ov11_0225092C

	thumb_func_start ov11_0224DE50
ov11_0224DE50: ; 0x0224DE50
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r6, #0
	add r4, #0x28
	add r7, r0, #0
	add r5, r2, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #1
	bl MIi_CpuClearFast
	mov r0, #0x65
	str r7, [r4, #0xc]
	lsl r0, r0, #2
	ldrb r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r0, r7, #0
	bl ov11_0222FF74
	add r1, r0, #0
	ldr r0, _0224DF10 ; =0x00000195
	ldrb r0, [r6, r0]
	bl ov11_02257F6C
	add r1, r4, #0
	add r1, #0x25
	strb r0, [r1]
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x4c
	strb r1, [r0]
	mov r0, #2
	ldrsh r0, [r5, r0]
	str r0, [r4, #0x28]
	ldrh r0, [r5, #4]
	str r0, [r4, #0x2c]
	add r0, r4, #0
	ldrb r1, [r5, #1]
	add r0, #0x48
	strb r1, [r0]
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x1e
	add r0, r4, #0
	add r0, #0x49
	strb r1, [r0]
	mov r1, #0
	str r1, [r4, #0x30]
	ldr r0, [r5, #8]
	str r0, [r4, #0x38]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x3c]
	add r0, r4, #0
	ldrb r2, [r5, #6]
	add r0, #0x26
	strb r2, [r0]
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x1b
	lsr r2, r0, #0x1b
	add r0, r4, #0
	add r0, #0x4a
	strb r2, [r0]
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x18
	lsr r2, r0, #0x1f
	add r0, r4, #0
	add r0, #0x4b
	strb r2, [r0]
	add r0, r4, #0
	ldrb r2, [r5, #0x14]
	add r0, #0x4d
	strb r2, [r0]
	add r0, r4, #0
	ldr r2, [r5, #0x10]
	add r0, #0x27
	strb r2, [r0]
	add r0, r4, #0
	bl ov11_022572AC
	mov r2, #0
	ldr r1, [r4, #0x28]
	add r0, r4, #0
	mvn r2, r2
	bl ov11_02256D70
	mov r2, #0xfa
	ldr r0, _0224DF14 ; =ov11_022509B4
	add r1, r4, #0
	lsl r2, r2, #2
	bl sub_0200CA44
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224DF10: .word 0x00000195
_0224DF14: .word ov11_022509B4

	thumb_func_start ov11_0224DF18
ov11_0224DF18: ; 0x0224DF18
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r5, #0
	add r4, #0x28
	add r6, r0, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #1
	bl MIi_CpuClearFast
	mov r0, #0x65
	str r6, [r4, #0xc]
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r5, #0x94
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x4c
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #1
	bl ov11_02257334
	mov r2, #0xfa
	ldr r0, _0224DF5C ; =ov11_02250A28
	add r1, r4, #0
	lsl r2, r2, #2
	bl sub_0200CA44
	str r0, [r4, #0x10]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224DF5C: .word ov11_02250A28

	thumb_func_start ov11_0224DF60
ov11_0224DF60: ; 0x0224DF60
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	str r1, [sp]
	mov r0, #5
	mov r1, #0x3c
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #0x3c
	bl MIi_CpuClearFast
	mov r7, #0
	strb r7, [r4, #0xa]
	strb r7, [r4, #0xb]
	str r6, [r4]
	ldrb r0, [r5]
	mov r1, #0x65
	lsl r1, r1, #2
	strb r0, [r4, #8]
	ldr r0, [sp]
	add r3, r5, #0
	ldrb r0, [r0, r1]
	add r1, r1, #1
	add r6, r4, #0
	strb r0, [r4, #9]
	ldr r0, [sp]
	ldrb r1, [r0, r1]
	add r0, r4, #0
	add r0, #0x34
	strb r1, [r0]
	ldr r0, [sp]
	add r0, #0x28
	str r0, [r4, #4]
	add r0, r4, #0
	ldrb r1, [r5, #1]
	add r0, #0x23
	strb r1, [r0]
	mov r0, #0x24
	ldrsh r0, [r5, r0]
	strh r0, [r4, #0x36]
	ldrh r0, [r5, #0x26]
	strh r0, [r4, #0x38]
	add r0, r5, #0
	add r0, #0x28
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x3a
	strb r1, [r0]
_0224DFC6:
	mov r2, #0
_0224DFC8:
	add r0, r3, r2
	ldrb r1, [r0, #8]
	add r0, r6, r2
	add r2, r2, #1
	strb r1, [r0, #0x10]
	cmp r2, #6
	blt _0224DFC8
	add r7, r7, #1
	add r3, r3, #6
	add r6, r6, #6
	cmp r7, #2
	blt _0224DFC6
	mov r0, #0
	add r3, r0, #0
_0224DFE4:
	add r2, r5, r0
	ldrb r1, [r2, #8]
	cmp r1, #2
	bne _0224DFF2
	add r1, r4, r0
	strb r3, [r1, #0x1c]
	b _0224DFF8
_0224DFF2:
	ldrb r2, [r2, #2]
	add r1, r4, r0
	strb r2, [r1, #0x1c]
_0224DFF8:
	add r0, r0, #1
	cmp r0, #6
	blt _0224DFE4
	mov r2, #0
	add r3, r5, #0
	add r6, r4, #0
_0224E004:
	ldrh r0, [r3, #0x14]
	add r7, r4, r2
	add r1, r5, r2
	strh r0, [r6, #0x24]
	ldrb r0, [r1, #0x1c]
	add r7, #0x2c
	add r1, #0x20
	strb r0, [r7]
	add r0, r4, r2
	ldrb r1, [r1]
	add r0, #0x30
	add r2, r2, #1
	strb r1, [r0]
	add r3, r3, #2
	add r6, r6, #2
	cmp r2, #4
	blt _0224E004
	ldr r0, [sp]
	add r1, r4, #0
	ldr r0, [r0]
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_0224E034
ov11_0224E034: ; 0x0224E034
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r1, [sp]
	mov r0, #5
	mov r1, #0x24
	add r7, r2, #0
	bl AllocFromHeap
	add r3, r0, #0
	mov r1, #0x65
	mov r4, #0
	add r0, #0x20
	strb r4, [r0]
	ldr r0, [sp]
	str r5, [r3]
	add r0, #0x94
	ldrb r0, [r0]
	lsl r1, r1, #2
	add r5, r7, #0
	strb r0, [r3, #0x1c]
	ldr r0, [sp]
	add r6, r3, #0
	ldrb r0, [r0, r1]
	add r1, r1, #1
	strb r0, [r3, #0x1d]
	ldr r0, [sp]
	ldrb r0, [r0, r1]
	strb r0, [r3, #0x1e]
	ldr r0, [sp]
	add r0, #0x28
	str r0, [r3, #4]
	ldrb r0, [r7, #1]
	strb r0, [r3, #0x1f]
_0224E076:
	ldrh r0, [r5, #4]
	add r2, r7, r4
	add r1, r3, r4
	strh r0, [r6, #0xc]
	ldrb r0, [r2, #0xc]
	add r4, r4, #1
	add r5, r5, #2
	strb r0, [r1, #0x14]
	ldrb r0, [r2, #0x10]
	add r6, r6, #2
	cmp r4, #4
	strb r0, [r1, #0x18]
	blt _0224E076
	ldrh r0, [r7, #2]
	add r1, r3, #0
	mov r2, #0
	strh r0, [r3, #0x22]
	ldr r0, [sp]
	ldr r0, [r0, #4]
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224E0A4
ov11_0224E0A4: ; 0x0224E0A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	add r7, r1, #0
	mov r0, #5
	mov r1, #0x34
	add r5, r2, #0
	bl AllocFromHeap
	add r6, r0, #0
	mov r0, #0
	strb r0, [r6, #0xf]
	ldr r0, [sp]
	str r0, [r6]
	add r0, r7, #0
	add r0, #0x94
	ldrb r0, [r0]
	strb r0, [r6, #0xc]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r7, r0]
	add r0, r0, #1
	strb r1, [r6, #0xd]
	ldrb r0, [r7, r0]
	strb r0, [r6, #0xe]
	ldrh r0, [r5, #2]
	strh r0, [r6, #0x30]
	add r0, r7, #0
	add r0, #0x28
	str r0, [r6, #4]
	add r0, r6, #0
	ldrb r1, [r5, #1]
	add r0, #0x32
	strb r1, [r0]
	ldr r0, [sp]
	add r1, sp, #4
	bl ov11_02231504
	ldr r0, [sp]
	bl ov11_0222FF84
	add r4, r0, #0
	ldr r0, [sp]
	bl ov11_0222FF74
	mov r0, #0
	cmp r4, #0
	ble _0224E120
	add r1, r6, #0
_0224E106:
	ldrh r2, [r5, #4]
	add r0, r0, #1
	strh r2, [r1, #0x10]
	ldrh r2, [r5, #6]
	strh r2, [r1, #0x12]
	ldrh r2, [r5, #8]
	strh r2, [r1, #0x14]
	ldrh r2, [r5, #0xa]
	add r5, #8
	strh r2, [r1, #0x16]
	add r1, #8
	cmp r0, r4
	blt _0224E106
_0224E120:
	ldr r0, [r7, #8]
	add r1, r6, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224E130
ov11_0224E130: ; 0x0224E130
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	str r1, [sp]
	mov r0, #5
	mov r1, #0x34
	str r2, [sp, #4]
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #5
	mov r1, #0x34
	bl AllocFromHeap
	str r0, [r4, #8]
	mov r0, #5
	mov r1, #0x38
	bl AllocFromHeap
	ldr r1, [r4, #8]
	str r0, [r1, #4]
	mov r0, #5
	bl SaveArray_Party_Alloc
	ldr r1, [r4, #8]
	mov r6, #0
	ldr r1, [r1, #4]
	ldr r3, [sp, #4]
	str r0, [r1]
	strb r6, [r4, #0xe]
	str r5, [r4]
	ldr r0, [sp, #4]
	mov r1, #0x65
	ldrb r0, [r0]
	lsl r1, r1, #2
	add r5, r4, #0
	strb r0, [r4, #0xc]
	ldr r0, [sp]
	ldrb r0, [r0, r1]
	add r1, r1, #1
	strb r0, [r4, #0xd]
	ldr r0, [sp]
	ldrb r0, [r0, r1]
	strb r0, [r4, #0xf]
	ldr r0, [sp, #4]
	ldrb r0, [r0, #1]
	strb r0, [r4, #0x14]
	ldr r0, [sp, #4]
	ldrb r0, [r0, #2]
	strb r0, [r4, #0x15]
	ldr r0, [sp, #4]
	ldrb r0, [r0, #3]
	strb r0, [r4, #0x16]
_0224E19A:
	ldr r0, [sp, #4]
	ldr r1, [r4, #8]
	add r7, r0, r6
	ldrb r0, [r7, #4]
	add r1, r1, r6
	mov r2, #0
	strb r0, [r1, #0xc]
_0224E1A8:
	add r0, r3, r2
	ldrb r1, [r0, #8]
	add r0, r5, r2
	add r2, r2, #1
	strb r1, [r0, #0x18]
	cmp r2, #6
	blt _0224E1A8
	add r7, #0x20
	ldrb r1, [r7]
	add r0, r4, r6
	add r0, #0x30
	add r6, r6, #1
	strb r1, [r0]
	add r3, r3, #6
	add r5, r5, #6
	cmp r6, #4
	blt _0224E19A
	ldr r0, [sp]
	add r1, r4, #0
	ldr r0, [r0, #0xc]
	mov r2, #0
	bl sub_0200CA44
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224E1DC
ov11_0224E1DC: ; 0x0224E1DC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	str r1, [sp]
	mov r0, #5
	mov r1, #0x34
	add r7, r2, #0
	bl AllocFromHeap
	add r2, r0, #0
	mov r3, #0
	strb r3, [r2, #0xa]
	str r4, [r2]
	ldrb r0, [r7]
	add r5, r7, #0
	add r6, r2, #0
	strb r0, [r2, #8]
	ldrb r0, [r7, #1]
	strb r0, [r2, #9]
	ldrb r0, [r7, #2]
	strb r0, [r2, #0xb]
	ldr r0, [r7, #0x20]
	str r0, [r2, #0x10]
	ldrb r0, [r7, #3]
	strb r0, [r2, #0x16]
	add r0, r7, #0
	strh r3, [r2, #0x14]
	add r0, #0x24
	ldrb r0, [r0]
	strb r0, [r2, #0x18]
_0224E216:
	add r0, r7, r3
	ldrb r1, [r0, #4]
	add r0, r2, r3
	mov r4, #0
	strb r1, [r0, #0xc]
_0224E220:
	add r0, r5, r4
	ldrb r1, [r0, #8]
	add r0, r6, r4
	add r4, r4, #1
	strb r1, [r0, #0x1c]
	cmp r4, #6
	blt _0224E220
	add r3, r3, #1
	add r5, r5, #6
	add r6, r6, #6
	cmp r3, #4
	blt _0224E216
	ldr r0, [sp]
	add r1, r2, #0
	ldr r0, [r0, #0x10]
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_0224E248
ov11_0224E248: ; 0x0224E248
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #5
	mov r1, #0x1c
	add r4, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #0xe]
	str r6, [r1]
	ldrb r0, [r4]
	strb r0, [r1, #0xc]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	strb r0, [r1, #0xd]
	add r0, r5, #0
	add r0, #0x28
	str r0, [r1, #4]
	ldrh r0, [r4, #2]
	str r0, [r1, #0x10]
	ldrb r0, [r4, #1]
	strb r0, [r1, #0xf]
	ldr r0, [r4, #4]
	strh r0, [r1, #0x18]
	ldr r0, [r4, #8]
	str r0, [r1, #0x14]
	ldr r0, [r5, #0x14]
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224E28C
ov11_0224E28C: ; 0x0224E28C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	bl ov11_022300C8
	str r0, [sp]
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r6, [r4]
	ldrb r0, [r5]
	mov r1, #0x65
	lsl r1, r1, #2
	strb r0, [r4, #4]
	ldrb r0, [r7, r1]
	strb r0, [r4, #5]
	ldrh r2, [r5, #2]
	lsl r0, r2, #1
	add r2, r2, r0
	add r0, sp, #4
	strh r2, [r0, #2]
	mov r2, #2
	strb r2, [r0, #1]
	ldrb r0, [r5, #1]
	ldrb r1, [r7, r1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [sp, #8]
	add r0, r6, #0
	bl ov11_02230E54
	add r3, r0, #0
	ldr r1, [sp]
	add r0, r6, #0
	add r2, sp, #4
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224E2F0 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E2F0: .word ov11_02253008

	thumb_func_start ov11_0224E2F4
ov11_0224E2F4: ; 0x0224E2F4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl ov11_022300C4
	str r0, [sp]
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	add r0, r6, #0
	str r5, [r4]
	add r0, #0x94
	ldrb r0, [r0]
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r7, #0
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224E340 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E340: .word ov11_02253008

	thumb_func_start ov11_0224E344
ov11_0224E344: ; 0x0224E344
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	mov r0, #5
	mov r1, #0x70
	add r5, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	add r0, #0x6a
	strb r1, [r0]
	str r7, [r4]
	add r0, r6, #0
	str r6, [r4, #4]
	add r0, #0x94
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x68
	strb r1, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x69
	strb r1, [r0]
	add r0, r7, #0
	bl ov11_02230070
	add r3, r4, #0
	str r0, [r4, #0xc]
	add r7, r5, #0
	add r3, #0x10
	mov r2, #0xb
_0224E388:
	ldmia r7!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224E388
	ldr r0, [r6, #0x20]
	str r0, [r4, #8]
	ldr r0, [r5, #0x4c]
	cmp r0, #1
	bne _0224E3A8
	ldr r0, [r5, #0x50]
	cmp r0, #0x19
	bne _0224E3A8
	mov r0, #0x1a
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r6, r0]
_0224E3A8:
	ldr r0, [r5, #0x4c]
	cmp r0, #1
	bne _0224E3BC
	ldr r0, [r5, #0x50]
	cmp r0, #0x1a
	bne _0224E3BC
	mov r0, #0x1a
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
_0224E3BC:
	ldrh r0, [r5, #2]
	add r1, r4, #0
	add r1, #0x6c
	str r0, [sp]
	add r0, r4, #0
	ldr r2, [r5, #0x4c]
	ldr r3, [r5, #0x50]
	add r0, #0x6b
	bl ov11_022545B4
	ldr r0, _0224E3DC ; =ov11_02252754
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224E3DC: .word ov11_02252754

	thumb_func_start ov11_0224E3E0
ov11_0224E3E0: ; 0x0224E3E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0xc
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #9]
	str r5, [r1]
	ldr r0, [r4, #0x20]
	str r0, [r1, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	strb r0, [r1, #8]
	ldr r0, _0224E40C ; =ov11_022529C0
	strb r2, [r1, #0xa]
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224E40C: .word ov11_022529C0

	thumb_func_start ov11_0224E410
ov11_0224E410: ; 0x0224E410
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	ldr r0, [r6, #0x2c]
	add r5, r2, #0
	cmp r0, #0
	bne _0224E422
	bl GF_AssertFail
_0224E422:
	add r4, r6, #0
	add r4, #0x28
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MI_CpuFill8
	str r7, [r4, #0xc]
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x4c
	strb r1, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r0, r7, #0
	bl ov11_0222FF74
	add r1, r0, #0
	ldr r0, _0224E490 ; =0x00000195
	ldrb r0, [r6, r0]
	bl ov11_02257F6C
	add r1, r4, #0
	add r1, #0x25
	strb r0, [r1]
	mov r0, #2
	ldrsh r0, [r5, r0]
	str r0, [r4, #0x28]
	ldrh r0, [r5, #4]
	str r0, [r4, #0x2c]
	ldr r0, [r5, #8]
	str r0, [r4, #0x30]
	add r0, r4, #0
	ldrb r1, [r5, #1]
	add r0, #0x48
	strb r1, [r0]
	ldr r1, [r5, #8]
	ldr r0, _0224E494 ; =0x00007FFF
	cmp r1, r0
	bne _0224E480
	mov r0, #0
	str r0, [r4, #0x28]
	str r0, [r4, #0x30]
_0224E480:
	mov r2, #0xfa
	ldr r0, _0224E498 ; =ov11_02252A1C
	add r1, r4, #0
	lsl r2, r2, #2
	bl sub_0200CA44
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224E490: .word 0x00000195
_0224E494: .word 0x00007FFF
_0224E498: .word ov11_02252A1C

	thumb_func_start ov11_0224E49C
ov11_0224E49C: ; 0x0224E49C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	ldr r0, [r6, #0x2c]
	add r5, r2, #0
	cmp r0, #0
	bne _0224E4AE
	bl GF_AssertFail
_0224E4AE:
	add r4, r6, #0
	add r4, #0x28
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl MI_CpuFill8
	str r7, [r4, #0xc]
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x4c
	strb r1, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r2, [r6, r0]
	add r1, r4, #0
	add r1, #0x24
	strb r2, [r1]
	ldr r1, [r5, #4]
	add r0, r0, #1
	str r1, [r4, #0x38]
	ldr r1, [r5, #0xc]
	str r1, [r4, #0x3c]
	ldr r2, [r5, #8]
	ldr r1, [r4, #0x38]
	sub r1, r2, r1
	str r1, [r4, #0x40]
	ldrb r0, [r6, r0]
	cmp r0, #0
	bne _0224E4FA
	mov r2, #0xfa
	ldr r0, _0224E50C ; =ov11_02252A70
	add r1, r4, #0
	lsl r2, r2, #2
	bl sub_0200CA44
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_0224E4FA:
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x24
	add r4, #0x4c
	ldrb r1, [r1]
	ldrb r2, [r4]
	bl ov11_022567B8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224E50C: .word ov11_02252A70

	thumb_func_start ov11_0224E510
ov11_0224E510: ; 0x0224E510
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x74
	str r2, [sp]
	bl AllocFromHeap
	add r1, r0, #0
	ldr r0, _0224E5F0 ; =0x00000195
	ldrb r2, [r4, r0]
	mov r0, #1
	tst r0, r2
	beq _0224E532
	mov r2, #2
	b _0224E534
_0224E532:
	mov r2, #0
_0224E534:
	add r0, r1, #0
	add r0, #0x67
	strb r2, [r0]
	add r0, r1, #0
	mov r2, #0
	add r0, #0x66
	strb r2, [r0]
	str r5, [r1]
	ldr r0, [sp]
	str r4, [r1, #4]
	ldrb r3, [r0]
	add r0, r1, #0
	add r0, #0x64
	strb r3, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r3, [r4, r0]
	add r0, r1, #0
	add r0, #0x65
	strb r3, [r0]
	ldr r0, [r4, #0x20]
	add r7, r1, #0
	str r0, [r1, #8]
	ldr r0, [sp]
	add r5, r1, #0
	ldrh r3, [r0, #2]
	add r0, r1, #0
	add r0, #0x68
	strh r3, [r0]
	ldr r0, [sp]
	ldrb r3, [r0, #1]
	add r0, r1, #0
	add r0, #0x6a
	strb r3, [r0]
	ldr r0, [sp]
	ldrb r3, [r0, #8]
	add r0, r1, #0
	add r0, #0x6b
	strb r3, [r0]
	ldr r0, [sp]
	ldr r0, [r0, #4]
	str r0, [r1, #0x6c]
	ldr r0, [sp]
	ldrb r3, [r0, #9]
	add r0, r1, #0
	add r0, #0x70
	strh r3, [r0]
	ldr r0, [sp]
	ldrb r3, [r0, #0xa]
	add r0, r1, #0
	add r0, #0x72
	strh r3, [r0]
	ldr r3, [sp]
	add r4, r3, #0
_0224E5A0:
	ldrh r0, [r3, #0xc]
	add r3, r3, #2
	strh r0, [r7, #0x24]
	ldr r0, [sp]
	add r7, r7, #2
	add r0, r0, r2
	str r0, [sp, #0x10]
	ldrb r0, [r0, #0x14]
	str r0, [sp, #8]
	add r0, r1, r2
	ldr r6, [sp, #8]
	add r0, #0x2c
	strb r6, [r0]
	ldr r0, [sp, #0x10]
	add r6, r1, r2
	ldrb r0, [r0, #0x18]
	str r6, [sp, #4]
	add r6, #0x30
	str r0, [sp, #0xc]
	strb r0, [r6]
	ldr r0, [sp, #0x10]
	str r6, [sp, #4]
	add r6, r1, r2
	ldrb r0, [r0, #0x1c]
	add r6, #0x34
	add r2, r2, #1
	strb r0, [r6]
	ldr r0, [r4, #0x20]
	add r4, r4, #4
	str r0, [r5, #0x38]
	add r5, r5, #4
	cmp r2, #4
	blt _0224E5A0
	ldr r0, _0224E5F4 ; =ov11_02252B30
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0224E5F0: .word 0x00000195
_0224E5F4: .word ov11_02252B30

	thumb_func_start ov11_0224E5F8
ov11_0224E5F8: ; 0x0224E5F8
	push {r3, r4, r5, lr}
	add r5, r2, #0
	ldr r2, _0224E624 ; =0x00000195
	mov r4, #1
	ldrb r2, [r1, r2]
	tst r2, r4
	beq _0224E60A
	mov r4, #0x75
	b _0224E60C
_0224E60A:
	sub r4, #0x76
_0224E60C:
	mov r2, #0x65
	lsl r2, r2, #2
	ldrb r1, [r1, r2]
	ldrb r2, [r5]
	bl ov11_022567B8
	ldrh r0, [r5, #2]
	add r1, r4, #0
	bl sub_020054A8
	pop {r3, r4, r5, pc}
	nop
_0224E624: .word 0x00000195

	thumb_func_start ov11_0224E628
ov11_0224E628: ; 0x0224E628
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #6]
	add r0, r4, #0
	str r5, [r1]
	add r0, #0x94
	ldrb r0, [r0]
	strb r0, [r1, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	strb r0, [r1, #5]
	ldr r0, _0224E658 ; =ov11_02252DB4
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	nop
_0224E658: .word ov11_02252DB4

	thumb_func_start ov11_0224E65C
ov11_0224E65C: ; 0x0224E65C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x68
	str r2, [sp]
	bl AllocFromHeap
	add r1, r0, #0
	str r5, [r1]
	ldr r0, [sp]
	str r4, [r1, #4]
	ldrb r2, [r0]
	add r0, r1, #0
	add r0, #0x60
	strb r2, [r0]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x61
	strb r2, [r0]
	add r0, r1, #0
	mov r2, #0
	add r0, #0x62
	strb r2, [r0]
	ldr r0, [sp]
	add r7, r1, #0
	ldrb r3, [r0, #1]
	add r0, r1, #0
	add r0, #0x63
	strb r3, [r0]
	ldr r0, [sp]
	ldr r3, [sp]
	ldrb r0, [r0, #2]
	add r4, r3, #0
	add r5, r1, #0
	str r0, [r1, #0x64]
_0224E6AA:
	ldrh r0, [r3, #4]
	add r3, r3, #2
	strh r0, [r7, #0x20]
	ldr r0, [sp]
	add r7, r7, #2
	add r0, r0, r2
	str r0, [sp, #0x10]
	ldrb r0, [r0, #0xc]
	str r0, [sp, #8]
	add r0, r1, r2
	ldr r6, [sp, #8]
	add r0, #0x28
	strb r6, [r0]
	ldr r0, [sp, #0x10]
	add r6, r1, r2
	ldrb r0, [r0, #0x10]
	str r6, [sp, #4]
	add r6, #0x2c
	str r0, [sp, #0xc]
	strb r0, [r6]
	ldr r0, [sp, #0x10]
	str r6, [sp, #4]
	add r6, r1, r2
	ldrb r0, [r0, #0x14]
	add r6, #0x30
	add r2, r2, #1
	strb r0, [r6]
	ldr r0, [r4, #0x18]
	add r4, r4, #4
	str r0, [r5, #0x34]
	add r5, r5, #4
	cmp r2, #4
	blt _0224E6AA
	ldr r0, _0224E6F8 ; =ov11_02252E50
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224E6F8: .word ov11_02252E50

	thumb_func_start ov11_0224E6FC
ov11_0224E6FC: ; 0x0224E6FC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x2c]
	add r4, r2, #0
	cmp r0, #0
	bne _0224E70E
	bl GF_AssertFail
_0224E70E:
	ldrb r1, [r4, #1]
	add r0, r5, #0
	add r0, #0x72
	strb r1, [r0]
	add r0, r5, #0
	mov r2, #1
	ldr r1, [r5, #0x50]
	add r0, #0x28
	lsl r2, r2, #8
	bl ov11_02256D70
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	add r0, r6, #0
	bl ov11_022567B8
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_0224E734
ov11_0224E734: ; 0x0224E734
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r6, r0, #0
	add r7, r2, #0
	bl ov11_02230140
	str r0, [sp, #4]
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r6, [r4]
	ldrb r0, [r7]
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	strb r0, [r4, #5]
	add r0, r6, #0
	bl ov11_02230E54
	str r0, [sp]
	mov r2, #0x65
	lsl r2, r2, #2
	ldrb r2, [r5, r2]
	ldrb r3, [r7, #1]
	ldr r1, [sp, #4]
	add r0, r6, #0
	bl ov11_02231684
	strb r0, [r4, #6]
	ldr r0, _0224E78C ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E78C: .word ov11_02253008

	thumb_func_start ov11_0224E790
ov11_0224E790: ; 0x0224E790
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r3, sp, #4
	add r6, r1, #0
	add r7, r2, #0
	bl ov11_02253B74
	add r0, r5, #0
	bl ov11_022300C4
	str r0, [sp]
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	ldrb r0, [r7]
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	add r2, sp, #4
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224E7E4 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E7E4: .word ov11_02253008

	thumb_func_start ov11_0224E7E8
ov11_0224E7E8: ; 0x0224E7E8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r3, sp, #4
	add r6, r1, #0
	add r7, r2, #0
	bl ov11_02253C48
	add r0, r5, #0
	bl ov11_022300C4
	str r0, [sp]
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	ldrb r0, [r7]
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	add r2, sp, #4
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224E83C ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E83C: .word ov11_02253008

	thumb_func_start ov11_0224E840
ov11_0224E840: ; 0x0224E840
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r2, sp, #0
	add r6, r1, #0
	bl ov11_02253D28
	add r0, r5, #0
	bl ov11_022300C4
	add r7, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	mov r0, #0x22
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, sp, #0
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224E890 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224E890: .word ov11_02253008

	thumb_func_start ov11_0224E894
ov11_0224E894: ; 0x0224E894
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	add r3, sp, #4
	add r6, r1, #0
	add r7, r2, #0
	bl ov11_02253DD4
	add r0, r5, #0
	bl ov11_022300C4
	str r0, [sp]
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	ldrb r0, [r7]
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	ldr r1, [sp]
	add r0, r5, #0
	add r2, sp, #4
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224E8E8 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224E8E8: .word ov11_02253008

	thumb_func_start ov11_0224E8EC
ov11_0224E8EC: ; 0x0224E8EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0xc
	bl AllocFromHeap
	add r1, r0, #0
	add r0, r4, #0
	str r5, [r1]
	add r0, #0x94
	ldrb r0, [r0]
	mov r2, #0
	strb r0, [r1, #8]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	add r4, #0x28
	strb r0, [r1, #9]
	strb r2, [r1, #0xa]
	ldr r0, _0224E920 ; =ov11_02252FBC
	str r4, [r1, #4]
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	nop
_0224E920: .word ov11_02252FBC

	thumb_func_start ov11_0224E924
ov11_0224E924: ; 0x0224E924
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, _0224E9B8 ; =0x00000196
	add r4, r2, #0
	ldrb r2, [r5, r1]
	add r6, r0, #0
	cmp r2, #0
	bne _0224E976
	bl ov11_022300C4
	str r0, [sp]
	mov r0, #5
	mov r1, #0xc
	bl AllocFromHeap
	add r7, r0, #0
	str r6, [r7]
	ldrb r0, [r4]
	strb r0, [r7, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	strb r0, [r7, #5]
	mov r0, #0
	strb r0, [r7, #7]
	add r0, r6, #0
	bl ov11_02230E54
	add r3, r0, #0
	ldr r1, [sp]
	add r0, r6, #0
	add r2, r4, #4
	bl ov11_0223178C
	strb r0, [r7, #6]
	ldr r0, _0224E9BC ; =ov11_0225304C
	add r1, r7, #0
	mov r2, #0
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_0224E976:
	cmp r2, #1
	bne _0224E992
	sub r1, r1, #2
	ldrb r1, [r5, r1]
	bl ov11_02256004
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	add r0, r6, #0
	bl ov11_022567B8
	pop {r3, r4, r5, r6, r7, pc}
_0224E992:
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	bne _0224E9A8
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	add r0, r6, #0
	bl ov11_02256004
_0224E9A8:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	add r0, r6, #0
	bl ov11_022567B8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224E9B8: .word 0x00000196
_0224E9BC: .word ov11_0225304C

	thumb_func_start ov11_0224E9C0
ov11_0224E9C0: ; 0x0224E9C0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r6, #0
	add r4, #0x28
	add r7, r0, #0
	add r5, r2, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #1
	bl MIi_CpuClearFast
	mov r0, #0x65
	str r7, [r4, #0xc]
	lsl r0, r0, #2
	ldrb r1, [r6, r0]
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r0, r7, #0
	bl ov11_0222FF74
	add r1, r0, #0
	ldr r0, _0224EA70 ; =0x00000195
	ldrb r0, [r6, r0]
	bl ov11_02257F6C
	add r1, r4, #0
	add r1, #0x25
	strb r0, [r1]
	add r0, r4, #0
	ldrb r1, [r5]
	add r0, #0x4c
	mov r2, #0
	strb r1, [r0]
	mov r0, #2
	ldrsh r0, [r5, r0]
	str r0, [r4, #0x28]
	ldrh r0, [r5, #4]
	str r0, [r4, #0x2c]
	add r0, r4, #0
	ldrb r1, [r5, #1]
	add r0, #0x48
	strb r1, [r0]
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x1e
	add r0, r4, #0
	add r0, #0x49
	strb r1, [r0]
	str r2, [r4, #0x30]
	ldr r0, [r5, #8]
	sub r2, #0x21
	str r0, [r4, #0x38]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x3c]
	add r0, r4, #0
	ldrb r1, [r5, #6]
	add r0, #0x26
	strb r1, [r0]
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x1b
	add r0, r4, #0
	add r0, #0x4a
	strb r1, [r0]
	ldrb r0, [r5, #7]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x1f
	add r0, r4, #0
	add r0, #0x4b
	strb r1, [r0]
	add r0, r4, #0
	ldr r1, [r5, #0x10]
	add r0, #0x27
	strb r1, [r0]
	ldr r1, [r4, #0x28]
	add r0, r4, #0
	bl ov11_02256D70
	add r1, r4, #0
	ldr r0, [r4, #0xc]
	add r1, #0x24
	add r4, #0x4c
	ldrb r1, [r1]
	ldrb r2, [r4]
	bl ov11_022567B8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224EA70: .word 0x00000195

	thumb_func_start ov11_0224EA74
ov11_0224EA74: ; 0x0224EA74
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r4, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #0xa]
	str r5, [r1]
	ldrb r0, [r4]
	strb r0, [r1, #8]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r1, #9]
	ldrh r0, [r4, #2]
	strh r0, [r1, #0xc]
	ldrb r0, [r4, #1]
	strb r0, [r1, #0xe]
	ldr r0, _0224EAA8 ; =ov11_022533F4
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224EAA8: .word ov11_022533F4

	thumb_func_start ov11_0224EAAC
ov11_0224EAAC: ; 0x0224EAAC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r4, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #0xa]
	str r6, [r1]
	ldr r0, [r5, #0x20]
	str r0, [r1, #4]
	ldrb r0, [r4]
	strb r0, [r1, #8]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	strb r0, [r1, #9]
	ldrb r0, [r4, #1]
	strb r0, [r1, #0xb]
	strb r2, [r1, #0xc]
	ldrb r0, [r4, #2]
	strb r0, [r1, #0xd]
	ldr r0, _0224EAE8 ; =ov11_0225352C
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	nop
_0224EAE8: .word ov11_0225352C

	thumb_func_start ov11_0224EAEC
ov11_0224EAEC: ; 0x0224EAEC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r4, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r0, #0
	strb r0, [r1, #7]
	str r6, [r1]
	ldrb r2, [r4]
	strb r2, [r1, #4]
	mov r2, #0x65
	lsl r2, r2, #2
	ldrb r3, [r5, r2]
	add r2, r2, #1
	strb r3, [r1, #5]
	ldrb r2, [r5, r2]
	strb r2, [r1, #6]
_0224EB16:
	add r2, r4, r0
	ldrb r3, [r2, #2]
	add r2, r1, r0
	add r0, r0, #1
	strb r3, [r2, #8]
	cmp r0, #6
	blt _0224EB16
	ldr r0, _0224EB30 ; =ov11_0225359C
	mov r2, #0
	strb r2, [r1, #0xe]
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224EB30: .word ov11_0225359C

	thumb_func_start ov11_0224EB34
ov11_0224EB34: ; 0x0224EB34
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r6, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #7]
	str r5, [r1]
	ldrb r0, [r6]
	strb r0, [r1, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r3, [r4, r0]
	add r0, r0, #1
	strb r3, [r1, #5]
	ldrb r0, [r4, r0]
	strb r0, [r1, #6]
	ldr r0, _0224EB68 ; =ov11_02253650
	strb r2, [r1, #0xe]
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224EB68: .word ov11_02253650

	thumb_func_start ov11_0224EB6C
ov11_0224EB6C: ; 0x0224EB6C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r4, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r0, #0
	strb r0, [r1, #7]
	str r6, [r1]
	ldrb r2, [r4]
	strb r2, [r1, #4]
	mov r2, #0x65
	lsl r2, r2, #2
	ldrb r3, [r5, r2]
	add r2, r2, #1
	strb r3, [r1, #5]
	ldrb r2, [r5, r2]
	strb r2, [r1, #6]
_0224EB96:
	add r2, r4, r0
	ldrb r3, [r2, #2]
	add r2, r1, r0
	add r0, r0, #1
	strb r3, [r2, #8]
	cmp r0, #6
	blt _0224EB96
	mov r0, #1
	strb r0, [r1, #0xe]
	ldr r0, _0224EBB4 ; =ov11_0225359C
	mov r2, #0
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	nop
_0224EBB4: .word ov11_0225359C

	thumb_func_start ov11_0224EBB8
ov11_0224EBB8: ; 0x0224EBB8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x10
	add r6, r2, #0
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #7]
	str r5, [r1]
	ldrb r0, [r6]
	strb r0, [r1, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r3, [r4, r0]
	add r0, r0, #1
	strb r3, [r1, #5]
	ldrb r0, [r4, r0]
	strb r0, [r1, #6]
	mov r0, #1
	strb r0, [r1, #0xe]
	ldr r0, _0224EBF0 ; =ov11_02253650
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	nop
_0224EBF0: .word ov11_02253650

	thumb_func_start ov11_0224EBF4
ov11_0224EBF4: ; 0x0224EBF4
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r1, #0
	ldr r1, _0224EC44 ; =0x00000196
	add r5, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _0224EC32
	bl ov11_022300C4
	add r1, r0, #0
	ldr r2, _0224EC48 ; =0x0000039B
	add r0, sp, #0
	strh r2, [r0, #2]
	mov r3, #0
	strb r3, [r0, #1]
	add r0, r5, #0
	add r2, sp, #0
	bl ov11_0223178C
	add r0, r5, #0
	mov r1, #0
	bl ov11_0222FF6C
	mov r1, #1
	bl WaitingIcon_New
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_022312C8
_0224EC32:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r5, #0
	mov r2, #0x37
	bl ov11_022567B8
	add sp, #0x24
	pop {r4, r5, pc}
	.align 2, 0
_0224EC44: .word 0x00000196
_0224EC48: .word 0x0000039B

	thumb_func_start ov11_0224EC4C
ov11_0224EC4C: ; 0x0224EC4C
	push {r4, r5, r6, lr}
	sub sp, #0x50
	mov r3, #0x65
	add r4, r1, #0
	lsl r3, r3, #2
	add r6, r2, #0
	ldrb r3, [r4, r3]
	add r1, r6, #0
	add r2, sp, #0
	add r5, r0, #0
	bl ov11_0225452C
	add r0, sp, #0
	mov r1, #5
	bl ov08_0222A494
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	ldrb r2, [r6]
	add r0, r5, #0
	bl ov11_022567B8
	add sp, #0x50
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224EC80
ov11_0224EC80: ; 0x0224EC80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x10
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #0xe]
	str r5, [r1]
	add r0, r4, #0
	str r4, [r1, #4]
	add r0, #0x94
	ldrb r0, [r0]
	strb r0, [r1, #0xc]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	strb r0, [r1, #0xd]
	ldr r0, [r4, #0x20]
	str r0, [r1, #8]
	ldr r0, _0224ECB4 ; =ov11_022536D4
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224ECB4: .word ov11_022536D4

	thumb_func_start ov11_0224ECB8
ov11_0224ECB8: ; 0x0224ECB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #5
	mov r1, #0x10
	bl AllocFromHeap
	add r1, r0, #0
	mov r2, #0
	strb r2, [r1, #0xe]
	str r5, [r1]
	add r0, r4, #0
	str r4, [r1, #4]
	add r0, #0x94
	ldrb r0, [r0]
	strb r0, [r1, #0xc]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	strb r0, [r1, #0xd]
	ldr r0, [r4, #0x20]
	str r0, [r1, #8]
	ldr r0, _0224ECEC ; =ov11_02253720
	bl sub_0200CA44
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224ECEC: .word ov11_02253720

	thumb_func_start ov11_0224ECF0
ov11_0224ECF0: ; 0x0224ECF0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r2, sp, #0
	add r6, r1, #0
	bl ov11_02254108
	add r0, r5, #0
	bl ov11_022300C4
	add r7, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	mov r0, #0x3b
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, sp, #0
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224ED40 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224ED40: .word ov11_02253008

	thumb_func_start ov11_0224ED44
ov11_0224ED44: ; 0x0224ED44
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r3, sp, #0
	add r6, r1, #0
	bl ov11_022541C4
	add r0, r5, #0
	bl ov11_022300C4
	add r7, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	mov r0, #0x3c
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, sp, #0
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224ED94 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224ED94: .word ov11_02253008

	thumb_func_start ov11_0224ED98
ov11_0224ED98: ; 0x0224ED98
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r2, sp, #0
	add r6, r1, #0
	bl ov11_022542B4
	add r0, r5, #0
	bl ov11_022300C4
	add r7, r0, #0
	mov r0, #5
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	str r5, [r4]
	mov r0, #0x3d
	strb r0, [r4, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	strb r0, [r4, #5]
	add r0, r5, #0
	bl ov11_02230E54
	add r3, r0, #0
	add r0, r5, #0
	add r1, r7, #0
	add r2, sp, #0
	bl ov11_0223178C
	strb r0, [r4, #6]
	ldr r0, _0224EDE8 ; =ov11_02253008
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224EDE8: .word ov11_02253008

	thumb_func_start ov11_0224EDEC
ov11_0224EDEC: ; 0x0224EDEC
	push {r4, r5, r6, lr}
	sub sp, #0x50
	mov r3, #0x65
	add r4, r1, #0
	lsl r3, r3, #2
	add r6, r2, #0
	ldrb r3, [r4, r3]
	add r1, r6, #0
	add r2, sp, #0
	add r5, r0, #0
	bl ov11_0225452C
	add r0, sp, #0
	mov r1, #5
	bl ov08_0222A568
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	ldrb r2, [r6]
	add r0, r5, #0
	bl ov11_022567B8
	add sp, #0x50
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224EE20
ov11_0224EE20: ; 0x0224EE20
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	ldr r0, _0224EE70 ; =0x00000195
	mov r1, #1
	ldrb r0, [r5, r0]
	add r4, r2, #0
	tst r0, r1
	beq _0224EE36
	mov r1, #0x75
	b _0224EE38
_0224EE36:
	sub r1, #0x76
_0224EE38:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _0224EE48
	cmp r0, #1
	beq _0224EE58
	cmp r0, #2
	beq _0224EE50
	b _0224EE5E
_0224EE48:
	ldr r0, _0224EE74 ; =0x000006FE
	bl sub_020054A8
	b _0224EE5E
_0224EE50:
	ldr r0, _0224EE78 ; =0x000006FC
	bl sub_020054A8
	b _0224EE5E
_0224EE58:
	ldr r0, _0224EE7C ; =0x000006FD
	bl sub_020054A8
_0224EE5E:
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	add r0, r6, #0
	bl ov11_022567B8
	pop {r4, r5, r6, pc}
	nop
_0224EE70: .word 0x00000195
_0224EE74: .word 0x000006FE
_0224EE78: .word 0x000006FC
_0224EE7C: .word 0x000006FD

	thumb_func_start ov11_0224EE80
ov11_0224EE80: ; 0x0224EE80
	push {r4, r5, r6, lr}
	add r4, r2, #0
	add r6, r0, #0
	ldrh r0, [r4, #2]
	add r5, r1, #0
	bl sub_0200521C
	mov r1, #0x65
	lsl r1, r1, #2
	ldrb r1, [r5, r1]
	ldrb r2, [r4]
	add r0, r6, #0
	bl ov11_022567B8
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_0224EEA0
ov11_0224EEA0: ; 0x0224EEA0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x6c
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	ldrb r1, [r4, #0x12]
	add r5, r0, #0
	cmp r1, #5
	bls _0224EEB8
	b _0224F2C2
_0224EEB8:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224EEC4: ; jump table
	.short _0224EED0 - _0224EEC4 - 2 ; case 0
	.short _0224EEDA - _0224EEC4 - 2 ; case 1
	.short _0224EEE8 - _0224EEC4 - 2 ; case 2
	.short _0224F15E - _0224EEC4 - 2 ; case 3
	.short _0224F1B2 - _0224EEC4 - 2 ; case 4
	.short _0224F1D0 - _0224EEC4 - 2 ; case 5
_0224EED0:
	mov r0, #0x1c
	str r0, [r4, #0x20]
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
_0224EEDA:
	ldr r0, [r4, #0x20]
	sub r0, r0, #1
	str r0, [r4, #0x20]
	bne _0224EFAE
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
_0224EEE8:
	ldrb r0, [r4, #0x13]
	add r1, sp, #0x10
	cmp r0, #2
	ldr r0, [r4, #0xc]
	beq _0224EEF4
	b _0224F040
_0224EEF4:
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0x10
	bl sub_0200C7A0
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	beq _0224EF08
	cmp r0, #3
	bne _0224EF2A
_0224EF08:
	add r1, sp, #0x10
	mov r0, #2
	ldrsh r0, [r1, r0]
	cmp r0, #0xc0
	ldr r0, [r4, #0xc]
	bge _0224EF20
	ldr r0, [r0]
	mov r1, #8
	mov r2, #0
	bl sub_0200C82C
	b _0224EF2A
_0224EF20:
	ldr r0, [r0]
	mov r1, #0xc0
	mov r2, #0x58
	bl sub_0200C714
_0224EF2A:
	ldr r0, [r4, #0xc]
	add r1, sp, #0x10
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0x10
	bl sub_0200C7A0
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	bne _0224EF4E
	add r3, sp, #0x10
	mov r2, #2
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_02007558
	b _0224EF9E
_0224EF4E:
	cmp r0, #3
	bne _0224EF78
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0x10
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r0, r1
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x18
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #8]
	neg r2, r2
	bl sub_020079E0
	b _0224EF9E
_0224EF78:
	cmp r0, #5
	bne _0224EF9E
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0x10
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r1, r0
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x10
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #8]
	bl sub_020079E0
_0224EF9E:
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_0200782C
	mov r1, #0x14
	ldrsh r1, [r4, r1]
	cmp r0, r1
	bge _0224EFB0
_0224EFAE:
	b _0224F2D8
_0224EFB0:
	ldr r0, [r4, #8]
	mov r1, #1
	bl sub_02007314
	ldr r0, [r4, #8]
	mov r1, #0x2c
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #8]
	mov r1, #0x2d
	mov r2, #0
	bl sub_02007558
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_02007558
	ldr r0, [r4]
	bl ov11_02230E80
	ldr r1, [r4, #0x24]
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	ldrb r1, [r4, #0x11]
	str r1, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldrb r3, [r4, #0x13]
	ldr r1, [r4, #8]
	bl sub_02069038
	ldrb r1, [r4, #0x11]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #5
	str r1, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldr r1, [r4, #0x18]
	mov r3, #0x75
	bl sub_02069FB0
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	beq _0224F01C
	cmp r0, #3
	bne _0224F028
_0224F01C:
	ldr r0, [r4, #0xc]
	mov r1, #0xc0
	ldr r0, [r0]
	mov r2, #0x58
	bl sub_0200C714
_0224F028:
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4, #8]
	mov r1, #8
	add r3, r2, #0
	bl sub_02007E68
	ldrb r0, [r4, #0x12]
	add sp, #0x6c
	add r0, r0, #1
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_0224F040:
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0x10
	bl sub_0200C7A0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _0224F054
	cmp r0, #2
	bne _0224F076
_0224F054:
	add r0, sp, #0x10
	mov r1, #2
	ldrsh r0, [r0, r1]
	cmp r0, #0x40
	ldr r0, [r4, #0xc]
	ble _0224F06C
	ldr r0, [r0]
	sub r1, #0xa
	mov r2, #0
	bl sub_0200C82C
	b _0224F076
_0224F06C:
	ldr r0, [r0]
	mov r1, #0x40
	mov r2, #0x88
	bl sub_0200C714
_0224F076:
	ldr r0, [r4, #0xc]
	add r1, sp, #0x10
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0x10
	bl sub_0200C7A0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	bne _0224F09A
	add r3, sp, #0x10
	mov r2, #2
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_02007558
	b _0224F0EA
_0224F09A:
	cmp r0, #2
	bne _0224F0C2
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0x10
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r1, r0
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x18
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #8]
	bl sub_020079E0
	b _0224F0EA
_0224F0C2:
	cmp r0, #4
	bne _0224F0EA
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0x10
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r0, r1
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x10
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #8]
	neg r2, r2
	bl sub_020079E0
_0224F0EA:
	mov r0, #0x14
	ldrsh r5, [r4, r0]
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_0200782C
	cmp r0, r5
	bgt _0224F1C0
	ldr r0, [r4, #8]
	mov r1, #0
	add r2, r5, #0
	bl sub_02007558
	ldr r0, [r4]
	bl ov11_02230E80
	ldr r1, [r4, #0x24]
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	ldrb r1, [r4, #0x11]
	str r1, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldrb r3, [r4, #0x13]
	ldr r1, [r4, #8]
	bl sub_02069038
	ldrb r1, [r4, #0x11]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #5
	str r3, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldr r1, [r4, #0x18]
	sub r3, #0x7a
	bl sub_02069FB0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _0224F148
	cmp r0, #2
	bne _0224F154
_0224F148:
	ldr r0, [r4, #0xc]
	mov r1, #0x40
	ldr r0, [r0]
	mov r2, #0x88
	bl sub_0200C714
_0224F154:
	ldrb r0, [r4, #0x12]
	add sp, #0x6c
	add r0, r0, #1
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_0224F15E:
	ldr r0, [r4]
	bl ov11_02230E80
	ldrb r1, [r4, #0x11]
	bl sub_02014D7C
	cmp r0, #1
	bne _0224F1C0
	ldr r0, [r4, #8]
	bl sub_02007390
	cmp r0, #0
	bne _0224F1C0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0224F1AA
	ldrb r1, [r4, #0x11]
	mov r0, #0xb
	add r2, sp, #0x14
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x14
	bl ov11_02254404
	mov r0, #4
	add sp, #0x6c
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_0224F1AA:
	mov r0, #0xff
	add sp, #0x6c
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_0224F1B2:
	bl ov08_02212384
	add r0, r5, #0
	bl ov08_022123A0
	cmp r0, #0
	beq _0224F1C2
_0224F1C0:
	b _0224F2D8
_0224F1C2:
	add r0, r5, #0
	bl ov08_022123B0
	mov r0, #0xff
	add sp, #0x6c
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_0224F1D0:
	ldrb r5, [r4, #0x13]
	cmp r5, #2
	bne _0224F25E
	ldr r0, [r4, #8]
	mov r1, #1
	bl sub_02007314
	ldr r0, [r4, #8]
	mov r1, #0x2c
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #8]
	mov r1, #0x2d
	mov r2, #0
	bl sub_02007558
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_02007558
	ldr r0, [r4]
	bl ov11_02230E80
	ldr r1, [r4, #0x24]
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	ldrb r1, [r4, #0x11]
	str r1, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldrb r3, [r4, #0x13]
	ldr r1, [r4, #8]
	bl sub_02069038
	ldrb r1, [r4, #0x11]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #5
	str r1, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldr r1, [r4, #0x18]
	mov r3, #0x75
	bl sub_02069FB0
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	beq _0224F242
	cmp r0, #3
	bne _0224F24E
_0224F242:
	ldr r0, [r4, #0xc]
	mov r1, #0xc0
	ldr r0, [r0]
	mov r2, #0x58
	bl sub_0200C714
_0224F24E:
	mov r2, #0
	str r2, [sp]
	ldr r0, [r4, #8]
	mov r1, #8
	add r3, r2, #0
	bl sub_02007E68
	b _0224F2BA
_0224F25E:
	ldr r0, [r4]
	bl ov11_02230E80
	ldr r1, [r4, #0x24]
	add r3, r5, #0
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	ldrb r1, [r4, #0x11]
	str r1, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldr r1, [r4, #8]
	bl sub_02069038
	ldrb r1, [r4, #0x11]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #5
	str r3, [sp, #8]
	ldrh r2, [r4, #0x16]
	ldr r1, [r4, #0x18]
	sub r3, #0x7a
	bl sub_02069FB0
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	ldr r0, [r4, #8]
	mov r1, #0
	bl sub_02007558
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _0224F2AE
	cmp r0, #2
	bne _0224F2BA
_0224F2AE:
	ldr r0, [r4, #0xc]
	mov r1, #0x40
	ldr r0, [r0]
	mov r2, #0x88
	bl sub_0200C714
_0224F2BA:
	mov r0, #3
	add sp, #0x6c
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_0224F2C2:
	ldrb r1, [r4, #0x11]
	ldrb r2, [r4, #0x10]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_0224F2D8:
	add sp, #0x6c
	pop {r3, r4, r5, r6, pc}

	thumb_func_start ov11_0224F2DC
ov11_0224F2DC: ; 0x0224F2DC
	push {r4, r5, lr}
	sub sp, #0x9c
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	cmp r0, #7
	bls _0224F2F0
	b _0224F7A2
_0224F2F0:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224F2FC: ; jump table
	.short _0224F30C - _0224F2FC - 2 ; case 0
	.short _0224F322 - _0224F2FC - 2 ; case 1
	.short _0224F366 - _0224F2FC - 2 ; case 2
	.short _0224F4B0 - _0224F2FC - 2 ; case 3
	.short _0224F4CC - _0224F2FC - 2 ; case 4
	.short _0224F6E2 - _0224F2FC - 2 ; case 5
	.short _0224F6F6 - _0224F2FC - 2 ; case 6
	.short _0224F77C - _0224F2FC - 2 ; case 7
_0224F30C:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x96
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x83
	strb r1, [r0]
_0224F322:
	add r1, sp, #0x38
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r4, #0
	add r0, #0x82
	ldrb r0, [r0]
	add r1, r4, #0
	add r2, r4, #0
	str r0, [sp, #0x38]
	add r1, #0x81
	add r2, #0x8c
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_02230014
	str r0, [sp, #0x40]
	mov r0, #5
	add r1, sp, #0x38
	bl ov08_02228218
	str r0, [r4, #8]
	bl ov08_02228524
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x9c
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F366:
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A80
	cmp r0, #0
	bne _0224F3AE
	ldr r0, [r4, #8]
	bl ov08_02228570
	cmp r0, #1
	bne _0224F3AE
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A00
	cmp r0, #1
	bne _0224F3AE
	add r0, r4, #0
	add r0, #0x82
	ldrb r0, [r0]
	cmp r0, #4
	bne _0224F3B8
	add r0, r4, #0
	add r0, #0x96
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x96
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x96
	ldrb r0, [r0]
	cmp r0, #0xc
	bhs _0224F3B0
_0224F3AE:
	b _0224F7C0
_0224F3B0:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x96
	strb r1, [r0]
_0224F3B8:
	ldr r0, [r4]
	bl ov11_02230068
	add r1, r4, #0
	add r1, #0x86
	add r5, r0, #0
	ldrh r1, [r1]
	add r0, sp, #0x24
	bl sub_02069010
	add r0, r4, #0
	add r0, #0x82
	ldrb r3, [r0]
	mov r0, #6
	add r2, r4, #0
	add r1, r3, #0
	mul r1, r0
	ldr r0, _0224F690 ; =ov08_0222D552
	add r2, #0x14
	ldrsh r0, [r0, r1]
	str r0, [sp]
	ldr r0, _0224F694 ; =ov08_0222D554
	ldrsh r0, [r0, r1]
	add r1, r5, #0
	lsl r5, r3, #2
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x85
	ldrb r0, [r0]
	ldr r3, _0224F698 ; =ov08_0222D538
	str r0, [sp, #8]
	mov r0, #0x90
	ldrsb r0, [r4, r0]
	ldrsh r3, [r3, r5]
	str r0, [sp, #0xc]
	mov r0, #0x91
	ldrsb r0, [r4, r0]
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0x93
	ldrb r0, [r0]
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0x81
	ldrb r0, [r0]
	str r0, [sp, #0x18]
	add r0, sp, #0x24
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [r4]
	bl ov11_02253A88
	ldr r1, [r4, #4]
	mov r2, #0
	str r0, [r1, #0x20]
	ldr r0, [r4, #4]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #0xd
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #0x2c
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #6
	ldr r0, [r0, #0x20]
	mov r2, #1
	bl sub_02007558
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	mov r3, #0
	lsl r1, r0, #1
	ldr r0, _0224F69C ; =ov11_0225E84A
	ldrh r0, [r0, r1]
	mov r1, #0x10
	add r2, r1, #0
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007E68
	ldr r0, [r4, #4]
	mov r1, #6
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #8]
	bl ov08_022285A4
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	cmp r0, #2
	ldr r0, _0224F6A0 ; =0x00000706
	bne _0224F498
	mov r1, #0x75
	bl sub_020054A8
	b _0224F4A0
_0224F498:
	mov r1, #0x74
	mvn r1, r1
	bl sub_020054A8
_0224F4A0:
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x9c
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F4B0:
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_022299E8
	cmp r0, #1
	beq _0224F4CC
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x83
	strb r1, [r0]
_0224F4CC:
	ldr r0, [r4, #4]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	bl sub_0200782C
	mov r1, #1
	lsl r1, r1, #8
	cmp r0, r1
	bne _0224F5B2
	ldr r0, [r4, #8]
	bl ov08_022285B4
	cmp r0, #0
	bne _0224F5B2
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	cmp r0, #2
	bne _0224F534
	ldr r0, [r4, #4]
	mov r1, #1
	ldr r0, [r0, #0x20]
	bl sub_02007314
	ldr r0, [r4, #4]
	mov r1, #0x2d
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #5
	add r2, r4, #0
	str r1, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	mov r3, #0x75
	bl sub_02069FB0
	b _0224F55E
_0224F534:
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #5
	add r2, r4, #0
	str r3, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	sub r3, #0x7a
	bl sub_02069FB0
_0224F55E:
	ldr r0, [r4]
	bl ov11_02230E80
	add r1, r4, #0
	add r1, #0x8d
	ldrb r1, [r1]
	add r2, r4, #0
	add r3, r4, #0
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	add r2, #0x86
	add r3, #0x84
	str r1, [sp, #8]
	ldr r1, [r4, #4]
	ldrh r2, [r2]
	ldrb r3, [r3]
	ldr r1, [r1, #0x20]
	bl sub_02069038
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	mov r2, #0
	add r3, r2, #0
	lsl r1, r0, #1
	ldr r0, _0224F69C ; =ov11_0225E84A
	ldrh r0, [r0, r1]
	mov r1, #0x10
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007E68
	mov r0, #5
	add r4, #0x83
	add sp, #0x9c
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F5B2:
	ldr r0, [r4, #4]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	bl sub_0200782C
	mov r2, #1
	lsl r2, r2, #8
	cmp r0, r2
	ldr r0, [r4, #4]
	blt _0224F6BC
	ldr r0, [r0, #0x20]
	mov r1, #0xc
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r0, #0x20]
	add r2, #0xf3
	bl sub_02007558
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	cmp r0, #2
	bne _0224F628
	ldr r0, [r4, #4]
	mov r1, #1
	ldr r0, [r0, #0x20]
	bl sub_02007314
	ldr r0, [r4, #4]
	mov r1, #0x2d
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #5
	add r2, r4, #0
	str r1, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	mov r3, #0x75
	bl sub_02069FB0
	b _0224F652
_0224F628:
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #5
	add r2, r4, #0
	str r3, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	sub r3, #0x7a
	bl sub_02069FB0
_0224F652:
	ldr r0, [r4]
	bl ov11_02230E80
	add r1, r4, #0
	add r1, #0x8d
	ldrb r1, [r1]
	add r2, r4, #0
	add r3, r4, #0
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	add r2, #0x86
	add r3, #0x84
	str r1, [sp, #8]
	ldr r1, [r4, #4]
	ldrh r2, [r2]
	ldrb r3, [r3]
	ldr r1, [r1, #0x20]
	bl sub_02069038
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	mov r2, #0
	mov r3, #1
	lsl r1, r0, #1
	ldr r0, _0224F69C ; =ov11_0225E84A
	b _0224F6A4
	.align 2, 0
_0224F690: .word ov08_0222D552
_0224F694: .word ov08_0222D554
_0224F698: .word ov08_0222D538
_0224F69C: .word ov11_0225E84A
_0224F6A0: .word 0x00000706
_0224F6A4:
	ldrh r0, [r0, r1]
	mov r1, #0x10
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007E68
	mov r0, #5
	add r4, #0x83
	add sp, #0x9c
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F6BC:
	ldr r0, [r0, #0x20]
	mov r1, #0xc
	mov r2, #0x20
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0xd
	ldr r0, [r0, #0x20]
	mov r2, #0x20
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0x90
	ldrsb r1, [r4, r1]
	ldr r0, [r0, #0x20]
	bl sub_02007F34
	add sp, #0x9c
	pop {r4, r5, pc}
_0224F6E2:
	ldr r0, [r4, #8]
	bl ov08_022285B4
	cmp r0, #0
	bne _0224F7C0
	mov r0, #6
	add r4, #0x83
	add sp, #0x9c
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F6F6:
	ldr r0, [r4]
	bl ov11_02230E80
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	bl sub_02014D7C
	cmp r0, #1
	bne _0224F7C0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007390
	cmp r0, #0
	bne _0224F7C0
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A2C
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x88
	str r1, [r0]
	ldr r0, [r4, #8]
	bl ov08_02228618
	add r0, r4, #0
	add r0, #0x92
	ldrb r0, [r0]
	cmp r0, #0
	beq _0224F772
	mov r0, #5
	bl ov08_02211F5C
	str r0, [r4, #0x24]
	add r0, r4, #0
	add r0, #0x81
	ldrb r1, [r0]
	mov r0, #0xb
	add r2, sp, #0x44
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0x24]
	add r3, sp, #0x44
	bl ov11_02254404
	mov r0, #7
	add r4, #0x83
	add sp, #0x9c
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F772:
	mov r0, #0xff
	add r4, #0x83
	add sp, #0x9c
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F77C:
	ldr r0, [r4, #0x24]
	bl ov08_02212384
	ldr r0, [r4, #0x24]
	bl ov08_022123A0
	cmp r0, #0
	bne _0224F7C0
	ldr r0, [r4, #0x24]
	bl ov08_022123B0
	ldr r0, [r4, #0x24]
	bl ov08_02212024
	mov r0, #0xff
	add r4, #0x83
	add sp, #0x9c
	strb r0, [r4]
	pop {r4, r5, pc}
_0224F7A2:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x81
	add r2, #0x80
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0224F7C0:
	add sp, #0x9c
	pop {r4, r5, pc}

	thumb_func_start ov11_0224F7C4
ov11_0224F7C4: ; 0x0224F7C4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c4
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r1, r4, #0
	add r1, #0x83
	ldrb r1, [r1]
	add r5, r0, #0
	cmp r1, #0xb
	bls _0224F7E0
	b _0224FD68
_0224F7E0:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224F7EC: ; jump table
	.short _0224F804 - _0224F7EC - 2 ; case 0
	.short _0224F90C - _0224F7EC - 2 ; case 1
	.short _0224F958 - _0224F7EC - 2 ; case 2
	.short _0224F9E2 - _0224F7EC - 2 ; case 3
	.short _0224F9FA - _0224F7EC - 2 ; case 4
	.short _0224FC14 - _0224F7EC - 2 ; case 5
	.short _0224FC28 - _0224F7EC - 2 ; case 6
	.short _0224FC9C - _0224F7EC - 2 ; case 7
	.short _0224FCC0 - _0224F7EC - 2 ; case 8
	.short _0224FC9C - _0224F7EC - 2 ; case 9
	.short _0224FD0C - _0224F7EC - 2 ; case 10
	.short _0224FC9C - _0224F7EC - 2 ; case 11
_0224F804:
	add r0, r4, #0
	add r0, #0x82
	ldrb r1, [r0]
	ldr r0, _0224FB58 ; =ov11_0225E818
	ldrb r0, [r0, r1]
	str r0, [sp, #0x44]
	mov r0, #5
	str r0, [sp, #0x48]
	add r0, r4, #0
	add r0, #0x81
	ldrb r0, [r0]
	str r0, [sp, #0x50]
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	str r0, [sp, #0x54]
	ldr r0, [r4]
	bl ov11_02230078
	str r0, [sp, #0x60]
	ldr r0, [r4]
	bl ov11_022300CC
	str r0, [sp, #0x64]
	mov r2, #1
	mov r1, #0
	add r0, r4, #0
	str r2, [sp, #0x58]
	str r1, [sp, #0x5c]
	add r0, #0x94
	ldrh r0, [r0]
	cmp r0, #1
	bne _0224F84A
	str r2, [sp, #0x4c]
	b _0224F84C
_0224F84A:
	str r1, [sp, #0x4c]
_0224F84C:
	add r0, sp, #0x44
	bl ov08_02229918
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_02230068
	add r1, r4, #0
	add r1, #0x86
	add r5, r0, #0
	ldrh r1, [r1]
	add r0, sp, #0x30
	bl sub_02069010
	add r0, r4, #0
	add r0, #0x82
	ldrb r3, [r0]
	mov r0, #6
	add r2, r4, #0
	add r1, r3, #0
	mul r1, r0
	ldr r0, _0224FB5C ; =ov08_0222D552
	add r2, #0x14
	ldrsh r0, [r0, r1]
	str r0, [sp]
	ldr r0, _0224FB60 ; =ov08_0222D554
	ldrsh r0, [r0, r1]
	add r1, r5, #0
	lsl r5, r3, #2
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x85
	ldrb r0, [r0]
	ldr r3, _0224FB64 ; =ov08_0222D538
	str r0, [sp, #8]
	mov r0, #0x90
	ldrsb r0, [r4, r0]
	ldrsh r3, [r3, r5]
	str r0, [sp, #0xc]
	mov r0, #0x91
	ldrsb r0, [r4, r0]
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0x93
	ldrb r0, [r0]
	str r0, [sp, #0x14]
	add r0, r4, #0
	add r0, #0x81
	ldrb r0, [r0]
	str r0, [sp, #0x18]
	add r0, sp, #0x30
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [r4]
	bl ov11_02253A88
	ldr r1, [r4, #4]
	mov r2, #0
	str r0, [r1, #0x20]
	ldr r0, [r4, #4]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #0xd
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #0x2c
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #6
	ldr r0, [r0, #0x20]
	mov r2, #1
	bl sub_02007558
	ldr r0, [r4]
	mov r1, #5
	bl ov08_0221590C
	str r0, [r4, #0x10]
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x1c4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224F90C:
	add r1, sp, #0x24
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r0, r4, #0
	add r0, #0x82
	ldrb r0, [r0]
	add r1, r4, #0
	add r2, r4, #0
	str r0, [sp, #0x24]
	add r1, #0x81
	add r2, #0x8c
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_02230014
	str r0, [sp, #0x2c]
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	add r1, sp, #0x24
	str r0, [sp, #0x28]
	mov r0, #5
	bl ov08_02228218
	str r0, [r4, #8]
	bl ov08_02228524
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x1c4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224F958:
	ldr r0, [r4, #0xc]
	bl ov08_02229A80
	cmp r0, #0
	beq _0224F96C
	add r0, r4, #0
	add r0, #0x94
	ldrh r0, [r0]
	cmp r0, #0
	beq _0224F980
_0224F96C:
	ldr r0, [r4, #8]
	bl ov08_02228570
	cmp r0, #1
	bne _0224F980
	ldr r0, [r4, #0xc]
	bl ov08_02229A00
	cmp r0, #1
	beq _0224F982
_0224F980:
	b _0224FD86
_0224F982:
	ldr r0, [r4, #0x10]
	bl ov08_02215918
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	mov r3, #0
	lsl r1, r0, #1
	ldr r0, _0224FB68 ; =ov11_0225E84A
	ldrh r0, [r0, r1]
	mov r1, #0x10
	add r2, r1, #0
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007E68
	ldr r0, [r4, #4]
	mov r1, #6
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #8]
	bl ov08_022285A4
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	cmp r0, #2
	ldr r0, _0224FB6C ; =0x00000706
	bne _0224F9CA
	mov r1, #0x75
	bl sub_020054A8
	b _0224F9D2
_0224F9CA:
	mov r1, #0x74
	mvn r1, r1
	bl sub_020054A8
_0224F9D2:
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x1c4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224F9E2:
	ldr r0, [r4, #0xc]
	bl ov08_022299E8
	cmp r0, #1
	beq _0224F9FA
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x83
	strb r1, [r0]
_0224F9FA:
	ldr r0, [r4, #4]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	bl sub_0200782C
	mov r1, #1
	lsl r1, r1, #8
	cmp r0, r1
	bne _0224FAE0
	ldr r0, [r4, #8]
	bl ov08_022285B4
	cmp r0, #0
	bne _0224FAE0
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	cmp r0, #2
	bne _0224FA62
	ldr r0, [r4, #4]
	mov r1, #1
	ldr r0, [r0, #0x20]
	bl sub_02007314
	ldr r0, [r4, #4]
	mov r1, #0x2d
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #5
	add r2, r4, #0
	str r1, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	mov r3, #0x75
	bl sub_02069FB0
	b _0224FA8C
_0224FA62:
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #5
	add r2, r4, #0
	str r3, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	sub r3, #0x7a
	bl sub_02069FB0
_0224FA8C:
	ldr r0, [r4]
	bl ov11_02230E80
	add r1, r4, #0
	add r1, #0x8d
	ldrb r1, [r1]
	add r2, r4, #0
	add r3, r4, #0
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	add r2, #0x86
	add r3, #0x84
	str r1, [sp, #8]
	ldr r1, [r4, #4]
	ldrh r2, [r2]
	ldrb r3, [r3]
	ldr r1, [r1, #0x20]
	bl sub_02069038
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	mov r2, #0
	add r3, r2, #0
	lsl r1, r0, #1
	ldr r0, _0224FB68 ; =ov11_0225E84A
	ldrh r0, [r0, r1]
	mov r1, #0x10
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007E68
	mov r0, #5
	add r4, #0x83
	add sp, #0x1c4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FAE0:
	ldr r0, [r4, #4]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	bl sub_0200782C
	mov r2, #1
	lsl r2, r2, #8
	cmp r0, r2
	ldr r0, [r4, #4]
	blt _0224FBEE
	ldr r0, [r0, #0x20]
	mov r1, #0xc
	bl sub_02007558
	ldr r0, [r4, #4]
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r0, #0x20]
	add r2, #0xf3
	bl sub_02007558
	add r0, r4, #0
	add r0, #0x84
	ldrb r0, [r0]
	cmp r0, #2
	bne _0224FB70
	ldr r0, [r4, #4]
	mov r1, #1
	ldr r0, [r0, #0x20]
	bl sub_02007314
	ldr r0, [r4, #4]
	mov r1, #0x2d
	ldr r0, [r0, #0x20]
	mov r2, #0
	bl sub_02007558
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #5
	add r2, r4, #0
	str r1, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	mov r3, #0x75
	bl sub_02069FB0
	b _0224FB9A
	nop
_0224FB58: .word ov11_0225E818
_0224FB5C: .word ov08_0222D552
_0224FB60: .word ov08_0222D554
_0224FB64: .word ov08_0222D538
_0224FB68: .word ov11_0225E84A
_0224FB6C: .word 0x00000706
_0224FB70:
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r3, #5
	add r2, r4, #0
	str r3, [sp, #8]
	add r1, r4, #0
	add r2, #0x86
	add r1, #0x88
	ldrh r2, [r2]
	ldr r1, [r1]
	sub r3, #0x7a
	bl sub_02069FB0
_0224FB9A:
	ldr r0, [r4]
	bl ov11_02230E80
	add r1, r4, #0
	add r1, #0x8d
	ldrb r1, [r1]
	add r2, r4, #0
	add r3, r4, #0
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	add r2, #0x86
	add r3, #0x84
	str r1, [sp, #8]
	ldr r1, [r4, #4]
	ldrh r2, [r2]
	ldrb r3, [r3]
	ldr r1, [r1, #0x20]
	bl sub_02069038
	add r0, r4, #0
	add r0, #0x8e
	ldrh r0, [r0]
	mov r2, #0
	mov r3, #1
	lsl r1, r0, #1
	ldr r0, _0224FD8C ; =ov11_0225E84A
	ldrh r0, [r0, r1]
	mov r1, #0x10
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007E68
	mov r0, #5
	add r4, #0x83
	add sp, #0x1c4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FBEE:
	ldr r0, [r0, #0x20]
	mov r1, #0xc
	mov r2, #0x20
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0xd
	ldr r0, [r0, #0x20]
	mov r2, #0x20
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0x90
	ldrsb r1, [r4, r1]
	ldr r0, [r0, #0x20]
	bl sub_02007F34
	add sp, #0x1c4
	pop {r3, r4, r5, r6, pc}
_0224FC14:
	ldr r0, [r4, #8]
	bl ov08_022285B4
	cmp r0, #0
	bne _0224FC48
	mov r0, #6
	add r4, #0x83
	add sp, #0x1c4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FC28:
	ldr r0, [r4]
	bl ov11_02230E80
	add r1, r4, #0
	add r1, #0x81
	ldrb r1, [r1]
	bl sub_02014D7C
	cmp r0, #1
	bne _0224FC48
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	bl sub_02007390
	cmp r0, #0
	beq _0224FC4A
_0224FC48:
	b _0224FD86
_0224FC4A:
	ldr r0, [r4, #0xc]
	bl ov08_02229A2C
	ldr r0, [r4, #8]
	bl ov08_02228618
	add r0, r4, #0
	add r0, #0x92
	ldrb r0, [r0]
	cmp r0, #0
	beq _0224FC92
	add r0, r4, #0
	add r0, #0x81
	ldrb r1, [r0]
	mov r0, #0xb
	add r2, sp, #0x16c
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x16c
	bl ov11_02254404
	mov r0, #7
	add r4, #0x83
	add sp, #0x1c4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FC92:
	mov r0, #8
	add r4, #0x83
	add sp, #0x1c4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FC9C:
	bl ov08_02212384
	add r0, r5, #0
	bl ov08_022123A0
	cmp r0, #0
	bne _0224FD86
	add r0, r5, #0
	bl ov08_022123B0
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x1c4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FCC0:
	add r0, r4, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	beq _0224FD02
	add r0, r4, #0
	add r0, #0x81
	ldrb r1, [r0]
	mov r0, #0xf
	add r2, sp, #0x114
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x114
	bl ov11_02254404
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x1c4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FD02:
	mov r0, #0xff
	add r4, #0x83
	add sp, #0x1c4
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FD0C:
	add r3, r4, #0
	add r3, #0x81
	ldrb r3, [r3]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x28
	add r2, sp, #0xc4
	bl ov11_0225452C
	add r0, sp, #0xc4
	mov r1, #5
	bl ov08_0222A568
	add r0, r4, #0
	add r0, #0x81
	ldrb r1, [r0]
	mov r0, #0x10
	add r2, sp, #0x6c
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x6c
	bl ov11_02254404
	mov r0, #0x1a
	ldr r1, [r4, #4]
	mov r2, #1
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x83
	ldrb r0, [r0]
	add r4, #0x83
	add sp, #0x1c4
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, r6, pc}
_0224FD68:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x81
	add r2, #0x80
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_0224FD86:
	add sp, #0x1c4
	pop {r3, r4, r5, r6, pc}
	nop
_0224FD8C: .word ov11_0225E84A

	thumb_func_start ov11_0224FD90
ov11_0224FD90: ; 0x0224FD90
	push {r4, r5, r6, lr}
	sub sp, #0x138
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r1, r4, #0
	add r1, #0x6b
	ldrb r1, [r1]
	add r5, r0, #0
	cmp r1, #8
	bhi _0224FE7A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224FDB6: ; jump table
	.short _0224FDC8 - _0224FDB6 - 2 ; case 0
	.short _0224FE6C - _0224FDB6 - 2 ; case 1
	.short _0224FE10 - _0224FDB6 - 2 ; case 2
	.short _0224FE6C - _0224FDB6 - 2 ; case 3
	.short _0224FE92 - _0224FDB6 - 2 ; case 4
	.short _0224FF36 - _0224FDB6 - 2 ; case 5
	.short _0224FF50 - _0224FDB6 - 2 ; case 6
	.short _0224FFA6 - _0224FDB6 - 2 ; case 7
	.short _0224FFC0 - _0224FDB6 - 2 ; case 8
_0224FDC8:
	ldr r0, [r4, #0x70]
	cmp r0, #0
	beq _0224FE06
	add r0, r4, #0
	add r0, #0x69
	ldrb r1, [r0]
	mov r0, #0xf
	add r2, sp, #0xe0
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0xe0
	bl ov11_02254404
	add r0, r4, #0
	add r0, #0x6b
	ldrb r0, [r0]
	add r4, #0x6b
	add sp, #0x138
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FE06:
	mov r0, #4
	add r4, #0x6b
	add sp, #0x138
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FE10:
	add r3, r4, #0
	add r3, #0x69
	ldrb r3, [r3]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x10
	add r2, sp, #0x90
	bl ov11_0225452C
	add r0, sp, #0x90
	mov r1, #5
	bl ov08_0222A494
	add r0, r4, #0
	add r0, #0x69
	ldrb r1, [r0]
	mov r0, #0x10
	add r2, sp, #0x38
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x38
	bl ov11_02254404
	mov r0, #0x1a
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x6b
	ldrb r0, [r0]
	add r4, #0x6b
	add sp, #0x138
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FE6C:
	bl ov08_02212384
	add r0, r5, #0
	bl ov08_022123A0
	cmp r0, #0
	beq _0224FE7C
_0224FE7A:
	b _0224FFDE
_0224FE7C:
	add r0, r5, #0
	bl ov08_022123B0
	add r0, r4, #0
	add r0, #0x6b
	ldrb r0, [r0]
	add r4, #0x6b
	add sp, #0x138
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FE92:
	add r0, r4, #0
	add r0, #0x6a
	ldrb r1, [r0]
	mov r0, #1
	tst r0, r1
	beq _0224FEDA
	ldr r0, _0224FFE4 ; =ov11_0225E818
	ldrb r0, [r0, r1]
	str r0, [sp, #0x10]
	mov r0, #5
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r0, #0x69
	ldrb r0, [r0]
	str r0, [sp, #0x1c]
	add r0, r4, #0
	add r0, #0x6e
	ldrh r0, [r0]
	str r0, [sp, #0x20]
	ldr r0, [r4]
	bl ov11_02230078
	str r0, [sp, #0x2c]
	ldr r0, [r4]
	bl ov11_022300CC
	str r0, [sp, #0x30]
	mov r0, #1
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x28]
	add r0, sp, #0x10
	bl ov08_02229918
	str r0, [r4, #0xc]
_0224FEDA:
	add r0, r4, #0
	mov r1, #5
	add r0, #0x6b
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x6e
	ldrh r0, [r0]
	mov r2, #0x10
	lsl r1, r0, #1
	ldr r0, _0224FFE8 ; =ov11_0225E84A
	ldrh r0, [r0, r1]
	mov r1, #0
	add r3, r1, #0
	str r0, [sp]
	ldr r0, [r4, #8]
	bl sub_02007E68
	add r4, #0x6a
	ldrb r0, [r4]
	cmp r0, #5
	bhi _0224FFDE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224FF10: ; jump table
	.short _0224FF1C - _0224FF10 - 2 ; case 0
	.short _0224FF2A - _0224FF10 - 2 ; case 1
	.short _0224FF1C - _0224FF10 - 2 ; case 2
	.short _0224FF2A - _0224FF10 - 2 ; case 3
	.short _0224FF1C - _0224FF10 - 2 ; case 4
	.short _0224FF2A - _0224FF10 - 2 ; case 5
_0224FF1C:
	mov r1, #0x74
	ldr r0, _0224FFEC ; =0x00000706
	mvn r1, r1
	bl sub_020054A8
	add sp, #0x138
	pop {r4, r5, r6, pc}
_0224FF2A:
	ldr r0, _0224FFEC ; =0x00000706
	mov r1, #0x75
	bl sub_020054A8
	add sp, #0x138
	pop {r4, r5, r6, pc}
_0224FF36:
	ldr r0, [r4, #8]
	bl sub_02007F20
	cmp r0, #0
	bne _0224FFDE
	add r0, r4, #0
	add r0, #0x6b
	ldrb r0, [r0]
	add r4, #0x6b
	add sp, #0x138
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FF50:
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #8]
	sub r2, #0x2c
	bl sub_020079E0
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #8]
	sub r2, #0x2d
	bl sub_020079E0
	add r1, r4, #0
	add r1, #0x6c
	ldrb r1, [r1]
	ldr r0, [r4, #8]
	bl sub_02007F34
	ldr r0, [r4, #8]
	mov r1, #0xc
	bl sub_0200782C
	cmp r0, #0
	bgt _0224FFDE
	ldr r0, [r4, #8]
	bl sub_02007534
	add r0, r4, #0
	add r0, #0x6a
	ldrb r1, [r0]
	mov r0, #1
	tst r0, r1
	beq _0224FF9C
	mov r0, #7
	add r4, #0x6b
	add sp, #0x138
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FF9C:
	mov r0, #8
	add r4, #0x6b
	add sp, #0x138
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FFA6:
	ldr r0, [r4, #0xc]
	bl ov08_022299E8
	cmp r0, #0
	bne _0224FFDE
	ldr r0, [r4, #0xc]
	bl ov08_02229A2C
	mov r0, #8
	add r4, #0x6b
	add sp, #0x138
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_0224FFC0:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x69
	add r2, #0x68
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_0224FFDE:
	add sp, #0x138
	pop {r4, r5, r6, pc}
	nop
_0224FFE4: .word ov11_0225E818
_0224FFE8: .word ov11_0225E84A
_0224FFEC: .word 0x00000706

	thumb_func_start ov11_0224FFF0
ov11_0224FFF0: ; 0x0224FFF0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	beq _02250002
	cmp r0, #1
	beq _02250048
	pop {r3, r4, r5, pc}
_02250002:
	mov r1, #0xc
	add r2, r1, #0
	ldr r0, [r4, #4]
	sub r2, #0x2c
	bl sub_020079E0
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #4]
	sub r2, #0x2d
	bl sub_020079E0
	ldrb r0, [r4, #0xc]
	cmp r0, #0
	beq _0225002E
	sub r0, r0, #1
	strb r0, [r4, #0xc]
	mov r1, #1
	ldr r0, [r4, #4]
	sub r2, r1, #2
	bl sub_020079E0
_0225002E:
	ldr r0, [r4, #4]
	mov r1, #0xc
	bl sub_0200782C
	cmp r0, #0
	bgt _0225005E
	ldr r0, [r4, #4]
	bl sub_02007534
	ldrb r0, [r4, #0xb]
	add r0, r0, #1
	strb r0, [r4, #0xb]
	pop {r3, r4, r5, pc}
_02250048:
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0225005E:
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02250060
ov11_02250060: ; 0x02250060
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF74
	add r5, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0x21
	bge _0225009C
	ldrb r0, [r4, #0x12]
	cmp r0, #2
	blo _0225009C
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _02250086
	cmp r0, #2
	bne _0225009C
_02250086:
	ldr r0, [r4]
	bl ov11_0222FF68
	mov r1, #3
	mov r2, #1
	mov r3, #4
	bl BgSetPosTextAndCommit
	ldr r0, [r4, #0x20]
	add r0, r0, #1
	str r0, [r4, #0x20]
_0225009C:
	ldrb r0, [r4, #0x12]
	cmp r0, #4
	bls _022500A4
	b _02250332
_022500A4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022500B0: ; jump table
	.short _022500BA - _022500B0 - 2 ; case 0
	.short _022500C4 - _022500B0 - 2 ; case 1
	.short _022500D2 - _022500B0 - 2 ; case 2
	.short _022502CA - _022500B0 - 2 ; case 3
	.short _022502E4 - _022500B0 - 2 ; case 4
_022500BA:
	mov r0, #0x1c
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
_022500C4:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	bne _022501A6
	ldrb r0, [r4, #0x12]
	add r0, r0, #1
	strb r0, [r4, #0x12]
_022500D2:
	ldrb r0, [r4, #0x13]
	add r1, sp, #0
	cmp r0, #2
	ldr r0, [r4, #8]
	bne _022501D2
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl sub_0200C7A0
	ldr r0, [r4, #0x18]
	cmp r0, #1
	beq _022500F0
	cmp r0, #3
	bne _02250112
_022500F0:
	add r1, sp, #0
	mov r0, #2
	ldrsh r0, [r1, r0]
	cmp r0, #0xc0
	ldr r0, [r4, #8]
	bge _02250108
	ldr r0, [r0]
	mov r1, #8
	mov r2, #0
	bl sub_0200C82C
	b _02250112
_02250108:
	ldr r0, [r0]
	mov r1, #0xc0
	mov r2, #0x58
	bl sub_0200C714
_02250112:
	ldr r0, [r4, #8]
	add r1, sp, #0
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl sub_0200C7A0
	ldr r0, [r4, #0x18]
	cmp r0, #1
	beq _02250136
	cmp r0, #3
	bne _02250146
	cmp r5, #3
	beq _02250136
	cmp r5, #0x83
	beq _02250136
	cmp r5, #7
	bne _02250146
_02250136:
	add r3, sp, #0
	mov r2, #2
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_02007558
	b _02250196
_02250146:
	cmp r0, #3
	bne _02250170
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r0, r1
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x18
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #4]
	neg r2, r2
	bl sub_020079E0
	b _02250196
_02250170:
	cmp r0, #5
	bne _02250196
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r1, r0
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x10
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #4]
	bl sub_020079E0
_02250196:
	mov r0, #0x14
	ldrsh r5, [r4, r0]
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	cmp r0, r5
	bge _022501A8
_022501A6:
	b _02250332
_022501A8:
	ldr r0, [r4, #4]
	mov r1, #0
	add r2, r5, #0
	bl sub_02007558
	ldr r0, [r4, #0x18]
	cmp r0, #1
	beq _022501BC
	cmp r0, #3
	bne _022501C8
_022501BC:
	ldr r0, [r4, #8]
	mov r1, #0xc0
	ldr r0, [r0]
	mov r2, #0x58
	bl sub_0200C714
_022501C8:
	ldrb r0, [r4, #0x12]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_022501D2:
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl sub_0200C7A0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _022501E6
	cmp r0, #2
	bne _02250208
_022501E6:
	add r0, sp, #0
	mov r1, #2
	ldrsh r0, [r0, r1]
	cmp r0, #0x40
	ldr r0, [r4, #8]
	ble _022501FE
	ldr r0, [r0]
	sub r1, #0xa
	mov r2, #0
	bl sub_0200C82C
	b _02250208
_022501FE:
	ldr r0, [r0]
	mov r1, #0x40
	mov r2, #0x88
	bl sub_0200C714
_02250208:
	ldr r0, [r4, #8]
	add r1, sp, #0
	ldr r0, [r0]
	add r1, #2
	add r2, sp, #0
	bl sub_0200C7A0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _02250230
	cmp r0, #2
	bne _02250240
	cmp r5, #3
	beq _02250230
	cmp r5, #0x83
	beq _02250230
	cmp r5, #0x13
	beq _02250230
	cmp r5, #7
	bne _02250240
_02250230:
	add r3, sp, #0
	mov r2, #2
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_02007558
	b _02250290
_02250240:
	cmp r0, #2
	bne _02250268
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r1, r0
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x18
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #4]
	bl sub_020079E0
	b _02250290
_02250268:
	cmp r0, #4
	bne _02250290
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	add r3, sp, #0
	mov r2, #2
	ldrsh r1, [r3, r2]
	sub r0, r0, r1
	strh r0, [r3, #2]
	ldrsh r0, [r3, r2]
	mov r1, #0
	sub r0, #0x10
	strh r0, [r3, #2]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, #4]
	neg r2, r2
	bl sub_020079E0
_02250290:
	mov r0, #0x14
	ldrsh r5, [r4, r0]
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	cmp r0, r5
	bgt _02250332
	ldr r0, [r4, #4]
	mov r1, #0
	add r2, r5, #0
	bl sub_02007558
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _022502B4
	cmp r0, #2
	bne _022502C0
_022502B4:
	ldr r0, [r4, #8]
	mov r1, #0x40
	ldr r0, [r0]
	mov r2, #0x88
	bl sub_0200C714
_022502C0:
	ldrb r0, [r4, #0x12]
	add sp, #4
	add r0, r0, #1
	strb r0, [r4, #0x12]
	pop {r3, r4, r5, r6, pc}
_022502CA:
	ldrb r1, [r4, #0x11]
	ldrb r2, [r4, #0x10]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_022502E4:
	ldrb r0, [r4, #0x13]
	cmp r0, #2
	ldr r0, [r4, #4]
	bne _0225030E
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	mov r1, #0
	bl sub_02007558
	ldr r0, [r4, #0x18]
	cmp r0, #1
	beq _02250300
	cmp r0, #3
	bne _0225032E
_02250300:
	ldr r0, [r4, #8]
	mov r1, #0xc0
	ldr r0, [r0]
	mov r2, #0x58
	bl sub_0200C714
	b _0225032E
_0225030E:
	mov r2, #0x14
	ldrsh r2, [r4, r2]
	mov r1, #0
	bl sub_02007558
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _02250322
	cmp r0, #2
	bne _0225032E
_02250322:
	ldr r0, [r4, #8]
	mov r1, #0x40
	ldr r0, [r0]
	mov r2, #0x88
	bl sub_0200C714
_0225032E:
	mov r0, #3
	strb r0, [r4, #0x12]
_02250332:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02250338
ov11_02250338: ; 0x02250338
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xd0
	ldr r3, _022505EC ; =ov11_0225E8D0
	add r4, r1, #0
	add r5, r0, #0
	add r2, sp, #0x30
	mov r1, #0x50
_02250346:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _02250346
	ldr r0, [r4]
	bl ov11_0222FF74
	add r6, r0, #0
	ldrb r0, [r4, #0xa]
	cmp r0, #6
	bls _02250362
	b _0225088A
_02250362:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225036E: ; jump table
	.short _0225037C - _0225036E - 2 ; case 0
	.short _02250494 - _0225036E - 2 ; case 1
	.short _0225059E - _0225036E - 2 ; case 2
	.short _0225073C - _0225036E - 2 ; case 3
	.short _022507F2 - _0225036E - 2 ; case 4
	.short _0225084C - _0225036E - 2 ; case 5
	.short _02250874 - _0225036E - 2 ; case 6
_0225037C:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _0225038A
	mov r0, #1
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_0225038A:
	cmp r0, #4
	bhi _022503A4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225039A: ; jump table
	.short _022503A4 - _0225039A - 2 ; case 0
	.short _022503A4 - _0225039A - 2 ; case 1
	.short _022503B2 - _0225039A - 2 ; case 2
	.short _022503C0 - _0225039A - 2 ; case 3
	.short _022503CE - _0225039A - 2 ; case 4
_022503A4:
	mov r0, #0xf
	str r0, [sp, #8]
	mov r0, #3
	str r0, [r4, #0x18]
	mov r0, #5
	str r0, [sp, #0x18]
	b _022503DC
_022503B2:
	mov r0, #0xc
	str r0, [sp, #8]
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, _022505F0 ; =0x00000111
	str r0, [sp, #0x18]
	b _022503DC
_022503C0:
	mov r0, #0xd
	str r0, [sp, #8]
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, _022505F4 ; =0x00000112
	str r0, [sp, #0x18]
	b _022503DC
_022503CE:
	mov r0, #0xf
	str r0, [sp, #8]
	mov r0, #3
	str r0, [r4, #0x18]
	mov r0, #0x11
	lsl r0, r0, #4
	str r0, [sp, #0x18]
_022503DC:
	mov r0, #5
	str r0, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	ldrb r0, [r4, #9]
	str r0, [sp, #0x14]
	ldr r0, [r4]
	bl ov11_02230078
	str r0, [sp, #0x24]
	ldr r0, [r4]
	bl ov11_022300CC
	str r0, [sp, #0x28]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [r4]
	str r0, [sp, #0x2c]
	add r0, sp, #8
	bl ov08_02229918
	ldr r1, [r4, #4]
	add r1, #0x88
	str r0, [r1]
	ldr r0, [r4, #4]
	mov r1, #0x64
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_0222A00C
	ldr r0, [r4, #4]
	mov r1, #2
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_0222A018
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_0222A008
	mov r1, #0
	ldr r0, [r4]
	ldr r2, [r4, #0xc]
	add r3, r1, #0
	bl ov11_02254308
	ldr r1, [r4, #4]
	str r0, [r1, #0x18]
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	add r1, sp, #4
	strh r0, [r1, #2]
	ldr r0, [r4, #4]
	mov r1, #1
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	add r3, sp, #4
	strh r0, [r3]
	ldr r0, [r4, #4]
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r0, #0x18]
	bl sub_0200C714
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x18]
	bl sub_0200C61C
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x18]
	bl sub_0200C5C0
	ldr r0, [r4, #4]
	mov r1, #6
	ldr r0, [r0, #0x1c]
	mov r2, #1
	bl sub_02007558
	mov r0, #3
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_02250494:
	ldrb r0, [r4, #0xb]
	cmp r0, #2
	ldr r0, [r4, #4]
	bne _0225054A
	ldr r0, [r0, #0x1c]
	mov r1, #0
	mov r2, #5
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	mov r1, #0x45
	lsl r1, r1, #2
	cmp r0, r1
	blt _02250520
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A80
	cmp r0, #0
	beq _02250520
	ldr r0, [r4, #4]
	mov r1, #1
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229FE4
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A5C
	mov r0, #2
	tst r0, r6
	beq _02250532
	mov r0, #8
	tst r0, r6
	bne _02250532
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_022302BC
	add r1, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF7C
	add r4, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #1
	bl ov08_02229FE4
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0
	bl ov08_02229A5C
	add r4, #0x88
	ldr r0, [r4]
	mov r1, #0xc
	bl ov08_0222A024
	add sp, #0xd0
	pop {r3, r4, r5, r6, r7, pc}
_02250520:
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	mov r1, #0x4a
	lsl r1, r1, #2
	cmp r0, r1
	bge _02250534
_02250532:
	b _0225088A
_02250534:
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x1c]
	bl sub_02007534
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x1c]
	mov r0, #6
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_0225054A:
	ldr r0, [r0, #0x1c]
	mov r1, #0
	bl sub_0200782C
	add r1, sp, #4
	strh r0, [r1, #2]
	ldr r0, [r4, #4]
	mov r1, #1
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	add r3, sp, #4
	strh r0, [r3]
	ldr r0, [r4, #4]
	mov r1, #2
	mov r2, #0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r0, #0x18]
	bl sub_0200C714
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x18]
	bl sub_0200C61C
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x18]
	bl sub_0200C5C0
	mov r0, #2
	strb r0, [r4, #0xa]
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x1c]
	bl sub_02007534
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x1c]
	add sp, #0xd0
	pop {r3, r4, r5, r6, r7, pc}
_0225059E:
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x18]
	bl sub_0200C5A8
	ldr r0, [r4, #4]
	mov r1, #4
	ldr r0, [r0, #0x18]
	mvn r1, r1
	mov r2, #0
	bl sub_0200C82C
	ldr r0, [r4, #4]
	add r1, sp, #4
	ldr r0, [r0, #0x18]
	add r1, #2
	add r2, sp, #4
	bl sub_0200C7A0
	ldr r1, [r4, #4]
	add r0, r1, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	bne _022505D0
	b _022506E4
_022505D0:
	ldr r0, [r1, #0x18]
	bl sub_0200C630
	ldr r1, [r4, #0xc]
	str r0, [sp]
	lsl r5, r0, #2
	mov r0, #0x14
	add r2, r1, #0
	mul r2, r0
	add r0, sp, #0x30
	add r0, r0, r2
	ldrsh r1, [r5, r0]
	ldr r0, _022505F8 ; =0x00007FFF
	b _022505FC
	.align 2, 0
_022505EC: .word ov11_0225E8D0
_022505F0: .word 0x00000111
_022505F4: .word 0x00000112
_022505F8: .word 0x00007FFF
_022505FC:
	cmp r1, r0
	beq _022506E4
	ldr r0, [r4, #4]
	mov r1, #1
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229FE4
	ldr r1, [r4, #0xc]
	mov r0, #0x14
	add r3, r1, #0
	mul r3, r0
	add r2, sp, #0x30
	add r2, r2, r3
	add r7, sp, #4
	mov r1, #2
	ldrsh r1, [r7, r1]
	ldrsh r2, [r5, r2]
	ldr r0, [r4, #4]
	add r1, r1, r2
	mov r2, #0
	ldrsh r7, [r7, r2]
	add r2, sp, #0x30
	add r2, #2
	add r2, r2, r3
	ldrsh r2, [r5, r2]
	add r0, #0x88
	lsl r1, r1, #0x10
	add r2, r7, r2
	lsl r2, r2, #0x10
	ldr r0, [r0]
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl ov08_02229FF0
	ldr r0, [sp]
	cmp r0, #3
	bne _022506E4
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A80
	cmp r0, #0
	beq _022506E4
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A5C
	ldr r0, [r4, #4]
	mov r1, #1
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_0222A008
	mov r0, #2
	tst r0, r6
	beq _022506E4
	mov r0, #8
	tst r0, r6
	bne _022506E4
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_022302BC
	add r1, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF7C
	ldr r1, [r4, #0xc]
	add r6, r0, #0
	add r3, r1, #0
	mov r0, #0x14
	mul r3, r0
	add r2, sp, #0x30
	add r2, r2, r3
	add r0, r6, #0
	add r0, #0x88
	add r7, sp, #4
	mov r1, #2
	ldrsh r1, [r7, r1]
	ldrsh r2, [r5, r2]
	ldr r0, [r0]
	add r1, r1, r2
	mov r2, #0
	ldrsh r7, [r7, r2]
	add r2, sp, #0x30
	add r2, #2
	add r2, r2, r3
	ldrsh r2, [r5, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r7, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl ov08_02229FF0
	add r0, r6, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #1
	bl ov08_02229FE4
	add r0, r6, #0
	add r0, #0x88
	ldr r0, [r0]
	mov r1, #0
	bl ov08_02229A5C
	add r6, #0x88
	ldr r0, [r6]
	mov r1, #1
	bl ov08_0222A008
_022506E4:
	add r1, sp, #4
	mov r0, #2
	ldrsh r1, [r1, r0]
	sub r0, #0x2a
	cmp r1, r0
	ble _022506F2
	b _0225088A
_022506F2:
	ldr r0, [r4]
	bl ov11_02230080
	add r6, r0, #0
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02230260
	asr r5, r0, #1
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x18]
	bl sub_0200C3DC
	ldr r1, _02250890 ; =0x00004E2F
	add r0, r6, #0
	add r1, r5, r1
	bl sub_0200C358
	ldr r1, _02250894 ; =0x00004E2A
	add r0, r6, #0
	add r1, r5, r1
	bl sub_0200C368
	ldr r1, _02250898 ; =0x00004E27
	add r0, r6, #0
	add r1, r5, r1
	bl sub_0200C378
	ldr r1, _02250898 ; =0x00004E27
	add r0, r6, #0
	add r1, r5, r1
	bl sub_0200C388
	mov r0, #6
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_0225073C:
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x18]
	bl sub_0200C5A8
	ldr r0, [r4, #4]
	add r1, sp, #4
	ldr r0, [r0, #0x18]
	add r1, #2
	add r2, sp, #4
	bl sub_0200C7A0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x18]
	bl sub_0200C630
	add r5, r0, #0
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	beq _022507E2
	ldr r2, [r4, #0xc]
	mov r1, #0x14
	add r3, r2, #0
	mul r3, r1
	add r1, sp, #0x30
	lsl r6, r5, #2
	add r1, r1, r3
	ldrsh r1, [r6, r1]
	ldr r2, _0225089C ; =0x00007FFF
	cmp r1, r2
	beq _022507E2
	add r7, sp, #4
	mov r2, #2
	ldrsh r2, [r7, r2]
	add r1, r2, r1
	mov r2, #0
	ldrsh r7, [r7, r2]
	add r2, sp, #0x30
	add r2, #2
	add r2, r2, r3
	ldrsh r2, [r6, r2]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r7, r2
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	bl ov08_02229FF0
	cmp r5, #3
	bne _022507E2
	ldr r0, [r4, #4]
	ldr r6, [r4, #0x18]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A80
	cmp r6, r0
	beq _022507E2
	ldr r0, [r4, #4]
	add r1, r6, #0
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A5C
	ldr r0, [r4, #4]
	mov r1, #1
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_0222A018
	ldr r0, [r4, #4]
	mov r1, #1
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_0222A008
	ldr r0, [r4, #0x18]
	cmp r0, #3
	beq _022507E2
	ldr r0, _022508A0 ; =0x0000070A
	bl PlaySE
_022507E2:
	cmp r5, #4
	bne _0225088A
	mov r0, #8
	str r0, [r4, #0x14]
	mov r0, #4
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_022507F2:
	ldr r0, [r4, #0x14]
	sub r0, r0, #1
	str r0, [r4, #0x14]
	bne _0225088A
	ldr r0, [r4]
	bl ov11_02230080
	add r5, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x18]
	bl sub_0200C3DC
	ldr r1, _02250890 ; =0x00004E2F
	add r0, r5, #0
	bl sub_0200C358
	ldr r1, _02250894 ; =0x00004E2A
	add r0, r5, #0
	bl sub_0200C368
	ldr r1, _02250898 ; =0x00004E27
	add r0, r5, #0
	bl sub_0200C378
	ldr r1, _02250898 ; =0x00004E27
	add r0, r5, #0
	bl sub_0200C388
	ldr r0, [r4, #4]
	mov r1, #6
	ldr r0, [r0, #0x1c]
	mov r2, #0
	bl sub_02007558
	ldr r0, [r4, #0x18]
	cmp r0, #3
	bne _02250844
	mov r0, #6
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_02250844:
	mov r0, #5
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_0225084C:
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_022299E8
	cmp r0, #1
	beq _0225088A
	ldr r0, [r4, #4]
	add r0, #0x88
	ldr r0, [r0]
	bl ov08_02229A2C
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x88
	str r1, [r0]
	mov r0, #6
	add sp, #0xd0
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, r7, pc}
_02250874:
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0225088A:
	add sp, #0xd0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02250890: .word 0x00004E2F
_02250894: .word 0x00004E2A
_02250898: .word 0x00004E27
_0225089C: .word 0x00007FFF
_022508A0: .word 0x0000070A

	thumb_func_start ov11_022508A4
ov11_022508A4: ; 0x022508A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	beq _022508B6
	cmp r0, #1
	beq _02250906
	pop {r3, r4, r5, pc}
_022508B6:
	ldrb r0, [r4, #0xb]
	cmp r0, #2
	ldr r0, [r4, #4]
	bne _022508E2
	ldr r0, [r0, #0x1c]
	mov r1, #0
	mov r2, #5
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	mov r1, #0x4a
	lsl r1, r1, #2
	cmp r0, r1
	blt _0225092A
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_022508E2:
	mov r1, #0
	ldr r0, [r0, #0x1c]
	sub r2, r1, #5
	bl sub_020079E0
	ldr r0, [r4, #4]
	mov r1, #0
	ldr r0, [r0, #0x1c]
	bl sub_0200782C
	mov r1, #0x27
	mvn r1, r1
	cmp r0, r1
	bgt _0225092A
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_02250906:
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x1c]
	bl sub_02007534
	ldr r0, [r4, #4]
	mov r1, #0
	str r1, [r0, #0x1c]
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0225092A:
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0225092C
ov11_0225092C: ; 0x0225092C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	beq _0225093E
	cmp r0, #1
	beq _0225099A
	pop {r3, r4, r5, pc}
_0225093E:
	ldrb r0, [r4, #0xb]
	cmp r0, #0
	ldr r0, [r4, #4]
	bne _02250970
	mov r1, #0
	mov r2, #5
	bl sub_020079E0
	mov r0, #0xc
	ldrsh r5, [r4, r0]
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	cmp r0, r5
	blt _022509B0
	ldr r0, [r4, #4]
	mov r1, #0
	add r2, r5, #0
	bl sub_02007558
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_02250970:
	mov r1, #0
	sub r2, r1, #5
	bl sub_020079E0
	mov r0, #0xc
	ldrsh r5, [r4, r0]
	ldr r0, [r4, #4]
	mov r1, #0
	bl sub_0200782C
	cmp r0, r5
	bgt _022509B0
	ldr r0, [r4, #4]
	mov r1, #0
	add r2, r5, #0
	bl sub_02007558
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_0225099A:
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_022509B0:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022509B4
ov11_022509B4: ; 0x022509B4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	beq _022509C6
	cmp r1, #1
	beq _022509F6
	b _02250A0A
_022509C6:
	add r0, r4, #0
	add r0, #0x4d
	ldrb r0, [r0]
	cmp r0, #0
	beq _022509DE
	add r0, r4, #0
	add r0, #0x4d
	ldrb r0, [r0]
	add r4, #0x4d
	sub r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_022509DE:
	add r0, r4, #0
	mov r1, #0
	bl ov11_02257334
	add r0, r4, #0
	mov r1, #1
	bl ov11_022572AC
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_022509F6:
	add r0, r4, #0
	add r0, #0x4f
	ldrb r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02250A26
	add r0, r1, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02250A0A:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x24
	add r2, #0x4c
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4, #0xc]
	bl ov11_022567B8
	mov r0, #0
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl sub_0200CAB4
_02250A26:
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02250A28
ov11_02250A28: ; 0x02250A28
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #0
	bne _02250A48
	add r0, r4, #0
	add r0, #0x4f
	ldrb r0, [r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02250A6C
	add r0, r1, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02250A48:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x24
	add r2, #0x4c
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4, #0xc]
	bl ov11_022567B8
	mov r0, #0
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl sub_0200CAB4
	add r0, r4, #0
	mov r1, #0
	bl ov11_022572AC
_02250A6C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02250A70
ov11_02250A70: ; 0x02250A70
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r4, r1, #0
	str r0, [sp]
	ldr r0, [r4]
	bl ov11_0222FF68
	ldr r0, [r4]
	bl ov11_02230094
	add r6, r0, #0
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_0222FF7C
	str r0, [sp, #4]
	ldr r0, [r4]
	bl ov11_0222FF74
	add r7, r0, #0
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_022302BC
	add r1, r0, #0
	ldrb r0, [r4, #9]
	cmp r1, r0
	beq _02250AB2
	ldr r0, [r4]
	bl ov11_02231380
	add r5, r0, #0
	b _02250AB4
_02250AB2:
	mov r5, #0
_02250AB4:
	ldrb r0, [r4, #0xa]
	cmp r0, #8
	bls _02250ABC
	b _02250F3E
_02250ABC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02250AC8: ; jump table
	.short _02250ADA - _02250AC8 - 2 ; case 0
	.short _02250B16 - _02250AC8 - 2 ; case 1
	.short _02250C04 - _02250AC8 - 2 ; case 2
	.short _02250C1A - _02250AC8 - 2 ; case 3
	.short _02250C2C - _02250AC8 - 2 ; case 4
	.short _02250DA0 - _02250AC8 - 2 ; case 5
	.short _02250DF2 - _02250AC8 - 2 ; case 6
	.short _02250ED6 - _02250AC8 - 2 ; case 7
	.short _02250F14 - _02250AC8 - 2 ; case 8
_02250ADA:
	mov r0, #0
	add r1, r4, #0
	add r2, sp, #0x34
_02250AE0:
	ldrh r3, [r1, #0x24]
	add r1, r1, #2
	strh r3, [r2]
	add r3, r4, r0
	add r3, #0x2c
	ldrb r3, [r3]
	strh r3, [r2, #8]
	add r3, r4, r0
	add r3, #0x30
	ldrb r3, [r3]
	add r0, r0, #1
	strh r3, [r2, #0x10]
	add r2, r2, #2
	cmp r0, #4
	blt _02250AE0
	ldr r0, [r4]
	bl ov11_02230094
	add r1, r4, #0
	add r1, #0x34
	ldrb r1, [r1]
	add r2, sp, #0x34
	bl ov11_0225A760
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
_02250B16:
	ldr r0, [r4]
	bl ov11_022300C4
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #0xa
	add r1, r7, #0
	tst r1, r0
	beq _02250B9A
	ldr r0, [r4]
	bl ov11_02231268
	cmp r0, #0
	beq _02250B3A
	cmp r0, #1
	beq _02250B66
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
_02250B3A:
	mov r0, #2
	add r1, sp, #8
	strb r0, [r1, #9]
	add r0, r4, #0
	add r0, #0x23
	ldrb r0, [r0]
	ldrb r2, [r4, #9]
	mov r3, #0
	lsl r0, r0, #8
	orr r0, r2
	str r0, [sp, #0x14]
	ldr r0, _02250E84 ; =0x00000399
	add r2, sp, #0x10
	strh r0, [r1, #0xa]
	ldr r0, [r4]
	add r1, r5, #0
	bl ov11_0223178C
	mov r0, #3
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250B66:
	mov r1, #0
	add r0, sp, #8
	strb r1, [r0, #9]
	ldr r0, [r4]
	bl ov11_0223021C
	ldr r1, _02250E88 ; =0x000004CA
	add r1, r0, r1
	add r0, sp, #8
	strh r1, [r0, #0xa]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #0x10
	bl ov11_0223178C
	add r1, r4, #0
	add r1, #0x35
	strb r0, [r1]
	mov r0, #2
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250B9A:
	mov r1, #0x20
	add r2, r7, #0
	tst r2, r1
	beq _02250BBA
	mov r1, #8
	add r0, sp, #8
	strb r1, [r0, #9]
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02230140
	str r0, [sp, #0x14]
	ldr r1, _02250E8C ; =0x0000039A
	add r0, sp, #8
	strh r1, [r0, #0xa]
	b _02250BF0
_02250BBA:
	lsl r1, r1, #4
	tst r1, r7
	beq _02250BD8
	mov r1, #8
	add r0, sp, #8
	strb r1, [r0, #9]
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02230140
	str r0, [sp, #0x14]
	ldr r1, _02250E90 ; =0x000004C6
	add r0, sp, #8
	strh r1, [r0, #0xa]
	b _02250BF0
_02250BD8:
	add r2, r4, #0
	mov r1, #2
	add r3, sp, #8
	strb r1, [r3, #9]
	add r2, #0x23
	ldrb r2, [r2]
	ldrb r1, [r4, #9]
	sub r0, #0x67
	lsl r2, r2, #8
	orr r1, r2
	str r1, [sp, #0x14]
	strh r0, [r3, #0xa]
_02250BF0:
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #0x10
	mov r3, #0
	bl ov11_0223178C
	mov r0, #3
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250C04:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	bl sub_0201BD70
	cmp r0, #0
	bne _02250C36
	mov r0, #3
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250C1A:
	ldr r0, [r4, #4]
	bl ov11_02257208
	ldr r0, [sp, #4]
	ldr r1, [r4]
	bl ov11_0225464C
	mov r0, #4
	strb r0, [r4, #0xa]
_02250C2C:
	add r0, r6, #0
	bl ov11_02258F5C
	cmp r0, #0
	bne _02250C38
_02250C36:
	b _02250F3E
_02250C38:
	ldrb r1, [r4, #9]
	add r0, sp, #8
	strb r1, [r0, #1]
	add r1, r4, #0
	add r1, #0x34
	ldrb r1, [r1]
	strb r1, [r0]
	add r1, r4, #0
	add r1, #0x23
	ldrb r1, [r1]
	strb r1, [r0, #2]
	mov r1, #0x36
	ldrsh r1, [r4, r1]
	strh r1, [r0, #4]
	ldrh r1, [r4, #0x38]
	strh r1, [r0, #6]
	add r1, r4, #0
	add r1, #0x3a
	ldrb r1, [r1]
	strb r1, [r0, #3]
	ldr r1, _02250E94 ; =0x00000197
	ldr r0, [sp, #4]
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _02250CFA
	add r0, r6, #0
	mov r1, #1
	bl ov11_0225B77C
	ldr r0, [r4]
	bl ov11_02230C50
	mov r1, #1
	tst r0, r1
	beq _02250C8C
	add r0, r6, #0
	mov r1, #6
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
	b _02250CF0
_02250C8C:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	lsl r1, r1, #8
	tst r0, r1
	beq _02250CA8
	add r0, r6, #0
	mov r1, #0xa
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
	b _02250CF0
_02250CA8:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #0x20
	tst r0, r1
	beq _02250CC2
	add r0, r6, #0
	mov r1, #8
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
	b _02250CF0
_02250CC2:
	add r0, sp, #8
	ldrb r0, [r0]
	cmp r0, #4
	bne _02250CE4
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _02250CE4
	add r0, r6, #0
	mov r1, #4
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
	b _02250CF0
_02250CE4:
	add r0, r6, #0
	mov r1, #3
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
_02250CF0:
	ldr r0, [r4]
	mov r1, #1
	bl ov11_022312AC
	b _02250D70
_02250CFA:
	ldr r0, [r4]
	bl ov11_02230C50
	mov r1, #1
	tst r0, r1
	beq _02250D14
	add r0, r6, #0
	mov r1, #5
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
	b _02250D68
_02250D14:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	lsl r1, r1, #8
	tst r0, r1
	beq _02250D30
	add r0, r6, #0
	mov r1, #9
	mov r2, #0
	add r3, sp, #8
	bl ov11_02258820
	b _02250D68
_02250D30:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #0x20
	tst r0, r1
	add r3, sp, #8
	beq _02250D4A
	add r0, r6, #0
	mov r1, #7
	mov r2, #0
	bl ov11_02258820
	b _02250D68
_02250D4A:
	add r0, sp, #8
	ldrb r0, [r0]
	cmp r0, #4
	beq _02250D5E
	add r0, r6, #0
	mov r1, #1
	mov r2, #0
	bl ov11_02258820
	b _02250D68
_02250D5E:
	add r0, r6, #0
	mov r1, #2
	mov r2, #0
	bl ov11_02258820
_02250D68:
	ldr r1, _02250E94 ; =0x00000197
	ldr r0, [sp, #4]
	mov r2, #1
	strb r2, [r0, r1]
_02250D70:
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x1c
	bl ov11_02258D60
	add r1, r4, #0
	add r2, r4, #0
	add r0, r6, #0
	add r1, #0x10
	add r2, #0x16
	bl ov11_02258D7C
	add r0, r6, #0
	bl ov11_02258DD0
	cmp r5, #0
	beq _02250D98
	add r0, r5, #0
	bl ov11_02258180
_02250D98:
	mov r0, #5
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250DA0:
	ldr r0, _02250E98 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #8
	tst r0, r1
	beq _02250DD0
	ldr r0, [r4]
	mov r5, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _02250DD0
_02250DB6:
	ldr r0, [r4]
	add r1, r5, #0
	bl ov11_0222FF7C
	add r0, #0x28
	bl ov11_0225704C
	ldr r0, [r4]
	add r5, r5, #1
	bl ov11_0222FF84
	cmp r5, r0
	blt _02250DB6
_02250DD0:
	add r0, r6, #0
	bl ov11_02258E74
	mov r1, #0
	mvn r1, r1
	str r0, [r4, #0xc]
	cmp r0, r1
	beq _02250E02
	mov r0, #0xa
	strb r0, [r4, #0xb]
	ldr r0, _02250E9C ; =0x000005DD
	bl PlaySE
	mov r0, #6
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250DF2:
	add r0, r6, #0
	bl ov11_02258F5C
	cmp r0, #1
	beq _02250E04
	ldr r0, [r4, #0xc]
	cmp r0, #1
	beq _02250E04
_02250E02:
	b _02250F3E
_02250E04:
	ldr r0, [r4, #0xc]
	cmp r0, #4
	bhi _02250EC4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02250E16: ; jump table
	.short _02250EC4 - _02250E16 - 2 ; case 0
	.short _02250E20 - _02250E16 - 2 ; case 1
	.short _02250E34 - _02250E16 - 2 ; case 2
	.short _02250E5C - _02250E16 - 2 ; case 3
	.short _02250EA0 - _02250E16 - 2 ; case 4
_02250E20:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	beq _02250EC8
	mov r0, #7
	strb r0, [r4, #0xa]
	b _02250EC8
_02250E34:
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov11_02258820
	add r0, r6, #0
	mov r1, #0
	bl ov11_0225B77C
	add r0, r5, #0
	bl ov11_02258184
	ldr r0, [r4, #4]
	bl ov11_02257238
	ldr r0, [sp, #4]
	bl ov11_0225468C
	b _02250EC8
_02250E5C:
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov11_02258820
	add r0, r6, #0
	mov r1, #0
	bl ov11_0225B77C
	add r0, r5, #0
	bl ov11_02258184
	ldr r0, [r4, #4]
	bl ov11_02257238
	ldr r0, [sp, #4]
	bl ov11_0225468C
	b _02250EC8
	.align 2, 0
_02250E84: .word 0x00000399
_02250E88: .word 0x000004CA
_02250E8C: .word 0x0000039A
_02250E90: .word 0x000004C6
_02250E94: .word 0x00000197
_02250E98: .word gSystem
_02250E9C: .word 0x000005DD
_02250EA0:
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02230CB8
	cmp r0, #1
	bne _02250EB6
	add r0, r5, #0
	bl ov11_02258184
	mov r0, #0xff
	str r0, [r4, #0xc]
_02250EB6:
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov11_02258820
	b _02250EC8
_02250EC4:
	bl GF_AssertFail
_02250EC8:
	add r0, r6, #0
	bl ov11_02258E30
	mov r0, #8
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250ED6:
	add r0, r6, #0
	bl ov11_02258F5C
	cmp r0, #1
	bne _02250F3E
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov11_02258820
	add r0, r6, #0
	mov r1, #0
	bl ov11_0225B77C
	add r0, r5, #0
	bl ov11_02258184
	ldr r0, [r4, #4]
	bl ov11_02257238
	ldr r0, [sp, #4]
	bl ov11_0225468C
	add r0, r6, #0
	bl ov11_02258E30
	mov r0, #8
	add sp, #0x4c
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_02250F14:
	add r0, r6, #0
	bl ov11_0225B780
	cmp r0, #1
	bne _02250F3E
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	ldr r2, [r4, #0xc]
	bl ov11_02255528
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp]
	bl sub_0200CAB4
_02250F3E:
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02250F44
ov11_02250F44: ; 0x02250F44
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #9]
	add r5, r0, #0
	ldr r0, [r4]
	bl ov16_021F45A4
	add r2, r0, #0
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02255528
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02250F74
ov11_02250F74: ; 0x02250F74
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #9]
	add r5, r0, #0
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02250F94
ov11_02250F94: ; 0x02250F94
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02230DE0
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF78
	mov r2, #0
	ldrb r1, [r4, #9]
	add r3, r2, #0
	bl ov11_02243420
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x1a ; BASE_GREAT_MARSH_RATE
	bl GetMonBaseStat
	ldr r2, _0225100C ; =ov11_0225E830
	lsl r1, r5, #1
	ldrb r2, [r2, r1]
	mul r2, r0
	add r0, r2, #0
	ldr r2, _02251010 ; =ov11_0225E831
	ldrb r1, [r2, r1]
	bl _s32_div_f
	add r5, r0, #0
	bl LCRandom
	mov r1, #0xff
	bl _s32_div_f
	cmp r1, r5
	ldr r0, [r4]
	bgt _02250FEA
	ldrb r1, [r4, #9]
	mov r2, #4
	bl ov11_02255528
	b _02250FF2
_02250FEA:
	ldrb r1, [r4, #9]
	mov r2, #5
	bl ov11_02255528
_02250FF2:
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
	pop {r4, r5, r6, pc}
	nop
_0225100C: .word ov11_0225E830
_02251010: .word ov11_0225E831

	thumb_func_start ov11_02251014
ov11_02251014: ; 0x02251014
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #9]
	add r5, r0, #0
	ldr r0, [r4]
	mov r2, #4
	bl ov11_02255528
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0225103C
ov11_0225103C: ; 0x0225103C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF68
	ldr r0, [r4]
	bl ov11_02230094
	add r7, r0, #0
	ldrb r1, [r4, #0x1d]
	ldr r0, [r4]
	bl ov11_0222FF7C
	str r0, [sp]
	ldrb r1, [r4, #0x1d]
	ldr r0, [r4]
	bl ov11_022302BC
	add r1, r0, #0
	ldrb r0, [r4, #0x1d]
	cmp r1, r0
	beq _02251076
	ldr r0, [r4]
	bl ov11_02231380
	add r5, r0, #0
	b _02251078
_02251076:
	mov r5, #0
_02251078:
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	cmp r0, #3
	bls _02251084
	b _0225118E
_02251084:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02251090: ; jump table
	.short _02251098 - _02251090 - 2 ; case 0
	.short _02251114 - _02251090 - 2 ; case 1
	.short _0225113A - _02251090 - 2 ; case 2
	.short _02251180 - _02251090 - 2 ; case 3
_02251098:
	add r0, r7, #0
	bl ov11_02258F5C
	cmp r0, #0
	bne _022510A4
	b _022511B6
_022510A4:
	ldr r0, [r4]
	bl ov11_022300C4
	add r1, r0, #0
	mov r2, #2
	add r0, sp, #4
	strb r2, [r0, #0x15]
	ldrb r2, [r4, #0x1f]
	ldrb r3, [r4, #0x1d]
	lsl r2, r2, #8
	orr r2, r3
	str r2, [sp, #0x1c]
	ldr r2, _022511BC ; =0x00000399
	mov r3, #0
	strh r2, [r0, #0x16]
	ldr r0, [r4]
	add r2, sp, #0x18
	bl ov11_0223178C
	add r0, r7, #0
	bl ov11_02258E30
	add r5, sp, #4
	mov r2, #0
	add r3, r4, #0
	add r6, r5, #0
_022510D8:
	ldrh r0, [r3, #0xc]
	add r1, r4, r2
	add r2, r2, #1
	strh r0, [r5]
	ldrb r0, [r1, #0x14]
	add r3, r3, #2
	add r5, r5, #2
	strb r0, [r6, #8]
	ldrb r0, [r1, #0x18]
	strb r0, [r6, #0xc]
	add r6, r6, #1
	cmp r2, #4
	blt _022510D8
	ldrb r1, [r4, #0x1e]
	add r0, sp, #4
	mov r2, #0
	strb r1, [r0, #0x10]
	add r0, r7, #0
	mov r1, #0xb
	add r3, sp, #4
	bl ov11_02258820
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #0x3c
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, r7, pc}
_02251114:
	add r0, r7, #0
	bl ov11_02258E74
	mov r1, #0
	mvn r1, r1
	str r0, [r4, #8]
	cmp r0, r1
	beq _022511B6
	ldr r0, _022511C0 ; =0x000005DD
	bl PlaySE
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #0x3c
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0225113A:
	ldr r0, [r4, #8]
	cmp r0, #0xff
	beq _02251166
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02251166
	add r0, r7, #0
	mov r1, #0
	bl ov11_0225B77C
	add r0, r5, #0
	bl ov11_02258184
	ldr r0, [r4, #4]
	bl ov11_02257238
	ldr r0, [sp]
	bl ov11_0225468C
_02251166:
	ldrb r1, [r4, #0x1d]
	ldr r0, [r4]
	ldr r2, [r4, #8]
	bl ov11_022555E4
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r4, #0x20
	add sp, #0x3c
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, r7, pc}
_02251180:
	add r0, r4, #0
	add r0, #0x20
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x20
	strb r1, [r0]
_0225118E:
	add r0, r7, #0
	bl ov11_0225B780
	cmp r0, #1
	bne _022511B6
	ldr r0, [r4]
	mov r1, #1
	bl ov11_02231274
	ldrb r1, [r4, #0x1d]
	ldrb r2, [r4, #0x1c]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_022511B6:
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_022511BC: .word 0x00000399
_022511C0: .word 0x000005DD

	thumb_func_start ov11_022511C4
ov11_022511C4: ; 0x022511C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r6, r1, #0
	str r0, [sp, #8]
	ldr r0, [r6]
	bl ov11_0222FF74
	add r4, r0, #0
	ldr r0, [r6]
	bl ov11_0222FF78
	str r0, [sp, #0xc]
	ldr r0, _02251290 ; =0x00000101
	tst r0, r4
	bne _022511FA
	ldr r0, [r6]
	bl ov11_02230C50
	mov r1, #1
	tst r0, r1
	bne _022511FA
	ldrb r1, [r6, #0x1d]
	ldr r0, [r6]
	bl ov11_02230270
	cmp r0, #0
	bne _02251216
_022511FA:
	bl sub_02033590
	cmp r0, #0
	beq _02251206
	bl GF_AssertFail
_02251206:
	ldrb r1, [r6, #0x1d]
	ldr r0, [r6]
	bl ov16_021EFD8C
	cmp r0, #0xff
	beq _0225128C
	add r4, r0, #1
	b _0225126C
_02251216:
	mov r7, #0
	add r4, r7, #0
	add r5, sp, #0x10
_0225121C:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldrh r1, [r6, #0x22]
	tst r0, r1
	bne _0225122E
	add r0, r4, #1
	stmia r5!, {r0}
	add r7, r7, #1
_0225122E:
	add r4, r4, #1
	cmp r4, #4
	blt _0225121C
	bl LCRandom
	add r1, r7, #0
	bl _s32_div_f
	lsl r1, r1, #2
	add r0, sp, #0x10
	ldr r4, [r0, r1]
	mov r0, #1
	sub r3, r4, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	lsl r3, r3, #1
	add r3, r6, r3
	ldrb r2, [r6, #0x1d]
	ldrh r3, [r3, #0xc]
	ldr r0, [r6]
	ldr r1, [sp, #0xc]
	bl ov11_02244C28
	str r0, [sp]
	ldrb r3, [r6, #0x1d]
	ldr r0, [r6]
	ldr r1, [sp, #0xc]
	mov r2, #0xb
	bl ov11_0224C54C
_0225126C:
	ldrb r1, [r6, #0x1d]
	ldr r0, [r6]
	add r2, r4, #0
	bl ov11_022555E4
	ldrb r1, [r6, #0x1d]
	ldrb r2, [r6, #0x1c]
	ldr r0, [r6]
	bl ov11_022567B8
	add r0, r6, #0
	bl FreeToHeap
	ldr r0, [sp, #8]
	bl sub_0200CAB4
_0225128C:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02251290: .word 0x00000101

	thumb_func_start ov11_02251294
ov11_02251294: ; 0x02251294
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0x1d]
	add r5, r0, #0
	ldrb r2, [r4, #0x1c]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022512B4
ov11_022512B4: ; 0x022512B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r4, r1, #0
	str r0, [sp]
	ldr r0, [r4]
	bl ov11_0222FF68
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF7C
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_02230094
	add r5, r0, #0
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_022302BC
	add r1, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r1, r0
	beq _022512EE
	ldr r0, [r4]
	bl ov11_02231380
	add r6, r0, #0
	b _022512F0
_022512EE:
	mov r6, #0
_022512F0:
	ldrb r0, [r4, #0xf]
	cmp r0, #3
	bhi _022513BE
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02251302: ; jump table
	.short _0225130A - _02251302 - 2 ; case 0
	.short _02251366 - _02251302 - 2 ; case 1
	.short _02251386 - _02251302 - 2 ; case 2
	.short _022513BA - _02251302 - 2 ; case 3
_0225130A:
	add r0, r5, #0
	bl ov11_02258F5C
	cmp r0, #0
	bne _02251316
	b _02251418
_02251316:
	add r2, sp, #8
	mov r0, #0
	add r1, r4, #0
	add r2, #2
_0225131E:
	ldrh r3, [r1, #0x10]
	add r0, r0, #1
	strh r3, [r2]
	ldrh r3, [r1, #0x12]
	strh r3, [r2, #2]
	ldrh r3, [r1, #0x14]
	strh r3, [r2, #4]
	ldrh r3, [r1, #0x16]
	add r1, #8
	strh r3, [r2, #6]
	add r2, #8
	cmp r0, #4
	blt _0225131E
	ldrb r1, [r4, #0xe]
	add r0, sp, #0x28
	add r0, #2
	strb r1, [r0]
	ldrh r0, [r4, #0x30]
	ldrb r1, [r4, #0xe]
	bl ov11_02258F88
	add r1, sp, #0x28
	add r1, #2
	strb r0, [r1, #1]
	add r3, sp, #8
	add r0, r5, #0
	mov r1, #0xc
	mov r2, #0
	add r3, #2
	bl ov11_02258820
	ldrb r0, [r4, #0xf]
	add sp, #0x2c
	add r0, r0, #1
	strb r0, [r4, #0xf]
	pop {r4, r5, r6, r7, pc}
_02251366:
	add r0, r5, #0
	bl ov11_02258E74
	mov r1, #0
	mvn r1, r1
	str r0, [r4, #8]
	cmp r0, r1
	beq _02251418
	ldr r0, _0225141C ; =0x000005DD
	bl PlaySE
	ldrb r0, [r4, #0xf]
	add sp, #0x2c
	add r0, r0, #1
	strb r0, [r4, #0xf]
	pop {r4, r5, r6, r7, pc}
_02251386:
	ldr r0, [r4, #8]
	cmp r0, #0xff
	beq _022513B0
	ldr r0, [r4, #4]
	bl ov11_02257238
	add r0, r7, #0
	bl ov11_0225468C
	add r0, r6, #0
	bl ov11_02258184
	add r0, r4, #0
	add r0, #0x32
	ldrb r0, [r0]
	cmp r0, #1
	bne _022513B0
	add r0, r5, #0
	mov r1, #0
	bl ov11_0225B77C
_022513B0:
	ldrb r0, [r4, #0xf]
	add sp, #0x2c
	add r0, r0, #1
	strb r0, [r4, #0xf]
	pop {r4, r5, r6, r7, pc}
_022513BA:
	add r0, r0, #1
	strb r0, [r4, #0xf]
_022513BE:
	add r0, r5, #0
	bl ov11_0225B780
	cmp r0, #1
	bne _02251418
	ldr r0, [r4]
	ldr r5, [r4, #8]
	bl ov11_0222FF74
	add r6, r0, #0
	cmp r5, #0xff
	beq _022513F8
	ldr r0, [r4]
	add r1, sp, #4
	bl ov11_022314E0
	mov r0, #2
	tst r0, r6
	ldr r0, [r4, #8]
	beq _022513F0
	add r1, r0, #1
	add r0, sp, #4
	ldrb r0, [r0, r1]
	add r5, r0, #1
	b _022513F8
_022513F0:
	sub r1, r0, #1
	add r0, sp, #4
	ldrb r0, [r0, r1]
	add r5, r0, #1
_022513F8:
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	add r2, r5, #0
	bl ov11_02255720
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp]
	bl sub_0200CAB4
_02251418:
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0225141C: .word 0x000005DD

	thumb_func_start ov11_02251420
ov11_02251420: ; 0x02251420
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	bl ov11_0222FF78
	add r1, r0, #0
	ldrb r3, [r5, #0xd]
	ldr r0, [r5]
	mov r2, #0xb
	bl ov11_0224C474
	add r4, r0, #1
	cmp r4, #5
	blt _02251442
	bl GF_AssertFail
_02251442:
	ldrb r1, [r5, #0xd]
	ldr r0, [r5]
	add r2, r4, #0
	bl ov11_02255720
	ldrb r1, [r5, #0xd]
	ldrb r2, [r5, #0xc]
	ldr r0, [r5]
	bl ov11_022567B8
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_02251464
ov11_02251464: ; 0x02251464
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02251484
ov11_02251484: ; 0x02251484
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x14
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_022300CC
	ldrb r1, [r4, #0xe]
	add r5, r0, #0
	cmp r1, #0x1e
	bls _022514A0
	bl _02251FEA
_022514A0:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022514AC: ; jump table
	.short _022514EA - _022514AC - 2 ; case 0
	.short _02251540 - _022514AC - 2 ; case 1
	.short _022515C2 - _022514AC - 2 ; case 2
	.short _022515D6 - _022514AC - 2 ; case 3
	.short _02251634 - _022514AC - 2 ; case 4
	.short _0225177C - _022514AC - 2 ; case 5
	.short _022517B8 - _022514AC - 2 ; case 6
	.short _02251808 - _022514AC - 2 ; case 7
	.short _022519DC - _022514AC - 2 ; case 8
	.short _02251A5A - _022514AC - 2 ; case 9
	.short _02251A96 - _022514AC - 2 ; case 10
	.short _02251AB8 - _022514AC - 2 ; case 11
	.short _02251FA2 - _022514AC - 2 ; case 12
	.short _02251B3E - _022514AC - 2 ; case 13
	.short _02251FA2 - _022514AC - 2 ; case 14
	.short _02251BF2 - _022514AC - 2 ; case 15
	.short _02251FD0 - _022514AC - 2 ; case 16
	.short _02251AF8 - _022514AC - 2 ; case 17
	.short _02251FA2 - _022514AC - 2 ; case 18
	.short _02251CA6 - _022514AC - 2 ; case 19
	.short _02251FA2 - _022514AC - 2 ; case 20
	.short _02251CEC - _022514AC - 2 ; case 21
	.short _02251D86 - _022514AC - 2 ; case 22
	.short _02251DBC - _022514AC - 2 ; case 23
	.short _02251FD0 - _022514AC - 2 ; case 24
	.short _02251AF8 - _022514AC - 2 ; case 25
	.short _02251FA2 - _022514AC - 2 ; case 26
	.short _02251CA6 - _022514AC - 2 ; case 27
	.short _02251FA2 - _022514AC - 2 ; case 28
	.short _02251E2E - _022514AC - 2 ; case 29
	.short _02251FD0 - _022514AC - 2 ; case 30
_022514EA:
	ldr r0, [r4]
	bl ov11_02230094
	bl ov11_0225C76C
	strb r0, [r4, #0x10]
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	mov r2, #3
	str r1, [sp]
	mov r0, #7
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #5
	add r3, r1, #0
	add r0, r5, #0
	lsl r2, r2, #0xa
	sub r3, #0xd
	bl sub_02003210
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0xa
	add r3, r1, #0
	ldr r2, _02251850 ; =0x0000FFFF
	add r0, r5, #0
	sub r3, #0x12
	bl sub_02003210
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251540:
	bl sub_020038E4
	cmp r0, #0
	bne _022515FE
	ldr r0, [r4]
	bl ov11_0222D7F8
	mov r0, #5
	mov r1, #0x34
	bl AllocFromHeap
	str r0, [r4, #4]
	ldr r1, [r4]
	str r1, [r0]
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_022301D4
	ldr r1, [r4, #4]
	str r0, [r1, #4]
	ldr r0, [r4, #4]
	mov r1, #5
	str r1, [r0, #0xc]
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x26
	strb r1, [r0]
	ldr r0, [r4]
	bl ov11_02230214
	ldr r1, [r4, #4]
	str r0, [r1, #8]
	ldrb r1, [r4, #0xd]
	ldr r0, [r4, #4]
	str r1, [r0, #0x10]
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0x10]
	add r0, #0x25
	strb r1, [r0]
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0x14]
	add r0, #0x22
	strb r1, [r0]
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0x15]
	add r0, #0x23
	strb r1, [r0]
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0x16]
	add r0, #0x24
	strb r1, [r0]
	ldrb r0, [r4, #0xd]
	add r0, r4, r0
	add r0, #0x30
	ldrb r1, [r0]
	ldr r0, [r4, #4]
	str r1, [r0, #0x18]
	ldr r0, [r4, #4]
	bl ov09_022186F0
	add sp, #0x1fc
	mov r0, #3
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_022515C2:
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0x10]
	add r0, #0x25
	strb r1, [r0]
	ldr r0, [r4, #4]
	bl ov09_022186F0
	ldrb r0, [r4, #0xe]
	add r0, r0, #1
	strb r0, [r4, #0xe]
_022515D6:
	ldr r1, [r4, #4]
	add r0, r1, #0
	add r0, #0x26
	ldrb r0, [r0]
	cmp r0, #0
	beq _022515FE
	mov r0, #0
	add r1, #0x26
	strb r0, [r1]
	ldr r0, [r4, #4]
	add r0, #0x25
	ldrb r0, [r0]
	strb r0, [r4, #0x10]
	ldr r1, [r4, #4]
	ldrh r0, [r1, #0x1c]
	cmp r0, #0
	beq _0225162A
	ldrb r0, [r1, #0x1e]
	cmp r0, #3
	bls _02251602
_022515FE:
	bl _02251FEA
_02251602:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225160E: ; jump table
	.short _02251616 - _0225160E - 2 ; case 0
	.short _02251616 - _0225160E - 2 ; case 1
	.short _02251620 - _0225160E - 2 ; case 2
	.short _02251620 - _0225160E - 2 ; case 3
_02251616:
	add sp, #0x1fc
	mov r0, #4
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251620:
	add sp, #0x1fc
	mov r0, #6
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_0225162A:
	add sp, #0x1fc
	mov r0, #6
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251634:
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF88
	str r0, [sp, #0x14]
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02251660
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _02251660
	ldrb r1, [r4, #0xd]
	mov r0, #1
	add r7, r1, #0
	and r7, r0
	b _02251662
_02251660:
	ldrb r7, [r4, #0xd]
_02251662:
	ldr r0, [r4, #8]
	mov r1, #6
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl Party_InitWithMaxSize
	ldr r0, [sp, #0x14]
	mov r6, #0
	bl Party_GetCount
	cmp r0, #0
	ble _022516B0
	mov r0, #6
	mul r0, r7
	add r5, r4, r0
_02251680:
	ldrb r2, [r5, #0x18]
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_02230014
	add r1, r0, #0
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl Party_AddMon
	ldr r1, [r4, #8]
	ldrb r0, [r5, #0x18]
	ldr r1, [r1, #4]
	add r5, r5, #1
	add r1, r1, r6
	add r1, #0x2c
	strb r0, [r1]
	ldr r0, [sp, #0x14]
	add r6, r6, #1
	bl Party_GetCount
	cmp r6, r0
	blt _02251680
_022516B0:
	ldr r0, [r4, #8]
	ldr r1, [r4]
	ldr r0, [r0, #4]
	str r1, [r0, #8]
	ldr r0, [r4, #8]
	mov r1, #5
	ldr r0, [r0, #4]
	str r1, [r0, #0xc]
	ldr r1, [r4, #8]
	mov r0, #0
	ldr r1, [r1, #4]
	strb r0, [r1, #0x11]
	ldr r1, [r4, #8]
	ldr r1, [r1, #4]
	add r1, #0x36
	strb r0, [r1]
	ldr r1, [r4, #8]
	ldr r1, [r1, #4]
	strh r0, [r1, #0x24]
	ldr r0, [r4, #8]
	mov r1, #2
	ldr r0, [r0, #4]
	add r0, #0x35
	strb r1, [r0]
	ldr r0, [r4, #4]
	ldrh r1, [r0, #0x1c]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	strh r1, [r0, #0x22]
	ldr r0, [r4, #4]
	ldrb r1, [r0, #0x1e]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	add r0, #0x33
	strb r1, [r0]
	ldr r0, [r4, #4]
	ldr r1, [r0, #0x10]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	str r1, [r0, #0x28]
	ldr r0, [r4, #8]
	ldrb r1, [r4, #0x10]
	ldr r0, [r0, #4]
	add r0, #0x32
	strb r1, [r0]
	ldrb r0, [r4, #0xd]
	ldr r2, [r4, #8]
	add r0, r2, r0
	ldrb r1, [r0, #0xc]
	ldr r0, [r2, #4]
	strb r1, [r0, #0x14]
	ldrb r1, [r4, #0xd]
	ldr r5, [r4, #8]
	ldr r0, [r4]
	bl ov11_022302BC
	add r0, r5, r0
	ldrb r1, [r0, #0xc]
	ldr r0, [r5, #4]
	strb r1, [r0, #0x15]
	ldrb r0, [r4, #0xf]
	cmp r0, #4
	bne _02251746
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_022302BC
	add r0, r4, r0
	add r0, #0x30
	ldrb r1, [r0]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	str r1, [r0, #0x18]
	ldrb r0, [r4, #0xd]
	b _0225175C
_02251746:
	ldrb r0, [r4, #0xd]
	add r0, r4, r0
	add r0, #0x30
	ldrb r1, [r0]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	str r1, [r0, #0x18]
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_022302BC
_0225175C:
	add r0, r4, r0
	add r0, #0x30
	ldrb r1, [r0]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	str r1, [r0, #0x1c]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	bl ov07_02211E60
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_0225177C:
	ldr r0, [r4, #8]
	ldr r1, [r0, #4]
	add r0, r1, #0
	add r0, #0x36
	ldrb r0, [r0]
	cmp r0, #0
	beq _02251832
	add r1, #0x32
	ldrb r0, [r1]
	mov r1, #0
	strb r0, [r4, #0x10]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	add r0, #0x36
	strb r1, [r0]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #0x11]
	cmp r0, #6
	bne _022517AE
	add sp, #0x1fc
	mov r0, #2
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_022517AE:
	add sp, #0x1fc
	mov r0, #6
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_022517B8:
	ldr r0, [r4]
	bl ov11_0222D88C
	ldr r0, [r4]
	bl ov11_02230094
	ldrb r1, [r4, #0x10]
	bl ov11_0225C778
	mov r0, #7
	str r0, [sp]
	mov r0, #0
	mov r1, #5
	str r0, [sp, #4]
	mov r2, #3
	add r3, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	lsl r2, r2, #0xa
	sub r3, #0xd
	bl sub_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	mov r1, #0xa
	str r0, [sp, #4]
	add r3, r1, #0
	str r0, [sp, #8]
	ldr r2, _02251850 ; =0x0000FFFF
	add r0, r5, #0
	sub r3, #0x12
	bl sub_02003210
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251808:
	bl sub_020038E4
	cmp r0, #0
	bne _02251832
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #0
	bl sub_020143A8
	ldr r0, [r4, #4]
	ldrh r0, [r0, #0x1c]
	cmp r0, #0
	bne _02251826
	b _022519D2
_02251826:
	mov r0, #9
	strb r0, [r4, #0xe]
	ldr r0, [r4, #4]
	ldrb r1, [r0, #0x1e]
	cmp r1, #3
	bls _02251834
_02251832:
	b _02251FEA
_02251834:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02251840: ; jump table
	.short _022518F4 - _02251840 - 2 ; case 0
	.short _02251848 - _02251840 - 2 ; case 1
	.short _022519C8 - _02251840 - 2 ; case 2
	.short _0225195E - _02251840 - 2 ; case 3
_02251848:
	ldrh r1, [r0, #0x1c]
	ldr r0, _02251854 ; =0x0000FFE4
	b _02251858
	nop
_02251850: .word 0x0000FFFF
_02251854: .word 0x0000FFE4
_02251858:
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _0225186C
	add sp, #0x1fc
	mov r0, #8
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_0225186C:
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #0x11]
	cmp r0, #2
	bhs _0225188A
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #3
	beq _02251894
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #0x13
	beq _02251894
_0225188A:
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #0x11]
	cmp r0, #1
	bhs _022518EA
_02251894:
	ldr r0, [r4, #4]
	ldrh r0, [r0, #0x1c]
	cmp r0, #0x17
	ldr r0, [r4]
	bne _022518C4
	bl ov11_02230E20
	cmp r0, #1
	bne _022518B0
	add sp, #0x1fc
	mov r0, #0x11
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022518B0:
	mov r1, #0x74
	ldr r0, _02251BF8 ; =0x000005EC
	mvn r1, r1
	bl sub_020054A8
	add sp, #0x1fc
	mov r0, #0x15
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022518C4:
	bl ov11_02230E20
	cmp r0, #1
	bne _022518D6
	add sp, #0x1fc
	mov r0, #0x19
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022518D6:
	mov r1, #0x74
	ldr r0, _02251BF8 ; =0x000005EC
	mvn r1, r1
	bl sub_020054A8
	add sp, #0x1fc
	mov r0, #0x1d
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022518EA:
	add sp, #0x1fc
	mov r0, #8
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_022518F4:
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #0x11]
	cmp r0, #2
	bhs _02251912
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #3
	beq _0225191C
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #0x13
	beq _0225191C
_02251912:
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #0x11]
	cmp r0, #1
	bhs _02251954
_0225191C:
	ldr r0, [r4, #4]
	mov r1, #0x26
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251954
	ldr r0, [r4]
	bl ov11_02230E20
	cmp r0, #1
	bne _02251940
	add sp, #0x1fc
	mov r0, #0x11
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_02251940:
	mov r1, #0x74
	ldr r0, _02251BF8 ; =0x000005EC
	mvn r1, r1
	bl sub_020054A8
	add sp, #0x1fc
	mov r0, #0x15
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_02251954:
	add sp, #0x1fc
	mov r0, #8
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_0225195E:
	ldrh r1, [r0, #0x1c]
	ldr r0, _02251BFC ; =0x0000FFC1
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #1
	bhi _02251976
	add sp, #0x1fc
	mov r0, #8
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251976:
	cmp r1, #0x37
	ldr r0, [r4]
	bne _022519A2
	bl ov11_02230E20
	cmp r0, #1
	bne _0225198E
	add sp, #0x1fc
	mov r0, #0xd
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_0225198E:
	mov r1, #0x74
	ldr r0, _02251BF8 ; =0x000005EC
	mvn r1, r1
	bl sub_020054A8
	add sp, #0x1fc
	mov r0, #0xf
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022519A2:
	bl ov11_02230E20
	cmp r0, #1
	bne _022519B4
	add sp, #0x1fc
	mov r0, #0xb
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022519B4:
	mov r1, #0x74
	ldr r0, _02251BF8 ; =0x000005EC
	mvn r1, r1
	bl sub_020054A8
	add sp, #0x1fc
	mov r0, #0xf
	add sp, #0x14
	strh r0, [r4, #0x12]
	pop {r3, r4, r5, r6, r7, pc}
_022519C8:
	add sp, #0x1fc
	mov r0, #8
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_022519D2:
	add sp, #0x1fc
	mov r0, #8
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_022519DC:
	ldr r2, [r4, #4]
	ldrh r0, [r2, #0x1c]
	cmp r0, #0
	bne _022519EC
	mov r1, #0xff
	add r0, sp, #0x1c
	strh r1, [r0]
	b _02251A08
_022519EC:
	add r1, sp, #0x1c
	strh r0, [r1]
	ldrb r0, [r2, #0x1e]
	strb r0, [r1, #2]
	cmp r0, #1
	bhi _02251A08
	ldr r0, [r4, #8]
	ldr r2, [r0, #4]
	ldrb r0, [r2, #0x11]
	add r0, r2, r0
	add r0, #0x2c
	ldrb r0, [r0]
	add r0, r0, #1
	strb r0, [r1, #3]
_02251A08:
	add r3, sp, #0x1c
	ldrb r1, [r4, #0xd]
	mov r2, sp
	ldrh r5, [r3]
	ldr r0, [r4]
	sub r2, r2, #4
	strh r5, [r2]
	ldrh r3, [r3, #2]
	strh r3, [r2, #2]
	ldr r2, [r2]
	bl ov11_022558C4
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	bl FreeToHeap
	ldr r0, [r4, #8]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add r0, r7, #0
	bl sub_0200CAB4
	add sp, #0x1fc
	add sp, #0x14
	pop {r3, r4, r5, r6, r7, pc}
_02251A5A:
	ldr r1, _02251C00 ; =0x000004B6
	add r0, sp, #0x8c
	strh r1, [r0, #2]
	mov r1, #5
	strb r1, [r0, #1]
	ldr r0, [r4, #4]
	ldrh r0, [r0, #0x1c]
	str r0, [sp, #0x90]
	ldr r0, [r4]
	bl ov11_022300C4
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #0x8c
	bl ov11_0223178C
	strb r0, [r4, #0x11]
	mov r0, #0x14
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251A96:
	ldrb r0, [r4, #0x11]
	bl sub_0201BD70
	cmp r0, #0
	bne _02251AAC
	ldrb r0, [r4, #0x17]
	sub r0, r0, #1
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0x17]
	cmp r0, #0
	beq _02251AAE
_02251AAC:
	b _02251FEA
_02251AAE:
	ldrh r0, [r4, #0x12]
	add sp, #0x1fc
	add sp, #0x14
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251AB8:
	ldrb r1, [r4, #0xd]
	mov r0, #9
	add r2, sp, #0x1b8
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF7C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r3, sp, #0x1b8
	bl ov11_02254404
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251AF8:
	ldr r0, [r4, #8]
	mov r1, #0
	ldr r0, [r0, #4]
	add r2, sp, #0x160
	ldrb r0, [r0, #0x11]
	mov r3, #1
	lsl r5, r0, #1
	mov r0, #9
	str r0, [sp]
	str r5, [sp, #4]
	str r5, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4]
	bl ov11_02256854
	ldr r0, [r4]
	add r1, r5, #0
	bl ov11_0222FF7C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r3, sp, #0x160
	bl ov11_02254404
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251B3E:
	ldr r0, [r4, #4]
	add r2, sp, #0x108
	ldrh r0, [r0, #0x1c]
	cmp r0, #0x37
	bne _02251B7C
	ldrb r0, [r4, #0xd]
	mov r1, #0
	add r3, r1, #0
	str r1, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x36
	str r0, [sp, #0xc]
	ldr r0, [r4]
	bl ov11_02256854
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF7C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r3, sp, #0x108
	bl ov11_02254404
	b _02251BE6
_02251B7C:
	cmp r0, #0x38
	bne _02251BB4
	ldrb r0, [r4, #0xd]
	mov r1, #0
	add r3, r1, #0
	str r1, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x74
	str r0, [sp, #0xc]
	ldr r0, [r4]
	bl ov11_02256854
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF7C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r3, sp, #0x108
	bl ov11_02254404
	b _02251BE6
_02251BB4:
	ldrb r1, [r4, #0xd]
	mov r0, #0xc
	mov r3, #1
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	bl ov11_02256854
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF7C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r3, sp, #0x108
	bl ov11_02254404
_02251BE6:
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251BF2:
	ldr r2, _02251C04 ; =0x000004B3
	b _02251C08
	nop
_02251BF8: .word 0x000005EC
_02251BFC: .word 0x0000FFC1
_02251C00: .word 0x000004B6
_02251C04: .word 0x000004B3
_02251C08:
	add r0, sp, #0x68
	strh r2, [r0, #2]
	mov r1, #0xc
	strb r1, [r0, #1]
	ldrb r1, [r4, #0xd]
	ldr r3, [r4, #8]
	add r3, r3, r1
	ldrb r3, [r3, #0xc]
	lsl r3, r3, #8
	orr r1, r3
	str r1, [sp, #0x6c]
	ldr r1, [r4, #4]
	ldrh r1, [r1, #0x1c]
	sub r1, #0x37
	cmp r1, #7
	bhi _02251C7A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02251C34: ; jump table
	.short _02251C68 - _02251C34 - 2 ; case 0
	.short _02251C72 - _02251C34 - 2 ; case 1
	.short _02251C44 - _02251C34 - 2 ; case 2
	.short _02251C4A - _02251C34 - 2 ; case 3
	.short _02251C50 - _02251C34 - 2 ; case 4
	.short _02251C56 - _02251C34 - 2 ; case 5
	.short _02251C5C - _02251C34 - 2 ; case 6
	.short _02251C62 - _02251C34 - 2 ; case 7
_02251C44:
	mov r0, #1
	str r0, [sp, #0x70]
	b _02251C7A
_02251C4A:
	mov r0, #2
	str r0, [sp, #0x70]
	b _02251C7A
_02251C50:
	mov r0, #3
	str r0, [sp, #0x70]
	b _02251C7A
_02251C56:
	mov r0, #6
	str r0, [sp, #0x70]
	b _02251C7A
_02251C5C:
	mov r0, #4
	str r0, [sp, #0x70]
	b _02251C7A
_02251C62:
	mov r0, #5
	str r0, [sp, #0x70]
	b _02251C7A
_02251C68:
	add r1, r2, #1
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	b _02251C7A
_02251C72:
	add r1, r2, #2
	strh r1, [r0, #2]
	mov r1, #2
	strb r1, [r0, #1]
_02251C7A:
	ldr r0, [r4]
	bl ov11_022300C4
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #0x68
	bl ov11_0223178C
	strb r0, [r4, #0x11]
	mov r0, #0x14
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251CA6:
	ldr r0, [r4, #8]
	mov r1, #0
	ldr r0, [r0, #4]
	add r2, sp, #0xb0
	ldrb r0, [r0, #0x11]
	mov r3, #1
	lsl r5, r0, #1
	mov r0, #0xe
	str r0, [sp]
	str r5, [sp, #4]
	str r5, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r4]
	bl ov11_02256854
	ldr r0, [r4]
	add r1, r5, #0
	bl ov11_0222FF7C
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r2, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r3, sp, #0xb0
	bl ov11_02254404
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251CEC:
	ldr r0, [r4, #8]
	ldr r1, [r0, #4]
	ldrb r0, [r1, #0x11]
	lsl r6, r0, #1
	add r0, r1, r0
	add r0, #0x2c
	ldrb r7, [r0]
	ldr r0, [r4]
	add r1, r6, #0
	bl ov11_02231380
	mov r1, #0
	mov r2, #1
	add r5, r0, #0
	bl MI_CpuFill8
	ldr r0, [r4]
	add r1, r6, #0
	bl ov11_02230260
	str r0, [sp, #0x18]
	ldr r0, [r4]
	bl ov11_0222FF74
	add r1, r0, #0
	ldr r0, [sp, #0x18]
	bl ov11_02257F6C
	add r1, r5, #0
	add r1, #0x25
	strb r0, [r1]
	ldr r0, [r4]
	add r1, r6, #0
	add r2, r7, #0
	bl ov11_02230014
	mov r1, #0xa2
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	ldr r1, [r4, #8]
	mov r2, #0
	ldr r1, [r1, #4]
	ldrh r1, [r1, #0x20]
	sub r0, r0, r1
	str r0, [r5, #0x28]
	add r0, r6, #0
	mov r1, #0xa3
	bl GetMonData
	str r0, [r5, #0x2c]
	ldr r0, [r4, #8]
	mov r1, #0x9f
	ldr r0, [r0, #4]
	mov r2, #0
	ldrh r0, [r0, #0x20]
	str r0, [r5, #0x30]
	add r0, r6, #0
	bl GetMonData
	cmp r0, #0
	bne _02251D72
	add r0, r5, #0
	mov r1, #0
	add r0, #0x4a
	strb r1, [r0]
_02251D72:
	ldr r1, [r5, #0x30]
	add r0, r5, #0
	bl ov11_02257150
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251D86:
	ldr r1, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r1, #4]
	ldrb r1, [r1, #0x11]
	lsl r1, r1, #1
	bl ov11_02231380
	add r5, r0, #0
	bl ov11_02257184
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02251DA4
	b _02251FEA
_02251DA4:
	mov r2, #1
	add r0, r5, #0
	mov r1, #0
	lsl r2, r2, #8
	bl ov11_02256D70
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251DBC:
	ldr r0, [r4]
	bl ov11_022300C4
	add r5, r0, #0
	ldr r0, [r4, #8]
	ldr r1, [r0, #4]
	ldrb r0, [r1, #0x11]
	ldrh r1, [r1, #0x20]
	lsl r0, r0, #1
	cmp r1, #0
	add r1, sp, #0x1c
	beq _02251DF4
	ldr r2, _02251FF0 ; =0x000004BE
	strh r2, [r1, #0x2a]
	mov r2, #0x11
	add r1, sp, #0x44
	strb r2, [r1, #1]
	ldr r1, [r4, #8]
	add r1, r1, r0
	ldrb r1, [r1, #0xc]
	lsl r1, r1, #8
	orr r0, r1
	str r0, [sp, #0x48]
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldrh r0, [r0, #0x20]
	str r0, [sp, #0x4c]
	b _02251E0A
_02251DF4:
	ldr r2, _02251FF4 ; =0x000004E2
	strh r2, [r1, #0x2a]
	mov r2, #2
	add r1, sp, #0x44
	strb r2, [r1, #1]
	ldr r1, [r4, #8]
	add r1, r1, r0
	ldrb r1, [r1, #0xc]
	lsl r1, r1, #8
	orr r0, r1
	str r0, [sp, #0x48]
_02251E0A:
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #0x44
	bl ov11_0223178C
	strb r0, [r4, #0x11]
	mov r0, #0x14
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251E2E:
	ldr r0, [r4, #8]
	mov r5, #0
	ldr r0, [r0, #4]
	ldrb r0, [r0, #0x11]
	lsl r7, r0, #1
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_02231380
	str r0, [sp, #0x10]
	ldr r0, [r4, #8]
	add r1, r7, #0
	ldr r3, [r0, #4]
	ldr r0, [r4]
	ldrb r2, [r3, #0x11]
	add r2, r3, r2
	add r2, #0x2c
	ldrb r2, [r2]
	bl ov11_02230014
	mov r1, #0x9f
	add r2, r5, #0
	bl GetMonData
	cmp r0, #0
	bne _02251E6A
	ldr r0, [sp, #0x10]
	add r1, r5, #0
	add r0, #0x4a
	strb r1, [r0]
_02251E6A:
	ldr r0, [sp, #0x10]
	mov r2, #1
	add r1, r0, #0
	ldr r1, [r1, #0x28]
	lsl r2, r2, #8
	bl ov11_02256D70
	mov r1, #2
	add r0, sp, #0x1c
	strb r1, [r0, #5]
	ldr r0, [r4, #8]
	mov r1, #0xf
	add r0, r0, r7
	ldrb r0, [r0, #0xc]
	mov r2, #5
	lsl r0, r0, #8
	orr r0, r7
	str r0, [sp, #0x24]
	ldr r0, [r4, #4]
	ldrh r0, [r0, #0x1c]
	bl GetItemAttr
	cmp r0, #0
	beq _02251E9E
	mov r6, #0
	add r5, r5, #1
_02251E9E:
	ldr r0, [r4, #4]
	mov r1, #0x10
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251EB2
	mov r6, #1
	add r5, r5, #1
_02251EB2:
	ldr r0, [r4, #4]
	mov r1, #0x11
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251EC6
	mov r6, #2
	add r5, r5, #1
_02251EC6:
	ldr r0, [r4, #4]
	mov r1, #0x12
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251EDA
	mov r6, #3
	add r5, r5, #1
_02251EDA:
	ldr r0, [r4, #4]
	mov r1, #0x13
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251EEE
	mov r6, #4
	add r5, r5, #1
_02251EEE:
	ldr r0, [r4, #4]
	mov r1, #0x14
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251F02
	mov r6, #5
	add r5, r5, #1
_02251F02:
	ldr r0, [r4, #4]
	mov r1, #0x15
	ldrh r0, [r0, #0x1c]
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02251F16
	mov r6, #6
	add r5, r5, #1
_02251F16:
	cmp r5, #1
	beq _02251F22
	ldr r1, _02251FF8 ; =0x000004CD
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F22:
	cmp r6, #6
	bhi _02251F76
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02251F32: ; jump table
	.short _02251F40 - _02251F32 - 2 ; case 0
	.short _02251F48 - _02251F32 - 2 ; case 1
	.short _02251F50 - _02251F32 - 2 ; case 2
	.short _02251F58 - _02251F32 - 2 ; case 3
	.short _02251F60 - _02251F32 - 2 ; case 4
	.short _02251F68 - _02251F32 - 2 ; case 5
	.short _02251F70 - _02251F32 - 2 ; case 6
_02251F40:
	ldr r1, _02251FFC ; =0x000004BA
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F48:
	ldr r1, _02252000 ; =0x000004B7
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F50:
	ldr r1, _02252004 ; =0x000004B9
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F58:
	ldr r1, _02252008 ; =0x000004BB
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F60:
	ldr r1, _0225200C ; =0x000004B8
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F68:
	ldr r1, _02252010 ; =0x000004BC
	add r0, sp, #0x1c
	strh r1, [r0, #6]
	b _02251F76
_02251F70:
	ldr r1, _02252014 ; =0x000004BD
	add r0, sp, #0x1c
	strh r1, [r0, #6]
_02251F76:
	ldr r0, [r4]
	bl ov11_022300C4
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #0x20
	bl ov11_0223178C
	strb r0, [r4, #0x11]
	mov r0, #0x14
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251FA2:
	ldr r0, [r4]
	bl ov11_02230070
	bl ov08_02212384
	ldr r0, [r4]
	bl ov11_02230070
	bl ov08_022123A0
	cmp r0, #0
	bne _02251FEA
	ldr r0, [r4]
	bl ov11_02230070
	bl ov08_022123B0
	ldrb r0, [r4, #0xe]
	add sp, #0x1fc
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, r6, r7, pc}
_02251FD0:
	ldrb r0, [r4, #0x11]
	bl sub_0201BD70
	cmp r0, #0
	bne _02251FEA
	ldrb r0, [r4, #0x17]
	sub r0, r0, #1
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0x17]
	cmp r0, #0
	bne _02251FEA
	mov r0, #8
	strb r0, [r4, #0xe]
_02251FEA:
	add sp, #0x1fc
	add sp, #0x14
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02251FF0: .word 0x000004BE
_02251FF4: .word 0x000004E2
_02251FF8: .word 0x000004CD
_02251FFC: .word 0x000004BA
_02252000: .word 0x000004B7
_02252004: .word 0x000004B9
_02252008: .word 0x000004BB
_0225200C: .word 0x000004B8
_02252010: .word 0x000004BC
_02252014: .word 0x000004BD

	thumb_func_start ov11_02252018
ov11_02252018: ; 0x02252018
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #1
	add r3, sp, #0
	strh r0, [r3]
	add r4, r1, #0
	mov r2, sp
	ldrb r1, [r4, #0xd]
	ldrh r6, [r3]
	ldr r0, [r4]
	sub r2, r2, #4
	strh r6, [r2]
	ldrh r3, [r3, #2]
	strh r3, [r2, #2]
	ldr r2, [r2]
	bl ov11_022558C4
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	bl FreeToHeap
	ldr r0, [r4, #8]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02252070
ov11_02252070: ; 0x02252070
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, [r4, #8]
	ldr r0, [r0, #4]
	bl FreeToHeap
	ldr r0, [r4, #8]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022520A8
ov11_022520A8: ; 0x022520A8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_022300CC
	ldrb r1, [r4, #0xa]
	add r5, r0, #0
	cmp r1, #3
	bhi _02252144
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022520CA: ; jump table
	.short _022520D2 - _022520CA - 2 ; case 0
	.short _0225213C - _022520CA - 2 ; case 1
	.short _022523B2 - _022520CA - 2 ; case 2
	.short _0225240E - _022520CA - 2 ; case 3
_022520D2:
	ldr r0, [r4]
	mov r1, #0
	bl ov11_0222FF6C
	add r6, r0, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add r0, r6, #0
	bl CopyWindowPixelsToVram_TextMode
	ldr r0, [r4]
	bl ov11_02230094
	bl ov11_0225C76C
	strb r0, [r4, #0x17]
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	mov r2, #3
	str r1, [sp]
	mov r0, #7
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #5
	add r3, r1, #0
	add r0, r5, #0
	lsl r2, r2, #0xa
	sub r3, #0xd
	bl sub_02003210
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0xa
	add r3, r1, #0
	ldr r2, _0225246C ; =0x0000FFFF
	add r0, r5, #0
	sub r3, #0x12
	bl sub_02003210
	ldrb r0, [r4, #0xa]
	add sp, #0x24
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_0225213C:
	bl sub_020038E4
	cmp r0, #0
	beq _02252146
_02252144:
	b _02252468
_02252146:
	ldr r0, [r4]
	bl ov11_0222D7F8
	mov r0, #5
	mov r1, #0x38
	bl AllocFromHeap
	str r0, [r4, #4]
	mov r0, #5
	bl SaveArray_Party_Alloc
	ldr r1, [r4, #4]
	str r0, [r1]
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #0xc
	and r0, r1
	cmp r0, #0xc
	beq _0225217A
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #0xcb
	beq _0225217A
	b _0225228E
_0225217A:
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02230260
	cmp r0, #2
	bne _02252196
	ldrb r0, [r4, #9]
	str r0, [sp, #0x18]
	ldr r0, [r4]
	ldr r1, [sp, #0x18]
	bl ov11_022302BC
	str r0, [sp, #0x14]
	b _022521A4
_02252196:
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_022302BC
	str r0, [sp, #0x18]
	ldrb r0, [r4, #9]
	str r0, [sp, #0x14]
_022521A4:
	mov r0, #5
	bl AllocMonZeroed
	add r6, r0, #0
	mov r5, #0
_022521AE:
	ldr r0, [r4, #4]
	add r1, r6, #0
	ldr r0, [r0]
	bl Party_AddMon
	add r5, r5, #1
	cmp r5, #6
	blt _022521AE
	add r0, r6, #0
	bl FreeToHeap
	ldr r0, [r4]
	ldr r1, [sp, #0x18]
	mov r7, #0
	bl ov11_0222FFC8
	cmp r0, #0
	ble _02252216
	ldr r0, [sp, #0x18]
	mov r1, #6
	mul r1, r0
	add r5, r4, r1
	add r6, r7, #0
_022521DC:
	ldrb r2, [r5, #0x1c]
	ldr r0, [r4]
	ldr r1, [sp, #0x18]
	bl ov11_02230014
	str r0, [sp, #0x1c]
	ldr r0, [r4, #4]
	add r1, r6, #0
	ldr r0, [r0]
	bl Party_GetMonByIndex
	add r1, r0, #0
	ldr r0, [sp, #0x1c]
	bl CopyPokemonToPokemon
	ldr r0, [r4, #4]
	ldrb r1, [r5, #0x1c]
	add r0, r0, r6
	add r0, #0x2c
	strb r1, [r0]
	ldr r0, [r4]
	ldr r1, [sp, #0x18]
	add r5, r5, #1
	add r6, r6, #2
	add r7, r7, #1
	bl ov11_0222FFC8
	cmp r7, r0
	blt _022521DC
_02252216:
	ldr r0, [r4]
	ldr r1, [sp, #0x14]
	mov r6, #0
	bl ov11_0222FFC8
	cmp r0, #0
	ble _02252272
	ldr r0, [sp, #0x14]
	mov r1, #6
	mul r1, r0
	mov r0, #1
	add r5, r4, r1
	str r0, [sp, #0xc]
	add r7, r6, #0
_02252232:
	ldrb r2, [r5, #0x1c]
	ldr r0, [r4]
	ldr r1, [sp, #0x14]
	bl ov11_02230014
	str r0, [sp, #0x20]
	ldr r0, [r4, #4]
	ldr r1, [sp, #0xc]
	ldr r0, [r0]
	bl Party_GetMonByIndex
	add r1, r0, #0
	ldr r0, [sp, #0x20]
	bl CopyPokemonToPokemon
	ldr r0, [r4, #4]
	ldrb r1, [r5, #0x1c]
	add r0, r0, r7
	add r0, #0x2d
	strb r1, [r0]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x14]
	add r0, r0, #2
	str r0, [sp, #0xc]
	ldr r0, [r4]
	add r5, r5, #1
	add r7, r7, #2
	add r6, r6, #1
	bl ov11_0222FFC8
	cmp r6, r0
	blt _02252232
_02252272:
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_02230260
	cmp r0, #4
	bne _02252286
	ldr r0, [r4, #4]
	mov r1, #1
	strb r1, [r0, #0x11]
	b _0225230E
_02252286:
	ldr r0, [r4, #4]
	mov r1, #0
	strb r1, [r0, #0x11]
	b _0225230E
_0225228E:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _022522B0
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	bne _022522B0
	ldrb r1, [r4, #9]
	mov r0, #1
	add r7, r1, #0
	and r7, r0
	b _022522B4
_022522B0:
	ldrb r1, [r4, #9]
	add r7, r1, #0
_022522B4:
	ldr r0, [r4]
	bl ov11_02230260
	cmp r0, #4
	bne _022522C2
	mov r1, #1
	b _022522C4
_022522C2:
	mov r1, #0
_022522C4:
	ldr r0, [r4, #4]
	strb r1, [r0, #0x11]
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_0222FF88
	str r0, [sp, #0x10]
	mov r5, #0
	bl Party_GetCount
	cmp r0, #0
	ble _0225230E
	mov r0, #6
	mul r0, r7
	add r6, r4, r0
_022522E2:
	ldrb r2, [r6, #0x1c]
	ldr r0, [r4]
	add r1, r7, #0
	bl ov11_02230014
	add r1, r0, #0
	ldr r0, [r4, #4]
	ldr r0, [r0]
	bl Party_AddMon
	ldr r0, [r4, #4]
	ldrb r1, [r6, #0x1c]
	add r0, r0, r5
	add r0, #0x2c
	strb r1, [r0]
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r5, r5, #1
	bl Party_GetCount
	cmp r5, r0
	blt _022522E2
_0225230E:
	ldr r1, [r4]
	ldr r0, [r4, #4]
	str r1, [r0, #8]
	ldr r0, [r4, #4]
	mov r1, #5
	str r1, [r0, #0xc]
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x36
	strb r1, [r0]
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #4]
	strh r1, [r0, #0x24]
	ldrb r1, [r4, #0x16]
	ldr r0, [r4, #4]
	strb r1, [r0, #0x12]
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0xb]
	add r0, #0x35
	strb r1, [r0]
	ldrh r1, [r4, #0x14]
	ldr r0, [r4, #4]
	strh r1, [r0, #0x22]
	ldrb r1, [r4, #9]
	ldr r0, [r4, #4]
	str r1, [r0, #0x28]
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0x17]
	add r0, #0x32
	strb r1, [r0]
	ldrb r0, [r4, #9]
	bl MaskOfFlagNo
	ldrb r1, [r4, #0x18]
	tst r0, r1
	bne _0225235E
	ldrb r0, [r4, #9]
	add r0, r4, r0
	ldrb r1, [r0, #0xc]
	b _02252360
_0225235E:
	mov r1, #6
_02252360:
	ldr r0, [r4, #4]
	strb r1, [r0, #0x14]
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	beq _02252378
	ldr r0, [r4, #4]
	mov r1, #6
	strb r1, [r0, #0x15]
	b _022523A2
_02252378:
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_022302BC
	bl MaskOfFlagNo
	ldrb r1, [r4, #0x18]
	tst r0, r1
	bne _0225239C
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_022302BC
	add r0, r4, r0
	ldrb r1, [r0, #0xc]
	ldr r0, [r4, #4]
	strb r1, [r0, #0x15]
	b _022523A2
_0225239C:
	ldr r0, [r4, #4]
	mov r1, #6
	strb r1, [r0, #0x15]
_022523A2:
	ldr r0, [r4, #4]
	bl ov07_02211E60
	ldrb r0, [r4, #0xa]
	add sp, #0x24
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_022523B2:
	ldr r0, [r4, #4]
	add r0, #0x36
	ldrb r0, [r0]
	cmp r0, #0
	beq _02252468
	ldr r0, [r4]
	bl ov11_0222D88C
	ldr r0, [r4]
	bl ov11_02230094
	ldr r1, [r4, #4]
	add r1, #0x32
	ldrb r1, [r1]
	bl ov11_0225C778
	mov r0, #7
	str r0, [sp]
	mov r0, #0
	mov r1, #5
	str r0, [sp, #4]
	mov r2, #3
	add r3, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	lsl r2, r2, #0xa
	sub r3, #0xd
	bl sub_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	mov r1, #0xa
	str r0, [sp, #4]
	add r3, r1, #0
	str r0, [sp, #8]
	ldr r2, _0225246C ; =0x0000FFFF
	add r0, r5, #0
	sub r3, #0x12
	bl sub_02003210
	ldrb r0, [r4, #0xa]
	add sp, #0x24
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r4, r5, r6, r7, pc}
_0225240E:
	bl sub_020038E4
	cmp r0, #0
	bne _02252468
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #0
	bl sub_020143A8
	ldr r3, [r4, #4]
	ldr r0, [r4]
	ldrb r2, [r3, #0x11]
	cmp r2, #6
	bne _02252436
	ldrb r1, [r4, #9]
	mov r2, #0xff
	bl ov11_02255964
	b _02252444
_02252436:
	add r2, r3, r2
	add r2, #0x2c
	ldrb r2, [r2]
	ldrb r1, [r4, #9]
	add r2, r2, #1
	bl ov11_02255964
_02252444:
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	ldr r0, [r4, #4]
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_02252468:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0225246C: .word 0x0000FFFF

	thumb_func_start ov11_02252470
ov11_02252470: ; 0x02252470
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	str r0, [sp]
	ldr r0, [r5]
	bl ov11_0222FF74
	mov r1, #0x10
	ldrb r6, [r5, #9]
	tst r1, r0
	bne _0225248C
	mov r1, #8
	tst r0, r1
	beq _02252490
_0225248C:
	str r6, [sp, #4]
	b _0225249A
_02252490:
	ldr r0, [r5]
	add r1, r6, #0
	bl ov11_022302BC
	str r0, [sp, #4]
_0225249A:
	ldr r0, [r5]
	add r1, r6, #0
	bl ov16_021F4A30
	add r4, r0, #0
	cmp r4, #6
	bne _022524FE
	ldr r0, [r5]
	add r1, r6, #0
	bl ov16_021F4698
	add r4, r0, #0
	cmp r4, #6
	bne _022524FE
	ldrb r1, [r5, #9]
	ldr r0, [r5]
	bl ov11_0222FF88
	str r0, [sp, #8]
	mov r4, #0
	bl Party_GetCount
	cmp r0, #0
	ble _022524FE
	ldr r0, [sp, #4]
	add r7, r5, r6
	add r6, r5, r0
_022524D0:
	ldrb r1, [r5, #9]
	ldr r0, [r5]
	add r2, r4, #0
	bl ov11_02230014
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022524F2
	ldrb r0, [r7, #0xc]
	cmp r4, r0
	beq _022524F2
	ldrb r0, [r6, #0xc]
	cmp r4, r0
	bne _022524FE
_022524F2:
	ldr r0, [sp, #8]
	add r4, r4, #1
	bl Party_GetCount
	cmp r4, r0
	blt _022524D0
_022524FE:
	ldrb r1, [r5, #9]
	ldr r0, [r5]
	add r2, r4, #1
	bl ov11_02255964
	ldrb r1, [r5, #9]
	ldrb r2, [r5, #8]
	ldr r0, [r5]
	bl ov11_022567B8
	add r0, r5, #0
	bl FreeToHeap
	ldr r0, [sp]
	bl sub_0200CAB4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_02252524
ov11_02252524: ; 0x02252524
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #9]
	add r5, r0, #0
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02252544
ov11_02252544: ; 0x02252544
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_0222FF68
	ldr r0, [r4]
	bl ov11_02230094
	add r5, r0, #0
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_0222FF7C
	str r0, [sp]
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	bl ov11_022302BC
	add r1, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r1, r0
	beq _0225257E
	ldr r0, [r4]
	bl ov11_02231380
	add r6, r0, #0
	b _02252580
_0225257E:
	mov r6, #0
_02252580:
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bhi _02252600
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02252592: ; jump table
	.short _0225259C - _02252592 - 2 ; case 0
	.short _022525EC - _02252592 - 2 ; case 1
	.short _0225267E - _02252592 - 2 ; case 2
	.short _0225269C - _02252592 - 2 ; case 3
	.short _022526E0 - _02252592 - 2 ; case 4
_0225259C:
	add r0, r5, #0
	bl ov11_02258F5C
	cmp r0, #0
	beq _02252600
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _022525E4
	ldr r0, [r4]
	bl ov11_022300C4
	add r5, r0, #0
	ldrb r0, [r4, #0xf]
	cmp r0, #5
	add r0, sp, #4
	bne _022525C6
	mov r1, #0x82
	strb r1, [r0, #5]
	ldr r0, [r4, #0x14]
	str r0, [sp, #0xc]
	b _022525CA
_022525C6:
	mov r1, #0
	strb r1, [r0, #5]
_022525CA:
	ldr r1, [r4, #0x10]
	add r0, sp, #4
	strh r1, [r0, #6]
	ldr r0, [r4]
	bl ov11_02230E54
	add r3, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	add r2, sp, #8
	bl ov11_0223178C
	strh r0, [r4, #0x1a]
_022525E4:
	mov r0, #1
	add sp, #0x2c
	strb r0, [r4, #0xe]
	pop {r4, r5, r6, r7, pc}
_022525EC:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl sub_0201BD70
	cmp r0, #0
	beq _02252602
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _02252602
_02252600:
	b _0225270A
_02252602:
	add r0, r5, #0
	bl ov11_02258E30
	ldrh r1, [r4, #0x18]
	add r0, sp, #4
	strh r1, [r0]
	ldrb r0, [r4, #0xf]
	cmp r0, #5
	bhi _02252672
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02252620: ; jump table
	.short _0225262C - _02252620 - 2 ; case 0
	.short _0225263A - _02252620 - 2 ; case 1
	.short _02252648 - _02252620 - 2 ; case 2
	.short _02252656 - _02252620 - 2 ; case 3
	.short _02252664 - _02252620 - 2 ; case 4
	.short _0225262C - _02252620 - 2 ; case 5
_0225262C:
	add r0, r5, #0
	mov r1, #0xd
	mov r2, #0
	add r3, sp, #4
	bl ov11_02258820
	b _02252676
_0225263A:
	add r0, r5, #0
	mov r1, #0xe
	mov r2, #0
	add r3, sp, #4
	bl ov11_02258820
	b _02252676
_02252648:
	add r0, r5, #0
	mov r1, #0xf
	mov r2, #0
	add r3, sp, #4
	bl ov11_02258820
	b _02252676
_02252656:
	add r0, r5, #0
	mov r1, #0x10
	mov r2, #0
	add r3, sp, #4
	bl ov11_02258820
	b _02252676
_02252664:
	add r0, r5, #0
	mov r1, #0x11
	mov r2, #0
	add r3, sp, #4
	bl ov11_02258820
	b _02252676
_02252672:
	bl GF_AssertFail
_02252676:
	mov r0, #2
	add sp, #0x2c
	strb r0, [r4, #0xe]
	pop {r4, r5, r6, r7, pc}
_0225267E:
	add r0, r5, #0
	bl ov11_02258E74
	mov r1, #0
	mvn r1, r1
	str r0, [r4, #8]
	cmp r0, r1
	beq _0225270A
	ldr r0, _02252710 ; =0x000005DD
	bl PlaySE
	mov r0, #3
	add sp, #0x2c
	strb r0, [r4, #0xe]
	pop {r4, r5, r6, r7, pc}
_0225269C:
	add r0, r5, #0
	bl ov11_02258F5C
	cmp r0, #1
	bne _0225270A
	ldr r0, [r4, #4]
	bl ov11_02257238
	ldr r0, [sp]
	bl ov11_0225468C
	add r0, r6, #0
	bl ov11_02258184
	add r0, r5, #0
	bl ov11_02258E30
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	add r3, r1, #0
	bl ov11_02258820
	ldr r0, [r4, #8]
	cmp r0, #1
	bne _022526D8
	add r0, r5, #0
	mov r1, #0
	bl ov11_0225B77C
_022526D8:
	mov r0, #4
	add sp, #0x2c
	strb r0, [r4, #0xe]
	pop {r4, r5, r6, r7, pc}
_022526E0:
	add r0, r5, #0
	bl ov11_0225B780
	cmp r0, #1
	bne _0225270A
	ldrb r1, [r4, #0xd]
	ldr r0, [r4]
	ldr r2, [r4, #8]
	bl ov11_02255528
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r7, #0
	bl sub_0200CAB4
_0225270A:
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_02252710: .word 0x000005DD

	thumb_func_start ov11_02252714
ov11_02252714: ; 0x02252714
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02252734
ov11_02252734: ; 0x02252734
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4, #0xd]
	add r5, r0, #0
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02252754
ov11_02252754: ; 0x02252754
	push {r3, r4, r5, lr}
	sub sp, #0x1fc
	sub sp, #0x14
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x6a
	ldrb r0, [r0]
	cmp r0, #0xa
	bls _0225276A
	b _022529B8
_0225276A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02252776: ; jump table
	.short _0225278C - _02252776 - 2 ; case 0
	.short _02252996 - _02252776 - 2 ; case 1
	.short _022527E6 - _02252776 - 2 ; case 2
	.short _02252996 - _02252776 - 2 ; case 3
	.short _02252842 - _02252776 - 2 ; case 4
	.short _02252996 - _02252776 - 2 ; case 5
	.short _02252890 - _02252776 - 2 ; case 6
	.short _02252996 - _02252776 - 2 ; case 7
	.short _02252918 - _02252776 - 2 ; case 8
	.short _02252996 - _02252776 - 2 ; case 9
	.short _02252974 - _02252776 - 2 ; case 10
_0225278C:
	ldrh r0, [r4, #0x1e]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _022527DA
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bne _022527DA
	ldr r0, [r4, #8]
	mov r1, #6
	bl sub_0200782C
	cmp r0, #0
	bne _022527DA
	add r0, r4, #0
	add r0, #0x69
	ldrb r1, [r0]
	mov r0, #0xf
	add r2, sp, #0x1b8
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0xc]
	add r3, sp, #0x1b8
	bl ov11_02254404
	add sp, #0x1fc
	mov r0, #1
	add r4, #0x6a
	add sp, #0x14
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_022527DA:
	add sp, #0x1fc
	mov r0, #4
	add r4, #0x6a
	add sp, #0x14
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_022527E6:
	add r3, r4, #0
	add r3, #0x69
	ldrb r3, [r3]
	ldr r0, [r4]
	add r1, #0x10
	add r2, sp, #0x168
	bl ov11_0225452C
	add r0, sp, #0x168
	mov r1, #5
	bl ov08_0222A494
	add r0, r4, #0
	add r0, #0x69
	ldrb r1, [r0]
	mov r0, #0x10
	add r2, sp, #0x110
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0xc]
	add r3, sp, #0x110
	bl ov11_02254404
	mov r0, #0x1a
	add sp, #0x1fc
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x6a
	ldrb r0, [r0]
	add r4, #0x6a
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252842:
	ldr r0, [r4]
	mov r1, #2
	bl ov11_02231484
	add r0, r4, #0
	add r0, #0x6b
	ldrb r0, [r0]
	cmp r0, #0
	beq _0225285A
	ldr r0, [r4]
	bl ov11_02231410
_0225285A:
	add r0, r4, #0
	add r0, #0x6c
	ldrb r0, [r0]
	cmp r0, #0
	beq _02252870
	ldr r0, [r4]
	bl ov11_02230068
	mov r1, #1
	bl sub_02008284
_02252870:
	add r3, r4, #0
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0xc]
	add r3, #0x10
	bl ov11_02254404
	add r0, r4, #0
	add r0, #0x6a
	ldrb r0, [r0]
	add sp, #0x1fc
	add r4, #0x6a
	add r0, r0, #1
	add sp, #0x14
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252890:
	ldr r0, [r4]
	mov r1, #0
	bl ov11_02231484
	add r0, r4, #0
	add r0, #0x6b
	ldrb r0, [r0]
	cmp r0, #0
	beq _022528A8
	ldr r0, [r4]
	bl ov11_022313E0
_022528A8:
	add r0, r4, #0
	add r0, #0x6c
	ldrb r0, [r0]
	cmp r0, #0
	beq _022528BE
	ldr r0, [r4]
	bl ov11_02230068
	mov r1, #1
	bl sub_02008290
_022528BE:
	ldrh r0, [r4, #0x1e]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0225290C
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bne _0225290C
	ldr r0, [r4, #8]
	mov r1, #6
	bl sub_0200782C
	cmp r0, #0
	bne _0225290C
	add r0, r4, #0
	add r0, #0x69
	ldrb r1, [r0]
	mov r0, #0xf
	add r2, sp, #0xb8
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0xc]
	add r3, sp, #0xb8
	bl ov11_02254404
	add sp, #0x1fc
	mov r0, #7
	add r4, #0x6a
	add sp, #0x14
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0225290C:
	add sp, #0x1fc
	mov r0, #0xa
	add r4, #0x6a
	add sp, #0x14
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252918:
	add r3, r4, #0
	add r3, #0x69
	ldrb r3, [r3]
	ldr r0, [r4]
	add r1, #0x10
	add r2, sp, #0x68
	bl ov11_0225452C
	add r0, sp, #0x68
	mov r1, #5
	bl ov08_0222A568
	add r0, r4, #0
	add r0, #0x69
	ldrb r1, [r0]
	mov r0, #0x10
	add r2, sp, #0x10
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #0xc]
	add r3, sp, #0x10
	bl ov11_02254404
	mov r0, #0x1a
	add sp, #0x1fc
	ldr r1, [r4, #4]
	mov r2, #1
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x6a
	ldrb r0, [r0]
	add r4, #0x6a
	add sp, #0x14
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252974:
	add r2, r4, #0
	add r1, #0x69
	add r2, #0x68
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	add sp, #0x1fc
	add sp, #0x14
	pop {r3, r4, r5, pc}
_02252996:
	ldr r0, [r4, #0xc]
	bl ov08_02212384
	ldr r0, [r4, #0xc]
	bl ov08_022123A0
	cmp r0, #0
	bne _022529B8
	ldr r0, [r4, #0xc]
	bl ov08_022123B0
	add r0, r4, #0
	add r0, #0x6a
	ldrb r0, [r0]
	add r4, #0x6a
	add r0, r0, #1
	strb r0, [r4]
_022529B8:
	add sp, #0x1fc
	add sp, #0x14
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022529C0
ov11_022529C0: ; 0x022529C0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #9]
	cmp r0, #6
	bhs _022529FA
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	bne _022529F4
	mov r0, #2
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #9]
	mov r1, #6
	add r0, r0, #1
	strb r0, [r4, #9]
	ldr r0, [r4, #4]
	bl sub_0200782C
	add r3, r0, #0
	mov r2, #1
	ldr r0, [r4, #4]
	mov r1, #6
	eor r2, r3
	bl sub_02007558
	pop {r3, r4, r5, pc}
_022529F4:
	sub r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_022529FA:
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0
	bl sub_02007558
	ldrb r1, [r4, #8]
	ldr r0, [r4]
	mov r2, #0x17
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02252A1C
ov11_02252A1C: ; 0x02252A1C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _02252A2E
	cmp r0, #1
	beq _02252A3C
	b _02252A52
_02252A2E:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	bl ov11_02257150
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_02252A3C:
	add r0, r4, #0
	bl ov11_02257184
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02252A6C
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252A52:
	add r2, r4, #0
	add r1, #0x24
	add r2, #0x4c
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4, #0xc]
	bl ov11_022567B8
	mov r0, #0
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl sub_0200CAB4
_02252A6C:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02252A70
ov11_02252A70: ; 0x02252A70
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _02252A86
	cmp r0, #1
	beq _02252AA2
	cmp r0, #2
	beq _02252AE8
	b _02252B0E
_02252A86:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x4e
	strb r1, [r0]
	ldr r0, _02252B2C ; =0x0000070B
	bl PlaySE
	ldr r1, [r4, #0x40]
	add r0, r4, #0
	bl ov11_022571B8
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
_02252AA2:
	add r0, r4, #0
	add r0, #0x4e
	ldrb r0, [r0]
	cmp r0, #8
	bhs _02252ABA
	add r0, r4, #0
	add r0, #0x4e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x4e
	strb r1, [r0]
_02252ABA:
	add r0, r4, #0
	bl ov11_022571EC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _02252B28
	add r0, r4, #0
	add r0, #0x4e
	ldrb r0, [r0]
	cmp r0, #8
	blo _02252AE0
	ldr r0, _02252B2C ; =0x0000070B
	mov r1, #0
	bl sub_020054F0
	mov r0, #0x64
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252AE0:
	ldrb r0, [r4]
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252AE8:
	add r0, r4, #0
	add r0, #0x4e
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x4e
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x4e
	ldrb r0, [r0]
	cmp r0, #8
	blo _02252B28
	ldr r0, _02252B2C ; =0x0000070B
	mov r1, #0
	bl sub_020054F0
	mov r0, #0x64
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02252B0E:
	add r2, r4, #0
	add r1, #0x24
	add r2, #0x4c
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4, #0xc]
	bl ov11_022567B8
	mov r0, #0
	str r0, [r4, #0x10]
	add r0, r5, #0
	bl sub_0200CAB4
_02252B28:
	pop {r3, r4, r5, pc}
	nop
_02252B2C: .word 0x0000070B

	thumb_func_start ov11_02252B30
ov11_02252B30: ; 0x02252B30
	push {r4, r5, r6, lr}
	sub sp, #0x110
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r1, r4, #0
	add r1, #0x66
	ldrb r1, [r1]
	add r5, r0, #0
	cmp r1, #0xa
	bls _02252B4C
	b _02252DAA
_02252B4C:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02252B58: ; jump table
	.short _02252B6E - _02252B58 - 2 ; case 0
	.short _02252C16 - _02252B58 - 2 ; case 1
	.short _02252BBA - _02252B58 - 2 ; case 2
	.short _02252C16 - _02252B58 - 2 ; case 3
	.short _02252C3A - _02252B58 - 2 ; case 4
	.short _02252C82 - _02252B58 - 2 ; case 5
	.short _02252C9C - _02252B58 - 2 ; case 6
	.short _02252CD8 - _02252B58 - 2 ; case 7
	.short _02252D04 - _02252B58 - 2 ; case 8
	.short _02252D44 - _02252B58 - 2 ; case 9
	.short _02252D8C - _02252B58 - 2 ; case 10
_02252B6E:
	add r0, r4, #0
	add r0, #0x70
	ldrh r0, [r0]
	cmp r0, #0
	beq _02252BB0
	add r0, r4, #0
	add r0, #0x65
	ldrb r1, [r0]
	mov r0, #0xf
	add r2, sp, #0xb8
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0xb8
	bl ov11_02254404
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r4, #0x66
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252BB0:
	mov r0, #4
	add r4, #0x66
	add sp, #0x110
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252BBA:
	add r3, r4, #0
	add r3, #0x65
	ldrb r3, [r3]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0xc
	add r2, sp, #0x68
	bl ov11_0225452C
	add r0, sp, #0x68
	mov r1, #5
	bl ov08_0222A494
	add r0, r4, #0
	add r0, #0x65
	ldrb r1, [r0]
	mov r0, #0x10
	add r2, sp, #0x10
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x10
	bl ov11_02254404
	mov r0, #0x1a
	ldr r1, [r4, #4]
	mov r2, #0
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r4, #0x66
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252C16:
	bl ov08_02212384
	add r0, r5, #0
	bl ov08_022123A0
	cmp r0, #0
	bne _02252C8A
	add r0, r5, #0
	bl ov08_022123B0
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r4, #0x66
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252C3A:
	add r0, r4, #0
	add r0, #0x67
	ldrb r0, [r0]
	cmp r0, #2
	bne _02252C48
	mov r5, #0x75
	b _02252C4C
_02252C48:
	mov r5, #0x74
	mvn r5, r5
_02252C4C:
	add r1, r4, #0
	add r1, #0x65
	ldrb r1, [r1]
	ldr r0, [r4]
	bl ov11_02230E88
	mov r1, #0x7f
	str r1, [sp]
	add r1, r4, #0
	add r1, #0x72
	ldrh r1, [r1]
	add r2, r4, #0
	add r2, #0x68
	str r1, [sp, #4]
	mov r1, #5
	str r1, [sp, #8]
	ldrh r2, [r2]
	add r3, r5, #0
	bl sub_02069FB0
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x66
	strb r1, [r0]
_02252C82:
	bl sub_02005670
	cmp r0, #0
	beq _02252C8C
_02252C8A:
	b _02252DAA
_02252C8C:
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r4, #0x66
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252C9C:
	add r0, r4, #0
	add r0, #0x67
	ldrb r0, [r0]
	cmp r0, #2
	ldr r0, _02252DB0 ; =0x00000703
	bne _02252CB0
	mov r1, #0x75
	bl sub_020054A8
	b _02252CB8
_02252CB0:
	mov r1, #0x74
	mvn r1, r1
	bl sub_020054A8
_02252CB8:
	ldr r0, [r4, #8]
	mov r1, #0x29
	bl sub_0200782C
	cmp r0, #0
	ble _02252CCE
	mov r0, #7
	add r4, #0x66
	add sp, #0x110
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252CCE:
	mov r0, #8
	add r4, #0x66
	add sp, #0x110
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252CD8:
	ldr r0, [r4, #8]
	mov r1, #0x29
	bl sub_0200782C
	add r5, r0, #0
	sub r5, #8
	bpl _02252CE8
	mov r5, #0
_02252CE8:
	ldr r0, [r4, #8]
	mov r1, #0x29
	add r2, r5, #0
	bl sub_02007558
	cmp r5, #0
	bne _02252DAA
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x66
	strb r1, [r0]
_02252D04:
	ldr r0, [r4, #0x6c]
	add r1, r4, #0
	str r0, [sp]
	add r0, r4, #0
	add r2, r4, #0
	add r3, r4, #0
	add r0, #0x68
	add r1, #0x6a
	add r2, #0x67
	add r3, #0x6b
	ldrh r0, [r0]
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldrb r3, [r3]
	bl sub_02068E88
	mov r3, #0x50
	sub r0, r3, r0
	str r0, [sp]
	mov r1, #0
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl sub_02007E40
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r4, #0x66
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252D44:
	ldr r0, [r4, #8]
	mov r1, #1
	bl sub_0200782C
	add r2, r0, #0
	ldr r0, [r4, #8]
	mov r1, #1
	add r2, #8
	bl sub_02007558
	ldr r0, [r4, #8]
	mov r1, #0x12
	bl sub_0200782C
	add r5, r0, #0
	sub r5, #8
	bpl _02252D68
	mov r5, #0
_02252D68:
	ldr r0, [r4, #8]
	mov r1, #0x12
	add r2, r5, #0
	bl sub_02007558
	cmp r5, #0
	bne _02252DAA
	ldr r0, [r4, #8]
	bl sub_02007534
	add r0, r4, #0
	add r0, #0x66
	ldrb r0, [r0]
	add r4, #0x66
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252D8C:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x65
	add r2, #0x64
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_02252DAA:
	add sp, #0x110
	pop {r4, r5, r6, pc}
	nop
_02252DB0: .word 0x00000703

	thumb_func_start ov11_02252DB4
ov11_02252DB4: ; 0x02252DB4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	bl ov11_022300CC
	add r4, r0, #0
	ldr r0, [r5]
	bl ov11_02230068
	add r7, r0, #0
	ldrb r0, [r5, #6]
	cmp r0, #0
	beq _02252DDE
	cmp r0, #1
	beq _02252E1C
	cmp r0, #2
	beq _02252E30
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02252DDE:
	ldr r0, [r5]
	bl ov11_02230288
	mov r1, #1
	bl sub_020143A8
	mov r1, #0
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r2, _02252E4C ; =0x0000FFFF
	add r0, r4, #0
	mov r1, #0xf
	mov r3, #1
	bl sub_02003210
	mov r1, #0
	add r0, r7, #0
	mov r2, #0x10
	add r3, r1, #0
	str r1, [sp]
	bl sub_02007E98
	mov r0, #0
	mov r1, #0x10
	bl sub_020053CC
	ldrb r0, [r5, #6]
	add r0, r0, #1
	strb r0, [r5, #6]
_02252E1C:
	add r0, r4, #0
	bl sub_020038E4
	cmp r0, #0
	bne _02252E46
	ldrb r0, [r5, #6]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r5, #6]
	pop {r4, r5, r6, r7, pc}
_02252E30:
	ldrb r1, [r5, #5]
	ldrb r2, [r5, #4]
	ldr r0, [r5]
	bl ov11_022567B8
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_02252E46:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02252E4C: .word 0x0000FFFF

	thumb_func_start ov11_02252E50
ov11_02252E50: ; 0x02252E50
	push {r4, r5, r6, lr}
	sub sp, #0x110
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02230070
	add r1, r4, #0
	add r1, #0x62
	ldrb r1, [r1]
	add r5, r0, #0
	cmp r1, #4
	bls _02252E6C
	b _02252F98
_02252E6C:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02252E78: ; jump table
	.short _02252E82 - _02252E78 - 2 ; case 0
	.short _02252EC4 - _02252E78 - 2 ; case 1
	.short _02252F74 - _02252E78 - 2 ; case 2
	.short _02252F18 - _02252E78 - 2 ; case 3
	.short _02252F74 - _02252E78 - 2 ; case 4
_02252E82:
	ldr r0, [r4, #4]
	ldr r0, [r0, #0x20]
	cmp r0, #0
	beq _02252EBA
	add r2, r4, #0
	add r2, #0x63
	ldrb r2, [r2]
	mov r1, #6
	bl sub_02007558
	add r0, r4, #0
	add r0, #0x63
	ldrb r0, [r0]
	cmp r0, #1
	bne _02252EAA
	mov r0, #0xff
	add r4, #0x62
	add sp, #0x110
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252EAA:
	add r0, r4, #0
	add r0, #0x62
	ldrb r0, [r0]
	add r4, #0x62
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252EBA:
	mov r0, #0xff
	add r4, #0x62
	add sp, #0x110
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252EC4:
	ldr r0, [r4, #0x64]
	cmp r0, #0
	beq _02252F0E
	mov r0, #0x1a
	ldr r1, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02252F0E
	add r0, r4, #0
	add r0, #0x61
	ldrb r1, [r0]
	mov r0, #0xf
	add r2, sp, #0xb8
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0xb8
	bl ov11_02254404
	add r0, r4, #0
	add r0, #0x62
	ldrb r0, [r0]
	add r4, #0x62
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252F0E:
	mov r0, #0xff
	add r4, #0x62
	add sp, #0x110
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252F18:
	add r3, r4, #0
	add r3, #0x61
	ldrb r3, [r3]
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #8
	add r2, sp, #0x68
	bl ov11_0225452C
	add r0, sp, #0x68
	mov r1, #5
	bl ov08_0222A568
	add r0, r4, #0
	add r0, #0x61
	ldrb r1, [r0]
	mov r0, #0x10
	add r2, sp, #0x10
	str r0, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r1, #0
	str r1, [sp, #0xc]
	ldr r0, [r4]
	mov r3, #1
	bl ov11_02256854
	ldr r0, [r4]
	ldr r1, [r4, #4]
	add r2, r5, #0
	add r3, sp, #0x10
	bl ov11_02254404
	mov r0, #0x1a
	ldr r1, [r4, #4]
	mov r2, #1
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	add r0, #0x62
	ldrb r0, [r0]
	add r4, #0x62
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252F74:
	bl ov08_02212384
	add r0, r5, #0
	bl ov08_022123A0
	cmp r0, #0
	bne _02252FB6
	add r0, r5, #0
	bl ov08_022123B0
	add r0, r4, #0
	add r0, #0x62
	ldrb r0, [r0]
	add r4, #0x62
	add sp, #0x110
	add r0, r0, #1
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02252F98:
	add r1, r4, #0
	add r2, r4, #0
	add r1, #0x61
	add r2, #0x60
	ldrb r1, [r1]
	ldrb r2, [r2]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_02252FB6:
	add sp, #0x110
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02252FBC
ov11_02252FBC: ; 0x02252FBC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xa]
	cmp r0, #0
	beq _02252FCE
	cmp r0, #1
	beq _02252FE4
	pop {r3, r4, r5, pc}
_02252FCE:
	ldr r0, [r4, #4]
	add r1, #0xb
	bl ov11_0225805C
	ldr r0, _02253004 ; =0x0000070C
	bl PlaySE
	ldrb r0, [r4, #0xa]
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, pc}
_02252FE4:
	ldrb r0, [r4, #0xb]
	cmp r0, #1
	bne _02253000
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_02253000:
	pop {r3, r4, r5, pc}
	nop
_02253004: .word 0x0000070C

	thumb_func_start ov11_02253008
ov11_02253008: ; 0x02253008
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_022312C0
	cmp r0, #0
	beq _0225302A
	ldr r0, [r4]
	bl ov11_022312C0
	bl sub_0200DBFC
	ldr r0, [r4]
	mov r1, #0
	bl ov11_022312C8
_0225302A:
	ldrb r0, [r4, #6]
	bl sub_0201BD70
	cmp r0, #0
	bne _0225304A
	ldrb r1, [r4, #5]
	ldrb r2, [r4, #4]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0225304A:
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_0225304C
ov11_0225304C: ; 0x0225304C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #7]
	cmp r0, #0
	beq _0225305E
	cmp r0, #1
	beq _02253074
	pop {r3, r4, r5, pc}
_0225305E:
	ldrb r0, [r4, #6]
	bl sub_0201BD70
	cmp r0, #0
	bne _0225309E
	ldrb r0, [r4, #7]
	add r0, r0, #1
	strb r0, [r4, #7]
	mov r0, #0
	strb r0, [r4, #8]
	pop {r3, r4, r5, pc}
_02253074:
	ldrb r0, [r4, #8]
	add r0, r0, #1
	strb r0, [r4, #8]
	ldrb r0, [r4, #8]
	cmp r0, #0x28
	bne _0225309E
	ldrb r1, [r4, #5]
	ldr r0, [r4]
	bl ov11_02256004
	ldrb r1, [r4, #5]
	ldrb r2, [r4, #4]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_0225309E:
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_022530A0
ov11_022530A0: ; 0x022530A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r4, r1, #0
	str r0, [sp, #0xc]
	ldr r0, [r4]
	bl ov11_0222FF68
	ldr r0, [r4]
	bl ov11_022300CC
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_02230294
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_022302A8
	lsl r1, r0, #2
	ldr r0, _022533D8 ; =ov11_0225E86C
	ldr r6, [r0, r1]
	ldrb r0, [r4, #0x15]
	add r0, r0, #1
	strb r0, [r4, #0x15]
	ldrb r0, [r4, #0x14]
	cmp r0, #6
	bhi _02253102
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022530E2: ; jump table
	.short _022530F0 - _022530E2 - 2 ; case 0
	.short _022530F8 - _022530E2 - 2 ; case 1
	.short _0225314A - _022530E2 - 2 ; case 2
	.short _022532AC - _022530E2 - 2 ; case 3
	.short _022532C8 - _022530E2 - 2 ; case 4
	.short _022532E4 - _022530E2 - 2 ; case 5
	.short _022532F6 - _022530E2 - 2 ; case 6
_022530F0:
	add r0, r0, #1
	add sp, #0x18
	strb r0, [r4, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
_022530F8:
	add r0, r5, #0
	bl sub_020038E4
	cmp r0, #0
	beq _02253104
_02253102:
	b _022533D4
_02253104:
	mov r0, #5
	mov r1, #0
	bl ov08_0222A0D4
	str r0, [r4, #4]
	ldr r0, _022533DC ; =ov11_0225E820
	add r1, sp, #0x10
	ldrb r5, [r0, r7]
	mov r0, #1
	str r0, [sp, #0x14]
	str r5, [sp, #0x10]
	ldr r0, [r4, #4]
	bl ov08_0222A110
	str r0, [r4, #8]
	add r0, r5, #1
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	ldr r0, [r4, #4]
	add r1, sp, #0x10
	bl ov08_0222A110
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	bl ov08_0222A1DC
	ldr r0, _022533E0 ; =0x0000084F
	bl PlaySE
	ldrb r0, [r4, #0x14]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
_0225314A:
	ldrb r0, [r4, #0x15]
	cmp r0, #0xa
	bne _02253180
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r2, _022533E4 ; =0x0000F3FF
	add r0, r5, #0
	mov r1, #1
	bl sub_02003210
	mov r3, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r2, _022533E8 ; =0x00003FFF
	add r0, r5, #0
	mov r1, #4
	bl sub_02003210
_02253180:
	ldrb r0, [r4, #0x15]
	cmp r0, #0x14
	bne _0225318C
	ldr r0, [r4, #0xc]
	bl ov08_0222A1DC
_0225318C:
	ldrb r0, [r4, #0x15]
	cmp r0, #0x17
	bne _0225319A
	mov r0, #0x85
	lsl r0, r0, #4
	bl PlaySE
_0225319A:
	ldrb r0, [r4, #0x15]
	cmp r0, #0x1c
	bne _02253286
	add r0, r5, #0
	mov r1, #0
	bl PaletteData_GetUnfadedBuf
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_02231244
	add r1, r7, #0
	mov r2, #0xe0
	bl MIi_CpuCopy16
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #0x4a
	bne _022531DC
	add r0, r5, #0
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r7, #0
	mov r2, #0xa0
	bl MIi_CpuCopy16
	b _0225323E
_022531DC:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02253200
	add r0, r5, #0
	bl PaletteData_GetUnfadedBuf
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r7, #0
	mov r2, #0xe0
	bl MIi_CpuCopy16
	b _0225323E
_02253200:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #1
	tst r0, r1
	beq _02253226
	add r0, r5, #0
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r7, #0
	mov r2, #0xa0
	bl MIi_CpuCopy16
	b _0225323E
_02253226:
	add r0, r5, #0
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	add r7, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r7, #0
	mov r2, #0x80
	bl MIi_CpuCopy16
_0225323E:
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	lsl r0, r6, #0x10
	str r3, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r2, _022533E4 ; =0x0000F3FF
	add r0, r5, #0
	mov r1, #1
	bl sub_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	lsl r0, r6, #0x10
	str r3, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r2, _022533E8 ; =0x00003FFF
	add r0, r5, #0
	mov r1, #4
	bl sub_02003210
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	lsl r0, r6, #0x10
	str r3, [sp, #4]
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	ldr r2, _022533EC ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #0xa
	bl sub_02003210
_02253286:
	ldrb r0, [r4, #0x15]
	cmp r0, #0x32
	bne _022532B6
	mov r0, #0x10
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	mov r2, #3
	str r3, [sp, #8]
	add r0, r5, #0
	mov r1, #1
	lsl r2, r2, #0xa
	bl sub_02003210
	ldrb r0, [r4, #0x14]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
_022532AC:
	ldr r0, [r4, #0xc]
	bl ov08_0222A204
	cmp r0, #0
	beq _022532B8
_022532B6:
	b _022533D4
_022532B8:
	ldr r0, [r4, #4]
	bl ov08_0222A14C
	ldrb r0, [r4, #0x14]
	add sp, #0x18
	add r0, r0, #1
	strb r0, [r4, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
_022532C8:
	ldr r0, [r4]
	bl ov11_02230288
	mov r1, #0
	bl sub_020143A8
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, [sp, #0xc]
	bl sub_0200CAB4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_022532E4:
	ldr r0, [r4, #4]
	bl ov08_0222A170
	ldr r0, [r4, #4]
	bl ov08_0222A14C
	ldrb r0, [r4, #0x14]
	add r0, r0, #1
	strb r0, [r4, #0x14]
_022532F6:
	add r0, r5, #0
	mov r1, #0
	bl PaletteData_GetUnfadedBuf
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02231244
	add r1, r6, #0
	mov r2, #0xe0
	bl MIi_CpuCopy16
	ldr r0, [r4]
	bl ov11_0222FF74
	cmp r0, #0x4a
	bne _02253332
	add r0, r5, #0
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r6, #0
	mov r2, #0xa0
	bl MIi_CpuCopy16
	b _02253394
_02253332:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	beq _02253356
	add r0, r5, #0
	bl PaletteData_GetUnfadedBuf
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r6, #0
	mov r2, #0xe0
	bl MIi_CpuCopy16
	b _02253394
_02253356:
	ldr r0, [r4]
	bl ov11_0222FF74
	mov r1, #1
	tst r0, r1
	beq _0225337C
	add r0, r5, #0
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r6, #0
	mov r2, #0xa0
	bl MIi_CpuCopy16
	b _02253394
_0225337C:
	add r0, r5, #0
	mov r1, #2
	bl PaletteData_GetUnfadedBuf
	add r6, r0, #0
	ldr r0, [r4]
	bl ov11_02231250
	add r1, r6, #0
	mov r2, #0x80
	bl MIi_CpuCopy16
_02253394:
	mov r3, #0
	str r3, [sp]
	ldr r0, _022533F0 ; =0x00007FFF
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r2, _022533EC ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #1
	bl sub_02003210
	mov r3, #0
	str r3, [sp]
	ldr r2, _022533EC ; =0x0000FFFF
	str r3, [sp, #4]
	str r2, [sp, #8]
	add r0, r5, #0
	mov r1, #4
	lsr r2, r2, #2
	bl sub_02003210
	mov r3, #0
	str r3, [sp]
	ldr r0, _022533F0 ; =0x00007FFF
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r2, _022533EC ; =0x0000FFFF
	add r0, r5, #0
	mov r1, #0xa
	bl sub_02003210
	mov r0, #4
	strb r0, [r4, #0x14]
_022533D4:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022533D8: .word ov11_0225E86C
_022533DC: .word ov11_0225E820
_022533E0: .word 0x0000084F
_022533E4: .word 0x0000F3FF
_022533E8: .word 0x00003FFF
_022533EC: .word 0x0000FFFF
_022533F0: .word 0x00007FFF

	thumb_func_start ov11_022533F4
ov11_022533F4: ; 0x022533F4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	bl ov11_022300CC
	ldrb r1, [r4, #0xa]
	add r6, r0, #0
	cmp r1, #3
	bls _0225340C
	b _02253524
_0225340C:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02253418: ; jump table
	.short _02253420 - _02253418 - 2 ; case 0
	.short _02253440 - _02253418 - 2 ; case 1
	.short _022534B0 - _02253418 - 2 ; case 2
	.short _022534E2 - _02253418 - 2 ; case 3
_02253420:
	mov r2, #0
	str r2, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	mov r1, #0xa
	str r2, [sp, #8]
	add r3, r1, #0
	ldr r2, _02253528 ; =0x0000FFFF
	sub r3, #0x12
	bl sub_02003210
	ldrb r0, [r4, #0xa]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, pc}
_02253440:
	bl sub_020038E4
	cmp r0, #0
	bne _02253524
	ldr r0, [r4]
	bl ov11_0222D7F8
	mov r0, #5
	mov r1, #0x38
	bl AllocFromHeap
	str r0, [r4, #4]
	ldrb r1, [r4, #9]
	ldr r0, [r4]
	bl ov11_0222FF88
	ldr r1, [r4, #4]
	mov r2, #3
	str r0, [r1]
	ldr r1, [r4]
	ldr r0, [r4, #4]
	str r1, [r0, #8]
	ldr r0, [r4, #4]
	mov r1, #5
	str r1, [r0, #0xc]
	ldrb r1, [r4, #0xe]
	ldr r0, [r4, #4]
	strb r1, [r0, #0x11]
	ldrh r1, [r4, #0xc]
	ldr r0, [r4, #4]
	strh r1, [r0, #0x24]
	ldr r1, [r4, #4]
	mov r0, #0
	add r1, #0x36
	strb r0, [r1]
	ldr r1, [r4, #4]
	strb r0, [r1, #0x12]
	ldr r1, [r4, #4]
	add r1, #0x35
	strb r2, [r1]
	ldr r1, [r4, #4]
	strh r0, [r1, #0x22]
	ldrb r2, [r4, #9]
	ldr r1, [r4, #4]
	str r2, [r1, #0x28]
	ldr r1, [r4, #4]
	add r1, #0x32
	strb r0, [r1]
	ldr r0, [r4, #4]
	bl ov07_02211E60
	ldrb r0, [r4, #0xa]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, pc}
_022534B0:
	ldr r0, [r4, #4]
	add r0, #0x36
	ldrb r0, [r0]
	cmp r0, #0
	beq _02253524
	ldr r0, [r4]
	bl ov11_0222D88C
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0
	mov r1, #0xa
	str r0, [sp, #4]
	add r3, r1, #0
	str r0, [sp, #8]
	ldr r2, _02253528 ; =0x0000FFFF
	add r0, r6, #0
	sub r3, #0x12
	bl sub_02003210
	ldrb r0, [r4, #0xa]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r4, #0xa]
	pop {r3, r4, r5, r6, pc}
_022534E2:
	bl sub_020038E4
	cmp r0, #0
	bne _02253524
	ldr r0, [r4, #4]
	add r0, #0x34
	ldrb r2, [r0]
	ldr r0, [r4]
	cmp r2, #4
	bne _02253500
	ldrb r1, [r4, #9]
	mov r2, #0xff
	bl ov11_02255964
	b _02253508
_02253500:
	ldrb r1, [r4, #9]
	add r2, r2, #1
	bl ov11_02255964
_02253508:
	ldrb r1, [r4, #9]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	bl ov11_022567B8
	ldr r0, [r4, #4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_02253524:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02253528: .word 0x0000FFFF

	thumb_func_start ov11_0225352C
ov11_0225352C: ; 0x0225352C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	ldrb r0, [r5, #0xa]
	cmp r0, #0
	beq _0225353E
	cmp r0, #1
	beq _02253582
	pop {r3, r4, r5, pc}
_0225353E:
	ldrb r1, [r5, #0xc]
	ldrb r0, [r5, #0xd]
	cmp r1, r0
	bne _0225357C
	mov r0, #0
	strb r0, [r5, #0xc]
	ldr r0, [r5, #4]
	mov r1, #0x28
	bl sub_0200782C
	add r4, r0, #0
	ldrb r0, [r5, #0xb]
	cmp r4, r0
	ble _0225355E
	sub r4, r4, #1
	b _02253564
_0225355E:
	cmp r4, r0
	bge _02253564
	add r4, r4, #1
_02253564:
	ldr r0, [r5, #4]
	mov r1, #0x28
	add r2, r4, #0
	bl sub_02007558
	ldrb r0, [r5, #0xb]
	cmp r4, r0
	bne _02253598
	ldrb r0, [r5, #0xa]
	add r0, r0, #1
	strb r0, [r5, #0xa]
	pop {r3, r4, r5, pc}
_0225357C:
	add r0, r1, #1
	strb r0, [r5, #0xc]
	pop {r3, r4, r5, pc}
_02253582:
	ldrb r1, [r5, #9]
	ldrb r2, [r5, #8]
	ldr r0, [r5]
	bl ov11_022567B8
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl sub_0200CAB4
_02253598:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0225359C
ov11_0225359C: ; 0x0225359C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	ldrb r1, [r5, #5]
	add r6, r0, #0
	ldr r0, [r5]
	bl ov11_02230270
	cmp r0, #0
	bne _022535B4
	mov r4, #0
	b _022535B6
_022535B4:
	mov r4, #1
_022535B6:
	ldrb r0, [r5, #7]
	cmp r0, #0
	beq _022535C2
	cmp r0, #1
	beq _0225361C
	b _02253636
_022535C2:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	bne _022535CE
	mov r7, #0
	mov r6, #1
	b _022535E6
_022535CE:
	ldrb r0, [r5, #6]
	mov r7, #1
	cmp r0, #3
	beq _022535DC
	cmp r0, #5
	beq _022535E0
	b _022535E4
_022535DC:
	mov r6, #0
	b _022535E6
_022535E0:
	mov r6, #2
	b _022535E6
_022535E4:
	add r6, r7, #0
_022535E6:
	ldr r0, [r5]
	bl ov11_02230078
	str r0, [sp, #8]
	ldr r0, [r5]
	bl ov11_02230080
	ldr r1, [sp, #8]
	add r2, r7, #0
	str r1, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #8
	add r1, r4, #0
	add r3, r6, #0
	bl ov11_0225CA08
	add r2, r0, #0
	ldr r0, [r5]
	add r1, r4, #0
	bl ov11_022300A8
	ldrb r0, [r5, #7]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r5, #7]
	pop {r4, r5, r6, r7, pc}
_0225361C:
	ldr r0, [r5]
	add r1, r4, #0
	bl ov11_0223009C
	bl ov11_0225CA6C
	cmp r0, #1
	bne _0225364C
	ldrb r0, [r5, #7]
	add sp, #0xc
	add r0, r0, #1
	strb r0, [r5, #7]
	pop {r4, r5, r6, r7, pc}
_02253636:
	ldrb r1, [r5, #5]
	ldrb r2, [r5, #4]
	ldr r0, [r5]
	bl ov11_022567B8
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_0225364C:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_02253650
ov11_02253650: ; 0x02253650
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldrb r1, [r5, #5]
	add r7, r0, #0
	ldr r0, [r5]
	bl ov11_02230270
	cmp r0, #0
	bne _02253666
	mov r4, #0
	b _02253668
_02253666:
	mov r4, #1
_02253668:
	ldr r0, [r5]
	add r1, r4, #0
	bl ov11_0223009C
	ldrb r1, [r5, #7]
	add r6, r0, #0
	cmp r1, #0
	beq _0225367E
	cmp r1, #1
	beq _0225369A
	b _022536BA
_0225367E:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	bne _02253688
	mov r1, #0
	b _0225368A
_02253688:
	mov r1, #1
_0225368A:
	add r0, r6, #0
	add r2, r1, #0
	bl ov11_0225CA90
	ldrb r0, [r5, #7]
	add r0, r0, #1
	strb r0, [r5, #7]
	pop {r3, r4, r5, r6, r7, pc}
_0225369A:
	bl ov11_0225CAC8
	cmp r0, #1
	bne _022536D0
	add r0, r6, #0
	bl ov11_0225CAEC
	ldr r0, [r5]
	add r1, r4, #0
	mov r2, #0
	bl ov11_022300A8
	ldrb r0, [r5, #7]
	add r0, r0, #1
	strb r0, [r5, #7]
	pop {r3, r4, r5, r6, r7, pc}
_022536BA:
	ldrb r1, [r5, #5]
	ldrb r2, [r5, #4]
	ldr r0, [r5]
	bl ov11_022567B8
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl sub_0200CAB4
_022536D0:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022536D4
ov11_022536D4: ; 0x022536D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _02253706
	ldr r0, [r4, #4]
	add r0, #0x8c
	ldr r0, [r0]
	cmp r0, #0
	beq _022536EE
	bl GF_AssertFail
_022536EE:
	ldrb r2, [r4, #0xd]
	ldr r0, [r4]
	mov r1, #5
	bl ov08_022156C0
	ldr r1, [r4, #4]
	add r1, #0x8c
	str r0, [r1]
	ldrb r0, [r4, #0xe]
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, pc}
_02253706:
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02253720
ov11_02253720: ; 0x02253720
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	add r0, #0x8c
	ldr r0, [r0]
	cmp r0, #0
	bne _02253734
	bl GF_AssertFail
_02253734:
	ldr r0, [r4, #4]
	add r0, #0x8c
	ldr r0, [r0]
	bl ov08_02215988
	cmp r0, #3
	bne _0225374E
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bhs _0225374E
	add r0, r0, #1
	strb r0, [r4, #0xe]
	pop {r3, r4, r5, pc}
_0225374E:
	ldr r0, [r4, #4]
	ldrb r1, [r4, #0xd]
	add r0, #0x8c
	ldr r0, [r0]
	bl ov08_0221594C
	ldr r0, [r4, #4]
	mov r1, #0
	add r0, #0x8c
	str r1, [r0]
	ldrb r1, [r4, #0xd]
	ldrb r2, [r4, #0xc]
	ldr r0, [r4]
	bl ov11_022567B8
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_0225377C
ov11_0225377C: ; 0x0225377C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov11_0222FF74
	mov r1, #0x40
	tst r1, r0
	beq _022537D6
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _022537B6
	ldr r1, _022539F4 ; =ov11_02250F44
	add r0, r0, #2
	str r1, [r4]
	ldr r1, _022539F8 ; =ov11_022511C4
	str r1, [r4, #4]
	ldr r1, _022539FC ; =ov11_02251420
	str r1, [r4, #8]
	ldr r1, _02253A00 ; =ov11_02252018
	str r1, [r4, #0xc]
	ldr r1, _02253A04 ; =ov11_02252470
	str r1, [r4, #0x10]
	ldr r1, _02253A08 ; =ov11_02252714
	str r1, [r4, #0x14]
	mov r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_022537B6:
	ldr r1, _02253A0C ; =ov11_02250A70
	add r0, r0, #2
	str r1, [r4]
	ldr r1, _02253A10 ; =ov11_0225103C
	str r1, [r4, #4]
	ldr r1, _02253A14 ; =ov11_022512B4
	str r1, [r4, #8]
	ldr r1, _02253A18 ; =ov11_02251484
	str r1, [r4, #0xc]
	ldr r1, _02253A1C ; =ov11_022520A8
	str r1, [r4, #0x10]
	ldr r1, _02253A20 ; =ov11_02252544
	str r1, [r4, #0x14]
	mov r1, #0
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_022537D6:
	mov r1, #0x88
	and r1, r0
	cmp r1, #0x88
	bne _02253888
	ldr r0, _02253A24 ; =0x00000195
	ldrb r1, [r4, r0]
	mov r0, #1
	tst r0, r1
	beq _02253832
	add r0, r5, #0
	bl ov11_02230DD4
	cmp r0, #0
	beq _02253812
	ldr r0, _022539F4 ; =ov11_02250F44
	mov r1, #1
	str r0, [r4]
	ldr r0, _022539F8 ; =ov11_022511C4
	str r0, [r4, #4]
	ldr r0, _022539FC ; =ov11_02251420
	str r0, [r4, #8]
	ldr r0, _02253A00 ; =ov11_02252018
	str r0, [r4, #0xc]
	ldr r0, _02253A04 ; =ov11_02252470
	str r0, [r4, #0x10]
	ldr r0, _02253A08 ; =ov11_02252714
	str r0, [r4, #0x14]
	ldr r0, _02253A28 ; =0x00000196
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02253812:
	ldr r0, _02253A2C ; =ov11_02250F74
	mov r1, #2
	str r0, [r4]
	ldr r0, _02253A30 ; =ov11_02251294
	str r0, [r4, #4]
	ldr r0, _02253A34 ; =ov11_02251464
	str r0, [r4, #8]
	ldr r0, _02253A38 ; =ov11_02252070
	str r0, [r4, #0xc]
	ldr r0, _02253A3C ; =ov11_02252524
	str r0, [r4, #0x10]
	ldr r0, _02253A40 ; =ov11_02252734
	str r0, [r4, #0x14]
	ldr r0, _02253A28 ; =0x00000196
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02253832:
	bl sub_02031190
	add r1, r0, #0
	add r0, r5, #0
	lsl r1, r1, #1
	bl ov11_02230260
	ldr r1, _02253A24 ; =0x00000195
	ldrb r2, [r4, r1]
	cmp r2, r0
	beq _02253868
	ldr r0, _02253A2C ; =ov11_02250F74
	mov r2, #2
	str r0, [r4]
	ldr r0, _02253A30 ; =ov11_02251294
	str r0, [r4, #4]
	ldr r0, _02253A34 ; =ov11_02251464
	str r0, [r4, #8]
	ldr r0, _02253A38 ; =ov11_02252070
	str r0, [r4, #0xc]
	ldr r0, _02253A3C ; =ov11_02252524
	str r0, [r4, #0x10]
	ldr r0, _02253A40 ; =ov11_02252734
	str r0, [r4, #0x14]
	add r0, r1, #1
	strb r2, [r4, r0]
	pop {r3, r4, r5, pc}
_02253868:
	ldr r0, _02253A0C ; =ov11_02250A70
	mov r2, #0
	str r0, [r4]
	ldr r0, _02253A10 ; =ov11_0225103C
	str r0, [r4, #4]
	ldr r0, _02253A14 ; =ov11_022512B4
	str r0, [r4, #8]
	ldr r0, _02253A18 ; =ov11_02251484
	str r0, [r4, #0xc]
	ldr r0, _02253A1C ; =ov11_022520A8
	str r0, [r4, #0x10]
	ldr r0, _02253A20 ; =ov11_02252544
	str r0, [r4, #0x14]
	add r0, r1, #1
	strb r2, [r4, r0]
	pop {r3, r4, r5, pc}
_02253888:
	mov r1, #8
	tst r1, r0
	beq _022538E2
	bl sub_02031190
	add r1, r0, #0
	add r0, r5, #0
	bl ov11_02230260
	ldr r1, _02253A24 ; =0x00000195
	ldrb r2, [r4, r1]
	cmp r2, r0
	beq _022538C2
	ldr r0, _02253A2C ; =ov11_02250F74
	mov r2, #2
	str r0, [r4]
	ldr r0, _02253A30 ; =ov11_02251294
	str r0, [r4, #4]
	ldr r0, _02253A34 ; =ov11_02251464
	str r0, [r4, #8]
	ldr r0, _02253A38 ; =ov11_02252070
	str r0, [r4, #0xc]
	ldr r0, _02253A3C ; =ov11_02252524
	str r0, [r4, #0x10]
	ldr r0, _02253A40 ; =ov11_02252734
	str r0, [r4, #0x14]
	add r0, r1, #1
	strb r2, [r4, r0]
	pop {r3, r4, r5, pc}
_022538C2:
	ldr r0, _02253A0C ; =ov11_02250A70
	mov r2, #0
	str r0, [r4]
	ldr r0, _02253A10 ; =ov11_0225103C
	str r0, [r4, #4]
	ldr r0, _02253A14 ; =ov11_022512B4
	str r0, [r4, #8]
	ldr r0, _02253A18 ; =ov11_02251484
	str r0, [r4, #0xc]
	ldr r0, _02253A1C ; =ov11_022520A8
	str r0, [r4, #0x10]
	ldr r0, _02253A20 ; =ov11_02252544
	str r0, [r4, #0x14]
	add r0, r1, #1
	strb r2, [r4, r0]
	pop {r3, r4, r5, pc}
_022538E2:
	mov r1, #4
	add r2, r0, #0
	tst r2, r1
	beq _02253934
	ldr r0, _02253A24 ; =0x00000195
	mov r1, #1
	ldrb r2, [r4, r0]
	tst r1, r2
	beq _02253914
	ldr r1, _02253A2C ; =ov11_02250F74
	add r0, r0, #1
	str r1, [r4]
	ldr r1, _02253A30 ; =ov11_02251294
	str r1, [r4, #4]
	ldr r1, _02253A34 ; =ov11_02251464
	str r1, [r4, #8]
	ldr r1, _02253A38 ; =ov11_02252070
	str r1, [r4, #0xc]
	ldr r1, _02253A3C ; =ov11_02252524
	str r1, [r4, #0x10]
	ldr r1, _02253A40 ; =ov11_02252734
	str r1, [r4, #0x14]
	mov r1, #2
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02253914:
	ldr r1, _02253A0C ; =ov11_02250A70
	add r0, r0, #1
	str r1, [r4]
	ldr r1, _02253A10 ; =ov11_0225103C
	str r1, [r4, #4]
	ldr r1, _02253A14 ; =ov11_022512B4
	str r1, [r4, #8]
	ldr r1, _02253A18 ; =ov11_02251484
	str r1, [r4, #0xc]
	ldr r1, _02253A1C ; =ov11_022520A8
	str r1, [r4, #0x10]
	ldr r1, _02253A20 ; =ov11_02252544
	str r1, [r4, #0x14]
	mov r1, #0
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02253934:
	lsl r1, r1, #7
	tst r1, r0
	beq _02253970
	ldr r0, _02253A24 ; =0x00000195
	mov r1, #1
	ldrb r2, [r4, r0]
	tst r2, r1
	beq _0225395A
	ldr r2, _02253A44 ; =ov11_02251014
	add r0, r0, #1
	str r2, [r4]
	mov r2, #0
	str r2, [r4, #4]
	str r2, [r4, #8]
	str r2, [r4, #0xc]
	str r2, [r4, #0x10]
	str r2, [r4, #0x14]
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_0225395A:
	ldr r1, _02253A0C ; =ov11_02250A70
	add r0, r0, #1
	str r1, [r4]
	mov r1, #0
	str r1, [r4, #4]
	str r1, [r4, #8]
	str r1, [r4, #0xc]
	str r1, [r4, #0x10]
	str r1, [r4, #0x14]
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02253970:
	mov r1, #0x20
	tst r0, r1
	ldr r0, _02253A24 ; =0x00000195
	beq _022539AE
	ldrb r2, [r4, r0]
	mov r1, #1
	tst r2, r1
	beq _02253996
	ldr r2, _02253A48 ; =ov11_02250F94
	add r0, r0, #1
	str r2, [r4]
	mov r2, #0
	str r2, [r4, #4]
	str r2, [r4, #8]
	str r2, [r4, #0xc]
	str r2, [r4, #0x10]
	str r2, [r4, #0x14]
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02253996:
	ldr r1, _02253A0C ; =ov11_02250A70
	mov r2, #0
	str r1, [r4]
	str r2, [r4, #4]
	str r2, [r4, #8]
	str r2, [r4, #0xc]
	ldr r1, _02253A20 ; =ov11_02252544
	str r2, [r4, #0x10]
	str r1, [r4, #0x14]
	add r0, r0, #1
	strb r2, [r4, r0]
	pop {r3, r4, r5, pc}
_022539AE:
	ldrb r2, [r4, r0]
	mov r1, #1
	tst r2, r1
	beq _022539D4
	ldr r2, _022539F4 ; =ov11_02250F44
	add r0, r0, #1
	str r2, [r4]
	ldr r2, _022539F8 ; =ov11_022511C4
	str r2, [r4, #4]
	ldr r2, _022539FC ; =ov11_02251420
	str r2, [r4, #8]
	ldr r2, _02253A00 ; =ov11_02252018
	str r2, [r4, #0xc]
	ldr r2, _02253A04 ; =ov11_02252470
	str r2, [r4, #0x10]
	ldr r2, _02253A08 ; =ov11_02252714
	str r2, [r4, #0x14]
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_022539D4:
	ldr r1, _02253A0C ; =ov11_02250A70
	add r0, r0, #1
	str r1, [r4]
	ldr r1, _02253A10 ; =ov11_0225103C
	str r1, [r4, #4]
	ldr r1, _02253A14 ; =ov11_022512B4
	str r1, [r4, #8]
	ldr r1, _02253A18 ; =ov11_02251484
	str r1, [r4, #0xc]
	ldr r1, _02253A1C ; =ov11_022520A8
	str r1, [r4, #0x10]
	ldr r1, _02253A20 ; =ov11_02252544
	str r1, [r4, #0x14]
	mov r1, #0
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_022539F4: .word ov11_02250F44
_022539F8: .word ov11_022511C4
_022539FC: .word ov11_02251420
_02253A00: .word ov11_02252018
_02253A04: .word ov11_02252470
_02253A08: .word ov11_02252714
_02253A0C: .word ov11_02250A70
_02253A10: .word ov11_0225103C
_02253A14: .word ov11_022512B4
_02253A18: .word ov11_02251484
_02253A1C: .word ov11_022520A8
_02253A20: .word ov11_02252544
_02253A24: .word 0x00000195
_02253A28: .word 0x00000196
_02253A2C: .word ov11_02250F74
_02253A30: .word ov11_02251294
_02253A34: .word ov11_02251464
_02253A38: .word ov11_02252070
_02253A3C: .word ov11_02252524
_02253A40: .word ov11_02252734
_02253A44: .word ov11_02251014
_02253A48: .word ov11_02250F94

	thumb_func_start ov11_02253A4C
ov11_02253A4C: ; 0x02253A4C
	ldr r1, _02253A54 ; =0x00000195
	ldrb r0, [r0, r1]
	bx lr
	nop
_02253A54: .word 0x00000195

	thumb_func_start ov11_02253A58
ov11_02253A58: ; 0x02253A58
	ldr r1, _02253A60 ; =0x00000196
	ldrb r0, [r0, r1]
	bx lr
	nop
_02253A60: .word 0x00000196

	thumb_func_start ov11_02253A64
ov11_02253A64: ; 0x02253A64
	ldr r1, [r0, #0x20]
	cmp r1, #0
	bne _02253A6C
	ldr r1, [r0, #0x1c]
_02253A6C:
	add r0, r1, #0
	bx lr

	thumb_func_start ov11_02253A70
ov11_02253A70: ; 0x02253A70
	add r0, #0x28
	bx lr

	thumb_func_start ov11_02253A74
ov11_02253A74: ; 0x02253A74
	add r0, #0x80
	bx lr

	thumb_func_start ov11_02253A78
ov11_02253A78: ; 0x02253A78
	ldr r3, _02253A84 ; =MI_CpuFill8
	add r0, #0x80
	mov r1, #0
	mov r2, #8
	bx r3
	nop
_02253A84: .word MI_CpuFill8

	thumb_func_start ov11_02253A88
ov11_02253A88: ; 0x02253A88
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	ldr r4, [sp, #0x50]
	add r7, r0, #0
	str r1, [sp, #0x14]
	add r5, r2, #0
	str r3, [sp, #0x18]
	bl ov11_02230130
	add r1, r4, #0
	bl ov11_022312DC
	str r0, [sp, #0x20]
	add r0, r7, #0
	add r1, r4, #0
	bl ov11_02230260
	add r6, r0, #0
	mov r0, #1
	and r0, r6
	str r0, [sp, #0x1c]
	beq _02253AB8
	mov r1, #2
	b _02253ABA
_02253AB8:
	mov r1, #0
_02253ABA:
	ldr r0, [r5, #0xc]
	ldr r3, [sp, #0x20]
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldrh r0, [r5, #6]
	mov r2, #5
	str r0, [sp, #0xc]
	ldrh r0, [r5]
	ldrh r1, [r5, #2]
	bl sub_02012560
	add r0, r7, #0
	bl ov11_02230130
	ldrh r2, [r5]
	add r1, r4, #0
	bl ov11_022312F0
	add r0, r7, #0
	bl ov11_02230130
	ldrh r2, [r5, #4]
	add r1, r4, #0
	bl ov11_02231308
	add r0, r7, #0
	bl ov11_02230130
	ldr r2, [sp, #0x40]
	add r1, r4, #0
	bl ov11_02231320
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x40]
	str r0, [sp]
	str r4, [sp, #4]
	str r4, [sp, #8]
	ldr r0, [sp, #0x54]
	ldr r4, [sp, #0x38]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x58]
	ldr r2, [sp, #0x18]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	add r1, r5, #0
	add r3, r4, r3
	bl sub_020073E8
	add r4, r0, #0
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _02253B6E
	cmp r6, #1
	ble _02253B2C
	asr r6, r6, #1
_02253B2C:
	add r0, r4, #0
	mov r1, #0x2a
	add r2, r6, #0
	bl sub_02007558
	ldr r2, [sp, #0x4c]
	add r0, r4, #0
	mov r1, #0x2e
	bl sub_02007558
	ldr r2, [sp, #0x38]
	add r0, r4, #0
	mov r1, #0x14
	add r2, #0x24
	bl sub_02007558
	ldr r2, [sp, #0x48]
	add r0, r4, #0
	mov r1, #0x15
	bl sub_02007558
	ldr r3, [sp, #0x40]
	mov r2, #0x24
	add r0, r4, #0
	mov r1, #0x16
	sub r2, r2, r3
	bl sub_02007558
	ldr r2, [sp, #0x44]
	add r0, r4, #0
	mov r1, #0x29
	bl sub_02007558
_02253B6E:
	add r0, r4, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_02253B74
ov11_02253B74: ; 0x02253B74
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, _02253C30 ; =0x00000195
	add r6, r2, #0
	ldrb r2, [r5, r1]
	mov r1, #1
	add r7, r0, #0
	add r4, r3, #0
	tst r1, r2
	beq _02253BCE
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	beq _02253BAE
	ldr r0, _02253C34 ; =0x000003DE
	strh r0, [r4, #2]
	mov r0, #0x1b
	strb r0, [r4, #1]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	str r1, [r4, #4]
	ldrb r1, [r5, r0]
	ldrb r0, [r6, #1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02253BAE:
	ldr r0, _02253C38 ; =0x000003DD
	strh r0, [r4, #2]
	mov r0, #0x32
	strb r0, [r4, #1]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	str r1, [r4, #4]
	ldrb r1, [r5, r0]
	str r1, [r4, #8]
	ldrb r1, [r5, r0]
	ldrb r0, [r6, #1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02253BCE:
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02253C18
	add r0, r7, #0
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	bne _02253C18
	ldrh r0, [r6, #2]
	cmp r0, #0
	bne _02253BF2
	mov r0, #0xf6
	lsl r0, r0, #2
	strh r0, [r4, #2]
	b _02253C1C
_02253BF2:
	cmp r0, #0x19
	bhs _02253BFC
	ldr r0, _02253C3C ; =0x000003D9
	strh r0, [r4, #2]
	b _02253C1C
_02253BFC:
	cmp r0, #0x32
	bhs _02253C08
	mov r0, #0xf7
	lsl r0, r0, #2
	strh r0, [r4, #2]
	b _02253C1C
_02253C08:
	cmp r0, #0x4b
	bhs _02253C12
	ldr r0, _02253C40 ; =0x000003DA
	strh r0, [r4, #2]
	b _02253C1C
_02253C12:
	ldr r0, _02253C44 ; =0x000003DB
	strh r0, [r4, #2]
	b _02253C1C
_02253C18:
	ldr r0, _02253C3C ; =0x000003D9
	strh r0, [r4, #2]
_02253C1C:
	mov r0, #2
	strb r0, [r4, #1]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	ldrb r0, [r6, #1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02253C30: .word 0x00000195
_02253C34: .word 0x000003DE
_02253C38: .word 0x000003DD
_02253C3C: .word 0x000003D9
_02253C40: .word 0x000003DA
_02253C44: .word 0x000003DB

	thumb_func_start ov11_02253C48
ov11_02253C48: ; 0x02253C48
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	ldr r1, _02253D08 ; =0x00000195
	add r6, r2, #0
	ldrb r2, [r5, r1]
	mov r1, #1
	add r7, r0, #0
	add r4, r3, #0
	tst r1, r2
	beq _02253CA4
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	bne _02253C88
	mov r0, #0xf3
	lsl r0, r0, #2
	strh r0, [r4, #2]
	mov r0, #0x32
	strb r0, [r4, #1]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	str r1, [r4, #4]
	ldrb r1, [r5, r0]
	str r1, [r4, #8]
	ldrb r1, [r5, r0]
	ldrb r0, [r6, #1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02253C88:
	ldr r0, _02253D0C ; =0x000003CE
	strh r0, [r4, #2]
	mov r0, #0x1b
	strb r0, [r4, #1]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	str r1, [r4, #4]
	ldrb r1, [r5, r0]
	ldrb r0, [r6, #1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02253CA4:
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _02253CF0
	add r0, r7, #0
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	bne _02253CF0
	ldrh r1, [r6, #2]
	cmp r1, #0x64
	bhs _02253CC6
	ldr r0, _02253D10 ; =0x000003D6
	strh r0, [r4, #2]
	b _02253CF4
_02253CC6:
	ldr r0, _02253D14 ; =0x00000145
	cmp r1, r0
	bhs _02253CD2
	ldr r0, _02253D18 ; =0x000003D7
	strh r0, [r4, #2]
	b _02253CF4
_02253CD2:
	add r0, #0xe1
	cmp r1, r0
	bhs _02253CDE
	ldr r0, _02253D1C ; =0x000003D5
	strh r0, [r4, #2]
	b _02253CF4
_02253CDE:
	ldr r0, _02253D20 ; =0x00000307
	cmp r1, r0
	bhs _02253CEA
	add r0, #0xcd
	strh r0, [r4, #2]
	b _02253CF4
_02253CEA:
	add r0, #0xcc
	strh r0, [r4, #2]
	b _02253CF4
_02253CF0:
	ldr r0, _02253D24 ; =0x000003D3
	strh r0, [r4, #2]
_02253CF4:
	mov r0, #2
	strb r0, [r4, #1]
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	ldrb r0, [r6, #1]
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02253D08: .word 0x00000195
_02253D0C: .word 0x000003CE
_02253D10: .word 0x000003D6
_02253D14: .word 0x00000145
_02253D18: .word 0x000003D7
_02253D1C: .word 0x000003D5
_02253D20: .word 0x00000307
_02253D24: .word 0x000003D3

	thumb_func_start ov11_02253D28
ov11_02253D28: ; 0x02253D28
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r2, #0
	bl ov11_0222FF74
	add r4, r0, #0
	mov r0, #2
	tst r0, r4
	beq _02253D4E
	add r0, r7, #0
	mov r1, #3
	bl ov11_0223022C
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #5
	bl ov11_0223022C
	b _02253D58
_02253D4E:
	add r0, r7, #0
	mov r1, #1
	bl ov11_0223022C
	add r6, r0, #0
_02253D58:
	mov r1, #4
	tst r1, r4
	beq _02253D98
	mov r1, #0x80
	tst r1, r4
	beq _02253D78
	mov r1, #0x3e
	lsl r1, r1, #4
	strh r1, [r5, #2]
	mov r1, #0x3b
	strb r1, [r5, #1]
	str r6, [r5, #4]
	str r6, [r5, #8]
	str r0, [r5, #0xc]
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_02253D78:
	mov r1, #8
	add r2, r4, #0
	tst r2, r1
	beq _02253D8E
	ldr r1, _02253DC8 ; =0x000003CB
	strh r1, [r5, #2]
	mov r1, #0x1a
	strb r1, [r5, #1]
	str r6, [r5, #4]
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02253D8E:
	ldr r0, _02253DCC ; =0x000003CA
	strh r0, [r5, #2]
	strb r1, [r5, #1]
	str r6, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02253D98:
	mov r1, #0x10
	tst r1, r4
	bne _02253DA4
	mov r1, #8
	tst r1, r4
	beq _02253DB8
_02253DA4:
	mov r1, #0x3e
	lsl r1, r1, #4
	strh r1, [r5, #2]
	mov r1, #0x3b
	strb r1, [r5, #1]
	str r6, [r5, #4]
	str r6, [r5, #8]
	str r0, [r5, #0xc]
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_02253DB8:
	ldr r0, _02253DD0 ; =0x000003C9
	strh r0, [r5, #2]
	mov r0, #0x1e
	strb r0, [r5, #1]
	str r6, [r5, #4]
	str r6, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02253DC8: .word 0x000003CB
_02253DCC: .word 0x000003CA
_02253DD0: .word 0x000003C9

	thumb_func_start ov11_02253DD4
ov11_02253DD4: ; 0x02253DD4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #4]
	str r0, [sp]
	add r6, r2, #0
	add r4, r3, #0
	bl ov11_0222FF74
	str r0, [sp, #0x14]
	ldr r2, _022540E4 ; =0x00000195
	ldr r0, [sp, #4]
	ldrb r1, [r0, r2]
	mov r0, #1
	tst r0, r1
	bne _02253DF4
	b _02253F3C
_02253DF4:
	ldr r0, [sp, #0x14]
	mov r1, #2
	and r0, r1
	str r0, [sp, #0x10]
	beq _02253E10
	ldr r0, [sp, #4]
	sub r1, r2, #1
	ldrb r5, [r0, r1]
	ldr r0, [sp]
	add r1, r5, #0
	bl ov11_022302BC
	add r7, r0, #0
	b _02253E18
_02253E10:
	ldr r0, [sp, #4]
	sub r1, r2, #1
	ldrb r5, [r0, r1]
	add r7, r5, #0
_02253E18:
	ldr r0, [sp, #0x14]
	mov r1, #4
	tst r0, r1
	beq _02253EBE
	ldr r0, [sp, #0x14]
	mov r1, #0x80
	tst r0, r1
	beq _02253E50
	ldr r0, _022540E8 ; =0x000003DF
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x3c
	strb r0, [r4, #1]
	str r5, [r4, #4]
	str r5, [r4, #8]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #0xc]
	str r7, [r4, #0x10]
	str r7, [r4, #0x14]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_02253E50:
	ldr r0, [sp, #0x14]
	mov r1, #8
	tst r0, r1
	beq _02253E7E
	mov r0, #0x3d
	lsl r0, r0, #4
	strh r0, [r4, #2]
	mov r0, #0x38
	strb r0, [r4, #1]
	str r5, [r4, #4]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	add sp, #0x18
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #8]
	str r7, [r4, #0xc]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_02253E7E:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _02253EA6
	ldr r0, _022540EC ; =0x000003CF
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x31
	strb r0, [r4, #1]
	str r5, [r4, #4]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #8]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02253EA6:
	ldr r0, _022540F0 ; =0x000003CE
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x1b
	strb r0, [r4, #1]
	str r5, [r4, #4]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02253EBE:
	ldr r0, [sp, #0x14]
	mov r1, #0x10
	tst r0, r1
	bne _02253ECE
	ldr r0, [sp, #0x14]
	mov r1, #8
	tst r0, r1
	beq _02253EF6
_02253ECE:
	ldr r0, _022540E8 ; =0x000003DF
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x3c
	strb r0, [r4, #1]
	str r5, [r4, #4]
	str r5, [r4, #8]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #0xc]
	str r7, [r4, #0x10]
	str r7, [r4, #0x14]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
_02253EF6:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _02253F20
	ldr r0, _022540F4 ; =0x000003CD
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x39
	strb r0, [r4, #1]
	str r5, [r4, #4]
	str r5, [r4, #8]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #0xc]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_02253F20:
	mov r0, #0xf3
	lsl r0, r0, #2
	strh r0, [r4, #2]
	mov r0, #0x32
	strb r0, [r4, #1]
	str r5, [r4, #4]
	str r5, [r4, #8]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	add sp, #0x18
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02253F3C:
	ldr r0, [sp, #0x14]
	mov r1, #4
	and r0, r1
	str r0, [sp, #0xc]
	beq _02253FCC
	bl sub_02031190
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	ldr r0, [sp, #0x14]
	mov r1, #8
	and r0, r1
	str r0, [sp, #8]
	beq _02253FA2
	add r0, r2, #0
	bl sub_020313CC
	cmp r0, #3
	bhi _02254012
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02253F6E: ; jump table
	.short _02253F76 - _02253F6E - 2 ; case 0
	.short _02253F8C - _02253F6E - 2 ; case 1
	.short _02253F8C - _02253F6E - 2 ; case 2
	.short _02253F76 - _02253F6E - 2 ; case 3
_02253F76:
	ldr r0, [sp]
	mov r1, #4
	bl ov11_0223022C
	add r5, r0, #0
	ldr r0, [sp]
	mov r1, #2
	bl ov11_0223022C
	add r7, r0, #0
	b _02254012
_02253F8C:
	ldr r0, [sp]
	mov r1, #2
	bl ov11_0223022C
	add r5, r0, #0
	ldr r0, [sp]
	mov r1, #4
	bl ov11_0223022C
	add r7, r0, #0
	b _02254012
_02253FA2:
	ldr r0, [sp, #0x14]
	mov r1, #2
	tst r0, r1
	beq _02253FBE
	ldr r0, [sp]
	bl ov11_0223022C
	add r5, r0, #0
	ldr r0, [sp]
	mov r1, #4
	bl ov11_0223022C
	add r7, r0, #0
	b _02254012
_02253FBE:
	ldr r0, [sp]
	mov r1, #0
	bl ov11_0223022C
	add r5, r0, #0
	add r7, r5, #0
	b _02254012
_02253FCC:
	ldr r0, [sp, #0x14]
	mov r1, #8
	and r0, r1
	str r0, [sp, #8]
	beq _02253FEE
	ldr r1, [sp, #4]
	sub r2, r2, #1
	ldrb r1, [r1, r2]
	ldr r0, [sp]
	bl ov11_022302BC
	add r5, r0, #0
	mov r1, #0x65
	ldr r0, [sp, #4]
	lsl r1, r1, #2
	ldrb r7, [r0, r1]
	b _02254012
_02253FEE:
	ldr r0, [sp, #0x14]
	mov r1, #2
	tst r0, r1
	beq _0225400A
	ldr r0, [sp]
	bl ov11_0223022C
	add r5, r0, #0
	ldr r0, [sp]
	mov r1, #4
	bl ov11_0223022C
	add r7, r0, #0
	b _02254012
_0225400A:
	ldr r0, [sp, #4]
	sub r1, r2, #1
	ldrb r5, [r0, r1]
	add r7, r5, #0
_02254012:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _0225407C
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _02254040
	ldr r0, _022540F8 ; =0x000003D1
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x31
	strb r0, [r4, #1]
	str r5, [r4, #4]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #8]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_02254040:
	ldr r0, [sp, #0x14]
	mov r1, #2
	tst r0, r1
	beq _02254068
	ldr r0, _022540FC ; =0x000003D2
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #9
	strb r0, [r4, #1]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #4]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02254068:
	ldr r0, _02254100 ; =0x000003D3
	add sp, #0x18
	strh r0, [r4, #2]
	strb r1, [r4, #1]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0225407C:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _022540A6
	ldr r0, _02254104 ; =0x000003E1
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #0x39
	strb r0, [r4, #1]
	str r5, [r4, #4]
	str r5, [r4, #8]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #0xc]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
_022540A6:
	ldr r0, [sp, #0x14]
	mov r1, #2
	tst r0, r1
	beq _022540CE
	ldr r0, _022540FC ; =0x000003D2
	add sp, #0x18
	strh r0, [r4, #2]
	mov r0, #9
	strb r0, [r4, #1]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #4]
	add r0, r6, r7
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r7
	str r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
_022540CE:
	ldr r0, _02254100 ; =0x000003D3
	strh r0, [r4, #2]
	strb r1, [r4, #1]
	add r0, r6, r5
	ldrb r0, [r0, #4]
	lsl r0, r0, #8
	orr r0, r5
	str r0, [r4, #4]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022540E4: .word 0x00000195
_022540E8: .word 0x000003DF
_022540EC: .word 0x000003CF
_022540F0: .word 0x000003CE
_022540F4: .word 0x000003CD
_022540F8: .word 0x000003D1
_022540FC: .word 0x000003D2
_02254100: .word 0x000003D3
_02254104: .word 0x000003E1

	thumb_func_start ov11_02254108
ov11_02254108: ; 0x02254108
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r5, r2, #0
	bl ov11_0222FF74
	add r6, r0, #0
	ldr r0, [sp]
	bl ov11_0223145C
	add r7, r0, #0
	mov r0, #2
	tst r0, r6
	beq _02254136
	ldr r0, [sp]
	mov r1, #3
	bl ov11_0223022C
	add r4, r0, #0
	ldr r0, [sp]
	mov r1, #5
	bl ov11_0223022C
	b _02254140
_02254136:
	ldr r0, [sp]
	mov r1, #1
	bl ov11_0223022C
	add r4, r0, #0
_02254140:
	cmp r7, #1
	beq _0225414E
	cmp r7, #2
	beq _0225416E
	cmp r7, #3
	beq _02254190
	pop {r3, r4, r5, r6, r7, pc}
_0225414E:
	mov r1, #8
	add r2, r6, #0
	tst r2, r1
	beq _02254164
	ldr r1, _022541B0 ; =0x00000312
	strh r1, [r5, #2]
	mov r1, #0x1a
	strb r1, [r5, #1]
	str r4, [r5, #4]
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02254164:
	ldr r0, _022541B4 ; =0x00000311
	strh r0, [r5, #2]
	strb r1, [r5, #1]
	str r4, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0225416E:
	mov r1, #8
	add r2, r6, #0
	tst r2, r1
	beq _02254186
	mov r1, #0xc5
	lsl r1, r1, #2
	strh r1, [r5, #2]
	mov r1, #0x1a
	strb r1, [r5, #1]
	str r4, [r5, #4]
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_02254186:
	ldr r0, _022541B8 ; =0x00000313
	strh r0, [r5, #2]
	strb r1, [r5, #1]
	str r4, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02254190:
	mov r1, #8
	add r2, r6, #0
	tst r2, r1
	beq _022541A6
	ldr r1, _022541BC ; =0x00000316
	strh r1, [r5, #2]
	mov r1, #0x1a
	strb r1, [r5, #1]
	str r4, [r5, #4]
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_022541A6:
	ldr r0, _022541C0 ; =0x00000315
	strh r0, [r5, #2]
	strb r1, [r5, #1]
	str r4, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022541B0: .word 0x00000312
_022541B4: .word 0x00000311
_022541B8: .word 0x00000313
_022541BC: .word 0x00000316
_022541C0: .word 0x00000315

	thumb_func_start ov11_022541C4
ov11_022541C4: ; 0x022541C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r6, #0
	add r5, r0, #0
	str r2, [sp]
	add r7, r3, #0
	str r6, [sp, #4]
	add r4, r6, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _0225420C
_022541DC:
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, [sp]
	ldrb r1, [r1, #1]
	tst r0, r1
	beq _02254200
	add r0, r5, #0
	add r1, r4, #0
	bl ov11_02230270
	cmp r0, #0
	beq _022541FE
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	b _02254200
_022541FE:
	add r6, r6, #1
_02254200:
	add r0, r5, #0
	add r4, r4, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _022541DC
_0225420C:
	cmp r6, #0
	beq _0225422A
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _0225422A
	ldr r0, _022542AC ; =0x0000030D
	mov r1, #0xc3
	strh r0, [r7, #2]
	mov r0, #0
	strb r0, [r7, #1]
	add r0, r5, #0
	bl ov11_02231468
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0225422A:
	cmp r6, #0
	beq _02254242
	ldr r0, _022542AC ; =0x0000030D
	mov r1, #0xc2
	strh r0, [r7, #2]
	mov r0, #0
	strb r0, [r7, #1]
	add r0, r5, #0
	bl ov11_02231468
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02254242:
	add r0, r5, #0
	bl ov11_0222FF74
	mov r1, #8
	tst r0, r1
	beq _0225426E
	mov r0, #0xc6
	lsl r0, r0, #2
	strh r0, [r7, #2]
	mov r0, #0x1a
	strb r0, [r7, #1]
	add r0, r5, #0
	mov r1, #3
	bl ov11_0223022C
	str r0, [r7, #4]
	add r0, r5, #0
	mov r1, #5
	bl ov11_0223022C
	str r0, [r7, #8]
	b _0225429E
_0225426E:
	add r0, r5, #0
	bl ov11_0222FF74
	mov r1, #2
	tst r0, r1
	ldr r0, _022542B0 ; =0x00000317
	beq _0225428E
	strh r0, [r7, #2]
	mov r0, #8
	strb r0, [r7, #1]
	add r0, r5, #0
	mov r1, #3
	bl ov11_0223022C
	str r0, [r7, #4]
	b _0225429E
_0225428E:
	strh r0, [r7, #2]
	mov r0, #8
	strb r0, [r7, #1]
	add r0, r5, #0
	mov r1, #1
	bl ov11_0223022C
	str r0, [r7, #4]
_0225429E:
	add r0, r5, #0
	mov r1, #0xc1
	bl ov11_02231468
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022542AC: .word 0x0000030D
_022542B0: .word 0x00000317

	thumb_func_start ov11_022542B4
ov11_022542B4: ; 0x022542B4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0xef
	add r4, r2, #0
	lsl r1, r1, #2
	strh r1, [r4, #2]
	mov r1, #8
	add r5, r0, #0
	strb r1, [r4, #1]
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	beq _022542F4
	bl sub_02031190
	bl sub_020313CC
	cmp r0, #0
	beq _022542E8
	add r0, r5, #0
	mov r1, #4
	bl ov11_0223022C
	str r0, [r4, #4]
	b _022542FC
_022542E8:
	add r0, r5, #0
	mov r1, #2
	bl ov11_0223022C
	str r0, [r4, #4]
	b _022542FC
_022542F4:
	mov r0, #0x65
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	str r0, [r4, #4]
_022542FC:
	add r0, r5, #0
	mov r1, #0xc2
	bl ov11_02231468
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02254308
ov11_02254308: ; 0x02254308
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	str r0, [sp, #0x18]
	str r1, [sp, #0x1c]
	add r5, r2, #0
	add r4, r3, #0
	bl ov11_02230078
	add r7, r0, #0
	ldr r0, [sp, #0x18]
	bl ov11_02230080
	add r6, r0, #0
	ldr r0, [sp, #0x18]
	bl ov11_022300CC
	str r0, [sp, #0x20]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _022543EC ; =0x00004E2F
	add r3, r5, #0
	add r0, r4, r0
	str r0, [sp, #8]
	add r0, r7, #0
	add r1, r6, #0
	mov r2, #0x1b
	add r3, #0xc3
	bl sub_0200C00C
	mov r0, #0x1b
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x2f
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _022543F0 ; =0x00004E2A
	mov r1, #2
	add r0, r4, r0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	add r2, r7, #0
	add r3, r6, #0
	bl sub_0200C0DC
	mov r0, #1
	str r0, [sp]
	ldr r0, _022543F4 ; =0x00004E27
	add r3, r5, #0
	add r0, r4, r0
	str r0, [sp, #4]
	add r0, r7, #0
	add r1, r6, #0
	mov r2, #0x1b
	add r3, #0xcb
	bl sub_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _022543F4 ; =0x00004E27
	add r5, #0xd3
	add r0, r4, r0
	str r0, [sp, #4]
	add r0, r7, #0
	add r1, r6, #0
	mov r2, #0x1b
	add r3, r5, #0
	bl sub_0200C13C
	ldr r5, _022543F8 ; =ov11_0225E89C
	add r3, sp, #0x24
	mov r2, #6
_022543A0:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022543A0
	ldr r0, [r5]
	ldr r1, _022543EC ; =0x00004E2F
	str r0, [r3]
	add r0, r4, r1
	str r0, [sp, #0x38]
	sub r0, r1, #5
	add r0, r4, r0
	sub r1, #8
	str r0, [sp, #0x3c]
	add r0, r4, r1
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	add r0, r7, #0
	add r1, r6, #0
	add r2, sp, #0x24
	bl sub_0200C154
	ldr r1, [sp, #0x1c]
	mov r2, #6
	add r3, r1, #0
	mul r3, r2
	ldr r1, _022543FC ; =ov08_0222D550
	ldr r2, _02254400 ; =ov08_0222D552
	ldrsh r1, [r1, r3]
	ldrsh r2, [r2, r3]
	add r4, r0, #0
	bl sub_0200C714
	add r0, r4, #0
	bl sub_0200C5A8
	add r0, r4, #0
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022543EC: .word 0x00004E2F
_022543F0: .word 0x00004E2A
_022543F4: .word 0x00004E27
_022543F8: .word ov11_0225E89C
_022543FC: .word ov08_0222D550
_02254400: .word ov08_0222D552

	thumb_func_start ov11_02254404
ov11_02254404: ; 0x02254404
	push {r4, r5, r6, r7, lr}
	sub sp, #0xac
	str r0, [sp]
	ldr r0, [r3, #0x4c]
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	cmp r0, #0
	bne _02254422
	mov r0, #8
	str r0, [sp, #0x84]
	add r0, r3, #0
	ldrh r0, [r0, #2]
	str r0, [sp, #0x18]
	b _0225442C
_02254422:
	mov r0, #0x3f
	str r0, [sp, #0x84]
	add r0, r3, #0
	ldr r0, [r0, #0x50]
	str r0, [sp, #0x18]
_0225442C:
	ldr r0, [sp]
	bl ov11_0222FF68
	str r0, [sp, #0x20]
	ldr r0, [sp]
	bl ov11_022300CC
	str r0, [sp, #0x24]
	ldr r0, [sp]
	bl ov11_02230078
	add r5, sp, #0x1c
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xc]
	mov r4, #0
	str r0, [sp, #0x14]
	str r5, [sp, #0x10]
	add r6, r5, #0
	add r7, r0, #0
_02254452:
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_022312D0
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x14]
	ldrh r1, [r0, #0x18]
	ldr r0, [sp, #0x10]
	strh r1, [r0, #0x34]
	ldr r0, [sp, #0xc]
	add r0, r0, r4
	add r0, #0x20
	ldrb r1, [r0]
	add r0, r6, #0
	add r0, #0x3c
	strb r1, [r0]
	ldr r0, [sp, #0xc]
	add r0, r0, r4
	add r0, #0x24
	ldrb r1, [r0]
	add r0, r6, #0
	add r0, #0x40
	strb r1, [r0]
	ldr r0, [sp, #0xc]
	add r0, r0, r4
	add r0, #0x28
	ldrb r1, [r0]
	add r0, r6, #0
	add r0, #0x44
	strb r1, [r0]
	ldr r0, [r7, #0x2c]
	add r4, r4, #1
	str r0, [r5, #0x48]
	ldr r0, [r7, #0x3c]
	add r6, r6, #1
	str r0, [r5, #0x58]
	ldr r0, [sp, #0x14]
	add r5, r5, #4
	add r0, r0, #2
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r7, r7, #4
	add r0, r0, #2
	str r0, [sp, #0x10]
	cmp r4, #4
	blt _02254452
	ldr r0, [sp]
	add r1, sp, #0x38
	bl ov11_02231504
	ldr r0, [sp]
	add r1, sp, #0x3c
	bl ov11_02231534
	ldr r0, [sp]
	bl ov11_0222FF74
	mov r2, #0x65
	str r0, [sp, #0x4c]
	ldr r1, [sp, #4]
	lsl r2, r2, #2
	ldrb r1, [r1, r2]
	ldr r0, [sp]
	bl ov11_02230E88
	str r0, [sp, #0xa0]
	ldr r0, [sp]
	bl ov11_02231228
	str r0, [sp, #0xa4]
	ldr r0, [sp]
	bl ov11_02231230
	str r0, [sp, #0xa8]
	mov r0, #7
	str r0, [sp, #0x88]
	ldr r0, [sp]
	bl ov11_022302A8
	add r0, r0, #3
	str r0, [sp, #0x8c]
	ldr r0, [sp]
	bl ov11_02230C68
	add r4, r0, #0
	ldr r0, [sp]
	bl ov11_022302A8
	lsl r1, r0, #1
	add r0, r0, r1
	add r0, #0x9e
	add r0, r4, r0
	str r0, [sp, #0x90]
	mov r0, #2
	str r0, [sp, #0x94]
	mov r0, #0
	ldr r2, [sp, #0x18]
	str r0, [sp, #0x98]
	mov r0, #8
	str r0, [sp, #0x9c]
	lsl r2, r2, #0x10
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	lsr r2, r2, #0x10
	add r3, sp, #0x1c
	bl ov08_02212048
	add sp, #0xac
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_0225452C
ov11_0225452C: ; 0x0225452C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r2, #0
	add r7, r1, #0
	str r3, [r6]
	str r0, [sp]
	str r3, [r6, #4]
	mov r4, #0
	add r5, r6, #0
	str r7, [sp, #0xc]
	str r6, [sp, #8]
	str r7, [sp, #4]
_02254544:
	ldr r0, [sp]
	add r1, r4, #0
	bl ov11_022312D0
	str r0, [r5, #8]
	ldr r0, [sp, #0xc]
	ldrh r1, [r0, #0x18]
	ldr r0, [sp, #8]
	strh r1, [r0, #0x28]
	add r0, r7, r4
	add r0, #0x20
	ldrb r1, [r0]
	add r0, r6, r4
	add r0, #0x30
	strb r1, [r0]
	add r0, r7, r4
	add r0, #0x24
	ldrb r1, [r0]
	add r0, r6, r4
	add r0, #0x34
	strb r1, [r0]
	add r0, r7, r4
	add r0, #0x28
	ldrb r1, [r0]
	add r0, r6, r4
	add r0, #0x38
	strb r1, [r0]
	ldr r0, [sp, #4]
	add r4, r4, #1
	ldr r0, [r0, #0x2c]
	str r0, [r5, #0x3c]
	ldr r0, [sp, #0xc]
	add r5, r5, #4
	add r0, r0, #2
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	add r0, r0, #2
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r0, r0, #4
	str r0, [sp, #4]
	cmp r4, #4
	blt _02254544
	add r1, r6, #0
	ldr r0, [sp]
	add r1, #0x4c
	bl ov11_02231504
	add r6, #0x18
	ldr r0, [sp]
	add r1, r6, #0
	bl ov11_02231534
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022545B4
ov11_022545B4: ; 0x022545B4
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r5, r1, #0
	cmp r2, #0
	bne _022545F2
	add r0, sp, #0
	ldrh r6, [r0, #0x10]
	mov r1, #9
	add r0, r6, #0
	bl GetWazaAttr
	mov r1, #0x40
	tst r0, r1
	bne _022545D4
	mov r0, #1
	b _022545D6
_022545D4:
	mov r0, #0
_022545D6:
	strb r0, [r4]
	add r0, r6, #0
	mov r1, #9
	bl GetWazaAttr
	mov r1, #0x80
	tst r0, r1
	beq _022545EC
	mov r0, #1
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_022545EC:
	mov r0, #0
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_022545F2:
	sub r3, #0x12
	cmp r3, #0x15
	bhi _02254642
	add r0, r3, r3
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254604: ; jump table
	.short _02254630 - _02254604 - 2 ; case 0
	.short _02254630 - _02254604 - 2 ; case 1
	.short _02254630 - _02254604 - 2 ; case 2
	.short _02254630 - _02254604 - 2 ; case 3
	.short _02254630 - _02254604 - 2 ; case 4
	.short _02254642 - _02254604 - 2 ; case 5
	.short _02254642 - _02254604 - 2 ; case 6
	.short _02254642 - _02254604 - 2 ; case 7
	.short _02254642 - _02254604 - 2 ; case 8
	.short _02254642 - _02254604 - 2 ; case 9
	.short _02254642 - _02254604 - 2 ; case 10
	.short _02254642 - _02254604 - 2 ; case 11
	.short _02254642 - _02254604 - 2 ; case 12
	.short _02254630 - _02254604 - 2 ; case 13
	.short _02254630 - _02254604 - 2 ; case 14
	.short _02254642 - _02254604 - 2 ; case 15
	.short _02254630 - _02254604 - 2 ; case 16
	.short _02254630 - _02254604 - 2 ; case 17
	.short _0225463A - _02254604 - 2 ; case 18
	.short _02254630 - _02254604 - 2 ; case 19
	.short _0225463A - _02254604 - 2 ; case 20
	.short _02254630 - _02254604 - 2 ; case 21
_02254630:
	mov r0, #1
	strb r0, [r4]
	mov r0, #0
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_0225463A:
	mov r0, #1
	strb r0, [r4]
	strb r0, [r5]
	pop {r4, r5, r6, pc}
_02254642:
	mov r0, #0
	strb r0, [r4]
	strb r0, [r5]
	pop {r4, r5, r6, pc}
	.align 2, 0

	.section .rodata

	.global ov11_0225E818
ov11_0225E818: ; 0x0225E818
	.byte 0x06, 0x01, 0x08, 0x03, 0x07, 0x05, 0x00, 0x00

	.global ov11_0225E820
ov11_0225E820: ; 0x0225E820
	.byte 0x09, 0x17, 0x05, 0x13, 0x0D, 0x11, 0x0F, 0x07
	.byte 0x15, 0x0B, 0x19, 0x0B, 0x0B, 0x00, 0x00, 0x00

	.global ov11_0225E830
ov11_0225E830: ; 0x0225E830
	.byte 0x0A

	.global ov11_0225E831
ov11_0225E831: ; 0x0225E831
	.byte 0x28, 0x0A, 0x23, 0x0A, 0x1E, 0x0A, 0x19
	.byte 0x0A, 0x14, 0x0A, 0x0F, 0x0A, 0x0A, 0x0F, 0x0A, 0x14, 0x0A, 0x19, 0x0A, 0x1E, 0x0A, 0x23, 0x0A
	.byte 0x28, 0x0A

	.global ov11_0225E84A
ov11_0225E84A: ; 0x0225E84A
	.byte 0x00, 0x00, 0x97, 0x72, 0xFF, 0x3F, 0xF0, 0x7A, 0xDF, 0x7A, 0xD7, 0x53, 0xF5, 0x67
	.byte 0x2C, 0x7B, 0x7E, 0x2B, 0x1F, 0x43, 0xDD, 0x7B, 0x3F, 0x2A, 0x3F, 0x29, 0xCE, 0x45, 0x1F, 0x73
	.byte 0x51, 0x7F, 0x1E, 0x15

	.global ov11_0225E86C
ov11_0225E86C: ; 0x0225E86C
	.byte 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00
	.byte 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00
	.byte 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov11_0225E89C
ov11_0225E89C: ; 0x0225E89C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2F, 0x4E, 0x00, 0x00, 0x2A, 0x4E, 0x00, 0x00
	.byte 0x27, 0x4E, 0x00, 0x00, 0x27, 0x4E, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global ov11_0225E8D0
ov11_0225E8D0: ; 0x0225E8D0
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xFF, 0x04, 0x00
	.byte 0xE4, 0xFF, 0xF5, 0xFF, 0x32, 0x00, 0xF4, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xDE, 0xFF, 0x04, 0x00, 0xE4, 0xFF, 0xF5, 0xFF, 0x32, 0x00, 0xF4, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xFF, 0x04, 0x00, 0xE4, 0xFF, 0xF5, 0xFF, 0x32, 0x00, 0xF4, 0xFF
	.byte 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFA, 0xFF, 0xE4, 0xFF, 0xEE, 0xFF
	.byte 0x32, 0x00, 0xDC, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFE, 0xFF
	.byte 0xE4, 0xFF, 0xEE, 0xFF, 0x32, 0x00, 0xE4, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xDE, 0xFF, 0x04, 0x00, 0xE4, 0xFF, 0xF5, 0xFF, 0x32, 0x00, 0xF4, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xFF, 0x04, 0x00, 0xE4, 0xFF, 0xF5, 0xFF, 0x32, 0x00, 0xF4, 0xFF
	.byte 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xFF, 0x04, 0x00, 0xE9, 0xFF, 0xFF, 0xFF
	.byte 0x32, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0xFF, 0x7F
