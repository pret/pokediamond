	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F3BC0
ov05_021F3BC0: ; 0x021F3BC0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	add r5, r0, #0
	mov r4, #0
_021F3BD0:
	mov r1, #0xf
	lsl r1, r1, #0xc
	add r2, r4, #0
	mul r2, r1
	ldr r1, _021F3C2C ; =ov05_021FD684
	lsl r0, r4, #2
	add r1, r1, r2
	add r6, r5, r0
	str r1, [r5, r0]
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021F3BEC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3BEC:
	cmp r7, #0
	beq _021F3C0A
	mov r1, #9
	mov r0, #4
	lsl r1, r1, #0xc
	bl AllocFromHeap
	str r0, [r6, #0x10]
	cmp r0, #0
	bne _021F3C04
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F3C04:
	mov r2, #9
	lsl r2, r2, #0xc
	b _021F3C10
_021F3C0A:
	mov r0, #0
	str r0, [r6, #0x10]
	add r2, r0, #0
_021F3C10:
	mov r1, #0xf
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r3, r5, #0
	bl ov05_021F3C74
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021F3BD0
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F3C2C: .word ov05_021FD684

	thumb_func_start ov05_021F3C30
ov05_021F3C30: ; 0x021F3C30
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r6, r0, #0
	add r7, r4, #0
_021F3C38:
	lsl r0, r4, #2
	add r5, r6, r0
	str r7, [r6, r0]
	ldr r0, [r5, #0x10]
	cmp r0, #0
	beq _021F3C4C
	bl FreeToHeap
	mov r0, #0
	str r0, [r5, #0x10]
_021F3C4C:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021F3C38
	add r0, r6, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F3C60
ov05_021F3C60: ; 0x021F3C60
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	str r0, [r2]
	bx lr

	thumb_func_start ov05_021F3C68
ov05_021F3C68: ; 0x021F3C68
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r0, [r0, #0x10]
	str r0, [r2]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F3C74
ov05_021F3C74: ; 0x021F3C74
	push {r3, r4, r5, r6, r7, lr}
	add r5, r3, #0
	lsl r4, r0, #2
	add r6, r1, #0
	add r7, r2, #0
	ldr r0, [r5, r4]
	mov r1, #0
	add r2, r6, #0
	bl MI_CpuFill8
	add r0, r5, r4
	ldr r0, [r0, #0x10]
	mov r1, #0
	add r2, r7, #0
	bl MI_CpuFill8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	.section .bss

	.global ov05_021FD684
ov05_021FD684: ; 0x021FD684
	.space 0x3C01C
