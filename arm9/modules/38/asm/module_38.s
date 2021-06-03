	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD38_02254854
MOD38_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x24
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD38_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD38_0225494C
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
_02254898: .word MOD38_0225494C
	thumb_func_end MOD38_02254854

	thumb_func_start MOD38_0225489C
MOD38_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	add r6, r2, #0
	add r0, r3, #0
	add r1, #8
	mov r2, #0xc
	str r3, [r5, #4]
	bl FUN_02089418
	cmp r0, #0
	bne _022548C0
	add r0, r5, #0
	add r0, #8
	bl MOD38_02254908
_022548C0:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x14
	add r1, #8
	add r2, r6, #0
	bl MOD38_02254BC4
	cmp r0, #0
	beq _022548F8
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254900 ; =MOD38_0225511C
	ldr r2, _02254904 ; =MOD38_02254988
	mov r1, #6
	add r3, r5, #0
	bl MOD20_02254130
	str r0, [r5, #0x1c]
	mov r0, #0
	str r0, [r5, #0x20]
	add sp, #4
	str r4, [r5, #0x18]
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_022548F8:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02254900: .word MOD38_0225511C
_02254904: .word MOD38_02254988
	thumb_func_end MOD38_0225489C

	thumb_func_start MOD38_02254908
MOD38_02254908: ; 0x02254908
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	str r0, [r4]
	strh r0, [r4, #6]
	strh r0, [r4, #8]
	mov r0, #0x12
	strh r0, [r4, #0xa]
	ldrh r0, [r4, #6]
	ldrh r1, [r4, #8]
	ldrh r2, [r4, #0xa]
	bl MOD38_02254B2C
	strh r0, [r4, #4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD38_02254908

	thumb_func_start MOD38_02254928
MOD38_02254928: ; 0x02254928
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #8
	mov r2, #0xc
	bl FUN_020893F0
	ldr r0, [r4, #0x1c]
	bl MOD20_02254198
	ldr r0, [r4, #0x14]
	bl MOD38_02254D04
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD38_02254928

	thumb_func_start MOD38_0225494C
MOD38_0225494C: ; 0x0225494C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254982
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0x1c]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254984 ; =MOD38_02255110
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254982
	add r0, r4, #0
	bl MOD38_02254928
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x18]
	bl MOD20_022529A0
_02254982:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254984: .word MOD38_02255110
	thumb_func_end MOD38_0225494C

	thumb_func_start MOD38_02254988
MOD38_02254988: ; 0x02254988
	str r0, [r3, #8]
	str r1, [r3, #0x20]
	bx lr
	.align 2, 0
	thumb_func_end MOD38_02254988

	thumb_func_start MOD38_02254990
MOD38_02254990: ; 0x02254990
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD38_02254990

	thumb_func_start MOD38_02254998
MOD38_02254998: ; 0x02254998
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _022549A0
	b _022549A2
_022549A0:
	mov r1, #2
_022549A2:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD38_02254998

	thumb_func_start MOD38_022549AC
MOD38_022549AC: ; 0x022549AC
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549BC
	cmp r0, #1
	beq _022549CC
	b _022549E6
_022549BC:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD38_02254D34
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549E6
_022549CC:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD38_02254D58
	cmp r0, #0
	beq _022549E6
	ldr r0, [r4, #0x18]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD38_02254998
_022549E6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD38_022549AC

	thumb_func_start MOD38_022549EC
MOD38_022549EC: ; 0x022549EC
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #2]
	cmp r0, #0
	beq _02254A0C
	ldr r0, [r4, #0x14]
	bl MOD38_02254D64
	cmp r0, #0
	beq _02254A08
	add r0, r4, #0
	mov r1, #2
	bl MOD38_02254998
_02254A08:
	mov r0, #0
	pop {r4, pc}
_02254A0C:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A1C
	cmp r0, #1
	beq _02254A32
	cmp r0, #2
	beq _02254AE4
	b _02254AF2
_02254A1C:
	ldr r0, [r4, #0x20]
	cmp r0, #1
	bne _02254AF2
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl MOD38_02254D34
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AF2
_02254A32:
	ldr r0, [r4, #0x20]
	cmp r0, #2
	bne _02254A46
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl MOD38_02254D34
	mov r0, #0
	strb r0, [r4, #1]
	b _02254AF2
_02254A46:
	cmp r0, #3
	bne _02254AF2
	ldr r0, [r4, #8]
	cmp r0, #5
	bhi _02254AC0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254A5C: ; jump table
	.short _02254A68 - _02254A5C - 2 ; case 0
	.short _02254A78 - _02254A5C - 2 ; case 1
	.short _02254A86 - _02254A5C - 2 ; case 2
	.short _02254A96 - _02254A5C - 2 ; case 3
	.short _02254AA4 - _02254A5C - 2 ; case 4
	.short _02254AB4 - _02254A5C - 2 ; case 5
_02254A68:
	ldrh r0, [r4, #0xe]
	mov r1, #0
	mvn r1, r1
	mov r2, #0
	bl MOD38_02254B6C
	strh r0, [r4, #0xe]
	b _02254AC0
_02254A78:
	ldrh r0, [r4, #0xe]
	mov r1, #1
	mov r2, #0
	bl MOD38_02254B6C
	strh r0, [r4, #0xe]
	b _02254AC0
_02254A86:
	ldrh r0, [r4, #0x10]
	mov r1, #0
	mvn r1, r1
	mov r2, #0
	bl MOD38_02254B6C
	strh r0, [r4, #0x10]
	b _02254AC0
_02254A96:
	ldrh r0, [r4, #0x10]
	mov r1, #1
	mov r2, #0
	bl MOD38_02254B6C
	strh r0, [r4, #0x10]
	b _02254AC0
_02254AA4:
	ldrh r0, [r4, #0x12]
	mov r1, #0
	mvn r1, r1
	mov r2, #1
	bl MOD38_02254B6C
	strh r0, [r4, #0x12]
	b _02254AC0
_02254AB4:
	ldrh r0, [r4, #0x12]
	mov r1, #1
	add r2, r1, #0
	bl MOD38_02254B6C
	strh r0, [r4, #0x12]
_02254AC0:
	ldrh r0, [r4, #0xe]
	ldrh r1, [r4, #0x10]
	ldrh r2, [r4, #0x12]
	bl MOD38_02254B2C
	strh r0, [r4, #0xc]
	ldr r0, [r4, #0x14]
	mov r1, #3
	bl MOD38_02254D34
	ldr r0, [r4, #0x14]
	mov r1, #4
	bl MOD38_02254D34
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AF2
_02254AE4:
	ldr r0, [r4, #0x14]
	bl MOD38_02254D64
	cmp r0, #0
	beq _02254AF2
	mov r0, #0
	strb r0, [r4, #1]
_02254AF2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD38_022549EC

	thumb_func_start MOD38_02254AF8
MOD38_02254AF8: ; 0x02254AF8
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254B08
	cmp r0, #1
	beq _02254B18
	b _02254B26
_02254B08:
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl MOD38_02254D34
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B26
_02254B18:
	ldr r0, [r4, #0x14]
	bl MOD38_02254D64
	cmp r0, #0
	beq _02254B26
	mov r0, #1
	pop {r4, pc}
_02254B26:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD38_02254AF8

	thumb_func_start MOD38_02254B2C
MOD38_02254B2C: ; 0x02254B2C
	push {r4, r5}
	ldr r5, _02254B68 ; =MOD38_02255134
	mov r3, #0x12
	add r4, r0, #0
	mul r4, r3
	add r4, r5, r4
	add r0, r3, #0
	ldrsb r5, [r4, r1]
	sub r0, #0x1c
	cmp r5, r0
	beq _02254B4E
	cmp r2, #0x12
	beq _02254B54
	ldrsb r0, [r4, r2]
	sub r3, #0x1c
	cmp r0, r3
	bne _02254B54
_02254B4E:
	mov r0, #0
	pop {r4, r5}
	bx lr
_02254B54:
	mov r0, #3
	add r0, r0, r5
	cmp r2, #0x12
	beq _02254B64
	cmp r2, r1
	beq _02254B64
	ldrsb r1, [r4, r2]
	add r0, r0, r1
_02254B64:
	pop {r4, r5}
	bx lr
	.align 2, 0
_02254B68: .word MOD38_02255134
	thumb_func_end MOD38_02254B2C

	thumb_func_start MOD38_02254B6C
MOD38_02254B6C: ; 0x02254B6C
	push {r4, r5}
	ldr r5, _02254BC0 ; =MOD38_02255278
	mov r4, #0
_02254B72:
	ldrb r3, [r5]
	cmp r3, r0
	beq _02254B80
	add r4, r4, #1
	add r5, r5, #1
	cmp r4, #0x11
	blo _02254B72
_02254B80:
	cmp r4, #0x11
	bne _02254B94
	cmp r1, #0
	ble _02254B8E
	mov r0, #0
	pop {r4, r5}
	bx lr
_02254B8E:
	mov r0, #8
	pop {r4, r5}
	bx lr
_02254B94:
	add r4, r4, r1
	cmp r4, #0x11
	blt _02254BA6
	cmp r2, #0
	beq _02254BA4
	mov r0, #0x12
	pop {r4, r5}
	bx lr
_02254BA4:
	mov r4, #0
_02254BA6:
	cmp r4, #0
	bge _02254BB6
	cmp r2, #0
	beq _02254BB4
	mov r0, #0x12
	pop {r4, r5}
	bx lr
_02254BB4:
	mov r4, #0x10
_02254BB6:
	ldr r0, _02254BC0 ; =MOD38_02255278
	ldrb r0, [r0, r4]
	pop {r4, r5}
	bx lr
	nop
_02254BC0: .word MOD38_02255278
	thumb_func_end MOD38_02254B6C

	thumb_func_start MOD38_02254BC4
MOD38_02254BC4: ; 0x02254BC4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0xc0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254C2A
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x30]
	ldr r2, _02254C30 ; =0x00000235
	mov r0, #1
	mov r1, #0x1a
	mov r3, #8
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0xb4
	str r0, [r1]
	ldr r2, _02254C34 ; =0x00000195
	mov r0, #1
	mov r1, #0x1a
	mov r3, #8
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r1, #0xb8
	str r0, [r1]
	mov r0, #0x80
	mov r1, #8
	bl String_ctor
	add r1, r4, #0
	add r1, #0xbc
	str r0, [r1]
	add r0, r4, #0
	bl MOD38_02254C38
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254C2A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02254C30: .word 0x00000235
_02254C34: .word 0x00000195
	thumb_func_end MOD38_02254BC4

	thumb_func_start MOD38_02254C38
MOD38_02254C38: ; 0x02254C38
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r6, r0, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x40
	bl GfGfxLoader_LoadWholePalette
	mov r0, #8
	str r0, [sp]
	add r0, r6, #0
	add r0, #0x60
	mov r1, #0xc
	mov r2, #0x3e
	mov r3, #0x3f
	bl MOD20_02253FBC
	add r0, r6, #0
	str r0, [sp, #0xc]
	add r0, #0x60
	ldr r4, _02254CBC ; =MOD38_02255300
	mov r7, #0
	add r5, r6, #0
	str r0, [sp, #0xc]
_02254C72:
	ldr r0, [r6, #0x30]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	bl MOD20_02253E74
	str r0, [r5, #0x34]
	add r7, r7, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r7, #6
	blt _02254C72
	add r0, r6, #0
	str r0, [sp, #0x10]
	add r0, #0x60
	mov r7, #0
	add r4, r6, #0
	mov r5, #0x2c
	str r0, [sp, #0x10]
_02254C96:
	ldr r0, [r6, #0x30]
	ldr r1, _02254CC0 ; =MOD38_0225528C
	ldr r2, [sp, #0x10]
	bl MOD20_02253E74
	mov r2, #3
	lsl r1, r5, #0xc
	lsl r2, r2, #0x10
	str r0, [r4, #0x4c]
	bl MOD20_02253F64
	add r7, r7, #1
	add r4, r4, #4
	add r5, #8
	cmp r7, #5
	blt _02254C96
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02254CBC: .word MOD38_02255300
_02254CC0: .word MOD38_0225528C
	thumb_func_end MOD38_02254C38

	thumb_func_start MOD38_02254CC4
MOD38_02254CC4: ; 0x02254CC4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
_02254CCC:
	ldr r1, [r4, #0x34]
	cmp r1, #0
	beq _02254CD8
	ldr r0, [r5, #0x30]
	bl MOD20_02253F14
_02254CD8:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #6
	blt _02254CCC
	mov r6, #0
	add r4, r5, #0
_02254CE4:
	ldr r1, [r4, #0x4c]
	cmp r1, #0
	beq _02254CF0
	ldr r0, [r5, #0x30]
	bl MOD20_02253F14
_02254CF0:
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #5
	blt _02254CE4
	add r5, #0x60
	add r0, r5, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD38_02254CC4

	thumb_func_start MOD38_02254D04
MOD38_02254D04: ; 0x02254D04
	push {r4, lr}
	add r4, r0, #0
	beq _02254D32
	add r0, #0xbc
	ldr r0, [r0]
	bl String_dtor
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	bl DestroyMsgData
	add r0, r4, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl DestroyMsgData
	add r0, r4, #0
	bl MOD38_02254CC4
	add r0, r4, #0
	bl FreeToHeap
_02254D32:
	pop {r4, pc}
	thumb_func_end MOD38_02254D04

	thumb_func_start MOD38_02254D34
MOD38_02254D34: ; 0x02254D34
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254D54 ; =MOD38_022552B8
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254D54: .word MOD38_022552B8
	thumb_func_end MOD38_02254D34

	thumb_func_start MOD38_02254D58
MOD38_02254D58: ; 0x02254D58
	ldr r3, _02254D60 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254D60: .word MOD20_02253794
	thumb_func_end MOD38_02254D58

	thumb_func_start MOD38_02254D64
MOD38_02254D64: ; 0x02254D64
	ldr r3, _02254D6C ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254D6C: .word MOD20_022537B8
	thumb_func_end MOD38_02254D64

	thumb_func_start MOD38_02254D70
MOD38_02254D70: ; 0x02254D70
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD38_02254D70

	thumb_func_start MOD38_02254D84
MOD38_02254D84: ; 0x02254D84
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r7, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254E1C ; =MOD38_0225529C
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
	mov r1, #0x3d
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x3c
	mov r3, #6
	bl GfGfxLoader_LoadScrnData
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	add r0, r5, #0
	add r1, r7, #0
	lsr r2, r4, #5
	bl MOD38_02254E28
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254E20 ; =0x04001000
	ldr r0, _02254E24 ; =0xFFFFE0FF
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
	add r0, r6, #0
	bl MOD38_02254D70
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02254E1C: .word MOD38_0225529C
_02254E20: .word 0x04001000
_02254E24: .word 0xFFFFE0FF
	thumb_func_end MOD38_02254D84

	thumb_func_start MOD38_02254E28
MOD38_02254E28: ; 0x02254E28
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0xf
	add r4, r2, #0
	str r0, [sp]
	mov r2, #6
	str r2, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	add r6, r1, #0
	str r0, [sp, #0x10]
	add r1, r5, #0
	ldr r0, [r5, #4]
	add r1, #0x74
	add r3, r2, #0
	bl FUN_02019064
	mov r0, #4
	str r0, [sp]
	mov r2, #6
	add r1, r5, #0
	str r2, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0xc
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, #0x84
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #8
	str r0, [sp]
	mov r2, #6
	add r1, r5, #0
	str r2, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x18
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, #0x94
	mov r3, #0x10
	bl FUN_02019064
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x16
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	add r1, r5, #0
	add r4, #0x24
	str r0, [sp, #0xc]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	add r1, #0xa4
	mov r2, #6
	mov r3, #3
	bl FUN_02019064
	add r0, r5, #0
	add r0, #0x74
	bl PutWindowTilemap
	add r0, r5, #0
	add r0, #0x84
	bl PutWindowTilemap
	add r0, r5, #0
	add r0, #0x94
	bl PutWindowTilemap
	add r0, r5, #0
	add r0, #0xa4
	bl PutWindowTilemap
	add r0, r5, #0
	add r1, r6, #0
	bl MOD38_02254FCC
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD38_02254E28

	thumb_func_start MOD38_02254EF4
MOD38_02254EF4: ; 0x02254EF4
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x74
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x84
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x94
	bl FUN_02019178
	add r4, #0xa4
	add r0, r4, #0
	bl FUN_02019178
	pop {r4, pc}
	thumb_func_end MOD38_02254EF4

	thumb_func_start MOD38_02254F18
MOD38_02254F18: ; 0x02254F18
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD38_02254EF4
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD38_02254D70
	pop {r3, r4, r5, pc}
	thumb_func_end MOD38_02254F18

	thumb_func_start MOD38_02254F38
MOD38_02254F38: ; 0x02254F38
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	ldr r2, [r0]
	mov r1, #1
	add r0, r2, #0
	tst r0, r1
	beq _02254F56
	mov r1, #3
_02254F56:
	lsl r0, r2, #2
	add r0, r4, r0
	ldr r0, [r0, #0x34]
	bl MOD20_02253F28
	ldr r0, _02254F70 ; =0x00000663
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD38_02254D70
	pop {r3, r4, r5, pc}
	nop
_02254F70: .word 0x00000663
	thumb_func_end MOD38_02254F38

	thumb_func_start MOD38_02254F74
MOD38_02254F74: ; 0x02254F74
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	ldr r2, [r0]
	mov r0, #1
	tst r0, r2
	beq _02254F92
	mov r1, #2
	b _02254F94
_02254F92:
	mov r1, #0
_02254F94:
	lsl r0, r2, #2
	add r0, r4, r0
	ldr r0, [r0, #0x34]
	bl MOD20_02253F28
	add r0, r5, #0
	bl MOD38_02254D70
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD38_02254F74

	thumb_func_start MOD38_02254FA8
MOD38_02254FA8: ; 0x02254FA8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r1, r0, #0
	add r0, r4, #0
	bl MOD38_02254FCC
	add r0, r5, #0
	bl MOD38_02254D70
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD38_02254FA8

	thumb_func_start MOD38_02254FCC
MOD38_02254FCC: ; 0x02254FCC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r1, r5, #0
	ldrh r2, [r4, #6]
	add r1, #0x74
	bl MOD38_0225500C
	add r1, r5, #0
	ldrh r2, [r4, #8]
	add r0, r5, #0
	add r1, #0x84
	bl MOD38_0225500C
	add r1, r5, #0
	ldrh r2, [r4, #0xa]
	add r0, r5, #0
	add r1, #0x94
	bl MOD38_0225500C
	add r1, r5, #0
	ldrh r2, [r4, #4]
	add r0, r5, #0
	add r1, #0xa4
	bl MOD38_02255084
	ldrh r1, [r4, #4]
	add r0, r5, #0
	bl MOD38_022550D0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD38_02254FCC

	thumb_func_start MOD38_0225500C
MOD38_0225500C: ; 0x0225500C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #4
	add r6, r2, #0
	bl FillWindowPixelBuffer
	cmp r6, #0x12
	bne _02255036
	add r0, r5, #0
	add r2, r5, #0
	add r0, #0xb8
	add r2, #0xbc
	ldr r0, [r0]
	ldr r2, [r2]
	mov r1, #6
	bl ReadMsgDataIntoString
	b _02255048
_02255036:
	add r0, r5, #0
	add r2, r5, #0
	add r0, #0xb4
	add r2, #0xbc
	ldr r0, [r0]
	ldr r2, [r2]
	add r1, r6, #0
	bl ReadMsgDataIntoString
_02255048:
	add r1, r5, #0
	add r1, #0xbc
	mov r0, #0
	ldr r1, [r1]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02255080 ; =0x00010104
	add r5, #0xbc
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5]
	mov r5, #0x30
	sub r3, r5, r3
	add r0, r4, #0
	lsr r3, r3, #1
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_02255080: .word 0x00010104
	thumb_func_end MOD38_0225500C

	thumb_func_start MOD38_02255084
MOD38_02255084: ; 0x02255084
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #4
	add r6, r2, #0
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r2, r5, #0
	add r0, #0xb8
	add r2, #0xbc
	ldr r0, [r0]
	ldr r2, [r2]
	add r1, r6, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _022550CC ; =0x00010104
	add r5, #0xbc
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r5]
	add r0, r4, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl FUN_02019548
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_022550CC: .word 0x00010104
	thumb_func_end MOD38_02255084

	thumb_func_start MOD38_022550D0
MOD38_022550D0: ; 0x022550D0
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r6, r1, #0
	ldr r4, _0225510C ; =0x00000000
	beq _022550EE
	add r5, r0, #0
	mov r7, #4
_022550DE:
	ldr r0, [r5, #0x4c]
	add r1, r7, #0
	bl MOD20_02253F28
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r6
	blo _022550DE
_022550EE:
	cmp r4, #5
	bhs _0225510A
	ldr r0, [sp]
	lsl r1, r4, #2
	add r5, r0, r1
	mov r6, #5
_022550FA:
	ldr r0, [r5, #0x4c]
	add r1, r6, #0
	bl MOD20_02253F28
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blo _022550FA
_0225510A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225510C: .word 0x00000000
	thumb_func_end MOD38_022550D0

	.section .rodata

	.global MOD38_02255110
MOD38_02255110: ; 0x02255110
	.word MOD38_022549AC, MOD38_022549EC, MOD38_02254AF8

	.global MOD38_0225511C
MOD38_0225511C: ; 0x0225511C
	.byte 0x70, 0x90, 0x10, 0x28
	.byte 0x70, 0x90, 0x68, 0x80, 0x18, 0x38, 0x60, 0x78, 0x18, 0x38, 0xB8, 0xD0, 0x38, 0x58, 0x60, 0x78
	.byte 0x38, 0x58, 0xB8, 0xD0

	.global MOD38_02255134
MOD38_02255134: ; 0x02255134
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xF6, 0xFF, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xF6, 0x01, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00
	.byte 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0xFF, 0xF6, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF6, 0x01
	.byte 0x00, 0x01, 0xFF, 0x00, 0x01, 0x00, 0x01, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
	.byte 0x01, 0x00, 0xFF, 0x00, 0x01, 0x00, 0xFF, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x01, 0x00, 0x01, 0x00
	.byte 0x00, 0x01, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF
	.byte 0x00, 0xFF, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00
	.byte 0x01, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF
	.byte 0x01, 0x01, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00
	.byte 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00
	.byte 0x00, 0xF6, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0x00
	.byte 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF

	.global MOD38_02255278
MOD38_02255278: ; 0x02255278
	.byte 0x00, 0x0A, 0x0B, 0x0D, 0x0C, 0x0F, 0x01, 0x03
	.byte 0x04, 0x02, 0x0E, 0x06, 0x05, 0x07, 0x10, 0x11, 0x08, 0x00, 0x00, 0x00

	.global MOD38_0225528C
MOD38_0225528C: ; 0x0225528C
	.byte 0x00, 0xC0, 0x02, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00

	.global MOD38_0225529C
MOD38_0225529C: ; 0x0225529C
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD38_022552B8
MOD38_022552B8: ; 0x022552B8
	.word 0x00, MOD38_02254D84, 0x00
	.word 0x01, MOD38_02254F18, 0x00
	.word 0x02, MOD38_02254F38, 0x00
	.word 0x03, MOD38_02254F74, 0x00
	.word 0x04, MOD38_02254FA8, 0x00
	.word 0x00, 0x00000000, 0x00

	.global MOD38_02255300
MOD38_02255300: ; 0x02255300
	.byte 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0x06, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x0C, 0x00, 0x00, 0x80, 0x02, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0xC0, 0x06, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x40, 0x0C, 0x00, 0x00, 0x80, 0x04, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
