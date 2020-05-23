	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_0210400C
	.extern UNK_021D6B20
	.extern UNK_021D6B24
	.extern UNK_021D6B0C
	.extern UNK_021D6B38
	.extern UNK_02104048
	.extern UNK_021D6B08

    .text

	arm_func_start CTRDGi_WriteFlashSectorAsyncAT
CTRDGi_WriteFlashSectorAsyncAT: ; 0x020DC5DC
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DC604 ; =CTRDGi_WriteFlashSectorCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC604: .word CTRDGi_WriteFlashSectorCoreAT

	arm_func_start CTRDGi_EraseFlashSectorAsyncAT
CTRDGi_EraseFlashSectorAsyncAT: ; 0x020DC608
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DC630 ; =CTRDGi_EraseFlashSectorCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC630: .word CTRDGi_EraseFlashSectorCoreAT

	arm_func_start CTRDGi_WriteFlashSectorAT
CTRDGi_WriteFlashSectorAT: ; 0x020DC634
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashSectorAT
CTRDGi_EraseFlashSectorAT: ; 0x020DC660
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashSectorCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlash4KBAsyncAT
CTRDGi_WriteFlash4KBAsyncAT: ; 0x020DC688
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DC6B0 ; =CTRDGi_WriteFlash4KBCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC6B0: .word CTRDGi_WriteFlash4KBCoreAT

	arm_func_start CTRDGi_EraseFlash4KBAsyncAT
CTRDGi_EraseFlash4KBAsyncAT: ; 0x020DC6B4
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DC6DC ; =CTRDGi_EraseFlash4KBCoreAT
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC6DC: .word CTRDGi_EraseFlash4KBCoreAT

	arm_func_start CTRDGi_EraseFlashChipAsyncAT
CTRDGi_EraseFlashChipAsyncAT: ; 0x020DC6E0
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	ldr r1, _020DC704 ; =CTRDGi_EraseFlashChipCoreAT
	mov r2, r0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC704: .word CTRDGi_EraseFlashChipCoreAT

	arm_func_start CTRDGi_WriteFlash4KBAT
