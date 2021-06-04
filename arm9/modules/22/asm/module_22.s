	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD22_02254854
MOD22_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x68
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r2, [sp]
	add r1, r7, #0
	bl MOD22_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD22_0225497C
	add r1, r4, #0
	mov r2, #1
	str r6, [r4, #0x64]
	bl FUN_0200CA44
	cmp r0, #0
	beq _02254892
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
_02254898: .word MOD22_0225497C
	thumb_func_end MOD22_02254854

	thumb_func_start MOD22_0225489C
MOD22_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	str r2, [r5, #8]
	add r0, r2, #0
	add r1, #0x38
	mov r2, #0x24
	bl FUN_02089418
	cmp r0, #0
	beq _022548F0
	add r0, r5, #0
	add r0, #0x4c
	ldmia r0!, {r2, r3}
	add r0, r5, #0
	add r0, #0xc
	stmia r0!, {r2, r3}
	add r0, r5, #0
	add r0, #0x54
	ldmia r0!, {r2, r3}
	add r0, r5, #0
	add r0, #0x14
	stmia r0!, {r2, r3}
	ldr r0, [r5, #0x3c]
	str r0, [r5, #0x30]
	ldr r0, [r5, #0x40]
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x44]
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x48]
	str r0, [r5, #0x24]
	ldr r0, [r5, #0x38]
	str r0, [r5, #0x1c]
	cmp r0, #0
	beq _022548EA
	mov r0, #2
	str r0, [r5, #0x34]
	b _022548FA
_022548EA:
	mov r0, #0
	str r0, [r5, #0x34]
	b _022548FA
_022548F0:
	add r0, r5, #0
	bl MOD22_02254CE4
	mov r0, #0
	str r0, [r5, #0x34]
_022548FA:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x60
	add r1, #0x1c
	add r2, r4, #0
	bl MOD22_02254E8C
	cmp r0, #0
	beq _02254926
	mov r1, #0
	strb r1, [r5]
	strb r1, [r5, #1]
	ldrb r0, [r5]
	strb r0, [r5, #3]
	add r0, r5, #0
	strb r1, [r5, #2]
	bl MOD22_02254C88
	cmp r0, #0
	beq _02254926
	mov r0, #1
	pop {r3, r4, r5, pc}
_02254926:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD22_0225489C

	thumb_func_start MOD22_0225492C
MOD22_0225492C: ; 0x0225492C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xc
	ldmia r0!, {r2, r3}
	add r0, r4, #0
	add r0, #0x4c
	stmia r0!, {r2, r3}
	add r0, r4, #0
	add r0, #0x14
	ldmia r0!, {r2, r3}
	add r0, r4, #0
	add r0, #0x54
	stmia r0!, {r2, r3}
	ldr r0, [r4, #0x30]
	add r1, r4, #0
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x2c]
	add r1, #0x38
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x28]
	mov r2, #0x24
	str r0, [r4, #0x44]
	ldr r0, [r4, #0x24]
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x1c]
	str r0, [r4, #0x38]
	ldr r0, [r4, #8]
	bl FUN_020893F0
	add r0, r4, #0
	bl MOD22_02254CD4
	ldr r0, [r4, #0x60]
	bl MOD22_02254F10
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_0225492C

	thumb_func_start MOD22_0225497C
MOD22_0225497C: ; 0x0225497C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #6
	bhs _022549D2
	ldrb r0, [r4, #2]
	cmp r0, #0
	beq _0225499E
	cmp r1, #5
	beq _0225499E
	add r0, r4, #0
	mov r1, #5
	bl MOD22_022549E0
	mov r0, #0
	strb r0, [r4, #2]
_0225499E:
	ldr r0, [r4, #0x64]
	ldr r1, [r4, #0x5c]
	bl MOD20_02252C14
	add r1, r4, #0
	add r0, r4, #0
	add r1, #0x1c
	bl MOD22_02254D58
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022549D4 ; =MOD22_0225561C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _022549D2
	add r0, r4, #0
	bl MOD22_0225492C
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x64]
	bl MOD20_022529A0
_022549D2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022549D4: .word MOD22_0225561C
	thumb_func_end MOD22_0225497C

	thumb_func_start MOD22_022549D8
MOD22_022549D8: ; 0x022549D8
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD22_022549D8

	thumb_func_start MOD22_022549E0
MOD22_022549E0: ; 0x022549E0
	ldrb r2, [r0]
	strb r2, [r0, #3]
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _022549EE
	strb r1, [r0]
	b _022549F6
_022549EE:
	mov r1, #5
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #2]
_022549F6:
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	thumb_func_end MOD22_022549E0

	thumb_func_start MOD22_022549FC
MOD22_022549FC: ; 0x022549FC
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A0C
	cmp r0, #1
	beq _02254A1C
	b _02254A46
_02254A0C:
	ldr r0, [r4, #0x60]
	mov r1, #0
	bl MOD22_02255048
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A46
_02254A1C:
	ldr r0, [r4, #0x60]
	mov r1, #0
	bl MOD22_0225506C
	cmp r0, #0
	beq _02254A46
	ldr r0, [r4, #0x64]
	bl MOD20_0225298C
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _02254A3E
	add r0, r4, #0
	mov r1, #2
	bl MOD22_022549E0
	b _02254A46
_02254A3E:
	add r0, r4, #0
	mov r1, #1
	bl MOD22_022549E0
_02254A46:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_022549FC

	thumb_func_start MOD22_02254A4C
MOD22_02254A4C: ; 0x02254A4C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A5C
	cmp r0, #1
	beq _02254A74
	b _02254AC8
_02254A5C:
	ldrb r0, [r4, #4]
	cmp r0, #1
	bne _02254AC8
	mov r1, #1
	str r1, [r4, #0x34]
	ldr r0, [r4, #0x60]
	bl MOD22_02255048
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AC8
_02254A74:
	ldrb r0, [r4, #4]
	cmp r0, #2
	beq _02254A84
	cmp r0, #3
	beq _02254A98
	cmp r0, #5
	beq _02254AB4
	b _02254AC8
_02254A84:
	mov r0, #0
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	ldrb r0, [r4, #1]
	sub r0, r0, #1
	strb r0, [r4, #1]
	b _02254AC8
_02254A98:
	mov r0, #2
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	bl MOD22_02254D00
	add r0, r4, #0
	mov r1, #2
	bl MOD22_022549E0
	b _02254AC8
_02254AB4:
	mov r0, #3
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #3
	bl MOD22_022549E0
_02254AC8:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD22_02254A4C

	thumb_func_start MOD22_02254ACC
MOD22_02254ACC: ; 0x02254ACC
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254ADC
	cmp r1, #1
	beq _02254AFA
	b _02254B4A
_02254ADC:
	ldrb r1, [r4, #4]
	cmp r1, #1
	bne _02254B4A
	mov r1, #1
	str r1, [r4, #0x34]
	bl MOD22_02254D44
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B4A
_02254AFA:
	ldrb r0, [r4, #4]
	cmp r0, #2
	beq _02254B0A
	cmp r0, #3
	beq _02254B20
	cmp r0, #5
	beq _02254B36
	b _02254B4A
_02254B0A:
	mov r0, #0
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #1
	bl MOD22_022549E0
	b _02254B4A
_02254B20:
	mov r0, #0
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #1
	bl MOD22_022549E0
	b _02254B4A
_02254B36:
	mov r0, #3
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #3
	bl MOD22_022549E0
_02254B4A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_02254ACC

	thumb_func_start MOD22_02254B50
MOD22_02254B50: ; 0x02254B50
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #4]
	cmp r1, #2
	beq _02254B84
	cmp r1, #3
	beq _02254B64
	cmp r1, #6
	beq _02254B9A
	b _02254BAE
_02254B64:
	ldrb r1, [r4, #3]
	cmp r1, #1
	bne _02254B84
	bl MOD22_02254D00
	mov r0, #2
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #2
	bl MOD22_022549E0
	b _02254BAE
_02254B84:
	mov r0, #0
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #1
	bl MOD22_022549E0
	b _02254BAE
_02254B9A:
	mov r0, #4
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #4
	bl MOD22_022549E0
_02254BAE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_02254B50

	thumb_func_start MOD22_02254BB4
MOD22_02254BB4: ; 0x02254BB4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #3
	bhi _02254C4A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254BCA: ; jump table
	.short _02254BD2 - _02254BCA - 2 ; case 0
	.short _02254BDC - _02254BCA - 2 ; case 1
	.short _02254C00 - _02254BCA - 2 ; case 2
	.short _02254C2A - _02254BCA - 2 ; case 3
_02254BD2:
	mov r0, #0
	strh r0, [r4, #6]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
_02254BDC:
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	ldrh r0, [r4, #6]
	cmp r0, #0x5a
	blo _02254C4A
	mov r0, #5
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	mov r0, #0
	strh r0, [r4, #6]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C4A
_02254C00:
	ldrh r0, [r4, #6]
	add r0, r0, #1
	strh r0, [r4, #6]
	ldrh r0, [r4, #6]
	cmp r0, #0x3c
	blo _02254C4A
	mov r0, #6
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	bl MOD22_02254CE4
	mov r0, #0
	strh r0, [r4, #6]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C4A
_02254C2A:
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_0225506C
	cmp r0, #0
	beq _02254C4A
	mov r0, #0
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #1
	bl MOD22_02255048
	add r0, r4, #0
	mov r1, #1
	bl MOD22_022549E0
_02254C4A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_02254BB4

	thumb_func_start MOD22_02254C50
MOD22_02254C50: ; 0x02254C50
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254C60
	cmp r0, #1
	beq _02254C74
	b _02254C82
_02254C60:
	mov r0, #7
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x60]
	mov r1, #3
	bl MOD22_02255048
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C82
_02254C74:
	ldr r0, [r4, #0x60]
	bl MOD22_02255078
	cmp r0, #0
	beq _02254C82
	mov r0, #1
	pop {r4, pc}
_02254C82:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_02254C50

	thumb_func_start MOD22_02254C88
MOD22_02254C88: ; 0x02254C88
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254CCC ; =MOD22_02255618
	ldr r2, _02254CD0 ; =MOD22_02254CE0
	mov r1, #1
	add r3, r4, #0
	bl MOD20_02254130
	str r0, [r4, #0x5c]
	cmp r0, #0
	beq _02254CC4
	mov r1, #0
	add r2, r1, #0
	mov r3, #0xf
	bl MOD20_022542AC
	ldr r0, [r4, #0x5c]
	mov r1, #0
	mov r2, #1
	mov r3, #0x4b
	bl MOD20_022542AC
	mov r0, #0
	strb r0, [r4, #4]
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_02254CC4:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_02254CCC: .word MOD22_02255618
_02254CD0: .word MOD22_02254CE0
	thumb_func_end MOD22_02254C88

	thumb_func_start MOD22_02254CD4
MOD22_02254CD4: ; 0x02254CD4
	ldr r3, _02254CDC ; =MOD20_02254198
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_02254CDC: .word MOD20_02254198
	thumb_func_end MOD22_02254CD4

	thumb_func_start MOD22_02254CE0
MOD22_02254CE0: ; 0x02254CE0
	strb r1, [r3, #4]
	bx lr
	thumb_func_end MOD22_02254CE0

	thumb_func_start MOD22_02254CE4
MOD22_02254CE4: ; 0x02254CE4
	mov r2, #0
	str r2, [r0, #0x1c]
	mov r1, #1
	str r1, [r0, #0x20]
	str r2, [r0, #0x24]
	str r2, [r0, #0x28]
	str r2, [r0, #0x2c]
	str r2, [r0, #0x30]
	str r2, [r0, #0xc]
	str r2, [r0, #0x10]
	str r2, [r0, #0x14]
	str r2, [r0, #0x18]
	bx lr
	.align 2, 0
	thumb_func_end MOD22_02254CE4

	thumb_func_start MOD22_02254D00
MOD22_02254D00: ; 0x02254D00
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r3, [r4, #0xc]
	mov r0, #0
	ldr r2, [r4, #0x10]
	mov r1, #0
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _02254D32
	bl GetTimer3Count
	add r5, r4, #0
	add r5, #0xc
	ldr r7, [r4, #0x14]
	ldr r2, [r4, #0xc]
	ldr r6, [r4, #0x18]
	sub r0, r0, r7
	sbc r1, r6
	ldr r3, [r5, #4]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	str r3, [r5, #4]
	b _02254D3A
_02254D32:
	bl GetTimer3Count
	str r0, [r4, #0xc]
	str r1, [r4, #0x10]
_02254D3A:
	mov r0, #1
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x20]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD22_02254D00

	thumb_func_start MOD22_02254D44
MOD22_02254D44: ; 0x02254D44
	push {r4, lr}
	add r4, r0, #0
	bl GetTimer3Count
	str r0, [r4, #0x14]
	str r1, [r4, #0x18]
	mov r0, #0
	str r0, [r4, #0x1c]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_02254D44

	thumb_func_start MOD22_02254D58
MOD22_02254D58: ; 0x02254D58
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _02254D66
	b _02254E7C
_02254D66:
	bl GetTimer3Count
	ldr r3, [r5, #0xc]
	ldr r2, [r5, #0x10]
	sub r0, r0, r3
	sbc r1, r2
	bl Timer3CountToMilliSeconds
	ldr r2, _02254E80 ; =0x04000280
	mov r3, #1
	strh r3, [r2]
	add r3, r2, #0
	add r3, #0x10
	str r0, [r3]
	str r1, [r3, #4]
	mov r3, #0xfa
	add r0, r2, #0
	lsl r3, r3, #2
	add r0, #0x18
	mov r1, #0
	str r3, [r0]
	str r1, [r0, #4]
	lsr r0, r2, #0xb
_02254D94:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254D94
	ldr r0, _02254E84 ; =0x040002A0
	add r3, r0, #0
	ldr r6, [r0]
	ldr r5, [r0, #4]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254DA6:
	ldrh r1, [r3]
	tst r1, r0
	bne _02254DA6
	ldr r2, _02254E88 ; =0x040002A8
	mov r0, #1
	ldr r1, [r2]
	ldr r7, [r2, #4]
	strh r0, [r3]
	add r0, r2, #0
	sub r0, #0x18
	str r1, [r0]
	str r7, [r0, #4]
	mov r1, #0xa
	sub r2, #0x10
	str r1, [r2]
	mov r0, #0
	ldr r1, _02254E80 ; =0x04000280
	str r0, [r2, #4]
	lsr r0, r1, #0xb
_02254DCC:
	ldrh r2, [r1]
	tst r2, r0
	bne _02254DCC
	ldr r0, _02254E84 ; =0x040002A0
	ldr r2, [r0]
	str r2, [r4, #8]
	mov r2, #1
	strh r2, [r1]
	add r1, r0, #0
	sub r1, #0x10
	str r6, [r1]
	str r5, [r1, #4]
	mov r2, #0x3c
	sub r0, #8
	str r2, [r0]
	mov r1, #0
	ldr r2, _02254E80 ; =0x04000280
	str r1, [r0, #4]
	lsr r0, r2, #0xb
_02254DF2:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254DF2
	ldr r0, _02254E84 ; =0x040002A0
	add r1, r0, #0
	ldr r3, [r0]
	ldr r2, [r0, #4]
	sub r1, #0x20
	lsr r0, r0, #0xb
_02254E04:
	ldrh r5, [r1]
	tst r5, r0
	bne _02254E04
	ldr r0, _02254E88 ; =0x040002A8
	ldr r5, [r0]
	str r5, [r4, #0xc]
	mov r5, #1
	strh r5, [r1]
	add r1, r0, #0
	sub r1, #0x18
	str r3, [r1]
	str r2, [r1, #4]
	mov r2, #0x3c
	sub r0, #0x10
	str r2, [r0]
	mov r1, #0
	ldr r2, _02254E80 ; =0x04000280
	str r1, [r0, #4]
	lsr r0, r2, #0xb
_02254E2A:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254E2A
	ldr r0, _02254E84 ; =0x040002A0
	add r2, r0, #0
	ldr r5, [r0]
	ldr r3, [r0, #4]
	sub r2, #0x20
	lsr r0, r0, #0xb
_02254E3C:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254E3C
	ldr r1, _02254E88 ; =0x040002A8
	mov r6, #0x18
	ldr r0, [r1]
	str r0, [r4, #0x10]
	mov r0, #0
	sub r6, r5, r6
	mov ip, r3
	mov r6, ip
	sbc r6, r0
	blo _02254E7A
	mov r0, #1
	strh r0, [r2]
	add r0, r1, #0
	sub r0, #0x18
	str r5, [r0]
	str r3, [r0, #4]
	mov r2, #0x18
	sub r1, #0x10
	str r2, [r1]
	mov r0, #0
	ldr r2, _02254E80 ; =0x04000280
	str r0, [r1, #4]
	lsr r0, r2, #0xb
_02254E70:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254E70
	ldr r0, _02254E88 ; =0x040002A8
	ldr r5, [r0]
_02254E7A:
	str r5, [r4, #0x14]
_02254E7C:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254E80: .word 0x04000280
_02254E84: .word 0x040002A0
_02254E88: .word 0x040002A8
	thumb_func_end MOD22_02254D58

	thumb_func_start MOD22_02254E8C
MOD22_02254E8C: ; 0x02254E8C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x88
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254F08
	str r6, [r4]
	bl MOD20_02252D24
	str r0, [r4, #0x5c]
	mov r0, #8
	bl FUN_02016B94
	str r0, [r4, #4]
	cmp r0, #0
	bne _02254EBA
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_02254EBA:
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x34
	mov r1, #0xc
	mov r2, #0x12
	mov r3, #0x13
	bl MOD20_02253FBC
	cmp r0, #0
	beq _02254F08
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl MOD20_02253FBC
	cmp r0, #0
	beq _02254F00
	add r0, r4, #0
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	add r0, r4, #0
	mov r1, #0
	add r0, #0x84
	str r1, [r0]
	add sp, #4
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02254F00:
	add r4, #0x34
	add r0, r4, #0
	bl MOD20_02254014
_02254F08:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD22_02254E8C

	thumb_func_start MOD22_02254F10
MOD22_02254F10: ; 0x02254F10
	push {r4, lr}
	add r4, r0, #0
	beq _02254F26
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02254F20
	bl FreeToHeap
_02254F20:
	add r0, r4, #0
	bl FreeToHeap
_02254F26:
	pop {r4, pc}
	thumb_func_end MOD22_02254F10

	thumb_func_start MOD22_02254F28
MOD22_02254F28: ; 0x02254F28
	ldr r3, _02254F30 ; =MOD22_02254F34
	add r0, r1, #0
	bx r3
	nop
_02254F30: .word MOD22_02254F34
	thumb_func_end MOD22_02254F28

	thumb_func_start MOD22_02254F34
MOD22_02254F34: ; 0x02254F34
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r2, _0225503C ; =0x04000280
	ldr r0, [r0, #0x14]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254F50:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254F50
	ldr r0, _02255040 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254F60:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254F60
	ldr r0, _02255044 ; =0x040002A8
	ldr r5, [r0]
	ldr r0, [r4, #0x60]
	bl MOD20_02253F28
	ldr r0, [r4, #0x64]
	add r1, r5, #0
	bl MOD20_02253F28
	ldr r0, [r4]
	ldr r2, _0225503C ; =0x04000280
	ldr r0, [r0, #0x10]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254F90:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254F90
	ldr r0, _02255040 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254FA0:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254FA0
	ldr r0, _02255044 ; =0x040002A8
	ldr r5, [r0]
	ldr r0, [r4, #0x68]
	bl MOD20_02253F28
	ldr r0, [r4, #0x6c]
	add r1, r5, #0
	bl MOD20_02253F28
	ldr r0, [r4]
	ldr r2, _0225503C ; =0x04000280
	ldr r0, [r0, #0xc]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254FD0:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254FD0
	ldr r0, _02255040 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254FE0:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254FE0
	ldr r0, _02255044 ; =0x040002A8
	ldr r5, [r0]
	ldr r0, [r4, #0x70]
	bl MOD20_02253F28
	ldr r0, [r4, #0x74]
	add r1, r5, #0
	bl MOD20_02253F28
	ldr r0, [r4]
	ldr r2, _0225503C ; =0x04000280
	ldr r0, [r0, #8]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02255010:
	ldrh r1, [r2]
	tst r1, r0
	bne _02255010
	ldr r0, _02255040 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02255020:
	ldrh r2, [r3]
	tst r2, r0
	bne _02255020
	ldr r0, _02255044 ; =0x040002A8
	ldr r5, [r0]
	ldr r0, [r4, #0x78]
	bl MOD20_02253F28
	ldr r0, [r4, #0x7c]
	add r1, r5, #0
	bl MOD20_02253F28
	pop {r3, r4, r5, pc}
	nop
_0225503C: .word 0x04000280
_02255040: .word 0x040002A0
_02255044: .word 0x040002A8
	thumb_func_end MOD22_02254F34

	thumb_func_start MOD22_02255048
MOD22_02255048: ; 0x02255048
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02255068 ; =MOD22_02255670
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02255068: .word MOD22_02255670
	thumb_func_end MOD22_02255048

	thumb_func_start MOD22_0225506C
MOD22_0225506C: ; 0x0225506C
	ldr r3, _02255074 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02255074: .word MOD20_02253794
	thumb_func_end MOD22_0225506C

	thumb_func_start MOD22_02255078
MOD22_02255078: ; 0x02255078
	ldr r3, _02255080 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02255080: .word MOD20_022537B8
	thumb_func_end MOD22_02255078

	thumb_func_start MOD22_02255084
MOD22_02255084: ; 0x02255084
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD22_02255084

	thumb_func_start MOD22_02255098
MOD22_02255098: ; 0x02255098
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r1, #0
	add r0, r7, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _0225515C ; =MOD22_02255654
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x15
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x14
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r7, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r7, #0
	bl MOD20_022538A4
	add r6, r0, #0
	add r0, r4, #0
	bl MOD22_0225516C
	add r0, r4, #0
	add r1, r6, #0
	bl MOD22_022551A4
	ldr r0, _02255160 ; =MOD22_02254F28
	add r1, r5, #0
	mov r2, #3
	bl FUN_0200CA44
	add r5, #0x84
	str r0, [r5]
	add r0, r4, #0
	bl MOD22_02254F34
	ldr r0, [r6]
	cmp r0, #0
	beq _02255136
	add r0, r4, #0
	mov r1, #1
	bl MOD22_02255048
_02255136:
	ldr r1, _02255164 ; =0x04001000
	ldr r0, _02255168 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #0x14
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r7, #0
	bl MOD22_02255084
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0225515C: .word MOD22_02255654
_02255160: .word MOD22_02254F28
_02255164: .word 0x04001000
_02255168: .word 0xFFFFE0FF
	thumb_func_end MOD22_02255098

	thumb_func_start MOD22_0225516C
MOD22_0225516C: ; 0x0225516C
	push {lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [sp]
	mov r2, #1
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
	mov r1, #0x16
	lsl r3, r3, #8
	bl GfGfxLoader_LoadWholePalette
	mov r0, #1
	add sp, #0xc
	pop {pc}
	.align 2, 0
	thumb_func_end MOD22_0225516C

	thumb_func_start MOD22_022551A4
MOD22_022551A4: ; 0x022551A4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r0, [sp, #4]
	add r0, #0x48
	ldr r4, _022551FC ; =MOD22_022556A0
	str r1, [sp]
	mov r6, #0
	add r5, r7, #0
	str r0, [sp, #4]
_022551B8:
	ldr r0, [r7, #0x5c]
	ldr r2, [sp, #4]
	add r1, r4, #0
	bl MOD20_02253E74
	str r0, [r5, #0x60]
	add r6, r6, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #7
	bls _022551B8
	ldr r2, _022551FC ; =MOD22_022556A0
	lsl r1, r6, #4
	add r1, r2, r1
	add r2, r7, #0
	ldr r0, [r7, #0x5c]
	add r2, #0x34
	bl MOD20_02253E74
	add r1, r7, #0
	add r1, #0x80
	str r0, [r1]
	ldr r0, [sp]
	ldr r0, [r0]
	cmp r0, #0
	bne _022551F6
	add r7, #0x80
	ldr r0, [r7]
	mov r1, #1
	bl MOD20_02253F78
_022551F6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022551FC: .word MOD22_022556A0
	thumb_func_end MOD22_022551A4

	thumb_func_start MOD22_02255200
MOD22_02255200: ; 0x02255200
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r1, [r4, #0x18]
	add r0, r5, #0
	lsl r2, r1, #2
	ldr r1, _0225522C ; =MOD22_02255638
	ldr r1, [r1, r2]
	bl FUN_0201B6C4
	ldr r2, [r4, #0x18]
	add r0, r5, #0
	lsl r3, r2, #2
	ldr r2, _0225522C ; =MOD22_02255638
	add r1, r6, #0
	ldr r2, [r2, r3]
	blx r2
	pop {r4, r5, r6, pc}
	.align 2, 0
_0225522C: .word MOD22_02255638
	thumb_func_end MOD22_02255200

	thumb_func_start MOD22_02255230
MOD22_02255230: ; 0x02255230
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD22_02255084
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD22_02255230

	thumb_func_start MOD22_02255268
MOD22_02255268: ; 0x02255268
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0
	bl MOD20_02253F78
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0xb
	bl MOD20_02253F28
	ldr r0, [r4, #4]
	mov r1, #1
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r0, _022552A8 ; =0x00000669
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD22_02255084
	pop {r3, r4, r5, pc}
	.align 2, 0
_022552A8: .word 0x00000669
	thumb_func_end MOD22_02255268

	thumb_func_start MOD22_022552AC
MOD22_022552AC: ; 0x022552AC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r6, #0x18]
	cmp r0, #2
	beq _022552CE
	add r0, r5, #0
	bl MOD22_02255084
	pop {r4, r5, r6, pc}
_022552CE:
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _022552DC
	cmp r0, #1
	pop {r4, r5, r6, pc}
_022552DC:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0xc
	bl MOD20_02253F28
	ldr r0, [r4, #4]
	mov r1, #0
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD22_022552AC

	thumb_func_start MOD22_02255300
MOD22_02255300: ; 0x02255300
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r7, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl MOD20_022538A8
	add r5, r0, #0
	ldr r0, [r7, #0x18]
	cmp r0, #3
	beq _0225532A
	add r0, r6, #0
	bl MOD22_02255084
	pop {r3, r4, r5, r6, r7, pc}
_0225532A:
	add r0, r6, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _0225533A
	cmp r0, #1
	beq _02255358
	pop {r3, r4, r5, r6, r7, pc}
_0225533A:
	mov r0, #6
	strh r0, [r5]
	mov r0, #2
	strb r0, [r5, #3]
	mov r0, #0
	strb r0, [r5, #2]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0xd
	bl MOD20_02253F28
	add r0, r6, #0
	bl MOD20_022538B0
_02255358:
	add r0, r5, #0
	mov r1, #6
	bl MOD22_02255510
	cmp r0, #0
	beq _0225537A
	ldr r0, _0225537C ; =0x00000669
	bl MOD20_02252B28
	ldrb r1, [r5, #3]
	ldr r0, [r4, #4]
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
_0225537A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225537C: .word 0x00000669
	thumb_func_end MOD22_02255300

	thumb_func_start MOD22_02255380
MOD22_02255380: ; 0x02255380
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r7, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl MOD20_022538A8
	add r5, r0, #0
	ldr r0, [r7, #0x18]
	cmp r0, #4
	beq _022553AA
	add r0, r6, #0
	bl MOD22_02255084
	pop {r3, r4, r5, r6, r7, pc}
_022553AA:
	add r0, r6, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _022553BA
	cmp r0, #1
	beq _022553D8
	pop {r3, r4, r5, r6, r7, pc}
_022553BA:
	mov r0, #3
	strh r0, [r5]
	mov r0, #2
	strb r0, [r5, #3]
	mov r0, #0
	strb r0, [r5, #2]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0xe
	bl MOD20_02253F28
	add r0, r6, #0
	bl MOD20_022538B0
_022553D8:
	add r0, r5, #0
	mov r1, #3
	bl MOD22_02255510
	cmp r0, #0
	beq _022553FA
	ldr r0, _022553FC ; =0x00000669
	bl MOD20_02252B28
	ldrb r1, [r5, #3]
	ldr r0, [r4, #4]
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
_022553FA:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022553FC: .word 0x00000669
	thumb_func_end MOD22_02255380

	thumb_func_start MOD22_02255400
MOD22_02255400: ; 0x02255400
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r7, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl MOD20_022538A8
	add r5, r0, #0
	ldr r0, [r7, #0x18]
	cmp r0, #5
	beq _0225542A
	add r0, r6, #0
	bl MOD22_02255084
	pop {r3, r4, r5, r6, r7, pc}
_0225542A:
	add r0, r6, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _0225543A
	cmp r0, #1
	beq _02255468
	pop {r3, r4, r5, r6, r7, pc}
_0225543A:
	mov r0, #0
	strh r0, [r5]
	strb r0, [r5, #2]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0xf
	bl MOD20_02253F28
	ldr r0, [r4, #4]
	mov r1, #5
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r0, _02255498 ; =0x00000666
	bl MOD20_02252B28
	add r0, r6, #0
	bl MOD20_022538B0
_02255468:
	ldrh r0, [r5]
	add r0, r0, #1
	strh r0, [r5]
	ldrh r0, [r5]
	cmp r0, #2
	bls _02255496
	mov r0, #0
	strh r0, [r5]
	ldrb r1, [r5, #2]
	mov r0, #1
	eor r0, r1
	strb r0, [r5, #2]
	ldrb r0, [r5, #2]
	add r0, r0, #5
	strb r0, [r5, #3]
	ldrb r1, [r5, #3]
	ldr r0, [r4, #4]
	bl MOD22_02255544
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
_02255496:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02255498: .word 0x00000666
	thumb_func_end MOD22_02255400

	thumb_func_start MOD22_0225549C
MOD22_0225549C: ; 0x0225549C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r7, r0, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r6, r0, #0
	add r0, r5, #0
	bl MOD20_022538A8
	add r4, r0, #0
	ldr r0, [r7, #0x18]
	cmp r0, #6
	beq _022554C6
	add r0, r5, #0
	bl MOD22_02255084
	pop {r3, r4, r5, r6, r7, pc}
_022554C6:
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _022554D6
	cmp r0, #1
	beq _022554FC
	pop {r3, r4, r5, r6, r7, pc}
_022554D6:
	add r0, r6, #0
	add r0, #0x80
	ldr r0, [r0]
	mov r1, #0x10
	bl MOD20_02253F28
	ldr r0, [r6, #4]
	mov r1, #6
	bl MOD22_02255544
	ldr r0, [r6, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD20_022538B0
	mov r0, #0
	strh r0, [r4]
_022554FC:
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	ldrh r0, [r4]
	cmp r0, #0x50
	bls _0225550E
	add r0, r5, #0
	bl MOD22_02255084
_0225550E:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD22_0225549C

	thumb_func_start MOD22_02255510
MOD22_02255510: ; 0x02255510
	ldrh r2, [r0]
	add r2, r2, #1
	strh r2, [r0]
	ldrh r2, [r0]
	cmp r2, r1
	bls _0225553A
	mov r2, #0
	strh r2, [r0]
	ldrb r1, [r0, #2]
	add r1, r1, #1
	strb r1, [r0, #2]
	ldrb r1, [r0, #2]
	cmp r1, #3
	blo _0225552E
	strb r2, [r0, #2]
_0225552E:
	ldrb r2, [r0, #2]
	ldr r1, _02255540 ; =MOD22_02255634
	ldrb r1, [r1, r2]
	strb r1, [r0, #3]
	mov r0, #1
	bx lr
_0225553A:
	mov r0, #0
	bx lr
	nop
_02255540: .word MOD22_02255634
	thumb_func_end MOD22_02255510

	thumb_func_start MOD22_02255544
MOD22_02255544: ; 0x02255544
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #6
	bl GetBgTilemapBuffer
	ldr r1, _022555A0 ; =0x00000252
	mov r7, #1
	add r1, r0, r1
	lsl r0, r4, #2
	add r0, r4, r0
	add r0, r0, #2
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0
	mov ip, r0
	lsl r7, r7, #0xa
	mov r6, #9
_02255568:
	ldr r3, [sp]
	mov r2, #0
	add r4, r1, #0
_0225556E:
	sub r5, r6, r2
	add r0, r3, #0
	strh r3, [r4]
	orr r0, r7
	lsl r5, r5, #1
	add r2, r2, #1
	strh r0, [r1, r5]
	add r3, r3, #1
	add r4, r4, #2
	cmp r2, #5
	blo _0225556E
	ldr r0, [sp]
	add r1, #0x40
	add r0, #0x25
	str r0, [sp]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #0xb
	blo _02255568
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022555A0: .word 0x00000252
	thumb_func_end MOD22_02255544

	thumb_func_start MOD22_022555A4
MOD22_022555A4: ; 0x022555A4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _022555C0
	cmp r0, #1
	beq _022555CC
	pop {r3, r4, r5, pc}
_022555C0:
	add r0, r4, #0
	bl MOD22_022555FC
	add r0, r5, #0
	bl MOD20_022538B0
_022555CC:
	add r0, r4, #0
	add r0, #0x34
	bl MOD20_02254014
	add r0, r4, #0
	add r0, #0x48
	bl MOD20_02254014
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	bl FUN_0200CAB4
	mov r0, #0
	add r4, #0x84
	str r0, [r4]
	add r0, r5, #0
	bl MOD22_02255084
	pop {r3, r4, r5, pc}
	thumb_func_end MOD22_022555A4

	thumb_func_start MOD22_022555FC
MOD22_022555FC: ; 0x022555FC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02255604:
	ldr r0, [r6, #0x5c]
	ldr r1, [r5, #0x60]
	bl MOD20_02253F14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #9
	blo _02255604
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD22_022555FC

	.section .rodata

	.global MOD22_02255618
MOD22_02255618: ; 0x02255618
	.byte 0xFE, 0x70, 0x70, 0x27

	.global MOD22_0225561C
MOD22_0225561C: ; 0x0225561C
	.word MOD22_022549FC, MOD22_02254A4C, MOD22_02254ACC, MOD22_02254B50
	.word MOD22_02254BB4, MOD22_02254C50

	.global MOD22_02255634
MOD22_02255634: ; 0x02255634
	.byte 0x02, 0x03, 0x04, 0x00

	.global MOD22_02255638
MOD22_02255638: ; 0x02255638
	.word MOD22_02255230, MOD22_02255268, MOD22_022552AC, MOD22_02255300
	.word MOD22_02255380, MOD22_02255400, MOD22_0225549C

	.global MOD22_02255654
MOD22_02255654: ; 0x02255654
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD22_02255670
MOD22_02255670: ; 0x02255670
	.word 0x00, MOD22_02255098, 0x00
	.word 0x01, MOD22_02255200, 0x04
	.word 0x03, MOD22_022555A4, 0x00
	.word 0x00, 0x00000000, 0x00

	.global MOD22_022556A0
MOD22_022556A0: ; 0x022556A0
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x80, 0x02, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00
	.byte 0x0A, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00
