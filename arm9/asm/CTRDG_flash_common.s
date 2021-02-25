	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021D6B08
UNK_021D6B08: ; 0x021D6B08
	.space 0x4

	.global ctrdgi_flash_lock_id
ctrdgi_flash_lock_id: ; 0x021D6B0C
	.space 0x4

	.global UNK_021D6B10
UNK_021D6B10: ; 0x021D6B10
	.space 0x4

	.global CTRDGi_WriteAgbFlashSector
CTRDGi_WriteAgbFlashSector: ; 0x021D6B14
	.space 0x4

	.global CTRDGi_WriteAgbFlashSectorAsync
CTRDGi_WriteAgbFlashSectorAsync: ; 0x021D6B18
	.space 0x4

	.global CTRDGi_EraseAgbFlashChipAsync
CTRDGi_EraseAgbFlashChipAsync: ; 0x021D6B1C
	.space 0x4

	.global AgbFlash
AgbFlash: ; 0x021D6B20
	.space 0x4

	.global CTRDGi_PollingSR
CTRDGi_PollingSR: ; 0x021D6B24
	.space 0x4

	.global ctrdgi_fl_maxtime
ctrdgi_fl_maxtime: ; 0x021D6B28
	.space 0x4

	.global CTRDGi_EraseAgbFlashSector
CTRDGi_EraseAgbFlashSector: ; 0x021D6B2C
	.space 0x4

	.global CTRDGi_EraseAgbFlashSectorAsync
CTRDGi_EraseAgbFlashSectorAsync: ; 0x021D6B30
	.space 0x4

	.global CTRDGi_EraseAgbFlashChip
CTRDGi_EraseAgbFlashChip: ; 0x021D6B34
	.space 0x4

	.global ctrdgi_backup_irq
ctrdgi_backup_irq: ; 0x021D6B38
	.space 0x4

	.global UNK_021D6B3C
UNK_021D6B3C: ; 0x021D6B3C
	.space 0x8

	.global UNK_021D6B44
UNK_021D6B44: ; 0x021D6B44
	.space 0x8

	.global ctrdgi_sram_lock_id
ctrdgi_sram_lock_id: ; 0x021D6B4C
	.space 0x4

    .text

	arm_func_start CTRDG_WriteAndVerifyAgbFlashAsync
