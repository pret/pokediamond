    .include "asm/macros.inc"
    .include "global.inc"

	.extern FX_SinCosTable_

	.section .rodata

	.global UNK_020ED64C
UNK_020ED64C: ; 0x020ED64C
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0x02
	.byte 0x02, 0x02, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00

	.global UNK_020ED668
UNK_020ED668: ; 0x020ED668
	.word FUN_02015A34

	.global UNK_020ED66C
UNK_020ED66C: ; 0x020ED66C
	.byte 0x06, 0x00, 0x00, 0x00

	.global UNK_020ED670
UNK_020ED670: ; 0x020ED670
	.byte 0x01, 0x00, 0x00, 0x00
	.word FUN_02015AEC
	.byte 0x06, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00
	.word FUN_02015BAC
	.byte 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word FUN_02015BE8
	.byte 0x03, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
	.word FUN_02015C24
	.byte 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020ED6A4
UNK_020ED6A4: ; 0x020ED6A4
	.word FUN_020151B8
	.word FUN_020151C8
	.word FUN_020151D0
	.word FUN_02015300
	.word FUN_020153E0
	.word FUN_02015218
	.word FUN_02015240
	.word FUN_02015264
	.word FUN_0201528C
	.word FUN_020152B0
	.word FUN_020152D8
	.word FUN_02015404
	.word FUN_02015428
	.word FUN_02015444
	.word FUN_02015470
	.word FUN_0201549C
	.word FUN_0201551C
	.word FUN_02015550
	.word FUN_02015588
	.word FUN_020155D0
	.word FUN_02015620
	.word FUN_020156E8
	.word FUN_02015730
	.word FUN_02015798
	.word FUN_0201585C
	.word FUN_02015868
	.word FUN_020158A0
	.word FUN_020158AC
	.word FUN_020158B8
	.word FUN_020158C4
	.word FUN_020158D0
	.word FUN_020157EC
	.word FUN_02015800
	.word FUN_02015840

	.text

	thumb_func_start FUN_02014BF4
