    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204653C
FUN_0204653C: ; 0x0204653C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02046562
	cmp r0, #0x1
	beq _02046572
	b _02046580
_02046562:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0203780C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046580
_02046572:
	add r0, r5, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _02046580
	mov r0, #0x1
	pop {r4-r6, pc}
_02046580:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02046584
FUN_02046584: ; 0x02046584
	ldr r3, _0204658C ; =FUN_0204640C
	add r2, r1, #0x0
	ldr r1, _02046590 ; =FUN_0204653C
	bx r3
	.balign 4
_0204658C: .word FUN_0204640C
_02046590: .word FUN_0204653C

	thumb_func_start FUN_02046594
FUN_02046594: ; 0x02046594
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x14
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl AllocFromHeapAtEnd
	str r4, [r0, #0x0]
	cmp r4, #0x0
	beq _020465B0
	mov r1, #0x0
	str r1, [r4, #0x0]
_020465B0:
	str r6, [r0, #0x4]
	str r7, [r0, #0x8]
	str r5, [r0, #0x10]
	pop {r3-r7, pc}

	thumb_func_start FUN_020465B8
FUN_020465B8: ; 0x020465B8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	bl FUN_02047964
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020465CC
FUN_020465CC: ; 0x020465CC
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020465D8
	ldr r1, [r0, #0x10]
	ldr r1, [r1, #0x14]
	str r1, [r2, #0x0]
_020465D8:
	ldr r0, [r0, #0x10]
	ldr r3, _020465E0 ; =FUN_020480B8
	ldr r0, [r0, #0x14]
	bx r3
	.balign 4
_020465E0: .word FUN_020480B8

	thumb_func_start FUN_020465E4
FUN_020465E4: ; 0x020465E4
	push {r3, lr}
	mov r2, #0x2
	ldr r3, [r0, #0x0]
	lsl r2, r2, #0x1e
	tst r2, r3
	bne _020465F4
	bl FUN_02047F38
_020465F4:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020465F8
FUN_020465F8: ; 0x020465F8
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x5
	bhi _020466F8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02046624: ; jump table (using 16-bit offset)
	.short _02046630 - _02046624 - 2; case 0
	.short _02046648 - _02046624 - 2; case 1
	.short _02046656 - _02046624 - 2; case 2
	.short _02046666 - _02046624 - 2; case 3
	.short _020466DA - _02046624 - 2; case 4
	.short _020466EE - _02046624 - 2; case 5
_02046630:
	ldr r0, [r6, #0x34]
	bl FUN_02058780
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r7, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020466F8
_02046648:
	add r0, r7, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020466F8
_02046656:
	ldr r1, [r5, #0x10]
	add r0, r7, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020466F8
_02046666:
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	bl FUN_020465E4
	ldr r2, [r5, #0x10]
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02046682
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	beq _02046682
	cmp r1, #0x4a
	bne _02046690
_02046682:
	mov r1, #0x4d
	lsl r1, r1, #0x2
	ldr r1, [r2, r1]
	ldr r2, [r2, #0x14]
	add r0, r6, #0x0
	bl FUN_02061080
_02046690:
	add r0, r5, #0x0
	bl FUN_020465CC
	cmp r0, #0x0
	bne _020466A4
	add r0, r5, #0x0
	bl FUN_020465B8
	mov r0, #0x1
	pop {r3-r7, pc}
_020466A4:
	ldr r0, [r6, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	cmp r0, #0x0
	beq _020466BC
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	bl FUN_02085140
_020466BC:
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_020472F4
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_020473CC
	add r0, r7, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020466F8
_020466DA:
	ldr r0, [r6, #0x34]
	bl FUN_020587B0
	add r0, r7, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020466F8
_020466EE:
	add r0, r5, #0x0
	bl FUN_020465B8
	mov r0, #0x1
	pop {r3-r7, pc}
_020466F8:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020466FC
FUN_020466FC: ; 0x020466FC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r3, [sp, #0x8]
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _02046718 ; =FUN_020465F8
	add r0, r4, #0x0
	bl FUN_0204640C
	pop {r4, pc}
	.balign 4
_02046718: .word FUN_020465F8

	thumb_func_start FUN_0204671C
FUN_0204671C: ; 0x0204671C
	push {r3, lr}
	mov r2, #0xf
	and r0, r2
	cmp r0, #0x6
	bhi _02046754
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02046732: ; jump table (using 16-bit offset)
	.short _02046754 - _02046732 - 2; case 0
	.short _02046740 - _02046732 - 2; case 1
	.short _0204674A - _02046732 - 2; case 2
	.short _02046754 - _02046732 - 2; case 3
	.short _02046754 - _02046732 - 2; case 4
	.short _0204674A - _02046732 - 2; case 5
	.short _02046740 - _02046732 - 2; case 6
_02046740:
	ldr r0, [r1, #0xc]
	mov r1, #0x1
	bl FUN_0202E25C
	pop {r3, pc}
_0204674A:
	ldr r0, [r1, #0xc]
	sub r2, #0x10
	add r1, r2, #0x0
	bl FUN_0202E25C
_02046754:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02046758
FUN_02046758: ; 0x02046758
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x5
	bhi _020467F6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02046784: ; jump table (using 16-bit offset)
	.short _02046790 - _02046784 - 2; case 0
	.short _020467A2 - _02046784 - 2; case 1
	.short _020467B0 - _02046784 - 2; case 2
	.short _020467C0 - _02046784 - 2; case 3
	.short _020467EC - _02046784 - 2; case 4
	.short _020467EC - _02046784 - 2; case 5
_02046790:
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r6, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020467F6
_020467A2:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020467F6
_020467B0:
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020467F6
_020467C0:
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	ldr r0, [r0, #0x14]
	bl FUN_0204671C
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	bl FUN_02047FA4
	ldr r0, [r7, #0xc]
	bl FUN_02029FC8
	mov r1, #0x15
	bl FUN_0202A170
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020467F6
_020467EC:
	add r0, r5, #0x0
	bl FUN_020465B8
	mov r0, #0x1
	pop {r3-r7, pc}
_020467F6:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020467FC
FUN_020467FC: ; 0x020467FC
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02046826
	cmp r0, #0x1
	beq _02046844
	cmp r0, #0x2
	beq _0204686A
	b _02046874
_02046826:
	ldr r1, [r5, #0x8]
	mov r0, #0x5
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x1
	bl FUN_0200433C
	ldr r1, [r5, #0x10]
	add r0, r7, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046874
_02046844:
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	ldr r0, [r0, #0x14]
	bl FUN_0204671C
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	bl FUN_02047FA4
	ldr r0, [r6, #0xc]
	bl FUN_02029FC8
	mov r1, #0x15
	bl FUN_0202A170
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046874
_0204686A:
	add r0, r5, #0x0
	bl FUN_020465B8
	mov r0, #0x1
	pop {r3-r7, pc}
_02046874:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02046878
FUN_02046878: ; 0x02046878
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x5
	bhi _02046922
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020468A4: ; jump table (using 16-bit offset)
	.short _020468B0 - _020468A4 - 2; case 0
	.short _020468C2 - _020468A4 - 2; case 1
	.short _020468D0 - _020468A4 - 2; case 2
	.short _020468E0 - _020468A4 - 2; case 3
	.short _0204690A - _020468A4 - 2; case 4
	.short _02046918 - _020468A4 - 2; case 5
_020468B0:
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r6, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046922
_020468C2:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046922
_020468D0:
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046922
_020468E0:
	ldr r0, [r5, #0x10]
	add r1, r7, #0x0
	bl FUN_02047FA4
	mov r1, #0x4e
	ldr r2, [r5, #0x10]
	lsl r1, r1, #0x2
	add r0, r7, #0x0
	add r1, r2, r1
	bl FUN_02060044
	add r0, r5, #0x0
	bl FUN_020465CC
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046922
_0204690A:
	add r0, r6, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046922
_02046918:
	add r0, r5, #0x0
	bl FUN_020465B8
	mov r0, #0x1
	pop {r3-r7, pc}
_02046922:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02046928
FUN_02046928: ; 0x02046928
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r3, [sp, #0x8]
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _02046944 ; =FUN_02046878
	add r0, r4, #0x0
	bl FUN_0204640C
	pop {r4, pc}
	.balign 4
_02046944: .word FUN_02046878

	thumb_func_start FUN_02046948
FUN_02046948: ; 0x02046948
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r7, r0, #0x0
	add r5, r2, #0x0
	bl FUN_02046528
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl MOD06_02244558
	add r4, r0, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	str r5, [sp, #0x0]
	bl FUN_02046928
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0204697C
FUN_0204697C: ; 0x0204697C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x14
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl AllocFromHeapAtEnd
	str r4, [r0, #0xc]
	cmp r4, #0x0
	beq _02046998
	mov r1, #0x0
	str r1, [r4, #0x0]
_02046998:
	str r6, [r0, #0x4]
	str r7, [r0, #0x8]
	str r5, [r0, #0x10]
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_020469A4
FUN_020469A4: ; 0x020469A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	bl FUN_02047964
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020469B8
FUN_020469B8: ; 0x020469B8
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_020462AC
	bl FUN_0205F214
	cmp r0, #0x0
	beq _020469F2
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _02046A18 ; =FUN_02046C1C
	add r0, r5, #0x0
	bl FUN_020463CC
	pop {r4-r6, pc}
_020469F2:
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0204697C
	add r2, r0, #0x0
	ldr r1, _02046A1C ; =FUN_02046A88
	add r0, r5, #0x0
	bl FUN_020463CC
	pop {r4-r6, pc}
	.balign 4
_02046A18: .word FUN_02046C1C
_02046A1C: .word FUN_02046A88

	thumb_func_start FUN_02046A20
FUN_02046A20: ; 0x02046A20
	push {r4-r6, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020462AC
	bl FUN_0205F214
	cmp r0, #0x0
	beq _02046A5A
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _02046A80 ; =FUN_02046C1C
	add r0, r5, #0x0
	bl FUN_020463EC
	pop {r4-r6, pc}
_02046A5A:
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_0204697C
	add r2, r0, #0x0
	ldr r1, _02046A84 ; =FUN_02046A88
	add r0, r5, #0x0
	bl FUN_020463EC
	pop {r4-r6, pc}
	.balign 4
_02046A80: .word FUN_02046C1C
_02046A84: .word FUN_02046A88

	thumb_func_start FUN_02046A88
FUN_02046A88: ; 0x02046A88
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x6
	bls _02046AA2
	b _02046C12
_02046AA2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02046AAE: ; jump table (using 16-bit offset)
	.short _02046ABC - _02046AAE - 2; case 0
	.short _02046AE0 - _02046AAE - 2; case 1
	.short _02046AEE - _02046AAE - 2; case 2
	.short _02046AFE - _02046AAE - 2; case 3
	.short _02046BAE - _02046AAE - 2; case 4
	.short _02046BC4 - _02046AAE - 2; case 5
	.short _02046BF4 - _02046AAE - 2; case 6
_02046ABC:
	ldr r0, [r5, #0x34]
	bl FUN_02058780
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	mov r1, #0x7
	bl FUN_0202A0E8
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r6, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046C12
_02046AE0:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046C12
_02046AEE:
	ldr r1, [r4, #0x10]
	add r0, r6, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046C12
_02046AFE:
	ldr r0, [r4, #0x10]
	add r1, r5, #0x0
	bl FUN_020465E4
	mov r1, #0x4d
	ldr r2, [r4, #0x10]
	lsl r1, r1, #0x2
	ldr r1, [r2, r1]
	ldr r2, [r2, #0x14]
	add r0, r5, #0x0
	bl FUN_02061080
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x14]
	bl FUN_020480B8
	cmp r0, #0x0
	bne _02046B3E
	add r0, r4, #0x0
	bl FUN_020469A4
	add r5, #0x90
	ldr r0, [r5, #0x0]
	bl FUN_0205DD40
	ldr r1, _02046C18 ; =FUN_0204837C
	add r0, r6, #0x0
	mov r2, #0x0
	bl FUN_020463EC
	mov r0, #0x0
	pop {r4-r6, pc}
_02046B3E:
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	cmp r0, #0x0
	beq _02046B56
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	bl FUN_02085140
_02046B56:
	ldr r1, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_020472F4
	ldr r1, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_020473CC
	add r0, r5, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205E128
	cmp r0, #0x0
	beq _02046BA0
	add r0, r5, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205E0A4
	cmp r0, #0x0
	beq _02046B98
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x14]
	cmp r0, #0x1
	beq _02046BA0
	cmp r0, #0x4
	beq _02046BA0
	add r5, #0x90
	ldr r0, [r5, #0x0]
	bl FUN_0205DD40
	b _02046BA0
_02046B98:
	add r5, #0x90
	ldr r0, [r5, #0x0]
	bl FUN_0205DD40
_02046BA0:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046C12
_02046BAE:
	ldr r1, [r4, #0x10]
	add r0, r5, #0x0
	bl MOD06_02248724
	add r0, r6, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046C12
_02046BC4:
	add r0, r5, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205E128
	cmp r0, #0x0
	beq _02046BEC
	ldr r1, [r4, #0x10]
	add r2, r5, #0x0
	add r2, #0x90
	ldr r1, [r1, #0x14]
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	bl FUN_0205DED4
	add r0, r5, #0x0
	add r5, #0x90
	ldr r1, [r5, #0x0]
	bl FUN_0205DF44
_02046BEC:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046C12
_02046BF4:
	add r0, r5, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DF9C
	cmp r0, #0x0
	beq _02046C12
	ldr r0, [r5, #0x34]
	bl FUN_020587B0
	add r0, r4, #0x0
	bl FUN_020469A4
	mov r0, #0x1
	pop {r4-r6, pc}
_02046C12:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02046C18: .word FUN_0204837C

	thumb_func_start FUN_02046C1C
FUN_02046C1C: ; 0x02046C1C
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_02034E30
	bl FUN_02034E24
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	cmp r0, #0x7
	bls _02046C4C
	b _02046DA0
_02046C4C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02046C58: ; jump table (using 16-bit offset)
	.short _02046C68 - _02046C58 - 2; case 0
	.short _02046C8C - _02046C58 - 2; case 1
	.short _02046C9A - _02046C58 - 2; case 2
	.short _02046CAA - _02046C58 - 2; case 3
	.short _02046D0E - _02046C58 - 2; case 4
	.short _02046D1C - _02046C58 - 2; case 5
	.short _02046D30 - _02046C58 - 2; case 6
	.short _02046D94 - _02046C58 - 2; case 7
_02046C68:
	ldr r0, [r6, #0x34]
	bl FUN_02058780
	ldr r0, [r6, #0xc]
	bl FUN_02029FC8
	mov r1, #0x7
	bl FUN_0202A0E8
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r7, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046C8C:
	add r0, r7, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046C9A:
	ldr r1, [r5, #0x10]
	add r0, r7, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046CAA:
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	bl FUN_020465E4
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #0x14]
	cmp r0, #0x4
	bne _02046CD4
	ldr r0, [r6, #0xc]
	bl FUN_02022504
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x10]
	mov r1, #0x0
	ldr r0, [r0, #0x8]
	bl FUN_0206B9B0
	add r1, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02060FE0
_02046CD4:
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_020472F4
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02046CFE
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #0x14]
	cmp r0, #0x4
	beq _02046CFE
	ldr r0, [r6, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02049160
_02046CFE:
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_020473CC
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046D0E:
	add r0, r7, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046D1C:
	ldr r0, [r6, #0x34]
	bl FUN_020587B0
	add r0, r7, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046D30:
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02046D5C
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #0x14]
	cmp r0, #0x4
	bne _02046D4E
	mov r2, #0x0
	ldr r1, _02046DA8 ; =0x00002262
	add r0, r7, #0x0
	add r3, r2, #0x0
	bl FUN_02038CD8
	b _02046D8C
_02046D4E:
	mov r2, #0x0
	ldr r1, _02046DAC ; =0x00002269
	add r0, r7, #0x0
	add r3, r2, #0x0
	bl FUN_02038CD8
	b _02046D8C
_02046D5C:
	ldr r0, [r6, #0xc]
	bl FUN_02022510
	str r0, [sp, #0x8]
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	add r5, r0, #0x0
	ldr r0, [sp, #0x8]
	bl FUN_0206B334
	cmp r0, #0x12
	bne _02046D8C
	add r0, r5, #0x0
	bl FUN_0206B9AC
	cmp r0, #0x6
	bne _02046D8C
	mov r2, #0x0
	ldr r1, _02046DB0 ; =0x00002276
	add r0, r7, #0x0
	add r3, r2, #0x0
	bl FUN_02038CD8
_02046D8C:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046DA0
_02046D94:
	add r0, r5, #0x0
	bl FUN_020465B8
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02046DA0:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02046DA8: .word 0x00002262
_02046DAC: .word 0x00002269
_02046DB0: .word 0x00002276

	thumb_func_start FUN_02046DB4
FUN_02046DB4: ; 0x02046DB4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	mov r0, #0xb
	mov r1, #0x0
	bl FUN_020476CC
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_02047BB0
	mov r0, #0x15
	mov r1, #0x0
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	add r0, r0, #0x4
	str r1, [r4, r0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MOD06_0223CCDC
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	mov r1, #0x7
	bl FUN_0202A0E8
	add r0, r4, #0x0
	bl FUN_020475A0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	str r6, [sp, #0x0]
	bl FUN_020466FC
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02046E18
FUN_02046E18: ; 0x02046E18
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x4]
	add r7, r1, #0x0
	str r2, [sp, #0x8]
	add r6, r3, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	mov r0, #0xb
	mov r1, #0x0
	bl FUN_020476CC
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_02047BB0
	ldr r2, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r3, r4, #0x0
	bl MOD06_0223CD7C
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	beq _02046E60
	mov r1, #0x63
	lsl r1, r1, #0x2
	ldr r2, [r4, r1]
	mov r0, #0x8
	orr r0, r2
	str r0, [r4, r1]
_02046E60:
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	mov r1, #0x7
	bl FUN_0202A0E8
	add r0, r4, #0x0
	bl FUN_020475A0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r3, r0, #0x0
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	add r2, r5, #0x0
	str r6, [sp, #0x0]
	bl FUN_020466FC
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02046E8C
FUN_02046E8C: ; 0x02046E8C
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x6
	bhi _02046F6C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02046EB8: ; jump table (using 16-bit offset)
	.short _02046EC6 - _02046EB8 - 2; case 0
	.short _02046EEA - _02046EB8 - 2; case 1
	.short _02046EF8 - _02046EB8 - 2; case 2
	.short _02046F08 - _02046EB8 - 2; case 3
	.short _02046F28 - _02046EB8 - 2; case 4
	.short _02046F36 - _02046EB8 - 2; case 5
	.short _02046F4A - _02046EB8 - 2; case 6
_02046EC6:
	ldr r0, [r6, #0x34]
	bl FUN_02058780
	ldr r0, [r6, #0xc]
	bl FUN_02029FC8
	mov r1, #0x7
	bl FUN_0202A0E8
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r0, r7, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046F6C
_02046EEA:
	add r0, r7, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046F6C
_02046EF8:
	ldr r1, [r5, #0x10]
	add r0, r7, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046F6C
_02046F08:
	ldr r0, [r5, #0x10]
	add r1, r6, #0x0
	bl FUN_020465E4
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_0204BAA0
	ldr r1, [r5, #0x10]
	add r0, r6, #0x0
	bl FUN_020472F4
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046F6C
_02046F28:
	add r0, r7, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046F6C
_02046F36:
	ldr r0, [r6, #0x34]
	bl FUN_020587B0
	add r0, r7, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02046F6C
_02046F4A:
	add r0, r5, #0x0
	bl FUN_020465B8
	add r0, r6, #0x0
	bl FUN_0204BAB0
	cmp r0, #0x0
	bne _02046F68
	add r0, r7, #0x0
	mov r1, #0x3
	mov r2, #0x0
	bl FUN_02038D10
	mov r0, #0x0
	pop {r3-r7, pc}
_02046F68:
	mov r0, #0x1
	pop {r3-r7, pc}
_02046F6C:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02046F70
FUN_02046F70: ; 0x02046F70
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _02046F9C ; =FUN_02046E8C
	add r0, r5, #0x0
	bl FUN_020463CC
	pop {r4-r6, pc}
	.balign 4
_02046F9C: .word FUN_02046E8C

	thumb_func_start FUN_02046FA0
FUN_02046FA0: ; 0x02046FA0
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x4]
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x0
	bl FUN_020476CC
	add r4, r0, #0x0
	add r1, r5, #0x0
	bl FUN_02047BB0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl MOD06_0223CD7C
	mov r0, #0x63
	mov r1, #0x1
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	mov r1, #0x7
	bl FUN_0202A0E8
	add r0, r4, #0x0
	bl FUN_020475A0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r3, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_020466FC
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02047004
FUN_02047004: ; 0x02047004
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x6
	bhi _020470A6
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02047030: ; jump table (using 16-bit offset)
	.short _0204703E - _02047030 - 2; case 0
	.short _02047056 - _02047030 - 2; case 1
	.short _02047064 - _02047030 - 2; case 2
	.short _02047074 - _02047030 - 2; case 3
	.short _0204707A - _02047030 - 2; case 4
	.short _02047088 - _02047030 - 2; case 5
	.short _0204709C - _02047030 - 2; case 6
_0204703E:
	ldr r0, [r7, #0x34]
	bl FUN_02058780
	ldr r1, [r6, #0x4]
	ldr r2, [r6, #0x8]
	add r0, r5, #0x0
	bl FUN_0204AEF8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020470A6
_02047056:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020470A6
_02047064:
	ldr r1, [r6, #0x10]
	add r0, r5, #0x0
	bl FUN_02046584
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020470A6
_02047074:
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020470A6
_0204707A:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020470A6
_02047088:
	ldr r0, [r7, #0x34]
	bl FUN_020587B0
	add r0, r5, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020470A6
_0204709C:
	add r0, r6, #0x0
	bl FUN_020465B8
	mov r0, #0x1
	pop {r3-r7, pc}
_020470A6:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020470AC
FUN_020470AC: ; 0x020470AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r1, r0, #0x0
	mov r0, #0xb
	bl FUN_02047814
	add r4, r0, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _020470E4 ; =FUN_02047004
	add r0, r5, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
	nop
_020470E4: .word FUN_02047004

	thumb_func_start FUN_020470E8
FUN_020470E8: ; 0x020470E8
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x4]
	add r6, r1, #0x0
	add r5, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_02046528
	add r7, r0, #0x0
	cmp r5, #0x0
	beq _02047110
	cmp r6, r5
	beq _02047110
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0204710C
	mov r4, #0x13
	b _0204711A
_0204710C:
	mov r4, #0x4b
	b _0204711A
_02047110:
	cmp r6, r5
	bne _02047118
	mov r4, #0x3
	b _0204711A
_02047118:
	mov r4, #0x1
_0204711A:
	add r0, r7, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	mov r0, #0xb
	add r1, r4, #0x0
	bl FUN_020476CC
	add r4, r0, #0x0
	add r1, r7, #0x0
	bl FUN_02047BB0
	str r6, [r4, #0x1c]
	ldr r0, [sp, #0x8]
	str r5, [r4, #0x24]
	str r0, [r4, #0x20]
	ldr r1, [r7, #0xc]
	ldr r2, [sp, #0x20]
	add r0, r4, #0x0
	bl FUN_0206ABC4
	ldr r0, [r7, #0xc]
	bl FUN_02029FC8
	mov r1, #0x8
	bl FUN_0202A0E8
	add r0, r4, #0x0
	bl FUN_020475A0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r3, r0, #0x0
	ldr r0, [sp, #0x24]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r2, r5, #0x0
	bl FUN_020466FC
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02047174
FUN_02047174: ; 0x02047174
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r7, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	mov r0, #0xb
	add r1, r5, #0x0
	bl FUN_020476CC
	add r5, r0, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02047F1C
	add r0, r5, #0x0
	bl FUN_020475A0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _020471BC ; =FUN_02046758
	add r0, r7, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	nop
_020471BC: .word FUN_02046758

	thumb_func_start FUN_020471C0
FUN_020471C0: ; 0x020471C0
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	cmp r4, #0x0
	beq _020471DE
	mov r0, #0xb
	mov r1, #0x5
	bl FUN_020476CC
	b _020471E6
_020471DE:
	mov r0, #0xb
	mov r1, #0x7
	bl FUN_020476CC
_020471E6:
	add r4, r0, #0x0
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02047BC0
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r1, _0204721C ; =FUN_020467FC
	str r5, [r2, #0xc]
	bl FUN_0204640C
	pop {r3-r7, pc}
	nop
_0204721C: .word FUN_020467FC

	thumb_func_start FUN_02047220
FUN_02047220: ; 0x02047220
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02047246
	cmp r0, #0x1
	beq _02047258
	b _02047262
_02047246:
	ldr r1, _02047268 ; =FUN_02046758
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl FUN_0204640C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02047262
_02047258:
	add r0, r6, #0x0
	bl FUN_0204FF5C
	mov r0, #0x1
	pop {r3-r7, pc}
_02047262:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02047268: .word FUN_02046758

	thumb_func_start FUN_0204726C
FUN_0204726C: ; 0x0204726C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	add r1, r2, #0x0
	bl FUN_020476CC
	add r4, r0, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02047F1C
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _020472AC ; =FUN_02047220
	add r0, r5, #0x0
	bl FUN_020463CC
	pop {r4-r6, pc}
	nop
_020472AC: .word FUN_02047220

	thumb_func_start FUN_020472B0
FUN_020472B0: ; 0x020472B0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	add r1, r2, #0x0
	bl FUN_020476CC
	add r4, r0, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	bl FUN_02047D48
	add r0, r4, #0x0
	bl FUN_020475A0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020475B0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x0
	bl FUN_02046594
	add r2, r0, #0x0
	ldr r1, _020472F0 ; =FUN_02047220
	add r0, r5, #0x0
	bl FUN_020463CC
	pop {r4-r6, pc}
	.balign 4
_020472F0: .word FUN_02047220

	thumb_func_start FUN_020472F4
FUN_020472F4: ; 0x020472F4
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, [r1, #0x0]
	mov r3, #0x4
	ldr r2, [r1, #0x14]
	tst r3, r0
	bne _020473C8
	mov r3, #0x80
	add r5, r0, #0x0
	tst r5, r3
	bne _020473C8
	cmp r0, #0x0
	beq _02047318
	add r3, #0x80
	cmp r0, r3
	beq _02047318
	cmp r0, #0x4a
	bne _02047364
_02047318:
	cmp r2, #0x1
	bne _0204732A
	ldr r0, [r4, #0xc]
	bl FUN_02029FC8
	mov r1, #0x8
	bl FUN_0202A170
	pop {r3-r5, pc}
_0204732A:
	cmp r2, #0x4
	bne _020473C8
	ldr r0, [r1, #0x8]
	mov r1, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x0
	mov r0, #0x0
	bl FUN_0206BB48
	cmp r0, #0x0
	ldr r0, [r4, #0xc]
	beq _02047358
	bl FUN_02029FC8
	mov r1, #0x9
	bl FUN_0202A170
	pop {r3-r5, pc}
_02047358:
	bl FUN_02029FC8
	mov r1, #0xa
	bl FUN_0202A170
	pop {r3-r5, pc}
_02047364:
	mov r3, #0x1
	tst r3, r0
	bne _02047370
	mov r3, #0x10
	tst r3, r0
	beq _02047382
_02047370:
	cmp r2, #0x1
	bne _020473C8
	ldr r0, [r4, #0xc]
	bl FUN_02029FC8
	mov r1, #0xb
	bl FUN_0202A170
	pop {r3-r5, pc}
_02047382:
	mov r3, #0x20
	add r5, r0, #0x0
	tst r5, r3
	bne _02047390
	lsl r3, r3, #0x4
	tst r0, r3
	beq _020473C8
_02047390:
	cmp r2, #0x4
	bne _020473C8
	ldr r0, [r1, #0x8]
	mov r1, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x0
	mov r0, #0x0
	bl FUN_0206BB48
	cmp r0, #0x0
	ldr r0, [r4, #0xc]
	beq _020473BE
	bl FUN_02029FC8
	mov r1, #0x9
	bl FUN_0202A170
	pop {r3-r5, pc}
_020473BE:
	bl FUN_02029FC8
	mov r1, #0xa
	bl FUN_0202A170
_020473C8:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020473CC
FUN_020473CC: ; 0x020473CC
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x4
	ldr r1, [r4, #0x14]
	tst r2, r0
	bne _020473EC
	mov r3, #0x80
	add r2, r0, #0x0
	tst r2, r3
	bne _020473EC
	lsl r2, r3, #0x2
	tst r2, r0
	beq _020473EE
_020473EC:
	b _020474FC
_020473EE:
	cmp r0, #0x0
	beq _02047400
	add r3, #0x80
	cmp r0, r3
	beq _02047400
	cmp r0, #0x4a
	beq _02047400
	cmp r0, #0x20
	bne _020474D2
_02047400:
	cmp r1, #0x1
	bne _02047470
	add r0, r5, #0x0
	add r0, #0x76
	ldrh r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r5, #0x0
	add r0, #0x76
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x76
	ldrh r0, [r0, #0x0]
	cmp r0, #0x5
	blo _020474FC
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl FUN_0206B9B0
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02023918
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r3, #0xb
	str r3, [sp, #0x0]
	lsl r3, r3, #0x5
	ldr r3, [r4, r3]
	lsl r1, r7, #0x10
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x4]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0202920C
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x2
	bl FUN_02028AD4
	add sp, #0xc
	pop {r4-r7, pc}
_02047470:
	cmp r1, #0x4
	bne _020474FC
	mov r0, #0x17
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x4]
	bl FUN_0206B9B0
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02023918
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r3, #0xb
	str r3, [sp, #0x0]
	lsl r3, r3, #0x5
	ldr r3, [r4, r3]
	lsl r1, r7, #0x10
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x8]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0202918C
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x2
	bl FUN_02028AD4
	add sp, #0xc
	pop {r4-r7, pc}
_020474D2:
	mov r2, #0x1
	tst r2, r0
	bne _020474DE
	mov r2, #0x10
	tst r0, r2
	beq _020474FC
_020474DE:
	cmp r1, #0x1
	bne _020474FC
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	ldr r2, [r4, #0x1c]
	add r0, #0x98
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #0xb
	bl FUN_020299DC
_020474FC:
	add sp, #0xc
	pop {r4-r7, pc}
