    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02058EE8
FUN_02058EE8: ; 0x02058EE8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058638
	add r0, r4, #0x0
	bl FUN_0205BEF8
	pop {r4, pc}

	thumb_func_start FUN_02058EF8
FUN_02058EF8: ; 0x02058EF8
	push {r4, lr}
	mov r1, #0x2
	add r4, r0, #0x0
	bl FUN_020587F4
	cmp r0, #0x0
	bne _02058F5C
	add r0, r4, #0x0
	bl FUN_02058F94
	add r0, r4, #0x0
	bl FUN_02058FAC
	add r0, r4, #0x0
	bl FUN_02058FD0
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058F2C
	add r0, r4, #0x0
	bl FUN_0205B058
	b _02058F50
_02058F2C:
	add r0, r4, #0x0
	bl FUN_02058920
	cmp r0, #0x0
	bne _02058F50
	add r0, r4, #0x0
	bl FUN_02058F60
	cmp r0, #0x1
	bne _02058F50
	add r0, r4, #0x0
	bl FUN_0205BF00
	cmp r0, #0x0
	bne _02058F50
	add r0, r4, #0x0
	bl FUN_0205864C
_02058F50:
	add r0, r4, #0x0
	bl FUN_02058FF4
	add r0, r4, #0x0
	bl FUN_0205902C
_02058F5C:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02058F60
FUN_02058F60: ; 0x02058F60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x1
	bne _02058F70
	mov r0, #0x1
	pop {r4, pc}
_02058F70:
	mov r1, #0x6
	add r0, r4, #0x0
	lsl r1, r1, #0xa
	bl FUN_02058424
	cmp r0, #0x0
	bne _02058F82
	mov r0, #0x1
	pop {r4, pc}
_02058F82:
	add r0, r4, #0x0
	bl FUN_02058480
	cmp r0, #0x32
	bne _02058F90
	mov r0, #0x1
	pop {r4, pc}
_02058F90:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02058F94
FUN_02058F94: ; 0x02058F94
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xc
	add r4, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058FAA
	add r0, r4, #0x0
	bl FUN_02059D1C
_02058FAA:
	pop {r4, pc}

	thumb_func_start FUN_02058FAC
FUN_02058FAC: ; 0x02058FAC
	push {r4, lr}
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r4, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058FCC
	add r0, r4, #0x0
	bl FUN_02059DB4
	cmp r0, #0x1
	bne _02058FCC
	add r0, r4, #0x0
	bl FUN_02058860
_02058FCC:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02058FD0
FUN_02058FD0: ; 0x02058FD0
	push {r4, lr}
	mov r1, #0x4
	add r4, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	beq _02058FE4
	add r0, r4, #0x0
	bl FUN_02059064
_02058FE4:
	ldr r1, _02058FF0 ; =0x00010004
	add r0, r4, #0x0
	bl FUN_02058418
	pop {r4, pc}
	nop
_02058FF0: .word 0x00010004

	thumb_func_start FUN_02058FF4
FUN_02058FF4: ; 0x02058FF4
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0x10
	add r4, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205900C
	add r0, r4, #0x0
	bl FUN_020591A8
	b _0205901E
_0205900C:
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02058424
	cmp r0, #0x0
	beq _0205901E
	add r0, r4, #0x0
	bl FUN_020590F4
_0205901E:
	ldr r1, _02059028 ; =0x00010004
	add r0, r4, #0x0
	bl FUN_02058418
	pop {r4, pc}
	.balign 4
_02059028: .word 0x00010004

	thumb_func_start FUN_0205902C
FUN_0205902C: ; 0x0205902C
	push {r4, lr}
	mov r1, #0x2
	lsl r1, r1, #0x10
	add r4, r0, #0x0
	bl FUN_02058424
	cmp r0, #0x0
	beq _02059044
	add r0, r4, #0x0
	bl FUN_0205928C
	b _02059056
_02059044:
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02058424
	cmp r0, #0x0
	beq _02059056
	add r0, r4, #0x0
	bl FUN_02059214
_02059056:
	ldr r1, _02059060 ; =0x00020008
	add r0, r4, #0x0
	bl FUN_02058418
	pop {r4, pc}
	.balign 4
