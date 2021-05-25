    .include "asm/macros.inc"
    .include "global.inc"

	.section .text

	thumb_func_start FUN_02003108
FUN_02003108: ; 0x02003108
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x14
	add r6, r0, #0x0
	mul r1, r4
	add r5, r2, #0x0
	add r1, r6, r1
	add r7, r3, #0x0
	lsl r0, r5, #0x1
	ldr r1, [r1, #0x8]
	add r0, r7, r0
	cmp r0, r1
	bls _02003126
	bl GF_AssertFail
_02003126:
	cmp r4, #0x3
	bhi _0200315E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02003136: ; jump table (using 16-bit offset)
	.short _0200313E - _02003136 - 2; case 0
	.short _02003146 - _02003136 - 2; case 1
	.short _0200314E - _02003136 - 2; case 2
	.short _02003156 - _02003136 - 2; case 3
_0200313E:
	bl FUN_020222E8
	add r1, r0, #0x0
	b _02003164
_02003146:
	bl FUN_020222F8
	add r1, r0, #0x0
	b _02003164
_0200314E:
	bl FUN_02022308
	add r1, r0, #0x0
	b _02003164
_02003156:
	bl FUN_02022310
	add r1, r0, #0x0
	b _02003164
_0200315E:
	bl GF_AssertFail
	pop {r3-r7, pc}
_02003164:
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	lsl r2, r5, #0x1
	str r0, [sp, #0x0]
	add r1, r1, r2
	add r0, r6, #0x0
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl FUN_02003054
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200317C
FUN_0200317C: ; 0x0200317C
	push {r3-r5, lr}
	add r4, r2, #0x0
	add r5, r3, #0x0
	add r2, sp, #0x0
	add r3, r4, #0x0
	bl FUN_02006C08
	add r4, r0, #0x0
	bne _02003192
	bl GF_AssertFail
_02003192:
	cmp r5, #0x0
	bne _0200319A
	ldr r0, [sp, #0x0]
	ldr r5, [r0, #0x8]
_0200319A:
	ldr r0, [sp, #0x0]
	add r2, r5, #0x0
	ldr r1, [r0, #0xc]
	add r0, sp, #0x0
	ldrh r0, [r0, #0x10]
	lsl r0, r0, #0x1
	add r0, r1, r0
	ldr r1, [sp, #0x14]
	bl MIi_CpuCopy16
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020031B8
FUN_020031B8: ; 0x020031B8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, sp, #0x10
	add r5, r0, #0x0
	add r0, r1, #0x0
	ldrh r1, [r4, #0x14]
	add r6, r3, #0x0
	str r1, [sp, #0x0]
	ldrh r1, [r4, #0x10]
	lsl r4, r2, #0x1
	ldr r2, [sp, #0x0]
	lsl r7, r1, #0x1
	mov r1, #0x14
	mul r6, r1
	mul r1, r0
	ldr r0, [r5, r1]
	str r1, [sp, #0x4]
	ldr r1, [r5, r6]
	add r0, r0, r4
	add r1, r1, r7
	bl MIi_CpuCopy16
	ldr r0, [sp, #0x4]
	add r1, r5, r6
	ldr r0, [r5, r0]
	ldr r1, [r1, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r0, r4
	add r1, r1, r7
	bl MIi_CpuCopy16
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020031FC
FUN_020031FC: ; 0x020031FC
	mov r2, #0x14
	mul r2, r1
	ldr r0, [r0, r2]
	bx lr

	thumb_func_start FUN_02003204
FUN_02003204: ; 0x02003204
	mov r2, #0x14
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_02003210
FUN_02003210: ; 0x02003210
	push {r0-r3}
	push {r3-r7, lr}
	sub sp, #0x10
	str r3, [sp, #0x8]
	add r5, r0, #0x0
	ldr r0, [sp, #0x38]
	mov r6, #0x0
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	add r7, r1, #0x0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x40]
	add r4, r6, #0x0
	str r0, [sp, #0x40]
	add r0, sp, #0x28
	ldrh r0, [r0, #0x8]
	str r0, [sp, #0xc]
_02003232:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02003314
	cmp r0, #0x1
	bne _020032A6
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldrh r0, [r5, r0]
	add r1, r4, #0x0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bl FUN_02003314
	cmp r0, #0x0
	bne _020032A6
	mov r0, #0x14
	add r6, r4, #0x0
	mul r6, r0
	add r0, r4, #0x0
	add r1, r5, r6
	add r2, sp, #0x30
	bl FUN_02003368
	ldr r0, [sp, #0x3c]
	add r1, sp, #0x28
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x40]
	str r0, [sp, #0x4]
	add r0, r5, r6
	ldrh r1, [r1, #0x8]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0x38]
	add r0, #0xc
	bl FUN_020033A4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02003328
	cmp r4, #0x4
	blo _02003294
	mov r2, #0x1
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x8
	bl FUN_0200359C
	b _0200329E
_02003294:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x10
	bl FUN_0200359C
_0200329E:
	ldr r1, [sp, #0xc]
	add r0, sp, #0x28
	strh r1, [r0, #0x8]
	mov r6, #0x1
_020032A6:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xe
	blo _02003232
	cmp r6, #0x1
	bne _02003300
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldrh r2, [r5, r0]
	ldr r1, _0200330C ; =0xFFFF0003
	and r1, r2
	lsl r2, r2, #0x10
	lsr r2, r2, #0x12
	orr r2, r7
	lsl r2, r2, #0x12
	lsr r2, r2, #0x10
	orr r1, r2
	strh r1, [r5, r0]
	add r1, r0, #0x2
	ldrh r1, [r5, r1]
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1f
	bne _02003300
	add r1, r0, #0x2
	ldrh r2, [r5, r1]
	mov r1, #0x1
	lsl r1, r1, #0xe
	orr r2, r1
	add r1, r0, #0x2
	strh r2, [r5, r1]
	ldrh r2, [r5, r0]
	mov r1, #0x3
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r5, r0]
	mov r2, #0x0
	add r0, r0, #0x4
	strb r2, [r5, r0]
	ldr r0, _02003310 ; =FUN_02003464
	add r1, r5, #0x0
	sub r2, r2, #0x2
	bl FUN_0200CA44
_02003300:
	add r0, r6, #0x0
	add sp, #0x10
	pop {r3-r7}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4
_0200330C: .word 0xFFFF0003
_02003310: .word FUN_02003464

	thumb_func_start FUN_02003314
FUN_02003314: ; 0x02003314
	mov r3, #0x1
	add r2, r3, #0x0
	lsl r2, r1
	tst r0, r2
	bne _02003320
	mov r3, #0x0
_02003320:
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_02003328
FUN_02003328: ; 0x02003328
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _02003360 ; =0x0000011A
	add r4, r1, #0x0
	ldrh r0, [r5, r0]
	lsl r0, r0, #0x12
	lsr r0, r0, #0x12
	bl FUN_02003314
	cmp r0, #0x1
	beq _0200335E
	ldr r3, _02003360 ; =0x0000011A
	ldr r1, _02003364 ; =0xFFFFC000
	ldrh r2, [r5, r3]
	add r0, r2, #0x0
	lsl r2, r2, #0x12
	lsr r6, r2, #0x12
	mov r2, #0x1
	lsl r2, r4
	orr r2, r6
	lsl r2, r2, #0x10
	and r0, r1
	lsr r2, r2, #0x10
	lsr r1, r1, #0x12
	and r1, r2
	orr r0, r1
	strh r0, [r5, r3]
_0200335E:
	pop {r4-r6, pc}
	.balign 4
_02003360: .word 0x0000011A
_02003364: .word 0xFFFFC000

	thumb_func_start FUN_02003368
FUN_02003368: ; 0x02003368
	push {r4-r5}
	cmp r0, #0x4
	ldr r0, [r1, #0x8]
	bge _02003374
	lsl r0, r0, #0x13
	b _02003378
_02003374:
	lsr r0, r0, #0x9
	lsl r0, r0, #0x18
_02003378:
	mov r4, #0x0
	lsr r0, r0, #0x18
	add r5, r4, #0x0
	cmp r0, #0x0
	bls _02003398
	mov r3, #0x1
_02003384:
	add r1, r3, #0x0
	lsl r1, r5
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	add r1, r5, #0x1
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	cmp r5, r0
	blo _02003384
_02003398:
	ldrh r0, [r2, #0x0]
	and r0, r4
	strh r0, [r2, #0x0]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_020033A4
FUN_020033A4: ; 0x020033A4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r3, #0x0
	cmp r2, #0x0
	bge _020033D4
	add r0, r2, #0x0
	bl abs
	add r0, r0, #0x2
	ldrh r1, [r5, #0x6]
	mov r2, #0xf
	lsl r0, r0, #0x10
	bic r1, r2
	lsr r2, r0, #0x10
	mov r0, #0xf
	and r0, r2
	orr r0, r1
	strh r0, [r5, #0x6]
	ldrh r1, [r5, #0x2]
	mov r0, #0x3f
	bic r1, r0
	strh r1, [r5, #0x2]
	b _020033F2
_020033D4:
	ldrh r1, [r5, #0x6]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x2
	orr r0, r1
	strh r0, [r5, #0x6]
	ldrh r0, [r5, #0x2]
	mov r1, #0x3f
	bic r0, r1
	lsl r1, r2, #0x10
	lsr r2, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r0, r1
	strh r0, [r5, #0x2]
_020033F2:
	strh r6, [r5, #0x0]
	ldrh r1, [r5, #0x2]
	ldr r0, _02003454 ; =0xFFFFF83F
	add r3, sp, #0x0
	and r1, r0
	lsl r0, r4, #0x1b
	lsr r0, r0, #0x15
	orr r0, r1
	strh r0, [r5, #0x2]
	ldrh r1, [r5, #0x2]
	ldr r0, _02003458 ; =0xFFFF07FF
	add r2, r1, #0x0
	ldrb r1, [r3, #0x10]
	and r2, r0
	lsl r0, r1, #0x1b
	lsr r0, r0, #0x10
	orr r0, r2
	strh r0, [r5, #0x2]
	ldrh r0, [r5, #0x4]
	ldr r2, _0200345C ; =0xFFFF8000
	ldrh r6, [r3, #0x14]
	lsr r3, r2, #0x11
	and r0, r2
	and r3, r6
	orr r0, r3
	strh r0, [r5, #0x4]
	ldrh r3, [r5, #0x6]
	ldr r0, _02003460 ; =0xFFFFFC0F
	and r0, r3
	ldrh r3, [r5, #0x2]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1a
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x16
	orr r0, r3
	strh r0, [r5, #0x6]
	cmp r4, r1
	ldrh r1, [r5, #0x4]
	bhs _02003448
	sub r0, r2, #0x1
	and r0, r1
	strh r0, [r5, #0x4]
	pop {r4-r6, pc}
_02003448:
	mov r0, #0x2
	lsl r0, r0, #0xe
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r4-r6, pc}
	nop
_02003454: .word 0xFFFFF83F
_02003458: .word 0xFFFF07FF
_0200345C: .word 0xFFFF8000
_02003460: .word 0xFFFFFC0F

	thumb_func_start FUN_02003464
FUN_02003464: ; 0x02003464
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x47
	lsl r1, r1, #0x2
	ldrb r2, [r4, r1]
	add r5, r0, #0x0
	cmp r2, #0x1
	bne _020034A4
	mov r2, #0x0
	strb r2, [r4, r1]
	sub r2, r1, #0x2
	ldrh r3, [r4, r2]
	ldr r2, _020034F4 ; =0xFFFFC000
	add r5, r3, #0x0
	and r5, r2
	sub r3, r1, #0x2
	strh r5, [r4, r3]
	sub r3, r1, #0x4
	ldrh r5, [r4, r3]
	ldr r3, _020034F8 ; =0xFFFF0003
	sub r2, r2, #0x1
	and r5, r3
	sub r3, r1, #0x4
	strh r5, [r4, r3]
	sub r3, r1, #0x2
	ldrh r3, [r4, r3]
	sub r1, r1, #0x2
	and r2, r3
	strh r2, [r4, r1]
	bl FUN_0200CAB4
	pop {r4-r6, pc}
_020034A4:
	sub r0, r1, #0x4
	ldrh r2, [r4, r0]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1e
	cmp r0, #0x1
	bne _020034F0
	sub r0, r1, #0x2
	ldrh r0, [r4, r0]
	ldr r3, _020034F4 ; =0xFFFFC000
	lsl r2, r2, #0x10
	lsr r6, r2, #0x12
	lsr r2, r3, #0x12
	and r0, r3
	and r2, r6
	orr r2, r0
	sub r0, r1, #0x2
	strh r2, [r4, r0]
	add r0, r4, #0x0
	bl FUN_02003500
	add r0, r4, #0x0
	bl FUN_02003520
	mov r1, #0x46
	lsl r1, r1, #0x2
	ldrh r0, [r4, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bne _020034F0
	add r0, r1, #0x2
	ldrh r2, [r4, r0]
	ldr r0, _020034FC ; =0xFFFFBFFF
	and r2, r0
	add r0, r1, #0x2
	strh r2, [r4, r0]
	add r0, r5, #0x0
	bl FUN_0200CAB4
_020034F0:
	pop {r4-r6, pc}
	nop
_020034F4: .word 0xFFFFC000
_020034F8: .word 0xFFFF0003
_020034FC: .word 0xFFFFBFFF

	thumb_func_start FUN_02003500
FUN_02003500: ; 0x02003500
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0x10
_02003508:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02003540
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02003508
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02003520
FUN_02003520: ; 0x02003520
	push {r4-r6, lr}
	mov r4, #0x4
	add r6, r4, #0x0
	add r5, r0, #0x0
	add r6, #0xfc
_0200352A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02003540
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xe
	blo _0200352A
	pop {r4-r6, pc}

	thumb_func_start FUN_02003540
FUN_02003540: ; 0x02003540
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldrh r0, [r5, r0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bl FUN_02003314
	cmp r0, #0x0
	beq _02003594
	mov r0, #0x14
	mul r0, r4
	add r2, r5, r0
	ldrh r0, [r2, #0x12]
	ldrh r3, [r2, #0xe]
	lsl r1, r0, #0x16
	lsl r3, r3, #0x1a
	lsr r1, r1, #0x1a
	lsr r3, r3, #0x1a
	cmp r1, r3
	bhs _02003584
	ldr r3, _02003598 ; =0xFFFFFC0F
	and r3, r0
	add r0, r1, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x16
	orr r0, r3
	strh r0, [r2, #0x12]
	pop {r4-r6, pc}
_02003584:
	ldr r1, _02003598 ; =0xFFFFFC0F
	and r0, r1
	strh r0, [r2, #0x12]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0200359C
_02003594:
	pop {r4-r6, pc}
	nop
_02003598: .word 0xFFFFFC0F

	thumb_func_start FUN_0200359C
FUN_0200359C: ; 0x0200359C
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x4]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	mov r1, #0x14
	mul r1, r0
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	add r5, r0, r1
	add r0, r5, #0x0
	str r0, [sp, #0x8]
	add r0, #0xc
	add r7, r2, #0x0
	add r4, r6, #0x0
	str r0, [sp, #0x8]
_020035BC:
	ldrh r0, [r5, #0xc]
	lsl r1, r6, #0x10
	lsr r1, r1, #0x10
	bl FUN_02003314
	cmp r0, #0x0
	beq _020035DC
	ldr r0, [r5, #0x0]
	lsl r1, r4, #0x1
	ldr r2, [r5, #0x4]
	add r0, r0, r1
	add r1, r2, r1
	ldr r2, [sp, #0x8]
	add r3, r7, #0x0
	bl FUN_020035F8
_020035DC:
	add r6, r6, #0x1
	add r4, r4, r7
	cmp r6, #0x10
	blo _020035BC
	ldr r1, [sp, #0x4]
	add r5, #0xc
	lsl r1, r1, #0x18
	ldr r0, [sp, #0x0]
	lsr r1, r1, #0x18
	add r2, r5, #0x0
	bl FUN_02003684
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_020035F8
FUN_020035F8: ; 0x020035F8
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x4]
	mov r0, #0x0
	add r6, r1, #0x0
	mov r12, r0
	str r2, [sp, #0x0]
	mov lr, r3
	add r0, r3, #0x0
	beq _02003680
_0200360C:
	ldr r0, [sp, #0x4]
	mov r1, #0x1f
	ldrh r0, [r0, #0x0]
	asr r2, r0, #0x5
	add r5, r2, #0x0
	and r5, r1
	ldr r1, [sp, #0x0]
	asr r4, r0, #0xa
	ldrh r1, [r1, #0x4]
	lsl r1, r1, #0x11
	lsr r3, r1, #0x11
	ldr r1, [sp, #0x0]
	ldrh r1, [r1, #0x2]
	lsl r1, r1, #0x15
	lsr r2, r1, #0x1b
	mov r1, #0x1f
	and r1, r4
	mov r4, #0x1f
	and r0, r4
	and r4, r3
	sub r4, r4, r0
	mul r4, r2
	asr r4, r4, #0x4
	add r0, r0, r4
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	asr r4, r3, #0xa
	mov r0, #0x1f
	and r0, r4
	sub r0, r0, r1
	mul r0, r2
	asr r0, r0, #0x4
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	asr r3, r3, #0x5
	mov r1, #0x1f
	and r1, r3
	sub r1, r1, r5
	mul r1, r2
	asr r1, r1, #0x4
	add r1, r5, r1
	lsl r1, r1, #0x18
	lsl r0, r0, #0xa
	lsr r1, r1, #0x13
	orr r0, r1
	orr r0, r7
	strh r0, [r6, #0x0]
	ldr r0, [sp, #0x4]
	add r6, r6, #0x2
	add r0, r0, #0x2
	str r0, [sp, #0x4]
	mov r0, r12
	add r1, r0, #0x1
	mov r0, lr
	mov r12, r1
	cmp r1, r0
	blo _0200360C
_02003680:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003684
FUN_02003684: ; 0x02003684
	push {r4-r5}
	ldrh r4, [r2, #0x2]
	lsl r3, r4, #0x10
	lsl r4, r4, #0x15
	lsr r3, r3, #0x1b
	lsr r4, r4, #0x1b
	cmp r4, r3
	bne _020036BE
	mov r3, #0x46
	lsl r3, r3, #0x2
	ldrh r4, [r0, r3]
	mov r2, #0x1
	lsl r2, r1
	lsl r1, r4, #0x10
	lsr r5, r1, #0x12
	add r1, r5, #0x0
	tst r1, r2
	beq _0200371E
	eor r2, r5
	lsl r2, r2, #0x10
	ldr r1, _02003724 ; =0xFFFF0003
	lsr r2, r2, #0x10
	lsl r2, r2, #0x12
	and r1, r4
	lsr r2, r2, #0x10
	orr r1, r2
	strh r1, [r0, r3]
	pop {r4-r5}
	bx lr
_020036BE:
	ldrh r0, [r2, #0x4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	bne _020036F4
	lsl r0, r4, #0x10
	asr r1, r0, #0x10
	ldrh r0, [r2, #0x6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	add r0, r1, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r4, r3
	ble _020036DE
	lsl r0, r3, #0x10
	asr r4, r0, #0x10
_020036DE:
	ldrh r1, [r2, #0x2]
	ldr r0, _02003728 ; =0xFFFFF83F
	and r1, r0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x15
	orr r0, r1
	strh r0, [r2, #0x2]
	pop {r4-r5}
	bx lr
_020036F4:
	lsl r0, r4, #0x10
	asr r1, r0, #0x10
	ldrh r0, [r2, #0x6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r4, r3
	bge _0200370C
	lsl r0, r3, #0x10
	asr r4, r0, #0x10
_0200370C:
	ldrh r1, [r2, #0x2]
	ldr r0, _02003728 ; =0xFFFFF83F
	and r1, r0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x15
	orr r0, r1
	strh r0, [r2, #0x2]
_0200371E:
	pop {r4-r5}
	bx lr
	nop
_02003724: .word 0xFFFF0003
_02003728: .word 0xFFFFF83F

	thumb_func_start FUN_0200372C
FUN_0200372C: ; 0x0200372C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _020038DC ; =0x0000011A
	ldrh r1, [r6, r0]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x1f
	bne _02003748
	sub r0, r0, #0x2
	ldrh r0, [r6, r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	cmp r0, #0x1
	beq _02003748
	b _020038DA
_02003748:
	mov r7, #0x2
	mov r5, #0x0
	add r4, r6, #0x0
	lsl r7, r7, #0xc
_02003750:
	ldr r0, _020038DC ; =0x0000011A
	ldrh r1, [r6, r0]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x1f
	bne _02003770
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0200377C
	lsl r0, r1, #0x12
	lsl r1, r5, #0x10
	lsr r0, r0, #0x12
	lsr r1, r1, #0x10
	bl FUN_02003314
	cmp r0, #0x0
	beq _0200377C
_02003770:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl DC_FlushRange
	cmp r5, #0xd
	bls _0200377E
_0200377C:
	b _020038A4
_0200377E:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200378A: ; jump table (using 16-bit offset)
	.short _020037A6 - _0200378A - 2; case 0
	.short _020037B2 - _0200378A - 2; case 1
	.short _020037BE - _0200378A - 2; case 2
	.short _020037CA - _0200378A - 2; case 3
	.short _020037D6 - _0200378A - 2; case 4
	.short _020037EA - _0200378A - 2; case 5
	.short _020037FE - _0200378A - 2; case 6
	.short _02003814 - _0200378A - 2; case 7
	.short _0200382A - _0200378A - 2; case 8
	.short _0200383E - _0200378A - 2; case 9
	.short _02003852 - _0200378A - 2; case 10
	.short _02003868 - _0200378A - 2; case 11
	.short _0200387E - _0200378A - 2; case 12
	.short _02003892 - _0200378A - 2; case 13
_020037A6:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GX_LoadBGPltt
	b _020038A4
_020037B2:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GXS_LoadBGPltt
	b _020038A4
_020037BE:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GX_LoadOBJPltt
	b _020038A4
_020037CA:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GXS_LoadOBJPltt
	b _020038A4
_020037D6:
	bl GX_BeginLoadBGExtPltt
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GX_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	b _020038A4
_020037EA:
	bl GX_BeginLoadBGExtPltt
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r1, r7, #0x0
	bl GX_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	b _020038A4
_020037FE:
	bl GX_BeginLoadBGExtPltt
	mov r1, #0x1
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xe
	bl GX_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	b _020038A4
_02003814:
	bl GX_BeginLoadBGExtPltt
	mov r1, #0x6
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xc
	bl GX_LoadBGExtPltt
	bl GX_EndLoadBGExtPltt
	b _020038A4
_0200382A:
	bl GXS_BeginLoadBGExtPltt
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GXS_LoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	b _020038A4
_0200383E:
	bl GXS_BeginLoadBGExtPltt
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r1, r7, #0x0
	bl GXS_LoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	b _020038A4
_02003852:
	bl GXS_BeginLoadBGExtPltt
	mov r1, #0x1
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xe
	bl GXS_LoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	b _020038A4
_02003868:
	bl GXS_BeginLoadBGExtPltt
	mov r1, #0x6
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xc
	bl GXS_LoadBGExtPltt
	bl GXS_EndLoadBGExtPltt
	b _020038A4
_0200387E:
	bl GX_BeginLoadOBJExtPltt
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GX_LoadOBJExtPltt
	bl GX_EndLoadOBJExtPltt
	b _020038A4
_02003892:
	bl GXS_BeginLoadOBJExtPltt
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	bl GXS_LoadOBJExtPltt
	bl GXS_EndLoadOBJExtPltt
_020038A4:
	add r5, r5, #0x1
	add r4, #0x14
	cmp r5, #0xe
	bge _020038AE
	b _02003750
_020038AE:
	ldr r3, _020038DC ; =0x0000011A
	ldr r1, _020038E0 ; =0xFFFFC000
	sub r2, r3, #0x2
	ldrh r2, [r6, r2]
	ldrh r0, [r6, r3]
	lsl r2, r2, #0x10
	and r0, r1
	lsr r2, r2, #0x12
	lsr r1, r1, #0x12
	and r1, r2
	orr r0, r1
	strh r0, [r6, r3]
	ldrh r0, [r6, r3]
	lsl r0, r0, #0x12
	lsr r0, r0, #0x12
	bne _020038DA
	sub r0, r3, #0x2
	ldrh r1, [r6, r0]
	mov r0, #0x3
	bic r1, r0
	sub r0, r3, #0x2
	strh r1, [r6, r0]
_020038DA:
	pop {r3-r7, pc}
	.balign 4
_020038DC: .word 0x0000011A
_020038E0: .word 0xFFFFC000

	thumb_func_start FUN_020038E4
FUN_020038E4: ; 0x020038E4
	mov r1, #0x46
	lsl r1, r1, #0x2
	ldrh r0, [r0, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bx lr

	thumb_func_start FUN_020038F0
FUN_020038F0: ; 0x020038F0
	push {r3-r4}
	ldr r3, _0200390C ; =0x0000011A
	lsl r1, r1, #0x10
	ldrh r4, [r0, r3]
	ldr r2, _02003910 ; =0xFFFF7FFF
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	and r2, r4
	lsr r1, r1, #0x10
	orr r1, r2
	strh r1, [r0, r3]
	pop {r3-r4}
	bx lr
	nop
_0200390C: .word 0x0000011A
_02003910: .word 0xFFFF7FFF

	thumb_func_start FUN_02003914
FUN_02003914: ; 0x02003914
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x14
	add r4, r1, #0x0
	mul r4, r0
	add r0, sp, #0x10
	ldrh r0, [r0, #0x14]
	add r7, r2, #0x0
	ldr r5, [sp, #0x20]
	str r0, [sp, #0x4]
	lsl r1, r0, #0x1
	add r0, r6, r4
	ldr r0, [r0, #0x8]
	cmp r1, r0
	bls _0200393A
	bl GF_AssertFail
_0200393A:
	sub r0, r7, #0x1
	cmp r0, #0x1
	bhi _02003952
	ldr r2, [r6, r4]
	lsl r1, r5, #0x1
	add r1, r2, r1
	ldr r2, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r2, r2, r5
	lsl r2, r2, #0x1
	bl MIi_CpuClear16
_02003952:
	cmp r7, #0x0
	beq _0200395A
	cmp r7, #0x2
	bne _0200396E
_0200395A:
	add r1, r6, r4
	ldr r2, [r1, #0x4]
	lsl r1, r5, #0x1
	add r1, r2, r1
	ldr r2, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r2, r2, r5
	lsl r2, r2, #0x1
	bl MIi_CpuClear16
_0200396E:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02003974
FUN_02003974: ; 0x02003974
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	mov r12, r1
	lsl r1, r0, #0x16
	lsl r0, r0, #0x11
	lsr r1, r1, #0x1b
	lsr r0, r0, #0x1b
	mov r2, #0x0
	mov lr, r1
	str r0, [sp, #0x8]
	cmp r7, #0x0
	bls _020039E2
_0200399A:
	ldr r0, [sp, #0x0]
	lsl r6, r2, #0x1
	ldrh r4, [r0, r6]
	lsl r0, r4, #0x1b
	lsr r1, r0, #0x1b
	lsl r0, r4, #0x16
	lsl r4, r4, #0x11
	lsr r5, r4, #0x1b
	ldr r4, [sp, #0x8]
	lsr r0, r0, #0x1b
	sub r4, r4, r5
	mul r4, r3
	asr r4, r4, #0x4
	add r4, r5, r4
	lsl r5, r4, #0xa
	mov r4, r12
	sub r4, r4, r1
	mul r4, r3
	asr r4, r4, #0x4
	add r1, r1, r4
	mov r4, lr
	sub r4, r4, r0
	mul r4, r3
	asr r4, r4, #0x4
	add r0, r0, r4
	lsl r0, r0, #0x5
	orr r0, r1
	add r1, r5, #0x0
	orr r1, r0
	ldr r0, [sp, #0x4]
	strh r1, [r0, r6]
	add r0, r2, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, r7
	blo _0200399A
_020039E2:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020039E8
FUN_020039E8: ; 0x020039E8
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r2, #0x0
	add r5, r0, #0x0
	mov r2, #0x14
	add r6, r1, #0x0
	mul r6, r2
	str r3, [sp, #0x4]
	ldr r1, [r5, r6]
	mov r0, #0x0
	add r4, r5, r6
	cmp r1, #0x0
	beq _02003A0A
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _02003A0A
	mov r0, #0x1
_02003A0A:
	cmp r0, #0x0
	bne _02003A12
	bl GF_AssertFail
_02003A12:
	add r3, sp, #0x10
	ldrh r0, [r3, #0x14]
	add r2, r5, r6
	lsl r1, r7, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, [r2, #0x4]
	add r0, r0, r1
	add r1, r2, r1
	ldrb r3, [r3, #0x10]
	ldr r2, [sp, #0x4]
	bl FUN_02003974
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003A30
FUN_02003A30: ; 0x02003A30
	push {r3-r7, lr}
	sub sp, #0x8
	str r3, [sp, #0x4]
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	ldr r7, [sp, #0x20]
	beq _02003A60
_02003A40:
	mov r0, #0x1
	tst r0, r4
	beq _02003A54
	str r7, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x10
	bl FUN_02003974
_02003A54:
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
	add r6, #0x20
	add r5, #0x20
	cmp r4, #0x0
	bne _02003A40
_02003A60:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003A64
FUN_02003A64: ; 0x02003A64
	push {r4-r7, lr}
	sub sp, #0xc
	str r3, [sp, #0x8]
	add r6, r0, #0x0
	add r7, r1, #0x0
	ldr r0, [sp, #0x20]
	add r5, r2, #0x0
	mov r1, #0x14
	add r2, r7, #0x0
	str r0, [sp, #0x20]
	mul r2, r1
	mov r4, #0x0
	ldr r1, [r6, r2]
	add r0, r4, #0x0
	cmp r1, #0x0
	beq _02003A8E
	add r1, r6, r2
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _02003A8E
	mov r0, #0x1
_02003A8E:
	cmp r0, #0x0
	bne _02003A96
	bl GF_AssertFail
_02003A96:
	cmp r5, #0x0
	beq _02003AC0
_02003A9A:
	mov r0, #0x1
	tst r0, r5
	beq _02003AB6
	ldr r0, [sp, #0x8]
	lsl r2, r4, #0x10
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	lsr r2, r2, #0x10
	mov r3, #0x10
	bl FUN_020039E8
_02003AB6:
	lsl r0, r5, #0xf
	lsr r5, r0, #0x10
	add r4, #0x10
	cmp r5, #0x0
	bne _02003A9A
_02003AC0:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02003AC4
FUN_02003AC4: ; 0x02003AC4
	push {r3-r7, lr}
	mov lr, r1
	mov r12, r2
	add r7, r3, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	ble _02003B3C
	ldr r6, [sp, #0x18]
_02003AD4:
	ldrh r3, [r0, #0x0]
	mov r1, #0x1f
	add r2, r3, #0x0
	asr r5, r3, #0xa
	and r2, r1
	and r5, r1
	mov r1, #0x1d
	mul r1, r5
	mov r5, #0x4c
	mul r5, r2
	asr r3, r3, #0x5
	mov r2, #0x1f
	and r3, r2
	mov r2, #0x97
	mul r2, r3
	add r2, r5, r2
	add r1, r1, r2
	asr r3, r1, #0x8
	mov r1, r12
	add r2, r1, #0x0
	mul r2, r3
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	asr r2, r1, #0x8
	add r1, r7, #0x0
	mul r1, r3
	mul r3, r6
	lsl r1, r1, #0x10
	lsl r3, r3, #0x10
	lsr r1, r1, #0x10
	lsr r3, r3, #0x10
	asr r1, r1, #0x8
	asr r3, r3, #0x8
	cmp r2, #0x1f
	ble _02003B1C
	mov r2, #0x1f
_02003B1C:
	cmp r1, #0x1f
	ble _02003B22
	mov r1, #0x1f
_02003B22:
	cmp r3, #0x1f
	ble _02003B28
	mov r3, #0x1f
_02003B28:
	lsl r3, r3, #0xa
	lsl r1, r1, #0x5
	orr r1, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	add r4, r4, #0x1
	mov r1, lr
	add r0, r0, #0x2
	cmp r4, r1
	blt _02003AD4
_02003B3C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02003B40
FUN_02003B40: ; 0x02003B40
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, sp, #0x4
	bl FUN_02006C08
	add r4, r0, #0x0
	bne _02003B58
	bl GF_AssertFail
_02003B58:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _02003B64
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x8]
	str r0, [sp, #0x1c]
_02003B64:
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x24]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x28]
	ldr r0, [r0, #0xc]
	mov r1, #0x10
	bl FUN_02003AC4
	ldr r0, [sp, #0x1c]
	add r3, sp, #0x8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldrh r3, [r3, #0x18]
	ldr r1, [r1, #0xc]
	ldr r2, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_02003054
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x8
	pop {r3-r5, pc}
