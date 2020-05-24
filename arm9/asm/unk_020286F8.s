	.include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C59D0
UNK_021C59D0: ; 0x021C59D0
	.space 0x4

	.text

	thumb_func_start FUN_020286F8
FUN_020286F8: ; 0x020286F8
	mov r0, #0x42
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02028700
FUN_02028700: ; 0x02028700
	push {r4-r5}
	add r5, r2, #0x0
	mov r3, #0x2c
	add r2, r1, #0x0
	mul r2, r3
	mul r5, r3
	add r4, r0, r2
	add r3, r0, r5
	mov r2, #0x5
_02028712:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02028712
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02028724
FUN_02028724: ; 0x02028724
	push {r4, lr}
	add r4, r0, #0x0
	mov r2, #0x42
	mov r0, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl MIi_CpuClearFast
	ldr r0, _0202874C ; =0x0000FFFF
	mov r1, #0x0
	add r2, r4, #0x0
_0202873A:
	strh r0, [r2, #0x0]
	strh r0, [r2, #0x10]
	add r1, r1, #0x1
	add r2, #0x2c
	cmp r1, #0x6
	blt _0202873A
	ldr r0, _02028750 ; =UNK_021C59D0
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_0202874C: .word 0x0000FFFF
_02028750: .word UNK_021C59D0

	thumb_func_start FUN_02028754
FUN_02028754: ; 0x02028754
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r7, #0x0
_0202875C:
	mov r4, #0x0
	cmp r6, #0x0
	bls _02028770
_02028762:
	ldr r0, [r5, #0x28]
	bl rand_ALT
	add r4, r4, #0x1
	str r0, [r5, #0x28]
	cmp r4, r6
	blo _02028762
_02028770:
	add r7, r7, #0x1
	add r5, #0x2c
	cmp r7, #0x6
	blo _0202875C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202877C
FUN_0202877C: ; 0x0202877C
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x24]
	bx lr
	.balign 4

	thumb_func_start FUN_02028788
FUN_02028788: ; 0x02028788
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x2c
	add r4, r1, #0x0
	mul r4, r0
	add r0, r5, r4
	str r2, [r0, #0x24]
	add r0, r2, #0x0
	bl rand_ALT
	add r1, r5, r4
	str r0, [r1, #0x28]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020287A4
FUN_020287A4: ; 0x020287A4
	ldr r0, [r0, #0x54]
	bx lr

	thumb_func_start FUN_020287A8
FUN_020287A8: ; 0x020287A8
	cmp r2, #0x0
	bne _020287B4
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	bx lr
_020287B4:
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	add r0, #0x10
	bx lr
	.balign 4

	thumb_func_start FUN_020287C0
FUN_020287C0: ; 0x020287C0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r2, #0x0
	bne _020287D8
	mov r2, #0x2c
	mul r2, r1
	add r1, r4, r2
	add r0, r3, #0x0
	mov r2, #0x8
	bl FUN_02021EF0
	pop {r4, pc}
_020287D8:
	mov r2, #0x2c
	mul r2, r1
	add r1, r4, r2
	add r0, r3, #0x0
	add r1, #0x10
	mov r2, #0x8
	bl FUN_02021EF0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020287EC
FUN_020287EC: ; 0x020287EC
	mov r3, #0x2c
	mul r3, r1
	add r0, r0, r3
	add r0, #0x20
	strb r2, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020287F8
FUN_020287F8: ; 0x020287F8
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02028804
FUN_02028804: ; 0x02028804
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02028810
FUN_02028810: ; 0x02028810
	mov r3, #0x2c
	mul r3, r1
	add r0, r0, r3
	add r0, #0x21
	strb r2, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202881C
FUN_0202881C: ; 0x0202881C
	ldr r3, _02028824 ; =FUN_02022610
	mov r1, #0x11
	bx r3
	nop
_02028824: .word FUN_02022610

	thumb_func_start FUN_02028828
FUN_02028828: ; 0x02028828
	push {r3, lr}
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	bl FUN_0202888C
	cmp r0, #0x0
	bne _0202883C
	mov r0, #0x1
	pop {r3, pc}
_0202883C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02028840
FUN_02028840: ; 0x02028840
	mov r2, #0x2c
	add r3, r0, #0x0
	mul r2, r1
	add r1, r3, r2
	ldr r3, _02028850 ; =FUN_020288AC
	add r0, #0x2c
	bx r3
	nop
_02028850: .word FUN_020288AC

	thumb_func_start FUN_02028854
FUN_02028854: ; 0x02028854
	push {r3-r7, lr}
	add r6, r1, #0x0
	ldrh r1, [r6, #0x0]
	add r5, r0, #0x0
	ldr r0, _02028888 ; =0x0000FFFF
	cmp r1, r0
	bne _02028866
	mov r0, #0x0
	pop {r3-r7, pc}
_02028866:
	mov r4, #0x0
	mov r7, #0x8
_0202886A:
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl StringNotEqualN
	cmp r0, #0x0
	bne _0202887C
	mov r0, #0x1
	pop {r3-r7, pc}
_0202887C:
	add r4, r4, #0x1
	add r5, #0x2c
	cmp r4, #0x6
	blt _0202886A
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02028888: .word 0x0000FFFF

	thumb_func_start FUN_0202888C
FUN_0202888C: ; 0x0202888C
	ldrh r2, [r0, #0x0]
	ldr r1, _020288A8 ; =0x0000FFFF
	cmp r2, r1
	bne _02028898
	mov r0, #0x1
	bx lr
_02028898:
	ldrh r0, [r0, #0x10]
	cmp r0, r1
	bne _020288A2
	mov r0, #0x1
	bx lr
_020288A2:
	mov r0, #0x0
	bx lr
	nop
_020288A8: .word 0x0000FFFF

	thumb_func_start FUN_020288AC
FUN_020288AC: ; 0x020288AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, #0x10
	add r1, #0x10
	mov r2, #0x8
	bl StringNotEqualN
	cmp r0, #0x0
	beq _020288C4
	mov r0, #0x0
	pop {r3-r5, pc}
_020288C4:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x8
	bl StringNotEqualN
	cmp r0, #0x0
	beq _020288D6
	mov r0, #0x0
	pop {r3-r5, pc}
_020288D6:
	add r0, r5, #0x0
	add r0, #0x20
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	beq _020288EA
	mov r0, #0x0
	pop {r3-r5, pc}
_020288EA:
	add r0, r5, #0x0
	add r0, #0x21
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	beq _020288FE
	mov r0, #0x0
	pop {r3-r5, pc}
_020288FE:
	ldr r1, [r5, #0x24]
	ldr r0, [r4, #0x24]
	cmp r1, r0
	bne _0202890A
	mov r0, #0x1
	pop {r3-r5, pc}
_0202890A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
