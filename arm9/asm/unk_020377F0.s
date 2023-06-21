	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020F2A9C
	.extern UNK_020F96DC
	.extern UNK_020FA5FC
	.extern UNK_020FA6E8
	.extern UNK_020FCAC8
	.extern UNK_020FD1B0

	.section .rodata

	.balign 4
	.global UNK_020F2BC4
UNK_020F2BC4: ; 0x020F2BC4
	.byte 0x04, 0xFF

	.balign 4
	.global UNK_020F2BC8
UNK_020F2BC8: ; 0x020F2BC8
	.byte 0x00, 0xFF

	.balign 4
	.global UNK_020F2BCC
UNK_020F2BCC: ; 0x020F2BCC
	.byte 0x03, 0x05, 0x08

	.balign 4
	.global UNK_020F2BD0
UNK_020F2BD0: ; 0x020F2BD0
	.byte 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08

	.balign 4
	.global UNK_020F2BDC
UNK_020F2BDC: ; 0x020F2BDC
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF

	.balign 4
	.global UNK_020F2BE8
UNK_020F2BE8: ; 0x020F2BE8
	.byte 0x00, 0x05, 0x01, 0x01, 0x04, 0x04, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03

	.balign 4
	.global UNK_020F2BF4
UNK_020F2BF4: ; 0x020F2BF4
	.word ov70_021D74E0, ov70_021D758C, ov70_021D755C, SDK_OVERLAY_OVERLAY_70_ID

	.balign 4
	.global UNK_020F2C04
UNK_020F2C04: ; 0x020F2C04
	.word ov84_021D74E0, ov84_021D7748, ov84_021D76A4, SDK_OVERLAY_OVERLAY_84_ID

	.balign 4
	.global UNK_020F2C14
UNK_020F2C14: ; 0x020F2C14
	.word ov85_021D74E0, ov85_021D75A0, ov85_021D7644, SDK_OVERLAY_OVERLAY_85_ID

	.balign 4
	.global UNK_020F2C24
UNK_020F2C24: ; 0x020F2C24
	.word ov58_021D9A20, ov58_021D9B8C, ov58_021D9BF0, SDK_OVERLAY_OVERLAY_58_ID

	.balign 4
	.global UNK_020F2C34
UNK_020F2C34: ; 0x020F2C34
	.word ov64_021D74E0, ov64_021D7640, ov64_021D76F4, SDK_OVERLAY_OVERLAY_64_ID

	.balign 4
	.global UNK_020F2C44
UNK_020F2C44: ; 0x020F2C44
	.word ov16_021D74E0, ov16_021D7588, ov16_021D7614, SDK_OVERLAY_OVERLAY_16_ID

	.balign 4
	.global UNK_020F2C54
UNK_020F2C54: ; 0x020F2C54
	.word ov57_021D74E0, ov57_021D7714, ov57_021D7944, SDK_OVERLAY_OVERLAY_57_ID

	.balign 4
	.global UNK_020F2C64
UNK_020F2C64: ; 0x020F2C64
	.word ov80_0222DFD0, ov80_0222E134, ov80_0222E25C, SDK_OVERLAY_OVERLAY_80_ID

	.balign 4
	.global UNK_020F2C74
UNK_020F2C74: ; 0x020F2C74
	.word ov82_0222DA34, ov82_0222DB7C, ov82_0222DC50, SDK_OVERLAY_OVERLAY_82_ID

	.balign 4
	.global UNK_020F2C84
UNK_020F2C84: ; 0x020F2C84
	.word ov76_021D74E0, ov76_021D7568, ov76_021D761C, SDK_OVERLAY_OVERLAY_76_ID

	.balign 4
	.global UNK_020F2C94
UNK_020F2C94: ; 0x020F2C94
	.word ov53_021D74E0, ov53_021D7654, ov53_021D7764, SDK_OVERLAY_OVERLAY_53_ID

	.balign 4
	.global UNK_020F2CA4
UNK_020F2CA4: ; 0x020F2CA4
	.word ov81_02237E40, ov81_02238064, ov81_02238004, SDK_OVERLAY_OVERLAY_81_ID

	.balign 4
	.global UNK_020F2CB4
UNK_020F2CB4: ; 0x020F2CB4
	.word ov74_021D74E0, ov74_021D755C, ov74_021D7540, SDK_OVERLAY_OVERLAY_74_ID

	.balign 4
	.global UNK_020F2CC4
UNK_020F2CC4: ; 0x020F2CC4
	.word ov60_021D74E0, ov60_021D76B8, ov60_021D75B0, SDK_OVERLAY_OVERLAY_60_ID

	.balign 4
	.global UNK_020F2CD4
UNK_020F2CD4: ; 0x020F2CD4
	.word ov66_021D74E0, ov66_021D7538, ov66_021D75B0, SDK_OVERLAY_OVERLAY_66_ID

	.balign 4
	.global UNK_020F2CE4
UNK_020F2CE4: ; 0x020F2CE4
	.word ov15_021D74E0, ov15_021D7558, ov15_021D7608, SDK_OVERLAY_OVERLAY_15_ID

	.balign 4
	.global UNK_020F2CF4
UNK_020F2CF4: ; 0x020F2CF4
	.word StoragePC_Overlay_Init, StoragePC_Overlay_Run, StoragePC_Overlay_Teardown, SDK_OVERLAY_OVERLAY_14_ID

	.balign 4
	.global UNK_020F2D04
UNK_020F2D04: ; 0x020F2D04
	.word ov54_021D74E0, ov54_021D764C, ov54_021D7740, SDK_OVERLAY_OVERLAY_54_ID

	.balign 4
	.global UNK_020F2D14
UNK_020F2D14: ; 0x020F2D14
	.word ov77_021D74E0, ov77_021D7604, ov77_021D7BAC, SDK_OVERLAY_OVERLAY_77_ID

	.balign 4
	.global UNK_020F2D24
UNK_020F2D24: ; 0x020F2D24
	.word ov67_021D74E0, ov67_021D75D0, ov67_021D7624, SDK_OVERLAY_OVERLAY_67_ID

	.balign 4
	.global UNK_020F2D34
UNK_020F2D34: ; 0x020F2D34
	.word ov55_021D7614, ov55_021D76BC, ov55_021D77AC, SDK_OVERLAY_OVERLAY_55_ID

	.balign 4
	.global UNK_020F2D44
UNK_020F2D44: ; 0x020F2D44
	.word ov68_021D74E0, ov68_021D75D8, ov68_021D762C, SDK_OVERLAY_OVERLAY_68_ID

	.balign 4
	.global UNK_020F2D54
