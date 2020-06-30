	.include "asm/macros.inc"
	.include "global.inc"

	.extern CTRDGi_EraseFlash4KBAT
	.extern CTRDGi_EraseFlash4KBAsyncAT
	.extern CTRDGi_EraseFlashChipAT
	.extern CTRDGi_EraseFlashChipAsyncAT
	.extern CTRDGi_EraseFlashChipAsyncLE
	.extern CTRDGi_EraseFlashChipAsyncMX
	.extern CTRDGi_EraseFlashChipLE
	.extern CTRDGi_EraseFlashChipMX
	.extern CTRDGi_EraseFlashSectorAT
	.extern CTRDGi_EraseFlashSectorAsyncAT
	.extern CTRDGi_EraseFlashSectorAsyncLE
	.extern CTRDGi_EraseFlashSectorAsyncMX
	.extern CTRDGi_EraseFlashSectorMX
	.extern CTRDGi_PollingSR1MCOMMON
	.extern CTRDGi_PollingSR512kCOMMON
	.extern CTRDGi_WriteFlash4KBAT
	.extern CTRDGi_WriteFlash4KBAsyncAT
	.extern CTRDGi_WriteFlashSectorAT
	.extern CTRDGi_WriteFlashSectorAsyncAT
	.extern CTRDGi_WriteFlashSectorAsyncLE
	.extern CTRDGi_WriteFlashSectorAsyncMX
	.extern CTRDGi_WriteFlashSectorLE
	.extern CTRDGi_WriteFlashSectorMX
	.extern CTRDGi_WriteFlashSectorAsyncMX5
	.extern CTRDGi_WriteFlashSectorMX5
	.extern UNK_021D6B14
	.extern UNK_021D6B30
	.extern UNK_021D6B28
	.extern UNK_021D6B1C
	.extern UNK_021D6B24
	.extern UNK_021D6B20
	.extern UNK_021D6B0C
	.extern UNK_021D6B34
	.extern UNK_021D6B2C
	.extern UNK_021D6B4C
	.extern UNK_021D6B18

	.section .rodata

	.global UNK_02103FE4
UNK_02103FE4: ; 0x02103FE4
	.byte 0x14, 0x00, 0x00, 0x00

	.global UNK_02103FE8
UNK_02103FE8: ; 0x02103FE8
	.word UNK_02104150
	.word UNK_0210408C
	.word UNK_0210418C

	.global UNK_02103FF4
UNK_02103FF4: ; 0x02103FF4
	.word UNK_0210410C
	.word UNK_0210400C
	.word UNK_021041D0
	.word UNK_021040D0

	.global UNK_02104004
UNK_02104004: ; 0x02104004
	.byte 0x0A, 0x00, 0x28, 0x00, 0x00, 0x00, 0x28, 0x00

	.global UNK_0210400C
UNK_0210400C: ; 0x0210400C
	.word CTRDGi_WriteFlash4KBAT
	.word CTRDGi_EraseFlashChipAT
	.word CTRDGi_EraseFlash4KBAT
	.word CTRDGi_WriteFlash4KBAsyncAT
	.word CTRDGi_EraseFlashChipAsyncAT
	.word CTRDGi_EraseFlash4KBAsyncAT
	.word CTRDGi_PollingSR512kCOMMON
	.word UNK_02104004
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x3D, 0x00

	.global UNK_02104048
UNK_02104048: ; 0x02104048
	.word CTRDGi_WriteFlashSectorAT
	.word CTRDGi_EraseFlashChipAT
	.word CTRDGi_EraseFlashSectorAT
	.word CTRDGi_WriteFlashSectorAsyncAT
	.word CTRDGi_EraseFlashChipAsyncAT
	.word CTRDGi_EraseFlashSectorAsyncAT
	.word CTRDGi_PollingSR512kCOMMON
	.word UNK_02104004
	.byte 0x00, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x3D, 0x00

	.global UNK_02104084
UNK_02104084: ; 0x02104084
	.byte 0x0A, 0x00, 0x0A, 0x00, 0xD0, 0x07, 0x88, 0x13

	.global UNK_0210408C
