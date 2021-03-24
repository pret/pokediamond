	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020343A8
FUN_020343A8: ; 0x020343A8
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x0
	strb r2, [r4, #0x1]
	mov r0, #0xe1
	ldr r7, _02034488 ; =0x0000070A
	ldr r6, _0203448C ; =0x00000A8E
	mov r12, r1
	strb r2, [r4, #0x0]
	add r3, r4, #0x0
	add r5, r2, #0x0
	lsl r0, r0, #0x2
_020343C4:
	add r1, r4, r2
	strh r5, [r3, #0x2]
	strb r5, [r1, r7]
	strh r5, [r3, r6]
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, r0
	blt _020343C4
	ldr r0, _02034490 ; =0x00001196
	mov r2, #0x0
_020343D8:
	add r1, r4, r5
	add r5, r5, #0x1
	strb r2, [r1, r0]
	cmp r5, #0x10
	blt _020343D8
	mov r0, #0x29
	mov r1, r12
	mov r2, #0xb
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	add r6, r0, #0x0
	ldrb r0, [r6, #0x0]
	add r5, r6, #0x5
	strb r0, [r4, #0x1]
	ldrb r0, [r6, #0x1]
	strb r0, [r4, #0x0]
	ldrb r0, [r6, #0x2]
	str r0, [sp, #0x8]
	ldrb r0, [r6, #0x3]
	str r0, [sp, #0x4]
	ldrb r7, [r6, #0x4]
	cmp r7, #0x10
	bls _0203440A
	bl ErrorHandling
_0203440A:
	ldr r1, _02034490 ; =0x00001196
	add r0, r5, #0x0
	add r1, r4, r1
	add r2, r7, #0x0
	bl MI_CpuCopy8
	ldr r0, [sp, #0x8]
	add r5, r5, r7
	cmp r0, #0x0
	beq _0203443A
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x2
	mul r2, r3
	lsl r2, r2, #0x1
	bl MI_CpuCopy8
	ldrb r1, [r4, #0x1]
	ldrb r0, [r4, #0x0]
	mul r0, r1
	lsl r0, r0, #0x1
	add r5, r5, r0
	b _0203444E
_0203443A:
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	ldr r0, [sp, #0x0]
	add r1, r4, #0x2
	lsl r0, r0, #0x10
	mul r2, r3
	lsr r0, r0, #0x10
	lsl r2, r2, #0x1
	bl MIi_CpuClear16
_0203444E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0203446C
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	ldr r1, _02034488 ; =0x0000070A
	add r0, r5, #0x0
	add r1, r4, r1
	mul r2, r3
	bl MI_CpuCopy8
	ldrb r1, [r4, #0x1]
	ldrb r0, [r4, #0x0]
	mul r0, r1
	add r5, r5, r0
_0203446C:
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	ldr r1, _0203448C ; =0x00000A8E
	add r0, r5, #0x0
	mul r2, r3
	add r1, r4, r1
	lsl r2, r2, #0x1
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02034488: .word 0x0000070A
_0203448C: .word 0x00000A8E
_02034490: .word 0x00001196

	thumb_func_start FUN_02034494
FUN_02034494: ; 0x02034494
	push {r3, lr}
	ldr r1, _020344A8 ; =0x000011AA
	mov r0, #0xb
	bl AllocFromHeap
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	pop {r3, pc}
	.balign 4
_020344A8: .word 0x000011AA

	thumb_func_start FUN_020344AC
FUN_020344AC: ; 0x020344AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl MapHeader_GetMatrixId
	add r6, r0, #0x0
	add r0, r4, #0x4
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_020343A8
	strb r6, [r4, #0x2]
	ldrb r0, [r4, #0x4]
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x5]
	strb r0, [r4, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020344D0
FUN_020344D0: ; 0x020344D0
	ldr r3, _020344D4 ; =FreeToHeap
	bx r3
	.balign 4
_020344D4: .word FreeToHeap

	thumb_func_start FUN_020344D8
FUN_020344D8: ; 0x020344D8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrb r1, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mul r0, r1
	cmp r5, r0
	blt _020344EC
	bl ErrorHandling
_020344EC:
	lsl r0, r5, #0x1
	add r1, r4, r0
	ldr r0, _020344F8 ; =0x00000A92
	ldrh r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_020344F8: .word 0x00000A92

	thumb_func_start FUN_020344FC
FUN_020344FC: ; 0x020344FC
	push {r4, lr}
	add r4, r0, #0x0
	bne _02034506
	bl ErrorHandling
_02034506:
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203450C
FUN_0203450C: ; 0x0203450C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02034516
	bl ErrorHandling
_02034516:
	ldrb r0, [r4, #0x1]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203451C
FUN_0203451C: ; 0x0203451C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldrb r0, [r7, #0x1]
	add r5, r1, #0x0
	add r4, r2, #0x0
	ldrb r6, [r7, #0x0]
	str r0, [sp, #0x0]
	cmp r5, #0x0
	blt _02034532
	cmp r5, r6
	blt _02034536
_02034532:
	bl ErrorHandling
_02034536:
	cmp r4, #0x0
	blt _02034540
	ldr r0, [sp, #0x0]
	cmp r4, r0
	blt _02034544
_02034540:
	bl ErrorHandling
_02034544:
	add r0, r4, #0x0
	mul r0, r6
	add r0, r5, r0
	lsl r0, r0, #0x1
	add r0, r7, r0
	ldrh r0, [r0, #0x6]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02034554
FUN_02034554: ; 0x02034554
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldrb r1, [r5, #0x0]
	ldrb r0, [r5, #0x1]
	mul r0, r1
	cmp r4, #0x0
	blt _02034568
	cmp r4, r0
	blt _0203456C
_02034568:
	bl ErrorHandling
_0203456C:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, #0x6]
	pop {r3-r5, pc}

	thumb_func_start FUN_02034574
FUN_02034574: ; 0x02034574
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02034578
FUN_02034578: ; 0x02034578
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x10]
	add r4, r2, #0x0
	add r6, r3, #0x0
	cmp r4, r0
	blt _0203458A
	bl ErrorHandling
_0203458A:
	ldr r0, [sp, #0x10]
	mul r0, r6
	add r4, r4, r0
	mov r0, #0xe1
	lsl r0, r0, #0x2
	cmp r4, r0
	blt _0203459C
	bl ErrorHandling
_0203459C:
	ldr r0, _020345A4 ; =0x0000070E
	add r1, r5, r4
	ldrb r0, [r1, r0]
	pop {r4-r6, pc}
	.balign 4
_020345A4: .word 0x0000070E

	thumb_func_start FUN_020345A8
FUN_020345A8: ; 0x020345A8
	push {r3-r5, lr}
	ldr r1, _020345D8 ; =0x00000708
	add r4, r0, #0x0
	bl AllocFromHeap
	add r5, r0, #0x0
	mov r0, #0x29
	mov r1, #0x0
	add r2, r4, #0x0
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	add r4, r0, #0x0
	ldrb r1, [r4, #0x4]
	add r0, r4, #0x5
	ldr r2, _020345D8 ; =0x00000708
	add r0, r0, r1
	add r1, r5, #0x0
	bl MI_CpuCopy8
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_020345D8: .word 0x00000708

	thumb_func_start FUN_020345DC
FUN_020345DC: ; 0x020345DC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020345E6
	bl ErrorHandling
_020345E6:
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020345F0
FUN_020345F0: ; 0x020345F0
	mov r3, #0x1e
	mul r3, r2
	add r1, r1, r3
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020345FC
FUN_020345FC: ; 0x020345FC
	push {r3-r5, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1c8
	add r3, r0, #0x0
	add r5, r1, #0x0
	lsl r1, r3, #0x10
	add r4, r2, #0x0
	add r0, sp, #0x0
	lsr r1, r1, #0x10
	mov r2, #0x0
	bl FUN_020343A8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r5, r0
	blt _0203462E
	bl ErrorHandling
_0203462E:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r4, r0
	blt _0203463A
	bl ErrorHandling
_0203463A:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	mul r0, r4
	add r0, r5, r0
	lsl r1, r0, #0x1
	add r0, sp, #0x0
	add r0, #0x2
	ldrh r0, [r0, r1]
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1c8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034660
FUN_02034660: ; 0x02034660
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bne _0203466C
	bl ErrorHandling
_0203466C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020344D8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034678
FUN_02034678: ; 0x02034678
	push {r4-r7}
	ldr r1, _020346C4 ; =0x00000A92
	ldrb r7, [r0, #0x0]
	add r2, r0, r1
	ldr r1, _020346C8 ; =0x0000070E
	add r1, r0, r1
	ldrb r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020346BE
	mov r0, #0x15
	add r6, r7, #0x0
	mul r6, r0
	add r5, r6, #0x0
	add r5, #0x17
	mov r4, #0xb0
	lsl r0, r5, #0x1
	add r6, #0x18
	strh r4, [r2, r0]
	lsl r0, r6, #0x1
	strh r4, [r2, r0]
	mov r0, #0x16
	add r3, r7, #0x0
	mul r3, r0
	add r0, r3, #0x0
	add r0, #0x17
	lsl r7, r0, #0x1
	add r3, #0x18
	strh r4, [r2, r7]
	lsl r7, r3, #0x1
	strh r4, [r2, r7]
	mov r2, #0x2
	strb r2, [r1, r5]
	strb r2, [r1, r6]
	strb r2, [r1, r0]
	strb r2, [r1, r3]
_020346BE:
	pop {r4-r7}
	bx lr
	nop
_020346C4: .word 0x00000A92
_020346C8: .word 0x0000070E

	thumb_func_start FUN_020346CC
FUN_020346CC: ; 0x020346CC
	push {r3-r4}
	ldr r1, _0203470C ; =0x00000A92
	add r2, r0, r1
	ldrb r1, [r0, #0x0]
	ldrb r0, [r0, #0x2]
	cmp r0, #0x0
	bne _02034706
	mov r0, #0xf
	mul r0, r1
	add r0, #0x1c
	mov r3, #0x77
	lsl r0, r0, #0x1
	strh r3, [r2, r0]
	lsl r0, r1, #0x4
	add r3, r0, #0x0
	add r3, #0x1b
	mov r4, #0x78
	lsl r3, r3, #0x1
	strh r4, [r2, r3]
	add r3, r0, #0x0
	add r3, #0x1c
	add r0, r1, r0
	add r0, #0x1b
	mov r4, #0x79
	lsl r3, r3, #0x1
	strh r4, [r2, r3]
	mov r3, #0x7a
	lsl r0, r0, #0x1
	strh r3, [r2, r0]
_02034706:
	pop {r3-r4}
	bx lr
	nop
_0203470C: .word 0x00000A92
