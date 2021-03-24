    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206367C
FUN_0206367C: ; 0x0206367C
	add r0, #0xb4
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02063684
FUN_02063684: ; 0x02063684
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02063818
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x0
	bl FUN_0205F264
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_02034F88
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	mov r1, #0x0
	bl FUN_0202AB68
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0x74
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F214
	cmp r0, #0x0
	bne _020636DA
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	ldr r1, [r5, #0x1c]
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_02060478
	add r0, r4, #0x0
	bl FUN_020603F0
_020636DA:
	pop {r3-r5, pc}

	thumb_func_start FUN_020636DC
FUN_020636DC: ; 0x020636DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0xb4
	ldr r1, [r1, #0x0]
	cmp r1, #0x1
	beq _020637A6
	bl FUN_02063818
	cmp r0, #0x0
	bne _020636F8
	add r0, r5, #0x0
	bl FUN_0206384C
_020636F8:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F254
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x0
	bl FUN_0205F264
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_02034F88
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	mov r1, #0x0
	bl FUN_0202AB68
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0x74
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0202A9B0
	ldr r1, [r5, #0x1c]
	ldr r1, [r1, #0x0]
	bl FUN_02060478
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034930
	cmp r0, #0x0
	bne _02063758
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	bl FUN_0205F284
	add r0, r4, #0x0
	bl FUN_0205F2B4
_02063758:
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034E20
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0206377C
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0x0]
	bl MapHeader_IsBikeAllowed
	cmp r0, #0x0
	bne _0206377C
	mov r0, #0x0
	str r0, [r4, #0x4]
	b _02063786
_0206377C:
	ldr r0, [r4, #0x4]
	cmp r0, #0x2
	bne _02063786
	mov r0, #0x0
	str r0, [r4, #0x4]
_02063786:
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0x0]
	bl MapHeader_MapIsOnOverworldMatrix
	cmp r0, #0x0
	beq _020637A6
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034E0C
	ldr r2, [r5, #0x1c]
	ldr r1, [r2, #0x8]
	ldr r2, [r2, #0xc]
	bl FUN_0204AE04
_020637A6:
	pop {r3-r5, pc}

	thumb_func_start FUN_020637A8
FUN_020637A8: ; 0x020637A8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F204
	ldr r0, [r4, #0xc]
	bl FUN_0202A9B0
	bl FUN_020603C8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020637C4
FUN_020637C4: ; 0x020637C4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F204
	ldr r0, [r4, #0xc]
	bl FUN_0202A9B0
	bl FUN_020603C8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020637E0
FUN_020637E0: ; 0x020637E0
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F204
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020637F0
FUN_020637F0: ; 0x020637F0
	push {r4, lr}
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r4, r0, #0x0
	bl FUN_0205ED2C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205F358
	pop {r4, pc}

	thumb_func_start FUN_02063808
FUN_02063808: ; 0x02063808
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0202A9B0
	bl FUN_020603C8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02063818
FUN_02063818: ; 0x02063818
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034F1C
	add r1, r0, #0x0
	beq _02063846
	add r0, r4, #0x0
	bl FUN_02034FC0
	cmp r0, #0x0
	bne _02063846
	add r0, r4, #0x0
	ldr r1, [r4, #0x1c]
	add r0, #0x98
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	mov r2, #0x20
	bl FUN_020299C0
	mov r0, #0x1
	pop {r4, pc}
_02063846:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0206384C
FUN_0206384C: ; 0x0206384C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034DC8
	ldr r1, [r5, #0x1c]
	ldr r6, [r0, #0x0]
	ldr r4, [r1, #0x0]
	cmp r6, r4
	beq _02063882
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	mov r1, #0x20
	add r5, #0x98
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x0]
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02029880
	add sp, #0x4
	mov r0, #0x1
	pop {r3-r6, pc}
_02063882:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}