UNK_020F2D54: ; 0x020F2D54
	.word ov55_021D756C, ov55_021D76BC, ov55_021D77AC, SDK_OVERLAY_OVERLAY_55_ID

	.balign 4
	.global UNK_020F2D64
UNK_020F2D64: ; 0x020F2D64
	.word HOF_OverlayInit, HOF_OverlayRun, HOF_OverlayTeardown, SDK_OVERLAY_OVERLAY_69_ID

	.balign 4
	.global UNK_020F2D74
UNK_020F2D74: ; 0x020F2D74
	.word ov75_021E6BA0, ov75_021E6D6C, ov75_021E6F00, SDK_OVERLAY_OVERLAY_75_ID

	.balign 4
	.global UNK_020F2D84
UNK_020F2D84: ; 0x020F2D84
	.word ov78_021D74E0, ov78_021D75D0, ov78_021D76B8, SDK_OVERLAY_OVERLAY_78_ID

	.balign 4
	.global UNK_020F2D94
UNK_020F2D94: ; 0x020F2D94
	.word sub_020377F0, sub_020377F4, sub_02037808, SDK_OVERLAY_OVERLAY_11_ID

	.balign 4
	.global UNK_020F2DA4
UNK_020F2DA4: ; 0x020F2DA4
	.word ov86_021D74E0, ov86_021D758C, ov86_021D76B0, SDK_OVERLAY_OVERLAY_86_ID

	.section .data

	.balign 4
	.global UNK_02105DB8
UNK_02105DB8: ; 0x02105DB8
	.word 0 ; u8 *

	.balign 4
	.global UNK_02105DBC
UNK_02105DBC: ; 0x02105DBC
	.word ov71_0222D5C0, ov71_0222D9C8, ov71_0222E438, SDK_OVERLAY_OVERLAY_71_ID

	.balign 4
	.global UNK_02105DCC
UNK_02105DCC: ; 0x02105DCC
	.word ov17_021DDB58, ov17_021DDC30, ov17_021DDCF4, SDK_OVERLAY_OVERLAY_17_ID

	.balign 4
	.global UNK_02105DDC
UNK_02105DDC: ; 0x02105DDC
	.word ov17_021D83E4, ov17_021D84F0, ov17_021D8738, SDK_OVERLAY_OVERLAY_17_ID

	.text

	thumb_func_start sub_020377F0
sub_020377F0: ; 0x020377F0
	mov r0, #0x1
	bx lr

	thumb_func_start sub_020377F4
sub_020377F4: ; 0x020377F4
	push {r3, lr}
	bl ov11_0222D5C0
	cmp r0, #0x0
	beq _02037802
	mov r0, #0x1
	pop {r3, pc}
_02037802:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02037808
sub_02037808: ; 0x02037808
	mov r0, #0x1
	bx lr

	thumb_func_start sub_0203780C
sub_0203780C: ; 0x0203780C
	ldr r3, _02037814 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037818 ; =UNK_020F2D94
	bx r3
	.balign 4
_02037814: .word sub_020373D4
_02037818: .word UNK_020F2D94

	thumb_func_start sub_0203781C
sub_0203781C: ; 0x0203781C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02037840 ; =UNK_020F2D74
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02037840: .word UNK_020F2D74

	thumb_func_start sub_02037844
