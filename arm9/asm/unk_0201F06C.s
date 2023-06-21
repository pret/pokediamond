	.include "asm/macros.inc"
	.include "global.inc"

	.extern FX_SinCosTable_
	.extern NNS_GfdDefaultFuncAllocPlttVram
	.extern NNS_GfdDefaultFuncAllocTexVram
	.extern NNS_GfdDefaultFuncFreeTexVram
	.extern NNS_GfdDefaultFuncFreePlttVram

	.section .rodata

	.global UNK_020EE658
UNK_020EE658: ; 0x020EE658
	.word sub_02020774, sub_02020618

	.global UNK_020EE660
UNK_020EE660: ; 0x020EE660
	.word sub_02020784, sub_02020778

	.section .data

	.global UNK_02105BBC
UNK_02105BBC: ; 0x02105BBC
	.asciz "data/clact_default.NANR"

	.section .bss

	.global UNK_021C59A8
UNK_021C59A8: ; 0x021C59A8
	.space 0x8

	.text

	thumb_func_start sub_0201F06C
sub_0201F06C: ; 0x0201F06C
	mov r2, #0x0
	strb r2, [r0, #0x0]
	strb r2, [r0, #0x1]
	str r2, [r0, #0x4]
	add r1, r0, #0x0
	str r2, [r0, #0x8]
	add r1, #0xc4
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xc8
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xcc
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xd0
	str r2, [r1, #0x0]
	strb r2, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start sub_0201F094
sub_0201F094: ; 0x0201F094
	mov r3, #0x0
	str r3, [r0, #0x1c]
	str r3, [r0, #0x20]
	str r3, [r0, #0x78]
	add r1, r0, #0x0
	str r3, [r0, #0x7c]
	add r1, #0x80
	str r3, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x84
	add r2, r0, #0x0
	str r3, [r1, #0x0]
	add r2, #0x94
	mov r1, #0x10
_0201F0B0:
	strb r3, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0201F0B0
	add r2, r0, #0x0
	mov r1, #0x0
	add r2, #0x88
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0x8c
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0x90
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xa4
	str r1, [r2, #0x0]
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	mov r2, #0x1
	str r1, [r0, #0x8]
	lsl r2, r2, #0xc
	str r2, [r0, #0xc]
	str r2, [r0, #0x10]
	str r2, [r0, #0x14]
	add r2, r0, #0x0
	add r2, #0xaa
	strh r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xa8
	strb r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xb0
	str r1, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xb4
	str r1, [r2, #0x0]
	strb r1, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start sub_0201F100
sub_0201F100: ; 0x0201F100
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _0201F13C ; =UNK_021C59A8
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201F112
	bl GF_AssertFail
_0201F112:
	mov r1, #0xd4
	add r0, r4, #0x0
	mul r1, r6
	bl AllocFromHeap
	ldr r7, _0201F13C ; =UNK_021C59A8
	mov r4, #0x0
	str r0, [r7, #0x0]
	str r6, [r7, #0x4]
	cmp r6, #0x0
	ble _0201F13A
	add r5, r4, #0x0
_0201F12A:
	ldr r0, [r7, #0x0]
	add r0, r0, r5
	bl sub_0201F06C
	add r4, r4, #0x1
	add r5, #0xd4
	cmp r4, r6
	blt _0201F12A
_0201F13A:
	pop {r3-r7, pc}
	.balign 4
_0201F13C: .word UNK_021C59A8

	thumb_func_start sub_0201F140
sub_0201F140: ; 0x0201F140
	push {r4-r6, lr}
	ldr r6, _0201F174 ; =UNK_021C59A8
	mov r4, #0x0
	ldr r0, [r6, #0x4]
	cmp r0, #0x0
	ble _0201F160
	add r5, r4, #0x0
_0201F14E:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	bl sub_0201F23C
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, #0xd4
	cmp r4, r0
	blt _0201F14E
_0201F160:
	ldr r0, _0201F174 ; =UNK_021C59A8
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _0201F174 ; =UNK_021C59A8
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	pop {r4-r6, pc}
	nop
_0201F174: .word UNK_021C59A8

	thumb_func_start sub_0201F178
sub_0201F178: ; 0x0201F178
	push {r3-r7, lr}
	ldr r6, _0201F1B0 ; =UNK_021C59A8
	mov r4, #0x0
	ldr r0, [r6, #0x4]
	cmp r0, #0x0
	ble _0201F1AC
	add r5, r4, #0x0
	mov r7, #0x2
_0201F188:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	ldrb r1, [r0, #0x1]
	cmp r1, #0x1
	bne _0201F196
	bl sub_0201F318
_0201F196:
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldrb r0, [r1, #0x3]
	cmp r0, #0x1
	bne _0201F1A2
	strb r7, [r1, #0x3]
_0201F1A2:
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, #0xd4
	cmp r4, r0
	blt _0201F188
_0201F1AC:
	pop {r3-r7, pc}
	nop
_0201F1B0: .word UNK_021C59A8

	thumb_func_start sub_0201F1B4
sub_0201F1B4: ; 0x0201F1B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_0201F2E4
	add r4, r0, #0x0
	bne _0201F1C8
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r5, pc}
_0201F1C8:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	strb r0, [r4, #0x1]
	ldr r2, [r5, #0x0]
	mov r1, #0xb8
	ldr r0, [r5, #0x4]
	mul r1, r2
	bl AllocFromHeap
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	add r0, #0xc
	bl sub_0201F094
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0xc
	add r0, #0xbc
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0xc0
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x0]
	ldr r0, [r5, #0x4]
	lsl r1, r1, #0x2
	bl AllocFromHeap
	add r1, r4, #0x0
	add r1, #0xc4
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	bl sub_0201FABC
	ldr r0, [r5, #0x4]
	mov r1, #0x10
	bl AllocFromHeap
	add r1, r4, #0x0
	add r1, #0xcc
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0xcc
	ldr r0, [r0, #0x0]
	ldr r1, [r5, #0x4]
	mov r2, #0x4
	bl GF_ExpHeap_FndInitAllocator
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	bl sub_0201C360
	add r1, r4, #0x0
	add r1, #0xd0
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_0201F23C
sub_0201F23C: ; 0x0201F23C
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F24A
	bl GF_AssertFail
	mov r0, #0x0
	pop {r4, pc}
_0201F24A:
	ldrb r1, [r4, #0x0]
	cmp r1, #0x0
	beq _0201F27E
	bl sub_0201F284
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	add r0, r4, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	add r0, #0xcc
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	bl sub_0201C39C
	add r0, r4, #0x0
	bl sub_0201F06C
_0201F27E:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201F284
sub_0201F284: ; 0x0201F284
	push {r3-r5, lr}
	cmp r0, #0x0
	bne _0201F294
	bne _0201F290
	bl GF_AssertFail
_0201F290:
	mov r0, #0x0
	pop {r3-r5, pc}
_0201F294:
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0201F2BA
	add r1, r0, #0x0
	add r1, #0xbc
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	add r4, #0xc
	cmp r1, r4
	beq _0201F2BA
_0201F2A8:
	add r0, r1, #0x0
	add r0, #0xb0
	ldr r5, [r0, #0x0]
	add r0, r1, #0x0
	bl sub_0201F744
	add r1, r5, #0x0
	cmp r5, r4
	bne _0201F2A8
_0201F2BA:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F2C0
sub_0201F2C0: ; 0x0201F2C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F2CA
	bl GF_AssertFail
_0201F2CA:
	ldrb r0, [r4, #0x3]
	cmp r0, #0x0
	bne _0201F2D4
	mov r0, #0x0
	pop {r4, pc}
_0201F2D4:
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start sub_0201F2D8
sub_0201F2D8: ; 0x0201F2D8
	ldrb r1, [r0, #0x3]
	cmp r1, #0x2
	bne _0201F2E2
	mov r1, #0x0
	strb r1, [r0, #0x3]
_0201F2E2:
	bx lr

	thumb_func_start sub_0201F2E4
sub_0201F2E4: ; 0x0201F2E4
	push {r3-r4}
	ldr r0, _0201F314 ; =UNK_021C59A8
	mov r1, #0x0
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	ble _0201F30C
	ldr r4, [r0, #0x0]
	add r2, r4, #0x0
_0201F2F4:
	ldrb r0, [r2, #0x0]
	cmp r0, #0x0
	bne _0201F304
	mov r0, #0xd4
	mul r0, r1
	add r0, r4, r0
	pop {r3-r4}
	bx lr
_0201F304:
	add r1, r1, #0x1
	add r2, #0xd4
	cmp r1, r3
	blt _0201F2F4
_0201F30C:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0201F314: .word UNK_021C59A8

	thumb_func_start sub_0201F318
sub_0201F318: ; 0x0201F318
	push {r3-r6, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	bne _0201F324
	bl GF_AssertFail
_0201F324:
	add r0, sp, #0x0
	bl MTX_Identity33_
	add r0, r5, #0x0
	add r0, #0xbc
	ldr r4, [r0, #0x0]
	add r5, #0xc
	cmp r4, r5
	beq _0201F37E
	add r6, sp, #0x0
_0201F338:
	ldrb r0, [r4, #0x18]
	cmp r0, #0x1
	bne _0201F376
	add r0, r4, #0x0
	bl sub_0201FC54
	add r0, r4, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _0201F356
	add r0, r4, #0x0
	bl sub_0201F90C
	b _0201F360
_0201F356:
	cmp r0, #0x2
	bne _0201F360
	add r0, r4, #0x0
	bl sub_0201F8F0
_0201F360:
	add r0, r4, #0x0
	add r3, r4, #0x0
	add r0, #0x24
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, #0xc
	bl sub_0201B26C
	add r0, r4, #0x0
	bl sub_0201FC70
_0201F376:
	add r4, #0xb0
	ldr r4, [r4, #0x0]
	cmp r4, r5
	bne _0201F338
_0201F37E:
	add sp, #0x24
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start sub_0201F384
sub_0201F384: ; 0x0201F384
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r6, [r5, #0x1c]
	add r4, r1, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_0201F5B8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0201F5D4
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl sub_0201F648
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201F3BA
	add r6, #0xc
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_0201FB58
_0201F3BA:
	add r0, r5, #0x0
	mov r1, #0x2
	add r0, #0xa8
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r0, [r5, #0x20]
	add r0, r5, #0x0
	add r0, #0xaa
	strh r1, [r0, #0x0]
	add r5, #0xac
	str r1, [r5, #0x0]
	pop {r4-r6, pc}

	thumb_func_start sub_0201F3D4
sub_0201F3D4: ; 0x0201F3D4
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r6, [r5, #0x1c]
	add r4, r1, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_0201F5B8
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F3FE
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, #0x88
	add r1, #0x8c
	add r2, #0x90
	bl sub_0201F524
_0201F3FE:
	add r0, r5, #0x0
	ldr r1, [r4, #0x1c]
	add r0, #0x88
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	ldr r1, [r4, #0x20]
	add r0, #0x8c
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	ldr r1, [r4, #0x24]
	add r0, #0x90
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0201F69C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0201F6C8
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201F43A
	add r6, #0xc
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl sub_0201FB58
_0201F43A:
	add r0, r5, #0x0
	mov r1, #0x3
	add r0, #0xa8
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r0, [r5, #0x20]
	add r0, r5, #0x0
	add r0, #0xaa
	strh r1, [r0, #0x0]
	add r5, #0xac
	str r1, [r5, #0x0]
	pop {r4-r6, pc}

	thumb_func_start sub_0201F454
sub_0201F454: ; 0x0201F454
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl NNS_G3dTexGetRequiredSize
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl NNS_G3dTex4x4GetRequiredSize
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl NNS_G3dPlttGetRequiredSize
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _0201F492
	ldr r3, _0201F4E4 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	add r2, r1, #0x0
	blx r3
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0201F496
	bl GF_AssertFail
	b _0201F496
_0201F492:
	mov r0, #0x0
	str r0, [r4, #0x0]
_0201F496:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0201F4B2
	ldr r3, _0201F4E4 ; =NNS_GfdDefaultFuncAllocTexVram
	mov r1, #0x1
	ldr r3, [r3, #0x0]
	mov r2, #0x0
	blx r3
	str r0, [r6, #0x0]
	cmp r0, #0x0
	bne _0201F4B6
	bl GF_AssertFail
	b _0201F4B6
_0201F4B2:
	mov r0, #0x0
	str r0, [r6, #0x0]
_0201F4B6:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _0201F4DA
	ldr r3, _0201F4E8 ; =NNS_GfdDefaultFuncAllocPlttVram
	mov r1, #0x2
	ldrh r2, [r5, #0x20]
	lsl r1, r1, #0xe
	ldr r3, [r3, #0x0]
	and r1, r2
	mov r2, #0x0
	blx r3
	str r0, [r7, #0x0]
	cmp r0, #0x0
	bne _0201F4DE
	bl GF_AssertFail
	add sp, #0xc
	pop {r4-r7, pc}
_0201F4DA:
	mov r0, #0x0
	str r0, [r7, #0x0]
_0201F4DE:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0201F4E4: .word NNS_GfdDefaultFuncAllocTexVram
_0201F4E8: .word NNS_GfdDefaultFuncAllocPlttVram

	thumb_func_start sub_0201F4EC
sub_0201F4EC: ; 0x0201F4EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl NNS_G3dTexReleaseTexKey
	add r0, r5, #0x0
	bl NNS_G3dPlttReleasePlttKey
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0201F500
sub_0201F500: ; 0x0201F500
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [r2, #0x0]
	ldr r2, [r3, #0x0]
	add r5, r0, #0x0
	bl NNS_G3dTexSetTexKey
	ldr r1, [sp, #0x10]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	bl NNS_G3dPlttSetPlttKey
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl NNS_G3dBindMdlSet
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F524
sub_0201F524: ; 0x0201F524
	push {r3-r5, lr}
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r0, #0x0
	beq _0201F536
	ldr r1, _0201F550 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r1, [r1, #0x0]
	blx r1
_0201F536:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0201F542
	ldr r1, _0201F550 ; =NNS_GfdDefaultFuncFreeTexVram
	ldr r1, [r1, #0x0]
	blx r1
_0201F542:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0201F54E
	ldr r1, _0201F554 ; =NNS_GfdDefaultFuncFreePlttVram
	ldr r1, [r1, #0x0]
	blx r1
_0201F54E:
	pop {r3-r5, pc}
	.balign 4
_0201F550: .word NNS_GfdDefaultFuncFreeTexVram
_0201F554: .word NNS_GfdDefaultFuncFreePlttVram

	thumb_func_start sub_0201F558
sub_0201F558: ; 0x0201F558
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	beq _0201F568
	cmp r5, #0x0
	bne _0201F56E
_0201F568:
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0201F56E:
	bl NNS_G3dTexGetRequiredSize
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl NNS_G3dTex4x4GetRequiredSize
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl NNS_G3dPlttGetRequiredSize
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl NNS_G3dTexGetRequiredSize
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl NNS_G3dTex4x4GetRequiredSize
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl NNS_G3dPlttGetRequiredSize
	ldr r1, [sp, #0x0]
	cmp r1, r6
	bne _0201F5AA
	ldr r1, [sp, #0x4]
	cmp r1, r7
	bne _0201F5AA
	cmp r4, r0
	beq _0201F5B0
_0201F5AA:
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0201F5B0:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0201F5B8
sub_0201F5B8: ; 0x0201F5B8
	push {r4, lr}
	add r4, r1, #0x0
	add r0, r4, #0x0
	add r0, #0xa4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201F5D0
	bl sub_0201C40C
	mov r0, #0x0
	add r4, #0xa4
	str r0, [r4, #0x0]
_0201F5D0:
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201F5D4
sub_0201F5D4: ; 0x0201F5D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r1, #0x7c
	add r2, #0x80
	bl sub_0201FB9C
	str r0, [r5, #0x78]
	add r0, r5, #0x0
	ldr r1, [r5, #0x7c]
	add r0, #0x24
	bl NNS_G3dRenderObjInit
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0201F60E
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	bl sub_0201F558
	b _0201F610
_0201F60E:
	mov r0, #0x0
_0201F610:
	cmp r0, #0x0
	bne _0201F644
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F62E
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, #0x88
	add r1, #0x8c
	add r2, #0x90
	bl sub_0201F524
_0201F62E:
	add r0, r5, #0x0
	add r0, #0x80
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r5, #0x90
	ldr r0, [r0, #0x0]
	add r1, #0x88
	add r2, #0x8c
	add r3, r5, #0x0
	bl sub_0201F454
_0201F644:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F648
sub_0201F648: ; 0x0201F648
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r4, #0x0
	bl sub_0201FBCC
	add r1, r5, #0x0
	add r1, #0x84
	add r3, r5, #0x0
	add r3, #0x94
	str r0, [r1, #0x0]
	add r4, #0xc
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r5, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	add r1, r2, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0xac
	ldr r0, [r0, #0x0]
	add r2, r5, #0x0
	add r3, r5, #0x0
	str r0, [sp, #0x4]
	add r6, #0xd0
	add r2, #0x84
	add r3, #0x88
	ldr r0, [r6, #0x0]
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	bl sub_0201C3B4
	add r5, #0xa4
	str r0, [r5, #0x0]
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start sub_0201F69C
sub_0201F69C: ; 0x0201F69C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, r4, #0x0
	add r1, #0x7c
	add r2, #0x80
	bl sub_0201FB9C
	str r0, [r5, #0x78]
	add r0, r5, #0x0
	ldr r1, [r5, #0x7c]
	add r0, #0x24
	bl NNS_G3dRenderObjInit
	add r0, r4, #0x0
	bl sub_0201FBCC
	add r5, #0x84
	str r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0201F6C8
sub_0201F6C8: ; 0x0201F6C8
	push {r3-r4}
	add r4, r0, #0x0
	add r2, r4, #0x0
	add r3, r1, #0x0
	add r3, #0xc
	add r2, #0x94
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	add r4, #0xa4
	str r0, [r4, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start sub_0201F6E8
sub_0201F6E8: ; 0x0201F6E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r6, [r5, #0x0]
	cmp r6, #0x0
	bne _0201F6F6
	mov r0, #0x0
	pop {r4-r6, pc}
_0201F6F6:
	add r0, r6, #0x0
	bl sub_0201FAF4
	add r4, r0, #0x0
	bne _0201F704
	mov r0, #0x0
	pop {r4-r6, pc}
_0201F704:
	add r3, r5, #0x0
	str r6, [r4, #0x1c]
	add r3, #0x8
	ldmia r3!, {r0-r1}
	add r2, r4, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r3, r5, #0x0
	str r0, [r2, #0x0]
	add r3, #0x14
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0xc
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	mov r1, #0x0
	str r0, [r2, #0x0]
	add r0, r4, #0x0
	add r0, #0xaa
	strh r1, [r0, #0x0]
	mov r1, #0x1
	add r0, r4, #0x0
	strb r1, [r4, #0x18]
	add r0, #0xa8
	strb r1, [r0, #0x0]
	ldr r1, [r5, #0x4]
	add r0, r4, #0x0
	bl sub_0201FBD8
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_0201F744
sub_0201F744: ; 0x0201F744
	push {r3-r5, lr}
	add r5, r0, #0x0
	bne _0201F74E
	bl GF_AssertFail
_0201F74E:
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201F75C
	bl GF_AssertFail
_0201F75C:
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	ldr r4, [r5, #0x1c]
	cmp r0, #0x0
	bne _0201F76C
	mov r0, #0x0
	pop {r3-r5, pc}
_0201F76C:
	add r0, r5, #0x0
	bl sub_0201FB7C
	add r0, r5, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F78C
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r5, #0x0
	add r0, #0x88
	add r1, #0x8c
	add r2, #0x90
	bl sub_0201F524
_0201F78C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_0201F5B8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_0201FB20
	mov r0, #0x1
	strb r0, [r4, #0x3]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F7A4
sub_0201F7A4: ; 0x0201F7A4
	push {r3-r4}
	add r4, r0, #0x0
	str r1, [r4, #0x0]
	str r2, [r4, #0x4]
	str r3, [r4, #0x8]
	ldr r3, [sp, #0x8]
	add r2, r4, #0x0
	add r2, #0xc
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	pop {r3-r4}
	bx lr

	thumb_func_start sub_0201F7C8
sub_0201F7C8: ; 0x0201F7C8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _0201F7D6
	bl GF_AssertFail
_0201F7D6:
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0201F7E0
sub_0201F7E0: ; 0x0201F7E0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F7EA
	bl GF_AssertFail
_0201F7EA:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201F7F0
sub_0201F7F0: ; 0x0201F7F0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _0201F7FE
	bl GF_AssertFail
_0201F7FE:
	ldmia r5!, {r0-r1}
	add r4, #0xc
	stmia r4!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F80C
sub_0201F80C: ; 0x0201F80C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F81A
	bl GF_AssertFail
_0201F81A:
	strb r4, [r5, #0x18]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F820
sub_0201F820: ; 0x0201F820
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F82A
	bl GF_AssertFail
_0201F82A:
	ldrb r0, [r4, #0x18]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201F830
sub_0201F830: ; 0x0201F830
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F83E
	bl GF_AssertFail
_0201F83E:
	add r5, #0xaa
	strh r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0201F844
sub_0201F844: ; 0x0201F844
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F84E
	bl GF_AssertFail
_0201F84E:
	add r4, #0xaa
	ldrh r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start sub_0201F854
sub_0201F854: ; 0x0201F854
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F862
	bl GF_AssertFail
_0201F862:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0201FBFC
	pop {r3-r5, pc}

	thumb_func_start sub_0201F86C
sub_0201F86C: ; 0x0201F86C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F87A
	bl GF_AssertFail
_0201F87A:
	add r5, #0xac
	str r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0201F880
sub_0201F880: ; 0x0201F880
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F88A
	bl GF_AssertFail
_0201F88A:
	add r4, #0xac
	ldr r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start sub_0201F890
sub_0201F890: ; 0x0201F890
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0201F89E
	bl GF_AssertFail
_0201F89E:
	add r1, r5, #0x0
	add r1, #0xaa
	ldrh r1, [r1, #0x0]
	add r0, r5, #0x0
	bl sub_0201FBEC
	add r1, r5, #0x0
	add r1, #0xac
	str r0, [r1, #0x0]
	add r0, r5, #0x0
	add r0, #0xac
	ldr r0, [r0, #0x0]
	add r5, #0xac
	add r0, r0, r4
	str r0, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201F8C0
sub_0201F8C0: ; 0x0201F8C0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F8CA
	bl GF_AssertFail
_0201F8CA:
	add r1, r4, #0x0
	add r1, #0xaa
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl sub_0201FBEC
	add r4, #0xac
	ldr r1, [r4, #0x0]
	sub r0, r1, r0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201F8E0
sub_0201F8E0: ; 0x0201F8E0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201F8EA
	bl GF_AssertFail
_0201F8EA:
	ldr r0, [r4, #0x7c]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201F8F0
sub_0201F8F0: ; 0x0201F8F0
	push {r3, lr}
	add r1, r0, #0x0
	add r0, #0xa8
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _0201F90A
	add r0, r1, #0x0
	add r0, #0xa4
	add r1, #0xac
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	bl sub_0201C438
_0201F90A:
	pop {r3, pc}

	thumb_func_start sub_0201F90C
sub_0201F90C: ; 0x0201F90C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0xac
	ldr r1, [r1, #0x0]
	add r0, #0x94
	lsl r1, r1, #0x4
	lsr r1, r1, #0x10
	bl sub_02022244
	add r2, sp, #0x0
	strb r0, [r2, #0x0]
	lsr r0, r0, #0x8
	strb r0, [r2, #0x1]
	ldrb r0, [r2, #0x0]
	add r1, r4, #0x0
	add r1, #0x84
	strb r0, [r2, #0x2]
	ldrb r0, [r2, #0x1]
	strb r0, [r2, #0x3]
	ldrb r2, [r2, #0x2]
	ldr r0, [r4, #0x7c]
	ldr r1, [r1, #0x0]
	bl sub_0201F954
	add r2, sp, #0x0
	ldr r0, [r4, #0x7c]
	add r4, #0x84
	ldrb r2, [r2, #0x3]
	ldr r1, [r4, #0x0]
	bl sub_0201FA04
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start sub_0201F954
sub_0201F954: ; 0x0201F954
	push {r3-r7, lr}
	ldr r3, [r0, #0x8]
	mov r5, #0x0
	add r6, r0, r3
	ldrh r0, [r0, r3]
	add r3, r1, #0x0
	add r1, #0x42
	ldrh r1, [r1, #0x0]
	add r3, #0x3c
	add r4, r6, r0
	add r0, r3, r1
	ldrh r1, [r3, r1]
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x4]
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	ldrb r0, [r4, #0x1]
	cmp r0, #0x0
	ble _0201F9A2
_0201F97C:
	ldrh r0, [r4, #0x6]
	add r1, r4, r0
	ldrh r0, [r4, r0]
	add r2, r1, #0x4
	add r1, r0, #0x0
	mul r1, r5
	add r1, r2, r1
	ldrb r2, [r1, #0x3]
	mov r0, #0x1
	tst r0, r2
	beq _0201F99A
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl sub_0201F9A4
_0201F99A:
	ldrb r0, [r4, #0x1]
	add r5, r5, #0x1
	cmp r5, r0
	blt _0201F97C
_0201F9A2:
	pop {r3-r7, pc}

	thumb_func_start sub_0201F9A4
sub_0201F9A4: ; 0x0201F9A4
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r0, r1, #0x0
	ldrh r0, [r0, #0x0]
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	add r0, r6, r0
	str r0, [sp, #0x4]
	add r0, r1, #0x0
	ldrb r0, [r0, #0x2]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0201F9FC
	add r0, r6, #0x4
	str r0, [sp, #0x8]
_0201F9C4:
	ldrh r2, [r6, #0xa]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x8]
	add r0, r0, r2
	ldrh r2, [r1, r2]
	ldr r1, [sp, #0x4]
	ldrb r1, [r1, r4]
	mul r1, r2
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	add r5, r6, r0
	ldr r0, [r5, #0x14]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r0, r7
	ldr r0, _0201FA00 ; =0x0000FFFF
	cmp r1, r0
	bls _0201F9EC
	bl GF_AssertFail
_0201F9EC:
	ldr r0, [r5, #0x14]
	add r4, r4, #0x1
	add r0, r0, r7
	str r0, [r5, #0x14]
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x2]
	cmp r4, r0
	blt _0201F9C4
_0201F9FC:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0201FA00: .word 0x0000FFFF

	thumb_func_start sub_0201FA04
sub_0201FA04: ; 0x0201FA04
	push {r3-r7, lr}
	ldr r3, [r0, #0x8]
	add r7, r0, r3
	ldrh r0, [r7, #0x2]
	add r4, r7, r0
	ldrh r0, [r1, #0x34]
	add r5, r1, r0
	ldrh r0, [r5, #0x6]
	add r1, r5, r0
	ldrh r0, [r5, r0]
	add r3, r1, #0x4
	add r1, r0, #0x0
	mul r1, r2
	add r0, r3, r1
	ldrh r6, [r3, r1]
	ldrh r1, [r0, #0x2]
	mov r0, #0x1
	tst r0, r1
	bne _0201FA2C
	lsr r6, r6, #0x1
_0201FA2C:
	ldrb r0, [r4, #0x1]
	mov r5, #0x0
	cmp r0, #0x0
	bls _0201FA5A
_0201FA34:
	ldrh r0, [r4, #0x6]
	add r1, r4, r0
	ldrh r0, [r4, r0]
	add r2, r1, #0x4
	add r1, r0, #0x0
	mul r1, r5
	add r1, r2, r1
	ldrb r2, [r1, #0x3]
	mov r0, #0x1
	tst r0, r2
	beq _0201FA52
	add r0, r7, #0x0
	add r2, r6, #0x0
	bl sub_0201FA5C
_0201FA52:
	ldrb r0, [r4, #0x1]
	add r5, r5, #0x1
	cmp r5, r0
	blo _0201FA34
_0201FA5A:
	pop {r3-r7, pc}

	thumb_func_start sub_0201FA5C
sub_0201FA5C: ; 0x0201FA5C
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r0, r1, #0x0
	ldrh r0, [r0, #0x0]
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	add r0, r6, r0
	str r0, [sp, #0x4]
	add r0, r1, #0x0
	ldrb r0, [r0, #0x2]
	mov r4, #0x0
	cmp r0, #0x0
	bls _0201FAB4
	add r0, r6, #0x4
	str r0, [sp, #0x8]
_0201FA7C:
	ldrh r2, [r6, #0xa]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x8]
	add r0, r0, r2
	ldrh r2, [r1, r2]
	ldr r1, [sp, #0x4]
	ldrb r1, [r1, r4]
	mul r1, r2
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	add r5, r6, r0
	ldrh r1, [r5, #0x1c]
	ldr r0, _0201FAB8 ; =0x00001FFF
	and r0, r1
	add r1, r0, r7
	ldr r0, _0201FAB8 ; =0x00001FFF
	cmp r1, r0
	bls _0201FAA4
	bl GF_AssertFail
_0201FAA4:
	ldrh r0, [r5, #0x1c]
	add r4, r4, #0x1
	add r0, r0, r7
	strh r0, [r5, #0x1c]
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x2]
	cmp r4, r0
	blo _0201FA7C
_0201FAB4:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0201FAB8: .word 0x00001FFF

	thumb_func_start sub_0201FABC
sub_0201FABC: ; 0x0201FABC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201FAEC
	add r4, r7, #0x0
	add r6, r7, #0x0
_0201FACC:
	ldr r0, [r5, #0x4]
	add r0, r0, r4
	bl sub_0201F094
	ldr r0, [r5, #0x4]
	add r7, r7, #0x1
	add r1, r0, r4
	add r0, r5, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	add r4, #0xb8
	str r1, [r0, r6]
	ldr r0, [r5, #0x8]
	add r6, r6, #0x4
	cmp r7, r0
	blt _0201FACC
_0201FAEC:
	mov r0, #0x0
	add r5, #0xc8
	str r0, [r5, #0x0]
	pop {r3-r7, pc}

	thumb_func_start sub_0201FAF4
sub_0201FAF4: ; 0x0201FAF4
	add r1, r0, #0x0
	add r1, #0xc8
	ldr r3, [r1, #0x0]
	ldr r1, [r0, #0x8]
	cmp r3, r1
	blt _0201FB04
	mov r0, #0x0
	bx lr
_0201FB04:
	add r1, r0, #0x0
	add r1, #0xc4
	ldr r2, [r1, #0x0]
	lsl r1, r3, #0x2
	ldr r2, [r2, r1]
	add r1, r0, #0x0
	add r1, #0xc8
	ldr r1, [r1, #0x0]
	add r0, #0xc8
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_0201FB20
sub_0201FB20: ; 0x0201FB20
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0xc8
	ldr r0, [r0, #0x0]
	add r4, r1, #0x0
	cmp r0, #0x0
	bgt _0201FB32
	mov r0, #0x0
	pop {r3-r5, pc}
_0201FB32:
	add r0, r4, #0x0
	bl sub_0201F094
	add r0, r5, #0x0
	add r0, #0xc8
	ldr r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r5, #0x0
	add r0, #0xc8
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xc4
	add r5, #0xc8
	ldr r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	lsl r0, r0, #0x2
	str r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start sub_0201FB58
sub_0201FB58: ; 0x0201FB58
	add r2, r0, #0x0
	add r2, #0xb4
	ldr r3, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xb4
	str r3, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xb4
	ldr r2, [r2, #0x0]
	add r2, #0xb0
	str r1, [r2, #0x0]
	add r2, r1, #0x0
	add r2, #0xb0
	str r0, [r2, #0x0]
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0201FB7C
sub_0201FB7C: ; 0x0201FB7C
	add r1, r0, #0x0
	add r1, #0xb0
	ldr r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0xb4
	ldr r1, [r1, #0x0]
	add r1, #0xb0
	str r2, [r1, #0x0]
	add r1, r0, #0x0
	add r0, #0xb0
	add r1, #0xb4
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start sub_0201FB9C
sub_0201FB9C: ; 0x0201FB9C
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x0
	add r5, r2, #0x0
	bl sub_0201FC90
	add r7, r0, #0x0
	bl NNS_G3dGetMdlSet
	add r4, r0, #0x0
	ldrh r0, [r4, #0xe]
	add r0, r4, r0
	ldr r0, [r0, #0xc]
	add r0, r4, r0
	str r0, [r6, #0x0]
	cmp r5, #0x0
	beq _0201FBC6
	add r0, r7, #0x0
	bl NNS_G3dGetTex
	str r0, [r5, #0x0]
_0201FBC6:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_0201FBCC
sub_0201FBCC: ; 0x0201FBCC
	ldr r3, _0201FBD4 ; =sub_0201FC90
	mov r1, #0x1
	bx r3
	nop
_0201FBD4: .word sub_0201FC90

	thumb_func_start sub_0201FBD8
sub_0201FBD8: ; 0x0201FBD8
	push {r3, lr}
	ldr r2, [r1, #0x1c]
	cmp r2, #0x0
	bne _0201FBE6
	bl sub_0201F384
	pop {r3, pc}
_0201FBE6:
	bl sub_0201F3D4
	pop {r3, pc}

	thumb_func_start sub_0201FBEC
sub_0201FBEC: ; 0x0201FBEC
	push {r3, lr}
	ldr r0, [r0, #0x20]
	bl sub_0201FCA8
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_0201FBFC
sub_0201FBFC: ; 0x0201FBFC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	add r1, #0xaa
	ldrh r1, [r1, #0x0]
	ldr r0, [r5, #0x20]
	bl sub_0201FCA8
	add r5, #0xac
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl sub_0201FC1C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0201FC1C
sub_0201FC1C: ; 0x0201FC1C
	push {r3-r6}
	ldr r4, [r0, #0x0]
	ldr r6, [r1, #0x0]
	lsl r4, r4, #0xc
	mov r3, #0x0
	cmp r4, r6
	bgt _0201FC32
	ldr r5, [r0, #0x4]
	lsl r5, r5, #0xc
	cmp r5, r6
	bge _0201FC36
_0201FC32:
	str r4, [r1, #0x0]
	b _0201FC4E
_0201FC36:
	add r2, r6, r2
	cmp r5, r2
	bge _0201FC4C
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0201FC46
	str r4, [r1, #0x0]
	b _0201FC4E
_0201FC46:
	mov r3, #0x1
	str r5, [r1, #0x0]
	b _0201FC4E
_0201FC4C:
	str r2, [r1, #0x0]
_0201FC4E:
	add r0, r3, #0x0
	pop {r3-r6}
	bx lr

	thumb_func_start sub_0201FC54
sub_0201FC54: ; 0x0201FC54
	push {r3, lr}
	add r3, r0, #0x0
	add r0, #0x90
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	add r0, #0x80
	add r2, r3, #0x0
	ldr r1, [r3, #0x78]
	ldr r0, [r0, #0x0]
	add r2, #0x88
	add r3, #0x8c
	bl sub_0201F500
	pop {r3, pc}

	thumb_func_start sub_0201FC70
sub_0201FC70: ; 0x0201FC70
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, [r4, #0x78]
	bl NNS_G3dReleaseMdlSet
	add r4, #0x80
	ldr r0, [r4, #0x0]
	add r1, sp, #0x4
	add r2, sp, #0x8
	add r3, sp, #0x0
	bl sub_0201F4EC
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start sub_0201FC90
sub_0201FC90: ; 0x0201FC90
	cmp r1, #0x0
	beq _0201FC9A
	cmp r1, #0x1
	beq _0201FC9E
	b _0201FCA2
_0201FC9A:
	ldr r0, [r0, #0x0]
	bx lr
_0201FC9E:
	ldr r0, [r0, #0x4]
	bx lr
_0201FCA2:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_0201FCA8
sub_0201FCA8: ; 0x0201FCA8
	mov r2, #0xc
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start sub_0201FCB0
sub_0201FCB0: ; 0x0201FCB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bne _0201FCBA
	bl GF_AssertFail
_0201FCBA:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _0201FCC4
	bl GF_AssertFail
_0201FCC4:
	mov r1, #0x49
	ldr r0, [r5, #0x8]
	lsl r1, r1, #0x2
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0201FCD6
	bl GF_AssertFail
_0201FCD6:
	add r0, r4, #0x0
	bl sub_0201FE44
	ldr r2, [r5, #0x0]
	ldr r0, [r5, #0x8]
	lsl r1, r2, #0x6
	add r1, r2, r1
	lsl r1, r1, #0x2
	bl AllocFromHeap
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0201FCF4
	bl GF_AssertFail
_0201FCF4:
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x4]
	ldr r1, [r5, #0x0]
	ldr r0, [r5, #0x8]
	lsl r1, r1, #0x2
	bl AllocFromHeap
	str r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0201FD0C
	bl GF_AssertFail
_0201FD0C:
	add r0, r4, #0x0
	bl sub_0202083C
	add r0, r4, #0x0
	add r0, #0x10
	bl sub_0201FE6C
	add r2, r4, #0x0
	mov r1, #0x43
	lsl r1, r1, #0x2
	add r2, #0x10
	str r2, [r4, r1]
	add r0, r1, #0x4
	str r2, [r4, r0]
	ldr r0, [r5, #0x4]
	add r1, #0x8
	str r0, [r4, r1]
	ldr r0, [r5, #0x8]
	ldr r1, _0201FD54 ; =UNK_02105BBC
	bl AllocAndReadFile
	mov r1, #0x46
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	add r1, r4, r1
	bl NNS_G2dGetUnpackedAnimBank
	mov r0, #0x12
	mov r1, #0x1
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_0201FD54: .word UNK_02105BBC

	thumb_func_start sub_0201FD58
sub_0201FD58: ; 0x0201FD58
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201FD62
	mov r0, #0x0
	pop {r4, pc}
_0201FD62:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bne _0201FD6C
	mov r0, #0x1
	pop {r4, pc}
_0201FD6C:
	bl sub_0201FDB4
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, [r4, #0x8]
	bl FreeToHeap
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl sub_0201FE44
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201FD98
sub_0201FD98: ; 0x0201FD98
	cmp r0, #0x0
	bne _0201FDA0
	mov r0, #0x0
	bx lr
_0201FDA0:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _0201FDAA
	mov r0, #0x0
	bx lr
_0201FDAA:
	mov r2, #0x12
	lsl r2, r2, #0x4
	str r1, [r0, r2]
	mov r0, #0x1
	bx lr

	thumb_func_start sub_0201FDB4
sub_0201FDB4: ; 0x0201FDB4
	push {r4-r6, lr}
	cmp r0, #0x0
	bne _0201FDBE
	mov r0, #0x0
	pop {r4-r6, pc}
_0201FDBE:
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _0201FDC8
	mov r0, #0x1
	pop {r4-r6, pc}
_0201FDC8:
	mov r1, #0x11
	lsl r1, r1, #0x4
	add r4, r0, #0x0
	ldr r1, [r0, r1]
	add r4, #0x10
	cmp r1, r4
	beq _0201FDE8
	mov r6, #0x1
	lsl r6, r6, #0x8
_0201FDDA:
	ldr r5, [r1, r6]
	add r0, r1, #0x0
	bl sub_0201FFC8
	add r1, r5, #0x0
	cmp r5, r4
	bne _0201FDDA
_0201FDE8:
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start sub_0201FDEC
sub_0201FDEC: ; 0x0201FDEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bne _0201FDF6
	bl GF_AssertFail
_0201FDF6:
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r1, [r5, r0]
	cmp r1, #0x0
	beq _0201FE38
	sub r0, #0x10
	add r6, r5, #0x0
	ldr r4, [r5, r0]
	add r6, #0x10
	cmp r4, r6
	beq _0201FE38
	ldr r7, _0201FE3C ; =UNK_020EE658
_0201FE0E:
	add r2, r4, #0x0
	add r2, #0x34
	ldrb r2, [r2, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	ldr r2, [r7, r2]
	blx r2
	add r1, r4, #0x0
	add r1, #0x35
	ldrb r1, [r1, #0x0]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	ldr r1, _0201FE40 ; =UNK_020EE660
	ldr r1, [r1, r2]
	blx r1
	mov r0, #0x1
	lsl r0, r0, #0x8
	ldr r4, [r4, r0]
	cmp r4, r6
	bne _0201FE0E
_0201FE38:
	pop {r3-r7, pc}
	nop
_0201FE3C: .word UNK_020EE658
_0201FE40: .word UNK_020EE660

	thumb_func_start sub_0201FE44
sub_0201FE44: ; 0x0201FE44
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	str r1, [r4, #0x0]
	str r1, [r4, #0x4]
	str r1, [r4, #0x8]
	mov r0, #0x45
	str r1, [r4, #0xc]
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r4, #0x0
	add r0, #0x10
	bl sub_0201FE6C
	mov r0, #0x12
	mov r1, #0x0
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201FE6C
sub_0201FE6C: ; 0x0201FE6C
	push {r4, lr}
	mov r2, #0x41
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	str r1, [r4, #0x3c]
	bl memset
	add r0, r4, #0x0
	add r0, #0xb4
	bl NNS_G2dInitImageProxy
	add r0, r4, #0x0
	add r0, #0xd8
	bl NNS_G2dInitImagePaletteProxy
	mov r0, #0x0
	str r0, [r4, #0x30]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201FE94
sub_0201FE94: ; 0x0201FE94
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	bl sub_02020874
	add r4, r0, #0x0
	bne _0201FEA6
	mov r0, #0x0
	pop {r4-r6, pc}
_0201FEA6:
	ldr r0, [r5, #0x0]
	add r6, r5, #0x0
	str r0, [r4, #0x3c]
	add r0, r4, #0x0
	mov r2, #0x0
	add r0, #0xf0
	add r6, #0x8
	strh r2, [r0, #0x0]
	ldmia r6!, {r0-r1}
	add r3, r4, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r6, r5, #0x0
	str r0, [r3, #0x0]
	add r6, #0x14
	add r3, r4, #0x0
	ldmia r6!, {r0-r1}
	add r3, #0x18
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	str r0, [r3, #0x0]
	ldrh r0, [r5, #0x20]
	strh r0, [r4, #0x24]
	add r0, r4, #0x0
	ldr r1, [r5, #0x28]
	add r0, #0xf8
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r5, #0x24]
	add r0, #0xf4
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x26
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x27
	strb r2, [r0, #0x0]
	str r2, [r4, #0x2c]
	add r0, r4, #0x0
	str r2, [r4, #0x30]
	mov r1, #0x11
	add r0, #0x28
	strb r1, [r0, #0x0]
	mov r0, #0x45
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r1, r4, #0x0
	add r1, #0x26
	ldrb r1, [r1, #0x0]
	bl NNS_G2dSetRndCoreAffineOverwriteMode
	add r0, r4, #0x0
	add r0, #0x27
	ldrb r2, [r0, #0x0]
	mov r0, #0x45
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	mov r1, #0x1
	mov r3, #0x2
	and r1, r2
	and r2, r3
	bl NNS_G2dSetRndCoreFlipMode
	add r0, r4, #0x0
	mov r2, #0x1
	add r0, #0x34
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x35
	strb r1, [r0, #0x0]
	lsl r0, r2, #0xd
	str r0, [r4, #0x38]
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r3, [r5, #0x2c]
	add r2, r4, #0x0
	bl sub_02020434
	cmp r0, #0x0
	bne _0201FF56
	add r0, r4, #0x0
	bl sub_0201FFC8
	mov r0, #0x0
	pop {r4-r6, pc}
_0201FF56:
	add r1, r4, #0x0
	add r1, #0xf8
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xd8
	bl sub_020205E8
	add r1, r4, #0x0
	add r1, #0x2a
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2a
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x29
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl sub_02020788
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_0201FF84
sub_0201FF84: ; 0x0201FF84
	push {r4, lr}
	sub sp, #0x30
	add r2, r0, #0x0
	ldr r0, [r2, #0x0]
	add r4, r2, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r2, #0x4]
	add r4, #0x8
	str r0, [sp, #0x4]
	ldmia r4!, {r0-r1}
	add r3, sp, #0x8
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	add r0, sp, #0x0
	strh r1, [r0, #0x20]
	ldr r0, [r2, #0x14]
	str r0, [sp, #0x24]
	ldr r0, [r2, #0x18]
	str r0, [sp, #0x28]
	ldr r0, [r2, #0x1c]
	str r0, [sp, #0x2c]
	add r0, sp, #0x0
	bl sub_0201FE94
	add sp, #0x30
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0201FFC8
sub_0201FFC8: ; 0x0201FFC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0xec
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02020040
	add r1, r5, #0x0
	add r1, #0xfc
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0201FFE4
	bl sub_02020820
_0201FFE4:
	add r0, r5, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x3
	bne _0202000E
	add r1, r5, #0x0
	add r1, #0xf8
	add r0, r5, #0x0
	add r4, r5, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xb4
	add r4, #0x40
	bl NNS_G2dGetImageLocation
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0202000E
	ldr r0, [r4, #0x5c]
	bl NNS_G2dFreeCellTransferStateHandle
_0202000E:
	add r0, r5, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x2
	bne _02020030
	add r4, r5, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x70]
	cmp r0, #0x0
	beq _02020026
	bl FreeToHeap
_02020026:
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	beq _02020030
	bl FreeToHeap
_02020030:
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0xec
	str r1, [r0, #0x0]
	ldr r0, [r5, #0x3c]
	add r1, r5, #0x0
	bl sub_02020890
_02020040:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02020044
sub_02020044: ; 0x02020044
	add r2, r1, #0x0
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020054
sub_02020054: ; 0x02020054
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0xc
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02020064
sub_02020064: ; 0x02020064
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x18
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02020074
sub_02020074: ; 0x02020074
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl sub_02020064
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_020200EC
	pop {r3-r5, pc}

	thumb_func_start sub_02020088
sub_02020088: ; 0x02020088
	strh r1, [r0, #0x24]
	bx lr

	thumb_func_start sub_0202008C
sub_0202008C: ; 0x0202008C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl sub_02020088
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_020200EC
	pop {r3-r5, pc}

	thumb_func_start sub_020200A0
sub_020200A0: ; 0x020200A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200AE
	bl GF_AssertFail
_020200AE:
	cmp r4, #0x2
	blt _020200B6
	bl GF_AssertFail
_020200B6:
	add r5, #0x34
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_020200BC
sub_020200BC: ; 0x020200BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200CA
	bl GF_AssertFail
_020200CA:
	cmp r4, #0x2
	blt _020200D2
	bl GF_AssertFail
_020200D2:
	add r5, #0x35
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_020200D8
sub_020200D8: ; 0x020200D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200E6
	bl GF_AssertFail
_020200E6:
	str r4, [r5, #0x38]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020200EC
sub_020200EC: ; 0x020200EC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020200FA
	bl GF_AssertFail
_020200FA:
	add r5, #0x26
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_02020100
sub_02020100: ; 0x02020100
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0202010E
	bl GF_AssertFail
_0202010E:
	add r0, r5, #0x0
	add r0, #0x27
	strb r4, [r0, #0x0]
	mov r0, #0x0
	add r5, #0x26
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0202011C
sub_0202011C: ; 0x0202011C
	bx lr
	.balign 4

	thumb_func_start sub_02020120
sub_02020120: ; 0x02020120
	add r0, #0x18
	bx lr

	thumb_func_start sub_02020124
sub_02020124: ; 0x02020124
	ldrh r0, [r0, #0x24]
	bx lr

	thumb_func_start sub_02020128
sub_02020128: ; 0x02020128
	add r0, #0x34
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020130
sub_02020130: ; 0x02020130
	push {r4, lr}
	lsl r2, r1, #0x10
	lsr r3, r2, #0x10
	add r2, r0, #0x0
	add r2, #0xf0
	strh r3, [r2, #0x0]
	add r2, r0, #0x0
	add r2, #0xec
	ldr r2, [r2, #0x0]
	cmp r2, #0x1
	beq _0202014A
	cmp r2, #0x3
	bne _02020168
_0202014A:
	add r4, r0, #0x0
	add r4, #0x40
	lsl r1, r1, #0x10
	ldr r0, [r4, #0x4]
	lsr r1, r1, #0x10
	bl NNS_G2dGetAnimSequenceByIdx
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x8
	bl NNS_G2dSetCellAnimationSequence
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r4, pc}
_02020168:
	add r4, r0, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x6c]
	add r1, r3, #0x0
	bl NNS_G2dGetAnimSequenceByIdx
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x8
	bl NNS_G2dSetAnimSequenceToMCAnimation
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r4, pc}

	thumb_func_start sub_02020184
sub_02020184: ; 0x02020184
	push {r3, lr}
	add r2, r0, #0x0
	add r2, #0xf0
	ldrh r2, [r2, #0x0]
	cmp r2, r1
	beq _02020194
	bl sub_02020130
_02020194:
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02020198
sub_02020198: ; 0x02020198
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020201A8
	cmp r0, #0x3
	bne _020201C2
_020201A8:
	add r5, r4, #0x0
	add r5, #0x40
	add r0, r5, #0x0
	add r0, #0x8
	bl NNS_G2dResetAnimCtrlState
	mov r0, #0x1
	str r0, [r5, #0x10]
	add r0, r4, #0x0
	mov r1, #0x0
	bl sub_02020208
	pop {r3-r5, pc}
_020201C2:
	add r5, r4, #0x0
	add r5, #0x40
	add r0, r5, #0x0
	add r0, #0x8
	bl NNS_G2dResetAnimCtrlState
	mov r0, #0x1
	str r0, [r5, #0x10]
	add r0, r4, #0x0
	mov r1, #0x0
	bl sub_02020208
	pop {r3-r5, pc}

	thumb_func_start sub_020201DC
sub_020201DC: ; 0x020201DC
	add r0, #0xf0
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020201E4
sub_020201E4: ; 0x020201E4
	push {r3, lr}
	add r2, r0, #0x0
	add r2, #0xec
	ldr r2, [r2, #0x0]
	cmp r2, #0x1
	beq _020201F4
	cmp r2, #0x3
	bne _020201FE
_020201F4:
	add r0, #0x40
	add r0, #0x8
	bl NNS_G2dTickCellAnimation
	pop {r3, pc}
_020201FE:
	add r0, #0x40
	add r0, #0x8
	bl NNS_G2dTickMCAnimation
	pop {r3, pc}

	thumb_func_start sub_02020208
sub_02020208: ; 0x02020208
	push {r3, lr}
	add r2, r0, #0x0
	add r2, #0xec
	ldr r2, [r2, #0x0]
	cmp r2, #0x1
	beq _02020218
	cmp r2, #0x3
	bne _02020222
_02020218:
	add r0, #0x40
	add r0, #0x8
	bl NNS_G2dSetCellAnimationCurrentFrame
	pop {r3, pc}
_02020222:
	add r0, #0x40
	add r0, #0x8
	bl NNS_G2dSetMCAnimationCurrentFrame
	pop {r3, pc}

	thumb_func_start sub_0202022C
sub_0202022C: ; 0x0202022C
	ldr r3, _02020234 ; =NNS_G2dGetAnimCtrlCurrentFrame
	add r0, #0x40
	add r0, #0x8
	bx r3
	.balign 4
_02020234: .word NNS_G2dGetAnimCtrlCurrentFrame

	thumb_func_start sub_02020238
sub_02020238: ; 0x02020238
	add r0, #0xf2
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020240
sub_02020240: ; 0x02020240
	add r0, #0xf2
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020248
sub_02020248: ; 0x02020248
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02020256
	bl GF_AssertFail
_02020256:
	add r0, r5, #0x0
	add r0, #0x29
	strb r4, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x28
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x10
	add r5, #0x28
	bic r1, r0
	strb r1, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_0202027C
sub_0202027C: ; 0x0202027C
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02020248
	add r1, r4, #0x0
	add r1, #0xf8
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xd8
	bl sub_020205E8
	add r1, r4, #0x0
	add r1, #0x29
	ldrb r1, [r1, #0x0]
	add r4, #0x29
	add r0, r1, r0
	strb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start sub_020202A0
sub_020202A0: ; 0x020202A0
	add r0, #0x29
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020202A8
sub_020202A8: ; 0x020202A8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020202B6
	bl GF_AssertFail
_020202B6:
	add r0, r5, #0x0
	add r0, #0x2a
	strb r4, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x10
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x28
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	add r5, #0x28
	bic r1, r0
	strb r1, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_020202DC
sub_020202DC: ; 0x020202DC
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_020202A8
	add r1, r4, #0x0
	add r1, #0xf8
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r0, #0xd8
	bl sub_020205E8
	add r1, r4, #0x0
	add r1, #0x2a
	ldrb r1, [r1, #0x0]
	add r4, #0x2a
	add r0, r1, r0
	strb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start sub_02020300
sub_02020300: ; 0x02020300
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202030A
	bl GF_AssertFail
_0202030A:
	add r4, #0x2a
	ldrb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start sub_02020310
sub_02020310: ; 0x02020310
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r2, r5, #0x0
	ldr r4, [r5, #0x3c]
	add r2, #0xf4
	strh r1, [r2, #0x0]
	bl sub_02020820
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_02020788
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0202032C
sub_0202032C: ; 0x0202032C
	add r0, #0xf4
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020334
sub_02020334: ; 0x02020334
	push {r3-r4}
	add r3, r0, #0x0
	add r4, r1, #0x0
	add r3, #0xb4
	mov r2, #0x4
_0202033E:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202033E
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start sub_02020350
sub_02020350: ; 0x02020350
	add r0, #0xb4
	bx lr

	thumb_func_start sub_02020354
sub_02020354: ; 0x02020354
	add r0, #0xd8
	bx lr

	thumb_func_start sub_02020358
sub_02020358: ; 0x02020358
	str r1, [r0, #0x2c]
	cmp r1, #0x1
	bne _0202036E
	add r1, r0, #0x0
	add r1, #0x28
	ldrb r2, [r1, #0x0]
	mov r1, #0x4
	add r0, #0x28
	orr r1, r2
	strb r1, [r0, #0x0]
	bx lr
_0202036E:
	add r1, r0, #0x0
	add r1, #0x28
	ldrb r2, [r1, #0x0]
	mov r1, #0x4
	eor r1, r2
	add r0, #0x28
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020380
sub_02020380: ; 0x02020380
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020388
sub_02020388: ; 0x02020388
	push {r4, lr}
	add r4, r0, #0x0
	bne _02020392
	bl GF_AssertFail
_02020392:
	ldr r0, [r4, #0x50]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02020398
sub_02020398: ; 0x02020398
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _020203A6
	bl GF_AssertFail
_020203A6:
	str r5, [r4, #0x30]
	cmp r5, #0x0
	bne _020203BC
	add r0, r4, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	add r4, #0x28
	eor r0, r1
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
_020203BC:
	add r0, r4, #0x0
	add r0, #0x28
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	orr r0, r1
	add r4, #0x28
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start sub_020203CC
sub_020203CC: ; 0x020203CC
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0xb
	mov r2, #0x1
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	lsl r2, r2, #0xa
	bl MIi_CpuClear16
	mov r1, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0xa
	bl DC_FlushRange
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	bl GX_LoadOAM
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start sub_02020404
sub_02020404: ; 0x02020404
	push {r4, lr}
	mov r1, #0x1
	lsl r1, r1, #0xa
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0xb
	mov r2, #0x1
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	lsl r2, r2, #0xa
	bl MIi_CpuClear16
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0xa
	bl GXS_LoadOAM
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02020434
sub_02020434: ; 0x02020434
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	add r4, r2, #0x0
	add r0, r5, #0x0
	add r7, r3, #0x0
	bl sub_020204DC
	add r1, r4, #0x0
	add r1, #0xec
	str r0, [r1, #0x0]
	add r3, r4, #0x0
	ldr r6, [r5, #0x0]
	add r3, #0xb4
	mov r2, #0x4
_02020452:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02020452
	ldr r0, [r6, #0x0]
	add r2, r4, #0x0
	str r0, [r3, #0x0]
	ldr r3, [r5, #0x8]
	add r2, #0xd8
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r4, #0x0
	str r0, [r2, #0x0]
	ldr r0, [r5, #0xc]
	bl sub_020204F4
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _02020486
	add r1, r4, #0x0
	bl sub_020204F8
	b _02020494
_02020486:
	mov r1, #0x47
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	add r1, r4, #0x0
	bl sub_020204F8
_02020494:
	add r0, r4, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x2
	bne _020204B8
	ldr r0, [r5, #0x14]
	add r1, r4, #0x0
	bl sub_020204FC
	ldr r0, [r5, #0x18]
	add r1, r4, #0x0
	bl sub_02020504
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl sub_02020588
	b _020204D0
_020204B8:
	cmp r0, #0x3
	bne _020204C8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl sub_0202052C
	b _020204D0
_020204C8:
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl sub_0202050C
_020204D0:
	add r5, #0x20
	ldrb r0, [r5, #0x0]
	add r4, #0xf2
	strb r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start sub_020204DC
sub_020204DC: ; 0x020204DC
	ldr r1, [r0, #0x14]
	cmp r1, #0x0
	beq _020204E6
	mov r0, #0x2
	bx lr
_020204E6:
	ldr r0, [r0, #0x1c]
	cmp r0, #0x1
	bne _020204F0
	mov r0, #0x3
	bx lr
_020204F0:
	mov r0, #0x1
	bx lr

	thumb_func_start sub_020204F4
sub_020204F4: ; 0x020204F4
	str r0, [r1, #0x40]
	bx lr

	thumb_func_start sub_020204F8
sub_020204F8: ; 0x020204F8
	str r0, [r1, #0x44]
	bx lr

	thumb_func_start sub_020204FC
sub_020204FC: ; 0x020204FC
	add r1, #0xa8
	str r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02020504
sub_02020504: ; 0x02020504
	add r1, #0xac
	str r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0202050C
sub_0202050C: ; 0x0202050C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r5, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	bl NNS_G2dGetAnimSequenceByIdx
	add r4, #0x8
	add r1, r0, #0x0
	ldr r2, [r5, #0x40]
	add r0, r4, #0x0
	bl NNS_G2dInitCellAnimation
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0202052C
sub_0202052C: ; 0x0202052C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r6, r1, #0x0
	add r4, r6, #0x0
	add r4, #0x40
	add r5, r0, #0x0
	bl NNS_G2dGetNewCellTransferStateHandle
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	ldr r5, [r5, #0x4]
	bl NNS_G2dGetAnimSequenceByIdx
	str r0, [sp, #0x18]
	add r0, r6, #0x0
	add r0, #0xb4
	mov r1, #0x1
	bl NNS_G2dGetImageLocation
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r0, #0xb4
	mov r1, #0x2
	bl NNS_G2dGetImageLocation
	mov r1, #0x0
	mvn r1, r1
	str r1, [sp, #0x0]
	str r7, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x14]
	ldr r1, [sp, #0x18]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	ldr r2, [r6, #0x40]
	ldr r3, [r4, #0x5c]
	add r0, #0x8
	bl NNS_G2dInitCellAnimationVramTransfered
	add sp, #0x1c
	pop {r4-r7, pc}

	thumb_func_start sub_02020588
sub_02020588: ; 0x02020588
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r5, #0x0
	add r4, #0x40
	ldr r0, [r4, #0x6c]
	add r7, r1, #0x0
	mov r1, #0x0
	bl NNS_G2dGetAnimSequenceByIdx
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x68]
	bl NNS_G2dGetMCBankNumNodesRequired
	add r6, r0, #0x0
	mov r1, #0x28
	add r0, r7, #0x0
	mul r1, r6
	bl AllocFromHeap
	mov r1, #0x54
	str r0, [r4, #0x70]
	add r0, r7, #0x0
	mul r1, r6
	bl AllocFromHeap
	str r0, [r4, #0x74]
	ldr r0, [r4, #0x4]
	add r3, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x68]
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	ldr r1, [r4, #0x70]
	ldr r2, [r4, #0x74]
	add r0, #0x8
	bl NNS_G2dInitMCAnimation
	add r4, #0x8
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl NNS_G2dSetAnimSequenceToMCAnimation
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_020205E8
sub_020205E8: ; 0x020205E8
	push {r4, lr}
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _020205F6
	mov r4, #0x2
	lsl r4, r4, #0x8
	b _02020602
_020205F6:
	ldr r2, [r0, #0x0]
	cmp r2, #0x4
	bne _02020600
	mov r4, #0x0
	b _02020602
_02020600:
	mov r4, #0x20
_02020602:
	cmp r4, #0x0
	beq _02020612
	bl NNS_G2dGetImagePaletteLocation
	add r1, r4, #0x0
	bl _u32_div_f
	pop {r4, pc}
_02020612:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02020618
sub_02020618: ; 0x02020618
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r3, r4, #0x0
	add r5, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r4, #0x0
	str r0, [r2, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0x2
	add r2, r4, #0x0
	ldr r0, [r5, r0]
	add r1, #0xb4
	add r2, #0xd8
	bl NNS_G2dSetRendererImageProxy
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl NNS_G2dBeginRendering
	bl NNS_G2dPushMtx
	add r1, r4, #0x0
	mov r0, #0x45
	add r1, #0x26
	lsl r0, r0, #0x2
	ldrb r1, [r1, #0x0]
	ldr r0, [r5, r0]
	bl NNS_G2dSetRndCoreAffineOverwriteMode
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02020680
	add r0, r4, #0x0
	add r0, #0x27
	ldrb r2, [r0, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0x2
	mov r1, #0x1
	ldr r0, [r5, r0]
	mov r3, #0x2
	and r1, r2
	and r2, r3
	bl NNS_G2dSetRndCoreFlipMode
	b _0202068E
_02020680:
	mov r0, #0x45
	lsl r0, r0, #0x2
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r2, r1, #0x0
	bl NNS_G2dSetRndCoreFlipMode
_0202068E:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	bl NNS_G2dTranslate
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020206DC
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	bl NNS_G2dTranslate
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0x1c]
	ldr r2, [r4, #0x20]
	bl NNS_G2dScale
	ldrh r0, [r4, #0x24]
	ldr r2, _02020770 ; =FX_SinCosTable_
	asr r0, r0, #0x4
	lsl r1, r0, #0x1
	lsl r0, r1, #0x1
	add r1, r1, #0x1
	lsl r1, r1, #0x1
	ldrsh r0, [r2, r0]
	ldrsh r1, [r2, r1]
	bl NNS_G2dRotZ
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x14]
	neg r0, r0
	neg r1, r1
	neg r2, r2
	bl NNS_G2dTranslate
_020206DC:
	add r0, r4, #0x0
	add r0, #0x28
	ldrb r3, [r0, #0x0]
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldr r2, [r5, r0]
	add r1, r2, #0x0
	add r1, #0x84
	ldr r1, [r1, #0x0]
	add r2, #0x84
	orr r1, r3
	str r1, [r2, #0x0]
	add r1, r4, #0x0
	add r1, #0x28
	ldrb r1, [r1, #0x0]
	mvn r6, r1
	ldr r1, [r5, r0]
	add r2, r1, #0x0
	add r2, #0x84
	ldr r3, [r2, #0x0]
	mvn r2, r6
	and r2, r3
	add r1, #0x84
	str r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x29
	ldrb r2, [r1, #0x0]
	ldr r1, [r5, r0]
	add r1, #0x8a
	strh r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x2a
	ldrb r2, [r1, #0x0]
	ldr r1, [r5, r0]
	add r1, #0x94
	strh r2, [r1, #0x0]
	ldr r1, [r5, r0]
	ldr r2, [r4, #0x2c]
	add r1, #0x90
	str r2, [r1, #0x0]
	ldr r1, [r5, r0]
	ldr r2, [r4, #0x30]
	add r1, #0x8c
	str r2, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0xf2
	ldr r0, [r5, r0]
	ldrb r1, [r1, #0x0]
	add r0, #0x88
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0xec
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _0202074E
	cmp r0, #0x3
	bne _0202075A
_0202074E:
	add r4, #0x40
	add r4, #0x8
	add r0, r4, #0x0
	bl NNS_G2dDrawCellAnimation
	b _02020764
_0202075A:
	add r4, #0x40
	add r4, #0x8
	add r0, r4, #0x0
	bl NNS_G2dDrawMultiCellAnimation
_02020764:
	bl NNS_G2dPopMtx
	bl NNS_G2dEndRendering
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_02020770: .word FX_SinCosTable_

	thumb_func_start sub_02020774
sub_02020774: ; 0x02020774
	bx lr
	.balign 4

	thumb_func_start sub_02020778
sub_02020778: ; 0x02020778
	ldr r3, _02020780 ; =sub_020201E4
	ldr r1, [r0, #0x38]
	bx r3
	nop
_02020780: .word sub_020201E4

	thumb_func_start sub_02020784
sub_02020784: ; 0x02020784
	bx lr
	.balign 4

	thumb_func_start sub_02020788
sub_02020788: ; 0x02020788
	push {r4-r7}
	mov r2, #0x11
	lsl r2, r2, #0x4
	add r4, r0, #0x0
	ldr r5, [r0, r2]
	add r4, #0x10
	cmp r5, r4
	bne _020207AC
	str r1, [r0, r2]
	sub r3, r2, #0x4
	str r1, [r0, r3]
	add r0, r1, #0x0
	add r0, #0xfc
	str r4, [r0, #0x0]
	sub r2, #0x10
	str r4, [r1, r2]
	pop {r4-r7}
	bx lr
_020207AC:
	add r3, r1, #0x0
	add r3, #0xf4
	ldrh r6, [r3, #0x0]
	sub r3, r2, #0x4
	ldr r3, [r0, r3]
	add r7, r3, #0x0
	add r7, #0xf4
	ldrh r7, [r7, #0x0]
	cmp r7, r6
	bhi _020207DE
	add r5, r1, #0x0
	add r5, #0xfc
	str r3, [r5, #0x0]
	sub r3, r2, #0x4
	ldr r5, [r0, r3]
	add r3, r2, #0x0
	sub r3, #0x10
	str r1, [r5, r3]
	add r3, r2, #0x0
	sub r3, #0x10
	str r4, [r1, r3]
	sub r2, r2, #0x4
	str r1, [r0, r2]
	pop {r4-r7}
	bx lr
_020207DE:
	cmp r5, r4
	beq _0202081A
	add r0, r2, #0x0
	sub r0, #0x10
_020207E6:
	add r2, r5, #0x0
	add r2, #0xf4
	ldrh r2, [r2, #0x0]
	cmp r2, r6
	bls _02020814
	add r0, r5, #0x0
	add r0, #0xfc
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	lsl r2, r2, #0x8
	str r1, [r0, r2]
	add r0, r5, #0x0
	add r0, #0xfc
	ldr r3, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0xfc
	str r3, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xfc
	str r1, [r0, #0x0]
	str r5, [r1, r2]
	pop {r4-r7}
	bx lr
_02020814:
	ldr r5, [r5, r0]
	cmp r5, r4
	bne _020207E6
_0202081A:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start sub_02020820
sub_02020820: ; 0x02020820
	mov r2, #0x1
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	add r1, #0xfc
	ldr r3, [r0, r2]
	ldr r1, [r1, #0x0]
	str r3, [r1, r2]
	add r1, r0, #0x0
	add r1, #0xfc
	ldr r0, [r0, r2]
	ldr r1, [r1, #0x0]
	add r0, #0xfc
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start sub_0202083C
sub_0202083C: ; 0x0202083C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0202086C
	add r4, r7, #0x0
	add r6, r7, #0x0
_0202084C:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	bl sub_0201FE6C
	ldr r0, [r5, #0x0]
	add r7, r7, #0x1
	add r1, r0, r4
	ldr r0, [r5, #0x8]
	str r1, [r0, r6]
	mov r0, #0x41
	lsl r0, r0, #0x2
	add r4, r4, r0
	ldr r0, [r5, #0x4]
	add r6, r6, #0x4
	cmp r7, r0
	blt _0202084C
_0202086C:
	mov r0, #0x0
	str r0, [r5, #0xc]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_02020874
sub_02020874: ; 0x02020874
	ldr r3, [r0, #0xc]
	ldr r1, [r0, #0x4]
	cmp r3, r1
	blt _02020880
	mov r0, #0x0
	bx lr
_02020880:
	ldr r2, [r0, #0x8]
	lsl r1, r3, #0x2
	ldr r2, [r2, r1]
	add r1, r3, #0x1
	str r1, [r0, #0xc]
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_02020890
sub_02020890: ; 0x02020890
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	cmp r0, #0x0
	bgt _020208A0
	mov r0, #0x0
	pop {r3-r5, pc}
_020208A0:
	add r0, r4, #0x0
	bl sub_0201FE6C
	ldr r0, [r5, #0xc]
	sub r0, r0, #0x1
	str r0, [r5, #0xc]
	ldr r1, [r5, #0x8]
	lsl r0, r0, #0x2
	str r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