CTRDGi_WriteFlash4KBAT: ; 0x020DC708
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlash4KBCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlash4KBAT
CTRDGi_EraseFlash4KBAT: ; 0x020DC734
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlash4KBCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashChipAT
CTRDGi_EraseFlashChipAT: ; 0x020DC75C
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashChipCoreAT
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlash4KBCoreAT
CTRDGi_WriteFlash4KBCoreAT: ; 0x020DC780
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
	ldrh r0, [sp, #0x20]
	ldr r7, [sp, #0xc]
	cmp r0, #0x10
	addcs sp, sp, #0x24
	ldrhs r0, _020DC85C ; =0x000080FF
	ldmcsia sp!, {r4-r9,lr}
	bxcs lr
	ldr r1, _020DC860 ; =UNK_0210400C
	mov r0, r0, lsl #0x15
	ldr r1, [r1, #0x24]
	ldr r4, _020DC864 ; =UNK_021D6B08
	mov r8, r0, lsr #0x10
	strh r1, [r4, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC84C
	ldr r0, _020DC868 ; =UNK_02104048
	ldr r6, [r0, #0x24]
	mov r5, #0x2
_020DC7F4:
	mov r9, r5
_020DC7F8:
	mov r0, r8
	mov r1, r7
	bl CTRDGi_WriteFlashSectorAT
	movs r12, r0
	beq _020DC81C
	sub r0, r9, #0x1
	mov r0, r0, lsl #0x10
	movs r9, r0, lsr #0x10
	bne _020DC7F8
_020DC81C:
	cmp r12, #0x0
	bne _020DC84C
	ldrh r1, [r4, #0x0]
	add r0, r8, #0x1
	mov r0, r0, lsl #0x10
	sub r1, r1, r6
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	add r7, r7, r6
	mov r8, r0, lsr #0x10
	cmp r1, #0x0
	bne _020DC7F4
_020DC84C:
	mov r0, r12
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020DC85C: .word 0x000080FF
_020DC860: .word UNK_0210400C
_020DC864: .word UNK_021D6B08
_020DC868: .word UNK_02104048

	arm_func_start CTRDGi_WriteFlashSectorCoreAT
CTRDGi_WriteFlashSectorCoreAT: ; 0x020DC86C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x24
	mov r5, r0
	add r4, sp, #0x0
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DC984 ; =UNK_021D6B0C
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldr r4, [sp, #0xc]
	bl OS_LockCartridge
	ldr r5, _020DC988 ; =0x04000204
	ldr r1, _020DC98C ; =UNK_021D6B20
	ldrh r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r3, [r1, #0x10]
	ldr r1, _020DC990 ; =UNK_02104048
	bic r2, r2, #0x3
	orr r2, r2, r3
	strh r2, [r5, #0x0]
	ldr r5, _020DC994 ; =0x04000208
	ldrh lr, [sp, #0x20]
	ldrh r12, [r1, #0x28]
	ldrh r2, [r5, #0x0]
	mov r3, #0x0
	mov lr, lr, lsl r12
	strh r3, [r5, #0x0]
	ldr ip, _020DC998 ; =0x0A005555
	mov r5, #0xaa
	strb r5, [r12, #0x0]
	ldr r3, _020DC99C ; =0x0A002AAA
	mov r5, #0x55
	strb r5, [r3, #0x0]
	mov r3, #0xa0
	strb r3, [r12, #0x0]
	ldr r3, [r1, #0x24]
	and r5, r0, #0x3
	cmp r3, #0x0
	add r1, lr, #0xa000000
	beq _020DC92C
_020DC91C:
	ldrb r0, [r4], #0x1
	subs r3, r3, #0x1
	strb r0, [r1], #0x1
	bne _020DC91C
_020DC92C:
	ldr ip, _020DC994 ; =0x04000208
	ldr r3, _020DC9A0 ; =UNK_021D6B24
	ldrh r0, [r12, #0x0]
	sub r1, r1, #0x1
	mov r0, #0x1
	strh r2, [r12, #0x0]
	ldrb r2, [r4, #-0x1]
	ldr r3, [r3, #0x0]
	blx r3
	ldr r3, _020DC988 ; =0x04000204
	ldr r1, _020DC984 ; =UNK_021D6B0C
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r4
	add sp, sp, #0x24
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DC984: .word UNK_021D6B0C
_020DC988: .word 0x04000204
_020DC98C: .word UNK_021D6B20
_020DC990: .word UNK_02104048
_020DC994: .word 0x04000208
_020DC998: .word 0x0A005555
_020DC99C: .word 0x0A002AAA
_020DC9A0: .word UNK_021D6B24

	arm_func_start CTRDGi_EraseFlash4KBCoreAT
CTRDGi_EraseFlash4KBCoreAT: ; 0x020DC9A4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x0]
	ldrh r0, [sp, #0x20]
	cmp r0, #0x10
	addcs sp, sp, #0x24
	ldrhs r0, _020DCA54 ; =0x000080FF
	ldmcsia sp!, {r4-r7,lr}
	bxcs lr
	mov r0, r0, lsl #0x15
	mov r5, r0, lsr #0x10
	mov r6, #0x0
	mov r4, #0x2
_020DC9F4:
	mov r7, r4
_020DC9F8:
	mov r0, r5
	bl CTRDGi_EraseFlashSectorAT
_020DCA00: ; 0x020DCA00
	cmp r0, #0x0
	beq _020DCA18
	sub r1, r7, #0x1
	mov r1, r1, lsl #0x10
	movs r7, r1, lsr #0x10
	bne _020DC9F8
_020DCA18:
	add r1, r5, #0x1
	mov r1, r1, lsl #0x10
	cmp r0, #0x0
	mov r5, r1, lsr #0x10
	addne sp, sp, #0x24
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	add r1, r6, #0x1
	mov r1, r1, lsl #0x10
	mov r6, r1, lsr #0x10
	cmp r6, #0x20
	blo _020DC9F4
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DCA54: .word 0x000080FF

	arm_func_start CTRDGi_EraseFlashSectorCoreAT
CTRDGi_EraseFlashSectorCoreAT: ; 0x020DCA58
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, [r5, #0x0]
	ldr r1, _020DCB80 ; =UNK_02104048
	str r0, [r4, #0x0]
	ldr r0, _020DCB84 ; =UNK_021D6B0C
	ldrh r2, [sp, #0x20]
	ldrh r1, [r1, #0x28]
	ldrh r0, [r0, #0x0]
	mov r1, r2, lsl r1
	add r5, r1, #0xa000000
	bl OS_LockCartridge
	ldr r4, _020DCB88 ; =0x04000204
	ldr r1, _020DCB8C ; =UNK_021D6B20
	ldrh r0, [r4, #0x0]
	ldr r2, [r1, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r2, #0x10]
	ldr r3, _020DCB90 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r2, [r3, #0x0]
	mov r1, #0x0
	ldr r4, _020DCB94 ; =0x0A005555
	strh r1, [r3, #0x0]
	mov r3, #0xaa
	strb r3, [r4, #0x0]
	ldr r1, _020DCB98 ; =0x0A002AAA
	mov r3, #0x55
	strb r3, [r1, #0x0]
	mov r3, #0xa0
	strb r3, [r4, #0x0]
	ldr r1, _020DCB80 ; =UNK_02104048
	and r4, r0, #0x3
	ldr r1, [r1, #0x24]
	cmp r1, #0x0
	beq _020DCB18
	mov r0, #0xff
_020DCB0C:
	strb r0, [r5], #0x1
	subs r1, r1, #0x1
	bne _020DCB0C
_020DCB18:
	ldr ip, _020DCB90 ; =0x04000208
	ldr r3, _020DCB9C ; =UNK_021D6B24
	ldrh r0, [r12, #0x0]
	sub r1, r5, #0x1
	strh r2, [r12, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x1
	mov r2, #0xff
	blx r3
	ldr r2, _020DCB88 ; =0x04000204
	movs r5, r0
	ldrh r1, [r2, #0x0]
	andne r0, r5, #0xff00
	orrne r0, r0, #0x2
	movne r0, r0, lsl #0x10
	bic r1, r1, #0x3
	movne r5, r0, lsr #0x10
	orr r1, r1, r4
	ldr r0, _020DCB84 ; =UNK_021D6B0C
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge2
	mov r0, r5
	add sp, sp, #0x24
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DCB80: .word UNK_02104048
_020DCB84: .word UNK_021D6B0C
_020DCB88: .word 0x04000204
_020DCB8C: .word UNK_021D6B20
_020DCB90: .word 0x04000208
_020DCB94: .word 0x0A005555
_020DCB98: .word 0x0A002AAA
_020DCB9C: .word UNK_021D6B24

	arm_func_start CTRDGi_EraseFlashChipCoreAT
CTRDGi_EraseFlashChipCoreAT: ; 0x020DCBA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DCC7C ; =UNK_021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r4, _020DCC80 ; =0x04000204
	ldr r0, _020DCC84 ; =UNK_021D6B20
	ldrh r3, [r4, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r0, #0x10]
	ldr r0, _020DCC88 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020DCC8C ; =UNK_021D6B38
	strh r2, [r0, #0x0]
	ldr lr, _020DCC90 ; =0x0A005555
	str r4, [r1, #0x0]
	mov r5, #0xaa
	ldr r4, _020DCC94 ; =0x0A002AAA
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
	ldr r1, _020DCC98 ; =UNK_021D6B24
	strh r2, [r0, #0x0]
	ldr r4, [r1, #0x0]
	mov r0, #0x3
	mov r1, #0xa000000
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DCC80 ; =0x04000204
	ldr r1, _020DCC7C ; =UNK_021D6B0C
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
_020DCC7C: .word UNK_021D6B0C
_020DCC80: .word 0x04000204
_020DCC84: .word UNK_021D6B20
_020DCC88: .word 0x04000208
_020DCC8C: .word UNK_021D6B38
_020DCC90: .word 0x0A005555
_020DCC94: .word 0x0A002AAA
_020DCC98: .word UNK_021D6B24
