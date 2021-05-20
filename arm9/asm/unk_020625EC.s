    .include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020F7BC8
UNK_020F7BC8: ; 0x020F7BC8
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x55, 0x03

	.global UNK_020F7BD0
UNK_020F7BD0: ; 0x020F7BD0
	.word UNK_020F7C4C, UNK_020F7C0C, UNK_020F7BF4

	.global UNK_020F7BDC
UNK_020F7BDC: ; 0x020F7BDC
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F7BF4
UNK_020F7BF4: ; 0x020F7BF4
	.byte 0x0F, 0x27, 0x00, 0x00, 0x04, 0x00, 0x15, 0x00, 0x64, 0x00, 0x00, 0x00, 0x04, 0x00, 0x14, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x05, 0x00, 0x11, 0x00

	.global UNK_020F7C0C
UNK_020F7C0C: ; 0x020F7C0C
	.byte 0x3F, 0x42, 0x0F, 0x00, 0x06, 0x00, 0x13, 0x00, 0x3F, 0x42, 0x0F, 0x00, 0x06, 0x00, 0x13, 0x00
	.byte 0x3F, 0x42, 0x0F, 0x00, 0x06, 0x00, 0x12, 0x00, 0x3F, 0x42, 0x0F, 0x00, 0x06, 0x00, 0x13, 0x00

	.global UNK_020F7C2C
UNK_020F7C2C: ; 0x020F7C2C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x07, 0x00, 0x02, 0x08, 0x01, 0x10, 0x2F, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F7C4C
UNK_020F7C4C: ; 0x020F7C4C
	.byte 0x0F, 0x27, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00, 0x0F, 0x27, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00
	.byte 0x0F, 0x27, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00, 0x0F, 0x27, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00
	.byte 0x0F, 0x27, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00

	.global UNK_020F7C7C
UNK_020F7C7C: ; 0x020F7C7C
	.byte 0x7E, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00
	.byte 0xD8, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x4A, 0x00, 0x78, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00
	.byte 0xD8, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_020625EC
