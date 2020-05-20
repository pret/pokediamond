    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021C48F8
	.extern gUnk021C4918
	.extern UNK_021C4928
	.extern UNK_021C492C
	.extern UNK_021C4D20
	.extern gUnknown21C48B8
	.extern UNK_020EDB10

	.text

	thumb_func_start FUN_02015EA0
FUN_02015EA0: ; 0x02015EA0
	push {r3, lr}
	ldr r3, _02015EC8 ; =0x027E0000
	ldr r1, _02015ECC ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	mov r0, #0x3
	bl MI_WaitDma
	ldr r0, _02015ED0 ; =gUnknown21C48B8
	ldr r0, [r0, #0x1c]
	bl FUN_0201B5CC
	ldr r0, _02015ED0 ; =gUnknown21C48B8
	ldr r1, [r0, #0x30]
	add r1, r1, #0x1
	str r1, [r0, #0x30]
	pop {r3, pc}
	nop
_02015EC8: .word 0x027E0000
_02015ECC: .word 0x00003FF8
_02015ED0: .word gUnknown21C48B8

	thumb_func_start FUN_02015ED4
FUN_02015ED4: ; 0x02015ED4
	ldr r3, _02015EE8 ; =0x027E0000
	ldr r1, _02015EEC ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	ldr r3, _02015EF0 ; =MI_WaitDma
	mov r0, #0x3
	bx r3
	nop
_02015EE8: .word 0x027E0000
_02015EEC: .word 0x00003FF8
_02015EF0: .word MI_WaitDma

	thumb_func_start FUN_02015EF4
FUN_02015EF4: ; 0x02015EF4
	push {r3, lr}
	mov r0, #0x1
	bl OS_DisableIrqMask
	ldr r1, _02015F0C ; =FUN_02015ED4
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	pop {r3, pc}
	.balign 4
_02015F0C: .word FUN_02015ED4

	thumb_func_start FUN_02015F10
FUN_02015F10: ; 0x02015F10
	ldr r2, _02015F18 ; =gUnknown21C48B8
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	bx lr
	.balign 4
_02015F18: .word gUnknown21C48B8

	thumb_func_start FUN_02015F1C
FUN_02015F1C: ; 0x02015F1C
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02015F80
	ldr r0, _02015F30 ; =gUnknown21C48B8
	mov r1, #0x0
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	pop {r3, pc}
	nop
_02015F30: .word gUnknown21C48B8

	thumb_func_start FUN_02015F34
FUN_02015F34: ; 0x02015F34
	push {r3, lr}
	cmp r0, #0x0
	bne _02015F4C
	mov r0, #0x0
	bl FUN_02015F80
	ldr r0, _02015F68 ; =gUnknown21C48B8
	mov r1, #0x0
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	mov r0, #0x1
	pop {r3, pc}
_02015F4C:
	ldr r2, _02015F68 ; =gUnknown21C48B8
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	bne _02015F62
	str r1, [r2, #0xc]
	str r0, [r2, #0x8]
	mov r0, #0x1
	bl FUN_02015F80
	mov r0, #0x1
	pop {r3, pc}
_02015F62:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02015F68: .word gUnknown21C48B8

	thumb_func_start FUN_02015F6C
FUN_02015F6C: ; 0x02015F6C
	push {r3, lr}
	ldr r0, _02015F7C ; =gUnknown21C48B8
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _02015F7A
	ldr r0, [r0, #0xc]
	blx r1
_02015F7A:
	pop {r3, pc}
	.balign 4
_02015F7C: .word gUnknown21C48B8

	thumb_func_start FUN_02015F80
FUN_02015F80: ; 0x02015F80
	push {r3, lr}
	ldr r2, _02015FC0 ; =0x04000208
	ldrh r1, [r2, #0x0]
	mov r1, #0x0
	strh r1, [r2, #0x0]
	cmp r0, #0x0
	bne _02015F9E
	ldr r0, [r2, #0x8]
	mov r0, #0x2
	bl OS_DisableIrqMask
	mov r0, #0x0
	bl GX_HBlankIntr
	b _02015FB4
_02015F9E:
	ldr r0, [r2, #0x8]
	ldr r1, _02015FC4 ; =FUN_02015F6C
	mov r0, #0x2
	bl OS_SetIrqFunction
	mov r0, #0x2
	bl OS_EnableIrqMask
	mov r0, #0x1
	bl GX_HBlankIntr
_02015FB4:
	ldr r1, _02015FC0 ; =0x04000208
	ldrh r0, [r1, #0x0]
	mov r0, #0x1
	strh r0, [r1, #0x0]
	pop {r3, pc}
	nop
_02015FC0: .word 0x04000208
_02015FC4: .word FUN_02015F6C

	thumb_func_start FUN_02015FC8
FUN_02015FC8: ; 0x02015FC8
	push {r3, lr}
	sub sp, #0x30
	add r0, sp, #0x10
	bl OS_GetLowEntropyData
	add r0, sp, #0x0
	add r1, sp, #0x10
	mov r2, #0x20
	bl MATH_CalcMD5
	mov r3, #0x0
	add r1, r3, #0x0
	add r2, sp, #0x0
_02015FE2:
	ldrb r0, [r2, #0x0]
	add r1, r1, #0x1
	add r2, r2, #0x1
	add r3, r3, r0
	cmp r1, #0x10
	blo _02015FE2
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	mov r0, #0x3
	tst r0, r3
	beq _02016002
	mov r0, #0x3
_02015FFA:
	add r3, r3, #0x1
	add r1, r3, #0x0
	tst r1, r0
	bne _02015FFA
_02016002:
	ldr r0, _02016010 ; =UNK_020EDB10
	mov r1, #0x4
	mov r2, #0x5c
	bl FUN_020166C8
	add sp, #0x30
	pop {r3, pc}
	.balign 4
_02016010: .word UNK_020EDB10

	thumb_func_start InitSystemForTheGame
InitSystemForTheGame: ; 0x02016014
	push {r3-r5, lr}
	bl OS_Init
	bl FX_Init
	ldr r2, _02016124 ; =0x04000304
	ldr r0, _02016128 ; =0xFFFFFDF1
	ldrh r1, [r2, #0x0]
	and r1, r0
	ldr r0, _0201612C ; =0x0000020E
	orr r0, r1
	strh r0, [r2, #0x0]
	bl GX_Init
	bl OS_InitTick
	bl FUN_02015FC8
	mov r0, #0xa0
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0xa0
	bl FUN_0201B580
	ldr r1, _02016130 ; =gUnknown21C48B8
	str r0, [r1, #0x18]
	mov r0, #0x10
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0x10
	bl FUN_0201B580
	ldr r1, _02016130 ; =gUnknown21C48B8
	str r0, [r1, #0x1c]
	mov r0, #0x20
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0x20
	bl FUN_0201B580
	ldr r1, _02016130 ; =gUnknown21C48B8
	str r0, [r1, #0x20]
	mov r0, #0x4
	bl FUN_0201B578
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r1, r0, #0x0
	mov r0, #0x4
	bl FUN_0201B580
	ldr r1, _02016130 ; =gUnknown21C48B8
	str r0, [r1, #0x24]
	bl GX_DispOff
	ldr r2, _02016134 ; =0x04001000
	ldr r0, _02016138 ; =0xFFFEFFFF
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r2, _02016124 ; =0x04000304
	ldrh r1, [r2, #0x0]
	lsr r0, r2, #0xb
	orr r0, r1
	strh r0, [r2, #0x0]
	ldr r1, _0201613C ; =FUN_02015EA0
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	mov r0, #0x1
	lsl r0, r0, #0x12
	bl OS_EnableIrqMask
	ldr r1, _02016140 ; =0x04000208
	ldrh r0, [r1, #0x0]
	mov r0, #0x1
	strh r0, [r1, #0x0]
	bl GX_VBlankIntr
	mov r0, #0x1
	bl FS_Init
	bl FUN_02022450
	mov r0, #0x0
	add r1, r0, #0x0
	bl FS_TryLoadTable
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	add r5, r0, #0x0
	bne _02016108
	bl ErrorHandling
_02016108:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FS_TryLoadTable
	ldr r0, _02016130 ; =gUnknown21C48B8
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x8]
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #0x2c]
	ldr r0, _02016144 ; =gUnk021C4918
	strb r1, [r0, #0x5]
	pop {r3-r5, pc}
	.balign 4
_02016124: .word 0x04000304
_02016128: .word 0xFFFFFDF1
_0201612C: .word 0x0000020E
_02016130: .word gUnknown21C48B8
_02016134: .word 0x04001000
_02016138: .word 0xFFFEFFFF
_0201613C: .word FUN_02015EA0
_02016140: .word 0x04000208
_02016144: .word gUnk021C4918

	thumb_func_start InitGraphicMemory
InitGraphicMemory: ; 0x02016148
	push {r3, lr}
	ldr r0, _02016198 ; =0x000001FF
	bl GX_SetBankForLCDC
	mov r1, #0x1a
	mov r2, #0x29
	mov r0, #0x0
	lsl r1, r1, #0x16
	lsl r2, r2, #0xe
	bl MIi_CpuClearFast
	bl GX_DisableBankForLCDC
	mov r1, #0x7
	mov r2, #0x1
	mov r0, #0xc0
	lsl r1, r1, #0x18
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	mov r2, #0x1
	ldr r1, _0201619C ; =0x07000400
	mov r0, #0xc0
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	mov r1, #0x5
	mov r2, #0x1
	mov r0, #0x0
	lsl r1, r1, #0x18
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	mov r2, #0x1
	ldr r1, _020161A0 ; =0x05000400
	mov r0, #0x0
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	pop {r3, pc}
	.balign 4
_02016198: .word 0x000001FF
_0201619C: .word 0x07000400
_020161A0: .word 0x05000400

	thumb_func_start FUN_020161A4
FUN_020161A4: ; 0x020161A4
	push {r4-r6, lr}
	sub sp, #0x48
	add r6, r0, #0x0
	add r4, r1, #0x0
	add r0, sp, #0x0
	bl FS_InitFile
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _020161F0
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x24]
	sub r5, r1, r0
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	beq _020161E8
	add r0, sp, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FS_ReadFile
	cmp r5, r0
	beq _020161E8
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02016A8C
	mov r4, #0x0
_020161E8:
	add r0, sp, #0x0
	bl FS_CloseFile
	b _020161F2
_020161F0:
	mov r4, #0x0
_020161F2:
	add r0, r4, #0x0
	add sp, #0x48
	pop {r4-r6, pc}

	thumb_func_start FUN_020161F8
FUN_020161F8: ; 0x020161F8
	push {r3-r5, lr}
	sub sp, #0x48
	add r5, r0, #0x0
	add r0, sp, #0x0
	add r4, r1, #0x0
	bl FS_InitFile
	add r0, sp, #0x0
	add r1, r5, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _0201622A
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x24]
	sub r2, r1, r0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02016224
	add r0, sp, #0x0
	bl FS_ReadFile
_02016224:
	add r0, sp, #0x0
	bl FS_CloseFile
_0201622A:
	add sp, #0x48
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02016230
FUN_02016230: ; 0x02016230
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	bl strlen
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	lsr r2, r3, #0x1f
	lsl r1, r3, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	beq _02016258
	lsr r0, r3, #0x2
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	b _0201625E
_02016258:
	lsl r0, r3, #0xe
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
_0201625E:
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	mov r12, r7
	cmp r0, #0x0
	ble _0201629A
	add r6, r7, #0x0
	add r4, r7, #0x0
_0201626C:
	ldr r2, [sp, #0x0]
	mov r1, #0x0
	add r0, r1, #0x0
	add r2, r2, r6
	add r3, r1, #0x0
_02016276:
	ldrsb r5, [r2, r4]
	cmp r5, #0x0
	beq _0201628A
	lsl r5, r3
	add r0, r0, #0x1
	orr r1, r5
	add r2, r2, #0x1
	add r3, #0x8
	cmp r0, #0x4
	blt _02016276
_0201628A:
	mov r0, r12
	eor r7, r1
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	add r6, r6, #0x4
	mov r12, r1
	cmp r1, r0
	blt _0201626C
_0201629A:
	add r0, r7, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_020162A0
FUN_020162A0: ; 0x020162A0
	ldr r3, _020162C4 ; =UNK_021C4928
	mov r2, #0x0
_020162A4:
	ldr r1, [r3, #0x4]
	cmp r0, r1
	bne _020162B4
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _020162B4
	add r0, r2, #0x0
	bx lr
_020162B4:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x80
	blt _020162A4
	mov r0, #0x0
	mvn r0, r0
	bx lr
	nop
_020162C4: .word UNK_021C4928

	thumb_func_start FUN_020162C8
FUN_020162C8: ; 0x020162C8
	push {r3-r4}
	ldr r3, _020162F4 ; =UNK_021C4928
	mov r4, #0x0
_020162CE:
	ldr r2, [r3, #0x0]
	cmp r2, #0x0
	bne _020162E4
	ldr r2, _020162F4 ; =UNK_021C4928
	lsl r3, r4, #0x3
	str r0, [r2, r3]
	ldr r0, _020162F8 ; =UNK_021C492C
	str r1, [r0, r3]
	add r0, r4, #0x0
	pop {r3-r4}
	bx lr
_020162E4:
	add r4, r4, #0x1
	add r3, #0x8
	cmp r4, #0x80
	blt _020162CE
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
	.balign 4
_020162F4: .word UNK_021C4928
_020162F8: .word UNK_021C492C

	thumb_func_start FUN_020162FC
FUN_020162FC: ; 0x020162FC
	push {r3-r7, lr}
	mov r6, #0x0
	ldr r5, _02016320 ; =UNK_021C4D20
	mov r4, #0x7f
	sub r7, r6, #0x1
_02016306:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02016314
	bl FUN_02016A18
	str r6, [r5, #0x0]
	str r6, [r5, #0x4]
_02016314:
	sub r4, r4, #0x1
	sub r5, #0x8
	cmp r4, r7
	bgt _02016306
	pop {r3-r7, pc}
	nop
_02016320: .word UNK_021C4D20

	thumb_func_start FUN_02016324
FUN_02016324: ; 0x02016324
	push {r3-r7, lr}
	sub sp, #0x68
	add r2, r0, #0x0
	mov r5, #0x0
	ldrsb r0, [r2, r5]
	add r4, r1, #0x0
	cmp r0, #0x21
	add r0, sp, #0x0
	bne _02016340
	add r1, r2, #0x1
	bl strcpy
	mov r5, #0x1
	b _02016346
_02016340:
	add r1, r2, #0x0
	bl strcpy
_02016346:
	add r0, sp, #0x0
	bl FUN_02016230
	add r7, r0, #0x0
	bl FUN_020162A0
	cmp r0, #0x0
	blt _02016362
	cmp r5, #0x0
	bne _02016362
	lsl r1, r0, #0x3
	ldr r0, _020163B8 ; =UNK_021C4928
	ldr r4, [r0, r1]
	b _020163B2
_02016362:
	add r0, sp, #0x20
	bl FS_InitFile
	add r0, sp, #0x20
	add r1, sp, #0x0
	bl FS_OpenFile
	cmp r0, #0x0
	beq _020163B0
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x44]
	sub r6, r1, r0
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	beq _0201639C
	add r0, sp, #0x20
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FS_ReadFile
	cmp r6, r0
	beq _0201639C
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r4, #0x0
_0201639C:
	add r0, sp, #0x20
	bl FS_CloseFile
	cmp r5, #0x0
	bne _020163B2
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_020162C8
	b _020163B2
_020163B0:
	mov r4, #0x0
_020163B2:
	add r0, r4, #0x0
	add sp, #0x68
	pop {r3-r7, pc}
	.balign 4
_020163B8: .word UNK_021C4928

	thumb_func_start FUN_020163BC
FUN_020163BC: ; 0x020163BC
	push {r3, lr}
	sub sp, #0x8
	ldr r0, _0201641C ; =gUnknown21C48B8
	mov r2, #0x0
	str r2, [r0, #0x34]
	str r2, [r0, #0x38]
	str r2, [r0, #0x3c]
	str r2, [r0, #0x40]
	str r2, [r0, #0x44]
	str r2, [r0, #0x48]
	str r2, [r0, #0x4c]
	str r2, [r0, #0x50]
	mov r1, #0x8
	str r1, [r0, #0x54]
	mov r1, #0xf
	str r1, [r0, #0x58]
	ldr r0, _02016420 ; =UNK_021C48F8
	strh r2, [r0, #0x1c]
	strh r2, [r0, #0x1e]
	strh r2, [r0, #0x20]
	strh r2, [r0, #0x22]
	ldr r0, _02016424 ; =gUnk021C4918
	strb r2, [r0, #0x4]
	bl TP_Init
	add r0, sp, #0x0
	bl TP_GetUserInfo
	cmp r0, #0x1
	add r0, sp, #0x0
	bne _02016402
	bl TP_SetCalibrateParam
	add sp, #0x8
	pop {r3, pc}
_02016402:
	ldr r1, _02016428 ; =0x000002AE
	strh r1, [r0, #0x0]
	ldr r1, _0201642C ; =0x0000058C
	strh r1, [r0, #0x2]
	ldr r1, _02016430 ; =0x00000E25
	strh r1, [r0, #0x4]
	ldr r1, _02016434 ; =0x00001208
	strh r1, [r0, #0x6]
	add r0, sp, #0x0
	bl TP_SetCalibrateParam
	add sp, #0x8
	pop {r3, pc}
	.balign 4
_0201641C: .word gUnknown21C48B8
_02016420: .word UNK_021C48F8
_02016424: .word gUnk021C4918
_02016428: .word 0x000002AE
_0201642C: .word 0x0000058C
_02016430: .word 0x00000E25
_02016434: .word 0x00001208

	thumb_func_start FUN_02016438
FUN_02016438: ; 0x02016438
	ldr r1, _02016440 ; =gUnk021C4918
	strb r0, [r1, #0x6]
	bx lr
	nop
_02016440: .word gUnk021C4918

	thumb_func_start FUN_02016444
FUN_02016444: ; 0x02016444
	ldr r1, _02016450 ; =gUnk021C4918
	ldrb r2, [r1, #0x7]
	orr r0, r2
	strb r0, [r1, #0x7]
	bx lr
	nop
_02016450: .word gUnk021C4918

	thumb_func_start FUN_02016454
FUN_02016454: ; 0x02016454
	ldr r1, _02016460 ; =gUnk021C4918
	mvn r0, r0
	ldrb r2, [r1, #0x7]
	and r0, r2
	strb r0, [r1, #0x7]
	bx lr
	.balign 4
_02016460: .word gUnk021C4918

	thumb_func_start FUN_02016464
FUN_02016464: ; 0x02016464
	push {r4, lr}
	sub sp, #0x10
	ldr r2, _02016550 ; =0x027FFFA8
	mov r0, #0x2
	ldrh r1, [r2, #0x0]
	lsl r0, r0, #0xe
	and r0, r1
	asr r0, r0, #0xf
	beq _0201648A
	ldr r0, _02016554 ; =gUnknown21C48B8
	mov r1, #0x0
	str r1, [r0, #0x48]
	str r1, [r0, #0x44]
	str r1, [r0, #0x4c]
	ldr r0, _02016558 ; =UNK_021C48F8
	add sp, #0x10
	strh r1, [r0, #0x20]
	strh r1, [r0, #0x22]
	pop {r4, pc}
_0201648A:
	ldr r0, _0201655C ; =0x04000130
	ldrh r1, [r0, #0x0]
	ldrh r0, [r2, #0x0]
	orr r1, r0
	ldr r0, _02016560 ; =0x00002FFF
	eor r1, r0
	and r0, r1
	ldr r1, _02016554 ; =gUnknown21C48B8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	ldr r2, [r1, #0x38]
	add r3, r0, #0x0
	eor r3, r2
	and r3, r0
	str r3, [r1, #0x3c]
	str r3, [r1, #0x40]
	cmp r0, #0x0
	beq _020164C2
	cmp r2, r0
	bne _020164C2
	ldr r2, [r1, #0x50]
	sub r2, r2, #0x1
	str r2, [r1, #0x50]
	bne _020164C8
	str r0, [r1, #0x40]
	ldr r2, [r1, #0x54]
	str r2, [r1, #0x50]
	b _020164C8
_020164C2:
	ldr r1, _02016554 ; =gUnknown21C48B8
	ldr r2, [r1, #0x58]
	str r2, [r1, #0x50]
_020164C8:
	ldr r1, _02016554 ; =gUnknown21C48B8
	str r0, [r1, #0x38]
	ldr r2, [r1, #0x3c]
	str r2, [r1, #0x48]
	str r0, [r1, #0x44]
	ldr r0, [r1, #0x40]
	str r0, [r1, #0x4c]
	bl FUN_02016568
	ldr r0, _02016564 ; =gUnk021C4918
	ldrb r0, [r0, #0x4]
	cmp r0, #0x0
	bne _020164F4
	add r4, sp, #0x8
_020164E4:
	bl TP_RequestSamplingAsync
	add r0, r4, #0x0
	bl TP_WaitRawResult
	cmp r0, #0x0
	bne _020164E4
	b _020164FA
_020164F4:
	add r0, sp, #0x8
	bl TP_GetLatestRawPointInAuto
_020164FA:
	add r0, sp, #0x0
	add r1, sp, #0x8
	bl TP_GetCalibratedPoint
	add r1, sp, #0x0
	ldrh r3, [r1, #0x6]
	cmp r3, #0x0
	bne _02016516
	ldrh r2, [r1, #0x0]
	ldr r0, _02016558 ; =UNK_021C48F8
	strh r2, [r0, #0x1c]
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x1e]
	b _0201653A
_02016516:
	ldr r0, _02016558 ; =UNK_021C48F8
	ldrh r2, [r0, #0x22]
	cmp r2, #0x0
	beq _02016536
	cmp r3, #0x1
	beq _0201652A
	cmp r3, #0x2
	beq _02016530
	cmp r3, #0x3
	b _0201653A
_0201652A:
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x1e]
	b _0201653A
_02016530:
	ldrh r1, [r1, #0x0]
	strh r1, [r0, #0x1c]
	b _0201653A
_02016536:
	mov r0, #0x0
	strh r0, [r1, #0x4]
_0201653A:
	add r0, sp, #0x0
	ldrh r2, [r0, #0x4]
	ldr r0, _02016558 ; =UNK_021C48F8
	ldrh r1, [r0, #0x22]
	eor r1, r2
	and r1, r2
	strh r1, [r0, #0x20]
	strh r2, [r0, #0x22]
	add sp, #0x10
	pop {r4, pc}
	nop
_02016550: .word 0x027FFFA8
_02016554: .word gUnknown21C48B8
_02016558: .word UNK_021C48F8
_0201655C: .word 0x04000130
_02016560: .word 0x00002FFF
_02016564: .word gUnk021C4918

	thumb_func_start FUN_02016568
FUN_02016568: ; 0x02016568
	ldr r0, _02016690 ; =gUnknown21C48B8
	ldr r1, [r0, #0x34]
	cmp r1, #0x3
	bls _02016572
	b _0201668C
_02016572:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201657E: ; jump table (using 16-bit offset)
	.short _0201668C - _0201657E - 2; case 0
	.short _02016586 - _0201657E - 2; case 1
	.short _020165BC - _0201657E - 2; case 2
	.short _02016642 - _0201657E - 2; case 3
_02016586:
	ldr r2, [r0, #0x48]
	mov r1, #0x8
	add r3, r2, #0x0
	tst r3, r1
	beq _02016596
	lsl r1, r1, #0x7
	orr r1, r2
	str r1, [r0, #0x48]
_02016596:
	ldr r1, _02016690 ; =gUnknown21C48B8
	mov r0, #0x8
	ldr r2, [r1, #0x44]
	add r3, r2, #0x0
	tst r3, r0
	beq _020165A8
	lsl r0, r0, #0x7
	orr r0, r2
	str r0, [r1, #0x44]
_020165A8:
	ldr r1, _02016690 ; =gUnknown21C48B8
	mov r0, #0x8
	ldr r2, [r1, #0x4c]
	add r3, r2, #0x0
	tst r3, r0
	beq _0201668C
	lsl r0, r0, #0x7
	orr r0, r2
	str r0, [r1, #0x4c]
	bx lr
_020165BC:
	ldr r3, [r0, #0x48]
	mov r0, #0x1
	lsl r0, r0, #0xa
	add r2, r3, #0x0
	mov r1, #0x0
	tst r2, r0
	beq _020165CE
	lsl r0, r0, #0x1
	orr r1, r0
_020165CE:
	mov r0, #0x2
	lsl r0, r0, #0xa
	add r2, r3, #0x0
	tst r2, r0
	beq _020165DC
	lsr r0, r0, #0x1
	orr r1, r0
_020165DC:
	ldr r2, _02016690 ; =gUnknown21C48B8
	ldr r0, _02016694 ; =0x0000F3FF
	ldr r3, [r2, #0x48]
	and r0, r3
	orr r0, r1
	str r0, [r2, #0x48]
	ldr r3, [r2, #0x44]
	mov r1, #0x1
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	mov r0, #0x0
	tst r2, r1
	beq _020165FA
	lsl r1, r1, #0x1
	orr r0, r1
_020165FA:
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	tst r2, r1
	beq _02016608
	lsr r1, r1, #0x1
	orr r0, r1
_02016608:
	ldr r2, _02016690 ; =gUnknown21C48B8
	ldr r1, _02016694 ; =0x0000F3FF
	ldr r3, [r2, #0x44]
	and r1, r3
	orr r0, r1
	str r0, [r2, #0x44]
	ldr r3, [r2, #0x4c]
	mov r1, #0x1
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	mov r0, #0x0
	tst r2, r1
	beq _02016626
	lsl r1, r1, #0x1
	orr r0, r1
_02016626:
	mov r1, #0x2
	lsl r1, r1, #0xa
	add r2, r3, #0x0
	tst r2, r1
	beq _02016634
	lsr r1, r1, #0x1
	orr r0, r1
_02016634:
	ldr r2, _02016690 ; =gUnknown21C48B8
	ldr r1, _02016694 ; =0x0000F3FF
	ldr r3, [r2, #0x4c]
	and r1, r3
	orr r0, r1
	str r0, [r2, #0x4c]
	bx lr
_02016642:
	mov r1, #0x2
	ldr r2, [r0, #0x48]
	lsl r1, r1, #0x8
	tst r1, r2
	beq _02016652
	mov r1, #0x1
	orr r1, r2
	str r1, [r0, #0x48]
_02016652:
	ldr r1, _02016690 ; =gUnknown21C48B8
	mov r0, #0x2
	ldr r2, [r1, #0x44]
	lsl r0, r0, #0x8
	tst r0, r2
	beq _02016664
	mov r0, #0x1
	orr r0, r2
	str r0, [r1, #0x44]
_02016664:
	ldr r1, _02016690 ; =gUnknown21C48B8
	mov r0, #0x2
	ldr r2, [r1, #0x4c]
	lsl r0, r0, #0x8
	tst r0, r2
	beq _02016676
	mov r0, #0x1
	orr r0, r2
	str r0, [r1, #0x4c]
_02016676:
	ldr r1, _02016690 ; =gUnknown21C48B8
	ldr r0, _02016698 ; =0x0000FCFF
	ldr r2, [r1, #0x48]
	and r2, r0
	str r2, [r1, #0x48]
	ldr r2, [r1, #0x44]
	and r2, r0
	str r2, [r1, #0x44]
	ldr r2, [r1, #0x4c]
	and r0, r2
	str r0, [r1, #0x4c]
_0201668C:
	bx lr
	nop
_02016690: .word gUnknown21C48B8
_02016694: .word 0x0000F3FF
_02016698: .word 0x0000FCFF

	thumb_func_start FUN_0201669C
FUN_0201669C: ; 0x0201669C
	ldr r2, _020166A4 ; =gUnknown21C48B8
	str r0, [r2, #0x54]
	str r1, [r2, #0x58]
	bx lr
	.balign 4
_020166A4: .word gUnknown21C48B8

	thumb_func_start FUN_020166A8
FUN_020166A8: ; 0x020166A8
	ldr r1, _020166B4 ; =gUnk021C4918
	ldrb r2, [r1, #0x8]
	orr r0, r2
	strb r0, [r1, #0x8]
	bx lr
	nop
_020166B4: .word gUnk021C4918

	thumb_func_start FUN_020166B8
FUN_020166B8: ; 0x020166B8
	ldr r1, _020166C4 ; =gUnk021C4918
	mvn r0, r0
	ldrb r2, [r1, #0x8]
	and r0, r2
	strb r0, [r1, #0x8]
	bx lr
	.balign 4
_020166C4: .word gUnk021C4918
