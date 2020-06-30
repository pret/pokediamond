    .include "asm/macros.inc"
    .include "global.inc"

	.extern gUnk021C4918

	.section .rodata

	.global UNK_020FF49C
UNK_020FF49C: ; 0x020FF49C
	.byte 0x00, 0x03, 0x03, 0x1A, 0x12, 0x01, 0x23, 0x00

	.global UNK_020FF4A4
UNK_020FF4A4: ; 0x020FF4A4
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF4AC
UNK_020FF4AC: ; 0x020FF4AC
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF4BC
UNK_020FF4BC: ; 0x020FF4BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF4D8
UNK_020FF4D8: ; 0x020FF4D8
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

	.global UNK_021C8C58
UNK_021C8C58: ; 0x021C8C58
	.space 0x4

	.text

	thumb_func_start FUN_0208A998
FUN_0208A998: ; 0x0208A998
	ldr r3, _0208A9AC ; =OS_IRQTable
	ldr r1, _0208A9B0 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	ldr r3, _0208A9B4 ; =MI_WaitDma
	mov r0, #0x3
	bx r3
	nop
_0208A9AC: .word OS_IRQTable
_0208A9B0: .word 0x00003FF8
_0208A9B4: .word MI_WaitDma

	thumb_func_start FUN_0208A9B8
FUN_0208A9B8: ; 0x0208A9B8
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r0, _0208ABC8 ; =UNK_021C8C58
	ldr r1, [r0, #0x0]
	cmp r1, #0x1
	bne _0208A9C6
	b _0208ABC4
_0208A9C6:
	mov r1, #0x1
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl OS_GetInitArenaHi
	add r1, r0, #0x0
	mov r0, #0x0
	bl OS_SetArenaHi
	mov r0, #0x0
	bl OS_GetInitArenaLo
	add r1, r0, #0x0
	mov r0, #0x0
	bl OS_SetArenaLo
	mov r1, #0x1
	ldr r0, _0208ABCC ; =UNK_020FF4A4
	add r2, r1, #0x0
	mov r3, #0x0
	bl FUN_020166C8
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	bl OS_DisableIrqMask
	ldr r1, _0208ABD0 ; =FUN_0208A998
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _0208ABD4 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0208ABD8 ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _0208ABDC ; =gUnk021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _0208ABE0 ; =0x04000050
	mov r0, #0x0
	strh r0, [r3, #0x0]
	ldr r2, _0208ABE4 ; =0x04001050
	sub r3, #0x50
	strh r0, [r2, #0x0]
	ldr r1, [r3, #0x0]
	ldr r0, _0208ABE8 ; =0xFFFF1FFF
	sub r2, #0x50
	and r1, r0
	str r1, [r3, #0x0]
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r0, _0208ABEC ; =UNK_020FF4D8
	bl FUN_0201E66C
	mov r0, #0x0
	bl FUN_02016B94
	str r0, [sp, #0x10]
	ldr r0, _0208ABF0 ; =UNK_020FF4AC
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r0, [sp, #0x10]
	ldr r2, _0208ABF4 ; =UNK_020FF4BC
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r2, _0208ABF8 ; =0x000001F7
	mov r3, #0x2
	str r1, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_02017F18
	ldr r1, _0208ABFC ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _0208ABFC ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc8
	mov r3, #0x0
	bl NewMsgDataFromNarc
	str r0, [sp, #0xc]
	mov r0, #0x6
	lsl r0, r0, #0x6
	mov r1, #0x0
	bl String_ctor
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r0, [sp, #0x10]
	ldr r2, _0208AC00 ; =UNK_020FF49C
	add r1, sp, #0x14
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x14
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _0208ABF8 ; =0x000001F7
	add r0, sp, #0x14
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	ldr r0, [sp, #0xc]
	mov r1, #0x3
	add r2, r4, #0x0
	bl ReadMsgDataIntoString
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0x14
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl String_dtor
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	bl FUN_02032DAC
	mov r4, #0x1
_0208AB58:
	bl FUN_02000FE8
	bl FUN_0202FB80
	bl FUN_02033678
	cmp r0, #0x0
	bne _0208AB72
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl OS_WaitIrq
	b _0208AB58
_0208AB72:
	ldr r5, _0208AC04 ; =0x04000130
	ldr r4, _0208AC08 ; =0x027FFFA8
	ldr r7, _0208AC0C ; =0x00002FFF
	mov r6, #0x1
_0208AB7A:
	bl FUN_02000FE8
	ldrh r1, [r5, #0x0]
	ldrh r0, [r4, #0x0]
	orr r1, r0
	ldr r0, _0208AC0C ; =0x00002FFF
	eor r0, r1
	and r0, r7
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	tst r0, r6
	bne _0208AB9C
	mov r0, #0x1
	add r1, r0, #0x0
	bl OS_WaitIrq
	b _0208AB7A
_0208AB9C:
	ldr r1, _0208AC10 ; =0x00007FFF
	mov r0, #0x0
	bl FUN_0200E3A0
	ldr r1, _0208AC10 ; =0x00007FFF
	mov r0, #0x1
	bl FUN_0200E3A0
	add r0, sp, #0x14
	bl FUN_02019178
	ldr r0, [sp, #0xc]
	bl DestroyMsgData
	ldr r0, [sp, #0x10]
	bl FreeToHeap
	mov r0, #0x0
	bl OS_ResetSystem
_0208ABC4:
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_0208ABC8: .word UNK_021C8C58
_0208ABCC: .word UNK_020FF4A4
_0208ABD0: .word FUN_0208A998
_0208ABD4: .word 0xFFFFE0FF
_0208ABD8: .word 0x04001000
_0208ABDC: .word gUnk021C4918
_0208ABE0: .word 0x04000050
_0208ABE4: .word 0x04001050
_0208ABE8: .word 0xFFFF1FFF
_0208ABEC: .word UNK_020FF4D8
_0208ABF0: .word UNK_020FF4AC
_0208ABF4: .word UNK_020FF4BC
_0208ABF8: .word 0x000001F7
_0208ABFC: .word 0x00006C21
_0208AC00: .word UNK_020FF49C
_0208AC04: .word 0x04000130
_0208AC08: .word 0x027FFFA8
_0208AC0C: .word 0x00002FFF
_0208AC10: .word 0x00007FFF
