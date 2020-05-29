    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204AEA8
FUN_0204AEA8: ; 0x0204AEA8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _0204AEC6
	cmp r1, #0x1
	beq _0204AEE6
	b _0204AEF4
_0204AEC6:
	ldr r0, [r4, #0x8]
	add r1, r5, #0x0
	add r2, r4, #0x4
	bl MOD05_021E3444
	ldr r1, [r4, #0xc]
	mov r0, #0x5
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x1
	bl FUN_0200433C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204AEF4
_0204AEE6:
	ldr r1, [r4, #0x4]
	cmp r1, #0x1
	bne _0204AEF4
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0204AEF4:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0204AEF8
FUN_0204AEF8: ; 0x0204AEF8
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x10
	add r4, r2, #0x0
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r0, [r2, #0x4]
	str r5, [r2, #0x8]
	ldr r1, _0204AF20 ; =FUN_0204AEA8
	add r0, r6, #0x0
	str r4, [r2, #0xc]
	bl FUN_0204640C
	pop {r4-r6, pc}
	nop
_0204AF20: .word FUN_0204AEA8
