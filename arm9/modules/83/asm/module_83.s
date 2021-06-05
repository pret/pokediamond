	.include "asm/macros.inc"
	.include "global.inc"
	.include "constants/species.h"
	.section .text
	.balign 4, 0

	thumb_func_start MOD83_0222D5C0
MOD83_0222D5C0: ; 0x0222D5C0
	mov r0, #0
	bx lr
	thumb_func_end MOD83_0222D5C0

	thumb_func_start MOD83_0222D5C4
MOD83_0222D5C4: ; 0x0222D5C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	add r5, r0, #0
	mov r0, #5
	lsl r0, r0, #6
	add r0, r5, r0
	bl WindowIsInUse
	cmp r0, #0
	bne _0222D63C
	mov r1, #0x4f
	mov r0, #0
	add r3, r5, #0
	lsl r1, r1, #2
_0222D5E0:
	ldr r2, [r3, r1]
	cmp r2, #1
	bne _0222D632
	lsl r1, r0, #2
	add r3, r5, r1
	mov r1, #0x4f
	add r6, r0, #0
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r3, r1]
	mov r3, #0x1c
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r1, r1, #4
	ldr r7, _0222D670 ; =MOD83_0223A794
	mul r6, r3
	add r4, r7, r6
	ldr r3, [r4, #0x10]
	add r0, sp, #8
	add r1, r5, r1
	bl MOD83_022388E4
	ldr r1, [r4, #8]
	ldr r2, [r4, #0xc]
	add r0, sp, #8
	mov r3, #0x13
	bl MOD83_02238934
	ldr r0, [r4, #0x14]
	add r1, sp, #8
	str r0, [sp]
	ldr r0, [r5]
	ldr r2, [r7, r6]
	ldr r3, [r4, #4]
	bl MOD83_02238A38
	add sp, #0x5c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0222D632:
	add r0, r0, #1
	add r3, r3, #4
	cmp r0, #1
	blt _0222D5E0
	b _0222D668
_0222D63C:
	ldr r0, _0222D674 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0222D662
	ldr r0, _0222D678 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #5
	lsl r0, r0, #6
	add r0, r5, r0
	mov r1, #0
	bl FUN_0200CCF8
	mov r0, #5
	lsl r0, r0, #6
	add r0, r5, r0
	bl RemoveWindow
_0222D662:
	add sp, #0x5c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0222D668:
	mov r0, #0
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_0222D670: .word MOD83_0223A794
_0222D674: .word gMain
_0222D678: .word 0x000005DC
	thumb_func_end MOD83_0222D5C4

	thumb_func_start MOD83_0222D67C
MOD83_0222D67C: ; 0x0222D67C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0
	bl MOD83_02236E18
	mov r4, #0
	str r4, [r5, #0x24]
	cmp r0, #0
	bne _0222D6E6
	bl MOD83_02236E9C
	cmp r0, #4
	bhi _0222D6BE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222D6A2: ; jump table
	.short _0222D6AC - _0222D6A2 - 2 ; case 0
	.short _0222D6B0 - _0222D6A2 - 2 ; case 1
	.short _0222D6B4 - _0222D6A2 - 2 ; case 2
	.short _0222D6B8 - _0222D6A2 - 2 ; case 3
	.short _0222D6BC - _0222D6A2 - 2 ; case 4
_0222D6AC:
	mov r4, #2
	b _0222D6BE
_0222D6B0:
	mov r4, #1
	b _0222D6BE
_0222D6B4:
	mov r4, #5
	b _0222D6BE
_0222D6B8:
	mov r4, #4
	b _0222D6BE
_0222D6BC:
	mov r4, #3
_0222D6BE:
	add r0, r4, #0
	bl FUN_02016438
	ldr r0, [r5, #8]
	bl Pokedex_GetNatDexFlag
	cmp r0, #0
	beq _0222D6E6
	bl MOD83_02236EA8
	ldr r1, _0222D6E8 ; =gGameLanguage
	ldrb r1, [r1]
	cmp r1, r0
	bne _0222D6E6
	bl MOD83_02236E9C
	add r0, r0, #1
	str r0, [r5, #0x24]
	bl MOD83_02239490
_0222D6E6:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222D6E8: .word gGameLanguage
	thumb_func_end MOD83_0222D67C

	thumb_func_start MOD83_0222D6EC
MOD83_0222D6EC: ; 0x0222D6EC
	push {r4, lr}
	mov r1, #0x43
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r0, #0xa
	cmp r0, #4
	bhi _0222D7DC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222D708: ; jump table
	.short _0222D712 - _0222D708 - 2 ; case 0
	.short _0222D718 - _0222D708 - 2 ; case 1
	.short _0222D7DC - _0222D708 - 2 ; case 2
	.short _0222D74C - _0222D708 - 2 ; case 3
	.short _0222D7D0 - _0222D708 - 2 ; case 4
_0222D712:
	mov r0, #0xb
	str r0, [r4, r1]
	pop {r4, pc}
_0222D718:
	ldr r0, [r4, #4]
	bl FUN_02032D44
	mov r1, #0x78
	add r0, r1, #0
	add r0, #0x98
	str r1, [r4, r0]
	mov r1, #0xd
	add r0, r1, #0
	add r0, #0xff
	str r1, [r4, r0]
	mov r0, #0
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x14]
	bl FUN_0202AF50
	cmp r0, #1
	bne _0222D7DC
	ldr r1, [r4, #0x40]
	mov r0, #1
	orr r1, r0
	str r1, [r4, #0x40]
	ldr r1, [r4, #0x44]
	orr r0, r1
	str r0, [r4, #0x44]
	pop {r4, pc}
_0222D74C:
	add r1, #0xc
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _0222D7DC
	bl FUN_02032D9C
	ldr r1, [r4, #0x40]
	bic r0, r1
	beq _0222D7B2
	mov r2, #0x45
	lsl r2, r2, #2
	ldr r3, [r4, r2]
	cmp r3, #0xf
	bne _0222D7B2
	add r2, r2, #4
	ldr r2, [r4, r2]
	cmp r2, #0
	bne _0222D7B2
	cmp r1, r0
	beq _0222D7B2
	mov r2, #1
	add r1, r0, #0
	str r2, [r4, #0x48]
	tst r1, r2
	beq _0222D782
	str r2, [r4, #0x34]
	add r0, r2, #0
_0222D782:
	mov r1, #2
	add r2, r0, #0
	tst r2, r1
	beq _0222D790
	mov r0, #1
	str r0, [r4, #0x2c]
	add r0, r1, #0
_0222D790:
	mov r1, #4
	add r2, r0, #0
	tst r2, r1
	beq _0222D79E
	mov r0, #1
	str r0, [r4, #0x30]
	add r0, r1, #0
_0222D79E:
	mov r1, #3
	tst r1, r0
	beq _0222D7AC
	mov r1, #0x4e
	mov r2, #1
	lsl r1, r1, #2
	str r2, [r4, r1]
_0222D7AC:
	ldr r1, [r4, #0x40]
	orr r0, r1
	str r0, [r4, #0x40]
_0222D7B2:
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222D7DC
	bl FUN_02032D80
	mov r0, #0x43
	mov r1, #0xc
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r4, pc}
_0222D7D0:
	bl FUN_02032D80
	mov r0, #0x43
	mov r1, #0xc
	lsl r0, r0, #2
	str r1, [r4, r0]
_0222D7DC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_0222D6EC

	thumb_func_start MOD83_0222D7E0
MOD83_0222D7E0: ; 0x0222D7E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	mov r1, #0x45
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r0, #0xf
	cmp r0, #4
	bls _0222D7F4
	b _0222D994
_0222D7F4:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222D800: ; jump table
	.short _0222D80A - _0222D800 - 2 ; case 0
	.short _0222D832 - _0222D800 - 2 ; case 1
	.short _0222D85E - _0222D800 - 2 ; case 2
	.short _0222D932 - _0222D800 - 2 ; case 3
	.short _0222D974 - _0222D800 - 2 ; case 4
_0222D80A:
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222D818
	add sp, #0x60
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0222D818:
	add r0, r1, #4
	ldr r0, [r4, r0]
	sub r2, r0, #1
	add r0, r1, #4
	str r2, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222D82C
	mov r0, #0x10
	str r0, [r4, r1]
_0222D82C:
	add sp, #0x60
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222D832:
	mov r0, #0
	str r0, [sp]
	mov r0, #0x51
	str r0, [sp, #4]
	mov r1, #1
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #2
	bl FUN_0200CB00
	ldr r0, [r4]
	mov r1, #1
	bl FUN_02018744
	ldr r1, _0222D99C ; =0x00006B5A
	ldr r0, _0222D9A0 ; =0x05000042
	strh r1, [r0]
	mov r0, #0x45
	mov r1, #0x11
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0222D994
_0222D85E:
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	add r1, #0x10
	str r0, [sp, #4]
	add r0, sp, #0xc
	add r1, r4, r1
	mov r2, #0
	mov r3, #0xc
	bl MOD83_022388E4
	ldr r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	mvn r0, r0
	and r0, r1
	mov r1, #1
	add r2, r0, #0
	tst r2, r1
	beq _0222D892
	ldr r2, [r4, #0x38]
	tst r1, r2
	beq _0222D88E
	ldr r5, _0222D9A4 ; =MOD83_0223A7F0
	b _0222D8B2
_0222D88E:
	ldr r5, _0222D9A8 ; =MOD83_0223A804
	b _0222D8B2
_0222D892:
	mov r1, #2
	add r2, r0, #0
	tst r2, r1
	beq _0222D8A8
	ldr r2, [r4, #0x38]
	tst r1, r2
	beq _0222D8A4
	ldr r5, _0222D9AC ; =MOD83_0223A818
	b _0222D8B2
_0222D8A4:
	ldr r5, _0222D9B0 ; =MOD83_0223A82C
	b _0222D8B2
_0222D8A8:
	mov r1, #0x80
	tst r1, r0
	beq _0222D8B2
	ldr r5, _0222D9B4 ; =MOD83_0223A840
	mov r0, #0
_0222D8B2:
	ldr r1, [r4, #0x44]
	mov r3, #0x13
	orr r0, r1
	str r0, [r4, #0x44]
	ldr r1, [r5, #8]
	ldr r2, [r5, #0xc]
	add r0, sp, #0xc
	bl MOD83_02238934
	mov r0, #1
	str r0, [sp, #0x38]
	ldr r0, [r5, #0x10]
	add r1, sp, #0xc
	str r0, [sp]
	ldr r0, [r4]
	ldr r2, [r5]
	ldr r3, [r5, #4]
	bl MOD83_02238A38
	ldr r0, [sp, #0x1c]
	bl GetWindowX
	add r6, r0, #0
	ldr r0, [sp, #0x1c]
	bl GetWindowY
	add r7, r0, #0
	ldr r0, [sp, #0x1c]
	bl GetWindowWidth
	add r5, r0, #0
	ldr r0, [sp, #0x1c]
	bl GetWindowHeight
	str r5, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #1
	add r2, r6, #0
	add r3, r7, #0
	bl FUN_020186B4
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r1, #0x1e
	add r0, r1, #0
	add r0, #0xfe
	str r1, [r4, r0]
	mov r0, #0x12
	add r1, #0xf6
	str r0, [r4, r1]
	b _0222D994
_0222D932:
	add r0, r1, #0
	add r0, #8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222D94A
	add r0, r1, #0
	add r0, #8
	ldr r0, [r4, r0]
	add r1, #8
	sub r0, r0, #1
	str r0, [r4, r1]
	b _0222D994
_0222D94A:
	ldr r0, _0222D9B8 ; =gMain
	ldr r2, [r0, #0x48]
	mov r0, #3
	tst r0, r2
	beq _0222D994
	add r1, #0x10
	add r0, r4, r1
	bl RemoveWindow
	mov r0, #0x45
	mov r1, #0x13
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r1, _0222D9B8 ; =gMain
	add r0, #0xc
	ldr r1, [r1, #0x48]
	str r1, [r4, r0]
	ldr r0, _0222D9BC ; =0x000005DC
	bl FUN_020054C8
	b _0222D994
_0222D974:
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #0x45
	mov r1, #0xf
	lsl r0, r0, #2
	str r1, [r4, r0]
_0222D994:
	mov r0, #1
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222D99C: .word 0x00006B5A
_0222D9A0: .word 0x05000042
_0222D9A4: .word MOD83_0223A7F0
_0222D9A8: .word MOD83_0223A804
_0222D9AC: .word MOD83_0223A818
_0222D9B0: .word MOD83_0223A82C
_0222D9B4: .word MOD83_0223A840
_0222D9B8: .word gMain
_0222D9BC: .word 0x000005DC
	thumb_func_end MOD83_0222D7E0

	thumb_func_start MOD83_0222D9C0
MOD83_0222D9C0: ; 0x0222D9C0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, r1
	beq _0222DA48
	sub r1, r1, r0
	asr r0, r1, #1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #2
	asr r2, r0, #0x1f
	add r1, r0, #0
	eor r1, r2
	sub r2, r1, r2
	mov r1, #3
	lsl r1, r1, #0xe
	cmp r2, r1
	ble _0222D9F6
	cmp r0, #0
	ble _0222D9F4
	add r0, r1, #0
	b _0222D9F6
_0222D9F4:
	ldr r0, _0222DA4C ; =0xFFFF4000
_0222D9F6:
	mov r1, #0x41
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	add r0, r2, r0
	str r0, [r4, r1]
	add r0, r1, #4
	ldr r0, [r4, r0]
	ldr r2, [r4, r1]
	sub r2, r0, r2
	asr r3, r2, #0x1f
	eor r2, r3
	sub r3, r2, r3
	add r2, r1, #0
	add r2, #0xfc
	cmp r3, r2
	bge _0222DA18
	str r0, [r4, r1]
_0222DA18:
	mov r3, #0x41
	lsl r3, r3, #2
	ldr r5, [r4, r3]
	ldr r0, [r4]
	asr r3, r5, #0xb
	lsr r3, r3, #0x14
	add r3, r5, r3
	mov r1, #0
	mov r2, #3
	asr r3, r3, #0xc
	bl ScheduleSetBgPosText
	mov r3, #0x41
	lsl r3, r3, #2
	ldr r0, [r4]
	ldr r4, [r4, r3]
	mov r1, #2
	asr r3, r4, #0xb
	lsr r3, r3, #0x14
	add r3, r4, r3
	mov r2, #3
	asr r3, r3, #0xc
	bl ScheduleSetBgPosText
_0222DA48:
	pop {r3, r4, r5, pc}
	nop
_0222DA4C: .word 0xFFFF4000
	thumb_func_end MOD83_0222D9C0

	thumb_func_start MOD83_0222DA50
MOD83_0222DA50: ; 0x0222DA50
	push {r3, r4, r5, lr}
	sub sp, #0x40
	ldr r5, _0222DB4C ; =MOD83_0223A380
	add r4, r0, #0
	add r3, sp, #0x18
	mov r2, #5
_0222DA5C:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222DA5C
	ldr r3, _0222DB50 ; =MOD83_0223A370
	add r2, sp, #8
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, sp, #0x18
	bl GX_SetBanks
	add r0, sp, #8
	bl FUN_02016BBC
	mov r1, #0
	str r1, [sp]
	mov r3, #0xf
	ldr r0, [r4]
	mov r2, #2
	lsl r3, r3, #0xc
	bl MOD83_022387D8
	ldr r1, _0222DB54 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0x51
	bic r2, r0
	mov r0, #2
	orr r0, r2
	strh r0, [r1]
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	bl BG_ClearCharDataRange
	mov r0, #2
	lsl r0, r0, #0xe
	str r0, [sp]
	mov r1, #1
	mov r3, #0x36
	ldr r0, [r4]
	add r2, r1, #0
	lsl r3, r3, #0xa
	bl MOD83_022387D8
	ldr r1, _0222DB58 ; =0x0400000A
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0x51
	bic r2, r0
	mov r0, #1
	orr r2, r0
	strh r2, [r1]
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	mov r0, #0
	str r0, [sp]
	mov r1, #2
	mov r3, #0xe
	ldr r0, [r4]
	add r2, r1, #0
	lsl r3, r3, #0xc
	bl MOD83_022387D8
	ldr r1, _0222DB5C ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0x51
	bic r2, r0
	strh r2, [r1]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	bl BG_ClearCharDataRange
	bl FUN_0201BD5C
	mov r0, #0
	mov r1, #0x20
	mov r2, #0x51
	bl FUN_02002ED0
	mov r0, #0
	add r1, r0, #0
	mov r2, #0x51
	bl FUN_02002ED0
	mov r2, #5
	mov r1, #0
	lsl r2, r2, #0x18
	ldr r0, _0222DB60 ; =0x00006B5A
	strh r1, [r2]
	strh r0, [r2, #0x3e]
	str r1, [sp]
	mov r0, #0x51
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r2, #1
	mov r3, #2
	bl FUN_0200CB00
	mov r0, #1
	str r0, [sp]
	mov r0, #0x51
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0xa
	mov r3, #3
	bl FUN_0200CB00
	ldr r1, _0222DB60 ; =0x00006B5A
	ldr r0, _0222DB64 ; =0x05000042
	strh r1, [r0]
	add sp, #0x40
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222DB4C: .word MOD83_0223A380
_0222DB50: .word MOD83_0223A370
_0222DB54: .word 0x04000008
_0222DB58: .word 0x0400000A
_0222DB5C: .word 0x0400000C
_0222DB60: .word 0x00006B5A
_0222DB64: .word 0x05000042
	thumb_func_end MOD83_0222DA50

	thumb_func_start MOD83_0222DB68
MOD83_0222DB68: ; 0x0222DB68
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	bl MOD83_02238AFC
	bl MOD83_02238B4C
	mov r0, #0x25
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x27
	mov r2, #0x24
	mov r3, #0x26
	bl MOD83_02238BC4
	mov r0, #0
	mov r1, #0x15
	str r0, [sp]
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0x80
	mov r3, #8
	bl MOD83_02238DBC
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #1
	mov r1, #0x55
	str r0, [sp]
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r0, #0
	mov r2, #0x80
	mov r3, #0xb8
	bl MOD83_02238DBC
	mov r1, #0x55
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD83_0222DB68

	thumb_func_start MOD83_0222DBD0
MOD83_0222DBD0: ; 0x0222DBD0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x51
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x29
	mov r2, #0
	mov r3, #0x80
	bl GfGfxLoader_GXLoadPal
	mov r0, #0xe
	lsl r0, r0, #6
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r0, #0x51
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x74
	mov r1, #0x28
	mov r3, #2
	bl GfGfxLoader_LoadCharData
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_0222DBD0

	thumb_func_start MOD83_0222DC10
MOD83_0222DC10: ; 0x0222DC10
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	mov r1, #2
	add r6, r2, #0
	add r7, r3, #0
	bl GetBgTilemapBuffer
	ldr r1, _0222DC5C ; =0x00004380
	cmp r7, #2
	bne _0222DC2A
	add r1, r1, #2
_0222DC2A:
	lsl r2, r6, #5
	add r3, r4, r2
	lsl r2, r3, #1
	add r3, r3, #1
	strh r1, [r0, r2]
	add r2, r1, #1
	lsl r3, r3, #1
	strh r2, [r0, r3]
	add r3, r1, #0
	add r2, r6, #1
	lsl r2, r2, #5
	add r4, r4, r2
	add r3, #8
	lsl r2, r4, #1
	strh r3, [r0, r2]
	add r2, r4, #1
	add r1, #9
	lsl r2, r2, #1
	strh r1, [r0, r2]
	ldr r0, [r5]
	mov r1, #2
	bl FUN_02017CD0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222DC5C: .word 0x00004380
	thumb_func_end MOD83_0222DC10

	thumb_func_start MOD83_0222DC60
MOD83_0222DC60: ; 0x0222DC60
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	add r6, r2, #0
	mov r1, #2
	bl GetBgTilemapBuffer
	lsl r1, r6, #5
	add r3, r4, r1
	ldr r1, _0222DC9C ; =0x00004384
	lsl r2, r3, #1
	strh r1, [r0, r2]
	add r2, r3, #1
	lsl r2, r2, #1
	strh r1, [r0, r2]
	add r2, r6, #1
	lsl r2, r2, #5
	add r3, r4, r2
	lsl r2, r3, #1
	strh r1, [r0, r2]
	add r2, r3, #1
	lsl r2, r2, #1
	strh r1, [r0, r2]
	ldr r0, [r5]
	mov r1, #2
	bl FUN_02017CD0
	pop {r4, r5, r6, pc}
	nop
_0222DC9C: .word 0x00004384
	thumb_func_end MOD83_0222DC60

	thumb_func_start MOD83_0222DCA0
MOD83_0222DCA0: ; 0x0222DCA0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r6, r0, #0
	add r0, r2, #0
	add r7, r3, #0
	ldr r2, [sp, #0x28]
	mov r3, #0x51
	bl ReadMsgData_ExpandPlaceholders
	add r5, r0, #0
	mov r0, #0
	mov r1, #2
	bl GetFontAttribute
	add r2, r0, #0
	mov r0, #0
	add r1, r5, #0
	bl FUN_02002E14
	add r4, r0, #0
	add r0, r6, #0
	bl GetWindowWidth
	lsl r0, r0, #3
	add r4, #0x20
	sub r3, r0, r4
	ldr r0, [sp, #0x2c]
	mov r1, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r7, [sp, #8]
	add r0, r6, #0
	add r2, r5, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl String_dtor
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_0222DCA0

	thumb_func_start MOD83_0222DCF4
MOD83_0222DCF4: ; 0x0222DCF4
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	cmp r2, #0x64
	blt _0222DD04
	mov r3, #3
	mov r1, #0
	b _0222DD12
_0222DD04:
	cmp r2, #0xa
	blt _0222DD0E
	mov r3, #3
	mov r1, #1
	b _0222DD12
_0222DD0E:
	mov r3, #2
	mov r1, #1
_0222DD12:
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #0
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_0222DCF4

	thumb_func_start MOD83_0222DD24
MOD83_0222DD24: ; 0x0222DD24
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r2, [sp, #0x18]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	add r4, r3, #0
	ldr r2, _0222DEB4 ; =0x000001EE
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x51
	bl NewMsgDataFromNarc
	str r0, [sp, #0x24]
	mov r0, #0x51
	bl ScrStrBufs_new
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0xc]
	bl PlayerProfile_GetTrainerGender
	cmp r0, #1
	bne _0222DD58
	ldr r0, _0222DEB8 ; =0x0003040F
	str r0, [sp, #0x1c]
	b _0222DD5C
_0222DD58:
	ldr r0, _0222DEBC ; =0x0007080F
	str r0, [sp, #0x1c]
_0222DD5C:
	ldr r0, [sp, #0x14]
	ldr r1, _0222DEC0 ; =MOD83_0223A85C
	lsl r0, r0, #4
	str r0, [sp, #0x20]
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x18]
	str r0, [sp]
	ldr r0, [sp, #0x10]
	mov r2, #3
	ldr r0, [r0]
	add r3, r4, #0
	bl MOD83_02238A38
	ldr r4, _0222DEC4 ; =MOD83_0223A784
	mov r6, #1
	mov r5, #0x10
_0222DD7C:
	cmp r6, #4
	bne _0222DD88
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x4c]
	cmp r0, #0
	beq _0222DDB8
_0222DD88:
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x24]
	ldr r2, [r4]
	mov r3, #0x51
	bl ReadMsgData_ExpandPlaceholders
	add r7, r0, #0
	str r5, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x18]
	add r2, r7, #0
	ldr r0, [r0, #0x10]
	mov r3, #0x20
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
_0222DDB8:
	add r6, r6, #1
	add r4, r4, #4
	add r5, #0x10
	cmp r6, #5
	blo _0222DD7C
	ldr r2, [sp, #0x10]
	ldr r0, [sp, #0x28]
	ldr r2, [r2, #0xc]
	mov r1, #0
	bl BufferPlayersName
	mov r0, #0x10
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x24]
	ldr r0, [r0, #0x10]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x1c]
	bl MOD83_0222DCA0
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x10]
	bl GetIGTHours
	add r1, r0, #0
	ldr r0, [sp, #0x28]
	bl MOD83_0222DCF4
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x10]
	bl GetIGTMinutes
	add r2, r0, #0
	mov r3, #2
	ldr r0, [sp, #0x28]
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	bl BufferIntegerAsString
	mov r0, #0x11
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x24]
	ldr r0, [r0, #0x10]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x1c]
	bl MOD83_0222DCA0
	mov r1, #0
	str r1, [sp]
	mov r3, #1
	ldr r2, [sp, #0x10]
	str r3, [sp, #4]
	ldr r0, [sp, #0x28]
	ldr r2, [r2, #0x50]
	bl BufferIntegerAsString
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x30
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x24]
	ldr r0, [r0, #0x10]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x1c]
	bl MOD83_0222DCA0
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x4c]
	cmp r0, #0
	beq _0222DE76
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #8]
	bl Pokedex_CountSeenMons
	add r1, r0, #0
	ldr r0, [sp, #0x28]
	bl MOD83_0222DCF4
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0x40
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x24]
	ldr r0, [r0, #0x10]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x1c]
	bl MOD83_0222DCA0
_0222DE76:
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x18]
	ldr r0, [sp, #0x18]
	ldr r2, [r2, #0x38]
	ldr r3, [r3, #0x3c]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x10]
	mov r1, #0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_0200CCA4
	ldr r1, _0222DEC8 ; =MOD83_0223A854
	ldr r0, [sp, #0x20]
	ldr r2, [r1, r0]
	ldr r0, [sp, #0x14]
	lsl r1, r0, #2
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r0, #0xcc
	str r2, [r0]
	ldr r0, [sp, #0x28]
	bl ScrStrBufs_delete
	ldr r0, [sp, #0x24]
	bl DestroyMsgData
	mov r0, #1
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222DEB4: .word 0x000001EE
_0222DEB8: .word 0x0003040F
_0222DEBC: .word 0x0007080F
_0222DEC0: .word MOD83_0223A85C
_0222DEC4: .word MOD83_0223A784
_0222DEC8: .word MOD83_0223A854
	thumb_func_end MOD83_0222DD24

	thumb_func_start MOD83_0222DECC
MOD83_0222DECC: ; 0x0222DECC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	add r5, r1, #0
	add r1, r2, #0
	ldr r2, [r4, #0x24]
	add r6, r3, #0
	cmp r2, #0
	bne _0222DEE4
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_0222DEE4:
	sub r2, r2, #1
	cmp r2, #4
	bhi _0222DF12
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0222DEF6: ; jump table
	.short _0222DF00 - _0222DEF6 - 2 ; case 0
	.short _0222DF04 - _0222DEF6 - 2 ; case 1
	.short _0222DF08 - _0222DEF6 - 2 ; case 2
	.short _0222DF0C - _0222DEF6 - 2 ; case 3
	.short _0222DF10 - _0222DEF6 - 2 ; case 4
_0222DF00:
	mov r0, #4
	b _0222DF12
_0222DF04:
	mov r0, #5
	b _0222DF12
_0222DF08:
	mov r0, #6
	b _0222DF12
_0222DF0C:
	mov r0, #7
	b _0222DF12
_0222DF10:
	mov r0, #8
_0222DF12:
	str r0, [sp]
	ldr r0, [r4]
	mov r2, #3
	add r3, r6, #0
	bl MOD83_02238A38
	add r0, r4, #0
	mov r1, #0x1a
	add r2, r6, #0
	bl MOD83_0222DC60
	ldr r0, _0222DF3C ; =MOD83_0223A854
	lsl r1, r5, #4
	ldr r1, [r0, r1]
	lsl r0, r5, #2
	add r0, r4, r0
	add r0, #0xcc
	str r1, [r0]
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222DF3C: .word MOD83_0223A854
	thumb_func_end MOD83_0222DECC

	thumb_func_start MOD83_0222DF40
MOD83_0222DF40: ; 0x0222DF40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	add r4, r1, #0
	add r7, r3, #0
	str r2, [sp, #4]
	cmp r0, #0
	bne _0222DF88
	ldr r0, [r5, #0x14]
	bl FUN_0202AF50
	cmp r0, #1
	bne _0222DF60
	mov r0, #1
	str r0, [r5, #0x34]
_0222DF60:
	ldr r0, [r5, #4]
	bl Sav2_SysInfo_get
	bl FUN_02023820
	cmp r0, #1
	bne _0222DF72
	mov r0, #1
	str r0, [r5, #0x34]
_0222DF72:
	mov r0, #0x51
	bl MOD83_SetHeapId
	bl MOD83_02238700
	cmp r0, #0
	beq _0222DF88
	mov r0, #1
	str r0, [r5, #0x34]
	bl MOD83_02239450
_0222DF88:
	ldr r0, [r5, #0x34]
	cmp r0, #1
	bne _0222DF98
	ldr r0, [r5, #0x4c]
	cmp r0, #0
	bne _0222DF98
	mov r0, #0
	str r0, [r5, #0x34]
_0222DF98:
	ldr r0, [r5, #0x34]
	cmp r0, #1
	bne _0222DFDC
	ldr r0, _0222DFE4 ; =MOD83_0223A85C
	lsl r6, r4, #4
	ldr r0, [r0, r6]
	ldr r1, [sp, #4]
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #3
	add r3, r7, #0
	bl MOD83_02238A38
	add r0, r5, #0
	mov r1, #0x1a
	add r2, r7, #0
	bl MOD83_0222DC60
	ldr r0, _0222DFE8 ; =MOD83_0223A854
	ldr r1, [r0, r6]
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0xcc
	str r1, [r0]
	ldr r1, [r5, #0x38]
	mov r0, #1
	orr r0, r1
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x14]
	bl FUN_0202AF60
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222DFDC:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222DFE4: .word MOD83_0223A85C
_0222DFE8: .word MOD83_0223A854
	thumb_func_end MOD83_0222DF40

	thumb_func_start MOD83_0222DFEC
MOD83_0222DFEC: ; 0x0222DFEC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x2c]
	add r4, r1, #0
	add r7, r3, #0
	cmp r0, #1
	bne _0222E03C
	ldr r0, [r5, #0x4c]
	cmp r0, #1
	bne _0222E03C
	ldr r0, _0222E040 ; =MOD83_0223A85C
	lsl r6, r4, #4
	ldr r0, [r0, r6]
	add r1, r2, #0
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #3
	bl MOD83_02238A38
	add r0, r5, #0
	mov r1, #0x1a
	add r2, r7, #0
	mov r3, #1
	bl MOD83_0222DC10
	lsl r3, r4, #2
	add r1, r5, r3
	mov r0, #1
	add r1, #0xe8
	str r0, [r1]
	ldr r1, _0222E044 ; =MOD83_0223A854
	ldr r2, [r1, r6]
	add r1, r5, r3
	add r1, #0xcc
	str r2, [r1]
	ldr r2, [r5, #0x38]
	mov r1, #2
	orr r1, r2
	str r1, [r5, #0x38]
	pop {r3, r4, r5, r6, r7, pc}
_0222E03C:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E040: .word MOD83_0223A85C
_0222E044: .word MOD83_0223A854
	thumb_func_end MOD83_0222DFEC

	thumb_func_start MOD83_0222E048
MOD83_0222E048: ; 0x0222E048
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	add r5, r1, #0
	add r7, r3, #0
	cmp r0, #1
	bne _0222E08A
	ldr r0, _0222E090 ; =MOD83_0223A85C
	lsl r6, r5, #4
	ldr r0, [r0, r6]
	add r1, r2, #0
	str r0, [sp]
	ldr r0, [r4]
	mov r2, #3
	bl MOD83_02238A38
	lsl r5, r5, #2
	add r0, r4, r5
	mov r3, #1
	add r0, #0xe8
	str r3, [r0]
	add r0, r4, #0
	mov r1, #0x1a
	add r2, r7, #0
	bl MOD83_0222DC10
	ldr r0, _0222E094 ; =MOD83_0223A854
	ldr r1, [r0, r6]
	add r0, r4, r5
	add r0, #0xcc
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222E08A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E090: .word MOD83_0223A85C
_0222E094: .word MOD83_0223A854
	thumb_func_end MOD83_0222E048

	thumb_func_start MOD83_0222E098
MOD83_0222E098: ; 0x0222E098
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, _0222E0D4 ; =MOD83_0223A85C
	lsl r6, r4, #4
	ldr r0, [r0, r6]
	add r1, r2, #0
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #3
	add r7, r3, #0
	bl MOD83_02238A38
	lsl r4, r4, #2
	add r0, r5, r4
	mov r3, #2
	add r0, #0xe8
	str r3, [r0]
	add r0, r5, #0
	mov r1, #0x1a
	add r2, r7, #0
	bl MOD83_0222DC10
	ldr r0, _0222E0D8 ; =MOD83_0223A854
	ldr r1, [r0, r6]
	add r0, r5, r4
	add r0, #0xcc
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E0D4: .word MOD83_0223A85C
_0222E0D8: .word MOD83_0223A854
	thumb_func_end MOD83_0222E098

	thumb_func_start MOD83_0222E0DC
MOD83_0222E0DC: ; 0x0222E0DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x70
	add r7, r0, #0
	mov r0, #0
	str r0, [sp, #0xc]
	mov r0, #0x13
	str r0, [r7, #0x20]
	ldr r0, [sp, #0xc]
	ldr r4, _0222E1F0 ; =MOD83_0223A854
	str r0, [sp, #0x10]
	add r0, r7, #0
	str r0, [sp, #8]
	add r0, #0x5c
	str r0, [sp, #8]
	add r0, r7, #0
	str r0, [sp, #0x14]
	add r0, #0x20
	mov r5, #1
	str r7, [sp, #0x18]
	str r0, [sp, #0x14]
_0222E104:
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r1, [sp, #8]
	ldr r3, _0222E1F4 ; =0x000001EE
	add r0, sp, #0x1c
	mov r2, #1
	bl MOD83_022388E4
	ldr r2, [r4, #4]
	ldr r3, [r7, #0x20]
	add r0, sp, #0x1c
	mov r1, #0x1a
	bl MOD83_02238934
	ldr r0, [r4, #0xc]
	mov ip, r0
	cmp r0, #0
	beq _0222E1A4
	ldr r0, [sp, #0x18]
	add r0, #0xcc
	ldr r0, [r0]
	cmp r0, #0
	beq _0222E188
	ldr r0, [sp, #0x2c]
	mov r1, #3
	bl MoveWindowX
	lsl r1, r5, #0x18
	ldr r0, [sp, #0x2c]
	lsr r1, r1, #0x18
	bl MoveWindowY
	ldr r2, [sp, #0x54]
	ldr r3, [sp, #0x58]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [sp, #0x2c]
	mov r1, #0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_0200CCA4
	ldr r0, [sp, #0x18]
	add r0, #0xe8
	ldr r3, [r0]
	cmp r3, #0
	beq _0222E172
	add r0, r7, #0
	mov r1, #0x1a
	add r2, r5, #0
	bl MOD83_0222DC10
	b _0222E17C
_0222E172:
	add r0, r7, #0
	mov r1, #0x1a
	add r2, r5, #0
	bl MOD83_0222DC60
_0222E17C:
	ldr r0, [r4, #4]
	add r0, r0, #2
	add r5, r5, r0
	mov r0, #1
	str r0, [sp, #0xc]
	b _0222E1C2
_0222E188:
	ldr r1, [sp, #0x10]
	add r0, r7, #0
	add r2, sp, #0x1c
	add r3, r5, #0
	mov r6, ip
	blx r6
	cmp r0, #1
	bne _0222E1C2
	ldr r0, [r4, #4]
	add r0, r0, #2
	add r5, r5, r0
	mov r0, #1
	str r0, [sp, #0xc]
	b _0222E1C2
_0222E1A4:
	ldr r0, [r4, #8]
	add r1, sp, #0x1c
	str r0, [sp]
	ldr r0, [r7]
	mov r2, #3
	add r3, r5, #0
	bl MOD83_02238A38
	ldr r0, [sp, #0x18]
	ldr r1, [r4]
	add r0, #0xcc
	str r1, [r0]
	ldr r0, [r4, #4]
	add r0, r0, #2
	add r5, r5, r0
_0222E1C2:
	ldr r0, [sp, #0x14]
	ldr r1, [r4, #4]
	ldr r2, [r0]
	mov r0, #0x1a
	mul r0, r1
	add r1, r2, r0
	ldr r0, [sp, #0x14]
	add r4, #0x10
	str r1, [r0]
	ldr r0, [sp, #8]
	add r0, #0x10
	str r0, [sp, #8]
	ldr r0, [sp, #0x18]
	add r0, r0, #4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #7
	blo _0222E104
	ldr r0, [sp, #0xc]
	add sp, #0x70
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E1F0: .word MOD83_0223A854
_0222E1F4: .word 0x000001EE
	thumb_func_end MOD83_0222E0DC

	thumb_func_start MOD83_0222E1F8
MOD83_0222E1F8: ; 0x0222E1F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r6, r0, #0
	add r5, r6, #0
	str r1, [sp, #0xc]
	mov r4, #0
	add r5, #0x5c
_0222E206:
	add r0, r5, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _0222E294
	ldr r0, [sp, #0xc]
	cmp r4, r0
	bne _0222E256
	add r0, r5, #0
	mov r1, #1
	mov r2, #0xa
	mov r3, #3
	bl FUN_0200CCA4
	add r0, r5, #0
	bl GetWindowX
	str r0, [sp, #0x10]
	add r0, r5, #0
	bl GetWindowY
	str r0, [sp, #0x14]
	add r0, r5, #0
	bl GetWindowWidth
	add r7, r0, #0
	add r0, r5, #0
	bl GetWindowHeight
	str r7, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [r6]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	mov r1, #0
	bl FUN_020186B4
	b _0222E294
_0222E256:
	mov r1, #1
	add r0, r5, #0
	add r2, r1, #0
	mov r3, #2
	bl FUN_0200CCA4
	add r0, r5, #0
	bl GetWindowX
	str r0, [sp, #0x18]
	add r0, r5, #0
	bl GetWindowY
	str r0, [sp, #0x1c]
	add r0, r5, #0
	bl GetWindowWidth
	add r7, r0, #0
	add r0, r5, #0
	bl GetWindowHeight
	str r7, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r6]
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	mov r1, #0
	bl FUN_020186B4
_0222E294:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #7
	blo _0222E206
	ldr r0, [r6]
	mov r1, #0
	bl FUN_02017CD0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_0222E1F8

	thumb_func_start MOD83_0222E2A8
MOD83_0222E2A8: ; 0x0222E2A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r2, r1, #0
	ldr r1, [r5, #0x54]
	mov r7, #6
	add r4, r1, #0
	mov r0, #0
	sub r6, r7, #7
_0222E2B8:
	add r4, r4, r2
	cmp r4, r6
	bne _0222E2C0
	add r4, r0, #0
_0222E2C0:
	cmp r4, #7
	bne _0222E2C6
	add r4, r7, #0
_0222E2C6:
	cmp r4, r1
	beq _0222E2DC
	lsl r3, r4, #2
	add r3, r5, r3
	add r3, #0xcc
	ldr r3, [r3]
	cmp r3, #0
	beq _0222E2B8
	ldr r0, _0222E2E0 ; =0x000005DC
	bl FUN_020054C8
_0222E2DC:
	str r4, [r5, #0x54]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E2E0: .word 0x000005DC
	thumb_func_end MOD83_0222E2A8

	thumb_func_start MOD83_0222E2E4
MOD83_0222E2E4: ; 0x0222E2E4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x54]
	add r1, r5, #0
	add r1, #0x5c
	lsl r0, r0, #4
	add r0, r1, r0
	bl GetWindowY
	sub r0, r0, #1
	lsl r4, r0, #3
	ldr r0, [r5, #0x54]
	add r1, r5, #0
	add r1, #0x5c
	lsl r0, r0, #4
	add r0, r1, r0
	bl GetWindowHeight
	add r0, r0, #2
	lsl r3, r0, #3
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r2, [r5, r0]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r2, r1, #0xc
	cmp r2, r4
	ble _0222E322
	lsl r1, r4, #0xc
	str r1, [r5, r0]
_0222E322:
	add r2, #0xc0
	cmp r2, r4
	bgt _0222E334
	add r0, r4, r3
	sub r0, #0xc0
	lsl r1, r0, #0xc
	mov r0, #0x42
	lsl r0, r0, #2
	str r1, [r5, r0]
_0222E334:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD83_0222E2E4

	thumb_func_start MOD83_0222E338
MOD83_0222E338: ; 0x0222E338
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #0x42
	ldr r0, [sp]
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	ldr r5, [sp]
	asr r0, r1, #0xb
	lsr r0, r0, #0x14
	add r0, r1, r0
	asr r7, r0, #0xc
	add r0, r7, #0
	str r0, [sp, #0xc]
	add r0, #0xc0
	ldr r6, [sp, #4]
	add r5, #0x5c
	str r0, [sp, #0xc]
_0222E362:
	add r0, r5, #0
	bl WindowIsInUse
	cmp r0, #0
	beq _0222E38E
	add r0, r5, #0
	bl GetWindowY
	sub r0, r0, #1
	lsl r4, r0, #3
	add r0, r5, #0
	bl GetWindowHeight
	cmp r7, r4
	ble _0222E384
	mov r0, #1
	str r0, [sp, #8]
_0222E384:
	ldr r0, [sp, #0xc]
	cmp r0, r4
	bgt _0222E38E
	mov r0, #1
	str r0, [sp, #4]
_0222E38E:
	add r6, r6, #1
	add r5, #0x10
	cmp r6, #7
	blo _0222E362
	mov r1, #0x15
	ldr r0, [sp]
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	ldr r1, [sp, #8]
	bl FUN_020200A0
	mov r1, #0x55
	ldr r0, [sp]
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	ldr r1, [sp, #4]
	bl FUN_020200A0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD83_0222E338

	thumb_func_start MOD83_0222E3B8
MOD83_0222E3B8: ; 0x0222E3B8
	push {r3, r4, r5, r6, r7, lr}
	bl OverlayManager_GetData
	mov r1, #0x15
	add r7, r0, #0
	lsl r1, r1, #4
	ldr r0, [r7, r1]
	cmp r0, #0
	bne _0222E3D2
	add r1, r1, #4
	ldr r1, [r7, r1]
	cmp r1, #0
	beq _0222E3E4
_0222E3D2:
	bl FUN_0201FFC8
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	bl FUN_0201FFC8
	bl MOD83_02238E48
_0222E3E4:
	add r5, r7, #0
	mov r6, #0
	add r4, r7, #0
	add r5, #0x5c
_0222E3EC:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	beq _0222E3FE
	add r0, r5, #0
	bl FUN_02019570
	add r0, r5, #0
	bl RemoveWindow
_0222E3FE:
	add r6, r6, #1
	add r4, #0x10
	add r5, #0x10
	cmp r6, #7
	blo _0222E3EC
	ldr r0, [r7]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r7]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r7]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r7]
	bl FreeToHeap
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_0222E3B8

	thumb_func_start MOD83_0222E430
MOD83_0222E430: ; 0x0222E430
	mov r1, #0x56
	lsl r1, r1, #2
	ldr r2, [r0, r1]
	lsl r3, r2, #1
	ldr r2, _0222E45C ; =MOD83_0223A7B0
	ldrh r2, [r2, r3]
	cmp r2, #0
	bne _0222E444
	mov r2, #0
	str r2, [r0, r1]
_0222E444:
	mov r1, #0x56
	lsl r1, r1, #2
	ldr r3, [r0, r1]
	add r2, r3, #1
	str r2, [r0, r1]
	ldr r0, _0222E45C ; =MOD83_0223A7B0
	lsl r1, r3, #1
	ldrh r1, [r0, r1]
	ldr r0, _0222E460 ; =0x0500006C
	strh r1, [r0]
	bx lr
	nop
_0222E45C: .word MOD83_0223A7B0
_0222E460: .word 0x0500006C
	thumb_func_end MOD83_0222E430

	thumb_func_start MOD83_0222E464
MOD83_0222E464: ; 0x0222E464
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0201C30C
	bl FUN_02009F80
	add r0, r4, #0
	bl DoScheduledBgGpuUpdates
	ldr r3, _0222E484 ; =MOD83_027E0000
	ldr r1, _0222E488 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_0222E484: .word 0x027E0000
_0222E488: .word 0x00003FF8
	thumb_func_end MOD83_0222E464

	thumb_func_start MOD83_0222E48C
MOD83_0222E48C: ; 0x0222E48C
	push {r3, r4, r5, lr}
	mov r2, #1
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x51
	lsl r2, r2, #0x12
	bl CreateHeap
	mov r1, #0x57
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #0x51
	bl OverlayManager_CreateAndGetData
	mov r2, #0x57
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r0, #0x51
	bl FUN_02016B94
	str r0, [r4]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl OverlayManager_GetField18
	ldr r0, [r0, #8]
	str r0, [r4, #4]
	bl FUN_0202251C
	str r0, [r4, #0x14]
	mov r0, #0x41
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	ldr r0, [r4, #4]
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r4, #0xc]
	ldr r0, [r4, #4]
	bl Sav2_Pokedex_get
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	bl Sav2_PlayerData_GetIGTAddr
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	bl Pokedex_GetSinnohDexFlag
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0xc]
	bl PlayerProfile_CountBadges
	str r0, [r4, #0x50]
	mov r0, #0x45
	mov r1, #0xf
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0x51
	bl MOD83_02238770
	ldr r0, [r4, #4]
	bl FUN_02022804
	cmp r0, #0
	bne _0222E530
	mov r0, #0x4d
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
_0222E530:
	mov r0, #0
	bl FUN_0200516C
	mov r0, #0
	bl FUN_0200415C
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_0222E48C

	thumb_func_start MOD83_0222E540
MOD83_0222E540: ; 0x0222E540
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	add r0, r0, #1
	str r0, [r4, #0x18]
	bl CTRDG_IsExisting
	add r0, r4, #0
	bl MOD83_0222D7E0
	cmp r0, #1
	bne _0222E570
	add r0, r4, #0
	bl MOD83_0222D6EC
	add r0, r4, #0
	bl MOD83_0222D9C0
	mov r0, #0
	pop {r4, r5, r6, pc}
_0222E570:
	add r0, r4, #0
	bl MOD83_0222E430
	ldr r0, [r5]
	cmp r0, #9
	bhi _0222E5D8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E588: ; jump table
	.short _0222E59C - _0222E588 - 2 ; case 0
	.short _0222E5A8 - _0222E588 - 2 ; case 1
	.short _0222E5CE - _0222E588 - 2 ; case 2
	.short _0222E5E8 - _0222E588 - 2 ; case 3
	.short _0222E616 - _0222E588 - 2 ; case 4
	.short _0222E656 - _0222E588 - 2 ; case 5
	.short _0222E74A - _0222E588 - 2 ; case 6
	.short _0222E772 - _0222E588 - 2 ; case 7
	.short _0222E77C - _0222E588 - 2 ; case 8
	.short _0222E784 - _0222E588 - 2 ; case 9
_0222E59C:
	add r0, r4, #0
	bl MOD83_0222DA50
	mov r0, #1
	str r0, [r5]
	b _0222E788
_0222E5A8:
	add r0, r4, #0
	bl MOD83_0222D5C0
	cmp r0, #0
	bne _0222E5B8
	mov r0, #3
	str r0, [r5]
	b _0222E788
_0222E5B8:
	mov r0, #1
	mov r1, #2
	add r2, r5, #0
	mov r3, #8
	bl MOD83_0223886C
	mov r0, #5
	ldr r1, _0222E79C ; =0x00007D8C
	lsl r0, r0, #0x18
	strh r1, [r0]
	b _0222E788
_0222E5CE:
	add r0, r4, #0
	bl MOD83_0222D5C4
	cmp r0, #0
	beq _0222E5DA
_0222E5D8:
	b _0222E788
_0222E5DA:
	mov r0, #0
	mov r1, #3
	add r2, r5, #0
	mov r3, #8
	bl MOD83_0223886C
	b _0222E788
_0222E5E8:
	mov r0, #0x43
	mov r1, #0xc
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, #0x28
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222E60A
	mov r0, #2
	str r0, [r4, #0x58]
	mov r0, #0
	mov r1, #7
	add r2, r5, #0
	mov r3, #8
	bl MOD83_0223886C
	b _0222E788
_0222E60A:
	add r0, r4, #0
	bl MOD83_0222D67C
	mov r0, #4
	str r0, [r5]
	b _0222E788
_0222E616:
	add r0, r4, #0
	bl MOD83_0222DB68
	add r0, r4, #0
	bl MOD83_0222DBD0
	ldr r0, _0222E7A0 ; =MOD83_0222E464
	ldr r1, [r4]
	bl Main_SetVBlankIntrCB
	add r0, r4, #0
	bl MOD83_0222E0DC
	ldr r1, [r4, #0x54]
	add r0, r4, #0
	bl MOD83_0222E1F8
	mov r0, #1
	mov r1, #5
	add r2, r5, #0
	mov r3, #8
	bl MOD83_0223886C
	mov r0, #5
	ldr r1, _0222E79C ; =0x00007D8C
	lsl r0, r0, #0x18
	strh r1, [r0]
	mov r0, #0x43
	mov r1, #0xa
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _0222E788
_0222E656:
	ldr r0, _0222E7A4 ; =gMain
	mov r1, #3
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0222E6E8
	mov r1, #1
	tst r0, r1
	ldr r0, _0222E7A8 ; =0x000005DC
	beq _0222E69A
	bl FUN_020054C8
	ldr r0, [r4, #0x54]
	lsl r0, r0, #2
	add r0, r4, r0
	add r0, #0xcc
	ldr r0, [r0]
	str r0, [r4, #0x58]
	cmp r0, #5
	bne _0222E6A8
	bl CTRDG_IsPulledOut
	cmp r0, #1
	bne _0222E6A8
	mov r0, #0x43
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0xc
	beq _0222E692
	bl FUN_02032D80
_0222E692:
	mov r0, #0x51
	bl FUN_02089F24
	b _0222E6A8
_0222E69A:
	bl FUN_020054C8
	mov r0, #0
	str r0, [r4, #0x58]
	mov r0, #1
	bl MOD83_02238860
_0222E6A8:
	ldr r0, [r4, #0x58]
	cmp r0, #2
	bne _0222E6C2
	ldr r1, [r4, #0x40]
	mov r0, #0x80
	orr r1, r0
	str r1, [r4, #0x40]
	mov r1, #1
	add r0, #0x98
	str r1, [r4, r0]
	mov r0, #6
	str r0, [r5]
	b _0222E6D8
_0222E6C2:
	cmp r0, #6
	bne _0222E6CC
	mov r0, #1
	bl MOD83_02238860
_0222E6CC:
	mov r0, #0
	mov r1, #7
	add r2, r5, #0
	mov r3, #8
	bl MOD83_0223886C
_0222E6D8:
	mov r0, #0x43
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0xd
	bne _0222E788
	mov r1, #0xe
	str r1, [r4, r0]
	b _0222E788
_0222E6E8:
	ldr r1, [r4, #0x48]
	cmp r1, #1
	bne _0222E6FA
	add r0, r4, #0
	bl MOD83_0222E0DC
	mov r0, #0
	str r0, [r4, #0x48]
	b _0222E788
_0222E6FA:
	mov r1, #0x40
	tst r0, r1
	beq _0222E708
	add r0, r4, #0
	sub r1, #0x41
	bl MOD83_0222E2A8
_0222E708:
	ldr r0, _0222E7A4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x80
	tst r0, r1
	beq _0222E71A
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222E2A8
_0222E71A:
	ldr r1, [r4, #0x54]
	add r0, r4, #0
	bl MOD83_0222E1F8
	add r0, r4, #0
	bl MOD83_0222E2E4
	add r0, r4, #0
	bl MOD83_0222E338
	ldr r0, [r5]
	cmp r0, #5
	bne _0222E788
	mov r0, #0x4e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _0222E788
	mov r1, #0
	str r1, [r4, r0]
	mov r1, #1
	sub r0, #0x20
	str r1, [r4, r0]
	b _0222E788
_0222E74A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0xf
	bne _0222E788
	add r0, #0xc
	ldr r1, [r4, r0]
	mov r0, #2
	tst r0, r1
	beq _0222E764
	mov r0, #5
	str r0, [r5]
	b _0222E788
_0222E764:
	mov r0, #0
	mov r1, #7
	add r2, r5, #0
	mov r3, #8
	bl MOD83_0223886C
	b _0222E788
_0222E772:
	add r0, r6, #0
	bl MOD83_0222E3B8
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222E77C:
	add r0, r5, #0
	bl MOD83_022388CC
	b _0222E788
_0222E784:
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222E788:
	add r0, r4, #0
	bl MOD83_0222D6EC
	add r0, r4, #0
	bl MOD83_0222D9C0
	bl MOD83_02238D58
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E79C: .word 0x00007D8C
_0222E7A0: .word MOD83_0222E464
_0222E7A4: .word gMain
_0222E7A8: .word 0x000005DC
	thumb_func_end MOD83_0222E540

	thumb_func_start MOD83_0222E7AC
MOD83_0222E7AC: ; 0x0222E7AC
	push {r3, lr}
	ldr r0, [r0, #0x58]
	cmp r0, #7
	bhi _0222E822
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E7C0: ; jump table
	.short _0222E81A - _0222E7C0 - 2 ; case 0
	.short _0222E7D0 - _0222E7C0 - 2 ; case 1
	.short _0222E7DA - _0222E7C0 - 2 ; case 2
	.short _0222E7E4 - _0222E7C0 - 2 ; case 3
	.short _0222E7F8 - _0222E7C0 - 2 ; case 4
	.short _0222E7EE - _0222E7C0 - 2 ; case 5
	.short _0222E802 - _0222E7C0 - 2 ; case 6
	.short _0222E80A - _0222E7C0 - 2 ; case 7
_0222E7D0:
	ldr r0, _0222E824 ; =SDK_OVERLAY_MODULE_52_ID
	ldr r1, _0222E828 ; =MOD52_021D76C8
	bl RegisterMainOverlay
	pop {r3, pc}
_0222E7DA:
	ldr r0, _0222E824 ; =SDK_OVERLAY_MODULE_52_ID
	ldr r1, _0222E82C ; =MOD52_021D76E8
	bl RegisterMainOverlay
	pop {r3, pc}
_0222E7E4:
	ldr r0, _0222E830 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _0222E834 ; =MOD83_0223A434
	bl RegisterMainOverlay
	pop {r3, pc}
_0222E7EE:
	ldr r0, _0222E830 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _0222E838 ; =MOD83_0223A4FC
	bl RegisterMainOverlay
	pop {r3, pc}
_0222E7F8:
	ldr r0, _0222E830 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _0222E83C ; =MOD83_0223A3A8
	bl RegisterMainOverlay
	pop {r3, pc}
_0222E802:
	ldr r0, _0222E840 ; =MOD83_0223A8C4
	bl FUN_020224D8
	pop {r3, pc}
_0222E80A:
	bl FUN_0200541C
	mov r0, #0
	ldr r1, _0222E844 ; =UNK_020FD6D4
	mvn r0, r0
	bl RegisterMainOverlay
	pop {r3, pc}
_0222E81A:
	ldr r0, _0222E848 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _0222E84C ; =MOD63_021DBAB8
	bl RegisterMainOverlay
_0222E822:
	pop {r3, pc}
	.align 2, 0
_0222E824: .word SDK_OVERLAY_MODULE_52_ID
_0222E828: .word MOD52_021D76C8
_0222E82C: .word MOD52_021D76E8
_0222E830: .word SDK_OVERLAY_MODULE_83_ID
_0222E834: .word MOD83_0223A434
_0222E838: .word MOD83_0223A4FC
_0222E83C: .word MOD83_0223A3A8
_0222E840: .word MOD83_0223A8C4
_0222E844: .word UNK_020FD6D4
_0222E848: .word SDK_OVERLAY_MODULE_63_ID
_0222E84C: .word MOD63_021DBAB8
	thumb_func_end MOD83_0222E7AC

	thumb_func_start MOD83_0222E850
MOD83_0222E850: ; 0x0222E850
	push {r4, lr}
	add r4, r0, #0
	bl OverlayManager_GetData
	bl MOD83_0222E7AC
	add r0, r4, #0
	bl OverlayManager_FreeData
	mov r0, #0x51
	bl DestroyHeap
	mov r0, #0
	bl MOD83_02239450
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_0222E850

	thumb_func_start MOD83_0222E874
MOD83_0222E874: ; 0x0222E874
	push {r3, r4}
	ldr r4, _0222E89C ; =MOD83_0223A8E0
	ldr r1, _0222E8A0 ; =0x00000123
	mov r3, #0
_0222E87C:
	ldrh r2, [r4, #2]
	cmp r0, r2
	bne _0222E88C
	ldr r0, _0222E89C ; =MOD83_0223A8E0
	lsl r1, r3, #2
	ldrh r0, [r0, r1]
	pop {r3, r4}
	bx lr
_0222E88C:
	add r3, r3, #1
	add r4, r4, #4
	cmp r3, r1
	blo _0222E87C
	mov r0, #0x3f
	pop {r3, r4}
	bx lr
	nop
_0222E89C: .word MOD83_0223A8E0
_0222E8A0: .word 0x00000123
	thumb_func_end MOD83_0222E874

	thumb_func_start MOD83_0222E8A4
MOD83_0222E8A4: ; 0x0222E8A4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r1, _0222E90C ; =0x00002710
	add r0, r4, #0
	bl _s32_div_f
	add r0, #0x30
	strh r0, [r5]
	ldr r1, _0222E90C ; =0x00002710
	add r0, r4, #0
	bl _s32_div_f
	add r4, r1, #0
	mov r1, #0xfa
	add r0, r4, #0
	lsl r1, r1, #2
	bl _s32_div_f
	add r0, #0x30
	mov r1, #0xfa
	strh r0, [r5, #2]
	add r0, r4, #0
	lsl r1, r1, #2
	bl _s32_div_f
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #0x64
	bl _s32_div_f
	add r0, #0x30
	strh r0, [r5, #4]
	add r0, r4, #0
	mov r1, #0x64
	bl _s32_div_f
	add r4, r1, #0
	add r0, r4, #0
	mov r1, #0xa
	bl _s32_div_f
	add r0, #0x30
	strh r0, [r5, #6]
	add r0, r4, #0
	mov r1, #0xa
	bl _s32_div_f
	add r4, r1, #0
	add r4, #0x30
	strh r4, [r5, #8]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222E90C: .word 0x00002710
	thumb_func_end MOD83_0222E8A4

	thumb_func_start MOD83_0222E910
MOD83_0222E910: ; 0x0222E910
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7, #0x10]
	bl PlayerProfile_GetNamePtr
	ldr r5, _0222E948 ; =MOD83_0223B860
	add r4, r0, #0
	mov r6, #0
_0222E920:
	ldrh r0, [r4]
	bl MOD83_0222E874
	strh r0, [r5]
	add r6, r6, #1
	add r4, r4, #2
	add r5, r5, #2
	cmp r6, #8
	blt _0222E920
	ldr r0, [r7, #0x10]
	bl PlayerProfile_GetTrainerID_VisibleHalf
	add r1, r0, #0
	ldr r0, _0222E94C ; =MOD83_0223B870
	bl MOD83_0222E8A4
	ldr r0, _0222E950 ; =MOD83_0223B860
	mov r1, #0
	strh r1, [r0, #0x1a]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222E948: .word MOD83_0223B860
_0222E94C: .word MOD83_0223B870
_0222E950: .word MOD83_0223B860
	thumb_func_end MOD83_0222E910

	thumb_func_start MOD83_0222E954
MOD83_0222E954: ; 0x0222E954
	push {r3, r4, r5, lr}
	sub sp, #0x48
	ldr r5, _0222EA80 ; =MOD83_0223A3C8
	add r4, r0, #0
	add r3, sp, #0x20
	mov r2, #5
_0222E960:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E960
	ldr r3, _0222EA84 ; =MOD83_0223A3B8
	add r2, sp, #0x10
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, sp, #0x20
	bl GX_SetBanks
	add r0, sp, #0x10
	bl FUN_02016BBC
	mov r1, #0
	str r1, [sp]
	mov r3, #0xf
	ldr r0, [r4, #4]
	mov r2, #1
	lsl r3, r3, #0xc
	bl MOD83_022387D8
	mov r0, #1
	lsl r0, r0, #0xe
	str r0, [sp]
	mov r1, #1
	mov r3, #0x3e
	ldr r0, [r4, #4]
	add r2, r1, #0
	lsl r3, r3, #0xa
	bl MOD83_022387D8
	mov r0, #0
	str r0, [sp]
	mov r3, #0x1e
	ldr r0, [r4, #4]
	mov r1, #4
	mov r2, #1
	lsl r3, r3, #0xa
	bl MOD83_022387D8
	mov r0, #1
	lsl r0, r0, #0xe
	str r0, [sp]
	mov r3, #7
	ldr r0, [r4, #4]
	mov r1, #5
	mov r2, #1
	lsl r3, r3, #0xc
	bl MOD83_022387D8
	bl FUN_0201BD5C
	mov r0, #0
	ldr r2, [r4]
	add r1, r0, #0
	bl FUN_02002ED0
	mov r1, #0
	str r1, [sp]
	ldr r0, [r4]
	mov r2, #1
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	add r3, r2, #0
	bl FUN_0200CB00
	ldr r0, [r4, #0x14]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4]
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [r4, #4]
	mov r2, #0xa
	mov r3, #2
	bl FUN_0200CD68
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r4]
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0x74
	add r3, r0, #0
	add r2, r1, #0
	add r3, #0x8c
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	mov r1, #1
	str r0, [sp, #4]
	str r1, [sp, #8]
	ldr r0, [r4]
	add r3, r1, #0
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x74
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	ldr r0, [r4]
	mov r1, #2
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x74
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r2, #0
	ldr r0, [r4, #4]
	mov r1, #1
	add r3, r2, #0
	bl FUN_020186B4
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_02017CD0
	add r0, r4, #0
	bl MOD83_0222EA88
	add sp, #0x48
	pop {r3, r4, r5, pc}
	nop
_0222EA80: .word MOD83_0223A3C8
_0222EA84: .word MOD83_0223A3B8
	thumb_func_end MOD83_0222E954

	thumb_func_start MOD83_0222EA88
MOD83_0222EA88: ; 0x0222EA88
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r4]
	mov r2, #4
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0
	add r3, #0xfc
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	ldr r0, [r4]
	mov r3, #4
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x74
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [r4]
	mov r1, #2
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x74
	mov r3, #4
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r2, #0
	ldr r0, [r4, #4]
	mov r1, #4
	add r3, r2, #0
	bl FUN_020186B4
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_02017CD0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_0222EA88

	thumb_func_start MOD83_0222EB04
MOD83_0222EB04: ; 0x0222EB04
	push {r3, r4, lr}
	sub sp, #0x5c
	add r4, r0, #0
	add r0, #0x18
	bl WindowIsInUse
	cmp r0, #0
	bne _0222EB4E
	mov r0, #1
	str r0, [sp]
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, sp, #8
	add r1, #0x18
	mov r2, #0
	mov r3, #0xc
	bl MOD83_022388E4
	mov r3, #0x51
	lsl r3, r3, #2
	ldr r3, [r4, r3]
	add r0, sp, #8
	mov r1, #0x16
	mov r2, #0x10
	bl MOD83_02238934
	mov r0, #2
	str r0, [sp]
	ldr r0, [r4, #4]
	add r1, sp, #8
	mov r2, #5
	mov r3, #4
	bl MOD83_02238A38
	add sp, #0x5c
	mov r0, #1
	pop {r3, r4, pc}
_0222EB4E:
	ldr r0, _0222EB78 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0222EB70
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	bl FUN_0200CCF8
	add r4, #0x18
	add r0, r4, #0
	bl RemoveWindow
	add sp, #0x5c
	mov r0, #0
	pop {r3, r4, pc}
_0222EB70:
	mov r0, #1
	add sp, #0x5c
	pop {r3, r4, pc}
	nop
_0222EB78: .word gMain
	thumb_func_end MOD83_0222EB04

	thumb_func_start MOD83_0222EB7C
MOD83_0222EB7C: ; 0x0222EB7C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0xa
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, #0
	ldr r3, _0222EC70 ; =0x00000172
	add r0, #0x48
	add r1, #0x28
	mov r2, #0
	bl MOD83_022388E4
	mov r3, #0x51
	lsl r3, r3, #2
	add r0, r4, #0
	ldr r3, [r4, r3]
	add r0, #0x48
	mov r1, #0x1b
	mov r2, #4
	bl MOD83_02238934
	add r0, r4, #0
	mov r1, #1
	add r0, #0x48
	add r2, r1, #0
	bl MOD83_0223893C
	mov r0, #0x46
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	add r0, r4, #0
	add r0, #0x48
	bl MOD83_02238AF4
	mov r3, #0x51
	lsl r3, r3, #2
	ldr r1, [r4, r3]
	mov r2, #0
	add r0, r1, r0
	str r0, [r4, r3]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x9c
	add r1, #0x18
	add r3, #0x2e
	bl MOD83_022388E4
	mov r3, #0x51
	lsl r3, r3, #2
	add r0, r4, #0
	ldr r3, [r4, r3]
	add r0, #0x9c
	mov r1, #0x1e
	mov r2, #4
	bl MOD83_02238934
	add r0, r4, #0
	add r0, #0x9c
	mov r1, #0
	mov r2, #1
	bl MOD83_0223893C
	mov r0, #0xb
	str r0, [sp]
	add r1, r4, #0
	mov r2, #1
	ldr r0, [r4, #4]
	add r1, #0x9c
	add r3, r2, #0
	bl MOD83_02238A38
	add r0, r4, #0
	add r0, #0x9c
	bl MOD83_02238AF4
	mov r1, #0x51
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	add r0, r2, r0
	str r0, [r4, r1]
	bl MOD83_02238AFC
	bl MOD83_02238B4C
	mov r0, #8
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0xa
	mov r2, #7
	mov r3, #9
	bl MOD83_02238BC4
	mov r0, #1
	str r0, [sp]
	ldr r1, _0222EC74 ; =0x00003170
	mov r0, #0
	ldr r1, [r4, r1]
	mov r2, #0x80
	mov r3, #0x4c
	bl MOD83_02238DBC
	ldr r1, _0222EC74 ; =0x00003170
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD83_0222EC78
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_0222EC70: .word 0x00000172
_0222EC74: .word 0x00003170
	thumb_func_end MOD83_0222EB7C

	thumb_func_start MOD83_0222EC78
MOD83_0222EC78: ; 0x0222EC78
	push {r3, r4, r5, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, [r5]
	bl ScrStrBufs_new
	add r4, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r5, #0
	ldr r3, _0222ED84 ; =0x00000172
	add r0, #0xf0
	add r1, #0x38
	mov r2, #0
	bl MOD83_022388E4
	mov r3, #0x51
	lsl r3, r3, #2
	add r0, r5, #0
	ldr r3, [r5, r3]
	add r0, #0xf0
	mov r1, #0x1a
	mov r2, #4
	bl MOD83_02238934
	add r0, r5, #0
	add r0, #0xf0
	mov r1, #0
	mov r2, #1
	bl MOD83_0223893C
	mov r0, #0x41
	lsl r0, r0, #2
	str r4, [r5, r0]
	ldr r2, [r5, #0x10]
	add r0, r4, #0
	mov r1, #0
	bl BufferPlayersName
	ldr r0, [r5, #0x10]
	bl PlayerProfile_GetTrainerID_VisibleHalf
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r1, #1
	add r0, r4, #0
	mov r3, #5
	str r1, [sp, #4]
	bl BufferIntegerAsString
	mov r0, #0x42
	str r0, [sp]
	add r1, r5, #0
	ldr r0, [r5, #4]
	add r1, #0xf0
	mov r2, #3
	mov r3, #0xd
	bl MOD83_02238A38
	add r1, r5, #0
	mov r0, #0
	add r1, #0xf8
	str r0, [r1]
	mov r1, #1
	bl GetFontAttribute
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0xf0
	mov r1, #0
	bl MOD83_02238944
	mov r2, #0x44
	str r2, [sp]
	add r1, r5, #0
	sub r2, #0x45
	ldr r0, [r5, #4]
	add r1, #0xf0
	add r3, r2, #0
	bl MOD83_02238A38
	add r0, sp, #0x10
	bl OS_GetMacAddress
	add r0, sp, #0x10
	bl MOD83_02234704
	add r1, sp, #0x1c
	add r2, sp, #0x18
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	bl MOD83_02234748
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	mov r0, #2
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [sp, #0x18]
	add r0, r4, #0
	mov r3, #4
	bl BufferIntegerAsString
	add r0, r5, #0
	mov r1, #1
	add r0, #0xfc
	str r1, [r0]
	mov r2, #0x45
	str r2, [sp]
	ldr r0, [r5, #4]
	add r5, #0xf0
	sub r2, #0x46
	add r1, r5, #0
	add r3, r2, #0
	bl MOD83_02238A38
	add r0, r4, #0
	bl ScrStrBufs_delete
	add sp, #0x20
	pop {r3, r4, r5, pc}
	nop
_0222ED84: .word 0x00000172
	thumb_func_end MOD83_0222EC78

	thumb_func_start MOD83_0222ED88
MOD83_0222ED88: ; 0x0222ED88
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD83_02238E48
	add r0, r4, #0
	add r0, #0x18
	bl WindowIsInUse
	cmp r0, #1
	bne _0222EDD0
	add r0, r4, #0
	add r0, #0x18
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x18
	bl RemoveWindow
	add r0, r4, #0
	add r0, #0x28
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x28
	bl RemoveWindow
	add r0, r4, #0
	add r0, #0x38
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0x38
	bl RemoveWindow
_0222EDD0:
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #4]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD83_0222ED88

	thumb_func_start MOD83_0222EDF8
MOD83_0222EDF8: ; 0x0222EDF8
	push {r3, r4, r5, lr}
	mov r3, #2
	ldr r2, _0222EE80 ; =0x000034DC
	mov r1, #0x55
	lsl r3, r3, #0x10
	add r5, r0, #0
	bl MOD83_022387A0
	add r4, r0, #0
	mov r0, #0x55
	str r0, [r4]
	bl FUN_02016B94
	str r0, [r4, #4]
	add r0, r5, #0
	bl OverlayManager_GetField18
	ldr r0, [r0, #8]
	str r0, [r4, #8]
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r4, #0x10]
	ldr r0, [r4, #8]
	bl Sav2_Pokedex_get
	str r0, [r4, #0xc]
	ldr r0, [r4, #8]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0x14]
	ldr r0, [r4]
	bl MOD83_02238770
	ldr r0, [r4, #8]
	bl FUN_0202251C
	ldr r1, _0222EE84 ; =0x00003174
	mov r2, #0x53
	str r0, [r4, r1]
	mov r0, #9
	lsl r2, r2, #2
	str r0, [r4, r2]
	add r0, r2, #0
	mov r1, #0x28
	sub r0, #8
	str r1, [r4, r0]
	add r1, r2, #0
	mov r0, #0
	add r1, #8
	str r0, [r4, r1]
	add r1, r2, #0
	add r1, #0x10
	str r0, [r4, r1]
	add r2, #0xc
	str r0, [r4, r2]
	mov r2, #3
	mov r1, #0x5b
	lsl r2, r2, #8
	bl CreateHeap
	ldr r1, _0222EE88 ; =0x00000496
	mov r0, #9
	mov r2, #1
	bl FUN_0200433C
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0222EE80: .word 0x000034DC
_0222EE84: .word 0x00003174
_0222EE88: .word 0x00000496
	thumb_func_end MOD83_0222EDF8

	thumb_func_start MOD83_0222EE8C
MOD83_0222EE8C: ; 0x0222EE8C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	add r6, r0, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0xd
	bhi _0222EEF2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0222EEAC: ; jump table
	.short _0222EEC8 - _0222EEAC - 2 ; case 0
	.short _0222EEEA - _0222EEAC - 2 ; case 1
	.short _0222EF08 - _0222EEAC - 2 ; case 2
	.short _0222EF5A - _0222EEAC - 2 ; case 3
	.short _0222EF86 - _0222EEAC - 2 ; case 4
	.short _0222EFC2 - _0222EEAC - 2 ; case 5
	.short _0222EFFC - _0222EEAC - 2 ; case 6
	.short _0222F02C - _0222EEAC - 2 ; case 7
	.short _0222F02C - _0222EEAC - 2 ; case 8
	.short _0222F02C - _0222EEAC - 2 ; case 9
	.short _0222F02C - _0222EEAC - 2 ; case 10
	.short _0222F012 - _0222EEAC - 2 ; case 11
	.short _0222F01A - _0222EEAC - 2 ; case 12
	.short _0222F026 - _0222EEAC - 2 ; case 13
_0222EEC8:
	bl MOD83_0222E954
	ldr r0, [r4, #0xc]
	bl Pokedex_GetSinnohDexFlag
	cmp r0, #0
	bne _0222EEE4
	mov r0, #1
	add r1, r0, #0
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EEE4:
	mov r0, #2
	str r0, [r5]
	b _0222F02C
_0222EEEA:
	bl MOD83_0222EB04
	cmp r0, #0
	beq _0222EEF4
_0222EEF2:
	b _0222F02C
_0222EEF4:
	mov r0, #1
	bl MOD83_02238860
	mov r0, #0
	mov r1, #0xc
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EF08:
	bl MOD83_0222EB7C
	ldr r0, _0222F038 ; =0x00003174
	ldr r0, [r4, r0]
	bl FUN_0202ADF0
	cmp r0, #0
	bne _0222EF44
	add r0, r4, #0
	mov r1, #1
	add r0, #0x98
	str r1, [r0]
	mov r0, #0x15
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	ldr r1, _0222F03C ; =0x0000317C
	add r2, r5, #0
	str r0, [r4, r1]
	mov r0, #1
	mov r1, #3
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EF44:
	mov r0, #0x53
	mov r1, #7
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	mov r1, #4
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EF5A:
	ldr r0, _0222F03C ; =0x0000317C
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222F02C
	ldr r0, _0222F040 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r1, r0
	beq _0222F02C
	bl MOD83_02238860
	mov r0, #0
	mov r1, #0xc
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EF86:
	bl MOD83_0222F210
	mov r1, #0x15
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #5
	bne _0222EFAA
	mov r0, #1
	bl MOD83_02238860
	mov r0, #0
	mov r1, #0xc
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EFAA:
	cmp r0, #4
	bne _0222F02C
	mov r0, #1
	bl MOD83_02238860
	mov r0, #0
	mov r1, #0xc
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222EFC2:
	bl MOD83_0222EA88
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r1, #0xc6
	lsl r1, r1, #6
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0x55
	bl MOD83_02233168
	mov r0, #1
	mov r1, #6
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	ldr r1, _0222F044 ; =0x000032D2
	mov r0, #4
	ldrb r2, [r4, r1]
	bic r2, r0
	strb r2, [r4, r1]
	b _0222F02C
_0222EFFC:
	ldr r0, _0222F040 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _0222F02C
	mov r0, #0
	mov r1, #0xb
	add r2, r5, #0
	mov r3, #0xd
	bl MOD83_0223886C
	b _0222F02C
_0222F012:
	mov r0, #0
	bl OS_ResetSystem
	b _0222F02C
_0222F01A:
	add r0, r6, #0
	bl MOD83_0222ED88
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0222F026:
	add r0, r5, #0
	bl MOD83_022388CC
_0222F02C:
	bl MOD83_02238D58
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0222F038: .word 0x00003174
_0222F03C: .word 0x0000317C
_0222F040: .word gMain
_0222F044: .word 0x000032D2
	thumb_func_end MOD83_0222EE8C

	thumb_func_start MOD83_0222F048
MOD83_0222F048: ; 0x0222F048
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x5b
	bl DestroyHeap
	ldr r0, _0222F06C ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _0222F070 ; =MOD63_021DBAB8
	bl RegisterMainOverlay
	add r0, r4, #0
	bl OverlayManager_FreeData
	mov r0, #0x55
	bl DestroyHeap
	mov r0, #1
	pop {r4, pc}
	nop
_0222F06C: .word SDK_OVERLAY_MODULE_63_ID
_0222F070: .word MOD63_021DBAB8
	thumb_func_end MOD83_0222F048

	thumb_func_start MOD83_0222F074
MOD83_0222F074: ; 0x0222F074
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0xc6
	lsl r0, r0, #6
	add r4, r5, r0
	mov r2, #0xd6
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	ldr r2, _0222F1A0 ; =0x00000172
	ldr r3, [r5]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r6, r0, #0
	ldr r0, [r5]
	bl ScrStrBufs_new
	mov r1, #0xc6
	mov r2, #7
	lsl r1, r1, #6
	strh r2, [r5, r1]
	ldr r3, [r5]
	add r1, r6, #0
	mov r2, #0x4c
	str r0, [sp]
	bl ReadMsgData_ExpandPlaceholders
	mov r1, #0x41
	lsl r1, r1, #2
	add r7, r0, #0
	add r1, r4, r1
	mov r2, #0x24
	bl CopyStringToU16Array
	add r0, r7, #0
	bl String_dtor
	mov r0, #0xc
	bl MOD83_02238EF4
	add r7, r0, #0
	mov r0, #0xa
	bl MOD83_02238EF4
	str r0, [sp, #4]
	mov r0, #0xb
	bl MOD83_02238EF4
	ldr r1, [sp, #4]
	mov r2, #1
	orr r0, r1
	add r1, r7, #0
	orr r1, r0
	mov r0, #0x53
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r1, r0, #4
	strh r2, [r4, r1]
	add r1, r0, #6
	ldrb r2, [r4, r1]
	mov r1, #1
	bic r2, r1
	add r1, r0, #6
	strb r2, [r4, r1]
	ldrb r2, [r4, r1]
	mov r1, #2
	bic r2, r1
	add r1, r0, #6
	strb r2, [r4, r1]
	ldrb r2, [r4, r1]
	mov r1, #4
	orr r2, r1
	add r1, r0, #6
	strb r2, [r4, r1]
	ldrb r2, [r4, r1]
	mov r1, #8
	orr r2, r1
	add r1, r0, #6
	strb r2, [r4, r1]
	ldrb r2, [r4, r1]
	mov r1, #0x20
	add r0, r0, #6
	bic r2, r1
	strb r2, [r4, r0]
	ldr r0, [sp]
	ldr r3, [r5]
	add r1, r6, #0
	mov r2, #0x4b
	bl ReadMsgData_ExpandPlaceholders
	add r7, r0, #0
	mov r1, #0x55
	lsl r1, r1, #2
	add r1, r4, r1
	mov r2, #0xfa
	bl CopyStringToU16Array
	add r0, r7, #0
	bl String_dtor
	mov r0, #0xd2
	lsl r0, r0, #2
	mov r1, #0
	ldr r3, _0222F1A4 ; =0x000001EA
	strb r1, [r4, r0]
	add r2, r0, #2
	strh r3, [r4, r2]
	add r2, r0, #4
	strh r1, [r4, r2]
	add r2, r0, #6
	strh r1, [r4, r2]
	add r0, #8
	strb r1, [r4, r0]
	add r0, sp, #8
	bl GF_RTC_CopyDate
	add r0, sp, #8
	bl RTC_ConvertDateToDay
	mov r1, #0xd5
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp]
	bl ScrStrBufs_delete
	add r0, r6, #0
	bl DestroyMsgData
	ldr r0, _0222F1A8 ; =0x00003174
	add r1, r4, #0
	ldr r0, [r5, r0]
	mov r2, #0
	bl FUN_0202AC98
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl MOD83_022391EC
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F1A0: .word 0x00000172
_0222F1A4: .word 0x000001EA
_0222F1A8: .word 0x00003174
	thumb_func_end MOD83_0222F074

	thumb_func_start MOD83_0222F1AC
MOD83_0222F1AC: ; 0x0222F1AC
	mov r2, #0x16
	lsl r2, r2, #4
	str r1, [r0, r2]
	bx lr
	thumb_func_end MOD83_0222F1AC

	thumb_func_start MOD83_0222F1B4
MOD83_0222F1B4: ; 0x0222F1B4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x16
	lsl r1, r1, #4
	add r4, r3, #0
	ldr r3, [r0, r1]
	sub r3, r3, #1
	str r3, [r0, r1]
	ldr r0, [r0, r1]
	cmp r0, #0
	bne _0222F1D6
	bl MOD83_02234518
	mov r0, #0x17
	str r0, [r5]
	mov r0, #0
	pop {r3, r4, r5, pc}
_0222F1D6:
	cmp r2, #0
	beq _0222F1EE
	bl MOD83_022344E4
	cmp r0, #0
	bne _0222F1EE
	bl MOD83_02234518
	mov r0, #0x16
	str r0, [r5]
	mov r0, #0
	pop {r3, r4, r5, pc}
_0222F1EE:
	cmp r4, #0
	beq _0222F206
	ldr r0, _0222F20C ; =gMain
	ldr r0, [r0, #0x48]
	tst r0, r4
	beq _0222F206
	bl MOD83_02234518
	mov r0, #0x1a
	str r0, [r5]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222F206:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222F20C: .word gMain
	thumb_func_end MOD83_0222F1B4

	thumb_func_start MOD83_0222F210
MOD83_0222F210: ; 0x0222F210
	push {r3, r4, r5, lr}
	mov r5, #0x57
	lsl r5, r5, #2
	add r4, r0, #0
	sub r0, r5, #4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222F236
	bl MOD83_0223438C
	mov r1, #3
	sub r0, r1, r0
	bl FUN_02033EEC
	bl MOD83_02234238
	mov r0, #1
	bl MOD83_022345C8
_0222F236:
	ldr r0, [r4, r5]
	cmp r0, #0x1e
	bls _0222F23E
	b _0222F736
_0222F23E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222F24A: ; jump table
	.short _0222F288 - _0222F24A - 2 ; case 0
	.short _0222F29E - _0222F24A - 2 ; case 1
	.short _0222F2C4 - _0222F24A - 2 ; case 2
	.short _0222F2E6 - _0222F24A - 2 ; case 3
	.short _0222F310 - _0222F24A - 2 ; case 4
	.short _0222F736 - _0222F24A - 2 ; case 5
	.short _0222F736 - _0222F24A - 2 ; case 6
	.short _0222F342 - _0222F24A - 2 ; case 7
	.short _0222F3B8 - _0222F24A - 2 ; case 8
	.short _0222F3D6 - _0222F24A - 2 ; case 9
	.short _0222F420 - _0222F24A - 2 ; case 10
	.short _0222F45C - _0222F24A - 2 ; case 11
	.short _0222F476 - _0222F24A - 2 ; case 12
	.short _0222F4AA - _0222F24A - 2 ; case 13
	.short _0222F4EC - _0222F24A - 2 ; case 14
	.short _0222F50C - _0222F24A - 2 ; case 15
	.short _0222F524 - _0222F24A - 2 ; case 16
	.short _0222F53E - _0222F24A - 2 ; case 17
	.short _0222F594 - _0222F24A - 2 ; case 18
	.short _0222F61C - _0222F24A - 2 ; case 19
	.short _0222F664 - _0222F24A - 2 ; case 20
	.short _0222F736 - _0222F24A - 2 ; case 21
	.short _0222F698 - _0222F24A - 2 ; case 22
	.short _0222F69C - _0222F24A - 2 ; case 23
	.short _0222F736 - _0222F24A - 2 ; case 24
	.short _0222F736 - _0222F24A - 2 ; case 25
	.short _0222F704 - _0222F24A - 2 ; case 26
	.short _0222F736 - _0222F24A - 2 ; case 27
	.short _0222F6D0 - _0222F24A - 2 ; case 28
	.short _0222F35E - _0222F24A - 2 ; case 29
	.short _0222F39C - _0222F24A - 2 ; case 30
_0222F288:
	add r0, r4, #0
	bl MOD83_0222E910
	bl FUN_0202E49C
	mov r0, #0x52
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	str r1, [r4, r5]
	b _0222F736
_0222F29E:
	bl FUN_0202E4C8
	cmp r0, #0
	beq _0222F356
	mov r1, #0x5b
	lsl r1, r1, #2
	ldr r0, _0222F5E0 ; =MOD83_0223A8D4
	add r1, r4, r1
	bl MOD83_02233F94
	mov r0, #0x56
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	bl FUN_02033E74
	mov r0, #2
	str r0, [r4, r5]
	b _0222F736
_0222F2C4:
	bl MOD83_0223427C
	mov r1, #0x19
	add r0, r4, #0
	lsl r1, r1, #6
	bl MOD83_0222F1AC
	add r0, r4, #0
	add r0, #0x28
	mov r1, #0xa
	bl FUN_0200D858
	ldr r1, _0222F5E4 ; =0x000034D8
	str r0, [r4, r1]
	mov r0, #3
	str r0, [r4, r5]
	b _0222F736
_0222F2E6:
	bl MOD83_022343A4
	cmp r0, #0
	beq _0222F302
	sub r1, r0, #1
	mov r0, #0x59
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r1, _0222F5E8 ; =0x00000708
	add r0, r4, #0
	bl MOD83_0222F1AC
	mov r0, #4
	str r0, [r4, r5]
_0222F302:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #0
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F310:
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD83_022342C8
	cmp r0, #0
	beq _0222F334
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD83_02234304
	mov r0, #7
	str r0, [r4, r5]
	mov r0, #0x16
	ldr r1, _0222F5E8 ; =0x00000708
	lsl r0, r0, #4
	str r1, [r4, r0]
_0222F334:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #0
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F342:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #0
	mov r3, #2
	bl MOD83_0222F1B4
	bl MOD83_022344E4
	cmp r0, #0
	bne _0222F358
_0222F356:
	b _0222F736
_0222F358:
	mov r0, #0x1d
	str r0, [r4, r5]
	b _0222F736
_0222F35E:
	mov r0, #0x1e
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	ldr r0, _0222F5EC ; =0x00003170
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0222F5E4 ; =0x000034D8
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	ldr r0, _0222F5E4 ; =0x000034D8
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, _0222F5F0 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x16
	ldr r1, _0222F5E8 ; =0x00000708
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0x1e
	str r0, [r4, r5]
	b _0222F736
_0222F39C:
	ldr r0, _0222F5F4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0222F3AA
	mov r0, #8
	str r0, [r4, r5]
_0222F3AA:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #1
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F3B8:
	bl MOD83_022343C4
	mov r0, #9
	str r0, [r4, r5]
	mov r0, #0x16
	ldr r1, _0222F5E8 ; =0x00000708
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #1
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F3D6:
	bl MOD83_02234450
	cmp r0, #0
	beq _0222F412
	bl MOD83_022343F8
	mov r0, #0xa
	str r0, [r4, r5]
	mov r1, #0x32
	mov r0, #0x16
	lsl r1, r1, #6
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0x22
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	ldr r0, _0222F5F0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0222F5E4 ; =0x000034D8
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222F412:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #1
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F420:
	bl MOD83_02234450
	cmp r0, #0
	beq _0222F44E
	mov r0, #0x47
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	ldr r0, _0222F5EC ; =0x00003170
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	add r0, r4, #0
	bl MOD83_0222EC78
	mov r0, #0xb
	str r0, [r4, r5]
_0222F44E:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #1
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F45C:
	ldr r0, _0222F5F8 ; =MOD83_0223AD6C
	mov r1, #0x2a
	mov r2, #1
	bl MOD83_02234424
	mov r0, #0xc
	str r0, [r4, r5]
	mov r1, #0x32
	mov r0, #0x16
	lsl r1, r1, #6
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _0222F736
_0222F476:
	bl MOD83_0223447C
	cmp r0, #0
	beq _0222F49C
	mov r0, #0xd
	str r0, [r4, r5]
	mov r0, #0x16
	mov r1, #0x3c
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0x47
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
_0222F49C:
	add r0, r4, #0
	add r1, r4, r5
	mov r2, #1
	mov r3, #2
	bl MOD83_0222F1B4
	b _0222F736
_0222F4AA:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222F51C
	mov r0, #0x48
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	add r0, r4, #0
	add r0, #0x28
	mov r1, #0xa
	bl FUN_0200D858
	ldr r1, _0222F5E4 ; =0x000034D8
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD83_0222F074
	ldr r0, [r4, #8]
	bl MOD83_022394BC
	mov r0, #0xe
	str r0, [r4, r5]
	b _0222F736
_0222F4EC:
	bl MOD83_022394CC
	cmp r0, #1
	bne _0222F51C
	mov r0, #0xf
	str r0, [r4, r5]
	bl OS_GetTickLo
	mov r1, #0x36
	bl _s32_div_f
	mov r0, #0x16
	add r1, r1, #6
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _0222F736
_0222F50C:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222F51E
_0222F51C:
	b _0222F736
_0222F51E:
	mov r0, #0x10
	str r0, [r4, r5]
	b _0222F736
_0222F524:
	ldr r0, _0222F5F8 ; =MOD83_0223AD6C
	mov r1, #0x2a
	mov r2, #2
	bl MOD83_02234424
	mov r0, #0x11
	str r0, [r4, r5]
	mov r1, #0x4b
	mov r0, #0x16
	lsl r1, r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _0222F736
_0222F53E:
	bl MOD83_022344A8
	cmp r0, #0
	beq _0222F55A
	bl MOD83_02239544
	mov r0, #0x12
	str r0, [r4, r5]
	mov r1, #0x32
	mov r0, #0x16
	lsl r1, r1, #4
	lsl r0, r0, #4
	str r1, [r4, r0]
	b _0222F736
_0222F55A:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222F57A
	bl MOD83_02234518
	mov r0, #0x17
	mov r1, #0x78
	str r0, [r4, r5]
	add r0, r1, #0
	add r0, #0xe8
	str r1, [r4, r0]
_0222F57A:
	bl MOD83_022344E4
	cmp r0, #0
	bne _0222F62C
	bl MOD83_02234518
	mov r0, #0x16
	mov r1, #0x78
	str r0, [r4, r5]
	add r0, r1, #0
	add r0, #0xe8
	str r1, [r4, r0]
	b _0222F736
_0222F594:
	bl MOD83_02239574
	cmp r0, #3
	bne _0222F5AE
	bl MOD83_02234518
	mov r0, #0x16
	mov r1, #0x78
	str r0, [r4, r5]
	add r0, r1, #0
	add r0, #0xe8
	str r1, [r4, r0]
	b _0222F5FC
_0222F5AE:
	bl MOD83_02239574
	cmp r0, #2
	beq _0222F5BC
	bl MOD83_022394CC
	b _0222F5FC
_0222F5BC:
	bl MOD83_0223447C
	cmp r0, #0
	bne _0222F5CC
	bl MOD83_022344E4
	cmp r0, #0
	bne _0222F5FC
_0222F5CC:
	mov r0, #0x13
	str r0, [r4, r5]
	mov r0, #0x16
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	bl MOD83_02234518
	b _0222F736
	nop
_0222F5E0: .word MOD83_0223A8D4
_0222F5E4: .word 0x000034D8
_0222F5E8: .word 0x00000708
_0222F5EC: .word 0x00003170
_0222F5F0: .word 0x000005DC
_0222F5F4: .word gMain
_0222F5F8: .word MOD83_0223AD6C
_0222F5FC:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222F61C
	bl MOD83_02234518
	mov r0, #0x17
	str r0, [r4, r5]
	mov r0, #0x16
	mov r1, #0xa
	lsl r0, r0, #4
	str r1, [r4, r0]
_0222F61C:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222F62E
_0222F62C:
	b _0222F736
_0222F62E:
	mov r0, #0x14
	str r0, [r4, r5]
	mov r0, #0x49
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	ldr r0, _0222F73C ; =0x00003170
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0222F740 ; =0x000034D8
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	ldr r0, _0222F744 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0222F740 ; =0x000034D8
	mov r1, #0
	str r1, [r4, r0]
	b _0222F736
_0222F664:
	bl MOD83_02234558
	cmp r0, #0
	beq _0222F736
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222F686
	bl FUN_0202E4F0
	bl FUN_02033ED0
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_0222F686:
	ldr r0, _0222F748 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0222F736
	mov r0, #0x1b
	str r0, [r4, r5]
	mov r0, #4
	pop {r3, r4, r5, pc}
_0222F698:
	mov r0, #0x17
	str r0, [r4, r5]
_0222F69C:
	mov r0, #0x4a
	str r0, [sp]
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x48
	mov r2, #2
	mov r3, #0x13
	bl MOD83_02238A38
	ldr r0, _0222F73C ; =0x00003170
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	ldr r0, _0222F740 ; =0x000034D8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222F6C4
	bl FUN_0200DBFC
_0222F6C4:
	ldr r0, _0222F740 ; =0x000034D8
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #0x1c
	str r0, [r4, r5]
	b _0222F736
_0222F6D0:
	bl MOD83_02234558
	cmp r0, #0
	beq _0222F736
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222F6F2
	bl FUN_0202E4F0
	bl FUN_02033ED0
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_0222F6F2:
	ldr r0, _0222F748 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0222F736
	mov r0, #0
	bl OS_ResetSystem
	b _0222F736
_0222F704:
	bl MOD83_02234558
	cmp r0, #0
	beq _0222F736
	mov r0, #0x52
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222F736
	bl FUN_0202E4F0
	bl FUN_02033ED0
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _0222F740 ; =0x000034D8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222F732
	bl FUN_0200DBFC
_0222F732:
	mov r0, #5
	pop {r3, r4, r5, pc}
_0222F736:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0222F73C: .word 0x00003170
_0222F740: .word 0x000034D8
_0222F744: .word 0x000005DC
_0222F748: .word gMain
	thumb_func_end MOD83_0222F210

	thumb_func_start MOD83_0222F74C
MOD83_0222F74C: ; 0x0222F74C
	push {r4, lr}
	ldr r1, _0222F79C ; =MOD83_0223B884
	add r4, r0, #0
	ldr r1, [r1]
	cmp r1, #0
	bne _0222F798
	bl MOD83_0222F9F8
	mov r1, #0xf5
	mov r0, #0xf
	lsl r1, r1, #2
	bl AllocFromHeap
	ldr r1, _0222F79C ; =MOD83_0223B884
	mov r2, #0xf5
	str r0, [r1]
	mov r1, #0
	lsl r2, r2, #2
	bl MI_CpuFill8
	ldr r0, _0222F79C ; =MOD83_0223B884
	mov r1, #0x32
	ldr r0, [r0]
	mov r2, #0xa
	strh r1, [r0, #0x24]
	ldr r0, _0222F7A0 ; =MOD83_0222F89C
	mov r1, #0
	bl FUN_0200CA44
	ldr r1, _0222F79C ; =MOD83_0223B884
	ldr r2, [r1]
	str r0, [r2, #0x1c]
	ldr r0, [r1]
	str r4, [r0]
	ldr r0, [r1]
	add r0, r0, #4
	bl FUN_020312BC
_0222F798:
	pop {r4, pc}
	nop
_0222F79C: .word MOD83_0223B884
_0222F7A0: .word MOD83_0222F89C
	thumb_func_end MOD83_0222F74C

	thumb_func_start MOD83_0222F7A4
MOD83_0222F7A4: ; 0x0222F7A4
	ldr r2, _0222F7B0 ; =MOD83_0223B884
	ldr r3, [r2]
	str r0, [r3, #0x20]
	ldr r0, [r2]
	strh r1, [r0, #0x24]
	bx lr
	.align 2, 0
_0222F7B0: .word MOD83_0223B884
	thumb_func_end MOD83_0222F7A4

	thumb_func_start MOD83_0222F7B4
MOD83_0222F7B4: ; 0x0222F7B4
	push {r4, lr}
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0
	beq _0222F7E2
	mov r4, #0
	ldr r1, _0222F7E4 ; =MOD83_0223B884
	ldr r0, _0222F7E8 ; =0x000003C1
	add r3, r4, #0
_0222F7CA:
	ldr r2, [r1]
	add r2, r2, r4
	add r4, r4, #1
	strb r3, [r2, r0]
	cmp r4, #0x10
	blt _0222F7CA
	bl FUN_0202DBE0
	ldr r0, _0222F7EC ; =MOD83_0222F7F0
	mov r1, #0
	bl MOD83_0222F7A4
_0222F7E2:
	pop {r4, pc}
	.align 2, 0
_0222F7E4: .word MOD83_0223B884
_0222F7E8: .word 0x000003C1
_0222F7EC: .word MOD83_0222F7F0
	thumb_func_end MOD83_0222F7B4

	thumb_func_start MOD83_0222F7F0
MOD83_0222F7F0: ; 0x0222F7F0
	push {r4, r5, r6, lr}
	mov r4, #0
	ldr r6, _0222F824 ; =MOD83_0223B884
	add r5, r4, #0
_0222F7F8:
	ldr r0, [r6]
	add r0, r0, r5
	ldr r0, [r0, #0x28]
	cmp r0, #0
	bne _0222F81A
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #1
	bne _0222F81A
	add r0, r4, #0
	bl FUN_0202DFA4
	ldr r1, [r6]
	add r1, r1, r5
	str r0, [r1, #0x28]
_0222F81A:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x10
	blt _0222F7F8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222F824: .word MOD83_0223B884
	thumb_func_end MOD83_0222F7F0

	thumb_func_start MOD83_0222F828
MOD83_0222F828: ; 0x0222F828
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0
	beq _0222F83A
	ldr r0, _0222F83C ; =MOD83_0222F840
	mov r1, #0
	bl MOD83_0222F7A4
_0222F83A:
	pop {r3, pc}
	.align 2, 0
_0222F83C: .word MOD83_0222F840
	thumb_func_end MOD83_0222F828

	thumb_func_start MOD83_0222F840
MOD83_0222F840: ; 0x0222F840
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0222F840

	thumb_func_start MOD83_0222F844
MOD83_0222F844: ; 0x0222F844
	push {r3, lr}
	ldr r0, _0222F85C ; =MOD83_0223B884
	ldr r0, [r0]
	add r0, #0x27
	ldrb r0, [r0]
	bl FUN_020319D8
	ldr r0, _0222F860 ; =MOD83_0222F864
	mov r1, #0
	bl MOD83_0222F7A4
	pop {r3, pc}
	.align 2, 0
_0222F85C: .word MOD83_0223B884
_0222F860: .word MOD83_0222F864
	thumb_func_end MOD83_0222F844

	thumb_func_start MOD83_0222F864
MOD83_0222F864: ; 0x0222F864
	push {r3, lr}
	bl FUN_02031A2C
	cmp r0, #0
	beq _0222F88C
	ldr r0, _0222F890 ; =MOD83_0223B884
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0xf
	lsl r0, r0, #6
	strb r2, [r1, r0]
	bl FUN_0202DBE0
	mov r0, #0xab
	bl FUN_02031588
	ldr r0, _0222F894 ; =MOD83_0222F898
	mov r1, #0
	bl MOD83_0222F7A4
_0222F88C:
	pop {r3, pc}
	nop
_0222F890: .word MOD83_0223B884
_0222F894: .word MOD83_0222F898
	thumb_func_end MOD83_0222F864

	thumb_func_start MOD83_0222F898
MOD83_0222F898: ; 0x0222F898
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0222F898

	thumb_func_start MOD83_0222F89C
MOD83_0222F89C: ; 0x0222F89C
	push {r3, lr}
	ldr r1, _0222F8C0 ; =MOD83_0223B884
	ldr r2, [r1]
	cmp r2, #0
	bne _0222F8AC
	bl FUN_0200CAB4
	pop {r3, pc}
_0222F8AC:
	ldr r1, [r2, #0x20]
	cmp r1, #0
	beq _0222F8BC
	add r2, #0x26
	ldrb r0, [r2]
	cmp r0, #0
	bne _0222F8BC
	blx r1
_0222F8BC:
	pop {r3, pc}
	nop
_0222F8C0: .word MOD83_0223B884
	thumb_func_end MOD83_0222F89C

	thumb_func_start MOD83_0222F8C4
MOD83_0222F8C4: ; 0x0222F8C4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl FUN_02030F40
	cmp r0, #0
	bne _0222F8EA
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_02031C74
	add r0, r5, #0
	bl MOD83_0222F74C
	ldr r0, _0222F8EC ; =MOD83_0222F7B4
	mov r1, #0
	bl MOD83_0222F7A4
_0222F8EA:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222F8EC: .word MOD83_0222F7B4
	thumb_func_end MOD83_0222F8C4

	thumb_func_start MOD83_0222F8F0
MOD83_0222F8F0: ; 0x0222F8F0
	add r3, r0, #0
	add r2, r1, #0
	add r1, r3, #0
	ldr r3, _0222F8FC ; =FUN_02030B3C
	mov r0, #0x16
	bx r3
	.align 2, 0
_0222F8FC: .word FUN_02030B3C
	thumb_func_end MOD83_0222F8F0

	thumb_func_start MOD83_0222F900
MOD83_0222F900: ; 0x0222F900
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02030F40
	cmp r0, #0
	bne _0222F92C
	bl MOD83_02231364
	bl OverlayManager_GetField18
	ldr r0, [r0, #8]
	add r1, r4, #0
	bl FUN_02031CA8
	add r0, r5, #0
	bl MOD83_0222F74C
	ldr r0, _0222F930 ; =MOD83_0222F828
	mov r1, #0
	bl MOD83_0222F7A4
_0222F92C:
	pop {r3, r4, r5, pc}
	nop
_0222F930: .word MOD83_0222F828
	thumb_func_end MOD83_0222F900

	thumb_func_start MOD83_0222F934
MOD83_0222F934: ; 0x0222F934
	ldr r1, _0222F944 ; =MOD83_0223B884
	ldr r3, _0222F948 ; =MOD83_0222F7A4
	ldr r1, [r1]
	add r1, #0x27
	strb r0, [r1]
	ldr r0, _0222F94C ; =MOD83_0222F844
	mov r1, #0
	bx r3
	.align 2, 0
_0222F944: .word MOD83_0223B884
_0222F948: .word MOD83_0222F7A4
_0222F94C: .word MOD83_0222F844
	thumb_func_end MOD83_0222F934

	thumb_func_start MOD83_0222F950
MOD83_0222F950: ; 0x0222F950
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_0222F956:
	add r0, r4, #0
	bl FUN_0202F124
	add r1, r0, #0
	beq _0222F976
	add r0, #0x4c
	ldrh r0, [r0]
	cmp r0, #0
	beq _0222F976
	add r5, #0x8c
	add r0, r5, #0
	mov r2, #0x50
	bl memcpy
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_0222F976:
	add r4, r4, #1
	cmp r4, #0x10
	blt _0222F956
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD83_0222F950

	thumb_func_start MOD83_0222F984
MOD83_0222F984: ; 0x0222F984
	ldr r1, _0222F99C ; =MOD83_0223B884
	ldr r2, [r1]
	add r1, r2, #0
	add r1, #0x27
	ldrb r1, [r1]
	cmp r1, r0
	bne _0222F99A
	mov r0, #0xf
	mov r1, #1
	lsl r0, r0, #6
	strb r1, [r2, r0]
_0222F99A:
	bx lr
	.align 2, 0
_0222F99C: .word MOD83_0223B884
	thumb_func_end MOD83_0222F984

	thumb_func_start MOD83_0222F9A0
MOD83_0222F9A0: ; 0x0222F9A0
	ldr r0, _0222F9AC ; =MOD83_0223B884
	ldr r1, [r0]
	mov r0, #0xf
	lsl r0, r0, #6
	ldrb r0, [r1, r0]
	bx lr
	.align 2, 0
_0222F9AC: .word MOD83_0223B884
	thumb_func_end MOD83_0222F9A0

	thumb_func_start MOD83_0222F9B0
MOD83_0222F9B0: ; 0x0222F9B0
	mov r0, #0xd6
	lsl r0, r0, #2
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0222F9B0

	thumb_func_start MOD83_0222F9B8
MOD83_0222F9B8: ; 0x0222F9B8
	ldr r0, _0222F9C0 ; =MOD83_0223B884
	ldr r0, [r0]
	add r0, #0x68
	bx lr
	.align 2, 0
_0222F9C0: .word MOD83_0223B884
	thumb_func_end MOD83_0222F9B8

	thumb_func_start MOD83_0222F9C4
MOD83_0222F9C4: ; 0x0222F9C4
	ldr r1, _0222F9D4 ; =MOD83_0223B884
	mov r2, #1
	ldr r1, [r1]
	add r1, r1, r0
	ldr r0, _0222F9D8 ; =0x000003C1
	strb r2, [r1, r0]
	bx lr
	nop
_0222F9D4: .word MOD83_0223B884
_0222F9D8: .word 0x000003C1
	thumb_func_end MOD83_0222F9C4

	thumb_func_start MOD83_0222F9DC
MOD83_0222F9DC: ; 0x0222F9DC
	push {r3, lr}
	ldr r1, _0222F9F4 ; =MOD83_0223B884
	mov r0, #0xf
	ldr r1, [r1]
	bl FreeToHeapExplicit
	ldr r0, _0222F9F4 ; =MOD83_0223B884
	mov r1, #0
	str r1, [r0]
	bl FUN_02031A08
	pop {r3, pc}
	.align 2, 0
_0222F9F4: .word MOD83_0223B884
	thumb_func_end MOD83_0222F9DC

	thumb_func_start MOD83_0222F9F8
MOD83_0222F9F8: ; 0x0222F9F8
	ldr r3, _0222FA04 ; =FUN_0202D8D0
	add r2, r0, #0
	ldr r0, _0222FA08 ; =MOD83_0223A3F0
	mov r1, #2
	bx r3
	nop
_0222FA04: .word FUN_0202D8D0
_0222FA08: .word MOD83_0223A3F0
	thumb_func_end MOD83_0222F9F8

	thumb_func_start MOD83_0222FA0C
MOD83_0222FA0C: ; 0x0222FA0C
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #1
	ldr r0, _0222FA40 ; =0x00002994
	bne _0222FA2C
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0222FA3C
	add r0, r4, #0
	add r0, #0x18
	mov r1, #1
	bl FUN_0200D858
	ldr r1, _0222FA40 ; =0x00002994
	str r0, [r4, r1]
	pop {r4, pc}
_0222FA2C:
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222FA36
	bl FUN_0200DBFC
_0222FA36:
	ldr r0, _0222FA40 ; =0x00002994
	mov r1, #0
	str r1, [r4, r0]
_0222FA3C:
	pop {r4, pc}
	nop
_0222FA40: .word 0x00002994
	thumb_func_end MOD83_0222FA0C

	thumb_func_start MOD83_0222FA44
MOD83_0222FA44: ; 0x0222FA44
	ldr r3, _0222FA48 ; =MOD83_0222FA0C
	bx r3
	.align 2, 0
_0222FA48: .word MOD83_0222FA0C
	thumb_func_end MOD83_0222FA44

	thumb_func_start MOD83_0222FA4C
MOD83_0222FA4C: ; 0x0222FA4C
	push {r3, r4, r5, r6, r7, lr}
	bl OverlayManager_GetData
	add r7, r0, #0
	bl MOD83_02238E48
	ldr r0, [r7, #0x7c]
	cmp r0, #0
	beq _0222FA62
	bl ListMenuItems_dtor
_0222FA62:
	ldr r0, [r7, #0x78]
	cmp r0, #0
	beq _0222FA70
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
_0222FA70:
	add r0, r7, #0
	add r0, #0x18
	bl FUN_02019570
	add r0, r7, #0
	add r0, #0x18
	bl RemoveWindow
	add r0, r7, #0
	add r0, #0x58
	bl WindowIsInUse
	cmp r0, #0
	beq _0222FA9C
	add r0, r7, #0
	add r0, #0x58
	bl FUN_02019570
	add r0, r7, #0
	add r0, #0x58
	bl RemoveWindow
_0222FA9C:
	add r5, r7, #0
	mov r6, #0
	add r4, r7, #0
	add r5, #0x28
_0222FAA4:
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0222FAB6
	add r0, r5, #0
	bl FUN_02019570
	add r0, r5, #0
	bl RemoveWindow
_0222FAB6:
	add r6, r6, #1
	add r4, #0x10
	add r5, #0x10
	cmp r6, #3
	blt _0222FAA4
	ldr r0, [r7]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r7]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r7]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r7]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r7]
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_0222FA4C

	thumb_func_start MOD83_0222FAE8
MOD83_0222FAE8: ; 0x0222FAE8
	push {r3, lr}
	sub sp, #8
	bl MOD83_02238AFC
	bl MOD83_02238B4C
	mov r0, #8
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0xa
	mov r2, #7
	mov r3, #9
	bl MOD83_02238BC4
	add sp, #8
	pop {r3, pc}
	thumb_func_end MOD83_0222FAE8

	thumb_func_start MOD83_0222FB0C
MOD83_0222FB0C: ; 0x0222FB0C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _0222FB32
	str r1, [sp]
	ldr r1, _0222FB40 ; =0x000005C4
	mov r0, #0
	ldr r1, [r4, r1]
	mov r2, #0x80
	mov r3, #0x64
	bl MOD83_02238DBC
	ldr r1, _0222FB40 ; =0x000005C4
	add sp, #4
	str r0, [r4, r1]
	pop {r3, r4, pc}
_0222FB32:
	ldr r0, _0222FB40 ; =0x000005C4
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222FB40: .word 0x000005C4
	thumb_func_end MOD83_0222FB0C

	thumb_func_start MOD83_0222FB44
MOD83_0222FB44: ; 0x0222FB44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl WindowIsInUse
	cmp r0, #1
	bne _0222FB5A
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CCF8
_0222FB5A:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_0222FB44

	thumb_func_start MOD83_0222FB5C
MOD83_0222FB5C: ; 0x0222FB5C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, _0222FBB0 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #2
	beq _0222FB7A
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x18
	mov r2, #3
	bl MOD83_0223050C
_0222FB7A:
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	ldr r0, _0222FBB0 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #2
	beq _0222FBAA
	add r0, r4, #0
	mov r1, #0xf
	bl MOD83_0222F900
	ldr r1, _0222FBB4 ; =0x00001C20
	ldr r0, _0222FBB8 ; =0x00000434
	str r1, [r4, r0]
	bl FUN_02033E74
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	mov r0, #7
	pop {r3, r4, r5, pc}
_0222FBAA:
	mov r0, #0x13
	pop {r3, r4, r5, pc}
	nop
_0222FBB0: .word 0x000015D4
_0222FBB4: .word 0x00001C20
_0222FBB8: .word 0x00000434
	thumb_func_end MOD83_0222FB5C

	thumb_func_start MOD83_0222FBBC
MOD83_0222FBBC: ; 0x0222FBBC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, #0x80
	ldr r1, [r0]
	cmp r1, #1
	bne _0222FBD2
	mov r0, #0x30
	pop {r3, r4, r5, pc}
_0222FBD2:
	sub r0, r1, #2
	cmp r0, #2
	bhi _0222FBDC
	mov r0, #0x30
	pop {r3, r4, r5, pc}
_0222FBDC:
	cmp r1, #5
	bne _0222FBE4
	mov r0, #0x30
	pop {r3, r4, r5, pc}
_0222FBE4:
	ldr r0, _0222FC38 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222FBF4
	ldr r0, _0222FC3C ; =0x00000438
	ldr r0, [r4, r0]
	bl MOD83_0222F934
_0222FBF4:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x18
	mov r2, #6
	bl MOD83_0223050C
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	ldr r0, _0222FC38 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222FC22
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FB0C
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
_0222FC22:
	ldr r0, _0222FC38 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222FC34
	mov r0, #0xab
	bl FUN_02031588
	mov r0, #9
	pop {r3, r4, r5, pc}
_0222FC34:
	mov r0, #0x15
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222FC38: .word 0x000015D4
_0222FC3C: .word 0x00000438
	thumb_func_end MOD83_0222FBBC

	thumb_func_start MOD83_0222FC40
MOD83_0222FC40: ; 0x0222FC40
	push {r3, r4, r5, r6, r7, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, _0222FCA4 ; =0x000015D4
	add r5, r4, #0
	add r6, r4, #0
	ldr r0, [r4, r0]
	add r5, #0xdc
	add r6, #0x8c
	cmp r0, #1
	beq _0222FC5E
	cmp r0, #3
	beq _0222FC84
	b _0222FC9E
_0222FC5E:
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl MOD83_0222F9B8
	mov r2, #0xd6
	add r1, r0, #0
	add r0, r5, #0
	lsl r2, r2, #2
	bl memcpy
	add r0, r4, #0
	add r4, #0xdc
	add r0, #0x8c
	add r1, r4, #0
	mov r2, #0x56
	bl MOD83_02239374
	b _0222FC9E
_0222FC84:
	ldr r7, _0222FCA8 ; =0x000005D4
	mov r2, #0xd6
	add r1, r4, r7
	add r0, r5, #0
	add r1, #0x50
	lsl r2, r2, #2
	bl memcpy
	add r0, r6, #0
	add r1, r4, r7
	mov r2, #0x50
	bl memcpy
_0222FC9E:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222FCA4: .word 0x000015D4
_0222FCA8: .word 0x000005D4
	thumb_func_end MOD83_0222FC40

	thumb_func_start MOD83_0222FCAC
MOD83_0222FCAC: ; 0x0222FCAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222FCD8 ; =0x00002990
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _0222FCBE
	mov r1, #0
	sub r0, r0, #4
	str r1, [r4, r0]
_0222FCBE:
	bl MOD83_022394CC
	sub r0, r0, #2
	cmp r0, #1
	bhi _0222FCD4
	ldr r0, _0222FCDC ; =0x0000061B
	bl FUN_020054C8
	ldr r0, _0222FCE0 ; =0x0000298C
	mov r1, #0
	str r1, [r4, r0]
_0222FCD4:
	pop {r4, pc}
	nop
_0222FCD8: .word 0x00002990
_0222FCDC: .word 0x0000061B
_0222FCE0: .word 0x0000298C
	thumb_func_end MOD83_0222FCAC

	thumb_func_start MOD83_0222FCE4
MOD83_0222FCE4: ; 0x0222FCE4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	bl OverlayManager_GetData
	add r6, r0, #0
	add r4, r6, #0
	add r5, r6, #0
	add r0, r7, #0
	add r4, #0x8c
	add r5, #0xdc
	bl OverlayManager_GetField18
	ldr r0, [r0, #8]
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x4e
	ldrb r0, [r0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _0222FD12
	mov r7, #0
	b _0222FD3E
_0222FD12:
	mov r1, #0x35
	add r2, r4, #0
	mov r0, #0
	lsl r1, r1, #4
	strb r0, [r5, r1]
	add r2, #0x4e
	ldrb r2, [r2]
	mov r7, #1
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1f
	bne _0222FD2C
	sub r1, #8
	strb r0, [r5, r1]
_0222FD2C:
	add r0, sp, #8
	bl GF_RTC_CopyDate
	add r0, sp, #8
	bl RTC_ConvertDateToDay
	mov r1, #0xd5
	lsl r1, r1, #2
	str r0, [r5, r1]
_0222FD3E:
	ldr r0, [sp]
	bl FUN_0202251C
	add r4, #0x4c
	ldrh r1, [r4]
	str r0, [sp, #4]
	bl FUN_0202AF24
	cmp r7, #0
	bne _0222FD5E
	ldr r0, [sp, #4]
	add r1, r5, #0
	mov r2, #0
	bl FUN_0202AC98
	b _0222FD66
_0222FD5E:
	ldr r0, [sp, #4]
	add r1, r5, #0
	bl FUN_0202AD08
_0222FD66:
	ldr r0, [sp]
	bl MOD83_022394BC
	ldr r0, _0222FD7C ; =0x00002990
	mov r1, #0
	str r1, [r6, r0]
	ldr r1, _0222FD80 ; =MOD83_0222FCAC
	sub r0, r0, #4
	str r1, [r6, r0]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222FD7C: .word 0x00002990
_0222FD80: .word MOD83_0222FCAC
	thumb_func_end MOD83_0222FCE4

	thumb_func_start MOD83_0222FD84
MOD83_0222FD84: ; 0x0222FD84
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r0, #0
	add r4, r1, #0
	bl OverlayManager_GetData
	cmp r4, #0
	bne _0222FD98
	mov r5, #4
	b _0222FD9C
_0222FD98:
	mov r5, #0
	mvn r5, r5
_0222FD9C:
	ldr r1, [r0, #0x48]
	add r4, r0, #0
	add r4, #0x48
	cmp r1, #0
	bne _0222FDC6
	mov r1, #0xa
	str r1, [sp]
	mov r1, #6
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r2, #0
	mov r1, #0x6b
	str r2, [sp, #0xc]
	lsl r1, r1, #2
	str r1, [sp, #0x10]
	ldr r0, [r0]
	add r1, r4, #0
	mov r3, #0x17
	bl AddWindowParameterized
_0222FDC6:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	ldr r1, _0222FDE4 ; =MOD83_0223ADD8
	add r0, r6, #0
	mov r2, #2
	add r3, r4, #0
	str r5, [sp]
	bl MOD83_022303B0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222FDE4: .word MOD83_0223ADD8
	thumb_func_end MOD83_0222FD84

	thumb_func_start MOD83_0222FDE8
MOD83_0222FDE8: ; 0x0222FDE8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl MOD83_0222FB44
	ldr r0, _0222FE20 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222FE14
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
_0222FE14:
	bl FUN_02033ED0
	add r0, r5, #0
	bl MOD83_02230118
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222FE20: .word 0x000015D4
	thumb_func_end MOD83_0222FDE8

	thumb_func_start MOD83_0222FE24
MOD83_0222FE24: ; 0x0222FE24
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl OverlayManager_GetData
	add r5, r0, #0
	bl MOD83_02238700
	cmp r0, #0
	beq _0222FE3C
	mov r1, #2
	b _0222FE3E
_0222FE3C:
	mov r1, #1
_0222FE3E:
	ldr r0, _0222FE98 ; =0x000015D4
	str r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x38
	mov r1, #0
	bl MOD83_0222FB44
	add r4, r5, #0
	ldr r0, [r5, #0x48]
	add r4, #0x48
	cmp r0, #0
	bne _0222FE76
	mov r0, #0xa
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x6b
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, r4, #0
	mov r3, #0x17
	bl AddWindowParameterized
_0222FE76:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	mov r2, #2
	ldr r1, _0222FE9C ; =MOD83_0223ADC8
	add r0, r6, #0
	add r3, r4, #0
	str r2, [sp]
	bl MOD83_022303B0
	mov r0, #5
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_0222FE98: .word 0x000015D4
_0222FE9C: .word MOD83_0223ADC8
	thumb_func_end MOD83_0222FE24

	thumb_func_start MOD83_0222FEA0
MOD83_0222FEA0: ; 0x0222FEA0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, _0222FF08 ; =0x000015D4
	mov r1, #4
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x38
	mov r1, #0
	bl MOD83_0222FB44
	add r5, r4, #0
	ldr r0, [r4, #0x48]
	add r5, #0x48
	cmp r0, #0
	bne _0222FEE6
	mov r0, #0xa
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x6b
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, r5, #0
	mov r3, #0x17
	bl AddWindowParameterized
_0222FEE6:
	add r0, r5, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	mov r0, #0x4e
	str r0, [sp]
	ldr r1, _0222FF0C ; =MOD83_0223AD98
	add r0, r6, #0
	mov r2, #2
	add r3, r5, #0
	bl MOD83_022303B0
	mov r0, #5
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222FF08: .word 0x000015D4
_0222FF0C: .word MOD83_0223AD98
	thumb_func_end MOD83_0222FEA0

	thumb_func_start MOD83_0222FF10
MOD83_0222FF10: ; 0x0222FF10
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, _0222FF78 ; =0x000015D4
	mov r1, #3
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x38
	mov r1, #0
	bl MOD83_0222FB44
	add r5, r4, #0
	ldr r0, [r4, #0x48]
	add r5, #0x48
	cmp r0, #0
	bne _0222FF56
	mov r0, #0xa
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x6b
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, r5, #0
	mov r3, #0x17
	bl AddWindowParameterized
_0222FF56:
	add r0, r5, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	mov r0, #0x4d
	str r0, [sp]
	ldr r1, _0222FF7C ; =MOD83_0223ADA8
	add r0, r6, #0
	mov r2, #2
	add r3, r5, #0
	bl MOD83_022303B0
	mov r0, #5
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222FF78: .word 0x000015D4
_0222FF7C: .word MOD83_0223ADA8
	thumb_func_end MOD83_0222FF10

	thumb_func_start MOD83_0222FF80
MOD83_0222FF80: ; 0x0222FF80
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r1, [r0, #0x48]
	add r4, #0x48
	cmp r1, #0
	bne _0222FFB4
	mov r1, #0xa
	str r1, [sp]
	mov r1, #6
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r2, #0
	mov r1, #0x6b
	str r2, [sp, #0xc]
	lsl r1, r1, #2
	str r1, [sp, #0x10]
	ldr r0, [r0]
	add r1, r4, #0
	mov r3, #0x17
	bl AddWindowParameterized
_0222FFB4:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	mov r0, #4
	str r0, [sp]
	ldr r1, _0222FFD4 ; =MOD83_0223ADB8
	add r0, r5, #0
	mov r2, #2
	add r3, r4, #0
	bl MOD83_022303B0
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_0222FFD4: .word MOD83_0223ADB8
	thumb_func_end MOD83_0222FF80

	thumb_func_start MOD83_0222FFD8
MOD83_0222FFD8: ; 0x0222FFD8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl MOD83_0222FB44
	bl FUN_02033ED0
	ldr r0, _0223000C ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _02230004
	bl MOD83_0222F9DC
_02230004:
	add r0, r5, #0
	bl MOD83_02230118
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223000C: .word 0x000015D4
	thumb_func_end MOD83_0222FFD8

	thumb_func_start MOD83_02230010
MOD83_02230010: ; 0x02230010
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x18
	mov r2, #3
	bl MOD83_0223050C
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	ldr r0, _02230044 ; =MOD83_0223B888
	mov r1, #0x24
	str r1, [r0, #0x10]
	mov r0, #0x20
	pop {r3, r4, r5, pc}
	nop
_02230044: .word MOD83_0223B888
	thumb_func_end MOD83_02230010

	thumb_func_start MOD83_02230048
MOD83_02230048: ; 0x02230048
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r0, #0x80
	ldr r0, [r0]
	sub r0, r0, #2
	cmp r0, #2
	bhi _02230060
	mov r0, #0x30
	pop {r3, r4, r5, pc}
_02230060:
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FB0C
	add r4, #0x18
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #7
	bl MOD83_0223050C
	mov r0, #0x21
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD83_02230048

	thumb_func_start MOD83_02230084
MOD83_02230084: ; 0x02230084
	push {r3, lr}
	ldr r0, _022300A8 ; =MOD83_0223B888
	ldr r0, [r0, #0x10]
	cmp r0, #0x27
	beq _02230096
	cmp r0, #0x28
	beq _02230096
	cmp r0, #0x2f
	bne _022300A4
_02230096:
	bl MOD83_02239A14
	cmp r0, #0
	beq _022300A4
	ldr r0, _022300A8 ; =MOD83_0223B888
	mov r1, #0x2a
	str r1, [r0, #0x10]
_022300A4:
	mov r0, #0x23
	pop {r3, pc}
	.align 2, 0
_022300A8: .word MOD83_0223B888
	thumb_func_end MOD83_02230084

	thumb_func_start MOD83_022300AC
MOD83_022300AC: ; 0x022300AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x18
	mov r2, #3
	bl MOD83_0223050C
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	mov r1, #1
	ldr r0, _022300F0 ; =0x000015DC
	lsl r1, r1, #0xc
	str r1, [r4, r0]
	ldr r0, _022300F4 ; =0x00002620
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #0x1b
	pop {r3, r4, r5, pc}
	nop
_022300F0: .word 0x000015DC
_022300F4: .word 0x00002620
	thumb_func_end MOD83_022300AC

	thumb_func_start MOD83_022300F8
MOD83_022300F8: ; 0x022300F8
	push {r4, lr}
	add r4, r0, #0
	bl OverlayManager_GetData
	add r0, #0x38
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	mov r1, #0xc4
	mov r2, #0
	bl MOD83_02230464
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_022300F8

	thumb_func_start MOD83_02230118
MOD83_02230118: ; 0x02230118
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl OverlayManager_GetData
	add r5, r0, #0
	ldr r0, [r5, #4]
	bl FUN_0202251C
	ldr r0, _02230194 ; =0x000005C8
	ldr r1, [r5, r0]
	cmp r1, #0x1e
	bne _0223013E
	mov r1, #1
	add r0, r0, #4
	str r1, [r5, r0]
	add r0, r5, #0
	bl MOD83_022313E4
_0223013E:
	add r0, r5, #0
	add r0, #0x28
	mov r1, #0
	bl MOD83_0222FB44
	add r4, r5, #0
	ldr r0, [r5, #0x38]
	add r4, #0x38
	cmp r0, #0
	bne _02230172
	mov r0, #9
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x49
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r5]
	add r1, r4, #0
	mov r3, #0xf
	bl AddWindowParameterized
_02230172:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	mov r0, #1
	str r0, [sp]
	ldr r1, _02230198 ; =MOD83_0223AE20
	add r0, r6, #0
	mov r2, #4
	add r3, r4, #0
	bl MOD83_022303B0
	mov r0, #4
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02230194: .word 0x000005C8
_02230198: .word MOD83_0223AE20
	thumb_func_end MOD83_02230118

	thumb_func_start MOD83_0223019C
MOD83_0223019C: ; 0x0223019C
	push {r4, lr}
	bl OverlayManager_GetData
	ldr r1, _022301CC ; =0x000005C8
	add r4, r0, #0
	ldr r2, [r4, r1]
	cmp r2, #0x1e
	bne _022301B6
	mov r2, #1
	add r1, r1, #4
	str r2, [r4, r1]
	bl MOD83_022313E4
_022301B6:
	ldr r2, _022301D0 ; =0x000015D8
	mov r0, #0
	ldr r2, [r4, r2]
	mov r1, #0x35
	mov r3, #2
	bl MOD83_0223886C
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}
	nop
_022301CC: .word 0x000005C8
_022301D0: .word 0x000015D8
	thumb_func_end MOD83_0223019C

	thumb_func_start MOD83_022301D4
MOD83_022301D4: ; 0x022301D4
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, _02230204 ; =0x000005C8
	ldr r1, [r4, r0]
	cmp r1, #0x1e
	bne _022301EA
	mov r1, #1
	add r0, r0, #4
	str r1, [r4, r0]
_022301EA:
	mov r0, #1
	bl MOD83_02238860
	ldr r2, _02230208 ; =0x000015D8
	mov r0, #0
	ldr r2, [r4, r2]
	mov r1, #0x34
	mov r3, #2
	bl MOD83_0223886C
	mov r0, #0
	mvn r0, r0
	pop {r4, pc}
	.align 2, 0
_02230204: .word 0x000005C8
_02230208: .word 0x000015D8
	thumb_func_end MOD83_022301D4

	thumb_func_start MOD83_0223020C
MOD83_0223020C: ; 0x0223020C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r3, #0
	ldr r3, _02230254 ; =MOD83_0223A418
	add r7, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r2, sp, #0
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	lsr r1, r6, #0xb
	str r0, [r2]
	add r0, sp, #0
	strb r1, [r0, #0x12]
	lsr r1, r5, #0xe
	strb r1, [r0, #0x13]
	lsl r1, r4, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	mov r2, ip
	mov r3, #0
	bl FUN_02016C18
	lsl r1, r4, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	bl FUN_02018744
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02230254: .word MOD83_0223A418
	thumb_func_end MOD83_0223020C

	thumb_func_start MOD83_02230258
MOD83_02230258: ; 0x02230258
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r5, _022302B0 ; =MOD83_0223A408
	add r3, sp, #0
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	mov r1, #0
	mov r2, #0xf
	add r0, r4, #0
	lsl r2, r2, #0xc
	add r3, r1, #0
	bl MOD83_0223020C
	mov r1, #1
	mov r2, #0x3e
	add r0, r4, #0
	lsl r2, r2, #0xa
	lsl r3, r1, #0xf
	bl MOD83_0223020C
	mov r2, #0xe
	add r0, r4, #0
	mov r1, #4
	lsl r2, r2, #0xa
	mov r3, #0
	bl MOD83_0223020C
	mov r2, #0x1e
	mov r3, #1
	add r0, r4, #0
	mov r1, #5
	lsl r2, r2, #0xa
	lsl r3, r3, #0xe
	bl MOD83_0223020C
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_022302B0: .word MOD83_0223A408
	thumb_func_end MOD83_02230258

	thumb_func_start MOD83_022302B4
MOD83_022302B4: ; 0x022302B4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x20
	mov r2, #4
	str r0, [sp]
	mov r0, #0x56
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0
	add r3, #0xfc
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x56
	str r0, [sp, #0xc]
	mov r0, #0x74
	add r2, r4, #0
	mov r3, #5
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x56
	str r0, [sp, #0xc]
	mov r0, #0x74
	mov r1, #2
	add r2, r4, #0
	mov r3, #5
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #8
	mov r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #5
	add r3, r2, #0
	bl FUN_020186B4
	add r0, r4, #0
	mov r1, #5
	bl FUN_02017CD0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_022302B4

	thumb_func_start MOD83_02230330
MOD83_02230330: ; 0x02230330
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x56
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0
	add r3, r0, #0
	add r2, r1, #0
	add r3, #0x8c
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	mov r0, #0x56
	str r0, [sp, #0xc]
	mov r0, #0x74
	add r2, r4, #0
	add r3, r1, #0
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x56
	str r0, [sp, #0xc]
	mov r0, #0x74
	mov r1, #2
	add r2, r4, #0
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #8
	mov r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl FUN_020186B4
	add r0, r4, #0
	mov r1, #1
	bl FUN_02017CD0
	add r0, r4, #0
	bl MOD83_022302B4
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02230330

	thumb_func_start MOD83_022303B0
MOD83_022303B0: ; 0x022303B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp]
	add r5, r1, #0
	add r7, r2, #0
	str r3, [sp, #4]
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #0x7c]
	cmp r0, #0
	beq _022303CC
	bl ListMenuItems_dtor
_022303CC:
	add r0, r7, #0
	mov r1, #0x56
	bl ListMenuItems_ctor
	str r0, [r4, #0x7c]
	ldr r2, _0223045C ; =0x00000172
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x56
	bl NewMsgDataFromNarc
	mov r6, #0
	str r0, [r4, #0x10]
	cmp r7, #0
	ble _022303FE
_022303EA:
	ldr r0, [r4, #0x7c]
	ldr r1, [r4, #0x10]
	ldr r2, [r5]
	ldr r3, [r5, #4]
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r5, #8
	cmp r6, r7
	blt _022303EA
_022303FE:
	ldr r0, [r4, #0x10]
	bl DestroyMsgData
	ldr r3, _02230460 ; =MOD83_0223AE00
	add r2, sp, #8
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x7c]
	str r0, [sp, #8]
	add r0, sp, #8
	strh r7, [r0, #0x12]
	ldrh r1, [r0, #0x12]
	strh r1, [r0, #0x10]
	ldr r0, [sp, #4]
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x78]
	cmp r0, #0
	beq _02230436
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
_02230436:
	mov r1, #0
	add r0, sp, #8
	add r2, r1, #0
	mov r3, #0x56
	bl ListMenuInit
	str r0, [r4, #0x78]
	mov r0, #0
	ldr r2, [sp, #0x40]
	mvn r0, r0
	cmp r2, r0
	beq _02230458
	add r4, #0x18
	ldr r0, [sp]
	add r1, r4, #0
	bl MOD83_0223050C
_02230458:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223045C: .word 0x00000172
_02230460: .word MOD83_0223AE00
	thumb_func_end MOD83_022303B0

	thumb_func_start MOD83_02230464
MOD83_02230464: ; 0x02230464
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	str r0, [sp, #0x14]
	str r1, [sp, #0x1c]
	str r2, [sp, #0x18]
	bl OverlayManager_GetData
	add r7, r0, #0
	ldr r0, [r7, #4]
	mov r5, #0
	bl FUN_0202251C
	ldr r1, _02230508 ; =MOD83_0223AD98
	add r4, r7, #0
	ldr r2, [r1, #0x50]
	ldr r1, [r1, #0x54]
	add r4, #0x28
	add r5, r5, #1
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	bl FUN_0202AE70
	cmp r0, #0
	beq _022304A8
	lsl r6, r5, #3
	add r0, sp, #0x20
	add r1, r0, r6
	ldr r0, _02230508 ; =MOD83_0223AD98
	add r5, r5, #1
	ldr r3, [r0, #0x58]
	ldr r2, [r0, #0x5c]
	add r0, sp, #0x20
	str r3, [r0, r6]
	str r2, [r1, #4]
_022304A8:
	lsl r6, r5, #3
	add r0, sp, #0x20
	add r1, r0, r6
	ldr r0, _02230508 ; =MOD83_0223AD98
	ldr r3, [r0, #0x60]
	ldr r2, [r0, #0x64]
	add r0, sp, #0x20
	str r3, [r0, r6]
	str r2, [r1, #4]
	ldr r0, [r4]
	cmp r0, #0
	bne _022304E6
	mov r0, #7
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r5, #1
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	mov r2, #0
	lsl r0, r0, #0x10
	str r2, [sp, #0xc]
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r7]
	add r1, r4, #0
	mov r3, #8
	bl AddWindowParameterized
_022304E6:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	ldr r0, [sp, #0x18]
	add r1, sp, #0x20
	str r0, [sp]
	ldr r0, [sp, #0x14]
	add r2, r5, #1
	add r3, r4, #0
	bl MOD83_022303B0
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02230508: .word MOD83_0223AD98
	thumb_func_end MOD83_02230464

	thumb_func_start MOD83_0223050C
MOD83_0223050C: ; 0x0223050C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r7, r2, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r2, _0223059C ; =0x00000172
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x56
	bl NewMsgDataFromNarc
	str r0, [r4, #0x10]
	mov r0, #0x56
	bl ScrStrBufs_new
	str r0, [r4, #0xc]
	mov r0, #1
	mov r1, #6
	bl GetFontAttribute
	add r1, r0, #0
	add r0, r5, #0
	bl FillWindowPixelBuffer
	ldr r6, [r4, #0x14]
	cmp r6, #0
	bne _02230554
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r2, r7, #0
	mov r3, #0x56
	bl ReadMsgData_ExpandPlaceholders
	add r6, r0, #0
_02230554:
	mov r3, #0
	str r3, [sp]
	ldr r0, [r4, #0x68]
	mov r1, #1
	str r0, [sp, #4]
	ldr r0, _022305A0 ; =0x0001020F
	add r2, r6, #0
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	add r0, r5, #0
	bl AddTextPrinterParameterized2
	str r0, [r4, #0x6c]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _0223057A
	add r0, r6, #0
	bl String_dtor
_0223057A:
	add r0, r5, #0
	mov r1, #0
	mov r2, #1
	mov r3, #2
	bl FUN_0200D0BC
	ldr r0, [r4, #0x10]
	bl DestroyMsgData
	ldr r0, [r4, #0xc]
	bl ScrStrBufs_delete
	mov r0, #0xff
	str r0, [r4, #0x68]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223059C: .word 0x00000172
_022305A0: .word 0x0001020F
	thumb_func_end MOD83_0223050C

	thumb_func_start MOD83_022305A4
MOD83_022305A4: ; 0x022305A4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r2, #0
	bl OverlayManager_GetData
	mov r0, #0x25
	mov r1, #0x56
	bl String_ctor
	add r1, r6, #0
	mov r2, #0x24
	add r4, r0, #0
	bl CopyU16ArrayToStringN
	mov r0, #0
	mov r1, #6
	bl GetFontAttribute
	add r1, r0, #0
	add r0, r5, #0
	bl FillWindowPixelBuffer
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02230600 ; =0x0001020F
	add r2, r4, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r3, r1, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CCA4
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_02230600: .word 0x0001020F
	thumb_func_end MOD83_022305A4

	thumb_func_start MOD83_02230604
MOD83_02230604: ; 0x02230604
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl OverlayManager_GetData
	ldr r0, [r0, #0x78]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02230628
	add r0, r0, #1
	cmp r4, r0
	beq _0223065E
	b _02230642
_02230628:
	ldr r0, _02230660 ; =0x000005DC
	bl FUN_020054C8
	cmp r6, #0
	beq _0223065E
	add r0, r7, #0
	blx r6
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223065E
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02230642:
	ldr r0, _02230660 ; =0x000005DC
	bl FUN_020054C8
	cmp r4, #0
	beq _0223065E
	ldr r0, _02230664 ; =MOD83_0223B888
	str r4, [r0, #0xc]
	add r0, r7, #0
	blx r4
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223065E
	str r0, [r5]
_0223065E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02230660: .word 0x000005DC
_02230664: .word MOD83_0223B888
	thumb_func_end MOD83_02230604

	thumb_func_start MOD83_02230668
MOD83_02230668: ; 0x02230668
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0201BD5C
	mov r0, #0
	add r1, r0, #0
	mov r2, #0x56
	bl FUN_02002ED0
	mov r0, #0
	mov r1, #0x20
	mov r2, #0x56
	bl FUN_02002ED0
	ldr r0, [r4, #8]
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x56
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #0
	mov r2, #1
	mov r3, #2
	bl FUN_0200CD68
	mov r0, #1
	str r0, [sp]
	mov r0, #0x56
	str r0, [sp, #4]
	ldr r0, [r4]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #3
	bl FUN_0200CB00
	mov r0, #5
	ldr r1, _02230710 ; =0x00007D8C
	lsl r0, r0, #0x18
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x18
	bl WindowIsInUse
	cmp r0, #0
	bne _022306EC
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	add r1, r4, #0
	str r2, [sp, #0xc]
	mov r0, #0x28
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x18
	mov r3, #2
	bl AddWindowParameterized
_022306EC:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x18
	mov r2, #0
	bl MOD83_0223050C
	add r0, r5, #0
	mov r1, #0xc4
	mov r2, #0
	bl MOD83_02230464
	ldr r0, [r4]
	bl MOD83_02230330
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02230710: .word 0x00007D8C
	thumb_func_end MOD83_02230668

	thumb_func_start MOD83_02230714
MOD83_02230714: ; 0x02230714
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r1, _022307A4 ; =0x000015DC
	add r0, r6, #0
	add r1, r4, r1
	bl MOD83_02239F34
	cmp r0, #4
	bhi _022307A2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223073A: ; jump table
	.short _022307A2 - _0223073A - 2 ; case 0
	.short _02230744 - _0223073A - 2 ; case 1
	.short _02230768 - _0223073A - 2 ; case 2
	.short _02230768 - _0223073A - 2 ; case 3
	.short _02230776 - _0223073A - 2 ; case 4
_02230744:
	ldr r1, _022307A8 ; =0x000015FC
	add r0, r4, #0
	mov r2, #0xea
	add r0, #0x8c
	add r1, r4, r1
	lsl r2, r2, #2
	bl memcpy
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #0x1b
	add r4, #0x84
	str r0, [r4]
	mov r0, #0x13
	str r0, [r5]
	pop {r4, r5, r6, pc}
_02230768:
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #0x11
	str r0, [r5]
	pop {r4, r5, r6, pc}
_02230776:
	ldr r0, _022307AC ; =0x00002624
	add r0, r4, r0
	bl FUN_02019570
	ldr r0, _022307AC ; =0x00002624
	add r0, r4, r0
	bl RemoveWindow
	ldr r0, [r4]
	mov r1, #0
	bl FUN_02018744
	ldr r0, _022307B0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r6, #0
	mov r1, #0xc4
	mov r2, #0
	bl MOD83_02230464
	mov r0, #3
	str r0, [r5]
_022307A2:
	pop {r4, r5, r6, pc}
	.align 2, 0
_022307A4: .word 0x000015DC
_022307A8: .word 0x000015FC
_022307AC: .word 0x00002624
_022307B0: .word 0x000005DC
	thumb_func_end MOD83_02230714

	thumb_func_start MOD83_022307B4
MOD83_022307B4: ; 0x022307B4
	push {r3, r4, r5, r6, lr}
	sub sp, #0x5c
	add r5, r0, #0
	ldr r0, _0223083C ; =0x00002610
	ldr r4, [r5, r0]
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _022307C8
	mov r4, #0xb
_022307C8:
	mov r0, #0x10
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	mov r1, #0
	bl FUN_02018744
	mov r0, #0x56
	bl ScrStrBufs_new
	mov r1, #2
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, _02230840 ; =0x00002614
	mov r1, #0
	ldr r2, [r5, r2]
	mov r3, #5
	add r6, r0, #0
	bl BufferIntegerAsString
	mov r0, #0x1f
	ldr r1, _02230844 ; =0x00002624
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r3, _02230848 ; =0x00000265
	add r0, sp, #8
	add r1, r5, r1
	mov r2, #1
	bl MOD83_022388E4
	add r0, sp, #8
	mov r1, #0x18
	mov r2, #0x10
	mov r3, #0x64
	bl MOD83_02238934
	add r0, sp, #8
	mov r1, #0
	mov r2, #1
	bl MOD83_0223893C
	str r6, [sp, #0x1c]
	str r4, [sp]
	mov r2, #4
	ldr r0, [r5]
	add r1, sp, #8
	add r3, r2, #0
	bl MOD83_02238A38
	add r0, r6, #0
	bl ScrStrBufs_delete
	add sp, #0x5c
	pop {r3, r4, r5, r6, pc}
	nop
_0223083C: .word 0x00002610
_02230840: .word 0x00002614
_02230844: .word 0x00002624
_02230848: .word 0x00000265
	thumb_func_end MOD83_022307B4

	thumb_func_start MOD83_0223084C
MOD83_0223084C: ; 0x0223084C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r1, r0, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #3
	bne _02230862
	mov r4, #0x15
	b _0223088C
_02230862:
	cmp r0, #4
	bne _0223086A
	mov r4, #0x19
	b _0223088C
_0223086A:
	cmp r0, #2
	bne _02230872
	mov r4, #0x16
	b _0223088C
_02230872:
	cmp r0, #1
	bne _0223087A
	mov r4, #0x1b
	b _0223088C
_0223087A:
	cmp r0, #5
	bne _0223088C
	add r0, r5, #0
	add r1, #0x18
	mov r2, #9
	mov r3, #0x33
	bl MOD83_0223089C
	pop {r3, r4, r5, pc}
_0223088C:
	add r0, r5, #0
	add r1, #0x18
	add r2, r4, #0
	mov r3, #0x32
	bl MOD83_0223089C
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD83_0223084C

	thumb_func_start MOD83_0223089C
MOD83_0223089C: ; 0x0223089C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	add r6, r1, #0
	add r5, r2, #0
	str r3, [sp, #4]
	bl OverlayManager_GetData
	add r4, r0, #0
	cmp r6, #0
	beq _022308F8
	cmp r5, #0
	beq _022308F8
	ldr r2, _02230920 ; =0x00000172
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x56
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #0x56
	bl ScrStrBufs_new
	add r1, r7, #0
	add r2, r5, #0
	mov r3, #0x56
	str r0, [sp, #8]
	bl ReadMsgData_ExpandPlaceholders
	str r0, [r4, #0x14]
	mov r0, #1
	str r0, [r4, #0x68]
	ldr r0, [sp]
	add r1, r6, #0
	add r2, r5, #0
	bl MOD83_0223050C
	ldr r0, [sp, #4]
	str r0, [r4, #0x74]
	ldr r0, [sp, #8]
	bl ScrStrBufs_delete
	add r0, r7, #0
	bl DestroyMsgData
	b _02230918
_022308F8:
	ldr r0, [r4, #0x6c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02230918
	ldr r0, [r4, #0x14]
	bl String_dtor
	mov r0, #0
	str r0, [r4, #0x14]
	str r0, [r4, #0x68]
	add sp, #0xc
	ldr r0, [r4, #0x74]
	pop {r4, r5, r6, r7, pc}
_02230918:
	mov r0, #0x31
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02230920: .word 0x00000172
	thumb_func_end MOD83_0223089C

	thumb_func_start MOD83_02230924
MOD83_02230924: ; 0x02230924
	push {r3, lr}
	ldr r1, _02230950 ; =0x000015D4
	ldr r0, [r0, r1]
	cmp r0, #4
	bhi _0223094C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223093A: ; jump table
	.short _0223094C - _0223093A - 2 ; case 0
	.short _02230944 - _0223093A - 2 ; case 1
	.short _0223094C - _0223093A - 2 ; case 2
	.short _0223094C - _0223093A - 2 ; case 3
	.short _0223094C - _0223093A - 2 ; case 4
_02230944:
	bl MOD83_0222F9DC
	bl FUN_02033ED0
_0223094C:
	pop {r3, pc}
	nop
_02230950: .word 0x000015D4
	thumb_func_end MOD83_02230924

	thumb_func_start MOD83_02230954
MOD83_02230954: ; 0x02230954
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD83_02231370
	mov r0, #3
	mov r1, #0x56
	lsl r2, r0, #0x10
	bl CreateHeap
	ldr r1, _022309FC ; =0x00002998
	add r0, r5, #0
	mov r2, #0x56
	bl OverlayManager_CreateAndGetData
	ldr r2, _022309FC ; =0x00002998
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x56
	bl FUN_02016B94
	str r0, [r4]
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	bl MOD83_022331C0
	ldr r0, [r4]
	bl MOD83_02230258
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, _02230A00 ; =0x00000496
	mov r0, #0xa
	mov r2, #1
	bl FUN_0200433C
	mov r0, #0x56
	bl MOD83_SetHeapId
	bl MOD83_02238700
	cmp r0, #0
	beq _022309D0
	ldr r0, _02230A04 ; =0x000015D4
	mov r1, #2
	str r1, [r4, r0]
	ldr r0, _02230A08 ; =gGameVersion
	ldrb r0, [r0]
	bl FUN_02016438
	mov r0, #1
	bl MOD83_02239450
_022309D0:
	ldr r0, _02230A0C ; =0x000005C8
	mov r1, #0x1d
	str r1, [r4, r0]
	add r0, r5, #0
	bl OverlayManager_GetField18
	ldr r0, [r0, #8]
	str r0, [r4, #4]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #8]
	mov r0, #0xff
	mov r2, #3
	str r0, [r4, #0x68]
	mov r0, #0
	mov r1, #0x5b
	lsl r2, r2, #8
	bl CreateHeap
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_022309FC: .word 0x00002998
_02230A00: .word 0x00000496
_02230A04: .word 0x000015D4
_02230A08: .word gGameVersion
_02230A0C: .word 0x000005C8
	thumb_func_end MOD83_02230954

	thumb_func_start MOD83_02230A10
MOD83_02230A10: ; 0x02230A10
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl CTRDG_IsExisting
	ldr r0, _02230D5C ; =0x000005C8
	ldr r0, [r4, r0]
	cmp r0, #0x1d
	beq _02230A30
	add r0, r4, #0
	bl MOD83_022313E4
_02230A30:
	ldr r3, [r5]
	cmp r3, #0x38
	bls _02230A3A
	bl _02231334
_02230A3A:
	add r0, r3, r3
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02230A46: ; jump table
	.short _02230AB8 - _02230A46 - 2 ; case 0
	.short _02230ACA - _02230A46 - 2 ; case 1
	.short _02230AE8 - _02230A46 - 2 ; case 2
	.short _02230AF2 - _02230A46 - 2 ; case 3
	.short _02230B00 - _02230A46 - 2 ; case 4
	.short _02230B0E - _02230A46 - 2 ; case 5
	.short _02231334 - _02230A46 - 2 ; case 6
	.short _02230CA0 - _02230A46 - 2 ; case 7
	.short _02230D50 - _02230A46 - 2 ; case 8
	.short _02230D8C - _02230A46 - 2 ; case 9
	.short _02230E4C - _02230A46 - 2 ; case 10
	.short _02230E9A - _02230A46 - 2 ; case 11
	.short _02230EBC - _02230A46 - 2 ; case 12
	.short _02230F4C - _02230A46 - 2 ; case 13
	.short _02230FA2 - _02230A46 - 2 ; case 14
	.short _02230FCE - _02230A46 - 2 ; case 15
	.short _0223100E - _02230A46 - 2 ; case 16
	.short _02231030 - _02230A46 - 2 ; case 17
	.short _0223105A - _02230A46 - 2 ; case 18
	.short _0223107A - _02230A46 - 2 ; case 19
	.short _0223110E - _02230A46 - 2 ; case 20
	.short _0223111A - _02230A46 - 2 ; case 21
	.short _0223113C - _02230A46 - 2 ; case 22
	.short _02231172 - _02230A46 - 2 ; case 23
	.short _0223118C - _02230A46 - 2 ; case 24
	.short _02231204 - _02230A46 - 2 ; case 25
	.short _02231334 - _02230A46 - 2 ; case 26
	.short _02230B1C - _02230A46 - 2 ; case 27
	.short _02231334 - _02230A46 - 2 ; case 28
	.short _02231334 - _02230A46 - 2 ; case 29
	.short _02231334 - _02230A46 - 2 ; case 30
	.short _02230BD6 - _02230A46 - 2 ; case 31
	.short _02230B28 - _02230A46 - 2 ; case 32
	.short _02230BE8 - _02230A46 - 2 ; case 33
	.short _02230C0A - _02230A46 - 2 ; case 34
	.short _02230C7C - _02230A46 - 2 ; case 35
	.short _02231334 - _02230A46 - 2 ; case 36
	.short _02231334 - _02230A46 - 2 ; case 37
	.short _02231334 - _02230A46 - 2 ; case 38
	.short _02231334 - _02230A46 - 2 ; case 39
	.short _02231334 - _02230A46 - 2 ; case 40
	.short _02231334 - _02230A46 - 2 ; case 41
	.short _02231334 - _02230A46 - 2 ; case 42
	.short _02231334 - _02230A46 - 2 ; case 43
	.short _02231334 - _02230A46 - 2 ; case 44
	.short _02231334 - _02230A46 - 2 ; case 45
	.short _02231334 - _02230A46 - 2 ; case 46
	.short _02231334 - _02230A46 - 2 ; case 47
	.short _02231220 - _02230A46 - 2 ; case 48
	.short _02231244 - _02230A46 - 2 ; case 49
	.short _02231252 - _02230A46 - 2 ; case 50
	.short _0223126E - _02230A46 - 2 ; case 51
	.short _02231284 - _02230A46 - 2 ; case 52
	.short _02231298 - _02230A46 - 2 ; case 53
	.short _022312AA - _02230A46 - 2 ; case 54
	.short _022312EC - _02230A46 - 2 ; case 55
	.short _0223132E - _02230A46 - 2 ; case 56
_02230AB8:
	mov r0, #0x56
	bl MOD83_02238770
	ldr r0, _02230D60 ; =0x000015D8
	str r5, [r4, r0]
	mov r0, #1
	str r0, [r5]
	bl _02231334
_02230ACA:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD83_02230668
	add r0, r4, #0
	bl MOD83_0222FAE8
	mov r0, #1
	mov r1, #3
	add r2, r5, #0
	mov r3, #2
	bl MOD83_0223886C
	bl _02231334
_02230AE8:
	add r0, r5, #0
	bl MOD83_022388CC
	bl _02231334
_02230AF2:
	ldr r2, _02230D64 ; =MOD83_022301D4
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230604
	bl _02231334
_02230B00:
	ldr r2, _02230D68 ; =MOD83_022300F8
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230604
	bl _02231334
_02230B0E:
	ldr r2, _02230D6C ; =MOD83_0222FDE8
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230604
	bl _02231334
_02230B1C:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230714
	bl _02231334
_02230B28:
	add r0, r4, #0
	bl MOD83_022314B4
	ldr r0, _02230D70 ; =MOD83_0223B888
	ldr r0, [r0, #0x10]
	cmp r0, #0x2c
	bne _02230BC0
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	add r0, r6, #0
	bl MOD83_0222FC40
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x8c
	bl MOD83_022332B4
	add r1, r4, #0
	add r1, #0x80
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _02230B6C
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #0x30
	str r0, [r5]
	b _02230BC0
_02230B6C:
	add r0, r4, #0
	add r0, #0x58
	bl WindowIsInUse
	cmp r0, #0
	bne _02230B9A
	mov r0, #2
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x71
	add r1, r4, #0
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x58
	mov r3, #3
	bl AddWindowParameterized
_02230B9A:
	bl MOD83_02239DA0
	add r1, r4, #0
	add r2, r0, #0
	add r0, r6, #0
	add r1, #0x58
	bl MOD83_022305A4
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #4
	bl MOD83_0223050C
	add r0, r6, #0
	bl MOD83_0222FF80
	mov r0, #0x1f
	str r0, [r5]
_02230BC0:
	ldr r0, _02230D70 ; =MOD83_0223B888
	ldr r0, [r0, #0x10]
	sub r0, #0x2d
	cmp r0, #1
	bls _02230BCC
	b _02231334
_02230BCC:
	bl MOD83_02231494
	mov r0, #0x11
	str r0, [r5]
	b _02231334
_02230BD6:
	ldr r2, _02230D74 ; =MOD83_02230084
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230604
	add r0, r4, #0
	bl MOD83_022314B4
	b _02231334
_02230BE8:
	add r0, r6, #0
	bl MOD83_0222FC40
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD83_022391EC
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	add r0, r6, #0
	bl MOD83_0222FCE4
	mov r0, #0x22
	str r0, [r5]
	b _02231334
_02230C0A:
	bl MOD83_02239574
	cmp r0, #4
	bne _02230C16
	bl MOD83_02239544
_02230C16:
	bl MOD83_02239574
	cmp r0, #2
	bne _02230C48
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	ldr r0, _02230D78 ; =0x00000624
	bl FUN_020054C8
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #8
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02230C48:
	bl MOD83_02239574
	cmp r0, #3
	bne _02230D38
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	add r0, r4, #0
	add r0, #0xda
	ldrb r1, [r0]
	mov r0, #4
	mov r2, #0x1a
	bic r1, r0
	add r0, r4, #0
	add r0, #0xda
	strb r1, [r0]
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02230C7C:
	add r0, r4, #0
	bl MOD83_022314B4
	ldr r0, _02230D70 ; =MOD83_0223B888
	ldr r1, [r0, #0x10]
	add r0, r1, #0
	sub r0, #0x2c
	cmp r0, #2
	bhi _02230D38
	cmp r1, #0x2e
	bne _02230C96
	bl MOD83_02231494
_02230C96:
	add r0, r6, #0
	bl MOD83_0222FFD8
	str r0, [r5]
	b _02231334
_02230CA0:
	add r0, r4, #0
	bl MOD83_0222F950
	ldr r1, _02230D7C ; =0x00000438
	str r0, [r4, r1]
	mov r0, #0
	ldr r1, [r4, r1]
	mvn r0, r0
	cmp r1, r0
	beq _02230D20
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x8c
	bl MOD83_022332B4
	add r1, r4, #0
	add r1, #0x80
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x58
	bl WindowIsInUse
	cmp r0, #0
	bne _02230CFA
	mov r0, #2
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x71
	add r1, r4, #0
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x58
	mov r3, #3
	bl AddWindowParameterized
_02230CFA:
	add r1, r4, #0
	add r2, r4, #0
	add r0, r6, #0
	add r1, #0x58
	add r2, #0x8c
	bl MOD83_022305A4
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #4
	bl MOD83_0223050C
	add r0, r6, #0
	mov r1, #0
	bl MOD83_0222FD84
	mov r0, #8
	str r0, [r5]
_02230D20:
	ldr r0, _02230D80 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	bne _02230D3A
	ldr r0, _02230D84 ; =0x00000434
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02230D3A
_02230D38:
	b _02231334
_02230D3A:
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	bl MOD83_0222F9DC
	bl FUN_02033ED0
	mov r0, #0x11
	str r0, [r5]
	b _02231334
_02230D50:
	ldr r2, _02230D88 ; =MOD83_0222FFD8
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230604
	b _02231334
	.align 2, 0
_02230D5C: .word 0x000005C8
_02230D60: .word 0x000015D8
_02230D64: .word MOD83_022301D4
_02230D68: .word MOD83_022300F8
_02230D6C: .word MOD83_0222FDE8
_02230D70: .word MOD83_0223B888
_02230D74: .word MOD83_02230084
_02230D78: .word 0x00000624
_02230D7C: .word 0x00000438
_02230D80: .word gMain
_02230D84: .word 0x00000434
_02230D88: .word MOD83_0222FFD8
_02230D8C:
	bl FUN_02031190
	add r7, r0, #0
	beq _02230DE4
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	beq _02230DE4
	mov r0, #0xab
	bl FUN_020315D8
	cmp r0, #1
	bne _02230E14
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #1
	add r1, r0, #0
	bl FUN_020334E8
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #7
	bl MOD83_0223050C
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FB0C
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	mov r1, #0x96
	ldr r0, _02231120 ; =0x00000434
	lsl r1, r1, #2
	str r1, [r4, r0]
	mov r0, #0xa
	str r0, [r5]
	b _02230E14
_02230DE4:
	cmp r7, #0
	beq _02230E14
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	bne _02230E14
	bl MOD83_0222F9DC
	bl FUN_02033ED0
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #0x10
	str r0, [r5]
	b _02231334
_02230E14:
	ldr r0, _02231124 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	bne _02230E2C
	ldr r0, _02231120 ; =0x00000434
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02230F1C
_02230E2C:
	bl MOD83_0222F9DC
	bl FUN_02033ED0
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #0x11
	str r0, [r5]
	b _02231334
_02230E4C:
	bl MOD83_0222F9A0
	cmp r0, #0
	beq _02230E58
	mov r0, #0xb
	str r0, [r5]
_02230E58:
	bl FUN_02031190
	ldr r1, _02231124 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #2
	tst r1, r2
	bne _02230E84
	ldr r1, _02231120 ; =0x00000434
	ldr r2, [r4, r1]
	sub r2, r2, #1
	str r2, [r4, r1]
	ldr r1, [r4, r1]
	cmp r1, #0
	beq _02230E84
	cmp r0, #0
	beq _02230F1C
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	bne _02230F1C
_02230E84:
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	bl MOD83_0222F9DC
	bl FUN_02033ED0
	mov r0, #0x11
	str r0, [r5]
	b _02231334
_02230E9A:
	add r0, r6, #0
	bl MOD83_0222FC40
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD83_022391EC
	mov r0, #0
	add r1, r0, #0
	bl FUN_020334E8
	add r0, r6, #0
	bl MOD83_0222FCE4
	mov r0, #0xc
	str r0, [r5]
	b _02231334
_02230EBC:
	bl FUN_02031190
	cmp r0, #0
	beq _02230EFA
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	bne _02230EFA
	bl MOD83_0222F9DC
	ldr r0, _02231128 ; =0x00002990
	mov r1, #1
	str r1, [r4, r0]
	bl MOD83_0223955C
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	bl FUN_02033ED0
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	mov r0, #0xe
	str r0, [r5]
	b _02231334
_02230EFA:
	bl MOD83_02239574
	cmp r0, #4
	bne _02230F14
	mov r0, #0x93
	bl FUN_02031588
	mov r0, #0xd
	str r0, [r5]
	ldr r0, _0223112C ; =0x0000043C
	mov r1, #0x78
	str r1, [r4, r0]
	b _02231334
_02230F14:
	bl MOD83_02239574
	cmp r0, #3
	beq _02230F1E
_02230F1C:
	b _02231334
_02230F1E:
	bl MOD83_0223955C
	add r0, r4, #0
	add r0, #0xda
	ldrb r1, [r0]
	mov r0, #4
	bic r1, r0
	add r0, r4, #0
	add r0, #0xda
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #0x1a
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02230F4C:
	mov r0, #0x93
	bl FUN_020315D8
	cmp r0, #1
	bne _02230F66
	bl MOD83_02239544
	ldr r0, _0223112C ; =0x0000043C
	mov r1, #0xa
	str r1, [r4, r0]
	mov r0, #0xf
	str r0, [r5]
	b _02231334
_02230F66:
	ldr r0, _0223112C ; =0x0000043C
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02231062
	bl MOD83_0223955C
	add r0, r4, #0
	add r0, #0xda
	ldrb r1, [r0]
	mov r0, #4
	bic r1, r0
	add r0, r4, #0
	add r0, #0xda
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #0x1a
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02230FA2:
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r4, #0
	add r0, #0xda
	ldrb r1, [r0]
	mov r0, #4
	mov r2, #0x1c
	bic r1, r0
	add r0, r4, #0
	add r0, #0xda
	strb r1, [r0]
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02230FCE:
	ldr r0, _0223112C ; =0x0000043C
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02231062
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	bl MOD83_0222F9DC
	bl FUN_02033ED0
	ldr r0, _02231130 ; =0x00000624
	bl FUN_020054C8
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #8
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_0223100E:
	ldr r0, _02231134 ; =0x000005DC
	bl FUN_020054C8
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #0x18
	bl MOD83_0223050C
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl MOD83_0222FB44
	mov r0, #0x12
	str r0, [r5]
	b _02231334
_02231030:
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	ldr r0, _02231134 ; =0x000005DC
	bl FUN_020054C8
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #0x17
	bl MOD83_0223050C
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl MOD83_0222FB44
	mov r0, #0x12
	str r0, [r5]
	b _02231334
_0223105A:
	ldr r0, _02231124 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	bne _02231064
_02231062:
	b _02231334
_02231064:
	ldr r0, _02231134 ; =0x000005DC
	bl FUN_020054C8
	add r0, r6, #0
	mov r1, #0xc4
	mov r2, #0
	bl MOD83_02230464
	mov r0, #3
	str r0, [r5]
	b _02231334
_0223107A:
	add r0, r4, #0
	add r0, #0x84
	ldr r0, [r0]
	cmp r0, #0x1b
	beq _02231090
	add r0, r4, #0
	mov r1, #0xea
	add r0, #0x8c
	lsl r1, r1, #2
	bl MOD83_02238728
_02231090:
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #0x8c
	bl MOD83_022332B4
	add r1, r4, #0
	add r1, #0x80
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _022310B8
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r0, #0x30
	str r0, [r5]
	b _02231334
_022310B8:
	add r0, r4, #0
	add r0, #0x58
	bl WindowIsInUse
	cmp r0, #0
	bne _022310E6
	mov r0, #2
	str r0, [sp]
	mov r0, #0x1a
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #0x71
	add r1, r4, #0
	str r2, [sp, #0xc]
	lsl r0, r0, #2
	str r0, [sp, #0x10]
	ldr r0, [r4]
	add r1, #0x58
	mov r3, #3
	bl AddWindowParameterized
_022310E6:
	add r1, r4, #0
	add r2, r4, #0
	add r0, r6, #0
	add r1, #0x58
	add r2, #0x8c
	bl MOD83_022305A4
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #4
	bl MOD83_0223050C
	add r0, r6, #0
	mov r1, #0
	bl MOD83_0222FD84
	mov r0, #0x14
	str r0, [r5]
	b _02231334
_0223110E:
	ldr r2, _02231138 ; =MOD83_0222FFD8
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02230604
	b _02231334
_0223111A:
	mov r0, #0x16
	str r0, [r5]
	b _02231334
	.align 2, 0
_02231120: .word 0x00000434
_02231124: .word gMain
_02231128: .word 0x00002990
_0223112C: .word 0x0000043C
_02231130: .word 0x00000624
_02231134: .word 0x000005DC
_02231138: .word MOD83_0222FFD8
_0223113C:
	add r0, r6, #0
	bl MOD83_0222FC40
	add r1, r0, #0
	ldr r0, [r4]
	bl MOD83_022391EC
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #7
	bl MOD83_0223050C
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FB0C
	add r0, r4, #0
	mov r1, #1
	bl MOD83_0222FA0C
	ldr r0, _0223134C ; =0x0000043C
	mov r1, #0x3c
	str r1, [r4, r0]
	mov r0, #0x17
	str r0, [r5]
	b _02231334
_02231172:
	ldr r0, _0223134C ; =0x0000043C
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02231212
	add r0, r6, #0
	bl MOD83_0222FCE4
	mov r0, #0x18
	str r0, [r5]
	b _02231334
_0223118C:
	bl MOD83_02239574
	cmp r0, #4
	bne _02231198
	bl MOD83_02239544
_02231198:
	bl MOD83_02239574
	cmp r0, #2
	bne _022311D0
	ldr r0, _0223134C ; =0x0000043C
	mov r1, #1
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #0
	bl MOD83_0222FA0C
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	ldr r0, _02231350 ; =0x00000624
	bl FUN_020054C8
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r2, #8
	mov r3, #0x19
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_022311D0:
	bl MOD83_02239574
	cmp r0, #3
	bne _02231212
	mov r1, #0
	add r0, r4, #0
	mvn r1, r1
	bl MOD83_0222FB0C
	add r0, r4, #0
	add r0, #0xda
	ldrb r1, [r0]
	mov r0, #4
	mov r2, #0x1a
	bic r1, r0
	add r0, r4, #0
	add r0, #0xda
	strb r1, [r0]
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x18
	mov r3, #0x36
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02231204:
	ldr r0, _0223134C ; =0x0000043C
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02231214
_02231212:
	b _02231334
_02231214:
	mov r1, #1
	lsl r1, r1, #0x10
	str r1, [r4, r0]
	mov r0, #0x36
	str r0, [r5]
	b _02231334
_02231220:
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #5
	beq _02231230
	add r0, r4, #0
	bl MOD83_02230924
_02231230:
	add r0, r6, #0
	bl MOD83_0223084C
	str r0, [r5]
	add r0, r4, #0
	add r0, #0x48
	mov r1, #0
	bl MOD83_0222FB44
	b _02231334
_02231244:
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	bl MOD83_0223089C
	str r0, [r5]
	b _02231334
_02231252:
	ldr r0, _02231354 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _02231334
	add r0, r4, #0
	add r0, #0x58
	mov r1, #0
	bl MOD83_0222FB44
	add r0, r6, #0
	bl MOD83_022300F8
	str r0, [r5]
	b _02231334
_0223126E:
	add r0, r6, #0
	mov r1, #1
	bl MOD83_0222FD84
	mov r0, #8
	str r0, [r5]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x80
	str r1, [r0]
	b _02231334
_02231284:
	add r0, r6, #0
	bl MOD83_0222FA4C
	mov r0, #0x11
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02231298:
	add r0, r6, #0
	bl MOD83_0222FA4C
	mov r1, #0x11
	mov r0, #1
	lsl r1, r1, #6
	add sp, #0x14
	str r0, [r4, r1]
	pop {r4, r5, r6, r7, pc}
_022312AA:
	ldr r0, _02231354 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _02231334
	ldr r0, _02231358 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0xda
	ldrb r0, [r0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _022312D6
	ldr r2, _0223135C ; =0x000015D8
	mov r0, #0
	ldr r2, [r4, r2]
	mov r1, #0x37
	mov r3, #2
	bl MOD83_0223886C
	b _02231334
_022312D6:
	mov r0, #1
	bl MOD83_02238860
	ldr r2, _0223135C ; =0x000015D8
	mov r0, #0
	ldr r2, [r4, r2]
	mov r1, #0x38
	mov r3, #2
	bl MOD83_0223886C
	b _02231334
_022312EC:
	ldr r0, [r4]
	bl MOD83_022302B4
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineBToggleLayers
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0xdc
	mov r2, #0x56
	bl MOD83_02233168
	ldr r2, _0223135C ; =0x000015D8
	mov r0, #1
	ldr r2, [r4, r2]
	mov r1, #0x36
	mov r3, #2
	bl MOD83_0223886C
	add r0, r4, #0
	add r0, #0xda
	ldrb r1, [r0]
	mov r0, #4
	bic r1, r0
	add r0, r4, #0
	add r0, #0xda
	strb r1, [r0]
	b _02231334
_0223132E:
	mov r0, #0
	bl OS_ResetSystem
_02231334:
	ldr r0, _02231360 ; =0x0000298C
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02231340
	add r0, r4, #0
	blx r1
_02231340:
	bl MOD83_02238D58
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0223134C: .word 0x0000043C
_02231350: .word 0x00000624
_02231354: .word gMain
_02231358: .word 0x000005DC
_0223135C: .word 0x000015D8
_02231360: .word 0x0000298C
	thumb_func_end MOD83_02230A10

	thumb_func_start MOD83_02231364
MOD83_02231364: ; 0x02231364
	ldr r0, _0223136C ; =MOD83_0223B888
	ldr r0, [r0, #4]
	bx lr
	nop
_0223136C: .word MOD83_0223B888
	thumb_func_end MOD83_02231364

	thumb_func_start MOD83_02231370
MOD83_02231370: ; 0x02231370
	ldr r1, _02231378 ; =MOD83_0223B888
	str r0, [r1, #4]
	bx lr
	nop
_02231378: .word MOD83_0223B888
	thumb_func_end MOD83_02231370

	thumb_func_start MOD83_0223137C
MOD83_0223137C: ; 0x0223137C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	mov r0, #0x11
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0223139A
	ldr r0, _022313D0 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _022313D4 ; =MOD63_021DBAB8
	bl RegisterMainOverlay
	b _022313A6
_0223139A:
	cmp r0, #1
	bne _022313A6
	ldr r0, _022313D8 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _022313DC ; =MOD83_0223A444
	bl RegisterMainOverlay
_022313A6:
	mov r0, #0x5b
	bl DestroyHeap
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0x56
	bl DestroyHeap
	ldr r0, _022313E0 ; =0x000015D4
	ldr r0, [r4, r0]
	cmp r0, #2
	bne _022313C6
	mov r0, #0
	bl FUN_02016438
_022313C6:
	mov r0, #0
	bl MOD83_02239450
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_022313D0: .word SDK_OVERLAY_MODULE_63_ID
_022313D4: .word MOD63_021DBAB8
_022313D8: .word SDK_OVERLAY_MODULE_83_ID
_022313DC: .word MOD83_0223A444
_022313E0: .word 0x000015D4
	thumb_func_end MOD83_0223137C

	thumb_func_start MOD83_022313E4
MOD83_022313E4: ; 0x022313E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02231438 ; =0x000005C8
	ldr r0, [r4, r0]
	cmp r0, #0x1c
	beq _022313FA
	cmp r0, #0x1d
	beq _02231436
	cmp r0, #0x1e
	beq _0223140E
	pop {r4, pc}
_022313FA:
	ldr r0, [r4, #4]
	bl FUN_02032D44
	ldr r0, _0223143C ; =0x000005CC
	mov r1, #0x78
	str r1, [r4, r0]
	mov r1, #0x1e
	sub r0, r0, #4
	str r1, [r4, r0]
	pop {r4, pc}
_0223140E:
	bl FUN_02032D9C
	mov r1, #1
	tst r0, r1
	beq _0223141E
	mov r0, #0x5d
	lsl r0, r0, #4
	str r1, [r4, r0]
_0223141E:
	ldr r0, _0223143C ; =0x000005CC
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02231436
	bl FUN_02032D80
	ldr r0, _02231438 ; =0x000005C8
	mov r1, #0x1d
	str r1, [r4, r0]
_02231436:
	pop {r4, pc}
	.align 2, 0
_02231438: .word 0x000005C8
_0223143C: .word 0x000005CC
	thumb_func_end MOD83_022313E4

	thumb_func_start MOD83_02231440
MOD83_02231440: ; 0x02231440
	cmp r0, #4
	bhi _0223148C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02231450: ; jump table
	.short _0223145A - _02231450 - 2 ; case 0
	.short _02231462 - _02231450 - 2 ; case 1
	.short _0223146A - _02231450 - 2 ; case 2
	.short _02231472 - _02231450 - 2 ; case 3
	.short _02231486 - _02231450 - 2 ; case 4
_0223145A:
	ldr r0, _02231490 ; =MOD83_0223B888
	mov r1, #0x27
	str r1, [r0, #0x10]
	bx lr
_02231462:
	ldr r0, _02231490 ; =MOD83_0223B888
	mov r1, #0x28
	str r1, [r0, #0x10]
	bx lr
_0223146A:
	ldr r0, _02231490 ; =MOD83_0223B888
	mov r1, #0x29
	str r1, [r0, #0x10]
	bx lr
_02231472:
	ldr r0, _02231490 ; =MOD83_0223B888
	ldr r1, [r0, #0x10]
	cmp r1, #0x29
	bne _02231480
	mov r1, #0x2b
	str r1, [r0, #0x10]
	bx lr
_02231480:
	mov r1, #0x2e
	str r1, [r0, #0x10]
	bx lr
_02231486:
	ldr r0, _02231490 ; =MOD83_0223B888
	mov r1, #0x2f
	str r1, [r0, #0x10]
_0223148C:
	bx lr
	nop
_02231490: .word MOD83_0223B888
	thumb_func_end MOD83_02231440

	thumb_func_start MOD83_02231494
MOD83_02231494: ; 0x02231494
	push {r3, lr}
	bl FUN_0202E4F0
	ldr r0, _022314B0 ; =MOD83_0223B888
	ldr r0, [r0, #8]
	bl FreeToHeap
	bl FUN_02033ED0
	ldr r0, _022314B0 ; =MOD83_0223B888
	mov r1, #0
	str r1, [r0, #8]
	pop {r3, pc}
	nop
_022314B0: .word MOD83_0223B888
	thumb_func_end MOD83_02231494

	thumb_func_start MOD83_022314B4
MOD83_022314B4: ; 0x022314B4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022315C0 ; =MOD83_0223B888
	ldr r0, [r0, #0x10]
	cmp r0, #0x2b
	bne _022314DA
	bl MOD83_02231494
	bl MOD83_02239CEC
	cmp r0, #0
	beq _022314D4
	ldr r0, _022315C0 ; =MOD83_0223B888
	mov r1, #0x2c
	str r1, [r0, #0x10]
	b _022314DA
_022314D4:
	ldr r0, _022315C0 ; =MOD83_0223B888
	mov r1, #0x2d
	str r1, [r0, #0x10]
_022314DA:
	ldr r0, _022315C0 ; =MOD83_0223B888
	ldr r0, [r0, #0x10]
	cmp r0, #0x24
	beq _022314F6
	cmp r0, #0x25
	beq _022314F6
	cmp r0, #0x26
	beq _022314F6
	cmp r0, #0x27
	beq _022314F6
	cmp r0, #0x28
	beq _022314F6
	cmp r0, #0x2a
	bne _02231502
_022314F6:
	bl WM_GetLinkLevel
	mov r1, #3
	sub r0, r1, r0
	bl FUN_02033EEC
_02231502:
	ldr r1, _022315C0 ; =MOD83_0223B888
	ldr r0, [r1, #0x10]
	sub r0, #0x24
	cmp r0, #0xb
	bhi _0223157C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02231518: ; jump table
	.short _02231530 - _02231518 - 2 ; case 0
	.short _0223153C - _02231518 - 2 ; case 1
	.short _0223157C - _02231518 - 2 ; case 2
	.short _0223157C - _02231518 - 2 ; case 3
	.short _02231572 - _02231518 - 2 ; case 4
	.short _0223157C - _02231518 - 2 ; case 5
	.short _0223157C - _02231518 - 2 ; case 6
	.short _0223157C - _02231518 - 2 ; case 7
	.short _0223157C - _02231518 - 2 ; case 8
	.short _0223157C - _02231518 - 2 ; case 9
	.short _0223157A - _02231518 - 2 ; case 10
	.short _0223157C - _02231518 - 2 ; case 11
_02231530:
	bl FUN_0202E49C
	ldr r0, _022315C0 ; =MOD83_0223B888
	mov r1, #0x25
	str r1, [r0, #0x10]
	b _0223157C
_0223153C:
	bl FUN_0202E4C8
	cmp r0, #1
	bne _0223157C
	ldr r0, _022315C0 ; =MOD83_0223B888
	mov r1, #0
	str r1, [r0]
	bl MOD83_02239D98
	add r1, r0, #0
	mov r0, #0x56
	bl AllocFromHeap
	add r2, r0, #0
	ldr r0, _022315C0 ; =MOD83_0223B888
	ldr r1, _022315C4 ; =MOD83_02231440
	str r2, [r0, #8]
	ldr r0, _022315C8 ; =0x000005D4
	add r0, r4, r0
	bl MOD83_02239A98
	ldr r0, _022315C0 ; =MOD83_0223B888
	mov r1, #0x26
	str r1, [r0, #0x10]
	bl FUN_02033E74
	b _0223157C
_02231572:
	ldr r0, [r1]
	add r0, r0, #1
	str r0, [r1]
	b _0223157C
_0223157A:
	pop {r4, pc}
_0223157C:
	ldr r0, _022315CC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _022315BC
	ldr r0, _022315C0 ; =MOD83_0223B888
	ldr r0, [r0, #0x10]
	sub r0, #0x27
	cmp r0, #8
	bhi _022315BC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223159C: ; jump table
	.short _022315AE - _0223159C - 2 ; case 0
	.short _022315AE - _0223159C - 2 ; case 1
	.short _022315BC - _0223159C - 2 ; case 2
	.short _022315BC - _0223159C - 2 ; case 3
	.short _022315BC - _0223159C - 2 ; case 4
	.short _022315BC - _0223159C - 2 ; case 5
	.short _022315BC - _0223159C - 2 ; case 6
	.short _022315BC - _0223159C - 2 ; case 7
	.short _022315AE - _0223159C - 2 ; case 8
_022315AE:
	bl MOD83_02239A14
	cmp r0, #0
	beq _022315BC
	ldr r0, _022315C0 ; =MOD83_0223B888
	mov r1, #0x2a
	str r1, [r0, #0x10]
_022315BC:
	pop {r4, pc}
	nop
_022315C0: .word MOD83_0223B888
_022315C4: .word MOD83_02231440
_022315C8: .word 0x000005D4
_022315CC: .word gMain
	thumb_func_end MOD83_022314B4

	thumb_func_start MOD83_022315D0
MOD83_022315D0: ; 0x022315D0
	push {r3, lr}
	sub sp, #8
	bl MOD83_022315F8
	bl MOD83_02238AFC
	bl MOD83_02238B4C
	mov r0, #0xd
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0xf
	mov r2, #0xc
	mov r3, #0xe
	bl MOD83_02238BC4
	add sp, #8
	pop {r3, pc}
	thumb_func_end MOD83_022315D0

	thumb_func_start MOD83_022315F8
MOD83_022315F8: ; 0x022315F8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0223165C ; =0x00002D64
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02231608
	bl FUN_0201FFC8
_02231608:
	ldr r0, _02231660 ; =0x00002D68
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02231614
	bl FUN_0201FFC8
_02231614:
	ldr r0, _02231660 ; =0x00002D68
	mov r1, #0
	str r1, [r4, r0]
	ldr r2, [r4, r0]
	sub r1, r0, #4
	str r2, [r4, r1]
	add r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223162C
	bl FUN_0201FFC8
_0223162C:
	ldr r0, _02231664 ; =0x00002D70
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02231638
	bl FUN_0201FFC8
_02231638:
	ldr r0, _02231668 ; =0x00002D74
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02231644
	bl FUN_0201FFC8
_02231644:
	ldr r1, _02231668 ; =0x00002D74
	mov r0, #0
	str r0, [r4, r1]
	ldr r2, [r4, r1]
	sub r0, r1, #4
	str r2, [r4, r0]
	ldr r0, [r4, r0]
	sub r1, #8
	str r0, [r4, r1]
	bl MOD83_02238E48
	pop {r4, pc}
	.align 2, 0
_0223165C: .word 0x00002D64
_02231660: .word 0x00002D68
_02231664: .word 0x00002D70
_02231668: .word 0x00002D74
	thumb_func_end MOD83_022315F8

	thumb_func_start MOD83_0223166C
MOD83_0223166C: ; 0x0223166C
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _022316B4 ; =0x00003CEC
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, r1]
	mov r1, #1
	str r1, [sp]
	ldr r1, _022316B8 ; =0x00002D64
	mov r2, #0x48
	ldr r1, [r4, r1]
	mov r3, #0xa8
	bl MOD83_02238DBC
	ldr r1, _022316B8 ; =0x00002D64
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #2
	bl FUN_02020238
	mov r0, #0
	ldr r1, _022316BC ; =0x00002D68
	str r0, [sp]
	ldr r1, [r4, r1]
	mov r2, #0xb8
	mov r3, #0xa8
	bl MOD83_02238DBC
	ldr r1, _022316BC ; =0x00002D68
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #2
	bl FUN_02020238
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_022316B4: .word 0x00003CEC
_022316B8: .word 0x00002D64
_022316BC: .word 0x00002D68
	thumb_func_end MOD83_0223166C

	thumb_func_start MOD83_022316C0
MOD83_022316C0: ; 0x022316C0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl WindowIsInUse
	cmp r0, #1
	bne _022316D6
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200CCF8
_022316D6:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_022316C0

	thumb_func_start MOD83_022316D8
MOD83_022316D8: ; 0x022316D8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl WindowIsInUse
	cmp r0, #1
	bne _022316EE
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0200D0E0
_022316EE:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_022316D8

	thumb_func_start MOD83_022316F0
MOD83_022316F0: ; 0x022316F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, _02231794 ; =0x00002B6C
	add r4, r1, #0
	ldr r0, [r5, r0]
	add r7, r2, #0
	str r3, [sp]
	cmp r0, #0
	beq _02231708
	bl ListMenuItems_dtor
_02231708:
	ldr r0, _02231798 ; =0x00002B68
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02231718
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
_02231718:
	add r0, r7, #0
	mov r1, #0x57
	bl ListMenuItems_ctor
	ldr r1, _02231794 ; =0x00002B6C
	ldr r2, _0223179C ; =0x00000172
	str r0, [r5, r1]
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x57
	bl NewMsgDataFromNarc
	ldr r1, _022317A0 ; =0x000029A4
	mov r6, #0
	str r0, [r5, r1]
	cmp r7, #0
	ble _02231752
_0223173A:
	ldr r0, _02231794 ; =0x00002B6C
	ldr r1, _022317A0 ; =0x000029A4
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r4, #8
	cmp r6, r7
	blt _0223173A
_02231752:
	ldr r0, _022317A0 ; =0x000029A4
	ldr r0, [r5, r0]
	bl DestroyMsgData
	ldr r4, _022317A4 ; =MOD83_0223AE90
	add r3, sp, #4
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, _02231794 ; =0x00002B6C
	mov r1, #0
	ldr r0, [r5, r0]
	mov r3, #0x57
	str r0, [sp, #4]
	add r0, sp, #4
	strh r7, [r0, #0x10]
	ldr r0, [sp]
	str r0, [sp, #0x10]
	add r0, r2, #0
	add r2, r1, #0
	bl ListMenuInit
	ldr r1, _02231798 ; =0x00002B68
	str r0, [r5, r1]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02231794: .word 0x00002B6C
_02231798: .word 0x00002B68
_0223179C: .word 0x00000172
_022317A0: .word 0x000029A4
_022317A4: .word MOD83_0223AE90
	thumb_func_end MOD83_022316F0

	thumb_func_start MOD83_022317A8
MOD83_022317A8: ; 0x022317A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r2, _02231818 ; =0x00000172
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x57
	bl NewMsgDataFromNarc
	add r4, r0, #0
	mov r0, #0x57
	bl ScrStrBufs_new
	add r6, r0, #0
	mov r0, #1
	mov r1, #6
	bl GetFontAttribute
	add r1, r0, #0
	add r0, r5, #0
	bl FillWindowPixelBuffer
	add r0, r6, #0
	add r1, r4, #0
	add r2, r7, #0
	mov r3, #0x57
	bl ReadMsgData_ExpandPlaceholders
	add r7, r0, #0
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _0223181C ; =0x00010200
	mov r1, #1
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r7, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r5, #0
	bl CopyWindowToVram
	add r0, r7, #0
	bl String_dtor
	add r0, r4, #0
	bl DestroyMsgData
	add r0, r6, #0
	bl ScrStrBufs_delete
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02231818: .word 0x00000172
_0223181C: .word 0x00010200
	thumb_func_end MOD83_022317A8

	thumb_func_start MOD83_02231820
MOD83_02231820: ; 0x02231820
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x57
	mov r3, #0x1e
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0xb
	mov r2, #0
	lsl r3, r3, #4
	bl GfGfxLoader_GXLoadPal
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x57
	mov r3, #6
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x10
	mov r2, #0
	lsl r3, r3, #6
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x57
	str r0, [sp, #0xc]
	mov r0, #0x74
	mov r1, #0x11
	add r2, r4, #0
	bl GfGfxLoader_LoadCharData
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x57
	str r0, [sp, #0xc]
	mov r0, #0x74
	mov r1, #0x12
	add r2, r4, #0
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0xc
	mov r2, #0
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #1
	add r3, r2, #0
	bl FUN_020186B4
	add r0, r4, #0
	mov r1, #1
	bl FUN_02017CD0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02231820

	thumb_func_start MOD83_022318B0
MOD83_022318B0: ; 0x022318B0
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD83_02231A00
	ldr r0, _022318DC ; =0x00002B70
	mov r1, #0x2e
	add r0, r4, r0
	bl MOD83_022317A8
	mov r3, #0xae
	lsl r3, r3, #6
	add r1, r4, r3
	add r3, #0x10
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r2, #0xa
	bl MOD83_02231F88
	mov r0, #0xd
	pop {r4, pc}
	.align 2, 0
_022318DC: .word 0x00002B70
	thumb_func_end MOD83_022318B0

	thumb_func_start MOD83_022318E0
MOD83_022318E0: ; 0x022318E0
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD83_02231A00
	mov r1, #0xad
	lsl r1, r1, #6
	ldr r0, [r4, r1]
	add r1, #0x20
	ldr r1, [r4, r1]
	add r1, r1, #1
	bl FUN_0202AE90
	cmp r0, #1
	ldr r0, _0223192C ; =0x00002B70
	bne _0223190C
	add r0, r4, r0
	mov r1, #0x3e
	bl MOD83_022317A8
	b _02231914
_0223190C:
	add r0, r4, r0
	mov r1, #0x3d
	bl MOD83_022317A8
_02231914:
	mov r3, #0xae
	lsl r3, r3, #6
	add r1, r4, r3
	add r3, #0x10
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r2, #9
	bl MOD83_02231F88
	mov r0, #0xc
	pop {r4, pc}
	nop
_0223192C: .word 0x00002B70
	thumb_func_end MOD83_022318E0

	thumb_func_start MOD83_02231930
MOD83_02231930: ; 0x02231930
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD83_02231A00
	ldr r0, _022319C0 ; =0x00002B70
	mov r1, #0x3f
	add r0, r4, r0
	bl MOD83_022317A8
	ldr r0, _022319C0 ; =0x00002B70
	mov r1, #0x13
	add r0, r4, r0
	bl FUN_0200D858
	ldr r1, _022319C4 ; =0x00003CF0
	str r0, [r4, r1]
	mov r1, #0xad
	lsl r1, r1, #6
	ldr r0, [r4, r1]
	add r1, #0x20
	ldr r1, [r4, r1]
	bl FUN_0202ADC8
	ldr r0, _022319C8 ; =0x00002B44
	ldr r0, [r4, r0]
	bl FUN_02022720
	ldr r0, _022319C4 ; =0x00003CF0
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	mov r0, #0xad
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl FUN_0202AE70
	cmp r0, #0
	bne _02231984
	mov r0, #0x1a
	pop {r4, pc}
_02231984:
	ldr r1, _022319CC ; =0x00002B60
	add r0, r4, #0
	ldr r1, [r4, r1]
	mov r2, #1
	bl MOD83_022320A4
	ldr r1, _022319CC ; =0x00002B60
	str r0, [r4, r1]
	add r1, #0x10
	add r0, r4, r1
	mov r1, #0x24
	bl MOD83_022317A8
	mov r3, #0xae
	lsl r3, r3, #6
	add r1, r4, r3
	add r3, #0x10
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r2, #8
	bl MOD83_02231F88
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD83_02231DF0
	mov r0, #5
	pop {r4, pc}
	nop
_022319C0: .word 0x00002B70
_022319C4: .word 0x00003CF0
_022319C8: .word 0x00002B44
_022319CC: .word 0x00002B60
	thumb_func_end MOD83_02231930

	thumb_func_start MOD83_022319D0
MOD83_022319D0: ; 0x022319D0
	push {r4, lr}
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD83_02231A00
	ldr r0, _022319FC ; =0x00002B70
	mov r1, #0x24
	add r0, r4, r0
	bl MOD83_022317A8
	mov r3, #0xae
	lsl r3, r3, #6
	add r1, r4, r3
	add r3, #0x10
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r2, #8
	bl MOD83_02231F88
	mov r0, #5
	pop {r4, pc}
	.align 2, 0
_022319FC: .word 0x00002B70
	thumb_func_end MOD83_022319D0

	thumb_func_start MOD83_02231A00
MOD83_02231A00: ; 0x02231A00
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02231A40 ; =0x00002B6C
	ldr r0, [r4, r0]
	bl ListMenuItems_dtor
	mov r1, #0
	ldr r0, _02231A40 ; =0x00002B6C
	add r2, r1, #0
	str r1, [r4, r0]
	sub r0, r0, #4
	ldr r0, [r4, r0]
	bl DestroyListMenu
	ldr r0, _02231A44 ; =0x00002B68
	mov r1, #0
	str r1, [r4, r0]
	add r0, #0x18
	add r0, r4, r0
	bl MOD83_022316C0
	mov r0, #0xae
	lsl r0, r0, #6
	add r0, r4, r0
	bl FUN_02019570
	mov r0, #0xae
	lsl r0, r0, #6
	add r0, r4, r0
	bl RemoveWindow
	pop {r4, pc}
	.align 2, 0
_02231A40: .word 0x00002B6C
_02231A44: .word 0x00002B68
	thumb_func_end MOD83_02231A00

	thumb_func_start MOD83_02231A48
MOD83_02231A48: ; 0x02231A48
	mov r0, #1
	bx lr
	thumb_func_end MOD83_02231A48

	thumb_func_start MOD83_02231A4C
MOD83_02231A4C: ; 0x02231A4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r7, r1, #0
	ldr r1, [r5]
	mov r0, #0x25
	add r4, r2, #0
	bl String_ctor
	ldr r1, _02231A9C ; =0x00002B60
	add r6, r0, #0
	ldr r2, [r5, r1]
	sub r1, #0xc
	lsl r2, r2, #2
	add r2, r5, r2
	ldr r2, [r2, r1]
	mov r1, #0x41
	lsl r1, r1, #2
	add r1, r2, r1
	mov r2, #0x24
	bl CopyU16ArrayToStringN
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r4, [sp, #8]
	add r0, r7, #0
	mov r1, #1
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02231A9C: .word 0x00002B60
	thumb_func_end MOD83_02231A4C

	thumb_func_start MOD83_02231AA0
MOD83_02231AA0: ; 0x02231AA0
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, _02231B10 ; =0x00002B60
	add r6, r1, #0
	ldr r1, [r4, r0]
	add r5, r2, #0
	lsl r2, r1, #2
	add r3, r4, r2
	add r2, r0, #0
	sub r2, #0xc
	ldr r3, [r3, r2]
	ldr r2, _02231B14 ; =0x00000152
	ldrb r2, [r3, r2]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1f
	bne _02231AC6
	mov r2, #0x27
	b _02231ADE
_02231AC6:
	sub r0, #0x20
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02231AD8
	add r1, r1, #1
	bl FUN_0202AE90
	cmp r0, #1
	bne _02231ADC
_02231AD8:
	mov r2, #0x25
	b _02231ADE
_02231ADC:
	mov r2, #0x26
_02231ADE:
	ldr r1, _02231B18 ; =0x000029A0
	ldr r3, [r4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl ReadMsgData_ExpandPlaceholders
	add r4, r0, #0
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r5, [sp, #8]
	add r0, r6, #0
	mov r1, #1
	add r2, r4, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	mov r0, #1
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_02231B10: .word 0x00002B60
_02231B14: .word 0x00000152
_02231B18: .word 0x000029A0
	thumb_func_end MOD83_02231AA0

	thumb_func_start MOD83_02231B1C
MOD83_02231B1C: ; 0x02231B1C
	push {r4, lr}
	sub sp, #0x18
	ldr r1, _02231B7C ; =0x00002B60
	add r4, r0, #0
	ldr r2, [r4, r1]
	sub r1, #0xc
	lsl r2, r2, #2
	add r2, r4, r2
	ldr r2, [r2, r1]
	mov r1, #0xd5
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	add r0, sp, #8
	bl RTC_ConvertDayToDate
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02231B80 ; =0x000029A0
	mov r2, #0x7d
	ldr r3, [sp, #8]
	lsl r2, r2, #4
	add r2, r3, r2
	ldr r0, [r4, r0]
	mov r1, #0
	mov r3, #4
	bl BufferIntegerAsString
	ldr r0, _02231B80 ; =0x000029A0
	ldr r2, [sp, #0xc]
	ldr r0, [r4, r0]
	mov r1, #1
	bl BufferMonthNameAbbr
	mov r1, #2
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02231B80 ; =0x000029A0
	ldr r2, [sp, #0x10]
	ldr r0, [r4, r0]
	add r3, r1, #0
	bl BufferIntegerAsString
	mov r0, #1
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_02231B7C: .word 0x00002B60
_02231B80: .word 0x000029A0
	thumb_func_end MOD83_02231B1C

	thumb_func_start MOD83_02231B84
MOD83_02231B84: ; 0x02231B84
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #0xfb
	mov r1, #0x57
	add r4, r2, #0
	bl String_ctor
	ldr r1, _02231BD4 ; =0x00002B60
	add r6, r0, #0
	ldr r2, [r5, r1]
	sub r1, #0xc
	lsl r2, r2, #2
	add r2, r5, r2
	ldr r2, [r2, r1]
	mov r1, #0x55
	lsl r1, r1, #2
	add r1, r2, r1
	mov r2, #0xfa
	bl CopyU16ArrayToStringN
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r4, [sp, #8]
	add r0, r7, #0
	mov r1, #1
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r6, #0
	bl String_dtor
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02231BD4: .word 0x00002B60
	thumb_func_end MOD83_02231B84

	thumb_func_start MOD83_02231BD8
MOD83_02231BD8: ; 0x02231BD8
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r3, r0, #0
	ldr r0, _02231C50 ; =0x00002B60
	add r6, r1, #0
	ldr r1, [r3, r0]
	sub r0, #0xc
	lsl r1, r1, #2
	add r1, r3, r1
	ldr r1, [r1, r0]
	mov r0, #0xd2
	lsl r0, r0, #2
	add r5, r2, #0
	ldrb r2, [r1, r0]
	cmp r2, #0xff
	bne _02231C2C
	ldr r1, _02231C54 ; =0x000029A0
	mov r2, #0x33
	ldr r0, [r3, r1]
	add r1, r1, #4
	ldr r1, [r3, r1]
	mov r3, #0x57
	bl ReadMsgData_ExpandPlaceholders
	add r4, r0, #0
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r5, [sp, #8]
	add r0, r6, #0
	mov r1, #1
	add r2, r4, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl String_dtor
	add sp, #0x10
	mov r0, #0
	pop {r4, r5, r6, pc}
_02231C2C:
	cmp r2, #0
	beq _02231C48
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _02231C54 ; =0x000029A0
	ldr r0, [r3, r0]
	mov r3, #3
	bl BufferIntegerAsString
	add sp, #0x10
	mov r0, #1
	pop {r4, r5, r6, pc}
_02231C48:
	mov r0, #0
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_02231C50: .word 0x00002B60
_02231C54: .word 0x000029A0
	thumb_func_end MOD83_02231BD8

	thumb_func_start MOD83_02231C58
MOD83_02231C58: ; 0x02231C58
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #0
	add r7, r1, #0
	add r1, r0, #1
	ldr r0, _02231D38 ; =MOD83_0223AE40
	ldr r2, _02231D38 ; =MOD83_0223AE40
	ldr r0, [r0, #0x30]
	ldr r2, [r2, #0x34]
	str r0, [sp, #0x14]
	ldr r0, _02231D3C ; =0x00002B60
	str r2, [sp, #0x18]
	ldr r2, [r5, r0]
	sub r0, #0xc
	lsl r2, r2, #2
	add r2, r5, r2
	ldr r2, [r2, r0]
	mov r0, #0xd2
	lsl r0, r0, #2
	ldrb r0, [r2, r0]
	add r4, r1, #0
	add r6, sp, #0x14
	cmp r0, #0
	beq _02231C9C
	ldr r0, _02231D38 ; =MOD83_0223AE40
	ldr r2, _02231D38 ; =MOD83_0223AE40
	ldr r0, [r0, #0x38]
	add r4, r1, #1
	lsl r1, r1, #3
	ldr r2, [r2, #0x3c]
	add r3, r6, r1
	str r0, [r6, r1]
	str r2, [r3, #4]
_02231C9C:
	mov r1, #0xad
	lsl r1, r1, #6
	ldr r0, [r5, r1]
	add r1, #0x20
	ldr r1, [r5, r1]
	add r1, r1, #1
	bl FUN_0202AE90
	cmp r0, #0
	bne _02231CC2
	ldr r2, _02231D38 ; =MOD83_0223AE40
	lsl r1, r4, #3
	ldr r0, [r2, #0x40]
	add r6, sp, #0x14
	ldr r2, [r2, #0x44]
	add r3, r6, r1
	str r0, [r6, r1]
	add r4, r4, #1
	str r2, [r3, #4]
_02231CC2:
	ldr r2, _02231D38 ; =MOD83_0223AE40
	lsl r1, r4, #3
	ldr r0, [r2, #0x48]
	add r6, sp, #0x14
	str r0, [r6, r1]
	ldr r2, [r2, #0x4c]
	add r3, r6, r1
	ldr r0, _02231D40 ; =0x00002B3C
	str r2, [r3, #4]
	ldr r6, [r5, r0]
	add r0, r7, #0
	bl FUN_02019570
	add r0, r7, #0
	bl RemoveWindow
	add r1, r4, #1
	mov r0, #4
	sub r0, r0, r1
	ldr r1, [r6, #8]
	lsl r0, r0, #1
	add r1, r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp]
	ldr r1, [r6, #0xc]
	mov r2, #2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #4]
	ldr r1, [r6, #0x10]
	sub r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	ldr r0, _02231D44 ; =0x00002B38
	add r1, r7, #0
	ldr r0, [r5, r0]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, _02231D48 ; =0x0000299C
	ldr r3, [r6, #4]
	ldr r0, [r5, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl AddWindowParameterized
	add r0, r5, #0
	add r1, sp, #0x14
	add r2, r4, #1
	add r3, r7, #0
	bl MOD83_022316F0
	mov r0, #1
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02231D38: .word MOD83_0223AE40
_02231D3C: .word 0x00002B60
_02231D40: .word 0x00002B3C
_02231D44: .word 0x00002B38
_02231D48: .word 0x0000299C
	thumb_func_end MOD83_02231C58

	thumb_func_start MOD83_02231D4C
MOD83_02231D4C: ; 0x02231D4C
	push {r3, lr}
	add r3, r1, #0
	ldr r1, _02231D5C ; =MOD83_0223AE40
	mov r2, #2
	bl MOD83_022316F0
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02231D5C: .word MOD83_0223AE40
	thumb_func_end MOD83_02231D4C

	thumb_func_start MOD83_02231D60
MOD83_02231D60: ; 0x02231D60
	push {r3, lr}
	add r3, r1, #0
	ldr r1, _02231D70 ; =MOD83_0223AE60
	mov r2, #2
	bl MOD83_022316F0
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02231D70: .word MOD83_0223AE60
	thumb_func_end MOD83_02231D60

	thumb_func_start MOD83_02231D74
MOD83_02231D74: ; 0x02231D74
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02231D94 ; =0x00002B70
	add r4, r1, #0
	add r0, r5, r0
	mov r1, #2
	bl MOD83_022317A8
	ldr r1, _02231D98 ; =MOD83_0223AE50
	add r0, r5, #0
	mov r2, #2
	add r3, r4, #0
	bl MOD83_022316F0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_02231D94: .word 0x00002B70
_02231D98: .word MOD83_0223AE50
	thumb_func_end MOD83_02231D74

	thumb_func_start MOD83_02231D9C
MOD83_02231D9C: ; 0x02231D9C
	push {r3, lr}
	sub sp, #8
	mov r3, #1
	str r3, [sp]
	ldr r1, _02231DB8 ; =0x000029A0
	str r3, [sp, #4]
	ldr r0, [r0, r1]
	mov r1, #0
	add r2, r1, #0
	bl BufferIntegerAsString
	mov r0, #1
	add sp, #8
	pop {r3, pc}
	.align 2, 0
_02231DB8: .word 0x000029A0
	thumb_func_end MOD83_02231D9C

	thumb_func_start MOD83_02231DBC
MOD83_02231DBC: ; 0x02231DBC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x57
	str r0, [sp, #8]
	add r6, r2, #0
	mov r0, #0
	add r4, r3, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	cmp r4, #0
	beq _02231DE4
	mov r0, #0x1b
	str r0, [r4]
_02231DE4:
	ldr r0, _02231DEC ; =0x00002BE0
	str r6, [r5, r0]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02231DEC: .word 0x00002BE0
	thumb_func_end MOD83_02231DBC

	thumb_func_start MOD83_02231DF0
MOD83_02231DF0: ; 0x02231DF0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	str r2, [sp, #0x14]
	ldr r2, _02231F68 ; =0x00000172
	ldr r3, [r5]
	mov r0, #1
	mov r1, #0x1a
	ldr r4, _02231F6C ; =MOD83_0223AEB0
	bl NewMsgDataFromNarc
	ldr r1, _02231F70 ; =0x000029A4
	str r0, [r5, r1]
	ldr r0, [r5]
	bl ScrStrBufs_new
	ldr r1, _02231F74 ; =0x000029A0
	str r0, [r5, r1]
	ldr r1, _02231F78 ; =0x00002B64
	ldr r0, [sp, #0x14]
	str r0, [r5, r1]
	ldr r1, [sp, #0x14]
	add r0, r5, #0
	bl MOD83_02232118
	mov r0, #0
	str r0, [sp, #0x2c]
	ldr r0, _02231F7C ; =0x000029A8
	add r7, r4, #0
	str r5, [sp, #0x1c]
	add r6, r5, r0
_02231E2E:
	ldr r1, [r7]
	ldr r0, [sp, #0x14]
	cmp r0, r1
	beq _02231E50
	cmp r1, #2
	beq _02231E50
	ldr r1, [sp, #0x1c]
	ldr r0, _02231F7C ; =0x000029A8
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02231E50
	add r0, r6, #0
	bl FUN_02019570
	add r0, r6, #0
	bl RemoveWindow
_02231E50:
	ldr r0, [sp, #0x1c]
	add r7, #0x30
	add r0, #0x10
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x2c]
	add r6, #0x10
	add r0, r0, #1
	str r0, [sp, #0x2c]
	cmp r0, #0x13
	blo _02231E2E
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r0, _02231F7C ; =0x000029A8
	mov r7, #0x31
	str r5, [sp, #0x24]
	str r5, [sp, #0x20]
	add r6, r5, r0
_02231E72:
	ldr r1, [r4]
	ldr r0, [sp, #0x14]
	cmp r0, r1
	bne _02231F2E
	ldr r1, [sp, #0x24]
	ldr r0, _02231F7C ; =0x000029A8
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _02231EBE
	ldr r1, [sp, #0x20]
	ldr r0, _02231F80 ; =0x00002AE8
	mov r2, #0
	str r7, [r1, r0]
	ldr r0, [r4, #8]
	add r1, r6, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, _02231F84 ; =0x0000299C
	ldr r3, [r4, #4]
	ldr r0, [r5, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl AddWindowParameterized
_02231EBE:
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl GetFontAttribute
	add r1, r0, #0
	add r0, r6, #0
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0x18]
	ldr r3, [r4, #0x24]
	str r0, [sp, #0x28]
	ldr r2, [sp, #0x28]
	add r0, r5, #0
	add r1, r6, #0
	blx r3
	cmp r0, #1
	bne _02231F20
	ldr r2, [r4, #0x20]
	cmp r2, #0
	beq _02231F20
	ldr r0, _02231F74 ; =0x000029A0
	ldr r1, _02231F70 ; =0x000029A4
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r3, [r5]
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x30]
	ldr r0, [r4, #0x2c]
	ldr r2, [sp, #0x30]
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [sp, #0x28]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r1, [r4, #0x14]
	ldr r3, [r4, #0x28]
	add r0, r6, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x30]
	bl String_dtor
_02231F20:
	add r0, r6, #0
	bl CopyWindowToVram
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x10]
	mul r0, r1
	add r7, r7, r0
_02231F2E:
	ldr r0, [sp, #0x24]
	add r4, #0x30
	add r0, #0x10
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r6, #0x10
	add r0, r0, #4
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0x13
	blo _02231E72
	ldr r0, _02231F70 ; =0x000029A4
	ldr r0, [r5, r0]
	bl DestroyMsgData
	ldr r0, _02231F74 ; =0x000029A0
	ldr r0, [r5, r0]
	bl ScrStrBufs_delete
	ldr r0, [sp, #0x14]
	cmp r0, #0
	bne _02231F64
	add r0, r5, #0
	bl MOD83_0223227C
_02231F64:
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02231F68: .word 0x00000172
_02231F6C: .word MOD83_0223AEB0
_02231F70: .word 0x000029A4
_02231F74: .word 0x000029A0
_02231F78: .word 0x00002B64
_02231F7C: .word 0x000029A8
_02231F80: .word 0x00002AE8
_02231F84: .word 0x0000299C
	thumb_func_end MOD83_02231DF0

	thumb_func_start MOD83_02231F88
MOD83_02231F88: ; 0x02231F88
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r0, #0
	add r7, r3, #0
	mov r3, #0x30
	ldr r0, _02232084 ; =MOD83_0223AEB0
	mul r3, r2
	add r6, r1, #0
	add r4, r0, r3
	ldr r0, [r6]
	cmp r0, #0
	bne _02231FD2
	ldr r0, [r4, #8]
	mov r2, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xf
	str r0, [sp, #0xc]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, _02232088 ; =0x0000299C
	ldr r3, [r4, #4]
	ldr r0, [r5, r0]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl AddWindowParameterized
_02231FD2:
	ldr r1, [r4, #0x1c]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FillWindowPixelBuffer
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _02231FFE
	ldr r2, _0223208C ; =0x00000172
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x57
	bl NewMsgDataFromNarc
	ldr r1, _02232090 ; =0x000029A4
	str r0, [r5, r1]
	mov r0, #0x57
	bl ScrStrBufs_new
	ldr r1, _02232094 ; =0x000029A0
	str r0, [r5, r1]
_02231FFE:
	ldr r0, _02232098 ; =0x00002B38
	ldr r2, _0223209C ; =0x00010200
	str r7, [r5, r0]
	add r0, r0, #4
	str r4, [r5, r0]
	ldr r3, [r4, #0x24]
	add r0, r5, #0
	add r1, r6, #0
	blx r3
	ldr r2, [r4, #0x20]
	cmp r2, #0
	beq _02232054
	ldr r1, _02232094 ; =0x000029A0
	mov r3, #0x57
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x14]
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, [r4, #0x18]
	ldr r2, [sp, #0x14]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r1, [r4, #0x14]
	add r0, r6, #0
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x14]
	bl String_dtor
	ldr r0, _02232090 ; =0x000029A4
	ldr r0, [r5, r0]
	bl DestroyMsgData
	ldr r0, _02232094 ; =0x000029A0
	ldr r0, [r5, r0]
	bl ScrStrBufs_delete
_02232054:
	ldr r0, _022320A0 ; =0x00002B70
	add r0, r5, r0
	cmp r6, r0
	bne _0223206A
	add r0, r6, #0
	mov r1, #0
	mov r2, #0x13
	mov r3, #0xa
	bl FUN_0200D0BC
	b _02232076
_0223206A:
	add r0, r6, #0
	mov r1, #0
	mov r2, #0xa
	mov r3, #0xe
	bl FUN_0200CCA4
_02232076:
	ldr r1, [r4, #0xc]
	ldr r0, [r4, #0x10]
	mul r0, r1
	add r0, r7, r0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232084: .word MOD83_0223AEB0
_02232088: .word 0x0000299C
_0223208C: .word 0x00000172
_02232090: .word 0x000029A4
_02232094: .word 0x000029A0
_02232098: .word 0x00002B38
_0223209C: .word 0x00010200
_022320A0: .word 0x00002B70
	thumb_func_end MOD83_02231F88

	thumb_func_start MOD83_022320A4
MOD83_022320A4: ; 0x022320A4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	add r7, r4, #0
_022320AE:
	add r4, r4, r6
	cmp r4, #3
	bne _022320B6
	mov r4, #0
_022320B6:
	mov r0, #0
	mvn r0, r0
	cmp r4, r0
	bne _022320C0
	mov r4, #2
_022320C0:
	cmp r7, r4
	beq _022320D4
	mov r0, #0xad
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_0202AE4C
	cmp r0, #0
	beq _022320AE
_022320D4:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022320A4

	thumb_func_start MOD83_022320D8
MOD83_022320D8: ; 0x022320D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r2, #0
	mov r2, #1
	add r5, r0, #0
	str r2, [sp]
	add r6, r3, #0
	ldr r3, [r5]
	mov r0, #0x74
	bl GfGfxLoader_LoadFromNarc
	add r1, sp, #4
	add r7, r0, #0
	bl NNS_G2dGetUnpackedScreenData
	ldr r0, _02232114 ; =0x0000299C
	ldr r2, [sp, #4]
	lsl r1, r4, #0x18
	ldr r0, [r5, r0]
	lsr r1, r1, #0x18
	add r2, #0xc
	add r3, r6, #0
	bl FUN_02017DFC
	add r0, r7, #0
	bl FreeToHeap
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232114: .word 0x0000299C
	thumb_func_end MOD83_022320D8

	thumb_func_start MOD83_02232118
MOD83_02232118: ; 0x02232118
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #0
	add r4, r1, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #3
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	ldr r0, [r5]
	ldr r2, _02232204 ; =0x0000299C
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x74
	mov r1, #6
	bl GfGfxLoader_LoadCharData
	cmp r4, #0
	beq _0223215E
	cmp r4, #1
	beq _0223217E
	b _0223219C
_0223215E:
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	ldr r0, [r5]
	ldr r2, _02232204 ; =0x0000299C
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x74
	mov r1, #4
	bl GfGfxLoader_LoadScrnData
	b _0223219C
_0223217E:
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	ldr r0, [r5]
	ldr r2, _02232204 ; =0x0000299C
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x74
	mov r1, #5
	bl GfGfxLoader_LoadScrnData
_0223219C:
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [r5]
	mov r1, #0
	str r0, [sp, #4]
	mov r0, #0x74
	add r3, r0, #0
	add r2, r1, #0
	add r3, #0xec
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r1, #1
	str r1, [sp, #8]
	ldr r0, [r5]
	ldr r2, _02232204 ; =0x0000299C
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x74
	mov r3, #3
	bl GfGfxLoader_LoadCharData
	mov r2, #3
	add r0, r5, #0
	mov r1, #2
	lsl r3, r2, #9
	bl MOD83_022320D8
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0xb
	str r0, [sp, #8]
	ldr r0, _02232204 ; =0x0000299C
	mov r2, #0
	ldr r0, [r5, r0]
	mov r1, #3
	add r3, r2, #0
	bl FUN_020186B4
	ldr r0, _02232204 ; =0x0000299C
	mov r1, #3
	ldr r0, [r5, r0]
	bl FUN_02017CD0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232204: .word 0x0000299C
	thumb_func_end MOD83_02232118

	thumb_func_start MOD83_02232208
MOD83_02232208: ; 0x02232208
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl OverlayManager_GetData
	ldr r1, _02232270 ; =0x00002B68
	ldr r0, [r0, r1]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0223222E
	add r0, r0, #1
	cmp r4, r0
	beq _0223226C
	b _02232248
_0223222E:
	ldr r0, _02232274 ; =0x000005DC
	bl FUN_020054C8
	cmp r6, #0
	beq _0223226C
	add r0, r7, #0
	blx r6
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223226C
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02232248:
	ldr r0, _02232274 ; =0x000005DC
	bl FUN_020054C8
	cmp r4, #0
	beq _0223226C
	cmp r4, #0x1e
	bhs _0223225A
	str r4, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_0223225A:
	ldr r0, _02232278 ; =MOD83_0223B89C
	str r4, [r0]
	add r0, r7, #0
	blx r4
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223226C
	str r0, [r5]
_0223226C:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232270: .word 0x00002B68
_02232274: .word 0x000005DC
_02232278: .word MOD83_0223B89C
	thumb_func_end MOD83_02232208

	thumb_func_start MOD83_0223227C
MOD83_0223227C: ; 0x0223227C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r1, _02232398 ; =0x00002D6C
	add r5, r0, #0
	ldr r0, [r5, r1]
	cmp r0, #0
	bne _022322DC
	add r0, r1, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _022322DC
	add r1, #8
	ldr r0, [r5, r1]
	cmp r0, #0
	bne _022322DC
	bl MOD83_02238B38
	cmp r0, #1
	bne _022322A8
	add r0, r5, #0
	bl MOD83_022315F8
_022322A8:
	bl MOD83_02238AFC
	bl MOD83_02238B4C
	mov r0, #0x18
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x1a
	mov r2, #0x17
	mov r3, #0x19
	bl MOD83_02238BC4
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #1
	str r0, [sp, #4]
	mov r0, #0x13
	mov r3, #0x60
	bl GfGfxLoader_GXLoadPal
_022322DC:
	mov r0, #0xb2
	mov r6, #0
	str r0, [sp, #0x10]
	str r6, [sp, #8]
	add r4, r5, #0
	mov r7, #0x64
_022322E8:
	ldr r0, _0223239C ; =0x00002B60
	ldr r0, [r5, r0]
	lsl r0, r0, #2
	add r1, r5, r0
	ldr r0, _022323A0 ; =0x00002B54
	ldr r1, [r1, r0]
	ldr r0, [sp, #8]
	add r1, r1, r0
	ldr r0, _022323A4 ; =0x0000034A
	ldrh r0, [r1, r0]
	str r0, [sp, #0xc]
	cmp r0, #0
	bne _02232312
	ldr r0, _02232398 ; =0x00002D6C
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0223237C
	mov r1, #0
	bl FUN_020200A0
	b _0223237C
_02232312:
	add r0, r6, #0
	add r0, #0xa
	str r0, [sp]
	ldr r1, _02232398 ; =0x00002D6C
	ldr r2, [sp, #0x10]
	ldr r1, [r4, r1]
	mov r0, #0
	mov r3, #0x10
	bl MOD83_02238DBC
	ldr r1, _02232398 ; =0x00002D6C
	str r0, [r4, r1]
	mov r1, #0
	ldr r0, [sp, #0xc]
	add r2, r1, #0
	bl FUN_0206B6D4
	add r1, r0, #0
	ldr r0, [r5]
	mov r2, #0
	str r0, [sp]
	mov r0, #0x13
	add r3, sp, #0x18
	bl GfGfxLoader_GetCharData
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	mov r1, #2
	ldr r0, [r0, #0x14]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #0x18]
	mov r2, #2
	ldr r0, [r0, #0x14]
	lsl r1, r7, #5
	lsl r2, r2, #8
	bl GX_LoadOBJ
	mov r1, #0
	ldr r0, [sp, #0xc]
	add r2, r1, #0
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, _02232398 ; =0x00002D6C
	add r1, r1, #3
	ldr r0, [r4, r0]
	bl FUN_02020248
	ldr r0, [sp, #0x14]
	bl FreeToHeap
_0223237C:
	ldr r0, [sp, #8]
	add r6, r6, #1
	add r0, r0, #2
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	add r4, r4, #4
	add r0, #0x19
	add r7, #0x10
	str r0, [sp, #0x10]
	cmp r6, #3
	blt _022322E8
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02232398: .word 0x00002D6C
_0223239C: .word 0x00002B60
_022323A0: .word 0x00002B54
_022323A4: .word 0x0000034A
	thumb_func_end MOD83_0223227C

	thumb_func_start MOD83_022323A8
MOD83_022323A8: ; 0x022323A8
	push {r4, lr}
	mov r2, #2
	add r4, r0, #0
	mov r0, #3
	mov r1, #0x57
	lsl r2, r2, #0x10
	bl CreateHeap
	ldr r1, _0223240C ; =0x00003CF4
	add r0, r4, #0
	mov r2, #0x57
	bl OverlayManager_CreateAndGetData
	ldr r2, _0223240C ; =0x00003CF4
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x57
	bl FUN_02016B94
	ldr r1, _02232410 ; =0x0000299C
	str r0, [r4, r1]
	mov r0, #0x57
	str r0, [r4]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, _02232414 ; =0x00002B60
	mov r1, #2
	str r1, [r4, r0]
	mov r1, #1
	add r0, #0x7c
	str r1, [r4, r0]
	mov r0, #0x57
	bl MOD83_02238770
	mov r2, #3
	mov r0, #0
	mov r1, #0x5b
	lsl r2, r2, #8
	bl CreateHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_0223240C: .word 0x00003CF4
_02232410: .word 0x0000299C
_02232414: .word 0x00002B60
	thumb_func_end MOD83_022323A8

	thumb_func_start MOD83_02232418
MOD83_02232418: ; 0x02232418
	push {r4, lr}
	add r4, r1, #0
	bl FUN_020129C8
	mov r0, #3
	lsl r0, r0, #0xa
	ldr r0, [r4, r0]
	bl FUN_0201299C
	ldr r1, _02232438 ; =0x04000010
	mov r2, #8
	mov r3, #1
	bl FUN_020129D8
	pop {r4, pc}
	nop
_02232438: .word 0x04000010
	thumb_func_end MOD83_02232418

	thumb_func_start MOD83_0223243C
MOD83_0223243C: ; 0x0223243C
	push {r3, r4, r5, lr}
	ldr r4, _02232490 ; =0x000030D0
	ldr r5, _02232494 ; =0x00000C14
	add r4, r0, r4
	add r0, r5, #0
	str r1, [r4, r5]
	sub r0, #0xc
	str r2, [r4, r0]
	add r0, r5, #0
	sub r0, #8
	sub r5, #0x14
	str r3, [r4, r0]
	ldr r0, [r4, r5]
	cmp r0, #0
	bne _0223246E
	mov r2, #6
	lsl r2, r2, #8
	mov r0, #0x57
	add r1, r4, #0
	add r2, r4, r2
	bl FUN_02012944
	mov r1, #3
	lsl r1, r1, #0xa
	str r0, [r4, r1]
_0223246E:
	ldr r0, _02232498 ; =0x00000C04
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02232486
	mov r2, #1
	ldr r0, _0223249C ; =MOD83_02232418
	add r1, r4, #0
	lsl r2, r2, #0xa
	bl FUN_0200CA60
	ldr r1, _02232498 ; =0x00000C04
	str r0, [r4, r1]
_02232486:
	mov r0, #0xc1
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232490: .word 0x000030D0
_02232494: .word 0x00000C14
_02232498: .word 0x00000C04
_0223249C: .word MOD83_02232418
	thumb_func_end MOD83_0223243C

	thumb_func_start MOD83_022324A0
MOD83_022324A0: ; 0x022324A0
	push {r4, lr}
	ldr r1, _022324D4 ; =0x000030D0
	add r4, r0, r1
	mov r0, #3
	lsl r0, r0, #0xa
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022324B4
	bl FUN_02012974
_022324B4:
	ldr r0, _022324D8 ; =0x00000C04
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022324C0
	bl FUN_0200CAB4
_022324C0:
	mov r0, #3
	mov r1, #0
	lsl r0, r0, #0xa
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	bl FUN_020129C8
	pop {r4, pc}
	nop
_022324D4: .word 0x000030D0
_022324D8: .word 0x00000C04
	thumb_func_end MOD83_022324A0

	thumb_func_start MOD83_022324DC
MOD83_022324DC: ; 0x022324DC
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _022325E4 ; =0x000030D0
	mov r5, #0x15
	add r4, r0, r1
	mov r0, #0xc1
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	lsl r5, r5, #0xe
	cmp r1, #0
	bne _022324F4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022324F4:
	add r1, r0, #4
	ldr r1, [r4, r1]
	cmp r1, #1
	bne _02232542
	add r1, r0, #0
	sub r1, #8
	ldr r2, [r4, r1]
	sub r1, r0, #4
	ldr r1, [r4, r1]
	add r2, r2, r1
	add r1, r0, #0
	sub r1, #8
	str r2, [r4, r1]
	sub r1, r0, #4
	ldr r2, [r4, r1]
	add r1, r2, #0
	add r2, r2, r1
	sub r1, r0, #4
	str r2, [r4, r1]
	add r1, r0, #0
	sub r1, #8
	ldr r2, [r4, r1]
	asr r1, r2, #0xb
	lsr r1, r1, #0x14
	add r1, r2, r1
	asr r2, r1, #0xc
	mov r1, #0xfa
	lsl r1, r1, #2
	cmp r2, r1
	ble _0223257C
	mov r2, #0
	add r1, r0, #0
	str r2, [r4, r0]
	sub r1, #8
	str r2, [r4, r1]
	sub r0, r0, #4
	mov r5, #0xa8
	str r2, [r4, r0]
	b _0223257C
_02232542:
	add r1, r0, #0
	sub r1, #8
	ldr r2, [r4, r1]
	sub r1, r0, #4
	ldr r1, [r4, r1]
	sub r2, r2, r1
	add r1, r0, #0
	sub r1, #8
	str r2, [r4, r1]
	sub r1, r0, #4
	ldr r2, [r4, r1]
	lsr r1, r2, #0x1f
	add r1, r2, r1
	asr r2, r1, #1
	sub r1, r0, #4
	str r2, [r4, r1]
	mov r2, #1
	ldr r1, [r4, r1]
	lsl r2, r2, #0xa
	cmp r1, r2
	bge _0223257C
	mov r1, #0
	lsl r3, r2, #2
	add r2, r0, #0
	str r1, [r4, r0]
	sub r2, #8
	str r3, [r4, r2]
	sub r0, r0, #4
	str r1, [r4, r0]
_0223257C:
	mov r0, #3
	lsl r0, r0, #0xa
	ldr r0, [r4, r0]
	bl FUN_02012988
	add r2, r0, #0
	mov r0, #0x54
	add r3, r0, #0
	add r3, #0xfc
_0223258E:
	asr r1, r5, #0xb
	lsr r1, r1, #0x14
	add r1, r5, r1
	asr r1, r1, #0xc
	bpl _0223259A
	mov r1, #0
_0223259A:
	cmp r1, #0xa8
	ble _022325A0
	mov r1, #0xa8
_022325A0:
	lsl r6, r3, #1
	add r7, r2, r6
	sub r6, r1, r0
	strh r6, [r7, #6]
	ldrh r6, [r7, #6]
	sub r1, r0, r1
	add r3, r3, #4
	strh r6, [r7, #2]
	mov r6, #0xa8
	sub r6, r6, r0
	lsl r6, r6, #3
	add r6, r2, r6
	strh r1, [r6, #6]
	ldrh r1, [r6, #6]
	add r0, r0, #1
	strh r1, [r6, #2]
	ldr r1, _022325E8 ; =0x00000C08
	ldr r1, [r4, r1]
	add r5, r5, r1
	cmp r0, #0xa8
	blt _0223258E
	mov r1, #6
	add r0, r2, #0
	lsl r1, r1, #8
	bl DC_FlushRange
	mov r0, #3
	lsl r0, r0, #0xa
	ldr r0, [r4, r0]
	bl FUN_020129B4
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022325E4: .word 0x000030D0
_022325E8: .word 0x00000C08
	thumb_func_end MOD83_022324DC

	thumb_func_start MOD83_022325EC
MOD83_022325EC: ; 0x022325EC
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_022394CC
	sub r0, r0, #2
	cmp r0, #1
	bhi _02232606
	ldr r0, _02232608 ; =0x0000061B
	bl FUN_020054C8
	ldr r0, _0223260C ; =0x00003CE8
	mov r1, #0
	str r1, [r4, r0]
_02232606:
	pop {r4, pc}
	.align 2, 0
_02232608: .word 0x0000061B
_0223260C: .word 0x00003CE8
	thumb_func_end MOD83_022325EC

	thumb_func_start MOD83_02232610
MOD83_02232610: ; 0x02232610
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02232658 ; =0x00002B60
	ldr r1, [r4, r0]
	sub r0, #0xc
	lsl r1, r1, #2
	add r1, r4, r1
	ldr r2, [r1, r0]
	mov r0, #0x35
	lsl r0, r0, #4
	ldrb r1, [r2, r0]
	cmp r1, #0xff
	beq _0223262E
	add r1, r1, #1
	strb r1, [r2, r0]
_0223262E:
	ldr r0, _02232658 ; =0x00002B60
	ldr r1, [r4, r0]
	sub r0, #0xc
	lsl r1, r1, #2
	add r1, r4, r1
	ldr r2, [r1, r0]
	mov r0, #0xd2
	lsl r0, r0, #2
	ldrb r1, [r2, r0]
	cmp r1, #0xff
	beq _02232648
	sub r1, r1, #1
	strb r1, [r2, r0]
_02232648:
	ldr r0, _0223265C ; =0x00002B44
	ldr r0, [r4, r0]
	bl MOD83_022394BC
	ldr r1, _02232660 ; =MOD83_022325EC
	ldr r0, _02232664 ; =0x00003CE8
	str r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_02232658: .word 0x00002B60
_0223265C: .word 0x00002B44
_02232660: .word MOD83_022325EC
_02232664: .word 0x00003CE8
	thumb_func_end MOD83_02232610

	thumb_func_start MOD83_02232668
MOD83_02232668: ; 0x02232668
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	ldr r2, _02232768 ; =gMain
	add r6, r1, #0
	ldr r3, [r2, #0x48]
	ldr r1, _0223276C ; =0x00003CEC
	add r5, r0, #0
	mov r2, #0x10
	ldr r0, [r5, r1]
	tst r2, r3
	beq _02232686
	cmp r0, #1
	beq _02232686
	mov r2, #1
	str r2, [r5, r1]
_02232686:
	ldr r1, _02232768 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x20
	tst r1, r2
	beq _0223269C
	ldr r1, _0223276C ; =0x00003CEC
	ldr r2, [r5, r1]
	cmp r2, #0
	beq _0223269C
	mov r2, #0
	str r2, [r5, r1]
_0223269C:
	ldr r1, _0223276C ; =0x00003CEC
	ldr r1, [r5, r1]
	cmp r0, r1
	beq _022326CC
	cmp r1, #0
	bne _022326AC
	mov r1, #1
	b _022326AE
_022326AC:
	mov r1, #0
_022326AE:
	ldr r0, _02232770 ; =0x00002D64
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _0223276C ; =0x00003CEC
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _022326C2
	mov r1, #1
	b _022326C4
_022326C2:
	mov r1, #0
_022326C4:
	ldr r0, _02232774 ; =0x00002D68
	ldr r0, [r5, r0]
	bl FUN_02020130
_022326CC:
	ldr r0, _02232768 ; =gMain
	mov r4, #0
	ldr r1, [r0, #0x48]
	mov r0, #2
	add r2, r1, #0
	tst r2, r0
	beq _022326DE
	add r4, r0, #0
	b _0223270E
_022326DE:
	mov r0, #1
	and r1, r0
	beq _022326F4
	cmp r6, #0
	beq _022326F4
	ldr r2, _0223276C ; =0x00003CEC
	ldr r2, [r5, r2]
	cmp r2, #0
	bne _022326F4
	add r4, r0, #0
	b _0223270E
_022326F4:
	cmp r1, #0
	beq _02232704
	ldr r0, _0223276C ; =0x00003CEC
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _02232704
	mov r4, #2
	b _0223270E
_02232704:
	cmp r1, #0
	beq _0223270E
	cmp r6, #0
	bne _0223270E
	mov r4, #3
_0223270E:
	cmp r4, #1
	bne _02232746
	ldr r0, _02232778 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0xab
	bl FUN_02031588
	mov r3, #0xa
	ldr r1, _0223277C ; =0x00002BD4
	mov r0, #1
	str r0, [r5, r1]
	mov r0, #0x15
	sub r1, #0x64
	str r0, [r7]
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #0x11
	lsl r3, r3, #6
	bl MOD83_02231F88
	ldr r0, _02232780 ; =0x00002B70
	mov r1, #0x13
	add r0, r5, r0
	bl FUN_0200D858
	ldr r1, _02232784 ; =0x00003CF0
	str r0, [r5, r1]
_02232746:
	cmp r4, #2
	bne _0223275A
	ldr r0, _02232778 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0x13
	bl MOD83_02233084
_0223275A:
	cmp r4, #3
	bne _02232764
	ldr r0, _02232778 ; =0x000005DC
	bl FUN_020054C8
_02232764:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232768: .word gMain
_0223276C: .word 0x00003CEC
_02232770: .word 0x00002D64
_02232774: .word 0x00002D68
_02232778: .word 0x000005DC
_0223277C: .word 0x00002BD4
_02232780: .word 0x00002B70
_02232784: .word 0x00003CF0
	thumb_func_end MOD83_02232668

	thumb_func_start MOD83_02232788
MOD83_02232788: ; 0x02232788
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0x1d
	bls _0223279E
	b _02232CF4
_0223279E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022327AA: ; jump table
	.short _022327E6 - _022327AA - 2 ; case 0
	.short _02232854 - _022327AA - 2 ; case 1
	.short _02232866 - _022327AA - 2 ; case 2
	.short _022328DC - _022327AA - 2 ; case 3
	.short _02232956 - _022327AA - 2 ; case 4
	.short _0223297E - _022327AA - 2 ; case 5
	.short _0223299E - _022327AA - 2 ; case 6
	.short _022329D6 - _022327AA - 2 ; case 7
	.short _022329FA - _022327AA - 2 ; case 8
	.short _02232A20 - _022327AA - 2 ; case 9
	.short _02232A4C - _022327AA - 2 ; case 10
	.short _02232A88 - _022327AA - 2 ; case 11
	.short _02232AAC - _022327AA - 2 ; case 12
	.short _02232AB8 - _022327AA - 2 ; case 13
	.short _02232AC4 - _022327AA - 2 ; case 14
	.short _02232AD6 - _022327AA - 2 ; case 15
	.short _02232AE2 - _022327AA - 2 ; case 16
	.short _02232B24 - _022327AA - 2 ; case 17
	.short _02232B3A - _022327AA - 2 ; case 18
	.short _02232BDC - _022327AA - 2 ; case 19
	.short _02232BE8 - _022327AA - 2 ; case 20
	.short _02232C36 - _022327AA - 2 ; case 21
	.short _02232C26 - _022327AA - 2 ; case 22
	.short _02232C6A - _022327AA - 2 ; case 23
	.short _02232C7E - _022327AA - 2 ; case 24
	.short _02232CB8 - _022327AA - 2 ; case 25
	.short _02232CC8 - _022327AA - 2 ; case 26
	.short _02232CD4 - _022327AA - 2 ; case 27
	.short _02232CE4 - _022327AA - 2 ; case 28
	.short _02232CF4 - _022327AA - 2 ; case 29
_022327E6:
	add r0, r6, #0
	bl OverlayManager_GetField18
	ldr r1, [r0, #8]
	ldr r0, _02232B54 ; =0x00002B44
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	bl FUN_0202251C
	mov r1, #0xad
	lsl r1, r1, #6
	str r0, [r4, r1]
	add r0, r1, #4
	ldr r0, [r4, r0]
	bl Sav2_PlayerData_GetOptionsAddr
	ldr r1, _02232B58 ; =0x00002B48
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl Options_GetFrame
	ldr r1, _02232B5C ; =0x00002B4C
	str r0, [r4, r1]
	sub r1, #0xc
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_0202AC64
	ldr r1, _02232B60 ; =0x00002B54
	str r0, [r4, r1]
	sub r1, #0x14
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_0202AC64
	ldr r1, _02232B64 ; =0x00002B58
	str r0, [r4, r1]
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #2
	bl FUN_0202AC64
	ldr r1, _02232B68 ; =0x00002B5C
	mov r2, #1
	str r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r4, #0
	bl MOD83_022320A4
	ldr r1, _02232B6C ; =0x00002B60
	str r0, [r4, r1]
	mov r0, #1
	str r0, [r5]
	b _02232CF4
_02232854:
	bl MOD83_022331C0
	ldr r0, _02232B70 ; =0x0000299C
	ldr r0, [r4, r0]
	bl MOD83_022331E0
	mov r0, #2
	str r0, [r5]
	b _02232CF4
_02232866:
	bl FUN_0201BD5C
	add r0, r4, #0
	mov r1, #0
	bl MOD83_02232118
	mov r1, #0x1e
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x57
	bl FUN_02002ED0
	mov r1, #0
	str r1, [sp]
	mov r0, #0x57
	str r0, [sp, #4]
	ldr r0, _02232B70 ; =0x0000299C
	mov r2, #1
	ldr r0, [r4, r0]
	mov r3, #0xd
	bl FUN_0200CB00
	mov r0, #1
	str r0, [sp]
	mov r0, #0x57
	str r0, [sp, #4]
	ldr r0, _02232B70 ; =0x0000299C
	mov r1, #0
	ldr r0, [r4, r0]
	mov r2, #0xa
	mov r3, #0xe
	bl FUN_0200CB00
	ldr r0, _02232B5C ; =0x00002B4C
	mov r1, #0
	ldr r0, [r4, r0]
	mov r2, #0x13
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x57
	str r0, [sp, #4]
	ldr r0, _02232B70 ; =0x0000299C
	mov r3, #0xa
	ldr r0, [r4, r0]
	bl FUN_0200CD68
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD83_02231DF0
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232CF4
_022328DC:
	ldr r1, _02232B6C ; =0x00002B60
	mov r2, #0x40
	ldr r6, [r4, r1]
	ldr r1, _02232B74 ; =gMain
	ldr r1, [r1, #0x48]
	add r3, r1, #0
	tst r3, r2
	beq _022328F8
	add r1, r6, #0
	sub r2, #0x41
	bl MOD83_022320A4
	add r6, r0, #0
	b _02232934
_022328F8:
	mov r2, #0x80
	tst r2, r1
	beq _0223290A
	add r1, r6, #0
	mov r2, #1
	bl MOD83_022320A4
	add r6, r0, #0
	b _02232934
_0223290A:
	mov r0, #2
	tst r0, r1
	beq _02232924
	ldr r0, _02232B78 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x1c
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232934
_02232924:
	mov r0, #1
	tst r0, r1
	beq _02232934
	ldr r0, _02232B78 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #4
	str r0, [r5]
_02232934:
	ldr r0, _02232B6C ; =0x00002B60
	ldr r0, [r4, r0]
	cmp r0, r6
	bne _0223293E
	b _02232CF4
_0223293E:
	mov r0, #6
	lsl r0, r0, #8
	bl FUN_020054C8
	ldr r0, _02232B6C ; =0x00002B60
	mov r1, #1
	str r6, [r4, r0]
	add r0, r4, #0
	mov r2, #0
	bl MOD83_02231DF0
	b _02232CF4
_02232956:
	ldr r1, _02232B7C ; =0x00002B70
	mov r3, #0xa
	add r1, r4, r1
	mov r2, #7
	lsl r3, r3, #6
	bl MOD83_02231F88
	ldr r3, _02232B80 ; =0x00002B90
	mov r2, #8
	add r1, r3, #0
	str r0, [r4, r3]
	sub r1, #0x10
	ldr r3, [r4, r3]
	add r0, r4, #0
	add r1, r4, r1
	bl MOD83_02231F88
	mov r0, #5
	str r0, [r5]
	b _02232CF4
_0223297E:
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #0
	bl MOD83_02232208
	ldr r0, _02232B74 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _02232A54
	ldr r0, _02232B78 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0xb
	str r0, [r5]
	b _02232CF4
_0223299E:
	mov r0, #6
	lsl r0, r0, #8
	bl FUN_020054C8
	mov r0, #0x10
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, _02232B7C ; =0x00002B70
	mov r1, #0
	add r0, r4, r0
	bl MOD83_022316D8
	mov r0, #0xae
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #0
	bl MOD83_022316C0
	mov r1, #1
	add r0, r4, #0
	lsl r2, r1, #0xc
	mov r3, #0x66
	bl MOD83_0223243C
	mov r0, #7
	str r0, [r5]
	b _02232CF4
_022329D6:
	bl MOD83_022324DC
	cmp r0, #0
	beq _02232A54
	mov r1, #1
	add r0, r4, #0
	add r2, r1, #0
	bl MOD83_02231DF0
	ldr r2, _02232B84 ; =0x00708000
	add r0, r4, #0
	mov r1, #0
	lsr r3, r2, #1
	bl MOD83_0223243C
	mov r0, #8
	str r0, [r5]
	b _02232CF4
_022329FA:
	bl MOD83_022324DC
	ldr r0, _02232B74 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r1, r0
	beq _02232A54
	lsl r0, r0, #9
	bl FUN_020054C8
	mov r1, #1
	add r0, r4, #0
	lsl r2, r1, #0xc
	mov r3, #0x66
	bl MOD83_0223243C
	mov r0, #9
	str r0, [r5]
	b _02232CF4
_02232A20:
	bl MOD83_022324DC
	cmp r0, #0
	beq _02232A54
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD83_02231DF0
	ldr r2, _02232B84 ; =0x00708000
	add r0, r4, #0
	mov r1, #0
	lsr r3, r2, #1
	bl MOD83_0223243C
	mov r0, #0x10
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #0xa
	str r0, [r5]
	b _02232CF4
_02232A4C:
	bl MOD83_022324DC
	cmp r0, #0
	bne _02232A56
_02232A54:
	b _02232CF4
_02232A56:
	ldr r0, _02232B7C ; =0x00002B70
	mov r1, #0
	add r0, r4, r0
	mov r2, #0x13
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r0, #0xae
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #0
	mov r2, #0xa
	mov r3, #0xe
	bl FUN_0200CCA4
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	bl MOD83_022324A0
	mov r0, #5
	str r0, [r5]
	b _02232CF4
_02232A88:
	bl MOD83_02231A00
	ldr r0, _02232B7C ; =0x00002B70
	mov r1, #0
	add r0, r4, r0
	bl MOD83_022316D8
	ldr r0, _02232B7C ; =0x00002B70
	add r0, r4, r0
	bl FUN_02019570
	ldr r0, _02232B7C ; =0x00002B70
	add r0, r4, r0
	bl RemoveWindow
	mov r0, #3
	str r0, [r5]
	b _02232CF4
_02232AAC:
	ldr r2, _02232B88 ; =MOD83_022319D0
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02232208
	b _02232CF4
_02232AB8:
	ldr r2, _02232B88 ; =MOD83_022319D0
	add r0, r6, #0
	add r1, r5, #0
	bl MOD83_02232208
	b _02232CF4
_02232AC4:
	mov r1, #0xae
	lsl r1, r1, #6
	ldr r2, _02232B8C ; =0x00010200
	add r1, r4, r1
	bl MOD83_02231D74
	mov r0, #0xd
	str r0, [r5]
	b _02232CF4
_02232AD6:
	mov r1, #0
	mov r2, #0x10
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232CF4
_02232AE2:
	bl MOD83_02231A00
	ldr r0, _02232B7C ; =0x00002B70
	mov r1, #0
	add r0, r4, r0
	bl MOD83_022316D8
	ldr r0, _02232B7C ; =0x00002B70
	add r0, r4, r0
	bl FUN_02019570
	ldr r0, _02232B7C ; =0x00002B70
	add r0, r4, r0
	bl RemoveWindow
	add r0, r4, #0
	mov r1, #0
	mov r2, #3
	bl MOD83_02231DF0
	ldr r0, _02232B70 ; =0x0000299C
	ldr r0, [r4, r0]
	bl MOD83_02231820
	add r0, r4, #0
	bl MOD83_022315D0
	add r0, r4, #0
	bl MOD83_0223166C
	mov r0, #0x11
	str r0, [r5]
	b _02232CF4
_02232B24:
	bl MOD83_02232D44
	bl FUN_02033E74
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x12
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232CF4
_02232B3A:
	mov r6, #0
	add r0, r6, #0
	bl FUN_02030E7C
	cmp r0, #0
	beq _02232BD0
	add r0, r4, #0
	add r0, #0x90
	bl FUN_0202F10C
	ldr r1, _02232B90 ; =0x00002AA8
	b _02232B94
	nop
_02232B54: .word 0x00002B44
_02232B58: .word 0x00002B48
_02232B5C: .word 0x00002B4C
_02232B60: .word 0x00002B54
_02232B64: .word 0x00002B58
_02232B68: .word 0x00002B5C
_02232B6C: .word 0x00002B60
_02232B70: .word 0x0000299C
_02232B74: .word gMain
_02232B78: .word 0x000005DC
_02232B7C: .word 0x00002B70
_02232B80: .word 0x00002B90
_02232B84: .word 0x00708000
_02232B88: .word MOD83_022319D0
_02232B8C: .word 0x00010200
_02232B90: .word 0x00002AA8
_02232B94:
	add r0, r4, #0
	add r1, r4, r1
	bl MOD83_02232E0C
	add r6, r0, #0
	bne _02232BC0
	ldr r0, _02232D18 ; =0x00002BD0
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02232BC0
	ldr r0, _02232D1C ; =0x00002AA8
	mov r1, #0
	add r0, r4, r0
	bl FillWindowPixelBuffer
	ldr r0, _02232D1C ; =0x00002AA8
	add r0, r4, r0
	bl CopyWindowToVram
	ldr r0, _02232D18 ; =0x00002BD0
	mov r1, #0
	str r1, [r4, r0]
_02232BC0:
	ldr r1, _02232D20 ; =0x00002A98
	add r0, r4, #0
	add r1, r4, r1
	add r2, r6, #0
	bl MOD83_02232FE4
	ldr r0, _02232D18 ; =0x00002BD0
	str r6, [r4, r0]
_02232BD0:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD83_02232668
	b _02232CF4
_02232BDC:
	mov r1, #0
	mov r2, #0x14
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232CF4
_02232BE8:
	bl MOD83_022315F8
	ldr r0, _02232D24 ; =0x00002B70
	mov r1, #0
	add r0, r4, r0
	bl MOD83_022316D8
	mov r0, #0xae
	lsl r0, r0, #6
	add r0, r4, r0
	mov r1, #0
	bl MOD83_022316C0
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD83_02231DF0
	mov r1, #0x1e
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x57
	bl FUN_02002ED0
	add r0, r4, #0
	mov r1, #1
	mov r2, #4
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232CF4
_02232C26:
	bl FUN_02031810
	cmp r0, #0
	bne _02232CF4
	ldr r0, _02232D28 ; =0x00002BE0
	ldr r0, [r4, r0]
	str r0, [r5]
	b _02232CF4
_02232C36:
	ldr r0, _02232D2C ; =0x00002BD4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02232CF4
	ldr r1, _02232D30 ; =0x00002D78
	add r0, r4, #0
	ldr r2, [r4]
	add r0, #0x90
	add r1, r4, r1
	bl MOD83_022392EC
	ldr r0, _02232D30 ; =0x00002D78
	mov r1, #0xd6
	add r0, r4, r0
	lsl r1, r1, #2
	bl MOD83_0222F8F0
	add r0, r4, #0
	bl MOD83_02232610
	mov r0, #0x17
	str r0, [r5]
	b _02232CF4
_02232C6A:
	bl MOD83_02239574
	cmp r0, #4
	bne _02232CF4
	mov r0, #0x93
	bl FUN_02031588
	mov r0, #0x18
	str r0, [r5]
	b _02232CF4
_02232C7E:
	bl MOD83_02232DF0
	cmp r0, #0
	beq _02232C90
	mov r0, #0x93
	bl FUN_020315D8
	cmp r0, #1
	bne _02232CF4
_02232C90:
	bl MOD83_02239544
	ldr r1, _02232D24 ; =0x00002B70
	mov r3, #0xa
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0x12
	lsl r3, r3, #6
	bl MOD83_02231F88
	ldr r0, _02232D34 ; =0x00003CF0
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x19
	bl MOD83_02233084
	b _02232CF4
_02232CB8:
	ldr r0, _02232D38 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02232CF4
	mov r0, #0x13
	str r0, [r5]
	b _02232CF4
_02232CC8:
	mov r1, #0
	mov r2, #0x1c
	add r3, r5, #0
	bl MOD83_02231DBC
	b _02232CF4
_02232CD4:
	bl FUN_0200E308
	cmp r0, #0
	beq _02232CF4
	ldr r0, _02232D28 ; =0x00002BE0
	ldr r0, [r4, r0]
	str r0, [r5]
	b _02232CF4
_02232CE4:
	bl MOD83_022315F8
	add r0, r4, #0
	bl MOD83_022324A0
	add sp, #8
	mov r0, #1
	pop {r4, r5, r6, pc}
_02232CF4:
	ldr r0, _02232D3C ; =0x00002BE4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02232D00
	bl FUN_0201FDEC
_02232D00:
	bl MOD83_02238D58
	ldr r0, _02232D40 ; =0x00003CE8
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02232D10
	add r0, r4, #0
	blx r1
_02232D10:
	mov r0, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02232D18: .word 0x00002BD0
_02232D1C: .word 0x00002AA8
_02232D20: .word 0x00002A98
_02232D24: .word 0x00002B70
_02232D28: .word 0x00002BE0
_02232D2C: .word 0x00002BD4
_02232D30: .word 0x00002D78
_02232D34: .word 0x00003CF0
_02232D38: .word gMain
_02232D3C: .word 0x00002BE4
_02232D40: .word 0x00003CE8
	thumb_func_end MOD83_02232788

	thumb_func_start MOD83_02232D44
MOD83_02232D44: ; 0x02232D44
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02232DA8 ; =0x00002B60
	mov r2, #0xd6
	ldr r1, [r5, r0]
	sub r0, #0xc
	lsl r1, r1, #2
	add r1, r5, r1
	ldr r4, [r1, r0]
	add r0, r5, #0
	add r0, #0xe0
	add r1, r4, #0
	lsl r2, r2, #2
	bl memcpy
	mov r1, #0x41
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0x90
	add r1, r4, r1
	mov r2, #0x50
	bl memcpy
	ldr r0, _02232DAC ; =0x00000428
	mov r1, #0
	strb r1, [r5, r0]
	add r0, r5, #0
	add r0, #0xde
	ldrb r1, [r0]
	mov r0, #0x10
	mov r2, #0xf
	bic r1, r0
	add r0, r5, #0
	add r0, #0xde
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xde
	ldrb r1, [r0]
	mov r0, #0x20
	orr r1, r0
	add r0, r5, #0
	add r0, #0xde
	strb r1, [r0]
	ldr r1, _02232DB0 ; =0x00002B44
	add r0, r5, #4
	ldr r1, [r5, r1]
	bl MOD83_0222F8C4
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232DA8: .word 0x00002B60
_02232DAC: .word 0x00000428
_02232DB0: .word 0x00002B44
	thumb_func_end MOD83_02232D44

	thumb_func_start MOD83_02232DB4
MOD83_02232DB4: ; 0x02232DB4
	push {r3, r4}
	ldr r3, [r0]
	ldr r1, [r0, #4]
	add r2, r0, #0
	mov r4, #0
	cmp r1, r3
	bge _02232DC8
	add r3, r1, #0
	mov r4, #1
	add r2, r0, #4
_02232DC8:
	ldr r1, [r0, #8]
	cmp r1, r3
	bge _02232DD6
	add r2, r0, #0
	add r3, r1, #0
	mov r4, #2
	add r2, #8
_02232DD6:
	ldr r1, [r0, #0xc]
	cmp r1, r3
	bge _02232DE2
	add r2, r0, #0
	mov r4, #3
	add r2, #0xc
_02232DE2:
	ldr r0, _02232DEC ; =0x3FFF0001
	str r0, [r2]
	add r0, r4, #1
	pop {r3, r4}
	bx lr
	.align 2, 0
_02232DEC: .word 0x3FFF0001
	thumb_func_end MOD83_02232DB4

	thumb_func_start MOD83_02232DF0
MOD83_02232DF0: ; 0x02232DF0
	push {r3, r4, r5, lr}
	mov r5, #0
	mov r4, #1
_02232DF6:
	add r0, r4, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _02232E02
	add r5, r5, #1
_02232E02:
	add r4, r4, #1
	cmp r4, #5
	blt _02232DF6
	add r0, r5, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_02232DF0

	thumb_func_start MOD83_02232E0C
MOD83_02232E0C: ; 0x02232E0C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	add r5, r0, #0
	mov r6, #0
	mov r0, #1
	str r1, [sp, #0x10]
	add r7, r6, #0
	str r0, [sp, #0x24]
	add r4, r5, #4
_02232E1E:
	ldr r0, [sp, #0x24]
	bl FUN_0202DFA4
	cmp r0, #0
	bne _02232E40
	ldr r0, _02232FCC ; =0x00002BA8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02232E32
	add r7, r7, #1
_02232E32:
	ldr r0, _02232FCC ; =0x00002BA8
	mov r1, #0
	str r1, [r4, r0]
	ldr r1, _02232FD0 ; =0x3FFF0001
	add r0, #0x14
	str r1, [r4, r0]
	b _02232E68
_02232E40:
	ldr r1, _02232FCC ; =0x00002BA8
	ldr r1, [r4, r1]
	cmp r1, r0
	beq _02232E66
	ldr r1, _02232FCC ; =0x00002BA8
	add r7, r7, #1
	str r0, [r4, r1]
	add r0, r1, #0
	add r1, #0x34
	ldr r1, [r5, r1]
	add r0, #0x34
	add r2, r1, #1
	ldr r0, [r5, r0]
	ldr r1, _02232FD4 ; =0x00002BDC
	add r6, r6, #1
	str r2, [r5, r1]
	sub r1, #0x20
	str r0, [r4, r1]
	b _02232E68
_02232E66:
	add r6, r6, #1
_02232E68:
	ldr r0, [sp, #0x24]
	add r4, r4, #4
	add r0, r0, #1
	str r0, [sp, #0x24]
	cmp r0, #5
	blt _02232E1E
	cmp r7, #0
	bne _02232E7E
	add sp, #0x48
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_02232E7E:
	mov r1, #0xaf
	lsl r1, r1, #6
	ldr r0, [r5, r1]
	str r0, [sp, #0x38]
	add r0, r1, #4
	ldr r0, [r5, r0]
	str r0, [sp, #0x3c]
	add r0, r1, #0
	add r0, #8
	ldr r0, [r5, r0]
	add r1, #0xc
	str r0, [sp, #0x40]
	ldr r0, [r5, r1]
	str r0, [sp, #0x44]
	add r0, sp, #0x38
	bl MOD83_02232DB4
	str r0, [sp, #0x28]
	add r0, sp, #0x38
	bl MOD83_02232DB4
	str r0, [sp, #0x2c]
	add r0, sp, #0x38
	bl MOD83_02232DB4
	str r0, [sp, #0x30]
	add r0, sp, #0x38
	bl MOD83_02232DB4
	str r0, [sp, #0x34]
	mov r0, #0x57
	bl ScrStrBufs_new
	add r4, r0, #0
	ldr r2, _02232FD8 ; =0x00000172
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x57
	bl NewMsgDataFromNarc
	str r0, [sp, #0x1c]
	mov r5, #0
	ldr r0, [sp, #0x10]
	add r1, r5, #0
	bl FillWindowPixelBuffer
	add r0, r5, #0
	str r0, [sp, #0x14]
	cmp r6, #0
	ble _02232FAE
	add r0, sp, #0x28
	str r0, [sp, #0x18]
_02232EE6:
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	bl FUN_0202DFA4
	add r7, r0, #0
	beq _02232F9E
	add r0, r4, #0
	mov r1, #0
	add r2, r7, #0
	bl BufferPlayersName
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	mov r2, #0x35
	mov r3, #0x57
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x20]
	add r0, r7, #0
	bl PlayerProfile_GetTrainerGender
	cmp r0, #0
	str r5, [sp]
	bne _02232F30
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02232FDC ; =0x00050600
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x20]
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	b _02232F4A
_02232F30:
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0xc1
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	mov r1, #0
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x20]
	add r3, r1, #0
	bl AddTextPrinterParameterized2
_02232F4A:
	ldr r0, [sp, #0x20]
	bl String_dtor
	add r0, r7, #0
	bl PlayerProfile_GetTrainerID
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	lsl r2, r2, #0x10
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	lsr r2, r2, #0x10
	mov r3, #5
	bl BufferIntegerAsString
	ldr r1, [sp, #0x1c]
	add r0, r4, #0
	mov r2, #0x36
	mov r3, #0x57
	bl ReadMsgData_ExpandPlaceholders
	add r7, r0, #0
	str r5, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02232FE0 ; =0x000E0F00
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r2, r7, #0
	mov r3, #0x50
	bl AddTextPrinterParameterized2
	add r0, r7, #0
	bl String_dtor
	add r5, #0x18
_02232F9E:
	ldr r0, [sp, #0x18]
	add r0, r0, #4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	cmp r0, r6
	blt _02232EE6
_02232FAE:
	cmp r6, #0
	beq _02232FB8
	ldr r0, [sp, #0x10]
	bl CopyWindowToVram
_02232FB8:
	ldr r0, [sp, #0x1c]
	bl DestroyMsgData
	add r0, r4, #0
	bl ScrStrBufs_delete
	add r0, r6, #0
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232FCC: .word 0x00002BA8
_02232FD0: .word 0x3FFF0001
_02232FD4: .word 0x00002BDC
_02232FD8: .word 0x00000172
_02232FDC: .word 0x00050600
_02232FE0: .word 0x000E0F00
	thumb_func_end MOD83_02232E0C

	thumb_func_start MOD83_02232FE4
MOD83_02232FE4: ; 0x02232FE4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _02233070 ; =0x00002B94
	add r4, r1, #0
	str r2, [r5, r0]
	ldr r2, _02233074 ; =0x00000172
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x57
	bl NewMsgDataFromNarc
	ldr r1, _02233078 ; =0x000029A4
	str r0, [r5, r1]
	mov r0, #0x57
	bl ScrStrBufs_new
	ldr r1, _0223307C ; =0x000029A0
	str r0, [r5, r1]
	add r0, r4, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r3, #1
	str r3, [sp]
	ldr r0, _0223307C ; =0x000029A0
	str r3, [sp, #4]
	ldr r2, _02233070 ; =0x00002B94
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	mov r1, #0
	bl BufferIntegerAsString
	ldr r1, _0223307C ; =0x000029A0
	mov r2, #0x38
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r3, #0x57
	bl ReadMsgData_ExpandPlaceholders
	add r6, r0, #0
	mov r3, #0
	str r3, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _02233080 ; =0x00010200
	mov r1, #1
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r6, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add r0, r4, #0
	bl CopyWindowToVram
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02233078 ; =0x000029A4
	ldr r0, [r5, r0]
	bl DestroyMsgData
	ldr r0, _0223307C ; =0x000029A0
	ldr r0, [r5, r0]
	bl ScrStrBufs_delete
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_02233070: .word 0x00002B94
_02233074: .word 0x00000172
_02233078: .word 0x000029A4
_0223307C: .word 0x000029A0
_02233080: .word 0x00010200
	thumb_func_end MOD83_02232FE4

	thumb_func_start MOD83_02233084
MOD83_02233084: ; 0x02233084
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl MOD83_0222F9DC
	bl FUN_02033ED0
	ldr r0, _022330A0 ; =0x00002BE0
	str r6, [r5, r0]
	mov r0, #0x16
	str r0, [r4]
	pop {r4, r5, r6, pc}
	nop
_022330A0: .word 0x00002BE0
	thumb_func_end MOD83_02233084

	thumb_func_start MOD83_022330A4
MOD83_022330A4: ; 0x022330A4
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	bl OverlayManager_GetData
	add r7, r0, #0
	ldr r0, _02233154 ; =0x000029A8
	mov r6, #0
	add r4, r7, #0
	add r5, r7, r0
_022330B6:
	ldr r0, _02233154 ; =0x000029A8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022330CA
	add r0, r5, #0
	bl FUN_02019570
	add r0, r5, #0
	bl RemoveWindow
_022330CA:
	add r6, r6, #1
	add r4, #0x10
	add r5, #0x10
	cmp r6, #0x13
	blo _022330B6
	ldr r0, _02233158 ; =0x00002B70
	ldr r1, [r7, r0]
	cmp r1, #0
	beq _022330EA
	add r0, r7, r0
	bl FUN_02019570
	ldr r0, _02233158 ; =0x00002B70
	add r0, r7, r0
	bl RemoveWindow
_022330EA:
	mov r0, #0xae
	lsl r0, r0, #6
	ldr r1, [r7, r0]
	cmp r1, #0
	beq _02233104
	add r0, r7, r0
	bl FUN_02019570
	mov r0, #0xae
	lsl r0, r0, #6
	add r0, r7, r0
	bl RemoveWindow
_02233104:
	ldr r0, _0223315C ; =0x0000299C
	mov r1, #0
	ldr r0, [r7, r0]
	bl FUN_020178A0
	ldr r0, _0223315C ; =0x0000299C
	mov r1, #1
	ldr r0, [r7, r0]
	bl FUN_020178A0
	ldr r0, _0223315C ; =0x0000299C
	mov r1, #2
	ldr r0, [r7, r0]
	bl FUN_020178A0
	ldr r0, _0223315C ; =0x0000299C
	mov r1, #3
	ldr r0, [r7, r0]
	bl FUN_020178A0
	ldr r0, _0223315C ; =0x0000299C
	ldr r0, [r7, r0]
	bl FreeToHeap
	ldr r0, _02233160 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _02233164 ; =MOD83_0223A434
	bl RegisterMainOverlay
	mov r0, #0x5b
	bl DestroyHeap
	ldr r0, [sp]
	bl OverlayManager_FreeData
	mov r0, #0x57
	bl DestroyHeap
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02233154: .word 0x000029A8
_02233158: .word 0x00002B70
_0223315C: .word 0x0000299C
_02233160: .word SDK_OVERLAY_MODULE_83_ID
_02233164: .word MOD83_0223A434
	thumb_func_end MOD83_022330A4

	thumb_func_start MOD83_02233168
MOD83_02233168: ; 0x02233168
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	bl MOD83_022331E0
	ldr r1, _022331B4 ; =0x00003CF4
	add r0, r5, #0
	bl AllocFromHeapAtEnd
	ldr r2, _022331B4 ; =0x00003CF4
	mov r1, #0
	add r4, r0, #0
	bl memset
	ldr r0, _022331B8 ; =0x0000299C
	mov r1, #0x1e
	str r6, [r4, r0]
	mov r0, #0
	lsl r1, r1, #4
	add r2, r5, #0
	str r5, [r4]
	bl FUN_02002ED0
	ldr r0, _022331BC ; =0x00002B54
	mov r2, #0
	str r7, [r4, r0]
	add r0, #0xc
	str r2, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl MOD83_02231DF0
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022331B4: .word 0x00003CF4
_022331B8: .word 0x0000299C
_022331BC: .word 0x00002B54
	thumb_func_end MOD83_02233168

	thumb_func_start MOD83_022331C0
MOD83_022331C0: ; 0x022331C0
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _022331DC ; =MOD83_0223A4D4
	add r3, sp, #0
	mov r2, #5
_022331CA:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _022331CA
	add r0, sp, #0
	bl GX_SetBanks
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_022331DC: .word MOD83_0223A4D4
	thumb_func_end MOD83_022331C0

	thumb_func_start MOD83_022331E0
MOD83_022331E0: ; 0x022331E0
	push {r3, r4, r5, lr}
	sub sp, #0x80
	ldr r5, _022332A0 ; =MOD83_0223A454
	add r3, sp, #0x70
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _022332A4 ; =MOD83_0223A480
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _022332A8 ; =MOD83_0223A4B8
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _022332AC ; =MOD83_0223A49C
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _022332B0 ; =MOD83_0223A464
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	add sp, #0x80
	pop {r3, r4, r5, pc}
	nop
_022332A0: .word MOD83_0223A454
_022332A4: .word MOD83_0223A480
_022332A8: .word MOD83_0223A4B8
_022332AC: .word MOD83_0223A49C
_022332B0: .word MOD83_0223A464
	thumb_func_end MOD83_022331E0

	thumb_func_start MOD83_022332B4
MOD83_022332B4: ; 0x022332B4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	bl FUN_0202251C
	mov r1, #0
	ldr r4, [r5, #0x48]
	mvn r1, r1
	add r6, r0, #0
	cmp r4, r1
	bne _022332E8
	add r2, r5, #0
	add r2, #0x4c
	ldrh r2, [r2]
	lsr r1, r1, #0x10
	cmp r2, r1
	bne _022332E8
	bl FUN_0202AC28
	add r0, r7, #0
	mov r1, #0
	bl FUN_020227A0
	mov r0, #0
	bl OS_ResetSystem
_022332E8:
	cmp r4, #0
	bne _022332F0
	mov r4, #0
	mvn r4, r4
_022332F0:
	.ifdef DIAMOND
	mov r0, #1
	.else
	mov r0, #2
	.endif
	lsl r0, r0, #0xa
	tst r0, r4
	bne _022332FC
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022332FC:
	add r0, r5, #0
	add r0, #0x4e
	ldrb r0, [r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223331E
	add r1, r5, #0
	add r1, #0x4c
	ldrh r1, [r1]
	add r0, r6, #0
	bl FUN_0202AEF4
	cmp r0, #1
	bne _0223331E
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_0223331E:
	add r0, r5, #0
	add r0, #0x4e
	ldrb r0, [r0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223333A
	add r0, r6, #0
	bl FUN_0202AE0C
	cmp r0, #0
	bne _0223333A
	mov r0, #4
	pop {r3, r4, r5, r6, r7, pc}
_0223333A:
	add r0, r6, #0
	bl FUN_0202ADF0
	cmp r0, #0
	bne _02233348
	mov r0, #3
	pop {r3, r4, r5, r6, r7, pc}
_02233348:
	add r5, #0x4e
	ldrb r0, [r5]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _02233358
	mov r0, #5
	pop {r3, r4, r5, r6, r7, pc}
_02233358:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022332B4

	thumb_func_start MOD83_0223335C
MOD83_0223335C: ; 0x0223335C
	push {r3, lr}
	mov r0, #4
	bl MOD83_02234580
	bl MOD83_02234C34
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_0223335C

	thumb_func_start MOD83_0223336C
MOD83_0223336C: ; 0x0223336C
	push {r3, lr}
	bl MOD83_02234704
	str r0, [sp]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_0223336C

	thumb_func_start MOD83_02233378
MOD83_02233378: ; 0x02233378
	push {r3, lr}
	bl MOD83_02234724
	add r1, sp, #0
	strh r0, [r1]
	mov r0, #0
	ldrsh r0, [r1, r0]
	pop {r3, pc}
	thumb_func_end MOD83_02233378

	thumb_func_start MOD83_02233388
MOD83_02233388: ; 0x02233388
	push {r4, lr}
	bl MOD83_0223458C
	cmp r0, #0xc
	bne _022333AA
	bl MOD83_0223456C
	add r4, r0, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	bne _022333A6
	bl MOD83_02234C34
	mov r0, #1
	str r0, [r4, #0x1c]
_022333A6:
	mov r0, #1
	pop {r4, pc}
_022333AA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02233388

	thumb_func_start MOD83_022333B0
MOD83_022333B0: ; 0x022333B0
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223466C
	mov r3, #0
	add r1, r3, #0
_022333BC:
	ldr r2, [r0]
	cmp r2, #0
	beq _022333CC
	ldrh r2, [r0, #6]
	cmp r4, r2
	bne _022333CC
	strb r1, [r0, #8]
	strb r1, [r0, #0xa]
_022333CC:
	add r3, r3, #1
	add r0, #0xc
	cmp r3, #8
	blt _022333BC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_022333B0

	thumb_func_start MOD83_022333D8
MOD83_022333D8: ; 0x022333D8
	push {r3, lr}
	bl MOD83_0223466C
	add r1, r0, #0
	add r1, #0x62
	ldrh r3, [r1]
	mov r2, #1
	add r1, r3, #0
	tst r1, r2
	beq _022333FE
	add r1, r0, #0
	add r1, #0x62
	ldrh r3, [r1]
	mov r1, #1
	add r0, #0x62
	bic r3, r1
	strh r3, [r0]
	add r0, r2, #0
	pop {r3, pc}
_022333FE:
	mov r1, #0x40
	add r2, r3, #0
	tst r2, r1
	beq _02233418
	add r1, r0, #0
	add r1, #0x62
	ldrh r2, [r1]
	mov r1, #0x40
	add r0, #0x62
	bic r2, r1
	strh r2, [r0]
	mov r0, #7
	pop {r3, pc}
_02233418:
	lsl r1, r1, #6
	tst r1, r3
	beq _02233430
	add r1, r0, #0
	add r1, #0x62
	ldrh r2, [r1]
	ldr r1, _02233434 ; =0xFFFFEFFF
	add r0, #0x62
	and r1, r2
	strh r1, [r0]
	mov r0, #0xd
	pop {r3, pc}
_02233430:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_02233434: .word 0xFFFFEFFF
	thumb_func_end MOD83_022333D8

	thumb_func_start MOD83_02233438
MOD83_02233438: ; 0x02233438
	push {r4, lr}
	bl MOD83_0223466C
	add r4, r0, #0
	mov r1, #1
	add r0, #0x60
	strb r1, [r0]
	bl WM_GetAllowedChannel
	add r1, r4, #0
	add r1, #0x62
	strh r0, [r1]
	add r0, r4, #0
	add r0, #0x62
	ldrh r1, [r0]
	cmp r1, #0
	beq _02233462
	mov r0, #2
	lsl r0, r0, #0xe
	cmp r1, r0
	bne _02233466
_02233462:
	mov r0, #0
	pop {r4, pc}
_02233466:
	add r0, r4, #0
	mov r1, #0x66
	add r0, #0x61
	strb r1, [r0]
	mov r0, #0
	add r4, #0x64
	strb r0, [r4]
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD83_02233438

	thumb_func_start MOD83_02233478
MOD83_02233478: ; 0x02233478
	push {r4, lr}
	bl MOD83_02234564
	add r4, r0, #0
	bl WM_GetDispersionBeaconPeriod
	strh r0, [r4, #0x18]
	bl WM_GetNextTgid
	strh r0, [r4, #0xc]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02233478

	thumb_func_start MOD83_02233490
MOD83_02233490: ; 0x02233490
	push {r4, lr}
	bl MOD83_022345D4
	add r4, r0, #0
	bl MOD83_02234610
	str r0, [r4]
	bl MOD83_02234564
	ldrh r0, [r0, #0x32]
	strh r0, [r4, #4]
	bl WM_GetDispersionScanPeriod
	strh r0, [r4, #6]
	mov r0, #0xff
	strb r0, [r4, #8]
	strb r0, [r4, #9]
	strb r0, [r4, #0xa]
	strb r0, [r4, #0xb]
	strb r0, [r4, #0xc]
	strb r0, [r4, #0xd]
	pop {r4, pc}
	thumb_func_end MOD83_02233490

	thumb_func_start MOD83_022334BC
MOD83_022334BC: ; 0x022334BC
	push {r3, r4, r5, r6, r7, lr}
	bl MOD83_022345D4
	add r7, r0, #0
	bl WM_GetAllowedChannel
	add r3, r0, #0
	beq _02233508
	ldrh r2, [r7, #4]
	mov r1, #0
	mov r0, #1
	mov ip, r2
	mov r4, #0x1c
_022334D6:
	lsr r6, r2, #0x1f
	lsl r5, r2, #0x1c
	sub r5, r5, r6
	ror r5, r4
	add r5, r6, r5
	add r6, r0, #0
	lsl r6, r5
	add r5, r3, #0
	tst r5, r6
	beq _02233500
	mov r0, ip
	add r0, r0, r1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1c
	sub r1, r1, r2
	mov r0, #0x1c
	ror r1, r0
	add r0, r2, r1
	add r0, r0, #1
	strh r0, [r7, #4]
	pop {r3, r4, r5, r6, r7, pc}
_02233500:
	add r1, r1, #1
	add r2, r2, #1
	cmp r1, #0x10
	blt _022334D6
_02233508:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD83_022334BC

	thumb_func_start MOD83_0223350C
MOD83_0223350C: ; 0x0223350C
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #4]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #8
	bne _02233524
	bl MOD83_02234958
	bl MOD83_0223335C
_02233524:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_0223350C

	thumb_func_start MOD83_02233528
MOD83_02233528: ; 0x02233528
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #8]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _0223353C
	bl MOD83_02234958
_0223353C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02233528

	thumb_func_start MOD83_02233540
MOD83_02233540: ; 0x02233540
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _02233576
	mov r0, #2
	bl MOD83_02234580
	bl MOD83_0223458C
	cmp r0, #0xc
	bne _02233562
	bl MOD83_022349CC
	mov r0, #2
	bl MOD83_02234580
	pop {r3, pc}
_02233562:
	bl MOD83_02234BF8
	cmp r0, #0
	bne _0223357E
	bl MOD83_022349CC
	mov r0, #2
	bl MOD83_02234580
	pop {r3, pc}
_02233576:
	bl MOD83_02234958
	bl MOD83_022349CC
_0223357E:
	pop {r3, pc}
	thumb_func_end MOD83_02233540

	thumb_func_start MOD83_02233580
MOD83_02233580: ; 0x02233580
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _022335AA
	bl MOD83_0223458C
	cmp r0, #0xc
	bne _022335A2
	bl WM_Finish
	mov r0, #0xc
	bl MOD83_02234580
	mov r0, #1
	bl MOD83_0223464C
	pop {r3, pc}
_022335A2:
	mov r0, #1
	bl MOD83_02234580
	pop {r3, pc}
_022335AA:
	bl MOD83_02234958
	mov r0, #4
	bl MOD83_02234580
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02233580

	thumb_func_start MOD83_022335B8
MOD83_022335B8: ; 0x022335B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrh r0, [r5, #2]
	cmp r0, #0
	bne _02233616
	bl MOD83_0223466C
	add r4, r0, #0
	add r0, #0x61
	ldrh r1, [r5, #0xa]
	ldrb r0, [r0]
	cmp r0, r1
	ble _022335E0
	add r0, r4, #0
	add r0, #0x61
	strb r1, [r0]
	add r0, r4, #0
	ldrh r1, [r5, #8]
	add r0, #0x64
	strb r1, [r0]
_022335E0:
	bl MOD83_022333D8
	cmp r0, #0
	beq _022335F6
	bl MOD83_022349EC
	cmp r0, #0
	bne _0223361E
	bl MOD83_0223335C
	pop {r3, r4, r5, pc}
_022335F6:
	add r4, #0x61
	ldrb r0, [r4]
	cmp r0, #0x66
	bhs _02233610
	bl MOD83_02233478
	bl MOD83_02234A18
	cmp r0, #0
	bne _0223361E
	bl MOD83_0223335C
	pop {r3, r4, r5, pc}
_02233610:
	bl MOD83_0223335C
	pop {r3, r4, r5, pc}
_02233616:
	bl MOD83_02234958
	bl MOD83_0223335C
_0223361E:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_022335B8

	thumb_func_start MOD83_02233620
MOD83_02233620: ; 0x02233620
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _0223363E
	bl MOD83_02233388
	cmp r0, #0
	bne _02233646
	bl MOD83_02234A54
	cmp r0, #0
	bne _02233646
	bl MOD83_0223335C
	pop {r3, pc}
_0223363E:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233646:
	pop {r3, pc}
	thumb_func_end MOD83_02233620

	thumb_func_start MOD83_02233648
MOD83_02233648: ; 0x02233648
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldrh r0, [r5, #8]
	bl MOD83_0223495C
	ldrh r0, [r5, #2]
	cmp r0, #0
	beq _0223365C
	b _0223376E
_0223365C:
	bl MOD83_0223466C
	add r4, r0, #0
	mov r0, #8
	bl MOD83_02234580
	bl MOD83_02233388
	cmp r0, #0
	beq _02233672
	b _02233776
_02233672:
	add r0, r4, #0
	add r0, #0x60
	ldrb r0, [r0]
	cmp r0, #1
	bne _02233684
	add r0, r4, #0
	mov r1, #2
	add r0, #0x60
	strb r1, [r0]
_02233684:
	ldrh r0, [r5, #8]
	cmp r0, #7
	bgt _0223369C
	bge _022336BE
	cmp r0, #2
	bgt _02233776
	cmp r0, #0
	blt _02233776
	beq _022336A4
	add sp, #0xc
	cmp r0, #2
	pop {r4, r5, pc}
_0223369C:
	cmp r0, #9
	beq _02233764
	add sp, #0xc
	pop {r4, r5, pc}
_022336A4:
	bl MOD83_02234B80
	cmp r0, #0
	bne _022336B4
	bl MOD83_0223335C
	add sp, #0xc
	pop {r4, r5, pc}
_022336B4:
	mov r0, #0
	bl MOD83_0223461C
	add sp, #0xc
	pop {r4, r5, pc}
_022336BE:
	bl MOD83_0223466C
	bl MOD83_02234968
	add r4, #0x60
	ldrb r0, [r4]
	cmp r0, #2
	bne _02233776
	add r4, r5, #0
	add r4, #0x14
	bl MOD83_022346BC
	ldr r1, [r5, #0x14]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r0
	bne _02233776
	bl MOD83_022346CC
	ldr r1, [r4]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	cmp r1, r0
	bhi _02233776
	bl MOD83_022346DC
	ldr r1, [r4, #4]
	lsr r1, r1, #0x10
	cmp r1, r0
	bne _02233776
	bl MOD83_0223466C
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xa
	bl MOD83_0223336C
	str r0, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xa
	bl MOD83_02233378
	add r1, sp, #0
	strh r0, [r1]
	ldrh r0, [r1]
	ldr r2, [sp, #8]
	add r3, r4, #0
	strh r0, [r1, #2]
	mov r0, #0
_02233722:
	ldr r1, [r3]
	cmp r1, r2
	bne _0223373A
	mov r1, #0xc
	mul r1, r0
	ldrh r0, [r5, #0x10]
	add r1, r4, r1
	add sp, #0xc
	strh r0, [r1, #6]
	mov r0, #1
	strb r0, [r1, #0xa]
	pop {r4, r5, pc}
_0223373A:
	cmp r1, #0
	bne _02233758
	mov r1, #0xc
	mul r1, r0
	str r2, [r4, r1]
	add r0, sp, #0
	ldrh r0, [r0, #2]
	add r1, r4, r1
	add sp, #0xc
	strh r0, [r1, #4]
	ldrh r0, [r5, #0x10]
	strh r0, [r1, #6]
	mov r0, #1
	strb r0, [r1, #0xa]
	pop {r4, r5, pc}
_02233758:
	add r0, r0, #1
	add r3, #0xc
	cmp r0, #8
	blt _02233722
	add sp, #0xc
	pop {r4, r5, pc}
_02233764:
	ldrh r0, [r5, #0x10]
	bl MOD83_022333B0
	add sp, #0xc
	pop {r4, r5, pc}
_0223376E:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233776:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD83_02233648

	thumb_func_start MOD83_0223377C
MOD83_0223377C: ; 0x0223377C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	str r0, [sp]
	bl MOD83_02234664
	add r7, r0, #0
	add r0, r4, #4
	bl MOD83_0223336C
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r4, #4
	bl MOD83_02233378
	add r2, sp, #4
	strh r0, [r2]
	ldrh r0, [r2]
	ldr r6, [sp, #0xc]
	add r1, r7, #0
	strh r0, [r2, #2]
	ldrh r3, [r2, #2]
	mov r0, #0
_022337AA:
	ldr r2, [r1]
	add r5, r1, #0
	add r5, #0x34
	cmp r2, r6
	bne _022337C0
	ldrh r5, [r5]
	cmp r5, r3
	bne _022337C0
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022337C0:
	cmp r2, #0
	bne _0223380C
	mov r1, #0x38
	mul r1, r0
	ldr r0, [sp, #0xc]
	add r5, r4, #0
	str r0, [r7, r1]
	add r0, r7, r1
	add r5, #0x58
	add r3, r0, #4
	mov r2, #0xc
_022337D6:
	ldrh r0, [r5]
	add r5, r5, #2
	strh r0, [r3]
	add r3, r3, #2
	sub r2, r2, #1
	bne _022337D6
	add r3, r7, r1
	add r4, #0x70
	add r3, #0x1c
	mov r2, #0xc
_022337EA:
	ldrh r0, [r4]
	add r4, r4, #2
	strh r0, [r3]
	add r3, r3, #2
	sub r2, r2, #1
	bne _022337EA
	add r0, sp, #4
	ldrh r0, [r0, #2]
	add r1, r7, r1
	strh r0, [r1, #0x34]
	ldr r0, [sp]
	add r1, #0x36
	ldrh r0, [r0, #0x12]
	add sp, #0x10
	strb r0, [r1]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223380C:
	add r0, r0, #1
	add r1, #0x38
	cmp r0, #8
	blt _022337AA
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD83_0223377C

	thumb_func_start MOD83_0223381C
MOD83_0223381C: ; 0x0223381C
	push {r3, lr}
	bl MOD83_022334BC
	bl MOD83_02234A70
	cmp r0, #0
	bne _0223382E
	bl MOD83_0223335C
_0223382E:
	pop {r3, pc}
	thumb_func_end MOD83_0223381C

	thumb_func_start MOD83_02233830
MOD83_02233830: ; 0x02233830
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD83_02234610
	add r4, r0, #0
	bl MOD83_02234664
	add r5, r0, #0
	bl MOD83_02233388
	cmp r0, #0
	beq _0223384C
	mov r0, #1
	pop {r4, r5, r6, pc}
_0223384C:
	mov r1, #0
	add r2, r1, #0
	add r3, r5, #0
_02233852:
	ldr r0, [r3]
	cmp r0, #0
	beq _0223385C
	mov r1, #1
	b _02233864
_0223385C:
	add r2, r2, #1
	add r3, #0x38
	cmp r2, #8
	blt _02233852
_02233864:
	cmp r1, #0
	beq _02233882
	mov r0, #7
	lsl r0, r0, #6
	ldrh r0, [r5, r0]
	cmp r0, #0
	bne _02233882
	bl MOD83_02234B2C
	cmp r0, #0
	bne _0223387E
	bl MOD83_0223335C
_0223387E:
	mov r0, #1
	pop {r4, r5, r6, pc}
_02233882:
	add r0, r4, #0
	mov r1, #0xc0
	bl DC_InvalidateRange
	bl MOD83_02234664
	bl MOD83_02234964
	ldrh r0, [r6, #0x36]
	cmp r0, #8
	blo _0223390C
	bl MOD83_022346B0
	ldr r1, [r4, #0x44]
	cmp r1, r0
	bne _0223390C
	add r5, r4, #0
	add r5, #0x50
	bl MOD83_022346BC
	ldr r1, [r4, #0x50]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r0
	bne _0223390C
	bl MOD83_022346CC
	ldr r1, [r5]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	cmp r1, r0
	bhi _0223390C
	bl MOD83_022346DC
	ldr r1, [r5, #4]
	lsr r1, r1, #0x10
	cmp r1, r0
	bne _0223390C
	add r0, r6, #0
	add r1, r4, #0
	bl MOD83_0223377C
	cmp r0, #0
	beq _022338FC
	bl MOD83_02234664
	ldr r1, _02233910 ; =0x000001C2
	ldrb r2, [r0, r1]
	add r2, r2, #1
	strb r2, [r0, r1]
	ldrb r0, [r0, r1]
	cmp r0, #0x1c
	bls _0223390C
	bl MOD83_02234B2C
	cmp r0, #0
	bne _0223390C
	bl MOD83_0223335C
	mov r0, #1
	pop {r4, r5, r6, pc}
_022338FC:
	bl MOD83_02234B2C
	cmp r0, #0
	bne _02233908
	bl MOD83_0223335C
_02233908:
	mov r0, #1
	pop {r4, r5, r6, pc}
_0223390C:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02233910: .word 0x000001C2
	thumb_func_end MOD83_02233830

	thumb_func_start MOD83_02233914
MOD83_02233914: ; 0x02233914
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #8]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #0
	bne _0223397A
	bl MOD83_02234610
	bl MOD83_02234960
	mov r0, #6
	bl MOD83_02234580
	bl MOD83_02233388
	cmp r0, #0
	bne _02233982
	bl MOD83_022345A4
	cmp r0, #1
	bne _02233954
	bl MOD83_02234664
	ldr r2, _02233984 ; =0x000001C3
	mov r1, #0xf0
	ldrb r3, [r0, r2]
	bic r3, r1
	mov r1, #0x10
	orr r1, r3
	strb r1, [r0, r2]
_02233954:
	ldrh r0, [r4, #8]
	cmp r0, #4
	beq _02233968
	cmp r0, #5
	bne _0223396E
	add r0, r4, #0
	bl MOD83_02233830
	cmp r0, #0
	bne _02233982
_02233968:
	bl MOD83_0223381C
	pop {r4, pc}
_0223396E:
	ldrh r0, [r4, #2]
	bl MOD83_02234958
	bl MOD83_0223335C
	pop {r4, pc}
_0223397A:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233982:
	pop {r4, pc}
	.align 2, 0
_02233984: .word 0x000001C3
	thumb_func_end MOD83_02233914

	thumb_func_start MOD83_02233988
MOD83_02233988: ; 0x02233988
	push {r4, r5, r6, lr}
	sub sp, #8
	bl MOD83_02234610
	add r4, r0, #0
	bl MOD83_02234664
	add r6, r0, #0
	bl MOD83_02234564
	bl MOD83_02233388
	cmp r0, #0
	beq _022339AA
	add sp, #8
	mov r0, #1
	pop {r4, r5, r6, pc}
_022339AA:
	add r0, r4, #0
	mov r1, #0xc0
	bl DC_InvalidateRange
	bl MOD83_02234664
	bl MOD83_02234964
	ldrh r0, [r4, #0x3c]
	cmp r0, #8
	blo _02233A24
	bl MOD83_022346B0
	ldr r1, [r4, #0x44]
	cmp r1, r0
	bne _02233A24
	add r5, r4, #0
	add r5, #0x50
	bl MOD83_022346BC
	ldr r1, [r4, #0x50]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r0
	bne _02233A24
	bl MOD83_022346CC
	ldr r1, [r5]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	cmp r1, r0
	bhi _02233A24
	bl MOD83_022346DC
	ldr r1, [r5, #4]
	lsr r1, r1, #0x10
	cmp r1, r0
	bne _02233A24
	add r0, r4, #4
	bl MOD83_0223336C
	ldr r1, _02233A2C ; =0x000001C3
	str r0, [sp]
	ldrb r1, [r6, r1]
	str r0, [sp, #4]
	lsl r1, r1, #0x1c
	lsr r2, r1, #0x1c
	mov r1, #0x38
	mul r1, r2
	ldr r1, [r6, r1]
	cmp r1, r0
	bne _02233A24
	bl MOD83_02234B2C
	cmp r0, #0
	bne _02233A1E
	bl MOD83_0223335C
_02233A1E:
	add sp, #8
	mov r0, #1
	pop {r4, r5, r6, pc}
_02233A24:
	mov r0, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02233A2C: .word 0x000001C3
	thumb_func_end MOD83_02233988

	thumb_func_start MOD83_02233A30
MOD83_02233A30: ; 0x02233A30
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #8]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #0
	bne _02233A90
	bl MOD83_02234664
	ldr r2, _02233A9C ; =0x000001C3
	mov r1, #0xf0
	ldrb r3, [r0, r2]
	bic r3, r1
	mov r1, #0x20
	orr r1, r3
	strb r1, [r0, r2]
	mov r0, #6
	bl MOD83_02234580
	bl MOD83_02233388
	cmp r0, #0
	bne _02233A98
	ldrh r0, [r4, #8]
	cmp r0, #4
	beq _02233A72
	cmp r0, #5
	bne _02233A84
	bl MOD83_02233988
	cmp r0, #0
	bne _02233A98
_02233A72:
	bl MOD83_022334BC
	bl MOD83_02234A94
	cmp r0, #0
	bne _02233A98
	bl MOD83_0223335C
	pop {r4, pc}
_02233A84:
	ldrh r0, [r4, #2]
	bl MOD83_02234958
	bl MOD83_0223335C
	pop {r4, pc}
_02233A90:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233A98:
	pop {r4, pc}
	nop
_02233A9C: .word 0x000001C3
	thumb_func_end MOD83_02233A30

	thumb_func_start MOD83_02233AA0
MOD83_02233AA0: ; 0x02233AA0
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _02233AE4
	mov r0, #7
	bl MOD83_02234580
	bl MOD83_02233388
	cmp r0, #0
	bne _02233AEC
	bl MOD83_022345A4
	cmp r0, #1
	bne _02233AEC
	bl MOD83_02234664
	ldr r1, _02233AF0 ; =0x000001C3
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #2
	bne _02233AEC
	bl MOD83_02234B48
	cmp r0, #0
	bne _02233ADC
	bl MOD83_0223335C
	pop {r3, pc}
_02233ADC:
	mov r0, #3
	bl MOD83_02234580
	pop {r3, pc}
_02233AE4:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233AEC:
	pop {r3, pc}
	nop
_02233AF0: .word 0x000001C3
	thumb_func_end MOD83_02233AA0

	thumb_func_start MOD83_02233AF4
MOD83_02233AF4: ; 0x02233AF4
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #8]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #0
	bne _02233B7A
	mov r0, #9
	bl MOD83_02234580
	bl MOD83_02233388
	cmp r0, #0
	bne _02233B82
	ldrh r0, [r4, #8]
	cmp r0, #9
	bhi _02233B6E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02233B24: ; jump table
	.short _02233B6E - _02233B24 - 2 ; case 0
	.short _02233B6E - _02233B24 - 2 ; case 1
	.short _02233B6E - _02233B24 - 2 ; case 2
	.short _02233B6E - _02233B24 - 2 ; case 3
	.short _02233B6E - _02233B24 - 2 ; case 4
	.short _02233B6E - _02233B24 - 2 ; case 5
	.short _02233B82 - _02233B24 - 2 ; case 6
	.short _02233B38 - _02233B24 - 2 ; case 7
	.short _02233B82 - _02233B24 - 2 ; case 8
	.short _02233B58 - _02233B24 - 2 ; case 9
_02233B38:
	ldrh r0, [r4, #0xa]
	bl MOD83_0223461C
	mov r0, #1
	bl MOD83_02234634
	mov r0, #0
	bl MOD83_02234640
	bl MOD83_02234B80
	cmp r0, #0
	bne _02233B82
	bl MOD83_0223335C
	pop {r4, pc}
_02233B58:
	bl MOD83_02234628
	cmp r0, #0
	beq _02233B66
	mov r0, #1
	bl MOD83_02234640
_02233B66:
	mov r0, #0
	bl MOD83_02234634
	pop {r4, pc}
_02233B6E:
	ldrh r0, [r4, #2]
	bl MOD83_02234958
	bl MOD83_0223335C
	pop {r4, pc}
_02233B7A:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233B82:
	pop {r4, pc}
	thumb_func_end MOD83_02233AF4

	thumb_func_start MOD83_02233B84
MOD83_02233B84: ; 0x02233B84
	push {r3, lr}
	bl MOD83_022345A4
	cmp r0, #1
	beq _02233BBE
	cmp r0, #2
	bne _02233BD6
	bl MOD83_02233438
	cmp r0, #0
	beq _02233BB8
	bl MOD83_022333D8
	bl MOD83_022349EC
	cmp r0, #0
	beq _02233BB8
	bl MOD83_0223466C
	mov r1, #1
	add r0, #0x60
	strb r1, [r0]
	mov r0, #3
	bl MOD83_02234580
	pop {r3, pc}
_02233BB8:
	bl MOD83_0223335C
	pop {r3, pc}
_02233BBE:
	bl MOD83_02233490
	bl MOD83_02234A70
	cmp r0, #0
	bne _02233BD0
	bl MOD83_0223335C
	pop {r3, pc}
_02233BD0:
	mov r0, #3
	bl MOD83_02234580
_02233BD6:
	pop {r3, pc}
	thumb_func_end MOD83_02233B84

	thumb_func_start MOD83_02233BD8
MOD83_02233BD8: ; 0x02233BD8
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #4]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #0
	bne _02233C12
	ldrh r0, [r4]
	cmp r0, #0xe
	bne _02233BF6
	bl MOD83_02233388
	cmp r0, #0
	bne _02233C22
_02233BF6:
	bl MOD83_022345A4
	cmp r0, #1
	beq _02233C0A
	cmp r0, #2
	bne _02233C22
	mov r0, #0xa
	bl MOD83_02234580
	pop {r4, pc}
_02233C0A:
	mov r0, #0xb
	bl MOD83_02234580
	pop {r4, pc}
_02233C12:
	cmp r0, #9
	beq _02233C22
	cmp r0, #0xd
	beq _02233C22
	cmp r0, #0xf
	beq _02233C22
	bl MOD83_0223335C
_02233C22:
	pop {r4, pc}
	thumb_func_end MOD83_02233BD8

	thumb_func_start MOD83_02233C24
MOD83_02233C24: ; 0x02233C24
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD83_02234694
	add r4, r0, #0
	ldrb r0, [r4, #0x19]
	cmp r0, #1
	bne _02233C9A
	ldrh r1, [r6, #0x10]
	ldr r0, [r6, #0xc]
	ldr r5, [r4, #0xc]
	bl DC_FlushRange
	ldrh r2, [r6, #0x10]
	ldr r0, [r6, #0xc]
	ldr r1, [r4, #0xc]
	bl MI_CpuCopy8
	bl MOD83_022346BC
	ldr r1, [r5]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r0
	bne _02233C9A
	bl MOD83_022346CC
	ldr r1, [r5]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	cmp r1, r0
	bhi _02233C9A
	ldr r0, [r4, #0xc]
	bl MOD83_02234900
	ldr r0, [r5, #8]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldrb r0, [r4, #0x1c]
	cmp r1, r0
	bne _02233C9A
	ldr r0, [r4, #0xc]
	bl MOD83_0223496C
	ldr r0, [r4, #0xc]
	bl MOD83_02234934
	cmp r0, #0
	beq _02233C96
	ldr r0, [r5, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x18
	cmp r0, #1
	beq _02233C96
	mov r0, #2
	strb r0, [r4, #0x19]
	pop {r4, r5, r6, pc}
_02233C96:
	mov r0, #0
	strb r0, [r4, #0x19]
_02233C9A:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD83_02233C24

	thumb_func_start MOD83_02233C9C
MOD83_02233C9C: ; 0x02233C9C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD83_02234694
	add r4, r0, #0
	bl MOD83_022345A4
	cmp r0, #2
	bne _02233D24
	ldrb r0, [r4, #0x19]
	cmp r0, #2
	beq _02233D24
	ldrh r1, [r6, #0x10]
	ldr r0, [r6, #0xc]
	ldr r5, [r4, #0xc]
	bl DC_FlushRange
	ldrh r2, [r6, #0x10]
	ldr r0, [r6, #0xc]
	ldr r1, [r4, #0xc]
	bl MI_CpuCopy8
	bl MOD83_022346BC
	ldr r1, [r5]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r0
	bne _02233D24
	bl MOD83_022346CC
	ldr r1, [r5]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	cmp r1, r0
	bhi _02233D24
	ldr r0, [r4, #0xc]
	bl MOD83_02234900
	ldr r0, [r5, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0xfd
	bne _02233D24
	bl MOD83_0223466C
	ldrh r5, [r6, #0x12]
	mov r2, #0
	add r3, r0, #0
_02233CFE:
	ldrh r1, [r3, #6]
	cmp r5, r1
	bne _02233D1C
	mov r1, #0xc
	mul r1, r2
	add r1, r0, r1
	mov r2, #1
	strb r2, [r1, #8]
	mov r0, #3
	strb r0, [r1, #9]
	mov r0, #0xb4
	strb r0, [r4, #0x1a]
	mov r0, #0
	strb r0, [r4, #0x19]
	pop {r4, r5, r6, pc}
_02233D1C:
	add r2, r2, #1
	add r3, #0xc
	cmp r2, #8
	blt _02233CFE
_02233D24:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_02233C9C

	thumb_func_start MOD83_02233D28
MOD83_02233D28: ; 0x02233D28
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl MOD83_02234694
	add r4, r0, #0
	ldrb r0, [r4, #0x1c]
	cmp r0, #0xfd
	bne _02233D40
	add r0, r6, #0
	bl MOD83_02233C9C
	pop {r4, r5, r6, pc}
_02233D40:
	ldrb r0, [r4, #0x19]
	cmp r0, #1
	beq _02233D4C
	ldrb r0, [r4, #0x19]
	cmp r0, #3
	bne _02233DE8
_02233D4C:
	ldrb r0, [r4, #0x1b]
	cmp r0, #0
	bne _02233DE8
	ldrh r1, [r6, #0x10]
	ldr r0, [r6, #0xc]
	ldr r5, [r4, #0xc]
	bl DC_FlushRange
	ldrh r2, [r6, #0x10]
	ldr r0, [r6, #0xc]
	ldr r1, [r4, #0xc]
	bl MI_CpuCopy8
	bl MOD83_022346BC
	ldr r1, [r5]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, r0
	bne _02233DE8
	bl MOD83_022346CC
	ldr r1, [r5]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	cmp r1, r0
	bhi _02233DE8
	ldr r0, [r4, #0xc]
	bl MOD83_02234900
	ldr r0, [r5, #8]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldrb r0, [r4, #0x1c]
	cmp r1, r0
	bne _02233DE8
	ldr r0, [r4, #0xc]
	bl MOD83_0223496C
	mov r0, #0
	strb r0, [r4, #0x19]
	ldr r0, [r4, #0xc]
	bl MOD83_02234934
	cmp r0, #0
	beq _02233DDA
	ldr r0, [r5, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0xfd
	bne _02233DBA
	add r0, r6, #0
	bl MOD83_02233C9C
	b _02233DCC
_02233DBA:
	ldr r2, [r5, #0xc]
	ldr r1, [r4, #0xc]
	lsl r0, r2, #0x18
	lsr r0, r0, #0x18
	add r0, r1, r0
	ldr r1, [r4, #4]
	lsr r2, r2, #8
	bl MI_CpuCopy8
_02233DCC:
	ldr r1, [r5, #8]
	ldr r0, _02233DEC ; =0xFFFF00FF
	and r0, r1
	str r0, [r5, #8]
	mov r0, #4
	strb r0, [r4, #0x1b]
	pop {r4, r5, r6, pc}
_02233DDA:
	ldr r1, [r5, #8]
	ldr r0, _02233DEC ; =0xFFFF00FF
	and r1, r0
	mov r0, #1
	lsl r0, r0, #8
	orr r0, r1
	str r0, [r5, #8]
_02233DE8:
	pop {r4, r5, r6, pc}
	nop
_02233DEC: .word 0xFFFF00FF
	thumb_func_end MOD83_02233D28

	thumb_func_start MOD83_02233DF0
MOD83_02233DF0: ; 0x02233DF0
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #4]
	bl MOD83_0223495C
	ldrh r0, [r4, #2]
	cmp r0, #0
	bne _02233E72
	ldrh r0, [r4, #4]
	cmp r0, #7
	beq _02233E3A
	cmp r0, #9
	beq _02233E48
	cmp r0, #0x15
	bne _02233E72
	bl MOD83_02234574
	cmp r0, #0xa
	beq _02233E1A
	cmp r0, #0xb
	bne _02233E72
_02233E1A:
	bl MOD83_02234694
	ldrb r0, [r0, #0x18]
	cmp r0, #1
	beq _02233E2A
	cmp r0, #2
	beq _02233E32
	pop {r4, pc}
_02233E2A:
	add r0, r4, #0
	bl MOD83_02233C24
	pop {r4, pc}
_02233E32:
	add r0, r4, #0
	bl MOD83_02233D28
	pop {r4, pc}
_02233E3A:
	mov r0, #1
	bl MOD83_02234634
	mov r0, #0
	bl MOD83_02234640
	pop {r4, pc}
_02233E48:
	bl MOD83_02234628
	cmp r0, #0
	beq _02233E56
	mov r0, #1
	bl MOD83_02234640
_02233E56:
	bl MOD83_02234574
	cmp r0, #0xa
	beq _02233E64
	cmp r0, #0xb
	beq _02233E6C
	pop {r4, pc}
_02233E64:
	ldrh r0, [r4, #0x12]
	bl MOD83_022333B0
	pop {r4, pc}
_02233E6C:
	mov r0, #0
	bl MOD83_02234634
_02233E72:
	pop {r4, pc}
	thumb_func_end MOD83_02233DF0

	thumb_func_start MOD83_02233E74
MOD83_02233E74: ; 0x02233E74
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _02233E8A
	bl MOD83_02233388
	cmp r0, #0
	bne _02233E94
	bl MOD83_02233B84
	pop {r3, pc}
_02233E8A:
	bl MOD83_02234958
	mov r0, #4
	bl MOD83_02234580
_02233E94:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02233E74

	thumb_func_start MOD83_02233E98
MOD83_02233E98: ; 0x02233E98
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _02233EB0
	bl MOD83_022349CC
	cmp r0, #0
	beq _02233EB8
	mov r0, #2
	bl MOD83_02234580
	pop {r3, pc}
_02233EB0:
	bl MOD83_02234958
	bl MOD83_0223335C
_02233EB8:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02233E98

	thumb_func_start MOD83_02233EBC
MOD83_02233EBC: ; 0x02233EBC
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _02233EF2
	mov r0, #0
	bl MOD83_0223461C
	bl MOD83_0223458C
	cmp r0, #0xc
	bne _02233EE2
	bl MOD83_02234C54
	cmp r0, #0
	beq _02233EFC
	mov r0, #3
	bl MOD83_02234580
	pop {r3, pc}
_02233EE2:
	bl MOD83_02234C14
	cmp r0, #0
	beq _02233EFC
	mov r0, #3
	bl MOD83_02234580
	pop {r3, pc}
_02233EF2:
	bl MOD83_02234958
	mov r0, #4
	bl MOD83_02234580
_02233EFC:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02233EBC

	thumb_func_start MOD83_02233F00
MOD83_02233F00: ; 0x02233F00
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	bne _02233F16
	mov r0, #0xc
	bl MOD83_02234580
	mov r0, #1
	bl MOD83_0223464C
	pop {r3, pc}
_02233F16:
	bl MOD83_02234958
	mov r0, #4
	bl MOD83_02234580
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02233F00

	thumb_func_start MOD83_02233F24
MOD83_02233F24: ; 0x02233F24
	push {r3, lr}
	ldr r0, _02233F40 ; =MOD83_0223350C
	bl WM_SetIndCallback
	cmp r0, #0
	beq _02233F3A
	mov r0, #4
	bl MOD83_02234580
	mov r0, #0
	pop {r3, pc}
_02233F3A:
	mov r0, #1
	pop {r3, pc}
	nop
_02233F40: .word MOD83_0223350C
	thumb_func_end MOD83_02233F24

	thumb_func_start MOD83_02233F44
MOD83_02233F44: ; 0x02233F44
	push {r3, lr}
	bl MOD83_02234574
	cmp r0, #0
	beq _02233F56
	cmp r0, #1
	beq _02233F56
	cmp r0, #2
	bne _02233F5A
_02233F56:
	bl MOD83_022349B0
_02233F5A:
	pop {r3, pc}
	thumb_func_end MOD83_02233F44

	thumb_func_start MOD83_02233F5C
MOD83_02233F5C: ; 0x02233F5C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl MOD83_02234564
	ldrh r0, [r0, #0x34]
	cmp r4, r0
	bhi _02233F80
	add r0, r5, #0
	add r1, r4, #0
	bl DC_FlushRange
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD83_02234970
_02233F80:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_02233F5C

	thumb_func_start MOD83_02233F84
MOD83_02233F84: ; 0x02233F84
	mov r0, #0x17
	lsl r0, r0, #6
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02233F84

	thumb_func_start MOD83_02233F8C
MOD83_02233F8C: ; 0x02233F8C
	mov r0, #0x17
	lsl r0, r0, #6
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02233F8C

	thumb_func_start MOD83_02233F94
MOD83_02233F94: ; 0x02233F94
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	bl MOD83_02234564
	bl MOD83_0223456C
	add r4, r0, #0
	mov r0, #0x1f
	add r1, r7, #0
	and r1, r0
	beq _02233FB2
	mov r0, #0x20
	sub r0, r0, r1
	add r7, r7, r0
_02233FB2:
	mov r1, #0
	strb r1, [r4]
	strb r1, [r4, #1]
	strb r1, [r4, #2]
	mov r0, #4
	strb r0, [r4, #3]
	ldr r0, _022340B8 ; =0x00400131
	str r0, [r4, #4]
	mov r0, #0xf
	strh r1, [r4, #0xc]
	lsl r0, r0, #8
	str r7, [r4, #0x34]
	add r7, r7, r0
	str r7, [r4, #0x38]
	bl MOD83_02233F84
	str r0, [r4, #0x2c]
	add r7, r7, r0
	str r7, [r4, #0x3c]
	bl MOD83_02233F8C
	add r7, r7, r0
	str r0, [r4, #0x30]
	add r0, r7, #0
	str r7, [r4, #0x28]
	add r0, #0xc0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x34]
	mov r1, #2
	add r7, #0xe0
	bl WM_Init
	bl MOD83_02233F24
	str r0, [r4, #0x10]
	mov r2, #0
	str r2, [r4, #0x14]
	str r2, [r4, #0x18]
	str r2, [r4, #0x1c]
	str r2, [r4, #0x20]
	ldr r0, [r4, #0x40]
	mov r6, #0xff
	bic r0, r6
	add r3, r0, #0
	mov r1, #0xf
	orr r3, r1
	ldr r0, _022340BC ; =0xFFFFF0FF
	add r1, #0xf1
	and r0, r3
	orr r1, r0
	ldr r0, _022340C0 ; =0xFFFF0FFF
	and r1, r0
	mov r0, #1
	lsl r0, r0, #0xc
	orr r0, r1
	str r0, [r4, #0x40]
	ldr r3, [r5]
	ldr r1, [r4, #0x44]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	lsl r3, r3, #0x18
	add r0, r4, #0
	bic r1, r6
	lsr r3, r3, #0x18
	orr r3, r1
	ldr r1, _022340BC ; =0xFFFFF0FF
	str r3, [r4, #0x44]
	and r1, r3
	ldr r3, [r5]
	add r0, #0x44
	lsl r3, r3, #0x14
	lsr r3, r3, #0x1c
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x14
	orr r3, r1
	ldr r1, _022340C0 ; =0xFFFF0FFF
	str r3, [r4, #0x44]
	and r1, r3
	ldr r3, [r5]
	lsl r3, r3, #0x10
	lsr r3, r3, #0x1c
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x10
	orr r1, r3
	str r1, [r4, #0x44]
	ldr r1, [r0]
	ldr r3, [r5]
	lsl r1, r1, #0x10
	lsr r3, r3, #0x10
	lsr r1, r1, #0x10
	lsl r3, r3, #0x10
	orr r1, r3
	str r1, [r0]
	ldr r0, [r5, #8]
	ldr r1, [r5, #4]
	add r3, r4, #0
	b _0223408C
_02234074:
	ldrh r6, [r0]
	add r5, r3, #0
	add r5, #0x48
	strh r6, [r5]
	add r5, r3, #0
	ldrh r6, [r1]
	add r5, #0x60
	add r3, r3, #2
	strh r6, [r5]
	add r2, r2, #1
	add r0, r0, #2
	add r1, r1, #2
_0223408C:
	cmp r0, #0
	beq _02234094
	cmp r2, #0xc
	blo _02234074
_02234094:
	ldr r1, [r4, #0x40]
	ldr r0, [r4, #0x44]
	str r1, [r4, #0x78]
	str r0, [r4, #0x7c]
	bl MOD83_022346A4
	bl MOD83_02234694
	str r7, [r0, #8]
	ldr r0, [r4, #0x2c]
	add r7, r7, r0
	bl MOD83_02234694
	str r7, [r0, #0xc]
	bl WM_GetNextTgid
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022340B8: .word 0x00400131
_022340BC: .word 0xFFFFF0FF
_022340C0: .word 0xFFFF0FFF
	thumb_func_end MOD83_02233F94

	thumb_func_start MOD83_022340C4
MOD83_022340C4: ; 0x022340C4
	push {r3, r4, r5, lr}
	bl MOD83_02234694
	add r4, r0, #0
	ldrb r0, [r4, #0x19]
	cmp r0, #1
	bne _022340E2
	ldrb r0, [r4, #0x1a]
	sub r0, r0, #1
	strb r0, [r4, #0x1a]
	ldrb r0, [r4, #0x1a]
	cmp r0, #0
	bne _02234118
	mov r0, #0
	strb r0, [r4, #0x19]
_022340E2:
	ldrb r0, [r4, #0x19]
	cmp r0, #0
	bne _02234118
	bl MOD83_02234770
	mov r1, #0x40
	sub r5, r1, r0
	ldrb r0, [r4, #0x1c]
	add r2, r5, #0
	mov r3, #3
	str r0, [sp]
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	bl MOD83_022347D0
	bl MOD83_02234770
	add r1, r0, #0
	ldr r0, [r4, #8]
	ldr r2, _0223411C ; =0x0000FFFF
	add r1, r5, r1
	bl MOD83_02233F5C
	mov r0, #1
	strb r0, [r4, #0x19]
	mov r0, #0x3c
	strb r0, [r4, #0x1a]
_02234118:
	pop {r3, r4, r5, pc}
	nop
_0223411C: .word 0x0000FFFF
	thumb_func_end MOD83_022340C4

	thumb_func_start MOD83_02234120
MOD83_02234120: ; 0x02234120
	push {r3, r4, r5, r6, r7, lr}
	bl MOD83_02234694
	add r4, r0, #0
	ldrb r0, [r4, #0x19]
	cmp r0, #0
	bne _022341D6
	ldrb r0, [r4, #0x1c]
	cmp r0, #0xfd
	bne _02234198
	bl MOD83_0223466C
	add r5, r0, #0
	mov r1, #0
	add r2, r5, #0
_0223413E:
	ldrb r0, [r2, #9]
	cmp r0, #0
	beq _0223417E
	add r6, r1, #0
	mov r0, #0xc
	mul r6, r0
	add r0, r5, r6
	ldrh r0, [r0, #6]
	mov r1, #1
	mov r2, #0
	lsl r1, r0
	lsl r0, r1, #0x10
	lsr r7, r0, #0x10
	mov r0, #0xfd
	str r0, [sp]
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	add r3, r2, #0
	bl MOD83_022347D0
	bl MOD83_02234770
	add r1, r0, #0
	ldr r0, [r4, #8]
	add r2, r7, #0
	bl MOD83_02233F5C
	add r5, #9
	ldrb r0, [r5, r6]
	sub r0, r0, #1
	strb r0, [r5, r6]
	pop {r3, r4, r5, r6, r7, pc}
_0223417E:
	add r1, r1, #1
	add r2, #0xc
	cmp r1, #8
	blt _0223413E
	ldrb r0, [r4, #0x1a]
	sub r0, r0, #1
	strb r0, [r4, #0x1a]
	ldrb r0, [r4, #0x1a]
	cmp r0, #0
	bne _022341D6
	mov r0, #2
	strb r0, [r4, #0x19]
	pop {r3, r4, r5, r6, r7, pc}
_02234198:
	bl MOD83_02234770
	bl MOD83_02233F84
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #8]
	lsl r0, r0, #0x10
	lsr r3, r0, #0x18
	bne _022341BA
	ldrb r0, [r4, #0x1b]
	cmp r0, #0
	bne _022341B6
	mov r0, #2
	strb r0, [r4, #0x19]
	pop {r3, r4, r5, r6, r7, pc}
_022341B6:
	sub r0, r0, #1
	strb r0, [r4, #0x1b]
_022341BA:
	ldrb r0, [r4, #0x1c]
	mov r2, #0
	str r0, [sp]
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	bl MOD83_022347D0
	bl MOD83_02234770
	add r1, r0, #0
	ldr r0, [r4, #8]
	ldr r2, _022341D8 ; =0x0000FFFF
	bl MOD83_02233F5C
_022341D6:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022341D8: .word 0x0000FFFF
	thumb_func_end MOD83_02234120

	thumb_func_start MOD83_022341DC
MOD83_022341DC: ; 0x022341DC
	push {r3, lr}
	bl MOD83_02234694
	ldrb r0, [r0, #0x18]
	cmp r0, #1
	beq _022341EE
	cmp r0, #2
	beq _022341F4
	pop {r3, pc}
_022341EE:
	bl MOD83_022340C4
	pop {r3, pc}
_022341F4:
	bl MOD83_02234120
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022341DC

	thumb_func_start MOD83_022341FC
MOD83_022341FC: ; 0x022341FC
	push {r4, lr}
	bl MOD83_02234664
	add r4, r0, #0
	bl MOD83_02234574
	cmp r0, #6
	beq _02234212
	cmp r0, #0xb
	beq _02234222
	pop {r4, pc}
_02234212:
	mov r0, #7
	lsl r0, r0, #6
	ldrh r1, [r4, r0]
	cmp r1, #0
	beq _02234226
	sub r1, r1, #1
	strh r1, [r4, r0]
	pop {r4, pc}
_02234222:
	bl MOD83_022341DC
_02234226:
	pop {r4, pc}
	thumb_func_end MOD83_022341FC

	thumb_func_start MOD83_02234228
MOD83_02234228: ; 0x02234228
	push {r3, lr}
	bl MOD83_02234574
	cmp r0, #0xa
	bne _02234236
	bl MOD83_022341DC
_02234236:
	pop {r3, pc}
	thumb_func_end MOD83_02234228

	thumb_func_start MOD83_02234238
MOD83_02234238: ; 0x02234238
	push {r3, lr}
	bl MOD83_02234574
	cmp r0, #0xc
	beq _0223427A
	bl MOD83_0223458C
	cmp r0, #0xc
	bne _02234258
	bl MOD83_02234574
	cmp r0, #7
	bne _0223427A
	bl MOD83_02234C34
	pop {r3, pc}
_02234258:
	bl MOD83_022345A4
	cmp r0, #1
	beq _02234266
	cmp r0, #2
	beq _0223426C
	b _02234272
_02234266:
	bl MOD83_022341FC
	pop {r3, pc}
_0223426C:
	bl MOD83_02234228
	pop {r3, pc}
_02234272:
	bl MOD83_0223456C
	bl MOD83_02234574
_0223427A:
	pop {r3, pc}
	thumb_func_end MOD83_02234238

	thumb_func_start MOD83_0223427C
MOD83_0223427C: ; 0x0223427C
	push {r3, lr}
	bl MOD83_02234674
	mov r0, #1
	bl MOD83_022345B0
	bl MOD83_02233F44
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_0223427C

	thumb_func_start MOD83_02234290
MOD83_02234290: ; 0x02234290
	push {r4, lr}
	bl MOD83_022345A4
	mov r4, #0
	cmp r0, #1
	bne _022342BE
	bl MOD83_02234664
	ldr r1, _022342C4 ; =0x000001C3
	ldrb r1, [r0, r1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	cmp r1, #1
	bne _022342BE
	add r2, r4, #0
_022342AE:
	ldr r1, [r0]
	cmp r1, #0
	beq _022342B6
	add r4, r4, #1
_022342B6:
	add r2, r2, #1
	add r0, #0x38
	cmp r2, #8
	blo _022342AE
_022342BE:
	add r0, r4, #0
	pop {r4, pc}
	nop
_022342C4: .word 0x000001C3
	thumb_func_end MOD83_02234290

	thumb_func_start MOD83_022342C8
MOD83_022342C8: ; 0x022342C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_022345A4
	cmp r0, #1
	bne _022342FA
	bl MOD83_02234574
	cmp r0, #7
	bne _022342FA
	bl MOD83_02234664
	ldr r1, _02234300 ; =0x000001C3
	ldrb r1, [r0, r1]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	cmp r1, #1
	bne _022342FA
	mov r1, #0x38
	mul r1, r4
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _022342FA
	mov r0, #1
	pop {r4, pc}
_022342FA:
	mov r0, #0
	pop {r4, pc}
	nop
_02234300: .word 0x000001C3
	thumb_func_end MOD83_022342C8

	thumb_func_start MOD83_02234304
MOD83_02234304: ; 0x02234304
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD83_022345A4
	cmp r0, #1
	bne _0223434E
	bl MOD83_02234574
	cmp r0, #7
	bne _0223434E
	bl MOD83_02234664
	ldr r2, _02234350 ; =0x000001C3
	ldrb r3, [r0, r2]
	lsl r1, r3, #0x18
	lsr r1, r1, #0x1c
	cmp r1, #1
	bne _0223434E
	mov r1, #0x38
	add r5, r4, #0
	mul r5, r1
	ldr r5, [r0, r5]
	cmp r5, #0
	beq _0223434E
	mov r5, #0xf
	lsl r4, r4, #0x18
	bic r3, r5
	lsr r5, r4, #0x18
	mov r4, #0xf
	and r4, r5
	orr r3, r4
	strb r3, [r0, r2]
	mov r2, #0x78
	lsl r1, r1, #3
	strh r2, [r0, r1]
	bl MOD83_02234A94
_0223434E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02234350: .word 0x000001C3
	thumb_func_end MOD83_02234304

	thumb_func_start MOD83_02234354
MOD83_02234354: ; 0x02234354
	push {r4, lr}
	bl MOD83_022345A4
	mov r4, #0
	cmp r0, #2
	bne _02234386
	bl MOD83_0223466C
	add r1, r0, #0
	add r1, #0x60
	ldrb r1, [r1]
	cmp r1, #2
	bne _02234386
	add r2, r4, #0
_02234370:
	ldr r1, [r0]
	cmp r1, #0
	beq _0223437E
	ldrb r1, [r0, #0xa]
	cmp r1, #0
	beq _0223437E
	add r4, r4, #1
_0223437E:
	add r2, r2, #1
	add r0, #0xc
	cmp r2, #8
	blo _02234370
_02234386:
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02234354

	thumb_func_start MOD83_0223438C
MOD83_0223438C: ; 0x0223438C
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x20]
	cmp r0, #0
	beq _0223439C
	mov r0, #0
	pop {r3, pc}
_0223439C:
	bl WM_GetLinkLevel
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_0223438C

	thumb_func_start MOD83_022343A4
MOD83_022343A4: ; 0x022343A4
	push {r3, lr}
	bl MOD83_022345A4
	cmp r0, #1
	beq _022343B4
	cmp r0, #2
	beq _022343BA
	b _022343C0
_022343B4:
	bl MOD83_02234290
	pop {r3, pc}
_022343BA:
	bl MOD83_02234354
	pop {r3, pc}
_022343C0:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD83_022343A4

	thumb_func_start MOD83_022343C4
MOD83_022343C4: ; 0x022343C4
	push {r3, r4, r5, lr}
	bl MOD83_02234694
	add r5, r0, #0
	bl MOD83_022346EC
	add r4, r0, #0
	bl MOD83_022345A4
	cmp r0, #1
	bne _022343F6
	mov r0, #1
	strb r0, [r5, #0x18]
	mov r1, #0
	strb r1, [r5, #0x19]
	add r4, #8
	str r4, [r5]
	str r4, [r5, #4]
	str r1, [r5, #0x10]
	str r1, [r5, #0x14]
	mov r0, #0x78
	strb r0, [r5, #0x1a]
	strb r1, [r5, #0x1b]
	mov r0, #0xfd
	strb r0, [r5, #0x1c]
_022343F6:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_022343C4

	thumb_func_start MOD83_022343F8
MOD83_022343F8: ; 0x022343F8
	push {r4, lr}
	bl MOD83_02234694
	add r4, r0, #0
	bl MOD83_022346EC
	mov r1, #1
	strb r1, [r4, #0x18]
	mov r1, #0
	strb r1, [r4, #0x19]
	add r0, #8
	str r0, [r4]
	str r0, [r4, #4]
	mov r0, #0x30
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	mov r0, #0x78
	strb r0, [r4, #0x1a]
	strb r1, [r4, #0x1b]
	mov r0, #0xfe
	strb r0, [r4, #0x1c]
	pop {r4, pc}
	thumb_func_end MOD83_022343F8

	thumb_func_start MOD83_02234424
MOD83_02234424: ; 0x02234424
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	bl MOD83_02234694
	cmp r4, #0xf0
	bgt _0223444E
	mov r1, #2
	strb r1, [r0, #0x18]
	mov r1, #3
	strb r1, [r0, #0x19]
	str r5, [r0]
	str r5, [r0, #4]
	str r6, [r0, #0x10]
	mov r2, #0
	str r2, [r0, #0x14]
	mov r1, #0x78
	strb r1, [r0, #0x1a]
	strb r2, [r0, #0x1b]
	strb r4, [r0, #0x1c]
_0223444E:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD83_02234424

	thumb_func_start MOD83_02234450
MOD83_02234450: ; 0x02234450
	push {r3, lr}
	bl MOD83_022345A4
	cmp r0, #1
	beq _0223445E
	cmp r0, #2
	bne _02234478
_0223445E:
	bl MOD83_02234574
	cmp r0, #0xa
	beq _0223446A
	cmp r0, #0xb
	bne _02234478
_0223446A:
	bl MOD83_02234694
	ldrb r0, [r0, #0x19]
	cmp r0, #2
	bne _02234478
	mov r0, #1
	pop {r3, pc}
_02234478:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD83_02234450

	thumb_func_start MOD83_0223447C
MOD83_0223447C: ; 0x0223447C
	push {r3, lr}
	bl MOD83_022345A4
	cmp r0, #1
	beq _0223448A
	cmp r0, #2
	bne _022344A4
_0223448A:
	bl MOD83_02234574
	cmp r0, #0xa
	beq _02234496
	cmp r0, #0xb
	bne _022344A4
_02234496:
	bl MOD83_02234694
	ldrb r0, [r0, #0x19]
	cmp r0, #2
	bne _022344A4
	mov r0, #1
	pop {r3, pc}
_022344A4:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD83_0223447C

	thumb_func_start MOD83_022344A8
MOD83_022344A8: ; 0x022344A8
	push {r3, lr}
	bl MOD83_022345A4
	cmp r0, #1
	beq _022344B6
	cmp r0, #2
	bne _022344E0
_022344B6:
	bl MOD83_02234574
	cmp r0, #0xa
	beq _022344C2
	cmp r0, #0xb
	bne _022344E0
_022344C2:
	bl MOD83_02234694
	ldrb r1, [r0, #0x19]
	cmp r1, #0
	bne _022344E0
	ldr r1, [r0, #0xc]
	ldr r1, [r1, #8]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x18
	bne _022344E0
	ldrb r0, [r0, #0x1b]
	cmp r0, #4
	bhs _022344E0
	mov r0, #1
	pop {r3, pc}
_022344E0:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD83_022344A8

	thumb_func_start MOD83_022344E4
MOD83_022344E4: ; 0x022344E4
	push {r3, lr}
	bl MOD83_022345A4
	cmp r0, #2
	bne _02234510
	bl MOD83_0223466C
	mov r2, #0
_022344F4:
	ldr r1, [r0]
	cmp r1, #0
	beq _02234504
	ldrb r1, [r0, #0xa]
	cmp r1, #0
	beq _02234504
	mov r0, #1
	pop {r3, pc}
_02234504:
	add r2, r2, #1
	add r0, #0xc
	cmp r2, #8
	blt _022344F4
	mov r0, #0
	pop {r3, pc}
_02234510:
	bl MOD83_02234628
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022344E4

	thumb_func_start MOD83_02234518
MOD83_02234518: ; 0x02234518
	push {r4, lr}
	mov r0, #0xc
	bl MOD83_02234598
	bl MOD83_02234574
	cmp r0, #0
	beq _02234532
	cmp r0, #1
	beq _02234532
	cmp r0, #9
	beq _0223453E
	pop {r4, pc}
_02234532:
	bl WM_Finish
	mov r0, #1
	bl MOD83_0223464C
	pop {r4, pc}
_0223453E:
	bl MOD83_02234628
	cmp r0, #0
	bne _02234554
	bl MOD83_0223456C
	add r4, r0, #0
	bl MOD83_02234C34
	mov r0, #1
	str r0, [r4, #0x1c]
_02234554:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02234518

	thumb_func_start MOD83_02234558
MOD83_02234558: ; 0x02234558
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x20]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234558

	thumb_func_start MOD83_02234564
MOD83_02234564: ; 0x02234564
	ldr r0, _02234568 ; =MOD83_0223B240
	bx lr
	.align 2, 0
_02234568: .word MOD83_0223B240
	thumb_func_end MOD83_02234564

	thumb_func_start MOD83_0223456C
MOD83_0223456C: ; 0x0223456C
	ldr r0, _02234570 ; =MOD83_0223B8A0
	bx lr
	.align 2, 0
_02234570: .word MOD83_0223B8A0
	thumb_func_end MOD83_0223456C

	thumb_func_start MOD83_02234574
MOD83_02234574: ; 0x02234574
	push {r3, lr}
	bl MOD83_0223456C
	ldrb r0, [r0]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234574

	thumb_func_start MOD83_02234580
MOD83_02234580: ; 0x02234580
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	strb r4, [r0]
	pop {r4, pc}
	thumb_func_end MOD83_02234580

	thumb_func_start MOD83_0223458C
MOD83_0223458C: ; 0x0223458C
	push {r3, lr}
	bl MOD83_0223456C
	ldrb r0, [r0, #1]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_0223458C

	thumb_func_start MOD83_02234598
MOD83_02234598: ; 0x02234598
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	strb r4, [r0, #1]
	pop {r4, pc}
	thumb_func_end MOD83_02234598

	thumb_func_start MOD83_022345A4
MOD83_022345A4: ; 0x022345A4
	push {r3, lr}
	bl MOD83_0223456C
	ldrb r0, [r0, #2]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022345A4

	thumb_func_start MOD83_022345B0
MOD83_022345B0: ; 0x022345B0
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	strb r4, [r0, #2]
	pop {r4, pc}
	thumb_func_end MOD83_022345B0

	thumb_func_start MOD83_022345BC
MOD83_022345BC: ; 0x022345BC
	push {r3, lr}
	bl MOD83_0223456C
	ldrb r0, [r0, #3]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022345BC

	thumb_func_start MOD83_022345C8
MOD83_022345C8: ; 0x022345C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_02234564
	strh r4, [r0, #0x32]
	pop {r4, pc}
	thumb_func_end MOD83_022345C8

	thumb_func_start MOD83_022345D4
MOD83_022345D4: ; 0x022345D4
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x24]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022345D4

	thumb_func_start MOD83_022345E0
MOD83_022345E0: ; 0x022345E0
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x2c]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022345E0

	thumb_func_start MOD83_022345EC
MOD83_022345EC: ; 0x022345EC
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x30]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022345EC

	thumb_func_start MOD83_022345F8
MOD83_022345F8: ; 0x022345F8
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x38]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022345F8

	thumb_func_start MOD83_02234604
MOD83_02234604: ; 0x02234604
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x3c]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234604

	thumb_func_start MOD83_02234610
MOD83_02234610: ; 0x02234610
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x28]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234610

	thumb_func_start MOD83_0223461C
MOD83_0223461C: ; 0x0223461C
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	strh r4, [r0, #0xc]
	pop {r4, pc}
	thumb_func_end MOD83_0223461C

	thumb_func_start MOD83_02234628
MOD83_02234628: ; 0x02234628
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x14]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234628

	thumb_func_start MOD83_02234634
MOD83_02234634: ; 0x02234634
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	str r4, [r0, #0x14]
	pop {r4, pc}
	thumb_func_end MOD83_02234634

	thumb_func_start MOD83_02234640
MOD83_02234640: ; 0x02234640
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	str r4, [r0, #0x18]
	pop {r4, pc}
	thumb_func_end MOD83_02234640

	thumb_func_start MOD83_0223464C
MOD83_0223464C: ; 0x0223464C
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_0223456C
	str r4, [r0, #0x20]
	pop {r4, pc}
	thumb_func_end MOD83_0223464C

	thumb_func_start MOD83_02234658
MOD83_02234658: ; 0x02234658
	push {r3, lr}
	bl MOD83_0223456C
	add r0, #0x90
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234658

	thumb_func_start MOD83_02234664
MOD83_02234664: ; 0x02234664
	ldr r3, _02234668 ; =MOD83_02234658
	bx r3
	.align 2, 0
_02234668: .word MOD83_02234658
	thumb_func_end MOD83_02234664

	thumb_func_start MOD83_0223466C
MOD83_0223466C: ; 0x0223466C
	ldr r3, _02234670 ; =MOD83_02234658
	bx r3
	.align 2, 0
_02234670: .word MOD83_02234658
	thumb_func_end MOD83_0223466C

	thumb_func_start MOD83_02234674
MOD83_02234674: ; 0x02234674
	push {r4, lr}
	bl MOD83_02234664
	mov r2, #0x71
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	mov r1, #0x46
	lsl r1, r1, #2
	add r0, r1, #0
	add r0, #0xa8
	strh r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02234674

	thumb_func_start MOD83_02234694
MOD83_02234694: ; 0x02234694
	push {r3, lr}
	bl MOD83_0223456C
	mov r1, #0x95
	lsl r1, r1, #2
	add r0, r0, r1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_02234694

	thumb_func_start MOD83_022346A4
MOD83_022346A4: ; 0x022346A4
	push {r3, lr}
	bl MOD83_02234694
	mov r1, #0
	strb r1, [r0, #0x18]
	pop {r3, pc}
	thumb_func_end MOD83_022346A4

	thumb_func_start MOD83_022346B0
MOD83_022346B0: ; 0x022346B0
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #4]
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022346B0

	thumb_func_start MOD83_022346BC
MOD83_022346BC: ; 0x022346BC
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x40]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022346BC

	thumb_func_start MOD83_022346CC
MOD83_022346CC: ; 0x022346CC
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x40]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1c
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022346CC

	thumb_func_start MOD83_022346DC
MOD83_022346DC: ; 0x022346DC
	push {r3, lr}
	bl MOD83_0223456C
	ldr r0, [r0, #0x44]
	lsr r0, r0, #0x10
	pop {r3, pc}
	thumb_func_end MOD83_022346DC

	thumb_func_start MOD83_022346E8
MOD83_022346E8: ; 0x022346E8
	mov r0, #0x38
	bx lr
	thumb_func_end MOD83_022346E8

	thumb_func_start MOD83_022346EC
MOD83_022346EC: ; 0x022346EC
	push {r3, lr}
	bl MOD83_0223456C
	add r0, #0x40
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022346EC

	thumb_func_start MOD83_022346F8
MOD83_022346F8: ; 0x022346F8
	push {r3, lr}
	bl MOD83_0223456C
	add r0, #0x78
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022346F8

	thumb_func_start MOD83_02234704
MOD83_02234704: ; 0x02234704
	push {r3}
	sub sp, #4
	mov r2, #0
	str r2, [sp]
	add r3, sp, #0
_0223470E:
	add r1, r0, r2
	ldrb r1, [r1, #2]
	add r2, r2, #1
	strb r1, [r3]
	add r3, r3, #1
	cmp r2, #4
	blo _0223470E
	ldr r0, [sp]
	add sp, #4
	pop {r3}
	bx lr
	thumb_func_end MOD83_02234704

	thumb_func_start MOD83_02234724
MOD83_02234724: ; 0x02234724
	push {r3}
	sub sp, #4
	mov r2, #0
	add r1, sp, #0
	strh r2, [r1]
	add r3, sp, #0
_02234730:
	ldrb r1, [r0, r2]
	add r2, r2, #1
	strb r1, [r3]
	add r3, r3, #1
	cmp r2, #2
	blo _02234730
	add r1, sp, #0
	mov r0, #0
	ldrsh r0, [r1, r0]
	add sp, #4
	pop {r3}
	bx lr
	thumb_func_end MOD83_02234724

	thumb_func_start MOD83_02234748
MOD83_02234748: ; 0x02234748
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r1, _0223476C ; =0x00002710
	add r6, r0, #0
	add r4, r2, #0
	bl _u32_div_f
	str r1, [r5]
	ldr r1, _0223476C ; =0x00002710
	add r0, r6, #0
	bl _u32_div_f
	ldr r1, _0223476C ; =0x00002710
	bl _u32_div_f
	str r1, [r4]
	pop {r4, r5, r6, pc}
	nop
_0223476C: .word 0x00002710
	thumb_func_end MOD83_02234748

	thumb_func_start MOD83_02234770
MOD83_02234770: ; 0x02234770
	mov r0, #0x10
	bx lr
	thumb_func_end MOD83_02234770

	thumb_func_start MOD83_02234774
MOD83_02234774: ; 0x02234774
	push {r4, lr}
	ldr r0, _02234788 ; =0x04000006
	ldrh r4, [r0]
	bl OS_GetTick
	add r1, r0, r4
	mov r0, #1
	bic r1, r0
	add r0, r1, #1
	pop {r4, pc}
	.align 2, 0
_02234788: .word 0x04000006
	thumb_func_end MOD83_02234774

	thumb_func_start MOD83_0223478C
MOD83_0223478C: ; 0x0223478C
	push {r4, r5, r6, r7}
	add r3, r0, #0
	mov r0, #0
	lsr r1, r1, #2
	beq _022347C2
	ldr r4, _022347C8 ; =0x00269EC3
_02234798:
	ldr r5, _022347CC ; =0x5D588B65
	ldr r6, _022347CC ; =0x5D588B65
	mul r5, r3
	ldr r3, _022347C8 ; =0x00269EC3
	add r0, r0, #1
	add r3, r5, r3
	lsr r5, r3, #0x10
	mul r6, r3
	add r3, r6, r4
	lsl r5, r5, #0x10
	lsr r7, r3, #0x10
	lsr r5, r5, #0x10
	lsl r7, r7, #0x10
	ldr r6, [r2]
	lsl r5, r5, #0x10
	lsr r7, r7, #0x10
	orr r5, r7
	eor r5, r6
	stmia r2!, {r5}
	cmp r0, r1
	blo _02234798
_022347C2:
	add r0, r3, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_022347C8: .word 0x00269EC3
_022347CC: .word 0x5D588B65
	thumb_func_end MOD83_0223478C

	thumb_func_start MOD83_022347D0
MOD83_022347D0: ; 0x022347D0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	str r3, [sp]
	bl MOD83_022346EC
	add r4, r0, #0
	ldr r0, [r5]
	mov r1, #0xff
	bic r0, r1
	ldr r1, [r4]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	orr r1, r0
	ldr r0, _022348F4 ; =0xFFFFF0FF
	str r1, [r5]
	and r0, r1
	ldr r1, [r4]
	lsl r1, r1, #0x14
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x14
	orr r1, r0
	ldr r0, _022348F8 ; =0xFFFF0FFF
	str r1, [r5]
	and r0, r1
	ldr r1, [r4]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x1c
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x10
	orr r0, r1
	str r0, [r5]
	bl MOD83_02234774
	ldr r1, [r5]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	lsl r0, r0, #0x10
	orr r0, r1
	str r0, [r5]
	ldr r2, [r4, #4]
	ldr r1, [r5, #4]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	mov r0, #0xff
	lsl r2, r2, #0x18
	bic r1, r0
	lsr r2, r2, #0x18
	orr r2, r1
	ldr r1, _022348F4 ; =0xFFFFF0FF
	str r2, [r5, #4]
	and r1, r2
	ldr r2, [r4, #4]
	lsl r2, r2, #0x14
	lsr r2, r2, #0x1c
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x14
	orr r2, r1
	ldr r1, _022348F8 ; =0xFFFF0FFF
	str r2, [r5, #4]
	and r1, r2
	ldr r2, [r4, #4]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x1c
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x10
	orr r1, r2
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	str r1, [r5, #4]
	ldr r1, [r5, #8]
	bic r1, r0
	ldr r0, [sp, #0x18]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	orr r1, r0
	ldr r0, _022348FC ; =0xFFFF00FF
	and r0, r1
	ldr r1, [sp]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x10
	orr r0, r1
	str r0, [r5, #8]
	mov r0, #0
	add r1, r7, #0
	add r2, r6, #0
	bl SVC_GetCRC16
	ldr r1, [r5, #8]
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	orr r0, r1
	str r0, [r5, #8]
	bl MOD83_02234770
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x18
	ldr r1, [r5, #0xc]
	mov r2, #0xff
	bic r1, r2
	lsr r0, r0, #0x18
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsl r0, r6, #8
	orr r0, r1
	str r0, [r5, #0xc]
	cmp r6, #0
	beq _022348CE
	ldr r1, [r5, #0xc]
	add r0, r7, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r1, r5, r1
	add r2, r6, #0
	bl MI_CpuCopy8
_022348CE:
	add r0, r5, #0
	bl MOD83_0223496C
	ldr r0, [r4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1c
	cmp r0, #1
	bne _022348F2
	ldr r1, [r5, #0xc]
	ldr r0, [r5]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r1, r6, r1
	lsr r0, r0, #0x10
	sub r1, r1, #4
	add r2, r5, #4
	bl MOD83_0223478C
_022348F2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022348F4: .word 0xFFFFF0FF
_022348F8: .word 0xFFFF0FFF
_022348FC: .word 0xFFFF00FF
	thumb_func_end MOD83_022347D0

	thumb_func_start MOD83_02234900
MOD83_02234900: ; 0x02234900
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_022346EC
	ldr r0, [r4]
	lsl r1, r0, #0x10
	lsr r1, r1, #0x1c
	cmp r1, #1
	bne _02234930
	lsr r0, r0, #0x10
	mov r1, #0xc
	add r2, r4, #4
	bl MOD83_0223478C
	ldr r1, [r4, #0xc]
	add r4, #0x10
	lsl r2, r1, #0x18
	lsr r2, r2, #0x18
	lsr r1, r1, #8
	add r1, r2, r1
	sub r1, #0x10
	add r2, r4, #0
	bl MOD83_0223478C
_02234930:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02234900

	thumb_func_start MOD83_02234934
MOD83_02234934: ; 0x02234934
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4, #0xc]
	mov r0, #0
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	add r1, r4, r1
	lsr r2, r2, #8
	bl SVC_GetCRC16
	ldr r1, [r4, #8]
	lsr r1, r1, #0x10
	cmp r1, r0
	bne _02234954
	mov r0, #1
	pop {r4, pc}
_02234954:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD83_02234934

	thumb_func_start MOD83_02234958
MOD83_02234958: ; 0x02234958
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02234958

	thumb_func_start MOD83_0223495C
MOD83_0223495C: ; 0x0223495C
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0223495C

	thumb_func_start MOD83_02234960
MOD83_02234960: ; 0x02234960
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02234960

	thumb_func_start MOD83_02234964
MOD83_02234964: ; 0x02234964
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02234964

	thumb_func_start MOD83_02234968
MOD83_02234968: ; 0x02234968
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02234968

	thumb_func_start MOD83_0223496C
MOD83_0223496C: ; 0x0223496C
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0223496C

	thumb_func_start MOD83_02234970
MOD83_02234970: ; 0x02234970
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	bl MOD83_022345BC
	lsl r0, r0, #0x10
	lsl r3, r5, #0x10
	lsr r0, r0, #0x10
	str r4, [sp]
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldr r0, _022349AC ; =MOD83_02233528
	mov r1, #0
	add r2, r6, #0
	lsr r3, r3, #0x10
	bl WM_SetMPDataToPortEx
	cmp r0, #2
	beq _022349A6
	bl MOD83_02234958
	add sp, #0xc
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_022349A6:
	mov r0, #1
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022349AC: .word MOD83_02233528
	thumb_func_end MOD83_02234970

	thumb_func_start MOD83_022349B0
MOD83_022349B0: ; 0x022349B0
	push {r3, lr}
	ldr r0, _022349C8 ; =MOD83_02233540
	bl WM_Enable
	cmp r0, #2
	beq _022349C4
	bl MOD83_02234958
	mov r0, #0
	pop {r3, pc}
_022349C4:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_022349C8: .word MOD83_02233540
	thumb_func_end MOD83_022349B0

	thumb_func_start MOD83_022349CC
MOD83_022349CC: ; 0x022349CC
	push {r3, lr}
	ldr r0, _022349E8 ; =MOD83_02233580
	bl WM_Disable
	cmp r0, #2
	beq _022349E4
	bl MOD83_02234958
	bl OS_Terminate
	mov r0, #0
	pop {r3, pc}
_022349E4:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_022349E8: .word MOD83_02233580
	thumb_func_end MOD83_022349CC

	thumb_func_start MOD83_022349EC
MOD83_022349EC: ; 0x022349EC
	push {r3, lr}
	add r3, r0, #0
	mov r0, #0x1e
	str r0, [sp]
	lsl r3, r3, #0x10
	ldr r0, _02234A14 ; =MOD83_022335B8
	mov r1, #3
	mov r2, #0x11
	lsr r3, r3, #0x10
	bl WM_MeasureChannel
	cmp r0, #2
	beq _02234A0E
	bl MOD83_02234958
	mov r0, #0
	pop {r3, pc}
_02234A0E:
	mov r0, #1
	pop {r3, pc}
	nop
_02234A14: .word MOD83_022335B8
	thumb_func_end MOD83_022349EC

	thumb_func_start MOD83_02234A18
MOD83_02234A18: ; 0x02234A18
	push {r3, r4, r5, lr}
	bl MOD83_02234564
	add r5, r0, #0
	bl MOD83_022346EC
	add r4, r0, #0
	bl MOD83_0223466C
	add r0, #0x64
	ldrb r0, [r0]
	strh r0, [r5, #0x32]
	str r4, [r5]
	bl MOD83_022346E8
	strh r0, [r5, #4]
	ldr r0, _02234A50 ; =MOD83_02233620
	add r1, r5, #0
	bl WM_SetParentParameter
	cmp r0, #2
	beq _02234A4C
	bl MOD83_02234958
	mov r0, #0
	pop {r3, r4, r5, pc}
_02234A4C:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_02234A50: .word MOD83_02233620
	thumb_func_end MOD83_02234A18

	thumb_func_start MOD83_02234A54
MOD83_02234A54: ; 0x02234A54
	push {r3, lr}
	ldr r0, _02234A6C ; =MOD83_02233648
	bl WM_StartParent
	cmp r0, #2
	beq _02234A68
	bl MOD83_02234958
	mov r0, #0
	pop {r3, pc}
_02234A68:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02234A6C: .word MOD83_02233648
	thumb_func_end MOD83_02234A54

	thumb_func_start MOD83_02234A70
MOD83_02234A70: ; 0x02234A70
	push {r3, lr}
	bl MOD83_022345D4
	add r1, r0, #0
	ldr r0, _02234A90 ; =MOD83_02233914
	bl WM_StartScan
	cmp r0, #2
	beq _02234A8A
	bl MOD83_02234958
	mov r0, #0
	pop {r3, pc}
_02234A8A:
	mov r0, #1
	pop {r3, pc}
	nop
_02234A90: .word MOD83_02233914
	thumb_func_end MOD83_02234A70

	thumb_func_start MOD83_02234A94
MOD83_02234A94: ; 0x02234A94
	push {r3, r4, r5, lr}
	bl MOD83_022345D4
	add r4, r0, #0
	bl MOD83_02234664
	ldr r2, _02234B24 ; =0x000001C3
	mov r3, #0x38
	ldrb r1, [r0, r2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r5, r1, #0
	mul r5, r3
	add r1, r0, r5
	add r1, #0x34
	ldrb r1, [r1]
	strb r1, [r4, #8]
	ldrb r1, [r0, r2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r5, r1, #0
	mul r5, r3
	add r1, r0, r5
	add r1, #0x35
	ldrb r1, [r1]
	strb r1, [r4, #9]
	ldrb r1, [r0, r2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r5, r1, #0
	mul r5, r3
	ldrb r1, [r0, r5]
	strb r1, [r4, #0xa]
	ldrb r1, [r0, r2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r5, r1, #0
	mul r5, r3
	add r1, r0, r5
	ldrb r1, [r1, #1]
	strb r1, [r4, #0xb]
	ldrb r1, [r0, r2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r5, r1, #0
	mul r5, r3
	add r1, r0, r5
	ldrb r1, [r1, #2]
	strb r1, [r4, #0xc]
	ldrb r1, [r0, r2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r2, r1, #0
	mul r2, r3
	add r0, r0, r2
	ldrb r0, [r0, #3]
	strb r0, [r4, #0xd]
	bl MOD83_022345D4
	add r1, r0, #0
	ldr r0, _02234B28 ; =MOD83_02233A30
	bl WM_StartScan
	cmp r0, #2
	beq _02234B1E
	bl MOD83_02234958
	mov r0, #0
	pop {r3, r4, r5, pc}
_02234B1E:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_02234B24: .word 0x000001C3
_02234B28: .word MOD83_02233A30
	thumb_func_end MOD83_02234A94

	thumb_func_start MOD83_02234B2C
MOD83_02234B2C: ; 0x02234B2C
	push {r3, lr}
	ldr r0, _02234B44 ; =MOD83_02233AA0
	bl WM_EndScan
	cmp r0, #2
	beq _02234B40
	bl MOD83_02234958
	mov r0, #0
	pop {r3, pc}
_02234B40:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02234B44: .word MOD83_02233AA0
	thumb_func_end MOD83_02234B2C

	thumb_func_start MOD83_02234B48
MOD83_02234B48: ; 0x02234B48
	push {r3, r4, lr}
	sub sp, #4
	bl MOD83_022346F8
	add r4, r0, #0
	bl MOD83_02234610
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02234B7C ; =MOD83_02233AF4
	add r2, r4, #0
	mov r3, #1
	bl WM_StartConnectEx
	cmp r0, #2
	beq _02234B74
	bl MOD83_02234958
	add sp, #4
	mov r0, #0
	pop {r3, r4, pc}
_02234B74:
	mov r0, #1
	add sp, #4
	pop {r3, r4, pc}
	nop
_02234B7C: .word MOD83_02233AF4
	thumb_func_end MOD83_02234B48

	thumb_func_start MOD83_02234B80
MOD83_02234B80: ; 0x02234B80
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r1, _02234BF0 ; =MOD83_02233DF0
	mov r0, #4
	mov r2, #0
	bl WM_SetPortCallback
	cmp r0, #0
	beq _02234B9C
	bl MOD83_02234958
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02234B9C:
	bl MOD83_02234564
	ldrh r0, [r0, #0x16]
	cmp r0, #0
	bne _02234BAA
	mov r5, #1
	b _02234BAC
_02234BAA:
	mov r5, #0
_02234BAC:
	bl MOD83_02234604
	add r6, r0, #0
	bl MOD83_022345EC
	add r4, r0, #0
	bl MOD83_022345F8
	add r7, r0, #0
	bl MOD83_022345E0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	lsl r2, r4, #0x10
	ldr r0, _02234BF4 ; =MOD83_02233BD8
	add r1, r6, #0
	lsr r2, r2, #0x10
	add r3, r7, #0
	bl WM_StartMP
	cmp r0, #2
	beq _02234BEA
	bl MOD83_02234958
	add sp, #8
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02234BEA:
	mov r0, #1
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02234BF0: .word MOD83_02233DF0
_02234BF4: .word MOD83_02233BD8
	thumb_func_end MOD83_02234B80

	thumb_func_start MOD83_02234BF8
MOD83_02234BF8: ; 0x02234BF8
	push {r3, lr}
	ldr r0, _02234C10 ; =MOD83_02233E74
	bl WM_PowerOn
	cmp r0, #2
	beq _02234C0C
	bl MOD83_02234958
	mov r0, #0
	pop {r3, pc}
_02234C0C:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02234C10: .word MOD83_02233E74
	thumb_func_end MOD83_02234BF8

	thumb_func_start MOD83_02234C14
MOD83_02234C14: ; 0x02234C14
	push {r3, lr}
	ldr r0, _02234C30 ; =MOD83_02233E98
	bl WM_PowerOff
	cmp r0, #2
	beq _02234C2C
	bl MOD83_02234958
	bl OS_Terminate
	mov r0, #0
	pop {r3, pc}
_02234C2C:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02234C30: .word MOD83_02233E98
	thumb_func_end MOD83_02234C14

	thumb_func_start MOD83_02234C34
MOD83_02234C34: ; 0x02234C34
	push {r3, lr}
	ldr r0, _02234C50 ; =MOD83_02233EBC
	bl WM_Reset
	cmp r0, #2
	beq _02234C4C
	bl MOD83_02234958
	bl OS_Terminate
	mov r0, #0
	pop {r3, pc}
_02234C4C:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02234C50: .word MOD83_02233EBC
	thumb_func_end MOD83_02234C34

	thumb_func_start MOD83_02234C54
MOD83_02234C54: ; 0x02234C54
	push {r3, lr}
	ldr r0, _02234C70 ; =MOD83_02233F00
	bl WM_End
	cmp r0, #2
	beq _02234C6C
	bl MOD83_02234958
	bl OS_Terminate
	mov r0, #0
	pop {r3, pc}
_02234C6C:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02234C70: .word MOD83_02233F00
	thumb_func_end MOD83_02234C54

	thumb_func_start MOD83_RS_SpeciesIsInvalid
MOD83_RS_SpeciesIsInvalid: ; 0x02234C74
	cmp r0, #0 ; RS_SPECIES_NONE
	bgt _02234C7C
	mov r0, #1
	bx lr
_02234C7C:
	cmp r0, #0xfb ; RS_SPECIES_CELEBI
	bgt _02234C84
	mov r0, #0
	bx lr
_02234C84:
	ldr r1, _02234C9C ; =0x00000115 RS_SPECIES_TREECKO
	cmp r0, r1
	bge _02234C8E
	mov r0, #1
	bx lr
_02234C8E:
	add r1, #0x86 ; RS_SPECIES_CHIMECHO
	cmp r0, r1
	ble _02234C98
	mov r0, #1
	bx lr
_02234C98:
	mov r0, #0
	bx lr
	.align 2, 0
_02234C9C: .word 0x00000115
	thumb_func_end MOD83_RS_SpeciesIsInvalid

	thumb_func_start MOD83_02234CA0
MOD83_02234CA0: ; 0x02234CA0
	push {r4, lr}
	add r4, r0, #0
	bl MOD83_02236E9C
	cmp r0, #4
	bhi _02234CE0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02234CB8: ; jump table
	.short _02234CC2 - _02234CB8 - 2 ; case 0
	.short _02234CC8 - _02234CB8 - 2 ; case 1
	.short _02234CCE - _02234CB8 - 2 ; case 2
	.short _02234CD4 - _02234CB8 - 2 ; case 3
	.short _02234CDA - _02234CB8 - 2 ; case 4
_02234CC2:
	mov r0, #2
	str r0, [r4]
	pop {r4, pc}
_02234CC8:
	mov r0, #1
	str r0, [r4]
	pop {r4, pc}
_02234CCE:
	mov r0, #5
	str r0, [r4]
	pop {r4, pc}
_02234CD4:
	mov r0, #4
	str r0, [r4]
	pop {r4, pc}
_02234CDA:
	mov r0, #3
	str r0, [r4]
	pop {r4, pc}
_02234CE0:
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	pop {r4, pc}
	thumb_func_end MOD83_02234CA0

	thumb_func_start MOD83_02234CE8
MOD83_02234CE8: ; 0x02234CE8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r1, _02234E3C ; =0x0000E890
	add r5, r0, #0
	add r4, r5, r1
	ldr r1, [r4]
	cmp r1, #9
	bls _02234CFA
	b _02234E34
_02234CFA:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234D06: ; jump table
	.short _02234D1A - _02234D06 - 2 ; case 0
	.short _02234D3A - _02234D06 - 2 ; case 1
	.short _02234D52 - _02234D06 - 2 ; case 2
	.short _02234D62 - _02234D06 - 2 ; case 3
	.short _02234D72 - _02234D06 - 2 ; case 4
	.short _02234D8E - _02234D06 - 2 ; case 5
	.short _02234DA2 - _02234D06 - 2 ; case 6
	.short _02234DBE - _02234D06 - 2 ; case 7
	.short _02234DEA - _02234D06 - 2 ; case 8
	.short _02234E10 - _02234D06 - 2 ; case 9
_02234D1A:
	bl MOD83_02234E6C
	ldr r0, [r5, #0x10]
	bl FUN_02022528
	add r5, r0, #0
	bl MOD83_02237448
	add r1, r0, #0
	add r0, r5, #0
	bl FUN_0202BF90
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234D3A:
	bl OS_GetTick
	mov r2, #0x78
	mov r3, #0
	bl _ull_mod
	add r0, r0, #1
	str r0, [r4, #4]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234D52:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	bne _02234E34
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234D62:
	ldr r0, [r5, #0x10]
	mov r1, #2
	bl FUN_02022840
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234D72:
	ldr r0, [r5, #0x10]
	bl FUN_02022854
	cmp r0, #3
	bne _02234D82
	add sp, #0x10
	mov r0, #0xc
	pop {r3, r4, r5, pc}
_02234D82:
	cmp r0, #1
	bne _02234E34
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234D8E:
	mov r0, #0
	add r1, r0, #0
	add r2, sp, #0
	mov r3, #0x10
	bl CTRDG_ReadAgbFlash
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234DA2:
	bl MOD83_0223736C
	cmp r0, #0
	bne _02234DB6
	mov r0, #1
	bl FUN_02016454
	add sp, #0x10
	mov r0, #0xc
	pop {r3, r4, r5, pc}
_02234DB6:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234DBE:
	bl MOD83_022373F4
	cmp r0, #9
	beq _02234E34
	bl MOD83_022373F4
	cmp r0, #0xb
	bne _02234DD6
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234DD6:
	bl MOD83_022373B4
	cmp r0, #8
	bne _02234E34
	mov r0, #1
	bl FUN_02016454
	add sp, #0x10
	mov r0, #0xc
	pop {r3, r4, r5, pc}
_02234DEA:
	ldr r0, [r5, #0x10]
	bl FUN_02022854
	cmp r0, #3
	bne _02234DFA
	add sp, #0x10
	mov r0, #0xc
	pop {r3, r4, r5, pc}
_02234DFA:
	cmp r0, #2
	bne _02234DEA
	bl MOD83_022373B4
	mov r0, #1
	bl FUN_02016444
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _02234E34
_02234E10:
	bl MOD83_022373B4
	cmp r0, #8
	bne _02234E24
	mov r0, #1
	bl FUN_02016454
	add sp, #0x10
	mov r0, #0xc
	pop {r3, r4, r5, pc}
_02234E24:
	cmp r0, #0
	bne _02234E34
	mov r0, #1
	bl FUN_02016454
	add sp, #0x10
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_02234E34:
	mov r0, #0xa
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_02234E3C: .word 0x0000E890
	thumb_func_end MOD83_02234CE8

	thumb_func_start MOD83_02234E40
MOD83_02234E40: ; 0x02234E40
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	bl FUN_02022528
	add r4, r0, #0
	bl MOD83_02237448
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_0202BF90
	mov r0, #4
	bl SetSoftResetDisableMask
	ldr r0, [r5, #0x10]
	bl FUN_02022720
	mov r0, #4
	bl ClearSoftResetDisableMask
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_02234E40

	thumb_func_start MOD83_02234E6C
MOD83_02234E6C: ; 0x02234E6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xf4
	add r7, r0, #0
	ldr r0, [r7, #0x10]
	bl FUN_02022528
	str r0, [sp]
	add r0, sp, #8
	bl FUN_020690E4
	add r6, r0, #0
	mov r4, #0
	add r5, r7, #0
_02234E86:
	ldr r0, _02234F04 ; =0x0000E880
	mov r1, #0x3d
	lsl r1, r1, #4
	ldr r0, [r7, r0]
	ldr r2, [r5, r1]
	mov r1, #0x96
	lsl r1, r1, #4
	add r0, r0, #4
	mul r1, r2
	add r0, r0, r1
	mov r1, #0xf3
	lsl r1, r1, #2
	ldr r2, [r5, r1]
	mov r1, #0x50
	mul r1, r2
	add r0, r0, r1
	add r1, r6, #0
	bl MigrateBoxMon
	ldr r0, [sp]
	add r1, r6, #0
	add r2, r4, #0
	bl FUN_0202BF7C
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #6
	blt _02234E86
	mov r5, #0
	add r0, sp, #4
	strh r5, [r0]
	add r4, r7, #0
	sub r6, r5, #1
_02234EC8:
	mov r0, #0xf3
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	add r0, r0, #4
	ldr r1, [r4, r0]
	cmp r2, r6
	beq _02234EF6
	cmp r1, #0xe
	beq _02234EF6
	ldr r0, _02234F04 ; =0x0000E880
	mov r3, #0x96
	ldr r0, [r7, r0]
	lsl r3, r3, #4
	mul r3, r1
	add r0, r0, #4
	mov r1, #0x50
	mul r1, r2
	add r0, r0, r3
	add r0, r0, r1
	mov r1, #0xb
	add r2, sp, #4
	bl MOD83_02237D90
_02234EF6:
	add r5, r5, #1
	add r4, #0xc
	cmp r5, #6
	blt _02234EC8
	add sp, #0xf4
	pop {r4, r5, r6, r7, pc}
	nop
_02234F04: .word 0x0000E880
	thumb_func_end MOD83_02234E6C

	thumb_func_start MOD83_02234F08
MOD83_02234F08: ; 0x02234F08
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	tst r2, r0
	beq _02234F26
	mov r2, #0
	bl FUN_02002E14
	ldr r1, [r4, #0x10]
	lsl r1, r1, #3
	sub r1, r1, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #1
	pop {r4, pc}
_02234F26:
	ldr r0, [r4, #0x18]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02234F08

	thumb_func_start MOD83_02234F2C
MOD83_02234F2C: ; 0x02234F2C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r1, #0
	ldr r6, [r5, #0x44]
	add r4, r2, #0
	cmp r6, #0
	bne _02234F3C
	mov r6, #0xff
_02234F3C:
	ldr r1, [r5]
	ldr r2, [r1]
	cmp r2, #0
	bne _02234F7A
	ldr r2, [r5, #0xc]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp]
	ldr r2, [r5, #0x10]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #4]
	ldr r2, [r5, #0x14]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #8]
	mov r2, #0xf
	str r2, [sp, #0xc]
	ldr r2, [r5, #0x20]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	str r2, [sp, #0x10]
	ldr r2, [r5, #0x24]
	ldr r3, [r5, #8]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x20]
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl AddWindowParameterized
_02234F7A:
	mov r0, #2
	tst r0, r4
	bne _02234F8C
	ldr r1, [r5, #0x30]
	ldr r0, [r5]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FillWindowPixelBuffer
_02234F8C:
	mov r0, #0
	ldr r1, [r5, #0x34]
	mvn r0, r0
	cmp r1, r0
	beq _02235004
	ldr r2, _022350B4 ; =0x00000193
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x4e
	bl NewMsgDataFromNarc
	ldr r7, [r5, #0x40]
	str r0, [sp, #0x14]
	cmp r7, #0
	bne _02234FB2
	mov r0, #0x4e
	bl ScrStrBufs_new
	add r7, r0, #0
_02234FB2:
	ldr r1, [sp, #0x14]
	ldr r2, [r5, #0x34]
	add r0, r7, #0
	mov r3, #0x4e
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	add r2, r4, #0
	bl MOD83_02234F08
	add r3, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r2, [sp, #0x18]
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r5]
	ldr r1, [r5, #0x28]
	bl AddTextPrinterParameterized2
	str r0, [r5, #0x48]
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [r5, #0x40]
	cmp r0, #0
	bne _02234FF8
	add r0, r7, #0
	bl ScrStrBufs_delete
_02234FF8:
	ldr r0, [sp, #0x14]
	bl DestroyMsgData
	mov r0, #0
	mvn r0, r0
	str r0, [r5, #0x34]
_02235004:
	ldr r0, [r5, #0x38]
	cmp r0, #0
	beq _0223504C
	mov r0, #0x40
	mov r1, #0x4e
	bl String_ctor
	ldr r1, [r5, #0x38]
	add r7, r0, #0
	mov r2, #0x40
	bl CopyU16ArrayToStringN
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl MOD83_02234F08
	add r3, r0, #0
	ldr r0, [r5, #0x1c]
	add r2, r7, #0
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r5]
	ldr r1, [r5, #0x28]
	bl AddTextPrinterParameterized2
	str r0, [r5, #0x48]
	add r0, r7, #0
	bl String_dtor
	mov r0, #0
	str r0, [r5, #0x38]
_0223504C:
	ldr r1, [r5, #0x3c]
	cmp r1, #0
	beq _0223507A
	add r0, r5, #0
	add r2, r4, #0
	bl MOD83_02234F08
	add r3, r0, #0
	ldr r0, [r5, #0x1c]
	str r0, [sp]
	str r6, [sp, #4]
	ldr r0, [r5, #0x2c]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r5]
	ldr r1, [r5, #0x28]
	ldr r2, [r5, #0x3c]
	bl AddTextPrinterParameterized2
	str r0, [r5, #0x48]
	mov r0, #0
	str r0, [r5, #0x3c]
_0223507A:
	mov r0, #4
	tst r0, r4
	bne _02235086
	ldr r0, [r5]
	bl CopyWindowToVram
_02235086:
	mov r0, #8
	tst r0, r4
	beq _022350AE
	mov r0, #0x10
	tst r0, r4
	ldr r0, [r5]
	beq _022350A2
	ldr r2, _022350B8 ; =0x000003D2
	mov r1, #0
	mov r3, #0xd
	bl FUN_0200D0BC
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
_022350A2:
	mov r2, #0x3f
	mov r1, #0
	lsl r2, r2, #4
	mov r3, #0xe
	bl FUN_0200CCA4
_022350AE:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_022350B4: .word 0x00000193
_022350B8: .word 0x000003D2
	thumb_func_end MOD83_02234F2C

	thumb_func_start MOD83_022350BC
MOD83_022350BC: ; 0x022350BC
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _022350E8 ; =MOD83_0223A50C
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x4e
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_022350E8: .word MOD83_0223A50C
	thumb_func_end MOD83_022350BC

	thumb_func_start MOD83_022350EC
MOD83_022350EC: ; 0x022350EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4e
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r6, #0
	mov r0, #0x50
	add r1, #0x2c
	mov r2, #0x4e
	bl FUN_02008C9C
	str r0, [r6, #0x28]
	add r0, r6, #0
	mov r2, #1
	add r0, #0x2c
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0x55
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02235132:
	mov r0, #3
	add r1, r4, #0
	mov r2, #0x4e
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02235132
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x4e
	str r0, [sp, #8]
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0x74
	mov r2, #0x1a
	bl FUN_02008F34
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0x4e
	sub r1, #0x14
	str r0, [sp, #0xc]
	ldr r0, [r6, r1]
	mov r1, #0x74
	mov r2, #0x17
	bl FUN_02008FEC
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r6, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4e
	sub r1, #0x14
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x74
	mov r2, #0x19
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4e
	sub r1, #0x14
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x74
	mov r2, #0x18
	mov r3, #1
	bl FUN_020090AC
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	bl FUN_02009A50
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009CF0
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0
	mov r2, #1
	str r0, [sp]
	mov r0, #0x4e
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #0x13
	add r3, #0xff
	bl GfGfxLoader_GXLoadPal
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022350EC

	thumb_func_start MOD83_022351F8
MOD83_022351F8: ; 0x022351F8
	push {lr}
	sub sp, #0x2c
	mov r1, #0
	str r1, [sp]
	sub r2, r1, #1
	str r2, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	mov r3, #0x55
	str r1, [sp, #0x10]
	lsl r3, r3, #2
	ldr r2, [r0, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r0, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r0, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r0, r2]
	add r3, #0x30
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r0, r3
	add r2, r1, #0
	add r3, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0x2c
	pop {pc}
	thumb_func_end MOD83_022351F8

	thumb_func_start MOD83_02235244
MOD83_02235244: ; 0x02235244
	ldr r2, [r1, #0x28]
	str r2, [r0]
	mov r2, #0x61
	lsl r2, r2, #2
	add r1, r1, r2
	str r1, [r0, #4]
	mov r2, #0
	mov r1, #1
	str r2, [r0, #0x10]
	lsl r1, r1, #0xc
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	strh r2, [r0, #0x20]
	mov r1, #0x14
	str r1, [r0, #0x24]
	str r3, [r0, #0x28]
	mov r1, #0x4e
	str r1, [r0, #0x2c]
	bx lr
	thumb_func_end MOD83_02235244

	thumb_func_start MOD83_0223526C
MOD83_0223526C: ; 0x0223526C
	ldr r3, _02235288 ; =0x0000E880
	ldr r0, [r0, r3]
	add r3, r0, #4
	mov r0, #0x96
	lsl r0, r0, #4
	mul r0, r1
	add r1, r3, r0
	mov r0, #0x50
	mul r0, r2
	add r0, r1, r0
	ldr r3, _0223528C ; =AGB_GetBoxMonData
	mov r1, #0xb
	mov r2, #0
	bx r3
	.align 2, 0
_02235288: .word 0x0000E880
_0223528C: .word AGB_GetBoxMonData
	thumb_func_end MOD83_0223526C

	thumb_func_start MOD83_02235290
MOD83_02235290: ; 0x02235290
	ldr r3, _022352AC ; =0x0000E880
	ldr r0, [r0, r3]
	add r3, r0, #4
	mov r0, #0x96
	lsl r0, r0, #4
	mul r0, r1
	add r1, r3, r0
	mov r0, #0x50
	mul r0, r2
	add r0, r1, r0
	ldr r3, _022352B0 ; =AGB_GetBoxMonData
	mov r1, #0x2d
	mov r2, #0
	bx r3
	.align 2, 0
_022352AC: .word 0x0000E880
_022352B0: .word AGB_GetBoxMonData
	thumb_func_end MOD83_02235290

	thumb_func_start MOD83_022352B4
MOD83_022352B4: ; 0x022352B4
	ldr r3, _022352D0 ; =0x0000E880
	ldr r0, [r0, r3]
	add r3, r0, #4
	mov r0, #0x96
	lsl r0, r0, #4
	mul r0, r1
	add r1, r3, r0
	mov r0, #0x50
	mul r0, r2
	add r0, r1, r0
	mov r1, #0
	ldr r3, _022352D4 ; =AGB_GetBoxMonData
	add r2, r1, #0
	bx r3
	.align 2, 0
_022352D0: .word 0x0000E880
_022352D4: .word AGB_GetBoxMonData
	thumb_func_end MOD83_022352B4

	thumb_func_start MOD83_022352D8
MOD83_022352D8: ; 0x022352D8
	push {r4, r5}
	ldr r5, [sp, #8]
	lsr r4, r5, #0x1f
	add r4, r5, r4
	asr r4, r4, #1
	sub r5, r2, r4
	strb r5, [r0]
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r5, r5, #1
	sub r3, r1, r5
	strb r3, [r0, #2]
	add r2, r2, r4
	strb r2, [r0, #1]
	add r1, r1, r5
	strb r1, [r0, #3]
	pop {r4, r5}
	bx lr
	thumb_func_end MOD83_022352D8

	thumb_func_start MOD83_022352FC
MOD83_022352FC: ; 0x022352FC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #1
	add r5, r0, #0
	add r0, r3, #0
	lsl r1, r1, #0xc
	add r7, r2, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	beq _02235330
	add r1, r5, #0
	add r2, r6, #0
	bl ReadWholeNarcMemberByIdPair
	add r0, r4, #0
	add r1, r7, #0
	bl NNS_G2dGetUnpackedBGCharacterData
	cmp r0, #0
	bne _02235330
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02235330:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022352FC

	thumb_func_start MOD83_02235334
MOD83_02235334: ; 0x02235334
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	add r0, r3, #0
	add r1, r6, #0
	bl NARC_ReadWholeMember
	add r0, r4, #0
	add r1, r5, #0
	bl NNS_G2dGetUnpackedBGCharacterData
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_02235334

	thumb_func_start MOD83_02235350
MOD83_02235350: ; 0x02235350
	push {r4, lr}
	add r3, r1, #0
	mov r4, #0
	cmp r0, #0xc9
	beq _02235362
	ldr r1, _022353BC ; =0x00000182
	cmp r0, r1
	beq _0223538C
	b _022353B6
_02235362:
	mov r4, #3
	lsl r0, r4, #8
	add r2, r3, #0
	and r0, r3
	lsr r1, r0, #6
	lsl r0, r4, #0x18
	and r2, r4
	and r0, r3
	lsl r4, r4, #0x10
	and r3, r4
	lsr r0, r0, #0x12
	lsr r3, r3, #0xc
	orr r0, r3
	orr r0, r1
	orr r0, r2
	mov r1, #0x1c
	bl _u32_div_f
	lsl r0, r1, #0x18
	lsr r4, r0, #0x18
	b _022353B6
_0223538C:
	cmp r2, #5
	bhi _022353A8
	add r0, r2, r2
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223539C: ; jump table
	.short _022353A8 - _0223539C - 2 ; case 0
	.short _022353A8 - _0223539C - 2 ; case 1
	.short _022353A8 - _0223539C - 2 ; case 2
	.short _022353B4 - _0223539C - 2 ; case 3
	.short _022353AC - _0223539C - 2 ; case 4
	.short _022353B0 - _0223539C - 2 ; case 5
_022353A8:
	mov r4, #0
	b _022353B6
_022353AC:
	mov r4, #1
	b _022353B6
_022353B0:
	mov r4, #2
	b _022353B6
_022353B4:
	mov r4, #3
_022353B6:
	add r0, r4, #0
	pop {r4, pc}
	nop
_022353BC: .word 0x00000182
	thumb_func_end MOD83_02235350

	thumb_func_start MOD83_022353C0
MOD83_022353C0: ; 0x022353C0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r7, r3, #0
	add r5, r1, #0
	bl MOD83_TranslateAgbSpecies
	add r1, r6, #0
	add r2, r7, #0
	add r4, r0, #0
	bl MOD83_02235350
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	add r2, r7, #0
	bl FUN_0206B6D4
	add r1, r0, #0
	mov r0, #0x13
	add r2, sp, #0
	mov r3, #0x4e
	bl MOD83_022352FC
	add r6, r0, #0
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0, #0x14]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r1, [sp, #0x18]
	ldr r0, [sp]
	lsl r1, r1, #4
	add r1, #0x64
	mov r2, #2
	ldr r0, [r0, #0x14]
	lsl r1, r1, #5
	lsl r2, r2, #8
	bl GX_LoadOBJ
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl FUN_0206B7BC
	add r1, r0, #0
	ldr r0, [sp, #0x1c]
	add r1, #8
	bl FUN_02020248
	add r0, r6, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022353C0

	thumb_func_start MOD83_0223542C
MOD83_0223542C: ; 0x0223542C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	ldr r1, _022354A8 ; =MOD83_0223BB14
	str r2, [sp]
	ldr r2, [r1]
	mov r1, #0x83
	add r5, r3, #0
	lsl r1, r1, #2
	mul r1, r5
	add r4, r2, r1
	ldr r1, [sp, #0x20]
	add r6, r0, #0
	cmp r1, #0
	beq _022354A0
	bl MOD83_RS_SpeciesIsInvalid
	cmp r0, #0
	bne _0223545C
	add r0, r6, #0
	bl MOD83_TranslateAgbSpecies
	add r6, r0, #0
	b _0223545E
_0223545C:
	mov r6, #0
_0223545E:
	ldr r2, [sp]
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_0206B6D4
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	add r1, sp, #4
	bl MOD83_02235334
	ldr r0, [sp, #4]
	add r1, r4, #0
	mov r2, #2
	ldr r0, [r0, #0x14]
	add r1, #0xc
	lsl r2, r2, #8
	bl MIi_CpuCopyFast
	lsl r0, r5, #4
	add r0, #0x64
	lsl r0, r0, #5
	str r0, [r4]
	ldr r0, [sp, #0x20]
	ldr r1, [sp]
	str r0, [r4, #8]
	add r0, r6, #0
	add r2, r7, #0
	bl FUN_0206B7BC
	add r0, #8
	add sp, #8
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_022354A0:
	mov r0, #0
	str r0, [r4, #8]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022354A8: .word MOD83_0223BB14
	thumb_func_end MOD83_0223542C

	thumb_func_start MOD83_022354AC
MOD83_022354AC: ; 0x022354AC
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _022354EC ; =MOD83_0223BB14
	mov r6, #2
	lsl r6, r6, #8
	add r7, r6, #0
	ldr r5, [r0]
	mov r4, #0
	add r7, #0xc
_022354BC:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _022354E0
	add r0, r5, #0
	add r0, #0xc
	add r1, r6, #0
	bl DC_FlushRange
	add r0, r5, #0
	ldr r1, [r5]
	add r0, #0xc
	add r2, r6, #0
	bl GX_LoadOBJ
	ldr r0, [r5, #8]
	ldr r1, [r5, #4]
	bl FUN_02020248
_022354E0:
	add r4, r4, #1
	add r5, r5, r7
	cmp r4, #0x1e
	blt _022354BC
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022354EC: .word MOD83_0223BB14
	thumb_func_end MOD83_022354AC

	thumb_func_start MOD83_022354F0
MOD83_022354F0: ; 0x022354F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	mov r0, #0x13
	mov r1, #0x4e
	bl NARC_ctor
	mov r1, #1
	str r0, [sp, #0xc]
	mov r0, #0x4e
	lsl r1, r1, #0xc
	bl AllocFromHeapAtEnd
	mov r6, #0
	str r0, [sp, #0x10]
	add r7, r6, #0
	add r4, r5, #0
_02235512:
	ldr r0, _02235634 ; =0x0000E880
	ldr r1, _02235638 ; =0x0000E884
	ldr r0, [r5, r0]
	ldr r2, [r5, r1]
	mov r1, #0x96
	lsl r1, r1, #4
	mul r1, r2
	add r0, r0, #4
	add r0, r0, r1
	add r0, r0, r7
	mov r1, #5
	mov r2, #0
	bl AGB_GetBoxMonData
	cmp r0, #0
	beq _022355D2
	ldr r1, _02235638 ; =0x0000E884
	add r0, r5, #0
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl MOD83_0223526C
	ldr r1, _02235638 ; =0x0000E884
	str r0, [sp, #0x1c]
	ldr r1, [r5, r1]
	add r0, r5, #0
	add r2, r6, #0
	bl MOD83_02235290
	ldr r1, _02235638 ; =0x0000E884
	str r0, [sp, #0x18]
	ldr r1, [r5, r1]
	add r0, r5, #0
	add r2, r6, #0
	bl MOD83_022352B4
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	bl MOD83_TranslateAgbSpecies
	ldr r2, _0223563C ; =gMain + 0x60
	ldr r1, [sp, #0x20]
	ldrb r2, [r2, #6]
	bl MOD83_02235350
	str r0, [sp, #0x14]
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x18]
	str r0, [sp]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x14]
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	add r3, r6, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	bl MOD83_0223542C
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _02235634 ; =0x0000E880
	ldr r1, _02235638 ; =0x0000E884
	ldr r0, [r5, r0]
	ldr r2, [r5, r1]
	mov r1, #0x96
	lsl r1, r1, #4
	mul r1, r2
	add r0, r0, #4
	add r0, r0, r1
	add r0, r0, r7
	mov r1, #0xc
	mov r2, #0
	bl AGB_GetBoxMonData
	cmp r0, #0
	beq _022355C4
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	b _02235602
_022355C4:
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	b _02235602
_022355D2:
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x14]
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	add r3, r6, #0
	bl MOD83_0223542C
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
_02235602:
	add r6, r6, #1
	add r7, #0x50
	add r4, #0xc
	cmp r6, #0x1e
	blt _02235512
	ldr r0, [sp, #0x10]
	bl FreeToHeap
	ldr r0, [sp, #0xc]
	bl NARC_dtor
	ldr r1, _02235640 ; =MOD83_022354AC
	ldr r0, _02235644 ; =0x00012604
	str r1, [r5, r0]
	ldr r1, _02235638 ; =0x0000E884
	add r0, r5, #0
	ldr r1, [r5, r1]
	bl MOD83_02235B6C
	add r0, r5, #0
	bl MOD83_02235B20
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02235634: .word 0x0000E880
_02235638: .word 0x0000E884
_0223563C: .word gMain + 0x60
_02235640: .word MOD83_022354AC
_02235644: .word 0x00012604
	thumb_func_end MOD83_022354F0

	thumb_func_start MOD83_02235648
MOD83_02235648: ; 0x02235648
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	mov r2, #0x61
	add r5, r0, #0
	lsl r2, r2, #2
	add r0, sp, #0x14
	add r1, r5, #0
	add r2, r5, r2
	mov r3, #1
	bl MOD83_02235244
	mov r0, #0x28
	str r0, [sp, #8]
	mov r0, #0x31
	mov r4, #0
	lsl r0, r0, #4
	str r4, [sp, #0xc]
	add r7, r5, r0
_0223566C:
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #8]
	mov r6, #0x1c
	lsl r0, r0, #0xc
	str r0, [sp, #4]
_02235678:
	mov r0, #0x1c
	str r0, [sp]
	ldr r2, [sp, #8]
	add r0, r7, #0
	add r1, r6, #0
	mov r3, #0x1c
	bl MOD83_022352D8
	lsl r0, r6, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [sp, #4]
	str r0, [sp, #0x20]
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _022356A6
	add r0, sp, #0x14
	bl FUN_0201FE94
	mov r1, #0x6a
	lsl r1, r1, #2
	str r0, [r5, r1]
_022356A6:
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x6a
	lsl r0, r0, #2
	add r1, r4, #0
	ldr r0, [r5, r0]
	add r1, #0xa
	bl FUN_02020130
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020238
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6a
	lsl r0, r0, #2
	add r1, r4, #0
	ldr r0, [r5, r0]
	add r1, #0x64
	bl FUN_02020310
	mov r0, #6
	ldr r1, [sp, #0x1c]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x1c]
	mov r0, #3
	ldr r1, [sp, #0x20]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x20]
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _02235710
	add r0, sp, #0x14
	bl FUN_0201FE94
	mov r1, #0x6b
	lsl r1, r1, #2
	str r0, [r5, r1]
_02235710:
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0x28
	bl FUN_02020130
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020238
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02020310
	add r4, r4, #1
	add r7, r7, #4
	add r5, #0xc
	cmp r4, #0x1e
	beq _02235774
	ldr r0, [sp, #0x10]
	add r6, #0x28
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #6
	blt _02235678
	ldr r0, [sp, #8]
	add r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #5
	bge _02235774
	b _0223566C
_02235774:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD83_02235648

	thumb_func_start MOD83_02235778
MOD83_02235778: ; 0x02235778
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r4, r2, #0
	mov r2, #0x61
	add r6, r0, #0
	lsl r2, r2, #2
	add r5, r1, #0
	add r7, r3, #0
	add r0, sp, #0
	add r1, r6, #0
	add r2, r6, r2
	mov r3, #1
	bl MOD83_02235244
	lsl r0, r5, #0xc
	str r0, [sp, #8]
	lsl r0, r4, #0xc
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x24]
	add r0, sp, #0
	bl FUN_0201FE94
	add r4, r0, #0
	mov r1, #1
	bl FUN_020200BC
	add r0, r4, #0
	add r1, r7, #0
	bl FUN_02020130
	add r0, r4, #0
	mov r1, #1
	bl FUN_02020238
	ldr r1, [sp, #0x48]
	add r0, r4, #0
	bl FUN_020200A0
	add r0, r4, #0
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_02235778

	thumb_func_start MOD83_022357CC
MOD83_022357CC: ; 0x022357CC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0xe2
	lsl r0, r0, #2
	add r0, r6, r0
	mov r1, #0xe4
	mov r2, #0xb0
	mov r3, #0x32
	bl MOD83_022352D8
	mov r0, #1
	str r0, [sp]
	add r0, r6, #0
	mov r1, #0xe4
	mov r2, #0xb0
	mov r3, #6
	bl MOD83_02235778
	mov r1, #0xe6
	lsl r1, r1, #2
	str r0, [r6, r1]
	sub r1, #8
	add r0, r6, r1
	mov r1, #0xb0
	mov r3, #0x20
	add r2, r1, #0
	str r3, [sp]
	bl MOD83_022352D8
	mov r0, #1
	mov r1, #0xb0
	str r0, [sp]
	add r0, r6, #0
	add r2, r1, #0
	mov r3, #3
	bl MOD83_02235778
	mov r1, #0xea
	lsl r1, r1, #2
	str r0, [r6, r1]
	sub r1, #0x1c
	mov r3, #0x20
	add r0, r6, r1
	mov r1, #0x18
	mov r2, #0xb0
	str r3, [sp]
	bl MOD83_022352D8
	mov r0, #1
	str r0, [sp]
	add r0, r6, #0
	mov r1, #0x18
	mov r2, #0xb0
	mov r3, #0
	bl MOD83_02235778
	mov r1, #0xee
	lsl r1, r1, #2
	str r0, [r6, r1]
	mov r7, #0
	mov r0, #0xff
	sub r1, #0x24
	strb r0, [r6, r1]
	add r4, r7, #0
	add r5, r6, #0
_02235852:
	mov r0, #0
	str r0, [sp]
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0x40
	mov r3, #9
	bl MOD83_02235778
	mov r1, #0xf2
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r1, #0
	mov r0, #0xf3
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0xe
	add r0, r0, #4
	str r1, [r5, r0]
	add r7, r7, #1
	add r4, #0x24
	add r5, #0xc
	cmp r7, #6
	blt _02235852
	mov r0, #0x41
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022357CC

	thumb_func_start MOD83_0223588C
MOD83_0223588C: ; 0x0223588C
	push {r3, lr}
	ldr r3, _022358C0 ; =0x0000E880
	ldr r2, [r0, r3]
	add r3, r3, #4
	ldr r3, [r0, r3]
	mov r0, #0x96
	lsl r0, r0, #4
	add r2, r2, #4
	mul r0, r3
	add r2, r2, r0
	mov r0, #0x50
	mul r0, r1
	add r0, r2, r0
	mov r1, #0x41
	mov r2, #0
	bl AGB_GetBoxMonData
	mov r1, #0x67
	lsl r1, r1, #2
	cmp r0, r1
	bne _022358BA
	mov r0, #1
	pop {r3, pc}
_022358BA:
	mov r0, #0
	pop {r3, pc}
	nop
_022358C0: .word 0x0000E880
	thumb_func_end MOD83_0223588C

	thumb_func_start MOD83_022358C4
MOD83_022358C4: ; 0x022358C4
	push {r3, r4, r5, r6, r7, lr}
	ldr r3, _02235910 ; =0x0000E880
	mov r5, #0
	ldr r2, [r0, r3]
	add r3, r3, #4
	ldr r3, [r0, r3]
	mov r0, #0x96
	lsl r0, r0, #4
	add r2, r2, #4
	mul r0, r3
	add r4, r2, r0
	mov r0, #0x50
	add r6, r1, #0
	mul r6, r0
	add r7, r5, #0
_022358E2:
	add r1, r5, #0
	add r0, r4, r6
	add r1, #0xd
	add r2, r7, #0
	bl AGB_GetBoxMonData
	ldr r3, _02235914 ; =MOD83_0223B2B8
	add r2, r0, #0
	mov r1, #0
_022358F4:
	ldr r0, [r3]
	cmp r2, r0
	bne _022358FE
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022358FE:
	add r1, r1, #1
	add r3, r3, #4
	cmp r1, #8
	blo _022358F4
	add r5, r5, #1
	cmp r5, #4
	blt _022358E2
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235910: .word 0x0000E880
_02235914: .word MOD83_0223B2B8
	thumb_func_end MOD83_022358C4

	thumb_func_start MOD83_02235918
MOD83_02235918: ; 0x02235918
	push {r3, lr}
	ldr r3, _0223595C ; =0x0000E880
	ldr r2, [r0, r3]
	add r3, r3, #4
	ldr r3, [r0, r3]
	mov r0, #0x96
	lsl r0, r0, #4
	add r2, r2, #4
	mul r0, r3
	add r2, r2, r0
	mov r0, #0x50
	mul r0, r1
	add r0, r2, r0
	mov r1, #0xc
	mov r2, #0
	bl AGB_GetBoxMonData
	ldr r1, _02235960 ; =MOD83_InvalidItemIds - 0x30
	ldrh r1, [r1, #0x30]
	cmp r1, #0
	beq _02235956
	ldr r2, _02235964 ; =MOD83_InvalidItemIds
_02235944:
	ldrh r1, [r2]
	cmp r0, r1
	bne _0223594E
	mov r0, #1
	pop {r3, pc}
_0223594E:
	add r2, r2, #2
	ldrh r1, [r2]
	cmp r1, #0
	bne _02235944
_02235956:
	mov r0, #0
	pop {r3, pc}
	nop
_0223595C: .word 0x0000E880
_02235960: .word MOD83_InvalidItemIds - 0x30
_02235964: .word MOD83_InvalidItemIds
	thumb_func_end MOD83_02235918

	thumb_func_start MOD83_02235968
MOD83_02235968: ; 0x02235968
	push {r3, lr}
	ldr r3, _02235990 ; =0x0000E880
	ldr r2, [r0, r3]
	add r3, r3, #4
	ldr r3, [r0, r3]
	mov r0, #0x96
	lsl r0, r0, #4
	add r2, r2, #4
	mul r0, r3
	add r2, r2, r0
	mov r0, #0x50
	mul r0, r1
	add r0, r2, r0
	mov r1, #0xb
	mov r2, #0
	bl AGB_GetBoxMonData
	bl MOD83_RS_SpeciesIsInvalid
	pop {r3, pc}
	.align 2, 0
_02235990: .word 0x0000E880
	thumb_func_end MOD83_02235968

	thumb_func_start MOD83_02235994
MOD83_02235994: ; 0x02235994
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x6a
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp]
	add r6, r1, #0
	mov r0, #0xc
	mul r0, r6
	ldr r1, [sp]
	str r0, [sp, #4]
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022359C0
	bl FUN_02020128
	cmp r0, #0
	bne _022359C0
	add sp, #0x14
	mov r0, #3
	pop {r4, r5, r6, r7, pc}
_022359C0:
	mov r5, #0
	mov r7, #0x3d
	mvn r5, r5
	mov r2, #0
	add r3, r4, #0
	lsl r7, r7, #4
	b _022359E8
_022359CE:
	ldr r0, _02235B1C ; =0x0000E884
	ldr r1, [r4, r0]
	ldr r0, [r3, r7]
	cmp r1, r0
	bne _022359E4
	mov r0, #0xf3
	lsl r0, r0, #2
	ldr r0, [r3, r0]
	cmp r6, r0
	bne _022359E4
	add r5, r2, #0
_022359E4:
	add r3, #0xc
	add r2, r2, #1
_022359E8:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _022359F4
	cmp r2, #6
	blt _022359CE
_022359F4:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD83_0223588C
	cmp r0, #1
	bne _02235A06
	add sp, #0x14
	mov r0, #4
	pop {r4, r5, r6, r7, pc}
_02235A06:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD83_022358C4
	cmp r0, #1
	bne _02235A18
	add sp, #0x14
	mov r0, #5
	pop {r4, r5, r6, r7, pc}
_02235A18:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD83_02235918
	cmp r0, #1
	bne _02235A2A
	add sp, #0x14
	mov r0, #6
	pop {r4, r5, r6, r7, pc}
_02235A2A:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD83_02235968
	cmp r0, #1
	bne _02235A3C
	add sp, #0x14
	mov r0, #7
	pop {r4, r5, r6, r7, pc}
_02235A3C:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _02235AE4
	mov r0, #0x41
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #6
	bne _02235A54
	add sp, #0x14
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02235A54:
	mov r5, #0
	mov r0, #0xf3
	add r3, r4, #0
	lsl r0, r0, #2
	sub r1, r5, #1
_02235A5E:
	ldr r2, [r3, r0]
	cmp r2, r1
	bne _02235ADA
	ldr r1, [sp]
	ldr r0, [sp, #4]
	ldr r0, [r1, r0]
	bl FUN_0202011C
	add r1, r0, #0
	mov r0, #0xc
	add r7, r5, #0
	mul r7, r0
	mov r0, #0xf2
	lsl r0, r0, #2
	add r5, r4, r0
	ldr r0, [r5, r7]
	bl FUN_02020044
	ldr r0, [r5, r7]
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #8
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #2
	str r0, [r2]
	ldr r0, [sp, #8]
	lsl r1, r1, #0xe
	sub r0, r0, r1
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	lsr r1, r1, #1
	sub r0, r0, r1
	str r0, [sp, #0xc]
	ldr r0, [r5, r7]
	mov r1, ip
	bl FUN_02020044
	ldr r0, [r5, r7]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #0xf3
	add r3, r4, r7
	lsl r1, r1, #2
	ldr r0, _02235B1C ; =0x0000E884
	str r6, [r3, r1]
	ldr r2, [r4, r0]
	add r0, r1, #4
	str r2, [r3, r0]
	add r0, r1, #0
	add r0, #0x44
	ldr r0, [r4, r0]
	add r1, #0x44
	add r0, r0, #1
	str r0, [r4, r1]
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02235ADA:
	add r5, r5, #1
	add r3, #0xc
	cmp r5, #6
	blt _02235A5E
	b _02235B16
_02235AE4:
	mov r0, #0xc
	add r6, r5, #0
	mul r6, r0
	mov r0, #0xf2
	add r1, r4, r6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r2, #0
	mov r1, #0xf3
	mvn r2, r2
	add r0, r4, r6
	lsl r1, r1, #2
	str r2, [r0, r1]
	add r0, r1, #0
	add r0, #0x44
	ldr r0, [r4, r0]
	add r1, #0x44
	sub r0, r0, #1
	str r0, [r4, r1]
	add sp, #0x14
	mov r0, #2
	pop {r4, r5, r6, r7, pc}
_02235B16:
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02235B1C: .word 0x0000E884
	thumb_func_end MOD83_02235994

	thumb_func_start MOD83_02235B20
MOD83_02235B20: ; 0x02235B20
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
	sub r7, r4, #1
_02235B2A:
	mov r0, #0xf3
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, r7
	beq _02235B50
	ldr r0, _02235B68 ; =0x0000E884
	ldr r1, [r6, r0]
	mov r0, #0x3d
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r1, r0
	bne _02235B50
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	b _02235B5C
_02235B50:
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
_02235B5C:
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #6
	blt _02235B2A
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02235B68: .word 0x0000E884
	thumb_func_end MOD83_02235B20

	thumb_func_start MOD83_02235B6C
MOD83_02235B6C: ; 0x02235B6C
	push {r3, r4, r5, lr}
	sub sp, #0x60
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	add r3, sp, #0x14
	add r1, r0, #0
	mov r2, #4
_02235B7C:
	stmia r3!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02235B7C
	stmia r3!, {r0, r1}
	str r0, [r3]
	ldr r0, _02235BE4 ; =0x00000478
	add r0, r5, r0
	str r0, [sp, #0x14]
	mov r0, #6
	str r0, [sp, #0x1c]
	mov r0, #0x15
	str r0, [sp, #0x20]
	mov r0, #0xd
	str r0, [sp, #0x24]
	mov r0, #2
	str r0, [sp, #0x28]
	sub r0, r0, #3
	str r0, [sp, #0x48]
	mov r0, #0
	str r0, [sp, #0x2c]
	str r0, [sp, #0x30]
	mov r0, #1
	str r0, [sp, #0x38]
	str r0, [sp, #0x3c]
	ldr r0, _02235BE8 ; =0x00010200
	str r0, [sp, #0x40]
	mov r0, #0xa0
	str r0, [sp, #0x34]
	bl MOD83_02236EA8
	add r3, r0, #0
	ldr r0, _02235BEC ; =0x0000E880
	mov r2, #9
	ldr r1, [r5, r0]
	ldr r0, _02235BF0 ; =0x00008344
	add r1, r1, r0
	lsl r0, r4, #3
	add r0, r4, r0
	add r0, r1, r0
	add r1, sp, #0
	bl FUN_02015D88
	add r0, sp, #0
	str r0, [sp, #0x4c]
	add r0, r5, #0
	add r1, sp, #0x14
	mov r2, #1
	bl MOD83_02234F2C
	add sp, #0x60
	pop {r3, r4, r5, pc}
	.align 2, 0
_02235BE4: .word 0x00000478
_02235BE8: .word 0x00010200
_02235BEC: .word 0x0000E880
_02235BF0: .word 0x00008344
	thumb_func_end MOD83_02235B6C

	thumb_func_start MOD83_02235BF4
MOD83_02235BF4: ; 0x02235BF4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x20]
	add r6, r1, #0
	mov r1, #2
	bl GetBgTilemapBuffer
	add r4, r0, #0
	cmp r6, #0
	beq _02235C18
	add r0, r6, #0
	mov r1, #8
	mov r2, #0
	bl AGB_GetBoxMonData
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _02235C1A
_02235C18:
	mov r1, #0
_02235C1A:
	mov r2, #0
	mov r0, #1
_02235C1E:
	add r3, r1, #0
	tst r3, r0
	beq _02235C2A
	add r6, r2, #0
	add r6, #0x80
	b _02235C2E
_02235C2A:
	add r6, r2, #0
	add r6, #0x60
_02235C2E:
	add r3, r4, #0
	add r3, #0xd6
	lsl r1, r1, #0x17
	add r2, r2, #1
	strh r6, [r3]
	lsr r1, r1, #0x18
	add r4, r4, #2
	cmp r2, #4
	blt _02235C1E
	ldr r0, [r5, #0x20]
	mov r1, #2
	bl FUN_02017CD0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_02235BF4

	thumb_func_start MOD83_02235C4C
MOD83_02235C4C: ; 0x02235C4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x78
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	add r3, sp, #0x2c
	add r1, r0, #0
	mov r2, #4
_02235C5C:
	stmia r3!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02235C5C
	stmia r3!, {r0, r1}
	str r0, [r3]
	mov r1, #0x20
	str r1, [sp, #0x3c]
	mov r1, #1
	ldr r0, _02235DF8 ; =0x00000488
	str r1, [sp, #0x50]
	str r1, [sp, #0x54]
	mov r1, #0xbc
	str r1, [sp, #0x4c]
	ldr r1, _02235DFC ; =0x000F0200
	add r0, r5, r0
	str r1, [sp, #0x58]
	mov r1, #0x2c
	str r0, [sp, #0x2c]
	mov r0, #0
	str r1, [sp, #0x60]
	mov r1, #0x90
	mov r2, #4
	str r1, [sp, #0x44]
	str r0, [sp, #0x34]
	str r0, [sp, #0x38]
	str r0, [sp, #0x64]
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r1, sp, #0x2c
	str r2, [sp, #0x40]
	bl MOD83_02234F2C
	mov r0, #0x2b
	str r0, [sp, #0x60]
	mov r0, #0x50
	str r0, [sp, #0x44]
	mov r0, #8
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r1, sp, #0x2c
	mov r2, #6
	bl MOD83_02234F2C
	add r0, r5, #0
	add r1, r4, #0
	bl MOD83_02235BF4
	cmp r4, #0
	bne _02235CCA
	ldr r0, [sp, #0x2c]
	bl CopyWindowToVram
	add sp, #0x78
	pop {r3, r4, r5, r6, r7, pc}
_02235CCA:
	add r2, sp, #0x1c
	add r0, r4, #0
	mov r1, #2
	add r2, #2
	bl AGB_GetBoxMonData
	add r0, r4, #0
	mov r1, #3
	mov r2, #0
	bl AGB_GetBoxMonData
	add r3, r0, #0
	add r0, sp, #0x1c
	add r0, #2
	add r1, sp, #8
	mov r2, #0xb
	bl FUN_02015D88
	add r0, sp, #8
	str r0, [sp, #0x64]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x60]
	mov r0, #8
	str r0, [sp, #0x44]
	mov r0, #0
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r1, sp, #0x2c
	mov r2, #6
	bl MOD83_02234F2C
	mov r0, #0x40
	mov r1, #0x4e
	bl String_ctor
	add r6, r0, #0
	ldr r2, _02235E00 ; =0x0000016A
	mov r0, #1
	mov r1, #0x1a
	mov r3, #0x4e
	bl NewMsgDataFromNarc
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #0xb
	mov r2, #0
	bl AGB_GetBoxMonData
	bl MOD83_TranslateAgbSpecies
	str r0, [sp, #4]
	ldr r1, [sp, #4]
	add r0, r7, #0
	add r2, r6, #0
	bl ReadMsgDataIntoString
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x60]
	mov r0, #0x10
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r1, sp, #0x2c
	mov r2, #6
	str r6, [sp, #0x68]
	bl MOD83_02234F2C
	add r0, r7, #0
	bl DestroyMsgData
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	mov r1, #0xc
	mov r2, #0
	bl AGB_GetBoxMonData
	cmp r0, #0
	beq _02235DAC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl UpConvertItemId_Gen3to4
	add r7, r0, #0
	mov r0, #0x40
	mov r1, #0x4e
	bl String_ctor
	lsl r1, r7, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x4e
	add r6, r0, #0
	bl GetItemNameIntoString
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x60]
	mov r0, #0x98
	str r0, [sp, #0x44]
	mov r0, #0x10
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r1, sp, #0x2c
	mov r2, #6
	str r6, [sp, #0x68]
	bl MOD83_02234F2C
	add r0, r6, #0
	bl String_dtor
_02235DAC:
	add r0, r4, #0
	bl MOD83_02237EDC
	add r6, r0, #0
	mov r0, #0xa
	mov r1, #0x4e
	bl String_ctor
	mov r3, #1
	add r1, r6, #0
	mov r2, #3
	add r4, r0, #0
	str r3, [sp]
	bl String16_FormatInteger
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0x60]
	mov r0, #0x64
	str r0, [sp, #0x44]
	mov r0, #8
	str r0, [sp, #0x48]
	add r0, r5, #0
	add r1, sp, #0x2c
	mov r2, #2
	str r4, [sp, #0x68]
	bl MOD83_02234F2C
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
	add sp, #0x78
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235DF8: .word 0x00000488
_02235DFC: .word 0x000F0200
_02235E00: .word 0x0000016A
	thumb_func_end MOD83_02235C4C

	thumb_func_start MOD83_02235E04
MOD83_02235E04: ; 0x02235E04
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4e
	str r0, [sp, #8]
	add r6, r2, #0
	mov r0, #0
	add r4, r3, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	cmp r4, #0
	beq _02235E2C
	mov r0, #0x17
	str r0, [r4]
_02235E2C:
	str r6, [r5, #0x24]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_02235E04

	thumb_func_start MOD83_02235E34
MOD83_02235E34: ; 0x02235E34
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	add r4, r3, #0
	str r0, [sp, #4]
	mov r0, #0x4e
	add r6, r2, #0
	str r0, [sp, #8]
	ldr r3, _02235E64 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	cmp r4, #0
	beq _02235E5C
	mov r0, #0x17
	str r0, [r4]
_02235E5C:
	str r6, [r5, #0x24]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02235E64: .word 0x00007FFF
	thumb_func_end MOD83_02235E34

	thumb_func_start MOD83_02235E68
MOD83_02235E68: ; 0x02235E68
	push {r3, r4, r5, lr}
	sub sp, #0x80
	ldr r5, _02235F28 ; =MOD83_0223A51C
	add r3, sp, #0x70
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _02235F2C ; =MOD83_0223A52C
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02235F30 ; =MOD83_0223A548
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _02235F34 ; =MOD83_0223A564
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _02235F38 ; =MOD83_0223A580
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	add sp, #0x80
	pop {r3, r4, r5, pc}
	nop
_02235F28: .word MOD83_0223A51C
_02235F2C: .word MOD83_0223A52C
_02235F30: .word MOD83_0223A548
_02235F34: .word MOD83_0223A564
_02235F38: .word MOD83_0223A580
	thumb_func_end MOD83_02235E68

	thumb_func_start MOD83_02235F3C
MOD83_02235F3C: ; 0x02235F3C
	push {r3, r4, r5, lr}
	sub sp, #0x38
	ldr r5, _02235FB4 ; =MOD83_0223A59C
	add r4, r0, #0
	add r3, sp, #0x10
	mov r2, #5
_02235F48:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02235F48
	add r0, sp, #0x10
	bl GX_SetBanks
	ldr r0, [r4, #0x20]
	bl MOD83_02235E68
	ldr r0, _02235FB8 ; =gMain + 0x60
	mov r1, #1
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	bl FUN_0201BD5C
	mov r1, #0x1e
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x4e
	bl FUN_02002ED0
	mov r0, #0xc0
	str r0, [sp]
	mov r0, #0x4e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x13
	add r3, r2, #0
	bl GfGfxLoader_GXLoadPal
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4e
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x20]
	mov r0, #0x74
	mov r1, #0x16
	mov r3, #2
	bl GfGfxLoader_LoadCharData
	mov r0, #2
	mov r1, #0x4e
	bl FUN_02002C50
	add sp, #0x38
	pop {r3, r4, r5, pc}
	.align 2, 0
_02235FB4: .word MOD83_0223A59C
_02235FB8: .word gMain + 0x60
	thumb_func_end MOD83_02235F3C

	thumb_func_start MOD83_02235FBC
MOD83_02235FBC: ; 0x02235FBC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4e
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x20]
	mov r0, #0x74
	mov r1, #0x14
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r2, #0
	ldr r1, [r4]
	ldr r0, _02236008 ; =MOD83_0223B280
	add r3, r2, #0
	ldrb r0, [r0, r1]
	mov r1, #2
	str r0, [sp, #8]
	ldr r0, [r4, #0x20]
	bl FUN_020186B4
	ldr r0, [r4, #0x20]
	mov r1, #2
	bl FUN_02017CD0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02236008: .word MOD83_0223B280
	thumb_func_end MOD83_02235FBC

	thumb_func_start MOD83_0223600C
MOD83_0223600C: ; 0x0223600C
	push {r4, lr}
	sub sp, #8
	mov r1, #7
	add r4, r0, #0
	mov r0, #0
	lsl r1, r1, #6
	mov r2, #0x4e
	bl FUN_02002ED0
	mov r1, #0
	mov r2, #0x3f
	str r1, [sp]
	mov r0, #0x4e
	str r0, [sp, #4]
	ldr r0, [r4, #0x20]
	lsl r2, r2, #4
	mov r3, #0xe
	bl FUN_0200CB00
	ldr r0, [r4, #0x1c]
	ldr r2, _022360B4 ; =0x000003D2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x4e
	str r0, [sp, #4]
	ldr r0, [r4, #0x20]
	mov r1, #0
	mov r3, #0xd
	bl FUN_0200CD68
	ldr r0, _022360B8 ; =0x0000042C
	mov r1, #0
	add r0, r4, r0
	mov r2, #0x4c
	bl memset
	ldr r0, _022360BC ; =0x00000498
	mov r3, #0x1b
	add r1, r0, #0
	add r2, r4, r0
	sub r1, #0x6c
	str r2, [r4, r1]
	add r1, r0, #0
	mov r2, #2
	sub r1, #0x64
	str r2, [r4, r1]
	add r1, r0, #0
	mov r2, #1
	sub r1, #0x60
	str r2, [r4, r1]
	add r1, r0, #0
	sub r1, #0x5c
	str r3, [r4, r1]
	add r1, r0, #0
	mov r3, #4
	sub r1, #0x58
	str r3, [r4, r1]
	add r3, r0, #0
	mov r1, #0
	sub r3, #0x48
	str r1, [r4, r3]
	add r3, r0, #0
	sub r3, #0x44
	str r2, [r4, r3]
	add r3, r0, #0
	sub r3, #0x4c
	str r2, [r4, r3]
	add r2, r0, #0
	ldr r3, _022360C0 ; =0x0001020F
	sub r2, #0x40
	str r3, [r4, r2]
	add r2, r0, #0
	ldr r3, _022360C4 ; =0x000F020F
	sub r2, #0x3c
	str r3, [r4, r2]
	add r2, r0, #0
	sub r2, #0x34
	str r1, [r4, r2]
	sub r0, #0x30
	str r1, [r4, r0]
	add sp, #8
	pop {r4, pc}
	nop
_022360B4: .word 0x000003D2
_022360B8: .word 0x0000042C
_022360BC: .word 0x00000498
_022360C0: .word 0x0001020F
_022360C4: .word 0x000F020F
	thumb_func_end MOD83_0223600C

	thumb_func_start MOD83_022360C8
MOD83_022360C8: ; 0x022360C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r6, r0, #0
	mov r7, #0x6b
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_022360D6:
	mov r0, #0x6a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, r7]
	mov r1, #0
	bl FUN_020200A0
	add r5, r5, #1
	add r4, #0xc
	cmp r5, #0x1e
	blt _022360D6
	mov r7, #0xf2
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_022360FA:
	ldr r0, [r4, r7]
	mov r1, #0
	bl FUN_020200A0
	add r5, r5, #1
	add r4, #0xc
	cmp r5, #6
	blt _022360FA
	mov r0, #0xe6
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xee
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0xea
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r2, #0x61
	lsl r2, r2, #2
	add r0, sp, #0x1c
	add r1, r6, #0
	add r2, r6, r2
	mov r3, #1
	bl MOD83_02235244
	mov r0, #0x1c
	mov r7, #0
	str r0, [sp, #0x10]
	add r4, r6, #0
	add r5, r6, #0
_02236148:
	ldr r0, [sp, #0x10]
	lsl r0, r0, #0xc
	str r0, [sp, #0x24]
	mov r0, #0x8e
	lsl r0, r0, #0xc
	str r0, [sp, #0x28]
	add r0, sp, #0x1c
	bl FUN_0201FE94
	ldr r1, _02236288 ; =0x00000414
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _02236288 ; =0x00000414
	add r1, r7, #0
	ldr r0, [r4, r0]
	add r1, #0xa
	bl FUN_02020130
	ldr r0, _02236288 ; =0x00000414
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_02020238
	ldr r0, _02236288 ; =0x00000414
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_020200A0
	mov r1, #0x3d
	mov r2, #0xf3
	lsl r1, r1, #4
	lsl r2, r2, #2
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r0, r6, #0
	bl MOD83_0223526C
	mov r1, #0x3d
	mov r2, #0xf3
	lsl r1, r1, #4
	lsl r2, r2, #2
	str r0, [sp, #0x14]
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r0, r6, #0
	bl MOD83_02235290
	mov r1, #0x3d
	mov r2, #0xf3
	lsl r1, r1, #4
	lsl r2, r2, #2
	str r0, [sp, #0x18]
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r0, r6, #0
	bl MOD83_022352B4
	add r2, r0, #0
	ldr r0, _02236288 ; =0x00000414
	str r7, [sp]
	ldr r0, [r4, r0]
	ldr r3, _0223628C ; =gMain + 0x60
	str r0, [sp, #4]
	ldrb r3, [r3, #6]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	bl MOD83_022353C0
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	add r0, #0x28
	str r0, [sp, #0x10]
	add r4, r4, #4
	add r5, #0xc
	cmp r7, #6
	blt _02236148
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x4e
	str r0, [sp, #0xc]
	ldr r2, [r6, #0x20]
	mov r0, #0x74
	mov r1, #0x15
	mov r3, #2
	bl GfGfxLoader_LoadScrnData
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r2, #0
	ldr r1, [r6]
	ldr r0, _02236290 ; =MOD83_0223B280
	add r3, r2, #0
	ldrb r0, [r0, r1]
	mov r1, #2
	str r0, [sp, #8]
	ldr r0, [r6, #0x20]
	bl FUN_020186B4
	ldr r0, [r6, #0x20]
	mov r1, #2
	bl FUN_02017CD0
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r1, #7
	mov r0, #0
	lsl r1, r1, #6
	mov r2, #0x4e
	bl FUN_02002ED0
	mov r1, #0
	mov r2, #0x3f
	str r1, [sp]
	mov r0, #0x4e
	str r0, [sp, #4]
	ldr r0, [r6, #0x20]
	lsl r2, r2, #4
	mov r3, #0xe
	bl FUN_0200CB00
	ldr r0, [r6, #0x1c]
	ldr r2, _02236294 ; =0x000003D2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x4e
	str r0, [sp, #4]
	ldr r0, [r6, #0x20]
	mov r1, #0
	mov r3, #0xd
	bl FUN_0200CD68
	add r0, r6, #0
	bl MOD83_0223600C
	mov r1, #0x46
	mov r0, #0xa
	lsl r1, r1, #4
	str r0, [r6, r1]
	sub r1, #0x34
	add r0, r6, #0
	add r1, r6, r1
	mov r2, #0x18
	bl MOD83_02234F2C
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02236288: .word 0x00000414
_0223628C: .word gMain + 0x60
_02236290: .word MOD83_0223B280
_02236294: .word 0x000003D2
	thumb_func_end MOD83_022360C8

	thumb_func_start MOD83_02236298
MOD83_02236298: ; 0x02236298
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _022362B4
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r4, #0
	bl FUN_02019570
	add r0, r4, #0
	bl RemoveWindow
_022362B4:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD83_02236298

	thumb_func_start MOD83_022362B8
MOD83_022362B8: ; 0x022362B8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r7, _02236328 ; =0x00000414
	mov r4, #0
	add r5, r6, #0
_022362C2:
	ldr r0, [r5, r7]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _022362C2
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, _0223632C ; =0x00000498
	add r0, r6, r0
	bl MOD83_02236298
	mov r0, #0xe6
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xee
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xea
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xf3
	mov r5, #0
	lsl r0, r0, #2
	add r4, r6, #0
	sub r3, r5, #1
	mov r2, #0xe
	add r1, r0, #4
_02236312:
	str r3, [r4, r0]
	str r2, [r4, r1]
	add r5, r5, #1
	add r4, #0xc
	cmp r5, #6
	blt _02236312
	mov r0, #0x41
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r6, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02236328: .word 0x00000414
_0223632C: .word 0x00000498
	thumb_func_end MOD83_022362B8

	thumb_func_start MOD83_02236330
MOD83_02236330: ; 0x02236330
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r7, #0x6a
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02236344:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _0223634E
	bl FUN_0201FFC8
_0223634E:
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0223635C
	bl FUN_0201FFC8
_0223635C:
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #0x1e
	blt _02236344
	mov r7, #0xf2
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_0223636C:
	ldr r0, [r4, r7]
	cmp r0, #0
	beq _02236376
	bl FUN_0201FFC8
_02236376:
	add r5, r5, #1
	add r4, #0xc
	cmp r5, #6
	blt _0223636C
	mov r0, #0xe6
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _0223638C
	bl FUN_0201FFC8
_0223638C:
	mov r0, #0xee
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _0223639A
	bl FUN_0201FFC8
_0223639A:
	mov r0, #0xea
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _022363A8
	bl FUN_0201FFC8
_022363A8:
	ldr r0, _0223643C ; =0x00000478
	add r0, r6, r0
	bl MOD83_02236298
	ldr r0, _02236440 ; =0x00000488
	add r0, r6, r0
	bl MOD83_02236298
	ldr r0, _02236444 ; =0x00000498
	add r0, r6, r0
	bl MOD83_02236298
	mov r0, #2
	bl FUN_02002CF8
	mov r0, #0x5b
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0x55
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #2
_022363E2:
	ldr r0, [r4, r7]
	bl FUN_02008E2C
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #6
	blt _022363E2
	ldr r0, [r6, #0x28]
	bl FUN_0201FD58
	mov r0, #0
	str r0, [r6, #0x28]
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	ldr r0, _02236448 ; =0x0000E88C
	ldr r0, [r6, r0]
	bl FUN_020145A8
	ldr r0, _0223644C ; =gMain + 0x60
	mov r1, #0
	strb r1, [r0, #5]
	bl GX_SwapDisplay
	ldr r0, [r6, #0x20]
	mov r1, #0
	bl FUN_020178A0
	ldr r0, [r6, #0x20]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r6, #0x20]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r6, #0x20]
	mov r1, #3
	bl FUN_020178A0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223643C: .word 0x00000478
_02236440: .word 0x00000488
_02236444: .word 0x00000498
_02236448: .word 0x0000E88C
_0223644C: .word gMain + 0x60
	thumb_func_end MOD83_02236330

	thumb_func_start MOD83_02236450
MOD83_02236450: ; 0x02236450
	push {lr}
	sub sp, #0x14
	ldr r1, [r0, #0x20]
	mov r2, #0x19
	str r1, [sp]
	mov r1, #0
	str r1, [sp, #4]
	mov r1, #2
	lsl r1, r1, #8
	str r1, [sp, #8]
	mov r1, #8
	str r1, [sp, #0xc]
	add r1, sp, #0
	strb r2, [r1, #0x10]
	mov r2, #7
	strb r2, [r1, #0x11]
	ldr r1, _02236480 ; =0x0000E88C
	ldr r0, [r0, r1]
	add r1, sp, #0
	bl FUN_020145C8
	add sp, #0x14
	pop {pc}
	nop
_02236480: .word 0x0000E88C
	thumb_func_end MOD83_02236450

	thumb_func_start MOD83_02236484
MOD83_02236484: ; 0x02236484
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r0, #0
	bl MOD83_02237464
	add r4, r0, #0
	bl MOD83_02236EA8
	add r3, r0, #0
	add r0, r4, #0
	add r1, sp, #8
	mov r2, #8
	bl FUN_02015D88
	mov r0, #0x4e
	bl ScrStrBufs_new
	add r4, r0, #0
	mov r0, #8
	mov r1, #0x4e
	bl String_ctor
	add r1, sp, #8
	add r6, r0, #0
	bl CopyU16ArrayToString
	mov r1, #1
	str r1, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	mov r3, #0
	bl BufferString
	add r0, r5, #0
	bl MOD83_0223600C
	ldr r0, [r5]
	mov r2, #0x18
	lsl r1, r0, #2
	ldr r0, _02236508 ; =MOD83_0223B2A0
	ldr r0, [r0, r1]
	mov r1, #0x46
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	add r0, #0xc
	sub r1, #0x34
	str r4, [r5, r0]
	add r0, r5, #0
	add r1, r5, r1
	bl MOD83_02234F2C
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl ScrStrBufs_delete
	add r0, r5, #0
	bl MOD83_02236450
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_02236508: .word MOD83_0223B2A0
	thumb_func_end MOD83_02236484

	thumb_func_start MOD83_0223650C
MOD83_0223650C: ; 0x0223650C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0223653C ; =0x00012604
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02236520
	blx r0
	ldr r0, _0223653C ; =0x00012604
	mov r1, #0
	str r1, [r4, r0]
_02236520:
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r0, [r4, #0x20]
	bl DoScheduledBgGpuUpdates
	ldr r3, _02236540 ; =MOD83_027E0000
	ldr r1, _02236544 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_0223653C: .word 0x00012604
_02236540: .word 0x027E0000
_02236544: .word 0x00003FF8
	thumb_func_end MOD83_0223650C

	thumb_func_start MOD83_02236548
MOD83_02236548: ; 0x02236548
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	str r0, [sp]
	ldr r0, [r0, #0x10]
	bl FUN_02022528
	str r0, [sp, #8]
	bl FUN_0202C0B8
	cmp r0, #0
	bne _0223659C
	ldr r0, [sp, #8]
	bl FUN_0202C060
	cmp r0, #0
	bne _0223656E
	add sp, #0xc
	mov r0, #3
	pop {r4, r5, r6, r7, pc}
_0223656E:
	ldr r0, [sp, #8]
	bl FUN_0202C094
	cmp r0, #0
	bne _0223657E
	add sp, #0xc
	mov r0, #4
	pop {r4, r5, r6, r7, pc}
_0223657E:
	bl MOD83_02237448
	add r1, r0, #0
	ldr r0, [sp, #8]
	bl FUN_0202C028
	cmp r0, #0
	bne _02236590
	ldr r0, _022365F8 ; =0x0002A300
_02236590:
	ldr r1, _022365FC ; =0x00015180
	cmp r0, r1
	bge _0223659C
	add sp, #0xc
	mov r0, #2
	pop {r4, r5, r6, r7, pc}
_0223659C:
	mov r6, #0
	str r6, [sp, #4]
	add r7, r6, #0
_022365A2:
	mov r4, #0
	add r5, r4, #0
_022365A6:
	ldr r1, [sp]
	ldr r0, _02236600 ; =0x0000E880
	mov r2, #0
	ldr r0, [r1, r0]
	mov r1, #5
	add r0, r0, #4
	add r0, r0, r7
	add r0, r0, r5
	bl AGB_GetBoxMonData
	cmp r0, #0
	beq _022365C0
	add r6, r6, #1
_022365C0:
	add r4, r4, #1
	add r5, #0x50
	cmp r4, #0x1e
	blt _022365A6
	mov r0, #0x96
	lsl r0, r0, #4
	add r7, r7, r0
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #0xe
	blt _022365A2
	cmp r6, #6
	bge _022365E2
	add sp, #0xc
	mov r0, #5
	pop {r4, r5, r6, r7, pc}
_022365E2:
	ldr r0, [sp, #8]
	bl FUN_0202C000
	cmp r0, #0
	beq _022365F2
	add sp, #0xc
	mov r0, #6
	pop {r4, r5, r6, r7, pc}
_022365F2:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022365F8: .word 0x0002A300
_022365FC: .word 0x00015180
_02236600: .word 0x0000E880
	thumb_func_end MOD83_02236548

	thumb_func_start MOD83_02236604
MOD83_02236604: ; 0x02236604
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	cmp r1, #0
	beq _02236640
	bl MOD83_0223600C
	mov r0, #1
	bl FUN_02002BB8
	ldr r0, _02236660 ; =MOD83_0223B2D8
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	mov r1, #0x46
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	sub r1, #0x34
	mov r2, #1
	add r0, #0x10
	str r2, [r5, r0]
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #0x18
	bl MOD83_02234F2C
	mov r0, #0
	str r0, [r5, #4]
	b _0223665A
_02236640:
	ldr r0, _02236664 ; =0x00000474
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223665A
	mov r0, #0
	bl FUN_02002BB8
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223665A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02236660: .word MOD83_0223B2D8
_02236664: .word 0x00000474
	thumb_func_end MOD83_02236604

	thumb_func_start MOD83_02236668
MOD83_02236668: ; 0x02236668
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #4]
	cmp r1, #0
	beq _022366A4
	bl MOD83_0223600C
	mov r0, #1
	bl FUN_02002BB8
	ldr r0, _022366C8 ; =MOD83_0223B2D8
	lsl r1, r4, #2
	ldr r0, [r0, r1]
	mov r1, #0x46
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	sub r1, #0x34
	mov r2, #1
	add r0, #0x10
	str r2, [r5, r0]
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #0x18
	bl MOD83_02234F2C
	mov r0, #0
	str r0, [r5, #4]
	b _022366C4
_022366A4:
	ldr r0, _022366CC ; =0x00000474
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _022366C4
	add r0, r5, #0
	bl MOD83_02236450
	mov r0, #0
	bl FUN_02002BB8
	mov r0, #1
	pop {r3, r4, r5, pc}
_022366C4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022366C8: .word MOD83_0223B2D8
_022366CC: .word 0x00000474
	thumb_func_end MOD83_02236668

	thumb_func_start MOD83_022366D0
MOD83_022366D0: ; 0x022366D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	ldr r2, [r5, #8]
	mvn r1, r1
	cmp r2, r1
	beq _02236712
	bl MOD83_0223600C
	mov r0, #1
	bl FUN_02002BB8
	mov r1, #0x46
	ldr r0, [r5, #8]
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	add r0, #0x10
	sub r1, #0x34
	str r4, [r5, r0]
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #0x18
	bl MOD83_02234F2C
	mov r0, #0
	mvn r0, r0
	str r0, [r5, #8]
	ldr r0, _02236754 ; =0x000005DC
	bl FUN_020054C8
	b _02236750
_02236712:
	cmp r4, #0
	beq _02236730
	ldr r0, _02236758 ; =0x00000474
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02236750
	mov r0, #0
	bl FUN_02002BB8
	mov r0, #1
	pop {r3, r4, r5, pc}
_02236730:
	ldr r0, _0223675C ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _02236740
	ldr r0, _02236760 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _02236750
_02236740:
	mov r0, #0
	bl FUN_02002BB8
	ldr r0, _02236754 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #1
	pop {r3, r4, r5, pc}
_02236750:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02236754: .word 0x000005DC
_02236758: .word 0x00000474
_0223675C: .word gMain + 0x40
_02236760: .word gMain
	thumb_func_end MOD83_022366D0

	thumb_func_start MOD83_02236764
MOD83_02236764: ; 0x02236764
	push {r3, r4, r5, lr}
	mov r2, #0xa
	add r5, r0, #0
	mov r0, #3
	mov r1, #0x4e
	lsl r2, r2, #0xe
	bl CreateHeap
	ldr r1, _022367F0 ; =0x00012608
	add r0, r5, #0
	mov r2, #0x4e
	bl OverlayManager_CreateAndGetData
	ldr r2, _022367F0 ; =0x00012608
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x4e
	bl FUN_02016B94
	str r0, [r4, #0x20]
	mov r0, #0x4e
	bl FUN_02014590
	ldr r1, _022367F4 ; =0x0000E88C
	str r0, [r4, r1]
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl OverlayManager_GetField18
	ldr r0, [r0, #8]
	str r0, [r4, #0x10]
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x10]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0x18]
	bl Options_GetFrame
	str r0, [r4, #0x1c]
	ldr r1, _022367F8 ; =0x00000496
	mov r0, #9
	mov r2, #1
	bl FUN_0200433C
	bl OS_IsTickAvailable
	cmp r0, #0
	bne _022367DE
	bl OS_InitTick
_022367DE:
	bl MOD83_02239490
	ldr r0, _022367FC ; =0x0000E89C
	add r1, r4, r0
	ldr r0, _02236800 ; =MOD83_0223BB14
	str r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_022367F0: .word 0x00012608
_022367F4: .word 0x0000E88C
_022367F8: .word 0x00000496
_022367FC: .word 0x0000E89C
_02236800: .word MOD83_0223BB14
	thumb_func_end MOD83_02236764

	thumb_func_start MOD83_02236804
MOD83_02236804: ; 0x02236804
	push {r4, r5, r6, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl CTRDG_IsExisting
	bl CTRDG_IsPulledOut
	cmp r0, #1
	beq _02236822
	ldr r0, _02236B3C ; =UNK_02016FA4
	ldr r0, [r0]
	cmp r0, #0
	beq _02236828
_02236822:
	mov r0, #0x4e
	bl FUN_02089F24
_02236828:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r5]
	cmp r0, #0x18
	bhi _02236924
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02236840: ; jump table
	.short _02236872 - _02236840 - 2 ; case 0
	.short _022368BA - _02236840 - 2 ; case 1
	.short _02236900 - _02236840 - 2 ; case 2
	.short _02236914 - _02236840 - 2 ; case 3
	.short _0223694E - _02236840 - 2 ; case 4
	.short _02236966 - _02236840 - 2 ; case 5
	.short _022369BC - _02236840 - 2 ; case 6
	.short _022369CE - _02236840 - 2 ; case 7
	.short _022369EC - _02236840 - 2 ; case 8
	.short _022369FE - _02236840 - 2 ; case 9
	.short _02236A5C - _02236840 - 2 ; case 10
	.short _02236A74 - _02236840 - 2 ; case 11
	.short _02236A88 - _02236840 - 2 ; case 12
	.short _02236AC8 - _02236840 - 2 ; case 13
	.short _02236BF0 - _02236840 - 2 ; case 14
	.short _02236C0A - _02236840 - 2 ; case 15
	.short _02236C26 - _02236840 - 2 ; case 16
	.short _02236C40 - _02236840 - 2 ; case 17
	.short _02236C76 - _02236840 - 2 ; case 18
	.short _02236C9C - _02236840 - 2 ; case 19
	.short _02236D06 - _02236840 - 2 ; case 20
	.short _02236D12 - _02236840 - 2 ; case 21
	.short _02236D54 - _02236840 - 2 ; case 22
	.short _02236D78 - _02236840 - 2 ; case 23
	.short _02236D86 - _02236840 - 2 ; case 24
_02236872:
	bl MOD83_02236E90
	mov r0, #0x4b
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD83_02236E18
	ldr r1, _02236B40 ; =0x000004A8
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _022368AE
	bl MOD83_022371C4
	ldr r1, _02236B44 ; =0x000004AC
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _022368AA
	bl MOD83_0223742C
	ldr r1, _02236B48 ; =0x0000E880
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldrb r2, [r0]
	add r0, r1, #4
	str r2, [r4, r0]
	b _022368AE
_022368AA:
	mov r0, #1
	str r0, [r4, #4]
_022368AE:
	add r0, r4, #0
	bl MOD83_02234CA0
	mov r0, #1
	str r0, [r5]
	b _02236D90
_022368BA:
	add r0, r4, #0
	bl MOD83_02235F3C
	bl MOD83_022350BC
	add r0, r4, #0
	bl MOD83_022350EC
	add r0, r4, #0
	bl MOD83_022351F8
	add r0, r4, #0
	bl MOD83_022357CC
	ldr r0, _02236B4C ; =MOD83_0223650C
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x10
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _022368FA
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xb
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_022368FA:
	mov r0, #2
	str r0, [r5]
	b _02236D90
_02236900:
	add r0, r4, #0
	bl MOD83_02236484
	add r0, r4, #0
	mov r1, #1
	mov r2, #3
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_02236914:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _02236926
	cmp r0, #2
	beq _02236938
_02236924:
	b _02236D90
_02236926:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	.ifdef DIAMOND
	mov r0, #0x22
	.else
	mov r0, #0x23
	.endif
	str r0, [r4, #8]
	mov r0, #4
	str r0, [r5]
	b _02236D90
_02236938:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x18
	add r3, r5, #0
	bl MOD83_02235E34
	b _02236D90
_0223694E:
	add r0, r4, #0
	mov r1, #1
	bl MOD83_022366D0
	cmp r0, #0
	beq _02236976
	add r0, r4, #0
	bl MOD83_02236450
	mov r0, #5
	str r0, [r5]
	b _02236D90
_02236966:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _02236978
	cmp r0, #2
	beq _022369A6
_02236976:
	b _02236D90
_02236978:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	bl MOD83_02236548
	str r0, [r4, #4]
	cmp r0, #0
	beq _0223699E
	sub r0, r0, #3
	cmp r0, #1
	bhi _02236998
	mov r0, #8
	str r0, [r5]
	b _02236D90
_02236998:
	mov r0, #0xb
	str r0, [r5]
	b _02236D90
_0223699E:
	mov r0, #6
	str r0, [r4, #8]
	str r0, [r5]
	b _02236D90
_022369A6:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x18
	add r3, r5, #0
	bl MOD83_02235E34
	b _02236D90
_022369BC:
	add r0, r4, #0
	mov r1, #1
	bl MOD83_022366D0
	cmp r0, #0
	beq _02236A0E
	mov r0, #7
	str r0, [r5]
	b _02236D90
_022369CE:
	ldr r0, _02236B54 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _022369DE
	ldr r0, _02236B58 ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _02236A0E
_022369DE:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xc
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_022369EC:
	ldr r1, [r4, #4]
	add r0, r4, #0
	bl MOD83_02236668
	cmp r0, #0
	beq _02236A0E
	mov r0, #9
	str r0, [r5]
	b _02236D90
_022369FE:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _02236A10
	cmp r0, #2
	beq _02236A46
_02236A0E:
	b _02236D90
_02236A10:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	mov r1, #0x47
	lsl r1, r1, #4
	mov r2, #0
	add r0, r1, #0
	str r2, [r4, r1]
	sub r1, #0x44
	mov r3, #0x28
	sub r0, #0x10
	str r3, [r4, r0]
	add r0, r4, #0
	add r1, r4, r1
	bl MOD83_02234F2C
	ldr r1, _02236B5C ; =0x00000498
	add r0, r4, r1
	sub r1, #0xc6
	bl FUN_0200D858
	ldr r1, _02236B60 ; =0x0000E898
	str r0, [r4, r1]
	mov r0, #0xa
	str r0, [r5]
	b _02236D90
_02236A46:
	ldr r0, _02236B50 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x18
	add r3, r5, #0
	bl MOD83_02235E34
	b _02236D90
_02236A5C:
	add r0, r4, #0
	bl MOD83_02234E40
	ldr r0, _02236B60 ; =0x0000E898
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	mov r0, #7
	str r0, [r4, #4]
	mov r0, #0xb
	str r0, [r5]
	b _02236D90
_02236A74:
	ldr r1, [r4, #4]
	add r0, r4, #0
	bl MOD83_02236604
	cmp r0, #0
	bne _02236A82
	b _02236D90
_02236A82:
	mov r0, #0x16
	str r0, [r5]
	b _02236D90
_02236A88:
	ldr r0, _02236B5C ; =0x00000498
	add r0, r4, r0
	bl MOD83_02236298
	add r0, r4, #0
	bl MOD83_02235FBC
	add r0, r4, #0
	bl MOD83_02235648
	add r0, r4, #0
	bl MOD83_022354F0
	ldr r0, _02236B4C ; =MOD83_0223650C
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add r0, r4, #0
	mov r1, #0
	bl MOD83_02235C4C
	add r0, r4, #0
	mov r1, #1
	mov r2, #0xd
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_02236AC8:
	mov r0, #0x31
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02020988
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _02236B9C
	cmp r6, #0x1e
	bge _02236B92
	add r0, r4, #0
	add r1, r6, #0
	bl MOD83_02235994
	cmp r0, #1
	bne _02236B20
	ldr r2, _02236B48 ; =0x0000E880
	add r0, r4, #0
	ldr r1, [r4, r2]
	add r2, r2, #4
	ldr r3, [r4, r2]
	mov r2, #0x96
	lsl r2, r2, #4
	add r1, r1, #4
	mul r2, r3
	add r2, r1, r2
	mov r1, #0x50
	mul r1, r6
	add r1, r2, r1
	bl MOD83_02235C4C
	mov r0, #0x41
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #6
	bne _02236B9C
	ldr r0, _02236B64 ; =0x0000E888
	mov r1, #0x2d
	str r1, [r4, r0]
	mov r0, #0xf
	str r0, [r5]
	b _02236D90
_02236B20:
	cmp r0, #2
	bne _02236B2E
	add r0, r4, #0
	mov r1, #0
	bl MOD83_02235C4C
	b _02236D90
_02236B2E:
	cmp r0, #4
	bne _02236B68
	mov r0, #8
	str r0, [r4, #8]
	mov r0, #0xe
	str r0, [r5]
	b _02236D90
	.align 2, 0
_02236B3C: .word UNK_02016FA4
_02236B40: .word 0x000004A8
_02236B44: .word 0x000004AC
_02236B48: .word 0x0000E880
_02236B4C: .word MOD83_0223650C
_02236B50: .word 0x0000E88C
_02236B54: .word gMain + 0x40
_02236B58: .word gMain
_02236B5C: .word 0x00000498
_02236B60: .word 0x0000E898
_02236B64: .word 0x0000E888
_02236B68:
	cmp r0, #5
	bne _02236B76
	mov r0, #9
	str r0, [r4, #8]
	mov r0, #0xe
	str r0, [r5]
	b _02236D90
_02236B76:
	cmp r0, #6
	bne _02236B84
	mov r0, #0x26
	str r0, [r4, #8]
	mov r0, #0xe
	str r0, [r5]
	b _02236D90
_02236B84:
	cmp r0, #7
	bne _02236B9C
	mov r0, #0x26
	str r0, [r4, #8]
	mov r0, #0xe
	str r0, [r5]
	b _02236D90
_02236B92:
	beq _02236BDC
	cmp r6, #0x1f
	beq _02236B9E
	cmp r6, #0x20
	beq _02236BBC
_02236B9C:
	b _02236D90
_02236B9E:
	ldr r0, _02236DA0 ; =0x0000E884
	ldr r1, [r4, r0]
	cmp r1, #0
	bne _02236BAA
	mov r1, #0xd
	b _02236BAC
_02236BAA:
	sub r1, r1, #1
_02236BAC:
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD83_022354F0
	ldr r0, _02236DA4 ; =0x000005DC
	bl FUN_020054C8
	b _02236D90
_02236BBC:
	ldr r0, _02236DA0 ; =0x0000E884
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0xe
	bne _02236BCE
	mov r1, #0
	str r1, [r4, r0]
_02236BCE:
	add r0, r4, #0
	bl MOD83_022354F0
	ldr r0, _02236DA4 ; =0x000005DC
	bl FUN_020054C8
	b _02236D90
_02236BDC:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x18
	add r3, r5, #0
	bl MOD83_02235E34
	ldr r0, _02236DA4 ; =0x000005DC
	bl FUN_020054C8
	b _02236D90
_02236BF0:
	add r0, r4, #0
	mov r1, #0
	bl MOD83_022366D0
	cmp r0, #0
	beq _02236C50
	ldr r0, _02236DA8 ; =0x00000498
	add r0, r4, r0
	bl MOD83_02236298
	mov r0, #0xd
	str r0, [r5]
	b _02236D90
_02236C0A:
	ldr r0, _02236DAC ; =0x0000E888
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02236C50
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x10
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_02236C26:
	add r0, r4, #0
	bl MOD83_022360C8
	add r0, r4, #0
	mov r1, #1
	mov r2, #0x11
	add r3, r5, #0
	bl MOD83_02235E04
	add r0, r4, #0
	bl MOD83_02236450
	b _02236D90
_02236C40:
	ldr r0, _02236DB0 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _02236C52
	cmp r0, #2
	beq _02236C60
_02236C50:
	b _02236D90
_02236C52:
	ldr r0, _02236DB0 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	mov r0, #0x12
	str r0, [r5]
	b _02236D90
_02236C60:
	ldr r0, _02236DB0 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x14
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_02236C76:
	mov r1, #0x46
	mov r0, #0xb
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r1, #0x34
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	bl MOD83_02234F2C
	add r0, r4, #0
	bl MOD83_02236450
	ldr r0, _02236DA4 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0x13
	str r0, [r5]
	b _02236D90
_02236C9C:
	ldr r0, _02236DB0 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_0201466C
	cmp r0, #1
	beq _02236CAE
	cmp r0, #2
	beq _02236CF0
	b _02236D90
_02236CAE:
	ldr r0, [r4]
	mov r2, #0
	lsl r1, r0, #2
	ldr r0, _02236DB4 ; =MOD83_0223B288
	ldr r0, [r0, r1]
	mov r1, #0x46
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r1, #0x34
	add r0, r4, #0
	add r1, r4, r1
	bl MOD83_02234F2C
	ldr r0, _02236DB0 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	ldr r0, _02236DB8 ; =0x0000E890
	mov r1, #0
	str r1, [r4, r0]
	ldr r1, _02236DA8 ; =0x00000498
	add r0, r4, r1
	sub r1, #0xc6
	bl FUN_0200D858
	ldr r1, _02236DBC ; =0x0000E898
	str r0, [r4, r1]
	mov r0, #0x15
	str r0, [r5]
	mov r0, #4
	bl SetSoftResetDisableMask
	b _02236D90
_02236CF0:
	ldr r0, _02236DB0 ; =0x0000E88C
	ldr r0, [r4, r0]
	bl FUN_020146C4
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x14
	add r3, r5, #0
	bl MOD83_02235E04
	b _02236D90
_02236D06:
	add r0, r4, #0
	bl MOD83_022362B8
	mov r0, #0xc
	str r0, [r5]
	b _02236D90
_02236D12:
	add r0, r4, #0
	bl MOD83_02234CE8
	add r6, r0, #0
	cmp r6, #0xa
	beq _02236D90
	ldr r0, _02236DBC ; =0x0000E898
	ldr r0, [r4, r0]
	bl FUN_0200DBFC
	ldr r0, _02236DC0 ; =0x0000061B
	bl FUN_020054C8
	cmp r6, #0xb
	bne _02236D34
	.ifdef DIAMOND
	mov r1, #0x1d
	.else
	mov r1, #0x1e
	.endif
	b _02236D36
_02236D34:
	mov r1, #0x24
_02236D36:
	mov r0, #0x46
	lsl r0, r0, #4
	str r1, [r4, r0]
	ldr r1, _02236DC4 ; =0x0000042C
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	bl MOD83_02234F2C
	mov r0, #0x16
	str r0, [r5]
	mov r0, #4
	bl ClearSoftResetDisableMask
	b _02236D90
_02236D54:
	ldr r0, _02236DC8 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _02236D64
	ldr r0, _02236DCC ; =gMain
	ldr r0, [r0, #0x48]
	cmp r0, #0
	beq _02236D90
_02236D64:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x18
	add r3, r5, #0
	bl MOD83_02235E34
	ldr r0, _02236DA4 ; =0x000005DC
	bl FUN_020054C8
	b _02236D90
_02236D78:
	bl FUN_0200E308
	cmp r0, #0
	beq _02236D90
	ldr r0, [r4, #0x24]
	str r0, [r5]
	b _02236D90
_02236D86:
	add r0, r4, #0
	bl MOD83_02236330
	mov r0, #1
	pop {r4, r5, r6, pc}
_02236D90:
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _02236D9A
	bl FUN_0201FDEC
_02236D9A:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02236DA0: .word 0x0000E884
_02236DA4: .word 0x000005DC
_02236DA8: .word 0x00000498
_02236DAC: .word 0x0000E888
_02236DB0: .word 0x0000E88C
_02236DB4: .word MOD83_0223B288
_02236DB8: .word 0x0000E890
_02236DBC: .word 0x0000E898
_02236DC0: .word 0x0000061B
_02236DC4: .word 0x0000042C
_02236DC8: .word gMain + 0x40
_02236DCC: .word gMain
	thumb_func_end MOD83_02236804

	thumb_func_start MOD83_02236DD0
MOD83_02236DD0: ; 0x02236DD0
	push {r4, lr}
	add r4, r0, #0
	bl OverlayManager_GetData
	ldr r0, [r0, #0x20]
	bl FreeToHeap
	ldr r0, _02236DFC ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _02236E00 ; =MOD63_021DBAB8
	bl RegisterMainOverlay
	add r0, r4, #0
	bl OverlayManager_FreeData
	mov r0, #0x4e
	bl DestroyHeap
	mov r0, #0
	bl MOD83_02239450
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_02236DFC: .word SDK_OVERLAY_MODULE_63_ID
_02236E00: .word MOD63_021DBAB8
	thumb_func_end MOD83_02236DD0

	thumb_func_start MOD83_02236E04
MOD83_02236E04: ; 0x02236E04
	push {r3, lr}
	mov r0, #1
	bl CTRDG_IdentifyAgbBackup
	cmp r0, #0
	bne _02236E14
	mov r0, #1
	pop {r3, pc}
_02236E14:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD83_02236E04

	thumb_func_start MOD83_02236E18
MOD83_02236E18: ; 0x02236E18
	push {r3, lr}
	ldr r1, _02236E74 ; =MOD83_0223BB18
	str r0, [r1, #8]
	ldr r0, _02236E78 ; =MOD83_0223B41C
	ldr r0, [r0]
	cmp r0, #0
	beq _02236E2A
	mov r0, #0xc
	pop {r3, pc}
_02236E2A:
	ldr r0, _02236E7C ; =MOD83_0223A5C4
	mov r1, #0x1e
	bl MOD83_02236EB4
	cmp r0, #0
	bne _02236E72
	ldr r0, _02236E78 ; =MOD83_0223B41C
	ldr r0, [r0]
	ldrb r0, [r0, #4]
	cmp r0, #0
	bne _02236E5A
	mov r0, #0x89
	ldr r1, _02236E80 ; =MOD83_0223BB98
	lsl r0, r0, #4
	str r0, [r1, #0x20]
	mov r0, #0xeb
	lsl r0, r0, #6
	str r0, [r1, #0x24]
	ldr r2, _02236E84 ; =0x00001220
	ldr r0, _02236E74 ; =MOD83_0223BB18
	str r2, [r0, #0x68]
	mov r0, #9
	str r0, [r1, #0x30]
	b _02236E64
_02236E5A:
	ldr r0, _02236E88 ; =0x08000100
	ldr r1, _02236E8C ; =MOD83_0223BB30
	mov r2, #0xfc
	bl CTRDG_CpuCopy32
_02236E64:
	bl MOD83_02236E04
	cmp r0, #0
	bne _02236E70
	mov r0, #3
	pop {r3, pc}
_02236E70:
	mov r0, #0
_02236E72:
	pop {r3, pc}
	.align 2, 0
_02236E74: .word MOD83_0223BB18
_02236E78: .word MOD83_0223B41C
_02236E7C: .word MOD83_0223A5C4
_02236E80: .word MOD83_0223BB98
_02236E84: .word 0x00001220
_02236E88: .word 0x08000100
_02236E8C: .word MOD83_0223BB30
	thumb_func_end MOD83_02236E18

	thumb_func_start MOD83_02236E90
MOD83_02236E90: ; 0x02236E90
	ldr r0, _02236E98 ; =MOD83_0223B41C
	mov r1, #0
	str r1, [r0]
	bx lr
	.align 2, 0
_02236E98: .word MOD83_0223B41C
	thumb_func_end MOD83_02236E90

	thumb_func_start MOD83_02236E9C
MOD83_02236E9C: ; 0x02236E9C
	ldr r0, _02236EA4 ; =MOD83_0223B41C
	ldr r0, [r0]
	ldrb r0, [r0, #5]
	bx lr
	.align 2, 0
_02236EA4: .word MOD83_0223B41C
	thumb_func_end MOD83_02236E9C

	thumb_func_start MOD83_02236EA8
MOD83_02236EA8: ; 0x02236EA8
	ldr r0, _02236EB0 ; =MOD83_0223B41C
	ldr r0, [r0]
	ldrh r0, [r0, #6]
	bx lr
	.align 2, 0
_02236EB0: .word MOD83_0223B41C
	thumb_func_end MOD83_02236EA8

	thumb_func_start MOD83_02236EB4
MOD83_02236EB4: ; 0x02236EB4
	push {r3, r4, r5, lr}
	sub sp, #0xc0
	add r5, r0, #0
	add r4, r1, #0
	ldr r0, _02236F60 ; =MOD83_0223B41C
	mov r1, #0
	str r1, [r0]
	bl CTRDG_IsAgbCartridge
	cmp r0, #0
	bne _02236ED0
	add sp, #0xc0
	mov r0, #1
	pop {r3, r4, r5, pc}
_02236ED0:
	bl CTRDG_GetAgbGameCode
	mov r2, #0
	cmp r4, #0
	ble _02236EF4
	add r3, r5, #0
_02236EDC:
	ldr r1, [r3]
	cmp r0, r1
	bne _02236EEC
	lsl r0, r2, #3
	add r1, r5, r0
	ldr r0, _02236F60 ; =MOD83_0223B41C
	str r1, [r0]
	b _02236EF4
_02236EEC:
	add r2, r2, #1
	add r3, #8
	cmp r2, r4
	blt _02236EDC
_02236EF4:
	ldr r0, _02236F60 ; =MOD83_0223B41C
	ldr r0, [r0]
	cmp r0, #0
	bne _02236F02
	add sp, #0xc0
	mov r0, #2
	pop {r3, r4, r5, pc}
_02236F02:
	mov r0, #1
	bl CTRDG_Enable
	add r4, sp, #0
	mov r0, #2
	lsl r0, r0, #0x1a
	add r1, r4, #0
	mov r2, #0xc0
	bl CTRDG_CpuCopy32
	ldr r3, _02236F64 ; =MOD83_0223B424
	mov r2, #0
_02236F1A:
	add r0, r4, r2
	ldrb r1, [r3]
	ldrb r0, [r0, #4]
	cmp r1, r0
	beq _02236F2A
	add sp, #0xc0
	mov r0, #4
	pop {r3, r4, r5, pc}
_02236F2A:
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #0x9c
	blo _02236F1A
	mov r2, #0
	mov r1, #0xa0
_02236F36:
	ldrb r0, [r4, r1]
	add r1, r1, #1
	add r0, r2, r0
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r1, #0xbc
	ble _02236F36
	add r2, #0x19
	neg r0, r2
	lsl r0, r0, #0x18
	add r4, #0xbd
	lsr r1, r0, #0x18
	ldrb r0, [r4]
	cmp r0, r1
	beq _02236F5A
	add sp, #0xc0
	mov r0, #4
	pop {r3, r4, r5, pc}
_02236F5A:
	mov r0, #0
	add sp, #0xc0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02236F60: .word MOD83_0223B41C
_02236F64: .word MOD83_0223B424
	thumb_func_end MOD83_02236EB4

	thumb_func_start MOD83_02236F68
MOD83_02236F68: ; 0x02236F68
	push {r3, r4}
	mov r2, #0
	lsr r4, r1, #2
	add r3, r2, #0
	cmp r4, #0
	ble _02236F84
_02236F74:
	ldr r1, [r0]
	add r0, r0, #4
	add r2, r2, r1
	add r1, r3, #1
	lsl r1, r1, #0x10
	lsr r3, r1, #0x10
	cmp r3, r4
	blt _02236F74
_02236F84:
	lsr r0, r2, #0x10
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, r4}
	bx lr
	thumb_func_end MOD83_02236F68

	thumb_func_start MOD83_02236F98
MOD83_02236F98: ; 0x02236F98
	push {r3, lr}
	lsl r0, r0, #0x10
	mov r3, #1
	add r2, r1, #0
	lsr r0, r0, #0x10
	mov r1, #0
	lsl r3, r3, #0xc
	bl CTRDG_ReadAgbFlash
	pop {r3, pc}
	thumb_func_end MOD83_02236F98

	thumb_func_start MOD83_02236FAC
MOD83_02236FAC: ; 0x02236FAC
	cmp r0, #0
	bne _02236FBA
	ldr r0, _02236FE0 ; =MOD83_0223BB98
	ldr r0, [r0, #0x20]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_02236FBA:
	cmp r0, #4
	bne _02236FCE
	ldr r0, _02236FE0 ; =MOD83_0223BB98
	ldr r1, [r0, #0x24]
	mov r0, #0xba
	lsl r0, r0, #6
	sub r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
_02236FCE:
	cmp r0, #0xd
	bne _02236FD8
	mov r0, #0x7d
	lsl r0, r0, #4
	bx lr
_02236FD8:
	mov r0, #0x3e
	lsl r0, r0, #6
	bx lr
	nop
_02236FE0: .word MOD83_0223BB98
	thumb_func_end MOD83_02236FAC

	thumb_func_start MOD83_02236FE4
MOD83_02236FE4: ; 0x02236FE4
	cmp r0, #0
	bne _02236FF4
	ldr r0, _02237034 ; =MOD83_0223BB18
	ldr r1, [r0, #8]
	mov r0, #1
	lsl r0, r0, #0xc
	add r0, r1, r0
	bx lr
_02236FF4:
	cmp r0, #1
	blt _02237012
	cmp r0, #4
	bgt _02237012
	ldr r1, _02237034 ; =MOD83_0223BB18
	ldr r2, [r1, #8]
	mov r1, #2
	lsl r1, r1, #0xc
	add r2, r2, r1
	sub r1, r0, #1
	mov r0, #0x3e
	lsl r0, r0, #6
	mul r0, r1
	add r0, r2, r0
	bx lr
_02237012:
	cmp r0, #5
	blt _02237030
	cmp r0, #0xe
	bge _02237030
	ldr r1, _02237034 ; =MOD83_0223BB18
	ldr r2, [r1, #8]
	mov r1, #6
	lsl r1, r1, #0xc
	add r2, r2, r1
	sub r1, r0, #5
	mov r0, #0x3e
	lsl r0, r0, #6
	mul r0, r1
	add r0, r2, r0
	bx lr
_02237030:
	mov r0, #0
	bx lr
	.align 2, 0
_02237034: .word MOD83_0223BB18
	thumb_func_end MOD83_02236FE4

	thumb_func_start MOD83_02237038
MOD83_02237038: ; 0x02237038
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r6, #0
	add r5, r1, #0
	str r6, [sp, #4]
	add r1, r2, #0
	str r6, [r1]
	ldr r1, _022370CC ; =MOD83_0223BB18
	add r7, r0, #0
	str r6, [r1, #4]
	mov r1, #0xe
	str r2, [sp]
	add r4, r6, #0
	mul r7, r1
_02237054:
	add r0, r4, #0
	mov r1, #0xe
	bl _s32_div_f
	add r0, r1, r7
	add r1, r5, #0
	bl MOD83_02236F98
	mov r1, #1
	add r0, r5, #0
	lsl r1, r1, #0xc
	bl DC_FlushRange
	ldr r0, _022370D0 ; =0x00000FF8
	ldr r1, [r5, r0]
	ldr r0, _022370D4 ; =0x08012025
	cmp r1, r0
	bne _022370A6
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _022370D8 ; =0x00000FF4
	ldrh r0, [r5, r0]
	bl MOD83_02236FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD83_02236F68
	ldr r1, _022370DC ; =0x00000FF6
	ldrh r1, [r5, r1]
	cmp r1, r0
	bne _022370A6
	ldr r0, _022370E0 ; =0x00000FFC
	ldr r1, [r5, r0]
	ldr r0, [sp]
	str r1, [r0]
	ldr r0, _022370D8 ; =0x00000FF4
	ldrh r1, [r5, r0]
	mov r0, #1
	lsl r0, r1
	orr r6, r0
_022370A6:
	add r4, r4, #1
	cmp r4, #0xe
	blt _02237054
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _022370C4
	ldr r0, _022370E4 ; =0x00003FFF
	cmp r6, r0
	bne _022370BE
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022370BE:
	add sp, #8
	mov r0, #0xff
	pop {r3, r4, r5, r6, r7, pc}
_022370C4:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022370CC: .word MOD83_0223BB18
_022370D0: .word 0x00000FF8
_022370D4: .word 0x08012025
_022370D8: .word 0x00000FF4
_022370DC: .word 0x00000FF6
_022370E0: .word 0x00000FFC
_022370E4: .word 0x00003FFF
	thumb_func_end MOD83_02237038

	thumb_func_start MOD83_022370E8
MOD83_022370E8: ; 0x022370E8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	mov r0, #0
	add r1, r7, #0
	add r2, sp, #4
	bl MOD83_02237038
	add r6, r0, #0
	mov r0, #1
	add r1, r7, #0
	add r2, sp, #0
	bl MOD83_02237038
	cmp r6, #1
	bne _02237160
	cmp r0, #1
	bne _02237160
	mov r1, #0
	ldr r0, [sp, #4]
	mvn r1, r1
	cmp r0, r1
	bne _02237120
	ldr r3, [sp]
	cmp r3, #0
	beq _0223712E
_02237120:
	cmp r0, #0
	bne _02237146
	mov r1, #0
	ldr r3, [sp]
	mvn r1, r1
	cmp r3, r1
	bne _02237146
_0223712E:
	add r2, r0, #1
	add r1, r3, #1
	cmp r2, r1
	bhs _0223713E
	str r3, [r4]
	mov r0, #1
	str r0, [r5]
	b _0223715A
_0223713E:
	str r0, [r4]
	mov r0, #0
	str r0, [r5]
	b _0223715A
_02237146:
	ldr r1, [sp]
	cmp r0, r1
	bhs _02237154
	str r1, [r4]
	mov r0, #1
	str r0, [r5]
	b _0223715A
_02237154:
	str r0, [r4]
	mov r0, #0
	str r0, [r5]
_0223715A:
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02237160:
	cmp r6, #1
	bne _02237184
	cmp r0, #1
	beq _02237184
	ldr r1, [sp, #4]
	cmp r0, #0xff
	str r1, [r4]
	bne _0223717A
	mov r0, #0
	str r0, [r5]
	add sp, #8
	mov r0, #0xff
	pop {r3, r4, r5, r6, r7, pc}
_0223717A:
	mov r0, #0
	str r0, [r5]
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02237184:
	cmp r0, #1
	bne _022371A6
	cmp r6, #1
	beq _022371A6
	ldr r0, [sp]
	cmp r6, #0xff
	str r0, [r4]
	bne _0223719E
	mov r0, #1
	str r0, [r5]
	add sp, #8
	mov r0, #0xff
	pop {r3, r4, r5, r6, r7, pc}
_0223719E:
	mov r0, #1
	add sp, #8
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_022371A6:
	cmp r6, #0
	bne _022371B8
	cmp r0, #0
	bne _022371B8
	mov r0, #0
	str r0, [r4]
	add sp, #8
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_022371B8:
	mov r0, #0
	str r0, [r4]
	str r0, [r5]
	mov r0, #2
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_022370E8

	thumb_func_start MOD83_022371C4
MOD83_022371C4: ; 0x022371C4
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02237278 ; =MOD83_0223BB18
	ldr r1, _0223727C ; =MOD83_0223BB18
	ldr r0, [r0, #8]
	ldr r2, _02237280 ; =MOD83_0223BB28
	bl MOD83_022370E8
	cmp r0, #1
	beq _022371EE
	cmp r0, #0
	beq _022371E6
	cmp r0, #2
	beq _022371EA
	cmp r0, #0xff
	bne _022371EE
	mov r0, #5
	pop {r3, r4, r5, r6, r7, pc}
_022371E6:
	mov r0, #7
	pop {r3, r4, r5, r6, r7, pc}
_022371EA:
	mov r0, #6
	pop {r3, r4, r5, r6, r7, pc}
_022371EE:
	ldr r7, _02237278 ; =MOD83_0223BB18
	ldr r0, [r7]
	cmp r0, #1
	bhi _02237272
	mov r6, #0
	ldr r5, [r7, #8]
	add r4, r6, #0
_022371FC:
	ldr r1, [r7]
	mov r0, #0xe
	mul r0, r1
	add r0, r4, r0
	add r1, r5, #0
	bl MOD83_02236F98
	ldr r0, _02237284 ; =0x00000FF8
	ldr r1, [r5, r0]
	ldr r0, _02237288 ; =0x08012025
	cmp r1, r0
	bne _0223725E
	ldr r0, _0223728C ; =0x00000FF4
	ldrh r0, [r5, r0]
	bl MOD83_02236FAC
	add r1, r0, #0
	add r0, r5, #0
	bl MOD83_02236F68
	ldr r1, _02237290 ; =0x00000FF6
	ldrh r1, [r5, r1]
	cmp r1, r0
	bne _0223725E
	ldr r0, _02237294 ; =0x00000FFC
	mov r1, #1
	ldr r0, [r5, r0]
	str r0, [r7, #0x10]
	ldr r0, _0223728C ; =0x00000FF4
	ldrh r0, [r5, r0]
	lsl r1, r0
	orr r6, r1
	bl MOD83_02236FAC
	str r0, [sp]
	ldr r0, _0223728C ; =0x00000FF4
	ldrh r0, [r5, r0]
	bl MOD83_02236FE4
	add r1, r0, #0
	ldr r2, [sp]
	add r0, r5, #0
	bl MIi_CpuCopy32
	ldr r0, _0223728C ; =0x00000FF4
	ldrh r0, [r5, r0]
	cmp r0, #0
	bne _0223725E
	str r4, [r7, #0xc]
_0223725E:
	add r4, r4, #1
	cmp r4, #0xe
	blt _022371FC
	ldr r0, _02237298 ; =0x00003FFF
	cmp r6, r0
	bne _0223726E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223726E:
	mov r0, #4
	pop {r3, r4, r5, r6, r7, pc}
_02237272:
	mov r0, #6
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02237278: .word MOD83_0223BB18
_0223727C: .word MOD83_0223BB18
_02237280: .word MOD83_0223BB28
_02237284: .word 0x00000FF8
_02237288: .word 0x08012025
_0223728C: .word 0x00000FF4
_02237290: .word 0x00000FF6
_02237294: .word 0x00000FFC
_02237298: .word 0x00003FFF
	thumb_func_end MOD83_022371C4

	thumb_func_start MOD83_0223729C
MOD83_0223729C: ; 0x0223729C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _02237318 ; =MOD83_0223BB18
	mov r2, #1
	ldr r4, [r0, #8]
	str r2, [r0, #0x14]
	mov r0, #0
	add r1, r4, #0
	lsl r2, r2, #0xc
	bl MIi_CpuClear32
	add r0, r5, #0
	bl MOD83_02236FAC
	add r6, r0, #0
	add r0, r5, #0
	bl MOD83_02236FE4
	add r1, r4, #0
	add r2, r6, #0
	bl MIi_CpuCopy32
	ldr r0, _02237318 ; =MOD83_0223BB18
	ldr r1, [r0, #0x10]
	ldr r0, _0223731C ; =0x00000FFC
	str r1, [r4, r0]
	add r1, r0, #0
	sub r1, #8
	strh r5, [r4, r1]
	ldr r1, _02237320 ; =0x08012025
	sub r0, r0, #4
	str r1, [r4, r0]
	add r0, r5, #0
	bl MOD83_02236FAC
	add r1, r0, #0
	add r0, r4, #0
	bl MOD83_02236F68
	ldr r1, _02237324 ; =0x00000FF6
	strh r0, [r4, r1]
	ldr r0, _02237318 ; =MOD83_0223BB18
	mov r1, #0xe
	ldr r0, [r0, #0xc]
	add r0, r5, r0
	add r0, r0, #1
	bl _s32_div_f
	ldr r0, _02237328 ; =MOD83_0223B41C
	ldr r3, _0223732C ; =MOD83_02237330
	ldr r2, [r0, #4]
	mov r0, #0xe
	mul r0, r2
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r4, #0
	mov r2, #4
	bl CTRDG_WriteAndVerifyAgbFlashAsync
	pop {r4, r5, r6, pc}
	nop
_02237318: .word MOD83_0223BB18
_0223731C: .word 0x00000FFC
_02237320: .word 0x08012025
_02237324: .word 0x00000FF6
_02237328: .word MOD83_0223B41C
_0223732C: .word MOD83_02237330
	thumb_func_end MOD83_0223729C

	thumb_func_start MOD83_02237330
MOD83_02237330: ; 0x02237330
	ldr r0, [r0, #8]
	cmp r0, #0
	bne _0223735C
	ldr r1, _02237368 ; =MOD83_0223BB18
	ldr r0, [r1, #4]
	add r0, r0, #1
	str r0, [r1, #4]
	cmp r0, #0xe
	blt _0223734A
	mov r0, #0
	str r0, [r1, #4]
	str r0, [r1, #0x14]
	bx lr
_0223734A:
	cmp r0, #0xd
	bne _02237356
	mov r0, #2
	str r0, [r1, #0x14]
	mov r0, #0
	bx lr
_02237356:
	mov r0, #3
	str r0, [r1, #0x14]
	b _02237362
_0223735C:
	ldr r0, _02237368 ; =MOD83_0223BB18
	mov r1, #4
	str r1, [r0, #0x14]
_02237362:
	mov r0, #0
	bx lr
	nop
_02237368: .word MOD83_0223BB18
	thumb_func_end MOD83_02237330

	thumb_func_start MOD83_0223736C
MOD83_0223736C: ; 0x0223736C
	push {r3, lr}
	ldr r1, _022373AC ; =MOD83_0223BB18
	ldr r0, [r1, #4]
	cmp r0, #0
	bne _02237392
	ldr r1, [r1]
	cmp r1, #1
	bne _02237382
	mov r2, #0
	ldr r1, _022373B0 ; =MOD83_0223B41C
	b _02237386
_02237382:
	ldr r1, _022373B0 ; =MOD83_0223B41C
	mov r2, #1
_02237386:
	str r2, [r1, #4]
	ldr r1, _022373AC ; =MOD83_0223BB18
	ldr r2, [r1, #0x10]
	add r2, r2, #1
	str r2, [r1, #0x10]
	b _02237396
_02237392:
	mov r0, #0
	pop {r3, pc}
_02237396:
	ldr r1, _022373B0 ; =MOD83_0223B41C
	ldr r1, [r1, #4]
	cmp r1, #0
	bge _022373A2
	mov r0, #0
	pop {r3, pc}
_022373A2:
	bl MOD83_0223729C
	mov r0, #1
	pop {r3, pc}
	nop
_022373AC: .word MOD83_0223BB18
_022373B0: .word MOD83_0223B41C
	thumb_func_end MOD83_0223736C

	thumb_func_start MOD83_022373B4
MOD83_022373B4: ; 0x022373B4
	push {r3, lr}
	ldr r1, _022373F0 ; =MOD83_0223BB18
	ldr r0, [r1, #0x14]
	cmp r0, #4
	bhi _022373EC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022373CA: ; jump table
	.short _022373EC - _022373CA - 2 ; case 0
	.short _022373E4 - _022373CA - 2 ; case 1
	.short _022373D4 - _022373CA - 2 ; case 2
	.short _022373DE - _022373CA - 2 ; case 3
	.short _022373E8 - _022373CA - 2 ; case 4
_022373D4:
	ldr r0, [r1, #4]
	bl MOD83_0223729C
	mov r0, #0
	pop {r3, pc}
_022373DE:
	ldr r0, [r1, #4]
	bl MOD83_0223729C
_022373E4:
	mov r0, #0xa
	pop {r3, pc}
_022373E8:
	mov r0, #8
	pop {r3, pc}
_022373EC:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_022373F0: .word MOD83_0223BB18
	thumb_func_end MOD83_022373B4

	thumb_func_start MOD83_022373F4
MOD83_022373F4: ; 0x022373F4
	ldr r0, _02237428 ; =MOD83_0223BB18
	ldr r0, [r0, #0x14]
	cmp r0, #4
	bhi _02237422
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237408: ; jump table
	.short _02237422 - _02237408 - 2 ; case 0
	.short _0223741A - _02237408 - 2 ; case 1
	.short _02237412 - _02237408 - 2 ; case 2
	.short _02237416 - _02237408 - 2 ; case 3
	.short _0223741E - _02237408 - 2 ; case 4
_02237412:
	mov r0, #0xb
	bx lr
_02237416:
	mov r0, #0xa
	bx lr
_0223741A:
	mov r0, #9
	bx lr
_0223741E:
	mov r0, #8
	bx lr
_02237422:
	mov r0, #0
	bx lr
	nop
_02237428: .word MOD83_0223BB18
	thumb_func_end MOD83_022373F4

	thumb_func_start MOD83_0223742C
MOD83_0223742C: ; 0x0223742C
	ldr r0, _02237438 ; =MOD83_0223BB18
	ldr r1, [r0, #8]
	mov r0, #6
	lsl r0, r0, #0xc
	add r0, r1, r0
	bx lr
	.align 2, 0
_02237438: .word MOD83_0223BB18
	thumb_func_end MOD83_0223742C

	thumb_func_start MOD83_0223743C
MOD83_0223743C: ; 0x0223743C
	ldr r3, _02237444 ; =MOD83_02236FE4
	mov r0, #0
	bx r3
	nop
_02237444: .word MOD83_02236FE4
	thumb_func_end MOD83_0223743C

	thumb_func_start MOD83_02237448
MOD83_02237448: ; 0x02237448
	push {r3, lr}
	bl MOD83_0223743C
	ldrb r2, [r0, #0xb]
	ldrb r1, [r0, #0xa]
	lsl r3, r2, #8
	ldrb r2, [r0, #0xd]
	ldrb r0, [r0, #0xc]
	lsl r2, r2, #0x18
	lsl r0, r0, #0x10
	orr r0, r2
	orr r0, r3
	orr r0, r1
	pop {r3, pc}
	thumb_func_end MOD83_02237448

	thumb_func_start MOD83_02237464
MOD83_02237464: ; 0x02237464
	ldr r3, _02237468 ; =MOD83_0223743C
	bx r3
	.align 2, 0
_02237468: .word MOD83_0223743C
	thumb_func_end MOD83_02237464

	thumb_func_start MOD83_0223746C
MOD83_0223746C: ; 0x0223746C
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #0x18
	add r5, r2, #0
	mov r6, #0
	bl _u32_div_f
	cmp r1, #0x17
	bhi _022374C2
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223748C: ; jump table
	.short _022374BC - _0223748C - 2 ; case 0
	.short _022374EE - _0223748C - 2 ; case 1
	.short _0223751E - _0223748C - 2 ; case 2
	.short _0223754E - _0223748C - 2 ; case 3
	.short _0223757E - _0223748C - 2 ; case 4
	.short _022375AE - _0223748C - 2 ; case 5
	.short _022375DE - _0223748C - 2 ; case 6
	.short _02237610 - _0223748C - 2 ; case 7
	.short _02237640 - _0223748C - 2 ; case 8
	.short _02237670 - _0223748C - 2 ; case 9
	.short _022376A0 - _0223748C - 2 ; case 10
	.short _022376D0 - _0223748C - 2 ; case 11
	.short _02237700 - _0223748C - 2 ; case 12
	.short _02237732 - _0223748C - 2 ; case 13
	.short _02237762 - _0223748C - 2 ; case 14
	.short _02237792 - _0223748C - 2 ; case 15
	.short _022377C2 - _0223748C - 2 ; case 16
	.short _022377F2 - _0223748C - 2 ; case 17
	.short _02237822 - _0223748C - 2 ; case 18
	.short _02237854 - _0223748C - 2 ; case 19
	.short _02237884 - _0223748C - 2 ; case 20
	.short _022378B4 - _0223748C - 2 ; case 21
	.short _022378E4 - _0223748C - 2 ; case 22
	.short _02237914 - _0223748C - 2 ; case 23
_022374BC:
	add r4, #0x20
	cmp r5, #3
	bls _022374C4
_022374C2:
	b _02237942
_022374C4:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022374D0: ; jump table
	.short _022374D8 - _022374D0 - 2 ; case 0
	.short _022374DC - _022374D0 - 2 ; case 1
	.short _022374E2 - _022374D0 - 2 ; case 2
	.short _022374E8 - _022374D0 - 2 ; case 3
_022374D8:
	add r6, r4, #0
	b _02237942
_022374DC:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022374E2:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022374E8:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022374EE:
	add r4, #0x20
	cmp r5, #3
	bhi _022375E4
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237500: ; jump table
	.short _02237508 - _02237500 - 2 ; case 0
	.short _0223750C - _02237500 - 2 ; case 1
	.short _02237512 - _02237500 - 2 ; case 2
	.short _02237518 - _02237500 - 2 ; case 3
_02237508:
	add r6, r4, #0
	b _02237942
_0223750C:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237512:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237518:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_0223751E:
	add r4, #0x20
	cmp r5, #3
	bhi _022375E4
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237530: ; jump table
	.short _02237538 - _02237530 - 2 ; case 0
	.short _0223753C - _02237530 - 2 ; case 1
	.short _02237542 - _02237530 - 2 ; case 2
	.short _02237548 - _02237530 - 2 ; case 3
_02237538:
	add r6, r4, #0
	b _02237942
_0223753C:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237542:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237548:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_0223754E:
	add r4, #0x20
	cmp r5, #3
	bhi _022375E4
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237560: ; jump table
	.short _02237568 - _02237560 - 2 ; case 0
	.short _0223756C - _02237560 - 2 ; case 1
	.short _02237572 - _02237560 - 2 ; case 2
	.short _02237578 - _02237560 - 2 ; case 3
_02237568:
	add r6, r4, #0
	b _02237942
_0223756C:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237572:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237578:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_0223757E:
	add r4, #0x20
	cmp r5, #3
	bhi _022375E4
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237590: ; jump table
	.short _02237598 - _02237590 - 2 ; case 0
	.short _0223759C - _02237590 - 2 ; case 1
	.short _022375A2 - _02237590 - 2 ; case 2
	.short _022375A8 - _02237590 - 2 ; case 3
_02237598:
	add r6, r4, #0
	b _02237942
_0223759C:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022375A2:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022375A8:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022375AE:
	add r4, #0x20
	cmp r5, #3
	bhi _022375E4
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022375C0: ; jump table
	.short _022375C8 - _022375C0 - 2 ; case 0
	.short _022375CC - _022375C0 - 2 ; case 1
	.short _022375D2 - _022375C0 - 2 ; case 2
	.short _022375D8 - _022375C0 - 2 ; case 3
_022375C8:
	add r6, r4, #0
	b _02237942
_022375CC:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022375D2:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022375D8:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022375DE:
	add r4, #0x20
	cmp r5, #3
	bls _022375E6
_022375E4:
	b _02237942
_022375E6:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022375F2: ; jump table
	.short _022375FA - _022375F2 - 2 ; case 0
	.short _02237600 - _022375F2 - 2 ; case 1
	.short _02237604 - _022375F2 - 2 ; case 2
	.short _0223760A - _022375F2 - 2 ; case 3
_022375FA:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237600:
	add r6, r4, #0
	b _02237942
_02237604:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_0223760A:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237610:
	add r4, #0x20
	cmp r5, #3
	bhi _02237706
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237622: ; jump table
	.short _0223762A - _02237622 - 2 ; case 0
	.short _02237630 - _02237622 - 2 ; case 1
	.short _02237634 - _02237622 - 2 ; case 2
	.short _0223763A - _02237622 - 2 ; case 3
_0223762A:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237630:
	add r6, r4, #0
	b _02237942
_02237634:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_0223763A:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237640:
	add r4, #0x20
	cmp r5, #3
	bhi _02237706
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237652: ; jump table
	.short _0223765A - _02237652 - 2 ; case 0
	.short _02237660 - _02237652 - 2 ; case 1
	.short _02237664 - _02237652 - 2 ; case 2
	.short _0223766A - _02237652 - 2 ; case 3
_0223765A:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237660:
	add r6, r4, #0
	b _02237942
_02237664:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_0223766A:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237670:
	add r4, #0x20
	cmp r5, #3
	bhi _02237706
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237682: ; jump table
	.short _0223768A - _02237682 - 2 ; case 0
	.short _02237690 - _02237682 - 2 ; case 1
	.short _02237694 - _02237682 - 2 ; case 2
	.short _0223769A - _02237682 - 2 ; case 3
_0223768A:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237690:
	add r6, r4, #0
	b _02237942
_02237694:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_0223769A:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022376A0:
	add r4, #0x20
	cmp r5, #3
	bhi _02237706
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022376B2: ; jump table
	.short _022376BA - _022376B2 - 2 ; case 0
	.short _022376C0 - _022376B2 - 2 ; case 1
	.short _022376C4 - _022376B2 - 2 ; case 2
	.short _022376CA - _022376B2 - 2 ; case 3
_022376BA:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022376C0:
	add r6, r4, #0
	b _02237942
_022376C4:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022376CA:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022376D0:
	add r4, #0x20
	cmp r5, #3
	bhi _02237706
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022376E2: ; jump table
	.short _022376EA - _022376E2 - 2 ; case 0
	.short _022376F0 - _022376E2 - 2 ; case 1
	.short _022376F4 - _022376E2 - 2 ; case 2
	.short _022376FA - _022376E2 - 2 ; case 3
_022376EA:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022376F0:
	add r6, r4, #0
	b _02237942
_022376F4:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022376FA:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237700:
	add r4, #0x20
	cmp r5, #3
	bls _02237708
_02237706:
	b _02237942
_02237708:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237714: ; jump table
	.short _0223771C - _02237714 - 2 ; case 0
	.short _02237722 - _02237714 - 2 ; case 1
	.short _02237728 - _02237714 - 2 ; case 2
	.short _0223772C - _02237714 - 2 ; case 3
_0223771C:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237722:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237728:
	add r6, r4, #0
	b _02237942
_0223772C:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237732:
	add r4, #0x20
	cmp r5, #3
	bhi _02237828
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237744: ; jump table
	.short _0223774C - _02237744 - 2 ; case 0
	.short _02237752 - _02237744 - 2 ; case 1
	.short _02237758 - _02237744 - 2 ; case 2
	.short _0223775C - _02237744 - 2 ; case 3
_0223774C:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237752:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237758:
	add r6, r4, #0
	b _02237942
_0223775C:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237762:
	add r4, #0x20
	cmp r5, #3
	bhi _02237828
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237774: ; jump table
	.short _0223777C - _02237774 - 2 ; case 0
	.short _02237782 - _02237774 - 2 ; case 1
	.short _02237788 - _02237774 - 2 ; case 2
	.short _0223778C - _02237774 - 2 ; case 3
_0223777C:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237782:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237788:
	add r6, r4, #0
	b _02237942
_0223778C:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237792:
	add r4, #0x20
	cmp r5, #3
	bhi _02237828
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022377A4: ; jump table
	.short _022377AC - _022377A4 - 2 ; case 0
	.short _022377B2 - _022377A4 - 2 ; case 1
	.short _022377B8 - _022377A4 - 2 ; case 2
	.short _022377BC - _022377A4 - 2 ; case 3
_022377AC:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022377B2:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022377B8:
	add r6, r4, #0
	b _02237942
_022377BC:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022377C2:
	add r4, #0x20
	cmp r5, #3
	bhi _02237828
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022377D4: ; jump table
	.short _022377DC - _022377D4 - 2 ; case 0
	.short _022377E2 - _022377D4 - 2 ; case 1
	.short _022377E8 - _022377D4 - 2 ; case 2
	.short _022377EC - _022377D4 - 2 ; case 3
_022377DC:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022377E2:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022377E8:
	add r6, r4, #0
	b _02237942
_022377EC:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022377F2:
	add r4, #0x20
	cmp r5, #3
	bhi _02237828
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237804: ; jump table
	.short _0223780C - _02237804 - 2 ; case 0
	.short _02237812 - _02237804 - 2 ; case 1
	.short _02237818 - _02237804 - 2 ; case 2
	.short _0223781C - _02237804 - 2 ; case 3
_0223780C:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237812:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237818:
	add r6, r4, #0
	b _02237942
_0223781C:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237822:
	add r4, #0x20
	cmp r5, #3
	bls _0223782A
_02237828:
	b _02237942
_0223782A:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237836: ; jump table
	.short _0223783E - _02237836 - 2 ; case 0
	.short _02237844 - _02237836 - 2 ; case 1
	.short _0223784A - _02237836 - 2 ; case 2
	.short _02237850 - _02237836 - 2 ; case 3
_0223783E:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237844:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_0223784A:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237850:
	add r6, r4, #0
	b _02237942
_02237854:
	add r4, #0x20
	cmp r5, #3
	bhi _02237942
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237866: ; jump table
	.short _0223786E - _02237866 - 2 ; case 0
	.short _02237874 - _02237866 - 2 ; case 1
	.short _0223787A - _02237866 - 2 ; case 2
	.short _02237880 - _02237866 - 2 ; case 3
_0223786E:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237874:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_0223787A:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237880:
	add r6, r4, #0
	b _02237942
_02237884:
	add r4, #0x20
	cmp r5, #3
	bhi _02237942
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237896: ; jump table
	.short _0223789E - _02237896 - 2 ; case 0
	.short _022378A4 - _02237896 - 2 ; case 1
	.short _022378AA - _02237896 - 2 ; case 2
	.short _022378B0 - _02237896 - 2 ; case 3
_0223789E:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022378A4:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022378AA:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022378B0:
	add r6, r4, #0
	b _02237942
_022378B4:
	add r4, #0x20
	cmp r5, #3
	bhi _02237942
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022378C6: ; jump table
	.short _022378CE - _022378C6 - 2 ; case 0
	.short _022378D4 - _022378C6 - 2 ; case 1
	.short _022378DA - _022378C6 - 2 ; case 2
	.short _022378E0 - _022378C6 - 2 ; case 3
_022378CE:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_022378D4:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_022378DA:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_022378E0:
	add r6, r4, #0
	b _02237942
_022378E4:
	add r4, #0x20
	cmp r5, #3
	bhi _02237942
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022378F6: ; jump table
	.short _022378FE - _022378F6 - 2 ; case 0
	.short _02237904 - _022378F6 - 2 ; case 1
	.short _0223790A - _022378F6 - 2 ; case 2
	.short _02237910 - _022378F6 - 2 ; case 3
_022378FE:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_02237904:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_0223790A:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237910:
	add r6, r4, #0
	b _02237942
_02237914:
	add r4, #0x20
	cmp r5, #3
	bhi _02237942
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237926: ; jump table
	.short _0223792E - _02237926 - 2 ; case 0
	.short _02237934 - _02237926 - 2 ; case 1
	.short _0223793A - _02237926 - 2 ; case 2
	.short _02237940 - _02237926 - 2 ; case 3
_0223792E:
	add r6, r4, #0
	add r6, #0x24
	b _02237942
_02237934:
	add r6, r4, #0
	add r6, #0x18
	b _02237942
_0223793A:
	add r6, r4, #0
	add r6, #0xc
	b _02237942
_02237940:
	add r6, r4, #0
_02237942:
	add r0, r6, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_0223746C

	thumb_func_start MOD83_02237948
MOD83_02237948: ; 0x02237948
	push {r3, r4}
	add r4, r0, #0
	mov r3, #0
	add r4, #0x20
_02237950:
	ldr r2, [r4]
	ldr r1, [r0, #4]
	add r3, r3, #1
	eor r2, r1
	str r2, [r4]
	ldr r1, [r0]
	eor r1, r2
	stmia r4!, {r1}
	cmp r3, #0xc
	blo _02237950
	pop {r3, r4}
	bx lr
	thumb_func_end MOD83_02237948

	thumb_func_start MOD83_02237968
MOD83_02237968: ; 0x02237968
	push {r3, r4}
	add r4, r0, #0
	mov r3, #0
	add r4, #0x20
_02237970:
	ldr r2, [r4]
	ldr r1, [r0]
	add r3, r3, #1
	eor r2, r1
	str r2, [r4]
	ldr r1, [r0, #4]
	eor r1, r2
	stmia r4!, {r1}
	cmp r3, #0xc
	blo _02237970
	pop {r3, r4}
	bx lr
	thumb_func_end MOD83_02237968

	thumb_func_start MOD83_02237988
MOD83_02237988: ; 0x02237988
	push {r3, r4, r5, r6, r7, lr}
	add r1, r0, #0
	mov r4, #0
	ldr r1, [r1]
	str r0, [sp]
	add r2, r4, #0
	bl MOD83_0223746C
	add r5, r0, #0
	ldr r0, [sp]
	mov r2, #1
	add r1, r0, #0
	ldr r1, [r1]
	bl MOD83_0223746C
	add r6, r0, #0
	ldr r0, [sp]
	mov r2, #2
	add r1, r0, #0
	ldr r1, [r1]
	bl MOD83_0223746C
	add r7, r0, #0
	ldr r0, [sp]
	mov r2, #3
	add r1, r0, #0
	ldr r1, [r1]
	bl MOD83_0223746C
	add r1, r4, #0
_022379C4:
	ldrh r2, [r5]
	add r1, r1, #1
	add r5, r5, #2
	add r2, r4, r2
	lsl r2, r2, #0x10
	lsr r4, r2, #0x10
	cmp r1, #6
	blt _022379C4
	mov r2, #0
_022379D6:
	ldrh r1, [r6]
	add r2, r2, #1
	add r6, r6, #2
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r2, #6
	blt _022379D6
	mov r2, #0
_022379E8:
	ldrh r1, [r7]
	add r2, r2, #1
	add r7, r7, #2
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r2, #6
	blt _022379E8
	mov r2, #0
_022379FA:
	ldrh r1, [r0]
	add r2, r2, #1
	add r0, r0, #2
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r2, #6
	blt _022379FA
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD83_02237988

	thumb_func_start AGB_GetBoxMonData
AGB_GetBoxMonData: ; 0x02237A10
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r4, #0
	add r5, r0, #0
	str r1, [sp]
	add r7, r2, #0
	add r6, r4, #0
	str r4, [sp, #0xc]
	str r4, [sp, #8]
	str r4, [sp, #4]
	cmp r1, #0xa
	ble _02237A86
	ldr r1, [r5]
	add r2, r4, #0
	bl MOD83_0223746C
	str r0, [sp, #0xc]
	ldr r1, [r5]
	add r0, r5, #0
	mov r2, #1
	bl MOD83_0223746C
	str r0, [sp, #8]
	ldr r1, [r5]
	add r0, r5, #0
	mov r2, #2
	bl MOD83_0223746C
	str r0, [sp, #4]
	ldr r1, [r5]
	add r0, r5, #0
	mov r2, #3
	bl MOD83_0223746C
	add r6, r0, #0
	add r0, r5, #0
	bl MOD83_02237948
	add r0, r5, #0
	bl MOD83_02237988
	ldrh r1, [r5, #0x1c]
	cmp r0, r1
	beq _02237A86
	ldrb r0, [r5, #0x13]
	mov r1, #1
	bic r0, r1
	mov r1, #1
	orr r0, r1
	strb r0, [r5, #0x13]
	ldrb r1, [r5, #0x13]
	mov r0, #4
	orr r0, r1
	strb r0, [r5, #0x13]
	mov r0, #1
	ldr r1, [r6, #4]
	lsl r0, r0, #0x1e
	orr r0, r1
	str r0, [r6, #4]
_02237A86:
	ldr r0, [sp]
	cmp r0, #0x50
	bls _02237A8E
	b _02237D7C
_02237A8E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237A9A: ; jump table
	.short _02237B3C - _02237A9A - 2 ; case 0
	.short _02237B40 - _02237A9A - 2 ; case 1
	.short _02237B44 - _02237A9A - 2 ; case 2
	.short _02237B64 - _02237A9A - 2 ; case 3
	.short _02237B68 - _02237A9A - 2 ; case 4
	.short _02237B70 - _02237A9A - 2 ; case 5
	.short _02237B78 - _02237A9A - 2 ; case 6
	.short _02237B80 - _02237A9A - 2 ; case 7
	.short _02237B94 - _02237A9A - 2 ; case 8
	.short _02237B98 - _02237A9A - 2 ; case 9
	.short _02237B9C - _02237A9A - 2 ; case 10
	.short _02237BA0 - _02237A9A - 2 ; case 11
	.short _02237BB4 - _02237A9A - 2 ; case 12
	.short _02237BCC - _02237A9A - 2 ; case 13
	.short _02237BCC - _02237A9A - 2 ; case 14
	.short _02237BCC - _02237A9A - 2 ; case 15
	.short _02237BCC - _02237A9A - 2 ; case 16
	.short _02237BD8 - _02237A9A - 2 ; case 17
	.short _02237BD8 - _02237A9A - 2 ; case 18
	.short _02237BD8 - _02237A9A - 2 ; case 19
	.short _02237BD8 - _02237A9A - 2 ; case 20
	.short _02237BC0 - _02237A9A - 2 ; case 21
	.short _02237C08 - _02237A9A - 2 ; case 22
	.short _02237C0E - _02237A9A - 2 ; case 23
	.short _02237C14 - _02237A9A - 2 ; case 24
	.short _02237BBA - _02237A9A - 2 ; case 25
	.short _02237BE4 - _02237A9A - 2 ; case 26
	.short _02237BEA - _02237A9A - 2 ; case 27
	.short _02237BF0 - _02237A9A - 2 ; case 28
	.short _02237BF6 - _02237A9A - 2 ; case 29
	.short _02237BFC - _02237A9A - 2 ; case 30
	.short _02237C02 - _02237A9A - 2 ; case 31
	.short _02237BC6 - _02237A9A - 2 ; case 32
	.short _02237C1A - _02237A9A - 2 ; case 33
	.short _02237C2C - _02237A9A - 2 ; case 34
	.short _02237C34 - _02237A9A - 2 ; case 35
	.short _02237C3C - _02237A9A - 2 ; case 36
	.short _02237C44 - _02237A9A - 2 ; case 37
	.short _02237C4C - _02237A9A - 2 ; case 38
	.short _02237C5A - _02237A9A - 2 ; case 39
	.short _02237C62 - _02237A9A - 2 ; case 40
	.short _02237C6A - _02237A9A - 2 ; case 41
	.short _02237C72 - _02237A9A - 2 ; case 42
	.short _02237C7A - _02237A9A - 2 ; case 43
	.short _02237C82 - _02237A9A - 2 ; case 44
	.short _02237C8A - _02237A9A - 2 ; case 45
	.short _02237C92 - _02237A9A - 2 ; case 46
	.short _02237C20 - _02237A9A - 2 ; case 47
	.short _02237C26 - _02237A9A - 2 ; case 48
	.short _02237C54 - _02237A9A - 2 ; case 49
	.short _02237C98 - _02237A9A - 2 ; case 50
	.short _02237CA0 - _02237A9A - 2 ; case 51
	.short _02237CA8 - _02237A9A - 2 ; case 52
	.short _02237CB0 - _02237A9A - 2 ; case 53
	.short _02237CB8 - _02237A9A - 2 ; case 54
	.short _02237D7C - _02237A9A - 2 ; case 55
	.short _02237D7C - _02237A9A - 2 ; case 56
	.short _02237D7C - _02237A9A - 2 ; case 57
	.short _02237D7C - _02237A9A - 2 ; case 58
	.short _02237D7C - _02237A9A - 2 ; case 59
	.short _02237D7C - _02237A9A - 2 ; case 60
	.short _02237D7C - _02237A9A - 2 ; case 61
	.short _02237D7C - _02237A9A - 2 ; case 62
	.short _02237D7C - _02237A9A - 2 ; case 63
	.short _02237D7C - _02237A9A - 2 ; case 64
	.short _02237D2E - _02237A9A - 2 ; case 65
	.short _02237D4C - _02237A9A - 2 ; case 66
	.short _02237CC0 - _02237A9A - 2 ; case 67
	.short _02237CC8 - _02237A9A - 2 ; case 68
	.short _02237CD0 - _02237A9A - 2 ; case 69
	.short _02237CD8 - _02237A9A - 2 ; case 70
	.short _02237CE0 - _02237A9A - 2 ; case 71
	.short _02237CE8 - _02237A9A - 2 ; case 72
	.short _02237CF0 - _02237A9A - 2 ; case 73
	.short _02237CF8 - _02237A9A - 2 ; case 74
	.short _02237D00 - _02237A9A - 2 ; case 75
	.short _02237D08 - _02237A9A - 2 ; case 76
	.short _02237D10 - _02237A9A - 2 ; case 77
	.short _02237D18 - _02237A9A - 2 ; case 78
	.short _02237D20 - _02237A9A - 2 ; case 79
	.short _02237D28 - _02237A9A - 2 ; case 80
_02237B3C:
	ldr r4, [r5]
	b _02237D7C
_02237B40:
	ldr r4, [r5, #4]
	b _02237D7C
_02237B44:
	ldrb r0, [r5, #0x13]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _02237B50
	mov r4, #0
	b _02237B5E
_02237B50:
	mov r4, #0
_02237B52:
	add r0, r5, r4
	ldrb r0, [r0, #8]
	strb r0, [r7, r4]
	add r4, r4, #1
	cmp r4, #0xa
	blo _02237B52
_02237B5E:
	mov r0, #0xff
	strb r0, [r7, r4]
	b _02237D7C
_02237B64:
	ldrb r4, [r5, #0x12]
	b _02237D7C
_02237B68:
	ldrb r0, [r5, #0x13]
	lsl r0, r0, #0x1f
	lsr r4, r0, #0x1f
	b _02237D7C
_02237B70:
	ldrb r0, [r5, #0x13]
	lsl r0, r0, #0x1e
	lsr r4, r0, #0x1f
	b _02237D7C
_02237B78:
	ldrb r0, [r5, #0x13]
	lsl r0, r0, #0x1d
	lsr r4, r0, #0x1f
	b _02237D7C
_02237B80:
	mov r4, #0
_02237B82:
	add r0, r5, r4
	ldrb r0, [r0, #0x14]
	strb r0, [r7, r4]
	add r4, r4, #1
	cmp r4, #7
	blo _02237B82
	mov r0, #0xff
	strb r0, [r7, r4]
	b _02237D7C
_02237B94:
	ldrb r4, [r5, #0x1b]
	b _02237D7C
_02237B98:
	ldrh r4, [r5, #0x1c]
	b _02237D7C
_02237B9C:
	ldrh r4, [r5, #0x1e]
	b _02237D7C
_02237BA0:
	ldrb r0, [r5, #0x13]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _02237BAE
	mov r4, #0x67
	lsl r4, r4, #2
	b _02237D7C
_02237BAE:
	ldr r0, [sp, #0xc]
	ldrh r4, [r0]
	b _02237D7C
_02237BB4:
	ldr r0, [sp, #0xc]
	ldrh r4, [r0, #2]
	b _02237D7C
_02237BBA:
	ldr r0, [sp, #0xc]
	ldr r4, [r0, #4]
	b _02237D7C
_02237BC0:
	ldr r0, [sp, #0xc]
	ldrb r4, [r0, #8]
	b _02237D7C
_02237BC6:
	ldr r0, [sp, #0xc]
	ldrb r4, [r0, #9]
	b _02237D7C
_02237BCC:
	ldr r0, [sp]
	sub r0, #0xd
	lsl r1, r0, #1
	ldr r0, [sp, #8]
	ldrh r4, [r0, r1]
	b _02237D7C
_02237BD8:
	ldr r1, [sp]
	ldr r0, [sp, #8]
	sub r1, #0x11
	add r0, r0, r1
	ldrb r4, [r0, #8]
	b _02237D7C
_02237BE4:
	ldr r0, [sp, #4]
	ldrb r4, [r0]
	b _02237D7C
_02237BEA:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #1]
	b _02237D7C
_02237BF0:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #2]
	b _02237D7C
_02237BF6:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #3]
	b _02237D7C
_02237BFC:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #4]
	b _02237D7C
_02237C02:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #5]
	b _02237D7C
_02237C08:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #6]
	b _02237D7C
_02237C0E:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #7]
	b _02237D7C
_02237C14:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #8]
	b _02237D7C
_02237C1A:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #9]
	b _02237D7C
_02237C20:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #0xa]
	b _02237D7C
_02237C26:
	ldr r0, [sp, #4]
	ldrb r4, [r0, #0xb]
	b _02237D7C
_02237C2C:
	ldr r0, [r6]
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	b _02237D7C
_02237C34:
	ldr r0, [r6]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x18
	b _02237D7C
_02237C3C:
	ldr r0, [r6]
	lsl r0, r0, #9
	lsr r4, r0, #0x19
	b _02237D7C
_02237C44:
	ldr r0, [r6]
	lsl r0, r0, #5
	lsr r4, r0, #0x1c
	b _02237D7C
_02237C4C:
	ldr r0, [r6]
	lsl r0, r0, #1
	lsr r4, r0, #0x1c
	b _02237D7C
_02237C54:
	ldr r0, [r6]
	lsr r4, r0, #0x1f
	b _02237D7C
_02237C5A:
	ldr r0, [r6, #4]
	lsl r0, r0, #0x1b
	lsr r4, r0, #0x1b
	b _02237D7C
_02237C62:
	ldr r0, [r6, #4]
	lsl r0, r0, #0x16
	lsr r4, r0, #0x1b
	b _02237D7C
_02237C6A:
	ldr r0, [r6, #4]
	lsl r0, r0, #0x11
	lsr r4, r0, #0x1b
	b _02237D7C
_02237C72:
	ldr r0, [r6, #4]
	lsl r0, r0, #0xc
	lsr r4, r0, #0x1b
	b _02237D7C
_02237C7A:
	ldr r0, [r6, #4]
	lsl r0, r0, #7
	lsr r4, r0, #0x1b
	b _02237D7C
_02237C82:
	ldr r0, [r6, #4]
	lsl r0, r0, #2
	lsr r4, r0, #0x1b
	b _02237D7C
_02237C8A:
	ldr r0, [r6, #4]
	lsl r0, r0, #1
	lsr r4, r0, #0x1f
	b _02237D7C
_02237C92:
	ldr r0, [r6, #4]
	lsr r4, r0, #0x1f
	b _02237D7C
_02237C98:
	ldr r0, [r6, #8]
	lsl r0, r0, #0x1d
	lsr r4, r0, #0x1d
	b _02237D7C
_02237CA0:
	ldr r0, [r6, #8]
	lsl r0, r0, #0x1a
	lsr r4, r0, #0x1d
	b _02237D7C
_02237CA8:
	ldr r0, [r6, #8]
	lsl r0, r0, #0x17
	lsr r4, r0, #0x1d
	b _02237D7C
_02237CB0:
	ldr r0, [r6, #8]
	lsl r0, r0, #0x14
	lsr r4, r0, #0x1d
	b _02237D7C
_02237CB8:
	ldr r0, [r6, #8]
	lsl r0, r0, #0x11
	lsr r4, r0, #0x1d
	b _02237D7C
_02237CC0:
	ldr r0, [r6, #8]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CC8:
	ldr r0, [r6, #8]
	lsl r0, r0, #0xf
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CD0:
	ldr r0, [r6, #8]
	lsl r0, r0, #0xe
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CD8:
	ldr r0, [r6, #8]
	lsl r0, r0, #0xd
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CE0:
	ldr r0, [r6, #8]
	lsl r0, r0, #0xc
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CE8:
	ldr r0, [r6, #8]
	lsl r0, r0, #0xb
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CF0:
	ldr r0, [r6, #8]
	lsl r0, r0, #0xa
	lsr r4, r0, #0x1f
	b _02237D7C
_02237CF8:
	ldr r0, [r6, #8]
	lsl r0, r0, #9
	lsr r4, r0, #0x1f
	b _02237D7C
_02237D00:
	ldr r0, [r6, #8]
	lsl r0, r0, #8
	lsr r4, r0, #0x1f
	b _02237D7C
_02237D08:
	ldr r0, [r6, #8]
	lsl r0, r0, #7
	lsr r4, r0, #0x1f
	b _02237D7C
_02237D10:
	ldr r0, [r6, #8]
	lsl r0, r0, #6
	lsr r4, r0, #0x1f
	b _02237D7C
_02237D18:
	ldr r0, [r6, #8]
	lsl r0, r0, #5
	lsr r4, r0, #0x1f
	b _02237D7C
_02237D20:
	ldr r0, [r6, #8]
	lsl r0, r0, #1
	lsr r4, r0, #0x1c
	b _02237D7C
_02237D28:
	ldr r0, [r6, #8]
	lsr r4, r0, #0x1f
	b _02237D7C
_02237D2E:
	ldr r0, [sp, #0xc]
	ldrh r4, [r0]
	cmp r4, #0
	beq _02237D7C
	ldr r0, [r6, #4]
	lsl r0, r0, #1
	lsr r0, r0, #0x1f
	bne _02237D46
	ldrb r0, [r5, #0x13]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _02237D7C
_02237D46:
	mov r4, #0x67
	lsl r4, r4, #2
	b _02237D7C
_02237D4C:
	ldr r4, [r6, #4]
	lsl r0, r4, #2
	lsr r0, r0, #0x1b
	lsl r6, r0, #0x19
	lsl r0, r4, #7
	lsr r0, r0, #0x1b
	lsl r3, r0, #0x14
	lsl r0, r4, #0xc
	lsr r0, r0, #0x1b
	lsl r2, r0, #0xf
	lsl r0, r4, #0x11
	lsr r0, r0, #0x1b
	lsl r1, r0, #0xa
	lsl r0, r4, #0x1b
	lsl r4, r4, #0x16
	lsr r4, r4, #0x1b
	lsr r0, r0, #0x1b
	lsl r4, r4, #5
	orr r0, r4
	orr r0, r1
	orr r0, r2
	orr r0, r3
	add r4, r6, #0
	orr r4, r0
_02237D7C:
	ldr r0, [sp]
	cmp r0, #0xa
	ble _02237D88
	add r0, r5, #0
	bl MOD83_02237968
_02237D88:
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end AGB_GetBoxMonData

	thumb_func_start MOD83_02237D90
MOD83_02237D90: ; 0x02237D90
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	add r4, r0, #0
	add r5, r2, #0
	mov r7, #0
	cmp r6, #0xa
	ble _02237E04
	ldr r1, [r4]
	add r2, r7, #0
	bl MOD83_0223746C
	add r7, r0, #0
	ldr r1, [r4]
	add r0, r4, #0
	mov r2, #1
	bl MOD83_0223746C
	ldr r1, [r4]
	add r0, r4, #0
	mov r2, #2
	bl MOD83_0223746C
	ldr r1, [r4]
	add r0, r4, #0
	mov r2, #3
	bl MOD83_0223746C
	str r0, [sp]
	add r0, r4, #0
	bl MOD83_02237948
	add r0, r4, #0
	bl MOD83_02237988
	ldrh r1, [r4, #0x1c]
	cmp r0, r1
	beq _02237E04
	ldrb r1, [r4, #0x13]
	mov r0, #1
	bic r1, r0
	mov r0, #1
	orr r0, r1
	strb r0, [r4, #0x13]
	ldrb r1, [r4, #0x13]
	mov r0, #4
	orr r0, r1
	strb r0, [r4, #0x13]
	ldr r0, [sp]
	ldr r1, [r0, #4]
	mov r0, #1
	lsl r0, r0, #0x1e
	orr r1, r0
	ldr r0, [sp]
	str r1, [r0, #4]
	add r0, r4, #0
	bl MOD83_02237968
	pop {r3, r4, r5, r6, r7, pc}
_02237E04:
	cmp r6, #0xb
	bhi _02237EA8
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02237E14: ; jump table
	.short _02237EA8 - _02237E14 - 2 ; case 0
	.short _02237EA8 - _02237E14 - 2 ; case 1
	.short _02237E2C - _02237E14 - 2 ; case 2
	.short _02237E3C - _02237E14 - 2 ; case 3
	.short _02237E42 - _02237E14 - 2 ; case 4
	.short _02237E54 - _02237E14 - 2 ; case 5
	.short _02237E66 - _02237E14 - 2 ; case 6
	.short _02237E78 - _02237E14 - 2 ; case 7
	.short _02237EA8 - _02237E14 - 2 ; case 8
	.short _02237EA8 - _02237E14 - 2 ; case 9
	.short _02237EA8 - _02237E14 - 2 ; case 10
	.short _02237E88 - _02237E14 - 2 ; case 11
_02237E2C:
	mov r2, #0
_02237E2E:
	ldrb r1, [r5, r2]
	add r0, r4, r2
	add r2, r2, #1
	strb r1, [r0, #8]
	cmp r2, #0xa
	blt _02237E2E
	b _02237EA8
_02237E3C:
	ldrb r0, [r5]
	strb r0, [r4, #0x12]
	b _02237EA8
_02237E42:
	ldrb r0, [r4, #0x13]
	ldrb r2, [r5]
	mov r1, #1
	bic r0, r1
	mov r1, #1
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x13]
	b _02237EA8
_02237E54:
	ldrb r0, [r4, #0x13]
	mov r1, #2
	bic r0, r1
	ldrb r1, [r5]
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1e
	orr r0, r1
	strb r0, [r4, #0x13]
	b _02237EA8
_02237E66:
	ldrb r0, [r4, #0x13]
	mov r1, #4
	bic r0, r1
	ldrb r1, [r5]
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1d
	orr r0, r1
	strb r0, [r4, #0x13]
	b _02237EA8
_02237E78:
	mov r2, #0
_02237E7A:
	ldrb r1, [r5, r2]
	add r0, r4, r2
	add r2, r2, #1
	strb r1, [r0, #0x14]
	cmp r2, #7
	blt _02237E7A
	b _02237EA8
_02237E88:
	ldrb r0, [r5, #1]
	ldrb r1, [r5]
	lsl r0, r0, #8
	add r0, r1, r0
	strh r0, [r7]
	ldrh r0, [r7]
	ldrb r1, [r4, #0x13]
	cmp r0, #0
	beq _02237EA2
	mov r0, #2
	orr r0, r1
	strb r0, [r4, #0x13]
	b _02237EA8
_02237EA2:
	mov r0, #2
	bic r1, r0
	strb r1, [r4, #0x13]
_02237EA8:
	cmp r6, #0xa
	ble _02237EBA
	add r0, r4, #0
	bl MOD83_02237988
	strh r0, [r4, #0x1c]
	add r0, r4, #0
	bl MOD83_02237968
_02237EBA:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD83_02237D90

	thumb_func_start MOD83_TranslateAgbSpecies
MOD83_TranslateAgbSpecies: ; 0x02237EBC
	ldr r2, _02237ED4 ; =0x00000115
	cmp r0, r2
	blt _02237ED2
	add r1, r2, #0
	add r1, #0x86
	cmp r0, r1
	bgt _02237ED2
	sub r0, r0, r2
	lsl r1, r0, #1
	ldr r0, _02237ED8 ; =MOD83_UpConvertSpeciesLUT
	ldrh r0, [r0, r1]
_02237ED2:
	bx lr
	.align 2, 0
_02237ED4: .word 0x00000115
_02237ED8: .word MOD83_UpConvertSpeciesLUT
	thumb_func_end MOD83_TranslateAgbSpecies

	thumb_func_start MOD83_02237EDC
MOD83_02237EDC: ; 0x02237EDC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0xb
	mov r2, #0
	bl AGB_GetBoxMonData
	bl MOD83_TranslateAgbSpecies
	add r4, r0, #0
	add r0, r5, #0
	mov r1, #0x19
	mov r2, #0
	bl AGB_GetBoxMonData
	add r1, r0, #0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CalcLevelBySpeciesAndExp
	pop {r3, r4, r5, pc}
	thumb_func_end MOD83_02237EDC

	thumb_func_start MOD83_02237F04
MOD83_02237F04: ; 0x02237F04
	push {r4, r5, r6, lr}
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0
	mov r1, #0x2e
	mov r2, #0
	bl AGB_GetBoxMonData
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #0x19 ; BASE_ABILITY_2
	bl GetMonBaseStat
	cmp r0, #0
	beq _02237F5E
	ldr r2, _02237F68 ; =MOD83_SpeciesWithAbilityOverridesList
	mov r4, #0
_02237F32:
	ldrh r1, [r2]
	cmp r5, r1
	bne _02237F42
	add r0, r5, #0
	mov r1, #0x18 ; BASE_ABILITY_1
	bl GetMonBaseStat
	b _02237F4A
_02237F42:
	add r4, r4, #1
	add r2, r2, #2
	cmp r4, #0x5e
	blo _02237F32
_02237F4A:
	cmp r4, #0x5e
	bne _02237F66
	mov r1, #1
	tst r1, r6
	bne _02237F66
	add r0, r5, #0
	mov r1, #0x18 ; BASE_ABILITY_1
	bl GetMonBaseStat
	pop {r4, r5, r6, pc}
_02237F5E:
	add r0, r5, #0
	mov r1, #0x18 ; BASE_ABILITY_1
	bl GetMonBaseStat
_02237F66:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02237F68: .word MOD83_SpeciesWithAbilityOverridesList
	thumb_func_end MOD83_02237F04

	thumb_func_start MigrateBoxMon
MigrateBoxMon: ; 0x02237F6C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r4, r1, #0
	add r6, r0, #0
	add r0, r4, #0
	bl ZeroBoxMonData
	add r0, r4, #0
	bl AcquireBoxMonLock
	mov r1, #0
	str r0, [sp]
	add r0, r6, #0
	add r2, r1, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0xb
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	bl MOD83_TranslateAgbSpecies
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #5
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0xc
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	cmp r0, #0
	beq _02237FCE
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl UpConvertItemId_Gen3to4
	str r0, [sp, #8]
_02237FCE:
	add r0, r4, #0
	mov r1, #6
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #1
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #7
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x19
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #8
	add r2, sp, #8
	bl SetBoxMonData
	mov r0, #0x46
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #9
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	add r1, r4, #0
	bl MOD83_02237F04
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xa
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #8
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xb
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #3
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0xc
	add r2, sp, #4
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x1a
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xd
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x1b
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xe
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x1c
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0xf
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x1d
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x10
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x1e
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x11
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x1f
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x12
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x16
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x13
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x17
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x14
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x18
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x15
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x21
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x16
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x2f
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x17
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x30
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x18
	add r2, sp, #8
	bl SetBoxMonData
	mov r5, #0
	add r7, r5, #0
_0223815E:
	add r1, r5, #0
	add r0, r6, #0
	add r1, #0xd
	mov r2, #0
	bl AGB_GetBoxMonData
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x36
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x15
	mov r2, #0
	bl AGB_GetBoxMonData
	mov r1, #3
	lsl r1, r7
	str r0, [sp, #8]
	and r0, r1
	lsr r0, r7
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x3e
	add r2, sp, #8
	bl SetBoxMonData
	add r1, r5, #0
	add r0, r4, #0
	add r1, #0x42
	mov r2, #0
	bl GetBoxMonData
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x3a
	add r2, sp, #8
	bl SetBoxMonData
	add r5, r5, #1
	add r7, r7, #2
	cmp r5, #4
	blt _0223815E
	add r0, r6, #0
	mov r1, #0x27
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x46
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x28
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x47
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x29
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x48
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x2a
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x49
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x2b
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x4a
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x2c
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x4b
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x2d
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x4c
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x32
	mov r2, #0
	bl AGB_GetBoxMonData
	add r7, r0, #0
	cmp r7, #4
	bgt _02238282
	mov r5, #0
	cmp r7, #0
	ble _02238282
_0223826C:
	mov r0, #1
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x4e
	add r2, sp, #8
	bl SetBoxMonData
	add r5, r5, #1
	cmp r5, r7
	blt _0223826C
_02238282:
	add r0, r6, #0
	mov r1, #0x33
	mov r2, #0
	bl AGB_GetBoxMonData
	add r7, r0, #0
	cmp r7, #4
	bgt _022382AE
	mov r5, #0
	cmp r7, #0
	ble _022382AE
_02238298:
	mov r0, #1
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x52
	add r2, sp, #8
	bl SetBoxMonData
	add r5, r5, #1
	cmp r5, r7
	blt _02238298
_022382AE:
	add r0, r6, #0
	mov r1, #0x34
	mov r2, #0
	bl AGB_GetBoxMonData
	add r7, r0, #0
	cmp r7, #4
	bgt _022382DA
	mov r5, #0
	cmp r7, #0
	ble _022382DA
_022382C4:
	mov r0, #1
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x56
	add r2, sp, #8
	bl SetBoxMonData
	add r5, r5, #1
	cmp r5, r7
	blt _022382C4
_022382DA:
	add r0, r6, #0
	mov r1, #0x35
	mov r2, #0
	bl AGB_GetBoxMonData
	add r7, r0, #0
	cmp r7, #4
	bgt _02238306
	mov r5, #0
	cmp r7, #0
	ble _02238306
_022382F0:
	mov r0, #1
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x5a
	add r2, sp, #8
	bl SetBoxMonData
	add r5, r5, #1
	cmp r5, r7
	blt _022382F0
_02238306:
	add r0, r6, #0
	mov r1, #0x36
	mov r2, #0
	bl AGB_GetBoxMonData
	add r7, r0, #0
	cmp r7, #4
	bgt _02238332
	mov r5, #0
	cmp r7, #0
	ble _02238332
_0223831C:
	mov r0, #1
	add r1, r5, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, #0x5e
	add r2, sp, #8
	bl SetBoxMonData
	add r5, r5, #1
	cmp r5, r7
	blt _0223831C
_02238332:
	add r0, r6, #0
	mov r1, #0x43
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x62
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x44
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x63
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x45
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x64
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x46
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x65
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x47
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x66
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x48
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x67
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x49
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x68
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x4a
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x69
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x4b
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x6a
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x4c
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x6b
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x4d
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x6c
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x4e
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x6d
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x50
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x6e
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r4, #0
	bl GetBoxMonGender
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x6f
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0xc9
	bne _022384AE
	mov r1, #0
	add r0, r6, #0
	add r2, r1, #0
	bl AGB_GetBoxMonData
	add r3, r0, #0
	mov r7, #3
	lsl r0, r7, #8
	and r0, r3
	lsr r1, r0, #6
	lsl r0, r7, #0x18
	and r0, r3
	lsr r5, r0, #0x12
	lsl r0, r7, #0x10
	and r0, r3
	lsr r0, r0, #0xc
	add r2, r3, #0
	orr r0, r5
	orr r0, r1
	and r2, r7
	str r3, [sp, #8]
	orr r0, r2
	mov r1, #0x1c
	bl _u32_div_f
	str r1, [sp, #8]
	add r0, r4, #0
	mov r1, #0x70
	add r2, sp, #8
	bl SetBoxMonData
_022384AE:
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	ldr r1, _022385F0 ; =0x00000182
	cmp r0, r1
	bne _022384FE
	ldr r0, _022385F4 ; =gMain + 0x60
	ldrb r0, [r0, #6]
	cmp r0, #5
	bhi _022384DE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022384D2: ; jump table
	.short _022384DE - _022384D2 - 2 ; case 0
	.short _022384DE - _022384D2 - 2 ; case 1
	.short _022384DE - _022384D2 - 2 ; case 2
	.short _022384F0 - _022384D2 - 2 ; case 3
	.short _022384E4 - _022384D2 - 2 ; case 4
	.short _022384EA - _022384D2 - 2 ; case 5
_022384DE:
	mov r0, #0
	str r0, [sp, #8]
	b _022384F4
_022384E4:
	mov r0, #1
	str r0, [sp, #8]
	b _022384F4
_022384EA:
	mov r0, #2
	str r0, [sp, #8]
	b _022384F4
_022384F0:
	mov r0, #3
	str r0, [sp, #8]
_022384F4:
	add r0, r4, #0
	mov r1, #0x70
	add r2, sp, #8
	bl SetBoxMonData
_022384FE:
	add r0, r6, #0
	mov r1, #2
	add r2, sp, #0x24
	bl AGB_GetBoxMonData
	ldr r3, [sp, #4]
	add r0, sp, #0x24
	add r1, sp, #0xc
	mov r2, #0xc
	bl FUN_02015D88
	add r0, r4, #0
	mov r1, #0x75
	add r2, sp, #0xc
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #3
	mov r2, #0
	bl AGB_GetBoxMonData
	ldr r1, _022385F8 ; =gGameLanguage
	ldrb r1, [r1]
	cmp r1, r0
	beq _0223853E
	mov r0, #1
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x4d
	add r2, sp, #8
	bl SetBoxMonData
_0223853E:
	add r0, r6, #0
	mov r1, #0x25
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x79
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #7
	add r2, sp, #0x24
	bl AGB_GetBoxMonData
	ldr r3, [sp, #4]
	add r0, sp, #0x24
	add r1, sp, #0xc
	mov r2, #8
	bl FUN_02015D88
	add r0, r4, #0
	mov r1, #0x8f
	add r2, sp, #0xc
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x23
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x98
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x22
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x99
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x26
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x9a
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x24
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x9b
	add r2, sp, #8
	bl SetBoxMonData
	add r0, r6, #0
	mov r1, #0x31
	mov r2, #0
	bl AGB_GetBoxMonData
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #0x9c
	add r2, sp, #8
	bl SetBoxMonData
	ldr r1, [sp]
	add r0, r4, #0
	bl ReleaseBoxMonLock
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022385F0: .word 0x00000182
_022385F4: .word gMain + 0x60
_022385F8: .word gGameLanguage
	thumb_func_end MigrateBoxMon

	thumb_func_start MOD83_SetHeapId
MOD83_SetHeapId: ; 0x022385FC
	ldr r1, _02238604 ; =heap_id
	str r0, [r1]
	bx lr
	nop
_02238604: .word heap_id
	thumb_func_end MOD83_SetHeapId

	thumb_func_start MOD83_Alloc
MOD83_Alloc: ; 0x02238608
	add r1, r0, #0
	ldr r0, _02238614 ; =heap_id
	ldr r3, _02238618 ; =AllocFromHeap
	ldr r0, [r0]
	bx r3
	nop
_02238614: .word heap_id
_02238618: .word AllocFromHeap
	thumb_func_end MOD83_Alloc

	thumb_func_start MOD83_0223861C
MOD83_0223861C: ; 0x0223861C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x130
	bl CTRDG_GetAgbGameCode
	lsr r1, r0, #0x18
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	lsr r1, r0, #0x10
	lsl r3, r0, #0x18
	lsr r0, r0, #8
	lsl r0, r0, #0x18
	lsl r1, r1, #0x18
	lsr r0, r0, #8
	lsr r1, r1, #0x10
	orr r0, r3
	orr r0, r1
	add r6, r2, #0
	orr r6, r0
	ldr r0, _022386B0 ; =MOD83_0223B69C
	mov r4, #0
	ldr r0, [r0]
	cmp r0, #0
	bls _022386A6
	ldr r5, _022386B4 ; =MOD83_0223B69C
	add r7, sp, #0x80
_02238652:
	ldr r0, [r5]
	cmp r6, r0
	bne _0223869C
	mov r0, #1
	bl CTRDG_Enable
	mov r0, #0x81
	ldr r2, _022386B8 ; =0x000004A8
	lsl r0, r0, #0x14
	add r1, r7, #0
	bl CTRDG_CpuCopy8
	ldr r0, _022386BC ; =0x08020000
	add r1, sp, #0
	mov r2, #0x80
	bl CTRDG_CpuCopy8
	mov r0, #0
	bl CTRDG_Enable
	ldr r0, _022386C0 ; =MOD83_Alloc
	ldr r1, _022386C4 ; =FreeToHeap
	bl SetCustomAllocatorAndDestructor
	ldr r1, _022386B8 ; =0x000004A8
	ldr r3, _022386C8 ; =MOD83_0223A6B4
	add r0, r7, #0
	add r2, sp, #0
	bl FUN_020910EC
	cmp r0, #0
	beq _0223869C
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x130
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223869C:
	add r5, r5, #4
	ldr r0, [r5]
	add r4, r4, #1
	cmp r4, r0
	blo _02238652
_022386A6:
	mov r0, #0
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x130
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022386B0: .word MOD83_0223B69C
_022386B4: .word MOD83_0223B69C
_022386B8: .word 0x000004A8
_022386BC: .word 0x08020000
_022386C0: .word MOD83_Alloc
_022386C4: .word FreeToHeap
_022386C8: .word MOD83_0223A6B4
	thumb_func_end MOD83_0223861C

	thumb_func_start MOD83_022386CC
MOD83_022386CC: ; 0x022386CC
	push {r3, lr}
	bl CTRDG_Init
	bl CTRDG_IsAgbCartridge
	cmp r0, #0
	bne _022386DE
	mov r0, #0
	pop {r3, pc}
_022386DE:
	bl CTRDG_GetAgbMakerCode
	ldr r1, _022386FC ; =0x00003130 "01"
	cmp r0, r1
	beq _022386EC
	mov r0, #0
	pop {r3, pc}
_022386EC:
	bl MOD83_0223861C
	cmp r0, #0
	beq _022386F8
	mov r0, #1
	pop {r3, pc}
_022386F8:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_022386FC: .word 0x00003130
	thumb_func_end MOD83_022386CC

	thumb_func_start MOD83_02238700
MOD83_02238700: ; 0x02238700
	push {r3, lr}
	bl MOD83_022386CC
	cmp r0, #0
	bne _0223870E
	mov r0, #0
	pop {r3, pc}
_0223870E:
	mov r0, #1
	bl CTRDG_Enable
	mov r0, #0x81
	lsl r0, r0, #0x14
	add r1, sp, #0
	bl CTRDG_Read32
	mov r0, #0
	bl CTRDG_Enable
	ldr r0, [sp]
	pop {r3, pc}
	thumb_func_end MOD83_02238700

	thumb_func_start MOD83_02238728
MOD83_02238728: ; 0x02238728
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD83_022386CC
	cmp r0, #0
	bne _0223873A
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223873A:
	cmp r4, #0
	bne _02238744
	bl MOD83_02238700
	add r4, r0, #0
_02238744:
	mov r0, #1
	bl CTRDG_Enable
	ldr r0, _0223876C ; =0x08100100
	add r1, r5, #0
	add r2, r4, #0
	bl CTRDG_CpuCopy16
	add r4, r0, #0
	mov r0, #0
	bl CTRDG_Enable
	bl CTRDG_IsExisting
	cmp r0, #0
	bne _02238768
	mov r0, #0
	pop {r3, r4, r5, pc}
_02238768:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223876C: .word 0x08100100
	thumb_func_end MOD83_02238728

	thumb_func_start MOD83_02238770
MOD83_02238770: ; 0x02238770
	push {r3, r4, r5, r6}
	add r4, r0, #0
	mov r0, #0
	ldr r6, _02238798 ; =MOD83_0223BC30
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	mov r5, #0x75
_02238780:
	stmia r6!, {r0, r1, r2, r3}
	stmia r6!, {r0, r1, r2, r3}
	sub r5, r5, #1
	bne _02238780
	str r0, [r6]
	ldr r0, _0223879C ; =MOD83_0223BC30
	mov r1, #1
	str r1, [r0]
	str r4, [r0, #4]
	pop {r3, r4, r5, r6}
	bx lr
	nop
_02238798: .word MOD83_0223BC30
_0223879C: .word MOD83_0223BC30
	thumb_func_end MOD83_02238770

	thumb_func_start MOD83_022387A0
MOD83_022387A0: ; 0x022387A0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	add r6, r1, #0
	mov r0, #3
	add r2, r3, #0
	bl CreateHeap
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl OverlayManager_CreateAndGetData
	mov r1, #0
	add r2, r4, #0
	add r5, r0, #0
	bl memset
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD83_022387A0

	thumb_func_start MOD83_022387D8
MOD83_022387D8: ; 0x022387D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	ldr r5, _0223885C ; =MOD83_0223A760
	add r6, r3, #0
	add r7, r0, #0
	add r4, r1, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	cmp r2, #4
	str r0, [r3]
	add r0, sp, #0
	strb r2, [r0, #0x10]
	bhi _02238832
	add r0, r2, r2
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223880A: ; jump table
	.short _02238832 - _0223880A - 2 ; case 0
	.short _02238814 - _0223880A - 2 ; case 1
	.short _0223881C - _0223880A - 2 ; case 2
	.short _02238824 - _0223880A - 2 ; case 3
	.short _0223882C - _0223880A - 2 ; case 4
_02238814:
	mov r0, #2
	lsl r0, r0, #0xa
	str r0, [sp, #8]
	b _02238832
_0223881C:
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	b _02238832
_02238824:
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	b _02238832
_0223882C:
	mov r0, #2
	lsl r0, r0, #0xc
	str r0, [sp, #8]
_02238832:
	lsr r1, r6, #0xb
	add r0, sp, #0
	strb r1, [r0, #0x12]
	ldr r1, [sp, #0x30]
	add r2, sp, #0
	lsr r1, r1, #0xe
	strb r1, [r0, #0x13]
	lsl r1, r4, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	mov r3, #0
	bl FUN_02016C18
	lsl r1, r4, #0x18
	add r0, r7, #0
	lsr r1, r1, #0x18
	bl FUN_02018744
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_0223885C: .word MOD83_0223A760
	thumb_func_end MOD83_022387D8

	thumb_func_start MOD83_02238860
MOD83_02238860: ; 0x02238860
	ldr r1, _02238868 ; =MOD83_0223BC30
	str r0, [r1, #0xc]
	bx lr
	nop
_02238868: .word MOD83_0223BC30
	thumb_func_end MOD83_02238860

	thumb_func_start MOD83_0223886C
MOD83_0223886C: ; 0x0223886C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp, #0xc]
	ldr r0, _022388C0 ; =MOD83_0223BC30
	add r5, r1, #0
	ldr r0, [r0, #0xc]
	add r4, r2, #0
	add r6, r3, #0
	ldr r7, _022388C4 ; =MOD83_0223BC30
	cmp r0, #0
	bne _0223889C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r7, #4]
	ldr r1, [sp, #0xc]
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _022388B4
_0223889C:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r7, #4]
	ldr r1, [sp, #0xc]
	str r0, [sp, #8]
	ldr r3, _022388C8 ; =0x00007FFF
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
_022388B4:
	cmp r4, #0
	beq _022388BA
	str r6, [r4]
_022388BA:
	str r5, [r7, #8]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022388C0: .word MOD83_0223BC30
_022388C4: .word MOD83_0223BC30
_022388C8: .word 0x00007FFF
	thumb_func_end MOD83_0223886C

	thumb_func_start MOD83_022388CC
MOD83_022388CC: ; 0x022388CC
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r5, _022388E0 ; =MOD83_0223BC30
	bl FUN_0200E308
	cmp r0, #0
	beq _022388DE
	ldr r0, [r5, #8]
	str r0, [r4]
_022388DE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022388E0: .word MOD83_0223BC30
	thumb_func_end MOD83_022388CC

	thumb_func_start MOD83_022388E4
MOD83_022388E4: ; 0x022388E4
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r2, #0
	mov r1, #0
	mov r2, #0x54
	add r5, r0, #0
	add r7, r3, #0
	bl memset
	mov r0, #1
	str r0, [r5, #4]
	str r0, [r5, #8]
	sub r0, r0, #2
	str r0, [r5, #0x4c]
	str r4, [r5, #0x10]
	str r6, [r5, #0x30]
	ldr r0, [sp, #0x18]
	str r7, [r5, #0x34]
	str r0, [r5, #0x38]
	ldr r0, [sp, #0x1c]
	mov r2, #0
	str r0, [r5, #0x3c]
	str r2, [r5, #0x2c]
	ldr r0, _02238930 ; =0x0001020F
	str r2, [r5, #0x40]
	str r0, [r5, #0x44]
	add r0, r5, #0
	mov r1, #0xf
	add r0, #0x48
	strb r1, [r0]
	str r2, [r5]
	str r2, [r5, #0x24]
	str r2, [r5, #0x20]
	str r2, [r5, #0x14]
	mov r0, #0xff
	str r0, [r5, #0x50]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02238930: .word 0x0001020F
	thumb_func_end MOD83_022388E4

	thumb_func_start MOD83_02238934
MOD83_02238934: ; 0x02238934
	str r1, [r0, #0x18]
	str r2, [r0, #0x1c]
	str r3, [r0, #0x28]
	bx lr
	thumb_func_end MOD83_02238934

	thumb_func_start MOD83_0223893C
MOD83_0223893C: ; 0x0223893C
	str r1, [r0]
	str r2, [r0, #0x40]
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0223893C

	thumb_func_start MOD83_02238944
MOD83_02238944: ; 0x02238944
	str r1, [r0, #0x20]
	str r2, [r0, #0x24]
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02238944

	thumb_func_start MOD83_0223894C
MOD83_0223894C: ; 0x0223894C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0
	mvn r0, r0
	ldr r4, _02238A34 ; =MOD83_0223BC30
	cmp r1, r0
	beq _02238A2A
	ldr r0, [r5, #0x4c]
	cmp r0, r1
	beq _02238A2A
	str r1, [r5, #0x4c]
	ldr r0, [r5, #8]
	cmp r0, #1
	bne _02238976
	add r1, r5, #0
	add r1, #0x48
	ldrb r1, [r1]
	ldr r0, [r5, #0x10]
	bl FillWindowPixelBuffer
_02238976:
	mov r0, #0
	ldr r1, [r5, #0x4c]
	mvn r0, r0
	cmp r1, r0
	beq _02238A2A
	ldr r2, [r5, #0x34]
	ldr r3, [r4, #4]
	mov r0, #1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	ldr r6, [r5, #0x14]
	str r0, [sp, #0x10]
	cmp r6, #0
	bne _0223899C
	ldr r0, [r4, #4]
	bl ScrStrBufs_new
	add r6, r0, #0
_0223899C:
	ldr r1, [sp, #0x10]
	ldr r2, [r5, #0x4c]
	ldr r3, [r4, #4]
	add r0, r6, #0
	bl ReadMsgData_ExpandPlaceholders
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _022389D0
	ldr r0, [r5, #0x24]
	add r2, r4, #0
	str r0, [sp]
	ldr r0, [r5, #0x50]
	str r0, [sp, #4]
	ldr r0, [r5, #0x44]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x40]
	ldr r3, [r5, #0x20]
	bl AddTextPrinterParameterized2
	add r7, r0, #0
	b _02238A12
_022389D0:
	ldr r0, [r5, #0x40]
	mov r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl GetFontAttribute
	add r2, r0, #0
	ldr r0, [r5, #0x40]
	add r1, r4, #0
	bl FUN_02002E14
	add r7, r0, #0
	ldr r0, [r5, #0x10]
	bl GetWindowWidth
	lsl r0, r0, #3
	sub r3, r0, r7
	ldr r0, [r5, #0x24]
	add r2, r4, #0
	str r0, [sp]
	ldr r0, [r5, #0x50]
	str r0, [sp, #4]
	ldr r0, [r5, #0x44]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x40]
	bl AddTextPrinterParameterized2
	add r7, r0, #0
	mov r0, #0
	str r0, [r5, #0xc]
_02238A12:
	add r0, r4, #0
	bl String_dtor
	ldr r0, [r5, #0x14]
	cmp r0, #0
	bne _02238A24
	add r0, r6, #0
	bl ScrStrBufs_delete
_02238A24:
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
_02238A2A:
	mov r0, #0xff
	str r0, [r5, #0x50]
	add r0, r7, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238A34: .word MOD83_0223BC30
	thumb_func_end MOD83_0223894C

	thumb_func_start MOD83_02238A38
MOD83_02238A38: ; 0x02238A38
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r1, #0
	ldr r1, [r4, #0x10]
	add r6, r2, #0
	ldr r2, [r1]
	add r5, r3, #0
	cmp r2, #0
	bne _02238A8A
	lsl r2, r5, #0x18
	lsr r2, r2, #0x18
	str r2, [sp]
	ldr r2, [r4, #0x18]
	lsl r3, r6, #0x18
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #4]
	ldr r2, [r4, #0x1c]
	lsr r3, r3, #0x18
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #8]
	ldr r2, [r4, #0x30]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0xc]
	ldr r2, [r4, #0x28]
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	str r2, [sp, #0x10]
	ldr r2, [r4, #0x2c]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	bl AddWindowParameterized
	ldr r1, [sp, #0x28]
	add r0, r4, #0
	bl MOD83_0223894C
	add r5, r0, #0
	b _02238AB8
_02238A8A:
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _02238A9C
	add r0, r1, #0
	lsl r1, r6, #0x18
	lsr r1, r1, #0x18
	bl MoveWindowX
_02238A9C:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _02238AAE
	lsl r1, r5, #0x18
	ldr r0, [r4, #0x10]
	lsr r1, r1, #0x18
	bl MoveWindowY
_02238AAE:
	ldr r1, [sp, #0x28]
	add r0, r4, #0
	bl MOD83_0223894C
	add r5, r0, #0
_02238AB8:
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _02238AEC
	ldr r0, [r4]
	cmp r0, #0
	ldr r0, [r4, #0x10]
	bne _02238ADA
	ldr r2, [r4, #0x38]
	ldr r3, [r4, #0x3c]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	mov r1, #0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_0200CCA4
	b _02238AEC
_02238ADA:
	ldr r2, [r4, #0x38]
	ldr r3, [r4, #0x3c]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	mov r1, #0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_0200D0BC
_02238AEC:
	add r0, r5, #0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD83_02238A38

	thumb_func_start MOD83_02238AF4
MOD83_02238AF4: ; 0x02238AF4
	ldr r1, [r0, #0x18]
	ldr r0, [r0, #0x1c]
	mul r0, r1
	bx lr
	thumb_func_end MOD83_02238AF4

	thumb_func_start MOD83_02238AFC
MOD83_02238AFC: ; 0x02238AFC
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _02238B30 ; =MOD83_0223A734
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, _02238B34 ; =MOD83_0223BC30
	ldr r0, [r0, #4]
	str r0, [sp, #0xc]
	add r0, r2, #0
	bl FUN_0201D040
	ldr r1, _02238B34 ; =MOD83_0223BC30
	mov r0, #0x14
	ldr r1, [r1, #4]
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02238B30: .word MOD83_0223A734
_02238B34: .word MOD83_0223BC30
	thumb_func_end MOD83_02238AFC

	thumb_func_start MOD83_02238B38
MOD83_02238B38: ; 0x02238B38
	ldr r0, _02238B48 ; =MOD83_0223BC30
	ldr r0, [r0, #0x30]
	cmp r0, #0
	beq _02238B44
	mov r0, #1
	bx lr
_02238B44:
	mov r0, #0
	bx lr
	.align 2, 0
_02238B48: .word MOD83_0223BC30
	thumb_func_end MOD83_02238B38

	thumb_func_start MOD83_02238B4C
MOD83_02238B4C: ; 0x02238B4C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r6, _02238BB4 ; =MOD83_0223BC30
	bl NNS_G2dInitOamManagerModule
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	ldr r2, _02238BB8 ; =MOD83_0223BC30
	str r3, [sp, #0xc]
	ldr r2, [r2, #4]
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	ldr r2, _02238BB8 ; =MOD83_0223BC30
	ldr r1, _02238BBC ; =MOD83_0223BC64
	ldr r2, [r2, #4]
	mov r0, #0x46
	bl FUN_02008C9C
	ldr r1, _02238BB8 ; =MOD83_0223BC30
	mov r2, #1
	str r0, [r1, #0x30]
	ldr r0, _02238BBC ; =MOD83_0223BC64
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r1, #3
	mov r7, #0x57
	ldr r0, _02238BC0 ; =MOD83_0223BE30
	lsl r1, r1, #0x12
	str r1, [r0, #0xc]
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_02238B9C:
	ldr r2, [r6, #4]
	mov r0, #3
	add r1, r4, #0
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02238B9C
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02238BB4: .word MOD83_0223BC30
_02238BB8: .word MOD83_0223BC30
_02238BBC: .word MOD83_0223BC64
_02238BC0: .word MOD83_0223BE30
	thumb_func_end MOD83_02238B4C

	thumb_func_start MOD83_02238BC4
MOD83_02238BC4: ; 0x02238BC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	ldr r4, [sp, #0x54]
	add r6, r0, #0
	mov ip, r1
	str r2, [sp, #0x2c]
	str r3, [sp, #0x30]
	ldr r5, _02238D30 ; =MOD83_0223BC30
	cmp r4, #0
	bne _02238BDC
	mov r7, #1
	b _02238BDE
_02238BDC:
	mov r7, #2
_02238BDE:
	mov r0, #1
	str r0, [sp, #0x34]
	cmp r6, #0x10
	bne _02238BEA
	mov r0, #0
	str r0, [sp, #0x34]
_02238BEA:
	mov r1, #0
	mvn r1, r1
	mov r0, ip
	cmp r0, r1
	beq _02238C18
	str r4, [sp]
	str r7, [sp, #4]
	ldr r0, [r5, #4]
	ldr r3, [sp, #0x34]
	str r0, [sp, #8]
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	mov r2, ip
	bl FUN_02008F34
	mov r1, #0x18
	mul r1, r4
	add r2, r5, r1
	mov r1, #0x5d
	lsl r1, r1, #2
	str r0, [r2, r1]
_02238C18:
	mov r1, #0
	ldr r0, [sp, #0x2c]
	mvn r1, r1
	cmp r0, r1
	beq _02238C4A
	str r4, [sp]
	str r7, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	ldr r2, [sp, #0x2c]
	str r0, [sp, #0xc]
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, r6, #0
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0x18
	mul r1, r4
	add r2, r5, r1
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r2, r1]
_02238C4A:
	mov r1, #0
	ldr r0, [sp, #0x30]
	mvn r1, r1
	cmp r0, r1
	beq _02238C7A
	str r4, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	ldr r2, [sp, #0x30]
	str r0, [sp, #8]
	mov r0, #0x59
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r3, [sp, #0x34]
	add r1, r6, #0
	bl FUN_020090AC
	mov r1, #0x18
	mul r1, r4
	add r2, r5, r1
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r2, r1]
_02238C7A:
	mov r0, #0
	ldr r2, [sp, #0x50]
	mvn r0, r0
	cmp r2, r0
	beq _02238CA8
	str r4, [sp]
	mov r0, #3
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	ldr r3, [sp, #0x34]
	str r0, [sp, #8]
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_020090AC
	mov r1, #0x18
	add r2, r4, #0
	mul r2, r1
	add r2, r5, r2
	lsl r1, r1, #4
	str r0, [r2, r1]
_02238CA8:
	mov r0, #0x18
	add r6, r4, #0
	mul r6, r0
	mov r0, #0x5d
	add r1, r5, r6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009A50
	mov r0, #0x5e
	add r1, r5, r6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009CF0
	mov r0, #0
	mov r2, #0x57
	str r4, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	add r3, r4, #0
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	str r1, [sp, #0x1c]
	add r1, r2, #0
	add r1, #0xc
	ldr r1, [r5, r1]
	add r2, #0x48
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	mov r0, #0x24
	add r1, r5, r2
	mul r0, r4
	add r0, r1, r0
	add r1, r4, #0
	add r2, r4, #0
	bl FUN_02008AA4
	cmp r4, #0
	bne _02238D1A
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	b _02238D22
_02238D1A:
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
_02238D22:
	ldr r0, _02238D34 ; =MOD83_02238F00
	mov r1, #0
	bl Main_SetVBlankIntrCB
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02238D30: .word MOD83_0223BC30
_02238D34: .word MOD83_02238F00
	thumb_func_end MOD83_02238BC4

	thumb_func_start MOD83_02238D38
MOD83_02238D38: ; 0x02238D38
	push {r4, lr}
	add r2, r0, #0
	add r4, r1, #0
	add r1, r2, #0
	ldr r0, _02238D50 ; =MOD83_0223BC64
	add r2, r4, #0
	bl FUN_02008D24
	ldr r0, _02238D54 ; =MOD83_0223BE30
	str r4, [r0, #0xc]
	pop {r4, pc}
	nop
_02238D50: .word MOD83_0223BC64
_02238D54: .word MOD83_0223BE30
	thumb_func_end MOD83_02238D38

	thumb_func_start MOD83_02238D58
MOD83_02238D58: ; 0x02238D58
	push {r4, lr}
	ldr r0, _02238DB4 ; =MOD83_0223BE30
	ldr r4, _02238DB8 ; =MOD83_0223BC30
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02238DA6
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	bne _02238DA2
	sub r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02020128
	cmp r0, #0
	bne _02238D86
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
_02238D86:
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	mov r1, #6
	ldr r2, [r0, #4]
	lsl r1, r1, #0x12
	cmp r2, r1
	bge _02238DA6
	lsr r1, r1, #7
	add r1, r2, r1
	str r1, [r0, #4]
	b _02238DA6
_02238DA2:
	sub r1, r1, #1
	str r1, [r4, r0]
_02238DA6:
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _02238DB0
	bl FUN_0201FDEC
_02238DB0:
	pop {r4, pc}
	nop
_02238DB4: .word MOD83_0223BE30
_02238DB8: .word MOD83_0223BC30
	thumb_func_end MOD83_02238D58

	thumb_func_start MOD83_02238DBC
MOD83_02238DBC: ; 0x02238DBC
	push {r3, r4, r5, lr}
	sub sp, #0x30
	add r4, r1, #0
	ldr r1, _02238E44 ; =MOD83_0223BC30
	bne _02238E1E
	ldr r4, [r1, #0x30]
	lsl r2, r2, #0xc
	str r4, [sp]
	mov r4, #0x69
	lsl r4, r4, #2
	add r5, r1, r4
	mov r4, #0x24
	mul r4, r0
	add r4, r5, r4
	str r4, [sp, #4]
	mov r4, #1
	lsl r4, r4, #0xc
	mov r5, #0
	str r5, [sp, #0x10]
	str r4, [sp, #0x14]
	str r4, [sp, #0x18]
	str r4, [sp, #0x1c]
	add r4, sp, #0
	strh r5, [r4, #0x20]
	str r2, [sp, #8]
	lsl r2, r3, #0xc
	str r2, [sp, #0xc]
	mov r2, #0xa
	str r2, [sp, #0x24]
	cmp r0, #0
	bne _02238DFE
	mov r2, #1
	b _02238E00
_02238DFE:
	mov r2, #2
_02238E00:
	ldr r0, [r1, #4]
	str r2, [sp, #0x28]
	str r0, [sp, #0x2c]
	cmp r2, #2
	bne _02238E16
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r2, [sp, #0xc]
	ldr r0, [r1, r0]
	add r0, r2, r0
	str r0, [sp, #0xc]
_02238E16:
	add r0, sp, #0
	bl FUN_0201FE94
	add r4, r0, #0
_02238E1E:
	add r0, r4, #0
	mov r1, #1
	bl FUN_020200BC
	add r0, r4, #0
	mov r1, #0
	bl FUN_02020238
	ldr r1, [sp, #0x40]
	add r0, r4, #0
	bl FUN_02020130
	add r0, r4, #0
	mov r1, #1
	bl FUN_020200A0
	add r0, r4, #0
	add sp, #0x30
	pop {r3, r4, r5, pc}
	.align 2, 0
_02238E44: .word MOD83_0223BC30
	thumb_func_end MOD83_02238DBC

	thumb_func_start MOD83_02238E48
MOD83_02238E48: ; 0x02238E48
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02238EE8 ; =MOD83_0223BE30
	ldr r4, _02238EEC ; =MOD83_0223BC30
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02238E66
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r0, #0x81
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_02238E66:
	mov r1, #0x51
	ldr r0, _02238EF0 ; =MOD83_0223BC60
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _02238E76
	bl FUN_02009C0C
_02238E76:
	mov r1, #0x57
	ldr r0, _02238EF0 ; =MOD83_0223BC60
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _02238E86
	bl FUN_02009C0C
_02238E86:
	mov r1, #0x52
	ldr r0, _02238EF0 ; =MOD83_0223BC60
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _02238E96
	bl FUN_02009E04
_02238E96:
	mov r1, #0x16
	ldr r0, _02238EF0 ; =MOD83_0223BC60
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	cmp r0, #0
	beq _02238EA6
	bl FUN_02009E04
_02238EA6:
	mov r4, #0
	mov r7, #0x4b
	ldr r5, _02238EF0 ; =MOD83_0223BC60
	add r6, r4, #0
	lsl r7, r7, #2
_02238EB0:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02008E2C
	str r6, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02238EB0
	ldr r0, _02238EF0 ; =MOD83_0223BC60
	ldr r0, [r0]
	bl FUN_0201FD58
	ldr r0, _02238EF0 ; =MOD83_0223BC60
	mov r1, #0
	str r1, [r0]
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02238EE8: .word MOD83_0223BE30
_02238EEC: .word MOD83_0223BC30
_02238EF0: .word MOD83_0223BC60
	thumb_func_end MOD83_02238E48

	thumb_func_start MOD83_02238EF4
MOD83_02238EF4: ; 0x02238EF4
	mov r1, #1
	sub r0, #0xa
	lsl r1, r0
	add r0, r1, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02238EF4

	thumb_func_start MOD83_02238F00
MOD83_02238F00: ; 0x02238F00
	push {r4, lr}
	ldr r0, _02238F34 ; =MOD83_0223CAB0
	ldr r4, _02238F38 ; =MOD83_0223BC30
	ldr r0, [r0, #0x20]
	cmp r0, #0
	beq _02238F1E
	mov r1, #0xea
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r4, #0
	blx r1
	mov r0, #0xea
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
_02238F1E:
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r3, _02238F3C ; =MOD83_027E0000
	ldr r1, _02238F40 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	.align 2, 0
_02238F34: .word MOD83_0223CAB0
_02238F38: .word MOD83_0223BC30
_02238F3C: .word 0x027E0000
_02238F40: .word 0x00003FF8
	thumb_func_end MOD83_02238F00

	thumb_func_start MOD83_02238F44
MOD83_02238F44: ; 0x02238F44
	push {r4}
	sub sp, #0x1c
	ldr r4, _02238F90 ; =MOD83_0223A744
	add r3, sp, #0
	mov r2, #0x1a
_02238F4E:
	ldrb r1, [r4]
	add r4, r4, #1
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _02238F4E
	add r1, sp, #0
	ldrb r2, [r1]
	mov r3, #0
	sub r1, r3, #1
	cmp r2, r1
	beq _02238F88
	add r4, sp, #0
	sub r1, r3, #1
_02238F6A:
	ldrb r2, [r4]
	cmp r0, r2
	bne _02238F7E
	add r0, sp, #0
	lsl r1, r3, #1
	add r0, #1
	add sp, #0x1c
	ldrb r0, [r0, r1]
	pop {r4}
	bx lr
_02238F7E:
	add r4, r4, #2
	ldrb r2, [r4]
	add r3, r3, #1
	cmp r2, r1
	bne _02238F6A
_02238F88:
	mov r0, #0
	add sp, #0x1c
	pop {r4}
	bx lr
	.align 2, 0
_02238F90: .word MOD83_0223A744
	thumb_func_end MOD83_02238F44

	thumb_func_start MOD83_02238F94
MOD83_02238F94: ; 0x02238F94
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0x20]
	add r5, r1, #0
	add r7, r2, #0
	add r6, r3, #0
	ldr r4, [sp, #0x40]
	bl GetMonGender
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	bl MonIsShiny
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	lsl r0, r7, #0x18
	ldr r2, [sp, #0x24]
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	mov r0, #0
	lsl r1, r5, #0x10
	lsl r2, r2, #0x18
	str r0, [sp, #8]
	add r0, r4, #0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x18
	mov r3, #2
	bl FUN_02068C00
	mov r1, #0
	ldr r0, [sp, #0x20]
	add r2, r1, #0
	bl GetMonData
	mov r3, #0
	str r3, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	str r1, [sp, #8]
	str r6, [sp, #0xc]
	str r0, [sp, #0x10]
	str r3, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0x18]
	str r5, [sp, #0x1c]
	ldr r2, _0223902C ; =MOD83_0223BC30
	ldrh r0, [r4]
	ldrh r1, [r4, #2]
	ldr r2, [r2, #4]
	bl FUN_020124B4
	mov r1, #0x32
	add r0, r6, #0
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r1, #0x32
	lsl r1, r1, #6
	add r0, r6, #0
	add r2, r1, #0
	bl GXS_LoadOBJ
	mov r0, #0x20
	str r0, [sp]
	ldr r0, _0223902C ; =MOD83_0223BC30
	mov r2, #5
	ldr r0, [r0, #4]
	mov r3, #0x60
	str r0, [sp, #4]
	ldrh r0, [r4]
	ldrh r1, [r4, #4]
	bl GfGfxLoader_GXLoadPal
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223902C: .word MOD83_0223BC30
	thumb_func_end MOD83_02238F94

	thumb_func_start MOD83_02239030
MOD83_02239030: ; 0x02239030
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0x21
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x23
	mov r2, #0x20
	mov r3, #0x22
	bl MOD83_02238BC4
	mov r1, #1
	mov r0, #0
	lsl r1, r1, #0x14
	bl MOD83_02238D38
	mov r3, #0
	mov r1, #0x81
	str r3, [sp]
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	mov r0, #1
	mov r2, #0x80
	bl MOD83_02238DBC
	mov r1, #0x81
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD83_02239030

	thumb_func_start MOD83_02239070
MOD83_02239070: ; 0x02239070
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	add r6, r1, #0
	add r4, r2, #0
	str r0, [sp, #4]
	mov r0, #0x36
	mov r1, #0xa
	mov r2, #0
	mov r3, #0xb
	bl MOD83_02238BC4
	mov r1, #1
	mov r0, #0
	lsl r1, r1, #0x14
	bl MOD83_02238D38
	mov r0, #1
	mov r1, #0x81
	str r0, [sp]
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	mov r2, #0x80
	mov r3, #0
	bl MOD83_02238DBC
	mov r3, #0x81
	lsl r3, r3, #2
	add r4, #8
	str r0, [r5, r3]
	cmp r6, #1
	beq _022390C2
	cmp r6, #2
	beq _022390F4
	cmp r6, #7
	beq _02239110
	add sp, #8
	pop {r4, r5, r6, pc}
_022390C2:
	add r0, r4, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r6, r0, #0
	add r0, r4, #0
	mov r1, #0x70
	mov r2, #0
	bl GetMonData
	add r2, r0, #0
	mov r0, #0xe9
	lsl r0, r0, #4
	mov r3, #0x21
	add r0, r5, r0
	lsl r3, r3, #4
	str r0, [sp]
	add r0, r4, #0
	add r1, r6, #0
	add r3, r5, r3
	bl MOD83_02238F94
	add sp, #8
	pop {r4, r5, r6, pc}
_022390F4:
	mov r0, #0xe9
	lsl r0, r0, #4
	add r1, r3, #0
	add r0, r5, r0
	add r3, #0xc
	str r0, [sp]
	add r0, r4, #0
	sub r1, #0x16
	mov r2, #0
	add r3, r5, r3
	bl MOD83_02238F94
	add sp, #8
	pop {r4, r5, r6, pc}
_02239110:
	mov r0, #0xe9
	lsl r0, r0, #4
	add r1, r3, #0
	add r0, r5, r0
	add r3, #0xc
	str r0, [sp]
	add r0, r4, #0
	sub r1, #0x16
	mov r2, #1
	add r3, r5, r3
	bl MOD83_02238F94
	add sp, #8
	pop {r4, r5, r6, pc}
	thumb_func_end MOD83_02239070

	thumb_func_start MOD83_0223912C
MOD83_0223912C: ; 0x0223912C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	cmp r1, #0xa
	bhi _02239168
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02239142: ; jump table
	.short _02239168 - _02239142 - 2 ; case 0
	.short _02239168 - _02239142 - 2 ; case 1
	.short _02239168 - _02239142 - 2 ; case 2
	.short _02239158 - _02239142 - 2 ; case 3
	.short _02239168 - _02239142 - 2 ; case 4
	.short _02239168 - _02239142 - 2 ; case 5
	.short _02239168 - _02239142 - 2 ; case 6
	.short _02239168 - _02239142 - 2 ; case 7
	.short _0223915C - _02239142 - 2 ; case 8
	.short _02239160 - _02239142 - 2 ; case 9
	.short _02239166 - _02239142 - 2 ; case 10
_02239158:
	ldr r4, [r2, #4]
	b _02239168
_0223915C:
	ldr r4, _022391C4 ; =0x000001C6
	b _02239168
_02239160:
	mov r4, #0x71
	lsl r4, r4, #2
	b _02239168
_02239166:
	ldr r4, _022391C8 ; =0x000001C7
_02239168:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	mov r1, #1
	bl GetItemIndexMapping
	add r7, r0, #0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	mov r1, #2
	bl GetItemIndexMapping
	add r4, r0, #0
	bl FUN_0206E708
	add r6, r0, #0
	bl FUN_0206E70C
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x10
	add r1, r7, #0
	add r2, r4, #0
	add r3, r6, #0
	bl MOD83_02238BC4
	mov r1, #1
	mov r0, #0
	lsl r1, r1, #0x14
	bl MOD83_02238D38
	mov r3, #0
	mov r1, #0x81
	str r3, [sp]
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	mov r0, #1
	mov r2, #0x80
	bl MOD83_02238DBC
	mov r1, #0x81
	lsl r1, r1, #2
	str r0, [r5, r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022391C4: .word 0x000001C6
_022391C8: .word 0x000001C7
	thumb_func_end MOD83_0223912C

	thumb_func_start MOD83_022391CC
MOD83_022391CC: ; 0x022391CC
	push {r3, lr}
	sub sp, #8
	mov r1, #0xc0
	str r1, [sp]
	ldr r0, [r0, #4]
	mov r2, #4
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #0x74
	mov r1, #0x1d
	add r3, #0xfc
	bl GfGfxLoader_GXLoadPal
	add sp, #8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022391CC

	thumb_func_start MOD83_022391EC
MOD83_022391EC: ; 0x022391EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r1, #0
	ldrh r4, [r6]
	add r5, r0, #0
	add r0, r4, #0
	bl MOD83_02238F44
	add r7, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, _022392DC ; =MOD83_0223BC30
	mov r1, #0x1e
	ldr r0, [r0, #4]
	add r2, r5, #0
	str r0, [sp, #0xc]
	mov r0, #0x74
	mov r3, #5
	bl GfGfxLoader_LoadCharData
	mov r2, #1
	ldr r3, _022392DC ; =MOD83_0223BC30
	str r2, [sp]
	ldr r3, [r3, #4]
	mov r0, #0x74
	mov r1, #0x1f
	bl GfGfxLoader_LoadFromNarc
	add r1, sp, #0x14
	str r0, [sp, #0x10]
	bl NNS_G2dGetUnpackedScreenData
	ldr r2, [sp, #0x14]
	mov r3, #6
	add r0, r5, #0
	mov r1, #5
	add r2, #0xc
	lsl r3, r3, #8
	bl FUN_02017DFC
	ldr r0, [sp, #0x10]
	bl FreeToHeap
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	mov r2, #0
	add r7, #8
	str r0, [sp, #4]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	add r0, r5, #0
	mov r1, #5
	add r3, r2, #0
	bl FUN_020186B4
	add r0, r5, #0
	mov r1, #5
	bl FUN_02017CD0
	ldr r1, _022392E0 ; =MOD83_022391CC
	ldr r0, _022392E4 ; =MOD83_0223CAB0
	cmp r4, #0xb
	str r1, [r0, #0x20]
	bhi _022392CA
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02239286: ; jump table
	.short _022392CA - _02239286 - 2 ; case 0
	.short _022392B4 - _02239286 - 2 ; case 1
	.short _022392B4 - _02239286 - 2 ; case 2
	.short _022392C0 - _02239286 - 2 ; case 3
	.short _0223929E - _02239286 - 2 ; case 4
	.short _0223929E - _02239286 - 2 ; case 5
	.short _0223929E - _02239286 - 2 ; case 6
	.short _022392AA - _02239286 - 2 ; case 7
	.short _022392C0 - _02239286 - 2 ; case 8
	.short _022392C0 - _02239286 - 2 ; case 9
	.short _022392C0 - _02239286 - 2 ; case 10
	.short _0223929E - _02239286 - 2 ; case 11
_0223929E:
	ldr r0, _022392E8 ; =MOD83_0223BC30
	add r1, r4, #0
	add r2, r6, #0
	bl MOD83_02239030
	b _022392CA
_022392AA:
	mov r1, #0x82
	ldr r0, _022392E8 ; =MOD83_0223BC30
	mov r2, #0x78
	lsl r1, r1, #2
	str r2, [r0, r1]
_022392B4:
	ldr r0, _022392E8 ; =MOD83_0223BC30
	add r1, r4, #0
	add r2, r6, #0
	bl MOD83_02239070
	b _022392CA
_022392C0:
	ldr r0, _022392E8 ; =MOD83_0223BC30
	add r1, r4, #0
	add r2, r6, #0
	bl MOD83_0223912C
_022392CA:
	mov r1, #0x81
	ldr r0, _022392E8 ; =MOD83_0223BC30
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022392DC: .word MOD83_0223BC30
_022392E0: .word MOD83_022391CC
_022392E4: .word MOD83_0223CAB0
_022392E8: .word MOD83_0223BC30
	thumb_func_end MOD83_022391EC

	thumb_func_start MOD83_022392EC
MOD83_022392EC: ; 0x022392EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r0, r2, #0
	lsl r1, r1, #8
	str r2, [sp]
	bl AllocFromHeap
	ldr r1, _0223936C ; =0x0000A001
	add r4, r0, #0
	bl MATHi_CRC16InitTableRev
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x50
	bl MATH_CalcCRC16
	add r6, r0, #0
	add r0, r4, #0
	bl FreeToHeap
	add r0, sp, #4
	bl OS_GetMacAddress
	add r0, sp, #4
	ldrh r1, [r0, #2]
	mov r2, #0
	add r3, sp, #4
	strh r1, [r0, #6]
	ldr r1, _02239370 ; =0x0000D679
	strh r6, [r0, #2]
_0223932E:
	ldrh r0, [r3]
	add r2, r2, #1
	eor r0, r1
	strh r0, [r3]
	ldrh r1, [r3]
	add r3, r3, #2
	cmp r2, #4
	blt _0223932E
	mov r1, #0x41
	ldr r0, [sp]
	lsl r1, r1, #2
	bl AllocFromHeap
	add r1, sp, #4
	mov r2, #8
	add r4, r0, #0
	bl FUN_0209521C
	add r5, #0x50
	mov r2, #0xd6
	add r0, r4, #0
	add r1, r5, #0
	lsl r2, r2, #2
	add r3, r7, #0
	bl FUN_020952AC
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223936C: .word 0x0000A001
_02239370: .word 0x0000D679
	thumb_func_end MOD83_022392EC

	thumb_func_start MOD83_02239374
MOD83_02239374: ; 0x02239374
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r0, r2, #0
	lsl r1, r1, #8
	str r2, [sp]
	bl AllocFromHeap
	ldr r1, _0223940C ; =0x0000A001
	add r4, r0, #0
	bl MATHi_CRC16InitTableRev
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x50
	bl MATH_CalcCRC16
	add r6, r0, #0
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #0
	bl FUN_0202EF18
	ldrb r2, [r0, #4]
	add r1, sp, #4
	mov r3, #0
	strb r2, [r1]
	ldrb r2, [r0, #5]
	strb r2, [r1, #1]
	ldrb r2, [r0, #6]
	strb r2, [r1, #2]
	ldrb r2, [r0, #7]
	strb r2, [r1, #3]
	ldrb r2, [r0, #8]
	strb r2, [r1, #4]
	ldrb r0, [r0, #9]
	strb r0, [r1, #5]
	add r0, sp, #4
	ldrh r2, [r0, #2]
	strh r2, [r0, #6]
	ldr r2, _02239410 ; =0x0000D679
	strh r6, [r0, #2]
_022393CE:
	ldrh r0, [r1]
	add r3, r3, #1
	eor r0, r2
	strh r0, [r1]
	ldrh r2, [r1]
	add r1, r1, #2
	cmp r3, #4
	blt _022393CE
	mov r1, #0x41
	ldr r0, [sp]
	lsl r1, r1, #2
	bl AllocFromHeap
	add r1, sp, #4
	mov r2, #8
	add r4, r0, #0
	bl FUN_0209521C
	add r5, #0x50
	mov r2, #0xd6
	add r0, r4, #0
	add r1, r5, #0
	lsl r2, r2, #2
	add r3, r7, #0
	bl FUN_020952AC
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223940C: .word 0x0000A001
_02239410: .word 0x0000D679
	thumb_func_end MOD83_02239374

	thumb_func_start MOD83_02239414
MOD83_02239414: ; 0x02239414
	push {r3, lr}
	cmp r2, #0
	beq _0223941E
	cmp r2, #1
	pop {r3, pc}
_0223941E:
	ldr r0, _02239428 ; =0x000005DC
	bl FUN_020054C8
	pop {r3, pc}
	nop
_02239428: .word 0x000005DC
	thumb_func_end MOD83_02239414

	thumb_func_start MOD83_0223942C
MOD83_0223942C: ; 0x0223942C
	push {r3, lr}
	ldr r0, _0223944C ; =MOD83_027FFFA8
	ldrh r1, [r0]
	mov r0, #2
	lsl r0, r0, #0xe
	and r0, r1
	asr r0, r0, #0xf
	bne _02239448
	bl CTRDG_IsAgbCartridge
	cmp r0, #0
	bne _02239448
	bl CTRDG_TerminateForPulledOut
_02239448:
	pop {r3, pc}
	nop
_0223944C: .word 0x027FFFA8
	thumb_func_end MOD83_0223942C

	thumb_func_start MOD83_02239450
MOD83_02239450: ; 0x02239450
	push {r3, lr}
	cmp r0, #1
	bne _02239478
	ldr r1, _02239484 ; =0x04000208
	ldrh r0, [r1]
	mov r0, #0
	strh r0, [r1]
	lsr r0, r1, #0xd
	ldr r1, _02239488 ; =MOD83_0223942C
	bl OS_SetIrqFunction
	mov r0, #2
	lsl r0, r0, #0xc
	bl OS_EnableIrqMask
	ldr r1, _02239484 ; =0x04000208
	ldrh r0, [r1]
	mov r0, #1
	strh r0, [r1]
	pop {r3, pc}
_02239478:
	mov r0, #2
	lsl r0, r0, #0xc
	bl OS_DisableIrqMask
	pop {r3, pc}
	nop
_02239484: .word 0x04000208
_02239488: .word MOD83_0223942C
	thumb_func_end MOD83_02239450

	thumb_func_start MOD83_0223948C
MOD83_0223948C: ; 0x0223948C
	bx lr
	.align 2, 0
	thumb_func_end MOD83_0223948C

	thumb_func_start MOD83_02239490
MOD83_02239490: ; 0x02239490
	push {r3, lr}
	ldr r1, _022394B4 ; =0x04000208
	ldrh r0, [r1]
	mov r0, #0
	strh r0, [r1]
	lsr r0, r1, #0xd
	ldr r1, _022394B8 ; =MOD83_0223948C
	bl OS_SetIrqFunction
	mov r0, #2
	lsl r0, r0, #0xc
	bl OS_EnableIrqMask
	ldr r1, _022394B4 ; =0x04000208
	ldrh r0, [r1]
	mov r0, #1
	strh r0, [r1]
	pop {r3, pc}
	.align 2, 0
_022394B4: .word 0x04000208
_022394B8: .word MOD83_0223948C
	thumb_func_end MOD83_02239490

	thumb_func_start MOD83_022394BC
MOD83_022394BC: ; 0x022394BC
	ldr r1, _022394C8 ; =MOD83_0223BC30
	str r0, [r1, #0x14]
	mov r0, #0
	str r0, [r1, #0x10]
	bx lr
	nop
_022394C8: .word MOD83_0223BC30
	thumb_func_end MOD83_022394BC

	thumb_func_start MOD83_022394CC
MOD83_022394CC: ; 0x022394CC
	push {r3, r4, r5, lr}
	ldr r0, _0223953C ; =MOD83_0223BC30
	ldr r4, _02239540 ; =MOD83_0223BC30
	ldr r0, [r0, #0x10]
	cmp r0, #4
	bhi _02239538
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022394E4: ; jump table
	.short _022394EE - _022394E4 - 2 ; case 0
	.short _02239504 - _022394E4 - 2 ; case 1
	.short _02239538 - _022394E4 - 2 ; case 2
	.short _02239538 - _022394E4 - 2 ; case 3
	.short _02239538 - _022394E4 - 2 ; case 4
_022394EE:
	mov r0, #4
	bl SetSoftResetDisableMask
	ldr r0, [r4, #0x14]
	mov r1, #2
	bl FUN_02022840
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _02239538
_02239504:
	ldr r0, [r4, #0x14]
	bl FUN_02022854
	add r5, r0, #0
	cmp r5, #3
	bne _02239516
	mov r0, #3
	str r0, [r4, #0x10]
	b _02239528
_02239516:
	cmp r5, #2
	bne _02239520
	mov r0, #2
	str r0, [r4, #0x10]
	b _02239528
_02239520:
	cmp r5, #1
	bne _02239528
	mov r0, #4
	str r0, [r4, #0x10]
_02239528:
	sub r0, r5, #2
	cmp r0, #1
	bhi _02239534
	mov r0, #4
	bl ClearSoftResetDisableMask
_02239534:
	add r0, r5, #0
	pop {r3, r4, r5, pc}
_02239538:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223953C: .word MOD83_0223BC30
_02239540: .word MOD83_0223BC30
	thumb_func_end MOD83_022394CC

	thumb_func_start MOD83_02239544
MOD83_02239544: ; 0x02239544
	ldr r0, _02239554 ; =MOD83_0223BC30
	ldr r1, _02239558 ; =MOD83_0223BC30
	ldr r0, [r0, #0x10]
	cmp r0, #4
	bne _02239552
	mov r0, #1
	str r0, [r1, #0x10]
_02239552:
	bx lr
	.align 2, 0
_02239554: .word MOD83_0223BC30
_02239558: .word MOD83_0223BC30
	thumb_func_end MOD83_02239544

	thumb_func_start MOD83_0223955C
MOD83_0223955C: ; 0x0223955C
	push {r3, lr}
	ldr r0, _02239570 ; =MOD83_0223BC30
	ldr r0, [r0, #0x14]
	bl FUN_0202287C
	mov r0, #4
	bl ClearSoftResetDisableMask
	pop {r3, pc}
	nop
_02239570: .word MOD83_0223BC30
	thumb_func_end MOD83_0223955C

	thumb_func_start MOD83_02239574
MOD83_02239574: ; 0x02239574
	ldr r0, _0223957C ; =MOD83_0223BC30
	ldr r0, [r0, #0x10]
	bx lr
	nop
_0223957C: .word MOD83_0223BC30
	thumb_func_end MOD83_02239574

	thumb_func_start MOD83_02239580
MOD83_02239580: ; 0x02239580
	push {r4, lr}
	ldr r1, _022395BC ; =MOD83_0223CAD4
	add r4, r0, #0
	ldr r2, [r1, #4]
	cmp r2, #0
	beq _0223959C
	ldr r3, [r1]
	ldr r1, _022395C0 ; =0x00001150
	ldr r0, _022395C4 ; =MOD83_0223B80C
	ldr r1, [r3, r1]
	lsl r3, r1, #2
	ldr r1, _022395C8 ; =MOD83_0223B7E4
	ldr r1, [r1, r3]
	blx r2
_0223959C:
	ldr r3, _022395BC ; =MOD83_0223CAD4
	ldr r1, _022395C0 ; =0x00001150
	ldr r0, [r3]
	str r4, [r0, r1]
	ldr r2, [r3, #4]
	cmp r2, #0
	beq _022395B8
	ldr r3, [r3]
	ldr r0, _022395CC ; =MOD83_0223B814
	ldr r1, [r3, r1]
	lsl r3, r1, #2
	ldr r1, _022395C8 ; =MOD83_0223B7E4
	ldr r1, [r1, r3]
	blx r2
_022395B8:
	pop {r4, pc}
	nop
_022395BC: .word MOD83_0223CAD4
_022395C0: .word 0x00001150
_022395C4: .word MOD83_0223B80C
_022395C8: .word MOD83_0223B7E4
_022395CC: .word MOD83_0223B814
	thumb_func_end MOD83_02239580

	thumb_func_start MOD83_022395D0
MOD83_022395D0: ; 0x022395D0
	ldr r1, _022395E4 ; =MOD83_0223CAD4
	ldr r3, [r1]
	ldr r1, _022395E8 ; =0x00001150
	ldr r2, [r3, r1]
	sub r2, #9
	cmp r2, #1
	bls _022395E2
	add r1, r1, #4
	str r0, [r3, r1]
_022395E2:
	bx lr
	.align 2, 0
_022395E4: .word MOD83_0223CAD4
_022395E8: .word 0x00001150
	thumb_func_end MOD83_022395D0

	thumb_func_start MOD83_022395EC
MOD83_022395EC: ; 0x022395EC
	push {r4, lr}
	ldr r0, _02239658 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _0223965C ; =0x00001150
	ldr r0, [r1, r0]
	cmp r0, #4
	bne _022395FE
	bl OS_Terminate
_022395FE:
	mov r0, #2
	bl MOD83_02239580
	ldr r3, _02239658 ; =MOD83_0223CAD4
	ldr r0, _02239660 ; =0x0000FFFF
	ldr r2, [r3]
	ldr r1, _02239664 ; =0x00000FCC
	strh r0, [r2, r1]
	sub r2, r1, #2
	ldr r4, [r3]
	sub r1, r1, #4
	strh r0, [r4, r2]
	ldr r2, [r3]
	strh r0, [r2, r1]
	bl MOD83_02239670
	cmp r0, #0
	bne _0223963C
	mov r0, #9
	bl MOD83_02239580
	ldr r0, _02239658 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239668 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _02239638
	mov r0, #4
	blx r1
_02239638:
	mov r0, #0
	pop {r4, pc}
_0223963C:
	ldr r1, _02239658 ; =MOD83_0223CAD4
	ldr r0, _0223966C ; =0x00001158
	ldr r2, [r1]
	mov r3, #2
	strh r3, [r2, r0]
	ldr r1, [r1]
	add r0, #0x24
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _02239654
	mov r0, #0
	blx r1
_02239654:
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_02239658: .word MOD83_0223CAD4
_0223965C: .word 0x00001150
_02239660: .word 0x0000FFFF
_02239664: .word 0x00000FCC
_02239668: .word 0x0000117C
_0223966C: .word 0x00001158
	thumb_func_end MOD83_022395EC

	thumb_func_start MOD83_02239670
MOD83_02239670: ; 0x02239670
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02239748 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _0223974C ; =0x00001150
	ldr r0, [r1, r0]
	cmp r0, #2
	beq _02239684
	bl OS_Terminate
	mov r0, #0
_02239684:
	bl WM_GetAllowedChannel
	add r4, r0, #0
	mov r0, #2
	lsl r0, r0, #0xe
	cmp r4, r0
	bne _0223969C
	mov r0, #3
	bl MOD83_022395D0
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223969C:
	cmp r4, #0
	bne _022396AA
	mov r0, #0x16
	bl MOD83_022395D0
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_022396AA:
	ldr r0, _02239748 ; =MOD83_0223CAD4
	ldr r2, [r0]
	ldr r0, _02239750 ; =0x00001176
	ldrh r1, [r2, r0]
	cmp r1, #0x10
	blo _022396EC
	sub r1, #0x10
	mov r5, #0
	mov r7, #0xd
	mov r6, #1
	b _022396D2
_022396C0:
	add r0, r1, #1
	add r1, r7, #0
	bl _s32_div_f
	add r0, r6, #0
	lsl r0, r1
	tst r0, r4
	bne _022396D6
	add r5, r5, #1
_022396D2:
	cmp r5, #0xd
	blt _022396C0
_022396D6:
	ldr r2, _02239748 ; =MOD83_0223CAD4
	add r4, r1, #0
	ldr r3, [r2]
	ldr r0, _02239750 ; =0x00001176
	add r4, #0x10
	strh r4, [r3, r0]
	add r3, r1, #1
	ldr r1, [r2]
	ldr r0, _02239754 ; =0x00000FC4
	strh r3, [r1, r0]
	b _022396F0
_022396EC:
	ldr r0, _02239754 ; =0x00000FC4
	strh r1, [r2, r0]
_022396F0:
	ldr r2, _02239748 ; =MOD83_0223CAD4
	ldr r0, _02239758 ; =0x00000FC6
	ldr r1, [r2]
	mov r3, #0xdc
	strh r3, [r1, r0]
	add r1, r0, #0
	ldr r3, [r2]
	sub r1, #0xc6
	add r1, r3, r1
	sub r0, r0, #6
	str r1, [r3, r0]
	ldr r1, [r2]
	ldr r0, _0223975C ; =0x00001158
	ldrh r0, [r1, r0]
	cmp r0, #3
	bne _02239726
	mov r5, #0
	ldr r0, _02239760 ; =0x00001170
	ldr r1, _02239764 ; =0x00000FC8
	b _02239722
_02239718:
	ldr r3, [r2]
	add r4, r3, r5
	ldrb r3, [r4, r0]
	add r5, r5, #1
	strb r3, [r4, r1]
_02239722:
	cmp r5, #6
	blt _02239718
_02239726:
	ldr r1, _02239748 ; =MOD83_0223CAD4
	ldr r0, _02239768 ; =MOD83_0223976C
	ldr r2, [r1]
	mov r1, #0x3f
	lsl r1, r1, #6
	add r1, r2, r1
	bl WM_StartScan
	cmp r0, #2
	beq _02239742
	bl MOD83_022395D0
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02239742:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239748: .word MOD83_0223CAD4
_0223974C: .word 0x00001150
_02239750: .word 0x00001176
_02239754: .word 0x00000FC4
_02239758: .word 0x00000FC6
_0223975C: .word 0x00001158
_02239760: .word 0x00001170
_02239764: .word 0x00000FC8
_02239768: .word MOD83_0223976C
	thumb_func_end MOD83_02239670

	thumb_func_start MOD83_0223976C
MOD83_0223976C: ; 0x0223976C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02239792
	bl MOD83_022395D0
	mov r0, #9
	bl MOD83_02239580
	ldr r0, _02239880 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239884 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _0223987E
	mov r0, #4
	blx r1
	pop {r3, r4, r5, pc}
_02239792:
	ldr r0, _02239880 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239888 ; =0x00001150
	ldr r0, [r1, r0]
	cmp r0, #2
	beq _022397BE
	bl MOD83_022398A4
	cmp r0, #0
	bne _0223987E
	mov r0, #9
	bl MOD83_02239580
	ldr r0, _02239880 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239884 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _0223987E
	mov r0, #4
	blx r1
	pop {r3, r4, r5, pc}
_022397BE:
	ldrh r0, [r4, #8]
	cmp r0, #3
	beq _0223987E
	cmp r0, #4
	beq _02239860
	cmp r0, #5
	bne _02239860
	mov r0, #0xf
	lsl r0, r0, #8
	add r0, r1, r0
	mov r1, #0xc0
	bl DC_InvalidateRange
	ldrh r0, [r4, #0x36]
	cmp r0, #8
	blo _022397E6
	ldr r1, [r4, #0x3c]
	ldr r0, _0223988C ; =0x00400318
	cmp r1, r0
	beq _022397F8
_022397E6:
	ldr r0, _02239880 ; =MOD83_0223CAD4
	ldr r3, [r0, #4]
	cmp r3, #0
	beq _02239860
	ldr r0, _02239890 ; =MOD83_0223B818
	ldr r1, [r4, #0x3c]
	ldr r2, _0223988C ; =0x00400318
	blx r3
	b _02239860
_022397F8:
	ldr r1, _02239880 ; =MOD83_0223CAD4
	ldrh r3, [r4, #0x12]
	ldr r2, [r1]
	ldr r0, _02239894 ; =0x0000116C
	str r3, [r2, r0]
	ldr r1, [r1]
	sub r0, #0x14
	ldrh r0, [r1, r0]
	cmp r0, #2
	bne _02239844
	add r0, r4, #0
	add r0, #0x48
	bl MOD83_02239B00
	ldr r2, _02239880 ; =MOD83_0223CAD4
	ldr r1, _02239898 ; =0x00001170
	mov r0, #0
_0223981A:
	add r3, r4, r0
	ldrb r5, [r3, #0xa]
	ldr r3, [r2]
	add r3, r3, r0
	add r0, r0, #1
	strb r5, [r3, r1]
	cmp r0, #6
	blt _0223981A
	ldr r1, _02239880 ; =MOD83_0223CAD4
	ldr r0, _0223989C ; =0x00001176
	ldr r3, [r1]
	ldrh r2, [r3, r0]
	sub r2, #0xf
	strh r2, [r3, r0]
	ldr r1, [r1]
	add r0, r0, #6
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _02239844
	mov r0, #1
	blx r1
_02239844:
	add r4, #0x48
	add r0, r4, #0
	bl MOD83_02239B80
	cmp r0, #0
	beq _02239860
	ldr r0, _02239880 ; =MOD83_0223CAD4
	mov r2, #4
	ldr r1, [r0]
	ldr r0, _022398A0 ; =0x00001158
	strh r2, [r1, r0]
	bl MOD83_02239A14
	pop {r3, r4, r5, pc}
_02239860:
	bl MOD83_02239670
	cmp r0, #0
	bne _0223987E
	mov r0, #9
	bl MOD83_02239580
	ldr r0, _02239880 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239884 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _0223987E
	mov r0, #4
	blx r1
_0223987E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02239880: .word MOD83_0223CAD4
_02239884: .word 0x0000117C
_02239888: .word 0x00001150
_0223988C: .word 0x00400318
_02239890: .word MOD83_0223B818
_02239894: .word 0x0000116C
_02239898: .word 0x00001170
_0223989C: .word 0x00001176
_022398A0: .word 0x00001158
	thumb_func_end MOD83_0223976C

	thumb_func_start MOD83_022398A4
MOD83_022398A4: ; 0x022398A4
	push {r3, lr}
	ldr r0, _022398BC ; =MOD83_022398C0
	bl WM_EndScan
	cmp r0, #2
	beq _022398B8
	bl MOD83_022395D0
	mov r0, #0
	pop {r3, pc}
_022398B8:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_022398BC: .word MOD83_022398C0
	thumb_func_end MOD83_022398A4

	thumb_func_start MOD83_022398C0
MOD83_022398C0: ; 0x022398C0
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _022398CE
	bl MOD83_022395D0
	pop {r3, pc}
_022398CE:
	mov r0, #1
	bl MOD83_02239580
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD83_022398C0

	thumb_func_start MOD83_022398D8
MOD83_022398D8: ; 0x022398D8
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _022398E8
	mov r0, #0xa
	bl MOD83_02239580
	pop {r3, pc}
_022398E8:
	mov r0, #0
	bl MOD83_02239580
	ldr r0, _02239900 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239904 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _022398FE
	mov r0, #3
	blx r1
_022398FE:
	pop {r3, pc}
	.align 2, 0
_02239900: .word MOD83_0223CAD4
_02239904: .word 0x0000117C
	thumb_func_end MOD83_022398D8

	thumb_func_start MOD83_02239908
MOD83_02239908: ; 0x02239908
	push {r3, lr}
	ldr r0, _02239924 ; =MOD83_0223CAD4
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _02239928 ; =0x00001154
	str r2, [r1, r0]
	bl MOD83_02239954
	cmp r0, #0
	beq _02239920
	mov r0, #1
	pop {r3, pc}
_02239920:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_02239924: .word MOD83_0223CAD4
_02239928: .word 0x00001154
	thumb_func_end MOD83_02239908

	thumb_func_start MOD83_0223992C
MOD83_0223992C: ; 0x0223992C
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #8
	bne _0223994A
	mov r0, #9
	bl MOD83_02239580
	ldr r0, _0223994C ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239950 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _0223994A
	mov r0, #4
	blx r1
_0223994A:
	pop {r3, pc}
	.align 2, 0
_0223994C: .word MOD83_0223CAD4
_02239950: .word 0x0000117C
	thumb_func_end MOD83_0223992C

	thumb_func_start MOD83_02239954
MOD83_02239954: ; 0x02239954
	push {r3, lr}
	mov r0, #3
	bl MOD83_02239580
	ldr r0, _02239980 ; =MOD83_0223CAD4
	ldr r1, _02239984 ; =MOD83_02239988
	ldr r0, [r0]
	mov r2, #2
	bl WM_Initialize
	cmp r0, #2
	beq _0223997A
	bl MOD83_022395D0
	mov r0, #0xa
	bl MOD83_02239580
	mov r0, #0
	pop {r3, pc}
_0223997A:
	mov r0, #1
	pop {r3, pc}
	nop
_02239980: .word MOD83_0223CAD4
_02239984: .word MOD83_02239988
	thumb_func_end MOD83_02239954

	thumb_func_start MOD83_02239988
MOD83_02239988: ; 0x02239988
	push {r3, lr}
	ldrh r0, [r0, #2]
	cmp r0, #0
	beq _0223999C
	bl MOD83_022395D0
	mov r0, #0xa
	bl MOD83_02239580
	pop {r3, pc}
_0223999C:
	ldr r0, _022399C0 ; =MOD83_0223992C
	bl WM_SetIndCallback
	cmp r0, #0
	beq _022399B2
	bl MOD83_022395D0
	mov r0, #0xa
	bl MOD83_02239580
	pop {r3, pc}
_022399B2:
	mov r0, #1
	bl MOD83_02239580
	bl MOD83_022395EC
	pop {r3, pc}
	nop
_022399C0: .word MOD83_0223992C
	thumb_func_end MOD83_02239988

	thumb_func_start MOD83_022399C4
MOD83_022399C4: ; 0x022399C4
	push {r3, lr}
	ldr r0, _02239A04 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239A08 ; =0x00001150
	ldr r0, [r1, r0]
	cmp r0, #1
	beq _022399D6
	bl OS_Terminate
_022399D6:
	mov r0, #3
	bl MOD83_02239580
	ldr r0, _02239A0C ; =MOD83_022398D8
	bl WM_End
	cmp r0, #2
	beq _02239A00
	mov r0, #9
	bl MOD83_02239580
	ldr r0, _02239A04 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239A10 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _022399FC
	mov r0, #4
	blx r1
_022399FC:
	mov r0, #0
	pop {r3, pc}
_02239A00:
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_02239A04: .word MOD83_0223CAD4
_02239A08: .word 0x00001150
_02239A0C: .word MOD83_022398D8
_02239A10: .word 0x0000117C
	thumb_func_end MOD83_022399C4

	thumb_func_start MOD83_02239A14
MOD83_02239A14: ; 0x02239A14
	push {r3, lr}
	ldr r0, _02239A30 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239A34 ; =0x00001150
	ldr r0, [r1, r0]
	cmp r0, #1
	bne _02239A28
	bl MOD83_022399C4
	pop {r3, pc}
_02239A28:
	bl MOD83_02239A38
	pop {r3, pc}
	nop
_02239A30: .word MOD83_0223CAD4
_02239A34: .word 0x00001150
	thumb_func_end MOD83_02239A14

	thumb_func_start MOD83_02239A38
MOD83_02239A38: ; 0x02239A38
	push {r3, lr}
	mov r0, #3
	bl MOD83_02239580
	ldr r0, _02239A58 ; =MOD83_02239A5C
	bl WM_Reset
	cmp r0, #2
	beq _02239A52
	bl MOD83_022395D0
	mov r0, #0
	pop {r3, pc}
_02239A52:
	mov r0, #1
	pop {r3, pc}
	nop
_02239A58: .word MOD83_02239A5C
	thumb_func_end MOD83_02239A38

	thumb_func_start MOD83_02239A5C
MOD83_02239A5C: ; 0x02239A5C
	push {r4, lr}
	add r4, r0, #0
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02239A84
	mov r0, #9
	bl MOD83_02239580
	ldrh r0, [r4, #2]
	bl MOD83_022395D0
	ldr r0, _02239A90 ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239A94 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _02239A8E
	mov r0, #4
	blx r1
	pop {r4, pc}
_02239A84:
	mov r0, #1
	bl MOD83_02239580
	bl MOD83_022399C4
_02239A8E:
	pop {r4, pc}
	.align 2, 0
_02239A90: .word MOD83_0223CAD4
_02239A94: .word 0x0000117C
	thumb_func_end MOD83_02239A5C

	thumb_func_start MOD83_02239A98
MOD83_02239A98: ; 0x02239A98
	push {r3, r4, r5, r6, r7, lr}
	add r3, r0, #0
	add r2, #0x1f
	mov r0, #0x1f
	bic r2, r0
	ldr r5, _02239AF4 ; =MOD83_0223CAD4
	ldr r4, _02239AF8 ; =0x00001150
	str r2, [r5]
	mov r0, #0
	str r0, [r2, r4]
	add r2, r4, #0
	ldr r6, [r5]
	mov r7, #1
	add r2, #8
	strh r7, [r6, r2]
	add r2, r4, #0
	ldr r6, [r5]
	add r2, #0x28
	str r3, [r6, r2]
	add r2, r4, #0
	ldr r3, [r5]
	add r2, #0xc
	strh r0, [r3, r2]
	add r2, r4, #0
	ldr r3, [r5]
	add r2, #0xe
	strh r0, [r3, r2]
	add r2, r4, #0
	ldr r3, [r5]
	add r2, #0x2c
	str r1, [r3, r2]
	add r2, r4, #0
	ldr r3, [r5]
	mov r1, #0x10
	add r2, #0x26
	strh r1, [r3, r2]
	ldr r3, [r5]
	ldr r2, _02239AFC ; =0x00001048
	sub r1, #0x11
	str r0, [r3, r2]
	ldr r0, [r5]
	add r4, #0x1c
	str r1, [r0, r4]
	bl MOD83_02239908
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239AF4: .word MOD83_0223CAD4
_02239AF8: .word 0x00001150
_02239AFC: .word 0x00001048
	thumb_func_end MOD83_02239A98

	thumb_func_start MOD83_02239B00
MOD83_02239B00: ; 0x02239B00
	push {r4, r5, r6, lr}
	ldr r3, _02239B70 ; =MOD83_0223CAD4
	ldr r1, _02239B74 ; =0x00001048
	ldr r2, [r3]
	mov r4, #0
	str r4, [r2, r1]
	ldr r1, [r3]
	ldr r2, _02239B78 ; =0x00001158
	mov r4, #3
	strh r4, [r1, r2]
	ldrh r5, [r0]
	ldr r4, [r3]
	add r1, r2, #2
	strh r5, [r4, r1]
	ldr r4, [r0, #4]
	add r0, r2, #0
	ldr r1, [r3]
	add r0, #8
	str r4, [r1, r0]
	ldr r4, [r3]
	add r2, #8
	ldr r0, [r4, r2]
	mov r1, #0x68
	sub r0, r0, #1
	bl _u32_div_f
	ldr r2, _02239B7C ; =0x0000115C
	add r0, r0, #1
	strh r0, [r4, r2]
	ldr r4, _02239B70 ; =MOD83_0223CAD4
	mov r0, #0
	ldr r3, [r4]
	add r1, r2, #2
	strh r0, [r3, r1]
	add r1, r2, #0
	ldr r3, [r4]
	add r1, #8
	str r0, [r3, r1]
	ldr r1, [r4]
	ldrh r2, [r1, r2]
	cmp r2, #0
	ble _02239B6C
	mov r2, #0x46
	lsl r2, r2, #6
	add r3, r2, #0
	add r6, r0, #0
	sub r3, #0x24
_02239B5E:
	add r1, r1, r0
	strb r6, [r1, r2]
	ldr r1, [r4]
	add r0, r0, #1
	ldrh r5, [r1, r3]
	cmp r0, r5
	blt _02239B5E
_02239B6C:
	pop {r4, r5, r6, pc}
	nop
_02239B70: .word MOD83_0223CAD4
_02239B74: .word 0x00001048
_02239B78: .word 0x00001158
_02239B7C: .word 0x0000115C
	thumb_func_end MOD83_02239B00

	thumb_func_start MOD83_02239B80
MOD83_02239B80: ; 0x02239B80
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _02239C9C ; =MOD83_0223CAD4
	ldrh r1, [r4]
	ldr r3, [r0]
	ldr r0, _02239CA0 ; =0x0000115A
	ldrh r2, [r3, r0]
	cmp r2, r1
	bne _02239B9C
	add r0, r0, #6
	ldr r1, [r3, r0]
	ldr r0, [r4, #4]
	cmp r1, r0
	beq _02239BC8
_02239B9C:
	ldr r0, _02239C9C ; =MOD83_0223CAD4
	ldr r3, [r0]
	ldr r0, _02239CA4 ; =0x00001164
	ldr r2, [r3, r0]
	add r1, r2, #1
	str r1, [r3, r0]
	cmp r2, #0x10
	blo _02239BC4
	add r0, r4, #0
	bl MOD83_02239B00
	ldr r0, _02239C9C ; =MOD83_0223CAD4
	ldr r1, [r0]
	ldr r0, _02239CA8 ; =0x0000117C
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _02239BC8
	mov r0, #5
	blx r1
	b _02239BC8
_02239BC4:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02239BC8:
	ldrh r3, [r4, #2]
	ldr r0, _02239CAC ; =0x0000FFFF
	cmp r3, r0
	bne _02239BF0
	ldr r1, _02239C9C ; =MOD83_0223CAD4
	add r4, #8
	ldr r2, [r1]
	mov r1, #0xfe
	lsl r1, r1, #4
	add r1, r2, r1
	add r0, r4, #0
	mov r2, #0x68
	bl MIi_CpuCopy32
	ldr r0, _02239C9C ; =MOD83_0223CAD4
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _02239CB0 ; =0x00001048
	str r2, [r1, r0]
	b _02239C98
_02239BF0:
	ldr r1, _02239C9C ; =MOD83_0223CAD4
	ldr r0, _02239CB4 ; =0x00001168
	ldr r2, [r1]
	str r3, [r2, r0]
	ldr r3, [r1]
	add r1, r0, #0
	sub r1, #0xc
	ldrh r2, [r4, #2]
	ldrh r1, [r3, r1]
	cmp r2, r1
	blo _02239C18
	add r0, #0x14
	ldr r1, [r3, r0]
	cmp r1, #0
	beq _02239C12
	mov r0, #4
	blx r1
_02239C12:
	mov r0, #9
	bl MOD83_02239580
_02239C18:
	ldr r0, _02239C9C ; =MOD83_0223CAD4
	mov r2, #0x46
	ldr r1, [r0]
	lsl r2, r2, #6
	ldrh r3, [r4, #2]
	add r5, r1, r2
	ldrb r1, [r5, r3]
	cmp r1, #0
	bne _02239C98
	mov r1, #1
	strb r1, [r5, r3]
	ldr r5, [r0]
	add r0, r2, #0
	sub r0, #0x24
	ldrh r0, [r5, r0]
	ldrh r1, [r4, #2]
	sub r0, r0, #1
	cmp r1, r0
	bne _02239C5C
	add r3, r1, #0
	add r1, r2, #0
	sub r1, #8
	sub r2, #0x20
	mov r0, #0x68
	ldr r1, [r5, r1]
	mul r3, r0
	ldr r2, [r5, r2]
	add r4, #8
	add r0, r4, #0
	add r1, r1, r3
	sub r2, r2, r3
	bl MIi_CpuCopy32
	b _02239C70
_02239C5C:
	add r4, #8
	sub r2, #8
	add r0, r4, #0
	ldr r4, [r5, r2]
	mov r2, #0x68
	add r3, r1, #0
	mul r3, r2
	add r1, r4, r3
	bl MIi_CpuCopy32
_02239C70:
	ldr r1, _02239C9C ; =MOD83_0223CAD4
	ldr r0, _02239CB8 ; =0x0000115E
	ldr r3, [r1]
	ldrh r2, [r3, r0]
	add r2, r2, #1
	strh r2, [r3, r0]
	ldr r3, [r1]
	sub r1, r0, #2
	ldrh r2, [r3, r0]
	ldrh r1, [r3, r1]
	cmp r2, r1
	bne _02239C98
	add r0, #0x1e
	ldr r1, [r3, r0]
	cmp r1, #0
	beq _02239C94
	mov r0, #2
	blx r1
_02239C94:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02239C98:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_02239C9C: .word MOD83_0223CAD4
_02239CA0: .word 0x0000115A
_02239CA4: .word 0x00001164
_02239CA8: .word 0x0000117C
_02239CAC: .word 0x0000FFFF
_02239CB0: .word 0x00001048
_02239CB4: .word 0x00001168
_02239CB8: .word 0x0000115E
	thumb_func_end MOD83_02239B80

	thumb_func_start MOD83_02239CBC
MOD83_02239CBC: ; 0x02239CBC
	push {r3, r4}
	mov r2, #0
	add r3, r2, #0
	lsr r1, r1, #1
	beq _02239CE4
_02239CC6:
	lsl r4, r3, #1
	ldrh r4, [r0, r4]
	add r3, r3, #1
	lsl r3, r3, #0x10
	add r2, r2, r4
	lsl r2, r2, #0x10
	lsr r2, r2, #0x10
	lsl r4, r2, #1
	asr r2, r2, #0xf
	orr r2, r4
	lsl r2, r2, #0x10
	lsr r3, r3, #0x10
	lsr r2, r2, #0x10
	cmp r3, r1
	blo _02239CC6
_02239CE4:
	add r0, r2, #0
	pop {r3, r4}
	bx lr
	.align 2, 0
	thumb_func_end MOD83_02239CBC

	thumb_func_start MOD83_02239CEC
MOD83_02239CEC: ; 0x02239CEC
	push {r4, lr}
	sub sp, #8
	ldr r0, _02239D80 ; =MOD83_0223CAD4
	add r1, sp, #0
	ldr r4, [r0]
	ldr r0, _02239D84 ; =0x00001170
	add r3, r4, r0
	ldrh r2, [r3]
	sub r0, #0x16
	strh r2, [r1]
	ldrh r2, [r3, #2]
	strh r2, [r1, #6]
	ldrh r2, [r3, #4]
	add r3, sp, #0
	strh r2, [r1, #4]
	ldrh r0, [r4, r0]
	ldr r2, _02239D88 ; =0x00003FA2
	strh r0, [r1, #2]
	mov r1, #0
_02239D12:
	ldrh r0, [r3]
	add r1, r1, #1
	eor r0, r2
	strh r0, [r3]
	ldrh r2, [r3]
	add r3, r3, #2
	cmp r1, #4
	blt _02239D12
	ldr r0, _02239D80 ; =MOD83_0223CAD4
	mov r2, #8
	ldr r1, [r0]
	ldr r0, _02239D8C ; =0x0000104C
	add r0, r1, r0
	add r1, sp, #0
	bl FUN_0209521C
	ldr r0, _02239D80 ; =MOD83_0223CAD4
	ldr r2, _02239D90 ; =0x00001178
	ldr r3, [r0]
	ldr r0, _02239D8C ; =0x0000104C
	ldr r1, [r3, r2]
	sub r2, #0x18
	ldr r2, [r3, r2]
	add r0, r3, r0
	add r3, r1, #0
	bl FUN_020952AC
	ldr r1, _02239D80 ; =MOD83_0223CAD4
	ldr r2, _02239D8C ; =0x0000104C
	ldr r1, [r1]
	mov r0, #0
	add r1, r1, r2
	lsr r2, r2, #4
	bl MIi_CpuClear32
	ldr r0, _02239D80 ; =MOD83_0223CAD4
	ldr r1, _02239D90 ; =0x00001178
	ldr r2, [r0]
	ldr r0, [r2, r1]
	sub r1, #0x18
	ldr r1, [r2, r1]
	bl MOD83_02239CBC
	ldr r1, _02239D80 ; =MOD83_0223CAD4
	ldr r2, [r1]
	ldr r1, _02239D94 ; =0x0000115A
	ldrh r1, [r2, r1]
	cmp r1, r0
	bne _02239D7A
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_02239D7A:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_02239D80: .word MOD83_0223CAD4
_02239D84: .word 0x00001170
_02239D88: .word 0x00003FA2
_02239D8C: .word 0x0000104C
_02239D90: .word 0x00001178
_02239D94: .word 0x0000115A
	thumb_func_end MOD83_02239CEC

	thumb_func_start MOD83_02239D98
MOD83_02239D98: ; 0x02239D98
	ldr r0, _02239D9C ; =0x000016A0
	bx lr
	.align 2, 0
_02239D9C: .word 0x000016A0
	thumb_func_end MOD83_02239D98

	thumb_func_start MOD83_02239DA0
MOD83_02239DA0: ; 0x02239DA0
	ldr r0, _02239DB8 ; =MOD83_0223CAD4
	ldr r2, [r0]
	ldr r0, _02239DBC ; =0x00001048
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _02239DB2
	sub r0, #0x68
	add r0, r2, r0
	bx lr
_02239DB2:
	mov r0, #0
	bx lr
	nop
_02239DB8: .word MOD83_0223CAD4
_02239DBC: .word 0x00001048
	thumb_func_end MOD83_02239DA0

	thumb_func_start MOD83_02239DC0
MOD83_02239DC0: ; 0x02239DC0
	push {r3, lr}
	add r1, #0x24
	mov r0, #0x1f
	bic r1, r0
	add r1, #0x20
	mov r0, #0x56
	bl AllocFromHeap
	add r2, r0, #0
	add r2, #0x20
	mov r1, #0x1f
	bic r2, r1
	sub r1, r2, #4
	str r0, [r1]
	add r0, r2, #0
	pop {r3, pc}
	thumb_func_end MOD83_02239DC0

	thumb_func_start MOD83_02239DE0
MOD83_02239DE0: ; 0x02239DE0
	push {r3, lr}
	cmp r1, #0
	beq _02239DEE
	sub r0, r1, #4
	ldr r0, [r0]
	bl FreeToHeap
_02239DEE:
	pop {r3, pc}
	thumb_func_end MOD83_02239DE0

	thumb_func_start MOD83_02239DF0
MOD83_02239DF0: ; 0x02239DF0
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, sp, #0
	add r1, sp, #4
	bl MOD04_021DD718
	ldr r0, [sp]
	neg r0, r0
	bl MOD04_021D80E0
	ldr r1, _02239E34 ; =0x00002610
	str r0, [r4, r1]
	ldr r0, [sp]
	neg r2, r0
	add r0, r1, #4
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, [sp, #4]
	add r0, #8
	str r2, [r4, r0]
	sub r0, r1, #4
	mov r2, #1
	str r2, [r4, r0]
	ldr r0, _02239E38 ; =MOD83_0223CADC
	mov r1, #0
	str r1, [r0, #0xc]
	add r0, r4, #0
	bl MOD83_0222FA44
	ldr r0, _02239E3C ; =0x0000100E
	add sp, #8
	pop {r4, pc}
	nop
_02239E34: .word 0x00002610
_02239E38: .word MOD83_0223CADC
_02239E3C: .word 0x0000100E
	thumb_func_end MOD83_02239DF0

	thumb_func_start MOD83_02239E40
MOD83_02239E40: ; 0x02239E40
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02239E70 ; =0x00002618
	ldr r0, [r4, r0]
	cmp r0, #5
	beq _02239E50
	cmp r0, #6
	bne _02239E5C
_02239E50:
	bl MOD04_021DDC1C
	ldr r0, _02239E74 ; =MOD83_0223CADC
	mov r1, #1
	str r1, [r0, #0xc]
	b _02239E62
_02239E5C:
	ldr r0, _02239E74 ; =MOD83_0223CADC
	mov r1, #1
	str r1, [r0, #0xc]
_02239E62:
	bl FUN_02033ED0
	ldr r0, _02239E78 ; =0x0000260C
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, _02239E7C ; =0x0000100F
	pop {r4, pc}
	.align 2, 0
_02239E70: .word 0x00002618
_02239E74: .word MOD83_0223CADC
_02239E78: .word 0x0000260C
_02239E7C: .word 0x0000100F
	thumb_func_end MOD83_02239E40

	thumb_func_start MOD83_02239E80
MOD83_02239E80: ; 0x02239E80
	push {lr}
	sub sp, #0x3c
	bl MOD04_021DDC1C
	cmp r0, #4
	beq _02239E94
	cmp r0, #7
	beq _02239EA0
	cmp r0, #8
	b _02239EA0
_02239E94:
	add r0, sp, #0
	bl MOD04_021DD9DC
	add sp, #0x3c
	mov r0, #1
	pop {pc}
_02239EA0:
	mov r0, #0
	add sp, #0x3c
	pop {pc}
	.align 2, 0
	thumb_func_end MOD83_02239E80

	thumb_func_start MOD83_02239EA8
MOD83_02239EA8: ; 0x02239EA8
	push {r3, r4}
	ldr r3, _02239EBC ; =MOD83_0223CADC
	mov r4, #0
	str r4, [r3]
	ldr r3, _02239EC0 ; =0x000015F4
	str r2, [r0, r3]
	ldr r0, _02239EC4 ; =0x00001011
	str r0, [r1]
	pop {r3, r4}
	bx lr
	.align 2, 0
_02239EBC: .word MOD83_0223CADC
_02239EC0: .word 0x000015F4
_02239EC4: .word 0x00001011
	thumb_func_end MOD83_02239EA8

	thumb_func_start MOD83_02239EC8
MOD83_02239EC8: ; 0x02239EC8
	push {r3, r4, r5, lr}
	ldr r4, _02239EE4 ; =MOD83_0223CADC
	mov r5, #0
	str r5, [r4, #8]
	str r1, [r4, #4]
	ldr r1, _02239EE8 ; =0x000015F4
	str r3, [r0, r1]
	ldr r0, _02239EEC ; =0x00001012
	str r0, [r2]
	ldr r0, _02239EF0 ; =MOD83_02239F28
	bl MOD04_021DE404
	pop {r3, r4, r5, pc}
	nop
_02239EE4: .word MOD83_0223CADC
_02239EE8: .word 0x000015F4
_02239EEC: .word 0x00001012
_02239EF0: .word MOD83_02239F28
	thumb_func_end MOD83_02239EC8

	thumb_func_start MOD83_02239EF4
MOD83_02239EF4: ; 0x02239EF4
	push {r3, lr}
	cmp r1, #6
	bhi _02239F1C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02239F06: ; jump table
	.short _02239F1C - _02239F06 - 2 ; case 0
	.short _02239F1C - _02239F06 - 2 ; case 1
	.short _02239F1C - _02239F06 - 2 ; case 2
	.short _02239F14 - _02239F06 - 2 ; case 3
	.short _02239F1C - _02239F06 - 2 ; case 4
	.short _02239F1C - _02239F06 - 2 ; case 5
	.short _02239F1C - _02239F06 - 2 ; case 6
_02239F14:
	cmp r0, #1
	bne _02239F1C
	bl OS_Terminate
_02239F1C:
	ldr r0, _02239F24 ; =MOD83_0223CADC
	mov r1, #1
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_02239F24: .word MOD83_0223CADC
	thumb_func_end MOD83_02239EF4

	thumb_func_start MOD83_02239F28
MOD83_02239F28: ; 0x02239F28
	ldr r0, _02239F30 ; =MOD83_0223CADC
	mov r1, #1
	str r1, [r0, #8]
	bx lr
	.align 2, 0
_02239F30: .word MOD83_0223CADC
	thumb_func_end MOD83_02239F28

	thumb_func_start MOD83_02239F34
MOD83_02239F34: ; 0x02239F34
	push {r3, r4, r5, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	ldr r1, _0223A24C ; =0x0000260C
	add r4, r0, #0
	ldr r1, [r4, r1]
	cmp r1, #1
	bne _02239F4C
	bl MOD83_02239E40
	str r0, [r5]
_02239F4C:
	ldr r0, _0223A250 ; =0x00002620
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02239F62
	blx r0
	cmp r0, #1
	bne _02239F62
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
_02239F62:
	mov r3, #1
	ldr r0, [r5]
	lsl r3, r3, #0xc
	sub r0, r0, r3
	cmp r0, #0x12
	bls _02239F70
	b _0223A342
_02239F70:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02239F7C: ; jump table
	.short _02239FA2 - _02239F7C - 2 ; case 0
	.short _02239FB0 - _02239F7C - 2 ; case 1
	.short _02239FCC - _02239F7C - 2 ; case 2
	.short _02239FF4 - _02239F7C - 2 ; case 3
	.short _0223A046 - _02239F7C - 2 ; case 4
	.short _0223A05E - _02239F7C - 2 ; case 5
	.short _0223A09A - _02239F7C - 2 ; case 6
	.short _0223A0BE - _02239F7C - 2 ; case 7
	.short _0223A0F2 - _02239F7C - 2 ; case 8
	.short _0223A114 - _02239F7C - 2 ; case 9
	.short _0223A14E - _02239F7C - 2 ; case 10
	.short _0223A174 - _02239F7C - 2 ; case 11
	.short _0223A1E8 - _02239F7C - 2 ; case 12
	.short _0223A212 - _02239F7C - 2 ; case 13
	.short _0223A342 - _02239F7C - 2 ; case 14
	.short _0223A238 - _02239F7C - 2 ; case 15
	.short _0223A2D4 - _02239F7C - 2 ; case 16
	.short _0223A2F8 - _02239F7C - 2 ; case 17
	.short _0223A31E - _02239F7C - 2 ; case 18
_02239FA2:
	bl FUN_0202E49C
	bl FUN_02088858
	ldr r0, _0223A254 ; =0x00001001
	str r0, [r5]
	b _0223A342
_02239FB0:
	bl FUN_0202E4C8
	cmp r0, #0
	beq _0223A092
	ldr r0, _0223A258 ; =MOD83_02239DC0
	ldr r1, _0223A25C ; =MOD83_02239DE0
	bl MOD04_021DD968
	ldr r0, [r4, #4]
	bl FUN_02033310
	ldr r0, _0223A260 ; =0x00001002
	str r0, [r5]
	b _0223A342
_02239FCC:
	ldr r0, _0223A264 ; =0x000015E4
	mov r1, #2
	add r0, r4, r0
	mov r2, #1
	mov r3, #0x14
	bl MOD04_021DDEE0
	mov r0, #2
	bl MOD04_021DDE7C
	bl MOD04_021DDDCC
	bl FUN_02033E74
	ldr r0, _0223A268 ; =0x00001003
	mov r1, #0
	str r0, [r5]
	ldr r0, _0223A26C ; =0x0000261C
	str r1, [r4, r0]
	b _0223A342
_02239FF4:
	bl MOD04_021DDD7C
	cmp r0, #0
	bne _0223A002
	bl MOD04_021DDCE8
	b _0223A034
_0223A002:
	add r0, r4, #0
	bl MOD83_02239E80
	cmp r0, #1
	bne _0223A02C
	ldr r0, _0223A26C ; =0x0000261C
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _0223A020
	ldr r0, _0223A270 ; =MOD83_0223CADC
	mov r1, #3
	str r1, [r0, #4]
	ldr r0, _0223A274 ; =0x0000100D
	str r0, [r5]
	b _0223A034
_0223A020:
	ldr r1, _0223A278 ; =MOD04_021DD984
	add r0, r0, #4
	str r1, [r4, r0]
	ldr r0, _0223A27C ; =0x00001004
	str r0, [r5]
	b _0223A034
_0223A02C:
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
_0223A034:
	ldr r0, _0223A280 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _0223A092
	ldr r0, _0223A26C ; =0x0000261C
	mov r1, #1
	str r1, [r4, r0]
	b _0223A342
_0223A046:
	bl MOD04_021DE05C
	cmp r0, #0
	bne _0223A058
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A342
_0223A058:
	ldr r0, _0223A284 ; =0x00001005
	str r0, [r5]
	b _0223A342
_0223A05E:
	bl MOD04_021DDF4C
	cmp r0, #3
	bne _0223A06C
	ldr r0, _0223A288 ; =0x00001006
	str r0, [r5]
	b _0223A088
_0223A06C:
	cmp r0, #4
	bne _0223A07A
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A088
_0223A07A:
	cmp r0, #5
	bne _0223A088
	ldr r0, _0223A270 ; =MOD83_0223CADC
	mov r1, #3
	str r1, [r0, #4]
	ldr r0, _0223A274 ; =0x0000100D
	str r0, [r5]
_0223A088:
	ldr r0, _0223A280 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	bne _0223A094
_0223A092:
	b _0223A342
_0223A094:
	bl MOD04_021DDF40
	b _0223A342
_0223A09A:
	ldr r0, _0223A28C ; =MOD83_02239EF4
	ldr r1, _0223A290 ; =MOD83_0223B838
	ldr r2, _0223A294 ; =MOD83_0223B840
	bl MOD04_021DE45C
	cmp r0, #0
	bne _0223A0B2
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A342
_0223A0B2:
	ldr r2, _0223A298 ; =0x00001007
	add r0, r4, #0
	add r1, r5, #0
	bl MOD83_02239EA8
	b _0223A342
_0223A0BE:
	ldr r0, _0223A26C ; =0x0000261C
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0223A0D4
	add r0, r4, #0
	mov r1, #3
	add r2, r5, #0
	add r3, #0xc
	bl MOD83_02239EC8
	b _0223A342
_0223A0D4:
	ldr r0, _0223A29C ; =MOD83_0223B854
	add r1, r0, #0
	add r2, r0, #0
	bl MOD04_021DE3D0
	cmp r0, #0
	bne _0223A0EC
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A342
_0223A0EC:
	ldr r0, _0223A2A0 ; =0x00001008
	str r0, [r5]
	b _0223A342
_0223A0F2:
	ldr r0, _0223A2A4 ; =0x000015F8
	add r0, r4, r0
	bl MOD04_021DE3AC
	cmp r0, #0
	bne _0223A108
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A342
_0223A108:
	ldr r2, _0223A2A8 ; =0x00001009
	add r0, r4, #0
	add r1, r5, #0
	bl MOD83_02239EA8
	b _0223A342
_0223A114:
	ldr r0, _0223A2A4 ; =0x000015F8
	ldr r0, [r4, r0]
	cmp r0, #1
	beq _0223A12A
	add r0, r4, #0
	mov r1, #2
	add r2, r5, #0
	add r3, #0xd
	bl MOD83_02239EC8
	b _0223A342
_0223A12A:
	ldr r0, _0223A2AC ; =MOD83_0223CAEC
	mov r1, #0
	mov r2, #0xa
	bl MOD04_021DE364
	cmp r0, #0
	bne _0223A142
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A342
_0223A142:
	ldr r2, _0223A2B0 ; =0x0000100A
	add r0, r4, #0
	add r1, r5, #0
	bl MOD83_02239EA8
	b _0223A342
_0223A14E:
	ldr r1, _0223A2B4 ; =0x000015FC
	ldr r0, _0223A2AC ; =MOD83_0223CAEC
	add r1, r4, r1
	add r2, r3, #0
	bl MOD04_021DE330
	cmp r0, #0
	bne _0223A168
	add r0, r4, #0
	bl MOD83_02239DF0
	str r0, [r5]
	b _0223A342
_0223A168:
	ldr r0, _0223A2B8 ; =0x0000100B
	mov r1, #0
	str r0, [r5]
	ldr r0, _0223A2BC ; =0x00002608
	str r1, [r4, r0]
	b _0223A342
_0223A174:
	ldr r0, _0223A270 ; =MOD83_0223CADC
	ldr r0, [r0]
	cmp r0, #0
	bne _0223A1C4
	ldr r0, _0223A280 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _0223A194
	add r0, r4, #0
	mov r1, #3
	add r2, r5, #0
	add r3, #0xc
	bl MOD83_02239EC8
	b _0223A342
_0223A194:
	mov r1, #0x26
	lsl r1, r1, #8
	add r0, r4, r1
	add r1, r1, #4
	add r1, r4, r1
	bl MOD04_021DE2D0
	cmp r0, #1
	bne _0223A21A
	mov r1, #0x26
	lsl r1, r1, #8
	ldr r2, [r4, r1]
	add r1, r1, #4
	mov r0, #0x64
	ldr r1, [r4, r1]
	mul r0, r2
	bl _u32_div_f
	ldr r1, _0223A2BC ; =0x00002608
	ldr r2, [r4, r1]
	cmp r2, r0
	beq _0223A21A
	str r0, [r4, r1]
	b _0223A342
_0223A1C4:
	ldr r0, _0223A26C ; =0x0000261C
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _0223A1DA
	add r0, r4, #0
	mov r1, #1
	add r2, r5, #0
	add r3, #0xd
	bl MOD83_02239EC8
	b _0223A342
_0223A1DA:
	add r0, r4, #0
	mov r1, #3
	add r2, r5, #0
	add r3, #0xd
	bl MOD83_02239EC8
	b _0223A342
_0223A1E8:
	bl MOD04_021DE308
	cmp r0, #0
	bne _0223A1F6
	ldr r0, _0223A274 ; =0x0000100D
	str r0, [r5]
	b _0223A342
_0223A1F6:
	ldr r0, _0223A250 ; =0x00002620
	mov r1, #0
	str r1, [r4, r0]
	bl FUN_02033ED0
	bl FUN_02033364
	bl FUN_02088868
	bl FUN_0202E4F0
	ldr r0, _0223A270 ; =MOD83_0223CADC
	ldr r0, [r0, #4]
	pop {r3, r4, r5, pc}
_0223A212:
	bl MOD04_021DDB40
	cmp r0, #1
	beq _0223A21C
_0223A21A:
	b _0223A342
_0223A21C:
	ldr r0, _0223A250 ; =0x00002620
	mov r1, #0
	str r1, [r4, r0]
	bl FUN_02033ED0
	bl FUN_020332DC
	bl FUN_02088868
	bl FUN_0202E4F0
	ldr r0, _0223A270 ; =MOD83_0223CADC
	ldr r0, [r0, #4]
	pop {r3, r4, r5, pc}
_0223A238:
	ldr r0, _0223A270 ; =MOD83_0223CADC
	ldr r0, [r0, #0xc]
	cmp r0, #1
	beq _0223A242
	b _0223A342
_0223A242:
	add r0, r4, #0
	bl MOD83_022307B4
	ldr r0, _0223A2C0 ; =0x00002618
	b _0223A2C4
	.align 2, 0
_0223A24C: .word 0x0000260C
_0223A250: .word 0x00002620
_0223A254: .word 0x00001001
_0223A258: .word MOD83_02239DC0
_0223A25C: .word MOD83_02239DE0
_0223A260: .word 0x00001002
_0223A264: .word 0x000015E4
_0223A268: .word 0x00001003
_0223A26C: .word 0x0000261C
_0223A270: .word MOD83_0223CADC
_0223A274: .word 0x0000100D
_0223A278: .word MOD04_021DD984
_0223A27C: .word 0x00001004
_0223A280: .word gMain
_0223A284: .word 0x00001005
_0223A288: .word 0x00001006
_0223A28C: .word MOD83_02239EF4
_0223A290: .word MOD83_0223B838
_0223A294: .word MOD83_0223B840
_0223A298: .word 0x00001007
_0223A29C: .word MOD83_0223B854
_0223A2A0: .word 0x00001008
_0223A2A4: .word 0x000015F8
_0223A2A8: .word 0x00001009
_0223A2AC: .word MOD83_0223CAEC
_0223A2B0: .word 0x0000100A
_0223A2B4: .word 0x000015FC
_0223A2B8: .word 0x0000100B
_0223A2BC: .word 0x00002608
_0223A2C0: .word 0x00002618
_0223A2C4:
	ldr r0, [r4, r0]
	cmp r0, #6
	bne _0223A2CE
	bl MOD04_021DDBBC
_0223A2CE:
	ldr r0, _0223A348 ; =0x00001010
	str r0, [r5]
	b _0223A342
_0223A2D4:
	ldr r0, _0223A34C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0223A342
	ldr r0, _0223A350 ; =0x00002620
	mov r1, #0
	str r1, [r4, r0]
	bl MOD04_021DD6F0
	bl FUN_020332DC
	bl FUN_02088868
	bl FUN_0202E4F0
	mov r0, #4
	pop {r3, r4, r5, pc}
_0223A2F8:
	ldr r0, _0223A354 ; =MOD83_0223CADC
	ldr r1, [r0]
	cmp r1, #1
	bne _0223A30C
	mov r1, #0
	str r1, [r0]
	ldr r0, _0223A358 ; =0x000015F4
	ldr r0, [r4, r0]
	str r0, [r5]
	b _0223A342
_0223A30C:
	ldr r0, _0223A34C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _0223A342
	ldr r0, _0223A35C ; =0x0000261C
	mov r1, #1
	str r1, [r4, r0]
	b _0223A342
_0223A31E:
	ldr r0, _0223A354 ; =MOD83_0223CADC
	ldr r1, [r0, #8]
	cmp r1, #1
	bne _0223A332
	mov r1, #0
	str r1, [r0, #8]
	ldr r0, _0223A358 ; =0x000015F4
	ldr r0, [r4, r0]
	str r0, [r5]
	b _0223A342
_0223A332:
	ldr r0, _0223A34C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _0223A342
	ldr r0, _0223A35C ; =0x0000261C
	mov r1, #1
	str r1, [r4, r0]
_0223A342:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0223A348: .word 0x00001010
_0223A34C: .word gMain
_0223A350: .word 0x00002620
_0223A354: .word MOD83_0223CADC
_0223A358: .word 0x000015F4
_0223A35C: .word 0x0000261C
	thumb_func_end MOD83_02239F34

	.rodata
	.global MOD83_0223A360
MOD83_0223A360: ; 0x0223A360
	.word MOD83_0222E48C, MOD83_0222E540, MOD83_0222E850, 0xFFFFFFFF

	.global MOD83_0223A370
MOD83_0223A370: ; 0x0223A370
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A380
MOD83_0223A380: ; 0x0223A380
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD83_0223A3A8
MOD83_0223A3A8: ; 0x0223A3A8
	.word MOD83_0222EDF8, MOD83_0222EE8C, MOD83_0222F048, 0xFFFFFFFF

	.global MOD83_0223A3B8
MOD83_0223A3B8: ; 0x0223A3B8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A3C8
MOD83_0223A3C8: ; 0x0223A3C8
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD83_0223A3F0
MOD83_0223A3F0: ; 0x0223A3F0
	.word MOD83_0222F984, MOD83_0222F9B0, MOD83_0222F9B8, MOD83_0222F9C4
	.word FUN_0202DA80, 0x00000000

	.global MOD83_0223A408
MOD83_0223A408: ; 0x0223A408
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A418
MOD83_0223A418: ; 0x0223A418
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A434
MOD83_0223A434: ; 0x0223A434
	.word MOD83_02230954, MOD83_02230A10, MOD83_0223137C, 0xFFFFFFFF

	.global MOD83_0223A444
MOD83_0223A444: ; 0x0223A444
	.word MOD83_022323A8, MOD83_02232788, MOD83_022330A4, 0xFFFFFFFF

	.global MOD83_0223A454
MOD83_0223A454: ; 0x0223A454
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A464
MOD83_0223A464: ; 0x0223A464
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x03, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A480
MOD83_0223A480: ; 0x0223A480
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A49C
MOD83_0223A49C: ; 0x0223A49C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A4B8
MOD83_0223A4B8: ; 0x0223A4B8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A4D4
MOD83_0223A4D4: ; 0x0223A4D4
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD83_0223A4FC
MOD83_0223A4FC: ; 0x0223A4FC
	.word MOD83_02236764, MOD83_02236804, MOD83_02236DD0, 0xFFFFFFFF

	.global MOD83_0223A50C
MOD83_0223A50C: ; 0x0223A50C
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x4E, 0x00, 0x00, 0x00

	.global MOD83_0223A51C
MOD83_0223A51C: ; 0x0223A51C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A52C
MOD83_0223A52C: ; 0x0223A52C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A548
MOD83_0223A548: ; 0x0223A548
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A564
MOD83_0223A564: ; 0x0223A564
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A580
MOD83_0223A580: ; 0x0223A580
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A59C
MOD83_0223A59C: ; 0x0223A59C
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD83_0223A5C4
MOD83_0223A5C4: ; 0x0223A5C4
	.byte 0x41, 0x58, 0x56, 0x4A, 0x00, 0x00, 0x01, 0x00, 0x41, 0x58, 0x56, 0x45, 0x00, 0x00, 0x02, 0x00
	.byte 0x41, 0x58, 0x56, 0x46, 0x00, 0x00, 0x03, 0x00, 0x41, 0x58, 0x56, 0x44, 0x00, 0x00, 0x05, 0x00
	.byte 0x41, 0x58, 0x56, 0x53, 0x00, 0x00, 0x07, 0x00, 0x41, 0x58, 0x56, 0x49, 0x00, 0x00, 0x04, 0x00
	.byte 0x41, 0x58, 0x50, 0x4A, 0x00, 0x01, 0x01, 0x00, 0x41, 0x58, 0x50, 0x45, 0x00, 0x01, 0x02, 0x00
	.byte 0x41, 0x58, 0x50, 0x46, 0x00, 0x01, 0x03, 0x00, 0x41, 0x58, 0x50, 0x44, 0x00, 0x01, 0x05, 0x00
	.byte 0x41, 0x58, 0x50, 0x53, 0x00, 0x01, 0x07, 0x00, 0x41, 0x58, 0x50, 0x49, 0x00, 0x01, 0x04, 0x00
	.byte 0x42, 0x50, 0x52, 0x4A, 0x01, 0x03, 0x01, 0x00, 0x42, 0x50, 0x52, 0x45, 0x01, 0x03, 0x02, 0x00
	.byte 0x42, 0x50, 0x52, 0x46, 0x01, 0x03, 0x03, 0x00, 0x42, 0x50, 0x52, 0x44, 0x01, 0x03, 0x05, 0x00
	.byte 0x42, 0x50, 0x52, 0x53, 0x01, 0x03, 0x07, 0x00, 0x42, 0x50, 0x52, 0x49, 0x01, 0x03, 0x04, 0x00
	.byte 0x42, 0x50, 0x47, 0x4A, 0x01, 0x02, 0x01, 0x00, 0x42, 0x50, 0x47, 0x45, 0x01, 0x02, 0x02, 0x00
	.byte 0x42, 0x50, 0x47, 0x46, 0x01, 0x02, 0x03, 0x00, 0x42, 0x50, 0x47, 0x44, 0x01, 0x02, 0x05, 0x00
	.byte 0x42, 0x50, 0x47, 0x53, 0x01, 0x02, 0x07, 0x00, 0x42, 0x50, 0x47, 0x49, 0x01, 0x02, 0x04, 0x00
	.byte 0x42, 0x50, 0x45, 0x4A, 0x02, 0x04, 0x01, 0x00, 0x42, 0x50, 0x45, 0x45, 0x02, 0x04, 0x02, 0x00
	.byte 0x42, 0x50, 0x45, 0x46, 0x02, 0x04, 0x03, 0x00, 0x42, 0x50, 0x45, 0x44, 0x02, 0x04, 0x05, 0x00
	.byte 0x42, 0x50, 0x45, 0x53, 0x02, 0x04, 0x07, 0x00, 0x42, 0x50, 0x45, 0x49, 0x02, 0x04, 0x04, 0x00

	.global MOD83_0223A6B4
MOD83_0223A6B4: ; 0x0223A6B4
	.byte 0xC8, 0x7E, 0x66, 0x71, 0x46, 0x0B, 0xE6, 0x6F, 0x17, 0x8A, 0x5C, 0x7D, 0xEA, 0xE1, 0x93, 0xFD
	.byte 0xEE, 0xFA, 0x99, 0x84, 0xFE, 0x35, 0x02, 0xB9, 0x7F, 0x4F, 0xF1, 0x19, 0x74, 0xA2, 0x0F, 0x65
	.byte 0x8A, 0x9C, 0x44, 0x81, 0x0C, 0x1F, 0x94, 0xE4, 0xC0, 0xB6, 0xD7, 0x20, 0xEE, 0x11, 0x9A, 0x8D
	.byte 0x27, 0x33, 0x9B, 0x7B, 0x02, 0xE9, 0x33, 0x11, 0xDC, 0xCF, 0x72, 0xD9, 0xA8, 0x78, 0x12, 0x8C
	.byte 0x3B, 0x60, 0xD5, 0x24, 0xB8, 0xD9, 0xFC, 0x8D, 0x15, 0xBA, 0x0B, 0x90, 0xA3, 0xBD, 0x3A, 0xE4
	.byte 0x01, 0x18, 0xBA, 0xF9, 0x65, 0xA5, 0x15, 0x37, 0xDC, 0x7A, 0x48, 0x5C, 0x3A, 0x55, 0x35, 0x43
	.byte 0xE2, 0xC6, 0x66, 0xBA, 0x21, 0xEA, 0x67, 0x2E, 0xA8, 0x29, 0x03, 0xD7, 0x1F, 0x0F, 0xC6, 0xDE
	.byte 0x1B, 0xE2, 0xA1, 0xCA, 0x21, 0x51, 0xFE, 0xB9, 0x68, 0x17, 0x3C, 0xEB, 0x04, 0x54, 0xE0, 0xBD

	.global MOD83_0223A734
MOD83_0223A734: ; 0x0223A734
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A744
MOD83_0223A744: ; 0x0223A744
	.byte 0x00, 0x00, 0x01, 0x01, 0x02, 0x01, 0x03, 0x02, 0x04, 0x03, 0x05, 0x02, 0x06, 0x02, 0x07, 0x00
	.byte 0x08, 0x05, 0x09, 0x05, 0x0A, 0x05, 0x0B, 0x04, 0xFF, 0x00, 0x00, 0x00

	.global MOD83_0223A760
MOD83_0223A760: ; 0x0223A760
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.global MOD83_0223A780
MOD83_0223A780: ; 0x0223A780
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A784
MOD83_0223A784: ; 0x0223A784
	.byte 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00

	.global MOD83_0223A794
MOD83_0223A794: ; 0x0223A794
	.byte 0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.byte 0x65, 0x02, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A7B0
MOD83_0223A7B0: ; 0x0223A7B0
	.byte 0x81, 0x53, 0x83, 0x53, 0x85, 0x53, 0x87, 0x53, 0x89, 0x53, 0x8B, 0x53, 0x8D, 0x53, 0x8F, 0x53
	.byte 0x91, 0x53, 0x93, 0x53, 0x95, 0x53, 0x97, 0x53, 0x99, 0x53, 0x9B, 0x53, 0x9D, 0x53, 0x9F, 0x53
	.byte 0x9D, 0x53, 0x9B, 0x53, 0x99, 0x53, 0x97, 0x53, 0x95, 0x53, 0x93, 0x53, 0x91, 0x53, 0x8F, 0x53
	.byte 0x8D, 0x53, 0x8B, 0x53, 0x89, 0x53, 0x87, 0x53, 0x85, 0x53, 0x83, 0x53, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A7F0
MOD83_0223A7F0: ; 0x0223A7F0
	.byte 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD83_0223A804
MOD83_0223A804: ; 0x0223A804
	.byte 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00

	.global MOD83_0223A818
MOD83_0223A818: ; 0x0223A818
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223A82C
MOD83_0223A82C: ; 0x0223A82C
	.byte 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.global MOD83_0223A840
MOD83_0223A840: ; 0x0223A840
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00

	.global MOD83_0223A854
MOD83_0223A854: ; 0x0223A854
	.byte 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD83_0223A85C
MOD83_0223A85C: ; 0x0223A85C
	.word 0x00, MOD83_0222DD24, 0x02, 0x02
	.word 0x01, 0x00000000, 0x03, 0x02
	.word 0x02, MOD83_0222DF40, 0x04, 0x02
	.word 0x03, MOD83_0222DFEC, 0x05, 0x02
	.word 0x00, MOD83_0222DECC, 0x06, 0x02
	.word 0x0A, MOD83_0222E048, 0x07, 0x02
	.word 0x0B, MOD83_0222E098

	.global MOD83_0223A8C4
MOD83_0223A8C4: ; 0x0223A8C4
	.asciz "data/eoo.dat"

	.balign 4
	.global MOD83_0223A8D4
MOD83_0223A8D4: ; 0x0223A8D4
	.byte 0x16, 0x01, 0x15, 0x00
	.word MOD83_0223B870, MOD83_0223B860

	.global MOD83_0223A8E0
MOD83_0223A8E0: ; 0x0223A8E0
	.byte 0x00, 0x00, 0xFF, 0xFF, 0x21, 0x00, 0xE1, 0x00, 0x23, 0x00, 0xC0, 0x01, 0x25, 0x00, 0xD2, 0x01
	.byte 0x27, 0x00, 0xEA, 0x00, 0x28, 0x00, 0xEB, 0x00, 0x29, 0x00, 0xBF, 0x01, 0x2A, 0x00, 0xBD, 0x01
	.byte 0x2B, 0x00, 0xAD, 0x01, 0x2C, 0x00, 0xBE, 0x01, 0x2E, 0x00, 0xB1, 0x01, 0x30, 0x00, 0xA2, 0x00
	.byte 0x31, 0x00, 0xA3, 0x00, 0x32, 0x00, 0xA4, 0x00, 0x33, 0x00, 0xA5, 0x00, 0x34, 0x00, 0xA6, 0x00
	.byte 0x35, 0x00, 0xA7, 0x00, 0x36, 0x00, 0xA8, 0x00, 0x37, 0x00, 0xA9, 0x00, 0x38, 0x00, 0xAA, 0x00
	.byte 0x39, 0x00, 0xAB, 0x00, 0x3A, 0x00, 0xC4, 0x01, 0x3B, 0x00, 0xC5, 0x01, 0x3C, 0x00, 0xEC, 0x00
	.byte 0x3E, 0x00, 0xED, 0x00, 0x3F, 0x00, 0xAC, 0x01, 0x41, 0x00, 0xAC, 0x00, 0x42, 0x00, 0xAD, 0x00
	.byte 0x43, 0x00, 0xAE, 0x00, 0x44, 0x00, 0xAF, 0x00, 0x45, 0x00, 0xB0, 0x00, 0x46, 0x00, 0xB1, 0x00
	.byte 0x47, 0x00, 0xB2, 0x00, 0x48, 0x00, 0xB3, 0x00, 0x49, 0x00, 0xB4, 0x00, 0x4A, 0x00, 0xB5, 0x00
	.byte 0x4B, 0x00, 0xB6, 0x00, 0x4C, 0x00, 0xB7, 0x00, 0x4D, 0x00, 0xB8, 0x00, 0x4E, 0x00, 0xB9, 0x00
	.byte 0x4F, 0x00, 0xBA, 0x00, 0x50, 0x00, 0xBB, 0x00, 0x51, 0x00, 0xBC, 0x00, 0x52, 0x00, 0xBD, 0x00
	.byte 0x53, 0x00, 0xBE, 0x00, 0x54, 0x00, 0xBF, 0x00, 0x55, 0x00, 0xC0, 0x00, 0x56, 0x00, 0xC1, 0x00
	.byte 0x57, 0x00, 0xC2, 0x00, 0x58, 0x00, 0xC3, 0x00, 0x59, 0x00, 0xC4, 0x00, 0x5A, 0x00, 0xC5, 0x00
	.byte 0x61, 0x00, 0xC6, 0x00, 0x62, 0x00, 0xC7, 0x00, 0x63, 0x00, 0xC8, 0x00, 0x64, 0x00, 0xC9, 0x00
	.byte 0x65, 0x00, 0xCA, 0x00, 0x66, 0x00, 0xCB, 0x00, 0x67, 0x00, 0xCC, 0x00, 0x68, 0x00, 0xCD, 0x00
	.byte 0x69, 0x00, 0xCE, 0x00, 0x6A, 0x00, 0xCF, 0x00, 0x6B, 0x00, 0xD0, 0x00, 0x6C, 0x00, 0xD1, 0x00
	.byte 0x6D, 0x00, 0xD2, 0x00, 0x6E, 0x00, 0xD3, 0x00, 0x6F, 0x00, 0xD4, 0x00, 0x70, 0x00, 0xD5, 0x00
	.byte 0x71, 0x00, 0xD6, 0x00, 0x72, 0x00, 0xD7, 0x00, 0x73, 0x00, 0xD8, 0x00, 0x74, 0x00, 0xD9, 0x00
	.byte 0x75, 0x00, 0xDA, 0x00, 0x76, 0x00, 0xDB, 0x00, 0x77, 0x00, 0xDC, 0x00, 0x78, 0x00, 0xDD, 0x00
	.byte 0x79, 0x00, 0xDE, 0x00, 0x7A, 0x00, 0xDF, 0x00, 0x81, 0x00, 0x02, 0x00, 0x82, 0x00, 0x03, 0x00
	.byte 0x83, 0x00, 0x04, 0x00, 0x84, 0x00, 0x05, 0x00, 0x85, 0x00, 0x06, 0x00, 0x86, 0x00, 0x07, 0x00
	.byte 0x87, 0x00, 0x08, 0x00, 0x88, 0x00, 0x09, 0x00, 0x89, 0x00, 0x0A, 0x00, 0x8A, 0x00, 0x0B, 0x00
	.byte 0x8B, 0x00, 0x0C, 0x00, 0x8C, 0x00, 0x0D, 0x00, 0x8D, 0x00, 0x0E, 0x00, 0x8E, 0x00, 0x0F, 0x00
	.byte 0x8F, 0x00, 0x10, 0x00, 0x90, 0x00, 0x11, 0x00, 0x91, 0x00, 0x12, 0x00, 0x92, 0x00, 0x13, 0x00
	.byte 0x93, 0x00, 0x14, 0x00, 0x94, 0x00, 0x15, 0x00, 0x95, 0x00, 0x16, 0x00, 0x96, 0x00, 0x17, 0x00
	.byte 0x97, 0x00, 0x18, 0x00, 0x98, 0x00, 0x19, 0x00, 0x99, 0x00, 0x1A, 0x00, 0x9A, 0x00, 0x1B, 0x00
	.byte 0x9B, 0x00, 0x1C, 0x00, 0x9C, 0x00, 0x1D, 0x00, 0x9D, 0x00, 0x1E, 0x00, 0x9E, 0x00, 0x1F, 0x00
	.byte 0x9F, 0x00, 0x20, 0x00, 0xA0, 0x00, 0x21, 0x00, 0xA1, 0x00, 0x22, 0x00, 0xA2, 0x00, 0x23, 0x00
	.byte 0xA3, 0x00, 0x24, 0x00, 0xA4, 0x00, 0x25, 0x00, 0xA5, 0x00, 0x26, 0x00, 0xA6, 0x00, 0x27, 0x00
	.byte 0xA7, 0x00, 0x28, 0x00, 0xA8, 0x00, 0x29, 0x00, 0xA9, 0x00, 0x2A, 0x00, 0xAA, 0x00, 0x2B, 0x00
	.byte 0xAB, 0x00, 0x2C, 0x00, 0xAC, 0x00, 0x2D, 0x00, 0xAD, 0x00, 0x2E, 0x00, 0xAE, 0x00, 0x2F, 0x00
	.byte 0xAF, 0x00, 0x30, 0x00, 0xB0, 0x00, 0x31, 0x00, 0xB1, 0x00, 0x32, 0x00, 0xB2, 0x00, 0x33, 0x00
	.byte 0xB3, 0x00, 0x34, 0x00, 0xB4, 0x00, 0x35, 0x00, 0xB5, 0x00, 0x36, 0x00, 0xB6, 0x00, 0x37, 0x00
	.byte 0xB7, 0x00, 0x38, 0x00, 0xB8, 0x00, 0x39, 0x00, 0xB9, 0x00, 0x3A, 0x00, 0xBA, 0x00, 0x3B, 0x00
	.byte 0xBB, 0x00, 0x3C, 0x00, 0xBC, 0x00, 0x3D, 0x00, 0xBD, 0x00, 0x3E, 0x00, 0xBE, 0x00, 0x3F, 0x00
	.byte 0xBF, 0x00, 0x40, 0x00, 0xC0, 0x00, 0x41, 0x00, 0xC1, 0x00, 0x42, 0x00, 0xC2, 0x00, 0x43, 0x00
	.byte 0xC3, 0x00, 0x44, 0x00, 0xC4, 0x00, 0x45, 0x00, 0xC5, 0x00, 0x46, 0x00, 0xC6, 0x00, 0x47, 0x00
	.byte 0xC7, 0x00, 0x48, 0x00, 0xC8, 0x00, 0x49, 0x00, 0xC9, 0x00, 0x4A, 0x00, 0xCA, 0x00, 0x4B, 0x00
	.byte 0xCB, 0x00, 0x4C, 0x00, 0xCC, 0x00, 0x4D, 0x00, 0xCD, 0x00, 0x4E, 0x00, 0xCF, 0x00, 0x4F, 0x00
	.byte 0xD2, 0x00, 0x50, 0x00, 0xD3, 0x00, 0x51, 0x00, 0xE1, 0x00, 0x52, 0x00, 0xE2, 0x00, 0x53, 0x00
	.byte 0xE3, 0x00, 0x54, 0x00, 0xE4, 0x00, 0x55, 0x00, 0xE5, 0x00, 0x56, 0x00, 0xE6, 0x00, 0x57, 0x00
	.byte 0xE7, 0x00, 0x58, 0x00, 0xE8, 0x00, 0x59, 0x00, 0xE9, 0x00, 0x5A, 0x00, 0xEA, 0x00, 0x5B, 0x00
	.byte 0xEB, 0x00, 0x5C, 0x00, 0xEC, 0x00, 0x5D, 0x00, 0xED, 0x00, 0x5E, 0x00, 0xEE, 0x00, 0x5F, 0x00
	.byte 0xEF, 0x00, 0x60, 0x00, 0xF0, 0x00, 0x61, 0x00, 0xF1, 0x00, 0x62, 0x00, 0xF2, 0x00, 0x63, 0x00
	.byte 0xF3, 0x00, 0x64, 0x00, 0xF4, 0x00, 0x65, 0x00, 0xF5, 0x00, 0x66, 0x00, 0xF6, 0x00, 0x67, 0x00
	.byte 0xF7, 0x00, 0x68, 0x00, 0xF8, 0x00, 0x69, 0x00, 0xF9, 0x00, 0x6A, 0x00, 0xFA, 0x00, 0x6B, 0x00
	.byte 0xFB, 0x00, 0x6C, 0x00, 0xFC, 0x00, 0x6D, 0x00, 0xFD, 0x00, 0x6E, 0x00, 0xFE, 0x00, 0x6F, 0x00
	.byte 0xFF, 0x00, 0x70, 0x00, 0x00, 0x01, 0x71, 0x00, 0x01, 0x01, 0x72, 0x00, 0x02, 0x01, 0x73, 0x00
	.byte 0x03, 0x01, 0x74, 0x00, 0x04, 0x01, 0x75, 0x00, 0x05, 0x01, 0x76, 0x00, 0x06, 0x01, 0x77, 0x00
	.byte 0x07, 0x01, 0x78, 0x00, 0x08, 0x01, 0x79, 0x00, 0x09, 0x01, 0x7A, 0x00, 0x0A, 0x01, 0x7B, 0x00
	.byte 0x0B, 0x01, 0x7C, 0x00, 0x0C, 0x01, 0x7D, 0x00, 0x0D, 0x01, 0x7E, 0x00, 0x0E, 0x01, 0x7F, 0x00
	.byte 0x0F, 0x01, 0x80, 0x00, 0x10, 0x01, 0x81, 0x00, 0x11, 0x01, 0x82, 0x00, 0x12, 0x01, 0x83, 0x00
	.byte 0x13, 0x01, 0x84, 0x00, 0x14, 0x01, 0x85, 0x00, 0x15, 0x01, 0x86, 0x00, 0x16, 0x01, 0x87, 0x00
	.byte 0x17, 0x01, 0x88, 0x00, 0x18, 0x01, 0x89, 0x00, 0x19, 0x01, 0x8A, 0x00, 0x1A, 0x01, 0x8B, 0x00
	.byte 0x1B, 0x01, 0x8C, 0x00, 0x1C, 0x01, 0x8D, 0x00, 0x1D, 0x01, 0x8E, 0x00, 0x1E, 0x01, 0x8F, 0x00
	.byte 0x1F, 0x01, 0x90, 0x00, 0x20, 0x01, 0x91, 0x00, 0x21, 0x01, 0x92, 0x00, 0x22, 0x01, 0x93, 0x00
	.byte 0x23, 0x01, 0x94, 0x00, 0x24, 0x01, 0x95, 0x00, 0x25, 0x01, 0x96, 0x00, 0x26, 0x01, 0x97, 0x00
	.byte 0x27, 0x01, 0x98, 0x00, 0x28, 0x01, 0x99, 0x00, 0x29, 0x01, 0x9A, 0x00, 0x2A, 0x01, 0x9B, 0x00
	.byte 0x2B, 0x01, 0x9C, 0x00, 0x2C, 0x01, 0x9D, 0x00, 0x2D, 0x01, 0x9E, 0x00, 0x2F, 0x01, 0x9F, 0x00
	.byte 0x32, 0x01, 0xA0, 0x00, 0x33, 0x01, 0xA1, 0x00, 0x40, 0x01, 0xEA, 0x00, 0x41, 0x01, 0xEB, 0x00
	.byte 0x42, 0x01, 0xE8, 0x00, 0x43, 0x01, 0xE9, 0x00, 0x46, 0x01, 0xE6, 0x00, 0x47, 0x01, 0xE5, 0x00
	.byte 0x48, 0x01, 0xEE, 0x00, 0x49, 0x01, 0xEF, 0x00, 0x4A, 0x01, 0xE4, 0x00, 0x4B, 0x01, 0x12, 0x01
	.byte 0x4D, 0x01, 0x1C, 0x01, 0x4E, 0x01, 0x1E, 0x01, 0x4F, 0x01, 0x1D, 0x01, 0x50, 0x01, 0x1B, 0x01
	.byte 0x7C, 0x01, 0x9F, 0x01, 0x7D, 0x01, 0xA0, 0x01, 0x80, 0x01, 0x5F, 0x01, 0x81, 0x01, 0x60, 0x01
	.byte 0x82, 0x01, 0x61, 0x01, 0x84, 0x01, 0x63, 0x01, 0x87, 0x01, 0x66, 0x01, 0x89, 0x01, 0x68, 0x01
	.byte 0x8A, 0x01, 0x69, 0x01, 0x8B, 0x01, 0x6A, 0x01, 0x8C, 0x01, 0x6B, 0x01, 0x8D, 0x01, 0x6C, 0x01
	.byte 0x8E, 0x01, 0x6D, 0x01, 0x8F, 0x01, 0x6E, 0x01, 0x93, 0x01, 0x72, 0x01, 0x94, 0x01, 0x73, 0x01
	.byte 0x96, 0x01, 0x75, 0x01, 0x9A, 0x01, 0x79, 0x01, 0x9B, 0x01, 0x7A, 0x01, 0x9C, 0x01, 0x7B, 0x01
	.byte 0x9F, 0x01, 0x7E, 0x01, 0xA0, 0x01, 0x7F, 0x01, 0xA1, 0x01, 0x80, 0x01, 0xA2, 0x01, 0x81, 0x01
	.byte 0xA4, 0x01, 0x83, 0x01, 0xA7, 0x01, 0x86, 0x01, 0xA9, 0x01, 0x88, 0x01, 0xAA, 0x01, 0x89, 0x01
	.byte 0xAB, 0x01, 0x8A, 0x01, 0xAC, 0x01, 0x8B, 0x01, 0xAD, 0x01, 0x8C, 0x01, 0xAE, 0x01, 0x8D, 0x01
	.byte 0xAF, 0x01, 0x8E, 0x01, 0xB3, 0x01, 0x92, 0x01, 0xB4, 0x01, 0x93, 0x01, 0xB6, 0x01, 0x95, 0x01
	.byte 0xBA, 0x01, 0x99, 0x01, 0xBB, 0x01, 0x9A, 0x01, 0xBC, 0x01, 0x9B, 0x01

	.global MOD83_0223AD6C
MOD83_0223AD6C: ; 0x0223AD6C
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223AD98
MOD83_0223AD98: ; 0x0223AD98
	.word 0x12, MOD83_022300AC
	.word 0x13, MOD83_0222FDE8

	.global MOD83_0223ADA8
MOD83_0223ADA8: ; 0x0223ADA8
	.word 0x12, MOD83_02230010
	.word 0x13, MOD83_0222FDE8

	.global MOD83_0223ADB8
MOD83_0223ADB8: ; 0x0223ADB8
	.word 0x12, MOD83_02230048
	.word 0x13, MOD83_02230084

	.global MOD83_0223ADC8
MOD83_0223ADC8: ; 0x0223ADC8
	.word 0x12, MOD83_0222FB5C, 0x13, MOD83_0222FDE8

	.global MOD83_0223ADD8
MOD83_0223ADD8: ; 0x0223ADD8
	.word 0x12, MOD83_0222FBBC
	.word 0x13, MOD83_0222FFD8
	.word 0x0C, MOD83_02230118
	.word 0x0D, MOD83_0223019C
	.word 0x0E, MOD83_022301D4

	.global MOD83_0223AE00
MOD83_0223AE00: ; 0x0223AE00
	.word 0x00, MOD83_02239414, 0x00, 0x00
	.byte 0x00, 0x00, 0x03, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223AE20
MOD83_0223AE20: ; 0x0223AE20
	.word 0x0F, MOD83_0222FE24
	.word 0x14, MOD83_0222FF10
	.word 0x10, MOD83_0222FEA0
	.word 0x11, MOD83_022300F8

	.global MOD83_0223AE40
MOD83_0223AE40: ; 0x0223AE40
	.word 0x40, MOD83_02231930
	.word 0x41, MOD83_022319D0

	.global MOD83_0223AE50
MOD83_0223AE50: ; 0x0223AE50
	.byte 0x40, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
	.word 0x41, MOD83_022319D0

	.global MOD83_0223AE60
MOD83_0223AE60: ; 0x0223AE60
	.byte 0x40, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00
	.word 0x41, MOD83_022319D0
	.byte 0x2A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.word 0x2B, MOD83_022318B0
	.word 0x2C, MOD83_022318E0
	.byte 0x2D, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00


	.global MOD83_0223AE90
MOD83_0223AE90: ; 0x0223AE90
	.word 0x00, MOD83_02239414
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x04, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223AEB0
MOD83_0223AEB0: ; 0x0223AEB0
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x24, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0F, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x28, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0xA1, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0F, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x4D, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x31, 0x00, 0x00, 0x00, 0x1D, 0x1B, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x85, 0x1B, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x29, 0x00, 0x00, 0x00, 0xD9, 0x1B, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00
	.byte 0x24, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x59, 0x1C, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x4D, 0x1D, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x61, 0x1D, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x34, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x37, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x39, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x3A, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x38, 0x00, 0x00, 0x00, 0x9D, 0x1D, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x00
	.byte 0x3B, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x00
	.byte 0x3C, 0x00, 0x00, 0x00, 0x49, 0x1A, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223B240
MOD83_0223B240: ; 0x0223B240
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x01, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD83_0223B280
MOD83_0223B280: ; 0x0223B280
	.byte 0x00, 0x02, 0x01, 0x03, 0x04, 0x05, 0x00, 0x00

	.global MOD83_0223B288
MOD83_0223B288: ; 0x0223B288
	.word 0x00
	.ifdef DIAMOND
	.word 0x14
	.word 0x12
	.word 0x16
	.word 0x18
	.word 0x1A
	.else
	.word 0x15
	.word 0x13
	.word 0x17
	.word 0x19
	.word 0x1B
	.endif

	.global MOD83_0223B2A0
MOD83_0223B2A0: ; 0x0223B2A0
	.word 0x00000000, 0x00000001, 0x00000000, 0x00000002
	.word 0x00000003, 0x00000004

	.global MOD83_0223B2B8
MOD83_0223B2B8: ; 0x0223B2B8
	.word 0x0000000F, 0x00000013, 0x00000039, 0x00000046
	.word 0x00000094, 0x000000F9, 0x0000007F, 0x00000123

	.global MOD83_0223B2D8
MOD83_0223B2D8: ; 0x0223B2D8
	.word 0x00000000, 0x00000025, 0x0000001F, 0x00000020
	.word 0x00000020, 0x00000005, 0x00000007, 0x00000021

	.global MOD83_InvalidItemIds
MOD83_InvalidItemIds: ; 0x0223B2F8
	.short 0x0005 ; RS_ITEM_SAFARI_BALL
	.short 0x0034 ; RS_ITEM_034
	.short 0x0035 ; RS_ITEM_035
	.short 0x0036 ; RS_ITEM_036
	.short 0x0037 ; RS_ITEM_037
	.short 0x0038 ; RS_ITEM_038
	.short 0x0039 ; RS_ITEM_039
	.short 0x003A ; RS_ITEM_03A
	.short 0x003B ; RS_ITEM_03B
	.short 0x003C ; RS_ITEM_03C
	.short 0x003D ; RS_ITEM_03D
	.short 0x003E ; RS_ITEM_03E
	.short 0x0048 ; RS_ITEM_048
	.short 0x0052 ; RS_ITEM_052
	.short 0x0057 ; RS_ITEM_057
	.short 0x0058 ; RS_ITEM_058
	.short 0x0059 ; RS_ITEM_059
	.short 0x005A ; RS_ITEM_05A
	.short 0x005B ; RS_ITEM_05B
	.short 0x005C ; RS_ITEM_05C
	.short 0x0063 ; RS_ITEM_063
	.short 0x0064 ; RS_ITEM_064
	.short 0x0065 ; RS_ITEM_065
	.short 0x0066 ; RS_ITEM_066
	.short 0x0069 ; RS_ITEM_069
	.short 0x0070 ; RS_ITEM_070
	.short 0x0071 ; RS_ITEM_071
	.short 0x0072 ; RS_ITEM_072
	.short 0x0073 ; RS_ITEM_073
	.short 0x0074 ; RS_ITEM_074
	.short 0x0075 ; RS_ITEM_075
	.short 0x0076 ; RS_ITEM_076
	.short 0x0077 ; RS_ITEM_077
	.short 0x0078 ; RS_ITEM_078
	.short 0x0079 ; RS_ITEM_ORANGE_MAIL
	.short 0x007A ; RS_ITEM_HARBOR_MAIL
	.short 0x007B ; RS_ITEM_GLITTER_MAIL
	.short 0x007C ; RS_ITEM_MECH_MAIL
	.short 0x007D ; RS_ITEM_WOOD_MAIL
	.short 0x007E ; RS_ITEM_WAVE_MAIL
	.short 0x007F ; RS_ITEM_BEAD_MAIL
	.short 0x0080 ; RS_ITEM_SHADOW_MAIL
	.short 0x0081 ; RS_ITEM_TROPIC_MAIL
	.short 0x0082 ; RS_ITEM_DREAM_MAIL
	.short 0x0083 ; RS_ITEM_FAB_MAIL
	.short 0x0084 ; RS_ITEM_RETRO_MAIL
	.short 0x00B0 ; RS_ITEM_0B0
	.short 0x00B1 ; RS_ITEM_0B1
	.short 0x00B2 ; RS_ITEM_0B2
	.short 0x00E2 ; RS_ITEM_0E2
	.short 0x00E3 ; RS_ITEM_0E3
	.short 0x00E4 ; RS_ITEM_0E4
	.short 0x00E5 ; RS_ITEM_0E5
	.short 0x00E6 ; RS_ITEM_0E6
	.short 0x00E7 ; RS_ITEM_0E7
	.short 0x00E8 ; RS_ITEM_0E8
	.short 0x00E9 ; RS_ITEM_0E9
	.short 0x00EA ; RS_ITEM_0EA
	.short 0x00EB ; RS_ITEM_0EB
	.short 0x00EC ; RS_ITEM_0EC
	.short 0x00ED ; RS_ITEM_0ED
	.short 0x00EE ; RS_ITEM_0EE
	.short 0x00EF ; RS_ITEM_0EF
	.short 0x00F0 ; RS_ITEM_0F0
	.short 0x00F1 ; RS_ITEM_0F1
	.short 0x00F2 ; RS_ITEM_0F2
	.short 0x00F3 ; RS_ITEM_0F3
	.short 0x00F4 ; RS_ITEM_0F4
	.short 0x00F5 ; RS_ITEM_0F5
	.short 0x00F6 ; RS_ITEM_0F6
	.short 0x00F7 ; RS_ITEM_0F7
	.short 0x00F8 ; RS_ITEM_0F8
	.short 0x00F9 ; RS_ITEM_0F9
	.short 0x00FA ; RS_ITEM_0FA
	.short 0x00FB ; RS_ITEM_0FB
	.short 0x00FC ; RS_ITEM_0FC
	.short 0x00FD ; RS_ITEM_0FD
	.short 0x0103 ; RS_ITEM_MACH_BIKE
	.short 0x0104 ; RS_ITEM_COIN_CASE
	.short 0x0105 ; RS_ITEM_ITEMFINDER
	.short 0x0106 ; RS_ITEM_OLD_ROD
	.short 0x0107 ; RS_ITEM_GOOD_ROD
	.short 0x0108 ; RS_ITEM_SUPER_ROD
	.short 0x0109 ; RS_ITEM_SS_TICKET
	.short 0x010A ; RS_ITEM_CONTEST_PASS
	.short 0x010B ; RS_ITEM_10B
	.short 0x010C ; RS_ITEM_WAILMER_PAIL
	.short 0x010D ; RS_ITEM_DEVON_GOODS
	.short 0x010E ; RS_ITEM_SOOT_SACK
	.short 0x010F ; RS_ITEM_BASEMENT_KEY
	.short 0x0110 ; RS_ITEM_ACRO_BIKE
	.short 0x0111 ; RS_ITEM_POKEBLOCK_CASE
	.short 0x0112 ; RS_ITEM_LETTER
	.short 0x0113 ; RS_ITEM_EON_TICKET
	.short 0x0114 ; RS_ITEM_RED_ORB
	.short 0x0115 ; RS_ITEM_BLUE_ORB
	.short 0x0116 ; RS_ITEM_SCANNER
	.short 0x0117 ; RS_ITEM_GO_GOGGLES
	.short 0x0118 ; RS_ITEM_METEORITE
	.short 0x0119 ; RS_ITEM_ROOM_1_KEY
	.short 0x011A ; RS_ITEM_ROOM_2_KEY
	.short 0x011B ; RS_ITEM_ROOM_4_KEY
	.short 0x011C ; RS_ITEM_ROOM_6_KEY
	.short 0x011D ; RS_ITEM_STORAGE_KEY
	.short 0x011E ; RS_ITEM_ROOT_FOSSIL
	.short 0x011F ; RS_ITEM_CLAW_FOSSIL
	.short 0x0120 ; RS_ITEM_DEVON_SCOPE
	.short 0x0153 ; RS_ITEM_HM01
	.short 0x0154 ; RS_ITEM_HM02
	.short 0x0155 ; RS_ITEM_HM03
	.short 0x0156 ; RS_ITEM_HM04
	.short 0x0157 ; RS_ITEM_HM05
	.short 0x0158 ; RS_ITEM_HM06
	.short 0x0159 ; RS_ITEM_HM07
	.short 0x015A ; RS_ITEM_HM08
	.short 0x015B ; RS_ITEM_15B
	.short 0x015C ; RS_ITEM_15C
	.short 0x015D ; RS_ITEM_OAKS_PARCEL
	.short 0x015E ; RS_ITEM_POKE_FLUTE
	.short 0x015F ; RS_ITEM_SECRET_KEY
	.short 0x0160 ; RS_ITEM_BIKE_VOUCHER
	.short 0x0161 ; RS_ITEM_GOLD_TEETH
	.short 0x0162 ; RS_ITEM_OLD_AMBER
	.short 0x0163 ; RS_ITEM_CARD_KEY
	.short 0x0164 ; RS_ITEM_LIFT_KEY
	.short 0x0165 ; RS_ITEM_HELIX_FOSSIL
	.short 0x0166 ; RS_ITEM_DOME_FOSSIL
	.short 0x0167 ; RS_ITEM_SILPH_SCOPE
	.short 0x0168 ; RS_ITEM_BICYCLE
	.short 0x0169 ; RS_ITEM_TOWN_MAP
	.short 0x016A ; RS_ITEM_VS_SEEKER
	.short 0x016B ; RS_ITEM_FAME_CHECKER
	.short 0x016C ; RS_ITEM_TM_CASE
	.short 0x016D ; RS_ITEM_BERRY_POUCH
	.short 0x016E ; RS_ITEM_TEACHY_TV
	.short 0x016F ; RS_ITEM_TRI_PASS
	.short 0x0170 ; RS_ITEM_RAINBOW_PASS
	.short 0x0171 ; RS_ITEM_TEA
	.short 0x0172 ; RS_ITEM_MYSTIC_TICKET
	.short 0x0173 ; RS_ITEM_AURORA_TICKET
	.short 0x0174 ; RS_ITEM_POWDER_JAR
	.short 0x0175 ; RS_ITEM_RUBY
	.short 0x0176 ; RS_ITEM_SAPPHIRE
	.short 0x0177 ; RS_ITEM_MAGMA_EMBLEM
	.short 0x0178 ; RS_ITEM_OLD_SEA_MAP
	.short 0x0000 ; RS_ITEM_NONE

	.global MOD83_0223B41C
MOD83_0223B41C: ; 0x0223B41C
	.word 0, -1

	.global MOD83_0223B424
MOD83_0223B424: ; 0x0223B424
	.byte 0x24, 0xFF, 0xAE, 0x51, 0x69, 0x9A, 0xA2, 0x21, 0x3D, 0x84, 0x82, 0x0A, 0x84, 0xE4, 0x09, 0xAD
	.byte 0x11, 0x24, 0x8B, 0x98, 0xC0, 0x81, 0x7F, 0x21, 0xA3, 0x52, 0xBE, 0x19, 0x93, 0x09, 0xCE, 0x20
	.byte 0x10, 0x46, 0x4A, 0x4A, 0xF8, 0x27, 0x31, 0xEC, 0x58, 0xC7, 0xE8, 0x33, 0x82, 0xE3, 0xCE, 0xBF
	.byte 0x85, 0xF4, 0xDF, 0x94, 0xCE, 0x4B, 0x09, 0xC1, 0x94, 0x56, 0x8A, 0xC0, 0x13, 0x72, 0xA7, 0xFC
	.byte 0x9F, 0x84, 0x4D, 0x73, 0xA3, 0xCA, 0x9A, 0x61, 0x58, 0x97, 0xA3, 0x27, 0xFC, 0x03, 0x98, 0x76
	.byte 0x23, 0x1D, 0xC7, 0x61, 0x03, 0x04, 0xAE, 0x56, 0xBF, 0x38, 0x84, 0x00, 0x40, 0xA7, 0x0E, 0xFD
	.byte 0xFF, 0x52, 0xFE, 0x03, 0x6F, 0x95, 0x30, 0xF1, 0x97, 0xFB, 0xC0, 0x85, 0x60, 0xD6, 0x80, 0x25
	.byte 0xA9, 0x63, 0xBE, 0x03, 0x01, 0x4E, 0x38, 0xE2, 0xF9, 0xA2, 0x34, 0xFF, 0xBB, 0x3E, 0x03, 0x44
	.byte 0x78, 0x00, 0x90, 0xCB, 0x88, 0x11, 0x3A, 0x94, 0x65, 0xC0, 0x7C, 0x63, 0x87, 0xF0, 0x3C, 0xAF
	.byte 0xD6, 0x25, 0xE4, 0x8B, 0x38, 0x0A, 0xAC, 0x72, 0x21, 0xD4, 0xF8, 0x07

	.global MOD83_SpeciesWithAbilityOverridesList
MOD83_SpeciesWithAbilityOverridesList: ; 0x0223B4C0
	.short SPECIES_PIDGEY
	.short SPECIES_PIDGEOTTO
	.short SPECIES_PIDGEOT
	.short SPECIES_NIDORAN_F
	.short SPECIES_NIDORINA
	.short SPECIES_NIDOQUEEN
	.short SPECIES_NIDORAN_M
	.short SPECIES_NIDORINO
	.short SPECIES_NIDOKING
	.short SPECIES_CLEFAIRY
	.short SPECIES_CLEFABLE
	.short SPECIES_PARAS
	.short SPECIES_PARASECT
	.short SPECIES_VENONAT
	.short SPECIES_VENOMOTH
	.short SPECIES_MEOWTH
	.short SPECIES_PERSIAN
	.short SPECIES_MANKEY
	.short SPECIES_PRIMEAPE
	.short SPECIES_MACHOP
	.short SPECIES_MACHOKE
	.short SPECIES_MACHAMP
	.short SPECIES_SEEL
	.short SPECIES_DEWGONG
	.short SPECIES_SHELLDER
	.short SPECIES_CLOYSTER
	.short SPECIES_DROWZEE
	.short SPECIES_HYPNO
	.short SPECIES_HITMONLEE
	.short SPECIES_HITMONCHAN
	.short SPECIES_TANGELA
	.short SPECIES_KANGASKHAN
	.short SPECIES_HORSEA
	.short SPECIES_SEADRA
	.short SPECIES_MR_MIME
	.short SPECIES_SCYTHER
	.short SPECIES_JYNX
	.short SPECIES_PINSIR
	.short SPECIES_TAUROS
	.short SPECIES_EEVEE
	.short SPECIES_VAPOREON
	.short SPECIES_JOLTEON
	.short SPECIES_FLAREON
	.short SPECIES_PORYGON
	.short SPECIES_CLEFFA
	.short SPECIES_HOPPIP
	.short SPECIES_SKIPLOOM
	.short SPECIES_JUMPLUFF
	.short SPECIES_SUNKERN
	.short SPECIES_SUNFLORA
	.short SPECIES_ESPEON
	.short SPECIES_UMBREON
	.short SPECIES_MURKROW
	.short SPECIES_GRANBULL
	.short SPECIES_SCIZOR
	.short SPECIES_SHUCKLE
	.short SPECIES_TEDDIURSA
	.short SPECIES_URSARING
	.short SPECIES_SWINUB
	.short SPECIES_PILOSWINE
	.short SPECIES_REMORAID
	.short SPECIES_OCTILLERY
	.short SPECIES_KINGDRA
	.short SPECIES_PORYGON2
	.short SPECIES_STANTLER
	.short SPECIES_SMEARGLE
	.short SPECIES_TYROGUE
	.short SPECIES_HITMONTOP
	.short SPECIES_SMOOCHUM
	.short SPECIES_MILTANK
	.short SPECIES_POOCHYENA
	.short SPECIES_MIGHTYENA
	.short SPECIES_ZIGZAGOON
	.short SPECIES_LINOONE
	.short SPECIES_SHROOMISH
	.short SPECIES_BRELOOM
	.short SPECIES_SKITTY
	.short SPECIES_DELCATTY
	.short SPECIES_SABLEYE
	.short SPECIES_ILLUMISE
	.short SPECIES_NUMEL
	.short SPECIES_CAMERUPT
	.short SPECIES_SPINDA
	.short SPECIES_BARBOACH
	.short SPECIES_WHISCASH
	.short SPECIES_SHUPPET
	.short SPECIES_BANETTE
	.short SPECIES_TROPIUS
	.short SPECIES_ABSOL
	.short SPECIES_SNORUNT
	.short SPECIES_GLALIE
	.short SPECIES_SPHEAL
	.short SPECIES_SEALEO
	.short SPECIES_WALREIN

	.global MOD83_UpConvertSpeciesLUT
MOD83_UpConvertSpeciesLUT: ; 0x0223B57C
	.short SPECIES_TREECKO
	.short SPECIES_GROVYLE
	.short SPECIES_SCEPTILE
	.short SPECIES_TORCHIC
	.short SPECIES_COMBUSKEN
	.short SPECIES_BLAZIKEN
	.short SPECIES_MUDKIP
	.short SPECIES_MARSHTOMP
	.short SPECIES_SWAMPERT
	.short SPECIES_POOCHYENA
	.short SPECIES_MIGHTYENA
	.short SPECIES_ZIGZAGOON
	.short SPECIES_LINOONE
	.short SPECIES_WURMPLE
	.short SPECIES_SILCOON
	.short SPECIES_BEAUTIFLY
	.short SPECIES_CASCOON
	.short SPECIES_DUSTOX
	.short SPECIES_LOTAD
	.short SPECIES_LOMBRE
	.short SPECIES_LUDICOLO
	.short SPECIES_SEEDOT
	.short SPECIES_NUZLEAF
	.short SPECIES_SHIFTRY
	.short SPECIES_NINCADA
	.short SPECIES_NINJASK
	.short SPECIES_SHEDINJA
	.short SPECIES_TAILLOW
	.short SPECIES_SWELLOW
	.short SPECIES_SHROOMISH
	.short SPECIES_BRELOOM
	.short SPECIES_SPINDA
	.short SPECIES_WINGULL
	.short SPECIES_PELIPPER
	.short SPECIES_SURSKIT
	.short SPECIES_MASQUERAIN
	.short SPECIES_WAILMER
	.short SPECIES_WAILORD
	.short SPECIES_SKITTY
	.short SPECIES_DELCATTY
	.short SPECIES_KECLEON
	.short SPECIES_BALTOY
	.short SPECIES_CLAYDOL
	.short SPECIES_NOSEPASS
	.short SPECIES_TORKOAL
	.short SPECIES_SABLEYE
	.short SPECIES_BARBOACH
	.short SPECIES_WHISCASH
	.short SPECIES_LUVDISC
	.short SPECIES_CORPHISH
	.short SPECIES_CRAWDAUNT
	.short SPECIES_FEEBAS
	.short SPECIES_MILOTIC
	.short SPECIES_CARVANHA
	.short SPECIES_SHARPEDO
	.short SPECIES_TRAPINCH
	.short SPECIES_VIBRAVA
	.short SPECIES_FLYGON
	.short SPECIES_MAKUHITA
	.short SPECIES_HARIYAMA
	.short SPECIES_ELECTRIKE
	.short SPECIES_MANECTRIC
	.short SPECIES_NUMEL
	.short SPECIES_CAMERUPT
	.short SPECIES_SPHEAL
	.short SPECIES_SEALEO
	.short SPECIES_WALREIN
	.short SPECIES_CACNEA
	.short SPECIES_CACTURNE
	.short SPECIES_SNORUNT
	.short SPECIES_GLALIE
	.short SPECIES_LUNATONE
	.short SPECIES_SOLROCK
	.short SPECIES_AZURILL
	.short SPECIES_SPOINK
	.short SPECIES_GRUMPIG
	.short SPECIES_PLUSLE
	.short SPECIES_MINUN
	.short SPECIES_MAWILE
	.short SPECIES_MEDITITE
	.short SPECIES_MEDICHAM
	.short SPECIES_SWABLU
	.short SPECIES_ALTARIA
	.short SPECIES_WYNAUT
	.short SPECIES_DUSKULL
	.short SPECIES_DUSCLOPS
	.short SPECIES_ROSELIA
	.short SPECIES_SLAKOTH
	.short SPECIES_VIGOROTH
	.short SPECIES_SLAKING
	.short SPECIES_GULPIN
	.short SPECIES_SWALOT
	.short SPECIES_TROPIUS
	.short SPECIES_WHISMUR
	.short SPECIES_LOUDRED
	.short SPECIES_EXPLOUD
	.short SPECIES_CLAMPERL
	.short SPECIES_HUNTAIL
	.short SPECIES_GOREBYSS
	.short SPECIES_ABSOL
	.short SPECIES_SHUPPET
	.short SPECIES_BANETTE
	.short SPECIES_SEVIPER
	.short SPECIES_ZANGOOSE
	.short SPECIES_RELICANTH
	.short SPECIES_ARON
	.short SPECIES_LAIRON
	.short SPECIES_AGGRON
	.short SPECIES_CASTFORM
	.short SPECIES_VOLBEAT
	.short SPECIES_ILLUMISE
	.short SPECIES_LILEEP
	.short SPECIES_CRADILY
	.short SPECIES_ANORITH
	.short SPECIES_ARMALDO
	.short SPECIES_RALTS
	.short SPECIES_KIRLIA
	.short SPECIES_GARDEVOIR
	.short SPECIES_BAGON
	.short SPECIES_SHELGON
	.short SPECIES_SALAMENCE
	.short SPECIES_BELDUM
	.short SPECIES_METANG
	.short SPECIES_METAGROSS
	.short SPECIES_REGIROCK
	.short SPECIES_REGICE
	.short SPECIES_REGISTEEL
	.short SPECIES_KYOGRE
	.short SPECIES_GROUDON
	.short SPECIES_RAYQUAZA
	.short SPECIES_LATIAS
	.short SPECIES_LATIOS
	.short SPECIES_JIRACHI
	.short SPECIES_DEOXYS
	.short SPECIES_CHIMECHO
	.short SPECIES_BURMY
	.short SPECIES_WORMADAM
	.short SPECIES_MOTHIM
	.short SPECIES_COMBEE
	.short SPECIES_VESPIQUEN
	.short SPECIES_PACHIRISU
	.short SPECIES_BUIZEL
	.short SPECIES_FLOATZEL
	.short SPECIES_CHERUBI

	.global MOD83_0223B69C
MOD83_0223B69C: ; 0x0223B69C
	.word 0x42354245 ; "EB5B"
	.word 0x42354345 ; "EC5B"
	.word 0x42354445 ; "ED5B"
	.word 0x42354545 ; "EE5B"
	.word 0x42354645 ; "EF5B"
	.word 0x42354745 ; "EG5B"
	.word 0x42354845 ; "EH5B"
	.word 0x42354945 ; "EI5B"
	.word 0x42354A45 ; "EJ5B"
	.word 0x42354B45 ; "EK5B"
	.word 0x42354C45 ; "EL5B"
	.word 0x42354D45 ; "EM5B"
	.word 0x42355045 ; "EP5B"
	.word 0x42355145 ; "EQ5B"
	.word 0x42355245 ; "ER5B"
	.word 0x42355345 ; "ES5B"
	.word 0x42355445 ; "ET5B"
	.word 0x42355545 ; "EU5B"
	.word 0x42355645 ; "EV5B"
	.word 0x42355745 ; "EW5B"
	.word 0x00000000

	.global MOD83_0223B6F0
MOD83_0223B6F0: ; 0x0223B6F0
	.asciz "mywh_SYSSTATE_IDLE"

	.balign 4
	.global MOD83_0223B704
MOD83_0223B704: ; 0x0223B704
	.asciz "mywh_SYSSTATE_BUSY"

	.balign 4
	.global MOD83_0223B718
MOD83_0223B718: ; 0x0223B718
	.asciz "mywh_SYSSTATE_STOP"

	.balign 4
	.global MOD83_0223B72C
MOD83_0223B72C: ; 0x0223B72C
	.asciz "mywh_SYSSTATE_ERROR"

	.balign 4
	.global MOD83_0223B740
MOD83_0223B740: ; 0x0223B740
	.asciz "mywh_SYSSTATE_SCANNING"

	.balign 4
	.global MOD83_0223B758
MOD83_0223B758: ; 0x0223B758
	.asciz "mywh_SYSSTATE_CONNECTED"

	.balign 4
	.global MOD83_0223B770
MOD83_0223B770: ; 0x0223B770
	.asciz "mywh_SYSSTATE_KEYSHARING"

	.balign 4
	.global MOD83_0223B78C
MOD83_0223B78C: ; 0x0223B78C
	.asciz "mywh_SYSSTATE_DATASHARING"

	.balign 4
	.global MOD83_0223B7A8
MOD83_0223B7A8: ; 0x0223B7A8
	.asciz "mywh_SYSSTATE_CONNECT_FAIL"

	.balign 4
	.global MOD83_0223B7C4
MOD83_0223B7C4: ; 0x0223B7C4
	.asciz "mywh_SYSSTATE_MEASURECHANNEL"

	.balign 4
	.global MOD83_0223B7E4
MOD83_0223B7E4: ; 0x0223B7E4
	.word MOD83_0223B718, MOD83_0223B6F0, MOD83_0223B740, MOD83_0223B704
	.word MOD83_0223B758, MOD83_0223B78C, MOD83_0223B770, MOD83_0223B7C4
	.word MOD83_0223B7A8, MOD83_0223B72C

	.global MOD83_0223B80C
MOD83_0223B80C: ; 0x0223B80C
	.asciz "%s -> "

	.balign 4
	.global MOD83_0223B814
MOD83_0223B814: ; 0x0223B814
	.asciz "%s\n"

	.balign 4
	.global MOD83_0223B818
MOD83_0223B818: ; 0x0223B818
	.asciz "not my parent ggid (%d != %d)\n"

	.balign 4
	.global MOD83_0223B838
MOD83_0223B838: ; 0x0223B838
	.asciz "ADAE"

	.balign 4
	.global MOD83_0223B840
MOD83_0223B840: ; 0x0223B840
	.asciz "Sx439tCkbrWyR8X2"

	.balign 4
	.global MOD83_0223B854
MOD83_0223B854: ; 0x0223B854
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
	.global MOD83_0223B860
MOD83_0223B860: ; 0x0223B860
	.space 0x10

	.global MOD83_0223B870
MOD83_0223B870: ; 0x0223B870
	.space 0x14

	.global MOD83_0223B884
MOD83_0223B884: ; 0x0223B884
	.space 0x4

	.global MOD83_0223B888
MOD83_0223B888: ; 0x0223B888
	.space 0x14

	.global MOD83_0223B89C
MOD83_0223B89C: ; 0x0223B89C
	.space 0x4

	.global MOD83_0223B8A0
MOD83_0223B8A0: ; 0x0223B8A0
	.space 0x274

	.global MOD83_0223BB14
MOD83_0223BB14: ; 0x0223BB14
	.space 0x4

	.global MOD83_0223BB18
MOD83_0223BB18: ; 0x0223BB18
	.space 0x10

	.global MOD83_0223BB28
MOD83_0223BB28: ; 0x0223BB28
	.space 0x8

	.global MOD83_0223BB30
MOD83_0223BB30: ; 0x0223BB30
	.space 0x68

	.global MOD83_0223BB98
MOD83_0223BB98: ; 0x0223BB98
	.space 0x94

	.global heap_id
heap_id: ; 0x0223BC2C
	.space 0x4

	.global MOD83_0223BC30
MOD83_0223BC30: ; 0x0223BC30
	.space 0x30

	.global MOD83_0223BC60
MOD83_0223BC60: ; 0x0223BC60
	.space 0x4

	.global MOD83_0223BC64
MOD83_0223BC64: ; 0x0223BC64
	.space 0x1CC

	.global MOD83_0223BE30
MOD83_0223BE30: ; 0x0223BE30
	.space 0xC80

	.global MOD83_0223CAB0
MOD83_0223CAB0: ; 0x0223CAB0
	.space 0x24

	.global MOD83_0223CAD4
MOD83_0223CAD4: ; 0x0223CAD4
	.space 0x8

	.global MOD83_0223CADC
MOD83_0223CADC: ; 0x0223CADC
	.space 0x10

	.global MOD83_0223CAEC
MOD83_0223CAEC: ; 0x0223CAEC
	.space 0x6F4

