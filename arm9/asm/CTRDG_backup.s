	.include "asm/macros.inc"
	.include "global.inc"

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
	ldr r1, _020DBED8 ; =0x021D6B0C
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	bl OS_LockCartridge
	ldr r6, _020DBEDC ; =0x04000204
	ldr r1, _020DBEE0 ; =0x02103FE4
	ldrh r3, [r6, #0x0]
	ldrh r2, [r6, #0x0]
	ldr r0, _020DBEE4 ; =0x021D6B28
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
	ldreq r5, _020DBEE8 ; =0x02103FF4
	bic r1, r1, #0x3
	orr r1, r1, r4
	cmp r7, #0x1
	ldr r0, _020DBED8 ; =0x021D6B0C
	strh r1, [r2, #0x0]
	ldrh r0, [r0, #0x0]
	ldreq r5, _020DBEEC ; =0x02103FE8
	bl OS_UnlockCartridge2
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
	ldr r1, _020DBEF0 ; =0x021D6B14
	ldr r3, _020DBEF4 ; =0x021D6B34
	str r2, [r1, #0x0]
	ldr r1, [r5, #0x0]
	ldr r2, _020DBEF8 ; =0x021D6B2C
	ldr r4, [r1, #0x4]
	ldr r1, _020DBEFC ; =0x021D6B18
	str r4, [r3, #0x0]
	ldr r3, [r5, #0x0]
	ldr r6, _020DBF00 ; =0x021D6B1C
	ldr r3, [r3, #0x8]
	ldr r4, _020DBF04 ; =0x021D6B30
	str r3, [r2, #0x0]
	ldr r2, [r5, #0x0]
	ldr r3, _020DBF08 ; =0x021D6B24
	ldr r7, [r2, #0xc]
	ldr r2, _020DBEE4 ; =0x021D6B28
	str r7, [r1, #0x0]
	ldr r7, [r5, #0x0]
	ldr r1, _020DBF0C ; =0x021D6B20
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
	ldr r1, _020DBF10 ; =0x021D6B4C
	strh r0, [r1, #0x0]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020DBED8: .word 0x021D6B0C
_020DBEDC: .word 0x04000204
_020DBEE0: .word 0x02103FE4
_020DBEE4: .word 0x021D6B28
_020DBEE8: .word 0x02103FF4
_020DBEEC: .word 0x02103FE8
_020DBEF0: .word 0x021D6B14
_020DBEF4: .word 0x021D6B34
_020DBEF8: .word 0x021D6B2C
_020DBEFC: .word 0x021D6B18
_020DBF00: .word 0x021D6B1C
_020DBF04: .word 0x021D6B30
_020DBF08: .word 0x021D6B24
_020DBF0C: .word 0x021D6B20
_020DBF10: .word 0x021D6B4C
