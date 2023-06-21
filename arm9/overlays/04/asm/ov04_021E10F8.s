	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start ov04_021E10F8
ov04_021E10F8: ; 0x021E10F8
	ldr r0, _021E1108 ; =ov04_022106D0
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bx lr
	.align 2, 0
_021E1108: .word ov04_022106D0
	arm_func_end ov04_021E10F8

	arm_func_start ov04_021E110C
ov04_021E110C: ; 0x021E110C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x24
	mov sl, r1
	ldr r0, [sl]
	mov r8, #0
	cmp r0, #0
	mov r0, #1
	str r0, [sp]
	addne sp, sp, #0x24
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r4, _021E12B4 ; =ov04_022106D0
	mov sb, r8
	ldr r2, [r4]
	ldr r1, [r2, #0x14]
	cmp r1, #0
	ble _021E1274
	mov r7, r8
	str r0, [sp, #4]
	mov fp, r8
	mov r5, r0
_021E115C:
	ldr r0, [r2, #0x18]
	add r0, r0, r7
	bl DWC_GetFriendDataType
	cmp r0, #1
	bne _021E11C8
	bl ov04_021E0F00
	ldr r1, [r4]
	add r2, sp, #8
	ldr r1, [r1, #0x18]
	add r1, r1, r7
	bl DWC_LoginIdToUserName
	add r0, sp, #8
	add r1, sl, #0x8e
	bl strcmp
	cmp r0, #0
	bne _021E125C
	ldr r0, [r4]
	ldr r1, [sl, #4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_SetGsProfileId
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWCi_SetBuddyFriendData
	mov r8, r5
	b _021E125C
_021E11C8:
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_GetFriendDataType
	cmp r0, #3
	beq _021E11F8
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_GetFriendDataType
	cmp r0, #2
	bne _021E125C
_021E11F8:
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_IsBuddyFriendData
	cmp r0, #1
	streq fp, [sp]
	beq _021E125C
	ldr r6, [sl, #4]
	bl ov04_021E0F00
	ldr r1, [r4]
	ldr r1, [r1, #0x18]
	add r1, r1, r7
	bl DWC_GetGsProfileId
	cmp r6, r0
	bne _021E125C
	ldr r0, [r4]
	mov r1, r6
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_SetGsProfileId
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWCi_SetBuddyFriendData
	ldr r8, [sp, #4]
_021E125C:
	ldr r2, [r4]
	add sb, sb, #1
	ldr r1, [r2, #0x14]
	add r7, r7, #0xc
	cmp sb, r1
	blt _021E115C
_021E1274:
	cmp r8, #0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, [r2, #0x18]
	ldr r2, [sl, #4]
	bl ov04_021E17F0
	ldr r1, [sp]
	cmp r1, #0
	beq _021E129C
	bl ov04_021E1DA4
_021E129C:
	ldr r0, _021E12B4 ; =ov04_022106D0
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x1d]
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E12B4: .word ov04_022106D0
	arm_func_end ov04_021E110C

	arm_func_start ov04_021E12B8
ov04_021E12B8: ; 0x021E12B8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x1c
	mov sb, r1
	ldr r1, [sb]
	mov sl, r0
	cmp r1, #0
	mov fp, #0
	addne sp, sp, #0x1c
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r4, _021E1410 ; =ov04_022106D0
	mov r8, fp
	ldr r1, [r4]
	ldr r0, [r1, #0x14]
	cmp r0, #0
	ble _021E13E4
	add r0, sb, #0x8e
	mov r7, fp
	mov r5, #1
	str r0, [sp]
_021E1304:
	ldr r0, [r1, #0x18]
	add r0, r0, r7
	bl DWC_GetFriendDataType
	cmp r0, #1
	bne _021E136C
	bl ov04_021E0F00
	ldr r1, [r4]
	add r2, sp, #4
	ldr r1, [r1, #0x18]
	add r1, r1, r7
	bl DWC_LoginIdToUserName
	ldr r1, [sp]
	add r0, sp, #4
	bl strcmp
	cmp r0, #0
	bne _021E13CC
	ldr r1, [sb, #4]
	mov r0, sl
	bl ov04_021F0944
	ldr r0, [r4]
	ldr r1, [sb, #4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_SetGsProfileId
	mov fp, r5
	b _021E13CC
_021E136C:
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_GetFriendDataType
	cmp r0, #3
	beq _021E139C
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	add r0, r0, r7
	bl DWC_GetFriendDataType
	cmp r0, #2
	bne _021E13CC
_021E139C:
	ldr r6, [sb, #4]
	bl ov04_021E0F00
	ldr r1, [r4]
	ldr r1, [r1, #0x18]
	add r1, r1, r7
	bl DWC_GetGsProfileId
	cmp r6, r0
	bne _021E13CC
	mov r0, sl
	mov r1, r6
	bl ov04_021F0944
	mov fp, r5
_021E13CC:
	ldr r1, [r4]
	add r8, r8, #1
	ldr r0, [r1, #0x14]
	add r7, r7, #0xc
	cmp r8, r0
	blt _021E1304
_021E13E4:
	cmp fp, #0
	beq _021E13FC
	ldr r0, [sb, #4]
	bl ov04_021E17BC
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E13FC:
	ldr r1, [sb, #4]
	mov r0, sl
	bl ov04_021F0864
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E1410: .word ov04_022106D0
	arm_func_end ov04_021E12B8

	arm_func_start ov04_021E1414
ov04_021E1414: ; 0x021E1414
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #4
	mov sb, r1
	ldr r1, [sb]
	mov sl, r0
	mov r8, r2
	cmp r1, #0
	bne _021E15FC
	ldr r0, [sb, #4]
	cmp r0, #0
	beq _021E15FC
	mov r0, #0xc
	ldr r1, _021E1670 ; =ov04_022106D0
	mul r6, r8, r0
	ldr r0, [r1]
	ldr r0, [r0, #0x18]
	add r0, r0, r6
	bl DWC_GetFriendDataType
	cmp r0, #0
	beq _021E15FC
	ldr r7, _021E1670 ; =ov04_022106D0
	ldr r1, [r7]
	ldr r0, [r1]
	cmp r0, #1
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	mov r0, #1
	strb r0, [r1, #0x1d]
	ldr r0, [sb, #4]
	mov r5, #0
	cmp r0, #0
	ble _021E14FC
	mov r4, r5
_021E1498:
	ldr r0, [r7]
	ldr r1, [sb, #0xc]
	ldr r0, [r0, #0x18]
	ldr r2, [r1, r4]
	mov r1, r8
	bl ov04_021E1900
	cmp r0, #0
	beq _021E14E8
	ldr r0, _021E1670 ; =ov04_022106D0
	mov r2, #1
	ldr r4, [r0]
	ldr r1, _021E1674 ; =0x00000601
	ldrb r3, [r4, #0x1c]
	add sp, sp, #4
	add r3, r3, #1
	strb r3, [r4, #0x1c]
	ldr r0, [r0]
	strb r2, [r0, #0x1e]
	str r1, [sb, #8]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E14E8:
	ldr r0, [sb, #4]
	add r5, r5, #1
	cmp r5, r0
	add r4, r4, #0xac
	blt _021E1498
_021E14FC:
	cmp r0, #0
	mov r5, #0
	ble _021E15C4
	mov r7, r5
	add fp, sp, #0
	mvn r4, #0
_021E1514:
	ldr r1, [sb, #0xc]
	mov r0, sl
	ldr r1, [r1, r7]
	mov r2, fp
	bl ov04_021F0664
	bl ov04_021E1678
	ldr r0, [sp]
	cmp r0, r4
	bne _021E1548
	ldr r0, [sb, #0xc]
	ldr r0, [r0, r7]
	bl ov04_021E17BC
	b _021E15B0
_021E1548:
	ldr r0, _021E1670 ; =ov04_022106D0
	ldr r1, [sb, #0xc]
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r0, [r0, #0x18]
	add r0, r0, r6
	bl DWC_SetGsProfileId
	ldr r0, _021E1670 ; =ov04_022106D0
	ldr r0, [r0]
	ldr r0, [r0, #0x18]
	add r0, r0, r6
	bl DWCi_SetBuddyFriendData
	mov r0, r8
	bl ov04_021E1DA4
	ldr r0, _021E1670 ; =ov04_022106D0
	mov r2, #1
	ldr r4, [r0]
	ldr r1, _021E1674 ; =0x00000601
	ldrb r3, [r4, #0x1c]
	add sp, sp, #4
	add r3, r3, #1
	strb r3, [r4, #0x1c]
	ldr r0, [r0]
	strb r2, [r0, #0x1e]
	str r1, [sb, #8]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E15B0:
	ldr r0, [sb, #4]
	add r5, r5, #1
	cmp r5, r0
	add r7, r7, #0xac
	blt _021E1514
_021E15C4:
	ldr r0, [sb, #8]
	cmp r0, #0x600
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, _021E1670 ; =ov04_022106D0
	mov r1, #1
	ldr r3, [r0]
	add sp, sp, #4
	ldrb r2, [r3, #0x1c]
	add r2, r2, #1
	strb r2, [r3, #0x1c]
	ldr r0, [r0]
	strb r1, [r0, #0x1e]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E15FC:
	ldr r0, [sb]
	cmp r0, #0
	beq _021E1618
	bl ov04_021E1678
	add sp, sp, #4
	cmp r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E1618:
	ldr r0, _021E1670 ; =ov04_022106D0
	ldr r1, [r0]
	ldr r0, [r1]
	cmp r0, #1
	beq _021E1648
	ldr r1, [r1, #0x18]
	mov r0, #0xc
	mla r0, r8, r0, r1
	bl DWC_GetFriendDataType
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E1648:
	ldr r0, _021E1670 ; =ov04_022106D0
	mov r1, #1
	ldr r3, [r0]
	ldrb r2, [r3, #0x1c]
	add r2, r2, #1
	strb r2, [r3, #0x1c]
	ldr r0, [r0]
	strb r1, [r0, #0x1e]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E1670: .word ov04_022106D0
_021E1674: .word 0x00000601
	arm_func_end ov04_021E1414

	arm_func_start ov04_021E1678
ov04_021E1678: ; 0x021E1678
	stmdb sp!, {r4, lr}
	movs r4, r0
	moveq r0, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #4
	addls pc, pc, r4, lsl #2
	b _021E16D4
_021E1694: ; jump table
	b _021E16D4 ; case 0
	b _021E16A8 ; case 1
	b _021E16B4 ; case 2
	b _021E16C0 ; case 3
	b _021E16CC ; case 4
_021E16A8:
	mov r0, #9
	mvn r2, #0
	b _021E16D4
_021E16B4:
	mov r0, #9
	mvn r2, #1
	b _021E16D4
_021E16C0:
	mov r0, #6
	mvn r2, #9
	b _021E16D4
_021E16CC:
	mov r0, #6
	mvn r2, #0x13
_021E16D4:
	ldr r1, _021E16E8 ; =0xFFFEEAA8
	add r1, r2, r1
	bl ov04_021E2114
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E16E8: .word 0xFFFEEAA8
	arm_func_end ov04_021E1678

	arm_func_start ov04_021E16EC
ov04_021E16EC: ; 0x021E16EC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r2, _021E17B8 ; =ov04_022106D0
	mov r3, #0
	ldr r2, [r2]
	mov r5, r0
	mov r4, r1
	str r3, [sp]
	cmp r2, #0
	beq _021E1720
	bl ov04_021E05FC
	cmp r0, #0
	bne _021E172C
_021E1720:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E172C:
	bl ov04_021E0F00
	mov r1, r5
	bl DWC_GetGsProfileId
	mov r5, r0
	cmp r5, #0
	ble _021E176C
	ldr r0, _021E17B8 ; =ov04_022106D0
	add r2, sp, #0
	ldr r0, [r0]
	mov r1, r5
	ldr r0, [r0, #4]
	bl ov04_021F0664
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
_021E176C:
	cmp r5, #0
	ble _021E1784
	ldr r1, [sp]
	mvn r0, #0
	cmp r1, r0
	bne _021E1790
_021E1784:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E1790:
	ldr r0, _021E17B8 ; =ov04_022106D0
	mov r2, r4
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl ov04_021F06E4
	cmp r0, #0
	movne r0, #0
	moveq r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E17B8: .word ov04_022106D0
	arm_func_end ov04_021E16EC

	arm_func_start ov04_021E17BC
ov04_021E17BC: ; 0x021E17BC
	stmdb sp!, {r4, lr}
	ldr r2, _021E17E8 ; =ov04_022106D0
	mov r1, r0
	ldr r0, [r2]
	ldr r2, _021E17EC ; =ov04_0220D350
	ldr r0, [r0, #4]
	bl ov04_021F09B0
	mov r4, r0
	bl ov04_021E1678
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E17E8: .word ov04_022106D0
_021E17EC: .word ov04_0220D350
	arm_func_end ov04_021E17BC

	arm_func_start ov04_021E17F0
ov04_021E17F0: ; 0x021E17F0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0xc
	mov sl, r1
	mov fp, r0
	mvn r0, #0
	str r2, [sp]
	cmp sl, #0
	str r0, [sp, #4]
	mov r8, #0
	ble _021E18F0
	mov r6, fp
	mov r5, fp
	mov r0, #1
	str r0, [sp, #8]
_021E1828:
	mov r0, r8
	bl ov04_021E1F84
	movs sb, r0
	beq _021E18DC
	ldr r0, [sp]
	add r7, r8, #1
	cmp sb, r0
	streq r8, [sp, #4]
	cmp r7, sl
	bge _021E18DC
	mov r0, #0xc
	mla r4, r7, r0, fp
_021E1858:
	mov r0, r7
	bl ov04_021E1F84
	cmp sb, r0
	bne _021E18CC
	mov r0, r6
	bl DWC_GetFriendDataType
	cmp r0, #2
	bne _021E1894
	mov r0, r4
	bl DWC_GetFriendDataType
	cmp r0, #3
	bne _021E1894
	mov r0, r5
	mov r1, sb
	bl DWC_SetGsProfileId
_021E1894:
	mov r0, r4
	bl DWC_IsBuddyFriendData
	cmp r0, #0
	beq _021E18AC
	mov r0, r5
	bl DWCi_SetBuddyFriendData
_021E18AC:
	mov r0, fp
	mov r1, r7
	mov r2, r8
	bl ov04_021E19B8
	ldr r0, _021E18FC ; =ov04_022106D0
	ldr r1, [r0]
	ldr r0, [sp, #8]
	strb r0, [r1, #0x1d]
_021E18CC:
	add r7, r7, #1
	cmp r7, sl
	add r4, r4, #0xc
	blt _021E1858
_021E18DC:
	add r8, r8, #1
	cmp r8, sl
	add r6, r6, #0xc
	add r5, r5, #0xc
	blt _021E1828
_021E18F0:
	ldr r0, [sp, #4]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E18FC: .word ov04_022106D0
	arm_func_end ov04_021E17F0

	arm_func_start ov04_021E1900
ov04_021E1900: ; 0x021E1900
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r6, r1
	mov r7, r0
	mov r5, r2
	cmp r6, #0
	mov r4, #0
	ble _021E19A8
_021E1920:
	mov r0, r4
	bl ov04_021E1F84
	cmp r0, #0
	beq _021E199C
	cmp r0, r5
	bne _021E199C
	mov r0, #0xc
	mla r0, r6, r0, r7
	bl DWC_IsBuddyFriendData
	cmp r0, #0
	beq _021E1974
	mov r0, #0xc
	mla r0, r4, r0, r7
	bl DWC_IsBuddyFriendData
	cmp r0, #0
	bne _021E1974
	mov r0, r7
	mov r1, r4
	mov r2, r6
	bl ov04_021E19B8
	b _021E1984
_021E1974:
	mov r0, r7
	mov r1, r6
	mov r2, r4
	bl ov04_021E19B8
_021E1984:
	ldr r1, _021E19B4 ; =ov04_022106D0
	mov r0, #1
	ldr r1, [r1]
	add sp, sp, #4
	strb r0, [r1, #0x1d]
	ldmia sp!, {r4, r5, r6, r7, pc}
_021E199C:
	add r4, r4, #1
	cmp r4, r6
	blt _021E1920
_021E19A8:
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, pc}
	.align 2, 0
_021E19B4: .word ov04_022106D0
	arm_func_end ov04_021E1900

	arm_func_start ov04_021E19B8
ov04_021E19B8: ; 0x021E19B8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r3, _021E1A1C ; =ov04_022106D0
	mov r5, r1
	ldr r1, [r3]
	mov r4, r2
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	mov r2, #0xc
	mla r0, r5, r2, r0
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _021E1A1C ; =ov04_022106D0
	ldr r0, [r0]
	ldr r3, [r0, #0x3c]
	cmp r3, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r2, [r0, #0x40]
	mov r0, r5
	mov r1, r4
	blx r3
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E1A1C: .word ov04_022106D0
	arm_func_end ov04_021E19B8

	arm_func_start ov04_021E1A20
ov04_021E1A20: ; 0x021E1A20
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r1, _021E1A5C ; =ov04_022106D0
	mov r0, #0
	ldr r3, [r1]
	ldrb r1, [r3, #0x1d]
	ldr r2, [r3, #0x30]
	ldr r3, [r3, #0x2c]
	blx r3
	ldr r0, _021E1A5C ; =ov04_022106D0
	mov r1, #2
	ldr r0, [r0]
	str r1, [r0]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E1A5C: .word ov04_022106D0
	arm_func_end ov04_021E1A20

	arm_func_start ov04_021E1A60
ov04_021E1A60: ; 0x021E1A60
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x24c
	ldr r2, _021E1CC4 ; =ov04_022106D0
	mov r6, r0
	ldr r2, [r2]
	mov r5, r1
	ldrb r0, [r2, #0x1e]
	cmp r0, #0
	bne _021E1B8C
	ldr r0, [r2, #4]
	add r1, sp, #0x18
	bl ov04_021F0828
	bl ov04_021E1678
	ldr r0, [sp, #0x18]
	mov fp, #0
	str fp, [sp, #0x1c]
	cmp r0, #0
	ble _021E1B7C
	ldr r8, _021E1CC4 ; =ov04_022106D0
	mov sb, #1
	mov r7, #0xc
_021E1AB4:
	ldr r0, [r8]
	ldr r1, [sp, #0x1c]
	ldr r0, [r0, #4]
	add r2, sp, #0x38
	bl ov04_021F06E4
	bl ov04_021E1678
	mov r4, fp
	cmp r5, #0
	ble _021E1B30
_021E1AD8:
	mov r0, r4
	bl ov04_021E1F84
	ldr r1, [sp, #0x38]
	cmp r1, r0
	bne _021E1B24
	mul sl, r4, r7
	add r0, r6, sl
	bl DWC_IsBuddyFriendData
	cmp r0, #0
	bne _021E1B30
	add sl, r6, sl
	ldr r1, [sp, #0x38]
	mov r0, sl
	bl DWC_SetGsProfileId
	mov r0, sl
	bl DWCi_SetBuddyFriendData
	ldr r0, [r8]
	strb sb, [r0, #0x1d]
	b _021E1B30
_021E1B24:
	add r4, r4, #1
	cmp r4, r5
	blt _021E1AD8
_021E1B30:
	cmp r4, r5
	bne _021E1B64
	ldr r0, [r8]
	ldr r1, [sp, #0x38]
	ldr r0, [r0, #4]
	bl ov04_021F0580
	bl ov04_021E1678
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	sub r1, r1, #1
	sub r0, r0, #1
	str r1, [sp, #0x18]
	str r0, [sp, #0x1c]
_021E1B64:
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r1, r1, #1
	str r1, [sp, #0x1c]
	cmp r1, r0
	blt _021E1AB4
_021E1B7C:
	ldr r0, _021E1CC4 ; =ov04_022106D0
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x1e]
_021E1B8C:
	ldr sl, _021E1CC4 ; =ov04_022106D0
	ldr r0, [sl]
	ldrb r0, [r0, #0x1c]
	cmp r0, r5
	addge sp, sp, #0x24c
	ldmgeia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	add r4, sp, #0x1c
	mov r8, #0xc
	mvn sb, #0
_021E1BB0:
	bl ov04_021E1F84
	movs r7, r0
	beq _021E1C08
	ldr r1, [sl]
	mov r0, r6
	ldrb r1, [r1, #0x1c]
	mov r2, r7
	bl ov04_021E1900
	cmp r0, #0
	bne _021E1C9C
	ldr r0, [sl]
	mov r1, r7
	ldr r0, [r0, #4]
	mov r2, r4
	bl ov04_021F0664
	bl ov04_021E1678
	ldr r0, [sp, #0x1c]
	cmp r0, sb
	bne _021E1C9C
	mov r0, r7
	bl ov04_021E17BC
	b _021E1C9C
_021E1C08:
	bl ov04_021E0F00
	ldr r1, [sl]
	ldrb r2, [r1, #0x1c]
	mla r1, r2, r8, r6
	bl DWC_GetGsProfileId
	cmp r0, sb
	bne _021E1C9C
	bl ov04_021E0F00
	ldr r2, _021E1CC4 ; =ov04_022106D0
	mov r1, #0xc
	ldr r3, [r2]
	add r2, sp, #0x20
	ldrb r3, [r3, #0x1c]
	mla r1, r3, r1, r6
	bl DWC_LoginIdToUserName
	ldr r0, _021E1CC4 ; =ov04_022106D0
	mov r1, #0
	ldr r4, [r0]
	add r2, sp, #0x20
	str r1, [sp]
	str r2, [sp, #4]
	str r1, [sp, #8]
	ldr r0, _021E1CC8 ; =ov04_021E1414
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldrb r0, [r4, #0x1c]
	mov r2, r1
	mov r3, r1
	str r0, [sp, #0x14]
	ldr r0, [r4, #4]
	bl ov04_021F0C84
	ldr r0, _021E1CC4 ; =ov04_022106D0
	mov r1, #2
	ldr r0, [r0]
	add sp, sp, #0x24c
	strb r1, [r0, #0x1e]
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
_021E1C9C:
	ldr r1, [sl]
	ldrb r0, [r1, #0x1c]
	add r0, r0, #1
	strb r0, [r1, #0x1c]
	ldr r0, [sl]
	ldrb r0, [r0, #0x1c]
	cmp r0, r5
	blt _021E1BB0
	add sp, sp, #0x24c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021E1CC4: .word ov04_022106D0
_021E1CC8: .word ov04_021E1414
	arm_func_end ov04_021E1A60

	arm_func_start ov04_021E1CCC
ov04_021E1CCC: ; 0x021E1CCC
	ldr r0, _021E1CF8 ; =ov04_022106D0
	ldr r1, [r0]
	cmp r1, #0
	bxeq lr
	mov r2, #0
	str r2, [r1]
	ldr r1, [r0]
	strb r2, [r1, #0x1e]
	ldr r0, [r0]
	strb r2, [r0, #0x1f]
	bx lr
	.align 2, 0
_021E1CF8: .word ov04_022106D0
	arm_func_end ov04_021E1CCC

	arm_func_start ov04_021E1CFC
ov04_021E1CFC: ; 0x021E1CFC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _021E1D88 ; =ov04_022106D0
	mov r5, #0
	ldr r4, [r0]
	bl OS_GetTick
	ldr r3, [r4, #0xc]
	ldr r2, [r4, #0x10]
	subs r3, r0, r3
	sbc r0, r1, r2
	mov r1, r0, lsl #6
	ldr r2, _021E1D8C ; =0x000082EA
	orr r1, r1, r3, lsr #26
	mov r0, r3, lsl #6
	mov r3, r5
	bl _ll_udiv
	cmp r1, #0
	cmpeq r0, #0x12c
	blo _021E1D7C
	ldr r1, [r4, #8]
	ldr r0, _021E1D88 ; =ov04_022106D0
	add r1, r1, #1
	str r1, [r4, #8]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl ov04_021F0F18
	mov r5, r0
	bl OS_GetTick
	ldr r2, _021E1D88 ; =ov04_022106D0
	ldr r2, [r2]
	str r0, [r2, #0xc]
	str r1, [r2, #0x10]
_021E1D7C:
	mov r0, r5
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E1D88: .word ov04_022106D0
_021E1D8C: .word 0x000082EA
	arm_func_end ov04_021E1CFC

	arm_func_start ov04_021E1D90
ov04_021E1D90: ; 0x021E1D90
	ldr r0, _021E1DA0 ; =ov04_022106D0
	mov r1, #0
	str r1, [r0]
	bx lr
	.align 2, 0
_021E1DA0: .word ov04_022106D0
	arm_func_end ov04_021E1D90

	arm_func_start ov04_021E1DA4
ov04_021E1DA4: ; 0x021E1DA4
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x210
	ldr r1, _021E1E2C ; =ov04_022106D0
	mov r4, r0
	ldr r3, [r1]
	ldr r2, [r3, #0x44]
	cmp r2, #0
	beq _021E1DD8
	ldr r1, [r3]
	cmp r1, #1
	beq _021E1DD8
	ldr r1, [r3, #0x48]
	blx r2
_021E1DD8:
	ldr r0, _021E1E2C ; =ov04_022106D0
	ldr r1, [r0]
	ldr r0, [r1, #0x34]
	cmp r0, #0
	addeq sp, sp, #0x210
	ldmeqia sp!, {r4, pc}
	ldr r1, [r1, #0x18]
	mov r0, #0xc
	mla r0, r4, r0, r1
	add r1, sp, #0x108
	bl ov04_021E26B8
	ldr r2, _021E1E2C ; =ov04_022106D0
	mov r1, r0
	ldr r0, [r2]
	add r2, sp, #0x108
	ldr r3, [r0, #0x38]
	ldr ip, [r0, #0x34]
	mov r0, r4
	blx ip
	add sp, sp, #0x210
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E1E2C: .word ov04_022106D0
	arm_func_end ov04_021E1DA4

	arm_func_start ov04_021E1E30
ov04_021E1E30: ; 0x021E1E30
	stmdb sp!, {r4, r5, r6, lr}
	ldr r3, _021E1ED0 ; =ov04_022106D0
	mov r6, r0
	ldr r0, [r3]
	mov r5, r1
	mov r4, r2
	cmp r0, #0
	beq _021E1E5C
	bl ov04_021E05FC
	cmp r0, #0
	bne _021E1E64
_021E1E5C:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E1E64:
	mvn r0, #0
	cmp r6, r0
	ldreq r0, _021E1ED0 ; =ov04_022106D0
	ldreq r0, [r0]
	ldreq r0, [r0, #4]
	ldreq r0, [r0]
	ldreq r6, [r0, #0x214]
	cmp r5, #0
	ldreq r0, _021E1ED0 ; =ov04_022106D0
	mov r1, r6
	ldreq r0, [r0]
	ldreq r0, [r0, #4]
	ldreq r0, [r0]
	addeq r5, r0, #0x218
	cmp r4, #0
	ldreq r0, _021E1ED0 ; =ov04_022106D0
	mov r2, r5
	ldreq r0, [r0]
	ldreq r0, [r0, #4]
	ldreq r0, [r0]
	addeq r4, r0, #0x318
	ldr r0, _021E1ED0 ; =ov04_022106D0
	mov r3, r4
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl ov04_021F034C
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E1ED0: .word ov04_022106D0
	arm_func_end ov04_021E1E30

	arm_func_start ov04_021E1ED4
ov04_021E1ED4: ; 0x021E1ED4
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021E1F14 ; =ov04_022106D0
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	mov r0, #0
	str r0, [r1, #8]
	bl OS_GetTick
	ldr r2, _021E1F14 ; =ov04_022106D0
	ldr r2, [r2]
	str r0, [r2, #0xc]
	str r1, [r2, #0x10]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E1F14: .word ov04_022106D0
	arm_func_end ov04_021E1ED4

	arm_func_start ov04_021E1F18
ov04_021E1F18: ; 0x021E1F18
	stmdb sp!, {r4, r5, r6, lr}
	ldr r4, _021E1F80 ; =ov04_022106D0
	mov r6, r0
	ldr r0, [r4]
	cmp r0, #0
	beq _021E1F38
	cmp r6, #0
	bne _021E1F40
_021E1F38:
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, pc}
_021E1F40:
	ldr r0, [r0, #0x14]
	mov r5, #0
	cmp r0, #0
	ble _021E1F78
_021E1F50:
	mov r0, r5
	bl ov04_021E1F84
	cmp r6, r0
	moveq r0, r5
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, [r4]
	add r5, r5, #1
	ldr r0, [r0, #0x14]
	cmp r5, r0
	blt _021E1F50
_021E1F78:
	mvn r0, #0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E1F80: .word ov04_022106D0
	arm_func_end ov04_021E1F18

	arm_func_start ov04_021E1F84
ov04_021E1F84: ; 0x021E1F84
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _021E1FE0 ; =ov04_022106D0
	mov r5, r0
	ldr r0, [r1]
	ldr r4, [r0, #0x18]
	cmp r4, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	bl ov04_021E0F00
	mov r1, #0xc
	mla r1, r5, r1, r4
	bl DWC_GetGsProfileId
	cmp r0, #0
	beq _021E1FD4
	mvn r1, #0
	cmp r0, r1
	addne sp, sp, #4
	ldmneia sp!, {r4, r5, pc}
_021E1FD4:
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E1FE0: .word ov04_022106D0
	arm_func_end ov04_021E1F84

	arm_func_start ov04_021E1FE4
ov04_021E1FE4: ; 0x021E1FE4
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x210
	ldr r2, _021E2064 ; =ov04_022106D0
	mov r6, r0
	ldr r0, [r2]
	mov r5, r1
	ldr r0, [r0, #0x34]
	cmp r0, #0
	addeq sp, sp, #0x210
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r0, [r5]
	bl ov04_021E1F18
	mov r4, r0
	mvn r0, #0
	cmp r4, r0
	addeq sp, sp, #0x210
	ldmeqia sp!, {r4, r5, r6, pc}
	ldr r1, [r5, #8]
	add r2, sp, #0
	mov r0, r6
	bl ov04_021F06E4
	ldr r0, _021E2064 ; =ov04_022106D0
	ldr r1, [sp, #4]
	ldr r0, [r0]
	add r2, sp, #0x108
	ldr r3, [r0, #0x38]
	ldr ip, [r0, #0x34]
	mov r0, r4
	and r1, r1, #0xff
	blx ip
	add sp, sp, #0x210
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E2064: .word ov04_022106D0
	arm_func_end ov04_021E1FE4

	arm_func_start ov04_021E2068
ov04_021E2068: ; 0x021E2068
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	mov r4, r1
	mov r5, r0
	ldr r0, [r4, #8]
	ldr r1, _021E20C0 ; =ov04_0220D354
	bl strcmp
	cmp r0, #0
	addne sp, sp, #0xc
	movne r0, #0
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021E20C4 ; =ov04_021E110C
	mov r2, #0
	str r0, [sp]
	str r2, [sp, #4]
	ldr r1, [r4]
	mov r0, r5
	mov r3, r2
	bl ov04_021F0B9C
	mov r0, #1
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E20C0: .word ov04_0220D354
_021E20C4: .word ov04_021E110C
	arm_func_end ov04_021E2068

	arm_func_start ov04_021E20C8
ov04_021E20C8: ; 0x021E20C8
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r2, _021E210C ; =ov04_022106D0
	ldr r2, [r2]
	ldr r2, [r2, #0x18]
	cmp r2, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {pc}
	ldr r3, _021E2110 ; =ov04_021E12B8
	mov r2, #0
	str r3, [sp]
	str r2, [sp, #4]
	ldr r1, [r1]
	mov r3, r2
	bl ov04_021F0B9C
	add sp, sp, #0xc
	ldmfd sp!, {pc}
	.align 2, 0
_021E210C: .word ov04_022106D0
_021E2110: .word ov04_021E12B8
	arm_func_end ov04_021E20C8

	arm_func_start ov04_021E2114
ov04_021E2114: ; 0x021E2114
	stmdb sp!, {r4, lr}
	ldr r2, _021E2170 ; =ov04_022106D0
	mov r4, r0
	ldr r2, [r2]
	cmp r2, #0
	ldmeqia sp!, {r4, pc}
	cmp r4, #0
	ldmeqia sp!, {r4, pc}
	bl ov04_021DD6B0
	ldr r0, _021E2170 ; =ov04_022106D0
	ldr r3, [r0]
	ldr r0, [r3]
	cmp r0, #0
	beq _021E2168
	cmp r0, #2
	beq _021E2168
	ldrb r1, [r3, #0x1d]
	ldr r2, [r3, #0x30]
	ldr r3, [r3, #0x2c]
	mov r0, r4
	blx r3
_021E2168:
	bl ov04_021E1CCC
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E2170: .word ov04_022106D0
	arm_func_end ov04_021E2114

	arm_func_start ov04_021E2174
ov04_021E2174: ; 0x021E2174
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r0, _021E2224 ; =ov04_022106D0
	ldr r5, [sp, #0x10]
	ldr r1, [r0]
	ldr r4, [sp, #0x14]
	str r2, [r1, #0x2c]
	ldr r1, [r0]
	ldr lr, [sp, #0x18]
	str r3, [r1, #0x30]
	ldr r1, [r0]
	ldr ip, [sp, #0x1c]
	str r5, [r1, #0x34]
	ldr r1, [r0]
	mov r3, #0
	str r4, [r1, #0x38]
	ldr r1, [r0]
	mov r2, #1
	str lr, [r1, #0x3c]
	ldr r1, [r0]
	str ip, [r1, #0x40]
	ldr r1, [r0]
	strb r3, [r1, #0x1d]
	ldr r1, [r0]
	strb r3, [r1, #0x1e]
	ldr r1, [r0]
	strb r3, [r1, #0x1f]
	ldr r1, [r0]
	strb r3, [r1, #0x1c]
	ldr r1, [r0]
	str r2, [r1]
	ldr r1, [r0]
	ldr r0, [r1, #0x18]
	cmp r0, #0
	ldreqb r0, [r1, #0x1f]
	addeq r0, r0, #1
	streqb r0, [r1, #0x1f]
	ldr r0, _021E2224 ; =ov04_022106D0
	ldr r1, [r0]
	ldrb r0, [r1, #0x1f]
	add r0, r0, #1
	strb r0, [r1, #0x1f]
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E2224: .word ov04_022106D0
	arm_func_end ov04_021E2174

	arm_func_start ov04_021E2228
ov04_021E2228: ; 0x021E2228
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021E2348 ; =ov04_022106D0
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x18]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	bl ov04_021DD6D4
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	bl ov04_021E10F8
	cmp r0, #0
	bne _021E227C
	bl ov04_021FBE5C
	cmp r0, #0
	beq _021E2280
_021E227C:
	bl ov04_021FBD00
_021E2280:
	ldr r0, _021E2348 ; =ov04_022106D0
	ldr r0, [r0]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021E231C
	ldr r0, [r0]
	cmp r0, #0
	beq _021E231C
	bl ov04_021E1CFC
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {pc}
	ldr r0, _021E2348 ; =ov04_022106D0
	ldr r3, [r0]
	ldr r0, [r3, #0x18]
	cmp r0, #0
	beq _021E231C
	ldrb r2, [r3, #0x1e]
	cmp r2, #3
	beq _021E231C
	ldr r1, [r3, #8]
	cmp r1, #7
	bls _021E231C
	cmp r2, #1
	bhi _021E22EC
	ldr r1, [r3, #0x14]
	bl ov04_021E1A60
_021E22EC:
	ldr r0, _021E2348 ; =ov04_022106D0
	ldr r3, [r0]
	ldrb r2, [r3, #0x1c]
	ldr r1, [r3, #0x14]
	cmp r2, r1
	blt _021E231C
	mov r1, #3
	strb r1, [r3, #0x1e]
	ldr r1, [r0]
	ldrb r0, [r1, #0x1f]
	add r0, r0, #1
	strb r0, [r1, #0x1f]
_021E231C:
	ldr r0, _021E2348 ; =ov04_022106D0
	ldr r1, [r0]
	ldrb r0, [r1, #0x1f]
	cmp r0, #2
	addlo sp, sp, #4
	ldmloia sp!, {pc}
	mov r0, #0
	strb r0, [r1, #0x1f]
	bl ov04_021E1A20
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021E2348: .word ov04_022106D0
	arm_func_end ov04_021E2228

	arm_func_start ov04_021E234C
ov04_021E234C: ; 0x021E234C
	stmdb sp!, {r4, lr}
	ldr lr, _021E2428 ; =ov04_022106D0
	mov ip, #0
	str r0, [lr]
	str ip, [r0]
	ldr r4, [lr]
	ldr r0, [sp, #8]
	str r1, [r4, #4]
	ldr r1, [lr]
	str ip, [r1, #8]
	ldr r1, [lr]
	str ip, [r1, #0xc]
	str ip, [r1, #0x10]
	str r0, [r1, #0x14]
	ldr r0, [lr]
	str r3, [r0, #0x18]
	ldr r0, [lr]
	strb ip, [r0, #0x1c]
	ldr r0, [lr]
	strb ip, [r0, #0x1d]
	ldr r0, [lr]
	strb ip, [r0, #0x1e]
	ldr r0, [lr]
	strb ip, [r0, #0x1f]
	ldr r0, [lr]
	str ip, [r0, #0x20]
	ldr r0, [lr]
	str ip, [r0, #0x24]
	ldr r0, [lr]
	str r2, [r0, #0x28]
	ldr r0, [lr]
	str ip, [r0, #0x2c]
	ldr r0, [lr]
	str ip, [r0, #0x30]
	ldr r0, [lr]
	str ip, [r0, #0x34]
	ldr r0, [lr]
	str ip, [r0, #0x38]
	ldr r0, [lr]
	str ip, [r0, #0x3c]
	ldr r0, [lr]
	str ip, [r0, #0x40]
	ldr r0, [lr]
	str ip, [r0, #0x44]
	ldr r0, [lr]
	str ip, [r0, #0x48]
	ldr r0, [lr]
	str ip, [r0, #0x4c]
	ldr r0, [lr]
	str ip, [r0, #0x50]
	ldr r0, [lr]
	str ip, [r0, #0x54]
	ldr r0, [lr]
	str ip, [r0, #0x58]
	ldmia sp!, {r4, pc}
	.align 2, 0
_021E2428: .word ov04_022106D0
	arm_func_end ov04_021E234C

	arm_func_start ov04_021E242C
ov04_021E242C: ; 0x021E242C
	ldr r2, _021E2450 ; =ov04_022106D0
	ldr r3, [r2]
	cmp r3, #0
	moveq r0, #0
	strne r0, [r3, #0x44]
	ldrne r2, [r2]
	movne r0, #1
	strne r1, [r2, #0x48]
	bx lr
	.align 2, 0
_021E2450: .word ov04_022106D0
	arm_func_end ov04_021E242C

	arm_func_start ov04_021E2454
ov04_021E2454: ; 0x021E2454
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x104
	ldr r2, _021E24DC ; =ov04_022106D0
	mov r5, r0
	ldr r0, [r2]
	mov r4, r1
	cmp r0, #0
	beq _021E2480
	bl ov04_021E05FC
	cmp r0, #0
	bne _021E248C
_021E2480:
	add sp, sp, #0x104
	mov r0, #0
	ldmia sp!, {r4, r5, pc}
_021E248C:
	add r2, sp, #0
	mov r0, r5
	mov r1, r4
	mov r3, #0xff
	bl ov04_021DD4FC
	mvn r3, #0
	cmp r0, r3
	addeq sp, sp, #0x104
	moveq r0, #0
	ldmeqia sp!, {r4, r5, pc}
	add r2, sp, #0
	mov r1, #0
	strb r1, [r2, r0]
	mov r0, r3
	bl ov04_021E1E30
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	add sp, sp, #0x104
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021E24DC: .word ov04_022106D0
	arm_func_end ov04_021E2454

	arm_func_start ov04_021E24E0
ov04_021E24E0: ; 0x021E24E0
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x100
	mov r6, r3
	add r3, sp, #0
	ldr r4, [sp, #0x110]
	bl ov04_021E259C
	movs r5, r0
	mvneq r1, #0
	addeq sp, sp, #0x100
	streq r1, [r4]
	ldmeqia sp!, {r4, r5, r6, pc}
	add r0, sp, #0
	bl strlen
	mov r2, #0
	mov r1, r0
	add r0, sp, #0
	mov r3, r2
	bl ov04_021DD36C
	str r0, [r4]
	cmp r6, #0
	beq _021E2544
	ldr r4, [r4]
	mvn r0, #0
	cmp r4, r0
	bne _021E2550
_021E2544:
	add sp, sp, #0x100
	mov r0, r5
	ldmia sp!, {r4, r5, r6, pc}
_021E2550:
	add r0, sp, #0
	bl strlen
	mov r1, r0
	add r0, sp, #0
	mov r2, r6
	mov r3, r4
	bl ov04_021DD36C
	mov r0, r5
	add sp, sp, #0x100
	ldmia sp!, {r4, r5, r6, pc}
	arm_func_end ov04_021E24E0

	arm_func_start ov04_021E2578
ov04_021E2578: ; 0x021E2578
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r3, r1
	mov r1, #0
	str r2, [sp]
	mov r2, r1
	bl ov04_021E24E0
	add sp, sp, #4
	ldmfd sp!, {pc}
	arm_func_end ov04_021E2578

	arm_func_start ov04_021E259C
ov04_021E259C: ; 0x021E259C
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x218
	mov r6, r1
	add r1, sp, #4
	mov r4, r2
	mov r5, r3
	bl ov04_021E16EC
	cmp r0, #0
	beq _021E268C
	ldr r0, [sp, #8]
	cmp r0, #6
	bne _021E2650
	cmp r6, #0
	beq _021E260C
	ldr r0, _021E26B0 ; =ov04_0220D38C
	add r1, sp, #0
	add r2, sp, #0xc
	mov r3, #0x2f
	bl ov04_021DE9F4
	cmp r0, #0
	movle r0, #0
	strleb r0, [r6]
	ble _021E260C
	add r0, sp, #0
	mov r1, #0
	mov r2, #0xa
	bl strtoul
	strb r0, [r6]
_021E260C:
	cmp r4, #0
	beq _021E2668
	ldr r0, _021E26B4 ; =ov04_0220D390
	add r1, sp, #0
	add r2, sp, #0xc
	mov r3, #0x2f
	bl ov04_021DE9F4
	cmp r0, #0
	movle r0, #0
	strleb r0, [r4]
	ble _021E2668
	add r0, sp, #0
	mov r1, #0
	mov r2, #0xa
	bl strtoul
	strb r0, [r4]
	b _021E2668
_021E2650:
	cmp r6, #0
	movne r0, #0
	strneb r0, [r6]
	cmp r4, #0
	movne r0, #0
	strneb r0, [r4]
_021E2668:
	cmp r5, #0
	beq _021E267C
	add r1, sp, #0x10c
	mov r0, r5
	bl strcpy
_021E267C:
	ldr r0, [sp, #8]
	add sp, sp, #0x218
	and r0, r0, #0xff
	ldmia sp!, {r4, r5, r6, pc}
_021E268C:
	cmp r6, #0
	movne r0, #0
	strneb r0, [r6]
	cmp r4, #0
	movne r0, #0
	strneb r0, [r4]
	mov r0, #0
	add sp, sp, #0x218
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021E26B0: .word ov04_0220D38C
_021E26B4: .word ov04_0220D390
	arm_func_end ov04_021E259C

	arm_func_start ov04_021E26B8
ov04_021E26B8: ; 0x021E26B8
	ldr ip, _021E26CC ; =ov04_021E259C
	mov r3, r1
	mov r1, #0
	mov r2, r1
	bx ip
	.align 2, 0
_021E26CC: .word ov04_021E259C
	arm_func_end ov04_021E26B8

	.section .data

	.global ov04_0220D350
ov04_0220D350: ; 0x0220D350
	.byte 0x00, 0x00, 0x00, 0x00

	.global ov04_0220D354
ov04_0220D354: ; 0x0220D354
	.asciz "I have authorized your request to add me to your list"

	.balign 4, 0
	.global ov04_0220D38C
ov04_0220D38C: ; 0x0220D38C
	.asciz "SCM"

	.balign 4, 0
	.global ov04_0220D390
ov04_0220D390: ; 0x0220D390
	.asciz "SCN"

	.balign 4, 0
	.section .bss

	.global ov04_022106D0
ov04_022106D0: ; 0x022106D0
	.space 0x4
