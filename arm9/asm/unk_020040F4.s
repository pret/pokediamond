	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_020040F4
FUN_020040F4: ; 0x020040F4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x5
	bl FUN_02003D38
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004104
FUN_02004104: ; 0x02004104
	push {r3, lr}
	mov r0, #0x5
	bl FUN_02003D38
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02004110
FUN_02004110: ; 0x02004110
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x9
	bl FUN_02003D38
	strh r4, [r0, #0x0]
	mov r0, #0x0
	bl FUN_02004130
	pop {r4, pc}

	thumb_func_start FUN_02004124
FUN_02004124: ; 0x02004124
	push {r3, lr}
	mov r0, #0x9
	bl FUN_02003D38
	ldrh r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02004130
FUN_02004130: ; 0x02004130
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xa
	bl FUN_02003D38
	strh r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004140
FUN_02004140: ; 0x02004140
	push {r3, lr}
	mov r0, #0xa
	bl FUN_02003D38
	ldrh r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0200414C
FUN_0200414C: ; 0x0200414C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1f
	bl FUN_02003D38
	strh r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200415C
FUN_0200415C: ; 0x0200415C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x14
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x15
	bl FUN_02003D38
	cmp r5, #0x33
	bhs _0200417A
	strb r5, [r4, #0x0]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200417A:
	strb r5, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02004180
FUN_02004180: ; 0x02004180
	push {r3, lr}
	cmp r0, #0x39
	bgt _020041DE
	blt _0200418A
	b _020042C8
_0200418A:
	cmp r0, #0x35
	bgt _020041CC
	blt _02004192
	b _0200429A
_02004192:
	cmp r0, #0x33
	bgt _020041C6
	bge _0200427C
	cmp r0, #0xe
	bhi _020041CA
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_020041A8: ; jump table (using 16-bit offset)
	.short _0200432C - _020041A8 - 2; case 0
	.short _02004222 - _020041A8 - 2; case 1
	.short _0200422C - _020041A8 - 2; case 2
	.short _02004236 - _020041A8 - 2; case 3
	.short _02004240 - _020041A8 - 2; case 4
	.short _0200424A - _020041A8 - 2; case 5
	.short _0200425E - _020041A8 - 2; case 6
	.short _0200429A - _020041A8 - 2; case 7
	.short _02004268 - _020041A8 - 2; case 8
	.short _02004222 - _020041A8 - 2; case 9
	.short _02004222 - _020041A8 - 2; case 10
	.short _02004254 - _020041A8 - 2; case 11
	.short _02004272 - _020041A8 - 2; case 12
	.short _0200422C - _020041A8 - 2; case 13
	.short _02004222 - _020041A8 - 2; case 14
_020041C6:
	cmp r0, #0x34
	beq _02004290
_020041CA:
	b _0200432C
_020041CC:
	cmp r0, #0x37
	bgt _020041D8
	bge _020042AE
	cmp r0, #0x36
	beq _020042A4
	b _0200432C
_020041D8:
	cmp r0, #0x38
	beq _020042BE
	b _0200432C
_020041DE:
	cmp r0, #0x3d
	bgt _020041F8
	blt _020041E6
	b _020042F0
_020041E6:
	cmp r0, #0x3b
	bgt _020041F2
	bge _020042DC
	cmp r0, #0x3a
	beq _020042D2
	b _0200432C
_020041F2:
	cmp r0, #0x3c
	beq _020042E6
	b _0200432C
_020041F8:
	cmp r0, #0x3f
	bgt _02004206
	blt _02004200
	b _02004304
_02004200:
	cmp r0, #0x3e
	beq _020042FA
	b _0200432C
_02004206:
	sub r0, #0x40
	cmp r0, #0x3
	bls _0200420E
	b _0200432C
_0200420E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200421A: ; jump table (using 16-bit offset)
	.short _0200430E - _0200421A - 2; case 0
	.short _0200431E - _0200421A - 2; case 1
	.short _02004286 - _0200421A - 2; case 2
	.short _020042AE - _0200421A - 2; case 3
_02004222:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200422C:
	mov r0, #0x2
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004236:
	mov r0, #0xd
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004240:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200424A:
	mov r0, #0x2
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004254:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200425E:
	mov r0, #0xb
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004268:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004272:
	mov r0, #0xe
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200427C:
	mov r0, #0x3
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004286:
	mov r0, #0x6
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004290:
	mov r0, #0x5
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200429A:
	mov r0, #0x9
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042A4:
	mov r0, #0xa
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042AE:
	ldr r0, _02004330 ; =0x000005E5
	bl FUN_02003FDC
	ldr r0, _02004330 ; =0x000005E5
	bl FUN_02003FC4
	add r1, r0, #0x0
	b _0200432C
_020042BE:
	mov r0, #0xc
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042C8:
	mov r0, #0x7
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042D2:
	mov r0, #0x8
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042DC:
	mov r0, #0xf
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042E6:
	mov r0, #0x3
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042F0:
	mov r0, #0x5
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042FA:
	mov r0, #0xf
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004304:
	mov r0, #0x4
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200430E:
	ldr r0, _02004334 ; =0x000005ED
	bl FUN_02003FDC
	ldr r0, _02004334 ; =0x000005ED
	bl FUN_02003FC4
	add r1, r0, #0x0
	b _0200432C
_0200431E:
	ldr r0, _02004338 ; =0x000005EC
	bl FUN_02003FDC
	ldr r0, _02004338 ; =0x000005EC
	bl FUN_02003FC4
	add r1, r0, #0x0
_0200432C:
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4
_02004330: .word 0x000005E5
_02004334: .word 0x000005ED
_02004338: .word 0x000005EC

	thumb_func_start FUN_0200433C
FUN_0200433C: ; 0x0200433C
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0x14
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02003D38
	str r0, [sp, #0x0]
	mov r0, #0x15
	bl FUN_02003D38
	str r0, [sp, #0x4]
	mov r0, #0xd
	bl FUN_02003D38
	add r7, r0, #0x0
	cmp r4, #0x33
	bhs _02004370
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x0]
	cmp r0, r4
	bne _0200437E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_02004370:
	ldr r0, [sp, #0x4]
	ldrb r0, [r0, #0x0]
	cmp r0, r4
	bne _0200437E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0200437E:
	add r0, r4, #0x0
	bl FUN_0200415C
	cmp r4, #0x39
	bgt _020043DC
	bge _02004458
	cmp r4, #0x35
	bgt _020043CA
	bge _02004458
	cmp r4, #0x33
	bgt _020043C4
	bge _02004458
	cmp r4, #0xe
	bhi _020043C8
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020043A6: ; jump table (using 16-bit offset)
	.short _020044A0 - _020043A6 - 2; case 0
	.short _02004460 - _020043A6 - 2; case 1
	.short _02004484 - _020043A6 - 2; case 2
	.short _02004496 - _020043A6 - 2; case 3
	.short _0200441C - _020043A6 - 2; case 4
	.short _02004430 - _020043A6 - 2; case 5
	.short _02004444 - _020043A6 - 2; case 6
	.short _0200444E - _020043A6 - 2; case 7
	.short _02004496 - _020043A6 - 2; case 8
	.short _02004496 - _020043A6 - 2; case 9
	.short _02004496 - _020043A6 - 2; case 10
	.short _0200443A - _020043A6 - 2; case 11
	.short _02004496 - _020043A6 - 2; case 12
	.short _02004496 - _020043A6 - 2; case 13
	.short _02004472 - _020043A6 - 2; case 14
_020043C4:
	cmp r4, #0x34
	beq _02004458
_020043C8:
	b _020044A0
_020043CA:
	cmp r4, #0x37
	bgt _020043D6
	bge _02004458
	cmp r4, #0x36
	beq _02004458
	b _020044A0
_020043D6:
	cmp r4, #0x38
	beq _02004458
	b _020044A0
_020043DC:
	cmp r4, #0x3d
	bgt _020043F4
	bge _02004458
	cmp r4, #0x3b
	bgt _020043EE
	bge _02004458
	cmp r4, #0x3a
	beq _02004458
	b _020044A0
_020043EE:
	cmp r4, #0x3c
	beq _02004458
	b _020044A0
_020043F4:
	cmp r4, #0x3f
	bgt _02004400
	bge _02004458
	cmp r4, #0x3e
	beq _02004458
	b _020044A0
_02004400:
	add r0, r4, #0x0
	sub r0, #0x40
	cmp r0, #0x3
	bhi _020044A0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02004414: ; jump table (using 16-bit offset)
	.short _02004458 - _02004414 - 2; case 0
	.short _02004458 - _02004414 - 2; case 1
	.short _02004458 - _02004414 - 2; case 2
	.short _02004458 - _02004414 - 2; case 3
_0200441C:
	mov r0, #0x0
	bl FUN_0200516C
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020044D4
	mov r0, #0x0
	strh r0, [r7, #0x0]
	b _020044A0
_02004430:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02004648
	b _020044A0
_0200443A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02004680
	b _020044A0
_02004444:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020046A0
	b _020044A0
_0200444E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020046C4
	b _020044A0
_02004458:
	add r0, r4, #0x0
	bl FUN_020046E8
	b _020044A0
_02004460:
	mov r0, #0x1
	bl FUN_0200516C
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
	b _020044A0
_02004472:
	mov r0, #0x2
	bl FUN_0200516C
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
	b _020044A0
_02004484:
	mov r0, #0x0
	bl FUN_0200516C
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
	b _020044A0
_02004496:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
_020044A0:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020044A8
FUN_020044A8: ; 0x020044A8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	ldr r0, [r0, #0x0]
	bl FUN_02003F64
	mov r0, #0x18
	bl FUN_02003D38
	bl FUN_02003F3C
	add r0, r4, #0x0
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	pop {r4, pc}

	thumb_func_start FUN_020044D4
FUN_020044D4: ; 0x020044D4
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	mov r0, #0x1f
	bl FUN_02003D38
	mov r0, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	add r4, r0, #0x0
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	bne _0200450E
	cmp r4, r5
	bne _0200450E
	bl FUN_02004140
	mov r1, #0x12
	lsl r1, r1, #0x6
	cmp r0, r1
	bne _02004566
_0200450E:
	mov r0, #0x1
	bl FUN_02004DBC
	bl FUN_02005454
	cmp r4, r5
	beq _02004528
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020047C8
	bl FUN_0200541C
_02004528:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02004560
	mov r0, #0x2
	bl FUN_02004748
	bl FUN_02003F64
	mov r0, #0x4
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	cmp r4, r5
	beq _02004554
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020047C8
_02004554:
	lsl r1, r4, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_02004568
	pop {r4-r6, pc}
_02004560:
	add r0, r5, #0x0
	bl FUN_0200521C
_02004566:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004568
FUN_02004568: ; 0x02004568
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1f
	bl FUN_02003D38
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_02004900
	ldr r1, _020045C0 ; =0x000003E9
	cmp r0, r1
	beq _02004594
	add r1, r1, #0x2
	cmp r0, r1
	beq _02004594
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02003FA8
	bl ErrorHandling
	b _0200459C
_02004594:
	ldrh r0, [r4, #0x0]
	mov r1, #0x6
	bl FUN_02003FA8
_0200459C:
	mov r0, #0x1a
	bl FUN_02003D38
	bl FUN_02003F3C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020047C8
	mov r0, #0x7f
	mov r1, #0x28
	mov r2, #0x0
	bl FUN_0200538C
	mov r0, #0x0
	bl FUN_02004DBC
	pop {r3-r5, pc}
	.balign 4
_020045C0: .word 0x000003E9

	thumb_func_start FUN_020045C4
FUN_020045C4: ; 0x020045C4
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r0, #0x12
	add r5, r1, #0x0
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x1f
	bl FUN_02003D38
	add r4, r0, #0x0
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	beq _020045E4
	cmp r5, #0x0
	bne _02004642
_020045E4:
	mov r0, #0x1
	bl FUN_02004748
	bl FUN_02003F64
	ldrh r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02003FA8
	mov r0, #0x18
	bl FUN_02003D38
	bl FUN_02003F3C
	mov r0, #0x4
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	ldrh r0, [r4, #0x0]
	bl FUN_02004900
	ldr r1, _02004644 ; =0x000003E9
	cmp r0, r1
	beq _02004630
	add r1, r1, #0x2
	cmp r0, r1
	beq _02004630
	add r0, r7, #0x0
	mov r1, #0x4
	bl FUN_02003FA8
	bl ErrorHandling
	b _02004638
_02004630:
	ldrh r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_02003FA8
_02004638:
	mov r0, #0x1a
	bl FUN_02003D38
	bl FUN_02003F3C
_02004642:
	pop {r3-r7, pc}
	.balign 4
_02004644: .word 0x000003E9

	thumb_func_start FUN_02004648
FUN_02004648: ; 0x02004648
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_020051AC
	mov r0, #0x2
	bl FUN_02004748
	bl FUN_02003F64
	mov r0, #0x5
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	mov r0, #0x1
	bl FUN_02004DBC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004680
FUN_02004680: ; 0x02004680
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_0200541C
	bl FUN_02004810
	mov r0, #0x4
	bl FUN_020044A8
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}

	thumb_func_start FUN_020046A0
FUN_020046A0: ; 0x020046A0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_0200541C
	mov r0, #0x6
	bl FUN_020044A8
	mov r0, #0x1
	bl FUN_02004DBC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020046C4
FUN_020046C4: ; 0x020046C4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_0200541C
	mov r0, #0x7
	bl FUN_020044A8
	mov r0, #0x1
	bl FUN_02004DBC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020046E8
FUN_020046E8: ; 0x020046E8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02004738
	add r0, r4, #0x0
	bl FUN_02004180
	mov r0, #0x1b
	bl FUN_02003D38
	bl FUN_02003F3C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004704
FUN_02004704: ; 0x02004704
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x17
	add r4, r1, #0x0
	bl FUN_02003D38
	bl FUN_0200541C
	add r0, r5, #0x0
	bl FUN_020044A8
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02004724
FUN_02004724: ; 0x02004724
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	bl FUN_020051AC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}

	thumb_func_start FUN_02004738
FUN_02004738: ; 0x02004738
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02004748
	bl FUN_02003F64
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004748
FUN_02004748: ; 0x02004748
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	cmp r4, #0x7
	blt _02004762
	bl ErrorHandling
	mov r0, #0x1a
	bl FUN_02003D38
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
_02004762:
	cmp r4, #0x6
	bhi _020047C4
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02004772: ; jump table (using 16-bit offset)
	.short _02004780 - _02004772 - 2; case 0
	.short _0200478A - _02004772 - 2; case 1
	.short _02004794 - _02004772 - 2; case 2
	.short _0200479E - _02004772 - 2; case 3
	.short _020047A8 - _02004772 - 2; case 4
	.short _020047B2 - _02004772 - 2; case 5
	.short _020047BC - _02004772 - 2; case 6
_02004780:
	mov r0, #0x16
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_0200478A:
	mov r0, #0x17
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_02004794:
	mov r0, #0x18
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_0200479E:
	mov r0, #0x19
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_020047A8:
	mov r0, #0x1a
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_020047B2:
	mov r0, #0x1b
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_020047BC:
	mov r0, #0x1c
	bl FUN_02003D38
	add r5, r0, #0x0
_020047C4:
	ldr r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_020047C8
FUN_020047C8: ; 0x020047C8
	push {r4-r6, lr}
	add r5, r1, #0x0
	cmp r0, #0x1
	bne _020047DC
	mov r0, #0xb
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r4, #0x0
	b _020047EA
_020047DC:
	cmp r0, #0x7
	bne _0200480E
	mov r0, #0xc
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r4, #0x7
_020047EA:
	cmp r5, #0x0
	bne _02004800
	add r0, r4, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02004110
_02004800:
	add r0, r4, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	bl FUN_020C0F8C
	strb r5, [r6, #0x0]
_0200480E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004810
FUN_02004810: ; 0x02004810
	push {r4, lr}
	mov r0, #0xb
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0xc
	bl FUN_02003D38
	mov r1, #0x0
	strb r1, [r4, #0x0]
	strb r1, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02004828
FUN_02004828: ; 0x02004828
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020C0EF4
	pop {r3-r5, pc}

	thumb_func_start FUN_0200483C
FUN_0200483C: ; 0x0200483C
	push {r4, lr}
	add r4, r1, #0x0
	bpl _02004844
	mov r4, #0x0
_02004844:
	cmp r4, #0x7f
	ble _0200484A
	mov r4, #0x7f
_0200484A:
	bl FUN_02003FF4
	add r1, r4, #0x0
	bl FUN_020C0F30
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004858
FUN_02004858: ; 0x02004858
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_020C23FC
	cmp r5, #0x1
	beq _02004868
	cmp r5, #0x8
	bne _0200486C
_02004868:
	mov r4, #0x7f
	b _02004872
_0200486C:
	cmp r0, #0x0
	beq _0200488A
	ldrb r4, [r0, #0x2]
_02004872:
	bl FUN_020313EC
	cmp r0, #0x1
	bne _0200488A
	add r0, r4, #0x0
	mov r1, #0x5
	bl _s32_div_f
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200483C
_0200488A:
	pop {r3-r5, pc}

	thumb_func_start FUN_0200488C
FUN_0200488C: ; 0x0200488C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r1, r4, #0x0
	bl FUN_0200483C
	pop {r4, pc}

	thumb_func_start FUN_020048A0
FUN_020048A0: ; 0x020048A0
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	mov r2, #0x0
	mvn r2, r2
	add r1, r5, #0x0
	add r3, r2, #0x0
	str r4, [sp, #0x0]
	bl FUN_020C3910
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020048BC
FUN_020048BC: ; 0x020048BC
	push {r4, lr}
	add r4, r0, #0x0
	bpl _020048C6
	bl ErrorHandling
_020048C6:
	add r0, r4, #0x0
	bl FUN_020C0F50
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020048D0
FUN_020048D0: ; 0x020048D0
	push {r3, lr}
	cmp r0, #0x0
	bne _020048DA
	mov r0, #0xff
	pop {r3, pc}
_020048DA:
	bl FUN_020C23FC
	cmp r0, #0x0
	bne _020048E6
	mov r0, #0xff
	pop {r3, pc}
_020048E6:
	ldrb r0, [r0, #0x5]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020048EC
FUN_020048EC: ; 0x020048EC
	ldr r3, _020048F0 ; =FUN_020C0E14
	bx r3
	.balign 4
_020048F0: .word FUN_020C0E14

	thumb_func_start FUN_020048F4
FUN_020048F4: ; 0x020048F4
	push {r3, lr}
	bl FUN_02004900
	bl FUN_020C22D0
	pop {r3, pc}

	thumb_func_start FUN_02004900
FUN_02004900: ; 0x02004900
	push {r3, lr}
	bl FUN_020C23FC
	cmp r0, #0x0
	bne _0200490E
	mov r0, #0x0
	pop {r3, pc}
_0200490E:
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004914
FUN_02004914: ; 0x02004914
	ldr r3, _02004918 ; =MIC_StartAutoSampling
	bx r3
	.balign 4
_02004918: .word MIC_StartAutoSampling

	thumb_func_start FUN_0200491C
FUN_0200491C: ; 0x0200491C
	push {r3, lr}
	bl FUN_02003D30
	bl MIC_StopAutoSampling
	pop {r3, pc}

	thumb_func_start FUN_02004928
FUN_02004928: ; 0x02004928
	push {r3, lr}
	bl MIC_DoSamplingAsync
	pop {r3, pc}

	thumb_func_start FUN_02004930
FUN_02004930: ; 0x02004930
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _02004954
	cmp r5, #0xf
	beq _02004954
	bl ErrorHandling
_02004954:
	cmp r5, #0xe
	bne _02004962
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02004962
	bl ErrorHandling
_02004962:
	cmp r5, #0xf
	bne _02004970
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02004970
	bl ErrorHandling
_02004970:
	cmp r5, #0xe
	bne _0200497C
	mov r0, #0x0
	bl FUN_02003D38
	pop {r4-r6, pc}
_0200497C:
	mov r0, #0x1
	bl FUN_02003D38
	pop {r4-r6, pc}

	thumb_func_start FUN_02004984
FUN_02004984: ; 0x02004984
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _020049A8
	cmp r5, #0xf
	beq _020049A8
	bl ErrorHandling
_020049A8:
	cmp r5, #0xe
	bne _020049D6
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	bne _020049D0
	mov r0, #0x0
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020C0688
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020049CA
	mov r0, #0x0
	pop {r4-r6, pc}
_020049CA:
	mov r0, #0x1
	strb r0, [r6, #0x0]
	b _020049FE
_020049D0:
	bl ErrorHandling
	b _020049FE
_020049D6:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020049FA
	mov r0, #0x1
	bl FUN_02003D38
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020C0688
	str r0, [r6, #0x0]
	cmp r0, #0x0
	bne _020049F4
	mov r0, #0x0
	pop {r4-r6, pc}
_020049F4:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	b _020049FE
_020049FA:
	bl ErrorHandling
_020049FE:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02004A04
FUN_02004A04: ; 0x02004A04
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _02004A2A
	cmp r5, #0xf
	beq _02004A2A
	bl ErrorHandling
	pop {r4-r6, pc}
_02004A2A:
	cmp r5, #0xe
	bne _02004A4C
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02004A46
	add r0, r5, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	bl FUN_020C0670
	mov r0, #0x0
	strb r0, [r6, #0x0]
	pop {r4-r6, pc}
_02004A46:
	bl ErrorHandling
	pop {r4-r6, pc}
_02004A4C:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _02004A64
	add r0, r5, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	bl FUN_020C0670
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r4-r6, pc}
_02004A64:
	bl ErrorHandling
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02004A6C
FUN_02004A6C: ; 0x02004A6C
	push {r3-r5, lr}
	sub sp, #0x18
	add r3, r0, #0x0
	ldr r0, [r3, #0x10]
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r3, #0x14]
	str r0, [sp, #0x4]
	ldr r0, [r3, #0x18]
	str r0, [sp, #0x8]
	ldr r0, [r3, #0x1c]
	str r0, [sp, #0xc]
	ldr r0, [r3, #0x20]
	str r0, [sp, #0x10]
	ldr r0, [r3, #0x24]
	str r0, [sp, #0x14]
	ldr r0, [r3, #0x0]
	ldr r1, [r3, #0x4]
	ldr r2, [r3, #0x8]
	ldr r0, [r0, #0x0]
	ldr r3, [r3, #0xc]
	bl FUN_020C054C
	add r5, r0, #0x0
	bne _02004AA4
	add r0, r4, #0x0
	bl FUN_02004A04
_02004AA4:
	add r0, r5, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02004AAC
FUN_02004AAC: ; 0x02004AAC
	push {r3, lr}
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	bl FUN_020C0510
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004ABC
FUN_02004ABC: ; 0x02004ABC
	push {r3, lr}
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	bl FUN_020C03B8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004ACC
FUN_02004ACC: ; 0x02004ACC
	push {r4, lr}
	add r4, r1, #0x0
	cmp r4, #0x7f
	bls _02004AD6
	mov r4, #0x7f
_02004AD6:
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_020C041C
	pop {r4, pc}

	thumb_func_start FUN_02004AE4
FUN_02004AE4: ; 0x02004AE4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_020C044C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004AF8
FUN_02004AF8: ; 0x02004AF8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020313EC
	cmp r0, #0x1
	bne _02004B20
	add r0, r4, #0x0
	bl FUN_02004930
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	bl _s32_div_f
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020C04DC
	pop {r3-r5, pc}
_02004B20:
	add r0, r4, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	bl FUN_020C04DC
	pop {r3-r5, pc}

	thumb_func_start FUN_02004B30
FUN_02004B30: ; 0x02004B30
	push {r3-r7, lr}
	sub sp, #0x30
	add r6, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r5, r3, #0x0
	bl FUN_02003D30
	mov r0, #0x21
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _02004B54
	cmp r5, #0xf
	beq _02004B54
	bl ErrorHandling
_02004B54:
	add r0, r6, #0x0
	bl FUN_020C226C
	add r7, r0, #0x0
	bne _02004B68
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004B68:
	ldr r0, [r7, #0x0]
	lsl r0, r0, #0x8
	lsr r0, r0, #0x8
	bl FUN_020C217C
	add r6, r0, #0x0
	bne _02004B80
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004B80:
	cmp r5, #0xe
	bne _02004BCE
	ldr r0, [sp, #0x48]
	add r1, r6, #0x0
	bl FUN_02016998
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02004B9C
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004B9C:
	mov r1, #0x0
	add r2, r6, #0x0
	bl Call_FillMemWithValue
	ldr r0, [r7, #0x0]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x8
	lsr r0, r0, #0x8
	add r2, r6, #0x0
	mov r3, #0x0
	bl FUN_020C2104
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _02004BC6
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004BC6:
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_02004C1C
_02004BCE:
	add r0, r5, #0x0
	bl FUN_02004930
	mov r1, #0x0
	str r1, [sp, #0xc]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x10]
	ldr r0, _02004C18 ; =0x00003443
	str r1, [sp, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x18]
	str r0, [sp, #0x24]
	mov r0, #0x6
	lsl r0, r0, #0xc
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x4]
	add r1, r5, #0x0
	str r0, [sp, #0x2c]
	add r0, sp, #0x8
	str r6, [sp, #0x1c]
	bl FUN_02004A6C
	add r4, r0, #0x0
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02004AF8
	mov r0, #0xe
	bl FUN_02003D38
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02004C18: .word 0x00003443

	thumb_func_start FUN_02004C1C
FUN_02004C1C: ; 0x02004C1C
	push {r3-r6}
	mov r5, #0x0
	lsr r6, r1, #0x1
	beq _02004C36
	sub r2, r1, #0x1
_02004C26:
	sub r3, r2, r5
	ldrb r4, [r0, r5]
	ldrb r1, [r0, r3]
	strb r1, [r0, r5]
	add r5, r5, #0x1
	strb r4, [r0, r3]
	cmp r5, r6
	blo _02004C26
_02004C36:
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02004C3C
FUN_02004C3C: ; 0x02004C3C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xe
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x21
	bl FUN_02003D38
	add r6, r0, #0x0
	cmp r5, #0xe
	beq _02004C60
	cmp r5, #0xf
	beq _02004C60
	bl ErrorHandling
_02004C60:
	add r0, r5, #0x0
	bl FUN_02004AAC
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _02004C76
	mov r0, #0x0
	strb r0, [r4, #0x0]
	ldr r0, [r6, #0x0]
	bl FUN_02016A18
_02004C76:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004C78
FUN_02004C78: ; 0x02004C78
	ldr r3, _02004C7C ; =FUN_020C1E58
	bx r3
	.balign 4
_02004C7C: .word FUN_020C1E58

	thumb_func_start FUN_02004C80
FUN_02004C80: ; 0x02004C80
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_02003D30
	mov r0, #0x3
	bl FUN_02003D38
	mov r1, #0x1
	mov r3, #0xfa
	lsl r1, r1, #0xc
	mov r2, #0x0
	lsl r3, r3, #0x6
	str r4, [sp, #0x0]
	bl FUN_020C1FF0
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02004CA4
FUN_02004CA4: ; 0x02004CA4
	ldr r3, _02004CA8 ; =FUN_020C1F54
	bx r3
	.balign 4
_02004CA8: .word FUN_020C1F54

	thumb_func_start FUN_02004CAC
FUN_02004CAC: ; 0x02004CAC
	ldr r3, _02004CB0 ; =FUN_020C1FA4
	bx r3
	.balign 4
_02004CB0: .word FUN_020C1FA4

	thumb_func_start FUN_02004CB4
FUN_02004CB4: ; 0x02004CB4
	push {r3-r4, lr}
	sub sp, #0xc
	bl FUN_02003D30
	mov r0, #0x4
	bl FUN_02003D38
	mov r1, #0x0
	mov r2, #0x1c
	bl MI_CpuFill8
	mov r0, #0x3
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x4
	bl FUN_02003D38
	mov r2, #0x2
	ldr r1, _02004CF4 ; =FUN_02005068
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	lsl r1, r2, #0xb
	ldr r3, _02004CF8 ; =0x000055F0
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_020C1EA4
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_02004CF4: .word FUN_02005068
_02004CF8: .word 0x000055F0

	thumb_func_start FUN_02004CFC
FUN_02004CFC: ; 0x02004CFC
	ldr r3, _02004D00 ; =FUN_020C1E68
	bx r3
	.balign 4
_02004D00: .word FUN_020C1E68

	thumb_func_start FUN_02004D04
FUN_02004D04: ; 0x02004D04
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x13
	bl FUN_02003D38
	cmp r4, #0x8
	ble _02004D16
	mov r4, #0x8
	b _02004D1C
_02004D16:
	cmp r4, #0x0
	bge _02004D1C
	mov r4, #0x0
_02004D1C:
	strb r4, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02004D20
FUN_02004D20: ; 0x02004D20
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020C0EA4
	pop {r3-r5, pc}

	thumb_func_start FUN_02004D34
FUN_02004D34: ; 0x02004D34
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02004D20
	pop {r3-r5, pc}

	thumb_func_start FUN_02004D4C
FUN_02004D4C: ; 0x02004D4C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020C0E7C
	pop {r3-r5, pc}

	thumb_func_start FUN_02004D60
FUN_02004D60: ; 0x02004D60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020C0174
	ldr r0, _02004D70 ; =0x021C3DD8
	str r4, [r0, #0x0]
	pop {r4, pc}
	nop
_02004D70: .word 0x021C3DD8

	thumb_func_start FUN_02004D74
FUN_02004D74: ; 0x02004D74
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x6
	bl FUN_02003D38
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004D84
FUN_02004D84: ; 0x02004D84
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x7
	bl FUN_02003D38
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004D94
FUN_02004D94: ; 0x02004D94
	push {r3, lr}
	mov r0, #0x7
	bl FUN_02003D38
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	bne _02004DAA
	mov r1, #0x0
	strh r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}
_02004DAA:
	sub r1, r1, #0x1
	strh r1, [r0, #0x0]
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004DB4
FUN_02004DB4: ; 0x02004DB4
	ldr r0, _02004DB8 ; =0x021C3DE0
	bx lr
	.balign 4
_02004DB8: .word 0x021C3DE0

	thumb_func_start FUN_02004DBC
FUN_02004DBC: ; 0x02004DBC
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x12
	bl FUN_02003D38
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004DCC
FUN_02004DCC: ; 0x02004DCC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x15
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02004E44
	mov r0, #0x0
	strb r0, [r4, #0x0]
	mov r0, #0x5
	bl FUN_02003CE8
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02004E08
FUN_02004E08: ; 0x02004E08
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x8
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x14]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x28]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02004E44
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x0]
	mov r0, #0x6
	bl FUN_02003CE8
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02004E44
FUN_02004E44: ; 0x02004E44
	push {r3-r7, lr}
	add r6, r2, #0x0
	mov r0, #0x2
	add r5, r1, #0x0
	add r7, r3, #0x0
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	bl FUN_020053CC
	mov r0, #0x0
	bl FUN_02004110
	add r0, r5, #0x0
	bl FUN_02004130
	add r0, r7, #0x0
	bl FUN_02004D84
	add r0, r5, #0x0
	bl FUN_020048F4
	str r0, [r4, #0x0]
	add r0, sp, #0x8
	ldrb r0, [r0, #0x10]
	bl FUN_02004DBC
	pop {r3-r7, pc}

	thumb_func_start FUN_02004E80
FUN_02004E80: ; 0x02004E80
	cmp r0, #0x0
	bne _02004E88
	mov r0, #0x0
	bx lr
_02004E88:
	add r0, #0xc
	bx lr

	thumb_func_start FUN_02004E8C
FUN_02004E8C: ; 0x02004E8C
	cmp r0, #0x0
	bne _02004E94
	mov r0, #0x0
	bx lr
_02004E94:
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02004E98
FUN_02004E98: ; 0x02004E98
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x5
	bl FUN_02004748
	bl FUN_02003F64
	lsl r0, r5, #0x10
	lsr r4, r0, #0x10
	ldr r0, _02004ECC ; =0x000001B9
	cmp r4, r0
	beq _02004EBC
	add r0, #0x36
	cmp r5, r0
	bgt _02004EBA
	cmp r5, #0x0
	bne _02004EBC
_02004EBA:
	mov r4, #0x1
_02004EBC:
	add r0, r4, #0x0
	bl FUN_02003FC4
	add r0, r4, #0x0
	bl FUN_02004ED0
	pop {r3-r5, pc}
	nop
_02004ECC: .word 0x000001B9

	thumb_func_start FUN_02004ED0
FUN_02004ED0: ; 0x02004ED0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	bl FUN_02003D38
	add r4, r0, #0x0
	lsl r0, r5, #0x10
	ldr r1, _02004F24 ; =0x000001B9
	lsr r0, r0, #0x10
	cmp r0, r1
	beq _02004EF2
	add r1, #0x36
	cmp r5, r1
	bgt _02004EF0
	cmp r5, #0x0
	bne _02004EF2
_02004EF0:
	mov r0, #0x1
_02004EF2:
	bl FUN_020C226C
	cmp r0, #0x0
	bne _02004F02
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_02004F02:
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x8
	lsr r0, r0, #0x8
	bl FUN_020C20DC
	cmp r0, #0x0
	bne _02004F18
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_02004F18:
	mov r1, #0x0
	bl SND_GetWaveDataAddress
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	nop
_02004F24: .word 0x000001B9

	thumb_func_start FUN_02004F28
FUN_02004F28: ; 0x02004F28
	push {r4-r6, lr}
	mov r0, #0x1
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02004F64
	mov r1, #0x3
	add r4, r0, #0x0
	add r0, r6, #0x0
	lsl r1, r1, #0x8
	ldr r5, [r5, #0x8]
	bl _s32_div_f
	lsl r1, r0, #0x1
	bpl _02004F50
	mov r0, #0x20
	bl _s32_div_f
	neg r0, r0
	b _02004F5A
_02004F50:
	cmp r1, #0x0
	bne _02004F58
	mov r0, #0x20
	b _02004F5A
_02004F58:
	lsl r0, r1, #0x5
_02004F5A:
	mul r0, r4
	cmp r0, r5
	blo _02004F62
	mov r0, #0x0
_02004F62:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004F64
FUN_02004F64: ; 0x02004F64
	push {r3, lr}
	bl FUN_02003FF4
	bl FUN_020C0DD4
	pop {r3, pc}

	thumb_func_start FUN_02004F70
FUN_02004F70: ; 0x02004F70
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	ldr r1, [sp, #0x0]
	mov r0, #0x1
	add r2, r3, #0x0
	bl FUN_02004F28
	add r1, r0, #0x0
	mov r12, r0
	sub r1, #0x64
	bpl _02004F8E
	mov r1, #0x0
_02004F8E:
	ldr r0, [sp, #0x0]
	mov r3, #0x0
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	add r7, r3, #0x0
	cmp r0, #0x80
	bhs _02004FA0
	mov r0, #0x1
	b _02004FA2
_02004FA0:
	sub r0, r3, #0x1
_02004FA2:
	lsl r0, r0, #0x18
	asr r5, r0, #0x18
	mov r0, r12
	cmp r1, r0
	bhs _02005022
_02004FAC:
	mov r0, #0x0
	cmp r5, #0x0
	ble _02004FC6
	ldr r2, [sp, #0x0]
	add r2, r2, r1
	str r2, [sp, #0x4]
	ldrb r2, [r2, #0xc]
	cmp r2, #0x80
	bls _02004FC2
	mov r0, #0x1
	b _02004FD8
_02004FC2:
	add r3, r3, #0x1
	b _02004FD8
_02004FC6:
	ldr r2, [sp, #0x0]
	add r2, r2, r1
	str r2, [sp, #0x4]
	ldrb r2, [r2, #0xc]
	cmp r2, #0x80
	bhs _02004FD6
	mov r0, #0x1
	b _02004FD8
_02004FD6:
	add r3, r3, #0x1
_02004FD8:
	cmp r0, #0x1
	bne _0200501A
	ldr r5, _02005064 ; =0x020ECB8C
	mov r2, #0x0
_02004FE0:
	ldrb r0, [r5, #0x0]
	cmp r3, r0
	bge _02004FEA
	add r7, r2, #0x0
	b _02004FF2
_02004FEA:
	add r2, r2, #0x1
	add r5, r5, #0x1
	cmp r2, #0x9
	blt _02004FE0
_02004FF2:
	cmp r7, r6
	blt _02004FF8
	sub r7, r6, #0x1
_02004FF8:
	cmp r3, #0x0
	beq _02005006
	sub r0, r6, #0x1
	sub r0, r0, r7
	ldrb r2, [r4, r0]
	add r2, r2, #0x1
	strb r2, [r4, r0]
_02005006:
	ldr r0, [sp, #0x4]
	mov r3, #0x0
	ldrb r0, [r0, #0xc]
	cmp r0, #0x80
	bhs _02005014
	mov r0, #0x1
	b _02005016
_02005014:
	sub r0, r3, #0x1
_02005016:
	lsl r0, r0, #0x18
	asr r5, r0, #0x18
_0200501A:
	add r1, r1, #0x2
	mov r0, r12
	cmp r1, r0
	blo _02004FAC
_02005022:
	mov r2, #0x0
	cmp r6, #0x0
	ble _02005038
	mov r0, #0x9
_0200502A:
	ldrb r1, [r4, r2]
	cmp r1, #0xa
	blo _02005032
	strb r0, [r4, r2]
_02005032:
	add r2, r2, #0x1
	cmp r2, r6
	blt _0200502A
_02005038:
	sub r2, r6, #0x1
	mov r3, #0x0
	cmp r2, #0x0
	ble _02005060
_02005040:
	ldrb r0, [r4, r3]
	add r1, r4, r3
	cmp r0, #0x0
	bne _0200505A
	ldrb r0, [r1, #0x1]
	cmp r0, #0x0
	beq _0200505A
	add r0, r3, #0x1
	ldrb r0, [r4, r0]
	add sp, #0x8
	lsr r0, r0, #0x1
	strb r0, [r1, #0x0]
	pop {r3-r7, pc}
_0200505A:
	add r3, r3, #0x1
	cmp r3, r2
	blt _02005040
_02005060:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02005064: .word 0x020ECB8C

	thumb_func_start FUN_02005068
FUN_02005068: ; 0x02005068
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, [sp, #0x48]
	add r6, r1, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x13
	str r2, [sp, #0x0]
	add r4, r3, #0x0
	bl FUN_02003D38
	add r7, r0, #0x0
	cmp r4, #0x1
	beq _0200508A
	ldr r0, [sp, #0x0]
	lsr r0, r0, #0x1
	str r0, [sp, #0x0]
_0200508A:
	ldrb r2, [r7, #0x0]
	cmp r2, #0x0
	beq _0200515A
	mov r0, #0x0
	cmp r2, #0x0
	ble _020050BC
	add r1, sp, #0x10
_02005098:
	ldr r3, [sp, #0x0]
	sub r2, r3, r2
	add r2, r0, r2
	lsl r2, r2, #0x1
	ldrsh r2, [r5, r2]
	strh r2, [r1, #0x0]
	ldrb r3, [r7, #0x0]
	ldr r2, [sp, #0x0]
	sub r2, r2, r3
	add r2, r0, r2
	lsl r2, r2, #0x1
	ldrsh r2, [r6, r2]
	add r0, r0, #0x1
	strh r2, [r1, #0x2]
	ldrb r2, [r7, #0x0]
	add r1, r1, #0x4
	cmp r0, r2
	blt _02005098
_020050BC:
	ldr r0, [sp, #0x0]
	sub r4, r0, #0x1
	sub r0, r2, #0x1
	cmp r4, r0
	blt _02005126
	lsl r1, r4, #0x1
	add r0, r5, r1
	str r0, [sp, #0x8]
	add r0, r6, r1
	str r0, [sp, #0x4]
_020050D0:
	mov r0, #0x0
	add r1, r0, #0x0
	cmp r2, #0x0
	ble _020050E6
_020050D8:
	sub r3, r4, r1
	lsl r3, r3, #0x1
	ldrsh r3, [r5, r3]
	add r1, r1, #0x1
	add r0, r0, r3
	cmp r1, r2
	blt _020050D8
_020050E6:
	add r1, r2, #0x0
	bl _s32_div_f
	ldr r1, [sp, #0x8]
	strh r0, [r1, #0x0]
	mov r0, #0x0
	ldrb r1, [r7, #0x0]
	add r2, r0, #0x0
	cmp r1, #0x0
	ble _02005108
_020050FA:
	sub r3, r4, r2
	lsl r3, r3, #0x1
	ldrsh r3, [r6, r3]
	add r2, r2, #0x1
	add r0, r0, r3
	cmp r2, r1
	blt _020050FA
_02005108:
	bl _s32_div_f
	ldr r1, [sp, #0x4]
	sub r4, r4, #0x1
	strh r0, [r1, #0x0]
	ldr r0, [sp, #0x8]
	ldrb r2, [r7, #0x0]
	sub r0, r0, #0x2
	str r0, [sp, #0x8]
	add r0, r1, #0x0
	sub r0, r0, #0x2
	str r0, [sp, #0x4]
	sub r0, r2, #0x1
	cmp r4, r0
	bge _020050D0
_02005126:
	mov r1, #0x0
	cmp r2, #0x0
	ble _0200514A
	add r0, sp, #0x10
	mov r4, #0x2
_02005130:
	mov r2, #0x0
	ldrsh r3, [r0, r2]
	ldr r2, [sp, #0xc]
	add r1, r1, #0x1
	strh r3, [r2, #0x0]
	ldrsh r3, [r0, r4]
	add r0, r0, #0x4
	strh r3, [r2, #0x2]
	add r2, r2, #0x4
	str r2, [sp, #0xc]
	ldrb r2, [r7, #0x0]
	cmp r1, r2
	blt _02005130
_0200514A:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl DC_FlushRange
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl DC_FlushRange
_0200515A:
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02005160
FUN_02005160: ; 0x02005160
	ldr r3, _02005168 ; =FUN_020C1148
	add r1, r0, #0x0
	mov r0, #0x7
	bx r3
	.balign 4
_02005168: .word FUN_020C1148

	thumb_func_start FUN_0200516C
FUN_0200516C: ; 0x0200516C
	push {r3, lr}
	cmp r0, #0x0
	bne _02005180
	ldr r0, _020051A4 ; =0x000007FF
	bl FUN_02005160
	mov r0, #0x0
	bl FUN_02004CA4
	b _0200519C
_02005180:
	cmp r0, #0x1
	ldr r0, _020051A8 ; =0x00007FFF
	bne _02005192
	bl FUN_02005160
	mov r0, #0x1e
	bl FUN_02004C80
	b _0200519C
_02005192:
	bl FUN_02005160
	mov r0, #0xf
	bl FUN_02004C80
_0200519C:
	bl FUN_02004C78
	pop {r3, pc}
	nop
_020051A4: .word 0x000007FF
_020051A8: .word 0x00007FFF

	thumb_func_start FUN_020051AC
FUN_020051AC: ; 0x020051AC
	push {r3, lr}
	bl FUN_02005404
	cmp r0, #0x0
	bne _020051E0
	mov r0, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020051E0
	bl FUN_02004124
	ldr r1, _020051E8 ; =0x0000047E
	cmp r0, r1
	beq _020051E0
	bl FUN_02005454
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020047C8
	pop {r3, pc}
_020051E0:
	bl FUN_0200541C
	pop {r3, pc}
	nop
_020051E8: .word 0x0000047E

	thumb_func_start FUN_020051EC
FUN_020051EC: ; 0x020051EC
	ldr r3, _020051F0 ; =FUN_020C1180
	bx r3
	.balign 4
_020051F0: .word FUN_020C1180
