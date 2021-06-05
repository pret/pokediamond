	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F96DC
	.extern gMain
	.extern UNK_020FA6E8

	.section .rodata

	.global UNK_020F5880
UNK_020F5880: ; 0x020F5880
	.byte 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02050E48
FUN_02050E48: ; 0x02050E48
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	add r5, r1, #0x0
	ldr r0, [sp, #0x24]
	mov r1, #0x30
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	ldr r6, [r5, #0xc]
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0207C2A4
	add r0, r6, #0x0
	bl SavArray_IsNatDexEnabled
	str r0, [r4, #0x1c]
	add r0, r6, #0x0
	bl FUN_02079C70
	str r0, [r4, #0x2c]
	add r0, r6, #0x0
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	ldr r0, [sp, #0x4]
	strb r0, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl GetPartyCount
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	ldr r0, [sp, #0x20]
	strb r0, [r4, #0x12]
	add r0, r6, #0x0
	bl FUN_0202A918
	str r0, [r4, #0x20]
	ldr r1, _02050ECC ; =UNK_020F5880
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r1, _02050ED0 ; =UNK_020FA6E8
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	str r4, [r7, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02050ECC: .word UNK_020F5880
_02050ED0: .word UNK_020FA6E8

	thumb_func_start FUN_02050ED4
FUN_02050ED4: ; 0x02050ED4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x24]
	add r0, #0xac
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x14]
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0xc]
	bl Sav2_Bag_get
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x2
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x24]
	add r0, #0xac
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02050F64
	mov r1, #0x1
	bl FUN_02023B0C
	add r1, r4, #0x0
	add r1, #0x32
	ldrb r1, [r1, #0x0]
	mov r2, #0xf
	lsl r0, r0, #0x18
	bic r1, r2
	lsr r2, r0, #0x18
	mov r0, #0xf
	and r0, r2
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	mov r1, #0xf0
	bic r0, r1
	add r1, r4, #0x0
	add r1, #0x32
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	b _02050F84
_02050F64:
	add r0, r4, #0x0
	add r0, #0x32
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x3
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x32
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x30
_02050F84:
	orr r1, r0
	add r0, r4, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x64
	add r0, #0x33
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x3c
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x22
	strb r1, [r0, #0x0]
	mov r2, #0x0
_02050FA2:
	add r0, r5, r2
	add r0, #0x3d
	ldrb r1, [r0, #0x0]
	add r0, r4, r2
	add r0, #0x2c
	add r2, r2, #0x1
	strb r1, [r0, #0x0]
	cmp r2, #0x6
	blt _02050FA2
	ldr r0, [r5, #0x24]
	ldr r1, _02050FC4 ; =UNK_020F96DC
	add r2, r4, #0x0
	bl FUN_020373D4
	str r4, [r5, #0x4]
	pop {r3-r5, pc}
	nop
_02050FC4: .word UNK_020F96DC

	thumb_func_start FUN_02050FC8
FUN_02050FC8: ; 0x02050FC8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _02050FDA
	mov r0, #0x0
	pop {r4, pc}
_02050FDA:
	ldr r0, [r4, #0x4]
	add r1, r4, #0x0
	add r0, #0x2c
	add r1, #0x3d
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	cmp r0, #0x6
	beq _02050FFC
	cmp r0, #0x7
	bne _02051002
	mov r0, #0x0
	str r0, [r4, #0x38]
	b _02051006
_02050FFC:
	mov r0, #0x1
	str r0, [r4, #0x38]
	b _02051006
_02051002:
	mov r0, #0x2
	str r0, [r4, #0x38]
_02051006:
	ldr r0, [r4, #0x4]
	add r0, #0x22
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x3c
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_02051020
FUN_02051020: ; 0x02051020
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _02051032
	mov r0, #0x0
	pop {r4, pc}
_02051032:
	ldr r0, [r4, #0x0]
	ldrb r1, [r0, #0x14]
	add r0, r4, #0x0
	add r0, #0x3c
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0205104C
FUN_0205104C: ; 0x0205104C
	push {r3, lr}
	ldr r0, [r0, #0x24]
	bl FUN_020464A4
	cmp r0, #0x0
	beq _02051066
	mov r0, #0x1
	bl MOD05_021D7CA4
	bl FUN_0204CC9C
	mov r0, #0x1
	pop {r3, pc}
_02051066:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0205106C
FUN_0205106C: ; 0x0205106C
	push {r3-r5, lr}
	bl FUN_02030F20
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r5, #0x0
	ble _0205108E
_0205107A:
	add r0, r4, #0x0
	bl FUN_020315FC
	cmp r0, #0x5e
	bne _02051088
	mov r0, #0x1
	pop {r3-r5, pc}
_02051088:
	add r4, r4, #0x1
	cmp r4, r5
	blt _0205107A
_0205108E:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02051094
FUN_02051094: ; 0x02051094
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046528
	ldr r1, [r4, #0x34]
	cmp r1, #0x2c
	bls _020510AE
	b _020517B8
_020510AE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020510BA: ; jump table (using 16-bit offset)
	.short _02051114 - _020510BA - 2; case 0
	.short _02051136 - _020510BA - 2; case 1
	.short _02051150 - _020510BA - 2; case 2
	.short _0205116A - _020510BA - 2; case 3
	.short _020511A6 - _020510BA - 2; case 4
	.short _020511F6 - _020510BA - 2; case 5
	.short _020517B8 - _020510BA - 2; case 6
	.short _020511E4 - _020510BA - 2; case 7
	.short _0205120C - _020510BA - 2; case 8
	.short _02051232 - _020510BA - 2; case 9
	.short _0205123E - _020510BA - 2; case 10
	.short _0205126A - _020510BA - 2; case 11
	.short _02051288 - _020510BA - 2; case 12
	.short _0205129C - _020510BA - 2; case 13
	.short _020512A8 - _020510BA - 2; case 14
	.short _020512CA - _020510BA - 2; case 15
	.short _020512E0 - _020510BA - 2; case 16
	.short _0205130E - _020510BA - 2; case 17
	.short _02051334 - _020510BA - 2; case 18
	.short _02051346 - _020510BA - 2; case 19
	.short _0205138A - _020510BA - 2; case 20
	.short _0205136A - _020510BA - 2; case 21
	.short _020513A6 - _020510BA - 2; case 22
	.short _020513B6 - _020510BA - 2; case 23
	.short _020513D4 - _020510BA - 2; case 24
	.short _020513F2 - _020510BA - 2; case 25
	.short _02051406 - _020510BA - 2; case 26
	.short _02051472 - _020510BA - 2; case 27
	.short _020514A8 - _020510BA - 2; case 28
	.short _020514BE - _020510BA - 2; case 29
	.short _02051508 - _020510BA - 2; case 30
	.short _02051540 - _020510BA - 2; case 31
	.short _02051566 - _020510BA - 2; case 32
	.short _02051686 - _020510BA - 2; case 33
	.short _020516B6 - _020510BA - 2; case 34
	.short _020516CE - _020510BA - 2; case 35
	.short _020515BA - _020510BA - 2; case 36
	.short _020515F8 - _020510BA - 2; case 37
	.short _02051614 - _020510BA - 2; case 38
	.short _020516DE - _020510BA - 2; case 39
	.short _020517B8 - _020510BA - 2; case 40
	.short _02051702 - _020510BA - 2; case 41
	.short _02051744 - _020510BA - 2; case 42
	.short _02051766 - _020510BA - 2; case 43
	.short _02051798 - _020510BA - 2; case 44
_02051114:
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x43
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020511DC
	mov r0, #0x1
	str r0, [r4, #0x34]
	bl FUN_0204ECC0
	b _020517B8
_02051136:
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0x1
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x2
	str r0, [r4, #0x34]
	b _020517B8
_02051150:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _020511DC
	mov r0, #0x5d
	bl FUN_02031588
	mov r0, #0x3
	str r0, [r4, #0x34]
	b _020517B8
_0205116A:
	mov r0, #0x5d
	bl FUN_020315D8
	cmp r0, #0x0
	beq _0205118A
	mov r0, #0x7
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x24]
	ldr r0, [r0, #0x34]
	bl FUN_02058768
	ldr r1, [r4, #0x50]
	ldr r2, [r4, #0x8]
	mov r0, #0x1
	blx r2
	b _020517B8
_0205118A:
	ldr r0, _020514A4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _020511DC
	mov r0, #0x4
	str r0, [r4, #0x34]
	mov r0, #0x5c
	bl FUN_02031588
	mov r0, #0x5
	add r4, #0x43
	strb r0, [r4, #0x0]
	b _020517B8
_020511A6:
	mov r0, #0x5d
	bl FUN_020315D8
	cmp r0, #0x0
	beq _020511C4
	mov r0, #0x7
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x24]
	ldr r0, [r0, #0x34]
	bl FUN_02058768
	ldr r1, [r4, #0x50]
	ldr r2, [r4, #0x8]
	mov r0, #0x1
	blx r2
_020511C4:
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x43
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020511DE
_020511DC:
	b _020517B8
_020511DE:
	mov r0, #0x8
	str r0, [r4, #0x34]
	b _020517B8
_020511E4:
	add r0, r4, #0x0
	bl FUN_02051998
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r5, pc}
_020511F6:
	add r0, r4, #0x0
	bl FUN_02051998
	add r0, r4, #0x0
	bl FreeToHeap
	bl FUN_0204F7FC
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r5, pc}
_0205120C:
	mov r0, #0x5d
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02051224
	mov r0, #0x5
	str r0, [r4, #0x34]
	ldr r1, [r4, #0x50]
	ldr r2, [r4, #0x8]
	mov r0, #0x1
	blx r2
	b _020517B8
_02051224:
	ldr r1, [r4, #0x50]
	ldr r2, [r4, #0x8]
	mov r0, #0x0
	blx r2
	mov r0, #0x5
	str r0, [r4, #0x34]
	b _020517B8
_02051232:
	mov r0, #0xa
	str r0, [r4, #0x34]
	mov r0, #0x5
	add r4, #0x44
	strb r0, [r4, #0x0]
	b _020517B8
_0205123E:
	add r1, r4, #0x0
	add r1, #0x44
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02051256
	add r0, r4, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	add r4, #0x44
	sub r0, r0, #0x1
	strb r0, [r4, #0x0]
	b _020517B8
_02051256:
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	bl FUN_0205AE28
	cmp r0, #0x0
	beq _020512FA
	mov r0, #0xb
	str r0, [r4, #0x34]
	b _020517B8
_0205126A:
	bl FUN_0204ECC0
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0xd
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0xc
	str r0, [r4, #0x34]
	b _020517B8
_02051288:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _020512FA
	mov r0, #0xd
	str r0, [r4, #0x34]
	b _020517B8
_0205129C:
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0xe
	str r0, [r4, #0x34]
	b _020517B8
_020512A8:
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x43
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020512FA
	bl FUN_0204ECC0
	mov r0, #0xf
	str r0, [r4, #0x34]
	b _020517B8
_020512CA:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02051810
	add r0, r4, #0x0
	mov r1, #0xb
	bl FUN_02050ED4
	mov r0, #0x10
	str r0, [r4, #0x34]
	b _020517B8
_020512E0:
	ldr r1, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_02050FC8
	cmp r0, #0x0
	beq _020512FA
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020512FC
	cmp r0, #0x1
	beq _02051302
	cmp r0, #0x2
	beq _02051308
_020512FA:
	b _020517B8
_020512FC:
	mov r0, #0x14
	str r0, [r4, #0x34]
	b _020517B8
_02051302:
	mov r0, #0x13
	str r0, [r4, #0x34]
	b _020517B8
_02051308:
	mov r0, #0x11
	str r0, [r4, #0x34]
	b _020517B8
_0205130E:
	ldr r0, [r4, #0x24]
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0xb
	str r0, [sp, #0x4]
	add r3, r4, #0x0
	add r3, #0x3c
	ldrb r3, [r3, #0x0]
	ldr r1, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_02050E48
	mov r0, #0x12
	str r0, [r4, #0x34]
	b _020517B8
_02051334:
	ldr r1, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_02051020
	cmp r0, #0x0
	beq _02051410
	mov r0, #0xf
	str r0, [r4, #0x34]
	b _020517B8
_02051346:
	ldr r0, [r4, #0x24]
	bl FUN_0204649C
	add r0, r4, #0x0
	add r0, #0x88
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _02051364
	add r0, r4, #0x0
	mov r1, #0x5
	add r0, #0x43
	strb r1, [r0, #0x0]
	mov r0, #0x15
	str r0, [r4, #0x34]
	b _020517B8
_02051364:
	mov r0, #0x1a
	str r0, [r4, #0x34]
	b _020517B8
_0205136A:
	add r0, r4, #0x0
	add r0, #0x3d
	bl FUN_02033564
	add r0, r4, #0x0
	bl FUN_0205104C
	cmp r0, #0x0
	beq _02051410
	add r0, r4, #0x0
	mov r1, #0x5
	add r0, #0x43
	strb r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x34]
	b _020517B8
_0205138A:
	ldr r0, [r4, #0x24]
	bl FUN_0204649C
	add r0, r4, #0x0
	add r0, #0x88
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _020513A0
	mov r0, #0x16
	str r0, [r4, #0x34]
	b _020517B8
_020513A0:
	mov r0, #0x1a
	str r0, [r4, #0x34]
	b _020517B8
_020513A6:
	add r0, r4, #0x0
	bl FUN_0205104C
	cmp r0, #0x0
	beq _02051410
	mov r0, #0x8
	str r0, [r4, #0x34]
	b _020517B8
_020513B6:
	add r0, r4, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x44
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02051410
	mov r0, #0x18
	str r0, [r4, #0x34]
	b _020517B8
_020513D4:
	bl FUN_0204ECC0
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0x13
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x19
	str r0, [r4, #0x34]
	b _020517B8
_020513F2:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _02051410
	mov r0, #0xd
	str r0, [r4, #0x34]
	b _020517B8
_02051406:
	add r0, r4, #0x0
	bl FUN_0205104C
	cmp r0, #0x0
	bne _02051412
_02051410:
	b _020517B8
_02051412:
	bl FUN_0205106C
	cmp r0, #0x0
	beq _02051420
	mov r0, #0x5
	str r0, [r4, #0x34]
	b _020517B8
_02051420:
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _0205142A
	mov r1, #0x1
	b _0205142C
_0205142A:
	mov r1, #0x0
_0205142C:
	add r0, r4, #0x0
	add r0, #0x82
	strb r1, [r0, #0x0]
	add r1, r4, #0x0
	add r1, #0x82
	ldrb r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020519F0
	mov r0, #0x0
	bl FUN_02031588
	ldr r0, [r4, #0x28]
	ldr r2, [r4, #0x74]
	mov r1, #0x0
	bl BufferPlayersName
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0xe
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0xc]
	bl StringExpandPlaceholders
	ldr r1, [r4, #0x10]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x1b
	str r0, [r4, #0x34]
	b _020517B8
_02051472:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _02051574
	bl FUN_0205106C
	cmp r0, #0x0
	beq _0205148E
	mov r0, #0x5
	str r0, [r4, #0x34]
	b _020517B8
_0205148E:
	mov r0, #0x0
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02051574
	add r0, r4, #0x0
	bl FUN_02051A38
	mov r0, #0x1c
	str r0, [r4, #0x34]
	b _020517B8
	.balign 4
_020514A4: .word gMain
_020514A8:
	add r0, r4, #0x0
	bl FUN_02051A80
	cmp r0, #0x0
	beq _02051574
	mov r0, #0x1
	bl FUN_02031588
	mov r0, #0x1d
	str r0, [r4, #0x34]
	b _020517B8
_020514BE:
	mov r0, #0x1
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02051574
	add r0, r4, #0x0
	bl FUN_02051A90
	add r1, r4, #0x0
	add r1, #0x83
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x82
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02051502
	add r0, r4, #0x0
	add r0, #0x83
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02051502
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0x14
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x1e
	str r0, [r4, #0x34]
	b _020517B8
_02051502:
	mov r0, #0x2a
	str r0, [r4, #0x34]
	b _020517B8
_02051508:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _02051574
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x89
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0x11
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x84
	strb r1, [r0, #0x0]
	mov r0, #0x1f
	str r0, [r4, #0x34]
	b _020517B8
_02051540:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _02051574
	add r0, r4, #0x0
	bl FUN_02051AF0
	add r1, r4, #0x0
	add r1, #0x84
	ldrb r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_02051B68
	mov r0, #0x20
	str r0, [r4, #0x34]
	b _020517B8
_02051566:
	add r0, r4, #0x0
	bl FUN_02051D54
	cmp r0, #0x1
	beq _02051576
	cmp r0, #0x2
	beq _0205158C
_02051574:
	b _020517B8
_02051576:
	add r0, r4, #0x0
	bl FUN_02051E24
	mov r0, #0x81
	ldrsb r1, [r4, r0]
	add r0, r4, #0x0
	add r0, #0x84
	strb r1, [r0, #0x0]
	mov r0, #0x24
	str r0, [r4, #0x34]
	b _020517B8
_0205158C:
	add r0, r4, #0x0
	bl FUN_02051E24
	add r0, r4, #0x0
	mov r1, #0xff
	add r0, #0x84
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0xf
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x2
	bl FUN_02031588
	mov r0, #0x27
	str r0, [r4, #0x34]
	b _020517B8
_020515BA:
	add r1, r4, #0x0
	add r1, #0x84
	ldrb r1, [r1, #0x0]
	ldr r0, [r4, #0x50]
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0x28]
	mov r1, #0x1
	bl BufferBoxMonSpeciesName
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0x12
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0xc]
	bl StringExpandPlaceholders
	ldr r1, [r4, #0x10]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x25
	str r0, [r4, #0x34]
	b _020517B8
_020515F8:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _0205168E
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02051C88
	mov r0, #0x26
	str r0, [r4, #0x34]
	b _020517B8
_02051614:
	add r0, r4, #0x0
	bl FUN_02051D54
	cmp r0, #0x1
	beq _02051642
	cmp r0, #0x2
	bne _0205168E
	add r0, r4, #0x0
	bl FUN_02051E24
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0x11
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x1f
	str r0, [r4, #0x34]
	b _020517B8
_02051642:
	mov r0, #0x81
	ldrsb r0, [r4, r0]
	cmp r0, #0x1
	bne _0205167A
	add r0, r4, #0x0
	bl FUN_02051E24
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0xe
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0xc]
	bl StringExpandPlaceholders
	ldr r1, [r4, #0x10]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	mov r0, #0x2
	bl FUN_02031588
	mov r0, #0x27
	str r0, [r4, #0x34]
	b _020517B8
_0205167A:
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x21
	str r0, [r4, #0x34]
	b _020517B8
_02051686:
	bl FUN_0200E308
	cmp r0, #0x0
	bne _02051690
_0205168E:
	b _020517B8
_02051690:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02051810
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0xb
	str r0, [sp, #0x4]
	add r3, r4, #0x0
	add r3, #0x84
	ldrb r3, [r3, #0x0]
	ldr r1, [r4, #0x24]
	ldr r2, [r4, #0x50]
	add r0, r4, #0x0
	bl FUN_02050E48
	mov r0, #0x22
	str r0, [r4, #0x34]
	b _020517B8
_020516B6:
	ldr r1, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_02051020
	cmp r0, #0x0
	beq _020517B8
	ldr r0, [r4, #0x24]
	bl FUN_0204649C
	mov r0, #0x23
	str r0, [r4, #0x34]
	b _020517B8
_020516CE:
	add r0, r4, #0x0
	bl FUN_0205104C
	cmp r0, #0x0
	beq _020517B8
	mov r0, #0x24
	str r0, [r4, #0x34]
	b _020517B8
_020516DE:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _020517B8
	mov r0, #0x2
	bl FUN_020315D8
	cmp r0, #0x0
	beq _020517B8
	add r0, r4, #0x0
	bl FUN_02051AA4
	mov r0, #0x29
	str r0, [r4, #0x34]
	b _020517B8
_02051702:
	add r0, r4, #0x0
	bl FUN_02051AE0
	cmp r0, #0x0
	beq _020517B8
	add r0, r4, #0x0
	add r0, #0x84
	ldrb r0, [r0, #0x0]
	cmp r0, #0xff
	bne _02051722
	mov r0, #0x4
	bl FUN_02031588
	mov r0, #0x2c
	str r0, [r4, #0x34]
	b _020517B8
_02051722:
	add r0, r4, #0x0
	add r0, #0x85
	ldrb r0, [r0, #0x0]
	cmp r0, #0xff
	bne _02051732
	mov r0, #0x2a
	str r0, [r4, #0x34]
	b _020517B8
_02051732:
	add r0, r4, #0x0
	bl FUN_02051B1C
	mov r0, #0x5d
	bl FUN_02031588
	mov r0, #0x2
	str r0, [r4, #0x34]
	b _020517B8
_02051744:
	ldr r0, [r4, #0x2c]
	ldr r2, [r4, #0xc]
	mov r1, #0xf
	bl ReadMsgDataIntoString
	ldr r1, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020517C0
	str r0, [r4, #0x30]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x43
	strb r1, [r0, #0x0]
	mov r0, #0x2b
	str r0, [r4, #0x34]
	b _020517B8
_02051766:
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _020517B8
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x43
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x43
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3c
	bls _020517B8
	mov r0, #0x4
	bl FUN_02031588
	mov r0, #0x2c
	str r0, [r4, #0x34]
	b _020517B8
_02051798:
	mov r0, #0x4
	bl FUN_020315D8
	cmp r0, #0x0
	beq _020517B8
	add r0, r4, #0x0
	add r0, #0x14
	mov r1, #0x0
	bl FUN_0200D0E0
	mov r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r0, #0x0
	blx r2
	mov r0, #0x5
	str r0, [r4, #0x34]
_020517B8:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020517C0
FUN_020517C0: ; 0x020517C0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r5, #0x0
	add r4, #0x14
	add r0, r4, #0x0
	add r6, r1, #0x0
	bl FUN_02019048
	cmp r0, #0x0
	bne _020517F2
	ldr r0, [r5, #0x24]
	add r1, r4, #0x0
	ldr r0, [r0, #0x8]
	mov r2, #0x3
	bl FUN_020545B8
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054608
	b _020517F8
_020517F2:
	add r0, r4, #0x0
	bl FUN_0205464C
_020517F8:
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0x1
	bl FUN_02054658
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02051810
FUN_02051810: ; 0x02051810
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x14
	add r4, r1, #0x0
	bl FUN_02019048
	cmp r0, #0x0
	beq _02051846
	cmp r4, #0x0
	beq _02051836
	add r0, r5, #0x0
	add r0, #0x14
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r5, #0x0
	add r0, #0x14
	bl FUN_02019570
_02051836:
	add r0, r5, #0x0
	add r0, #0x14
	bl FUN_02019178
	add r0, r5, #0x0
	add r0, #0x14
	bl InitWindow
_02051846:
	add r0, r5, #0x0
	add r0, #0x54
	bl FUN_02019048
	cmp r0, #0x0
	beq _02051862
	add r0, r5, #0x0
	add r0, #0x54
	bl FUN_02019178
	add r0, r5, #0x0
	add r0, #0x54
	bl InitWindow
_02051862:
	add r0, r5, #0x0
	add r0, #0x64
	bl FUN_02019048
	cmp r0, #0x0
	beq _0205187E
	add r0, r5, #0x0
	add r0, #0x64
	bl FUN_02019178
	add r5, #0x64
	add r0, r5, #0x0
	bl InitWindow
_0205187E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02051880
FUN_02051880: ; 0x02051880
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	add r6, r1, #0x0
	cmp r0, #0x0
	beq _0205188E
	b _02051992
_0205188E:
	mov r0, #0xb
	mov r1, #0x8c
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x8c
	bl MI_CpuFill8
	add r0, r4, #0x0
	mov r1, #0x5
	add r0, #0x43
	strb r1, [r0, #0x0]
	str r5, [r4, #0x24]
	str r6, [r4, #0x8]
	mov r0, #0xb
	bl ScrStrBufs_new
	str r0, [r4, #0x28]
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0x9
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [r4, #0x2c]
	mov r0, #0xc8
	mov r1, #0xb
	bl String_ctor
	str r0, [r4, #0xc]
	mov r0, #0xc8
	mov r1, #0xb
	bl String_ctor
	str r0, [r4, #0x10]
	add r0, r4, #0x0
	add r0, #0x14
	bl InitWindow
	add r0, r4, #0x0
	add r0, #0x54
	bl InitWindow
	add r0, r4, #0x0
	add r0, #0x64
	bl InitWindow
	mov r0, #0xb
	bl ListMenuCursorNew
	str r0, [r4, #0x78]
	bl FUN_02033534
	add r1, r4, #0x0
	add r1, #0x88
	strb r0, [r1, #0x0]
	mov r1, #0x0
	str r1, [r4, #0x4c]
	str r1, [r4, #0x48]
	add r0, r4, #0x0
	str r1, [r4, #0x50]
	add r0, #0x89
	strb r1, [r0, #0x0]
	bl FUN_02031190
	add r1, r4, #0x0
	add r1, #0x86
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x86
	ldrh r1, [r0, #0x0]
	mov r0, #0x1
	eor r0, r1
	bl FUN_0202DFA4
	str r0, [r4, #0x74]
	add r0, r4, #0x0
	add r0, #0x88
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _02051938
	cmp r0, #0x4
	beq _0205196E
	b _02051974
_02051938:
	bl FUN_02051E54
	add r6, r0, #0x0
	mov r0, #0xb
	add r1, r6, #0x0
	bl AllocFromHeapAtEnd
	str r0, [r4, #0x4c]
	mov r0, #0xb
	add r1, r6, #0x0
	bl AllocFromHeapAtEnd
	str r0, [r4, #0x48]
	mov r0, #0xb
	bl SavArray_Party_alloc
	mov r1, #0x3
	str r0, [r4, #0x50]
	bl InitPartyWithMaxSize
	add r0, r4, #0x0
	mov r1, #0x5
	add r0, #0x44
	strb r1, [r0, #0x0]
	mov r0, #0x17
	str r0, [r4, #0x34]
	b _02051988
_0205196E:
	mov r0, #0x9
	str r0, [r4, #0x34]
	b _02051988
_02051974:
	ldr r0, [r4, #0x24]
	add r0, #0xac
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02051984
	mov r0, #0x9
	str r0, [r4, #0x34]
	b _02051988
_02051984:
	mov r0, #0x0
	str r0, [r4, #0x34]
_02051988:
	ldr r1, _02051994 ; =FUN_02051094
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463CC
_02051992:
	pop {r4-r6, pc}
	.balign 4
_02051994: .word FUN_02051094

	thumb_func_start FUN_02051998
FUN_02051998: ; 0x02051998
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x50]
	cmp r0, #0x0
	beq _020519A6
	bl FreeToHeap
_020519A6:
	ldr r0, [r4, #0x4c]
	cmp r0, #0x0
	beq _020519B0
	bl FreeToHeap
_020519B0:
	ldr r0, [r4, #0x48]
	cmp r0, #0x0
	beq _020519BA
	bl FreeToHeap
_020519BA:
	ldr r0, [r4, #0x2c]
	bl DestroyMsgData
	ldr r0, [r4, #0x28]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0xc]
	bl String_dtor
	ldr r0, [r4, #0x10]
	bl String_dtor
	ldr r0, [r4, #0x78]
	bl DestroyListMenuCursorObj
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02051810
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020519E4
FUN_020519E4: ; 0x020519E4
	ldr r3, _020519EC ; =FUN_0204652C
	ldr r0, [r0, #0x10]
	bx r3
	nop
_020519EC: .word FUN_0204652C

	thumb_func_start FUN_020519F0
FUN_020519F0: ; 0x020519F0
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [r7, #0x24]
	add r5, r1, #0x0
	ldr r0, [r0, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [sp, #0x0]
	ldr r4, [r7, #0x4c]
	bl FUN_020690C4
	add r6, r0, #0x0
	lsl r0, r6, #0x1
	add r0, r6, r0
	str r5, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02051A34
	mov r5, #0x0
_02051A16:
	add r1, r7, r5
	add r1, #0x3d
	ldrb r1, [r1, #0x0]
	ldr r0, [sp, #0x0]
	sub r1, r1, #0x1
	bl GetPartyMonByIndex
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r5, r5, #0x1
	add r4, r4, r6
	cmp r5, #0x3
	blt _02051A16
_02051A34:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02051A38
FUN_02051A38: ; 0x02051A38
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x89
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	tst r1, r0
	bne _02051A7C
	ldr r4, [r5, #0x4c]
	bl FUN_02051E54
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x86
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02051A62
	mov r0, #0x6a
	add r1, r4, #0x0
	bl FUN_02030B3C
	b _02051A6A
_02051A62:
	mov r0, #0x6a
	add r1, r4, #0x0
	bl FUN_02030A78
_02051A6A:
	cmp r0, #0x0
	beq _02051A7C
	add r1, r5, #0x0
	add r1, #0x89
	ldrb r2, [r1, #0x0]
	mov r1, #0x1
	add r5, #0x89
	orr r1, r2
	strb r1, [r5, #0x0]
_02051A7C:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02051A80
FUN_02051A80: ; 0x02051A80
	add r0, #0x89
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _02051A8C
	mov r0, #0x1
	bx lr
_02051A8C:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02051A90
FUN_02051A90: ; 0x02051A90
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020690C4
	lsl r1, r0, #0x1
	ldr r2, [r4, #0x48]
	add r0, r0, r1
	ldr r0, [r2, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02051AA4
FUN_02051AA4: ; 0x02051AA4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x86
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02051ABE
	add r1, r4, #0x0
	mov r0, #0x6b
	add r1, #0x84
	mov r2, #0x1
	bl FUN_02030BC4
	b _02051ACA
_02051ABE:
	add r1, r4, #0x0
	mov r0, #0x6b
	add r1, #0x84
	mov r2, #0x1
	bl FUN_02030ADC
_02051ACA:
	cmp r0, #0x0
	beq _02051ADC
	add r1, r4, #0x0
	add r1, #0x89
	ldrb r2, [r1, #0x0]
	mov r1, #0x1
	add r4, #0x89
	orr r1, r2
	strb r1, [r4, #0x0]
_02051ADC:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02051AE0
FUN_02051AE0: ; 0x02051AE0
	add r0, #0x89
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _02051AEC
	mov r0, #0x1
	bx lr
_02051AEC:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02051AF0
FUN_02051AF0: ; 0x02051AF0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020690C4
	add r6, r0, #0x0
	ldr r0, [r5, #0x50]
	mov r1, #0x3
	bl InitPartyWithMaxSize
	mov r4, #0x0
_02051B04:
	add r1, r4, #0x0
	ldr r2, [r5, #0x48]
	mul r1, r6
	ldr r0, [r5, #0x50]
	add r1, r2, r1
	bl AddMonToParty
	add r4, r4, #0x1
	cmp r4, #0x3
	blt _02051B04
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02051B1C
FUN_02051B1C: ; 0x02051B1C
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_020690C4
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x84
	ldrb r0, [r0, #0x0]
	ldr r2, [r6, #0x48]
	ldr r3, [r6, #0x4c]
	add r1, r0, #0x0
	mul r1, r4
	add r0, r2, r1
	add r1, r6, #0x0
	add r1, #0x85
	ldrb r1, [r1, #0x0]
	add r2, r1, #0x0
	mul r2, r4
	add r1, r3, r2
	add r2, r4, #0x0
	bl MI_CpuCopy8
	ldr r0, [r6, #0x50]
	mov r1, #0x3
	bl InitPartyWithMaxSize
	mov r5, #0x0
_02051B52:
	add r1, r5, #0x0
	ldr r2, [r6, #0x4c]
	mul r1, r4
	ldr r0, [r6, #0x50]
	add r1, r2, r1
	bl AddMonToParty
	add r5, r5, #0x1
	cmp r5, #0x3
	blt _02051B52
	pop {r4-r6, pc}

	thumb_func_start FUN_02051B68
FUN_02051B68: ; 0x02051B68
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	str r0, [sp, #0x20]
	add r0, #0x54
	str r1, [sp, #0x14]
	str r0, [sp, #0x20]
	bl FUN_02019048
	cmp r0, #0x0
	bne _02051C34
	ldr r2, _02051C84 ; =0x0000016A
	mov r0, #0x1
	mov r1, #0x1a
	mov r3, #0x4
	bl NewMsgDataFromNarc
	str r0, [sp, #0x18]
	bl FUN_020690C4
	str r0, [sp, #0x1c]
	mov r0, #0x9
	str r0, [sp, #0x0]
	mov r1, #0xa
	str r1, [sp, #0x4]
	mov r0, #0x8
	str r0, [sp, #0x8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	ldr r0, [r5, #0x24]
	ldr r1, [sp, #0x20]
	ldr r0, [r0, #0x8]
	mov r2, #0x3
	mov r3, #0x15
	bl FUN_02019064
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x24]
	mov r1, #0x3
	ldr r0, [r0, #0x8]
	mov r2, #0x1
	mov r3, #0xb
	bl FUN_0200CB00
	ldr r0, [sp, #0x20]
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r7, #0x0
	add r6, r7, #0x0
	add r4, r7, #0x0
_02051BD6:
	ldr r0, [r5, #0x48]
	mov r1, #0x5
	add r0, r0, r6
	mov r2, #0x0
	bl GetMonData
	add r1, r0, #0x0
	ldr r0, [sp, #0x18]
	ldr r2, [r5, #0xc]
	bl ReadMsgDataIntoString
	str r4, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x20]
	ldr r2, [r5, #0xc]
	mov r1, #0x0
	mov r3, #0x10
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x1c]
	add r7, r7, #0x1
	add r6, r6, r0
	add r4, #0x10
	cmp r7, #0x3
	blt _02051BD6
	ldr r0, [r5, #0x2c]
	ldr r2, [r5, #0xc]
	mov r1, #0x15
	bl ReadMsgDataIntoString
	lsl r0, r7, #0x4
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	ldr r0, [sp, #0x20]
	ldr r2, [r5, #0xc]
	mov r3, #0x10
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x18]
	bl DestroyMsgData
_02051C34:
	mov r0, #0x10
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	mov r2, #0x0
	ldrb r0, [r0, #0x8]
	mov r1, #0xf
	add r3, r2, #0x0
	lsl r0, r0, #0x13
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	bl FillWindowPixelRect
	ldr r3, [sp, #0x14]
	add r1, r5, #0x0
	ldr r0, [r5, #0x78]
	add r1, #0x54
	mov r2, #0x0
	lsl r3, r3, #0x4
	bl ListMenuUpdateCursorObj
	add r0, r5, #0x0
	add r0, #0x54
	mov r1, #0x0
	mov r2, #0x1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r1, r5, #0x0
	ldr r0, [sp, #0x14]
	add r1, #0x81
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	mov r1, #0x4
	add r0, #0x80
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x20]
	str r0, [r5, #0x7c]
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02051C84: .word 0x0000016A

	thumb_func_start FUN_02051C88
FUN_02051C88: ; 0x02051C88
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r7, r5, #0x0
	add r7, #0x64
	add r0, r7, #0x0
	str r1, [sp, #0x14]
	bl FUN_02019048
	cmp r0, #0x0
	bne _02051D0A
	mov r0, #0xb
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x5a
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x24]
	add r1, r7, #0x0
	ldr r0, [r0, #0x8]
	mov r2, #0x3
	mov r3, #0x14
	bl FUN_02019064
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x24]
	mov r1, #0x3
	ldr r0, [r0, #0x8]
	mov r2, #0x1
	mov r3, #0xb
	bl FUN_0200CB00
	add r0, r7, #0x0
	mov r1, #0xf
	bl FillWindowPixelBuffer
	mov r6, #0x0
	add r4, r6, #0x0
_02051CE0:
	add r1, r6, #0x0
	ldr r0, [r5, #0x2c]
	ldr r2, [r5, #0xc]
	add r1, #0x16
	bl ReadMsgDataIntoString
	str r4, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r2, [r5, #0xc]
	add r0, r7, #0x0
	mov r1, #0x0
	mov r3, #0x10
	bl AddTextPrinterParameterized
	add r6, r6, #0x1
	add r4, #0x10
	cmp r6, #0x3
	blt _02051CE0
_02051D0A:
	add r0, r5, #0x0
	mov r1, #0x3
	add r0, #0x80
	strb r1, [r0, #0x0]
	add r1, r5, #0x0
	ldr r0, [sp, #0x14]
	str r7, [r5, #0x7c]
	add r1, #0x81
	strb r0, [r1, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x0]
	ldrb r0, [r7, #0x8]
	mov r2, #0x0
	mov r1, #0xf
	lsl r0, r0, #0x13
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	add r3, r2, #0x0
	bl FillWindowPixelRect
	ldr r3, [sp, #0x14]
	ldr r0, [r5, #0x78]
	ldr r1, [r5, #0x7c]
	mov r2, #0x0
	lsl r3, r3, #0x4
	bl ListMenuUpdateCursorObj
	ldr r0, [r5, #0x7c]
	mov r1, #0x0
	mov r2, #0x1
	mov r3, #0xb
	bl FUN_0200CCA4
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02051D54
FUN_02051D54: ; 0x02051D54
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r0, _02051E1C ; =gMain
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _02051D7E
	mov r0, #0x81
	ldrsb r0, [r4, r0]
	cmp r0, #0x0
	bne _02051D74
	add r0, r4, #0x0
	add r0, #0x80
	ldrb r0, [r0, #0x0]
	b _02051D74
_02051D74:
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x81
	strb r1, [r0, #0x0]
	b _02051DE0
_02051D7E:
	mov r1, #0x80
	tst r1, r0
	beq _02051DA2
	mov r0, #0x81
	ldrsb r1, [r4, r0]
	add r0, r4, #0x0
	add r0, #0x80
	ldrb r0, [r0, #0x0]
	sub r0, r0, #0x1
	cmp r1, r0
	bne _02051D98
	mov r1, #0x0
	b _02051D9A
_02051D98:
	add r1, r1, #0x1
_02051D9A:
	add r0, r4, #0x0
	add r0, #0x81
	strb r1, [r0, #0x0]
	b _02051DE0
_02051DA2:
	mov r1, #0x1
	tst r1, r0
	beq _02051DC8
	ldr r0, _02051E20 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x81
	ldrsb r1, [r4, r0]
	add r4, #0x80
	ldrb r0, [r4, #0x0]
	sub r0, r0, #0x1
	cmp r1, r0
	bge _02051DC2
	add sp, #0x8
	mov r0, #0x1
	pop {r4, pc}
_02051DC2:
	add sp, #0x8
	mov r0, #0x2
	pop {r4, pc}
_02051DC8:
	mov r1, #0x2
	tst r0, r1
	beq _02051DDA
	ldr r0, _02051E20 ; =0x000005DC
	bl FUN_020054C8
	add sp, #0x8
	mov r0, #0x2
	pop {r4, pc}
_02051DDA:
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_02051DE0:
	ldr r0, _02051E20 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x7c]
	mov r1, #0x10
	str r1, [sp, #0x0]
	ldrb r1, [r0, #0x8]
	mov r2, #0x0
	add r3, r2, #0x0
	lsl r1, r1, #0x13
	lsr r1, r1, #0x10
	str r1, [sp, #0x4]
	mov r1, #0xf
	bl FillWindowPixelRect
	mov r3, #0x81
	ldrsb r3, [r4, r3]
	ldr r0, [r4, #0x78]
	ldr r1, [r4, #0x7c]
	mov r2, #0x0
	lsl r3, r3, #0x4
	bl ListMenuUpdateCursorObj
	ldr r0, [r4, #0x7c]
	bl FUN_02019548
	mov r0, #0x0
	add sp, #0x8
	pop {r4, pc}
	nop
_02051E1C: .word gMain
_02051E20: .word 0x000005DC

	thumb_func_start FUN_02051E24
FUN_02051E24: ; 0x02051E24
	ldr r3, _02051E2C ; =FUN_0200CCF8
	ldr r0, [r0, #0x7c]
	mov r1, #0x1
	bx r3
	.balign 4
_02051E2C: .word FUN_0200CCF8

	thumb_func_start FUN_02051E30
FUN_02051E30: ; 0x02051E30
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r3, #0x0
	bl FUN_020519E4
	add r1, r0, #0x0
	add r1, #0x86
	ldrh r1, [r1, #0x0]
	cmp r1, r4
	beq _02051E52
	add r1, r0, #0x0
	add r1, #0x89
	ldrb r2, [r1, #0x0]
	mov r1, #0x2
	add r0, #0x89
	orr r1, r2
	strb r1, [r0, #0x0]
_02051E52:
	pop {r4, pc}

	thumb_func_start FUN_02051E54
FUN_02051E54: ; 0x02051E54
	push {r3, lr}
	bl FUN_020690C4
	lsl r1, r0, #0x1
	add r0, r0, r1
	add r0, r0, #0x4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02051E64
FUN_02051E64: ; 0x02051E64
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_020519E4
	add r1, r0, #0x0
	add r1, #0x86
	ldrh r1, [r1, #0x0]
	cmp r1, r4
	beq _02051E7C
	ldr r0, [r0, #0x48]
	pop {r4, pc}
_02051E7C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02051E80
FUN_02051E80: ; 0x02051E80
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r3, #0x0
	add r4, r2, #0x0
	bl FUN_020519E4
	add r1, r0, #0x0
	add r1, #0x86
	ldrh r1, [r1, #0x0]
	cmp r1, r5
	beq _02051EAC
	ldrb r2, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x85
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x89
	ldrb r2, [r1, #0x0]
	mov r1, #0x2
	add r0, #0x89
	orr r1, r2
	strb r1, [r0, #0x0]
_02051EAC:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02051EB0
FUN_02051EB0: ; 0x02051EB0
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r0, [r4, #0x24]
	add r2, r1, #0x0
	bl FUN_02050BF8
	add r6, r0, #0x0
	ldr r0, [r4, #0x28]
	cmp r0, #0x7
	bls _02051ED6
	b _02052036
_02051ED6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02051EE2: ; jump table (using 16-bit offset)
	.short _02051EF2 - _02051EE2 - 2; case 0
	.short _02051F7C - _02051EE2 - 2; case 1
	.short _02051FCC - _02051EE2 - 2; case 2
	.short _02051FDC - _02051EE2 - 2; case 3
	.short _02051FEC - _02051EE2 - 2; case 4
	.short _02051FFE - _02051EE2 - 2; case 5
	.short _0205200C - _02051EE2 - 2; case 6
	.short _02052028 - _02051EE2 - 2; case 7
_02051EF2:
	mov r0, #0x4
	bl ScrStrBufs_new
	str r0, [r4, #0x18]
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0x9
	mov r3, #0x4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x1c]
	mov r0, #0xc8
	mov r1, #0x4
	bl String_ctor
	str r0, [r4, #0x0]
	mov r0, #0xc8
	mov r1, #0x4
	bl String_ctor
	str r0, [r4, #0x4]
	ldrb r1, [r6, #0x3]
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x0]
	add r1, r1, #0x2
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x24]
	bl FUN_0202DFA4
	add r2, r0, #0x0
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	bl BufferPlayersName
	ldr r0, [r4, #0x18]
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x0]
	bl StringExpandPlaceholders
	add r1, r4, #0x0
	ldr r0, [r5, #0x8]
	add r1, #0x8
	mov r2, #0x3
	bl FUN_020545B8
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x8
	bl FUN_02054608
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	add r2, r0, #0x0
	add r0, r4, #0x0
	ldr r1, [r4, #0x4]
	add r0, #0x8
	mov r3, #0x1
	bl FUN_02054658
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_02051F7C:
	ldr r0, [r4, #0x20]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0x0
	beq _0205203A
	ldr r0, _02052040 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _0205203A
	ldr r0, [r4, #0x1c]
	bl DestroyMsgData
	ldr r0, [r4, #0x18]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x0]
	bl String_dtor
	ldr r0, [r4, #0x4]
	bl String_dtor
	add r0, r4, #0x0
	add r0, #0x8
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r4, #0x0
	add r0, #0x8
	bl FUN_02019178
	mov r0, #0x0
	bl MOD05_021D7CA4
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_02051FCC:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0205203A
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_02051FDC:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02038680
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_02051FEC:
	add r0, r5, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _0205203A
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_02051FFE:
	add r0, r5, #0x0
	bl FUN_0204649C
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_0205200C:
	add r0, r5, #0x0
	bl FUN_020464A4
	cmp r0, #0x0
	bne _0205203A
	mov r0, #0x1
	bl MOD05_021D7CA4
	bl FUN_0204CC9C
	ldr r0, [r4, #0x28]
	add r0, r0, #0x1
	str r0, [r4, #0x28]
	b _0205203A
_02052028:
	bl FUN_0204F7FC
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r4-r6, pc}
_02052036:
	mov r0, #0x1
	pop {r4-r6, pc}
_0205203A:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02052040: .word gMain

	thumb_func_start FUN_02052044
FUN_02052044: ; 0x02052044
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	bl FUN_02031190
	add r5, r0, #0x0
	bl FUN_0204E4D4
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204E50C
	add r6, r0, #0x0
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _020520A6
_02052066:
	cmp r4, r5
	beq _0205209C
	add r0, r4, #0x0
	bl FUN_0204E3EC
	cmp r7, r0
	bne _0205209C
	add r0, r4, #0x0
	bl FUN_0204E440
	cmp r6, r0
	bne _0205209C
	mov r0, #0xb
	mov r1, #0x2c
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	str r4, [r2, #0x24]
	mov r0, #0x0
	str r0, [r2, #0x28]
	ldr r0, [sp, #0x0]
	ldr r1, _020520A8 ; =FUN_02051EB0
	bl FUN_020463CC
	bl FUN_02037760
	pop {r3-r7, pc}
_0205209C:
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _02052066
_020520A6:
	pop {r3-r7, pc}
	.balign 4
_020520A8: .word FUN_02051EB0
