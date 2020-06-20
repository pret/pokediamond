	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202A1E0
FUN_0202A1E0: ; 0x0202A1E0
	mov r0, #0xe4
	bx lr

	thumb_func_start FUN_0202A1E4
FUN_0202A1E4: ; 0x0202A1E4
	ldr r3, _0202A1EC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x3c
	bx r3
	.balign 4
_0202A1EC: .word MI_CpuFill8

	thumb_func_start FUN_0202A1F0
FUN_0202A1F0: ; 0x0202A1F0
	push {r4, lr}
	mov r2, #0x5a
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x1
	strb r0, [r4, #0x3]
	pop {r4, pc}

	thumb_func_start FUN_0202A204
FUN_0202A204: ; 0x0202A204
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_02013764
	add r0, r4, #0x0
	add r0, #0x8
	mov r1, #0x1
	bl FUN_02013764
	add r0, r4, #0x0
	add r0, #0x10
	mov r1, #0x2
	bl FUN_02013764
	add r4, #0x18
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02013764
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A230
FUN_0202A230: ; 0x0202A230
	ldr r3, _0202A238 ; =MI_CpuFill8
	mov r1, #0x0
	ldr r2, _0202A23C ; =0x00000B3C
	bx r3
	.balign 4
_0202A238: .word MI_CpuFill8
_0202A23C: .word 0x00000B3C

	thumb_func_start FUN_0202A240
FUN_0202A240: ; 0x0202A240
	push {r3, lr}
	cmp r1, #0xa
	bhi _0202A2BE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202A252: ; jump table (using 16-bit offset)
	.short _0202A268 - _0202A252 - 2; case 0
	.short _0202A270 - _0202A252 - 2; case 1
	.short _0202A274 - _0202A252 - 2; case 2
	.short _0202A278 - _0202A252 - 2; case 3
	.short _0202A27C - _0202A252 - 2; case 4
	.short _0202A280 - _0202A252 - 2; case 5
	.short _0202A28E - _0202A252 - 2; case 6
	.short _0202A29C - _0202A252 - 2; case 7
	.short _0202A2A4 - _0202A252 - 2; case 8
	.short _0202A2B2 - _0202A252 - 2; case 9
	.short _0202A2BA - _0202A252 - 2; case 10
_0202A268:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1d
	pop {r3, pc}
_0202A270:
	ldrb r0, [r0, #0x2]
	pop {r3, pc}
_0202A274:
	ldrb r0, [r0, #0x3]
	pop {r3, pc}
_0202A278:
	ldrh r0, [r0, #0x4]
	pop {r3, pc}
_0202A27C:
	ldrh r0, [r0, #0x6]
	pop {r3, pc}
_0202A280:
	add r1, r2, #0x0
	add r0, #0x8
	mov r2, #0x4
	bl MI_CpuCopy8
	mov r0, #0x0
	pop {r3, pc}
_0202A28E:
	add r1, r2, #0x0
	add r0, #0x2c
	mov r2, #0x10
	bl MI_CpuCopy8
	mov r0, #0x0
	pop {r3, pc}
_0202A29C:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	pop {r3, pc}
_0202A2A4:
	add r1, r2, #0x0
	add r0, #0xc
	mov r2, #0x1c
	bl MI_CpuCopy8
	mov r0, #0x0
	pop {r3, pc}
_0202A2B2:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	pop {r3, pc}
_0202A2BA:
	ldr r0, [r0, #0x28]
	pop {r3, pc}
_0202A2BE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202A2C4
FUN_0202A2C4: ; 0x0202A2C4
	push {r4, lr}
	add r3, r0, #0x0
	cmp r1, #0xa
	bhi _0202A36A
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202A2D8: ; jump table (using 16-bit offset)
	.short _0202A2EE - _0202A2D8 - 2; case 0
	.short _0202A300 - _0202A2D8 - 2; case 1
	.short _0202A306 - _0202A2D8 - 2; case 2
	.short _0202A30C - _0202A2D8 - 2; case 3
	.short _0202A312 - _0202A2D8 - 2; case 4
	.short _0202A318 - _0202A2D8 - 2; case 5
	.short _0202A326 - _0202A2D8 - 2; case 6
	.short _0202A334 - _0202A2D8 - 2; case 7
	.short _0202A346 - _0202A2D8 - 2; case 8
	.short _0202A35A - _0202A2D8 - 2; case 9
	.short _0202A354 - _0202A2D8 - 2; case 10
_0202A2EE:
	ldrb r1, [r3, #0x0]
	mov r0, #0x1c
	bic r1, r0
	ldrb r0, [r2, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r3, #0x0]
	pop {r4, pc}
_0202A300:
	ldrb r0, [r2, #0x0]
	strb r0, [r3, #0x2]
	pop {r4, pc}
_0202A306:
	ldrb r0, [r2, #0x0]
	strb r0, [r3, #0x3]
	pop {r4, pc}
_0202A30C:
	ldrh r0, [r2, #0x0]
	strh r0, [r3, #0x4]
	pop {r4, pc}
_0202A312:
	ldrh r0, [r2, #0x0]
	strh r0, [r3, #0x6]
	pop {r4, pc}
_0202A318:
	add r3, #0x8
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x4
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A326:
	add r3, #0x2c
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x10
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A334:
	ldrb r4, [r3, #0x0]
	ldrb r1, [r2, #0x0]
	mov r0, #0x1
	bic r4, r0
	mov r0, #0x1
	and r0, r1
	orr r0, r4
	strb r0, [r3, #0x0]
	pop {r4, pc}
_0202A346:
	add r3, #0xc
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x1c
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A354:
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x28]
	pop {r4, pc}
_0202A35A:
	ldrb r1, [r3, #0x0]
	mov r0, #0xe0
	bic r1, r0
	ldrb r0, [r2, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r3, #0x0]
_0202A36A:
	pop {r4, pc}

	thumb_func_start FUN_0202A36C
FUN_0202A36C: ; 0x0202A36C
	push {r3-r4}
	ldrb r4, [r0, #0x3]
	add r1, r4, r1
	cmp r1, #0xff
	bge _0202A378
	strb r1, [r0, #0x3]
_0202A378:
	ldrh r1, [r0, #0x4]
	add r2, r1, r2
	ldr r1, _0202A394 ; =0x0000FFFF
	cmp r2, r1
	bge _0202A384
	strh r2, [r0, #0x4]
_0202A384:
	ldrh r1, [r0, #0x6]
	add r2, r1, r3
	ldr r1, _0202A394 ; =0x0000FFFF
	cmp r2, r1
	bge _0202A390
	strh r2, [r0, #0x6]
_0202A390:
	pop {r3-r4}
	bx lr
	.balign 4
_0202A394: .word 0x0000FFFF

	thumb_func_start FUN_0202A398
FUN_0202A398: ; 0x0202A398
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_0202A3A0
FUN_0202A3A0: ; 0x0202A3A0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	ldrb r3, [r0, #0x0]
	mov r2, #0x2
	lsr r1, r1, #0x1e
	bic r3, r2
	orr r1, r3
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202A3B4
FUN_0202A3B4: ; 0x0202A3B4
	cmp r2, #0x6
	bhi _0202A402
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0202A3C4: ; jump table (using 16-bit offset)
	.short _0202A402 - _0202A3C4 - 2; case 0
	.short _0202A3D2 - _0202A3C4 - 2; case 1
	.short _0202A402 - _0202A3C4 - 2; case 2
	.short _0202A402 - _0202A3C4 - 2; case 3
	.short _0202A402 - _0202A3C4 - 2; case 4
	.short _0202A3E0 - _0202A3C4 - 2; case 5
	.short _0202A3F2 - _0202A3C4 - 2; case 6
_0202A3D2:
	ldr r2, _0202A408 ; =0x0000270F
	cmp r1, r2
	bls _0202A3DC
	strh r2, [r0, #0x0]
	b _0202A402
_0202A3DC:
	strh r1, [r0, #0x0]
	b _0202A402
_0202A3E0:
	ldrh r2, [r0, #0x0]
	add r2, r2, r1
	ldr r1, _0202A408 ; =0x0000270F
	cmp r2, r1
	ble _0202A3EE
	strh r1, [r0, #0x0]
	b _0202A402
_0202A3EE:
	strh r2, [r0, #0x0]
	b _0202A402
_0202A3F2:
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	bhs _0202A3FE
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _0202A402
_0202A3FE:
	sub r1, r2, r1
	strh r1, [r0, #0x0]
_0202A402:
	ldrh r0, [r0, #0x0]
	bx lr
	nop
_0202A408: .word 0x0000270F

	thumb_func_start FUN_0202A40C
FUN_0202A40C: ; 0x0202A40C
	cmp r1, #0x2
	beq _0202A416
	cmp r1, #0x3
	beq _0202A424
	b _0202A440
_0202A416:
	mov r1, #0x0
	strb r1, [r0, #0x2]
	ldrh r2, [r0, #0x8]
	mov r1, #0x10
	bic r2, r1
	strh r2, [r0, #0x8]
	b _0202A440
_0202A424:
	ldrh r1, [r0, #0x8]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1f
	beq _0202A434
	ldrb r1, [r0, #0x2]
	add r1, r1, #0x1
	strb r1, [r0, #0x2]
	b _0202A440
_0202A434:
	mov r1, #0x1
	strb r1, [r0, #0x2]
	ldrh r2, [r0, #0x8]
	mov r1, #0x10
	orr r1, r2
	strh r1, [r0, #0x8]
_0202A440:
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_0202A444
FUN_0202A444: ; 0x0202A444
	cmp r1, #0x2
	beq _0202A452
	cmp r1, #0x3
	beq _0202A458
	cmp r1, #0x4
	beq _0202A464
	b _0202A46E
_0202A452:
	mov r1, #0x1
	strb r1, [r0, #0x3]
	b _0202A46E
_0202A458:
	ldrb r1, [r0, #0x3]
	cmp r1, #0xa
	bhs _0202A46E
	add r1, r1, #0x1
	strb r1, [r0, #0x3]
	b _0202A46E
_0202A464:
	ldrb r1, [r0, #0x3]
	cmp r1, #0x1
	bls _0202A46E
	sub r1, r1, #0x1
	strb r1, [r0, #0x3]
_0202A46E:
	ldrb r0, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A474
FUN_0202A474: ; 0x0202A474
	push {r3, lr}
	add r3, r0, #0x0
	cmp r1, #0x0
	bne _0202A48A
	add r3, #0xc0
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}
_0202A48A:
	add r3, #0x18
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}

	thumb_func_start FUN_0202A498
FUN_0202A498: ; 0x0202A498
	push {r3, lr}
	cmp r1, #0x0
	bne _0202A4AA
	add r1, r2, #0x0
	add r0, #0xc0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}
_0202A4AA:
	add r1, r2, #0x0
	add r0, #0x18
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202A4B8
FUN_0202A4B8: ; 0x0202A4B8
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldrb r0, [r1, #0x2]
	mov r2, #0xfa
	lsl r2, r2, #0x2
	sub r0, r0, #0x1
	add r3, r0, #0x0
	mul r3, r2
	lsl r0, r3, #0x10
	lsr r4, r0, #0x10
	ldrh r3, [r1, #0x4]
	mov r0, #0xa
	ldrb r5, [r1, #0x3]
	mul r0, r3
	mov r3, #0x14
	mul r3, r5
	lsl r0, r0, #0x10
	lsl r3, r3, #0x10
	lsr r0, r0, #0x10
	lsr r3, r3, #0x10
	add r3, r0, r3
	add r0, r2, #0x0
	sub r0, #0x32
	cmp r3, r0
	ble _0202A4EE
	mov r5, #0x0
	b _0202A4F6
_0202A4EE:
	sub r2, #0x32
	sub r0, r2, r3
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_0202A4F6:
	ldrh r1, [r1, #0x6]
	ldr r0, _0202A51C ; =0x000003CA
	cmp r1, r0
	bls _0202A502
	mov r1, #0x0
	b _0202A510
_0202A502:
	add r0, #0x1e
	sub r0, r0, r1
	mov r1, #0x1e
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_0202A510:
	add r0, r4, r5
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	strh r0, [r6, #0x16]
	pop {r4-r6, pc}
	.balign 4
_0202A51C: .word 0x000003CA

	thumb_func_start FUN_0202A520
FUN_0202A520: ; 0x0202A520
	ldrh r0, [r0, #0x16]
	bx lr

	thumb_func_start FUN_0202A524
FUN_0202A524: ; 0x0202A524
	push {r3, lr}
	ldrh r0, [r0, #0x16]
	mov r1, #0xfa
	lsl r1, r1, #0x2
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202A538
FUN_0202A538: ; 0x0202A538
	push {r4-r5}
	cmp r1, #0x5
	bne _0202A544
	mov r0, #0x0
	pop {r4-r5}
	bx lr
_0202A544:
	cmp r2, #0x2
	beq _0202A54E
	cmp r2, #0x3
	beq _0202A558
	b _0202A56A
_0202A54E:
	lsl r2, r1, #0x1
	mov r3, #0x0
	add r2, r0, r2
	strh r3, [r2, #0xc]
	b _0202A56A
_0202A558:
	add r5, r0, #0x0
	add r5, #0xc
	lsl r4, r1, #0x1
	ldrh r3, [r5, r4]
	ldr r2, _0202A574 ; =0x0000FFFE
	cmp r3, r2
	bhs _0202A56A
	add r2, r3, #0x1
	strh r2, [r5, r4]
_0202A56A:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0xc]
	pop {r4-r5}
	bx lr
	.balign 4
_0202A574: .word 0x0000FFFE

	thumb_func_start FUN_0202A578
FUN_0202A578: ; 0x0202A578
	push {r3-r4}
	mov r3, #0x1
	mov r4, #0x0
	cmp r1, #0x0
	bls _0202A590
_0202A582:
	add r4, r4, #0x1
	lsl r4, r4, #0x10
	lsl r3, r3, #0x11
	lsr r4, r4, #0x10
	lsr r3, r3, #0x10
	cmp r4, r1
	blo _0202A582
_0202A590:
	cmp r2, #0x0
	beq _0202A5B4
	cmp r2, #0x1
	beq _0202A5AC
	cmp r2, #0x2
	bne _0202A5C2
	ldr r1, _0202A5C8 ; =0x0000FFFF
	eor r1, r3
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldrh r1, [r0, #0x8]
	and r1, r2
	strh r1, [r0, #0x8]
	b _0202A5C2
_0202A5AC:
	ldrh r1, [r0, #0x8]
	orr r1, r3
	strh r1, [r0, #0x8]
	b _0202A5C2
_0202A5B4:
	ldrh r0, [r0, #0x8]
	add r2, r0, #0x0
	asr r2, r1
	mov r0, #0x1
	and r0, r2
	pop {r3-r4}
	bx lr
_0202A5C2:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
_0202A5C8: .word 0x0000FFFF

	thumb_func_start FUN_0202A5CC
FUN_0202A5CC: ; 0x0202A5CC
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0202A5D0
FUN_0202A5D0: ; 0x0202A5D0
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0202A5D4
FUN_0202A5D4: ; 0x0202A5D4
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x17
	add r4, r2, #0x0
	bl FUN_02022610
	mov r1, #0x69
	lsl r1, r1, #0x2
	add r1, r0, r1
	lsl r0, r5, #0x3
	add r0, r1, r0
	add r1, r4, #0x0
	bl FUN_02013960
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202A5F4
FUN_0202A5F4: ; 0x0202A5F4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x17
	bl FUN_02022610
	mov r1, #0x69
	lsl r1, r1, #0x2
	add r1, r0, r1
	lsl r0, r4, #0x3
	add r0, r1, r0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A60C
FUN_0202A60C: ; 0x0202A60C
	push {r3-r6}
	add r4, r3, #0x0
	mov r3, #0x1
	cmp r2, #0x0
	beq _0202A66C
	cmp r2, #0xc8
	bhi _0202A66C
	cmp r1, #0x0
	beq _0202A66C
	cmp r1, #0xa
	bhi _0202A66C
	sub r5, r2, #0x1
	sub r2, r1, #0x1
	mov r1, #0xc8
	mul r1, r2
	add r1, r5, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsr r6, r1, #0x1f
	lsl r5, r1, #0x1d
	sub r5, r5, r6
	mov r2, #0x1d
	ror r5, r2
	add r2, r6, r5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	lsl r3, r2
	lsl r2, r3, #0x18
	lsl r1, r1, #0x15
	lsr r5, r2, #0x18
	add r3, r0, #0x4
	lsr r2, r1, #0x18
	ldrb r1, [r3, r2]
	orr r1, r5
	strb r1, [r3, r2]
	ldr r3, [r4, #0x0]
	ldr r1, [r4, #0x8]
	lsl r5, r3, #0x18
	ldr r3, [r4, #0x4]
	lsl r1, r1, #0x18
	lsl r3, r3, #0x18
	lsr r3, r3, #0x8
	ldr r2, [r4, #0xc]
	lsr r1, r1, #0x10
	orr r3, r5
	orr r1, r3
	orr r1, r2
	str r1, [r0, #0x0]
_0202A66C:
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_0202A670
FUN_0202A670: ; 0x0202A670
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r4, #0x4
	mov r1, #0x0
	mov r2, #0xfa
	bl MI_CpuFill8
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A68C
FUN_0202A68C: ; 0x0202A68C
	ldr r3, [r0, #0x0]
	ldr r2, [r1, #0x0]
	cmp r3, r2
	bls _0202A698
	mov r0, #0x1
	bx lr
_0202A698:
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	cmp r3, r2
	bls _0202A6A4
	mov r0, #0x1
	bx lr
_0202A6A4:
	ldr r2, [r0, #0x8]
	ldr r0, [r1, #0x8]
	cmp r2, r0
	bls _0202A6B0
	mov r0, #0x1
	bx lr
_0202A6B0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202A6B4
FUN_0202A6B4: ; 0x0202A6B4
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r7, #0x1
	cmp r6, #0xc8
	bhi _0202A6C8
	cmp r4, #0xa
	bls _0202A6CE
_0202A6C8:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0202A6CE:
	ldr r0, [r5, #0x0]
	lsr r1, r0, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	lsr r1, r0, #0x10
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x4]
	lsr r1, r0, #0x8
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r3, #0x0
	add r1, sp, #0x0
	bl FUN_0202A68C
	cmp r0, #0x0
	beq _0202A706
	add r0, r5, #0x0
	bl FUN_0202A670
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0202A706:
	sub r1, r4, #0x1
	mov r0, #0xc8
	mul r0, r1
	sub r2, r6, #0x1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1d
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	add r0, r5, r0
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r7, #0x0
	lsl r2, r1
	lsl r1, r2, #0x18
	ldrb r0, [r0, #0x4]
	lsr r1, r1, #0x18
	tst r0, r1
	beq _0202A73E
	add sp, #0x10
	add r0, r7, #0x0
	pop {r3-r7, pc}
_0202A73E:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_0202A744
FUN_0202A744: ; 0x0202A744
	add r0, #0xfe
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A74C
FUN_0202A74C: ; 0x0202A74C
	add r0, #0xff
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A754
FUN_0202A754: ; 0x0202A754
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x41
	add r4, r2, #0x0
	lsl r1, r1, #0x2
	ldr r2, _0202A77C ; =0x0000063C
	add r1, r5, r1
	add r6, r3, #0x0
	bl MI_CpuCopy8
	ldr r0, _0202A780 ; =0x00000101
	strb r4, [r5, r0]
	sub r0, r0, #0x1
	strb r6, [r5, r0]
	mov r0, #0x1
	add r5, #0xfe
	strb r0, [r5, #0x0]
	pop {r4-r6, pc}
	nop
_0202A77C: .word 0x0000063C
_0202A780: .word 0x00000101

	thumb_func_start FUN_0202A784
FUN_0202A784: ; 0x0202A784
	ldr r2, _0202A794 ; =0x00000101
	ldrb r3, [r0, r2]
	sub r2, r2, #0x1
	strb r3, [r1, #0x0]
	ldrb r0, [r0, r2]
	strb r0, [r1, #0x1]
	bx lr
	nop
_0202A794: .word 0x00000101

	thumb_func_start FUN_0202A798
FUN_0202A798: ; 0x0202A798
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x41
	lsl r1, r1, #0x2
	add r5, r0, r1
	mov r0, #0xe4
	add r4, r2, #0x0
	mul r4, r0
	ldr r0, _0202A834 ; =0x00002710
	add r7, r6, #0x0
	str r0, [r6, #0x0]
	add r0, r5, r4
	add r0, #0xc9
	ldrb r0, [r0, #0x0]
	add r7, #0x30
	strh r0, [r6, #0x4]
	add r0, r5, r4
	add r0, #0xc8
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0202A7EE
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0x11
	mov r3, #0xb
	bl NewMsgDataFromNarc
	add r1, r5, r4
	add r1, #0xc8
	ldrb r1, [r1, #0x0]
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x1f
	add r1, #0x16
	add r2, #0x8
	bl ReadMsgDataIntoU16Array
	ldr r0, [sp, #0x0]
	bl DestroyMsgData
	b _0202A7FC
_0202A7EE:
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xa8
	add r1, #0x8
	mov r2, #0x10
	bl MI_CpuCopy8
_0202A7FC:
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xca
	add r1, #0x18
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xd2
	add r1, #0x20
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r6, #0x28
	add r0, #0xda
	add r1, r6, #0x0
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r1, r7, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3-r7, pc}
	nop
_0202A834: .word 0x00002710

	thumb_func_start FUN_0202A838
FUN_0202A838: ; 0x0202A838
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x1d
	add r4, r2, #0x0
	lsl r1, r1, #0x6
	mov r2, #0xff
	add r1, r5, r1
	lsl r2, r2, #0x2
	add r6, r3, #0x0
	bl MI_CpuCopy8
	ldr r0, _0202A860 ; =0x00000103
	strb r4, [r5, r0]
	sub r0, r0, #0x1
	strb r6, [r5, r0]
	mov r0, #0x1
	add r5, #0xff
	strb r0, [r5, #0x0]
	pop {r4-r6, pc}
	.balign 4
_0202A860: .word 0x00000103

	thumb_func_start FUN_0202A864
FUN_0202A864: ; 0x0202A864
	ldr r2, _0202A874 ; =0x00000103
	ldrb r3, [r0, r2]
	sub r2, r2, #0x1
	strb r3, [r1, #0x0]
	ldrb r0, [r0, r2]
	strb r0, [r1, #0x1]
	bx lr
	nop
_0202A874: .word 0x00000103

	thumb_func_start FUN_0202A878
FUN_0202A878: ; 0x0202A878
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0xff
	lsl r1, r1, #0x2
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x1d
	lsl r0, r0, #0x6
	mov r2, #0xff
	add r0, r5, r0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuCopy8
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202A89C
FUN_0202A89C: ; 0x0202A89C
	mov r0, #0xd
	lsl r0, r0, #0x8
	bx lr
	.balign 4

	thumb_func_start FUN_0202A8A4
FUN_0202A8A4: ; 0x0202A8A4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0202A1E4
	add r0, r4, #0x0
	add r0, #0x3c
	bl FUN_0202A1F0
	mov r0, #0x69
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0202A204
	mov r0, #0x71
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0202A230
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A8CC
FUN_0202A8CC: ; 0x0202A8CC
	ldr r3, _0202A8D4 ; =FUN_02022610
	mov r1, #0x17
	bx r3
	nop
_0202A8D4: .word FUN_02022610

	thumb_func_start FUN_0202A8D8
FUN_0202A8D8: ; 0x0202A8D8
	push {r3, lr}
	mov r1, #0x17
	bl FUN_02022610
	add r0, #0x3c
	pop {r3, pc}

	thumb_func_start FUN_0202A8E4
FUN_0202A8E4: ; 0x0202A8E4
	push {r3, lr}
	mov r1, #0x17
	bl FUN_02022610
	mov r1, #0x71
	lsl r1, r1, #0x2
	add r0, r0, r1
	pop {r3, pc}
