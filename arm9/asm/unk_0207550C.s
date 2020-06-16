    .include "asm/macros.inc"
    .include "global.inc"

	.extern gUnknown21C48B8

	.text

	thumb_func_start FUN_0207550C
FUN_0207550C: ; 0x0207550C
	push {r3-r5, lr}
	mov r1, #0x0
	mov r2, #0xc
	bl FUN_0206E710
	mov r1, #0xe
	add r4, r0, #0x0
	bl FUN_0206E7DC
	cmp r0, #0x1
	beq _0207552C
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1c
	pop {r3-r5, pc}
_0207552C:
	add r0, r4, #0x0
	mov r1, #0x1b
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02075580
	add r0, r4, #0x0
	mov r1, #0x1c
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02075580
	add r0, r4, #0x0
	mov r1, #0x1d
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02075580
	add r0, r4, #0x0
	mov r1, #0x1e
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02075580
	add r0, r4, #0x0
	mov r1, #0x1f
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02075580
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02075580
	add r0, r4, #0x0
	mov r1, #0x21
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0207558A
_02075580:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_0207558A:
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020755A0
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_020755A0:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020755B6
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x2
	pop {r3-r5, pc}
_020755B6:
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_0206E7DC
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_0206E7DC
	lsl r0, r0, #0x1
	add r5, r5, r0
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_0206E7DC
	lsl r0, r0, #0x2
	add r5, r5, r0
	add r0, r4, #0x0
	mov r1, #0x12
	bl FUN_0206E7DC
	lsl r0, r0, #0x3
	add r5, r5, r0
	add r0, r4, #0x0
	mov r1, #0x13
	bl FUN_0206E7DC
	lsl r0, r0, #0x4
	add r5, r5, r0
	add r0, r4, #0x0
	mov r1, #0x14
	bl FUN_0206E7DC
	lsl r0, r0, #0x5
	add r5, r5, r0
	cmp r5, #0x10
	bgt _02075624
	bge _0207565A
	cmp r5, #0x8
	bhi _0207568E
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02075612: ; jump table (using 16-bit offset)
	.short _0207568E - _02075612 - 2; case 0
	.short _02075632 - _02075612 - 2; case 1
	.short _0207563C - _02075612 - 2; case 2
	.short _0207568E - _02075612 - 2; case 3
	.short _02075646 - _02075612 - 2; case 4
	.short _0207568E - _02075612 - 2; case 5
	.short _0207568E - _02075612 - 2; case 6
	.short _0207568E - _02075612 - 2; case 7
	.short _02075650 - _02075612 - 2; case 8
_02075624:
	cmp r5, #0x20
	bgt _0207562C
	beq _02075664
	b _0207568E
_0207562C:
	cmp r5, #0x3f
	beq _0207566E
	b _0207568E
_02075632:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x3
	pop {r3-r5, pc}
_0207563C:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x4
	pop {r3-r5, pc}
_02075646:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x5
	pop {r3-r5, pc}
_02075650:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x6
	pop {r3-r5, pc}
_0207565A:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x7
	pop {r3-r5, pc}
_02075664:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x8
	pop {r3-r5, pc}
_0207566E:
	add r0, r4, #0x0
	mov r1, #0x26
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02075684
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xb
	pop {r3-r5, pc}
_02075684:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x9
	pop {r3-r5, pc}
_0207568E:
	add r0, r4, #0x0
	mov r1, #0x15
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020756A4
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xa
	pop {r3-r5, pc}
_020756A4:
	add r0, r4, #0x0
	mov r1, #0x26
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020756BA
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xb
	pop {r3-r5, pc}
_020756BA:
	add r0, r4, #0x0
	mov r1, #0x30
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _020756D0
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xc
	pop {r3-r5, pc}
_020756D0:
	bge _020756DC
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x12
	pop {r3-r5, pc}
_020756DC:
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _020756F2
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xd
	pop {r3-r5, pc}
_020756F2:
	bge _020756FE
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x13
	pop {r3-r5, pc}
_020756FE:
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02075714
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xe
	pop {r3-r5, pc}
_02075714:
	bge _02075720
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x14
	pop {r3-r5, pc}
_02075720:
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02075736
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0xf
	pop {r3-r5, pc}
_02075736:
	bge _02075742
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x15
	pop {r3-r5, pc}
_02075742:
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02075758
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x10
	pop {r3-r5, pc}
_02075758:
	bge _02075764
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x16
	pop {r3-r5, pc}
_02075764:
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _0207577A
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x11
	pop {r3-r5, pc}
_0207577A:
	bge _02075786
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x17
	pop {r3-r5, pc}
_02075786:
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0207579C
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x18
	pop {r3-r5, pc}
_0207579C:
	add r0, r4, #0x0
	mov r1, #0x22
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020757B2
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x19
	pop {r3-r5, pc}
_020757B2:
	add r0, r4, #0x0
	mov r1, #0x23
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020757C8
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1a
	pop {r3-r5, pc}
_020757C8:
	add r0, r4, #0x0
	mov r1, #0x24
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _020757E0
	add r0, r4, #0x0
	mov r1, #0x25
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020757EA
_020757E0:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1b
	pop {r3-r5, pc}
_020757EA:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1c
	pop {r3-r5, pc}

	thumb_func_start FUN_020757F4
FUN_020757F4: ; 0x020757F4
	push {r4-r6, lr}
	add r4, r0, #0x0
	ldr r0, _02075B8C ; =0x000005A4
	add r6, r1, #0x0
	ldr r1, _02075B90 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	add r5, r2, #0x0
	bl GetPartyMonByIndex
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	add r0, r6, #0x0
	bl FUN_0207550C
	cmp r0, #0x1b
	bls _02075828
	b _02075C40
_02075828:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02075834: ; jump table (using 16-bit offset)
	.short _02075C40 - _02075834 - 2; case 0
	.short _02075C40 - _02075834 - 2; case 1
	.short _02075C40 - _02075834 - 2; case 2
	.short _02075890 - _02075834 - 2; case 3
	.short _0207586C - _02075834 - 2; case 4
	.short _020758B4 - _02075834 - 2; case 5
	.short _020758D8 - _02075834 - 2; case 6
	.short _020758FC - _02075834 - 2; case 7
	.short _02075920 - _02075834 - 2; case 8
	.short _02075968 - _02075834 - 2; case 9
	.short _02075944 - _02075834 - 2; case 10
	.short _02075C40 - _02075834 - 2; case 11
	.short _0207598C - _02075834 - 2; case 12
	.short _020759BE - _02075834 - 2; case 13
	.short _020759F0 - _02075834 - 2; case 14
	.short _02075A22 - _02075834 - 2; case 15
	.short _02075A54 - _02075834 - 2; case 16
	.short _02075A86 - _02075834 - 2; case 17
	.short _02075AB8 - _02075834 - 2; case 18
	.short _02075AEC - _02075834 - 2; case 19
	.short _02075B20 - _02075834 - 2; case 20
	.short _02075B54 - _02075834 - 2; case 21
	.short _02075B88 - _02075834 - 2; case 22
	.short _02075BCA - _02075834 - 2; case 23
	.short _02075C40 - _02075834 - 2; case 24
	.short _02075BFE - _02075834 - 2; case 25
	.short _02075BFE - _02075834 - 2; case 26
	.short _02075C30 - _02075834 - 2; case 27
_0207586C:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x41
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075890:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x5b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_020758B4:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x43
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_020758D8:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x44
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_020758FC:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x42
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075920:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x49
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075944:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4a
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075968:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x47
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_0207598C:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_020759BE:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	mov r1, #0x1
	ldr r0, [r4, r0]
	add r2, r1, #0x0
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_020759F0:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x2
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075A22:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x3
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075A54:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x4
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075A86:
	ldr r0, _02075B94 ; =0x0000069C
	mov r1, #0x4b
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x5
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075AB8:
	ldr r0, _02075B94 ; =0x0000069C
	add r5, #0x6e
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075AEC:
	ldr r0, _02075B94 ; =0x0000069C
	add r5, #0x6e
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	mov r1, #0x1
	ldr r0, [r4, r0]
	add r2, r1, #0x0
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075B20:
	ldr r0, _02075B94 ; =0x0000069C
	add r5, #0x6e
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x2
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075B54:
	ldr r0, _02075B94 ; =0x0000069C
	add r5, #0x6e
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x3
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075B88:
	ldr r0, _02075B94 ; =0x0000069C
	b _02075B98
	.balign 4
