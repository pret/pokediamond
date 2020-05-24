	.include "asm/macros.inc"
    .include "global.inc"

	.section .data

	.global UNK_02105BD4
UNK_02105BD4: ; 0x02105BD4
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x32, 0x00, 0x00, 0x01, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x03, 0x1E, 0xEC, 0xEC, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x00, 0x10, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x32, 0x00, 0x9D, 0x00, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x32, 0x00, 0x00, 0x01, 0x00

	.text

	thumb_func_start FUN_02023AC4
FUN_02023AC4: ; 0x02023AC4
	mov r0, #0x20
	bx lr

	thumb_func_start FUN_02023AC8
FUN_02023AC8: ; 0x02023AC8
	mov r0, #0x20
	bx lr

	thumb_func_start FUN_02023ACC
FUN_02023ACC: ; 0x02023ACC
	ldr r3, _02023AD4 ; =MI_CpuCopy8
	mov r2, #0x20
	bx r3
	nop
_02023AD4: .word MI_CpuCopy8

	thumb_func_start FUN_02023AD8
FUN_02023AD8: ; 0x02023AD8
	ldr r3, _02023AE0 ; =memset
	mov r1, #0x0
	mov r2, #0x20
	bx r3
	.balign 4
_02023AE0: .word memset

	thumb_func_start FUN_02023AE4
FUN_02023AE4: ; 0x02023AE4
	ldr r3, _02023AF0 ; =FUN_02021E8C
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0xc
	bx r3
	.balign 4
_02023AF0: .word FUN_02021E8C

	thumb_func_start FUN_02023AF4
FUN_02023AF4: ; 0x02023AF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x18
	bl FUN_020219F4
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_02021E28
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023B0C
FUN_02023B0C: ; 0x02023B0C
	mov r2, #0x0
	cmp r1, #0xc
	bhi _02023B9E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02023B1E: ; jump table (using 16-bit offset)
	.short _02023B9E - _02023B1E - 2; case 0
	.short _02023B38 - _02023B1E - 2; case 1
	.short _02023B3C - _02023B1E - 2; case 2
	.short _02023B40 - _02023B1E - 2; case 3
	.short _02023B44 - _02023B1E - 2; case 4
	.short _02023B4C - _02023B1E - 2; case 5
	.short _02023B52 - _02023B1E - 2; case 6
	.short _02023B66 - _02023B1E - 2; case 7
	.short _02023B6C - _02023B1E - 2; case 8
	.short _02023B80 - _02023B1E - 2; case 9
	.short _02023B88 - _02023B1E - 2; case 10
	.short _02023B90 - _02023B1E - 2; case 11
	.short _02023B98 - _02023B1E - 2; case 12
_02023B38:
	ldrb r2, [r0, #0x1a]
	b _02023B9E
_02023B3C:
	ldrb r2, [r0, #0x1b]
	b _02023B9E
_02023B40:
	ldrh r2, [r0, #0x18]
	b _02023B9E
_02023B44:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1f
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B4C:
	mov r1, #0x1c
	ldrsb r2, [r0, r1]
	b _02023B9E
_02023B52:
	mov r1, #0x1c
	ldrsb r0, [r0, r1]
	cmp r0, #0x0
	ble _02023B5E
	mov r2, #0x1
	b _02023B9E
_02023B5E:
	bge _02023B9E
	add r2, r1, #0x0
	sub r2, #0x1d
	b _02023B9E
_02023B66:
	mov r1, #0x1d
	ldrsb r2, [r0, r1]
	b _02023B9E
_02023B6C:
	mov r1, #0x1d
	ldrsb r0, [r0, r1]
	cmp r0, #0x0
	ble _02023B78
	mov r2, #0x1
	b _02023B9E
_02023B78:
	bge _02023B9E
	add r2, r1, #0x0
	sub r2, #0x1e
	b _02023B9E
_02023B80:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B88:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1d
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B90:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1e
	lsr r2, r0, #0x1f
	b _02023B9E
_02023B98:
	ldrb r0, [r0, #0x1e]
	lsl r0, r0, #0x1b
	lsr r2, r0, #0x1f
_02023B9E:
	add r0, r2, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02023BA4
FUN_02023BA4: ; 0x02023BA4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x1
	blt _02023BB2
	bl ErrorHandling
_02023BB2:
	add r0, r4, #0x0
	mov r1, #0xd
	bl FUN_02022610
	add r4, r0, #0x0
	lsl r5, r5, #0x5
	add r0, r4, r5
	mov r1, #0x1
	bl FUN_02023B0C
	cmp r0, #0x0
	beq _02023BCE
	add r0, r4, r5
	pop {r3-r5, pc}
_02023BCE:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023BD4
FUN_02023BD4: ; 0x02023BD4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0xd
	bl FUN_02022610
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02023ACC
	pop {r4, pc}

	thumb_func_start FUN_02023BE8
FUN_02023BE8: ; 0x02023BE8
	push {r3, lr}
	cmp r1, #0x5
	bhs _02023BF6
	ldr r2, _02023C00 ; =UNK_02105BD4
	lsl r0, r1, #0x5
	add r0, r2, r0
	pop {r3, pc}
_02023BF6:
	mov r1, #0xd
	bl FUN_02022610
	pop {r3, pc}
	nop
_02023C00: .word UNK_02105BD4

	thumb_func_start FUN_02023C04
FUN_02023C04: ; 0x02023C04
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x5
	bhs _02023C2C
	ldr r2, _02023C3C ; =0x0000013A
	mov r0, #0x0
	mov r1, #0x1a
	bl FUN_0200A86C
	add r5, #0x38
	add r6, r0, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0200A8E0
	add r0, r6, #0x0
	bl FUN_0200A8B8
	pop {r4-r6, pc}
_02023C2C:
	mov r1, #0x0
	bl FUN_02023BA4
	add r1, r4, #0x0
	bl FUN_02023AE4
	pop {r4-r6, pc}
	nop
_02023C3C: .word 0x0000013A
