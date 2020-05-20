    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020799E8
FUN_020799E8: ; 0x020799E8
	lsl r1, r0, #0x1
	ldr r0, _020799F0 ; =0x020FA60C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_020799F0: .word 0x020FA60C

	thumb_func_start FUN_020799F4
FUN_020799F4: ; 0x020799F4
	push {r3, lr}
	add r2, r0, #0x0
	mul r2, r0
	add r0, r1, #0x0
	mul r0, r1
	add r0, r2, r0
	lsl r0, r0, #0x4
	bl SVC_Sqrt
	lsr r0, r0, #0x2
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02079A0C
FUN_02079A0C: ; 0x02079A0C
	push {r4, lr}
	add r4, r0, #0x0
	mul r0, r2
	bl _u32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bne _02079A22
	cmp r4, #0x0
	beq _02079A22
	mov r0, #0x1
_02079A22:
	pop {r4, pc}

	thumb_func_start FUN_02079A24
FUN_02079A24: ; 0x02079A24
	push {r4, lr}
	add r4, r0, #0x0
	lsl r0, r1, #0x8
	lsl r4, r4, #0x8
	lsr r1, r0, #0x1
	cmp r4, r1
	bls _02079A36
	mov r0, #0x3
	pop {r4, pc}
_02079A36:
	mov r1, #0x5
	bl _u32_div_f
	cmp r4, r0
	bls _02079A44
	mov r0, #0x2
	pop {r4, pc}
_02079A44:
	cmp r4, #0x0
	beq _02079A4C
	mov r0, #0x1
	b _02079A4E
_02079A4C:
	mov r0, #0x0
_02079A4E:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}

	thumb_func_start FUN_02079A54
FUN_02079A54: ; 0x02079A54
	push {r4, lr}
	add r4, r2, #0x0
	cmp r0, r1
	bne _02079A60
	mov r0, #0x4
	pop {r4, pc}
_02079A60:
	lsl r2, r4, #0x18
	lsr r2, r2, #0x18
	bl FUN_02079A0C
	add r1, r4, #0x0
	bl FUN_02079A24
	pop {r4, pc}

	thumb_func_start FUN_02079A70
FUN_02079A70: ; 0x02079A70
	push {lr}
	sub sp, #0xc
	cmp r0, #0x0
	bne _02079A90
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	mov r0, #0x0
	str r1, [sp, #0x8]
	add r1, r2, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
_02079A90:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r1, [sp, #0x8]
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_02079AAC
FUN_02079AAC: ; 0x02079AAC
	push {r4-r5}
	ldr r3, _02079B5C ; =0x021C48B8
	mov r2, #0x0
	ldr r3, [r3, #0x4c]
	mov r5, #0x40
	ldrsh r4, [r0, r2]
	tst r5, r3
	beq _02079ADE
	add r3, r4, #0x1
	strh r3, [r0, #0x0]
	ldrsh r2, [r0, r2]
	cmp r2, r1
	ble _02079ACA
	mov r1, #0x1
	strh r1, [r0, #0x0]
_02079ACA:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079AD8
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079AD8:
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02079ADE:
	mov r5, #0x80
	tst r5, r3
	beq _02079B04
	sub r3, r4, #0x1
	strh r3, [r0, #0x0]
	ldrsh r2, [r0, r2]
	cmp r2, #0x0
	bgt _02079AF0
	strh r1, [r0, #0x0]
_02079AF0:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079AFE
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079AFE:
	mov r0, #0x2
	pop {r4-r5}
	bx lr
_02079B04:
	mov r5, #0x20
	tst r5, r3
	beq _02079B2E
	add r1, r4, #0x0
	sub r1, #0xa
	strh r1, [r0, #0x0]
	ldrsh r1, [r0, r2]
	cmp r1, #0x0
	bgt _02079B1A
	mov r1, #0x1
	strh r1, [r0, #0x0]
_02079B1A:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079B28
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079B28:
	mov r0, #0x2
	pop {r4-r5}
	bx lr
_02079B2E:
	mov r5, #0x10
	tst r3, r5
	beq _02079B56
	add r3, r4, #0x0
	add r3, #0xa
	strh r3, [r0, #0x0]
	ldrsh r2, [r0, r2]
	cmp r2, r1
	ble _02079B42
	strh r1, [r0, #0x0]
_02079B42:
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, r4
	bne _02079B50
	add r0, r1, #0x0
	pop {r4-r5}
	bx lr
_02079B50:
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02079B56:
	add r0, r2, #0x0
	pop {r4-r5}
	bx lr
	.balign 4
_02079B5C: .word 0x021C48B8

	thumb_func_start FUN_02079B60
FUN_02079B60: ; 0x02079B60
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r1, #0x0
	add r6, r0, #0x0
	ldr r1, [sp, #0x28]
	add r0, r3, #0x0
	str r2, [sp, #0x4]
	ldr r5, [sp, #0x2c]
	ldr r4, [sp, #0x34]
	bl LoadFromNARC_7
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_020169D8
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x28]
	add r2, r7, #0x0
	bl FUN_02006774
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _02079B9A
	cmp r0, #0x1
	beq _02079BC6
	cmp r0, #0x2
	beq _02079C10
	b _02079C36
_02079B9A:
	add r0, r7, #0x0
	add r1, sp, #0x10
	bl FUN_020B0088
	cmp r4, #0x0
	bne _02079BAE
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02079BAE:
	add r0, sp, #0x18
	ldrh r0, [r0, #0x20]
	lsl r1, r5, #0x18
	lsr r1, r1, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	add r0, r6, #0x0
	ldr r2, [r2, #0x14]
	add r3, r4, #0x0
	bl FUN_02017E14
	b _02079C36
_02079BC6:
	add r0, r7, #0x0
	add r1, sp, #0xc
	bl FUN_020B0180
	cmp r4, #0x0
	bne _02079BDA
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02079BDA:
	lsl r1, r5, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	bl FUN_0201886C
	cmp r0, #0x0
	beq _02079BF8
	ldr r2, [sp, #0xc]
	lsl r1, r5, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	add r2, #0xc
	add r3, r4, #0x0
	bl FUN_02017DFC
_02079BF8:
	add r0, sp, #0x18
	ldrh r0, [r0, #0x20]
	lsl r1, r5, #0x18
	lsr r1, r1, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0xc]
	add r0, r6, #0x0
	add r2, #0xc
	add r3, r4, #0x0
	bl FUN_02017CE8
	b _02079C36
_02079C10:
	add r0, r7, #0x0
	add r1, sp, #0x8
	bl FUN_020B0138
	cmp r4, #0x0
	bne _02079C24
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_02079C24:
	ldr r1, [sp, #0x8]
	add r3, sp, #0x18
	lsl r0, r5, #0x18
	ldrh r3, [r3, #0x20]
	ldr r1, [r1, #0xc]
	lsr r0, r0, #0x18
	add r2, r4, #0x0
	bl FUN_02017FB4
_02079C36:
	add r0, r7, #0x0
	bl FUN_02016A18
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_02079C40
FUN_02079C40: ; 0x02079C40
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r6, r0, #0x0
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r7, r3, #0x0
	bl LoadFromNARC_7
	add r1, r0, #0x0
	ldr r0, [sp, #0x18]
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02006774
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_020B0180
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02079C70
FUN_02079C70: ; 0x02079C70
	push {r3, lr}
	bl FUN_020462AC
	bl FUN_0205F184
	pop {r3, pc}

	thumb_func_start FUN_02079C7C
FUN_02079C7C: ; 0x02079C7C
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r1, #0x1
	lsl r1, r1, #0x1a
	ldr r0, [r1, #0x0]
	ldr r2, _02079DA0 ; =0xFFFFE0FF
	and r0, r2
	str r0, [r1, #0x0]
	ldr r0, _02079DA4 ; =0x04001000
	ldr r3, [r0, #0x0]
	and r2, r3
	str r2, [r0, #0x0]
	ldr r3, [r1, #0x0]
	ldr r2, _02079DA8 ; =0xFFFF1FFF
	and r3, r2
	str r3, [r1, #0x0]
	ldr r3, [r0, #0x0]
	add r1, #0x50
	and r2, r3
	str r2, [r0, #0x0]
	mov r2, #0x0
	strh r2, [r1, #0x0]
	add r0, #0x50
	strh r2, [r0, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	mov r2, #0x1
	mov r0, #0x3
	mov r1, #0x13
	lsl r2, r2, #0x12
	bl FUN_0201681C
	ldr r1, _02079DAC ; =0x0000069C
	add r0, r4, #0x0
	mov r2, #0x13
	bl FUN_02006268
	ldr r2, _02079DAC ; =0x0000069C
	mov r1, #0x0
	add r5, r0, #0x0
	bl memset
	add r0, r4, #0x0
	bl FUN_0200628C
	mov r1, #0x93
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	mov r0, #0x13
	bl FUN_02016B94
	mov r1, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x13
	add r2, r1, #0x0
	bl FUN_02014BF4
	mov r1, #0x2d
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	mov r0, #0x0
	mov r1, #0x13
	bl FUN_02002C84
	bl FUN_0201CC08
	mov r0, #0x4
	bl FUN_0201CC24
	add r0, r5, #0x0
	bl FUN_0207B028
	bl FUN_02079F58
	ldr r0, [r5, #0x0]
	bl FUN_02079F78
	add r0, r5, #0x0
	bl FUN_0207A0CC
	bl FUN_0207A188
	add r0, r5, #0x0
	bl FUN_0207EF6C
	add r0, r5, #0x0
	bl FUN_0207A1A0
	add r0, r5, #0x0
	bl FUN_0207AAB0
	add r0, r5, #0x0
	bl FUN_0207C328
	add r0, r5, #0x0
	bl FUN_0207C448
	add r0, r5, #0x0
	bl FUN_0207F840
	add r0, r5, #0x0
	bl FUN_0207C71C
	add r0, r5, #0x0
	bl FUN_0207C77C
	add r0, r5, #0x0
	bl FUN_0207D5BC
	add r0, r5, #0x0
	bl FUN_0207AF58
	add r0, r5, #0x0
	bl FUN_0207F95C
	add r0, r5, #0x0
	bl FUN_0207F098
	ldr r0, _02079DB0 ; =FUN_02079F24
	add r1, r5, #0x0
	bl FUN_02015F10
	bl FUN_0201E788
	mov r1, #0x0
	mov r0, #0x3d
	add r2, r1, #0x0
	bl FUN_0200433C
	bl FUN_02033F20
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02079DA0: .word 0xFFFFE0FF
_02079DA4: .word 0x04001000
_02079DA8: .word 0xFFFF1FFF
_02079DAC: .word 0x0000069C
_02079DB0: .word FUN_02079F24

	thumb_func_start FUN_02079DB4
FUN_02079DB4: ; 0x02079DB4
	push {r3-r5, lr}
	add r4, r1, #0x0
	bl FUN_02006278
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	cmp r1, #0x13
	bhi _02079EA2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02079DD0: ; jump table (using 16-bit offset)
	.short _02079DF8 - _02079DD0 - 2; case 0
	.short _02079E06 - _02079DD0 - 2; case 1
	.short _02079E0E - _02079DD0 - 2; case 2
	.short _02079E16 - _02079DD0 - 2; case 3
	.short _02079E1E - _02079DD0 - 2; case 4
	.short _02079E26 - _02079DD0 - 2; case 5
	.short _02079E2E - _02079DD0 - 2; case 6
	.short _02079E36 - _02079DD0 - 2; case 7
	.short _02079E3E - _02079DD0 - 2; case 8
	.short _02079E46 - _02079DD0 - 2; case 9
	.short _02079E4E - _02079DD0 - 2; case 10
	.short _02079E56 - _02079DD0 - 2; case 11
	.short _02079E5E - _02079DD0 - 2; case 12
	.short _02079E66 - _02079DD0 - 2; case 13
	.short _02079E6E - _02079DD0 - 2; case 14
	.short _02079E76 - _02079DD0 - 2; case 15
	.short _02079E7E - _02079DD0 - 2; case 16
	.short _02079E86 - _02079DD0 - 2; case 17
	.short _02079E8E - _02079DD0 - 2; case 18
	.short _02079E96 - _02079DD0 - 2; case 19
_02079DF8:
	mov r0, #0x0
	mov r1, #0x13
	bl FUN_02079A70
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02079EA2
_02079E06:
	bl FUN_0207A2D8
	str r0, [r4, #0x0]
	b _02079EA2
_02079E0E:
	bl FUN_0207A310
	str r0, [r4, #0x0]
	b _02079EA2
_02079E16:
	bl FUN_0207A448
	str r0, [r4, #0x0]
	b _02079EA2
_02079E1E:
	bl FUN_0207A45C
	str r0, [r4, #0x0]
	b _02079EA2
_02079E26:
	bl FUN_0207A470
	str r0, [r4, #0x0]
	b _02079EA2
_02079E2E:
	bl FUN_0207A484
	str r0, [r4, #0x0]
	b _02079EA2
_02079E36:
	bl FUN_0207A498
	str r0, [r4, #0x0]
	b _02079EA2
_02079E3E:
	bl FUN_0207A57C
	str r0, [r4, #0x0]
	b _02079EA2
_02079E46:
	bl FUN_0207A654
	str r0, [r4, #0x0]
	b _02079EA2
_02079E4E:
	bl FUN_0207A760
	str r0, [r4, #0x0]
	b _02079EA2
_02079E56:
	bl FUN_0207A77C
	str r0, [r4, #0x0]
	b _02079EA2
_02079E5E:
	bl FUN_0207A790
	str r0, [r4, #0x0]
	b _02079EA2
_02079E66:
	bl FUN_0207A7A4
	str r0, [r4, #0x0]
	b _02079EA2
_02079E6E:
	bl FUN_0207A818
	str r0, [r4, #0x0]
	b _02079EA2
_02079E76:
	bl FUN_0207A884
	str r0, [r4, #0x0]
	b _02079EA2
_02079E7E:
	bl FUN_0207AA20
	str r0, [r4, #0x0]
	b _02079EA2
_02079E86:
	bl FUN_0207AA70
	str r0, [r4, #0x0]
	b _02079EA2
_02079E8E:
	bl FUN_0207AA88
	str r0, [r4, #0x0]
	b _02079EA2
_02079E96:
	bl FUN_0207AA98
	cmp r0, #0x1
	bne _02079EA2
	mov r0, #0x1
	pop {r3-r5, pc}
_02079EA2:
	add r0, r5, #0x0
	bl FUN_0207C3F4
	add r0, r5, #0x0
	bl FUN_0207CC88
	add r0, r5, #0x0
	bl FUN_0207D3F4
	ldr r0, _02079EC8 ; =0x00000404
	ldr r0, [r5, r0]
	bl FUN_0200BC1C
	add r0, r5, #0x0
	bl FUN_0207F008
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02079EC8: .word 0x00000404

	thumb_func_start FUN_02079ECC
FUN_02079ECC: ; 0x02079ECC
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02006278
	add r5, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	add r0, r5, #0x0
	bl FUN_0207F068
	add r0, r5, #0x0
	bl FUN_0207C3D4
	add r0, r5, #0x0
	bl FUN_0207D74C
	ldr r0, [r5, #0x0]
	bl FUN_0207A08C
	bl FUN_0201CD04
	bl FUN_0201C29C
	add r0, r5, #0x0
	bl FUN_0207A264
	mov r0, #0x0
	bl FUN_02002CC0
	ldr r0, _02079F20 ; =0x04000050
	mov r1, #0x0
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0200627C
	mov r0, #0x13
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02079F20: .word 0x04000050

	thumb_func_start FUN_02079F24
FUN_02079F24: ; 0x02079F24
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0201AB60
	mov r0, #0xae
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020081C4
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r3, _02079F50 ; =0x027E0000
	ldr r1, _02079F54 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_02079F50: .word 0x027E0000
_02079F54: .word 0x00003FF8

	thumb_func_start FUN_02079F58
FUN_02079F58: ; 0x02079F58
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _02079F74 ; =0x020FA6C0
	add r3, sp, #0x0
	mov r2, #0x5
_02079F62:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02079F62
	add r0, sp, #0x0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.balign 4
_02079F74: .word 0x020FA6C0

	thumb_func_start FUN_02079F78
FUN_02079F78: ; 0x02079F78
	push {r4-r5, lr}
	sub sp, #0x9c
	ldr r5, _0207A074 ; =0x020FA624
	add r3, sp, #0x8c
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _0207A078 ; =0x020FA650
	add r3, sp, #0x70
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02018744
	ldr r5, _0207A07C ; =0x020FA66C
	add r3, sp, #0x54
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02018744
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl FUN_0201AEE4
	ldr r5, _0207A080 ; =0x020FA688
	add r3, sp, #0x38
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	ldr r5, _0207A084 ; =0x020FA6A4
	add r3, sp, #0x1c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02018744
	ldr r5, _0207A088 ; =0x020FA634
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x5
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	mov r0, #0x1
	mov r1, #0x20
	mov r2, #0x0
	mov r3, #0x13
	bl FUN_02017F18
	mov r0, #0x4
	mov r1, #0x20
	mov r2, #0x0
	mov r3, #0x13
	bl FUN_02017F18
	add sp, #0x9c
	pop {r4-r5, pc}
	nop
_0207A074: .word 0x020FA624
_0207A078: .word 0x020FA650
_0207A07C: .word 0x020FA66C
_0207A080: .word 0x020FA688
_0207A084: .word 0x020FA6A4
_0207A088: .word 0x020FA634

	thumb_func_start FUN_0207A08C
FUN_0207A08C: ; 0x0207A08C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201E6D8
	bl FUN_0201E740
	add r0, r4, #0x0
	mov r1, #0x5
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_020178A0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_020178A0
	mov r0, #0x13
	add r1, r4, #0x0
	bl FUN_02016A8C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207A0CC
FUN_0207A0CC: ; 0x0207A0CC
	push {r4, lr}
	sub sp, #0x10
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r4, r0, #0x0
	str r1, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r3, #0x3
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	mov r1, #0x3
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	add r3, r1, #0x0
	bl FUN_020068C8
	mov r2, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	mov r0, #0x27
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_02006930
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0xb
	mov r3, #0x2
	bl FUN_020068C8
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0x2
	mov r3, #0x4
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0x10
	mov r3, #0x5
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x13
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x0]
	mov r0, #0x27
	mov r1, #0xf
	mov r3, #0x5
	bl FUN_020068C8
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	mov r0, #0x27
	mov r1, #0xe
	mov r2, #0x4
	bl FUN_02006930
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_0207A188
FUN_0207A188: ; 0x0207A188
	push {r3, lr}
	mov r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, _0207A19C ; =0x04000050
	mov r1, #0x1
	mov r2, #0x1e
	mov r3, #0x17
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.balign 4
_0207A19C: .word 0x04000050

	thumb_func_start FUN_0207A1A0
FUN_0207A1A0: ; 0x0207A1A0
	push {r4, lr}
	mov r2, #0x65
	add r4, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0x13
	bl FUN_0200A86C
	ldr r1, _0207A250 ; =0x00000674
	mov r2, #0x79
	str r0, [r4, r1]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0x13
	bl FUN_0200A86C
	ldr r1, _0207A254 ; =0x00000678
	mov r2, #0x0
	str r0, [r4, r1]
	mov r0, #0x1
	mov r1, #0x2
	mov r3, #0x13
	bl FUN_0200B870
	mov r1, #0x67
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	mov r0, #0x13
	bl FUN_0200AA80
	ldr r1, _0207A258 ; =0x0000067C
	str r0, [r4, r1]
	mov r0, #0xc
	mov r1, #0x13
	bl FUN_020219F4
	mov r1, #0x25
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	mov r0, #0xc
	mov r1, #0x13
	bl FUN_020219F4
	mov r1, #0x95
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x8
	mov r1, #0x13
	bl FUN_020219F4
	mov r1, #0x96
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x80
	mov r1, #0x13
	bl FUN_020219F4
	mov r1, #0x1a
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	mov r2, #0x93
	mov r0, #0x0
	mov r1, #0x1a
	lsl r2, r2, #0x2
	mov r3, #0x13
	bl FUN_0200A86C
	ldr r1, _0207A25C ; =0x00000688
	str r0, [r4, r1]
	mov r0, #0x8
	mov r1, #0x13
	bl FUN_020219F4
	ldr r2, _0207A260 ; =0x00000684
	str r0, [r4, r2]
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0207A24C
	ldr r0, [r4, r2]
	bl FUN_02021E28
_0207A24C:
	pop {r4, pc}
	nop
_0207A250: .word 0x00000674
_0207A254: .word 0x00000678
_0207A258: .word 0x0000067C
_0207A25C: .word 0x00000688
_0207A260: .word 0x00000684

	thumb_func_start FUN_0207A264
FUN_0207A264: ; 0x0207A264
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207A2C4 ; =0x00000688
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	ldr r0, _0207A2C8 ; =0x00000678
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	ldr r0, _0207A2CC ; =0x00000674
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	mov r0, #0x67
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_0200B990
	ldr r0, _0207A2D0 ; =0x0000067C
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	mov r0, #0x25
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02021A20
	mov r0, #0x95
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02021A20
	mov r0, #0x96
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02021A20
	mov r0, #0x1a
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	bl FUN_02021A20
	ldr r0, _0207A2D4 ; =0x00000684
	ldr r0, [r4, r0]
	bl FUN_02021A20
	pop {r4, pc}
	.balign 4
_0207A2C4: .word 0x00000688
_0207A2C8: .word 0x00000678
_0207A2CC: .word 0x00000674
_0207A2D0: .word 0x0000067C
_0207A2D4: .word 0x00000684

	thumb_func_start FUN_0207A2D8
FUN_0207A2D8: ; 0x0207A2D8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0207A30C
	add r0, r4, #0x0
	bl FUN_0207F8D0
	add r0, r4, #0x0
	bl FUN_0207AF20
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207A300
	mov r0, #0x9
	pop {r4, pc}
_0207A300:
	cmp r0, #0x4
	bne _0207A308
	mov r0, #0xf
	pop {r4, pc}
_0207A308:
	mov r0, #0x2
	pop {r4, pc}
_0207A30C:
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0207A310
FUN_0207A310: ; 0x0207A310
	push {r4-r6, lr}
	ldr r3, _0207A438 ; =0x0000068F
	add r4, r0, #0x0
	ldrb r1, [r4, r3]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	cmp r1, #0x1
	bne _0207A32E
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4-r6, pc}
_0207A32E:
	ldr r2, _0207A43C ; =0x021C48B8
	mov r1, #0x20
	ldr r5, [r2, #0x4c]
	add r6, r5, #0x0
	tst r6, r1
	beq _0207A344
	sub r1, #0x21
	bl FUN_0207B178
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A344:
	mov r1, #0x10
	tst r1, r5
	beq _0207A354
	mov r1, #0x1
	bl FUN_0207B178
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A354:
	mov r1, #0x40
	add r6, r5, #0x0
	tst r6, r1
	beq _0207A366
	sub r1, #0x41
	bl FUN_0207B3F0
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A366:
	mov r1, #0x80
	tst r1, r5
	beq _0207A376
	mov r1, #0x1
	bl FUN_0207B3F0
	mov r0, #0x2
	pop {r4-r6, pc}
_0207A376:
	ldr r1, [r2, #0x48]
	mov r0, #0x2
	tst r0, r1
	beq _0207A394
	sub r3, #0xb2
	add r0, r3, #0x0
	bl FUN_020054C8
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4-r6, pc}
_0207A394:
	mov r0, #0x1
	tst r0, r1
	beq _0207A420
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x3
	bne _0207A3BE
	sub r0, r3, #0x3
	ldrsb r0, [r4, r0]
	cmp r0, #0x4
	bne _0207A3BE
	sub r3, #0xb2
	add r0, r3, #0x0
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207C23C
	pop {r4-r6, pc}
_0207A3BE:
	ldr r0, _0207A440 ; =0x0000068C
	ldrsb r1, [r4, r0]
	cmp r1, #0x3
	bne _0207A3D6
	add r0, #0x10
	bl FUN_020054C8
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0x3
	pop {r4-r6, pc}
_0207A3D6:
	cmp r1, #0x5
	bne _0207A3EA
	add r0, #0x10
	bl FUN_020054C8
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0x5
	pop {r4-r6, pc}
_0207A3EA:
	cmp r1, #0x6
	bne _0207A408
	add r1, r0, #0x0
	add r1, #0xd
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207A420
	sub r0, #0xaf
	bl FUN_020054C8
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0xb
	pop {r4-r6, pc}
_0207A408:
	cmp r1, #0x7
	bne _0207A420
	sub r0, #0xaf
	bl FUN_020054C8
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4-r6, pc}
_0207A420:
	add r0, r4, #0x0
	bl FUN_0207B200
	cmp r0, #0x1
	bne _0207A434
	ldr r0, _0207A444 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	mov r0, #0xe
	pop {r4-r6, pc}
_0207A434:
	mov r0, #0x2
	pop {r4-r6, pc}
	.balign 4
_0207A438: .word 0x0000068F
_0207A43C: .word 0x021C48B8
_0207A440: .word 0x0000068C
_0207A444: .word 0x0000068E

	thumb_func_start FUN_0207A448
FUN_0207A448: ; 0x0207A448
	push {r3, lr}
	bl FUN_0207B66C
	cmp r0, #0x1
	bne _0207A456
	mov r0, #0x7
	pop {r3, pc}
_0207A456:
	mov r0, #0x3
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A45C
FUN_0207A45C: ; 0x0207A45C
	push {r3, lr}
	bl FUN_0207B788
	cmp r0, #0x1
	bne _0207A46A
	mov r0, #0x2
	pop {r3, pc}
_0207A46A:
	mov r0, #0x4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A470
FUN_0207A470: ; 0x0207A470
	push {r3, lr}
	bl FUN_0207BAEC
	cmp r0, #0x1
	bne _0207A47E
	mov r0, #0x7
	pop {r3, pc}
_0207A47E:
	mov r0, #0x5
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A484
FUN_0207A484: ; 0x0207A484
	push {r3, lr}
	bl FUN_0207BBF0
	cmp r0, #0x1
	bne _0207A492
	mov r0, #0x2
	pop {r3, pc}
_0207A492:
	mov r0, #0x6
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A498
FUN_0207A498: ; 0x0207A498
	push {r4, lr}
	ldr r1, _0207A568 ; =0x021C48B8
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x40
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A4C2
	sub r1, #0x41
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A4BE
	ldr r0, _0207A56C ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A4BE:
	mov r0, #0x7
	pop {r4, pc}
_0207A4C2:
	mov r1, #0x80
	tst r1, r2
	beq _0207A4E2
	mov r1, #0x1
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A4DE
	ldr r0, _0207A56C ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A4DE:
	mov r0, #0x7
	pop {r4, pc}
_0207A4E2:
	mov r0, #0x1
	tst r0, r2
	beq _0207A542
	ldr r0, _0207A570 ; =0x0000068D
	ldrb r1, [r4, r0]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, #0x4
	bne _0207A510
	add r0, #0xf
	bl FUN_020054C8
	ldr r0, _0207A574 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, r0, #0x2
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207A50C
	mov r0, #0x4
	pop {r4, pc}
_0207A50C:
	mov r0, #0x6
	pop {r4, pc}
_0207A510:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x1
	beq _0207A542
	sub r0, #0xb0
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207CBE8
	ldr r2, _0207A570 ; =0x0000068D
	mov r1, #0xf0
	ldrb r3, [r4, r2]
	add r0, r3, #0x0
	bic r0, r1
	lsl r1, r3, #0x1c
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r4, r2]
	mov r0, #0x8
	pop {r4, pc}
_0207A542:
	mov r0, #0x2
	tst r0, r2
	beq _0207A564
	ldr r0, _0207A578 ; =0x0000069C
	bl FUN_020054C8
	ldr r0, _0207A574 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, r0, #0x2
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207A560
	mov r0, #0x4
	pop {r4, pc}
_0207A560:
	mov r0, #0x6
	pop {r4, pc}
_0207A564:
	mov r0, #0x7
	pop {r4, pc}
	.balign 4
_0207A568: .word 0x021C48B8
_0207A56C: .word 0x000005DC
_0207A570: .word 0x0000068D
_0207A574: .word 0x0000068E
_0207A578: .word 0x0000069C

	thumb_func_start FUN_0207A57C
FUN_0207A57C: ; 0x0207A57C
	push {r4, lr}
	ldr r1, _0207A644 ; =0x021C48B8
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x40
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A5A6
	sub r1, #0x41
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A5A2
	ldr r0, _0207A648 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A5A2:
	mov r0, #0x8
	pop {r4, pc}
_0207A5A6:
	mov r1, #0x80
	tst r1, r2
	beq _0207A5C6
	mov r1, #0x1
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A5C2
	ldr r0, _0207A648 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A5C2:
	mov r0, #0x8
	pop {r4, pc}
_0207A5C6:
	mov r0, #0x1
	tst r0, r2
	beq _0207A622
	mov r0, #0x43
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207A64C ; =0x0000068D
	ldrb r1, [r4, r0]
	lsl r2, r1, #0x1c
	lsr r2, r2, #0x1c
	cmp r2, #0x4
	beq _0207A618
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	cmp r2, r1
	beq _0207A618
	sub r0, #0xb0
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B9C0
	ldr r1, _0207A64C ; =0x0000068D
	add r0, r4, #0x0
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r1, r1, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_0207CB08
	add r0, r4, #0x0
	bl FUN_0207ED30
	add r0, r4, #0x0
	bl FUN_0207B8D8
	b _0207A61E
_0207A618:
	ldr r0, _0207A650 ; =0x000005DD
	bl FUN_020054C8
_0207A61E:
	mov r0, #0x7
	pop {r4, pc}
_0207A622:
	mov r0, #0x2
	tst r0, r2
	beq _0207A63E
	ldr r0, _0207A650 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x43
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	mov r0, #0x7
	pop {r4, pc}
_0207A63E:
	mov r0, #0x8
	pop {r4, pc}
	nop
_0207A644: .word 0x021C48B8
_0207A648: .word 0x000005DC
_0207A64C: .word 0x0000068D
_0207A650: .word 0x000005DD

	thumb_func_start FUN_0207A654
FUN_0207A654: ; 0x0207A654
	push {r4, lr}
	ldr r1, _0207A750 ; =0x021C48B8
	add r4, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x20
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A66E
	sub r1, #0x21
	bl FUN_0207B178
	mov r0, #0x9
	pop {r4, pc}
_0207A66E:
	mov r1, #0x10
	tst r1, r2
	beq _0207A67E
	mov r1, #0x1
	bl FUN_0207B178
	mov r0, #0x9
	pop {r4, pc}
_0207A67E:
	mov r1, #0x40
	add r3, r2, #0x0
	tst r3, r1
	beq _0207A6A0
	sub r1, #0x41
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A69C
	ldr r0, _0207A754 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A69C:
	mov r0, #0x9
	pop {r4, pc}
_0207A6A0:
	mov r1, #0x80
	tst r1, r2
	beq _0207A6C0
	mov r1, #0x1
	bl FUN_0207B878
	cmp r0, #0x1
	bne _0207A6BC
	ldr r0, _0207A754 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207B8D8
_0207A6BC:
	mov r0, #0x9
	pop {r4, pc}
_0207A6C0:
	mov r0, #0x1
	tst r0, r2
	beq _0207A72C
	ldr r0, _0207A758 ; =0x000005DD
	bl FUN_020054C8
	ldr r0, _0207A75C ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0x4
	beq _0207A712
	lsl r0, r0, #0x1
	add r1, r4, r0
	mov r0, #0xa1
	lsl r0, r0, #0x2
	ldrh r0, [r1, r0]
	bl FUN_0206EA54
	cmp r0, #0x1
	bne _0207A712
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0207A712
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	add r0, r4, #0x0
	bl FUN_0207BD58
	add r0, r4, #0x0
	bl FUN_0207EDB4
	mov r0, #0xa
	pop {r4, pc}
_0207A712:
	ldr r0, _0207A75C ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1c
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	strb r2, [r1, #0x16]
	ldr r0, [r4, r0]
	mov r1, #0x0
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4, pc}
_0207A72C:
	mov r0, #0x2
	tst r0, r2
	beq _0207A74C
	ldr r0, _0207A758 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	mov r2, #0x4
	strb r2, [r1, #0x16]
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	mov r0, #0x12
	pop {r4, pc}
_0207A74C:
	mov r0, #0x9
	pop {r4, pc}
	.balign 4
_0207A750: .word 0x021C48B8
_0207A754: .word 0x000005DC
_0207A758: .word 0x000005DD
_0207A75C: .word 0x0000068D

	thumb_func_start FUN_0207A760
FUN_0207A760: ; 0x0207A760
	push {r3, lr}
	ldr r1, _0207A778 ; =0x021C48B8
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	beq _0207A774
	bl FUN_0207B8D8
	mov r0, #0x9
	pop {r3, pc}
_0207A774:
	mov r0, #0xa
	pop {r3, pc}
	.balign 4
_0207A778: .word 0x021C48B8

	thumb_func_start FUN_0207A77C
FUN_0207A77C: ; 0x0207A77C
	push {r3, lr}
	bl FUN_0207BE68
	cmp r0, #0x1
	bne _0207A78A
	mov r0, #0xd
	pop {r3, pc}
_0207A78A:
	mov r0, #0xb
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A790
FUN_0207A790: ; 0x0207A790
	push {r3, lr}
	bl FUN_0207BF90
	cmp r0, #0x1
	bne _0207A79E
	mov r0, #0x2
	pop {r3, pc}
_0207A79E:
	mov r0, #0xc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207A7A4
FUN_0207A7A4: ; 0x0207A7A4
	push {r3-r5, lr}
	ldr r3, _0207A80C ; =0x021C48B8
	mov r1, #0x20
	ldr r2, [r3, #0x4c]
	add r4, r0, #0x0
	add r5, r2, #0x0
	tst r5, r1
	beq _0207A7BE
	sub r1, #0x21
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7BE:
	mov r1, #0x10
	tst r1, r2
	beq _0207A7CE
	mov r1, #0x1
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7CE:
	mov r1, #0x40
	add r5, r2, #0x0
	tst r5, r1
	beq _0207A7E0
	sub r1, #0x44
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7E0:
	mov r1, #0x80
	tst r1, r2
	beq _0207A7F0
	mov r1, #0x4
	bl FUN_0207C07C
	mov r0, #0xd
	pop {r3-r5, pc}
_0207A7F0:
	ldr r1, [r3, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207A808
	ldr r0, _0207A810 ; =0x000005DD
	bl FUN_020054C8
	ldr r0, _0207A814 ; =0x0000068E
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r0, #0xc
	pop {r3-r5, pc}
_0207A808:
	mov r0, #0xd
	pop {r3-r5, pc}
	.balign 4
_0207A80C: .word 0x021C48B8
_0207A810: .word 0x000005DD
_0207A814: .word 0x0000068E

	thumb_func_start FUN_0207A818
FUN_0207A818: ; 0x0207A818
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207FB28
	cmp r0, #0x1
	bne _0207A82A
	ldr r0, _0207A878 ; =0x0000068E
	ldrb r0, [r4, r0]
	pop {r4, pc}
_0207A82A:
	ldr r1, _0207A87C ; =0x00000695
	ldrb r0, [r4, r1]
	cmp r0, #0x1
	bne _0207A874
	add r1, r1, #0x1
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0207FC40
	add r1, r0, #0x0
	cmp r1, #0x7
	bne _0207A850
	ldr r2, _0207A880 ; =0x0000068F
	mov r0, #0xf0
	ldrb r3, [r4, r2]
	bic r3, r0
	mov r0, #0x10
	orr r0, r3
	strb r0, [r4, r2]
_0207A850:
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _0207A86E
	cmp r1, #0x1
	beq _0207A866
	cmp r1, #0x7
	bne _0207A874
_0207A866:
	add r0, r4, #0x0
	bl FUN_0207B0CC
	b _0207A874
_0207A86E:
	add r0, r4, #0x0
	bl FUN_0207B0CC
_0207A874:
	mov r0, #0xe
	pop {r4, pc}
	.balign 4
_0207A878: .word 0x0000068E
_0207A87C: .word 0x00000695
_0207A880: .word 0x0000068F

	thumb_func_start FUN_0207A884
FUN_0207A884: ; 0x0207A884
	push {r4-r6, lr}
	sub sp, #0x8
	ldr r1, _0207AA00 ; =0x021C48B8
	add r5, r0, #0x0
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	bne _0207A896
	b _0207A9FA
_0207A896:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldrb r1, [r1, #0x11]
	cmp r1, #0x2
	bne _0207A8BA
	bl FUN_0207B628
	add r6, r0, #0x0
	mov r0, #0x13
	bl FUN_020669C0
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02069A64
	b _0207A8C0
_0207A8BA:
	bl FUN_0207B628
	add r4, r0, #0x0
_0207A8C0:
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x24]
	bl FUN_0208821C
	ldr r0, _0207AA04 ; =0x0000068E
	mov r2, #0x0
	strb r2, [r5, r0]
	ldr r0, _0207AA08 ; =0x00000295
	mov r1, #0x13
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	bl FUN_020671BC
	ldr r1, _0207AA08 ; =0x00000295
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A8F4
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x1
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A8F4:
	ldr r0, _0207AA0C ; =0x00000296
	mov r1, #0x14
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, _0207AA0C ; =0x00000296
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A916
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x2
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A916:
	ldr r0, _0207AA10 ; =0x00000297
	mov r1, #0x15
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, _0207AA10 ; =0x00000297
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A938
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x4
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A938:
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r1, #0x16
	mov r2, #0x0
	bl FUN_020671BC
	mov r1, #0xa6
	lsl r1, r1, #0x2
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A95E
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x8
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A95E:
	ldr r0, _0207AA14 ; =0x00000299
	mov r1, #0x17
	ldrb r6, [r5, r0]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, _0207AA14 ; =0x00000299
	strb r0, [r5, r1]
	ldrb r0, [r5, r1]
	cmp r6, r0
	beq _0207A980
	ldr r1, _0207AA04 ; =0x0000068E
	mov r0, #0x10
	ldrb r2, [r5, r1]
	orr r0, r2
	strb r0, [r5, r1]
_0207A980:
	add r0, r4, #0x0
	mov r1, #0x18
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, _0207AA18 ; =0x0000029A
	strb r0, [r5, r1]
	sub r1, #0x4e
	ldr r0, [r5, r1]
	ldrb r0, [r0, #0x11]
	cmp r0, #0x2
	bne _0207A99E
	add r0, r4, #0x0
	bl FUN_02016A18
_0207A99E:
	mov r1, #0x7
	mov r0, #0x0
	lsl r1, r1, #0x6
	mov r2, #0x13
	bl FUN_02002EEC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x4]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r2, _0207AA1C ; =0x000003E2
	mov r1, #0x1
	mov r3, #0xd
	bl FUN_0200CD68
	ldr r0, _0207AA04 ; =0x0000068E
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	bne _0207A9E2
	add r0, r5, #0x0
	mov r1, #0xfe
	bl FUN_0207EECC
	add sp, #0x8
	mov r0, #0x11
	pop {r4-r6, pc}
_0207A9E2:
	add r0, r5, #0x0
	bl FUN_0207F608
	add r0, r5, #0x0
	bl FUN_0207CC24
	add r0, r5, #0x0
	bl FUN_0207CF78
	add sp, #0x8
	mov r0, #0x10
	pop {r4-r6, pc}
_0207A9FA:
	mov r0, #0xf
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0207AA00: .word 0x021C48B8
_0207AA04: .word 0x0000068E
_0207AA08: .word 0x00000295
_0207AA0C: .word 0x00000296
_0207AA10: .word 0x00000297
_0207AA14: .word 0x00000299
_0207AA18: .word 0x0000029A
_0207AA1C: .word 0x000003E2

	thumb_func_start FUN_0207AA20
FUN_0207AA20: ; 0x0207AA20
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0207AA68 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207AA62
	ldr r0, _0207AA6C ; =0x0000068E
	mov r1, #0x0
	ldrb r2, [r5, r0]
	mov r0, #0x1
_0207AA36:
	add r4, r0, #0x0
	lsl r4, r1
	add r3, r2, #0x0
	tst r3, r4
	beq _0207AA58
	add r0, r5, #0x0
	bl FUN_0207EECC
	ldr r0, _0207AA6C ; =0x0000068E
	ldrb r1, [r5, r0]
	eor r1, r4
	strb r1, [r5, r0]
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	bne _0207AA62
	mov r0, #0x11
	pop {r3-r5, pc}
_0207AA58:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x5
	blo _0207AA36
_0207AA62:
	mov r0, #0x10
	pop {r3-r5, pc}
	nop
_0207AA68: .word 0x021C48B8
_0207AA6C: .word 0x0000068E

	thumb_func_start FUN_0207AA70
FUN_0207AA70: ; 0x0207AA70
	ldr r0, _0207AA84 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _0207AA7E
	mov r0, #0x12
	bx lr
_0207AA7E:
	mov r0, #0x11
	bx lr
	nop
_0207AA84: .word 0x021C48B8

	thumb_func_start FUN_0207AA88
FUN_0207AA88: ; 0x0207AA88
	push {r3, lr}
	mov r0, #0x1
	mov r1, #0x13
	bl FUN_02079A70
	mov r0, #0x13
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207AA98
FUN_0207AA98: ; 0x0207AA98
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0207AAA6
	mov r0, #0x1
	b _0207AAA8
_0207AAA6:
	mov r0, #0x0
_0207AAA8:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207AAB0
FUN_0207AAB0: ; 0x0207AAB0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207B628
	mov r2, #0x93
	lsl r2, r2, #0x2
	add r1, r0, #0x0
	ldr r0, [r4, r2]
	ldrb r0, [r0, #0x11]
	cmp r0, #0x2
	bne _0207AAD2
	add r2, r2, #0x4
	add r0, r4, #0x0
	add r2, r4, r2
	bl FUN_0207AAE0
	pop {r4, pc}
_0207AAD2:
	add r2, r2, #0x4
	add r0, r4, #0x0
	add r2, r4, r2
	bl FUN_0207AB0C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207AAE0
FUN_0207AAE0: ; 0x0207AAE0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x13
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_020669C0
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02069A64
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0207AB0C
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207AB0C
FUN_0207AB0C: ; 0x0207AB0C
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r5, r2, #0x0
	bl FUN_020669D4
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0xc]
	add r0, r6, #0x0
	bl FUN_020690E4
	ldr r2, _0207AEAC ; =0x00000674
	add r4, r0, #0x0
	ldr r0, [r7, r2]
	add r2, #0xc
	ldr r2, [r7, r2]
	mov r1, #0xb
	bl FUN_0200A8E0
	ldr r0, _0207AEB0 ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r7, r0]
	add r2, r4, #0x0
	bl FUN_0200AC60
	ldr r2, _0207AEB0 ; =0x0000067C
	mov r1, #0x25
	ldr r0, [r7, r2]
	lsl r1, r1, #0x4
	add r2, r2, #0x4
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	bl FUN_0200B7B8
	ldr r2, _0207AEAC ; =0x00000674
	mov r1, #0x0
	ldr r0, [r7, r2]
	add r2, #0xc
	ldr r2, [r7, r2]
	bl FUN_0200A8E0
	ldr r0, _0207AEB0 ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r7, r0]
	add r2, r4, #0x0
	bl FUN_0200ACF8
	ldr r2, _0207AEB0 ; =0x0000067C
	mov r1, #0x95
	ldr r0, [r7, r2]
	lsl r1, r1, #0x2
	add r2, r2, #0x4
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	bl FUN_0200B7B8
	ldr r2, _0207AEAC ; =0x00000674
	mov r1, #0xe
	ldr r0, [r7, r2]
	add r2, #0xc
	ldr r2, [r7, r2]
	bl FUN_0200A8E0
	ldr r0, _0207AEB0 ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r7, r0]
	add r2, r4, #0x0
	bl FUN_0200AD18
	ldr r2, _0207AEB0 ; =0x0000067C
	mov r1, #0x96
	ldr r0, [r7, r2]
	lsl r1, r1, #0x2
	add r2, r2, #0x4
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	bl FUN_0200B7B8
	add r0, r6, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0xe]
	add r0, r6, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	ldrb r1, [r5, #0x12]
	mov r2, #0x7f
	lsl r0, r0, #0x18
	bic r1, r2
	lsr r2, r0, #0x18
	mov r0, #0x7f
	and r0, r2
	orr r0, r1
	strb r0, [r5, #0x12]
	add r0, r6, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x1f
	ldr r2, [r5, #0x50]
	ldr r1, _0207AEB4 ; =0xEFFFFFFF
	lsr r0, r0, #0x3
	and r1, r2
	orr r0, r1
	str r0, [r5, #0x50]
	add r0, r6, #0x0
	mov r1, #0xaf
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _0207AC16
	ldr r0, [r5, #0x50]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	bne _0207AC16
	ldrb r1, [r5, #0x12]
	mov r0, #0x80
	bic r1, r0
	strb r1, [r5, #0x12]
	b _0207AC1E
_0207AC16:
	ldrb r1, [r5, #0x12]
	mov r0, #0x80
	orr r0, r1
	strb r0, [r5, #0x12]
_0207AC1E:
	add r0, r6, #0x0
	bl FUN_020689E0
	ldrb r1, [r5, #0x13]
	mov r2, #0x3
	bic r1, r2
	mov r2, #0x3
	and r0, r2
	orr r0, r1
	strb r0, [r5, #0x13]
	add r0, r6, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1a
	ldrb r1, [r5, #0x13]
	mov r2, #0xfc
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r5, #0x13]
	add r0, r6, #0x0
	mov r1, #0xb0
	mov r2, #0x0
	bl FUN_020671BC
	strb r0, [r5, #0x10]
	add r0, r6, #0x0
	mov r1, #0xb1
	mov r2, #0x0
	bl FUN_020671BC
	strb r0, [r5, #0x11]
	add r0, r6, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x14]
	add r0, r6, #0x0
	mov r1, #0x8
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x18]
	add r0, r6, #0x0
	mov r1, #0x9c
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x44
	strb r0, [r1, #0x0]
	ldrb r1, [r5, #0x12]
	ldrh r0, [r5, #0xc]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x19
	bl FUN_02068758
	str r0, [r5, #0x1c]
	ldrb r0, [r5, #0x12]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x19
	cmp r1, #0x64
	bne _0207ACAA
	ldr r0, [r5, #0x1c]
	b _0207ACB2
_0207ACAA:
	ldrh r0, [r5, #0xc]
	add r1, r1, #0x1
	bl FUN_02068758
_0207ACB2:
	str r0, [r5, #0x20]
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x24]
	add r0, r6, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x26]
	add r0, r6, #0x0
	mov r1, #0xa4
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x28]
	add r0, r6, #0x0
	mov r1, #0xa5
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x2a]
	add r0, r6, #0x0
	mov r1, #0xa7
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x2c]
	add r0, r6, #0x0
	mov r1, #0xa8
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x2e]
	add r0, r6, #0x0
	mov r1, #0xa6
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x30]
	add r0, r6, #0x0
	mov r1, #0xa
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x32
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02068854
	add r1, r5, #0x0
	add r1, #0x33
	strb r0, [r1, #0x0]
	mov r4, #0x0
_0207AD26:
	lsl r0, r4, #0x1
	add r0, r5, r0
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [sp, #0x0]
	mov r2, #0x0
	strh r0, [r1, #0x34]
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x3a
	bl FUN_020671BC
	add r1, r5, r4
	add r1, #0x3c
	strb r0, [r1, #0x0]
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x34]
	bl FUN_0206AB30
	add r1, r5, r4
	add r1, #0x40
	strb r0, [r1, #0x0]
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x4
	blo _0207AD26
	add r0, r6, #0x0
	mov r1, #0x13
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x45
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x14
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x46
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x15
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x47
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x16
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x48
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x17
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x49
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x18
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x4a
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	mov r1, #0x5
	add r0, #0x4b
	strb r1, [r0, #0x0]
	mov r4, #0x0
_0207ADE0:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02069BC8
	cmp r0, #0x1
	bne _0207ADF4
	add r0, r5, #0x0
	add r0, #0x4b
	strb r4, [r0, #0x0]
	b _0207ADFE
_0207ADF4:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x5
	blo _0207ADE0
_0207ADFE:
	add r0, r6, #0x0
	mov r1, #0xb
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x4c
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x4e
	strh r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_0207C2D4
	mov r1, #0xf
	ldr r2, [r5, #0x50]
	lsl r1, r1, #0x1c
	and r2, r1
	ldr r1, _0207AEB8 ; =0x0FFFFFFF
	and r0, r1
	orr r0, r2
	str r0, [r5, #0x50]
	add r0, r6, #0x0
	bl FUN_02069E94
	cmp r0, #0x1
	bne _0207AE4E
	ldr r1, [r5, #0x50]
	ldr r0, _0207AEBC ; =0x3FFFFFFF
	and r1, r0
	mov r0, #0x2
	lsl r0, r0, #0x1e
	orr r0, r1
	str r0, [r5, #0x50]
	b _0207AE84
_0207AE4E:
	add r0, r6, #0x0
	bl FUN_02069E74
	cmp r0, #0x1
	bne _0207AE7C
	ldr r2, [r5, #0x50]
	ldr r1, _0207AEBC ; =0x3FFFFFFF
	add r0, r5, #0x0
	and r2, r1
	add r1, r1, #0x1
	orr r1, r2
	str r1, [r5, #0x50]
	lsl r1, r1, #0x4
	lsr r1, r1, #0x4
	add r0, #0x50
	cmp r1, #0x7
	bne _0207AE84
	mov r1, #0xf
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x1c
	and r1, r2
	str r1, [r0, #0x0]
	b _0207AE84
_0207AE7C:
	ldr r1, [r5, #0x50]
	ldr r0, _0207AEBC ; =0x3FFFFFFF
	and r0, r1
	str r0, [r5, #0x50]
_0207AE84:
	add r0, r6, #0x0
	bl FUN_02068A80
	cmp r0, #0x1
	ldr r1, [r5, #0x50]
	bne _0207AE98
	mov r0, #0x2
	lsl r0, r0, #0x1c
	orr r0, r1
	b _0207AE9C
_0207AE98:
	ldr r0, _0207AEC0 ; =0xDFFFFFFF
	and r0, r1
_0207AE9C:
	str r0, [r5, #0x50]
	mov r4, #0x0
	str r4, [r5, #0x54]
	str r4, [r5, #0x58]
	str r4, [r5, #0x5c]
	ldr r0, _0207AEC4 ; =0x00000699
	b _0207AEC8
	nop
_0207AEAC: .word 0x00000674
_0207AEB0: .word 0x0000067C
_0207AEB4: .word 0xEFFFFFFF
_0207AEB8: .word 0x0FFFFFFF
_0207AEBC: .word 0x3FFFFFFF
_0207AEC0: .word 0xDFFFFFFF
_0207AEC4: .word 0x00000699
_0207AEC8:
	str r4, [r5, #0x60]
	strb r4, [r7, r0]
_0207AECC:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x0
	bl FUN_0207FC5C
	add r1, r0, #0x0
	add r0, r6, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0207AF04
	lsr r0, r4, #0x5
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1f
	add r2, r4, #0x0
	and r2, r1
	mov r1, #0x1
	ldr r3, [r0, #0x54]
	lsl r1, r2
	orr r1, r3
	str r1, [r0, #0x54]
	ldr r0, _0207AF1C ; =0x00000699
	ldrb r0, [r7, r0]
	add r1, r0, #0x1
	ldr r0, _0207AF1C ; =0x00000699
	strb r1, [r7, r0]
_0207AF04:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x50
	blo _0207AECC
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	bl FUN_02066A20
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0207AF1C: .word 0x00000699

	thumb_func_start FUN_0207AF20
FUN_0207AF20: ; 0x0207AF20
	push {r3, lr}
	mov r2, #0x2a
	lsl r2, r2, #0x4
	ldr r1, [r0, r2]
	lsl r1, r1, #0x3
	lsr r1, r1, #0x1f
	bne _0207AF54
	add r1, r2, #0x0
	sub r1, #0x44
	ldrh r3, [r0, r1]
	add r1, r2, #0x0
	sub r1, #0xe7
	cmp r3, r1
	bne _0207AF4E
	sub r2, #0x54
	ldr r0, [r0, r2]
	mov r1, #0x0
	ldr r0, [r0, #0x28]
	mov r2, #0x64
	add r3, r1, #0x0
	bl FUN_02005E90
	pop {r3, pc}
_0207AF4E:
	add r0, r3, #0x0
	bl FUN_02005578
_0207AF54:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207AF58
FUN_0207AF58: ; 0x0207AF58
	push {r4, lr}
	mov r1, #0x93
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	ldr r0, [r4, r1]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x4
	bhi _0207AFA4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207AF74: ; jump table (using 16-bit offset)
	.short _0207AF7E - _0207AF74 - 2; case 0
	.short _0207AF7E - _0207AF74 - 2; case 1
	.short _0207AF96 - _0207AF74 - 2; case 2
	.short _0207AF9E - _0207AF74 - 2; case 3
	.short _0207AF9E - _0207AF74 - 2; case 4
_0207AF7E:
	add r1, #0x54
	ldr r0, [r4, r1]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	ldr r0, _0207AFFC ; =0x0000068C
	bne _0207AF90
	mov r1, #0x0
	strb r1, [r4, r0]
	b _0207AFA4
_0207AF90:
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207AFA4
_0207AF96:
	ldr r0, _0207AFFC ; =0x0000068C
	mov r1, #0x3
	strb r1, [r4, r0]
	b _0207AFA4
_0207AF9E:
	ldr r0, _0207AFFC ; =0x0000068C
	mov r1, #0x4
	strb r1, [r4, r0]
_0207AFA4:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207C5D4
	add r0, r4, #0x0
	bl FUN_0207C838
	add r0, r4, #0x0
	bl FUN_0207D2C8
	add r0, r4, #0x0
	bl FUN_0207C6A4
	add r0, r4, #0x0
	bl FUN_0207CE4C
	add r0, r4, #0x0
	bl FUN_0207CC24
	add r0, r4, #0x0
	bl FUN_0207D604
	add r0, r4, #0x0
	bl FUN_0207DD88
	add r0, r4, #0x0
	bl FUN_0207B228
	add r0, r4, #0x0
	bl FUN_0207F2A0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207AFFA
	add r0, r4, #0x0
	bl FUN_0207BA74
_0207AFFA:
	pop {r4, pc}
	.balign 4
_0207AFFC: .word 0x0000068C

	thumb_func_start FUN_0207B000
FUN_0207B000: ; 0x0207B000
	push {r3-r6}
	mov r6, #0x0
	strb r6, [r0, #0x15]
	add r0, #0x15
	mov r3, #0x1
_0207B00A:
	ldrb r5, [r1, r6]
	cmp r5, #0x8
	beq _0207B024
	add r2, r3, #0x0
	ldrb r4, [r0, #0x0]
	lsl r2, r5
	orr r2, r4
	strb r2, [r0, #0x0]
	add r2, r6, #0x1
	lsl r2, r2, #0x18
	lsr r6, r2, #0x18
	cmp r6, #0x8
	blo _0207B00A
_0207B024:
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_0207B028
FUN_0207B028: ; 0x0207B028
	push {r3-r4}
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	ldr r1, [r4, #0x2c]
	cmp r1, #0x1
	beq _0207B06C
	ldrb r2, [r4, #0x15]
	mov r1, #0x10
	add r3, r2, #0x0
	tst r3, r1
	beq _0207B044
	eor r1, r2
	strb r1, [r4, #0x15]
_0207B044:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	mov r1, #0x20
	ldrb r2, [r4, #0x15]
	add r3, r2, #0x0
	tst r3, r1
	beq _0207B058
	eor r1, r2
	strb r1, [r4, #0x15]
_0207B058:
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r3, [r0, r1]
	mov r0, #0x40
	ldrb r1, [r3, #0x15]
	add r2, r1, #0x0
	tst r2, r0
	beq _0207B06C
	eor r0, r1
	strb r0, [r3, #0x15]
_0207B06C:
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0207B070
FUN_0207B070: ; 0x0207B070
	mov r2, #0x2a
	lsl r2, r2, #0x4
	ldr r2, [r0, r2]
	lsl r2, r2, #0x3
	lsr r2, r2, #0x1f
	beq _0207B088
	cmp r1, #0x1
	beq _0207B088
	cmp r1, #0x7
	beq _0207B088
	mov r0, #0x0
	bx lr
_0207B088:
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r0, [r0, r2]
	ldrb r2, [r0, #0x15]
	mov r0, #0x1
	lsl r0, r1
	and r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_0207B09C
FUN_0207B09C: ; 0x0207B09C
	push {r3-r4}
	mov r3, #0x93
	lsl r3, r3, #0x2
	ldr r0, [r0, r3]
	mov r2, #0x0
	ldrb r0, [r0, #0x15]
	add r1, r2, #0x0
	mov r3, #0x1
_0207B0AC:
	add r4, r3, #0x0
	lsl r4, r1
	tst r4, r0
	beq _0207B0BA
	add r2, r2, #0x1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
_0207B0BA:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x8
	blo _0207B0AC
	add r0, r2, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0207B0CC
FUN_0207B0CC: ; 0x0207B0CC
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	ldr r1, _0207B174 ; =0x0000068C
	add r5, r0, #0x0
	ldrsb r1, [r5, r1]
	cmp r1, r4
	beq _0207B170
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x2
	bne _0207B0EC
	bl FUN_0207BDD8
_0207B0EC:
	add r0, r5, #0x0
	bl FUN_0207D6F8
	ldr r0, _0207B174 ; =0x0000068C
	mov r1, #0x0
	strb r4, [r5, r0]
	add r0, r5, #0x0
	bl FUN_0207CFAC
	add r0, r5, #0x0
	bl FUN_0207C5D4
	add r0, r5, #0x0
	bl FUN_0207C6A4
	add r0, r5, #0x0
	bl FUN_0207C838
	add r0, r5, #0x0
	bl FUN_0207D2C8
	add r0, r5, #0x0
	bl FUN_0207CC24
	add r0, r5, #0x0
	bl FUN_0207D604
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0207D418
	mov r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	mov r0, #0x14
	str r0, [sp, #0x8]
	mov r2, #0x0
	str r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	mov r3, #0xe
	bl FUN_02018540
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	bl FUN_02017CD0
	add r0, r5, #0x0
	bl FUN_0207DD88
	add r0, r5, #0x0
	bl FUN_0207B228
	add r0, r5, #0x0
	bl FUN_0207F2A0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207B170
	add r0, r5, #0x0
	bl FUN_0207BDF4
_0207B170:
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_0207B174: .word 0x0000068C

	thumb_func_start FUN_0207B178
FUN_0207B178: ; 0x0207B178
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0207B1F8 ; =0x0000068C
	mov r6, #0x1
	ldrsb r4, [r5, r0]
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r12, r4
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	add r7, r6, #0x0
_0207B190:
	add r2, r4, r1
	lsl r2, r2, #0x18
	asr r4, r2, #0x18
	bpl _0207B19C
	mov r4, #0x7
	b _0207B1A2
_0207B19C:
	cmp r4, #0x7
	ble _0207B1A2
	mov r4, #0x0
_0207B1A2:
	cmp r0, #0x0
	bne _0207B1B8
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r2, [r5, r2]
	ldrb r3, [r2, #0x15]
	add r2, r6, #0x0
	lsl r2, r4
	tst r2, r3
	bne _0207B1D0
	b _0207B190
_0207B1B8:
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r2, [r5, r2]
	ldrb r3, [r2, #0x15]
	add r2, r7, #0x0
	lsl r2, r4
	tst r2, r3
	beq _0207B190
	cmp r4, #0x1
	beq _0207B1D0
	cmp r4, #0x7
	bne _0207B190
_0207B1D0:
	mov r0, r12
	cmp r4, r0
	beq _0207B1F4
	ldr r0, _0207B1FC ; =0x000005E1
	bl FUN_020054C8
	add r0, r5, #0x0
	bl FUN_0207FA38
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0207D418
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0207B0CC
_0207B1F4:
	pop {r3-r7, pc}
	nop
_0207B1F8: .word 0x0000068C
_0207B1FC: .word 0x000005E1

	thumb_func_start FUN_0207B200
FUN_0207B200: ; 0x0207B200
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207FA80
	cmp r0, #0xff
	bne _0207B210
	mov r0, #0x0
	pop {r4, pc}
_0207B210:
	ldr r1, _0207B224 ; =0x00000694
	mov r3, #0x0
	strb r3, [r4, r1]
	add r2, r1, #0x2
	strb r0, [r4, r2]
	add r0, r1, #0x1
	strb r3, [r4, r0]
	mov r0, #0x1
	pop {r4, pc}
	nop
_0207B224: .word 0x00000694

	thumb_func_start FUN_0207B228
FUN_0207B228: ; 0x0207B228
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	ldrb r0, [r1, #0x12]
	cmp r0, #0x2
	bne _0207B250
	ldrh r0, [r1, #0x18]
	cmp r0, #0x0
	beq _0207B250
	ldr r0, _0207B2AC ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x3
	bne _0207B24C
	mov r1, #0xc
	b _0207B256
_0207B24C:
	mov r1, #0xd
	b _0207B256
_0207B250:
	ldr r0, _0207B2AC ; =0x0000068C
	ldrsb r0, [r5, r0]
	add r1, r0, #0x3
_0207B256:
	mov r0, #0x27
	mov r2, #0x13
	bl LoadFromNarc_2
	add r1, sp, #0xc
	add r4, r0, #0x0
	bl FUN_020B0180
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	add r2, #0xc
	bl FUN_02018148
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	bl FUN_0201AC68
	add r0, r4, #0x0
	bl FUN_02016A18
	ldr r0, _0207B2AC ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x0
	bne _0207B29C
	add r0, r5, #0x0
	bl FUN_0207B364
	add sp, #0x10
	pop {r3-r5, pc}
_0207B29C:
	cmp r0, #0x2
	bne _0207B2A6
	add r0, r5, #0x0
	bl FUN_0207B2B0
_0207B2A6:
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_0207B2AC: .word 0x0000068C

	thumb_func_start FUN_0207B2B0
FUN_0207B2B0: ; 0x0207B2B0
	push {r4-r7, lr}
	sub sp, #0x14
	mov r1, #0x9d
	add r6, r0, #0x0
	lsl r1, r1, #0x2
	ldrh r0, [r6, r1]
	add r1, r1, #0x2
	ldrh r1, [r6, r1]
	mov r2, #0x30
	bl FUN_02079A54
	cmp r0, #0x4
	bhi _0207B2EC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207B2D6: ; jump table (using 16-bit offset)
	.short _0207B2E0 - _0207B2D6 - 2; case 0
	.short _0207B2E8 - _0207B2D6 - 2; case 1
	.short _0207B2E4 - _0207B2D6 - 2; case 2
	.short _0207B2E0 - _0207B2D6 - 2; case 3
	.short _0207B2E0 - _0207B2D6 - 2; case 4
_0207B2E0:
	ldr r7, _0207B35C ; =0x0000A0C0
	b _0207B2EC
_0207B2E4:
	ldr r7, _0207B360 ; =0x0000A0E0
	b _0207B2EC
_0207B2E8:
	mov r7, #0xa1
	lsl r7, r7, #0x8
_0207B2EC:
	mov r1, #0x9d
	lsl r1, r1, #0x2
	ldrh r0, [r6, r1]
	add r1, r1, #0x2
	ldrh r1, [r6, r1]
	mov r2, #0x30
	bl FUN_02079A0C
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r5, #0x0
	str r0, [sp, #0x10]
_0207B30A:
	cmp r4, #0x8
	blo _0207B312
	ldr r2, [sp, #0x10]
	b _0207B318
_0207B312:
	add r0, r7, r4
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0207B318:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r3, r5, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x11
	add r3, #0x18
	str r0, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	lsr r3, r3, #0x18
	bl FUN_02018540
	cmp r4, #0x8
	bhs _0207B33E
	mov r4, #0x0
	b _0207B344
_0207B33E:
	sub r4, #0x8
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
_0207B344:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x6
	blo _0207B30A
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	bl FUN_0201AC68
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_0207B35C: .word 0x0000A0C0
_0207B360: .word 0x0000A0E0

	thumb_func_start FUN_0207B364
FUN_0207B364: ; 0x0207B364
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r2, _0207B3EC ; =0x00000262
	add r6, r0, #0x0
	ldrb r0, [r6, r2]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	cmp r0, #0x64
	bhs _0207B38C
	add r0, r2, #0x0
	add r1, r2, #0x0
	add r0, #0xa
	add r1, #0xe
	add r2, r2, #0x6
	ldr r0, [r6, r0]
	ldr r1, [r6, r1]
	ldr r2, [r6, r2]
	sub r1, r1, r0
	sub r0, r2, r0
	b _0207B390
_0207B38C:
	mov r1, #0x0
	add r0, r1, #0x0
_0207B390:
	mov r2, #0x38
	bl FUN_02079A0C
	add r4, r0, #0x0
	mov r5, #0x0
	mov r7, #0x17
_0207B39C:
	cmp r4, #0x8
	blo _0207B3A4
	mov r2, #0xb4
	b _0207B3AC
_0207B3A4:
	add r0, r4, #0x0
	add r0, #0xac
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0207B3AC:
	str r7, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r3, r5, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x11
	add r3, #0x17
	str r0, [sp, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	lsr r3, r3, #0x18
	bl FUN_02018540
	cmp r4, #0x8
	bhs _0207B3D0
	mov r4, #0x0
	b _0207B3D6
_0207B3D0:
	sub r4, #0x8
	lsl r0, r4, #0x18
	lsr r4, r0, #0x18
_0207B3D6:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x7
	blo _0207B39C
	ldr r0, [r6, #0x0]
	mov r1, #0x3
	bl FUN_0201AC68
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0207B3EC: .word 0x00000262

	thumb_func_start FUN_0207B3F0
FUN_0207B3F0: ; 0x0207B3F0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207B4A4
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0207B49C
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	strb r0, [r1, #0x14]
	add r0, r4, #0x0
	bl FUN_0207AAB0
	add r0, r4, #0x0
	bl FUN_0207AF20
	add r0, r4, #0x0
	bl FUN_0207D768
	add r0, r4, #0x0
	bl FUN_0207D800
	add r0, r4, #0x0
	bl FUN_0207D8A0
	ldr r0, _0207B4A0 ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x0
	bne _0207B436
	add r0, r4, #0x0
	bl FUN_0207B364
	b _0207B44C
_0207B436:
	cmp r0, #0x2
	bne _0207B442
	add r0, r4, #0x0
	bl FUN_0207B2B0
	b _0207B44C
_0207B442:
	cmp r0, #0x4
	bne _0207B44C
	add r0, r4, #0x0
	bl FUN_0207F608
_0207B44C:
	add r0, r4, #0x0
	bl FUN_0207F934
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207C5D4
	add r0, r4, #0x0
	bl FUN_0207C6A4
	add r0, r4, #0x0
	bl FUN_0207CA44
	add r0, r4, #0x0
	bl FUN_0207C838
	add r0, r4, #0x0
	bl FUN_0207D2C8
	add r0, r4, #0x0
	bl FUN_0207CFEC
	add r0, r4, #0x0
	bl FUN_0207C71C
	add r0, r4, #0x0
	bl FUN_0207C77C
	add r0, r4, #0x0
	bl FUN_0207CC24
	add r0, r4, #0x0
	bl FUN_0207CE4C
	add r0, r4, #0x0
	bl FUN_0207DD88
_0207B49C:
	pop {r4, pc}
	nop
_0207B4A0: .word 0x0000068C

	thumb_func_start FUN_0207B4A4
FUN_0207B4A4: ; 0x0207B4A4
	push {r3, lr}
	mov r2, #0x93
	lsl r2, r2, #0x2
	ldr r2, [r0, r2]
	ldrb r2, [r2, #0x11]
	cmp r2, #0x0
	beq _0207B4BC
	cmp r2, #0x1
	beq _0207B4C2
	cmp r2, #0x2
	beq _0207B4C8
	b _0207B4CE
_0207B4BC:
	bl FUN_0207B4FC
	pop {r3, pc}
_0207B4C2:
	bl FUN_0207B564
	pop {r3, pc}
_0207B4C8:
	bl FUN_0207B5C0
	pop {r3, pc}
_0207B4CE:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}

	thumb_func_start FUN_0207B4D4
FUN_0207B4D4: ; 0x0207B4D4
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r0, r1]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x3
	bne _0207B4E4
	mov r0, #0x0
	bx lr
_0207B4E4:
	ldr r1, _0207B4F8 ; =0x0000068C
	ldrsb r0, [r0, r1]
	cmp r0, #0x1
	beq _0207B4F4
	cmp r0, #0x7
	beq _0207B4F4
	mov r0, #0x0
	bx lr
_0207B4F4:
	mov r0, #0x1
	bx lr
	.balign 4
_0207B4F8: .word 0x0000068C

	thumb_func_start FUN_0207B4FC
FUN_0207B4FC: ; 0x0207B4FC
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	str r1, [sp, #0x0]
	ldr r1, [r5, r0]
	mov r0, #0x14
	ldrsb r4, [r1, r0]
_0207B50C:
	ldr r0, [sp, #0x0]
	add r0, r4, r0
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	bmi _0207B522
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x13]
	cmp r4, r0
	blt _0207B528
_0207B522:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0207B528:
	bl FUN_020690C4
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	add r7, r4, #0x0
	ldr r6, [r1, #0x0]
	mul r7, r0
	add r0, r6, r7
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0207B50C
	add r0, r6, r7
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0207B55E
	add r0, r5, #0x0
	bl FUN_0207B4D4
	cmp r0, #0x1
	bne _0207B50C
_0207B55E:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207B564
FUN_0207B564: ; 0x0207B564
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	add r7, r1, #0x0
	ldr r1, [r5, r0]
	mov r0, #0x14
	ldrsb r4, [r1, r0]
_0207B574:
	add r0, r4, r7
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	bmi _0207B588
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	ldrb r0, [r1, #0x13]
	cmp r4, r0
	blt _0207B58E
_0207B588:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0207B58E:
	ldr r0, [r1, #0x0]
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0207B574
	add r0, r6, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0207B5BC
	add r0, r5, #0x0
	bl FUN_0207B4D4
	cmp r0, #0x1
	bne _0207B574
_0207B5BC:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0207B5C0
FUN_0207B5C0: ; 0x0207B5C0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	str r1, [sp, #0x0]
	ldr r1, [r5, r0]
	mov r0, #0x14
	ldrsb r4, [r1, r0]
_0207B5D0:
	ldr r0, [sp, #0x0]
	add r0, r4, r0
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
	bmi _0207B5E6
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrb r0, [r0, #0x13]
	cmp r4, r0
	blt _0207B5EC
_0207B5E6:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0207B5EC:
	bl FUN_020690C8
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	add r7, r4, #0x0
	ldr r6, [r1, #0x0]
	mul r7, r0
	add r0, r6, r7
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	beq _0207B5D0
	add r0, r6, r7
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	beq _0207B622
	add r0, r5, #0x0
	bl FUN_0207B4D4
	cmp r0, #0x1
	bne _0207B5D0
_0207B622:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207B628
FUN_0207B628: ; 0x0207B628
	push {r4, lr}
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r4, [r0, r1]
	ldrb r0, [r4, #0x11]
	cmp r0, #0x0
	beq _0207B640
	cmp r0, #0x1
	beq _0207B64E
	cmp r0, #0x2
	beq _0207B658
	b _0207B666
_0207B640:
	bl FUN_020690C4
	ldrb r1, [r4, #0x14]
	ldr r2, [r4, #0x0]
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0207B64E:
	ldrb r1, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9B0
	pop {r4, pc}
_0207B658:
	bl FUN_020690C8
	ldrb r1, [r4, #0x14]
	ldr r2, [r4, #0x0]
	mul r0, r1
	add r0, r2, r0
	pop {r4, pc}
_0207B666:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207B66C
FUN_0207B66C: ; 0x0207B66C
	push {r4, lr}
	ldr r1, _0207B774 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207B682
	cmp r1, #0x1
	beq _0207B6E2
	cmp r1, #0x2
	beq _0207B70E
	b _0207B76E
_0207B682:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl FUN_0201AEE4
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl FUN_0201AEE4
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_0201958C
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	ldr r1, _0207B778 ; =0x0000068D
	mov r0, #0xf
	ldrb r2, [r4, r1]
	bic r2, r0
	strb r2, [r4, r1]
	mov r2, #0x1
	add r0, r1, #0x1
	strb r2, [r4, r0]
	b _0207B76E
_0207B6E2:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02017B48
	cmp r0, #0x40
	ldr r0, [r4, #0x0]
	bgt _0207B702
	mov r2, #0x0
	mov r1, #0x2
	add r3, r2, #0x0
	bl FUN_0201AEE4
	ldr r0, _0207B774 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207B76E
_0207B702:
	mov r1, #0x2
	add r2, r1, #0x0
	mov r3, #0x40
	bl FUN_0201AEE4
	b _0207B76E
_0207B70E:
	bl FUN_0207ECDC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x1
	beq _0207B732
	add r0, r4, #0x0
	mov r1, #0x98
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
_0207B732:
	add r0, r4, #0x0
	bl FUN_0207B8D8
	ldr r0, _0207B77C ; =0x00000434
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	add r0, r4, #0x0
	bl FUN_0207D06C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0207B760
	ldr r0, _0207B780 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
_0207B760:
	ldr r0, _0207B784 ; =0x0000042C
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x1
	pop {r4, pc}
_0207B76E:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207B774: .word 0x0000068E
_0207B778: .word 0x0000068D
_0207B77C: .word 0x00000434
_0207B780: .word 0x00000438
_0207B784: .word 0x0000042C

	thumb_func_start FUN_0207B788
FUN_0207B788: ; 0x0207B788
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207B864 ; =0x0000068E
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	beq _0207B79E
	cmp r0, #0x1
	beq _0207B7F8
	cmp r0, #0x2
	beq _0207B824
	b _0207B860
_0207B79E:
	ldr r0, _0207B868 ; =0x00000434
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	ldr r0, _0207B86C ; =0x00000438
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	ldr r0, _0207B870 ; =0x00000454
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	ldr r0, _0207B874 ; =0x0000042C
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207ED18
	add r0, r4, #0x0
	bl FUN_0207EC94
	ldr r0, _0207B864 ; =0x0000068E
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207B860
_0207B7F8:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02017B48
	cmp r0, #0x80
	ldr r0, [r4, #0x0]
	blt _0207B818
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl FUN_0201AEE4
	ldr r0, _0207B864 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207B860
_0207B818:
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x40
	bl FUN_0201AEE4
	b _0207B860
_0207B824:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_02019220
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	add r0, r4, #0x0
	mov r1, #0x81
	bl FUN_0207D924
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207C6F0
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x1
	pop {r4, pc}
_0207B860:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0207B864: .word 0x0000068E
_0207B868: .word 0x00000434
_0207B86C: .word 0x00000438
_0207B870: .word 0x00000454
_0207B874: .word 0x0000042C

	thumb_func_start FUN_0207B878
FUN_0207B878: ; 0x0207B878
	push {r4-r7}
	add r5, r0, #0x0
	ldr r0, _0207B8D4 ; =0x0000068D
	mov r6, #0xa1
	ldrb r0, [r5, r0]
	mov r2, #0x4
	lsl r6, r6, #0x2
	lsl r0, r0, #0x1c
	lsr r4, r0, #0x1c
	add r3, r4, #0x0
	mov r0, #0x0
_0207B88E:
	add r3, r3, r1
	lsl r3, r3, #0x18
	asr r3, r3, #0x18
	bpl _0207B89A
	add r3, r2, #0x0
	b _0207B8A0
_0207B89A:
	cmp r3, #0x5
	bne _0207B8A0
	add r3, r0, #0x0
_0207B8A0:
	lsl r7, r3, #0x1
	add r7, r5, r7
	ldrh r7, [r7, r6]
	cmp r7, #0x0
	bne _0207B8AE
	cmp r3, #0x4
	bne _0207B88E
_0207B8AE:
	cmp r3, r4
	beq _0207B8CC
	ldr r2, _0207B8D4 ; =0x0000068D
	mov r1, #0xf
	ldrb r0, [r5, r2]
	bic r0, r1
	lsl r1, r3, #0x18
	lsr r3, r1, #0x18
	mov r1, #0xf
	and r1, r3
	orr r0, r1
	strb r0, [r5, r2]
	mov r0, #0x1
	pop {r4-r7}
	bx lr
_0207B8CC:
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_0207B8D4: .word 0x0000068D

	thumb_func_start FUN_0207B8D8
FUN_0207B8D8: ; 0x0207B8D8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207CBC0
	ldr r2, _0207B95C ; =0x0000068D
	ldrb r0, [r4, r2]
	lsl r0, r0, #0x1c
	lsr r1, r0, #0x1c
	cmp r1, #0x4
	bne _0207B930
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrh r1, [r0, #0x18]
	cmp r1, #0x0
	beq _0207B910
	sub r0, r2, #0x1
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207B908
	add r0, r4, #0x0
	bl FUN_0207B960
	pop {r4, pc}
_0207B908:
	add r0, r4, #0x0
	bl FUN_0207B99C
	pop {r4, pc}
_0207B910:
	sub r0, r2, #0x1
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207B924
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207B960
	pop {r4, pc}
_0207B924:
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207B99C
	pop {r4, pc}
_0207B930:
	sub r0, r2, #0x1
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207B94A
	lsl r1, r1, #0x1
	add r2, r4, r1
	mov r1, #0xa1
	lsl r1, r1, #0x2
	ldrh r1, [r2, r1]
	add r0, r4, #0x0
	bl FUN_0207B960
	pop {r4, pc}
_0207B94A:
	lsl r1, r1, #0x1
	add r2, r4, r1
	mov r1, #0xa1
	lsl r1, r1, #0x2
	ldrh r1, [r2, r1]
	add r0, r4, #0x0
	bl FUN_0207B99C
	pop {r4, pc}
	.balign 4
_0207B95C: .word 0x0000068D

	thumb_func_start FUN_0207B960
FUN_0207B960: ; 0x0207B960
	push {r3-r5, lr}
	mov r2, #0x0
	add r4, r1, #0x0
	mvn r2, r2
	add r5, r0, #0x0
	cmp r4, r2
	bne _0207B980
	bl FUN_0207EC94
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	pop {r3-r5, pc}
_0207B980:
	bl FUN_0207EB64
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207CB70
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_0200C63C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0207B99C
FUN_0207B99C: ; 0x0207B99C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0207BD84
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0207B9B6
	add r0, r5, #0x0
	bl FUN_0207EEB0
	pop {r3-r5, pc}
_0207B9B6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207EE2C
	pop {r3-r5, pc}

	thumb_func_start FUN_0207B9C0
FUN_0207B9C0: ; 0x0207B9C0
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl FUN_0207B628
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldrb r1, [r1, #0x11]
	cmp r1, #0x2
	ldr r1, _0207BA70 ; =0x0000068D
	bne _0207B9E6
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r1, r1, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_020698E8
	b _0207B9F4
_0207B9E6:
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x1c
	lsl r2, r2, #0x18
	lsr r1, r1, #0x1c
	lsr r2, r2, #0x1c
	bl FUN_020698E0
_0207B9F4:
	ldr r0, _0207BA70 ; =0x0000068D
	mov r1, #0xa1
	ldrb r6, [r4, r0]
	lsl r1, r1, #0x2
	add r5, r4, r1
	lsl r2, r6, #0x1c
	lsl r6, r6, #0x18
	lsr r6, r6, #0x1c
	lsl r6, r6, #0x1
	lsr r3, r2, #0x1b
	add r6, r4, r6
	ldrh r2, [r5, r3]
	ldrh r6, [r6, r1]
	strh r6, [r5, r3]
	ldrb r3, [r4, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	lsl r3, r3, #0x1
	add r3, r4, r3
	strh r2, [r3, r1]
	add r2, r1, #0x0
	add r2, #0x8
	ldrb r6, [r4, r0]
	add r5, r4, r2
	lsl r2, r6, #0x1c
	lsl r6, r6, #0x18
	lsr r6, r6, #0x1c
	add r7, r4, r6
	add r6, r1, #0x0
	lsr r3, r2, #0x1c
	add r6, #0x8
	ldrb r2, [r5, r3]
	ldrb r6, [r7, r6]
	strb r6, [r5, r3]
	ldrb r3, [r4, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x1c
	add r5, r4, r3
	add r3, r1, #0x0
	add r3, #0x8
	strb r2, [r5, r3]
	add r2, r1, #0x0
	add r2, #0xc
	ldrb r6, [r4, r0]
	add r5, r4, r2
	lsl r2, r6, #0x1c
	lsl r6, r6, #0x18
	lsr r6, r6, #0x1c
	add r7, r4, r6
	add r6, r1, #0x0
	lsr r3, r2, #0x1c
	add r6, #0xc
	ldrb r2, [r5, r3]
	ldrb r6, [r7, r6]
	add r1, #0xc
	strb r6, [r5, r3]
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	add r0, r4, r0
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	.balign 4
_0207BA70: .word 0x0000068D

	thumb_func_start FUN_0207BA74
FUN_0207BA74: ; 0x0207BA74
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_0201958C
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r2, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	add r3, r2, #0x0
	bl FUN_0201AEE4
	add r0, r4, #0x0
	bl FUN_0207ECDC
	add r0, r4, #0x0
	bl FUN_0207B8D8
	ldr r0, _0207BAE0 ; =0x00000434
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	add r0, r4, #0x0
	bl FUN_0207D06C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0207BAD4
	ldr r0, _0207BAE4 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
_0207BAD4:
	ldr r0, _0207BAE8 ; =0x0000042C
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
	.balign 4
_0207BAE0: .word 0x00000434
_0207BAE4: .word 0x00000438
_0207BAE8: .word 0x0000042C

	thumb_func_start FUN_0207BAEC
FUN_0207BAEC: ; 0x0207BAEC
	push {r4, lr}
	ldr r1, _0207BBE4 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207BB02
	cmp r1, #0x1
	beq _0207BB6E
	cmp r1, #0x2
	beq _0207BB9A
	b _0207BBDE
_0207BB02:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl FUN_0201AEE4
	mov r2, #0x3
	add r3, r2, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	add r3, #0xfd
	bl FUN_0201AEE4
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207BD84
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_0201958C
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	ldr r1, _0207BBE8 ; =0x0000068D
	mov r0, #0xf
	ldrb r2, [r4, r1]
	bic r2, r0
	strb r2, [r4, r1]
	mov r2, #0x1
	add r0, r1, #0x1
	strb r2, [r4, r0]
	b _0207BBDE
_0207BB6E:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02017B48
	cmp r0, #0x40
	ldr r0, [r4, #0x0]
	bgt _0207BB8E
	mov r2, #0x0
	mov r1, #0x2
	add r3, r2, #0x0
	bl FUN_0201AEE4
	ldr r0, _0207BBE4 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207BBDE
_0207BB8E:
	mov r1, #0x2
	add r2, r1, #0x0
	mov r3, #0x40
	bl FUN_0201AEE4
	b _0207BBDE
_0207BB9A:
	bl FUN_0207ECDC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x1
	beq _0207BBBE
	add r0, r4, #0x0
	mov r1, #0x98
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
_0207BBBE:
	add r0, r4, #0x0
	bl FUN_0207B8D8
	add r0, r4, #0x0
	bl FUN_0207D06C
	add r0, r4, #0x0
	bl FUN_0207D10C
	ldr r0, _0207BBEC ; =0x0000042C
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x1
	pop {r4, pc}
_0207BBDE:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207BBE4: .word 0x0000068E
_0207BBE8: .word 0x0000068D
_0207BBEC: .word 0x0000042C

	thumb_func_start FUN_0207BBF0
FUN_0207BBF0: ; 0x0207BBF0
	push {r4, lr}
	ldr r1, _0207BCBC ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207BC06
	cmp r1, #0x1
	beq _0207BC4E
	cmp r1, #0x2
	beq _0207BC7A
	b _0207BCB6
_0207BC06:
	bl FUN_0207D22C
	ldr r0, _0207BCC0 ; =0x00000454
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_0207BD84
	ldr r0, _0207BCC4 ; =0x0000042C
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207ED18
	add r0, r4, #0x0
	bl FUN_0207EEB0
	ldr r0, _0207BCBC ; =0x0000068E
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207BCB6
_0207BC4E:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02017B48
	cmp r0, #0x80
	ldr r0, [r4, #0x0]
	blt _0207BC6E
	mov r1, #0x2
	mov r2, #0x0
	mov r3, #0x88
	bl FUN_0201AEE4
	ldr r0, _0207BCBC ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207BCB6
_0207BC6E:
	mov r1, #0x2
	mov r2, #0x1
	mov r3, #0x40
	bl FUN_0201AEE4
	b _0207BCB6
_0207BC7A:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_02019220
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	add r0, r4, #0x0
	mov r1, #0x9e
	bl FUN_0207D924
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207C6F0
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x1
	pop {r4, pc}
_0207BCB6:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207BCBC: .word 0x0000068E
_0207BCC0: .word 0x00000454
_0207BCC4: .word 0x0000042C

	thumb_func_start FUN_0207BCC8
FUN_0207BCC8: ; 0x0207BCC8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x2f
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r6, r2, #0x1
	add r4, r1, #0x0
	str r0, [sp, #0x4]
	add r7, r6, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	lsl r3, r7, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	add r2, r4, #0x0
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #0x2f
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r6, r6, #0x3
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r2, r4, #0x1
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #0x30
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r2, r4, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r2, #0x20
	str r0, [sp, #0xc]
	lsl r2, r2, #0x10
	lsl r3, r7, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	mov r0, #0x30
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	add r4, #0x21
	str r0, [sp, #0xc]
	lsl r2, r4, #0x10
	lsl r3, r6, #0x18
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_0207BD58
FUN_0207BD58: ; 0x0207BD58
	push {r4-r6, lr}
	ldr r6, _0207BD80 ; =0x0000012E
	add r5, r0, #0x0
	mov r4, #0x0
_0207BD60:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_0207BCC8
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x6
	blo _0207BD60
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	bl FUN_0201AC68
	pop {r4-r6, pc}
	.balign 4
_0207BD80: .word 0x0000012E

	thumb_func_start FUN_0207BD84
FUN_0207BD84: ; 0x0207BD84
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0207BD58
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0207BDCC
	add r0, r4, #0x0
	mov r1, #0xa
	bl FUN_0206AB18
	bl FUN_02083114
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	asr r6, r0, #0x18
	mov r4, #0x0
	cmp r6, #0x0
	ble _0207BDCC
	mov r7, #0x4b
	lsl r7, r7, #0x2
_0207BDB6:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	add r1, r7, #0x0
	lsr r2, r2, #0x18
	bl FUN_0207BCC8
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r6
	blt _0207BDB6
_0207BDCC:
	ldr r0, [r5, #0x0]
	mov r1, #0x2
	bl FUN_0201AC68
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207BDD8
FUN_0207BDD8: ; 0x0207BDD8
	push {r3, lr}
	ldr r1, _0207BDF0 ; =0x0000068C
	ldrsb r1, [r0, r1]
	cmp r1, #0x3
	bne _0207BDE8
	bl FUN_0207EC94
	pop {r3, pc}
_0207BDE8:
	bl FUN_0207EEB0
	pop {r3, pc}
	nop
_0207BDF0: .word 0x0000068C

	thumb_func_start FUN_0207BDF4
FUN_0207BDF4: ; 0x0207BDF4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0207ECDC
	add r0, r4, #0x0
	bl FUN_0207B8D8
	add r0, r4, #0x0
	bl FUN_0207D06C
	ldr r0, _0207BE5C ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	bne _0207BE46
	add r0, r4, #0x0
	bl FUN_0207D22C
	ldr r0, _0207BE60 ; =0x00000434
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r4, r0]
	add r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r1, r0
	beq _0207BE38
	ldr r0, _0207BE64 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
_0207BE38:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl FUN_0201AEE4
	pop {r4, pc}
_0207BE46:
	add r0, r4, #0x0
	bl FUN_0207D10C
	mov r2, #0x3
	add r3, r2, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	add r3, #0xfd
	bl FUN_0201AEE4
	pop {r4, pc}
	.balign 4
_0207BE5C: .word 0x0000068C
_0207BE60: .word 0x00000434
_0207BE64: .word 0x00000438

	thumb_func_start FUN_0207BE68
FUN_0207BE68: ; 0x0207BE68
	push {r4, lr}
	ldr r1, _0207BF78 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	beq _0207BE7E
	cmp r1, #0x1
	beq _0207BEEA
	cmp r1, #0x2
	beq _0207BF16
	b _0207BF74
_0207BE7E:
	mov r1, #0x2
	add r3, r1, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x0
	add r3, #0xfe
	bl FUN_0201AEE4
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl FUN_0201AEE4
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_0201958C
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x79
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0201958C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	ldr r1, _0207BF7C ; =0x00000697
	mov r2, #0x0
	strb r2, [r4, r1]
	add r0, r1, #0x1
	strb r2, [r4, r0]
	mov r0, #0x1
	sub r1, #0x9
	strb r0, [r4, r1]
	b _0207BF74
_0207BEEA:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02017B54
	cmp r0, #0x30
	ldr r0, [r4, #0x0]
	blt _0207BF0A
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x38
	bl FUN_0201AEE4
	ldr r0, _0207BF78 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207BF74
_0207BF0A:
	mov r1, #0x2
	mov r2, #0x4
	mov r3, #0x10
	bl FUN_0201AEE4
	b _0207BF74
_0207BF16:
	mov r1, #0xb5
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	ldr r0, _0207BF80 ; =0x00000514
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x52
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_020200A0
	ldr r0, _0207BF84 ; =0x00000504
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207BF88 ; =0x00000508
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207BF8C ; =0x0000050C
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x51
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207C07C
	mov r0, #0x1
	pop {r4, pc}
_0207BF74:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0207BF78: .word 0x0000068E
_0207BF7C: .word 0x00000697
_0207BF80: .word 0x00000514
_0207BF84: .word 0x00000504
_0207BF88: .word 0x00000508
_0207BF8C: .word 0x0000050C

	thumb_func_start FUN_0207BF90
FUN_0207BF90: ; 0x0207BF90
	push {r4, lr}
	ldr r1, _0207C078 ; =0x0000068E
	add r4, r0, #0x0
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	beq _0207BFA6
	cmp r0, #0x1
	beq _0207BFF6
	cmp r0, #0x2
	beq _0207C022
	b _0207C072
_0207BFA6:
	add r0, r1, #0x0
	mov r2, #0x0
	add r0, #0x9
	strb r2, [r4, r0]
	add r1, #0xa
	mov r0, #0x91
	strb r2, [r4, r1]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FUN_0201958C
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207CFAC
	add r0, r4, #0x0
	bl FUN_0207D2C8
	ldr r0, _0207C078 ; =0x0000068E
	mov r1, #0x1
	strb r1, [r4, r0]
	b _0207C072
_0207BFF6:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02017B54
	cmp r0, #0x8
	ldr r0, [r4, #0x0]
	bgt _0207C016
	mov r1, #0x2
	mov r2, #0x3
	mov r3, #0x0
	bl FUN_0201AEE4
	ldr r0, _0207C078 ; =0x0000068E
	mov r1, #0x2
	strb r1, [r4, r0]
	b _0207C072
_0207C016:
	mov r1, #0x2
	mov r2, #0x5
	mov r3, #0x10
	bl FUN_0201AEE4
	b _0207C072
_0207C022:
	add r0, r4, #0x0
	add r0, #0x64
	bl FUN_02019220
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x79
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	add r0, r4, #0x0
	mov r1, #0xb4
	bl FUN_0207D924
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207C6F0
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x1
	pop {r4, pc}
_0207C072:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207C078: .word 0x0000068E

	thumb_func_start FUN_0207C07C
FUN_0207C07C: ; 0x0207C07C
	push {r4-r6, lr}
	ldr r2, _0207C1D0 ; =0x00000697
	add r5, r0, #0x0
	add r3, r2, #0x1
	ldrb r0, [r5, r2]
	ldrb r4, [r5, r3]
	cmp r1, #0x1
	bne _0207C0A8
	mov r1, #0x3
	and r1, r0
	cmp r1, #0x3
	beq _0207C0B6
	lsl r1, r4, #0x2
	add r1, r0, r1
	add r3, r1, #0x1
	add r1, r2, #0x2
	ldrb r1, [r5, r1]
	cmp r3, r1
	bge _0207C14A
	add r1, r0, #0x1
	strb r1, [r5, r2]
	b _0207C14A
_0207C0A8:
	mov r3, #0x0
	mvn r3, r3
	cmp r1, r3
	bne _0207C0BE
	mov r1, #0x3
	tst r1, r0
	bne _0207C0B8
_0207C0B6:
	b _0207C1CE
_0207C0B8:
	sub r1, r0, #0x1
	strb r1, [r5, r2]
	b _0207C14A
_0207C0BE:
	cmp r1, #0x4
	bne _0207C12C
	cmp r0, #0x4
	bhs _0207C0F2
	add r1, r2, #0x2
	ldrb r3, [r5, r1]
	lsl r1, r4, #0x2
	add r1, r0, r1
	add r1, r1, #0x4
	cmp r1, r3
	blt _0207C0EC
	cmp r3, #0x4
	bls _0207C14A
	lsr r1, r3, #0x1f
	lsl r6, r3, #0x1e
	sub r6, r6, r1
	mov r3, #0x1e
	ror r6, r3
	add r1, r1, r6
	beq _0207C14A
	add r1, r1, #0x3
	strb r1, [r5, r2]
	b _0207C14A
_0207C0EC:
	add r1, r0, #0x4
	strb r1, [r5, r2]
	b _0207C14A
_0207C0F2:
	add r1, r2, #0x2
	ldrb r1, [r5, r1]
	lsl r3, r4, #0x2
	add r3, #0x8
	cmp r3, r1
	bge _0207C14A
	add r1, r2, #0x1
	ldrb r1, [r5, r1]
	add r6, r2, #0x1
	add r3, r1, #0x1
	add r1, r2, #0x1
	strb r3, [r5, r1]
	add r1, r2, #0x2
	ldrb r6, [r5, r6]
	ldrb r3, [r5, r1]
	ldrb r1, [r5, r2]
	lsl r6, r6, #0x2
	add r1, r1, r6
	cmp r1, r3
	blt _0207C14A
	lsr r1, r3, #0x1f
	lsl r6, r3, #0x1e
	sub r6, r6, r1
	mov r3, #0x1e
	ror r6, r3
	add r1, r1, r6
	add r1, r1, #0x3
	strb r1, [r5, r2]
	b _0207C14A
_0207C12C:
	sub r3, r3, #0x3
	cmp r1, r3
	bne _0207C14A
	cmp r0, #0x4
	blo _0207C13C
	sub r1, r0, #0x4
	strb r1, [r5, r2]
	b _0207C14A
_0207C13C:
	cmp r4, #0x0
	beq _0207C14A
	add r1, r2, #0x1
	ldrb r1, [r5, r1]
	sub r3, r1, #0x1
	add r1, r2, #0x1
	strb r3, [r5, r1]
_0207C14A:
	ldr r1, _0207C1D0 ; =0x00000697
	ldrb r2, [r5, r1]
	cmp r0, r2
	bne _0207C15A
	add r0, r1, #0x1
	ldrb r0, [r5, r0]
	cmp r4, r0
	beq _0207C160
_0207C15A:
	ldr r0, _0207C1D4 ; =0x000005DC
	bl FUN_020054C8
_0207C160:
	ldr r1, _0207C1D0 ; =0x00000697
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_0207C1E8
	ldr r1, _0207C1D8 ; =0x0000069A
	strb r0, [r5, r1]
	add r0, r5, #0x0
	bl FUN_0207D3C4
	ldr r0, _0207C1DC ; =0x00000698
	ldrb r0, [r5, r0]
	cmp r4, r0
	beq _0207C182
	add r0, r5, #0x0
	bl FUN_0207D364
_0207C182:
	add r0, r5, #0x0
	bl FUN_0207E9A0
	add r0, r5, #0x0
	bl FUN_0207E840
	ldr r0, _0207C1DC ; =0x00000698
	ldrb r0, [r5, r0]
	cmp r0, #0x0
	ldr r0, _0207C1E0 ; =0x00000518
	beq _0207C1A2
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_020200A0
	b _0207C1AA
_0207C1A2:
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
_0207C1AA:
	ldr r0, _0207C1DC ; =0x00000698
	ldrb r1, [r5, r0]
	add r0, r0, #0x1
	ldrb r0, [r5, r0]
	lsl r1, r1, #0x2
	add r1, #0x8
	cmp r1, r0
	ldr r0, _0207C1E4 ; =0x0000051C
	bge _0207C1C6
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_020200A0
	pop {r4-r6, pc}
_0207C1C6:
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
_0207C1CE:
	pop {r4-r6, pc}
	.balign 4
_0207C1D0: .word 0x00000697
_0207C1D4: .word 0x000005DC
_0207C1D8: .word 0x0000069A
_0207C1DC: .word 0x00000698
_0207C1E0: .word 0x00000518
_0207C1E4: .word 0x0000051C

	thumb_func_start FUN_0207C1E8
FUN_0207C1E8: ; 0x0207C1E8
	push {r4-r7}
	ldr r2, _0207C238 ; =0x00000698
	mov r6, #0x0
	ldrb r2, [r0, r2]
	add r4, r6, #0x0
	lsl r2, r2, #0x2
	add r1, r1, r2
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	mov r1, #0xa9
	mov r2, #0x1
	lsl r1, r1, #0x2
_0207C200:
	mov r3, #0x1f
	add r7, r4, #0x0
	and r7, r3
	add r3, r2, #0x0
	lsl r3, r7
	lsr r7, r4, #0x5
	lsl r7, r7, #0x2
	add r7, r0, r7
	ldr r7, [r7, r1]
	tst r3, r7
	beq _0207C228
	cmp r5, r6
	bne _0207C222
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	pop {r4-r7}
	bx lr
_0207C222:
	add r3, r6, #0x1
	lsl r3, r3, #0x18
	lsr r6, r3, #0x18
_0207C228:
	add r3, r4, #0x1
	lsl r3, r3, #0x10
	lsr r4, r3, #0x10
	cmp r4, #0x50
	blo _0207C200
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	.balign 4
_0207C238: .word 0x00000698

	thumb_func_start FUN_0207C23C
FUN_0207C23C: ; 0x0207C23C
	push {r4, lr}
	sub sp, #0x8
	ldr r1, _0207C29C ; =0x0000029A
	add r4, r0, #0x0
	ldrb r0, [r4, r1]
	cmp r0, #0xff
	bne _0207C28E
	mov r0, #0x0
	sub r1, #0xda
	mov r2, #0x13
	bl FUN_02002EEC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x4]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x13
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	ldr r2, _0207C2A0 ; =0x000003E2
	mov r1, #0x1
	mov r3, #0xd
	bl FUN_0200CD68
	add r0, r4, #0x0
	mov r1, #0xff
	bl FUN_0207EECC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	strb r1, [r0, #0x17]
	add sp, #0x8
	mov r0, #0x11
	pop {r4, pc}
_0207C28E:
	sub r1, #0x4e
	ldr r0, [r4, r1]
	mov r2, #0x0
	strb r2, [r0, #0x17]
	mov r0, #0x12
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0207C29C: .word 0x0000029A
_0207C2A0: .word 0x000003E2

	thumb_func_start FUN_0207C2A4
FUN_0207C2A4: ; 0x0207C2A4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202398C
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_020239BC
	str r0, [r5, #0xc]
	add r0, r4, #0x0
	bl FUN_020239CC
	strb r0, [r5, #0x10]
	pop {r3-r5, pc}

	thumb_func_start FUN_0207C2C4
FUN_0207C2C4: ; 0x0207C2C4
	mov r0, #0x40
	bx lr

	thumb_func_start FUN_0207C2C8
FUN_0207C2C8: ; 0x0207C2C8
	mov r0, #0x41
	bx lr

	thumb_func_start FUN_0207C2CC
FUN_0207C2CC: ; 0x0207C2CC
	mov r0, #0x3f
	bx lr

	thumb_func_start FUN_0207C2D0
FUN_0207C2D0: ; 0x0207C2D0
	mov r0, #0x3e
	bx lr

	thumb_func_start FUN_0207C2D4
FUN_0207C2D4: ; 0x0207C2D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x9f
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _0207C2F4
	mov r0, #0x6
	pop {r3-r5, pc}
_0207C2F4:
	mov r0, #0x88
	tst r0, r4
	beq _0207C2FE
	mov r0, #0x4
	pop {r3-r5, pc}
_0207C2FE:
	mov r0, #0x7
	add r1, r4, #0x0
	tst r1, r0
	beq _0207C30A
	mov r0, #0x3
	pop {r3-r5, pc}
_0207C30A:
	mov r1, #0x10
	tst r1, r4
	beq _0207C314
	mov r0, #0x5
	pop {r3-r5, pc}
_0207C314:
	mov r1, #0x20
	tst r1, r4
	beq _0207C31E
	mov r0, #0x2
	pop {r3-r5, pc}
_0207C31E:
	mov r1, #0x40
	tst r1, r4
	beq _0207C326
	mov r0, #0x1
_0207C326:
	pop {r3-r5, pc}

	thumb_func_start FUN_0207C328
FUN_0207C328: ; 0x0207C328
	push {r3-r7, lr}
	sub sp, #0x50
	add r4, r0, #0x0
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E74C
	mov r0, #0x20
	mov r1, #0x13
	bl FUN_0201C24C
	mov r0, #0x13
	bl FUN_0200BB14
	mov r1, #0x1
	lsl r1, r1, #0xa
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl FUN_0200BB34
	ldr r7, _0207C3C4 ; =0x00000404
	add r2, sp, #0x30
	ldr r3, _0207C3C8 ; =0x020FA73C
	str r0, [r4, r7]
	ldmia r3!, {r0-r1}
	add r6, r2, #0x0
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	ldr r5, _0207C3CC ; =0x020FA70C
	stmia r2!, {r0-r1}
	add r3, sp, #0x1c
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [r3, #0x0]
	sub r0, r7, #0x4
	ldr r0, [r4, r0]
	mov r3, #0x20
	bl FUN_0200BB6C
	sub r1, r7, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	mov r2, #0x4d
	bl FUN_0200BBF0
	ldr r5, _0207C3D0 ; =0x020FA720
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	sub r1, r7, #0x4
	str r0, [r3, #0x0]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	bl FUN_0200BD20
	add sp, #0x50
	pop {r3-r7, pc}
	.balign 4
_0207C3C4: .word 0x00000404
_0207C3C8: .word 0x020FA73C
_0207C3CC: .word 0x020FA70C
_0207C3D0: .word 0x020FA720

	thumb_func_start FUN_0207C3D4
FUN_0207C3D4: ; 0x0207C3D4
	push {r4, lr}
	mov r1, #0x1
	add r4, r0, #0x0
	lsl r1, r1, #0xa
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	bl FUN_0200BCE0
	mov r0, #0x1
	lsl r0, r0, #0xa
	ldr r0, [r4, r0]
	bl FUN_0200BD04
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207C3F4
FUN_0207C3F4: ; 0x0207C3F4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207C438 ; =0x0000045C
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	mov r0, #0x46
	lsl r0, r0, #0x4
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, _0207C43C ; =0x000004AC
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, _0207C440 ; =0x00000518
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, _0207C444 ; =0x0000051C
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	pop {r4, pc}
	.balign 4
_0207C438: .word 0x0000045C
_0207C43C: .word 0x000004AC
_0207C440: .word 0x00000518
_0207C444: .word 0x0000051C

	thumb_func_start FUN_0207C448
FUN_0207C448: ; 0x0207C448
	push {r3-r7, lr}
	ldr r6, _0207C550 ; =0x020FA784
	ldr r7, _0207C554 ; =0x00000408
	add r5, r0, #0x0
	mov r4, #0x0
_0207C452:
	mov r0, #0x1
	ldr r1, _0207C558 ; =0x00000404
	lsl r0, r0, #0xa
	mov r2, #0x28
	mul r2, r4
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, r2
	bl FUN_0200BE38
	lsl r1, r4, #0x2
	add r1, r5, r1
	str r0, [r1, r7]
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x4d
	blo _0207C452
	add r0, r5, #0x0
	bl FUN_0207C7EC
	ldr r0, _0207C55C ; =0x0000042C
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0x43
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207C560 ; =0x000004AC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0x4b
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207C564 ; =0x000004B4
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C568 ; =0x000004B8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C56C ; =0x000004BC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0x13
	lsl r0, r0, #0x6
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207C570 ; =0x000004C4
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C574 ; =0x000004C8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C578 ; =0x000004CC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0x4d
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207C57C ; =0x000004D4
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C580 ; =0x000004D8
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C584 ; =0x00000524
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C588 ; =0x00000528
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C58C ; =0x0000052C
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0x53
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207C590 ; =0x00000534
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207C594 ; =0x00000538
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	pop {r3-r7, pc}
	.balign 4
_0207C550: .word 0x020FA784
_0207C554: .word 0x00000408
_0207C558: .word 0x00000404
_0207C55C: .word 0x0000042C
_0207C560: .word 0x000004AC
_0207C564: .word 0x000004B4
_0207C568: .word 0x000004B8
_0207C56C: .word 0x000004BC
_0207C570: .word 0x000004C4
_0207C574: .word 0x000004C8
_0207C578: .word 0x000004CC
_0207C57C: .word 0x000004D4
_0207C580: .word 0x000004D8
_0207C584: .word 0x00000524
_0207C588: .word 0x00000528
_0207C58C: .word 0x0000052C
_0207C590: .word 0x00000534
_0207C594: .word 0x00000538

	thumb_func_start FUN_0207C598
FUN_0207C598: ; 0x0207C598
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_0207C5A0:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0207B070
	cmp r0, #0x0
	beq _0207C5B2
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0207C5B2:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x8
	blo _0207C5A0
	sub r0, r5, #0x1
	lsl r1, r0, #0x4
	add r1, #0x18
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #0x1
	mov r0, #0xbc
	sub r0, r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0207C5D4
FUN_0207C5D4: ; 0x0207C5D4
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	bl FUN_0207C598
	str r0, [sp, #0x4]
	ldr r0, _0207C69C ; =0x00000408
	mov r5, #0x0
	add r4, r7, r0
	ldr r0, [sp, #0x4]
	str r5, [sp, #0x8]
	str r0, [sp, #0x0]
	add r0, #0x18
	str r0, [sp, #0x0]
_0207C5F0:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_0207B070
	cmp r0, #0x0
	bne _0207C608
	lsl r0, r5, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	b _0207C68E
_0207C608:
	lsl r6, r5, #0x2
	ldr r0, [r4, r6]
	bl FUN_020201DC
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _0207C6A0 ; =0x0000068C
	ldrsb r0, [r7, r0]
	cmp r0, r5
	bne _0207C62A
	cmp r1, #0x8
	bhs _0207C636
	ldr r0, [r4, r6]
	add r1, #0x8
	bl FUN_02020130
	b _0207C636
_0207C62A:
	cmp r1, #0x8
	blo _0207C636
	ldr r0, [r4, r6]
	sub r1, #0x8
	bl FUN_02020130
_0207C636:
	add r1, sp, #0xc
	ldr r0, [r4, r6]
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C75C
	ldr r0, _0207C6A0 ; =0x0000068C
	ldrsb r0, [r7, r0]
	cmp r0, r5
	blt _0207C652
	ldr r0, [sp, #0x8]
	lsl r1, r0, #0x4
	ldr r0, [sp, #0x4]
	b _0207C65A
_0207C652:
	ldr r0, [sp, #0x8]
	sub r0, r0, #0x1
	lsl r1, r0, #0x4
	ldr r0, [sp, #0x0]
_0207C65A:
	add r0, r0, r1
	lsl r0, r0, #0x10
	asr r1, r0, #0x10
	add r0, sp, #0xc
	strh r1, [r0, #0x2]
	lsl r0, r5, #0x2
	add r1, r7, r0
	ldr r0, _0207C69C ; =0x00000408
	add r2, sp, #0xc
	ldr r0, [r1, r0]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	add r3, r2, #0x0
	mov r2, #0x0
	ldrsh r2, [r3, r2]
	bl FUN_0200C6E4
	ldr r0, [r4, r6]
	mov r1, #0x1
	bl FUN_020200A0
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
_0207C68E:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0207C5F0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0207C69C: .word 0x00000408
_0207C6A0: .word 0x0000068C

	thumb_func_start FUN_0207C6A4
FUN_0207C6A4: ; 0x0207C6A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0207B09C
	cmp r0, #0x1
	bhi _0207C6B8
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0207C6F0
_0207C6B8:
	add r0, r5, #0x0
	bl FUN_0207C598
	add r4, r0, #0x0
	ldr r0, _0207C6EC ; =0x0000045C
	add r1, r4, #0x0
	sub r1, #0xc
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	mov r2, #0x18
	bl FUN_0200C6E4
	mov r1, #0x5d
	mov r0, #0x46
	lsl r1, r1, #0x2
	lsl r0, r0, #0x4
	sub r1, r1, r4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	asr r1, r1, #0x10
	mov r2, #0x18
	bl FUN_0200C6E4
	pop {r3-r5, pc}
	nop
_0207C6EC: .word 0x0000045C

	thumb_func_start FUN_0207C6F0
FUN_0207C6F0: ; 0x0207C6F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0207B09C
	cmp r0, #0x1
	bhi _0207C700
	mov r4, #0x0
_0207C700:
	ldr r0, _0207C718 ; =0x0000045C
	add r1, r4, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	mov r0, #0x46
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	add r1, r4, #0x0
	bl FUN_020200A0
	pop {r3-r5, pc}
	.balign 4
_0207C718: .word 0x0000045C

	thumb_func_start FUN_0207C71C
FUN_0207C71C: ; 0x0207C71C
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r0, _0207C774 ; =0x00000263
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r3, r0, #0x1a
	bne _0207C730
	mov r3, #0x15
	b _0207C732
_0207C730:
	add r3, #0x14
_0207C732:
	mov r0, #0x0
	mov r1, #0x1
	str r0, [sp, #0x0]
	lsl r1, r1, #0xa
	str r0, [sp, #0x4]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	mov r2, #0x27
	bl FUN_0200C9D8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	mov r1, #0x1
	ldr r3, _0207C774 ; =0x00000263
	str r0, [sp, #0x4]
	ldrb r3, [r4, r3]
	lsl r1, r1, #0xa
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	lsl r3, r3, #0x18
	ldr r1, [r4, r1]
	lsr r4, r3, #0x1a
	ldr r3, _0207C778 ; =0x020FA6F8
	mov r2, #0x27
	ldrb r3, [r3, r4]
	add r3, #0x25
	bl FUN_0200CA0C
	add sp, #0x8
	pop {r4, pc}
	nop
_0207C774: .word 0x00000263
_0207C778: .word 0x020FA6F8

	thumb_func_start FUN_0207C77C
FUN_0207C77C: ; 0x0207C77C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	lsl r0, r0, #0x4
	lsr r0, r0, #0x4
	cmp r0, #0x7
	bne _0207C7A4
	ldr r0, _0207C7E4 ; =0x00000458
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207C7E8 ; =0x00000538
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
_0207C7A4:
	cmp r0, #0x0
	ldr r0, _0207C7E8 ; =0x00000538
	beq _0207C7D0
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207C7E4 ; =0x00000458
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r1, #0x2a
	lsl r1, r1, #0x4
	ldr r0, _0207C7E4 ; =0x00000458
	ldr r1, [r4, r1]
	ldr r0, [r4, r0]
	lsl r1, r1, #0x4
	lsr r1, r1, #0x4
	bl FUN_02020130
	pop {r4, pc}
_0207C7D0:
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_020200A0
	ldr r0, _0207C7E4 ; =0x00000458
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
	.balign 4
_0207C7E4: .word 0x00000458
_0207C7E8: .word 0x00000538

	thumb_func_start FUN_0207C7EC
FUN_0207C7EC: ; 0x0207C7EC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_0207CA44
	mov r6, #0xa1
	mov r4, #0x0
	mov r7, #0x3
	lsl r6, r6, #0x2
_0207C7FC:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, r6]
	cmp r0, #0x0
	beq _0207C826
	add r1, r7, #0x0
	bl FUN_0206AB18
	add r3, r0, #0x0
	add r1, r4, #0x0
	add r1, #0xd
	add r2, r4, #0x5
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0207CA6C
_0207C826:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x4
	blo _0207C7FC
	add r0, r5, #0x0
	bl FUN_0207CFEC
	pop {r3-r7, pc}

	thumb_func_start FUN_0207C838
FUN_0207C838: ; 0x0207C838
	push {r3-r7, lr}
	ldr r6, _0207CA2C ; =0x00000408
	add r5, r0, #0x0
	mov r4, #0xb
	mov r7, #0x0
_0207C842:
	lsl r0, r4, #0x2
	add r0, r5, r0
	ldr r0, [r0, r6]
	add r1, r7, #0x0
	bl FUN_0200C63C
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x13
	bls _0207C842
	ldr r0, _0207CA30 ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x0
	beq _0207C86C
	cmp r0, #0x3
	beq _0207C8B4
	cmp r0, #0x5
	bne _0207C86A
	b _0207C96E
_0207C86A:
	pop {r3-r7, pc}
_0207C86C:
	ldr r0, _0207CA34 ; =0x00000434
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_0200C63C
	mov r0, #0x26
	lsl r0, r0, #0x4
	ldrb r1, [r5, r0]
	add r0, r0, #0x1
	ldrb r0, [r5, r0]
	cmp r1, r0
	ldr r0, _0207CA34 ; =0x00000434
	bne _0207C892
	ldr r0, [r5, r0]
	mov r1, #0xd8
	mov r2, #0x50
	bl FUN_0200C6E4
	pop {r3-r7, pc}
_0207C892:
	ldr r0, [r5, r0]
	mov r1, #0xc7
	mov r2, #0x50
	bl FUN_0200C6E4
	ldr r0, _0207CA38 ; =0x00000438
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_0200C63C
	ldr r0, _0207CA38 ; =0x00000438
	mov r1, #0xe9
	ldr r0, [r5, r0]
	mov r2, #0x50
	bl FUN_0200C6E4
	pop {r3-r7, pc}
_0207C8B4:
	mov r7, #0xa1
	mov r4, #0x0
	lsl r7, r7, #0x2
_0207C8BA:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, r7]
	cmp r0, #0x0
	beq _0207C904
	mov r1, #0x3
	bl FUN_0206AB18
	add r3, r0, #0x0
	add r1, r4, #0x0
	add r1, #0xd
	add r2, r4, #0x5
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0207CA6C
	lsl r0, r4, #0x2
	add r6, r5, r0
	ldr r0, _0207CA3C ; =0x0000043C
	mov r1, #0x1
	ldr r0, [r6, r0]
	bl FUN_0200C63C
	ldr r0, _0207CA3C ; =0x0000043C
	lsl r2, r4, #0x5
	add r2, #0x2a
	lsl r2, r2, #0x10
	ldr r0, [r6, r0]
	mov r1, #0x97
	asr r2, r2, #0x10
	bl FUN_0200C6E4
_0207C904:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x4
	blo _0207C8BA
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0207C946
	mov r1, #0x3
	bl FUN_0206AB18
	add r3, r0, #0x0
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x9
	lsr r3, r3, #0x18
	bl FUN_0207CA6C
	ldr r0, _0207CA40 ; =0x0000044C
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_0200C63C
	ldr r0, _0207CA40 ; =0x0000044C
	mov r1, #0x97
	ldr r0, [r5, r0]
	mov r2, #0xaa
	bl FUN_0200C6E4
_0207C946:
	ldr r0, _0207CA34 ; =0x00000434
	mov r1, #0x3f
	ldr r0, [r5, r0]
	mov r2, #0x34
	bl FUN_0200C6E4
	ldr r0, _0207CA38 ; =0x00000438
	mov r1, #0x61
	ldr r0, [r5, r0]
	mov r2, #0x34
	bl FUN_0200C6E4
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x6c
	mov r2, #0x48
	bl FUN_0200C6E4
	pop {r3-r7, pc}
_0207C96E:
	mov r7, #0xa1
	mov r4, #0x0
	lsl r7, r7, #0x2
_0207C974:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, r7]
	cmp r0, #0x0
	beq _0207C9C0
	mov r1, #0xb
	bl FUN_0206AB18
	add r3, r0, #0x0
	add r1, r4, #0x0
	add r1, #0xd
	add r2, r4, #0x5
	add r3, #0x12
	lsl r1, r1, #0x18
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0207CA6C
	lsl r0, r4, #0x2
	add r6, r5, r0
	ldr r0, _0207CA3C ; =0x0000043C
	mov r1, #0x1
	ldr r0, [r6, r0]
	bl FUN_0200C63C
	ldr r0, _0207CA3C ; =0x0000043C
	lsl r2, r4, #0x5
	add r2, #0x2a
	lsl r2, r2, #0x10
	ldr r0, [r6, r0]
	mov r1, #0x97
	asr r2, r2, #0x10
	bl FUN_0200C6E4
_0207C9C0:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x4
	blo _0207C974
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldrh r0, [r0, #0x18]
	cmp r0, #0x0
	beq _0207CA04
	mov r1, #0xb
	bl FUN_0206AB18
	add r3, r0, #0x0
	add r3, #0x12
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x9
	lsr r3, r3, #0x18
	bl FUN_0207CA6C
	ldr r0, _0207CA40 ; =0x0000044C
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_0200C63C
	ldr r0, _0207CA40 ; =0x0000044C
	mov r1, #0x97
	ldr r0, [r5, r0]
	mov r2, #0xaa
	bl FUN_0200C6E4
_0207CA04:
	ldr r0, _0207CA34 ; =0x00000434
	mov r1, #0x3f
	ldr r0, [r5, r0]
	mov r2, #0x34
	bl FUN_0200C6E4
	ldr r0, _0207CA38 ; =0x00000438
	mov r1, #0x61
	ldr r0, [r5, r0]
	mov r2, #0x34
	bl FUN_0200C6E4
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x6c
	mov r2, #0x48
	bl FUN_0200C6E4
	pop {r3-r7, pc}
	.balign 4
_0207CA2C: .word 0x00000408
_0207CA30: .word 0x0000068C
_0207CA34: .word 0x00000434
_0207CA38: .word 0x00000438
_0207CA3C: .word 0x0000043C
_0207CA40: .word 0x0000044C

	thumb_func_start FUN_0207CA44
FUN_0207CA44: ; 0x0207CA44
	push {r4, lr}
	mov r3, #0x26
	add r4, r0, #0x0
	lsl r3, r3, #0x4
	ldrb r3, [r4, r3]
	mov r1, #0xb
	mov r2, #0x3
	bl FUN_0207CA6C
	ldr r3, _0207CA68 ; =0x00000261
	add r0, r4, #0x0
	ldrb r3, [r4, r3]
	mov r1, #0xc
	mov r2, #0x4
	bl FUN_0207CA6C
	pop {r4, pc}
	nop
_0207CA68: .word 0x00000261

	thumb_func_start FUN_0207CA6C
FUN_0207CA6C: ; 0x0207CA6C
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0206E12C
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	bl FUN_0206E0F0
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r1, _0207CAB4 ; =0x00000404
	str r6, [sp, #0x4]
	lsl r0, r0, #0xa
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, [sp, #0x8]
	bl FUN_0200C9D8
	add r0, r7, #0x0
	bl FUN_0206E114
	add r2, r0, #0x0
	lsl r0, r4, #0x2
	add r1, r5, r0
	ldr r0, _0207CAB8 ; =0x00000408
	ldr r0, [r1, r0]
	add r1, r2, #0x3
	bl FUN_0200C664
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0207CAB4: .word 0x00000404
_0207CAB8: .word 0x00000408

	thumb_func_start FUN_0207CABC
FUN_0207CABC: ; 0x0207CABC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	ldrb r0, [r0, #0x0]
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	lsl r0, r0, #0x5
	add r0, #0x2a
	lsl r0, r0, #0x10
	add r4, r3, #0x0
	asr r7, r0, #0x10
	mov r6, #0x0
_0207CAD6:
	ldr r0, _0207CB04 ; =0x0000043C
	ldr r1, [sp, #0x4]
	ldr r0, [r5, r0]
	add r2, r4, #0x0
	bl FUN_0200C75C
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	cmp r7, r0
	bne _0207CAF2
	ldr r0, [sp, #0x0]
	add sp, #0x8
	strb r6, [r0, #0x0]
	pop {r3-r7, pc}
_0207CAF2:
	add r0, r6, #0x1
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	add r5, r5, #0x4
	cmp r6, #0x4
	blt _0207CAD6
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0207CB04: .word 0x0000043C

	thumb_func_start FUN_0207CB08
FUN_0207CB08: ; 0x0207CB08
	push {r0-r3}
	push {r4, lr}
	sub sp, #0x8
	add r2, sp, #0x4
	add r1, sp, #0x14
	add r2, #0x2
	add r3, sp, #0x4
	add r4, r0, #0x0
	bl FUN_0207CABC
	add r2, sp, #0x0
	add r0, r4, #0x0
	add r1, sp, #0x18
	add r2, #0x2
	add r3, sp, #0x0
	bl FUN_0207CABC
	add r0, sp, #0x10
	ldrb r0, [r0, #0x4]
	add r3, sp, #0x0
	mov r2, #0x0
	add r0, #0xd
	lsl r0, r0, #0x2
	add r1, r4, r0
	ldr r0, _0207CB6C ; =0x00000408
	ldrsh r2, [r3, r2]
	ldr r0, [r1, r0]
	mov r1, #0x2
	ldrsh r1, [r3, r1]
	bl FUN_0200C6E4
	add r0, sp, #0x10
	ldrb r0, [r0, #0x8]
	add r3, sp, #0x0
	mov r2, #0x4
	add r0, #0xd
	lsl r0, r0, #0x2
	add r1, r4, r0
	ldr r0, _0207CB6C ; =0x00000408
	ldrsh r2, [r3, r2]
	ldr r0, [r1, r0]
	mov r1, #0x6
	ldrsh r1, [r3, r1]
	bl FUN_0200C6E4
	add sp, #0x8
	pop {r4}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4
_0207CB6C: .word 0x00000408

	thumb_func_start FUN_0207CB70
FUN_0207CB70: ; 0x0207CB70
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x1
	bl FUN_0206AB18
	add r4, r0, #0x0
	bl FUN_0206E2A8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0206E278
	mov r1, #0x1
	add r3, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xa
	str r0, [sp, #0x4]
	lsl r0, r1, #0xa
	ldr r1, _0207CBBC ; =0x00000404
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	add r2, r6, #0x0
	bl FUN_0200C9D8
	add r0, r4, #0x0
	bl FUN_0206E290
	add r1, r0, #0x0
	mov r0, #0x45
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	add r1, r1, #0x3
	bl FUN_0200C664
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0207CBBC: .word 0x00000404

	thumb_func_start FUN_0207CBC0
FUN_0207CBC0: ; 0x0207CBC0
	ldr r2, _0207CBDC ; =0x0000068D
	add r3, r0, #0x0
	ldrb r2, [r3, r2]
	ldr r0, _0207CBE0 ; =0x0000042C
	mov r1, #0xc2
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	lsl r2, r2, #0x5
	ldr r0, [r3, r0]
	add r2, #0x30
	lsl r2, r2, #0x10
	ldr r3, _0207CBE4 ; =FUN_0200C6E4
	asr r2, r2, #0x10
	bx r3
	.balign 4
_0207CBDC: .word 0x0000068D
_0207CBE0: .word 0x0000042C
_0207CBE4: .word FUN_0200C6E4

	thumb_func_start FUN_0207CBE8
FUN_0207CBE8: ; 0x0207CBE8
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, _0207CC20 ; =0x0000042C
	add r1, sp, #0x0
	ldr r0, [r4, r0]
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_0200C75C
	mov r0, #0x43
	lsl r0, r0, #0x4
	add r3, sp, #0x0
	mov r1, #0x2
	mov r2, #0x0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	mov r0, #0x43
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_020200A0
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0207CC20: .word 0x0000042C

	thumb_func_start FUN_0207CC24
FUN_0207CC24: ; 0x0207CC24
	push {r3-r7, lr}
	mov r2, #0x69
	lsl r2, r2, #0x4
	mov r1, #0x0
	strb r1, [r0, r2]
	add r3, r2, #0x3
	strb r1, [r0, r3]
	add r3, r2, #0x2
	strb r1, [r0, r3]
	ldr r3, _0207CC80 ; =0x0000029A
	ldrb r3, [r0, r3]
	cmp r3, #0x0
	bne _0207CC44
	add r2, r2, #0x1
	strb r1, [r0, r2]
	b _0207CC5A
_0207CC44:
	cmp r3, #0xff
	bne _0207CC50
	mov r3, #0xc
	add r1, r2, #0x1
	strb r3, [r0, r1]
	b _0207CC5A
_0207CC50:
	mov r1, #0xc
	mul r1, r3
	asr r3, r1, #0x8
	add r1, r2, #0x1
	strb r3, [r0, r1]
_0207CC5A:
	ldr r7, _0207CC84 ; =0x00000408
	add r5, r0, #0x0
	mov r4, #0x1d
	add r5, #0x74
	add r6, r7, #0x0
_0207CC64:
	ldr r0, [r5, r7]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, [r5, r6]
	mov r1, #0x0
	bl FUN_02020208
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x28
	bls _0207CC64
	pop {r3-r7, pc}
	nop
_0207CC80: .word 0x0000029A
_0207CC84: .word 0x00000408

	thumb_func_start FUN_0207CC88
FUN_0207CC88: ; 0x0207CC88
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r0, _0207CE38 ; =0x0000068C
	ldrsb r1, [r4, r0]
	cmp r1, #0x4
	bne _0207CC9C
	add r1, r0, #0x5
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	bne _0207CC9E
_0207CC9C:
	b _0207CE34
_0207CC9E:
	add r2, r0, #0x4
	ldrb r2, [r4, r2]
	cmp r2, #0x4
	bhi _0207CCCC
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0207CCB2: ; jump table (using 16-bit offset)
	.short _0207CCBC - _0207CCB2 - 2; case 0
	.short _0207CCE0 - _0207CCB2 - 2; case 1
	.short _0207CD50 - _0207CCB2 - 2; case 2
	.short _0207CD70 - _0207CCB2 - 2; case 3
	.short _0207CDCA - _0207CCB2 - 2; case 4
_0207CCBC:
	add r1, r0, #0x7
	ldrb r1, [r4, r1]
	add r2, r1, #0x1
	add r1, r0, #0x7
	strb r2, [r4, r1]
	ldrb r1, [r4, r1]
	cmp r1, #0x8
	beq _0207CCCE
_0207CCCC:
	b _0207CDE8
_0207CCCE:
	mov r2, #0x1
	add r1, r0, #0x4
	strb r2, [r4, r1]
	add r1, r0, #0x7
	mov r2, #0x0
	strb r2, [r4, r1]
	add r0, r0, #0x6
	strb r2, [r4, r0]
	b _0207CDE8
_0207CCE0:
	add r1, r0, #0x7
	ldrb r1, [r4, r1]
	cmp r1, #0x0
	bne _0207CD3E
	add r0, r0, #0x6
	ldrb r0, [r4, r0]
	add r0, #0x1d
	lsl r0, r0, #0x2
	add r1, r4, r0
	ldr r0, _0207CE3C ; =0x00000408
	ldr r0, [r1, r0]
	mov r1, #0x1
	bl FUN_020200A0
	ldr r0, _0207CE40 ; =0x00000692
	ldrb r0, [r4, r0]
	add r0, #0x1d
	lsl r0, r0, #0x2
	add r1, r4, r0
	ldr r0, _0207CE3C ; =0x00000408
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl FUN_02020208
	ldr r0, _0207CE40 ; =0x00000692
	ldrb r0, [r4, r0]
	add r0, #0x1d
	lsl r0, r0, #0x2
	add r1, r4, r0
	ldr r0, _0207CE3C ; =0x00000408
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl FUN_02020130
	ldr r0, _0207CE40 ; =0x00000692
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	sub r1, r0, #0x1
	ldrb r2, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r2, r1
	bne _0207CD3E
	mov r1, #0x2
	sub r0, r0, #0x2
	strb r1, [r4, r0]
	b _0207CDE8
_0207CD3E:
	ldr r0, _0207CE44 ; =0x00000693
	mov r1, #0xa
	ldrb r0, [r4, r0]
	add r0, r0, #0x1
	bl _s32_div_f
	ldr r0, _0207CE44 ; =0x00000693
	strb r1, [r4, r0]
	b _0207CDE8
_0207CD50:
	add r1, #0x1c
	lsl r0, r1, #0x2
	add r1, r4, r0
	ldr r0, _0207CE3C ; =0x00000408
	ldr r0, [r1, r0]
	bl FUN_02020128
	cmp r0, #0x0
	bne _0207CDE8
	ldr r0, _0207CE44 ; =0x00000693
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r1, #0x3
	sub r0, r0, #0x3
	strb r1, [r4, r0]
	b _0207CDE8
_0207CD70:
	add r1, r0, #0x7
	ldrb r1, [r4, r1]
	add r2, r1, #0x1
	add r1, r0, #0x7
	strb r2, [r4, r1]
	ldrb r1, [r4, r1]
	cmp r1, #0x20
	bne _0207CDE8
	add r0, r0, #0x5
	ldrb r0, [r4, r0]
	mov r6, #0x1d
	add r0, #0x1d
	cmp r0, #0x1d
	bls _0207CDBC
	add r5, r4, #0x0
	ldr r7, _0207CE48 ; =0x00000691
	add r5, #0x74
_0207CD92:
	ldr r0, _0207CE3C ; =0x00000408
	mov r1, #0x1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _0207CE3C ; =0x00000408
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02020208
	ldr r0, _0207CE3C ; =0x00000408
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldrb r0, [r4, r7]
	add r6, r6, #0x1
	add r5, r5, #0x4
	add r0, #0x1d
	cmp r6, r0
	blo _0207CD92
_0207CDBC:
	ldr r0, _0207CE44 ; =0x00000693
	mov r1, #0x0
	strb r1, [r4, r0]
	mov r1, #0x4
	sub r0, r0, #0x3
	strb r1, [r4, r0]
	b _0207CDE8
_0207CDCA:
	add r1, r0, #0x7
	ldrb r1, [r4, r1]
	add r2, r1, #0x1
	add r1, r0, #0x7
	strb r2, [r4, r1]
	ldrb r1, [r4, r1]
	cmp r1, #0x20
	bne _0207CDE8
	mov r2, #0x0
	add r1, r0, #0x4
	strb r2, [r4, r1]
	add r1, r0, #0x7
	strb r2, [r4, r1]
	add r0, r0, #0x6
	strb r2, [r4, r0]
_0207CDE8:
	ldr r0, _0207CE48 ; =0x00000691
	mov r6, #0x1d
	ldrb r0, [r4, r0]
	add r0, #0x1d
	cmp r0, #0x1d
	bls _0207CE34
	add r5, r4, #0x0
	ldr r7, _0207CE3C ; =0x00000408
	add r5, #0x74
_0207CDFA:
	ldr r0, [r5, r7]
	bl FUN_02020128
	cmp r0, #0x0
	beq _0207CE26
	ldr r0, _0207CE3C ; =0x00000408
	mov r1, #0x1
	ldr r0, [r5, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	ldr r0, _0207CE3C ; =0x00000408
	ldr r0, [r5, r0]
	bl FUN_0202022C
	cmp r0, #0x6
	bne _0207CE26
	ldr r0, _0207CE3C ; =0x00000408
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_020200A0
_0207CE26:
	ldr r0, _0207CE48 ; =0x00000691
	add r6, r6, #0x1
	ldrb r0, [r4, r0]
	add r5, r5, #0x4
	add r0, #0x1d
	cmp r6, r0
	blo _0207CDFA
_0207CE34:
	pop {r3-r7, pc}
	nop
_0207CE38: .word 0x0000068C
_0207CE3C: .word 0x00000408
_0207CE40: .word 0x00000692
_0207CE44: .word 0x00000693
_0207CE48: .word 0x00000691

	thumb_func_start FUN_0207CE4C
FUN_0207CE4C: ; 0x0207CE4C
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
	mov r7, #0x1
_0207CE56:
	mov r0, #0xa7
	lsl r0, r0, #0x2
	ldrh r1, [r6, r0]
	add r0, r7, #0x0
	lsl r0, r4
	tst r0, r1
	ldr r0, _0207CED4 ; =0x00000464
	beq _0207CE70
	ldr r0, [r5, r0]
	add r1, r7, #0x0
	bl FUN_02020130
	b _0207CE78
_0207CE70:
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_02020130
_0207CE78:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x6
	blo _0207CE56
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r6, r0]
	lsl r1, r0, #0x2
	lsr r1, r1, #0x1f
	cmp r1, #0x1
	bne _0207CEA0
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	bne _0207CEA0
	ldr r0, _0207CED8 ; =0x000004DC
	mov r1, #0x1
	ldr r0, [r6, r0]
	bl FUN_0200C63C
	b _0207CEAA
_0207CEA0:
	ldr r0, _0207CED8 ; =0x000004DC
	mov r1, #0x0
	ldr r0, [r6, r0]
	bl FUN_0200C63C
_0207CEAA:
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r6, r0]
	lsr r0, r0, #0x1e
	cmp r0, #0x2
	bne _0207CEC4
	mov r0, #0x4e
	lsl r0, r0, #0x4
	ldr r0, [r6, r0]
	mov r1, #0x1
	bl FUN_0200C63C
	pop {r3-r7, pc}
_0207CEC4:
	mov r0, #0x4e
	lsl r0, r0, #0x4
	ldr r0, [r6, r0]
	mov r1, #0x0
	bl FUN_0200C63C
	pop {r3-r7, pc}
	nop
_0207CED4: .word 0x00000464
_0207CED8: .word 0x000004DC

	thumb_func_start FUN_0207CEDC
FUN_0207CEDC: ; 0x0207CEDC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, _0207CF50 ; =0x000004AC
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207CF50 ; =0x000004AC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_02020208
	ldr r0, _0207CF50 ; =0x000004AC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_02020130
	add r1, sp, #0x0
	add r0, r4, #0x0
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_0207FC04
	ldr r0, _0207CF54 ; =0x0000068F
	add r3, sp, #0x0
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	ldr r0, _0207CF50 ; =0x000004AC
	bne _0207CF32
	mov r2, #0x0
	ldrsh r2, [r3, r2]
	mov r1, #0x2
	ldrsh r1, [r3, r1]
	add r2, #0xc0
	lsl r2, r2, #0x10
	ldr r0, [r4, r0]
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	add sp, #0x4
	pop {r3-r4, pc}
_0207CF32:
	mov r1, #0x2
	mov r2, #0x0
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldr r0, [r4, r0]
	sub r1, r1, #0x4
	add r2, #0xc0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0207CF50: .word 0x000004AC
_0207CF54: .word 0x0000068F

	thumb_func_start FUN_0207CF58
FUN_0207CF58: ; 0x0207CF58
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207CF74 ; =0x000004AC
	ldr r0, [r4, r0]
	bl FUN_0202022C
	cmp r0, #0x2
	bne _0207CF72
	ldr r0, _0207CF74 ; =0x000004AC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
_0207CF72:
	pop {r4, pc}
	.balign 4
_0207CF74: .word 0x000004AC

	thumb_func_start FUN_0207CF78
FUN_0207CF78: ; 0x0207CF78
	push {r3-r7, lr}
	ldr r7, _0207CFA8 ; =0x0000068E
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0x1
_0207CF82:
	add r0, r6, #0x0
	ldrb r1, [r5, r7]
	lsl r0, r4
	tst r0, r1
	beq _0207CF9C
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x4b
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	add r1, r6, #0x0
	bl FUN_020200A0
_0207CF9C:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x5
	blo _0207CF82
	pop {r3-r7, pc}
	.balign 4
_0207CFA8: .word 0x0000068E

	thumb_func_start FUN_0207CFAC
FUN_0207CFAC: ; 0x0207CFAC
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0207CFC0
	ldr r0, _0207CFE8 ; =0x000004C4
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
_0207CFC0:
	add r0, r1, #0x0
	bl FUN_0201AB14
	add r1, r0, #0x0
	ldr r0, _0207CFE8 ; =0x000004C4
	lsl r1, r1, #0x3
	sub r1, #0xa
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	asr r1, r1, #0x10
	mov r2, #0x8
	bl FUN_0200C6E4
	ldr r0, _0207CFE8 ; =0x000004C4
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
	nop
_0207CFE8: .word 0x000004C4

	thumb_func_start FUN_0207CFEC
FUN_0207CFEC: ; 0x0207CFEC
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_0207B628
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldrb r1, [r1, #0x11]
	cmp r1, #0x2
	bne _0207D008
	bl FUN_0206B688
	b _0207D00C
_0207D008:
	bl FUN_0206B6C8
_0207D00C:
	add r3, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1
	str r0, [sp, #0x0]
	mov r0, #0xb
	lsl r1, r1, #0xa
	str r0, [sp, #0x4]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	mov r2, #0x13
	bl FUN_0200C9D8
	mov r2, #0x97
	lsl r2, r2, #0x2
	add r1, r2, #0x0
	ldrh r0, [r4, r2]
	add r2, #0x44
	add r1, #0x42
	ldr r2, [r4, r2]
	ldrh r1, [r4, r1]
	lsl r2, r2, #0x3
	lsr r2, r2, #0x1f
	bl FUN_0206B7BC
	add r1, r0, #0x0
	ldr r0, _0207D068 ; =0x00000454
	add r1, r1, #0x7
	ldr r0, [r4, r0]
	bl FUN_0200C664
	mov r0, #0x97
	lsl r0, r0, #0x2
	ldrh r0, [r4, r0]
	mov r1, #0x1c
	bl FUN_02068678
	add r2, r0, #0x0
	ldr r0, _0207D068 ; =0x00000454
	mov r1, #0x1
	ldr r0, [r4, r0]
	eor r1, r2
	bl FUN_02020100
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0207D068: .word 0x00000454

	thumb_func_start FUN_0207D06C
FUN_0207D06C: ; 0x0207D06C
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_0206B888
	add r3, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x5
	lsl r1, r1, #0xa
	str r0, [sp, #0x4]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	mov r2, #0x13
	bl FUN_0200CA0C
	ldr r0, _0207D0C0 ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x3
	ldr r0, _0207D0C4 ; =0x00000454
	bne _0207D0A6
	ldr r0, [r4, r0]
	mov r1, #0x18
	mov r2, #0x30
	bl FUN_0200C6E4
	b _0207D0B0
_0207D0A6:
	ldr r0, [r4, r0]
	mov r1, #0x20
	mov r2, #0x44
	bl FUN_0200C6E4
_0207D0B0:
	ldr r0, _0207D0C4 ; =0x00000454
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_0200C63C
	add sp, #0x8
	pop {r4, pc}
	nop
_0207D0C0: .word 0x0000068C
_0207D0C4: .word 0x00000454

	thumb_func_start FUN_0207D0C8
FUN_0207D0C8: ; 0x0207D0C8
	push {r4, lr}
	add r4, r2, #0x0
	cmp r4, r1
	ble _0207D0EE
	add r0, #0x2c
	sub r1, r4, r1
	mul r1, r0
	lsl r0, r1, #0x10
	mov r1, #0x4b
	lsl r1, r1, #0x2
	bl _u32_div_f
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r0, r4, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	pop {r4, pc}
_0207D0EE:
	add r0, #0x2c
	sub r1, r1, r4
	mul r1, r0
	lsl r0, r1, #0x10
	mov r1, #0x4b
	lsl r1, r1, #0x2
	bl _u32_div_f
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, r4, r0
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	pop {r4, pc}

	thumb_func_start FUN_0207D10C
FUN_0207D10C: ; 0x0207D10C
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _0207D20C ; =0x00000295
	mov r1, #0x58
	ldrb r0, [r4, r0]
	add r2, r1, #0x0
	bl FUN_0207D0C8
	add r5, r0, #0x0
	ldr r0, _0207D20C ; =0x00000295
	mov r1, #0x31
	ldrb r0, [r4, r0]
	mov r2, #0x49
	bl FUN_0207D0C8
	add r2, r0, #0x0
	ldr r0, _0207D210 ; =0x000004C8
	add r1, r5, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	ldr r0, _0207D214 ; =0x00000296
	mov r1, #0x6e
	ldrb r0, [r4, r0]
	mov r2, #0x58
	bl FUN_0207D0C8
	add r5, r0, #0x0
	ldr r0, _0207D214 ; =0x00000296
	mov r1, #0x41
	ldrb r0, [r4, r0]
	mov r2, #0x49
	bl FUN_0207D0C8
	add r2, r0, #0x0
	ldr r0, _0207D218 ; =0x000004CC
	add r1, r5, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	ldr r0, _0207D21C ; =0x00000297
	mov r1, #0x67
	ldrb r0, [r4, r0]
	mov r2, #0x58
	bl FUN_0207D0C8
	add r5, r0, #0x0
	ldr r0, _0207D21C ; =0x00000297
	mov r1, #0x5c
	ldrb r0, [r4, r0]
	mov r2, #0x49
	bl FUN_0207D0C8
	add r2, r0, #0x0
	mov r0, #0x4d
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200C6E4
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	mov r1, #0x48
	mov r2, #0x57
	bl FUN_0207D0C8
	add r5, r0, #0x0
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldrb r0, [r4, r0]
	mov r1, #0x5c
	mov r2, #0x49
	bl FUN_0207D0C8
	add r2, r0, #0x0
	ldr r0, _0207D220 ; =0x000004D4
	add r1, r5, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	ldr r0, _0207D224 ; =0x00000299
	mov r1, #0x41
	ldrb r0, [r4, r0]
	mov r2, #0x57
	bl FUN_0207D0C8
	add r5, r0, #0x0
	ldr r0, _0207D224 ; =0x00000299
	mov r1, #0x41
	ldrb r0, [r4, r0]
	mov r2, #0x49
	bl FUN_0207D0C8
	add r2, r0, #0x0
	ldr r0, _0207D228 ; =0x000004D8
	add r1, r5, #0x0
	ldr r0, [r4, r0]
	bl FUN_0200C6E4
	ldr r0, _0207D210 ; =0x000004C8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207D218 ; =0x000004CC
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x4d
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_020200A0
	ldr r0, _0207D220 ; =0x000004D4
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207D228 ; =0x000004D8
	mov r1, #0x1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r3-r5, pc}
	nop
_0207D20C: .word 0x00000295
_0207D210: .word 0x000004C8
_0207D214: .word 0x00000296
_0207D218: .word 0x000004CC
_0207D21C: .word 0x00000297
_0207D220: .word 0x000004D4
_0207D224: .word 0x00000299
_0207D228: .word 0x000004D8

	thumb_func_start FUN_0207D22C
FUN_0207D22C: ; 0x0207D22C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207D268 ; =0x000004C8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207D26C ; =0x000004CC
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r0, #0x4d
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_020200A0
	ldr r0, _0207D270 ; =0x000004D4
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0207D274 ; =0x000004D8
	mov r1, #0x0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
	nop
_0207D268: .word 0x000004C8
_0207D26C: .word 0x000004CC
_0207D270: .word 0x000004D4
_0207D274: .word 0x000004D8

	thumb_func_start FUN_0207D278
FUN_0207D278: ; 0x0207D278
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x1
	add r4, r2, #0x0
	bl FUN_0207FC5C
	add r3, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x1
	add r0, #0x1a
	lsl r1, r1, #0xa
	str r0, [sp, #0x4]
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	mov r2, #0x27
	bl FUN_0200C9D8
	add r0, r6, #0x0
	mov r1, #0x2
	bl FUN_0207FC5C
	add r4, #0x37
	add r2, r0, #0x0
	lsl r0, r4, #0x2
	add r1, r5, r0
	ldr r0, _0207D2C4 ; =0x00000408
	ldr r0, [r1, r0]
	add r1, r2, #0x7
	bl FUN_0200C664
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0207D2C4: .word 0x00000408

	thumb_func_start FUN_0207D2C8
FUN_0207D2C8: ; 0x0207D2C8
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r6, _0207D354 ; =0x00000408
	add r5, r0, #0x0
	mov r4, #0x37
	mov r7, #0x0
_0207D2D4:
	lsl r0, r4, #0x2
	add r0, r5, r0
	ldr r0, [r0, r6]
	add r1, r7, #0x0
	bl FUN_020200A0
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x46
	bls _0207D2D4
	ldr r0, _0207D358 ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x6
	bne _0207D350
	mov r0, #0x0
	mov r1, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x5
	lsl r1, r1, #0xa
	str r0, [sp, #0x4]
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	mov r2, #0x27
	mov r3, #0x88
	bl FUN_0200CA0C
	ldr r7, _0207D35C ; =0x000004E4
	ldr r6, _0207D360 ; =0x00000699
	mov r4, #0x0
_0207D312:
	ldrb r0, [r5, r6]
	cmp r4, r0
	bge _0207D33A
	lsl r0, r4, #0x2
	add r0, r5, r0
	ldr r0, [r0, r7]
	mov r1, #0x1
	bl FUN_020200A0
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0207C1E8
	lsl r2, r4, #0x18
	add r1, r0, #0x0
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_0207D278
_0207D33A:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xc
	blo _0207D312
	mov r0, #0x52
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_02020130
_0207D350:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0207D354: .word 0x00000408
_0207D358: .word 0x0000068C
_0207D35C: .word 0x000004E4
_0207D360: .word 0x00000699

	thumb_func_start FUN_0207D364
FUN_0207D364: ; 0x0207D364
	push {r3-r7, lr}
	ldr r7, _0207D3BC ; =0x00000698
	add r5, r0, #0x0
	mov r4, #0x0
	add r6, r7, #0x1
_0207D36E:
	ldrb r0, [r5, r7]
	lsl r0, r0, #0x2
	add r1, r4, r0
	ldrb r0, [r5, r6]
	cmp r1, r0
	bge _0207D3A0
	lsl r0, r4, #0x2
	add r1, r5, r0
	ldr r0, _0207D3C0 ; =0x000004E4
	ldr r0, [r1, r0]
	mov r1, #0x1
	bl FUN_020200A0
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0207C1E8
	lsl r2, r4, #0x18
	add r1, r0, #0x0
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_0207D278
	b _0207D3AE
_0207D3A0:
	lsl r0, r4, #0x2
	add r1, r5, r0
	ldr r0, _0207D3C0 ; =0x000004E4
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl FUN_020200A0
_0207D3AE:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x8
	blo _0207D36E
	pop {r3-r7, pc}
	nop
_0207D3BC: .word 0x00000698
_0207D3C0: .word 0x000004E4

	thumb_func_start FUN_0207D3C4
FUN_0207D3C4: ; 0x0207D3C4
	ldr r1, _0207D3E8 ; =0x00000697
	ldrb r2, [r0, r1]
	ldr r1, _0207D3EC ; =0x00000514
	ldr r0, [r0, r1]
	lsl r1, r2, #0x1e
	lsr r3, r2, #0x2
	mov r2, #0x28
	mul r2, r3
	lsr r1, r1, #0x19
	add r1, #0x84
	add r2, #0x38
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	ldr r3, _0207D3F0 ; =FUN_0200C6E4
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bx r3
	nop
_0207D3E8: .word 0x00000697
_0207D3EC: .word 0x00000514
_0207D3F0: .word FUN_0200C6E4

	thumb_func_start FUN_0207D3F4
FUN_0207D3F4: ; 0x0207D3F4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x52
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02020128
	cmp r0, #0x1
	bne _0207D414
	mov r0, #0x52
	lsl r0, r0, #0x4
	mov r1, #0x1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
_0207D414:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207D418
FUN_0207D418: ; 0x0207D418
	push {r3-r7, lr}
	add r5, r0, #0x0
	cmp r1, #0x0
	bne _0207D43E
	mov r4, #0x0
	ldr r6, _0207D4C0 ; =0x00000524
	add r7, r4, #0x0
_0207D426:
	lsl r0, r4, #0x2
	add r0, r5, r0
	ldr r0, [r0, r6]
	add r1, r7, #0x0
	bl FUN_020200A0
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x5
	blo _0207D426
	pop {r3-r7, pc}
_0207D43E:
	ldr r0, _0207D4C4 ; =0x00000295
	ldrb r1, [r5, r0]
	add r0, r0, #0x1
	ldrb r0, [r5, r0]
	add r4, r1, #0x0
	cmp r1, r0
	bge _0207D44E
	add r4, r0, #0x0
_0207D44E:
	ldr r0, _0207D4C8 ; =0x00000297
	ldrb r0, [r5, r0]
	cmp r4, r0
	bge _0207D458
	add r4, r0, #0x0
_0207D458:
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldrb r0, [r5, r0]
	cmp r4, r0
	bge _0207D464
	add r4, r0, #0x0
_0207D464:
	ldr r0, _0207D4CC ; =0x00000299
	ldrb r0, [r5, r0]
	cmp r4, r0
	bge _0207D46E
	add r4, r0, #0x0
_0207D46E:
	ldr r0, _0207D4C0 ; =0x00000524
	ldr r3, _0207D4D0 ; =0x020FA75C
	ldr r0, [r5, r0]
	add r2, r4, #0x0
	bl FUN_0207D4F4
	ldr r1, _0207D4D4 ; =0x00000296
	ldr r0, _0207D4D8 ; =0x00000528
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	ldr r3, _0207D4DC ; =0x020FA764
	add r2, r4, #0x0
	bl FUN_0207D4F4
	ldr r1, _0207D4C8 ; =0x00000297
	ldr r0, _0207D4E0 ; =0x0000052C
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	ldr r3, _0207D4E4 ; =0x020FA76C
	add r2, r4, #0x0
	bl FUN_0207D4F4
	mov r1, #0x53
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	lsr r1, r1, #0x1
	ldrb r1, [r5, r1]
	ldr r3, _0207D4E8 ; =0x020FA774
	add r2, r4, #0x0
	bl FUN_0207D4F4
	ldr r1, _0207D4CC ; =0x00000299
	ldr r0, _0207D4EC ; =0x00000534
	ldrb r1, [r5, r1]
	ldr r0, [r5, r0]
	ldr r3, _0207D4F0 ; =0x020FA77C
	add r2, r4, #0x0
	bl FUN_0207D4F4
	pop {r3-r7, pc}
	nop
_0207D4C0: .word 0x00000524
_0207D4C4: .word 0x00000295
_0207D4C8: .word 0x00000297
_0207D4CC: .word 0x00000299
_0207D4D0: .word 0x020FA75C
_0207D4D4: .word 0x00000296
_0207D4D8: .word 0x00000528
_0207D4DC: .word 0x020FA764
_0207D4E0: .word 0x0000052C
_0207D4E4: .word 0x020FA76C
_0207D4E8: .word 0x020FA774
_0207D4EC: .word 0x00000534
_0207D4F0: .word 0x020FA77C

	thumb_func_start FUN_0207D4F4
FUN_0207D4F4: ; 0x0207D4F4
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, r3, #0x0
	cmp r5, #0x0
	beq _0207D504
	cmp r5, r2
	beq _0207D50E
_0207D504:
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_020200A0
	pop {r4-r6, pc}
_0207D50E:
	mov r1, #0x1
	bl FUN_020200A0
	mov r0, #0x0
	ldrsh r1, [r4, r0]
	mov r0, #0x4
	ldrsh r0, [r4, r0]
	cmp r1, r0
	blt _0207D534
	sub r1, r1, r0
	lsl r2, r1, #0x8
	asr r1, r2, #0x7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #0x8
	mul r1, r5
	lsr r1, r1, #0x8
	add r1, r0, r1
	b _0207D546
_0207D534:
	sub r1, r0, r1
	lsl r2, r1, #0x8
	asr r1, r2, #0x7
	lsr r1, r1, #0x18
	add r1, r2, r1
	asr r1, r1, #0x8
	mul r1, r5
	lsr r1, r1, #0x8
	sub r1, r0, r1
_0207D546:
	mov r0, #0x2
	ldrsh r2, [r4, r0]
	mov r0, #0x6
	ldrsh r0, [r4, r0]
	cmp r2, r0
	blt _0207D566
	sub r2, r2, r0
	lsl r3, r2, #0x8
	asr r2, r3, #0x7
	lsr r2, r2, #0x18
	add r2, r3, r2
	asr r2, r2, #0x8
	mul r2, r5
	lsr r2, r2, #0x8
	add r2, r0, r2
	b _0207D578
_0207D566:
	sub r2, r0, r2
	lsl r3, r2, #0x8
	asr r2, r3, #0x7
	lsr r2, r2, #0x18
	add r2, r3, r2
	asr r2, r2, #0x8
	mul r2, r5
	lsr r2, r2, #0x8
	sub r2, r0, r2
_0207D578:
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, r6, #0x0
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_0200C6E4
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_02020208
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_02020130
	pop {r4-r6, pc}

	thumb_func_start FUN_0207D598
FUN_0207D598: ; 0x0207D598
	push {r3-r7, lr}
	mov r7, #0x1
	ldr r6, _0207D5B8 ; =0x00000524
	add r5, r0, #0x0
	mov r4, #0x0
	lsl r7, r7, #0xc
_0207D5A4:
	ldr r0, [r5, r6]
	add r1, r7, #0x0
	bl FUN_020201E4
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x5
	blo _0207D5A4
	pop {r3-r7, pc}
	nop
_0207D5B8: .word 0x00000524

	thumb_func_start FUN_0207D5BC
FUN_0207D5BC: ; 0x0207D5BC
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r5, #0x0
	add r4, r7, #0x4
_0207D5C4:
	ldr r2, _0207D600 ; =0x020FB4AC
	lsl r6, r5, #0x4
	lsl r3, r5, #0x3
	ldr r0, [r7, #0x0]
	add r1, r4, r6
	add r2, r2, r3
	bl FUN_02019150
	add r0, r4, r6
	mov r1, #0x0
	bl FUN_02019620
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x24
	blo _0207D5C4
	add r0, r7, #0x0
	bl FUN_0207DB78
	add r0, r7, #0x0
	bl FUN_0207D768
	add r0, r7, #0x0
	bl FUN_0207D800
	add r0, r7, #0x0
	bl FUN_0207D8A0
	pop {r3-r7, pc}
	.balign 4
_0207D600: .word 0x020FB4AC

	thumb_func_start FUN_0207D604
FUN_0207D604: ; 0x0207D604
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r0, _0207D6D8 ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x7
	bhi _0207D6D4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207D61C: ; jump table (using 16-bit offset)
	.short _0207D62C - _0207D61C - 2; case 0
	.short _0207D638 - _0207D61C - 2; case 1
	.short _0207D644 - _0207D61C - 2; case 2
	.short _0207D650 - _0207D61C - 2; case 3
	.short _0207D674 - _0207D61C - 2; case 4
	.short _0207D65C - _0207D61C - 2; case 5
	.short _0207D668 - _0207D61C - 2; case 6
	.short _0207D674 - _0207D61C - 2; case 7
_0207D62C:
	mov r0, #0x92
	mov r1, #0x6
	lsl r0, r0, #0x2
	ldr r5, _0207D6DC ; =0x020FB3FC
	str r1, [r4, r0]
	b _0207D692
_0207D638:
	mov r0, #0x92
	mov r1, #0x1
	lsl r0, r0, #0x2
	ldr r5, _0207D6E0 ; =0x020FB38C
	str r1, [r4, r0]
	b _0207D692
_0207D644:
	mov r0, #0x92
	mov r1, #0x8
	lsl r0, r0, #0x2
	ldr r5, _0207D6E4 ; =0x020FB42C
	str r1, [r4, r0]
	b _0207D692
_0207D650:
	mov r0, #0x92
	mov r1, #0x8
	lsl r0, r0, #0x2
	ldr r5, _0207D6E8 ; =0x020FB46C
	str r1, [r4, r0]
	b _0207D692
_0207D65C:
	mov r0, #0x92
	mov r1, #0x6
	lsl r0, r0, #0x2
	ldr r5, _0207D6EC ; =0x020FB3CC
	str r1, [r4, r0]
	b _0207D692
_0207D668:
	mov r0, #0x92
	mov r1, #0x4
	lsl r0, r0, #0x2
	ldr r5, _0207D6F0 ; =0x020FB3AC
	str r1, [r4, r0]
	b _0207D692
_0207D674:
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x3
	beq _0207D684
	cmp r0, #0x4
	bne _0207D6D4
_0207D684:
	mov r0, #0x92
	mov r1, #0x3
	lsl r0, r0, #0x2
	ldr r5, _0207D6F4 ; =0x020FB394
	str r1, [r4, r0]
	b _0207D692
_0207D690:
	pop {r3-r7, pc}
_0207D692:
	mov r1, #0x92
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r0, #0x13
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02018FF4
	mov r1, #0x91
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r0, r1, #0x4
	ldr r0, [r4, r0]
	mov r6, #0x0
	cmp r0, #0x0
	bls _0207D6D4
	add r7, r6, #0x0
_0207D6B4:
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r0, [r4, #0x0]
	add r1, r1, r7
	add r2, r5, #0x0
	bl FUN_02019150
	mov r0, #0x92
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r6, r6, #0x1
	add r5, #0x8
	add r7, #0x10
	cmp r6, r0
	blo _0207D6B4
_0207D6D4:
	pop {r3-r7, pc}
	nop
_0207D6D8: .word 0x0000068C
_0207D6DC: .word 0x020FB3FC
_0207D6E0: .word 0x020FB38C
_0207D6E4: .word 0x020FB42C
_0207D6E8: .word 0x020FB46C
_0207D6EC: .word 0x020FB3CC
_0207D6F0: .word 0x020FB3AC
_0207D6F4: .word 0x020FB394

	thumb_func_start FUN_0207D6F8
FUN_0207D6F8: ; 0x0207D6F8
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, _0207D748 ; =0x0000068C
	ldrsb r0, [r1, r0]
	cmp r0, #0x7
	bhi _0207D744
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207D710: ; jump table (using 16-bit offset)
	.short _0207D732 - _0207D710 - 2; case 0
	.short _0207D732 - _0207D710 - 2; case 1
	.short _0207D732 - _0207D710 - 2; case 2
	.short _0207D732 - _0207D710 - 2; case 3
	.short _0207D720 - _0207D710 - 2; case 4
	.short _0207D732 - _0207D710 - 2; case 5
	.short _0207D732 - _0207D710 - 2; case 6
	.short _0207D720 - _0207D710 - 2; case 7
_0207D720:
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x3
	beq _0207D732
	cmp r0, #0x4
	beq _0207D732
	pop {r3, pc}
_0207D732:
	mov r2, #0x91
	lsl r2, r2, #0x2
	ldr r0, [r1, r2]
	add r2, r2, #0x4
	ldr r1, [r1, r2]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_020191A4
_0207D744:
	pop {r3, pc}
	nop
_0207D748: .word 0x0000068C

	thumb_func_start FUN_0207D74C
FUN_0207D74C: ; 0x0207D74C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0207D6F8
	mov r4, #0x0
	add r5, r5, #0x4
_0207D758:
	add r0, r5, #0x0
	bl FUN_02019178
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x24
	blo _0207D758
	pop {r3-r5, pc}

	thumb_func_start FUN_0207D768
FUN_0207D768: ; 0x0207D768
	push {r3-r5, lr}
	sub sp, #0x10
	mov r4, #0x89
	add r5, r0, #0x0
	lsl r4, r4, #0x2
	add r0, r5, r4
	mov r1, #0x0
	bl FUN_02019620
	mov r1, #0x0
	add r2, r4, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207D7F4 ; =0x000F0E00
	add r2, #0x30
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r2, [r5, r2]
	add r0, r5, r4
	add r3, r1, #0x0
	bl FUN_0201BDE0
	add r0, r4, #0x0
	add r0, #0x3e
	ldrb r1, [r5, r0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1f
	bne _0207D7E8
	add r0, r0, #0x1
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	bne _0207D7CA
	ldr r2, _0207D7F8 ; =0x00000674
	mov r1, #0x1
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	mov r2, #0xc1
	add r0, r5, #0x0
	add r1, r5, r4
	lsl r2, r2, #0xa
	mov r3, #0x1
	bl FUN_0207D998
	b _0207D7E8
_0207D7CA:
	cmp r0, #0x1
	bne _0207D7E8
	ldr r2, _0207D7F8 ; =0x00000674
	mov r1, #0x2
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	ldr r2, _0207D7FC ; =0x00050600
	add r0, r5, #0x0
	add r1, r5, r4
	mov r3, #0x1
	bl FUN_0207D998
_0207D7E8:
	add r0, r5, r4
	bl FUN_02019220
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_0207D7F4: .word 0x000F0E00
_0207D7F8: .word 0x00000674
_0207D7FC: .word 0x00050600

	thumb_func_start FUN_0207D800
FUN_0207D800: ; 0x0207D800
	push {r4-r6, lr}
	sub sp, #0x10
	mov r6, #0x85
	add r5, r0, #0x0
	lsl r6, r6, #0x2
	add r0, r5, r6
	mov r1, #0x0
	bl FUN_02019620
	add r0, r6, #0x0
	add r0, #0x8c
	ldr r0, [r5, r0]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	bne _0207D88A
	mov r0, #0x5
	str r0, [sp, #0x0]
	mov r0, #0x67
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x1
	add r2, r5, r6
	mov r3, #0x0
	bl FUN_0200B9A8
	ldr r0, _0207D894 ; =0x00000674
	mov r1, #0x3
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x0
	add r4, r0, #0x0
	add r2, r6, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r2, #0x4e
	ldrb r2, [r5, r2]
	ldr r0, _0207D898 ; =0x0000067C
	mov r3, #0x3
	lsl r2, r2, #0x19
	ldr r0, [r5, r0]
	lsr r2, r2, #0x19
	bl FUN_0200AD38
	ldr r1, _0207D898 ; =0x0000067C
	add r2, r4, #0x0
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	mov r2, #0x1a
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207D89C ; =0x00010200
	lsl r2, r2, #0x6
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r2, [r5, r2]
	add r0, r5, r6
	mov r3, #0x10
	bl FUN_0201BDE0
_0207D88A:
	add r0, r5, r6
	bl FUN_02019220
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0207D894: .word 0x00000674
_0207D898: .word 0x0000067C
_0207D89C: .word 0x00010200

	thumb_func_start FUN_0207D8A0
FUN_0207D8A0: ; 0x0207D8A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x0
	bl FUN_02019620
	ldr r0, _0207D918 ; =0x0000025E
	ldrh r2, [r5, r0]
	cmp r2, #0x0
	beq _0207D8E4
	ldr r0, _0207D91C ; =0x0000067C
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200AE38
	ldr r0, _0207D920 ; =0x00000674
	mov r1, #0x5
	ldr r0, [r5, r0]
	bl FUN_0200A914
	add r4, r0, #0x0
	ldr r1, _0207D91C ; =0x0000067C
	add r2, r4, #0x0
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	b _0207D8F2
_0207D8E4:
	ldr r2, _0207D920 ; =0x00000674
	mov r1, #0x6
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
_0207D8F2:
	mov r2, #0x81
	lsl r2, r2, #0x2
	add r1, r5, r2
	add r0, r5, #0x0
	lsl r2, r2, #0x7
	mov r3, #0x0
	bl FUN_0207D998
	add r0, r5, #0x0
	add r0, #0x64
	bl FUN_02019220
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r5, r0
	bl FUN_02019220
	pop {r3-r5, pc}
	nop
_0207D918: .word 0x0000025E
_0207D91C: .word 0x0000067C
_0207D920: .word 0x00000674

	thumb_func_start FUN_0207D924
FUN_0207D924: ; 0x0207D924
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r4, r1, #0x0
	add r0, r5, r0
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207D954 ; =0x000F0E00
	add r0, r5, #0x0
	mov r1, #0x23
	add r2, r4, #0x0
	bl FUN_0207DA1C
	mov r0, #0x8d
	lsl r0, r0, #0x2
	add r0, r5, r0
	bl FUN_02019220
	pop {r3-r5, pc}
	nop
_0207D954: .word 0x000F0E00

	thumb_func_start FUN_0207D958
FUN_0207D958: ; 0x0207D958
	push {r4, lr}
	mov r3, #0x93
	lsl r3, r3, #0x2
	add r1, r0, #0x0
	add r2, r3, #0x0
	add r2, #0x18
	ldr r0, [r1, r3]
	ldr r4, [r1, r2]
	ldr r2, [r0, #0xc]
	cmp r4, r2
	bne _0207D98E
	add r2, r3, #0x0
	add r2, #0x48
	ldrb r2, [r1, r2]
	ldrb r0, [r0, #0x10]
	cmp r2, r0
	bne _0207D98E
	ldr r2, _0207D994 ; =0x00000684
	add r3, #0xc
	ldr r0, [r1, r3]
	ldr r1, [r1, r2]
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _0207D98E
	mov r0, #0x1
	pop {r4, pc}
_0207D98E:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0207D994: .word 0x00000684

	thumb_func_start FUN_0207D998
FUN_0207D998: ; 0x0207D998
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	cmp r3, #0x0
	beq _0207D9B0
	cmp r3, #0x1
	beq _0207D9B4
	cmp r3, #0x2
	beq _0207D9D8
	b _0207D9FE
_0207D9B0:
	mov r3, #0x0
	b _0207D9FE
_0207D9B4:
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r4, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r6, #0x0
	bl FUN_0201AB0C
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x18
	sub r0, r0, r5
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	b _0207D9FE
_0207D9D8:
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r4, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r6, #0x0
	bl FUN_0201AB0C
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x18
	sub r1, r0, r5
	lsr r0, r1, #0x1f
	add r0, r1, r0
	lsl r0, r0, #0x17
	lsr r3, r0, #0x18
_0207D9FE:
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	str r7, [sp, #0x8]
	mov r2, #0x1a
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r2, [r4, r2]
	add r0, r6, #0x0
	bl FUN_0201BDE0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207DA1C
FUN_0207DA1C: ; 0x0207DA1C
	push {r4-r6, lr}
	add r6, r3, #0x0
	ldr r3, _0207DA44 ; =0x00000674
	add r5, r0, #0x0
	ldr r0, [r5, r3]
	add r4, r1, #0x0
	add r3, #0xc
	add r1, r2, #0x0
	ldr r2, [r5, r3]
	bl FUN_0200A8E0
	add r2, r5, #0x4
	lsl r1, r4, #0x4
	add r1, r2, r1
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0207D998
	pop {r4-r6, pc}
	.balign 4
_0207DA44: .word 0x00000674

	thumb_func_start FUN_0207DA48
FUN_0207DA48: ; 0x0207DA48
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0207DA8C ; =0x00000674
	add r6, r2, #0x0
	ldr r0, [r5, r0]
	add r7, r3, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	mov r1, #0x0
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, _0207DA90 ; =0x0000067C
	add r3, r7, #0x0
	ldr r0, [r5, r0]
	bl FUN_0200AD38
	ldr r1, _0207DA90 ; =0x0000067C
	add r2, r4, #0x0
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0207DA8C: .word 0x00000674
_0207DA90: .word 0x0000067C

	thumb_func_start FUN_0207DA94
FUN_0207DA94: ; 0x0207DA94
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	str r3, [sp, #0x10]
	mov r0, #0x91
	lsl r0, r0, #0x2
	lsl r7, r1, #0x4
	ldr r3, _0207DB70 ; =0x00000674
	ldr r5, [r4, r0]
	ldr r0, [r4, r3]
	add r3, #0xc
	add r1, r2, #0x0
	ldr r2, [r4, r3]
	bl FUN_0200A8E0
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r4, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	add r1, sp, #0x48
	ldrb r2, [r1, #0x0]
	lsr r1, r0, #0x1
	sub r1, r2, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	add r0, r1, r0
	str r1, [sp, #0x14]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x18]
	add r0, sp, #0x4c
	ldrb r0, [r0, #0x0]
	mov r2, #0x1a
	mov r1, #0x0
	str r0, [sp, #0x1c]
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207DB74 ; =0x00010200
	lsl r2, r2, #0x6
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r2, [r4, r2]
	ldr r3, [sp, #0x14]
	add r0, r5, r7
	bl FUN_0201BDE0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r3, sp, #0x28
	ldrh r2, [r3, #0x14]
	ldrb r3, [r3, #0x1c]
	ldr r1, [sp, #0x10]
	add r0, r4, #0x0
	bl FUN_0207DA48
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r4, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	mov r12, r0
	ldr r0, [sp, #0x1c]
	mov r2, #0x1a
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207DB74 ; =0x00010200
	mov r1, #0x0
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r3, [sp, #0x14]
	mov r6, r12
	ldr r2, [r4, r2]
	add r0, r5, r7
	sub r3, r3, r6
	bl FUN_0201BDE0
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r3, sp, #0x28
	ldrh r2, [r3, #0x18]
	ldrb r3, [r3, #0x1c]
	ldr r1, [sp, #0x38]
	add r0, r4, #0x0
	bl FUN_0207DA48
	ldr r0, [sp, #0x1c]
	mov r2, #0x1a
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207DB74 ; =0x00010200
	mov r1, #0x0
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r2, [r4, r2]
	ldr r3, [sp, #0x18]
	add r0, r5, r7
	bl FUN_0201BDE0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_0207DB70: .word 0x00000674
_0207DB74: .word 0x00010200

	thumb_func_start FUN_0207DB78
FUN_0207DB78: ; 0x0207DB78
	push {r4, lr}
	sub sp, #0x10
	ldr r3, _0207DD7C ; =0x000F0E00
	mov r1, #0x0
	mov r2, #0x7
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x1
	mov r2, #0x17
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x6d
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x3
	mov r2, #0x7e
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x4
	mov r2, #0x80
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x9d
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x6
	mov r2, #0x4
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x8
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x8
	mov r2, #0xa
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x9
	mov r2, #0xc
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0xa
	mov r2, #0xd
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0xb
	mov r2, #0xf
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0xc
	mov r2, #0x11
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0xd
	mov r2, #0x13
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0xf
	mov r2, #0x6e
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x10
	mov r2, #0x6f
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x11
	mov r2, #0x70
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x12
	mov r2, #0x71
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x13
	mov r2, #0x72
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x14
	mov r2, #0x73
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x15
	mov r2, #0x74
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x16
	mov r2, #0x7f
	bl FUN_0207DA1C
	ldr r2, _0207DD80 ; =0x00000674
	mov r1, #0x92
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r2, #0xff
	str r2, [sp, #0x4]
	ldr r0, _0207DD7C ; =0x000F0E00
	mov r1, #0x0
	str r0, [sp, #0x8]
	add r2, #0x85
	add r0, r4, r2
	mov r2, #0x1a
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r2, [r4, r2]
	add r3, r1, #0x0
	bl FUN_0201BDE0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x19
	mov r2, #0x95
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x1a
	mov r2, #0x93
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x1b
	mov r2, #0x94
	bl FUN_0207DA1C
	mov r0, #0x2
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x1c
	mov r2, #0xa2
	bl FUN_0207DA1C
	mov r0, #0x2
	str r0, [sp, #0x0]
	ldr r3, _0207DD84 ; =0x00010200
	add r0, r4, #0x0
	mov r1, #0x1d
	mov r2, #0xa0
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD84 ; =0x00010200
	add r0, r4, #0x0
	mov r1, #0x1e
	mov r2, #0xb6
	bl FUN_0207DA1C
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, _0207DD7C ; =0x000F0E00
	add r0, r4, #0x0
	mov r1, #0x1f
	mov r2, #0xb3
	bl FUN_0207DA1C
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0207DD7C: .word 0x000F0E00
_0207DD80: .word 0x00000674
_0207DD84: .word 0x00010200

	thumb_func_start FUN_0207DD88
FUN_0207DD88: ; 0x0207DD88
	push {r4, lr}
	sub sp, #0x10
	mov r2, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_02018540
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x12
	str r0, [sp, #0x4]
	mov r0, #0x16
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	mov r2, #0x0
	mov r3, #0xe
	bl FUN_02018540
	ldr r0, _0207DE38 ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x7
	bhi _0207DE34
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207DDD8: ; jump table (using 16-bit offset)
	.short _0207DDE8 - _0207DDD8 - 2; case 0
	.short _0207DDF2 - _0207DDD8 - 2; case 1
	.short _0207DDFC - _0207DDD8 - 2; case 2
	.short _0207DE10 - _0207DDD8 - 2; case 3
	.short _0207DE06 - _0207DDD8 - 2; case 4
	.short _0207DE1A - _0207DDD8 - 2; case 5
	.short _0207DE24 - _0207DDD8 - 2; case 6
	.short _0207DE2E - _0207DDD8 - 2; case 7
_0207DDE8:
	add r0, r4, #0x0
	bl FUN_0207DE3C
	add sp, #0x10
	pop {r4, pc}
_0207DDF2:
	add r0, r4, #0x0
	bl FUN_0207E190
	add sp, #0x10
	pop {r4, pc}
_0207DDFC:
	add r0, r4, #0x0
	bl FUN_0207E200
	add sp, #0x10
	pop {r4, pc}
_0207DE06:
	add r0, r4, #0x0
	bl FUN_0207E4A0
	add sp, #0x10
	pop {r4, pc}
_0207DE10:
	add r0, r4, #0x0
	bl FUN_0207E594
	add sp, #0x10
	pop {r4, pc}
_0207DE1A:
	add r0, r4, #0x0
	bl FUN_0207E650
	add sp, #0x10
	pop {r4, pc}
_0207DE24:
	add r0, r4, #0x0
	bl FUN_0207E70C
	add sp, #0x10
	pop {r4, pc}
_0207DE2E:
	add r0, r4, #0x0
	bl FUN_0207E788
_0207DE34:
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0207DE38: .word 0x0000068C

	thumb_func_start FUN_0207DE3C
FUN_0207DE3C: ; 0x0207DE3C
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, r4, #0x4
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0x74
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0x84
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0x94
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0xa4
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0xb4
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0xc4
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0xd4
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0xe4
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x20
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x40
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x50
	bl FUN_02019620
	mov r1, #0x93
	lsl r1, r1, #0x2
	ldr r0, [r4, r1]
	add r1, #0x10
	ldrh r1, [r4, r1]
	ldr r0, [r0, #0x1c]
	bl FUN_0206BB48
	add r2, r0, #0x0
	beq _0207DEFE
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x9
	mov r3, #0x3
	bl FUN_0207DA48
	b _0207DF0C
_0207DEFE:
	ldr r2, _0207E0B4 ; =0x00000674
	mov r1, #0x16
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
_0207DF0C:
	mov r1, #0x2a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	lsl r0, r0, #0x2
	lsr r0, r0, #0x1f
	bne _0207DF28
	sub r1, #0x5c
	ldr r1, [r4, r1]
	ldr r2, _0207E0B8 ; =0x00010200
	add r0, r4, #0x0
	mov r3, #0x2
	bl FUN_0207D998
	b _0207DF36
_0207DF28:
	sub r1, #0x5c
	ldr r1, [r4, r1]
	ldr r2, _0207E0BC ; =0x00050600
	add r0, r4, #0x0
	mov r3, #0x2
	bl FUN_0207D998
_0207DF36:
	mov r1, #0x25
	lsl r1, r1, #0x4
	mov r0, #0x0
	ldr r1, [r4, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	mov r2, #0x91
	lsl r2, r2, #0x2
	ldr r3, [r4, r2]
	mov r1, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E0B8 ; =0x00010200
	add r2, #0xc
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r0, r3, #0x0
	ldrb r3, [r3, #0x17]
	ldr r2, [r4, r2]
	add r0, #0x10
	lsl r3, r3, #0x3
	sub r3, r3, r5
	lsr r3, r3, #0x1
	bl FUN_0201BDE0
	mov r1, #0x96
	lsl r1, r1, #0x2
	mov r0, #0x0
	ldr r1, [r4, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	mov r5, #0x91
	lsl r5, r5, #0x2
	ldr r2, [r4, r5]
	add r1, r2, #0x0
	add r1, #0x27
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x3
	sub r0, r1, r0
	lsr r3, r0, #0x1
	add r0, r5, #0x0
	add r0, #0x50
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0207DFB6
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #0x8]
	add r2, #0x20
	str r1, [sp, #0xc]
	add r5, #0x14
	add r0, r2, #0x0
	ldr r2, [r4, r5]
	bl FUN_0201BDE0
	b _0207DFD0
_0207DFB6:
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E0BC ; =0x00050600
	add r2, #0x20
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r5, #0x14
	add r0, r2, #0x0
	ldr r2, [r4, r5]
	bl FUN_0201BDE0
_0207DFD0:
	mov r0, #0x2
	mov r2, #0x99
	str r0, [sp, #0x0]
	lsl r2, r2, #0x2
	ldr r2, [r4, r2]
	add r0, r4, #0x0
	lsl r2, r2, #0x10
	mov r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #0x5
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E0B8 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x30
	mov r3, #0x2
	bl FUN_0207D998
	mov r0, #0x1
	mov r2, #0x9a
	str r0, [sp, #0x0]
	lsl r2, r2, #0x2
	ldr r2, [r4, r2]
	add r0, r4, #0x0
	mov r1, #0x12
	mov r3, #0x7
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E0B8 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x40
	mov r3, #0x2
	bl FUN_0207D998
	ldr r3, _0207E0C0 ; =0x00000262
	ldrb r0, [r4, r3]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	cmp r0, #0x64
	bhs _0207E048
	mov r0, #0x1
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r2, #0xe
	ldr r5, [r4, r2]
	add r2, r3, #0x6
	ldr r2, [r4, r2]
	add r0, r4, #0x0
	mov r1, #0x15
	sub r2, r5, r2
	mov r3, #0x7
	bl FUN_0207DA48
	b _0207E058
_0207E048:
	mov r0, #0x1
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x15
	mov r2, #0x0
	mov r3, #0x7
	bl FUN_0207DA48
_0207E058:
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E0B8 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x50
	mov r3, #0x2
	bl FUN_0207D998
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x40
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x50
	bl FUN_02019220
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_0207E0B4: .word 0x00000674
_0207E0B8: .word 0x00010200
_0207E0BC: .word 0x00050600
_0207E0C0: .word 0x00000262

	thumb_func_start FUN_0207E0C4
FUN_0207E0C4: ; 0x0207E0C4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0x13
	bl FUN_0207FD00
	add r4, r0, #0x0
	ldr r2, [r4, #0x18]
	cmp r2, #0x0
	beq _0207E0F8
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	sub r0, r0, #0x1
	lsl r0, r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E18C ; =0x00010200
	add r3, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
_0207E0F8:
	ldr r2, [r4, #0x20]
	cmp r2, #0x0
	beq _0207E11A
	ldr r0, [r4, #0x1c]
	mov r1, #0x0
	sub r0, r0, #0x1
	lsl r0, r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E18C ; =0x00010200
	add r3, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
_0207E11A:
	ldr r2, [r4, #0x28]
	cmp r2, #0x0
	beq _0207E13C
	ldr r0, [r4, #0x24]
	mov r1, #0x0
	sub r0, r0, #0x1
	lsl r0, r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E18C ; =0x00010200
	add r3, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
_0207E13C:
	ldr r2, [r4, #0x30]
	cmp r2, #0x0
	beq _0207E15E
	ldr r0, [r4, #0x2c]
	mov r1, #0x0
	sub r0, r0, #0x1
	lsl r0, r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E18C ; =0x00010200
	add r3, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
_0207E15E:
	ldr r2, [r4, #0x38]
	cmp r2, #0x0
	beq _0207E180
	ldr r0, [r4, #0x34]
	mov r1, #0x0
	sub r0, r0, #0x1
	lsl r0, r0, #0x4
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E18C ; =0x00010200
	add r3, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	str r1, [sp, #0xc]
	bl FUN_0201BDE0
_0207E180:
	add r0, r4, #0x0
	bl FUN_02080094
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_0207E18C: .word 0x00010200

	thumb_func_start FUN_0207E190
FUN_0207E190: ; 0x0207E190
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_02019620
	add r0, r5, #0x0
	bl FUN_0207B628
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0207D958
	add r7, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	ldrb r1, [r1, #0x11]
	cmp r1, #0x2
	bne _0207E1E8
	mov r0, #0x13
	bl FUN_020669C0
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02069A64
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0207E0C4
	add r0, r4, #0x0
	bl FUN_02016A18
	b _0207E1F4
_0207E1E8:
	sub r0, #0x8
	ldr r0, [r5, r0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_0207E0C4
_0207E1F4:
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_02019220
	pop {r3-r7, pc}

	thumb_func_start FUN_0207E200
FUN_0207E200: ; 0x0207E200
	push {r3-r5, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	add r0, #0x24
	bl FUN_02019220
	add r0, r4, #0x0
	add r0, #0xf4
	bl FUN_02019220
	mov r0, #0x41
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x45
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x49
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x51
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x55
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x20
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x40
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x50
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x60
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x70
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0201AB0C
	mov r1, #0x76
	str r1, [sp, #0x0]
	mov r1, #0x9d
	lsl r1, r1, #0x2
	ldrh r2, [r4, r1]
	lsl r0, r0, #0x1a
	add r1, r1, #0x2
	str r2, [sp, #0x4]
	ldrh r1, [r4, r1]
	lsr r0, r0, #0x18
	mov r2, #0x75
	str r1, [sp, #0x8]
	mov r1, #0x3
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r1, #0x0
	add r0, r4, #0x0
	mov r3, #0x77
	str r1, [sp, #0x14]
	bl FUN_0207DA94
	mov r0, #0x0
	mov r2, #0x9e
	str r0, [sp, #0x0]
	lsl r2, r2, #0x2
	ldrh r2, [r4, r2]
	add r0, r4, #0x0
	mov r1, #0x78
	mov r3, #0x3
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x10
	mov r3, #0x1
	bl FUN_0207D998
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r2, _0207E488 ; =0x0000027A
	add r0, r4, #0x0
	ldrh r2, [r4, r2]
	mov r1, #0x79
	mov r3, #0x3
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x20
	mov r3, #0x1
	bl FUN_0207D998
	mov r0, #0x0
	mov r2, #0x9f
	str r0, [sp, #0x0]
	lsl r2, r2, #0x2
	ldrh r2, [r4, r2]
	add r0, r4, #0x0
	mov r1, #0x7a
	mov r3, #0x3
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x30
	mov r3, #0x1
	bl FUN_0207D998
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r2, _0207E48C ; =0x0000027E
	add r0, r4, #0x0
	ldrh r2, [r4, r2]
	mov r1, #0x7b
	mov r3, #0x3
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x40
	mov r3, #0x1
	bl FUN_0207D998
	mov r0, #0x0
	mov r2, #0xa
	str r0, [sp, #0x0]
	lsl r2, r2, #0x6
	ldrh r2, [r4, r2]
	add r0, r4, #0x0
	mov r1, #0x7c
	mov r3, #0x3
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x50
	mov r3, #0x1
	bl FUN_0207D998
	ldr r2, _0207E490 ; =0x00000282
	ldr r0, _0207E494 ; =0x0000067C
	ldrb r2, [r4, r2]
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ADCC
	ldr r0, _0207E498 ; =0x00000674
	mov r1, #0x7d
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	ldr r1, _0207E494 ; =0x0000067C
	add r2, r5, #0x0
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x60
	mov r3, #0x0
	bl FUN_0207D998
	ldr r2, _0207E49C ; =0x0000022A
	mov r0, #0x1
	mov r1, #0x1a
	mov r3, #0x13
	bl FUN_0200A86C
	ldr r1, _0207E490 ; =0x00000282
	mov r2, #0x1a
	lsl r2, r2, #0x6
	ldrb r1, [r4, r1]
	ldr r2, [r4, r2]
	add r5, r0, #0x0
	bl FUN_0200A8E0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E484 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x70
	mov r3, #0x0
	bl FUN_0207D998
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x40
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x50
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x60
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x70
	bl FUN_02019220
	add sp, #0x18
	pop {r3-r5, pc}
	nop
_0207E484: .word 0x00010200
_0207E488: .word 0x0000027A
_0207E48C: .word 0x0000027E
_0207E490: .word 0x00000282
_0207E494: .word 0x0000067C
_0207E498: .word 0x00000674
_0207E49C: .word 0x0000022A

	thumb_func_start FUN_0207E4A0
FUN_0207E4A0: ; 0x0207E4A0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, #0x34
	bl FUN_02019220
	mov r0, #0x59
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x3
	beq _0207E4C6
	cmp r0, #0x4
	bne _0207E580
_0207E4C6:
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	ldr r2, _0207E584 ; =0x00000674
	mov r1, #0xa5
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E588 ; =0x000F0E00
	add r0, r4, #0x0
	add r1, #0x10
	mov r3, #0x0
	bl FUN_0207D998
	ldr r1, _0207E58C ; =0x0000029B
	ldr r2, _0207E584 ; =0x00000674
	ldrb r1, [r4, r1]
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	add r1, #0xa6
	bl FUN_0200A8E0
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E590 ; =0x00010200
	mov r1, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x91
	mov r2, #0x1a
	str r1, [sp, #0xc]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	lsl r2, r2, #0x6
	ldr r2, [r4, r2]
	add r0, #0x10
	add r3, r1, #0x0
	bl FUN_0201BDE0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_02019220
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldrb r1, [r1, #0x12]
	cmp r1, #0x3
	bne _0207E580
	sub r0, #0x8
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02019620
	ldr r2, _0207E584 ; =0x00000674
	mov r1, #0xa3
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E588 ; =0x000F0E00
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_0207D998
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0207CFAC
_0207E580:
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0207E584: .word 0x00000674
_0207E588: .word 0x000F0E00
_0207E58C: .word 0x0000029B
_0207E590: .word 0x00010200

	thumb_func_start FUN_0207E594
FUN_0207E594: ; 0x0207E594
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x44
	bl FUN_02019220
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207E5B4
	add r0, r4, #0x0
	mov r1, #0x9b
	bl FUN_0207D924
	b _0207E5BC
_0207E5B4:
	add r0, r4, #0x0
	mov r1, #0x81
	bl FUN_0207D924
_0207E5BC:
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x20
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207EA44
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207EA44
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0207EA44
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_0207EA44
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FUN_02019220
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207E650
FUN_0207E650: ; 0x0207E650
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x54
	bl FUN_02019220
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x2
	bne _0207E670
	add r0, r4, #0x0
	mov r1, #0x9f
	bl FUN_0207D924
	b _0207E678
_0207E670:
	add r0, r4, #0x0
	mov r1, #0x9e
	bl FUN_0207D924
_0207E678:
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x20
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0207EA44
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0207EA44
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0207EA44
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_0207EA44
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FUN_02019220
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207E70C
FUN_0207E70C: ; 0x0207E70C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x7d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x79
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r2, _0207E780 ; =0x00000699
	add r0, r4, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0xb7
	mov r3, #0x3
	bl FUN_0207DA48
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E784 ; =0x00010200
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_0207D998
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02019220
	ldr r0, _0207E780 ; =0x00000699
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	beq _0207E77A
	add r0, r4, #0x0
	mov r1, #0xb4
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
_0207E77A:
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_0207E780: .word 0x00000699
_0207E784: .word 0x00010200

	thumb_func_start FUN_0207E788
FUN_0207E788: ; 0x0207E788
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	mov r0, #0x71
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_02019220
	add r0, r4, #0x0
	mov r1, #0xa1
	bl FUN_0207D924
	mov r1, #0x8d
	lsl r1, r1, #0x2
	add r0, r4, #0x0
	add r1, r4, r1
	bl FUN_0207CFAC
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x12]
	cmp r0, #0x3
	beq _0207E7BC
	cmp r0, #0x4
	bne _0207E82C
_0207E7BC:
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	ldr r2, _0207E830 ; =0x00000674
	mov r1, #0xa5
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207E834 ; =0x000F0E00
	add r0, r4, #0x0
	add r1, #0x10
	mov r3, #0x0
	bl FUN_0207D998
	ldr r1, _0207E838 ; =0x0000029B
	ldr r2, _0207E830 ; =0x00000674
	ldrb r1, [r4, r1]
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	add r1, #0xa6
	bl FUN_0200A8E0
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E83C ; =0x00010200
	mov r1, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x91
	mov r2, #0x1a
	str r1, [sp, #0xc]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	lsl r2, r2, #0x6
	ldr r2, [r4, r2]
	add r0, #0x10
	add r3, r1, #0x0
	bl FUN_0201BDE0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x10
	bl FUN_02019220
_0207E82C:
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_0207E830: .word 0x00000674
_0207E834: .word 0x000F0E00
_0207E838: .word 0x0000029B
_0207E83C: .word 0x00010200

	thumb_func_start FUN_0207E840
FUN_0207E840: ; 0x0207E840
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x0
	add r0, #0x10
	bl FUN_02019620
	ldr r0, _0207E994 ; =0x00000674
	mov r1, #0xba
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x0
	add r4, r0, #0x0
	ldr r2, _0207E998 ; =0x0000067C
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, r2]
	add r2, #0x1d
	ldrb r2, [r5, r2]
	mov r3, #0x3
	bl FUN_0200AD38
	ldr r1, _0207E998 ; =0x0000067C
	add r2, r4, #0x0
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r5, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x38
	sub r0, r0, r1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	mov r1, #0x0
	mov r2, #0x1a
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E99C ; =0x00010200
	lsl r2, r2, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x91
	str r1, [sp, #0xc]
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	add r0, #0x10
	add r3, r4, #0x0
	bl FUN_0201BDE0
	ldr r0, _0207E994 ; =0x00000674
	mov r1, #0xb9
	ldr r0, [r5, r0]
	bl FUN_0200A914
	add r6, r0, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r0, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r0, r4, r0
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E99C ; =0x00010200
	add r2, r6, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x91
	str r1, [sp, #0xc]
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r3, r4, #0x0
	add r0, #0x10
	bl FUN_0201BDE0
	add r0, r6, #0x0
	bl FUN_02021A20
	ldr r0, _0207E994 ; =0x00000674
	mov r1, #0xb8
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x0
	ldr r2, _0207E998 ; =0x0000067C
	add r6, r0, #0x0
	add r3, r2, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, r2]
	add r2, #0x1c
	add r3, #0x1b
	ldrb r2, [r5, r2]
	ldrb r3, [r5, r3]
	lsl r2, r2, #0x2
	add r2, r3, r2
	add r2, r2, #0x1
	mov r3, #0x3
	bl FUN_0200AD38
	ldr r1, _0207E998 ; =0x0000067C
	add r2, r6, #0x0
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	bl FUN_0200B7B8
	add r0, r6, #0x0
	bl FUN_02021A20
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r5, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r0, r4, r0
	lsl r0, r0, #0x18
	mov r1, #0x0
	lsr r3, r0, #0x18
	mov r2, #0x1a
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207E99C ; =0x00010200
	lsl r2, r2, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x91
	str r1, [sp, #0xc]
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	add r0, #0x10
	bl FUN_0201BDE0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x10
	bl FUN_02019220
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0207E994: .word 0x00000674
_0207E998: .word 0x0000067C
_0207E99C: .word 0x00010200

	thumb_func_start FUN_0207E9A0
FUN_0207E9A0: ; 0x0207E9A0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x20
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x30
	bl FUN_02019620
	ldr r0, _0207EA34 ; =0x0000069A
	mov r1, #0x3
	ldrb r0, [r4, r0]
	bl FUN_0207FC5C
	ldr r2, _0207EA38 ; =0x00000678
	add r1, r0, #0x0
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207EA3C ; =0x000F0E00
	add r0, r4, #0x0
	add r1, #0x20
	mov r3, #0x0
	bl FUN_0207D998
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, _0207EA34 ; =0x0000069A
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x20]
	bl FUN_0207FCC0
	ldr r2, _0207EA38 ; =0x00000678
	add r1, r0, #0x0
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	ldr r2, _0207EA40 ; =0x00010200
	add r0, r4, #0x0
	add r1, #0x30
	mov r3, #0x0
	bl FUN_0207D998
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x20
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x30
	bl FUN_02019220
	pop {r4, pc}
	.balign 4
_0207EA34: .word 0x0000069A
_0207EA38: .word 0x00000678
_0207EA3C: .word 0x000F0E00
_0207EA40: .word 0x00010200

	thumb_func_start FUN_0207EA44
FUN_0207EA44: ; 0x0207EA44
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	mov r0, #0x91
	add r7, r1, #0x0
	lsl r0, r0, #0x2
	lsl r6, r7, #0x4
	ldr r4, [r5, r0]
	cmp r7, #0x4
	beq _0207EA76
	lsl r1, r7, #0x1
	add r2, r5, r1
	add r1, r0, #0x0
	add r1, #0x40
	ldrh r1, [r2, r1]
	add r2, r0, #0x0
	add r2, #0x48
	str r1, [sp, #0x20]
	add r1, r5, r7
	ldrb r2, [r1, r2]
	add r0, #0x4c
	str r2, [sp, #0x1c]
	ldrb r0, [r1, r0]
	str r0, [sp, #0x18]
	b _0207EA88
_0207EA76:
	add r0, #0x8
	ldr r0, [r5, r0]
	mov r1, #0x0
	ldrh r0, [r0, #0x18]
	str r0, [sp, #0x20]
	bl FUN_0206AB30
	str r0, [sp, #0x1c]
	str r0, [sp, #0x18]
_0207EA88:
	ldr r2, _0207EB54 ; =0x00000688
	ldr r1, [sp, #0x20]
	ldr r0, [r5, r2]
	sub r2, #0x8
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207EB58 ; =0x000F0E00
	mov r2, #0x1a
	str r0, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r2, [r5, r2]
	add r0, r4, r6
	mov r3, #0x1
	bl FUN_0201BDE0
	ldr r0, [sp, #0x20]
	ldr r2, _0207EB5C ; =0x00000674
	cmp r0, #0x0
	beq _0207EB10
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	mov r1, #0x87
	bl FUN_0200A8E0
	mov r3, #0x10
	mov r2, #0x1a
	str r3, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207EB60 ; =0x00010200
	mov r1, #0x0
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r2, [r5, r2]
	add r0, r4, r6
	bl FUN_0201BDE0
	add r0, r7, #0x0
	add r0, #0x8d
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x18]
	add r7, #0x88
	str r0, [sp, #0x8]
	mov r0, #0x2
	str r0, [sp, #0xc]
	mov r0, #0x3c
	str r0, [sp, #0x10]
	mov r0, #0x10
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	mov r2, #0x75
	add r3, r7, #0x0
	bl FUN_0207DA94
	add sp, #0x24
	pop {r4-r7, pc}
_0207EB10:
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	mov r1, #0x99
	bl FUN_0200A8E0
	mov r1, #0x1a
	lsl r1, r1, #0x6
	mov r0, #0x0
	ldr r1, [r5, r1]
	add r2, r0, #0x0
	bl FUN_02002E14
	add r3, r0, #0x0
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207EB60 ; =0x00010200
	mov r2, #0x1a
	str r0, [sp, #0x8]
	mov r1, #0x0
	add r0, r4, r6
	lsr r4, r3, #0x1
	mov r3, #0x3c
	str r1, [sp, #0xc]
	lsl r2, r2, #0x6
	ldr r2, [r5, r2]
	sub r3, r3, r4
	bl FUN_0201BDE0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0207EB54: .word 0x00000688
_0207EB58: .word 0x000F0E00
_0207EB5C: .word 0x00000674
_0207EB60: .word 0x00010200

	thumb_func_start FUN_0207EB64
FUN_0207EB64: ; 0x0207EB64
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x65
	lsl r0, r0, #0x2
	add r0, r5, r0
	add r4, r1, #0x0
	bl FUN_02019220
	mov r0, #0x69
	lsl r0, r0, #0x2
	add r0, r5, r0
	bl FUN_02019220
	mov r0, #0x6d
	lsl r0, r0, #0x2
	add r0, r5, r0
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x0
	add r0, #0x50
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x0
	add r0, #0x60
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x0
	add r0, #0x70
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0206AB18
	add r2, r0, #0x0
	cmp r2, #0x1
	bhi _0207EBD2
	ldr r2, _0207EC88 ; =0x00000674
	mov r1, #0x9a
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	b _0207EBE0
_0207EBD2:
	mov r0, #0x1
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x96
	mov r3, #0x3
	bl FUN_0207DA48
_0207EBE0:
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldr r2, _0207EC8C ; =0x00010200
	add r0, r5, #0x0
	add r1, #0x50
	mov r3, #0x2
	bl FUN_0207D998
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_0206AB18
	add r2, r0, #0x0
	bne _0207EC0E
	ldr r2, _0207EC88 ; =0x00000674
	mov r1, #0x9a
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	b _0207EC1C
_0207EC0E:
	mov r0, #0x1
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	mov r1, #0x97
	mov r3, #0x3
	bl FUN_0207DA48
_0207EC1C:
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldr r2, _0207EC8C ; =0x00010200
	add r0, r5, #0x0
	add r1, #0x60
	mov r3, #0x2
	bl FUN_0207D998
	ldr r2, _0207EC90 ; =0x0000024B
	mov r0, #0x1
	mov r1, #0x1a
	mov r3, #0x13
	bl FUN_0200A86C
	mov r2, #0x1a
	lsl r2, r2, #0x6
	ldr r2, [r5, r2]
	add r1, r4, #0x0
	add r6, r0, #0x0
	bl FUN_0200A8E0
	mov r1, #0x91
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	ldr r2, _0207EC8C ; =0x00010200
	add r0, r5, #0x0
	add r1, #0x70
	mov r3, #0x0
	bl FUN_0207D998
	add r0, r6, #0x0
	bl FUN_0200A8B8
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x60
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x70
	bl FUN_02019220
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_0207EC88: .word 0x00000674
_0207EC8C: .word 0x00010200
_0207EC90: .word 0x0000024B

	thumb_func_start FUN_0207EC94
FUN_0207EC94: ; 0x0207EC94
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x65
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x69
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x6d
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x50
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x60
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x70
	bl FUN_0201958C
	pop {r4, pc}

	thumb_func_start FUN_0207ECDC
FUN_0207ECDC: ; 0x0207ECDC
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldrh r1, [r1, #0x18]
	cmp r1, #0x0
	beq _0207ED0E
	sub r0, #0x8
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r0, #0x40
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_0207EA44
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x40
	bl FUN_02019220
	pop {r4, pc}
_0207ED0E:
	sub r0, #0xc8
	add r0, r4, r0
	bl FUN_02019220
	pop {r4, pc}

	thumb_func_start FUN_0207ED18
FUN_0207ED18: ; 0x0207ED18
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x61
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	bl FUN_0201AC68
	pop {r4, pc}

	thumb_func_start FUN_0207ED30
FUN_0207ED30: ; 0x0207ED30
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldr r0, _0207EDB0 ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x4
	add r0, r1, r0
	mov r1, #0x0
	bl FUN_02019620
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldr r0, _0207EDB0 ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x4
	add r0, r1, r0
	mov r1, #0x0
	bl FUN_02019620
	ldr r1, _0207EDB0 ; =0x0000068D
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FUN_0207EA44
	ldr r1, _0207EDB0 ; =0x0000068D
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	bl FUN_0207EA44
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldr r0, _0207EDB0 ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x4
	add r0, r1, r0
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	ldr r0, _0207EDB0 ; =0x0000068D
	ldrb r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x4
	add r0, r1, r0
	bl FUN_02019220
	pop {r4, pc}
	nop
_0207EDB0: .word 0x0000068D

	thumb_func_start FUN_0207EDB4
FUN_0207EDB4: ; 0x0207EDB4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0207EE20 ; =0x0000068C
	ldrsb r0, [r5, r0]
	cmp r0, #0x3
	bne _0207EDEE
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x60
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x70
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r4, [r5, r0]
	add r4, #0x70
	b _0207EDF6
_0207EDEE:
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r4, [r5, r0]
	add r4, #0x50
_0207EDF6:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02019620
	ldr r2, _0207EE24 ; =0x00000674
	mov r1, #0x9c
	ldr r0, [r5, r2]
	add r2, #0xc
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	ldr r2, _0207EE28 ; =0x00010200
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_0207D998
	add r0, r4, #0x0
	bl FUN_02019220
	pop {r3-r5, pc}
	.balign 4
_0207EE20: .word 0x0000068C
_0207EE24: .word 0x00000674
_0207EE28: .word 0x00010200

	thumb_func_start FUN_0207EE2C
FUN_0207EE2C: ; 0x0207EE2C
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r4, r1, #0x0
	add r0, #0x50
	mov r1, #0x0
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0xa
	bl FUN_0206AB18
	bl FUN_0208315C
	add r4, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0xc5
	mov r3, #0x13
	bl FUN_0200A86C
	mov r2, #0x1a
	lsl r2, r2, #0x6
	ldr r2, [r5, r2]
	add r1, r4, #0x0
	add r6, r0, #0x0
	bl FUN_0200A8E0
	mov r1, #0x0
	mov r2, #0x1a
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207EEAC ; =0x00010200
	lsl r2, r2, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x91
	str r1, [sp, #0xc]
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	add r0, #0x50
	add r3, r1, #0x0
	bl FUN_0201BDE0
	add r0, r6, #0x0
	bl FUN_0200A8B8
	mov r0, #0x75
	lsl r0, r0, #0x2
	add r0, r5, r0
	bl FUN_02019220
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r0, #0x50
	bl FUN_02019220
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0207EEAC: .word 0x00010200

	thumb_func_start FUN_0207EEB0
FUN_0207EEB0: ; 0x0207EEB0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x75
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0201958C
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r0, #0x50
	bl FUN_0201958C
	pop {r4, pc}

	thumb_func_start FUN_0207EECC
FUN_0207EECC: ; 0x0207EECC
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	cmp r1, #0x4
	bgt _0207EEF0
	cmp r1, #0x0
	blt _0207EF0E
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207EEE6: ; jump table (using 16-bit offset)
	.short _0207EEF6 - _0207EEE6 - 2; case 0
	.short _0207EEFA - _0207EEE6 - 2; case 1
	.short _0207EEFE - _0207EEE6 - 2; case 2
	.short _0207EF02 - _0207EEE6 - 2; case 3
	.short _0207EF06 - _0207EEE6 - 2; case 4
_0207EEF0:
	cmp r1, #0xfe
	beq _0207EF0A
	b _0207EF0E
_0207EEF6:
	mov r5, #0xac
	b _0207EF10
_0207EEFA:
	mov r5, #0xae
	b _0207EF10
_0207EEFE:
	mov r5, #0xaf
	b _0207EF10
_0207EF02:
	mov r5, #0xb0
	b _0207EF10
_0207EF06:
	mov r5, #0xad
	b _0207EF10
_0207EF0A:
	mov r5, #0xb1
	b _0207EF10
_0207EF0E:
	mov r5, #0xb2
_0207EF10:
	mov r0, #0x91
	lsl r0, r0, #0x2
	ldr r6, [r4, r0]
	ldr r2, _0207EF60 ; =0x000003E2
	add r6, #0x20
	add r0, r6, #0x0
	mov r1, #0x1
	mov r3, #0xd
	bl FUN_0200D0BC
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02019620
	ldr r2, _0207EF64 ; =0x00000674
	add r1, r5, #0x0
	ldr r0, [r4, r2]
	add r2, #0xc
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r3, #0x0
	mov r2, #0x1a
	str r3, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0207EF68 ; =0x0001020F
	lsl r2, r2, #0x6
	str r0, [sp, #0x8]
	str r3, [sp, #0xc]
	ldr r2, [r4, r2]
	add r0, r6, #0x0
	mov r1, #0x1
	bl FUN_0201BDE0
	add r0, r6, #0x0
	bl FUN_02019220
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0207EF60: .word 0x000003E2
_0207EF64: .word 0x00000674
_0207EF68: .word 0x0001020F

	thumb_func_start FUN_0207EF6C
FUN_0207EF6C: ; 0x0207EF6C
	push {r3-r4, lr}
	sub sp, #0x4
	bl FUN_020BB7F4
	bl G3X_Init
	bl G3X_InitMtxStack
	ldr r0, _0207EFEC ; =0x04000060
	ldr r1, _0207EFF0 ; =0xFFFFCFFD
	ldrh r2, [r0, #0x0]
	ldr r3, _0207EFF4 ; =0x0000CFFB
	and r2, r1
	strh r2, [r0, #0x0]
	ldrh r2, [r0, #0x0]
	and r2, r3
	strh r2, [r0, #0x0]
	add r2, r1, #0x2
	ldrh r4, [r0, #0x0]
	add r1, r1, #0x2
	sub r3, #0x1c
	and r4, r2
	mov r2, #0x8
	orr r2, r4
	strh r2, [r0, #0x0]
	ldrh r2, [r0, #0x0]
	and r2, r1
	mov r1, #0x10
	orr r1, r2
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	and r1, r3
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl G3X_SetFog
	mov r0, #0x0
	ldr r2, _0207EFF8 ; =0x00007FFF
	add r1, r0, #0x0
	mov r3, #0x3f
	str r0, [sp, #0x0]
	bl G3X_SetClearColor
	ldr r1, _0207EFFC ; =0x04000540
	mov r0, #0x0
	str r0, [r1, #0x0]
	ldr r0, _0207F000 ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0201E6E4
	ldr r1, _0207F004 ; =0x04000008
	mov r0, #0x3
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x2
	orr r0, r2
	strh r0, [r1, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0207EFEC: .word 0x04000060
_0207EFF0: .word 0xFFFFCFFD
_0207EFF4: .word 0x0000CFFB
_0207EFF8: .word 0x00007FFF
_0207EFFC: .word 0x04000540
_0207F000: .word 0xBFFF0000
_0207F004: .word 0x04000008

	thumb_func_start FUN_0207F008
FUN_0207F008: ; 0x0207F008
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0207F05C ; =0x0000068C
	ldrsb r0, [r4, r0]
	cmp r0, #0x4
	bne _0207F046
	bl FUN_020222AC
	bl FUN_0201EBA4
	ldr r2, _0207F060 ; =0x04000440
	mov r3, #0x0
	add r1, r2, #0x0
	str r3, [r2, #0x0]
	add r1, #0x14
	str r3, [r1, #0x0]
	mov r0, #0x2
	str r0, [r2, #0x0]
	str r3, [r1, #0x0]
	bl FUN_020B849C
	mov r0, #0xb7
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0207F108
	bl FUN_020B849C
	add r0, r4, #0x0
	bl FUN_0207F1A4
_0207F046:
	bl FUN_020B02C8
	mov r0, #0xae
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02006ED4
	ldr r0, _0207F064 ; =0x04000540
	mov r1, #0x1
	str r1, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_0207F05C: .word 0x0000068C
_0207F060: .word 0x04000440
_0207F064: .word 0x04000540

	thumb_func_start FUN_0207F068
FUN_0207F068: ; 0x0207F068
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xad
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0201EB70
	mov r0, #0x2d
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02014D9C
	mov r0, #0x2d
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02014C28
	mov r0, #0xae
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020072E8
	pop {r4, pc}

	thumb_func_start FUN_0207F098
FUN_0207F098: ; 0x0207F098
	push {r3-r4, lr}
	sub sp, #0x1c
	ldr r3, _0207F100 ; =0x020FB5CC
	add r4, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x10
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, sp, #0x8
	str r0, [r2, #0x0]
	mov r0, #0x0
	strh r0, [r1, #0x0]
	strh r0, [r1, #0x2]
	strh r0, [r1, #0x4]
	strh r0, [r1, #0x6]
	mov r0, #0x13
	bl FUN_0201EB64
	mov r1, #0xad
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r2, #0x1
	str r2, [sp, #0x0]
	ldr r0, [r4, r1]
	lsl r1, r2, #0x10
	str r0, [sp, #0x4]
	ldr r3, _0207F104 ; =0x000005C1
	add r0, sp, #0x10
	add r2, sp, #0x8
	bl FUN_0201ED10
	mov r2, #0xad
	lsl r2, r2, #0x2
	mov r1, #0x19
	ldr r2, [r4, r2]
	mov r0, #0x0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	mov r0, #0xad
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0201EC88
	mov r0, #0xad
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0201EB8C
	add sp, #0x1c
	pop {r3-r4, pc}
	nop
_0207F100: .word 0x020FB5CC
_0207F104: .word 0x000005C1

	thumb_func_start FUN_0207F108
FUN_0207F108: ; 0x0207F108
	push {r4-r7}
	add r4, r0, #0x0
	ldr r0, _0207F170 ; =0x121400C0
	ldr r1, _0207F174 ; =0x040004A4
	ldr r2, _0207F178 ; =0x00003FE8
	str r0, [r1, #0x0]
	mov r0, #0x1
	str r0, [r1, #0x5c]
	ldr r0, _0207F17C ; =0x0400048C
	mov r3, #0x0
	sub r1, #0x24
_0207F11E:
	str r2, [r1, #0x0]
	ldrh r7, [r4, #0x2]
	ldrh r5, [r4, #0x0]
	ldrh r6, [r4, #0x4]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0, #0x0]
	str r6, [r0, #0x0]
	str r2, [r1, #0x0]
	ldrh r7, [r4, #0x8]
	ldrh r5, [r4, #0x6]
	ldrh r6, [r4, #0xa]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0, #0x0]
	str r6, [r0, #0x0]
	str r2, [r1, #0x0]
	ldrh r7, [r4, #0x14]
	ldrh r5, [r4, #0x12]
	ldrh r6, [r4, #0x16]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0, #0x0]
	str r6, [r0, #0x0]
	str r2, [r1, #0x0]
	ldrh r7, [r4, #0xe]
	ldrh r5, [r4, #0xc]
	ldrh r6, [r4, #0x10]
	lsl r7, r7, #0x10
	orr r5, r7
	str r5, [r0, #0x0]
	add r3, r3, #0x1
	add r4, #0x18
	str r6, [r0, #0x0]
	cmp r3, #0x4
	blo _0207F11E
	ldr r0, _0207F180 ; =0x04000504
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r4-r7}
	bx lr
	.balign 4
_0207F170: .word 0x121400C0
_0207F174: .word 0x040004A4
_0207F178: .word 0x00003FE8
_0207F17C: .word 0x0400048C
_0207F180: .word 0x04000504

	thumb_func_start FUN_0207F184
FUN_0207F184: ; 0x0207F184
	mov r2, #0x0
	ldrsh r3, [r0, r2]
	ldrsh r2, [r1, r2]
	add r2, r3, r2
	strh r2, [r0, #0x0]
	mov r2, #0x2
	ldrsh r3, [r0, r2]
	ldrsh r2, [r1, r2]
	add r2, r3, r2
	strh r2, [r0, #0x2]
	mov r2, #0x4
	ldrsh r3, [r0, r2]
	ldrsh r1, [r1, r2]
	add r1, r3, r1
	strh r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0207F1A4
FUN_0207F1A4: ; 0x0207F1A4
	push {r3-r7, lr}
	sub sp, #0x18
	mov r2, #0xff
	lsl r2, r2, #0x2
	add r1, r0, #0x0
	ldr r1, [r1, r2]
	str r0, [sp, #0x0]
	cmp r1, #0x4
	bne _0207F1BE
	bl FUN_0207D598
	add sp, #0x18
	pop {r3-r7, pc}
_0207F1BE:
	cmp r1, #0x3
	bne _0207F1EA
	add r6, r0, #0x0
	add r7, r2, #0x0
	mov r0, #0xb7
	mov r5, #0x0
	sub r7, #0x60
	lsl r0, r0, #0x2
_0207F1CE:
	add r4, r6, r7
	add r3, r6, r0
	mov r2, #0xc
_0207F1D4:
	ldrh r1, [r4, #0x0]
	add r4, r4, #0x2
	strh r1, [r3, #0x0]
	add r3, r3, #0x2
	sub r2, r2, #0x1
	bne _0207F1D4
	add r5, r5, #0x1
	add r6, #0x18
	cmp r5, #0x4
	blo _0207F1CE
	b _0207F274
_0207F1EA:
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r2, #0xc0
	add r0, r0, r2
	str r0, [sp, #0x14]
	mov r0, #0xb7
	lsl r0, r0, #0x2
	ldr r1, [sp, #0x0]
	add r2, r0, #0x0
	add r1, r1, r0
	str r1, [sp, #0x10]
	ldr r1, [sp, #0x0]
	add r2, #0x66
	add r1, r1, r2
	str r1, [sp, #0xc]
	ldr r1, [sp, #0x0]
	add r2, r0, #0x6
	add r1, r1, r2
	str r1, [sp, #0x8]
	add r2, r0, #0x0
	ldr r1, [sp, #0x0]
	add r2, #0x6c
	add r7, r1, r2
	add r2, r0, #0x0
	add r2, #0xc
	add r6, r1, r2
	add r2, r0, #0x0
	add r2, #0x72
	add r0, #0x12
	add r4, r1, r2
	add r5, r1, r0
_0207F22A:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	bl FUN_0207F184
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	bl FUN_0207F184
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_0207F184
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0207F184
	ldr r0, [sp, #0x14]
	add r7, #0x18
	add r0, #0x18
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r6, #0x18
	add r0, #0x18
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r4, #0x18
	add r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r5, #0x18
	add r0, #0x18
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	cmp r0, #0x4
	blo _0207F22A
_0207F274:
	mov r1, #0xff
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	str r2, [r0, r1]
	ldr r0, [r0, r1]
	cmp r0, #0x4
	bne _0207F294
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	bl FUN_0207D418
	add sp, #0x18
	pop {r3-r7, pc}
_0207F294:
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	bl FUN_0207D418
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_0207F2A0
FUN_0207F2A0: ; 0x0207F2A0
	push {r3-r7, lr}
	sub sp, #0x18
	ldr r1, _0207F420 ; =0x0000068C
	ldrsb r1, [r0, r1]
	cmp r1, #0x4
	beq _0207F2AE
	b _0207F41A
_0207F2AE:
	ldr r7, _0207F424 ; =0x020FB60C
	add r3, sp, #0x0
	ldrh r1, [r7, #0x8]
	strh r1, [r3, #0x12]
	ldrh r1, [r7, #0xa]
	strh r1, [r3, #0x14]
	ldrh r1, [r7, #0xc]
	strh r1, [r3, #0x16]
	mov r1, #0xb7
	lsl r1, r1, #0x2
	ldrh r5, [r3, #0x12]
	add r2, r1, #0x2
	strh r5, [r0, r1]
	ldrh r4, [r3, #0x14]
	strh r4, [r0, r2]
	ldrh r6, [r3, #0x16]
	add r2, r1, #0x4
	strh r6, [r0, r2]
	add r2, r1, #0x6
	strh r5, [r0, r2]
	add r2, r1, #0x0
	add r2, #0x8
	strh r4, [r0, r2]
	add r2, r1, #0x0
	add r2, #0xa
	strh r6, [r0, r2]
	add r2, r1, #0x0
	add r2, #0xc
	strh r5, [r0, r2]
	add r2, r1, #0x0
	add r2, #0xe
	strh r4, [r0, r2]
	add r2, r1, #0x0
	add r2, #0x10
	strh r6, [r0, r2]
	add r2, r1, #0x0
	add r2, #0x12
	strh r5, [r0, r2]
	add r2, r1, #0x0
	add r2, #0x14
	strh r4, [r0, r2]
	add r2, r1, #0x0
	add r2, #0x16
	strh r6, [r0, r2]
	ldrh r2, [r7, #0x3e]
	ldr r6, _0207F428 ; =0x020FB64C
	add r7, r1, #0x0
	strh r2, [r3, #0xc]
	ldrh r2, [r6, #0x0]
	add r7, #0x1c
	strh r2, [r3, #0xe]
	ldrh r2, [r6, #0x2]
	strh r2, [r3, #0x10]
	add r2, r1, #0x0
	ldrh r5, [r3, #0xc]
	add r2, #0x18
	strh r5, [r0, r2]
	add r2, r1, #0x0
	ldrh r4, [r3, #0xe]
	add r2, #0x1a
	strh r4, [r0, r2]
	ldrh r2, [r3, #0x10]
	strh r2, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x1e
	strh r5, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x20
	strh r4, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x22
	strh r2, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x24
	strh r5, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x26
	strh r4, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x28
	strh r2, [r0, r7]
	add r7, r1, #0x0
	add r7, #0x2a
	strh r5, [r0, r7]
	add r5, r1, #0x0
	add r5, #0x2c
	strh r4, [r0, r5]
	add r4, r1, #0x0
	add r4, #0x2e
	strh r2, [r0, r4]
	ldrh r2, [r6, #0x34]
	strh r2, [r3, #0x6]
	ldrh r2, [r6, #0x36]
	strh r2, [r3, #0x8]
	ldrh r2, [r6, #0x38]
	add r6, r1, #0x0
	add r6, #0x34
	strh r2, [r3, #0xa]
	add r2, r1, #0x0
	ldrh r5, [r3, #0x6]
	add r2, #0x30
	strh r5, [r0, r2]
	add r2, r1, #0x0
	ldrh r4, [r3, #0x8]
	add r2, #0x32
	strh r4, [r0, r2]
	ldrh r2, [r3, #0xa]
	strh r2, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x36
	strh r5, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x38
	strh r4, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x3a
	strh r2, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x3c
	strh r5, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x3e
	strh r4, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x40
	strh r2, [r0, r6]
	add r6, r1, #0x0
	add r6, #0x42
	strh r5, [r0, r6]
	add r5, r1, #0x0
	add r5, #0x44
	strh r4, [r0, r5]
	add r4, r1, #0x0
	add r4, #0x46
	strh r2, [r0, r4]
	ldr r2, _0207F42C ; =0x020FB68C
	ldrh r4, [r2, #0x2a]
	strh r4, [r3, #0x0]
	ldrh r4, [r2, #0x2c]
	strh r4, [r3, #0x2]
	ldrh r2, [r2, #0x2e]
	strh r2, [r3, #0x4]
	add r2, r1, #0x0
	ldrh r5, [r3, #0x0]
	add r2, #0x48
	strh r5, [r0, r2]
	add r2, r1, #0x0
	ldrh r4, [r3, #0x2]
	add r2, #0x4a
	strh r4, [r0, r2]
	ldrh r2, [r3, #0x4]
	add r3, r1, #0x0
	add r3, #0x4c
	strh r2, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x4e
	strh r5, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x50
	strh r4, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x52
	strh r2, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x54
	strh r5, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x56
	strh r4, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x58
	strh r2, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x5a
	strh r5, [r0, r3]
	add r3, r1, #0x0
	add r3, #0x5c
	strh r4, [r0, r3]
	add r1, #0x5e
	strh r2, [r0, r1]
	bl FUN_0207F608
_0207F41A:
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_0207F420: .word 0x0000068C
_0207F424: .word 0x020FB60C
_0207F428: .word 0x020FB64C
_0207F42C: .word 0x020FB68C

	thumb_func_start FUN_0207F430
FUN_0207F430: ; 0x0207F430
	push {r4-r5}
	cmp r2, #0xff
	bne _0207F446
	ldrh r2, [r0, #0x0]
	strh r2, [r1, #0x0]
	ldrh r2, [r0, #0x2]
	strh r2, [r1, #0x2]
	ldrh r0, [r0, #0x4]
	strh r0, [r1, #0x4]
	pop {r4-r5}
	bx lr
_0207F446:
	cmp r2, #0x0
	bne _0207F45A
	ldrh r2, [r0, #0x6]
	strh r2, [r1, #0x0]
	ldrh r2, [r0, #0x8]
	strh r2, [r1, #0x2]
	ldrh r0, [r0, #0xa]
	strh r0, [r1, #0x4]
	pop {r4-r5}
	bx lr
_0207F45A:
	mov r3, #0x6
	ldrsh r5, [r0, r3]
	mov r3, #0xc
	ldrsh r3, [r0, r3]
	add r4, r3, #0x0
	mul r4, r2
	add r3, r5, r4
	strh r3, [r1, #0x0]
	mov r3, #0x8
	ldrsh r5, [r0, r3]
	mov r3, #0xe
	ldrsh r3, [r0, r3]
	add r4, r3, #0x0
	mul r4, r2
	add r3, r5, r4
	strh r3, [r1, #0x2]
	mov r3, #0xa
	ldrsh r4, [r0, r3]
	mov r3, #0x10
	ldrsh r0, [r0, r3]
	mul r2, r0
	add r0, r4, r2
	strh r0, [r1, #0x4]
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_0207F48C
FUN_0207F48C: ; 0x0207F48C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x0
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r0]
	add r6, r2, #0x0
	sub r7, r1, r0
	add r0, r7, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	mov r1, #0x0
	bl _fgr
	bls _0207F4E0
	add r0, r7, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	add r1, r0, #0x0
	ldr r0, _0207F600 ; =0x45800000
	bl _fmul
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	bl _ffix
	b _0207F506
_0207F4E0:
	add r0, r7, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	add r1, r0, #0x0
	ldr r0, _0207F600 ; =0x45800000
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	bl _ffix
_0207F506:
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	strh r0, [r6, #0x0]
	mov r0, #0x2
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r0]
	sub r7, r1, r0
	add r0, r7, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	mov r1, #0x0
	bl _fgr
	bls _0207F558
	add r0, r7, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	add r1, r0, #0x0
	ldr r0, _0207F600 ; =0x45800000
	bl _fmul
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	bl _ffix
	b _0207F57E
_0207F558:
	add r0, r7, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	add r1, r0, #0x0
	ldr r0, _0207F600 ; =0x45800000
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	bl _ffix
_0207F57E:
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	strh r0, [r6, #0x2]
	mov r0, #0x4
	ldrsh r1, [r4, r0]
	ldrsh r0, [r5, r0]
	sub r4, r1, r0
	add r0, r4, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	mov r1, #0x0
	bl _fgr
	bls _0207F5D0
	add r0, r4, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	add r1, r0, #0x0
	ldr r0, _0207F600 ; =0x45800000
	bl _fmul
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	bl _ffix
	b _0207F5F6
_0207F5D0:
	add r0, r4, #0x0
	bl _fflt
	ldr r1, _0207F600 ; =0x45800000
	bl _fdiv
	ldr r1, _0207F604 ; =0x40800000
	bl _fdiv
	add r1, r0, #0x0
	ldr r0, _0207F600 ; =0x45800000
	bl _fmul
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
	bl _ffix
_0207F5F6:
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	strh r0, [r6, #0x4]
	pop {r3-r7, pc}
	nop
_0207F600: .word 0x45800000
_0207F604: .word 0x40800000

	thumb_func_start FUN_0207F608
FUN_0207F608: ; 0x0207F608
	push {r3-r7, lr}
	sub sp, #0x28
	ldr r2, _0207F7D0 ; =0x00000295
	add r5, r0, #0x0
	mov r1, #0xe7
	lsl r1, r1, #0x2
	ldrb r2, [r5, r2]
	ldr r0, _0207F7D4 ; =0x020FB5D8
	add r1, r5, r1
	bl FUN_0207F430
	ldr r2, _0207F7D8 ; =0x00000296
	ldr r1, _0207F7DC ; =0x000003A2
	ldrb r2, [r5, r2]
	ldr r0, _0207F7E0 ; =0x020FB5EA
	add r1, r5, r1
	bl FUN_0207F430
	ldr r2, _0207F7E4 ; =0x00000297
	ldr r1, _0207F7E8 ; =0x000003AE
	ldrb r2, [r5, r2]
	ldr r0, _0207F7EC ; =0x020FB5FC
	add r1, r5, r1
	bl FUN_0207F430
	mov r1, #0xea
	lsl r1, r1, #0x2
	ldr r0, _0207F7F0 ; =0x020FB60E
	add r1, r5, r1
	mov r2, #0x0
	bl FUN_0207F430
	ldr r2, _0207F7F4 ; =0x00000299
	mov r1, #0xed
	lsl r1, r1, #0x2
	ldrb r2, [r5, r2]
	ldr r0, _0207F7F8 ; =0x020FB620
	add r1, r5, r1
	bl FUN_0207F430
	ldr r2, _0207F7D0 ; =0x00000295
	ldr r1, _0207F7FC ; =0x000003BA
	ldrb r2, [r5, r2]
	ldr r0, _0207F800 ; =0x020FB632
	add r1, r5, r1
	bl FUN_0207F430
	ldr r1, _0207F804 ; =0x000003C6
	ldr r0, _0207F808 ; =0x020FB644
	add r1, r5, r1
	mov r2, #0x0
	bl FUN_0207F430
	mov r2, #0xa6
	lsl r2, r2, #0x2
	mov r1, #0xf
	lsl r1, r1, #0x6
	ldrb r2, [r5, r2]
	ldr r0, _0207F80C ; =0x020FB656
	add r1, r5, r1
	bl FUN_0207F430
	ldr r2, _0207F7F4 ; =0x00000299
	mov r1, #0xf3
	lsl r1, r1, #0x2
	ldrb r2, [r5, r2]
	ldr r0, _0207F810 ; =0x020FB668
	add r1, r5, r1
	bl FUN_0207F430
	ldr r1, _0207F814 ; =0x000003D2
	ldr r0, _0207F818 ; =0x020FB67A
	add r1, r5, r1
	mov r2, #0x0
	bl FUN_0207F430
	ldr r2, _0207F7E4 ; =0x00000297
	ldr r1, _0207F81C ; =0x000003DE
	ldrb r2, [r5, r2]
	ldr r0, _0207F820 ; =0x020FB68C
	add r1, r5, r1
	bl FUN_0207F430
	mov r2, #0xa6
	lsl r2, r2, #0x2
	mov r1, #0xf6
	lsl r1, r1, #0x2
	ldrb r2, [r5, r2]
	ldr r0, _0207F824 ; =0x020FB69E
	add r1, r5, r1
	bl FUN_0207F430
	mov r1, #0xf9
	lsl r1, r1, #0x2
	ldr r0, _0207F828 ; =0x020FB6B0
	add r1, r5, r1
	mov r2, #0x0
	bl FUN_0207F430
	ldr r2, _0207F7D8 ; =0x00000296
	ldr r1, _0207F82C ; =0x000003EA
	ldrb r2, [r5, r2]
	ldr r0, _0207F830 ; =0x020FB6C2
	add r1, r5, r1
	bl FUN_0207F430
	ldr r2, _0207F7E4 ; =0x00000297
	ldr r1, _0207F834 ; =0x000003F6
	ldrb r2, [r5, r2]
	ldr r0, _0207F838 ; =0x020FB6D4
	add r1, r5, r1
	bl FUN_0207F430
	mov r2, #0xa6
	lsl r2, r2, #0x2
	mov r1, #0x3f
	lsl r1, r1, #0x4
	ldrb r2, [r5, r2]
	ldr r0, _0207F83C ; =0x020FB6E6
	add r1, r5, r1
	bl FUN_0207F430
	mov r0, #0x0
	str r0, [sp, #0x24]
	mov r0, #0xcf
	lsl r0, r0, #0x2
	add r1, r5, r0
	str r1, [sp, #0x20]
	add r1, r0, #0x0
	add r1, #0x60
	add r1, r5, r1
	str r1, [sp, #0x1c]
	add r1, r0, #0x0
	sub r1, #0x60
	add r1, r5, r1
	str r1, [sp, #0x18]
	add r1, r0, #0x6
	add r1, r5, r1
	str r1, [sp, #0x14]
	add r1, r0, #0x0
	add r1, #0x66
	add r1, r5, r1
	str r1, [sp, #0x10]
	add r1, r0, #0x0
	sub r1, #0x5a
	add r1, r5, r1
	str r1, [sp, #0xc]
	add r1, r0, #0x0
	add r1, #0xc
	add r1, r5, r1
	str r1, [sp, #0x8]
	add r1, r0, #0x0
	add r1, #0x6c
	add r1, r5, r1
	str r1, [sp, #0x4]
	add r1, r0, #0x0
	sub r1, #0x54
	add r1, r5, r1
	str r1, [sp, #0x0]
	add r1, r0, #0x0
	add r1, #0x12
	add r7, r5, r1
	add r1, r0, #0x0
	add r1, #0x72
	sub r0, #0x4e
	add r6, r5, r1
	add r4, r5, r0
_0207F756:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	bl FUN_0207F48C
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x14]
	bl FUN_0207F48C
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	bl FUN_0207F48C
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_0207F48C
	ldr r0, [sp, #0x20]
	add r7, #0x18
	add r0, #0x18
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r6, #0x18
	add r0, #0x18
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r4, #0x18
	add r0, #0x18
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #0x18
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, #0x18
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	add r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r0, #0x18
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r0, #0x18
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r0, r0, #0x1
	str r0, [sp, #0x24]
	cmp r0, #0x4
	blo _0207F756
	mov r0, #0xff
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r5, r0]
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_0207F7D0: .word 0x00000295
_0207F7D4: .word 0x020FB5D8
_0207F7D8: .word 0x00000296
_0207F7DC: .word 0x000003A2
_0207F7E0: .word 0x020FB5EA
_0207F7E4: .word 0x00000297
_0207F7E8: .word 0x000003AE
_0207F7EC: .word 0x020FB5FC
_0207F7F0: .word 0x020FB60E
_0207F7F4: .word 0x00000299
_0207F7F8: .word 0x020FB620
_0207F7FC: .word 0x000003BA
_0207F800: .word 0x020FB632
_0207F804: .word 0x000003C6
_0207F808: .word 0x020FB644
_0207F80C: .word 0x020FB656
_0207F810: .word 0x020FB668
_0207F814: .word 0x000003D2
_0207F818: .word 0x020FB67A
_0207F81C: .word 0x000003DE
_0207F820: .word 0x020FB68C
_0207F824: .word 0x020FB69E
_0207F828: .word 0x020FB6B0
_0207F82C: .word 0x000003EA
_0207F830: .word 0x020FB6C2
_0207F834: .word 0x000003F6
_0207F838: .word 0x020FB6D4
_0207F83C: .word 0x020FB6E6

	thumb_func_start FUN_0207F840
FUN_0207F840: ; 0x0207F840
	push {r4, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	mov r0, #0x13
	bl FUN_02006D98
	mov r1, #0xae
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0207B628
	add r1, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x11]
	cmp r0, #0x2
	add r0, sp, #0x10
	bne _0207F870
	mov r2, #0x2
	bl FUN_02068B70
	b _0207F876
_0207F870:
	mov r2, #0x2
	bl FUN_02068B68
_0207F876:
	mov r1, #0xaf
	lsl r1, r1, #0x2
	add r0, r4, r1
	sub r1, #0x60
	ldrh r1, [r4, r1]
	bl FUN_02069010
	mov r0, #0x97
	lsl r0, r0, #0x2
	ldrh r0, [r4, r0]
	mov r1, #0x1c
	bl FUN_02068678
	mov r1, #0x1
	eor r0, r1
	mov r1, #0xb6
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r0, r1, #0x0
	mov r2, #0x0
	str r2, [sp, #0x0]
	sub r0, #0x1c
	str r2, [sp, #0x4]
	add r0, r4, r0
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	sub r1, #0x20
	ldr r0, [r4, r1]
	add r1, sp, #0x10
	mov r2, #0x34
	mov r3, #0x68
	bl FUN_020073A0
	mov r2, #0xb5
	lsl r2, r2, #0x2
	str r0, [r4, r2]
	ldr r0, [r4, r2]
	add r2, r2, #0x4
	ldr r2, [r4, r2]
	mov r1, #0x23
	bl FUN_02007558
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0207F8D0
FUN_0207F8D0: ; 0x0207F8D0
	push {r3-r4, lr}
	sub sp, #0xc
	mov r1, #0x2a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	beq _0207F904
	mov r2, #0x0
	add r0, r1, #0x0
	str r2, [sp, #0x0]
	add r0, #0x38
	ldr r0, [r4, r0]
	mov r3, #0x2
	str r0, [sp, #0x4]
	add r0, r1, #0x0
	str r2, [sp, #0x8]
	add r0, #0x30
	add r1, #0x34
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	bl FUN_02069038
	add sp, #0xc
	pop {r3-r4, pc}
_0207F904:
	add r1, #0x34
	ldr r0, [r4, r1]
	mov r1, #0x1
	bl FUN_02007314
	mov r1, #0x0
	mov r2, #0xb6
	str r1, [sp, #0x0]
	lsl r2, r2, #0x2
	ldr r0, [r4, r2]
	mov r3, #0x2
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	add r0, r2, #0x0
	sub r1, r2, #0x4
	sub r2, #0x7c
	sub r0, #0x8
	ldrh r2, [r4, r2]
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	bl FUN_02069038
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0207F934
FUN_0207F934: ; 0x0207F934
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x2d
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_02014D9C
	mov r0, #0xae
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_020072E8
	add r0, r4, #0x0
	bl FUN_0207F840
	add r0, r4, #0x0
	bl FUN_0207F8D0
	pop {r4, pc}

	thumb_func_start FUN_0207F95C
FUN_0207F95C: ; 0x0207F95C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x93
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldrb r1, [r0, #0x12]
	cmp r1, #0x3
	bhi _0207F9AC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0207F978: ; jump table (using 16-bit offset)
	.short _0207F980 - _0207F978 - 2; case 0
	.short _0207F980 - _0207F978 - 2; case 1
	.short _0207F9AC - _0207F978 - 2; case 2
	.short _0207F9AC - _0207F978 - 2; case 3
_0207F980:
	ldr r0, [r0, #0x2c]
	ldr r1, _0207F9C4 ; =0x0000068F
	cmp r0, #0x0
	beq _0207F992
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	strb r2, [r4, r1]
	b _0207F9BA
_0207F992:
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	mov r1, #0x4
	ldr r0, [r4, #0x0]
	mov r2, #0x0
	add r3, r1, #0x0
	bl FUN_0201AEE4
	b _0207F9BA
_0207F9AC:
	ldr r1, _0207F9C4 ; =0x0000068F
	mov r0, #0xf
	ldrb r2, [r4, r1]
	bic r2, r0
	mov r0, #0xf
	orr r0, r2
	strb r0, [r4, r1]
_0207F9BA:
	add r0, r4, #0x0
	bl FUN_0207FA38
	pop {r4, pc}
	nop
_0207F9C4: .word 0x0000068F

	thumb_func_start FUN_0207F9C8
FUN_0207F9C8: ; 0x0207F9C8
	push {r3-r7, lr}
	ldr r0, [r0, #0x0]
	add r4, r1, #0x0
	mov r1, #0x4
	add r5, r2, #0x0
	bl FUN_0201886C
	add r7, r0, #0x0
	lsl r0, r5, #0x2
	add r1, r5, r0
	ldrb r2, [r4, #0x0]
	mov r0, #0x1
	mov r3, #0x0
	add r5, r2, #0x0
	and r5, r0
	mov r0, #0xf
	mul r0, r5
	lsr r5, r2, #0x1
	mov r2, #0x96
	mul r2, r5
	add r0, r0, r2
	add r0, r1, r0
	add r0, #0x1e
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r12, r0
_0207F9FC:
	mov r0, #0x1e
	add r1, r3, #0x0
	mul r1, r0
	mov r0, r12
	mov r2, #0x0
	add r5, r0, r1
_0207FA08:
	ldrb r0, [r4, #0x1]
	ldrb r6, [r4, #0x3]
	lsl r1, r0, #0xc
	add r0, r2, r5
	add r1, r1, r0
	add r6, r3, r6
	lsl r6, r6, #0x5
	ldrb r0, [r4, #0x2]
	add r6, r2, r6
	add r0, r0, r6
	lsl r0, r0, #0x1
	strh r1, [r7, r0]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #0x5
	blo _0207FA08
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x5
	blo _0207F9FC
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0207FA38
FUN_0207FA38: ; 0x0207FA38
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _0207FA78 ; =0x0000068F
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0xf
	beq _0207FA74
	lsl r1, r0, #0x2
	ldr r0, _0207FA7C ; =0x02106148
	mov r5, #0x0
	ldr r4, [r0, r1]
	add r7, r5, #0x0
_0207FA52:
	lsl r1, r5, #0x2
	ldrb r0, [r4, r1]
	cmp r0, #0xff
	beq _0207FA6C
	add r0, r6, #0x0
	add r1, r4, r1
	add r2, r7, #0x0
	bl FUN_0207F9C8
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	b _0207FA52
_0207FA6C:
	ldr r0, [r6, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
_0207FA74:
	pop {r3-r7, pc}
	nop
_0207FA78: .word 0x0000068F
_0207FA7C: .word 0x02106148

	thumb_func_start FUN_0207FA80
FUN_0207FA80: ; 0x0207FA80
	push {r3, lr}
	bl FUN_0207FA98
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _0207FA94
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
_0207FA94:
	mov r0, #0xff
	pop {r3, pc}

	thumb_func_start FUN_0207FA98
FUN_0207FA98: ; 0x0207FA98
	push {r3, lr}
	ldr r1, _0207FAB8 ; =0x0000068F
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0xf
	bne _0207FAAC
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
_0207FAAC:
	lsl r1, r0, #0x2
	ldr r0, _0207FABC ; =0x0210613C
	ldr r0, [r0, r1]
	bl FUN_02020988
	pop {r3, pc}
	.balign 4
_0207FAB8: .word 0x0000068F
_0207FABC: .word 0x0210613C

	thumb_func_start FUN_0207FAC0
FUN_0207FAC0: ; 0x0207FAC0
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0207FB18 ; =0x0000068F
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0xf
	bne _0207FADA
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r5, pc}
_0207FADA:
	lsl r1, r0, #0x2
	ldr r0, _0207FB1C ; =0x0210613C
	ldr r0, [r0, r1]
	bl FUN_02020968
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	beq _0207FB12
	ldr r1, _0207FB20 ; =0x0000FFFE
	add r0, sp, #0x4
	strh r1, [r0, #0x0]
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	ldr r3, _0207FB24 ; =0x021C48F8
	ldr r0, [r5, #0x0]
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #0x4
	bl FUN_0201AFBC
	cmp r0, #0x0
	bne _0207FB12
	mov r0, #0x0
	add sp, #0x8
	mvn r0, r0
	pop {r3-r5, pc}
_0207FB12:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0207FB18: .word 0x0000068F
_0207FB1C: .word 0x0210613C
_0207FB20: .word 0x0000FFFE
_0207FB24: .word 0x021C48F8

	thumb_func_start FUN_0207FB28
FUN_0207FB28: ; 0x0207FB28
	push {r4-r6, lr}
	ldr r1, _0207FBF4 ; =0x0000068F
	add r5, r0, #0x0
	ldrb r2, [r5, r1]
	lsl r2, r2, #0x1c
	lsr r3, r2, #0x1a
	ldr r2, _0207FBF8 ; =0x02106148
	ldr r4, [r2, r3]
	add r2, r1, #0x6
	ldrb r2, [r5, r2]
	cmp r2, #0x0
	beq _0207FB4A
	cmp r2, #0x1
	beq _0207FB84
	cmp r2, #0x2
	beq _0207FB8C
	b _0207FBEE
_0207FB4A:
	sub r1, #0xab
	add r0, r1, #0x0
	bl FUN_020054C8
	add r0, r5, #0x0
	bl FUN_0207FA38
	ldr r1, _0207FBFC ; =0x00000696
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	mov r2, #0x2
	lsl r1, r1, #0x2
	add r1, r4, r1
	bl FUN_0207F9C8
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	add r0, r5, #0x0
	bl FUN_0207CEDC
	ldr r0, _0207FC00 ; =0x00000694
	mov r1, #0x0
	strb r1, [r5, r0]
	mov r1, #0x1
	add r0, r0, #0x1
	strb r1, [r5, r0]
	b _0207FBEE
_0207FB84:
	mov r2, #0x2
	add r0, r1, #0x6
	strb r2, [r5, r0]
	b _0207FBEE
_0207FB8C:
	add r2, r1, #0x5
	ldrb r2, [r5, r2]
	cmp r2, #0x3
	beq _0207FBA0
	add r0, r1, #0x5
	ldrb r0, [r5, r0]
	add r2, r0, #0x1
	add r0, r1, #0x5
	strb r2, [r5, r0]
	b _0207FBEE
_0207FBA0:
	bl FUN_0207CF58
	ldr r0, _0207FBFC ; =0x00000696
	ldrb r6, [r5, r0]
	add r0, r5, #0x0
	bl FUN_0207FAC0
	cmp r6, r0
	beq _0207FBEE
	mov r0, #0x2a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	lsl r0, r0, #0x3
	lsr r0, r0, #0x1f
	beq _0207FBD6
	lsl r1, r6, #0x2
	ldrb r0, [r4, r1]
	cmp r0, #0x1
	beq _0207FBD6
	cmp r0, #0x7
	beq _0207FBD6
	add r0, r5, #0x0
	add r1, r4, r1
	mov r2, #0x0
	bl FUN_0207F9C8
	b _0207FBE2
_0207FBD6:
	lsl r1, r6, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	mov r2, #0x1
	bl FUN_0207F9C8
_0207FBE2:
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	bl FUN_0201AC68
	mov r0, #0x1
	pop {r4-r6, pc}
_0207FBEE:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0207FBF4: .word 0x0000068F
_0207FBF8: .word 0x02106148
_0207FBFC: .word 0x00000696
_0207FC00: .word 0x00000694

	thumb_func_start FUN_0207FC04
FUN_0207FC04: ; 0x0207FC04
	push {r4-r5}
	ldr r4, _0207FC38 ; =0x0000068F
	ldrb r3, [r0, r4]
	lsl r3, r3, #0x1c
	lsr r5, r3, #0x1a
	ldr r3, _0207FC3C ; =0x02106148
	ldr r3, [r3, r5]
	add r5, r4, #0x7
	ldrb r5, [r0, r5]
	lsl r5, r5, #0x2
	add r5, r3, r5
	ldrb r5, [r5, #0x2]
	lsl r5, r5, #0x3
	add r5, #0x14
	strh r5, [r1, #0x0]
	add r1, r4, #0x7
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x2
	add r0, r3, r0
	ldrb r0, [r0, #0x3]
	lsl r0, r0, #0x3
	add r0, #0x14
	strh r0, [r2, #0x0]
	pop {r4-r5}
	bx lr
	nop
_0207FC38: .word 0x0000068F
_0207FC3C: .word 0x02106148

	thumb_func_start FUN_0207FC40
FUN_0207FC40: ; 0x0207FC40
	ldr r2, _0207FC54 ; =0x0000068F
	ldrb r0, [r0, r2]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1a
	ldr r0, _0207FC58 ; =0x02106148
	ldr r2, [r0, r2]
	lsl r0, r1, #0x2
	ldrb r0, [r2, r0]
	bx lr
	nop
_0207FC54: .word 0x0000068F
_0207FC58: .word 0x02106148

	thumb_func_start FUN_0207FC5C
FUN_0207FC5C: ; 0x0207FC5C
	cmp r1, #0x4
	bhi _0207FCA8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0207FC6C: ; jump table (using 16-bit offset)
	.short _0207FC76 - _0207FC6C - 2; case 0
	.short _0207FC80 - _0207FC6C - 2; case 1
	.short _0207FC8A - _0207FC6C - 2; case 2
	.short _0207FC94 - _0207FC6C - 2; case 3
	.short _0207FC9E - _0207FC6C - 2; case 4
_0207FC76:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCAC ; =0x020FB788
	ldr r0, [r0, r1]
	bx lr
_0207FC80:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCB0 ; =0x020FB78C
	ldrh r0, [r0, r1]
	bx lr
_0207FC8A:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCB4 ; =0x020FB78E
	ldrh r0, [r0, r1]
	bx lr
_0207FC94:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCB8 ; =0x020FB790
	ldrh r0, [r0, r1]
	bx lr
_0207FC9E:
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCBC ; =0x020FB792
	ldrh r0, [r0, r1]
	bx lr
_0207FCA8:
	mov r0, #0x0
	bx lr
	.balign 4
_0207FCAC: .word 0x020FB788
_0207FCB0: .word 0x020FB78C
_0207FCB4: .word 0x020FB78E
_0207FCB8: .word 0x020FB790
_0207FCBC: .word 0x020FB792

	thumb_func_start FUN_0207FCC0
FUN_0207FCC0: ; 0x0207FCC0
	mov r2, #0xc
	mul r2, r1
	ldr r1, _0207FCDC ; =0x020FB792
	ldrh r2, [r1, r2]
	mov r1, #0x2
	lsl r1, r1, #0xe
	tst r1, r2
	beq _0207FCD8
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	ldrb r2, [r0, r1]
	add r2, #0x92
_0207FCD8:
	add r0, r2, #0x0
	bx lr
	.balign 4
_0207FCDC: .word 0x020FB792

	thumb_func_start FUN_0207FCE0
FUN_0207FCE0: ; 0x0207FCE0
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0207FCFC ; =0x020FB792
	ldrh r1, [r0, r1]
	mov r0, #0x2
	lsl r0, r0, #0xe
	tst r0, r1
	beq _0207FCF6
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	bx lr
_0207FCF6:
	mov r0, #0xff
	bx lr
	nop
_0207FCFC: .word 0x020FB792

	thumb_func_start FUN_0207FD00
FUN_0207FD00: ; 0x0207FD00
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x3c
	bl FUN_02016998
	add r4, r0, #0x0
	mov r2, #0x65
	str r7, [r4, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	add r3, r7, #0x0
	bl FUN_0200A86C
	str r0, [r4, #0x4]
	ldr r2, [r4, #0x0]
	mov r0, #0x9
	mov r1, #0x20
	bl FUN_0200AA90
	str r0, [r4, #0x8]
	str r5, [r4, #0xc]
	str r6, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	str r0, [r4, #0x30]
	str r0, [r4, #0x34]
	str r0, [r4, #0x38]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x0]
	bl FUN_020806F4
	cmp r0, #0x14
	bls _0207FD5A
	b _02080090
_0207FD5A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0207FD66: ; jump table (using 16-bit offset)
	.short _0207FD90 - _0207FD66 - 2; case 0
	.short _0207FDBC - _0207FD66 - 2; case 1
	.short _0207FDE8 - _0207FD66 - 2; case 2
	.short _0207FE14 - _0207FD66 - 2; case 3
	.short _0207FE40 - _0207FD66 - 2; case 4
	.short _0207FE6C - _0207FD66 - 2; case 5
	.short _0207FE98 - _0207FD66 - 2; case 6
	.short _0207FEC4 - _0207FD66 - 2; case 7
	.short _0207FEF0 - _0207FD66 - 2; case 8
	.short _0207FF1C - _0207FD66 - 2; case 9
	.short _0207FF3E - _0207FD66 - 2; case 10
	.short _0207FF60 - _0207FD66 - 2; case 11
	.short _0207FF82 - _0207FD66 - 2; case 12
	.short _0207FFA4 - _0207FD66 - 2; case 13
	.short _0207FFC6 - _0207FD66 - 2; case 14
	.short _0207FFE8 - _0207FD66 - 2; case 15
	.short _02080014 - _0207FD66 - 2; case 16
	.short _0208002E - _0207FD66 - 2; case 17
	.short _02080046 - _0207FD66 - 2; case 18
	.short _02080060 - _0207FD66 - 2; case 19
	.short _02080078 - _0207FD66 - 2; case 20
_0207FD90:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_02080108
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FDBC:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_02080108
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FDE8:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_02080108
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE14:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE40:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE6C:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x36
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FE98:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x37
	bl FUN_02080108
	mov r0, #0x8
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x9
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FEC4:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x38
	bl FUN_02080108
	mov r0, #0x7
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x8
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FEF0:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x39
	bl FUN_02080108
	mov r0, #0x7
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x8
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_0207FF1C:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3a
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FF3E:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3b
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FF60:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3c
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FF82:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3d
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FFA4:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3e
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FFC6:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x3f
	bl FUN_02080108
	mov r0, #0x9
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	b _02080090
_0207FFE8:
	mov r0, #0x1
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	bl FUN_020800E0
	mov r0, #0x2
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x40
	bl FUN_02080228
	mov r0, #0x6
	str r0, [r4, #0x24]
	add r0, r4, #0x0
	bl FUN_0208048C
	mov r0, #0x7
	str r0, [r4, #0x2c]
	add r0, r4, #0x0
	bl FUN_02080678
	b _02080090
_02080014:
	mov r0, #0x1
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x65
	mov r2, #0x0
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_0208002E:
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x66
	str r2, [r4, #0x1c]
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_02080046:
	mov r0, #0x1
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x67
	mov r2, #0x0
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_02080060:
	mov r2, #0x1
	add r0, r4, #0x0
	mov r1, #0x67
	str r2, [r4, #0x1c]
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
	b _02080090
_02080078:
	mov r0, #0x1
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	mov r1, #0x68
	mov r2, #0x0
	bl FUN_02080384
	mov r0, #0x6
	str r0, [r4, #0x34]
	add r0, r4, #0x0
	bl FUN_020806B4
_02080090:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02080094
FUN_02080094: ; 0x02080094
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _020800A2
	bl FUN_02016A18
_020800A2:
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _020800AC
	bl FUN_02016A18
_020800AC:
	ldr r0, [r4, #0x28]
	cmp r0, #0x0
	beq _020800B6
	bl FUN_02016A18
_020800B6:
	ldr r0, [r4, #0x30]
	cmp r0, #0x0
	beq _020800C0
	bl FUN_02016A18
_020800C0:
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020800CA
	bl FUN_02016A18
_020800CA:
	ldr r0, [r4, #0x8]
	bl FUN_0200AB18
	ldr r0, [r4, #0x4]
	bl FUN_0200A8B8
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020800E0
FUN_020800E0: ; 0x020800E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02068854
	add r4, r0, #0x0
	cmp r4, #0x18
	bgt _02080106
	ldr r1, [r5, #0x0]
	mov r0, #0x48
	bl FUN_020219F4
	str r0, [r5, #0x18]
	add r4, #0x18
	ldr r0, [r5, #0x4]
	ldr r2, [r5, #0x18]
	add r1, r4, #0x0
	bl FUN_0200A8E0
_02080106:
	pop {r3-r5, pc}

	thumb_func_start FUN_02080108
FUN_02080108: ; 0x02080108
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x9
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x6
	bl FUN_020219F4
	add r4, r0, #0x0
	mov r0, #0x9
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x6
	bl FUN_020219F4
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x4]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0200A8E0
	ldr r0, [r5, #0xc]
	mov r1, #0x94
	mov r2, #0x0
	bl FUN_020671BC
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x95
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x1
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x96
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x2
	ldr r0, [r5, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x9b
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x3
	ldr r0, [r5, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x98
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	ldr r0, [r5, #0xc]
	mov r1, #0x91
	mov r2, #0x0
	bl FUN_020671BC
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x5
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x92
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x93
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x7
	mov r3, #0x2
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x8
	bl FUN_0200B59C
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0x20]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02080228
FUN_02080228: ; 0x02080228
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x12
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	bl FUN_020219F4
	add r5, r0, #0x0
	mov r0, #0x12
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	bl FUN_020219F4
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_0200A8E0
	ldr r0, [r4, #0xc]
	mov r1, #0x94
	mov r2, #0x0
	bl FUN_020671BC
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	mov r1, #0x95
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_0200B764
	ldr r0, [r4, #0xc]
	mov r1, #0x96
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x2
	ldr r0, [r4, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	mov r1, #0x9b
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x3
	ldr r0, [r4, #0x8]
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldr r0, [r4, #0xc]
	mov r1, #0x79
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0xf
	bhi _020802F8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020802D8: ; jump table (using 16-bit offset)
	.short _020802F8 - _020802D8 - 2; case 0
	.short _02080334 - _020802D8 - 2; case 1
	.short _02080334 - _020802D8 - 2; case 2
	.short _02080334 - _020802D8 - 2; case 3
	.short _0208030C - _020802D8 - 2; case 4
	.short _0208030C - _020802D8 - 2; case 5
	.short _020802F8 - _020802D8 - 2; case 6
	.short _02080320 - _020802D8 - 2; case 7
	.short _02080320 - _020802D8 - 2; case 8
	.short _020802F8 - _020802D8 - 2; case 9
	.short _0208035C - _020802D8 - 2; case 10
	.short _0208035C - _020802D8 - 2; case 11
	.short _020802F8 - _020802D8 - 2; case 12
	.short _020802F8 - _020802D8 - 2; case 13
	.short _020802F8 - _020802D8 - 2; case 14
	.short _02080348 - _020802D8 - 2; case 15
_020802F8:
	mov r0, #0x1
	mov r1, #0x7
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_0208030C:
	mov r0, #0x1
	mov r1, #0x3
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_02080320:
	mov r0, #0x1
	mov r1, #0x4
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_02080334:
	mov r0, #0x1
	mov r1, #0x5
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_02080348:
	mov r0, #0x1
	mov r1, #0x8
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
	b _0208036E
_0208035C:
	mov r0, #0x1
	mov r1, #0x7
	bl FUN_02015CF8
	add r2, r0, #0x0
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_0200B59C
_0208036E:
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x20]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02080384
FUN_02080384: ; 0x02080384
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	mov r0, #0x5a
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	add r6, r2, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	mov r0, #0x5a
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x2
	bl FUN_020219F4
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x4]
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl FUN_0200A8E0
	cmp r6, #0x0
	ldr r0, [r5, #0xc]
	bne _02080418
	mov r1, #0x91
	mov r2, #0x0
	bl FUN_020671BC
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x5
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x92
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x93
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x7
	mov r3, #0x2
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x8
	bl FUN_0200B59C
	b _02080478
_02080418:
	mov r1, #0x94
	mov r2, #0x0
	bl FUN_020671BC
	mov r3, #0x2
	add r2, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x5
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x95
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x6
	bl FUN_0200B764
	ldr r0, [r5, #0xc]
	mov r1, #0x96
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x8]
	mov r1, #0x7
	mov r3, #0x2
	bl FUN_0200AD38
	ldr r0, [r5, #0xc]
	mov r1, #0x98
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r1, #0x8
	bl FUN_0200B59C
_02080478:
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0x20]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0208048C
FUN_0208048C: ; 0x0208048C
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	mov r0, #0x48
	bl FUN_020219F4
	str r0, [r4, #0x28]
	ldr r0, [r4, #0xc]
	mov r1, #0x46
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0xc]
	ldr r0, [r4, #0xc]
	mov r1, #0x47
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	ldr r0, [r4, #0xc]
	mov r1, #0x48
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	mov r1, #0x49
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x0]
	ldr r0, [r4, #0xc]
	mov r1, #0x4a
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x4b
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	add r2, r1, #0x0
	bl FUN_020671BC
	mov r1, #0x6
	bl _u32_div_f
	cmp r1, #0x5
	bhi _02080510
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02080504: ; jump table (using 16-bit offset)
	.short _02080510 - _02080504 - 2; case 0
	.short _02080548 - _02080504 - 2; case 1
	.short _0208057E - _02080504 - 2; case 2
	.short _020805B4 - _02080504 - 2; case 3
	.short _020805EA - _02080504 - 2; case 4
	.short _02080620 - _02080504 - 2; case 5
_02080510:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x8]
	add r2, r0, #0x0
	mov r5, #0x0
	cmp r2, r1
	bge _02080520
	mov r5, #0x1
	add r0, r1, #0x0
_02080520:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _0208052A
	mov r5, #0x2
	add r0, r1, #0x0
_0208052A:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _02080534
	mov r5, #0x3
	add r0, r1, #0x0
_02080534:
	cmp r0, r7
	bge _0208053C
	mov r5, #0x4
	add r0, r7, #0x0
_0208053C:
	cmp r0, r6
	blt _02080542
	b _02080654
_02080542:
	mov r5, #0x5
	add r0, r6, #0x0
	b _02080654
_02080548:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	add r2, r0, #0x0
	mov r5, #0x1
	cmp r2, r1
	bge _02080558
	mov r5, #0x2
	add r0, r1, #0x0
_02080558:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _02080562
	mov r5, #0x3
	add r0, r1, #0x0
_02080562:
	cmp r0, r7
	bge _0208056A
	mov r5, #0x4
	add r0, r7, #0x0
_0208056A:
	cmp r0, r6
	bge _02080572
	mov r5, #0x5
	add r0, r6, #0x0
_02080572:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _02080654
	mov r5, #0x0
	add r0, r1, #0x0
	b _02080654
_0208057E:
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	add r2, r0, #0x0
	mov r5, #0x2
	cmp r2, r1
	bge _0208058E
	mov r5, #0x3
	add r0, r1, #0x0
_0208058E:
	cmp r0, r7
	bge _02080596
	mov r5, #0x4
	add r0, r7, #0x0
_02080596:
	cmp r0, r6
	bge _0208059E
	mov r5, #0x5
	add r0, r6, #0x0
_0208059E:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _020805A8
	mov r5, #0x0
	add r0, r1, #0x0
_020805A8:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _02080654
	mov r5, #0x1
	add r0, r1, #0x0
	b _02080654
_020805B4:
	ldr r0, [sp, #0x0]
	mov r5, #0x3
	add r1, r0, #0x0
	cmp r1, r7
	bge _020805C2
	mov r5, #0x4
	add r0, r7, #0x0
_020805C2:
	cmp r0, r6
	bge _020805CA
	mov r5, #0x5
	add r0, r6, #0x0
_020805CA:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _020805D4
	mov r5, #0x0
	add r0, r1, #0x0
_020805D4:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _020805DE
	mov r5, #0x1
	add r0, r1, #0x0
_020805DE:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _02080654
	mov r5, #0x2
	add r0, r1, #0x0
	b _02080654
_020805EA:
	mov r5, #0x4
	add r0, r7, #0x0
	cmp r7, r6
	bge _020805F6
	mov r5, #0x5
	add r0, r6, #0x0
_020805F6:
	ldr r1, [sp, #0xc]
	cmp r0, r1
	bge _02080600
	mov r5, #0x0
	add r0, r1, #0x0
_02080600:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _0208060A
	mov r5, #0x1
	add r0, r1, #0x0
_0208060A:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _02080614
	mov r5, #0x2
	add r0, r1, #0x0
_02080614:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _02080654
	mov r5, #0x3
	add r0, r1, #0x0
	b _02080654
_02080620:
	ldr r1, [sp, #0xc]
	mov r5, #0x5
	add r0, r6, #0x0
	cmp r6, r1
	bge _0208062E
	mov r5, #0x0
	add r0, r1, #0x0
_0208062E:
	ldr r1, [sp, #0x8]
	cmp r0, r1
	bge _02080638
	mov r5, #0x1
	add r0, r1, #0x0
_02080638:
	ldr r1, [sp, #0x4]
	cmp r0, r1
	bge _02080642
	mov r5, #0x2
	add r0, r1, #0x0
_02080642:
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bge _0208064C
	mov r5, #0x3
	add r0, r1, #0x0
_0208064C:
	cmp r0, r7
	bge _02080654
	mov r5, #0x4
	add r0, r7, #0x0
_02080654:
	mov r1, #0x5
	bl _s32_div_f
	mov r2, #0xa
	add r6, r5, #0x0
	mul r6, r2
	ldr r3, _02080674 ; =0x020FBB54
	lsl r2, r1, #0x1
	add r1, r3, r6
	ldrh r1, [r2, r1]
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x28]
	bl FUN_0200A8E0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02080674: .word 0x020FBB54

	thumb_func_start FUN_02080678
FUN_02080678: ; 0x02080678
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x0]
	mov r0, #0x48
	bl FUN_020219F4
	mov r6, #0x0
	str r0, [r5, #0x30]
	add r4, r6, #0x0
_0208068A:
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	bl FUN_02069BC8
	cmp r0, #0x1
	bne _02080698
	add r6, r4, #0x1
_02080698:
	add r4, r4, #0x1
	cmp r4, #0x5
	blt _0208068A
	ldr r1, _020806B0 ; =0x020FBB48
	lsl r2, r6, #0x1
	ldrh r1, [r1, r2]
	ldr r0, [r5, #0x4]
	ldr r2, [r5, #0x30]
	bl FUN_0200A8E0
	pop {r4-r6, pc}
	nop
_020806B0: .word 0x020FBB48

	thumb_func_start FUN_020806B4
FUN_020806B4: ; 0x020806B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	mov r0, #0x12
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0x4
	bl FUN_020219F4
	str r0, [r5, #0x38]
	cmp r4, #0x5
	bgt _020806D8
	mov r1, #0x69
	b _020806EA
_020806D8:
	cmp r4, #0xa
	bgt _020806E0
	mov r1, #0x6a
	b _020806EA
_020806E0:
	cmp r4, #0x28
	bgt _020806E8
	mov r1, #0x6b
	b _020806EA
_020806E8:
	mov r1, #0x6c
_020806EA:
	ldr r0, [r5, #0x4]
	ldr r2, [r5, #0x38]
	bl FUN_0200A8E0
	pop {r3-r5, pc}

	thumb_func_start FUN_020806F4
FUN_020806F4: ; 0x020806F4
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _02080708
	b _0208084E
_02080708:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02080774
	add r0, r5, #0x0
	mov r1, #0x98
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	mov r0, #0x0
	mov r1, #0x37
	bl FUN_02015CF8
	cmp r6, r0
	bne _02080732
	mov r0, #0xf
	pop {r4-r6, pc}
_02080732:
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _0208074C
	cmp r4, #0x1
	bne _02080748
	mov r0, #0x7
	pop {r4-r6, pc}
_02080748:
	mov r0, #0x8
	pop {r4-r6, pc}
_0208074C:
	add r0, r5, #0x0
	mov r1, #0x98
	mov r2, #0x0
	bl FUN_020671BC
	add r5, r0, #0x0
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	cmp r5, r0
	bne _02080768
	mov r0, #0x2
	pop {r4-r6, pc}
_02080768:
	cmp r4, #0x1
	bne _02080770
	mov r0, #0x0
	pop {r4-r6, pc}
_02080770:
	mov r0, #0x1
	pop {r4-r6, pc}
_02080774:
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _020807D6
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x2
	bl FUN_02015CF8
	cmp r6, r0
	bne _020807A6
	cmp r4, #0x1
	bne _020807A2
	mov r0, #0xd
	pop {r4-r6, pc}
_020807A2:
	mov r0, #0xe
	pop {r4-r6, pc}
_020807A6:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r5, r0, #0x0
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_02015CF8
	cmp r5, r0
	bne _020807CA
	cmp r4, #0x1
	bne _020807C6
	mov r0, #0xb
	pop {r4-r6, pc}
_020807C6:
	mov r0, #0xc
	pop {r4-r6, pc}
_020807CA:
	cmp r4, #0x1
	bne _020807D2
	mov r0, #0x9
	pop {r4-r6, pc}
_020807D2:
	mov r0, #0xa
	pop {r4-r6, pc}
_020807D6:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	cmp r6, r0
	beq _02080836
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02015CF8
	cmp r6, r0
	beq _02080836
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x9
	bl FUN_02015CF8
	cmp r6, r0
	beq _02080836
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r5, r0, #0x0
	mov r0, #0x1
	mov r1, #0xa
	bl FUN_02015CF8
	cmp r5, r0
	bne _02080842
_02080836:
	cmp r4, #0x1
	bne _0208083E
	mov r0, #0x5
	pop {r4-r6, pc}
_0208083E:
	mov r0, #0x6
	pop {r4-r6, pc}
_02080842:
	cmp r4, #0x1
	bne _0208084A
	mov r0, #0x3
	pop {r4-r6, pc}
_0208084A:
	mov r0, #0x4
	pop {r4-r6, pc}
_0208084E:
	cmp r4, #0x1
	bne _02080884
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _02080880
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_02015CF8
	cmp r4, r0
	bne _0208087C
	mov r0, #0x14
	pop {r4-r6, pc}
_0208087C:
	mov r0, #0x12
	pop {r4-r6, pc}
_02080880:
	mov r0, #0x10
	pop {r4-r6, pc}
_02080884:
	add r0, r5, #0x0
	mov r1, #0x6e
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x1
	bne _02080896
	mov r0, #0x13
	pop {r4-r6, pc}
_02080896:
	mov r0, #0x11
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0208089C
FUN_0208089C: ; 0x0208089C
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	bl FUN_020808AC
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020808AC
FUN_020808AC: ; 0x020808AC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, r3, #0x0
	ldr r6, [sp, #0x18]
	cmp r2, #0x6
	bls _020808BC
	b _02080AE0
_020808BC:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_020808C8: ; jump table (using 16-bit offset)
	.short _020808D6 - _020808C8 - 2; case 0
	.short _0208092A - _020808C8 - 2; case 1
	.short _02080974 - _020808C8 - 2; case 2
	.short _02080994 - _020808C8 - 2; case 3
	.short _020809B0 - _020808C8 - 2; case 4
	.short _02080A38 - _020808C8 - 2; case 5
	.short _02080A58 - _020808C8 - 2; case 6
_020808D6:
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02015CF8
	cmp r5, r0
	ble _020808E4
	mov r5, #0x0
_020808E4:
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	bne _0208090C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	b _0208091E
_0208090C:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_02080B30
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02080BA8
_0208091E:
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02080AE4
	pop {r3-r7, pc}
_0208092A:
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	bne _02080958
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	pop {r3-r7, pc}
_02080958:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	pop {r3-r7, pc}
_02080974:
	mov r1, #0x0
	bl FUN_02080BA8
	mov r0, #0x0
	mov r1, #0x37
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	pop {r3-r7, pc}
_02080994:
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_02080B30
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02080AE4
	pop {r3-r7, pc}
_020809B0:
	add r2, r6, #0x0
	bl FUN_0206A9AC
	cmp r0, #0x1
	bne _020809F6
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	bne _020809E2
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	b _02080A30
_020809E2:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_02080B30
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02080BA8
	b _02080A30
_020809F6:
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	bne _02080A1E
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	bl FUN_02080C08
	b _02080A30
_02080A1E:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02080BA8
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
_02080A30:
	add r0, r4, #0x0
	bl FUN_02080C28
	pop {r3-r7, pc}
_02080A38:
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020672BC
	cmp r0, #0x0
	beq _02080AE0
	mov r0, #0x1
	mov r1, #0x2
	bl FUN_02015CF8
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	pop {r3-r7, pc}
_02080A58:
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02015CF8
	cmp r5, r0
	ble _02080A66
	mov r5, #0x0
_02080A66:
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_0206A9AC
	cmp r0, #0x0
	bne _02080ACC
	add r0, r4, #0x0
	mov r1, #0x98
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x97
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x94
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x91
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x95
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x92
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x96
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x93
	add r2, sp, #0x0
	bl FUN_02067960
_02080ACC:
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	bl FUN_02080B30
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02080AE4
_02080AE0:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02080AE4
FUN_02080AE4: ; 0x02080AE4
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r2, #0x0
	bl FUN_020239BC
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_020239CC
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020239A0
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x7
	add r2, sp, #0x4
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x9c
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x90
	add r2, r4, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	bl FUN_02021A20
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02080B30
FUN_02080B30: ; 0x02080B30
	push {r0-r3}
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, sp, #0x0
	add r4, r2, #0x0
	bl FUN_020126B4
	cmp r4, #0x0
	add r2, sp, #0x24
	bne _02080B76
	add r0, r5, #0x0
	mov r1, #0x97
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x91
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x92
	add r2, sp, #0x4
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x93
	add r2, sp, #0x8
	bl FUN_02067960
	add sp, #0x10
	pop {r3-r5}
	pop {r3}
	add sp, #0x10
	bx r3
_02080B76:
	add r0, r5, #0x0
	mov r1, #0x98
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x94
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x95
	add r2, sp, #0x4
	bl FUN_02067960
	add r0, r5, #0x0
	mov r1, #0x96
	add r2, sp, #0x8
	bl FUN_02067960
	add sp, #0x10
	pop {r3-r5}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4

	thumb_func_start FUN_02080BA8
FUN_02080BA8: ; 0x02080BA8
	push {r3-r4, lr}
	sub sp, #0x4
	mov r2, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	cmp r1, #0x0
	add r2, sp, #0x0
	bne _02080BE0
	mov r1, #0x97
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x91
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x92
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x93
	add r2, sp, #0x0
	bl FUN_02067960
	add sp, #0x4
	pop {r3-r4, pc}
_02080BE0:
	mov r1, #0x98
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x94
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x95
	add r2, sp, #0x0
	bl FUN_02067960
	add r0, r4, #0x0
	mov r1, #0x96
	add r2, sp, #0x0
	bl FUN_02067960
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02080C08
FUN_02080C08: ; 0x02080C08
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020672BC
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0x9b
	add r2, sp, #0x0
	bl FUN_02067960
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02080C28
FUN_02080C28: ; 0x02080C28
	push {r3, lr}
	mov r1, #0x1
	str r1, [sp, #0x0]
	mov r1, #0x6e
	add r2, sp, #0x0
	bl FUN_02067960
	pop {r3, pc}

	thumb_func_start FUN_02080C38
FUN_02080C38: ; 0x02080C38
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x8
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r1, _02080C5C ; =FUN_02080C60
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	nop
_02080C5C: .word FUN_02080C60

	thumb_func_start FUN_02080C60
FUN_02080C60: ; 0x02080C60
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0xe
	bls _02080C7C
	b _02080DE2
_02080C7C:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02080C88: ; jump table (using 16-bit offset)
	.short _02080CA6 - _02080C88 - 2; case 0
	.short _02080CB4 - _02080C88 - 2; case 1
	.short _02080D16 - _02080C88 - 2; case 2
	.short _02080D28 - _02080C88 - 2; case 3
	.short _02080D36 - _02080C88 - 2; case 4
	.short _02080D48 - _02080C88 - 2; case 5
	.short _02080D64 - _02080C88 - 2; case 6
	.short _02080D78 - _02080C88 - 2; case 7
	.short _02080D8A - _02080C88 - 2; case 8
	.short _02080D9C - _02080C88 - 2; case 9
	.short _02080DAE - _02080C88 - 2; case 10
	.short _02080DC0 - _02080C88 - 2; case 11
	.short _02080DCE - _02080C88 - 2; case 12
	.short _02080DD4 - _02080C88 - 2; case 13
	.short _02080DE6 - _02080C88 - 2; case 14
_02080CA6:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080CB4:
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	mov r1, #0x0
	bl FUN_0206B9B0
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	mov r1, #0xb
	str r0, [sp, #0x0]
	bl FUN_020239A0
	add r5, r0, #0x0
	mov r1, #0x0
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	mov r1, #0x2
	strb r1, [r0, #0x2]
	ldr r0, [sp, #0x0]
	str r7, [sp, #0xc]
	str r5, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [r6, #0xc]
	bl FUN_02027E24
	str r0, [sp, #0x18]
	ldr r0, [r6, #0xc]
	bl LoadPlayerDataAddress
	str r0, [sp, #0x1c]
	add r0, sp, #0x4
	bl FUN_02081214
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02021A20
	ldr r0, [r4, #0x0]
	bl FUN_02081DC4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D16:
	ldr r0, [r4, #0x0]
	bl FUN_02081EB8
	cmp r0, #0x1
	bne _02080DF2
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D28:
	mov r0, #0x1
	bl FUN_02031588
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D36:
	mov r0, #0x1
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02080DF2
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D48:
	ldr r0, [r4, #0x0]
	bl FUN_020815D0
	ldr r3, [r4, #0x0]
	ldr r2, _02080DF8 ; =0x000019B8
	ldr r1, _02080DFC ; =0x020FBBD8
	ldr r2, [r3, r2]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D64:
	ldr r0, [r4, #0x0]
	bl FUN_02081668
	ldr r0, [r4, #0x0]
	bl FUN_02081ED4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D78:
	ldr r0, [r4, #0x0]
	bl FUN_02081EC0
	cmp r0, #0x1
	bne _02080DF2
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D8A:
	ldr r1, _02080E00 ; =0x020FBBC8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080D9C:
	ldr r1, _02080E04 ; =0x020FBBF8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DAE:
	ldr r1, _02080E08 ; =0x020FBBE8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DC0:
	ldr r0, [r4, #0x0]
	bl FUN_020814E8
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DCE:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DD4:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080DF2
_02080DE2:
	bl ErrorHandling
_02080DE6:
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x28
	mov r0, #0x1
	pop {r3-r7, pc}
_02080DF2:
	mov r0, #0x0
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_02080DF8: .word 0x000019B8
_02080DFC: .word 0x020FBBD8
_02080E00: .word 0x020FBBC8
_02080E04: .word 0x020FBBF8
_02080E08: .word 0x020FBBE8

	thumb_func_start FUN_02080E0C
FUN_02080E0C: ; 0x02080E0C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x8
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, _02080E50 ; =0x00000121
	str r6, [r4, #0x0]
	ldrb r0, [r6, r0]
	cmp r0, #0x0
	beq _02080E36
	cmp r0, #0x1
	beq _02080E36
	cmp r0, #0x2
	bne _02080E42
_02080E36:
	ldr r1, _02080E54 ; =FUN_02080E5C
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
_02080E42:
	ldr r1, _02080E58 ; =FUN_02081000
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
	nop
_02080E50: .word 0x00000121
_02080E54: .word FUN_02080E5C
_02080E58: .word FUN_02081000

	thumb_func_start FUN_02080E5C
FUN_02080E5C: ; 0x02080E5C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0xd
	bls _02080E74
	b _02080FCE
_02080E74:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02080E80: ; jump table (using 16-bit offset)
	.short _02080E9C - _02080E80 - 2; case 0
	.short _02080EAA - _02080E80 - 2; case 1
	.short _02080EC6 - _02080E80 - 2; case 2
	.short _02080EDE - _02080E80 - 2; case 3
	.short _02080F00 - _02080E80 - 2; case 4
	.short _02080F1C - _02080E80 - 2; case 5
	.short _02080F3E - _02080E80 - 2; case 6
	.short _02080F58 - _02080E80 - 2; case 7
	.short _02080F6A - _02080E80 - 2; case 8
	.short _02080F8A - _02080E80 - 2; case 9
	.short _02080FA8 - _02080E80 - 2; case 10
	.short _02080FBA - _02080E80 - 2; case 11
	.short _02080FC0 - _02080E80 - 2; case 12
	.short _02080FD2 - _02080E80 - 2; case 13
_02080E9C:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EAA:
	ldr r0, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _02080EBE
	bl FUN_02081EC0
	cmp r0, #0x1
	beq _02080EBE
	b _02080FDC
_02080EBE:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EC6:
	ldr r1, [r4, #0x0]
	ldr r0, _02080FE0 ; =0x00000171
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _02080ED6
	mov r0, #0x0
	bl FUN_02031588
_02080ED6:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EDE:
	ldr r2, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r2, r1]
	cmp r1, #0x1
	bne _02080EFA
	mov r0, #0x0
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02080FDC
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080EFA:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F00:
	ldr r0, [r4, #0x0]
	bl FUN_020815D0
	ldr r3, [r4, #0x0]
	ldr r2, _02080FE4 ; =0x000019B8
	ldr r1, _02080FE8 ; =0x020FBBD8
	ldr r2, [r3, r2]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F1C:
	ldr r0, [r4, #0x0]
	bl FUN_02081668
	ldr r0, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x1
	bne _02080F38
	bl FUN_02081ED4
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F38:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02080FDC
_02080F3E:
	ldr r0, [r4, #0x0]
	ldr r1, _02080FE0 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _02080F50
	bl FUN_02081EC0
	cmp r0, #0x1
	bne _02080FDC
_02080F50:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F58:
	ldr r1, _02080FEC ; =0x020FBBC8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F6A:
	ldr r2, [r4, #0x0]
	ldr r0, _02080FF0 ; =0x00000121
	ldrb r0, [r2, r0]
	add r0, #0xff
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _02080F82
	ldr r1, _02080FF4 ; =0x020FBBF8
	add r0, r5, #0x0
	bl FUN_02046500
_02080F82:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080F8A:
	ldr r2, [r4, #0x0]
	ldr r0, _02080FF0 ; =0x00000121
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	beq _02080F98
	cmp r0, #0x2
	bne _02080FA0
_02080F98:
	ldr r1, _02080FF8 ; =0x020FBBE8
	add r0, r5, #0x0
	bl FUN_02046500
_02080FA0:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FA8:
	ldr r1, _02080FFC ; =0x020FBBB8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FBA:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FC0:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02080FDC
_02080FCE:
	bl ErrorHandling
_02080FD2:
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_02080FDC:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02080FE0: .word 0x00000171
_02080FE4: .word 0x000019B8
_02080FE8: .word 0x020FBBD8
_02080FEC: .word 0x020FBBC8
_02080FF0: .word 0x00000121
_02080FF4: .word 0x020FBBF8
_02080FF8: .word 0x020FBBE8
_02080FFC: .word 0x020FBBB8

	thumb_func_start FUN_02081000
FUN_02081000: ; 0x02081000
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl FUN_02046528
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x9
	bls _0208101A
	b _020811A4
_0208101A:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02081026: ; jump table (using 16-bit offset)
	.short _0208103A - _02081026 - 2; case 0
	.short _02081048 - _02081026 - 2; case 1
	.short _02081070 - _02081026 - 2; case 2
	.short _0208108A - _02081026 - 2; case 3
	.short _02081090 - _02081026 - 2; case 4
	.short _020810AE - _02081026 - 2; case 5
	.short _020810D2 - _02081026 - 2; case 6
	.short _020810F0 - _02081026 - 2; case 7
	.short _02081196 - _02081026 - 2; case 8
	.short _020811A8 - _02081026 - 2; case 9
_0208103A:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081048:
	ldr r0, [r4, #0x0]
	ldr r1, _020811BC ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #0x3
	beq _02081056
	cmp r1, #0x4
	bne _02081068
_02081056:
	bl FUN_020815D0
	ldr r3, [r4, #0x0]
	ldr r2, _020811C0 ; =0x000019B8
	ldr r1, _020811C4 ; =0x020FBBD8
	ldr r2, [r3, r2]
	add r0, r5, #0x0
	bl FUN_02046500
_02081068:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081070:
	ldr r0, [r4, #0x0]
	ldr r1, _020811BC ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #0x3
	beq _0208107E
	cmp r1, #0x4
	bne _02081082
_0208107E:
	bl FUN_02081668
_02081082:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_0208108A:
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081090:
	ldr r2, [r4, #0x0]
	ldr r0, _020811BC ; =0x00000121
	ldrb r0, [r2, r0]
	cmp r0, #0x3
	beq _0208109E
	cmp r0, #0x4
	bne _020810A6
_0208109E:
	ldr r1, _020811C8 ; =0x020FBBC8
	add r0, r5, #0x0
	bl FUN_02046500
_020810A6:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020810AE:
	ldr r0, [r4, #0x0]
	ldr r1, _020811BC ; =0x00000121
	ldrb r1, [r0, r1]
	cmp r1, #0x5
	beq _020810BC
	cmp r1, #0x6
	bne _020810CA
_020810BC:
	bl FUN_02082D18
	ldr r1, _020811CC ; =0x020FBBF8
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02046500
_020810CA:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020810D2:
	ldr r2, [r4, #0x0]
	ldr r0, _020811BC ; =0x00000121
	ldrb r0, [r2, r0]
	cmp r0, #0x7
	beq _020810E0
	cmp r0, #0x8
	bne _020810E8
_020810E0:
	ldr r1, _020811D0 ; =0x020FBBE8
	add r0, r5, #0x0
	bl FUN_02046500
_020810E8:
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020810F0:
	ldr r1, [r4, #0x0]
	ldr r0, _020811BC ; =0x00000121
	ldrb r0, [r1, r0]
	cmp r0, #0x8
	bhi _0208116E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02081106: ; jump table (using 16-bit offset)
	.short _0208116E - _02081106 - 2; case 0
	.short _0208116E - _02081106 - 2; case 1
	.short _0208116E - _02081106 - 2; case 2
	.short _02081118 - _02081106 - 2; case 3
	.short _02081118 - _02081106 - 2; case 4
	.short _0208113A - _02081106 - 2; case 5
	.short _0208113A - _02081106 - 2; case 6
	.short _02081156 - _02081106 - 2; case 7
	.short _02081156 - _02081106 - 2; case 8
_02081118:
	mov r5, #0x0
	add r6, sp, #0x0
_0208111C:
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_02083308
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_0208336C
	add r0, r7, r0
	add r5, r5, #0x1
	stmia r6!, {r0}
	cmp r5, #0x4
	blt _0208111C
	b _0208116E
_0208113A:
	mov r2, #0x0
	mov r3, #0x4b
	add r0, r2, #0x0
	add r1, sp, #0x0
	lsl r3, r3, #0x2
_02081144:
	ldr r5, [r4, #0x0]
	add r2, r2, #0x1
	add r5, r5, r0
	ldrsh r5, [r5, r3]
	add r0, #0xc
	cmp r2, #0x4
	stmia r1!, {r5}
	blt _02081144
	b _0208116E
_02081156:
	mov r2, #0x0
	ldr r3, _020811D4 ; =0x0000012E
	add r0, r2, #0x0
	add r1, sp, #0x0
_0208115E:
	ldr r5, [r4, #0x0]
	add r2, r2, #0x1
	add r5, r5, r0
	ldrsh r5, [r5, r3]
	add r0, #0xc
	cmp r2, #0x4
	stmia r1!, {r5}
	blt _0208115E
_0208116E:
	ldr r1, [sp, #0x0]
	mov r2, #0x0
	mov r5, #0x1
	add r3, sp, #0x4
_02081176:
	ldr r0, [r3, #0x0]
	cmp r1, r0
	bge _0208117E
	add r2, r2, #0x1
_0208117E:
	add r5, r5, #0x1
	add r3, r3, #0x4
	cmp r5, #0x4
	blt _02081176
	mov r0, #0x13
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_02081196:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _020811B4
_020811A4:
	bl ErrorHandling
_020811A8:
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_020811B4:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_020811BC: .word 0x00000121
_020811C0: .word 0x000019B8
_020811C4: .word 0x020FBBD8
_020811C8: .word 0x020FBBC8
_020811CC: .word 0x020FBBF8
_020811D0: .word 0x020FBBE8
_020811D4: .word 0x0000012E

	thumb_func_start FUN_020811D8
FUN_020811D8: ; 0x020811D8
	push {r4, lr}
	ldr r1, _02081204 ; =0x000019C4
	mov r0, #0x14
	bl FUN_02016998
	ldr r2, _02081204 ; =0x000019C4
	mov r1, #0x0
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, _02081208 ; =0x00000123
	mov r1, #0x0
	strb r1, [r4, r0]
	add r1, r0, #0x4
	mov r2, #0x1
	strb r2, [r4, r1]
	mov r1, #0x3
	add r0, r0, #0x3
	strb r1, [r4, r0]
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02081204: .word 0x000019C4
_02081208: .word 0x00000123

	thumb_func_start FUN_0208120C
FUN_0208120C: ; 0x0208120C
	ldr r3, _02081210 ; =FUN_02016A18
	bx r3
	.balign 4
_02081210: .word FUN_02016A18

	thumb_func_start FUN_02081214
FUN_02081214: ; 0x02081214
	push {r3-r7, lr}
	mov r2, #0x1
	add r6, r0, #0x0
	mov r0, #0xb
	mov r1, #0x14
	lsl r2, r2, #0xe
	bl FUN_0201681C
	bl FUN_020811D8
	add r4, r0, #0x0
	bl getseed_LC
	mov r1, #0x67
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0208285C
	ldrb r1, [r6, #0x0]
	ldr r0, _020813E4 ; =0x0000011F
	strb r1, [r4, r0]
	add r1, r0, #0x1
	ldrb r2, [r6, #0x1]
	add r0, r0, #0x2
	strb r2, [r4, r1]
	ldrb r1, [r6, #0x2]
	strb r1, [r4, r0]
	ldrb r0, [r6, #0x1]
	mov r1, #0x0
	bl FUN_02083454
	ldr r1, _020813E8 ; =0x00000122
	mov r7, #0x0
	strb r0, [r4, r1]
	add r0, r1, #0x1
	ldrb r2, [r4, r0]
	sub r0, r1, #0x6
	add r5, r4, #0x0
	strb r2, [r4, r0]
	mov r0, #0x64
	add r1, r0, #0x0
	add r1, #0xc1
	strb r0, [r4, r1]
	add r1, r0, #0x0
	add r1, #0xc1
	ldrb r2, [r4, r1]
	add r1, r0, #0x0
	add r1, #0xb9
	strb r2, [r4, r1]
	mov r1, #0x1
	add r0, #0xba
	strb r1, [r4, r0]
	ldr r1, [r6, #0x14]
	ldr r0, _020813EC ; =0x0000199C
	str r1, [r4, r0]
	add r1, r0, #0x0
	ldr r2, [r6, #0x18]
	sub r1, #0x14
	str r2, [r4, r1]
	add r1, r0, #0x0
	ldr r2, [r6, #0x1c]
	sub r1, #0x10
	str r2, [r4, r1]
	add r1, r0, #0x0
	ldr r2, [r6, #0x8]
	sub r1, #0xc
	str r2, [r4, r1]
	ldrb r2, [r6, #0x5]
	sub r1, r0, #0x4
	strb r2, [r4, r1]
	add r1, r0, #0x0
	ldr r2, [r6, #0x10]
	sub r1, #0x8
	str r2, [r4, r1]
	sub r1, r0, #0x3
	ldrb r2, [r6, #0x3]
	sub r0, r0, #0x2
	strb r2, [r4, r1]
	ldrb r1, [r6, #0x4]
	strb r1, [r4, r0]
_020812B6:
	mov r0, #0x14
	bl FUN_02026FE8
	add r1, r5, #0x0
	add r1, #0xf8
	add r7, r7, #0x1
	add r5, r5, #0x4
	str r0, [r1, #0x0]
	cmp r7, #0x4
	blt _020812B6
	mov r3, #0x12
	lsl r3, r3, #0x4
	ldrb r0, [r4, r3]
	sub r2, r3, #0x2
	sub r3, r3, #0x1
	str r0, [sp, #0x0]
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	add r0, r4, #0x0
	mov r1, #0xb
	bl FUN_02082ED0
	mov r0, #0x14
	bl FUN_0206B8AC
	mov r1, #0x56
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r7, #0x0
	add r5, r4, #0x0
_020812F2:
	mov r0, #0x14
	bl FUN_020669C0
	add r7, r7, #0x1
	stmia r5!, {r0}
	cmp r7, #0x4
	blt _020812F2
	mov r7, #0x0
	add r5, r4, #0x0
_02081304:
	mov r0, #0x14
	bl FUN_02029EE4
	mov r1, #0x57
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	add r7, r7, #0x1
	add r5, r5, #0x4
	cmp r7, #0x4
	blt _02081304
	add r0, r1, #0x0
	ldr r0, [r4, r0]
	ldr r1, [r6, #0x20]
	bl FUN_02029F9C
	ldr r0, [r6, #0x8]
	ldr r1, [r4, #0x0]
	bl FUN_02069B88
	mov r0, #0x8
	mov r1, #0x14
	bl FUN_020219F4
	add r1, r4, #0x0
	add r1, #0xe8
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	ldr r1, [r6, #0xc]
	bl FUN_02021A74
	ldr r0, [r6, #0x10]
	bl FUN_020239CC
	mov r1, #0x42
	lsl r1, r1, #0x2
	strb r0, [r4, r1]
	add r0, r1, #0x4
	mov r2, #0x0
	strb r2, [r4, r0]
	add r1, #0x17
	ldrb r1, [r4, r1]
	ldr r0, [r4, #0x0]
	bl FUN_02081540
	mov r1, #0x11
	lsl r1, r1, #0x4
	strb r0, [r4, r1]
	add r0, r4, #0x0
	bl FUN_020832EC
	cmp r0, #0x0
	ldr r0, [r6, #0x10]
	bne _0208138E
	bl FUN_020239CC
	cmp r0, #0x0
	bne _02081384
	mov r1, #0xba
	add r0, r1, #0x0
	add r0, #0x5a
	strh r1, [r4, r0]
	b _020813A8
_02081384:
	mov r1, #0xbb
	add r0, r1, #0x0
	add r0, #0x59
	strh r1, [r4, r0]
	b _020813A8
_0208138E:
	bl FUN_020239CC
	cmp r0, #0x0
	bne _020813A0
	mov r0, #0x45
	mov r1, #0x0
	lsl r0, r0, #0x2
	strh r1, [r4, r0]
	b _020813A8
_020813A0:
	mov r1, #0x61
	add r0, r1, #0x0
	add r0, #0xb3
	strh r1, [r4, r0]
_020813A8:
	ldrb r1, [r6, #0x3]
	ldrb r2, [r6, #0x4]
	add r0, r4, #0x0
	bl FUN_020813F4
	add r0, r4, #0x0
	bl FUN_020832EC
	cmp r0, #0x1
	bne _020813D0
	ldr r1, _020813F0 ; =0x00000172
	mov r5, #0x0
	mov r0, #0x3
_020813C2:
	sub r3, r0, r5
	add r2, r4, r5
	add r5, r5, #0x1
	strb r3, [r2, r1]
	cmp r5, #0x4
	blt _020813C2
	b _020813DE
_020813D0:
	ldr r0, _020813F0 ; =0x00000172
	mov r2, #0x0
_020813D4:
	add r1, r4, r2
	strb r2, [r1, r0]
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _020813D4
_020813DE:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_020813E4: .word 0x0000011F
_020813E8: .word 0x00000122
_020813EC: .word 0x0000199C
_020813F0: .word 0x00000172

	thumb_func_start FUN_020813F4
FUN_020813F4: ; 0x020813F4
	push {r3-r7, lr}
	sub sp, #0x10
	mov r3, #0x12
	add r5, r0, #0x0
	lsl r3, r3, #0x4
	ldrb r4, [r5, r3]
	str r4, [sp, #0x0]
	add r4, r3, #0x1
	ldrb r4, [r5, r4]
	sub r3, r3, #0x1
	str r4, [sp, #0x4]
	str r1, [sp, #0x8]
	str r2, [sp, #0xc]
	ldrb r3, [r5, r3]
	mov r1, #0xb
	mov r2, #0x3
	bl FUN_020828E4
	add r4, r5, #0x0
	add r4, #0x10
	mov r7, #0x1
	add r6, r5, #0x4
	add r4, #0x30
_02081422:
	ldr r1, [r6, #0x0]
	add r0, r4, #0x0
	mov r2, #0x14
	bl FUN_02082D60
	add r7, r7, #0x1
	add r6, r6, #0x4
	add r4, #0x30
	cmp r7, #0x4
	blt _02081422
	mov r6, #0x1
	add r4, r5, #0x4
	mov r7, #0x8
_0208143C:
	add r0, r4, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02081454
	add r0, r7, #0x0
	mov r1, #0x14
	bl FUN_020219F4
	add r1, r4, #0x0
	add r1, #0xe8
	str r0, [r1, #0x0]
_02081454:
	add r2, r4, #0x0
	add r2, #0xe8
	ldr r0, [r4, #0x0]
	ldr r2, [r2, #0x0]
	mov r1, #0x90
	bl FUN_020671BC
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, #0x4
	blt _0208143C
	add r0, r5, #0x0
	add r0, #0x30
	mov r2, #0x42
	mov r1, #0x1
	add r0, #0x30
	lsl r2, r2, #0x2
_02081476:
	ldrh r3, [r0, #0x0]
	add r0, #0x30
	lsl r3, r3, #0x12
	lsr r4, r3, #0x1e
	add r3, r5, r1
	add r1, r1, #0x1
	strb r4, [r3, r2]
	cmp r1, #0x4
	blt _02081476
	add r0, r5, #0x0
	add r0, #0x30
	mov r2, #0x43
	mov r1, #0x1
	add r0, #0x30
	lsl r2, r2, #0x2
_02081494:
	ldrh r3, [r0, #0x0]
	add r0, #0x30
	lsl r3, r3, #0x10
	lsr r4, r3, #0x1e
	add r3, r5, r1
	add r1, r1, #0x1
	strb r4, [r3, r2]
	cmp r1, #0x4
	blt _02081494
	add r3, r5, #0x0
	mov r1, #0x11
	mov r4, #0x1
	add r3, #0x30
	lsl r1, r1, #0x4
_020814B0:
	add r0, r3, #0x0
	add r0, #0x3e
	ldrb r2, [r0, #0x0]
	add r0, r5, r4
	add r4, r4, #0x1
	add r3, #0x30
	strb r2, [r0, r1]
	cmp r4, #0x4
	blt _020814B0
	add r2, r5, #0x0
	mov r0, #0x45
	mov r4, #0x1
	add r2, #0x30
	add r3, r5, #0x2
	lsl r0, r0, #0x2
_020814CE:
	ldrh r1, [r2, #0x18]
	add r4, r4, #0x1
	add r2, #0x30
	strh r1, [r3, r0]
	add r3, r3, #0x2
	cmp r4, #0x4
	blt _020814CE
	add r0, r5, #0x0
	mov r1, #0xb
	bl FUN_02082B90
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_020814E8
FUN_020814E8: ; 0x020814E8
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r0, #0x56
	lsl r0, r0, #0x2
	ldr r0, [r7, r0]
	bl FUN_02016A18
	mov r6, #0x57
	mov r4, #0x0
	add r5, r7, #0x0
	lsl r6, r6, #0x2
_020814FE:
	ldr r0, [r5, #0x0]
	bl FUN_02016A18
	add r0, r5, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bl FUN_02021A20
	add r0, r5, #0x0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, [r5, r6]
	bl FUN_02016A18
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _020814FE
	mov r0, #0x67
	lsl r0, r0, #0x6
	ldr r0, [r7, r0]
	bl seedr_LC
	add r0, r7, #0x0
	bl FUN_0208120C
	mov r0, #0x14
	bl FUN_020168D0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02081540
FUN_02081540: ; 0x02081540
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	add r7, r1, #0x0
	str r0, [sp, #0x0]
	mov r4, #0x0
_0208154C:
	cmp r7, #0x4
	bhi _020815B6
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0208155C: ; jump table (using 16-bit offset)
	.short _02081566 - _0208155C - 2; case 0
	.short _02081576 - _0208155C - 2; case 1
	.short _02081586 - _0208155C - 2; case 2
	.short _02081596 - _0208155C - 2; case 3
	.short _020815A6 - _0208155C - 2; case 4
_02081566:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x7a
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	b _020815BA
_02081576:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x7e
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	b _020815BA
_02081586:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x82
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	b _020815BA
_02081596:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x86
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	b _020815BA
_020815A6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x8a
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	b _020815BA
_020815B6:
	bl ErrorHandling
_020815BA:
	cmp r6, #0x0
	beq _020815CA
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r4, #0x3
	ble _0208154C
_020815CA:
	ldr r0, [sp, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020815D0
FUN_020815D0: ; 0x020815D0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02081658 ; =0x00000123
	ldrb r0, [r5, r0]
	lsl r0, r0, #0x2
	add r0, r5, r0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bl FUN_02027740
	mov r0, #0x14
	mov r1, #0x28
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x28
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, _02081658 ; =0x00000123
	ldrb r1, [r5, r0]
	lsl r1, r1, #0x2
	ldr r1, [r5, r1]
	str r1, [r4, #0x0]
	ldrb r1, [r5, r0]
	lsl r1, r1, #0x2
	add r1, r5, r1
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	str r1, [r4, #0x4]
	sub r1, r0, #0x1
	ldrb r1, [r5, r1]
	str r1, [r4, #0x8]
	add r1, r0, #0x0
	add r1, #0x4e
	ldrb r1, [r5, r1]
	cmp r1, #0x1
	bne _02081620
	mov r0, #0x4
	b _02081624
_02081620:
	sub r0, r0, #0x3
	ldrb r0, [r5, r0]
_02081624:
	str r0, [r4, #0xc]
	ldr r0, _0208165C ; =0x00000121
	ldrb r1, [r5, r0]
	sub r0, r0, #0x2
	str r1, [r4, #0x10]
	ldrb r0, [r5, r0]
	str r0, [r4, #0x14]
	ldr r0, _02081660 ; =0x0000199C
	ldr r0, [r5, r0]
	bl FUN_0202708C
	ldr r1, _02081664 ; =0x000019A0
	str r0, [r4, #0x18]
	add r0, r5, r1
	str r0, [r4, #0x1c]
	add r0, r1, #0x0
	sub r0, #0x18
	ldr r0, [r5, r0]
	str r0, [r4, #0x20]
	add r0, r1, #0x0
	sub r0, #0xc
	ldr r0, [r5, r0]
	add r1, #0x18
	str r0, [r4, #0x24]
	str r4, [r5, r1]
	pop {r3-r5, pc}
	.balign 4
_02081658: .word 0x00000123
_0208165C: .word 0x00000121
_02081660: .word 0x0000199C
_02081664: .word 0x000019A0

	thumb_func_start FUN_02081668
FUN_02081668: ; 0x02081668
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0208167C ; =0x000019B8
	ldr r0, [r4, r0]
	bl FUN_02016A18
	ldr r0, _0208167C ; =0x000019B8
	mov r1, #0x0
	str r1, [r4, r0]
	pop {r4, pc}
	.balign 4
_0208167C: .word 0x000019B8

	thumb_func_start FUN_02081680
FUN_02081680: ; 0x02081680
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r2, _020819E8 ; =0x00000176
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, r2]
	cmp r0, #0x2f
	bls _02081692
	b _02081D24
_02081692:
	add r3, r0, r0
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0208169E: ; jump table (using 16-bit offset)
	.short _020816FE - _0208169E - 2; case 0
	.short _02081716 - _0208169E - 2; case 1
	.short _0208172C - _0208169E - 2; case 2
	.short _02081742 - _0208169E - 2; case 3
	.short _0208175E - _0208169E - 2; case 4
	.short _02081776 - _0208169E - 2; case 5
	.short _0208178C - _0208169E - 2; case 6
	.short _020817A8 - _0208169E - 2; case 7
	.short _020817C4 - _0208169E - 2; case 8
	.short _020817DC - _0208169E - 2; case 9
	.short _020817F2 - _0208169E - 2; case 10
	.short _02081822 - _0208169E - 2; case 11
	.short _02081838 - _0208169E - 2; case 12
	.short _02081850 - _0208169E - 2; case 13
	.short _02081866 - _0208169E - 2; case 14
	.short _02081884 - _0208169E - 2; case 15
	.short _020818A0 - _0208169E - 2; case 16
	.short _020818B8 - _0208169E - 2; case 17
	.short _020818CE - _0208169E - 2; case 18
	.short _0208190A - _0208169E - 2; case 19
	.short _02081940 - _0208169E - 2; case 20
	.short _02081958 - _0208169E - 2; case 21
	.short _0208196E - _0208169E - 2; case 22
	.short _0208198E - _0208169E - 2; case 23
	.short _020819DE - _0208169E - 2; case 24
	.short _02081A04 - _0208169E - 2; case 25
	.short _02081A1A - _0208169E - 2; case 26
	.short _02081A54 - _0208169E - 2; case 27
	.short _02081A8A - _0208169E - 2; case 28
	.short _02081AB6 - _0208169E - 2; case 29
	.short _02081ACC - _0208169E - 2; case 30
	.short _02081AE8 - _0208169E - 2; case 31
	.short _02081B04 - _0208169E - 2; case 32
	.short _02081B1C - _0208169E - 2; case 33
	.short _02081B32 - _0208169E - 2; case 34
	.short _02081B6C - _0208169E - 2; case 35
	.short _02081BA2 - _0208169E - 2; case 36
	.short _02081BBA - _0208169E - 2; case 37
	.short _02081BD0 - _0208169E - 2; case 38
	.short _02081BFA - _0208169E - 2; case 39
	.short _02081C16 - _0208169E - 2; case 40
	.short _02081C2E - _0208169E - 2; case 41
	.short _02081C44 - _0208169E - 2; case 42
	.short _02081C86 - _0208169E - 2; case 43
	.short _02081CBC - _0208169E - 2; case 44
	.short _02081CD4 - _0208169E - 2; case 45
	.short _02081CEA - _0208169E - 2; case 46
	.short _02081D08 - _0208169E - 2; case 47
_020816FE:
	mov r0, #0x5
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081716:
	mov r0, #0x5
	bl FUN_020315D8
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208172C:
	add r0, r4, #0x0
	bl FUN_02083630
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081742:
	ldr r0, _020819EC ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _0208180C
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_0208175E:
	mov r0, #0x6
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081776:
	mov r0, #0x6
	bl FUN_020315D8
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208178C:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	bl FUN_020836BC
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020817A8:
	ldr r0, _020819EC ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _0208180C
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_020817C4:
	mov r0, #0x7
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020817DC:
	mov r0, #0x7
	bl FUN_020315D8
	cmp r0, #0x1
	bne _0208180C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020817F2:
	add r3, r2, #0x0
	sub r3, #0x53
	ldrb r5, [r4, r3]
	add r3, r2, #0x0
	sub r3, #0x5a
	ldrb r3, [r4, r3]
	cmp r5, r3
	bne _0208181A
	add r0, r4, #0x0
	bl FUN_0208373C
	cmp r0, #0x1
	beq _0208180E
_0208180C:
	b _02081DBC
_0208180E:
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208181A:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081822:
	ldr r0, _020819EC ; =0x00000584
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	beq _02081912
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081838:
	mov r0, #0x8
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081850:
	mov r0, #0x8
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081866:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r2, r4, #0x0
	add r0, r4, #0x0
	add r2, #0x10
	bl FUN_020837B4
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081884:
	ldr r0, _020819EC ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081912
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_020818A0:
	mov r0, #0x9
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020818B8:
	mov r0, #0x9
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020818CE:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081902
	add r0, r2, #0x2
	ldr r1, [r4, r0]
	add r3, r4, #0x0
	mov r2, #0x30
	add r3, #0x10
	mul r2, r1
	add r0, r4, #0x0
	add r2, r3, r2
	bl FUN_020837B4
	cmp r0, #0x1
	bne _02081912
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081902:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_0208190A:
	ldr r1, _020819EC ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081914
_02081912:
	b _02081DBC
_02081914:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081932
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081932:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081940:
	mov r0, #0xa
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081958:
	mov r0, #0xa
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208196E:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r2, r4, #0x0
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	bl FUN_020838B4
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_0208198E:
	ldr r0, _020819EC ; =0x00000584
	sub r2, #0x4f
	ldrb r1, [r4, r2]
	ldrb r0, [r4, r0]
	cmp r0, r1
	blo _02081A5C
	mov r5, #0x0
	cmp r1, #0x0
	ble _020819CC
	add r6, r4, #0x0
_020819A2:
	add r0, r5, #0x0
	bl FUN_0202DFA4
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bl FUN_02021A4C
	add r1, r6, #0x0
	add r1, #0xe8
	ldr r1, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02023990
	ldr r0, _020819F0 ; =0x00000127
	add r5, r5, #0x1
	ldrb r0, [r4, r0]
	add r6, r6, #0x4
	cmp r5, r0
	blt _020819A2
_020819CC:
	ldr r0, _020819EC ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _020819E8 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_020819DE:
	mov r0, #0xb
	bl FUN_02031588
	ldr r0, _020819EC ; =0x00000584
	b _020819F4
	.balign 4
_020819E8: .word 0x00000176
_020819EC: .word 0x00000584
_020819F0: .word 0x00000127
_020819F4:
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081A04:
	mov r0, #0xb
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081A1A:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081A4C
	add r0, r2, #0x2
	ldr r1, [r4, r0]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	add r2, r4, r2
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	bl FUN_020838B4
	cmp r0, #0x1
	bne _02081A5C
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081A4C:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081A54:
	ldr r1, _02081D2C ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081A5E
_02081A5C:
	b _02081DBC
_02081A5E:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081A7C
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081A7C:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081A8A:
	bl FUN_02029EC4
	add r2, r0, #0x0
	mov r0, #0x57
	lsl r0, r0, #0x2
	ldr r1, _02081D30 ; =0x00000585
	ldr r0, [r4, r0]
	add r1, r4, r1
	bl MI_CpuCopy8
	mov r0, #0xc
	bl FUN_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081AB6:
	mov r0, #0xc
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081ACC:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_02083AD4
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081AE8:
	ldr r0, _02081D2C ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081B74
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081B04:
	mov r0, #0xd
	bl FUN_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081B1C:
	mov r0, #0xd
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081B32:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081B64
	add r0, r2, #0x2
	ldr r1, [r4, r0]
	sub r2, #0x1a
	lsl r3, r1, #0x2
	add r3, r4, r3
	ldr r2, [r3, r2]
	add r0, r4, #0x0
	bl FUN_02083AD4
	cmp r0, #0x1
	bne _02081B74
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081B64:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081B6C:
	ldr r1, _02081D2C ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081B76
_02081B74:
	b _02081DBC
_02081B76:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081B94
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081B94:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081BA2:
	mov r0, #0xe
	bl FUN_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081BBA:
	mov r0, #0xe
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081BD0:
	add r2, sp, #0x8
	add r0, r4, #0x0
	mov r1, #0x0
	add r2, #0x2
	bl FUN_02082894
	ldr r1, _02081D34 ; =0x00000123
	add r2, sp, #0x8
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	add r2, #0x2
	bl FUN_02083B48
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081BFA:
	ldr r0, _02081D2C ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081C8E
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081C16:
	mov r0, #0xf
	bl FUN_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081C2E:
	mov r0, #0xf
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081C44:
	add r1, r2, #0x0
	sub r1, #0x53
	ldrb r3, [r4, r1]
	add r1, r2, #0x0
	sub r1, #0x5a
	ldrb r1, [r4, r1]
	cmp r3, r1
	bne _02081C7E
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	add r2, sp, #0x4
	bl FUN_02082894
	mov r1, #0x5e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	add r2, sp, #0x4
	bl FUN_02083B48
	cmp r0, #0x1
	bne _02081C8E
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081C7E:
	add r0, r0, #0x1
	add sp, #0x10
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081C86:
	ldr r1, _02081D2C ; =0x00000584
	ldrb r0, [r4, r1]
	cmp r0, #0x0
	bne _02081C90
_02081C8E:
	b _02081DBC
_02081C90:
	mov r0, #0x0
	strb r0, [r4, r1]
	add r1, r2, #0x2
	ldr r1, [r4, r1]
	add r3, r1, #0x1
	add r1, r2, #0x2
	str r3, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0x4
	bge _02081CAE
	ldrb r0, [r4, r2]
	add sp, #0x10
	sub r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081CAE:
	add r1, r2, #0x2
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081CBC:
	mov r0, #0x10
	bl FUN_02031588
	ldr r0, _02081D2C ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081CD4:
	mov r0, #0x10
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02081DBC
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081CEA:
	sub r2, #0x53
	ldrb r1, [r4, r2]
	add r2, r4, #0x0
	add r0, r4, #0x0
	add r2, #0xd0
	bl FUN_02083834
	cmp r0, #0x1
	bne _02081DBC
	ldr r0, _02081D28 ; =0x00000176
	add sp, #0x10
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r7, pc}
_02081D08:
	ldr r0, _02081D2C ; =0x00000584
	add r1, r2, #0x0
	sub r1, #0x4f
	ldrb r3, [r4, r0]
	ldrb r1, [r4, r1]
	cmp r3, r1
	blo _02081DBC
	mov r1, #0x0
	strb r1, [r4, r0]
	ldrb r0, [r4, r2]
	add sp, #0x10
	add r0, r0, #0x1
	strb r0, [r4, r2]
	pop {r3-r7, pc}
_02081D24:
	ldr r0, _02081D38 ; =0x00000127
	b _02081D3C
	.balign 4
_02081D28: .word 0x00000176
_02081D2C: .word 0x00000584
_02081D30: .word 0x00000585
_02081D34: .word 0x00000123
_02081D38: .word 0x00000127
_02081D3C:
	mov r5, #0x0
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	ble _02081D62
	mov r7, #0x42
	lsl r7, r7, #0x2
	add r6, r7, #0x0
	add r6, #0x1f
_02081D4C:
	add r0, r5, #0x0
	bl FUN_0202DFA4
	bl FUN_020239CC
	add r1, r4, r5
	strb r0, [r1, r7]
	ldrb r0, [r4, r6]
	add r5, r5, #0x1
	cmp r5, r0
	blt _02081D4C
_02081D62:
	cmp r5, #0x4
	bge _02081D86
	add r1, r4, #0x0
	mov r0, #0x30
	add r1, #0x30
	mul r0, r5
	add r0, r1, r0
	mov r1, #0x42
	lsl r1, r1, #0x2
_02081D74:
	ldrh r2, [r0, #0x0]
	add r0, #0x30
	lsl r2, r2, #0x12
	lsr r3, r2, #0x1e
	add r2, r4, r5
	add r5, r5, #0x1
	strb r3, [r2, r1]
	cmp r5, #0x4
	blt _02081D74
_02081D86:
	mov r0, #0x47
	lsl r0, r0, #0x2
	ldrb r2, [r4, r0]
	ldr r1, _02081DC0 ; =0x000019B4
	strb r2, [r4, r1]
	add r2, r0, #0x0
	add r2, #0x8
	ldrb r3, [r4, r2]
	add r2, r1, #0x1
	strb r3, [r4, r2]
	add r2, r1, #0x2
	mov r3, #0x1
	strb r3, [r4, r2]
	add r2, r0, #0x0
	add r2, #0xb
	ldrb r2, [r4, r2]
	add r1, r1, #0x3
	strb r2, [r4, r1]
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x64
	str r2, [r4, r1]
	add r0, #0x5a
	strb r2, [r4, r0]
	ldr r0, [sp, #0x0]
	bl FUN_0200CAB4
_02081DBC:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02081DC0: .word 0x000019B4

	thumb_func_start FUN_02081DC4
FUN_02081DC4: ; 0x02081DC4
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02081DD4
	mov r0, #0x0
	pop {r3-r7, pc}
_02081DD4:
	ldr r0, _02081EA4 ; =0x00000171
	mov r1, #0x1
	strb r1, [r6, r0]
	bl FUN_02030F20
	add r4, r0, #0x0
	bl FUN_02031190
	mov r5, #0x0
	str r0, [sp, #0x0]
	cmp r4, #0x0
	ble _02081E0A
_02081DEC:
	add r0, r5, #0x0
	bl FUN_0202DFA4
	add r7, r0, #0x0
	bne _02081DFA
	bl ErrorHandling
_02081DFA:
	add r0, r7, #0x0
	bl FUN_02023A88
	cmp r0, #0x0
	beq _02081E0A
	add r5, r5, #0x1
	cmp r5, r4
	blt _02081DEC
_02081E0A:
	cmp r5, r4
	beq _02081E12
	mov r1, #0x0
	b _02081E14
_02081E12:
	mov r1, #0x1
_02081E14:
	ldr r0, _02081EA8 ; =0x00001999
	mov r5, #0x0
	strb r1, [r6, r0]
	cmp r4, #0x0
	ble _02081E3C
_02081E1E:
	add r0, r5, #0x0
	bl FUN_0202DFA4
	add r7, r0, #0x0
	bne _02081E2C
	bl ErrorHandling
_02081E2C:
	add r0, r7, #0x0
	bl FUN_02023A9C
	cmp r0, #0x0
	beq _02081E3C
	add r5, r5, #0x1
	cmp r5, r4
	blt _02081E1E
_02081E3C:
	cmp r5, r4
	beq _02081E44
	mov r1, #0x0
	b _02081E46
_02081E44:
	mov r1, #0x1
_02081E46:
	ldr r0, _02081EAC ; =0x0000199A
	ldr r2, _02081EA8 ; =0x00001999
	strb r1, [r6, r0]
	ldrb r1, [r6, r2]
	add r2, r2, #0x1
	ldrb r2, [r6, r2]
	add r0, r6, #0x0
	bl FUN_020813F4
	ldr r0, [sp, #0x0]
	mov r1, #0x49
	lsl r0, r0, #0x18
	mov r2, #0x4
	lsr r0, r0, #0x18
	lsl r1, r1, #0x2
	sub r3, r2, r4
	strb r0, [r6, r1]
	add r2, r1, #0x2
	strb r3, [r6, r2]
	add r2, r1, #0x3
	strb r4, [r6, r2]
	sub r1, r1, #0x1
	strb r0, [r6, r1]
	mov r1, #0x64
	add r0, r1, #0x0
	add r0, #0xc1
	strb r1, [r6, r0]
	add r1, #0xbc
	ldrb r0, [r6, r1]
	mov r1, #0x1
	bl FUN_02083454
	ldr r1, _02081EB0 ; =0x00000122
	strb r0, [r6, r1]
	add r0, r6, #0x0
	bl FUN_020834D0
	ldr r0, _02081EB4 ; =FUN_02081680
	add r1, r6, #0x0
	mov r2, #0xa
	bl FUN_0200CA44
	mov r1, #0x6
	lsl r1, r1, #0x6
	str r0, [r6, r1]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_02081EA4: .word 0x00000171
_02081EA8: .word 0x00001999
_02081EAC: .word 0x0000199A
_02081EB0: .word 0x00000122
_02081EB4: .word FUN_02081680

	thumb_func_start FUN_02081EB8
FUN_02081EB8: ; 0x02081EB8
	ldr r3, _02081EBC ; =FUN_02081EC0
	bx r3
	.balign 4
_02081EBC: .word FUN_02081EC0

	thumb_func_start FUN_02081EC0
FUN_02081EC0: ; 0x02081EC0
	mov r1, #0x6
	lsl r1, r1, #0x6
	ldr r0, [r0, r1]
	cmp r0, #0x0
	bne _02081ECE
	mov r0, #0x1
	bx lr
_02081ECE:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02081ED4
FUN_02081ED4: ; 0x02081ED4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02081EE6
	bl ErrorHandling
_02081EE6:
	ldr r0, _02081F00 ; =0x00000176
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02081F04 ; =FUN_02081F08
	add r1, r4, #0x0
	mov r2, #0xa
	bl FUN_0200CA44
	mov r1, #0x6
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_02081F00: .word 0x00000176
_02081F04: .word FUN_02081F08

	thumb_func_start FUN_02081F08
FUN_02081F08: ; 0x02081F08
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _02082014 ; =0x00000176
	ldrb r2, [r4, r1]
	cmp r2, #0x7
	bhi _02082000
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02081F20: ; jump table (using 16-bit offset)
	.short _02081F30 - _02081F20 - 2; case 0
	.short _02081F46 - _02081F20 - 2; case 1
	.short _02081F5A - _02081F20 - 2; case 2
	.short _02081F7A - _02081F20 - 2; case 3
	.short _02081F94 - _02081F20 - 2; case 4
	.short _02081FAA - _02081F20 - 2; case 5
	.short _02081FBE - _02081F20 - 2; case 6
	.short _02081FEC - _02081F20 - 2; case 7
_02081F30:
	mov r0, #0x11
	bl FUN_02031588
	ldr r0, _02082018 ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081F46:
	mov r0, #0x11
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081F5A:
	sub r1, #0x53
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	lsl r2, r1, #0x2
	add r2, r4, r2
	add r2, #0xf8
	ldr r2, [r2, #0x0]
	bl FUN_02083930
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081F7A:
	ldr r0, _02082018 ; =0x00000584
	add r2, r1, #0x0
	sub r2, #0x4f
	ldrb r3, [r4, r0]
	ldrb r2, [r4, r2]
	cmp r3, r2
	blo _02082010
	mov r2, #0x0
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	add r0, r0, #0x1
	strb r0, [r4, r1]
	pop {r4, pc}
_02081F94:
	mov r0, #0x12
	bl FUN_02031588
	ldr r0, _02082018 ; =0x00000584
	mov r1, #0x0
	strb r1, [r4, r0]
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081FAA:
	mov r0, #0x12
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081FBE:
	add r0, r1, #0x0
	sub r0, #0x53
	ldrb r3, [r4, r0]
	add r0, r1, #0x0
	sub r0, #0x5a
	ldrb r0, [r4, r0]
	cmp r3, r0
	bne _02081FE6
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0xf8
	bl FUN_020839C0
	cmp r0, #0x1
	bne _02082010
	ldr r0, _02082014 ; =0x00000176
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4, pc}
_02081FE6:
	add r0, r2, #0x1
	strb r0, [r4, r1]
	pop {r4, pc}
_02081FEC:
	ldr r0, _02082018 ; =0x00000584
	ldrb r2, [r4, r0]
	cmp r2, #0x0
	beq _02082010
	mov r2, #0x0
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	add r0, r0, #0x1
	strb r0, [r4, r1]
	pop {r4, pc}
_02082000:
	mov r1, #0x6
	mov r2, #0x0
	lsl r1, r1, #0x6
	str r2, [r4, r1]
	sub r1, #0xa
	strb r2, [r4, r1]
	bl FUN_0200CAB4
_02082010:
	pop {r4, pc}
	nop
_02082014: .word 0x00000176
_02082018: .word 0x00000584

	thumb_func_start FUN_0208201C
FUN_0208201C: ; 0x0208201C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r2, #0x0
	lsl r2, r4, #0x3
	add r2, r5, r2
	add r2, #0xd0
	ldrh r2, [r2, #0x0]
	add r1, r3, #0x0
	bl FUN_0200B244
	pop {r3-r5, pc}

	thumb_func_start FUN_02082034
FUN_02082034: ; 0x02082034
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020832E4
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	lsl r2, r3, #0x2
	add r4, r5, r3
	mov r3, #0x42
	add r2, r5, r2
	lsl r3, r3, #0x2
	add r2, #0xe8
	ldrb r3, [r4, r3]
	ldr r2, [r2, #0x0]
	add r1, r6, #0x0
	bl FUN_0200ABB4
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0208206C
FUN_0208206C: ; 0x0208206C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020832E4
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020690E4
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0200ACF8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02082090
FUN_02082090: ; 0x02082090
	push {r3-r5, lr}
	add r4, r2, #0x0
	mov r2, #0x12
	add r3, r0, #0x0
	lsl r2, r2, #0x4
	add r5, r1, #0x0
	add r1, r2, #0x1
	ldrb r0, [r3, r2]
	add r2, #0x51
	ldrb r1, [r3, r1]
	ldrb r2, [r3, r2]
	bl FUN_02083228
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200B278
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020820B8
FUN_020820B8: ; 0x020820B8
	push {r3-r5, lr}
	add r5, r1, #0x0
	ldr r1, _020820D8 ; =0x0000011F
	add r3, r0, #0x0
	ldrb r0, [r3, r1]
	add r1, r1, #0x2
	ldrb r1, [r3, r1]
	add r4, r2, #0x0
	bl FUN_020832A4
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200B2AC
	pop {r3-r5, pc}
	.balign 4
_020820D8: .word 0x0000011F

	thumb_func_start FUN_020820DC
FUN_020820DC: ; 0x020820DC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0x13
	add r6, r2, #0x0
	mov r0, #0x0
	add r3, r5, #0x0
	lsl r1, r1, #0x4
_020820EC:
	ldrb r2, [r3, r1]
	cmp r2, #0x0
	beq _020820FA
	add r0, r0, #0x1
	add r3, #0xc
	cmp r0, #0x4
	blt _020820EC
_020820FA:
	bl FUN_020832DC
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02082034
	pop {r4-r6, pc}

	thumb_func_start FUN_0208210C
FUN_0208210C: ; 0x0208210C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r1, #0x13
	add r6, r2, #0x0
	mov r0, #0x0
	add r3, r5, #0x0
	lsl r1, r1, #0x4
_0208211C:
	ldrb r2, [r3, r1]
	cmp r2, #0x0
	beq _0208212A
	add r0, r0, #0x1
	add r3, #0xc
	cmp r0, #0x4
	blt _0208211C
_0208212A:
	bl FUN_020832DC
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_0208206C
	pop {r4-r6, pc}

	thumb_func_start FUN_0208213C
FUN_0208213C: ; 0x0208213C
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02082140
FUN_02082140: ; 0x02082140
	push {r3, lr}
	ldr r2, _02082154 ; =0x00000171
	ldrb r0, [r0, r2]
	cmp r0, #0x0
	beq _02082150
	add r0, r1, #0x0
	bl FUN_02031588
_02082150:
	pop {r3, pc}
	nop
_02082154: .word 0x00000171

	thumb_func_start FUN_02082158
FUN_02082158: ; 0x02082158
	push {r3, lr}
	ldr r2, _02082178 ; =0x00000171
	ldrb r0, [r0, r2]
	cmp r0, #0x0
	bne _02082166
	mov r0, #0x1
	pop {r3, pc}
_02082166:
	add r0, r1, #0x0
	bl FUN_020315D8
	cmp r0, #0x1
	bne _02082174
	mov r0, #0x1
	pop {r3, pc}
_02082174:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02082178: .word 0x00000171

	thumb_func_start FUN_0208217C
FUN_0208217C: ; 0x0208217C
	ldr r2, _0208218C ; =0x00000123
	mov r1, #0xc
	ldrb r3, [r0, r2]
	add r2, #0xd
	mul r1, r3
	add r0, r0, r1
	ldrb r0, [r0, r2]
	bx lr
	.balign 4
_0208218C: .word 0x00000123

	thumb_func_start FUN_02082190
FUN_02082190: ; 0x02082190
	push {r3, lr}
	mov r1, #0x13
	mov r3, #0x0
	lsl r1, r1, #0x4
_02082198:
	ldrb r2, [r0, r1]
	cmp r2, #0x0
	bne _020821A6
	add r0, r3, #0x0
	bl FUN_020832DC
	pop {r3, pc}
_020821A6:
	add r3, r3, #0x1
	add r0, #0xc
	cmp r3, #0x4
	blt _02082198
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020821B4
FUN_020821B4: ; 0x020821B4
	ldr r1, _020821BC ; =0x00000123
	ldr r3, _020821C0 ; =FUN_020832DC
	ldrb r0, [r0, r1]
	bx r3
	.balign 4
_020821BC: .word 0x00000123
_020821C0: .word FUN_020832DC

	thumb_func_start FUN_020821C4
FUN_020821C4: ; 0x020821C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_020832E4
	lsl r0, r0, #0x1
	add r1, r4, r0
	mov r0, #0x45
	lsl r0, r0, #0x2
	ldrh r0, [r1, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020821DC
FUN_020821DC: ; 0x020821DC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_020832E4
	add r1, r4, r0
	mov r0, #0x11
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	pop {r4, pc}

	thumb_func_start FUN_020821F0
FUN_020821F0: ; 0x020821F0
	push {r3, lr}
	ldr r1, _02082210 ; =0x00000171
	ldrb r1, [r0, r1]
	cmp r1, #0x1
	bne _020821FE
	mov r0, #0x1
	pop {r3, pc}
_020821FE:
	bl FUN_020832EC
	cmp r0, #0x1
	bne _0208220A
	mov r0, #0x2
	pop {r3, pc}
_0208220A:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02082210: .word 0x00000171

	thumb_func_start FUN_02082214
FUN_02082214: ; 0x02082214
	push {r4-r5}
	mov r4, #0x12
	lsl r4, r4, #0x4
	ldrb r5, [r0, r4]
	strh r5, [r1, #0x0]
	sub r1, r4, #0x1
	ldrb r1, [r0, r1]
	strh r1, [r2, #0x0]
	add r1, r4, #0x1
	ldrb r1, [r0, r1]
	strh r1, [r3, #0x0]
	ldr r1, _02082238 ; =0x00001998
	ldrb r1, [r0, r1]
	ldr r0, [sp, #0x8]
	strh r1, [r0, #0x0]
	pop {r4-r5}
	bx lr
	nop
_02082238: .word 0x00001998

	thumb_func_start FUN_0208223C
FUN_0208223C: ; 0x0208223C
	ldr r1, _02082244 ; =0x00000171
	ldr r3, _02082248 ; =FUN_020833D4
	ldrb r0, [r0, r1]
	bx r3
	.balign 4
_02082244: .word 0x00000171
_02082248: .word FUN_020833D4

	thumb_func_start FUN_0208224C
FUN_0208224C: ; 0x0208224C
	ldr r3, _02082250 ; =FUN_02083404
	bx r3
	.balign 4
_02082250: .word FUN_02083404

	thumb_func_start FUN_02082254
FUN_02082254: ; 0x02082254
	push {r4, lr}
	mov r1, #0x12
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldrb r0, [r4, r1]
	sub r1, r1, #0x1
	ldrb r1, [r4, r1]
	bl FUN_0208341C
	add r1, r0, #0x0
	ldr r0, _02082280 ; =0x00001990
	mov r2, #0x0
	ldr r0, [r4, r0]
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0208227A
	mov r0, #0x1
	pop {r4, pc}
_0208227A:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02082280: .word 0x00001990

	thumb_func_start FUN_02082284
FUN_02082284: ; 0x02082284
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, _020822EC ; =0x0000011F
	add r5, r2, #0x0
	ldrb r2, [r0, r1]
	cmp r2, #0x4
	bhi _020822D0
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0208229E: ; jump table (using 16-bit offset)
	.short _020822A8 - _0208229E - 2; case 0
	.short _020822B0 - _0208229E - 2; case 1
	.short _020822B8 - _0208229E - 2; case 2
	.short _020822C0 - _0208229E - 2; case 3
	.short _020822C8 - _0208229E - 2; case 4
_020822A8:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x21
	b _020822D6
_020822B0:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x25
	b _020822D6
_020822B8:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x29
	b _020822D6
_020822C0:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x2d
	b _020822D6
_020822C8:
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	add r0, #0x31
	b _020822D6
_020822D0:
	bl ErrorHandling
	pop {r3-r5, pc}
_020822D6:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r1, #0x3
	bl FUN_0207FC5C
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0200AD94
	pop {r3-r5, pc}
	.balign 4
_020822EC: .word 0x0000011F

	thumb_func_start FUN_020822F0
FUN_020822F0: ; 0x020822F0
	push {r3-r5, lr}
	mov r4, #0x64
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0xbf
	ldrb r1, [r5, r0]
	mov r0, #0xc
	mul r0, r1
	add r1, r5, r0
	add r0, r4, #0x0
	add r0, #0xcc
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02082310
	ldr r0, _0208243C ; =0x0000FFFF
	pop {r3-r5, pc}
_02082310:
	add r0, r4, #0x0
	add r0, #0xbb
	ldrb r0, [r5, r0]
	cmp r0, #0x4
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082326: ; jump table (using 16-bit offset)
	.short _02082330 - _02082326 - 2; case 0
	.short _0208235E - _02082326 - 2; case 1
	.short _0208238C - _02082326 - 2; case 2
	.short _020823BA - _02082326 - 2; case 3
	.short _020823E8 - _02082326 - 2; case 4
_02082330:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082346: ; jump table (using 16-bit offset)
	.short _0208234E - _02082346 - 2; case 0
	.short _02082352 - _02082346 - 2; case 1
	.short _02082356 - _02082346 - 2; case 2
	.short _0208235A - _02082346 - 2; case 3
_0208234E:
	mov r4, #0x49
	b _02082414
_02082352:
	mov r4, #0x4e
	b _02082414
_02082356:
	mov r4, #0x53
	b _02082414
_0208235A:
	mov r4, #0x58
	b _02082414
_0208235E:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082374: ; jump table (using 16-bit offset)
	.short _0208237C - _02082374 - 2; case 0
	.short _02082380 - _02082374 - 2; case 1
	.short _02082384 - _02082374 - 2; case 2
	.short _02082388 - _02082374 - 2; case 3
_0208237C:
	mov r4, #0x4a
	b _02082414
_02082380:
	mov r4, #0x4f
	b _02082414
_02082384:
	mov r4, #0x54
	b _02082414
_02082388:
	mov r4, #0x59
	b _02082414
_0208238C:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020823A2: ; jump table (using 16-bit offset)
	.short _020823AA - _020823A2 - 2; case 0
	.short _020823AE - _020823A2 - 2; case 1
	.short _020823B2 - _020823A2 - 2; case 2
	.short _020823B6 - _020823A2 - 2; case 3
_020823AA:
	mov r4, #0x48
	b _02082414
_020823AE:
	mov r4, #0x4d
	b _02082414
_020823B2:
	mov r4, #0x52
	b _02082414
_020823B6:
	mov r4, #0x57
	b _02082414
_020823BA:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020823D0: ; jump table (using 16-bit offset)
	.short _020823D8 - _020823D0 - 2; case 0
	.short _020823DC - _020823D0 - 2; case 1
	.short _020823E0 - _020823D0 - 2; case 2
	.short _020823E4 - _020823D0 - 2; case 3
_020823D8:
	mov r4, #0x4c
	b _02082414
_020823DC:
	mov r4, #0x51
	b _02082414
_020823E0:
	mov r4, #0x56
	b _02082414
_020823E4:
	mov r4, #0x5b
	b _02082414
_020823E8:
	add r0, r4, #0x0
	add r0, #0xbc
	ldrb r0, [r5, r0]
	cmp r0, #0x3
	bhi _02082414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020823FE: ; jump table (using 16-bit offset)
	.short _02082406 - _020823FE - 2; case 0
	.short _0208240A - _020823FE - 2; case 1
	.short _0208240E - _020823FE - 2; case 2
	.short _02082412 - _020823FE - 2; case 3
_02082406:
	mov r4, #0x4b
	b _02082414
_0208240A:
	mov r4, #0x50
	b _02082414
_0208240E:
	mov r4, #0x55
	b _02082414
_02082412:
	mov r4, #0x5a
_02082414:
	cmp r4, #0x64
	bne _0208241C
	bl ErrorHandling
_0208241C:
	ldr r0, _02082440 ; =0x0000198C
	ldr r0, [r5, r0]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_020270D8
	cmp r0, #0x0
	bne _02082438
	ldr r0, _0208243C ; =0x0000FFFF
	pop {r3-r5, pc}
_02082438:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_0208243C: .word 0x0000FFFF
_02082440: .word 0x0000198C

	thumb_func_start FUN_02082444
FUN_02082444: ; 0x02082444
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _020824F0 ; =0x000019BC
	add r6, r1, #0x0
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _02082456
	bl ErrorHandling
_02082456:
	mov r0, #0x4
	mov r1, #0x10
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x10
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r6, #0x0
	bl FUN_020832E4
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xc]
	mov r1, #0x43
	lsl r1, r1, #0x2
	add r0, r5, r0
	ldrb r2, [r0, r1]
	mov r0, #0x1
	and r0, r2
	add r2, r1, #0x0
	add r2, #0x65
	ldrb r2, [r5, r2]
	cmp r2, #0x1
	bne _02082494
	mov r1, #0x6
	ldr r2, _020824F4 ; =0x020FBBAC
	mul r1, r0
	add r0, r2, r1
	str r0, [r4, #0x4]
	b _020824DC
_02082494:
	add r1, #0x14
	ldrb r1, [r5, r1]
	cmp r1, #0x3
	bhi _020824D2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020824A8: ; jump table (using 16-bit offset)
	.short _020824B0 - _020824A8 - 2; case 0
	.short _020824BC - _020824A8 - 2; case 1
	.short _020824C6 - _020824A8 - 2; case 2
	.short _020824D2 - _020824A8 - 2; case 3
_020824B0:
	lsl r1, r0, #0x1
	ldr r2, _020824F8 ; =0x020FBB90
	add r0, r0, r1
	add r0, r2, r0
	str r0, [r4, #0x4]
	b _020824DC
_020824BC:
	ldr r1, _020824FC ; =0x020FBB98
	lsl r0, r0, #0x2
	add r0, r1, r0
	str r0, [r4, #0x4]
	b _020824DC
_020824C6:
	lsl r1, r0, #0x2
	ldr r2, _02082500 ; =0x020FBBA0
	add r0, r0, r1
	add r0, r2, r0
	str r0, [r4, #0x4]
	b _020824DC
_020824D2:
	mov r1, #0x6
	ldr r2, _020824F4 ; =0x020FBBAC
	mul r1, r0
	add r0, r2, r1
	str r0, [r4, #0x4]
_020824DC:
	ldr r0, _02082504 ; =FUN_0208251C
	add r1, r5, #0x0
	mov r2, #0x64
	bl FUN_0200CA44
	str r0, [r4, #0x0]
	ldr r0, _020824F0 ; =0x000019BC
	str r4, [r5, r0]
	pop {r4-r6, pc}
	nop
_020824F0: .word 0x000019BC
_020824F4: .word 0x020FBBAC
_020824F8: .word 0x020FBB90
_020824FC: .word 0x020FBB98
_02082500: .word 0x020FBBA0
_02082504: .word FUN_0208251C

	thumb_func_start FUN_02082508
FUN_02082508: ; 0x02082508
	ldr r1, _02082518 ; =0x000019BC
	ldr r0, [r0, r1]
	cmp r0, #0x0
	bne _02082514
	mov r0, #0x1
	bx lr
_02082514:
	mov r0, #0x0
	bx lr
	.balign 4
_02082518: .word 0x000019BC

	thumb_func_start FUN_0208251C
FUN_0208251C: ; 0x0208251C
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	ldr r0, _02082598 ; =0x000019BC
	add r5, r1, #0x0
	ldr r4, [r5, r0]
	mov r0, #0x1
	bl FUN_0200A344
	cmp r0, #0x0
	beq _02082594
	ldrb r0, [r4, #0xb]
	cmp r0, #0x0
	bne _02082580
	mov r0, #0x8
	ldrsh r1, [r4, r0]
	add r1, r1, #0x1
	strh r1, [r4, #0x8]
	ldrsh r2, [r4, r0]
	ldrb r0, [r4, #0xa]
	ldr r1, [r4, #0x4]
	ldrb r0, [r1, r0]
	cmp r2, r0
	ble _02082594
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x6
	mov r1, #0x0
	mov r2, #0x4
	mov r3, #0x3f
	bl FUN_0200A208
	ldr r0, _0208259C ; =0x000005F8
	bl FUN_020054C8
	ldrb r0, [r4, #0xa]
	add r0, r0, #0x1
	strb r0, [r4, #0xa]
	mov r0, #0x0
	strh r0, [r4, #0x8]
	ldrb r0, [r4, #0xa]
	ldr r1, [r4, #0x4]
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	bne _02082594
	ldrb r0, [r4, #0xb]
	add sp, #0x4
	add r0, r0, #0x1
	strb r0, [r4, #0xb]
	pop {r3-r6, pc}
_02082580:
	ldr r0, _02082598 ; =0x000019BC
	ldr r0, [r5, r0]
	bl FUN_02016A18
	ldr r0, _02082598 ; =0x000019BC
	mov r1, #0x0
	str r1, [r5, r0]
	add r0, r6, #0x0
	bl FUN_0200CAB4
_02082594:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02082598: .word 0x000019BC
_0208259C: .word 0x000005F8

	thumb_func_start FUN_020825A0
FUN_020825A0: ; 0x020825A0
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x13
	str r2, [sp, #0x4]
	ldr r6, [sp, #0x20]
	ldr r7, [sp, #0x24]
	str r1, [sp, #0x0]
	str r3, [sp, #0x8]
	mov r4, #0x0
	add r2, r5, #0x0
	lsl r0, r0, #0x4
_020825B8:
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	beq _020825C6
	add r4, r4, #0x1
	add r2, #0xc
	cmp r4, #0x4
	blt _020825B8
_020825C6:
	add r0, r4, #0x0
	bl FUN_020832DC
	ldr r1, [sp, #0x0]
	str r0, [r1, #0x0]
	ldr r1, _02082628 ; =0x00000171
	ldr r0, [sp, #0x4]
	ldrb r2, [r5, r1]
	sub r1, #0x4a
	str r2, [r0, #0x0]
	ldrb r0, [r5, r1]
	cmp r4, r0
	blt _020825E6
	mov r1, #0x1
	ldr r0, [sp, #0x8]
	b _020825EA
_020825E6:
	ldr r0, [sp, #0x8]
	mov r1, #0x0
_020825EA:
	str r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r6, #0x0]
	str r0, [r7, #0x0]
	ldr r0, _0208262C ; =0x00000121
	ldrb r0, [r5, r0]
	cmp r0, #0x8
	bhi _02082624
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082606: ; jump table (using 16-bit offset)
	.short _02082624 - _02082606 - 2; case 0
	.short _02082624 - _02082606 - 2; case 1
	.short _02082624 - _02082606 - 2; case 2
	.short _02082618 - _02082606 - 2; case 3
	.short _02082620 - _02082606 - 2; case 4
	.short _02082618 - _02082606 - 2; case 5
	.short _02082620 - _02082606 - 2; case 6
	.short _02082618 - _02082606 - 2; case 7
	.short _02082620 - _02082606 - 2; case 8
_02082618:
	mov r0, #0x1
	add sp, #0xc
	str r0, [r6, #0x0]
	pop {r4-r7, pc}
_02082620:
	mov r0, #0x1
	str r0, [r7, #0x0]
_02082624:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02082628: .word 0x00000171
_0208262C: .word 0x00000121

	thumb_func_start FUN_02082630
FUN_02082630: ; 0x02082630
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r0, _02082840 ; =0x00000121
	str r2, [sp, #0x4]
	ldrb r0, [r4, r0]
	add r6, r3, #0x0
	mov r5, #0x0
	cmp r0, #0x8
	bhi _02082666
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082650: ; jump table (using 16-bit offset)
	.short _02082666 - _02082650 - 2; case 0
	.short _02082666 - _02082650 - 2; case 1
	.short _02082666 - _02082650 - 2; case 2
	.short _02082662 - _02082650 - 2; case 3
	.short _02082662 - _02082650 - 2; case 4
	.short _02082662 - _02082650 - 2; case 5
	.short _02082662 - _02082650 - 2; case 6
	.short _02082662 - _02082650 - 2; case 7
	.short _02082662 - _02082650 - 2; case 8
_02082662:
	add sp, #0xc
	pop {r4-r7, pc}
_02082666:
	ldr r2, _02082844 ; =0x00000171
	ldrb r0, [r4, r2]
	cmp r0, #0x0
	ldr r0, _02082848 ; =0x0000198C
	beq _02082672
	b _02082774
_02082672:
	ldr r0, [r4, r0]
	bl FUN_020462AC
	add r6, r0, #0x0
	ldr r0, _02082840 ; =0x00000121
	ldrb r1, [r4, r0]
	cmp r1, #0x2
	bne _020826AC
	sub r0, r0, #0x1
	ldrb r0, [r4, r0]
	cmp r0, #0x3
	blo _020826AC
	add r0, r4, #0x0
	bl FUN_0208217C
	cmp r0, #0x0
	bne _020826AC
	ldr r1, _0208284C ; =0x0000011F
	add r0, r6, #0x0
	ldrb r1, [r4, r1]
	bl FUN_0205EE60
	cmp r0, #0x0
	bne _020826AC
	ldr r1, _0208284C ; =0x0000011F
	add r0, r6, #0x0
	ldrb r1, [r4, r1]
	bl FUN_0205EE08
_020826AC:
	add r0, r4, #0x0
	bl FUN_0208217C
	cmp r0, #0x0
	bne _020826EA
	mov r1, #0x1
	add r0, sp, #0x8
	strb r1, [r0, #0x0]
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldrb r0, [r4, r1]
	sub r1, r1, #0x1
	ldrb r1, [r4, r1]
	bl FUN_0208341C
	add r6, r0, #0x0
	ldr r0, _02082850 ; =0x00001990
	add r1, r6, #0x0
	ldr r0, [r4, r0]
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _020826DE
	mov r5, #0x1
_020826DE:
	ldr r0, _02082850 ; =0x00001990
	add r1, r6, #0x0
	ldr r0, [r4, r0]
	add r2, sp, #0x8
	bl FUN_02067830
_020826EA:
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl FUN_02022504
	ldr r3, _02082854 ; =0x00000123
	mov r1, #0xc
	ldrb r2, [r4, r3]
	mul r1, r2
	add r2, r4, r1
	add r1, r3, #0x0
	add r1, #0xd
	ldrb r1, [r2, r1]
	sub r2, r3, #0x4
	sub r3, r3, #0x3
	add r1, r1, #0x1
	str r1, [sp, #0x0]
	ldr r1, _02082850 ; =0x00001990
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	ldr r1, [r4, r1]
	bl FUN_02060F10
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl FUN_02029FC8
	mov r1, #0x3f
	add r6, r0, #0x0
	bl FUN_0202A0E8
	add r0, r4, #0x0
	bl FUN_0208217C
	cmp r0, #0x0
	bne _02082740
	add r0, r6, #0x0
	mov r1, #0x41
	bl FUN_0202A0E8
	add r0, r6, #0x0
	mov r1, #0xd
	bl FUN_0202A170
_02082740:
	cmp r5, #0x1
	bne _0208274C
	add r0, r6, #0x0
	mov r1, #0x43
	bl FUN_0202A0E8
_0208274C:
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl FUN_02024DA0
	add r7, r0, #0x0
	ldr r0, _02082858 ; =0x00000127
	ldrb r6, [r4, r0]
	cmp r6, #0x4
	bge _020827E8
	lsl r0, r6, #0x2
	add r5, r4, r0
_02082762:
	ldr r1, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_0202498C
	add r6, r6, #0x1
	add r5, r5, #0x4
	cmp r6, #0x4
	blt _02082762
	b _020827E8
_02082774:
	add r3, r2, #0x0
	sub r3, #0x4e
	ldrb r5, [r4, r3]
	add r1, r2, #0x0
	mov r3, #0xc
	mul r3, r5
	sub r1, #0x52
	add r3, r4, r3
	sub r2, #0x41
	ldrb r1, [r4, r1]
	ldrb r2, [r3, r2]
	ldr r0, [r4, r0]
	bl FUN_0202C108
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl FUN_02029FC8
	mov r1, #0x40
	add r5, r0, #0x0
	bl FUN_0202A0E8
	add r0, r4, #0x0
	bl FUN_0208217C
	cmp r0, #0x0
	bne _020827BA
	add r0, r5, #0x0
	mov r1, #0x42
	bl FUN_0202A0E8
	add r0, r5, #0x0
	mov r1, #0x13
	bl FUN_0202A170
_020827BA:
	ldr r1, _02082854 ; =0x00000123
	mov r0, #0xc
	ldrb r2, [r4, r1]
	add r1, #0xd
	mul r0, r2
	add r0, r4, r0
	ldrb r0, [r0, r1]
	mov r1, #0xb
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02029500
	add r5, r0, #0x0
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl FUN_020289A4
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x4
	bl FUN_02028AD4
_020827E8:
	add r0, r4, #0x0
	bl FUN_0208217C
	cmp r0, #0x0
	bne _02082820
	ldr r0, _02082848 ; =0x0000198C
	ldr r0, [r4, r0]
	bl FUN_02027E24
	ldr r1, _0208284C ; =0x0000011F
	ldrb r1, [r4, r1]
	bl FUN_02027044
	add r5, r0, #0x0
	bl FUN_02027740
	ldr r1, _02082854 ; =0x00000123
	add r0, r5, #0x0
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x2
	add r1, r4, r1
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	bl FUN_020278DC
	add r0, r5, #0x0
	bl FUN_02027710
_02082820:
	add r0, r4, #0x0
	bl FUN_0208217C
	cmp r0, #0x0
	bne _0208283A
	ldr r0, _02082850 ; =0x00001990
	ldr r2, [sp, #0x4]
	ldr r0, [r4, r0]
	lsl r2, r2, #0x10
	mov r1, #0x9
	lsr r2, r2, #0x10
	bl FUN_020688E8
_0208283A:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02082840: .word 0x00000121
_02082844: .word 0x00000171
_02082848: .word 0x0000198C
_0208284C: .word 0x0000011F
_02082850: .word 0x00001990
_02082854: .word 0x00000123
_02082858: .word 0x00000127

	thumb_func_start FUN_0208285C
FUN_0208285C: ; 0x0208285C
	push {r4, lr}
	bl FUN_020126D8
	add r4, r0, #0x0
	bl getseed_LC
	add r0, #0xa
	mul r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl seedr_LC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02082878
FUN_02082878: ; 0x02082878
	ldr r3, _0208287C ; =rand_LC
	bx r3
	.balign 4
_0208287C: .word rand_LC

	thumb_func_start FUN_02082880
FUN_02082880: ; 0x02082880
	push {r4, lr}
	add r4, r1, #0x0
	bl rand_ALT
	str r0, [r4, #0x0]
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02082894
FUN_02082894: ; 0x02082894
	push {r4-r5}
	mov r5, #0x42
	add r3, r0, r1
	lsl r5, r5, #0x2
	ldrb r4, [r3, r5]
	lsl r1, r1, #0x1
	add r0, r0, r1
	strb r4, [r2, #0x0]
	add r4, r5, #0x4
	ldrb r4, [r3, r4]
	strb r4, [r2, #0x1]
	add r4, r5, #0x0
	add r4, #0x8
	ldrb r3, [r3, r4]
	add r5, #0xc
	strb r3, [r2, #0x2]
	ldrh r0, [r0, r5]
	strh r0, [r2, #0x4]
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_020828BC
FUN_020828BC: ; 0x020828BC
	ldr r2, _020828E0 ; =0x00000171
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	beq _020828D6
	cmp r1, #0x1
	bne _020828DA
	add r1, r2, #0x0
	sub r1, #0x55
	sub r2, #0x4e
	ldrb r1, [r0, r1]
	ldrb r0, [r0, r2]
	cmp r1, r0
	bne _020828DA
_020828D6:
	mov r0, #0x1
	bx lr
_020828DA:
	mov r0, #0x0
	bx lr
	nop
_020828E0: .word 0x00000171

	thumb_func_start FUN_020828E4
FUN_020828E4: ; 0x020828E4
	push {r3-r7, lr}
	sub sp, #0x58
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x70]
	mov r6, #0x0
	str r0, [sp, #0x70]
	ldr r0, [sp, #0x74]
	add r5, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x8]
	str r6, [sp, #0x20]
	str r6, [sp, #0x18]
	str r6, [sp, #0x1c]
	cmp r0, #0x8
	bhi _0208292A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0208290E: ; jump table (using 16-bit offset)
	.short _0208292A - _0208290E - 2; case 0
	.short _0208292A - _0208290E - 2; case 1
	.short _0208292A - _0208290E - 2; case 2
	.short _02082920 - _0208290E - 2; case 3
	.short _02082926 - _0208290E - 2; case 4
	.short _02082920 - _0208290E - 2; case 5
	.short _02082926 - _0208290E - 2; case 6
	.short _02082920 - _0208290E - 2; case 7
	.short _02082926 - _0208290E - 2; case 8
_02082920:
	mov r0, #0x1
	str r0, [sp, #0x18]
	b _0208292A
_02082926:
	mov r0, #0x1
	str r0, [sp, #0x1c]
_0208292A:
	mov r0, #0x1
	mov r1, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x5a
	add r2, r1, #0x0
	add r3, r5, #0x0
	bl FUN_02006C98
	str r0, [sp, #0x14]
	mov r0, #0x5a
	mov r1, #0x0
	bl LoadFromNARC_7
	mov r1, #0x30
	bl _u32_div_f
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r5, #0x0
	add r1, r1, #0x1
	bl FUN_020169D8
	add r5, r0, #0x0
	ldr r0, [sp, #0x78]
	cmp r0, #0x1
	bne _02082968
	ldr r0, [sp, #0x7c]
	cmp r0, #0x1
	bne _02082968
	mov r0, #0x1
	str r0, [sp, #0x20]
_02082968:
	ldr r0, [sp, #0x24]
	mov r2, #0x0
	cmp r0, #0x0
	ble _02082A1A
	ldr r3, [sp, #0x14]
_02082972:
	ldrh r7, [r3, #0x20]
	lsl r0, r7, #0x1d
	lsr r1, r0, #0x1d
	ldr r0, [sp, #0x70]
	cmp r0, r1
	bne _02082A10
	ldr r0, [sp, #0x20]
	cmp r0, #0x1
	bne _0208298E
	lsl r0, r7, #0x14
	lsr r0, r0, #0x1e
	cmp r0, #0x1
	beq _02082A10
	b _0208299A
_0208298E:
	lsl r0, r7, #0x14
	lsr r0, r0, #0x1e
	cmp r0, #0x2
	beq _02082A10
	cmp r0, #0x3
	beq _02082A10
_0208299A:
	ldr r0, [sp, #0x18]
	cmp r0, #0x1
	bne _020829AA
	ldrh r0, [r3, #0x20]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1f
	beq _02082A10
	b _020829CA
_020829AA:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x1
	ldrh r0, [r3, #0x20]
	bne _020829BA
	lsl r0, r0, #0x17
	lsr r0, r0, #0x1f
	beq _02082A10
	b _020829CA
_020829BA:
	lsl r1, r0, #0x16
	lsr r1, r1, #0x1f
	cmp r1, #0x1
	beq _02082A10
	lsl r0, r0, #0x17
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	beq _02082A10
_020829CA:
	cmp r4, #0x0
	bne _020829D6
	ldrh r0, [r3, #0x20]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bne _02082A06
_020829D6:
	cmp r4, #0x1
	bne _020829E2
	ldrh r0, [r3, #0x20]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bne _02082A06
_020829E2:
	cmp r4, #0x2
	bne _020829EE
	ldrh r0, [r3, #0x20]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	bne _02082A06
_020829EE:
	cmp r4, #0x3
	bne _020829FA
	ldrh r0, [r3, #0x20]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bne _02082A06
_020829FA:
	cmp r4, #0x4
	bne _02082A10
	ldrh r0, [r3, #0x20]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	beq _02082A10
_02082A06:
	add r1, r6, #0x1
	add r0, r6, #0x0
	lsl r1, r1, #0x18
	lsr r6, r1, #0x18
	strb r2, [r5, r0]
_02082A10:
	ldr r0, [sp, #0x24]
	add r2, r2, #0x1
	add r3, #0x30
	cmp r2, r0
	blt _02082972
_02082A1A:
	mov r0, #0xff
	strb r0, [r5, r6]
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _02082A26
	b _02082B4E
_02082A26:
	ldr r0, [sp, #0x8]
	cmp r6, r0
	bge _02082A30
	bl ErrorHandling
_02082A30:
	mov r0, #0x0
	str r0, [sp, #0x10]
	cmp r6, #0x0
	ble _02082A5A
	mov r2, #0x30
_02082A3A:
	ldrb r1, [r5, r0]
	add r3, r1, #0x0
	ldr r1, [sp, #0x14]
	mul r3, r2
	add r1, r1, r3
	ldrh r1, [r1, #0x20]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1e
	cmp r1, #0x3
	bne _02082A54
	ldr r1, [sp, #0x10]
	add r1, r1, #0x1
	str r1, [sp, #0x10]
_02082A54:
	add r0, r0, #0x1
	cmp r0, r6
	blt _02082A3A
_02082A5A:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	ble _02082AA2
	ldr r0, [sp, #0x4]
	bl FUN_02082878
	ldr r1, [sp, #0x10]
	bl _s32_div_f
	mov r3, #0x0
	cmp r6, #0x0
	ble _02082AA2
	mov r0, #0x30
_02082A74:
	ldrb r4, [r5, r3]
	add r2, r4, #0x0
	ldr r4, [sp, #0x14]
	mul r2, r0
	add r2, r4, r2
	ldrh r4, [r2, #0x20]
	lsl r4, r4, #0x14
	lsr r4, r4, #0x1e
	cmp r4, #0x3
	bne _02082A9C
	cmp r1, #0x0
	bne _02082A9A
	add r4, sp, #0x28
	mov r3, #0x6
_02082A90:
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r3, r3, #0x1
	bne _02082A90
	b _02082AA2
_02082A9A:
	sub r1, r1, #0x1
_02082A9C:
	add r3, r3, #0x1
	cmp r3, r6
	blt _02082A74
_02082AA2:
	ldr r0, [sp, #0x8]
	mov r1, #0x4
	sub r4, r1, r0
	add r0, r4, #0x0
	str r4, [sp, #0xc]
	cmp r0, #0x4
	bge _02082B16
_02082AB0:
	ldr r0, [sp, #0x4]
	bl FUN_02082878
	add r1, r6, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r2, r0, #0x10
	ldrb r3, [r5, r2]
	mov r0, #0x30
	add r1, r3, #0x0
	ldr r3, [sp, #0x14]
	mul r1, r0
	add r7, r3, r1
	ldrh r1, [r7, #0x20]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1e
	cmp r1, #0x3
	bne _02082ADA
	sub r4, r4, #0x1
	b _02082B10
_02082ADA:
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	add r3, r0, r1
	mov r0, #0x6
	add r3, #0x10
	mov r12, r0
_02082AE8:
	ldmia r7!, {r0-r1}
	stmia r3!, {r0-r1}
	mov r0, r12
	sub r0, r0, #0x1
	mov r12, r0
	bne _02082AE8
	ldrb r1, [r5, r2]
	add r0, r5, r2
	cmp r1, #0xff
	beq _02082B0A
_02082AFC:
	ldrb r1, [r0, #0x1]
	add r2, r2, #0x1
	strb r1, [r0, #0x0]
	ldrb r1, [r5, r2]
	add r0, r5, r2
	cmp r1, #0xff
	bne _02082AFC
_02082B0A:
	sub r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02082B10:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02082AB0
_02082B16:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	ble _02082B7E
	ldr r0, [sp, #0xc]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [sp, #0x4]
	bl FUN_02082878
	ldr r1, [sp, #0x8]
	bl _s32_div_f
	add r0, r4, r1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	add r1, r2, #0x0
	mov r0, #0x30
	mul r1, r0
	ldr r0, [sp, #0x4]
	add r4, sp, #0x28
	add r3, r0, r1
	add r3, #0x10
	mov r2, #0x6
_02082B44:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02082B44
	b _02082B7E
_02082B4E:
	cmp r6, #0x4
	bhs _02082B56
	bl ErrorHandling
_02082B56:
	mov r6, #0x0
	mov r7, #0x30
_02082B5A:
	ldrb r0, [r5, r6]
	ldr r3, [sp, #0x4]
	mov r2, #0x6
	add r1, r0, #0x0
	ldr r0, [sp, #0x14]
	mul r1, r7
	add r4, r0, r1
	add r3, #0x10
_02082B6A:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02082B6A
	ldr r0, [sp, #0x4]
	add r6, r6, #0x1
	add r0, #0x30
	str r0, [sp, #0x4]
	cmp r6, #0x4
	blt _02082B5A
_02082B7E:
	add r0, r5, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x14]
	bl FUN_02016A18
	add sp, #0x58
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02082B90
FUN_02082B90: ; 0x02082B90
	push {r3-r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x8]
	mov r0, #0x1
	add r3, r1, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x5a
	mov r1, #0x2
	mov r2, #0x0
	bl FUN_02006C98
	str r0, [sp, #0x14]
	ldr r1, _02082D10 ; =0x00000121
	ldr r0, [sp, #0x8]
	ldrb r0, [r0, r1]
	cmp r0, #0x4
	beq _02082BBA
	cmp r0, #0x6
	beq _02082BBA
	cmp r0, #0x8
	bne _02082BC0
_02082BBA:
	mov r0, #0x0
	str r0, [sp, #0xc]
	b _02082BC8
_02082BC0:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x6
	ldrb r0, [r0, r1]
	str r0, [sp, #0xc]
_02082BC8:
	ldr r0, [sp, #0xc]
	cmp r0, #0x4
	blt _02082BD0
	b _02082D06
_02082BD0:
	mov r1, #0x30
	mul r1, r0
	ldr r0, [sp, #0x8]
	add r7, r0, r1
	ldr r0, [sp, #0xc]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x8]
	add r6, r0, r1
_02082BE0:
	ldr r1, _02082D14 ; =0x00000122
	ldr r0, [sp, #0x8]
	ldrb r0, [r0, r1]
	cmp r0, #0xb
	bhi _02082C6E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02082BF6: ; jump table (using 16-bit offset)
	.short _02082C0E - _02082BF6 - 2; case 0
	.short _02082C16 - _02082BF6 - 2; case 1
	.short _02082C1E - _02082BF6 - 2; case 2
	.short _02082C26 - _02082BF6 - 2; case 3
	.short _02082C2E - _02082BF6 - 2; case 4
	.short _02082C36 - _02082BF6 - 2; case 5
	.short _02082C3E - _02082BF6 - 2; case 6
	.short _02082C46 - _02082BF6 - 2; case 7
	.short _02082C4E - _02082BF6 - 2; case 8
	.short _02082C56 - _02082BF6 - 2; case 9
	.short _02082C5E - _02082BF6 - 2; case 10
	.short _02082C66 - _02082BF6 - 2; case 11
_02082C0E:
	add r0, r7, #0x0
	add r0, #0x32
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C16:
	add r0, r7, #0x0
	add r0, #0x33
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C1E:
	add r0, r7, #0x0
	add r0, #0x34
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C26:
	add r0, r7, #0x0
	add r0, #0x35
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C2E:
	add r0, r7, #0x0
	add r0, #0x36
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C36:
	add r0, r7, #0x0
	add r0, #0x37
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C3E:
	add r0, r7, #0x0
	add r0, #0x38
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C46:
	add r0, r7, #0x0
	add r0, #0x39
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C4E:
	add r0, r7, #0x0
	add r0, #0x3a
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C56:
	add r0, r7, #0x0
	add r0, #0x3b
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C5E:
	add r0, r7, #0x0
	add r0, #0x3c
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C66:
	add r0, r7, #0x0
	add r0, #0x3d
	ldrb r2, [r0, #0x0]
	b _02082C74
_02082C6E:
	bl ErrorHandling
	mov r2, #0x0
_02082C74:
	mov r0, #0x54
	add r1, r2, #0x0
	mul r1, r0
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bl FUN_02027740
	add r0, r6, #0x0
	add r0, #0xf8
	ldr r2, [sp, #0x10]
	mov r3, #0x51
	ldrsb r2, [r2, r3]
	ldr r0, [r0, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_02027914
	ldr r0, [sp, #0x10]
	mov r5, #0x0
	add r0, #0x50
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	ble _02082CD2
	ldr r4, [sp, #0x10]
_02082CAA:
	ldrb r0, [r4, #0x2]
	add r1, r5, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x3
	ldrsb r0, [r4, r0]
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r0, #0xf8
	ldrb r2, [r4, #0x0]
	ldrb r3, [r4, #0x1]
	ldr r0, [r0, #0x0]
	bl FUN_02027964
	ldr r0, [sp, #0x10]
	add r5, r5, #0x1
	add r0, #0x50
	ldrb r0, [r0, #0x0]
	add r4, r4, #0x4
	cmp r5, r0
	blt _02082CAA
_02082CD2:
	ldr r1, [sp, #0x10]
	add r0, r6, #0x0
	add r1, #0x52
	add r0, #0xf8
	str r1, [sp, #0x10]
	ldrb r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_0202787C
	mov r2, #0x12
	add r0, r6, #0x0
	add r0, #0xf8
	ldr r1, [sp, #0x8]
	lsl r2, r2, #0x4
	ldrb r1, [r1, r2]
	ldr r0, [r0, #0x0]
	bl FUN_020278AC
	ldr r0, [sp, #0xc]
	add r7, #0x30
	add r0, r0, #0x1
	add r6, r6, #0x4
	str r0, [sp, #0xc]
	cmp r0, #0x4
	bge _02082D06
	b _02082BE0
_02082D06:
	ldr r0, [sp, #0x14]
	bl FUN_02016A18
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_02082D10: .word 0x00000121
_02082D14: .word 0x00000122

	thumb_func_start FUN_02082D18
FUN_02082D18: ; 0x02082D18
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r7, #0x12
	mov r4, #0x0
	add r5, r6, #0x0
	lsl r7, r7, #0x4
_02082D24:
	add r0, r5, #0x0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bl FUN_02027740
	add r0, r5, #0x0
	add r0, #0xf8
	mov r2, #0x0
	ldr r0, [r0, #0x0]
	ldr r1, [r5, #0x0]
	mvn r2, r2
	bl FUN_02027914
	add r0, r5, #0x0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_0202787C
	add r0, r5, #0x0
	add r0, #0xf8
	ldrb r1, [r6, r7]
	ldr r0, [r0, #0x0]
	bl FUN_020278AC
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _02082D24
	pop {r3-r7, pc}

	thumb_func_start FUN_02082D60
FUN_02082D60: ; 0x02082D60
	push {r3-r7, lr}
	sub sp, #0x20
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldrh r1, [r7, #0x20]
	str r2, [sp, #0x10]
	ldrh r0, [r7, #0x14]
	lsl r1, r1, #0x12
	lsr r1, r1, #0x1e
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	mov r2, #0x0
	bl FUN_02066E74
	mov r1, #0x1
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	ldr r0, _02082E60 ; =0x0F0F0F0F
	mov r2, #0xa
	str r0, [sp, #0xc]
	ldrh r1, [r7, #0x14]
	add r0, r6, #0x0
	mov r3, #0x20
	bl FUN_02066ACC
	mov r4, #0x0
	add r5, r7, #0x0
_02082D9A:
	ldrh r1, [r5, #0xc]
	add r0, sp, #0x18
	add r2, sp, #0x1c
	strh r1, [r0, #0x6]
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	add r2, #0x2
	bl FUN_02067830
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x4
	blt _02082D9A
	ldr r3, [sp, #0x10]
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc0
	bl FUN_0200A86C
	ldrh r1, [r7, #0x16]
	add r4, r0, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	ldrh r1, [r7, #0x18]
	add r0, r4, #0x0
	bl FUN_0200A914
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0x76
	add r2, r5, #0x0
	bl FUN_02067830
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0x90
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02021A20
	ldr r0, [sp, #0x14]
	bl FUN_02021A20
	add r0, r4, #0x0
	bl FUN_0200A8B8
	add r2, sp, #0x1c
	ldrb r1, [r7, #0x1a]
	add r0, sp, #0x18
	add r2, #0x1
	strb r1, [r0, #0x5]
	ldrb r1, [r7, #0x1b]
	strb r1, [r0, #0x4]
	ldrb r1, [r7, #0x1c]
	strb r1, [r0, #0x3]
	ldrb r1, [r7, #0x1d]
	strb r1, [r0, #0x2]
	ldrb r1, [r7, #0x1e]
	strb r1, [r0, #0x1]
	ldrb r1, [r7, #0x1f]
	strb r1, [r0, #0x0]
	add r0, r6, #0x0
	mov r1, #0x13
	bl FUN_02067830
	add r0, r6, #0x0
	mov r1, #0x14
	add r2, sp, #0x1c
	bl FUN_02067830
	add r2, sp, #0x18
	add r0, r6, #0x0
	mov r1, #0x15
	add r2, #0x3
	bl FUN_02067830
	add r2, sp, #0x18
	add r0, r6, #0x0
	mov r1, #0x16
	add r2, #0x2
	bl FUN_02067830
	add r2, sp, #0x18
	add r0, r6, #0x0
	mov r1, #0x17
	add r2, #0x1
	bl FUN_02067830
	add r0, r6, #0x0
	mov r1, #0x18
	add r2, sp, #0x18
	bl FUN_02067830
	add sp, #0x20
	pop {r3-r7, pc}
	nop
_02082E60: .word 0x0F0F0F0F

	thumb_func_start FUN_02082E64
FUN_02082E64: ; 0x02082E64
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r3, #0x0
	add r5, r2, #0x0
	lsl r2, r6, #0x18
	str r0, [sp, #0x10]
	add r7, r1, #0x0
	add r0, sp, #0x14
	add r1, r5, #0x0
	lsr r2, r2, #0x18
	ldr r4, [sp, #0x38]
	bl FUN_02068B68
	lsl r1, r6, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02068E14
	add r5, r0, #0x0
	cmp r4, #0x0
	beq _02082EB0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02082E98
	bl ErrorHandling
_02082E98:
	add r1, sp, #0x14
	ldrh r0, [r1, #0x0]
	ldrh r1, [r1, #0x2]
	ldr r2, [sp, #0x3c]
	ldr r3, [r4, #0x0]
	bl FUN_02012420
	add r0, sp, #0x14
	ldrh r1, [r0, #0x4]
	str r1, [r4, #0x8]
	ldrh r0, [r0, #0x0]
	str r0, [r4, #0x4]
_02082EB0:
	ldr r0, [sp, #0x48]
	ldr r3, [sp, #0x44]
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x40]
	add r1, sp, #0x14
	add r3, r3, r5
	bl FUN_020073A0
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02082ED0
FUN_02082ED0: ; 0x02082ED0
	push {r4-r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [sp, #0x38]
	add r7, r3, #0x0
	mov r5, #0x0
	str r2, [sp, #0xc]
	str r0, [sp, #0x38]
	mov r1, #0x1
	ldr r3, [sp, #0x8]
	mov r0, #0x5a
	add r2, r5, #0x0
	add r4, r5, #0x0
	str r1, [sp, #0x0]
	bl FUN_02006C98
	str r0, [sp, #0x14]
	mov r0, #0x5a
	mov r1, #0x1
	bl LoadFromNARC_7
	lsr r0, r0, #0x3
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	bl FUN_020169D8
	ldr r1, [sp, #0x18]
	add r6, r0, #0x0
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	bl FUN_020169D8
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	add r2, r5, #0x0
	cmp r0, #0x0
	ble _0208300A
	ldr r3, [sp, #0x14]
_02082F22:
	ldrh r0, [r3, #0x4]
	mov r12, r0
	lsl r0, r0, #0x14
	lsr r1, r0, #0x1e
	ldr r0, [sp, #0x38]
	cmp r0, r1
	bne _02083000
	cmp r7, #0x0
	bne _02082F5A
	mov r0, r12
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	beq _02082F5A
	cmp r0, #0x1
	bls _02082F4E
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	add r1, r4, #0x0
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x10]
	strb r2, [r0, r1]
	b _02083000
_02082F4E:
	add r1, r5, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	strb r2, [r6, r0]
	b _02083000
_02082F5A:
	cmp r7, #0x1
	bne _02082F84
	ldrh r0, [r3, #0x4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1e
	beq _02082F84
	cmp r0, #0x1
	bls _02082F78
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	add r1, r4, #0x0
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x10]
	strb r2, [r0, r1]
	b _02083000
_02082F78:
	add r1, r5, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	strb r2, [r6, r0]
	b _02083000
_02082F84:
	cmp r7, #0x2
	bne _02082FAE
	ldrh r0, [r3, #0x4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	beq _02082FAE
	cmp r0, #0x1
	bls _02082FA2
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	add r1, r4, #0x0
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x10]
	strb r2, [r0, r1]
	b _02083000
_02082FA2:
	add r1, r5, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	strb r2, [r6, r0]
	b _02083000
_02082FAE:
	cmp r7, #0x3
	bne _02082FD8
	ldrh r0, [r3, #0x4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1e
	beq _02082FD8
	cmp r0, #0x1
	bls _02082FCC
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	add r1, r4, #0x0
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x10]
	strb r2, [r0, r1]
	b _02083000
_02082FCC:
	add r1, r5, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	strb r2, [r6, r0]
	b _02083000
_02082FD8:
	cmp r7, #0x4
	bne _02083000
	ldrh r0, [r3, #0x4]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1e
	beq _02083000
	cmp r0, #0x1
	bls _02082FF6
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	add r1, r4, #0x0
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x10]
	strb r2, [r0, r1]
	b _02083000
_02082FF6:
	add r1, r5, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	strb r2, [r6, r0]
_02083000:
	ldr r0, [sp, #0x18]
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, r0
	blt _02082F22
_0208300A:
	mov r1, #0xff
	ldr r0, [sp, #0x10]
	strb r1, [r6, r5]
	strb r1, [r0, r4]
	cmp r5, #0x2
	bhs _0208301A
	bl ErrorHandling
_0208301A:
	ldr r2, [sp, #0x4]
	mov r3, #0x0
_0208301E:
	ldrb r0, [r6, r3]
	ldr r5, [sp, #0x14]
	add r3, r3, #0x1
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x14]
	ldrh r5, [r5, r1]
	add r0, r0, r1
	add r1, r2, #0x0
	add r1, #0xd0
	strh r5, [r1, #0x0]
	add r1, r2, #0x0
	ldrh r5, [r0, #0x2]
	add r1, #0xd2
	strh r5, [r1, #0x0]
	add r1, r2, #0x0
	ldrh r5, [r0, #0x4]
	add r1, #0xd4
	strh r5, [r1, #0x0]
	ldrh r1, [r0, #0x6]
	add r0, r2, #0x0
	add r0, #0xd6
	add r2, #0x8
	strh r1, [r0, #0x0]
	cmp r3, #0x2
	blt _0208301E
	cmp r4, #0x1
	bhs _02083058
	bl ErrorHandling
_02083058:
	ldr r0, [sp, #0x4]
	bl FUN_02082878
	add r1, r4, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x10]
	ldrb r0, [r0, r1]
	ldr r1, [sp, #0x14]
	lsl r2, r0, #0x3
	ldr r0, [sp, #0x14]
	add r0, r0, r2
	ldrh r2, [r1, r2]
	ldr r1, [sp, #0x4]
	add r1, #0xe0
	strh r2, [r1, #0x0]
	ldr r1, [sp, #0x4]
	ldrh r2, [r0, #0x2]
	add r1, #0xe2
	strh r2, [r1, #0x0]
	ldr r1, [sp, #0x4]
	ldrh r2, [r0, #0x4]
	add r1, #0xe4
	strh r2, [r1, #0x0]
	ldrh r1, [r0, #0x6]
	ldr r0, [sp, #0x4]
	ldr r2, _02083110 ; =0x0000011E
	add r0, #0xe6
	strh r1, [r0, #0x0]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x4]
	strb r1, [r0, r2]
	add r2, r0, #0x0
	add r0, r1, #0x0
	lsl r1, r0, #0x3
	add r2, #0xd0
	ldrh r4, [r2, r1]
	add r0, sp, #0x1c
	add r3, r2, r1
	strh r4, [r0, #0x0]
	ldrh r4, [r3, #0x2]
	strh r4, [r0, #0x2]
	ldrh r4, [r3, #0x4]
	strh r4, [r0, #0x4]
	ldrh r4, [r3, #0x6]
	strh r4, [r0, #0x6]
	ldr r4, [sp, #0x4]
	add r4, #0xe0
	ldrh r4, [r4, #0x0]
	strh r4, [r2, r1]
	ldr r1, [sp, #0x4]
	add r1, #0xe2
	ldrh r1, [r1, #0x0]
	strh r1, [r3, #0x2]
	ldr r1, [sp, #0x4]
	add r1, #0xe4
	ldrh r1, [r1, #0x0]
	strh r1, [r3, #0x4]
	ldr r1, [sp, #0x4]
	add r1, #0xe6
	ldrh r1, [r1, #0x0]
	strh r1, [r3, #0x6]
	ldr r1, [sp, #0x4]
	ldrh r2, [r0, #0x0]
	add r1, #0xe0
	strh r2, [r1, #0x0]
	ldr r1, [sp, #0x4]
	ldrh r2, [r0, #0x2]
	add r1, #0xe2
	strh r2, [r1, #0x0]
	ldr r1, [sp, #0x4]
	ldrh r2, [r0, #0x4]
	add r1, #0xe4
	strh r2, [r1, #0x0]
	ldrh r1, [r0, #0x6]
	ldr r0, [sp, #0x4]
	add r0, #0xe6
	str r0, [sp, #0x4]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	add r0, r6, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x14]
	bl FUN_02016A18
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02083110: .word 0x0000011E

	thumb_func_start FUN_02083114
FUN_02083114: ; 0x02083114
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x18
	blo _02083120
	bl ErrorHandling
_02083120:
	mov r0, #0x1a
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _0208312C ; =0x020FBC6C
	ldrsb r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_0208312C: .word 0x020FBC6C

	thumb_func_start FUN_02083130
FUN_02083130: ; 0x02083130
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r5, #0x18
	blo _02083140
	bl ErrorHandling
_02083140:
	mov r0, #0x1a
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, _02083154 ; =0x020FBC68
	ldrh r0, [r0, r1]
	str r0, [r4, #0x0]
	ldr r0, _02083158 ; =0x020FBC6A
	ldrh r0, [r0, r1]
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	.balign 4
_02083154: .word 0x020FBC68
_02083158: .word 0x020FBC6A

	thumb_func_start FUN_0208315C
FUN_0208315C: ; 0x0208315C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x18
	blo _02083168
	bl ErrorHandling
_02083168:
	add r4, #0x2d
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02083170
FUN_02083170: ; 0x02083170
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r6, r3, #0x0
	cmp r4, #0x18
	blo _02083182
	bl ErrorHandling
_02083182:
	cmp r7, #0x4
	bhi _0208319C
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02083192: ; jump table (using 16-bit offset)
	.short _0208319C - _02083192 - 2; case 0
	.short _020831B0 - _02083192 - 2; case 1
	.short _020831C4 - _02083192 - 2; case 2
	.short _020831D8 - _02083192 - 2; case 3
	.short _020831EC - _02083192 - 2; case 4
_0208319C:
	mov r0, #0x1a
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02083200 ; =0x020FBC6E
	ldrh r0, [r0, r1]
	str r0, [r5, #0x0]
	ldr r0, _02083204 ; =0x020FBC70
	ldrb r0, [r0, r1]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
_020831B0:
	mov r0, #0x1a
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02083208 ; =0x020FBC72
	ldrh r0, [r0, r1]
	str r0, [r5, #0x0]
	ldr r0, _0208320C ; =0x020FBC74
	ldrb r0, [r0, r1]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
_020831C4:
	mov r0, #0x1a
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02083210 ; =0x020FBC76
	ldrh r0, [r0, r1]
	str r0, [r5, #0x0]
	ldr r0, _02083214 ; =0x020FBC78
	ldrb r0, [r0, r1]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
_020831D8:
	mov r0, #0x1a
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02083218 ; =0x020FBC7A
	ldrh r0, [r0, r1]
	str r0, [r5, #0x0]
	ldr r0, _0208321C ; =0x020FBC7C
	ldrb r0, [r0, r1]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
_020831EC:
	mov r0, #0x1a
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02083220 ; =0x020FBC7E
	ldrh r0, [r0, r1]
	str r0, [r5, #0x0]
	ldr r0, _02083224 ; =0x020FBC80
	ldrb r0, [r0, r1]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
	.balign 4
_02083200: .word 0x020FBC6E
_02083204: .word 0x020FBC70
_02083208: .word 0x020FBC72
_0208320C: .word 0x020FBC74
_02083210: .word 0x020FBC76
_02083214: .word 0x020FBC78
_02083218: .word 0x020FBC7A
_0208321C: .word 0x020FBC7C
_02083220: .word 0x020FBC7E
_02083224: .word 0x020FBC80

	thumb_func_start FUN_02083228
FUN_02083228: ; 0x02083228
	cmp r2, #0x1
	bne _02083230
	mov r0, #0x33
	bx lr
_02083230:
	cmp r1, #0x3
	beq _0208323C
	cmp r1, #0x5
	beq _0208323C
	cmp r1, #0x7
	bne _02083240
_0208323C:
	mov r0, #0x32
	bx lr
_02083240:
	cmp r0, #0x3
	bhi _02083264
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02083250: ; jump table (using 16-bit offset)
	.short _02083258 - _02083250 - 2; case 0
	.short _0208325C - _02083250 - 2; case 1
	.short _02083260 - _02083250 - 2; case 2
	.short _02083264 - _02083250 - 2; case 3
_02083258:
	mov r0, #0x2e
	bx lr
_0208325C:
	mov r0, #0x2f
	bx lr
_02083260:
	mov r0, #0x30
	bx lr
_02083264:
	mov r0, #0x31
	bx lr

	thumb_func_start FUN_02083268
FUN_02083268: ; 0x02083268
	cmp r0, #0x4
	bhi _02083292
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02083278: ; jump table (using 16-bit offset)
	.short _02083282 - _02083278 - 2; case 0
	.short _02083286 - _02083278 - 2; case 1
	.short _0208328A - _02083278 - 2; case 2
	.short _0208328E - _02083278 - 2; case 3
	.short _02083292 - _02083278 - 2; case 4
_02083282:
	mov r0, #0x2e
	bx lr
_02083286:
	mov r0, #0x2f
	bx lr
_0208328A:
	mov r0, #0x30
	bx lr
_0208328E:
	mov r0, #0x31
	bx lr
_02083292:
	mov r0, #0x33
	bx lr
	.balign 4

	thumb_func_start FUN_02083298
FUN_02083298: ; 0x02083298
	ldr r3, _020832A0 ; =FUN_020832A4
	mov r1, #0x2
	bx r3
	nop
_020832A0: .word FUN_020832A4

	thumb_func_start FUN_020832A4
FUN_020832A4: ; 0x020832A4
	cmp r1, #0x5
	bne _020832AC
	mov r0, #0x34
	bx lr
_020832AC:
	cmp r0, #0x4
	bhi _020832D6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020832BC: ; jump table (using 16-bit offset)
	.short _020832C6 - _020832BC - 2; case 0
	.short _020832CA - _020832BC - 2; case 1
	.short _020832CE - _020832BC - 2; case 2
	.short _020832D2 - _020832BC - 2; case 3
	.short _020832D6 - _020832BC - 2; case 4
_020832C6:
	mov r0, #0x29
	bx lr
_020832CA:
	mov r0, #0x2a
	bx lr
_020832CE:
	mov r0, #0x2b
	bx lr
_020832D2:
	mov r0, #0x2c
	bx lr
_020832D6:
	mov r0, #0x2d
	bx lr
	.balign 4

	thumb_func_start FUN_020832DC
FUN_020832DC: ; 0x020832DC
	mov r1, #0x3
	sub r0, r1, r0
	bx lr
	.balign 4

	thumb_func_start FUN_020832E4
FUN_020832E4: ; 0x020832E4
	mov r1, #0x3
	sub r0, r1, r0
	bx lr
	.balign 4

	thumb_func_start FUN_020832EC
FUN_020832EC: ; 0x020832EC
	ldr r1, _02083304 ; =0x00000121
	ldrb r0, [r0, r1]
	cmp r0, #0x3
	beq _020832FC
	cmp r0, #0x5
	beq _020832FC
	cmp r0, #0x7
	bne _02083300
_020832FC:
	mov r0, #0x1
	bx lr
_02083300:
	mov r0, #0x0
	bx lr
	.balign 4
_02083304: .word 0x00000121

	thumb_func_start FUN_02083308
FUN_02083308: ; 0x02083308
	push {r4-r5}
	sub sp, #0x50
	ldr r5, _02083368 ; =0x020FBC18
	add r4, sp, #0x0
	mov r3, #0x28
_02083312:
	ldrh r2, [r5, #0x0]
	add r5, r5, #0x2
	strh r2, [r4, #0x0]
	add r4, r4, #0x2
	sub r3, r3, #0x1
	bne _02083312
	mov r3, #0xc
	mul r3, r1
	add r1, r0, r3
	mov r3, #0x4a
	lsl r3, r3, #0x2
	add r4, r3, #0x0
	add r4, #0x49
	ldrb r4, [r0, r4]
	mov r2, #0x0
	ldrsh r1, [r1, r3]
	cmp r4, #0x1
	bne _0208333A
	add r4, sp, #0x40
	b _02083344
_0208333A:
	sub r3, #0x8
	ldrb r0, [r0, r3]
	add r4, sp, #0x0
	lsl r0, r0, #0x4
	add r4, r4, r0
_02083344:
	mov r3, #0x0
_02083346:
	ldrh r0, [r4, #0x0]
	cmp r1, r0
	bge _02083354
	add sp, #0x50
	add r0, r2, #0x0
	pop {r4-r5}
	bx lr
_02083354:
	add r3, r3, #0x1
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r3, #0x8
	blt _02083346
	add r0, r2, #0x0
	add sp, #0x50
	pop {r4-r5}
	bx lr
	nop
_02083368: .word 0x020FBC18

	thumb_func_start FUN_0208336C
FUN_0208336C: ; 0x0208336C
	push {r4-r5}
	sub sp, #0x10
	ldr r5, _020833CC ; =0x020FBC08
	add r4, sp, #0x0
	mov r3, #0xf
_02083376:
	ldrb r2, [r5, #0x0]
	add r5, r5, #0x1
	strb r2, [r4, #0x0]
	add r4, r4, #0x1
	sub r3, r3, #0x1
	bne _02083376
	mov r2, #0xc
	mul r2, r1
	ldr r3, _020833D0 ; =0x0000012A
	add r1, r0, r2
	ldrsh r1, [r1, r3]
	cmp r1, #0x0
	bne _02083398
	add sp, #0x10
	mov r0, #0x0
	pop {r4-r5}
	bx lr
_02083398:
	add r2, r3, #0x0
	add r2, #0x47
	ldrb r2, [r0, r2]
	cmp r2, #0x1
	bne _020833A6
	add r4, sp, #0xc
	b _020833B2
_020833A6:
	sub r3, #0xa
	ldrb r2, [r0, r3]
	add r4, sp, #0x0
	lsl r0, r2, #0x1
	add r0, r2, r0
	add r4, r4, r0
_020833B2:
	mov r0, #0x1
	mov r3, #0x0
_020833B6:
	ldrb r2, [r4, r3]
	cmp r1, r2
	ble _020833C4
	add r3, r3, #0x1
	add r0, r0, #0x1
	cmp r3, #0x3
	blt _020833B6
_020833C4:
	add sp, #0x10
	pop {r4-r5}
	bx lr
	nop
_020833CC: .word 0x020FBC08
_020833D0: .word 0x0000012A

	thumb_func_start FUN_020833D4
FUN_020833D4: ; 0x020833D4
	push {r3, lr}
	cmp r0, #0x0
	bne _020833EE
	mov r0, #0x1
	bl FUN_02002B60
	mov r0, #0x3
	bl FUN_02002B7C
	mov r0, #0x1
	bl FUN_02002BB8
	pop {r3, pc}
_020833EE:
	mov r0, #0x1
	bl FUN_02002B7C
	mov r0, #0x0
	bl FUN_02002B60
	mov r0, #0x0
	bl FUN_02002BB8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02083404
FUN_02083404: ; 0x02083404
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02002B60
	mov r0, #0x0
	bl FUN_02002B7C
	mov r0, #0x0
	bl FUN_02002BB8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0208341C
FUN_0208341C: ; 0x0208341C
	push {r3, lr}
	cmp r1, #0x4
	bhi _0208344C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0208342E: ; jump table (using 16-bit offset)
	.short _02083438 - _0208342E - 2; case 0
	.short _0208343C - _0208342E - 2; case 1
	.short _02083440 - _0208342E - 2; case 2
	.short _02083444 - _0208342E - 2; case 3
	.short _02083448 - _0208342E - 2; case 4
_02083438:
	add r0, #0x7a
	pop {r3, pc}
_0208343C:
	add r0, #0x7e
	pop {r3, pc}
_02083440:
	add r0, #0x82
	pop {r3, pc}
_02083444:
	add r0, #0x86
	pop {r3, pc}
_02083448:
	add r0, #0x8a
	pop {r3, pc}
_0208344C:
	bl ErrorHandling
	mov r0, #0x7a
	pop {r3, pc}

	thumb_func_start FUN_02083454
FUN_02083454: ; 0x02083454
	push {r4-r5, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r5, #0x3
	beq _02083464
	cmp r1, #0x1
	bne _02083474
_02083464:
	bl rand_LC
	mov r1, #0xc
	bl _s32_div_f
	add sp, #0xc
	add r0, r1, #0x0
	pop {r4-r5, pc}
_02083474:
	add r0, sp, #0x0
	add r1, r4, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	mov r1, #0x2
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	mov r1, #0x3
	strb r1, [r0, #0x1]
	mov r1, #0x4
	add r4, r4, #0x3
	strb r1, [r0, #0x2]
	cmp r5, #0x1
	blt _020834A6
	mov r0, #0x0
	add r2, sp, #0x0
	strb r0, [r2, r4]
	mov r1, #0x1
	add r0, r4, #0x1
	strb r1, [r2, r0]
	add r1, r4, #0x2
	mov r0, #0x5
	add r4, r4, #0x3
	strb r0, [r2, r1]
_020834A6:
	cmp r5, #0x2
	blt _020834BE
	mov r0, #0x6
	add r2, sp, #0x0
	strb r0, [r2, r4]
	mov r1, #0x7
	add r0, r4, #0x1
	strb r1, [r2, r0]
	add r1, r4, #0x2
	mov r0, #0x8
	add r4, r4, #0x3
	strb r0, [r2, r1]
_020834BE:
	bl rand_LC
	add r1, r4, #0x0
	bl _s32_div_f
	add r0, sp, #0x0
	ldrb r0, [r0, r1]
	add sp, #0xc
	pop {r4-r5, pc}

	thumb_func_start FUN_020834D0
FUN_020834D0: ; 0x020834D0
	ldr r3, _020834DC ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _020834E0 ; =0x020FBED8
	mov r1, #0x10
	bx r3
	nop
_020834DC: .word FUN_0202D8D0
_020834E0: .word 0x020FBED8

	thumb_func_start FUN_020834E4
FUN_020834E4: ; 0x020834E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xa
	add r4, r1, #0x0
	cmp r2, r0
	blt _020834F6
	bl ErrorHandling
_020834F6:
	ldr r0, _02083500 ; =0x00000985
	add r1, r4, r0
	lsl r0, r5, #0xa
	add r0, r1, r0
	pop {r3-r5, pc}
	.balign 4
_02083500: .word 0x00000985

	thumb_func_start FUN_02083504
FUN_02083504: ; 0x02083504
	mov r0, #0xa
	bx lr

	thumb_func_start FUN_02083508
FUN_02083508: ; 0x02083508
	mov r0, #0x8
	bx lr

	thumb_func_start FUN_0208350C
FUN_0208350C: ; 0x0208350C
	bx lr
	.balign 4

	thumb_func_start FUN_02083510
FUN_02083510: ; 0x02083510
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x17
	lsl r0, r0, #0x4
	add r6, r1, #0x0
	ldrb r1, [r3, r0]
	str r2, [sp, #0x0]
	cmp r1, #0x0
	bne _0208352C
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	ldr r0, _02083590 ; =0x000004FC
	add r4, r1, r0
	b _0208355E
_0208352C:
	cmp r1, #0x1
	bne _0208353A
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	ldr r0, _02083594 ; =0x00001158
	add r4, r1, r0
	b _0208355E
_0208353A:
	cmp r1, #0x2
	bne _0208354A
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	mov r0, #0xc3
	lsl r0, r0, #0x4
	add r4, r1, r0
	b _0208355E
_0208354A:
	cmp r1, #0x3
	bne _02083558
	sub r0, r0, #0x4
	ldr r1, [r3, r0]
	ldr r0, _02083598 ; =0x0000085C
	add r4, r1, r0
	b _0208355E
_02083558:
	bl ErrorHandling
	pop {r3-r7, pc}
_0208355E:
	mov r0, #0x2
	lsl r0, r0, #0x8
	cmp r6, r0
	ble _0208356A
	bl ErrorHandling
_0208356A:
	ldr r0, _0208359C ; =0x00000A11
	add r7, r4, r0
	ldrb r0, [r7, r5]
	cmp r0, #0x0
	beq _02083578
	bl ErrorHandling
_02083578:
	mov r1, #0x21
	lsl r1, r1, #0x4
	add r2, r4, r1
	lsl r1, r5, #0x9
	add r1, r2, r1
	ldr r0, [sp, #0x0]
	add r2, r6, #0x0
	bl MI_CpuCopy8
	mov r0, #0x1
	strb r0, [r7, r5]
	pop {r3-r7, pc}
	.balign 4
_02083590: .word 0x000004FC
_02083594: .word 0x00001158
_02083598: .word 0x0000085C
_0208359C: .word 0x00000A11

	thumb_func_start FUN_020835A0
FUN_020835A0: ; 0x020835A0
	mov r0, #0x5b
	lsl r0, r0, #0x2
	ldr r0, [r3, r0]
	ldr r3, _020835AC ; =MOD12_0223D1CC
	add r1, r2, #0x0
	bx r3
	.balign 4
_020835AC: .word MOD12_0223D1CC

	thumb_func_start FUN_020835B0
FUN_020835B0: ; 0x020835B0
	push {r3-r6, lr}
	sub sp, #0x14
	add r5, r1, #0x0
	mov r1, #0x61
	add r6, r0, #0x0
	add r4, r3, #0x0
	lsl r1, r1, #0x2
	add r0, r2, #0x0
	add r2, r4, r1
	lsl r1, r6, #0x8
	add r1, r2, r1
	add r2, r5, #0x0
	bl MI_CpuCopy8
	ldr r2, _02083628 ; =0x00000584
	ldrb r0, [r4, r2]
	add r0, r0, #0x1
	strb r0, [r4, r2]
	ldr r0, _0208362C ; =0x00000127
	ldrb r2, [r4, r2]
	ldrb r1, [r4, r0]
	cmp r2, r1
	blo _02083622
	mov r3, #0x0
	cmp r1, #0x0
	ble _020835FE
	add r0, #0x5d
	add r5, r4, r0
	mov r0, #0x1
	lsl r0, r0, #0x8
	add r2, r0, #0x0
	add r6, sp, #0x4
	add r2, #0x27
_020835F2:
	stmia r6!, {r5}
	ldrb r1, [r4, r2]
	add r3, r3, #0x1
	add r5, r5, r0
	cmp r3, r1
	blt _020835F2
_020835FE:
	add r0, sp, #0x4
	add r2, sp, #0x0
	bl FUN_02083660
	mov r1, #0x47
	lsl r1, r1, #0x2
	strb r0, [r4, r1]
	add r0, sp, #0x0
	ldrb r2, [r0, #0x0]
	add r0, r1, #0x1
	strb r2, [r4, r0]
	ldrb r0, [r4, r1]
	lsl r2, r0, #0x2
	add r0, sp, #0x4
	ldr r0, [r0, r2]
	ldrb r2, [r0, #0x2]
	add r0, r1, #0x6
	strb r2, [r4, r0]
_02083622:
	add sp, #0x14
	pop {r3-r6, pc}
	nop
_02083628: .word 0x00000584
_0208362C: .word 0x00000127

	thumb_func_start FUN_02083630
FUN_02083630: ; 0x02083630
	push {r3, lr}
	ldr r1, _0208365C ; =0x00000125
	add r3, sp, #0x0
	ldrb r2, [r0, r1]
	strb r2, [r3, #0x0]
	sub r2, r1, #0x2
	ldrb r2, [r0, r2]
	sub r1, r1, #0x3
	strb r2, [r3, #0x1]
	ldrb r0, [r0, r1]
	add r1, sp, #0x0
	mov r2, #0x4
	strb r0, [r3, #0x2]
	mov r0, #0x1a
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _02083658
	mov r0, #0x1
	pop {r3, pc}
_02083658:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0208365C: .word 0x00000125

	thumb_func_start FUN_02083660
FUN_02083660: ; 0x02083660
	push {r4-r7}
	mov r5, #0x0
	add r4, r5, #0x0
	cmp r1, #0x0
	ble _02083684
	add r6, r0, #0x0
_0208366C:
	lsl r3, r5, #0x2
	ldr r3, [r0, r3]
	ldr r7, [r6, #0x0]
	ldrb r3, [r3, #0x0]
	ldrb r7, [r7, #0x0]
	cmp r3, r7
	bhs _0208367C
	add r5, r4, #0x0
_0208367C:
	add r4, r4, #0x1
	add r6, r6, #0x4
	cmp r4, r1
	blt _0208366C
_02083684:
	lsl r1, r5, #0x2
	ldr r0, [r0, r1]
	ldrb r0, [r0, #0x0]
	strb r0, [r2, #0x0]
	add r0, r5, #0x0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02083694
FUN_02083694: ; 0x02083694
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_020669BC
	add r2, r0, #0x0
	ldrb r1, [r5, r2]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	bl MI_CpuCopy8
	ldr r0, _020836B8 ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	nop
_020836B8: .word 0x00000584

	thumb_func_start FUN_020836BC
FUN_020836BC: ; 0x020836BC
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_020669BC
	add r4, r0, #0x0
	mov r0, #0x14
	add r1, r4, #0x1
	bl FUN_02016998
	add r5, r0, #0x0
	add r0, r7, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl MI_CpuCopy8
	mov r0, #0x1b
	add r1, r5, #0x0
	add r2, r4, #0x1
	strb r6, [r5, r4]
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _020836F0
	mov r4, #0x1
	b _020836F2
_020836F0:
	mov r4, #0x0
_020836F2:
	add r0, r5, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020836FC
FUN_020836FC: ; 0x020836FC
	push {r3-r7, lr}
	sub sp, #0x8
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl FUN_020669BC
	mov r7, #0x0
	ldr r4, [sp, #0x4]
	add r6, r0, #0x0
	add r5, r7, #0x0
_02083710:
	ldr r0, [sp, #0x0]
	ldr r1, [r4, #0x0]
	add r0, r0, r5
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, #0x4
	add r5, r5, r6
	cmp r7, #0x4
	blt _02083710
	ldr r1, _02083738 ; =0x00000584
	ldr r0, [sp, #0x4]
	ldrb r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	strb r2, [r0, r1]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02083738: .word 0x00000584

	thumb_func_start FUN_0208373C
FUN_0208373C: ; 0x0208373C
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020669BC
	add r6, r0, #0x0
	lsl r0, r6, #0x2
	str r0, [sp, #0x0]
	ldr r0, _02083788 ; =0x00000585
	mov r7, #0x0
	add r0, r4, r0
	str r0, [sp, #0x4]
	add r4, r7, #0x0
_02083758:
	ldr r1, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r1, r4
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, r6
	add r5, r5, #0x4
	cmp r7, #0x4
	blt _02083758
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mov r0, #0x1c
	bl FUN_02030A78
	cmp r0, #0x1
	bne _02083782
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02083782:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02083788: .word 0x00000585

	thumb_func_start FUN_0208378C
FUN_0208378C: ; 0x0208378C
	push {r3-r5, lr}
	add r0, r2, #0x0
	add r2, #0x30
	ldrb r1, [r2, #0x0]
	add r4, r3, #0x0
	add r5, r4, #0x0
	mov r2, #0x30
	add r3, r1, #0x0
	add r5, #0x10
	mul r3, r2
	add r1, r5, r3
	bl MI_CpuCopy8
	ldr r0, _020837B0 ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	.balign 4
_020837B0: .word 0x00000584

	thumb_func_start FUN_020837B4
FUN_020837B4: ; 0x020837B4
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r0, #0x14
	mov r1, #0x31
	add r6, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	mov r2, #0x30
	bl MI_CpuCopy8
	add r0, r4, #0x0
	add r0, #0x30
	strb r5, [r0, #0x0]
	mov r0, #0x1d
	add r1, r4, #0x0
	mov r2, #0x31
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _020837E6
	mov r5, #0x1
	b _020837E8
_020837E6:
	mov r5, #0x0
_020837E8:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020837F4
FUN_020837F4: ; 0x020837F4
	push {r3-r7, lr}
	add r5, r3, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	mov r4, #0x0
	add r5, #0xd0
	mov r7, #0x8
_02083802:
	lsl r0, r4, #0x3
	add r0, r6, r0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl MI_CpuCopy8
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x3
	blt _02083802
	ldrb r2, [r6, #0x18]
	ldr r1, _0208382C ; =0x0000011E
	ldr r0, [sp, #0x0]
	strb r2, [r0, r1]
	ldr r1, _02083830 ; =0x00000584
	ldrb r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	nop
_0208382C: .word 0x0000011E
_02083830: .word 0x00000584

	thumb_func_start FUN_02083834
FUN_02083834: ; 0x02083834
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	mov r0, #0x14
	mov r1, #0x19
	add r5, r2, #0x0
	bl FUN_02016998
	add r6, r0, #0x0
	mov r4, #0x0
	mov r7, #0x8
_02083848:
	lsl r1, r4, #0x3
	add r0, r5, #0x0
	add r1, r6, r1
	add r2, r7, #0x0
	bl MI_CpuCopy8
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x3
	blt _02083848
	ldr r1, _02083884 ; =0x0000011E
	ldr r0, [sp, #0x0]
	mov r2, #0x19
	ldrb r0, [r0, r1]
	add r1, r6, #0x0
	strb r0, [r6, #0x18]
	mov r0, #0x1e
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _02083876
	mov r4, #0x1
	b _02083878
_02083876:
	mov r4, #0x0
_02083878:
	add r0, r6, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_02083884: .word 0x0000011E

	thumb_func_start FUN_02083888
FUN_02083888: ; 0x02083888
	push {r3-r7, lr}
	add r5, r2, #0x0
	ldrb r0, [r5, #0x0]
	add r6, r3, #0x0
	add r4, r6, #0x0
	add r4, #0xe8
	lsl r7, r0, #0x2
	ldr r0, [r4, r7]
	bl FUN_02021A4C
	ldr r0, [r4, r7]
	add r1, r5, #0x4
	bl FUN_02021E28
	ldr r0, _020838B0 ; =0x00000584
	ldrb r1, [r6, r0]
	add r1, r1, #0x1
	strb r1, [r6, r0]
	pop {r3-r7, pc}
	nop
_020838B0: .word 0x00000584

	thumb_func_start FUN_020838B4
FUN_020838B4: ; 0x020838B4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	add r0, r2, #0x0
	add r1, sp, #0x0
	mov r2, #0x8
	bl FUN_02021EF0
	mov r0, #0x14
	add r1, r0, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, sp, #0x0
	add r1, r4, #0x4
	mov r2, #0x10
	bl MI_CpuCopy8
	strb r5, [r4, #0x0]
	mov r0, #0x10
	strb r0, [r4, #0x1]
	mov r0, #0x0
	strb r0, [r4, #0x2]
	strb r0, [r4, #0x3]
	mov r0, #0x1f
	add r1, r4, #0x0
	mov r2, #0x14
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _020838F6
	mov r5, #0x1
	b _020838F8
_020838F6:
	mov r5, #0x0
_020838F8:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02083904
FUN_02083904: ; 0x02083904
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02026FE4
	add r2, r0, #0x0
	ldrb r1, [r5, r2]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	add r1, r4, r1
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	bl MI_CpuCopy8
	ldr r0, _0208392C ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	nop
_0208392C: .word 0x00000584

	thumb_func_start FUN_02083930
FUN_02083930: ; 0x02083930
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_02026FE4
	add r4, r0, #0x0
	mov r0, #0x14
	add r1, r4, #0x1
	bl FUN_02016998
	add r5, r0, #0x0
	add r0, r7, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl MI_CpuCopy8
	mov r0, #0x20
	add r1, r5, #0x0
	add r2, r4, #0x1
	strb r6, [r5, r4]
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _02083964
	mov r4, #0x1
	b _02083966
_02083964:
	mov r4, #0x0
_02083966:
	add r0, r5, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02083970
FUN_02083970: ; 0x02083970
	push {r3-r7, lr}
	sub sp, #0x8
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl FUN_02026FE4
	add r6, r0, #0x0
	mov r0, #0x1
	lsl r1, r6, #0x2
	lsl r0, r0, #0xa
	cmp r1, r0
	blt _0208398C
	bl ErrorHandling
_0208398C:
	mov r7, #0x0
	ldr r4, [sp, #0x4]
	add r5, r7, #0x0
_02083992:
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0xf8
	ldr r1, [r1, #0x0]
	add r0, r0, r5
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, #0x4
	add r5, r5, r6
	cmp r7, #0x4
	blt _02083992
	ldr r1, _020839BC ; =0x00000584
	ldr r0, [sp, #0x4]
	ldrb r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	strb r2, [r0, r1]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020839BC: .word 0x00000584

	thumb_func_start FUN_020839C0
FUN_020839C0: ; 0x020839C0
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_02026FE4
	add r6, r0, #0x0
	mov r1, #0x1
	lsl r0, r6, #0x2
	lsl r1, r1, #0xa
	str r0, [sp, #0x0]
	cmp r0, r1
	blt _020839DE
	bl ErrorHandling
_020839DE:
	ldr r0, _02083A18 ; =0x00000585
	mov r7, #0x0
	add r0, r4, r0
	str r0, [sp, #0x4]
	add r4, r7, #0x0
_020839E8:
	ldr r1, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r1, r4
	add r2, r6, #0x0
	bl MI_CpuCopy8
	add r7, r7, #0x1
	add r4, r4, r6
	add r5, r5, #0x4
	cmp r7, #0x4
	blt _020839E8
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mov r0, #0x21
	bl FUN_02030A78
	cmp r0, #0x1
	bne _02083A12
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02083A12:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02083A18: .word 0x00000585

	thumb_func_start FUN_02083A1C
FUN_02083A1C: ; 0x02083A1C
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _02083A30 ; =0x000019A0
	add r0, r2, #0x0
	add r1, r3, r1
	add r2, r4, #0x0
	bl MI_CpuCopy8
	pop {r4, pc}
	nop
_02083A30: .word 0x000019A0

	thumb_func_start FUN_02083A34
FUN_02083A34: ; 0x02083A34
	push {r3, lr}
	add r3, r0, #0x0
	ldrb r0, [r3, #0x16]
	cmp r0, #0x0
	bne _02083A44
	str r1, [r3, #0x0]
	mov r0, #0x1
	pop {r3, pc}
_02083A44:
	ldrb r2, [r3, #0x14]
	ldrb r0, [r3, #0x15]
	cmp r2, r0
	beq _02083A50
	mov r0, #0x0
	pop {r3, pc}
_02083A50:
	str r1, [r3, #0x8]
	add r3, #0x8
	mov r0, #0x22
	add r1, r3, #0x0
	mov r2, #0x8
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _02083A66
	mov r0, #0x1
	pop {r3, pc}
_02083A66:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02083A6C
FUN_02083A6C: ; 0x02083A6C
	ldrb r2, [r2, #0x4]
	add r1, r3, r0
	ldr r0, _02083A78 ; =0x000019B0
	strb r2, [r1, r0]
	bx lr
	nop
_02083A78: .word 0x000019B0

	thumb_func_start FUN_02083A7C
FUN_02083A7C: ; 0x02083A7C
	push {r3, lr}
	add r2, r0, #0x0
	ldrb r0, [r2, #0x16]
	cmp r0, #0x0
	bne _02083A8C
	strb r1, [r2, #0x10]
	mov r0, #0x1
	pop {r3, pc}
_02083A8C:
	strb r1, [r2, #0xc]
	add r2, #0x8
	add r1, r2, #0x0
	mov r0, #0x23
	mov r2, #0x8
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _02083AA2
	mov r0, #0x1
	pop {r3, pc}
_02083AA2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02083AA8
FUN_02083AA8: ; 0x02083AA8
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02029EC4
	add r2, r0, #0x0
	ldrb r1, [r5, r2]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	add r3, r4, r1
	mov r1, #0x57
	lsl r1, r1, #0x2
	ldr r1, [r3, r1]
	bl MI_CpuCopy8
	ldr r0, _02083AD0 ; =0x00000584
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r3-r5, pc}
	.balign 4
_02083AD0: .word 0x00000584

	thumb_func_start FUN_02083AD4
FUN_02083AD4: ; 0x02083AD4
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02029EC4
	add r5, r0, #0x0
	ldr r0, _02083B0C ; =0x00000585
	add r4, r4, r0
	cmp r6, #0x0
	beq _02083AF4
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl MI_CpuCopy8
_02083AF4:
	mov r0, #0x24
	add r1, r4, #0x0
	add r2, r5, #0x1
	strb r7, [r4, r5]
	bl FUN_02030A78
	cmp r0, #0x1
	bne _02083B08
	mov r0, #0x1
	pop {r3-r7, pc}
_02083B08:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02083B0C: .word 0x00000585

	thumb_func_start FUN_02083B10
FUN_02083B10: ; 0x02083B10
	push {r3-r6}
	ldrb r1, [r2, #0x6]
	ldrb r4, [r2, #0x0]
	mov r5, #0x42
	add r0, r3, r1
	lsl r5, r5, #0x2
	strb r4, [r0, r5]
	ldrb r6, [r2, #0x1]
	add r4, r5, #0x4
	strb r6, [r0, r4]
	add r4, r5, #0x0
	ldrb r6, [r2, #0x2]
	add r4, #0x8
	add r5, #0xc
	strb r6, [r0, r4]
	lsl r0, r1, #0x1
	ldrh r2, [r2, #0x4]
	add r0, r3, r0
	strh r2, [r0, r5]
	ldr r0, _02083B44 ; =0x00000584
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	pop {r3-r6}
	bx lr
	nop
_02083B44: .word 0x00000584

	thumb_func_start FUN_02083B48
FUN_02083B48: ; 0x02083B48
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r0, #0x14
	mov r1, #0x7
	add r6, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r0, #0x25
	add r1, r4, #0x0
	mov r2, #0x7
	strb r5, [r4, #0x6]
	bl FUN_02030ADC
	cmp r0, #0x1
	bne _02083B76
	mov r5, #0x1
	b _02083B78
_02083B76:
	mov r5, #0x0
_02083B78:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02083B84
FUN_02083B84: ; 0x02083B84
	ldr r3, _02083B90 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _02083B94 ; =0x020FBF98
	mov r1, #0xb
	bx r3
	nop
_02083B90: .word FUN_0202D8D0
_02083B94: .word 0x020FBF98

	thumb_func_start FUN_02083B98
FUN_02083B98: ; 0x02083B98
	cmp r0, #0xc
	bne _02083BA0
	mov r0, #0xc
	bx lr
_02083BA0:
	cmp r0, #0x6
	bhs _02083BA8
	add r0, r0, #0x6
	bx lr
_02083BA8:
	sub r0, r0, #0x6
	bx lr

	thumb_func_start FUN_02083BAC
FUN_02083BAC: ; 0x02083BAC
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083C1A
	ldr r0, _02083C1C ; =0x0000221C
	mov r2, #0x59
	ldr r0, [r4, r0]
	add r1, r6, #0x0
	lsl r2, r2, #0x4
	bl memcpy
	ldr r0, [r4, #0x58]
	add r0, r0, #0x1
	str r0, [r4, #0x58]
	bl FUN_0206B8A4
	mov r1, #0x59
	ldr r2, [r4, #0x58]
	lsl r1, r1, #0x4
	mul r1, r2
	cmp r1, r0
	blt _02083C06
	bl FUN_02031190
	cmp r0, #0x1
	bne _02083BF6
	add r0, r4, #0x0
	mov r1, #0x1b
	mov r2, #0x0
	bl MOD70_0222F440
	b _02083C14
_02083BF6:
	bl FUN_02031190
	ldr r1, _02083C20 ; =0x00002218
	ldr r2, [r4, #0x50]
	ldr r1, [r4, r1]
	bl MOD70_0222F480
	b _02083C14
_02083C06:
	bl FUN_02031190
	ldr r1, _02083C20 ; =0x00002218
	ldr r2, [r4, #0x50]
	ldr r1, [r4, r1]
	bl MOD70_0222F480
_02083C14:
	ldr r0, [r4, #0x50]
	add r0, r0, #0x1
	str r0, [r4, #0x50]
_02083C1A:
	pop {r4-r6, pc}
	.balign 4
_02083C1C: .word 0x0000221C
_02083C20: .word 0x00002218

	thumb_func_start FUN_02083C24
FUN_02083C24: ; 0x02083C24
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083C40
	ldrb r0, [r6, #0x0]
	bl FUN_02083B98
	add r4, #0x8c
	str r0, [r4, #0x0]
_02083C40:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02083C44
FUN_02083C44: ; 0x02083C44
	add r3, #0x84
	ldrb r2, [r2, #0x0]
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x2
	add r0, r1, r0
	str r2, [r0, #0x60]
	bx lr
	.balign 4

	thumb_func_start FUN_02083C54
FUN_02083C54: ; 0x02083C54
	bx lr
	.balign 4

	thumb_func_start FUN_02083C58
FUN_02083C58: ; 0x02083C58
	bx lr
	.balign 4

	thumb_func_start FUN_02083C5C
FUN_02083C5C: ; 0x02083C5C
	add r3, #0x84
	ldr r0, [r3, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x54]
	bx lr
	.balign 4

	thumb_func_start FUN_02083C68
FUN_02083C68: ; 0x02083C68
	bx lr
	.balign 4

	thumb_func_start FUN_02083C6C
FUN_02083C6C: ; 0x02083C6C
	add r3, #0x84
	mov r0, #0x8b
	ldrb r2, [r2, #0x0]
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x6
	str r2, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02083C7C
FUN_02083C7C: ; 0x02083C7C
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, [r3, #0xc]
	add r5, r2, #0x0
	bl FUN_0202A918
	add r4, r0, #0x0
	bl FUN_02031190
	cmp r6, r0
	beq _02083CA8
	mov r2, #0x0
_02083C94:
	ldrb r1, [r5, r2]
	cmp r1, #0x0
	beq _02083CA2
	ldrb r0, [r4, r2]
	cmp r0, r1
	beq _02083CA2
	strb r1, [r4, r2]
_02083CA2:
	add r2, r2, #0x1
	cmp r2, #0xe
	blt _02083C94
_02083CA8:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02083CAC
FUN_02083CAC: ; 0x02083CAC
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083CD0
	ldr r0, _02083CD4 ; =0x00002224
	add r1, r6, #0x0
	ldr r0, [r4, r0]
	mov r2, #0x1
	mov r3, #0x1a
	bl FUN_02025520
	mov r0, #0x3
	str r0, [r4, #0x54]
_02083CD0:
	pop {r4-r6, pc}
	nop
_02083CD4: .word 0x00002224

	thumb_func_start FUN_02083CD8
FUN_02083CD8: ; 0x02083CD8
	push {r4-r6, lr}
	add r3, #0x84
	add r5, r0, #0x0
	add r6, r2, #0x0
	ldr r4, [r3, #0x0]
	bl FUN_02031190
	cmp r5, r0
	beq _02083D0A
	ldr r1, _02083D0C ; =0x00002E14
	mov r2, #0xfb
	add r3, r4, r1
	lsl r2, r2, #0x2
	add r1, r5, #0x0
	mul r1, r2
	add r0, r6, #0x0
	add r1, r3, r1
	sub r2, r2, #0x4
	bl MIi_CpuCopyFast
	mov r0, #0x4
	str r0, [r4, #0x54]
	mov r0, #0x0
	bl FUN_02031400
_02083D0A:
	pop {r4-r6, pc}
	.balign 4
_02083D0C: .word 0x00002E14

	thumb_func_start FUN_02083D10
FUN_02083D10: ; 0x02083D10
	add r0, #0x84
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02083D18
FUN_02083D18: ; 0x02083D18
	mov r0, #0xfb
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02083D20
FUN_02083D20: ; 0x02083D20
	mov r0, #0xe
	bx lr

	thumb_func_start FUN_02083D24
FUN_02083D24: ; 0x02083D24
	mov r0, #0x88
	bx lr

	thumb_func_start FUN_02083D28
FUN_02083D28: ; 0x02083D28
	mov r0, #0x59
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02083D30
FUN_02083D30: ; 0x02083D30
	add r1, #0x84
	ldr r2, [r1, #0x0]
	ldr r1, _02083D44 ; =0x000022F4
	add r2, r2, r1
	mov r1, #0x59
	lsl r1, r1, #0x4
	mul r1, r0
	add r0, r2, r1
	bx lr
	nop
_02083D44: .word 0x000022F4

	thumb_func_start FUN_02083D48
FUN_02083D48: ; 0x02083D48
	ldr r3, _02083D54 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _02083D58 ; =0x020FC01C
	mov r1, #0x6c
	bx r3
	nop
_02083D54: .word FUN_0202D8D0
_02083D58: .word 0x020FC01C

	thumb_func_start FUN_02083D5C
FUN_02083D5C: ; 0x02083D5C
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02083DBA
	mov r3, #0xfb
	lsl r3, r3, #0x2
	ldrb r2, [r5, r3]
	sub r0, r3, #0x4
	add r1, r2, #0x0
	mul r1, r0
	mov r0, #0xe1
	lsl r0, r0, #0x6
	cmp r1, r0
	ldr r2, _02083DE8 ; =0x000043D0
	ble _02083D90
	add r2, r4, r2
	add r1, r2, r1
	mov r2, #0x19
	add r0, r5, #0x0
	lsl r2, r2, #0x4
	bl MIi_CpuCopyFast
	b _02083D9C
_02083D90:
	add r2, r4, r2
	add r1, r2, r1
	add r0, r5, #0x0
	sub r2, r3, #0x4
	bl MIi_CpuCopyFast
_02083D9C:
	mov r1, #0xb5
	ldr r0, _02083DE8 ; =0x000043D0
	lsl r1, r1, #0x2
	mov r2, #0xe1
	ldr r1, [r4, r1]
	add r0, r4, r0
	lsl r2, r2, #0x6
	bl MIi_CpuCopyFast
	mov r0, #0xb2
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_020191D0
	pop {r3-r5, pc}
_02083DBA:
	ldr r1, _02083DEC ; =0x000043CC
	mov r0, #0xfa
	ldr r2, [r4, r1]
	lsl r0, r0, #0x2
	add r3, r2, #0x0
	mul r3, r0
	mov r0, #0xe1
	lsl r0, r0, #0x6
	cmp r3, r0
	bge _02083DDC
	add r0, r2, #0x1
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0208402C
	pop {r3-r5, pc}
_02083DDC:
	mov r1, #0x0
	mov r0, #0x7c
	add r2, r1, #0x0
	bl FUN_02030BC4
	pop {r3-r5, pc}
	.balign 4
_02083DE8: .word 0x000043D0
_02083DEC: .word 0x000043CC

	thumb_func_start FUN_02083DF0
FUN_02083DF0: ; 0x02083DF0
	push {r3-r4}
	cmp r0, #0x0
	beq _02083E0E
	add r4, r0, #0x0
	mov r1, #0xa
	mul r4, r1
	ldr r0, _02083E14 ; =0x000093BD
	add r3, r3, r4
	add r3, r3, r0
_02083E02:
	ldrb r0, [r2, #0x0]
	add r2, r2, #0x1
	strb r0, [r3, #0x0]
	add r3, r3, #0x1
	sub r1, r1, #0x1
	bne _02083E02
_02083E0E:
	pop {r3-r4}
	bx lr
	nop
_02083E14: .word 0x000093BD

	thumb_func_start FUN_02083E18
FUN_02083E18: ; 0x02083E18
	push {r4-r7}
	cmp r3, #0x0
	beq _02083E42
	cmp r0, #0x0
	bne _02083E42
	ldr r0, _02083E48 ; =0x00004382
	mov r7, #0x0
_02083E26:
	add r6, r2, #0x0
	add r5, r3, r0
	mov r4, #0xa
_02083E2C:
	ldrb r1, [r6, #0x0]
	add r6, r6, #0x1
	strb r1, [r5, #0x0]
	add r5, r5, #0x1
	sub r4, r4, #0x1
	bne _02083E2C
	add r7, r7, #0x1
	add r2, #0xa
	add r3, #0xa
	cmp r7, #0x5
	blt _02083E26
_02083E42:
	pop {r4-r7}
	bx lr
	nop
_02083E48: .word 0x00004382

	thumb_func_start FUN_02083E4C
FUN_02083E4C: ; 0x02083E4C
	push {r4, lr}
	add r4, r3, #0x0
	add r0, r4, #0x0
	mov r1, #0x3
	mov r2, #0x0
	bl MOD53_021D8B64
	ldr r1, _02083E8C ; =0x000043D0
	mov r2, #0xe1
	mov r0, #0x0
	add r1, r4, r1
	lsl r2, r2, #0x6
	bl MIi_CpuClearFast
	bl FUN_02031190
	cmp r0, #0x0
	bne _02083E8A
	bl FUN_02030F20
	mov r1, #0xc6
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	bl FUN_0202CB8C
	mov r1, #0xc7
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, _02083E90 ; =0x000093F4
	mov r1, #0x1
	str r1, [r4, r0]
_02083E8A:
	pop {r4, pc}
	.balign 4
_02083E8C: .word 0x000043D0
_02083E90: .word 0x000093F4

	thumb_func_start FUN_02083E94
FUN_02083E94: ; 0x02083E94
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	cmp r6, #0x0
	beq _02083F2E
	bl FUN_02031190
	cmp r0, #0x0
	bne _02083F78
	ldrb r0, [r5, #0x0]
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	ldrb r0, [r5, #0x1]
	strb r0, [r1, #0x1]
	ldrb r0, [r5, #0x2]
	strb r0, [r1, #0x2]
	ldrb r0, [r5, #0x3]
	strb r0, [r1, #0x3]
	mov r0, #0xc6
	strb r6, [r1, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	strb r0, [r1, #0x1]
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _02083ED0
	cmp r0, #0x1
	b _02083F20
_02083ED0:
	bl FUN_02030F20
	mov r1, #0xc6
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _02083EFE
	bl MOD53_021D917C
	mov r1, #0xc6
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _02083EFE
	bl FUN_0202CB8C
	bl MATH_CountPopulation
	mov r1, #0xc6
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	cmp r1, r0
	beq _02083F06
_02083EFE:
	mov r1, #0x0
	add r0, sp, #0x0
	strb r1, [r0, #0x3]
	b _02083F20
_02083F06:
	ldr r0, _02083F7C ; =0x000093B4
	mov r1, #0x1
	add r2, r1, #0x0
	ldr r3, [r4, r0]
	lsl r2, r6
	orr r2, r3
	str r2, [r4, r0]
	add r0, sp, #0x0
	strb r1, [r0, #0x3]
	bl FUN_02030F20
	bl FUN_02032B6C
_02083F20:
	mov r0, #0x7e
	add r1, sp, #0x0
	mov r2, #0x4
	bl FUN_02030BC4
	add sp, #0x4
	pop {r3-r6, pc}
_02083F2E:
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _02083F3C
	cmp r0, #0x1
	beq _02083F6E
	add sp, #0x4
	pop {r3-r6, pc}
_02083F3C:
	ldrb r6, [r5, #0x0]
	bl FUN_02031190
	cmp r6, r0
	bne _02083F78
	ldrb r0, [r5, #0x3]
	cmp r0, #0x0
	bne _02083F5A
	add r0, r4, #0x0
	mov r1, #0x9
	add r2, r6, #0x0
	bl MOD53_021D8B64
	add sp, #0x4
	pop {r3-r6, pc}
_02083F5A:
	ldrb r1, [r5, #0x1]
	ldr r0, _02083F80 ; =0x000093B8
	strh r1, [r4, r0]
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x8
	bl MOD53_021D8B64
	add sp, #0x4
	pop {r3-r6, pc}
_02083F6E:
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x15
	bl MOD53_021D8B64
_02083F78:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02083F7C: .word 0x000093B4
_02083F80: .word 0x000093B8

	thumb_func_start FUN_02083F84
FUN_02083F84: ; 0x02083F84
	bx lr
	.balign 4

	thumb_func_start FUN_02083F88
FUN_02083F88: ; 0x02083F88
	push {r4, lr}
	ldrb r2, [r2, #0x0]
	add r4, r3, #0x0
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD53_021D8B64
	bl FUN_02031190
	cmp r0, #0x0
	bne _02083FB6
	mov r0, #0x3
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	cmp r0, #0x1
	bne _02083FB6
	ldr r1, _02083FB8 ; =0x000043CC
	mov r0, #0x0
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_0208402C
_02083FB6:
	pop {r4, pc}
	.balign 4
_02083FB8: .word 0x000043CC

	thumb_func_start FUN_02083FBC
FUN_02083FBC: ; 0x02083FBC
	bx lr
	.balign 4

	thumb_func_start FUN_02083FC0
FUN_02083FC0: ; 0x02083FC0
	bx lr
	.balign 4

	thumb_func_start FUN_02083FC4
FUN_02083FC4: ; 0x02083FC4
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02083FDA
	add r0, r4, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl MOD53_021D8B64
_02083FDA:
	pop {r4, pc}

	thumb_func_start FUN_02083FDC
FUN_02083FDC: ; 0x02083FDC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r3, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02083FEE
	bl ErrorHandling
_02083FEE:
	bl FUN_02031190
	cmp r0, #0x0
	bne _02084012
	ldr r0, _0208401C ; =0x000093FC
	ldr r1, [r4, r0]
	cmp r1, #0x0
	beq _0208400E
	add r0, sp, #0x0
	strb r5, [r0, #0x0]
	mov r0, #0x7b
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_02030BC4
	b _02084012
_0208400E:
	mov r1, #0x1
	str r1, [r4, r0]
_02084012:
	mov r0, #0x0
	mov r1, #0x1
	bl FUN_020334E8
	pop {r3-r5, pc}
	.balign 4
_0208401C: .word 0x000093FC

	thumb_func_start FUN_02084020
FUN_02084020: ; 0x02084020
	ldr r0, _02084028 ; =0x000093F4
	mov r1, #0x1
	str r1, [r3, r0]
	bx lr
	.balign 4
_02084028: .word 0x000093F4

	thumb_func_start FUN_0208402C
FUN_0208402C: ; 0x0208402C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb5
	mov r2, #0xfa
	add r4, r1, #0x0
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	lsl r2, r2, #0x2
	add r0, r4, #0x0
	mul r0, r2
	add r0, r1, r0
	ldr r1, _02084078 ; =0x00007C10
	add r1, r5, r1
	bl MIi_CpuCopyFast
	ldr r0, _02084078 ; =0x00007C10
	mov r2, #0x0
	add r1, r2, #0x0
	add r3, r5, r0
_02084052:
	ldr r0, [r3, #0x0]
	add r1, r1, #0x1
	eor r2, r0
	add r3, r3, #0x4
	cmp r1, #0xfa
	blt _02084052
	ldr r0, _0208407C ; =0x00007FF8
	ldr r1, _02084078 ; =0x00007C10
	str r2, [r5, r0]
	add r0, r0, #0x4
	mov r2, #0x3f
	strb r4, [r5, r0]
	mov r0, #0x76
	add r1, r5, r1
	lsl r2, r2, #0x4
	bl FUN_02030B3C
	pop {r3-r5, pc}
	nop
_02084078: .word 0x00007C10
_0208407C: .word 0x00007FF8

	thumb_func_start FUN_02084080
FUN_02084080: ; 0x02084080
	mov r2, #0x2
	lsl r2, r2, #0xe
	add r2, r1, r2
	mov r1, #0x3f
	lsl r1, r1, #0x4
	mul r1, r0
	add r0, r2, r1
	bx lr

	thumb_func_start FUN_02084090
FUN_02084090: ; 0x02084090
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02084094
FUN_02084094: ; 0x02084094
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02084098
FUN_02084098: ; 0x02084098
	ldr r3, _020840A4 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _020840A8 ; =0x020FC52C
	mov r1, #0x6c
	bx r3
	nop
_020840A4: .word FUN_0202D8D0
_020840A8: .word 0x020FC52C

	thumb_func_start FUN_020840AC
FUN_020840AC: ; 0x020840AC
	ldr r0, _020840B8 ; =0x00004A34
	ldr r1, [r3, r0]
	add r1, r1, #0x1
	str r1, [r3, r0]
	bx lr
	nop
_020840B8: .word 0x00004A34

	thumb_func_start FUN_020840BC
FUN_020840BC: ; 0x020840BC
	cmp r0, #0x0
	bne _020840C6
	ldrb r1, [r2, #0x0]
	ldr r0, _020840C8 ; =0x00004A3C
	str r1, [r3, r0]
_020840C6:
	bx lr
	.balign 4
_020840C8: .word 0x00004A3C

	thumb_func_start FUN_020840CC
FUN_020840CC: ; 0x020840CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0208410C ; =0x00004A34
	add r4, r3, #0x0
	mov r1, #0x0
	str r1, [r4, r0]
	mov r1, #0x1
	add r0, #0xc
	strb r1, [r4, r0]
	bl FUN_02031190
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02084270
	add r0, r4, #0x0
	bl MOD54_021D844C
	lsl r2, r5, #0x18
	add r0, r4, #0x0
	mov r1, #0x19
	lsr r2, r2, #0x18
	bl MOD54_021D88E4
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _02084110 ; =0x00000658
	bl FUN_020054C8
	pop {r3-r5, pc}
	.balign 4
_0208410C: .word 0x00004A34
_02084110: .word 0x00000658

	thumb_func_start FUN_02084114
FUN_02084114: ; 0x02084114
	add r0, r3, #0x0
	ldr r3, _02084120 ; =MOD54_021D88E4
	mov r1, #0x2
	mov r2, #0x0
	bx r3
	nop
_02084120: .word MOD54_021D88E4

	thumb_func_start FUN_02084124
FUN_02084124: ; 0x02084124
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	cmp r6, #0x0
	beq _020841BA
	bl FUN_02031190
	cmp r0, #0x0
	bne _02084204
	ldrb r0, [r5, #0x0]
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	ldrb r0, [r5, #0x1]
	strb r0, [r1, #0x1]
	ldrb r0, [r5, #0x2]
	strb r0, [r1, #0x2]
	ldrb r0, [r5, #0x3]
	strb r0, [r1, #0x3]
	ldr r0, _02084208 ; =0x00004A48
	strb r6, [r1, #0x0]
	ldr r0, [r4, r0]
	strb r0, [r1, #0x1]
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _0208415E
	cmp r0, #0x1
	b _020841AC
_0208415E:
	bl FUN_02030F20
	ldr r1, _02084208 ; =0x00004A48
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _02084186
	bl MOD54_021D8C24
	ldr r1, _02084208 ; =0x00004A48
	ldr r1, [r4, r1]
	cmp r1, r0
	bne _02084186
	bl FUN_0202CB8C
	bl MATH_CountPopulation
	ldr r1, _02084208 ; =0x00004A48
	ldr r2, [r4, r1]
	cmp r2, r0
	beq _0208418E
_02084186:
	mov r1, #0x0
	add r0, sp, #0x0
	strb r1, [r0, #0x3]
	b _020841AC
_0208418E:
	add r0, r1, #0x0
	add r0, #0x8
	mov r2, #0x1
	ldr r3, [r4, r0]
	add r0, r2, #0x0
	lsl r0, r6
	orr r0, r3
	add r1, #0x8
	str r0, [r4, r1]
	add r0, sp, #0x0
	strb r2, [r0, #0x3]
	bl FUN_02030F20
	bl FUN_02032B6C
_020841AC:
	mov r0, #0x70
	add r1, sp, #0x0
	mov r2, #0x4
	bl FUN_02030ADC
	add sp, #0x4
	pop {r3-r6, pc}
_020841BA:
	ldrb r0, [r5, #0x2]
	cmp r0, #0x0
	beq _020841C8
	cmp r0, #0x1
	beq _020841FA
	add sp, #0x4
	pop {r3-r6, pc}
_020841C8:
	ldrb r6, [r5, #0x0]
	bl FUN_02031190
	cmp r6, r0
	bne _02084204
	ldrb r0, [r5, #0x3]
	cmp r0, #0x0
	bne _020841E6
	add r0, r4, #0x0
	mov r1, #0x8
	add r2, r6, #0x0
	bl MOD54_021D88E4
	add sp, #0x4
	pop {r3-r6, pc}
_020841E6:
	ldrb r1, [r5, #0x1]
	ldr r0, _0208420C ; =0x00004A5C
	strh r1, [r4, r0]
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x7
	bl MOD54_021D88E4
	add sp, #0x4
	pop {r3-r6, pc}
_020841FA:
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x13
	bl MOD54_021D88E4
_02084204:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02084208: .word 0x00004A48
_0208420C: .word 0x00004A5C

	thumb_func_start FUN_02084210
FUN_02084210: ; 0x02084210
	push {r4, lr}
	ldrb r2, [r2, #0x0]
	add r4, r3, #0x0
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD54_021D89CC
	bl FUN_02031190
	cmp r0, #0x0
	bne _0208422E
	mov r0, #0x3b
	mov r1, #0x0
	lsl r0, r0, #0x4
	str r1, [r4, r0]
_0208422E:
	pop {r4, pc}

	thumb_func_start FUN_02084230
FUN_02084230: ; 0x02084230
	bx lr
	.balign 4

	thumb_func_start FUN_02084234
FUN_02084234: ; 0x02084234
	bx lr
	.balign 4

	thumb_func_start FUN_02084238
FUN_02084238: ; 0x02084238
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _0208424E
	add r0, r4, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl MOD54_021D88E4
_0208424E:
	pop {r4, pc}

	thumb_func_start FUN_02084250
FUN_02084250: ; 0x02084250
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0208426C
	add r0, sp, #0x0
	strb r4, [r0, #0x0]
	mov r0, #0x6e
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_02030ADC
_0208426C:
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02084270
FUN_02084270: ; 0x02084270
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0xed
	mov r3, #0x0
	lsl r0, r0, #0x2
	add r5, r4, r0
	add r2, r3, #0x0
	sub r0, #0xc6
_02084280:
	ldr r1, [r5, #0x0]
	add r2, r2, #0x1
	eor r3, r1
	add r5, r5, #0x4
	cmp r2, r0
	blt _02084280
	ldr r0, _020842AC ; =0x00000F6C
	str r3, [r4, r0]
	bl rand_LC
	mov r1, #0xf7
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	mov r1, #0xed
	lsl r1, r1, #0x2
	mov r2, #0x2f
	mov r0, #0x74
	add r1, r4, r1
	lsl r2, r2, #0x6
	bl FUN_02030A78
	pop {r3-r5, pc}
	.balign 4
_020842AC: .word 0x00000F6C

	thumb_func_start FUN_020842B0
FUN_020842B0: ; 0x020842B0
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020842B4
FUN_020842B4: ; 0x020842B4
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020842B8
FUN_020842B8: ; 0x020842B8
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_020842BC
FUN_020842BC: ; 0x020842BC
	ldr r2, _020842CC ; =0x00000F74
	add r2, r1, r2
	mov r1, #0x2f
	lsl r1, r1, #0x6
	mul r1, r0
	add r0, r2, r1
	bx lr
	nop
_020842CC: .word 0x00000F74

	thumb_func_start FUN_020842D0
FUN_020842D0: ; 0x020842D0
	ldr r0, _020842D4 ; =0x020FCA3C
	bx lr
	.balign 4
_020842D4: .word 0x020FCA3C

	thumb_func_start FUN_020842D8
FUN_020842D8: ; 0x020842D8
	mov r0, #0x9
	bx lr

	thumb_func_start FUN_020842DC
FUN_020842DC: ; 0x020842DC
	push {r3-r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x4]
	add r6, r0, #0x0
	add r7, r2, #0x0
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	add r2, r3, #0x0
	bl FUN_0206E710
	mov r1, #0xe
	add r4, r0, #0x0
	bl FUN_0206E7DC
	cmp r0, #0x1
	beq _02084308
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r7, pc}
_02084308:
	add r0, r6, #0x0
	mov r1, #0x9f
	mov r2, #0x0
	bl FUN_020671BC
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084332
	mov r0, #0x7
	tst r0, r5
	beq _02084332
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084332:
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084350
	mov r0, #0x88
	tst r0, r5
	beq _02084350
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084350:
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208436E
	mov r0, #0x10
	tst r0, r5
	beq _0208436E
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208436E:
	add r0, r4, #0x0
	mov r1, #0x12
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208438C
	mov r0, #0x20
	tst r0, r5
	beq _0208438C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208438C:
	add r0, r4, #0x0
	mov r1, #0x13
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020843AA
	mov r0, #0x40
	tst r0, r5
	beq _020843AA
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020843AA:
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x17
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _020843CE
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020843EA
_020843CE:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _020843EA
	cmp r5, #0x0
	bne _02084414
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020843EA:
	add r0, r4, #0x0
	mov r1, #0x26
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084414
	cmp r5, #0x0
	beq _02084414
	add r0, r6, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	cmp r5, r0
	bhs _02084414
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084414:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208443A
	add r0, r6, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x64
	bhs _0208443A
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208443A:
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084464
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r6, #0x0
	mov r2, #0x3
	bl FUN_02069168
	cmp r0, #0x0
	beq _02084464
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084464:
	add r0, r4, #0x0
	mov r1, #0x22
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _0208447C
	add r0, r4, #0x0
	mov r1, #0x23
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020844B2
_0208447C:
	add r1, r7, #0x0
	add r0, r6, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x3
	bhs _020844B2
	add r1, r7, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x0
	bl FUN_0206AB30
	cmp r0, #0x5
	blo _020844B2
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020844B2:
	add r0, r4, #0x0
	mov r1, #0x24
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020844D6
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02084DF0
	cmp r0, #0x1
	bne _020844D6
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020844D6:
	add r0, r4, #0x0
	mov r1, #0x25
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084502
	mov r5, #0x0
_020844E4:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02084DF0
	cmp r0, #0x1
	bne _020844FC
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020844FC:
	add r5, r5, #0x1
	cmp r5, #0x4
	blt _020844E4
_02084502:
	add r0, r6, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_020671BC
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0xc]
	add r0, r6, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	mov r1, #0x49
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _020845C6
	add r0, r4, #0x0
	mov r1, #0x27
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020845C6
	add r0, r4, #0x0
	mov r1, #0x30
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _0208459C
	cmp r5, #0x64
	bge _020845C6
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _020845C6
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208459C:
	bge _020845C6
	cmp r5, #0x0
	ble _020845AE
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020845AE:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _020845C6
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020845C6:
	add r0, r4, #0x0
	mov r1, #0x28
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084632
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02084606
	ldr r0, [sp, #0x14]
	cmp r0, #0x64
	bge _02084632
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _02084632
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084606:
	bge _02084632
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	ble _0208461A
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208461A:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _02084632
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084632:
	add r0, r4, #0x0
	mov r1, #0x29
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020846A0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02084674
	ldr r0, [sp, #0x10]
	cmp r0, #0x64
	bge _020846A0
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _020846A0
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084674:
	bge _020846A0
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	ble _02084688
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084688:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _020846A0
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020846A0:
	add r0, r4, #0x0
	mov r1, #0x2a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208470E
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _020846E2
	ldr r0, [sp, #0xc]
	cmp r0, #0x64
	bge _0208470E
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _0208470E
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020846E2:
	bge _0208470E
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	ble _020846F6
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020846F6:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _0208470E
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208470E:
	add r0, r4, #0x0
	mov r1, #0x2b
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208477C
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02084750
	ldr r0, [sp, #0x8]
	cmp r0, #0x64
	bge _0208477C
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _0208477C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084750:
	bge _0208477C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02084764
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084764:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _0208477C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208477C:
	add r0, r4, #0x0
	mov r1, #0x2c
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020847E6
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _020847BC
	cmp r7, #0x64
	bge _020847E6
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _020847E6
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020847BC:
	bge _020847E6
	cmp r7, #0x0
	ble _020847CE
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020847CE:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _020847E6
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020847E6:
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_020847F4: .word 0x000001FE

	thumb_func_start FUN_020847F8
FUN_020847F8: ; 0x020847F8
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r1, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0206B9B0
	ldr r3, [sp, #0x10]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020842DC
	pop {r3-r5, pc}

	thumb_func_start FUN_02084810
FUN_02084810: ; 0x02084810
	push {r3-r7, lr}
	sub sp, #0x70
	add r5, r0, #0x0
	ldr r0, [sp, #0x88]
	str r2, [sp, #0x4]
	str r0, [sp, #0x88]
	add r0, r1, #0x0
	ldr r2, [sp, #0x88]
	mov r1, #0x0
	str r3, [sp, #0x8]
	bl FUN_0206E710
	mov r1, #0xe
	add r4, r0, #0x0
	bl FUN_0206E7DC
	cmp r0, #0x1
	beq _02084840
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x70
	mov r0, #0x0
	pop {r3-r7, pc}
_02084840:
	mov r6, #0x0
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, r6, #0x0
	add r7, r6, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x50]
	str r0, [sp, #0x54]
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084868
	ldr r1, [sp, #0x54]
	mov r0, #0x7
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_02084868:
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208487E
	ldr r1, [sp, #0x54]
	ldr r0, _02084A28 ; =0xFFFFF077
	mov r7, #0x1
	and r0, r1
	str r0, [sp, #0x54]
_0208487E:
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084894
	ldr r1, [sp, #0x54]
	mov r0, #0x10
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_02084894:
	add r0, r4, #0x0
	mov r1, #0x12
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020848AA
	ldr r1, [sp, #0x54]
	mov r0, #0x20
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_020848AA:
	add r0, r4, #0x0
	mov r1, #0x13
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020848C0
	ldr r1, [sp, #0x54]
	mov r0, #0x40
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_020848C0:
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x54]
	cmp r1, r0
	beq _020848D4
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x54
	bl FUN_02067830
	mov r6, #0x1
_020848D4:
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x54]
	add r0, r4, #0x0
	mov r1, #0x17
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02084904
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084930
_02084904:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084930
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	bne _0208492C
	add r0, r4, #0x0
	mov r1, #0x36
	bl FUN_0206E7DC
	add r3, r0, #0x0
	ldr r1, [sp, #0x50]
	ldr r2, [sp, #0x54]
	add r0, r5, #0x0
	bl FUN_02084F68
	mov r6, #0x1
_0208492C:
	mov r7, #0x1
	b _0208495C
_02084930:
	add r0, r4, #0x0
	mov r1, #0x26
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208495C
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x54]
	cmp r1, r0
	bge _0208495A
	add r0, r4, #0x0
	mov r1, #0x36
	bl FUN_0206E7DC
	add r3, r0, #0x0
	ldr r1, [sp, #0x50]
	ldr r2, [sp, #0x54]
	add r0, r5, #0x0
	bl FUN_02084F68
	mov r6, #0x1
_0208495A:
	mov r7, #0x1
_0208495C:
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x58]
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020849B4
	ldr r0, [sp, #0x58]
	cmp r0, #0x64
	bge _020849B2
	add r0, r5, #0x0
	bl FUN_020686F8
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl FUN_02068018
	add r0, r5, #0x0
	bl FUN_02066ED8
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	bne _020849B0
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	ldr r3, [sp, #0x54]
	ldr r1, [sp, #0x50]
	add r0, r5, #0x0
	sub r3, r2, r3
	str r2, [sp, #0x5c]
	bl FUN_02084F68
_020849B0:
	mov r6, #0x1
_020849B2:
	mov r7, #0x1
_020849B4:
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020849C2
	mov r7, #0x1
_020849C2:
	add r0, r4, #0x0
	mov r1, #0x22
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020849E2
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02084EC0
	cmp r0, #0x1
	bne _020849DE
	mov r6, #0x1
_020849DE:
	mov r7, #0x1
	b _02084A00
_020849E2:
	add r0, r4, #0x0
	mov r1, #0x23
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084A00
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	mov r2, #0x3
	bl FUN_02084EC0
	cmp r0, #0x1
	bne _020849FE
	mov r6, #0x1
_020849FE:
	mov r7, #0x1
_02084A00:
	add r0, r4, #0x0
	mov r1, #0x24
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084A2C
	add r0, r4, #0x0
	mov r1, #0x37
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02084E40
	cmp r0, #0x1
	bne _02084A24
	mov r6, #0x1
_02084A24:
	mov r7, #0x1
	b _02084A66
	.balign 4
_02084A28: .word 0xFFFFF077
_02084A2C:
	add r0, r4, #0x0
	mov r1, #0x25
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084A66
	mov r0, #0x0
	str r0, [sp, #0x50]
	cmp r0, #0x4
	bge _02084A64
	mov r7, #0x37
_02084A42:
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r1, [sp, #0x50]
	add r0, r5, #0x0
	bl FUN_02084E40
	cmp r0, #0x1
	bne _02084A5A
	mov r6, #0x1
_02084A5A:
	ldr r0, [sp, #0x50]
	add r0, r0, #0x1
	str r0, [sp, #0x50]
	cmp r0, #0x4
	blt _02084A42
_02084A64:
	mov r7, #0x1
_02084A66:
	add r0, r5, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x54]
	add r0, r5, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x58]
	add r0, r5, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x5c]
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x60]
	add r0, r5, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x64]
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	mov r1, #0x49
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _02084B20
	add r0, r4, #0x0
	mov r1, #0x27
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084B20
	add r0, r4, #0x0
	mov r1, #0x30
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x54]
	str r1, [sp, #0x10]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0xc]
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x14]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x50]
	add r1, r1, r2
	ldr r2, [sp, #0xc]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084B18
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xd
	add r2, sp, #0x50
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	mov r6, #0x1
_02084B18:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084B20
	mov r7, #0x1
_02084B20:
	add r0, r4, #0x0
	mov r1, #0x28
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084B80
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0x18]
	str r1, [sp, #0x20]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x20]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x54]
	add r1, r1, r2
	ldr r2, [sp, #0x18]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084B78
	str r0, [sp, #0x54]
	add r0, r5, #0x0
	mov r1, #0xe
	add r2, sp, #0x54
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	mov r6, #0x1
_02084B78:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084B80
	mov r7, #0x1
_02084B80:
	add r0, r4, #0x0
	mov r1, #0x29
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084BE0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x28]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0x24]
	str r1, [sp, #0x2c]
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x2c]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x58]
	add r1, r1, r2
	ldr r2, [sp, #0x24]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084BD8
	str r0, [sp, #0x58]
	add r0, r5, #0x0
	mov r1, #0xf
	add r2, sp, #0x58
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	mov r6, #0x1
_02084BD8:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084BE0
	mov r7, #0x1
_02084BE0:
	add r0, r4, #0x0
	mov r1, #0x2a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084C40
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x34]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x30]
	str r1, [sp, #0x38]
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x38]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x34]
	ldr r0, [sp, #0x5c]
	add r1, r1, r2
	ldr r2, [sp, #0x30]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084C38
	str r0, [sp, #0x5c]
	add r0, r5, #0x0
	mov r1, #0x10
	add r2, sp, #0x5c
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	mov r6, #0x1
_02084C38:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084C40
	mov r7, #0x1
_02084C40:
	add r0, r4, #0x0
	mov r1, #0x2b
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084CA0
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_0206E7DC
	ldr r1, [sp, #0x5c]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x40]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x3c]
	str r1, [sp, #0x44]
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x44]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x60]
	add r1, r1, r2
	ldr r2, [sp, #0x3c]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084C98
	str r0, [sp, #0x60]
	add r0, r5, #0x0
	mov r1, #0x11
	add r2, sp, #0x60
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	mov r6, #0x1
_02084C98:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084CA0
	mov r7, #0x1
_02084CA0:
	add r0, r4, #0x0
	mov r1, #0x2c
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084D00
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_0206E7DC
	ldr r1, [sp, #0x5c]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x4c]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x48]
	mov r12, r1
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r1, r2, r1
	mov r2, r12
	add r2, r2, r1
	ldr r1, [sp, #0x4c]
	ldr r3, [sp, #0x60]
	add r1, r1, r2
	ldr r0, [sp, #0x64]
	ldr r2, [sp, #0x48]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084CF8
	str r0, [sp, #0x64]
	add r0, r5, #0x0
	mov r1, #0x12
	add r2, sp, #0x64
	bl FUN_02067830
	add r0, r5, #0x0
	bl FUN_02066ED8
	mov r6, #0x1
_02084CF8:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084D00
	mov r7, #0x1
_02084D00:
	cmp r6, #0x0
	bne _02084D14
	cmp r7, #0x1
	bne _02084D14
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x70
	mov r0, #0x0
	pop {r3-r7, pc}
_02084D14:
	add r0, r5, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x50]
	cmp r0, #0x64
	bge _02084D54
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084DC2
	add r0, r4, #0x0
	mov r1, #0x38
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r0, [sp, #0x88]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x50]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0208508C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x70
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02084D54:
	blt _02084D8A
	cmp r0, #0xc8
	bge _02084D8A
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084DC2
	add r0, r4, #0x0
	mov r1, #0x39
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r0, [sp, #0x88]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x50]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0208508C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x70
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02084D8A:
	cmp r0, #0xc8
	blt _02084DC2
	cmp r0, #0xff
	bgt _02084DC2
	add r0, r4, #0x0
	mov r1, #0x2f
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084DC2
	add r0, r4, #0x0
	mov r1, #0x3a
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r0, [sp, #0x88]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x50]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0208508C
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x70
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02084DC2:
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
	add sp, #0x70
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02084DD0
FUN_02084DD0: ; 0x02084DD0
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r1, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0206B9B0
	ldr r1, [sp, #0x14]
	add r3, sp, #0x0
	str r1, [sp, #0x0]
	ldrh r3, [r3, #0x10]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02084810
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02084DF0
FUN_02084DF0: ; 0x02084DF0
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r1, #0x36
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	bne _02084E08
	mov r0, #0x0
	pop {r3-r7, pc}
_02084E08:
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	add r6, #0x3e
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, r7, #0x0
	bl FUN_0206AB30
	cmp r4, r0
	bhs _02084E36
	mov r0, #0x1
	b _02084E38
_02084E36:
	mov r0, #0x0
_02084E38:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02084E40
FUN_02084E40: ; 0x02084E40
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r1, #0x36
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	bne _02084E5E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_02084E5E:
	add r0, r5, #0x0
	str r0, [sp, #0x0]
	add r0, #0x3a
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	add r1, sp, #0x4
	strb r0, [r1, #0x0]
	add r5, #0x3e
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r7, #0x0
	lsr r1, r1, #0x18
	bl FUN_0206AB30
	add r1, sp, #0x4
	ldrb r2, [r1, #0x0]
	cmp r2, r0
	bhs _02084EB8
	cmp r4, #0x7f
	bne _02084E9C
	strb r0, [r1, #0x0]
	b _02084EA8
_02084E9C:
	add r2, r2, r4
	strb r2, [r1, #0x0]
	ldrb r2, [r1, #0x0]
	cmp r2, r0
	bls _02084EA8
	strb r0, [r1, #0x0]
_02084EA8:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	add r2, sp, #0x4
	bl FUN_02067830
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02084EB8:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02084EC0
FUN_02084EC0: ; 0x02084EC0
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r2, #0x0
	add r4, r1, #0x0
	str r1, [sp, #0x0]
	add r1, #0x3e
	mov r2, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_020671BC
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x3
	bne _02084EE6
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02084EE6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x0
	str r0, [sp, #0x4]
	bl FUN_0206AB30
	cmp r0, #0x5
	bhs _02084F08
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02084F08:
	add r4, #0x3a
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	add r1, sp, #0x8
	strb r0, [r1, #0x1]
	ldrb r1, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_0206AB30
	add r7, r0, #0x0
	add r0, sp, #0x8
	ldrb r0, [r0, #0x0]
	add r0, r0, r6
	cmp r0, #0x3
	bls _02084F30
	mov r0, #0x3
	b _02084F34
_02084F30:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
_02084F34:
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	ldrb r1, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_0206AB30
	add r1, sp, #0x8
	ldrb r2, [r1, #0x1]
	add r0, r2, r0
	sub r0, r0, r7
	strb r0, [r1, #0x1]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	add r2, sp, #0x8
	bl FUN_02067830
	add r2, sp, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, #0x1
	bl FUN_02067830
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02084F68
FUN_02084F68: ; 0x02084F68
	push {r0-r3}
	push {r3, lr}
	cmp r2, #0x1
	bne _02084F74
	mov r3, #0x1
	b _02084F8A
_02084F74:
	cmp r3, #0xff
	bne _02084F7C
	add r3, r2, #0x0
	b _02084F8A
_02084F7C:
	cmp r3, #0xfe
	bne _02084F84
	lsr r3, r2, #0x1
	b _02084F8A
_02084F84:
	cmp r3, #0xfd
	bne _02084F8A
	lsr r3, r2, #0x2
_02084F8A:
	ldr r1, [sp, #0xc]
	add r1, r1, r3
	cmp r1, r2
	bls _02084F96
	str r2, [sp, #0xc]
	b _02084F98
_02084F96:
	str r1, [sp, #0xc]
_02084F98:
	mov r1, #0xa2
	add r2, sp, #0xc
	bl FUN_02067830
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_02084FA8
FUN_02084FA8: ; 0x02084FA8
	push {r3-r4}
	cmp r0, #0x0
	bne _02084FBA
	cmp r2, #0x0
	bge _02084FBA
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
_02084FBA:
	cmp r0, #0x64
	blt _02084FCA
	cmp r2, #0x0
	ble _02084FCA
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
_02084FCA:
	ldr r3, _02084FFC ; =0x000001FE
	add r4, r0, r1
	cmp r4, r3
	blt _02084FDE
	cmp r2, #0x0
	ble _02084FDE
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
_02084FDE:
	add r0, r0, r2
	cmp r0, #0x64
	ble _02084FE8
	mov r0, #0x64
	b _02084FEE
_02084FE8:
	cmp r0, #0x0
	bge _02084FEE
	mov r0, #0x0
_02084FEE:
	ldr r2, _02084FFC ; =0x000001FE
	add r3, r0, r1
	cmp r3, r2
	ble _02084FF8
	sub r0, r2, r1
_02084FF8:
	pop {r3-r4}
	bx lr
	.balign 4
_02084FFC: .word 0x000001FE

	thumb_func_start FUN_02085000
FUN_02085000: ; 0x02085000
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0xff
	blt _02085014
	mov r0, #0x0
	pop {r4, pc}
_02085014:
	cmp r0, #0x64
	bge _02085038
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02085034
	add r0, r4, #0x0
	mov r1, #0x38
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02085034
	mov r0, #0x1
	pop {r4, pc}
_02085034:
	mov r0, #0x0
	pop {r4, pc}
_02085038:
	blt _0208505E
	cmp r0, #0xc8
	bge _0208505E
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208505A
	add r0, r4, #0x0
	mov r1, #0x39
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _0208505A
	mov r0, #0x1
	pop {r4, pc}
_0208505A:
	mov r0, #0x0
	pop {r4, pc}
_0208505E:
	cmp r0, #0xc8
	blt _02085086
	cmp r0, #0xff
	bge _02085086
	add r0, r4, #0x0
	mov r1, #0x2f
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02085082
	add r0, r4, #0x0
	mov r1, #0x3a
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02085082
	mov r0, #0x1
	pop {r4, pc}
_02085082:
	mov r0, #0x0
	pop {r4, pc}
_02085086:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0208508C
FUN_0208508C: ; 0x0208508C
	push {r0-r3}
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r3, #0x0
	cmp r4, #0xff
	bne _020850AA
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	ble _020850AA
	mov r0, #0x0
	pop {r4-r6}
	pop {r3}
	add sp, #0x10
	bx r3
_020850AA:
	cmp r4, #0x0
	bne _020850BE
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bge _020850BE
	mov r0, #0x0
	pop {r4-r6}
	pop {r3}
	add sp, #0x10
	bx r3
_020850BE:
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	ble _02085114
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	ldr r2, [sp, #0x20]
	lsr r0, r0, #0x10
	mov r1, #0x1
	bl FUN_0206E7B8
	cmp r0, #0x34
	bne _020850EC
	ldr r1, [sp, #0x18]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #0x18]
_020850EC:
	add r0, r5, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0xb
	bne _02085100
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
_02085100:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl FUN_020671BC
	cmp r6, r0
	bne _02085114
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
_02085114:
	ldr r0, [sp, #0x18]
	add r0, r0, r4
	str r0, [sp, #0x18]
	cmp r0, #0xff
	ble _02085122
	mov r0, #0xff
	str r0, [sp, #0x18]
_02085122:
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bge _0208512C
	mov r0, #0x0
	str r0, [sp, #0x18]
_0208512C:
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x18
	bl FUN_02067830
	mov r0, #0x1
	pop {r4-r6}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_02085140
FUN_02085140: ; 0x02085140
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	bl FUN_0206B9AC
	mov r7, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	ble _020851B4
	mov r6, #0x7f
_02085154:
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_0206B9B0
	mov r1, #0xab
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _020851AC
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0xa2
	add r2, sp, #0x8
	bl FUN_02067830
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x8
	bl FUN_02067830
	mov r4, #0x0
_02085190:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02084DF0
	cmp r0, #0x1
	bne _020851A6
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02084E40
_020851A6:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02085190
_020851AC:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	cmp r7, r0
	blt _02085154
_020851B4:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_020851B8
FUN_020851B8: ; 0x020851B8
	push {r3, lr}
	mov r1, #0xc
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	pop {r3, pc}

	thumb_func_start FUN_020851DC
FUN_020851DC: ; 0x020851DC
	push {r4-r6, lr}
	sub r1, #0x95
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	add r1, r6, #0x0
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02085200
	cmp r4, #0x1
	bne _020851F4
	strb r6, [r5, #0x8]
_020851F4:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020851F8
FUN_020851F8: ; 0x020851F8
	strb r1, [r0, #0x9]
	strb r2, [r0, #0xa]
	strb r3, [r0, #0xb]
	bx lr

	thumb_func_start FUN_02085200
FUN_02085200: ; 0x02085200
	push {r3-r6}
	lsr r6, r1, #0x1f
	lsl r5, r1, #0x1b
	lsr r2, r1, #0x5
	lsl r4, r2, #0x2
	sub r5, r5, r6
	mov r1, #0x1b
	ror r5, r1
	ldr r3, [r0, r4]
	mov r2, #0x1
	add r1, r6, r5
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r0, r4]
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02085224
FUN_02085224: ; 0x02085224
	push {r4-r5}
	lsr r5, r1, #0x1f
	lsl r4, r1, #0x1b
	lsr r1, r1, #0x5
	lsl r1, r1, #0x2
	sub r4, r4, r5
	mov r3, #0x1b
	ror r4, r3
	mov r2, #0x1
	add r3, r5, r4
	add r4, r2, #0x0
	lsl r4, r3
	ldr r0, [r0, r1]
	tst r0, r4
	bne _02085244
	mov r2, #0x0
_02085244:
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_0208524C
FUN_0208524C: ; 0x0208524C
	ldrb r3, [r0, #0x9]
	strb r3, [r1, #0x0]
	ldrb r0, [r0, #0xa]
	strb r0, [r2, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02085258
FUN_02085258: ; 0x02085258
	ldr r3, _02085260 ; =FUN_02006670
	add r1, r0, #0x0
	mov r0, #0x44
	bx r3
	.balign 4
_02085260: .word FUN_02006670

	thumb_func_start FUN_02085264
FUN_02085264: ; 0x02085264
	ldr r3, _02085268 ; =FUN_02006704
	bx r3
	.balign 4
_02085268: .word FUN_02006704

	thumb_func_start FUN_0208526C
FUN_0208526C: ; 0x0208526C
	ldr r3, _02085270 ; =FUN_020066F4
	bx r3
	.balign 4
_02085270: .word FUN_020066F4

	thumb_func_start FUN_02085274
FUN_02085274: ; 0x02085274
	add r3, r0, #0x0
	add r2, r1, #0x0
	add r1, r3, #0x0
	ldr r3, _02085280 ; =LoadFromNarc_2
	mov r0, #0x44
	bx r3
	.balign 4
_02085280: .word LoadFromNarc_2

	thumb_func_start FUN_02085284
FUN_02085284: ; 0x02085284
	ldr r3, _0208528C ; =FUN_02085274
	sub r0, #0x95
	bx r3
	nop
_0208528C: .word FUN_02085274

	thumb_func_start FUN_02085290
FUN_02085290: ; 0x02085290
	cmp r1, #0xa
	bhi _020852E2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020852A0: ; jump table (using 16-bit offset)
	.short _020852B6 - _020852A0 - 2; case 0
	.short _020852BA - _020852A0 - 2; case 1
	.short _020852BE - _020852A0 - 2; case 2
	.short _020852C2 - _020852A0 - 2; case 3
	.short _020852C6 - _020852A0 - 2; case 4
	.short _020852CA - _020852A0 - 2; case 5
	.short _020852CE - _020852A0 - 2; case 6
	.short _020852D2 - _020852A0 - 2; case 7
	.short _020852D6 - _020852A0 - 2; case 8
	.short _020852DA - _020852A0 - 2; case 9
	.short _020852DE - _020852A0 - 2; case 10
_020852B6:
	ldrh r0, [r0, #0x0]
	bx lr
_020852BA:
	ldrb r0, [r0, #0x2]
	bx lr
_020852BE:
	ldrb r0, [r0, #0x3]
	bx lr
_020852C2:
	ldrb r0, [r0, #0x4]
	bx lr
_020852C6:
	ldrb r0, [r0, #0x5]
	bx lr
_020852CA:
	ldrb r0, [r0, #0x6]
	bx lr
_020852CE:
	ldrb r0, [r0, #0x7]
	bx lr
_020852D2:
	ldrb r0, [r0, #0x8]
	bx lr
_020852D6:
	ldrb r0, [r0, #0x9]
	bx lr
_020852DA:
	ldrb r0, [r0, #0xa]
	bx lr
_020852DE:
	ldrb r0, [r0, #0xb]
	bx lr
_020852E2:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020852E8
FUN_020852E8: ; 0x020852E8
	push {r3-r5, lr}
	ldr r2, _0208530C ; =0x00000175
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_0208530C: .word 0x00000175

	thumb_func_start FUN_02085310
FUN_02085310: ; 0x02085310
	push {r3-r5, lr}
	mov r2, #0x5d
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl FUN_0200A86C
	add r5, r0, #0x0
	add r1, r4, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02085338
FUN_02085338: ; 0x02085338
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0x24
	add r6, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	strb r5, [r4, #0x0]
	strb r7, [r4, #0x1]
	add r0, r6, #0x0
	bl FUN_02024DA0
	str r0, [r4, #0xc]
	add r0, r6, #0x0
	bl FUN_02013B5C
	str r0, [r4, #0x10]
	add r0, r6, #0x0
	bl FUN_020462AC
	bl FUN_0205ED0C
	strb r0, [r4, #0x4]
	mov r1, #0x0
	strb r1, [r4, #0x5]
	mov r0, #0x1
	strb r0, [r4, #0x2]
	add r0, r6, #0x0
	strb r1, [r4, #0x3]
	bl LoadPlayerDataAddress
	bl FUN_02025084
	str r0, [r4, #0x8]
	cmp r5, #0x2
	bne _02085390
	add r0, r4, #0x0
	add r0, #0x14
	mov r1, #0x3
	bl FUN_0201373C
	b _020853A0
_02085390:
	ldr r0, _020853A4 ; =0x0000FFFF
	mov r1, #0x0
	add r2, r4, #0x0
_02085396:
	add r1, r1, #0x1
	strh r0, [r2, #0x1c]
	add r2, r2, #0x2
	cmp r1, #0x2
	blt _02085396
_020853A0:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_020853A4: .word 0x0000FFFF

	thumb_func_start FUN_020853A8
FUN_020853A8: ; 0x020853A8
	ldr r3, _020853AC ; =FUN_02016A18
	bx r3
	.balign 4
_020853AC: .word FUN_02016A18

	thumb_func_start FUN_020853B0
FUN_020853B0: ; 0x020853B0
	strh r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_020853B4
FUN_020853B4: ; 0x020853B4
	strh r1, [r0, #0x1c]
	strh r2, [r0, #0x1e]
	bx lr
	.balign 4

	thumb_func_start FUN_020853BC
FUN_020853BC: ; 0x020853BC
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x14]
	ldrh r2, [r1, #0x2]
	strh r2, [r0, #0x16]
	ldrh r2, [r1, #0x4]
	strh r2, [r0, #0x18]
	ldrh r1, [r1, #0x6]
	strh r1, [r0, #0x1a]
	bx lr
	.balign 4

	thumb_func_start FUN_020853D0
FUN_020853D0: ; 0x020853D0
	mov r1, #0x1
	strb r1, [r0, #0x2]
	mov r1, #0x0
	strb r1, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_020853DC
FUN_020853DC: ; 0x020853DC
	mov r1, #0x1
	strb r1, [r0, #0x5]
	bx lr
	.balign 4

	thumb_func_start FUN_020853E4
FUN_020853E4: ; 0x020853E4
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_020853E8
FUN_020853E8: ; 0x020853E8
	ldrb r0, [r0, #0x3]
	bx lr

	thumb_func_start FUN_020853EC
FUN_020853EC: ; 0x020853EC
	ldrh r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_020853F0
FUN_020853F0: ; 0x020853F0
	ldrh r2, [r0, #0x1c]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x1e]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_020853FC
FUN_020853FC: ; 0x020853FC
	add r2, r0, #0x0
	ldr r3, _02085408 ; =FUN_02013960
	add r2, #0x14
	add r0, r1, #0x0
	add r1, r2, #0x0
	bx r3
	.balign 4
_02085408: .word FUN_02013960

	thumb_func_start FUN_0208540C
FUN_0208540C: ; 0x0208540C
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02085410
FUN_02085410: ; 0x02085410
	ldrb r0, [r0, #0x1]
	bx lr

	thumb_func_start FUN_02085414
FUN_02085414: ; 0x02085414
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02085418
FUN_02085418: ; 0x02085418
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_0208541C
FUN_0208541C: ; 0x0208541C
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02085420
FUN_02085420: ; 0x02085420
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02085424
FUN_02085424: ; 0x02085424
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_02085428
FUN_02085428: ; 0x02085428
	ldrb r3, [r0, #0x0]
	cmp r3, #0x0
	beq _02085438
	cmp r3, #0x1
	beq _0208543E
	cmp r3, #0x2
	beq _02085448
	bx lr
_02085438:
	ldrh r0, [r0, #0x1c]
	strh r0, [r1, #0x0]
	bx lr
_0208543E:
	ldrh r2, [r0, #0x1c]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x1e]
	strh r0, [r1, #0x2]
	bx lr
_02085448:
	ldrh r1, [r0, #0x14]
	strh r1, [r2, #0x0]
	ldrh r1, [r0, #0x16]
	strh r1, [r2, #0x2]
	ldrh r1, [r0, #0x18]
	strh r1, [r2, #0x4]
	ldrh r0, [r0, #0x1a]
	strh r0, [r2, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_0208545C
FUN_0208545C: ; 0x0208545C
	push {r3, lr}
	ldrb r3, [r0, #0x0]
	cmp r3, #0x0
	beq _0208546C
	cmp r3, #0x1
	beq _0208547C
	cmp r3, #0x2
	b _02085494
_0208546C:
	ldrh r1, [r1, #0x0]
	ldrh r0, [r0, #0x1c]
	cmp r1, r0
	bne _02085478
	mov r0, #0x1
	pop {r3, pc}
_02085478:
	mov r0, #0x0
	pop {r3, pc}
_0208547C:
	ldrh r3, [r1, #0x0]
	ldrh r2, [r0, #0x1c]
	cmp r3, r2
	bne _02085490
	ldrh r1, [r1, #0x2]
	ldrh r0, [r0, #0x1e]
	cmp r1, r0
	bne _02085490
	mov r0, #0x1
	pop {r3, pc}
_02085490:
	mov r0, #0x0
	pop {r3, pc}
_02085494:
	add r0, #0x14
	add r1, r2, #0x0
	bl FUN_02013928
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020854A0
FUN_020854A0: ; 0x020854A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0208545C
	cmp r0, #0x0
	bne _020854B4
	mov r0, #0x1
	b _020854B6
_020854B4:
	mov r0, #0x0
_020854B6:
	strb r0, [r5, #0x3]
	mov r1, #0x0
	strb r1, [r5, #0x2]
	add r2, r5, #0x0
_020854BE:
	ldrh r0, [r4, #0x0]
	add r1, r1, #0x1
	add r4, r4, #0x2
	strh r0, [r2, #0x1c]
	add r2, r2, #0x2
	cmp r1, #0x2
	blt _020854BE
	ldrh r0, [r6, #0x0]
	strh r0, [r5, #0x14]
	ldrh r0, [r6, #0x2]
	strh r0, [r5, #0x16]
	ldrh r0, [r6, #0x4]
	strh r0, [r5, #0x18]
	ldrh r0, [r6, #0x6]
	strh r0, [r5, #0x1a]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020854E0
FUN_020854E0: ; 0x020854E0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_02025838
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	mov r1, #0x1c
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	strb r0, [r4, #0xf]
	ldr r0, [sp, #0x4]
	strb r6, [r4, #0xe]
	str r0, [r4, #0x18]
	mov r0, #0x1
	strh r0, [r4, #0x0]
	str r7, [r4, #0x8]
	mov r0, #0x0
	strh r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	str r5, [r4, #0x10]
	bl FUN_020256BC
	str r0, [r4, #0x14]
	bl FUN_02025658
	ldr r0, [r4, #0x14]
	mov r1, #0xff
	add r2, r6, #0x0
	add r3, r5, #0x0
	bl FUN_020256DC
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02085538
FUN_02085538: ; 0x02085538
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0x1c
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	str r5, [r4, #0x8]
	strh r6, [r4, #0xc]
	add r0, r7, #0x0
	str r7, [r4, #0x10]
	bl FUN_02025838
	ldr r3, [sp, #0x0]
	add r1, r5, #0x0
	add r2, r6, #0x0
	str r0, [r4, #0x18]
	bl FUN_020258B0
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02085578
FUN_02085578: ; 0x02085578
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x1c
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	str r5, [r4, #0x10]
	add r0, r7, #0x0
	bl FUN_020256BC
	str r0, [r4, #0x14]
	ldr r2, [r4, #0x14]
	add r0, r6, #0x0
	mov r1, #0xa9
	bl FUN_020671BC
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020855B0
FUN_020855B0: ; 0x020855B0
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x1c
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r7, #0x0
	str r5, [r4, #0x10]
	bl FUN_020256BC
	add r1, r6, #0x0
	str r0, [r4, #0x14]
	bl FUN_020257D0
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020855E4
FUN_020855E4: ; 0x020855E4
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020855E8
FUN_020855E8: ; 0x020855E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020855E4
	cmp r0, #0x0
	bne _020855FC
	mov r0, #0x0
	pop {r4-r6, pc}
_020855FC:
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0x14]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02025888
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0208560C
FUN_0208560C: ; 0x0208560C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020855E4
	cmp r0, #0x0
	bne _0208561E
	mov r0, #0x0
	pop {r3-r5, pc}
_0208561E:
	ldr r2, [r5, #0x14]
	add r0, r4, #0x0
	mov r1, #0xa9
	bl FUN_02067830
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0208562C
FUN_0208562C: ; 0x0208562C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	beq _0208563A
	bl FUN_02016A18
_0208563A:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02085644
FUN_02085644: ; 0x02085644
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x0
	add r7, r0, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0x0]
	bl FUN_02025864
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _0208569E
	add r0, r4, #0x0
	bl FUN_020256BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa9
	add r2, r4, #0x0
	bl FUN_020671BC
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_02025888
	add r0, r4, #0x0
	bl FUN_02025658
	add r0, r5, #0x0
	mov r1, #0xa9
	add r2, r4, #0x0
	bl FUN_02067830
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
_0208569E:
	pop {r3-r7, pc}

	thumb_func_start FUN_020856A0
FUN_020856A0: ; 0x020856A0
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_020258B0
	add r6, r0, #0x0
	bne _020856BC
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_020856BC:
	bl FUN_020257CC
	bl FUN_0206EAD8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0xa9
	add r2, r6, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	bl FUN_02025878
	add r0, r6, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020856F0
FUN_020856F0: ; 0x020856F0
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x34
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x34
	add r6, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r4, #0x0
	bl FUN_020257C0
	str r0, [r6, #0x8]
	mov r0, #0x8
	add r1, r5, #0x0
	bl FUN_020219F4
	str r0, [r6, #0x10]
	add r0, r4, #0x0
	bl FUN_020257C4
	add r1, r0, #0x0
	ldr r0, [r6, #0x10]
	bl FUN_02021E28
	add r0, r4, #0x0
	bl FUN_020257CC
	strb r0, [r6, #0xf]
	add r0, r4, #0x0
	bl FUN_020257D8
	strb r0, [r6, #0xd]
	add r0, r4, #0x0
	bl FUN_020257DC
	strb r0, [r6, #0xe]
	mov r5, #0x0
	mov r7, #0x2
_02085748:
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	add r2, r7, #0x0
	bl FUN_020257E0
	lsl r1, r5, #0x1
	add r1, r6, r1
	strh r0, [r1, #0x14]
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3
	blo _02085748
	add r7, r6, #0x0
	mov r5, #0x0
	add r7, #0x1a
_0208576A:
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02025814
	add r1, r0, #0x0
	lsl r0, r5, #0x3
	add r0, r7, r0
	bl FUN_02013960
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3
	blo _0208576A
	add r0, r6, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0208578C
FUN_0208578C: ; 0x0208578C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0208579A
	bl FUN_02021A20
_0208579A:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020857A4
FUN_020857A4: ; 0x020857A4
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r4, r7, #0x0
	add r6, r0, #0x0
	mov r5, #0x0
	add r4, #0x1a
_020857B0:
	lsl r1, r5, #0x3
	lsl r2, r5, #0x18
	add r0, r6, #0x0
	add r1, r4, r1
	lsr r2, r2, #0x18
	bl FUN_02025824
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3
	blo _020857B0
	ldrb r1, [r7, #0xf]
	add r0, r6, #0x0
	bl FUN_020257D0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020857D4
FUN_020857D4: ; 0x020857D4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020857F4
	bl FUN_02006290
	cmp r0, #0x0
	beq _020857F4
	ldr r0, [r4, #0x0]
	bl FUN_02006260
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_020857F4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020857F8
FUN_020857F8: ; 0x020857F8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_0200628C
	mov r2, #0x1
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x28
	lsl r2, r2, #0xc
	bl FUN_0201681C
	add r0, r4, #0x0
	mov r1, #0x1c
	mov r2, #0x28
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r1, #0x28
	str r1, [r4, #0x0]
	ldr r0, [r5, #0x14]
	bl FUN_020856F0
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x10]
	bl LoadPlayerDataAddress
	ldr r1, [r4, #0x10]
	str r0, [r1, #0x4]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02085844
	ldrb r1, [r5, #0xf]
	ldr r0, [r4, #0x10]
	strb r1, [r0, #0xf]
_02085844:
	ldr r1, [r4, #0x10]
	ldrb r0, [r1, #0xf]
	cmp r0, #0xc
	blo _02085850
	mov r0, #0x0
	strb r0, [r1, #0xf]
_02085850:
	ldrh r1, [r5, #0x0]
	ldr r0, [r4, #0x10]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0208585C
FUN_0208585C: ; 0x0208585C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0200628C
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x4
	bls _02085878
	b _02085990
_02085878:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02085884: ; jump table (using 16-bit offset)
	.short _0208588E - _02085884 - 2; case 0
	.short _020858A6 - _02085884 - 2; case 1
	.short _020858D2 - _02085884 - 2; case 2
	.short _02085900 - _02085884 - 2; case 3
	.short _0208595E - _02085884 - 2; case 4
_0208588E:
	ldrh r1, [r6, #0x0]
	ldr r0, [r4, #0x10]
	strh r1, [r0, #0x0]
	ldr r0, _02085994 ; =0x020FCAA8
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x0]
	bl FUN_02006234
	str r0, [r4, #0xc]
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02085990
_020858A6:
	add r0, r4, #0x0
	add r0, #0xc
	bl FUN_020857D4
	cmp r0, #0x0
	beq _02085990
	ldr r0, [r4, #0x10]
	ldrh r1, [r0, #0x0]
	cmp r1, #0x3
	beq _020858C6
	ldr r0, _02085998 ; =0x0000FFFF
	cmp r1, r0
	bne _020858CC
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02085990
_020858C6:
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02085990
_020858CC:
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _02085990
_020858D2:
	ldrh r0, [r6, #0x0]
	cmp r0, #0x1
	bne _020858FC
	ldr r1, [r4, #0x10]
	ldrh r0, [r1, #0x0]
	cmp r0, #0x3
	bne _020858F8
	ldr r0, [r6, #0x14]
	bl FUN_020857A4
	ldr r0, [r6, #0x10]
	bl FUN_02029FC8
	mov r1, #0x2
	bl FUN_0202A170
	mov r0, #0x1
	str r0, [r6, #0x4]
	b _020858FC
_020858F8:
	mov r0, #0x0
	str r0, [r6, #0x4]
_020858FC:
	mov r0, #0x1
	pop {r4-r6, pc}
_02085900:
	ldr r2, [r6, #0x10]
	ldr r3, [r4, #0x0]
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_02085338
	str r0, [r4, #0x8]
	ldr r0, [r4, #0x10]
	add r1, r0, #0x0
	ldrb r0, [r0, #0x2]
	add r1, #0x1a
	lsl r0, r0, #0x3
	add r0, r1, r0
	bl FUN_0201385C
	cmp r0, #0x0
	beq _02085938
	ldr r1, [r4, #0x10]
	add r0, r4, #0x0
	add r2, r1, #0x0
	ldrb r1, [r1, #0x2]
	add r2, #0x1a
	add r0, #0x14
	lsl r1, r1, #0x3
	add r1, r2, r1
	bl FUN_02013960
	b _02085942
_02085938:
	add r0, r4, #0x0
	add r0, #0x14
	mov r1, #0x3
	bl FUN_0201373C
_02085942:
	add r1, r4, #0x0
	ldr r0, [r4, #0x8]
	add r1, #0x14
	bl FUN_020853BC
	ldr r0, _0208599C ; =0x020FCAB8
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x0]
	bl FUN_02006234
	str r0, [r4, #0xc]
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02085990
_0208595E:
	add r0, r4, #0x0
	add r0, #0xc
	bl FUN_020857D4
	cmp r0, #0x0
	beq _02085990
	ldr r0, [r4, #0x8]
	bl FUN_020853E4
	cmp r0, #0x0
	bne _02085986
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x8]
	add r2, r1, #0x0
	ldrb r1, [r1, #0x2]
	add r2, #0x1a
	lsl r1, r1, #0x3
	add r1, r2, r1
	bl FUN_020853FC
_02085986:
	ldr r0, [r4, #0x8]
	bl FUN_020853A8
	mov r0, #0x0
	str r0, [r5, #0x0]
_02085990:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_02085994: .word 0x020FCAA8
_02085998: .word 0x0000FFFF
_0208599C: .word 0x020FCAB8

	thumb_func_start FUN_020859A0
FUN_020859A0: ; 0x020859A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	bl FUN_0208578C
	add r0, r5, #0x0
	bl FUN_0200627C
	ldr r0, [r4, #0x0]
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}

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
	ldr r1, _02085F40 ; =0x020FCAD8
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
	ldr r1, _02085F44 ; =0x020F96DC
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
_02085F40: .word 0x020FCAD8
_02085F44: .word 0x020F96DC

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
	ldr r0, _02085FCC ; =0x020FCAE8
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02085FC8: .word 0x0000032A
_02085FCC: .word 0x020FCAE8

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
	ldr r0, _02085FF0 ; =0x020FCAEA
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_02085FEC: .word 0x0000032A
_02085FF0: .word 0x020FCAEA

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
	ldr r0, _02086014 ; =0x020FCAEC
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_02086010: .word 0x0000032A
_02086014: .word 0x020FCAEC

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
	ldr r0, _02086038 ; =0x020FCAED
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_02086034: .word 0x0000032A
_02086038: .word 0x020FCAED

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
	ldr r0, _0208605C ; =0x020FCAEE
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02086058: .word 0x0000032A
_0208605C: .word 0x020FCAEE

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
	ldr r0, _02086080 ; =0x020FCAF0
	ldrb r0, [r0, r1]
	pop {r4, pc}
	nop
_0208607C: .word 0x0000032A
_02086080: .word 0x020FCAF0

	thumb_func_start FUN_02086084
FUN_02086084: ; 0x02086084
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	bl FUN_02015F1C
	mov r2, #0x1
	mov r0, #0x3
	mov r1, #0x47
	lsl r2, r2, #0x12
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0x80
	mov r2, #0x47
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x80
	add r4, r0, #0x0
	bl memset
	add r0, r5, #0x0
	bl FUN_0200628C
	str r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02024FF4
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02025084
	str r0, [r4, #0x14]
	bl FUN_02086468
	str r0, [r4, #0x38]
	mov r0, #0x47
	bl FUN_02006D98
	str r0, [r4, #0x3c]
	mov r0, #0x47
	bl FUN_02016B94
	str r0, [r4, #0x4]
	mov r0, #0x40
	mov r1, #0x47
	bl FUN_0201C24C
	mov r0, #0x47
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02014BF4
	str r0, [r4, #0x54]
	mov r0, #0x47
	bl FUN_02002FD0
	str r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_020038F0
	mov r2, #0x2
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	lsl r2, r2, #0x8
	mov r3, #0x47
	bl FUN_02003008
	mov r1, #0x2
	ldr r0, [r4, #0x8]
	lsl r2, r1, #0x8
	mov r3, #0x47
	bl FUN_02003008
	mov r1, #0x1
	ldr r0, [r4, #0x8]
	lsl r2, r1, #0x9
	mov r3, #0x47
	bl FUN_02003008
	mov r2, #0x2
	ldr r0, [r4, #0x8]
	mov r1, #0x3
	lsl r2, r2, #0x8
	mov r3, #0x47
	bl FUN_02003008
	bl FUN_02086414
	bl FUN_0208643C
	bl FUN_0208650C
	ldr r0, [r4, #0x4]
	bl FUN_0208654C
	add r0, r4, #0x4
	bl FUN_02086E48
	bl FUN_0200541C
	ldr r0, _02086164 ; =FUN_02086664
	add r1, r4, #0x0
	bl FUN_02015F10
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02086164: .word FUN_02086664

	thumb_func_start FUN_02086168
FUN_02086168: ; 0x02086168
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	beq _0208617E
	cmp r1, #0x1
	beq _020861AA
	b _020861C6
_0208617E:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0208618C
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
_0208618C:
	ldr r0, [r4, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, _020861D8 ; =0x000001EA
	cmp r0, r1
	bne _020861A4
	mov r0, #0x1
	str r0, [r4, #0x58]
	b _020861D2
_020861A4:
	mov r0, #0x0
	str r0, [r4, #0x58]
	b _020861D2
_020861AA:
	bl FUN_02086FA8
	cmp r0, #0x0
	bne _020861BA
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _020861D2
_020861BA:
	ldr r0, [r4, #0x3c]
	bl FUN_02006ED4
	bl FUN_02086698
	b _020861D2
_020861C6:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _020861D2
	mov r0, #0x1
	pop {r3-r5, pc}
_020861D2:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_020861D8: .word 0x000001EA

	thumb_func_start FUN_020861DC
FUN_020861DC: ; 0x020861DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020223BC
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201E74C
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	mov r1, #0x2
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	mov r1, #0x3
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	bl FUN_02002FEC
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	mov r1, #0x2
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	mov r1, #0x3
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	bl FUN_0201C29C
	ldr r0, [r4, #0x3c]
	bl FUN_020072E8
	ldr r0, [r4, #0x54]
	bl FUN_02014C28
	add r0, r4, #0x4
	bl FUN_02086ED4
	add r0, r5, #0x0
	bl FUN_0200627C
	mov r0, #0x47
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02086280
FUN_02086280: ; 0x02086280
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x6
	bls _02086294
	b _020863CE
_02086294:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020862A0: ; jump table (using 16-bit offset)
	.short _020862AE - _020862A0 - 2; case 0
	.short _020862C4 - _020862A0 - 2; case 1
	.short _020862D6 - _020862A0 - 2; case 2
	.short _0208633A - _020862A0 - 2; case 3
	.short _02086396 - _020862A0 - 2; case 4
	.short _020863B6 - _020862A0 - 2; case 5
	.short _020863C4 - _020862A0 - 2; case 6
_020862AE:
	ldr r0, [r4, #0xc]
	mov r1, #0xb
	bl MOD05_021ED940
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020862C4:
	ldr r1, _020863D4 ; =0x020FCE14
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020862D6:
	add r0, r5, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	ldr r5, [r4, #0xc]
	bl FUN_020377AC
	bl FUN_020238F4
	add r7, r0, #0x0
	ldr r0, [r6, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x4c
	add r2, sp, #0x8
	bl FUN_02067830
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x6
	bl FUN_0208089C
	add r0, r5, #0x0
	mov r1, #0xb2
	mov r2, #0x0
	bl FUN_02067830
	add r0, r6, #0x0
	bl FUN_020377AC
	ldr r1, [r4, #0xc]
	bl FUN_0202C144
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _02086334
	mov r0, #0x3
	str r0, [r4, #0x0]
	b _020863CE
_02086334:
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _020863CE
_0208633A:
	add r0, r5, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020377AC
	bl LoadPlayerDataAddress
	str r0, [sp, #0x0]
	mov r0, #0xb
	mov r1, #0x1
	add r2, r7, #0x0
	mov r3, #0xa
	bl FUN_02077A84
	str r0, [r4, #0x8]
	ldr r0, [r4, #0xc]
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [r4, #0x8]
	mov r2, #0x0
	str r0, [r1, #0x10]
	ldr r0, [r4, #0xc]
	mov r1, #0x70
	bl FUN_020671BC
	ldr r1, [r4, #0x8]
	str r0, [r1, #0x8]
	ldr r1, _020863D8 ; =0x020FA5FC
	ldr r2, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_02086396:
	ldr r2, [r4, #0x8]
	ldr r0, [r2, #0x14]
	cmp r0, #0x0
	bne _020863A8
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #0x18]
	mov r1, #0x77
	bl FUN_02067830
_020863A8:
	ldr r0, [r4, #0x8]
	bl FUN_02077AC4
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020863B6:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020863C4:
	bl FUN_02016A18
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_020863CE:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_020863D4: .word 0x020FCE14
_020863D8: .word 0x020FA5FC

	thumb_func_start FUN_020863DC
FUN_020863DC: ; 0x020863DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xb
	mov r1, #0x1c
	bl FUN_020169D8
	add r2, r0, #0x0
	add r3, r2, #0x0
	mov r1, #0x1c
	mov r0, #0x0
_020863F2:
	strb r0, [r3, #0x0]
	add r3, r3, #0x1
	sub r1, r1, #0x1
	bne _020863F2
	add r3, r2, #0x0
	add r3, #0xc
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r1, _02086410 ; =FUN_02086280
	add r0, r5, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	.balign 4
_02086410: .word FUN_02086280

	thumb_func_start FUN_02086414
FUN_02086414: ; 0x02086414
	push {r3, lr}
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02086434 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _02086438 ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	pop {r3, pc}
	.balign 4
_02086434: .word 0xFFFFE0FF
_02086438: .word 0x04001000

	thumb_func_start FUN_0208643C
FUN_0208643C: ; 0x0208643C
	push {r3, lr}
	mov r0, #0x7
	str r0, [sp, #0x0]
	ldr r0, _02086460 ; =0x04000050
	mov r1, #0x0
	mov r2, #0xe
	mov r3, #0xb
	bl G2x_SetBlendAlpha_
	mov r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, _02086464 ; =0x04001050
	mov r1, #0x0
	mov r2, #0xe
	mov r3, #0x7
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.balign 4
_02086460: .word 0x04000050
_02086464: .word 0x04001050

	thumb_func_start FUN_02086468
FUN_02086468: ; 0x02086468
	push {r3, lr}
	sub sp, #0x8
	mov r2, #0x2
	mov r1, #0x0
	ldr r0, _02086484 ; =FUN_02086488
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x47
	add r3, r1, #0x0
	bl FUN_02022318
	add sp, #0x8
	pop {r3, pc}
	nop
_02086484: .word FUN_02086488

	thumb_func_start FUN_02086488
FUN_02086488: ; 0x02086488
	push {r3, lr}
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0201E6E4
	ldr r0, _020864F4 ; =0x04000008
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r0, #0x0]
	add r0, #0x58
	ldrh r2, [r0, #0x0]
	ldr r1, _020864F8 ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0, #0x0]
	add r2, r1, #0x2
	ldrh r3, [r0, #0x0]
	add r1, r1, #0x2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r2, _020864FC ; =0x0000CFFB
	and r3, r2
	strh r3, [r0, #0x0]
	ldrh r3, [r0, #0x0]
	sub r2, #0x1c
	and r3, r1
	mov r1, #0x8
	orr r1, r3
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	and r1, r2
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl G3X_SetFog
	mov r0, #0x0
	ldr r2, _02086500 ; =0x00007FFF
	add r1, r0, #0x0
	mov r3, #0x3f
	str r0, [sp, #0x0]
	bl G3X_SetClearColor
	ldr r1, _02086504 ; =0xBFFF0000
	ldr r0, _02086508 ; =0x04000580
	str r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_020864F4: .word 0x04000008
_020864F8: .word 0xFFFFCFFD
_020864FC: .word 0x0000CFFB
_02086500: .word 0x00007FFF
_02086504: .word 0xBFFF0000
_02086508: .word 0x04000580

	thumb_func_start FUN_0208650C
FUN_0208650C: ; 0x0208650C
	push {r3-r5, lr}
	ldr r3, _02086544 ; =0x021064B8
	mov r0, #0x2
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	lsl r0, r0, #0xe
	add r2, r1, #0x0
	blx r3
	ldr r3, _02086548 ; =0x021064C0
	mov r1, #0x0
	add r4, r0, #0x0
	ldr r3, [r3, #0x0]
	mov r0, #0x80
	add r2, r1, #0x0
	blx r3
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _02086534
	bl ErrorHandling
_02086534:
	cmp r5, #0x0
	bne _0208653C
	bl ErrorHandling
_0208653C:
	bl FUN_02012CC8
	pop {r3-r5, pc}
	nop
_02086544: .word 0x021064B8
_02086548: .word 0x021064C0

	thumb_func_start FUN_0208654C
FUN_0208654C: ; 0x0208654C
	push {r3-r5, lr}
	sub sp, #0xa8
	add r4, r0, #0x0
	bl FUN_0201E6D8
	ldr r5, _02086650 ; =0x020FCEBC
	add r3, sp, #0x2c
	mov r2, #0x5
_0208655C:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0208655C
	add r0, sp, #0x2c
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
	ldr r5, _02086654 ; =0x020FCE24
	add r3, sp, #0x1c
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _02086658 ; =0x020FCF84
	add r3, sp, #0x54
	mov r2, #0xa
_020865BC:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _020865BC
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	add r2, sp, #0x54
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x2
	add r2, sp, #0x70
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x3
	add r2, sp, #0x8c
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02018744
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02018744
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02018744
	ldr r1, _0208665C ; =0x04000008
	mov r0, #0x3
	ldrh r2, [r1, #0x0]
	bic r2, r0
	mov r0, #0x1
	orr r2, r0
	strh r2, [r1, #0x0]
	add r1, r0, #0x0
	bl FUN_0201E6E4
	bl FUN_0201E788
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E6E4
	ldr r5, _02086660 ; =0x020FCE60
	add r3, sp, #0x0
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x4
	str r0, [r3, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl FUN_02016C18
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02018744
	add sp, #0xa8
	pop {r3-r5, pc}
	.balign 4
_02086650: .word 0x020FCEBC
_02086654: .word 0x020FCE24
_02086658: .word 0x020FCF84
_0208665C: .word 0x04000008
_02086660: .word 0x020FCE60

	thumb_func_start FUN_02086664
FUN_02086664: ; 0x02086664
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x3c]
	bl FUN_020081C4
	bl FUN_0201C30C
	bl FUN_0200BC30
	ldr r0, [r4, #0x8]
	bl FUN_0200372C
	ldr r0, [r4, #0x4]
	bl FUN_0201AB60
	ldr r3, _02086690 ; =0x027E0000
	ldr r1, _02086694 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.balign 4
_02086690: .word 0x027E0000
_02086694: .word 0x00003FF8

	thumb_func_start FUN_02086698
FUN_02086698: ; 0x02086698
	push {r3, lr}
	bl FUN_020222AC
	bl FUN_02013364
	cmp r0, #0x0
	ble _020866AE
	bl FUN_020222AC
	bl FUN_020B02C8
_020866AE:
	bl FUN_02013388
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020222B4
	pop {r3, pc}

	thumb_func_start FUN_020866BC
FUN_020866BC: ; 0x020866BC
	push {lr}
	sub sp, #0xc
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x47
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r2, r1, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}
	.balign 4

	thumb_func_start FUN_020866DC
FUN_020866DC: ; 0x020866DC
	push {lr}
	sub sp, #0xc
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x47
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_020866FC
FUN_020866FC: ; 0x020866FC
	push {r3-r6, lr}
	sub sp, #0xc
	add r6, r2, #0x0
	add r4, r1, #0x0
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	mov r1, #0x47
	str r1, [sp, #0x4]
	mov r1, #0x1
	mov r2, #0x14
	mov r3, #0xf
	add r5, r0, #0x0
	bl FUN_0200CD68
	add r0, r6, #0x0
	bl FUN_0200CD64
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xc0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x26
	mov r3, #0x47
	bl FUN_020030E8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x47
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x32
	mov r3, #0xd
	bl FUN_0200CB00
	bl FUN_0200CAFC
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xd0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x26
	mov r3, #0x47
	bl FUN_020030E8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xe0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0xe
	mov r2, #0x7
	mov r3, #0x47
	bl FUN_020030E8
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_02086784
FUN_02086784: ; 0x02086784
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r1, #0x0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_0201901C
	ldr r0, [sp, #0x28]
	lsl r2, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	lsl r3, r6, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x30]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x38]
	lsr r2, r2, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x34]
	lsr r3, r3, #0x18
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_02019064
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x14
	mov r3, #0xc
	bl FUN_0200D0BC
	add r0, r5, #0x0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r5, #0x0
	bl FUN_020191D0
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_020867EC
FUN_020867EC: ; 0x020867EC
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r1, #0x0
	mov r1, #0xf
	str r0, [sp, #0xc]
	str r2, [sp, #0x10]
	add r6, r3, #0x0
	bl FUN_02019620
	ldr r2, _02086874 ; =0x0000013F
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0x47
	bl FUN_0200A86C
	add r7, r0, #0x0
	mov r0, #0x47
	bl FUN_0200AA80
	add r5, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_0200A914
	str r0, [sp, #0x14]
	mov r0, #0xff
	mov r1, #0x47
	bl FUN_020219F4
	add r4, r0, #0x0
	ldr r0, [sp, #0x10]
	bl FUN_020690E4
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200AC60
	ldr r2, [sp, #0x14]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200B7B8
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xc]
	mov r1, #0x1
	add r2, r4, #0x0
	str r3, [sp, #0x8]
	bl FUN_0201BD84
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	bl FUN_02021A20
	ldr r0, [sp, #0x14]
	bl FUN_02021A20
	add r0, r5, #0x0
	bl FUN_0200AB18
	add r0, r6, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_02086874: .word 0x0000013F

	thumb_func_start FUN_02086878
FUN_02086878: ; 0x02086878
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r6, r1, #0x0
	str r2, [sp, #0x14]
	add r4, r3, #0x0
	bl FUN_0201901C
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x38]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x40]
	lsl r2, r4, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x44]
	lsl r3, r3, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4c]
	ldr r1, [sp, #0x14]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x48]
	lsr r2, r2, #0x18
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	lsr r3, r3, #0x18
	bl FUN_02019064
	mov r0, #0x2
	mov r1, #0x47
	bl FUN_02012838
	str r0, [r5, #0x44]
	ldr r2, _0208695C ; =0x0000013F
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0x47
	bl FUN_0200A86C
	add r7, r0, #0x0
	mov r4, #0x0
_020868DE:
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_0200A914
	add r6, r0, #0x0
	ldr r0, [r5, #0x44]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_020128A0
	add r0, r6, #0x0
	bl FUN_02021A20
	add r4, r4, #0x1
	cmp r4, #0x2
	blt _020868DE
	add r0, r7, #0x0
	bl FUN_0200A8B8
	ldr r0, [r5, #0x44]
	mov r1, #0x0
	str r0, [sp, #0x18]
	add r0, sp, #0x18
	strb r1, [r0, #0x8]
	ldr r1, [sp, #0x14]
	mov r2, #0x2
	str r1, [sp, #0x1c]
	mov r1, #0x1
	strb r1, [r0, #0x9]
	strb r2, [r0, #0xa]
	ldrb r3, [r0, #0xb]
	mov r2, #0xf
	bic r3, r2
	strb r3, [r0, #0xb]
	ldrb r3, [r0, #0xb]
	mov r2, #0x30
	bic r3, r2
	strb r3, [r0, #0xb]
	ldrb r3, [r0, #0xb]
	mov r2, #0xc0
	bic r3, r2
	mov r2, #0x40
	orr r2, r3
	strb r2, [r0, #0xb]
	ldr r0, [sp, #0x14]
	mov r2, #0x32
	mov r3, #0xd
	bl FUN_0200CCA4
	mov r0, #0x47
	str r0, [sp, #0x0]
	mov r0, #0x2
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x18
	mov r1, #0x8
	add r3, r2, #0x0
	bl FUN_02001C14
	str r0, [r5, #0x48]
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0208695C: .word 0x0000013F

	thumb_func_start FUN_02086960
FUN_02086960: ; 0x02086960
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x28
	mov r1, #0x1
	bl FUN_0200CCF8
	add r0, r4, #0x0
	add r0, #0x28
	bl FUN_02019570
	add r0, r4, #0x0
	add r0, #0x28
	bl FUN_02019178
	ldr r0, [r4, #0x48]
	mov r1, #0x0
	bl FUN_02001C5C
	ldr r0, [r4, #0x44]
	bl FUN_02012870
	pop {r4, pc}

	thumb_func_start FUN_0208698C
FUN_0208698C: ; 0x0208698C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02019570
	add r0, r4, #0x0
	bl FUN_02019178
	pop {r4, pc}

	thumb_func_start FUN_0208699C
FUN_0208699C: ; 0x0208699C
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	mov r1, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x47
	str r0, [sp, #0xc]
	mov r0, #0x76
	add r2, r5, #0x0
	mov r3, #0x3
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x1
	str r1, [sp, #0x8]
	mov r0, #0x47
	str r0, [sp, #0xc]
	mov r0, #0x76
	add r2, r5, #0x0
	mov r3, #0x3
	bl FUN_020068C8
	mov r1, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x40
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x76
	mov r2, #0x8
	mov r3, #0x47
	bl FUN_020030E8
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020869F0
FUN_020869F0: ; 0x020869F0
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x47
	add r4, r1, #0x0
	str r0, [sp, #0xc]
	mov r0, #0xc
	mov r1, #0xa
	add r2, r5, #0x0
	mov r3, #0x4
	bl FUN_0200687C
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x47
	str r0, [sp, #0xc]
	mov r0, #0xc
	mov r1, #0xb
	add r2, r5, #0x0
	mov r3, #0x4
	bl FUN_020068C8
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	mov r0, #0x0
	mov r1, #0xc
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	add r2, r1, #0x0
	mov r3, #0x47
	bl FUN_020030E8
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02086A48
FUN_02086A48: ; 0x02086A48
	push {r4, lr}
	ldr r3, _02086A60 ; =0x021064B8
	mov r2, #0x0
	ldr r3, [r3, #0x0]
	blx r3
	add r4, r0, #0x0
	bl FUN_0201327C
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02086A60: .word 0x021064B8

	thumb_func_start FUN_02086A64
FUN_02086A64: ; 0x02086A64
	push {r4, lr}
	ldr r3, _02086A7C ; =0x021064C0
	mov r2, #0x0
	ldr r3, [r3, #0x0]
	blx r3
	add r4, r0, #0x0
	bl FUN_020132BC
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_02086A7C: .word 0x021064C0

	thumb_func_start FUN_02086A80
FUN_02086A80: ; 0x02086A80
	push {r4, lr}
	sub sp, #0x8
	mov r1, #0x12
	lsl r1, r1, #0xa
	add r4, r0, #0x0
	bl FUN_02016998
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r3, #0x12
	ldr r0, _02086AC0 ; =FUN_02086A48
	ldr r1, _02086AC4 ; =FUN_02086A64
	lsl r3, r3, #0xa
	str r4, [sp, #0x4]
	bl FUN_02012CDC
	add r4, r0, #0x0
	bl FUN_0201343C
	add r2, r0, #0x0
	beq _02086AB8
	mov r0, #0x1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
_02086AB8:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4, pc}
	nop
_02086AC0: .word FUN_02086A48
_02086AC4: .word FUN_02086A64

	thumb_func_start FUN_02086AC8
FUN_02086AC8: ; 0x02086AC8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_02086A80
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0201318C
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0xa
	mov r3, #0x1
	bl FUN_02013194
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02086AF0
FUN_02086AF0: ; 0x02086AF0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020133E8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02012DE4
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}

	thumb_func_start FUN_02086B08
FUN_02086B08: ; 0x02086B08
	push {r3}
	sub sp, #0xc
	add r2, sp, #0x0
	mov r1, #0x0
	str r1, [r2, #0x0]
	str r1, [r2, #0x4]
	str r1, [r2, #0x8]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #0x0]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x4]
	add r1, r2, r1
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #0x4]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #0x8]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	add r1, r2, r1
	str r1, [r0, #0x30]
	add sp, #0xc
	pop {r3}
	bx lr

	thumb_func_start FUN_02086B40
FUN_02086B40: ; 0x02086B40
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x10
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02086B54
	bl ErrorHandling
_02086B54:
	ldr r0, [r5, #0x0]
	ldr r2, [r5, #0x4]
	mov r1, #0x77
	str r0, [r4, #0x0]
	str r2, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_02086AC8
	mov r1, #0x1
	str r0, [r4, #0xc]
	bl FUN_02013440
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02086B70
FUN_02086B70: ; 0x02086B70
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r2, _02086B88 ; =FUN_02086B08
	add r3, r4, #0x0
	bl FUN_020133AC
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_02013440
	pop {r4, pc}
	.balign 4
_02086B88: .word FUN_02086B08

	thumb_func_start FUN_02086B8C
FUN_02086B8C: ; 0x02086B8C
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_020133C8
	cmp r0, #0x0
	beq _02086B9C
	mov r0, #0x1
	pop {r3, pc}
_02086B9C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02086BA0
FUN_02086BA0: ; 0x02086BA0
	ldr r3, _02086BA4 ; =FUN_02016A18
	bx r3
	.balign 4
_02086BA4: .word FUN_02016A18

	thumb_func_start FUN_02086BA8
FUN_02086BA8: ; 0x02086BA8
	push {r4-r6, lr}
	sub sp, #0x38
	ldr r3, _02086C8C ; =0x020FCE9C
	add r2, sp, #0x18
	add r6, r0, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r5, [r6, #0x4c]
	ldr r4, [r6, #0x50]
	ldr r6, [r6, #0x8]
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02086C90 ; =0x00004E20
	add r1, r5, #0x0
	str r0, [sp, #0x8]
	ldr r3, [sp, #0x18]
	add r0, r4, #0x0
	mov r2, #0x76
	bl FUN_0200C00C
	mov r0, #0x76
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	mov r1, #0x2
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _02086C94 ; =0x00004E21
	add r2, r4, #0x0
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	add r3, r5, #0x0
	bl FUN_0200C0DC
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _02086C98 ; =0x00004E22
	add r1, r5, #0x0
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x20]
	add r0, r4, #0x0
	mov r2, #0x76
	bl FUN_0200C124
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _02086C9C ; =0x00004E23
	add r1, r5, #0x0
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x24]
	add r0, r4, #0x0
	mov r2, #0x76
	bl FUN_0200C13C
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02086CA0 ; =0x000061A8
	add r1, r5, #0x0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r2, #0x76
	mov r3, #0x7
	bl FUN_0200C00C
	mov r0, #0x76
	str r0, [sp, #0x0]
	mov r0, #0xa
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _02086CA4 ; =0x000061A9
	mov r1, #0x2
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl FUN_0200C0DC
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _02086CA8 ; =0x000061AA
	add r1, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r2, #0x76
	mov r3, #0x6
	bl FUN_0200C124
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _02086CAC ; =0x000061AB
	add r1, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r2, #0x76
	mov r3, #0x5
	bl FUN_0200C13C
	add sp, #0x38
	pop {r4-r6, pc}
	.balign 4
_02086C8C: .word 0x020FCE9C
_02086C90: .word 0x00004E20
_02086C94: .word 0x00004E21
_02086C98: .word 0x00004E22
_02086C9C: .word 0x00004E23
_02086CA0: .word 0x000061A8
_02086CA4: .word 0x000061A9
_02086CA8: .word 0x000061AA
_02086CAC: .word 0x000061AB

	thumb_func_start FUN_02086CB0
FUN_02086CB0: ; 0x02086CB0
	push {r3-r4, lr}
	sub sp, #0x34
	add r4, r0, #0x0
	mov r1, #0x80
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	mov r1, #0x78
	strh r1, [r0, #0x2]
	mov r1, #0x0
	strh r1, [r0, #0x4]
	strh r1, [r0, #0x6]
	mov r0, #0x1
	mov r2, #0x2
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x30]
	ldr r1, _02086D4C ; =0x00004E20
	str r0, [sp, #0x10]
	add r0, r1, #0x1
	str r0, [sp, #0x18]
	add r0, r1, #0x2
	str r0, [sp, #0x1c]
	add r0, r1, #0x3
	str r0, [sp, #0x20]
	sub r0, r2, #0x3
	str r2, [sp, #0x2c]
	str r1, [sp, #0x14]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	ldr r0, [r4, #0x50]
	ldr r1, [r4, #0x4c]
	add r2, sp, #0x0
	bl FUN_0200C154
	str r0, [r4, #0x6c]
	bl FUN_0200C5A8
	ldr r0, [r4, #0x6c]
	mov r1, #0x2
	bl FUN_0200C840
	mov r2, #0x0
	add r0, sp, #0x0
	add r1, r2, #0x0
	strh r2, [r0, #0x0]
	sub r1, #0x10
	strh r1, [r0, #0x2]
	ldr r1, _02086D50 ; =0x000061A8
	str r2, [sp, #0x2c]
	add r0, r1, #0x1
	str r0, [sp, #0x18]
	add r0, r1, #0x2
	str r0, [sp, #0x1c]
	add r0, r1, #0x3
	str r1, [sp, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [r4, #0x50]
	ldr r1, [r4, #0x4c]
	add r2, sp, #0x0
	bl FUN_0200C154
	str r0, [r4, #0x70]
	bl FUN_0200C5A8
	mov r1, #0x90
	add r0, sp, #0x0
	strh r1, [r0, #0x2]
	ldr r0, [r4, #0x50]
	ldr r1, [r4, #0x4c]
	add r2, sp, #0x0
	bl FUN_0200C154
	str r0, [r4, #0x74]
	bl FUN_0200C5A8
	add sp, #0x34
	pop {r3-r4, pc}
	nop
_02086D4C: .word 0x00004E20
_02086D50: .word 0x000061A8

	thumb_func_start FUN_02086D54
FUN_02086D54: ; 0x02086D54
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r4, r6, #0x0
	ldr r1, [r6, #0x78]
	add r4, #0x78
	cmp r1, #0x0
	bne _02086DE6
	ldr r0, [r4, #0x4]
	cmp r0, #0xa
	blt _02086D74
	add r0, r1, #0x1
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	b _02086DE6
_02086D74:
	mov r1, #0x14
	add r3, r7, #0x0
	mul r3, r1
	ldr r1, _02086DF4 ; =0x020FCEE4
	lsl r2, r0, #0x1
	add r1, r1, r3
	ldrsh r1, [r2, r1]
	lsl r0, r0, #0x2
	mov r5, #0x0
	mov r12, r1
	ldr r1, _02086DF8 ; =0x020FCF34
	add r1, r1, r3
	ldrsh r2, [r2, r1]
	mov r1, #0x28
	add r3, r7, #0x0
	mul r3, r1
	ldr r1, _02086DFC ; =0x020FCFD8
	add r1, r1, r3
	ldr r7, [r0, r1]
	ldr r1, _02086E00 ; =0x020FD078
	add r1, r1, r3
	ldr r0, [r0, r1]
	str r0, [sp, #0x0]
	mov r0, r12
	cmp r0, #0xff
	bne _02086DAC
	mov r12, r5
	add r5, r5, #0x1
_02086DAC:
	cmp r2, #0xff
	bne _02086DB4
	mov r2, #0x0
	add r5, r5, #0x1
_02086DB4:
	ldr r0, [r6, #0x6c]
	mov r1, r12
	bl FUN_0200C82C
	mov r0, #0x0
	add r1, r7, #0x0
	bl _feq
	beq _02086DD2
	ldr r0, [r6, #0x6c]
	ldr r2, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_0200C884
	b _02086DD4
_02086DD2:
	add r5, r5, #0x1
_02086DD4:
	cmp r5, #0x3
	beq _02086DE0
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02086DEE
_02086DE0:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02086DE6:
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	pop {r3-r7, pc}
_02086DEE:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_02086DF4: .word 0x020FCEE4
_02086DF8: .word 0x020FCF34
_02086DFC: .word 0x020FCFD8
_02086E00: .word 0x020FD078

	thumb_func_start FUN_02086E04
FUN_02086E04: ; 0x02086E04
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02086D54
	cmp r0, #0x0
	bne _02086E16
	mov r0, #0x2
	pop {r3-r5, pc}
_02086E16:
	cmp r4, #0x4
	ldr r0, [r5, #0x7c]
	bne _02086E24
	cmp r0, #0x6
	bne _02086E2C
	mov r0, #0x1
	pop {r3-r5, pc}
_02086E24:
	cmp r0, #0x6
	bne _02086E2C
	mov r0, #0x1
	pop {r3-r5, pc}
_02086E2C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02086E30
FUN_02086E30: ; 0x02086E30
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x6c]
	bl FUN_0200C3DC
	ldr r0, [r4, #0x70]
	bl FUN_0200C3DC
	ldr r0, [r4, #0x74]
	bl FUN_0200C3DC
	pop {r4, pc}

	thumb_func_start FUN_02086E48
FUN_02086E48: ; 0x02086E48
	push {r3-r6, lr}
	sub sp, #0x4c
	add r4, r0, #0x0
	mov r0, #0x47
	bl FUN_0200BB14
	add r2, sp, #0x2c
	ldr r5, _02086EC8 ; =0x020FCE7C
	str r0, [r4, #0x4c]
	ldmia r5!, {r0-r1}
	add r3, r2, #0x0
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	ldr r6, _02086ECC ; =0x020FCE34
	stmia r2!, {r0-r1}
	add r5, sp, #0x18
	ldmia r6!, {r0-r1}
	add r2, r5, #0x0
	stmia r5!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r1, r3, #0x0
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x4c]
	mov r3, #0x20
	bl FUN_0200BB6C
	ldr r3, _02086ED0 ; =0x020FCE48
	add r2, sp, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x4c]
	bl FUN_0200BB34
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	ldr r1, [r4, #0x48]
	mov r2, #0xff
	bl FUN_0200BBF0
	cmp r0, #0x0
	bne _02086EB2
	bl ErrorHandling
_02086EB2:
	ldr r0, [r4, #0x4c]
	ldr r1, [r4, #0x48]
	add r2, sp, #0x0
	bl FUN_0200BF60
	cmp r0, #0x0
	bne _02086EC4
	bl ErrorHandling
_02086EC4:
	add sp, #0x4c
	pop {r3-r6, pc}
	.balign 4
_02086EC8: .word 0x020FCE7C
_02086ECC: .word 0x020FCE34
_02086ED0: .word 0x020FCE48

	thumb_func_start FUN_02086ED4
FUN_02086ED4: ; 0x02086ED4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4c]
	ldr r1, [r4, #0x48]
	bl FUN_0200C398
	ldr r0, [r4, #0x4c]
	bl FUN_0200BD04
	pop {r4, pc}

	thumb_func_start FUN_02086EE8
FUN_02086EE8: ; 0x02086EE8
	push {r3-r7, lr}
	sub sp, #0x38
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x5
	ldr r4, [r0, #0xc]
	mov r2, #0x0
	add r0, r4, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02068E14
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x4c
	add r2, sp, #0x10
	bl FUN_02067830
	add r0, sp, #0x28
	add r1, r4, #0x0
	mov r2, #0x2
	bl FUN_02068B68
	lsl r1, r6, #0x10
	add r0, sp, #0x14
	lsr r1, r1, #0x10
	bl FUN_02069010
	mov r1, #0x0
	str r1, [sp, #0x0]
	add r7, #0x60
	str r1, [sp, #0x4]
	add r0, sp, #0x14
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #0x3c]
	add r1, sp, #0x28
	mov r2, #0x80
	add r3, r7, #0x0
	bl FUN_020073A0
	str r0, [r5, #0x68]
	add sp, #0x38
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02086F4C
FUN_02086F4C: ; 0x02086F4C
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02068854
	add r6, r0, #0x0
	ldr r0, [r5, #0x68]
	mov r1, #0x1
	bl FUN_02007314
	lsl r2, r4, #0x10
	str r6, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x68]
	lsr r2, r2, #0x10
	mov r3, #0x2
	bl FUN_02069038
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_02086F8C
FUN_02086F8C: ; 0x02086F8C
	ldr r3, _02086F94 ; =FUN_02007534
	ldr r0, [r0, #0x68]
	bx r3
	nop
_02086F94: .word FUN_02007534

	thumb_func_start FUN_02086F98
FUN_02086F98: ; 0x02086F98
	ldr r3, _02086FA4 ; =FUN_02007558
	add r2, r1, #0x0
	ldr r0, [r0, #0x68]
	mov r1, #0x6
	bx r3
	nop
_02086FA4: .word FUN_02007558

	thumb_func_start FUN_02086FA8
FUN_02086FA8: ; 0x02086FA8
	push {r3, lr}
	ldr r1, [r0, #0x58]
	lsl r2, r1, #0x2
	ldr r1, _02086FB8 ; =0x020FD118
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02086FB8: .word 0x020FD118

	thumb_func_start FUN_02086FBC
FUN_02086FBC: ; 0x02086FBC
	push {r3-r5, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	ldr r1, [r4, #0x5c]
	mov r5, #0x1
	cmp r1, #0x11
	bls _02086FCC
	b _0208720E
_02086FCC:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02086FD8: ; jump table (using 16-bit offset)
	.short _02086FFC - _02086FD8 - 2; case 0
	.short _0208706A - _02086FD8 - 2; case 1
	.short _02087074 - _02086FD8 - 2; case 2
	.short _02087092 - _02086FD8 - 2; case 3
	.short _020870A2 - _02086FD8 - 2; case 4
	.short _020870B2 - _02086FD8 - 2; case 5
	.short _020870C2 - _02086FD8 - 2; case 6
	.short _020870D2 - _02086FD8 - 2; case 7
	.short _0208710E - _02086FD8 - 2; case 8
	.short _02087122 - _02086FD8 - 2; case 9
	.short _02087132 - _02086FD8 - 2; case 10
	.short _02087158 - _02086FD8 - 2; case 11
	.short _020871AA - _02086FD8 - 2; case 12
	.short _020871E2 - _02086FD8 - 2; case 13
	.short _020871EE - _02086FD8 - 2; case 14
	.short _020871F4 - _02086FD8 - 2; case 15
	.short _020871FE - _02086FD8 - 2; case 16
	.short _0208720E - _02086FD8 - 2; case 17
_02086FFC:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_0208699C
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_020869F0
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x14]
	bl FUN_020866FC
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x3b
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	add r1, r4, #0x0
	ldr r0, [r4, #0x4]
	add r1, #0x18
	add r2, r5, #0x0
	mov r3, #0x2
	bl FUN_02086784
	add r0, r4, #0x0
	bl FUN_02086BA8
	add r0, r4, #0x0
	bl FUN_02086CB0
	add r0, r4, #0x0
	bl FUN_02086EE8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02086F98
	mov r0, #0x47
	str r0, [sp, #0x18]
	mov r0, #0x0
	str r0, [sp, #0x1c]
	add r0, sp, #0x18
	bl FUN_02086B40
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_0208706A:
	bl FUN_020866BC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087074:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0208712A
	bl FUN_0200541C
	ldr r1, _02087240 ; =0x00000475
	mov r0, #0xd
	mov r2, #0x1
	bl FUN_0200433C
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_02087092:
	bl FUN_0208749C
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870A2:
	bl FUN_020874E4
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870B2:
	bl FUN_02087554
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870C2:
	bl FUN_020875AC
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870D2:
	bl FUN_02087610
	cmp r0, #0x0
	bne _0208712A
	add r0, r4, #0x0
	bl FUN_02086F4C
	ldr r0, [r4, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x0
	bl FUN_020867EC
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_0208710E:
	bl FUN_02005670
	cmp r0, #0x0
	bne _0208712A
	ldr r0, _02087244 ; =0x00000484
	bl FUN_02005C28
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087122:
	bl FUN_02005CBC
	cmp r0, #0x0
	beq _0208712C
_0208712A:
	b _02087232
_0208712C:
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087132:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087232
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x1
	bl FUN_020867EC
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087158:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087232
	ldr r0, [r4, #0x54]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _02087232
	ldr r0, [r4, #0x68]
	bl FUN_02007390
	cmp r0, #0x0
	bne _02087232
	mov r0, #0x19
	str r0, [sp, #0x0]
	mov r0, #0xd
	str r0, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	mov r0, #0xa7
	str r0, [sp, #0x10]
	mov r0, #0xe
	str r0, [sp, #0x14]
	add r2, r4, #0x0
	ldr r1, [r4, #0x4]
	add r0, r4, #0x0
	add r2, #0x28
	mov r3, #0x1
	bl FUN_02086878
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871AA:
	ldr r0, [r4, #0x48]
	bl FUN_02001C78
	sub r1, r5, #0x3
	cmp r0, r1
	beq _020871BE
	add r1, r1, #0x1
	cmp r0, r1
	beq _02087232
	b _020871CC
_020871BE:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871CC:
	cmp r0, #0x0
	bne _020871D4
	add r1, r5, #0x0
	b _020871D6
_020871D4:
	mov r1, #0x0
_020871D6:
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871E2:
	bl FUN_02086960
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871EE:
	add r0, r1, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871F4:
	bl FUN_020866DC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_020871FE:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02087232
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_0208720E:
	add r0, r4, #0x0
	bl FUN_02086F8C
	add r0, r4, #0x0
	bl FUN_02086E30
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_0208698C
	ldr r0, [r4, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02086AF0
	ldr r0, [r4, #0x40]
	bl FUN_02086BA0
	mov r5, #0x0
_02087232:
	ldr r0, [r4, #0x4c]
	bl FUN_0200BC1C
	add r0, r5, #0x0
	add sp, #0x20
	pop {r3-r5, pc}
	nop
_02087240: .word 0x00000475
_02087244: .word 0x00000484

	thumb_func_start FUN_02087248
FUN_02087248: ; 0x02087248
	push {r3-r5, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	ldr r1, [r4, #0x5c]
	mov r5, #0x1
	cmp r1, #0x11
	bls _02087258
	b _02087462
_02087258:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02087264: ; jump table (using 16-bit offset)
	.short _02087288 - _02087264 - 2; case 0
	.short _020872FE - _02087264 - 2; case 1
	.short _02087308 - _02087264 - 2; case 2
	.short _02087322 - _02087264 - 2; case 3
	.short _0208735C - _02087264 - 2; case 4
	.short _0208735C - _02087264 - 2; case 5
	.short _0208735C - _02087264 - 2; case 6
	.short _0208735C - _02087264 - 2; case 7
	.short _02087362 - _02087264 - 2; case 8
	.short _02087376 - _02087264 - 2; case 9
	.short _02087386 - _02087264 - 2; case 10
	.short _020873AC - _02087264 - 2; case 11
	.short _020873FE - _02087264 - 2; case 12
	.short _02087436 - _02087264 - 2; case 13
	.short _02087442 - _02087264 - 2; case 14
	.short _02087448 - _02087264 - 2; case 15
	.short _02087452 - _02087264 - 2; case 16
	.short _02087462 - _02087264 - 2; case 17
_02087288:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_0208699C
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_020869F0
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x14]
	bl FUN_020866FC
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x3b
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	add r1, r4, #0x0
	ldr r0, [r4, #0x4]
	add r1, #0x18
	add r2, r5, #0x0
	mov r3, #0x2
	bl FUN_02086784
	add r0, r4, #0x0
	bl FUN_02086BA8
	add r0, r4, #0x0
	bl FUN_02086CB0
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	add r0, r4, #0x0
	bl FUN_02086EE8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02086F98
	mov r0, #0x47
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	str r0, [sp, #0x1c]
	add r0, sp, #0x18
	bl FUN_02086B40
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_020872FE:
	bl FUN_020866BC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087308:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0208737E
	ldr r1, _02087494 ; =0x00000475
	mov r0, #0xd
	mov r2, #0x1
	bl FUN_0200433C
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087322:
	bl FUN_02087820
	cmp r0, #0x0
	bne _0208737E
	add r0, r4, #0x0
	bl FUN_02086F4C
	ldr r0, [r4, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x0
	bl FUN_020867EC
	str r0, [r4, #0xc]
	mov r0, #0x8
	str r0, [r4, #0x5c]
	b _02087486
_0208735C:
	bl ErrorHandling
	b _02087486
_02087362:
	bl FUN_02005670
	cmp r0, #0x0
	bne _0208737E
	ldr r0, _02087498 ; =0x00000484
	bl FUN_02005C28
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087376:
	bl FUN_02005CBC
	cmp r0, #0x0
	beq _02087380
_0208737E:
	b _02087486
_02087380:
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087386:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087486
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x1
	bl FUN_020867EC
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_020873AC:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087486
	ldr r0, [r4, #0x54]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _02087486
	ldr r0, [r4, #0x68]
	bl FUN_02007390
	cmp r0, #0x0
	bne _02087486
	mov r0, #0x19
	str r0, [sp, #0x0]
	mov r0, #0xd
	str r0, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	mov r0, #0xa7
	str r0, [sp, #0x10]
	mov r0, #0xe
	str r0, [sp, #0x14]
	add r2, r4, #0x0
	ldr r1, [r4, #0x4]
	add r0, r4, #0x0
	add r2, #0x28
	mov r3, #0x1
	bl FUN_02086878
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_020873FE:
	ldr r0, [r4, #0x48]
	bl FUN_02001C78
	sub r1, r5, #0x3
	cmp r0, r1
	beq _02087412
	add r1, r1, #0x1
	cmp r0, r1
	beq _02087486
	b _02087420
_02087412:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087420:
	cmp r0, #0x0
	bne _02087428
	add r1, r5, #0x0
	b _0208742A
_02087428:
	mov r1, #0x0
_0208742A:
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087436:
	bl FUN_02086960
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087442:
	add r0, r1, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087448:
	bl FUN_020866DC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087452:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02087486
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087462:
	add r0, r4, #0x0
	bl FUN_02086F8C
	add r0, r4, #0x0
	bl FUN_02086E30
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_0208698C
	ldr r0, [r4, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02086AF0
	ldr r0, [r4, #0x40]
	bl FUN_02086BA0
	mov r5, #0x0
_02087486:
	ldr r0, [r4, #0x4c]
	bl FUN_0200BC1C
	add r0, r5, #0x0
	add sp, #0x20
	pop {r3-r5, pc}
	nop
_02087494: .word 0x00000475
_02087498: .word 0x00000484

	thumb_func_start FUN_0208749C
FUN_0208749C: ; 0x0208749C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x64]
	cmp r0, #0x0
	beq _020874AC
	cmp r0, #0x1
	beq _020874BC
	b _020874D4
_020874AC:
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C61C
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _020874DC
_020874BC:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0x19
	blt _020874DC
	ldr r0, _020874E0 ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _020874DC
_020874D4:
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r4, pc}
_020874DC:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_020874E0: .word 0x00000714

	thumb_func_start FUN_020874E4
FUN_020874E4: ; 0x020874E4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _020874F4
	cmp r1, #0x1
	beq _0208750E
	b _02087532
_020874F4:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _0208754C
	ldr r0, [r4, #0x6c]
	mov r1, #0x1
	bl FUN_0200C61C
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _0208754C
_0208750E:
	mov r1, #0x0
	bl FUN_02086E04
	cmp r0, #0x2
	bne _0208754C
	ldr r0, _02087550 ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x6c]
	mov r1, #0x2
	bl FUN_0200C61C
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	mov r0, #0x0
	str r0, [r4, #0x60]
	b _0208754C
_02087532:
	mov r1, #0x0
	bl FUN_02086E04
	cmp r0, #0x2
	bne _0208754C
	ldr r0, [r4, #0x6c]
	mov r1, #0x2
	bl FUN_0200C61C
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r4, pc}
_0208754C:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02087550: .word 0x00000714

	thumb_func_start FUN_02087554
FUN_02087554: ; 0x02087554
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _02087564
	cmp r1, #0x1
	beq _0208756A
	b _0208759C
_02087564:
	add r0, r1, #0x1
	str r0, [r4, #0x64]
	b _020875A4
_0208756A:
	mov r1, #0x1
	bl FUN_02086E04
	add r5, r0, #0x0
	cmp r5, #0x1
	bne _0208758C
	ldr r0, _020875A8 ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x6c]
	mov r1, #0x3
	bl FUN_0200C61C
	ldr r0, [r4, #0x40]
	mov r1, #0x0
	bl FUN_02086B70
_0208758C:
	cmp r5, #0x2
	bne _020875A4
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _020875A4
_0208759C:
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r3-r5, pc}
_020875A4:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_020875A8: .word 0x00000714

	thumb_func_start FUN_020875AC
FUN_020875AC: ; 0x020875AC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _020875BC
	cmp r1, #0x1
	beq _020875CE
	b _02087600
_020875BC:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _02087608
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087608
_020875CE:
	mov r1, #0x2
	bl FUN_02086E04
	add r5, r0, #0x0
	cmp r5, #0x1
	bne _020875F0
	ldr r0, _0208760C ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x6c]
	mov r1, #0x4
	bl FUN_0200C61C
	ldr r0, [r4, #0x40]
	mov r1, #0x1
	bl FUN_02086B70
_020875F0:
	cmp r5, #0x2
	bne _02087608
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087608
_02087600:
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r3-r5, pc}
_02087608:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0208760C: .word 0x00000714

	thumb_func_start FUN_02087610
FUN_02087610: ; 0x02087610
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x5
	bls _0208761E
	b _020877FC
_0208761E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0208762A: ; jump table (using 16-bit offset)
	.short _02087636 - _0208762A - 2; case 0
	.short _02087658 - _0208762A - 2; case 1
	.short _0208769A - _0208762A - 2; case 2
	.short _02087702 - _0208762A - 2; case 3
	.short _02087794 - _0208762A - 2; case 4
	.short _020877E0 - _0208762A - 2; case 5
_02087636:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _020876A4
	ldr r0, [r4, #0x6c]
	mov r1, #0x4
	bl FUN_0200C61C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_02087658:
	mov r1, #0x3
	bl FUN_02086E04
	add r5, r0, #0x0
	cmp r5, #0x1
	bne _02087682
	ldr r0, [r4, #0x6c]
	mov r1, #0x5
	bl FUN_0200C61C
	ldr r0, _02087818 ; =0x00000707
	bl FUN_020054C8
	ldr r0, [r4, #0x40]
	mov r1, #0x2
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x3
	bl FUN_02086B70
_02087682:
	cmp r5, #0x2
	bne _020876A4
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_0208769A:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0xa
	bge _020876A6
_020876A4:
	b _02087810
_020876A6:
	mov r3, #0x0
	str r3, [r4, #0x60]
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _0208781C ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	bl FUN_02020354
	mov r1, #0x1
	bl FUN_0201E28C
	add r5, r0, #0x0
	mov r3, #0x0
	mov r6, #0x1
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _0208781C ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	lsl r6, r5
	eor r2, r6
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	lsr r2, r2, #0x10
	bl FUN_02003210
	ldr r0, _0208781C ; =0x0000FFFF
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E68
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_02087702:
	add r1, sp, #0xc
	ldr r0, [r4, #0x70]
	mov r5, #0x0
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	add r1, r5, #0x0
	ldrsh r2, [r0, r1]
	add r0, r1, #0x0
	sub r0, #0x30
	cmp r2, r0
	ble _02087728
	ldr r0, [r4, #0x70]
	sub r2, r1, #0x4
	bl FUN_0200C82C
	b _0208772A
_02087728:
	add r5, r5, #0x1
_0208772A:
	add r1, sp, #0xc
	ldr r0, [r4, #0x74]
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, #0xc0
	bge _0208774A
	ldr r0, [r4, #0x74]
	mov r2, #0x4
	bl FUN_0200C82C
	b _0208774C
_0208774A:
	add r5, r5, #0x1
_0208774C:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087810
	cmp r5, #0x2
	bne _02087810
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087810
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_0201E6E4
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02086F98
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x70]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x74]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_02087794:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0x19
	blt _02087810
	mov r2, #0x0
	ldr r0, _0208781C ; =0x0000FFFF
	str r2, [r4, #0x60]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E68
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _0208781C ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _0208781C ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_02003210
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_020877E0:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087810
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087810
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_020877FC:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _02087810
	mov r0, #0x0
	str r0, [r4, #0x64]
	add sp, #0x10
	str r0, [r4, #0x60]
	pop {r4-r6, pc}
_02087810:
	mov r0, #0x1
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02087818: .word 0x00000707
_0208781C: .word 0x0000FFFF

	thumb_func_start FUN_02087820
FUN_02087820: ; 0x02087820
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r0, [r4, #0x64]
	cmp r0, #0x4
	bls _0208782E
	b _020879FC
_0208782E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0208783A: ; jump table (using 16-bit offset)
	.short _02087844 - _0208783A - 2; case 0
	.short _02087874 - _0208783A - 2; case 1
	.short _02087902 - _0208783A - 2; case 2
	.short _02087994 - _0208783A - 2; case 3
	.short _020879E0 - _0208783A - 2; case 4
_02087844:
	ldr r0, [r4, #0x40]
	mov r1, #0x0
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x1
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x2
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x3
	bl FUN_02086B70
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_02087874:
	ldr r0, [r4, #0x60]
	cmp r0, #0x19
	beq _02087884
	cmp r0, #0x50
	beq _0208788C
	cmp r0, #0x8e
	beq _02087894
	b _0208789A
_02087884:
	ldr r0, _02087A0C ; =0x00000806
	bl FUN_020054C8
	b _0208789A
_0208788C:
	ldr r0, _02087A10 ; =0x000007AA
	bl FUN_020054C8
	b _0208789A
_02087894:
	ldr r0, _02087A14 ; =0x00000815
	bl FUN_020054C8
_0208789A:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0xa0
	bge _020878A6
	b _02087A06
_020878A6:
	mov r3, #0x0
	str r3, [r4, #0x60]
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _02087A18 ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	bl FUN_02020354
	mov r1, #0x1
	bl FUN_0201E28C
	add r5, r0, #0x0
	mov r3, #0x0
	mov r6, #0x1
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _02087A18 ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	lsl r6, r5
	eor r2, r6
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	lsr r2, r2, #0x10
	bl FUN_02003210
	ldr r0, _02087A18 ; =0x0000FFFF
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E68
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_02087902:
	add r1, sp, #0xc
	ldr r0, [r4, #0x70]
	mov r5, #0x0
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	add r1, r5, #0x0
	ldrsh r2, [r0, r1]
	add r0, r1, #0x0
	sub r0, #0x30
	cmp r2, r0
	ble _02087928
	ldr r0, [r4, #0x70]
	sub r2, r1, #0x4
	bl FUN_0200C82C
	b _0208792A
_02087928:
	add r5, r5, #0x1
_0208792A:
	add r1, sp, #0xc
	ldr r0, [r4, #0x74]
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, #0xc0
	bge _0208794A
	ldr r0, [r4, #0x74]
	mov r2, #0x4
	bl FUN_0200C82C
	b _0208794C
_0208794A:
	add r5, r5, #0x1
_0208794C:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087A06
	cmp r5, #0x2
	bne _02087A06
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087A06
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02086F98
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_0201E6E4
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x70]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x74]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_02087994:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0x19
	blt _02087A06
	mov r2, #0x0
	ldr r0, _02087A18 ; =0x0000FFFF
	str r2, [r4, #0x60]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E68
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _02087A18 ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _02087A18 ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_02003210
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_020879E0:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087A06
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087A06
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_020879FC:
	mov r0, #0x0
	str r0, [r4, #0x64]
	add sp, #0x10
	str r0, [r4, #0x60]
	pop {r4-r6, pc}
_02087A06:
	mov r0, #0x1
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02087A0C: .word 0x00000806
_02087A10: .word 0x000007AA
_02087A14: .word 0x00000815
_02087A18: .word 0x0000FFFF

	thumb_func_start FUN_02087A1C
FUN_02087A1C: ; 0x02087A1C
	ldr r3, _02087A34 ; =0x020FD13C
	mov r2, #0x0
_02087A20:
	ldrb r1, [r3, #0x0]
	cmp r0, r1
	beq _02087A2E
	add r2, r2, #0x1
	add r3, r3, #0x1
	cmp r2, #0x6
	blt _02087A20
_02087A2E:
	add r0, r2, #0x0
	bx lr
	nop
_02087A34: .word 0x020FD13C

	thumb_func_start FUN_02087A38
FUN_02087A38: ; 0x02087A38
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x6
	blt _02087A44
	bl ErrorHandling
_02087A44:
	ldr r0, _02087A4C ; =0x020FD13C
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_02087A4C: .word 0x020FD13C

	thumb_func_start FUN_02087A50
FUN_02087A50: ; 0x02087A50
	ldr r3, _02087A68 ; =0x020FD120
	mov r2, #0x0
_02087A54:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	beq _02087A62
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0xe
	blt _02087A54
_02087A62:
	add r0, r2, #0x0
	bx lr
	nop
_02087A68: .word 0x020FD120

	thumb_func_start FUN_02087A6C
FUN_02087A6C: ; 0x02087A6C
	push {r3, lr}
	mov r1, #0x18
	bl FUN_02016998
	add r3, r0, #0x0
	mov r2, #0x18
	mov r1, #0x0
_02087A7A:
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _02087A7A
	pop {r3, pc}

	thumb_func_start FUN_02087A84
FUN_02087A84: ; 0x02087A84
	push {r4, lr}
	add r4, r0, #0x0
	bne _02087A8E
	bl ErrorHandling
_02087A8E:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02087A98
FUN_02087A98: ; 0x02087A98
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _02087AA8
	bl ErrorHandling
_02087AA8:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02087AB2
	bl ErrorHandling
_02087AB2:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02087ABC
	bl ErrorHandling
_02087ABC:
	add r0, r4, #0x0
	bl FUN_02087C18
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02087C2C
	str r0, [r5, #0x4]
	cmp r6, #0x0
	bne _02087AEE
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r0, #0x8
	add r1, #0xc
	add r2, r4, #0x0
	bl FUN_02087C40
	add r0, r5, #0x0
	add r5, #0x14
	add r0, #0x10
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02087CA0
	pop {r4-r6, pc}
_02087AEE:
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r0, #0x8
	add r1, #0xc
	add r2, r4, #0x0
	bl FUN_02087C70
	add r0, r5, #0x0
	add r5, #0x14
	add r0, #0x10
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02087CD0
	pop {r4-r6, pc}

	thumb_func_start FUN_02087B0C
FUN_02087B0C: ; 0x02087B0C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02087B1A
	bl ErrorHandling
_02087B1A:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	bne _02087B24
	bl ErrorHandling
_02087B24:
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	ldr r0, [r4, #0xc]
	bl FUN_02016A18
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	ldr r0, [r4, #0x14]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	str r0, [r4, #0x8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start FUN_02087B58
FUN_02087B58: ; 0x02087B58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087B66
	bl ErrorHandling
_02087B66:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _02087B70
	bl ErrorHandling
_02087B70:
	ldr r1, [r5, #0x0]
	lsl r0, r4, #0x2
	ldr r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087B78
FUN_02087B78: ; 0x02087B78
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087B86
	bl ErrorHandling
_02087B86:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02087B90
	bl ErrorHandling
_02087B90:
	ldr r1, [r5, #0x4]
	lsl r0, r4, #0x2
	ldr r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087B98
FUN_02087B98: ; 0x02087B98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087BA6
	bl ErrorHandling
_02087BA6:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _02087BB0
	bl ErrorHandling
_02087BB0:
	ldr r1, [r5, #0x8]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087BB8
FUN_02087BB8: ; 0x02087BB8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087BC6
	bl ErrorHandling
_02087BC6:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	bne _02087BD0
	bl ErrorHandling
_02087BD0:
	ldr r1, [r5, #0xc]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087BD8
FUN_02087BD8: ; 0x02087BD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087BE6
	bl ErrorHandling
_02087BE6:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _02087BF0
	bl ErrorHandling
_02087BF0:
	ldr r1, [r5, #0x10]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087BF8
FUN_02087BF8: ; 0x02087BF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087C06
	bl ErrorHandling
_02087C06:
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	bne _02087C10
	bl ErrorHandling
_02087C10:
	ldr r1, [r5, #0x14]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087C18
FUN_02087C18: ; 0x02087C18
	push {r3, lr}
	mov r1, #0x0
	add r3, r0, #0x0
	mov r0, #0x4b
	add r2, r1, #0x0
	str r1, [sp, #0x0]
	bl FUN_02006C98
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02087C2C
FUN_02087C2C: ; 0x02087C2C
	push {r3, lr}
	add r3, r0, #0x0
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x1
	str r2, [sp, #0x0]
	bl FUN_02006C98
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02087C40
FUN_02087C40: ; 0x02087C40
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x9
	add r3, r6, #0x0
	bl FUN_02006C98
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0xa
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl FUN_02006C98
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087C70
FUN_02087C70: ; 0x02087C70
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x7
	add r3, r6, #0x0
	bl FUN_02006C98
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x8
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl FUN_02006C98
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087CA0
FUN_02087CA0: ; 0x02087CA0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x5
	add r3, r6, #0x0
	bl FUN_02006C98
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x6
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl FUN_02006C98
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087CD0
FUN_02087CD0: ; 0x02087CD0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x3
	add r3, r6, #0x0
	bl FUN_02006C98
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x4
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl FUN_02006C98
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087D00
FUN_02087D00: ; 0x02087D00
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x0
	mov r1, #0xcf
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0xcf
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r7, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl FUN_02028048
	str r0, [r7, #0x8]
	add r0, r4, #0x0
	bl FUN_020238F4
	str r0, [r7, #0xc]
	add r0, r4, #0x0
	bl FUN_0206BB1C
	str r0, [r7, #0x10]
	add r0, r4, #0x0
	bl FUN_0206F158
	str r0, [r7, #0x14]
	add r0, r4, #0x0
	bl LoadPlayerDataAddress
	str r0, [r7, #0x18]
	add r0, r5, #0x0
	bl FUN_02027E5C
	add r4, r0, #0x0
	mov r0, #0x1
	mov r1, #0x20
	add r2, r5, #0x0
	bl FUN_0200AA90
	str r0, [sp, #0x4]
	mov r6, #0x0
_02087D60:
	ldr r0, [r7, #0x8]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02028174
	add r0, r4, #0x0
	bl FUN_02027E34
	cmp r0, #0x0
	beq _02087DEE
	add r0, r4, #0x0
	add r1, sp, #0x8
	bl FUN_02027FBC
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	add r1, #0x1c
	lsl r0, r0, #0x3
	add r5, r1, r0
	strb r6, [r1, r0]
	add r0, r4, #0x0
	bl FUN_02027FDC
	strb r0, [r5, #0x1]
	add r0, sp, #0x8
	ldrb r1, [r0, #0x0]
	mov r2, #0x1
	strb r1, [r5, #0x2]
	ldrb r0, [r0, #0x6]
	mov r1, #0x0
	strb r0, [r5, #0x3]
	add r0, sp, #0x8
_02087DA0:
	add r3, r0, r1
	ldrb r3, [r3, #0x1]
	cmp r3, #0x0
	beq _02087DAE
	ldrb r3, [r5, #0x4]
	orr r3, r2
	strb r3, [r5, #0x4]
_02087DAE:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsl r2, r2, #0x19
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	cmp r1, #0x5
	blo _02087DA0
	ldrb r1, [r5, #0x4]
	mov r0, #0x20
	orr r0, r1
	strb r0, [r5, #0x4]
	ldrb r2, [r5, #0x4]
	mov r1, #0x80
	add r0, r2, #0x0
	bic r0, r1
	lsl r1, r2, #0x1a
	lsr r1, r1, #0x1f
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r5, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	strb r0, [r5, #0x5]
	mov r0, #0xff
	strb r0, [r5, #0x6]
	ldrb r0, [r5, #0x6]
	strb r0, [r5, #0x7]
_02087DEE:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x64
	blo _02087D60
	ldr r0, [sp, #0x4]
	bl FUN_0200AB18
	add r0, r4, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x0]
	strb r0, [r7, #0x0]
	mov r0, #0x5
	strb r0, [r7, #0x3]
	add r0, r7, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02087E14
FUN_02087E14: ; 0x02087E14
	ldr r3, _02087E18 ; =FUN_02016A18
	bx r3
	.balign 4
_02087E18: .word FUN_02016A18

	thumb_func_start FUN_02087E1C
FUN_02087E1C: ; 0x02087E1C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02087E3C
	bl FUN_02006290
	cmp r0, #0x0
	beq _02087E3C
	ldr r0, [r4, #0x0]
	bl FUN_02006260
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_02087E3C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02087E40
FUN_02087E40: ; 0x02087E40
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_0200628C
	mov r2, #0x1
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x2c
	lsl r2, r2, #0xc
	bl FUN_0201681C
	add r0, r4, #0x0
	mov r1, #0x18
	mov r2, #0x2c
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x18
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x2c
	str r0, [r4, #0x0]
	str r5, [r4, #0xc]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02087E74
FUN_02087E74: ; 0x02087E74
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02006278
	ldr r1, [r4, #0x0]
	cmp r1, #0x8
	bhi _02087EE4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02087E8E: ; jump table (using 16-bit offset)
	.short _02087EA0 - _02087E8E - 2; case 0
	.short _02087EA8 - _02087E8E - 2; case 1
	.short _02087EB0 - _02087E8E - 2; case 2
	.short _02087EB8 - _02087E8E - 2; case 3
	.short _02087EC0 - _02087E8E - 2; case 4
	.short _02087EC8 - _02087E8E - 2; case 5
	.short _02087ED0 - _02087E8E - 2; case 6
	.short _02087ED8 - _02087E8E - 2; case 7
	.short _02087EE0 - _02087E8E - 2; case 8
_02087EA0:
	bl FUN_02087F50
	str r0, [r4, #0x0]
	b _02087EE4
_02087EA8:
	bl FUN_02087F68
	str r0, [r4, #0x0]
	b _02087EE4
_02087EB0:
	bl FUN_02087FD4
	str r0, [r4, #0x0]
	b _02087EE4
_02087EB8:
	bl FUN_0208805C
	str r0, [r4, #0x0]
	b _02087EE4
_02087EC0:
	bl FUN_020880A0
	str r0, [r4, #0x0]
	b _02087EE4
_02087EC8:
	bl FUN_0208810C
	str r0, [r4, #0x0]
	b _02087EE4
_02087ED0:
	bl FUN_02088130
	str r0, [r4, #0x0]
	b _02087EE4
_02087ED8:
	bl FUN_020881AC
	str r0, [r4, #0x0]
	b _02087EE4
_02087EE0:
	mov r0, #0x1
	pop {r4, pc}
_02087EE4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02087EE8
FUN_02087EE8: ; 0x02087EE8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	bl FUN_02087F08
	add r0, r5, #0x0
	bl FUN_0200627C
	ldr r0, [r4, #0x0]
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02087F08
FUN_02087F08: ; 0x02087F08
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0xc]
	mov r0, #0x0
	ldrb r1, [r2, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	bls _02087F42
	mov r6, #0x1
_02087F1A:
	add r3, r2, #0x0
	add r3, #0x1c
	lsl r1, r4, #0x3
	add r1, r3, r1
	ldrb r3, [r1, #0x4]
	lsl r3, r3, #0x19
	lsr r3, r3, #0x1f
	beq _02087F34
	ldrb r1, [r1, #0x0]
	ldr r0, [r2, #0x8]
	bl FUN_020280B8
	add r0, r6, #0x0
_02087F34:
	add r1, r4, #0x1
	lsl r1, r1, #0x18
	ldr r2, [r5, #0xc]
	lsr r4, r1, #0x18
	ldrb r1, [r2, #0x0]
	cmp r4, r1
	blo _02087F1A
_02087F42:
	cmp r0, #0x0
	beq _02087F4C
	ldr r0, [r2, #0x8]
	bl FUN_020280F4
_02087F4C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02087F50
FUN_02087F50: ; 0x02087F50
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02087F64 ; =0x020FD15C
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x0]
	bl FUN_02006234
	str r0, [r4, #0x14]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02087F64: .word 0x020FD15C

	thumb_func_start FUN_02087F68
FUN_02087F68: ; 0x02087F68
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _02087F7A
	mov r0, #0x1
	pop {r3-r5, pc}
_02087F7A:
	ldr r1, [r5, #0xc]
	ldrb r0, [r1, #0x2]
	cmp r0, #0x0
	bne _02087F86
	mov r0, #0x8
	pop {r3-r5, pc}
_02087F86:
	mov r0, #0x0
	strb r0, [r1, #0x2]
	ldr r0, [r5, #0x0]
	mov r1, #0x40
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [r5, #0xc]
	mov r1, #0x0
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x14]
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	ldr r0, [r0, #0x18]
	str r0, [r4, #0xc]
	ldr r0, _02087FD0 ; =0x020F96DC
	ldr r2, [r5, #0x0]
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x2
	pop {r3-r5, pc}
	.balign 4
_02087FD0: .word 0x020F96DC

	thumb_func_start FUN_02087FD4
FUN_02087FD4: ; 0x02087FD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _02087FE6
	mov r0, #0x2
	pop {r3-r7, pc}
_02087FE6:
	ldr r7, [r5, #0x10]
	add r0, r7, #0x0
	add r0, #0x22
	ldrb r6, [r0, #0x0]
	strb r6, [r5, #0x8]
	ldr r0, [r5, #0x10]
	bl FUN_02016A18
	cmp r6, #0x7
	bne _02087FFE
	mov r0, #0x0
	pop {r3-r7, pc}
_02087FFE:
	ldr r0, [r5, #0x0]
	mov r1, #0x30
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	strb r6, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9AC
	strb r0, [r4, #0x13]
	mov r1, #0x0
	strh r1, [r4, #0x18]
	mov r0, #0x3
	strb r0, [r4, #0x12]
	mov r0, #0x1
	str r0, [r4, #0x2c]
	str r1, [r4, #0x28]
	ldr r1, _02088054 ; =0x020FD158
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r1, [r5, #0xc]
	add r0, r4, #0x0
	ldr r1, [r1, #0xc]
	bl FUN_0207C2A4
	ldr r0, _02088058 ; =0x020FA6E8
	ldr r2, [r5, #0x0]
	add r1, r7, #0x0
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x3
	pop {r3-r7, pc}
	.balign 4
_02088054: .word 0x020FD158
_02088058: .word 0x020FA6E8

	thumb_func_start FUN_0208805C
FUN_0208805C: ; 0x0208805C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _0208806E
	mov r0, #0x3
	pop {r3-r5, pc}
_0208806E:
	ldr r0, [r5, #0x10]
	ldrb r4, [r0, #0x17]
	ldrb r0, [r0, #0x14]
	strb r0, [r5, #0x8]
	ldr r0, [r5, #0x10]
	bl FUN_02016A18
	cmp r4, #0x1
	bne _02088084
	mov r0, #0x0
	pop {r3-r5, pc}
_02088084:
	ldr r0, [r5, #0xc]
	add r3, r0, #0x0
	ldrb r0, [r0, #0x1]
	add r3, #0x20
	lsl r2, r0, #0x3
	ldrb r1, [r3, r2]
	mov r0, #0x40
	orr r0, r1
	strb r0, [r3, r2]
	ldr r0, [r5, #0xc]
	mov r1, #0x1
	strb r1, [r0, #0x2]
	mov r0, #0x4
	pop {r3-r5, pc}

	thumb_func_start FUN_020880A0
FUN_020880A0: ; 0x020880A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0xc
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0xc
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r1, [r5, #0xc]
	ldrb r0, [r1, #0x1]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldrb r0, [r0, #0x1e]
	strh r0, [r4, #0x8]
	ldr r2, [r5, #0xc]
	ldrb r1, [r2, #0x1]
	ldr r0, [r2, #0x8]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldrb r1, [r1, #0x1c]
	ldr r2, [r5, #0x0]
	bl FUN_02028190
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	ldrb r1, [r5, #0x8]
	ldr r0, [r0, #0x10]
	bl FUN_0206B9B0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	bl FUN_02024FF4
	strb r0, [r4, #0xa]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	bl FUN_02025084
	strb r0, [r4, #0xb]
	ldr r0, _02088108 ; =0x020FD16C
	ldr r2, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x5
	pop {r3-r5, pc}
	.balign 4
_02088108: .word 0x020FD16C

	thumb_func_start FUN_0208810C
FUN_0208810C: ; 0x0208810C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _0208811E
	mov r0, #0x5
	pop {r4, pc}
_0208811E:
	ldr r4, [r4, #0x10]
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x6
	pop {r4, pc}

	thumb_func_start FUN_02088130
FUN_02088130: ; 0x02088130
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x30
	bl FUN_02016998
	ldr r2, [r5, #0xc]
	add r4, r0, #0x0
	ldrb r1, [r2, #0x1]
	ldr r0, [r2, #0x8]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldrb r1, [r1, #0x1c]
	ldr r2, [r5, #0x0]
	bl FUN_02028190
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	ldrb r0, [r5, #0x8]
	strb r0, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9AC
	strb r0, [r4, #0x13]
	mov r1, #0x0
	strh r1, [r4, #0x18]
	mov r0, #0x4
	strb r0, [r4, #0x12]
	str r6, [r4, #0x24]
	mov r0, #0x1
	str r0, [r4, #0x2c]
	str r1, [r4, #0x28]
	ldr r1, _020881A4 ; =0x020FD154
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r1, [r5, #0xc]
	add r0, r4, #0x0
	ldr r1, [r1, #0xc]
	bl FUN_0207C2A4
	ldr r0, _020881A8 ; =0x020FA6E8
	ldr r2, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x7
	pop {r4-r6, pc}
	nop
_020881A4: .word 0x020FD154
_020881A8: .word 0x020FA6E8

	thumb_func_start FUN_020881AC
FUN_020881AC: ; 0x020881AC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _020881BE
	mov r0, #0x7
	pop {r4, pc}
_020881BE:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x24]
	bl FUN_02016A18
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020881D0
FUN_020881D0: ; 0x020881D0
	push {r3-r5, lr}
	sub sp, #0x8
	lsl r2, r1, #0x1
	ldr r1, _02088214 ; =0x020FD17C
	ldrb r4, [r1, r2]
	ldr r1, _02088218 ; =0x020FD17D
	ldrb r5, [r1, r2]
	cmp r4, #0x5
	bne _020881E8
	add sp, #0x8
	mov r0, #0x2
	pop {r3-r5, pc}
_020881E8:
	add r1, sp, #0x0
	bl FUN_02027FBC
	add r0, r4, #0x1
	add r2, sp, #0x0
	ldrb r1, [r2, r0]
	add r0, r5, #0x1
	ldrb r0, [r2, r0]
	cmp r1, r0
	bne _02088202
	add sp, #0x8
	mov r0, #0x2
	pop {r3-r5, pc}
_02088202:
	cmp r1, r0
	bls _0208820C
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0208820C:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_02088214: .word 0x020FD17C
_02088218: .word 0x020FD17D

	thumb_func_start FUN_0208821C
FUN_0208821C: ; 0x0208821C
	push {r3-r7, lr}
	sub sp, #0x30
	add r6, r1, #0x0
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02068854
	lsl r1, r0, #0x1
	ldr r0, _02088310 ; =0x020FD17C
	ldrb r0, [r0, r1]
	str r0, [sp, #0x4]
	ldr r0, _02088314 ; =0x020FD17D
	ldrb r0, [r0, r1]
	add r1, sp, #0x10
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02027FBC
	mov r4, #0x0
	add r7, r4, #0x0
	add r5, sp, #0x18
_02088246:
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x13
	add r2, r7, #0x0
	bl FUN_020671BC
	lsl r1, r4, #0x2
	str r0, [r5, r1]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _02088246
	add r4, sp, #0x8
	mov r1, #0x0
	mov r3, #0x1
	add r0, sp, #0x10
	add r4, #0x1
_0208826A:
	ldrb r5, [r0, r3]
	add r2, r1, #0x0
	add r1, r1, #0x1
	strb r5, [r4, r2]
	add r2, r3, #0x1
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r3, r2, #0x18
	lsr r1, r1, #0x18
	cmp r3, #0x6
	bls _0208826A
	ldr r0, [sp, #0x4]
	cmp r0, #0x5
	beq _020882B8
	ldrb r0, [r4, r0]
	bl _ffltu
	add r1, r0, #0x0
	ldr r0, _02088318 ; =0x3F8CCCCD
	bl _fmul
	bl _ffixu
	ldr r1, [sp, #0x4]
	strb r0, [r4, r1]
	add r4, sp, #0x8
	ldr r0, [sp, #0x0]
	add r4, #0x1
	ldrb r0, [r4, r0]
	bl _ffltu
	add r1, r0, #0x0
	ldr r0, _0208831C ; =0x3F666666
	bl _fmul
	bl _ffixu
	ldr r1, [sp, #0x0]
	strb r0, [r4, r1]
_020882B8:
	add r7, sp, #0x8
	mov r5, #0x0
	add r4, sp, #0x18
	add r7, #0x1
_020882C0:
	lsl r2, r5, #0x2
	ldrb r0, [r7, r5]
	ldr r1, [r4, r2]
	add r0, r1, r0
	str r0, [r4, r2]
	ldr r0, [r4, r2]
	cmp r0, #0xff
	ble _020882D4
	mov r0, #0xff
	str r0, [r4, r2]
_020882D4:
	add r1, r5, #0x0
	add r0, r6, #0x0
	add r1, #0x13
	add r2, r4, r2
	bl FUN_02067830
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x6
	blo _020882C0
	add r0, r6, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	ldrb r0, [r1, #0x0]
	cmp r0, #0xff
	bhs _0208830C
	add r0, r0, #0x1
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x9
	add r2, sp, #0x8
	bl FUN_02067830
_0208830C:
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02088310: .word 0x020FD17C
_02088314: .word 0x020FD17D
_02088318: .word 0x3F8CCCCD
_0208831C: .word 0x3F666666

	thumb_func_start FUN_02088320
FUN_02088320: ; 0x02088320
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x59
	lsl r1, r1, #0x2
	add r6, r0, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_02016998
	mov r2, #0x59
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl MI_CpuFill8
	str r6, [r4, #0x0]
	cmp r5, #0x10
	bls _0208834A
	mov r0, #0x10
	strh r0, [r4, #0xa]
	b _0208834C
_0208834A:
	strh r7, [r4, #0xa]
_0208834C:
	strh r5, [r4, #0xc]
	ldr r0, [sp, #0x0]
	strh r0, [r4, #0xe]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	bl FUN_0208837C
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02088360
FUN_02088360: ; 0x02088360
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0208843C
	mov r2, #0x59
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_0208837C
FUN_0208837C: ; 0x0208837C
	push {r4-r7, lr}
	sub sp, #0xc
	ldr r1, _02088438 ; =0x020FD1C0
	str r0, [sp, #0x0]
	ldrb r2, [r1, #0x0]
	add r0, sp, #0x8
	strb r2, [r0, #0x0]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x2]
	ldrb r1, [r1, #0x3]
	strb r2, [r0, #0x2]
	strb r1, [r0, #0x3]
	ldr r0, [sp, #0x0]
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x0]
	ldrh r0, [r0, #0xc]
	ldr r2, [r2, #0x0]
	add r1, #0x14
	bl FUN_02008C9C
	ldr r1, [sp, #0x0]
	mov r6, #0x15
	str r0, [r1, #0x10]
	add r0, r1, #0x0
	ldrh r1, [r0, #0xa]
	add r0, sp, #0x8
	ldr r5, [sp, #0x0]
	strb r1, [r0, #0x1]
	mov r0, #0x0
	str r0, [sp, #0x4]
	add r7, sp, #0x8
	add r4, r0, #0x0
	lsl r6, r6, #0x4
_020883C0:
	ldr r2, [sp, #0x0]
	ldrb r0, [r7, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [r2, #0x0]
	bl FUN_02008DEC
	mov r1, #0x5
	lsl r1, r1, #0x6
	str r0, [r5, r1]
	ldr r1, [sp, #0x0]
	ldrb r0, [r7, #0x0]
	ldr r1, [r1, #0x0]
	bl FUN_02009424
	mov r1, #0x15
	lsl r1, r1, #0x4
	str r0, [r5, r1]
	mov r0, #0x15
	lsl r0, r0, #0x4
	ldr r3, [r5, r0]
	mov r1, #0x0
	ldr r0, [r3, #0x4]
	cmp r0, #0x0
	bls _02088402
	add r2, r1, #0x0
_020883F2:
	ldr r0, [r3, #0x0]
	add r1, r1, #0x1
	str r4, [r0, r2]
	ldr r3, [r5, r6]
	add r2, r2, #0x4
	ldr r0, [r3, #0x4]
	cmp r1, r0
	blo _020883F2
_02088402:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r0, r0, #0x1
	add r5, r5, #0x4
	str r0, [sp, #0x4]
	cmp r0, #0x4
	blo _020883C0
	ldr r0, [sp, #0x0]
	bl FUN_020886CC
	ldr r0, [sp, #0x0]
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	bl FUN_02016998
	mov r2, #0x16
	ldr r1, [sp, #0x0]
	lsl r2, r2, #0x4
	str r0, [r1, r2]
	add r0, r1, #0x0
	ldr r0, [r0, r2]
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02088438: .word 0x020FD1C0

	thumb_func_start FUN_0208843C
FUN_0208843C: ; 0x0208843C
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x16
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_02016A18
	ldr r0, [r5, #0x10]
	bl FUN_0201FD58
	mov r0, #0x15
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	bl FUN_02009C30
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_02009E28
	mov r7, #0x15
	lsl r7, r7, #0x4
	add r6, r7, #0x0
	mov r4, #0x0
	sub r6, #0x10
_0208846E:
	ldr r0, [r5, r7]
	bl FUN_02009448
	ldr r0, [r5, r6]
	bl FUN_02008E2C
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blo _0208846E
	pop {r3-r7, pc}

	thumb_func_start FUN_02088484
FUN_02088484: ; 0x02088484
	ldr r3, _0208848C ; =FUN_0201FDEC
	ldr r0, [r0, #0x10]
	bx r3
	nop
_0208848C: .word FUN_0201FDEC

	thumb_func_start FUN_02088490
FUN_02088490: ; 0x02088490
	push {r3-r7, lr}
	sub sp, #0x70
	str r1, [sp, #0x2c]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r5, r0, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x30]
	bl FUN_020887CC
	str r0, [sp, #0x3c]
	cmp r0, #0x0
	bge _020884B4
	bl ErrorHandling
	add sp, #0x70
	mov r0, #0x0
	pop {r3-r7, pc}
_020884B4:
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	bl FUN_02016998
	str r0, [sp, #0x38]
	mov r1, #0x0
	mov r2, #0x8
	bl MI_CpuFill8
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #0x38]
	strh r1, [r0, #0x0]
	ldr r0, [sp, #0x94]
	cmp r0, #0x0
	bne _020884D6
	mov r6, #0x1
	b _020884D8
_020884D6:
	mov r6, #0x2
_020884D8:
	ldr r0, [sp, #0x3c]
	mov r1, #0x55
	lsl r1, r1, #0x2
	lsl r4, r0, #0x2
	ldr r0, [r5, r1]
	ldr r3, [sp, #0x2c]
	ldr r0, [r0, #0x0]
	sub r1, #0x10
	ldr r0, [r0, r4]
	mov r2, #0x58
	str r0, [sp, #0x34]
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	add r3, r3, #0x3
	str r0, [sp, #0x4]
	ldr r0, [r5, r1]
	ldr r1, [sp, #0x34]
	bl FUN_02009168
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02009DE0
	ldr r0, [r5, #0x0]
	mov r1, #0x10
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	bl FUN_02016998
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x0]
	mov r1, #0x24
	bl FUN_02016998
	ldr r1, [r4, #0x8]
	mov r3, #0xe
	str r0, [r1, #0x0]
	ldr r0, [r4, #0x8]
	lsl r3, r3, #0xc
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x0
	str r3, [sp, #0x0]
	mvn r0, r0
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r0, sp, #0x78
	ldrb r0, [r0, #0x14]
	str r0, [sp, #0x10]
	mov r0, #0x5
	lsl r0, r0, #0x6
	ldr r2, [r5, r0]
	str r2, [sp, #0x14]
	add r2, r0, #0x4
	ldr r2, [r5, r2]
	str r2, [sp, #0x18]
	add r2, r0, #0x0
	add r2, #0x8
	ldr r2, [r5, r2]
	add r0, #0xc
	str r2, [sp, #0x1c]
	ldr r0, [r5, r0]
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	str r1, [sp, #0x28]
	ldr r2, [sp, #0x3c]
	ldr r0, [r4, #0x4]
	add r1, r3, #0x0
	add r2, r2, r3
	bl FUN_02008AA4
	ldr r0, [r5, #0x10]
	cmp r7, #0x0
	str r0, [sp, #0x40]
	ldr r0, [r4, #0x4]
	str r0, [sp, #0x44]
	beq _02088596
	lsl r0, r7, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _020885A4
_02088596:
	lsl r0, r7, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_020885A4:
	bl _ffix
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	beq _020885C2
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _020885D0
_020885C2:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_020885D0:
	bl _ffix
	str r0, [sp, #0x4c]
	add r0, sp, #0x78
	ldrh r0, [r0, #0x10]
	cmp r0, #0x0
	beq _020885F0
	lsl r0, r0, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _020885FE
_020885F0:
	lsl r0, r0, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_020885FE:
	bl _ffix
	str r0, [sp, #0x50]
	cmp r6, #0x2
	bne _02088612
	mov r0, #0x3
	ldr r1, [sp, #0x4c]
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r0, [sp, #0x4c]
_02088612:
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x54]
	str r0, [sp, #0x58]
	str r0, [sp, #0x5c]
	mov r1, #0x0
	add r0, sp, #0x40
	strh r1, [r0, #0x20]
	add r0, sp, #0x78
	ldrb r0, [r0, #0x18]
	str r6, [sp, #0x68]
	str r0, [sp, #0x64]
	ldr r0, [r5, #0x0]
	str r0, [sp, #0x6c]
	add r0, sp, #0x40
	bl FUN_0201FE94
	str r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02088652
	mov r1, #0x0
	bl FUN_02020130
	ldr r0, [sp, #0x34]
	add r1, r6, #0x0
	bl FUN_02009E88
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02020248
	b _02088656
_02088652:
	bl ErrorHandling
_02088656:
	ldr r0, [sp, #0x38]
	str r4, [r0, #0x4]
	add sp, #0x70
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02088660
FUN_02088660: ; 0x02088660
	push {r4, lr}
	sub sp, #0x8
	add r3, r2, #0x0
	mov r2, #0x55
	lsl r2, r2, #0x2
	ldr r4, [r0, r2]
	ldrh r1, [r1, #0x0]
	ldr r4, [r4, #0x0]
	sub r2, #0x10
	lsl r1, r1, #0x2
	ldr r4, [r4, r1]
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r1, [r0, #0x0]
	add r3, r3, #0x3
	str r1, [sp, #0x4]
	ldr r0, [r0, r2]
	add r1, r4, #0x0
	mov r2, #0x58
	bl FUN_02009168
	add r0, r4, #0x0
	bl FUN_02009DE0
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02088694
FUN_02088694: ; 0x02088694
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	bl FUN_0200C3DC
	mov r1, #0x16
	ldrh r2, [r4, #0x0]
	lsl r1, r1, #0x4
	ldr r3, [r5, r1]
	mov r0, #0x0
	lsl r2, r2, #0x2
	strb r0, [r3, r2]
	ldrh r2, [r4, #0x0]
	ldr r3, [r5, r1]
	lsl r2, r2, #0x2
	add r2, r3, r2
	strh r0, [r2, #0x2]
	ldr r2, [r5, r1]
	ldrh r1, [r4, #0x0]
	lsl r1, r1, #0x2
	add r1, r2, r1
	strb r0, [r1, #0x1]
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020886CC
FUN_020886CC: ; 0x020886CC
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	mov r0, #0x15
	lsl r0, r0, #0x4
	ldr r4, [r5, r0]
	mov r1, #0xe
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	ldrh r1, [r5, #0xe]
	mov r2, #0x0
	sub r0, #0x10
	str r1, [sp, #0x4]
	ldr r1, [r5, #0x0]
	add r3, r2, #0x0
	str r1, [sp, #0x8]
	ldr r0, [r5, r0]
	mov r1, #0x58
	bl FUN_02008F34
	ldr r1, [r4, #0x0]
	str r0, [r1, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02088704
	bl ErrorHandling
_02088704:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02088728
	cmp r0, #0x1
	beq _02088714
	cmp r0, #0x2
	beq _0208871E
	b _02088728
_02088714:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02009B04
	b _02088730
_0208871E:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02009B78
	b _02088730
_02088728:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02009A50
_02088730:
	mov r4, #0x0
	add r6, r5, #0x0
_02088734:
	mov r0, #0x56
	lsl r0, r0, #0x2
	ldr r7, [r6, r0]
	mov r0, #0xe
	lsl r0, r0, #0xc
	str r0, [sp, #0x0]
	add r0, r4, #0x2
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	mov r1, #0x58
	str r0, [sp, #0x8]
	mov r0, #0x52
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r2, r4, #0x1
	mov r3, #0x0
	bl FUN_020090AC
	ldr r1, [r7, #0x0]
	str r0, [r1, #0x0]
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02088768
	bl ErrorHandling
_02088768:
	add r4, r4, #0x1
	add r6, r6, #0x4
	cmp r4, #0x2
	blt _02088734
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldr r6, [r5, r0]
	ldrh r0, [r5, #0xa]
	mov r7, #0x0
	cmp r0, #0x0
	ble _020887C6
	add r4, r7, #0x0
_02088780:
	mov r0, #0xe
	lsl r0, r0, #0xc
	add r0, r7, r0
	str r0, [sp, #0x0]
	ldrh r0, [r5, #0xe]
	mov r1, #0x58
	mov r2, #0x4
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	mov r3, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x51
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_02008FEC
	ldr r1, [r6, #0x0]
	str r0, [r1, r4]
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	bne _020887B4
	bl ErrorHandling
_020887B4:
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02009CF0
	ldrh r0, [r5, #0xa]
	add r7, r7, #0x1
	add r4, r4, #0x4
	cmp r7, r0
	blt _02088780
_020887C6:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020887CC
FUN_020887CC: ; 0x020887CC
	push {r3-r6}
	ldrh r5, [r0, #0xa]
	mov r3, #0x0
	cmp r5, #0x0
	bls _0208880A
	mov r2, #0x16
	lsl r2, r2, #0x4
	ldr r4, [r0, r2]
_020887DC:
	lsl r2, r3, #0x2
	ldrb r6, [r4, r2]
	cmp r6, #0x0
	bne _02088800
	add r4, r4, r2
	strh r3, [r4, #0x2]
	mov r4, #0x16
	lsl r4, r4, #0x4
	ldr r5, [r0, r4]
	add r5, r5, r2
	strb r1, [r5, #0x1]
	ldr r0, [r0, r4]
	mov r1, #0x1
	strb r1, [r0, r2]
	lsl r0, r3, #0x10
	asr r0, r0, #0x10
	pop {r3-r6}
	bx lr
_02088800:
	add r2, r3, #0x1
	lsl r2, r2, #0x10
	lsr r3, r2, #0x10
	cmp r3, r5
	blo _020887DC
_0208880A:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02088814
FUN_02088814: ; 0x02088814
	mov r0, #0x3
	bx lr

	thumb_func_start FUN_02088818
FUN_02088818: ; 0x02088818
	bx lr
	.balign 4

	thumb_func_start FUN_0208881C
FUN_0208881C: ; 0x0208881C
	ldr r3, _02088828 ; =FUN_0202D8D0
	add r2, r0, #0x0
	ldr r0, _0208882C ; =0x020FD1C4
	mov r1, #0x6c
	bx r3
	nop
_02088828: .word FUN_0202D8D0
_0208882C: .word 0x020FD1C4

	thumb_func_start FUN_02088830
FUN_02088830: ; 0x02088830
	ldr r0, _02088834 ; =0x0000066C
	bx lr
	.balign 4
_02088834: .word 0x0000066C

	thumb_func_start FUN_02088838
FUN_02088838: ; 0x02088838
	mov r0, #0x2f
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_02088840
FUN_02088840: ; 0x02088840
	mov r0, #0x3f
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02088848
FUN_02088848: ; 0x02088848
	mov r0, #0xa
	bx lr

	thumb_func_start FUN_0208884C
FUN_0208884C: ; 0x0208884C
	mov r0, #0x32
	bx lr

	thumb_func_start FUN_02088850
FUN_02088850: ; 0x02088850
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02088854
FUN_02088854: ; 0x02088854
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02088858
FUN_02088858: ; 0x02088858
	ldr r3, _02088860 ; =HandleLoadOverlay
	ldr r0, _02088864 ; =SDK_OVERLAY_MODULE_04_ID
	mov r1, #0x2
	bx r3
	.balign 4
_02088860: .word HandleLoadOverlay
_02088864: .word SDK_OVERLAY_MODULE_04_ID

	thumb_func_start FUN_02088868
FUN_02088868: ; 0x02088868
	ldr r3, _02088870 ; =UnloadOverlayByID
	ldr r0, _02088874 ; =SDK_OVERLAY_MODULE_04_ID
	bx r3
	nop
_02088870: .word UnloadOverlayByID
_02088874: .word SDK_OVERLAY_MODULE_04_ID

	thumb_func_start FUN_02088878
FUN_02088878: ; 0x02088878
	ldr r3, _02088880 ; =HandleLoadOverlay
	ldr r0, _02088884 ; =SDK_OVERLAY_MODULE_13_ID
	mov r1, #0x2
	bx r3
	.balign 4
_02088880: .word HandleLoadOverlay
_02088884: .word SDK_OVERLAY_MODULE_13_ID

	thumb_func_start FUN_02088888
FUN_02088888: ; 0x02088888
	ldr r3, _02088890 ; =UnloadOverlayByID
	ldr r0, _02088894 ; =SDK_OVERLAY_MODULE_13_ID
	bx r3
	nop
_02088890: .word UnloadOverlayByID
_02088894: .word SDK_OVERLAY_MODULE_13_ID

	thumb_func_start FUN_02088898
FUN_02088898: ; 0x02088898
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02088858
	bl FUN_02088878
	add r0, r4, #0x0
	bl MOD07_02211E60
	bl FUN_02088888
	bl FUN_02088868
	mov r0, #0x0
	bl OS_ResetSystem
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020888BC
FUN_020888BC: ; 0x020888BC
	ldr r3, _020888C4 ; =HandleLoadOverlay
	ldr r0, _020888C8 ; =SDK_OVERLAY_MODULE_79_ID
	mov r1, #0x2
	bx r3
	.balign 4
_020888C4: .word HandleLoadOverlay
_020888C8: .word SDK_OVERLAY_MODULE_79_ID

	thumb_func_start FUN_020888CC
FUN_020888CC: ; 0x020888CC
	ldr r3, _020888D4 ; =UnloadOverlayByID
	ldr r0, _020888D8 ; =SDK_OVERLAY_MODULE_79_ID
	bx r3
	nop
_020888D4: .word UnloadOverlayByID
_020888D8: .word SDK_OVERLAY_MODULE_79_ID

	thumb_func_start FUN_020888DC
FUN_020888DC: ; 0x020888DC
	push {r4, lr}
	mov r2, #0x41
	add r4, r0, #0x0
	mov r0, #0x3
	mov r1, #0x31
	lsl r2, r2, #0xc
	bl FUN_0201681C
	add r0, r4, #0x0
	bl FUN_0200628C
	ldr r0, [r0, #0x8]
	mov r1, #0x31
	bl FUN_02088898
	mov r0, #0x31
	bl FUN_020168D0
	mov r0, #0x0
	bl OS_ResetSystem
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0208890C
FUN_0208890C: ; 0x0208890C
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x20
	add r7, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	str r5, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_02028048
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_020238F4
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_0206F158
	str r0, [r4, #0x14]
	add r0, r5, #0x0
	bl LoadPlayerDataAddress
	str r0, [r4, #0x18]
	str r7, [r4, #0x1c]
	str r6, [r4, #0x4]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02088950
FUN_02088950: ; 0x02088950
	ldr r3, _02088958 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _0208895C ; =0x020FD6E4
	bx r3
	.balign 4
_02088958: .word FUN_020373D4
_0208895C: .word 0x020FD6E4

	thumb_func_start FUN_02088960
FUN_02088960: ; 0x02088960
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020377AC
	add r3, r5, #0x0
	add r3, #0x98
	add r1, r0, #0x0
	ldr r3, [r3, #0x0]
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0208890C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02088950
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0208898C
FUN_0208898C: ; 0x0208898C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020889AC
	bl FUN_02006290
	cmp r0, #0x0
	beq _020889AC
	ldr r0, [r4, #0x0]
	bl FUN_02006260
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_020889AC:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020889B0
FUN_020889B0: ; 0x020889B0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_0200628C
	mov r2, #0x1
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x37
	lsl r2, r2, #0xe
	bl FUN_0201681C
	add r0, r4, #0x0
	mov r1, #0x24
	mov r2, #0x37
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x24
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x37
	str r0, [r4, #0x0]
	str r5, [r4, #0x10]
	ldr r0, [r4, #0x0]
	bl FUN_0206F164
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _020889FA
	ldrh r1, [r4, #0x6]
	mov r0, #0xff
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0x6]
_020889FA:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02088A00
FUN_02088A00: ; 0x02088A00
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02006278
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r5, [r4, #0x0]
	cmp r5, #0x4
	bhi _02088A6A
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02088A24: ; jump table (using 16-bit offset)
	.short _02088A2E - _02088A24 - 2; case 0
	.short _02088A3C - _02088A24 - 2; case 1
	.short _02088A4A - _02088A24 - 2; case 2
	.short _02088A58 - _02088A24 - 2; case 3
	.short _02088A66 - _02088A24 - 2; case 4
_02088A2E:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088AAC
	str r0, [r4, #0x0]
	b _02088A6A
_02088A3C:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088AFC
	str r0, [r4, #0x0]
	b _02088A6A
_02088A4A:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088B28
	str r0, [r4, #0x0]
	b _02088A6A
_02088A58:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088B48
	str r0, [r4, #0x0]
	b _02088A6A
_02088A66:
	mov r0, #0x1
	pop {r4-r6, pc}
_02088A6A:
	ldr r0, [r4, #0x0]
	cmp r5, r0
	beq _02088A74
	mov r0, #0x0
	str r0, [r6, #0x14]
_02088A74:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02088A78
FUN_02088A78: ; 0x02088A78
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r0, [r4, #0xc]
	ldr r6, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x24
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl FUN_0200627C
	add r0, r6, #0x0
	bl FUN_020168D0
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02088AAC
FUN_02088AAC: ; 0x02088AAC
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x5
	bhi _02088AF6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02088AC2: ; jump table (using 16-bit offset)
	.short _02088ACE - _02088AC2 - 2; case 0
	.short _02088AD6 - _02088AC2 - 2; case 1
	.short _02088ADE - _02088AC2 - 2; case 2
	.short _02088AE6 - _02088AC2 - 2; case 3
	.short _02088AEE - _02088AC2 - 2; case 4
	.short _02088AF2 - _02088AC2 - 2; case 5
_02088ACE:
	bl FUN_02088B4C
	str r0, [r4, #0x0]
	b _02088AF6
_02088AD6:
	bl FUN_02088BA8
	str r0, [r4, #0x0]
	b _02088AF6
_02088ADE:
	bl FUN_02088C3C
	str r0, [r4, #0x0]
	b _02088AF6
_02088AE6:
	bl FUN_02088CDC
	str r0, [r4, #0x0]
	b _02088AF6
_02088AEE:
	mov r0, #0x1
	pop {r4, pc}
_02088AF2:
	mov r0, #0x4
	pop {r4, pc}
_02088AF6:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02088AFC
FUN_02088AFC: ; 0x02088AFC
	push {r3-r5, lr}
	sub sp, #0x10
	ldr r5, _02088B24 ; =0x020FD708
	add r3, sp, #0x0
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	ldr r2, [r4, #0x0]
	add r1, r4, #0x0
	bl FUN_02006234
	str r0, [r4, #0x1c]
	mov r0, #0x2
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02088B24: .word 0x020FD708

	thumb_func_start FUN_02088B28
FUN_02088B28: ; 0x02088B28
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_0208898C
	cmp r0, #0x0
	bne _02088B3A
	mov r0, #0x2
	pop {r4, pc}
_02088B3A:
	ldr r0, [r4, #0x20]
	cmp r0, #0x1
	bne _02088B44
	mov r0, #0x0
	pop {r4, pc}
_02088B44:
	mov r0, #0x3
	pop {r4, pc}

	thumb_func_start FUN_02088B48
FUN_02088B48: ; 0x02088B48
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02088B4C
FUN_02088B4C: ; 0x02088B4C
	push {r3-r5, lr}
	sub sp, #0x10
	ldr r3, _02088BA0 ; =0x020FD6F8
	add r2, sp, #0x0
	add r5, r0, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x10]
	ldr r1, _02088BA4 ; =0x020FD6F4
	ldr r0, [r0, #0x14]
	ldr r2, [r5, #0x0]
	bl FUN_0206EFEC
	add r4, r0, #0x0
	ldrh r0, [r5, #0x6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bne _02088B7A
	mov r2, #0x5
	b _02088B7C
_02088B7A:
	mov r2, #0x4
_02088B7C:
	ldr r1, [r5, #0x10]
	lsl r2, r2, #0x18
	ldr r1, [r1, #0xc]
	ldr r3, [r5, #0xc]
	add r0, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_0206E314
	ldr r2, [r5, #0x0]
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FUN_02006234
	str r0, [r5, #0x1c]
	str r4, [r5, #0x18]
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_02088BA0: .word 0x020FD6F8
_02088BA4: .word 0x020FD6F4

	thumb_func_start FUN_02088BA8
FUN_02088BA8: ; 0x02088BA8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_0208898C
	cmp r0, #0x0
	bne _02088BBA
	mov r0, #0x1
	pop {r3-r5, pc}
_02088BBA:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0206E2F0
	add r5, r0, #0x0
	bl FUN_0206E308
	add r2, r0, #0x0
	ldr r1, [r4, #0x18]
	add r0, r5, #0x0
	bl memcpy
	ldr r0, [r4, #0x18]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x18]
	add r0, r5, #0x0
	bl FUN_0206E37C
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	bl FUN_0206E384
	cmp r0, #0x5
	bhi _02088C16
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02088C02: ; jump table (using 16-bit offset)
	.short _02088C1E - _02088C02 - 2; case 0
	.short _02088C0E - _02088C02 - 2; case 1
	.short _02088C1E - _02088C02 - 2; case 2
	.short _02088C1E - _02088C02 - 2; case 3
	.short _02088C1E - _02088C02 - 2; case 4
	.short _02088C12 - _02088C02 - 2; case 5
_02088C0E:
	mov r0, #0x2
	pop {r3-r5, pc}
_02088C12:
	mov r0, #0x5
	pop {r3-r5, pc}
_02088C16:
	bl ErrorHandling
	mov r0, #0x95
	str r0, [r4, #0x8]
_02088C1E:
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x8]
	ldr r0, [r0, #0x14]
	lsl r1, r1, #0x10
	ldr r3, [r4, #0x0]
	lsr r1, r1, #0x10
	mov r2, #0x1
	bl FUN_0206EDD4
	cmp r0, #0x0
	bne _02088C38
	bl ErrorHandling
_02088C38:
	mov r0, #0x4
	pop {r3-r5, pc}

	thumb_func_start FUN_02088C3C
FUN_02088C3C: ; 0x02088C3C
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	ldr r3, _02088CD8 ; =0x020FD718
	ldr r0, [r0, #0x14]
	add r2, sp, #0x8
	str r0, [sp, #0x0]
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020851B8
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x8]
	mov r2, #0x1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_020851DC
	mov r6, #0x0
	add r4, r6, #0x0
_02088C70:
	add r0, r4, #0x0
	bl FUN_0206EB1C
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #0x0]
	ldr r3, [r5, #0x0]
	add r1, r7, #0x0
	mov r2, #0x1
	bl FUN_0206EE50
	cmp r0, #0x1
	bne _02088C9A
	ldr r0, [r5, #0x18]
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_020851DC
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02088C9A:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x40
	blo _02088C70
	add r3, sp, #0x4
	ldr r0, [r5, #0xc]
	mov r1, #0x4
	add r2, sp, #0x4
	add r3, #0x1
	bl FUN_0206F17C
	add r2, sp, #0x4
	ldrb r1, [r2, #0x1]
	add r3, r6, #0x2
	lsl r3, r3, #0x18
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, #0x18]
	lsr r3, r3, #0x18
	bl FUN_020851F8
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x0]
	add r0, sp, #0x8
	bl FUN_02006234
	str r0, [r5, #0x1c]
	mov r0, #0x3
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_02088CD8: .word 0x020FD718

	thumb_func_start FUN_02088CDC
FUN_02088CDC: ; 0x02088CDC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_0208898C
	cmp r0, #0x0
	bne _02088CF2
	add sp, #0x4
	mov r0, #0x3
	pop {r3-r4, pc}
_02088CF2:
	add r1, sp, #0x0
	ldr r0, [r4, #0x18]
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_0208524C
	add r3, sp, #0x0
	ldrb r2, [r3, #0x0]
	ldrb r3, [r3, #0x1]
	ldr r0, [r4, #0xc]
	mov r1, #0x4
	bl FUN_0206F190
	ldr r0, [r4, #0x18]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x18]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02088D1C
FUN_02088D1C: ; 0x02088D1C
	mov r0, #0x13
	bx lr

	thumb_func_start FUN_02088D20
FUN_02088D20: ; 0x02088D20
	ldr r3, _02088D3C ; =0x020FD8C8
	mov r2, #0x0
_02088D24:
	ldrb r1, [r3, #0x0]
	cmp r0, r1
	bne _02088D2E
	add r0, r2, #0x0
	bx lr
_02088D2E:
	add r2, r2, #0x1
	add r3, #0xc
	cmp r2, #0x13
	blo _02088D24
	mov r0, #0x0
	bx lr
	nop
_02088D3C: .word 0x020FD8C8

	thumb_func_start FUN_02088D40
FUN_02088D40: ; 0x02088D40
	push {r3, lr}
	bl FUN_02088D20
	bl FUN_02088D4C
	pop {r3, pc}

	thumb_func_start FUN_02088D4C
FUN_02088D4C: ; 0x02088D4C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088D58
	bl ErrorHandling
_02088D58:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088D64 ; =0x020FD8CA
	ldrh r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088D64: .word 0x020FD8CA

	thumb_func_start FUN_02088D68
FUN_02088D68: ; 0x02088D68
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088D74
	bl ErrorHandling
_02088D74:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088D80 ; =0x020FD8C8
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088D80: .word 0x020FD8C8

	thumb_func_start FUN_02088D84
FUN_02088D84: ; 0x02088D84
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088D90
	bl ErrorHandling
_02088D90:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088D9C ; =0x020FD8C9
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088D9C: .word 0x020FD8C9

	thumb_func_start FUN_02088DA0
FUN_02088DA0: ; 0x02088DA0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088DAC
	bl ErrorHandling
_02088DAC:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088DB8 ; =0x020FD8CC
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088DB8: .word 0x020FD8CC

	thumb_func_start FUN_02088DBC
FUN_02088DBC: ; 0x02088DBC
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088DC8
	bl ErrorHandling
_02088DC8:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088DD4 ; =0x020FD8D0
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088DD4: .word 0x020FD8D0

	thumb_func_start FUN_02088DD8
FUN_02088DD8: ; 0x02088DD8
	push {r3, lr}
	mov r1, #0x18
	bl FUN_02016998
	add r3, r0, #0x0
	mov r2, #0x18
	mov r1, #0x0
_02088DE6:
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _02088DE6
	pop {r3, pc}

	thumb_func_start FUN_02088DF0
FUN_02088DF0: ; 0x02088DF0
	ldr r3, _02088DF4 ; =FUN_02016A18
	bx r3
	.balign 4
_02088DF4: .word FUN_02016A18

	thumb_func_start FUN_02088DF8
FUN_02088DF8: ; 0x02088DF8
	push {r3-r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x0]
	mov r1, #0x5
	mov r2, #0x0
	add r5, r0, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r4, #0x0
	str r0, [sp, #0x4]
	add r7, r4, #0x0
	add r6, sp, #0x10
_02088E34:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	add r2, r7, #0x0
	bl FUN_020671BC
	lsl r1, r4, #0x1
	strh r0, [r6, r1]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02088E34
	ldr r0, [sp, #0x0]
	mov r1, #0x2c
	bl FUN_02016998
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x2c
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x8]
	add r2, r7, #0x0
	bl FUN_02069F9C
	mov r2, #0x0
	mov r12, r2
_02088E70:
	mov r0, r12
	lsl r0, r0, #0x1
	ldrh r5, [r7, r0]
	ldr r6, _02088EF4 ; =0x0000FFFF
	cmp r5, r6
	bne _02088E82
	lsl r0, r2, #0x1
	strh r6, [r4, r0]
	b _02088EE8
_02088E82:
	mov r1, #0xfe
	lsl r1, r1, #0x8
	and r1, r5
	asr r3, r1, #0x9
	ldr r1, [sp, #0x4]
	cmp r3, r1
	bgt _02088EDA
	lsr r1, r6, #0x7
	and r1, r5
	strh r1, [r7, r0]
	ldrh r3, [r7, r0]
	mov r1, #0x0
	add r6, sp, #0x10
_02088E9C:
	lsl r5, r1, #0x1
	ldrh r5, [r6, r5]
	cmp r3, r5
	beq _02088EAE
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x4
	blo _02088E9C
_02088EAE:
	cmp r1, #0x4
	bne _02088EDA
	mov r1, #0x0
	cmp r2, #0x0
	bls _02088ECA
_02088EB8:
	lsl r5, r1, #0x1
	ldrh r5, [r4, r5]
	cmp r5, r3
	beq _02088ECA
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r2
	blo _02088EB8
_02088ECA:
	cmp r1, r2
	bne _02088EDA
	ldrh r1, [r7, r0]
	lsl r0, r2, #0x1
	strh r1, [r4, r0]
	add r0, r2, #0x1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
_02088EDA:
	mov r0, r12
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r12, r0
	cmp r0, #0x16
	blo _02088E70
_02088EE8:
	add r0, r7, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_02088EF4: .word 0x0000FFFF

	thumb_func_start FUN_02088EF8
FUN_02088EF8: ; 0x02088EF8
	ldrh r1, [r0, #0x0]
	ldr r0, _02088F08 ; =0x0000FFFF
	cmp r1, r0
	beq _02088F04
	mov r0, #0x1
	bx lr
_02088F04:
	mov r0, #0x0
	bx lr
	.balign 4
_02088F08: .word 0x0000FFFF

	thumb_func_start FUN_02088F0C
FUN_02088F0C: ; 0x02088F0C
	push {r4-r6, lr}
	add r5, r1, #0x0
	ldr r1, _02088F44 ; =0x0000195C
	add r6, r0, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r6, #0x0
	str r5, [r4, #0x0]
	bl FUN_020139D8
	str r0, [r4, #0x4]
	mov r3, #0x0
	ldr r0, _02088F48 ; =0x0000189E
	add r2, r3, #0x0
_02088F2A:
	add r1, r4, r3
	add r3, r3, #0x1
	strb r2, [r1, r0]
	cmp r3, #0xbb
	blt _02088F2A
	add r0, r4, #0x0
	bl FUN_02088F60
	add r0, r4, #0x0
	bl FUN_020891D0
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02088F44: .word 0x0000195C
_02088F48: .word 0x0000189E

	thumb_func_start FUN_02088F4C
FUN_02088F4C: ; 0x02088F4C
	push {r4, lr}
	add r4, r0, #0x0
	beq _02088F5E
	ldr r0, [r4, #0x4]
	bl FUN_02013A10
	add r0, r4, #0x0
	bl FUN_02016A18
_02088F5E:
	pop {r4, pc}

	thumb_func_start FUN_02088F60
FUN_02088F60: ; 0x02088F60
	push {r4-r7, lr}
	sub sp, #0xc
	mov r4, #0x0
	str r0, [sp, #0x0]
	add r7, r0, #0x0
	str r0, [sp, #0x8]
	add r0, #0x68
	ldr r5, _02088F9C ; =0x020FE17C
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
_02088F74:
	ldr r3, [sp, #0x8]
	str r4, [r7, #0x38]
	lsl r6, r4, #0x1
	add r3, r3, r6
	ldr r0, [sp, #0x0]
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	ldr r6, [r5, #0x0]
	blx r6
	str r0, [r7, #0x8]
	add r4, r4, r0
	ldr r0, [sp, #0x4]
	add r7, r7, #0x4
	add r0, r0, #0x1
	add r5, #0xc
	str r0, [sp, #0x4]
	cmp r0, #0xc
	blt _02088F74
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02088F9C: .word 0x020FE17C

	thumb_func_start FUN_02088FA0
FUN_02088FA0: ; 0x02088FA0
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	str r2, [sp, #0x4]
	add r5, r1, #0x0
	add r4, r3, #0x0
	mov r6, #0x0
	bl FUN_02085418
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r7, r6, #0x0
	cmp r0, #0x0
	bls _02088FF6
_02088FBE:
	ldrh r1, [r5, #0x0]
	ldr r0, [sp, #0x8]
	bl FUN_020245F0
	cmp r0, #0x0
	beq _02088FEC
	ldrh r3, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r2, #0x7
	lsr r1, r3, #0x3
	add r1, r0, r1
	ldr r0, _02088FFC ; =0x0000189E
	and r3, r2
	mov r2, #0x1
	ldrb r0, [r1, r0]
	lsl r2, r3
	orr r2, r0
	ldr r0, _02088FFC ; =0x0000189E
	add r6, r6, #0x1
	strb r2, [r1, r0]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
_02088FEC:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r5, r5, #0x2
	cmp r7, r0
	blo _02088FBE
_02088FF6:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02088FFC: .word 0x0000189E

	thumb_func_start FUN_02089000
FUN_02089000: ; 0x02089000
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02085420
	cmp r0, #0x0
	beq _02089046
	mov r2, #0x0
	cmp r7, #0x0
	bls _02089042
_0208901A:
	ldrh r6, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r3, #0x7
	lsr r1, r6, #0x3
	add r1, r0, r1
	ldr r0, _0208904C ; =0x0000189E
	and r6, r3
	mov r3, #0x1
	ldrb r0, [r1, r0]
	lsl r3, r6
	orr r3, r0
	ldr r0, _0208904C ; =0x0000189E
	add r2, r2, #0x1
	strb r3, [r1, r0]
	ldrh r0, [r5, #0x0]
	add r5, r5, #0x2
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
	cmp r2, r7
	blo _0208901A
_02089042:
	add r0, r7, #0x0
	pop {r3-r7, pc}
_02089046:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0208904C: .word 0x0000189E

	thumb_func_start FUN_02089050
FUN_02089050: ; 0x02089050
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	add r4, r3, #0x0
	bl FUN_0208541C
	str r0, [sp, #0xc]
	ldr r0, _020890BC ; =0x00000189
	mov r1, #0x0
	bl FUN_02013A9C
	str r0, [sp, #0x8]
	mov r7, #0x0
	ldr r0, [sp, #0x4]
	add r6, r7, #0x0
	cmp r0, #0x0
	bls _020890B4
_02089078:
	ldrh r2, [r5, #0x0]
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	sub r1, r2, r1
	bl FUN_02013B68
	cmp r0, #0x0
	beq _020890AA
	ldrh r3, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r2, #0x7
	lsr r1, r3, #0x3
	add r1, r0, r1
	ldr r0, _020890C0 ; =0x0000189E
	and r3, r2
	mov r2, #0x1
	ldrb r0, [r1, r0]
	lsl r2, r3
	orr r2, r0
	ldr r0, _020890C0 ; =0x0000189E
	add r6, r6, #0x1
	strb r2, [r1, r0]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
_020890AA:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r5, r5, #0x2
	cmp r7, r0
	blo _02089078
_020890B4:
	add r0, r6, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_020890BC: .word 0x00000189
_020890C0: .word 0x0000189E

	thumb_func_start FUN_020890C4
FUN_020890C4: ; 0x020890C4
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	add r4, r3, #0x0
	bl FUN_0208541C
	str r0, [sp, #0x10]
	ldr r0, _02089144 ; =0x00000186
	mov r1, #0x0
	bl FUN_02013A9C
	add r6, r0, #0x0
	add r0, r6, #0x5
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	mov r7, #0x0
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x8]
	cmp r0, #0x0
	bls _0208913C
_020890F4:
	ldrh r1, [r5, #0x0]
	cmp r1, r6
	blo _0208910C
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bhi _0208910C
	ldr r0, [sp, #0x10]
	sub r1, r1, r6
	bl FUN_02013C0C
	cmp r0, #0x0
	beq _0208912E
_0208910C:
	ldrh r3, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r2, #0x7
	lsr r1, r3, #0x3
	add r1, r0, r1
	ldr r0, _02089148 ; =0x0000189E
	and r3, r2
	mov r2, #0x1
	ldrb r0, [r1, r0]
	lsl r2, r3
	orr r2, r0
	ldr r0, _02089148 ; =0x0000189E
	add r7, r7, #0x1
	strb r2, [r1, r0]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
_0208912E:
	ldr r0, [sp, #0x8]
	add r5, r5, #0x2
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x8]
	cmp r1, r0
	blo _020890F4
_0208913C:
	add r0, r7, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02089144: .word 0x00000186
_02089148: .word 0x0000189E

	thumb_func_start FUN_0208914C
FUN_0208914C: ; 0x0208914C
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x0
	mov lr, r2
	mov r12, r0
	mov r0, lr
	add r4, r1, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	bls _020891C2
_02089160:
	ldrh r2, [r4, #0x0]
	ldr r0, _020891C8 ; =0x0000FFFE
	cmp r2, r0
	bne _02089196
	add r0, r4, #0x2
	add r4, r4, #0x4
	ldrh r2, [r0, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r2, #0x0
	strh r0, [r7, #0x0]
	beq _020891B6
_02089176:
	ldrh r5, [r4, #0x0]
	mov r3, #0x7
	add r4, r4, #0x2
	lsr r0, r5, #0x3
	add r1, r6, r0
	ldr r0, _020891CC ; =0x0000189E
	and r5, r3
	mov r3, #0x1
	ldrb r0, [r1, r0]
	lsl r3, r5
	orr r3, r0
	ldr r0, _020891CC ; =0x0000189E
	sub r2, r2, #0x1
	strb r3, [r1, r0]
	bne _02089176
	b _020891B6
_02089196:
	lsr r0, r2, #0x3
	ldr r1, _020891CC ; =0x0000189E
	add r0, r6, r0
	ldrb r3, [r0, r1]
	mov r1, #0x7
	mov r5, #0x1
	and r1, r2
	add r2, r5, #0x0
	lsl r2, r1
	ldr r1, _020891CC ; =0x0000189E
	orr r2, r3
	strb r2, [r0, r1]
	ldrh r0, [r4, #0x0]
	add r4, r4, #0x2
	strh r0, [r7, #0x0]
	add r7, r7, #0x2
_020891B6:
	mov r0, r12
	add r1, r0, #0x1
	mov r0, lr
	mov r12, r1
	cmp r1, r0
	blo _02089160
_020891C2:
	mov r0, lr
	pop {r3-r7, pc}
	nop
_020891C8: .word 0x0000FFFE
_020891CC: .word 0x0000189E

	thumb_func_start FUN_020891D0
FUN_020891D0: ; 0x020891D0
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r4, #0x0
	ldr r6, _0208920C ; =0x020FDDF0
	str r4, [sp, #0x0]
	add r5, r7, #0x0
_020891DC:
	ldr r0, _02089210 ; =0x00000C84
	mov r2, #0xcf
	str r4, [r5, r0]
	lsl r2, r2, #0x4
	ldr r1, [r6, #0x0]
	add r0, r7, #0x0
	add r2, r7, r2
	add r3, r4, #0x0
	bl FUN_02089218
	ldr r1, _02089214 ; =0x00000C18
	add r6, r6, #0x4
	str r0, [r5, r1]
	add r0, r1, #0x0
	ldr r0, [r5, r0]
	add r5, r5, #0x4
	add r4, r4, r0
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, #0x1b
	blo _020891DC
	pop {r3-r7, pc}
	nop
_0208920C: .word 0x020FDDF0
_02089210: .word 0x00000C84
_02089214: .word 0x00000C18

	thumb_func_start FUN_02089218
FUN_02089218: ; 0x02089218
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r6, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x0
	mov r12, r0
	ldrh r2, [r7, #0x0]
	ldr r0, _020892B8 ; =0x0000FFFF
	mov lr, r3
	cmp r2, r0
	beq _020892B4
_0208922E:
	ldr r0, _020892BC ; =0x0000FFFE
	cmp r2, r0
	bne _02089280
	add r0, r7, #0x2
	ldrh r5, [r0, #0x0]
	add r7, r7, #0x4
	mov r3, #0x0
	cmp r5, #0x0
	bls _0208927A
	add r4, r7, #0x0
_02089242:
	ldrh r2, [r4, #0x0]
	mov r0, #0x7
	mov r1, #0x1
	and r0, r2
	lsl r1, r0
	lsr r0, r2, #0x3
	add r2, r6, r0
	ldr r0, _020892C0 ; =0x0000189E
	ldrb r0, [r2, r0]
	tst r0, r1
	beq _02089272
	lsl r0, r3, #0x1
	ldrh r1, [r7, r0]
	mov r0, lr
	lsl r2, r0, #0x1
	mov r0, lr
	add r0, r0, #0x1
	mov lr, r0
	ldr r0, [sp, #0x0]
	strh r1, [r0, r2]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	b _0208927A
_02089272:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, r5
	blo _02089242
_0208927A:
	lsl r0, r5, #0x1
	add r7, r7, r0
	b _020892AC
_02089280:
	mov r1, #0x1
	mov r0, #0x7
	and r0, r2
	add r3, r1, #0x0
	lsl r3, r0
	lsr r0, r2, #0x3
	add r1, r6, r0
	ldr r0, _020892C0 ; =0x0000189E
	ldrb r0, [r1, r0]
	tst r0, r3
	beq _020892AA
	mov r1, lr
	add r1, r1, #0x1
	mov r0, lr
	mov lr, r1
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x1
	strh r2, [r1, r0]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
_020892AA:
	add r7, r7, #0x2
_020892AC:
	ldrh r2, [r7, #0x0]
	ldr r0, _020892B8 ; =0x0000FFFF
	cmp r2, r0
	bne _0208922E
_020892B4:
	mov r0, r12
	pop {r3-r7, pc}
	.balign 4
_020892B8: .word 0x0000FFFF
_020892BC: .word 0x0000FFFE
_020892C0: .word 0x0000189E

	thumb_func_start FUN_020892C4
FUN_020892C4: ; 0x020892C4
	lsl r1, r1, #0x2
	add r0, r0, r1
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_020892CC
FUN_020892CC: ; 0x020892CC
	push {r4, lr}
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x38]
	ldr r0, [r4, #0x4]
	add r1, r1, r2
	lsl r1, r1, #0x1
	add r1, r4, r1
	add r1, #0x68
	ldrh r1, [r1, #0x0]
	add r2, r3, #0x0
	bl FUN_02013A30
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020892EC
FUN_020892EC: ; 0x020892EC
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r1, [r1, #0x38]
	add r1, r1, r2
	lsl r1, r1, #0x1
	add r0, r0, r1
	add r0, #0x68
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02089300
FUN_02089300: ; 0x02089300
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r0, _0208930C ; =0x00000C18
	ldr r0, [r1, r0]
	bx lr
	nop
_0208930C: .word 0x00000C18

	thumb_func_start FUN_02089310
FUN_02089310: ; 0x02089310
	push {r4-r6, lr}
	add r4, r3, #0x0
	add r5, r0, #0x0
	lsl r3, r1, #0x2
	add r6, r5, r3
	ldr r3, _02089334 ; =0x00000C18
	ldr r3, [r6, r3]
	cmp r3, #0x0
	beq _02089330
	bl FUN_02089338
	add r1, r0, #0x0
	ldr r0, [r5, #0x4]
	add r2, r4, #0x0
	bl FUN_02013A30
_02089330:
	pop {r4-r6, pc}
	nop
_02089334: .word 0x00000C18

	thumb_func_start FUN_02089338
FUN_02089338: ; 0x02089338
	push {r3-r4}
	lsl r1, r1, #0x2
	ldr r3, _02089360 ; =0x00000C18
	add r4, r0, r1
	ldr r1, [r4, r3]
	cmp r1, #0x0
	beq _0208935A
	add r1, r3, #0x0
	add r1, #0x6c
	ldr r1, [r4, r1]
	add r3, #0xd8
	add r1, r2, r1
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, r3]
	pop {r3-r4}
	bx lr
_0208935A:
	ldr r0, _02089364 ; =0x0000FFFF
	pop {r3-r4}
	bx lr
	.balign 4
_02089360: .word 0x00000C18
_02089364: .word 0x0000FFFF

	thumb_func_start FUN_02089368
FUN_02089368: ; 0x02089368
	push {r3-r6}
	mov r1, #0x0
	ldr r2, _0208938C ; =0x020FF2FC
	ldr r5, _02089390 ; =0x020FE17C
	add r0, r1, #0x0
	mov r3, #0xc
_02089374:
	ldrb r4, [r2, #0x0]
	add r1, r1, #0x1
	add r2, r2, #0x1
	add r6, r4, #0x0
	mul r6, r3
	add r4, r5, r6
	ldr r4, [r4, #0x8]
	add r0, r0, r4
	cmp r1, #0x5
	blo _02089374
	pop {r3-r6}
	bx lr
	.balign 4
_0208938C: .word 0x020FF2FC
_02089390: .word 0x020FE17C

	thumb_func_start FUN_02089394
FUN_02089394: ; 0x02089394
	push {r4-r7}
	mov r2, #0x0
	ldr r3, _020893D8 ; =0x020FF2FC
	add r1, r2, #0x0
_0208939C:
	ldrb r5, [r3, #0x0]
	mov r4, #0xc
	add r6, r5, #0x0
	mul r6, r4
	ldr r4, _020893DC ; =0x020FE17C
	add r5, r4, r6
	ldr r7, [r5, #0x8]
	mov r6, #0x0
	ldr r4, [r5, #0x4]
	cmp r7, #0x0
	ble _020893C8
_020893B2:
	ldrh r5, [r4, #0x0]
	cmp r0, r5
	bne _020893BE
	add r0, r2, #0x0
	pop {r4-r7}
	bx lr
_020893BE:
	add r6, r6, #0x1
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r6, r7
	blt _020893B2
_020893C8:
	add r1, r1, #0x1
	add r3, r3, #0x1
	cmp r1, #0x5
	blo _0208939C
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4
_020893D8: .word 0x020FF2FC
_020893DC: .word 0x020FE17C

	thumb_func_start FUN_020893E0
FUN_020893E0: ; 0x020893E0
	mov r1, #0x0
	ldr r0, _020893EC ; =0x02106154
	mvn r1, r1
	str r1, [r0, #0x0]
	bx lr
	nop
_020893EC: .word 0x02106154

	thumb_func_start FUN_020893F0
FUN_020893F0: ; 0x020893F0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x3
	lsl r0, r0, #0xc
	cmp r2, r0
	bhs _0208940A
	add r0, r1, #0x0
	ldr r1, _02089410 ; =0x021C5C58
	bl MIi_CpuCopy32
	ldr r0, _02089414 ; =0x02106154
	str r4, [r0, #0x0]
	pop {r4, pc}
_0208940A:
	bl ErrorHandling
	pop {r4, pc}
	.balign 4
_02089410: .word 0x021C5C58
_02089414: .word 0x02106154

	thumb_func_start FUN_02089418
FUN_02089418: ; 0x02089418
	push {r3, lr}
	mov r3, #0x3
	lsl r3, r3, #0xc
	cmp r2, r3
	bhs _02089434
	ldr r3, _0208943C ; =0x02106154
	ldr r3, [r3, #0x0]
	cmp r0, r3
	bne _02089438
	ldr r0, _02089440 ; =0x021C5C58
	bl MIi_CpuCopy32
	mov r0, #0x1
	pop {r3, pc}
_02089434:
	bl ErrorHandling
_02089438:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0208943C: .word 0x02106154
_02089440: .word 0x021C5C58

	thumb_func_start FUN_02089444
FUN_02089444: ; 0x02089444
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x3
	lsl r0, r0, #0xc
	cmp r2, r0
	bhs _0208945E
	add r0, r1, #0x0
	ldr r1, _02089464 ; =0x021C5C58
	bl MIi_CpuCopyFast
	ldr r0, _02089468 ; =0x02106154
	str r4, [r0, #0x0]
	pop {r4, pc}
_0208945E:
	bl ErrorHandling
	pop {r4, pc}
	.balign 4
_02089464: .word 0x021C5C58
_02089468: .word 0x02106154

	thumb_func_start FUN_0208946C
FUN_0208946C: ; 0x0208946C
	push {r3, lr}
	mov r3, #0x3
	lsl r3, r3, #0xc
	cmp r2, r3
	bhs _02089488
	ldr r3, _02089490 ; =0x02106154
	ldr r3, [r3, #0x0]
	cmp r0, r3
	bne _0208948C
	ldr r0, _02089494 ; =0x021C5C58
	bl MIi_CpuCopyFast
	mov r0, #0x1
	pop {r3, pc}
_02089488:
	bl ErrorHandling
_0208948C:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02089490: .word 0x02106154
_02089494: .word 0x021C5C58

	thumb_func_start FUN_02089498
FUN_02089498: ; 0x02089498
	push {r3-r5, lr}
	mov r2, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x58
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0x38
	mov r2, #0x58
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x38
	add r4, r0, #0x0
	bl memset
	mov r0, #0x58
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r0, [r0, #0x8]
	str r0, [r4, #0x30]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020894D4
FUN_020894D4: ; 0x020894D4
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r4, r0, #0x0
	mov r6, #0x0
	cmp r1, #0x3
	bhi _020895DA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020894F4: ; jump table (using 16-bit offset)
	.short _020894FC - _020894F4 - 2; case 0
	.short _02089588 - _020894F4 - 2; case 1
	.short _02089596 - _020894F4 - 2; case 2
	.short _020895BC - _020894F4 - 2; case 3
_020894FC:
	ldr r0, _020895E0 ; =0x00000495
	add r1, r6, #0x0
	bl FUN_02005350
	add r0, r6, #0x0
	bl FUN_0200516C
	add r0, r6, #0x0
	bl FUN_0200415C
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	add r1, r6, #0x0
	bl FUN_0200E3A0
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _020895E4 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _020895E8 ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	add r0, r4, #0x0
	bl FUN_0208961C
	add r0, r4, #0x0
	bl FUN_02089734
	ldr r0, _020895EC ; =FUN_02089610
	add r1, r4, #0x0
	bl FUN_02015F10
	bl FUN_0201E788
	mov r0, #0x6
	mov r1, #0x1
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _020895DA
_02089588:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _020895DA
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _020895DA
_02089596:
	bl FUN_02089790
	cmp r0, #0x1
	bne _020895DA
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _020895DA
_020895BC:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _020895DA
	add r0, r4, #0x0
	bl FUN_0208977C
	add r0, r4, #0x0
	bl FUN_020896E0
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r6, #0x1
_020895DA:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_020895E0: .word 0x00000495
_020895E4: .word 0xFFFFE0FF
_020895E8: .word 0x04001000
_020895EC: .word FUN_02089610

	thumb_func_start FUN_020895F0
FUN_020895F0: ; 0x020895F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	ldr r4, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_0200627C
	add r0, r4, #0x0
	bl FUN_020168D0
	mov r0, #0x0
	bl OS_ResetSystem
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02089610
FUN_02089610: ; 0x02089610
	ldr r3, _02089618 ; =FUN_0201AB60
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02089618: .word FUN_0201AB60

	thumb_func_start FUN_0208961C
FUN_0208961C: ; 0x0208961C
	push {r4-r5, lr}
	sub sp, #0x5c
	ldr r5, _020896C8 ; =0x020FF340
	add r4, r0, #0x0
	add r3, sp, #0x34
	mov r2, #0x5
_02089628:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02089628
	add r0, sp, #0x34
	bl FUN_0201E66C
	ldr r0, [r4, #0x0]
	bl FUN_02016B94
	add r3, sp, #0x24
	ldr r5, _020896CC ; =0x020FF314
	str r0, [r4, #0x14]
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _020896D0 ; =0x020FF324
	add r3, sp, #0x8
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	ldr r0, [r4, #0x14]
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _020896D4 ; =0x000001E2
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	mov r3, #0x2
	bl FUN_0200CD68
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _020896D8 ; =0x000001D9
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	mov r3, #0x3
	bl FUN_0200CB00
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	mov r1, #0x20
	bl FUN_02002ED0
	mov r0, #0x0
	ldr r3, [r4, #0x0]
	mov r1, #0x20
	add r2, r0, #0x0
	bl FUN_02017F18
	ldr r1, _020896DC ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _020896DC ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	add sp, #0x5c
	pop {r4-r5, pc}
	.balign 4
_020896C8: .word 0x020FF340
_020896CC: .word 0x020FF314
_020896D0: .word 0x020FF324
_020896D4: .word 0x000001E2
_020896D8: .word 0x000001D9
_020896DC: .word 0x00006C21

	thumb_func_start FUN_020896E0
FUN_020896E0: ; 0x020896E0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0201797C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x5
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x6
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x7
	mov r1, #0x0
	bl FUN_0201797C
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	bl FUN_020178A0
	ldr r0, [r4, #0x14]
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02089734
FUN_02089734: ; 0x02089734
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r3, [r4, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x4
	bl FUN_0200A86C
	str r0, [r4, #0x18]
	bl FUN_0201BD5C
	mov r0, #0x0
	str r0, [r4, #0x8]
	add r1, r4, #0x0
	ldr r0, [r4, #0x14]
	ldr r2, _02089778 ; =0x020FF304
	add r1, #0x1c
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	mov r2, #0x0
	add r4, #0x1c
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	add sp, #0x8
	pop {r4, pc}
	nop
_02089778: .word 0x020FF304

	thumb_func_start FUN_0208977C
FUN_0208977C: ; 0x0208977C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_02019178
	ldr r0, [r4, #0x18]
	bl FUN_0200A8B8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02089790
FUN_02089790: ; 0x02089790
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r5, #0x0
	cmp r1, #0x6
	bhi _02089888
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020897AA: ; jump table (using 16-bit offset)
	.short _020897B8 - _020897AA - 2; case 0
	.short _020897E2 - _020897AA - 2; case 1
	.short _02089802 - _020897AA - 2; case 2
	.short _0208982C - _020897AA - 2; case 3
	.short _0208984C - _020897AA - 2; case 4
	.short _0208986C - _020897AA - 2; case 5
	.short _0208987E - _020897AA - 2; case 6
_020897B8:
	add r1, r5, #0x0
	mov r2, #0x1
	mov r3, #0x4
	bl FUN_0208989C
	cmp r0, #0x1
	bne _02089888
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, _02089890 ; =0x020FF30C
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	ldr r2, _02089894 ; =0x000001D9
	mov r3, #0x3
	bl FUN_020020EC
	str r0, [r4, #0x2c]
	mov r0, #0x1
	str r0, [r4, #0x4]
	b _02089888
_020897E2:
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _020897F6
	sub r1, r5, #0x2
	cmp r0, r1
	beq _020897FC
	b _02089888
_020897F6:
	mov r0, #0x2
	str r0, [r4, #0x4]
	b _02089888
_020897FC:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02089888
_02089802:
	mov r1, #0x1
	add r2, r1, #0x0
	mov r3, #0x4
	bl FUN_0208989C
	cmp r0, #0x1
	bne _02089888
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, _02089890 ; =0x020FF30C
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	ldr r2, _02089894 ; =0x000001D9
	mov r3, #0x3
	bl FUN_020020EC
	str r0, [r4, #0x2c]
	mov r0, #0x3
	str r0, [r4, #0x4]
	b _02089888
_0208982C:
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _02089840
	sub r1, r5, #0x2
	cmp r0, r1
	beq _02089846
	b _02089888
_02089840:
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _02089888
_02089846:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02089888
_0208984C:
	mov r1, #0x2
	mov r2, #0x1
	add r3, r5, #0x0
	bl FUN_0208989C
	cmp r0, #0x1
	bne _02089888
	add r0, r4, #0x0
	ldr r1, _02089898 ; =0x000001E2
	add r0, #0x1c
	bl FUN_0200D858
	str r0, [r4, #0x34]
	mov r0, #0x5
	str r0, [r4, #0x4]
	b _02089888
_0208986C:
	ldr r0, [r4, #0x30]
	bl FUN_0202263C
	ldr r0, [r4, #0x34]
	bl FUN_0200DBFC
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02089888
_0208987E:
	ldr r0, [r4, #0x14]
	add r1, r5, #0x0
	bl FUN_02018744
	mov r5, #0x1
_02089888:
	add r0, r5, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_02089890: .word 0x020FF30C
_02089894: .word 0x000001D9
_02089898: .word 0x000001E2

	thumb_func_start FUN_0208989C
FUN_0208989C: ; 0x0208989C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	add r7, r1, #0x0
	add r4, r3, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	beq _020898B8
	cmp r0, #0x1
	beq _02089920
	cmp r0, #0x2
	beq _0208993C
	b _02089950
_020898B8:
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x1c
	mov r1, #0xf
	add r2, r6, #0x0
	add r3, r6, #0x0
	bl FUN_020196F4
	add r0, r5, #0x0
	ldr r2, _02089958 ; =0x000001E2
	add r0, #0x1c
	add r1, r6, #0x0
	mov r3, #0x2
	bl FUN_0200D0BC
	mov r0, #0x1
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	str r0, [r5, #0x10]
	ldr r0, [r5, #0x18]
	ldr r2, [r5, #0x10]
	add r1, r7, #0x0
	bl FUN_0200A8E0
	add r3, r6, #0x0
	str r3, [sp, #0x0]
	str r4, [sp, #0x4]
	str r3, [sp, #0x8]
	add r0, r5, #0x0
	ldr r2, [r5, #0x10]
	add r0, #0x1c
	mov r1, #0x1
	bl FUN_0201BD84
	str r0, [r5, #0xc]
	cmp r4, #0x0
	bne _02089918
	ldr r0, [r5, #0x10]
	bl FUN_02021A20
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
_02089918:
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	b _02089950
_02089920:
	ldr r0, [r5, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02089950
	ldr r0, [r5, #0x10]
	bl FUN_02021A20
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	b _02089950
_0208993C:
	cmp r2, #0x0
	bne _0208994A
	ldr r0, _0208995C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _02089950
_0208994A:
	mov r0, #0x0
	str r0, [r5, #0x8]
	mov r6, #0x1
_02089950:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02089958: .word 0x000001E2
_0208995C: .word 0x021C48B8

	thumb_func_start FUN_02089960
FUN_02089960: ; 0x02089960
	push {r3-r5, lr}
	mov r2, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x58
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0x3c
	mov r2, #0x58
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x3c
	add r4, r0, #0x0
	bl memset
	mov r0, #0x58
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r0, [r0, #0x8]
	str r0, [r4, #0x34]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0208999C
FUN_0208999C: ; 0x0208999C
	push {r4-r6, lr}
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r6, r0, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	beq _020899B8
	cmp r1, #0x1
	beq _02089A12
	cmp r1, #0x2
	beq _02089A20
	b _02089A34
_020899B8:
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	add r1, r4, #0x0
	bl FUN_0200E3A0
	add r0, r4, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	add r0, r4, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02089A38 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _02089A3C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	add r0, r6, #0x0
	bl FUN_02089A6C
	add r0, r6, #0x0
	bl FUN_02089B80
	bl FUN_0201E788
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02089A34
_02089A12:
	bl FUN_02089BE0
	cmp r0, #0x1
	bne _02089A34
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02089A34
_02089A20:
	bl FUN_02089BCC
	add r0, r6, #0x0
	bl FUN_02089B2C
	add r0, r4, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r4, #0x1
_02089A34:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02089A38: .word 0xFFFFE0FF
_02089A3C: .word 0x04001000

	thumb_func_start FUN_02089A40
FUN_02089A40: ; 0x02089A40
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	ldr r4, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_0200627C
	add r0, r4, #0x0
	bl FUN_020168D0
	ldr r0, _02089A64 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _02089A68 ; =0x0223A360
	bl FUN_02000E7C
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02089A64: .word SDK_OVERLAY_MODULE_83_ID
_02089A68: .word 0x0223A360

	thumb_func_start FUN_02089A6C
FUN_02089A6C: ; 0x02089A6C
	push {r4-r5, lr}
	sub sp, #0x5c
	ldr r5, _02089B18 ; =0x020FF3AC
	add r4, r0, #0x0
	add r3, sp, #0x34
	mov r2, #0x5
_02089A78:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02089A78
	add r0, sp, #0x34
	bl FUN_0201E66C
	ldr r0, [r4, #0x0]
	bl FUN_02016B94
	add r3, sp, #0x24
	ldr r5, _02089B1C ; =0x020FF380
	str r0, [r4, #0x18]
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _02089B20 ; =0x020FF390
	add r3, sp, #0x8
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	ldr r0, [r4, #0x18]
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _02089B24 ; =0x000001E2
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x18]
	mov r3, #0x2
	bl FUN_0200CD68
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _02089B28 ; =0x000001D9
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x18]
	mov r3, #0x3
	bl FUN_0200CB00
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	mov r1, #0x20
	bl FUN_02002ED0
	mov r0, #0x0
	ldr r3, [r4, #0x0]
	mov r1, #0x20
	add r2, r0, #0x0
	bl FUN_02017F18
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02017FE4
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_02017FE4
	add sp, #0x5c
	pop {r4-r5, pc}
	.balign 4
_02089B18: .word 0x020FF3AC
_02089B1C: .word 0x020FF380
_02089B20: .word 0x020FF390
_02089B24: .word 0x000001E2
_02089B28: .word 0x000001D9

	thumb_func_start FUN_02089B2C
FUN_02089B2C: ; 0x02089B2C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0201797C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x5
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x6
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x7
	mov r1, #0x0
	bl FUN_0201797C
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02089B80
FUN_02089B80: ; 0x02089B80
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r2, _02089BC4 ; =0x00000167
	ldr r3, [r4, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	str r0, [r4, #0x1c]
	bl FUN_0201BD5C
	mov r0, #0x0
	str r0, [r4, #0xc]
	add r1, r4, #0x0
	ldr r0, [r4, #0x18]
	ldr r2, _02089BC8 ; =0x020FF378
	add r1, #0x20
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	mov r2, #0x0
	add r4, #0x20
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	add sp, #0x8
	pop {r4, pc}
	nop
_02089BC4: .word 0x00000167
_02089BC8: .word 0x020FF378

	thumb_func_start FUN_02089BCC
FUN_02089BCC: ; 0x02089BCC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x20
	bl FUN_02019178
	ldr r0, [r4, #0x1c]
	bl FUN_0200A8B8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02089BE0
FUN_02089BE0: ; 0x02089BE0
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r5, #0x0
	cmp r1, #0x5
	bhi _02089CC2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02089BFA: ; jump table (using 16-bit offset)
	.short _02089C06 - _02089BFA - 2; case 0
	.short _02089C3C - _02089BFA - 2; case 1
	.short _02089C68 - _02089BFA - 2; case 2
	.short _02089C76 - _02089BFA - 2; case 3
	.short _02089CA2 - _02089BFA - 2; case 4
	.short _02089CC0 - _02089BFA - 2; case 5
_02089C06:
	ldr r0, [r4, #0x34]
	bl FUN_02022800
	cmp r0, #0x3
	bhi _02089CC2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02089C1C: ; jump table (using 16-bit offset)
	.short _02089C24 - _02089C1C - 2; case 0
	.short _02089C24 - _02089C1C - 2; case 1
	.short _02089C2A - _02089C1C - 2; case 2
	.short _02089C34 - _02089C1C - 2; case 3
_02089C24:
	mov r0, #0x5
	str r0, [r4, #0x4]
	b _02089CC2
_02089C2A:
	add r0, r5, #0x0
	str r0, [r4, #0x8]
	mov r0, #0x1
	str r0, [r4, #0x4]
	b _02089CC2
_02089C34:
	mov r0, #0x1
	str r0, [r4, #0x8]
	str r0, [r4, #0x4]
	b _02089CC2
_02089C3C:
	ldr r1, _02089CC8 ; =0x00006C21
	add r0, r5, #0x0
	bl FUN_02017FE4
	ldr r1, _02089CC8 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x6
	mov r1, #0x1
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x2
	str r0, [r4, #0x4]
	b _02089CC2
_02089C68:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02089CC2
	mov r0, #0x3
	str r0, [r4, #0x4]
	b _02089CC2
_02089C76:
	ldr r1, [r4, #0x8]
	add r2, r5, #0x0
	mov r3, #0x4
	bl FUN_02089CCC
	cmp r0, #0x1
	bne _02089CC2
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _02089CC2
_02089CA2:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02089CC2
	add r0, r5, #0x0
	add r1, r0, #0x0
	bl FUN_02017FE4
	mov r0, #0x4
	add r1, r5, #0x0
	bl FUN_02017FE4
	mov r0, #0x5
	str r0, [r4, #0x4]
	b _02089CC2
_02089CC0:
	mov r5, #0x1
_02089CC2:
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_02089CC8: .word 0x00006C21

	thumb_func_start FUN_02089CCC
FUN_02089CCC: ; 0x02089CCC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r7, r1, #0x0
	add r4, r3, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	beq _02089CE8
	cmp r0, #0x1
	beq _02089D50
	cmp r0, #0x2
	beq _02089D6C
	b _02089D80
_02089CE8:
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x20
	mov r1, #0xf
	add r2, r6, #0x0
	add r3, r6, #0x0
	bl FUN_020196F4
	add r0, r5, #0x0
	ldr r2, _02089D88 ; =0x000001E2
	add r0, #0x20
	add r1, r6, #0x0
	mov r3, #0x2
	bl FUN_0200D0BC
	mov r0, #0x1
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x1c]
	ldr r2, [r5, #0x14]
	add r1, r7, #0x0
	bl FUN_0200A8E0
	add r3, r6, #0x0
	str r3, [sp, #0x0]
	str r4, [sp, #0x4]
	str r3, [sp, #0x8]
	add r0, r5, #0x0
	ldr r2, [r5, #0x14]
	add r0, #0x20
	mov r1, #0x1
	bl FUN_0201BD84
	str r0, [r5, #0x10]
	cmp r4, #0x0
	bne _02089D48
	ldr r0, [r5, #0x14]
	bl FUN_02021A20
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
_02089D48:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02089D80
_02089D50:
	ldr r0, [r5, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02089D80
	ldr r0, [r5, #0x14]
	bl FUN_02021A20
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02089D80
_02089D6C:
	cmp r2, #0x0
	bne _02089D7A
	ldr r0, _02089D8C ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _02089D80
_02089D7A:
	mov r0, #0x0
	str r0, [r5, #0xc]
	mov r6, #0x1
_02089D80:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02089D88: .word 0x000001E2
_02089D8C: .word 0x021C48B8

	thumb_func_start FUN_02089D90
FUN_02089D90: ; 0x02089D90
	push {r3-r6, lr}
	sub sp, #0x1c
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
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02089EF4 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _02089EF8 ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _02089EFC ; =0x021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _02089F00 ; =0x04000050
	mov r0, #0x0
	strh r0, [r3, #0x0]
	ldr r2, _02089F04 ; =0x04001050
	sub r3, #0x50
	strh r0, [r2, #0x0]
	ldr r1, [r3, #0x0]
	ldr r0, _02089F08 ; =0xFFFF1FFF
	sub r2, #0x50
	and r1, r0
	str r1, [r3, #0x0]
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r0, _02089F0C ; =0x020FF418
	bl FUN_0201E66C
	add r0, r4, #0x0
	bl FUN_02016B94
	add r5, r0, #0x0
	ldr r0, _02089F10 ; =0x020FF3EC
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _02089F14 ; =0x020FF3FC
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _02089F18 ; =0x000001F7
	add r0, r5, #0x0
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _02089F1C ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _02089F1C ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x5
	add r3, r4, #0x0
	bl FUN_0200A86C
	add r6, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r2, _02089F20 ; =0x020FF3E4
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0xc
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _02089F18 ; =0x000001F7
	add r0, sp, #0xc
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	add r0, r6, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_0200A8E0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0xc
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl FUN_02021A20
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	mov r4, #0x1
_02089EE4:
	bl FUN_02000FE8
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl OS_WaitIrq
	b _02089EE4
	nop
_02089EF4: .word 0xFFFFE0FF
_02089EF8: .word 0x04001000
_02089EFC: .word 0x021C4918
_02089F00: .word 0x04000050
_02089F04: .word 0x04001050
_02089F08: .word 0xFFFF1FFF
_02089F0C: .word 0x020FF418
_02089F10: .word 0x020FF3EC
_02089F14: .word 0x020FF3FC
_02089F18: .word 0x000001F7
_02089F1C: .word 0x00006C21
_02089F20: .word 0x020FF3E4

	thumb_func_start FUN_02089F24
FUN_02089F24: ; 0x02089F24
	push {r3-r6, lr}
	sub sp, #0x1c
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
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _0208A088 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0208A08C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _0208A090 ; =0x021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _0208A094 ; =0x04000050
	mov r0, #0x0
	strh r0, [r3, #0x0]
	ldr r2, _0208A098 ; =0x04001050
	sub r3, #0x50
	strh r0, [r2, #0x0]
	ldr r1, [r3, #0x0]
	ldr r0, _0208A09C ; =0xFFFF1FFF
	sub r2, #0x50
	and r1, r0
	str r1, [r3, #0x0]
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r0, _0208A0A0 ; =0x020FF418
	bl FUN_0201E66C
	add r0, r4, #0x0
	bl FUN_02016B94
	add r5, r0, #0x0
	ldr r0, _0208A0A4 ; =0x020FF3EC
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _0208A0A8 ; =0x020FF3FC
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _0208A0AC ; =0x000001F7
	add r0, r5, #0x0
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _0208A0B0 ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _0208A0B0 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x5
	add r3, r4, #0x0
	bl FUN_0200A86C
	add r6, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r2, _0208A0B4 ; =0x020FF3E4
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0xc
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _0208A0AC ; =0x000001F7
	add r0, sp, #0xc
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	add r0, r6, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0200A8E0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0xc
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl FUN_02021A20
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	mov r4, #0x1
_0208A078:
	bl FUN_02000FE8
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl OS_WaitIrq
	b _0208A078
	nop
_0208A088: .word 0xFFFFE0FF
_0208A08C: .word 0x04001000
_0208A090: .word 0x021C4918
_0208A094: .word 0x04000050
_0208A098: .word 0x04001050
_0208A09C: .word 0xFFFF1FFF
_0208A0A0: .word 0x020FF418
_0208A0A4: .word 0x020FF3EC
_0208A0A8: .word 0x020FF3FC
_0208A0AC: .word 0x000001F7
_0208A0B0: .word 0x00006C21
_0208A0B4: .word 0x020FF3E4

	thumb_func_start FUN_0208A0B8
FUN_0208A0B8: ; 0x0208A0B8
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0208A0C6
	mov r6, #0x1
	b _0208A0C8
_0208A0C6:
	mov r6, #0x0
_0208A0C8:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	bl FUN_02015EF4
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
	ldr r0, _0208A228 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0208A22C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _0208A230 ; =0x021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _0208A234 ; =0x04000050
	mov r1, #0x0
	strh r1, [r3, #0x0]
	ldr r0, _0208A238 ; =0x04001050
	sub r3, #0x50
	strh r1, [r0, #0x0]
	ldr r2, [r3, #0x0]
	ldr r1, _0208A23C ; =0xFFFF1FFF
	sub r0, #0x50
	and r2, r1
	str r2, [r3, #0x0]
	ldr r2, [r0, #0x0]
	and r1, r2
	str r1, [r0, #0x0]
	ldr r0, _0208A240 ; =0x020FF474
	bl FUN_0201E66C
	add r0, r4, #0x0
	bl FUN_02016B94
	add r5, r0, #0x0
	ldr r0, _0208A244 ; =0x020FF448
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _0208A248 ; =0x020FF458
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _0208A24C ; =0x000001F7
	add r0, r5, #0x0
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _0208A250 ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _0208A250 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x6
	add r3, r4, #0x0
	bl FUN_0200A86C
	add r7, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r2, _0208A254 ; =0x020FF440
	add r0, r5, #0x0
	add r1, sp, #0xc
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0xc
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _0208A24C ; =0x000001F7
	add r0, sp, #0xc
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0200A8E0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0xc
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl FUN_02021A20
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	mov r4, #0x1
_0208A21A:
	bl FUN_02000FE8
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl OS_WaitIrq
	b _0208A21A
	.balign 4
_0208A228: .word 0xFFFFE0FF
_0208A22C: .word 0x04001000
_0208A230: .word 0x021C4918
_0208A234: .word 0x04000050
_0208A238: .word 0x04001050
_0208A23C: .word 0xFFFF1FFF
_0208A240: .word 0x020FF474
_0208A244: .word 0x020FF448
_0208A248: .word 0x020FF458
_0208A24C: .word 0x000001F7
_0208A250: .word 0x00006C21
_0208A254: .word 0x020FF440

	thumb_func_start FUN_0208A258
FUN_0208A258: ; 0x0208A258
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, _0208A290 ; =0x0000022F
	ldrb r0, [r4, r0]
	cmp r0, #0x10
	beq _0208A278
	cmp r0, #0x11
	beq _0208A286
	b _0208A28C
_0208A278:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0208A294
	ldr r1, _0208A290 ; =0x0000022F
	strb r0, [r4, r1]
	b _0208A28C
_0208A286:
	add r0, r5, #0x0
	bl FUN_0208A2C4
_0208A28C:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0208A290: .word 0x0000022F

	thumb_func_start FUN_0208A294
FUN_0208A294: ; 0x0208A294
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0208A2A6
	mov r0, #0x10
	pop {r3-r5, pc}
_0208A2A6:
	ldr r0, [r4, #0x4]
	bl FUN_0206E394
	mov r1, #0x9
	lsl r1, r1, #0x6
	strb r0, [r4, r1]
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r5, #0x0
	bl FUN_0204649C
	mov r0, #0x11
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0208A2C4
FUN_0208A2C4: ; 0x0208A2C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020464A4
	cmp r0, #0x0
	beq _0208A2F6
	mov r0, #0x1
	bl MOD05_021D7CA4
	ldr r1, _0208A2F8 ; =0x0223D4AD
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463EC
	ldr r0, _0208A2FC ; =0x0000022F
	mov r1, #0x12
	strb r1, [r4, r0]
_0208A2F6:
	pop {r4-r6, pc}
	.balign 4
_0208A2F8: .word 0x0223D4AD
_0208A2FC: .word 0x0000022F

	thumb_func_start FUN_0208A300
FUN_0208A300: ; 0x0208A300
	push {r3, lr}
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	mov r1, #0x2
	str r1, [r0, #0x4]
	pop {r3, pc}

	thumb_func_start FUN_0208A320
FUN_0208A320: ; 0x0208A320
	ldr r3, _0208A324 ; =FUN_02016A18
	bx r3
	.balign 4
_0208A324: .word FUN_02016A18

	thumb_func_start FUN_0208A328
FUN_0208A328: ; 0x0208A328
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0208A32C
FUN_0208A32C: ; 0x0208A32C
	str r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0208A330
FUN_0208A330: ; 0x0208A330
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0208A334
FUN_0208A334: ; 0x0208A334
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0208A338
FUN_0208A338: ; 0x0208A338
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	mov r0, #0x20
	mov r1, #0x6c
	bl FUN_02016998
	add r4, r0, #0x0
	mov r0, #0x19
	str r5, [r4, #0x0]
	lsl r0, r0, #0x4
	mov r1, #0x20
	bl FUN_020219F4
	str r0, [r4, #0x4]
	mov r0, #0x19
	lsl r0, r0, #0x4
	mov r1, #0x20
	bl FUN_020219F4
	str r0, [r4, #0x8]
	mov r0, #0x20
	bl FUN_0200AA80
	str r0, [r4, #0xc]
	ldr r2, _0208A3C0 ; =0x00000171
	mov r0, #0x1
	mov r1, #0x1a
	mov r3, #0x20
	bl FUN_0200A86C
	str r0, [r4, #0x10]
	mov r0, #0x20
	bl FUN_02013690
	str r0, [r4, #0x14]
	ldr r2, [r4, #0x0]
	mov r0, #0x2
	ldr r2, [r2, #0xc]
	mov r1, #0x0
	mov r3, #0x20
	bl FUN_02085338
	str r0, [r4, #0x50]
	bl FUN_020853DC
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_0201901C
	add r0, r4, #0x0
	add r0, #0x28
	bl FUN_0201901C
	add r0, r4, #0x0
	add r0, #0x38
	bl FUN_0201901C
	mov r0, #0x0
	str r0, [r4, #0x54]
	ldr r1, _0208A3C4 ; =FUN_0208A458
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r4-r6, pc}
	.balign 4
_0208A3C0: .word 0x00000171
_0208A3C4: .word FUN_0208A458

	thumb_func_start FUN_0208A3C8
FUN_0208A3C8: ; 0x0208A3C8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x50]
	bl FUN_020853A8
	ldr r0, [r4, #0x14]
	bl FUN_020136C0
	ldr r0, [r4, #0x4]
	bl FUN_02021A20
	ldr r0, [r4, #0x8]
	bl FUN_02021A20
	ldr r0, [r4, #0xc]
	bl FUN_0200AB18
	ldr r0, [r4, #0x10]
	bl FUN_0200A8B8
	add r0, r4, #0x0
	bl FUN_0208A400
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0208A400
FUN_0208A400: ; 0x0208A400
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x18
	bl FUN_02019048
	cmp r0, #0x0
	beq _0208A41E
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_02019178
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_0201901C
_0208A41E:
	add r0, r4, #0x0
	add r0, #0x28
	bl FUN_02019048
	cmp r0, #0x0
	beq _0208A43A
	add r0, r4, #0x0
	add r0, #0x28
	bl FUN_02019178
	add r0, r4, #0x0
	add r0, #0x28
	bl FUN_0201901C
_0208A43A:
	add r0, r4, #0x0
	add r0, #0x38
	bl FUN_02019048
	cmp r0, #0x0
	beq _0208A456
	add r0, r4, #0x0
	add r0, #0x38
	bl FUN_02019178
	add r4, #0x38
	add r0, r4, #0x0
	bl FUN_0201901C
_0208A456:
	pop {r4, pc}

	thumb_func_start FUN_0208A458
FUN_0208A458: ; 0x0208A458
	push {r3-r5, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x54]
	cmp r1, #0xd
	bhi _0208A4A4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0208A472: ; jump table (using 16-bit offset)
	.short _0208A48E - _0208A472 - 2; case 0
	.short _0208A49C - _0208A472 - 2; case 1
	.short _0208A4B8 - _0208A472 - 2; case 2
	.short _0208A556 - _0208A472 - 2; case 3
	.short _0208A566 - _0208A472 - 2; case 4
	.short _0208A57A - _0208A472 - 2; case 5
	.short _0208A5A6 - _0208A472 - 2; case 6
	.short _0208A5BE - _0208A472 - 2; case 7
	.short _0208A5D4 - _0208A472 - 2; case 8
	.short _0208A614 - _0208A472 - 2; case 9
	.short _0208A628 - _0208A472 - 2; case 10
	.short _0208A694 - _0208A472 - 2; case 11
	.short _0208A6A2 - _0208A472 - 2; case 12
	.short _0208A6C0 - _0208A472 - 2; case 13
_0208A48E:
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_0208A6D4
	mov r0, #0x1
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A49C:
	bl FUN_0208A750
	cmp r0, #0x0
	bne _0208A4A6
_0208A4A4:
	b _0208A6C8
_0208A4A6:
	add r0, r4, #0x0
	bl FUN_0208A760
	add r0, r4, #0x0
	bl FUN_0208A77C
	mov r0, #0x2
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A4B8:
	bl FUN_0208A8DC
	mov r1, #0x0
	mvn r1, r1
	str r0, [r4, #0x64]
	cmp r0, r1
	beq _0208A5B0
	add r0, r4, #0x0
	bl FUN_0208A820
	ldr r0, [r4, #0x64]
	cmp r0, #0x4
	bhi _0208A5B0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0208A4DE: ; jump table (using 16-bit offset)
	.short _0208A4E8 - _0208A4DE - 2; case 0
	.short _0208A502 - _0208A4DE - 2; case 1
	.short _0208A51C - _0208A4DE - 2; case 2
	.short _0208A536 - _0208A4DE - 2; case 3
	.short _0208A550 - _0208A4DE - 2; case 4
_0208A4E8:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0xc]
	bl FUN_0202A5F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x48
	bl FUN_02013960
	mov r0, #0x3
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A502:
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0xc]
	bl FUN_0202A5F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x48
	bl FUN_02013960
	mov r0, #0x3
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A51C:
	ldr r0, [r4, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0xc]
	bl FUN_0202A5F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x48
	bl FUN_02013960
	mov r0, #0x3
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A536:
	ldr r0, [r4, #0x0]
	mov r1, #0x3
	ldr r0, [r0, #0xc]
	bl FUN_0202A5F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x48
	bl FUN_02013960
	mov r0, #0x3
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A550:
	mov r0, #0xb
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A556:
	ldr r1, [r4, #0x64]
	mov r2, #0x0
	add r1, r1, #0x1
	bl FUN_0208A6D4
	mov r0, #0x4
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A566:
	bl FUN_0208A750
	cmp r0, #0x0
	beq _0208A5B0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x5
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A57A:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0208A5B0
	add r1, r4, #0x0
	ldr r0, [r4, #0x50]
	add r1, #0x48
	bl FUN_020853BC
	ldr r0, [r4, #0x50]
	bl FUN_020853D0
	add r0, r4, #0x0
	bl FUN_0208A400
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x50]
	bl FUN_02037E80
	mov r0, #0x6
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A5A6:
	ldr r0, [r4, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0208A5B2
_0208A5B0:
	b _0208A6C8
_0208A5B2:
	ldr r0, [r4, #0x0]
	bl FUN_0204649C
	mov r0, #0x7
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A5BE:
	ldr r0, [r4, #0x0]
	bl FUN_020464A4
	cmp r0, #0x0
	beq _0208A6C8
	mov r0, #0x1
	bl MOD05_021D7CA4
	mov r0, #0x8
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A5D4:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0208A6C8
	ldr r0, [r4, #0x50]
	bl FUN_020853E4
	cmp r0, #0x0
	beq _0208A5EC
	mov r0, #0xb
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A5EC:
	add r1, r4, #0x0
	ldr r0, [r4, #0x50]
	add r1, #0x48
	bl FUN_020853FC
	ldr r0, [r4, #0x0]
	add r2, r4, #0x0
	ldr r0, [r0, #0xc]
	ldr r1, [r4, #0x64]
	add r2, #0x48
	bl FUN_0202A5D4
	add r0, r4, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_0208A6D4
	mov r0, #0x9
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A614:
	bl FUN_0208A750
	cmp r0, #0x0
	beq _0208A6C8
	add r0, r4, #0x0
	bl FUN_0208A82C
	mov r0, #0xa
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A628:
	bl FUN_0208A8DC
	mov r1, #0x0
	mvn r1, r1
	str r0, [r4, #0x64]
	cmp r0, r1
	beq _0208A6C8
	cmp r0, #0x0
	beq _0208A63E
	cmp r0, #0x1
	b _0208A656
_0208A63E:
	add r0, r4, #0x0
	bl FUN_0208A8D0
	add r0, r4, #0x0
	bl FUN_0208A760
	add r0, r4, #0x0
	bl FUN_0208A77C
	mov r0, #0x2
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A656:
	add r0, r4, #0x0
	add r0, #0x48
	mov r1, #0x0
	bl FUN_02013918
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0208A8D0
	ldr r0, _0208A6CC ; =0x0000FFFF
	cmp r5, r0
	beq _0208A684
	ldr r0, [r4, #0xc]
	mov r1, #0x0
	add r2, r5, #0x0
	bl FUN_0200B518
	add r0, r4, #0x0
	mov r1, #0x8
	mov r2, #0x1
	bl FUN_0208A6D4
	b _0208A68E
_0208A684:
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_0208A6D4
_0208A68E:
	mov r0, #0xc
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A694:
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_0208A6D4
	mov r0, #0xc
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A6A2:
	bl FUN_0208A750
	cmp r0, #0x0
	beq _0208A6C8
	ldr r0, _0208A6D0 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0xf3
	tst r0, r1
	beq _0208A6C8
	add r0, r4, #0x0
	bl FUN_0208A760
	mov r0, #0xd
	str r0, [r4, #0x54]
	b _0208A6C8
_0208A6C0:
	bl FUN_0208A3C8
	mov r0, #0x1
	pop {r3-r5, pc}
_0208A6C8:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0208A6CC: .word 0x0000FFFF
_0208A6D0: .word 0x021C48B8

	thumb_func_start FUN_0208A6D4
FUN_0208A6D4: ; 0x0208A6D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r5, #0x0
	add r4, #0x18
	cmp r2, #0x0
	ldr r0, [r5, #0x10]
	beq _0208A6F4
	ldr r2, [r5, #0x4]
	bl FUN_0200A8E0
	ldr r0, [r5, #0xc]
	ldr r1, [r5, #0x8]
	ldr r2, [r5, #0x4]
	bl FUN_0200B7B8
	b _0208A6FA
_0208A6F4:
	ldr r2, [r5, #0x8]
	bl FUN_0200A8E0
_0208A6FA:
	add r0, r4, #0x0
	bl FUN_02019048
	cmp r0, #0x0
	bne _0208A722
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x8]
	mov r2, #0x3
	bl FUN_020545B8
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02054608
	b _0208A734
_0208A722:
	add r0, r4, #0x0
	bl FUN_0205464C
	ldr r2, _0208A74C ; =0x000003E2
	add r0, r4, #0x0
	mov r1, #0x0
	mov r3, #0xa
	bl FUN_0200D0BC
_0208A734:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r2, r0, #0x0
	ldr r1, [r5, #0x8]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	str r0, [r5, #0x58]
	pop {r3-r5, pc}
	.balign 4
_0208A74C: .word 0x000003E2

	thumb_func_start FUN_0208A750
FUN_0208A750: ; 0x0208A750
	ldr r0, [r0, #0x58]
	ldr r3, _0208A75C ; =FUN_020546C8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx r3
	nop
_0208A75C: .word FUN_020546C8

	thumb_func_start FUN_0208A760
FUN_0208A760: ; 0x0208A760
	push {r4, lr}
	add r4, r0, #0x0
	add r4, #0x18
	add r0, r4, #0x0
	bl FUN_02019048
	cmp r0, #0x0
	beq _0208A778
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200D0E0
_0208A778:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0208A77C
FUN_0208A77C: ; 0x0208A77C
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r7, r5, #0x0
	add r7, #0x28
	add r0, r7, #0x0
	bl FUN_02019048
	cmp r0, #0x0
	bne _0208A808
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	ldr r0, [r0, #0x8]
	mov r2, #0xa5
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0xd
	str r1, [sp, #0x0]
	mov r0, #0xe
	str r0, [sp, #0x4]
	mov r0, #0xa
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x8]
	mov r2, #0x3
	mov r3, #0x11
	bl FUN_02019064
	add r0, r7, #0x0
	mov r1, #0xf
	bl FUN_02019620
	mov r6, #0x0
	add r4, r6, #0x0
_0208A7D2:
	add r1, r6, #0x0
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x8]
	add r1, #0x9
	bl FUN_0200A8E0
	str r4, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r2, [r5, #0x8]
	add r0, r7, #0x0
	mov r1, #0x0
	mov r3, #0xc
	bl FUN_0201BD84
	add r6, r6, #0x1
	add r4, #0x10
	cmp r6, #0x5
	blt _0208A7D2
	mov r2, #0x0
	ldr r0, [r5, #0x14]
	add r1, r7, #0x0
	add r3, r2, #0x0
	bl FUN_020136F8
_0208A808:
	str r7, [r5, #0x68]
	mov r1, #0x0
	str r1, [r5, #0x5c]
	mov r0, #0x5
	str r0, [r5, #0x60]
	add r0, r7, #0x0
	mov r2, #0xa5
	mov r3, #0xb
	bl FUN_0200CCA4
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0208A820
FUN_0208A820: ; 0x0208A820
	ldr r3, _0208A828 ; =FUN_0200CCF8
	add r0, #0x28
	mov r1, #0x1
	bx r3
	.balign 4
_0208A828: .word FUN_0200CCF8

	thumb_func_start FUN_0208A82C
FUN_0208A82C: ; 0x0208A82C
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r7, r5, #0x0
	add r7, #0x38
	add r0, r7, #0x0
	bl FUN_02019048
	cmp r0, #0x0
	bne _0208A8B8
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	ldr r0, [r0, #0x8]
	mov r2, #0xa5
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0xd
	str r1, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	mov r0, #0x8d
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x8]
	mov r2, #0x3
	mov r3, #0x19
	bl FUN_02019064
	add r0, r7, #0x0
	mov r1, #0xf
	bl FUN_02019620
	mov r6, #0x0
	add r4, r6, #0x0
_0208A882:
	add r1, r6, #0x0
	ldr r0, [r5, #0x10]
	ldr r2, [r5, #0x8]
	add r1, #0xe
	bl FUN_0200A8E0
	str r4, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r2, [r5, #0x8]
	add r0, r7, #0x0
	mov r1, #0x0
	mov r3, #0xc
	bl FUN_0201BD84
	add r6, r6, #0x1
	add r4, #0x10
	cmp r6, #0x2
	blt _0208A882
	mov r2, #0x0
	ldr r0, [r5, #0x14]
	add r1, r7, #0x0
	add r3, r2, #0x0
	bl FUN_020136F8
_0208A8B8:
	str r7, [r5, #0x68]
	mov r1, #0x0
	str r1, [r5, #0x5c]
	mov r0, #0x2
	str r0, [r5, #0x60]
	add r0, r7, #0x0
	mov r2, #0xa5
	mov r3, #0xb
	bl FUN_0200CCA4
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0208A8D0
FUN_0208A8D0: ; 0x0208A8D0
	ldr r3, _0208A8D8 ; =FUN_0200CCF8
	add r0, #0x38
	mov r1, #0x1
	bx r3
	.balign 4
_0208A8D8: .word FUN_0200CCF8

	thumb_func_start FUN_0208A8DC
FUN_0208A8DC: ; 0x0208A8DC
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r0, _0208A990 ; =0x021C48B8
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0208A906
	ldr r0, [r4, #0x5c]
	sub r0, r0, #0x1
	str r0, [r4, #0x5c]
	bpl _0208A954
	ldr r0, [r4, #0x60]
	cmp r0, #0x2
	ble _0208A900
	sub r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _0208A954
_0208A900:
	mov r0, #0x0
	str r0, [r4, #0x5c]
	b _0208A954
_0208A906:
	mov r1, #0x80
	tst r1, r0
	beq _0208A928
	ldr r0, [r4, #0x5c]
	add r1, r0, #0x1
	str r1, [r4, #0x5c]
	ldr r0, [r4, #0x60]
	cmp r1, r0
	blt _0208A954
	cmp r0, #0x2
	ble _0208A922
	mov r0, #0x0
	str r0, [r4, #0x5c]
	b _0208A954
_0208A922:
	sub r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _0208A954
_0208A928:
	mov r1, #0x1
	tst r1, r0
	beq _0208A93A
	ldr r0, _0208A994 ; =0x000005DC
	bl FUN_020054C8
	add sp, #0x8
	ldr r0, [r4, #0x5c]
	pop {r4, pc}
_0208A93A:
	mov r1, #0x2
	tst r0, r1
	beq _0208A94E
	ldr r0, _0208A994 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, [r4, #0x60]
	add sp, #0x8
	sub r0, r0, #0x1
	pop {r4, pc}
_0208A94E:
	add sp, #0x8
	sub r0, r1, #0x3
	pop {r4, pc}
_0208A954:
	ldr r0, [r4, #0x68]
	mov r1, #0xc
	str r1, [sp, #0x0]
	ldrb r1, [r0, #0x8]
	mov r2, #0x0
	add r3, r2, #0x0
	lsl r1, r1, #0x13
	lsr r1, r1, #0x10
	str r1, [sp, #0x4]
	mov r1, #0xf
	bl FUN_020196F4
	ldr r3, [r4, #0x5c]
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x68]
	mov r2, #0x0
	lsl r3, r3, #0x4
	bl FUN_020136F8
	ldr r0, [r4, #0x68]
	bl FUN_02019548
	ldr r0, _0208A994 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x0
	mvn r0, r0
	add sp, #0x8
	pop {r4, pc}
	nop
_0208A990: .word 0x021C48B8
_0208A994: .word 0x000005DC

	thumb_func_start FUN_0208A998
FUN_0208A998: ; 0x0208A998
	ldr r3, _0208A9AC ; =0x027E0000
	ldr r1, _0208A9B0 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	ldr r3, _0208A9B4 ; =MI_WaitDma
	mov r0, #0x3
	bx r3
	nop
_0208A9AC: .word 0x027E0000
_0208A9B0: .word 0x00003FF8
_0208A9B4: .word MI_WaitDma

	thumb_func_start FUN_0208A9B8
FUN_0208A9B8: ; 0x0208A9B8
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r0, _0208ABC8 ; =0x021C8C58
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
	ldr r0, _0208ABCC ; =0x020FF4A4
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
	ldr r0, _0208ABDC ; =0x021C4918
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
	ldr r0, _0208ABEC ; =0x020FF4D8
	bl FUN_0201E66C
	mov r0, #0x0
	bl FUN_02016B94
	str r0, [sp, #0x10]
	ldr r0, _0208ABF0 ; =0x020FF4AC
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r0, [sp, #0x10]
	ldr r2, _0208ABF4 ; =0x020FF4BC
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
	bl FUN_0200A86C
	str r0, [sp, #0xc]
	mov r0, #0x6
	lsl r0, r0, #0x6
	mov r1, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r0, [sp, #0x10]
	ldr r2, _0208AC00 ; =0x020FF49C
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
	bl FUN_0200A8E0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0x14
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl FUN_02021A20
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
	bl FUN_0200A8B8
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	mov r0, #0x0
	bl OS_ResetSystem
_0208ABC4:
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_0208ABC8: .word 0x021C8C58
_0208ABCC: .word 0x020FF4A4
_0208ABD0: .word FUN_0208A998
_0208ABD4: .word 0xFFFFE0FF
_0208ABD8: .word 0x04001000
_0208ABDC: .word 0x021C4918
_0208ABE0: .word 0x04000050
_0208ABE4: .word 0x04001050
_0208ABE8: .word 0xFFFF1FFF
_0208ABEC: .word 0x020FF4D8
_0208ABF0: .word 0x020FF4AC
_0208ABF4: .word 0x020FF4BC
_0208ABF8: .word 0x000001F7
_0208ABFC: .word 0x00006C21
_0208AC00: .word 0x020FF49C
_0208AC04: .word 0x04000130
_0208AC08: .word 0x027FFFA8
_0208AC0C: .word 0x00002FFF
_0208AC10: .word 0x00007FFF
