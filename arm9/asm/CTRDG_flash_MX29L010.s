	.include "asm/macros.inc"
	.include "global.inc"

	.extern CTRDGi_PollingSR1MCOMMON
	.extern AgbFlash
	.extern CTRDGi_PollingSR
	.extern ctrdgi_flash_lock_id
	.extern ctrdgi_backup_irq
	.extern UNK_021D6B08

	.section .rodata

	.global MxMaxTime
MxMaxTime: ; 0x02104148
	.short 10, 10, 2000, 2000

	.global MX29L010
MX29L010: ; 0x02104150
	.word CTRDGi_WriteFlashSectorMX
	.word CTRDGi_EraseFlashChipMX
	.word CTRDGi_EraseFlashSectorMX
	.word CTRDGi_WriteFlashSectorAsyncMX
	.word CTRDGi_EraseFlashChipAsyncMX
	.word CTRDGi_EraseFlashSectorAsyncMX
	.word CTRDGi_PollingSR1MCOMMON
	.word MxMaxTime
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC2, 0x00, 0x09, 0x00

	.global defaultFlash1M
defaultFlash1M: ; 0x0210418C
	.word CTRDGi_WriteFlashSectorMX
	.word CTRDGi_EraseFlashChipMX
	.word CTRDGi_EraseFlashSectorMX
	.word CTRDGi_WriteFlashSectorAsyncMX
	.word CTRDGi_EraseFlashChipAsyncMX
	.word CTRDGi_EraseFlashSectorAsyncMX
	.word CTRDGi_PollingSR1MCOMMON
	.word MxMaxTime
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

    .text

	arm_func_start CTRDGi_WriteFlashSectorAsyncMX
CTRDGi_WriteFlashSectorAsyncMX: ; 0x020DD2D8
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DD300 ; =CTRDGi_WriteFlashSectorCoreMX
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD300: .word CTRDGi_WriteFlashSectorCoreMX

	arm_func_start CTRDGi_EraseFlashSectorAsyncMX