_02075B8C: .word 0x000005A4
_02075B90: .word 0x00000B25
_02075B94: .word 0x0000069C
_02075B98:
	add r5, #0x6e
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x4
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075BCA:
	ldr r0, _02075C50 ; =0x0000069C
	add r5, #0x6e
	ldr r0, [r4, r0]
	add r1, r5, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	mov r2, #0x5
	bl FUN_0200AF50
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075BFE:
	ldr r0, _02075C50 ; =0x0000069C
	mov r1, #0x48
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r6, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	add r2, r5, #0x0
	bl FUN_0200AD5C
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r6, #0x0
	bl FUN_0200B7B8
	add r0, r6, #0x0
	bl FUN_02021A20
	pop {r4-r6, pc}
_02075C30:
	ldr r2, _02075C50 ; =0x0000069C
	mov r1, #0x45
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	pop {r4-r6, pc}
_02075C40:
	ldr r2, _02075C50 ; =0x0000069C
	mov r1, #0x69
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	pop {r4-r6, pc}
	.balign 4
_02075C50: .word 0x0000069C

	thumb_func_start FUN_02075C54
FUN_02075C54: ; 0x02075C54
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02075CCC ; =0x000005A4
	ldr r0, [r4, r0]
	ldrh r0, [r0, #0x24]
	bl FUN_0207550C
	cmp r0, #0x1c
	bhi _02075CCA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02075C72: ; jump table (using 16-bit offset)
	.short _02075CCA - _02075C72 - 2; case 0
	.short _02075CCA - _02075C72 - 2; case 1
	.short _02075CAC - _02075C72 - 2; case 2
	.short _02075CB4 - _02075C72 - 2; case 3
	.short _02075CB4 - _02075C72 - 2; case 4
	.short _02075CB4 - _02075C72 - 2; case 5
	.short _02075CB4 - _02075C72 - 2; case 6
	.short _02075CB4 - _02075C72 - 2; case 7
	.short _02075CB4 - _02075C72 - 2; case 8
	.short _02075CB4 - _02075C72 - 2; case 9
	.short _02075CB4 - _02075C72 - 2; case 10
	.short _02075CC4 - _02075C72 - 2; case 11
	.short _02075CB4 - _02075C72 - 2; case 12
	.short _02075CB4 - _02075C72 - 2; case 13
	.short _02075CB4 - _02075C72 - 2; case 14
	.short _02075CB4 - _02075C72 - 2; case 15
	.short _02075CB4 - _02075C72 - 2; case 16
	.short _02075CB4 - _02075C72 - 2; case 17
	.short _02075CBC - _02075C72 - 2; case 18
	.short _02075CBC - _02075C72 - 2; case 19
	.short _02075CBC - _02075C72 - 2; case 20
	.short _02075CBC - _02075C72 - 2; case 21
	.short _02075CBC - _02075C72 - 2; case 22
	.short _02075CBC - _02075C72 - 2; case 23
	.short _02075CCA - _02075C72 - 2; case 24
	.short _02075CB4 - _02075C72 - 2; case 25
	.short _02075CB4 - _02075C72 - 2; case 26
	.short _02075CB4 - _02075C72 - 2; case 27
	.short _02075CCA - _02075C72 - 2; case 28
_02075CAC:
	ldr r1, _02075CD0 ; =FUN_0207640C
	ldr r0, _02075CD4 ; =0x00000B14
	str r1, [r4, r0]
	pop {r4, pc}
_02075CB4:
	ldr r1, _02075CD8 ; =FUN_02075D20
	ldr r0, _02075CD4 ; =0x00000B14
	str r1, [r4, r0]
	pop {r4, pc}
_02075CBC:
	ldr r1, _02075CDC ; =FUN_02075DC0
	ldr r0, _02075CD4 ; =0x00000B14
	str r1, [r4, r0]
	pop {r4, pc}
_02075CC4:
	ldr r1, _02075CE0 ; =FUN_02075F60
	ldr r0, _02075CD4 ; =0x00000B14
	str r1, [r4, r0]
_02075CCA:
	pop {r4, pc}
	.balign 4
_02075CCC: .word 0x000005A4
_02075CD0: .word FUN_0207640C
_02075CD4: .word 0x00000B14
_02075CD8: .word FUN_02075D20
_02075CDC: .word FUN_02075DC0
_02075CE0: .word FUN_02075F60

	thumb_func_start FUN_02075CE4
FUN_02075CE4: ; 0x02075CE4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02075D14 ; =0x00000B24
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	beq _02075CF8
	mov r0, #0x5
	pop {r4, pc}
_02075CF8:
	ldr r0, _02075D18 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02075D10
	ldr r0, _02075D1C ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	mov r0, #0x1b
	pop {r4, pc}
_02075D10:
	mov r0, #0x5
	pop {r4, pc}
	.balign 4
_02075D14: .word 0x00000B24
_02075D18: .word gUnknown21C48B8
_02075D1C: .word 0x000005A4

	thumb_func_start FUN_02075D20
FUN_02075D20: ; 0x02075D20
	push {r3-r5, lr}
	sub sp, #0x8
	ldr r1, _02075DA8 ; =0x000005A4
	add r5, r0, #0x0
	ldr r4, [r5, r1]
	bl FUN_020772CC
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r2, _02075DAC ; =0x00000B25
	ldrh r1, [r4, #0x24]
	ldrb r2, [r5, r2]
	ldr r0, [r4, #0x0]
	mov r3, #0x0
	bl FUN_02084DD0
	ldr r1, _02075DAC ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_0207008C
	ldr r1, _02075DAC ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072D1C
	ldr r1, _02075DAC ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072DDC
	ldr r0, _02075DAC ; =0x00000B25
	mov r2, #0x2c
	ldrb r1, [r5, r0]
	add r0, r5, #0x0
	mul r2, r1
	add r3, r5, r2
	ldr r2, _02075DB0 ; =0x0000070E
	ldrh r2, [r3, r2]
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	ldr r1, _02075DA8 ; =0x000005A4
	add r0, r5, #0x0
	ldr r1, [r5, r1]
	mov r2, #0x0
	ldrh r1, [r1, #0x24]
	bl FUN_020757F4
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02075DB4 ; =0x000005EC
	bl FUN_020054C8
	ldr r1, _02075DB8 ; =FUN_02075CE4
	ldr r0, _02075DBC ; =0x00000B14
	str r1, [r5, r0]
	mov r0, #0x5
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02075DA8: .word 0x000005A4
_02075DAC: .word 0x00000B25
_02075DB0: .word 0x0000070E
_02075DB4: .word 0x000005EC
_02075DB8: .word FUN_02075CE4
_02075DBC: .word 0x00000B14

	thumb_func_start FUN_02075DC0
FUN_02075DC0: ; 0x02075DC0
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	ldr r0, _02075F4C ; =0x000005A4
	ldr r1, _02075F50 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0xd
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1c]
	add r0, r4, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, _02075F4C ; =0x000005A4
	ldr r6, [r5, r0]
	add r0, r5, #0x0
	bl FUN_020772CC
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r2, _02075F50 ; =0x00000B25
	ldrh r1, [r6, #0x24]
	ldrb r2, [r5, r2]
	ldr r0, [r6, #0x0]
	mov r3, #0x0
	bl FUN_02084DD0
	ldr r1, _02075F50 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_0207008C
	ldr r1, _02075F50 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072D1C
	ldr r1, _02075F50 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072DDC
	ldr r0, _02075F50 ; =0x00000B25
	mov r2, #0x2c
	ldrb r1, [r5, r0]
	add r0, r5, #0x0
	mul r2, r1
	add r3, r5, r2
	ldr r2, _02075F54 ; =0x0000070E
	ldrh r2, [r3, r2]
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r0, r4, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x1c]
	cmp r1, r0
	bne _02075EFA
	add r0, r4, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x18]
	cmp r1, r0
	bne _02075EFA
	add r0, r4, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x14]
	cmp r1, r0
	bne _02075EFA
	add r0, r4, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x10]
	cmp r1, r0
	bne _02075EFA
	add r0, r4, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0xc]
	cmp r1, r0
	bne _02075EFA
	add r0, r4, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x8]
	cmp r1, r0
	beq _02075F26
