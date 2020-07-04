	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD40_02254840
MOD40_02254840: ; 0x02254840
	ldr r3, _02254848 ; =Poketch_InitApp
	ldr r0, _0225484C ; =MOD40_02254854
	ldr r1, _02254850 ; =MOD40_022549D4
	bx r3
	.align 2, 0
_02254848: .word Poketch_InitApp
_0225484C: .word MOD40_02254854
_02254850: .word MOD40_022549D4
	thumb_func_end MOD40_02254840

	thumb_func_start MOD40_02254854
MOD40_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x34
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD40_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD40_02254998
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
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
_02254898: .word MOD40_02254998
	thumb_func_end MOD40_02254854

	thumb_func_start MOD40_0225489C
MOD40_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r6, r2, #0
	bl MOD20_02252C3C
	str r0, [r5, #0x10]
	bl FUN_0204BF94
	strb r0, [r5, #3]
	ldr r0, [r5, #0x10]
	add r1, sp, #8
	add r2, sp, #4
	bl FUN_0204BF9C
	ldr r0, [sp, #8]
	strb r0, [r5, #6]
	ldr r0, [sp, #4]
	strb r0, [r5, #7]
	add r0, r5, #3
	bl MOD40_02254940
	add r0, r5, #0
	add r0, #8
	add r1, r5, #3
	add r2, r6, #0
	bl MOD40_02254D6C
	cmp r0, #0
	beq _02254930
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254938 ; =0x02255328
	ldr r2, _0225493C ; =MOD40_02254990
	mov r1, #6
	add r3, r5, #0
	bl MOD20_02254130
	str r0, [r5, #0x14]
	mov r0, #0
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x14]
	mov r1, #2
	mov r2, #4
	bl MOD20_022542C0
	ldr r0, [r5, #0x14]
	mov r1, #3
	mov r2, #4
	bl MOD20_022542C0
	mov r1, #4
	ldr r0, [r5, #0x14]
	add r2, r1, #0
	bl MOD20_022542C0
	ldr r0, [r5, #0x14]
	mov r1, #5
	mov r2, #4
	bl MOD20_022542C0
	mov r0, #0
	str r0, [r5, #0x2c]
	str r0, [r5, #0x30]
	add sp, #0xc
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02254930:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02254938: .word 0x02255328
_0225493C: .word MOD40_02254990
	thumb_func_end MOD40_0225489C

	thumb_func_start MOD40_02254940
MOD40_02254940: ; 0x02254940
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r0, sp, #0
	bl FUN_02012690
	ldr r0, [sp]
	cmp r0, #0x18
	blo _0225495A
	mov r1, #0x18
	bl _u32_div_f
	str r1, [sp]
_0225495A:
	ldr r0, [sp, #4]
	cmp r0, #0x3c
	blo _0225496A
	ldr r0, [sp]
	mov r1, #0x3c
	bl _u32_div_f
	str r1, [sp]
_0225496A:
	ldr r0, [sp]
	strb r0, [r4, #1]
	ldr r0, [sp, #4]
	strb r0, [r4, #2]
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD40_02254940

	thumb_func_start MOD40_02254978
MOD40_02254978: ; 0x02254978
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	bl MOD20_02254198
	ldr r0, [r4, #8]
	bl MOD40_02254DA8
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD40_02254978

	thumb_func_start MOD40_02254990
MOD40_02254990: ; 0x02254990
	str r0, [r3, #0x18]
	str r1, [r3, #0x1c]
	bx lr
	.align 2, 0
	thumb_func_end MOD40_02254990

	thumb_func_start MOD40_02254998
MOD40_02254998: ; 0x02254998
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #5
	bhs _022549CE
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022549D0 ; =0x02255314
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _022549CE
	add r0, r4, #0
	bl MOD40_02254978
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0xc]
	bl MOD20_022529A0
_022549CE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022549D0: .word 0x02255314
	thumb_func_end MOD40_02254998

	thumb_func_start MOD40_022549D4
MOD40_022549D4: ; 0x022549D4
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD40_022549D4

	thumb_func_start MOD40_022549DC
MOD40_022549DC: ; 0x022549DC
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _022549E4
	b _022549E6
_022549E4:
	mov r1, #4
_022549E6:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD40_022549DC

	thumb_func_start MOD40_022549F0
MOD40_022549F0: ; 0x022549F0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A00
	cmp r0, #1
	beq _02254A10
	b _02254A3A
_02254A00:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD40_02254F98
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A3A
_02254A10:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD40_02254FBC
	cmp r0, #0
	beq _02254A3A
	ldr r0, [r4, #0xc]
	bl MOD20_0225298C
	ldrb r0, [r4, #3]
	cmp r0, #0
	beq _02254A32
	add r0, r4, #0
	mov r1, #2
	bl MOD40_022549DC
	b _02254A3A
_02254A32:
	add r0, r4, #0
	mov r1, #1
	bl MOD40_022549DC
_02254A3A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD40_022549F0

	thumb_func_start MOD40_02254A40
MOD40_02254A40: ; 0x02254A40
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254A54
	mov r1, #4
	bl MOD40_022549DC
	mov r0, #0
	pop {r4, pc}
_02254A54:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A60
	cmp r0, #1
	beq _02254B32
	b _02254B46
_02254A60:
	ldr r1, [r4, #0x1c]
	cmp r1, #1
	bne _02254A9A
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02254A9A
	mov r0, #1
	strb r0, [r4, #3]
	add r0, r4, #3
	bl MOD40_02254940
	mov r2, #6
	mov r3, #7
	ldrsb r2, [r4, r2]
	ldrsb r3, [r4, r3]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_0204BFB0
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD40_02254F98
	mov r0, #0
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B46
_02254A9A:
	cmp r1, #1
	bne _02254AB0
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _02254AB0
	mov r0, #0
	str r0, [r4, #0x1c]
	ldr r0, _02254B4C ; =0x0000066E
	bl MOD20_02252B28
	b _02254B46
_02254AB0:
	cmp r1, #1
	beq _02254AB8
	cmp r1, #7
	bne _02254B46
_02254AB8:
	ldr r0, [r4, #0x18]
	cmp r0, #5
	bhi _02254B24
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254ACA: ; jump table
	.short _02254B24 - _02254ACA - 2 ; case 0
	.short _02254B24 - _02254ACA - 2 ; case 1
	.short _02254AD6 - _02254ACA - 2 ; case 2
	.short _02254AEA - _02254ACA - 2 ; case 3
	.short _02254AFE - _02254ACA - 2 ; case 4
	.short _02254B12 - _02254ACA - 2 ; case 5
_02254AD6:
	mov r0, #6
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #6]
	ldrsb r0, [r4, r0]
	cmp r0, #0x17
	ble _02254B24
	mov r0, #0
	strb r0, [r4, #6]
	b _02254B24
_02254AEA:
	mov r0, #6
	ldrsb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, #6]
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bge _02254B24
	mov r0, #0x17
	strb r0, [r4, #6]
	b _02254B24
_02254AFE:
	mov r0, #7
	ldrsb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, #7]
	ldrsb r0, [r4, r0]
	cmp r0, #0x3b
	ble _02254B24
	mov r0, #0
	strb r0, [r4, #7]
	b _02254B24
_02254B12:
	mov r0, #7
	ldrsb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, #7]
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bge _02254B24
	mov r0, #0x3b
	strb r0, [r4, #7]
_02254B24:
	mov r0, #0
	str r0, [r4, #0x1c]
	ldr r0, [r4, #8]
	mov r1, #4
	bl MOD40_02254F98
	b _02254B46
_02254B32:
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD40_02254FBC
	cmp r0, #0
	beq _02254B46
	add r0, r4, #0
	mov r1, #2
	bl MOD40_022549DC
_02254B46:
	mov r0, #0
	pop {r4, pc}
	nop
_02254B4C: .word 0x0000066E
	thumb_func_end MOD40_02254A40

	thumb_func_start MOD40_02254B50
MOD40_02254B50: ; 0x02254B50
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254B68
	mov r1, #4
	bl MOD40_022549DC
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254B68:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254B74
	cmp r0, #1
	beq _02254C02
	b _02254C12
_02254B74:
	add r0, r4, #3
	bl MOD40_02254D4C
	cmp r0, #0
	beq _02254B8C
	add r0, r4, #0
	mov r1, #3
	bl MOD40_022549DC
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254B8C:
	ldr r1, [r4, #0x1c]
	cmp r1, #1
	bne _02254BB2
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _02254BB2
	mov r0, #0
	strb r0, [r4, #3]
	ldr r0, [r4, #8]
	mov r1, #3
	bl MOD40_02254F98
	mov r0, #0
	str r0, [r4, #0x1c]
	add r0, r4, #0
	mov r1, #1
	bl MOD40_022549DC
	b _02254C12
_02254BB2:
	cmp r1, #1
	bne _02254BC4
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02254BC4
	ldr r0, _02254C18 ; =0x0000066E
	bl MOD20_02252B28
	b _02254C12
_02254BC4:
	add r0, r4, #0
	bl MOD40_02254CE4
	cmp r0, #0
	bne _02254BD4
	add r0, r4, #0
	bl MOD40_02254CE8
_02254BD4:
	add r0, r4, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD40_02254D00
	cmp r0, #0
	beq _02254C12
	mov r0, #5
	ldrsb r0, [r4, r0]
	ldr r1, [sp]
	cmp r1, r0
	beq _02254C12
	strb r1, [r4, #5]
	ldr r0, [sp, #4]
	mov r1, #4
	strb r0, [r4, #4]
	ldr r0, [r4, #8]
	bl MOD40_02254F98
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C12
_02254C02:
	ldr r0, [r4, #8]
	mov r1, #4
	bl MOD40_02254FBC
	cmp r0, #0
	beq _02254C12
	mov r0, #0
	strb r0, [r4, #1]
_02254C12:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_02254C18: .word 0x0000066E
	thumb_func_end MOD40_02254B50

	thumb_func_start MOD40_02254C1C
MOD40_02254C1C: ; 0x02254C1C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254C34
	mov r1, #4
	bl MOD40_022549DC
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254C34:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254C40
	cmp r0, #1
	beq _02254C50
	b _02254CDC
_02254C40:
	ldr r0, [r4, #8]
	mov r1, #5
	bl MOD40_02254F98
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254CDC
_02254C50:
	add r0, r4, #3
	bl MOD40_02254D4C
	cmp r0, #0
	bne _02254C76
	ldr r0, [r4, #8]
	bl MOD40_0225530C
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD40_02254F98
	add r0, r4, #0
	mov r1, #2
	bl MOD40_022549DC
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254C76:
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	bne _02254CA6
	ldr r0, [r4, #0x18]
	cmp r0, #1
	bne _02254CA6
	mov r0, #0
	strb r0, [r4, #3]
	ldr r0, [r4, #8]
	bl MOD40_0225530C
	ldr r0, [r4, #8]
	mov r1, #3
	bl MOD40_02254F98
	mov r0, #0
	str r0, [r4, #0x1c]
	add r0, r4, #0
	mov r1, #1
	bl MOD40_022549DC
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254CA6:
	add r0, r4, #0
	bl MOD40_02254CE4
	cmp r0, #0
	bne _02254CB6
	add r0, r4, #0
	bl MOD40_02254CE8
_02254CB6:
	add r0, r4, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD40_02254D00
	cmp r0, #0
	beq _02254CDC
	mov r0, #5
	ldrsb r0, [r4, r0]
	ldr r1, [sp]
	cmp r1, r0
	beq _02254CDC
	strb r1, [r4, #5]
	ldr r0, [sp, #4]
	mov r1, #4
	strb r0, [r4, #4]
	ldr r0, [r4, #8]
	bl MOD40_02254F98
_02254CDC:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD40_02254C1C

	thumb_func_start MOD40_02254CE4
MOD40_02254CE4: ; 0x02254CE4
	ldr r0, [r0, #0x2c]
	bx lr
	thumb_func_end MOD40_02254CE4

	thumb_func_start MOD40_02254CE8
MOD40_02254CE8: ; 0x02254CE8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	bne _02254CFE
	add r0, r4, #0
	add r0, #0x20
	bl FUN_02012690
	mov r0, #1
	str r0, [r4, #0x30]
_02254CFE:
	pop {r4, pc}
	thumb_func_end MOD40_02254CE8

	thumb_func_start MOD40_02254D00
MOD40_02254D00: ; 0x02254D00
	ldr r3, [r0, #0x30]
	cmp r3, #0
	beq _02254D12
	ldr r3, [r0, #0x20]
	str r3, [r1]
	ldr r0, [r0, #0x24]
	str r0, [r2]
	mov r0, #1
	bx lr
_02254D12:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD40_02254D00

	thumb_func_start MOD40_02254D18
MOD40_02254D18: ; 0x02254D18
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254D28
	cmp r0, #1
	beq _02254D38
	b _02254D46
_02254D28:
	ldr r0, [r4, #8]
	mov r1, #1
	bl MOD40_02254F98
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254D46
_02254D38:
	ldr r0, [r4, #8]
	bl MOD40_02254FC8
	cmp r0, #0
	beq _02254D46
	mov r0, #1
	pop {r4, pc}
_02254D46:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD40_02254D18

	thumb_func_start MOD40_02254D4C
MOD40_02254D4C: ; 0x02254D4C
	mov r1, #1
	mov r2, #3
	ldrsb r3, [r0, r1]
	ldrsb r2, [r0, r2]
	cmp r3, r2
	bne _02254D64
	mov r2, #2
	ldrsb r3, [r0, r2]
	mov r2, #4
	ldrsb r0, [r0, r2]
	cmp r3, r0
	beq _02254D66
_02254D64:
	mov r1, #0
_02254D66:
	add r0, r1, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD40_02254D4C

	thumb_func_start MOD40_02254D6C
MOD40_02254D6C: ; 0x02254D6C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x9c
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254DA2
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x30]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD40_02254DBC
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254DA2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD40_02254D6C

	thumb_func_start MOD40_02254DA8
MOD40_02254DA8: ; 0x02254DA8
	push {r4, lr}
	add r4, r0, #0
	beq _02254DB8
	bl MOD40_02254EE4
	add r0, r4, #0
	bl FreeToHeap
_02254DB8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD40_02254DA8

	thumb_func_start MOD40_02254DBC
MOD40_02254DBC: ; 0x02254DBC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r5, r0, #0
	str r1, [sp, #0xc]
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #2
	bl FUN_02006A34
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	mov r3, #0xa
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x4f
	lsl r3, r3, #8
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x68
	mov r1, #0xc
	mov r2, #0x4d
	mov r3, #0x4e
	bl MOD20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x7c
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl MOD20_02253FBC
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #0x68
	str r0, [sp, #0x14]
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x7c
	ldr r7, _02254EE0 ; =0x022553B0
	mov r4, #0
	add r6, r5, #0
	str r0, [sp, #0x10]
_02254E2A:
	cmp r4, #9
	blt _02254E40
	cmp r4, #0xc
	bgt _02254E40
	ldr r0, [r5, #0x30]
	ldr r2, [sp, #0x10]
	add r1, r7, #0
	bl MOD20_02253E74
	str r0, [r6, #0x34]
	b _02254E52
_02254E40:
	ldr r0, [r5, #0x30]
	ldr r2, [sp, #0x14]
	add r1, r7, #0
	bl MOD20_02253E74
	mov r1, #0x50
	str r0, [r6, #0x34]
	bl MOD20_02253FA4
_02254E52:
	add r4, r4, #1
	add r7, #0x10
	add r6, r6, #4
	cmp r4, #0xd
	blt _02254E2A
	ldr r0, [sp, #0xc]
	ldrb r0, [r0]
	cmp r0, #0
	ldr r0, [r5, #0x34]
	beq _02254EB2
	mov r1, #3
	bl MOD20_02253F28
	ldr r0, [r5, #0x40]
	mov r1, #5
	bl MOD20_02253F28
	ldr r0, [r5, #0x44]
	mov r1, #5
	bl MOD20_02253F28
	ldr r0, [r5, #0x48]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r5, #0x4c]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r5, #0x54]
	mov r1, #1
	bl MOD20_02253F78
	ldr r1, [sp, #0xc]
	mov r2, #1
	ldrsb r1, [r1, r2]
	ldr r2, [sp, #0xc]
	mov r3, #2
	ldrsb r2, [r2, r3]
	add r0, r5, #0
	bl MOD40_02254F14
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_02254EB2:
	mov r1, #2
	bl MOD20_02253F28
	ldr r0, [r5, #0x40]
	mov r1, #5
	bl MOD20_02253F28
	ldr r0, [r5, #0x44]
	mov r1, #4
	bl MOD20_02253F28
	ldr r1, [sp, #0xc]
	mov r2, #3
	ldrsb r1, [r1, r2]
	ldr r2, [sp, #0xc]
	mov r3, #4
	ldrsb r2, [r2, r3]
	add r0, r5, #0
	bl MOD40_02254F14
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254EE0: .word 0x022553B0
	thumb_func_end MOD40_02254DBC

	thumb_func_start MOD40_02254EE4
MOD40_02254EE4: ; 0x02254EE4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02254EEC:
	ldr r1, [r5, #0x34]
	cmp r1, #0
	beq _02254EF8
	ldr r0, [r6, #0x30]
	bl MOD20_02253F14
_02254EF8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xd
	blt _02254EEC
	add r0, r6, #0
	add r0, #0x68
	bl MOD20_02254014
	add r6, #0x7c
	add r0, r6, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD40_02254EE4

	thumb_func_start MOD40_02254F14
MOD40_02254F14: ; 0x02254F14
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02254F8C ; =0x04000280
	mov r3, #0
	strh r3, [r0]
	str r1, [r0, #0x10]
	add r1, r0, #0
	add r4, r2, #0
	mov r2, #0xa
	add r1, #0x18
	str r2, [r1]
	str r3, [r1, #4]
	lsr r1, r0, #0xb
_02254F2E:
	ldrh r2, [r0]
	tst r2, r1
	bne _02254F2E
	ldr r1, _02254F90 ; =0x040002A0
	ldr r0, [r5, #0x58]
	ldr r1, [r1]
	bl MOD20_02253F28
	ldr r2, _02254F8C ; =0x04000280
	lsr r0, r2, #0xb
_02254F42:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254F42
	ldr r1, _02254F94 ; =0x040002A8
	ldr r0, [r5, #0x5c]
	ldr r1, [r1]
	bl MOD20_02253F28
	ldr r0, _02254F8C ; =0x04000280
	mov r3, #0
	strh r3, [r0]
	add r1, r0, #0
	str r4, [r0, #0x10]
	mov r2, #0xa
	add r1, #0x18
	str r2, [r1]
	str r3, [r1, #4]
	lsr r1, r0, #0xb
_02254F66:
	ldrh r2, [r0]
	tst r2, r1
	bne _02254F66
	ldr r1, _02254F90 ; =0x040002A0
	ldr r0, [r5, #0x60]
	ldr r1, [r1]
	bl MOD20_02253F28
	ldr r2, _02254F8C ; =0x04000280
	lsr r0, r2, #0xb
_02254F7A:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254F7A
	ldr r1, _02254F94 ; =0x040002A8
	ldr r0, [r5, #0x64]
	ldr r1, [r1]
	bl MOD20_02253F28
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254F8C: .word 0x04000280
_02254F90: .word 0x040002A0
_02254F94: .word 0x040002A8
	thumb_func_end MOD40_02254F14

	thumb_func_start MOD40_02254F98
MOD40_02254F98: ; 0x02254F98
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254FB8 ; =0x0225535C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254FB8: .word 0x0225535C
	thumb_func_end MOD40_02254F98

	thumb_func_start MOD40_02254FBC
MOD40_02254FBC: ; 0x02254FBC
	ldr r3, _02254FC4 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254FC4: .word MOD20_02253794
	thumb_func_end MOD40_02254FBC

	thumb_func_start MOD40_02254FC8
MOD40_02254FC8: ; 0x02254FC8
	ldr r3, _02254FD0 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254FD0: .word MOD20_022537B8
	thumb_func_end MOD40_02254FC8

	thumb_func_start MOD40_02254FD4
MOD40_02254FD4: ; 0x02254FD4
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD40_02254FD4

	thumb_func_start MOD40_02254FE8
MOD40_02254FE8: ; 0x02254FE8
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _0225506C ; =0x02255340
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
	mov r1, #0x4c
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x4b
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02255070 ; =0x04001000
	ldr r0, _02255074 ; =0xFFFFE0FF
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
	add r0, r4, #0
	bl MOD40_02254FD4
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_0225506C: .word 0x02255340
_02255070: .word 0x04001000
_02255074: .word 0xFFFFE0FF
	thumb_func_end MOD40_02254FE8

	thumb_func_start MOD40_02255078
MOD40_02255078: ; 0x02255078
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _02255094
	cmp r0, #1
	beq _022550A2
	pop {r3, r4, r5, pc}
_02255094:
	add r0, r4, #0
	bl MOD40_0225530C
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_022550A2:
	add r0, r4, #0
	mov r1, #5
	bl MOD40_02254FBC
	cmp r0, #0
	beq _022550BC
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD40_02254FD4
_022550BC:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD40_02255078

	thumb_func_start MOD40_022550C0
MOD40_022550C0: ; 0x022550C0
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r0, _02255138 ; =0x00000663
	bl MOD20_02252B28
	ldr r0, [r5, #0x34]
	mov r1, #3
	bl MOD20_02253F28
	ldr r0, [r5, #0x40]
	mov r1, #5
	bl MOD20_02253F28
	ldr r0, [r5, #0x44]
	mov r1, #5
	bl MOD20_02253F28
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r5, #0x3c]
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r5, #0x48]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r5, #0x4c]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r5, #0x50]
	mov r1, #1
	bl MOD20_02253F78
	ldr r0, [r5, #0x54]
	mov r1, #1
	bl MOD20_02253F78
	mov r1, #1
	mov r2, #2
	ldrsb r1, [r4, r1]
	ldrsb r2, [r4, r2]
	add r0, r5, #0
	bl MOD40_02254F14
	add r0, r6, #0
	bl MOD40_02254FD4
	pop {r4, r5, r6, pc}
	.align 2, 0
_02255138: .word 0x00000663
	thumb_func_end MOD40_022550C0

	thumb_func_start MOD40_0225513C
MOD40_0225513C: ; 0x0225513C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r0, _022551B4 ; =0x00000663
	bl MOD20_02252B28
	ldr r0, [r5, #0x34]
	mov r1, #2
	bl MOD20_02253F28
	ldr r0, [r5, #0x40]
	mov r1, #5
	bl MOD20_02253F28
	ldr r0, [r5, #0x44]
	mov r1, #4
	bl MOD20_02253F28
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r5, #0x3c]
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r5, #0x48]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r5, #0x4c]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r5, #0x50]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r5, #0x54]
	mov r1, #0
	bl MOD20_02253F78
	mov r1, #3
	mov r2, #4
	ldrsb r1, [r4, r1]
	ldrsb r2, [r4, r2]
	add r0, r5, #0
	bl MOD40_02254F14
	add r0, r6, #0
	bl MOD40_02254FD4
	pop {r4, r5, r6, pc}
	.align 2, 0
_022551B4: .word 0x00000663
	thumb_func_end MOD40_0225513C

	thumb_func_start MOD40_022551B8
MOD40_022551B8: ; 0x022551B8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r2, r0, #0
	ldrb r0, [r2]
	cmp r0, #0
	beq _022551E2
	mov r1, #1
	mov r3, #2
	ldrsb r1, [r2, r1]
	ldrsb r2, [r2, r3]
	add r0, r4, #0
	bl MOD40_02254F14
	b _022551F0
_022551E2:
	mov r1, #3
	mov r3, #4
	ldrsb r1, [r2, r1]
	ldrsb r2, [r2, r3]
	add r0, r4, #0
	bl MOD40_02254F14
_022551F0:
	add r0, r5, #0
	bl MOD40_02254FD4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD40_022551B8

	thumb_func_start MOD40_022551F8
MOD40_022551F8: ; 0x022551F8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _0225521A
	cmp r0, #1
	beq _02255262
	pop {r3, r4, r5, pc}
_0225521A:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x90
	str r1, [r0]
	ldr r0, [r4, #0x40]
	mov r1, #4
	bl MOD20_02253F28
	ldr r0, [r4, #0x44]
	mov r1, #4
	bl MOD20_02253F28
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl MOD20_02253F28
	ldr r0, [r4, #0x3c]
	mov r1, #1
	bl MOD20_02253F28
	ldr r0, _02255304 ; =0x00000663
	bl MOD20_02252B28
	ldr r0, _02255308 ; =0x00000126
	bl MOD20_02252B48
	add r0, r4, #0
	mov r1, #0
	add r0, #0x94
	str r1, [r0]
	add r4, #0x98
	add r0, r5, #0
	str r1, [r4]
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_02255262:
	add r0, r4, #0
	add r0, #0x90
	ldr r0, [r0]
	cmp r0, #0
	beq _02255294
	ldr r0, [r4, #0x58]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x5c]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x60]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x64]
	mov r1, #0
	bl MOD20_02253F78
	add r0, r5, #0
	bl MOD40_02254FD4
	pop {r3, r4, r5, pc}
_02255294:
	bl FUN_02005670
	cmp r0, #0
	bne _022552A2
	ldr r0, _02255308 ; =0x00000126
	bl MOD20_02252B48
_022552A2:
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x94
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x94
	ldr r0, [r0]
	cmp r0, #0xf
	blo _02255300
	add r0, r4, #0
	mov r1, #0
	add r0, #0x94
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x98
	ldr r1, [r0]
	mov r0, #1
	eor r1, r0
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	add r1, r4, #0
	add r1, #0x98
	ldr r0, [r4, #0x58]
	ldr r1, [r1]
	bl MOD20_02253F78
	add r1, r4, #0
	add r1, #0x98
	ldr r0, [r4, #0x5c]
	ldr r1, [r1]
	bl MOD20_02253F78
	add r1, r4, #0
	add r1, #0x98
	ldr r0, [r4, #0x60]
	ldr r1, [r1]
	bl MOD20_02253F78
	ldr r0, [r4, #0x64]
	add r4, #0x98
	ldr r1, [r4]
	bl MOD20_02253F78
_02255300:
	pop {r3, r4, r5, pc}
	nop
_02255304: .word 0x00000663
_02255308: .word 0x00000126
	thumb_func_end MOD40_022551F8

	thumb_func_start MOD40_0225530C
MOD40_0225530C: ; 0x0225530C
	mov r1, #1
	add r0, #0x90
	str r1, [r0]
	bx lr
	thumb_func_end MOD40_0225530C

	.section .rodata
	; 0x02255314
	.byte 0xF1, 0x49, 0x25, 0x02, 0x41, 0x4A, 0x25, 0x02, 0x51, 0x4B, 0x25, 0x02, 0x1D, 0x4C, 0x25, 0x02
	.byte 0x19, 0x4D, 0x25, 0x02, 0x48, 0x68, 0xB0, 0xD0, 0x68, 0x88, 0xB0, 0xD0, 0x70, 0x80, 0x40, 0x50
	.byte 0xA0, 0xB0, 0x40, 0x50, 0x70, 0x80, 0x70, 0x80, 0xA0, 0xB0, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x4F, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x79, 0x50, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0xC1, 0x50, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x3D, 0x51, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xB9, 0x51, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0xF9, 0x51, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00
	.byte 0x00, 0x80, 0x06, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00
	.byte 0x00, 0x80, 0x07, 0x00, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00
	.byte 0x00, 0x40, 0x0A, 0x00, 0x06, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00
	.byte 0x00, 0x80, 0x07, 0x00, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00
	.byte 0x00, 0x40, 0x0A, 0x00, 0x06, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00
	.byte 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.section .sinit
	.word MOD40_02254840
