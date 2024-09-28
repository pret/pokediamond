	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov41_02254854
ov41_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x90
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov41_02254990
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov41_02254A88
	add r1, r4, #0
	mov r2, #1
	bl SysTask_CreateOnMainQueue
	cmp r0, #0
	beq _0225488C
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488C:
	add r0, r4, #0
	bl FreeToHeap
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word ov41_02254A88
	thumb_func_end ov41_02254854

	thumb_func_start ov41_0225489C
ov41_0225489C: ; 0x0225489C
	push {r4, r5}
	mov r4, #0
	add r5, r0, #0
	mov r3, #1
	add r2, r4, #0
_022548A6:
	add r1, r0, r4
	str r3, [r5, #0x5c]
	add r1, #0x4c
	add r4, r4, #1
	add r5, r5, #4
	strb r2, [r1]
	cmp r4, #3
	blt _022548A6
	str r3, [r0, #0x44]
	pop {r4, r5}
	bx lr
	thumb_func_end ov41_0225489C

	thumb_func_start ov41_022548BC
ov41_022548BC: ; 0x022548BC
	lsl r3, r1, #2
	add r3, r0, r3
	str r2, [r3, #0x5c]
	cmp r2, #0
	beq _022548CA
	mov r2, #0
	b _022548CC
_022548CA:
	mov r2, #1
_022548CC:
	add r1, r0, r1
	add r1, #0x4c
	strb r2, [r1]
	mov r1, #1
	str r1, [r0, #0x44]
	bx lr
	thumb_func_end ov41_022548BC

	thumb_func_start ov41_022548D8
ov41_022548D8: ; 0x022548D8
	lsl r3, r1, #2
	add r3, r0, r3
	ldr r3, [r3, #0x5c]
	cmp r3, #0
	beq _022548EC
	add r1, r0, r1
	add r1, #0x4c
	strb r2, [r1]
	mov r1, #1
	str r1, [r0, #0x44]
_022548EC:
	bx lr
	.align 2, 0
	thumb_func_end ov41_022548D8

	thumb_func_start ov41_022548F0
ov41_022548F0: ; 0x022548F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	add r4, r1, #0
	bl ov41_0225578C
	str r0, [r4, #0x10]
	ldr r0, [r5, #4]
	add r1, r4, #0
	mov r2, #0x48
	bl sub_020893F0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_022548F0

	thumb_func_start ov41_0225490C
ov41_0225490C: ; 0x0225490C
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #0x48
	bl sub_02089418
	cmp r0, #0
	beq _0225494C
	add r0, r4, #0
	add r0, #0x8c
	ldr r0, [r0]
	cmp r0, #2
	bne _02254952
	add r0, r4, #0
	bl ov41_02255108
	add r0, r4, #0
	bl ov41_022550F8
	cmp r0, #0
	beq _02254952
	add r0, r4, #0
	mov r1, #4
	add r0, #0x8c
	str r1, [r0]
	mov r0, #0
	str r0, [r4, #0x50]
	mov r0, #2
	str r0, [r4, #0x54]
	pop {r4, pc}
_0225494C:
	add r0, r4, #0
	bl ov41_02254954
_02254952:
	pop {r4, pc}
	thumb_func_end ov41_0225490C

	thumb_func_start ov41_02254954
ov41_02254954: ; 0x02254954
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r3, r4, #0
	mov r2, #1
	add r1, #0x8c
	str r2, [r1]
	mov r1, #0
	add r3, #0x48
	strb r1, [r3]
	add r3, r4, #0
	add r3, #0x49
	strb r1, [r3]
	add r3, r4, #0
	add r3, #0x4a
	strb r1, [r3]
	add r3, r4, #0
	add r3, #0x4b
	strb r1, [r3]
	str r2, [r4, #0x50]
	str r1, [r4, #0x54]
	str r1, [r4, #0x58]
	bl ov41_0225489C
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	pop {r4, pc}
	thumb_func_end ov41_02254954

	thumb_func_start ov41_02254990
ov41_02254990: ; 0x02254990
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	str r3, [r5, #4]
	bl ov41_0225490C
	add r0, r5, #0
	add r1, r5, #0
	add r0, #8
	add r1, #0x48
	add r2, r6, #0
	bl ov41_0225524C
	cmp r0, #0
	beq _02254A28
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #3]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254A30 ; =ov41_022557B0
	ldr r2, _02254A34 ; =ov41_02254A58
	mov r1, #0xb
	add r3, r5, #0
	bl ov20_02254130
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x10]
	mov r1, #3
	mov r2, #4
	bl ov20_022542C0
	ldr r0, [r5, #0x10]
	mov r1, #5
	mov r2, #4
	bl ov20_022542C0
	mov r1, #4
	ldr r0, [r5, #0x10]
	add r2, r1, #0
	bl ov20_022542C0
	ldr r0, [r5, #0x10]
	mov r1, #6
	mov r2, #4
	bl ov20_022542C0
	ldr r0, [r5, #0x10]
	mov r1, #7
	mov r2, #4
	bl ov20_022542C0
	ldr r0, [r5, #0x10]
	mov r1, #9
	mov r2, #4
	bl ov20_022542C0
	ldr r0, [r5, #0x10]
	mov r1, #8
	mov r2, #4
	bl ov20_022542C0
	ldr r0, [r5, #0x10]
	mov r1, #0xa
	mov r2, #4
	bl ov20_022542C0
	add sp, #4
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02254A28:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02254A30: .word ov41_022557B0
_02254A34: .word ov41_02254A58
	thumb_func_end ov41_02254990

	thumb_func_start ov41_02254A38
ov41_02254A38: ; 0x02254A38
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0x48
	bl ov41_022548F0
	ldr r0, [r4, #0x10]
	bl ov20_02254198
	ldr r0, [r4, #8]
	bl ov41_0225528C
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end ov41_02254A38

	thumb_func_start ov41_02254A58
ov41_02254A58: ; 0x02254A58
	push {r3, lr}
	add r2, r0, #0
	str r2, [r3, #0x14]
	str r1, [r3, #0x18]
	cmp r2, #3
	bhs _02254A84
	cmp r1, #1
	bne _02254A74
	add r1, r2, #0
	add r0, r3, #0
	mov r2, #1
	bl ov41_022548D8
	pop {r3, pc}
_02254A74:
	sub r0, r1, #2
	cmp r0, #1
	bhi _02254A84
	add r1, r2, #0
	add r0, r3, #0
	mov r2, #0
	bl ov41_022548D8
_02254A84:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov41_02254A58

	thumb_func_start ov41_02254A88
ov41_02254A88: ; 0x02254A88
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #7
	bhs _02254AD0
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	bl ov20_02252C14
	ldr r0, [r4, #0x44]
	cmp r0, #0
	beq _02254AAE
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov41_022553A4
	mov r0, #0
	str r0, [r4, #0x44]
_02254AAE:
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254AD4 ; =ov41_02255794
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254AD0
	add r0, r4, #0
	bl ov41_02254A38
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0xc]
	bl ov20_022529A0
_02254AD0:
	pop {r3, r4, r5, pc}
	nop
_02254AD4: .word ov41_02255794
	thumb_func_end ov41_02254A88

	thumb_func_start ov41_02254AD8
ov41_02254AD8: ; 0x02254AD8
	mov r1, #1
	strb r1, [r0, #3]
	bx lr
	.align 2, 0
	thumb_func_end ov41_02254AD8

	thumb_func_start ov41_02254AE0
ov41_02254AE0: ; 0x02254AE0
	ldrb r3, [r0, #3]
	ldrb r2, [r0]
	cmp r3, #0
	beq _02254AEA
	mov r1, #6
_02254AEA:
	strb r1, [r0]
	cmp r1, #0
	beq _02254AFA
	cmp r1, #6
	beq _02254AFA
	add r3, r0, #0
	add r3, #0x8c
	str r2, [r3]
_02254AFA:
	cmp r1, #6
	bhi _02254B50
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02254B0A: ; jump table
	.short _02254B50 - _02254B0A - 2 ; case 0
	.short _02254B18 - _02254B0A - 2 ; case 1
	.short _02254B22 - _02254B0A - 2 ; case 2
	.short _02254B2C - _02254B0A - 2 ; case 3
	.short _02254B36 - _02254B0A - 2 ; case 4
	.short _02254B40 - _02254B0A - 2 ; case 5
	.short _02254B4A - _02254B0A - 2 ; case 6
_02254B18:
	mov r1, #1
	str r1, [r0, #0x50]
	mov r1, #0
	str r1, [r0, #0x54]
	b _02254B50
_02254B22:
	mov r1, #0
	str r1, [r0, #0x50]
	mov r1, #1
	str r1, [r0, #0x54]
	b _02254B50
_02254B2C:
	mov r1, #0
	str r1, [r0, #0x50]
	mov r1, #1
	str r1, [r0, #0x54]
	b _02254B50
_02254B36:
	mov r1, #0
	str r1, [r0, #0x50]
	mov r1, #2
	str r1, [r0, #0x54]
	b _02254B50
_02254B40:
	mov r1, #0
	str r1, [r0, #0x50]
	mov r1, #3
	str r1, [r0, #0x54]
	b _02254B50
_02254B4A:
	add r1, r0, #0
	add r1, #0x8c
	str r2, [r1]
_02254B50:
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov41_02254AE0

	thumb_func_start ov41_02254B58
ov41_02254B58: ; 0x02254B58
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254B68
	cmp r0, #1
	beq _02254B78
	b _02254B94
_02254B68:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov41_022553A4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B94
_02254B78:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov41_022553C8
	cmp r0, #0
	beq _02254B94
	ldr r0, [r4, #0xc]
	bl ov20_0225298C
	add r0, r4, #0
	add r4, #0x8c
	ldr r1, [r4]
	bl ov41_02254AE0
_02254B94:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov41_02254B58

	thumb_func_start ov41_02254B98
ov41_02254B98: ; 0x02254B98
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #3]
	cmp r1, #0
	beq _02254BAC
	mov r1, #6
	bl ov41_02254AE0
	mov r0, #0
	pop {r4, pc}
_02254BAC:
	ldr r0, [r4, #8]
	bl ov41_022553D4
	cmp r0, #0
	bne _02254BBA
	mov r0, #0
	pop {r4, pc}
_02254BBA:
	ldr r1, [r4, #0x18]
	cmp r1, #1
	bne _02254C36
	ldr r0, [r4, #0x14]
	cmp r0, #2
	bhi _02254C36
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02254BEE
	cmp r0, #1
	beq _02254C2C
	cmp r0, #2
	bne _02254C32
	add r0, r4, #0
	bl ov41_02255170
	ldr r0, [r4, #8]
	mov r1, #5
	bl ov41_022553A4
	ldr r0, _02254D18 ; =0x00000663
	bl Poketch_PlaySoundEffect
	b _02254C32
_02254BEE:
	ldr r0, _02254D18 ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	bl ov41_0225504C
	mov r3, #0
	mov r2, #0
	eor r1, r3
	eor r0, r2
	orr r0, r1
	beq _02254C32
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	ldr r0, [r4, #8]
	mov r1, #3
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #2
	bl ov41_02254AE0
	b _02254C32
_02254C2C:
	ldr r0, _02254D1C ; =0x0000066E
	bl Poketch_PlaySoundEffect
_02254C32:
	mov r0, #0
	pop {r4, pc}
_02254C36:
	cmp r1, #1
	beq _02254C3E
	cmp r1, #7
	bne _02254D12
_02254C3E:
	ldr r1, [r4, #0x14]
	add r0, r4, #0
	add r0, #0x48
	cmp r1, #0xa
	bhi _02254D06
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02254C54: ; jump table
	.short _02254D06 - _02254C54 - 2 ; case 0
	.short _02254D06 - _02254C54 - 2 ; case 1
	.short _02254D06 - _02254C54 - 2 ; case 2
	.short _02254C6A - _02254C54 - 2 ; case 3
	.short _02254C7C - _02254C54 - 2 ; case 4
	.short _02254C90 - _02254C54 - 2 ; case 5
	.short _02254CA4 - _02254C54 - 2 ; case 6
	.short _02254CB8 - _02254C54 - 2 ; case 7
	.short _02254CCC - _02254C54 - 2 ; case 8
	.short _02254CE0 - _02254C54 - 2 ; case 9
	.short _02254CF4 - _02254C54 - 2 ; case 10
_02254C6A:
	mov r1, #0
	ldrsb r2, [r0, r1]
	add r2, r2, #1
	strb r2, [r0]
	ldrsb r2, [r0, r1]
	cmp r2, #9
	ble _02254D06
	strb r1, [r0]
	b _02254D06
_02254C7C:
	mov r1, #1
	ldrsb r2, [r0, r1]
	add r2, r2, #1
	strb r2, [r0, #1]
	ldrsb r1, [r0, r1]
	cmp r1, #9
	ble _02254D06
	mov r1, #0
	strb r1, [r0, #1]
	b _02254D06
_02254C90:
	mov r1, #0
	ldrsb r2, [r0, r1]
	sub r2, r2, #1
	strb r2, [r0]
	ldrsb r1, [r0, r1]
	cmp r1, #0
	bge _02254D06
	mov r1, #9
	strb r1, [r0]
	b _02254D06
_02254CA4:
	mov r1, #1
	ldrsb r2, [r0, r1]
	sub r2, r2, #1
	strb r2, [r0, #1]
	ldrsb r1, [r0, r1]
	cmp r1, #0
	bge _02254D06
	mov r1, #9
	strb r1, [r0, #1]
	b _02254D06
_02254CB8:
	mov r1, #2
	ldrsb r2, [r0, r1]
	add r2, r2, #1
	strb r2, [r0, #2]
	ldrsb r1, [r0, r1]
	cmp r1, #5
	ble _02254D06
	mov r1, #0
	strb r1, [r0, #2]
	b _02254D06
_02254CCC:
	mov r1, #3
	ldrsb r2, [r0, r1]
	add r2, r2, #1
	strb r2, [r0, #3]
	ldrsb r1, [r0, r1]
	cmp r1, #9
	ble _02254D06
	mov r1, #0
	strb r1, [r0, #3]
	b _02254D06
_02254CE0:
	mov r1, #2
	ldrsb r2, [r0, r1]
	sub r2, r2, #1
	strb r2, [r0, #2]
	ldrsb r1, [r0, r1]
	cmp r1, #0
	bge _02254D06
	mov r1, #5
	strb r1, [r0, #2]
	b _02254D06
_02254CF4:
	mov r1, #3
	ldrsb r2, [r0, r1]
	sub r2, r2, #1
	strb r2, [r0, #3]
	ldrsb r1, [r0, r1]
	cmp r1, #0
	bge _02254D06
	mov r1, #9
	strb r1, [r0, #3]
_02254D06:
	ldr r0, [r4, #8]
	mov r1, #5
	bl ov41_022553A4
	mov r0, #0
	str r0, [r4, #0x18]
_02254D12:
	mov r0, #0
	pop {r4, pc}
	nop
_02254D18: .word 0x00000663
_02254D1C: .word 0x0000066E
	thumb_func_end ov41_02254B98

	thumb_func_start ov41_02254D20
ov41_02254D20: ; 0x02254D20
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #3]
	cmp r1, #0
	beq _02254D34
	mov r1, #6
	bl ov41_02254AE0
	mov r0, #0
	pop {r4, pc}
_02254D34:
	bl ov41_02255108
	cmp r0, #0
	beq _02254D6C
	ldr r0, [r4, #8]
	mov r1, #5
	bl ov41_022553A4
	add r0, r4, #0
	bl ov41_022550F8
	cmp r0, #0
	beq _02254D6C
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	ldr r0, [r4, #8]
	mov r1, #6
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #4
	bl ov41_02254AE0
	mov r0, #0
	pop {r4, pc}
_02254D6C:
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _02254E00
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02254D86
	cmp r0, #1
	beq _02254D8E
	cmp r0, #2
	beq _02254DC0
	b _02254E00
_02254D86:
	ldr r0, _02254E04 ; =0x0000066E
	bl Poketch_PlaySoundEffect
	b _02254E00
_02254D8E:
	ldr r0, _02254E08 ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov41_022548BC
	add r0, r4, #0
	bl ov41_022550BC
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #3
	bl ov41_02254AE0
	b _02254E00
_02254DC0:
	ldr r0, _02254E08 ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov41_022548BC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	add r0, r4, #0
	bl ov41_02255170
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #5
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #1
	bl ov41_02254AE0
_02254E00:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02254E04: .word 0x0000066E
_02254E08: .word 0x00000663
	thumb_func_end ov41_02254D20

	thumb_func_start ov41_02254E0C
ov41_02254E0C: ; 0x02254E0C
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #3]
	cmp r1, #0
	beq _02254E20
	mov r1, #6
	bl ov41_02254AE0
	mov r0, #0
	pop {r4, pc}
_02254E20:
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _02254EAC
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02254E3A
	cmp r0, #1
	beq _02254E64
	cmp r0, #2
	beq _02254E6C
	b _02254EAC
_02254E3A:
	ldr r0, _02254EB0 ; =0x00000663
	bl Poketch_PlaySoundEffect
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	add r0, r4, #0
	bl ov41_022550D0
	add r0, r4, #0
	mov r1, #2
	bl ov41_02254AE0
	b _02254EAC
_02254E64:
	ldr r0, _02254EB4 ; =0x0000066E
	bl Poketch_PlaySoundEffect
	b _02254EAC
_02254E6C:
	ldr r0, _02254EB0 ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov41_022548BC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	add r0, r4, #0
	bl ov41_02255170
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #5
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #1
	bl ov41_02254AE0
_02254EAC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02254EB0: .word 0x00000663
_02254EB4: .word 0x0000066E
	thumb_func_end ov41_02254E0C

	thumb_func_start ov41_02254EB8
ov41_02254EB8: ; 0x02254EB8
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #3]
	cmp r1, #0
	beq _02254ECC
	mov r1, #6
	bl ov41_02254AE0
	mov r0, #0
	pop {r4, pc}
_02254ECC:
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _02254F52
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02254EE6
	cmp r0, #1
	beq _02254EEE
	cmp r0, #2
	beq _02254F20
	b _02254F52
_02254EE6:
	ldr r0, _02254F58 ; =0x0000066E
	bl Poketch_PlaySoundEffect
	b _02254F52
_02254EEE:
	ldr r0, _02254F5C ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov41_022548BC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	ldr r0, [r4, #8]
	mov r1, #7
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #5
	bl ov41_02254AE0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254F52
_02254F20:
	ldr r0, _02254F5C ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov41_022548BC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	ldr r0, [r4, #8]
	mov r1, #7
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #1
	bl ov41_02254AE0
_02254F52:
	mov r0, #0
	pop {r4, pc}
	nop
_02254F58: .word 0x0000066E
_02254F5C: .word 0x00000663
	thumb_func_end ov41_02254EB8

	thumb_func_start ov41_02254F60
ov41_02254F60: ; 0x02254F60
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #3]
	cmp r1, #0
	beq _02254F74
	mov r1, #6
	bl ov41_02254AE0
	mov r0, #0
	pop {r4, pc}
_02254F74:
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _0225500A
	mov r0, #0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02254F8E
	cmp r0, #1
	beq _02254FBA
	cmp r0, #2
	beq _02254FC2
	b _0225500A
_02254F8E:
	ldr r0, _02255010 ; =0x00000663
	bl Poketch_PlaySoundEffect
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl ov41_022548BC
	ldr r0, [r4, #8]
	mov r1, #6
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #4
	bl ov41_02254AE0
	b _0225500A
_02254FBA:
	ldr r0, _02255014 ; =0x0000066E
	bl Poketch_PlaySoundEffect
	b _0225500A
_02254FC2:
	ldr r0, _02255010 ; =0x00000663
	bl Poketch_PlaySoundEffect
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	bl ov41_022548BC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl ov41_022548BC
	add r0, r4, #0
	bl ov41_02255170
	ldr r0, [r4, #8]
	mov r1, #7
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #4
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #5
	bl ov41_022553A4
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov41_022553A4
	add r0, r4, #0
	mov r1, #1
	bl ov41_02254AE0
_0225500A:
	mov r0, #0
	pop {r4, pc}
	nop
_02255010: .word 0x00000663
_02255014: .word 0x0000066E
	thumb_func_end ov41_02254F60

	thumb_func_start ov41_02255018
ov41_02255018: ; 0x02255018
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02255028
	cmp r0, #1
	beq _02255038
	b _02255046
_02255028:
	ldr r0, [r4, #8]
	mov r1, #1
	bl ov41_022553A4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02255046
_02255038:
	ldr r0, [r4, #8]
	bl ov41_022553D4
	cmp r0, #0
	beq _02255046
	mov r0, #1
	pop {r4, pc}
_02255046:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov41_02255018

	thumb_func_start ov41_0225504C
ov41_0225504C: ; 0x0225504C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x48
	bl GetTimer3Count
	str r0, [r5, #0x68]
	str r1, [r5, #0x6c]
	mov r2, #0
	str r2, [r5, #0x70]
	add r0, r5, #0
	str r2, [r5, #0x74]
	mov r1, #1
	add r0, #0x88
	str r1, [r0]
	str r2, [r5, #0x78]
	str r2, [r5, #0x7c]
	mov r2, #2
	ldrsb r3, [r4, r2]
	mov r0, #3
	ldrsb r0, [r4, r0]
	add r6, r3, #0
	ldrsb r3, [r4, r1]
	mov r1, #0x48
	mov r2, #0xa
	mul r6, r2
	ldrsb r1, [r5, r1]
	add r0, r0, r6
	mul r2, r1
	add r2, r3, r2
	mov r1, #0x3c
	mul r1, r2
	add r2, r0, r1
	add r0, r5, #0
	add r0, #0x80
	str r2, [r0]
	add r0, r5, #0
	asr r1, r2, #0x1f
	add r0, #0x84
	str r1, [r0]
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0x80
	add r2, #0x84
	ldr r1, [r1]
	ldr r2, [r2]
	add r0, r5, #0
	bl ov41_02255190
	add r0, r5, #0
	add r0, #0x80
	add r5, #0x84
	ldr r0, [r0]
	ldr r1, [r5]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov41_0225504C

	thumb_func_start ov41_022550BC
ov41_022550BC: ; 0x022550BC
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	add r0, #0x88
	str r1, [r0]
	bl GetTimer3Count
	str r0, [r4, #0x70]
	str r1, [r4, #0x74]
	pop {r4, pc}
	thumb_func_end ov41_022550BC

	thumb_func_start ov41_022550D0
ov41_022550D0: ; 0x022550D0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	bl GetTimer3Count
	add r5, r4, #0
	add r5, #0x68
	ldr r7, [r4, #0x70]
	ldr r2, [r4, #0x68]
	ldr r6, [r4, #0x74]
	sub r0, r0, r7
	sbc r1, r6
	ldr r3, [r5, #4]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0x68]
	str r3, [r5, #4]
	mov r0, #1
	add r4, #0x88
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov41_022550D0

	thumb_func_start ov41_022550F8
ov41_022550F8: ; 0x022550F8
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	bne _02255104
	mov r0, #1
	bx lr
_02255104:
	mov r0, #0
	bx lr
	thumb_func_end ov41_022550F8

	thumb_func_start ov41_02255108
ov41_02255108: ; 0x02255108
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	beq _0225516A
	bl GetTimer3Count
	ldr r3, [r4, #0x68]
	ldr r2, [r4, #0x6c]
	sub r0, r0, r3
	sbc r1, r2
	bl Timer3CountToSeconds
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x80
	add r6, r1, #0
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x84
	ldr r2, [r0]
	sub r0, r5, r1
	mov ip, r6
	mov r0, ip
	sbc r0, r2
	blo _02255148
	add r0, r4, #0
	bl ov41_02255170
	mov r0, #1
	pop {r4, r5, r6, pc}
_02255148:
	ldr r3, [r4, #0x78]
	ldr r0, [r4, #0x7c]
	eor r3, r5
	eor r0, r6
	orr r0, r3
	beq _02255166
	add r0, r4, #0
	sub r1, r1, r5
	sbc r2, r6
	bl ov41_02255190
	str r5, [r4, #0x78]
	str r6, [r4, #0x7c]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02255166:
	mov r0, #0
	pop {r4, r5, r6, pc}
_0225516A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov41_02255108

	thumb_func_start ov41_02255170
ov41_02255170: ; 0x02255170
	add r1, r0, #0
	mov r2, #0
	add r1, #0x88
	str r2, [r1]
	add r1, r0, #0
	add r1, #0x48
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0x49
	strb r2, [r1]
	add r1, r0, #0
	add r1, #0x4a
	strb r2, [r1]
	add r0, #0x4b
	strb r2, [r0]
	bx lr
	thumb_func_end ov41_02255170

	thumb_func_start ov41_02255190
ov41_02255190: ; 0x02255190
	push {r3, r4, r5, r6}
	add r3, r0, #0
	ldr r0, _02255240 ; =0x04000280
	mov r4, #1
	strh r4, [r0]
	add r4, r0, #0
	add r4, #0x10
	str r1, [r4]
	str r2, [r4, #4]
	add r1, r0, #0
	mov r4, #0x3c
	add r1, #0x18
	mov r2, #0
	str r4, [r1]
	str r2, [r1, #4]
	lsr r1, r0, #0xb
_022551B0:
	ldrh r2, [r0]
	tst r2, r1
	bne _022551B0
	ldr r0, _02255244 ; =0x040002A0
	ldr r6, _02255240 ; =0x04000280
	ldr r0, [r0]
	lsr r1, r6, #0xb
_022551BE:
	ldrh r2, [r6]
	tst r2, r1
	bne _022551BE
	ldr r5, _02255248 ; =0x040002A8
	mov r4, #0
	ldr r2, [r5]
	add r1, r5, #0
	strh r4, [r6]
	sub r1, #0x18
	str r0, [r1]
	mov r0, #0xa
	sub r5, #0x10
	str r0, [r5]
	str r4, [r5, #4]
	ldr r4, _02255240 ; =0x04000280
	lsr r0, r4, #0xb
_022551DE:
	ldrh r1, [r4]
	tst r1, r0
	bne _022551DE
	ldr r0, _02255244 ; =0x040002A0
	ldr r1, [r0]
	add r0, r3, #0
	add r0, #0x48
	strb r1, [r0]
	ldr r1, _02255240 ; =0x04000280
	lsr r0, r1, #0xb
_022551F2:
	ldrh r4, [r1]
	tst r4, r0
	bne _022551F2
	ldr r0, _02255248 ; =0x040002A8
	add r4, r3, #0
	ldr r5, [r0]
	add r4, #0x49
	strb r5, [r4]
	mov r4, #0
	strh r4, [r1]
	add r1, r0, #0
	sub r1, #0x18
	str r2, [r1]
	mov r1, #0xa
	sub r0, #0x10
	str r1, [r0]
	ldr r2, _02255240 ; =0x04000280
	str r4, [r0, #4]
	lsr r0, r2, #0xb
_02255218:
	ldrh r1, [r2]
	tst r1, r0
	bne _02255218
	ldr r0, _02255244 ; =0x040002A0
	ldr r2, _02255240 ; =0x04000280
	ldr r1, [r0]
	add r0, r3, #0
	add r0, #0x4a
	strb r1, [r0]
	lsr r0, r2, #0xb
_0225522C:
	ldrh r1, [r2]
	tst r1, r0
	bne _0225522C
	ldr r0, _02255248 ; =0x040002A8
	add r3, #0x4b
	ldr r0, [r0]
	strb r0, [r3]
	pop {r3, r4, r5, r6}
	bx lr
	nop
_02255240: .word 0x04000280
_02255244: .word 0x040002A0
_02255248: .word 0x040002A8
	thumb_func_end ov41_02255190

	thumb_func_start ov41_0225524C
ov41_0225524C: ; 0x0225524C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0xac
	bl AllocFromHeap
	add r4, r0, #0
	beq _02255288
	add r0, #8
	mov r1, #8
	bl ov20_022536F4
	str r5, [r4]
	bl ov20_02252D34
	str r0, [r4, #4]
	bl ov20_02252D24
	str r0, [r4, #0x30]
	add r0, r4, #0
	add r1, r5, #0
	bl ov41_022552A0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02255288
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02255288:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end ov41_0225524C

	thumb_func_start ov41_0225528C
ov41_0225528C: ; 0x0225528C
	push {r4, lr}
	add r4, r0, #0
	beq _0225529C
	bl ov41_02255374
	add r0, r4, #0
	bl FreeToHeap
_0225529C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov41_0225528C

	thumb_func_start ov41_022552A0
ov41_022552A0: ; 0x022552A0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r7, r0, #0
	str r1, [sp, #0xc]
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #2
	bl GfGfxLoader_LoadWholePalette
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	mov r3, #0xa
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x5e
	lsl r3, r3, #8
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x78
	mov r1, #0xc
	mov r2, #0x5c
	mov r3, #0x5d
	bl ov20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x8c
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl ov20_02253FBC
	add r0, r7, #0
	str r0, [sp, #0x14]
	add r0, #0x78
	str r0, [sp, #0x14]
	add r0, r7, #0
	str r0, [sp, #0x10]
	add r0, #0x8c
	ldr r6, _02255370 ; =ov41_02255864
	mov r4, #0
	add r5, r7, #0
	str r0, [sp, #0x10]
_0225530E:
	cmp r4, #0xd
	blt _02255324
	cmp r4, #0x10
	bgt _02255324
	ldr r0, [r7, #0x30]
	ldr r2, [sp, #0x10]
	add r1, r6, #0
	bl ov20_02253E74
	str r0, [r5, #0x34]
	b _02255336
_02255324:
	ldr r0, [r7, #0x30]
	ldr r2, [sp, #0x14]
	add r1, r6, #0
	bl ov20_02253E74
	mov r1, #0x50
	str r0, [r5, #0x34]
	bl ov20_02253FA4
_02255336:
	add r4, r4, #1
	add r6, #0x10
	add r5, r5, #4
	cmp r4, #0x11
	blt _0225530E
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl ov41_022556D4
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl ov41_02255714
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #8]
	cmp r0, #0
	bne _0225535C
	mov r1, #1
	b _0225535E
_0225535C:
	mov r1, #0
_0225535E:
	add r0, r7, #0
	bl ov41_02255744
	mov r0, #0
	add r7, #0xa8
	str r0, [r7]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255370: .word ov41_02255864
	thumb_func_end ov41_022552A0

	thumb_func_start ov41_02255374
ov41_02255374: ; 0x02255374
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_0225537C:
	ldr r1, [r5, #0x34]
	cmp r1, #0
	beq _02255388
	ldr r0, [r6, #0x30]
	bl ov20_02253F14
_02255388:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x11
	blt _0225537C
	add r0, r6, #0
	add r0, #0x78
	bl ov20_02254014
	add r6, #0x8c
	add r0, r6, #0
	bl ov20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov41_02255374

	thumb_func_start ov41_022553A4
ov41_022553A4: ; 0x022553A4
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _022553C4 ; =ov41_022557F8
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_022553C4: .word ov41_022557F8
	thumb_func_end ov41_022553A4

	thumb_func_start ov41_022553C8
ov41_022553C8: ; 0x022553C8
	ldr r3, _022553D0 ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_022553D0: .word ov20_02253794
	thumb_func_end ov41_022553C8

	thumb_func_start ov41_022553D4
ov41_022553D4: ; 0x022553D4
	ldr r3, _022553DC ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_022553DC: .word ov20_022537B8
	thumb_func_end ov41_022553D4

	thumb_func_start ov41_022553E0
ov41_022553E0: ; 0x022553E0
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov41_022553E0

	thumb_func_start ov41_022553F4
ov41_022553F4: ; 0x022553F4
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _022554CC ; =ov41_022557DC
	mov r1, #6
	mov r3, #0
	bl InitBgFromTemplate
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x5b
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x5a
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r4, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _022554D0 ; =0x04001000
	ldr r0, _022554D4 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	ldr r1, [r4]
	ldr r0, [r1, #0xc]
	cmp r0, #1
	beq _02255488
	cmp r0, #2
	beq _0225547E
	cmp r0, #3
	beq _0225549A
	b _022554C0
_0225547E:
	add r0, r4, #0
	mov r1, #6
	bl ov41_022553A4
	b _022554C0
_02255488:
	ldr r0, [r4, #0x34]
	mov r1, #3
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl ov20_02253F28
	b _022554C0
_0225549A:
	ldr r0, [r1, #0x10]
	cmp r0, #0
	ldr r0, [r4, #0x34]
	beq _022554B2
	mov r1, #2
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl ov20_02253F28
	b _022554C0
_022554B2:
	mov r1, #3
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl ov20_02253F28
_022554C0:
	add r0, r5, #0
	bl ov41_022553E0
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_022554CC: .word ov41_022557DC
_022554D0: .word 0x04001000
_022554D4: .word 0xFFFFE0FF
	thumb_func_end ov41_022553F4

	thumb_func_start ov41_022554D8
ov41_022554D8: ; 0x022554D8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _022554FA
	cmp r0, #1
	beq _02255508
	pop {r3, r4, r5, pc}
_022554FA:
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
	add r0, r5, #0
	bl ov20_022538B0
_02255508:
	add r0, r4, #0
	mov r1, #6
	bl ov41_022553C8
	cmp r0, #0
	beq _02255522
	ldr r0, [r4, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r5, #0
	bl ov41_022553E0
_02255522:
	pop {r3, r4, r5, pc}
	thumb_func_end ov41_022554D8

	thumb_func_start ov41_02255524
ov41_02255524: ; 0x02255524
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r0, r4, #0
	mov r1, #0
	bl ov41_02255744
	ldr r0, [r4, #0x34]
	mov r1, #2
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl ov20_02253F28
	add r0, r5, #0
	bl ov41_022553E0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_02255524

	thumb_func_start ov41_02255558
ov41_02255558: ; 0x02255558
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r0, r4, #0
	mov r1, #1
	bl ov41_02255744
	ldr r0, [r4, #0x34]
	mov r1, #3
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl ov20_02253F28
	add r0, r5, #0
	bl ov41_022553E0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_02255558

	thumb_func_start ov41_0225558C
ov41_0225558C: ; 0x0225558C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r1, r0, #0
	add r0, r4, #0
	bl ov41_022556D4
	add r0, r5, #0
	bl ov41_022553E0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_0225558C

	thumb_func_start ov41_022555B0
ov41_022555B0: ; 0x022555B0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r1, r0, #0
	add r0, r4, #0
	bl ov41_02255714
	add r0, r5, #0
	bl ov41_022553E0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_022555B0

	thumb_func_start ov41_022555D4
ov41_022555D4: ; 0x022555D4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _022555F6
	cmp r0, #1
	beq _0225561A
	pop {r3, r4, r5, pc}
_022555F6:
	ldr r0, [r4, #0x34]
	mov r1, #2
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl ov20_02253F28
	add r0, r4, #0
	mov r1, #0
	add r0, #0xa4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xa0
	str r1, [r0]
	add r0, r5, #0
	bl ov20_022538B0
_0225561A:
	add r0, r4, #0
	add r0, #0xa0
	ldr r0, [r0]
	cmp r0, #0
	beq _0225562C
	add r0, r5, #0
	bl ov41_022553E0
	pop {r3, r4, r5, pc}
_0225562C:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xa4
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	cmp r0, #8
	blo _0225568A
	add r0, r4, #0
	add r0, #0xa8
	ldr r1, [r0]
	mov r0, #1
	eor r1, r0
	add r0, r4, #0
	add r0, #0xa8
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	cmp r0, #0
	ldr r0, [r4, #0x34]
	beq _02255670
	mov r1, #2
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl ov20_02253F28
	b _0225567E
_02255670:
	mov r1, #3
	bl ov20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl ov20_02253F28
_0225567E:
	ldr r0, _0225568C ; =0x00000677
	bl Poketch_PlaySoundEffect
	mov r0, #0
	add r4, #0xa4
	str r0, [r4]
_0225568A:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225568C: .word 0x00000677
	thumb_func_end ov41_022555D4

	thumb_func_start ov41_02255690
ov41_02255690: ; 0x02255690
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov20_022538A4
	add r0, r5, #0
	bl ov20_022538AC
	cmp r0, #0
	beq _022556B2
	cmp r0, #1
	beq _022556C0
	pop {r3, r4, r5, pc}
_022556B2:
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
	add r0, r5, #0
	bl ov20_022538B0
_022556C0:
	add r0, r4, #0
	mov r1, #6
	bl ov41_022553C8
	cmp r0, #0
	beq _022556D2
	add r0, r5, #0
	bl ov41_022553E0
_022556D2:
	pop {r3, r4, r5, pc}
	thumb_func_end ov41_02255690

	thumb_func_start ov41_022556D4
ov41_022556D4: ; 0x022556D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #4]
	cmp r0, #0
	beq _022556E4
	mov r1, #6
	b _022556E6
_022556E4:
	mov r1, #5
_022556E6:
	ldr r0, [r5, #0x3c]
	bl ov20_02253F28
	ldrb r0, [r4, #5]
	cmp r0, #0
	beq _022556F6
	mov r1, #8
	b _022556F8
_022556F6:
	mov r1, #7
_022556F8:
	ldr r0, [r5, #0x40]
	bl ov20_02253F28
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _02255708
	mov r1, #0xa
	b _0225570A
_02255708:
	mov r1, #9
_0225570A:
	ldr r0, [r5, #0x44]
	bl ov20_02253F28
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_022556D4

	thumb_func_start ov41_02255714
ov41_02255714: ; 0x02255714
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	ldrsb r1, [r4, r1]
	ldr r0, [r5, #0x68]
	bl ov20_02253F28
	mov r1, #1
	ldrsb r1, [r4, r1]
	ldr r0, [r5, #0x6c]
	bl ov20_02253F28
	mov r1, #2
	ldrsb r1, [r4, r1]
	ldr r0, [r5, #0x70]
	bl ov20_02253F28
	mov r1, #3
	ldrsb r1, [r4, r1]
	ldr r0, [r5, #0x74]
	bl ov20_02253F28
	pop {r3, r4, r5, pc}
	thumb_func_end ov41_02255714

	thumb_func_start ov41_02255744
ov41_02255744: ; 0x02255744
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x48]
	add r4, r1, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x4c]
	add r1, r4, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x50]
	add r1, r4, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x54]
	add r1, r4, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x58]
	add r1, r4, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x5c]
	add r1, r4, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x60]
	add r1, r4, #0
	bl ov20_02253F78
	ldr r0, [r5, #0x64]
	add r1, r4, #0
	bl ov20_02253F78
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov41_02255744

	thumb_func_start ov41_0225578C
ov41_0225578C: ; 0x0225578C
	add r0, #0xa8
	ldr r0, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov41_0225578C

	.section .rodata

	.global ov41_02255794
ov41_02255794: ; 0x02255794
	.word ov41_02254B58, ov41_02254B98, ov41_02254D20, ov41_02254E0C
	.word ov41_02254EB8, ov41_02254F60, ov41_02255018

	.global ov41_022557B0
ov41_022557B0: ; 0x022557B0
	.byte 0x90, 0xB0, 0x10, 0x50
	.byte 0x90, 0xB0, 0x50, 0x90, 0x90, 0xB0, 0x90, 0xD0, 0x50, 0x60, 0x48, 0x58, 0x50, 0x60, 0x58, 0x68
	.byte 0x80, 0x90, 0x48, 0x58, 0x80, 0x90, 0x58, 0x68, 0x50, 0x60, 0x78, 0x88, 0x50, 0x60, 0x88, 0x98
	.byte 0x80, 0x90, 0x78, 0x88, 0x80, 0x90, 0x88, 0x98

	.global ov41_022557DC
ov41_022557DC: ; 0x022557DC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov41_022557F8
ov41_022557F8: ; 0x022557F8
	.word 0x00, ov41_022553F4, 0x00
	.word 0x01, ov41_022554D8, 0x00
	.word 0x02, ov41_02255524, 0x00
	.word 0x03, ov41_02255558, 0x00
	.word 0x04, ov41_0225558C, 0x00
	.word 0x05, ov41_022555B0, 0x00
	.word 0x06, ov41_022555D4, 0x00
	.word 0x07, ov41_02255690, 0x00
	.word 0x00, 0x00000000, 0x00

	.global ov41_02255864
ov41_02255864: ; 0x02255864
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x03, 0x00, 0x02, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x0B, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x07, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0x05, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x00, 0x80, 0x05, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x05, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x80, 0x05, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0x08, 0x00, 0x04, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x00, 0x80, 0x08, 0x00, 0x04, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x08, 0x00, 0x04, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x80, 0x08, 0x00, 0x04, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
