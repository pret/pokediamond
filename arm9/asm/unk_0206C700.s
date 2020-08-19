    .include "asm/macros.inc"
    .include "global.inc"

	.extern gMain
	.extern UNK_020FA6E8

	.section .rodata

	.global UNK_020F831C
UNK_020F831C: ; 0x020F831C
	.byte 0x03, 0x05, 0x08, 0x00

	.global UNK_020F8320
UNK_020F8320: ; 0x020F8320
	.byte 0x02, 0x17, 0x0D, 0x07, 0x04, 0x0B, 0x0A, 0x00

	.global UNK_020F8328
UNK_020F8328: ; 0x020F8328
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global UNK_020F8338
UNK_020F8338: ; 0x020F8338
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F8354
UNK_020F8354: ; 0x020F8354
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global UNK_020F837C
UNK_020F837C: ; 0x020F837C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x03
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_0206C700
FUN_0206C700: ; 0x0206C700
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r5, [sp, #0x54]
	add r6, r0, #0x0
	str r1, [sp, #0x14]
	add r0, r5, #0x0
	mov r1, #0x80
	add r7, r2, #0x0
	str r3, [sp, #0x18]
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x80
	bl MIi_CpuClearFast
	bl FUN_020222F0
	str r0, [sp, #0x1c]
	bl FUN_020222E8
	add r1, r0, #0x0
	ldr r2, [sp, #0x1c]
	mov r0, #0x0
	bl MIi_CpuClear16
	bl FUN_02022300
	str r0, [sp, #0x20]
	bl FUN_020222F8
	add r1, r0, #0x0
	ldr r2, [sp, #0x20]
	mov r0, #0x0
	bl MIi_CpuClear16
	ldr r0, [sp, #0x14]
	str r6, [r4, #0x24]
	mov r1, #0x5
	mov r2, #0x0
	str r0, [r4, #0x28]
	bl GetMonData
	add r1, r4, #0x0
	add r1, #0x60
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x62
	strh r7, [r0, #0x0]
	str r5, [r4, #0x5c]
	add r0, r5, #0x0
	bl FUN_02002FD0
	str r0, [r4, #0x14]
	mov r1, #0x1
	bl FUN_020038F0
	mov r2, #0x2
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	lsl r2, r2, #0x8
	add r3, r5, #0x0
	bl FUN_02003008
	mov r1, #0x1
	ldr r0, [r4, #0x14]
	lsl r2, r1, #0x9
	add r3, r5, #0x0
	bl FUN_02003008
	mov r2, #0x7
	ldr r0, [r4, #0x14]
	mov r1, #0x2
	lsl r2, r2, #0x6
	add r3, r5, #0x0
	bl FUN_02003008
	mov r2, #0x2
	ldr r0, [r4, #0x14]
	mov r1, #0x3
	lsl r2, r2, #0x8
	add r3, r5, #0x0
	bl FUN_02003008
	add r0, r5, #0x0
	bl FUN_02016B94
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02018FF4
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x2c]
	add r0, r5, #0x0
	bl FUN_0206DE78
	str r0, [r4, #0x34]
	bl FUN_0206DE24
	bl FUN_0206DE4C
	bl FUN_0206DF18
	ldr r1, [r4, #0x0]
	add r0, r4, #0x0
	bl FUN_0206D9B4
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	mov r2, #0x1
	mov r3, #0x2
	bl FUN_02019064
	ldr r0, [r4, #0x4]
	mov r1, #0xff
	bl FUN_02019620
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	mov r2, #0x1
	mov r3, #0xa
	bl FUN_0200D0BC
	add r0, r5, #0x0
	bl FUN_02006D98
	str r0, [r4, #0x18]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02014BF4
	str r0, [r4, #0x44]
	add r0, r4, #0x0
	mov r2, #0x51
	mov r1, #0x0
	add r0, #0x67
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x2
	add r0, #0x66
	strb r1, [r0, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	add r3, r5, #0x0
	bl NewMsgDataFromNarc
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_0200AA80
	str r0, [r4, #0xc]
	mov r0, #0x5
	lsl r0, r0, #0x6
	add r1, r5, #0x0
	bl String_ctor
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	mov r1, #0x30
	bl AllocFromHeap
	str r0, [r4, #0x3c]
	ldr r1, [r4, #0x3c]
	mov r0, #0x0
	mov r2, #0x30
	bl MIi_CpuClearFast
	ldr r1, [sp, #0x38]
	ldr r0, [r4, #0x3c]
	str r1, [r0, #0x2c]
	ldr r0, [sp, #0x3c]
	str r0, [r4, #0x48]
	ldr r0, [sp, #0x40]
	str r0, [r4, #0x4c]
	ldr r0, [sp, #0x44]
	str r0, [r4, #0x50]
	ldr r0, [sp, #0x48]
	str r0, [r4, #0x54]
	ldr r0, [sp, #0x4c]
	str r0, [r4, #0x78]
	ldr r0, [sp, #0x50]
	str r0, [r4, #0x7c]
	add r0, r4, #0x0
	bl FUN_0206DC80
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x14]
	ldr r2, _0206C8E4 ; =0x0000FFFF
	mov r1, #0xf
	mov r3, #0x1
	bl FUN_02003210
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E98
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	mov r2, #0xb
	add r3, r5, #0x0
	bl FUN_020142EC
	mov r1, #0x1
	str r0, [r4, #0x58]
	bl FUN_020143A8
	ldr r0, _0206C8E8 ; =FUN_0206C8EC
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_0200CA44
	mov r0, #0x1
	bl FUN_02002B60
	bl FUN_02033E74
	add r0, r4, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0206C8E4: .word 0x0000FFFF
_0206C8E8: .word FUN_0206C8EC

	thumb_func_start FUN_0206C8EC
FUN_0206C8EC: ; 0x0206C8EC
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0206C9C0
	ldr r0, [r5, #0x18]
	bl FUN_02006ED4
	bl FUN_0206DF58
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020222B4
	add r5, #0x67
	ldrb r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0206C918
	add r0, r4, #0x0
	bl FUN_0200CAB4
_0206C918:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0206C91C
FUN_0206C91C: ; 0x0206C91C
	add r0, #0x67
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0206C928
	mov r0, #0x1
	bx lr
_0206C928:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0206C92C
FUN_0206C92C: ; 0x0206C92C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	bl FUN_020191A4
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	bl FUN_02003038
	ldr r0, [r4, #0x14]
	mov r1, #0x1
	bl FUN_02003038
	ldr r0, [r4, #0x14]
	mov r1, #0x2
	bl FUN_02003038
	ldr r0, [r4, #0x14]
	mov r1, #0x3
	bl FUN_02003038
	ldr r0, [r4, #0x14]
	bl FUN_02002FEC
	ldr r0, [r4, #0x18]
	bl FUN_020072E8
	ldr r0, [r4, #0x44]
	bl FUN_02014C28
	ldr r0, [r4, #0x34]
	bl FUN_020223BC
	ldr r0, [r4, #0x0]
	bl FUN_0206DC48
	ldr r0, [r4, #0x8]
	bl DestroyMsgData
	ldr r0, [r4, #0xc]
	bl FUN_0200AB18
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	ldr r0, [r4, #0x3c]
	bl FreeToHeap
	ldr r0, [r4, #0x58]
	bl FUN_020143D0
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	bl FUN_02002B60
	pop {r4, pc}

	thumb_func_start FUN_0206C9C0
FUN_0206C9C0: ; 0x0206C9C0
	push {r3-r4, lr}
	sub sp, #0x54
	add r4, r0, #0x0
	add r0, #0x70
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0206CA9C
	mov r0, #0x1
	tst r0, r1
	ldr r0, [r4, #0x1c]
	bne _0206CA2E
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	mov r1, #0xc
	neg r2, r2
	bl FUN_020079E0
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	neg r2, r2
	bl FUN_020079E0
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x20]
	mov r1, #0xc
	bl FUN_020079E0
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x20]
	mov r1, #0xd
	bl FUN_020079E0
	ldr r0, [r4, #0x1c]
	mov r1, #0xc
	bl FUN_0200782C
	cmp r0, #0x0
	bne _0206CA9C
	add r0, r4, #0x0
	add r0, #0x70
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	eor r1, r0
	add r0, r4, #0x0
	add r0, #0x70
	strb r1, [r0, #0x0]
	b _0206CA9C
_0206CA2E:
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	mov r1, #0xc
	bl FUN_020079E0
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	bl FUN_020079E0
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x20]
	mov r1, #0xc
	neg r2, r2
	bl FUN_020079E0
	add r2, r4, #0x0
	add r2, #0x71
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x20]
	mov r1, #0xd
	neg r2, r2
	bl FUN_020079E0
	ldr r0, [r4, #0x20]
	mov r1, #0xc
	bl FUN_0200782C
	cmp r0, #0x0
	bne _0206CA9C
	add r0, r4, #0x0
	add r0, #0x70
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	eor r1, r0
	add r0, r4, #0x0
	add r0, #0x70
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x71
	ldrb r0, [r0, #0x0]
	cmp r0, #0x40
	bhs _0206CA9C
	add r0, r4, #0x0
	add r0, #0x71
	ldrb r0, [r0, #0x0]
	lsl r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x71
	strb r1, [r0, #0x0]
_0206CA9C:
	ldr r1, [r4, #0x7c]
	mov r0, #0x1
	tst r0, r1
	beq _0206CAD6
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	cmp r0, #0x8
	bne _0206CAD6
	ldr r0, _0206CE0C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _0206CAD6
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, _0206CE10 ; =0x00007FFF
	ldr r2, _0206CE14 ; =0x0000F3FF
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x14]
	mov r1, #0xf
	bl FUN_02003210
	add r0, r4, #0x0
	mov r1, #0x29
	add r0, #0x64
	strb r1, [r0, #0x0]
_0206CAD6:
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2d
	bhi _0206CBA8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206CAEC: ; jump table (using 16-bit offset)
	.short _0206CB48 - _0206CAEC - 2; case 0
	.short _0206CB70 - _0206CAEC - 2; case 1
	.short _0206CB9E - _0206CAEC - 2; case 2
	.short _0206CBCC - _0206CAEC - 2; case 3
	.short _0206CBE4 - _0206CAEC - 2; case 4
	.short _0206CC66 - _0206CAEC - 2; case 5
	.short _0206CCB2 - _0206CAEC - 2; case 6
	.short _0206CD34 - _0206CAEC - 2; case 7
	.short _0206CDC8 - _0206CAEC - 2; case 8
	.short _0206CE8A - _0206CAEC - 2; case 9
	.short _0206CF18 - _0206CAEC - 2; case 10
	.short _0206CF7E - _0206CAEC - 2; case 11
	.short _0206CFFA - _0206CAEC - 2; case 12
	.short _0206D06E - _0206CAEC - 2; case 13
	.short _0206D0E8 - _0206CAEC - 2; case 14
	.short _0206D188 - _0206CAEC - 2; case 15
	.short _0206D12C - _0206CAEC - 2; case 16
	.short _0206D188 - _0206CAEC - 2; case 17
	.short _0206D162 - _0206CAEC - 2; case 18
	.short _0206D188 - _0206CAEC - 2; case 19
	.short _0206D1C0 - _0206CAEC - 2; case 20
	.short _0206D20E - _0206CAEC - 2; case 21
	.short _0206D260 - _0206CAEC - 2; case 22
	.short _0206D2E2 - _0206CAEC - 2; case 23
	.short _0206D360 - _0206CAEC - 2; case 24
	.short _0206D480 - _0206CAEC - 2; case 25
	.short _0206D188 - _0206CAEC - 2; case 26
	.short _0206D4A6 - _0206CAEC - 2; case 27
	.short _0206D188 - _0206CAEC - 2; case 28
	.short _0206D4F8 - _0206CAEC - 2; case 29
	.short _0206D188 - _0206CAEC - 2; case 30
	.short _0206D51E - _0206CAEC - 2; case 31
	.short _0206D398 - _0206CAEC - 2; case 32
	.short _0206D188 - _0206CAEC - 2; case 33
	.short _0206D3CC - _0206CAEC - 2; case 34
	.short _0206D3EE - _0206CAEC - 2; case 35
	.short _0206D44E - _0206CAEC - 2; case 36
	.short _0206D5AA - _0206CAEC - 2; case 37
	.short _0206D5C8 - _0206CAEC - 2; case 38
	.short _0206D5F4 - _0206CAEC - 2; case 39
	.short _0206D628 - _0206CAEC - 2; case 40
	.short _0206D648 - _0206CAEC - 2; case 41
	.short _0206D6EE - _0206CAEC - 2; case 42
	.short _0206D748 - _0206CAEC - 2; case 43
	.short _0206D79C - _0206CAEC - 2; case 44
	.short _0206D7F6 - _0206CAEC - 2; case 45
_0206CB48:
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0206CBA8
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CB70:
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	ldr r0, [r4, #0x58]
	mov r1, #0x0
	bl FUN_020143A8
	ldr r1, [r4, #0x7c]
	mov r0, #0x2
	tst r1, r0
	beq _0206CB94
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CB94:
	mov r0, #0x4
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CB9E:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	beq _0206CBAC
_0206CBA8:
	bl _0206D806
_0206CBAC:
	mov r1, #0xe5
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CBCC:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206CCCA
	mov r0, #0x4
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CBE4:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206CCCA
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	add r2, #0x60
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0x44]
	ldr r1, [r4, #0x1c]
	mov r3, #0x2
	bl FUN_02069038
	add r1, r4, #0x0
	add r1, #0x60
	ldrh r1, [r1, #0x0]
	add r0, sp, #0x40
	bl FUN_02069010
	ldr r0, [r4, #0x1c]
	add r1, sp, #0x40
	bl FUN_0200737C
	ldr r0, [r4, #0x1c]
	mov r1, #0x0
	bl FUN_02007314
	add r0, r4, #0x0
	add r0, #0x60
	ldrh r0, [r0, #0x0]
	bl FUN_02005578
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r1, [r4, #0x7c]
	mov r0, #0x2
	tst r0, r1
	beq _0206CC4E
	ldr r1, _0206CE18 ; =0x00000395
	add r0, r4, #0x0
	bl FUN_0206DD6C
	b _0206CC56
_0206CC4E:
	ldr r1, _0206CE1C ; =0x00000393
	add r0, r4, #0x0
	bl FUN_0206DD6C
_0206CC56:
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	mov r0, #0x5
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CC66:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206CCCA
	bl FUN_02005670
	cmp r0, #0x0
	bne _0206CCCA
	ldr r0, [r4, #0x44]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _0206CCCA
	ldr r0, [r4, #0x1c]
	bl FUN_02007390
	cmp r0, #0x0
	bne _0206CCCA
	ldr r0, [r4, #0x58]
	mov r1, #0x1
	bl FUN_020143A8
	ldr r0, _0206CE20 ; =0x00000475
	bl FUN_020051F4
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	mov r0, #0x6
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CCB2:
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0206CCCE
_0206CCCA:
	bl _0206D806
_0206CCCE:
	ldr r0, [r4, #0x5c]
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
	add r0, sp, #0x10
	bl FUN_0206E07C
	mov r1, #0x0
	str r0, [r4, #0x30]
	bl FUN_0206E0AC
	ldr r0, _0206CE10 ; =0x00007FFF
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x1c]
	mov r2, #0x10
	mov r3, #0x4
	bl FUN_02007E68
	ldr r0, _0206CE10 ; =0x00007FFF
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x20]
	mov r2, #0x10
	mov r3, #0x4
	bl FUN_02007E68
	ldr r0, [r4, #0x5c]
	bl FUN_02016AF8
	mov r1, #0x2
	lsl r1, r1, #0xe
	cmp r0, r1
	bhi _0206CD16
	bl ErrorHandling
_0206CD16:
	ldr r0, _0206CE24 ; =0x000005F9
	bl FUN_020054C8
	add r0, r4, #0x0
	mov r1, #0x28
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CD34:
	add r0, r4, #0x0
	add r0, #0x73
	ldrb r0, [r0, #0x0]
	cmp r0, #0x28
	bhs _0206CD5A
	add r0, r4, #0x0
	add r0, #0x73
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x2
	add r0, r4, #0x0
	add r0, #0x73
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x75
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x2
	add r0, r4, #0x0
	add r0, #0x75
	strb r1, [r0, #0x0]
_0206CD5A:
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0206CDD2
	ldr r0, [r4, #0x30]
	mov r1, #0x1
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x2
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x7
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x8
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x9
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0xb
	bl FUN_0206E0AC
	ldr r0, _0206CE28 ; =0x000005FA
	bl FUN_020054C8
	add r0, r4, #0x0
	mov r1, #0x10
	add r0, #0x70
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x8
	add r0, #0x71
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CDC8:
	ldr r0, [r4, #0x30]
	bl FUN_0206E0C8
	cmp r0, #0x0
	beq _0206CDD6
_0206CDD2:
	bl _0206D806
_0206CDD6:
	ldr r0, [r4, #0x30]
	mov r1, #0x3
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x4
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x5
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0x6
	bl FUN_0206E0AC
	ldr r0, [r4, #0x30]
	mov r1, #0xa
	bl FUN_0206E0AC
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, _0206CE10 ; =0x00007FFF
	ldr r2, _0206CE14 ; =0x0000F3FF
	b _0206CE2C
	.balign 4
_0206CE0C: .word gMain
_0206CE10: .word 0x00007FFF
_0206CE14: .word 0x0000F3FF
_0206CE18: .word 0x00000395
_0206CE1C: .word 0x00000393
_0206CE20: .word 0x00000475
_0206CE24: .word 0x000005F9
_0206CE28: .word 0x000005FA
_0206CE2C:
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x14]
	mov r1, #0xf
	mov r3, #0x2
	bl FUN_02003210
	ldr r0, [r4, #0x1c]
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x1c]
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_02007558
	mov r1, #0xc
	add r2, r1, #0x0
	ldr r0, [r4, #0x20]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0x0
	ldr r0, [r4, #0x20]
	add r2, #0xf3
	bl FUN_02007558
	ldr r0, _0206D1C8 ; =0x000005FB
	bl FUN_020054C8
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x70
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x8
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CE8A:
	add r0, r4, #0x0
	add r0, #0x73
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0206CEB0
	add r0, r4, #0x0
	add r0, #0x73
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x2
	add r0, r4, #0x0
	add r0, #0x73
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x75
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x2
	add r0, r4, #0x0
	add r0, #0x75
	strb r1, [r0, #0x0]
_0206CEB0:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206CF2C
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0206CF2C
	ldr r0, [r4, #0x30]
	mov r1, #0xc
	bl FUN_0206E0AC
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _0206D1CC ; =0x00007FFF
	ldr r2, _0206D1D0 ; =0x0000F3FF
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x14]
	mov r1, #0xf
	mov r3, #0x4
	bl FUN_02003210
	ldr r0, _0206D1CC ; =0x00007FFF
	mov r1, #0x10
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r2, #0x0
	mov r3, #0x3
	bl FUN_02007E98
	ldr r0, _0206D1D4 ; =0x000005FC
	bl FUN_020054C8
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CF18:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206CF2C
	ldr r0, [r4, #0x30]
	bl FUN_0206E0C8
	cmp r0, #0x0
	beq _0206CF30
_0206CF2C:
	bl _0206D806
_0206CF30:
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	add r2, #0x62
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0x44]
	ldr r1, [r4, #0x20]
	mov r3, #0x2
	bl FUN_02069038
	add r1, r4, #0x0
	add r1, #0x62
	ldrh r1, [r1, #0x0]
	add r0, sp, #0x2c
	bl FUN_02069010
	ldr r0, [r4, #0x20]
	add r1, sp, #0x2c
	bl FUN_0200737C
	ldr r0, [r4, #0x20]
	mov r1, #0x0
	bl FUN_02007314
	add r0, r4, #0x0
	add r0, #0x62
	ldrh r0, [r0, #0x0]
	bl FUN_02005578
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CF7E:
	bl FUN_02005670
	cmp r0, #0x0
	bne _0206D084
	ldr r0, [r4, #0x44]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _0206D084
	ldr r0, [r4, #0x20]
	bl FUN_02007390
	cmp r0, #0x0
	bne _0206D084
	add r2, r4, #0x0
	ldr r0, [r4, #0x28]
	mov r1, #0x5
	add r2, #0x62
	bl SetMonData
	ldr r0, [r4, #0x28]
	bl FUN_0206A1C4
	ldr r0, [r4, #0x28]
	bl CalcMonLevelAndStats
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_0200AC60
	ldr r1, _0206D1D8 ; =0x00000396
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x28
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206CFFA:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206D084
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0206D084
	ldr r0, [r4, #0x48]
	ldr r1, [r4, #0x28]
	bl FUN_02024AF0
	ldr r0, [r4, #0x50]
	mov r1, #0xc
	bl FUN_0202A0E8
	ldr r0, [r4, #0x50]
	mov r1, #0x16
	bl FUN_0202A170
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r1, r0, #0x0
	ldr r0, [r4, #0x54]
	bl FUN_0204C104
	ldr r0, [r4, #0x28]
	mov r1, #0x4d
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _0206D05E
	ldr r0, [r4, #0x28]
	mov r1, #0xb2
	mov r2, #0x0
	bl SetMonData
_0206D05E:
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D06E:
	add r1, r4, #0x0
	ldr r0, [r4, #0x28]
	add r1, #0x68
	add r2, sp, #0xc
	bl FUN_02069818
	cmp r0, #0x0
	beq _0206D08E
	ldr r1, _0206D1DC ; =0x0000FFFE
	cmp r0, r1
	bne _0206D086
_0206D084:
	b _0206D806
_0206D086:
	add r1, r1, #0x1
	cmp r0, r1
	beq _0206D098
	b _0206D0AC
_0206D08E:
	mov r0, #0x27
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D098:
	add r0, sp, #0xc
	ldrh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x6c
	strh r1, [r0, #0x0]
	mov r0, #0xe
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D0AC:
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	add r2, sp, #0xc
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_0200AD5C
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	mov r0, #0x25
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D0E8:
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	add r2, r4, #0x0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_0200AD5C
	ldr r1, _0206D1E0 ; =0x000004A9
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D12C:
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r1, _0206D1E4 ; =0x000004AA
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D162:
	ldr r1, _0206D1E8 ; =0x000004AB
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x1
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D188:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206D1AE
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0206D1B0
_0206D1AE:
	b _0206D806
_0206D1B0:
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D1C0:
	ldr r0, [r4, #0x5c]
	ldr r1, _0206D1EC ; =UNK_020F8320
	b _0206D1F0
	nop
_0206D1C8: .word 0x000005FB
_0206D1CC: .word 0x00007FFF
_0206D1D0: .word 0x0000F3FF
_0206D1D4: .word 0x000005FC
_0206D1D8: .word 0x00000396
_0206D1DC: .word 0x0000FFFE
_0206D1E0: .word 0x000004A9
_0206D1E4: .word 0x000004AA
_0206D1E8: .word 0x000004AB
_0206D1EC: .word UNK_020F8320
_0206D1F0:
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	mov r3, #0x8
	bl FUN_02002198
	str r0, [r4, #0x40]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D20E:
	ldr r0, [r4, #0x40]
	ldr r1, [r4, #0x5c]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _0206D226
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _0206D256
	add sp, #0x54
	pop {r3-r4, pc}
_0206D226:
	add r0, r4, #0x0
	mov r1, #0x16
	add r0, #0x64
	strb r1, [r0, #0x0]
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r4, #0x14]
	ldr r2, _0206D540 ; =0x0000FFFF
	mov r1, #0xf
	mov r3, #0x1
	bl FUN_02003210
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E98
	add sp, #0x54
	pop {r3-r4, pc}
_0206D256:
	mov r0, #0x20
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D260:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206D2EC
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	ldr r0, [r4, #0x0]
	bl FUN_0206DC48
	ldr r0, [r4, #0x1c]
	mov r1, #0x6
	mov r2, #0x1
	bl FUN_02007558
	ldr r0, [r4, #0x20]
	mov r1, #0x6
	mov r2, #0x1
	bl FUN_02007558
	ldr r1, [r4, #0x28]
	ldr r0, [r4, #0x3c]
	mov r2, #0x1
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x2c]
	ldr r0, [r4, #0x3c]
	str r1, [r0, #0x4]
	ldr r1, [r4, #0x3c]
	mov r0, #0x0
	strb r0, [r1, #0x11]
	ldr r1, [r4, #0x3c]
	strb r0, [r1, #0x14]
	ldr r1, [r4, #0x3c]
	strb r2, [r1, #0x13]
	add r1, r4, #0x0
	add r1, #0x6c
	ldrh r2, [r1, #0x0]
	ldr r1, [r4, #0x3c]
	strh r2, [r1, #0x18]
	ldr r1, [r4, #0x3c]
	mov r2, #0x2
	strb r2, [r1, #0x12]
	ldr r1, [r4, #0x3c]
	str r0, [r1, #0x28]
	ldr r0, [r4, #0x3c]
	ldr r1, _0206D544 ; =UNK_020F831C
	bl FUN_0207B000
	add r0, r4, #0x0
	bl FUN_0206DE0C
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D2E2:
	ldr r0, [r4, #0x38]
	bl OverlayManager_Run
	cmp r0, #0x0
	bne _0206D2EE
_0206D2EC:
	b _0206D806
_0206D2EE:
	ldr r0, [r4, #0x38]
	bl OverlayManager_delete
	ldr r1, [r4, #0x0]
	add r0, r4, #0x0
	bl FUN_0206D9B4
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	mov r2, #0x1
	mov r3, #0xa
	bl FUN_0200D0BC
	ldr r0, [r4, #0x1c]
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x20]
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x1c]
	bl FUN_020080D0
	ldr r0, [r4, #0x20]
	bl FUN_020080D0
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x14]
	ldr r2, _0206D540 ; =0x0000FFFF
	mov r1, #0xf
	mov r3, #0x1
	bl FUN_02003210
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E98
	bl FUN_02033E74
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D360:
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206D474
	ldr r0, [r4, #0x3c]
	ldrb r1, [r0, #0x16]
	cmp r1, #0x4
	bne _0206D388
	mov r0, #0x20
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D388:
	add r0, r4, #0x0
	add r0, #0x6e
	strb r1, [r0, #0x0]
	mov r0, #0x19
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D398:
	add r2, r4, #0x0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200AD5C
	ldr r1, _0206D548 ; =0x000004AD
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x1
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D3CC:
	ldr r0, [r4, #0x5c]
	ldr r1, _0206D54C ; =UNK_020F8320
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	mov r3, #0x8
	bl FUN_02002198
	str r0, [r4, #0x40]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D3EE:
	ldr r0, [r4, #0x40]
	ldr r1, [r4, #0x5c]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _0206D406
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _0206D444
	add sp, #0x54
	pop {r3-r4, pc}
_0206D406:
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	add r2, r4, #0x0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_0200AD5C
	ldr r1, _0206D550 ; =0x000004AE
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	mov r0, #0x24
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D444:
	mov r0, #0xe
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D44E:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206D474
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0206D476
_0206D474:
	b _0206D806
_0206D476:
	mov r0, #0xd
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D480:
	ldr r1, _0206D554 ; =0x000004AF
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D4A6:
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	add r1, r4, #0x0
	add r1, #0x6e
	ldrb r1, [r1, #0x0]
	ldr r0, [r4, #0x28]
	mov r2, #0x0
	add r1, #0x36
	bl GetMonData
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_0200AD5C
	mov r1, #0x4b
	add r0, r4, #0x0
	lsl r1, r1, #0x4
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D4F8:
	ldr r1, _0206D558 ; =0x000004B1
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D51E:
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	add r2, r4, #0x0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_0200AD5C
	ldr r1, _0206D55C ; =0x000004B2
	b _0206D560
	.balign 4
_0206D540: .word 0x0000FFFF
_0206D544: .word UNK_020F831C
_0206D548: .word 0x000004AD
_0206D54C: .word UNK_020F8320
_0206D550: .word 0x000004AE
_0206D554: .word 0x000004AF
_0206D558: .word 0x000004B1
_0206D55C: .word 0x000004B2
_0206D560:
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	add r2, r4, #0x0
	mov r1, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r1, r4, #0x0
	add r1, #0x6e
	ldrb r1, [r1, #0x0]
	ldr r0, [r4, #0x28]
	add r2, #0x66
	add r1, #0x3e
	bl SetMonData
	add r1, r4, #0x0
	add r2, r4, #0x0
	add r1, #0x6c
	add r2, #0x6e
	ldrh r1, [r1, #0x0]
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x28]
	bl MonSetMoveInSlot
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	mov r0, #0x25
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D5AA:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206D5E8
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D5C8:
	bl FUN_02005CBC
	cmp r0, #0x0
	bne _0206D5E8
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0206D5EA
_0206D5E8:
	b _0206D806
_0206D5EA:
	mov r0, #0xd
	add r4, #0x64
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D5F4:
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r4, #0x14]
	ldr r2, _0206D80C ; =0x0000FFFF
	mov r1, #0xf
	mov r3, #0x1
	bl FUN_02003210
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E98
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D628:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206D6F8
	ldr r0, [r4, #0x30]
	bl FUN_0206E0DC
	add r0, r4, #0x0
	bl FUN_0206D820
	mov r0, #0x1
	add r4, #0x67
	add sp, #0x54
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D648:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206D6F8
	mov r1, #0xc
	add r2, r1, #0x0
	ldr r0, [r4, #0x1c]
	add r2, #0xf4
	bl FUN_02007558
	mov r1, #0xd
	add r2, r1, #0x0
	ldr r0, [r4, #0x1c]
	add r2, #0xf3
	bl FUN_02007558
	ldr r0, [r4, #0x20]
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x20]
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x20]
	mov r1, #0x6
	mov r2, #0x1
	bl FUN_02007558
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r0, _0206D810 ; =0x00007FFF
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x14]
	ldr r2, _0206D814 ; =0x0000F3FF
	mov r1, #0xf
	bl FUN_02003210
	ldr r0, _0206D810 ; =0x00007FFF
	mov r2, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E98
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x72
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x73
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r2, #0xff
	add r0, #0x74
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	mov r2, #0xa0
	add r0, #0x75
	strb r2, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x70
	strb r1, [r0, #0x0]
	ldr r0, _0206D818 ; =0x00000475
	bl FUN_02005350
	ldr r0, [r4, #0x30]
	bl FUN_0206E0DC
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D6EE:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	beq _0206D6FA
_0206D6F8:
	b _0206D806
_0206D6FA:
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r2, r4, #0x0
	add r2, #0x60
	ldrh r2, [r2, #0x0]
	ldr r0, [r4, #0x44]
	ldr r1, [r4, #0x1c]
	mov r3, #0x2
	bl FUN_02069038
	add r1, r4, #0x0
	add r1, #0x60
	ldrh r1, [r1, #0x0]
	add r0, sp, #0x18
	bl FUN_02069010
	ldr r0, [r4, #0x1c]
	add r1, sp, #0x18
	bl FUN_0200737C
	ldr r0, [r4, #0x1c]
	mov r1, #0x0
	bl FUN_02007314
	add r0, r4, #0x0
	add r0, #0x60
	ldrh r0, [r0, #0x0]
	bl FUN_02005578
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D748:
	bl FUN_02005670
	cmp r0, #0x0
	bne _0206D806
	ldr r0, [r4, #0x44]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _0206D806
	ldr r0, [r4, #0x1c]
	bl FUN_02007390
	cmp r0, #0x0
	bne _0206D806
	ldr r0, [r4, #0x28]
	bl FUN_020690E4
	add r2, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r1, _0206D81C ; =0x00000397
	add r0, r4, #0x0
	bl FUN_0206DD6C
	add r1, r4, #0x0
	add r1, #0x65
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D79C:
	add r0, r4, #0x0
	add r0, #0x65
	ldrb r0, [r0, #0x0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _0206D806
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x66
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x66
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0206D806
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x10
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r4, #0x14]
	ldr r2, _0206D80C ; =0x0000FFFF
	mov r1, #0xf
	mov r3, #0x1
	bl FUN_02003210
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x18]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E98
	add r0, r4, #0x0
	add r0, #0x64
	ldrb r0, [r0, #0x0]
	add r4, #0x64
	add sp, #0x54
	add r0, r0, #0x1
	strb r0, [r4, #0x0]
	pop {r3-r4, pc}
_0206D7F6:
	ldr r0, [r4, #0x14]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _0206D806
	mov r0, #0x1
	add r4, #0x67
	strb r0, [r4, #0x0]
_0206D806:
	add sp, #0x54
	pop {r3-r4, pc}
	nop
_0206D80C: .word 0x0000FFFF
_0206D810: .word 0x00007FFF
_0206D814: .word 0x0000F3FF
_0206D818: .word 0x00000475
_0206D81C: .word 0x00000397

	thumb_func_start FUN_0206D820
FUN_0206D820: ; 0x0206D820
	push {r4-r6, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	ldr r0, [r4, #0x78]
	cmp r0, #0x6
	bgt _0206D834
	bne _0206D830
	b _0206D9A0
_0206D830:
	add sp, #0x20
	pop {r4-r6, pc}
_0206D834:
	sub r0, #0xd
	cmp r0, #0x6
	bhi _0206D86C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206D846: ; jump table (using 16-bit offset)
	.short _0206D854 - _0206D846 - 2; case 0
	.short _0206D854 - _0206D846 - 2; case 1
	.short _0206D9AE - _0206D846 - 2; case 2
	.short _0206D9AE - _0206D846 - 2; case 3
	.short _0206D9AE - _0206D846 - 2; case 4
	.short _0206D9A0 - _0206D846 - 2; case 5
	.short _0206D9A0 - _0206D846 - 2; case 6
_0206D854:
	ldr r0, [r4, #0x4c]
	ldr r2, [r4, #0x5c]
	mov r1, #0x4
	bl Bag_GetQuantity
	cmp r0, #0x0
	beq _0206D86C
	ldr r0, [r4, #0x24]
	bl GetPartyCount
	cmp r0, #0x6
	blt _0206D86E
_0206D86C:
	b _0206D9AE
_0206D86E:
	ldr r0, [r4, #0x5c]
	bl AllocMonZeroed
	add r5, r0, #0x0
	ldr r0, [r4, #0x28]
	add r1, r5, #0x0
	bl FUN_02069B88
	mov r0, #0x49
	lsl r0, r0, #0x2
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x5
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x4
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x9a
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl SetMonData
	add r0, r5, #0x0
	mov r1, #0xb
	add r2, sp, #0x0
	bl SetMonData
	mov r1, #0x19
	str r1, [sp, #0x4]
	add r6, sp, #0x0
_0206D8BA:
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl SetMonData
	ldr r0, [sp, #0x4]
	add r1, r0, #0x1
	str r1, [sp, #0x4]
	cmp r1, #0x36
	blt _0206D8BA
	mov r1, #0x4e
	str r1, [sp, #0x4]
	add r6, sp, #0x0
_0206D8D2:
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl SetMonData
	ldr r0, [sp, #0x4]
	add r1, r0, #0x1
	str r1, [sp, #0x4]
	cmp r1, #0x6e
	blt _0206D8D2
	mov r1, #0x7a
	str r1, [sp, #0x4]
	add r6, sp, #0x0
_0206D8EA:
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl SetMonData
	ldr r0, [sp, #0x4]
	add r1, r0, #0x1
	str r1, [sp, #0x4]
	cmp r1, #0x8f
	blt _0206D8EA
	add r0, r5, #0x0
	mov r1, #0xb2
	mov r2, #0x0
	bl SetMonData
	add r0, r5, #0x0
	mov r1, #0x4d
	add r2, sp, #0x0
	bl SetMonData
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x0
	bl SetMonData
	ldr r0, [r4, #0x5c]
	bl CreateNewSealsObject
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa9
	add r2, r6, #0x0
	bl SetMonData
	add r0, r6, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	mov r1, #0xa1
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	add r1, sp, #0x8
	mov r2, #0x18
	bl MIi_CpuClearFast
	add r0, r5, #0x0
	mov r1, #0xaa
	add r2, sp, #0x8
	bl SetMonData
	add r0, r5, #0x0
	bl FUN_0206A1C4
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	ldr r0, [r4, #0x24]
	add r1, r5, #0x0
	bl AddMonToParty
	ldr r0, [r4, #0x48]
	add r1, r5, #0x0
	bl FUN_02024AF0
	ldr r0, [r4, #0x50]
	mov r1, #0xc
	bl FUN_0202A0E8
	ldr r0, [r4, #0x50]
	mov r1, #0x16
	bl FUN_0202A170
	add r0, r5, #0x0
	bl FUN_020690E4
	add r1, r0, #0x0
	ldr r0, [r4, #0x54]
	bl FUN_0204C104
	add r0, r5, #0x0
	bl FreeToHeap
	ldr r0, [r4, #0x4c]
	ldr r3, [r4, #0x5c]
	mov r1, #0x4
	mov r2, #0x1
	bl Bag_TakeItem
	add sp, #0x20
	pop {r4-r6, pc}
_0206D9A0:
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x28]
	mov r1, #0x6
	add r2, sp, #0x4
	bl SetMonData
_0206D9AE:
	add sp, #0x20
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206D9B4
FUN_0206D9B4: ; 0x0206D9B4
	push {r4-r6, lr}
	sub sp, #0xb8
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0201E6D8
	ldr r6, _0206DC28 ; =UNK_020F8354
	add r3, sp, #0x3c
	mov r2, #0x5
_0206D9C6:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206D9C6
	add r0, sp, #0x3c
	bl FUN_0201E66C
	mov r1, #0x6
	mov r2, #0x2
	mov r0, #0x0
	lsl r1, r1, #0x18
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x62
	mov r2, #0x2
	mov r0, #0x0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	mov r1, #0x19
	mov r2, #0x1
	mov r0, #0x0
	lsl r1, r1, #0x16
	lsl r2, r2, #0x12
	bl MIi_CpuClear32
	mov r1, #0x66
	mov r2, #0x2
	mov r0, #0x0
	lsl r1, r1, #0x14
	lsl r2, r2, #0x10
	bl MIi_CpuClear32
	ldr r6, _0206DC2C ; =UNK_020F8328
	add r3, sp, #0x2c
	add r2, r3, #0x0
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r6, _0206DC30 ; =UNK_020F837C
	add r3, sp, #0x64
	mov r2, #0xa
_0206DA26:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206DA26
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	add r2, sp, #0x64
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02018744
	add r0, r4, #0x0
	mov r1, #0x2
	add r2, sp, #0x80
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02018744
	add r0, r4, #0x0
	mov r1, #0x3
	add r2, sp, #0x9c
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02018744
	ldr r1, _0206DC34 ; =0x04000008
	mov r0, #0x3
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x1
	orr r2, r0
	strh r2, [r1, #0x0]
	add r1, r0, #0x0
	bl FUN_0201E6E4
	ldr r6, _0206DC38 ; =UNK_020F8338
	add r3, sp, #0x10
	ldmia r6!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	mov r1, #0x4
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02018744
	ldr r0, [r5, #0x2c]
	bl FUN_02025084
	add r6, r0, #0x0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x5c]
	mov r1, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r2, r1, #0x0
	mov r3, #0xa
	bl FUN_0200D274
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x5c]
	add r2, r4, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x76
	mov r3, #0x3
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x1
	str r1, [sp, #0x8]
	ldr r0, [r5, #0x5c]
	add r2, r4, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x76
	mov r3, #0x3
	bl FUN_020068C8
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x40
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r5, #0x14]
	ldr r3, [r5, #0x5c]
	mov r1, #0x76
	mov r2, #0x8
	bl FUN_020030E8
	add r0, r6, #0x0
	bl FUN_0200CD64
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xa0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x14]
	ldr r3, [r5, #0x5c]
	mov r1, #0x26
	bl FUN_020030E8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xb0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x14]
	ldr r3, [r5, #0x5c]
	mov r1, #0xe
	mov r2, #0x7
	bl FUN_020030E8
	ldr r0, [r5, #0x5c]
	mov r1, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	mov r3, #0x0
	bl FUN_0200CABC
	bl FUN_0200CAFC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0x80
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x14]
	ldr r3, [r5, #0x5c]
	mov r1, #0x26
	bl FUN_020030E8
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x5c]
	mov r1, #0xa
	str r0, [sp, #0xc]
	mov r0, #0xc
	add r2, r4, #0x0
	mov r3, #0x4
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x5c]
	mov r1, #0xb
	str r0, [sp, #0xc]
	mov r0, #0xc
	add r2, r4, #0x0
	mov r3, #0x4
	bl FUN_020068C8
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r1, #0xc
	ldr r0, [r5, #0x14]
	ldr r3, [r5, #0x5c]
	add r2, r1, #0x0
	bl FUN_020030E8
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	ldr r2, _0206DC3C ; =0xFFFF1FFF
	add r3, r1, #0x0
	and r3, r2
	lsr r1, r0, #0xd
	orr r1, r3
	ldr r3, _0206DC40 ; =0x04001000
	str r1, [r0, #0x0]
	ldr r1, [r3, #0x0]
	and r1, r2
	str r1, [r3, #0x0]
	add r3, r0, #0x0
	add r3, #0x48
	ldrh r4, [r3, #0x0]
	mov r2, #0x3f
	mov r1, #0x1f
	bic r4, r2
	orr r1, r4
	strh r1, [r3, #0x0]
	add r0, #0x4a
	ldrh r3, [r0, #0x0]
	mov r1, #0x12
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0x72
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x73
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0xff
	add r0, #0x74
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0xa0
	add r0, #0x75
	strb r1, [r0, #0x0]
	bl FUN_0201E788
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E6E4
	ldr r0, _0206DC44 ; =FUN_0206DD08
	add r1, r5, #0x0
	bl FUN_02015F10
	add sp, #0xb8
	pop {r4-r6, pc}
	.balign 4
_0206DC28: .word UNK_020F8354
_0206DC2C: .word UNK_020F8328
_0206DC30: .word UNK_020F837C
_0206DC34: .word 0x04000008
_0206DC38: .word UNK_020F8338
_0206DC3C: .word 0xFFFF1FFF
_0206DC40: .word 0x04001000
_0206DC44: .word FUN_0206DD08

	thumb_func_start FUN_0206DC48
FUN_0206DC48: ; 0x0206DC48
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_020178A0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0206DC80
FUN_0206DC80: ; 0x0206DC80
	push {r3-r5, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	ldr r1, [r4, #0x28]
	add r0, sp, #0x10
	mov r2, #0x2
	bl FUN_02068B68
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x18]
	add r1, sp, #0x10
	mov r2, #0x80
	mov r3, #0x50
	bl FUN_020073A0
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x5c]
	bl AllocMonZeroed
	add r5, r0, #0x0
	ldr r0, [r4, #0x28]
	add r1, r5, #0x0
	bl FUN_02069B88
	add r2, r4, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	add r2, #0x62
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	add r0, sp, #0x10
	add r1, r5, #0x0
	mov r2, #0x2
	bl FUN_02068B68
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x18]
	add r1, sp, #0x10
	mov r2, #0x80
	mov r3, #0x50
	bl FUN_020073A0
	str r0, [r4, #0x20]
	mov r1, #0xc
	mov r2, #0x0
	bl FUN_02007558
	ldr r0, [r4, #0x20]
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_02007558
	add sp, #0x20
	pop {r3-r5, pc}

	thumb_func_start FUN_0206DD08
FUN_0206DD08: ; 0x0206DD08
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x75
	ldrb r2, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x73
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x72
	ldrb r0, [r0, #0x0]
	mov r3, #0xff
	lsl r3, r3, #0x8
	lsl r0, r0, #0x8
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x74
	lsl r1, r1, #0x8
	and r1, r3
	ldrb r0, [r0, #0x0]
	and r5, r3
	orr r1, r2
	orr r5, r0
	ldr r0, _0206DD60 ; =0x04000040
	strh r5, [r0, #0x0]
	strh r1, [r0, #0x4]
	ldr r0, [r4, #0x18]
	bl FUN_020081C4
	bl FUN_0201C30C
	ldr r0, [r4, #0x14]
	bl FUN_0200372C
	ldr r0, [r4, #0x0]
	bl FUN_0201AB60
	ldr r3, _0206DD64 ; =0x027E0000
	ldr r1, _0206DD68 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3-r5, pc}
	nop
_0206DD60: .word 0x04000040
_0206DD64: .word 0x027E0000
_0206DD68: .word 0x00003FF8

	thumb_func_start FUN_0206DD6C
FUN_0206DD6C: ; 0x0206DD6C
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	bl NewString_ReadMsgData
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r2, r5, #0x0
	bl StringExpandPlaceholders
	add r0, r5, #0x0
	bl FreeToHeap
	ldr r0, [r4, #0x4]
	mov r1, #0xff
	bl FUN_02019620
	ldr r0, [r4, #0x2c]
	bl FUN_02024FF4
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _0206DDB0 ; =FUN_0206DDB4
	mov r1, #0x1
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x10]
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_0206DDB0: .word FUN_0206DDB4

	thumb_func_start FUN_0206DDB4
FUN_0206DDB4: ; 0x0206DDB4
	push {r4, lr}
	mov r4, #0x0
	cmp r1, #0x5
	bhi _0206DDFA
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206DDC8: ; jump table (using 16-bit offset)
	.short _0206DDFA - _0206DDC8 - 2; case 0
	.short _0206DDD4 - _0206DDC8 - 2; case 1
	.short _0206DDDC - _0206DDC8 - 2; case 2
	.short _0206DDE4 - _0206DDC8 - 2; case 3
	.short _0206DDEC - _0206DDC8 - 2; case 4
	.short _0206DDF4 - _0206DDC8 - 2; case 5
_0206DDD4:
	bl FUN_02005514
	add r4, r0, #0x0
	b _0206DDFA
_0206DDDC:
	bl FUN_02005CBC
	add r4, r0, #0x0
	b _0206DDFA
_0206DDE4:
	ldr r0, _0206DE00 ; =0x00000484
	bl PlayBGM
	b _0206DDFA
_0206DDEC:
	ldr r0, _0206DE04 ; =0x000005E6
	bl FUN_020054C8
	b _0206DDFA
_0206DDF4:
	ldr r0, _0206DE08 ; =0x00000483
	bl PlayBGM
_0206DDFA:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0206DE00: .word 0x00000484
_0206DE04: .word 0x000005E6
_0206DE08: .word 0x00000483

	thumb_func_start FUN_0206DE0C
FUN_0206DE0C: ; 0x0206DE0C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0206DE20 ; =UNK_020FA6E8
	ldr r1, [r4, #0x3c]
	ldr r2, [r4, #0x5c]
	bl OverlayManager_new
	str r0, [r4, #0x38]
	pop {r4, pc}
	nop
_0206DE20: .word UNK_020FA6E8
