    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F450C
UNK_020F450C: ; 0x020F450C
	.byte 0x67, 0x00

	.global UNK_020F450E
UNK_020F450E: ; 0x020F450E
	.byte 0x8E, 0x00, 0x65, 0x00, 0x8A, 0x00, 0x66, 0x00, 0x8C, 0x00, 0x63, 0x00, 0x59, 0x01, 0x64, 0x00
	.byte 0x5B, 0x01, 0x68, 0x00, 0x9A, 0x01, 0x69, 0x00, 0x98, 0x01

	.text

	thumb_func_start FUN_02045268
FUN_02045268: ; 0x02045268
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl GetVarPointer
	mov r4, #0x0
	ldr r7, _020452B0 ; =UNK_020F450C
	str r0, [sp, #0x0]
	add r5, r4, #0x0
_02045288:
	ldr r0, [r6, #0xc]
	bl Sav2_Bag_get
	lsl r1, r4, #0x2
	ldrh r1, [r7, r1]
	mov r2, #0x4
	bl Bag_GetQuantity
	add r0, r5, r0
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x7
	blo _02045288
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_020452B0: .word UNK_020F450C

	thumb_func_start FUN_020452B4
FUN_020452B4: ; 0x020452B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl VarGet
	mov r5, #0x0
	ldr r2, _02045300 ; =UNK_020F450C
	strh r5, [r4, #0x0]
_020452E0:
	lsl r3, r5, #0x2
	ldrh r1, [r2, r3]
	cmp r0, r1
	bne _020452F0
	ldr r0, _02045304 ; =UNK_020F450E
	ldrh r0, [r0, r3]
	strh r0, [r4, #0x0]
	b _020452FA
_020452F0:
	add r1, r5, #0x1
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	cmp r5, #0x7
	blo _020452E0
_020452FA:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02045300: .word UNK_020F450C
_02045304: .word UNK_020F450E

	thumb_func_start FUN_02045308
FUN_02045308: ; 0x02045308
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r7, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl GetVarPointer
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl VarGet
	str r0, [sp, #0x0]
	mov r4, #0x0
	ldr r0, [sp, #0x8]
	add r6, r4, #0x0
	strh r4, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r4, [r0, #0x0]
_02045358:
	ldr r0, [r7, #0xc]
	lsl r5, r4, #0x2
	bl Sav2_Bag_get
	ldr r1, _02045394 ; =UNK_020F450C
	mov r2, #0x4
	ldrh r1, [r1, r5]
	bl Bag_GetQuantity
	add r0, r6, r0
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	cmp r6, r0
	blo _02045384
	ldr r0, _02045394 ; =UNK_020F450C
	ldrh r1, [r0, r5]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	strh r4, [r0, #0x0]
	b _0204538E
_02045384:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x7
	blo _02045358
_0204538E:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02045394: .word UNK_020F450C

	thumb_func_start FUN_02045398
FUN_02045398: ; 0x02045398
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0204539C
FUN_0204539C: ; 0x0204539C
	mov r0, #0x0
	bx lr
