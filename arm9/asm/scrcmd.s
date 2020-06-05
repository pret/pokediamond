    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F34E0
	.extern ConditionLookup
	.extern UNK_020F34FC
	.extern UNK_020F3538
	.extern CompareUtil
	.extern gUnknown21C48B8
	.extern gUnk021C4918
	.extern FUN_0203A2F0

	.section .bss

	.global UNK_021C5A0C
UNK_021C5A0C: ; 0x021C5A0C
	.space 0x4

	.text

	thumb_func_start ScrCmd_BoardMsg
ScrCmd_BoardMsg: ; 0x0203A8B8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x3
	add r0, r4, #0x0
	bl FUN_02039438
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	ldr r1, [sp, #0x0]
	ldr r2, [r6, #0x0]
	bl FUN_0200A8E0
	ldr r0, [sp, #0x8]
	ldr r1, [r7, #0x0]
	ldr r0, [r0, #0x0]
	ldr r2, [r6, #0x0]
	bl FUN_0200B7B8
	ldr r0, [r4, #0x60]
	bl MOD05_021E8140
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r2, r0, #0x0
	ldr r1, [r7, #0x0]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	ldr r1, [sp, #0x4]
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0xc]
	ldr r1, _0203A948 ; =FUN_0203A94C
	str r0, [r5, #0x64]
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0203A948: .word FUN_0203A94C 

	thumb_func_start FUN_0203A94C
FUN_0203A94C: ; 0x0203A94C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x3
	add r0, r5, #0x0
	bl FUN_02039438
	ldr r1, [r7, #0x64]
	add r6, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0x60]
	bl MOD05_021E8144
	ldrb r0, [r6, #0x0]
	ldr r5, _0203A9E8 ; =0x0000FFFF
	bl FUN_020546C8
	cmp r0, #0x1
	bne _0203A986
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0203A986:
	ldr r0, _0203A9EC ; =gUnknown21C48B8
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0203A994
	mov r5, #0x0
	b _0203A9B0
_0203A994:
	mov r1, #0x80
	tst r1, r0
	beq _0203A99E
	mov r5, #0x1
	b _0203A9B0
_0203A99E:
	mov r1, #0x20
	tst r1, r0
	beq _0203A9A8
	mov r5, #0x2
	b _0203A9B0
_0203A9A8:
	mov r1, #0x10
	tst r1, r0
	beq _0203A9B0
	mov r5, #0x3
_0203A9B0:
	ldr r1, _0203A9E8 ; =0x0000FFFF
	cmp r5, r1
	beq _0203A9D0
	ldrb r0, [r6, #0x0]
	bl FUN_0201BD7C
	add r7, #0x80
	ldr r0, [r7, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0203A9D0:
	mov r1, #0x1
	lsl r1, r1, #0xa
	tst r0, r1
	beq _0203A9E4
	ldrb r0, [r6, #0x0]
	bl FUN_0201BD7C
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r7, pc}
_0203A9E4:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203A9E8: .word 0x0000FFFF
_0203A9EC: .word gUnknown21C48B8

	thumb_func_start ScrCmd_BoardEndWait
ScrCmd_BoardEndWait: ; 0x0203A9F0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203AA08 ; =FUN_0203AA0C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203AA08: .word FUN_0203AA0C 

	thumb_func_start FUN_0203AA0C
FUN_0203AA0C: ; 0x0203AA0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, _0203AA88 ; =gUnknown21C48B8
	ldr r1, _0203AA8C ; =0x0000FFFF
	ldr r2, [r0, #0x48]
	mov r0, #0x3
	add r3, r2, #0x0
	tst r3, r0
	beq _0203AA36
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203AA36:
	mov r3, #0x40
	tst r3, r2
	beq _0203AA40
	mov r1, #0x0
	b _0203AA5C
_0203AA40:
	mov r3, #0x80
	tst r3, r2
	beq _0203AA4A
	mov r1, #0x1
	b _0203AA5C
_0203AA4A:
	mov r3, #0x20
	tst r3, r2
	beq _0203AA54
	mov r1, #0x2
	b _0203AA5C
_0203AA54:
	mov r3, #0x10
	tst r3, r2
	beq _0203AA5C
	add r1, r0, #0x0
_0203AA5C:
	ldr r0, _0203AA8C ; =0x0000FFFF
	cmp r1, r0
	beq _0203AA74
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203AA74:
	mov r0, #0x1
	lsl r0, r0, #0xa
	tst r0, r2
	beq _0203AA82
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
_0203AA82:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203AA88: .word gUnknown21C48B8
_0203AA8C: .word 0x0000FFFF

	thumb_func_start ScrCmd_MenuReq
ScrCmd_MenuReq: ; 0x0203AA90
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02039460
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_YesNoWin
ScrCmd_YesNoWin: ; 0x0203AAA0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x2
	add r0, r4, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	ldr r2, _0203AAF4 ; =0x000003D9
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	ldr r1, _0203AAF8 ; =UNK_020F34E0
	ldr r2, _0203AAF4 ; =0x000003D9
	mov r3, #0xb
	bl FUN_02002198
	str r0, [r6, #0x0]
	ldr r1, _0203AAFC ; =FUN_0203AB00
	add r0, r5, #0x0
	str r7, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203AAF4: .word 0x000003D9
_0203AAF8: .word UNK_020F34E0
_0203AAFC: .word FUN_0203AB00 

	thumb_func_start FUN_0203AB00
FUN_0203AB00: ; 0x0203AB00
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x2
	add r0, r6, #0x0
	bl FUN_02039438
	ldr r1, [r5, #0x64]
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_020021AC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _0203AB34
	mov r0, #0x0
	pop {r4-r6, pc}
_0203AB34:
	cmp r0, #0x0
	bne _0203AB3C
	mov r0, #0x0
	b _0203AB3E
_0203AB3C:
	mov r0, #0x1
_0203AB3E:
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_TimeWaitIconAdd
ScrCmd_TimeWaitIconAdd: ; 0x0203AB44
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x12
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r1, _0203AB70 ; =0x000003E2
	add r0, r4, #0x0
	bl FUN_0200D858
	str r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203AB70: .word 0x000003E2

	thumb_func_start ScrCmd_TimeWaitIconDel
ScrCmd_TimeWaitIconDel: ; 0x0203AB74
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x12
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0200DBFC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpMenuInit
ScrCmd_BmpMenuInit: ; 0x0203AB8C
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1BF8
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpMenuInitEx
ScrCmd_BmpMenuInitEx: ; 0x0203AC14
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1BF8
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpMenuMakeList
ScrCmd_BmpMenuMakeList: ; 0x0203AC9C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r1, [r4, #0x8]
	add r3, r1, #0x1
	str r3, [r4, #0x8]
	ldrb r1, [r1, #0x0]
	add r2, r3, #0x1
	str r2, [r4, #0x8]
	ldrb r2, [r3, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E1C4C
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpMenuMakeList16
ScrCmd_BmpMenuMakeList16: ; 0x0203ACC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl MOD05_021E1C4C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpMenuStart
ScrCmd_BmpMenuStart: ; 0x0203AD08
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E1C54
	ldr r1, _0203AD28 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AD28: .word FUN_0203AD2C 

	thumb_func_start FUN_0203AD2C
FUN_0203AD2C: ; 0x0203AD2C
	push {r3, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	ldrh r1, [r0, #0x0]
	ldr r0, _0203AD50 ; =0x0000EEEE
	cmp r1, r0
	beq _0203AD4A
	mov r0, #0x1
	pop {r3, pc}
_0203AD4A:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0203AD50: .word 0x0000EEEE

	thumb_func_start ScrCmd_UnionBmpMenuStart
ScrCmd_UnionBmpMenuStart: ; 0x0203AD54
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E1C54
	ldr r1, _0203AD74 ; =FUN_0203AD78
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AD74: .word FUN_0203AD78 

	thumb_func_start FUN_0203AD78
FUN_0203AD78: ; 0x0203AD78
	push {r4-r6, lr}
	add r1, r0, #0x0
	add r0, #0x80
	ldr r1, [r1, #0x64]
	ldr r5, [r0, #0x0]
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0203ADC0 ; =0x0000EEEE
	cmp r1, r0
	bne _0203ADBC
	ldr r0, [r5, #0x78]
	bl FUN_02052714
	cmp r0, #0x0
	beq _0203ADB8
	mov r0, #0x8
	strh r0, [r4, #0x0]
	ldr r0, [r6, #0x0]
	bl MOD05_021E1ECC
	mov r0, #0x1
	pop {r4-r6, pc}
_0203ADB8:
	mov r0, #0x0
	pop {r4-r6, pc}
_0203ADBC:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203ADC0: .word 0x0000EEEE

	thumb_func_start ScrCmd_BmpListInit
ScrCmd_BmpListInit: ; 0x0203ADC4
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1F34
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpListInitEx
ScrCmd_BmpListInitEx: ; 0x0203AE4C
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	mov r1, #0x0
	add r0, r6, #0x0
	bl FUN_02039438
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	mov r1, #0xf
	bl FUN_02039438
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r0, [r0, #0x0]
	add r2, r1, #0x1
	str r0, [sp, #0x18]
	str r2, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	add r1, r2, #0x1
	str r0, [sp, #0x14]
	str r1, [r5, #0x8]
	ldrb r7, [r2, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x24]
	add r0, r6, #0x0
	bl FUN_020394B8
	str r0, [sp, #0x28]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	bl FUN_02039438
	ldr r1, [sp, #0x28]
	str r4, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x20]
	add r3, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x78]
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r6, #0x0
	bl MOD05_021E1F34
	ldr r1, [sp, #0x1c]
	str r0, [r1, #0x0]
	ldr r0, [sp, #0x24]
	str r0, [r5, #0x64]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_BmpListMakeList
ScrCmd_BmpListMakeList: ; 0x0203AED4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl MOD05_021E1F58
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_BmpListStart
ScrCmd_BmpListStart: ; 0x0203AF34
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E1F60
	ldr r1, _0203AF54 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AF54: .word FUN_0203AD2C 

	thumb_func_start ScrCmd_BmpMenuHVStart
ScrCmd_BmpMenuHVStart: ; 0x0203AF58
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E26CC
	ldr r1, _0203AF80 ; =FUN_0203AD2C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203AF80: .word FUN_0203AD2C 

	thumb_func_start FUN_0203AF84
FUN_0203AF84: ; 0x0203AF84
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E2B80
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start FUN_0203AFA4
FUN_0203AFA4: ; 0x0203AFA4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_02039438
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021E2B9C
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_ObjAnime
ScrCmd_ObjAnime: ; 0x0203AFC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadWord
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_0203B120
	add r6, r0, #0x0
	bne _0203AFF6
	bl ErrorHandling
_0203AFF6:
	ldr r1, [r5, #0x8]
	add r0, r6, #0x0
	add r1, r1, r4
	bl FUN_0205AEA4
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r1, [r0, #0x0]
	add r5, #0x80
	mov r2, #0x0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_0203B174
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ObjAnimePos
ScrCmd_ObjAnimePos: ; 0x0203B024
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_0203B120
	str r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0203B07A
	bl ErrorHandling
_0203B07A:
	mov r0, #0x4
	add r1, r0, #0x0
	add r1, #0xfc
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	bl FUN_02058B2C
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x4]
	bl FUN_02058B4C
	lsl r0, r0, #0x10
	ldr r2, [sp, #0x0]
	lsr r0, r0, #0x10
	mov r1, #0x0
	cmp r6, r2
	bhs _0203B0B0
	mov r2, #0xf
	strh r2, [r4, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, #0x1
	sub r2, r2, r6
	strh r2, [r4, #0x2]
	b _0203B0C0
_0203B0B0:
	cmp r6, r2
	bls _0203B0C0
	mov r2, #0xe
	strh r2, [r4, #0x0]
	ldr r2, [sp, #0x0]
	add r1, r1, #0x1
	sub r2, r6, r2
	strh r2, [r4, #0x2]
_0203B0C0:
	cmp r0, r7
	bhs _0203B0D4
	lsl r2, r1, #0x2
	mov r3, #0xc
	strh r3, [r4, r2]
	sub r3, r7, r0
	add r0, r4, r2
	strh r3, [r0, #0x2]
	add r1, r1, #0x1
	b _0203B0E6
_0203B0D4:
	cmp r0, r7
	bls _0203B0E6
	lsl r2, r1, #0x2
	mov r3, #0xd
	strh r3, [r4, r2]
	sub r3, r0, r7
	add r0, r4, r2
	strh r3, [r0, #0x2]
	add r1, r1, #0x1
_0203B0E6:
	lsl r2, r1, #0x2
	mov r0, #0xfe
	strh r0, [r4, r2]
	mov r1, #0x0
	add r0, r4, r2
	strh r1, [r0, #0x2]
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_0205AEA4
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r1, [r0, #0x0]
	add r5, #0x80
	add r2, r4, #0x0
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl FUN_0203B174
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0203B120
FUN_0203B120: ; 0x0203B120
	push {r3, lr}
	cmp r1, #0xf2
	bne _0203B130
	ldr r0, [r0, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	pop {r3, pc}
_0203B130:
	cmp r1, #0xf1
	bne _0203B13E
	mov r1, #0xb
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	pop {r3, pc}
_0203B13E:
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_ObjAnimeWait
ScrCmd_ObjAnimeWait: ; 0x0203B148
	push {r3, lr}
	ldr r1, _0203B154 ; =FUN_0203B158
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203B154: .word FUN_0203B158 

	thumb_func_start FUN_0203B158
FUN_0203B158: ; 0x0203B158
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B16E
	mov r0, #0x1
	pop {r3, pc}
_0203B16E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203B174
FUN_0203B174: ; 0x0203B174
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r0, #0x4
	mov r1, #0x10
	add r7, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	bne _0203B18E
	bl ErrorHandling
	pop {r3-r7, pc}
_0203B18E:
	str r5, [r4, #0xc]
	str r6, [r4, #0x4]
	ldr r0, _0203B1A4 ; =FUN_0203B1A8
	add r1, r4, #0x0
	mov r2, #0x0
	str r7, [r4, #0x8]
	bl FUN_0200CA44
	str r0, [r4, #0x0]
	pop {r3-r7, pc}
	nop
_0203B1A4: .word FUN_0203B1A8 

	thumb_func_start FUN_0203B1A8
FUN_0203B1A8: ; 0x0203B1A8
	push {r3-r5, lr}
	add r5, r1, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0x4
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FUN_0205AEF0
	cmp r0, #0x1
	bne _0203B1EC
	ldr r0, [r5, #0x4]
	bl FUN_0205AEFC
	ldr r0, [r5, #0x0]
	bl FUN_0200CAB4
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0203B1D6
	bl FreeToHeap
_0203B1D6:
	add r0, r5, #0x0
	bl FreeToHeap
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203B1E8
	bl ErrorHandling
	pop {r3-r5, pc}
_0203B1E8:
	sub r0, r0, #0x1
	strb r0, [r4, #0x0]
_0203B1EC:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ObjPauseAll
ScrCmd_ObjPauseAll: ; 0x0203B1F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B20E
	ldr r0, [r4, #0x34]
	bl FUN_02058780
	b _0203B214
_0203B20E:
	add r0, r5, #0x0
	bl ScrCmd_TalkObjPauseAll
_0203B214:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203B218
FUN_0203B218: ; 0x0203B218
	push {r4-r6, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	add r6, r0, #0x0
	ldrb r2, [r1, #0x0]
	mov r1, #0x1
	tst r1, r2
	beq _0203B252
	bl FUN_0205AE28
	cmp r0, #0x1
	bne _0203B252
	add r0, r6, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xfe
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B252:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	tst r0, r1
	beq _0203B276
	ldr r0, [r5, #0x0]
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B276
	ldr r0, [r5, #0x0]
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xfb
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B276:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	tst r0, r1
	beq _0203B2A2
	ldr r0, [r4, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B2A2
	add r0, r4, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xfd
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B2A2:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r1, [r0, #0x0]
	mov r0, #0x8
	tst r0, r1
	beq _0203B2CC
	ldr r0, [r5, #0x0]
	bl FUN_0205E7C4
	add r4, r0, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	bne _0203B2CC
	add r0, r4, #0x0
	bl FUN_02058908
	ldr r1, _0203B2DC ; =UNK_021C5A0C
	mov r0, #0xf7
	ldrb r2, [r1, #0x0]
	and r0, r2
	strb r0, [r1, #0x0]
_0203B2CC:
	ldr r0, _0203B2DC ; =UNK_021C5A0C
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B2D8
	mov r0, #0x1
	pop {r4-r6, pc}
_0203B2D8:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0203B2DC: .word UNK_021C5A0C

	thumb_func_start ScrCmd_TalkObjPauseAll
ScrCmd_TalkObjPauseAll: ; 0x0203B2E0
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0xa
	add r0, r4, #0x0
	bl FUN_02039438
	add r5, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020553A0
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x34]
	mov r1, #0x30
	bl FUN_020580B4
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_0205E7C4
	add r6, r0, #0x0
	ldr r0, [r4, #0x34]
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r2, #0x0
	strb r2, [r1, #0x0]
	bl FUN_02058780
	ldr r0, [sp, #0x4]
	bl FUN_0205AE28
	cmp r0, #0x0
	bne _0203B334
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x1
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_02058914
_0203B334:
	ldr r0, [r5, #0x0]
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B34E
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x4
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	ldr r0, [r5, #0x0]
	bl FUN_02058914
_0203B34E:
	cmp r7, #0x0
	beq _0203B37A
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	bl FUN_0205ED3C
	cmp r0, #0x1
	bne _0203B37A
	add r0, r7, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B37A
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x2
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02058914
_0203B37A:
	cmp r6, #0x0
	beq _0203B398
	add r0, r6, #0x0
	bl FUN_02058854
	cmp r0, #0x0
	beq _0203B398
	ldr r1, _0203B3A8 ; =UNK_021C5A0C
	mov r0, #0x8
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02058914
_0203B398:
	ldr r0, [sp, #0x0]
	ldr r1, _0203B3AC ; =FUN_0203B218
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203B3A8: .word UNK_021C5A0C
_0203B3AC: .word FUN_0203B218 

	thumb_func_start ScrCmd_ObjPauseClearAll
ScrCmd_ObjPauseClearAll: ; 0x0203B3B0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_020587B0
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_ObjPause
ScrCmd_ObjPause: ; 0x0203B3C0
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	bl FUN_02058060
	bl FUN_02058908
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_ObjPauseClear
ScrCmd_ObjPauseClear: ; 0x0203B3DC
	push {r4, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	bl FUN_02058060
	bl FUN_02058914
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_ObjAdd
ScrCmd_ObjAdd: ; 0x0203B3F8
	push {r3-r6, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034B64
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034B6C
	str r0, [sp, #0x0]
	ldr r3, [r5, #0x1c]
	ldr r0, [r5, #0x34]
	ldr r3, [r3, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020575D4
	cmp r0, #0x0
	bne _0203B43A
	bl ErrorHandling
_0203B43A:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start ScrCmd_ObjDel
ScrCmd_ObjDel: ; 0x0203B440
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	bl FUN_02057688
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_VanishDummyObjAdd
ScrCmd_VanishDummyObjAdd: ; 0x0203B468
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	mov r3, #0x0
	str r3, [sp, #0x4]
	ldr r1, [r0, #0x1c]
	add r2, r7, #0x0
	ldr r1, [r1, #0x0]
	str r1, [sp, #0x8]
	ldr r0, [r0, #0x34]
	add r1, r6, #0x0
	bl FUN_0205753C
	str r0, [r4, #0x0]
	bl FUN_02059D1C
	ldr r0, [r4, #0x0]
	mov r1, #0x1
	bl FUN_0205889C
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_020588B8
	ldr r0, [r4, #0x0]
	bl FUN_02058B7C
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r4, r0, #0x0
	ldr r1, [r1, #0x24]
	bl MOD05_021EF5E0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EC68
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_VanishDummyObjDel
ScrCmd_VanishDummyObjDel: ; 0x0203B500
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xb
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_02057654
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xff
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	bl FUN_02058B7C
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	add r4, r0, #0x0
	ldr r1, [r1, #0x24]
	bl MOD05_021EF5E0
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EC68
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ObjTurn
ScrCmd_ObjTurn: ; 0x0203B544
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	bl FUN_02059E74
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203B568
	mov r0, #0x0
	pop {r3-r5, pc}
_0203B568:
	add r1, r4, #0x0
	bl MOD05_021F1EC0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PlayerPosGet
ScrCmd_PlayerPosGet: ; 0x0203B574
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055320
	strh r0, [r6, #0x0]
	ldr r0, [r5, #0x38]
	bl FUN_0205532C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_ObjPosGet
ScrCmd_ObjPosGet: ; 0x0203B5B8
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058B2C
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_02058B4C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_PlayerDirGet
ScrCmd_PlayerDirGet: ; 0x0203B618
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PlayerPosOffsetSet
ScrCmd_PlayerPosOffsetSet: ; 0x0203B640
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	cmp r7, #0x0
	beq _0203B696
	lsl r0, r7, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6A4
_0203B696:
	lsl r0, r7, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6A4:
	bl _ffix
	str r0, [sp, #0x0]
	cmp r6, #0x0
	beq _0203B6C0
	lsl r0, r6, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6CE
_0203B6C0:
	lsl r0, r6, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6CE:
	bl _ffix
	str r0, [sp, #0x4]
	cmp r4, #0x0
	beq _0203B6EA
	lsl r0, r4, #0xc
	bl _fflt
	add r1, r0, #0x0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0203B6F8
_0203B6EA:
	lsl r0, r4, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0203B6F8:
	bl _ffix
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	add r1, sp, #0x0
	bl FUN_02058BB4
	add r5, #0x80
	ldr r1, [r5, #0x0]
	add r0, sp, #0x0
	ldr r1, [r1, #0x20]
	bl FUN_0201EF70
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_NotZoneDelSet
ScrCmd_NotZoneDelSet: ; 0x0203B724
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r1, [r2, #0x0]
	bl FUN_02058994
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_MoveCodeChange
ScrCmd_MoveCodeChange: ; 0x0203B758
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058E90
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_MoveCodeGet
ScrCmd_MoveCodeGet: ; 0x0203B790
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	cmp r0, #0x0
	beq _0203B7D2
	bl FUN_02058480
	strh r0, [r4, #0x0]
_0203B7D2:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PairObjIdSet
ScrCmd_PairObjIdSet: ; 0x0203B7D8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x30
	ldr r0, [r0, #0x34]
	bl FUN_020580B4
	mov r1, #0xfe
	bl FUN_02058EB0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_CBSealKindNumGet
ScrCmd_CBSealKindNumGet: ; 0x0203B7F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029C80
	bl FUN_02029E0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_CBItemNumGet
ScrCmd_CBItemNumGet: ; 0x0203B81C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029C80
	add r1, r6, #0x0
	bl FUN_02029E2C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_CBItemNumAdd
ScrCmd_CBItemNumAdd: ; 0x0203B85C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029C80
	lsl r2, r4, #0x10
	add r1, r6, #0x0
	asr r2, r2, #0x10
	bl FUN_02029D44
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_UnknownFormGet
ScrCmd_UnknownFormGet: ; 0x0203B8A0
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	bl FUN_020690CC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_PokeListSetProc
ScrCmd_PokeListSetProc: ; 0x0203B8E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_020379F8
	str r0, [r4, #0x0]
	ldr r1, _0203B910 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203B910: .word FUN_0203BC04 

	thumb_func_start ScrCmd_NpcTradePokeListSetProc
ScrCmd_NpcTradePokeListSetProc: ; 0x0203B914
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_02037A1C
	str r0, [r4, #0x0]
	ldr r1, _0203B940 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203B940: .word FUN_0203BC04 

	thumb_func_start ScrCmd_UnionPokeListSetProc
ScrCmd_UnionPokeListSetProc: ; 0x0203B944
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0x10]
	bl FUN_02037B44
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeListGetResult
ScrCmd_PokeListGetResult: ; 0x0203B968
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203B994
	bl ErrorHandling
_0203B994:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x7
	bne _0203B9A6
	mov r0, #0xff
	strh r0, [r5, #0x0]
_0203B9A6:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ConPokeListSetProc
ScrCmd_ConPokeListSetProc: ; 0x0203B9B4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r1, r5, #0x0
	str r6, [sp, #0x4]
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [sp, #0x8]
	mov r0, #0x20
	add r3, r7, #0x0
	bl FUN_02037BB0
	str r0, [r4, #0x0]
	ldr r1, _0203BA38 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0203BA38: .word FUN_0203BC04 

	thumb_func_start ScrCmd_ConPokeListGetResult
ScrCmd_ConPokeListGetResult: ; 0x0203BA3C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BA7C
	bl ErrorHandling
_0203BA7C:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203BA8E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203BA8E:
	ldr r0, [r4, #0x0]
	bl FUN_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203BAA0
	mov r0, #0x1
	b _0203BAA2
_0203BAA0:
	mov r0, #0x0
_0203BAA2:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ConPokeStatusSetProc
ScrCmd_ConPokeStatusSetProc: ; 0x0203BAB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r5, #0x0
	add r1, #0x80
	add r2, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	bl FUN_02037C00
	str r0, [r4, #0x0]
	ldr r1, _0203BAF0 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203BAF0: .word FUN_0203BC04 

	thumb_func_start ScrCmd_PokeStatusGetResult
ScrCmd_PokeStatusGetResult: ; 0x0203BAF4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BB20
	bl ErrorHandling
_0203BB20:
	ldr r0, [r4, #0x0]
	bl FUN_02037A78
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_RevengeTrainerSearch
ScrCmd_RevengeTrainerSearch: ; 0x0203BB34
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r7, #0x0
	bl MOD05_021E1858
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_SetWeather
ScrCmd_SetWeather: ; 0x0203BB80
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_InitWeather
ScrCmd_InitWeather: ; 0x0203BB84
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_UpdateWeather
ScrCmd_UpdateWeather: ; 0x0203BB88
	mov r0, #0x1
	bx lr

	thumb_func_start ScrCmd_GetMapPosition
ScrCmd_GetMapPosition: ; 0x0203BB8C
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0203BB90
FUN_0203BB90: ; 0x0203BB90
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x13
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0203BBAE
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BBAE:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BBBC
FUN_0203BBBC: ; 0x0203BBBC
	push {r4-r6, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x13
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r6, [r4, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0203BBDC
	mov r0, #0x0
	pop {r4-r6, pc}
_0203BBDC:
	ldr r0, [r6, #0x8]
	cmp r0, #0x1
	bne _0203BBF4
	mov r0, #0xb
	bl FUN_02029048
	add r5, #0x98
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	bl FUN_02028AD4
_0203BBF4:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203BC04
FUN_0203BC04: ; 0x0203BC04
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204647C
	cmp r0, #0x0
	bne _0203BC16
	mov r0, #0x1
	pop {r3, pc}
_0203BC16:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_SetMapProc
ScrCmd_SetMapProc: ; 0x0203BC1C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_0204AF84
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_FinishMapProc
ScrCmd_FinishMapProc: ; 0x0203BC2C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_0204AF3C
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_0203BC3C
FUN_0203BC3C: ; 0x0203BC3C
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02027E24
	cmp r5, #0x0
	bne _0203BC5A
	add r1, r4, #0x0
	bl FUN_02027098
	cmp r0, #0x0
	bne _0203BC68
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BC5A:
	add r1, r4, #0x0
	bl FUN_020270B4
	cmp r0, #0x0
	bne _0203BC68
	mov r0, #0x0
	pop {r3-r5, pc}
_0203BC68:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0203BC6C
FUN_0203BC6C: ; 0x0203BC6C
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02027E24
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x0
	bne _0203BC90
	mov r0, #0x0
	pop {r3-r7, pc}
_0203BC90:
	ldr r0, [sp, #0x0]
	mov r1, #0xc
	bl AllocFromHeap
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
	str r7, [r0, #0x0]
	str r4, [r0, #0x8]
	str r6, [r0, #0x4]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_WiFiAutoReg
ScrCmd_WiFiAutoReg: ; 0x0203BCBC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD05_021F02C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_WiFiP2PMatchEventCall
ScrCmd_WiFiP2PMatchEventCall: ; 0x0203BCCC
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0206F3B8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_WiFiP2PMatchSetDel
ScrCmd_WiFiP2PMatchSetDel: ; 0x0203BCD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x4]
	strh r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_CommGetCurrentID
ScrCmd_CommGetCurrentID: ; 0x0203BD08
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	bl FUN_02031190
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeWindowPut
ScrCmd_PokeWindowPut: ; 0x0203BD28
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, _0203BDB4 ; =0x000003D9
	ldr r0, [r0, #0x8]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _0203BDB4 ; =0x000003D9
	mov r1, #0x3
	str r0, [sp, #0x4]
	lsl r0, r7, #0x18
	str r4, [sp, #0x8]
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	mov r0, #0x4
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	ldr r0, [r0, #0x8]
	mov r3, #0x5
	bl FUN_0200DC4C
	add r5, #0x80
	str r0, [r6, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_0203ED2C
	mov r0, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_0203BDB4: .word 0x000003D9

	thumb_func_start ScrCmd_PokeWindowPutPP
ScrCmd_PokeWindowPutPP: ; 0x0203BDB8
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r2, _0203BE4C ; =0x000003D9
	ldr r0, [r0, #0x8]
	mov r1, #0x3
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _0203BE4C ; =0x000003D9
	mov r1, #0x3
	str r0, [sp, #0x4]
	str r4, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xa
	ldr r0, [r0, #0x8]
	mov r3, #0x5
	bl FUN_0200DCA4
	str r0, [r6, #0x0]
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r0, #0x0
	add r5, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r5, #0x0]
	lsr r1, r1, #0x10
	bl FUN_0203ED2C
	mov r0, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0203BE4C: .word 0x000003D9

	thumb_func_start ScrCmd_PokeWindowDel
ScrCmd_PokeWindowDel: ; 0x0203BE50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeWindowAnm
ScrCmd_PokeWindowAnm: ; 0x0203BE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	strb r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeWindowAnmWait
ScrCmd_PokeWindowAnmWait: ; 0x0203BE80
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203BE98 ; =FUN_0203BE9C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203BE98: .word FUN_0203BE9C 

	thumb_func_start FUN_0203BE9C
FUN_0203BE9C: ; 0x0203BE9C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	ldr r0, [r4, #0x0]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	beq _0203BEC8
	mov r0, #0x1
	pop {r3-r5, pc}
_0203BEC8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_BtlSearcherEventCall
ScrCmd_BtlSearcherEventCall: ; 0x0203BECC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020394B8
	add r2, r0, #0x0
	ldr r0, [r5, #0x74]
	ldr r1, [r4, #0x0]
	bl MOD05_021E1374
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_BtlSearcherDirMvSet
ScrCmd_BtlSearcherDirMvSet: ; 0x0203BF00
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0203BF1C
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl MOD05_021E1994
_0203BF1C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_MsgBoyEvent
ScrCmd_MsgBoyEvent: ; 0x0203BF20
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_0208A338
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_ImageClipSetProc
ScrCmd_ImageClipSetProc: ; 0x0203BF2C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	ldr r2, [r5, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r2, #0x10]
	ldr r2, [r2, #0xc]
	add r3, r4, #0x0
	bl FUN_020380CC
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_ImageClipPreviewTvProc
ScrCmd_ImageClipPreviewTvProc: ; 0x0203BF84
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r5, #0x0
	add r1, #0x80
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xb
	mov r2, #0x0
	add r3, r7, #0x0
	bl FUN_0203BC6C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203BFCC
	mov r0, #0x1
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0203BFCC:
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02038130
	ldr r1, _0203BFE8 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203BFE8: .word FUN_0203BB90 

	thumb_func_start ScrCmd_ImageClipPreviewConProc
ScrCmd_ImageClipPreviewConProc: ; 0x0203BFEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r5, #0x0
	add r1, #0x80
	add r6, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0xb
	mov r2, #0x1
	add r3, r7, #0x0
	bl FUN_0203BC6C
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203C034
	mov r0, #0x1
	strh r0, [r6, #0x0]
	pop {r3-r7, pc}
_0203C034:
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02038130
	ldr r1, _0203C050 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203C050: .word FUN_0203BB90 

	thumb_func_start ScrCmd_ImageClipTvSaveDataCheck
ScrCmd_ImageClipTvSaveDataCheck: ; 0x0203C054
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x1
	bne _0203C088
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0203C088:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ImageClipConSaveDataCheck
ScrCmd_ImageClipConSaveDataCheck: ; 0x0203C090
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_0203BC3C
	cmp r0, #0x1
	bne _0203C0C4
	mov r0, #0x1
	strh r0, [r4, #0x0]
	pop {r4-r6, pc}
_0203C0C4:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ImageClipTvSaveTitle
ScrCmd_ImageClipTvSaveTitle: ; 0x0203C0CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	mov r1, #0x0
	bl FUN_02027008
	add r1, r4, #0x0
	bl FUN_02027478
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_WifiEarthSetProc
ScrCmd_WifiEarthSetProc: ; 0x0203C0FC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02038804
	ldr r1, _0203C114 ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203C114: .word FUN_0203BC04 

	thumb_func_start ScrCmd_CustomBallEventCall
ScrCmd_CustomBallEventCall: ; 0x0203C118
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, [r1, #0x74]
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	bl FUN_02085F48
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_TMapBGSetProc
ScrCmd_TMapBGSetProc: ; 0x0203C12C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	mov r1, #0x5
	add r4, r0, #0x0
	mov r0, #0xb
	lsl r1, r1, #0x6
	bl AllocFromHeap
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	mov r2, #0x2
	bl FUN_0205F7A0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02037E90
	ldr r1, _0203C170 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C170: .word FUN_0203BB90 

	thumb_func_start ScrCmd_NutMixerProc
ScrCmd_NutMixerProc: ; 0x0203C174
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r2, #0xb
	bl FUN_02088960
	str r0, [r4, #0x0]
	ldr r1, _0203C1A8 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C1A8: .word FUN_0203BB90 

	thumb_func_start ScrCmd_NutMixerPlayStateCheck
ScrCmd_NutMixerPlayStateCheck: ; 0x0203C1AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206F158
	mov r1, #0x4
	bl FUN_0206EE64
	cmp r0, #0x0
	bne _0203C1E0
	mov r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_0203C1E0:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	bl FUN_020281B8
	cmp r0, #0x64
	blo _0203C1FA
	mov r0, #0x2
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
_0203C1FA:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_BTowerAppSetProc
ScrCmd_BTowerAppSetProc: ; 0x0203C200
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x8
	str r0, [r6, #0x0]
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	strh r7, [r4, #0x4]
	strh r0, [r4, #0x6]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r6, #0x0]
	bl FUN_02037FE4
	ldr r1, _0203C274 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203C274: .word FUN_0203BB90 

	thumb_func_start ScrCmd_BoxSetProc
ScrCmd_BoxSetProc: ; 0x0203C278
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeap
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	str r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r1, [r2, #0x0]
	str r1, [r0, #0x4]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02037D60
	ldr r1, _0203C2C0 ; =FUN_0203BBBC
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C2C0: .word FUN_0203BBBC 

	thumb_func_start ScrCmd_OekakiBoardSetProc
ScrCmd_OekakiBoardSetProc: ; 0x0203C2C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020383F8
	ldr r1, _0203C2DC ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203C2DC: .word FUN_0203BC04 

	thumb_func_start ScrCmd_CallTrCard
ScrCmd_CallTrCard: ; 0x0203C2E0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02065344
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_TradeListSetProc
ScrCmd_TradeListSetProc: ; 0x0203C2F0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_020383D8
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_RecordCornerSetProc
ScrCmd_RecordCornerSetProc: ; 0x0203C300
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0203842C
	str r0, [r4, #0x0]
	ldr r1, _0203C328 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C328: .word FUN_0203BB90 

	thumb_func_start ScrCmd_DendouSetProc
ScrCmd_DendouSetProc: ; 0x0203C32C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02048694
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_PcDendouSetProc
ScrCmd_PcDendouSetProc: ; 0x0203C33C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02038824
	str r0, [r4, #0x0]
	ldr r1, _0203C364 ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203C364: .word FUN_0203BB90 

	thumb_func_start ScrCmd_WorldTradeSetProc
ScrCmd_WorldTradeSetProc: ; 0x0203C368
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0203384C
	cmp r0, #0x0
	beq _0203C3BC
	mov r0, #0x1
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020386E0
	ldr r1, _0203C3C4 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	b _0203C3C0
_0203C3BC:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203C3C0:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C3C4: .word FUN_0203BC04 

	thumb_func_start ScrCmd_DPWInitProc
ScrCmd_DPWInitProc: ; 0x0203C3C8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_0206F3D8
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_FirstPokeSelectProc
ScrCmd_FirstPokeSelectProc: ; 0x0203C3E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeap
	str r0, [r4, #0x0]
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r6, #0x4]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_020386A4
	ldr r1, _0203C42C ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0203C42C: .word FUN_0203BC04 

	thumb_func_start ScrCmd_FirstPokeSelectSetAndDel
ScrCmd_FirstPokeSelectSetAndDel: ; 0x0203C430
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x0]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0205F378
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_BagSetProc
ScrCmd_BagSetProc: ; 0x0203C460
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0203C474
	mov r0, #0x1
	b _0203C476
_0203C474:
	mov r0, #0x0
_0203C476:
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0203C492
	bl ErrorHandling
_0203C492:
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_0203789C
	str r0, [r6, #0x0]
	ldr r1, _0203C4AC ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C4AC: .word FUN_0203BC04 

	thumb_func_start ScrCmd_BagGetResult
ScrCmd_BagGetResult: ; 0x0203C4B0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203C4DC
	bl ErrorHandling
_0203C4DC:
	ldr r0, [r4, #0x0]
	bl FUN_020378FC
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_NameIn
ScrCmd_NameIn: ; 0x0203C4F0
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	add r2, r1, #0x0
	mov r3, #0x7
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start ScrCmd_NameInPoke
ScrCmd_NameInPoke: ; 0x0203C520
	push {r4-r7, lr}
	sub sp, #0x34
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	mov r1, #0x74
	add r2, sp, #0xc
	add r7, r0, #0x0
	bl FUN_020671BC
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	str r6, [sp, #0x0]
	add r0, sp, #0xc
	str r0, [sp, #0x4]
	str r4, [sp, #0x8]
	ldr r0, [r5, #0x74]
	mov r1, #0x1
	mov r3, #0xa
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0x34
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_NameInStone
ScrCmd_NameInStone: ; 0x0203C58C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r2, #0x0
	str r2, [sp, #0x0]
	str r2, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	mov r1, #0x6
	mov r3, #0xa
	bl FUN_020385CC
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start ScrCmd_PMSInputSingleProc
ScrCmd_PMSInputSingleProc: ; 0x0203C5BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r2, r0, #0x0
	ldr r0, _0203C610 ; =0x0000FFFF
	add r5, #0x80
	strh r0, [r2, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	mov r3, #0x0
	bl FUN_02037E18
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_0203C610: .word 0x0000FFFF

	thumb_func_start ScrCmd_PMSInputDoubleProc
ScrCmd_PMSInputDoubleProc: ; 0x0203C614
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r3, r0, #0x0
	ldr r0, _0203C67C ; =0x0000FFFF
	add r5, #0x80
	strh r0, [r4, #0x0]
	strh r0, [r3, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x10]
	add r2, r4, #0x0
	bl FUN_02037E18
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203C67C: .word 0x0000FFFF

	thumb_func_start ScrCmd_PMSBuf
ScrCmd_PMSBuf: ; 0x0203C680
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_0200B518
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_WipeFadeStart
ScrCmd_WipeFadeStart: ; 0x0203C6C4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	add r3, r0, #0x0
	str r6, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r7, #0x0
	add r2, r7, #0x0
	bl FUN_0200E1D0
	mov r0, #0x0
	bl FUN_0200E388
	mov r0, #0x1
	bl FUN_0200E388
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_WipeFadeCheck
ScrCmd_WipeFadeCheck: ; 0x0203C70C
	push {r3, lr}
	ldr r1, _0203C718 ; =FUN_0203C71C
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0203C718: .word FUN_0203C71C 

	thumb_func_start FUN_0203C71C
FUN_0203C71C: ; 0x0203C71C
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0203C72A
	mov r0, #0x1
	pop {r3, pc}
_0203C72A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_MapChange
ScrCmd_MapChange: ; 0x0203C730
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r2, #0x0
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	mvn r2, r2
	add r3, r7, #0x0
	bl FUN_02049240
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_ColosseumMapChangeIn
ScrCmd_ColosseumMapChangeIn: ; 0x0203C788
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r4, [sp, #0x0]
	mov r2, #0x0
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x10]
	mvn r2, r2
	add r3, r7, #0x0
	bl FUN_02049F98
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_ColosseumMapChangeOut
ScrCmd_ColosseumMapChangeOut: ; 0x0203C7E4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02049FFC
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_GetBeforeZoneID
ScrCmd_GetBeforeZoneID: ; 0x0203C7F4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DC8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	ldr r1, [r5, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_GetNowZoneID
ScrCmd_GetNowZoneID: ; 0x0203C820
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	ldr r1, [r4, #0x0]
	ldr r1, [r1, #0x1c]
	ldr r1, [r1, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_KabeNobori
ScrCmd_KabeNobori: ; 0x0203C844
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl MOD05_021E6990
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Naminori
ScrCmd_Naminori: ; 0x0203C874
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl MOD05_021E6410
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Takinobori
ScrCmd_Takinobori: ; 0x0203C8B4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x74]
	add r2, r4, #0x0
	bl MOD05_021E6BF4
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_Sorawotobu
ScrCmd_Sorawotobu: ; 0x0203C8E4
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	mov r2, #0x1
	str r2, [sp, #0x4]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	sub r2, r2, #0x2
	add r3, r6, #0x0
	bl FUN_02049274
	mov r0, #0x1
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_HidenFlash
ScrCmd_HidenFlash: ; 0x0203C930
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_02034DF4
	add r0, r5, #0x0
	bl FUN_02034DEC
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xc]
	bl MOD05_021DC174
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_HidenKiribarai
ScrCmd_HidenKiribarai: ; 0x0203C960
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r5, r0, #0x0
	mov r1, #0x0
	bl FUN_02034DF4
	add r0, r5, #0x0
	bl FUN_02034DEC
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xc]
	bl MOD05_021DC174
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_CutIn
ScrCmd_CutIn: ; 0x0203C990
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206B9B0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553E8
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r2, r6, #0x0
	bl MOD06_0224666C
	str r0, [r4, #0x0]
	ldr r1, _0203C9F4 ; =FUN_0203C9F8
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0203C9F4: .word FUN_0203C9F8 

	thumb_func_start FUN_0203C9F8
FUN_0203C9F8: ; 0x0203C9F8
	push {r4, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD06_022466A0
	cmp r0, #0x1
	bne _0203CA1A
	ldr r0, [r4, #0x0]
	bl MOD06_022466AC
	mov r0, #0x1
	pop {r4, pc}
_0203CA1A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_ConHeroChange
ScrCmd_ConHeroChange: ; 0x0203CA20
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl MOD05_021E7030
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_BicycleCheck
ScrCmd_BicycleCheck: ; 0x0203CA2C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553C4
	cmp r0, #0x1
	bne _0203CA54
	mov r0, #0x1
	b _0203CA56
_0203CA54:
	mov r0, #0x0
_0203CA56:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_BicycleReq
ScrCmd_BicycleReq: ; 0x0203CA5C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x8]
	add r0, r1, #0x1
	str r0, [r4, #0x8]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x1
	bne _0203CAA4
	add r0, r4, #0x0
	add r0, #0x80
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x6
	bl FUN_0204AB20
	add r0, r4, #0x0
	add r0, #0x80
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x6
	mov r2, #0x1
	bl FUN_0204ABDC
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FD8
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FE0
	b _0203CAE4
_0203CAA4:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FD8
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FE0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	bl FUN_0204AB20
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x1c]
	ldr r1, [r1, #0x0]
	bl FUN_0204AB58
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	bl FUN_0204ABDC
_0203CAE4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_BicycleReqNonBgm
ScrCmd_BicycleReqNonBgm: ; 0x0203CAE8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x2
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FD8
	add r4, #0x80
	mov r1, #0x12
	ldr r0, [r4, #0x0]
	lsl r1, r1, #0x6
	bl FUN_0204AB20
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_CyclingRoadSet
ScrCmd_CyclingRoadSet: ; 0x0203CB08
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055720
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_PlayerFormGet
ScrCmd_PlayerFormGet: ; 0x0203CB20
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553C4
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PlayerReqBitOn
ScrCmd_PlayerReqBitOn: ; 0x0203CB48
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_020553D4
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_PlayerReqStart
ScrCmd_PlayerReqStart: ; 0x0203CB60
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl MOD05_021E5FE0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_GenerateInfoGet
ScrCmd_GenerateInfoGet: ; 0x0203CB70
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202A9B0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0202A990
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl MOD06_02245910
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_FirstPokeNoGet
ScrCmd_FirstPokeNoGet: ; 0x0203CBBC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F388
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_TrainerMessageSet
ScrCmd_TrainerMessageSet: ; 0x0203CBE8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r4, [r0, #0x0]
	mov r1, #0x8
	add r0, r4, #0x0
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x6
	bl FUN_02039438
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r2, [r6, #0x0]
	mov r3, #0xb
	bl FUN_0206AD4C
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl LoadPlayerDataAddress
	add r2, r0, #0x0
	ldr r1, [r6, #0x0]
	add r0, r4, #0x0
	mov r3, #0x1
	bl FUN_02054658
	strb r0, [r7, #0x0]
	ldr r1, _0203CC84 ; =FUN_0203A2F0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203CC84: .word FUN_0203A2F0 

	thumb_func_start ScrCmd_ConnectSelParentWin
ScrCmd_ConnectSelParentWin: ; 0x0203CC88
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MOD06_02240790
	ldr r1, _0203CCF4 ; =FUN_0203CCF8
	add r0, r5, #0x0
	str r6, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203CCF4: .word FUN_0203CCF8 

	thumb_func_start FUN_0203CCF8
FUN_0203CCF8: ; 0x0203CCF8
	push {r4, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	bl MOD06_022407DC
	cmp r0, #0x0
	bne _0203CD18
	mov r0, #0x0
	pop {r4, pc}
_0203CD18:
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_ConnectSelChildWin
ScrCmd_ConnectSelChildWin: ; 0x0203CD20
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MOD06_022407F8
	ldr r1, _0203CD8C ; =FUN_0203CD90
	add r0, r5, #0x0
	str r6, [r5, #0x64]
	bl SetupNativeScript
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0203CD8C: .word FUN_0203CD90 

	thumb_func_start FUN_0203CD90
FUN_0203CD90: ; 0x0203CD90
	push {r4, lr}
	add r1, r0, #0x0
	ldr r1, [r1, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	bl MOD06_02240844
	cmp r0, #0x0
	bne _0203CDB0
	mov r0, #0x0
	pop {r4, pc}
_0203CDB0:
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_ConnectDebugParentWin
ScrCmd_ConnectDebugParentWin: ; 0x0203CDB8
	push {r3, lr}
	bl ScriptReadHalfword
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_ConnectDebugChildWin
ScrCmd_ConnectDebugChildWin: ; 0x0203CDC4
	push {r3, lr}
	bl ScriptReadHalfword
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_DebugSioEncount
ScrCmd_DebugSioEncount: ; 0x0203CDD0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r6, r0, #0x0
	add r5, #0x80
	ldr r4, [r6, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0x10]
	add r1, #0x2c
	mov r2, #0x5
	bl FUN_02047174
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r6, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_DebugSioContest
ScrCmd_DebugSioContest: ; 0x0203CE00
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02080C38
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_SpLocationSet
ScrCmd_SpLocationSet: ; 0x0203CE0C
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, #0x80
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r1, sp, #0x0
	bl FUN_02034DD4
	mov r0, #0x0
	add sp, #0x14
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start ScrCmd_ElevatorNowFloorGet
ScrCmd_ElevatorNowFloorGet: ; 0x0203CE8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DD0
	ldr r0, [r0, #0x0]
	bl MOD05_021E2608
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ElevatorFloorWrite
ScrCmd_ElevatorFloorWrite: ; 0x0203CEBC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	str r0, [sp, #0x4]
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [r5, #0x8]
	add r1, r0, #0x1
	str r1, [r5, #0x8]
	ldrb r6, [r0, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r3, r0, #0x0
	ldr r0, [r7, #0x0]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	add r2, r4, #0x0
	bl MOD05_021E2464
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_GetShinouZukanSeeNum
ScrCmd_GetShinouZukanSeeNum: ; 0x0203CF04
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020244A4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetShinouZukanGetNum
ScrCmd_GetShinouZukanGetNum: ; 0x0203CF34
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202445C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetZenkokuZukanSeeNum
ScrCmd_GetZenkokuZukanSeeNum: ; 0x0203CF64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02024404
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetZenkokuZukanGetNum
ScrCmd_GetZenkokuZukanGetNum: ; 0x0203CF94
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020243C8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ChkZenkokuZukan
ScrCmd_ChkZenkokuZukan: ; 0x0203CFC4
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_GetZukanHyoukaMsgID
ScrCmd_GetZukanHyoukaMsgID: ; 0x0203CFC8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x0]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r6, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	cmp r6, #0x0
	bne _0203D02E
	add r0, r7, #0x0
	bl FUN_02024550
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	mov r1, #0x2
	mov r2, #0xa
	bl FUN_0205F2E4
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_02054CC8
	b _0203D048
_0203D02E:
	add r0, r7, #0x0
	bl FUN_02024518
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020239CC
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_02054D1C
_0203D048:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_WildBattleSet
ScrCmd_WildBattleSet: ; 0x0203D050
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	add r3, r4, #0x0
	bl FUN_02046E18
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_SpWildBattleSet
ScrCmd_SpWildBattleSet: ; 0x0203D0A4
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	add r3, r4, #0x0
	bl FUN_02046E18
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_FirstBattleSet
ScrCmd_FirstBattleSet: ; 0x0203D0F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x74]
	add r1, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_02046FA0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_CaptureBattleSet
ScrCmd_CaptureBattleSet: ; 0x0203D134
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_020470AC
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_HoneyTree
ScrCmd_HoneyTree: ; 0x0203D140
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD05_021F4DC8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_GetHoneyTreeState
ScrCmd_GetHoneyTreeState: ; 0x0203D150
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl MOD05_021F4D80
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_HoneyTreeBattleSet
ScrCmd_HoneyTreeBattleSet: ; 0x0203D178
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x17
	bl FUN_02039438
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_02046DB4
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_HoneyAfterTreeBattleSet
ScrCmd_HoneyAfterTreeBattleSet: ; 0x0203D194
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD05_021F4E7C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_TSignSetProc
ScrCmd_TSignSetProc: ; 0x0203D1A4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020386B4
	ldr r1, _0203D1BC ; =FUN_0203BC04
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D1BC: .word FUN_0203BC04 

	thumb_func_start ScrCmd_ReportSaveCheck
ScrCmd_ReportSaveCheck: ; 0x0203D1C0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r5, [r1, #0xc]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202280C
	cmp r0, #0x0
	beq _0203D1EC
	mov r0, #0x0
	strh r0, [r4, #0x0]
	b _0203D210
_0203D1EC:
	add r0, r5, #0x0
	bl FUN_02022804
	cmp r0, #0x0
	bne _0203D1FC
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203D210
_0203D1FC:
	add r0, r5, #0x0
	bl FUN_0202282C
	cmp r0, #0x0
	beq _0203D20C
	mov r0, #0x2
	strh r0, [r4, #0x0]
	b _0203D210
_0203D20C:
	mov r0, #0x3
	strh r0, [r4, #0x0]
_0203D210:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ReportSave
ScrCmd_ReportSave: ; 0x0203D214
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl MOD05_021E85FC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetPoketch
ScrCmd_GetPoketch: ; 0x0203D23C
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl MOD05_021E3424
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_GetPoketchFlag
ScrCmd_GetPoketchFlag: ; 0x0203D248
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0204C1A8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204BEC8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PoketchAppAdd
ScrCmd_PoketchAppAdd: ; 0x0203D278
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0204C1A8
	add r1, r5, #0x0
	bl FUN_0204BED8
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PoketchAppCheck
ScrCmd_PoketchAppCheck: ; 0x0203D2A4
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0204C1A8
	add r1, r6, #0x0
	bl FUN_0204BED0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_CommTimingSyncStart
ScrCmd_CommTimingSyncStart: ; 0x0203D2E4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [r4, #0x64]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02031588
	ldr r1, _0203D310 ; =FUN_0203D314
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D310: .word FUN_0203D314 

	thumb_func_start FUN_0203D314
FUN_0203D314: ; 0x0203D314
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F20
	cmp r0, #0x2
	bge _0203D324
	mov r0, #0x1
	pop {r4, pc}
_0203D324:
	ldr r0, [r4, #0x64]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020315D8
	pop {r4, pc}

	thumb_func_start ScrCmd_CommTempDataReset
ScrCmd_CommTempDataReset: ; 0x0203D330
	push {r3, lr}
	bl FUN_0203168C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionParentCardTalkNo
ScrCmd_UnionParentCardTalkNo: ; 0x0203D33C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionGetInfoTalkNo
ScrCmd_UnionGetInfoTalkNo: ; 0x0203D36C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r1, r0, #0x0
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052C0C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionBeaconChange
ScrCmd_UnionBeaconChange: ; 0x0203D3A4
	push {r4, lr}
	bl ScriptReadHalfword
	add r4, r0, #0x0
	cmp r4, #0x5
	beq _0203D3BC
	cmp r4, #0x7
	beq _0203D3BC
	cmp r4, #0x9
	beq _0203D3BC
	cmp r4, #0x6
	bne _0203D3C2
_0203D3BC:
	bl FUN_02031C54
	b _0203D3CA
_0203D3C2:
	cmp r4, #0xb
	bne _0203D3CA
	bl FUN_02031C64
_0203D3CA:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203D3D8
	add r0, r4, #0x0
	bl FUN_02052B74
_0203D3D8:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start ScrCmd_UnionTrainerNameRegist
ScrCmd_UnionTrainerNameRegist: ; 0x0203D3DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	bl FUN_020377AC
	bl FUN_02013B5C
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _0203D432
	ldr r0, [r7, #0x0]
	bl FUN_02058448
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	b _0203D434
_0203D432:
	mov r2, #0x0
_0203D434:
	str r5, [sp, #0x0]
	ldr r0, [r6, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_02052D08
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionReturnSetUp
ScrCmd_UnionReturnSetUp: ; 0x0203D448
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0208881C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionConnectCutRestart
ScrCmd_UnionConnectCutRestart: ; 0x0203D458
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x7c]
	bl FUN_02052F74
	bl FUN_02031B50
	ldr r1, _0203D478 ; =FUN_0203D47C
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D478: .word FUN_0203D47C 

	thumb_func_start FUN_0203D47C
FUN_0203D47C: ; 0x0203D47C
	push {r3, lr}
	bl FUN_02030F20
	cmp r0, #0x2
	bge _0203D48A
	mov r0, #0x1
	pop {r3, pc}
_0203D48A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionGetTalkNumber
ScrCmd_UnionGetTalkNumber: ; 0x0203D490
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_02058448
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x0]
	ldr r0, [r0, #0x78]
	ldr r3, [r7, #0x0]
	bl FUN_02052A10
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionBattleStartCheck
ScrCmd_UnionBattleStartCheck: ; 0x0203D4E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_020527A8
	strh r0, [r4, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0203D522
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FreeToHeap
_0203D522:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionIdSet
ScrCmd_UnionIdSet: ; 0x0203D528
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xa
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	ldr r0, [r5, #0x78]
	bl FUN_020524CC
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_UnionConnectStart
ScrCmd_UnionConnectStart: ; 0x0203D560
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0xa
	add r0, r5, #0x0
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r0, #0x0
	ldr r0, [r5, #0x78]
	add r2, r7, #0x0
	bl FUN_02052544
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionResultGet
ScrCmd_UnionResultGet: ; 0x0203D5B0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D5C8 ; =FUN_0203D5CC
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D5C8: .word FUN_0203D5CC 

	thumb_func_start FUN_0203D5CC
FUN_0203D5CC: ; 0x0203D5CC
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r0, #0x80
	ldr r5, [r0, #0x0]
	ldr r0, [r5, #0x78]
	bl FUN_02052604
	ldr r1, [r6, #0x64]
	add r4, r0, #0x0
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_020394B8
	cmp r4, #0x0
	bne _0203D5F0
	mov r0, #0x0
	pop {r4-r6, pc}
_0203D5F0:
	strh r4, [r0, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionObjAllVanish
ScrCmd_UnionObjAllVanish: ; 0x0203D5F8
	push {r3, lr}
	add r0, #0x80
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x34]
	ldr r1, [r1, #0x7c]
	bl FUN_020534DC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionConnectTalkDenied
ScrCmd_UnionConnectTalkDenied: ; 0x0203D60C
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02052B74
	bl FUN_02031C2C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_UnionConnectTalkOk
ScrCmd_UnionConnectTalkOk: ; 0x0203D61C
	push {r3, lr}
	bl FUN_02031C64
	bl FUN_02031B50
	mov r0, #0x0
	bl FUN_02052B74
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_UnionScriptResultSet
ScrCmd_UnionScriptResultSet: ; 0x0203D630
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r4, #0x78]
	add r1, r6, #0x0
	bl FUN_0205265C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionParentStartCommandSet
ScrCmd_UnionParentStartCommandSet: ; 0x0203D66C
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D684 ; =FUN_0203D688
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D684: .word FUN_0203D688 

	thumb_func_start FUN_0203D688
FUN_0203D688: ; 0x0203D688
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052608
	cmp r0, #0x1
	blo _0203D6BC
	add r5, #0x80
	strh r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052E10
	mov r0, #0x1
	pop {r3-r5, pc}
_0203D6BC:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionChildSelectCommandSet
ScrCmd_UnionChildSelectCommandSet: ; 0x0203D6C4
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	str r0, [r4, #0x64]
	ldr r1, _0203D6DC ; =FUN_0203D6E0
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	nop
_0203D6DC: .word FUN_0203D6E0 

	thumb_func_start FUN_0203D6E0
FUN_0203D6E0: ; 0x0203D6E0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x78]
	bl FUN_02052648
	ldr r1, _0203D724 ; =gUnknown21C48B8
	ldr r2, [r1, #0x48]
	mov r1, #0x2
	tst r1, r2
	beq _0203D716
	add r5, #0x80
	ldr r0, [r5, #0x0]
	mov r1, #0x8
	ldr r0, [r0, #0x78]
	bl FUN_02052718
_0203D716:
	cmp r0, #0x0
	beq _0203D720
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
_0203D720:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203D724: .word gUnknown21C48B8

	thumb_func_start ScrCmd_UnionMapChange
ScrCmd_UnionMapChange: ; 0x0203D728
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02049EA4
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_UnionViewSetUpTrainerTypeSelect
ScrCmd_UnionViewSetUpTrainerTypeSelect: ; 0x0203D738
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239CC
	add r1, r0, #0x0
	ldr r2, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_0205363C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionViewGetTrainerType
ScrCmd_UnionViewGetTrainerType: ; 0x0203D774
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239CC
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02053678
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020239CC
	ldrh r1, [r4, #0x0]
	mov r2, #0x2
	bl FUN_020536D0
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionViewGetTrainerTypeNo
ScrCmd_UnionViewGetTrainerTypeNo: ; 0x0203D7DC
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020239CC
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02053678
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionViewMyStatusSet
ScrCmd_UnionViewMyStatusSet: ; 0x0203D834
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02023A2C
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GameOverCall
ScrCmd_GameOverCall: ; 0x0203D868
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02048498
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_SetWarpId
ScrCmd_SetWarpId: ; 0x0203D874
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r1, r4, #0x0
	bl FUN_02034E04
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetMySex
ScrCmd_GetMySex: ; 0x0203D8A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020377AC
	bl FUN_020238F4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020239CC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_PcKaifuku
ScrCmd_PcKaifuku: ; 0x0203D8D0
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02046528
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	bl FUN_02085140
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UgManShopNpcRandomPlace
ScrCmd_UgManShopNpcRandomPlace: ; 0x0203D8E8
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_CommDirectEnd
ScrCmd_CommDirectEnd: ; 0x0203D8EC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02050024
	ldr r1, _0203D900 ; =FUN_0203D904
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D900: .word FUN_0203D904 

	thumb_func_start FUN_0203D904
FUN_0203D904: ; 0x0203D904
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x1
	beq _0203D91A
	bl FUN_0202EDF8
	cmp r0, #0x1
	beq _0203D91A
	mov r0, #0x1
	pop {r3, pc}
_0203D91A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_CommDirectEndTiming
ScrCmd_CommDirectEndTiming: ; 0x0203D920
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02050048
	ldr r1, _0203D934 ; =FUN_0203D904
	add r0, r4, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203D934: .word FUN_0203D904 

	thumb_func_start ScrCmd_CommDirectEnterBtlRoom
ScrCmd_CommDirectEnterBtlRoom: ; 0x0203D938
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204FF5C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_CommPlayerSetDir
ScrCmd_CommPlayerSetDir: ; 0x0203D948
	push {r3, lr}
	bl ScriptReadHalfword
	bl FUN_0204F6DC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PocketCheck
ScrCmd_PocketCheck: ; 0x0203D958
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206F158
	add r1, r6, #0x0
	bl FUN_0206EE64
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_SxyPosChange
ScrCmd_SxyPosChange: ; 0x0203D998
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034B74
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_ObjPosChange
ScrCmd_ObjPosChange: ; 0x0203D9E8
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r5, r0, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_02058E28
	add r0, r5, #0x0
	bl FUN_02059D1C
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_SxyMoveCodeChange
ScrCmd_SxyMoveCodeChange: ; 0x0203DA78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02034BDC
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_SxyDirChange
ScrCmd_SxyDirChange: ; 0x0203DAB0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r2, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02034BAC
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_SxyExitPosChange
ScrCmd_SxyExitPosChange: ; 0x0203DAE8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034C0C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_SxyBgPosChange
ScrCmd_SxyBgPosChange: ; 0x0203DB38
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r3, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02034C34
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_ObjDirChange
ScrCmd_ObjDirChange: ; 0x0203DB88
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203DBC6
	bl ErrorHandling
_0203DBC6:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl MOD05_021F1EC0
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_ReturnScriptWkSet
ScrCmd_ReturnScriptWkSet: ; 0x0203DBD4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xc
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	ldr r1, [r5, #0x0]
	cmp r1, #0x0
	beq _0203DBFC
	strh r0, [r1, #0x0]
_0203DBFC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_SetUpDoorAnime
ScrCmd_SetUpDoorAnime: ; 0x0203DC00
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	lsl r1, r4, #0x5
	ldr r3, [r5, #0x8]
	add r2, r0, #0x0
	add r0, r3, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	lsl r4, r6, #0x5
	ldrb r3, [r3, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r7, r1
	add r2, r2, r4
	bl MOD05_021DAE40
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_Wait3DAnime
ScrCmd_Wait3DAnime: ; 0x0203DC58
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAF78
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_Free3DAnime
ScrCmd_Free3DAnime: ; 0x0203DC70
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAF98
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_OpenDoor
ScrCmd_OpenDoor: ; 0x0203DC88
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAED4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_CloseDoor
ScrCmd_CloseDoor: ; 0x0203DCA0
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl MOD05_021DAF28
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_InitWaterGym
ScrCmd_InitWaterGym: ; 0x0203DCB8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064CA8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_PushWaterGymButton
ScrCmd_PushWaterGymButton: ; 0x0203DCC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_02241230
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_InitGhostGym
ScrCmd_InitGhostGym: ; 0x0203DCD8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064CC8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_MoveGhostGymLift
ScrCmd_MoveGhostGymLift: ; 0x0203DCE8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_02241914
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_InitSteelGym
ScrCmd_InitSteelGym: ; 0x0203DCF8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064D10
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_InitCombatGym
ScrCmd_InitCombatGym: ; 0x0203DD08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064D4C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_InitElecGym
ScrCmd_InitElecGym: ; 0x0203DD18
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_02064D88
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_RotElecGymGear
ScrCmd_RotElecGymGear: ; 0x0203DD34
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_02242A38
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_TamagoDemo
ScrCmd_TamagoDemo: ; 0x0203DD50
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020388B4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UgShopMenuInit
ScrCmd_UgShopMenuInit: ; 0x0203DD60
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xa
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r0, [r5, #0x64]
	ldr r0, [r6, #0x0]
	bl FUN_02058448
	add r1, r5, #0x0
	add r1, #0x80
	add r2, r0, #0x0
	ldr r1, [r1, #0x0]
	add r0, r7, #0x0
	bl MOD18_0224CA54
	str r0, [r4, #0x0]
	ldr r1, _0203DDBC ; =FUN_0203DDC0
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0203DDBC: .word FUN_0203DDC0 

	thumb_func_start FUN_0203DDC0
FUN_0203DDC0: ; 0x0203DDC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	ldr r1, [r5, #0x64]
	add r0, #0x80
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x0]
	lsr r1, r1, #0x10
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD18_0224CA2C
	strh r0, [r5, #0x0]
	ldrh r1, [r5, #0x0]
	ldr r0, _0203DDFC ; =0x0000FFFE
	cmp r1, r0
	beq _0203DDF6
	mov r0, #0x1
	pop {r3-r5, pc}
_0203DDF6:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203DDFC: .word 0x0000FFFE

	thumb_func_start ScrCmd_UgShopTalkStart
ScrCmd_UgShopTalkStart: ; 0x0203DE00
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	bl MOD06_0224CA58
	strb r0, [r4, #0x0]
	ldr r1, _0203DE34 ; =FUN_0203DE38
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203DE34: .word FUN_0203DE38 

	thumb_func_start FUN_0203DE38
FUN_0203DE38: ; 0x0203DE38
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x3
	bl FUN_02039438
	ldrb r0, [r0, #0x0]
	bl FUN_020546C8
	pop {r3, pc}

	thumb_func_start ScrCmd_UgShopTalkEnd
ScrCmd_UgShopTalkEnd: ; 0x0203DE4C
	push {r3, lr}
	bl MOD11_0224CA94
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UgShopTalkRegisterItemName
ScrCmd_UgShopTalkRegisterItemName: ; 0x0203DE58
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD18_0224CAA0
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UgShopTalkRegisterTrapName
ScrCmd_UgShopTalkRegisterTrapName: ; 0x0203DE80
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x8]
	add r1, r2, #0x1
	str r1, [r4, #0x8]
	ldrb r5, [r2, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD18_0224CAB4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GuinnessWin
ScrCmd_GuinnessWin: ; 0x0203DEA8
	push {r3, lr}
	sub sp, #0x8
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r1, #0x1
	ldr r0, [r0, #0x74]
	add r2, r1, #0x0
	bl MOD06_02242BE0
	mov r0, #0x1
	add sp, #0x8
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_ObjVisible
ScrCmd_ObjVisible: ; 0x0203DEC4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r4, r0, #0x0
	bne _0203DEEC
	bl ErrorHandling
_0203DEEC:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0205889C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ObjInvisible
ScrCmd_ObjInvisible: ; 0x0203DEF8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r5, #0x34]
	bl FUN_02058060
	add r4, r0, #0x0
	bne _0203DF20
	bl ErrorHandling
_0203DF20:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0205889C
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_MailBox
ScrCmd_MailBox: ; 0x0203DF2C
	push {r3, lr}
	ldr r0, [r0, #0x74]
	bl FUN_02066818
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_GetMailBoxDataNum
ScrCmd_GetMailBoxDataNum: ; 0x0203DF38
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02025838
	mov r1, #0x0
	bl FUN_0202589C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_RankingView
ScrCmd_RankingView: ; 0x0203DF64
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl FUN_02063650
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_GetTimeZone
ScrCmd_GetTimeZone: ; 0x0203DF84
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204B2A4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_GetRand
ScrCmd_GetRand: ; 0x0203DFA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bl rand_LC
	add r1, r5, #0x0
	bl _s32_div_f
	strh r1, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_GetRandNext
ScrCmd_GetRandNext: ; 0x0203DFE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	bl rand_LC
	add r1, r5, #0x0
	bl _s32_div_f
	strh r1, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_OokisaRecordChk
ScrCmd_OokisaRecordChk: ; 0x0203E018
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl MOD05_021F3A18
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_OokisaRecordSet
ScrCmd_OokisaRecordSet: ; 0x0203E054
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x80
	ldr r5, [r1, #0x0]
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl MOD05_021F3AB4
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_OokisaTemotiSet
ScrCmd_OokisaTemotiSet: ; 0x0203E078
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r3, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD05_021F3B7C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_OokisaKirokuSet
ScrCmd_OokisaKirokuSet: ; 0x0203E0CC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	lsl r1, r6, #0x18
	lsl r2, r7, #0x18
	add r3, r0, #0x0
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD05_021F3B4C
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_OokisaKurabeInit
ScrCmd_OokisaKurabeInit: ; 0x0203E120
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	mov r1, #0x82
	lsl r1, r1, #0x8
	bl FUN_0205F3F8
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_FNoteStartSet
ScrCmd_FNoteStartSet: ; 0x0203E138
	push {r4, lr}
	add r0, #0x80
	ldr r4, [r0, #0x0]
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	mov r1, #0x1
	bl FUN_0205F2D4
	ldr r0, [r4, #0xc]
	bl FUN_020289A4
	mov r1, #0x1
	bl FUN_020289B0
	add r1, r4, #0x0
	add r1, #0x98
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_02048C58
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_FNoteDataMake
ScrCmd_FNoteDataMake: ; 0x0203E168
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r5, r0, #0x0
	add r0, r7, #0x0
	sub r0, #0x10
	cmp r0, #0xa
	bhi _0203E23A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203E1EA: ; jump table (using 16-bit offset)
	.short _0203E200 - _0203E1EA - 2; case 0
	.short _0203E20C - _0203E1EA - 2; case 1
	.short _0203E218 - _0203E1EA - 2; case 2
	.short _0203E226 - _0203E1EA - 2; case 3
	.short _0203E23A - _0203E1EA - 2; case 4
	.short _0203E226 - _0203E1EA - 2; case 5
	.short _0203E226 - _0203E1EA - 2; case 6
	.short _0203E226 - _0203E1EA - 2; case 7
	.short _0203E226 - _0203E1EA - 2; case 8
	.short _0203E226 - _0203E1EA - 2; case 9
	.short _0203E226 - _0203E1EA - 2; case 10
_0203E200:
	mov r0, #0x4
	mov r6, #0x1
	bl FUN_02029120
	str r0, [r5, #0x0]
	b _0203E23E
_0203E20C:
	mov r0, #0x4
	mov r6, #0x1
	bl FUN_0202912C
	str r0, [r5, #0x0]
	b _0203E23E
_0203E218:
	ldr r0, [sp, #0x0]
	mov r1, #0x4
	mov r6, #0x1
	bl FUN_02029138
	str r0, [r5, #0x0]
	b _0203E23E
_0203E226:
	sub r7, #0x13
	lsl r0, r7, #0x18
	ldr r1, [sp, #0x0]
	lsr r0, r0, #0x18
	mov r2, #0x4
	mov r6, #0x1
	bl FUN_0202914C
	str r0, [r5, #0x0]
	b _0203E23E
_0203E23A:
	mov r0, #0x1
	pop {r3-r7, pc}
_0203E23E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r1, [r5, #0x0]
	add r0, #0x98
	ldr r0, [r0, #0x0]
	add r2, r6, #0x0
	bl FUN_02028AD4
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_FNoteDataSave
ScrCmd_FNoteDataSave: ; 0x0203E254
	mov r0, #0x0
	bx lr

	thumb_func_start ScrCmd_ImcAcceAddItem
ScrCmd_ImcAcceAddItem: ; 0x0203E258
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020271A4
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ImcAcceAddItemChk
ScrCmd_ImcAcceAddItemChk: ; 0x0203E29C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020270D8
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_ImcAcceCheckItem
ScrCmd_ImcAcceCheckItem: ; 0x0203E2F8
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r7, #0x0
	bl FUN_02027114
	cmp r6, r0
	bhi _0203E352
	mov r0, #0x1
	b _0203E354
_0203E352:
	mov r0, #0x0
_0203E354:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_ImcBgAddItem
ScrCmd_ImcBgAddItem: ; 0x0203E35C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	bl FUN_02027264
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ImcBgCheckItem
ScrCmd_ImcBgCheckItem: ; 0x0203E38C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r6, #0x0
	bl FUN_02027100
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ZukanChkShinou
ScrCmd_ZukanChkShinou: ; 0x0203E3D0
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02024504
	cmp r0, #0x1
	bne _0203E404
	mov r0, #0x1
	strh r0, [r4, #0x0]
_0203E404:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ZukanChkNational
ScrCmd_ZukanChkNational: ; 0x0203E408
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_020244EC
	cmp r0, #0x1
	bne _0203E43C
	mov r0, #0x1
	strh r0, [r4, #0x0]
_0203E43C:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ZukanRecongnizeShinou
ScrCmd_ZukanRecongnizeShinou: ; 0x0203E440
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x20
	mov r2, #0x0
	bl FUN_02038AF4
	str r0, [r4, #0x0]
	ldr r1, _0203E46C ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203E46C: .word FUN_0203BB90 

	thumb_func_start ScrCmd_ZukanRecongnizeNational
ScrCmd_ZukanRecongnizeNational: ; 0x0203E470
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x20
	mov r2, #0x1
	bl FUN_02038AF4
	str r0, [r4, #0x0]
	ldr r1, _0203E49C ; =FUN_0203BB90
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0203E49C: .word FUN_0203BB90 

	thumb_func_start ScrCmd_UrayamaEncountSet
ScrCmd_UrayamaEncountSet: ; 0x0203E4A0
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl MOD06_0224CBB0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_UrayamaEncountNoChk
ScrCmd_UrayamaEncountNoChk: ; 0x0203E4B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl MOD06_0224CC24
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PaperplaneSet
ScrCmd_PaperplaneSet: ; 0x0203E4D8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_RecordInc
ScrCmd_RecordInc: ; 0x0203E4F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r4, #0x0
	bl FUN_0202A0E8
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_RecordGet
ScrCmd_RecordGet: ; 0x0203E510
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r6, #0x0
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r7, #0x0
	bl FUN_0202A150
	ldr r1, _0203E564 ; =0xFFFF0000
	and r1, r0
	lsr r1, r1, #0x10
	strh r1, [r4, #0x0]
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203E564: .word 0xFFFF0000

	thumb_func_start ScrCmd_RecordSet
ScrCmd_RecordSet: ; 0x0203E568
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	lsl r2, r4, #0x10
	add r4, r2, #0x0
	orr r4, r0
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0203E59C
	cmp r0, #0x1
	beq _0203E5B0
	cmp r0, #0x2
	beq _0203E5C4
	b _0203E5D6
_0203E59C:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A11C
	b _0203E5D6
_0203E5B0:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A07C
	b _0203E5D6
_0203E5C4:
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202A0A8
_0203E5D6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_SafariControl
ScrCmd_SafariControl: ; 0x0203E5DC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022504
	ldr r1, [r5, #0x8]
	str r0, [sp, #0x4]
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r4, [r1, #0x0]
	add r0, r7, #0x0
	bl FUN_02034E24
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl FUN_02034E28
	add r7, r0, #0x0
	cmp r4, #0x0
	beq _0203E62C
	cmp r4, #0x1
	beq _0203E642
	b _0203E66E
_0203E62C:
	ldr r0, [sp, #0x0]
	bl FUN_0205F1F4
	ldr r0, [sp, #0x4]
	bl FUN_02060FD0
	mov r0, #0x1e
	strh r0, [r6, #0x0]
	mov r0, #0x0
	strh r0, [r7, #0x0]
	b _0203E66E
_0203E642:
	ldr r0, [sp, #0x0]
	bl FUN_0205F204
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02061574
	mov r0, #0x4
	bl FUN_0202912C
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r2, #0x1
	add r0, #0x98
	ldr r0, [r0, #0x0]
	bl FUN_02028AD4
	mov r0, #0x0
	strh r0, [r6, #0x0]
	strh r0, [r7, #0x0]
_0203E66E:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_CallSafariScope
ScrCmd_CallSafariScope: ; 0x0203E674
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0206015C
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_ClimaxDemoCall
ScrCmd_ClimaxDemoCall: ; 0x0203E684
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl MOD06_022456E8
	strh r0, [r6, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_InitSafariTrain
ScrCmd_InitSafariTrain: ; 0x0203E6B4
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02064E20
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_MoveSafariTrain
ScrCmd_MoveSafariTrain: ; 0x0203E6C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	mov r1, #0x0
	add r6, r0, #0x0
	mov r0, #0x41
	add r2, r1, #0x0
	bl FUN_0200433C
	add r5, #0x80
	ldrh r1, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r2, r6, #0x0
	bl MOD06_0224525C
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_CheckSafariTrain
ScrCmd_CheckSafariTrain: ; 0x0203E6FC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	bl MOD06_02245340
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_PlayerHeightValid
ScrCmd_PlayerHeightValid: ; 0x0203E72C
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_02055560
	mov r0, #0x1
	pop {r3, pc}

	thumb_func_start ScrCmd_UnderGroundTalkCount
ScrCmd_UnderGroundTalkCount: ; 0x0203E744
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F688
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetNewsPokeNo
ScrCmd_GetNewsPokeNo: ; 0x0203E774
	push {r3-r7, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_020244A4
	add r4, r0, #0x0
	bl rand_LC
	add r1, r4, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r6, r0, #0x10
	ldr r0, [sp, #0x0]
	mov r1, #0x19
	strh r1, [r0, #0x0]
	mov r4, #0x1
	mov r5, #0x0
_0203E7B6:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_020245F0
	cmp r0, #0x1
	bne _0203E7DC
	add r0, r4, #0x0
	bl FUN_02069B40
	cmp r0, #0x0
	beq _0203E7DC
	cmp r5, r6
	bne _0203E7D6
	ldr r0, [sp, #0x0]
	strh r4, [r0, #0x0]
	b _0203E7E8
_0203E7D6:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_0203E7DC:
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _0203E7EC ; =0x000001ED
	cmp r4, r0
	bls _0203E7B6
_0203E7E8:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0203E7EC: .word 0x000001ED

	thumb_func_start ScrCmd_NewsCountSet
ScrCmd_NewsCountSet: ; 0x0203E7F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r1, r4, #0x0
	bl FUN_0205F5A4
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_NewsCountChk
ScrCmd_NewsCountChk: ; 0x0203E81C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F594
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_StartGenerate
ScrCmd_StartGenerate: ; 0x0203E848
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202AA00
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_AddMovePoke
ScrCmd_AddMovePoke: ; 0x0203E858
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02060490
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_FldTradeAlloc
ScrCmd_FldTradeAlloc: ; 0x0203E870
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r4, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	ldrb r1, [r1, #0x0]
	mov r0, #0xb
	bl MOD06_0224884C
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_FldTradeMonsno
ScrCmd_FldTradeMonsno: ; 0x0203E894
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD06_022488EC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_FldTradeChgMonsno
ScrCmd_FldTradeChgMonsno: ; 0x0203E8C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl MOD06_022488F4
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_FldTradeEvent
ScrCmd_FldTradeEvent: ; 0x0203E8F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r5, #0x74]
	ldr r1, [r4, #0x0]
	mov r3, #0xb
	bl FUN_02060790
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_FldTradeDel
ScrCmd_FldTradeDel: ; 0x0203E928
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x14
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD06_022488CC
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_ZukanTextVerUp
ScrCmd_ZukanTextVerUp: ; 0x0203E940
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024D4C
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_ZukanSexVerUp
ScrCmd_ZukanSexVerUp: ; 0x0203E954
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024CE0
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_ZenkokuZukanFlag
ScrCmd_ZenkokuZukanFlag: ; 0x0203E968
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	mov r0, #0x0
	strh r0, [r6, #0x0]
	cmp r4, #0x1
	bne _0203E9AE
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024C84
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	bl FUN_02023A90
	b _0203E9C8
_0203E9AE:
	cmp r4, #0x2
	bne _0203E9C4
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	bl FUN_02024CA4
	strh r0, [r6, #0x0]
	b _0203E9C8
_0203E9C4:
	bl ErrorHandling
_0203E9C8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_ChkPrmExp
ScrCmd_ChkPrmExp: ; 0x0203E9CC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r5, r0, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl FUN_020671BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl FUN_020671BC
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r4, r6
	add r2, r7, r1
	ldr r1, [sp, #0x4]
	add r2, r1, r2
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_ChkWeek
ScrCmd_ChkWeek: ; 0x0203EA68
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r0, [sp, #0xc]
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_RegulationListCall
ScrCmd_RegulationListCall: ; 0x0203EA90
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r1, r0, #0x0
	ldr r0, [r4, #0x74]
	bl MOD06_022411F4
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_AshiatoChk
ScrCmd_AshiatoChk: ; 0x0203EAB0
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r5, #0x0
	bl MOD05_021F61E8
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl MOD05_021F61DC
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_PcRecoverAnm
ScrCmd_PcRecoverAnm: ; 0x0203EB20
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl MOD06_0224C27C
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_ElevatorAnm
ScrCmd_ElevatorAnm: ; 0x0203EB48
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	add r5, #0x80
	lsl r1, r4, #0x18
	lsl r2, r2, #0x18
	ldr r0, [r5, #0x0]
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	bl MOD06_0224C520
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_CallShipDemo
ScrCmd_CallShipDemo: ; 0x0203EB88
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r1, [r5, #0x8]
	add r2, r1, #0x1
	str r2, [r5, #0x8]
	ldrb r6, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	str r7, [sp, #0x0]
	add r5, #0x80
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_020607D4
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start ScrCmd_PMVersionGet
ScrCmd_PMVersionGet: ; 0x0203EBC8
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	mov r1, #0xa
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_AikotobaKabegamiSet
ScrCmd_AikotobaKabegamiSet: ; 0x0203EBE4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, #0x80
	ldr r6, [r0, #0x0]
	add r0, r6, #0x0
	bl FUN_020377AC
	bl FUN_020238F4
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_02022510
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	add r1, r7, #0x0
	bl MOD06_0224D14C
	add r5, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	beq _0203EC7E
	cmp r5, #0x7
	ble _0203EC88
_0203EC7E:
	mov r0, #0xff
	strh r0, [r4, #0x0]
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0203EC88:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0206B644
	cmp r0, #0x0
	beq _0203EC98
	mov r0, #0x0
	b _0203ECA2
_0203EC98:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0206B620
	add r0, r5, #0x1
_0203ECA2:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_GetUgHataNum
ScrCmd_GetUgHataNum: ; 0x0203ECAC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r4, [r1, #0xc]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02026CB4
	bl FUN_020269CC
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_SetUpPasoAnime
ScrCmd_SetUpPasoAnime: ; 0x0203ECD8
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_0224C678
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_StartPasoOnAnime
ScrCmd_StartPasoOnAnime: ; 0x0203ECF4
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_0224C6E8
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_StartPasoOffAnime
ScrCmd_StartPasoOffAnime: ; 0x0203ED10
	push {r3, lr}
	add r1, r0, #0x0
	add r1, #0x80
	ldr r2, [r0, #0x8]
	ldr r3, [r1, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	ldrb r1, [r2, #0x0]
	add r0, r3, #0x0
	bl MOD06_0224C6F4
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203ED2C
FUN_0203ED2C: ; 0x0203ED2C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024DA0
	add r6, r0, #0x0
	mov r0, #0x20
	bl FUN_020669C0
	add r4, r0, #0x0
	bl ZeroMonData
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x32
	mov r3, #0x20
	bl CreateMon
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202498C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeBoxCountEmptySpace
ScrCmd_PokeBoxCountEmptySpace: ; 0x0203ED70
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022510
	bl FUN_0206B3E4
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x87
	lsl r0, r0, #0x2
	sub r0, r0, r1
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ReportDrawProcSet
ScrCmd_ReportDrawProcSet: ; 0x0203EDA4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FUN_02039438
	add r4, r0, #0x0
	mov r0, #0x0
	add r5, #0x80
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	bl MOD05_021E7184
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ReportDrawProcDel
ScrCmd_ReportDrawProcDel: ; 0x0203EDC8
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x16
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl MOD05_021E71E8
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_DendouBallAnm
ScrCmd_DendouBallAnm: ; 0x0203EDE0
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r0, #0x0
	add r4, #0x80
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	lsr r1, r1, #0x18
	bl MOD06_0224E554
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_InitFldLift
ScrCmd_InitFldLift: ; 0x0203EE08
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0206486C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_MoveFldLift
ScrCmd_MoveFldLift: ; 0x0203EE18
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020649D4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_CheckFldLift
ScrCmd_CheckFldLift: ; 0x0203EE28
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020649B0
	cmp r0, #0x0
	beq _0203EE4E
	mov r0, #0x1
	b _0203EE50
_0203EE4E:
	mov r0, #0x0
_0203EE50:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SetupRAHCyl
ScrCmd_SetupRAHCyl: ; 0x0203EE58
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_0224E764
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_StartRAHCyl
ScrCmd_StartRAHCyl: ; 0x0203EE68
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl MOD06_0224E7C4
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_AddScore
ScrCmd_AddScore: ; 0x0203EE78
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	add r1, r4, #0x0
	bl FUN_0202A170
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PartyMonsNoCheck
ScrCmd_PartyMonsNoCheck: ; 0x0203EE98
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	add r1, r6, #0x0
	bl FUN_0206BAE4
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_PartyDeokisisuFormChange
ScrCmd_PartyDeokisisuFormChange: ; 0x0203EED8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, sp, #0x4
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	str r0, [sp, #0x0]
	bl FUN_0206B9AC
	add r4, #0x80
	add r6, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	mov r5, #0x0
	cmp r6, #0x0
	ble _0203EF4E
_0203EF18:
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_020671BC
	ldr r1, _0203EF54 ; =0x00000182
	cmp r0, r1
	bne _0203EF48
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, sp, #0x4
	bl FUN_02067830
	add r0, r4, #0x0
	bl FUN_02066ED8
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02024AF0
_0203EF48:
	add r5, r5, #0x1
	cmp r5, r6
	blt _0203EF18
_0203EF4E:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203EF54: .word 0x00000182

	thumb_func_start ScrCmd_CheckMinomuchiComp
ScrCmd_CheckMinomuchiComp: ; 0x0203EF58
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0206BB1C
	str r0, [sp, #0xc]
	bl FUN_0206B9AC
	add r2, sp, #0x18
	mov r4, #0x0
	ldr r3, _0203F008 ; =UNK_020F34FC
	str r0, [sp, #0x8]
	add r7, r2, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x8]
	str r4, [sp, #0x4]
	cmp r0, #0x0
	ble _0203EFFC
	mov r5, #0x1
	str r7, [sp, #0x14]
_0203EFA2:
	ldr r0, [sp, #0xc]
	add r1, r4, #0x0
	bl FUN_0206B9B0
	add r6, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r3, r0, #0x0
	mov r0, #0x67
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0x2
	cmp r1, r0
	bne _0203EFF2
	mov r2, #0x0
	add r1, r2, #0x0
	str r3, [r7, #0x0]
	cmp r4, #0x0
	ble _0203EFE8
	ldr r6, [sp, #0x14]
_0203EFD8:
	ldr r0, [r6, #0x0]
	cmp r3, r0
	bne _0203EFE0
	add r2, r5, #0x0
_0203EFE0:
	add r1, r1, #0x1
	add r6, r6, #0x4
	cmp r1, r4
	blt _0203EFD8
_0203EFE8:
	cmp r2, #0x0
	bne _0203EFF2
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0203EFF2:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r7, r7, #0x4
	cmp r4, r0
	blt _0203EFA2
_0203EFFC:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0203F008: .word UNK_020F34FC

	thumb_func_start ScrCmd_PoketchHookSet
ScrCmd_PoketchHookSet: ; 0x0203F00C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F1C4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_PoketchHookReset
ScrCmd_PoketchHookReset: ; 0x0203F020
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F1D4
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_SlotMachine
ScrCmd_SlotMachine: ; 0x0203F034
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_020389CC
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start ScrCmd_GetNowHour
ScrCmd_GetNowHour: ; 0x0203F058
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204B2D8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_ObjShakeAnm
ScrCmd_ObjShakeAnm: ; 0x0203F07C
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r7, r0, #0x0
	bne _0203F0FA
	bl ErrorHandling
_0203F0FA:
	str r6, [sp, #0x0]
	str r4, [sp, #0x4]
	ldr r0, [r5, #0x74]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x8]
	add r1, r7, #0x0
	bl FUN_02054F50
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_ObjBlinkAnm
ScrCmd_ObjBlinkAnm: ; 0x0203F110
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203F164
	bl ErrorHandling
_0203F164:
	ldr r0, [r4, #0x74]
	add r1, r5, #0x0
	add r2, r7, #0x0
	add r3, r6, #0x0
	bl FUN_0205502C
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_D20R0106Legend_IsUnseal
ScrCmd_D20R0106Legend_IsUnseal: ; 0x0203F174
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02054E30
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_DressingImcAcceCheck
ScrCmd_DressingImcAcceCheck: ; 0x0203F19C
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	mov r6, #0x0
	add r7, r0, #0x0
	add r4, r6, #0x0
	add r5, sp, #0x4
_0203F1CA:
	add r1, r4, #0x0
	add r0, r7, #0x0
	add r1, #0x22
	mov r2, #0x1
	bl FUN_020270D8
	cmp r0, #0x1
	bne _0203F1E0
	mov r0, #0x1
	strh r0, [r5, #0x0]
	add r6, r6, #0x1
_0203F1E0:
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x10
	blt _0203F1CA
	cmp r6, #0x0
	bne _0203F1F8
	ldr r0, [sp, #0x0]
	ldr r1, _0203F230 ; =0x0000FFFF
	add sp, #0x24
	strh r1, [r0, #0x0]
	mov r0, #0x0
	pop {r4-r7, pc}
_0203F1F8:
	bl rand_LC
	add r1, r6, #0x0
	bl _s32_div_f
	mov r4, #0x0
	add r2, sp, #0x4
_0203F206:
	ldrh r0, [r2, #0x0]
	cmp r0, #0x1
	bne _0203F212
	cmp r1, #0x0
	beq _0203F21A
	sub r1, r1, #0x1
_0203F212:
	add r4, r4, #0x1
	add r2, r2, #0x2
	cmp r4, #0x10
	blt _0203F206
_0203F21A:
	cmp r4, #0x10
	blt _0203F222
	bl ErrorHandling
_0203F222:
	ldr r0, [sp, #0x0]
	add r4, #0x22
	strh r4, [r0, #0x0]
	mov r0, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0203F230: .word 0x0000FFFF

	thumb_func_start ScrCmd_AgbCartridgeVerGet
ScrCmd_AgbCartridgeVerGet: ; 0x0203F234
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	ldr r1, _0203F250 ; =gUnk021C4918
	ldrb r1, [r1, #0x6]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0203F250: .word gUnk021C4918

	thumb_func_start ScrCmd_UnderGroundTalkCountClear
ScrCmd_UnderGroundTalkCountClear: ; 0x0203F254
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	mov r1, #0x0
	bl FUN_0205F698
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_HideMapStateChange
ScrCmd_HideMapStateChange: ; 0x0203F26C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r1, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	cmp r4, #0x0
	beq _0203F2A0
	add r1, r6, #0x0
	bl FUN_0205F4E4
	b _0203F2A6
_0203F2A0:
	add r1, r6, #0x0
	bl FUN_0205F50C
_0203F2A6:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_ImcBgNameSet
ScrCmd_ImcBgNameSet: ; 0x0203F2AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	ldr r1, [r5, #0x8]
	add r6, r0, #0x0
	add r0, r1, #0x1
	str r0, [r5, #0x8]
	add r0, r5, #0x0
	ldrb r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r4, #0x0
	bl FUN_0200B6D0
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_SlotRentyanChk
ScrCmd_SlotRentyanChk: ; 0x0203F2E4
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205F6C8
	cmp r0, #0xa
	blo _0203F314
	mov r0, #0x1
	b _0203F316
_0203F314:
	mov r0, #0x0
_0203F316:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_LevelJijiiNo
ScrCmd_LevelJijiiNo: ; 0x0203F31C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	bl FUN_0205F648
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ImcAcceSubItem
ScrCmd_ImcAcceSubItem: ; 0x0203F348
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0202708C
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02027210
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_c08r0801ScopeCameraSet
ScrCmd_c08r0801ScopeCameraSet: ; 0x0203F38C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02046030
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_LevelJijiiInit
ScrCmd_LevelJijiiInit: ; 0x0203F39C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0205F668
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start ScrCmd_NewNankaiWordSet
ScrCmd_NewNankaiWordSet: ; 0x0203F3AC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02013B5C
	bl FUN_02013B74
	cmp r0, #0x20
	bne _0203F3FE
	ldr r0, _0203F414 ; =0x0000FFFF
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_0203F3FE:
	strh r0, [r4, #0x0]
	bl FUN_02013BE4
	add r2, r0, #0x0
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	bl FUN_0200B518
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F414: .word 0x0000FFFF

	thumb_func_start ScrCmd_NankaiWordCompleteCheck
ScrCmd_NankaiWordCompleteCheck: ; 0x0203F418
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02013B5C
	bl FUN_02013BC8
	cmp r0, #0x1
	bne _0203F444
	mov r0, #0x1
	b _0203F446
_0203F444:
	mov r0, #0x0
_0203F446:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_RegularCheck
ScrCmd_RegularCheck: ; 0x0203F44C
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0205F710
	cmp r0, #0x5
	blo _0203F47C
	mov r0, #0x1
	b _0203F47E
_0203F47C:
	mov r0, #0x0
_0203F47E:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_BirthDayCheck
ScrCmd_BirthDayCheck: ; 0x0203F484
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	ldr r5, [r5, #0x0]
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02023788
	add r7, r0, #0x0
	bl FUN_02023818
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204B2B4
	cmp r6, r0
	bne _0203F4CE
	add r0, r7, #0x0
	bl FUN_0202381C
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204B2C0
	cmp r6, r0
	bne _0203F4CE
	mov r0, #0x1
	strh r0, [r4, #0x0]
	b _0203F4D2
_0203F4CE:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0203F4D2:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_AnoonSeeNum
ScrCmd_AnoonSeeNum: ; 0x0203F4D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202471C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_D17SystemMapSelect
ScrCmd_D17SystemMapSelect: ; 0x0203F508
	push {r3-r7, lr}
	add r6, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r1, r6, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x1c]
	ldr r1, [r2, #0x8]
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	ldr r1, [r2, #0xc]
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r7, #0x3
	blo _0203F54C
	ldr r7, _0203F5C8 ; =0x0000010E
	b _0203F582
_0203F54C:
	cmp r0, #0x1e
	blo _0203F556
	mov r7, #0x43
	lsl r7, r7, #0x2
	b _0203F582
_0203F556:
	bl rand_LC
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x19
	bge _0203F568
	ldr r7, _0203F5CC ; =0x0000010D
	b _0203F582
_0203F568:
	bl rand_LC
	mov r1, #0x6
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x6
	mul r0, r7
	add r0, r1, r0
	lsl r1, r0, #0x1
	ldr r0, _0203F5D0 ; =UNK_020F3538
	ldrh r7, [r0, r1]
_0203F582:
	cmp r5, #0xb
	bne _0203F59A
	cmp r4, #0x1
	bne _0203F58E
	mov r4, #0x0
	b _0203F5A4
_0203F58E:
	cmp r4, #0x14
	bne _0203F596
	mov r4, #0x2
	b _0203F5A4
_0203F596:
	mov r4, #0x5
	b _0203F5A4
_0203F59A:
	cmp r5, #0x14
	bne _0203F5A2
	mov r4, #0x1
	b _0203F5A4
_0203F5A2:
	mov r4, #0x3
_0203F5A4:
	mov r5, #0x0
_0203F5A6:
	cmp r5, r4
	beq _0203F5B8
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl FUN_02034C24
_0203F5B8:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x4
	blo _0203F5A6
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0203F5C8: .word 0x0000010E
_0203F5CC: .word 0x0000010D
_0203F5D0: .word UNK_020F3538

	thumb_func_start ScrCmd_UnderGroundToolGiveCount
ScrCmd_UnderGroundToolGiveCount: ; 0x0203F5D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F720
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnderGroundKasekiDigCount
ScrCmd_UnderGroundKasekiDigCount: ; 0x0203F604
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F740
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnderGroundTrapHitCount
ScrCmd_UnderGroundTrapHitCount: ; 0x0203F634
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F760
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PofinAdd
ScrCmd_PofinAdd: ; 0x0203F664
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, sp, #0x0
	add r0, #0x8
_0203F684:
	ldr r6, [r0, #0x0]
	ldr r1, [r5, #0x8]
	add r6, r6, #0x1
	str r6, [r0, #0x0]
	ldrb r1, [r1, #0x0]
	add r2, r2, #0x1
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	cmp r2, #0x5
	blt _0203F684
	ldr r1, [r0, #0x0]
	ldr r2, [r5, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ldrb r6, [r2, #0x0]
	mov r0, #0x4
	bl FUN_02027E5C
	add r1, sp, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	add r7, r0, #0x0
	bl FUN_02027F04
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	add r1, r7, #0x0
	bl FUN_02028094
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FreeToHeap
	ldr r0, _0203F6E0 ; =0x0000FFFF
	cmp r5, r0
	bne _0203F6D8
	strh r0, [r4, #0x0]
	b _0203F6DA
_0203F6D8:
	strh r6, [r4, #0x0]
_0203F6DA:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0203F6E0: .word 0x0000FFFF

	thumb_func_start ScrCmd_PofinAddCheck
ScrCmd_PofinAddCheck: ; 0x0203F6E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02028048
	bl FUN_02028074
	ldr r1, _0203F71C ; =0x0000FFFF
	cmp r0, r1
	bne _0203F712
	mov r0, #0x0
	b _0203F714
_0203F712:
	mov r0, #0x1
_0203F714:
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203F71C: .word 0x0000FFFF

	thumb_func_start ScrCmd_IsHaihuEventEnable
ScrCmd_IsHaihuEventEnable: ; 0x0203F720
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r5, r0, #0x0
	cmp r4, #0x3
	bls _0203F752
	bl ErrorHandling
_0203F752:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0205F4A0
	strh r0, [r6, #0x0]
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_DendouNumGet
ScrCmd_DendouNumGet: ; 0x0203F760
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	add r2, sp, #0x0
	bl FUN_02022534
	ldr r1, [sp, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	bne _0203F798
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F798:
	cmp r1, #0x1
	bne _0203F7AE
	mov r1, #0x0
	bl FUN_0202B21C
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7AE:
	cmp r1, #0x2
	bne _0203F7BE
	mov r1, #0x0
	strh r1, [r5, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	pop {r3-r5, pc}
_0203F7BE:
	mov r0, #0x0
	strh r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_SodateyaPokeListSetProc
ScrCmd_SodateyaPokeListSetProc: ; 0x0203F7C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r1, r5, #0x0
	add r1, #0x80
	add r4, r0, #0x0
	ldr r1, [r1, #0x0]
	mov r0, #0x20
	add r2, r6, #0x0
	bl FUN_02037A48
	str r0, [r4, #0x0]
	ldr r1, _0203F808 ; =FUN_0203BC04
	add r0, r5, #0x0
	bl SetupNativeScript
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0203F808: .word FUN_0203BC04 

	thumb_func_start ScrCmd_SodateyaPokeListGetResult
ScrCmd_SodateyaPokeListGetResult: ; 0x0203F80C
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r4, #0x80
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	mov r1, #0x13
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0203F84C
	bl ErrorHandling
_0203F84C:
	ldr r0, [r4, #0x0]
	bl FUN_02037A40
	strh r0, [r6, #0x0]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x7
	bne _0203F85E
	mov r0, #0xff
	strh r0, [r6, #0x0]
_0203F85E:
	ldr r0, [r4, #0x0]
	bl FUN_02037A70
	strh r0, [r5, #0x0]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0203F870
	mov r0, #0x1
	b _0203F872
_0203F870:
	mov r0, #0x0
_0203F872:
	strh r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4-r6, pc}

	thumb_func_start ScrCmd_GetRandomHit
ScrCmd_GetRandomHit: ; 0x0203F880
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0x8]
	add r1, r2, #0x1
	str r1, [r5, #0x8]
	ldrb r4, [r2, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	cmp r4, #0x64
	bls _0203F8A2
	mov r4, #0x64
_0203F8A2:
	bl rand_LC
	mov r1, #0x65
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	cmp r0, r4
	bgt _0203F8B8
	mov r0, #0x1
	b _0203F8BA
_0203F8B8:
	mov r0, #0x0
_0203F8BA:
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_HidenEffStart
ScrCmd_HidenEffStart: ; 0x0203F8C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r4, #0x0
	beq _0203F8FC
	cmp r4, #0x1
	beq _0203F906
	cmp r4, #0x2
	beq _0203F910
	b _0203F91A
_0203F8FC:
	mov r2, #0x0
	mov r3, #0x20
	bl MOD06_0224F12C
	b _0203F91E
_0203F906:
	mov r2, #0x1
	mov r3, #0x20
	bl MOD06_0224F12C
	b _0203F91E
_0203F910:
	mov r2, #0x2
	mov r3, #0x20
	bl MOD06_0224F12C
	b _0203F91E
_0203F91A:
	bl ErrorHandling
_0203F91E:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UnderGroundTalkCount2
ScrCmd_UnderGroundTalkCount2: ; 0x0203F924
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0205F6A8
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_Zishin
ScrCmd_Zishin: ; 0x0203F954
	push {r4, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	cmp r0, #0x0
	bne _0203F978
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl MOD06_02239944
	b _0203F982
_0203F978:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl MOD06_02239AAC
_0203F982:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start ScrCmd_CheckMyGSID
ScrCmd_CheckMyGSID: ; 0x0203F988
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0203384C
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_GetFriendDataNum
ScrCmd_GetFriendDataNum: ; 0x0203F9B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020286EC
	bl FUN_02028448
	strh r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_UgBallCheck
ScrCmd_UgBallCheck: ; 0x0203F9DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	ldr r1, _0203FA10 ; =0x0000FF79
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #0x1
	bhi _0203FA0C
	bl FUN_02025C30
_0203FA0C:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0203FA10: .word 0x0000FF79

	thumb_func_start ScrCmd_AusuItemCheck
ScrCmd_AusuItemCheck: ; 0x0203FA14
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r1, _0203FA54 ; =0x0000012A
	cmp r4, r1
	blo _0203FA4E
	add r1, #0xf
	cmp r4, r1
	bhi _0203FA4E
	mov r1, #0x1
	strh r1, [r0, #0x0]
_0203FA4E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0203FA54: .word 0x0000012A

	thumb_func_start ScrCmd_AikotobaOkurimonoChk
ScrCmd_AikotobaOkurimonoChk: ; 0x0203FA58
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	mov r0, #0x20
	bl FUN_0200AA80
	add r4, r0, #0x0
	ldr r2, _0203FB48 ; =0x00000147
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0x20
	bl FUN_0200A86C
	add r5, r0, #0x0
	ldr r2, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0200B518
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200B518
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	add r0, r4, #0x0
	mov r1, #0x3
	add r2, r7, #0x0
	bl FUN_0200B518
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0200A9C4
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0200A914
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _0203FB24
	mov r0, #0x1
	b _0203FB26
_0203FB24:
	mov r0, #0x0
_0203FB26:
	strh r0, [r6, #0x0]
	add r0, r7, #0x0
	bl FUN_02021A20
	ldr r0, [sp, #0x0]
	bl FUN_02021A20
	add r0, r5, #0x0
	bl FUN_0200A8B8
	add r0, r4, #0x0
	bl FUN_0200AB18
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0203FB48: .word 0x00000147

	thumb_func_start ScrCmd_WifiHusiginaokurimonoOpenFlagSet
ScrCmd_WifiHusiginaokurimonoOpenFlagSet: ; 0x0203FB4C
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02023788
	mov r1, #0x1
	bl FUN_02023828
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_UnionGetCardTalkNo
ScrCmd_UnionGetCardTalkNo: ; 0x0203FB64
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_02039438
	ldr r0, [r0, #0x0]
	bl FUN_0205296C
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_WirelessIconEasy
ScrCmd_WirelessIconEasy: ; 0x0203FB94
	push {r3, lr}
	bl FUN_02033E74
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_WirelessIconEasyEnd
ScrCmd_WirelessIconEasyEnd: ; 0x0203FBA0
	push {r3, lr}
	bl FUN_02033ED0
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_SaveFieldObj
ScrCmd_SaveFieldObj: ; 0x0203FBAC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_02034E48
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start ScrCmd_SetEscapeLocation
ScrCmd_SetEscapeLocation: ; 0x0203FBBC
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, #0x80
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02034E30
	bl FUN_02034DCC
	str r4, [r0, #0x0]
	str r6, [r0, #0x8]
	mov r1, #0x0
	str r7, [r0, #0xc]
	mvn r1, r1
	str r1, [r0, #0x4]
	mov r1, #0x1
	str r1, [r0, #0x10]
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start ScrCmd_FieldObjBitSetFellowHit
ScrCmd_FieldObjBitSetFellowHit: ; 0x0203FC1C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	ldr r2, [r5, #0x8]
	add r1, r0, #0x0
	add r0, r2, #0x1
	str r0, [r5, #0x8]
	add r5, #0x80
	ldr r0, [r5, #0x0]
	ldrb r4, [r2, #0x0]
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	add r5, r0, #0x0
	bne _0203FC4C
	bl ErrorHandling
_0203FC4C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020588B8
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start ScrCmd_GetCardRank
ScrCmd_GetCardRank: ; 0x0203FC58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r1, r5, #0x0
	add r1, #0x80
	ldr r4, [r1, #0x0]
	bl ScriptReadHalfword
	add r5, #0x80
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02065078
	strh r0, [r5, #0x0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ReportInfoWinOpen
ScrCmd_ReportInfoWinOpen: ; 0x0203FC80
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	bne _0203FCAA
	add r0, r5, #0x0
	mov r1, #0x4
	mov r2, #0x3
	bl MOD05_021E8588
	str r0, [r4, #0x0]
	bl MOD05_021E84F4
_0203FCAA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_ReportInfoWinClose
ScrCmd_ReportInfoWinClose: ; 0x0203FCB0
	push {r3-r5, lr}
	add r0, #0x80
	ldr r5, [r0, #0x0]
	mov r1, #0x28
	add r0, r5, #0x0
	bl FUN_02039438
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	bne _0203FCD6
	ldr r0, [r4, #0x0]
	bl MOD05_021E856C
	ldr r0, [r4, #0x0]
	bl MOD05_021E85E4
_0203FCD6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_FieldScopeModeSet
ScrCmd_FieldScopeModeSet: ; 0x0203FCDC
	push {r3, lr}
	ldr r2, [r0, #0x8]
	add r1, r2, #0x1
	str r1, [r0, #0x8]
	add r0, #0x80
	ldrb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_0206367C
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