_02075EFA:
	add r0, r4, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl GetMonData
	cmp r7, r0
	ldr r1, _02075F4C ; =0x000005A4
	beq _02075F18
	ldr r1, [r5, r1]
	add r0, r5, #0x0
	ldrh r1, [r1, #0x24]
	mov r2, #0x0
	bl FUN_020757F4
	b _02075F34
_02075F18:
	ldr r1, [r5, r1]
	add r0, r5, #0x0
	ldrh r1, [r1, #0x24]
	mov r2, #0x1
	bl FUN_020757F4
	b _02075F34
_02075F26:
	ldr r1, _02075F4C ; =0x000005A4
	add r0, r5, #0x0
	ldr r1, [r5, r1]
	mov r2, #0x2
	ldrh r1, [r1, #0x24]
	bl FUN_020757F4
_02075F34:
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r1, _02075F58 ; =FUN_02075CE4
	ldr r0, _02075F5C ; =0x00000B14
	str r1, [r5, r0]
	mov r0, #0x5
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02075F4C: .word 0x000005A4
_02075F50: .word 0x00000B25
_02075F54: .word 0x0000070E
_02075F58: .word FUN_02075CE4
_02075F5C: .word 0x00000B14

	thumb_func_start FUN_02075F60
FUN_02075F60: ; 0x02075F60
	push {r4-r7, lr}
	sub sp, #0xc
	ldr r1, _02076080 ; =0x000005A4
	add r5, r0, #0x0
	ldr r4, [r5, r1]
	bl FUN_020772CC
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r2, _02076084 ; =0x00000B25
	ldrh r1, [r4, #0x24]
	ldrb r2, [r5, r2]
	ldr r0, [r4, #0x0]
	mov r3, #0x0
	bl FUN_02084DD0
	ldr r0, _02076080 ; =0x000005A4
	ldr r1, _02076084 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0xa2
	mov r2, #0x0
	str r0, [sp, #0x8]
	bl GetMonData
	add r4, r0, #0x0
	ldr r0, _02076084 ; =0x00000B25
	ldrb r1, [r5, r0]
	mov r0, #0x2c
	mul r0, r1
	add r1, r5, r0
	ldr r0, _02076088 ; =0x00000706
	ldrh r1, [r1, r0]
	cmp r1, #0x0
	bne _02075FBC
	sub r0, #0x6a
	ldr r0, [r5, r0]
	mov r1, #0x46
	bl FUN_0200A914
	add r7, r0, #0x0
	b _02075FDA
_02075FBC:
	cmp r4, r1
	bne _02075FCE
	sub r0, #0x6a
	ldr r0, [r5, r0]
	mov r1, #0x47
	bl FUN_0200A914
	add r7, r0, #0x0
	b _02075FDA
_02075FCE:
	sub r0, #0x6a
	ldr r0, [r5, r0]
	mov r1, #0x40
	bl FUN_0200A914
	add r7, r0, #0x0
_02075FDA:
	ldr r0, [sp, #0x8]
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r0, #0x0
	mov r3, #0x6a
	str r0, [sp, #0x0]
	mov r1, #0x1
	ldr r2, _02076084 ; =0x00000B25
	str r1, [sp, #0x4]
	ldrb r6, [r5, r2]
	mov r2, #0x2c
	lsl r3, r3, #0x4
	mul r2, r6
	ldr r0, [r5, r3]
	add r2, r5, r2
	add r3, #0x66
	ldrh r2, [r2, r3]
	mov r3, #0x3
	sub r2, r4, r2
	bl FUN_0200AD38
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r7, #0x0
	bl FUN_0200B7B8
	add r0, r7, #0x0
	bl FUN_02021A20
	ldr r0, [sp, #0x8]
	bl FUN_0207C2D4
	add r4, r0, #0x0
	ldr r1, _02076084 ; =0x00000B25
	lsl r2, r4, #0x18
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	cmp r4, #0x7
	bne _02076062
	ldr r1, _02076084 ; =0x00000B25
	ldr r0, _0207608C ; =0x0000070E
	ldrb r3, [r5, r1]
	add r2, r5, r0
	mov r0, #0x2c
	mul r0, r3
	ldrh r4, [r2, r0]
	ldr r3, _02076090 ; =0xFFFFF000
	and r4, r3
	mov r3, #0x7
	orr r3, r4
	strh r3, [r2, r0]
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	bl FUN_02072B20
_02076062:
	ldr r1, _02076084 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_020709FC
	ldr r1, _02076094 ; =FUN_020760A0
	ldr r0, _02076098 ; =0x00000B14
	str r1, [r5, r0]
	ldr r0, _0207609C ; =0x000005EC
	bl FUN_020054C8
	mov r0, #0x5
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02076080: .word 0x000005A4
_02076084: .word 0x00000B25
_02076088: .word 0x00000706
_0207608C: .word 0x0000070E
_02076090: .word 0xFFFFF000
_02076094: .word FUN_020760A0
_02076098: .word 0x00000B14
_0207609C: .word 0x000005EC

	thumb_func_start FUN_020760A0
FUN_020760A0: ; 0x020760A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076130 ; =0x000005A4
	ldr r1, _02076134 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	ldr r1, _02076134 ; =0x00000B25
	add r4, r0, #0x0
	ldrb r2, [r5, r1]
	ldr r0, _02076138 ; =0x00000706
	mov r1, #0x2c
	add r3, r2, #0x0
	add r0, r5, r0
	mul r3, r1
	ldrh r1, [r0, r3]
	cmp r4, r1
	beq _020760D4
	add r1, r1, #0x1
	strh r1, [r0, r3]
_020760D4:
	ldr r1, _02076134 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072BBC
	ldr r1, _02076134 ; =0x00000B25
	add r0, r5, #0x4
	ldrb r2, [r5, r1]
	lsl r1, r2, #0x2
	add r1, r2, r1
	add r1, r1, #0x3
	lsl r1, r1, #0x4
	add r0, r0, r1
	mov r1, #0x0
	bl FUN_02019620
	ldr r1, _02076134 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072B7C
	ldr r1, _02076134 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072C28
	ldr r0, _02076134 ; =0x00000B25
	mov r1, #0x2c
	ldrb r0, [r5, r0]
	add r2, r0, #0x0
	mul r2, r1
	ldr r0, _02076138 ; =0x00000706
	add r2, r5, r2
	ldrh r0, [r2, r0]
	cmp r4, r0
	bne _0207612C
	add r0, r5, #0x0
	sub r1, #0x2d
	mov r2, #0x1
	bl FUN_020731E8
	ldr r1, _0207613C ; =FUN_02075CE4
	ldr r0, _02076140 ; =0x00000B14
	str r1, [r5, r0]
_0207612C:
	mov r0, #0x5
	pop {r3-r5, pc}
	.balign 4
_02076130: .word 0x000005A4
_02076134: .word 0x00000B25
_02076138: .word 0x00000706
_0207613C: .word FUN_02075CE4
_02076140: .word 0x00000B14

	thumb_func_start FUN_02076144
FUN_02076144: ; 0x02076144
	push {r3, lr}
	mov r1, #0x18
	mov r2, #0xc
	bl FUN_0206E7B8
	cmp r0, #0x0
	beq _02076156
	mov r0, #0x1
	pop {r3, pc}
_02076156:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0207615C
FUN_0207615C: ; 0x0207615C
	push {r3-r6}
	cmp r1, #0x6
	blo _02076168
	mov r0, #0xff
	pop {r3-r6}
	bx lr
_02076168:
	bhs _02076194
	ldr r2, _0207619C ; =0x00000706
	mov r3, #0x2c
	add r4, r2, #0x0
	add r4, #0x23
_02076172:
	add r5, r1, #0x0
	mul r5, r3
	add r6, r0, r5
	ldrb r5, [r6, r4]
	cmp r5, #0x0
	beq _0207618A
	ldrh r5, [r6, r2]
	cmp r5, #0x0
	bne _0207618A
	add r0, r1, #0x0
	pop {r3-r6}
	bx lr
_0207618A:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x6
	blo _02076172
_02076194:
	mov r0, #0xff
	pop {r3-r6}
	bx lr
	nop
_0207619C: .word 0x00000706

	thumb_func_start FUN_020761A0
FUN_020761A0: ; 0x020761A0
	push {r3-r7, lr}
	ldr r1, _020763DC ; =0x00000B22
	add r4, r0, #0x0
	ldrb r2, [r4, r1]
	cmp r2, #0x3
	bls _020761AE
	b _020763D6
_020761AE:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_020761BA: ; jump table (using 16-bit offset)
	.short _020761C2 - _020761BA - 2; case 0
	.short _02076212 - _020761BA - 2; case 1
	.short _020762DC - _020761BA - 2; case 2
	.short _02076360 - _020761BA - 2; case 3
_020761C2:
	mov r1, #0x0
	bl FUN_0207615C
	ldr r1, _020763E0 ; =0x00000B25
	strb r0, [r4, r1]
	ldrb r0, [r4, r1]
	cmp r0, #0xff
	bne _02076206
	ldr r2, _020763E4 ; =0x0000069C
	mov r1, #0x69
	ldr r0, [r4, r2]
	add r2, #0x8
	ldr r2, [r4, r2]
	bl FUN_0200A8E0
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r1, _020763E8 ; =FUN_02075CE4
	ldr r0, _020763EC ; =0x00000B14
	mov r2, #0x1
	str r1, [r4, r0]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02073CB4
	ldr r0, _020763E0 ; =0x00000B25
	mov r1, #0x7
	strb r1, [r4, r0]
	mov r0, #0x5
	pop {r3-r7, pc}
_02076206:
	cmp r0, #0x0
	beq _02076212
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020709FC
_02076212:
	ldr r0, _020763F0 ; =0x000005A4
	ldr r1, _020763E0 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020772CC
	add r3, r0, #0x0
	mov r0, #0xc
	str r0, [sp, #0x0]
	ldr r1, _020763F0 ; =0x000005A4
	add r0, r5, #0x0
	ldr r1, [r4, r1]
	mov r2, #0x0
	ldrh r1, [r1, #0x24]
	bl FUN_02084810
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	ldr r0, _020763E4 ; =0x0000069C
	mov r1, #0x46
	ldr r0, [r4, r0]
	bl FUN_0200A914
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r6, #0x0
	bl FUN_0200B7B8
	add r0, r6, #0x0
	bl FUN_02021A20
	ldr r7, _020763E0 ; =0x00000B25
	ldr r3, _020763F4 ; =0x0000070E
	ldrb r5, [r4, r7]
	mov r2, #0x2c
	add r1, r4, r3
	add r0, r5, #0x0
	mul r0, r2
	ldrh r6, [r1, r0]
	ldr r5, _020763F8 ; =0xFFFFF000
	and r6, r5
	mov r5, #0x7
	orr r5, r6
	strh r5, [r1, r0]
	ldrb r1, [r4, r7]
	add r0, r4, #0x0
	mul r2, r1
	add r2, r4, r2
	ldrh r2, [r2, r3]
	lsl r2, r2, #0x14
	lsr r2, r2, #0x14
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	add r1, r7, #0x0
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_02072B20
	add r1, r7, #0x0
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	bl FUN_020709FC
	add r1, r7, #0x0
	ldrb r1, [r4, r1]
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02073CB4
	ldr r0, _020763FC ; =0x000005EC
	bl FUN_020054C8
	sub r0, r7, #0x3
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	b _020763D6
_020762DC:
	ldr r0, _020763F0 ; =0x000005A4
	add r1, r1, #0x3
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	ldr r2, _020763E0 ; =0x00000B25
	add r5, r0, #0x0
	ldr r0, _02076400 ; =0x00000706
	ldrb r3, [r4, r2]
	add r1, r4, r0
	mov r0, #0x2c
	mul r0, r3
	ldrh r3, [r1, r0]
	add r3, r3, #0x1
	strh r3, [r1, r0]
	ldrb r1, [r4, r2]
	add r0, r4, #0x0
	bl FUN_02072BBC
	ldr r1, _020763E0 ; =0x00000B25
	add r0, r4, #0x4
	ldrb r2, [r4, r1]
	lsl r1, r2, #0x2
	add r1, r2, r1
	add r1, r1, #0x3
	lsl r1, r1, #0x4
	add r0, r0, r1
	mov r1, #0x0
	bl FUN_02019620
	ldr r1, _020763E0 ; =0x00000B25
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	bl FUN_02072B7C
	ldr r1, _020763E0 ; =0x00000B25
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	bl FUN_02072C28
	ldr r0, _020763E0 ; =0x00000B25
	mov r1, #0x2c
	ldrb r0, [r4, r0]
	add r2, r0, #0x0
	mul r2, r1
	ldr r0, _02076400 ; =0x00000706
	add r2, r4, r2
	ldrh r0, [r2, r0]
	cmp r5, r0
	bne _020763D6
	add r0, r4, #0x0
	sub r1, #0x2d
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _020763DC ; =0x00000B22
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	b _020763D6
_02076360:
	add r0, r1, #0x2
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _020763D6
	ldr r0, _02076404 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _020763D6
	ldr r0, _02076408 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _020763E0 ; =0x00000B25
	ldrb r5, [r4, r0]
	add r0, r4, #0x0
	add r1, r5, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0207615C
	ldr r1, _020763E0 ; =0x00000B25
	strb r0, [r4, r1]
	ldrb r0, [r4, r1]
	cmp r0, #0xff
	beq _020763B2
	mov r0, #0x89
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x0
	bl FUN_0200D0E0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020709FC
	ldr r0, _020763DC ; =0x00000B22
	mov r1, #0x1
	strb r1, [r4, r0]
	b _020763D6
_020763B2:
	ldr r0, _020763F0 ; =0x000005A4
	mov r2, #0x1
	ldr r1, [r4, r0]
	mov r3, #0xc
	ldr r0, [r1, #0x4]
	ldrh r1, [r1, #0x24]
	bl FUN_0206EDD4
	ldr r0, _020763F0 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _020763E0 ; =0x00000B25
	mov r1, #0x7
	strb r1, [r4, r0]
	mov r0, #0x1b
	pop {r3-r7, pc}
_020763D6:
	mov r0, #0x7
	pop {r3-r7, pc}
	nop
_020763DC: .word 0x00000B22
_020763E0: .word 0x00000B25
_020763E4: .word 0x0000069C
_020763E8: .word FUN_02075CE4
_020763EC: .word 0x00000B14
_020763F0: .word 0x000005A4
_020763F4: .word 0x0000070E
_020763F8: .word 0xFFFFF000
_020763FC: .word 0x000005EC
_02076400: .word 0x00000706
_02076404: .word gUnknown21C48B8
_02076408: .word 0x000005DC

	thumb_func_start FUN_0207640C
FUN_0207640C: ; 0x0207640C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _020765B0 ; =0x000005A4
	ldr r1, _020765B4 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	mov r1, #0xa3
	mov r2, #0x0
	add r4, r0, #0x0
	bl GetMonData
	ldr r1, _020765B8 ; =0x00000B28
	mov r2, #0x0
	strh r0, [r5, r1]
	add r0, r4, #0x0
	mov r1, #0xa4
	bl GetMonData
	ldr r1, _020765BC ; =0x00000B2A
	mov r2, #0x0
	strh r0, [r5, r1]
	add r0, r4, #0x0
	mov r1, #0xa5
	bl GetMonData
	ldr r1, _020765C0 ; =0x00000B2C
	mov r2, #0x0
	strh r0, [r5, r1]
	add r0, r4, #0x0
	mov r1, #0xa7
	bl GetMonData
	ldr r1, _020765C4 ; =0x00000B2E
	mov r2, #0x0
	strh r0, [r5, r1]
	add r0, r4, #0x0
	mov r1, #0xa8
	bl GetMonData
	mov r1, #0xb3
	lsl r1, r1, #0x4
	strh r0, [r5, r1]
	add r0, r4, #0x0
	mov r1, #0xa6
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020765C8 ; =0x00000B32
	strh r0, [r5, r1]
	ldr r0, _020765B0 ; =0x000005A4
	ldr r6, [r5, r0]
	add r0, r5, #0x0
	bl FUN_020772CC
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r2, _020765B4 ; =0x00000B25
	ldrh r1, [r6, #0x24]
	ldrb r2, [r5, r2]
	ldr r0, [r6, #0x0]
	mov r3, #0x0
	bl FUN_02084DD0
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020765B4 ; =0x00000B25
	ldrb r2, [r5, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r5, r1
	ldr r1, _020765CC ; =0x0000070A
	strh r0, [r2, r1]
	add r0, r4, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020765B4 ; =0x00000B25
	ldrb r2, [r5, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r5, r1
	ldr r1, _020765D0 ; =0x00000706
	strh r0, [r2, r1]
	add r0, r4, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	ldr r1, _020765B4 ; =0x00000B25
	ldrb r2, [r5, r1]
	mov r1, #0x2c
	mul r1, r2
	add r2, r5, r1
	ldr r1, _020765D4 ; =0x00000708
	strh r0, [r2, r1]
	sub r1, #0x6c
	ldr r0, [r5, r1]
	mov r1, #0xc1
	bl FUN_0200A914
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r0, #0x0
	mov r3, #0x6a
	str r0, [sp, #0x0]
	mov r1, #0x1
	ldr r2, _020765B4 ; =0x00000B25
	str r1, [sp, #0x4]
	ldrb r6, [r5, r2]
	mov r2, #0x2c
	lsl r3, r3, #0x4
	mul r2, r6
	ldr r0, [r5, r3]
	add r2, r5, r2
	add r3, #0x6a
	ldrh r2, [r2, r3]
	mov r3, #0x3
	bl FUN_0200AD38
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r7, #0x0
	bl FUN_0200B7B8
	add r0, r7, #0x0
	bl FUN_02021A20
	add r0, r4, #0x0
	bl FUN_0207C2D4
	add r4, r0, #0x0
	ldr r1, _020765B4 ; =0x00000B25
	lsl r2, r4, #0x18
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02073A4C
	cmp r4, #0x7
	bne _0207656E
	ldr r1, _020765B4 ; =0x00000B25
	ldr r0, _020765D8 ; =0x0000070E
	ldrb r3, [r5, r1]
	add r2, r5, r0
	mov r0, #0x2c
	mul r0, r3
	ldrh r4, [r2, r0]
	ldr r3, _020765DC ; =0xFFFFF000
	and r4, r3
	mov r3, #0x7
	orr r3, r4
	strh r3, [r2, r0]
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	bl FUN_02072B20
_0207656E:
	ldr r1, _020765B4 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_020709FC
	ldr r0, _020765E0 ; =FUN_020760A0
	ldr r1, _020765E4 ; =0x00000B14
	str r0, [r5, r1]
	add r1, #0x11
	ldrb r1, [r5, r1]
	add r0, r5, #0x0
	bl FUN_02072D1C
	ldr r1, _020765B4 ; =0x00000B25
	add r0, r5, #0x0
	ldrb r1, [r5, r1]
	bl FUN_02072DDC
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r1, _020765E8 ; =FUN_020765EC
	ldr r0, _020765E4 ; =0x00000B14
	str r1, [r5, r0]
	mov r1, #0x0
	add r0, #0x13
	strb r1, [r5, r0]
	mov r0, #0x5
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020765B0: .word 0x000005A4
_020765B4: .word 0x00000B25
_020765B8: .word 0x00000B28
_020765BC: .word 0x00000B2A
_020765C0: .word 0x00000B2C
_020765C4: .word 0x00000B2E
_020765C8: .word 0x00000B32
_020765CC: .word 0x0000070A
_020765D0: .word 0x00000706
_020765D4: .word 0x00000708
_020765D8: .word 0x0000070E
_020765DC: .word 0xFFFFF000
_020765E0: .word FUN_020760A0
_020765E4: .word 0x00000B14
_020765E8: .word FUN_020765EC

	thumb_func_start FUN_020765EC
FUN_020765EC: ; 0x020765EC
	push {r3-r5, lr}
	ldr r1, _0207686C ; =0x00000B27
	add r4, r0, #0x0
	ldrb r0, [r4, r1]
	cmp r0, #0x6
	bhi _020766A8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02076604: ; jump table (using 16-bit offset)
	.short _02076612 - _02076604 - 2; case 0
	.short _0207663C - _02076604 - 2; case 1
	.short _0207665A - _02076604 - 2; case 2
	.short _02076680 - _02076604 - 2; case 3
	.short _02076780 - _02076604 - 2; case 4
	.short _020767A4 - _02076604 - 2; case 5
	.short _02076814 - _02076604 - 2; case 6
_02076612:
	sub r0, r1, #0x3
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _020766A8
	ldr r0, _02076870 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _020766A8
	ldr r0, _02076874 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_020734C0
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x1
	strb r1, [r4, r0]
	b _02076868
_0207663C:
	ldr r0, _02076870 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _020766A8
	ldr r0, _02076874 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_0207363C
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x2
	strb r1, [r4, r0]
	b _02076868
_0207665A:
	ldr r0, _02076870 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _020766A8
	ldr r0, _02076874 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_020736F4
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x3
	strb r1, [r4, r0]
	ldr r0, _02076878 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	str r1, [r0, #0x34]
	b _02076868
_02076680:
	ldr r0, _02076878 ; =0x000005A4
	sub r1, r1, #0x2
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	ldr r1, _02076878 ; =0x000005A4
	add r5, r0, #0x0
	ldr r2, [r4, r1]
	add r1, r2, #0x0
	add r1, #0x34
	add r2, #0x26
	bl FUN_02069818
	cmp r0, #0x0
	beq _020766B2
	ldr r1, _0207687C ; =0x0000FFFE
	cmp r0, r1
	bne _020766AA
_020766A8:
	b _02076868
_020766AA:
	add r1, r1, #0x1
	cmp r0, r1
	beq _020766BA
	b _02076724
_020766B2:
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x6
	strb r1, [r4, r0]
	b _02076868
_020766BA:
	add r0, r5, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r2, #0x6a
	lsl r2, r2, #0x4
	ldr r0, [r4, r2]
	sub r2, #0xfc
	ldr r2, [r4, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x26]
	bl FUN_0200AD5C
	ldr r0, _02076880 ; =0x0000069C
	mov r1, #0x34
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076884 ; =FUN_02076950
	ldr r1, _02076888 ; =0x00000B18
	ldr r2, _0207688C ; =FUN_020769A4
	str r0, [r4, r1]
	add r0, r1, #0x4
	str r2, [r4, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r4, r1]
	mov r0, #0x14
	pop {r3-r5, pc}
_02076724:
	add r0, r5, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r2, #0x6a
	lsl r2, r2, #0x4
	ldr r0, [r4, r2]
	sub r2, #0xfc
	ldr r2, [r4, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x26]
	bl FUN_0200AD5C
	ldr r0, _02076880 ; =0x0000069C
	mov r1, #0xc2
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x4
	strb r1, [r4, r0]
	b _02076868
_02076780:
	sub r0, r1, #0x3
	ldrb r0, [r4, r0]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02076868
	ldr r0, _02076870 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02076868
	ldr r0, _02076874 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x3
	strb r1, [r4, r0]
	b _02076868
_020767A4:
	ldr r0, _02076870 ; =gUnknown21C48B8
	ldr r2, [r0, #0x48]
	mov r0, #0x3
	tst r0, r2
	beq _02076868
	ldr r0, _02076878 ; =0x000005A4
	sub r1, r1, #0x2
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	ldr r2, _02076878 ; =0x000005A4
	add r1, r0, #0x0
	ldr r2, [r4, r2]
	add r0, r4, #0x0
	add r2, #0x28
	ldrb r2, [r2, #0x0]
	bl FUN_02076F2C
	ldr r0, _02076880 ; =0x0000069C
	mov r1, #0x3d
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r5, r0, #0x0
	ldr r0, [r4, r2]
	sub r2, #0xfc
	ldr r2, [r4, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x26]
	bl FUN_0200AD5C
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _0207686C ; =0x00000B27
	mov r1, #0x4
	strb r1, [r4, r0]
	b _02076868
_02076814:
	ldr r0, _02076878 ; =0x000005A4
	sub r1, r1, #0x2
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	ldr r0, _02076878 ; =0x000005A4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034A04
	add r3, r0, #0x0
	ldr r0, _02076878 ; =0x000005A4
	lsl r3, r3, #0x10
	ldr r1, [r4, r0]
	mov r2, #0x0
	add r0, r1, #0x0
	add r0, #0x3c
	str r0, [sp, #0x0]
	ldr r0, [r1, #0x0]
	add r1, r5, #0x0
	lsr r3, r3, #0x10
	bl GetMonEvolution
	ldr r1, _02076878 ; =0x000005A4
	ldr r2, [r4, r1]
	strh r0, [r2, #0x38]
	ldr r1, [r4, r1]
	ldrh r0, [r1, #0x38]
	cmp r0, #0x0
	beq _0207685E
	mov r0, #0x9
	b _02076860
_0207685E:
	mov r0, #0x0
_02076860:
	add r1, #0x23
	strb r0, [r1, #0x0]
	mov r0, #0x1b
	pop {r3-r5, pc}
_02076868:
	mov r0, #0x5
	pop {r3-r5, pc}
	.balign 4
_0207686C: .word 0x00000B27
_02076870: .word gUnknown21C48B8
_02076874: .word 0x000005DC
_02076878: .word 0x000005A4
_0207687C: .word 0x0000FFFE
_02076880: .word 0x0000069C
_02076884: .word FUN_02076950
_02076888: .word 0x00000B18
_0207688C: .word FUN_020769A4

	thumb_func_start FUN_02076890
FUN_02076890: ; 0x02076890
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _0207693C ; =FUN_020765EC
	ldr r1, _02076940 ; =0x00000B14
	mov r2, #0x3
	str r0, [r4, r1]
	add r0, r1, #0x0
	add r0, #0x13
	strb r2, [r4, r0]
	ldr r0, _02076944 ; =0x000005A4
	add r1, #0x11
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r0, _02076944 ; =0x000005A4
	ldr r2, [r4, r0]
	add r1, r2, #0x0
	add r1, #0x28
	ldrb r1, [r1, #0x0]
	cmp r1, #0x4
	bne _020768E6
	add r0, #0xfc
	ldrh r2, [r2, #0x26]
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200AD5C
	add r0, r4, #0x0
	bl FUN_020769A4
	pop {r3-r5, pc}
_020768E6:
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200AD5C
	ldr r0, _02076948 ; =0x0000069C
	mov r1, #0x3c
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _0207694C ; =0x00000B22
	mov r1, #0x5
	strb r1, [r4, r0]
	add r0, r0, #0x5
	strb r1, [r4, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	nop
_0207693C: .word FUN_020765EC
_02076940: .word 0x00000B14
_02076944: .word 0x000005A4
_02076948: .word 0x0000069C
_0207694C: .word 0x00000B22

	thumb_func_start FUN_02076950
FUN_02076950: ; 0x02076950
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076998 ; =0x0000069C
	mov r1, #0x3b
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _0207699C ; =0x000005A4
	mov r1, #0x5
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _020769A0 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r5, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	nop
_02076998: .word 0x0000069C
_0207699C: .word 0x000005A4
_020769A0: .word 0x00000B22

	thumb_func_start FUN_020769A4
FUN_020769A4: ; 0x020769A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020769EC ; =0x0000069C
	mov r1, #0x37
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _020769F0 ; =FUN_020769FC
	ldr r1, _020769F4 ; =0x00000B18
	ldr r2, _020769F8 ; =FUN_02076A48
	str r0, [r5, r1]
	add r0, r1, #0x4
	str r2, [r5, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r5, r1]
	mov r0, #0x14
	pop {r3-r5, pc}
	.balign 4
_020769EC: .word 0x0000069C
_020769F0: .word FUN_020769FC
_020769F4: .word 0x00000B18
_020769F8: .word FUN_02076A48

	thumb_func_start FUN_020769FC
FUN_020769FC: ; 0x020769FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076A40 ; =0x0000069C
	mov r1, #0x3a
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076A44 ; =0x00000B22
	mov r1, #0x5
	strb r1, [r5, r0]
	mov r1, #0x4
	add r0, r0, #0x5
	strb r1, [r5, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	nop
_02076A40: .word 0x0000069C
_02076A44: .word 0x00000B22

	thumb_func_start FUN_02076A48
FUN_02076A48: ; 0x02076A48
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076A90 ; =0x0000069C
	mov r1, #0x34
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076A94 ; =FUN_02076950
	ldr r1, _02076A98 ; =0x00000B18
	ldr r2, _02076A9C ; =FUN_020769A4
	str r0, [r5, r1]
	add r0, r1, #0x4
	str r2, [r5, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r5, r1]
	mov r0, #0x14
	pop {r3-r5, pc}
	.balign 4
_02076A90: .word 0x0000069C
_02076A94: .word FUN_02076950
_02076A98: .word 0x00000B18
_02076A9C: .word FUN_020769A4

	thumb_func_start FUN_02076AA0
FUN_02076AA0: ; 0x02076AA0
	push {r3-r7, lr}
	ldr r7, _02076AF4 ; =0x000005A4
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r4, #0x0
_02076AAA:
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	ldr r0, [r5, r7]
	ldrh r1, [r0, #0x26]
	cmp r2, r1
	bne _02076AC6
	mov r0, #0xfd
	pop {r3-r7, pc}
_02076AC6:
	cmp r2, #0x0
	beq _02076AD4
	add r1, r4, #0x1
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	cmp r4, #0x4
	blo _02076AAA
_02076AD4:
	ldrh r0, [r0, #0x24]
	bl FUN_0206EA7C
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0206A13C
	cmp r0, #0x0
	bne _02076AEA
	mov r0, #0xff
	pop {r3-r7, pc}
_02076AEA:
	cmp r4, #0x4
	bne _02076AF0
	mov r4, #0xfe
_02076AF0:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_02076AF4: .word 0x000005A4

	thumb_func_start FUN_02076AF8
FUN_02076AF8: ; 0x02076AF8
	push {r4-r6, lr}
	add r4, r0, #0x0
	ldr r0, _02076C78 ; =0x000005A4
	ldr r1, _02076C7C ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02076AA0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	mov r2, #0x6a
	lsl r2, r2, #0x4
	ldr r0, [r4, r2]
	sub r2, #0xfc
	ldr r2, [r4, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x26]
	bl FUN_0200AD5C
	cmp r5, #0xfd
	bhi _02076B5A
	bhs _02076BB2
	cmp r5, #0x3
	bhi _02076B60
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02076B52: ; jump table (using 16-bit offset)
	.short _02076B68 - _02076B52 - 2; case 0
	.short _02076B68 - _02076B52 - 2; case 1
	.short _02076B68 - _02076B52 - 2; case 2
	.short _02076B68 - _02076B52 - 2; case 3
_02076B5A:
	cmp r5, #0xfe
	bhi _02076B62
	beq _02076BF2
_02076B60:
	b _02076C72
_02076B62:
	cmp r5, #0xff
	beq _02076C34
	b _02076C72
_02076B68:
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02076F2C
	ldr r0, _02076C80 ; =0x0000069C
	mov r1, #0x3d
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02076C78 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02076C84 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r4, r0]
	b _02076C72
_02076BB2:
	ldr r0, _02076C80 ; =0x0000069C
	mov r1, #0x3f
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02076C78 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02076C84 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r4, r0]
	b _02076C72
_02076BF2:
	ldr r0, _02076C80 ; =0x0000069C
	mov r1, #0x34
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02076C88 ; =FUN_02076DD4
	ldr r1, _02076C8C ; =0x00000B18
	ldr r2, _02076C90 ; =FUN_02076E28
	str r0, [r4, r1]
	add r0, r1, #0x4
	str r2, [r4, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r4, r1]
	b _02076C72
_02076C34:
	ldr r0, _02076C80 ; =0x0000069C
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02076C78 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02076C84 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r4, r0]
_02076C72:
	mov r0, #0x14
	pop {r4-r6, pc}
	nop
_02076C78: .word 0x000005A4
_02076C7C: .word 0x00000B25
_02076C80: .word 0x0000069C
_02076C84: .word 0x00000B22
_02076C88: .word FUN_02076DD4
_02076C8C: .word 0x00000B18
_02076C90: .word FUN_02076E28

	thumb_func_start FUN_02076C94
FUN_02076C94: ; 0x02076C94
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _02076D2C ; =0x000005A4
	ldr r1, _02076D30 ; =0x00000B25
	ldr r0, [r4, r0]
	ldrb r1, [r4, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r5, r0, #0x0
	bl FUN_020690E4
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200ACF8
	ldr r0, _02076D2C ; =0x000005A4
	ldr r2, [r4, r0]
	add r1, r2, #0x0
	add r1, #0x28
	ldrb r1, [r1, #0x0]
	cmp r1, #0x4
	bne _02076CDC
	add r0, #0xfc
	ldrh r2, [r2, #0x26]
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200AD5C
	add r0, r4, #0x0
	bl FUN_02076E28
	pop {r3-r5, pc}
_02076CDC:
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200AD5C
	ldr r0, _02076D34 ; =0x0000069C
	mov r1, #0x3c
	ldr r0, [r4, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r5, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	add r2, r5, #0x0
	bl FUN_0200B7B8
	add r0, r5, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02076D38 ; =0x00000B22
	mov r1, #0x12
	strb r1, [r4, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	.balign 4
_02076D2C: .word 0x000005A4
_02076D30: .word 0x00000B25
_02076D34: .word 0x0000069C
_02076D38: .word 0x00000B22

	thumb_func_start FUN_02076D3C
FUN_02076D3C: ; 0x02076D3C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076DC0 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	beq _02076DBC
	ldr r0, _02076DC4 ; =0x000005A4
	ldr r1, _02076DC8 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	ldr r2, _02076DC4 ; =0x000005A4
	add r1, r0, #0x0
	ldr r2, [r5, r2]
	add r0, r5, #0x0
	add r2, #0x28
	ldrb r2, [r2, #0x0]
	bl FUN_02076F2C
	ldr r0, _02076DCC ; =0x0000069C
	mov r1, #0x3d
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r2, #0x6a
	lsl r2, r2, #0x4
	add r4, r0, #0x0
	ldr r0, [r5, r2]
	sub r2, #0xfc
	ldr r2, [r5, r2]
	mov r1, #0x1
	ldrh r2, [r2, #0x26]
	bl FUN_0200AD5C
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076DC4 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02076DD0 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r5, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
_02076DBC:
	mov r0, #0x12
	pop {r3-r5, pc}
	.balign 4
_02076DC0: .word gUnknown21C48B8
_02076DC4: .word 0x000005A4
_02076DC8: .word 0x00000B25
_02076DCC: .word 0x0000069C
_02076DD0: .word 0x00000B22

	thumb_func_start FUN_02076DD4
FUN_02076DD4: ; 0x02076DD4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076E1C ; =0x0000069C
	mov r1, #0x3b
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076E20 ; =0x000005A4
	mov r1, #0x4
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02076E24 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r5, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	nop
_02076E1C: .word 0x0000069C
_02076E20: .word 0x000005A4
_02076E24: .word 0x00000B22

	thumb_func_start FUN_02076E28
FUN_02076E28: ; 0x02076E28
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076E70 ; =0x0000069C
	mov r1, #0x37
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02076E74 ; =FUN_02076E80
	ldr r1, _02076E78 ; =0x00000B18
	ldr r2, _02076E7C ; =FUN_02076ED4
	str r0, [r5, r1]
	add r0, r1, #0x4
	str r2, [r5, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r5, r1]
	mov r0, #0x14
	pop {r3-r5, pc}
	.balign 4
_02076E70: .word 0x0000069C
_02076E74: .word FUN_02076E80
_02076E78: .word 0x00000B18
_02076E7C: .word FUN_02076ED4

	thumb_func_start FUN_02076E80
FUN_02076E80: ; 0x02076E80
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076EC8 ; =0x0000069C
	mov r1, #0x3a
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076ECC ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r5, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02076ED0 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r5, r0]
	mov r0, #0x14
	pop {r3-r5, pc}
	nop
_02076EC8: .word 0x0000069C
_02076ECC: .word 0x000005A4
_02076ED0: .word 0x00000B22

	thumb_func_start FUN_02076ED4
FUN_02076ED4: ; 0x02076ED4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02076F1C ; =0x0000069C
	mov r1, #0x34
	ldr r0, [r5, r0]
	bl FUN_0200A914
	mov r1, #0x6a
	add r4, r0, #0x0
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, r1, #0x4
	ldr r1, [r5, r1]
	add r2, r4, #0x0
	bl FUN_0200B7B8
	add r0, r4, #0x0
	bl FUN_02021A20
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x0
	bl FUN_020731E8
	ldr r0, _02076F20 ; =FUN_02076DD4
	ldr r1, _02076F24 ; =0x00000B18
	ldr r2, _02076F28 ; =FUN_02076E28
	str r0, [r5, r1]
	add r0, r1, #0x4
	str r2, [r5, r0]
	mov r0, #0x16
	add r1, #0xa
	strb r0, [r5, r1]
	mov r0, #0x14
	pop {r3-r5, pc}
	.balign 4
_02076F1C: .word 0x0000069C
_02076F20: .word FUN_02076DD4
_02076F24: .word 0x00000B18
_02076F28: .word FUN_02076E28

	thumb_func_start FUN_02076F2C
FUN_02076F2C: ; 0x02076F2C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	ldr r0, _02076FAC ; =0x000005A4
	add r6, r2, #0x0
	ldr r0, [r5, r0]
	add r4, r1, #0x0
	ldrh r0, [r0, #0x26]
	add r1, r6, #0x0
	add r1, #0x36
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r2, sp, #0x0
	bl SetMonData
	mov r0, #0x0
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, #0x3e
	add r2, sp, #0x0
	bl SetMonData
	ldr r0, _02076FAC ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r5, r0]
	ldrh r0, [r0, #0x26]
	bl WazaGetMaxPp
	add r6, #0x3a
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, sp, #0x0
	bl SetMonData
	ldr r0, _02076FAC ; =0x000005A4
	ldr r1, [r5, r0]
	ldrh r0, [r1, #0x24]
	cmp r0, #0x0
	beq _02076FA8
	ldrh r0, [r1, #0x26]
	bl FUN_0206EA54
	cmp r0, #0x0
	bne _02076F98
	ldr r0, _02076FAC ; =0x000005A4
	mov r2, #0x1
	ldr r1, [r5, r0]
	mov r3, #0xc
	ldr r0, [r1, #0x4]
	ldrh r1, [r1, #0x24]
	bl FUN_0206EDD4
_02076F98:
	add r0, r5, #0x0
	bl FUN_020772CC
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x4
	bl MonApplyFriendshipMod
_02076FA8:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
_02076FAC: .word 0x000005A4

	thumb_func_start FUN_02076FB0
FUN_02076FB0: ; 0x02076FB0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0207702C ; =0x000005A4
	add r6, r1, #0x0
	ldr r1, _02077030 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r1, r6, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _02077034 ; =0x0000069C
	add r1, r6, #0x0
	ldr r0, [r5, r0]
	add r1, #0xa2
	bl FUN_0200A914
	add r7, r0, #0x0
	mov r0, #0x6a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_0200AD5C
	mov r1, #0x6a
	lsl r1, r1, #0x4
	ldr r0, [r5, r1]
	add r1, #0x8
	ldr r1, [r5, r1]
	add r2, r7, #0x0
	bl FUN_0200B7B8
	add r0, r7, #0x0
	bl FUN_02021A20
	cmp r4, #0x0
	ldr r1, _02077038 ; =0x000006F8
	bne _0207701C
	ldr r0, [r5, r1]
	sub r1, #0x50
	mov r2, #0x2
	ldr r1, [r5, r1]
	mvn r2, r2
	bl FUN_020128A0
	mov r0, #0x0
	pop {r3-r7, pc}
_0207701C:
	ldr r0, [r5, r1]
	sub r1, #0x50
	ldr r1, [r5, r1]
	add r2, r6, #0x0
	bl FUN_020128A0
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0207702C: .word 0x000005A4
_02077030: .word 0x00000B25
_02077034: .word 0x0000069C
_02077038: .word 0x000006F8

	thumb_func_start FUN_0207703C
FUN_0207703C: ; 0x0207703C
	push {r4-r5, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _02077050
	mov r1, #0x29
	mov r2, #0x1
	bl FUN_020731D4
	b _02077058
_02077050:
	mov r1, #0x28
	mov r2, #0x1
	bl FUN_020731D4
_02077058:
	mov r0, #0x4
	mov r1, #0xc
	bl FUN_02012838
	ldr r1, _02077108 ; =0x000006F8
	str r0, [r4, r1]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02076FB0
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02076FB0
	add r0, r5, r0
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02076FB0
	add r0, r5, r0
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02076FB0
	add r0, r5, r0
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, _02077108 ; =0x000006F8
	mov r2, #0x0
	ldr r0, [r4, r0]
	str r0, [sp, #0x8]
	mov r0, #0x91
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r0, [sp, #0xc]
	add r0, sp, #0x8
	strb r2, [r0, #0x8]
	mov r2, #0x1
	strb r2, [r0, #0x9]
	mov r2, #0x4
	strb r2, [r0, #0xa]
	ldrb r3, [r0, #0xb]
	mov r2, #0xf
	bic r3, r2
	strb r3, [r0, #0xb]
	ldrb r3, [r0, #0xb]
	mov r2, #0x30
	bic r3, r2
	strb r3, [r0, #0xb]
	cmp r1, #0x4
	ldrb r2, [r0, #0xb]
	bne _020770D6
	mov r1, #0xc0
	bic r2, r1
	mov r1, #0x40
	orr r1, r2
	strb r1, [r0, #0xb]
	b _020770DC
_020770D6:
	mov r1, #0xc0
	bic r2, r1
	strb r2, [r0, #0xb]
_020770DC:
	mov r0, #0x91
	lsl r0, r0, #0x2
	mov r1, #0x1
	add r0, r4, r0
	add r2, r1, #0x0
	mov r3, #0xe
	bl FUN_0200CCA4
	mov r0, #0xc
	str r0, [sp, #0x0]
	mov r0, #0x2
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x8
	mov r1, #0x8
	add r3, r2, #0x0
	bl FUN_02001C14
	ldr r1, _0207710C ; =0x000006FC
	str r0, [r4, r1]
	add sp, #0x14
	pop {r4-r5, pc}
	.balign 4
_02077108: .word 0x000006F8
_0207710C: .word 0x000006FC

	thumb_func_start FUN_02077110
FUN_02077110: ; 0x02077110
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0207722C ; =0x000006FC
	ldr r0, [r5, r0]
	bl FUN_02001C78
	add r4, r0, #0x0
	mov r0, #0x1
	mvn r0, r0
	cmp r4, r0
	beq _02077130
	add r0, r0, #0x1
	cmp r4, r0
	beq _02077226
	b _0207716A
_02077130:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	mov r0, #0x91
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200CCF8
	ldr r0, _0207722C ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02001C5C
	ldr r0, _02077230 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	add r0, r5, #0x0
	mov r1, #0x20
	mov r2, #0x1
	bl FUN_020731C0
	add sp, #0x8
	mov r0, #0x4
	pop {r4-r6, pc}
_0207716A:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	mov r0, #0x91
	lsl r0, r0, #0x2
	add r0, r5, r0
	mov r1, #0x1
	bl FUN_0200CCF8
	ldr r0, _0207722C ; =0x000006FC
	mov r1, #0x0
	ldr r0, [r5, r0]
	bl FUN_02001C5C
	ldr r0, _02077230 ; =0x000006F8
	ldr r0, [r5, r0]
	bl FUN_02012870
	ldr r0, _02077234 ; =0x000005A4
	ldr r6, [r5, r0]
	add r0, r5, #0x0
	bl FUN_020772CC
	str r0, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	ldr r2, _02077238 ; =0x00000B25
	lsl r3, r4, #0x18
	ldrh r1, [r6, #0x24]
	ldrb r2, [r5, r2]
	ldr r0, [r6, #0x0]
	lsr r3, r3, #0x18
	bl FUN_02084DD0
	cmp r0, #0x1
	bne _020771F6
	ldr r0, _02077234 ; =0x000005A4
	ldr r1, _02077238 ; =0x00000B25
	ldr r0, [r5, r0]
	ldrb r1, [r5, r1]
	ldr r0, [r0, #0x0]
	bl GetPartyMonByIndex
	add r4, #0x36
	add r1, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	ldr r1, _02077234 ; =0x000005A4
	add r2, r0, #0x0
	ldr r1, [r5, r1]
	add r0, r5, #0x0
	ldrh r1, [r1, #0x24]
	bl FUN_020757F4
	ldr r0, _02077234 ; =0x000005A4
	mov r2, #0x1
	ldr r1, [r5, r0]
	mov r3, #0xc
	ldr r0, [r1, #0x4]
	ldrh r1, [r1, #0x24]
	bl FUN_0206EDD4
	ldr r0, _0207723C ; =0x000005EC
	bl FUN_020054C8
	b _02077204
_020771F6:
	ldr r2, _02077240 ; =0x0000069C
	mov r1, #0x69
	ldr r0, [r5, r2]
	add r2, #0x8
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
_02077204:
	mov r1, #0x0
	add r0, r5, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _02077234 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r5, r0]
	add sp, #0x8
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _02077244 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r5, r0]
	mov r0, #0x14
	pop {r4-r6, pc}
_02077226:
	mov r0, #0x6
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0207722C: .word 0x000006FC
_02077230: .word 0x000006F8
_02077234: .word 0x000005A4
_02077238: .word 0x00000B25
_0207723C: .word 0x000005EC
_02077240: .word 0x0000069C
_02077244: .word 0x00000B22

	thumb_func_start FUN_02077248
FUN_02077248: ; 0x02077248
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x81
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x1
	bl FUN_0200D0E0
	ldr r0, _020772BC ; =0x00000B25
	ldr r2, _020772C0 ; =0x0000070C
	ldrb r1, [r4, r0]
	mov r0, #0x2c
	mul r0, r1
	add r0, r4, r0
	ldrh r0, [r0, r2]
	cmp r0, #0x0
	bne _02077286
	add r0, r2, #0x0
	sub r0, #0x70
	sub r2, #0x68
	ldr r0, [r4, r0]
	ldr r2, [r4, r2]
	mov r1, #0x7f
	bl FUN_0200A8E0
	ldr r1, _020772BC ; =0x00000B25
	add r0, r4, #0x0
	ldrb r1, [r4, r1]
	bl FUN_02073AB8
	b _0207729C
_02077286:
	add r0, r2, #0x0
	sub r0, #0x70
	sub r2, #0x68
	ldr r0, [r4, r0]
	ldr r2, [r4, r2]
	mov r1, #0x80
	bl FUN_0200A8E0
	ldr r0, _020772BC ; =0x00000B25
	mov r1, #0x7
	strb r1, [r4, r0]
_0207729C:
	mov r1, #0x0
	add r0, r4, #0x0
	mvn r1, r1
	mov r2, #0x1
	bl FUN_020731E8
	ldr r0, _020772C4 ; =0x000005A4
	mov r1, #0x0
	ldr r0, [r4, r0]
	add r0, #0x23
	strb r1, [r0, #0x0]
	ldr r0, _020772C8 ; =0x00000B22
	mov r1, #0x15
	strb r1, [r4, r0]
	pop {r4, pc}
	nop
_020772BC: .word 0x00000B25
_020772C0: .word 0x0000070C
_020772C4: .word 0x000005A4
_020772C8: .word 0x00000B22

	thumb_func_start FUN_020772CC
FUN_020772CC: ; 0x020772CC
	push {r3, lr}
	ldr r1, _020772E4 ; =0x000005A4
	ldr r0, [r0, r1]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, pc}
	nop
_020772E4: .word 0x000005A4
