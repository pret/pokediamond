.section .text

glabel GenerateFontHalfRowLookupTable

.extern UNK_021C570C
.extern UNK_021C5734

	push {r3-r7, lr}
	sub sp, #0x30
	ldr r3, _0201C0F8 ; =UNK_021C570C
	mov r5, #0x0
	str r5, [sp, #0x20]
	str r0, [sp, #0x24]
	str r2, [sp, #0x28]
	str r1, [sp, #0x2c]
	strh r1, [r3, #0x6]
	strh r0, [r3, #0x2]
	add r0, sp, #0x20
	strh r2, [r3, #0x4]
	str r5, [sp, #0x14]
	str r0, [sp, #0x8]
	mov r12, r0
	mov lr, r0
	str r0, [sp, #0x18]
_0201C07E:
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x1c]
_0201C08C:
	mov r0, #0x0
	str r0, [sp, #0xc]
	mov r0, lr
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x0]
	lsl r7, r0, #0x4
_0201C09A:
	ldr r0, [sp, #0x0]
	mov r3, #0x0
	ldr r0, [r0, #0x0]
	mov r4, r12
	lsl r6, r0, #0x8
_0201C0A4:
	ldr r0, [r4, #0x0]
	add r1, r7, #0x0
	lsl r0, r0, #0xc
	orr r0, r6
	orr r1, r0
	ldr r0, [sp, #0x1c]
	add r3, r3, #0x1
	add r2, r0, #0x0
	orr r2, r1
	lsl r1, r5, #0x1
	ldr r0, _0201C0FC ; =UNK_021C5734
	add r5, r5, #0x1
	add r4, r4, #0x4
	strh r2, [r0, r1]
	cmp r3, #0x4
	blt _0201C0A4
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _0201C09A
	ldr r0, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x10]
	add r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, #0x4
	blt _0201C08C
	ldr r0, [sp, #0x8]
	add r0, r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x4
	blt _0201C07E
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0201C0F8: .word UNK_021C570C
_0201C0FC: .word UNK_021C5734
