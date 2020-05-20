    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FCAEA
	.extern UNK_020FCAED
	.extern UNK_020FCAEE
	.extern UNK_020F96DC
	.extern UNK_020FCAD8
	.extern UNK_020FCAE8
	.extern UNK_020FCAEC
	.extern UNK_020FCAF0

	.text

	thumb_func_start FUN_020859C0
FUN_020859C0: ; 0x020859C0
	push {r3-r7, lr}
	mov r2, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x35
	lsl r2, r2, #0x12
	bl FUN_0201681C
	mov r0, #0x35
	bl MOD62_02230F3C
	bl MOD62_0222F7E0
	ldr r1, _02085BA0 ; =0x0000042C
	add r0, r5, #0x0
	mov r2, #0x35
	bl FUN_02006268
	ldr r2, _02085BA0 ; =0x0000042C
	mov r1, #0x0
	add r4, r0, #0x0
	bl memset
	bl MOD62_0222E2BC
	mov r1, #0x23
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	add r0, r5, #0x0
	bl FUN_0200628C
	str r0, [r4, #0x0]
	mov r0, #0x35
	bl FUN_020669C0
	ldr r1, _02085BA4 ; =0x00000428
	mov r2, #0xff
	str r0, [r4, r1]
	add r0, r4, #0x0
	add r0, #0xd4
	str r2, [r0, #0x0]
	mov r0, #0x0
	sub r1, #0x10
	str r0, [r4, r1]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x20]
	bl FUN_02029E0C
	asr r1, r0, #0x2
	lsr r1, r1, #0x1d
	add r1, r0, r1
	asr r0, r1, #0x3
	add r1, r0, #0x1
	ldr r0, _02085BA8 ; =0x0000041C
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0xa
	ble _02085A38
	mov r1, #0xa
	str r1, [r4, r0]
_02085A38:
	ldr r0, [r4, #0x0]
	bl FUN_02085D84
	mov r1, #0xf1
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, #0x0]
	bl FUN_02085D84
	mov r1, #0xf2
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x20]
	bl FUN_02029CEC
	str r0, [r4, #0x64]
	mov r6, #0x0
	add r5, r4, #0x0
	mov r7, #0xff
_02085A60:
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x20]
	bl FUN_02029C8C
	str r7, [r5, #0x4]
	str r0, [r5, #0x8]
	add r6, r6, #0x1
	add r5, #0x8
	cmp r6, #0xc
	blt _02085A60
	mov r5, #0x0
	add r6, r5, #0x0
	mov r7, #0xa1
_02085A7C:
	ldr r0, [r4, #0x0]
	add r0, r0, r6
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02085A9A
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02085A9A
	lsl r0, r0, #0x3
	add r0, r4, r0
	sub r0, r0, #0x4
	str r5, [r0, #0x0]
_02085A9A:
	add r5, r5, #0x1
	add r6, r6, #0x4
	cmp r5, #0x6
	blt _02085A7C
	mov r0, #0x35
	bl FUN_02016B94
	add r1, r4, #0x0
	add r1, #0xe4
	str r0, [r1, #0x0]
	mov r0, #0x40
	mov r1, #0x35
	bl FUN_0201C24C
	mov r0, #0x35
	bl FUN_02002FD0
	add r1, r4, #0x0
	add r1, #0xe8
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_020038F0
	add r0, r4, #0x0
	add r0, #0xe8
	mov r2, #0x2
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0x8
	mov r3, #0x35
	bl FUN_02003008
	add r0, r4, #0x0
	add r0, #0xe8
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r2, r1, #0x9
	mov r3, #0x35
	bl FUN_02003008
	add r0, r4, #0x0
	add r0, #0xe8
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r2, r1, #0x8
	mov r3, #0x35
	bl FUN_02003008
	add r0, r4, #0x0
	add r0, #0xe8
	mov r2, #0x2
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	lsl r2, r2, #0x8
	mov r3, #0x35
	bl FUN_02003008
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	bl MOD62_02230F80
	bl MOD62_0222E360
	mov r0, #0x35
	bl FUN_02006D98
	mov r1, #0x69
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x35
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02014BF4
	mov r1, #0x97
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r4, #0x0
	add r0, #0xe4
	add r1, #0xe8
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	add r2, r5, #0x0
	bl MOD62_0222ED34
	add r0, r4, #0x0
	add r1, r4, #0x0
	add r0, #0xe4
	add r1, #0xe8
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	add r2, r5, #0x0
	bl MOD62_0222EDBC
	add r0, r4, #0x0
	add r0, #0xd4
	bl MOD62_0222E7E8
	bl FUN_0201CC08
	mov r0, #0x4
	bl FUN_0201CC24
	add r0, r4, #0x0
	bl MOD62_022300E4
	ldr r0, _02085BAC ; =0x022310CD
	add r1, r4, #0x0
	bl FUN_02015F10
	add r0, r4, #0x0
	bl MOD62_0222DD1C
	mov r1, #0x0
	mov r0, #0x3b
	add r2, r1, #0x0
	bl FUN_0200433C
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_02085BA0: .word 0x0000042C
_02085BA4: .word 0x00000428
_02085BA8: .word 0x0000041C
_02085BAC: .word 0x022310CD

	thumb_func_start FUN_02085BB0
FUN_02085BB0: ; 0x02085BB0
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	beq _02085BCA
	cmp r1, #0x1
	beq _02085BD8
	cmp r1, #0x2
	beq _02085BF6
	b _02085C02
_02085BCA:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02085C02
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02085C02
_02085BD8:
	bl MOD12_0222F990
	cmp r0, #0x0
	bne _02085BE6
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02085C02
_02085BE6:
	mov r0, #0x69
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02006ED4
	bl MOD62_0222E3A0
	b _02085C02
_02085BF6:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02085C02
	mov r0, #0x1
	pop {r3-r5, pc}
_02085C02:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02085C08
FUN_02085C08: ; 0x02085C08
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x8
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201E74C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E74C
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201E74C
	mov r0, #0x8
	mov r1, #0x0
	bl FUN_0201E74C
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x5
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x6
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	mov r1, #0x7
	bl FUN_020178A0
	add r0, r4, #0x0
	add r0, #0xe4
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02003038
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02003038
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	bl FUN_02003038
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02003038
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bl FUN_02002FEC
	mov r1, #0xf1
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r0, [r4, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02085D8C
	ldr r0, _02085D64 ; =0x00000428
	ldr r0, [r4, r0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl MOD62_0222DAEC
	mov r0, #0x73
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0202212C
	mov r0, #0x69
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020072E8
	mov r0, #0x97
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02014C28
	add r0, r4, #0x0
	bl MOD62_0222DD38
	add r0, r4, #0x0
	add r0, #0xd4
	bl MOD62_0222E874
	bl FUN_0201C29C
	mov r0, #0x23
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_020223BC
	mov r0, #0x35
	bl MOD62_02230F70
	add r0, r5, #0x0
	bl FUN_0200627C
	bl FUN_0201CD04
	mov r0, #0x35
	bl FUN_020168D0
	ldr r0, _02085D68 ; =SDK_OVERLAY_MODULE_08_ID
	bl UnloadOverlayByID
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02085D64: .word 0x00000428
_02085D68: .word SDK_OVERLAY_MODULE_08_ID

	thumb_func_start FUN_02085D6C
FUN_02085D6C: ; 0x02085D6C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, r1
	bge _02085D7C
	bl ErrorHandling
	mov r1, #0x0
_02085D7C:
	lsl r0, r1, #0x2
	add r0, r4, r0
	ldr r0, [r0, #0x4]
	pop {r4, pc}

	thumb_func_start FUN_02085D84
FUN_02085D84: ; 0x02085D84
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02085D8C
FUN_02085D8C: ; 0x02085D8C
	add r0, #0x2c
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02085D94
FUN_02085D94: ; 0x02085D94
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02085D9C
FUN_02085D9C: ; 0x02085D9C
	add r0, #0x2d
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02085DA4
FUN_02085DA4: ; 0x02085DA4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	add r0, r5, #0x0
	ldr r7, [r6, #0x8]
	bl FUN_02046528
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x14]
	cmp r0, #0x6
	bls _02085DC2
	b _02085F38
_02085DC2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02085DCE: ; jump table (using 16-bit offset)
	.short _02085DDC - _02085DCE - 2; case 0
	.short _02085E38 - _02085DCE - 2; case 1
	.short _02085E48 - _02085DCE - 2; case 2
	.short _02085E66 - _02085DCE - 2; case 3
	.short _02085EA6 - _02085DCE - 2; case 4
	.short _02085F14 - _02085DCE - 2; case 5
	.short _02085F20 - _02085DCE - 2; case 6
_02085DDC:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r6, #0x10]
	bl FUN_02029C80
	str r0, [r7, #0x20]
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_02085D8C
	ldr r0, [r6, #0x10]
	bl FUN_0206BB1C
	str r0, [r7, #0x1c]
	bl FUN_0206B9AC
	mov r4, #0x0
	str r0, [sp, #0x0]
	str r0, [r7, #0x0]
	cmp r0, #0x0
	ble _02085E1E
	add r5, r7, #0x0
_02085E0A:
	ldr r0, [r7, #0x1c]
	add r1, r4, #0x0
	bl FUN_0206B9B0
	str r0, [r5, #0x4]
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r0
	blt _02085E0A
_02085E1E:
	cmp r4, #0x6
	bge _02085E32
	lsl r0, r4, #0x2
	add r1, r7, r0
	mov r0, #0x0
_02085E28:
	add r4, r4, #0x1
	str r0, [r1, #0x4]
	add r1, r1, #0x4
	cmp r4, #0x6
	blt _02085E28
_02085E32:
	mov r0, #0x1
	str r0, [r6, #0x14]
	b _02085F38
_02085E38:
	ldr r1, _02085F40 ; =UNK_020FCAD8
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl FUN_02046500
	mov r0, #0x2
	str r0, [r6, #0x14]
	b _02085F38
_02085E48:
	ldr r0, [r6, #0x8]
	bl FUN_02085D94
	cmp r0, #0x0
	beq _02085E5A
	cmp r0, #0x1
	beq _02085E60
	bl ErrorHandling
_02085E5A:
	mov r0, #0x5
	str r0, [r6, #0x14]
	b _02085F38
_02085E60:
	mov r0, #0x3
	str r0, [r6, #0x14]
	b _02085F38
_02085E66:
	ldr r4, [r6, #0xc]
	ldr r0, [r7, #0x1c]
	str r0, [r4, #0x0]
	ldr r0, [r6, #0x10]
	bl FUN_0206F158
	str r0, [r4, #0x4]
	ldr r0, [r6, #0x10]
	bl FUN_02025838
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x22
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0xf
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r0, [r7, #0x24]
	ldr r1, _02085F44 ; =UNK_020F96DC
	str r0, [r4, #0xc]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02046500
	mov r0, #0x4
	str r0, [r6, #0x14]
	b _02085F38
_02085EA6:
	ldr r0, [r6, #0x8]
	ldr r4, [r6, #0xc]
	bl FUN_02085D84
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	add r4, #0x22
	ldrb r1, [r4, #0x0]
	cmp r1, #0x7
	beq _02085F0E
	ldr r0, [r6, #0x8]
	bl FUN_02085D6C
	mov r1, #0xa1
	add r2, sp, #0x8
	add r5, r0, #0x0
	bl FUN_02067830
	ldr r1, [sp, #0x8]
	ldr r0, [r7, #0x20]
	sub r1, r1, #0x1
	bl FUN_02029C8C
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xaa
	bl FUN_02067830
	ldr r1, [sp, #0x8]
	ldr r0, [r7, #0x20]
	sub r1, r1, #0x1
	bl FUN_02029C8C
	mov r1, #0x0
	bl FUN_02029CC8
	bl FUN_02029CE0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02085FD0
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	lsl r2, r4, #0x18
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02061798
_02085F0E:
	mov r0, #0x1
	str r0, [r6, #0x14]
	b _02085F38
_02085F14:
	add r0, r5, #0x0
	bl FUN_0204AF84
	mov r0, #0x6
	str r0, [r6, #0x14]
	b _02085F38
_02085F20:
	ldr r0, [r6, #0xc]
	bl FUN_02016A18
	ldr r0, [r6, #0x8]
	bl FUN_02016A18
	add r0, r6, #0x0
	bl FUN_02016A18
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02085F38:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02085F40: .word UNK_020FCAD8
_02085F44: .word UNK_020F96DC

	thumb_func_start FUN_02085F48
FUN_02085F48: ; 0x02085F48
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x18
	bl FUN_020169D8
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x18
	mov r0, #0x0
_02085F5E:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _02085F5E
	mov r0, #0xb
	mov r1, #0x30
	str r5, [r4, #0x10]
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x30
	str r0, [r4, #0x8]
	bl memset
	add r0, r5, #0x0
	bl LoadPlayerDataAddress
	ldr r1, [r4, #0x8]
	str r0, [r1, #0x24]
	ldr r0, [r4, #0x8]
	mov r1, #0x40
	str r5, [r0, #0x28]
	mov r0, #0xb
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	str r0, [r4, #0xc]
	bl memset
	ldr r1, _02085FA8 ; =FUN_02085DA4
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
	nop
_02085FA8: .word FUN_02085DA4

	thumb_func_start FUN_02085FAC
FUN_02085FAC: ; 0x02085FAC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02085FC8 ; =0x0000032A
	cmp r4, r0
	blo _02085FBA
	bl ErrorHandling
_02085FBA:
	mov r0, #0xa
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02085FCC ; =UNK_020FCAE8
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02085FC8: .word 0x0000032A
_02085FCC: .word UNK_020FCAE8

	thumb_func_start FUN_02085FD0
FUN_02085FD0: ; 0x02085FD0
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02085FEC ; =0x0000032A
	cmp r4, r0
	blo _02085FDE
	bl ErrorHandling
_02085FDE:
	mov r0, #0xa
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02085FF0 ; =UNK_020FCAEA
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_02085FEC: .word 0x0000032A
_02085FF0: .word UNK_020FCAEA

	thumb_func_start FUN_02085FF4
FUN_02085FF4: ; 0x02085FF4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02086010 ; =0x0000032A
	cmp r4, r0
	blo _02086002
	bl ErrorHandling
_02086002:
	mov r0, #0xa
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02086014 ; =UNK_020FCAEC
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_02086010: .word 0x0000032A
_02086014: .word UNK_020FCAEC

	thumb_func_start FUN_02086018
FUN_02086018: ; 0x02086018
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02086034 ; =0x0000032A
	cmp r4, r0
	blo _02086026
	bl ErrorHandling
_02086026:
	mov r0, #0xa
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02086038 ; =UNK_020FCAED
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_02086034: .word 0x0000032A
_02086038: .word UNK_020FCAED

	thumb_func_start FUN_0208603C
FUN_0208603C: ; 0x0208603C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02086058 ; =0x0000032A
	cmp r4, r0
	blo _0208604A
	bl ErrorHandling
_0208604A:
	mov r0, #0xa
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _0208605C ; =UNK_020FCAEE
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02086058: .word 0x0000032A
_0208605C: .word UNK_020FCAEE

	thumb_func_start FUN_02086060
FUN_02086060: ; 0x02086060
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0208607C ; =0x0000032A
	cmp r4, r0
	blo _0208606E
	bl ErrorHandling
_0208606E:
	mov r0, #0xa
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02086080 ; =UNK_020FCAF0
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_0208607C: .word 0x0000032A
_02086080: .word UNK_020FCAF0
