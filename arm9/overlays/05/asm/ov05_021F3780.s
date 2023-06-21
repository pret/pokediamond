	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F3780
ov05_021F3780: ; 0x021F3780
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	bl ov05_021F37AC
	add r4, r0, #0
	str r6, [r4]
	str r5, [r4, #8]
	bl ov05_021F37DC
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F379C
ov05_021F379C: ; 0x021F379C
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021F37E0
	add r0, r4, #0
	bl ov05_021F37D0
	pop {r4, pc}

	thumb_func_start ov05_021F37AC
ov05_021F37AC: ; 0x021F37AC
	push {r4, lr}
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0
	bne _021F37BC
	bl GF_AssertFail
_021F37BC:
	add r2, r4, #0
	mov r1, #0x10
	mov r0, #0
_021F37C2:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _021F37C2
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F37D0
ov05_021F37D0: ; 0x021F37D0
	ldr r3, _021F37D8 ; =FreeToHeapExplicit
	add r1, r0, #0
	ldr r0, [r1]
	bx r3
	.balign 4, 0
_021F37D8: .word FreeToHeapExplicit

	thumb_func_start ov05_021F37DC
ov05_021F37DC: ; 0x021F37DC
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F37E0
ov05_021F37E0: ; 0x021F37E0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021F380E
	ldr r4, [r5, #0xc]
	cmp r4, #0
	beq _021F380E
_021F37F0:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	beq _021F37FC
	add r0, r4, #0
	bl ov05_021F383C
_021F37FC:
	ldr r0, [r5, #4]
	add r4, #0x60
	sub r0, r0, #1
	str r0, [r5, #4]
	bne _021F37F0
	ldr r0, [r5]
	ldr r1, [r5, #0xc]
	bl FreeToHeapExplicit
_021F380E:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F3810
ov05_021F3810: ; 0x021F3810
	push {r3, r4, r5, lr}
	add r4, r0, #0
	str r1, [r4, #4]
	mov r0, #0x60
	add r5, r1, #0
	mul r5, r0
	ldr r0, [r4]
	add r1, r5, #0
	bl AllocFromHeap
	str r0, [r4, #0xc]
	cmp r0, #0
	bne _021F382E
	bl GF_AssertFail
_021F382E:
	ldr r0, [r4, #0xc]
	mov r1, #0
	add r2, r5, #0
	bl memset
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F383C
ov05_021F383C: ; 0x021F383C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	bl FreeToHeap
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x60
	bl memset
	pop {r4, pc}
	.balign 4, 0