UNK_0210408C: ; 0x0210408C
	.word CTRDGi_WriteFlashSectorMX
	.word CTRDGi_EraseFlashChipMX
	.word CTRDGi_EraseFlashSectorMX
	.word CTRDGi_WriteFlashSectorAsyncMX
	.word CTRDGi_EraseFlashChipAsyncMX
	.word CTRDGi_EraseFlashSectorAsyncMX
	.word CTRDGi_PollingSR1MCOMMON
	.word UNK_02104084
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x62, 0x00, 0x13, 0x00

	.global UNK_021040C8
UNK_021040C8: ; 0x021040C8
	.byte 0x0A, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xC8, 0x00

	.global UNK_021040D0
UNK_021040D0: ; 0x021040D0
	.word CTRDGi_WriteFlashSectorLE
	.word CTRDGi_EraseFlashChipLE
	.word CTRDGi_EraseFlashSectorLE
	.word CTRDGi_WriteFlashSectorAsyncLE
	.word CTRDGi_EraseFlashChipAsyncLE
	.word CTRDGi_EraseFlashSectorAsyncLE
	.word CTRDGi_PollingSR512kCOMMON
	.word UNK_021040C8
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_0210410C
UNK_0210410C: ; 0x0210410C
	.word CTRDGi_WriteFlashSectorLE
	.word CTRDGi_EraseFlashChipLE
	.word CTRDGi_EraseFlashSectorLE
	.word CTRDGi_WriteFlashSectorAsyncLE
	.word CTRDGi_EraseFlashChipAsyncLE
	.word CTRDGi_EraseFlashSectorAsyncLE
	.word CTRDGi_PollingSR512kCOMMON
	.word UNK_021040C8
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xBF, 0x00, 0xD4, 0x00

	.global UNK_02104148
UNK_02104148: ; 0x02104148
	.byte 0x0A, 0x00, 0x0A, 0x00, 0xD0, 0x07, 0xD0, 0x07

	.global UNK_02104150
UNK_02104150: ; 0x02104150
	.word CTRDGi_WriteFlashSectorMX
	.word CTRDGi_EraseFlashChipMX
	.word CTRDGi_EraseFlashSectorMX
	.word CTRDGi_WriteFlashSectorAsyncMX
	.word CTRDGi_EraseFlashChipAsyncMX
	.word CTRDGi_EraseFlashSectorAsyncMX
	.word CTRDGi_PollingSR1MCOMMON
	.word UNK_02104148
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC2, 0x00, 0x09, 0x00

	.global UNK_0210418C
UNK_0210418C: ; 0x0210418C
	.word CTRDGi_WriteFlashSectorMX
	.word CTRDGi_EraseFlashChipMX
	.word CTRDGi_EraseFlashSectorMX
	.word CTRDGi_WriteFlashSectorAsyncMX
	.word CTRDGi_EraseFlashChipAsyncMX
	.word CTRDGi_EraseFlashSectorAsyncMX
	.word CTRDGi_PollingSR1MCOMMON
	.word UNK_02104148
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_021041C8
UNK_021041C8: ; 0x021041C8
	.byte 0x0A, 0x00, 0x0A, 0x00, 0xF4, 0x01, 0xF4, 0x01

	.global UNK_021041D0
UNK_021041D0: ; 0x021041D0
	.word CTRDGi_WriteFlashSectorMX5
	.word CTRDGi_EraseFlashChipLE
	.word CTRDGi_EraseFlashSectorLE
	.word CTRDGi_WriteFlashSectorAsyncMX5
	.word CTRDGi_EraseFlashChipAsyncLE
	.word CTRDGi_EraseFlashSectorAsyncLE
	.word CTRDGi_PollingSR512kCOMMON
	.word UNK_021041C8
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x32, 0x00, 0x1B, 0x00

	.section .bss

    .text

	arm_func_start CTRDG_IdentifyAgbBackup
