	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start CTRDGi_WriteFlashSectorAsyncLE
CTRDGi_WriteFlashSectorAsyncLE: ; 0x020DCC9C
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DCCC4 ; =CTRDGi_WriteFlashSectorCoreLE
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DCCC4: .word CTRDGi_WriteFlashSectorCoreLE

	arm_func_start CTRDGi_EraseFlashSectorAsyncLE
CTRDGi_EraseFlashSectorAsyncLE: ; 0x020DCCC8
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DCCF0 ; =CTRDGi_EraseFlashSectorCoreLE
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DCCF0: .word CTRDGi_EraseFlashSectorCoreLE

	arm_func_start CTRDGi_EraseFlashChipAsyncLE
CTRDGi_EraseFlashChipAsyncLE: ; 0x020DCCF4
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	ldr r1, _020DCD18 ; =CTRDGi_EraseFlashChipCoreLE
	mov r2, r0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DCD18: .word CTRDGi_EraseFlashChipCoreLE

	arm_func_start CTRDGi_WriteFlashSectorLE
CTRDGi_WriteFlashSectorLE: ; 0x020DCD1C
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreLE
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashSectorLE
CTRDGi_EraseFlashSectorLE: ; 0x020DCD48
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashSectorCoreLE
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashChipLE
CTRDGi_EraseFlashChipLE: ; 0x020DCD70
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashChipCoreLE
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_VerifyFlashErase
CTRDGi_VerifyFlashErase: ; 0x020DCD94
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020DCE14 ; =0x021D6B0C
	mov r4, r0
	ldrh r0, [r2, #0x0]
	mov r5, r1
	bl OS_LockCartridge
	ldr ip, _020DCE18 ; =0x04000204
	ldr r0, _020DCE1C ; =0x021D6B20
	ldrh r3, [r12, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r12, #0x0]
	ldr r2, [r0, #0x10]
	mov r0, r4
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r12, #0x0]
	and r6, r3, #0x3
	mov r4, #0x0
	blx r5
	cmp r0, #0x0
	ldr r2, _020DCE18 ; =0x04000204
	ldr r0, _020DCE14 ; =0x021D6B0C
	ldrh r1, [r2, #0x0]
	ldrne r4, _020DCE20 ; =0x00008004
	bic r1, r1, #0x3
	orr r1, r1, r6
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020DCE14: .word 0x021D6B0C
_020DCE18: .word 0x04000204
_020DCE1C: .word 0x021D6B20
_020DCE20: .word 0x00008004

	arm_func_start CTRDGi_VerifyFlashCoreFF
CTRDGi_VerifyFlashCoreFF: ; 0x020DCE24
	ldr r1, _020DCE54 ; =0x021D6B20
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _020DCE4C
_020DCE38:
	ldrb r1, [r0], #0x1
	cmp r1, #0xff
	bne _020DCE4C
	subs r2, r2, #0x1
	bne _020DCE38
_020DCE4C:
	mov r0, r2
	bx lr
	.balign 4
_020DCE54: .word 0x021D6B20

	arm_func_start CTRDGi_WriteFlashSectorCoreLE
CTRDGi_WriteFlashSectorCoreLE: ; 0x020DCE58
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r7, [sp, #0x20]
	ldr r6, [sp, #0xc]
	cmp r7, #0x10
	addcs sp, sp, #0x24
	ldrhs r0, _020DD018 ; =0x000080FF
	ldmcsia sp!, {r4-r9,lr}
	bxcs lr
	ldr r0, _020DD01C ; =0x021D6B20
	mov r9, #0x0
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x8]
	mov r0, r7, lsl r0
	add r4, r0, #0xa000000
	ldr r5, _020DD020 ; =CTRDGi_VerifyFlashCoreFF
_020DCEB8:
	mov r0, r7
	bl CTRDGi_EraseFlashSectorLE
	movs r8, r0
	bne _020DCEE0
	mov r0, r4
	mov r1, r5
	bl CTRDGi_VerifyFlashErase
	mov r0, r0, lsl #0x10
	movs r8, r0, lsr #0x10
	beq _020DCF04
_020DCEE0:
	add r0, r9, #0x1
	mov r0, r0, lsl #0x10
	cmp r9, #0x50
	mov r9, r0, lsr #0x10
	bne _020DCEB8
	add sp, sp, #0x24
	mov r0, r8
	ldmia sp!, {r4-r9,lr}
	bx lr
_020DCF04:
	mov r5, #0x1
	cmp r9, #0x0
	movne r5, #0x6
	cmp r5, #0x1
	mov r9, #0x1
	blo _020DCF38
_020DCF1C:
	mov r0, r7
	bl CTRDGi_EraseFlashSectorLE
	add r0, r9, #0x1
	mov r0, r0, lsl #0x10
	mov r9, r0, lsr #0x10
	cmp r9, r5
	bls _020DCF1C
_020DCF38:
	ldr r0, _020DD024 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r5, _020DD028 ; =0x04000204
	ldr r1, _020DD01C ; =0x021D6B20
	ldrh r0, [r5, #0x0]
	ldr r3, [r1, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r3, [r3, #0x10]
	ldr r7, _020DD02C ; =0x021D6B08
	bic r2, r2, #0x3
	orr r2, r2, r3
	strh r2, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldr sb, _020DD030 ; =0x04000208
	ldr r1, [r1, #0x4]
	mov r2, #0x0
	strh r1, [r7, #0x0]
	ldrh r3, [r9, #0x0]
	ldr r1, _020DD034 ; =0x021D6B38
	and r5, r0, #0x3
	strh r2, [r9, #0x0]
	ldrh r0, [r7, #0x0]
	str r3, [r1, #0x0]
	cmp r0, #0x0
	beq _020DCFD4
_020DCFA0:
	mov r0, r6
	mov r1, r4
	bl CTRDGi_ProgramFlashByteLE
	movs r8, r0
	bne _020DCFD4
	ldrh r0, [r7, #0x0]
	add r6, r6, #0x1
	add r4, r4, #0x1
	sub r0, r0, #0x1
	strh r0, [r7, #0x0]
	ldrh r0, [r7, #0x0]
	cmp r0, #0x0
	bne _020DCFA0
_020DCFD4:
	ldr r3, _020DD030 ; =0x04000208
	ldr r0, _020DD034 ; =0x021D6B38
	ldrh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, _020DD028 ; =0x04000204
	strh r0, [r3, #0x0]
	ldrh r1, [r2, #0x0]
	ldr r0, _020DD024 ; =0x021D6B0C
	bic r1, r1, #0x3
	orr r1, r1, r5
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r8
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020DD018: .word 0x000080FF
_020DD01C: .word 0x021D6B20
_020DD020: .word CTRDGi_VerifyFlashCoreFF
_020DD024: .word 0x021D6B0C
_020DD028: .word 0x04000204
_020DD02C: .word 0x021D6B08
_020DD030: .word 0x04000208
_020DD034: .word 0x021D6B38

	arm_func_start CTRDGi_ProgramFlashByteLE
CTRDGi_ProgramFlashByteLE: ; 0x020DD038
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020DD08C ; =0x0A005555
	mov r3, #0xaa
	ldr r2, _020DD090 ; =0x0A002AAA
	strb r3, [r12, #0x0]
	mov r3, #0x55
	mov lr, r0
	strb r3, [r2, #0x0]
	mov r0, #0xa0
	strb r0, [r12, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, _020DD094 ; =0x021D6B24
	mov r0, #0x1
	strb r2, [r1, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, [r3, #0x0]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD08C: .word 0x0A005555
_020DD090: .word 0x0A002AAA
_020DD094: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashSectorCoreLE
CTRDGi_EraseFlashSectorCoreLE: ; 0x020DD098
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r4, [sp, #0x20]
	cmp r4, #0x10
	addcs sp, sp, #0x28
	ldrhs r0, _020DD1B8 ; =0x000080FF
	ldmcsia sp!, {r4-r6,lr}
	bxcs lr
	ldr r0, _020DD1BC ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r6, _020DD1C0 ; =0x04000204
	ldr r1, _020DD1C4 ; =0x021D6B20
	ldrh r3, [r6, #0x0]
	ldr r0, [r1, #0x0]
	ldrh r2, [r6, #0x0]
	ldr r5, [r0, #0x10]
	ldr r0, _020DD1C8 ; =0x04000208
	bic r2, r2, #0x3
	orr r2, r2, r5
	strh r2, [r6, #0x0]
	ldr r1, [r1, #0x0]
	ldrh r5, [r0, #0x0]
	ldrh r12, [r1, #0x8]
	mov r1, #0x0
	ldr r2, _020DD1CC ; =0x021D6B38
	strh r1, [r0, #0x0]
	mov r6, r4, lsl r12
	ldr lr, _020DD1D0 ; =0x0A005555
	str r5, [r2, #0x0]
	mov r5, #0xaa
	ldr r4, _020DD1D4 ; =0x0A002AAA
	strb r5, [lr, #0x0]
	mov r12, #0x55
	strb r12, [r4, #0x0]
	mov r1, #0x80
	strb r1, [lr, #0x0]
	strb r5, [lr, #0x0]
	strb r12, [r4, #0x0]
	add r1, r6, #0xa000000
	mov r4, #0x30
	strb r4, [r1, #0x0]
	ldrh r4, [r0, #0x0]
	ldr r4, [r2, #0x0]
	ldr r2, _020DD1D8 ; =0x021D6B24
	strh r4, [r0, #0x0]
	ldr r4, [r2, #0x0]
	mov r0, #0x2
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DD1C0 ; =0x04000204
	ldr r1, _020DD1BC ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x28
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020DD1B8: .word 0x000080FF
_020DD1BC: .word 0x021D6B0C
_020DD1C0: .word 0x04000204
_020DD1C4: .word 0x021D6B20
_020DD1C8: .word 0x04000208
_020DD1CC: .word 0x021D6B38
_020DD1D0: .word 0x0A005555
_020DD1D4: .word 0x0A002AAA
_020DD1D8: .word 0x021D6B24

	arm_func_start CTRDGi_EraseFlashChipCoreLE
CTRDGi_EraseFlashChipCoreLE: ; 0x020DD1DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DD2B8 ; =0x021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r4, _020DD2BC ; =0x04000204
	ldr r0, _020DD2C0 ; =0x021D6B20
	ldrh r3, [r4, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r0, #0x10]
	ldr r0, _020DD2C4 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020DD2C8 ; =0x021D6B38
	strh r2, [r0, #0x0]
	ldr lr, _020DD2CC ; =0x0A005555
	str r4, [r1, #0x0]
	mov r5, #0xaa
	ldr r4, _020DD2D0 ; =0x0A002AAA
	strb r5, [lr, #0x0]
	mov r12, #0x55
	strb r12, [r4, #0x0]
	mov r2, #0x80
	strb r2, [lr, #0x0]
	strb r5, [lr, #0x0]
	strb r12, [r4, #0x0]
	mov r2, #0x10
	strb r2, [lr, #0x0]
	ldrh r2, [r0, #0x0]
	ldr r2, [r1, #0x0]
	ldr r1, _020DD2D4 ; =0x021D6B24
	strh r2, [r0, #0x0]
	ldr r4, [r1, #0x0]
	mov r0, #0x3
	mov r1, #0xa000000
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DD2BC ; =0x04000204
	ldr r1, _020DD2B8 ; =0x021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DD2B8: .word 0x021D6B0C
_020DD2BC: .word 0x04000204
_020DD2C0: .word 0x021D6B20
_020DD2C4: .word 0x04000208
_020DD2C8: .word 0x021D6B38
_020DD2CC: .word 0x0A005555
_020DD2D0: .word 0x0A002AAA
_020DD2D4: .word 0x021D6B24
