	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	.extern MOD21_02254918

	thumb_func_start MOD21_02254930
MOD21_02254930: ; 0x02254930
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254966
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x10]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254968 ; =MOD21_02254D84
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254966
	add r0, r4, #0
	bl MOD21_02254918
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x28]
	bl MOD20_022529A0
_02254966:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254968: .word MOD21_02254D84
	thumb_func_end MOD21_02254930

	thumb_func_start MOD21_0225496C
MOD21_0225496C: ; 0x0225496C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD21_0225496C

	thumb_func_start MOD21_02254974
MOD21_02254974: ; 0x02254974
	cmp r2, #0
	beq _02254984
	cmp r2, #1
	bne _0225498C
	mov r0, #1
	str r0, [r3, #0x20]
	strb r0, [r3, #6]
	bx lr
_02254984:
	mov r0, #0
	str r0, [r3, #0x20]
	mov r0, #1
	strb r0, [r3, #6]
_0225498C:
	bx lr
	.align 2, 0
	thumb_func_end MOD21_02254974

	thumb_func_start MOD21_02254990
MOD21_02254990: ; 0x02254990
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254998
	b _0225499A
_02254998:
	mov r1, #2
_0225499A:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD21_02254990

	thumb_func_start MOD21_022549A4
MOD21_022549A4: ; 0x022549A4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549B4
	cmp r0, #1
	beq _022549C4
	b _022549DE
_022549B4:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD21_02254B10
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549DE
_022549C4:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD21_02254B34
	cmp r0, #0
	beq _022549DE
	ldr r0, [r4, #0x28]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD21_02254990
_022549DE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_022549A4

	thumb_func_start MOD21_022549E4
MOD21_022549E4: ; 0x022549E4
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549F8
	mov r1, #2
	bl MOD21_02254990
	mov r0, #0
	pop {r4, pc}
_022549F8:
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _02254A0A
	mov r0, #0
	strb r0, [r4, #6]
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl MOD21_02254B10
_02254A0A:
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD21_02254B34
	cmp r0, #0
	beq _02254A32
	ldr r0, [r4, #0x18]
	strb r0, [r4, #5]
	add r0, r4, #0
	add r0, #0x14
	bl GF_RTC_CopyTime
	ldrb r1, [r4, #5]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	beq _02254A32
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD21_02254B10
_02254A32:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_022549E4

	thumb_func_start MOD21_02254A38
MOD21_02254A38: ; 0x02254A38
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A48
	cmp r0, #1
	beq _02254A58
	b _02254A66
_02254A48:
	ldr r0, [r4, #0x24]
	mov r1, #3
	bl MOD21_02254B10
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A66
_02254A58:
	ldr r0, [r4, #0x24]
	bl MOD21_02254B40
	cmp r0, #0
	beq _02254A66
	mov r0, #1
	pop {r4, pc}
_02254A66:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_02254A38

	.section .rodata

	.global MOD21_02254D80
MOD21_02254D80: ; 0x02254D80
	.byte 0x10, 0xAF, 0x10, 0xCF

	.global MOD21_02254D84
MOD21_02254D84: ; 0x02254D84
	.word MOD21_022549A4, MOD21_022549E4, MOD21_02254A38
