	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD84_021D74E0
MOD84_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r5, r1, #0
	ldr r1, [r5]
	add r6, r0, #0
	cmp r1, #0
	beq _021D74FC
	cmp r1, #1
	bne _021D74F4
	b _021D7620
_021D74F4:
	cmp r1, #2
	bne _021D74FA
	b _021D765A
_021D74FA:
	b _021D7668
_021D74FC:
	mov r0, #3
	mov r1, #0x4b
	lsl r2, r0, #0x10
	bl FUN_0201681C
	ldr r1, _021D7670 ; =0x00001244
	add r0, r6, #0
	mov r2, #0x4b
	bl OverlayManager_CreateAndGetData
	add r4, r0, #0
	bne _021D7516
	b _021D7618
_021D7516:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl GX_DisableEngineALayers
	bl GX_DisableEngineBLayers
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7674 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D7678 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	add r0, r6, #0
	bl OverlayManager_GetField18
	str r0, [r4, #0x18]
	mov r0, #0
	str r0, [r4, #0x1c]
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x4b
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	add r1, r4, #0
	mov r0, #0x80
	add r1, #0xe0
	mov r2, #0x4b
	bl FUN_02008C9C
	add r1, r4, #0
	add r1, #0xdc
	str r0, [r1]
	add r0, r4, #0
	mov r2, #0xd
	add r0, #0xe0
	mov r1, #0
	lsl r2, r2, #0x10
	bl FUN_02008D04
	add r0, r4, #0
	mov r1, #0
	add r0, #0xe0
	add r2, r1, #0
	bl FUN_02008D24
	add r0, r4, #0
	str r6, [r4]
	bl MOD84_021D7968
	add r0, r4, #0
	bl MOD84_021D7AA0
	add r0, r4, #0
	bl MOD84_021D7F94
	add r0, r4, #0
	bl MOD84_021D82B8
	ldr r2, _021D767C ; =0x000001ED
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x4b
	bl NewMsgDataFromNarc
	str r0, [r4, #0x14]
	str r0, [sp]
	mov r1, #0xef
	ldr r0, [r4, #4]
	mvn r1, r1
	mov r2, #1
	mov r3, #0
	bl MOD84_021D84F8
	str r0, [r4, #8]
	ldr r0, [r4, #0x14]
	ldr r1, _021D7680 ; =0xFFFFFE40
	str r0, [sp]
	ldr r0, [r4, #4]
	mov r2, #5
	mov r3, #0
	bl MOD84_021D84F8
	str r0, [r4, #0xc]
	mov r1, #0
	ldr r2, _021D7684 ; =0x021DA6C8
	ldr r0, _021D7688 ; =0x00001224
	str r1, [r4, #0x10]
	str r1, [r4, r0]
	add r0, r0, #4
	str r1, [r4, r0]
	ldr r1, [r4, #4]
	ldr r2, [r2, #0x2c]
	add r0, r4, #0
	blx r2
	ldr r1, _021D768C ; =0x0000122C
	mov r2, #1
	str r0, [r4, r1]
	ldr r1, _021D7690 ; =0x000004A2
	mov r0, #0xe
	bl FUN_0200433C
	ldr r0, _021D7694 ; =MOD84_021D7958
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA60
	ldr r1, _021D7698 ; =0x00001230
	str r0, [r4, r1]
	ldr r0, _021D769C ; =MOD84_021D7950
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
_021D7618:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7668
_021D7620:
	bl OverlayManager_GetData
	ldr r2, _021D7684 ; =0x021DA6C8
	ldr r1, _021D768C ; =0x0000122C
	add r4, r0, #0
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r2, [r2, #0x30]
	add r1, r4, r1
	blx r2
	cmp r0, #0
	beq _021D7668
	ldr r1, _021D76A0 ; =0x00001228
	mov r0, #0
	str r0, [r4, r1]
	mov r1, #0x20
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r2, #0x4b
	str r2, [sp, #8]
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7668
_021D765A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7668
	add sp, #0x14
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7668:
	mov r0, #0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021D7670: .word 0x00001244
_021D7674: .word 0xFFFFE0FF
_021D7678: .word 0x04001000
_021D767C: .word 0x000001ED
_021D7680: .word 0xFFFFFE40
_021D7684: .word MOD84_021DA6C8
_021D7688: .word 0x00001224
_021D768C: .word 0x0000122C
_021D7690: .word 0x000004A2
_021D7694: .word MOD84_021D7958
_021D7698: .word 0x00001230
_021D769C: .word MOD84_021D7950
_021D76A0: .word 0x00001228
	thumb_func_end MOD84_021D74E0

	thumb_func_start MOD84_021D76A4
MOD84_021D76A4: ; 0x021D76A4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	bl OverlayManager_GetData
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021D773E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D76C2: ; jump table
	.short _021D76CA - _021D76C2 - 2 ; case 0
	.short _021D76EE - _021D76C2 - 2 ; case 1
	.short _021D771A - _021D76C2 - 2 ; case 2
	.short _021D772E - _021D76C2 - 2 ; case 3
_021D76CA:
	bl OS_DisableInterrupts
	add r6, r0, #0
	ldr r0, _021D7744 ; =0x00001230
	ldr r0, [r5, r0]
	bl FUN_0200CAB4
	add r0, r6, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D773E
_021D76EE:
	ldr r0, [r5, #0xc]
	bl MOD84_021D85B8
	ldr r0, [r5, #8]
	bl MOD84_021D85B8
	ldr r0, [r5, #0x14]
	bl DestroyMsgData
	add r0, r5, #0
	bl MOD84_021D8000
	add r0, r5, #0
	bl MOD84_021D7AB8
	add r0, r5, #0
	bl MOD84_021D7A84
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D773E
_021D771A:
	add r5, #0xdc
	ldr r0, [r5]
	bl FUN_0201FD58
	bl FUN_02009FA0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D773E
_021D772E:
	add r0, r6, #0
	bl OverlayManager_FreeData
	mov r0, #0x4b
	bl FUN_020168D0
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D773E:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_021D7744: .word 0x00001230
	thumb_func_end MOD84_021D76A4

	thumb_func_start MOD84_021D7748
MOD84_021D7748: ; 0x021D7748
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r1, #1
	bl MOD84_021D85EC
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl MOD84_021D85EC
	str r0, [r4, #0x10]
	ldr r0, [r5]
	cmp r0, #0xa
	bhi _021D7804
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7778: ; jump table
	.short _021D778E - _021D7778 - 2 ; case 0
	.short _021D77EC - _021D7778 - 2 ; case 1
	.short _021D7826 - _021D7778 - 2 ; case 2
	.short _021D7846 - _021D7778 - 2 ; case 3
	.short _021D7868 - _021D7778 - 2 ; case 4
	.short _021D7874 - _021D7778 - 2 ; case 5
	.short _021D789C - _021D7778 - 2 ; case 6
	.short _021D78AA - _021D7778 - 2 ; case 7
	.short _021D78BE - _021D7778 - 2 ; case 8
	.short _021D7920 - _021D7778 - 2 ; case 9
	.short _021D7914 - _021D7778 - 2 ; case 10
_021D778E:
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	bne _021D77C8
	ldr r0, _021D7928 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #8
	tst r0, r1
	beq _021D77C8
	ldr r0, [r4, #0x18]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021D77C8
	mov r0, #0x10
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4b
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r4, #0x1c]
	mov r0, #7
	str r0, [r5]
	b _021D7920
_021D77C8:
	ldr r2, _021D792C ; =0x0000122C
	sub r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, #8
	ldr r2, [r4, r2]
	add r1, r4, r1
	lsl r3, r2, #4
	ldr r2, _021D7930 ; =0x021DA6FC
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _021D7804
	ldr r0, _021D7934 ; =0x00001228
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #1
	str r0, [r5]
	b _021D7920
_021D77EC:
	ldr r2, _021D792C ; =0x0000122C
	sub r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, #8
	ldr r2, [r4, r2]
	add r1, r4, r1
	lsl r3, r2, #4
	ldr r2, _021D7938 ; =0x021DA700
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	bne _021D7806
_021D7804:
	b _021D7920
_021D7806:
	ldr r0, _021D793C ; =0x00001224
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #7
	bhs _021D7820
	mov r1, #0
	add r0, r0, #4
	str r1, [r4, r0]
	mov r0, #2
	str r0, [r5]
	b _021D7920
_021D7820:
	mov r0, #4
	str r0, [r5]
	b _021D7920
_021D7826:
	ldr r2, _021D793C ; =0x00001224
	ldr r1, [r4, #4]
	ldr r2, [r4, r2]
	add r0, r4, #0
	lsl r3, r2, #4
	ldr r2, _021D7940 ; =0x021DA6F4
	ldr r2, [r2, r3]
	blx r2
	ldr r1, _021D792C ; =0x0000122C
	mov r2, #0
	str r0, [r4, r1]
	sub r0, r1, #4
	str r2, [r4, r0]
	mov r0, #3
	str r0, [r5]
	b _021D7920
_021D7846:
	ldr r2, _021D792C ; =0x0000122C
	sub r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, #8
	ldr r2, [r4, r2]
	add r1, r4, r1
	lsl r3, r2, #4
	ldr r2, _021D7944 ; =0x021DA6F8
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _021D7920
	ldr r0, _021D7934 ; =0x00001228
	mov r1, #0
	str r1, [r4, r0]
	str r1, [r5]
	b _021D7920
_021D7868:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021D7920
	mov r0, #5
	str r0, [r5]
	b _021D7920
_021D7874:
	ldr r0, _021D7928 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #9
	tst r0, r1
	beq _021D7920
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x4b
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #6
	str r0, [r5]
	b _021D7920
_021D789C:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7920
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, pc}
_021D78AA:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7920
	ldr r0, _021D7934 ; =0x00001228
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #8
	str r0, [r5]
	b _021D7920
_021D78BE:
	ldr r2, _021D792C ; =0x0000122C
	sub r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, #8
	ldr r2, [r4, r2]
	add r1, r4, r1
	lsl r3, r2, #4
	ldr r2, _021D7938 ; =0x021DA700
	ldr r2, [r2, r3]
	blx r2
	cmp r0, #0
	beq _021D7920
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl MOD84_021D87B0
	ldr r0, [r4, #8]
	bl MOD84_021D881C
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D7948 ; =0xFFFF1FFF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D794C ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #0x20
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x4b
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0xa
	str r0, [r5]
	b _021D7920
_021D7914:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7920
	mov r0, #5
	str r0, [r5]
_021D7920:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D7928: .word gMain
_021D792C: .word 0x0000122C
_021D7930: .word MOD84_021DA6FC
_021D7934: .word 0x00001228
_021D7938: .word MOD84_021DA700
_021D793C: .word 0x00001224
_021D7940: .word MOD84_021DA6F4
_021D7944: .word MOD84_021DA6F8
_021D7948: .word 0xFFFF1FFF
_021D794C: .word 0x04001000
	thumb_func_end MOD84_021D7748

	thumb_func_start MOD84_021D7950
MOD84_021D7950: ; 0x021D7950
	ldr r3, _021D7954 ; =MOD84_021D7CFC
	bx r3
	.align 2, 0
_021D7954: .word MOD84_021D7CFC
	thumb_func_end MOD84_021D7950

	thumb_func_start MOD84_021D7958
MOD84_021D7958: ; 0x021D7958
	push {r3, lr}
	add r1, #0xdc
	ldr r0, [r1]
	bl FUN_0201FDEC
	bl FUN_02009F80
	pop {r3, pc}
	thumb_func_end MOD84_021D7958

	thumb_func_start MOD84_021D7968
MOD84_021D7968: ; 0x021D7968
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0x4b
	bl FUN_02016B94
	str r0, [r4, #4]
	ldr r0, _021D7A60 ; =0x021DA68C
	bl FUN_0201E66C
	ldr r2, _021D7A64 ; =0x04000304
	ldr r0, _021D7A68 ; =0xFFFF7FFF
	ldrh r1, [r2]
	and r0, r1
	strh r0, [r2]
	mov r0, #1
	mov r1, #0
	add r2, r0, #0
	bl GX_SetGraphicsMode
	ldr r0, _021D7A6C ; =0x021DA650
	bl FUN_02016BBC
	ldr r0, [r4, #4]
	ldr r2, _021D7A70 ; =0x021DA670
	mov r1, #1
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021D7A70 ; =0x021DA670
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r2, #0
	str r2, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x4b
	str r0, [sp, #8]
	mov r0, #0x7f
	mov r1, #0x42
	add r3, r2, #0
	bl FUN_02006948
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x4b
	str r0, [sp, #8]
	mov r0, #0x7f
	mov r1, #0x42
	mov r2, #4
	bl FUN_02006948
	ldr r2, _021D7A74 ; =0x04000050
	mov r0, #0
	add r3, r2, #0
	add r7, r2, #0
	ldr r1, _021D7A78 ; =0x04001050
	strh r0, [r2]
	strh r0, [r1]
	mov r0, #0xff
	sub r3, #0x10
	strh r0, [r3]
	add r3, r2, #0
	ldr r4, _021D7A7C ; =0x00005EC0
	sub r3, #0xc
	strh r4, [r3]
	sub r7, #8
	ldrh r4, [r7]
	mov r5, #0x3f
	mov r3, #0x1d
	bic r4, r5
	add r6, r4, #0
	orr r6, r3
	mov r4, #0x20
	orr r6, r4
	strh r6, [r7]
	sub r7, r2, #6
	ldrh r6, [r7]
	mov r2, #0x1f
	bic r6, r5
	orr r6, r2
	orr r6, r4
	strh r6, [r7]
	add r6, r1, #0
	sub r6, #0x10
	strh r0, [r6]
	add r0, r1, #0
	mov r6, #0x18
	sub r0, #0xc
	strh r6, [r0]
	add r6, r1, #0
	sub r6, #8
	ldrh r0, [r6]
	bic r0, r5
	orr r0, r3
	orr r0, r4
	sub r3, r1, #6
	strh r0, [r6]
	ldrh r0, [r3]
	sub r1, #0x50
	bic r0, r5
	orr r0, r2
	orr r0, r4
	strh r0, [r3]
	lsl r3, r4, #0x15
	ldr r0, [r3]
	ldr r2, _021D7A80 ; =0xFFFF1FFF
	add r5, r0, #0
	and r5, r2
	lsl r0, r4, #8
	orr r0, r5
	str r0, [r3]
	ldr r0, [r1]
	and r2, r0
	lsl r0, r4, #8
	orr r0, r2
	str r0, [r1]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D7A60: .word MOD84_021DA68C
_021D7A64: .word 0x04000304
_021D7A68: .word 0xFFFF7FFF
_021D7A6C: .word MOD84_021DA650
_021D7A70: .word MOD84_021DA670
_021D7A74: .word 0x04000050
_021D7A78: .word 0x04001050
_021D7A7C: .word 0x00005EC0
_021D7A80: .word 0xFFFF1FFF
	thumb_func_end MOD84_021D7968

	thumb_func_start MOD84_021D7A84
MOD84_021D7A84: ; 0x021D7A84
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4, #4]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD84_021D7A84

	thumb_func_start MOD84_021D7AA0
MOD84_021D7AA0: ; 0x021D7AA0
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D7AC8
	add r0, r4, #0
	bl MOD84_021D7B54
	add r0, r4, #0
	bl MOD84_021D7BC8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D7AA0

	thumb_func_start MOD84_021D7AB8
MOD84_021D7AB8: ; 0x021D7AB8
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D7CD4
	add r0, r4, #0
	bl MOD84_021D7BBC
	pop {r4, pc}
	thumb_func_end MOD84_021D7AB8

	thumb_func_start MOD84_021D7AC8
MOD84_021D7AC8: ; 0x021D7AC8
	push {r3, lr}
	bl FUN_020BB7F4
	bl G3X_InitMtxStack
	ldr r0, _021D7B3C ; =0x04000060
	ldr r2, _021D7B40 ; =0xFFFFCFFD
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	add r1, r2, #2
	ldrh r3, [r0]
	lsr r2, r2, #0x11
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r3, [r0]
	ldr r1, _021D7B44 ; =0x0000CFFB
	and r3, r1
	strh r3, [r0]
	ldrh r3, [r0]
	sub r1, r1, #4
	and r1, r3
	strh r1, [r0]
	mov r0, #0
	add r1, r0, #0
	mov r3, #0x3f
	str r0, [sp]
	bl G3X_SetClearColor
	ldr r1, _021D7B48 ; =0x04000540
	mov r0, #2
	str r0, [r1]
	ldr r0, _021D7B4C ; =0xBFFF0000
	str r0, [r1, #0x40]
	mov r0, #1
	add r1, r0, #0
	bl FUN_020AEB70
	mov r0, #1
	lsl r0, r0, #0xe
	mov r1, #1
	bl FUN_020AEDF4
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	ldr r1, _021D7B50 ; =0x04000008
	mov r0, #3
	ldrh r2, [r1]
	bic r2, r0
	mov r0, #1
	orr r0, r2
	strh r0, [r1]
	pop {r3, pc}
	nop
_021D7B3C: .word 0x04000060
_021D7B40: .word 0xFFFFCFFD
_021D7B44: .word 0x0000CFFB
_021D7B48: .word 0x04000540
_021D7B4C: .word 0xBFFF0000
_021D7B50: .word 0x04000008
	thumb_func_end MOD84_021D7AC8

	thumb_func_start MOD84_021D7B54
MOD84_021D7B54: ; 0x021D7B54
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x4b
	bl FUN_0201EB64
	str r0, [r4, #0x20]
	mov r0, #0
	str r0, [r4, #0x24]
	str r0, [r4, #0x28]
	str r0, [r4, #0x2c]
	strh r0, [r4, #0x30]
	strh r0, [r4, #0x32]
	strh r0, [r4, #0x34]
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x20]
	mov r1, #0x4b
	str r0, [sp, #8]
	add r0, r4, #0
	add r2, r4, #0
	ldr r3, _021D7BB8 ; =0x00000FA4
	add r0, #0x24
	lsl r1, r1, #0xe
	add r2, #0x30
	bl FUN_0201ECA8
	mov r1, #0
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	str r1, [sp, #0xc]
	str r1, [sp, #0x14]
	ldr r1, [r4, #0x20]
	add r0, sp, #0xc
	bl FUN_0201EC58
	ldr r0, [r4, #0x20]
	bl FUN_0201EB8C
	mov r1, #0xfa
	ldr r2, [r4, #0x20]
	mov r0, #0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	add sp, #0x18
	pop {r4, pc}
	nop
_021D7BB8: .word 0x00000FA4
	thumb_func_end MOD84_021D7B54

	thumb_func_start MOD84_021D7BBC
MOD84_021D7BBC: ; 0x021D7BBC
	ldr r3, _021D7BC4 ; =FUN_0201EB70
	ldr r0, [r0, #0x20]
	bx r3
	nop
_021D7BC4: .word FUN_0201EB70
	thumb_func_end MOD84_021D7BBC

	thumb_func_start MOD84_021D7BC8
MOD84_021D7BC8: ; 0x021D7BC8
	push {r4, r5, lr}
	sub sp, #0xc
	mov r2, #0
	add r5, r0, #0
	add r4, r5, #0
	str r2, [sp]
	add r0, sp, #8
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r1, #1
	mov r3, #0x4b
	add r4, #0x38
	bl FUN_02006D18
	str r0, [r5, #0x38]
	ldr r1, [sp, #8]
	bl DC_FlushRange
	ldr r0, [r5, #0x38]
	cmp r0, #0
	beq _021D7CCC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x8c
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	str r1, [r0]
	mov r2, #0
	add r0, r4, #0
	ldr r1, _021D7CD0 ; =0xFFF8E000
	str r2, [r4, #0x7c]
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x84
	str r2, [r0]
	add r0, r4, #0
	add r0, #0x94
	strh r2, [r0]
	mov r1, #0xa5
	add r0, r4, #0
	lsl r1, r1, #4
	add r0, #0x96
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0x50
	add r0, #0x98
	strh r1, [r0]
	ldr r0, [r4]
	bl FUN_020BC13C
	str r0, [r4, #0x5c]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x60]
	ldr r0, [r4]
	bl FUN_020BC0FC
	str r0, [r4, #0x64]
	bl FUN_0201B3C4
	ldr r0, [r4]
	ldr r1, [r4, #0x64]
	bl FUN_0201B3A8
	add r0, r4, #0
	ldr r1, [r4, #0x60]
	add r0, #8
	bl FUN_020B80B4
	mov r2, #0
	str r2, [sp]
	add r0, sp, #8
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r1, #3
	mov r3, #0x4b
	bl FUN_02006D18
	str r0, [r4, #4]
	cmp r0, #0
	beq _021D7CCC
	ldr r1, [sp, #8]
	bl DC_FlushRange
	add r0, r4, #0
	add r0, #0x6c
	mov r1, #0x4b
	mov r2, #0x20
	bl FUN_02016B20
	ldr r0, [r4, #4]
	mov r1, #0
	bl FUN_020BC4C8
	add r5, r0, #0
	add r0, r4, #0
	ldr r2, [r4, #0x60]
	add r0, #0x6c
	add r1, r5, #0
	bl FUN_020BB8D0
	str r0, [r4, #0x68]
	ldr r2, [r4, #0x60]
	ldr r3, [r4, #0x64]
	add r1, r5, #0
	bl FUN_020B8110
	add r0, r4, #0
	ldr r1, [r4, #0x68]
	add r0, #8
	bl FUN_020B7EFC
	add r0, r4, #0
	mov r1, #0
	add r0, #0x9c
	str r1, [r0]
	ldr r0, [r4, #0x68]
	add r4, #0xa0
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	lsl r0, r0, #0xc
	str r0, [r4]
_021D7CCC:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021D7CD0: .word 0xFFF8E000
	thumb_func_end MOD84_021D7BC8

	thumb_func_start MOD84_021D7CD4
MOD84_021D7CD4: ; 0x021D7CD4
	push {r4, lr}
	add r4, r0, #0
	add r4, #0x38
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D7CF0
	add r0, r4, #0
	ldr r1, [r4, #0x68]
	add r0, #0x6c
	bl thunk_FUN_020ae84c
	ldr r0, [r4, #4]
	bl FreeToHeap
_021D7CF0:
	ldr r0, [r4]
	cmp r0, #0
	beq _021D7CFA
	bl FreeToHeap
_021D7CFA:
	pop {r4, pc}
	thumb_func_end MOD84_021D7CD4

	thumb_func_start MOD84_021D7CFC
MOD84_021D7CFC: ; 0x021D7CFC
	push {r3, r4, lr}
	sub sp, #0x4c
	add r4, r0, #0
	bl G3X_ResetMtxStack
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl FUN_020BB1C0
	bl FUN_0201EBA4
	add r4, #0x38
	add r0, sp, #0x28
	bl MTX_Identity33_
	add r0, r4, #0
	add r0, #0x94
	ldrh r0, [r0]
	ldr r3, _021D7DF0 ; =UNK_020FFA38
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #4
	bl MTX_RotX33_
	add r1, sp, #0x28
	add r0, sp, #4
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x96
	ldrh r0, [r0]
	ldr r3, _021D7DF0 ; =UNK_020FFA38
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #4
	bl MTX_RotY33_
	add r1, sp, #0x28
	add r0, sp, #4
	add r2, r1, #0
	bl MTX_Concat33
	add r0, r4, #0
	add r0, #0x98
	ldrh r0, [r0]
	ldr r3, _021D7DF0 ; =UNK_020FFA38
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #4
	bl MTX_RotZ33_
	add r1, sp, #0x28
	add r0, sp, #4
	add r2, r1, #0
	bl MTX_Concat33
	add r1, r4, #0
	add r1, #0x9c
	ldr r2, [r1]
	mov r1, #2
	lsl r1, r1, #0xa
	add r2, r2, r1
	add r1, r4, #0
	add r1, #0x9c
	str r2, [r1]
	add r1, r4, #0
	add r1, #0xa0
	ldr r2, [r1]
	add r1, r4, #0
	add r1, #0x9c
	add r0, r4, #0
	ldr r1, [r1]
	add r0, #0x9c
	cmp r1, r2
	blt _021D7DBA
	ldr r1, [r0]
	sub r1, r1, r2
	str r1, [r0]
_021D7DBA:
	add r0, r4, #0
	add r0, #0x9c
	ldr r1, [r0]
	ldr r0, [r4, #0x68]
	add r2, sp, #0x28
	str r1, [r0]
	add r0, r4, #0
	add r1, r4, #0
	add r4, #0x88
	add r0, #8
	add r1, #0x7c
	add r3, r4, #0
	bl FUN_0201B26C
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl FUN_020BB1C0
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
	add sp, #0x4c
	pop {r3, r4, pc}
	nop
_021D7DF0: .word UNK_020FFA38
	thumb_func_end MOD84_021D7CFC

	thumb_func_start MOD84_021D7DF4
MOD84_021D7DF4: ; 0x021D7DF4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r0, #0x38]
	add r5, r1, #0
	add r4, #0x38
	cmp r0, #0
	beq _021D7E08
	bl FreeToHeap
_021D7E08:
	ldr r1, _021D7ED4 ; =0x021DA648
	lsl r3, r5, #1
	mov r2, #0
	ldrh r1, [r1, r3]
	str r2, [sp]
	add r0, sp, #8
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r3, #0x4b
	bl FUN_02006D18
	str r0, [r4]
	cmp r0, #0
	beq _021D7E9A
	ldr r1, [sp, #8]
	bl DC_FlushRange
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0x88
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x8c
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	str r1, [r0]
	mov r2, #0
	add r0, r4, #0
	ldr r1, _021D7ED8 ; =0xFFF8E000
	str r2, [r4, #0x7c]
	add r0, #0x80
	str r1, [r0]
	add r0, r4, #0
	add r0, #0x84
	str r2, [r0]
	add r0, r4, #0
	add r0, #0x94
	strh r2, [r0]
	mov r1, #0xa5
	add r0, r4, #0
	lsl r1, r1, #4
	add r0, #0x96
	strh r1, [r0]
	add r0, r4, #0
	mov r1, #0x50
	add r0, #0x98
	strh r1, [r0]
	ldr r0, [r4]
	bl FUN_020BC13C
	str r0, [r4, #0x5c]
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r0, r0, r1
	str r0, [r4, #0x60]
	ldr r0, [r4]
	bl FUN_020BC0FC
	str r0, [r4, #0x64]
	bl FUN_0201B3C4
	ldr r0, [r4]
	ldr r1, [r4, #0x64]
	bl FUN_0201B3A8
	add r0, r4, #0
	ldr r1, [r4, #0x60]
	add r0, #8
	bl FUN_020B80B4
_021D7E9A:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D7ED0
	mov r1, #0
	bl FUN_020BC4C8
	add r1, r0, #0
	ldr r0, [r4, #0x68]
	ldr r2, [r4, #0x60]
	ldr r3, [r4, #0x64]
	bl FUN_020B8110
	add r0, r4, #0
	ldr r1, [r4, #0x68]
	add r0, #8
	bl FUN_020B7EFC
	add r0, r4, #0
	mov r1, #0
	add r0, #0x9c
	str r1, [r0]
	ldr r0, [r4, #0x68]
	add r4, #0xa0
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	lsl r0, r0, #0xc
	str r0, [r4]
_021D7ED0:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_021D7ED4: .word MOD84_021DA648
_021D7ED8: .word 0xFFF8E000
	thumb_func_end MOD84_021D7DF4

	thumb_func_start MOD84_021D7EDC
MOD84_021D7EDC: ; 0x021D7EDC
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0x82
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_020B1A24
	mov r0, #0x8b
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_020B1A24
	mov r0, #0x25
	lsl r0, r0, #4
	add r0, r5, r0
	bl FUN_020B1A24
	mov r0, #0x9d
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_020B19DC
	mov r0, #0xa2
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_020B19DC
	mov r0, #0xa7
	lsl r0, r0, #2
	add r0, r5, r0
	bl FUN_020B19DC
	ldr r0, [r5, #0x18]
	ldr r0, [r0]
	cmp r0, #1
	bne _021D7F2A
	mov r0, #1
	b _021D7F2C
_021D7F2A:
	mov r0, #0
_021D7F2C:
	mov r2, #0
	lsl r4, r0, #3
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	lsl r0, r0, #0xf
	str r0, [sp, #8]
	mov r0, #0x4b
	ldr r1, _021D7F84 ; =0x021DA660
	str r0, [sp, #0xc]
	mov r0, #0x82
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #0x10]
	ldrh r1, [r1, r4]
	mov r0, #0x7f
	add r3, r2, #0
	bl FUN_02006AE4
	mov r0, #0x4b
	ldr r1, _021D7F88 ; =0x021DA662
	str r0, [sp]
	mov r0, #0x9d
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp, #4]
	ldrh r1, [r1, r4]
	mov r0, #0x7f
	mov r2, #1
	mov r3, #0
	bl FUN_02006A8C
	ldr r1, _021D7F8C ; =0x021DA664
	ldr r2, _021D7F90 ; =0x021DA666
	ldrh r1, [r1, r4]
	ldrh r2, [r2, r4]
	mov r0, #0x7f
	bl MOD84_021D81DC
	mov r1, #0xad
	lsl r1, r1, #2
	str r0, [r5, r1]
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_021D7F84: .word MOD84_021DA660
_021D7F88: .word MOD84_021DA662
_021D7F8C: .word MOD84_021DA664
_021D7F90: .word MOD84_021DA666
	thumb_func_end MOD84_021D7EDC

	thumb_func_start MOD84_021D7F94
MOD84_021D7F94: ; 0x021D7F94
	push {r4, lr}
	sub sp, #0x30
	add r4, r0, #0
	bl MOD84_021D7EDC
	mov r3, #0xad
	mov r0, #1
	lsl r3, r3, #2
	str r0, [sp]
	add r2, r3, #0
	ldr r1, [r4, r3]
	sub r2, #0xac
	sub r3, #0x40
	add r0, sp, #0xc
	add r2, r4, r2
	add r3, r4, r3
	bl MOD84_021D8240
	mov r1, #0
	mov r2, #0xc8
	add r3, r2, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0xc
	add r3, #0x98
	bl MOD84_021D8260
	mov r1, #0x2b
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x2b
	lsl r0, r0, #4
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x30
	pop {r4, pc}
	thumb_func_end MOD84_021D7F94

	thumb_func_start MOD84_021D8000
MOD84_021D8000: ; 0x021D8000
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2b
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r0, #0xad
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD84_021D821C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8000

	thumb_func_start MOD84_021D801C
MOD84_021D801C: ; 0x021D801C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #0x4b
	mov r1, #0x30
	str r2, [sp]
	add r6, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D8090
	ldr r0, [sp]
	ldr r2, _021D8094 ; =0x021DA6B4
	lsl r1, r0, #4
	lsl r0, r5, #5
	add r2, r2, r0
	str r7, [r4]
	ldr r2, [r1, r2]
	str r6, [r4, #0x24]
	str r2, [r4, #0x14]
	ldr r2, _021D8098 ; =0x021DA6B8
	add r2, r2, r0
	ldr r2, [r1, r2]
	str r2, [r4, #0x18]
	ldr r2, _021D809C ; =0x021DA6BC
	add r2, r2, r0
	ldr r2, [r1, r2]
	str r2, [r4, #0x1c]
	ldr r2, _021D80A0 ; =0x021DA6C0
	add r0, r2, r0
	ldr r0, [r1, r0]
	cmp r5, #0
	str r0, [r4, #0x20]
	bne _021D8068
	ldr r0, _021D80A4 ; =MOD84_021D80B8
	str r0, [r4, #8]
	ldr r0, _021D80A8 ; =MOD84_021D80F0
	b _021D806E
_021D8068:
	ldr r0, _021D80AC ; =MOD84_021D8104
	str r0, [r4, #8]
	ldr r0, _021D80B0 ; =MOD84_021D813C
_021D806E:
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x28]
	mov r0, #1
	lsl r0, r0, #0x10
	add r1, r6, #0
	bl _s32_div_f
	str r0, [r4, #0x2c]
	mov r0, #0
	str r0, [r4, #0x10]
	ldr r0, _021D80B4 ; =MOD84_021D8150
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA98
	str r0, [r4, #4]
_021D8090:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8094: .word MOD84_021DA6B4
_021D8098: .word MOD84_021DA6B8
_021D809C: .word MOD84_021DA6BC
_021D80A0: .word MOD84_021DA6C0
_021D80A4: .word MOD84_021D80B8
_021D80A8: .word MOD84_021D80F0
_021D80AC: .word MOD84_021D8104
_021D80B0: .word MOD84_021D813C
_021D80B4: .word MOD84_021D8150
	thumb_func_end MOD84_021D801C

	.rodata

	.global MOD84_021DA648
MOD84_021DA648: ; 0x021DA648
	.byte 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00

	.global MOD84_021DA650
MOD84_021DA650: ; 0x021DA650
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD84_021DA660
MOD84_021DA660: ; 0x021DA660
	.byte 0x2F, 0x00

	.global MOD84_021DA662
MOD84_021DA662: ; 0x021DA662
	.byte 0x30, 0x00

	.global MOD84_021DA664
MOD84_021DA664: ; 0x021DA664
	.byte 0x2D, 0x00

	.global MOD84_021DA666
MOD84_021DA666: ; 0x021DA666
	.byte 0x2E, 0x00, 0x33, 0x00, 0x34, 0x00, 0x31, 0x00, 0x32, 0x00

	.global MOD84_021DA670
MOD84_021DA670: ; 0x021DA670
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD84_021DA68C
MOD84_021DA68C: ; 0x021DA68C
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD84_021DA6B4
MOD84_021DA6B4: ; 0x021DA6B4
	.byte 0x02, 0x00, 0x00, 0x00

	.global MOD84_021DA6B8
MOD84_021DA6B8: ; 0x021DA6B8
	.byte 0x03, 0x00, 0x00, 0x00

	.global MOD84_021DA6BC
MOD84_021DA6BC: ; 0x021DA6BC
	.byte 0x0C, 0x00, 0x00, 0x00

	.global MOD84_021DA6C0
MOD84_021DA6C0: ; 0x021DA6C0
	.byte 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

	.global MOD84_021DA6C8
MOD84_021DA6C8: ; 0x021DA6C8
	.byte 0x02, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00

	.global MOD84_021DA6F4
MOD84_021DA6F4: ; 0x021DA6F4
	.word MOD84_021D8874

	.global MOD84_021DA6F8
MOD84_021DA6F8: ; 0x021DA6F8
	.word MOD84_021D88A4

	.global MOD84_021DA6FC
MOD84_021DA6FC: ; 0x021DA6FC
	.word MOD84_021D88DC

	.global MOD84_021DA700
MOD84_021DA700: ; 0x021DA700
	.word MOD84_021D88C8, MOD84_021D8A8C, MOD84_021D8AAC, MOD84_021D8AD4
	.word MOD84_021D8AC0, MOD84_021D8C54, MOD84_021D8CD8, MOD84_021D8D0C
	.word MOD84_021D8CEC, MOD84_021D9394, MOD84_021D93B4, MOD84_021D93DC
	.word MOD84_021D93C8, MOD84_021D955C, MOD84_021D9594, MOD84_021D95CC
	.word MOD84_021D95B8, MOD84_021D9A54, MOD84_021D9A74, MOD84_021D9A9C
	.word MOD84_021D9A88, MOD84_021D9C1C, MOD84_021D9C80, MOD84_021D9CD4
	.word MOD84_021D9CA4
