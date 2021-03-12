	.include "asm/macros.inc"
    .include "global.inc"

    .extern gFonts
    .extern UNK_021C570C
    .extern UNK_021C5714
    .extern UNK_021C5734
    .extern FUN_0201BCC8
    .extern FUN_0201BCFC
    .extern FUN_0201BD44

	.text

	thumb_func_start FUN_0201C100
FUN_0201C100: ; 0x0201C100
	ldrh r2, [r0, #0x0]
	lsr r2, r2, #0x8
	lsl r3, r2, #0x1
	ldr r2, _0201C1A4 ; =UNK_021C5734
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x0]
	ldrh r3, [r0, #0x0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x2]
	ldrh r3, [r0, #0x2]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x4]
	ldrh r3, [r0, #0x2]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x6]
	ldrh r3, [r0, #0x4]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x8]
	ldrh r3, [r0, #0x4]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xa]
	ldrh r3, [r0, #0x6]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xc]
	ldrh r3, [r0, #0x6]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0xe]
	ldrh r3, [r0, #0x8]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x10]
	ldrh r3, [r0, #0x8]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x12]
	ldrh r3, [r0, #0xa]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x14]
	ldrh r3, [r0, #0xa]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x16]
	ldrh r3, [r0, #0xc]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x18]
	ldrh r3, [r0, #0xc]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x17
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x1a]
	ldrh r3, [r0, #0xe]
	lsr r3, r3, #0x8
	lsl r3, r3, #0x1
	ldrh r3, [r2, r3]
	strh r3, [r1, #0x1c]
	ldrh r0, [r0, #0xe]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x17
	ldrh r0, [r2, r0]
	strh r0, [r1, #0x1e]
	bx lr
	.balign 4
_0201C1A4: .word UNK_021C5734

	thumb_func_start FUN_0201C1A8
FUN_0201C1A8: ; 0x0201C1A8
	mov r1, #0x0
	str r1, [r0, #0x2c]
	bx lr
	.balign 4

	thumb_func_start FUN_0201C1B0
FUN_0201C1B0: ; 0x0201C1B0
	push {r3-r5, lr}
	sub sp, #0x8
	mov r1, #0x6
	mov r0, #0x0
	lsl r1, r1, #0x8
	bl AllocFromHeap
	mov r2, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0xe
	mov r1, #0x5
	add r3, sp, #0x4
	bl FUN_02006BB0
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	mov r2, #0x6
	ldr r0, [r0, #0x14]
	add r1, r5, #0x0
	lsl r2, r2, #0x8
	bl MIi_CpuCopy32
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201C1EC
FUN_0201C1EC: ; 0x0201C1EC
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	ldr r0, [r4, #0x2c]
	add r7, r3, #0x0
	ldr r5, [r4, #0x4]
	cmp r0, #0x0
	bne _0201C202
	bl FUN_0201C1B0
	str r0, [r4, #0x2c]
_0201C202:
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r6, r7, #0x0
	mul r6, r0
	add r0, r5, #0x0
	ldr r4, [r4, #0x2c]
	bl FUN_0201AB0C
	sub r0, r0, #0x3
	lsl r0, r0, #0x13
	mov r1, #0x18
	lsr r2, r0, #0x10
	str r1, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	add r1, r4, r6
	add r3, r2, #0x0
	bl FUN_02019658
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_0201C238
FUN_0201C238: ; 0x0201C238
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _0201C24A
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x2c]
_0201C24A:
	pop {r4, pc}
