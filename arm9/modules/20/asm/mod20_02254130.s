	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

	thumb_func_start MOD20_02254130
MOD20_02254130: ; 0x02254130
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	add r7, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	ldr r5, [sp, #0x20]
	bne _02254144
	bl GF_AssertFail
_02254144:
	add r0, r5, #0
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254192
	ldr r0, [sp]
	str r5, [r4, #8]
	str r0, [r4, #4]
	str r6, [r4]
	mov r1, #0xe
	ldr r0, [sp, #4]
	str r7, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r5, #0
	mul r1, r7
	bl AllocFromHeap
	str r0, [r4, #0x14]
	cmp r0, #0
	beq _02254188
	mov r6, #0
	cmp r7, #0
	bls _02254192
	add r5, r6, #0
_02254176:
	ldr r0, [r4, #0x14]
	add r0, r0, r5
	bl MOD20_022542E4
	add r6, r6, #1
	add r5, #0xe
	cmp r6, r7
	blo _02254176
	b _02254192
_02254188:
	add r0, r5, #0
	add r1, r4, #0
	bl FreeToHeapExplicit
	mov r4, #0
_02254192:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_02254130

	thumb_func_start MOD20_02254198
MOD20_02254198: ; 0x02254198
	push {r4, lr}
	add r4, r0, #0
	bne _022541A2
	bl GF_AssertFail
_022541A2:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x14]
	bl FreeToHeapExplicit
	ldr r0, [r4, #8]
	add r1, r4, #0
	bl FreeToHeapExplicit
	pop {r4, pc}
	thumb_func_end MOD20_02254198

	thumb_func_start MOD20_022541B4
MOD20_022541B4: ; 0x022541B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl FUN_02020A98
	str r0, [sp, #4]
	cmp r0, #0
	beq _0225420C
	bl FUN_02020AA4
	ldr r1, [r5, #0xc]
	mov r7, #0
	str r0, [sp]
	cmp r1, #0
	bls _02254232
	add r4, r7, #0
	add r6, r7, #0
_022541D6:
	ldr r0, [r5, #0x14]
	add r1, r0, r4
	ldrb r0, [r1, #1]
	strb r0, [r1, #2]
	ldr r0, [r5, #0x14]
	add r0, r0, r4
	ldrb r0, [r0, #1]
	cmp r0, #0
	ldr r0, [r5]
	beq _022541F2
	add r0, r0, r6
	bl FUN_02020A40
	b _022541F8
_022541F2:
	add r0, r0, r6
	bl FUN_02020A6C
_022541F8:
	ldr r1, [r5, #0x14]
	add r7, r7, #1
	add r1, r1, r4
	strb r0, [r1, #1]
	ldr r1, [r5, #0xc]
	add r4, #0xe
	add r6, r6, #4
	cmp r7, r1
	blo _022541D6
	b _02254232
_0225420C:
	ldr r1, [r5, #0xc]
	mov r2, #0
	str r2, [sp]
	cmp r1, #0
	bls _02254232
	add r0, r2, #0
	add r3, r2, #0
_0225421A:
	ldr r1, [r5, #0x14]
	add r2, r2, #1
	add r4, r1, r0
	ldrb r1, [r4, #1]
	strb r1, [r4, #2]
	ldr r1, [r5, #0x14]
	add r1, r1, r0
	strb r3, [r1, #1]
	ldr r1, [r5, #0xc]
	add r0, #0xe
	cmp r2, r1
	blo _0225421A
_02254232:
	mov r6, #0
	cmp r1, #0
	bls _02254278
	ldr r7, _022542A8 ; =MOD20_02254710
	add r4, r6, #0
_0225423C:
	ldr r3, [r5, #0x14]
	ldr r1, [sp, #4]
	add r0, r3, r4
	ldrb r3, [r3, r4]
	ldr r2, [sp]
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	blx r3
	add r1, r0, #0
	ldr r0, [r5, #0x14]
	add r0, r0, r4
	ldrb r2, [r0, #1]
	ldrb r0, [r0, #2]
	cmp r2, r0
	bne _0225425C
	mov r2, #2
_0225425C:
	cmp r1, #0
	bne _02254264
	cmp r2, #2
	beq _0225426E
_02254264:
	ldr r3, [r5, #0x10]
	ldr r4, [r5, #4]
	add r0, r6, #0
	blx r4
	b _02254278
_0225426E:
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	add r4, #0xe
	cmp r6, r0
	blo _0225423C
_02254278:
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	cmp r6, r0
	bhs _022542A2
	mov r0, #0xe
	add r4, r6, #0
	ldr r7, _022542A8 ; =MOD20_02254710
	mul r4, r0
_02254288:
	ldr r3, [r5, #0x14]
	ldr r1, [sp, #4]
	add r0, r3, r4
	ldrb r3, [r3, r4]
	ldr r2, [sp]
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	blx r3
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	add r4, #0xe
	cmp r6, r0
	blo _02254288
_022542A2:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022542A8: .word MOD20_02254710
	thumb_func_end MOD20_022541B4

	thumb_func_start MOD20_022542AC
MOD20_022542AC: ; 0x022542AC
	push {r3, r4}
	ldr r4, [r0, #0x14]
	mov r0, #0xe
	mul r0, r1
	add r1, r4, r0
	lsl r0, r2, #1
	add r0, r1, r0
	strh r3, [r0, #8]
	pop {r3, r4}
	bx lr
	thumb_func_end MOD20_022542AC

	thumb_func_start MOD20_022542C0
MOD20_022542C0: ; 0x022542C0
	ldr r3, [r0, #0x14]
	mov r0, #0xe
	mul r0, r1
	add r0, r3, r0
	strh r2, [r0, #0xc]
	bx lr
	thumb_func_end MOD20_022542C0

	thumb_func_start MOD20_022542CC
MOD20_022542CC: ; 0x022542CC
	add r3, r1, #0
	mov r2, #0xe
	mul r3, r2
	ldr r1, [r0, #0x14]
	mov r2, #0
	add r1, r1, r3
	strh r2, [r1, #4]
	ldr r0, [r0, #0x14]
	mov r1, #4
	strb r1, [r0, r3]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022542CC

	thumb_func_start MOD20_022542E4
MOD20_022542E4: ; 0x022542E4
	mov r2, #0
	strb r2, [r0]
	strb r2, [r0, #1]
	strb r2, [r0, #2]
	strh r2, [r0, #4]
	strh r2, [r0, #6]
	add r3, r0, #0
	add r1, r2, #0
_022542F4:
	add r2, r2, #1
	strh r1, [r3, #8]
	add r3, r3, #2
	cmp r2, #2
	blo _022542F4
	strh r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022542E4

	thumb_func_start MOD20_02254304
MOD20_02254304: ; 0x02254304
	strb r1, [r0]
	mov r1, #0
	strh r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_02254304

	thumb_func_start MOD20_0225430C
MOD20_0225430C: ; 0x0225430C
	strb r1, [r0]
	bx lr
	thumb_func_end MOD20_0225430C

	thumb_func_start MOD20_02254310
MOD20_02254310: ; 0x02254310
	ldrh r2, [r0, #4]
	ldr r1, _02254320 ; =0x0000FFFF
	cmp r2, r1
	bhs _0225431C
	add r1, r2, #1
	strh r1, [r0, #4]
_0225431C:
	bx lr
	nop
_02254320: .word 0x0000FFFF
	thumb_func_end MOD20_02254310

	thumb_func_start MOD20_02254324
MOD20_02254324: ; 0x02254324
	ldrh r3, [r0, #4]
	mov r2, #0
_02254328:
	ldrh r1, [r0, #8]
	cmp r3, r1
	bne _02254332
	add r0, r2, #5
	bx lr
_02254332:
	add r2, r2, #1
	add r0, r0, #2
	cmp r2, #2
	blo _02254328
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02254324

	thumb_func_start MOD20_02254340
MOD20_02254340: ; 0x02254340
	push {r3, lr}
	ldrb r1, [r0, #1]
	cmp r1, #0
	beq _02254356
	cmp r2, #0
	beq _02254356
	mov r1, #1
	bl MOD20_02254304
	mov r0, #1
	pop {r3, pc}
_02254356:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_02254340

	thumb_func_start MOD20_0225435C
MOD20_0225435C: ; 0x0225435C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02254310
	ldrb r0, [r5, #1]
	cmp r0, #0
	beq _0225438A
	add r0, r5, #0
	bl MOD20_02254324
	cmp r0, #0
	bne _022543B8
	ldrh r1, [r5, #0xc]
	cmp r1, #0
	beq _022543B6
	ldrh r0, [r5, #4]
	cmp r0, r1
	blo _022543B6
	mov r0, #0
	strh r0, [r5, #4]
	mov r0, #7
	pop {r3, r4, r5, pc}
_0225438A:
	cmp r4, #0
	beq _0225439A
	add r0, r5, #0
	mov r1, #0
	bl MOD20_02254304
	mov r0, #2
	pop {r3, r4, r5, pc}
_0225439A:
	ldrh r0, [r5, #6]
	cmp r0, #0
	beq _022543AA
	add r0, r5, #0
	mov r1, #2
	bl MOD20_0225430C
	b _022543B6
_022543AA:
	add r0, r5, #0
	mov r1, #0
	bl MOD20_02254304
	mov r0, #3
	pop {r3, r4, r5, pc}
_022543B6:
	mov r0, #0
_022543B8:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_0225435C

	thumb_func_start MOD20_022543BC
MOD20_022543BC: ; 0x022543BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl MOD20_02254310
	ldrh r1, [r5, #4]
	ldrh r0, [r5, #6]
	cmp r1, r0
	bls _022543DA
	add r0, r5, #0
	mov r1, #0
	bl MOD20_02254304
	mov r0, #3
	pop {r3, r4, r5, pc}
_022543DA:
	ldrb r0, [r5, #1]
	cmp r0, #0
	beq _022543F0
	cmp r4, #0
	beq _022543F0
	add r0, r5, #0
	mov r1, #3
	bl MOD20_02254304
	mov r0, #4
	pop {r3, r4, r5, pc}
_022543F0:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022543BC

	thumb_func_start MOD20_022543F4
MOD20_022543F4: ; 0x022543F4
	push {r3, lr}
	ldrb r1, [r0, #1]
	cmp r1, #0
	beq _02254402
	bl MOD20_02254310
	b _02254408
_02254402:
	mov r1, #0
	bl MOD20_02254304
_02254408:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD20_022543F4

	thumb_func_start MOD20_0225440C
MOD20_0225440C: ; 0x0225440C
	push {r3, lr}
	ldrb r1, [r0, #1]
	cmp r1, #0
	bne _0225441A
	mov r1, #0
	bl MOD20_02254304
_0225441A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_0225440C

    .section .rodata

	.global MOD20_02254710
MOD20_02254710: ; 0x02254710
	.word MOD20_02254340, MOD20_0225435C, MOD20_022543BC, MOD20_022543F4
	.word MOD20_0225440C
