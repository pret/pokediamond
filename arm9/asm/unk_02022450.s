	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EE6D4
UNK_020EE6D4: ; 0x020EE6D4
	.asciz "rom"

	.text

	thumb_func_start FUN_02022450
FUN_02022450: ; 0x02022450
	push {r3, lr}
	bl FS_IsAvailable
	cmp r0, #0x0
	bne _02022460
	bl OS_Terminate
	pop {r3, pc}
_02022460:
	ldr r0, _020224BC ; =0x027FF00C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202248A
	bl CARD_Init
	mov r2, #0x16
	ldr r0, _020224C0 ; =0x027FFE00
	ldr r1, _020224C4 ; =0x027FF000
	lsl r2, r2, #0x4
	bl MI_CpuCopy8
	mov r2, #0x16
	ldr r0, _020224C0 ; =0x027FFE00
	ldr r1, _020224C8 ; =0x027FFA80
	lsl r2, r2, #0x4
	bl MI_CpuCopy8
	ldr r1, _020224CC ; =0x4A414441
	ldr r0, _020224BC ; =0x027FF00C
	str r1, [r0, #0x0]
_0202248A:
	ldr r0, _020224D0 ; =UNK_020EE6D4
	mov r1, #0x3
	bl FS_FindArchive
	ldr r1, _020224C4 ; =0x027FF000
	ldr r2, [r1, #0x48]
	str r2, [r0, #0x2c]
	ldr r2, [r1, #0x4c]
	str r2, [r0, #0x30]
	ldr r2, [r1, #0x40]
	str r2, [r0, #0x34]
	ldr r2, [r1, #0x44]
	str r2, [r0, #0x38]
	ldr r2, [r1, #0xc]
	ldr r0, _020224CC ; =0x4A414441
	cmp r2, r0
	bne _020224B4
	ldrh r1, [r1, #0x10]
	ldr r0, _020224D4 ; =0x00003130
	cmp r1, r0
	beq _020224B8
_020224B4:
	bl OS_Terminate
_020224B8:
	pop {r3, pc}
	nop
_020224BC: .word 0x027FF00C
_020224C0: .word 0x027FFE00
_020224C4: .word 0x027FF000
_020224C8: .word 0x027FFA80
_020224CC: .word 0x4A414441
_020224D0: .word UNK_020EE6D4
_020224D4: .word 0x00003130

	thumb_func_start FUN_020224D8
FUN_020224D8: ; 0x020224D8
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FS_InitFile
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _020224FC
	ldr r1, [sp, #0x24]
	ldr r0, _02022500 ; =0x027FFC2C
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl OS_ResetSystem
_020224FC:
	add sp, #0x48
	pop {r4, pc}
	.balign 4
_02022500: .word 0x027FFC2C
