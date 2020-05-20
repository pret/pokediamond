    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FC52C

	.text

	thumb_func_start FUN_02084098
FUN_02084098: ; 0x02084098
	ldr r3, _020840A4 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _020840A8 ; =UNK_020FC52C
	mov r1, #0x6c
	bx r3
	nop
_020840A4: .word FUN_0202D8D0
_020840A8: .word UNK_020FC52C

	thumb_func_start FUN_020840AC
FUN_020840AC: ; 0x020840AC
	ldr r0, _020840B8 ; =0x00004A34
	ldr r1, [r3, r0]
	add r1, r1, #0x1
	str r1, [r3, r0]
	bx lr
	nop
_020840B8: .word 0x00004A34

	thumb_func_start FUN_020840BC
FUN_020840BC: ; 0x020840BC
	cmp r0, #0x0
	bne _020840C6
	ldrb r1, [r2, #0x0]
	ldr r0, _020840C8 ; =0x00004A3C
	str r1, [r3, r0]
_020840C6:
	bx lr
	.balign 4
_020840C8: .word 0x00004A3C

	thumb_func_start FUN_020840CC
FUN_020840CC: ; 0x020840CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0208410C ; =0x00004A34
	add r4, r3, #0x0
	mov r1, #0x0
	str r1, [r4, r0]
	mov r1, #0x1
	add r0, #0xc
	strb r1, [r4, r0]
	bl FUN_02031190
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02084270
	add r0, r4, #0x0
	bl MOD54_021D844C
	lsl r2, r5, #0x18
	add r0, r4, #0x0
	mov r1, #0x19
	lsr r2, r2, #0x18
	bl MOD54_021D88E4
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _02084110 ; =0x00000658
	bl FUN_020054C8
	pop {r3-r5, pc}
	.balign 4
_0208410C: .word 0x00004A34
_02084110: .word 0x00000658

	thumb_func_start FUN_02084114
FUN_02084114: ; 0x02084114
	add r0, r3, #0x0
	ldr r3, _02084120 ; =MOD54_021D88E4
	mov r1, #0x2
	mov r2, #0x0
	bx r3
	nop
_02084120: .word MOD54_021D88E4

	thumb_func_start FUN_02084124
FUN_02084124: ; 0x02084124
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	cmp r6, #0x0
	beq _020841BA
	bl FUN_02031190
	cmp r0, #0x0
	bne _02084204
	ldrb r0, [r5, #0x0]
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	ldrb r0, [r5, #0x1]
	strb r0, [r1, #0x1]
	ldrb r0, [r5, #0x2]
	strb r0, [r1, #0x2]
	ldrb r0, [r5, #0x3]
	strb r0, [r1, #0x3]
	ldr r0, _02084208 ; =0x00004A48
	strb r6, [r1, #0x0]
	ldr r0, [r4, r0]
	strb r0, [r1, #0x1]
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _0208415E
	cmp r0, #0x1
	b _020841AC
_0208415E:
	bl FUN_02030F20
	ldr r1, _02084208 ; =0x00004A48
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _02084186
	bl MOD54_021D8C24
	ldr r1, _02084208 ; =0x00004A48
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _02084186
	bl FUN_0202CB8C
	bl MATH_CountPopulation
	ldr r1, _02084208 ; =0x00004A48
	ldr r2, [r4, r1]
	cmp r2, r0
	beq _0208418E
_02084186:
	mov r1, #0x0
	add r0, sp, #0x0
	strb r1, [r0, #0x3]
	b _020841AC
_0208418E:
	add r0, r1, #0x0
	add r0, #0x8
	mov r2, #0x1
	ldr r3, [r4, r0]
	add r0, r2, #0x0
	lsl r0, r6
	orr r0, r3
	add r1, #0x8
	str r0, [r4, r1]
	add r0, sp, #0x0
	strb r2, [r0, #0x3]
	bl FUN_02030F20
	bl FUN_02032B6C
_020841AC:
	mov r0, #0x70
	add r1, sp, #0x0
	mov r2, #0x4
	bl FUN_02030ADC
	add sp, #0x4
	pop {r3-r6, pc}
_020841BA:
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _020841C8
	cmp r0, #0x1
	beq _020841FA
	add sp, #0x4
	pop {r3-r6, pc}
_020841C8:
	ldrb r6, [r5, #0x0]
	bl FUN_02031190
	cmp r6, r0
	bne _02084204
	ldrb r0, [r5, #0x3]
	cmp r0, #0x0
	bne _020841E6
	add r0, r4, #0x0
	mov r1, #0x8
	add r2, r6, #0x0
	bl MOD54_021D88E4
	add sp, #0x4
	pop {r3-r6, pc}
_020841E6:
	ldrb r1, [r5, #0x1]
	ldr r0, _0208420C ; =0x00004A5C
	strh r1, [r4, r0]
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x7
	bl MOD54_021D88E4
	add sp, #0x4
	pop {r3-r6, pc}
_020841FA:
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x13
	bl MOD54_021D88E4
_02084204:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02084208: .word 0x00004A48
_0208420C: .word 0x00004A5C

	thumb_func_start FUN_02084210
FUN_02084210: ; 0x02084210
	push {r4, lr}
	ldrb r2, [r2, #0x0]
	add r4, r3, #0x0
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD54_021D89CC
	bl FUN_02031190
	cmp r0, #0x0
	bne _0208422E
	mov r0, #0x3b
	mov r1, #0x0
	lsl r0, r0, #0x4
	str r1, [r4, r0]
_0208422E:
	pop {r4, pc}

	thumb_func_start FUN_02084230
FUN_02084230: ; 0x02084230
	bx lr
	.balign 4

	thumb_func_start FUN_02084234
FUN_02084234: ; 0x02084234
	bx lr
	.balign 4

	thumb_func_start FUN_02084238
FUN_02084238: ; 0x02084238
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _0208424E
	add r0, r4, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl MOD54_021D88E4
_0208424E:
	pop {r4, pc}

	thumb_func_start FUN_02084250
FUN_02084250: ; 0x02084250
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0208426C
	add r0, sp, #0x0
	strb r4, [r0, #0x0]
	mov r0, #0x6e
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_02030ADC
_0208426C:
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02084270
FUN_02084270: ; 0x02084270
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0xed
	mov r3, #0x0
	lsl r0, r0, #0x2
	add r5, r4, r0
	add r2, r3, #0x0
	sub r0, #0xc6
_02084280:
	ldr r1, [r5, #0x0]
	add r2, r2, #0x1
	eor r3, r1
	add r5, r5, #0x4
	cmp r2, r0
	blt _02084280
	ldr r0, _020842AC ; =0x00000F6C
	str r3, [r4, r0]
	bl rand_LC
	mov r1, #0xf7
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	mov r1, #0xed
	lsl r1, r1, #0x2
	mov r2, #0x2f
	mov r0, #0x74
	add r1, r4, r1
	lsl r2, r2, #0x6
	bl FUN_02030A78
	pop {r3-r5, pc}
	.balign 4
_020842AC: .word 0x00000F6C

	thumb_func_start FUN_020842B0
FUN_020842B0: ; 0x020842B0
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020842B4
FUN_020842B4: ; 0x020842B4
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020842B8
FUN_020842B8: ; 0x020842B8
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_020842BC
FUN_020842BC: ; 0x020842BC
	ldr r2, _020842CC ; =0x00000F74
	add r2, r1, r2
	mov r1, #0x2f
	lsl r1, r1, #0x6
	mul r1, r0
	add r0, r2, r1
	bx lr
	nop
_020842CC: .word 0x00000F74
