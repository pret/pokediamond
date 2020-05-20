	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD36_02254840
MOD36_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD36_02254854
	ldr r1, _02254850 ; =MOD36_02254990
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD36_02254854
_02254850: .word MOD36_02254990
	thumb_func_end MOD36_02254840

	thumb_func_start MOD36_02254854
MOD36_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r5, r0, #0
	ldr r1, _02254898 ; =0x00005B90
	mov r0, #8
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD36_022548A0
	cmp r0, #0
	beq _0225488C
	ldr r0, _0225489C ; =MOD36_02254938
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
	bl FUN_02016A18
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word 0x00005B90
_0225489C: .word MOD36_02254938
	thumb_func_end MOD36_02254854

	thumb_func_start MOD36_022548A0
MOD36_022548A0: ; 0x022548A0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, _02254904 ; =0x00005B78
	str r3, [r5, #0xc]
	mov r0, #0
	strb r0, [r5, r1]
	mov r6, #1
	add r3, r1, #1
	strb r6, [r5, r3]
	add r3, r1, #2
	strb r0, [r5, r3]
	add r0, r1, #4
	add r0, r5, r0
	add r1, r5, #4
	bl MOD36_02254E30
	cmp r0, #0
	beq _022548FC
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	strb r0, [r5, #3]
	add r0, r5, #4
	bl MOD36_02254E10
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254908 ; =0x022553E8
	ldr r2, _0225490C ; =MOD36_02254980
	mov r1, #3
	add r3, r5, #0
	bl MOD20_02254130
	ldr r1, _02254910 ; =0x00005B84
	mov r2, #0
	str r0, [r5, r1]
	add r0, r1, #4
	str r2, [r5, r0]
	sub r0, r1, #4
	str r4, [r5, r0]
	add sp, #4
	add r0, r6, #0
	pop {r3, r4, r5, r6, pc}
_022548FC:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02254904: .word 0x00005B78
_02254908: .word 0x022553E8
_0225490C: .word MOD36_02254980
_02254910: .word 0x00005B84
	thumb_func_end MOD36_022548A0

	thumb_func_start MOD36_02254914
MOD36_02254914: ; 0x02254914
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02254930 ; =0x00005B84
	ldr r0, [r4, r0]
	bl MOD20_02254198
	ldr r0, _02254934 ; =0x00005B7C
	ldr r0, [r4, r0]
	bl MOD36_02254E78
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}
	.align 2, 0
_02254930: .word 0x00005B84
_02254934: .word 0x00005B7C
	thumb_func_end MOD36_02254914

	thumb_func_start MOD36_02254938
MOD36_02254938: ; 0x02254938
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254974
	ldr r1, _02254978 ; =0x00005B80
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _0225497C ; =0x022553F4
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254974
	add r0, r4, #0
	bl MOD36_02254914
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, _02254978 ; =0x00005B80
	ldr r0, [r4, r0]
	bl MOD20_022529A0
_02254974:
	pop {r3, r4, r5, pc}
	nop
_02254978: .word 0x00005B80
_0225497C: .word 0x022553F4
	thumb_func_end MOD36_02254938

	thumb_func_start MOD36_02254980
MOD36_02254980: ; 0x02254980
	ldr r2, _0225498C ; =0x00005B88
	str r1, [r3, r2]
	add r1, r2, #4
	str r0, [r3, r1]
	bx lr
	nop
_0225498C: .word 0x00005B88
	thumb_func_end MOD36_02254980

	thumb_func_start MOD36_02254990
MOD36_02254990: ; 0x02254990
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD36_02254990

	thumb_func_start MOD36_02254998
MOD36_02254998: ; 0x02254998
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
	thumb_func_end MOD36_02254998

	thumb_func_start MOD36_022549AC
MOD36_022549AC: ; 0x022549AC
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549BC
	cmp r0, #1
	beq _022549CE
	b _022549EC
_022549BC:
	ldr r0, _022549F0 ; =0x00005B7C
	mov r1, #0
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549EC
_022549CE:
	ldr r0, _022549F0 ; =0x00005B7C
	mov r1, #0
	ldr r0, [r4, r0]
	bl MOD36_02254F30
	cmp r0, #0
	beq _022549EC
	ldr r0, _022549F4 ; =0x00005B80
	ldr r0, [r4, r0]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD36_02254998
_022549EC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_022549F0: .word 0x00005B7C
_022549F4: .word 0x00005B80
	thumb_func_end MOD36_022549AC

	thumb_func_start MOD36_022549F8
MOD36_022549F8: ; 0x022549F8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254A0A
	mov r1, #2
	bl MOD36_02254998
_02254A0A:
	ldrb r0, [r4, #1]
	cmp r0, #3
	bhi _02254A30
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02254A1C: ; jump table
	.short _02254A24 - _02254A1C - 2 ; case 0
	.short _02254AF4 - _02254A1C - 2 ; case 1
	.short _02254B4E - _02254A1C - 2 ; case 2
	.short _02254B7C - _02254A1C - 2 ; case 3
_02254A24:
	ldr r0, _02254BCC ; =0x00005B80
	ldr r0, [r4, r0]
	bl MOD20_02252C08
	cmp r0, #0
	beq _02254A32
_02254A30:
	b _02254BC4
_02254A32:
	ldr r1, _02254BD0 ; =0x00005B88
	ldr r0, [r4, r1]
	cmp r0, #1
	bne _02254AAE
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02254A4C
	cmp r0, #1
	beq _02254A82
	cmp r0, #2
	beq _02254A8A
	b _02254AA6
_02254A4C:
	add r0, r1, #0
	mov r3, #1
	sub r0, #0x10
	strb r3, [r4, r0]
	add r0, r1, #0
	mov r2, #0
	sub r0, #0xf
	strb r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xe
	sub r1, #0xc
	strb r3, [r4, r0]
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD36_02254F0C
	ldr r0, _02254BD4 ; =0x00005B7C
	mov r1, #7
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	ldr r0, _02254BD8 ; =0x00000663
	bl MOD20_02252B28
	mov r0, #1
	strb r0, [r4, #1]
	b _02254AA6
_02254A82:
	ldr r0, _02254BDC ; =0x0000066E
	bl MOD20_02252B28
	b _02254AA6
_02254A8A:
	add r0, r1, #0
	mov r2, #1
	sub r0, #0xe
	sub r1, #0xc
	strb r2, [r4, r0]
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD36_02254F0C
	ldr r0, _02254BD8 ; =0x00000663
	bl MOD20_02252B28
	mov r0, #3
	strb r0, [r4, #1]
_02254AA6:
	ldr r0, _02254BD0 ; =0x00005B88
	mov r1, #0
	str r1, [r4, r0]
	b _02254BC4
_02254AAE:
	ldrb r0, [r4, #3]
	cmp r0, #0
	beq _02254ADA
	add r0, r4, #0
	ldr r6, [r4, #4]
	ldr r5, [r4, #8]
	bl MOD36_02254C44
	cmp r0, #0
	beq _02254AD4
	ldr r0, [r4, #8]
	add r1, r6, #0
	str r0, [sp]
	ldr r3, [r4, #4]
	add r0, r4, #0
	add r2, r5, #0
	bl MOD36_02254C90
	b _02254BC4
_02254AD4:
	mov r0, #0
	strb r0, [r4, #3]
	b _02254BC4
_02254ADA:
	add r0, r4, #0
	bl MOD36_02254BE4
	cmp r0, #0
	beq _02254BC4
	ldr r0, _02254BD4 ; =0x00005B7C
	mov r1, #3
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	mov r0, #1
	strb r0, [r4, #3]
	b _02254BC4
_02254AF4:
	ldr r1, _02254BD0 ; =0x00005B88
	ldr r0, [r4, r1]
	cmp r0, #1
	bne _02254BC4
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02254B0C
	cmp r0, #1
	beq _02254B14
	cmp r0, #2
	bne _02254B46
_02254B0C:
	ldr r0, _02254BDC ; =0x0000066E
	bl MOD20_02252B28
	b _02254B46
_02254B14:
	add r0, r1, #0
	mov r2, #1
	sub r0, #0x10
	strb r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xf
	strb r2, [r4, r0]
	add r0, r1, #0
	sub r0, #0xe
	sub r1, #0xc
	strb r2, [r4, r0]
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD36_02254F0C
	ldr r0, _02254BD4 ; =0x00005B7C
	mov r1, #8
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	ldr r0, _02254BD8 ; =0x00000663
	bl MOD20_02252B28
	mov r0, #2
	strb r0, [r4, #1]
_02254B46:
	ldr r0, _02254BD0 ; =0x00005B88
	mov r1, #0
	str r1, [r4, r0]
	b _02254BC4
_02254B4E:
	ldr r0, _02254BD4 ; =0x00005B7C
	mov r1, #8
	ldr r0, [r4, r0]
	bl MOD36_02254F30
	cmp r0, #0
	beq _02254BC4
	ldr r0, _02254BE0 ; =0x00005B78
	mov r3, #0
	strb r3, [r4, r0]
	mov r2, #1
	add r1, r0, #1
	strb r2, [r4, r1]
	add r1, r0, #2
	strb r3, [r4, r1]
	add r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #5
	bl MOD36_02254F0C
	mov r0, #0
	strb r0, [r4, #1]
	b _02254BC4
_02254B7C:
	ldr r1, _02254BD0 ; =0x00005B88
	ldr r0, [r4, r1]
	cmp r0, #2
	bne _02254B9C
	add r0, r1, #0
	mov r2, #0
	sub r0, #0xe
	sub r1, #0xc
	strb r2, [r4, r0]
	ldr r0, [r4, r1]
	mov r1, #5
	bl MOD36_02254F0C
	mov r0, #0
	strb r0, [r4, #1]
	b _02254BC4
_02254B9C:
	cmp r0, #3
	bne _02254BC4
	mov r0, #0
	sub r1, #0xe
	strb r0, [r4, r1]
	add r0, r4, #4
	bl MOD36_02254E10
	ldr r0, _02254BD4 ; =0x00005B7C
	mov r1, #5
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	ldr r0, _02254BD4 ; =0x00005B7C
	mov r1, #6
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	mov r0, #0
	strb r0, [r4, #1]
_02254BC4:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02254BCC: .word 0x00005B80
_02254BD0: .word 0x00005B88
_02254BD4: .word 0x00005B7C
_02254BD8: .word 0x00000663
_02254BDC: .word 0x0000066E
_02254BE0: .word 0x00005B78
	thumb_func_end MOD36_022549F8

	thumb_func_start MOD36_02254BE4
MOD36_02254BE4: ; 0x02254BE4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252B68
	cmp r0, #0
	beq _02254C3E
	ldr r1, [sp, #4]
	ldr r2, [sp]
	sub r1, #0x10
	sub r2, #0x10
	cmp r1, #0x9b
	bhs _02254C06
	mov r0, #1
	b _02254C08
_02254C06:
	mov r0, #0
_02254C08:
	cmp r2, #0x95
	bhs _02254C10
	mov r3, #1
	b _02254C12
_02254C10:
	mov r3, #0
_02254C12:
	tst r0, r3
	beq _02254C3E
	lsr r3, r1, #1
	lsr r1, r2, #1
	add r2, r4, #0
	mov r0, #0x96
	add r2, #0x10
	mul r0, r3
	str r3, [sp, #4]
	str r1, [sp]
	add r2, r2, r0
	ldrb r0, [r2, r1]
	cmp r0, #0
	bne _02254C3E
	mov r0, #1
	strb r0, [r2, r1]
	ldr r1, [sp, #4]
	str r1, [r4, #4]
	ldr r1, [sp]
	add sp, #8
	str r1, [r4, #8]
	pop {r4, pc}
_02254C3E:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD36_02254BE4

	thumb_func_start MOD36_02254C44
MOD36_02254C44: ; 0x02254C44
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252B68
	cmp r0, #0
	beq _02254C8A
	ldr r1, [sp, #4]
	ldr r2, [sp]
	sub r1, #0x10
	sub r2, #0x10
	cmp r1, #0x9b
	bhs _02254C66
	mov r0, #1
	b _02254C68
_02254C66:
	mov r0, #0
_02254C68:
	cmp r2, #0x95
	bhs _02254C70
	mov r3, #1
	b _02254C72
_02254C70:
	mov r3, #0
_02254C72:
	tst r0, r3
	beq _02254C8A
	lsr r1, r1, #1
	lsr r0, r2, #1
	str r1, [sp, #4]
	str r0, [sp]
	str r1, [r4, #4]
	ldr r0, [sp]
	add sp, #8
	str r0, [r4, #8]
	mov r0, #1
	pop {r4, pc}
_02254C8A:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD36_02254C44

	thumb_func_start MOD36_02254C90
MOD36_02254C90: ; 0x02254C90
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	ldr r0, [sp, #0x28]
	add r4, r2, #0
	add r5, r1, #0
	str r3, [sp]
	str r0, [sp, #0x28]
	cmp r4, r0
	bne _02254CAC
	add r0, r3, #0
	cmp r5, r0
	bne _02254CAC
	b _02254DCC
_02254CAC:
	ldr r0, [sp]
	cmp r0, r5
	bls _02254CB6
	sub r1, r0, r5
	b _02254CB8
_02254CB6:
	sub r1, r5, r0
_02254CB8:
	ldr r0, [sp, #0x28]
	cmp r0, r4
	bls _02254CC2
	sub r2, r0, r4
	b _02254CC4
_02254CC2:
	sub r2, r4, r0
_02254CC4:
	cmp r1, r2
	bls _02254D46
	ldr r0, [sp]
	cmp r0, r5
	bls _02254CD4
	mov r0, #1
	str r0, [sp, #4]
	b _02254CDA
_02254CD4:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
_02254CDA:
	cmp r1, #0
	beq _02254CEC
	ldr r0, [sp, #0x28]
	sub r0, r0, r4
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #0x10]
	b _02254CF0
_02254CEC:
	mov r0, #0
	str r0, [sp, #0x10]
_02254CF0:
	ldr r0, [sp, #0x10]
	lsl r1, r4, #0xc
	add r7, r1, r0
	ldr r0, [sp, #4]
	add r5, r5, r0
	ldr r0, [sp]
	cmp r5, r0
	beq _02254DB0
	mov r1, #0x96
	add r0, r5, #0
	mul r0, r1
	add r4, r6, r0
	ldr r0, [sp, #4]
	mul r1, r0
	str r1, [sp, #0xc]
_02254D0E:
	asr r1, r7, #0xc
	cmp r5, #0x9c
	bhs _02254D32
	cmp r1, #0x96
	bhs _02254D32
	add r0, r4, r1
	ldrb r2, [r0, #0x10]
	cmp r2, #0
	bne _02254D32
	mov r2, #0
	strb r2, [r0, #0x10]
	str r5, [r6, #4]
	str r1, [r6, #8]
	ldr r0, _02254DD0 ; =0x00005B7C
	mov r1, #3
	ldr r0, [r6, r0]
	bl MOD36_02254F0C
_02254D32:
	ldr r0, [sp, #0xc]
	add r4, r4, r0
	ldr r0, [sp, #4]
	add r5, r5, r0
	ldr r0, [sp, #0x10]
	add r7, r7, r0
	ldr r0, [sp]
	cmp r5, r0
	bne _02254D0E
	b _02254DB0
_02254D46:
	ldr r0, [sp, #0x28]
	cmp r0, r4
	bls _02254D50
	mov r7, #1
	b _02254D54
_02254D50:
	mov r7, #0
	mvn r7, r7
_02254D54:
	cmp r2, #0
	beq _02254D68
	ldr r0, [sp]
	add r1, r2, #0
	sub r0, r0, r5
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #8]
	b _02254D6C
_02254D68:
	mov r0, #0
	str r0, [sp, #8]
_02254D6C:
	ldr r0, [sp, #8]
	lsl r1, r5, #0xc
	add r5, r1, r0
	ldr r0, [sp, #0x28]
	add r4, r4, r7
	cmp r4, r0
	beq _02254DB0
_02254D7A:
	asr r1, r5, #0xc
	cmp r4, #0x96
	bhs _02254DA4
	cmp r1, #0x9c
	bhs _02254DA4
	mov r0, #0x96
	mul r0, r1
	add r0, r6, r0
	add r0, r0, r4
	ldrb r2, [r0, #0x10]
	cmp r2, #0
	bne _02254DA4
	mov r2, #1
	strb r2, [r0, #0x10]
	str r1, [r6, #4]
	ldr r0, _02254DD0 ; =0x00005B7C
	str r4, [r6, #8]
	ldr r0, [r6, r0]
	mov r1, #3
	bl MOD36_02254F0C
_02254DA4:
	ldr r0, [sp, #8]
	add r4, r4, r7
	add r5, r5, r0
	ldr r0, [sp, #0x28]
	cmp r4, r0
	bne _02254D7A
_02254DB0:
	ldr r0, [sp, #0x28]
	cmp r0, #0x96
	bhs _02254DCC
	ldr r0, [sp]
	cmp r0, #0x9c
	bhs _02254DCC
	str r0, [r6, #4]
	ldr r0, [sp, #0x28]
	mov r1, #3
	str r0, [r6, #8]
	ldr r0, _02254DD0 ; =0x00005B7C
	ldr r0, [r6, r0]
	bl MOD36_02254F0C
_02254DCC:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254DD0: .word 0x00005B7C
	thumb_func_end MOD36_02254C90

	thumb_func_start MOD36_02254DD4
MOD36_02254DD4: ; 0x02254DD4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254DE4
	cmp r0, #1
	beq _02254DF6
	b _02254E06
_02254DE4:
	ldr r0, _02254E0C ; =0x00005B7C
	mov r1, #1
	ldr r0, [r4, r0]
	bl MOD36_02254F0C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254E06
_02254DF6:
	ldr r0, _02254E0C ; =0x00005B7C
	ldr r0, [r4, r0]
	bl MOD36_02254F3C
	cmp r0, #0
	beq _02254E06
	mov r0, #1
	pop {r4, pc}
_02254E06:
	mov r0, #0
	pop {r4, pc}
	nop
_02254E0C: .word 0x00005B7C
	thumb_func_end MOD36_02254DD4

	thumb_func_start MOD36_02254E10
MOD36_02254E10: ; 0x02254E10
	push {r4, r5}
	mov r4, #0
	add r2, r4, #0
	add r3, r4, #0
_02254E18:
	add r5, r3, #0
_02254E1A:
	add r1, r0, r5
	add r5, r5, #1
	strb r2, [r1, #0xc]
	cmp r5, #0x96
	blt _02254E1A
	add r4, r4, #1
	add r0, #0x96
	cmp r4, #0x9c
	blt _02254E18
	pop {r4, r5}
	bx lr
	thumb_func_end MOD36_02254E10

	thumb_func_start MOD36_02254E30
MOD36_02254E30: ; 0x02254E30
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x70
	bl FUN_02016998
	add r4, r0, #0
	beq _02254E74
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x68
	strh r1, [r0]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD36_02254E8C
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02254E74
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254E74:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD36_02254E30

	thumb_func_start MOD36_02254E78
MOD36_02254E78: ; 0x02254E78
	push {r4, lr}
	add r4, r0, #0
	beq _02254E88
	bl MOD36_02254EE4
	add r0, r4, #0
	bl FUN_02016A18
_02254E88:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD36_02254E78

	thumb_func_start MOD36_02254E8C
MOD36_02254E8C: ; 0x02254E8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r7, r0, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x59
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x34
	mov r1, #0xc
	mov r2, #0x57
	mov r3, #0x58
	bl MOD20_02253FBC
	add r0, r7, #0
	str r0, [sp, #0xc]
	add r0, #0x34
	ldr r4, _02254EE0 ; =0x02255440
	mov r6, #0
	add r5, r7, #0
	str r0, [sp, #0xc]
_02254EC6:
	ldr r0, [r7, #0x20]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	bl MOD20_02253E74
	str r0, [r5, #0x24]
	add r6, r6, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #4
	blt _02254EC6
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254EE0: .word 0x02255440
	thumb_func_end MOD36_02254E8C

	thumb_func_start MOD36_02254EE4
MOD36_02254EE4: ; 0x02254EE4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_02254EEC:
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _02254EF8
	ldr r0, [r6, #0x20]
	bl MOD20_02253F14
_02254EF8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02254EEC
	add r6, #0x34
	add r0, r6, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD36_02254EE4

	thumb_func_start MOD36_02254F0C
MOD36_02254F0C: ; 0x02254F0C
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254F2C ; =0x02255480
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254F2C: .word 0x02255480
	thumb_func_end MOD36_02254F0C

	thumb_func_start MOD36_02254F30
MOD36_02254F30: ; 0x02254F30
	ldr r3, _02254F38 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254F38: .word MOD20_02253794
	thumb_func_end MOD36_02254F30

	thumb_func_start MOD36_02254F3C
MOD36_02254F3C: ; 0x02254F3C
	ldr r3, _02254F44 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254F44: .word MOD20_022537B8
	thumb_func_end MOD36_02254F3C

	thumb_func_start MOD36_02254F48
MOD36_02254F48: ; 0x02254F48
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD36_02254F48

	thumb_func_start MOD36_02254F5C
MOD36_02254F5C: ; 0x02254F5C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	mov r0, #8
	add r5, r1, #0
	bl FUN_02016B90
	cmp r0, #0
	bne _02254F70
	bl ErrorHandling
_02254F70:
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _0225502C ; =0x02255408
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _02255030 ; =0x02255424
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254F9E
	bl ErrorHandling
_02254F9E:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x56
	mov r3, #6
	bl FUN_0200687C
	add r6, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x55
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254FEA
	bl ErrorHandling
_02254FEA:
	add r0, r4, #0
	lsr r1, r6, #5
	bl MOD36_0225503C
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_02017CD0
	ldr r1, _02255034 ; =0x04001000
	ldr r0, _02255038 ; =0xFFFFE0FF
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
	add r0, r5, #0
	bl MOD36_02254F48
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02255028
	bl ErrorHandling
_02255028:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0225502C: .word 0x02255408
_02255030: .word 0x02255424
_02255034: .word 0x04001000
_02255038: .word 0xFFFFE0FF
	thumb_func_end MOD36_02254F5C

	thumb_func_start MOD36_0225503C
MOD36_0225503C: ; 0x0225503C
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r3, _02255098 ; =0x02255400
	add r4, r0, #0
	ldrh r5, [r3]
	add r0, sp, #0
	add r2, sp, #0
	strh r5, [r0]
	ldrh r5, [r3, #2]
	strh r5, [r0, #2]
	ldrh r5, [r3, #4]
	ldrh r3, [r3, #6]
	strh r5, [r0, #4]
	strh r3, [r0, #6]
	str r1, [r4, #0x58]
	strh r1, [r0, #6]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	bl FUN_02019150
	ldr r0, [r4]
	mov r2, #0xbe
	ldr r0, [r0, #8]
	ldr r1, [r4, #0x54]
	lsl r2, r2, #6
	bl FUN_0208946C
	cmp r0, #0
	bne _02255082
	add r0, r4, #0
	add r0, #0x48
	mov r1, #4
	bl FUN_02019620
_02255082:
	add r0, r4, #0
	add r0, #0x48
	bl FUN_02019270
	add r4, #0x48
	add r0, r4, #0
	bl FUN_02019548
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02255098: .word 0x02255400
	thumb_func_end MOD36_0225503C

	thumb_func_start MOD36_0225509C
MOD36_0225509C: ; 0x0225509C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _022550B8
	cmp r0, #1
	beq _022550C4
	pop {r3, r4, r5, pc}
_022550B8:
	mov r0, #1
	str r0, [r4, #0x5c]
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_022550C4:
	ldr r0, [r4]
	mov r2, #0xbe
	ldr r0, [r0, #8]
	ldr r1, [r4, #0x54]
	lsl r2, r2, #6
	bl FUN_02089444
	add r0, r4, #0
	add r0, #0x48
	bl FUN_02019178
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD36_02254F48
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD36_0225509C

	thumb_func_start MOD36_022550F4
MOD36_022550F4: ; 0x022550F4
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r0, #0x48
	bl FUN_02019548
	add r0, r4, #0
	bl MOD36_02254F48
	pop {r4, pc}
	thumb_func_end MOD36_022550F4

	thumb_func_start MOD36_0225510C
MOD36_0225510C: ; 0x0225510C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r1, [r4]
	ldr r0, [r1]
	lsl r2, r0, #1
	ldr r0, [r1, #4]
	mov r1, #0x14
	lsl r3, r0, #1
	asr r5, r3, #3
	asr r0, r2, #3
	mul r1, r5
	add r5, r0, r1
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x48
	mov r1, #1
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_020196F4
	ldr r1, [r4, #0x54]
	lsl r0, r5, #5
	add r0, r1, r0
	ldr r1, [r4, #0x58]
	mov r2, #0x20
	add r1, r1, r5
	lsl r1, r1, #5
	bl GXS_LoadBG3Char
	add r0, r6, #0
	bl MOD36_02254F48
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD36_0225510C

	thumb_func_start MOD36_02255164
MOD36_02255164: ; 0x02255164
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r0, #0x48
	bl FUN_02019548
	add r0, r4, #0
	bl MOD36_02254F48
	pop {r4, pc}
	thumb_func_end MOD36_02255164

	thumb_func_start MOD36_0225517C
MOD36_0225517C: ; 0x0225517C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r5, r0, #0
	ldr r0, _022551D4 ; =0x00005B74
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _0225519C
	mov r1, #2
	b _0225519E
_0225519C:
	mov r1, #1
_0225519E:
	ldr r0, [r4, #0x28]
	bl MOD20_02253F28
	ldr r0, _022551D8 ; =0x00005B75
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _022551B0
	mov r1, #4
	b _022551B2
_022551B0:
	mov r1, #3
_022551B2:
	ldr r0, [r4, #0x2c]
	bl MOD20_02253F28
	ldr r0, _022551DC ; =0x00005B76
	ldrb r0, [r5, r0]
	cmp r0, #0
	beq _022551C4
	mov r1, #6
	b _022551C6
_022551C4:
	mov r1, #5
_022551C6:
	ldr r0, [r4, #0x30]
	bl MOD20_02253F28
	add r0, r6, #0
	bl MOD36_02254F48
	pop {r4, r5, r6, pc}
	.align 2, 0
_022551D4: .word 0x00005B74
_022551D8: .word 0x00005B75
_022551DC: .word 0x00005B76
	thumb_func_end MOD36_0225517C

	thumb_func_start MOD36_022551E0
MOD36_022551E0: ; 0x022551E0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r0, r4, #0
	add r0, #0x48
	mov r1, #4
	bl FUN_02019620
	add r4, #0x48
	add r0, r4, #0
	bl FUN_02019548
	add r0, r5, #0
	bl MOD36_02254F48
	pop {r3, r4, r5, pc}
	thumb_func_end MOD36_022551E0

	thumb_func_start MOD36_0225520C
MOD36_0225520C: ; 0x0225520C
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
	beq _02255236
	ldr r1, [r4, #0x5c]
	cmp r1, #0
	beq _02255236
	add r0, r5, #0
	bl MOD36_02254F48
	pop {r3, r4, r5, pc}
_02255236:
	cmp r0, #4
	bls _0225523C
	b _0225539A
_0225523C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02255248: ; jump table
	.short _02255252 - _02255248 - 2 ; case 0
	.short _02255286 - _02255248 - 2 ; case 1
	.short _022552D8 - _02255248 - 2 ; case 2
	.short _02255322 - _02255248 - 2 ; case 3
	.short _02255356 - _02255248 - 2 ; case 4
_02255252:
	add r0, r4, #0
	add r0, #0x68
	ldrh r0, [r0]
	mov r1, #0x15
	lsl r1, r1, #4
	add r2, r0, r1
	add r0, r4, #0
	add r0, #0x68
	strh r2, [r0]
	add r0, r4, #0
	add r0, #0x6a
	strh r1, [r0]
	add r1, r4, #0
	add r1, #0x68
	ldrh r1, [r1]
	ldr r0, [r4, #0x24]
	bl MOD20_02253FB4
	mov r0, #0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	str r0, [r4, #0x5c]
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_02255286:
	add r0, r4, #0
	add r0, #0x68
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x6a
	ldrh r0, [r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x68
	strh r1, [r0]
	add r1, r4, #0
	add r1, #0x68
	ldrh r1, [r1]
	ldr r0, [r4, #0x24]
	bl MOD20_02253FB4
	add r0, r4, #0
	add r0, #0x6a
	ldrh r1, [r0]
	mov r0, #0x15
	lsl r0, r0, #4
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x6a
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x6a
	mov r1, #3
	ldrh r0, [r0]
	lsl r1, r1, #0xc
	cmp r0, r1
	blo _0225539A
	add r0, r4, #0
	add r0, #0x6a
	strh r1, [r0]
	mov r0, #1
	str r0, [r4, #0x64]
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_022552D8:
	add r0, r4, #0
	add r0, #0x68
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x6a
	ldrh r0, [r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x68
	strh r1, [r0]
	add r1, r4, #0
	add r1, #0x68
	ldrh r1, [r1]
	ldr r0, [r4, #0x24]
	bl MOD20_02253FB4
	ldr r0, [r4, #0x60]
	cmp r0, #0
	beq _0225539A
	bl rand_MT
	mov r1, #7
	and r0, r1
	str r0, [r4, #0x6c]
	add r0, r4, #0
	add r0, #0x6a
	ldrh r1, [r0]
	mov r0, #0x1a
	lsl r0, r0, #8
	cmp r1, r0
	bls _0225531A
	add r4, #0x6a
	strh r0, [r4]
_0225531A:
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_02255322:
	add r0, r4, #0
	add r0, #0x68
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x6a
	ldrh r0, [r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x68
	strh r1, [r0]
	add r1, r4, #0
	add r1, #0x68
	ldrh r1, [r1]
	ldr r0, [r4, #0x24]
	bl MOD20_02253FB4
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	bne _0225534E
	sub r0, r0, #1
	str r0, [r4, #0x6c]
	pop {r3, r4, r5, pc}
_0225534E:
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_02255356:
	add r0, r4, #0
	add r0, #0x6a
	ldrh r0, [r0]
	cmp r0, #0x50
	bls _0225538E
	add r0, r4, #0
	add r0, #0x6a
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x6a
	sub r1, #0x50
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x68
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x6a
	ldrh r0, [r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0x68
	strh r1, [r0]
	ldr r0, [r4, #0x24]
	add r4, #0x68
	ldrh r1, [r4]
	bl MOD20_02253FB4
	pop {r3, r4, r5, pc}
_0225538E:
	mov r0, #0
	add r4, #0x6a
	strh r0, [r4]
	add r0, r5, #0
	bl MOD36_02254F48
_0225539A:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD36_0225520C

	thumb_func_start MOD36_0225539C
MOD36_0225539C: ; 0x0225539C
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
	beq _022553BE
	cmp r0, #1
	beq _022553CA
	pop {r3, r4, r5, pc}
_022553BE:
	mov r0, #1
	str r0, [r4, #0x60]
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r3, r4, r5, pc}
_022553CA:
	add r0, r4, #0
	mov r1, #7
	bl MOD36_02254F30
	cmp r0, #0
	beq _022553E2
	ldr r0, _022553E4 ; =0x0000066A
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD36_02254F48
_022553E2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022553E4: .word 0x0000066A
	thumb_func_end MOD36_0225539C

	.section .rodata
	; 0x022553E8
	.byte 0x22, 0x42, 0xA7, 0xCF, 0x50, 0x70, 0xA7, 0xCF, 0x7E, 0x9E, 0xA7, 0xCF, 0xAD, 0x49, 0x25, 0x02
	.byte 0xF9, 0x49, 0x25, 0x02, 0xD5, 0x4D, 0x25, 0x02, 0x07, 0x02, 0x02, 0x14, 0x13, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00
	.byte 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00
	.byte 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0xB0, 0x0B, 0x00, 0x00, 0x20, 0x03, 0x00
	.byte 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x0B, 0x00, 0x00, 0x00, 0x06, 0x00
	.byte 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x0B, 0x00, 0x00, 0xE0, 0x08, 0x00
	.byte 0x05, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5D, 0x4F, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x9D, 0x50, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0xF5, 0x50, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x0D, 0x51, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x65, 0x51, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x7D, 0x51, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0xE1, 0x51, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x0D, 0x52, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x9D, 0x53, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; .section .sinit
	.global SDK_OVERLAY.MODULE_36.SINIT_START
	.global SDK_OVERLAY.MODULE_36.SINIT_END
SDK_OVERLAY.MODULE_36.SINIT_START:
	.word MOD36_02254840
	.word 0
SDK_OVERLAY.MODULE_36.SINIT_END:
