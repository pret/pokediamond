	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD26_02254854
MOD26_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x9b
	add r5, r0, #0
	mov r0, #8
	lsl r1, r1, #2
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _0225489C
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD26_022548A8
	cmp r0, #0
	beq _02254896
	ldr r0, _022548A0 ; =MOD26_02254A4C
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	cmp r0, #0
	beq _02254896
	ldr r0, _022548A4 ; =MOD26_02254A30
	add r1, r4, #0
	str r4, [r5]
	bl MOD20_022529B4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02254896:
	add r0, r4, #0
	bl FreeToHeap
_0225489C:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022548A0: .word MOD26_02254A4C
_022548A4: .word MOD26_02254A30
	thumb_func_end MOD26_02254854

	thumb_func_start MOD26_022548A8
MOD26_022548A8: ; 0x022548A8
	push {r3, r4, r5, lr}
	add r4, r2, #0
	mov r2, #0x1f
	add r5, r0, #0
	lsl r2, r2, #4
	str r1, [r5, r2]
	add r1, r5, #0
	add r1, #0xc
	bl MOD26_022548E8
	mov r0, #0x7b
	lsl r0, r0, #2
	add r1, r5, #0
	add r0, r5, r0
	add r1, #0xc
	add r2, r4, #0
	bl MOD26_02254BD4
	cmp r0, #0
	beq _022548E4
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #0x19
	str r0, [r5, #4]
	mov r0, #0x15
	str r0, [r5, #8]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548E4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD26_022548A8

	thumb_func_start MOD26_022548E8
MOD26_022548E8: ; 0x022548E8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl MOD20_02252C3C
	add r6, r0, #0
	bl Sav2_Poketch_DotArtistIsEnabled
	cmp r0, #0
	beq _0225490E
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD26_02254918
	pop {r4, r5, r6, pc}
_0225490E:
	add r0, r4, #0
	bl MOD26_022549DC
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD26_022548E8

	thumb_func_start MOD26_02254918
MOD26_02254918: ; 0x02254918
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #0x7d
	add r5, r0, #0
	lsl r1, r1, #2
	add r0, r2, #0
	add r1, r5, r1
	bl Sav2_Poketch_DotArtistGetDrawing
	mov r3, #0
	mov r7, #0x7d
	mov ip, r3
	lsl r7, r7, #2
	mov r0, #3
_02254934:
	mov r2, #0
_02254936:
	asr r1, r3, #1
	lsr r1, r1, #0x1e
	add r1, r3, r1
	asr r1, r1, #2
	add r1, r5, r1
	add r6, r3, #0
	lsl r6, r6, #0x1e
	ldrb r1, [r1, r7]
	lsr r6, r6, #0x1d
	add r3, r3, #1
	asr r1, r6
	and r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r1, r1, #1
	strb r1, [r4, r2]
	add r2, r2, #1
	cmp r2, #0x18
	blt _02254936
	mov r1, ip
	add r1, r1, #1
	add r4, #0x18
	mov ip, r1
	cmp r1, #0x14
	blt _02254934
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD26_02254918

	thumb_func_start MOD26_0225496C
MOD26_0225496C: ; 0x0225496C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	mov r1, #0x7d
	str r2, [sp]
	lsl r1, r1, #2
	str r0, [sp, #4]
	add r0, r0, r1
	mov r1, #0
	mov r2, #0x78
	bl MI_CpuFill8
	mov r5, #0
	mov ip, r5
_02254988:
	mov r4, #0
_0225498A:
	asr r0, r5, #1
	lsr r0, r0, #0x1e
	add r0, r5, r0
	asr r1, r0, #2
	ldr r0, [sp, #4]
	add r6, r5, #0
	add r3, r0, r1
	mov r0, #0x7d
	lsl r0, r0, #2
	ldrb r2, [r3, r0]
	ldrb r0, [r7, r4]
	add r4, r4, #1
	add r5, r5, #1
	sub r1, r0, #1
	mov r0, #3
	and r0, r1
	lsl r1, r6, #0x1e
	lsr r1, r1, #0x1d
	lsl r0, r1
	add r1, r2, #0
	orr r1, r0
	mov r0, #0x7d
	lsl r0, r0, #2
	strb r1, [r3, r0]
	cmp r4, #0x18
	blt _0225498A
	mov r0, ip
	add r0, r0, #1
	add r7, #0x18
	mov ip, r0
	cmp r0, #0x14
	blt _02254988
	mov r2, #0x7d
	ldr r1, [sp, #4]
	lsl r2, r2, #2
	ldr r0, [sp]
	add r1, r1, r2
	bl Sav2_Poketch_DotArtistSetDrawingAndEnable
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD26_0225496C

	thumb_func_start MOD26_022549DC
MOD26_022549DC: ; 0x022549DC
	push {r4, r5}
	mov r4, #0
	ldr r5, _02254A00 ; =MOD26_02254DF0
	add r2, r4, #0
_022549E4:
	add r3, r2, #0
_022549E6:
	ldrb r1, [r5, r3]
	strb r1, [r0, r3]
	add r3, r3, #1
	cmp r3, #0x18
	blt _022549E6
	add r4, r4, #1
	add r5, #0x18
	add r0, #0x18
	cmp r4, #0x14
	blt _022549E4
	pop {r4, r5}
	bx lr
	nop
_02254A00: .word MOD26_02254DF0
	thumb_func_end MOD26_022549DC

	thumb_func_start MOD26_02254A04
MOD26_02254A04: ; 0x02254A04
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD20_02252C3C
	add r1, r4, #0
	add r2, r0, #0
	add r0, r4, #0
	add r1, #0xc
	bl MOD26_0225496C
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD26_02254C04
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD26_02254A04

	thumb_func_start MOD26_02254A30
MOD26_02254A30: ; 0x02254A30
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD20_02252C3C
	add r2, r0, #0
	add r0, r4, #0
	add r4, #0xc
	add r1, r4, #0
	bl MOD26_0225496C
	pop {r4, pc}
	thumb_func_end MOD26_02254A30

	thumb_func_start MOD26_02254A4C
MOD26_02254A4C: ; 0x02254A4C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _02254A7C
	lsl r2, r1, #2
	ldr r1, _02254A80 ; =MOD26_02254DE4
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254A7C
	add r0, r4, #0
	bl MOD26_02254A04
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD20_022529A0
_02254A7C:
	pop {r3, r4, r5, pc}
	nop
_02254A80: .word MOD26_02254DE4
	thumb_func_end MOD26_02254A4C

	thumb_func_start MOD26_02254A84
MOD26_02254A84: ; 0x02254A84
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD26_02254A84

	thumb_func_start MOD26_02254A8C
MOD26_02254A8C: ; 0x02254A8C
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254A94
	b _02254A96
_02254A94:
	mov r1, #2
_02254A96:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD26_02254A8C

	thumb_func_start MOD26_02254AA0
MOD26_02254AA0: ; 0x02254AA0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254AB0
	cmp r0, #1
	beq _02254AC4
	b _02254AE6
_02254AB0:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD26_02254C10
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254AE6
_02254AC4:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl MOD26_02254C34
	cmp r0, #0
	beq _02254AE6
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD26_02254A8C
_02254AE6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD26_02254AA0

	thumb_func_start MOD26_02254AEC
MOD26_02254AEC: ; 0x02254AEC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254B04
	mov r1, #2
	bl MOD26_02254A8C
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, pc}
_02254B04:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl MOD26_02254C34
	cmp r0, #0
	beq _02254B90
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252B68
	cmp r0, #0
	beq _02254B90
	ldr r1, [sp, #4]
	cmp r1, #0x10
	blo _02254B90
	ldr r0, [sp]
	cmp r0, #0x10
	blo _02254B90
	sub r1, #0x10
	lsr r2, r1, #3
	sub r0, #0x10
	lsr r1, r0, #3
	str r2, [sp, #4]
	str r1, [sp]
	cmp r2, #0x18
	bhs _02254B90
	cmp r1, #0x14
	bhs _02254B90
	ldr r0, [r4, #4]
	cmp r0, r2
	bne _02254B54
	ldr r0, [r4, #8]
	cmp r0, r1
	bne _02254B54
	bl FUN_02020AA4
	cmp r0, #1
	bne _02254B90
_02254B54:
	ldr r2, [sp]
	add r0, r4, #0
	mov r1, #0x18
	add r3, r2, #0
	add r0, #0xc
	mul r3, r1
	add r5, r0, r3
	ldr r3, [sp, #4]
	ldrb r2, [r5, r3]
	add r2, r2, #1
	strb r2, [r5, r3]
	ldr r2, [sp]
	mul r1, r2
	add r2, r0, r1
	ldr r1, [sp, #4]
	ldrb r0, [r2, r1]
	cmp r0, #4
	bls _02254B7C
	mov r0, #1
	strb r0, [r2, r1]
_02254B7C:
	ldr r0, [sp, #4]
	mov r1, #1
	str r0, [r4, #4]
	ldr r0, [sp]
	str r0, [r4, #8]
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD26_02254C10
_02254B90:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD26_02254AEC

	thumb_func_start MOD26_02254B98
MOD26_02254B98: ; 0x02254B98
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254BA8
	cmp r0, #1
	beq _02254BBC
	b _02254BCE
_02254BA8:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl MOD26_02254C10
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254BCE
_02254BBC:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD26_02254C40
	cmp r0, #0
	beq _02254BCE
	mov r0, #1
	pop {r4, pc}
_02254BCE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD26_02254B98

	thumb_func_start MOD26_02254BD4
MOD26_02254BD4: ; 0x02254BD4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254C00
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	cmp r0, #0
	beq _02254C00
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254C00:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD26_02254BD4

	thumb_func_start MOD26_02254C04
MOD26_02254C04: ; 0x02254C04
	push {r3, lr}
	cmp r0, #0
	beq _02254C0E
	bl FreeToHeap
_02254C0E:
	pop {r3, pc}
	thumb_func_end MOD26_02254C04

	thumb_func_start MOD26_02254C10
MOD26_02254C10: ; 0x02254C10
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254C30 ; =MOD26_02254FF0
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254C30: .word MOD26_02254FF0
	thumb_func_end MOD26_02254C10

	thumb_func_start MOD26_02254C34
MOD26_02254C34: ; 0x02254C34
	ldr r3, _02254C3C ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254C3C: .word MOD20_02253794
	thumb_func_end MOD26_02254C34

	thumb_func_start MOD26_02254C40
MOD26_02254C40: ; 0x02254C40
	ldr r3, _02254C48 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254C48: .word MOD20_022537B8
	thumb_func_end MOD26_02254C40

	thumb_func_start MOD26_02254C4C
MOD26_02254C4C: ; 0x02254C4C
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD26_02254C4C

	thumb_func_start MOD26_02254C60
MOD26_02254C60: ; 0x02254C60
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254CB8 ; =MOD26_02254FD4
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	bl MOD26_02254CC4
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl MOD26_02254DAC
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254CBC ; =0x04001000
	ldr r0, _02254CC0 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r4, #0
	bl MOD26_02254C4C
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254CB8: .word MOD26_02254FD4
_02254CBC: .word 0x04001000
_02254CC0: .word 0xFFFFE0FF
	thumb_func_end MOD26_02254C60

	thumb_func_start MOD26_02254CC4
MOD26_02254CC4: ; 0x02254CC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #4]
	mov r0, #8
	lsl r1, r0, #6
	bl AllocFromHeap
	str r0, [sp, #0x1c]
	cmp r0, #0
	beq _02254D68
	mov r0, #0
	str r0, [sp, #0x18]
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
	str r0, [sp, #0xc]
	str r0, [sp, #8]
	add r7, r0, #0
	add r6, r0, #0
	add r4, r0, #0
	add r5, r0, #0
_02254CEC:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	orr r1, r0
	ldr r0, [sp, #8]
	orr r0, r1
	orr r0, r7
	orr r0, r6
	orr r0, r4
	add r1, r5, #0
	orr r1, r0
	ldr r0, [sp, #0x18]
	orr r0, r1
	ldr r1, [sp, #0x14]
	add r1, r2, r1
	mov r2, #0x20
	bl MIi_CpuClearFast
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	add r0, #0x20
	str r0, [sp, #0x14]
	mov r0, #1
	lsl r0, r0, #0x18
	add r0, r1, r0
	str r0, [sp, #0x10]
	mov r0, #1
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0x1c
	add r0, r1, r0
	str r0, [sp, #0xc]
	mov r0, #1
	ldr r1, [sp, #8]
	lsl r0, r0, #0x14
	add r0, r1, r0
	str r0, [sp, #8]
	mov r0, #1
	lsl r0, r0, #0x10
	add r7, r7, r0
	lsr r0, r0, #4
	add r6, r6, r0
	mov r0, #1
	lsl r0, r0, #8
	add r4, r4, r0
	ldr r0, [sp, #0x18]
	add r5, #0x10
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0x10
	blt _02254CEC
	mov r0, #0
	str r0, [sp]
	mov r3, #2
	ldr r0, [sp, #4]
	ldr r2, [sp, #0x1c]
	mov r1, #6
	lsl r3, r3, #8
	bl FUN_02017E14
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
_02254D68:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD26_02254CC4

	thumb_func_start MOD26_02254D6C
MOD26_02254D6C: ; 0x02254D6C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r1, [r4]
	bl MOD26_02254DAC
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD26_02254C4C
	pop {r3, r4, r5, pc}
	thumb_func_end MOD26_02254D6C

	thumb_func_start MOD26_02254D90
MOD26_02254D90: ; 0x02254D90
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD26_02254C4C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD26_02254D90

	thumb_func_start MOD26_02254DAC
MOD26_02254DAC: ; 0x02254DAC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #6
	bl FUN_0201886C
	mov r5, #0
	ldr r1, _02254DE0 ; =MOD26_02254FD0
	add r0, #0x84
	add r2, r5, #0
_02254DBE:
	add r3, r2, #0
	add r6, r0, #0
_02254DC2:
	ldrb r7, [r4, r3]
	add r3, r3, #1
	add r7, r1, r7
	sub r7, r7, #1
	ldrb r7, [r7]
	strh r7, [r6]
	add r6, r6, #2
	cmp r3, #0x18
	blt _02254DC2
	add r5, r5, #1
	add r0, #0x40
	add r4, #0x18
	cmp r5, #0x14
	blt _02254DBE
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254DE0: .word MOD26_02254FD0
	thumb_func_end MOD26_02254DAC

	.section .rodata

	.global MOD26_02254DE4
MOD26_02254DE4: ; 0x02254DE4
	.word MOD26_02254AA0, MOD26_02254AEC, MOD26_02254B98

	.global MOD26_02254DF0
MOD26_02254DF0: ; 0x02254DF0
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1
	.byte 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1
	.byte 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 4, 1
	.byte 1, 1, 1, 4, 1, 1, 4, 4, 4, 1, 4, 1, 4, 1, 4, 4, 4, 1, 4, 4, 4, 1, 4, 1
	.byte 1, 1, 1, 4, 1, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 1, 1, 4, 1, 4, 1, 1, 1
	.byte 1, 1, 1, 4, 1, 1, 4, 4, 4, 1, 4, 4, 4, 1, 4, 4, 4, 1, 4, 1, 4, 1, 4, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1

	.global MOD26_02254FD0
MOD26_02254FD0: ; 0x02254FD0
	.byte 0x04, 0x0F, 0x08, 0x01

	.global MOD26_02254FD4
MOD26_02254FD4: ; 0x02254FD4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD26_02254FF0
MOD26_02254FF0: ; 0x02254FF0
	.word 0x00, MOD26_02254C60, 0x00
	.word 0x01, MOD26_02254D6C, 0x00
	.word 0x02, MOD26_02254D90, 0x00
	.word 0x00, 0x00000000, 0x00
