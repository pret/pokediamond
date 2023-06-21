	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_020643C0
sub_020643C0: ; 0x020643C0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl sub_020645DC
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_0206460C
	str r0, [r4, #0xc]
	str r6, [r4, #0x0]
	str r5, [r4, #0x8]
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_020643E0
sub_020643E0: ; 0x020643E0
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02064630
	add r0, r4, #0x0
	bl sub_02064600
	pop {r4, pc}

	thumb_func_start sub_020643F0
sub_020643F0: ; 0x020643F0
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02064558
	add r0, r4, #0x0
	bl sub_020643E0
	pop {r4, pc}

	thumb_func_start sub_02064400
sub_02064400: ; 0x02064400
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r4, #0x0
	bl sub_02064698
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl sub_0206469C
	add r5, r0, #0x0
_0206441C:
	add r0, r5, #0x0
	bl sub_020646A0
	cmp r0, #0x0
	beq _0206442E
	add r4, r4, #0x1
	add r5, #0xc8
	cmp r4, r6
	blt _0206441C
_0206442E:
	cmp r4, r6
	blt _02064438
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02064438:
	add r0, r5, #0x0
	bl sub_020646AC
	ldr r1, [sp, #0x8]
	add r0, r5, #0x0
	bl sub_02064750
	ldr r1, [sp, #0x20]
	add r0, r5, #0x0
	bl sub_02064758
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl sub_02064768
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl sub_0206476C
	ldr r1, [r7, #0x0]
	add r0, r5, #0x0
	bl sub_0206473C
	ldr r1, [r7, #0x4]
	add r0, r5, #0x0
	bl sub_020646B8
	ldr r1, [r7, #0x8]
	add r0, r5, #0x0
	bl sub_0206470C
	ldr r1, [r7, #0xc]
	add r0, r5, #0x0
	bl sub_020646D4
	ldr r1, [r7, #0x10]
	add r0, r5, #0x0
	bl sub_020646F0
	ldr r1, [r7, #0x14]
	add r0, r5, #0x0
	bl sub_02064728
	ldr r1, [r7, #0x18]
	add r0, r5, #0x0
	bl sub_02064730
	ldr r1, [sp, #0x24]
	add r0, r5, #0x0
	bl sub_020645B0
	add r4, r0, #0x0
	bne _020644AE
	add r0, r5, #0x0
	bl sub_02064640
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_020644AE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02064760
	add r0, r5, #0x0
	bl sub_020646C0
	cmp r0, #0x0
	bne _020644D2
	add r0, r4, #0x0
	bl sub_0200CAB4
	add r0, r5, #0x0
	bl sub_02064640
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_020644D2:
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x4]
	add r1, r0, #0x1
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x4]
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start sub_020644E4
sub_020644E4: ; 0x020644E4
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, sp, #0x8
	ldmia r5!, {r0-r1}
	add r7, r4, #0x0
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	str r0, [r4, #0x0]
	ldr r0, _02064518 ; =sub_0206479C
	str r0, [sp, #0x1c]
	ldr r0, _0206451C ; =sub_020647A0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x38]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x3c]
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	bl sub_02064400
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02064518: .word sub_0206479C
_0206451C: .word sub_020647A0

	thumb_func_start sub_02064520
sub_02064520: ; 0x02064520
	push {r4, lr}
	add r4, r0, #0x0
	bne _0206452A
	bl GF_AssertFail
_0206452A:
	add r0, r4, #0x0
	bl sub_020646A0
	cmp r0, #0x0
	beq _02064556
	add r0, r4, #0x0
	bl sub_02064714
	ldr r1, [r4, #0x14]
	ldr r0, [r1, #0x4]
	sub r0, r0, #0x1
	str r0, [r1, #0x4]
	add r0, r4, #0x0
	bl sub_02064764
	cmp r0, #0x0
	beq _02064550
	bl sub_0200CAB4
_02064550:
	add r0, r4, #0x0
	bl sub_02064640
_02064556:
	pop {r4, pc}

	thumb_func_start sub_02064558
sub_02064558: ; 0x02064558
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_02064698
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0206469C
	add r5, r0, #0x0
_0206456A:
	add r0, r5, #0x0
	bl sub_020646A0
	cmp r0, #0x1
	bne _0206457A
	add r0, r5, #0x0
	bl sub_02064520
_0206457A:
	add r5, #0xc8
	sub r4, r4, #0x1
	bne _0206456A
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02064584
sub_02064584: ; 0x02064584
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_02064698
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0206469C
	add r5, r0, #0x0
_02064596:
	add r0, r5, #0x0
	bl sub_020646A0
	cmp r0, #0x1
	bne _020645A6
	add r0, r5, #0x0
	bl sub_020646F8
_020645A6:
	add r5, #0xc8
	sub r4, r4, #0x1
	bne _02064596
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020645B0
sub_020645B0: ; 0x020645B0
	push {r4, lr}
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, _020645CC ; =sub_020645D0
	add r1, r3, #0x0
	bl sub_0200CA44
	add r4, r0, #0x0
	bne _020645C6
	bl GF_AssertFail
_020645C6:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_020645CC: .word sub_020645D0

	thumb_func_start sub_020645D0
sub_020645D0: ; 0x020645D0
	ldr r3, _020645D8 ; =sub_020646DC
	add r0, r1, #0x0
	bx r3
	nop
_020645D8: .word sub_020646DC

	thumb_func_start sub_020645DC
sub_020645DC: ; 0x020645DC
	push {r4, lr}
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _020645EC
	bl GF_AssertFail
_020645EC:
	add r2, r4, #0x0
	mov r1, #0x10
	mov r0, #0x0
_020645F2:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _020645F2
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02064600
sub_02064600: ; 0x02064600
	ldr r3, _02064608 ; =FreeToHeapExplicit
	add r1, r0, #0x0
	ldr r0, [r1, #0x8]
	bx r3
	.balign 4
_02064608: .word FreeToHeapExplicit

	thumb_func_start sub_0206460C
sub_0206460C: ; 0x0206460C
	push {r3-r5, lr}
	mov r2, #0xc8
	add r5, r1, #0x0
	mul r5, r2
	add r1, r5, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _02064622
	bl GF_AssertFail
_02064622:
	add r0, r4, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_02064630
sub_02064630: ; 0x02064630
	ldr r3, _0206463C ; =FreeToHeapExplicit
	add r1, r0, #0x0
	ldr r0, [r1, #0x8]
	ldr r1, [r1, #0xc]
	bx r3
	nop
_0206463C: .word FreeToHeapExplicit

	thumb_func_start sub_02064640
sub_02064640: ; 0x02064640
	push {r4, lr}
	mov r1, #0x0
	mov r2, #0xc8
	add r4, r0, #0x0
	bl memset
	ldr r1, _02064680 ; =sub_0206478C
	add r0, r4, #0x0
	bl sub_020646B8
	ldr r1, _02064684 ; =sub_02064798
	add r0, r4, #0x0
	bl sub_0206470C
	ldr r1, _02064688 ; =sub_02064790
	add r0, r4, #0x0
	bl sub_020646D4
	ldr r1, _0206468C ; =sub_02064794
	add r0, r4, #0x0
	bl sub_020646F0
	ldr r1, _02064690 ; =sub_0206479C
	add r0, r4, #0x0
	bl sub_02064728
	ldr r1, _02064694 ; =sub_020647A0
	add r0, r4, #0x0
	bl sub_02064730
	pop {r4, pc}
	nop
_02064680: .word sub_0206478C
_02064684: .word sub_02064798
_02064688: .word sub_02064790
_0206468C: .word sub_02064794
_02064690: .word sub_0206479C
_02064694: .word sub_020647A0

	thumb_func_start sub_02064698
sub_02064698: ; 0x02064698
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start sub_0206469C
sub_0206469C: ; 0x0206469C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start sub_020646A0
sub_020646A0: ; 0x020646A0
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	tst r1, r0
	bne _020646AA
	mov r0, #0x0
_020646AA:
	bx lr

	thumb_func_start sub_020646AC
sub_020646AC: ; 0x020646AC
	ldr r2, [r0, #0x0]
	mov r1, #0x1
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020646B8
sub_020646B8: ; 0x020646B8
	add r0, #0xb0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020646C0
sub_020646C0: ; 0x020646C0
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02064738
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r4, #0xb0
	ldr r2, [r4, #0x0]
	blx r2
	pop {r4, pc}

	thumb_func_start sub_020646D4
sub_020646D4: ; 0x020646D4
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020646DC
sub_020646DC: ; 0x020646DC
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02064738
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r4, #0xb4
	ldr r2, [r4, #0x0]
	blx r2
	pop {r4, pc}

	thumb_func_start sub_020646F0
sub_020646F0: ; 0x020646F0
	add r0, #0xb8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020646F8
sub_020646F8: ; 0x020646F8
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02064738
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r4, #0xb8
	ldr r2, [r4, #0x0]
	blx r2
	pop {r4, pc}

	thumb_func_start sub_0206470C
sub_0206470C: ; 0x0206470C
	add r0, #0xbc
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02064714
sub_02064714: ; 0x02064714
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02064738
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r4, #0xbc
	ldr r2, [r4, #0x0]
	blx r2
	pop {r4, pc}

	thumb_func_start sub_02064728
sub_02064728: ; 0x02064728
	add r0, #0xc0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02064730
sub_02064730: ; 0x02064730
	add r0, #0xc4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02064738
sub_02064738: ; 0x02064738
	add r0, #0x30
	bx lr

	thumb_func_start sub_0206473C
sub_0206473C: ; 0x0206473C
	push {r4, lr}
	add r4, r1, #0x0
	bl sub_02064738
	mov r1, #0x0
	add r2, r4, #0x0
	bl memset
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02064750
sub_02064750: ; 0x02064750
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start sub_02064754
sub_02064754: ; 0x02064754
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start sub_02064758
sub_02064758: ; 0x02064758
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start sub_0206475C
sub_0206475C: ; 0x0206475C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start sub_02064760
sub_02064760: ; 0x02064760
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start sub_02064764
sub_02064764: ; 0x02064764
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start sub_02064768
sub_02064768: ; 0x02064768
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start sub_0206476C
sub_0206476C: ; 0x0206476C
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x24
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_0206477C
sub_0206477C: ; 0x0206477C
	add r2, r0, #0x0
	add r2, #0x24
	add r3, r1, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start sub_0206478C
sub_0206478C: ; 0x0206478C
	mov r0, #0x1
	bx lr

	thumb_func_start sub_02064790
sub_02064790: ; 0x02064790
	bx lr
	.balign 4

	thumb_func_start sub_02064794
sub_02064794: ; 0x02064794
	bx lr
	.balign 4

	thumb_func_start sub_02064798
sub_02064798: ; 0x02064798
	bx lr
	.balign 4

	thumb_func_start sub_0206479C
sub_0206479C: ; 0x0206479C
	bx lr
	.balign 4

	thumb_func_start sub_020647A0
sub_020647A0: ; 0x020647A0
	bx lr
	.balign 4
