    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02085258
FUN_02085258: ; 0x02085258
	ldr r3, _02085260 ; =NARC_ctor
	add r1, r0, #0x0
	mov r0, #0x44
	bx r3
	.balign 4
_02085260: .word NARC_ctor

	thumb_func_start FUN_02085264
FUN_02085264: ; 0x02085264
	ldr r3, _02085268 ; =NARC_AllocAndReadWholeMember
	bx r3
	.balign 4
_02085268: .word NARC_AllocAndReadWholeMember

	thumb_func_start FUN_0208526C
FUN_0208526C: ; 0x0208526C
	ldr r3, _02085270 ; =NARC_dtor
	bx r3
	.balign 4
_02085270: .word NARC_dtor

	thumb_func_start FUN_02085274
FUN_02085274: ; 0x02085274
	add r3, r0, #0x0
	add r2, r1, #0x0
	add r1, r3, #0x0
	ldr r3, _02085280 ; =AllocAndReadWholeNarcMemberByIdPair
	mov r0, #0x44
	bx r3
	.balign 4
_02085280: .word AllocAndReadWholeNarcMemberByIdPair

	thumb_func_start FUN_02085284
FUN_02085284: ; 0x02085284
	ldr r3, _0208528C ; =FUN_02085274
	sub r0, #0x95
	bx r3
	nop
_0208528C: .word FUN_02085274

	thumb_func_start FUN_02085290
FUN_02085290: ; 0x02085290
	cmp r1, #0xa
	bhi _020852E2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020852A0: ; jump table (using 16-bit offset)
	.short _020852B6 - _020852A0 - 2; case 0
	.short _020852BA - _020852A0 - 2; case 1
	.short _020852BE - _020852A0 - 2; case 2
	.short _020852C2 - _020852A0 - 2; case 3
	.short _020852C6 - _020852A0 - 2; case 4
	.short _020852CA - _020852A0 - 2; case 5
	.short _020852CE - _020852A0 - 2; case 6
	.short _020852D2 - _020852A0 - 2; case 7
	.short _020852D6 - _020852A0 - 2; case 8
	.short _020852DA - _020852A0 - 2; case 9
	.short _020852DE - _020852A0 - 2; case 10
_020852B6:
	ldrh r0, [r0, #0x0]
	bx lr
_020852BA:
	ldrb r0, [r0, #0x2]
	bx lr
_020852BE:
	ldrb r0, [r0, #0x3]
	bx lr
_020852C2:
	ldrb r0, [r0, #0x4]
	bx lr
_020852C6:
	ldrb r0, [r0, #0x5]
	bx lr
_020852CA:
	ldrb r0, [r0, #0x6]
	bx lr
_020852CE:
	ldrb r0, [r0, #0x7]
	bx lr
_020852D2:
	ldrb r0, [r0, #0x8]
	bx lr
_020852D6:
	ldrb r0, [r0, #0x9]
	bx lr
_020852DA:
	ldrb r0, [r0, #0xa]
	bx lr
_020852DE:
	ldrb r0, [r0, #0xb]
	bx lr
_020852E2:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020852E8
FUN_020852E8: ; 0x020852E8
	push {r3-r5, lr}
	ldr r2, _0208530C ; =0x00000175
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_0208530C: .word 0x00000175

	thumb_func_start FUN_02085310
FUN_02085310: ; 0x02085310
	push {r3-r5, lr}
	mov r2, #0x5d
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl FUN_0200A86C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
