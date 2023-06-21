	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02012944
sub_02012944: ; 0x02012944
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0xc
	add r4, r2, #0x0
	bl AllocFromHeap
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	mov r1, #0x1
	strb r1, [r0, #0x9]
	str r5, [r0, #0x0]
	str r4, [r0, #0x4]
	pop {r3-r5, pc}

	thumb_func_start sub_02012974
sub_02012974: ; 0x02012974
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201297E
	bl GF_AssertFail
_0201297E:
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02012988
sub_02012988: ; 0x02012988
	push {r4, lr}
	add r4, r0, #0x0
	bne _02012992
	bl GF_AssertFail
_02012992:
	ldrb r0, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201299C
sub_0201299C: ; 0x0201299C
	push {r4, lr}
	add r4, r0, #0x0
	bne _020129A6
	bl GF_AssertFail
_020129A6:
	ldrb r1, [r4, #0x8]
	mov r0, #0x1
	eor r0, r1
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_020129B4
sub_020129B4: ; 0x020129B4
	cmp r0, #0x0
	beq _020129C6
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _020129C6
	ldrb r2, [r0, #0x8]
	mov r1, #0x1
	eor r1, r2
	strb r1, [r0, #0x8]
_020129C6:
	bx lr

	thumb_func_start sub_020129C8
sub_020129C8: ; 0x020129C8
	push {r3, lr}
	mov r0, #0x0
	bl MI_StopDma
	mov r0, #0x0
	bl MI_WaitDma
	pop {r3, pc}

	thumb_func_start sub_020129D8
sub_020129D8: ; 0x020129D8
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r3, #0x1
	bne _020129F2
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl MI_HBlankDmaCopy32
	pop {r4-r6, pc}
_020129F2:
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl MI_HBlankDmaCopy16
	pop {r4-r6, pc}

	thumb_func_start sub_02012A00
sub_02012A00: ; 0x02012A00
	push {r3-r5, lr}
	ldr r1, _02012A2C ; =0x0000079C
	add r5, r0, #0x0
	bl AllocFromHeap
	ldr r2, _02012A2C ; =0x0000079C
	mov r1, #0x0
	add r4, r0, #0x0
	bl memset
	mov r2, #0x3
	lsl r2, r2, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r4, r2
	bl sub_02012944
	mov r1, #0x6
	lsl r1, r1, #0x8
	str r0, [r4, r1]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02012A2C: .word 0x0000079C

	thumb_func_start sub_02012A30
sub_02012A30: ; 0x02012A30
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r5, #0x0
	bne _02012A42
	bl GF_AssertFail
_02012A42:
	ldr r0, _02012AB0 ; =0x00000604
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _02012A4E
	bl GF_AssertFail
_02012A4E:
	ldr r0, _02012AB4 ; =0x0000078C
	mov r2, #0x0
	strb r4, [r5, r0]
	add r1, r0, #0x1
	strb r6, [r5, r1]
	add r1, r0, #0x0
	add r1, #0xc
	strh r2, [r5, r1]
	add r2, sp, #0x8
	mov r1, #0x14
	ldrsh r2, [r2, r1]
	add r1, r0, #0x0
	add r1, #0xe
	strh r2, [r5, r1]
	add r1, r0, #0x4
	ldr r2, [sp, #0x20]
	add r0, #0x8
	str r2, [r5, r1]
	ldr r1, [sp, #0x24]
	ldr r3, [sp, #0x18]
	str r1, [r5, r0]
	ldr r0, _02012AB8 ; =0x0000060C
	mov r1, #0xc0
	add r0, r5, r0
	add r2, r7, #0x0
	bl sub_02012B88
	ldr r0, _02012ABC ; =sub_02012BE4
	ldr r2, [sp, #0x28]
	add r1, r5, #0x0
	bl sub_0200CA44
	ldr r1, _02012AB0 ; =0x00000604
	mov r2, #0x3
	str r0, [r5, r1]
	ldr r0, _02012AC0 ; =0x00000794
	add r1, r5, #0x0
	ldr r0, [r5, r0]
	lsl r2, r2, #0x8
	bl MIi_CpuClear32
	ldr r0, _02012AC0 ; =0x00000794
	mov r2, #0x3
	lsl r2, r2, #0x8
	ldr r0, [r5, r0]
	add r1, r5, r2
	bl MIi_CpuClear32
	pop {r3-r7, pc}
	.balign 4
_02012AB0: .word 0x00000604
_02012AB4: .word 0x0000078C
_02012AB8: .word 0x0000060C
_02012ABC: .word sub_02012BE4
_02012AC0: .word 0x00000794

	thumb_func_start sub_02012AC4
sub_02012AC4: ; 0x02012AC4
	push {r4, lr}
	add r4, r0, #0x0
	bne _02012ACE
	bl GF_AssertFail
_02012ACE:
	ldr r0, _02012AF8 ; =0x00000604
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02012AF4
	bl sub_0200CAB4
	ldr r0, _02012AF8 ; =0x00000604
	mov r1, #0x0
	str r1, [r4, r0]
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl sub_02012988
	ldr r1, _02012AFC ; =0x00000794
	mov r2, #0x3
	ldr r1, [r4, r1]
	lsl r2, r2, #0x8
	bl memset
_02012AF4:
	pop {r4, pc}
	nop
_02012AF8: .word 0x00000604
_02012AFC: .word 0x00000794

	thumb_func_start sub_02012B00
sub_02012B00: ; 0x02012B00
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02012AC4
	bl sub_02012C90
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl sub_02012974
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02012B20
sub_02012B20: ; 0x02012B20
	mov r1, #0x6
	lsl r1, r1, #0x8
	ldr r3, _02012B2C ; =sub_02012988
	ldr r0, [r0, r1]
	bx r3
	nop
_02012B2C: .word sub_02012988

	thumb_func_start sub_02012B30
sub_02012B30: ; 0x02012B30
	push {r4, lr}
	add r4, r0, #0x0
	beq _02012B5E
	ldr r0, _02012B60 ; =0x00000604
	ldr r1, [r4, r0]
	cmp r1, #0x0
	beq _02012B5E
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl sub_020129B4
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl sub_02012988
	add r1, r0, #0x0
	ldr r0, _02012B64 ; =0x00000794
	mov r2, #0x3
	ldr r0, [r4, r0]
	lsl r2, r2, #0x8
	bl MIi_CpuClear32
_02012B5E:
	pop {r4, pc}
	.balign 4
_02012B60: .word 0x00000604
_02012B64: .word 0x00000794

	thumb_func_start sub_02012B68
sub_02012B68: ; 0x02012B68
	push {r4, lr}
	add r4, r0, #0x0
	beq _02012B80
	ldr r0, _02012B84 ; =0x00000604
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02012B80
	bl sub_02012C90
	add r0, r4, #0x0
	bl sub_02012C98
_02012B80:
	pop {r4, pc}
	nop
_02012B84: .word 0x00000604

	thumb_func_start sub_02012B88
sub_02012B88: ; 0x02012B88
	push {r4-r7, lr}
	sub sp, #0xc
	mov r4, #0x0
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	str r2, [sp, #0x0]
	cmp r7, #0x0
	bls _02012BD6
	asr r0, r3, #0x1f
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
_02012BA0:
	asr r0, r4, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02012BDC ; =FX_SinCosTable_
	ldr r2, [sp, #0x4]
	ldrsh r0, [r0, r1]
	ldr r3, [sp, #0x8]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02012BE0 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r4, r0
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r5, r5, #0x2
	cmp r6, r7
	blo _02012BA0
_02012BD6:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02012BDC: .word FX_SinCosTable_
_02012BE0: .word 0x00000000

	thumb_func_start sub_02012BE4
sub_02012BE4: ; 0x02012BE4
	push {r3-r7, lr}
	mov r0, #0x6
	add r6, r1, #0x0
	lsl r0, r0, #0x8
	ldr r0, [r6, r0]
	bl sub_02012988
	add r5, r0, #0x0
	ldr r0, _02012C80 ; =0x00000798
	mov r1, #0x64
	ldrsh r0, [r6, r0]
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	ldr r0, _02012C84 ; =0x0000078C
	ldrb r4, [r6, r0]
	add r0, r0, #0x1
	ldrb r0, [r6, r0]
	cmp r4, r0
	bgt _02012C4C
	lsl r0, r4, #0x2
	add r5, r5, r0
_02012C12:
	ldr r2, [r5, #0x0]
	lsl r0, r2, #0x10
	asr r7, r0, #0x10
	lsl r0, r3, #0x1
	add r1, r6, r0
	ldr r0, _02012C88 ; =0x0000060C
	ldrsh r0, [r1, r0]
	add r0, r7, r0
	lsl r0, r0, #0x10
	asr r1, r0, #0x10
	lsr r0, r2, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r1, #0x10
	orr r0, r1
	stmia r5!, {r0}
	add r0, r3, #0x1
	mov r1, #0xc0
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r3, r0, #0x18
	ldr r0, _02012C8C ; =0x0000078D
	add r4, r4, #0x1
	ldrb r0, [r6, r0]
	cmp r4, r0
	ble _02012C12
_02012C4C:
	ldr r1, _02012C80 ; =0x00000798
	add r0, r1, #0x2
	ldrsh r2, [r6, r1]
	ldrsh r0, [r6, r0]
	add r4, r6, r1
	add r0, r2, r0
	strh r0, [r4, #0x0]
	ldrsh r0, [r6, r1]
	mov r1, #0x4b
	lsl r1, r1, #0x8
	cmp r0, r1
	blt _02012C70
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	bl _s32_div_f
	strh r1, [r4, #0x0]
	pop {r3-r7, pc}
_02012C70:
	cmp r0, #0x0
	bge _02012C7C
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, r1
	strh r0, [r4, #0x0]
_02012C7C:
	pop {r3-r7, pc}
	nop
_02012C80: .word 0x00000798
_02012C84: .word 0x0000078C
_02012C88: .word 0x0000060C
_02012C8C: .word 0x0000078D

	thumb_func_start sub_02012C90
sub_02012C90: ; 0x02012C90
	ldr r3, _02012C94 ; =sub_020129C8
	bx r3
	.balign 4
_02012C94: .word sub_020129C8

	thumb_func_start sub_02012C98
sub_02012C98: ; 0x02012C98
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02012CA2
	bl GF_AssertFail
_02012CA2:
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl sub_0201299C
	mov r1, #0x3
	lsl r1, r1, #0x8
	add r5, r0, #0x0
	bl DC_FlushRange
	mov r1, #0x79
	lsl r1, r1, #0x4
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	mov r2, #0x4
	mov r3, #0x1
	bl sub_020129D8
	pop {r3-r5, pc}
