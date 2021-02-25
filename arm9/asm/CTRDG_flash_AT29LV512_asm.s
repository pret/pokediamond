	.include "asm/macros.inc"
	.include "global.inc"

	.extern CTRDGi_PollingSR512kCOMMON
	.extern AgbFlash
	.extern CTRDGi_PollingSR
	.extern ctrdgi_flash_lock_id
	.extern UNK_021D6B08
	.extern CTRDGi_EraseFlashChipCoreAT
	.extern CTRDGi_EraseFlashSectorCoreAT
	.extern AT29LV512_org
	.extern AT29LV512_lib

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
	ldr r1, _020DC860 ; =AT29LV512_lib
	mov r0, r0, lsl #0x15
	ldr r1, [r1, #0x24]
	ldr r4, _020DC864 ; =UNK_021D6B08
	mov r8, r0, lsr #0x10
	strh r1, [r4, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC84C
	ldr r0, _020DC868 ; =AT29LV512_org
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
_020DC860: .word AT29LV512_lib
_020DC864: .word UNK_021D6B08
_020DC868: .word AT29LV512_org

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
	ldr r0, _020DC984 ; =ctrdgi_flash_lock_id
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldr r4, [sp, #0xc]
	bl OS_LockCartridge
	ldr r5, _020DC988 ; =0x04000204
	ldr r1, _020DC98C ; =AgbFlash
	ldrh r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r3, [r1, #0x10]
	ldr r1, _020DC990 ; =AT29LV512_org
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
	ldr r3, _020DC9A0 ; =CTRDGi_PollingSR
	ldrh r0, [r12, #0x0]
	sub r1, r1, #0x1
	mov r0, #0x1
	strh r2, [r12, #0x0]
	ldrb r2, [r4, #-0x1]
	ldr r3, [r3, #0x0]
	blx r3
	ldr r3, _020DC988 ; =0x04000204
	ldr r1, _020DC984 ; =ctrdgi_flash_lock_id
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge
	mov r0, r4
	add sp, sp, #0x24
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DC984: .word ctrdgi_flash_lock_id
_020DC988: .word 0x04000204
_020DC98C: .word AgbFlash
_020DC990: .word AT29LV512_org
_020DC994: .word 0x04000208
_020DC998: .word 0x0A005555
_020DC99C: .word 0x0A002AAA
_020DC9A0: .word CTRDGi_PollingSR

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