CTRDG_WriteAndVerifyAgbFlashAsync: ; 0x020DBF14
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	str r2, [sp, #0x18]
	ldr r1, _020DBF44 ; =CTRDGi_WriteAndVerifyAgbFlashSectorCore
	add r0, sp, #0x0
	mov r2, r3
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBF44: .word CTRDGi_WriteAndVerifyAgbFlashSectorCore

	arm_func_start CTRDG_VerifyAgbFlash
CTRDG_VerifyAgbFlash:
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	str r2, [sp, #0x18]
	bl CTRDGi_VerifyAgbFlashCore
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDG_WriteAgbFlashSector
CTRDG_WriteAgbFlashSector:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020DBF90 ; =CTRDGi_WriteAgbFlashSector
	ldr r2, [r2, #0x0]
	blx r2
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DBF90: .word CTRDGi_WriteAgbFlashSector

	arm_func_start CTRDG_ReadAgbFlash
CTRDG_ReadAgbFlash: ; 0x020DBF94
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0x14]
	str r2, [sp, #0x1c]
	str r3, [sp, #0x18]
	bl CTRDGi_ReadAgbFlashCore
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteAndVerifyAgbFlashSectorCore
CTRDGi_WriteAndVerifyAgbFlashSectorCore: ; 0x020DBFC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r4, r0
	ldmia r4!, {r0-r3}
	add r12, sp, #0x0
	stmia r12!, {r0-r3}
	ldmia r4!, {r0-r3}
	stmia r12!, {r0-r3}
	ldr r0, [r4, #0x0]
	mov r7, #0x0
	str r0, [r12, #0x0]
	ldrh r6, [sp, #0x20]
	ldr r5, [sp, #0xc]
	ldr r4, [sp, #0x18]
_020DBFF8:
	mov r0, r6
	mov r1, r5
	bl CTRDG_WriteAgbFlashSector
_020DC004: ; 0x020DC004
	cmp r0, #0x0
	bne _020DC02C
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl CTRDG_VerifyAgbFlash
_020DC01C: ; 0x020DC01C
	cmp r0, #0x0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_020DC02C:
	add r1, r7, #0x1
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	cmp r7, #0x3
	blo _020DBFF8
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CTRDGi_VerifyAgbFlashCore
CTRDGi_VerifyAgbFlashCore: ; 0x020DC04C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DC128 ; =ctrdgi_flash_lock_id
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r6, [sp, #0x20]
	ldr r5, [sp, #0xc]
	ldr r4, [sp, #0x18]
	bl OS_LockCartridge
	ldr r3, _020DC12C ; =0x04000204
	ldr r0, _020DC130 ; =AgbFlash
	ldrh r2, [r3, #0x0]
	ldrh r1, [r3, #0x0]
	and r7, r2, #0x3
	bic r1, r1, #0x3
	orr r1, r1, #0x3
	strh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x20000
	bne _020DC0D4
	mov r0, r6, lsl #0xc
	mov r0, r0, lsr #0x10
	bl CTRDGi_SetFlashBankMx
	and r0, r6, #0xf
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
_020DC0D4:
	ldr r1, _020DC130 ; =AgbFlash
	mov r0, r5
	ldr r1, [r1, #0x0]
	mov r2, r4
	ldrh r1, [r1, #0x8]
	mov r1, r6, lsl r1
	add r1, r1, #0xa000000
	bl CTRDGi_VerifyFlashSectorCore
	ldr r3, _020DC12C ; =0x04000204
	ldr r1, _020DC128 ; =ctrdgi_flash_lock_id
	ldrh r2, [r3, #0x0]
	mov r4, r0
	bic r0, r2, #0x3
	orr r0, r0, r7
	strh r0, [r3, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_UnlockCartridge
	mov r0, r4
	add sp, sp, #0x24
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DC128: .word ctrdgi_flash_lock_id
_020DC12C: .word 0x04000204
_020DC130: .word AgbFlash

	arm_func_start CTRDGi_VerifyFlashSectorCore
CTRDGi_VerifyFlashSectorCore: ; 0x020DC134
	cmp r2, #0x0
	sub r2, r2, #0x1
	beq _020DC160
_020DC140:
	ldrb r12, [r1], #0x1
	ldrb r3, [r0], #0x1
	cmp r12, r3
	subne r0, r1, #0x1
	bxne lr
	cmp r2, #0x0
	sub r2, r2, #0x1
	bne _020DC140
_020DC160:
	mov r0, #0x0
	bx lr

	arm_func_start CTRDGi_ReadAgbFlashCore
CTRDGi_ReadAgbFlashCore: ; 0x020DC168
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DC25C ; =ctrdgi_flash_lock_id
	ldr r1, [r5, #0x0]
	ldrh r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r7, [sp, #0x20]
	ldr r6, [sp, #0x14]
	ldr r5, [sp, #0x1c]
	ldr r4, [sp, #0x18]
	bl OS_LockCartridge
	ldr r3, _020DC260 ; =0x04000204
	ldr r0, _020DC264 ; =AgbFlash
	ldrh r2, [r3, #0x0]
	ldrh r1, [r3, #0x0]
	and r8, r2, #0x3
	bic r1, r1, #0x3
	orr r1, r1, #0x3
	strh r1, [r3, #0x0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x20000
	bne _020DC1F4
	mov r0, r7, lsl #0xc
	mov r0, r0, lsr #0x10
	bl CTRDGi_SetFlashBankMx
	and r0, r7, #0xf
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
_020DC1F4:
	ldr r0, _020DC264 ; =AgbFlash
	cmp r4, #0x0
	ldr r0, [r0, #0x0]
	sub r4, r4, #0x1
	ldrh r0, [r0, #0x8]
	mov r0, r7, lsl r0
	add r0, r0, #0xa000000
	add r1, r6, r0
	beq _020DC22C
_020DC218:
	ldrb r0, [r1], #0x1
	cmp r4, #0x0
	sub r4, r4, #0x1
	strb r0, [r5], #0x1
	bne _020DC218
_020DC22C:
	ldr r2, _020DC260 ; =0x04000204
	ldr r0, _020DC25C ; =ctrdgi_flash_lock_id
	ldrh r1, [r2, #0x0]
	bic r1, r1, #0x3
	orr r1, r1, r8
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	bl OS_UnlockCartridge
	mov r0, #0x0
	add sp, sp, #0x28
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DC25C: .word ctrdgi_flash_lock_id
_020DC260: .word 0x04000204
_020DC264: .word AgbFlash

	arm_func_start CTRDGi_PollingSR1MCOMMON
CTRDGi_PollingSR1MCOMMON: ; 0x020DC268
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x0
	bl StartFlashTimer
	ldr r4, _020DC318 ; =UNK_021D6B10
_020DC284:
	bl CheckFlashTimer
	mov r0, r7
	bl CTRDGi_ReadSrFunc
	cmp r0, r6
	beq _020DC300
	ands r0, r0, #0x20
	beq _020DC2CC
	mov r0, r7
	bl CTRDGi_ReadSrFunc
_020DC2A8: ; 0x020DC2A8
	cmp r6, r0
	beq _020DC300
	orr r0, r8, #0xa000
	mov r0, r0, lsl #0x10
	ldr r1, _020DC31C ; =0x0A005555
	mov r2, #0xf0
	strb r2, [r1, #0x0]
	mov r5, r0, lsr #0x10
	b _020DC300
_020DC2CC:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC284
	mov r0, r7
	bl CTRDGi_ReadSrFunc
_020DC2E0: ; 0x020DC2E0
	cmp r6, r0
	beq _020DC300
	orr r0, r8, #0xc000
	mov r0, r0, lsl #0x10
	ldr r1, _020DC31C ; =0x0A005555
	mov r2, #0xf0
	strb r2, [r1, #0x0]
	mov r5, r0, lsr #0x10
_020DC300:
	bl CTRDG_IsExisting
_020DC304: ; 0x020DC304
	cmp r0, #0x0
	moveq r5, #0x1000
	mov r0, r5
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DC318: .word UNK_021D6B10
_020DC31C: .word 0x0A005555

	arm_func_start CTRDGi_PollingSR512kCOMMON
CTRDGi_PollingSR512kCOMMON: ; 0x020DC320
	stmdb sp!, {r4-r8,lr}
	mov r4, r0
	mov r8, r1
	mov r7, r2
	mov r6, #0x0
	bl StartFlashTimer
	ldr r5, _020DC3A8 ; =UNK_021D6B10
_020DC33C:
	mov r0, r8
	bl CTRDGi_ReadSrFunc
	cmp r0, r7
	beq _020DC390
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020DC33C
	mov r0, r8
	bl CTRDGi_ReadSrFunc
_020DC360: ; 0x020DC360
	cmp r7, r0
	beq _020DC390
	ldr r0, _020DC3AC ; =AgbFlash
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x18]
	cmp r0, #0xc2
	ldreq r0, _020DC3B0 ; =0x0A005555
	moveq r1, #0xf0
	streqb r1, [r0, #0x0]
	orr r0, r4, #0xc000
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
_020DC390:
	bl CTRDG_IsExisting
_020DC394: ; 0x020DC394
	cmp r0, #0x0
	moveq r6, #0x1000
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020DC3A8: .word UNK_021D6B10
_020DC3AC: .word AgbFlash
_020DC3B0: .word 0x0A005555

	arm_func_start CTRDGi_ReadSrFunc
CTRDGi_ReadSrFunc:
	ldrb r0, [r0, #0x0]
	bx lr

	arm_func_start CheckFlashTimer
CheckFlashTimer: ; 0x020DC3BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_GetTick
	ldr r3, _020DC420 ; =UNK_021D6B44
	ldr r2, _020DC424 ; =0x000082EA
	ldr r12, [r3, #0x0]
	ldr r3, [r3, #0x4]
	subs r12, r0, r12
	sbc r0, r1, r3
	mov r1, r0, lsl #0x6
	orr r1, r1, r12, lsr #0x1a
	mov r0, r12, lsl #0x6
	mov r3, #0x0
	bl _ll_udiv
	ldr r2, _020DC428 ; =UNK_021D6B3C
	ldr r3, [r2, #0x4]
	ldr r2, [r2, #0x0]
	cmp r3, r1
	cmpeq r2, r0
	ldrls r0, _020DC42C ; =UNK_021D6B10
	movls r1, #0x1
	strlsh r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC420: .word UNK_021D6B44
_020DC424: .word 0x000082EA
_020DC428: .word UNK_021D6B3C
_020DC42C: .word UNK_021D6B10

	arm_func_start StartFlashTimer
StartFlashTimer: ; 0x020DC430
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020DC47C ; =ctrdgi_fl_maxtime
	ldr r2, _020DC480 ; =UNK_021D6B10
	mov r3, #0x0
	ldr r1, [r1, #0x0]
	strh r3, [r2, #0x0]
	mov r0, r0, lsl #0x1
	ldrh r1, [r1, r0]
	ldr r0, _020DC484 ; =UNK_021D6B3C
	str r1, [r0, #0x0]
	str r3, [r0, #0x4]
	bl OS_GetTick
	ldr r2, _020DC488 ; =UNK_021D6B44
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DC47C: .word ctrdgi_fl_maxtime
_020DC480: .word UNK_021D6B10
_020DC484: .word UNK_021D6B3C
_020DC488: .word UNK_021D6B44

	arm_func_start CTRDGi_ReadFlashID
CTRDGi_ReadFlashID: ; 0x020DC48C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020DC590 ; =0x04000208
	mov r0, #0x0
	ldrh r2, [r5, #0x0]
	ldr r1, _020DC594 ; =ctrdgi_backup_irq
	ldr r4, _020DC598 ; =0x0A005555
	strh r0, [r5, #0x0]
	str r2, [r1, #0x0]
	mov r3, #0xaa
	ldr r2, _020DC59C ; =0x0A002AAA
	strb r3, [r4, #0x0]
	mov r3, #0x55
	strb r3, [r2, #0x0]
	mov r2, #0x90
	strb r2, [r4, #0x0]
	ldrh r2, [r5, #0x0]
	ldr r1, [r1, #0x0]
	strh r1, [r5, #0x0]
	bl StartFlashTimer
	ldr r4, _020DC5A0 ; =UNK_021D6B10
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020DC4FC
_020DC4EC:
	bl CheckFlashTimer
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020DC4EC
_020DC4FC:
	ldr r0, _020DC5A4 ; =0x0A000001
	bl CTRDGi_ReadSrFunc
	mov r4, r0, lsl #0x18
	mov r0, #0xa000000
	bl CTRDGi_ReadSrFunc
	ldr ip, _020DC590 ; =0x04000208
	orr r4, r0, r4, lsr #0x10
	ldrh r2, [r12, #0x0]
	mov r0, #0x0
	ldr r1, _020DC594 ; =ctrdgi_backup_irq
	strh r0, [r12, #0x0]
	ldr r5, _020DC598 ; =0x0A005555
	str r2, [r1, #0x0]
	mov r3, #0xaa
	ldr r2, _020DC59C ; =0x0A002AAA
	strb r3, [r5, #0x0]
	mov r3, #0x55
	strb r3, [r2, #0x0]
	mov r2, #0xf0
	strb r2, [r5, #0x0]
	strb r2, [r5, #0x0]
	ldrh r2, [r12, #0x0]
	ldr r1, [r1, #0x0]
	strh r1, [r12, #0x0]
	bl StartFlashTimer
	ldr r5, _020DC5A0 ; =UNK_021D6B10
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020DC580
_020DC570:
	bl CheckFlashTimer
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020DC570
_020DC580:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020DC590: .word 0x04000208
_020DC594: .word ctrdgi_backup_irq
_020DC598: .word 0x0A005555
_020DC59C: .word 0x0A002AAA
_020DC5A0: .word UNK_021D6B10
_020DC5A4: .word 0x0A000001

	arm_func_start CTRDGi_SetFlashBankMx
CTRDGi_SetFlashBankMx: ; 0x020DC5A8
	ldr r3, _020DC5D4 ; =0x0A005555
	mov r2, #0xaa
	ldr r1, _020DC5D8 ; =0x0A002AAA
	strb r2, [r3, #0x0]
	mov r2, #0x55
	strb r2, [r1, #0x0]
	mov r1, #0xb0
	strb r1, [r3, #0x0]
	mov r1, #0xa000000
	strb r0, [r1, #0x0]
	bx lr
	.balign 4
_020DC5D4: .word 0x0A005555
_020DC5D8: .word 0x0A002AAA
