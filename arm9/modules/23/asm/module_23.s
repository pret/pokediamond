	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD23_02254854
MOD23_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x28
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254888
	ldr r1, [sp]
	add r2, r7, #0
	bl MOD23_02254890
	cmp r0, #0
	beq _02254888
	ldr r0, _0225488C ; =MOD23_0225494C
	str r6, [r4, #0x10]
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02254888:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225488C: .word MOD23_0225494C
	thumb_func_end MOD23_02254854

	thumb_func_start MOD23_02254890
MOD23_02254890: ; 0x02254890
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r1, r4, #0
	add r0, #0x14
	add r1, #0x18
	bl MOD23_02254FFC
	cmp r0, #0
	beq _0225490A
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	strb r0, [r4, #3]
	strb r0, [r4, #2]
	strb r0, [r4, #4]
	mov r0, #0x11
	strh r0, [r4, #6]
	sub r0, #0x12
	str r0, [r4, #8]
	add r0, r4, #0
	add r0, #0x1c
	mov r1, #0xa
	bl MOD23_0225551C
	add r0, r4, #0
	add r0, #0x20
	mov r1, #0xa
	bl MOD23_0225551C
	add r0, r4, #0
	add r0, #0x24
	mov r1, #0xa
	bl MOD23_0225551C
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _022548E8
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _022548E8
	ldr r0, [r4, #0x24]
	cmp r0, #0
	bne _022548EE
_022548E8:
	add sp, #4
	mov r0, #0
	pop {r3, r4, pc}
_022548EE:
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254910 ; =MOD23_02255CD8
	ldr r2, _02254914 ; =MOD23_022549C4
	mov r1, #0x11
	add r3, r4, #0
	bl MOD20_02254130
	str r0, [r4, #0xc]
	cmp r0, #0
	bne _0225490A
	add sp, #4
	mov r0, #0
	pop {r3, r4, pc}
_0225490A:
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02254910: .word MOD23_02255CD8
_02254914: .word MOD23_022549C4
	thumb_func_end MOD23_02254890

	thumb_func_start MOD23_02254918
MOD23_02254918: ; 0x02254918
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _02254926
	bl MOD23_02255540
_02254926:
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _02254930
	bl MOD23_02255540
_02254930:
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _0225493A
	bl MOD23_02255540
_0225493A:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02254944
	bl MOD20_02254198
_02254944:
	ldr r0, [r4, #0x14]
	bl MOD23_0225502C
	pop {r4, pc}
	thumb_func_end MOD23_02254918

	thumb_func_start MOD23_0225494C
MOD23_0225494C: ; 0x0225494C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #3]
	cmp r0, #0
	beq _02254964
	add r0, r4, #0
	mov r1, #6
	bl MOD23_022549AC
	mov r0, #0
	strb r0, [r4, #3]
_02254964:
	ldrb r0, [r4]
	cmp r0, #7
	bhs _0225499E
	mov r0, #0x11
	strh r0, [r4, #6]
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0xc]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022549A0 ; =MOD23_02255CBC
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225499E
	add r0, r4, #0
	bl MOD23_02254918
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x10]
	bl MOD20_022529A0
_0225499E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022549A0: .word MOD23_02255CBC
	thumb_func_end MOD23_0225494C

	thumb_func_start MOD23_022549A4
MOD23_022549A4: ; 0x022549A4
	mov r1, #1
	strb r1, [r0, #3]
	bx lr
	.align 2, 0
	thumb_func_end MOD23_022549A4

	thumb_func_start MOD23_022549AC
MOD23_022549AC: ; 0x022549AC
	ldrb r2, [r0, #3]
	cmp r2, #0
	bne _022549B4
	b _022549B6
_022549B4:
	mov r1, #6
_022549B6:
	strb r1, [r0]
	ldrb r1, [r0]
	strb r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD23_022549AC

	thumb_func_start MOD23_022549C4
MOD23_022549C4: ; 0x022549C4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r4, r3, #0
	cmp r2, #0
	beq _022549D6
	cmp r2, #1
	beq _022549E2
	b _022549EC
_022549D6:
	strh r5, [r4, #0x18]
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl MOD23_02255038
	b _022549EC
_022549E2:
	strh r5, [r4, #0x18]
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl MOD23_02255038
_022549EC:
	cmp r6, #3
	bne _022549F2
	strh r5, [r4, #6]
_022549F2:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD23_022549C4

	thumb_func_start MOD23_022549F4
MOD23_022549F4: ; 0x022549F4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A04
	cmp r0, #1
	beq _02254A14
	b _02254A2E
_02254A04:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A2E
_02254A14:
	ldr r0, [r4, #0x14]
	mov r1, #0
	bl MOD23_0225505C
	cmp r0, #0
	beq _02254A2E
	ldr r0, [r4, #0x10]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD23_022549AC
_02254A2E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_022549F4

	thumb_func_start MOD23_02254A34
MOD23_02254A34: ; 0x02254A34
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254A44
	cmp r1, #1
	beq _02254AE8
	b _02254B08
_02254A44:
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #8]
	ldrh r1, [r4, #6]
	add r2, r1, #0
	sub r2, #0xa
	cmp r2, #7
	bhi _02254A9E
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02254A60: ; jump table
	.short _02254A7A - _02254A60 - 2 ; case 0
	.short _02254A80 - _02254A60 - 2 ; case 1
	.short _02254A80 - _02254A60 - 2 ; case 2
	.short _02254A80 - _02254A60 - 2 ; case 3
	.short _02254A80 - _02254A60 - 2 ; case 4
	.short _02254A90 - _02254A60 - 2 ; case 5
	.short _02254A70 - _02254A60 - 2 ; case 6
	.short _02254AC0 - _02254A60 - 2 ; case 7
_02254A70:
	bl MOD23_02254EE8
	mov r0, #4
	str r0, [r4, #8]
	b _02254AC0
_02254A7A:
	mov r0, #1
	strb r0, [r4, #4]
	b _02254AC0
_02254A80:
	strh r1, [r4, #0x1a]
	mov r0, #0
	strb r0, [r4, #4]
	mov r0, #8
	str r0, [r4, #8]
	mov r0, #2
	strb r0, [r4, #2]
	b _02254AC0
_02254A90:
	ldr r1, [r4, #0x1c]
	bl MOD23_02254F94
	ldr r0, [r4, #0x1c]
	bl MOD23_02255548
	b _02254AC0
_02254A9E:
	ldrb r0, [r4, #4]
	cmp r0, #0
	ldr r0, [r4, #0x1c]
	beq _02254AB4
	bl MOD23_02255838
	cmp r0, #0
	beq _02254AC0
	mov r0, #3
	str r0, [r4, #8]
	b _02254AC0
_02254AB4:
	bl MOD23_022557FC
	cmp r0, #0
	beq _02254AC0
	mov r0, #3
	str r0, [r4, #8]
_02254AC0:
	mov r0, #0
	ldr r1, [r4, #8]
	mvn r0, r0
	cmp r1, r0
	beq _02254AD8
	ldr r0, [r4, #0x14]
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254B08
_02254AD8:
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254B08
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254B08
_02254AE8:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #8]
	bl MOD23_0225505C
	cmp r0, #0
	beq _02254B08
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254B04
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254B08
_02254B04:
	mov r0, #0
	strb r0, [r4, #1]
_02254B08:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD23_02254A34

	thumb_func_start MOD23_02254B0C
MOD23_02254B0C: ; 0x02254B0C
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254B1C
	cmp r1, #1
	beq _02254BE4
	b _02254C04
_02254B1C:
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #8]
	ldrh r1, [r4, #6]
	add r2, r1, #0
	sub r2, #0xa
	cmp r2, #7
	bhi _02254BA2
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02254B38: ; jump table
	.short _02254B56 - _02254B38 - 2 ; case 0
	.short _02254B6A - _02254B38 - 2 ; case 1
	.short _02254B6A - _02254B38 - 2 ; case 2
	.short _02254B6A - _02254B38 - 2 ; case 3
	.short _02254B6A - _02254B38 - 2 ; case 4
	.short _02254B72 - _02254B38 - 2 ; case 5
	.short _02254B48 - _02254B38 - 2 ; case 6
	.short _02254BBC - _02254B38 - 2 ; case 7
_02254B48:
	bl MOD23_02254EE8
	mov r0, #4
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #2]
	b _02254BBC
_02254B56:
	ldr r0, [r4, #0x20]
	bl MOD23_02255548
	mov r0, #5
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #4]
	mov r0, #3
	strb r0, [r4, #2]
	b _02254BBC
_02254B6A:
	strh r1, [r4, #0x1a]
	mov r0, #8
	str r0, [r4, #8]
	b _02254BBC
_02254B72:
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	bl MOD23_02255558
	ldrh r1, [r4, #0x1a]
	add r0, r4, #0
	bl MOD23_02254F08
	cmp r0, #0
	beq _02254B98
	ldr r1, [r4, #0x24]
	add r0, r4, #0
	bl MOD23_02254F94
	mov r0, #6
	str r0, [r4, #8]
	mov r0, #4
	strb r0, [r4, #2]
	b _02254BBC
_02254B98:
	mov r0, #9
	str r0, [r4, #8]
	mov r0, #5
	strb r0, [r4, #2]
	b _02254BBC
_02254BA2:
	ldr r0, [r4, #0x20]
	bl MOD23_02255548
	ldrh r1, [r4, #6]
	ldr r0, [r4, #0x20]
	bl MOD23_022557FC
	cmp r0, #0
	beq _02254BBC
	mov r0, #5
	str r0, [r4, #8]
	mov r0, #3
	strb r0, [r4, #2]
_02254BBC:
	mov r0, #0
	ldr r1, [r4, #8]
	mvn r0, r0
	cmp r1, r0
	beq _02254BD4
	ldr r0, [r4, #0x14]
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C04
_02254BD4:
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254C04
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254C04
_02254BE4:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #8]
	bl MOD23_0225505C
	cmp r0, #0
	beq _02254C04
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254C00
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254C04
_02254C00:
	mov r0, #0
	strb r0, [r4, #1]
_02254C04:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD23_02254B0C

	thumb_func_start MOD23_02254C08
MOD23_02254C08: ; 0x02254C08
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254C18
	cmp r1, #1
	beq _02254CFA
	b _02254D1A
_02254C18:
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #8]
	ldrh r1, [r4, #6]
	add r2, r1, #0
	sub r2, #0xa
	cmp r2, #7
	bhi _02254CB0
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02254C34: ; jump table
	.short _02254C52 - _02254C34 - 2 ; case 0
	.short _02254C58 - _02254C34 - 2 ; case 1
	.short _02254C58 - _02254C34 - 2 ; case 2
	.short _02254C58 - _02254C34 - 2 ; case 3
	.short _02254C58 - _02254C34 - 2 ; case 4
	.short _02254C86 - _02254C34 - 2 ; case 5
	.short _02254C44 - _02254C34 - 2 ; case 6
	.short _02254CD2 - _02254C34 - 2 ; case 7
_02254C44:
	bl MOD23_02254EE8
	mov r0, #4
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #2]
	b _02254CD2
_02254C52:
	mov r0, #1
	strb r0, [r4, #4]
	b _02254CD2
_02254C58:
	ldrh r1, [r4, #0x1a]
	bl MOD23_02254F08
	cmp r0, #0
	beq _02254C7C
	ldrh r0, [r4, #6]
	strh r0, [r4, #0x1a]
	mov r0, #0
	strb r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x24]
	bl MOD23_02255558
	mov r0, #7
	str r0, [r4, #8]
	mov r0, #2
	strb r0, [r4, #2]
	b _02254CD2
_02254C7C:
	mov r0, #9
	str r0, [r4, #8]
	mov r0, #5
	strb r0, [r4, #2]
	b _02254CD2
_02254C86:
	ldrh r1, [r4, #0x1a]
	bl MOD23_02254F08
	cmp r0, #0
	beq _02254CA6
	ldr r1, [r4, #0x24]
	add r0, r4, #0
	bl MOD23_02254F94
	mov r0, #6
	str r0, [r4, #8]
	mov r0, #0
	strb r0, [r4, #4]
	mov r0, #4
	strb r0, [r4, #2]
	b _02254CD2
_02254CA6:
	mov r0, #9
	str r0, [r4, #8]
	mov r0, #5
	strb r0, [r4, #2]
	b _02254CD2
_02254CB0:
	ldrb r0, [r4, #4]
	cmp r0, #0
	ldr r0, [r4, #0x20]
	beq _02254CC6
	bl MOD23_02255838
	cmp r0, #0
	beq _02254CD2
	mov r0, #5
	str r0, [r4, #8]
	b _02254CD2
_02254CC6:
	bl MOD23_022557FC
	cmp r0, #0
	beq _02254CD2
	mov r0, #5
	str r0, [r4, #8]
_02254CD2:
	mov r0, #0
	ldr r1, [r4, #8]
	mvn r0, r0
	cmp r1, r0
	beq _02254CEA
	ldr r0, [r4, #0x14]
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254D1A
_02254CEA:
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254D1A
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254D1A
_02254CFA:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #8]
	bl MOD23_0225505C
	cmp r0, #0
	beq _02254D1A
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254D16
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254D1A
_02254D16:
	mov r0, #0
	strb r0, [r4, #1]
_02254D1A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_02254C08

	thumb_func_start MOD23_02254D20
MOD23_02254D20: ; 0x02254D20
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254D30
	cmp r1, #1
	beq _02254E04
	b _02254E24
_02254D30:
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #8]
	ldrh r1, [r4, #6]
	add r2, r1, #0
	sub r2, #0xa
	cmp r2, #7
	bhi _02254DC2
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02254D4C: ; jump table
	.short _02254D6A - _02254D4C - 2 ; case 0
	.short _02254D7A - _02254D4C - 2 ; case 1
	.short _02254D7A - _02254D4C - 2 ; case 2
	.short _02254D7A - _02254D4C - 2 ; case 3
	.short _02254D7A - _02254D4C - 2 ; case 4
	.short _02254D92 - _02254D4C - 2 ; case 5
	.short _02254D5C - _02254D4C - 2 ; case 6
	.short _02254DDC - _02254D4C - 2 ; case 7
_02254D5C:
	bl MOD23_02254EE8
	mov r0, #4
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #2]
	b _02254DDC
_02254D6A:
	bl MOD23_02254EE8
	mov r0, #3
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #4]
	strb r0, [r4, #2]
	b _02254DDC
_02254D7A:
	strh r1, [r4, #0x1a]
	mov r0, #8
	str r0, [r4, #8]
	mov r0, #0
	strb r0, [r4, #4]
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x24]
	bl MOD23_02255558
	mov r0, #2
	strb r0, [r4, #2]
	b _02254DDC
_02254D92:
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x24]
	bl MOD23_02255558
	ldrh r1, [r4, #0x1a]
	add r0, r4, #0
	bl MOD23_02254F08
	cmp r0, #0
	beq _02254DB8
	ldr r1, [r4, #0x24]
	add r0, r4, #0
	bl MOD23_02254F94
	mov r0, #6
	str r0, [r4, #8]
	mov r0, #0
	strb r0, [r4, #4]
	b _02254DDC
_02254DB8:
	mov r0, #9
	str r0, [r4, #8]
	mov r0, #5
	strb r0, [r4, #2]
	b _02254DDC
_02254DC2:
	ldr r0, [r4, #0x1c]
	bl MOD23_02255548
	ldrh r1, [r4, #6]
	ldr r0, [r4, #0x1c]
	bl MOD23_022557FC
	cmp r0, #0
	beq _02254DD8
	mov r0, #3
	str r0, [r4, #8]
_02254DD8:
	mov r0, #1
	strb r0, [r4, #2]
_02254DDC:
	mov r0, #0
	ldr r1, [r4, #8]
	mvn r0, r0
	cmp r1, r0
	beq _02254DF4
	ldr r0, [r4, #0x14]
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254E24
_02254DF4:
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254E24
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254E24
_02254E04:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #8]
	bl MOD23_0225505C
	cmp r0, #0
	beq _02254E24
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254E20
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254E24
_02254E20:
	mov r0, #0
	strb r0, [r4, #1]
_02254E24:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD23_02254D20

	thumb_func_start MOD23_02254E28
MOD23_02254E28: ; 0x02254E28
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _02254E38
	cmp r1, #1
	beq _02254EC2
	b _02254EE2
_02254E38:
	mov r1, #0
	mvn r1, r1
	str r1, [r4, #8]
	ldrh r1, [r4, #6]
	sub r1, #0xa
	cmp r1, #7
	bhi _02254E80
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02254E52: ; jump table
	.short _02254E70 - _02254E52 - 2 ; case 0
	.short _02254E9A - _02254E52 - 2 ; case 1
	.short _02254E9A - _02254E52 - 2 ; case 2
	.short _02254E9A - _02254E52 - 2 ; case 3
	.short _02254E9A - _02254E52 - 2 ; case 4
	.short _02254E9A - _02254E52 - 2 ; case 5
	.short _02254E62 - _02254E52 - 2 ; case 6
	.short _02254E9A - _02254E52 - 2 ; case 7
_02254E62:
	bl MOD23_02254EE8
	mov r0, #3
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #2]
	b _02254E9A
_02254E70:
	bl MOD23_02254EE8
	mov r0, #3
	str r0, [r4, #8]
	mov r0, #1
	strb r0, [r4, #4]
	strb r0, [r4, #2]
	b _02254E9A
_02254E80:
	add r0, r4, #0
	bl MOD23_02254EE8
	ldrh r1, [r4, #6]
	ldr r0, [r4, #0x1c]
	bl MOD23_022557FC
	cmp r0, #0
	beq _02254E96
	mov r0, #3
	str r0, [r4, #8]
_02254E96:
	mov r0, #1
	strb r0, [r4, #2]
_02254E9A:
	mov r0, #0
	ldr r1, [r4, #8]
	mvn r0, r0
	cmp r1, r0
	beq _02254EB2
	ldr r0, [r4, #0x14]
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254EE2
_02254EB2:
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254EE2
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254EE2
_02254EC2:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #8]
	bl MOD23_0225505C
	cmp r0, #0
	beq _02254EE2
	ldrb r1, [r4, #2]
	ldrb r0, [r4]
	cmp r1, r0
	beq _02254EDE
	add r0, r4, #0
	bl MOD23_022549AC
	b _02254EE2
_02254EDE:
	mov r0, #0
	strb r0, [r4, #1]
_02254EE2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_02254E28

	thumb_func_start MOD23_02254EE8
MOD23_02254EE8: ; 0x02254EE8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	bl MOD23_02255548
	ldr r0, [r4, #0x20]
	bl MOD23_02255548
	ldr r0, [r4, #0x24]
	bl MOD23_02255548
	mov r0, #0x11
	strh r0, [r4, #0x1a]
	mov r0, #0
	strb r0, [r4, #4]
	pop {r4, pc}
	thumb_func_end MOD23_02254EE8

	thumb_func_start MOD23_02254F08
MOD23_02254F08: ; 0x02254F08
	push {r4, lr}
	sub r1, #0xb
	add r4, r0, #0
	cmp r1, #3
	bhi _02254F54
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254F1E: ; jump table
	.short _02254F32 - _02254F1E - 2 ; case 0
	.short _02254F26 - _02254F1E - 2 ; case 1
	.short _02254F3E - _02254F1E - 2 ; case 2
	.short _02254F4A - _02254F1E - 2 ; case 3
_02254F26:
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x24]
	bl MOD23_02255568
	b _02254F54
_02254F32:
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x24]
	bl MOD23_022555F4
	b _02254F54
_02254F3E:
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x24]
	bl MOD23_022556A8
	b _02254F54
_02254F4A:
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	ldr r2, [r4, #0x24]
	bl MOD23_022556D8
_02254F54:
	ldr r0, [r4, #0x24]
	mov r1, #0xa
	bl MOD23_022558C0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_02254F08

	thumb_func_start MOD23_02254F60
MOD23_02254F60: ; 0x02254F60
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254F70
	cmp r0, #1
	beq _02254F80
	b _02254F8E
_02254F70:
	ldr r0, [r4, #0x14]
	mov r1, #0xa
	bl MOD23_02255038
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254F8E
_02254F80:
	ldr r0, [r4, #0x14]
	bl MOD23_02255068
	cmp r0, #0
	beq _02254F8E
	mov r0, #1
	pop {r4, pc}
_02254F8E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_02254F60

	thumb_func_start MOD23_02254F94
MOD23_02254F94: ; 0x02254F94
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	bl MOD23_02255AE8
	add r4, r0, #0
	mov r2, #0
	mov r0, #0
	sub r0, r0, r4
	sbc r2, r1
	bge _02254FF4
	mov r2, #0
	ldr r0, _02254FF8 ; =0x000001ED
	sub r0, r0, r4
	sbc r2, r1
	blt _02254FF4
	ldr r0, [r5, #0x10]
	bl MOD20_02252C40
	bl FUN_02024DA0
	add r5, r0, #0
	bl Pokedex_GetNatDexFlag
	cmp r0, #0
	beq _02254FCE
	lsl r0, r4, #0x10
	lsr r4, r0, #0x10
	b _02254FD8
_02254FCE:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02069B60
	add r4, r0, #0
_02254FD8:
	cmp r4, #0
	beq _02254FF4
	ldr r0, _02254FF8 ; =0x000001ED
	cmp r4, r0
	bhi _02254FF4
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_020245F0
	cmp r0, #0
	beq _02254FF4
	add r0, r4, #0
	bl MOD20_02252B48
_02254FF4:
	pop {r3, r4, r5, pc}
	nop
_02254FF8: .word 0x000001ED
	thumb_func_end MOD23_02254F94

	thumb_func_start MOD23_02254FFC
MOD23_02254FFC: ; 0x02254FFC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r5, r0, #0
	ldr r1, _02255028 ; =0x0000048C
	mov r0, #8
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02255022
	str r6, [r4]
	str r7, [r4, #4]
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02255022:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255028: .word 0x0000048C
	thumb_func_end MOD23_02254FFC

	thumb_func_start MOD23_0225502C
MOD23_0225502C: ; 0x0225502C
	push {r3, lr}
	cmp r0, #0
	beq _02255036
	bl FreeToHeap
_02255036:
	pop {r3, pc}
	thumb_func_end MOD23_0225502C

	thumb_func_start MOD23_02255038
MOD23_02255038: ; 0x02255038
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02255058 ; =MOD23_02256040
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02255058: .word MOD23_02256040
	thumb_func_end MOD23_02255038

	thumb_func_start MOD23_0225505C
MOD23_0225505C: ; 0x0225505C
	ldr r3, _02255064 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02255064: .word MOD20_02253794
	thumb_func_end MOD23_0225505C

	thumb_func_start MOD23_02255068
MOD23_02255068: ; 0x02255068
	ldr r3, _02255070 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02255070: .word MOD20_022537B8
	thumb_func_end MOD23_02255068

	thumb_func_start MOD23_02255074
MOD23_02255074: ; 0x02255074
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_02255074

	thumb_func_start MOD23_02255088
MOD23_02255088: ; 0x02255088
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A4
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02255118 ; =MOD23_02255D1C
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
	mov r1, #0x10
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
	mov r1, #0x11
	mov r3, #6
	bl FUN_020068C8
	add r0, r5, #0
	bl MOD23_02255124
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _0225511C ; =0x04001000
	ldr r0, _02255120 ; =0xFFFFE0FF
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
	bl MOD23_02255074
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02255118: .word MOD23_02255D1C
_0225511C: .word 0x04001000
_02255120: .word 0xFFFFE0FF
	thumb_func_end MOD23_02255088

	thumb_func_start MOD23_02255124
MOD23_02255124: ; 0x02255124
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	ldr r0, [r6, #4]
	mov r1, #6
	bl FUN_0201886C
	mov ip, r0
	mov r0, #0
	ldr r3, _022551A0 ; =MOD23_02255FB8
	str r0, [sp, #4]
_0225513A:
	ldrb r7, [r3, #1]
	ldrb r0, [r3, #3]
	mov r2, #0
	add r0, r7, r0
	cmp r7, r0
	bhs _0225518C
	lsl r0, r7, #5
	str r0, [sp]
_0225514A:
	ldrb r1, [r3]
	ldrb r0, [r3, #2]
	add r0, r1, r0
	cmp r1, r0
	bhs _0225517A
	ldr r0, [sp]
	lsl r4, r0, #1
	mov r0, ip
	add r4, r0, r4
	lsl r0, r1, #1
	add r4, r4, r0
_02255160:
	lsl r5, r2, #1
	ldrh r0, [r4]
	add r5, r6, r5
	add r5, #0x4c
	strh r0, [r5]
	ldrb r5, [r3]
	ldrb r0, [r3, #2]
	add r1, r1, #1
	add r2, r2, #1
	add r0, r5, r0
	add r4, r4, #2
	cmp r1, r0
	blo _02255160
_0225517A:
	ldr r0, [sp]
	ldrb r1, [r3, #1]
	add r0, #0x20
	str r0, [sp]
	ldrb r0, [r3, #3]
	add r7, r7, #1
	add r0, r1, r0
	cmp r7, r0
	blo _0225514A
_0225518C:
	ldr r0, [sp, #4]
	add r3, r3, #4
	add r0, r0, #1
	add r6, #0x40
	str r0, [sp, #4]
	cmp r0, #0x11
	blo _0225513A
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022551A0: .word MOD23_02255FB8
	thumb_func_end MOD23_02255124

	thumb_func_start MOD23_022551A4
MOD23_022551A4: ; 0x022551A4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldrh r5, [r5]
	ldr r0, _022551F8 ; =0x00000663
	bl MOD20_02252B28
	lsl r3, r5, #2
	ldr r0, _022551FC ; =MOD23_02255FB9
	ldr r2, _02255200 ; =MOD23_02255FFC
	ldrb r0, [r0, r3]
	ldr r5, _02255204 ; =MOD23_02255FB8
	ldr r2, [r2, r3]
	str r0, [sp]
	ldr r0, _02255208 ; =MOD23_02255FBA
	mov r1, #6
	ldrb r0, [r0, r3]
	str r0, [sp, #4]
	ldr r0, _0225520C ; =MOD23_02255FBB
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02018148
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022551F8: .word 0x00000663
_022551FC: .word MOD23_02255FB9
_02255200: .word MOD23_02255FFC
_02255204: .word MOD23_02255FB8
_02255208: .word MOD23_02255FBA
_0225520C: .word MOD23_02255FBB
	thumb_func_end MOD23_022551A4

	thumb_func_start MOD23_02255210
MOD23_02255210: ; 0x02255210
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	ldrh r5, [r0]
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	lsl r3, r5, #2
	ldr r0, _02255260 ; =MOD23_02255FB9
	add r2, r4, #0
	ldrb r0, [r0, r3]
	add r2, #0x4c
	lsl r5, r5, #6
	str r0, [sp]
	ldr r0, _02255264 ; =MOD23_02255FBA
	add r2, r2, r5
	ldrb r0, [r0, r3]
	ldr r5, _02255268 ; =MOD23_02255FB8
	mov r1, #6
	str r0, [sp, #4]
	ldr r0, _0225526C ; =MOD23_02255FBB
	ldrb r0, [r0, r3]
	ldrb r3, [r5, r3]
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02018148
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02255260: .word MOD23_02255FB9
_02255264: .word MOD23_02255FBA
_02255268: .word MOD23_02255FB8
_0225526C: .word MOD23_02255FBB
	thumb_func_end MOD23_02255210

	thumb_func_start MOD23_02255270
MOD23_02255270: ; 0x02255270
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r5, #4]
	add r1, #0x30
	bl MOD23_022558EC
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x30
	bl MOD23_0225548C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	pop {r4, r5, r6, pc}
	thumb_func_end MOD23_02255270

	thumb_func_start MOD23_022552A8
MOD23_022552A8: ; 0x022552A8
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r5, #4]
	add r1, #0x30
	bl MOD23_022558EC
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x30
	bl MOD23_0225548C
	ldr r0, [r4, #4]
	bl MOD23_0225544C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD23_022552A8

	thumb_func_start MOD23_022552E8
MOD23_022552E8: ; 0x022552E8
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r5, #8]
	add r1, #0x30
	bl MOD23_022558EC
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x30
	bl MOD23_0225548C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	pop {r4, r5, r6, pc}
	thumb_func_end MOD23_022552E8

	thumb_func_start MOD23_02255320
MOD23_02255320: ; 0x02255320
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r5, #0xc]
	add r1, #0x30
	bl MOD23_022558EC
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x30
	bl MOD23_0225548C
	ldr r0, [r4, #4]
	bl MOD23_0225544C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD23_02255320

	thumb_func_start MOD23_02255360
MOD23_02255360: ; 0x02255360
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r5, #0xc]
	add r1, #0x30
	bl MOD23_022558EC
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x30
	bl MOD23_0225548C
	ldr r0, [r4, #4]
	add r1, r5, #0
	bl MOD23_02255410
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r6, #0
	bl MOD23_02255074
	pop {r4, r5, r6, pc}
	thumb_func_end MOD23_02255360

	thumb_func_start MOD23_022553A0
MOD23_022553A0: ; 0x022553A0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	mov r2, #0
	add r1, r4, #0
	mov r0, #0xc
_022553B2:
	add r2, r2, #1
	strh r0, [r1, #0x30]
	add r1, r1, #2
	cmp r2, #0xa
	blo _022553B2
	lsl r0, r2, #1
	mov r1, #0xd
	add r0, r4, r0
	strh r1, [r0, #0x30]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x30
	bl MOD23_0225548C
	ldr r0, [r4, #4]
	bl MOD23_0225544C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD23_02255074
	pop {r3, r4, r5, pc}
	thumb_func_end MOD23_022553A0

	thumb_func_start MOD23_022553E4
MOD23_022553E4: ; 0x022553E4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r1, r0, #0
	ldr r0, [r4, #4]
	bl MOD23_02255410
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD23_02255074
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD23_022553E4

	thumb_func_start MOD23_02255410
MOD23_02255410: ; 0x02255410
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	mov r1, #6
	add r4, r0, #0
	bl FUN_0201886C
	ldrh r1, [r5, #2]
	cmp r1, #0x11
	bne _0225542E
	add r0, r4, #0
	bl MOD23_0225544C
	add sp, #0xc
	pop {r4, r5, pc}
_0225542E:
	sub r1, #0xb
	lsl r1, r1, #1
	add r1, #0xf0
	str r1, [sp]
	mov r1, #0x28
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #3
	add r2, r1, #0
	mov r3, #0x20
	bl MOD20_022538BC
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD23_02255410

	thumb_func_start MOD23_0225544C
MOD23_0225544C: ; 0x0225544C
	push {lr}
	sub sp, #0xc
	mov r1, #6
	bl FUN_0201886C
	mov r1, #0x29
	str r1, [sp]
	mov r1, #0x28
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #8]
	mov r1, #3
	add r2, r1, #0
	mov r3, #0x20
	bl MOD20_022538BC
	add sp, #0xc
	pop {pc}
	thumb_func_end MOD23_0225544C

	thumb_func_start MOD23_02255470
MOD23_02255470: ; 0x02255470
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD23_02255074
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD23_02255470

	thumb_func_start MOD23_0225548C
MOD23_0225548C: ; 0x0225548C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r1, #0
	mov r1, #6
	bl FUN_0201886C
	add r7, r0, #0
	ldrh r0, [r6]
	mov r1, #0
	cmp r0, #0xd
	beq _022554AE
	add r2, r6, #0
_022554A4:
	add r2, r2, #2
	ldrh r0, [r2]
	add r1, r1, #1
	cmp r0, #0xd
	bne _022554A4
_022554AE:
	mov r0, #0xa
	mov r4, #0
	sub r0, r0, r1
	str r0, [sp, #0xc]
	beq _022554DC
	mov r5, #5
_022554BA:
	mov r0, #0x2b
	str r0, [sp]
	mov r0, #0x28
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #3
	mov r3, #0x20
	bl MOD20_022538BC
	ldr r0, [sp, #0xc]
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, r0
	blo _022554BA
_022554DC:
	mov r0, #0
	str r0, [sp, #0x10]
	cmp r4, #0xa
	bhs _02255516
	bhs _02255516
	lsl r0, r4, #1
	add r5, r0, #5
_022554EA:
	ldrh r0, [r6]
	add r1, r5, #0
	mov r2, #3
	lsl r0, r0, #1
	add r0, #0xa5
	str r0, [sp]
	mov r0, #0x28
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r7, #0
	mov r3, #0x20
	bl MOD20_022538BC
	ldr r0, [sp, #0x10]
	add r4, r4, #1
	add r0, r0, #1
	add r5, r5, #2
	add r6, r6, #2
	str r0, [sp, #0x10]
	cmp r4, #0xa
	blo _022554EA
_02255516:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD23_0225548C

	thumb_func_start MOD23_0225551C
MOD23_0225551C: ; 0x0225551C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #8
	mov r1, #0xc
	bl AllocFromHeap
	str r0, [r5]
	cmp r0, #0
	beq _0225553C
	strb r4, [r0, #0xa]
	ldr r0, [r5]
	bl MOD23_02255548
	mov r0, #1
	pop {r3, r4, r5, pc}
_0225553C:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD23_0225551C

	thumb_func_start MOD23_02255540
MOD23_02255540: ; 0x02255540
	ldr r3, _02255544 ; =FreeToHeap
	bx r3
	.align 2, 0
_02255544: .word FreeToHeap
	thumb_func_end MOD23_02255540

	thumb_func_start MOD23_02255548
MOD23_02255548: ; 0x02255548
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	strb r1, [r0, #9]
	strb r1, [r0, #8]
	strb r1, [r0, #0xb]
	bx lr
	.align 2, 0
	thumb_func_end MOD23_02255548

	thumb_func_start MOD23_02255558
MOD23_02255558: ; 0x02255558
	add r2, r1, #0
	add r3, r0, #0
	ldmia r2!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	str r0, [r3]
	bx lr
	.align 2, 0
	thumb_func_end MOD23_02255558

	thumb_func_start MOD23_02255568
MOD23_02255568: ; 0x02255568
	push {r4, r5, r6, lr}
	sub sp, #0x30
	add r5, r0, #0
	add r3, r1, #0
	ldrb r1, [r5, #9]
	add r4, r2, #0
	cmp r1, #0
	bne _0225559A
	ldrb r0, [r3, #9]
	cmp r0, #1
	bne _0225559A
	ldmia r3!, {r0, r1}
	add r6, sp, #0x24
	add r4, r6, #0
	stmia r6!, {r0, r1}
	ldr r0, [r3]
	add r1, r4, #0
	str r0, [r6]
	mov r0, #0
	strb r0, [r4, #9]
	add r0, r5, #0
	bl MOD23_022555F4
	add sp, #0x30
	pop {r4, r5, r6, pc}
_0225559A:
	cmp r1, #1
	bne _022555C2
	ldrb r0, [r3, #9]
	cmp r0, #0
	bne _022555C2
	ldmia r5!, {r0, r1}
	add r6, sp, #0x18
	add r2, r6, #0
	stmia r6!, {r0, r1}
	ldr r0, [r5]
	add r1, r2, #0
	str r0, [r6]
	mov r0, #0
	strb r0, [r2, #9]
	add r0, r3, #0
	add r2, r4, #0
	bl MOD23_022555F4
	add sp, #0x30
	pop {r4, r5, r6, pc}
_022555C2:
	add r1, r3, #0
	add r0, r5, #0
	add r2, sp, #0xc
	add r3, sp, #0
	bl MOD23_02255C6C
	ldr r2, [sp, #0xc]
	ldr r1, [sp]
	ldr r3, [sp, #0x10]
	ldr r0, [sp, #4]
	add r1, r2, r1
	adc r3, r0
	str r1, [r4]
	str r3, [r4, #4]
	add r0, sp, #0
	ldrb r1, [r0, #0x14]
	strb r1, [r4, #8]
	ldrb r0, [r0, #0x15]
	strb r0, [r4, #9]
	add r0, r4, #0
	bl MOD23_02255B7C
	add sp, #0x30
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD23_02255568

	thumb_func_start MOD23_022555F4
MOD23_022555F4: ; 0x022555F4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r4, r1, #0
	ldrb r1, [r5, #9]
	add r6, r2, #0
	cmp r1, #0
	bne _0225560A
	ldrb r0, [r4, #9]
	cmp r0, #1
	beq _02255614
_0225560A:
	cmp r1, #1
	bne _02255636
	ldrb r0, [r4, #9]
	cmp r0, #0
	bne _02255636
_02255614:
	ldmia r4!, {r0, r1}
	add r3, sp, #0x18
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [r3]
	ldrb r1, [r2, #9]
	mov r0, #1
	eor r0, r1
	strb r0, [r2, #9]
	add r1, r2, #0
	add r0, r5, #0
	add r2, r6, #0
	bl MOD23_02255568
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
_02255636:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD23_02255874
	cmp r0, #0
	beq _0225564C
	add r0, r6, #0
	bl MOD23_02255548
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
_0225564C:
	add r0, r5, #0
	add r1, r4, #0
	add r2, sp, #0xc
	add r3, sp, #0
	bl MOD23_02255C6C
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r5, sp, #0xc
	add r4, sp, #0
	sub r0, r3, r0
	sbc r2, r1
	bhs _0225566E
	mov r1, #1
	b _02255670
_0225566E:
	mov r1, #0
_02255670:
	add r0, sp, #0
	ldrb r0, [r0, #0x15]
	eor r0, r1
	beq _02255686
	add r0, r5, #0
	add r5, r4, #0
	ldrb r1, [r5, #9]
	add r4, r0, #0
	mov r0, #1
	eor r0, r1
	b _02255688
_02255686:
	ldrb r0, [r5, #9]
_02255688:
	strb r0, [r6, #9]
	ldr r2, [r5]
	ldr r1, [r4]
	ldr r3, [r5, #4]
	ldr r0, [r4, #4]
	sub r1, r2, r1
	sbc r3, r0
	str r1, [r6]
	str r3, [r6, #4]
	ldrb r0, [r5, #8]
	strb r0, [r6, #8]
	add r0, r6, #0
	bl MOD23_02255B7C
	add sp, #0x24
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD23_022555F4

	thumb_func_start MOD23_022556A8
MOD23_022556A8: ; 0x022556A8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	ldr r0, [r5]
	ldr r1, [r5, #4]
	ldr r2, [r6]
	ldr r3, [r6, #4]
	bl _ll_mul
	str r0, [r4]
	str r1, [r4, #4]
	ldrb r1, [r5, #8]
	ldrb r0, [r6, #8]
	add r0, r1, r0
	strb r0, [r4, #8]
	ldrb r1, [r5, #9]
	ldrb r0, [r6, #9]
	eor r0, r1
	strb r0, [r4, #9]
	add r0, r4, #0
	bl MOD23_02255B7C
	pop {r4, r5, r6, pc}
	thumb_func_end MOD23_022556A8

	thumb_func_start MOD23_022556D8
MOD23_022556D8: ; 0x022556D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r2, #0
	add r2, r1, #0
	add r3, r1, #0
	ldr r6, [r3, #4]
	mov r3, #0
	ldr r2, [r2]
	mov r4, #0
	eor r3, r6
	eor r2, r4
	str r1, [sp]
	orr r2, r3
	bne _022556FC
	mov r0, #1
	add sp, #0x1c
	strb r0, [r5, #0xb]
	pop {r4, r5, r6, r7, pc}
_022556FC:
	add r2, sp, #0x10
	add r3, sp, #4
	bl MOD23_02255C6C
	add r0, sp, #4
	str r0, [sp]
	ldr r4, [sp, #4]
	ldr r3, [sp, #8]
	ldr r2, [sp, #0x10]
	ldr r1, [sp, #0x14]
	ldr r0, _022557EC ; =0x04000280
	mov r6, #2
	strh r6, [r0]
	add r6, r0, #0
	add r6, #0x10
	str r2, [r6]
	str r1, [r6, #4]
	add r1, r0, #0
	add r1, #0x18
	str r4, [r1]
	str r3, [r1, #4]
	lsr r1, r0, #0xb
_02255728:
	ldrh r2, [r0]
	tst r2, r1
	bne _02255728
	ldr r0, _022557F0 ; =0x040002A0
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [r5]
	str r0, [r5, #4]
	mov r0, #0
	strb r0, [r5, #8]
	add r0, r5, #0
	bl MOD23_02255B18
	ldr r2, _022557EC ; =0x04000280
	add r7, r0, #0
	lsr r0, r2, #0xb
_02255748:
	ldrh r1, [r2]
	tst r1, r0
	bne _02255748
	ldr r0, _022557F4 ; =0x040002A8
	mov r1, #0
	ldr r2, [r0, #4]
	ldr r3, [r0]
	mov r0, #0
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _022557DC
_02255760:
	ldrb r0, [r5, #8]
	add r1, r7, #1
	add r1, r1, r0
	ldrb r0, [r5, #0xa]
	cmp r1, r0
	bhs _022557DC
	ldr r4, [sp, #4]
	ldr r6, [sp, #8]
	ldr r0, _022557EC ; =0x04000280
	mov r1, #2
	strh r1, [r0]
	add r0, r3, #0
	add r1, r2, #0
	mov r2, #0xa
	mov r3, #0
	bl _ll_mul
	ldr r2, _022557F8 ; =0x04000290
	mov r3, #0
	str r0, [r2]
	str r1, [r2, #4]
	add r2, #8
	str r4, [r2]
	str r6, [r2, #4]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	mov r2, #0xa
	bl _ll_mul
	str r0, [r5]
	ldr r2, _022557EC ; =0x04000280
	str r1, [r5, #4]
	lsr r0, r2, #0xb
_022557A2:
	ldrh r1, [r2]
	tst r1, r0
	bne _022557A2
	ldr r0, _022557F0 ; =0x040002A0
	ldr r2, [r5]
	ldr r1, [r0]
	ldr r3, [r5, #4]
	add r1, r2, r1
	ldr r0, [r0, #4]
	ldr r2, _022557EC ; =0x04000280
	adc r3, r0
	str r1, [r5]
	str r3, [r5, #4]
	ldrb r0, [r5, #8]
	add r0, r0, #1
	strb r0, [r5, #8]
	lsr r0, r2, #0xb
_022557C4:
	ldrh r1, [r2]
	tst r1, r0
	bne _022557C4
	ldr r0, _022557F4 ; =0x040002A8
	mov r1, #0
	ldr r2, [r0, #4]
	ldr r3, [r0]
	mov r0, #0
	eor r1, r2
	eor r0, r3
	orr r0, r1
	bne _02255760
_022557DC:
	add r0, sp, #0x10
	ldrb r1, [r0, #9]
	ldr r0, [sp]
	ldrb r0, [r0, #9]
	eor r0, r1
	strb r0, [r5, #9]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022557EC: .word 0x04000280
_022557F0: .word 0x040002A0
_022557F4: .word 0x040002A8
_022557F8: .word 0x04000290
	thumb_func_end MOD23_022556D8

	thumb_func_start MOD23_022557FC
MOD23_022557FC: ; 0x022557FC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD23_02255B68
	ldrb r1, [r5, #0xa]
	cmp r0, r1
	blo _02255810
	mov r0, #0
	pop {r3, r4, r5, pc}
_02255810:
	ldrb r0, [r5, #8]
	cmp r0, #0
	bne _02255832
	ldr r0, [r5]
	ldr r1, [r5, #4]
	mov r2, #0xa
	mov r3, #0
	bl _ll_mul
	str r0, [r5]
	str r1, [r5, #4]
	ldr r2, [r5]
	mov r0, #0
	add r2, r2, r4
	adc r1, r0
	str r2, [r5]
	str r1, [r5, #4]
_02255832:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD23_022557FC

	thumb_func_start MOD23_02255838
MOD23_02255838: ; 0x02255838
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD23_02255B68
	ldrb r1, [r5, #0xa]
	cmp r0, r1
	blo _0225584C
	mov r0, #0
	pop {r3, r4, r5, pc}
_0225584C:
	ldr r0, [r5]
	ldr r1, [r5, #4]
	mov r2, #0xa
	mov r3, #0
	bl _ll_mul
	str r0, [r5]
	str r1, [r5, #4]
	ldr r2, [r5]
	mov r0, #0
	add r2, r2, r4
	adc r1, r0
	str r2, [r5]
	str r1, [r5, #4]
	ldrb r0, [r5, #8]
	add r0, r0, #1
	strb r0, [r5, #8]
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD23_02255838

	thumb_func_start MOD23_02255874
MOD23_02255874: ; 0x02255874
	push {r3, r4, r5, r6}
	ldr r2, [r0, #4]
	ldr r3, [r0]
	ldr r4, [r1, #4]
	add r5, r2, #0
	eor r5, r4
	ldr r6, [r1]
	add r4, r3, #0
	eor r4, r6
	orr r4, r5
	beq _02255890
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_02255890:
	ldrb r5, [r0, #8]
	ldrb r4, [r1, #8]
	cmp r5, r4
	beq _0225589E
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_0225589E:
	ldrb r4, [r0, #9]
	ldrb r0, [r1, #9]
	cmp r4, r0
	beq _022558B8
	mov r1, #0
	mov r0, #0
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _022558B8
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
_022558B8:
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD23_02255874

	thumb_func_start MOD23_022558C0
MOD23_022558C0: ; 0x022558C0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldrb r1, [r5, #0xb]
	cmp r1, #0
	beq _022558D0
	mov r0, #0
	pop {r3, r4, r5, pc}
_022558D0:
	bl MOD23_02255B18
	ldrb r1, [r5, #8]
	cmp r1, #0
	beq _022558DE
	add r1, r1, #1
	add r0, r0, r1
_022558DE:
	cmp r0, r4
	bls _022558E6
	mov r0, #0
	pop {r3, r4, r5, pc}
_022558E6:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD23_022558C0

	thumb_func_start MOD23_022558EC
MOD23_022558EC: ; 0x022558EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp]
	ldrb r0, [r0, #0xb]
	str r1, [sp, #0x10]
	cmp r0, #0
	beq _02255900
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02255900:
	ldr r0, [sp]
	mov r1, #0
	ldr r7, [r0, #4]
	ldr r6, [r0]
	mov r0, #0
	eor r1, r7
	eor r0, r6
	orr r0, r1
	bne _02255956
	ldr r1, [sp, #0x10]
	add r0, r1, #0
	add r2, r0, #2
	mov r0, #0
	strh r0, [r1]
	ldr r1, [sp]
	str r2, [sp, #0x10]
	ldrb r1, [r1, #8]
	cmp r1, #0
	beq _0225594A
	add r1, r2, #2
	str r1, [sp, #0x10]
	mov r1, #0xa
	strh r1, [r2]
	ldr r1, [sp]
	ldrb r1, [r1, #8]
	cmp r1, #0
	ble _0225594A
	add r2, r0, #0
_02255938:
	ldr r1, [sp, #0x10]
	add r0, r0, #1
	strh r2, [r1]
	add r1, r1, #2
	str r1, [sp, #0x10]
	ldr r1, [sp]
	ldrb r1, [r1, #8]
	cmp r0, r1
	blt _02255938
_0225594A:
	ldr r0, [sp, #0x10]
	mov r1, #0xd
	strh r1, [r0]
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02255956:
	mov r2, #0xa
	mov r0, #1
	mov r1, #0
	sub r2, r6, r2
	mov ip, r7
	mov r2, ip
	sbc r2, r1
	blo _0225597A
	ldr r2, _02255ACC ; =MOD23_022560D8
_02255968:
	add r2, #8
	ldr r3, [r2]
	add r0, r0, #1
	ldr r1, [r2, #4]
	sub r3, r6, r3
	mov ip, r7
	mov r3, ip
	sbc r3, r1
	bhs _02255968
_0225597A:
	ldr r1, [sp]
	str r0, [sp, #8]
	ldrb r1, [r1, #8]
	sub r3, r1, r0
	bmi _0225598C
	add r1, r3, #2
	add r1, r0, r1
	str r1, [sp, #8]
	b _02255994
_0225598C:
	cmp r1, #0
	beq _02255994
	add r1, r0, #1
	str r1, [sp, #8]
_02255994:
	ldr r1, [sp]
	ldr r4, [sp]
	ldrb r2, [r1, #9]
	ldr r1, [sp, #8]
	ldrb r4, [r4, #0xa]
	add r1, r1, r2
	cmp r1, r4
	bls _022559AA
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022559AA:
	cmp r2, #1
	bne _022559B8
	ldr r1, [sp, #0x10]
	mov r2, #0xb
	strh r2, [r1]
	add r1, r1, #2
	str r1, [sp, #0x10]
_022559B8:
	ldr r5, [sp, #0x10]
	cmp r3, #0
	blt _022559E2
	add r0, r5, #0
	mov r1, #0
	strh r1, [r0]
	mov r1, #0xa
	add r5, r0, #4
	strh r1, [r0, #2]
	add r0, r3, #0
	sub r3, r3, #1
	cmp r0, #0
	beq _02255A4E
	mov r0, #0
_022559D4:
	add r1, r3, #0
	strh r0, [r5]
	add r5, r5, #2
	sub r3, r3, #1
	cmp r1, #0
	bne _022559D4
	b _02255A4E
_022559E2:
	neg r1, r3
	str r1, [sp, #4]
	mov r1, #0
	str r1, [sp, #0x14]
	ldr r1, [sp, #4]
	cmp r1, #0
	ble _02255A40
	ldr r4, _02255AD0 ; =0x04000280
	sub r0, r0, #1
	mov lr, r0
	lsr r3, r4, #0xb
	lsr r2, r4, #0xb
_022559FA:
	mov r0, #2
	strh r0, [r4]
	ldr r0, _02255AD4 ; =0x04000290
	mov r1, lr
	str r6, [r0]
	str r7, [r0, #4]
	ldr r0, [sp, #0x14]
	sub r0, r1, r0
	lsl r1, r0, #3
	ldr r0, _02255AD8 ; =MOD23_022560D0
	add r6, r0, r1
	ldr r1, [r0, r1]
	ldr r6, [r6, #4]
	ldr r0, _02255ADC ; =0x04000298
	str r1, [r0]
	str r6, [r0, #4]
_02255A1A:
	ldrh r0, [r4]
	tst r0, r3
	bne _02255A1A
	ldr r0, _02255AE0 ; =0x040002A0
	ldr r0, [r0]
	strh r0, [r5]
	add r5, r5, #2
_02255A28:
	ldrh r0, [r4]
	tst r0, r2
	bne _02255A28
	ldr r0, _02255AE4 ; =0x040002A8
	ldr r1, [sp, #4]
	ldr r6, [r0]
	ldr r7, [r0, #4]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r1
	blt _022559FA
_02255A40:
	ldr r0, [sp]
	ldrb r0, [r0, #8]
	cmp r0, #0
	beq _02255A4E
	mov r0, #0xa
	strh r0, [r5]
	add r5, r5, #2
_02255A4E:
	ldr r0, [sp, #0x10]
	sub r1, r5, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	ldr r0, [sp, #8]
	cmp r1, r0
	bhs _02255AC0
	sub r0, r0, r1
	str r0, [sp, #0x18]
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	cmp r0, #0
	ble _02255AC0
	ldr r4, _02255AD0 ; =0x04000280
	sub r0, r0, #1
	str r0, [sp, #0xc]
	lsr r3, r4, #0xb
	lsr r2, r4, #0xb
_02255A76:
	mov r0, #2
	strh r0, [r4]
	ldr r0, _02255AD4 ; =0x04000290
	ldr r1, [sp, #0xc]
	str r6, [r0]
	str r7, [r0, #4]
	ldr r0, [sp, #0x1c]
	ldr r6, _02255AD8 ; =MOD23_022560D0
	sub r0, r1, r0
	lsl r1, r0, #3
	ldr r0, _02255AD8 ; =MOD23_022560D0
	add r0, r0, r1
	ldr r1, [r6, r1]
	ldr r0, [r0, #4]
	ldr r6, _02255ADC ; =0x04000298
	str r1, [r6]
	add r1, r6, #0
	str r0, [r1, #4]
_02255A9A:
	ldrh r0, [r4]
	tst r0, r3
	bne _02255A9A
	ldr r0, _02255AE0 ; =0x040002A0
	ldr r0, [r0]
	strh r0, [r5]
	add r5, r5, #2
_02255AA8:
	ldrh r0, [r4]
	tst r0, r2
	bne _02255AA8
	ldr r0, _02255AE4 ; =0x040002A8
	ldr r1, [sp, #0x18]
	ldr r6, [r0]
	ldr r7, [r0, #4]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, r1
	blt _02255A76
_02255AC0:
	mov r0, #0xd
	strh r0, [r5]
	mov r0, #1
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255ACC: .word MOD23_022560D8
_02255AD0: .word 0x04000280
_02255AD4: .word 0x04000290
_02255AD8: .word MOD23_022560D0
_02255ADC: .word 0x04000298
_02255AE0: .word 0x040002A0
_02255AE4: .word 0x040002A8
	thumb_func_end MOD23_022558EC

	thumb_func_start MOD23_02255AE8
MOD23_02255AE8: ; 0x02255AE8
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	lsl r5, r2, #3
	ldr r2, _02255B14 ; =MOD23_022560D0
	add r3, r2, r5
	ldr r2, [r2, r5]
	ldr r3, [r3, #4]
	bl _ll_udiv
	ldrb r2, [r4, #9]
	cmp r2, #1
	bne _02255B10
	mov r2, #0
	mvn r2, r2
	add r3, r2, #0
	bl _ll_mul
_02255B10:
	pop {r3, r4, r5, pc}
	nop
_02255B14: .word MOD23_022560D0
	thumb_func_end MOD23_02255AE8

	thumb_func_start MOD23_02255B18
MOD23_02255B18: ; 0x02255B18
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	ldr r2, [sp]
	mov r0, #0xa
	ldr r5, [r2]
	ldr r6, [r2, #4]
	mov r2, #0xa
	mov r1, #0
	mov r4, #1
	mov r3, #0
	sub r2, r5, r2
	mov ip, r6
	mov r2, ip
	sbc r2, r3
	blo _02255B52
	ldr r2, [sp]
	ldrb r7, [r2, #0xa]
_02255B3A:
	add r4, r4, #1
	cmp r4, r7
	bhi _02255B52
	mov r2, #0xa
	mov r3, #0
	bl _ll_mul
	sub r2, r5, r0
	mov ip, r6
	mov r2, ip
	sbc r2, r1
	bhs _02255B3A
_02255B52:
	ldr r0, [sp]
	ldrb r0, [r0, #8]
	cmp r4, r0
	bls _02255B5E
	sub r4, r4, r0
	b _02255B60
_02255B5E:
	mov r4, #1
_02255B60:
	ldr r0, [sp]
	ldrb r0, [r0, #9]
	add r0, r4, r0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD23_02255B18

	thumb_func_start MOD23_02255B68
MOD23_02255B68: ; 0x02255B68
	push {r4, lr}
	add r4, r0, #0
	bl MOD23_02255B18
	ldrb r1, [r4, #8]
	cmp r1, #0
	beq _02255B7A
	add r1, r1, #1
	add r0, r0, r1
_02255B7A:
	pop {r4, pc}
	thumb_func_end MOD23_02255B68

	thumb_func_start MOD23_02255B7C
MOD23_02255B7C: ; 0x02255B7C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _02255C02
	ldr r5, _02255C5C ; =0x04000280
	ldr r2, [r4]
	add r3, r5, #0
	ldr r1, [r4, #4]
	mov r0, #1
	strh r0, [r5]
	add r3, #0x10
	str r2, [r3]
	add r0, r5, #0
	str r1, [r3, #4]
	add r0, #0x18
	mov r2, #0xa
	mov r1, #0
	str r2, [r0]
	str r1, [r0, #4]
	add r1, r4, #0
	mov ip, r0
	add r1, #8
	b _02255BE4
_02255BAC:
	mov r0, #2
	lsl r0, r0, #0xe
_02255BB0:
	ldrh r2, [r5]
	tst r2, r0
	bne _02255BB0
	ldr r0, _02255C60 ; =0x040002A0
	ldr r2, _02255C60 ; =0x040002A0
	ldr r0, [r0]
	ldr r2, [r2, #4]
	str r0, [r4]
	str r2, [r4, #4]
	ldr r6, [r4]
	mov r0, #1
	strh r0, [r5]
	str r6, [r3]
	str r2, [r3, #4]
	mov r2, #0xa
	mov r0, ip
	str r2, [r0]
	mov r2, #0
	mov r0, ip
	str r2, [r0, #4]
	ldrb r0, [r1]
	sub r0, r0, #1
	strb r0, [r1]
	ldrb r0, [r4, #8]
	cmp r0, #0
	beq _02255C02
_02255BE4:
	ldrh r2, [r5]
	mov r0, #2
	lsl r0, r0, #0xe
	tst r0, r2
	bne _02255BE4
	ldr r0, _02255C64 ; =0x040002A8
	mov r7, #0
	ldr r6, [r0]
	ldr r2, [r0, #4]
	mov r0, #0
	eor r0, r2
	add r2, r6, #0
	eor r2, r7
	orr r0, r2
	beq _02255BAC
_02255C02:
	add r0, r4, #0
	bl MOD23_02255B18
	ldrb r2, [r4, #8]
	cmp r2, #0
	beq _02255C58
	add r1, r2, #1
	add r1, r0, r1
	ldrb r0, [r4, #0xa]
	cmp r1, r0
	bls _02255C58
	sub r1, r1, r0
	cmp r1, r2
	bhi _02255C58
	ldr r5, [r4]
	ldr r3, [r4, #4]
	ldr r0, _02255C5C ; =0x04000280
	mov r2, #1
	strh r2, [r0]
	add r2, r0, #0
	add r2, #0x10
	str r5, [r2]
	str r3, [r2, #4]
	ldr r2, _02255C68 ; =MOD23_022560D0
	lsl r3, r1, #3
	ldr r5, [r2, r3]
	add r2, r0, #0
	add r2, #0x18
	mov r3, #0
	str r5, [r2]
	str r3, [r2, #4]
	lsr r2, r0, #0xb
_02255C42:
	ldrh r3, [r0]
	tst r3, r2
	bne _02255C42
	ldr r0, _02255C60 ; =0x040002A0
	ldr r2, [r0]
	ldr r0, [r0, #4]
	str r2, [r4]
	str r0, [r4, #4]
	ldrb r0, [r4, #8]
	sub r0, r0, r1
	strb r0, [r4, #8]
_02255C58:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255C5C: .word 0x04000280
_02255C60: .word 0x040002A0
_02255C64: .word 0x040002A8
_02255C68: .word MOD23_022560D0
	thumb_func_end MOD23_02255B7C

	thumb_func_start MOD23_02255C6C
MOD23_02255C6C: ; 0x02255C6C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	ldmia r6!, {r0, r1}
	add r5, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r6]
	add r4, r3, #0
	str r0, [r2]
	ldmia r7!, {r0, r1}
	add r2, r4, #0
	stmia r2!, {r0, r1}
	ldr r0, [r7]
	str r0, [r2]
	ldrb r1, [r5, #8]
	ldrb r0, [r4, #8]
	cmp r1, r0
	bhs _02255C96
	add r0, r5, #0
	add r5, r4, #0
	add r4, r0, #0
_02255C96:
	ldrb r3, [r5, #8]
	ldrb r2, [r4, #8]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	sub r2, r3, r2
	lsl r6, r2, #3
	ldr r2, _02255CB8 ; =MOD23_022560D0
	add r3, r2, r6
	ldr r2, [r2, r6]
	ldr r3, [r3, #4]
	bl _ll_mul
	str r0, [r4]
	str r1, [r4, #4]
	ldrb r0, [r5, #8]
	strb r0, [r4, #8]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02255CB8: .word MOD23_022560D0
	thumb_func_end MOD23_02255C6C

	.section .rodata

	.global MOD23_02255CBC
MOD23_02255CBC: ; 0x02255CBC
	.word MOD23_022549F4, MOD23_02254A34, MOD23_02254B0C, MOD23_02254C08
	.word MOD23_02254D20, MOD23_02254E28, MOD23_02254F60

	.global MOD23_02255CD8
MOD23_02255CD8: ; 0x02255CD8
	.byte 0x90, 0xAF, 0x20, 0x5F
	.byte 0x70, 0x8F, 0x20, 0x3F, 0x70, 0x8F, 0x40, 0x5F, 0x70, 0x8F, 0x60, 0x7F, 0x50, 0x6F, 0x20, 0x3F
	.byte 0x50, 0x6F, 0x40, 0x5F, 0x50, 0x6F, 0x60, 0x7F, 0x30, 0x4F, 0x20, 0x3F, 0x30, 0x4F, 0x40, 0x5F
	.byte 0x30, 0x4F, 0x60, 0x7F, 0x90, 0xAF, 0x60, 0x7F, 0x50, 0x6F, 0xA0, 0xBF, 0x50, 0x6F, 0x80, 0x9F
	.byte 0x70, 0x8F, 0x80, 0x9F, 0x70, 0x8F, 0xA0, 0xBF, 0x90, 0xAF, 0x80, 0xBF, 0x30, 0x4F, 0x80, 0xBF

	.global MOD23_02255D1C
MOD23_02255D1C: ; 0x02255D1C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD23_02255D38
MOD23_02255D38: ; 0x02255D38
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x57, 0x00, 0x58, 0x00, 0x25, 0x01, 0x23, 0x01, 0x7F, 0x00
	.byte 0x80, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255D58
MOD23_02255D58: ; 0x02255D58
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x5F, 0x00, 0x60, 0x00, 0x25, 0x01, 0x23, 0x01, 0x87, 0x00
	.byte 0x88, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255D78
MOD23_02255D78: ; 0x02255D78
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x5B, 0x00, 0x5C, 0x00, 0x25, 0x01, 0x23, 0x01, 0x83, 0x00
	.byte 0x84, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255D98
MOD23_02255D98: ; 0x02255D98
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x71, 0x00, 0x72, 0x00, 0x25, 0x01, 0x23, 0x01, 0x99, 0x00
	.byte 0x9A, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255DB8
MOD23_02255DB8: ; 0x02255DB8
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x6F, 0x00, 0x70, 0x00, 0x25, 0x01, 0x23, 0x01, 0x97, 0x00
	.byte 0x98, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255DD8
MOD23_02255DD8: ; 0x02255DD8
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x6B, 0x00, 0x6C, 0x00, 0x25, 0x01, 0x23, 0x01, 0x93, 0x00
	.byte 0x94, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255DF8
MOD23_02255DF8: ; 0x02255DF8
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x6D, 0x00, 0x6E, 0x00, 0x25, 0x01, 0x23, 0x01, 0x95, 0x00
	.byte 0x96, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255E18
MOD23_02255E18: ; 0x02255E18
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x59, 0x00, 0x5A, 0x00, 0x25, 0x01, 0x23, 0x01, 0x81, 0x00
	.byte 0x82, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255E38
MOD23_02255E38: ; 0x02255E38
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x69, 0x00, 0x6A, 0x00, 0x25, 0x01, 0x23, 0x01, 0x91, 0x00
	.byte 0x92, 0x00, 0x25, 0x01, 0x51, 0x01, 0x52, 0x01, 0x52, 0x01, 0x53, 0x01

	.global MOD23_02255E58
MOD23_02255E58: ; 0x02255E58
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x67, 0x00, 0x68, 0x00, 0x25, 0x01, 0x23, 0x01, 0x8F, 0x00
	.byte 0x90, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255E78
MOD23_02255E78: ; 0x02255E78
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x65, 0x00, 0x66, 0x00, 0x25, 0x01, 0x23, 0x01, 0x8D, 0x00
	.byte 0x8E, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255E98
MOD23_02255E98: ; 0x02255E98
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x63, 0x00, 0x64, 0x00, 0x25, 0x01, 0x23, 0x01, 0x8B, 0x00
	.byte 0x8C, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255EB8
MOD23_02255EB8: ; 0x02255EB8
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x61, 0x00, 0x62, 0x00, 0x25, 0x01, 0x23, 0x01, 0x89, 0x00
	.byte 0x8A, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255ED8
MOD23_02255ED8: ; 0x02255ED8
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x5D, 0x00, 0x5E, 0x00, 0x25, 0x01, 0x23, 0x01, 0x85, 0x00
	.byte 0x86, 0x00, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255EF8
MOD23_02255EF8: ; 0x02255EF8
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x75, 0x00
	.byte 0x76, 0x00, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x25, 0x01, 0x23, 0x01, 0x9D, 0x00
	.byte 0x9E, 0x00, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x25, 0x01, 0x4B, 0x01, 0x4C, 0x01
	.byte 0x4C, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4C, 0x01, 0x4D, 0x01

	.global MOD23_02255F38
MOD23_02255F38: ; 0x02255F38
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x73, 0x00
	.byte 0x74, 0x00, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x25, 0x01, 0x23, 0x01, 0x9B, 0x00
	.byte 0x9C, 0x00, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x25, 0x01, 0x51, 0x01, 0x52, 0x01
	.byte 0x52, 0x01, 0x52, 0x01, 0x52, 0x01, 0x52, 0x01, 0x52, 0x01, 0x53, 0x01

	.global MOD23_02255F78
MOD23_02255F78: ; 0x02255F78
	.byte 0xFB, 0x00, 0xFC, 0x00
	.byte 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0xFD, 0x00, 0x23, 0x01, 0x55, 0x00
	.byte 0x56, 0x00, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x25, 0x01, 0x23, 0x01, 0x7D, 0x00
	.byte 0x7E, 0x00, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x25, 0x01, 0x51, 0x01, 0x52, 0x01
	.byte 0x52, 0x01, 0x52, 0x01, 0x52, 0x01, 0x52, 0x01, 0x52, 0x01, 0x53, 0x01

	.global MOD23_02255FB8
MOD23_02255FB8: ; 0x02255FB8
	.byte 0x04

	.global MOD23_02255FB9
MOD23_02255FB9: ; 0x02255FB9
	.byte 0x12

	.global MOD23_02255FBA
MOD23_02255FBA: ; 0x02255FBA
	.byte 0x08

	.global MOD23_02255FBB
MOD23_02255FBB: ; 0x02255FBB
	.byte 0x04
	.byte 0x04, 0x0E, 0x04, 0x04, 0x08, 0x0E, 0x04, 0x04, 0x0C, 0x0E, 0x04, 0x04, 0x04, 0x0A, 0x04, 0x04
	.byte 0x08, 0x0A, 0x04, 0x04, 0x0C, 0x0A, 0x04, 0x04, 0x04, 0x06, 0x04, 0x04, 0x08, 0x06, 0x04, 0x04
	.byte 0x0C, 0x06, 0x04, 0x04, 0x0C, 0x12, 0x04, 0x04, 0x14, 0x0A, 0x04, 0x04, 0x10, 0x0A, 0x04, 0x04
	.byte 0x10, 0x0E, 0x04, 0x04, 0x14, 0x0E, 0x04, 0x04, 0x10, 0x12, 0x08, 0x04, 0x10, 0x06, 0x08, 0x04

	.global MOD23_02255FFC
MOD23_02255FFC: ; 0x02255FF
	.word MOD23_02255F78, MOD23_02255D38, MOD23_02255E18, MOD23_02255D78
	.word MOD23_02255ED8, MOD23_02255D58, MOD23_02255EB8, MOD23_02255E98
	.word MOD23_02255E78, MOD23_02255E58, MOD23_02255E38, MOD23_02255DD8
	.word MOD23_02255DF8, MOD23_02255DB8, MOD23_02255D98, MOD23_02255F38
	.word MOD23_02255EF8

	.global MOD23_02256040
MOD23_02256040: ; 0x02256040
	.word 0x00, MOD23_02255088, 0x00
	.word 0x01, MOD23_022551A4, 0x00
	.word 0x02, MOD23_02255210, 0x00
	.word 0x03, MOD23_02255270, 0x00
	.word 0x04, MOD23_022552A8, 0x00
	.word 0x05, MOD23_022552E8, 0x00
	.word 0x06, MOD23_02255320, 0x00
	.word 0x07, MOD23_02255360, 0x00
	.word 0x09, MOD23_022553A0, 0x00
	.word 0x08, MOD23_022553E4, 0x00
	.word 0x0A, MOD23_02255470, 0x00
	.word 0x00, 0x00000000, 0x00

	.global MOD23_022560D0
MOD23_022560D0: ; 0x022560D0
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD23_022560D8
MOD23_022560D8: ; 0x022560D8
	.byte 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x86, 0x01, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x96, 0x98, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xE1, 0xF5, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCA, 0x9A, 0x3B
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0xE4, 0x0B, 0x54, 0x02, 0x00, 0x00, 0x00
