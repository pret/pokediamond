	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

	thumb_func_start MOD20_02252440
MOD20_02252440: ; 0x02252440
	ldr r3, _02252444 ; =FUN_02037790
	bx r3
	.align 2, 0
_02252444: .word FUN_02037790
	thumb_func_end MOD20_02252440

	thumb_func_start MOD20_02252448
MOD20_02252448: ; 0x02252448
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #3
	str r2, [sp]
	mov r1, #7
	lsl r2, r0, #0xe
	add r7, r3, #0
	bl FUN_0201681C
	mov r0, #3
	mov r1, #8
	lsl r2, r0, #0xe
	bl FUN_0201681C
	mov r0, #7
	mov r1, #0x60
	bl AllocFromHeap
	add r4, r0, #0
	beq _022524B2
	str r4, [r5]
	ldr r0, [sp]
	str r6, [r4, #0x5c]
	str r0, [r4, #0x54]
	bl Sav2_Poketch_get
	str r0, [r4, #0x58]
	ldr r0, [sp, #0x18]
	str r7, [r4, #0x4c]
	str r0, [r4, #0x50]
	add r0, r4, #0
	bl MOD20_0225253C
	cmp r0, #0
	beq _022524B2
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	ldr r0, _022524B4 ; =MOD20_022525F0
	str r5, [r4, #0x34]
	add r1, r4, #0
	mov r2, #4
	bl FUN_0200CA44
	str r0, [r4, #0x38]
	ldr r0, _022524B8 ; =MOD20_0225259C
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
_022524B2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022524B4: .word MOD20_022525F0
_022524B8: .word MOD20_0225259C
	thumb_func_end MOD20_02252448

	thumb_func_start MOD20_022524BC
MOD20_022524BC: ; 0x022524BC
	push {r3, lr}
	ldrb r1, [r0]
	cmp r1, #3
	beq _022524CE
	cmp r1, #4
	beq _022524CE
	mov r1, #3
	bl MOD20_022525F8
_022524CE:
	pop {r3, pc}
	thumb_func_end MOD20_022524BC

	thumb_func_start MOD20_022524D0
MOD20_022524D0: ; 0x022524D0
	cmp r0, #0
	bne _022524D8
	mov r0, #1
	bx lr
_022524D8:
	mov r0, #0
	bx lr
	thumb_func_end MOD20_022524D0

	thumb_func_start MOD20_022524DC
MOD20_022524DC: ; 0x022524DC
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #5
	bhi _0225252E
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022524F0: ; jump table
	.short _0225252E - _022524F0 - 2 ; case 0
	.short _022524FC - _022524F0 - 2 ; case 1
	.short _0225252E - _022524F0 - 2 ; case 2
	.short _0225252E - _022524F0 - 2 ; case 3
	.short _0225251E - _022524F0 - 2 ; case 4
	.short _02252502 - _022524F0 - 2 ; case 5
_022524FC:
	mov r0, #1
	strb r0, [r4, #4]
	pop {r4, pc}
_02252502:
	ldr r0, [r4, #0x58]
	bl Sav2_Poketch_GetStepCounter
	add r1, r0, #1
	ldr r0, _02252530 ; =0x0001869F
	cmp r1, r0
	bls _02252512
	mov r1, #0
_02252512:
	ldr r0, [r4, #0x58]
	bl Sav2_Poketch_SetStepCounter
	mov r0, #1
	strb r0, [r4, #7]
	pop {r4, pc}
_0225251E:
	ldrb r0, [r4, #2]
	cmp r0, #2
	bne _0225252E
	ldr r1, [r4, #0x44]
	cmp r1, #0
	beq _0225252E
	ldr r0, [r4, #0x48]
	blx r1
_0225252E:
	pop {r4, pc}
	.align 2, 0
_02252530: .word 0x0001869F
	thumb_func_end MOD20_022524DC

	thumb_func_start MOD20_02252534
MOD20_02252534: ; 0x02252534
	ldrb r0, [r0, #3]
	bx lr
	thumb_func_end MOD20_02252534

	thumb_func_start MOD20_02252538
MOD20_02252538: ; 0x02252538
	ldr r0, [r0, #0x14]
	bx lr
	thumb_func_end MOD20_02252538

	thumb_func_start MOD20_0225253C
MOD20_0225253C: ; 0x0225253C
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r2, [r4, #0x50]
	add r0, #0x1c
	add r1, #0x20
	add r3, r4, #0
	bl MOD20_02252C5C
	cmp r0, #0
	beq _02252578
	mov r1, #0
	strb r1, [r4]
	strb r1, [r4, #1]
	strb r1, [r4, #3]
	strb r1, [r4, #4]
	strb r1, [r4, #7]
	strb r1, [r4, #5]
	strb r1, [r4, #6]
	sub r0, r1, #1
	str r0, [r4, #0x14]
	strb r1, [r4, #2]
	add r0, r4, #0
	str r1, [r4, #8]
	bl MOD20_022529C4
	cmp r0, #0
	beq _02252578
	mov r0, #1
	pop {r4, pc}
_02252578:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD20_0225253C

	thumb_func_start MOD20_0225257C
MOD20_0225257C: ; 0x0225257C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl MOD20_02252A08
	add r0, r4, #0
	bl ClosePoketchApp
	ldr r0, [r4, #0x1c]
	bl MOD20_02252E18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD20_0225257C

	thumb_func_start MOD20_0225259C
MOD20_0225259C: ; 0x0225259C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #4
	bhs _022525C0
	cmp r0, #0
	beq _022525B2
	add r0, r4, #0
	bl MOD20_02252A14
_022525B2:
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022525EC ; =MOD20_022544CC
	ldr r1, [r1, r2]
	blx r1
	pop {r3, r4, r5, pc}
_022525C0:
	beq _022525C6
	bl GF_AssertFail
_022525C6:
	ldr r0, [r4, #0x34]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl MOD20_0225257C
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #7
	bl FUN_020168D0
	mov r0, #8
	bl FUN_020168D0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022525EC: .word MOD20_022544CC
	thumb_func_end MOD20_0225259C

	thumb_func_start MOD20_022525F0
MOD20_022525F0: ; 0x022525F0
	mov r0, #0
	strb r0, [r1, #4]
	strb r0, [r1, #7]
	bx lr
	thumb_func_end MOD20_022525F0

	thumb_func_start MOD20_022525F8
MOD20_022525F8: ; 0x022525F8
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	thumb_func_end MOD20_022525F8

	thumb_func_start MOD20_02252600
MOD20_02252600: ; 0x02252600
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #3
	bhi _02252684
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02252616: ; jump table
	.short _0225261E - _02252616 - 2 ; case 0
	.short _0225262E - _02252616 - 2 ; case 1
	.short _0225265A - _02252616 - 2 ; case 2
	.short _02252670 - _02252616 - 2 ; case 3
_0225261E:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl MOD20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_0225262E:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl MOD20_02252EA4
	cmp r0, #0
	beq _02252684
	ldr r0, [r4, #0x58]
	bl Sav2_Poketch_GetSelectedApp
	add r5, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl LoadPoketchApp
	add r0, r4, #0
	add r1, r5, #0
	bl MOD20_02252918
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_0225265A:
	bl MOD20_0225293C
	cmp r0, #0
	beq _02252684
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl MOD20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
_02252670:
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl MOD20_02252EA4
	cmp r0, #0
	beq _02252684
	add r0, r4, #0
	mov r1, #1
	bl MOD20_022525F8
_02252684:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_02252600

	thumb_func_start MOD20_02252688
MOD20_02252688: ; 0x02252688
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #4
	bls _02252694
	b _022527AA
_02252694:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022526A0: ; jump table
	.short _022526AA - _022526A0 - 2 ; case 0
	.short _022526D4 - _022526A0 - 2 ; case 1
	.short _0225271A - _022526A0 - 2 ; case 2
	.short _02252750 - _022526A0 - 2 ; case 3
	.short _0225276C - _022526A0 - 2 ; case 4
_022526AA:
	bl MOD20_02252C08
	cmp r0, #0
	bne _022527AA
	ldr r0, [r4, #8]
	cmp r0, #3
	beq _022526BC
	cmp r0, #5
	bne _022527AA
_022526BC:
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #1
	strb r0, [r4, #5]
	ldr r0, [r4, #0x1c]
	mov r1, #4
	bl MOD20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r4, pc}
_022526D4:
	ldr r0, [r4, #8]
	cmp r0, #3
	beq _022526DE
	cmp r0, #5
	bne _022526E2
_022526DE:
	mov r0, #1
	str r0, [r4, #0xc]
_022526E2:
	ldr r0, [r4, #0x1c]
	bl MOD20_02252EB0
	cmp r0, #0
	beq _022527AA
	ldr r0, [r4, #0x58]
	bl Sav2_Poketch_CycleNextApp
	str r0, [r4, #0x20]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02252710
	ldr r0, [r4, #0x1c]
	mov r1, #9
	bl MOD20_02252E80
	mov r0, #0x1e
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #4
	strb r0, [r4, #1]
	pop {r4, pc}
_02252710:
	mov r0, #3
	str r0, [r4, #0x10]
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_0225271A:
	ldr r1, [r4, #8]
	cmp r1, #3
	beq _02252724
	cmp r1, #5
	bne _0225273A
_02252724:
	ldr r0, [r4, #0x1c]
	mov r1, #9
	bl MOD20_02252E80
	mov r0, #0x1e
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #4
	strb r0, [r4, #1]
	pop {r4, pc}
_0225273A:
	ldr r1, [r4, #0x10]
	cmp r1, #0
	beq _02252746
	sub r0, r1, #1
	str r0, [r4, #0x10]
	pop {r4, pc}
_02252746:
	bl MOD20_0225294C
	mov r0, #3
	strb r0, [r4, #1]
	pop {r4, pc}
_02252750:
	bl MOD20_02252968
	cmp r0, #0
	beq _022527AA
	add r0, r4, #0
	bl ClosePoketchApp
	bl FUN_020893E0
	add r0, r4, #0
	mov r1, #2
	bl MOD20_022525F8
	pop {r4, pc}
_0225276C:
	ldr r0, [r4, #8]
	cmp r0, #3
	beq _02252776
	cmp r0, #5
	bne _0225278C
_02252776:
	ldr r0, [r4, #0x58]
	bl Sav2_Poketch_CycleNextApp
	str r0, [r4, #0x20]
	mov r0, #0x1e
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl MOD20_02252E80
	pop {r4, pc}
_0225278C:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _02252798
	sub r0, r0, #1
	str r0, [r4, #0x10]
	pop {r4, pc}
_02252798:
	ldr r0, [r4, #0x1c]
	mov r1, #0xb
	bl MOD20_02252E80
	add r0, r4, #0
	bl MOD20_0225294C
	mov r0, #3
	strb r0, [r4, #1]
_022527AA:
	pop {r4, pc}
	thumb_func_end MOD20_02252688

	thumb_func_start MOD20_022527AC
MOD20_022527AC: ; 0x022527AC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _022527C0
	cmp r1, #1
	beq _022527E4
	cmp r1, #2
	beq _022527FC
	pop {r3, r4, r5, pc}
_022527C0:
	mov r0, #1
	strb r0, [r4, #6]
	ldr r0, [r4, #0x58]
	bl Sav2_Poketch_GetSelectedApp
	add r5, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl LoadPoketchApp
	add r0, r4, #0
	add r1, r5, #0
	bl MOD20_02252918
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_022527E4:
	bl MOD20_0225293C
	cmp r0, #0
	beq _02252816
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl MOD20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_022527FC:
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl MOD20_02252EA4
	cmp r0, #0
	beq _02252816
	mov r0, #0
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	add r0, r4, #0
	mov r1, #1
	bl MOD20_022525F8
_02252816:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022527AC

	thumb_func_start MOD20_02252818
MOD20_02252818: ; 0x02252818
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #1]
	cmp r1, #3
	bhi _022528AC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0225282E: ; jump table
	.short _02252836 - _0225282E - 2 ; case 0
	.short _02252866 - _0225282E - 2 ; case 1
	.short _0225287A - _0225282E - 2 ; case 2
	.short _02252890 - _0225282E - 2 ; case 3
_02252836:
	ldrb r1, [r4, #2]
	cmp r1, #3
	bhi _022528AC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02252848: ; jump table
	.short _02252860 - _02252848 - 2 ; case 0
	.short _02252850 - _02252848 - 2 ; case 1
	.short _02252856 - _02252848 - 2 ; case 2
	.short _02252860 - _02252848 - 2 ; case 3
_02252850:
	mov r0, #1
	strb r0, [r4, #1]
	pop {r4, pc}
_02252856:
	bl MOD20_0225294C
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_02252860:
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_02252866:
	bl MOD20_0225293C
	cmp r0, #0
	beq _022528AC
	add r0, r4, #0
	bl MOD20_0225294C
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_0225287A:
	bl MOD20_02252968
	cmp r0, #0
	beq _022528AC
	ldr r0, [r4, #0x1c]
	mov r1, #0xe
	bl MOD20_02252E80
	mov r0, #3
	strb r0, [r4, #1]
	pop {r4, pc}
_02252890:
	ldr r0, [r4, #0x1c]
	bl MOD20_02252EB0
	cmp r0, #0
	beq _022528AC
	add r0, r4, #0
	bl ClosePoketchApp
	bl FUN_0201CD04
	add r0, r4, #0
	mov r1, #4
	bl MOD20_022525F8
_022528AC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD20_02252818

	thumb_func_start LoadPoketchApp
LoadPoketchApp: ; 0x022528B0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	bmi _022528BC
	cmp r4, #0x19
	blo _022528C0
_022528BC:
	bl GF_AssertFail
_022528C0:
	mov r0, #0
	ldr r1, [r5, #0x14]
	mvn r0, r0
	cmp r1, r0
	bne _022528F0
	ldr r2, _022528F4 ; =sPoketchAppOverlayMapping
	mov r1, #0
_022528CE:
	ldr r0, [r2]
	cmp r4, r0
	bne _022528E8
	ldr r0, _022528F8 ; =sPoketchAppOverlayMapping + 4
	lsl r1, r1, #3
	ldr r6, [r0, r1]
	mov r1, #2
	add r0, r6, #0
	bl HandleLoadOverlay
	str r4, [r5, #0x14]
	str r6, [r5, #0x18]
	pop {r4, r5, r6, pc}
_022528E8:
	add r1, r1, #1
	add r2, #8
	cmp r1, #0x19
	blo _022528CE
_022528F0:
	pop {r4, r5, r6, pc}
	nop
_022528F4: .word sPoketchAppOverlayMapping
_022528F8: .word sPoketchAppOverlayMapping + 4
	thumb_func_end LoadPoketchApp

	thumb_func_start ClosePoketchApp
ClosePoketchApp: ; 0x022528FC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	ldr r1, [r4, #0x14]
	mvn r0, r0
	cmp r1, r0
	beq _02252916
	ldr r0, [r4, #0x18]
	bl UnloadOverlayByID
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x14]
_02252916:
	pop {r4, pc}
	thumb_func_end ClosePoketchApp

	thumb_func_start MOD20_02252918
MOD20_02252918: ; 0x02252918
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrb r0, [r4, #2]
	cmp r0, #0
	beq _02252926
	bl GF_AssertFail
_02252926:
	add r0, r4, #0
	ldr r2, [r4, #0x4c]
	ldr r3, [r4, #0x14]
	ldr r5, [r4, #0x3c]
	add r0, #0x24
	add r1, r4, #0
	blx r5
	mov r0, #1
	strb r0, [r4, #2]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_02252918

	thumb_func_start MOD20_0225293C
MOD20_0225293C: ; 0x0225293C
	ldrb r0, [r0, #2]
	cmp r0, #2
	bne _02252946
	mov r0, #1
	bx lr
_02252946:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD20_0225293C

	thumb_func_start MOD20_0225294C
MOD20_0225294C: ; 0x0225294C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #2]
	cmp r0, #2
	beq _0225295A
	bl GF_AssertFail
_0225295A:
	ldr r0, [r4, #0x24]
	ldr r1, [r4, #0x40]
	blx r1
	mov r0, #3
	strb r0, [r4, #2]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD20_0225294C

	thumb_func_start MOD20_02252968
MOD20_02252968: ; 0x02252968
	ldrb r0, [r0, #2]
	cmp r0, #0
	bne _02252972
	mov r0, #1
	bx lr
_02252972:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02252968

	thumb_func_start Poketch_InitApp
Poketch_InitApp: ; 0x02252978
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02252440
	str r5, [r0, #0x3c]
	str r4, [r0, #0x40]
	mov r1, #0
	str r1, [r0, #0x44]
	pop {r3, r4, r5, pc}
	thumb_func_end Poketch_InitApp

	thumb_func_start MOD20_0225298C
MOD20_0225298C: ; 0x0225298C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #2]
	cmp r0, #1
	beq _0225299A
	bl GF_AssertFail
_0225299A:
	mov r0, #2
	strb r0, [r4, #2]
	pop {r4, pc}
	thumb_func_end MOD20_0225298C

	thumb_func_start MOD20_022529A0
MOD20_022529A0: ; 0x022529A0
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #2]
	cmp r0, #3
	beq _022529AE
	bl GF_AssertFail
_022529AE:
	mov r0, #0
	strb r0, [r4, #2]
	pop {r4, pc}
	thumb_func_end MOD20_022529A0

	thumb_func_start MOD20_022529B4
MOD20_022529B4: ; 0x022529B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02252440
	str r5, [r0, #0x44]
	str r4, [r0, #0x48]
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022529B4

	thumb_func_start MOD20_022529C4
MOD20_022529C4: ; 0x022529C4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #7
	str r0, [sp]
	ldr r0, _02252A00 ; =MOD20_022544C4
	ldr r2, _02252A04 ; =MOD20_02252A24
	mov r1, #2
	add r3, r4, #0
	bl MOD20_02254130
	str r0, [r4, #0x28]
	cmp r0, #0
	beq _022529F8
	mov r1, #0
	add r2, r1, #0
	mov r3, #7
	bl MOD20_022542AC
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_022529F8:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	nop
_02252A00: .word MOD20_022544C4
_02252A04: .word MOD20_02252A24
	thumb_func_end MOD20_022529C4

	thumb_func_start MOD20_02252A08
MOD20_02252A08: ; 0x02252A08
	ldr r3, _02252A10 ; =MOD20_02254198
	ldr r0, [r0, #0x28]
	bx r3
	nop
_02252A10: .word MOD20_02254198
	thumb_func_end MOD20_02252A08

	thumb_func_start MOD20_02252A14
MOD20_02252A14: ; 0x02252A14
	ldr r3, _02252A20 ; =MOD20_022541B4
	mov r1, #0
	str r1, [r0, #8]
	ldr r0, [r0, #0x28]
	bx r3
	nop
_02252A20: .word MOD20_022541B4
	thumb_func_end MOD20_02252A14

	thumb_func_start MOD20_02252A24
MOD20_02252A24: ; 0x02252A24
	push {r3, r4, r5, r6, r7, lr}
	add r5, r3, #0
	add r4, r0, #0
	add r0, r5, #0
	add r6, r1, #0
	add r7, r2, #0
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252A4C
	cmp r7, #0
	beq _02252A46
	cmp r7, #1
	bne _02252A50
	mov r0, #1
	strb r0, [r5, #3]
	b _02252A50
_02252A46:
	mov r0, #0
	strb r0, [r5, #3]
	b _02252A50
_02252A4C:
	mov r0, #0
	strb r0, [r5, #3]
_02252A50:
	cmp r4, #1
	bne _02252A6A
	add r0, r5, #0
	bl MOD20_02252C08
	cmp r0, #0
	beq _02252AEA
	cmp r7, #1
	bne _02252AEA
	ldr r0, _02252AEC ; =0x0000066E
	bl FUN_020054C8
	pop {r3, r4, r5, r6, r7, pc}
_02252A6A:
	mov r4, #0
	mvn r4, r4
	cmp r7, #0
	beq _02252A78
	cmp r7, #1
	beq _02252A7C
	b _02252A94
_02252A78:
	mov r4, #8
	b _02252A94
_02252A7C:
	add r0, r5, #0
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252A8C
	ldrb r0, [r5, #6]
	cmp r0, #0
	beq _02252A92
_02252A8C:
	mov r4, #6
	mov r6, #0
	b _02252A94
_02252A92:
	mov r4, #7
_02252A94:
	mov r0, #0
	ldr r1, [r5, #0x2c]
	mvn r0, r0
	cmp r1, r0
	beq _02252AA4
	add r0, r4, #0
	add r4, r1, #0
	str r0, [r5, #0x2c]
_02252AA4:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	beq _02252AC0
	ldr r0, [r5, #0x1c]
	add r1, r4, #0
	bl MOD20_02252AF0
	cmp r0, #0
	beq _02252AC0
	sub r0, r4, #6
	cmp r0, #1
	bhi _02252AC0
	str r4, [r5, #0x30]
_02252AC0:
	cmp r6, #2
	beq _02252AE0
	cmp r6, #3
	beq _02252AD6
	cmp r6, #5
	bne _02252AE8
	ldr r0, [r5, #0x28]
	mov r1, #0
	bl MOD20_022542CC
	b _02252AE8
_02252AD6:
	ldr r0, [r5, #0x30]
	cmp r0, #6
	bne _02252AE8
	mov r6, #0
	b _02252AE8
_02252AE0:
	ldr r0, [r5, #0x30]
	cmp r0, #7
	bne _02252AE8
	mov r6, #3
_02252AE8:
	str r6, [r5, #8]
_02252AEA:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02252AEC: .word 0x0000066E
	thumb_func_end MOD20_02252A24

	thumb_func_start MOD20_02252AF0
MOD20_02252AF0: ; 0x02252AF0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_02252AF8:
	add r0, r5, #0
	add r1, r6, #0
	bl MOD20_02252EA4
	cmp r0, #0
	bne _02252B08
	mov r0, #0
	pop {r4, r5, r6, pc}
_02252B08:
	add r4, r4, #1
	cmp r4, #3
	blo _02252AF8
	add r0, r5, #0
	add r1, r6, #0
	bl MOD20_02252E80
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD20_02252AF0

	thumb_func_start MOD20_02252B1C
MOD20_02252B1C: ; 0x02252B1C
	push {r3, lr}
	bl MOD20_02252440
	ldr r0, [r0, #0x1c]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_02252B1C

	thumb_func_start MOD20_02252B28
MOD20_02252B28: ; 0x02252B28
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252B46
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252B46
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_020054C8
_02252B46:
	pop {r4, pc}
	thumb_func_end MOD20_02252B28

	thumb_func_start MOD20_02252B48
MOD20_02252B48: ; 0x02252B48
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252B66
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252B66
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
_02252B66:
	pop {r4, pc}
	thumb_func_end MOD20_02252B48

	thumb_func_start MOD20_02252B68
MOD20_02252B68: ; 0x02252B68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252BB4
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252BB4
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02020AB0
	cmp r0, #0
	beq _02252BB4
	ldr r0, [r5]
	sub r0, #0x10
	cmp r0, #0xbf
	bhs _02252B98
	mov r1, #1
	b _02252B9A
_02252B98:
	mov r1, #0
_02252B9A:
	ldr r0, [r4]
	sub r0, #0x10
	cmp r0, #0x9f
	bhs _02252BA6
	mov r0, #1
	b _02252BA8
_02252BA6:
	mov r0, #0
_02252BA8:
	tst r0, r1
	beq _02252BB0
	mov r0, #1
	pop {r3, r4, r5, pc}
_02252BB0:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02252BB4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02252B68

	thumb_func_start MOD20_02252BB8
MOD20_02252BB8: ; 0x02252BB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252C04
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252C04
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02020ACC
	cmp r0, #0
	beq _02252C04
	ldr r0, [r5]
	sub r0, #0x10
	cmp r0, #0xbf
	bhs _02252BE8
	mov r1, #1
	b _02252BEA
_02252BE8:
	mov r1, #0
_02252BEA:
	ldr r0, [r4]
	sub r0, #0x10
	cmp r0, #0x9f
	bhs _02252BF6
	mov r0, #1
	b _02252BF8
_02252BF6:
	mov r0, #0
_02252BF8:
	tst r0, r1
	beq _02252C00
	mov r0, #1
	pop {r3, r4, r5, pc}
_02252C00:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02252C04:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02252BB8

	thumb_func_start MOD20_02252C08
MOD20_02252C08: ; 0x02252C08
	ldr r3, _02252C10 ; =FUN_0204646C
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_02252C10: .word FUN_0204646C
	thumb_func_end MOD20_02252C08

	thumb_func_start MOD20_02252C14
MOD20_02252C14: ; 0x02252C14
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02252C08
	cmp r0, #0
	bne _02252C2E
	ldrb r0, [r5, #5]
	cmp r0, #0
	bne _02252C2E
	add r0, r4, #0
	bl MOD20_022541B4
_02252C2E:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02252C14

	thumb_func_start MOD20_02252C30
MOD20_02252C30: ; 0x02252C30
	ldrb r0, [r0, #4]
	bx lr
	thumb_func_end MOD20_02252C30

	thumb_func_start MOD20_02252C34
MOD20_02252C34: ; 0x02252C34
	ldrb r0, [r0, #7]
	bx lr
	thumb_func_end MOD20_02252C34

	thumb_func_start MOD20_02252C38
MOD20_02252C38: ; 0x02252C38
	ldr r0, [r0, #0x5c]
	bx lr
	thumb_func_end MOD20_02252C38

	thumb_func_start MOD20_02252C3C
MOD20_02252C3C: ; 0x02252C3C
	ldr r0, [r0, #0x58]
	bx lr
	thumb_func_end MOD20_02252C3C

	thumb_func_start MOD20_02252C40
MOD20_02252C40: ; 0x02252C40
	ldr r0, [r0, #0x54]
	bx lr
	thumb_func_end MOD20_02252C40

	thumb_func_start MOD20_02252C44
MOD20_02252C44: ; 0x02252C44
	push {r3, lr}
	ldr r0, [r0, #0x54]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	cmp r0, #1
	beq _02252C58
	mov r0, #1
	pop {r3, pc}
_02252C58:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD20_02252C44

	thumb_func_start MOD20_02252C5C
MOD20_02252C5C: ; 0x02252C5C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0xea
	add r5, r0, #0
	mov r0, #7
	lsl r1, r1, #2
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	str r0, [r5]
	add r4, r0, #0
	beq _02252D0A
	mov r0, #0x15
	lsl r0, r0, #4
	str r7, [r4, r0]
	ldr r0, [r4, r0]
	bl NNS_G2dResetOamManagerBuffer
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #7
	bl MOD20_02253BA4
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _02252CA6
	ldr r0, [r5]
	bl FreeToHeap
	mov r0, #0
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02252CA6:
	mov r0, #7
	str r6, [r4]
	bl FUN_02016B94
	mov r1, #6
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r0, [sp]
	add r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD20_02252D44
	mov r1, #0x57
	lsl r1, r1, #2
	add r0, r4, r1
	sub r1, #8
	ldr r1, [r4, r1]
	bl MOD20_02253428
	ldr r0, [r5]
	mov r1, #8
	add r0, r0, #4
	bl MOD20_022536F4
	ldr r0, [r5]
	mov r1, #0x88
	add r0, #0x2c
	bl MOD20_02252E5C
	ldr r0, [r5]
	mov r1, #0x8c
	add r0, #0x84
	bl MOD20_02252E5C
	ldr r0, [r5]
	mov r1, #0x90
	add r0, #0xdc
	bl MOD20_02252E5C
	ldr r0, _02252D10 ; =MOD20_02252D14
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA98
	mov r1, #0x56
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02252D0A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02252D10: .word MOD20_02252D14
	thumb_func_end MOD20_02252C5C

	thumb_func_start MOD20_02252D14
MOD20_02252D14: ; 0x02252D14
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r3, _02252D20 ; =MOD20_02253C78
	ldr r0, [r1, r0]
	bx r3
	nop
_02252D20: .word MOD20_02253C78
	thumb_func_end MOD20_02252D14

	thumb_func_start MOD20_02252D24
MOD20_02252D24: ; 0x02252D24
	push {r3, lr}
	bl MOD20_02252B1C
	mov r1, #0x55
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_02252D24

	thumb_func_start MOD20_02252D34
MOD20_02252D34: ; 0x02252D34
	push {r3, lr}
	bl MOD20_02252B1C
	mov r1, #6
	lsl r1, r1, #6
	ldr r0, [r0, r1]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_02252D34

	thumb_func_start MOD20_02252D44
MOD20_02252D44: ; 0x02252D44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xc
	mov r1, #0
	add r2, sp, #0
	mov r3, #7
	bl FUN_02006C08
	add r4, r0, #0
	beq _02252D7A
	ldr r0, [sp]
	mov r2, #0x62
	lsl r2, r2, #2
	add r1, r5, r2
	ldr r0, [r0, #0xc]
	add r2, #0x78
	bl MIi_CpuCopy32
	mov r1, #0x62
	lsl r1, r1, #2
	add r0, r5, r1
	add r1, #0x78
	bl DC_FlushRange
	add r0, r4, #0
	bl FreeToHeap
_02252D7A:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02252D44

	thumb_func_start MOD20_02252D7C
MOD20_02252D7C: ; 0x02252D7C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	bl MOD20_02252B1C
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD20_02252C3C
	bl Sav2_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r1, r1, #2
	add r5, r4, r1
	lsl r4, r0, #6
	add r0, r5, r4
	lsl r1, r6, #5
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r5, r4
	add r1, r7, #0
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_02252D7C

	thumb_func_start MOD20_02252DB4
MOD20_02252DB4: ; 0x02252DB4
	push {r3, r4, r5, lr}
	bl MOD20_02252B1C
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD20_02252C3C
	bl Sav2_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r0, r0, #5
	lsl r1, r1, #2
	add r0, #0x10
	add r4, r4, r1
	lsl r5, r0, #1
	add r0, r4, r5
	mov r1, #0
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r4, r5
	mov r1, #0
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02252DB4

	thumb_func_start MOD20_02252DEC
MOD20_02252DEC: ; 0x02252DEC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD20_02252B1C
	add r4, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD20_02252C3C
	bl Sav2_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r1, r1, #2
	add r1, r4, r1
	lsl r0, r0, #6
	add r0, r1, r0
	add r1, r5, #0
	mov r2, #0x20
	bl MIi_CpuCopy16
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02252DEC

	thumb_func_start MOD20_02252E18
MOD20_02252E18: ; 0x02252E18
	push {r4, lr}
	add r4, r0, #0
	beq _02252E58
	mov r0, #0x57
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD20_022535A4
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02252E36
	bl MOD20_02253C4C
_02252E36:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02252E44
	bl FreeToHeap
_02252E44:
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02252E52
	bl FUN_0200CAB4
_02252E52:
	add r0, r4, #0
	bl FreeToHeap
_02252E58:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD20_02252E18

	thumb_func_start MOD20_02252E5C
MOD20_02252E5C: ; 0x02252E5C
	push {r4, r5}
	mov r2, #0xf
	ldr r5, _02252E7C ; =MOD20_022545EC
	mov r4, #0
	lsl r2, r2, #0xc
_02252E66:
	ldrh r3, [r5]
	add r4, r4, #1
	add r5, r5, #2
	add r3, r1, r3
	orr r3, r2
	strh r3, [r0]
	add r0, r0, #2
	cmp r4, #0x2c
	blo _02252E66
	pop {r4, r5}
	bx lr
	.align 2, 0
_02252E7C: .word MOD20_022545EC
	thumb_func_end MOD20_02252E5C

	thumb_func_start MOD20_02252E80
MOD20_02252E80: ; 0x02252E80
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, r2, #4
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	ldr r0, _02252EA0 ; =MOD20_02254644
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02252EA0: .word MOD20_02254644
	thumb_func_end MOD20_02252E80

	thumb_func_start MOD20_02252EA4
MOD20_02252EA4: ; 0x02252EA4
	ldr r3, _02252EAC ; =MOD20_02253794
	add r0, r0, #4
	bx r3
	nop
_02252EAC: .word MOD20_02253794
	thumb_func_end MOD20_02252EA4

	thumb_func_start MOD20_02252EB0
MOD20_02252EB0: ; 0x02252EB0
	ldr r3, _02252EB8 ; =MOD20_022537B8
	add r0, r0, #4
	bx r3
	nop
_02252EB8: .word MOD20_022537B8
	thumb_func_end MOD20_02252EB0

	thumb_func_start MOD20_02252EBC
MOD20_02252EBC: ; 0x02252EBC
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, r0, #4
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD20_02252EBC

	thumb_func_start MOD20_02252ED0
MOD20_02252ED0: ; 0x02252ED0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	mov r0, #0
	bl GXS_SetGraphicsMode
	mov r0, #0x80
	bl GX_SetBankForSubBG
	mov r0, #1
	lsl r0, r0, #8
	bl GX_SetBankForSubOBJ
	ldr r2, _02252FD8 ; =0x04001000
	ldr r0, _02252FDC ; =0xFFCFFFEF
	ldr r1, [r2]
	and r1, r0
	mov r0, #0x10
	orr r0, r1
	str r0, [r2]
	bl GX_DisableEngineBLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	ldr r2, _02252FE0 ; =MOD20_022545B4
	mov r1, #4
	mov r3, #0
	bl FUN_02016C18
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	ldr r2, _02252FE4 ; =MOD20_022545D0
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #7
	str r0, [sp, #0xc]
	mov r0, #0xc
	lsl r2, r0, #5
	ldr r2, [r4, r2]
	mov r1, #0xe
	mov r3, #4
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #7
	str r0, [sp, #0xc]
	mov r0, #0xc
	lsl r2, r0, #5
	ldr r2, [r4, r2]
	mov r1, #0xf
	mov r3, #4
	bl FUN_020068C8
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD20_02252C44
	add r3, r0, #0
	mov r0, #0x1e
	lsl r0, r0, #4
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0xd
	mov r2, #4
	lsl r3, r3, #5
	bl FUN_02006948
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r1, #0x18
	str r1, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	mov r2, #0xd8
	bl FUN_02018540
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_02017CD0
	ldr r0, _02252FD8 ; =0x04001000
	ldr r1, _02252FE8 ; =0xFFFFE0FF
	ldr r2, [r0]
	and r2, r1
	mov r1, #0x13
	lsl r1, r1, #8
	orr r1, r2
	str r1, [r0]
	ldr r2, [r0]
	ldr r1, _02252FEC ; =0xFFFF1FFF
	and r1, r2
	str r1, [r0]
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_02252FD8: .word 0x04001000
_02252FDC: .word 0xFFCFFFEF
_02252FE0: .word MOD20_022545B4
_02252FE4: .word MOD20_022545D0
_02252FE8: .word 0xFFFFE0FF
_02252FEC: .word 0xFFFF1FFF
	thumb_func_end MOD20_02252ED0

	thumb_func_start MOD20_02252FF0
MOD20_02252FF0: ; 0x02252FF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	add r0, r1, #0
	bl MOD20_022538A8
	add r4, r0, #0
	ldr r0, [sp, #0x10]
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	bl MOD20_022538AC
	cmp r0, #0
	beq _0225301C
	cmp r0, #1
	beq _02253028
	cmp r0, #2
	beq _022530F6
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0225301C:
	mov r0, #0
	strh r0, [r4]
	strh r0, [r4, #2]
	ldr r0, [sp, #0x10]
	bl MOD20_022538B0
_02253028:
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	ldrh r0, [r4]
	cmp r0, #0
	beq _022530FC
	mov r0, #0
	strh r0, [r4]
	ldrh r0, [r4, #2]
	add r0, #0xc
	strh r0, [r4, #2]
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bls _02253048
	mov r0, #0x28
	strh r0, [r4, #2]
_02253048:
	ldrh r1, [r4, #2]
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1e
	lsr r0, r1, #2
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	mov r1, #0xc
	sub r6, r1, r0
	lsl r0, r0, #1
	str r0, [sp, #0x14]
	lsl r0, r6, #0x18
	ldr r1, [sp, #0x14]
	add r7, r3, r2
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x18
	lsl r1, r1, #0x18
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xf
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0x40
	mov r3, #2
	bl FUN_02018540
	cmp r7, #0
	beq _022530DA
	sub r0, r6, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r1, #0x18
	add r2, r7, #0
	add r2, #0xd8
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FUN_02018540
	ldr r0, [sp, #0x14]
	mov r2, #0xd8
	add r0, r6, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r1, #0x18
	sub r2, r2, r7
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FUN_02018540
_022530DA:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #5
	bl FUN_02017CD0
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bne _022530FC
	ldr r0, [sp, #0x10]
	bl MOD20_022538B0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_022530F6:
	ldr r0, [sp, #0x10]
	bl MOD20_02252EBC
_022530FC:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_02252FF0

	thumb_func_start MOD20_02253100
MOD20_02253100: ; 0x02253100
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	add r0, r1, #0
	bl MOD20_022538A8
	add r4, r0, #0
	ldr r0, [sp, #0x10]
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	bl MOD20_022538AC
	cmp r0, #0
	beq _0225312C
	cmp r0, #1
	beq _02253138
	cmp r0, #2
	beq _0225321E
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0225312C:
	mov r0, #0
	strh r0, [r4]
	strh r0, [r4, #2]
	ldr r0, [sp, #0x10]
	bl MOD20_022538B0
_02253138:
	ldrh r0, [r4]
	add r0, r0, #1
	strh r0, [r4]
	ldrh r0, [r4]
	cmp r0, #0
	beq _02253224
	mov r0, #0
	strh r0, [r4]
	ldrh r0, [r4, #2]
	add r0, #8
	strh r0, [r4, #2]
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bls _02253158
	mov r0, #0x28
	strh r0, [r4, #2]
_02253158:
	ldrh r0, [r4, #2]
	mov r3, #2
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	lsr r7, r0, #2
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r6, r2, r1
	mov r0, #0x16
	sub r0, r0, r7
	str r0, [sp, #0x14]
	lsl r1, r7, #0x18
	str r3, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xf
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0xd8
	bl FUN_02018540
	ldr r0, [sp, #0x14]
	lsl r1, r7, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	str r1, [sp, #8]
	mov r1, #0xf
	str r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #5
	mov r2, #0xd8
	mov r3, #2
	bl FUN_02018540
	cmp r6, #0
	beq _02253202
	mov r0, #0
	str r0, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	sub r3, r6, #1
	mov r2, #0xdb
	sub r2, r2, r3
	lsl r2, r2, #0x10
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FUN_02018540
	ldr r0, [sp, #0x14]
	add r6, #0xd4
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r1, #0x18
	lsl r2, r6, #0x10
	str r1, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r5, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	mov r3, #2
	bl FUN_02018540
_02253202:
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #5
	bl FUN_02017CD0
	ldrh r0, [r4, #2]
	cmp r0, #0x28
	bne _02253224
	ldr r0, [sp, #0x10]
	bl MOD20_022538B0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_0225321E:
	ldr r0, [sp, #0x10]
	bl MOD20_02252EBC
_02253224:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_02253100

	thumb_func_start MOD20_02253228
MOD20_02253228: ; 0x02253228
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A8
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	add r2, r0, #0
	cmp r2, #4
	bhs _02253280
	mov r3, #2
	str r3, [sp]
	mov r1, #0x18
	mov r6, #0xd7
	sub r2, r6, r2
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	bl FUN_02018540
	add r0, r6, #0
	add r0, #0xa9
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD20_022538B0
	add sp, #0x10
	pop {r4, r5, r6, pc}
_02253280:
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD20_02253228

	thumb_func_start MOD20_0225328C
MOD20_0225328C: ; 0x0225328C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A8
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	add r2, r0, #0
	cmp r2, #4
	bhs _022532E4
	mov r3, #2
	str r3, [sp]
	mov r1, #0x18
	mov r6, #0xdb
	sub r2, r6, r2
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	bl FUN_02018540
	add r0, r6, #0
	add r0, #0xa5
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD20_022538B0
	add sp, #0x10
	pop {r4, r5, r6, pc}
_022532E4:
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD20_0225328C

	thumb_func_start MOD20_022532F0
MOD20_022532F0: ; 0x022532F0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	mov r0, #0xb
	add r2, r4, #0
	str r0, [sp]
	mov r1, #4
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	add r2, #0x84
	mov r3, #0x1b
	bl FUN_02018148
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_02017CD0
	ldr r0, _02253334 ; =0x00000671
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02253334: .word 0x00000671
	thumb_func_end MOD20_022532F0

	thumb_func_start MOD20_02253338
MOD20_02253338: ; 0x02253338
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	mov r0, #0xb
	add r2, r4, #0
	str r0, [sp]
	mov r1, #4
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	add r2, #0x2c
	mov r3, #0x1b
	bl FUN_02018148
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_02253338

	thumb_func_start MOD20_02253378
MOD20_02253378: ; 0x02253378
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	mov r0, #0xb
	add r2, r4, #0
	str r0, [sp]
	mov r1, #4
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	add r2, #0xdc
	mov r3, #0x1b
	bl FUN_02018148
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_02017CD0
	ldr r0, _022533BC ; =0x0000066F
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022533BC: .word 0x0000066F
	thumb_func_end MOD20_02253378

	thumb_func_start MOD20_022533C0
MOD20_022533C0: ; 0x022533C0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	mov r1, #0x57
	add r4, r0, #0
	lsl r1, r1, #2
	add r1, r4, r1
	bl MOD20_02253430
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r1, [r4]
	add r0, r4, r0
	bl MOD20_0225354C
	add r0, r5, #0
	bl MOD20_02252EBC
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_022533C0

	thumb_func_start MOD20_022533EC
MOD20_022533EC: ; 0x022533EC
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r1, r0, #0
	mov r0, #0x57
	lsl r0, r0, #2
	add r0, r1, r0
	ldr r1, [r1]
	bl MOD20_0225354C
	add r0, r4, #0
	bl MOD20_02252EBC
	pop {r4, pc}
	thumb_func_end MOD20_022533EC

	thumb_func_start MOD20_0225340C
MOD20_0225340C: ; 0x0225340C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	mov r1, #0x57
	lsl r1, r1, #2
	add r0, r0, r1
	bl MOD20_022535A4
	add r0, r4, #0
	bl MOD20_02252EBC
	pop {r4, pc}
	thumb_func_end MOD20_0225340C

	thumb_func_start MOD20_02253428
MOD20_02253428: ; 0x02253428
	mov r2, #0
	str r2, [r0]
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_02253428

	thumb_func_start MOD20_02253430
MOD20_02253430: ; 0x02253430
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #7
	str r0, [sp]
	add r0, r4, #0
	add r0, #8
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl MOD20_02253FBC
	cmp r0, #0
	beq _022534CC
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #2
	bl FUN_02006A34
	mov r0, #0x60
	str r0, [sp]
	mov r0, #7
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0xc
	mov r2, #5
	add r3, r1, #0
	bl FUN_02006930
	add r0, r5, #0
	mov r1, #0xf
	bl MOD20_022534D4
	add r2, r4, #0
	ldr r0, [r4, #4]
	ldr r1, _022534D0 ; =MOD20_022545A4
	add r2, #8
	bl MOD20_02253E74
	str r0, [r4, #0x1c]
	cmp r0, #0
	beq _022534CC
	add r2, r4, #0
	ldr r0, [r4, #4]
	ldr r1, _022534D0 ; =MOD20_022545A4
	add r2, #8
	bl MOD20_02253E74
	str r0, [r4, #0x20]
	cmp r0, #0
	bne _022534AE
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x1c]
	bl MOD20_02253F14
	add sp, #0xc
	pop {r4, r5, pc}
_022534AE:
	mov r1, #1
	lsl r1, r1, #0x10
	mov r2, #0
	bl MOD20_02253F54
	ldr r0, [r4, #0x1c]
	mov r1, #0xf
	bl MOD20_02253F9C
	ldr r0, [r4, #0x20]
	mov r1, #0xf
	bl MOD20_02253F9C
	mov r0, #1
	str r0, [r4]
_022534CC:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022534D0: .word MOD20_022545A4
	thumb_func_end MOD20_02253430

	thumb_func_start MOD20_022534D4
MOD20_022534D4: ; 0x022534D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x61
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r4, r1, #0
	bl MOD20_02252C3C
	bl Sav2_Poketch_GetScreenTint
	mov r1, #0x62
	lsl r0, r0, #5
	lsl r1, r1, #2
	add r0, r0, #1
	add r2, r5, r1
	lsl r0, r0, #1
	add r0, r2, r0
	add r1, #0x5a
	mov r2, #2
	bl GXS_LoadBGPltt
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	bl MOD20_02252DEC
	ldr r1, _02253548 ; =0x0000038A
	add r0, r1, #6
	ldrh r2, [r5, r1]
	ldrh r0, [r5, r0]
	strh r0, [r5, r1]
	add r0, r1, #6
	strh r2, [r5, r0]
	add r0, r1, #0
	add r2, r1, #0
	add r0, #0xe
	add r2, #0x1c
	ldrh r3, [r5, r2]
	add r2, r1, #0
	ldrh r0, [r5, r0]
	add r2, #0xe
	strh r3, [r5, r2]
	add r2, r1, #0
	add r2, #0x1c
	strh r0, [r5, r2]
	sub r0, r1, #2
	add r0, r5, r0
	mov r1, #0x20
	bl DC_FlushRange
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r5, r0
	lsl r1, r4, #5
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, pc}
	.align 2, 0
_02253548: .word 0x0000038A
	thumb_func_end MOD20_022534D4

	thumb_func_start MOD20_0225354C
MOD20_0225354C: ; 0x0225354C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02253596
	ldr r0, [r1]
	ldr r2, _02253598 ; =0x04000280
	mov r3, #0
	add r0, r0, #1
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_0225356E:
	ldrh r1, [r2]
	tst r1, r0
	bne _0225356E
	ldr r0, _0225359C ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_0225357E:
	ldrh r2, [r3]
	tst r2, r0
	bne _0225357E
	ldr r0, _022535A0 ; =0x040002A8
	ldr r5, [r0]
	ldr r0, [r4, #0x1c]
	bl MOD20_02253F28
	ldr r0, [r4, #0x20]
	add r1, r5, #0
	bl MOD20_02253F28
_02253596:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02253598: .word 0x04000280
_0225359C: .word 0x040002A0
_022535A0: .word 0x040002A8
	thumb_func_end MOD20_0225354C

	thumb_func_start MOD20_022535A4
MOD20_022535A4: ; 0x022535A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _022535CA
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x1c]
	bl MOD20_02253F14
	ldr r0, [r4, #4]
	ldr r1, [r4, #0x20]
	bl MOD20_02253F14
	add r0, r4, #0
	add r0, #8
	bl MOD20_02254014
	mov r0, #0
	str r0, [r4]
_022535CA:
	pop {r4, pc}
	thumb_func_end MOD20_022535A4

	thumb_func_start MOD20_022535CC
MOD20_022535CC: ; 0x022535CC
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r6, #0
	bl MOD20_022538A8
	add r0, r6, #0
	bl MOD20_022538AC
	add r5, r0, #0
	cmp r5, #3
	bhi _0225365E
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022535F8: ; jump table
	.short _02253600 - _022535F8 - 2 ; case 0
	.short _0225361C - _022535F8 - 2 ; case 1
	.short _0225361C - _022535F8 - 2 ; case 2
	.short _0225361C - _022535F8 - 2 ; case 3
_02253600:
	mov r0, #6
	str r0, [sp]
	ldr r0, _02253664 ; =0x04001050
	mov r1, #2
	mov r2, #0x1c
	mov r3, #0x1a
	bl G2x_SetBlendAlpha_
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_02017CD0
_0225361C:
	mov r3, #2
	str r3, [sp]
	mov r1, #0x18
	mov r2, #0xdb
	sub r2, r2, r5
	lsl r2, r2, #0x10
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	lsr r2, r2, #0x10
	bl FUN_02018540
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_02017CD0
	cmp r5, #3
	bne _02253658
	add r0, r6, #0
	bl MOD20_02252EBC
	add sp, #0x10
	pop {r4, r5, r6, pc}
_02253658:
	add r0, r6, #0
	bl MOD20_022538B0
_0225365E:
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02253664: .word 0x04001050
	thumb_func_end MOD20_022535CC

	thumb_func_start MOD20_02253668
MOD20_02253668: ; 0x02253668
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	mov r3, #2
	add r4, r0, #0
	str r3, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #0x14
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r1, #4
	ldr r0, [r4, r0]
	mov r1, #5
	mov r2, #0x40
	bl FUN_02018540
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_02017CD0
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_02017CD0
	mov r1, #0
	ldr r0, _022536C4 ; =0x04001050
	add r2, r1, #0
	mov r3, #0x1f
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	add r0, r5, #0
	bl MOD20_02252EBC
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_022536C4: .word 0x04001050
	thumb_func_end MOD20_02253668

	thumb_func_start MOD20_022536C8
MOD20_022536C8: ; 0x022536C8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #4
	bl FUN_020178A0
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #5
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD20_02252EBC
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022536C8

	thumb_func_start MOD20_022536F4
MOD20_022536F4: ; 0x022536F4
	ldr r2, _02253710 ; =0x12345678
	str r1, [r0]
	mov r3, #0
	str r2, [r0, #4]
	cmp r1, #0
	bls _0225370C
	sub r2, r3, #1
_02253702:
	add r3, r3, #1
	str r2, [r0, #8]
	add r0, r0, #4
	cmp r3, r1
	blo _02253702
_0225370C:
	bx lr
	nop
_02253710: .word 0x12345678
	thumb_func_end MOD20_022536F4

	thumb_func_start MOD20_02253714
MOD20_02253714: ; 0x02253714
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	ldr r0, _02253750 ; =0x12345678
	cmp r1, r0
	beq _02253726
	bl GF_AssertFail
_02253726:
	ldr r6, [r5]
	mov r2, #0
	cmp r6, #0
	bls _0225374A
	add r3, r5, #0
	sub r0, r2, #1
_02253732:
	ldr r1, [r3, #8]
	cmp r1, r0
	bne _02253742
	lsl r0, r2, #2
	add r0, r5, r0
	str r4, [r0, #8]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02253742:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, r6
	blo _02253732
_0225374A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02253750: .word 0x12345678
	thumb_func_end MOD20_02253714

	thumb_func_start MOD20_02253754
MOD20_02253754: ; 0x02253754
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	ldr r0, _02253790 ; =0x12345678
	cmp r1, r0
	beq _02253766
	bl GF_AssertFail
_02253766:
	ldr r3, [r5]
	mov r2, #0
	cmp r3, #0
	bls _0225378A
	add r1, r5, #0
_02253770:
	ldr r0, [r1, #8]
	cmp r4, r0
	bne _02253782
	mov r1, #0
	lsl r0, r2, #2
	mvn r1, r1
	add r0, r5, r0
	str r1, [r0, #8]
	pop {r3, r4, r5, pc}
_02253782:
	add r2, r2, #1
	add r1, r1, #4
	cmp r2, r3
	blo _02253770
_0225378A:
	bl GF_AssertFail
	pop {r3, r4, r5, pc}
	.align 2, 0
_02253790: .word 0x12345678
	thumb_func_end MOD20_02253754

	thumb_func_start MOD20_02253794
MOD20_02253794: ; 0x02253794
	push {r3, r4}
	ldr r4, [r0]
	mov r3, #0
	cmp r4, #0
	bls _022537B2
_0225379E:
	ldr r2, [r0, #8]
	cmp r1, r2
	bne _022537AA
	mov r0, #0
	pop {r3, r4}
	bx lr
_022537AA:
	add r3, r3, #1
	add r0, r0, #4
	cmp r3, r4
	blo _0225379E
_022537B2:
	mov r0, #1
	pop {r3, r4}
	bx lr
	thumb_func_end MOD20_02253794

	thumb_func_start MOD20_022537B8
MOD20_022537B8: ; 0x022537B8
	push {r3, r4}
	ldr r4, [r0]
	mov r3, #0
	cmp r4, #0
	bls _022537D8
	sub r1, r3, #1
_022537C4:
	ldr r2, [r0, #8]
	cmp r2, r1
	beq _022537D0
	mov r0, #0
	pop {r3, r4}
	bx lr
_022537D0:
	add r3, r3, #1
	add r0, r0, #4
	cmp r3, r4
	blo _022537C4
_022537D8:
	mov r0, #1
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022537B8

	thumb_func_start MOD20_022537E0
MOD20_022537E0: ; 0x022537E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	str r2, [sp]
	mov r0, #0
	add r5, r1, #0
	ldr r2, [r7]
	sub r1, r0, #1
	str r3, [sp, #4]
	cmp r2, r1
	beq _02253880
	add r3, r7, #0
	sub r1, r0, #1
_022537FA:
	ldr r2, [r3]
	cmp r5, r2
	bne _02253876
	add r6, r0, #0
	add r0, r7, #0
	str r0, [sp, #8]
	add r0, #8
	mov r1, #0xc
	str r0, [sp, #8]
	mul r6, r1
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x28]
	ldr r1, [r1, r6]
	add r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	beq _02253870
	ldr r0, [sp, #8]
	ldr r0, [r0, r6]
	cmp r0, #0
	beq _0225382C
	add r0, r4, #0
	add r0, #0x18
	b _0225382E
_0225382C:
	mov r0, #0
_0225382E:
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	bl MOD20_02253714
	cmp r0, #0
	beq _02253866
	ldr r0, [sp]
	ldr r2, [sp, #0x24]
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #4]
	str r5, [r4]
	ldr r0, [sp, #4]
	add r5, r7, #4
	str r0, [r4, #0x10]
	ldr r0, [r5, r6]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x14]
	cmp r0, #0
	beq _02253884
	ldr r2, [r5, r6]
	add r1, r4, #0
	blx r2
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02253866:
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_02253870:
	bl GF_AssertFail
	b _02253880
_02253876:
	add r3, #0xc
	ldr r2, [r3]
	add r0, r0, #1
	cmp r2, r1
	bne _022537FA
_02253880:
	bl GF_AssertFail
_02253884:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD20_022537E0

	thumb_func_start MOD20_02253888
MOD20_02253888: ; 0x02253888
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4]
	bl MOD20_02253754
	ldr r0, [r4, #0x14]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD20_02253888

	thumb_func_start MOD20_022538A0
MOD20_022538A0: ; 0x022538A0
	ldr r0, [r0, #8]
	bx lr
	thumb_func_end MOD20_022538A0

	thumb_func_start MOD20_022538A4
MOD20_022538A4: ; 0x022538A4
	ldr r0, [r0, #0x10]
	bx lr
	thumb_func_end MOD20_022538A4

	thumb_func_start MOD20_022538A8
MOD20_022538A8: ; 0x022538A8
	ldr r0, [r0, #0xc]
	bx lr
	thumb_func_end MOD20_022538A8

	thumb_func_start MOD20_022538AC
MOD20_022538AC: ; 0x022538AC
	ldr r0, [r0, #4]
	bx lr
	thumb_func_end MOD20_022538AC

	thumb_func_start MOD20_022538B0
MOD20_022538B0: ; 0x022538B0
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_022538B0

	thumb_func_start MOD20_022538B8
MOD20_022538B8: ; 0x022538B8
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_022538B8

	thumb_func_start MOD20_022538BC
MOD20_022538BC: ; 0x022538BC
	push {r3, r4, r5, r6}
	mul r2, r3
	ldr r4, [sp, #0x18]
	add r1, r1, r2
	lsl r6, r1, #1
	lsl r4, r4, #0xc
	ldr r1, [sp, #0x10]
	add r5, r4, #0
	orr r5, r1
	add r2, r0, r6
	strh r5, [r0, r6]
	add r0, r1, #1
	orr r0, r4
	strh r0, [r2, #2]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #1
	add r1, r1, r0
	add r0, r4, #0
	orr r0, r1
	strh r0, [r2, r3]
	add r0, r1, #1
	add r1, r4, #0
	orr r1, r0
	add r0, r2, r3
	strh r1, [r0, #2]
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022538BC

	thumb_func_start MOD20_022538F4
MOD20_022538F4: ; 0x022538F4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r7, r0, #0
	beq _02253960
	bl MOD20_02252DEC
	mov r4, #0
	cmp r6, #0
	bls _0225395A
_02253910:
	ldrh r3, [r5]
	mov r0, #0x1f
	lsl r0, r0, #0xa
	and r0, r3
	asr r0, r0, #0xa
	add r2, r0, #0
	mov r1, #0x72
	mov r0, #0x1f
	mul r2, r1
	and r0, r3
	add r1, #0xb9
	mul r1, r0
	mov r0, #0x3e
	lsl r0, r0, #4
	and r0, r3
	asr r3, r0, #5
	ldr r0, _02253964 ; =0x0000024B
	mul r0, r3
	add r0, r1, r0
	mov r1, #0xfa
	add r0, r2, r0
	lsl r1, r1, #2
	bl _u32_div_f
	lsr r1, r0, #3
	cmp r1, #3
	bls _02253948
	mov r1, #3
_02253948:
	ldr r0, _02253968 ; =MOD20_0225470C
	add r4, r4, #1
	ldrb r0, [r0, r1]
	lsl r0, r0, #1
	ldrh r0, [r7, r0]
	strh r0, [r5]
	add r5, r5, #2
	cmp r4, r6
	blo _02253910
_0225395A:
	add r0, r7, #0
	bl FreeToHeap
_02253960:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02253964: .word 0x0000024B
_02253968: .word MOD20_0225470C
	thumb_func_end MOD20_022538F4

	thumb_func_start MOD20_0225396C
MOD20_0225396C: ; 0x0225396C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0
	beq _022539C2
	mov r0, #8
	mov r1, #0x20
	bl AllocFromHeap
	add r5, r0, #0
	add r0, r4, #0
	bl MOD20_02252DEC
	cmp r5, #0
	beq _022539BC
	mov r0, #0
	add r1, r5, #0
	lsl r3, r6, #1
_02253998:
	ldrh r2, [r4, r3]
	add r0, r0, #1
	strh r2, [r1]
	add r1, r1, #2
	cmp r0, #0x10
	blt _02253998
	add r0, r5, #0
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r5, #0
	lsl r1, r7, #5
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	add r0, r5, #0
	bl FreeToHeap
_022539BC:
	add r0, r4, #0
	bl FreeToHeap
_022539C2:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_0225396C

	thumb_func_start MOD20_022539C4
MOD20_022539C4: ; 0x022539C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0x13
	add r2, sp, #0
	mov r3, #8
	bl FUN_02006C08
	add r4, r0, #0
	beq _02253A02
	ldr r0, [sp]
	mov r1, #0x40
	ldr r0, [r0, #0xc]
	bl MOD20_022538F4
	ldr r0, [sp]
	mov r1, #0x80
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [sp]
	lsl r1, r5, #5
	ldr r0, [r0, #0xc]
	mov r2, #0x80
	bl GXS_LoadOBJPltt
	add r0, r4, #0
	bl FreeToHeap
_02253A02:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022539C4

	thumb_func_start MOD20_02253A04
MOD20_02253A04: ; 0x02253A04
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #4]
	lsl r0, r3, #1
	str r0, [sp, #0xc]
	add r6, r1, #0
	str r2, [sp, #8]
	ldr r2, _02253A9C ; =MOD20_02254708
	ldr r1, [sp, #0xc]
	mov r0, #8
	ldrh r1, [r2, r1]
	bl AllocFromHeap
	add r7, r0, #0
	beq _02253A98
	mov r0, #0x13
	mov r1, #8
	bl NARC_ctor
	str r0, [sp, #0x1c]
	cmp r0, #0
	beq _02253A92
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, [sp, #8]
	cmp r0, #0
	bls _02253A8C
	ldr r1, _02253AA0 ; =MOD20_02254704
	ldr r0, [sp, #0xc]
	ldr r4, [sp, #0x18]
	ldrh r5, [r1, r0]
	ldr r1, _02253A9C ; =MOD20_02254708
	ldrh r0, [r1, r0]
	str r0, [sp, #0x14]
	ldr r0, [sp, #4]
	lsl r0, r0, #5
	str r0, [sp, #0x10]
_02253A4E:
	str r7, [sp]
	ldr r0, [sp, #0x1c]
	ldr r1, [r6]
	ldr r3, [sp, #0x14]
	mov r2, #0
	bl NARC_ReadFromMember
	add r0, r7, #0
	add r1, sp, #0x20
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	ldr r0, [r0, #0x14]
	bl DC_FlushRange
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	ldr r0, [r0, #0x14]
	add r1, r1, r4
	add r2, r5, #0
	bl GXS_LoadOBJ
	ldr r0, [sp, #0x18]
	add r6, r6, #4
	add r1, r0, #1
	ldr r0, [sp, #8]
	add r4, r4, r5
	str r1, [sp, #0x18]
	cmp r1, r0
	blo _02253A4E
_02253A8C:
	ldr r0, [sp, #0x1c]
	bl NARC_dtor
_02253A92:
	add r0, r7, #0
	bl FreeToHeap
_02253A98:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02253A9C: .word MOD20_02254708
_02253AA0: .word MOD20_02254704
	thumb_func_end MOD20_02253A04

	thumb_func_start MOD20_02253AA4
MOD20_02253AA4: ; 0x02253AA4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r4, r2, #0
	mov r1, #2
	add r2, sp, #0xc
	strh r1, [r2]
	mov r3, #3
	strh r3, [r2, #2]
	mov r3, #0xa
	strh r3, [r2, #4]
	mov r3, #0xb
	strh r3, [r2, #6]
	str r3, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	lsl r1, r4, #0x18
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #9
	add r6, r0, #0
	bl FUN_02018148
	mov r1, #4
	add r0, sp, #0xc
	strh r1, [r0]
	mov r1, #5
	strh r1, [r0, #2]
	mov r1, #0xc
	strh r1, [r0, #4]
	mov r1, #0xd
	strh r1, [r0, #6]
	mov r3, #0xb
	lsl r1, r4, #0x18
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	bl FUN_02018148
	mov r1, #6
	add r0, sp, #0xc
	strh r1, [r0]
	mov r1, #7
	strh r1, [r0, #2]
	mov r1, #0xe
	strh r1, [r0, #4]
	mov r1, #0xf
	strh r1, [r0, #6]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	lsl r1, r4, #0x18
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #0xd
	bl FUN_02018148
	add r0, r5, #0
	mov r1, #0xa
	bl _u32_div_f
	mov r1, #0xa
	mul r1, r0
	add r0, r0, #4
	sub r5, r5, r1
	lsr r1, r0, #2
	lsl r0, r0, #0x1e
	lsl r1, r1, #4
	lsr r0, r0, #0x1d
	add r2, r1, r0
	add r0, sp, #0xc
	strh r2, [r0]
	add r1, r2, #1
	strh r1, [r0, #2]
	add r1, r2, #0
	add r1, #8
	strh r1, [r0, #4]
	add r2, #9
	strh r2, [r0, #6]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	lsl r1, r4, #0x18
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #0xf
	bl FUN_02018148
	add r0, r5, #4
	lsr r1, r0, #2
	lsl r0, r0, #0x1e
	lsl r1, r1, #4
	lsr r0, r0, #0x1d
	add r2, r1, r0
	add r0, sp, #0xc
	strh r2, [r0]
	add r1, r2, #1
	strh r1, [r0, #2]
	add r1, r2, #0
	add r1, #8
	strh r1, [r0, #4]
	add r2, #9
	strh r2, [r0, #6]
	mov r0, #0xb
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	lsl r1, r4, #0x18
	str r0, [sp, #8]
	add r0, r6, #0
	lsr r1, r1, #0x18
	add r2, sp, #0xc
	mov r3, #0x11
	bl FUN_02018148
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD20_02253AA4

	thumb_func_start MOD20_02253BA4
MOD20_02253BA4: ; 0x02253BA4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0x1c
	mov r6, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02253C0E
	add r0, r6, #0
	str r0, [r4, #0x14]
	str r0, [r4, #0xc]
	str r0, [r4, #4]
	str r7, [r4]
	str r5, [r4, #0x18]
	add r0, r7, #0
	bl NNS_G2dGetOamManagerOamCapacity
	strh r0, [r4, #0x10]
	ldrh r1, [r4, #0x10]
	add r0, r5, #0
	lsl r1, r1, #3
	bl AllocFromHeap
	str r0, [r4, #0x14]
	cmp r0, #0
	beq _02253C0E
	ldrh r2, [r4, #0x10]
	mov r1, #0x90
	add r0, r5, #0
	mul r1, r2
	bl AllocFromHeap
	str r0, [r4, #0xc]
	cmp r0, #0
	beq _02253C0E
	ldrh r1, [r4, #0x10]
	add r0, r5, #0
	lsl r1, r1, #2
	bl AllocFromHeap
	str r0, [r4, #4]
	cmp r0, #0
	beq _02253C0E
	ldrh r2, [r4, #0x10]
	ldr r1, [r4, #0xc]
	bl MOD20_0225403C
	add r0, r6, #0
	strh r0, [r4, #0x12]
	str r0, [r4, #8]
	mov r6, #1
_02253C0E:
	cmp r6, #0
	bne _02253C46
	cmp r4, #0
	beq _02253C42
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _02253C22
	add r0, r5, #0
	bl FreeToHeapExplicit
_02253C22:
	ldr r1, [r4, #0xc]
	cmp r1, #0
	beq _02253C2E
	add r0, r5, #0
	bl FreeToHeapExplicit
_02253C2E:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _02253C3A
	add r0, r5, #0
	bl FreeToHeapExplicit
_02253C3A:
	add r0, r5, #0
	add r1, r4, #0
	bl FreeToHeapExplicit
_02253C42:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02253C46:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD20_02253BA4

	thumb_func_start MOD20_02253C4C
MOD20_02253C4C: ; 0x02253C4C
	push {r4, lr}
	add r4, r0, #0
	beq _02253C76
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02253C5C
	bl FreeToHeap
_02253C5C:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02253C66
	bl FreeToHeap
_02253C66:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02253C70
	bl FreeToHeap
_02253C70:
	add r0, r4, #0
	bl FreeToHeap
_02253C76:
	pop {r4, pc}
	thumb_func_end MOD20_02253C4C

	thumb_func_start MOD20_02253C78
MOD20_02253C78: ; 0x02253C78
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0xc]
	ldrh r0, [r0, #0x12]
	cmp r0, #0
	bne _02253C86
	b _02253E52
_02253C86:
	ldr r0, [sp, #0xc]
	ldr r4, [r0, #8]
	ldr r5, [r0, #0x14]
	ldrh r0, [r0, #0x10]
	cmp r4, #0
	str r0, [sp, #0x10]
	bne _02253C96
	b _02253E38
_02253C96:
	add r0, r4, #0
	mov r1, #2
	add r0, #8
	lsl r1, r1, #0xc
	bl NNS_G2dTickCellAnimation
	add r0, r4, #0
	add r0, #0x86
	ldrb r0, [r0]
	cmp r0, #0
	beq _02253CAE
	b _02253E30
_02253CAE:
	add r6, r4, #0
	add r6, #0x40
	mov r0, #0xc
	ldrsh r0, [r6, r0]
	ldr r1, [r4, #0x64]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x18]
	mov r0, #0xe
	ldrsh r0, [r6, r0]
	ldr r1, [r4, #0x68]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x1c]
	add r0, r4, #0
	add r0, #0x87
	ldrb r0, [r0]
	cmp r0, #0
	bne _02253CEE
	add r0, sp, #0x18
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	ldr r1, [sp, #0x10]
	str r3, [sp, #8]
	lsl r1, r1, #0x10
	ldr r2, [r4, #0x34]
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl NNS_G2dMakeCellToOams
	b _02253D86
_02253CEE:
	ldr r0, [r4, #0x6c]
	bl MTX_Identity22_
	ldrh r1, [r6, #0x12]
	mov r0, #4
	tst r0, r1
	beq _02253D20
	add r0, r4, #0
	add r0, #0x8c
	ldrh r2, [r6, #0x10]
	ldrh r0, [r0]
	ldr r1, _02253E58 ; =FX_SinCosTable_
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r3, r0, #2
	add r2, r1, r3
	ldrsh r1, [r1, r3]
	mov r3, #2
	ldrsh r2, [r2, r3]
	ldr r0, [r4, #0x6c]
	bl MTX_Rot22_
	b _02253D3E
_02253D20:
	add r0, r4, #0
	add r0, #0x8c
	ldrh r0, [r0]
	cmp r0, #0
	beq _02253D3E
	asr r0, r0, #4
	lsl r3, r0, #2
	ldr r1, _02253E58 ; =FX_SinCosTable_
	ldr r0, [r4, #0x6c]
	add r2, r1, r3
	ldrsh r1, [r1, r3]
	mov r3, #2
	ldrsh r2, [r2, r3]
	bl MTX_Rot22_
_02253D3E:
	ldrh r1, [r6, #0x12]
	mov r0, #2
	tst r0, r1
	beq _02253D62
	ldr r0, [r6, #4]
	ldr r7, [r4, #0x6c]
	bl FX_Inv
	str r0, [sp, #0x14]
	ldr r0, [r6, #8]
	bl FX_Inv
	add r3, r0, #0
	ldr r2, [sp, #0x14]
	add r0, r7, #0
	add r1, r7, #0
	bl MTX_ScaleApply22
_02253D62:
	ldr r0, [sp, #0xc]
	ldr r1, [r4, #0x6c]
	ldr r0, [r0]
	bl NNS_G2dEntryOamManagerAffine
	add r1, sp, #0x18
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x34]
	lsl r1, r1, #0x10
	ldr r3, [r4, #0x6c]
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl NNS_G2dMakeCellToOams
_02253D86:
	ldr r1, [sp, #0x10]
	sub r1, r1, r0
	str r1, [sp, #0x10]
	add r1, r0, #0
	sub r0, r0, #1
	cmp r1, #0
	beq _02253E30
	ldr r7, _02253E5C ; =0xDFFFFFFF
	asr r1, r7, #0x11
_02253D98:
	ldr r3, [r5, #4]
	ldr r2, _02253E60 ; =0xFFFFF3FF
	add r6, r4, #0
	and r2, r3
	add r3, r4, #0
	add r3, #0x82
	ldrh r3, [r3]
	add r6, #0x84
	lsl r3, r3, #0x1e
	lsr r3, r3, #0x14
	orr r2, r3
	str r2, [r5, #4]
	ldr r3, _02253E64 ; =0xFFFF0FFF
	ldrh r6, [r6]
	and r3, r2
	lsl r2, r2, #0x10
	lsr r2, r2, #0x1c
	add r2, r2, r6
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x10
	orr r2, r3
	add r6, r4, #0
	ldr r3, _02253E68 ; =0xFFFFFC00
	str r2, [r5, #4]
	add r6, #0x88
	and r3, r2
	lsl r2, r2, #0x16
	ldrh r6, [r6]
	lsr r2, r2, #0x16
	add r6, r2, r6
	ldr r2, _02253E6C ; =0x000003FF
	and r2, r6
	orr r2, r3
	add r6, r4, #0
	str r2, [r5, #4]
	add r6, #0x8a
	ldr r2, [r5]
	ldr r3, _02253E70 ; =0xEFFFFFFF
	ldrb r6, [r6]
	and r3, r2
	lsl r2, r2, #3
	lsr r2, r2, #0x1f
	eor r2, r6
	lsl r2, r2, #0x1f
	lsr r2, r2, #3
	orr r2, r3
	add r6, r4, #0
	add r3, r2, #0
	str r2, [r5]
	add r6, #0x8b
	lsl r2, r2, #2
	ldrb r6, [r6]
	lsr r2, r2, #0x1f
	and r3, r7
	eor r2, r6
	lsl r2, r2, #0x1f
	lsr r2, r2, #2
	orr r2, r3
	add r6, r4, #0
	add r3, r2, #0
	str r2, [r5]
	add r6, #0x8e
	lsl r2, r2, #0x13
	ldrb r6, [r6]
	lsr r2, r2, #0x1f
	and r3, r1
	eor r2, r6
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x13
	orr r2, r3
	str r2, [r5]
	add r2, r0, #0
	add r5, #8
	sub r0, r0, #1
	cmp r2, #0
	bne _02253D98
_02253E30:
	ldr r4, [r4, #0x5c]
	cmp r4, #0
	beq _02253E38
	b _02253C96
_02253E38:
	ldr r0, [sp, #0xc]
	ldr r1, [r0, #0x14]
	cmp r5, r1
	bls _02253E52
	sub r3, r5, r1
	asr r2, r3, #2
	lsr r2, r2, #0x1d
	add r2, r3, r2
	lsl r2, r2, #0xd
	ldr r0, [r0]
	lsr r2, r2, #0x10
	bl NNS_G2dEntryOamManagerOam
_02253E52:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02253E58: .word FX_SinCosTable_
_02253E5C: .word 0xDFFFFFFF
_02253E60: .word 0xFFFFF3FF
_02253E64: .word 0xFFFF0FFF
_02253E68: .word 0xFFFFFC00
_02253E6C: .word 0x000003FF
_02253E70: .word 0xEFFFFFFF
	thumb_func_end MOD20_02253C78

	thumb_func_start MOD20_02253E74
MOD20_02253E74: ; 0x02253E74
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl MOD20_02254068
	add r4, r0, #0
	beq _02253F10
	ldrb r1, [r5, #0xb]
	add r0, #0x82
	strh r1, [r0]
	add r0, r4, #0
	ldrb r1, [r5, #0xc]
	add r0, #0x80
	strh r1, [r0]
	add r0, r7, #0
	add r1, r4, #0
	bl MOD20_022540A4
	ldr r0, [r6, #8]
	str r0, [r4]
	ldr r0, [r6, #0xc]
	str r0, [r4, #4]
	ldrh r1, [r5, #8]
	bl NNS_G2dGetAnimSequenceByIdx
	add r1, r0, #0
	add r0, r4, #0
	ldr r2, [r4]
	add r0, #8
	bl NNS_G2dInitCellAnimation
	ldr r1, [r5]
	ldr r0, [r5, #4]
	str r1, [r4, #0x64]
	add r1, r4, #0
	str r0, [r4, #0x68]
	mov r0, #0
	add r1, #0x84
	strh r0, [r1]
	add r1, r4, #0
	add r1, #0x88
	strh r0, [r1]
	ldrb r2, [r5, #0xa]
	mov r1, #1
	tst r2, r1
	beq _02253ED4
	add r0, r1, #0
_02253ED4:
	add r1, r4, #0
	add r1, #0x8a
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	mov r0, #2
	tst r0, r1
	beq _02253EE6
	mov r1, #1
	b _02253EE8
_02253EE6:
	mov r1, #0
_02253EE8:
	add r0, r4, #0
	add r0, #0x8b
	strb r1, [r0]
	add r1, r4, #0
	mov r0, #0
	add r1, #0x8e
	strb r0, [r1]
	add r1, r4, #0
	add r1, #0x8c
	strh r0, [r1]
	add r1, r4, #0
	add r1, #0x70
	str r1, [r4, #0x6c]
	add r1, r4, #0
	ldrb r2, [r5, #0xd]
	add r1, #0x87
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x86
	strb r0, [r1]
_02253F10:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_02253E74

	thumb_func_start MOD20_02253F14
MOD20_02253F14: ; 0x02253F14
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_022540FC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD20_02254080
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_02253F14

	thumb_func_start MOD20_02253F28
MOD20_02253F28: ; 0x02253F28
	push {r4, lr}
	add r4, r0, #0
	lsl r1, r1, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl NNS_G2dGetAnimSequenceByIdx
	add r1, r0, #0
	add r0, r4, #0
	ldr r2, [r4]
	add r0, #8
	bl NNS_G2dInitCellAnimation
	pop {r4, pc}
	thumb_func_end MOD20_02253F28

	thumb_func_start MOD20_02253F44
MOD20_02253F44: ; 0x02253F44
	ldr r0, [r0, #0x10]
	cmp r0, #0
	bne _02253F4E
	mov r0, #1
	bx lr
_02253F4E:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253F44

	thumb_func_start MOD20_02253F54
MOD20_02253F54: ; 0x02253F54
	ldr r3, [r0, #0x64]
	add r1, r3, r1
	str r1, [r0, #0x64]
	ldr r1, [r0, #0x68]
	add r1, r1, r2
	str r1, [r0, #0x68]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253F54

	thumb_func_start MOD20_02253F64
MOD20_02253F64: ; 0x02253F64
	str r1, [r0, #0x64]
	str r2, [r0, #0x68]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253F64

	thumb_func_start MOD20_02253F6C
MOD20_02253F6C: ; 0x02253F6C
	ldr r3, [r0, #0x64]
	str r3, [r1]
	ldr r0, [r0, #0x68]
	str r0, [r2]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253F6C

	thumb_func_start MOD20_02253F78
MOD20_02253F78: ; 0x02253F78
	add r0, #0x86
	strb r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253F78

	thumb_func_start MOD20_02253F80
MOD20_02253F80: ; 0x02253F80
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r4, r2, #0
	bl MOD20_022540FC
	add r0, r5, #0
	add r0, #0x80
	strh r4, [r0]
	add r0, r6, #0
	add r1, r5, #0
	bl MOD20_022540A4
	pop {r4, r5, r6, pc}
	thumb_func_end MOD20_02253F80

	thumb_func_start MOD20_02253F9C
MOD20_02253F9C: ; 0x02253F9C
	add r0, #0x84
	strh r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253F9C

	thumb_func_start MOD20_02253FA4
MOD20_02253FA4: ; 0x02253FA4
	add r0, #0x88
	strh r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253FA4

	thumb_func_start MOD20_02253FAC
MOD20_02253FAC: ; 0x02253FAC
	add r0, #0x8e
	strb r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253FAC

	thumb_func_start MOD20_02253FB4
MOD20_02253FB4: ; 0x02253FB4
	add r0, #0x8c
	strh r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02253FB4

	thumb_func_start MOD20_02253FBC
MOD20_02253FBC: ; 0x02253FBC
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r0, #0
	add r6, r1, #0
	add r1, r2, #0
	add r7, r3, #0
	str r4, [r5, #0x10]
	add r0, r6, #0
	add r2, r4, #0
	bl FUN_02006C88
	str r0, [r5]
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	bl FUN_02006C88
	str r0, [r5, #4]
	ldr r0, [r5]
	cmp r0, #0
	beq _0225400E
	ldr r1, [r5, #4]
	cmp r1, #0
	beq _0225400E
	add r1, r5, #0
	add r1, #8
	bl NNS_G2dGetUnpackedCellBank
	cmp r0, #0
	bne _02253FFC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02253FFC:
	ldr r0, [r5, #4]
	add r5, #0xc
	add r1, r5, #0
	bl NNS_G2dGetUnpackedMCAnimBank
	cmp r0, #0
	bne _0225400E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0225400E:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD20_02253FBC

	thumb_func_start MOD20_02254014
MOD20_02254014: ; 0x02254014
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _02254028
	ldr r0, [r4, #0x10]
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4]
_02254028:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _02254038
	ldr r0, [r4, #0x10]
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4, #4]
_02254038:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD20_02254014

	thumb_func_start MOD20_0225403C
MOD20_0225403C: ; 0x0225403C
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r1, #0
	sub r6, r6, #1
	cmp r0, #0
	beq _0225405E
_0225404C:
	add r0, r4, #0
	stmia r5!, {r4}
	bl MOD20_02254060
	add r0, r6, #0
	add r4, #0x90
	sub r6, r6, #1
	cmp r0, #0
	bne _0225404C
_0225405E:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD20_0225403C

	thumb_func_start MOD20_02254060
MOD20_02254060: ; 0x02254060
	mov r1, #0
	str r1, [r0, #0x5c]
	str r1, [r0, #0x60]
	bx lr
	thumb_func_end MOD20_02254060

	thumb_func_start MOD20_02254068
MOD20_02254068: ; 0x02254068
	ldrh r2, [r0, #0x12]
	ldrh r1, [r0, #0x10]
	cmp r2, r1
	bhs _0225407C
	add r1, r2, #1
	strh r1, [r0, #0x12]
	ldr r1, [r0, #4]
	lsl r0, r2, #2
	ldr r0, [r1, r0]
	bx lr
_0225407C:
	mov r0, #0
	bx lr
	thumb_func_end MOD20_02254068

	thumb_func_start MOD20_02254080
MOD20_02254080: ; 0x02254080
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrh r0, [r5, #0x12]
	add r4, r1, #0
	cmp r0, #0
	beq _022540A0
	add r0, r4, #0
	bl MOD20_02254060
	ldrh r0, [r5, #0x12]
	sub r0, r0, #1
	strh r0, [r5, #0x12]
	ldrh r0, [r5, #0x12]
	ldr r1, [r5, #4]
	lsl r0, r0, #2
	str r4, [r1, r0]
_022540A0:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_02254080

	thumb_func_start MOD20_022540A4
MOD20_022540A4: ; 0x022540A4
	push {r4, r5}
	ldr r3, [r0, #8]
	cmp r3, #0
	bne _022540B8
	str r1, [r0, #8]
	mov r0, #0
	str r0, [r1, #0x5c]
	str r0, [r1, #0x60]
	pop {r4, r5}
	bx lr
_022540B8:
	add r4, r1, #0
	add r4, #0x80
	ldr r5, [r4]
	add r2, r3, #0
_022540C0:
	add r4, r2, #0
	add r4, #0x80
	ldr r4, [r4]
	cmp r5, r4
	bhs _022540E2
	cmp r2, r3
	bne _022540D0
	str r1, [r0, #8]
_022540D0:
	ldr r0, [r2, #0x60]
	str r0, [r1, #0x60]
	cmp r0, #0
	beq _022540DA
	str r1, [r0, #0x5c]
_022540DA:
	str r2, [r1, #0x5c]
	str r1, [r2, #0x60]
	pop {r4, r5}
	bx lr
_022540E2:
	ldr r4, [r2, #0x5c]
	cmp r4, #0
	bne _022540F4
	str r1, [r2, #0x5c]
	str r2, [r1, #0x60]
	mov r0, #0
	str r0, [r1, #0x5c]
	pop {r4, r5}
	bx lr
_022540F4:
	add r2, r4, #0
	b _022540C0
	thumb_func_end MOD20_022540A4

	thumb_func_start MOD20_022540F8
MOD20_022540F8: ; 0x022540F8
	pop {r4, r5}
	bx lr
	thumb_func_end MOD20_022540F8

	thumb_func_start MOD20_022540FC
MOD20_022540FC: ; 0x022540FC
	ldr r2, [r1, #0x60]
	cmp r2, #0
	beq _02254118
	ldr r0, [r1, #0x5c]
	cmp r0, #0
	beq _02254112
	str r0, [r2, #0x5c]
	ldr r2, [r1, #0x60]
	ldr r0, [r1, #0x5c]
	str r2, [r0, #0x60]
	bx lr
_02254112:
	mov r0, #0
	str r0, [r2, #0x5c]
	bx lr
_02254118:
	ldr r3, [r1, #0x5c]
	cmp r3, #0
	beq _02254128
	mov r2, #0
	str r2, [r3, #0x60]
	ldr r1, [r1, #0x5c]
	str r1, [r0, #8]
	bx lr
_02254128:
	mov r1, #0
	str r1, [r0, #8]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022540FC

	thumb_func_start MOD20_02254130
MOD20_02254130: ; 0x02254130
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	add r7, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	ldr r5, [sp, #0x20]
	bne _02254144
	bl GF_AssertFail
_02254144:
	add r0, r5, #0
	mov r1, #0x18
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254192
	ldr r0, [sp]
	str r5, [r4, #8]
	str r0, [r4, #4]
	str r6, [r4]
	mov r1, #0xe
	ldr r0, [sp, #4]
	str r7, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r5, #0
	mul r1, r7
	bl AllocFromHeap
	str r0, [r4, #0x14]
	cmp r0, #0
	beq _02254188
	mov r6, #0
	cmp r7, #0
	bls _02254192
	add r5, r6, #0
_02254176:
	ldr r0, [r4, #0x14]
	add r0, r0, r5
	bl MOD20_022542E4
	add r6, r6, #1
	add r5, #0xe
	cmp r6, r7
	blo _02254176
	b _02254192
_02254188:
	add r0, r5, #0
	add r1, r4, #0
	bl FreeToHeapExplicit
	mov r4, #0
_02254192:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD20_02254130

	thumb_func_start MOD20_02254198
MOD20_02254198: ; 0x02254198
	push {r4, lr}
	add r4, r0, #0
	bne _022541A2
	bl GF_AssertFail
_022541A2:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x14]
	bl FreeToHeapExplicit
	ldr r0, [r4, #8]
	add r1, r4, #0
	bl FreeToHeapExplicit
	pop {r4, pc}
	thumb_func_end MOD20_02254198

	thumb_func_start MOD20_022541B4
MOD20_022541B4: ; 0x022541B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	bl FUN_02020A98
	str r0, [sp, #4]
	cmp r0, #0
	beq _0225420C
	bl FUN_02020AA4
	ldr r1, [r5, #0xc]
	mov r7, #0
	str r0, [sp]
	cmp r1, #0
	bls _02254232
	add r4, r7, #0
	add r6, r7, #0
_022541D6:
	ldr r0, [r5, #0x14]
	add r1, r0, r4
	ldrb r0, [r1, #1]
	strb r0, [r1, #2]
	ldr r0, [r5, #0x14]
	add r0, r0, r4
	ldrb r0, [r0, #1]
	cmp r0, #0
	ldr r0, [r5]
	beq _022541F2
	add r0, r0, r6
	bl FUN_02020A40
	b _022541F8
_022541F2:
	add r0, r0, r6
	bl FUN_02020A6C
_022541F8:
	ldr r1, [r5, #0x14]
	add r7, r7, #1
	add r1, r1, r4
	strb r0, [r1, #1]
	ldr r1, [r5, #0xc]
	add r4, #0xe
	add r6, r6, #4
	cmp r7, r1
	blo _022541D6
	b _02254232
_0225420C:
	ldr r1, [r5, #0xc]
	mov r2, #0
	str r2, [sp]
	cmp r1, #0
	bls _02254232
	add r0, r2, #0
	add r3, r2, #0
_0225421A:
	ldr r1, [r5, #0x14]
	add r2, r2, #1
	add r4, r1, r0
	ldrb r1, [r4, #1]
	strb r1, [r4, #2]
	ldr r1, [r5, #0x14]
	add r1, r1, r0
	strb r3, [r1, #1]
	ldr r1, [r5, #0xc]
	add r0, #0xe
	cmp r2, r1
	blo _0225421A
_02254232:
	mov r6, #0
	cmp r1, #0
	bls _02254278
	ldr r7, _022542A8 ; =MOD20_02254710
	add r4, r6, #0
_0225423C:
	ldr r3, [r5, #0x14]
	ldr r1, [sp, #4]
	add r0, r3, r4
	ldrb r3, [r3, r4]
	ldr r2, [sp]
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	blx r3
	add r1, r0, #0
	ldr r0, [r5, #0x14]
	add r0, r0, r4
	ldrb r2, [r0, #1]
	ldrb r0, [r0, #2]
	cmp r2, r0
	bne _0225425C
	mov r2, #2
_0225425C:
	cmp r1, #0
	bne _02254264
	cmp r2, #2
	beq _0225426E
_02254264:
	ldr r3, [r5, #0x10]
	ldr r4, [r5, #4]
	add r0, r6, #0
	blx r4
	b _02254278
_0225426E:
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	add r4, #0xe
	cmp r6, r0
	blo _0225423C
_02254278:
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	cmp r6, r0
	bhs _022542A2
	mov r0, #0xe
	add r4, r6, #0
	ldr r7, _022542A8 ; =MOD20_02254710
	mul r4, r0
_02254288:
	ldr r3, [r5, #0x14]
	ldr r1, [sp, #4]
	add r0, r3, r4
	ldrb r3, [r3, r4]
	ldr r2, [sp]
	lsl r3, r3, #2
	ldr r3, [r7, r3]
	blx r3
	ldr r0, [r5, #0xc]
	add r6, r6, #1
	add r4, #0xe
	cmp r6, r0
	blo _02254288
_022542A2:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022542A8: .word MOD20_02254710
	thumb_func_end MOD20_022541B4

	thumb_func_start MOD20_022542AC
MOD20_022542AC: ; 0x022542AC
	push {r3, r4}
	ldr r4, [r0, #0x14]
	mov r0, #0xe
	mul r0, r1
	add r1, r4, r0
	lsl r0, r2, #1
	add r0, r1, r0
	strh r3, [r0, #8]
	pop {r3, r4}
	bx lr
	thumb_func_end MOD20_022542AC

	thumb_func_start MOD20_022542C0
MOD20_022542C0: ; 0x022542C0
	ldr r3, [r0, #0x14]
	mov r0, #0xe
	mul r0, r1
	add r0, r3, r0
	strh r2, [r0, #0xc]
	bx lr
	thumb_func_end MOD20_022542C0

	thumb_func_start MOD20_022542CC
MOD20_022542CC: ; 0x022542CC
	add r3, r1, #0
	mov r2, #0xe
	mul r3, r2
	ldr r1, [r0, #0x14]
	mov r2, #0
	add r1, r1, r3
	strh r2, [r1, #4]
	ldr r0, [r0, #0x14]
	mov r1, #4
	strb r1, [r0, r3]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022542CC

	thumb_func_start MOD20_022542E4
MOD20_022542E4: ; 0x022542E4
	mov r2, #0
	strb r2, [r0]
	strb r2, [r0, #1]
	strb r2, [r0, #2]
	strh r2, [r0, #4]
	strh r2, [r0, #6]
	add r3, r0, #0
	add r1, r2, #0
_022542F4:
	add r2, r2, #1
	strh r1, [r3, #8]
	add r3, r3, #2
	cmp r2, #2
	blo _022542F4
	strh r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD20_022542E4

	thumb_func_start MOD20_02254304
MOD20_02254304: ; 0x02254304
	strb r1, [r0]
	mov r1, #0
	strh r1, [r0, #4]
	bx lr
	thumb_func_end MOD20_02254304

	thumb_func_start MOD20_0225430C
MOD20_0225430C: ; 0x0225430C
	strb r1, [r0]
	bx lr
	thumb_func_end MOD20_0225430C

	thumb_func_start MOD20_02254310
MOD20_02254310: ; 0x02254310
	ldrh r2, [r0, #4]
	ldr r1, _02254320 ; =0x0000FFFF
	cmp r2, r1
	bhs _0225431C
	add r1, r2, #1
	strh r1, [r0, #4]
_0225431C:
	bx lr
	nop
_02254320: .word 0x0000FFFF
	thumb_func_end MOD20_02254310

	thumb_func_start MOD20_02254324
MOD20_02254324: ; 0x02254324
	ldrh r3, [r0, #4]
	mov r2, #0
_02254328:
	ldrh r1, [r0, #8]
	cmp r3, r1
	bne _02254332
	add r0, r2, #5
	bx lr
_02254332:
	add r2, r2, #1
	add r0, r0, #2
	cmp r2, #2
	blo _02254328
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD20_02254324

	thumb_func_start MOD20_02254340
MOD20_02254340: ; 0x02254340
	push {r3, lr}
	ldrb r1, [r0, #1]
	cmp r1, #0
	beq _02254356
	cmp r2, #0
	beq _02254356
	mov r1, #1
	bl MOD20_02254304
	mov r0, #1
	pop {r3, pc}
_02254356:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_02254340

	thumb_func_start MOD20_0225435C
MOD20_0225435C: ; 0x0225435C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD20_02254310
	ldrb r0, [r5, #1]
	cmp r0, #0
	beq _0225438A
	add r0, r5, #0
	bl MOD20_02254324
	cmp r0, #0
	bne _022543B8
	ldrh r1, [r5, #0xc]
	cmp r1, #0
	beq _022543B6
	ldrh r0, [r5, #4]
	cmp r0, r1
	blo _022543B6
	mov r0, #0
	strh r0, [r5, #4]
	mov r0, #7
	pop {r3, r4, r5, pc}
_0225438A:
	cmp r4, #0
	beq _0225439A
	add r0, r5, #0
	mov r1, #0
	bl MOD20_02254304
	mov r0, #2
	pop {r3, r4, r5, pc}
_0225439A:
	ldrh r0, [r5, #6]
	cmp r0, #0
	beq _022543AA
	add r0, r5, #0
	mov r1, #2
	bl MOD20_0225430C
	b _022543B6
_022543AA:
	add r0, r5, #0
	mov r1, #0
	bl MOD20_02254304
	mov r0, #3
	pop {r3, r4, r5, pc}
_022543B6:
	mov r0, #0
_022543B8:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD20_0225435C

	thumb_func_start MOD20_022543BC
MOD20_022543BC: ; 0x022543BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl MOD20_02254310
	ldrh r1, [r5, #4]
	ldrh r0, [r5, #6]
	cmp r1, r0
	bls _022543DA
	add r0, r5, #0
	mov r1, #0
	bl MOD20_02254304
	mov r0, #3
	pop {r3, r4, r5, pc}
_022543DA:
	ldrb r0, [r5, #1]
	cmp r0, #0
	beq _022543F0
	cmp r4, #0
	beq _022543F0
	add r0, r5, #0
	mov r1, #3
	bl MOD20_02254304
	mov r0, #4
	pop {r3, r4, r5, pc}
_022543F0:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD20_022543BC

	thumb_func_start MOD20_022543F4
MOD20_022543F4: ; 0x022543F4
	push {r3, lr}
	ldrb r1, [r0, #1]
	cmp r1, #0
	beq _02254402
	bl MOD20_02254310
	b _02254408
_02254402:
	mov r1, #0
	bl MOD20_02254304
_02254408:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD20_022543F4

	thumb_func_start MOD20_0225440C
MOD20_0225440C: ; 0x0225440C
	push {r3, lr}
	ldrb r1, [r0, #1]
	cmp r1, #0
	bne _0225441A
	mov r1, #0
	bl MOD20_02254304
_0225441A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD20_0225440C

	thumb_func_start MOD20_02254420
MOD20_02254420: ; 0x02254420
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	cmp r5, #0x1e
	blo _02254432
	bl GF_AssertFail
_02254432:
	cmp r4, #0x21
	blo _0225443A
	bl GF_AssertFail
_0225443A:
	cmp r5, #0x1e
	blo _02254440
	mov r5, #0
_02254440:
	cmp r4, #0x21
	blo _02254446
	mov r4, #0
_02254446:
	ldr r0, _02254458 ; =MOD20_02254744
	lsl r1, r5, #1
	ldrh r0, [r0, r1]
	lsl r1, r4, #1
	str r0, [r6]
	ldr r0, _0225445C ; =MOD20_02254780
	ldrh r0, [r0, r1]
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254458: .word MOD20_02254744
_0225445C: .word MOD20_02254780
	thumb_func_end MOD20_02254420

	thumb_func_start MOD20_02254460
MOD20_02254460: ; 0x02254460
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	cmp r5, #4
	blo _02254470
	bl GF_AssertFail
_02254470:
	ldr r0, _02254480 ; =MOD20_02254724
	lsl r1, r5, #3
	ldr r0, [r0, r1]
	str r0, [r4]
	ldr r0, _02254484 ; =MOD20_02254724 + 4
	ldr r0, [r0, r1]
	str r0, [r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254480: .word MOD20_02254724
_02254484: .word MOD20_02254724 + 4
	thumb_func_end MOD20_02254460

	thumb_func_start MOD20_02254488
MOD20_02254488: ; 0x02254488
	push {r4, r5}
	ldr r5, _022544B8 ; =MOD20_022547C2
	mov r4, #0
_0225448E:
	ldrh r3, [r5]
	cmp r0, r3
	bne _022544A8
	ldr r0, _022544BC ; =MOD20_022547C2 + 2
	lsl r3, r4, #2
	ldrb r0, [r0, r3]
	str r0, [r1]
	ldr r0, _022544C0 ; =MOD20_022547C2 + 3
	ldrb r0, [r0, r3]
	str r0, [r2]
	mov r0, #1
	pop {r4, r5}
	bx lr
_022544A8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x1d
	blo _0225448E
	mov r0, #0
	pop {r4, r5}
	bx lr
	nop
_022544B8: .word MOD20_022547C2
_022544BC: .word MOD20_022547C2 + 2
_022544C0: .word MOD20_022547C2 + 3
	thumb_func_end MOD20_02254488

	.rodata
	.global MOD20_022544C4
MOD20_022544C4: ; 0x022544C4
	.byte 0x60, 0xAC, 0xDC, 0xF4, 0x10, 0xAF, 0x10, 0xCF

	.global MOD20_022544CC
MOD20_022544CC: ; 0x022544CC
	.word MOD20_02252600, MOD20_02252688, MOD20_022527AC, MOD20_02252818

	.global sPoketchAppOverlayMapping
sPoketchAppOverlayMapping: ; 0x022544DC
	.word  0, SDK_OVERLAY_MODULE_21_ID
	.word 23, SDK_OVERLAY_MODULE_22_ID
	.word  1, SDK_OVERLAY_MODULE_23_ID
	.word  2, SDK_OVERLAY_MODULE_24_ID
	.word 11, SDK_OVERLAY_MODULE_25_ID
	.word 17, SDK_OVERLAY_MODULE_26_ID
	.word  4, SDK_OVERLAY_MODULE_27_ID
	.word  5, SDK_OVERLAY_MODULE_28_ID
	.word  6, SDK_OVERLAY_MODULE_29_ID
	.word 10, SDK_OVERLAY_MODULE_30_ID
	.word  3, SDK_OVERLAY_MODULE_31_ID
	.word  8, SDK_OVERLAY_MODULE_35_ID
	.word 18, SDK_OVERLAY_MODULE_36_ID
	.word 14, SDK_OVERLAY_MODULE_37_ID
	.word 15, SDK_OVERLAY_MODULE_38_ID
	.word 22, SDK_OVERLAY_MODULE_39_ID
	.word 24, SDK_OVERLAY_MODULE_40_ID
	.word 20, SDK_OVERLAY_MODULE_41_ID
	.word 12, SDK_OVERLAY_MODULE_42_ID
	.word  7, SDK_OVERLAY_MODULE_43_ID
	.word 21, SDK_OVERLAY_MODULE_44_ID
	.word 16, SDK_OVERLAY_MODULE_45_ID
	.word 13, SDK_OVERLAY_MODULE_47_ID
	.word 19, SDK_OVERLAY_MODULE_48_ID
	.word  9, SDK_OVERLAY_MODULE_49_ID

	.global MOD20_022545A4
MOD20_022545A4: ; 0x022545A4
	.byte 0x00, 0x00, 0x0B, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD20_022545B4
MOD20_022545B4: ; 0x022545B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD20_022545D0
MOD20_022545D0: ; 0x022545D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0D, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD20_022545EC
MOD20_022545EC: ; 0x022545EC
	.short 0x0000, 0x0001, 0x0002, 0x0003, 0x0015, 0x0016, 0x0017, 0x0018
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x002A, 0x002B, 0x002C, 0x002D
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x002A, 0x002B, 0x002C, 0x002D
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x002A, 0x002B, 0x002C, 0x002D
	.short 0x002A, 0x002B, 0x002C, 0x002D, 0x003F, 0x0040, 0x0041, 0x0042
	.short 0x0054, 0x0055, 0x0056, 0x0057

	.global MOD20_02254644
MOD20_02254644: ; 0x02254644
	.word 0x00000000, MOD20_02252ED0, 0x00000000
	.word 0x00000001, MOD20_02252FF0, 0x00000004
	.word 0x00000002, MOD20_02252FF0, 0x00000004
	.word 0x00000003, MOD20_02253228, 0x00000004
	.word 0x00000004, MOD20_02253100, 0x00000004
	.word 0x00000005, MOD20_0225328C, 0x00000004
	.word 0x00000006, MOD20_022532F0, 0x00000000
	.word 0x00000008, MOD20_02253338, 0x00000000
	.word 0x00000007, MOD20_02253378, 0x00000000
	.word 0x00000009, MOD20_022533C0, 0x00000000
	.word 0x0000000A, MOD20_022533EC, 0x00000000
	.word 0x0000000B, MOD20_0225340C, 0x00000000
	.word 0x0000000C, MOD20_022535CC, 0x00000000
	.word 0x0000000D, MOD20_02253668, 0x00000000
	.word 0x0000000E, MOD20_022536C8, 0x00000000
	.word 0xFFFFFFFF, 0x00000000, 0x00000000

	.global MOD20_02254704
MOD20_02254704: ; 0x02254704
	.byte 0x00, 0x02, 0x00, 0x04

	.global MOD20_02254708
MOD20_02254708: ; 0x02254708
	.byte 0x80, 0x02, 0x80, 0x04

	.global MOD20_0225470C
MOD20_0225470C: ; 0x0225470C
	.byte 0x01, 0x08, 0x0F, 0x04

	.global MOD20_02254710
MOD20_02254710: ; 0x02254710
	.word MOD20_02254340, MOD20_0225435C, MOD20_022543BC, MOD20_022543F4
	.word MOD20_0225440C

	.global MOD20_02254724
MOD20_02254724: ; 0x02254724
	.word 0x00000020, 0x0000002A
	.word 0x00000032, 0x0000002A
	.word 0x000000A8, 0x0000007A
	.word 0x000000C2, 0x0000003A

	.global MOD20_02254744
MOD20_02254744: ; 0x02254744
	.short 0x001A, 0x0020, 0x0026, 0x002C, 0x0032, 0x0038, 0x003E, 0x0044
	.short 0x004A, 0x0050, 0x0056, 0x005C, 0x0062, 0x0068, 0x006E, 0x0074
	.short 0x007A, 0x0080, 0x0086, 0x008C, 0x0092, 0x0098, 0x009E, 0x00A4
	.short 0x00AA, 0x00B0, 0x00B6, 0x00BC, 0x00C2, 0x00C8

	.global MOD20_02254780
MOD20_02254780: ; 0x02254780
	.short 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0018, 0x001E, 0x0024
	.short 0x002A, 0x0030, 0x0036, 0x003C, 0x0042, 0x0048, 0x004E, 0x0054
	.short 0x005A, 0x0060, 0x0066, 0x006C, 0x0072, 0x0078, 0x007E, 0x0084
	.short 0x008A, 0x0090, 0x0096, 0x009C, 0x00A2, 0x00A8, 0x00AE, 0x00B4
	.short 0x00BA

	.global MOD20_022547C2
MOD20_022547C2: ; 0x022547C2
	.short 0x0156
	.byte 0x2F, 0x96
	.short 0x0157
	.byte 0x38, 0x90
	.short 0x0158
	.byte 0x41, 0x84
	.short 0x0159
	.byte 0x32, 0x7E
	.short 0x015A
	.byte 0x32, 0x78
	.short 0x015B
	.byte 0x3E, 0x6C
	.short 0x015D
	.byte 0x4A, 0x5A
	.short 0x015E
	.byte 0x50, 0x6F
	.short 0x0161
	.byte 0x53, 0x7E
	.short 0x0162
	.byte 0x65, 0x7E
	.short 0x0164
	.byte 0x7D, 0x7E
	.short 0x016A
	.byte 0x80, 0x66
	.short 0x016B
	.byte 0x7A, 0x5A
	.short 0x016D
	.byte 0x5C, 0x5A
	.short 0x016E
	.byte 0x68, 0x5A
	.short 0x016F
	.byte 0x6E, 0x8A
	.short 0x0173
	.byte 0x77, 0x96
	.short 0x0175
	.byte 0x98, 0x93
	.short 0x017C
	.byte 0x98, 0x78
	.short 0x017E
	.byte 0x8C, 0x66
	.short 0x017F
	.byte 0x56, 0x42
	.short 0x0181
	.byte 0x50, 0x33
	.short 0x0184
	.byte 0x29, 0x84
	.short 0x0187
	.byte 0x38, 0x9C
	.short 0x01D3
	.byte 0x3B, 0xA2
	.short 0x0188
	.byte 0x4A, 0xA2
	.short 0x018B
	.byte 0xAA, 0x8A
	.short 0x00C8
	.byte 0x44, 0x72
	.short 0x00CC
	.byte 0x38, 0x66

	.data
	.bss
