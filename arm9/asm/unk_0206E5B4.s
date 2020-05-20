    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206E5B4
FUN_0206E5B4: ; 0x0206E5B4
	push {r3-r6}
	add r3, r0, #0x0
	add r0, r2, #0x0
	cmp r1, r0
	beq _0206E63A
	lsl r2, r1, #0x2
	ldrh r4, [r3, r2]
	add r5, r3, r2
	add r2, sp, #0x0
	strh r4, [r2, #0x0]
	ldrh r4, [r5, #0x2]
	strh r4, [r2, #0x2]
	cmp r0, r1
	bls _0206E600
	sub r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r1, r1, #0x10
	lsl r2, r0, #0x10
	asr r1, r1, #0x10
	asr r5, r2, #0x10
	cmp r1, r5
	bge _0206E62C
	lsl r2, r1, #0x2
	add r2, r3, r2
	add r4, r2, #0x0
_0206E5E8:
	ldrh r6, [r2, #0x4]
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	strh r6, [r4, #0x0]
	ldrh r6, [r2, #0x6]
	asr r1, r1, #0x10
	add r2, r2, #0x4
	strh r6, [r4, #0x2]
	add r4, r4, #0x4
	cmp r1, r5
	blt _0206E5E8
	b _0206E62C
_0206E600:
	lsl r1, r1, #0x10
	asr r5, r1, #0x10
	lsl r1, r0, #0x10
	asr r4, r1, #0x10
	cmp r5, r4
	ble _0206E62C
	lsl r1, r5, #0x2
	add r1, r3, r1
	add r2, r1, #0x0
_0206E612:
	sub r6, r1, #0x4
	ldrh r6, [r6, #0x0]
	sub r5, r5, #0x1
	lsl r5, r5, #0x10
	strh r6, [r2, #0x0]
	sub r6, r1, #0x2
	ldrh r6, [r6, #0x0]
	asr r5, r5, #0x10
	sub r1, r1, #0x4
	strh r6, [r2, #0x2]
	sub r2, r2, #0x4
	cmp r5, r4
	bgt _0206E612
_0206E62C:
	lsl r4, r0, #0x2
	add r0, sp, #0x0
	ldrh r1, [r0, #0x0]
	add r2, r3, r4
	strh r1, [r3, r4]
	ldrh r0, [r0, #0x2]
	strh r0, [r2, #0x2]
_0206E63A:
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_0206E640
FUN_0206E640: ; 0x0206E640
	cmp r1, #0x3
	bhi _0206E6B2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206E650: ; jump table (using 16-bit offset)
	.short _0206E658 - _0206E650 - 2; case 0
	.short _0206E66A - _0206E650 - 2; case 1
	.short _0206E684 - _0206E650 - 2; case 2
	.short _0206E6A0 - _0206E650 - 2; case 3
_0206E658:
	cmp r0, #0x0
	beq _0206E6B2
	ldr r1, _0206E6B8 ; =0x0000FFFF
	cmp r0, r1
	beq _0206E6B2
	lsl r1, r0, #0x3
	ldr r0, _0206E6BC ; =0x020F85B4
	ldrh r0, [r0, r1]
	bx lr
_0206E66A:
	cmp r0, #0x0
	bne _0206E672
	ldr r0, _0206E6C0 ; =0x000002BB
	bx lr
_0206E672:
	ldr r1, _0206E6B8 ; =0x0000FFFF
	cmp r0, r1
	bne _0206E67C
	ldr r0, _0206E6C4 ; =0x000002BD
	bx lr
_0206E67C:
	lsl r1, r0, #0x3
	ldr r0, _0206E6C8 ; =0x020F85B6
	ldrh r0, [r0, r1]
	bx lr
_0206E684:
	cmp r0, #0x0
	bne _0206E68E
	mov r0, #0xaf
	lsl r0, r0, #0x2
	bx lr
_0206E68E:
	ldr r1, _0206E6B8 ; =0x0000FFFF
	cmp r0, r1
	bne _0206E698
	ldr r0, _0206E6CC ; =0x000002BE
	bx lr
_0206E698:
	lsl r1, r0, #0x3
	ldr r0, _0206E6D0 ; =0x020F85B8
	ldrh r0, [r0, r1]
	bx lr
_0206E6A0:
	cmp r0, #0x0
	beq _0206E6B2
	ldr r1, _0206E6B8 ; =0x0000FFFF
	cmp r0, r1
	beq _0206E6B2
	lsl r1, r0, #0x3
	ldr r0, _0206E6D4 ; =0x020F85BA
	ldrh r0, [r0, r1]
	bx lr
_0206E6B2:
	mov r0, #0x0
	bx lr
	nop
_0206E6B8: .word 0x0000FFFF
_0206E6BC: .word 0x020F85B4
_0206E6C0: .word 0x000002BB
_0206E6C4: .word 0x000002BD
_0206E6C8: .word 0x020F85B6
_0206E6CC: .word 0x000002BE
_0206E6D0: .word 0x020F85B8
_0206E6D4: .word 0x020F85BA

	thumb_func_start FUN_0206E6D8
FUN_0206E6D8: ; 0x0206E6D8
	push {r3-r4}
	mov r2, #0x1d
	ldr r3, _0206E704 ; =0x020F85B4
	mov r4, #0x1
	lsl r2, r2, #0x4
_0206E6E2:
	lsl r1, r4, #0x3
	add r1, r3, r1
	ldrh r1, [r1, #0x6]
	cmp r0, r1
	bne _0206E6F2
	add r0, r4, #0x0
	pop {r3-r4}
	bx lr
_0206E6F2:
	add r1, r4, #0x1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r4, r2
	bls _0206E6E2
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0206E704: .word 0x020F85B4

	thumb_func_start FUN_0206E708
FUN_0206E708: ; 0x0206E708
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0206E70C
FUN_0206E70C: ; 0x0206E70C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0206E710
FUN_0206E710: ; 0x0206E710
	push {r3, lr}
	add r3, r0, #0x0
	mov r0, #0x1d
	lsl r0, r0, #0x4
	cmp r3, r0
	bls _0206E71E
	mov r3, #0x0
_0206E71E:
	cmp r1, #0x0
	beq _0206E72C
	cmp r1, #0x1
	beq _0206E73A
	cmp r1, #0x2
	beq _0206E748
	b _0206E756
_0206E72C:
	ldr r1, _0206E75C ; =0x020F85B4
	lsl r3, r3, #0x3
	ldrh r1, [r1, r3]
	mov r0, #0xf
	bl LoadFromNarc_2
	pop {r3, pc}
_0206E73A:
	ldr r1, _0206E760 ; =0x020F85B6
	lsl r3, r3, #0x3
	ldrh r1, [r1, r3]
	mov r0, #0x10
	bl LoadFromNarc_2
	pop {r3, pc}
_0206E748:
	ldr r1, _0206E764 ; =0x020F85B8
	lsl r3, r3, #0x3
	ldrh r1, [r1, r3]
	mov r0, #0x10
	bl LoadFromNarc_2
	pop {r3, pc}
_0206E756:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0206E75C: .word 0x020F85B4
_0206E760: .word 0x020F85B6
_0206E764: .word 0x020F85B8

	thumb_func_start FUN_0206E768
FUN_0206E768: ; 0x0206E768
	push {r4-r6, lr}
	add r3, r2, #0x0
	mov r2, #0x56
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	bl FUN_0200A86C
	add r6, r0, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0200A8E0
	add r0, r6, #0x0
	bl FUN_0200A8B8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206E790
FUN_0206E790: ; 0x0206E790
	push {r4-r6, lr}
	add r3, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r2, _0206E7B4 ; =0x00000157
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	add r6, r0, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0200A8E0
	add r0, r6, #0x0
	bl FUN_0200A8B8
	pop {r4-r6, pc}
	.balign 4
_0206E7B4: .word 0x00000157

	thumb_func_start FUN_0206E7B8
FUN_0206E7B8: ; 0x0206E7B8
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	add r5, r2, #0x0
	bl FUN_0206E710
	add r6, r0, #0x0
	add r1, r4, #0x0
	bl FUN_0206E7DC
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02016A8C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206E7DC
FUN_0206E7DC: ; 0x0206E7DC
	push {r3, lr}
	cmp r1, #0xe
	bhi _0206E85C
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206E7EE: ; jump table (using 16-bit offset)
	.short _0206E80C - _0206E7EE - 2; case 0
	.short _0206E810 - _0206E7EE - 2; case 1
	.short _0206E814 - _0206E7EE - 2; case 2
	.short _0206E818 - _0206E7EE - 2; case 3
	.short _0206E820 - _0206E7EE - 2; case 4
	.short _0206E828 - _0206E7EE - 2; case 5
	.short _0206E830 - _0206E7EE - 2; case 6
	.short _0206E834 - _0206E7EE - 2; case 7
	.short _0206E838 - _0206E7EE - 2; case 8
	.short _0206E83C - _0206E7EE - 2; case 9
	.short _0206E840 - _0206E7EE - 2; case 10
	.short _0206E844 - _0206E7EE - 2; case 11
	.short _0206E848 - _0206E7EE - 2; case 12
	.short _0206E850 - _0206E7EE - 2; case 13
	.short _0206E858 - _0206E7EE - 2; case 14
_0206E80C:
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_0206E810:
	ldrb r0, [r0, #0x2]
	pop {r3, pc}
_0206E814:
	ldrb r0, [r0, #0x3]
	pop {r3, pc}
_0206E818:
	ldrh r0, [r0, #0x8]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	pop {r3, pc}
_0206E820:
	ldrh r0, [r0, #0x8]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	pop {r3, pc}
_0206E828:
	ldrh r0, [r0, #0x8]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1c
	pop {r3, pc}
_0206E830:
	ldrb r0, [r0, #0xa]
	pop {r3, pc}
_0206E834:
	ldrb r0, [r0, #0xb]
	pop {r3, pc}
_0206E838:
	ldrb r0, [r0, #0x4]
	pop {r3, pc}
_0206E83C:
	ldrb r0, [r0, #0x5]
	pop {r3, pc}
_0206E840:
	ldrb r0, [r0, #0x6]
	pop {r3, pc}
_0206E844:
	ldrb r0, [r0, #0x7]
	pop {r3, pc}
_0206E848:
	ldrh r0, [r0, #0x8]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1b
	pop {r3, pc}
_0206E850:
	ldrh r0, [r0, #0x8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1b
	pop {r3, pc}
_0206E858:
	ldrb r0, [r0, #0xc]
	pop {r3, pc}
_0206E85C:
	ldrb r2, [r0, #0xc]
	cmp r2, #0x0
	beq _0206E868
	cmp r2, #0x1
	beq _0206E86C
	b _0206E874
_0206E868:
	ldrb r0, [r0, #0xe]
	pop {r3, pc}
_0206E86C:
	add r0, #0xe
	bl FUN_0206E878
	pop {r3, pc}
_0206E874:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0206E878
FUN_0206E878: ; 0x0206E878
	sub r1, #0xf
	cmp r1, #0x2b
	bls _0206E880
	b _0206EA2A
_0206E880:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0206E88C: ; jump table (using 16-bit offset)
	.short _0206E8E4 - _0206E88C - 2; case 0
	.short _0206E8EC - _0206E88C - 2; case 1
	.short _0206E8F4 - _0206E88C - 2; case 2
	.short _0206E8FC - _0206E88C - 2; case 3
	.short _0206E904 - _0206E88C - 2; case 4
	.short _0206E90C - _0206E88C - 2; case 5
	.short _0206E914 - _0206E88C - 2; case 6
	.short _0206E91C - _0206E88C - 2; case 7
	.short _0206E924 - _0206E88C - 2; case 8
	.short _0206E92C - _0206E88C - 2; case 9
	.short _0206E934 - _0206E88C - 2; case 10
	.short _0206E93C - _0206E88C - 2; case 11
	.short _0206E944 - _0206E88C - 2; case 12
	.short _0206E94C - _0206E88C - 2; case 13
	.short _0206E954 - _0206E88C - 2; case 14
	.short _0206E95C - _0206E88C - 2; case 15
	.short _0206E964 - _0206E88C - 2; case 16
	.short _0206E96C - _0206E88C - 2; case 17
	.short _0206E974 - _0206E88C - 2; case 18
	.short _0206E97C - _0206E88C - 2; case 19
	.short _0206E984 - _0206E88C - 2; case 20
	.short _0206E98C - _0206E88C - 2; case 21
	.short _0206E994 - _0206E88C - 2; case 22
	.short _0206E99C - _0206E88C - 2; case 23
	.short _0206E9A4 - _0206E88C - 2; case 24
	.short _0206E9AC - _0206E88C - 2; case 25
	.short _0206E9B4 - _0206E88C - 2; case 26
	.short _0206E9BC - _0206E88C - 2; case 27
	.short _0206E9C4 - _0206E88C - 2; case 28
	.short _0206E9CC - _0206E88C - 2; case 29
	.short _0206E9D4 - _0206E88C - 2; case 30
	.short _0206E9DC - _0206E88C - 2; case 31
	.short _0206E9E4 - _0206E88C - 2; case 32
	.short _0206E9EC - _0206E88C - 2; case 33
	.short _0206E9F2 - _0206E88C - 2; case 34
	.short _0206E9F8 - _0206E88C - 2; case 35
	.short _0206E9FE - _0206E88C - 2; case 36
	.short _0206EA04 - _0206E88C - 2; case 37
	.short _0206EA0A - _0206E88C - 2; case 38
	.short _0206EA10 - _0206E88C - 2; case 39
	.short _0206EA14 - _0206E88C - 2; case 40
	.short _0206EA18 - _0206E88C - 2; case 41
	.short _0206EA1E - _0206E88C - 2; case 42
	.short _0206EA24 - _0206E88C - 2; case 43
_0206E8E4:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr
_0206E8EC:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr
_0206E8F4:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bx lr
_0206E8FC:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bx lr
_0206E904:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bx lr
_0206E90C:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	bx lr
_0206E914:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr
_0206E91C:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr
_0206E924:
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr
_0206E92C:
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr
_0206E934:
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bx lr
_0206E93C:
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bx lr
_0206E944:
	ldrb r0, [r0, #0x1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bx lr
_0206E94C:
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr
_0206E954:
	ldrb r0, [r0, #0x2]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bx lr
_0206E95C:
	ldrb r0, [r0, #0x3]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr
_0206E964:
	ldrb r0, [r0, #0x3]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bx lr
_0206E96C:
	ldrb r0, [r0, #0x4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr
_0206E974:
	ldrb r0, [r0, #0x4]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	bx lr
_0206E97C:
	ldrb r0, [r0, #0x4]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr
_0206E984:
	ldrb r0, [r0, #0x4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr
_0206E98C:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr
_0206E994:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr
_0206E99C:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bx lr
_0206E9A4:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bx lr
_0206E9AC:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bx lr
_0206E9B4:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	bx lr
_0206E9BC:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr
_0206E9C4:
	ldrb r0, [r0, #0x5]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr
_0206E9CC:
	ldrb r0, [r0, #0x6]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	bx lr
_0206E9D4:
	ldrb r0, [r0, #0x6]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr
_0206E9DC:
	ldrb r0, [r0, #0x6]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bx lr
_0206E9E4:
	ldrb r0, [r0, #0x6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	bx lr
_0206E9EC:
	mov r1, #0x7
	ldrsb r0, [r0, r1]
	bx lr
_0206E9F2:
	mov r1, #0x8
	ldrsb r0, [r0, r1]
	bx lr
_0206E9F8:
	mov r1, #0x9
	ldrsb r0, [r0, r1]
	bx lr
_0206E9FE:
	mov r1, #0xa
	ldrsb r0, [r0, r1]
	bx lr
_0206EA04:
	mov r1, #0xb
	ldrsb r0, [r0, r1]
	bx lr
_0206EA0A:
	mov r1, #0xc
	ldrsb r0, [r0, r1]
	bx lr
_0206EA10:
	ldrb r0, [r0, #0xd]
	bx lr
_0206EA14:
	ldrb r0, [r0, #0xe]
	bx lr
_0206EA18:
	mov r1, #0xf
	ldrsb r0, [r0, r1]
	bx lr
_0206EA1E:
	mov r1, #0x10
	ldrsb r0, [r0, r1]
	bx lr
_0206EA24:
	mov r1, #0x11
	ldrsb r0, [r0, r1]
	bx lr
_0206EA2A:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0206EA30
FUN_0206EA30: ; 0x0206EA30
	mov r2, #0x52
	lsl r2, r2, #0x2
	cmp r0, r2
	blo _0206EA40
	add r1, r2, #0x0
	add r1, #0x63
	cmp r0, r1
	bls _0206EA44
_0206EA40:
	mov r0, #0x0
	bx lr
_0206EA44:
	sub r0, r0, r2
	lsl r0, r0, #0x10
	lsr r1, r0, #0xf
	ldr r0, _0206EA50 ; =0x020F84EC
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_0206EA50: .word 0x020F84EC

	thumb_func_start FUN_0206EA54
FUN_0206EA54: ; 0x0206EA54
	ldr r2, _0206EA78 ; =0x020F84EC
	mov r3, #0x0
_0206EA58:
	lsl r1, r3, #0x1
	add r1, r2, r1
	add r1, #0xb8
	ldrh r1, [r1, #0x0]
	cmp r0, r1
	bne _0206EA68
	mov r0, #0x1
	bx lr
_0206EA68:
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x8
	blo _0206EA58
	mov r0, #0x0
	bx lr
	nop
_0206EA78: .word 0x020F84EC

	thumb_func_start FUN_0206EA7C
FUN_0206EA7C: ; 0x0206EA7C
	mov r2, #0x52
	lsl r2, r2, #0x2
	cmp r0, r2
	blo _0206EA8C
	add r1, r2, #0x0
	add r1, #0x63
	cmp r0, r1
	bls _0206EA90
_0206EA8C:
	mov r0, #0x0
	bx lr
_0206EA90:
	sub r0, r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_0206EA98
FUN_0206EA98: ; 0x0206EA98
	ldr r3, _0206EAB4 ; =0x020F8454
	mov r2, #0x0
_0206EA9C:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _0206EAA6
	mov r0, #0x1
	bx lr
_0206EAA6:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0xc
	blo _0206EA9C
	mov r0, #0x0
	bx lr
	nop
_0206EAB4: .word 0x020F8454

	thumb_func_start FUN_0206EAB8
FUN_0206EAB8: ; 0x0206EAB8
	ldr r3, _0206EAD4 ; =0x020F8454
	mov r2, #0x0
_0206EABC:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _0206EAC8
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	bx lr
_0206EAC8:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0xc
	blo _0206EABC
	mov r0, #0x0
	bx lr
	.balign 4
_0206EAD4: .word 0x020F8454

	thumb_func_start FUN_0206EAD8
FUN_0206EAD8: ; 0x0206EAD8
	cmp r0, #0xc
	blo _0206EAE0
	mov r0, #0x0
	bx lr
_0206EAE0:
	lsl r1, r0, #0x1
	ldr r0, _0206EAE8 ; =0x020F8454
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_0206EAE8: .word 0x020F8454

	thumb_func_start FUN_0206EAEC
FUN_0206EAEC: ; 0x0206EAEC
	ldr r3, _0206EB08 ; =0x020F846C
	mov r2, #0x0
_0206EAF0:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _0206EAFA
	mov r0, #0x1
	bx lr
_0206EAFA:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x40
	blo _0206EAF0
	mov r0, #0x0
	bx lr
	nop
_0206EB08: .word 0x020F846C

	thumb_func_start FUN_0206EB0C
FUN_0206EB0C: ; 0x0206EB0C
	cmp r0, #0x95
	bhs _0206EB14
	mov r0, #0xff
	bx lr
_0206EB14:
	sub r0, #0x95
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_0206EB1C
FUN_0206EB1C: ; 0x0206EB1C
	cmp r0, #0x40
	blo _0206EB24
	ldr r0, _0206EB2C ; =0x0000FFFF
	bx lr
_0206EB24:
	lsl r1, r0, #0x1
	ldr r0, _0206EB30 ; =0x020F846C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_0206EB2C: .word 0x0000FFFF
_0206EB30: .word 0x020F846C

	thumb_func_start FUN_0206EB34
FUN_0206EB34: ; 0x0206EB34
	ldr r1, _0206EB4C ; =0x0000FFDE
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x3
	bhi _0206EB44
	mov r0, #0x1
	b _0206EB46
_0206EB44:
	mov r0, #0x0
_0206EB46:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4
_0206EB4C: .word 0x0000FFDE

	thumb_func_start FUN_0206EB50
FUN_0206EB50: ; 0x0206EB50
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x1d
	lsl r0, r0, #0x4
	mov r1, #0x0
	bl FUN_0206E640
	mov r1, #0x24
	mul r1, r0
	str r1, [sp, #0x0]
	mov r1, #0x0
	mov r0, #0xf
	add r2, r4, #0x0
	add r3, r1, #0x0
	bl FUN_02006564
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0206EB78
FUN_0206EB78: ; 0x0206EB78
	mov r2, #0x24
	mul r2, r1
	add r0, r0, r2
	bx lr