CTRDGi_EraseFlashSectorAsyncMX: ; 0x020DD304
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	mov r2, r1
	strh r0, [sp, #0x20]
	ldr r1, _020DD32C ; =CTRDGi_EraseFlashSectorCoreMX
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD32C: .word CTRDGi_EraseFlashSectorCoreMX

	arm_func_start CTRDGi_EraseFlashChipAsyncMX
CTRDGi_EraseFlashChipAsyncMX: ; 0x020DD330
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	ldr r1, _020DD354 ; =CTRDGi_EraseFlashChipCoreMX
	mov r2, r0
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD354: .word CTRDGi_EraseFlashChipCoreMX

	arm_func_start CTRDGi_WriteFlashSectorMX
CTRDGi_WriteFlashSectorMX: ; 0x020DD358
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreMX
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashSectorMX
CTRDGi_EraseFlashSectorMX: ; 0x020DD384
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashSectorCoreMX
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_EraseFlashChipMX
CTRDGi_EraseFlashChipMX: ; 0x020DD3AC
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	add r0, sp, #0x0
	bl CTRDGi_EraseFlashChipCoreMX
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlashSectorCoreMX
CTRDGi_WriteFlashSectorCoreMX: ; 0x020DD3D0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DD540 ; =AgbFlash
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r5, [sp, #0x20]
	ldrh r0, [r0, #0xa]
	ldr r4, [sp, #0xc]
	cmp r5, r0
	addcs sp, sp, #0x28
	ldrhs r0, _020DD544 ; =0x000080FF
	ldmcsia sp!, {r4-r8,lr}
	bxcs lr
	mov r0, r5
	bl CTRDGi_EraseFlashSectorMX
	movs r6, r0
	addne sp, sp, #0x28
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r0, _020DD548 ; =ctrdgi_flash_lock_id
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r7, _020DD54C ; =0x04000204
	ldr r0, _020DD540 ; =AgbFlash
	ldrh r3, [r7, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r1, [r7, #0x0]
	mov r0, r5, lsl #0xc
	ldr r2, [r2, #0x10]
	bic r1, r1, #0x3
	orr r1, r1, r2
	mov r0, r0, lsr #0x10
	strh r1, [r7, #0x0]
	and r7, r3, #0x3
	bl CTRDGi_SetFlashBankMx
	ldr r0, _020DD540 ; =AgbFlash
	and r1, r5, #0xf
	ldr r3, [r0, #0x0]
	mov r0, r1, lsl #0x10
	ldr r2, [r3, #0x4]
	ldr r8, _020DD550 ; =UNK_021D6B08
	ldr r1, _020DD554 ; =0x04000208
	strh r2, [r8, #0x0]
	ldrh r3, [r3, #0x8]
	mov r5, r0, lsr #0x10
	ldrh r2, [r1, #0x0]
	mov r0, #0x0
	mov r3, r5, lsl r3
	strh r0, [r1, #0x0]
	ldrh r1, [r8, #0x0]
	ldr r0, _020DD558 ; =ctrdgi_backup_irq
	add r5, r3, #0xa000000
	str r2, [r0, #0x0]
	cmp r1, #0x0
	beq _020DD4FC
_020DD4C8:
	mov r0, r4
	mov r1, r5
	bl CTRDGi_ProgramFlashByteMX
	movs r6, r0
	bne _020DD4FC
	ldrh r0, [r8, #0x0]
	add r4, r4, #0x1
	add r5, r5, #0x1
	sub r0, r0, #0x1
	strh r0, [r8, #0x0]
	ldrh r0, [r8, #0x0]
	cmp r0, #0x0
	bne _020DD4C8
_020DD4FC:
	ldr r3, _020DD554 ; =0x04000208
	ldr r0, _020DD558 ; =ctrdgi_backup_irq
	ldrh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, _020DD54C ; =0x04000204
	strh r0, [r3, #0x0]
	ldrh r1, [r2, #0x0]
	ldr r0, _020DD548 ; =ctrdgi_flash_lock_id
	bic r1, r1, #0x3
	orr r1, r1, r7
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge
	mov r0, r6
	add sp, sp, #0x28
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DD540: .word AgbFlash
_020DD544: .word 0x000080FF
_020DD548: .word ctrdgi_flash_lock_id
_020DD54C: .word 0x04000204
_020DD550: .word UNK_021D6B08
_020DD554: .word 0x04000208
_020DD558: .word ctrdgi_backup_irq

	arm_func_start CTRDGi_ProgramFlashByteMX
CTRDGi_ProgramFlashByteMX: ; 0x020DD55C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr ip, _020DD5B0 ; =0x0A005555
	mov r3, #0xaa
	ldr r2, _020DD5B4 ; =0x0A002AAA
	strb r3, [r12, #0x0]
	mov r3, #0x55
	mov lr, r0
	strb r3, [r2, #0x0]
	mov r0, #0xa0
	strb r0, [r12, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, _020DD5B8 ; =CTRDGi_PollingSR
	mov r0, #0x1
	strb r2, [r1, #0x0]
	ldrb r2, [lr, #0x0]
	ldr r3, [r3, #0x0]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD5B0: .word 0x0A005555
_020DD5B4: .word 0x0A002AAA
_020DD5B8: .word CTRDGi_PollingSR

	arm_func_start CTRDGi_EraseFlashSectorCoreMX
CTRDGi_EraseFlashSectorCoreMX: ; 0x020DD5BC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x10
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DD748 ; =AgbFlash
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r4, [sp, #0x30]
	ldrh r0, [r0, #0xa]
	cmp r4, r0
	addcs sp, sp, #0x34
	ldrhs r0, _020DD74C ; =0x000080FF
	ldmcsia sp!, {r4-r11,lr}
	bxcs lr
	ldr r0, _020DD750 ; =ctrdgi_flash_lock_id
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r5, _020DD754 ; =0x04000204
	ldr r0, _020DD748 ; =AgbFlash
	ldrh r3, [r5, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r1, [r5, #0x0]
	mov r0, r4, lsl #0xc
	ldr r2, [r2, #0x10]
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r5, #0x0]
	and r1, r3, #0x3
	mov r0, r0, lsr #0x10
	str r1, [sp, #0x0]
	bl CTRDGi_SetFlashBankMx
	and r0, r4, #0xf
	mov r0, r0, lsl #0x10
	mov r9, r0, lsr #0x10
	mov r0, #0x2
	mov r10, #0x0
	str r0, [sp, #0x8]
	mov r0, #0xff
	ldr r8, _020DD758 ; =0x04000208
	mov r11, r10
	mov r7, #0xaa
	mov r6, #0x55
	mov r5, #0x80
	mov r4, #0x30
	str r0, [sp, #0xc]
_020DD684:
	ldr r0, _020DD748 ; =AgbFlash
	ldrh r12, [r8, #0x0]
	ldr r0, [r0, #0x0]
	ldr r3, _020DD75C ; =ctrdgi_backup_irq
	ldrh r1, [r0, #0x8]
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	strh r11, [r8, #0x0]
	str r12, [r3, #0x0]
	ldr r3, _020DD760 ; =0x0A005555
	mov r1, r9, lsl r1
	strb r7, [r3, #0x0]
	ldr r3, _020DD764 ; =0x0A002AAA
	add r1, r1, #0xa000000
	strb r6, [r3, #0x0]
	ldr r3, _020DD760 ; =0x0A005555
	strb r5, [r3, #0x0]
	strb r7, [r3, #0x0]
	ldr r3, _020DD764 ; =0x0A002AAA
	strb r6, [r3, #0x0]
	strb r4, [r1, #0x0]
	ldrh r3, [r8, #0x0]
	ldr r3, _020DD75C ; =ctrdgi_backup_irq
	ldr r3, [r3, #0x0]
	strh r3, [r8, #0x0]
	ldr r3, _020DD768 ; =CTRDGi_PollingSR
	ldr r3, [r3, #0x0]
	blx r3
	str r0, [sp, #0x4]
	ands r0, r0, #0xa000
	beq _020DD714
	cmp r10, #0x0
	addeq r0, r10, #0x1
	moveq r0, r0, lsl #0x10
	moveq r10, r0, lsr #0x10
	beq _020DD684
_020DD714:
	ldr r2, _020DD754 ; =0x04000204
	ldr r1, _020DD750 ; =ctrdgi_flash_lock_id
	ldrh r0, [r2, #0x0]
	bic r3, r0, #0x3
	ldr r0, [sp, #0x0]
	orr r0, r3, r0
	strh r0, [r2, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge
	ldr r0, [sp, #0x4]
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020DD748: .word AgbFlash
_020DD74C: .word 0x000080FF
_020DD750: .word ctrdgi_flash_lock_id
_020DD754: .word 0x04000204
_020DD758: .word 0x04000208
_020DD75C: .word ctrdgi_backup_irq
_020DD760: .word 0x0A005555
_020DD764: .word 0x0A002AAA
_020DD768: .word CTRDGi_PollingSR

	arm_func_start CTRDGi_EraseFlashChipCoreMX
CTRDGi_EraseFlashChipCoreMX: ; 0x020DD76C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020DD848 ; =ctrdgi_flash_lock_id
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r4, _020DD84C ; =0x04000204
	ldr r0, _020DD850 ; =AgbFlash
	ldrh r3, [r4, #0x0]
	ldr r0, [r0, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r2, [r0, #0x10]
	ldr r0, _020DD854 ; =0x04000208
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r4, #0x0]
	ldrh r4, [r0, #0x0]
	mov r2, #0x0
	ldr r1, _020DD858 ; =ctrdgi_backup_irq
	strh r2, [r0, #0x0]
	ldr lr, _020DD85C ; =0x0A005555
	str r4, [r1, #0x0]
	mov r5, #0xaa
	ldr r4, _020DD860 ; =0x0A002AAA
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
	ldr r1, _020DD864 ; =CTRDGi_PollingSR
	strh r2, [r0, #0x0]
	ldr r4, [r1, #0x0]
	mov r0, #0x3
	mov r1, #0xa000000
	mov r2, #0xff
	and r5, r3, #0x3
	blx r4
	ldr r3, _020DD84C ; =0x04000204
	ldr r1, _020DD848 ; =ctrdgi_flash_lock_id
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r5
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DD848: .word ctrdgi_flash_lock_id
_020DD84C: .word 0x04000204
_020DD850: .word AgbFlash
_020DD854: .word 0x04000208
_020DD858: .word ctrdgi_backup_irq
_020DD85C: .word 0x0A005555
_020DD860: .word 0x0A002AAA
_020DD864: .word CTRDGi_PollingSR