FUN_02014BF4: ; 0x02014BF4
	push {r3-r7, lr}
	add r7, r1, #0x0
	mov r1, #0xc
	add r5, r0, #0x0
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	strb r6, [r4, #0x8]
	mov r0, #0x1d
	strb r7, [r4, #0x9]
	lsl r0, r0, #0x4
	add r6, r7, #0x0
	mul r6, r0
	add r0, r5, #0x0
	add r1, r6, #0x0
	str r5, [r4, #0x4]
	bl AllocFromHeap
	mov r1, #0x0
	add r2, r6, #0x0
	str r0, [r4, #0x0]
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02014C28
FUN_02014C28: ; 0x02014C28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02014C3C
FUN_02014C3C: ; 0x02014C3C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x19
	blo _02014C48
	bl GF_AssertFail
_02014C48:
	ldr r0, _02014C50 ; =UNK_020ED64C
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_02014C50: .word UNK_020ED64C

	thumb_func_start FUN_02014C54
FUN_02014C54: ; 0x02014C54
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	str r3, [sp, #0x4]
	add r0, r2, #0x0
	ldrh r6, [r0, #0x0]
	ldrh r0, [r0, #0x2]
	add r7, r1, #0x0
	ldrb r1, [r5, #0x9]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	str r2, [sp, #0x0]
	cmp r0, r1
	blo _02014C74
	bl GF_AssertFail
_02014C74:
	ldr r0, [sp, #0x4]
	mov r1, #0x1d
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, #0x0]
	mul r4, r1
	add r0, r0, r4
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _02014C8C
	bl GF_AssertFail
_02014C8C:
	ldr r0, [r5, #0x0]
	mov r2, #0x1d
	add r0, r0, r4
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	add r0, r0, r4
	str r1, [r0, #0x10]
	ldr r0, [r5, #0x0]
	cmp r6, #0x86
	str r7, [r0, r4]
	blt _02014CAE
	mov r6, #0x0
	str r6, [sp, #0x8]
_02014CAE:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	str r6, [r0, #0x14]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x0
	beq _02014CC0
	ldr r0, [sp, #0x0]
	ldrb r2, [r0, #0x4]
	b _02014CC2
_02014CC0:
	mov r2, #0x0
_02014CC2:
	ldr r0, [r5, #0x0]
	add r1, r0, r4
	mov r0, #0x73
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	ldr r1, [r5, #0x0]
	ldr r2, [r5, #0x4]
	add r1, r1, r4
	ldr r1, [r1, #0x14]
	mov r0, #0x5e
	bl AllocAtEndAndReadWholeNarcMemberByIdPair
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	add r1, r1, r4
	str r0, [r1, #0x8]
	ldr r0, [r5, #0x0]
	mov r6, #0x1c
	add r1, r0, r4
	ldr r0, [r1, #0x8]
	str r0, [r1, #0xc]
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	str r2, [r0, #0x1c]
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	str r2, [r0, #0x20]
	ldr r0, [r5, #0x0]
	add r1, r0, r4
	ldr r0, _02014D74 ; =0x000001CD
	strb r2, [r1, r0]
	ldr r1, [r5, #0x0]
	add r3, r1, r4
	add r1, r0, #0x1
	strb r6, [r3, r1]
	ldr r1, [r5, #0x0]
	add r0, r0, #0x2
	add r1, r1, r4
	strb r2, [r1, r0]
	ldr r1, [r5, #0x0]
	ldr r0, _02014D78 ; =FUN_02014DD8
	add r1, r1, r4
	bl FUN_0200CA44
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r0, r4
	ldr r0, [sp, #0x8]
	str r0, [r1, #0x54]
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0200782C
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x58]
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0200782C
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x5c]
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	add r1, r1, r4
	str r0, [r1, #0x60]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x64]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x68]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x6c]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x70]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x74]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x78]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02014D74: .word 0x000001CD
_02014D78: .word FUN_02014DD8

	thumb_func_start FUN_02014D7C
FUN_02014D7C: ; 0x02014D7C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x9]
	add r4, r1, #0x0
	cmp r4, r0
	blo _02014D8C
	bl GF_AssertFail
_02014D8C:
	mov r0, #0x1d
	lsl r0, r0, #0x4
	ldr r1, [r5, #0x0]
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0x20]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014D9C
FUN_02014D9C: ; 0x02014D9C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1d
	lsl r0, r0, #0x4
	add r4, r1, #0x0
	mul r4, r0
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02014DD6
	bl FUN_0200CAB4
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	add r1, r1, r4
	str r0, [r1, #0x4]
	ldr r1, [r5, #0x0]
	mov r2, #0x1
	add r1, r1, r4
	str r2, [r1, #0x20]
	ldr r1, [r5, #0x0]
	add r1, r1, r4
	str r0, [r1, #0x10]
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	bl FreeToHeap
_02014DD6:
	pop {r3-r5, pc}

	thumb_func_start FUN_02014DD8
FUN_02014DD8: ; 0x02014DD8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x54]
	cmp r0, #0x0
	bne _02014DEC
	add r0, r4, #0x0
	bl FUN_02014E10
	b _02014DF0
_02014DEC:
	sub r0, r0, #0x1
	str r0, [r4, #0x54]
_02014DF0:
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	beq _02014E0E
	mov r0, #0x1
	str r0, [r4, #0x20]
	mov r0, #0x0
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_0200CAB4
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x8]
	bl FreeToHeap
_02014E0E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02014E10
FUN_02014E10: ; 0x02014E10
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r6, #0x0
	str r6, [r5, #0x18]
	add r7, r5, #0x0
	str r6, [r5, #0x44]
	add r4, r6, #0x0
	add r7, #0x7c
_02014E20:
	mov r0, #0x54
	add r1, r4, #0x0
	mul r1, r0
	add r0, r7, r1
	ldr r1, [r7, r1]
	cmp r1, #0x0
	beq _02014E4E
	add r1, r0, #0x0
	add r1, #0x2d
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02014E40
	ldr r2, [r0, #0x50]
	add r1, r5, #0x0
	blx r2
	b _02014E54
_02014E40:
	add r1, r0, #0x0
	add r1, #0x2d
	ldrb r1, [r1, #0x0]
	add r0, #0x2d
	sub r1, r1, #0x1
	strb r1, [r0, #0x0]
	b _02014E54
_02014E4E:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02014E54:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02014E20
	cmp r6, #0x4
	bne _02014E68
	ldr r0, _02014EFC ; =0x000001CD
	mov r1, #0x0
	strb r1, [r5, r0]
_02014E68:
	ldr r0, _02014EFC ; =0x000001CD
	ldrb r1, [r5, r0]
	cmp r1, #0x0
	beq _02014E7E
	add r0, r5, #0x0
	bl FUN_020156E8
	add r0, r5, #0x0
	bl FUN_02015730
	pop {r3-r7, pc}
_02014E7E:
	add r0, r0, #0x2
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	beq _02014E96
	ldr r0, [r5, #0x0]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02014EF8
	ldr r0, _02014F00 ; =0x000001CF
	mov r1, #0x0
	strb r1, [r5, r0]
_02014E96:
	add r6, r5, #0x0
	add r4, r5, #0x0
	ldr r7, _02014F04 ; =UNK_020ED6A4
	add r6, #0xc
	add r4, #0x44
_02014EA0:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x0]
	cmp r0, #0x22
	blo _02014EB2
	bl GF_AssertFail
_02014EB2:
	ldr r1, [r5, #0xc]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	lsl r1, r1, #0x2
	ldr r1, [r7, r1]
	blx r1
	ldr r0, [r5, #0x1c]
	cmp r0, #0x0
	bne _02014EF8
	ldr r0, [r6, #0x0]
	add r0, r0, #0x4
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	bne _02014EF8
	ldr r0, _02014EFC ; =0x000001CD
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	beq _02014EE6
	add r0, r5, #0x0
	bl FUN_020156E8
	add r0, r5, #0x0
	bl FUN_02015730
	pop {r3-r7, pc}
_02014EE6:
	mov r0, #0x1
	ldr r1, [r5, #0x44]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02014EA0
	bl GF_AssertFail
	mov r0, #0x1
	str r0, [r5, #0x1c]
_02014EF8:
	pop {r3-r7, pc}
	nop
_02014EFC: .word 0x000001CD
_02014F00: .word 0x000001CF
_02014F04: .word UNK_020ED6A4

	thumb_func_start FUN_02014F08
FUN_02014F08: ; 0x02014F08
	push {r4, lr}
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	cmp r2, #0x1
	beq _02014F16
	bl GF_AssertFail
_02014F16:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02014F1C
FUN_02014F1C: ; 0x02014F1C
	ldr r3, _02014F24 ; =FUN_02014F08
	add r2, r1, #0x0
	mov r1, #0x0
	bx r3
	.balign 4
_02014F24: .word FUN_02014F08

	thumb_func_start FUN_02014F28
FUN_02014F28: ; 0x02014F28
	ldr r3, _02014F30 ; =FUN_02014F1C
	mov r1, #0x1
	bx r3
	nop
_02014F30: .word FUN_02014F1C

	thumb_func_start FUN_02014F34
FUN_02014F34: ; 0x02014F34
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r3, #0x0
	add r0, #0x7c
	mov r2, #0x54
_02014F3E:
	add r1, r3, #0x0
	mul r1, r2
	add r4, r0, r1
	ldr r1, [r0, r1]
	cmp r1, #0x0
	bne _02014F68
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x54
	bl MI_CpuFill8
	mov r0, #0x1
	str r0, [r4, #0x0]
	mov r0, #0xc
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, _02014F7C ; =UNK_020ED668
	ldr r0, [r0, r1]
	str r0, [r4, #0x50]
	add r0, r4, #0x0
	pop {r3-r5, pc}
_02014F68:
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x4
	blo _02014F3E
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02014F7C: .word UNK_020ED668

	thumb_func_start FUN_02014F80
FUN_02014F80: ; 0x02014F80
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r0, #0xc]
	add r1, r1, #0x4
	str r1, [r0, #0xc]
	add r0, r1, #0x0
	bl FUN_02014F28
	str r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02014F94
FUN_02014F94: ; 0x02014F94
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r0, #0xc]
	add r1, r1, #0x4
	str r1, [r0, #0xc]
	add r0, r1, #0x0
	bl FUN_02014F28
	strb r0, [r4, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02014FA8
FUN_02014FA8: ; 0x02014FA8
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r0, #0xc]
	add r1, r1, #0x4
	str r1, [r0, #0xc]
	add r0, r1, #0x0
	bl FUN_02014F28
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r0, #0x8
	blo _02014FC4
	bl GF_AssertFail
_02014FC4:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02014FC8
FUN_02014FC8: ; 0x02014FC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02014FA8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014FA8
	pop {r3-r5, pc}

	thumb_func_start FUN_02014FDC
FUN_02014FDC: ; 0x02014FDC
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02014FA8
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x12
	bne _0201501C
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	add r1, r6, #0x0
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02014F80
	add sp, #0x4
	pop {r3-r6, pc}
_0201501C:
	cmp r0, #0x13
	bne _02015048
	add r1, sp, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	add r2, #0x1
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r1, [r0, #0x2]
	add sp, #0x4
	lsl r1, r1, #0x2
	add r1, r5, r1
	ldr r1, [r1, #0x24]
	str r1, [r4, #0x0]
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r6, #0x0]
	pop {r3-r6, pc}
_02015048:
	bl GF_AssertFail
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_02015050
FUN_02015050: ; 0x02015050
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02014FA8
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x12
	bne _02015082
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014F80
	b _020150A2
_02015082:
	cmp r0, #0x13
	bne _0201509E
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x0]
	b _020150A2
_0201509E:
	bl GF_AssertFail
_020150A2:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x12
	bne _020150B6
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02014F80
	add sp, #0x4
	pop {r3-r6, pc}
_020150B6:
	cmp r0, #0x13
	bne _020150D4
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r6, #0x0]
	pop {r3-r6, pc}
_020150D4:
	bl GF_AssertFail
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_020150DC
FUN_020150DC: ; 0x020150DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r2, sp, #0x0
	add r2, #0x3
	add r5, r0, #0x0
	add r6, r3, #0x0
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	add r1, sp, #0x0
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r7, [r0, #0x24]
	add r0, r5, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _02015112
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02014F80
	b _02015132
_02015112:
	cmp r0, #0x15
	bne _0201512E
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [r6, #0x0]
	b _02015132
_0201512E:
	bl GF_AssertFail
_02015132:
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _0201514C
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _0201516C
_0201514C:
	cmp r0, #0x15
	bne _02015168
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _0201516C
_02015168:
	bl GF_AssertFail
_0201516C:
	ldr r0, [sp, #0x4]
	add r0, r7, r0
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x10
	sub r1, r1, r2
	mov r0, #0x10
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02015184
FUN_02015184: ; 0x02015184
	ldr r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	sub r0, r2, r0
	bpl _02015190
	mov r0, #0xf
	bx lr
_02015190:
	cmp r0, #0x0
	ble _02015198
	mov r0, #0x10
	bx lr
_02015198:
	mov r0, #0x11
	bx lr

	thumb_func_start FUN_0201519C
FUN_0201519C: ; 0x0201519C
	add r2, r0, #0x0
	ldr r0, [r2, #0x0]
	ldr r2, [r2, #0x74]
	mov r1, #0x1
	neg r3, r2
	asr r2, r3, #0x2
	lsr r2, r2, #0x1d
	add r2, r3, r2
	ldr r3, _020151B4 ; =FUN_020079E0
	asr r2, r2, #0x3
	bx r3
	nop
_020151B4: .word FUN_020079E0

	thumb_func_start FUN_020151B8
FUN_020151B8: ; 0x020151B8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020151D0
	mov r0, #0x1
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	pop {r4, pc}

	thumb_func_start FUN_020151C8
FUN_020151C8: ; 0x020151C8
	mov r1, #0x1
	str r1, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start FUN_020151D0
FUN_020151D0: ; 0x020151D0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r4, #0x58]
	mov r1, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x0]
	ldr r2, [r4, #0x5c]
	mov r1, #0x1
	bl FUN_02007558
	ldr r0, [r4, #0x0]
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x0]
	mov r1, #0xa
	mov r2, #0x0
	bl FUN_02007558
	mov r1, #0xc
	add r2, r1, #0x0
	ldr r0, [r4, #0x0]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0x0
	ldr r0, [r4, #0x0]
	add r2, #0xf3
	bl FUN_02007558
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015218
FUN_02015218: ; 0x02015218
	push {r3-r4, lr}
	sub sp, #0x4
	add r1, sp, #0x0
	add r1, #0x1
	add r2, sp, #0x0
	add r4, r0, #0x0
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	ldrb r0, [r0, #0x1]
	lsl r1, r1, #0x2
	add r1, r4, r1
	lsl r0, r0, #0x2
	ldr r1, [r1, #0x24]
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015240
FUN_02015240: ; 0x02015240
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02014FDC
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r1, r1, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_02015264
FUN_02015264: ; 0x02015264
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02014FDC
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r2, r1, #0x0
	mul r2, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r2, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201528C
FUN_0201528C: ; 0x0201528C
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02015050
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	sub r1, r1, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_020152B0
FUN_020152B0: ; 0x020152B0
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02015050
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl _s32_div_f
	add r1, sp, #0x0
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	str r0, [r1, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020152D8
FUN_020152D8: ; 0x020152D8
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_02015050
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl _s32_div_f
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015300
FUN_02015300: ; 0x02015300
	push {r3-r5, lr}
	sub sp, #0x10
	add r1, sp, #0x0
	add r5, r0, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _02015334
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	add r1, sp, #0x8
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_02014F80
	b _02015362
_02015334:
	cmp r0, #0x15
	bne _0201535E
	add r1, sp, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	add r2, #0x2
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r1, [r0, #0x3]
	lsl r1, r1, #0x2
	add r1, r5, r1
	ldr r1, [r1, #0x24]
	str r1, [sp, #0xc]
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x8]
	b _02015362
_0201535E:
	bl GF_AssertFail
_02015362:
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x11
	bls _02015378
	bl GF_AssertFail
_02015378:
	add r0, sp, #0xc
	add r1, sp, #0x8
	bl FUN_02015184
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x14
	bne _020153A6
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	bl FUN_02014FA8
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _020153CA
_020153A6:
	cmp r0, #0x15
	bne _020153C6
	add r1, sp, #0x0
	add r2, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x3
	add r2, #0x2
	bl FUN_02014FC8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _020153CA
_020153C6:
	bl GF_AssertFail
_020153CA:
	add r0, sp, #0x0
	ldrb r1, [r0, #0x1]
	cmp r1, r4
	bne _020153DC
	ldrb r0, [r0, #0x3]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x2
	add r0, r5, r0
	str r1, [r0, #0x24]
_020153DC:
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_020153E0
FUN_020153E0: ; 0x020153E0
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	ldr r0, [r4, #0xc]
	add r0, r0, #0x4
	str r0, [r4, #0xc]
	bl FUN_02014F28
	add r1, sp, #0x0
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x2
	add r1, r4, r1
	str r0, [r1, #0x24]
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02015404
FUN_02015404: ; 0x02015404
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x50]
	cmp r0, #0x0
	beq _02015412
	bl GF_AssertFail
_02015412:
	ldr r0, [r4, #0xc]
	add r0, r0, #0x4
	str r0, [r4, #0xc]
	str r0, [r4, #0x50]
	ldr r0, [r4, #0xc]
	bl FUN_02014F28
	str r0, [r4, #0x48]
	mov r0, #0x0
	str r0, [r4, #0x4c]
	pop {r4, pc}

	thumb_func_start FUN_02015428
FUN_02015428: ; 0x02015428
	ldr r1, [r0, #0x4c]
	add r2, r1, #0x1
	str r2, [r0, #0x4c]
	ldr r1, [r0, #0x48]
	cmp r2, r1
	blt _0201543E
	mov r1, #0x0
	str r1, [r0, #0x50]
	str r1, [r0, #0x4c]
	str r1, [r0, #0x48]
	bx lr
_0201543E:
	ldr r1, [r0, #0x50]
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02015444
FUN_02015444: ; 0x02015444
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	add r2, sp, #0x0
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x4]
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldr r2, [r2, #0x24]
	bl FUN_02007558
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015470
FUN_02015470: ; 0x02015470
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	add r2, sp, #0x0
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x4]
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldr r2, [r2, #0x24]
	bl FUN_020079E0
	add sp, #0x8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201549C
FUN_0201549C: ; 0x0201549C
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x8
	add r4, r0, #0x0
	bl FUN_02014F80
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x14
	bne _020154C4
	add r0, r4, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _020154E4
_020154C4:
	cmp r0, #0x15
	bne _020154E0
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _020154E4
_020154E0:
	bl GF_AssertFail
_020154E4:
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x16
	bne _02015502
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	bl FUN_02007558
	add sp, #0xc
	pop {r3-r4, pc}
_02015502:
	cmp r0, #0x17
	bne _02015514
	ldr r0, [r4, #0x0]
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0x4]
	bl FUN_020079E0
	add sp, #0xc
	pop {r3-r4, pc}
_02015514:
	bl GF_AssertFail
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0201551C
FUN_0201551C: ; 0x0201551C
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_020150DC
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x4]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201554C ; =FX_SinCosTable_
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r1, r0, #0xc
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0201554C: .word FX_SinCosTable_

	thumb_func_start FUN_02015550
FUN_02015550: ; 0x02015550
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x0
	add r2, sp, #0x8
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_020150DC
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x4]
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015584 ; =FX_SinCosTable_
	ldrsh r1, [r1, r2]
	mul r1, r0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	asr r1, r1, #0xc
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r1, [r0, #0x24]
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_02015584: .word FX_SinCosTable_

	thumb_func_start FUN_02015588
FUN_02015588: ; 0x02015588
	push {r3-r4, lr}
	sub sp, #0x4
	add r1, sp, #0x0
	add r4, r0, #0x0
	add r1, #0x1
	bl FUN_02014FA8
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	cmp r1, #0x8
	bne _020155B4
	ldrb r0, [r0, #0x1]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x60]
	pop {r3-r4, pc}
_020155B4:
	cmp r1, #0x9
	bne _020155C6
	ldrb r0, [r0, #0x1]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x64]
	pop {r3-r4, pc}
_020155C6:
	bl GF_AssertFail
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020155D0
FUN_020155D0: ; 0x020155D0
	push {r3-r4, lr}
	sub sp, #0x4
	add r1, sp, #0x0
	add r4, r0, #0x0
	add r1, #0x1
	bl FUN_02014FA8
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r1, [r0, #0x0]
	cmp r1, #0x8
	bne _02015600
	ldrb r0, [r0, #0x1]
	ldr r1, [r4, #0x60]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	add r0, r1, r0
	str r0, [r4, #0x60]
	pop {r3-r4, pc}
_02015600:
	cmp r1, #0x9
	bne _02015616
	ldrb r0, [r0, #0x1]
	ldr r1, [r4, #0x64]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	add r0, r1, r0
	str r0, [r4, #0x64]
	pop {r3-r4, pc}
_02015616:
	bl GF_AssertFail
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015620
FUN_02015620: ; 0x02015620
	push {r3-r5, lr}
	sub sp, #0x8
	add r1, sp, #0x0
	add r1, #0x3
	add r5, r0, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x3]
	cmp r0, #0x8
	bne _0201563C
	add r4, r5, #0x0
	add r4, #0x60
	b _0201567C
_0201563C:
	cmp r0, #0x9
	bne _02015646
	add r4, r5, #0x0
	add r4, #0x64
	b _0201567C
_02015646:
	cmp r0, #0xa
	bne _02015650
	add r4, r5, #0x0
	add r4, #0x68
	b _0201567C
_02015650:
	cmp r0, #0xb
	bne _0201565A
	add r4, r5, #0x0
	add r4, #0x6c
	b _0201567C
_0201565A:
	cmp r0, #0xc
	bne _02015664
	add r4, r5, #0x0
	add r4, #0x70
	b _0201567C
_02015664:
	cmp r0, #0xd
	bne _0201566E
	add r4, r5, #0x0
	add r4, #0x74
	b _0201567C
_0201566E:
	cmp r0, #0xe
	bne _02015678
	add r4, r5, #0x0
	add r4, #0x78
	b _0201567C
_02015678:
	bl GF_AssertFail
_0201567C:
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r0, #0x14
	bne _02015698
	add r0, r5, #0x0
	add r1, sp, #0x4
	bl FUN_02014F80
	b _020156B8
_02015698:
	cmp r0, #0x15
	bne _020156B4
	add r1, sp, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	bl FUN_02014FA8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x2
	add r0, r5, r0
	ldr r0, [r0, #0x24]
	str r0, [sp, #0x4]
	b _020156B8
_020156B4:
	bl GF_AssertFail
_020156B8:
	add r0, r5, #0x0
	add r1, sp, #0x0
	bl FUN_02014F94
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x16
	bne _020156D0
	ldr r0, [sp, #0x4]
	add sp, #0x8
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
_020156D0:
	cmp r0, #0x17
	bne _020156E0
	ldr r0, [sp, #0x4]
	ldr r1, [r4, #0x0]
	add sp, #0x8
	add r0, r1, r0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
_020156E0:
	bl GF_AssertFail
	add sp, #0x8
	pop {r3-r5, pc}

	thumb_func_start FUN_020156E8
FUN_020156E8: ; 0x020156E8
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x73
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ldr r0, [r4, #0x0]
	beq _0201570A
	ldr r3, [r4, #0x60]
	ldr r2, [r4, #0x68]
	ldr r5, [r4, #0x58]
	add r2, r3, r2
	mov r1, #0x0
	sub r2, r5, r2
	bl FUN_02007558
	b _0201571A
_0201570A:
	ldr r3, [r4, #0x58]
	ldr r2, [r4, #0x60]
	ldr r5, [r4, #0x68]
	add r2, r3, r2
	mov r1, #0x0
	add r2, r5, r2
	bl FUN_02007558
_0201571A:
	ldr r3, [r4, #0x5c]
	ldr r2, [r4, #0x64]
	ldr r5, [r4, #0x6c]
	add r2, r3, r2
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	add r2, r5, r2
	bl FUN_02007558
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02015730
FUN_02015730: ; 0x02015730
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0xc
	add r2, r1, #0x0
	ldr r3, [r4, #0x70]
	add r2, #0xf4
	ldr r0, [r4, #0x0]
	add r2, r3, r2
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0x0
	ldr r3, [r4, #0x74]
	add r2, #0xf3
	ldr r0, [r4, #0x0]
	add r2, r3, r2
	bl FUN_02007558
	ldr r2, [r4, #0x78]
	ldr r0, [r4, #0x0]
	lsl r2, r2, #0x10
	mov r1, #0x9
	lsr r2, r2, #0x10
	bl FUN_02007558
	ldr r0, _02015794 ; =0x000001CE
	ldrb r0, [r4, r0]
	cmp r0, #0x1b
	bne _02015778
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	bge _02015792
	add r0, r4, #0x0
	bl FUN_0201519C
	pop {r4, pc}
_02015778:
	cmp r0, #0x1d
	bne _0201578A
	ldr r0, [r4, #0x74]
	cmp r0, #0x0
	beq _02015792
	add r0, r4, #0x0
	bl FUN_0201519C
	pop {r4, pc}
_0201578A:
	cmp r0, #0x1c
	beq _02015792
	bl GF_AssertFail
_02015792:
	pop {r4, pc}
	.balign 4
_02015794: .word 0x000001CE

	thumb_func_start FUN_02015798
FUN_02015798: ; 0x02015798
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02014FA8
	ldr r0, [r4, #0xc]
	add r0, r0, #0x4
	str r0, [r4, #0xc]
	bl FUN_02014F28
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x8
	beq _020157BA
	cmp r0, #0xa
	bne _020157CA
_020157BA:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x68]
	pop {r3-r4, pc}
_020157CA:
	cmp r0, #0x9
	beq _020157D2
	cmp r0, #0xb
	bne _020157E2
_020157D2:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	add sp, #0x4
	lsl r0, r0, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x6c]
	pop {r3-r4, pc}
_020157E2:
	bl GF_AssertFail
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020157EC
FUN_020157EC: ; 0x020157EC
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x54
	bl FUN_02014F80
	mov r0, #0x1
	str r0, [r4, #0x18]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015800
FUN_02015800: ; 0x02015800
	push {r3-r4, lr}
	sub sp, #0xc
	add r1, sp, #0x4
	add r1, #0x2
	add r4, r0, #0x0
	bl FUN_02014F94
	add r1, sp, #0x4
	add r0, r4, #0x0
	add r1, #0x1
	bl FUN_02014F94
	add r0, r4, #0x0
	add r1, sp, #0x4
	bl FUN_02014F94
	add r0, r4, #0x0
	add r1, sp, #0x8
	bl FUN_02014F80
	ldr r0, [sp, #0x8]
	add r3, sp, #0x4
	str r0, [sp, #0x0]
	ldrb r1, [r3, #0x2]
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_02007E68
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02015840
FUN_02015840: ; 0x02015840
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02007F20
	cmp r0, #0x0
	beq _02015856
	ldr r0, _02015858 ; =0x000001CF
	mov r1, #0x1
	strb r1, [r4, r0]
	str r1, [r4, #0x18]
_02015856:
	pop {r4, pc}
	.balign 4
_02015858: .word 0x000001CF

	thumb_func_start FUN_0201585C
FUN_0201585C: ; 0x0201585C
	ldr r1, _02015864 ; =0x000001CD
	mov r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_02015864: .word 0x000001CD

	thumb_func_start FUN_02015868
FUN_02015868: ; 0x02015868
	push {r4, lr}
	ldr r1, _0201589C ; =0x000001CE
	add r4, r0, #0x0
	add r1, r4, r1
	bl FUN_02014F94
	ldr r0, _0201589C ; =0x000001CE
	mov r1, #0x1
	ldrb r0, [r4, r0]
	add r2, r1, #0x0
	cmp r0, #0x1b
	beq _02015886
	cmp r0, #0x1d
	beq _02015886
	mov r2, #0x0
_02015886:
	cmp r2, #0x0
	bne _02015890
	cmp r0, #0x1c
	beq _02015890
	mov r1, #0x0
_02015890:
	cmp r1, #0x0
	bne _02015898
	bl GF_AssertFail
_02015898:
	pop {r4, pc}
	nop
_0201589C: .word 0x000001CE

	thumb_func_start FUN_020158A0
FUN_020158A0: ; 0x020158A0
	ldr r3, _020158A8 ; =FUN_0201598C
	mov r1, #0x0
	bx r3
	nop
_020158A8: .word FUN_0201598C

	thumb_func_start FUN_020158AC
FUN_020158AC: ; 0x020158AC
	ldr r3, _020158B4 ; =FUN_0201598C
	mov r1, #0x1
	bx r3
	nop
_020158B4: .word FUN_0201598C

	thumb_func_start FUN_020158B8
FUN_020158B8: ; 0x020158B8
	ldr r3, _020158C0 ; =FUN_0201598C
	mov r1, #0x2
	bx r3
	nop
_020158C0: .word FUN_0201598C

	thumb_func_start FUN_020158C4
FUN_020158C4: ; 0x020158C4
	ldr r3, _020158CC ; =FUN_0201598C
	mov r1, #0x3
	bx r3
	nop
_020158CC: .word FUN_0201598C

	thumb_func_start FUN_020158D0
FUN_020158D0: ; 0x020158D0
	ldr r3, _020158D8 ; =FUN_0201598C
	mov r1, #0x4
	bx r3
	nop
_020158D8: .word FUN_0201598C

	thumb_func_start FUN_020158DC
FUN_020158DC: ; 0x020158DC
	push {r3, lr}
	cmp r0, #0x18
	bne _020158E8
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	pop {r3, pc}
_020158E8:
	cmp r0, #0x19
	bne _020158F6
	ldr r1, [r1, #0x0]
	ldr r0, [r2, #0x0]
	add r0, r1, r0
	str r0, [r3, #0x0]
	pop {r3, pc}
_020158F6:
	cmp r0, #0x1a
	bne _02015904
	ldr r1, [r3, #0x0]
	ldr r0, [r2, #0x0]
	add r0, r1, r0
	str r0, [r3, #0x0]
	pop {r3, pc}
_02015904:
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201590C
FUN_0201590C: ; 0x0201590C
	push {r3, lr}
	sub r0, #0x23
	cmp r0, #0x4
	bhi _02015984
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015920: ; jump table (using 16-bit offset)
	.short _0201592A - _02015920 - 2; case 0
	.short _0201593C - _02015920 - 2; case 1
	.short _0201594E - _02015920 - 2; case 2
	.short _02015960 - _02015920 - 2; case 3
	.short _02015972 - _02015920 - 2; case 4
_0201592A:
	add r0, r1, #0x0
	add r0, #0x3c
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x68
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x68]
	str r0, [r1, #0x30]
	pop {r3, pc}
_0201593C:
	add r0, r1, #0x0
	add r0, #0x40
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x6c
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x6c]
	str r0, [r1, #0x30]
	pop {r3, pc}
_0201594E:
	add r0, r1, #0x0
	add r0, #0x44
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x70
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x70]
	str r0, [r1, #0x30]
	pop {r3, pc}
_02015960:
	add r0, r1, #0x0
	add r0, #0x48
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x74
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x74]
	str r0, [r1, #0x30]
	pop {r3, pc}
_02015972:
	add r0, r1, #0x0
	add r0, #0x4c
	str r0, [r1, #0x24]
	add r0, r2, #0x0
	add r0, #0x78
	str r0, [r1, #0x28]
	ldr r0, [r2, #0x78]
	str r0, [r1, #0x30]
	pop {r3, pc}
_02015984:
	bl GF_AssertFail
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201598C
FUN_0201598C: ; 0x0201598C
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	add r5, r0, #0x0
	bl FUN_02014F34
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	add r1, #0x2c
	bl FUN_02014F94
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	add r1, #0x2d
	bl FUN_02014F94
	mov r0, #0xc
	mul r0, r6
	ldr r1, _02015A28 ; =UNK_020ED66C
	str r0, [sp, #0x0]
	ldr r0, [r1, r0]
	mov r4, #0x0
	cmp r0, #0x0
	ble _020159E2
	ldr r1, _02015A2C ; =UNK_020ED668
	ldr r0, [sp, #0x0]
	add r6, r1, r0
	ldr r0, [sp, #0x4]
	add r7, r0, #0x4
_020159CC:
	lsl r1, r4, #0x2
	add r0, r5, #0x0
	add r1, r7, r1
	bl FUN_02014F80
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [r6, #0x4]
	cmp r4, r0
	blt _020159CC
_020159E2:
	ldr r1, _02015A30 ; =UNK_020ED670
	ldr r0, [sp, #0x0]
	add r2, r5, #0x0
	ldr r0, [r1, r0]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x4]
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201590C
	ldr r0, [sp, #0x4]
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02015A14
	ldr r0, [sp, #0x4]
	add r1, r5, #0x0
	add r2, r0, #0x0
	ldr r2, [r2, #0x50]
	blx r2
	add sp, #0x8
	pop {r3-r7, pc}
_02015A14:
	ldr r0, [sp, #0x4]
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	ldr r0, [sp, #0x4]
	add r0, #0x2d
	str r0, [sp, #0x4]
	strb r1, [r0, #0x0]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02015A28: .word UNK_020ED66C
_02015A2C: .word UNK_020ED668
_02015A30: .word UNK_020ED670

	thumb_func_start FUN_02015A34
FUN_02015A34: ; 0x02015A34
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x10]
	add r0, r0, #0x1
	ldr r2, [r4, #0x14]
	mul r0, r1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r4, #0x4]
	sub r0, #0x1e
	cmp r0, #0x3
	bhi _02015AC0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015A5C: ; jump table (using 16-bit offset)
	.short _02015A64 - _02015A5C - 2; case 0
	.short _02015A78 - _02015A5C - 2; case 1
	.short _02015A90 - _02015A5C - 2; case 2
	.short _02015AA6 - _02015A5C - 2; case 3
_02015A64:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015AE8 ; =FX_SinCosTable_
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r1, r0, #0xc
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015AC4
_02015A78:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015AE8 ; =FX_SinCosTable_
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	ldr r0, [r4, #0x24]
	asr r1, r1, #0xc
	str r1, [r0, #0x0]
	b _02015AC4
_02015A90:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015AE8 ; =FX_SinCosTable_
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r0, r0, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015AC4
_02015AA6:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015AE8 ; =FX_SinCosTable_
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	asr r0, r1, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015AC4
_02015AC0:
	bl GF_AssertFail
_02015AC4:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	blt _02015AE6
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015AE6:
	pop {r4, pc}
	.balign 4
_02015AE8: .word FX_SinCosTable_

	thumb_func_start FUN_02015AEC
FUN_02015AEC: ; 0x02015AEC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x10]
	add r0, r0, #0x1
	mul r0, r1
	ldr r1, [r4, #0x18]
	bl _s32_div_f
	ldr r1, [r4, #0x14]
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r4, #0x4]
	sub r0, #0x1e
	cmp r0, #0x3
	bhi _02015B7E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02015B1A: ; jump table (using 16-bit offset)
	.short _02015B22 - _02015B1A - 2; case 0
	.short _02015B36 - _02015B1A - 2; case 1
	.short _02015B4E - _02015B1A - 2; case 2
	.short _02015B64 - _02015B1A - 2; case 3
_02015B22:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015BA8 ; =FX_SinCosTable_
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r1, r0, #0xc
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015B82
_02015B36:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015BA8 ; =FX_SinCosTable_
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	ldr r0, [r4, #0x24]
	asr r1, r1, #0xc
	str r1, [r0, #0x0]
	b _02015B82
_02015B4E:
	asr r0, r1, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02015BA8 ; =FX_SinCosTable_
	ldr r2, [r4, #0xc]
	ldrsh r0, [r0, r1]
	mul r0, r2
	asr r0, r0, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015B82
_02015B64:
	asr r1, r1, #0x4
	lsl r1, r1, #0x1
	add r1, r1, #0x1
	lsl r2, r1, #0x1
	ldr r1, _02015BA8 ; =FX_SinCosTable_
	ldr r0, [r4, #0xc]
	ldrsh r1, [r1, r2]
	mul r1, r0
	asr r0, r1, #0xc
	neg r1, r0
	ldr r0, [r4, #0x24]
	str r1, [r0, #0x0]
	b _02015B82
_02015B7E:
	bl GF_AssertFail
_02015B82:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x1c]
	add r1, r0, #0x1
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	blt _02015BA4
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015BA4:
	pop {r4, pc}
	nop
_02015BA8: .word FX_SinCosTable_

	thumb_func_start FUN_02015BAC
FUN_02015BAC: ; 0x02015BAC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x24]
	ldr r3, [r4, #0xc]
	ldr r2, [r4, #0x14]
	ldr r5, [r4, #0x8]
	mul r2, r3
	ldr r0, [r1, #0x0]
	add r2, r5, r2
	add r0, r0, r2
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2c
	add r1, r4, #0x0
	ldrb r0, [r0, #0x0]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x14]
	add r1, r0, #0x1
	str r1, [r4, #0x14]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	blt _02015BE4
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015BE4:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02015BE8
FUN_02015BE8: ; 0x02015BE8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	add r1, r0, #0x1
	ldr r0, [r4, #0x8]
	mul r0, r1
	ldr r1, [r4, #0xc]
	bl _s32_div_f
	ldr r1, [r4, #0x24]
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2c
	add r1, r4, #0x0
	ldrb r0, [r0, #0x0]
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x10]
	add r1, r0, #0x1
	str r1, [r4, #0x10]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	blt _02015C20
	mov r0, #0x0
	str r0, [r4, #0x0]
_02015C20:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02015C24
FUN_02015C24: ; 0x02015C24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x14]
	ldr r2, [r4, #0x8]
	mul r0, r1
	ldr r1, [r4, #0x24]
	add r2, r2, r0
	ldr r0, [r1, #0x0]
	add r0, r0, r2
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x18
	beq _02015C48
	cmp r0, #0x1a
	bne _02015C6E
_02015C48:
	cmp r2, #0x0
	ldr r2, [r4, #0x10]
	bge _02015C5E
	ldr r1, [r4, #0x24]
	ldr r0, [r1, #0x0]
	cmp r0, r2
	bgt _02015CA4
	str r2, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015C5E:
	ldr r1, [r4, #0x24]
	ldr r0, [r1, #0x0]
	cmp r0, r2
	blt _02015CA4
	str r2, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015C6E:
	cmp r0, #0x19
	bne _02015CA0
	ldr r1, [r4, #0x24]
	ldr r3, [r4, #0x30]
	ldr r0, [r1, #0x0]
	add r3, r3, r0
	cmp r2, #0x0
	ldr r2, [r4, #0x10]
	bge _02015C90
	cmp r3, r2
	bgt _02015CA4
	sub r2, r2, r3
	add r0, r0, r2
	str r0, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015C90:
	cmp r3, r2
	blt _02015CA4
	sub r2, r3, r2
	sub r0, r0, r2
	str r0, [r1, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02015CA4
_02015CA0:
	bl GF_AssertFail
_02015CA4:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r2, [r4, #0x24]
	ldr r3, [r4, #0x28]
	add r1, #0x30
	bl FUN_020158DC
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
	pop {r4, pc}
	.balign 4
