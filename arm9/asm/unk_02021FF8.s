	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EE6CC
UNK_020EE6CC: ; 0x020EE6CC
	.word FUN_020221EC
	.word FUN_02022208

	.text

	thumb_func_start FUN_02022030
FUN_02022030: ; 0x02022030
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _02022044
	ldrh r1, [r0, #0x8]
	mov r0, #0xf1
	lsl r0, r0, #0x8
	cmp r1, r0
	bne _02022044
	mov r0, #0x1
	bx lr
_02022044:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02022048
FUN_02022048: ; 0x02022048
	push {r3-r7, lr}
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02022030
	cmp r0, #0x0
	beq _020220B2
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	ldrh r0, [r0, #0x2]
	add r1, #0x8
	ldr r7, _020220BC ; =0x000001FF
	lsl r0, r0, #0x1
	add r3, r1, r0
	mov r0, #0x0
	add r4, #0xa
	add r1, r0, #0x0
_0202206C:
	ldrh r2, [r4, #0x0]
	asr r2, r0
	and r2, r7
	lsl r2, r2, #0x10
	add r0, #0x9
	lsr r2, r2, #0x10
	cmp r0, #0xf
	blt _02022094
	add r4, r4, #0x2
	sub r0, #0xf
	beq _02022094
	ldrh r6, [r4, #0x0]
	mov r5, #0x9
	sub r5, r5, r0
	lsl r6, r5
	ldr r5, _020220BC ; =0x000001FF
	and r5, r6
	orr r2, r5
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
_02022094:
	ldr r5, _020220BC ; =0x000001FF
	cmp r2, r5
	beq _020220A2
	strh r2, [r3, #0x0]
	add r3, r3, #0x2
	add r1, r1, #0x1
	b _0202206C
_020220A2:
	ldr r0, _020220C0 ; =0x0000FFFF
	strh r0, [r3, #0x0]
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x2]
	add r1, r0, r1
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x2]
	pop {r3-r7, pc}
_020220B2:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl FUN_02021F4C
	pop {r3-r7, pc}
	.balign 4
_020220BC: .word 0x000001FF
_020220C0: .word 0x0000FFFF

	thumb_func_start FUN_020220C4
FUN_020220C4: ; 0x020220C4
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	cmp r7, #0x0
	bne _020220D6
	bl ErrorHandling
_020220D6:
	ldr r0, [sp, #0x18]
	mov r1, #0x14
	bl FUN_02016998
	add r4, r0, #0x0
	beq _0202211C
	str r5, [r4, #0x0]
	str r7, [r4, #0x4]
	ldr r0, [sp, #0x0]
	str r6, [r4, #0x8]
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x18]
	lsl r1, r7, #0x2
	bl FUN_02016998
	str r0, [r4, #0x10]
	cmp r0, #0x0
	beq _02022114
	mov r6, #0x0
	cmp r7, #0x0
	bls _0202211C
	add r5, r6, #0x0
_02022102:
	ldr r0, [r4, #0x10]
	add r0, r0, r5
	bl FUN_02022120
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, r7
	blo _02022102
	b _0202211C
_02022114:
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r4, #0x0
_0202211C:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02022120
FUN_02022120: ; 0x02022120
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strh r1, [r0, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_0202212C
FUN_0202212C: ; 0x0202212C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02022136
	bl ErrorHandling
_02022136:
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02022144
FUN_02022144: ; 0x02022144
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_02020A98
	str r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02022190
	bl FUN_02020AA4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	bls _020221AE
	add r4, r6, #0x0
_02022164:
	ldr r0, [r5, #0x10]
	add r0, r0, r4
	ldrb r0, [r0, #0x1]
	cmp r0, #0x0
	ldr r0, [r5, #0x0]
	beq _02022178
	add r0, r0, r4
	bl FUN_02020A40
	b _0202217E
_02022178:
	add r0, r0, r4
	bl FUN_02020A6C
_0202217E:
	ldr r1, [r5, #0x10]
	add r6, r6, #0x1
	add r1, r1, r4
	strb r0, [r1, #0x1]
	ldr r0, [r5, #0x4]
	add r4, r4, #0x4
	cmp r6, r0
	blo _02022164
	b _020221AE
_02022190:
	ldr r0, [r5, #0x4]
	mov r3, #0x0
	str r3, [sp, #0x4]
	cmp r0, #0x0
	bls _020221AE
	add r2, r3, #0x0
	add r1, r3, #0x0
_0202219E:
	ldr r0, [r5, #0x10]
	add r3, r3, #0x1
	add r0, r0, r2
	strb r1, [r0, #0x1]
	ldr r0, [r5, #0x4]
	add r2, r2, #0x4
	cmp r3, r0
	blo _0202219E
_020221AE:
	mov r4, #0x0
	cmp r0, #0x0
	bls _020221E4
	add r7, r4, #0x0
_020221B6:
	ldr r3, [r5, #0x10]
	ldr r1, [sp, #0x0]
	add r0, r3, r7
	ldrb r3, [r3, r7]
	ldr r2, [sp, #0x4]
	lsl r6, r3, #0x2
	ldr r3, _020221E8 ; =UNK_020EE6CC
	ldr r3, [r3, r6]
	blx r3
	add r1, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	beq _020221DA
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #0x8]
	add r0, r4, #0x0
	blx r3
_020221DA:
	ldr r0, [r5, #0x4]
	add r4, r4, #0x1
	add r7, r7, #0x4
	cmp r4, r0
	blo _020221B6
_020221E4:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020221E8: .word UNK_020EE6CC

	thumb_func_start FUN_020221EC
FUN_020221EC: ; 0x020221EC
	push {r3, lr}
	ldrb r1, [r0, #0x1]
	cmp r1, #0x0
	beq _02022202
	cmp r2, #0x0
	beq _02022202
	mov r1, #0x1
	bl FUN_0202223C
	mov r0, #0x0
	pop {r3, pc}
_02022202:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}

	thumb_func_start FUN_02022208
FUN_02022208: ; 0x02022208
	push {r3, lr}
	ldrb r2, [r0, #0x1]
	cmp r2, #0x0
	beq _02022220
	ldrh r2, [r0, #0x2]
	ldr r1, _02022238 ; =0x0000FFFF
	cmp r2, r1
	bhs _0202221C
	add r1, r2, #0x1
	strh r1, [r0, #0x2]
_0202221C:
	mov r0, #0x2
	pop {r3, pc}
_02022220:
	cmp r1, #0x0
	beq _0202222E
	mov r1, #0x0
	bl FUN_0202223C
	mov r0, #0x3
	pop {r3, pc}
_0202222E:
	mov r1, #0x0
	bl FUN_0202223C
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_02022238: .word 0x0000FFFF

	thumb_func_start FUN_0202223C
FUN_0202223C: ; 0x0202223C
	strb r1, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2]
	bx lr
