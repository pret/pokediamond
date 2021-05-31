	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD50_02254854
MOD50_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #8
	mov r1, #0x10
	str r2, [sp]
	add r5, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254894
	ldr r2, [sp]
	add r1, r7, #0
	add r3, r5, #0
	bl MOD50_0225489C
	cmp r0, #0
	beq _0225488E
	ldr r0, _02254898 ; =MOD50_022548D4
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	cmp r0, #0
	beq _0225488E
	str r4, [r6]
	str r5, [r4, #4]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488E:
	add r0, r4, #0
	bl FreeToHeap
_02254894:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254898: .word MOD50_022548D4
	thumb_func_end MOD50_02254854

	thumb_func_start MOD50_0225489C
MOD50_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, #8
	add r1, r5, #4
	bl MOD50_022549AC
	cmp r0, #0
	beq _022548BC
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548BC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD50_0225489C

	thumb_func_start MOD50_022548C0
MOD50_022548C0: ; 0x022548C0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl MOD50_022549E0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_022548C0

	thumb_func_start MOD50_022548D4
MOD50_022548D4: ; 0x022548D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _02254900
	lsl r2, r1, #2
	ldr r1, _02254904 ; =MOD50_02254B04
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254900
	add r0, r4, #0
	bl MOD50_022548C0
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0xc]
	bl MOD20_022529A0
_02254900:
	pop {r3, r4, r5, pc}
	nop
_02254904: .word MOD50_02254B04
	thumb_func_end MOD50_022548D4

	thumb_func_start MOD50_02254908
MOD50_02254908: ; 0x02254908
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD50_02254908

	thumb_func_start MOD50_02254910
MOD50_02254910: ; 0x02254910
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254918
	b _0225491A
_02254918:
	mov r1, #2
_0225491A:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD50_02254910

	thumb_func_start MOD50_02254924
MOD50_02254924: ; 0x02254924
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254934
	cmp r0, #1
	beq _02254944
	b _0225495E
_02254934:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD50_022549F8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _0225495E
_02254944:
	ldr r0, [r4, #8]
	mov r1, #0
	bl MOD50_02254A1C
	cmp r0, #0
	beq _0225495E
	ldr r0, [r4, #0xc]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD50_02254910
_0225495E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_02254924

	thumb_func_start MOD50_02254964
MOD50_02254964: ; 0x02254964
	push {r3, lr}
	ldrb r1, [r0, #2]
	cmp r1, #0
	beq _02254972
	mov r1, #2
	bl MOD50_02254910
_02254972:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD50_02254964

	thumb_func_start MOD50_02254978
MOD50_02254978: ; 0x02254978
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254988
	cmp r0, #1
	beq _02254998
	b _022549A6
_02254988:
	ldr r0, [r4, #8]
	mov r1, #1
	bl MOD50_022549F8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549A6
_02254998:
	ldr r0, [r4, #8]
	bl MOD50_02254A28
	cmp r0, #0
	beq _022549A6
	mov r0, #1
	pop {r4, pc}
_022549A6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_02254978

	thumb_func_start MOD50_022549AC
MOD50_022549AC: ; 0x022549AC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	beq _022549DA
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	mov r0, #8
	str r6, [r4]
	bl FUN_02016B94
	str r0, [r4, #4]
	cmp r0, #0
	beq _022549DA
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022549DA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD50_022549AC

	thumb_func_start MOD50_022549E0
MOD50_022549E0: ; 0x022549E0
	push {r4, lr}
	add r4, r0, #0
	beq _022549F6
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022549F0
	bl FreeToHeap
_022549F0:
	add r0, r4, #0
	bl FreeToHeap
_022549F6:
	pop {r4, pc}
	thumb_func_end MOD50_022549E0

	thumb_func_start MOD50_022549F8
MOD50_022549F8: ; 0x022549F8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254A18 ; =MOD50_02254B2C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254A18: .word MOD50_02254B2C
	thumb_func_end MOD50_022549F8

	thumb_func_start MOD50_02254A1C
MOD50_02254A1C: ; 0x02254A1C
	ldr r3, _02254A24 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254A24: .word MOD20_02253794
	thumb_func_end MOD50_02254A1C

	thumb_func_start MOD50_02254A28
MOD50_02254A28: ; 0x02254A28
	ldr r3, _02254A30 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254A30: .word MOD20_022537B8
	thumb_func_end MOD50_02254A28

	thumb_func_start MOD50_02254A34
MOD50_02254A34: ; 0x02254A34
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_02254A34

	thumb_func_start MOD50_02254A48
MOD50_02254A48: ; 0x02254A48
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254ADC ; =MOD50_02254B10
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #8
	str r1, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r3, #6
	bl GfGfxLoader_LoadCharData
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x18
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	ldr r0, [r5, #4]
	mov r1, #6
	add r3, r2, #0
	bl FUN_02018540
	mov r0, #0x20
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #0xc
	mov r1, #9
	mov r2, #4
	mov r3, #0
	bl GfGfxLoader_GXLoadPal
	ldr r1, [r5]
	ldr r0, [r5, #4]
	ldr r1, [r1]
	mov r2, #6
	bl MOD20_02253AA4
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254AE0 ; =0x04001000
	ldr r0, _02254AE4 ; =0xFFFFE0FF
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
	bl MOD50_02254A34
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254ADC: .word MOD50_02254B10
_02254AE0: .word 0x04001000
_02254AE4: .word 0xFFFFE0FF
	thumb_func_end MOD50_02254A48

	thumb_func_start MOD50_02254AE8
MOD50_02254AE8: ; 0x02254AE8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD50_02254A34
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD50_02254AE8

	.section .rodata

	.global MOD50_02254B04
MOD50_02254B04: ; 0x02254B04
	.word MOD50_02254924, MOD50_02254964, MOD50_02254978

	.global MOD50_02254B10
MOD50_02254B10: ; 0x02254B10
	.byte 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD50_02254B2C
MOD50_02254B2C: ; 0x02254B2C
	.word 0x00, MOD50_02254A48, 0x00
	.word 0x01, MOD50_02254AE8, 0x00
	.word 0x00, 0x00000000, 0x00
