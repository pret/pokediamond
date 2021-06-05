	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F58D4

	.section .bss

	.global UNK_021C5ABC
UNK_021C5ABC: ; 0x021C5ABC
	.space 0x4

	.text

	thumb_func_start FUN_02052EE8
FUN_02052EE8: ; 0x02052EE8
	push {r3-r5, lr}
	ldr r1, _02052F58 ; =0x000004E8
	add r5, r0, #0x0
	mov r0, #0x1f
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r2, _02052F58 ; =0x000004E8
	mov r0, #0x0
	add r1, r4, #0x0
	bl MIi_CpuClearFast
	mov r0, #0x4e
	str r5, [r4, #0x0]
	mov r1, #0x1
	lsl r0, r0, #0x4
	str r1, [r4, r0]
	ldr r0, _02052F5C ; =FUN_02052FC8
	add r1, r4, #0x0
	mov r2, #0xb
	bl FUN_0200CA44
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_020524BC
	ldr r1, _02052F60 ; =0x000004D4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0x9
	ldr r0, [r0, #0xc]
	bl SavArray_get
	ldr r1, _02052F64 ; =0x000004D8
	ldr r2, _02052F68 ; =0x00002710
	str r0, [r4, r1]
	sub r0, r1, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x59
	ldr r0, [r0, #0x38]
	str r0, [r4, #0x8]
	mov r0, #0xb
	bl CreateHeapAtEnd
	mov r0, #0x59
	bl FUN_02053618
	ldr r1, _02052F6C ; =0x000004DC
	str r0, [r4, r1]
	add r0, r4, #0x0
	bl FUN_02052F8C
	ldr r0, _02052F70 ; =UNK_021C5ABC
	str r4, [r0, #0x0]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02052F58: .word 0x000004E8
_02052F5C: .word FUN_02052FC8
_02052F60: .word 0x000004D4
_02052F64: .word 0x000004D8
_02052F68: .word 0x00002710
_02052F6C: .word 0x000004DC
_02052F70: .word UNK_021C5ABC

	thumb_func_start FUN_02052F74
FUN_02052F74: ; 0x02052F74
	mov r3, #0x0
	mov r1, #0x3
_02052F78:
	ldrb r2, [r0, #0xd]
	cmp r2, #0x0
	beq _02052F80
	strb r1, [r0, #0xc]
_02052F80:
	add r3, r3, #0x1
	add r0, #0x18
	cmp r3, #0x33
	blt _02052F78
	bx lr
	.balign 4

	thumb_func_start FUN_02052F8C
FUN_02052F8C: ; 0x02052F8C
	mov r2, #0x0
	add r1, r2, #0x0
_02052F90:
	strb r1, [r0, #0xc]
	strb r1, [r0, #0xd]
	strb r1, [r0, #0xe]
	strb r1, [r0, #0xf]
	add r2, r2, #0x1
	add r0, #0x18
	cmp r2, #0x33
	blt _02052F90
	bx lr
	.balign 4

	thumb_func_start FUN_02052FA4
FUN_02052FA4: ; 0x02052FA4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	bl FUN_0200CAB4
	ldr r0, _02052FC4 ; =0x000004DC
	ldr r0, [r4, r0]
	bl FUN_0205362C
	mov r0, #0x59
	bl DestroyHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4
_02052FC4: .word 0x000004DC

	thumb_func_start FUN_02052FC8
FUN_02052FC8: ; 0x02052FC8
	push {r3-r5, lr}
	ldr r0, _02052FFC ; =0x000004D4
	add r5, r1, #0x0
	ldr r0, [r5, r0]
	ldr r4, [r5, #0x0]
	bl FUN_0204646C
	cmp r0, #0x0
	bne _02052FF8
	ldr r3, _02052FFC ; =0x000004D4
	add r0, r5, #0x0
	ldr r2, [r5, r3]
	add r3, r3, #0x4
	ldr r2, [r2, #0x34]
	ldr r3, [r5, r3]
	add r1, r4, #0x0
	bl FUN_0205312C
	ldr r1, _02052FFC ; =0x000004D4
	add r0, r5, #0x0
	ldr r1, [r5, r1]
	ldr r1, [r1, #0x34]
	bl FUN_020531E4
_02052FF8:
	pop {r3-r5, pc}
	nop
_02052FFC: .word 0x000004D4

	thumb_func_start FUN_02053000
FUN_02053000: ; 0x02053000
	push {r4-r7, lr}
	sub sp, #0x14
	mov r5, #0x0
	str r0, [sp, #0x0]
	str r3, [sp, #0x4]
	cmp r2, #0x0
	bne _02053034
	ldr r0, _02053100 ; =UNK_020F58D4
	lsl r1, r1, #0x1
	ldrh r4, [r0, r1]
	ldr r0, [sp, #0x0]
	mov r6, #0x3
	add r0, #0xc
	str r0, [sp, #0x0]
_0205301C:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02053104
	add r5, r5, #0x1
	add r4, r4, #0x1
	cmp r5, #0x4
	blt _0205301C
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_02053034:
	add r0, r2, #0x0
	str r0, [sp, #0xc]
	add r0, #0x50
	str r0, [sp, #0xc]
	add r0, #0x30
	str r0, [sp, #0xc]
	ldr r0, [r2, #0x50]
	mov r2, #0x18
	add r3, r1, #0x0
	mul r3, r2
	ldr r2, [sp, #0x0]
	add r2, r2, r3
	ldr r2, [r2, #0x18]
	cmp r0, r2
	beq _02053078
	ldr r0, _02053100 ; =UNK_020F58D4
	lsl r1, r1, #0x1
	ldrh r4, [r0, r1]
	ldr r0, [sp, #0x0]
	mov r6, #0x3
	add r0, #0xc
	str r0, [sp, #0x0]
_02053060:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02053104
	add r5, r5, #0x1
	add r4, r4, #0x1
	cmp r5, #0x4
	blt _02053060
	add sp, #0x14
	mov r0, #0x0
	pop {r4-r7, pc}
_02053078:
	ldr r0, _02053100 ; =UNK_020F58D4
	lsl r1, r1, #0x1
	ldrh r7, [r0, r1]
	ldr r0, [sp, #0xc]
	add r6, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x10]
	add r0, #0xc
	str r0, [sp, #0x10]
_0205308C:
	mov r0, #0x18
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	add r4, r0, r1
	ldrb r0, [r4, #0xd]
	cmp r0, #0x0
	beq _020530A6
	cmp r0, #0x2
	beq _020530CC
	cmp r0, #0x4
	beq _020530E6
	b _020530EA
_020530A6:
	ldr r0, [sp, #0xc]
	add r1, r0, r6
	ldrb r0, [r1, #0x18]
	cmp r0, #0x0
	beq _020530EA
	mov r0, #0x2
	strb r0, [r4, #0xc]
	ldrb r1, [r1, #0x18]
	mov r0, #0x7f
	and r0, r1
	strb r0, [r4, #0x14]
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	ldr r1, [r1, #0x0]
	bl FUN_02025614
	strb r0, [r4, #0xe]
	mov r5, #0x1
	b _020530EA
_020530CC:
	ldr r0, [sp, #0xc]
	add r0, r0, r6
	ldrb r0, [r0, #0x18]
	cmp r0, #0x0
	bne _020530E2
	ldr r0, [sp, #0x10]
	add r1, r7, #0x0
	mov r2, #0x3
	bl FUN_02053104
	b _020530EA
_020530E2:
	mov r5, #0x1
	b _020530EA
_020530E6:
	mov r0, #0x0
	strb r0, [r4, #0xc]
_020530EA:
	ldr r0, [sp, #0x8]
	add r6, r6, #0x1
	add r0, r0, #0x4
	add r7, r7, #0x1
	str r0, [sp, #0x8]
	cmp r6, #0x4
	blt _0205308C
	add r0, r5, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02053100: .word UNK_020F58D4

	thumb_func_start FUN_02053104
FUN_02053104: ; 0x02053104
	push {r4-r6, lr}
	ldr r6, _02053124 ; =UNK_021C5ABC
	mov r4, #0x18
	ldr r3, [r6, #0x0]
	ldr r5, _02053128 ; =0x000004D4
	mul r4, r1
	ldr r3, [r3, r5]
	strb r2, [r0, r4]
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r5]
	cmp r3, r0
	beq _02053120
	bl GF_AssertFail
_02053120:
	pop {r4-r6, pc}
	nop
_02053124: .word UNK_021C5ABC
_02053128: .word 0x000004D4

	thumb_func_start FUN_0205312C
FUN_0205312C: ; 0x0205312C
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x0]
	add r5, r0, #0x0
	str r0, [sp, #0x10]
	add r0, #0xc
	str r1, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r4, #0x0
	str r0, [sp, #0x10]
_02053140:
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_020524C0
	add r6, r0, #0x0
	add r7, r6, #0x0
	add r7, #0x50
	add r0, r7, #0x0
	str r0, [sp, #0xc]
	add r0, #0x10
	str r0, [sp, #0xc]
	ldrb r0, [r5, #0xd]
	cmp r0, #0x0
	beq _02053166
	cmp r0, #0x2
	beq _020531A2
	cmp r0, #0x4
	beq _020531D4
	b _020531D8
_02053166:
	cmp r6, #0x0
	beq _020531D8
	ldr r0, [sp, #0xc]
	bl PlayerProfile_GetAvatar
	strb r0, [r5, #0x14]
	ldr r0, [sp, #0xc]
	bl PlayerProfile_GetTrainerID
	add r1, r0, #0x0
	ldr r0, [sp, #0x8]
	bl FUN_02025614
	strb r0, [r5, #0xe]
	ldr r0, [r7, #0x0]
	ldr r3, [sp, #0x8]
	str r0, [r5, #0x18]
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02053000
	cmp r0, #0x0
	beq _0205319C
	mov r0, #0x2
	strb r0, [r5, #0xc]
	b _020531D8
_0205319C:
	mov r0, #0x1
	strb r0, [r5, #0xc]
	b _020531D8
_020531A2:
	cmp r6, #0x0
	beq _020531AE
	ldr r1, [r7, #0x0]
	ldr r0, [r5, #0x18]
	cmp r1, r0
	beq _020531B8
_020531AE:
	ldr r0, [sp, #0x10]
	add r1, r4, #0x0
	mov r2, #0x3
	bl FUN_02053104
_020531B8:
	ldr r0, [sp, #0x0]
	ldr r3, [sp, #0x8]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02053000
	cmp r0, #0x0
	beq _020531D8
	ldrb r0, [r5, #0x15]
	cmp r0, #0x1
	bne _020531D8
	mov r0, #0x3
	strb r0, [r5, #0xc]
	b _020531D8
_020531D4:
	mov r0, #0x0
	strb r0, [r5, #0xc]
_020531D8:
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, #0xa
	blt _02053140
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_020531E4
FUN_020531E4: ; 0x020531E4
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x8]
	str r1, [sp, #0x4]
	bl FUN_02055320
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x8]
	bl FUN_0205532C
	ldr r4, [sp, #0x0]
	str r0, [sp, #0x8]
	add r6, r4, #0x0
	mov r7, #0x0
	add r6, #0xc
_02053206:
	ldr r0, [sp, #0x4]
	add r1, r7, #0x1
	bl FUN_02058060
	add r5, r0, #0x0
	bne _02053216
	bl GF_AssertFail
_02053216:
	ldrb r0, [r4, #0xd]
	cmp r0, #0x4
	bhi _0205330A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02053228: ; jump table (using 16-bit offset)
	.short _02053232 - _02053228 - 2; case 0
	.short _02053252 - _02053228 - 2; case 1
	.short _020532B2 - _02053228 - 2; case 2
	.short _020532DA - _02053228 - 2; case 3
	.short _02053306 - _02053228 - 2; case 4
_02053232:
	add r0, r5, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0205330A
	ldrb r0, [r4, #0xc]
	sub r0, r0, #0x1
	cmp r0, #0x1
	bhi _0205330A
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0205339C
	b _0205330A
_02053252:
	add r0, r5, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0205330A
	ldrb r0, [r4, #0xc]
	cmp r0, #0x3
	bne _02053272
	mov r0, #0x0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xc]
	add r0, r6, #0x0
	mov r1, #0x1
	bl FUN_0205333C
	b _0205330A
_02053272:
	add r0, r5, #0x0
	bl FUN_0205AE50
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020588EC
	ldrb r0, [r4, #0xc]
	cmp r0, #0x1
	bne _020532A8
	ldrb r0, [r4, #0x15]
	cmp r0, #0x0
	bne _020532A8
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_02058E90
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02058534
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205853C
	mov r0, #0x1
	strb r0, [r4, #0x15]
_020532A8:
	mov r0, #0x2
	strb r0, [r4, #0xd]
	mov r0, #0x0
	strb r0, [r4, #0xc]
	b _0205330A
_020532B2:
	add r0, r5, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0205330A
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02053478
	ldrb r0, [r4, #0xc]
	cmp r0, #0x3
	bne _020532D2
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02053444
_020532D2:
	add r0, r6, #0x0
	bl FUN_02053378
	b _0205330A
_020532DA:
	add r0, r5, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0205330A
	add r0, r5, #0x0
	bl FUN_0205AE50
	mov r0, #0x4
	strb r0, [r4, #0xd]
	mov r0, #0x0
	strb r0, [r4, #0xc]
	strb r0, [r4, #0x15]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020588B8
	b _0205330A
_02053306:
	mov r0, #0x0
	strb r0, [r4, #0xd]
_0205330A:
	add r7, r7, #0x1
	add r4, #0x18
	add r6, #0x18
	cmp r7, #0x32
	bge _02053316
	b _02053206
_02053316:
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x8]
	bl FUN_020553A0
	add r1, r0, #0x0
	ldr r2, _02053338 ; =0x000004BC
	ldr r0, [sp, #0x0]
	add r0, r0, r2
	bl FUN_02053478
	ldr r1, _02053338 ; =0x000004BC
	ldr r0, [sp, #0x0]
	add r0, r0, r1
	bl FUN_02053378
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02053338: .word 0x000004BC

	thumb_func_start FUN_0205333C
FUN_0205333C: ; 0x0205333C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	add r4, r1, #0x0
	cmp r0, #0x0
	beq _0205335A
	bl FUN_020646A0
	cmp r0, #0x0
	beq _02053356
	ldr r0, [r5, #0x10]
	bl FUN_02064520
_02053356:
	mov r0, #0x0
	str r0, [r5, #0x10]
_0205335A:
	cmp r4, #0x0
	beq _02053376
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	beq _02053376
	bl FUN_020646A0
	cmp r0, #0x0
	beq _02053372
	ldr r0, [r5, #0x14]
	bl FUN_02064520
_02053372:
	mov r0, #0x0
	str r0, [r5, #0x14]
_02053376:
	pop {r3-r5, pc}

	thumb_func_start FUN_02053378
FUN_02053378: ; 0x02053378
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r1, [r4, #0x4]
	cmp r1, #0x0
	beq _02053398
	ldrh r1, [r4, #0x6]
	sub r1, r1, #0x1
	strh r1, [r4, #0x6]
	ldrh r1, [r4, #0x6]
	cmp r1, #0x0
	bne _02053398
	mov r1, #0x0
	bl FUN_0205333C
	mov r0, #0x0
	strb r0, [r4, #0x4]
_02053398:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205339C
FUN_0205339C: ; 0x0205339C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl FUN_02058AFC
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02058B04
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02058B0C
	add r6, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r7, r0
	bne _020533CC
	ldr r0, [sp, #0x8]
	cmp r6, r0
	beq _0205343C
_020533CC:
	ldr r0, _02053440 ; =0x0000064F
	bl FUN_020054C8
	ldrb r1, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_02057634
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0205333C
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r3, r6, #0x0
	bl FUN_02058E28
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020584A4
	add r0, r4, #0x0
	mov r1, #0x44
	bl FUN_0205ADDC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205889C
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020588B8
	mov r1, #0x1
	strb r1, [r5, #0x1]
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _0205343C
	cmp r0, #0x1
	bne _0205342A
	add r0, r4, #0x0
	bl MOD06_02249668
	str r0, [r5, #0x14]
	b _02053438
_0205342A:
	cmp r0, #0x2
	blo _02053438
	add r0, r4, #0x0
	mov r1, #0x2
	bl MOD06_02249668
	str r0, [r5, #0x14]
_02053438:
	mov r0, #0x0
	strb r0, [r5, #0x2]
_0205343C:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02053440: .word 0x0000064F

	thumb_func_start FUN_02053444
FUN_02053444: ; 0x02053444
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x43
	bl FUN_0205ADDC
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_020588EC
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02058E90
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0205333C
	mov r0, #0x0
	strb r0, [r4, #0x4]
	strh r0, [r4, #0x6]
	mov r0, #0x3
	strb r0, [r4, #0x1]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02053478
FUN_02053478: ; 0x02053478
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r0, [r4, #0x3]
	cmp r0, #0x1
	bne _0205349C
	ldrb r0, [r4, #0x4]
	cmp r0, #0x0
	bne _0205349C
	add r0, r1, #0x0
	bl MOD05_021EDA48
	str r0, [r4, #0x10]
	mov r0, #0x1e
	strh r0, [r4, #0x6]
	mov r0, #0x0
	strb r0, [r4, #0x3]
	mov r0, #0x1
	strb r0, [r4, #0x4]
_0205349C:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020534A0
FUN_020534A0: ; 0x020534A0
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r0, #0x0
	cmp r5, r6
	bge _020534DA
_020534AC:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02058060
	add r4, r0, #0x0
	bne _020534BC
	bl GF_AssertFail
_020534BC:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020588B8
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020588EC
	add r5, r5, #0x1
	cmp r5, r6
	blt _020534AC
_020534DA:
	pop {r3-r7, pc}

	thumb_func_start FUN_020534DC
FUN_020534DC: ; 0x020534DC
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x0
	add r7, r0, #0x0
	bl FUN_02058060
	add r4, r0, #0x0
	bne _020534F0
	bl GF_AssertFail
_020534F0:
	add r0, r4, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _02053596
	bl FUN_02031B2C
	cmp r0, #0x0
	bne _0205350A
	bl FUN_02031AF4
	cmp r0, #0x0
	beq _0205358C
_0205350A:
	mov r6, #0x0
	add r5, #0xc
_0205350E:
	ldrb r0, [r5, #0x1]
	cmp r0, #0x1
	bne _02053578
	add r0, r7, #0x0
	add r1, r6, #0x1
	bl FUN_02058060
	add r4, r0, #0x0
	bne _02053524
	bl GF_AssertFail
_02053524:
	ldrb r1, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_02057634
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020584A4
	add r0, r4, #0x0
	mov r1, #0x44
	bl FUN_0205ADDC
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205889C
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020588B8
	mov r0, #0x1
	strb r0, [r5, #0x1]
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _02053578
	cmp r0, #0x1
	bne _02053566
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD06_02249668
	str r0, [r5, #0x14]
	b _02053574
_02053566:
	cmp r0, #0x2
	blo _02053574
	add r0, r4, #0x0
	mov r1, #0x2
	bl MOD06_02249668
	str r0, [r5, #0x14]
_02053574:
	mov r0, #0x0
	strb r0, [r5, #0x2]
_02053578:
	add r6, r6, #0x1
	add r5, #0x18
	cmp r6, #0xa
	blt _0205350E
	add r0, r7, #0x0
	mov r1, #0xb
	mov r2, #0x33
	bl FUN_020534A0
	pop {r3-r7, pc}
_0205358C:
	add r0, r7, #0x0
	mov r1, #0x1
	mov r2, #0x33
	bl FUN_020534A0
_02053596:
	pop {r3-r7, pc}

	thumb_func_start FUN_02053598
FUN_02053598: ; 0x02053598
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x8
	mov r1, #0x59
	bl String_ctor
	str r0, [r4, #0x0]
	mov r1, #0x0
	add r0, r4, #0x0
	str r1, [r4, #0x4]
	add r0, #0x14
	str r1, [r4, #0x8]
	bl MailMsg_init_withBank
	mov r0, #0x0
	str r0, [r4, #0x10]
	str r0, [r4, #0xc]
	pop {r4, pc}

	thumb_func_start FUN_020535BC
FUN_020535BC: ; 0x020535BC
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
_020535C4:
	add r0, r5, #0x0
	bl FUN_02053598
	add r4, r4, #0x1
	add r5, #0x1c
	cmp r4, #0x1e
	blt _020535C4
	mov r0, #0xd2
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r6, r0]
	add r0, r0, #0x4
	str r1, [r6, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_020535E0
FUN_020535E0: ; 0x020535E0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020535F4
	bl String_dtor
_020535F4:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _020535FE
	bl String_dtor
_020535FE:
	pop {r4, pc}

	thumb_func_start FUN_02053600
FUN_02053600: ; 0x02053600
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_02053606:
	add r0, r5, #0x0
	bl FUN_020535E0
	add r4, r4, #0x1
	add r5, #0x1c
	cmp r4, #0x1e
	blt _02053606
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02053618
FUN_02053618: ; 0x02053618
	push {r4, lr}
	mov r1, #0x35
	lsl r1, r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	bl FUN_020535BC
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_0205362C
FUN_0205362C: ; 0x0205362C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02053600
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
