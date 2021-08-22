	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021E05FC
MOD04_021E05FC: ; 0x021E05FC
	ldr r0, _021E0624 ; =UNK04_022106C8
	ldr r0, [r0]
	cmp r0, #0
	beq _021E061C
	ldr r0, [r0, #4]
	cmp r0, #5
	moveq r0, #1
	bxeq lr
_021E061C:
	mov r0, #0
	bx lr
	.align 2, 0
_021E0624: .word UNK04_022106C8
	arm_func_end MOD04_021E05FC

	arm_func_start MOD04_021E0628
MOD04_021E0628: ; 0x021E0628
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x4c
	mov r4, r1
	ldr r1, [r4]
	mov r5, r0
	cmp r1, #0
	addne sp, sp, #0x4c
	ldmneia sp!, {r4, r5, pc}
	ldr r1, _021E07CC ; =UNK04_022106C8
	ldr r2, [r1]
	ldr r1, [r2, #4]
	cmp r1, #3
	bne _021E0704
	ldrsb r1, [r4, #0x8e]
	cmp r1, #0
	bne _021E06DC
	ldr r0, [r2, #0x1c]
	ldr r1, [r2, #0xc]
	add r2, sp, #8
	add r0, r0, #4
	bl DWCi_Acc_LoginIdToUserName
	ldr r1, _021E07D0 ; =0x00000705
	add r2, sp, #8
	mov r0, r5
	bl MOD04_021F0B30
	bl MOD04_021E0DB0
	cmp r0, #0
	addne sp, sp, #0x4c
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021E07CC ; =UNK04_022106C8
	mov r3, #4
	ldr r1, [r0]
	ldr r0, _021E07D4 ; =MOD04_021E0628
	str r3, [r1, #4]
	mov r2, #0
	str r0, [sp]
	str r2, [sp, #4]
	ldr r1, [r4, #4]
	mov r0, r5
	mov r3, r2
	bl MOD04_021F0B9C
	bl MOD04_021E0DB0
	add sp, sp, #0x4c
	cmp r0, #0
	ldmia sp!, {r4, r5, pc}
_021E06DC:
	bl MOD04_021F0D54
	ldr r0, _021E07D8 ; =MOD04_021E0C80
	mov r1, #0
	bl MOD04_021E0A00
	ldr r0, _021E07CC ; =UNK04_022106C8
	mov r1, #1
	ldr r0, [r0]
	add sp, sp, #0x4c
	str r1, [r0, #4]
	ldmia sp!, {r4, r5, pc}
_021E0704:
	cmp r1, #4
	addne sp, sp, #0x4c
	ldmneia sp!, {r4, r5, pc}
	ldr r0, [r2, #0x1c]
	ldr r1, [r2, #0xc]
	add r2, sp, #0x1d
	add r0, r0, #4
	bl DWCi_Acc_LoginIdToUserName
	add r1, sp, #0x1d
	add r0, r4, #0x8e
	bl strcmp
	cmp r0, #0
	bne _021E079C
	ldr r0, _021E07CC ; =UNK04_022106C8
	add r2, sp, #0x32
	ldr r0, [r0]
	ldr r1, [r0, #0xc]
	add r0, r0, #0x3c
	bl DWCi_Acc_LoginIdToUserName
	ldr r0, _021E07CC ; =UNK04_022106C8
	ldr r2, [r4, #4]
	ldr r1, [r0]
	ldr r0, [r1, #0x1c]
	add r1, r1, #0x3c
	bl DWCi_Acc_SetLoginIdToUserData
	mov r0, r5
	bl MOD04_021F0D54
	ldr r0, _021E07CC ; =UNK04_022106C8
	ldr r1, _021E07DC ; =UNK04_022106C4
	ldr r4, [r0]
	ldr r0, _021E07E0 ; =UNK04_022106CC
	ldr r2, [r1]
	ldr r3, [r0]
	add r0, r4, #0x48
	add r1, r4, #0x148
	blx r3
	add sp, sp, #0x4c
	ldmia sp!, {r4, r5, pc}
_021E079C:
	ldr r0, _021E07D4 ; =MOD04_021E0628
	mov r2, #0
	str r0, [sp]
	str r2, [sp, #4]
	ldr r1, [r4, #4]
	mov r0, r5
	mov r3, r2
	bl MOD04_021F0B9C
	bl MOD04_021E0DB0
	cmp r0, #0
	add sp, sp, #0x4c
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E07CC: .word UNK04_022106C8
_021E07D0: .word 0x00000705
_021E07D4: .word MOD04_021E0628
_021E07D8: .word MOD04_021E0C80
_021E07DC: .word UNK04_022106C4
_021E07E0: .word UNK04_022106CC
	arm_func_end MOD04_021E0628

	arm_func_start MOD04_021E07E4
MOD04_021E07E4: ; 0x021E07E4
	stmdb sp!, {lr}
	sub sp, sp, #0x3d4
	bl MOD04_021D988C
	cmp r0, #0x15
	bne _021E08BC
	add r0, sp, #0
	bl MOD04_021D97F8
	ldr r0, _021E09DC ; =UNK04_022106C8
	add r1, sp, #0x4a
	ldr r0, [r0]
	add r0, r0, #0x48
	bl strcpy
	ldr r0, _021E09DC ; =UNK04_022106C8
	add r1, sp, #0x100
	ldr r0, [r0]
	add r1, r1, #0x77
	add r0, r0, #0x148
	bl strcpy
	bl MOD04_021D991C
	ldr r1, _021E09DC ; =UNK04_022106C8
	mov r0, #0
	ldr r1, [r1]
	mov r2, r0
	ldr r1, [r1, #0x24]
	bl MOD04_021DD904
	ldr r0, _021E09DC ; =UNK04_022106C8
	mov r2, #0
	ldr r1, [r0]
	str r2, [r1, #0x24]
	ldr r0, [r0]
	ldr r0, [r0, #0x1c]
	bl DWCi_Acc_IsAuthentic
	cmp r0, #0
	beq _021E0898
	ldr r0, _021E09DC ; =UNK04_022106C8
	ldr r1, _021E09E0 ; =UNK04_022106C4
	ldr ip, [r0]
	ldr r0, _021E09E4 ; =UNK04_022106CC
	ldr r2, [r1]
	ldr r3, [r0]
	add r0, ip, #0x48
	add r1, ip, #0x148
	blx r3
	add sp, sp, #0x3d4
	ldmfd sp!, {pc}
_021E0898:
	ldr r0, _021E09DC ; =UNK04_022106C8
	ldr r2, _021E09E8 ; =MOD04_021E0C98
	ldr r1, [r0]
	mov r3, #3
	add r0, r1, #0x48
	add r1, r1, #0x148
	bl MOD04_021E0BE0
	add sp, sp, #0x3d4
	ldmfd sp!, {pc}
_021E08BC:
	bl MOD04_021D988C
	cmp r0, #0
	addeq sp, sp, #0x3d4
	ldmeqia sp!, {pc}
	bl OS_GetTick
	ldr r3, _021E09DC ; =UNK04_022106C8
	ldr r2, _021E09EC ; =0x000082EA
	ldr ip, [r3]
	mov r3, #0
	ldr lr, [ip, #0x28]
	ldr ip, [ip, #0x2c]
	subs lr, r0, lr
	sbc r0, r1, ip
	mov r1, r0, lsl #6
	orr r1, r1, lr, lsr #26
	mov r0, lr, lsl #6
	bl _ll_udiv
	ldr r2, _021E09F0 ; =0x00002710
	cmp r1, #0
	cmpeq r0, r2
	bls _021E0958
	add r0, sp, #0x1c4
	bl MOD04_021D97F8
	bl MOD04_021D991C
	ldr r1, _021E09DC ; =UNK04_022106C8
	mov r0, #0
	ldr r1, [r1]
	mov r2, r0
	ldr r1, [r1, #0x24]
	bl MOD04_021DD904
	ldr r0, _021E09DC ; =UNK04_022106C8
	mov r2, #0
	ldr r1, [r0]
	mov r0, #2
	str r2, [r1, #0x24]
	ldr r1, [sp, #0x1c4]
	bl MOD04_021E0EAC
	add sp, sp, #0x3d4
	ldmfd sp!, {pc}
_021E0958:
	bl MOD04_021D991C
	add r0, sp, #0x388
	mov r1, #0
	mov r2, #0x48
	bl MI_CpuFill8
	ldr r0, _021E09DC ; =UNK04_022106C8
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	bl MOD04_021DE89C
	ldr r1, _021E09DC ; =UNK04_022106C8
	mov r2, r0, lsl #1
	ldr r1, [r1]
	add r2, r2, #2
	ldr r0, [r1, #0x10]
	add r1, sp, #0x388
	bl MI_CpuCopy8
	ldr r0, _021E09DC ; =UNK04_022106C8
	ldr r1, _021E09F4 ; =0x00000251
	ldr r2, [r0]
	add r0, sp, #0x3bc
	add r1, r2, r1
	bl strcpy
	ldr r2, _021E09F8 ; =MOD04_021DD944
	ldr r0, _021E09DC ; =UNK04_022106C8
	str r2, [sp, #0x3c8]
	ldr r2, _021E09FC ; =MOD04_021DD904
	ldr r1, [r0]
	str r2, [sp, #0x3cc]
	ldr r1, [r1, #0x24]
	add r0, sp, #0x388
	bl MOD04_021D9ACC
	add sp, sp, #0x3d4
	ldmfd sp!, {pc}
	.align 2, 0
_021E09DC: .word UNK04_022106C8
_021E09E0: .word UNK04_022106C4
_021E09E4: .word UNK04_022106CC
_021E09E8: .word MOD04_021E0C98
_021E09EC: .word 0x000082EA
_021E09F0: .word 0x00002710
_021E09F4: .word 0x00000251
_021E09F8: .word MOD04_021DD944
_021E09FC: .word MOD04_021DD904
	arm_func_end MOD04_021E07E4

	arm_func_start MOD04_021E0A00
MOD04_021E0A00: ; 0x021E0A00
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x4c
	mov r5, r0
	mov r4, r1
	add r0, sp, #0
	mov r1, #0
	mov r2, #0x48
	bl MI_CpuFill8
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r2, _021E0BBC ; =UNK04_022106CC
	ldr r1, _021E0BC0 ; =UNK04_022106C4
	ldr r0, [r0]
	str r5, [r2]
	str r4, [r1]
	ldr r0, [r0, #0x1c]
	bl DWCi_Acc_IsAuthentic
	cmp r0, #0
	beq _021E0A68
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r1, [r0]
	ldr r0, [r1, #0x1c]
	add r2, r1, #0x248
	ldr r1, [r0, #0x24]
	add r0, r0, #0x10
	bl DWCi_Acc_LoginIdToUserName
	b _021E0B1C
_021E0A68:
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r0, [r0]
	add r0, r0, #0x3c
	bl DWCi_Acc_IsValidLoginId
	cmp r0, #0
	bne _021E0AD0
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r0, [r0]
	ldr r0, [r0, #0x1c]
	add r0, r0, #4
	bl DWCi_Acc_CheckConsoleUserId
	cmp r0, #0
	beq _021E0ABC
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r1, [r0]
	ldr r0, [r1, #0x1c]
	add r3, r1, #0x3c
	add r0, r0, #4
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	b _021E0B04
_021E0ABC:
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r0, [r0]
	add r0, r0, #0x3c
	bl DWCi_Acc_CreateTempLoginId
	b _021E0B04
_021E0AD0:
	bl OS_GetTick
	ldr r2, _021E0BC4 ; =0x6C078965
	ldr r3, _021E0BC8 ; =0x5D588B65
	umull ip, r4, r0, r2
	mla r4, r0, r3, r4
	ldr r3, _021E0BB8 ; =UNK04_022106C8
	ldr r0, _021E0BCC ; =0x00269EC3
	mla r4, r1, r2, r4
	adds r0, ip, r0
	ldr r3, [r3]
	adc r1, r4, #0
	add r0, r3, #0x3c
	bl DWCi_Acc_SetPlayerId
_021E0B04:
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r2, [r0]
	ldr r1, [r2, #0xc]
	add r0, r2, #0x3c
	add r2, r2, #0x248
	bl DWCi_Acc_LoginIdToUserName
_021E0B1C:
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	bl MOD04_021DE89C
	ldr r1, _021E0BB8 ; =UNK04_022106C8
	mov r2, r0, lsl #1
	ldr r1, [r1]
	add r2, r2, #2
	ldr r0, [r1, #0x10]
	add r1, sp, #0
	bl MI_CpuCopy8
	ldr r0, _021E0BB8 ; =UNK04_022106C8
	ldr r1, _021E0BD0 ; =0x00000251
	ldr r2, [r0]
	add r0, sp, #0x34
	add r1, r2, r1
	bl strcpy
	ldr r4, _021E0BD4 ; =MOD04_021DD944
	ldr r3, _021E0BD8 ; =MOD04_021DD904
	ldr r1, _021E0BDC ; =0x00001C10
	mov r0, #0
	mov r2, #4
	str r4, [sp, #0x40]
	str r3, [sp, #0x44]
	bl MOD04_021DD924
	ldr r1, _021E0BB8 ; =UNK04_022106C8
	mov r4, r0
	ldr r0, [r1]
	str r4, [r0, #0x24]
	bl OS_GetTick
	ldr r2, _021E0BB8 ; =UNK04_022106C8
	ldr r2, [r2]
	str r0, [r2, #0x28]
	str r1, [r2, #0x2c]
	mov r1, r4
	add r0, sp, #0
	bl MOD04_021D9ACC
	add sp, sp, #0x4c
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E0BB8: .word UNK04_022106C8
_021E0BBC: .word UNK04_022106CC
_021E0BC0: .word UNK04_022106C4
_021E0BC4: .word 0x6C078965
_021E0BC8: .word 0x5D588B65
_021E0BCC: .word 0x00269EC3
_021E0BD0: .word 0x00000251
_021E0BD4: .word MOD04_021DD944
_021E0BD8: .word MOD04_021DD904
_021E0BDC: .word 0x00001C10
	arm_func_end MOD04_021E0A00

	arm_func_start MOD04_021E0BE0
MOD04_021E0BE0: ; 0x021E0BE0
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x10
	ldr r4, _021E0C7C ; =UNK04_022106C8
	mov r6, r1
	ldr r4, [r4]
	mov r1, r0
	add r0, r4, #0x48
	mov r5, r2
	mov r4, r3
	bl strcpy
	ldr r0, _021E0C7C ; =UNK04_022106C8
	mov r1, r6
	ldr r0, [r0]
	add r0, r0, #0x148
	bl strcpy
	ldr r0, _021E0C7C ; =UNK04_022106C8
	ldr r6, [r0]
	bl OS_GetTick
	str r0, [r6, #0x34]
	str r1, [r6, #0x38]
	mov r3, #1
	ldr r0, _021E0C7C ; =UNK04_022106C8
	str r3, [r6, #0x30]
	ldr r2, [r0]
	mov r1, #0
	str r1, [sp]
	str r5, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r2]
	add r1, r2, #0x48
	add r2, r2, #0x148
	bl MOD04_021F0D8C
	bl MOD04_021E0DB0
	cmp r0, #0
	ldreq r0, _021E0C7C ; =UNK04_022106C8
	ldreq r0, [r0]
	streq r4, [r0, #4]
	add sp, sp, #0x10
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E0C7C: .word UNK04_022106C8
	arm_func_end MOD04_021E0BE0

	arm_func_start MOD04_021E0C80
MOD04_021E0C80: ; 0x021E0C80
	ldr ip, _021E0C90 ; =MOD04_021E0BE0
	ldr r2, _021E0C94 ; =MOD04_021E0C98
	mov r3, #2
	bx ip
	.align 2, 0
_021E0C90: .word MOD04_021E0BE0
_021E0C94: .word MOD04_021E0C98
	arm_func_end MOD04_021E0C80

	arm_func_start MOD04_021E0C98
MOD04_021E0C98: ; 0x021E0C98
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r3, _021E0DA0 ; =UNK04_022106C8
	mov r2, #0
	ldr ip, [r3]
	mov r4, r1
	str r2, [ip, #0x30]
	ldr r1, [r4]
	cmp r1, #0
	bne _021E0D90
	ldr ip, [r3]
	ldr r1, [ip, #4]
	cmp r1, #2
	bne _021E0D5C
	ldr r1, [ip, #0x1c]
	ldr r0, [r4, #4]
	ldr r1, [r1, #0x1c]
	cmp r1, r0
	bne _021E0D48
	ldr r1, _021E0DA4 ; =UNK04_0220D34C
	mov r3, #5
	mov r0, #1
	str r3, [ip, #4]
	bl MOD04_021E1E30
	bl MOD04_021E0DB0
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r4, pc}
	ldr r0, _021E0DA0 ; =UNK04_022106C8
	ldr r1, [r4, #4]
	ldr r3, [r0]
	mov r0, #0
	ldr r2, [r3, #0x18]
	ldr r3, [r3, #0x14]
	blx r3
	bl MOD04_021DF7C4
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r4, pc}
	ldr r0, [r4, #4]
	bl MOD04_021EA1E0
	add sp, sp, #8
	cmp r0, #0
	ldmia sp!, {r4, pc}
_021E0D48:
	ldr r1, _021E0DA8 ; =0xFFFF15A0
	mov r0, #6
	bl MOD04_021E0EAC
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_021E0D5C:
	cmp r1, #3
	addne sp, sp, #8
	ldmneia sp!, {r4, pc}
	ldr r1, _021E0DAC ; =MOD04_021E0628
	mov r3, r2
	str r1, [sp]
	str r2, [sp, #4]
	ldr r1, [r4, #4]
	bl MOD04_021F0B9C
	bl MOD04_021E0DB0
	add sp, sp, #8
	cmp r0, #0
	ldmia sp!, {r4, pc}
_021E0D90:
	mov r0, r1
	bl MOD04_021E0DB0
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E0DA0: .word UNK04_022106C8
_021E0DA4: .word UNK04_0220D34C
_021E0DA8: .word 0xFFFF15A0
_021E0DAC: .word MOD04_021E0628
	arm_func_end MOD04_021E0C98

	arm_func_start MOD04_021E0DB0
MOD04_021E0DB0: ; 0x021E0DB0
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #4
	addls pc, pc, r4, lsl #2
	b _021E0E0C
_021E0DCC: ; jump table
	b _021E0E0C ; case 0
	b _021E0DE0 ; case 1
	b _021E0DEC ; case 2
	b _021E0DF8 ; case 3
	b _021E0E04 ; case 4
_021E0DE0:
	mov r0, #9
	mvn r2, #0
	b _021E0E0C
_021E0DEC:
	mov r0, #9
	mvn r2, #1
	b _021E0E0C
_021E0DF8:
	mov r0, #6
	mvn r2, #9
	b _021E0E0C
_021E0E04:
	mov r0, #6
	mvn r2, #0x13
_021E0E0C:
	ldr r1, _021E0E20 ; =0xFFFF11B8
	add r1, r2, r1
	bl MOD04_021E0EAC
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E0E20: .word 0xFFFF11B8
	arm_func_end MOD04_021E0DB0

	arm_func_start MOD04_021E0E24
MOD04_021E0E24: ; 0x021E0E24
	ldr r0, _021E0E44 ; =UNK04_022106C8
	ldr r2, [r0]
	cmp r2, #0
	movne r1, #0
	strne r1, [r2, #4]
	ldrne r0, [r0]
	strne r1, [r0, #0x30]
	bx lr
	.align 2, 0
_021E0E44: .word UNK04_022106C8
	arm_func_end MOD04_021E0E24

	arm_func_start MOD04_021E0E48
MOD04_021E0E48: ; 0x021E0E48
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021E0EA8 ; =UNK04_022106C8
	ldr r0, [r0]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	beq _021E0E94
	bl MOD04_021D9974
	bl MOD04_021D991C
	ldr r1, _021E0EA8 ; =UNK04_022106C8
	mov r0, #0
	ldr r1, [r1]
	mov r2, r0
	ldr r1, [r1, #0x24]
	bl MOD04_021DD904
	ldr r0, _021E0EA8 ; =UNK04_022106C8
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x24]
_021E0E94:
	ldr r0, _021E0EA8 ; =UNK04_022106C8
	mov r1, #0
	str r1, [r0]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E0EA8: .word UNK04_022106C8
	arm_func_end MOD04_021E0E48

	arm_func_start MOD04_021E0EAC
MOD04_021E0EAC: ; 0x021E0EAC
	stmdb sp!, {r4, lr}
	ldr r2, _021E0EFC ; =UNK04_022106C8
	mov r4, r0
	ldr r2, [r2]
	cmp r2, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #0
	ldmeqia sp!, {r4, pc}
	bl MOD04_021DD6B0
	ldr r0, _021E0EFC ; =UNK04_022106C8
	ldr r0, [r0]
	ldr r3, [r0, #0x14]
	cmp r3, #0
	beq _021E0EF4
	ldr r2, [r0, #0x18]
	mov r0, r4
	mov r1, #0
	blx r3
_021E0EF4:
	bl MOD04_021E0E24
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E0EFC: .word UNK04_022106C8
	arm_func_end MOD04_021E0EAC

	arm_func_start MOD04_021E0F00
MOD04_021E0F00: ; 0x021E0F00
	ldr r0, _021E0F18 ; =UNK04_022106C8
	ldr r0, [r0]
	cmp r0, #0
	ldrne r0, [r0, #0x1c]
	moveq r0, #0
	bx lr
	.align 2, 0
_021E0F18: .word UNK04_022106C8
	arm_func_end MOD04_021E0F00

	arm_func_start MOD04_021E0F1C
MOD04_021E0F1C: ; 0x021E0F1C
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021E1024 ; =UNK04_022106C8
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl MOD04_021DD6D4
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E1024 ; =UNK04_022106C8
	ldr r1, [r0]
	ldr r0, [r1, #4]
	cmp r0, #5
	addls pc, pc, r0, lsl #2
	b _021E101C
_021E0F60: ; jump table
	b _021E101C ; case 0
	b _021E0F78 ; case 1
	b _021E0F84 ; case 2
	b _021E0F84 ; case 3
	b _021E0F84 ; case 4
	b _021E101C ; case 5
_021E0F78:
	bl MOD04_021E07E4
	add sp, sp, #4
	ldmfd sp!, {pc}
_021E0F84:
	ldr r0, [r1]
	cmp r0, #0
	beq _021E0FA0
	ldr r1, [r0]
	cmp r1, #0
	beq _021E0FA0
	bl MOD04_021F0F18
_021E0FA0:
	ldr r0, _021E1024 ; =UNK04_022106C8
	ldr r0, [r0]
	ldr r0, [r0, #0x30]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl OS_GetTick
	ldr r3, _021E1024 ; =UNK04_022106C8
	ldr r2, _021E1028 ; =0x000082EA
	ldr ip, [r3]
	mov r3, #0
	ldr lr, [ip, #0x34]
	ldr ip, [ip, #0x38]
	subs lr, r0, lr
	sbc r0, r1, ip
	mov r1, r0, lsl #6
	orr r1, r1, lr, lsr #26
	mov r0, lr, lsl #6
	bl _ll_udiv
	ldr r2, _021E102C ; =0x0000EA60
	cmp r1, #0
	cmpeq r0, r2
	addls sp, sp, #4
	ldmlsia sp!, {pc}
	ldr r1, _021E1030 ; =0xFFFF1172
	mov r0, #6
	bl MOD04_021E0EAC
	ldr r0, _021E1024 ; =UNK04_022106C8
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #0x30]
_021E101C:
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E1024: .word UNK04_022106C8
_021E1028: .word 0x000082EA
_021E102C: .word 0x0000EA60
_021E1030: .word 0xFFFF1172
	arm_func_end MOD04_021E0F1C

	arm_func_start MOD04_021E1034
MOD04_021E1034: ; 0x021E1034
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021E106C ; =MOD04_021E0C80
	mov r1, #0
	bl MOD04_021E0A00
	ldr r0, _021E1070 ; =UNK04_022106C8
	mov r3, #1
	ldr r2, [r0]
	mov r1, #0
	str r3, [r2, #4]
	ldr r0, [r0]
	str r1, [r0, #0x30]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E106C: .word MOD04_021E0C80
_021E1070: .word UNK04_022106C8
	arm_func_end MOD04_021E1034

	arm_func_start MOD04_021E1074
MOD04_021E1074: ; 0x021E1074
	stmdb sp!, {r4, r5, r6, lr}
	ldr ip, _021E10F4 ; =UNK04_022106C8
	mov r6, r1
	mov r5, r2
	mov r1, #0
	mov r2, #0x260
	mov r4, r3
	str r0, [ip]
	bl MI_CpuFill8
	ldr r0, _021E10F4 ; =UNK04_022106C8
	mov r2, #0
	ldr r1, [r0]
	ldr ip, [sp, #0x10]
	str r5, [r1]
	ldr r1, [r0]
	ldr r5, [sp, #0x14]
	str r2, [r1, #4]
	ldr r1, [r0]
	ldr r3, [sp, #0x18]
	str r4, [r1, #8]
	ldr r1, [r0]
	ldr r2, [sp, #0x1c]
	str ip, [r1, #0xc]
	ldr r1, [r0]
	str r5, [r1, #0x10]
	ldr r1, [r0]
	str r3, [r1, #0x14]
	ldr r1, [r0]
	str r2, [r1, #0x18]
	ldr r0, [r0]
	str r6, [r0, #0x1c]
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E10F4: .word UNK04_022106C8
	arm_func_end MOD04_021E1074

	.section .data

	.global UNK04_0220D34C
UNK04_0220D34C: ; 0x0220D34C
	.byte 0x00, 0x00, 0x00, 0x00

	.section .bss

	.global UNK04_022106C4
UNK04_022106C4: ; 0x022106C4
	.space 0x4

	.global UNK04_022106C8
UNK04_022106C8: ; 0x022106C8
	.space 0x4

	.global UNK04_022106CC
UNK04_022106CC: ; 0x022106CC
	.space 0x4