_02059060: .word 0x00020008

	thumb_func_start FUN_02059064
FUN_02059064: ; 0x02059064
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02059DB4
	add r0, r5, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _020590F2
	add r0, r5, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0x0
	bl FUN_02058730
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	bl MOD05_021F1DC8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059838
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205941C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020594C0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059500
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205931C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059678
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020596A8
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020597A8
_020590F2:
	pop {r3-r7, pc}

	thumb_func_start FUN_020590F4
FUN_020590F4: ; 0x020590F4
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02059DB4
	add r0, r5, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _020591A6
	add r0, r5, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0x0
	bl FUN_02058730
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	bl MOD05_021F1DC8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059838
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059434
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205944C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020594C0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059508
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059690
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020596C0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020596D8
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059740
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020597A8
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059870
_020591A6:
	pop {r3-r7, pc}

	thumb_func_start FUN_020591A8
FUN_020591A8: ; 0x020591A8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02059DB4
	add r0, r5, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _02059212
	add r0, r5, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0x0
	bl FUN_02058730
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	bl MOD05_021F1DC8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059838
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059508
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020597A8
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020594F4
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059870
_02059212:
	pop {r3-r7, pc}

	thumb_func_start FUN_02059214
FUN_02059214: ; 0x02059214
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02059DB4
	add r0, r5, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _0205928A
	add r0, r5, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0x0
	bl FUN_02058730
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	bl MOD05_021F1DC8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205931C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205970C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059774
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020594C0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059804
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020595A4
_0205928A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0205928C
FUN_0205928C: ; 0x0205928C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02059DB4
	add r0, r5, #0x0
	bl FUN_02058934
	cmp r0, #0x1
	bne _0205931A
	add r0, r5, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	add r0, r5, #0x0
	bl FUN_02058730
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	bl MOD05_021F1DC8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205931C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205970C
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059774
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020594C0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059804
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_020595A4
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_02059434
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0205962C
_0205931A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0205931C
FUN_0205931C: ; 0x0205931C
	push {r3-r5, lr}
	sub sp, #0x48
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_02058A34
	cmp r0, #0x0
	bne _020593F4
	add r0, r5, #0x0
	bl FUN_02054984
	cmp r0, #0x1
	beq _02059340
	add r0, r5, #0x0
	bl FUN_020549A0
	cmp r0, #0x1
	bne _0205935A
_02059340:
	ldr r5, _02059408 ; =0x020F65FC
	add r3, sp, #0x3c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_02058BD4
	add sp, #0x48
	pop {r3-r5, pc}
_0205935A:
	add r0, r5, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	beq _0205936E
	add r0, r5, #0x0
	bl FUN_02054990
	cmp r0, #0x1
	bne _02059388
_0205936E:
	ldr r5, _0205940C ; =0x020F6608
	add r3, sp, #0x30
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_02058BD4
	add sp, #0x48
	pop {r3-r5, pc}
_02059388:
	add r0, r5, #0x0
	bl FUN_020549F0
	cmp r0, #0x1
	bne _020593AC
	ldr r5, _02059410 ; =0x020F65E4
	add r3, sp, #0x24
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_02058BD4
	add sp, #0x48
	pop {r3-r5, pc}
_020593AC:
	add r0, r5, #0x0
	bl FUN_020549E4
	cmp r0, #0x1
	bne _020593D0
	ldr r5, _02059414 ; =0x020F65F0
	add r3, sp, #0x18
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_02058BD4
	add sp, #0x48
	pop {r3-r5, pc}
_020593D0:
	add r0, r5, #0x0
	bl FUN_020549D8
	cmp r0, #0x1
	bne _020593F4
	ldr r5, _02059418 ; =0x020F6614
	add r3, sp, #0xc
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	bl FUN_02058BD4
	add sp, #0x48
	pop {r3-r5, pc}
_020593F4:
	add r1, sp, #0x0
	mov r0, #0x0
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	add r0, r4, #0x0
	bl FUN_02058BD4
	add sp, #0x48
	pop {r3-r5, pc}
	.balign 4
_02059408: .word 0x020F65FC
_0205940C: .word 0x020F6608
_02059410: .word 0x020F65E4
_02059414: .word 0x020F65F0
_02059418: .word 0x020F6614

	thumb_func_start FUN_0205941C