FUN_020625EC: ; 0x020625EC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x3
	mov r1, #0x50
	lsl r2, r0, #0xd
	ldr r6, [r5, #0xc]
	bl FUN_0201681C
	mov r1, #0x2d
	mov r0, #0x50
	lsl r1, r1, #0x4
	bl AllocFromHeap
	mov r2, #0x2d
	mov r1, #0x0
	lsl r2, r2, #0x4
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x50
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x0]
	mov r1, #0x3
	bl _s32_div_f
	strb r1, [r4, #0x16]
	ldr r0, [sp, #0x0]
	mov r1, #0x3
	bl _s32_div_f
	strb r0, [r4, #0x17]
	ldrb r0, [r4, #0x16]
	bl FUN_0202B870
	strb r0, [r4, #0x18]
	ldrb r0, [r4, #0x16]
	bl FUN_0202B87C
	strb r0, [r4, #0x19]
	add r0, r4, #0x0
	add r0, #0xcc
	str r5, [r0, #0x0]
	add r0, r4, #0x0
	ldr r1, [r5, #0x8]
	add r0, #0xd0
	str r1, [r0, #0x0]
	add r0, r6, #0x0
	bl FUN_0202B8E4
	mov r1, #0x2a
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	add r0, r6, #0x0
	bl Sav2_PlayerData_GetOptionsAddr
	bl Options_GetTextFrameDelay
	strh r0, [r4, #0x1a]
	add r0, r6, #0x0
	bl Sav2_PlayerData_GetOptionsAddr
	bl Options_GetFrame
	strh r0, [r4, #0x1c]
	str r4, [r7, #0x8]
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02062678
FUN_02062678: ; 0x02062678
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r4, [r0, #0x8]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldrb r0, [r4, #0x18]
	cmp r0, #0x0
	ble _020626FE
	ldr r0, [sp, #0x4]
	str r0, [sp, #0x0]
_0206268C:
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r2, [r4, r0]
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	add r1, r2, r0
	ldr r0, [r2, r0]
	add r7, r6, #0x0
	cmp r0, #0x0
	ble _020626EC
	add r5, r6, #0x0
_020626A2:
	add r0, r1, #0x4
	add r1, r0, r5
	ldrb r0, [r1, #0x6]
	mov r12, r0
	cmp r0, #0xff
	beq _020626D6
	ldrh r0, [r1, #0x4]
	cmp r0, #0x0
	bne _020626D6
	ldrb r2, [r4, #0x17]
	ldrb r3, [r4, #0x19]
	mov r1, #0xd
	mul r1, r2
	add r2, r3, r1
	ldr r1, [sp, #0x4]
	mov r0, #0x2a
	add r1, r1, r2
	mov r2, r12
	lsl r0, r0, #0x4
	sub r2, r2, r6
	lsl r2, r2, #0x18
	ldr r0, [r4, r0]
	lsr r2, r2, #0x18
	bl FUN_0202B8F0
	add r6, r6, #0x1
_020626D6:
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, r0
	ldr r0, [r2, r0]
	add r7, r7, #0x1
	add r5, #0x8
	cmp r7, r0
	blt _020626A2
_020626EC:
	ldr r0, [sp, #0x0]
	ldrb r1, [r4, #0x18]
	add r0, #0x3c
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	cmp r0, r1
	blt _0206268C
_020626FE:
	add r0, r4, #0x0
	ldr r5, [r4, #0x0]
	bl FreeToHeap
	mov r2, #0x2d
	add r0, r4, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl FUN_020168D0
	mov r0, #0xc
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02062720
FUN_02062720: ; 0x02062720
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02062A70
	add r0, r4, #0x0
	bl FUN_02062C80
	add r0, r4, #0x0
	bl FUN_02062DB0
	add r0, r4, #0x0
	bl FUN_02062F3C
	mov r0, #0x2
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02062740
FUN_02062740: ; 0x02062740
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02062FFC
	add r0, r4, #0x0
	bl FUN_02062EC4
	add r0, r4, #0x0
	bl FUN_02062D38
	add r0, r4, #0x0
	bl FUN_02062C4C
	mov r0, #0xb
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02062760
FUN_02062760: ; 0x02062760
	push {r3, lr}
	ldrh r1, [r0, #0x22]
	ldrh r2, [r0, #0x24]
	bl FUN_02063028
	mov r0, #0x3
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02062770
FUN_02062770: ; 0x02062770
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0xc0
	ldr r0, [r0, #0x0]
	bl ListMenu_ProcessInput
	ldr r1, _020627C8 ; =gMain
	ldr r3, [r1, #0x48]
	mov r1, #0x2
	tst r1, r3
	beq _02062790
	add r0, r4, #0x0
	bl FUN_02063178
	mov r0, #0xa
	pop {r4, pc}
_02062790:
	mov r2, #0x1
	add r1, r3, #0x0
	tst r1, r2
	bne _0206279C
	mov r0, #0x3
	pop {r4, pc}
_0206279C:
	sub r1, r2, #0x3
	cmp r0, r1
	beq _020627AE
	sub r1, r2, #0x2
	cmp r0, r1
	beq _020627AE
	ldr r1, _020627CC ; =0x0000FFFF
	cmp r0, r1
	bne _020627B8
_020627AE:
	add r0, r4, #0x0
	bl FUN_02063178
	mov r0, #0xa
	pop {r4, pc}
_020627B8:
	strb r0, [r4, #0x1f]
	mov r0, #0x0
	strh r0, [r4, #0x28]
	add r0, r4, #0x0
	bl FUN_02063178
	mov r0, #0x4
	pop {r4, pc}
	.balign 4
_020627C8: .word gMain
_020627CC: .word 0x0000FFFF

	thumb_func_start FUN_020627D0
FUN_020627D0: ; 0x020627D0
	push {r3, lr}
	ldrh r1, [r0, #0x28]
	bl FUN_02063430
	mov r0, #0x5
	pop {r3, pc}

	thumb_func_start FUN_020627DC
FUN_020627DC: ; 0x020627DC
	push {r3, lr}
	ldr r1, _02062804 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	beq _020627F0
	bl FUN_020634DC
	mov r0, #0x2
	pop {r3, pc}
_020627F0:
	mov r1, #0x4
	tst r1, r2
	beq _020627FE
	bl FUN_02063238
	mov r0, #0x6
	pop {r3, pc}
_020627FE:
	mov r0, #0x5
	pop {r3, pc}
	nop
_02062804: .word gMain

	thumb_func_start FUN_02062808
FUN_02062808: ; 0x02062808
	push {r4, lr}
	ldr r1, _020628B8 ; =gMain
	mov r2, #0x2
	ldr r1, [r1, #0x48]
	add r4, r0, #0x0
	tst r2, r1
	beq _0206281E
	bl FUN_02063264
	mov r0, #0x5
	pop {r4, pc}
_0206281E:
	mov r0, #0x1
	tst r0, r1
	beq _0206285C
	mov r0, #0x0
	str r0, [r4, #0xc]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldrb r2, [r4, #0x1f]
	mov r1, #0x3c
	ldr r3, [r4, r0]
	mul r1, r2
	add r1, r3, r1
	add r3, r1, #0x4
	ldrh r1, [r4, #0x28]
	add r2, r4, r1
	add r1, r0, #0x0
	add r1, #0x8
	ldrb r1, [r2, r1]
	lsl r1, r1, #0x3
	add r2, r3, r1
	add r1, r0, #0x4
	str r2, [r4, r1]
	add r0, r0, #0x4
	ldr r0, [r4, r0]
	ldrb r0, [r0, #0x6]
	cmp r0, #0xff
	bne _02062858
	mov r0, #0x8
	pop {r4, pc}
_02062858:
	mov r0, #0x7
	pop {r4, pc}
_0206285C:
	mov r0, #0x40
	tst r0, r1
	beq _02062882
	ldrh r0, [r4, #0x28]
	cmp r0, #0x0
	beq _02062882
	sub r0, r0, #0x1
	strh r0, [r4, #0x28]
	ldrh r2, [r4, #0x28]
	mov r0, #0xa6
	lsl r0, r0, #0x2
	lsl r2, r2, #0x4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, r0]
	mov r1, #0x7e
	asr r2, r2, #0x10
	bl FUN_0200C714
_02062882:
	ldr r0, _020628B8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x80
	tst r0, r1
	beq _020628B4
	add r0, r4, #0x0
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	ldrh r1, [r4, #0x28]
	sub r0, r0, #0x1
	cmp r1, r0
	bge _020628B4
	add r0, r1, #0x1
	strh r0, [r4, #0x28]
	ldrh r2, [r4, #0x28]
	mov r0, #0xa6
	lsl r0, r0, #0x2
	lsl r2, r2, #0x4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, r0]
	mov r1, #0x7e
	asr r2, r2, #0x10
	bl FUN_0200C714
_020628B4:
	mov r0, #0x6
	pop {r4, pc}
	.balign 4
_020628B8: .word gMain

	thumb_func_start FUN_020628BC
FUN_020628BC: ; 0x020628BC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, _020628E0 ; =UNK_020F7BC8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	ldr r2, _020628E4 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	add r4, #0xc8
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_020628E0: .word UNK_020F7BC8
_020628E4: .word 0x000003D9

	thumb_func_start FUN_020628E8
FUN_020628E8: ; 0x020628E8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x3
	bgt _0206290C
	cmp r1, #0x0
	blt _020629CE
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02062904: ; jump table (using 16-bit offset)
	.short _02062912 - _02062904 - 2; case 0
	.short _0206294E - _02062904 - 2; case 1
	.short _02062966 - _02062904 - 2; case 2
	.short _0206298C - _02062904 - 2; case 3
_0206290C:
	cmp r1, #0xff
	beq _020629B2
	b _020629CE
_02062912:
	add r0, #0xe4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldrh r0, [r4, #0x1a]
	add r2, r4, #0x0
	add r2, #0x98
	str r0, [sp, #0x4]
	ldr r0, _020629D4 ; =0x0001020F
	mov r1, #0x1
	str r0, [sp, #0x8]
	str r3, [sp, #0xc]
	add r0, r4, #0x0
	ldr r2, [r2, #0x0]
	add r0, #0xe4
	bl AddTextPrinterParameterized2
	strb r0, [r4, #0x1e]
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x2
	bl FUN_0200C66C
	ldr r0, [r4, #0xc]
	add r0, r0, #0x1
	str r0, [r4, #0xc]
	b _020629CE
_0206294E:
	ldrb r0, [r4, #0x1e]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _020629CE
	add r0, r4, #0x0
	bl FUN_020628BC
	ldr r0, [r4, #0xc]
	add r0, r0, #0x1
	str r0, [r4, #0xc]
	b _020629CE
_02062966:
	add r0, #0xc8
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _0206297E
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	beq _02062986
	b _020629CE
_0206297E:
	ldr r0, [r4, #0xc]
	add r0, r0, #0x1
	str r0, [r4, #0xc]
	b _020629CE
_02062986:
	mov r0, #0xff
	str r0, [r4, #0xc]
	b _020629CE
_0206298C:
	mov r1, #0xb1
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x0
	strh r2, [r1, #0x4]
	mov r1, #0x1
	bl FUN_020632A4
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200C66C
	mov r0, #0x0
	str r0, [r4, #0xc]
	add sp, #0x10
	mov r0, #0x6
	pop {r4, pc}
_020629B2:
	add r0, r4, #0x0
	bl FUN_02063208
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200C66C
	mov r0, #0x0
	str r0, [r4, #0xc]
	add sp, #0x10
	mov r0, #0x6
	pop {r4, pc}
_020629CE:
	mov r0, #0x7
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_020629D4: .word 0x0001020F

	thumb_func_start FUN_020629D8
FUN_020629D8: ; 0x020629D8
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	beq _020629EE
	cmp r1, #0x1
	beq _02062A2A
	cmp r1, #0x2
	beq _02062A3C
	b _02062A60
_020629EE:
	add r0, #0xe4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldrh r0, [r4, #0x1a]
	add r2, r4, #0x0
	add r2, #0x9c
	str r0, [sp, #0x4]
	ldr r0, _02062A68 ; =0x0001020F
	mov r1, #0x1
	str r0, [sp, #0x8]
	str r3, [sp, #0xc]
	add r0, r4, #0x0
	ldr r2, [r2, #0x0]
	add r0, #0xe4
	bl AddTextPrinterParameterized2
	strb r0, [r4, #0x1e]
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x2
	bl FUN_0200C66C
	ldr r0, [r4, #0xc]
	add r0, r0, #0x1
	str r0, [r4, #0xc]
	b _02062A60
_02062A2A:
	ldrb r0, [r4, #0x1e]
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02062A60
	ldr r0, [r4, #0xc]
	add r0, r0, #0x1
	str r0, [r4, #0xc]
	b _02062A60
_02062A3C:
	ldr r1, _02062A6C ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	beq _02062A60
	bl FUN_02063208
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200C66C
	mov r0, #0x0
	str r0, [r4, #0xc]
	add sp, #0x10
	mov r0, #0x6
	pop {r4, pc}
_02062A60:
	mov r0, #0x8
	add sp, #0x10
	pop {r4, pc}
	nop
_02062A68: .word 0x0001020F
_02062A6C: .word gMain

	thumb_func_start FUN_02062A70
FUN_02062A70: ; 0x02062A70
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	ldrb r2, [r4, #0x18]
	add r5, r1, #0x0
	mov r1, #0x3c
	ldr r0, [r4, #0x0]
	mul r1, r2
	bl AllocFromHeap
	mov r1, #0xb
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldrb r3, [r4, #0x18]
	mov r2, #0x3c
	mov r1, #0x0
	mul r2, r3
	bl MI_CpuFill8
	ldrb r1, [r4, #0x16]
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_0202BD6C
	mov r1, #0xa9
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldrb r0, [r4, #0x18]
	cmp r0, #0x0
	bgt _02062AB4
	b _02062C48
_02062AB4:
	ldr r0, [sp, #0x10]
	str r4, [sp, #0x8]
	str r0, [sp, #0x4]
	add r5, r0, #0x0
_02062ABC:
	ldrb r2, [r4, #0x17]
	ldrb r3, [r4, #0x19]
	mov r1, #0xd
	mul r1, r2
	mov r0, #0x2a
	add r2, r3, r1
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x4
	add r1, r1, r2
	ldr r0, [r4, r0]
	ldr r2, [r4, #0x0]
	bl FUN_0202BDF0
	mov r1, #0xaa
	mov r3, #0x0
	ldr r2, [sp, #0x8]
	lsl r1, r1, #0x2
	str r0, [r2, r1]
	add r0, r2, #0x0
	ldr r0, [r0, r1]
	mov r12, r3
	str r0, [sp, #0xc]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02062B22
	sub r0, r1, #0x4
	ldr r0, [r4, r0]
	add r3, r1, #0x0
	add r2, r0, #0x4
	ldr r0, [sp, #0x4]
	add r3, #0x18
	add r2, r2, r0
	add r0, r1, #0x0
	add r0, #0x18
	ldr r0, [r4, r0]
	add r0, r0, r5
	str r2, [r0, #0x4]
	add r0, r1, #0x0
	add r0, #0x18
	ldr r0, [r4, r0]
	mov r2, #0x1
	add r0, r0, r5
	strh r2, [r0, #0x8]
	ldr r3, [r4, r3]
	mov r0, #0xff
	add r3, r3, r5
	add r1, #0x18
	strb r0, [r3, #0xa]
	ldr r0, [r4, r1]
	str r2, [r0, r5]
	b _02062C2C
_02062B22:
	add r2, r3, #0x0
	cmp r0, #0x0
	ble _02062BE4
	ldr r0, [sp, #0xc]
	str r0, [sp, #0x0]
	add r7, r0, #0x4
_02062B2E:
	mov r0, r12
	cmp r0, #0x0
	bne _02062BA8
	mov r0, #0xa9
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x4]
	add r1, r1, r0
	ldr r6, [r1, #0x8]
	ldr r1, [sp, #0x0]
	ldr r1, [r1, #0x8]
	cmp r6, r1
	blo _02062BA8
	add r6, r0, #0x4
	ldr r0, [sp, #0x4]
	lsl r1, r3, #0x3
	add r0, r6, r0
	mov r6, #0xb
	lsl r6, r6, #0x6
	ldr r6, [r4, r6]
	add r3, r3, #0x1
	add r6, r5, r6
	add r6, r1, r6
	str r0, [r6, #0x4]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	add r0, r5, r0
	add r6, r1, r0
	mov r0, #0x1
	strh r0, [r6, #0x8]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	lsl r6, r3, #0x3
	add r0, r5, r0
	add r1, r1, r0
	mov r0, #0xff
	strb r0, [r1, #0xa]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	add r0, r5, r0
	add r0, r6, r0
	str r7, [r0, #0x4]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	add r0, r5, r0
	add r1, r6, r0
	mov r0, #0x1
	strh r0, [r1, #0x8]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	add r0, r5, r0
	add r0, r6, r0
	strb r2, [r0, #0xa]
	mov r0, #0x1
	mov r12, r0
	b _02062BD0
_02062BA8:
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	lsl r6, r3, #0x3
	add r0, r5, r0
	add r0, r6, r0
	str r7, [r0, #0x4]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	add r0, r5, r0
	add r1, r6, r0
	mov r0, #0x1
	strh r0, [r1, #0x8]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	add r0, r5, r0
	add r0, r6, r0
	strb r2, [r0, #0xa]
_02062BD0:
	ldr r0, [sp, #0x0]
	add r2, r2, #0x1
	add r0, #0xc
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r3, r3, #0x1
	ldr r0, [r0, #0x0]
	add r7, #0xc
	cmp r2, r0
	blt _02062B2E
_02062BE4:
	mov r0, r12
	cmp r0, #0x0
	bne _02062C1E
	mov r0, #0xa9
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	lsl r2, r3, #0x3
	add r3, r1, #0x4
	ldr r1, [sp, #0x4]
	add r1, r3, r1
	add r3, r0, #0x0
	add r3, #0x1c
	ldr r3, [r4, r3]
	add r3, r3, r5
	add r3, r2, r3
	str r1, [r3, #0x4]
	add r3, r0, #0x0
	add r3, #0x1c
	ldr r3, [r4, r3]
	mov r1, #0x1
	add r3, r3, r5
	add r3, r2, r3
	strh r1, [r3, #0x8]
	add r0, #0x1c
	ldr r0, [r4, r0]
	mov r1, #0xff
	add r0, r0, r5
	add r0, r2, r0
	strb r1, [r0, #0xa]
_02062C1E:
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x0]
	add r1, r0, #0x1
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r4, r0]
	str r1, [r0, r5]
_02062C2C:
	ldr r0, [sp, #0x8]
	ldrb r1, [r4, #0x18]
	add r0, r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r5, #0x3c
	add r0, #0xc
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x10]
	add r0, r0, #0x1
	str r0, [sp, #0x10]
	cmp r0, r1
	bge _02062C48
	b _02062ABC
_02062C48:
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_02062C4C
FUN_02062C4C: ; 0x02062C4C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldrb r0, [r6, #0x18]
	mov r4, #0x0
	add r0, r0, #0x1
	cmp r0, #0x0
	ble _02062C72
	mov r7, #0xa9
	add r5, r6, #0x0
	lsl r7, r7, #0x2
_02062C60:
	ldr r0, [r5, r7]
	bl FUN_0202BE6C
	ldrb r0, [r6, #0x18]
	add r4, r4, #0x1
	add r5, r5, #0x4
	add r0, r0, #0x1
	cmp r4, r0
	blt _02062C60
_02062C72:
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldr r0, [r6, r0]
	bl FreeToHeap
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02062C80
FUN_02062C80: ; 0x02062C80
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, _02062D34 ; =0x000001E1
	ldr r3, [r5, #0x0]
	mov r0, #0x0
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	str r0, [r5, #0x2c]
	ldr r2, [r5, #0x0]
	mov r0, #0x2
	mov r1, #0x4c
	bl ScrStrBufs_new_custom
	str r0, [r5, #0x30]
	ldr r1, [r5, #0x0]
	mov r0, #0x4c
	bl String_ctor
	str r0, [r5, #0x34]
	ldr r0, [r5, #0x2c]
	mov r1, #0xd
	bl NewString_ReadMsgData
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x2c]
	mov r1, #0x16
	bl NewString_ReadMsgData
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x2c]
	mov r1, #0x24
	bl NewString_ReadMsgData
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x2c]
	mov r1, #0xe
	bl NewString_ReadMsgData
	str r0, [r5, #0x44]
	ldrb r0, [r5, #0x18]
	mov r4, #0x0
	cmp r0, #0x0
	ble _02062CFE
	add r6, r5, #0x0
_02062CDA:
	ldrb r1, [r5, #0x19]
	ldr r0, [r5, #0x2c]
	add r1, r1, r4
	bl NewString_ReadMsgData
	str r0, [r6, #0x64]
	ldrb r1, [r5, #0x19]
	ldr r0, [r5, #0x2c]
	add r1, #0x17
	add r1, r1, r4
	bl NewString_ReadMsgData
	str r0, [r6, #0x7c]
	ldrb r0, [r5, #0x18]
	add r4, r4, #0x1
	add r6, r6, #0x4
	cmp r4, r0
	blt _02062CDA
_02062CFE:
	mov r4, #0x0
	add r6, r5, #0x0
_02062D02:
	add r1, r4, #0x0
	ldr r0, [r5, #0x2c]
	add r1, #0xf
	bl NewString_ReadMsgData
	str r0, [r6, #0x48]
	add r4, r4, #0x1
	add r6, r6, #0x4
	cmp r4, #0x7
	blt _02062D02
	mov r4, #0x0
	add r6, r5, #0x0
_02062D1A:
	add r1, r4, #0x0
	ldr r0, [r5, #0x2c]
	add r1, #0x25
	bl NewString_ReadMsgData
	add r1, r6, #0x0
	add r1, #0x94
	add r4, r4, #0x1
	add r6, r6, #0x4
	str r0, [r1, #0x0]
	cmp r4, #0x3
	blt _02062D1A
	pop {r4-r6, pc}
	.balign 4
_02062D34: .word 0x000001E1

	thumb_func_start FUN_02062D38
FUN_02062D38: ; 0x02062D38
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
_02062D40:
	add r0, r5, #0x0
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl String_dtor
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x3
	blt _02062D40
	mov r5, #0x0
	add r4, r6, #0x0
_02062D56:
	ldr r0, [r4, #0x48]
	bl String_dtor
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, #0x7
	blt _02062D56
	ldrb r0, [r6, #0x18]
	mov r5, #0x0
	cmp r0, #0x0
	ble _02062D84
	add r4, r6, #0x0
_02062D6E:
	ldr r0, [r4, #0x64]
	bl String_dtor
	ldr r0, [r4, #0x7c]
	bl String_dtor
	ldrb r0, [r6, #0x18]
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, r0
	blt _02062D6E
_02062D84:
	ldr r0, [r6, #0x44]
	bl String_dtor
	ldr r0, [r6, #0x40]
	bl String_dtor
	ldr r0, [r6, #0x3c]
	bl String_dtor
	ldr r0, [r6, #0x38]
	bl String_dtor
	ldr r0, [r6, #0x34]
	bl String_dtor
	ldr r0, [r6, #0x30]
	bl ScrStrBufs_delete
	ldr r0, [r6, #0x2c]
	bl DestroyMsgData
	pop {r4-r6, pc}

	thumb_func_start FUN_02062DB0
FUN_02062DB0: ; 0x02062DB0
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	mov r1, #0xad
	ldr r3, [r4, #0x0]
	mov r0, #0x1
	lsl r1, r1, #0x6
	mov r2, #0x0
	bl FUN_02017F18
	mov r2, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_02018540
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_0201AC68
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0201797C
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02018884
	strh r0, [r4, #0x10]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02018884
	strh r0, [r4, #0x12]
	mov r0, #0x0
	mov r1, #0x2
	bl FUN_020178BC
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020178BC
	ldrh r0, [r4, #0x1c]
	ldr r2, _02062EB8 ; =0x000003E2
	mov r1, #0x3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	mov r3, #0xa
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	bl FUN_0200CD68
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _02062EBC ; =0x000003D9
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _02062EBC ; =0x000003D9
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0x1a
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	lsl r1, r1, #0x4
	bl FUN_02002ED0
	mov r1, #0x6
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	lsl r1, r1, #0x6
	bl FUN_02002EEC
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02062EC0 ; =0x0000036D
	add r1, r4, #0x0
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	add r1, #0xe4
	mov r2, #0x3
	mov r3, #0x2
	bl FUN_02019064
	add r4, #0xe4
	add r0, r4, #0x0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	add sp, #0x14
	pop {r3-r4, pc}
	.balign 4
_02062EB8: .word 0x000003E2
_02062EBC: .word 0x000003D9
_02062EC0: .word 0x0000036D

	thumb_func_start FUN_02062EC4
FUN_02062EC4: ; 0x02062EC4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, #0xe4
	mov r1, #0x1
	bl FUN_0200D0E0
	add r0, r4, #0x0
	add r0, #0xe4
	bl FUN_02019570
	add r0, r4, #0x0
	add r0, #0xe4
	bl FUN_02019178
	mov r1, #0xad
	ldr r3, [r4, #0x0]
	mov r0, #0x1
	lsl r1, r1, #0x6
	mov r2, #0x0
	bl FUN_02017F18
	mov r2, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x11
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	add r3, r2, #0x0
	bl FUN_02018540
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_0201AC68
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201797C
	ldrh r1, [r4, #0x10]
	mov r0, #0x0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	ldrh r1, [r4, #0x12]
	mov r0, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_020178BC
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02062F3C
FUN_02062F3C: ; 0x02062F3C
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r4, _02062FF0 ; =UNK_020F7BDC
	add r3, sp, #0xc
	add r6, r0, #0x0
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r1, r2, #0x0
	ldr r3, [r6, #0x0]
	add r0, r6, r0
	mov r2, #0x2
	bl MOD05_021D959C
	mov r0, #0x3
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, _02062FF4 ; =0x000034D8
	mov r2, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r6, r0
	mov r1, #0x82
	add r3, r2, #0x0
	bl MOD05_021D967C
	ldr r0, _02062FF4 ; =0x000034D8
	mov r1, #0x82
	str r0, [sp, #0x0]
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r6, r0
	mov r2, #0x2
	mov r3, #0x0
	bl MOD05_021D96F4
	ldr r0, _02062FF4 ; =0x000034D8
	mov r1, #0x82
	str r0, [sp, #0x0]
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r6, r0
	mov r2, #0x3
	mov r3, #0x0
	bl MOD05_021D9708
	mov r2, #0x1
	ldr r0, _02062FF4 ; =0x000034D8
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r6, r0
	mov r1, #0x82
	mov r3, #0x0
	bl MOD05_021D971C
	ldr r4, _02062FF8 ; =UNK_020F7C7C
	mov r7, #0x0
	add r5, r6, #0x0
_02062FC4:
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r6, r0
	add r1, r4, #0x0
	bl MOD05_021D9820
	mov r1, #0xa6
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	add r7, r7, #0x1
	add r4, #0x34
	add r5, r5, #0x4
	cmp r7, #0x2
	blt _02062FC4
	add r0, r1, #0x4
	ldr r0, [r6, r0]
	mov r1, #0x0
	bl FUN_0200C644
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_02062FF0: .word UNK_020F7BDC
_02062FF4: .word 0x000034D8
_02062FF8: .word UNK_020F7C7C

	thumb_func_start FUN_02062FFC
FUN_02062FFC: ; 0x02062FFC
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r6, #0xa6
	mov r4, #0x0
	add r5, r7, #0x0
	lsl r6, r6, #0x2
_02063008:
	ldr r0, [r5, r6]
	cmp r0, #0x0
	beq _02063012
	bl FUN_0200C3DC
_02063012:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x2
	blt _02063008
	mov r0, #0x4d
	lsl r0, r0, #0x2
	add r0, r7, r0
	bl MOD05_021D99F8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02063028
FUN_02063028: ; 0x02063028
	push {r4-r7, lr}
	sub sp, #0x1c
	str r1, [sp, #0x14]
	add r5, r0, #0x0
	str r2, [sp, #0x18]
	ldrb r0, [r5, #0x18]
	ldr r1, [r5, #0x0]
	add r7, r0, #0x1
	add r0, r7, #0x0
	bl ListMenu_ctor
	add r1, r5, #0x0
	add r1, #0xc4
	str r0, [r1, #0x0]
	mov r2, #0x1
	add r1, r5, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x18
	str r0, [sp, #0x4]
	lsl r0, r7, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	str r2, [sp, #0x10]
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	add r1, #0xd4
	mov r3, #0x4
	bl FUN_02019064
	add r0, r5, #0x0
	add r0, #0xd4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	ldrb r0, [r5, #0x18]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02063094
	add r4, r5, #0x0
_0206307C:
	add r0, r5, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x64]
	add r2, r6, #0x0
	bl ListMenu_AddItem
	ldrb r0, [r5, #0x18]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _0206307C
_02063094:
	add r0, r5, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	ldr r1, [r5, #0x38]
	ldr r2, _02063160 ; =0x0000FFFF
	bl ListMenu_AddItem
	add r1, r5, #0x0
	ldr r0, _02063164 ; =UNK_020F7C2C
	add r1, #0xa0
	mov r2, #0x20
	bl MI_CpuCopy8
	add r1, r5, #0x0
	add r0, r5, #0x0
	add r1, #0xd4
	add r0, #0xac
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xc4
	ldr r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xa0
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xbc
	str r5, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xb0
	strh r7, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0xb7
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	bic r1, r0
	add r0, r5, #0x0
	add r0, #0xb7
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	ldr r1, _02063168 ; =FUN_020631C8
	add r0, #0xa4
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0xa8
	str r1, [r0, #0x0]
	ldr r3, [r5, #0x0]
	add r0, r5, #0x0
	lsl r3, r3, #0x18
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	add r0, #0xa0
	lsr r3, r3, #0x18
	bl ListMenuInit
	add r1, r5, #0x0
	add r1, #0xc0
	str r0, [r1, #0x0]
	add r0, r5, #0x0
	ldr r2, _0206316C ; =0x000003D9
	add r0, #0xd4
	mov r1, #0x0
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0x0
	ldr r2, _02063170 ; =0x000003E2
	add r0, #0xe4
	mov r1, #0x1
	mov r3, #0xa
	bl FUN_0200D0BC
	add r0, r5, #0x0
	add r0, #0xe4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r0, _02063174 ; =0x0001020F
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
	str r3, [sp, #0xc]
	add r0, r5, #0x0
	ldr r2, [r5, #0x3c]
	add r0, #0xe4
	mov r1, #0x1
	bl AddTextPrinterParameterized2
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r1, #0x1
	bl FUN_0200C644
	add r5, #0xd0
	ldr r0, [r5, #0x0]
	mov r1, #0x3
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4
_02063160: .word 0x0000FFFF
_02063164: .word UNK_020F7C2C
_02063168: .word FUN_020631C8
_0206316C: .word 0x000003D9
_02063170: .word 0x000003E2
_02063174: .word 0x0001020F

	thumb_func_start FUN_02063178
FUN_02063178: ; 0x02063178
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0xc0
	add r1, r4, #0x0
	add r2, r4, #0x0
	ldr r0, [r0, #0x0]
	add r1, #0x22
	add r2, #0x24
	bl FUN_02001300
	add r0, r4, #0x0
	add r0, #0xc4
	ldr r0, [r0, #0x0]
	bl ListMenu_dtor
	add r0, r4, #0x0
	add r0, #0xd4
	bl FUN_02019570
	add r0, r4, #0x0
	add r0, #0xd4
	mov r1, #0x0
	bl FUN_0200CCF8
	add r0, r4, #0x0
	add r0, #0xd4
	bl FUN_02019178
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C644
	add r4, #0xd0
	ldr r0, [r4, #0x0]
	mov r1, #0x3
	bl FUN_0201AC68
	pop {r4, pc}

	thumb_func_start FUN_020631C8
FUN_020631C8: ; 0x020631C8
	push {r3-r5, lr}
	mov r1, #0x13
	add r5, r0, #0x0
	bl FUN_02001470
	add r1, sp, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, #0x2
	add r2, sp, #0x0
	bl FUN_02001448
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02001470
	add r2, sp, #0x0
	ldrh r3, [r2, #0x0]
	ldrh r2, [r2, #0x2]
	mov r0, #0xa6
	lsl r0, r0, #0x2
	add r2, r3, r2
	lsl r2, r2, #0x4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, r0]
	mov r1, #0x7e
	asr r2, r2, #0x10
	bl FUN_0200C714
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02063208
FUN_02063208: ; 0x02063208
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, #0xe4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r0, _02063234 ; =0x0001020F
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	str r3, [sp, #0xc]
	add r4, #0x94
	ldr r2, [r4, #0x0]
	add r0, #0xe4
	mov r1, #0x1
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_02063234: .word 0x0001020F

	thumb_func_start FUN_02063238
FUN_02063238: ; 0x02063238
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02063208
	ldrh r2, [r4, #0x28]
	mov r0, #0xa6
	lsl r0, r0, #0x2
	lsl r2, r2, #0x4
	add r2, #0x10
	lsl r2, r2, #0x10
	ldr r0, [r4, r0]
	mov r1, #0x7e
	asr r2, r2, #0x10
	bl FUN_0200C714
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200C644
	pop {r4, pc}

	thumb_func_start FUN_02063264
FUN_02063264: ; 0x02063264
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r0, #0xe4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r0, _020632A0 ; =0x0001020F
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
	str r3, [sp, #0xc]
	ldrb r2, [r4, #0x1f]
	add r0, r4, #0x0
	add r0, #0xe4
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldr r2, [r2, #0x7c]
	mov r1, #0x1
	bl AddTextPrinterParameterized2
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C644
	add sp, #0x10
	pop {r4, pc}
	.balign 4
_020632A0: .word 0x0001020F

	thumb_func_start FUN_020632A4
FUN_020632A4: ; 0x020632A4
	push {r4-r7, lr}
	sub sp, #0x34
	str r1, [sp, #0x10]
	mov r1, #0xb
	add r4, r0, #0x0
	lsl r1, r1, #0x6
	ldr r1, [r4, r1]
	ldrb r0, [r4, #0x1f]
	str r1, [sp, #0x24]
	mov r1, #0x3c
	mul r1, r0
	str r1, [sp, #0x28]
	ldrb r1, [r4, #0x16]
	lsl r0, r0, #0x3
	lsl r2, r1, #0x2
	ldr r1, _02063428 ; =UNK_020F7BD0
	ldr r1, [r1, r2]
	add r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r4, #0x0
	add r0, #0xd4
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r0, #0x1
	str r0, [sp, #0x1c]
	mov r0, #0x0
	add r1, r0, #0x0
	str r1, [sp, #0x20]
	ldr r2, [sp, #0x24]
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x18]
	ldr r1, [r2, r1]
	cmp r1, #0x0
	ble _020633EA
	ldr r1, [sp, #0x28]
	add r7, r2, r1
	add r1, r0, #0x0
	str r1, [sp, #0x30]
	add r1, r4, #0x0
	str r1, [sp, #0x2c]
	add r1, #0xd4
	str r1, [sp, #0x2c]
_020632FA:
	ldrh r1, [r7, #0x8]
	cmp r1, #0x0
	beq _020633D6
	ldr r1, [r7, #0x4]
	ldr r5, [r1, #0x4]
	ldr r1, [sp, #0x14]
	ldr r1, [r1, #0x0]
	cmp r5, r1
	bls _0206330E
	add r5, r1, #0x0
_0206330E:
	cmp r5, r0
	bge _02063318
	ldr r0, [sp, #0x1c]
	add r0, r0, #0x1
	str r0, [sp, #0x1c]
_02063318:
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x30]
	ldr r2, [sp, #0x1c]
	mov r1, #0x0
	mov r3, #0x1
	bl BufferIntegerAsString
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r2, [r7, #0x4]
	ldr r0, [r4, #0x30]
	ldr r2, [r2, #0x8]
	mov r1, #0x1
	mov r3, #0x2
	bl BufferString
	ldr r0, [r4, #0x30]
	ldr r1, [r4, #0x34]
	ldr r2, [r4, #0x44]
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x30]
	mov r1, #0x0
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0206342C ; =0x0001020F
	mov r3, #0x8
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	ldr r2, [r4, #0x34]
	bl AddTextPrinterParameterized2
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x14]
	ldr r0, [r4, #0x30]
	ldrh r3, [r3, #0x4]
	mov r1, #0x0
	add r2, r5, #0x0
	bl BufferIntegerAsString
	ldr r2, [sp, #0x14]
	ldr r0, [r4, #0x30]
	ldrh r2, [r2, #0x6]
	ldr r1, [r4, #0x34]
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldr r2, [r2, #0xc]
	bl StringExpandPlaceholders
	mov r0, #0x0
	ldr r1, [r4, #0x34]
	add r2, r0, #0x0
	bl FUN_02002E14
	mov r12, r0
	ldr r0, [sp, #0x30]
	mov r3, #0xb8
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	ldr r0, _0206342C ; =0x0001020F
	mov r6, r12
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x2c]
	ldr r2, [r4, #0x34]
	mov r1, #0x0
	sub r3, r3, r6
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x20]
	add r2, r4, r0
	mov r0, #0xb2
	lsl r0, r0, #0x2
	strb r1, [r2, r0]
	ldr r1, [sp, #0x30]
	add r0, r5, #0x0
	add r1, #0x10
	str r1, [sp, #0x30]
	ldr r1, [sp, #0x18]
	add r1, r1, #0x1
	str r1, [sp, #0x18]
	cmp r1, #0x6
	bge _020633EA
_020633D6:
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x24]
	add r1, r1, #0x1
	str r1, [sp, #0x20]
	ldr r1, [sp, #0x28]
	add r7, #0x8
	ldr r2, [r2, r1]
	ldr r1, [sp, #0x20]
	cmp r1, r2
	blt _020632FA
_020633EA:
	add r0, r4, #0x0
	add r0, #0xd4
	bl CopyWindowToVram
	add r1, r4, #0x0
	ldr r0, [sp, #0x18]
	add r1, #0x21
	strb r0, [r1, #0x0]
	ldrh r1, [r4, #0x28]
	cmp r1, #0x0
	beq _0206340E
	add r0, r4, #0x0
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	blt _0206340E
	sub r0, r1, #0x1
	strh r0, [r4, #0x28]
_0206340E:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _0206341E
	add r0, r4, #0x0
	bl FUN_02063238
	add sp, #0x34
	pop {r4-r7, pc}
_0206341E:
	add r0, r4, #0x0
	bl FUN_02063264
	add sp, #0x34
	pop {r4-r7, pc}
	.balign 4
_02063428: .word UNK_020F7BD0
_0206342C: .word 0x0001020F

	thumb_func_start FUN_02063430
FUN_02063430: ; 0x02063430
	push {r3-r4, lr}
	sub sp, #0x14
	mov r2, #0x1
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x18
	str r0, [sp, #0x4]
	mov r0, #0xc
	str r0, [sp, #0x8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r4, #0x0
	str r2, [sp, #0x10]
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	add r1, #0xd4
	mov r3, #0x4
	bl FUN_02019064
	add r0, r4, #0x0
	ldr r2, _020634D0 ; =0x000003D9
	add r0, #0xd4
	mov r1, #0x1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_020632A4
	mov r0, #0xa7
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x1
	bl FUN_0200C644
	mov r0, #0xe
	str r0, [sp, #0x0]
	mov r3, #0x8
	add r1, r4, #0x0
	str r3, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _020634D4 ; =0x00000345
	add r1, #0xf4
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	add r0, #0xd0
	ldr r0, [r0, #0x0]
	mov r2, #0x3
	bl FUN_02019064
	add r0, r4, #0x0
	add r0, #0xf4
	mov r1, #0x0
	bl FillWindowPixelBuffer
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, _020634D8 ; =0x00010200
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r0, r4, #0x0
	ldr r2, [r4, #0x40]
	add r0, #0xf4
	add r3, r1, #0x0
	bl AddTextPrinterParameterized2
	add r4, #0xd0
	ldr r0, [r4, #0x0]
	mov r1, #0x3
	bl FUN_0201AC68
	add sp, #0x14
	pop {r3-r4, pc}
	nop
_020634D0: .word 0x000003D9
_020634D4: .word 0x00000345
_020634D8: .word 0x00010200

	thumb_func_start FUN_020634DC
FUN_020634DC: ; 0x020634DC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0xd4
	bl FUN_02019570
	add r0, r4, #0x0
	add r0, #0xd4
	mov r1, #0x0
	bl FUN_0200CCF8
	add r0, r4, #0x0
	add r0, #0xd4
	bl FUN_02019178
	add r0, r4, #0x0
	add r0, #0xf4
	bl FUN_02019570
	add r0, r4, #0x0
	add r0, #0xf4
	bl FUN_02019178
	mov r0, #0xa6
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C644
	mov r0, #0xa7
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	mov r1, #0x0
	bl FUN_0200C644
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02063524
FUN_02063524: ; 0x02063524
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r2, [r4, #0x0]
	ldr r1, [r4, #0x8]
	cmp r2, #0xc
	bls _02063540
	b _02063646
_02063540:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0206354C: ; jump table (using 16-bit offset)
	.short _02063566 - _0206354C - 2; case 0
	.short _02063572 - _0206354C - 2; case 1
	.short _0206357E - _0206354C - 2; case 2
	.short _02063594 - _0206354C - 2; case 3
	.short _020635AA - _0206354C - 2; case 4
	.short _020635C0 - _0206354C - 2; case 5
	.short _020635D6 - _0206354C - 2; case 6
	.short _020635EC - _0206354C - 2; case 7
	.short _02063602 - _0206354C - 2; case 8
	.short _02063618 - _0206354C - 2; case 9
	.short _0206362C - _0206354C - 2; case 10
	.short _02063636 - _0206354C - 2; case 11
	.short _0206363E - _0206354C - 2; case 12
_02063566:
	ldrh r2, [r4, #0x4]
	add r1, r5, #0x0
	bl FUN_020625EC
	str r0, [r4, #0x0]
	b _02063646
_02063572:
	add r0, r1, #0x0
	ldr r1, [r5, #0xc]
	bl FUN_02062720
	str r0, [r4, #0x0]
	b _02063646
_0206357E:
	add r0, r1, #0x0
	bl FUN_02062760
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_02063594:
	add r0, r1, #0x0
	bl FUN_02062770
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_020635AA:
	add r0, r1, #0x0
	bl FUN_020627D0
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_020635C0:
	add r0, r1, #0x0
	bl FUN_020627DC
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_020635D6:
	add r0, r1, #0x0
	bl FUN_02062808
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_020635EC:
	add r0, r1, #0x0
	bl FUN_020628E8
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_02063602:
	add r0, r1, #0x0
	bl FUN_020629D8
	str r0, [r4, #0x0]
	mov r0, #0x4d
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_0201FDEC
	b _02063646
_02063618:
	ldr r0, _0206364C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	bne _02063626
	mov r0, #0x0
	pop {r3-r5, pc}
_02063626:
	mov r0, #0xa
	str r0, [r4, #0x0]
	b _02063646
_0206362C:
	add r0, r1, #0x0
	bl FUN_02062740
	str r0, [r4, #0x0]
	b _02063646
_02063636:
	bl FUN_02062678
	str r0, [r4, #0x0]
	b _02063646
_0206363E:
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_02063646:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0206364C: .word gMain

	thumb_func_start FUN_02063650
FUN_02063650: ; 0x02063650
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeap
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	strh r5, [r2, #0x4]
	str r0, [r2, #0x8]
	ldr r0, [r4, #0x10]
	ldr r1, _02063678 ; =FUN_02063524
	bl FUN_0204640C
	pop {r3-r5, pc}
	nop
_02063678: .word FUN_02063524
