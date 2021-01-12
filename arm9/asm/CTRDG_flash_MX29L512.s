	.include "asm/macros.inc"
	.include "global.inc"

	.extern CTRDGi_EraseFlashChipAsyncLE
	.extern CTRDGi_EraseFlashChipLE
	.extern CTRDGi_EraseFlashSectorAsyncLE
	.extern CTRDGi_PollingSR512kCOMMON
	.extern UNK_021D6B08
	.extern UNK_021D6B20
	.extern UNK_021D6B0C

	.section .rodata

	.global PaMaxTime
PaMaxTime: ; 0x021041C8
	.byte 0x0A, 0x00, 0x0A, 0x00, 0xF4, 0x01, 0xF4, 0x01

	.global MN63F805MNP
MN63F805MNP: ; 0x021041D0
	.word CTRDGi_WriteFlashSectorMX5
	.word CTRDGi_EraseFlashChipLE
	.word CTRDGi_EraseFlashSectorLE
	.word CTRDGi_WriteFlashSectorAsyncMX5
	.word CTRDGi_EraseFlashChipAsyncLE
	.word CTRDGi_EraseFlashSectorAsyncLE
	.word CTRDGi_PollingSR512kCOMMON
	.word PaMaxTime
	.byte 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x32, 0x00, 0x1B, 0x00

    .text

	arm_func_start CTRDGi_WriteFlashSectorAsyncMX5
CTRDGi_WriteFlashSectorAsyncMX5: ; 0x020DD868
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	str r1, [sp, #0xc]
	strh r0, [sp, #0x20]
	ldr r1, _020DD890 ; =CTRDGi_WriteFlashSectorCoreMX5
	add r0, sp, #0x0
	bl CTRDGi_SetTask
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020DD890: .word CTRDGi_WriteFlashSectorCoreMX5

	arm_func_start CTRDGi_WriteFlashSectorMX5
CTRDGi_WriteFlashSectorMX5: ; 0x020DD894
	stmdb sp!, {lr}
	sub sp, sp, #0x24
	strh r0, [sp, #0x20]
	add r0, sp, #0x0
	str r1, [sp, #0xc]
	bl CTRDGi_WriteFlashSectorCoreMX5
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add sp, sp, #0x24
	ldmia sp!, {lr}
	bx lr

	arm_func_start CTRDGi_WriteFlashSectorCoreMX5
CTRDGi_WriteFlashSectorCoreMX5: ; 0x020DD8C0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x28
	mov r5, r0
	ldmia r5!, {r0-r3}
	add r4, sp, #0x0
	stmia r4!, {r0-r3}
	ldmia r5!, {r0-r3}
	stmia r4!, {r0-r3}
	ldr r0, _020DD9E8 ; =UNK_021D6B20
	ldr r1, [r5, #0x0]
	ldr r0, [r0, #0x0]
	str r1, [r4, #0x0]
	ldrh r5, [sp, #0x20]
	ldrh r0, [r0, #0xa]
	ldr r4, [sp, #0xc]
	cmp r5, r0
	addcs sp, sp, #0x28
	ldrhs r0, _020DD9EC ; =0x000080FF
	ldmcsia sp!, {r4-r8,lr}
	bxcs lr
	mov r0, r5
	bl CTRDGi_EraseFlashSectorLE
	movs r6, r0
	addne sp, sp, #0x28
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r0, _020DD9F0 ; =UNK_021D6B0C
	ldrh r0, [r0, #0x0]
	bl OS_LockCartridge
	ldr r7, _020DD9F4 ; =0x04000204
	ldr r0, _020DD9E8 ; =UNK_021D6B20
	ldrh r3, [r7, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r1, [r7, #0x0]
	ldr r2, [r2, #0x10]
	ldr r8, _020DD9F8 ; =UNK_021D6B08
	bic r1, r1, #0x3
	orr r1, r1, r2
	strh r1, [r7, #0x0]
	ldr r1, [r0, #0x0]
	and r7, r3, #0x3
	ldr r0, [r1, #0x4]
	strh r0, [r8, #0x0]
	ldrh r1, [r1, #0x8]
	ldrh r0, [r8, #0x0]
	mov r1, r5, lsl r1
	cmp r0, #0x0
	add r5, r1, #0xa000000
	beq _020DD9B8
_020DD984:
	mov r0, r4
	mov r1, r5
	bl CTRDGi_ProgramFlashByteLE
	movs r6, r0
	bne _020DD9B8
	ldrh r0, [r8, #0x0]
	add r4, r4, #0x1
	add r5, r5, #0x1
	sub r0, r0, #0x1
	strh r0, [r8, #0x0]
	ldrh r0, [r8, #0x0]
	cmp r0, #0x0
	bne _020DD984
_020DD9B8:
	ldr r2, _020DD9F4 ; =0x04000204
	ldr r0, _020DD9F0 ; =UNK_021D6B0C
	ldrh r1, [r2, #0x0]
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
_020DD9E8: .word UNK_021D6B20
_020DD9EC: .word 0x000080FF
_020DD9F0: .word UNK_021D6B0C
_020DD9F4: .word 0x04000204
_020DD9F8: .word UNK_021D6B08
