    .include "asm/macros.inc"
    .include "global.inc"

	.text
	.extern FUN_02000E9C
	.extern FUN_02000EC8

	thumb_func_start FUN_020010A8
FUN_020010A8: ; 0x020010A8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0x38
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_02016998
	add r4, r0, #0x0
	add r3, r5, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x0]
	bl FUN_02013690
	str r0, [r4, #0x28]
	strh r6, [r4, #0x2c]
	add r1, r4, #0x0
	strh r7, [r4, #0x2e]
	mov r0, #0x0
	add r1, #0x30
	strb r0, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x31
	strb r0, [r1, #0x0]
	add r1, r4, #0x0
	mov r2, #0xff
	add r1, #0x32
	strb r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x33
	strb r0, [r1, #0x0]
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x34
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	ldrb r1, [r4, #0x17]
	add r0, #0x20
	ldrb r2, [r0, #0x0]
	lsl r1, r1, #0x18
	mov r0, #0xf
	lsr r3, r1, #0x1c
	mov r1, #0xf
	bic r2, r0
	and r3, r1
	orr r3, r2
	add r2, r4, #0x0
	add r2, #0x20
	strb r3, [r2, #0x0]
	add r2, r4, #0x0
	add r2, #0x20
	ldrb r2, [r2, #0x0]
	mov r3, #0xf0
	bic r2, r3
	ldrb r3, [r4, #0x18]
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x1c
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	orr r3, r2
	add r2, r4, #0x0
	add r2, #0x20
	strb r3, [r2, #0x0]
	add r2, r4, #0x0
	add r2, #0x21
	ldrb r2, [r2, #0x0]
	bic r2, r0
	ldrb r0, [r4, #0x18]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	mov r1, #0x3f
	bic r0, r1
	ldrh r1, [r4, #0x1a]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1d
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0x3f
	and r1, r2
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x22
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x24
	ldrb r0, [r0, #0x0]
	mov r1, #0x7f
	bic r0, r1
	ldrh r1, [r4, #0x1a]
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1a
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0x7f
	and r1, r2
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x24
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x24
	ldrb r1, [r0, #0x0]
	mov r0, #0x80
	bic r1, r0
	add r0, r4, #0x0
	add r0, #0x24
	strb r1, [r0, #0x0]
	ldrh r1, [r4, #0x10]
	ldrh r0, [r4, #0x12]
	cmp r1, r0
	bhs _020011AC
	strh r1, [r4, #0x12]
_020011AC:
	ldrb r2, [r4, #0x18]
	ldr r0, [r4, #0x28]
	lsl r1, r2, #0x1c
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	ldrb r1, [r4, #0x17]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1c
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	lsr r1, r1, #0x8
	lsr r2, r2, #0x10
	orr r1, r2
	orr r1, r3
	bl FUN_020136E0
	ldrb r1, [r4, #0x18]
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FUN_02019620
	ldrh r1, [r4, #0x2c]
	ldrh r3, [r4, #0x12]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02001714
	add r0, r4, #0x0
	bl FUN_020017AC
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02001B64
	ldr r0, [r5, #0xc]
	bl FUN_020191D0
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02001204
FUN_02001204: ; 0x02001204
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	ldr r6, _020012FC ; =0x021C48B8
	mov r3, #0x0
	add r1, #0x33
	strb r3, [r1, #0x0]
	ldr r1, [r6, #0x48]
	mov r2, #0x1
	add r5, r1, #0x0
	tst r5, r2
	beq _0200122C
	ldrh r1, [r4, #0x2c]
	ldrh r0, [r4, #0x2e]
	ldr r2, [r4, #0x0]
	add r0, r1, r0
	lsl r0, r0, #0x3
	add r0, r2, r0
	ldr r0, [r0, #0x4]
	pop {r4-r6, pc}
_0200122C:
	mov r5, #0x2
	tst r1, r5
	beq _02001236
	sub r0, r5, #0x4
	pop {r4-r6, pc}
_02001236:
	ldr r5, [r6, #0x4c]
	mov r1, #0x40
	tst r1, r5
	beq _02001254
	add r1, r2, #0x0
	bl FUN_02001AA4
	cmp r0, #0x0
	bne _0200124E
	mov r0, #0x1
	add r4, #0x33
	strb r0, [r4, #0x0]
_0200124E:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001254:
	mov r1, #0x80
	add r3, r5, #0x0
	tst r3, r1
	beq _02001274
	add r1, r2, #0x0
	add r3, r2, #0x0
	bl FUN_02001AA4
	cmp r0, #0x0
	bne _0200126E
	mov r0, #0x2
	add r4, #0x33
	strb r0, [r4, #0x0]
_0200126E:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001274:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x17
	lsr r0, r0, #0x1e
	beq _02001284
	cmp r0, #0x1
	beq _0200128A
	cmp r0, #0x2
	beq _0200129C
_02001284:
	mov r0, #0x0
	add r1, r0, #0x0
	b _020012AC
_0200128A:
	mov r0, #0x20
	mov r1, #0x10
	and r0, r5
	and r1, r5
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	b _020012AC
_0200129C:
	lsl r0, r1, #0x2
	add r1, #0x80
	and r0, r5
	and r1, r5
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
_020012AC:
	cmp r0, #0x0
	beq _020012D0
	ldrh r2, [r4, #0x12]
	add r0, r4, #0x0
	mov r1, #0x1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r3, #0x0
	bl FUN_02001AA4
	cmp r0, #0x0
	bne _020012CA
	mov r0, #0x3
	add r4, #0x33
	strb r0, [r4, #0x0]
_020012CA:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_020012D0:
	cmp r1, #0x0
	beq _020012F4
	ldrh r2, [r4, #0x12]
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	add r3, r1, #0x0
	bl FUN_02001AA4
	cmp r0, #0x0
	bne _020012EE
	mov r0, #0x4
	add r4, #0x33
	strb r0, [r4, #0x0]
_020012EE:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_020012F4:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
	nop
_020012FC: .word 0x021C48B8

	thumb_func_start FUN_02001300
FUN_02001300: ; 0x02001300
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x0
	beq _0200130C
	ldrh r0, [r4, #0x2c]
	strh r0, [r1, #0x0]
_0200130C:
	cmp r2, #0x0
	beq _02001314
	ldrh r0, [r4, #0x2e]
	strh r0, [r2, #0x0]
_02001314:
	ldr r0, [r4, #0x28]
	bl FUN_020136C0
	add r0, r4, #0x0
	add r0, #0x34
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_02016A8C
	pop {r4, pc}

	thumb_func_start FUN_02001328
FUN_02001328: ; 0x02001328
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r1, [r4, #0x18]
	ldr r0, [r4, #0xc]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FUN_02019620
	ldrh r1, [r4, #0x2c]
	ldrh r3, [r4, #0x12]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02001714
	add r0, r4, #0x0
	bl FUN_020017AC
	ldr r0, [r4, #0xc]
	bl FUN_020191D0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02001354
FUN_02001354: ; 0x02001354
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r6, r1, #0x0
	beq _0200136E
	add r5, r4, #0x0
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
_0200136E:
	strh r2, [r4, #0x2c]
	add r0, r4, #0x0
	strh r3, [r4, #0x2e]
	mov r3, #0x0
	add r0, #0x30
	strb r3, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x31
	add r1, sp, #0x0
	strb r3, [r0, #0x0]
	ldrh r0, [r1, #0x14]
	cmp r0, #0x40
	bne _02001398
	ldrh r1, [r1, #0x10]
	add r0, r4, #0x0
	mov r2, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02001AA4
	b _020013AC
_02001398:
	cmp r0, #0x80
	bne _020013AC
	ldrh r1, [r1, #0x10]
	mov r2, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r3, r2, #0x0
	bl FUN_02001AA4
_020013AC:
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	beq _020013B6
	ldrh r0, [r4, #0x2c]
	strh r0, [r1, #0x0]
_020013B6:
	ldr r1, [sp, #0x1c]
	cmp r1, #0x0
	beq _020013C0
	ldrh r0, [r4, #0x2e]
	strh r0, [r1, #0x0]
_020013C0:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020013C8
FUN_020013C8: ; 0x020013C8
	push {r4, lr}
	sub sp, #0x10
	mov r4, #0x0
	str r4, [sp, #0x0]
	add r4, sp, #0x8
	ldrh r4, [r4, #0x10]
	str r4, [sp, #0x4]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x20]
	str r4, [sp, #0xc]
	bl FUN_02001354
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020013E8
FUN_020013E8: ; 0x020013E8
	push {r3-r6}
	add r4, r0, #0x0
	add r4, #0x20
	ldrb r6, [r4, #0x0]
	mov r4, #0xf
	mov r5, #0xf
	bic r6, r4
	and r1, r5
	orr r6, r1
	add r1, r0, #0x0
	add r1, #0x20
	strb r6, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x20
	lsl r2, r2, #0x1c
	ldrb r1, [r1, #0x0]
	mov r6, #0xf0
	lsr r2, r2, #0x18
	bic r1, r6
	orr r2, r1
	add r1, r0, #0x0
	add r1, #0x20
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x21
	ldrb r2, [r1, #0x0]
	add r1, r3, #0x0
	and r1, r5
	bic r2, r4
	orr r2, r1
	add r1, r0, #0x0
	add r1, #0x21
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x24
	ldrb r2, [r1, #0x0]
	mov r1, #0x80
	add r0, #0x24
	orr r1, r2
	strb r1, [r0, #0x0]
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_0200143C
FUN_0200143C: ; 0x0200143C
	ldrh r2, [r0, #0x2c]
	ldrh r0, [r0, #0x2e]
	add r0, r2, r0
	strh r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02001448
FUN_02001448: ; 0x02001448
	cmp r1, #0x0
	beq _02001450
	ldrh r3, [r0, #0x2c]
	strh r3, [r1, #0x0]
_02001450:
	cmp r2, #0x0
	beq _02001458
	ldrh r0, [r0, #0x2e]
	strh r0, [r2, #0x0]
_02001458:
	bx lr
	.balign 4

	thumb_func_start FUN_0200145C
FUN_0200145C: ; 0x0200145C
	add r0, #0x33
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02001464
FUN_02001464: ; 0x02001464
	ldr r2, [r0, #0x0]
	lsl r0, r1, #0x3
	add r0, r2, r0
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_02001470
FUN_02001470: ; 0x02001470
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x13
	bhi _02001532
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02001484: ; jump table (using 16-bit offset)
	.short _020014AC - _02001484 - 2; case 0
	.short _020014B0 - _02001484 - 2; case 1
	.short _020014B4 - _02001484 - 2; case 2
	.short _020014B8 - _02001484 - 2; case 3
	.short _02001532 - _02001484 - 2; case 4
	.short _020014BC - _02001484 - 2; case 5
	.short _020014C0 - _02001484 - 2; case 6
	.short _020014C4 - _02001484 - 2; case 7
	.short _020014C8 - _02001484 - 2; case 8
	.short _020014D0 - _02001484 - 2; case 9
	.short _020014EA - _02001484 - 2; case 10
	.short _020014F2 - _02001484 - 2; case 11
	.short _020014FA - _02001484 - 2; case 12
	.short _02001502 - _02001484 - 2; case 13
	.short _0200150A - _02001484 - 2; case 14
	.short _02001512 - _02001484 - 2; case 15
	.short _0200151A - _02001484 - 2; case 16
	.short _02001522 - _02001484 - 2; case 17
	.short _0200152A - _02001484 - 2; case 18
	.short _0200152E - _02001484 - 2; case 19
_020014AC:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
_020014B0:
	ldr r0, [r4, #0x8]
	pop {r4, pc}
_020014B4:
	ldrh r0, [r4, #0x10]
	pop {r4, pc}
_020014B8:
	ldrh r0, [r4, #0x12]
	pop {r4, pc}
_020014BC:
	ldrb r0, [r4, #0x14]
	pop {r4, pc}
_020014C0:
	ldrb r0, [r4, #0x15]
	pop {r4, pc}
_020014C4:
	ldrb r0, [r4, #0x16]
	pop {r4, pc}
_020014C8:
	ldrb r0, [r4, #0x17]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	pop {r4, pc}
_020014D0:
	ldrh r0, [r4, #0x1a]
	mov r1, #0x1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02002E4C
	ldrh r1, [r4, #0x1a]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	add r0, r1, r0
	pop {r4, pc}
_020014EA:
	ldrb r0, [r4, #0x17]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	pop {r4, pc}
_020014F2:
	ldrb r0, [r4, #0x18]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	pop {r4, pc}
_020014FA:
	ldrb r0, [r4, #0x18]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	pop {r4, pc}
_02001502:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	pop {r4, pc}
_0200150A:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1c
	pop {r4, pc}
_02001512:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x17
	lsr r0, r0, #0x1e
	pop {r4, pc}
_0200151A:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	pop {r4, pc}
_02001522:
	ldrh r0, [r4, #0x1a]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	pop {r4, pc}
_0200152A:
	ldr r0, [r4, #0xc]
	pop {r4, pc}
_0200152E:
	ldr r0, [r4, #0x1c]
	pop {r4, pc}
_02001532:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}

	thumb_func_start FUN_02001538
FUN_02001538: ; 0x02001538
	cmp r1, #0x13
	bls _0200153E
	b _02001648
_0200153E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0200154A: ; jump table (using 16-bit offset)
	.short _02001572 - _0200154A - 2; case 0
	.short _02001576 - _0200154A - 2; case 1
	.short _0200157A - _0200154A - 2; case 2
	.short _0200157E - _0200154A - 2; case 3
	.short _02001648 - _0200154A - 2; case 4
	.short _02001582 - _0200154A - 2; case 5
	.short _02001586 - _0200154A - 2; case 6
	.short _0200158A - _0200154A - 2; case 7
	.short _0200158E - _0200154A - 2; case 8
	.short _02001648 - _0200154A - 2; case 9
	.short _020015A2 - _0200154A - 2; case 10
	.short _020015B6 - _0200154A - 2; case 11
	.short _020015CA - _0200154A - 2; case 12
	.short _020015DE - _0200154A - 2; case 13
	.short _020015F2 - _0200154A - 2; case 14
	.short _02001606 - _0200154A - 2; case 15
	.short _0200161A - _0200154A - 2; case 16
	.short _0200162E - _0200154A - 2; case 17
	.short _02001642 - _0200154A - 2; case 18
	.short _02001646 - _0200154A - 2; case 19
_02001572:
	str r2, [r0, #0x4]
	bx lr
_02001576:
	str r2, [r0, #0x8]
	bx lr
_0200157A:
	strh r2, [r0, #0x10]
	bx lr
_0200157E:
	strh r2, [r0, #0x12]
	bx lr
_02001582:
	strb r2, [r0, #0x14]
	bx lr
_02001586:
	strb r2, [r0, #0x15]
	bx lr
_0200158A:
	strb r2, [r0, #0x16]
	bx lr
_0200158E:
	ldrb r3, [r0, #0x17]
	mov r1, #0xf
	bic r3, r1
	lsl r1, r2, #0x18
	lsr r2, r1, #0x18
	mov r1, #0xf
	and r1, r2
	orr r1, r3
	strb r1, [r0, #0x17]
	bx lr
_020015A2:
	ldrb r3, [r0, #0x17]
	mov r1, #0xf0
	bic r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	orr r1, r3
	strb r1, [r0, #0x17]
	bx lr
_020015B6:
	ldrb r3, [r0, #0x18]
	mov r1, #0xf
	bic r3, r1
	lsl r1, r2, #0x18
	lsr r2, r1, #0x18
	mov r1, #0xf
	and r1, r2
	orr r1, r3
	strb r1, [r0, #0x18]
	bx lr
_020015CA:
	ldrb r3, [r0, #0x18]
	mov r1, #0xf0
	bic r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	orr r1, r3
	strb r1, [r0, #0x18]
	bx lr
_020015DE:
	ldrh r3, [r0, #0x1a]
	mov r1, #0x7
	bic r3, r1
	lsl r1, r2, #0x18
	lsr r2, r1, #0x18
	mov r1, #0x7
	and r1, r2
	orr r1, r3
	strh r1, [r0, #0x1a]
	bx lr
_020015F2:
	ldrh r3, [r0, #0x1a]
	mov r1, #0x78
	bic r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x19
	orr r1, r3
	strh r1, [r0, #0x1a]
	bx lr
_02001606:
	ldrh r3, [r0, #0x1a]
	ldr r1, _0200164C ; =0xFFFFFE7F
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x17
	orr r1, r3
	strh r1, [r0, #0x1a]
	bx lr
_0200161A:
	ldrh r3, [r0, #0x1a]
	ldr r1, _02001650 ; =0xFFFF81FF
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x11
	orr r1, r3
	strh r1, [r0, #0x1a]
	bx lr
_0200162E:
	ldrh r3, [r0, #0x1a]
	ldr r1, _02001654 ; =0xFFFF7FFF
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x10
	orr r1, r3
	strh r1, [r0, #0x1a]
	bx lr
_02001642:
	str r2, [r0, #0xc]
	bx lr
_02001646:
	str r2, [r0, #0x1c]
_02001648:
	bx lr
	nop
_0200164C: .word 0xFFFFFE7F
_02001650: .word 0xFFFF81FF
_02001654: .word 0xFFFF7FFF

	thumb_func_start FUN_02001658
FUN_02001658: ; 0x02001658
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0200165C
FUN_0200165C: ; 0x0200165C
	push {r4-r6, lr}
	sub sp, #0x18
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	beq _02001710
	add r0, #0x24
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	str r3, [sp, #0x0]
	beq _020016CC
	mov r0, #0xff
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r0, #0x20
	ldrb r2, [r0, #0x0]
	add r3, r4, #0x0
	lsl r0, r2, #0x18
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsl r0, r2, #0x1c
	add r2, r6, #0x0
	add r2, #0x21
	ldrb r2, [r2, #0x0]
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x18
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r0, r0, #0x8
	lsr r2, r2, #0x10
	orr r0, r2
	orr r0, r1
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	add r2, r5, #0x0
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1a
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [r6, #0xc]
	add r6, #0x24
	ldrb r1, [r6, #0x0]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x19
	bl FUN_0201BE3C
	add sp, #0x18
	pop {r4-r6, pc}
_020016CC:
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldrb r1, [r6, #0x18]
	add r3, r4, #0x0
	lsl r0, r1, #0x1c
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	ldrb r0, [r6, #0x17]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x8
	lsr r1, r1, #0x10
	orr r0, r1
	orr r0, r2
	str r0, [sp, #0x8]
	ldrh r0, [r6, #0x1a]
	add r2, r5, #0x0
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1d
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	ldrh r1, [r6, #0x1a]
	ldr r0, [r6, #0xc]
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1a
	bl FUN_0201BE3C
_02001710:
	add sp, #0x18
	pop {r4-r6, pc}

	thumb_func_start FUN_02001714
FUN_02001714: ; 0x02001714
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	str r3, [sp, #0x0]
	ldrh r0, [r5, #0x1a]
	add r4, r1, #0x0
	mov r1, #0x1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r6, r2, #0x0
	bl FUN_02002E4C
	ldrh r1, [r5, #0x1a]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ble _020017A6
_02001748:
	ldr r1, [r5, #0x0]
	lsl r0, r4, #0x3
	str r0, [sp, #0x8]
	add r0, r1, r0
	ldr r1, [r0, #0x4]
	mov r0, #0x2
	mvn r0, r0
	cmp r1, r0
	beq _02001760
	ldrb r0, [r5, #0x15]
	str r0, [sp, #0x4]
	b _02001764
_02001760:
	ldrb r0, [r5, #0x14]
	str r0, [sp, #0x4]
_02001764:
	ldrb r0, [r5, #0x17]
	lsl r0, r0, #0x1c
	lsr r3, r0, #0x1c
	ldr r0, [sp, #0xc]
	add r2, r0, #0x0
	mul r2, r6
	add r0, r3, r2
	lsl r0, r0, #0x18
	ldr r3, [r5, #0x8]
	lsr r7, r0, #0x18
	cmp r3, #0x0
	beq _02001782
	add r0, r5, #0x0
	add r2, r7, #0x0
	blx r3
_02001782:
	ldr r2, [r5, #0x0]
	ldr r1, [sp, #0x8]
	add r0, r5, #0x0
	ldr r1, [r2, r1]
	ldr r2, [sp, #0x4]
	add r3, r7, #0x0
	bl FUN_0200165C
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [sp, #0x10]
	add r6, r6, #0x1
	add r1, r0, #0x1
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x10]
	cmp r1, r0
	blt _02001748
_020017A6:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020017AC
FUN_020017AC: ; 0x020017AC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x1a]
	mov r1, #0x1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02002E4C
	ldrh r1, [r4, #0x1a]
	ldrh r5, [r4, #0x2e]
	lsl r2, r1, #0x19
	lsr r2, r2, #0x1c
	add r0, r2, r0
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	ldrb r0, [r4, #0x17]
	mul r3, r5
	ldrb r2, [r4, #0x16]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	add r0, r0, r3
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	lsl r0, r1, #0x10
	lsr r0, r0, #0x1f
	cmp r0, #0x3
	bhi _02001802
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020017F2: ; jump table (using 16-bit offset)
	.short _020017FA - _020017F2 - 2; case 0
	.short _02001802 - _020017F2 - 2; case 1
	.short _02001802 - _020017F2 - 2; case 2
	.short _02001802 - _020017F2 - 2; case 3
_020017FA:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0xc]
	bl FUN_020136F8
_02001802:
	pop {r3-r5, pc}

	thumb_func_start FUN_02001804
FUN_02001804: ; 0x02001804
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldrh r0, [r4, #0x1a]
	add r5, r1, #0x0
	lsl r1, r0, #0x10
	lsr r1, r1, #0x1f
	cmp r1, #0x3
	bhi _02001868
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02001822: ; jump table (using 16-bit offset)
	.short _0200182A - _02001822 - 2; case 0
	.short _02001868 - _02001822 - 2; case 1
	.short _02001868 - _02001822 - 2; case 2
	.short _02001868 - _02001822 - 2; case 3
_0200182A:
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x1
	bl FUN_02002E4C
	ldrh r1, [r4, #0x1a]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	mov r0, #0x8
	str r0, [sp, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x4]
	ldrb r1, [r4, #0x18]
	ldr r0, [r4, #0xc]
	ldrb r2, [r4, #0x16]
	ldrb r4, [r4, #0x17]
	lsl r1, r1, #0x1c
	mul r3, r5
	lsl r4, r4, #0x1c
	lsr r4, r4, #0x1c
	add r3, r4, r3
	lsl r3, r3, #0x10
	lsr r1, r1, #0x1c
	lsr r3, r3, #0x10
	bl FUN_020196F4
_02001868:
	add sp, #0x8
	pop {r3-r5, pc}

	thumb_func_start FUN_0200186C
FUN_0200186C: ; 0x0200186C
	push {r4-r7}
	ldrh r4, [r0, #0x2e]
	ldrh r3, [r0, #0x2c]
	cmp r1, #0x0
	ldrh r2, [r0, #0x12]
	bne _020018FE
	cmp r2, #0x1
	bne _02001880
	mov r1, #0x0
	b _02001898
_02001880:
	lsr r7, r2, #0x1f
	lsl r6, r2, #0x1f
	sub r6, r6, r7
	mov r5, #0x1f
	ror r6, r5
	lsr r1, r2, #0x1
	add r5, r7, r6
	add r1, r1, r5
	sub r1, r2, r1
	sub r1, r1, #0x1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
_02001898:
	cmp r3, #0x0
	bne _020018CC
	cmp r4, #0x0
	beq _020018C6
	ldr r2, [r0, #0x0]
	lsl r1, r3, #0x3
	mov r3, #0x2
	add r1, r2, r1
	mvn r3, r3
_020018AA:
	sub r2, r4, #0x1
	lsl r2, r2, #0x10
	lsr r4, r2, #0x10
	lsl r2, r4, #0x3
	add r2, r1, r2
	ldr r2, [r2, #0x4]
	cmp r2, r3
	beq _020018C2
	strh r4, [r0, #0x2e]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_020018C2:
	cmp r4, #0x0
	bne _020018AA
_020018C6:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_020018CC:
	cmp r4, r1
	bls _020018F6
	ldr r5, [r0, #0x0]
	lsl r2, r3, #0x3
	add r2, r5, r2
	mov r5, #0x2
	mvn r5, r5
_020018DA:
	sub r4, r4, #0x1
	lsl r4, r4, #0x10
	lsr r4, r4, #0x10
	lsl r6, r4, #0x3
	add r6, r2, r6
	ldr r6, [r6, #0x4]
	cmp r6, r5
	beq _020018F2
	strh r4, [r0, #0x2e]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_020018F2:
	cmp r4, r1
	bhi _020018DA
_020018F6:
	strh r1, [r0, #0x2e]
	sub r1, r3, #0x1
	strh r1, [r0, #0x2c]
	b _02001984
_020018FE:
	cmp r2, #0x1
	bne _02001906
	mov r5, #0x0
	b _0200191A
_02001906:
	lsr r7, r2, #0x1f
	lsl r6, r2, #0x1f
	sub r6, r6, r7
	mov r5, #0x1f
	ror r6, r5
	lsr r1, r2, #0x1
	add r5, r7, r6
	add r1, r1, r5
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
_0200191A:
	ldrh r1, [r0, #0x10]
	sub r1, r1, r2
	cmp r3, r1
	bne _02001954
	sub r2, r2, #0x1
	cmp r4, r2
	bge _0200194E
	ldr r5, [r0, #0x0]
	lsl r1, r3, #0x3
	add r1, r5, r1
	mov r5, #0x2
	mvn r5, r5
_02001932:
	add r3, r4, #0x1
	lsl r3, r3, #0x10
	lsr r4, r3, #0x10
	lsl r3, r4, #0x3
	add r3, r1, r3
	ldr r3, [r3, #0x4]
	cmp r3, r5
	beq _0200194A
	strh r4, [r0, #0x2e]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_0200194A:
	cmp r4, r2
	blt _02001932
_0200194E:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_02001954:
	cmp r4, r5
	bhs _0200197E
	ldr r2, [r0, #0x0]
	lsl r1, r3, #0x3
	mov r6, #0x2
	add r1, r2, r1
	mvn r6, r6
_02001962:
	add r2, r4, #0x1
	lsl r2, r2, #0x10
	lsr r4, r2, #0x10
	lsl r2, r4, #0x3
	add r2, r1, r2
	ldr r2, [r2, #0x4]
	cmp r2, r6
	beq _0200197A
	strh r4, [r0, #0x2e]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_0200197A:
	cmp r4, r5
	blo _02001962
_0200197E:
	strh r5, [r0, #0x2e]
	add r1, r3, #0x1
	strh r1, [r0, #0x2c]
_02001984:
	mov r0, #0x2
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_0200198C
FUN_0200198C: ; 0x0200198C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldrh r0, [r5, #0x12]
	add r4, r1, #0x0
	add r7, r2, #0x0
	cmp r4, r0
	blt _020019B8
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FUN_02019620
	ldrh r1, [r5, #0x2c]
	ldrh r3, [r5, #0x12]
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_02001714
	add sp, #0x8
	pop {r3-r7, pc}
_020019B8:
	ldrh r0, [r5, #0x1a]
	mov r1, #0x1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02002E4C
	ldrh r1, [r5, #0x1a]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r7, #0x0
	ldrb r0, [r5, #0x18]
	bne _02001A46
	lsl r0, r0, #0x1c
	lsr r7, r0, #0x1c
	add r2, r4, #0x0
	lsl r3, r7, #0x4
	mul r2, r6
	orr r3, r7
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #0xc]
	mov r1, #0x1
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0201A8C8
	ldrh r1, [r5, #0x2c]
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, r4, #0x0
	bl FUN_02001714
	ldrb r0, [r5, #0x17]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1c
	ldrh r0, [r5, #0x12]
	add r1, r0, #0x0
	mul r1, r6
	add r0, r2, r1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, #0xc]
	bl FUN_0201AB0C
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0201AB10
	lsl r0, r0, #0x3
	lsl r1, r6, #0x13
	sub r0, r0, r4
	lsr r1, r1, #0x10
	lsl r0, r0, #0x10
	str r1, [sp, #0x0]
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	mov r2, #0x0
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r3, r4, #0x0
	bl FUN_020196F4
	add sp, #0x8
	pop {r3-r7, pc}
_02001A46:
	lsl r0, r0, #0x1c
	lsr r3, r0, #0x1c
	add r2, r4, #0x0
	mul r2, r6
	lsl r6, r3, #0x4
	orr r3, r6
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #0xc]
	mov r1, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0201A8C8
	ldrh r0, [r5, #0x12]
	ldrh r1, [r5, #0x2c]
	add r3, r4, #0x0
	sub r2, r0, r4
	add r1, r1, r2
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl FUN_02001714
	ldr r0, [r5, #0xc]
	bl FUN_0201AB0C
	lsl r0, r0, #0x13
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldrb r0, [r5, #0x17]
	mov r2, #0x0
	add r3, r2, #0x0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	str r0, [sp, #0x4]
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FUN_020196F4
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02001AA4
FUN_02001AA4: ; 0x02001AA4
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r4, r0, #0x0
	str r3, [sp, #0x8]
	ldrh r0, [r4, #0x2e]
	mov r6, #0x0
	add r5, r6, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	add r7, r6, #0x0
	cmp r0, #0x0
	bls _02001AF6
_02001AC0:
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_0200186C
	orr r5, r0
	cmp r0, #0x2
	bne _02001AEA
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrh r1, [r4, #0x2c]
	ldrh r0, [r4, #0x2e]
	ldr r2, [r4, #0x0]
	add r0, r1, r0
	lsl r0, r0, #0x3
	add r0, r2, r0
	ldr r1, [r0, #0x4]
	mov r0, #0x2
	mvn r0, r0
	cmp r1, r0
	beq _02001AC0
_02001AEA:
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #0x4]
	cmp r7, r0
	blo _02001AC0
_02001AF6:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02001B5E
	cmp r5, #0x3
	bhi _02001B14
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02001B0C: ; jump table (using 16-bit offset)
	.short _02001B14 - _02001B0C - 2; case 0
	.short _02001B1A - _02001B0C - 2; case 1
	.short _02001B38 - _02001B0C - 2; case 2
	.short _02001B38 - _02001B0C - 2; case 3
_02001B14:
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_02001B1A:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02001804
	add r0, r4, #0x0
	bl FUN_020017AC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02001B64
	ldr r0, [r4, #0xc]
	bl FUN_020191D0
	b _02001B5E
_02001B38:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02001804
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0200198C
	add r0, r4, #0x0
	bl FUN_020017AC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02001B64
	ldr r0, [r4, #0xc]
	bl FUN_020191D0
_02001B5E:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_02001B64
FUN_02001B64: ; 0x02001B64
	push {r3-r5, lr}
	ldr r3, [r0, #0x4]
	add r2, r1, #0x0
	cmp r3, #0x0
	beq _02001B7E
	ldrh r5, [r0, #0x2c]
	ldrh r4, [r0, #0x2e]
	ldr r1, [r0, #0x0]
	add r4, r5, r4
	lsl r4, r4, #0x3
	add r1, r1, r4
	ldr r1, [r1, #0x4]
	blx r3
_02001B7E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02001B80
FUN_02001B80: ; 0x02001B80
	ldr r3, _02001B88 ; =FUN_020191D0
	ldr r0, [r0, #0xc]
	bx r3
	nop
_02001B88: .word FUN_020191D0 

	thumb_func_start FUN_02001B8C
FUN_02001B8C: ; 0x02001B8C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r3, [sp, #0x0]
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	add r6, r1, #0x0
	mov r1, #0x20
	add r7, r2, #0x0
	str r0, [sp, #0x4]
	bl FUN_02016998
	add r4, r0, #0x0
	add r3, r5, #0x0
	ldmia r3!, {r0-r1}
	add r2, r4, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_02013690
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x24]
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x0]
	strb r0, [r4, #0x15]
	add r0, r4, #0x0
	bl FUN_02001FB4
	strb r0, [r4, #0x16]
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	mov r1, #0x0
	strb r0, [r4, #0x1c]
	strb r6, [r4, #0x17]
	strb r7, [r4, #0x18]
	ldrb r0, [r5, #0x8]
	bl FUN_02002E4C
	add r6, r0, #0x0
	ldrb r0, [r5, #0x8]
	mov r1, #0x2
	bl FUN_02002E4C
	add r0, r6, r0
	strb r0, [r4, #0x19]
	ldrb r0, [r5, #0x8]
	mov r1, #0x1
	bl FUN_02002E4C
	add r6, r0, #0x0
	ldrb r0, [r5, #0x8]
	mov r1, #0x3
	bl FUN_02002E4C
	add r0, r6, r0
	strb r0, [r4, #0x1a]
	add r0, r4, #0x0
	bl FUN_02001FF4
	add r0, r4, #0x0
	bl FUN_02002080
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02001C14
FUN_02001C14: ; 0x02001C14
	push {r4, lr}
	sub sp, #0x8
	add r4, sp, #0x0
	ldrb r4, [r4, #0x10]
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x14]
	str r4, [sp, #0x4]
	bl FUN_02001B8C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02001C34
FUN_02001C34: ; 0x02001C34
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldrb r0, [r5, #0x8]
	add r6, r1, #0x0
	add r4, r2, #0x0
	mov r1, #0x0
	bl FUN_02002E4C
	add r1, r0, #0x0
	str r4, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, r6, #0x0
	bl FUN_02001C14
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02001C5C
FUN_02001C5C: ; 0x02001C5C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x0
	beq _02001C68
	ldrb r0, [r4, #0x15]
	strb r0, [r1, #0x0]
_02001C68:
	ldr r0, [r4, #0xc]
	bl FUN_020136C0
	ldrb r0, [r4, #0x1c]
	add r1, r4, #0x0
	bl FUN_02016A8C
	pop {r4, pc}

	thumb_func_start FUN_02001C78
FUN_02001C78: ; 0x02001C78
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r2, _02001D24 ; =0x021C48B8
	strb r1, [r4, #0x1b]
	ldr r2, [r2, #0x48]
	mov r5, #0x1
	add r3, r2, #0x0
	tst r3, r5
	beq _02001C9E
	ldr r0, _02001D28 ; =0x000005DC
	bl FUN_020054C8
	ldrb r0, [r4, #0x15]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	pop {r3-r5, pc}
_02001C9E:
	ldr r3, [r4, #0x10]
	tst r3, r2
	beq _02001CAE
	ldr r0, _02001D28 ; =0x000005DC
	bl FUN_020054C8
	sub r0, r5, #0x3
	pop {r3-r5, pc}
_02001CAE:
	mov r3, #0x40
	tst r3, r2
	beq _02001CC8
	ldr r2, _02001D28 ; =0x000005DC
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001CC2
	add r0, r5, #0x0
	strb r0, [r4, #0x1b]
_02001CC2:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001CC8:
	mov r1, #0x80
	tst r1, r2
	beq _02001CE4
	ldr r2, _02001D28 ; =0x000005DC
	add r1, r5, #0x0
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001CDE
	mov r0, #0x2
	strb r0, [r4, #0x1b]
_02001CDE:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001CE4:
	mov r1, #0x20
	tst r1, r2
	beq _02001D00
	ldr r2, _02001D28 ; =0x000005DC
	mov r1, #0x2
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001CFA
	mov r0, #0x3
	strb r0, [r4, #0x1b]
_02001CFA:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001D00:
	mov r1, #0x10
	tst r2, r1
	beq _02001D1C
	ldr r2, _02001D28 ; =0x000005DC
	mov r1, #0x3
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001D16
	mov r0, #0x4
	strb r0, [r4, #0x1b]
_02001D16:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
_02001D1C:
	sub r1, #0x11
	add r0, r1, #0x0
	pop {r3-r5, pc}
	nop
_02001D24: .word 0x021C48B8
_02001D28: .word 0x000005DC

	thumb_func_start FUN_02001D2C
FUN_02001D2C: ; 0x02001D2C
	push {r4-r6, lr}
	add r2, r1, #0x0
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r3, _02001DD4 ; =0x021C48B8
	strb r1, [r4, #0x1b]
	ldr r5, [r3, #0x48]
	mov r3, #0x1
	add r6, r5, #0x0
	tst r6, r3
	beq _02001D54
	ldr r0, _02001DD8 ; =0x000005DC
	bl FUN_020054C8
	ldrb r0, [r4, #0x15]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	pop {r4-r6, pc}
_02001D54:
	ldr r6, [r4, #0x10]
	tst r6, r5
	beq _02001D66
	ldr r0, _02001DD8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x1
	mvn r0, r0
	pop {r4-r6, pc}
_02001D66:
	mov r6, #0x40
	tst r6, r5
	beq _02001D7E
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001D78
	mov r0, #0x1
	strb r0, [r4, #0x1b]
_02001D78:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001D7E:
	mov r1, #0x80
	tst r1, r5
	beq _02001D98
	add r1, r3, #0x0
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001D92
	mov r0, #0x2
	strb r0, [r4, #0x1b]
_02001D92:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001D98:
	mov r1, #0x20
	tst r1, r5
	beq _02001DB2
	mov r1, #0x2
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001DAC
	mov r0, #0x3
	strb r0, [r4, #0x1b]
_02001DAC:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001DB2:
	mov r1, #0x10
	add r3, r5, #0x0
	tst r3, r1
	beq _02001DCE
	mov r1, #0x3
	bl FUN_02001E64
	cmp r0, #0x1
	bne _02001DC8
	mov r0, #0x4
	strb r0, [r4, #0x1b]
_02001DC8:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}
_02001DCE:
	sub r1, #0x11
	add r0, r1, #0x0
	pop {r4-r6, pc}
	.balign 4
_02001DD4: .word 0x021C48B8
_02001DD8: .word 0x000005DC

	thumb_func_start FUN_02001DDC
FUN_02001DDC: ; 0x02001DDC
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x5
	bhi _02001E52
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02001DF0: ; jump table (using 16-bit offset)
	.short _02001DFC - _02001DF0 - 2; case 0
	.short _02001E0E - _02001DF0 - 2; case 1
	.short _02001E1A - _02001DF0 - 2; case 2
	.short _02001E28 - _02001DF0 - 2; case 3
	.short _02001E36 - _02001DF0 - 2; case 4
	.short _02001E44 - _02001DF0 - 2; case 5
_02001DFC:
	ldr r0, _02001E58 ; =0x000005DC
	bl FUN_020054C8
	ldrb r0, [r4, #0x15]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldr r0, [r0, #0x4]
	pop {r4, pc}
_02001E0E:
	ldr r0, _02001E58 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x1
	mvn r0, r0
	pop {r4, pc}
_02001E1A:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x0
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E28:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x1
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E36:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x2
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E44:
	ldr r2, _02001E58 ; =0x000005DC
	mov r1, #0x3
	bl FUN_02001E64
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_02001E52:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
	.balign 4
_02001E58: .word 0x000005DC

	thumb_func_start FUN_02001E5C
FUN_02001E5C: ; 0x02001E5C
	ldrb r0, [r0, #0x15]
	bx lr

	thumb_func_start FUN_02001E60
FUN_02001E60: ; 0x02001E60
	ldrb r0, [r0, #0x1b]
	bx lr

	thumb_func_start FUN_02001E64
FUN_02001E64: ; 0x02001E64
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldrb r4, [r5, #0x15]
	bl FUN_02001EBC
	cmp r0, #0x0
	bne _02001E7C
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02001E7C:
	ldrb r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_02002E4C
	add r1, sp, #0x8
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	add r2, sp, #0x8
	add r3, r4, #0x0
	bl FUN_020020B0
	mov r0, #0x8
	str r0, [sp, #0x0]
	ldrb r0, [r5, #0x1a]
	add r3, sp, #0x8
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	ldr r0, [r5, #0x4]
	bl FUN_020196F4
	add r0, r5, #0x0
	bl FUN_02002080
	add r0, r6, #0x0
	bl FUN_020054C8
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02001EBC
FUN_02001EBC: ; 0x02001EBC
	push {r4-r6, lr}
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _02001EFA
	ldrb r6, [r5, #0xa]
	cmp r6, #0x1
	bhi _02001ECE
	mov r0, #0x0
	pop {r4-r6, pc}
_02001ECE:
	ldrb r4, [r5, #0x15]
	add r1, r6, #0x0
	add r0, r4, #0x0
	bl _s32_div_f
	cmp r1, #0x0
	bne _02001EF2
	ldrb r0, [r5, #0xb]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _02001EE8
	mov r0, #0x0
	pop {r4-r6, pc}
_02001EE8:
	sub r0, r6, #0x1
	add r0, r4, r0
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001EF2:
	sub r0, r4, #0x1
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001EFA:
	cmp r1, #0x1
	bne _02001F32
	ldrb r1, [r5, #0xa]
	cmp r1, #0x1
	bhi _02001F08
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F08:
	ldrb r6, [r5, #0x15]
	sub r4, r1, #0x1
	add r0, r6, #0x0
	bl _s32_div_f
	cmp r4, r1
	bne _02001F2A
	ldrb r0, [r5, #0xb]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _02001F22
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F22:
	sub r0, r6, r4
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F2A:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F32:
	cmp r1, #0x2
	bne _02001F68
	ldrb r3, [r5, #0x9]
	cmp r3, #0x1
	bhi _02001F40
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F40:
	ldrb r2, [r5, #0xa]
	ldrb r1, [r5, #0x15]
	cmp r1, r2
	bhs _02001F60
	ldrb r0, [r5, #0xb]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	bne _02001F54
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F54:
	sub r0, r3, #0x1
	mul r0, r2
	add r0, r1, r0
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F60:
	sub r0, r1, r2
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F68:
	ldrb r2, [r5, #0x9]
	cmp r2, #0x1
	bhi _02001F72
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F72:
	ldrb r1, [r5, #0xa]
	ldrb r0, [r5, #0x15]
	sub r2, r2, #0x1
	mul r2, r1
	cmp r0, r2
	blt _02001F94
	ldrb r2, [r5, #0xb]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1e
	bne _02001F8A
	mov r0, #0x0
	pop {r4-r6, pc}
_02001F8A:
	bl _s32_div_f
	lsl r0, r1, #0x18
	asr r2, r0, #0x18
	b _02001F9A
_02001F94:
	add r0, r0, r1
	lsl r0, r0, #0x18
	asr r2, r0, #0x18
_02001F9A:
	ldr r1, [r5, #0x0]
	lsl r0, r2, #0x3
	add r0, r1, r0
	ldr r1, [r0, #0x4]
	mov r0, #0x2
	mvn r0, r0
	cmp r1, r0
	bne _02001FAE
	mov r0, #0x0
	pop {r4-r6, pc}
_02001FAE:
	strb r2, [r5, #0x15]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_02001FB4
FUN_02001FB4: ; 0x02001FB4
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrb r1, [r5, #0x9]
	ldrb r0, [r5, #0xa]
	mov r6, #0x0
	add r4, r6, #0x0
	mul r0, r1
	cmp r0, #0x0
	ble _02001FF0
	add r7, r6, #0x0
_02001FC8:
	ldr r2, [r5, #0x0]
	lsl r1, r4, #0x3
	ldr r1, [r2, r1]
	ldrb r0, [r5, #0x8]
	add r2, r7, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r6, r0
	bhs _02001FE0
	add r6, r0, #0x0
_02001FE0:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldrb r1, [r5, #0x9]
	ldrb r0, [r5, #0xa]
	mul r0, r1
	cmp r4, r0
	blt _02001FC8
_02001FF0:
	add r0, r6, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02001FF4
FUN_02001FF4: ; 0x02001FF4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldrb r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_02002E4C
	add r1, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FUN_02019620
	ldrb r0, [r5, #0x19]
	ldrb r1, [r5, #0x16]
	ldrb r7, [r5, #0x17]
	lsl r0, r0, #0x1
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldrb r0, [r5, #0x9]
	mov r6, #0x0
	cmp r0, #0x0
	bls _0200207C
_02002022:
	ldrb r2, [r5, #0xa]
	mov r4, #0x0
	cmp r2, #0x0
	bls _02002068
_0200202A:
	ldrb r3, [r5, #0xb]
	mul r2, r6
	ldrb r0, [r5, #0x1a]
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x1c
	add r0, r0, r3
	ldrb r1, [r5, #0x18]
	mul r0, r4
	add r2, r4, r2
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r3, [r5, #0x0]
	lsl r2, r2, #0x3
	ldr r2, [r3, r2]
	ldrb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	add r3, r7, #0x0
	bl FUN_0201BD84
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	ldrb r2, [r5, #0xa]
	lsr r4, r0, #0x18
	cmp r4, r2
	blo _0200202A
_02002068:
	ldr r0, [sp, #0xc]
	add r0, r7, r0
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrb r0, [r5, #0x9]
	cmp r6, r0
	blo _02002022
_0200207C:
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_02002080
FUN_02002080: ; 0x02002080
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldrb r1, [r4, #0xb]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1e
	cmp r1, #0x1
	beq _020020AA
	ldrb r3, [r4, #0x15]
	add r1, sp, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_020020B0
	add r3, sp, #0x0
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x4]
	bl FUN_020136F8
_020020AA:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020020B0
FUN_020020B0: ; 0x020020B0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r3, #0x0
	ldrb r1, [r5, #0xa]
	add r0, r7, #0x0
	add r6, r2, #0x0
	bl _s32_div_f
	ldrb r2, [r5, #0x19]
	ldrb r1, [r5, #0x16]
	lsl r2, r2, #0x1
	add r1, r1, r2
	mul r1, r0
	strb r1, [r4, #0x0]
	ldrb r1, [r5, #0xa]
	add r0, r7, #0x0
	bl _s32_div_f
	ldrb r2, [r5, #0xb]
	ldrb r3, [r5, #0x1a]
	ldrb r0, [r5, #0x18]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	add r2, r3, r2
	mul r2, r1
	add r0, r0, r2
	strb r0, [r6, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020020EC
FUN_020020EC: ; 0x020020EC
	push {r3-r7, lr}
	sub sp, #0x20
	ldr r5, [sp, #0x3c]
	str r2, [sp, #0xc]
	add r7, r0, #0x0
	str r1, [sp, #0x8]
	str r3, [sp, #0x10]
	ldr r2, _02002194 ; =0x00000141
	mov r0, #0x1
	mov r1, #0x1a
	add r3, r5, #0x0
	bl FUN_0200A86C
	add r4, r0, #0x0
	mov r0, #0x2
	add r1, r5, #0x0
	bl FUN_02012838
	add r1, r4, #0x0
	mov r2, #0x29
	mov r3, #0x0
	add r6, r0, #0x0
	bl FUN_02012880
	mov r3, #0x2a
	add r2, r3, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	sub r3, #0x2c
	bl FUN_02012880
	add r0, r4, #0x0
	bl FUN_0200A8B8
	add r0, r5, #0x0
	mov r1, #0x1
	str r6, [sp, #0x14]
	bl FUN_02018FF4
	add r1, r0, #0x0
	str r1, [sp, #0x18]
	mov r0, #0x0
	add r3, sp, #0x14
	strb r0, [r3, #0x8]
	mov r0, #0x1
	strb r0, [r3, #0x9]
	mov r0, #0x2
	strb r0, [r3, #0xa]
	ldrb r0, [r3, #0xb]
	mov r2, #0xf
	bic r0, r2
	strb r0, [r3, #0xb]
	ldrb r4, [r3, #0xb]
	mov r0, #0x30
	bic r4, r0
	strb r4, [r3, #0xb]
	ldrb r0, [r3, #0xb]
	bic r0, r2
	strb r0, [r3, #0xb]
	ldr r2, [sp, #0x8]
	add r0, r7, #0x0
	bl FUN_02019150
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	mov r1, #0x1
	bl FUN_0200CCA4
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r3, sp, #0x28
	ldrb r3, [r3, #0x10]
	add r0, sp, #0x14
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_02001C14
	add sp, #0x20
	pop {r3-r7, pc}
	nop
_02002194: .word 0x00000141

	thumb_func_start FUN_02002198
FUN_02002198: ; 0x02002198
	push {r4, lr}
	sub sp, #0x8
	mov r4, #0x0
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x4]
	bl FUN_020020EC
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_020021AC
FUN_020021AC: ; 0x020021AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02001C78
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _020021C8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020021EC
_020021C8:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020021CC
FUN_020021CC: ; 0x020021CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02001DDC
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _020021E8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020021EC
_020021E8:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020021EC
FUN_020021EC: ; 0x020021EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_0200CCF8
	ldr r0, [r5, #0x4]
	bl FUN_02019178
	ldr r1, [r5, #0x4]
	add r0, r4, #0x0
	bl FUN_02016A8C
	ldr r0, [r5, #0x0]
	bl FUN_02012870
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02001C5C
	pop {r3-r5, pc}

	thumb_func_start FUN_02002218
FUN_02002218: ; 0x02002218
	push {r4, lr}
	sub sp, #0x18
	mov r4, #0x8
	lsl r1, r1, #0x10
	str r4, [sp, #0x0]
	mov r3, #0x10
	str r3, [sp, #0x4]
	lsr r1, r1, #0x10
	str r1, [sp, #0x8]
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0xc]
	str r4, [sp, #0x10]
	ldr r1, _02002244 ; =0x020ECAC8
	mov r2, #0x0
	str r3, [sp, #0x14]
	add r3, r2, #0x0
	bl FUN_02019658
	add sp, #0x18
	pop {r4, pc}
	nop
_02002244: .word 0x020ECAC8