sub_02037844: ; 0x02037844
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r6, r1, #0x0
	bl Save_Bag_Get
	ldr r1, _02037898 ; =UNK_020F2BDC
	mov r2, #0xb
	bl CreateBagView
	add r3, r5, #0x0
	add r3, #0x94
	ldr r1, [r5, #0xc]
	ldr r3, [r3, #0x0]
	mov r2, #0x0
	add r4, r0, #0x0
	bl sub_0206E314
	ldr r1, [r5, #0x6c]
	add r0, r4, #0x0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl sub_0206E360
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetState
	cmp r0, #0x1
	bne _02037884
	add r0, r4, #0x0
	bl sub_0206E340
_02037884:
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl sub_0206E354
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0203781C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037898: .word UNK_020F2BDC

	thumb_func_start sub_0203789C
sub_0203789C: ; 0x0203789C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl Save_Bag_Get
	add r6, r0, #0x0
	cmp r4, #0x0
	beq _020378B4
	cmp r4, #0x1
	beq _020378BC
	b _020378C4
_020378B4:
	ldr r1, _020378F0 ; =UNK_020F2BC8
	ldr r0, _020378F4 ; =UNK_02105DB8
	str r1, [r0, #0x0]
	b _020378C8
_020378BC:
	ldr r1, _020378F8 ; =UNK_020F2BC4
	ldr r0, _020378F4 ; =UNK_02105DB8
	str r1, [r0, #0x0]
	b _020378C8
_020378C4:
	bl GF_AssertFail
_020378C8:
	ldr r1, _020378F4 ; =UNK_02105DB8
	add r0, r6, #0x0
	ldr r1, [r1, #0x0]
	mov r2, #0x20
	bl CreateBagView
	add r3, r5, #0x0
	add r3, #0x94
	ldr r1, [r5, #0xc]
	ldr r3, [r3, #0x0]
	add r4, r0, #0x0
	mov r2, #0x3
	bl sub_0206E314
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0203781C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_020378F0: .word UNK_020F2BC8
_020378F4: .word UNK_02105DB8
_020378F8: .word UNK_020F2BC4

	thumb_func_start sub_020378FC
sub_020378FC: ; 0x020378FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_0206E37C
	add r4, r0, #0x0
	beq _02037916
	add r0, r5, #0x0
	bl sub_0206E384
	cmp r0, #0x5
	bne _02037916
	bl GF_AssertFail
_02037916:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0203791C
sub_0203791C: ; 0x0203791C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02037940 ; =UNK_020F2D44
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02037940: .word UNK_020F2D44

	thumb_func_start sub_02037944
sub_02037944: ; 0x02037944
	push {r3-r5, lr}
	sub sp, #0x10
	ldr r4, _02037968 ; =UNK_020F2D24
	add r3, sp, #0x0
	add r5, r0, #0x0
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r1, r2, #0x0
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02037968: .word UNK_020F2D24

	thumb_func_start sub_0203796C
sub_0203796C: ; 0x0203796C
	ldr r3, _02037974 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037978 ; =UNK_020FA6E8
	bx r3
	.balign 4
_02037974: .word sub_020373D4
_02037978: .word UNK_020FA6E8

	thumb_func_start sub_0203797C
sub_0203797C: ; 0x0203797C
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x40
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x40
	bl MIi_CpuClearFast
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_Mailbox_Get
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	add r0, r4, #0x0
	add r0, #0x21
	strb r6, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x20
	strb r7, [r0, #0x0]
	str r5, [r4, #0x1c]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_020379C8
sub_020379C8: ; 0x020379C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r2, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	add r1, r5, #0x0
	add r3, r2, #0x0
	bl sub_0203797C
	add r4, r0, #0x0
	str r6, [r4, #0x18]
	add r0, #0x22
	strb r7, [r0, #0x0]
	ldr r1, _020379F4 ; =UNK_020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_020379F4: .word UNK_020F96DC

	thumb_func_start sub_020379F8
sub_020379F8: ; 0x020379F8
	push {r3-r5, lr}
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0x3
	add r5, r1, #0x0
	bl sub_0203797C
	add r4, r0, #0x0
	ldr r1, _02037A18 ; =UNK_020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02037A18: .word UNK_020F96DC

	thumb_func_start sub_02037A1C
sub_02037A1C: ; 0x02037A1C
	push {r3-r5, lr}
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0x13
	add r5, r1, #0x0
	bl sub_0203797C
	add r4, r0, #0x0
	ldr r1, _02037A3C ; =UNK_020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02037A3C: .word UNK_020F96DC

	thumb_func_start sub_02037A40
sub_02037A40: ; 0x02037A40
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02037A48
sub_02037A48: ; 0x02037A48
	push {r4-r6, lr}
	add r4, r2, #0x0
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0x12
	add r5, r1, #0x0
	bl sub_0203797C
	add r6, r0, #0x0
	add r0, #0x22
	strb r4, [r0, #0x0]
	ldr r1, _02037A6C ; =UNK_020F96DC
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl sub_020373D4
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037A6C: .word UNK_020F96DC

	thumb_func_start sub_02037A70
sub_02037A70: ; 0x02037A70
	add r0, #0x23
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02037A78
sub_02037A78: ; 0x02037A78
	ldrb r0, [r0, #0x14]
	bx lr

	thumb_func_start sub_02037A7C
sub_02037A7C: ; 0x02037A7C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02046530
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x4
	bhi _02037B3A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02037AA8: ; jump table (using 16-bit offset)
	.short _02037AB2 - _02037AA8 - 2; case 0
	.short _02037AC2 - _02037AA8 - 2; case 1
	.short _02037AF8 - _02037AA8 - 2; case 2
	.short _02037B1A - _02037AA8 - 2; case 3
	.short _02037B30 - _02037AA8 - 2; case 4
_02037AB2:
	ldr r1, _02037B40 ; =UNK_020F96DC
	ldr r2, [r4, #0x4]
	add r0, r6, #0x0
	bl sub_020373D4
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02037B3A
_02037AC2:
	add r0, r6, #0x0
	bl sub_0204647C
	cmp r0, #0x0
	bne _02037B3A
	ldr r0, [r4, #0x4]
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	cmp r0, #0x6
	beq _02037AE6
	cmp r0, #0x7
	bne _02037AF2
	mov r0, #0x2
	bl sub_020527D8
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02037B3A
_02037AE6:
	mov r0, #0x1
	bl sub_020527D8
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02037B3A
_02037AF2:
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02037B3A
_02037AF8:
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	mov r2, #0x0
	bl sub_02037C7C
	str r0, [r4, #0x8]
	ldr r1, [r4, #0x4]
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	strb r1, [r0, #0x14]
	ldr r1, [r4, #0x8]
	add r0, r6, #0x0
	bl sub_0203796C
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _02037B3A
_02037B1A:
	add r0, r6, #0x0
	bl sub_0204647C
	cmp r0, #0x0
	bne _02037B3A
	ldr r0, [r4, #0x8]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r5, #0x0]
	b _02037B3A
_02037B30:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r4-r6, pc}
_02037B3A:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02037B40: .word UNK_020F96DC

	thumb_func_start sub_02037B44
sub_02037B44: ; 0x02037B44
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xc
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x0
	mov r3, #0x2
	str r5, [r4, #0x0]
	bl sub_0203797C
	add r5, r0, #0x0
	add r0, #0x32
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	add r2, r4, #0x0
	bic r1, r0
	mov r0, #0x2
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x32
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x20
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1e
	add r0, #0x33
	strb r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x14]
	ldr r1, _02037BAC ; =sub_02037A7C
	add r0, r7, #0x0
	str r5, [r4, #0x4]
	bl sub_0204640C
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_02037BAC: .word sub_02037A7C

	thumb_func_start sub_02037BB0
sub_02037BB0: ; 0x02037BB0
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r6, r3, #0x0
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0xd
	add r7, r1, #0x0
	bl sub_0203797C
	add r4, r0, #0x0
	ldr r1, [sp, #0x1c]
	add r0, #0x22
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x2
	add r0, #0x29
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x2a
	strb r5, [r0, #0x0]
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _02037BE6
	add r0, r4, #0x0
	add r0, #0x2b
	strb r6, [r0, #0x0]
	b _02037BEE
_02037BE6:
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x2b
	strb r1, [r0, #0x0]
_02037BEE:
	ldr r1, _02037BFC ; =UNK_020F96DC
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_02037BFC: .word UNK_020F96DC

	thumb_func_start sub_02037C00
sub_02037C00: ; 0x02037C00
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x30
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	strb r6, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl GetPartyCount
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0xc]
	bl sub_0202A918
	str r0, [r4, #0x20]
	ldr r0, [r5, #0xc]
	bl SaveArray_IsNatDexEnabled
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0xc]
	bl sub_02079C70
	str r0, [r4, #0x2c]
	mov r0, #0x0
	str r0, [r4, #0x28]
	ldr r1, _02037C74 ; =UNK_020F2A9C
	add r0, r4, #0x0
	bl sub_0207B000
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_0207C2A4
	ldr r1, _02037C78 ; =UNK_020FA6E8
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037C74: .word UNK_020F2A9C
_02037C78: .word UNK_020FA6E8

	thumb_func_start sub_02037C7C
sub_02037C7C: ; 0x02037C7C
	push {r4-r6, lr}
	ldr r5, [r0, #0xc]
	add r0, r1, #0x0
	mov r1, #0x30
	add r6, r2, #0x0
	bl AllocFromHeapAtEnd
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	mov r0, #0x0
	strb r0, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl GetPartyCount
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	strb r6, [r4, #0x12]
	add r0, r5, #0x0
	bl SaveArray_IsNatDexEnabled
	str r0, [r4, #0x1c]
	add r0, r5, #0x0
	bl sub_02079C70
	str r0, [r4, #0x2c]
	add r0, r5, #0x0
	bl sub_0202A918
	str r0, [r4, #0x20]
	ldr r1, _02037CEC ; =UNK_020F2BD0
	add r0, r4, #0x0
	bl sub_0207B000
	add r0, r5, #0x0
	bl Save_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_0207C2A4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037CEC: .word UNK_020F2BD0

	thumb_func_start sub_02037CF0
sub_02037CF0: ; 0x02037CF0
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r1, #0x30
	add r6, r2, #0x0
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	strb r6, [r4, #0x14]
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	mov r0, #0x2
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0xc]
	bl SaveArray_IsNatDexEnabled
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0xc]
	bl sub_02079C70
	str r0, [r4, #0x2c]
	ldr r1, _02037D58 ; =UNK_020F2BCC
	add r0, r4, #0x0
	bl sub_0207B000
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_0207C2A4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_0203796C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037D58: .word UNK_020F2BCC

	thumb_func_start sub_02037D5C
sub_02037D5C: ; 0x02037D5C
	ldrb r0, [r0, #0x16]
	bx lr

	thumb_func_start LaunchStoragePCInterface
LaunchStoragePCInterface: ; 0x02037D60
	ldr r3, _02037D68 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037D6C ; =UNK_020F2CF4
	bx r3
	.balign 4
_02037D68: .word sub_020373D4
_02037D6C: .word UNK_020F2CF4

	thumb_func_start sub_02037D70
sub_02037D70: ; 0x02037D70
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	bl sub_02046530
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl sub_02046528
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02037D9A
	cmp r1, #0x1
	beq _02037DA8
	cmp r1, #0x2
	beq _02037DB8
	b _02037E12
_02037D9A:
	ldr r1, [r5, #0xc]
	bl sub_02037E80
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02037E12
_02037DA8:
	bl sub_0204647C
	cmp r0, #0x0
	bne _02037E12
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02037E12
_02037DB8:
	ldr r0, [r5, #0xc]
	bl sub_020853E4
	cmp r0, #0x0
	bne _02037DCC
	ldr r0, [r5, #0xc]
	bl sub_020853E8
	cmp r0, #0x0
	bne _02037DD4
_02037DCC:
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _02037E00
_02037DD4:
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	ldr r0, [r5, #0xc]
	bne _02037DEC
	bl sub_020853EC
	ldr r1, [r5, #0x4]
	strh r0, [r1, #0x0]
	b _02037E00
_02037DEC:
	add r1, sp, #0x0
	bl sub_020853F0
	add r0, sp, #0x0
	ldrh r2, [r0, #0x0]
	ldr r1, [r5, #0x4]
	strh r2, [r1, #0x0]
	ldrh r1, [r0, #0x2]
	ldr r0, [r5, #0x8]
	strh r1, [r0, #0x0]
_02037E00:
	ldr r0, [r5, #0xc]
	bl sub_020853A8
	add r0, r5, #0x0
	bl FreeToHeap
	add sp, #0x4
	mov r0, #0x1
	pop {r3-r6, pc}
_02037E12:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start sub_02037E18
sub_02037E18: ; 0x02037E18
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl sub_02046528
	add r7, r0, #0x0
	mov r0, #0x20
	mov r1, #0x10
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r6, #0x0
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
	str r6, [r4, #0x8]
	bne _02037E56
	mov r0, #0x0
	ldr r2, [r7, #0xc]
	add r1, r0, #0x0
	mov r3, #0x20
	bl sub_02085338
	str r0, [r4, #0xc]
	ldrh r1, [r5, #0x0]
	bl sub_020853B0
	b _02037E6C
_02037E56:
	ldr r2, [r7, #0xc]
	mov r0, #0x1
	mov r1, #0x0
	mov r3, #0x20
	bl sub_02085338
	str r0, [r4, #0xc]
	ldrh r1, [r5, #0x0]
	ldrh r2, [r6, #0x0]
	bl sub_020853B4
_02037E6C:
	ldr r0, [sp, #0x0]
	ldr r1, _02037E7C ; =sub_02037D70
	add r2, r4, #0x0
	bl sub_0204640C
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02037E7C: .word sub_02037D70

	thumb_func_start sub_02037E80
sub_02037E80: ; 0x02037E80
	ldr r3, _02037E88 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037E8C ; =UNK_020F2CE4
	bx r3
	.balign 4
_02037E88: .word sub_020373D4
_02037E8C: .word UNK_020F2CE4

	thumb_func_start sub_02037E90
sub_02037E90: ; 0x02037E90
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02037EB4 ; =UNK_020F2CD4
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02037EB4: .word UNK_020F2CD4

	thumb_func_start sub_02037EB8
sub_02037EB8: ; 0x02037EB8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034E0C
	mov r1, #0x5
	mov r0, #0xb
	lsl r1, r1, #0x6
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl sub_0205F7A0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02037E90
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_02037EE8
sub_02037EE8: ; 0x02037EE8
	ldr r3, _02037EF0 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037EF4 ; =UNK_020F2CC4
	bx r3
	.balign 4
_02037EF0: .word sub_020373D4
_02037EF4: .word UNK_020F2CC4

	thumb_func_start sub_02037EF8
sub_02037EF8: ; 0x02037EF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x2
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptEnvironment_GetSavePtr
	bl Save_PlayerData_GetOptionsAddr
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl sub_02037EE8
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_02037F1C
sub_02037F1C: ; 0x02037F1C
	ldr r3, _02037F24 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037F28 ; =UNK_020FCAC8
	bx r3
	.balign 4
_02037F24: .word sub_020373D4
_02037F28: .word UNK_020FCAC8

	thumb_func_start sub_02037F2C
sub_02037F2C: ; 0x02037F2C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl ScriptEnvironment_GetSavePtr
	mov r1, #0xb
	str r1, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl sub_020854E0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02037F1C
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_02037F58
sub_02037F58: ; 0x02037F58
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	cmp r5, #0x3
	bne _02037F74
	bl ScriptEnvironment_GetSavePtr
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl sub_020855B0
	b _02037F82
_02037F74:
	bl ScriptEnvironment_GetSavePtr
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl sub_02085538
_02037F82:
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl sub_02037F1C
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start sub_02037F90
sub_02037F90: ; 0x02037F90
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	bl ScriptEnvironment_GetSavePtr
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl sub_02085578
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl sub_02037F1C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02037FB4
sub_02037FB4: ; 0x02037FB4
	ldr r3, _02037FBC ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02037FC0 ; =UNK_020FD1B0
	bx r3
	.balign 4
_02037FBC: .word sub_020373D4
_02037FC0: .word UNK_020FD1B0

	thumb_func_start sub_02037FC4
sub_02037FC4: ; 0x02037FC4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	bl ScriptEnvironment_GetSavePtr
	add r1, r5, #0x0
	bl sub_02087D00
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_02037FB4
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_02037FE4
sub_02037FE4: ; 0x02037FE4
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02038008 ; =UNK_020F2CB4
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02038008: .word UNK_020F2CB4

	thumb_func_start sub_0203800C
sub_0203800C: ; 0x0203800C
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x20
	add r7, r2, #0x0
	add r6, r3, #0x0
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x20
	add r4, r0, #0x0
	bl memset
	add r0, r5, #0x0
	bl SaveArray_PlayerParty_Get
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl Save_FashionData_Get
	str r0, [sp, #0x0]
	mov r1, #0x0
	bl sub_02027008
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl sub_0202708C
	str r7, [r4, #0x4]
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	add r0, r5, #0x0
	bl Save_GameStats_Get
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	bl Save_PlayerData_GetProfileAddr
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0x18]
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start sub_02038070
sub_02038070: ; 0x02038070
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0203808E
	cmp r0, #0x1
	beq _0203809E
	b _020380C8
_0203808E:
	ldr r1, [r5, #0xc]
	add r0, r4, #0x0
	bl sub_0203811C
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _020380C8
_0203809E:
	add r0, r4, #0x0
	bl sub_0204647C
	cmp r0, #0x0
	bne _020380C8
	ldr r0, [r5, #0x8]
	cmp r0, #0x1
	bne _020380B2
	mov r1, #0x1
	b _020380B4
_020380B2:
	mov r1, #0x0
_020380B4:
	ldr r0, [r5, #0x4]
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_020380C8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start sub_020380CC
sub_020380CC: ; 0x020380CC
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x20
	mov r1, #0x10
	add r7, r2, #0x0
	str r3, [sp, #0x4]
	bl AllocFromHeap
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x10
	mov r0, #0x0
_020380E8:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _020380E8
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	add r3, r4, #0x0
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	mov r0, #0x20
	add r3, #0x8
	bl sub_0203800C
	str r0, [r4, #0xc]
	ldr r1, _02038118 ; =sub_02038070
	add r0, r6, #0x0
	add r2, r4, #0x0
	str r5, [r4, #0x4]
	bl sub_0204640C
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02038118: .word sub_02038070

	thumb_func_start sub_0203811C
sub_0203811C: ; 0x0203811C
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _0203812C ; =UNK_02105DDC
	bl sub_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_0203812C: .word UNK_02105DDC

	thumb_func_start sub_02038130
sub_02038130: ; 0x02038130
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _02038140 ; =UNK_02105DCC
	bl sub_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_02038140: .word UNK_02105DCC

	thumb_func_start sub_02038144
sub_02038144: ; 0x02038144
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl Save_PlayerData_GetProfileAddr
	str r0, [r5, #0x4]
	ldr r0, [r4, #0xc]
	bl SaveArray_PlayerParty_Get
	str r0, [r5, #0x8]
	ldr r0, [r4, #0xc]
	mov r1, #0x9
	bl SaveArray_Get
	str r0, [r5, #0xc]
	ldr r0, [r4, #0xc]
	bl sub_02029AFC
	str r0, [r5, #0x14]
	ldr r0, [r4, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r5, #0x18]
	ldr r0, [r4, #0xc]
	bl Save_Pokedex_Get
	str r0, [r5, #0x24]
	ldr r0, [r4, #0xc]
	bl SaveArray_IsNatDexEnabled
	str r0, [r5, #0x30]
	ldr r0, [r4, #0xc]
	str r0, [r5, #0x10]
	add r0, r4, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x1c]
	ldr r0, [r4, #0xc]
	bl Save_GameStats_Get
	str r0, [r5, #0x20]
	bl PlayerProfile_sizeof
	add r1, r0, #0x0
	mov r0, #0x20
	bl AllocFromHeap
	str r0, [r5, #0x38]
	bl sub_020690C4
	add r1, r0, #0x0
	mov r0, #0x20
	bl AllocFromHeap
	str r0, [r5, #0x3c]
	bl sub_020690C4
	add r1, r0, #0x0
	mov r0, #0x20
	bl AllocFromHeap
	str r0, [r5, #0x40]
	str r4, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x34]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020381CC
sub_020381CC: ; 0x020381CC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020381DE
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x38]
_020381DE:
	ldr r0, [r4, #0x3c]
	cmp r0, #0x0
	beq _020381EC
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x3c]
_020381EC:
	ldr r0, [r4, #0x40]
	cmp r0, #0x0
	beq _020381FA
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x40]
_020381FA:
	pop {r4, pc}

	thumb_func_start sub_020381FC
sub_020381FC: ; 0x020381FC
	push {r4-r7, lr}
	sub sp, #0x34
	add r6, r0, #0x0
	bl sub_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x7
	bls _02038218
	b _020383C8
_02038218:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02038224: ; jump table (using 16-bit offset)
	.short _02038234 - _02038224 - 2; case 0
	.short _0203824A - _02038224 - 2; case 1
	.short _02038258 - _02038224 - 2; case 2
	.short _0203826A - _02038224 - 2; case 3
	.short _02038288 - _02038224 - 2; case 4
	.short _020382F6 - _02038224 - 2; case 5
	.short _02038386 - _02038224 - 2; case 6
	.short _020383B2 - _02038224 - 2; case 7
_02038234:
	bl sub_02033590
	cmp r0, #0x0
	bne _02038242
	add r0, r6, #0x0
	bl sub_0204AF3C
_02038242:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020383C8
_0203824A:
	add r0, r4, #0x4
	add r1, r5, #0x0
	bl sub_02038144
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02038258:
	ldr r1, _020383D0 ; =UNK_02105DBC
	add r0, r6, #0x0
	add r2, r4, #0x4
	bl sub_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020383C8
_0203826A:
	ldr r1, [r4, #0x2c]
	cmp r1, #0x0
	bne _02038282
	add r0, r4, #0x4
	bl sub_020381CC
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x34
	mov r0, #0x1
	pop {r4-r7, pc}
_02038282:
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020383C8
_02038288:
	ldr r0, [r4, #0x3c]
	str r0, [r4, #0x50]
	ldr r0, [r4, #0x40]
	bl sub_020690E4
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x44]
	bl sub_020690E4
	str r0, [r4, #0x4c]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x5c]
	mov r0, #0x1
	str r0, [r4, #0x58]
	add r0, r5, #0x0
	bl Script_GetTimeOfDay
	cmp r0, #0x4
	bhi _020382C8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020382BE: ; jump table (using 16-bit offset)
	.short _020382C8 - _020382BE - 2; case 0
	.short _020382C8 - _020382BE - 2; case 1
	.short _020382CE - _020382BE - 2; case 2
	.short _020382D4 - _020382BE - 2; case 3
	.short _020382D4 - _020382BE - 2; case 4
_020382C8:
	mov r0, #0x0
	str r0, [r4, #0x54]
	b _020382D8
_020382CE:
	mov r0, #0x1
	str r0, [r4, #0x54]
	b _020382D8
_020382D4:
	mov r0, #0x2
	str r0, [r4, #0x54]
_020382D8:
	bl sub_02033590
	cmp r0, #0x0
	beq _020382E4
	mov r0, #0x3
	str r0, [r4, #0x54]
_020382E4:
	add r2, r4, #0x0
	ldr r1, _020383D4 ; =UNK_020F2CA4
	add r0, r6, #0x0
	add r2, #0x48
	bl sub_02046500
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _020383C8
_020382F6:
	ldr r0, [r4, #0x44]
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	add r3, r0, #0x0
	add r0, sp, #0x30
	str r0, [sp, #0x0]
	lsl r3, r3, #0x10
	ldr r1, [r4, #0x44]
	mov r0, #0x0
	mov r2, #0x1
	lsr r3, r3, #0x10
	bl GetMonEvolution
	str r0, [sp, #0x20]
	cmp r0, #0x0
	beq _02038380
	mov r0, #0x3
	mov r1, #0x1a
	lsl r2, r0, #0x10
	bl CreateHeap
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [sp, #0x24]
	ldr r0, [r5, #0xc]
	bl sub_02079C70
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_Pokedex_Get
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	str r0, [sp, #0x28]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0xc]
	bl Save_Poketch_Get
	str r6, [sp, #0x0]
	ldr r1, [sp, #0x28]
	str r7, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x20]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x30]
	ldr r3, [sp, #0x24]
	str r0, [sp, #0x14]
	mov r0, #0x4
	str r0, [sp, #0x18]
	mov r0, #0x1a
	str r0, [sp, #0x1c]
	ldr r1, [r4, #0x44]
	mov r0, #0x0
	bl sub_0206C700
	str r0, [r4, #0x60]
	mov r0, #0x6
	str r0, [r4, #0x0]
	b _020383C8
_02038380:
	mov r0, #0x7
	str r0, [r4, #0x0]
	b _020383C8
_02038386:
	ldr r0, [r4, #0x60]
	bl sub_0206C91C
	cmp r0, #0x0
	beq _020383C8
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x30]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	ldr r0, [r4, #0x44]
	bl CopyPokemonToPokemon
	ldr r0, [r4, #0x60]
	bl sub_0206C92C
	mov r0, #0x1a
	bl DestroyHeap
	mov r0, #0x7
	str r0, [r4, #0x0]
	b _020383C8
_020383B2:
	ldr r0, [r4, #0x38]
	add r0, r0, #0x1
	str r0, [r4, #0x38]
	mov r0, #0x2
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	mov r1, #0x10
	bl GameStats_AddSpecial
_020383C8:
	mov r0, #0x0
	add sp, #0x34
	pop {r4-r7, pc}
	nop
_020383D0: .word UNK_02105DBC
_020383D4: .word UNK_020F2CA4

	thumb_func_start sub_020383D8
sub_020383D8: ; 0x020383D8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x20
	mov r1, #0x68
	bl AllocFromHeap
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldr r1, _020383F4 ; =sub_020381FC
	add r0, r4, #0x0
	bl sub_0204640C
	pop {r4, pc}
	.balign 4
_020383F4: .word sub_020381FC

	thumb_func_start sub_020383F8
sub_020383F8: ; 0x020383F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	mov r1, #0xc
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [r5, #0x7c]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x8]
	ldr r1, _02038428 ; =UNK_020F2C94
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	pop {r3-r5, pc}
	nop
_02038428: .word UNK_020F2C94

	thumb_func_start sub_0203842C
sub_0203842C: ; 0x0203842C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x7c]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	str r0, [r4, #0xc]
	add r0, r5, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	ldr r1, _02038468 ; =UNK_020F2D04
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02038468: .word UNK_020F2D04

	thumb_func_start sub_0203846C
sub_0203846C: ; 0x0203846C
	ldr r3, _02038474 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02038478 ; =UNK_020F2D54
	bx r3
	.balign 4
_02038474: .word sub_020373D4
_02038478: .word UNK_020F2D54

	thumb_func_start sub_0203847C
sub_0203847C: ; 0x0203847C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl sub_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x3
	bhi _02038544
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020384A0: ; jump table (using 16-bit offset)
	.short _020384A8 - _020384A0 - 2; case 0
	.short _020384B6 - _020384A0 - 2; case 1
	.short _020384C8 - _020384A0 - 2; case 2
	.short _020384D6 - _020384A0 - 2; case 3
_020384A8:
	add r0, r5, #0x0
	bl sub_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02038544
_020384B6:
	ldr r1, _02038548 ; =UNK_020FA5FC
	ldr r2, [r4, #0xc]
	add r0, r5, #0x0
	bl sub_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02038544
_020384C8:
	add r0, r5, #0x0
	bl sub_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02038544
_020384D6:
	ldr r1, [r4, #0xc]
	ldr r0, [r1, #0x0]
	cmp r0, #0x1
	bne _020384F2
	ldr r0, [r1, #0x18]
	ldr r1, [r4, #0x10]
	bl StringCompare
	cmp r0, #0x0
	bne _02038514
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	str r1, [r0, #0x14]
	b _02038514
_020384F2:
	cmp r0, #0x5
	bne _02038514
	ldr r0, [r1, #0x18]
	bl String_c_str
	add r7, r0, #0x0
	ldr r0, [r6, #0xc]
	bl sub_0202881C
	add r1, r7, #0x0
	bl sub_02028854
	cmp r0, #0x0
	beq _02038514
	ldr r0, [r4, #0xc]
	mov r1, #0x2
	str r1, [r0, #0x14]
_02038514:
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x14]
	cmp r0, #0x0
	bne _02038522
	add r0, r5, #0x0
	bl sub_0203854C
_02038522:
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _0203852E
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x14]
	strh r0, [r1, #0x0]
_0203852E:
	ldr r0, [r4, #0xc]
	bl sub_02077AC4
	ldr r0, [r4, #0x10]
	bl String_Delete
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r7, pc}
_02038544:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02038548: .word UNK_020FA5FC

	thumb_func_start sub_0203854C
sub_0203854C: ; 0x0203854C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl sub_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl sub_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x0]
	cmp r0, #0x6
	bhi _020385CA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02038572: ; jump table (using 16-bit offset)
	.short _02038580 - _02038572 - 2; case 0
	.short _02038590 - _02038572 - 2; case 1
	.short _020385CA - _02038572 - 2; case 2
	.short _020385CA - _02038572 - 2; case 3
	.short _020385CA - _02038572 - 2; case 4
	.short _020385A8 - _02038572 - 2; case 5
	.short _020385BC - _02038572 - 2; case 6
_02038580:
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	ldr r1, [r4, #0xc]
	add r1, #0x1c
	bl CopyPlayerName
	pop {r3-r5, pc}
_02038590:
	ldr r0, [r5, #0xc]
	bl SaveArray_PlayerParty_Get
	ldr r1, [r4, #0x4]
	bl GetPartyMonByIndex
	ldr r2, [r4, #0xc]
	mov r1, #0x75
	add r2, #0x1c
	bl SetMonData
	pop {r3-r5, pc}
_020385A8:
	ldr r0, [r5, #0xc]
	bl sub_0202881C
	ldr r3, [r4, #0xc]
	mov r1, #0x0
	ldr r3, [r3, #0x18]
	add r2, r1, #0x0
	bl sub_020287C0
	pop {r3-r5, pc}
_020385BC:
	ldr r0, [r5, #0xc]
	bl sub_02024EB4
	ldr r1, [r4, #0xc]
	ldr r1, [r1, #0x18]
	bl sub_02024F18
_020385CA:
	pop {r3-r5, pc}

	thumb_func_start CreateNamingScreen
CreateNamingScreen: ; 0x020385CC
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x4]
	add r6, r1, #0x0
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	ldr r5, [sp, #0x2c]
	bl sub_02046528
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x28]
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x30]
	str r0, [r4, #0x8]
	ldr r0, [r7, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r0, #0xb
	add r1, r6, #0x0
	bl sub_02077A84
	str r0, [r4, #0xc]
	mov r0, #0xc
	mov r1, #0xb
	bl String_New
	str r0, [r4, #0x10]
	cmp r6, #0x1
	beq _02038620
	cmp r6, #0x5
	beq _02038656
	b _02038660
_02038620:
	ldr r0, [r7, #0xc]
	bl SaveArray_PlayerParty_Get
	ldr r1, [r4, #0x4]
	bl GetPartyMonByIndex
	mov r1, #0x6f
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	ldr r1, [r4, #0xc]
	mov r2, #0x0
	str r0, [r1, #0x10]
	add r0, r6, #0x0
	mov r1, #0x70
	bl GetMonData
	ldr r1, [r4, #0xc]
	cmp r5, #0x0
	str r0, [r1, #0x8]
	beq _0203866E
	ldr r0, [r4, #0x10]
	add r1, r5, #0x0
	bl CopyU16ArrayToString
	b _0203866E
_02038656:
	ldr r0, [r4, #0x10]
	add r1, r5, #0x0
	bl CopyU16ArrayToString
	b _0203866E
_02038660:
	cmp r5, #0x0
	beq _0203866E
	ldr r0, [r4, #0xc]
	add r1, r5, #0x0
	ldr r0, [r0, #0x18]
	bl CopyU16ArrayToString
_0203866E:
	ldr r0, [sp, #0x4]
	ldr r1, _0203867C ; =sub_0203847C
	add r2, r4, #0x0
	bl sub_0204640C
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0203867C: .word sub_0203847C

	thumb_func_start sub_02038680
sub_02038680: ; 0x02038680
	ldr r3, _02038688 ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _0203868C ; =UNK_020F2C54
	bx r3
	.balign 4
_02038688: .word sub_020373D4
_0203868C: .word UNK_020F2C54

	thumb_func_start sub_02038690
sub_02038690: ; 0x02038690
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _020386A0 ; =UNK_020F2C44
	bl sub_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_020386A0: .word UNK_020F2C44

	thumb_func_start sub_020386A4
sub_020386A4: ; 0x020386A4
	ldr r3, _020386AC ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _020386B0 ; =UNK_020F2C34
	bx r3
	.balign 4
_020386AC: .word sub_020373D4
_020386B0: .word UNK_020F2C34

	thumb_func_start sub_020386B4
sub_020386B4: ; 0x020386B4
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl sub_02029ABC
	ldr r5, _020386DC ; =UNK_020F2C24
	add r3, sp, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r1, r2, #0x0
	ldr r2, [r4, #0xc]
	add r0, r4, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_020386DC: .word UNK_020F2C24

	thumb_func_start sub_020386E0
sub_020386E0: ; 0x020386E0
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r3, _0203878C ; =UNK_020F2C64
	add r2, sp, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0xb
	mov r1, #0x44
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl sub_0202ABBC
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Save_SysInfo_Get
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	mov r1, #0x2
	bl SaveArray_Get
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl GetStoragePCPointer
	str r0, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl Save_Pokedex_Get
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl sub_020286EC
	str r0, [r4, #0x14]
	ldr r0, [r5, #0xc]
	bl sub_02029AFC
	str r0, [r4, #0x18]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetProfileAddr
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x24]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	str r0, [r4, #0x28]
	add r0, r5, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x2c]
	ldr r0, [r5, #0xc]
	bl sub_02079C70
	str r0, [r4, #0x3c]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x20]
	ldr r0, [r5, #0xc]
	bl SaveArray_IsNatDexEnabled
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x14]
	bl sub_02033830
	str r0, [r4, #0x38]
	ldr r0, [r5, #0xc]
	bl Save_Bag_Get
	str r0, [r4, #0x30]
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r4, #0x0
	str r6, [r4, #0x40]
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0203878C: .word UNK_020F2C64

	thumb_func_start sub_02038790
sub_02038790: ; 0x02038790
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r3, _02038800 ; =UNK_020F2C74
	add r7, r2, #0x0
	add r2, sp, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0xb
	mov r1, #0x28
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SaveStruct23_GetSubstruct2
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl SaveStruct23_GetSubstruct4
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl Save_SysInfo_Get
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl sub_020286EC
	bl sub_02028228
	str r0, [r4, #0x14]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl sub_020286EC
	bl sub_02033830
	str r0, [r4, #0x1c]
	str r6, [r4, #0x18]
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r4, #0x0
	str r7, [r4, #0x24]
	bl sub_020373D4
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02038800: .word UNK_020F2C74

	thumb_func_start ShowGeonetScreen
ShowGeonetScreen: ; 0x02038804
	ldr r3, _0203880C ; =sub_020373D4
	ldr r1, _02038810 ; =UNK_020F2D14
	ldr r2, [r0, #0xc]
	bx r3
	.balign 4
_0203880C: .word sub_020373D4
_02038810: .word UNK_020F2D14

	thumb_func_start sub_02038814
sub_02038814: ; 0x02038814
	ldr r3, _0203881C ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02038820 ; =UNK_020F2D64
	bx r3
	.balign 4
_0203881C: .word sub_020373D4
_02038820: .word UNK_020F2D64

	thumb_func_start sub_02038824
sub_02038824: ; 0x02038824
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0xb
	add r2, sp, #0x0
	bl LoadHallOfFame
	ldr r1, [sp, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x2
	bne _02038842
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}
_02038842:
	ldr r1, _02038850 ; =UNK_020F2BF4
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02038850: .word UNK_020F2BF4

	thumb_func_start sub_02038854
sub_02038854: ; 0x02038854
	ldr r3, _0203885C ; =sub_020373D4
	add r2, r1, #0x0
	ldr r1, _02038860 ; =UNK_020F2C04
	bx r3
	.balign 4
_0203885C: .word sub_020373D4
_02038860: .word UNK_020F2C04

	thumb_func_start sub_02038864
sub_02038864: ; 0x02038864
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02038888 ; =UNK_020F2C84
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02038888: .word UNK_020F2C84

	thumb_func_start sub_0203888C
sub_0203888C: ; 0x0203888C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _020388B0 ; =UNK_020F2D84
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl sub_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_020388B0: .word UNK_020F2D84

	thumb_func_start sub_020388B4
sub_020388B4: ; 0x020388B4
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SaveArray_PlayerParty_Get
	bl ov05_021ED49C
	add r5, r0, #0x0
	bne _020388CC
	bl GF_AssertFail
_020388CC:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_020613CC
	str r5, [sp, #0x0]
	ldr r0, [r4, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	bl Save_PlayerData_GetProfileAddr
	str r0, [sp, #0x8]
	ldr r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	bl FieldSystem_GetOverriddenMusicId
	add r1, sp, #0x0
	strh r0, [r1, #0xc]
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl sub_020863DC
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start sub_02038900
sub_02038900: ; 0x02038900
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _02038910 ; =UNK_020F2C14
	bl sub_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_02038910: .word UNK_020F2C14

	thumb_func_start sub_02038914
sub_02038914: ; 0x02038914
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	bl sub_02046528
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SaveArray_Flags_Get
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl sub_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl sub_02046530
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _02038944
	cmp r0, #0x1
	beq _02038956
	b _020389C6
_02038944:
	add r5, #0xc
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_02038900
	ldr r0, [r6, #0x0]
	add r0, r0, #0x1
	str r0, [r6, #0x0]
	b _020389C6
_02038956:
	add r0, r4, #0x0
	bl sub_0204647C
	cmp r0, #0x0
	bne _020389C6
	ldr r0, [r4, #0xc]
	bl Save_PlayerData_GetCoinsAddr
	str r0, [sp, #0x0]
	bl GF_RTC_DateTimeToSec
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r6, r1, #0x0
	bl CheckCoins
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0x8]
	ldr r2, [sp, #0x4]
	add r3, r6, #0x0
	bl GF_RTC_TimeDelta
	mov r2, #0x3c
	mov r3, #0x0
	bl _ll_sdiv
	add r3, r0, #0x0
	ldr r1, [sp, #0x8]
	ldr r2, [r5, #0x0]
	add r0, r4, #0x0
	bl sub_02061A8C
	ldr r0, [r4, #0xc]
	bl Save_PlayerData_GetCoinsAddr
	ldr r1, [r5, #0x0]
	bl SetCoins
	add r0, r7, #0x0
	bl sub_0205F6C8
	ldr r1, [r5, #0x18]
	cmp r1, r0
	ble _020389BA
	lsl r1, r1, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	bl sub_0205F6D8
_020389BA:
	add r0, r5, #0x0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_020389C6:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_020389CC
sub_020389CC: ; 0x020389CC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	bl sub_02046528
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetOptionsAddr
	str r0, [sp, #0x0]
	mov r0, #0x20
	add r1, r0, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	str r4, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl Save_PlayerData_GetCoinsAddr
	bl CheckCoins
	str r0, [r4, #0x0]
	bl GF_RTC_DateTimeToSec
	str r0, [r4, #0x4]
	str r1, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	str r0, [r4, #0x14]
	mov r0, #0x0
	str r0, [r4, #0x18]
	ldr r0, [sp, #0x0]
	bl Options_GetFrame
	str r0, [r4, #0x1c]
	lsl r1, r6, #0x18
	ldr r0, [r5, #0xc]
	lsr r1, r1, #0x18
	bl sub_02038A3C
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl Save_GameStats_Get
	mov r1, #0x5
	bl GameStats_AddSpecial
	ldr r1, _02038A38 ; =sub_02038914
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl sub_0204640C
	pop {r3-r7, pc}
	.balign 4
_02038A38: .word sub_02038914

	thumb_func_start sub_02038A3C
sub_02038A3C: ; 0x02038A3C
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	bl sub_0202881C
	add r4, r0, #0x0
	bl GetLCRNGSeed
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl sub_020287A4
	bl SetLCRNGSeed
	ldr r0, _02038AAC ; =UNK_020F2BE8
	add r1, sp, #0x8
	mov r2, #0xc
	bl MI_CpuCopy8
	mov r4, #0x0
	mov r7, #0xc
	add r6, sp, #0x8
_02038A68:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0xc
	bhs _02038A92
_02038A72:
	bl LCRandom
	add r1, r7, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r2, r0, #0x18
	ldrb r1, [r6, r4]
	ldrb r0, [r6, r2]
	strb r0, [r6, r4]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	strb r1, [r6, r2]
	cmp r5, #0xc
	blo _02038A72
_02038A92:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xc
	blo _02038A68
	ldr r0, [sp, #0x4]
	bl SetLCRNGSeed
	ldr r0, [sp, #0x0]
	add r1, sp, #0x8
	ldrb r0, [r1, r0]
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02038AAC: .word UNK_020F2BE8

	thumb_func_start sub_02038AB0
sub_02038AB0: ; 0x02038AB0
	push {r4, lr}
	bl sub_0204652C
	add r4, r0, #0x0
	bl ov06_0224D79C
	cmp r0, #0x1
	bne _02038ACA
	add r0, r4, #0x0
	bl ov06_0224D76C
	mov r0, #0x1
	pop {r4, pc}
_02038ACA:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02038AD0
sub_02038AD0: ; 0x02038AD0
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02046528
	add r2, r0, #0x0
	ldr r1, [r2, #0xc]
	ldr r2, [r2, #0x8]
	mov r0, #0x4
	bl ov06_0224D70C
	add r2, r0, #0x0
	ldr r1, _02038AF0 ; =sub_02038AB0
	add r0, r4, #0x0
	bl sub_0204640C
	pop {r4, pc}
	.balign 4
_02038AF0: .word sub_02038AB0

	thumb_func_start sub_02038AF4
sub_02038AF4: ; 0x02038AF4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x8
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	str r6, [r4, #0x4]
	ldr r0, [r5, #0xc]
	ldr r1, _02038B18 ; =UNK_020F2DA4
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl sub_020373D4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02038B18: .word UNK_020F2DA4
