	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD32_02254840
MOD32_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD32_02254854
	ldr r1, _02254850 ; =MOD32_0225495C
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD32_02254854
_02254850: .word MOD32_0225495C
	thumb_func_end MOD32_02254840

	thumb_func_start MOD32_02254854
MOD32_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x1c
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD32_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD32_02254920
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
_02254898: .word MOD32_02254920
	thumb_func_end MOD32_02254854

	thumb_func_start MOD32_0225489C
MOD32_0225489C: ; 0x0225489C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0
	add r1, sp, #4
	add r6, r2, #0
	bl PM_GetBackLight
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _022548B8
	mov r0, #1
	b _022548BA
_022548B8:
	mov r0, #0
_022548BA:
	str r0, [r5, #4]
	add r0, r5, #0
	add r0, #8
	add r1, r5, #4
	add r2, r6, #0
	bl MOD32_02254A54
	cmp r0, #0
	beq _022548F2
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _022548F8 ; =0x02254C54
	ldr r2, _022548FC ; =MOD32_02254918
	mov r1, #2
	add r3, r5, #0
	bl MOD20_02254130
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [r5, #0x14]
	add sp, #8
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022548F2:
	mov r0, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_022548F8: .word 0x02254C54
_022548FC: .word MOD32_02254918
	thumb_func_end MOD32_0225489C

	thumb_func_start MOD32_02254900
MOD32_02254900: ; 0x02254900
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl MOD20_02254198
	ldr r0, [r4, #8]
	bl MOD32_02254A90
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}
	thumb_func_end MOD32_02254900

	thumb_func_start MOD32_02254918
MOD32_02254918: ; 0x02254918
	str r0, [r3, #0x18]
	str r1, [r3, #0x14]
	bx lr
	.align 2, 0
	thumb_func_end MOD32_02254918

	thumb_func_start MOD32_02254920
MOD32_02254920: ; 0x02254920
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254956
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254958 ; =0x02254C5C
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254956
	add r0, r4, #0
	bl MOD32_02254900
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0xc]
	bl MOD20_022529A0
_02254956:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254958: .word 0x02254C5C
	thumb_func_end MOD32_02254920

	thumb_func_start MOD32_0225495C
MOD32_0225495C: ; 0x0225495C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD32_0225495C

	thumb_func_start MOD32_02254964
MOD32_02254964: ; 0x02254964
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _0225496C
	b _0225496E
_0225496C:
	mov r1, #2
_0225496E:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD32_02254964

	thumb_func_start MOD32_02254978
MOD32_02254978: ; 0x02254978
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254988
	cmp r0, #1
	beq _02254998
	b _022549B2
_02254988:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD32_02254B08
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549B2
_02254998:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD32_02254B2C
	cmp r0, #0
	beq _022549B2
	ldr r0, [r4, #0xc]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD32_02254964
_022549B2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD32_02254978

	thumb_func_start MOD32_022549B8
MOD32_022549B8: ; 0x022549B8
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549CC
	mov r1, #2
	bl MOD32_02254964
	mov r0, #0
	pop {r4, pc}
_022549CC:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549D8
	cmp r0, #1
	beq _02254A0C
	b _02254A1C
_022549D8:
	ldr r0, [r4, #0x14]
	cmp r0, #1
	bne _02254A1C
	ldr r1, [r4, #0x18]
	cmp r1, #0
	bne _022549EA
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022549F4
_022549EA:
	cmp r1, #1
	bne _02254A04
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _02254A04
_022549F4:
	ldr r1, [r4, #4]
	mov r0, #1
	eor r0, r1
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD32_02254B08
_02254A04:
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A1C
_02254A0C:
	ldr r0, [r4, #8]
	mov r1, #2
	bl MOD32_02254B2C
	cmp r0, #0
	beq _02254A1C
	mov r0, #0
	strb r0, [r4, #1]
_02254A1C:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD32_022549B8

	thumb_func_start MOD32_02254A20
MOD32_02254A20: ; 0x02254A20
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A30
	cmp r0, #1
	beq _02254A40
	b _02254A4E
_02254A30:
	ldr r0, [r4, #8]
	mov r1, #1
	bl MOD32_02254B08
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A4E
_02254A40:
	ldr r0, [r4, #8]
	bl MOD32_02254B38
	cmp r0, #0
	beq _02254A4E
	mov r0, #1
	pop {r4, pc}
_02254A4E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD32_02254A20

	thumb_func_start MOD32_02254A54
MOD32_02254A54: ; 0x02254A54
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x3c
	bl FUN_02016998
	add r4, r0, #0
	beq _02254A8A
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD32_02254A9C
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A8A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD32_02254A54

	thumb_func_start MOD32_02254A90
MOD32_02254A90: ; 0x02254A90
	push {r3, lr}
	cmp r0, #0
	beq _02254A9A
	bl FUN_02016A18
_02254A9A:
	pop {r3, pc}
	thumb_func_end MOD32_02254A90

	thumb_func_start MOD32_02254A9C
MOD32_02254A9C: ; 0x02254A9C
	push {r4, r5, lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r5, r0, #0
	add r4, r1, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x68
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	add r0, #0x28
	mov r1, #0xc
	mov r2, #0x66
	mov r3, #0x67
	bl MOD20_02253FBC
	add r2, r5, #0
	ldr r0, [r5, #0x20]
	ldr r1, _02254AEC ; =0x02254C68
	add r2, #0x28
	bl MOD20_02253E74
	str r0, [r5, #0x24]
	ldr r0, [r4]
	cmp r0, #0
	bne _02254AE6
	ldr r0, [r5, #0x24]
	mov r1, #1
	bl MOD20_02253F28
_02254AE6:
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02254AEC: .word 0x02254C68
	thumb_func_end MOD32_02254A9C

	thumb_func_start MOD32_02254AF0
MOD32_02254AF0: ; 0x02254AF0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	bl MOD20_02253F14
	add r4, #0x28
	add r0, r4, #0
	bl MOD20_02254014
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD32_02254AF0

	thumb_func_start MOD32_02254B08
MOD32_02254B08: ; 0x02254B08
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B28 ; =0x02254C94
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B28: .word 0x02254C94
	thumb_func_end MOD32_02254B08

	thumb_func_start MOD32_02254B2C
MOD32_02254B2C: ; 0x02254B2C
	ldr r3, _02254B34 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254B34: .word MOD20_02253794
	thumb_func_end MOD32_02254B2C

	thumb_func_start MOD32_02254B38
MOD32_02254B38: ; 0x02254B38
	ldr r3, _02254B40 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254B40: .word MOD20_022537B8
	thumb_func_end MOD32_02254B38

	thumb_func_start MOD32_02254B44
MOD32_02254B44: ; 0x02254B44
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD32_02254B44

	thumb_func_start MOD32_02254B58
MOD32_02254B58: ; 0x02254B58
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254BDC ; =0x02254C78
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
	mov r1, #0x65
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
	mov r1, #0x64
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254BE0 ; =0x04001000
	ldr r0, _02254BE4 ; =0xFFFFE0FF
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
	bl MOD32_02254B44
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254BDC: .word 0x02254C78
_02254BE0: .word 0x04001000
_02254BE4: .word 0xFFFFE0FF
	thumb_func_end MOD32_02254B58

	thumb_func_start MOD32_02254BE8
MOD32_02254BE8: ; 0x02254BE8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD32_02254AF0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD32_02254B44
	pop {r3, r4, r5, pc}
	thumb_func_end MOD32_02254BE8

	thumb_func_start MOD32_02254C08
MOD32_02254C08: ; 0x02254C08
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	ldr r0, _02254C50 ; =0x00000663
	bl MOD20_02252B28
	ldr r0, [r4]
	cmp r0, #0
	ldr r0, [r5, #0x24]
	beq _02254C3A
	mov r1, #0
	bl MOD20_02253F28
	mov r0, #1
	add r1, r0, #0
	bl PM_SetBackLight
	b _02254C48
_02254C3A:
	mov r1, #1
	bl MOD20_02253F28
	mov r0, #1
	mov r1, #0
	bl PM_SetBackLight
_02254C48:
	add r0, r6, #0
	bl MOD32_02254B44
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254C50: .word 0x00000663
	thumb_func_end MOD32_02254C08

	.section .data
	; 0x02254C54
	.incbin "baserom.nds", 0x28DC14, 0x8C
