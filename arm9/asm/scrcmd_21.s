    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020F4574
UNK_020F4574: ; 0x020F4574
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07

	.text

	thumb_func_start ScrCmd_SysFlagZukanGet
ScrCmd_SysFlagZukanGet: ; 0x020453F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02024D64
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagZukanSet
ScrCmd_SysFlagZukanSet: ; 0x02045424
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024D80
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagShoesGet
ScrCmd_SysFlagShoesGet: ; 0x02045438
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	bl FUN_02055474
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagShoesSet
ScrCmd_SysFlagShoesSet: ; 0x02045468
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	mov r1, #0x1
	bl FUN_02055488
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagBadgeGet
ScrCmd_SysFlagBadgeGet: ; 0x02045484
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	cmp r4, #0x8
	blo _020454B6
	bl ErrorHandling
_020454B6:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r4, #0x0
	bl FUN_020239D0
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_SysFlagBadgeSet
ScrCmd_SysFlagBadgeSet: ; 0x020454CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	cmp r4, #0x8
	blo _020454EA
	bl ErrorHandling
_020454EA:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r4, #0x0
	bl FUN_020239E4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagBagGet
ScrCmd_SysFlagBagGet: ; 0x02045500
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ECE0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagBadgeCount
ScrCmd_SysFlagBadgeCount: ; 0x0204552C
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r4, #0x0
	ldr r7, _02045578 ; =UNK_020F4574
	str r0, [sp, #0x0]
	add r5, r4, #0x0
_02045548:
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	ldrb r1, [r7, r4]
	bl FUN_020239D0
	cmp r0, #0x1
	bne _02045564
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_02045564:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x8
	blo _02045548
	ldr r0, [sp, #0x0]
	strh r5, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02045578: .word UNK_020F4574

	thumb_func_start ScrCmd_SysFlagBagSet
ScrCmd_SysFlagBagSet: ; 0x0204557C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ECD4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagPairGet
ScrCmd_SysFlagPairGet: ; 0x02045590
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagPairSet
ScrCmd_SysFlagPairSet: ; 0x020455BC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED1C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagPairReset
ScrCmd_SysFlagPairReset: ; 0x020455D0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED2C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagOneStepGet
ScrCmd_SysFlagOneStepGet: ; 0x020455E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED6C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagOneStepSet
ScrCmd_SysFlagOneStepSet: ; 0x02045610
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED4C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagOneStepReset
ScrCmd_SysFlagOneStepReset: ; 0x02045624
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED5C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagGameClearGet
ScrCmd_SysFlagGameClearGet: ; 0x02045638
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagGameClearSet
ScrCmd_SysFlagGameClearSet: ; 0x02045664
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205ECFC
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SysFlagKairiki
ScrCmd_SysFlagKairiki: ; 0x02045678
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020456A6
	cmp r1, #0x1
	beq _0204569E
	cmp r1, #0x2
	beq _020456AE
	b _020456CC
_0204569E:
	mov r1, #0x1
	bl FUN_0205F264
	b _020456D0
_020456A6:
	mov r1, #0x0
	bl FUN_0205F264
	b _020456D0
_020456AE:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0205F264
	strh r0, [r5, #0x0]
	b _020456D0
_020456CC:
	bl ErrorHandling
_020456D0:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_SysFlagFlash
ScrCmd_SysFlagFlash: ; 0x020456D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02045700
	cmp r1, #0x1
	beq _020456FA
	cmp r1, #0x2
	beq _02045706
	b _02045722
_020456FA:
	bl FUN_0205F274
	b _02045726
_02045700:
	bl FUN_0205F284
	b _02045726
_02045706:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F294
	strh r0, [r5, #0x0]
	b _02045726
_02045722:
	bl ErrorHandling
_02045726:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SysFlagKiribarai
ScrCmd_SysFlagKiribarai: ; 0x0204572C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, [r5, #0x8]
	add r4, r0, #0x0
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02045758
	cmp r1, #0x1
	beq _02045752
	cmp r1, #0x2
	beq _0204575E
	b _0204577A
_02045752:
	bl FUN_0205F2A4
	b _0204577E
_02045758:
	bl FUN_0205F2B4
	b _0204577E
_0204575E:
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F2C4
	strh r0, [r5, #0x0]
	b _0204577E
_0204577A:
	bl ErrorHandling
_0204577E:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
