    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02085338
FUN_02085338: ; 0x02085338
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0x24
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	strb r5, [r4, #0x0]
	strb r7, [r4, #0x1]
	add r0, r6, #0x0
	bl Sav2_Pokedex_get
	str r0, [r4, #0xc]
	add r0, r6, #0x0
	bl FUN_02013B5C
	str r0, [r4, #0x10]
	add r0, r6, #0x0
	bl SavArray_Flags_get
	bl FUN_0205ED0C
	strb r0, [r4, #0x4]
	mov r1, #0x0
	strb r1, [r4, #0x5]
	mov r0, #0x1
	strb r0, [r4, #0x2]
	add r0, r6, #0x0
	strb r1, [r4, #0x3]
	bl Sav2_PlayerData_GetOptionsAddr
	bl FUN_02025084
	str r0, [r4, #0x8]
	cmp r5, #0x2
	bne _02085390
	add r0, r4, #0x0
	add r0, #0x14
	mov r1, #0x3
	bl MailMsg_init_withBank
	b _020853A0
_02085390:
	ldr r0, _020853A4 ; =0x0000FFFF
	mov r1, #0x0
	add r2, r4, #0x0
_02085396:
	add r1, r1, #0x1
	strh r0, [r2, #0x1c]
	add r2, r2, #0x2
	cmp r1, #0x2
	blt _02085396
_020853A0:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_020853A4: .word 0x0000FFFF

	thumb_func_start FUN_020853A8
FUN_020853A8: ; 0x020853A8
	ldr r3, _020853AC ; =FreeToHeap
	bx r3
	.balign 4
_020853AC: .word FreeToHeap

	thumb_func_start FUN_020853B0
FUN_020853B0: ; 0x020853B0
	strh r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_020853B4
FUN_020853B4: ; 0x020853B4
	strh r1, [r0, #0x1c]
	strh r2, [r0, #0x1e]
	bx lr
	.balign 4

	thumb_func_start FUN_020853BC
FUN_020853BC: ; 0x020853BC
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x14]
	ldrh r2, [r1, #0x2]
	strh r2, [r0, #0x16]
	ldrh r2, [r1, #0x4]
	strh r2, [r0, #0x18]
	ldrh r1, [r1, #0x6]
	strh r1, [r0, #0x1a]
	bx lr
	.balign 4

	thumb_func_start FUN_020853D0
FUN_020853D0: ; 0x020853D0
	mov r1, #0x1
	strb r1, [r0, #0x2]
	mov r1, #0x0
	strb r1, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_020853DC
FUN_020853DC: ; 0x020853DC
	mov r1, #0x1
	strb r1, [r0, #0x5]
	bx lr
	.balign 4

	thumb_func_start FUN_020853E4
FUN_020853E4: ; 0x020853E4
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_020853E8
FUN_020853E8: ; 0x020853E8
	ldrb r0, [r0, #0x3]
	bx lr

	thumb_func_start FUN_020853EC
FUN_020853EC: ; 0x020853EC
	ldrh r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_020853F0
FUN_020853F0: ; 0x020853F0
	ldrh r2, [r0, #0x1c]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x1e]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_020853FC
FUN_020853FC: ; 0x020853FC
	add r2, r0, #0x0
	ldr r3, _02085408 ; =MailMsg_copy
	add r2, #0x14
	add r0, r1, #0x0
	add r1, r2, #0x0
	bx r3
	.balign 4
_02085408: .word MailMsg_copy

	thumb_func_start FUN_0208540C
FUN_0208540C: ; 0x0208540C
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02085410
FUN_02085410: ; 0x02085410
	ldrb r0, [r0, #0x1]
	bx lr

	thumb_func_start FUN_02085414
FUN_02085414: ; 0x02085414
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02085418
FUN_02085418: ; 0x02085418
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_0208541C
FUN_0208541C: ; 0x0208541C
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02085420
FUN_02085420: ; 0x02085420
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02085424
FUN_02085424: ; 0x02085424
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_02085428
FUN_02085428: ; 0x02085428
	ldrb r3, [r0, #0x0]
	cmp r3, #0x0
	beq _02085438
	cmp r3, #0x1
	beq _0208543E
	cmp r3, #0x2
	beq _02085448
	bx lr
_02085438:
	ldrh r0, [r0, #0x1c]
	strh r0, [r1, #0x0]
	bx lr
_0208543E:
	ldrh r2, [r0, #0x1c]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x1e]
	strh r0, [r1, #0x2]
	bx lr
_02085448:
	ldrh r1, [r0, #0x14]
	strh r1, [r2, #0x0]
	ldrh r1, [r0, #0x16]
	strh r1, [r2, #0x2]
	ldrh r1, [r0, #0x18]
	strh r1, [r2, #0x4]
	ldrh r0, [r0, #0x1a]
	strh r0, [r2, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_0208545C
FUN_0208545C: ; 0x0208545C
	push {r3, lr}
	ldrb r3, [r0, #0x0]
	cmp r3, #0x0
	beq _0208546C
	cmp r3, #0x1
	beq _0208547C
	cmp r3, #0x2
	b _02085494
_0208546C:
	ldrh r1, [r1, #0x0]
	ldrh r0, [r0, #0x1c]
	cmp r1, r0
	bne _02085478
	mov r0, #0x1
	pop {r3, pc}
_02085478:
	mov r0, #0x0
	pop {r3, pc}
_0208547C:
	ldrh r3, [r1, #0x0]
	ldrh r2, [r0, #0x1c]
	cmp r3, r2
	bne _02085490
	ldrh r1, [r1, #0x2]
	ldrh r0, [r0, #0x1e]
	cmp r1, r0
	bne _02085490
	mov r0, #0x1
	pop {r3, pc}
_02085490:
	mov r0, #0x0
	pop {r3, pc}
_02085494:
	add r0, #0x14
	add r1, r2, #0x0
	bl MailMsg_compare
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020854A0
FUN_020854A0: ; 0x020854A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0208545C
	cmp r0, #0x0
	bne _020854B4
	mov r0, #0x1
	b _020854B6
_020854B4:
	mov r0, #0x0
_020854B6:
	strb r0, [r5, #0x3]
	mov r1, #0x0
	strb r1, [r5, #0x2]
	add r2, r5, #0x0
_020854BE:
	ldrh r0, [r4, #0x0]
	add r1, r1, #0x1
	add r4, r4, #0x2
	strh r0, [r2, #0x1c]
	add r2, r2, #0x2
	cmp r1, #0x2
	blt _020854BE
	ldrh r0, [r6, #0x0]
	strh r0, [r5, #0x14]
	ldrh r0, [r6, #0x2]
	strh r0, [r5, #0x16]
	ldrh r0, [r6, #0x4]
	strh r0, [r5, #0x18]
	ldrh r0, [r6, #0x6]
	strh r0, [r5, #0x1a]
	pop {r4-r6, pc}
	.balign 4
