    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_02106FC8

	.text

	thumb_func_start FUN_02002F08
FUN_02002F08: ; 0x02002F08
	push {r4-r6, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002F3C ; =UNK_02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002F22
	bl ErrorHandling
_02002F22:
	add r0, r5, #0x0
	bl FUN_02021F2C
	add r1, r0, #0x0
	ldr r0, _02002F3C ; =UNK_02106FC8
	add r2, r6, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_02021934
	pop {r4-r6, pc}
	.balign 4
_02002F3C: .word UNK_02106FC8

	thumb_func_start FUN_02002F40
FUN_02002F40: ; 0x02002F40
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02002E14
	cmp r0, r4
	bhs _02002F52
	sub r0, r4, r0
	lsr r0, r0, #0x1
	pop {r4, pc}
_02002F52:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02002F58
FUN_02002F58: ; 0x02002F58
	push {r3-r7, lr}
	ldrh r2, [r0, #0x0]
	ldr r1, _02002F8C ; =0x0000FFFF
	mov r5, #0x1
	cmp r2, r1
	beq _02002F88
	mov r6, #0xe
	lsl r6, r6, #0xc
	add r7, r1, #0x0
	sub r4, r1, #0x1
_02002F6C:
	cmp r2, r4
	bne _02002F76
	bl FUN_0201B8B8
	b _02002F82
_02002F76:
	cmp r2, r6
	bne _02002F80
	add r5, r5, #0x1
	add r0, r0, #0x2
	b _02002F82
_02002F80:
	add r0, r0, #0x2
_02002F82:
	ldrh r2, [r0, #0x0]
	cmp r2, r7
	bne _02002F6C
_02002F88:
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_02002F8C: .word 0x0000FFFF

	thumb_func_start FUN_02002F90
FUN_02002F90: ; 0x02002F90
	push {r3, lr}
	bl FUN_02021F2C
	bl FUN_02002F58
	pop {r3, pc}

	thumb_func_start FUN_02002F9C
FUN_02002F9C: ; 0x02002F9C
	push {r3-r5, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002FCC ; =UNK_02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002FB4
	bl ErrorHandling
_02002FB4:
	add r0, r5, #0x0
	bl FUN_02021F2C
	add r1, r0, #0x0
	ldr r0, _02002FCC ; =UNK_02106FC8
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_0202199C
	pop {r3-r5, pc}
	.balign 4
_02002FCC: .word UNK_02106FC8

	thumb_func_start FUN_02002FD0
FUN_02002FD0: ; 0x02002FD0
	push {r4, lr}
	mov r1, #0x12
	lsl r1, r1, #0x4
	bl AllocFromHeap
	mov r2, #0x12
	mov r1, #0x0
	lsl r2, r2, #0x4
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02002FEC
FUN_02002FEC: ; 0x02002FEC
	ldr r3, _02002FF0 ; =FreeToHeap
	bx r3
	.balign 4
_02002FF0: .word FreeToHeap

	thumb_func_start FUN_02002FF4
FUN_02002FF4: ; 0x02002FF4
	push {r3-r4}
	mov r4, #0x14
	mul r4, r1
	str r2, [r0, r4]
	add r1, r0, r4
	ldr r0, [sp, #0x8]
	str r3, [r1, #0x4]
	str r0, [r1, #0x8]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02003008
FUN_02003008: ; 0x02003008
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	str r3, [sp, #0x4]
	add r0, r3, #0x0
	add r1, r4, #0x0
	bl AllocFromHeap
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	bl AllocFromHeap
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_02002FF4
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003038
FUN_02003038: ; 0x02003038
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x14
	add r5, r1, #0x0
	mul r5, r0
	ldr r0, [r4, r5]
	bl FreeToHeap
	add r0, r4, r5
	ldr r0, [r0, #0x4]
	bl FreeToHeap
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02003054
FUN_02003054: ; 0x02003054
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, sp, #0x8
	ldrh r7, [r0, #0x10]
	add r6, r2, #0x0
	mov r0, #0x14
	mul r6, r0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	ldr r1, [r5, r6]
	lsl r4, r3, #0x1
	add r1, r1, r4
	add r2, r7, #0x0
	bl MIi_CpuCopy16
	add r1, r5, r6
	ldr r1, [r1, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r1, r4
	add r2, r7, #0x0
	bl MIi_CpuCopy16
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02003084
FUN_02003084: ; 0x02003084
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, sp, #0x4
	ldr r4, [sp, #0x1c]
	bl FUN_02006C08
	add r6, r0, #0x0
	bne _0200309E
	bl ErrorHandling
_0200309E:
	cmp r4, #0x0
	bne _020030A6
	ldr r0, [sp, #0x4]
	ldr r4, [r0, #0x8]
_020030A6:
	add r0, sp, #0x8
	ldrh r0, [r0, #0x18]
	ldr r2, [sp, #0x18]
	mov r1, #0x14
	mul r1, r2
	add r1, r5, r1
	lsl r0, r0, #0x1
	ldr r1, [r1, #0x8]
	add r0, r4, r0
	cmp r0, r1
	bls _020030C0
	bl ErrorHandling
_020030C0:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r3, sp, #0x8
	ldr r2, [r1, #0xc]
	ldrh r1, [r3, #0x1c]
	ldrh r3, [r3, #0x18]
	add r0, r5, #0x0
	lsl r1, r1, #0x1
	add r1, r2, r1
	ldr r2, [sp, #0x18]
	bl FUN_02003054
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020030E8
FUN_020030E8: ; 0x020030E8
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #0x4]
	add r4, sp, #0x8
	ldrh r4, [r4, #0x18]
	str r4, [sp, #0x8]
	mov r4, #0x0
	str r4, [sp, #0xc]
	bl FUN_02003084
	add sp, #0x10
	pop {r4, pc}
	.balign 4
