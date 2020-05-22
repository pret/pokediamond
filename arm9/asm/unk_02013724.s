    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020ED54C
UNK_020ED54C: ; 0x020ED54C
	.byte 0x8D, 0x01, 0x8F, 0x01, 0x8B, 0x01, 0x8C, 0x01, 0x8E, 0x01

	.global UNK_020ED556
UNK_020ED556: ; 0x020ED556
	.byte 0x00

	.global UNK_020ED557
UNK_020ED557: ; 0x020ED557
	.byte 0x00

	.global UNK_020ED558
UNK_020ED558: ; 0x020ED558
	.byte 0x84, 0x01

	.global UNK_020ED55A
UNK_020ED55A: ; 0x020ED55A
	.byte 0x07, 0x00

	.global UNK_020ED55C
UNK_020ED55C: ; 0x020ED55C
	.byte 0xFF, 0xFF

	.global UNK_020ED55E
UNK_020ED55E: ; 0x020ED55E
	.byte 0x00, 0x00, 0x01, 0x00, 0x84, 0x01, 0x21, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x02, 0x00, 0x88, 0x01
	.byte 0x0A, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x04, 0x84, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00
	.byte 0x00, 0x00

	.text

	thumb_func_start FUN_02013724
FUN_02013724: ; 0x02013724
	ldr r1, _02013738 ; =0x0000FFFF
	mov r2, #0x0
	strh r1, [r0, #0x0]
_0201372A:
	add r2, r2, #0x1
	strh r1, [r0, #0x4]
	add r0, r0, #0x2
	cmp r2, #0x2
	blt _0201372A
	bx lr
	nop
_02013738: .word 0x0000FFFF

	thumb_func_start FUN_0201373C
FUN_0201373C: ; 0x0201373C
	strh r1, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _02013750 ; =0x0000FFFF
	strh r2, [r0, #0x2]
_02013744:
	add r2, r2, #0x1
	strh r1, [r0, #0x4]
	add r0, r0, #0x2
	cmp r2, #0x2
	blt _02013744
	bx lr
	.balign 4
_02013750: .word 0x0000FFFF

	thumb_func_start FUN_02013754
FUN_02013754: ; 0x02013754
	push {r4, lr}
	mov r1, #0x4
	add r4, r0, #0x0
	bl FUN_0201373C
	mov r0, #0x5
	strh r0, [r4, #0x2]
	pop {r4, pc}

	thumb_func_start FUN_02013764
FUN_02013764: ; 0x02013764
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0x4
	blo _02013772
	bl ErrorHandling
_02013772:
	cmp r6, #0x4
	bhs _020137B8
	mov r0, #0xa
	add r4, r6, #0x0
	mul r4, r0
	ldr r1, _020137BC ; =UNK_020ED556
	add r0, r5, #0x0
	ldrb r1, [r1, r4]
	bl FUN_0201373C
	ldr r0, _020137C0 ; =UNK_020ED557
	mov r1, #0x0
	ldrb r0, [r0, r4]
	mvn r1, r1
	strh r0, [r5, #0x2]
	ldr r0, _020137C4 ; =UNK_020ED558
	ldrsh r0, [r0, r4]
	cmp r0, r1
	beq _020137A2
	ldr r1, _020137C8 ; =UNK_020ED55A
	ldrh r1, [r1, r4]
	bl FUN_02013A9C
	strh r0, [r5, #0x4]
_020137A2:
	ldr r0, _020137CC ; =UNK_020ED55C
	mov r1, #0x0
	ldrsh r0, [r0, r4]
	mvn r1, r1
	cmp r0, r1
	beq _020137B8
	ldr r1, _020137D0 ; =UNK_020ED55E
	ldrh r1, [r1, r4]
	bl FUN_02013A9C
	strh r0, [r5, #0x6]
_020137B8:
	pop {r4-r6, pc}
	nop
_020137BC: .word UNK_020ED556
_020137C0: .word UNK_020ED557
_020137C4: .word UNK_020ED558
_020137C8: .word UNK_020ED55A
_020137CC: .word UNK_020ED55C
_020137D0: .word UNK_020ED55E

	thumb_func_start FUN_020137D4
FUN_020137D4: ; 0x020137D4
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, r1, #0x0
	str r1, [sp, #0x4]
	bl FUN_0200AA80
	ldr r5, [sp, #0x0]
	ldr r7, _02013838 ; =0x0000FFFF
	add r6, r0, #0x0
	mov r4, #0x0
_020137EA:
	ldrh r2, [r5, #0x4]
	cmp r2, r7
	beq _02013800
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0200B518
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x2
	blt _020137EA
_02013800:
	ldr r2, [sp, #0x0]
	mov r0, #0x1
	ldrh r2, [r2, #0x0]
	mov r1, #0x1a
	lsl r3, r2, #0x1
	ldr r2, _0201383C ; =UNK_020ED54C
	ldrh r2, [r2, r3]
	ldr r3, [sp, #0x4]
	bl FUN_0200A86C
	add r5, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	ldrh r2, [r2, #0x2]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0200A9C4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r6, #0x0
	bl FUN_0200AB18
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02013838: .word 0x0000FFFF
_0201383C: .word UNK_020ED54C

	thumb_func_start FUN_02013840
FUN_02013840: ; 0x02013840
	push {r4, lr}
	add r4, r0, #0x0
	add r3, r1, #0x0
	ldrh r1, [r4, #0x0]
	mov r0, #0x1a
	lsl r2, r1, #0x1
	ldr r1, _02013858 ; =UNK_020ED54C
	ldrh r1, [r1, r2]
	ldrh r2, [r4, #0x2]
	bl FUN_0200A738
	pop {r4, pc}
	.balign 4
_02013858: .word UNK_020ED54C

	thumb_func_start FUN_0201385C
FUN_0201385C: ; 0x0201385C
	ldrh r1, [r0, #0x0]
	ldr r0, _0201386C ; =0x0000FFFF
	cmp r1, r0
	beq _02013868
	mov r0, #0x1
	bx lr
_02013868:
	mov r0, #0x0
	bx lr
	.balign 4
_0201386C: .word 0x0000FFFF

	thumb_func_start FUN_02013870
FUN_02013870: ; 0x02013870
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	ldrh r1, [r4, #0x2]
	bl FUN_020138A0
	mov r3, #0x0
	cmp r0, #0x0
	bls _02013896
	ldr r1, _0201389C ; =0x0000FFFF
_02013884:
	ldrh r2, [r4, #0x4]
	cmp r2, r1
	bne _0201388E
	mov r0, #0x0
	pop {r4, pc}
_0201388E:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, r0
	blo _02013884
_02013896:
	mov r0, #0x1
	pop {r4, pc}
	nop
_0201389C: .word 0x0000FFFF

	thumb_func_start FUN_020138A0
FUN_020138A0: ; 0x020138A0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x5
	blo _020138AE
	bl ErrorHandling
_020138AE:
	add r0, r5, #0x0
	bl FUN_02013974
	cmp r4, r0
	blo _020138BC
	bl ErrorHandling
_020138BC:
	ldr r1, _02013910 ; =UNK_020ED54C
	lsl r2, r5, #0x1
	ldrh r1, [r1, r2]
	mov r0, #0x1a
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200A738
	str r0, [sp, #0x0]
	bl FUN_02021F2C
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _02013914 ; =0x0000FFFF
	mov r5, #0x0
	cmp r1, r0
	beq _02013904
	add r7, r0, #0x0
	sub r6, r0, #0x1
_020138E2:
	cmp r1, r6
	bne _020138FC
	add r0, r4, #0x0
	bl FUN_0201B8F8
	cmp r0, #0x0
	beq _020138F2
	add r5, r5, #0x1
_020138F2:
	add r0, r4, #0x0
	bl FUN_0201B8B8
	add r4, r0, #0x0
	b _020138FE
_020138FC:
	add r4, r4, #0x2
_020138FE:
	ldrh r1, [r4, #0x0]
	cmp r1, r7
	bne _020138E2
_02013904:
	ldr r0, [sp, #0x0]
	bl FUN_02021A20
	add r0, r5, #0x0
	pop {r3-r7, pc}
	nop
_02013910: .word UNK_020ED54C
_02013914: .word 0x0000FFFF

	thumb_func_start FUN_02013918
FUN_02013918: ; 0x02013918
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02013920
FUN_02013920: ; 0x02013920
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02013924
FUN_02013924: ; 0x02013924
	ldrh r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02013928
FUN_02013928: ; 0x02013928
	push {r3-r4}
	ldrh r3, [r0, #0x0]
	ldrh r2, [r1, #0x0]
	cmp r3, r2
	bne _0201393A
	ldrh r3, [r0, #0x2]
	ldrh r2, [r1, #0x2]
	cmp r3, r2
	beq _02013940
_0201393A:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_02013940:
	mov r4, #0x0
_02013942:
	ldrh r3, [r0, #0x4]
	ldrh r2, [r1, #0x4]
	cmp r3, r2
	beq _02013950
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_02013950:
	add r4, r4, #0x1
	add r1, r1, #0x2
	add r0, r0, #0x2
	cmp r4, #0x2
	blt _02013942
	mov r0, #0x1
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02013960
FUN_02013960: ; 0x02013960
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x0]
	ldrh r2, [r1, #0x2]
	strh r2, [r0, #0x2]
	ldrh r2, [r1, #0x4]
	strh r2, [r0, #0x4]
	ldrh r1, [r1, #0x6]
	strh r1, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_02013974
FUN_02013974: ; 0x02013974
	cmp r0, #0x5
	bhs _0201397C
	mov r0, #0x14
	bx lr
_0201397C:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02013980
FUN_02013980: ; 0x02013980
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x5
	blo _02013990
	bl ErrorHandling
_02013990:
	strh r4, [r5, #0x0]
	strh r6, [r5, #0x2]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02013998
FUN_02013998: ; 0x02013998
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x2
	blo _020139A8
	bl ErrorHandling
_020139A8:
	lsl r0, r4, #0x1
	add r0, r5, r0
	strh r6, [r0, #0x4]
	pop {r4-r6, pc}

	thumb_func_start FUN_020139B0
FUN_020139B0: ; 0x020139B0
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	ldrh r1, [r4, #0x2]
	bl FUN_020138A0
	cmp r0, #0x2
	bhs _020139D0
	lsl r1, r0, #0x1
	add r2, r4, r1
	ldr r1, _020139D4 ; =0x0000FFFF
_020139C6:
	add r0, r0, #0x1
	strh r1, [r2, #0x4]
	add r2, r2, #0x2
	cmp r0, #0x2
	blo _020139C6
_020139D0:
	pop {r4, pc}
	nop
_020139D4: .word 0x0000FFFF
