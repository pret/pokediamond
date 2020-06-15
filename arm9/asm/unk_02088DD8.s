    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02088DD8
FUN_02088DD8: ; 0x02088DD8
	push {r3, lr}
	mov r1, #0x18
	bl AllocFromHeap
	add r3, r0, #0x0
	mov r2, #0x18
	mov r1, #0x0
_02088DE6:
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _02088DE6
	pop {r3, pc}

	thumb_func_start FUN_02088DF0
FUN_02088DF0: ; 0x02088DF0
	ldr r3, _02088DF4 ; =FreeToHeap
	bx r3
	.balign 4
_02088DF4: .word FreeToHeap

	thumb_func_start FUN_02088DF8
FUN_02088DF8: ; 0x02088DF8
	push {r3-r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x0]
	mov r1, #0x5
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r4, #0x0
	str r0, [sp, #0x4]
	add r7, r4, #0x0
	add r6, sp, #0x10
_02088E34:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl GetMonData
	lsl r1, r4, #0x1
	strh r0, [r6, r1]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02088E34
	ldr r0, [sp, #0x0]
	mov r1, #0x2c
	bl AllocFromHeap
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x2c
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x8]
	add r2, r7, #0x0
	bl LoadWotbl_HandleAlternateForme
	mov r2, #0x0
	mov r12, r2
_02088E70:
	mov r0, r12
	lsl r0, r0, #0x1
	ldrh r5, [r7, r0]
	ldr r6, _02088EF4 ; =0x0000FFFF
	cmp r5, r6
	bne _02088E82
	lsl r0, r2, #0x1
	strh r6, [r4, r0]
	b _02088EE8
_02088E82:
	mov r1, #0xfe
	lsl r1, r1, #0x8
	and r1, r5
	asr r3, r1, #0x9
	ldr r1, [sp, #0x4]
	cmp r3, r1
	bgt _02088EDA
	lsr r1, r6, #0x7
	and r1, r5
	strh r1, [r7, r0]
	ldrh r3, [r7, r0]
	mov r1, #0x0
	add r6, sp, #0x10
_02088E9C:
	lsl r5, r1, #0x1
	ldrh r5, [r6, r5]
	cmp r3, r5
	beq _02088EAE
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x4
	blo _02088E9C
_02088EAE:
	cmp r1, #0x4
	bne _02088EDA
	mov r1, #0x0
	cmp r2, #0x0
	bls _02088ECA
_02088EB8:
	lsl r5, r1, #0x1
	ldrh r5, [r4, r5]
	cmp r5, r3
	beq _02088ECA
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r2
	blo _02088EB8
_02088ECA:
	cmp r1, r2
	bne _02088EDA
	ldrh r1, [r7, r0]
	lsl r0, r2, #0x1
	strh r1, [r4, r0]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
_02088EDA:
	mov r0, r12
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r12, r0
	cmp r0, #0x16
	blo _02088E70
_02088EE8:
	add r0, r7, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_02088EF4: .word 0x0000FFFF

	thumb_func_start FUN_02088EF8
FUN_02088EF8: ; 0x02088EF8
	ldrh r1, [r0, #0x0]
	ldr r0, _02088F08 ; =0x0000FFFF
	cmp r1, r0
	beq _02088F04
	mov r0, #0x1
	bx lr
_02088F04:
	mov r0, #0x0
	bx lr
	.balign 4
_02088F08: .word 0x0000FFFF
