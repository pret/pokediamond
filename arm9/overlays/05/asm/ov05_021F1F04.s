	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F1F04
ov05_021F1F04: ; 0x021F1F04
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	mov r2, #0x41
	add r5, r0, #0
	lsl r2, r2, #2
	str r1, [r5, r2]
	add r1, r4, #0
	bl ov05_021F2E40
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0xa
	bl ov05_021F33B4
	mov r2, #4
	mov r1, #8
	ldr r0, [sp, #0x18]
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	add r3, r1, #0
	str r0, [sp, #8]
	add r0, r5, #0
	bl ov05_021F22E0
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2160
	ldr r1, [sp, #0x20]
	ldr r2, _021F1F50 ; =ov05_021F8B90
	ldr r3, _021F1F54 ; =ov05_021F8B88
	add r0, r5, #0
	bl ov05_021F25A0
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0
_021F1F50: .word ov05_021F8B90
_021F1F54: .word ov05_021F8B88

	thumb_func_start ov05_021F1F58
ov05_021F1F58: ; 0x021F1F58
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021F3458
	add r0, r4, #0
	bl ov05_021F21AC
	add r0, r4, #0
	bl ov05_021F2D48
	bl ov05_021F2E68
	add r0, r4, #0
	bl ov05_021F2368
	pop {r4, pc}

	thumb_func_start ov05_021F1F78
ov05_021F1F78: ; 0x021F1F78
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #0
	add r6, r2, #0
	add r7, r0, #0
	str r1, [r5]
	bl ov05_021F2F3C
	add r1, r6, #0
	str r0, [sp]
	bl ov05_021F28E8
	add r4, r0, #0
	bne _021F1FA2
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	bl ov05_021F211C
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F1FA2:
	sub r0, r4, #3
	cmp r0, #1
	bhi _021F1FB8
	ldr r0, [sp]
	add r1, r7, #0
	add r2, r5, #0
	add r3, r6, #0
	bl ov05_021F32BC
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F1FB8:
	add r0, r7, #0
	add r1, r6, #0
	bl ov05_021F1FE0
	str r0, [r5]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1FC8
ov05_021F1FC8: ; 0x021F1FC8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MapObject_GetGfxID
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F1F78
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F1FE0
ov05_021F1FE0: ; 0x021F1FE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	bl ov05_021F2F3C
	add r4, r0, #0
	bl ov05_021F2D48
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F2AC8
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F21CC
	add r4, r0, #0
	bne _021F200C
	bl GF_AssertFail
_021F200C:
	add r0, r6, #0
	add r1, sp, #0
	bl ov05_021F1E64
	add r0, r7, #0
	add r1, r4, #0
	add r2, sp, #0
	bl ov05_021F2E70
	add r4, r0, #0
	bne _021F2026
	bl GF_AssertFail
_021F2026:
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F202C
ov05_021F202C: ; 0x021F202C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	add r6, r2, #0
	bl sub_0201F744
	mov r0, #0
	str r0, [r4]
	add r0, r5, #0
	bl MapObject_GetManager
	add r1, r5, #0
	add r2, r6, #0
	bl ov05_021F2284
	cmp r0, #0
	bne _021F205C
	add r0, r5, #0
	bl ov05_021F2F3C
	add r1, r6, #0
	bl ov05_021F2240
_021F205C:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2060
ov05_021F2060: ; 0x021F2060
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl ov05_021F2150
	ldr r0, [r4]
	cmp r0, #0
	beq _021F2092
	add r0, r5, #0
	bl MapObject_GetGfxID
	add r6, r0, #0
	bl sub_0205C334
	cmp r0, #1
	bne _021F2088
	add r0, r5, #0
	bl sub_0205C340
	add r6, r0, #0
_021F2088:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl ov05_021F202C
_021F2092:
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F2094
ov05_021F2094: ; 0x021F2094
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r4, r2, #0
	bl ov05_021F2150
	ldr r0, [r5]
	cmp r0, #0
	beq _021F20AE
	bl sub_0201F744
	mov r0, #0
	str r0, [r5]
_021F20AE:
	ldr r0, _021F20D4 ; =0x0000FFFF
	cmp r4, r0
	beq _021F20D2
	add r0, r6, #0
	bl MapObject_GetManager
	add r1, r6, #0
	add r2, r4, #0
	bl ov05_021F2284
	cmp r0, #0
	bne _021F20D2
	add r0, r6, #0
	bl ov05_021F2F3C
	add r1, r4, #0
	bl ov05_021F2240
_021F20D2:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F20D4: .word 0x0000FFFF

	thumb_func_start ov05_021F20D8
ov05_021F20D8: ; 0x021F20D8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl sub_0201F820
	str r0, [r4]
	add r0, r5, #0
	bl sub_0201F844
	strh r0, [r4, #6]
	add r0, r5, #0
	bl sub_0201F880
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F20F8
ov05_021F20F8: ; 0x021F20F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	add r5, r0, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl sub_0201F80C
	ldrh r1, [r4, #6]
	add r0, r5, #0
	bl sub_0201F830
	ldr r1, [r4, #8]
	add r0, r5, #0
	bl sub_0201F86C
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F211C
ov05_021F211C: ; 0x021F211C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r6, r0, #0
	add r5, r1, #0
	bl ov05_021F2F3C
	add r1, r4, #0
	add r7, r0, #0
	bl ov05_021F2460
	cmp r0, #0
	bne _021F2140
	add r0, r6, #0
	add r1, r4, #0
	bl ov05_021F1FE0
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_021F2140:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r5, #0
	add r3, r4, #0
	bl ov05_021F32BC
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2150
ov05_021F2150: ; 0x021F2150
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021F2F3C
	add r1, r4, #0
	bl ov05_021F32F8
	pop {r4, pc}

	thumb_func_start ov05_021F2160
ov05_021F2160: ; 0x021F2160
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x28
	add r7, r0, #0
	mov r0, #4
	mul r1, r6
	bl AllocFromHeap
	add r4, r0, #0
	add r0, r7, #0
	add r0, #0xe4
	str r4, [r0]
	cmp r4, #0
	bne _021F2180
	bl GF_AssertFail
_021F2180:
	mov r0, #4
	lsl r1, r6, #3
	bl AllocFromHeap
	add r5, r0, #0
	add r7, #0xf4
	str r5, [r7]
	cmp r5, #0
	bne _021F2196
	bl GF_AssertFail
_021F2196:
	ldr r0, _021F21A8 ; =0x0000FFFF
_021F2198:
	str r0, [r5]
	str r4, [r5, #4]
	add r5, #8
	add r4, #0x28
	sub r6, r6, #1
	bne _021F2198
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F21A8: .word 0x0000FFFF

	thumb_func_start ov05_021F21AC
ov05_021F21AC: ; 0x021F21AC
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021F2260
	add r1, r4, #0
	add r1, #0xe4
	ldr r1, [r1]
	mov r0, #4
	bl FreeToHeapExplicit
	add r4, #0xf4
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	pop {r4, pc}

	thumb_func_start ov05_021F21CC
ov05_021F21CC: ; 0x021F21CC
	push {r4, r5, r6, lr}
	add r2, r0, #0
	add r2, #0xf4
	ldr r4, [r2]
	ldr r2, [r0, #4]
	add r6, r4, #0
	add r5, r2, #0
_021F21DA:
	ldr r3, [r6]
	cmp r3, r1
	bne _021F21E4
	ldr r0, [r6, #4]
	pop {r4, r5, r6, pc}
_021F21E4:
	add r6, #8
	sub r5, r5, #1
	bne _021F21DA
	ldr r3, _021F2208 ; =0x0000FFFF
_021F21EC:
	ldr r5, [r4]
	cmp r5, r3
	bne _021F21FE
	str r1, [r4]
	ldr r2, [r4, #4]
	bl ov05_021F2ED0
	ldr r0, [r4, #4]
	pop {r4, r5, r6, pc}
_021F21FE:
	add r4, #8
	sub r2, r2, #1
	bne _021F21EC
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F2208: .word 0x0000FFFF

	thumb_func_start ov05_021F220C
ov05_021F220C: ; 0x021F220C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl sub_020583A0
	add r1, r0, #0
	add r1, #0xf4
	ldr r2, [r1]
	ldr r1, [r0, #4]
_021F221E:
	ldr r0, [r2]
	cmp r0, r5
	bne _021F2234
	ldr r3, [r2, #4]
	mov r2, #5
_021F2228:
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	bne _021F2228
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2234:
	add r2, #8
	sub r1, r1, #1
	bne _021F221E
	mov r0, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2240
ov05_021F2240: ; 0x021F2240
	add r2, r0, #0
	add r2, #0xf4
	ldr r3, [r2]
	ldr r2, [r0, #4]
_021F2248:
	ldr r0, [r3]
	cmp r0, r1
	bne _021F2254
	ldr r0, _021F225C ; =0x0000FFFF
	str r0, [r3]
	bx lr
_021F2254:
	add r3, #8
	sub r2, r2, #1
	bne _021F2248
	bx lr
	.balign 4, 0
_021F225C: .word 0x0000FFFF

	thumb_func_start ov05_021F2260
ov05_021F2260: ; 0x021F2260
	push {r3, r4}
	add r1, r0, #0
	add r1, #0xf4
	ldr r4, [r1]
	ldr r1, _021F2280 ; =0x0000FFFF
	ldr r3, [r0, #4]
	add r0, r1, #0
_021F226E:
	ldr r2, [r4]
	cmp r2, r0
	beq _021F2276
	str r1, [r4]
_021F2276:
	add r4, #8
	sub r3, r3, #1
	bne _021F226E
	pop {r3, r4}
	bx lr
	.balign 4, 0
_021F2280: .word 0x0000FFFF

	thumb_func_start ov05_021F2284
ov05_021F2284: ; 0x021F2284
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl MapObjectManager_GetObjectCount
	add r4, r0, #0
	add r0, r5, #0
	bl sub_020583BC
	str r0, [sp]
_021F229A:
	ldr r0, [sp]
	cmp r0, r6
	beq _021F22CE
	bl MapObject_IsInUse
	cmp r0, #1
	bne _021F22CE
	ldr r0, [sp]
	bl MapObject_GetGfxID
	add r5, r0, #0
	bl sub_0205C334
	cmp r0, #1
	bne _021F22C0
	ldr r0, [sp]
	bl sub_0205C340
	add r5, r0, #0
_021F22C0:
	ldr r0, _021F22DC ; =0x0000FFFF
	cmp r5, r0
	beq _021F22CE
	cmp r5, r7
	bne _021F22CE
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F22CE:
	add r0, sp, #0
	bl sub_020583D4
	sub r4, r4, #1
	bne _021F229A
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F22DC: .word 0x0000FFFF

	thumb_func_start ov05_021F22E0
ov05_021F22E0: ; 0x021F22E0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	mov r0, #4
	mov r1, #0x40
	lsl r2, r4, #0xc
	add r3, r4, #0
	bl ov05_021F5990
	add r1, r5, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r5, #0
	bl ov05_021F2614
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021F2D80
	add r0, r5, #0
	sub r1, r4, r6
	bl ov05_021F2D88
	mov r0, #4
	mov r1, #0x41
	lsl r2, r7, #7
	add r3, r7, #0
	bl ov05_021F5990
	add r1, r5, #0
	add r1, #0xfc
	str r0, [r1]
	add r0, r5, #0
	bl ov05_021F2750
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	bl ov05_021F2D90
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	sub r1, r7, r1
	bl ov05_021F2D98
	ldr r0, [sp, #0x1c]
	mov r1, #4
	bl sub_02020E90
	add r1, r0, #0
	add r0, r5, #0
	bl ov05_021F2D64
	add r0, r5, #0
	bl ov05_021F288C
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl ov05_021F2DA0
	ldr r2, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	sub r1, r2, r1
	bl ov05_021F2DA8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F2368
ov05_021F2368: ; 0x021F2368
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl ov05_021F59EC
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	bl ov05_021F59EC
	add r0, r4, #0
	bl ov05_021F2D6C
	bl sub_02020ED4
	pop {r4, pc}
	.balign 4, 0
_021F238C:
	ldr r3, [r2]
	cmp r3, r0
	bne _021F2396
	add r0, r2, #0
	bx lr
_021F2396:
	add r2, #8
	ldr r3, [r2]
	cmp r3, r1
	bne _021F238C
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F23A4
ov05_021F23A4: ; 0x021F23A4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	add r7, r3, #0
	bl ov05_021F5AA4
	cmp r0, #1
	bne _021F23BE
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F23BE:
	ldr r2, [sp, #0x18]
	add r0, r4, #0
	add r1, r7, #0
	bl _021F238C
	add r7, r0, #0
	bne _021F23D0
	bl GF_AssertFail
_021F23D0:
	mov r0, #0x41
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl sub_020583F4
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r3, [r7, #4]
	add r0, r6, #0
	add r1, r4, #0
	bl ov05_021F5AE4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F23F0
ov05_021F23F0: ; 0x021F23F0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0xf0
	add r4, r2, #0
	add r6, r1, #0
	ldr r0, [r0]
	add r1, r4, #0
	add r7, r3, #0
	bl sub_02020EF8
	cmp r0, #0
	bne _021F240C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F240C:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F3084
	cmp r0, #0
	beq _021F241C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F241C:
	ldr r1, _021F2448 ; =0x0000FFFF
	add r0, r4, #0
	add r2, r7, #0
	bl _021F238C
	add r2, r0, #0
	bne _021F242E
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_021F242E:
	ldr r2, [r2, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r6, #0
	bl ov05_021F2FD0
	cmp r0, #1
	bne _021F2442
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F2442:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F2448: .word 0x0000FFFF

	thumb_func_start ov05_021F244C
ov05_021F244C: ; 0x021F244C
	push {r3, lr}
	ldr r3, _021F245C ; =ov05_021FA0AC
	add r2, r1, #0
	mov r1, #0
	bl ov05_021F23F0
	pop {r3, pc}
	nop
_021F245C: .word ov05_021FA0AC

	thumb_func_start ov05_021F2460
ov05_021F2460: ; 0x021F2460
	push {r3, lr}
	ldr r3, _021F2470 ; =ov05_021FA0AC
	add r2, r1, #0
	mov r1, #1
	bl ov05_021F23F0
	pop {r3, pc}
	nop
_021F2470: .word ov05_021FA0AC

	thumb_func_start ov05_021F2474
ov05_021F2474: ; 0x021F2474
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _021F2494 ; =0x0000FFFF
	cmp r1, r0
	beq _021F2492
	add r6, r0, #0
_021F2484:
	add r0, r5, #0
	bl ov05_021F244C
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, r6
	bne _021F2484
_021F2492:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F2494: .word 0x0000FFFF

	thumb_func_start ov05_021F2498
ov05_021F2498: ; 0x021F2498
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D54
	ldr r0, _021F24C0 ; =ov05_021F9094
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xf8
	ldr r1, [r1]
	ldr r3, _021F24C4 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl ov05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2628
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F24C0: .word ov05_021F9094
_021F24C4: .word 0x0000FFFF

	thumb_func_start ov05_021F24C8
ov05_021F24C8: ; 0x021F24C8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D54
	ldr r0, _021F24F0 ; =ov05_021F9094
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xf8
	ldr r1, [r1]
	ldr r3, _021F24F4 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl ov05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2670
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F24F0: .word ov05_021F9094
_021F24F4: .word 0x0000FFFF

	thumb_func_start ov05_021F24F8
ov05_021F24F8: ; 0x021F24F8
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _021F2518 ; =0x0000FFFF
	cmp r1, r0
	beq _021F2516
	add r6, r0, #0
_021F2508:
	add r0, r5, #0
	bl ov05_021F2498
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, r6
	bne _021F2508
_021F2516:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F2518: .word 0x0000FFFF

	thumb_func_start ov05_021F251C
ov05_021F251C: ; 0x021F251C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D5C
	ldr r0, _021F2544 ; =ov05_021F90E4
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xfc
	ldr r1, [r1]
	ldr r3, _021F2548 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl ov05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2764
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F2544: .word ov05_021F90E4
_021F2548: .word 0x0000FFFF

	thumb_func_start ov05_021F254C
ov05_021F254C: ; 0x021F254C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D5C
	ldr r0, _021F2574 ; =ov05_021F90E4
	add r1, r5, #0
	str r0, [sp]
	add r1, #0xfc
	ldr r1, [r1]
	ldr r3, _021F2578 ; =0x0000FFFF
	add r0, r5, #0
	add r2, r4, #0
	bl ov05_021F23A4
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F27AC
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021F2574: .word ov05_021F90E4
_021F2578: .word 0x0000FFFF

	thumb_func_start ov05_021F257C
ov05_021F257C: ; 0x021F257C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, [r4]
	ldr r0, _021F259C ; =0x0000FFFF
	cmp r1, r0
	beq _021F259A
	add r6, r0, #0
_021F258C:
	add r0, r5, #0
	bl ov05_021F251C
	add r4, r4, #4
	ldr r1, [r4]
	cmp r1, r6
	bne _021F258C
_021F259A:
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F259C: .word 0x0000FFFF

	thumb_func_start ov05_021F25A0
ov05_021F25A0: ; 0x021F25A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	bl ov05_021F2474
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F24F8
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021F257C
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F25C0:
	stmia r0!, {r1}
	sub r2, r2, #1
	bne _021F25C0
	bx lr

	thumb_func_start ov05_021F25C8
ov05_021F25C8: ; 0x021F25C8
	push {r3, r4}
_021F25CA:
	ldr r4, [r0]
	cmp r4, r2
	bne _021F25D8
	str r1, [r0]
	mov r0, #1
	pop {r3, r4}
	bx lr
_021F25D8:
	add r0, r0, #4
	sub r3, r3, #1
	bne _021F25CA
	mov r0, #0
	pop {r3, r4}
	bx lr
_021F25E4:
	ldr r3, [r0]
	cmp r3, r1
	bne _021F25EE
	mov r0, #1
	bx lr
_021F25EE:
	add r0, r0, #4
	sub r2, r2, #1
	bne _021F25E4
	mov r0, #0
	bx lr

	thumb_func_start ov05_021F25F8
ov05_021F25F8: ; 0x021F25F8
	push {r3, r4}
_021F25FA:
	ldr r4, [r0]
	cmp r4, r1
	bne _021F2608
	str r2, [r0]
	mov r0, #1
	pop {r3, r4}
	bx lr
_021F2608:
	add r0, r0, #4
	sub r3, r3, #1
	bne _021F25FA
	mov r0, #0
	pop {r3, r4}
	bx lr

	thumb_func_start ov05_021F2614
ov05_021F2614: ; 0x021F2614
	push {r3, lr}
	bl ov05_021F2D78
	ldr r1, _021F2624 ; =0x0000FFFF
	mov r2, #8
	bl _021F25C0
	pop {r3, pc}
	.balign 4, 0
_021F2624: .word 0x0000FFFF

	thumb_func_start ov05_021F2628
ov05_021F2628: ; 0x021F2628
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D84
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D78
	ldr r2, _021F2650 ; =0x0000FFFF
	add r1, r4, #0
	add r3, r6, #0
	bl ov05_021F25C8
	cmp r0, #0
	bne _021F264C
	bl GF_AssertFail
_021F264C:
	pop {r4, r5, r6, pc}
	nop
_021F2650: .word 0x0000FFFF

	thumb_func_start ov05_021F2654
ov05_021F2654: ; 0x021F2654
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D84
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D78
	add r1, r4, #0
	add r2, r6, #0
	bl _021F25E4
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F2670
ov05_021F2670: ; 0x021F2670
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D78
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D84
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2D8C
	add r3, r0, #0
	ldr r2, _021F26A0 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl ov05_021F25C8
	cmp r0, #0
	bne _021F269E
	bl GF_AssertFail
_021F269E:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F26A0: .word 0x0000FFFF

	thumb_func_start ov05_021F26A4
ov05_021F26A4: ; 0x021F26A4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D78
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D84
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2D8C
	add r2, r0, #0
	add r0, r6, r4
	add r1, r7, #0
	bl _021F25E4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F26CC
ov05_021F26CC: ; 0x021F26CC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D78
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D84
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2D8C
	add r3, r0, #0
	ldr r2, _021F26F4 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl ov05_021F25F8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F26F4: .word 0x0000FFFF

	thumb_func_start ov05_021F26F8
ov05_021F26F8: ; 0x021F26F8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	add r0, r6, #0
	bl ov05_021F2D54
	add r0, r6, #0
	bl ov05_021F2D78
	add r4, r0, #0
	add r0, r6, #0
	bl ov05_021F2D84
	lsl r0, r0, #2
	add r5, r4, r0
	add r0, r6, #0
	bl ov05_021F2D8C
	add r4, r0, #0
_021F271E:
	ldr r1, [r5]
	ldr r0, _021F274C ; =0x0000FFFF
	cmp r1, r0
	beq _021F2742
	add r0, r7, #0
	mov r2, #0
	bl ov05_021F2B70
	cmp r0, #0
	bne _021F2742
	add r0, r6, #0
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [r5]
	bl ov05_021F5A74
	ldr r0, _021F274C ; =0x0000FFFF
	str r0, [r5]
_021F2742:
	add r5, r5, #4
	sub r4, r4, #1
	bne _021F271E
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F274C: .word 0x0000FFFF

	thumb_func_start ov05_021F2750
ov05_021F2750: ; 0x021F2750
	push {r3, lr}
	bl ov05_021F2D7C
	ldr r1, _021F2760 ; =0x0000FFFF
	mov r2, #8
	bl _021F25C0
	pop {r3, pc}
	.balign 4, 0
_021F2760: .word 0x0000FFFF

	thumb_func_start ov05_021F2764
ov05_021F2764: ; 0x021F2764
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D94
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D7C
	ldr r2, _021F278C ; =0x0000FFFF
	add r1, r4, #0
	add r3, r6, #0
	bl ov05_021F25C8
	cmp r0, #0
	bne _021F2788
	bl GF_AssertFail
_021F2788:
	pop {r4, r5, r6, pc}
	nop
_021F278C: .word 0x0000FFFF

	thumb_func_start ov05_021F2790
ov05_021F2790: ; 0x021F2790
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2D94
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D7C
	add r1, r4, #0
	add r2, r6, #0
	bl _021F25E4
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F27AC
ov05_021F27AC: ; 0x021F27AC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D7C
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D94
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2D9C
	add r3, r0, #0
	ldr r2, _021F27DC ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl ov05_021F25C8
	cmp r0, #0
	bne _021F27DA
	bl GF_AssertFail
_021F27DA:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F27DC: .word 0x0000FFFF

	thumb_func_start ov05_021F27E0
ov05_021F27E0: ; 0x021F27E0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D7C
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D94
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2D9C
	add r2, r0, #0
	add r0, r6, r4
	add r1, r7, #0
	bl _021F25E4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2808
ov05_021F2808: ; 0x021F2808
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D7C
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D94
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2D9C
	add r3, r0, #0
	ldr r2, _021F2830 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl ov05_021F25F8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2830: .word 0x0000FFFF

	thumb_func_start ov05_021F2834
ov05_021F2834: ; 0x021F2834
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r7, r0, #0
	add r0, r6, #0
	bl ov05_021F2D5C
	add r0, r6, #0
	bl ov05_021F2D7C
	add r4, r0, #0
	add r0, r6, #0
	bl ov05_021F2D94
	lsl r0, r0, #2
	add r5, r4, r0
	add r0, r6, #0
	bl ov05_021F2D9C
	add r4, r0, #0
_021F285A:
	ldr r1, [r5]
	ldr r0, _021F2888 ; =0x0000FFFF
	cmp r1, r0
	beq _021F287E
	add r0, r7, #0
	mov r2, #0
	bl ov05_021F2BF8
	cmp r0, #0
	bne _021F287E
	add r0, r6, #0
	add r0, #0xfc
	ldr r0, [r0]
	ldr r1, [r5]
	bl ov05_021F5A74
	ldr r0, _021F2888 ; =0x0000FFFF
	str r0, [r5]
_021F287E:
	add r5, r5, #4
	sub r4, r4, #1
	bne _021F285A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F2888: .word 0x0000FFFF

	thumb_func_start ov05_021F288C
ov05_021F288C: ; 0x021F288C
	push {r3, lr}
	bl ov05_021F2D74
	ldr r1, _021F289C ; =0x0000FFFF
	mov r2, #0x20
	bl _021F25C0
	pop {r3, pc}
	.balign 4, 0
_021F289C: .word 0x0000FFFF

	thumb_func_start ov05_021F28A0
ov05_021F28A0: ; 0x021F28A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2DA4
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D74
	ldr r2, _021F28C8 ; =0x0000FFFF
	add r1, r4, #0
	add r3, r6, #0
	bl ov05_021F25C8
	cmp r0, #0
	bne _021F28C4
	bl GF_AssertFail
_021F28C4:
	pop {r4, r5, r6, pc}
	nop
_021F28C8: .word 0x0000FFFF

	thumb_func_start ov05_021F28CC
ov05_021F28CC: ; 0x021F28CC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2DA4
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2D74
	add r1, r4, #0
	add r2, r6, #0
	bl _021F25E4
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F28E8
ov05_021F28E8: ; 0x021F28E8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F28CC
	cmp r0, #1
	bne _021F28FA
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F28FA:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F29E0
	cmp r0, #1
	bne _021F290A
	mov r0, #2
	pop {r3, r4, r5, pc}
_021F290A:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F3084
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2914
ov05_021F2914: ; 0x021F2914
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D74
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2DA4
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2DAC
	add r3, r0, #0
	ldr r2, _021F2944 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl ov05_021F25C8
	cmp r0, #0
	bne _021F2942
	bl GF_AssertFail
_021F2942:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2944: .word 0x0000FFFF

	thumb_func_start ov05_021F2948
ov05_021F2948: ; 0x021F2948
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D74
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2DA4
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2DAC
	add r3, r0, #0
	ldr r2, _021F2970 ; =0x0000FFFF
	add r0, r6, r4
	add r1, r7, #0
	bl ov05_021F25F8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2970: .word 0x0000FFFF

	thumb_func_start ov05_021F2974
ov05_021F2974: ; 0x021F2974
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	str r0, [sp]
	add r0, r6, #0
	bl ov05_021F2D6C
	str r0, [sp, #4]
	add r0, r6, #0
	bl ov05_021F2D74
	add r4, r0, #0
	add r0, r6, #0
	bl ov05_021F2DA4
	lsl r0, r0, #2
	add r5, r4, r0
	add r0, r6, #0
	bl ov05_021F2DAC
	add r7, r0, #0
_021F299E:
	ldr r4, [r5]
	ldr r0, _021F29DC ; =0x0000FFFF
	cmp r4, r0
	beq _021F29D0
	ldr r0, [sp]
	add r1, r4, #0
	mov r2, #0
	bl ov05_021F2B10
	cmp r0, #0
	bne _021F29D0
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl sub_02020FF0
	add r0, r6, #0
	add r1, r4, #0
	bl ov05_021F3050
	add r0, r6, #0
	add r1, r4, #0
	bl ov05_021F3204
	ldr r0, _021F29DC ; =0x0000FFFF
	str r0, [r5]
_021F29D0:
	add r5, r5, #4
	sub r7, r7, #1
	bne _021F299E
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F29DC: .word 0x0000FFFF

	thumb_func_start ov05_021F29E0
ov05_021F29E0: ; 0x021F29E0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	bl ov05_021F2D74
	add r6, r0, #0
	add r0, r5, #0
	bl ov05_021F2DA4
	lsl r4, r0, #2
	add r0, r5, #0
	bl ov05_021F2DAC
	add r2, r0, #0
	add r0, r6, r4
	add r1, r7, #0
	bl _021F25E4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2A08
ov05_021F2A08: ; 0x021F2A08
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F28CC
	cmp r0, #1
	bne _021F2A1A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F2A1A:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F29E0
	cmp r0, #1
	bne _021F2A2A
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2A2A:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2A30
ov05_021F2A30: ; 0x021F2A30
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2654
	cmp r0, #1
	bne _021F2A42
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F2A42:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F26A4
	cmp r0, #1
	bne _021F2A52
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2A52:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2A58
ov05_021F2A58: ; 0x021F2A58
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2790
	cmp r0, #1
	bne _021F2A6A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021F2A6A:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F27E0
	cmp r0, #1
	bne _021F2A7A
	mov r0, #1
	pop {r3, r4, r5, pc}
_021F2A7A:
	mov r0, #2
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2A80
ov05_021F2A80: ; 0x021F2A80
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F28E8
	cmp r0, #0
	bne _021F2A96
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2460
_021F2A96:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2A98
ov05_021F2A98: ; 0x021F2A98
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2A30
	cmp r0, #2
	bne _021F2AAE
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F24C8
_021F2AAE:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2AB0
ov05_021F2AB0: ; 0x021F2AB0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2A58
	cmp r0, #2
	bne _021F2AC6
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F254C
_021F2AC6:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2AC8
ov05_021F2AC8: ; 0x021F2AC8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl ov05_021F2DE8
	add r1, r0, #0
	add r0, r5, #0
	bl ov05_021F2A98
	add r0, r4, #0
	bl ov05_021F2DF4
	add r1, r0, #0
	add r0, r5, #0
	bl ov05_021F2AB0
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2A80
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2AF4
ov05_021F2AF4: ; 0x021F2AF4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F26F8
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2834
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2974
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2B10
ov05_021F2B10: ; 0x021F2B10
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r2, #0
	str r1, [sp, #4]
	str r1, [sp]
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	add r7, r0, #0
	bl sub_020580F4
	cmp r0, #1
	bne _021F2B6A
_021F2B2E:
	cmp r5, #0
	beq _021F2B38
	ldr r0, [sp]
	cmp r5, r0
	beq _021F2B5A
_021F2B38:
	ldr r0, [sp]
	bl MapObject_GetGfxID
	add r4, r0, #0
	bl sub_0205C334
	cmp r0, #1
	bne _021F2B50
	ldr r0, [sp]
	bl sub_0205C340
	add r4, r0, #0
_021F2B50:
	cmp r4, r6
	bne _021F2B5A
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F2B5A:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	bl sub_020580F4
	cmp r0, #1
	beq _021F2B2E
_021F2B6A:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F2B70
ov05_021F2B70: ; 0x021F2B70
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r2, #0
	str r1, [sp, #4]
	str r1, [sp]
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	add r7, r0, #0
	bl sub_020580F4
	cmp r0, #1
	bne _021F2BEE
_021F2B8E:
	cmp r5, #0
	beq _021F2B98
	ldr r0, [sp]
	cmp r5, r0
	beq _021F2BDE
_021F2B98:
	ldr r0, [sp]
	bl MapObject_GetGfxID
	add r4, r0, #0
	ldr r0, _021F2BF4 ; =0x0000FFFF
	cmp r4, r0
	beq _021F2BDE
	ldr r0, [sp]
	bl ov05_021F1DC8
	ldr r0, [r0, #4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _021F2BDE
	add r0, r4, #0
	bl sub_0205C334
	cmp r0, #1
	bne _021F2BC8
	ldr r0, [sp]
	bl sub_0205C340
	add r4, r0, #0
_021F2BC8:
	ldr r0, _021F2BF4 ; =0x0000FFFF
	cmp r4, r0
	beq _021F2BDE
	add r0, r4, #0
	bl ov05_021F2DE8
	cmp r6, r0
	bne _021F2BDE
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F2BDE:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	bl sub_020580F4
	cmp r0, #1
	beq _021F2B8E
_021F2BEE:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021F2BF4: .word 0x0000FFFF

	thumb_func_start ov05_021F2BF8
ov05_021F2BF8: ; 0x021F2BF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #0
	add r5, r2, #0
	str r1, [sp, #4]
	str r1, [sp]
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	add r7, r0, #0
	bl sub_020580F4
	cmp r0, #1
	bne _021F2C74
_021F2C16:
	cmp r5, #0
	beq _021F2C20
	ldr r0, [sp]
	cmp r0, r5
	beq _021F2C64
_021F2C20:
	ldr r0, _021F2C7C ; =0x0000FFFF
	cmp r4, r0
	beq _021F2C64
	ldr r0, [sp]
	bl ov05_021F1DC8
	ldr r0, [r0, #4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _021F2C64
	ldr r0, [sp]
	bl MapObject_GetGfxID
	add r4, r0, #0
	bl sub_0205C334
	cmp r0, #1
	bne _021F2C4E
	ldr r0, [sp]
	bl sub_0205C340
	add r4, r0, #0
_021F2C4E:
	ldr r0, _021F2C7C ; =0x0000FFFF
	cmp r4, r0
	beq _021F2C64
	add r0, r4, #0
	bl ov05_021F2DF4
	cmp r6, r0
	bne _021F2C64
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021F2C64:
	add r0, r7, #0
	add r1, sp, #0
	add r2, sp, #4
	mov r3, #1
	bl sub_020580F4
	cmp r0, #1
	beq _021F2C16
_021F2C74:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021F2C7C: .word 0x0000FFFF

	thumb_func_start ov05_021F2C80
ov05_021F2C80: ; 0x021F2C80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	add r7, r2, #0
	bl sub_020583A0
	add r4, r0, #0
	add r0, r5, #0
	bl ov05_021F2DE8
	str r0, [sp]
	ldr r1, [sp]
	add r0, r4, #0
	bl ov05_021F2A30
	cmp r0, #1
	bne _021F2CC6
	ldr r1, [sp]
	add r0, r6, #0
	add r2, r7, #0
	bl ov05_021F2B70
	cmp r0, #0
	bne _021F2CC6
	add r0, r4, #0
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp]
	bl ov05_021F5A74
	ldr r1, [sp]
	add r0, r4, #0
	bl ov05_021F26CC
_021F2CC6:
	add r0, r5, #0
	bl ov05_021F2DF4
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov05_021F2A58
	cmp r0, #1
	bne _021F2CFC
	ldr r1, [sp, #4]
	add r0, r6, #0
	add r2, r7, #0
	bl ov05_021F2BF8
	cmp r0, #0
	bne _021F2CFC
	add r0, r4, #0
	add r0, #0xfc
	ldr r0, [r0]
	ldr r1, [sp, #4]
	bl ov05_021F5A74
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl ov05_021F2808
_021F2CFC:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F2A08
	cmp r0, #1
	bne _021F2D3A
	add r0, r6, #0
	add r1, r5, #0
	add r2, r7, #0
	bl ov05_021F2B10
	cmp r0, #0
	bne _021F2D3A
	add r0, r4, #0
	bl ov05_021F2D6C
	add r1, r5, #0
	bl sub_02020FF0
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F2948
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F3050
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F3204
_021F2D3A:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2D40
ov05_021F2D40: ; 0x021F2D40
	add r0, #0xe0
	str r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F2D48
ov05_021F2D48: ; 0x021F2D48
	add r0, #0xe0
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F2D50
ov05_021F2D50: ; 0x021F2D50
	str r1, [r0, #4]
	bx lr

	thumb_func_start ov05_021F2D54
ov05_021F2D54: ; 0x021F2D54
	add r0, #0xe8
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F2D5C
ov05_021F2D5C: ; 0x021F2D5C
	add r0, #0xec
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F2D64
ov05_021F2D64: ; 0x021F2D64
	add r0, #0xf0
	str r1, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F2D6C
ov05_021F2D6C: ; 0x021F2D6C
	add r0, #0xf0
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F2D74
ov05_021F2D74: ; 0x021F2D74
	add r0, #0x60
	bx lr

	thumb_func_start ov05_021F2D78
ov05_021F2D78: ; 0x021F2D78
	add r0, #0x20
	bx lr

	thumb_func_start ov05_021F2D7C
ov05_021F2D7C: ; 0x021F2D7C
	add r0, #0x40
	bx lr

	thumb_func_start ov05_021F2D80
ov05_021F2D80: ; 0x021F2D80
	str r1, [r0, #8]
	bx lr

	thumb_func_start ov05_021F2D84
ov05_021F2D84: ; 0x021F2D84
	ldr r0, [r0, #8]
	bx lr

	thumb_func_start ov05_021F2D88
ov05_021F2D88: ; 0x021F2D88
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021F2D8C
ov05_021F2D8C: ; 0x021F2D8C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021F2D90
ov05_021F2D90: ; 0x021F2D90
	str r1, [r0, #0x10]
	bx lr

	thumb_func_start ov05_021F2D94
ov05_021F2D94: ; 0x021F2D94
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start ov05_021F2D98
ov05_021F2D98: ; 0x021F2D98
	str r1, [r0, #0x14]
	bx lr

	thumb_func_start ov05_021F2D9C
ov05_021F2D9C: ; 0x021F2D9C
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start ov05_021F2DA0
ov05_021F2DA0: ; 0x021F2DA0
	str r1, [r0, #0x18]
	bx lr

	thumb_func_start ov05_021F2DA4
ov05_021F2DA4: ; 0x021F2DA4
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start ov05_021F2DA8
ov05_021F2DA8: ; 0x021F2DA8
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start ov05_021F2DAC
ov05_021F2DAC: ; 0x021F2DAC
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start ov05_021F2DB0
ov05_021F2DB0: ; 0x021F2DB0
	mov r3, #0x41
	lsl r3, r3, #2
	ldr r0, [r0, r3]
	ldr r3, _021F2DBC ; =ov05_021F1E2C
	bx r3
	nop
_021F2DBC: .word ov05_021F1E2C

	thumb_func_start ov05_021F2DC0
ov05_021F2DC0: ; 0x021F2DC0
	push {r3, lr}
	ldr r3, _021F2DE0 ; =ov05_021FAC6C
	ldr r1, _021F2DE4 ; =0x0000FFFF
_021F2DC6:
	ldr r2, [r3]
	cmp r2, r0
	bne _021F2DD0
	add r0, r3, #0
	pop {r3, pc}
_021F2DD0:
	add r3, #0x10
	ldr r2, [r3]
	cmp r2, r1
	bne _021F2DC6
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0
_021F2DE0: .word ov05_021FAC6C
_021F2DE4: .word 0x0000FFFF

	thumb_func_start ov05_021F2DE8
ov05_021F2DE8: ; 0x021F2DE8
	push {r3, lr}
	bl ov05_021F2DC0
	ldr r0, [r0, #4]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2DF4
ov05_021F2DF4: ; 0x021F2DF4
	push {r3, lr}
	bl ov05_021F2DC0
	ldr r0, [r0, #8]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2E00
ov05_021F2E00: ; 0x021F2E00
	push {r3, lr}
	bl ov05_021F2DC0
	ldr r0, [r0, #0xc]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2E0C
ov05_021F2E0C: ; 0x021F2E0C
	push {r3, lr}
	cmp r1, #1
	bne _021F2E1C
	mov r1, #1
	lsl r1, r1, #0x16
	bl MapObject_SetFlagsBits
	pop {r3, pc}
_021F2E1C:
	mov r1, #1
	lsl r1, r1, #0x16
	bl MapObject_ClearFlagsBits
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2E28
ov05_021F2E28: ; 0x021F2E28
	push {r3, lr}
	mov r1, #1
	lsl r1, r1, #0x16
	bl MapObject_GetFlagsBits
	cmp r0, #0
	beq _021F2E3A
	mov r0, #1
	pop {r3, pc}
_021F2E3A:
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2E40
ov05_021F2E40: ; 0x021F2E40
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #4
	add r4, r1, #0
	str r0, [sp, #4]
	add r0, sp, #0
	str r4, [sp]
	bl sub_0201F1B4
	add r1, r0, #0
	add r0, r5, #0
	bl ov05_021F2D40
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2D50
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021F2E68
ov05_021F2E68: ; 0x021F2E68
	ldr r3, _021F2E6C ; =sub_0201F23C
	bx r3
	.balign 4, 0
_021F2E6C: .word sub_0201F23C

	thumb_func_start ov05_021F2E70
ov05_021F2E70: ; 0x021F2E70
	push {r4, lr}
	sub sp, #0x20
	str r0, [sp]
	str r1, [sp, #4]
	ldmia r2!, {r0, r1}
	add r3, sp, #8
	stmia r3!, {r0, r1}
	ldr r0, [r2]
	add r2, sp, #0x14
	str r0, [r3]
	ldr r3, _021F2ECC ; =0ov05_021FC550
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, sp, #0
	bl sub_0201F6E8
	add r4, r0, #0
	beq _021F2EC4
	mov r1, #0
	bl sub_0201F80C
	add r0, r4, #0
	mov r1, #0
	bl sub_0201F830
	add r0, r4, #0
	mov r1, #0
	bl sub_0201F890
	add r0, r4, #0
	bl sub_0201F8E0
	mov r1, #1
	bl NNS_G3dMdlSetMdlFogEnableFlagAll
	add r0, r4, #0
	bl sub_0201F8E0
	bl ov05_021DB5EC
_021F2EC4:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	nop
_021F2ECC: .word ov05_021FC550

	thumb_func_start ov05_021F2ED0
ov05_021F2ED0: ; 0x021F2ED0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r0, r5, #0
	add r4, r2, #0
	bl ov05_021F2DE8
	add r1, r0, #0
	add r0, r6, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl ov05_021F5A90
	str r0, [r4]
	add r0, r5, #0
	bl ov05_021F2DF4
	add r1, r0, #0
	add r0, r6, #0
	add r0, #0xfc
	ldr r0, [r0]
	bl ov05_021F5A90
	add r1, r4, #0
	add r1, #0xc
	bl sub_0202227C
	add r0, r6, #0
	bl ov05_021F2D6C
	add r1, r5, #0
	bl sub_02021050
	add r6, r0, #0
	bl sub_020210AC
	str r0, [r4, #4]
	add r0, r6, #0
	bl sub_020211AC
	str r0, [r4, #0x1c]
	add r0, r6, #0
	bl sub_020211BC
	str r0, [r4, #0x20]
	add r0, r6, #0
	bl sub_020211CC
	str r0, [r4, #0x24]
	add r0, r5, #0
	bl ov05_021F2E00
	str r0, [r4, #8]
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F2F3C
ov05_021F2F3C: ; 0x021F2F3C
	push {r3, lr}
	bl MapObject_GetManager
	bl sub_020583A0
	pop {r3, pc}

	thumb_func_start ov05_021F2F48
ov05_021F2F48: ; 0x021F2F48
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	bl ov05_021F1E64
	mov r0, #6
	ldr r1, [sp, #8]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl sub_0201F7C8
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov05_021F2F6C
ov05_021F2F6C: ; 0x021F2F6C
	push {r4, r5, r6, lr}
	mov r4, #1
	add r6, r1, #0
	lsl r1, r4, #9
	add r5, r0, #0
	bl MapObject_TestFlagsBits
	cmp r0, #1
	bne _021F2F80
	mov r4, #0
_021F2F80:
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl MapObject_TestFlagsBits
	cmp r0, #1
	bne _021F2F9E
	mov r1, #2
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl MapObject_TestFlagsBits
	cmp r0, #0
	bne _021F2F9E
	mov r4, #0
_021F2F9E:
	lsl r1, r4, #0x18
	add r0, r6, #0
	lsr r1, r1, #0x18
	bl sub_0201F80C
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F2FAC
ov05_021F2FAC: ; 0x021F2FAC
	lsl r1, r0, #2
	ldr r0, _021F2FB4 ; =ov05_021FC55C
	ldr r0, [r0, r1]
	bx lr
	.balign 4, 0
_021F2FB4: .word ov05_021FC55C

	thumb_func_start ov05_021F2FB8
ov05_021F2FB8: ; 0x021F2FB8
	lsl r1, r0, #2
	ldr r0, _021F2FC0 ; =ov05_021FC56C
	ldr r0, [r0, r1]
	bx lr
	.balign 4, 0
_021F2FC0: .word ov05_021FC56C

	thumb_func_start ov05_021F2FC4
ov05_021F2FC4: ; 0x021F2FC4
	lsl r1, r0, #2
	ldr r0, _021F2FCC ; =ov05_021FC57C
	ldr r0, [r0, r1]
	bx lr
	.balign 4, 0
_021F2FCC: .word ov05_021FC57C

	thumb_func_start ov05_021F2FD0
ov05_021F2FD0: ; 0x021F2FD0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r4, [r5, r0]
	mov r0, #4
	add r6, r1, #0
	ldrsh r1, [r4, r0]
	mov r0, #2
	ldrsh r0, [r4, r0]
	add r7, r2, #0
	str r3, [sp]
	cmp r1, r0
	bge _021F2FFA
	add r0, r5, #0
	add r0, #0xe0
	ldr r0, [r0]
	bl sub_0201F2C0
	cmp r0, #1
	bne _021F302C
_021F2FFA:
	mov r2, #0
	ldrsh r3, [r4, r2]
	ldr r0, [r4, #0xc]
	cmp r3, #0
	ble _021F3024
_021F3004:
	ldr r1, [r0, #0xc]
	cmp r1, #0
	bne _021F301C
	add r5, #0xf0
	ldr r1, [r5]
	str r1, [r0, #0xc]
	ldr r1, [sp]
	str r1, [r0, #8]
	str r6, [r0, #4]
	str r7, [r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F301C:
	add r2, r2, #1
	add r0, #0x10
	cmp r2, r3
	blt _021F3004
_021F3024:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021F302C:
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	bl ov05_021F2DB0
	add r2, r0, #0
	ldr r3, [sp]
	add r0, r5, #0
	add r1, r6, #0
	bl ov05_021F317C
	mov r0, #4
	ldrsh r0, [r4, r0]
	add r0, r0, #1
	strh r0, [r4, #4]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F3050
ov05_021F3050: ; 0x021F3050
	push {r3, r4}
	mov r2, #1
	lsl r2, r2, #8
	ldr r0, [r0, r2]
	mov r3, #0
	ldrsh r4, [r0, r3]
	ldr r2, [r0, #0xc]
	cmp r4, #0
	ble _021F307E
_021F3062:
	ldr r0, [r2, #4]
	cmp r0, r1
	bne _021F3076
	ldr r0, [r2, #0xc]
	cmp r0, #0
	beq _021F3076
	mov r0, #0
	str r0, [r2, #0xc]
	pop {r3, r4}
	bx lr
_021F3076:
	add r3, r3, #1
	add r2, #0x10
	cmp r3, r4
	blt _021F3062
_021F307E:
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F3084
ov05_021F3084: ; 0x021F3084
	push {r3, r4}
	mov r2, #1
	lsl r2, r2, #8
	ldr r0, [r0, r2]
	mov r3, #0
	ldrsh r4, [r0, r3]
	ldr r2, [r0, #0xc]
	cmp r4, #0
	ble _021F30BC
_021F3096:
	ldr r0, [r2, #4]
	cmp r0, r1
	bne _021F30B4
	ldr r0, [r2, #0xc]
	cmp r0, #0
	beq _021F30B4
	ldr r0, [r2, #8]
	cmp r0, #0
	bne _021F30AE
	mov r0, #3
	pop {r3, r4}
	bx lr
_021F30AE:
	mov r0, #4
	pop {r3, r4}
	bx lr
_021F30B4:
	add r3, r3, #1
	add r2, #0x10
	cmp r3, r4
	blt _021F3096
_021F30BC:
	mov r0, #0
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F30C4
ov05_021F30C4: ; 0x021F30C4
	push {r3, r4, r5, r6, r7, lr}
	str r1, [sp]
	mov r1, #1
	ldr r0, [sp]
	lsl r1, r1, #8
	ldr r4, [r0, r1]
	add r0, #0xe0
	ldr r0, [r0]
	mov r6, #0
	ldr r5, [r4, #0xc]
	bl sub_0201F2C0
	cmp r0, #1
	beq _021F3178
	add r7, r4, #4
	b _021F310E
_021F30E4:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _021F310A
	ldr r0, [sp]
	ldr r1, [r5]
	mov r2, #0
	bl ov05_021F2DB0
	add r2, r0, #0
	ldr r0, [sp]
	ldr r1, [r5, #4]
	ldr r3, [r5, #8]
	bl ov05_021F317C
	mov r0, #0
	str r0, [r5, #0xc]
	ldrsh r0, [r7, r0]
	add r0, r0, #1
	strh r0, [r7]
_021F310A:
	add r5, #0x10
	add r6, r6, #1
_021F310E:
	mov r0, #4
	ldrsh r1, [r4, r0]
	mov r0, #2
	ldrsh r0, [r4, r0]
	cmp r1, r0
	bge _021F3122
	mov r0, #0
	ldrsh r0, [r4, r0]
	cmp r6, r0
	blt _021F30E4
_021F3122:
	mov r6, #0
	ldrsh r0, [r4, r6]
	ldr r7, [r4, #0xc]
	sub r1, r0, #1
	cmp r1, #0
	ble _021F3174
	add r5, r7, #0
_021F3130:
	ldr r1, [r5, #0xc]
	cmp r1, #0
	bne _021F3166
	add r2, r6, #1
	cmp r2, r0
	bge _021F3166
	lsl r1, r2, #4
	add r3, r7, r1
_021F3140:
	ldr r1, [r3, #0xc]
	cmp r1, #0
	beq _021F315E
	lsl r0, r2, #4
	add r3, r7, r0
	mov ip, r3
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r1, #0
	mov r0, ip
	str r1, [r0, #0xc]
	b _021F3166
_021F315E:
	add r2, r2, #1
	add r3, #0x10
	cmp r2, r0
	blt _021F3140
_021F3166:
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r6, r6, #1
	add r5, #0x10
	sub r1, r0, #1
	cmp r6, r1
	blt _021F3130
_021F3174:
	mov r0, #0
	strh r0, [r4, #4]
_021F3178:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021F317C
ov05_021F317C: ; 0x021F317C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	mov r0, #4
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xf0
	add r4, r1, #0
	add r6, r3, #0
	add r1, r2, #0
	ldr r0, [r0]
	add r2, r4, #0
	mov r3, #1
	bl sub_02020F54
	cmp r0, #0
	bne _021F31A2
	bl GF_AssertFail
_021F31A2:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F31C8
	cmp r6, #0
	bne _021F31BA
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F28A0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021F31BA:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F2914
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F31C8
ov05_021F31C8: ; 0x021F31C8
	push {r4, r5, r6, lr}
	mov r3, #1
	lsl r3, r3, #8
	ldr r3, [r0, r3]
	mov r5, #1
	ldr r4, [r3, #0x10]
	mov r2, #0
	strh r5, [r3, #6]
	ldrsh r6, [r3, r2]
	cmp r6, #0
	ble _021F31FC
_021F31DE:
	ldr r5, [r4, #8]
	cmp r5, #0
	bne _021F31F4
	add r0, #0xf0
	ldr r0, [r0]
	str r0, [r4, #8]
	str r1, [r4, #4]
	mov r0, #0
	str r0, [r4]
	strh r0, [r3, #6]
	pop {r4, r5, r6, pc}
_021F31F4:
	add r2, r2, #1
	add r4, #0xc
	cmp r2, r6
	blt _021F31DE
_021F31FC:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021F3204
ov05_021F3204: ; 0x021F3204
	push {r4, r5}
	mov r2, #1
	lsl r2, r2, #8
	ldr r2, [r0, r2]
	mov r0, #1
	ldr r4, [r2, #0x10]
	mov r3, #0
	strh r0, [r2, #6]
	ldrsh r5, [r2, r3]
	cmp r5, #0
	ble _021F3236
_021F321A:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021F322E
	ldr r0, [r4, #4]
	cmp r0, r1
	bne _021F322E
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4]
	b _021F3236
_021F322E:
	add r3, r3, #1
	add r4, #0xc
	cmp r3, r5
	blt _021F321A
_021F3236:
	mov r0, #0
	strh r0, [r2, #6]
	pop {r4, r5}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F3240
ov05_021F3240: ; 0x021F3240
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #1
	lsl r0, r0, #8
	ldr r6, [r1, r0]
	ldrh r0, [r6, #6]
	cmp r0, #1
	beq _021F327A
	mov r4, #0
	ldrsh r0, [r6, r4]
	ldr r5, [r6, #0x10]
	cmp r0, #0
	ble _021F327A
	mov r7, #1
_021F325A:
	ldr r0, [r5]
	cmp r0, #0
	bne _021F326E
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021F326E
	ldr r1, [r5, #4]
	bl sub_020210F0
	str r7, [r5]
_021F326E:
	mov r0, #0
	ldrsh r0, [r6, r0]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021F325A
_021F327A:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F327C
ov05_021F327C: ; 0x021F327C
	push {r3, r4, r5, r6, r7, lr}
	mov r0, #1
	lsl r0, r0, #8
	ldr r6, [r1, r0]
	mov r4, #0
	ldr r5, [r6, #0x10]
	mov r0, #1
	strh r0, [r6, #6]
	ldrsh r0, [r6, r4]
	cmp r0, #0
	ble _021F32B6
	add r7, r4, #0
_021F3294:
	ldr r0, [r5]
	cmp r0, #1
	bne _021F32AA
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021F32AA
	ldr r1, [r5, #4]
	bl sub_02021158
	str r7, [r5]
	str r7, [r5, #8]
_021F32AA:
	mov r0, #0
	ldrsh r0, [r6, r0]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021F3294
_021F32B6:
	mov r0, #0
	strh r0, [r6, #6]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F32BC
ov05_021F32BC: ; 0x021F32BC
	push {r4, r5, r6, lr}
	mov r5, #1
	lsl r5, r5, #8
	ldr r5, [r0, r5]
	mov r4, #0
	ldrsh r6, [r5, r4]
	ldr r0, [r5, #8]
	cmp r6, #0
	ble _021F32F2
_021F32CE:
	ldr r5, [r0, #4]
	cmp r5, #0
	bne _021F32EA
	str r1, [r0, #4]
	str r2, [r0, #8]
	str r3, [r0]
	ldr r0, [r0, #8]
	mov r2, #0
	str r2, [r0]
	add r0, r1, #0
	mov r1, #1
	bl ov05_021F2E0C
	pop {r4, r5, r6, pc}
_021F32EA:
	add r4, r4, #1
	add r0, #0xc
	cmp r4, r6
	blt _021F32CE
_021F32F2:
	bl GF_AssertFail
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F32F8
ov05_021F32F8: ; 0x021F32F8
	push {r3, r4}
	mov r2, #1
	lsl r2, r2, #8
	ldr r0, [r0, r2]
	mov r3, #0
	ldrsh r4, [r0, r3]
	ldr r2, [r0, #8]
	cmp r4, #0
	ble _021F3322
_021F330A:
	ldr r0, [r2, #4]
	cmp r0, r1
	bne _021F331A
	mov r0, #0
	str r0, [r2, #4]
	str r0, [r2, #8]
	pop {r3, r4}
	bx lr
_021F331A:
	add r3, r3, #1
	add r2, #0xc
	cmp r3, r4
	blt _021F330A
_021F3322:
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F3328
ov05_021F3328: ; 0x021F3328
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r6, [r7, r0]
	mov r4, #0
	ldrsh r0, [r6, r4]
	ldr r5, [r6, #8]
	cmp r0, #0
	ble _021F3356
_021F333C:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021F334A
	add r0, r7, #0
	add r1, r5, #0
	bl ov05_021F3364
_021F334A:
	mov r0, #0
	ldrsh r0, [r6, r0]
	add r4, r4, #1
	add r5, #0xc
	cmp r4, r0
	blt _021F333C
_021F3356:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F3358
ov05_021F3358: ; 0x021F3358
	ldr r3, _021F3360 ; =ov05_021F3328
	add r0, r1, #0
	bx r3
	nop
_021F3360: .word ov05_021F3328

	thumb_func_start ov05_021F3364
ov05_021F3364: ; 0x021F3364
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	bl ov05_021F2A08
	cmp r0, #2
	beq _021F33B2
	ldr r0, [r4, #4]
	ldr r1, [r4]
	bl ov05_021F1FE0
	ldr r1, [r4, #8]
	str r0, [r1]
	ldr r0, [r4, #8]
	ldr r0, [r0]
	cmp r0, #0
	bne _021F338A
	bl GF_AssertFail
_021F338A:
	ldr r0, [r4, #4]
	mov r1, #0
	bl ov05_021F2E0C
	mov r1, #2
	ldr r0, [r4, #4]
	lsl r1, r1, #0x14
	bl MapObject_TestFlagsBits
	cmp r0, #1
	ldr r0, [r4, #4]
	bne _021F33A8
	bl sub_020586DC
	b _021F33AC
_021F33A8:
	bl sub_020586A0
_021F33AC:
	mov r0, #0
	str r0, [r4, #4]
	str r0, [r4, #8]
_021F33B2:
	pop {r4, pc}

	thumb_func_start ov05_021F33B4
ov05_021F33B4: ; 0x021F33B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	add r5, r0, #0
	mov r0, #0xc
	add r7, r6, #0
	mul r7, r0
	lsl r0, r6, #4
	lsl r1, r7, #1
	str r0, [sp, #4]
	add r0, r1, r0
	str r0, [sp, #8]
	add r0, #0x28
	str r0, [sp, #8]
	ldr r1, [sp, #8]
	mov r0, #4
	str r2, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	bne _021F33E2
	bl GF_AssertFail
_021F33E2:
	ldr r2, [sp, #8]
	add r0, r4, #0
	mov r1, #0
	bl memset
	ldr r0, [sp]
	strh r6, [r4]
	strh r0, [r4, #2]
	add r0, r4, #0
	add r0, #0x28
	str r0, [r4, #8]
	add r1, r0, r7
	ldr r0, [sp, #4]
	str r1, [r4, #0xc]
	add r0, r1, r0
	str r0, [r4, #0x10]
	mov r0, #1
	lsl r0, r0, #8
	str r4, [r5, r0]
	add r0, r0, #4
	ldr r0, [r5, r0]
	bl MapObjectManager_GetPriority
	add r6, r0, #0
	ldr r0, _021F3448 ; =ov05_021F30C4
	add r1, r5, #0
	add r2, r6, #1
	bl SysTask_CreateOnMainQueue
	str r0, [r4, #0x18]
	ldr r0, _021F344C ; =ov05_021F3358
	add r1, r5, #0
	add r2, r6, #2
	bl SysTask_CreateOnMainQueue
	str r0, [r4, #0x1c]
	ldr r0, _021F3450 ; =ov05_021F3240
	add r1, r5, #0
	mov r2, #0xff
	bl sub_0200CA60
	str r0, [r4, #0x20]
	ldr r0, _021F3454 ; =ov05_021F327C
	add r1, r5, #0
	mov r2, #0xff
	bl sub_0200CA98
	str r0, [r4, #0x24]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_021F3448: .word ov05_021F30C4
_021F344C: .word ov05_021F3358
_021F3450: .word ov05_021F3240
_021F3454: .word ov05_021F327C

	thumb_func_start ov05_021F3458
ov05_021F3458: ; 0x021F3458
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	ldr r4, [r5, r0]
	mov r0, #1
	strh r0, [r4, #6]
	ldr r0, [r4, #0x18]
	bl sub_0200CAB4
	ldr r0, [r4, #0x1c]
	bl sub_0200CAB4
	ldr r0, [r4, #0x20]
	bl sub_0200CAB4
	ldr r0, [r4, #0x24]
	bl sub_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	mov r1, #0
	lsl r0, r0, #8
	str r1, [r5, r0]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021F3490
ov05_021F3490: ; 0x021F3490
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov05_021F2E28
	cmp r0, #1
	beq _021F34A8
	add r0, r5, #0
	bl ov05_021F0514
	cmp r0, #0
	bne _021F34D2
_021F34A8:
	add r0, r5, #0
	bl MapObject_GetGfxID
	add r6, r0, #0
	add r0, r5, #0
	bl MapObject_GetManager
	add r7, r0, #0
	add r0, r5, #0
	bl sub_020576A8
	add r0, r7, #0
	add r1, r6, #0
	add r2, r5, #0
	bl ov05_021F2C80
	add r0, r5, #0
	add r1, r4, #0
	bl sub_02057614
	pop {r3, r4, r5, r6, r7, pc}
_021F34D2:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021F34DC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F34DC
ov05_021F34DC: ; 0x021F34DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r7, r0, #0
	str r1, [sp, #8]
	bl ov05_021F2F3C
	str r0, [sp, #0x18]
	bl ov05_021F2D48
	str r0, [sp, #0x14]
	add r0, r7, #0
	bl ov05_021F0514
	str r0, [sp, #0x10]
	mov r0, #4
	mov r1, #0x58
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x58
	add r5, r0, #0
	bl memset
	ldr r0, [sp, #8]
	str r0, [r5]
	add r0, r7, #0
	str r7, [r5, #0x50]
	bl MapObject_GetGfxID
	add r6, r0, #0
	bl ov05_021F2DE8
	ldr r4, _021F36C4 ; =ov05_021F9094
	ldr r2, _021F36C8 ; =0x0000FFFF
_021F3520:
	ldr r1, [r4]
	cmp r1, r0
	beq _021F352E
	add r4, #8
	ldr r1, [r4]
	cmp r1, r2
	bne _021F3520
_021F352E:
	ldr r0, _021F36C8 ; =0x0000FFFF
	cmp r1, r0
	bne _021F3538
	bl GF_AssertFail
_021F3538:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #4]
	mov r2, #0
	bl ov05_021F2DB0
	str r0, [r5, #8]
	add r0, r6, #0
	bl ov05_021F2DF4
	ldr r4, _021F36CC ; =ov05_021F90E4
	ldr r2, _021F36C8 ; =0x0000FFFF
_021F354E:
	ldr r1, [r4]
	cmp r1, r0
	beq _021F355C
	add r4, #8
	ldr r1, [r4]
	cmp r1, r2
	bne _021F354E
_021F355C:
	ldr r0, _021F36C8 ; =0x0000FFFF
	cmp r1, r0
	bne _021F3566
	bl GF_AssertFail
_021F3566:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #4]
	mov r2, #0
	bl ov05_021F2DB0
	add r1, r5, #0
	add r1, #0x14
	str r0, [r5, #0xc]
	bl sub_0202227C
	ldr r4, _021F36D0 ; =ov05_021FA0AC
	ldr r0, _021F36C8 ; =0x0000FFFF
_021F357E:
	ldr r1, [r4]
	cmp r1, r6
	beq _021F358C
	add r4, #8
	ldr r1, [r4]
	cmp r1, r0
	bne _021F357E
_021F358C:
	ldr r0, _021F36C8 ; =0x0000FFFF
	cmp r1, r0
	bne _021F3596
	bl GF_AssertFail
_021F3596:
	ldr r0, [sp, #0x18]
	ldr r1, [r4, #4]
	mov r2, #0
	bl ov05_021F2DB0
	str r0, [r5, #0x10]
	bl NNS_G3dGetTex
	add r4, r0, #0
	add r0, r6, #0
	bl ov05_021F2E00
	add r3, r0, #0
	add r0, r5, #0
	add r0, #0x14
	str r0, [sp]
	add r0, r5, #0
	ldr r1, [r5, #8]
	add r0, #0x28
	add r2, r4, #0
	bl sub_0201F7A4
	ldr r0, [sp, #0x10]
	bl sub_0201F7E0
	add r3, r0, #0
	add r2, sp, #0x28
	ldmia r3!, {r0, r1}
	add r4, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r5, #0
	str r0, [r2]
	ldr r0, [sp, #0x14]
	add r1, #0x28
	add r2, r4, #0
	bl ov05_021F2E70
	str r0, [r5, #0x24]
	cmp r0, #0
	bne _021F35EC
	bl GF_AssertFail
_021F35EC:
	ldr r0, [sp, #0x10]
	bl sub_0201F844
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl sub_0201F830
	ldr r0, [sp, #0x10]
	bl sub_0201F8C0
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl sub_0201F890
	ldr r0, [sp, #0x10]
	bl sub_0201F880
	add r1, r0, #0
	ldr r0, [r5, #0x24]
	bl sub_0201F86C
	ldr r0, [r5, #0x24]
	mov r1, #0
	bl sub_0201F854
	ldr r0, [r5, #0x24]
	mov r1, #1
	bl sub_0201F80C
	ldr r0, [r5, #0x24]
	bl sub_0201F8F0
	add r0, r7, #0
	bl sub_02058A9C
	cmp r0, #1
	bne _021F367A
	add r0, r7, #0
	mov r1, #2
	bl sub_0205829C
	str r0, [sp, #0xc]
	add r0, r7, #0
	mov r1, #1
	bl sub_02059C90
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r4, #0
	bl sub_02054AF0
	cmp r0, #0
	bne _021F3658
	mov r4, #1
_021F3658:
	add r0, r7, #0
	add r1, sp, #0x1c
	bl MapObject_GetPositionVec
	add r0, r7, #0
	bl ov05_021E4C24
	ldr r1, [sp, #0xc]
	str r4, [sp]
	str r1, [sp, #4]
	add r1, r5, #0
	ldr r2, [r5, #0x24]
	add r1, #0x28
	add r3, sp, #0x1c
	bl ov06_02249B7C
	str r0, [r5, #0x54]
_021F367A:
	add r0, r7, #0
	bl sub_020576A8
	mov r1, #0x41
	ldr r0, [sp, #0x18]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, r6, #0
	add r2, r7, #0
	bl ov05_021F2C80
	ldr r1, [sp, #8]
	add r0, r7, #0
	bl sub_02057614
	mov r1, #0x41
	ldr r0, [sp, #0x18]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl MapObjectManager_GetPriority
	ldr r0, _021F36D4 ; =ov05_021F36D8
	add r1, r5, #0
	mov r2, #0xff
	bl sub_0200CA98
	add r4, r0, #0
	bne _021F36B6
	bl GF_AssertFail
_021F36B6:
	add r0, r4, #0
	add r1, r5, #0
	bl ov05_021F36D8
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021F36C4: .word ov05_021F9094
_021F36C8: .word 0x0000FFFF
_021F36CC: .word ov05_021F90E4
_021F36D0: .word ov05_021FA0AC
_021F36D4: .word ov05_021F36D8

	thumb_func_start ov05_021F36D8
ov05_021F36D8: ; 0x021F36D8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r4, [r5, #0x50]
	cmp r0, #0
	beq _021F36EC
	cmp r0, #1
	beq _021F3744
	pop {r4, r5, r6, pc}
_021F36EC:
	add r0, r4, #0
	bl MapObject_IsInUse
	cmp r0, #0
	beq _021F3700
	add r0, r4, #0
	bl ov05_021F2E28
	cmp r0, #0
	bne _021F3730
_021F3700:
	ldr r0, [r5, #0x54]
	cmp r0, #0
	beq _021F370A
	bl sub_02064520
_021F370A:
	ldr r0, [r5, #0x24]
	bl sub_0201F744
	ldr r0, [r5, #8]
	bl FreeToHeap
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	ldr r0, [r5, #0x10]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
	pop {r4, r5, r6, pc}
_021F3730:
	add r0, r4, #0
	bl MapObject_GetGfxID
	ldr r1, [r5]
	cmp r1, r0
	beq _021F377C
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	pop {r4, r5, r6, pc}
_021F3744:
	add r0, r4, #0
	bl ov05_021F2E28
	cmp r0, #0
	bne _021F377C
	ldr r0, [r5, #0x54]
	cmp r0, #0
	beq _021F3758
	bl sub_02064520
_021F3758:
	ldr r0, [r5, #0x24]
	bl sub_0201F744
	ldr r0, [r5, #8]
	bl FreeToHeap
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	ldr r0, [r5, #0x10]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl sub_0200CAB4
_021F377C:
	pop {r4, r5, r6, pc}
	.balign 4, 0

	.section .rodata

	.global ov05_021FC550
ov05_021FC550: ; 0x021FC550
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global ov05_021FC55C
ov05_021FC55C: ; 0x021FC55C
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global ov05_021FC56C
ov05_021FC56C: ; 0x021FC56C
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00

	.global ov05_021FC57C
ov05_021FC57C: ; 0x021FC57C
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