FUN_0205941C: ; 0x0205941C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0205478C
	cmp r0, #0x1
	bne _02059432
	add r0, r4, #0x0
	mov r1, #0x0
	bl MOD06_0224B568
_02059432:
	pop {r4, pc}

	thumb_func_start FUN_02059434
FUN_02059434: ; 0x02059434
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0205478C
	cmp r0, #0x1
	bne _0205944A
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD06_0224B568
_0205944A:
	pop {r4, pc}

	thumb_func_start FUN_0205944C
FUN_0205944C: ; 0x0205944C
	push {r4-r6, lr}
	add r6, r3, #0x0
	ldr r1, [r6, #0x4]
	add r5, r0, #0x0
	lsl r1, r1, #0x16
	add r4, r2, #0x0
	lsr r1, r1, #0x1c
	beq _020594BC
	add r1, r4, #0x0
	bl FUN_02059AF8
	cmp r0, #0x1
	bne _02059484
	ldr r0, [r6, #0x4]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1c
	cmp r0, #0x1
	bne _02059478
	add r0, r5, #0x0
	bl MOD06_02249E6C
	pop {r4-r6, pc}
_02059478:
	cmp r0, #0x2
	bne _020594BC
	add r0, r5, #0x0
	bl MOD06_02249E78
	pop {r4-r6, pc}
_02059484:
	add r0, r4, #0x0
	bl FUN_020549E4
	cmp r0, #0x1
	beq _020594A2
	add r0, r4, #0x0
	bl FUN_020549F0
	cmp r0, #0x1
	beq _020594A2
	add r0, r4, #0x0
	bl FUN_020549D8
	cmp r0, #0x0
	beq _020594AA
_020594A2:
	add r0, r5, #0x0
	bl MOD06_02249E90
	pop {r4-r6, pc}
_020594AA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059B60
	cmp r0, #0x1
	bne _020594BC
	add r0, r5, #0x0
	bl MOD06_02249E84
_020594BC:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020594C0
FUN_020594C0: ; 0x020594C0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0205483C
	cmp r0, #0x1
	bne _020594EA
	add r0, r4, #0x0
	bl FUN_02058A00
	cmp r0, #0x0
	bne _020594F2
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD06_0224B9E0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020589E4
	pop {r4, pc}
_020594EA:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020589E4
_020594F2:
	pop {r4, pc}

	thumb_func_start FUN_020594F4
FUN_020594F4: ; 0x020594F4
	ldr r3, _020594FC ; =FUN_020589E4
	mov r1, #0x0
	bx r3
	nop
_020594FC: .word FUN_020589E4

	thumb_func_start FUN_02059500
FUN_02059500: ; 0x02059500
	push {r3, lr}
	bl FUN_02059508
	pop {r3, pc}

	thumb_func_start FUN_02059508
FUN_02059508: ; 0x02059508
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r3, #0x0
	bl FUN_02058578
	bl FUN_0205881C
	cmp r0, #0x0
	beq _020595A2
	ldr r0, [r6, #0x4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	beq _020595A2
	add r0, r4, #0x0
	bl FUN_0205478C
	cmp r0, #0x1
	beq _02059578
	add r0, r4, #0x0
	bl FUN_02054798
	cmp r0, #0x1
	beq _02059578
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059AC4
	cmp r0, #0x1
	beq _02059578
	add r0, r4, #0x0
	bl FUN_02054AF0
	cmp r0, #0x1
	beq _02059578
	add r0, r4, #0x0
	bl FUN_0205483C
	cmp r0, #0x1
	beq _02059578
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059B2C
	cmp r0, #0x1
	beq _02059578
	add r0, r4, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	beq _02059578
	add r0, r4, #0x0
	bl FUN_02054990
	cmp r0, #0x1
	bne _02059584
_02059578:
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r4-r6, pc}
_02059584:
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058424
	cmp r0, #0x0
	bne _020595A2
	add r0, r5, #0x0
	bl MOD06_02249508
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0xe
	bl FUN_02058410
_020595A2:
	pop {r4-r6, pc}

	thumb_func_start FUN_020595A4
FUN_020595A4: ; 0x020595A4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r3, #0x0
	bl FUN_02058578
	bl FUN_0205881C
	cmp r0, #0x0
	beq _0205962A
	ldr r0, [r6, #0x4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	beq _0205962A
	add r0, r4, #0x0
	bl FUN_0205478C
	cmp r0, #0x1
	beq _02059614
	add r0, r4, #0x0
	bl FUN_02054798
	cmp r0, #0x1
	beq _02059614
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059AC4
	cmp r0, #0x1
	beq _02059614
	add r0, r4, #0x0
	bl FUN_02054AF0
	cmp r0, #0x1
	beq _02059614
	add r0, r4, #0x0
	bl FUN_0205483C
	cmp r0, #0x1
	beq _02059614
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059B2C
	cmp r0, #0x1
	beq _02059614
	add r0, r4, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	beq _02059614
	add r0, r4, #0x0
	bl FUN_02054990
	cmp r0, #0x1
	bne _02059620
_02059614:
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058410
	pop {r4-r6, pc}
_02059620:
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x14
	bl FUN_02058418
_0205962A:
	pop {r4-r6, pc}

	thumb_func_start FUN_0205962C
FUN_0205962C: ; 0x0205962C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02059AC4
	cmp r0, #0x1
	beq _02059674
	add r0, r4, #0x0
	bl FUN_0205483C
	cmp r0, #0x1
	beq _02059674
	add r0, r4, #0x0
	bl FUN_020548F0
	cmp r0, #0x1
	beq _02059674
	add r0, r4, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	beq _02059674
	add r0, r4, #0x0
	bl FUN_02054990
	cmp r0, #0x1
	beq _02059674
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02059B2C
	cmp r0, #0x1
	beq _02059674
	add r0, r5, #0x0
	bl MOD06_0224BBEC
_02059674:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02059678
FUN_02059678: ; 0x02059678
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02054798
	cmp r0, #0x1
	bne _0205968E
	add r0, r4, #0x0
	mov r1, #0x0
	bl MOD06_0224BD90
_0205968E:
	pop {r4, pc}

	thumb_func_start FUN_02059690
FUN_02059690: ; 0x02059690
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02054798
	cmp r0, #0x1
	bne _020596A6
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD06_0224BD90
_020596A6:
	pop {r4, pc}

	thumb_func_start FUN_020596A8
FUN_020596A8: ; 0x020596A8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02054990
	cmp r0, #0x1
	bne _020596BE
	add r0, r4, #0x0
	mov r1, #0x0
	bl MOD06_0224C038
_020596BE:
	pop {r4, pc}

	thumb_func_start FUN_020596C0
FUN_020596C0: ; 0x020596C0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02054990
	cmp r0, #0x1
	bne _020596D6
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD06_0224C038
_020596D6:
	pop {r4, pc}

	thumb_func_start FUN_020596D8
FUN_020596D8: ; 0x020596D8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	bl FUN_02054AF0
	cmp r0, #0x1
	bne _02059708
	add r0, r5, #0x0
	bl FUN_02058B14
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B1C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B24
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl MOD06_0224B124
_02059708:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0205970C
FUN_0205970C: ; 0x0205970C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02054AF0
	cmp r0, #0x1
	bne _0205973C
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B3C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl MOD06_0224B124
_0205973C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02059740
FUN_02059740: ; 0x02059740
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	bne _02059770
	add r0, r5, #0x0
	bl FUN_02058B14
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B1C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B24
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl MOD06_0224B2C4
_02059770:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02059774
FUN_02059774: ; 0x02059774
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02054974
	cmp r0, #0x1
	bne _020597A4
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B3C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl MOD06_0224B2C4
_020597A4:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020597A8
FUN_020597A8: ; 0x020597A8
	push {r4-r6, lr}
	add r6, r1, #0x0
	ldr r1, [r3, #0x4]
	add r5, r0, #0x0
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1e
	beq _02059802
	mov r1, #0x1
	bl FUN_02059C90
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	bl FUN_02058A9C
	cmp r0, #0x0
	bne _02059802
	add r0, r4, #0x0
	bl FUN_02054B20
	cmp r0, #0x1
	beq _020597DE
	add r0, r6, #0x0
	bl FUN_02054B20
	cmp r0, #0x1
	bne _02059802
_020597DE:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058A80
	add r0, r4, #0x0
	bl FUN_02054AF0
	cmp r0, #0x1
	bne _020597FA
	add r0, r5, #0x0
	mov r1, #0x0
	bl MOD06_022497E8
	pop {r4-r6, pc}
_020597FA:
	add r0, r5, #0x0
	mov r1, #0x1
	bl MOD06_022497E8
_02059802:
	pop {r4-r6, pc}

	thumb_func_start FUN_02059804
FUN_02059804: ; 0x02059804
	push {r4, lr}
	ldr r1, [r3, #0x4]
	add r4, r0, #0x0
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1e
	beq _02059834
	bl FUN_02058A9C
	cmp r0, #0x0
	beq _02059834
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02059C90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054B20
	cmp r0, #0x0
	bne _02059834
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02058A80
_02059834:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02059838
FUN_02059838: ; 0x02059838
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054B6C
	cmp r0, #0x1
	bne _02059852
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058A4C
	pop {r3-r5, pc}
_02059852:
	add r0, r5, #0x0
	bl FUN_02058A68
	cmp r0, #0x1
	bne _0205986E
	add r0, r4, #0x0
	bl FUN_02054B78
	cmp r0, #0x0
	bne _0205986E
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058A4C
_0205986E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02059870
FUN_02059870: ; 0x02059870
	bx lr
	.balign 4

	thumb_func_start FUN_02059874
FUN_02059874: ; 0x02059874
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r7, [sp, #0x28]
	add r5, r2, #0x0
	str r1, [sp, #0x4]
	str r3, [sp, #0x8]
	add r2, r3, #0x0
	add r1, r5, #0x0
	add r3, r7, #0x0
	add r6, r0, #0x0
	mov r4, #0x0
	bl FUN_02059A08
	cmp r0, #0x1
	bne _02059896
	mov r0, #0x1
	orr r4, r0
_02059896:
	add r0, r6, #0x0
	bl FUN_02058738
	add r1, sp, #0xc
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r2, r5, #0x0
	add r3, r7, #0x0
	bl FUN_0204A770
	cmp r0, #0x1
	bne _020598C0
	mov r0, #0x2
	orr r4, r0
	add r1, sp, #0xc
	mov r0, #0x0
	ldrsb r0, [r1, r0]
	cmp r0, #0x0
	beq _020598C0
	mov r0, #0x8
	orr r4, r0
_020598C0:
	ldr r3, [sp, #0x2c]
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl FUN_02059A60
	cmp r0, #0x1
	bne _020598D4
	mov r0, #0x2
	orr r4, r0
_020598D4:
	ldr r2, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r3, r7, #0x0
	bl FUN_0205995C
	cmp r0, #0x1
	bne _020598E8
	mov r0, #0x4
	orr r4, r0
_020598E8:
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020598F0
FUN_020598F0: ; 0x020598F0
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r1, #0x0
	add r1, sp, #0x8
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02058B5C
	ldr r0, [sp, #0x28]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, sp, #0x8
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_02059874
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_02059918
FUN_02059918: ; 0x02059918
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B3C
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_02059C00
	str r4, [sp, #0x0]
	add r3, r0, #0x0
	ldr r4, [sp, #0x8]
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r6, r7
	add r3, r4, r3
	bl FUN_020598F0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0205995C
FUN_0205995C: ; 0x0205995C
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02058578
	add r7, r0, #0x0
	bl FUN_020583BC
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	bl FUN_02058368
	str r0, [sp, #0x4]
_0205997C:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x0]
	cmp r0, r1
	beq _020599F4
	mov r1, #0x1
	bl FUN_02058424
	cmp r0, #0x0
	beq _020599F4
	mov r1, #0x1
	ldr r0, [sp, #0x8]
	lsl r1, r1, #0x12
	bl FUN_02058424
	cmp r0, #0x0
	bne _020599F4
	ldr r0, [sp, #0x8]
	bl FUN_02058B2C
	add r7, r0, #0x0
	ldr r0, [sp, #0x8]
	bl FUN_02058B4C
	cmp r7, r5
	bne _020599C8
	cmp r0, r6
	bne _020599C8
	ldr r0, [sp, #0x8]
	bl FUN_02058B3C
	sub r0, r0, r4
	bpl _020599BE
	neg r0, r0
_020599BE:
	cmp r0, #0x2
	bge _020599C8
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_020599C8:
	ldr r0, [sp, #0x8]
	bl FUN_02058B14
	add r7, r0, #0x0
	ldr r0, [sp, #0x8]
	bl FUN_02058B24
	cmp r7, r5
	bne _020599F4
	cmp r0, r6
	bne _020599F4
	ldr r0, [sp, #0x8]
	bl FUN_02058B3C
	sub r0, r0, r4
	bpl _020599EA
	neg r0, r0
_020599EA:
	cmp r0, #0x2
	bge _020599F4
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_020599F4:
	add r0, sp, #0x8
	bl FUN_020583D4
	ldr r0, [sp, #0x4]
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
	bne _0205997C
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02059A08
FUN_02059A08: ; 0x02059A08
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r3, #0x0
	bl FUN_02058AFC
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02058538
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02059A34
	add r1, r7, r0
	sub r0, r7, r0
	cmp r0, r5
	bgt _02059A30
	cmp r1, r5
	bge _02059A34
_02059A30:
	mov r0, #0x1
	pop {r3-r7, pc}
_02059A34:
	add r0, r6, #0x0
	bl FUN_02058B0C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02058540
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02059A5A
	add r1, r5, r0
	sub r0, r5, r0
	cmp r0, r4
	bgt _02059A56
	cmp r1, r4
	bge _02059A5A
_02059A56:
	mov r0, #0x1
	pop {r3-r7, pc}
_02059A5A:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02059A60
FUN_02059A60: ; 0x02059A60
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r5, r3, #0x0
	bl FUN_02058738
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02058720
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_0204A6E0
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	bne _02059A92
	bl ErrorHandling
_02059A92:
	cmp r5, #0x4
	blt _02059A9A
	bl ErrorHandling
_02059A9A:
	ldr r1, _02059ABC ; =0x020F6630
	lsl r5, r5, #0x2
	ldr r1, [r1, r5]
	add r0, r4, #0x0
	blx r1
	cmp r0, #0x1
	beq _02059AB4
	ldr r1, _02059AC0 ; =0x020F6640
	add r0, r6, #0x0
	ldr r1, [r1, r5]
	blx r1
	cmp r0, #0x1
	bne _02059AB8
_02059AB4:
	mov r0, #0x1
	pop {r3-r7, pc}
_02059AB8:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02059ABC: .word 0x020F6630
_02059AC0: .word 0x020F6640

	thumb_func_start FUN_02059AC4
FUN_02059AC4: ; 0x02059AC4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054B8C
	cmp r0, #0x0
	beq _02059AE4
	add r0, r5, #0x0
	bl FUN_02058A68
	cmp r0, #0x0
	bne _02059AF4
	mov r0, #0x1
	pop {r3-r5, pc}
_02059AE4:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_0205481C
	cmp r0, #0x0
	beq _02059AF4
	mov r0, #0x1
	pop {r3-r5, pc}
_02059AF4:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02059AF8
FUN_02059AF8: ; 0x02059AF8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054BB0
	cmp r0, #0x0
	beq _02059B18
	add r0, r5, #0x0
	bl FUN_02058A68
	cmp r0, #0x0
	bne _02059B28
	mov r0, #0x1
	pop {r3-r5, pc}
_02059B18:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054830
	cmp r0, #0x0
	beq _02059B28
	mov r0, #0x1
	pop {r3-r5, pc}
_02059B28:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02059B2C
FUN_02059B2C: ; 0x02059B2C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054BD4
	cmp r0, #0x0
	beq _02059B4C
	add r0, r5, #0x0
	bl FUN_02058A68
	cmp r0, #0x0
	bne _02059B5C
	mov r0, #0x1
	pop {r3-r5, pc}
_02059B4C:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_020549AC
	cmp r0, #0x0
	beq _02059B5C
	mov r0, #0x1
	pop {r3-r5, pc}
_02059B5C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02059B60
FUN_02059B60: ; 0x02059B60
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054BD4
	cmp r0, #0x0
	beq _02059B80
	add r0, r5, #0x0
	bl FUN_02058A68
	cmp r0, #0x0
	bne _02059B90
	mov r0, #0x1
	pop {r3-r5, pc}
_02059B80:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_020549CC
	cmp r0, #0x0
	beq _02059B90
	mov r0, #0x1
	pop {r3-r5, pc}
_02059B90:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02059B94
FUN_02059B94: ; 0x02059B94
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02058A68
	cmp r0, #0x1
	bne _02059BB0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054B78
	cmp r0, #0x1
	bne _02059BB0
	mov r0, #0x1
	pop {r4, pc}
_02059BB0:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02059BB4
FUN_02059BB4: ; 0x02059BB4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02058A68
	cmp r0, #0x1
	bne _02059BD0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054BE0
	cmp r0, #0x1
	bne _02059BD0
	mov r0, #0x1
	pop {r4, pc}
_02059BD0:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02059BD4
FUN_02059BD4: ; 0x02059BD4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02058A68
	cmp r0, #0x1
	bne _02059BF0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	bl FUN_02054BF4
	cmp r0, #0x1
	bne _02059BF0
	mov r0, #0x1
	pop {r4, pc}
_02059BF0:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02059BF4
FUN_02059BF4: ; 0x02059BF4
	lsl r1, r0, #0x2
	ldr r0, _02059BFC ; =0x020F6620
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_02059BFC: .word 0x020F6620

	thumb_func_start FUN_02059C00
FUN_02059C00: ; 0x02059C00
	lsl r1, r0, #0x2
	ldr r0, _02059C08 ; =0x020F6650
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_02059C08: .word 0x020F6650

	thumb_func_start FUN_02059C0C
FUN_02059C0C: ; 0x02059C0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02058B2C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B18
	add r0, r5, #0x0
	bl FUN_02058B3C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B20
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B28
	add r0, r4, #0x0
	bl FUN_02059BF4
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B34
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058B44
	add r0, r4, #0x0
	bl FUN_02059C00
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B54
	pop {r3-r5, pc}

	thumb_func_start FUN_02059C60
FUN_02059C60: ; 0x02059C60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02058B2C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B18
	add r0, r4, #0x0
	bl FUN_02058B3C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B20
	add r0, r4, #0x0
	bl FUN_02058B4C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B28
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02059C90
FUN_02059C90: ; 0x02059C90
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	bl FUN_02058B2C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02059BF4
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B4C
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02059C00
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058738
	ldr r2, [sp, #0x0]
	add r1, r6, r7
	add r2, r2, r5
	bl FUN_0204A6E0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02059CC8
FUN_02059CC8: ; 0x02059CC8
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	add r1, sp, #0x0
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02058B5C
	cmp r5, #0x3
	bhi _02059D0E
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02059CE8: ; jump table (using 16-bit offset)
	.short _02059CF0 - _02059CE8 - 2; case 0
	.short _02059CF8 - _02059CE8 - 2; case 1
	.short _02059D00 - _02059CE8 - 2; case 2
	.short _02059D08 - _02059CE8 - 2; case 3
_02059CF0:
	ldr r0, [sp, #0x8]
	sub r0, r0, r4
	str r0, [sp, #0x8]
	b _02059D0E
_02059CF8:
	ldr r0, [sp, #0x8]
	add r0, r0, r4
	str r0, [sp, #0x8]
	b _02059D0E
_02059D00:
	ldr r0, [sp, #0x0]
	sub r0, r0, r4
	str r0, [sp, #0x0]
	b _02059D0E
_02059D08:
	ldr r0, [sp, #0x0]
	add r0, r0, r4
	str r0, [sp, #0x0]
_02059D0E:
	add r0, r6, #0x0
	add r1, sp, #0x0
	bl FUN_02058B6C
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02059D1C
FUN_02059D1C: ; 0x02059D1C
	push {r3-r5, lr}
	sub sp, #0x18
	add r1, sp, #0xc
	add r5, r0, #0x0
	bl FUN_02058B5C
	add r3, sp, #0xc
	ldmia r3!, {r0-r1}
	add r2, sp, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	add r0, r5, #0x0
	bl FUN_0205897C
	cmp r0, #0x1
	bne _02059D4E
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0xc
	bl FUN_02058418
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r5, pc}
_02059D4E:
	add r0, r5, #0x0
	bl FUN_02058AE4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058738
	add r1, sp, #0x0
	add r2, r4, #0x0
	bl FUN_02059EC8
	add r4, r0, #0x0
	cmp r4, #0x1
	bne _02059DA2
	ldr r0, [sp, #0x4]
	add r1, sp, #0xc
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_02058B6C
	add r0, r5, #0x0
	bl FUN_02058B3C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B20
	ldr r1, [sp, #0x10]
	add r0, r5, #0x0
	asr r2, r1, #0x3
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r1, r1, #0xc
	bl FUN_02058B40
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0xc
	bl FUN_02058418
	b _02059DAC
_02059DA2:
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0xc
	bl FUN_02058410
_02059DAC:
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02059DB4
FUN_02059DB4: ; 0x02059DB4
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02058B14
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B24
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058738
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r7, r0, #0x0
	bl FUN_0204A6E0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058728
	add r0, r5, #0x0
	bl FUN_02058B2C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B4C
	add r2, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_0204A6E0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02058718
	add r0, r4, #0x0
	bl FUN_02054C08
	cmp r0, #0x1
	bne _02059E18
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0xa
	bl FUN_02058410
	mov r0, #0x0
	pop {r3-r7, pc}
_02059E18:
	mov r1, #0x2
	add r0, r5, #0x0
	lsl r1, r1, #0xa
	bl FUN_02058418
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02059E28
FUN_02059E28: ; 0x02059E28
	cmp r0, #0x3
	bhi _02059E5E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02059E38: ; jump table (using 16-bit offset)
	.short _02059E40 - _02059E38 - 2; case 0
	.short _02059E48 - _02059E38 - 2; case 1
	.short _02059E50 - _02059E38 - 2; case 2
	.short _02059E58 - _02059E38 - 2; case 3
_02059E40:
	ldr r0, [r1, #0x8]
	sub r0, r0, r2
	str r0, [r1, #0x8]
	bx lr
_02059E48:
	ldr r0, [r1, #0x8]
	add r0, r0, r2
	str r0, [r1, #0x8]
	bx lr
_02059E50:
	ldr r0, [r1, #0x0]
	sub r0, r0, r2
	str r0, [r1, #0x0]
	bx lr
_02059E58:
	ldr r0, [r1, #0x0]
	add r0, r0, r2
	str r0, [r1, #0x0]
_02059E5E:
	bx lr

	thumb_func_start FUN_02059E60
FUN_02059E60: ; 0x02059E60
	lsl r3, r0, #0x10
	mov r0, #0x2
	lsl r0, r0, #0xe
	add r3, r3, r0
	lsl r1, r1, #0x10
	str r3, [r2, #0x0]
	add r0, r1, r0
	str r0, [r2, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_02059E74
FUN_02059E74: ; 0x02059E74
	lsl r1, r0, #0x2
	ldr r0, _02059E7C ; =0x020F6660
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_02059E7C: .word 0x020F6660

	thumb_func_start FUN_02059E80
FUN_02059E80: ; 0x02059E80
	cmp r0, r2
	ble _02059E88
	mov r0, #0x2
	bx lr
_02059E88:
	cmp r0, r2
	bge _02059E90
	mov r0, #0x3
	bx lr
_02059E90:
	cmp r1, r3
	bgt _02059E98
	mov r0, #0x1
	bx lr
_02059E98:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02059E9C
FUN_02059E9C: ; 0x02059E9C
	push {r4, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r1, sp, #0x4
	str r1, [sp, #0x0]
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x8]
	bl FUN_0204A708
	add r1, sp, #0x4
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02059EBE
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_02059EBE:
	str r0, [r4, #0x4]
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02059EC8
FUN_02059EC8: ; 0x02059EC8
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	add r1, sp, #0x4
	str r1, [sp, #0x0]
	add r4, r2, #0x0
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x0]
	ldr r3, [r5, #0x8]
	bl FUN_0204A708
	add r1, sp, #0x4
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02059EEC
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_02059EEC:
	cmp r1, #0x2
	bne _02059EFA
	cmp r4, #0x0
	bne _02059EFA
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_02059EFA:
	str r0, [r5, #0x4]
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
