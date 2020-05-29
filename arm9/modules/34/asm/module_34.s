	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD34_02254840
MOD34_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD34_02254854
	ldr r1, _02254850 ; =MOD34_02254948
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD34_02254854
_02254850: .word MOD34_02254948
	thumb_func_end MOD34_02254840

	thumb_func_start MOD34_02254854
MOD34_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x38
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD34_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD34_0225490C
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
_02254898: .word MOD34_0225490C
	thumb_func_end MOD34_02254854

	thumb_func_start MOD34_0225489C
MOD34_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0x24
	add r1, r5, #4
	bl MOD34_02254A5C
	cmp r0, #0
	beq _022548DC
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0x28]
	mov r0, #8
	str r0, [sp]
	ldr r0, _022548E0 ; =0x02254C7C
	ldr r2, _022548E4 ; =MOD34_02254904
	mov r1, #6
	add r3, r5, #0
	bl MOD20_02254130
	str r0, [r5, #0x2c]
	mov r1, #0
	str r1, [r5, #0x30]
	mov r0, #1
_022548D0:
	add r1, r1, #1
	str r0, [r5, #8]
	add r5, r5, #4
	cmp r1, #6
	blt _022548D0
	pop {r3, r4, r5, pc}
_022548DC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022548E0: .word 0x02254C7C
_022548E4: .word MOD34_02254904
	thumb_func_end MOD34_0225489C

	thumb_func_start MOD34_022548E8
MOD34_022548E8: ; 0x022548E8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _022548F6
	bl MOD20_02254198
_022548F6:
	ldr r0, [r4, #0x24]
	bl MOD34_02254A8C
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD34_022548E8

	thumb_func_start MOD34_02254904
MOD34_02254904: ; 0x02254904
	str r1, [r3, #0x30]
	str r0, [r3, #0x34]
	bx lr
	.align 2, 0
	thumb_func_end MOD34_02254904

	thumb_func_start MOD34_0225490C
MOD34_0225490C: ; 0x0225490C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254942
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254944 ; =0x02254C70
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254942
	add r0, r4, #0
	bl MOD34_022548E8
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x28]
	bl MOD20_022529A0
_02254942:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254944: .word 0x02254C70
	thumb_func_end MOD34_0225490C

	thumb_func_start MOD34_02254948
MOD34_02254948: ; 0x02254948
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD34_02254948

	thumb_func_start MOD34_02254950
MOD34_02254950: ; 0x02254950
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254958
	b _0225495A
_02254958:
	mov r1, #2
_0225495A:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD34_02254950

	thumb_func_start MOD34_02254964
MOD34_02254964: ; 0x02254964
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254974
	cmp r0, #1
	beq _02254984
	b _0225499E
_02254974:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD34_02254A98
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _0225499E
_02254984:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD34_02254ABC
	cmp r0, #0
	beq _0225499E
	ldr r0, [r4, #0x28]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD34_02254950
_0225499E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD34_02254964

	thumb_func_start MOD34_022549A4
MOD34_022549A4: ; 0x022549A4
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549B8
	mov r1, #2
	bl MOD34_02254950
	mov r0, #0
	pop {r4, pc}
_022549B8:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549C4
	cmp r0, #1
	beq _022549F6
	b _02254A1A
_022549C4:
	ldr r0, [r4, #0x30]
	cmp r0, #1
	bne _02254A1A
	ldr r1, [r4, #0x34]
	lsl r0, r1, #2
	add r0, r4, r0
	ldr r0, [r0, #8]
	cmp r0, #0
	beq _022549EE
	strh r1, [r4, #0x20]
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl MOD34_02254A98
	ldr r0, _02254A20 ; =0x00000663
	bl MOD20_02252B28
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A1A
_022549EE:
	ldr r0, _02254A24 ; =0x0000066E
	bl MOD20_02252B28
	b _02254A1A
_022549F6:
	ldr r0, [r4, #0x30]
	cmp r0, #2
	bne _02254A0A
	ldr r0, [r4, #0x24]
	mov r1, #3
	bl MOD34_02254A98
	mov r0, #0
	strb r0, [r4, #1]
	b _02254A1A
_02254A0A:
	cmp r0, #3
	bne _02254A1A
	ldr r0, [r4, #0x24]
	mov r1, #3
	bl MOD34_02254A98
	mov r0, #0
	strb r0, [r4, #1]
_02254A1A:
	mov r0, #0
	pop {r4, pc}
	nop
_02254A20: .word 0x00000663
_02254A24: .word 0x0000066E
	thumb_func_end MOD34_022549A4

	thumb_func_start MOD34_02254A28
MOD34_02254A28: ; 0x02254A28
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A38
	cmp r0, #1
	beq _02254A48
	b _02254A56
_02254A38:
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD34_02254A98
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A56
_02254A48:
	ldr r0, [r4, #0x24]
	bl MOD34_02254AC8
	cmp r0, #0
	beq _02254A56
	mov r0, #1
	pop {r4, pc}
_02254A56:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD34_02254A28

	thumb_func_start MOD34_02254A5C
MOD34_02254A5C: ; 0x02254A5C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254A88
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	cmp r0, #0
	beq _02254A88
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A88:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD34_02254A5C

	thumb_func_start MOD34_02254A8C
MOD34_02254A8C: ; 0x02254A8C
	push {r3, lr}
	cmp r0, #0
	beq _02254A96
	bl FreeToHeap
_02254A96:
	pop {r3, pc}
	thumb_func_end MOD34_02254A8C

	thumb_func_start MOD34_02254A98
MOD34_02254A98: ; 0x02254A98
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254AB8 ; =0x02254CBC
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254AB8: .word 0x02254CBC
	thumb_func_end MOD34_02254A98

	thumb_func_start MOD34_02254ABC
MOD34_02254ABC: ; 0x02254ABC
	ldr r3, _02254AC4 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254AC4: .word MOD20_02253794
	thumb_func_end MOD34_02254ABC

	thumb_func_start MOD34_02254AC8
MOD34_02254AC8: ; 0x02254AC8
	ldr r3, _02254AD0 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254AD0: .word MOD20_022537B8
	thumb_func_end MOD34_02254AC8

	thumb_func_start MOD34_02254AD4
MOD34_02254AD4: ; 0x02254AD4
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD34_02254AD4

	thumb_func_start MOD34_02254AE8
MOD34_02254AE8: ; 0x02254AE8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	add r0, r1, #0
	bl MOD20_022538A0
	add r6, r0, #0
	ldr r0, [sp, #0x10]
	bl MOD20_022538A4
	add r5, r0, #0
	ldr r0, [r6, #4]
	ldr r2, _02254B8C ; =0x02254CA0
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
	ldr r2, [r6, #4]
	mov r0, #0xc
	mov r1, #0x3b
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r6, #4]
	mov r0, #0xc
	mov r1, #0x3a
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	mov r4, #0
	add r7, r4, #0
_02254B4A:
	ldr r2, [r5, #4]
	add r0, r6, #0
	add r1, r4, #0
	add r3, r7, #0
	bl MOD34_02254C1C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02254B4A
	ldr r0, [r6, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r0, _02254B90 ; =0x04001000
	ldr r1, _02254B94 ; =0xFFFFE0FF
	ldr r2, [r0]
	ldr r4, [r0]
	add r3, r2, #0
	and r3, r1
	lsl r1, r4, #0x13
	lsr r2, r1, #0x1b
	mov r1, #4
	orr r1, r2
	lsl r1, r1, #8
	orr r1, r3
	str r1, [r0]
	ldr r0, [sp, #0x10]
	str r4, [sp, #0x14]
	bl MOD34_02254AD4
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254B8C: .word 0x02254CA0
_02254B90: .word 0x04001000
_02254B94: .word 0xFFFFE0FF
	thumb_func_end MOD34_02254AE8

	thumb_func_start MOD34_02254B98
MOD34_02254B98: ; 0x02254B98
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD34_02254AD4
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD34_02254B98

	thumb_func_start MOD34_02254BB4
MOD34_02254BB4: ; 0x02254BB4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r3, r0, #0
	ldrh r1, [r3, #0x1c]
	add r0, r4, #0
	lsl r2, r1, #2
	add r2, r3, r2
	ldr r2, [r2, #4]
	mov r3, #1
	bl MOD34_02254C1C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD34_02254AD4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD34_02254BB4

	thumb_func_start MOD34_02254BE8
MOD34_02254BE8: ; 0x02254BE8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r3, r0, #0
	ldrh r1, [r3, #0x1c]
	add r0, r4, #0
	lsl r2, r1, #2
	add r2, r3, r2
	ldr r2, [r2, #4]
	mov r3, #0
	bl MOD34_02254C1C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD34_02254AD4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD34_02254BE8

	thumb_func_start MOD34_02254C1C
MOD34_02254C1C: ; 0x02254C1C
	push {r4, r5, r6, lr}
	ldr r0, [r0, #4]
	add r5, r1, #0
	mov r1, #6
	add r4, r2, #0
	add r6, r3, #0
	bl FUN_0201886C
	ldr r1, _02254C6C ; =0x02254C94
	lsl r2, r5, #1
	ldrh r1, [r1, r2]
	lsl r1, r1, #1
	add r2, r0, r1
	cmp r4, #0
	beq _02254C44
	add r1, r5, #1
	mov r0, #0x48
	add r5, r1, #0
	mul r5, r0
	b _02254C46
_02254C44:
	mov r5, #0
_02254C46:
	cmp r6, #0
	beq _02254C4C
	add r5, #0x24
_02254C4C:
	mov r3, #0
	add r0, r3, #0
_02254C50:
	add r1, r0, #0
	add r4, r2, #0
_02254C54:
	add r1, r1, #1
	strh r5, [r4]
	add r5, r5, #1
	add r4, r4, #2
	cmp r1, #6
	blt _02254C54
	add r3, r3, #1
	add r2, #0x40
	cmp r3, #6
	blt _02254C50
	pop {r4, r5, r6, pc}
	nop
_02254C6C: .word 0x02254C94
	thumb_func_end MOD34_02254C1C

	.section .rodata
	; 0x02254C70
	.byte 0x65, 0x49, 0x25, 0x02, 0xA5, 0x49, 0x25, 0x02, 0x29, 0x4A, 0x25, 0x02, 0x10, 0x40, 0x10, 0x40
	.byte 0x10, 0x40, 0xA0, 0xD0, 0x48, 0x78, 0x10, 0x40, 0x48, 0x78, 0xA0, 0xD0, 0x80, 0xB0, 0x10, 0x40
	.byte 0x80, 0xB0, 0xA0, 0xD0, 0x42, 0x00, 0x54, 0x00, 0x22, 0x01, 0x34, 0x01, 0x02, 0x02, 0x14, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE9, 0x4A, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x99, 0x4B, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xB5, 0x4B, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0xE9, 0x4B, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	; .section .sinit
	.global SDK_OVERLAY.MODULE_34.SINIT_START
	.global SDK_OVERLAY.MODULE_34.SINIT_END
SDK_OVERLAY.MODULE_34.SINIT_START:
	.word MOD34_02254840
	.word 0
SDK_OVERLAY.MODULE_34.SINIT_END:
