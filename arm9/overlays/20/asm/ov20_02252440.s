	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

    thumb_func_start ov20_02252440
ov20_02252440: ; 0x02252440
	ldr r3, _02252444 ; =sub_02037790
	bx r3
	.align 2, 0
_02252444: .word sub_02037790
	thumb_func_end ov20_02252440

	thumb_func_start ov20_02252448
ov20_02252448: ; 0x02252448
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #3
	str r2, [sp]
	mov r1, #7
	lsl r2, r0, #0xe
	add r7, r3, #0
	bl CreateHeap
	mov r0, #3
	mov r1, #8
	lsl r2, r0, #0xe
	bl CreateHeap
	mov r0, #7
	mov r1, #0x60
	bl AllocFromHeap
	add r4, r0, #0
	beq _022524B2
	str r4, [r5]
	ldr r0, [sp]
	str r6, [r4, #0x5c]
	str r0, [r4, #0x54]
	bl Save_Poketch_Get
	str r0, [r4, #0x58]
	ldr r0, [sp, #0x18]
	str r7, [r4, #0x4c]
	str r0, [r4, #0x50]
	add r0, r4, #0
	bl ov20_0225253C
	cmp r0, #0
	beq _022524B2
	bl sub_0201CC08
	mov r0, #4
	bl sub_0201CC24
	ldr r0, _022524B4 ; =ov20_022525F0
	str r5, [r4, #0x34]
	add r1, r4, #0
	mov r2, #4
	bl sub_0200CA44
	str r0, [r4, #0x38]
	ldr r0, _022524B8 ; =ov20_0225259C
	add r1, r4, #0
	mov r2, #0
	bl sub_0200CA44
_022524B2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022524B4: .word ov20_022525F0
_022524B8: .word ov20_0225259C
	thumb_func_end ov20_02252448

	thumb_func_start ov20_022524BC
ov20_022524BC: ; 0x022524BC
	push {r3, lr}
	ldrb r1, [r0]
	cmp r1, #3
	beq _022524CE
	cmp r1, #4
	beq _022524CE
	mov r1, #3
	bl ov20_022525F8
_022524CE:
	pop {r3, pc}
	thumb_func_end ov20_022524BC

	thumb_func_start ov20_022524D0
ov20_022524D0: ; 0x022524D0
	cmp r0, #0
	bne _022524D8
	mov r0, #1
	bx lr
_022524D8:
	mov r0, #0
	bx lr
	thumb_func_end ov20_022524D0

	thumb_func_start ov20_022524DC
ov20_022524DC: ; 0x022524DC
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
	bl Save_Poketch_GetStepCounter
	add r1, r0, #1
	ldr r0, _02252530 ; =0x0001869F
	cmp r1, r0
	bls _02252512
	mov r1, #0
_02252512:
	ldr r0, [r4, #0x58]
	bl Save_Poketch_SetStepCounter
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
	thumb_func_end ov20_022524DC

	thumb_func_start ov20_02252534
ov20_02252534: ; 0x02252534
	ldrb r0, [r0, #3]
	bx lr
	thumb_func_end ov20_02252534

	thumb_func_start ov20_02252538
ov20_02252538: ; 0x02252538
	ldr r0, [r0, #0x14]
	bx lr
	thumb_func_end ov20_02252538

	thumb_func_start ov20_0225253C
ov20_0225253C: ; 0x0225253C
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r2, [r4, #0x50]
	add r0, #0x1c
	add r1, #0x20
	add r3, r4, #0
	bl ov20_02252C5C
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
	bl ov20_022529C4
	cmp r0, #0
	beq _02252578
	mov r0, #1
	pop {r4, pc}
_02252578:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov20_0225253C

	thumb_func_start ov20_0225257C
ov20_0225257C: ; 0x0225257C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x38]
	bl sub_0200CAB4
	add r0, r4, #0
	bl ov20_02252A08
	add r0, r4, #0
	bl ClosePoketchApp
	ldr r0, [r4, #0x1c]
	bl ov20_02252E18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov20_0225257C

	thumb_func_start ov20_0225259C
ov20_0225259C: ; 0x0225259C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #4
	bhs _022525C0
	cmp r0, #0
	beq _022525B2
	add r0, r4, #0
	bl ov20_02252A14
_022525B2:
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022525EC ; =ov20_022544CC
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
	bl ov20_0225257C
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
	mov r0, #7
	bl DestroyHeap
	mov r0, #8
	bl DestroyHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
_022525EC: .word ov20_022544CC
	thumb_func_end ov20_0225259C

	thumb_func_start ov20_022525F0
ov20_022525F0: ; 0x022525F0
	mov r0, #0
	strb r0, [r1, #4]
	strb r0, [r1, #7]
	bx lr
	thumb_func_end ov20_022525F0

	thumb_func_start ov20_022525F8
ov20_022525F8: ; 0x022525F8
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	thumb_func_end ov20_022525F8

	thumb_func_start ov20_02252600
ov20_02252600: ; 0x02252600
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
	bl ov20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_0225262E:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	bl ov20_02252EA4
	cmp r0, #0
	beq _02252684
	ldr r0, [r4, #0x58]
	bl Save_Poketch_GetSelectedApp
	add r5, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl LoadPoketchApp
	add r0, r4, #0
	add r1, r5, #0
	bl ov20_02252918
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_0225265A:
	bl ov20_0225293C
	cmp r0, #0
	beq _02252684
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl ov20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
_02252670:
	ldr r0, [r4, #0x1c]
	mov r1, #1
	bl ov20_02252EA4
	cmp r0, #0
	beq _02252684
	add r0, r4, #0
	mov r1, #1
	bl ov20_022525F8
_02252684:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov20_02252600

	thumb_func_start ov20_02252688
ov20_02252688: ; 0x02252688
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
	bl ov20_02252C08
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
	bl ov20_02252E80
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
	bl ov20_02252EB0
	cmp r0, #0
	beq _022527AA
	ldr r0, [r4, #0x58]
	bl Save_Poketch_CycleNextApp
	str r0, [r4, #0x20]
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02252710
	ldr r0, [r4, #0x1c]
	mov r1, #9
	bl ov20_02252E80
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
	bl ov20_02252E80
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
	bl ov20_0225294C
	mov r0, #3
	strb r0, [r4, #1]
	pop {r4, pc}
_02252750:
	bl ov20_02252968
	cmp r0, #0
	beq _022527AA
	add r0, r4, #0
	bl ClosePoketchApp
	bl sub_020893E0
	add r0, r4, #0
	mov r1, #2
	bl ov20_022525F8
	pop {r4, pc}
_0225276C:
	ldr r0, [r4, #8]
	cmp r0, #3
	beq _02252776
	cmp r0, #5
	bne _0225278C
_02252776:
	ldr r0, [r4, #0x58]
	bl Save_Poketch_CycleNextApp
	str r0, [r4, #0x20]
	mov r0, #0x1e
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x1c]
	mov r1, #0xa
	bl ov20_02252E80
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
	bl ov20_02252E80
	add r0, r4, #0
	bl ov20_0225294C
	mov r0, #3
	strb r0, [r4, #1]
_022527AA:
	pop {r4, pc}
	thumb_func_end ov20_02252688

	thumb_func_start ov20_022527AC
ov20_022527AC: ; 0x022527AC
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
	bl Save_Poketch_GetSelectedApp
	add r5, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl LoadPoketchApp
	add r0, r4, #0
	add r1, r5, #0
	bl ov20_02252918
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_022527E4:
	bl ov20_0225293C
	cmp r0, #0
	beq _02252816
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl ov20_02252E80
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	pop {r3, r4, r5, pc}
_022527FC:
	ldr r0, [r4, #0x1c]
	mov r1, #2
	bl ov20_02252EA4
	cmp r0, #0
	beq _02252816
	mov r0, #0
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	add r0, r4, #0
	mov r1, #1
	bl ov20_022525F8
_02252816:
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_022527AC

	thumb_func_start ov20_02252818
ov20_02252818: ; 0x02252818
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
	bl ov20_0225294C
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_02252860:
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_02252866:
	bl ov20_0225293C
	cmp r0, #0
	beq _022528AC
	add r0, r4, #0
	bl ov20_0225294C
	mov r0, #2
	strb r0, [r4, #1]
	pop {r4, pc}
_0225287A:
	bl ov20_02252968
	cmp r0, #0
	beq _022528AC
	ldr r0, [r4, #0x1c]
	mov r1, #0xe
	bl ov20_02252E80
	mov r0, #3
	strb r0, [r4, #1]
	pop {r4, pc}
_02252890:
	ldr r0, [r4, #0x1c]
	bl ov20_02252EB0
	cmp r0, #0
	beq _022528AC
	add r0, r4, #0
	bl ClosePoketchApp
	bl sub_0201CD04
	add r0, r4, #0
	mov r1, #4
	bl ov20_022525F8
_022528AC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov20_02252818

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

	thumb_func_start ov20_02252918
ov20_02252918: ; 0x02252918
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
	thumb_func_end ov20_02252918

	thumb_func_start ov20_0225293C
ov20_0225293C: ; 0x0225293C
	ldrb r0, [r0, #2]
	cmp r0, #2
	bne _02252946
	mov r0, #1
	bx lr
_02252946:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end ov20_0225293C

	thumb_func_start ov20_0225294C
ov20_0225294C: ; 0x0225294C
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
	thumb_func_end ov20_0225294C

	thumb_func_start ov20_02252968
ov20_02252968: ; 0x02252968
	ldrb r0, [r0, #2]
	cmp r0, #0
	bne _02252972
	mov r0, #1
	bx lr
_02252972:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end ov20_02252968

	thumb_func_start Poketch_InitApp
Poketch_InitApp: ; 0x02252978
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov20_02252440
	str r5, [r0, #0x3c]
	str r4, [r0, #0x40]
	mov r1, #0
	str r1, [r0, #0x44]
	pop {r3, r4, r5, pc}
	thumb_func_end Poketch_InitApp

	thumb_func_start ov20_0225298C
ov20_0225298C: ; 0x0225298C
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
	thumb_func_end ov20_0225298C

	thumb_func_start ov20_022529A0
ov20_022529A0: ; 0x022529A0
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
	thumb_func_end ov20_022529A0

	thumb_func_start ov20_022529B4
ov20_022529B4: ; 0x022529B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov20_02252440
	str r5, [r0, #0x44]
	str r4, [r0, #0x48]
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_022529B4

	thumb_func_start ov20_022529C4
ov20_022529C4: ; 0x022529C4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #7
	str r0, [sp]
	ldr r0, _02252A00 ; =ov20_022544C4
	ldr r2, _02252A04 ; =ov20_02252A24
	mov r1, #2
	add r3, r4, #0
	bl ov20_02254130
	str r0, [r4, #0x28]
	cmp r0, #0
	beq _022529F8
	mov r1, #0
	add r2, r1, #0
	mov r3, #7
	bl ov20_022542AC
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
_02252A00: .word ov20_022544C4
_02252A04: .word ov20_02252A24
	thumb_func_end ov20_022529C4

	thumb_func_start ov20_02252A08
ov20_02252A08: ; 0x02252A08
	ldr r3, _02252A10 ; =ov20_02254198
	ldr r0, [r0, #0x28]
	bx r3
	nop
_02252A10: .word ov20_02254198
	thumb_func_end ov20_02252A08

	thumb_func_start ov20_02252A14
ov20_02252A14: ; 0x02252A14
	ldr r3, _02252A20 ; =ov20_022541B4
	mov r1, #0
	str r1, [r0, #8]
	ldr r0, [r0, #0x28]
	bx r3
	nop
_02252A20: .word ov20_022541B4
	thumb_func_end ov20_02252A14

	thumb_func_start ov20_02252A24
ov20_02252A24: ; 0x02252A24
	push {r3, r4, r5, r6, r7, lr}
	add r5, r3, #0
	add r4, r0, #0
	add r0, r5, #0
	add r6, r1, #0
	add r7, r2, #0
	bl ov20_02252C08
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
	bl ov20_02252C08
	cmp r0, #0
	beq _02252AEA
	cmp r7, #1
	bne _02252AEA
	ldr r0, _02252AEC ; =0x0000066E
	bl PlaySE
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
	bl ov20_02252C08
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
	bl ov20_02252AF0
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
	bl ov20_022542CC
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
	thumb_func_end ov20_02252A24

	thumb_func_start ov20_02252AF0
ov20_02252AF0: ; 0x02252AF0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_02252AF8:
	add r0, r5, #0
	add r1, r6, #0
	bl ov20_02252EA4
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
	bl ov20_02252E80
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov20_02252AF0

	thumb_func_start ov20_02252B1C
ov20_02252B1C: ; 0x02252B1C
	push {r3, lr}
	bl ov20_02252440
	ldr r0, [r0, #0x1c]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov20_02252B1C

	thumb_func_start ov20_02252B28
ov20_02252B28: ; 0x02252B28
	push {r4, lr}
	add r4, r0, #0
	bl ov20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252B46
	bl ov20_02252C08
	cmp r0, #0
	bne _02252B46
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl PlaySE
_02252B46:
	pop {r4, pc}
	thumb_func_end ov20_02252B28

	thumb_func_start ov20_02252B48
ov20_02252B48: ; 0x02252B48
	push {r4, lr}
	add r4, r0, #0
	bl ov20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252B66
	bl ov20_02252C08
	cmp r0, #0
	bne _02252B66
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl sub_02005578
_02252B66:
	pop {r4, pc}
	thumb_func_end ov20_02252B48

	thumb_func_start ov20_02252B68
ov20_02252B68: ; 0x02252B68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252BB4
	bl ov20_02252C08
	cmp r0, #0
	bne _02252BB4
	add r0, r5, #0
	add r1, r4, #0
	bl sub_02020AB0
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
	thumb_func_end ov20_02252B68

	thumb_func_start ov20_02252BB8
ov20_02252BB8: ; 0x02252BB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov20_02252440
	ldrb r1, [r0, #5]
	cmp r1, #0
	bne _02252C04
	bl ov20_02252C08
	cmp r0, #0
	bne _02252C04
	add r0, r5, #0
	add r1, r4, #0
	bl sub_02020ACC
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
	thumb_func_end ov20_02252BB8

	thumb_func_start ov20_02252C08
ov20_02252C08: ; 0x02252C08
	ldr r3, _02252C10 ; =sub_0204646C
	ldr r0, [r0, #0x5c]
	bx r3
	nop
_02252C10: .word sub_0204646C
	thumb_func_end ov20_02252C08

	thumb_func_start ov20_02252C14
ov20_02252C14: ; 0x02252C14
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov20_02252C08
	cmp r0, #0
	bne _02252C2E
	ldrb r0, [r5, #5]
	cmp r0, #0
	bne _02252C2E
	add r0, r4, #0
	bl ov20_022541B4
_02252C2E:
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_02252C14

	thumb_func_start ov20_02252C30
ov20_02252C30: ; 0x02252C30
	ldrb r0, [r0, #4]
	bx lr
	thumb_func_end ov20_02252C30

	thumb_func_start ov20_02252C34
ov20_02252C34: ; 0x02252C34
	ldrb r0, [r0, #7]
	bx lr
	thumb_func_end ov20_02252C34

	thumb_func_start ov20_02252C38
ov20_02252C38: ; 0x02252C38
	ldr r0, [r0, #0x5c]
	bx lr
	thumb_func_end ov20_02252C38

	thumb_func_start ov20_02252C3C
ov20_02252C3C: ; 0x02252C3C
	ldr r0, [r0, #0x58]
	bx lr
	thumb_func_end ov20_02252C3C

	thumb_func_start ov20_02252C40
ov20_02252C40: ; 0x02252C40
	ldr r0, [r0, #0x54]
	bx lr
	thumb_func_end ov20_02252C40

	thumb_func_start ov20_02252C44
ov20_02252C44: ; 0x02252C44
	push {r3, lr}
	ldr r0, [r0, #0x54]
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	cmp r0, #1
	beq _02252C58
	mov r0, #1
	pop {r3, pc}
_02252C58:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end ov20_02252C44

    .section .rodata

    .global ov20_022544C4
ov20_022544C4: ; 0x022544C4
	.byte 0x60, 0xAC, 0xDC, 0xF4, 0x10, 0xAF, 0x10, 0xCF

	.global ov20_022544CC
ov20_022544CC: ; 0x022544CC
	.word ov20_02252600, ov20_02252688, ov20_022527AC, ov20_02252818
    
    .global sPoketchAppOverlayMapping
sPoketchAppOverlayMapping: ; 0x022544DC
	.word  0, SDK_OVERLAY_OVERLAY_21_ID
	.word 23, SDK_OVERLAY_OVERLAY_22_ID
	.word  1, SDK_OVERLAY_OVERLAY_23_ID
	.word  2, SDK_OVERLAY_OVERLAY_24_ID
	.word 11, SDK_OVERLAY_OVERLAY_25_ID
	.word 17, SDK_OVERLAY_OVERLAY_26_ID
	.word  4, SDK_OVERLAY_OVERLAY_27_ID
	.word  5, SDK_OVERLAY_OVERLAY_28_ID
	.word  6, SDK_OVERLAY_OVERLAY_29_ID
	.word 10, SDK_OVERLAY_OVERLAY_30_ID
	.word  3, SDK_OVERLAY_OVERLAY_31_ID
	.word  8, SDK_OVERLAY_OVERLAY_35_ID
	.word 18, SDK_OVERLAY_OVERLAY_36_ID
	.word 14, SDK_OVERLAY_OVERLAY_37_ID
	.word 15, SDK_OVERLAY_OVERLAY_38_ID
	.word 22, SDK_OVERLAY_OVERLAY_39_ID
	.word 24, SDK_OVERLAY_OVERLAY_40_ID
	.word 20, SDK_OVERLAY_OVERLAY_41_ID
	.word 12, SDK_OVERLAY_OVERLAY_42_ID
	.word  7, SDK_OVERLAY_OVERLAY_43_ID
	.word 21, SDK_OVERLAY_OVERLAY_44_ID
	.word 16, SDK_OVERLAY_OVERLAY_45_ID
	.word 13, SDK_OVERLAY_OVERLAY_47_ID
	.word 19, SDK_OVERLAY_OVERLAY_48_ID
	.word  9, SDK_OVERLAY_OVERLAY_49_ID