CTRDG_IdentifyAgbBackup: ; 0x020DBD50
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	cmp r7, #0x1
	mov r0, #0x1
	bhi _020DBEAC
	bl OS_GetLockID
	ldr r1, _020DBED8 ; =UNK_021D6B0C
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_LockCartridge
	ldr r6, _020DBEDC ; =0x04000204
	ldr r1, _020DBEE0 ; =UNK_02103FE4
	ldrh r3, [r6, #0x0]
	ldrh r2, [r6, #0x0]
	ldr r0, _020DBEE4 ; =UNK_021D6B28
	and r4, r3, #0x3
	bic r2, r2, #0x3
	orr r2, r2, #0x3
	strh r2, [r6, #0x0]
	str r1, [r0, #0x0]
	bl CTRDGi_ReadFlashID
	ldr r2, _020DBEDC ; =0x04000204
	mov r6, r0
	ldrh r1, [r2, #0x0]
	cmp r7, #0x0
	ldreq r5, _020DBEE8 ; =UNK_02103FF4
	bic r1, r1, #0x3
	orr r1, r1, r4
	cmp r7, #0x1
	ldr r0, _020DBED8 ; =UNK_021D6B0C
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	ldreq r5, _020DBEEC ; =UNK_02103FE8
	bl OS_UnlockCartridge
	ldr r2, [r5, #0x0]
	mov r0, #0x1
	ldrh r1, [r2, #0x38]
	cmp r1, #0x0
	beq _020DBE14
	and r3, r6, #0xff
_020DBDF4:
	ldrh r1, [r2, #0x38]
	cmp r3, r1
	moveq r0, #0x0
	beq _020DBE14
	ldr r2, [r5, #0x4]!
	ldrh r1, [r2, #0x38]
	cmp r1, #0x0
	bne _020DBDF4
_020DBE14:
	ldr r2, [r2, #0x0]
	ldr r1, _020DBEF0 ; =UNK_021D6B14
	ldr r3, _020DBEF4 ; =UNK_021D6B34
	str r2, [r1, #0x0]
	ldr r1, [r5, #0x0]
	ldr r2, _020DBEF8 ; =UNK_021D6B2C
	ldr r4, [r1, #0x4]
	ldr r1, _020DBEFC ; =UNK_021D6B18
	str r4, [r3, #0x0]
	ldr r3, [r5, #0x0]
	ldr r6, _020DBF00 ; =UNK_021D6B1C
	ldr r3, [r3, #0x8]
	ldr r4, _020DBF04 ; =UNK_021D6B30
	str r3, [r2, #0x0]
	ldr r2, [r5, #0x0]
	ldr r3, _020DBF08 ; =UNK_021D6B24
	ldr r7, [r2, #0xc]
	ldr r2, _020DBEE4 ; =UNK_021D6B28
	str r7, [r1, #0x0]
	ldr r7, [r5, #0x0]
	ldr r1, _020DBF0C ; =UNK_021D6B20
	ldr r7, [r7, #0x10]
	add sp, sp, #0x4
	str r7, [r6, #0x0]
	ldr r6, [r5, #0x0]
	ldr r6, [r6, #0x14]
	str r6, [r4, #0x0]
	ldr r4, [r5, #0x0]
	ldr r4, [r4, #0x18]
	str r4, [r3, #0x0]
	ldr r3, [r5, #0x0]
	ldr r3, [r3, #0x1c]
	str r3, [r2, #0x0]
	ldr r2, [r5, #0x0]
	add r2, r2, #0x20
	str r2, [r1, #0x0]
	ldmia sp!, {r4-r7,lr}
	bx lr
_020DBEAC:
	cmp r7, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	bl OS_GetLockID
	ldr r1, _020DBF10 ; =UNK_021D6B4C
	strh r0, [r1, #0x0]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DBED8: .word UNK_021D6B0C
_020DBEDC: .word 0x04000204
_020DBEE0: .word UNK_02103FE4
_020DBEE4: .word UNK_021D6B28
_020DBEE8: .word UNK_02103FF4
_020DBEEC: .word UNK_02103FE8
_020DBEF0: .word UNK_021D6B14
_020DBEF4: .word UNK_021D6B34
_020DBEF8: .word UNK_021D6B2C
_020DBEFC: .word UNK_021D6B18
_020DBF00: .word UNK_021D6B1C
_020DBF04: .word UNK_021D6B30
_020DBF08: .word UNK_021D6B24
_020DBF0C: .word UNK_021D6B20
_020DBF10: .word UNK_021D6B4C
