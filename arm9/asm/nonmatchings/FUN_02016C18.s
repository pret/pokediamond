.section .text

glabel FUN_02016C18

.extern FUN_020177DC
.extern FUN_020179E0
.extern GX_EngineAToggleLayers
.extern GX_EngineBToggleLayers
.extern AllocFromHeap
.extern MIi_CpuClear16

	push {r3-r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x4]
	str r3, [sp, #0x8]
	add r4, r2, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x10]
	ldr r1, [sp, #0x8]
	bl FUN_020177DC
	add r5, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r0, #0x7
	bls _02016C36
	b _0201705A
_02016C36:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02016C42: ; jump table (using 16-bit offset)
	.short _02016C52 - _02016C42 - 2; case 0
	.short _02016CAA - _02016C42 - 2; case 1
	.short _02016D02 - _02016C42 - 2; case 2
	.short _02016DA4 - _02016C42 - 2; case 3
	.short _02016E46 - _02016C42 - 2; case 4
	.short _02016E9E - _02016C42 - 2; case 5
	.short _02016EF6 - _02016C42 - 2; case 6
	.short _02016F98 - _02016C42 - 2; case 7
_02016C52:
	mov r0, #0x1
	add r1, r0, #0x0
	bl GX_EngineAToggleLayers
	ldrb r3, [r4, #0x14]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x13]
	lsl r6, r3, #0xd
	lsl r0, r0, #0x7
	lsl r3, r2, #0x2
	str r0, [sp, #0xc]
	ldr r2, _02016FB4 ; =0x04000008
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r1, r0
	ldr r0, [sp, #0xc]
	orr r0, r1
	orr r0, r7
	orr r0, r3
	orr r0, r6
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016CA0
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016CA0:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016CAA:
	mov r0, #0x2
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	ldrb r3, [r4, #0x14]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x13]
	lsl r6, r3, #0xd
	lsl r0, r0, #0x7
	lsl r3, r2, #0x2
	str r0, [sp, #0x10]
	ldr r2, _02016FB8 ; =0x0400000A
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r1, r0
	ldr r0, [sp, #0x10]
	orr r0, r1
	orr r0, r7
	orr r0, r3
	orr r0, r6
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016CF8
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016CF8:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016D02:
	mov r0, #0x4
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016D18
	cmp r0, #0x1
	beq _02016D3A
	cmp r0, #0x2
	beq _02016D5C
_02016D18:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FBC ; =0x0400000C
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016D7C
_02016D3A:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, _02016FBC ; =0x0400000C
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016D7C
_02016D5C:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FBC ; =0x0400000C
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02016D7C:
	ldr r0, _02016FBC ; =0x0400000C
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02016D9A
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02016D9A:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
	b _0201705A
_02016DA4:
	mov r0, #0x8
	mov r1, #0x1
	bl GX_EngineAToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016DBA
	cmp r0, #0x1
	beq _02016DDC
	cmp r0, #0x2
	beq _02016DFE
_02016DBA:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FC0 ; =0x0400000E
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016E1E
_02016DDC:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, _02016FC0 ; =0x0400000E
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016E1E
_02016DFE:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FC0 ; =0x0400000E
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02016E1E:
	ldr r0, _02016FC0 ; =0x0400000E
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02016E3C
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02016E3C:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
	b _0201705A
_02016E46:
	mov r0, #0x1
	add r1, r0, #0x0
	bl GX_EngineBToggleLayers
	ldrb r3, [r4, #0x14]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x13]
	lsl r6, r3, #0xd
	lsl r0, r0, #0x7
	lsl r3, r2, #0x2
	str r0, [sp, #0x14]
	ldr r2, _02016FC4 ; =0x04001008
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r1, r0
	ldr r0, [sp, #0x14]
	orr r0, r1
	orr r0, r7
	orr r0, r3
	orr r0, r6
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016E94
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016E94:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016E9E:
	mov r0, #0x2
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrb r3, [r4, #0x14]
	lsl r0, r0, #0x7
	mov r12, r0
	ldr r2, _02016FC8 ; =0x0400100A
	lsl r7, r1, #0x8
	ldrh r1, [r2, #0x0]
	mov r0, #0x43
	lsl r3, r3, #0xd
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	mov r1, r12
	orr r0, r1
	orr r0, r7
	orr r0, r6
	orr r0, r3
	strh r0, [r2, #0x0]
	ldrh r1, [r2, #0x0]
	mov r0, #0x3
	bic r1, r0
	ldrb r0, [r4, #0x15]
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _02016EEC
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	orr r0, r1
	strh r0, [r2, #0x0]
	b _0201705A
_02016EEC:
	ldrh r1, [r2, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r2, #0x0]
	b _0201705A
_02016EF6:
	mov r0, #0x4
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016F0C
	cmp r0, #0x1
	beq _02016F2E
	cmp r0, #0x2
	beq _02016F50
_02016F0C:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FCC ; =0x0400100C
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016F70
_02016F2E:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, _02016FCC ; =0x0400100C
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02016F70
_02016F50:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FCC ; =0x0400100C
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02016F70:
	ldr r0, _02016FCC ; =0x0400100C
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02016F8E
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02016F8E:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
	b _0201705A
_02016F98:
	mov r0, #0x8
	mov r1, #0x1
	bl GX_EngineBToggleLayers
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02016FAE
	cmp r0, #0x1
	beq _02016FF2
	cmp r0, #0x2
	beq _02017014
_02016FAE:
	ldrb r1, [r4, #0x12]
	ldr r7, _02016FD0 ; =0x0400100E
	b _02016FD4
	.balign 4
_02016FB4: .word 0x04000008
_02016FB8: .word 0x0400000A
_02016FBC: .word 0x0400000C
_02016FC0: .word 0x0400000E
_02016FC4: .word 0x04001008
_02016FC8: .word 0x0400100A
_02016FCC: .word 0x0400100C
_02016FD0: .word 0x0400100E
_02016FD4:
	ldrb r2, [r4, #0x13]
	lsl r3, r1, #0x8
	ldrb r0, [r4, #0x11]
	lsl r6, r2, #0x2
	ldrh r1, [r7, #0x0]
	lsl r2, r0, #0x7
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02017034
_02016FF2:
	ldrb r2, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x16]
	lsl r3, r2, #0x2
	ldr r7, _020170F0 ; =0x0400100E
	lsl r2, r1, #0x8
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
	b _02017034
_02017014:
	ldrb r1, [r4, #0x12]
	ldr r7, _020170F0 ; =0x0400100E
	ldrb r0, [r4, #0x16]
	lsl r3, r1, #0x8
	ldrb r2, [r4, #0x13]
	lsl r6, r0, #0xd
	ldrh r1, [r7, #0x0]
	mov r0, #0x43
	lsl r2, r2, #0x2
	and r0, r1
	lsl r1, r5, #0xe
	orr r0, r1
	orr r0, r2
	orr r0, r3
	orr r0, r6
	strh r0, [r7, #0x0]
_02017034:
	ldr r0, _020170F0 ; =0x0400100E
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	ldrb r1, [r4, #0x15]
	orr r1, r2
	strh r1, [r0, #0x0]
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	beq _02017052
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	orr r1, r2
	strh r1, [r0, #0x0]
	b _0201705A
_02017052:
	ldrh r2, [r0, #0x0]
	mov r1, #0x40
	bic r2, r1
	strh r2, [r0, #0x0]
_0201705A:
	ldr r0, [sp, #0x4]
	mov r1, #0x2c
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	mul r5, r1
	add r2, r0, r5
	mov r3, #0x0
	mov r0, #0x1
	strh r3, [r2, #0x20]
	lsl r0, r0, #0xc
	str r0, [r2, #0x24]
	str r0, [r2, #0x28]
	str r3, [r2, #0x2c]
	str r3, [r2, #0x30]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020170A2
	ldr r0, [sp, #0x0]
	ldr r6, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r6, #0x8
	bl AllocFromHeap
	str r0, [r6, r5]
	ldr r1, [r6, r5]
	ldr r2, [r4, #0x8]
	mov r0, #0x0
	bl MIi_CpuClear16
	ldr r0, [sp, #0x0]
	ldr r2, [r4, #0x8]
	add r1, r0, r5
	str r2, [r1, #0xc]
	ldr r0, [r4, #0xc]
	str r0, [r1, #0x10]
	b _020170A8
_020170A2:
	str r3, [r2, #0x8]
	str r3, [r2, #0xc]
	str r3, [r2, #0x10]
_020170A8:
	ldr r0, [sp, #0x0]
	ldrb r1, [r4, #0x10]
	add r0, r0, r5
	strb r1, [r0, #0x1d]
	ldr r1, [sp, #0x8]
	strb r1, [r0, #0x1c]
	ldrb r1, [r4, #0x11]
	strb r1, [r0, #0x1e]
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	bne _020170CA
	ldrb r1, [r4, #0x11]
	cmp r1, #0x0
	bne _020170CA
	mov r1, #0x20
	strb r1, [r0, #0x1f]
	b _020170D2
_020170CA:
	ldr r0, [sp, #0x0]
	mov r1, #0x40
	add r0, r0, r5
	strb r1, [r0, #0x1f]
_020170D2:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r3, [r4, #0x0]
	mov r2, #0x0
	bl FUN_020179E0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r3, [r4, #0x4]
	mov r2, #0x3
	bl FUN_020179E0
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_020170F0: .word 0x0400100E
