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
	bl FUN_02006268
	add r4, r0, #0
	bne _021D7516
	b _021D7618
_021D7516:
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
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
	bl FUN_0200628C
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
	bl FUN_02015F10
_021D7618:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7668
_021D7620:
	bl FUN_02006278
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
_021D7684: .word 0x021DA6C8
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
	bl FUN_02006278
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
	bl FUN_02015F10
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
	bl FUN_0200627C
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
	bl FUN_02006278
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
	ldr r0, _021D7928 ; =0x021C48B8
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
	ldr r0, _021D7928 ; =0x021C48B8
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
_021D7928: .word 0x021C48B8
_021D792C: .word 0x0000122C
_021D7930: .word 0x021DA6FC
_021D7934: .word 0x00001228
_021D7938: .word 0x021DA700
_021D793C: .word 0x00001224
_021D7940: .word 0x021DA6F4
_021D7944: .word 0x021DA6F8
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
_021D7A60: .word 0x021DA68C
_021D7A64: .word 0x04000304
_021D7A68: .word 0xFFFF7FFF
_021D7A6C: .word 0x021DA650
_021D7A70: .word 0x021DA670
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
	bl FUN_0201E6E4
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
	ldr r3, _021D7DF0 ; =0x020FFA38
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
	ldr r3, _021D7DF0 ; =0x020FFA38
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
	ldr r3, _021D7DF0 ; =0x020FFA38
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
_021D7DF0: .word 0x020FFA38
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
_021D7ED4: .word 0x021DA648
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
_021D7F84: .word 0x021DA660
_021D7F88: .word 0x021DA662
_021D7F8C: .word 0x021DA664
_021D7F90: .word 0x021DA666
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
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
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
	ldr r0, _021D80A4 ; =0x021D80B8
	str r0, [r4, #8]
	ldr r0, _021D80A8 ; =0x021D80F0
	b _021D806E
_021D8068:
	ldr r0, _021D80AC ; =0x021D8104
	str r0, [r4, #8]
	ldr r0, _021D80B0 ; =0x021D813C
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
	ldr r0, _021D80B4 ; =0x021D8151
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA98
	str r0, [r4, #4]
_021D8090:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8094: .word 0x021DA6B4
_021D8098: .word 0x021DA6B8
_021D809C: .word 0x021DA6BC
_021D80A0: .word 0x021DA6C0
_021D80A4: .word 0x021D80B8
_021D80A8: .word 0x021D80F0
_021D80AC: .word 0x021D8104
_021D80B0: .word 0x021D813C
_021D80B4: .word 0x021D8151
	thumb_func_end MOD84_021D801C

	thumb_func_start MOD84_021D80B8
MOD84_021D80B8: ; 0x021D80B8
	and r0, r3
	thumb_func_end MOD84_021D80B8

	non_word_aligned_thumb_func_start MOD84_021D80BA
MOD84_021D80BA: ; 0x021D80BA
	thumb_func_end MOD84_021D80BA
_021D80BA:
	.byte 0x2D, 0xE9, 0x04, 0xD0, 0x4D, 0xE2
	.byte 0x00, 0x40, 0xA0, 0xE1, 0x01, 0xE0, 0xA0, 0xE1, 0x02, 0xC0, 0xA0, 0xE1, 0x00, 0x30, 0x8D, 0xE5
	.byte 0x14, 0x00, 0x9F, 0xE5, 0x04, 0x10, 0xA0, 0xE1, 0x0E, 0x20, 0xA0, 0xE1, 0x0C, 0x30, 0xA0, 0xE1
	.byte 0xFD, 0xBC, 0xFB, 0xEB, 0x04, 0xD0, 0x8D, 0xE2, 0x18, 0x80, 0xBD, 0xE8, 0x50, 0x00, 0x00, 0x04
	.byte 0x08, 0x20, 0x9F, 0xE5, 0x01, 0x04, 0x80, 0xE1, 0xB0, 0x00, 0xC2, 0xE1, 0x1E, 0xFF, 0x2F, 0xE1
	.byte 0x52, 0x00, 0x00, 0x04, 0x18, 0x40, 0x2D, 0xE9, 0x04, 0xD0, 0x4D, 0xE2, 0x00, 0x40, 0xA0, 0xE1
	.byte 0x01, 0xE0, 0xA0, 0xE1, 0x02, 0xC0, 0xA0, 0xE1, 0x00, 0x30, 0x8D, 0xE5, 0x14, 0x00, 0x9F, 0xE5
	.byte 0x04, 0x10, 0xA0, 0xE1, 0x0E, 0x20, 0xA0, 0xE1, 0x0C, 0x30, 0xA0, 0xE1, 0xEA, 0xBC, 0xFB, 0xEB
	.byte 0x04, 0xD0, 0x8D, 0xE2, 0x18, 0x80, 0xBD, 0xE8, 0x50, 0x10, 0x00, 0x04, 0x08, 0x20, 0x9F, 0xE5
	.byte 0x01, 0x04, 0x80, 0xE1, 0xB0, 0x00, 0xC2, 0xE1, 0x1E, 0xFF, 0x2F, 0xE1, 0x52, 0x10, 0x00, 0x04
	.byte 0x70, 0xB5, 0x0D, 0x1C, 0x06, 0x1C, 0x28, 0x69, 0x00, 0x28, 0x04, 0xD0, 0x01, 0x28, 0x0C, 0xD0
	.byte 0x02, 0x28, 0x1A, 0xD0, 0x70, 0xBD, 0x28, 0x6A, 0xE9, 0x69, 0xAC, 0x68, 0x00, 0x22, 0x10, 0x23
	.byte 0xA0, 0x47, 0x28, 0x69, 0x40, 0x1C, 0x28, 0x61, 0x70, 0xBD, 0xA8, 0x69, 0x02, 0x21, 0x00, 0x06
	.byte 0x00, 0x0E, 0x3F, 0xF6, 0x9B, 0xFB, 0x68, 0x69, 0x03, 0x21, 0x00, 0x06, 0x00, 0x0E, 0x3F, 0xF6
	.byte 0x95, 0xFB, 0x28, 0x69, 0x40, 0x1C, 0x28, 0x61, 0x70, 0xBD, 0xA9, 0x6A, 0xE8, 0x6A, 0x08, 0x18
	.byte 0x04, 0x13, 0xA8, 0x62, 0x10, 0x2C, 0x00, 0xDB, 0x10, 0x24, 0x10, 0x21, 0xEA, 0x68, 0x20, 0x1C
	.byte 0x09, 0x1B, 0x90, 0x47, 0x10, 0x2C, 0x04, 0xDB, 0x00, 0x20, 0x68, 0x60, 0x30, 0x1C, 0x34, 0xF6
	.byte 0x79, 0xFC, 0x70, 0xBD

	thumb_func_start MOD84_021D81C4
MOD84_021D81C4: ; 0x021D81C4
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _021D81CE
	mov r0, #1
	bx lr
_021D81CE:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD84_021D81C4

	thumb_func_start MOD84_021D81D4
MOD84_021D81D4: ; 0x021D81D4
	ldr r3, _021D81D8 ; =FreeToHeap
	bx r3
	.align 2, 0
_021D81D8: .word FreeToHeap
	thumb_func_end MOD84_021D81D4

	thumb_func_start MOD84_021D81DC
MOD84_021D81DC: ; 0x021D81DC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x4b
	mov r1, #0x10
	add r7, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D8218
	mov r0, #0x4b
	add r3, r4, #0
	str r0, [sp]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	add r3, #8
	bl FUN_02006C30
	str r0, [r4]
	mov r0, #0x4b
	add r3, r4, #0
	str r0, [sp]
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0
	add r3, #0xc
	bl FUN_02006C5C
	str r0, [r4, #4]
_021D8218:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD84_021D81DC

	thumb_func_start MOD84_021D821C
MOD84_021D821C: ; 0x021D821C
	push {r4, lr}
	add r4, r0, #0
	beq _021D823C
	ldr r0, [r4]
	cmp r0, #0
	beq _021D822C
	bl FreeToHeap
_021D822C:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D8236
	bl FreeToHeap
_021D8236:
	add r0, r4, #0
	bl FreeToHeap
_021D823C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D821C

	thumb_func_start MOD84_021D8240
MOD84_021D8240: ; 0x021D8240
	str r2, [r0]
	str r3, [r0, #8]
	ldr r2, [r1, #8]
	str r2, [r0, #0xc]
	ldr r1, [r1, #0xc]
	ldr r2, [sp]
	str r1, [r0, #0x10]
	add r1, r0, #0
	add r1, #0x20
	strb r2, [r1]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	bx lr
	thumb_func_end MOD84_021D8240

	thumb_func_start MOD84_021D8260
MOD84_021D8260: ; 0x021D8260
	push {r4, lr}
	sub sp, #0x20
	add r0, #0xdc
	ldr r0, [r0]
	str r0, [sp]
	lsl r0, r2, #0xc
	str r0, [sp, #8]
	lsl r0, r3, #0xc
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x28]
	str r1, [sp, #4]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0x18]
	mov r0, #0x4b
	str r0, [sp, #0x1c]
	add r0, sp, #0
	bl FUN_0201FF84
	add r4, r0, #0
	beq _021D82A6
	mov r1, #1
	bl FUN_020200BC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r1, [sp, #0x30]
	add r0, r4, #0
	bl FUN_020200A0
_021D82A6:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	thumb_func_end MOD84_021D8260

	thumb_func_start MOD84_021D82AC
MOD84_021D82AC: ; 0x021D82AC
	mov r1, #0x2b
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bx lr
	thumb_func_end MOD84_021D82AC

	thumb_func_start MOD84_021D82B4
MOD84_021D82B4: ; 0x021D82B4
	ldr r0, [r0, #0x10]
	bx lr
	thumb_func_end MOD84_021D82B4

	thumb_func_start MOD84_021D82B8
MOD84_021D82B8: ; 0x021D82B8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _021D8428 ; =0x00001220
	mov r1, #3
	str r1, [r4, r0]
	ldr r0, [r4, #0x18]
	ldr r7, _021D8428 ; =0x00001220
	ldr r6, [r0, #8]
	mov r5, #1
_021D82CC:
	ldr r0, _021D842C ; =0x00000186
	cmp r5, r0
	beq _021D8340
	add r0, r0, #3
	cmp r5, r0
	beq _021D8340
	ldr r0, _021D8430 ; =0x00000183
	cmp r5, r0
	beq _021D8340
	lsl r1, r5, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	bl FUN_02024594
	cmp r0, #0
	beq _021D8340
	lsl r0, r5, #0x10
	lsr r1, r0, #0x10
	ldr r0, _021D8428 ; =0x00001220
	ldr r0, [r4, r0]
	lsl r0, r0, #3
	add r2, r4, r0
	mov r0, #0xae
	lsl r0, r0, #2
	strh r1, [r2, r0]
	add r0, r6, #0
	mov r2, #0
	bl FUN_02024674
	ldr r1, _021D8428 ; =0x00001220
	ldr r1, [r4, r1]
	lsl r1, r1, #3
	add r2, r4, r1
	ldr r1, _021D8434 ; =0x000002BA
	strb r0, [r2, r1]
	bl rand_LC
	ldr r1, _021D8428 ; =0x00001220
	ldr r1, [r4, r1]
	lsl r1, r1, #3
	add r2, r4, r1
	mov r1, #0xaf
	lsl r1, r1, #2
	str r0, [r2, r1]
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #0
	bl FUN_02024DAC
	ldr r1, _021D8428 ; =0x00001220
	ldr r1, [r4, r1]
	lsl r1, r1, #3
	add r2, r4, r1
	ldr r1, _021D8438 ; =0x000002BB
	strb r0, [r2, r1]
	ldr r0, [r4, r7]
	add r0, r0, #1
	str r0, [r4, r7]
_021D8340:
	ldr r0, _021D843C ; =0x000001ED
	add r5, r5, #1
	cmp r5, r0
	blt _021D82CC
	ldr r0, _021D8428 ; =0x00001220
	mov r7, #3
	ldr r0, [r4, r0]
	sub r0, r0, #1
	cmp r0, #3
	ble _021D83B0
	add r5, r4, #0
	add r5, #0x18
_021D8358:
	bl rand_LC
	ldr r1, _021D8428 ; =0x00001220
	ldr r1, [r4, r1]
	sub r1, r1, r7
	bl _s32_div_f
	add r0, r1, #3
	mov r2, #0xaf
	lsl r2, r2, #2
	ldr r2, [r5, r2]
	lsl r0, r0, #3
	mov r1, #0xae
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	str r2, [sp]
	str r2, [sp, #8]
	mov r2, #0xae
	add r0, r4, r0
	lsl r2, r2, #2
	ldr r3, [r0, r2]
	add r2, r2, #4
	ldr r2, [r0, r2]
	str r1, [sp, #4]
	mov ip, r2
	mov r2, #0xae
	lsl r2, r2, #2
	str r3, [r5, r2]
	mov r3, ip
	add r2, r2, #4
	str r3, [r5, r2]
	mov r2, #0xae
	lsl r2, r2, #2
	str r1, [r0, r2]
	ldr r1, [sp]
	add r2, r2, #4
	str r1, [r0, r2]
	ldr r0, _021D8428 ; =0x00001220
	add r7, r7, #1
	ldr r0, [r4, r0]
	add r5, #8
	sub r0, r0, #1
	cmp r7, r0
	blt _021D8358
_021D83B0:
	bl rand_LC
	mov r1, #3
	bl _s32_div_f
	add r5, r1, #0
	mov r7, #0
_021D83BE:
	cmp r5, #0
	beq _021D83CC
	cmp r5, #1
	beq _021D83D6
	cmp r5, #2
	beq _021D83E0
	b _021D83E8
_021D83CC:
	mov r0, #0xae
	ldr r1, _021D842C ; =0x00000186
	lsl r0, r0, #2
	strh r1, [r4, r0]
	b _021D83E8
_021D83D6:
	mov r0, #0xae
	ldr r1, _021D8440 ; =0x00000189
	lsl r0, r0, #2
	strh r1, [r4, r0]
	b _021D83E8
_021D83E0:
	mov r0, #0xae
	ldr r1, _021D8430 ; =0x00000183
	lsl r0, r0, #2
	strh r1, [r4, r0]
_021D83E8:
	mov r1, #0xae
	lsl r1, r1, #2
	ldrh r1, [r4, r1]
	add r0, r6, #0
	mov r2, #0
	bl FUN_02024674
	ldr r1, _021D8434 ; =0x000002BA
	strb r0, [r4, r1]
	bl rand_LC
	mov r1, #0xaf
	lsl r1, r1, #2
	str r0, [r4, r1]
	sub r1, r1, #4
	ldrh r1, [r4, r1]
	add r0, r6, #0
	mov r2, #0
	bl FUN_02024DAC
	ldr r1, _021D8438 ; =0x000002BB
	add r5, r5, #1
	strb r0, [r4, r1]
	cmp r5, #3
	blt _021D841C
	mov r5, #0
_021D841C:
	add r7, r7, #1
	add r4, #8
	cmp r7, #3
	blt _021D83BE
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8428: .word 0x00001220
_021D842C: .word 0x00000186
_021D8430: .word 0x00000183
_021D8434: .word 0x000002BA
_021D8438: .word 0x000002BB
_021D843C: .word 0x000001ED
_021D8440: .word 0x00000189
	thumb_func_end MOD84_021D82B8

	thumb_func_start MOD84_021D8444
MOD84_021D8444: ; 0x021D8444
	ldr r1, _021D844C ; =0x00001220
	ldr r0, [r0, r1]
	bx lr
	nop
_021D844C: .word 0x00001220
	thumb_func_end MOD84_021D8444

	thumb_func_start MOD84_021D8450
MOD84_021D8450: ; 0x021D8450
	mov r1, #0xae
	lsl r1, r1, #2
	add r0, r0, r1
	bx lr
	thumb_func_end MOD84_021D8450

	thumb_func_start MOD84_021D8458
MOD84_021D8458: ; 0x021D8458
	add r1, r0, #0
	ldr r0, _021D8464 ; =0x00001234
	ldr r3, _021D8468 ; =MOD84_021D847C
	add r0, r1, r0
	bx r3
	nop
_021D8464: .word 0x00001234
_021D8468: .word MOD84_021D847C
	thumb_func_end MOD84_021D8458

	thumb_func_start MOD84_021D846C
MOD84_021D846C: ; 0x021D846C
	ldr r1, _021D8474 ; =0x00001234
	ldr r3, _021D8478 ; =MOD84_021D84A0
	add r0, r0, r1
	bx r3
	.align 2, 0
_021D8474: .word 0x00001234
_021D8478: .word MOD84_021D84A0
	thumb_func_end MOD84_021D846C

	thumb_func_start MOD84_021D847C
MOD84_021D847C: ; 0x021D847C
	push {r3, lr}
	mov r3, #0
	str r3, [r0, #4]
	str r1, [r0]
	mov r1, #1
	str r3, [r0, #8]
	lsl r1, r1, #0xa
	str r1, [r0, #0xc]
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021D849C ; =0x04001050
	mov r1, #2
	mov r2, #0x3f
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.align 2, 0
_021D849C: .word 0x04001050
	thumb_func_end MOD84_021D847C

	thumb_func_start MOD84_021D84A0
MOD84_021D84A0: ; 0x021D84A0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r1, [r4]
	cmp r0, #0
	beq _021D84B2
	cmp r0, #1
	beq _021D84C2
	b _021D84EC
_021D84B2:
	ldr r0, [r1, #0xc]
	mov r1, #0
	bl MOD84_021D87B0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _021D84F0
_021D84C2:
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r0, r1, r0
	asr r2, r0, #0xc
	str r0, [r4, #8]
	cmp r2, #0x10
	blt _021D84D2
	mov r2, #0x10
_021D84D2:
	mov r0, #0x10
	sub r0, r0, r2
	lsl r0, r0, #8
	add r1, r2, #0
	orr r1, r0
	ldr r0, _021D84F4 ; =0x04001052
	cmp r2, #0x10
	strh r1, [r0]
	bne _021D84F0
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	b _021D84F0
_021D84EC:
	mov r0, #1
	pop {r4, pc}
_021D84F0:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D84F4: .word 0x04001052
	thumb_func_end MOD84_021D84A0

	thumb_func_start MOD84_021D84F8
MOD84_021D84F8: ; 0x021D84F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	str r1, [sp, #0x14]
	mov r0, #0x4b
	mov r1, #0x38
	add r5, r2, #0
	add r7, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D85AC
	ldr r0, [sp, #0x14]
	str r6, [r4, #0x20]
	str r0, [r4]
	add r0, #0xc0
	str r0, [r4, #4]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x30]
	str r5, [r4, #8]
	str r0, [r4, #0x2c]
	mov r0, #0
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0x4b
	bl FUN_020219F4
	str r0, [r4, #0x30]
	mov r0, #0x4b
	mov r1, #1
	bl FUN_02018FF4
	str r0, [r4, #0x24]
	mov r3, #0
	lsl r2, r5, #0x18
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r1, [r4, #0x24]
	add r0, r6, #0
	lsr r2, r2, #0x18
	bl FUN_02019064
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl FUN_02019620
	ldr r0, [r4, #0x24]
	bl FUN_02019270
	ldr r0, [r4, #0x24]
	bl FUN_020191D0
	mov r0, #0x4b
	mov r1, #1
	bl FUN_02018FF4
	str r0, [r4, #0x28]
	mov r3, #0
	lsl r2, r5, #0x18
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r1, [r4, #0x28]
	add r0, r6, #0
	lsr r2, r2, #0x18
	bl FUN_02019064
	ldr r0, _021D85B4 ; =MOD84_021D8784
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA98
	str r0, [r4, #0x34]
_021D85AC:
	add r0, r4, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D85B4: .word MOD84_021D8784
	thumb_func_end MOD84_021D84F8

	thumb_func_start MOD84_021D85B8
MOD84_021D85B8: ; 0x021D85B8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x34]
	cmp r0, #0
	beq _021D85C6
	bl FUN_0200CAB4
_021D85C6:
	ldr r0, [r4, #0x30]
	bl FUN_02021A20
	ldr r0, [r4, #0x24]
	bl FUN_02019178
	ldr r0, [r4, #0x28]
	bl FUN_02019178
	ldr r0, [r4, #0x24]
	bl FreeToHeap
	ldr r0, [r4, #0x28]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD84_021D85B8

	thumb_func_start MOD84_021D85EC
MOD84_021D85EC: ; 0x021D85EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	ldr r2, [r5, #0x1c]
	str r1, [sp, #0x18]
	cmp r2, #2
	bne _021D8600
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D8600:
	ldr r1, [r5, #4]
	ldr r0, [sp, #0x18]
	add r6, r1, r0
	cmp r2, #0
	bne _021D86E0
	ldr r2, [r5, #0xc]
	mov r0, #6
	add r1, r2, #0
	mul r1, r0
	ldr r0, _021D8774 ; =0x021DA766
	ldrh r0, [r0, r1]
	cmp r6, r0
	blt _021D86E0
	ldr r2, _021D8778 ; =0x021DA764
	ldr r0, [r5, #0x2c]
	ldrh r1, [r2, r1]
	ldr r2, [r5, #0x30]
	bl FUN_0200A8E0
	ldr r1, [r5, #0xc]
	mov r0, #6
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021D877C ; =0x021DA768
	ldrh r0, [r0, r2]
	cmp r0, #0
	beq _021D864A
	mov r0, #0
	ldr r1, [r5, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #1
	lsl r1, r1, #8
	sub r0, r1, r0
	lsr r7, r0, #1
	b _021D864C
_021D864A:
	mov r7, #0x20
_021D864C:
	ldr r1, [r5, #0xc]
	mov r0, #6
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021D8774 ; =0x021DA766
	mov r1, #0
	ldrh r0, [r0, r2]
	add r3, r7, #0
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	str r4, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8780 ; =0x00010200
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #0x24]
	ldr r2, [r5, #0x30]
	bl FUN_0201BDE0
	cmp r4, #0xf0
	ble _021D86D0
	ldr r0, [r5, #0x28]
	mov r1, #0
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8780 ; =0x00010200
	add r3, r7, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r5, #0x28]
	ldr r2, [r5, #0x30]
	bl FUN_0201BDE0
	ldr r1, [r5, #0x28]
	sub r4, #0xf0
	ldrb r2, [r1, #7]
	mov r0, #0x10
	sub r3, r0, r4
	add r4, r0, #0
	sub r0, r0, r3
	lsl r2, r2, #0x13
	lsr r2, r2, #0x10
	str r2, [sp]
	ldrb r2, [r1, #8]
	lsl r0, r0, #0x10
	lsl r3, r3, #0x10
	lsl r2, r2, #0x13
	lsr r2, r2, #0x10
	str r2, [sp, #4]
	mov r2, #0
	str r2, [sp, #8]
	str r2, [sp, #0xc]
	add r4, #0xf0
	str r4, [sp, #0x10]
	lsr r0, r0, #0x10
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x24]
	ldr r1, [r1, #0xc]
	lsr r3, r3, #0x10
	bl FUN_02019658
_021D86D0:
	mov r1, #1
	str r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #0xd6
	blo _021D86E0
	str r1, [r5, #0x1c]
_021D86E0:
	str r6, [r5, #4]
	ldr r0, [r5, #0x10]
	mov r1, #6
	add r2, r0, #0
	ldr r0, _021D8774 ; =0x021DA766
	mul r2, r1
	ldrh r3, [r0, r2]
	ldr r2, [r5]
	add r0, r3, #0
	add r0, #0x10
	cmp r2, r0
	ble _021D8766
	lsl r0, r3, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0xf0
	bgt _021D8718
	add r1, #0xfa
	str r1, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r1, #0
	lsl r3, r3, #0x10
	ldr r0, [r5, #0x24]
	add r2, r1, #0
	lsr r3, r3, #0x10
	bl FUN_020196F4
	b _021D8754
_021D8718:
	add r1, r3, #0
	sub r1, #0xf0
	mov r0, #0x10
	sub r4, r0, r1
	add r0, #0xf0
	str r0, [sp]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	mov r1, #0
	lsl r3, r3, #0x10
	ldr r0, [r5, #0x24]
	add r2, r1, #0
	lsr r3, r3, #0x10
	bl FUN_020196F4
	mov r1, #0
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x10
	sub r0, r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r5, #0x24]
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
_021D8754:
	mov r0, #1
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x10]
	add r0, r0, #1
	str r0, [r5, #0x10]
	cmp r0, #0xd7
	blo _021D8766
	mov r0, #2
	str r0, [r5, #0x1c]
_021D8766:
	ldr r1, [r5]
	ldr r0, [sp, #0x18]
	add r0, r1, r0
	str r0, [r5]
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8774: .word 0x021DA766
_021D8778: .word 0x021DA764
_021D877C: .word 0x021DA768
_021D8780: .word 0x00010200
	thumb_func_end MOD84_021D85EC

	thumb_func_start MOD84_021D8784
MOD84_021D8784: ; 0x021D8784
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021D8798
	ldr r0, [r4, #0x24]
	bl FUN_02019548
	mov r0, #0
	str r0, [r4, #0x18]
_021D8798:
	ldr r1, [r4, #8]
	ldr r3, [r4]
	lsl r1, r1, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r4, #0x20]
	lsr r1, r1, #0x18
	mov r2, #3
	lsr r3, r3, #0x18
	bl FUN_020179E0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8784

	thumb_func_start MOD84_021D87B0
MOD84_021D87B0: ; 0x021D87B0
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #2
	str r0, [r5, #0x1c]
	mov r0, #0
	str r0, [r5, #0x18]
	cmp r1, #0
	beq _021D87CE
	ldr r0, [r5, #0x24]
	mov r1, #0xf
	bl FUN_02019620
	ldr r4, _021D8814 ; =0x0001020F
	b _021D87D0
_021D87CE:
	ldr r4, _021D8818 ; =0x00010200
_021D87D0:
	ldr r0, [r5, #0x2c]
	ldr r2, [r5, #0x30]
	mov r1, #0xd7
	bl FUN_0200A8E0
	mov r0, #0
	ldr r1, [r5, #0x30]
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #1
	lsl r1, r1, #8
	sub r0, r1, r0
	mov r1, #0
	lsr r3, r0, #1
	str r1, [r5]
	mov r0, #0x50
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	str r4, [sp, #8]
	mov r0, #3
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [r5, #0x24]
	ldr r2, [r5, #0x30]
	bl FUN_0201BE3C
	ldr r0, [r5, #0x24]
	bl FUN_02019548
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8814: .word 0x0001020F
_021D8818: .word 0x00010200
	thumb_func_end MOD84_021D87B0

	thumb_func_start MOD84_021D881C
MOD84_021D881C: ; 0x021D881C
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #2
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #0x18]
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x20]
	ldr r3, [r4, #8]
	mov r0, #0x7f
	mov r1, #0x2a
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x20]
	ldr r3, [r4, #8]
	mov r0, #0x7f
	mov r1, #0x2b
	bl FUN_0200687C
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x4b
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r1, #0x2c
	add r3, r2, #0
	bl FUN_02006930
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D881C

	thumb_func_start MOD84_021D8874
MOD84_021D8874: ; 0x021D8874
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x4b
	mov r1, #0x1c
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D88A0
	str r5, [r4]
	str r6, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	add r0, r5, #0
	bl MOD84_021D82AC
	str r0, [r4, #8]
	mov r0, #0
	str r0, [r4, #0xc]
	sub r0, #0x36
	str r0, [r4, #0x10]
_021D88A0:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD84_021D8874

	thumb_func_start MOD84_021D88A4
MOD84_021D88A4: ; 0x021D88A4
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D8958
	cmp r0, #0
	beq _021D88C4
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #1
	pop {r4, pc}
_021D88C4:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD84_021D88A4

	thumb_func_start MOD84_021D88C8
MOD84_021D88C8: ; 0x021D88C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D8A74
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D88C8

	thumb_func_start MOD84_021D88DC
MOD84_021D88DC: ; 0x021D88DC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #0xc]
	ldr r0, [r5, #0x10]
	mov r7, #1
	add r0, r1, r0
	str r0, [r5, #0xc]
	asr r6, r0, #0xc
	lsl r7, r7, #8
	ldr r0, [r5, #4]
	mov r1, #2
	mov r2, #0
	add r3, r6, r7
	bl FUN_020179E0
	ldr r0, [r5, #4]
	mov r1, #6
	mov r2, #0
	add r3, r6, r7
	bl FUN_020179E0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D8914
	cmp r0, #1
	beq _021D893A
	b _021D8950
_021D8914:
	ldr r0, [r5, #0x14]
	add r1, r0, #1
	ldr r0, _021D8954 ; =0x00000708
	str r1, [r5, #0x14]
	cmp r1, r0
	blt _021D8950
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8950
_021D893A:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D8950
	ldr r0, [r5, #8]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8950:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8954: .word 0x00000708
	thumb_func_end MOD84_021D88DC

	thumb_func_start MOD84_021D8958
MOD84_021D8958: ; 0x021D8958
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #4
	bhi _021D8A50
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8972: ; jump table
	.short _021D897C - _021D8972 - 2 ; case 0
	.short _021D899C - _021D8972 - 2 ; case 1
	.short _021D89D8 - _021D8972 - 2 ; case 2
	.short _021D8A10 - _021D8972 - 2 ; case 3
	.short _021D8A30 - _021D8972 - 2 ; case 4
_021D897C:
	ldr r0, [r5, #4]
	ldr r2, _021D8A6C ; =0x021DAC70
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	ldr r2, _021D8A6C ; =0x021DAC70
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8A64
_021D899C:
	mov r0, #0x80
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #6
	str r0, [sp, #4]
	mov r0, #0x4b
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #0x7f
	mov r1, #0x41
	add r3, r2, #0
	bl FUN_02006948
	mov r0, #0x80
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #6
	str r0, [sp, #4]
	mov r0, #0x4b
	str r0, [sp, #8]
	mov r0, #0x7f
	mov r1, #0x41
	mov r2, #4
	mov r3, #0
	bl FUN_02006948
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8A64
_021D89D8:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #4
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	mov r1, #6
	ldr r2, [r5, #4]
	mov r0, #0x7f
	add r3, r1, #0
	bl FUN_020068C8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8A64
_021D8A10:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #5
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8A64
_021D8A30:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #7
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8A64
_021D8A50:
	ldr r0, _021D8A70 ; =0x04000050
	mov r1, #0
	mov r2, #0xc
	mov r3, #0x10
	str r1, [sp]
	bl G2x_SetBlendAlpha_
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8A64:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D8A6C: .word 0x021DAC70
_021D8A70: .word 0x04000050
	thumb_func_end MOD84_021D8958

	thumb_func_start MOD84_021D8A74
MOD84_021D8A74: ; 0x021D8A74
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8A74

	thumb_func_start MOD84_021D8A8C
MOD84_021D8A8C: ; 0x021D8A8C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x4b
	mov r1, #0x10
	bl AllocFromHeap
	cmp r0, #0
	beq _021D8AA8
	str r5, [r0]
	str r4, [r0, #4]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
_021D8AA8:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8A8C

	thumb_func_start MOD84_021D8AAC
MOD84_021D8AAC: ; 0x021D8AAC
	push {r3, lr}
	bl MOD84_021D8B70
	cmp r0, #0
	beq _021D8ABA
	mov r0, #1
	pop {r3, pc}
_021D8ABA:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8AAC

	thumb_func_start MOD84_021D8AC0
MOD84_021D8AC0: ; 0x021D8AC0
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D8C3C
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8AC0

	thumb_func_start MOD84_021D8AD4
MOD84_021D8AD4: ; 0x021D8AD4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _021D8B66
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8AEC: ; jump table
	.short _021D8AF4 - _021D8AEC - 2 ; case 0
	.short _021D8B16 - _021D8AEC - 2 ; case 1
	.short _021D8B28 - _021D8AEC - 2 ; case 2
	.short _021D8B4E - _021D8AEC - 2 ; case 3
_021D8AF4:
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r1, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x20
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8B66
_021D8B16:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D8B66
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8B66
_021D8B28:
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	ldr r0, _021D8B6C ; =0x000002DF
	cmp r1, r0
	blt _021D8B66
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8B66
_021D8B4E:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D8B66
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_021D8B66:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D8B6C: .word 0x000002DF
	thumb_func_end MOD84_021D8AD4

	thumb_func_start MOD84_021D8B70
MOD84_021D8B70: ; 0x021D8B70
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021D8C2A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8B8A: ; jump table
	.short _021D8B92 - _021D8B8A - 2 ; case 0
	.short _021D8BB2 - _021D8B8A - 2 ; case 1
	.short _021D8BEA - _021D8B8A - 2 ; case 2
	.short _021D8C0A - _021D8B8A - 2 ; case 3
_021D8B92:
	ldr r0, [r5, #4]
	ldr r2, _021D8C38 ; =0x021DAC8C
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	ldr r2, _021D8C38 ; =0x021DAC8C
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C30
_021D8BB2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x24
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x22
	mov r3, #6
	bl FUN_020068C8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C30
_021D8BEA:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x25
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C30
_021D8C0A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x23
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D8C30
_021D8C2A:
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8C30:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D8C38: .word 0x021DAC8C
	thumb_func_end MOD84_021D8B70

	thumb_func_start MOD84_021D8C3C
MOD84_021D8C3C: ; 0x021D8C3C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8C3C

	thumb_func_start MOD84_021D8C54
MOD84_021D8C54: ; 0x021D8C54
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0xe
	add r5, r0, #0
	mov r0, #0x4b
	lsl r1, r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D8CC6
	str r5, [r4]
	ldr r1, _021D8CCC ; =0x00000DF4
	str r6, [r4, #4]
	mov r2, #0
	str r2, [r4, r1]
	add r0, r1, #4
	str r2, [r4, r0]
	add r1, #0xa
	strh r2, [r4, r1]
	bl rand_LC
	ldr r1, _021D8CD0 ; =0x00000DFC
	strh r0, [r4, r1]
	add r0, r5, #0
	bl MOD84_021D8444
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r5, #0
	bl MOD84_021D8450
	mov r1, #0x5b
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, _021D8CD4 ; =MOD84_021D9278
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA44
	mov r1, #0x5a
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r2, #0
	str r2, [r4, #0xc]
	mov r0, #0x15
	str r2, [r4, #8]
	add r3, r4, #0
	add r1, r2, #0
	lsl r0, r0, #4
_021D8CB8:
	str r1, [r3, #0x60]
	str r1, [r3, #0x48]
	str r1, [r3, r0]
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, #6
	blt _021D8CB8
_021D8CC6:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_021D8CCC: .word 0x00000DF4
_021D8CD0: .word 0x00000DFC
_021D8CD4: .word MOD84_021D9278
	thumb_func_end MOD84_021D8C54

	thumb_func_start MOD84_021D8CD8
MOD84_021D8CD8: ; 0x021D8CD8
	push {r3, lr}
	bl MOD84_021D8DF8
	cmp r0, #0
	beq _021D8CE6
	mov r0, #1
	pop {r3, pc}
_021D8CE6:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD84_021D8CD8

	thumb_func_start MOD84_021D8CEC
MOD84_021D8CEC: ; 0x021D8CEC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D8D08 ; =0x00000DFC
	ldrh r0, [r4, r0]
	bl seedr_LC
	add r0, r4, #0
	bl MOD84_021D9044
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
_021D8D08: .word 0x00000DFC
	thumb_func_end MOD84_021D8CEC

	thumb_func_start MOD84_021D8D0C
MOD84_021D8D0C: ; 0x021D8D0C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #3
	bhi _021D8DC8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8D24: ; jump table
	.short _021D8D2C - _021D8D24 - 2 ; case 0
	.short _021D8D56 - _021D8D24 - 2 ; case 1
	.short _021D8D6E - _021D8D24 - 2 ; case 2
	.short _021D8D9E - _021D8D24 - 2 ; case 3
_021D8D2C:
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E74C
	mov r1, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x20
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8DE6
_021D8D56:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D8DE6
	ldr r0, _021D8DEC ; =0x00000DF4
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8DE6
_021D8D6E:
	ldr r1, _021D8DEC ; =0x00000DF4
	ldr r2, [r4, r1]
	cmp r2, #0
	bne _021D8D98
	mov r2, #0x64
	str r2, [r4, r1]
	add r1, #0xa
	ldrh r1, [r4, r1]
	bl MOD84_021D90C4
	ldr r0, _021D8DF0 ; =0x00000DFE
	ldrh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, r0]
	ldrh r0, [r4, r0]
	cmp r0, #6
	blo _021D8DE6
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8DE6
_021D8D98:
	sub r0, r2, #1
	str r0, [r4, r1]
	b _021D8DE6
_021D8D9E:
	ldr r0, _021D8DEC ; =0x00000DF4
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	ldr r0, _021D8DF4 ; =0x000002FD
	cmp r1, r0
	blt _021D8DE6
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8DE6
_021D8DC8:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D8DE6
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8DE6:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_021D8DEC: .word 0x00000DF4
_021D8DF0: .word 0x00000DFE
_021D8DF4: .word 0x000002FD
	thumb_func_end MOD84_021D8D0C

	thumb_func_start MOD84_021D8DF8
MOD84_021D8DF8: ; 0x021D8DF8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x6c
	add r4, r0, #0
	ldr r0, [r1]
	str r1, [sp, #0x14]
	cmp r0, #8
	bls _021D8E08
	b _021D9028
_021D8E08:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8E14: ; jump table
	.short _021D8E26 - _021D8E14 - 2 ; case 0
	.short _021D8E4A - _021D8E14 - 2 ; case 1
	.short _021D8E86 - _021D8E14 - 2 ; case 2
	.short _021D8EAA - _021D8E14 - 2 ; case 3
	.short _021D8ECE - _021D8E14 - 2 ; case 4
	.short _021D8EF2 - _021D8E14 - 2 ; case 5
	.short _021D8F40 - _021D8E14 - 2 ; case 6
	.short _021D8F86 - _021D8E14 - 2 ; case 7
	.short _021D8FD4 - _021D8E14 - 2 ; case 8
_021D8E26:
	ldr r0, [r4, #4]
	ldr r2, _021D903C ; =0x021DACB8
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021D903C ; =0x021DACB8
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8E4A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x22
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x22
	mov r3, #6
	bl FUN_020068C8
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8E86:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x23
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8EAA:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x23
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8ECE:
	mov r0, #0x7f
	mov r1, #0x35
	mov r2, #0x36
	bl MOD84_021D81DC
	str r0, [r4, #8]
	mov r0, #0x1b
	mov r1, #0x29
	mov r2, #0x2a
	bl MOD84_021D81DC
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8EF2:
	add r0, r4, #0
	add r0, #0x10
	bl FUN_020B1A24
	add r0, r4, #0
	add r0, #0x34
	bl FUN_020B19DC
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #0x10]
	mov r0, #0x7f
	mov r1, #0x37
	add r3, r2, #0
	bl FUN_02006AE4
	mov r0, #0x4b
	str r0, [sp]
	add r4, #0x34
	mov r0, #0x7f
	mov r1, #0x38
	mov r2, #1
	mov r3, #0
	str r4, [sp, #4]
	bl FUN_02006A8C
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8F40:
	mov r0, #1
	str r0, [sp]
	add r2, r4, #0
	add r3, r4, #0
	ldr r1, [r4, #8]
	add r0, sp, #0x48
	add r2, #0x10
	add r3, #0x34
	bl MOD84_021D8240
	mov r6, #0
	add r5, r4, #0
	add r7, r6, #0
_021D8F5A:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r7, [sp, #8]
	ldr r0, [r4]
	add r1, sp, #0x48
	add r2, r7, #0
	add r3, r7, #0
	bl MOD84_021D8260
	str r0, [r5, #0x48]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _021D8F5A
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8F86:
	mov r0, #0x4b
	str r0, [sp]
	mov r0, #0x1b
	mov r1, #0x28
	mov r2, #0
	add r3, sp, #0x20
	bl FUN_02006BB0
	str r0, [sp, #0x18]
	cmp r0, #0
	beq _021D8FC8
	mov r5, #0x19
	lsl r5, r5, #8
	mov r6, #0
	add r4, #0x78
	lsr r7, r5, #1
_021D8FA6:
	add r0, r4, #0
	bl FUN_020B1A24
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	mov r2, #1
	add r3, r4, #0
	bl FUN_020B1768
	add r6, r6, #1
	add r4, #0x24
	add r5, r5, r7
	cmp r6, #6
	blt _021D8FA6
	ldr r0, [sp, #0x18]
	bl FreeToHeap
_021D8FC8:
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D8FD4:
	add r0, r4, #0
	add r6, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0x34
	mov r7, #0
	add r6, #0x78
	add r5, r4, #0
	str r0, [sp, #0x1c]
_021D8FE4:
	mov r0, #1
	str r0, [sp]
	ldr r1, [r4, #0xc]
	ldr r3, [sp, #0x1c]
	add r0, sp, #0x24
	add r2, r6, #0
	bl MOD84_021D8240
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	mov r2, #0
	ldr r0, [r4]
	add r1, sp, #0x24
	add r3, r2, #0
	bl MOD84_021D8260
	mov r1, #0xe
	str r0, [r5, #0x60]
	bl FUN_020202A8
	add r7, r7, #1
	add r6, #0x24
	add r5, r5, #4
	cmp r7, #6
	blt _021D8FE4
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021D9034
_021D9028:
	ldr r0, _021D9040 ; =0x00003485
	bl seedr_LC
	add sp, #0x6c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D9034:
	mov r0, #0
	add sp, #0x6c
	pop {r4, r5, r6, r7, pc}
	nop
_021D903C: .word 0x021DACB8
_021D9040: .word 0x00003485
	thumb_func_end MOD84_021D8DF8

	thumb_func_start MOD84_021D9044
MOD84_021D9044: ; 0x021D9044
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl OS_DisableInterrupts
	mov r7, #0x15
	str r0, [sp]
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_021D9056:
	ldr r0, [r5, #0x48]
	cmp r0, #0
	beq _021D9060
	bl FUN_0201FFC8
_021D9060:
	ldr r0, [r5, #0x60]
	cmp r0, #0
	beq _021D906A
	bl FUN_0201FFC8
_021D906A:
	ldr r0, [r5, r7]
	cmp r0, #0
	beq _021D9082
	bl FUN_0201B6C8
	bl FreeToHeap
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0200CAB4
_021D9082:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _021D9056
	mov r0, #0x5a
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _021D9098
	bl FUN_0200CAB4
_021D9098:
	ldr r0, [r6, #8]
	cmp r0, #0
	beq _021D90A2
	bl MOD84_021D821C
_021D90A2:
	ldr r0, [r6, #0xc]
	cmp r0, #0
	beq _021D90AC
	bl MOD84_021D821C
_021D90AC:
	ldr r0, [r6, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r6, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [sp]
	bl OS_RestoreInterrupts
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD84_021D9044

	thumb_func_start MOD84_021D90C4
MOD84_021D90C4: ; 0x021D90C4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x4b
	mov r1, #0x38
	bl AllocFromHeap
	add r4, r0, #0
	bne _021D90DA
	b _021D91F6
_021D90DA:
	mov r0, #1
	str r0, [r4]
	str r5, [r4, #4]
	mov r0, #0x17
	str r6, [r4, #8]
	lsl r0, r0, #4
	ldr r1, [r5, r0]
	cmp r6, r1
	blt _021D90F4
	add r0, r6, #0
	bl _s32_div_f
	b _021D90F6
_021D90F4:
	add r1, r6, #0
_021D90F6:
	lsl r6, r6, #2
	str r1, [r4, #0xc]
	add r1, r5, r6
	ldr r0, [r1, #0x48]
	str r0, [r4, #0x14]
	ldr r0, [r1, #0x60]
	str r0, [r4, #0x10]
	mov r0, #0x5b
	lsl r0, r0, #2
	ldr r3, [r5, r0]
	ldr r0, [r4, #0xc]
	ldr r7, [r4, #8]
	lsl r1, r0, #3
	mov r0, #0
	add r2, r3, r1
	str r0, [sp]
	ldrb r0, [r2, #3]
	str r0, [sp, #4]
	ldr r0, [r2, #4]
	str r0, [sp, #8]
	ldrh r1, [r3, r1]
	ldrb r2, [r2, #2]
	add r0, sp, #0xc
	mov r3, #2
	bl FUN_02068C00
	mov r0, #0x5d
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp]
	add r1, sp, #0xc
	ldrh r0, [r1]
	ldrh r1, [r1, #2]
	ldr r3, _021D91FC ; =0x021DACA8
	mov r2, #0x4b
	bl FUN_02012400
	mov r0, #0x5d
	lsl r0, r0, #2
	mov r1, #0x32
	add r0, r5, r0
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r2, #0x32
	mov r0, #0x5d
	lsl r2, r2, #6
	add r1, r7, #0
	lsl r0, r0, #2
	mul r1, r2
	lsl r3, r2, #1
	add r0, r5, r0
	add r1, r1, r3
	bl GX_LoadOBJ
	mov r0, #0x4e
	lsl r0, r0, #0xe
	str r0, [r4, #0x18]
	bl rand_LC
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x19
	sub r1, r1, r2
	mov r0, #0x19
	ror r1, r0
	add r0, r2, r1
	add r0, #0xf0
	lsl r0, r0, #0xc
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x20]
	bl rand_LC
	ldr r1, _021D9200 ; =0x00000667
	bl _s32_div_f
	ldr r0, _021D9204 ; =0x00000666
	add r0, r1, r0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	str r0, [r4, #0x30]
	mov r0, #0
	str r0, [r4, #0x28]
	bl rand_LC
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	add r0, r0, #2
	lsl r0, r0, #0xc
	str r0, [r4, #0x2c]
	bl rand_LC
	mov r1, #0xc
	bl _s32_div_f
	add r0, r1, #4
	str r0, [r4, #0x34]
	add r1, r4, #0
	ldr r0, [r4, #0x14]
	add r1, #0x18
	bl FUN_02020044
	add r1, r4, #0
	ldr r0, [r4, #0x10]
	add r1, #0x18
	bl FUN_02020044
	ldr r0, [r4, #0x14]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _021D9208 ; =MOD84_021D920C
	add r1, r4, #0
	mov r2, #0
	bl FUN_0200CA60
	mov r1, #0x15
	add r2, r5, r6
	lsl r1, r1, #4
	str r0, [r2, r1]
_021D91F6:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D91FC: .word 0x021DACA8
_021D9200: .word 0x00000667
_021D9204: .word 0x00000666
_021D9208: .word MOD84_021D920C
	thumb_func_end MOD84_021D90C4

	thumb_func_start MOD84_021D920C
MOD84_021D920C: ; 0x021D920C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #1
	bne _021D9270
	ldr r2, [r4, #0x28]
	ldr r1, [r4, #0x2c]
	add r0, r4, #0
	add r2, r2, r1
	mov r1, #0x5a
	lsl r1, r1, #0xe
	add r0, #0x28
	str r2, [r4, #0x28]
	cmp r2, r1
	blt _021D9230
	ldr r2, [r0]
	sub r1, r2, r1
	str r1, [r0]
_021D9230:
	ldr r2, [r4, #0x28]
	ldr r0, [r4, #0x34]
	asr r2, r2, #0xc
	lsl r3, r2, #2
	ldr r2, _021D9274 ; =0x020EDF50
	ldr r1, [r4, #0x30]
	ldr r2, [r2, r3]
	mul r2, r0
	add r0, r1, r2
	str r0, [r4, #0x1c]
	ldr r2, [r4, #0x18]
	ldr r0, [r4, #0x24]
	add r1, r4, #0
	sub r0, r2, r0
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x14]
	add r1, #0x18
	bl FUN_02020044
	add r1, r4, #0
	ldr r0, [r4, #0x10]
	add r1, #0x18
	bl FUN_02020044
	ldr r0, [r4, #0x18]
	asr r1, r0, #0xc
	mov r0, #0x37
	mvn r0, r0
	cmp r1, r0
	bge _021D9270
	mov r0, #0
	str r0, [r4]
_021D9270:
	pop {r4, pc}
	nop
_021D9274: .word 0x020EDF50
	thumb_func_end MOD84_021D920C

	thumb_func_start MOD84_021D9278
MOD84_021D9278: ; 0x021D9278
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r1, [sp, #0xc]
	mov r7, #0
	add r6, r1, #0
_021D9282:
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	cmp r0, #0
	beq _021D937A
	bl FUN_0201B6C8
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _021D937A
	mov r1, #0x17
	ldr r0, [r4, #0xc]
	ldr r2, [sp, #0xc]
	lsl r1, r1, #4
	ldr r1, [r2, r1]
	add r0, r0, #6
	cmp r0, r1
	blt _021D92AE
	bl _s32_div_f
	add r0, r1, #0
_021D92AE:
	str r0, [r4, #0xc]
	ldr r1, [r4, #8]
	ldr r5, [r4, #4]
	str r1, [sp, #0x10]
	mov r1, #0x5b
	lsl r1, r1, #2
	ldr r3, [r5, r1]
	lsl r1, r0, #3
	mov r0, #0
	add r2, r3, r1
	str r0, [sp]
	ldrb r0, [r2, #3]
	str r0, [sp, #4]
	ldr r0, [r2, #4]
	str r0, [sp, #8]
	ldrh r1, [r3, r1]
	ldrb r2, [r2, #2]
	add r0, sp, #0x14
	mov r3, #2
	bl FUN_02068C00
	mov r0, #0x5d
	lsl r0, r0, #2
	add r0, r5, r0
	str r0, [sp]
	add r0, sp, #0x14
	add r1, sp, #0x14
	ldrh r0, [r0]
	ldrh r1, [r1, #2]
	ldr r3, _021D9388 ; =0x021DACA8
	mov r2, #0x4b
	bl FUN_02012400
	mov r0, #0x5d
	lsl r0, r0, #2
	mov r1, #0x32
	add r0, r5, r0
	lsl r1, r1, #6
	bl DC_FlushRange
	ldr r2, [sp, #0x10]
	mov r1, #0x32
	mov r0, #0x5d
	add r3, r2, #0
	lsl r1, r1, #6
	lsl r0, r0, #2
	mul r3, r1
	lsl r1, r1, #1
	mov r2, #0x32
	add r0, r5, r0
	add r1, r3, r1
	lsl r2, r2, #6
	bl GX_LoadOBJ
	mov r0, #0x4e
	lsl r0, r0, #0xe
	str r0, [r4, #0x18]
	bl rand_LC
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x19
	sub r1, r1, r2
	mov r0, #0x19
	ror r1, r0
	add r0, r2, r1
	add r0, #0xf0
	lsl r0, r0, #0xc
	str r0, [r4, #0x1c]
	mov r0, #0
	str r0, [r4, #0x20]
	bl rand_LC
	ldr r1, _021D938C ; =0x00000667
	bl _s32_div_f
	ldr r0, _021D9390 ; =0x00000666
	add r0, r1, r0
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	str r0, [r4, #0x30]
	mov r0, #0
	str r0, [r4, #0x28]
	bl rand_LC
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	add r0, r0, #2
	lsl r0, r0, #0xc
	str r0, [r4, #0x2c]
	bl rand_LC
	mov r1, #0xc
	bl _s32_div_f
	add r0, r1, #4
	str r0, [r4, #0x34]
	mov r0, #1
	str r0, [r4]
_021D937A:
	add r7, r7, #1
	add r6, r6, #4
	cmp r7, #6
	bge _021D9384
	b _021D9282
_021D9384:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D9388: .word 0x021DACA8
_021D938C: .word 0x00000667
_021D9390: .word 0x00000666
	thumb_func_end MOD84_021D9278

	thumb_func_start MOD84_021D9394
MOD84_021D9394: ; 0x021D9394
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x4b
	mov r1, #0x10
	bl AllocFromHeap
	cmp r0, #0
	beq _021D93B0
	str r5, [r0]
	str r4, [r0, #4]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
_021D93B0:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9394

	thumb_func_start MOD84_021D93B4
MOD84_021D93B4: ; 0x021D93B4
	push {r3, lr}
	bl MOD84_021D9478
	cmp r0, #0
	beq _021D93C2
	mov r0, #1
	pop {r3, pc}
_021D93C2:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD84_021D93B4

	thumb_func_start MOD84_021D93C8
MOD84_021D93C8: ; 0x021D93C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D9544
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D93C8

	thumb_func_start MOD84_021D93DC
MOD84_021D93DC: ; 0x021D93DC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _021D946E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D93F4: ; jump table
	.short _021D93FC - _021D93F4 - 2 ; case 0
	.short _021D941E - _021D93F4 - 2 ; case 1
	.short _021D9430 - _021D93F4 - 2 ; case 2
	.short _021D9456 - _021D93F4 - 2 ; case 3
_021D93FC:
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r1, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x20
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D946E
_021D941E:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D946E
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D946E
_021D9430:
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	ldr r0, _021D9474 ; =0x0000032F
	cmp r1, r0
	blt _021D946E
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D946E
_021D9456:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D946E
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_021D946E:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D9474: .word 0x0000032F
	thumb_func_end MOD84_021D93DC

	thumb_func_start MOD84_021D9478
MOD84_021D9478: ; 0x021D9478
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021D9532
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9492: ; jump table
	.short _021D949A - _021D9492 - 2 ; case 0
	.short _021D94BA - _021D9492 - 2 ; case 1
	.short _021D94F2 - _021D9492 - 2 ; case 2
	.short _021D9512 - _021D9492 - 2 ; case 3
_021D949A:
	ldr r0, [r5, #4]
	ldr r2, _021D9540 ; =0x021DACD4
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	ldr r2, _021D9540 ; =0x021DACD4
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9538
_021D94BA:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x26
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x22
	mov r3, #6
	bl FUN_020068C8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9538
_021D94F2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x27
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9538
_021D9512:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x23
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9538
_021D9532:
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D9538:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D9540: .word 0x021DACD4
	thumb_func_end MOD84_021D9478

	thumb_func_start MOD84_021D9544
MOD84_021D9544: ; 0x021D9544
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9544

	thumb_func_start MOD84_021D955C
MOD84_021D955C: ; 0x021D955C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x4b
	mov r1, #0x6c
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D958E
	str r5, [r4]
	str r6, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x64]
	str r0, [r4, #0x68]
	add r0, r5, #0
	bl MOD84_021D82AC
	str r0, [r4, #0x4c]
	mov r0, #0
	str r0, [r4, #0x50]
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x48]
	str r0, [r4, #0x54]
	str r0, [r4, #0x5c]
_021D958E:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD84_021D955C

	thumb_func_start MOD84_021D9594
MOD84_021D9594: ; 0x021D9594
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D9804
	cmp r0, #0
	beq _021D95B4
	ldr r0, [r4, #0x4c]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r4, #0x4c]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #1
	pop {r4, pc}
_021D95B4:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD84_021D9594

	thumb_func_start MOD84_021D95B8
MOD84_021D95B8: ; 0x021D95B8
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D9A04
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D95B8

	thumb_func_start MOD84_021D95CC
MOD84_021D95CC: ; 0x021D95CC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, [r4, #0x54]
	add r5, r1, #0
	add r0, #0x80
	asr r6, r0, #0xc
	str r0, [r4, #0x54]
	ldr r0, [r4, #4]
	mov r1, #2
	mov r2, #0
	add r3, r6, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0
	add r3, r6, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	mov r1, #3
	mov r2, #0
	add r3, r6, #0
	bl FUN_020179E0
	ldr r0, [r4, #4]
	mov r1, #7
	mov r2, #0
	add r3, r6, #0
	bl FUN_020179E0
	ldr r0, [r4, #0x50]
	cmp r0, #0
	beq _021D9632
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0x10
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r6, #0
	str r0, [r2]
	ldr r0, [sp, #0x14]
	sub r0, #0x40
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x50]
	bl FUN_02020044
_021D9632:
	ldr r0, [r5]
	cmp r0, #7
	bhi _021D96D2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9644: ; jump table
	.short _021D9654 - _021D9644 - 2 ; case 0
	.short _021D966E - _021D9644 - 2 ; case 1
	.short _021D968E - _021D9644 - 2 ; case 2
	.short _021D96BE - _021D9644 - 2 ; case 3
	.short _021D9750 - _021D9644 - 2 ; case 4
	.short _021D9780 - _021D9644 - 2 ; case 5
	.short _021D97B0 - _021D9644 - 2 ; case 6
	.short _021D97D8 - _021D9644 - 2 ; case 7
_021D9654:
	mov r1, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x10
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D966E:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D96D2
	mov r1, #0
	ldr r0, _021D97F8 ; =0x04000050
	str r1, [sp]
	mov r2, #0xc
	mov r3, #0x10
	bl G2x_SetBlendAlpha_
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D968E:
	ldr r0, [r4, #0x64]
	add r1, r0, #1
	ldr r0, _021D97FC ; =0x00000172
	str r1, [r4, #0x64]
	cmp r1, r0
	blt _021D96D2
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #8]
	ldr r0, [r4]
	mov r1, #1
	mov r2, #0
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #0xc]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D96BE:
	ldr r0, [r4, #8]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D96D2
	ldr r0, [r4, #0xc]
	bl MOD84_021D81C4
	cmp r0, #0
	bne _021D96D4
_021D96D2:
	b _021D97F0
_021D96D4:
	ldr r0, [r4, #8]
	bl MOD84_021D81D4
	ldr r0, [r4, #0xc]
	bl MOD84_021D81D4
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x10
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x12
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x11
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x13
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [r4, #0x64]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D9750:
	ldr r0, [r4, #0x64]
	add r1, r0, #1
	ldr r0, _021D9800 ; =0x0000010E
	str r1, [r4, #0x64]
	cmp r1, r0
	blt _021D97F0
	ldr r0, [r4]
	mov r1, #0
	mov r2, #1
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #8]
	mov r1, #1
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #0xc]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D9780:
	ldr r0, [r4, #8]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D97F0
	ldr r0, [r4, #0xc]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D97F0
	ldr r0, [r4, #8]
	bl MOD84_021D81D4
	ldr r0, [r4, #0xc]
	bl MOD84_021D81D4
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x64]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D97B0:
	ldr r0, [r4, #0x64]
	add r1, r0, #1
	mov r0, #0x4b
	lsl r0, r0, #2
	str r1, [r4, #0x64]
	cmp r1, r0
	blt _021D97F0
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D97F0
_021D97D8:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D97F0
	ldr r0, [r4, #0x4c]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x1c
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D97F0:
	mov r0, #0
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_021D97F8: .word 0x04000050
_021D97FC: .word 0x00000172
_021D9800: .word 0x0000010E
	thumb_func_end MOD84_021D95CC

	thumb_func_start MOD84_021D9804
MOD84_021D9804: ; 0x021D9804
	push {r3, r4, r5, lr}
	sub sp, #0x38
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #8
	bls _021D9814
	b _021D99F0
_021D9814:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9820: ; jump table
	.short _021D9832 - _021D9820 - 2 ; case 0
	.short _021D986A - _021D9820 - 2 ; case 1
	.short _021D98A2 - _021D9820 - 2 ; case 2
	.short _021D98C2 - _021D9820 - 2 ; case 3
	.short _021D98E2 - _021D9820 - 2 ; case 4
	.short _021D991A - _021D9820 - 2 ; case 5
	.short _021D993A - _021D9820 - 2 ; case 6
	.short _021D995A - _021D9820 - 2 ; case 7
	.short _021D99E0 - _021D9820 - 2 ; case 8
_021D9832:
	ldr r0, [r4, #4]
	ldr r2, _021D99FC ; =0x021DACF0
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021D9A00 ; =0x021DAD0C
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021D99FC ; =0x021DACF0
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021D9A00 ; =0x021DAD0C
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D986A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #8
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0xa
	mov r3, #6
	bl FUN_020068C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D98A2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #9
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D98C2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0xb
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D98E2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0xc
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0xe
	mov r3, #7
	bl FUN_020068C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D991A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0xd
	mov r3, #3
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D993A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0xf
	mov r3, #7
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D995A:
	mov r0, #0x7f
	mov r1, #0x39
	mov r2, #0x3a
	bl MOD84_021D81DC
	str r0, [r4, #0x48]
	add r0, r4, #0
	add r0, #0x10
	bl FUN_020B1A24
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #0x10]
	mov r0, #0x7f
	mov r1, #0x3b
	add r3, r2, #0
	bl FUN_02006AE4
	add r0, r4, #0
	add r0, #0x34
	bl FUN_020B19DC
	mov r0, #0x4b
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x34
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r1, #0x3c
	mov r2, #1
	mov r3, #0
	bl FUN_02006A8C
	mov r0, #2
	str r0, [sp]
	add r2, r4, #0
	add r3, r4, #0
	ldr r1, [r4, #0x48]
	add r0, sp, #0x14
	add r2, #0x10
	add r3, #0x34
	bl MOD84_021D8240
	mov r0, #5
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x19
	ldr r0, [r4]
	add r1, sp, #0x14
	mov r2, #0
	lsl r3, r3, #4
	bl MOD84_021D8260
	str r0, [r4, #0x50]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D99E0:
	ldr r0, [r4]
	mov r1, #0
	bl MOD84_021D7DF4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D99F6
_021D99F0:
	add sp, #0x38
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D99F6:
	mov r0, #0
	add sp, #0x38
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D99FC: .word 0x021DACF0
_021D9A00: .word 0x021DAD0C
	thumb_func_end MOD84_021D9804

	thumb_func_start MOD84_021D9A04
MOD84_021D9A04: ; 0x021D9A04
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	cmp r0, #0
	beq _021D9A12
	bl FUN_0201FFC8
_021D9A12:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021D9A1C
	bl MOD84_021D81D4
_021D9A1C:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021D9A26
	bl MOD84_021D81D4
_021D9A26:
	ldr r0, [r4, #0x48]
	cmp r0, #0
	beq _021D9A30
	bl MOD84_021D821C
_021D9A30:
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9A04

	thumb_func_start MOD84_021D9A54
MOD84_021D9A54: ; 0x021D9A54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x4b
	mov r1, #0x10
	bl AllocFromHeap
	cmp r0, #0
	beq _021D9A70
	str r5, [r0]
	str r4, [r0, #4]
	mov r1, #0
	str r1, [r0, #8]
	str r1, [r0, #0xc]
_021D9A70:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9A54

	thumb_func_start MOD84_021D9A74
MOD84_021D9A74: ; 0x021D9A74
	push {r3, lr}
	bl MOD84_021D9B38
	cmp r0, #0
	beq _021D9A82
	mov r0, #1
	pop {r3, pc}
_021D9A82:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9A74

	thumb_func_start MOD84_021D9A88
MOD84_021D9A88: ; 0x021D9A88
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021D9C04
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9A88

	thumb_func_start MOD84_021D9A9C
MOD84_021D9A9C: ; 0x021D9A9C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #3
	bhi _021D9B2E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D9AB4: ; jump table
	.short _021D9ABC - _021D9AB4 - 2 ; case 0
	.short _021D9ADE - _021D9AB4 - 2 ; case 1
	.short _021D9AF0 - _021D9AB4 - 2 ; case 2
	.short _021D9B16 - _021D9AB4 - 2 ; case 3
_021D9ABC:
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r1, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x20
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9B2E
_021D9ADE:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D9B2E
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9B2E
_021D9AF0:
	ldr r1, [r0, #8]
	add r1, r1, #1
	str r1, [r0, #8]
	ldr r0, _021D9B34 ; =0x00000352
	cmp r1, r0
	blt _021D9B2E
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9B2E
_021D9B16:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D9B2E
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	add sp, #4
	mov r0, #1
	pop {r3, r4, pc}
_021D9B2E:
	mov r0, #0
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_021D9B34: .word 0x00000352
	thumb_func_end MOD84_021D9A9C

	thumb_func_start MOD84_021D9B38
MOD84_021D9B38: ; 0x021D9B38
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #3
	bhi _021D9BF2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9B52: ; jump table
	.short _021D9B5A - _021D9B52 - 2 ; case 0
	.short _021D9B7A - _021D9B52 - 2 ; case 1
	.short _021D9BB2 - _021D9B52 - 2 ; case 2
	.short _021D9BD2 - _021D9B52 - 2 ; case 3
_021D9B5A:
	ldr r0, [r5, #4]
	ldr r2, _021D9C00 ; =0x021DAD28
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	ldr r2, _021D9C00 ; =0x021DAD28
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9BF8
_021D9B7A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x28
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x22
	mov r3, #6
	bl FUN_020068C8
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9BF8
_021D9BB2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x29
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9BF8
_021D9BD2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7f
	mov r1, #0x23
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D9BF8
_021D9BF2:
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D9BF8:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D9C00: .word 0x021DAD28
	thumb_func_end MOD84_021D9B38

	thumb_func_start MOD84_021D9C04
MOD84_021D9C04: ; 0x021D9C04
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021D9C04

	thumb_func_start MOD84_021D9C1C
MOD84_021D9C1C: ; 0x021D9C1C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x4b
	mov r1, #0xf4
	bl AllocFromHeap
	add r4, r0, #0
	beq _021D9C7C
	str r5, [r4]
	str r6, [r4, #4]
	mov r1, #0
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xf0
	str r1, [r0]
	add r0, r5, #0
	bl MOD84_021D82AC
	str r0, [r4, #0x10]
	mov r0, #0
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x54]
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x60]
	add r2, r4, #0
	str r0, [r4, #0x64]
	mov r0, #0x7f
	mov r1, #0x41
	add r2, #0x5c
	mov r3, #0x4b
	bl FUN_02006C08
	str r0, [r4, #0x58]
	cmp r0, #0
	beq _021D9C76
	ldr r0, [r4, #0x5c]
	mov r1, #6
	ldr r0, [r0, #0xc]
	lsl r1, r1, #6
	bl DC_FlushRange
_021D9C76:
	add r0, r4, #0
	bl MOD84_021DA388
_021D9C7C:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD84_021D9C1C

	thumb_func_start MOD84_021D9C80
MOD84_021D9C80: ; 0x021D9C80
	push {r4, lr}
	add r4, r0, #0
	bl MOD84_021DA078
	cmp r0, #0
	beq _021D9CA0
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #1
	pop {r4, pc}
_021D9CA0:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD84_021D9C80

	thumb_func_start MOD84_021D9CA4
MOD84_021D9CA4: ; 0x021D9CA4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	add r0, r5, #0
	bl MOD84_021DA390
	add r0, r5, #0
	bl MOD84_021DA31C
	ldr r0, [r5, #0x58]
	cmp r0, #0
	beq _021D9CC4
	bl FreeToHeap
_021D9CC4:
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD84_021D9CA4

	thumb_func_start MOD84_021D9CD4
MOD84_021D9CD4: ; 0x021D9CD4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #0xe
	bls _021D9CE4
	b _021DA068
_021D9CE4:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D9CF0: ; jump table
	.short _021D9D0E - _021D9CF0 - 2 ; case 0
	.short _021D9D28 - _021D9CF0 - 2 ; case 1
	.short _021D9D48 - _021D9CF0 - 2 ; case 2
	.short _021D9D6A - _021D9CF0 - 2 ; case 3
	.short _021D9E00 - _021D9CF0 - 2 ; case 4
	.short _021D9E3C - _021D9CF0 - 2 ; case 5
	.short _021D9ECE - _021D9CF0 - 2 ; case 6
	.short _021D9F08 - _021D9CF0 - 2 ; case 7
	.short _021D9F3A - _021D9CF0 - 2 ; case 8
	.short _021D9F54 - _021D9CF0 - 2 ; case 9
	.short _021D9F78 - _021D9CF0 - 2 ; case 10
	.short _021D9F90 - _021D9CF0 - 2 ; case 11
	.short _021D9FBE - _021D9CF0 - 2 ; case 12
	.short _021DA02A - _021D9CF0 - 2 ; case 13
	.short _021DA058 - _021D9CF0 - 2 ; case 14
_021D9D0E:
	mov r1, #0
	mov r0, #3
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x20
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9D28:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021D9E16
	mov r1, #0
	ldr r0, _021DA070 ; =0x04000050
	str r1, [sp]
	mov r2, #0xc
	mov r3, #0xa
	bl G2x_SetBlendAlpha_
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9D48:
	add r1, r4, #0
	add r1, #0xec
	ldr r1, [r1]
	add r2, r1, #1
	add r1, r4, #0
	add r1, #0xec
	add r4, #0xec
	str r2, [r1]
	ldr r1, [r4]
	cmp r1, #0xf0
	blt _021D9E16
	bl MOD84_021DA3A0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9D6A:
	bl MOD84_021DA3C8
	cmp r0, #0
	beq _021D9E16
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021DA070 ; =0x04000050
	mov r1, #4
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021DA074 ; =0x04001050
	mov r1, #4
	mov r2, #8
	mov r3, #0
	bl G2x_SetBlendAlpha_
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x1c
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x18
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x1d
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x19
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9E00:
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0x96
	bgt _021D9E18
_021D9E16:
	b _021DA068
_021D9E18:
	ldr r0, [r4]
	mov r1, #0
	mov r2, #1
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #8]
	mov r1, #1
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #0xc]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9E3C:
	ldr r0, [r4, #8]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D9F44
	ldr r0, [r4, #0xc]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D9F44
	ldr r0, [r4, #8]
	bl MOD84_021D81D4
	ldr r0, [r4, #0xc]
	bl MOD84_021D81D4
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x20
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x1e
	mov r3, #7
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x21
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x1f
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9ECE:
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0xc8
	blt _021D9F44
	mov r1, #0
	ldr r0, [r4]
	add r2, r1, #0
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #8]
	ldr r0, [r4]
	mov r1, #1
	mov r2, #0
	mov r3, #0x5a
	bl MOD84_021D801C
	str r0, [r4, #0xc]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9F08:
	ldr r0, [r4, #8]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D9F44
	ldr r0, [r4, #0xc]
	bl MOD84_021D81C4
	cmp r0, #0
	beq _021D9F44
	ldr r0, [r4, #8]
	bl MOD84_021D81D4
	ldr r0, [r4, #0xc]
	bl MOD84_021D81D4
	mov r0, #0
	str r0, [r4, #8]
	str r0, [r4, #0xc]
	add r4, #0xec
	str r0, [r4]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9F3A:
	ldr r0, [r4]
	bl MOD84_021D82B4
	cmp r0, #0
	bne _021D9F46
_021D9F44:
	b _021DA068
_021D9F46:
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9F54:
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xec
	ldr r0, [r0]
	cmp r0, #0x5a
	blt _021DA068
	ldr r0, [r4]
	bl MOD84_021D8458
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9F78:
	ldr r0, [r4]
	bl MOD84_021D846C
	cmp r0, #0
	beq _021DA068
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9F90:
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xec
	add r4, #0xec
	str r1, [r0]
	ldr r0, [r4]
	cmp r0, #0x96
	blt _021DA068
	mov r0, #3
	str r0, [sp]
	mov r0, #0x20
	add r1, r0, #0
	sub r1, #0x30
	mov r2, #0
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021D9FBE:
	mov r0, #3
	bl FUN_0200A344
	cmp r0, #0
	beq _021DA068
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x2a
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x2b
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x4b
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r1, #0x2c
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0
	add r4, #0xec
	str r0, [r4]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021DA02A:
	add r0, #0xec
	ldr r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xec
	add r4, #0xec
	str r1, [r0]
	ldr r0, [r4]
	cmp r0, #0x2d
	blt _021DA068
	mov r1, #0
	mov r0, #1
	add r2, r1, #0
	str r0, [sp]
	mov r0, #0x10
	sub r2, #0x10
	mov r3, #0x1d
	bl FUN_0200A208
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA068
_021DA058:
	mov r0, #1
	bl FUN_0200A344
	cmp r0, #0
	beq _021DA068
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA068:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021DA070: .word 0x04000050
_021DA074: .word 0x04001050
	thumb_func_end MOD84_021D9CD4

	thumb_func_start MOD84_021DA078
MOD84_021DA078: ; 0x021DA078
	push {r3, r4, r5, lr}
	sub sp, #0x38
	add r5, r1, #0
	add r4, r0, #0
	ldr r0, [r5]
	cmp r0, #0xa
	bls _021DA088
	b _021DA2FE
_021DA088:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA094: ; jump table
	.short _021DA0AA - _021DA094 - 2 ; case 0
	.short _021DA0E2 - _021DA094 - 2 ; case 1
	.short _021DA11A - _021DA094 - 2 ; case 2
	.short _021DA13A - _021DA094 - 2 ; case 3
	.short _021DA15A - _021DA094 - 2 ; case 4
	.short _021DA192 - _021DA094 - 2 ; case 5
	.short _021DA1B2 - _021DA094 - 2 ; case 6
	.short _021DA1D2 - _021DA094 - 2 ; case 7
	.short _021DA1E2 - _021DA094 - 2 ; case 8
	.short _021DA238 - _021DA094 - 2 ; case 9
	.short _021DA2CE - _021DA094 - 2 ; case 10
_021DA0AA:
	ldr r0, [r4, #4]
	ldr r2, _021DA30C ; =0x021DAD68
	mov r1, #2
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021DA310 ; =0x021DAD4C
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021DA30C ; =0x021DAD68
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r4, #4]
	ldr r2, _021DA310 ; =0x021DAD4C
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA0E2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x16
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x1a
	mov r3, #6
	bl FUN_020068C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA11A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x17
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA13A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x1b
	mov r3, #6
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA15A:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x14
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x18
	mov r3, #7
	bl FUN_020068C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA192:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x15
	mov r3, #3
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA1B2:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7f
	mov r1, #0x19
	mov r3, #7
	bl FUN_0200687C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA1D2:
	ldr r0, [r4]
	mov r1, #2
	bl MOD84_021D7DF4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA1E2:
	mov r0, #0x7f
	mov r1, #0x3d
	mov r2, #0x3e
	bl MOD84_021D81DC
	str r0, [r4, #0x54]
	add r0, r4, #0
	add r0, #0x1c
	bl FUN_020B1A24
	add r0, r4, #0
	add r0, #0x40
	bl FUN_020B19DC
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x1c
	str r0, [sp, #0x10]
	mov r0, #0x7f
	mov r1, #0x3f
	add r3, r2, #0
	bl FUN_02006AE4
	mov r0, #0x4b
	str r0, [sp]
	add r4, #0x40
	str r4, [sp, #4]
	mov r0, #0x7f
	mov r1, #0x40
	mov r2, #1
	mov r3, #0
	bl FUN_02006A8C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA238:
	mov r2, #0
	str r2, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0x4b
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x1c
	str r0, [sp, #0x10]
	mov r0, #0x7f
	mov r1, #0x3f
	add r3, r2, #0
	bl FUN_02006AE4
	mov r0, #0x4b
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x40
	str r0, [sp, #4]
	mov r0, #0x7f
	mov r1, #0x40
	mov r2, #2
	mov r3, #0
	bl FUN_02006A8C
	mov r0, #2
	str r0, [sp]
	add r2, r4, #0
	add r3, r4, #0
	ldr r1, [r4, #0x54]
	add r0, sp, #0x14
	add r2, #0x1c
	add r3, #0x40
	bl MOD84_021D8240
	mov r0, #3
	str r0, [sp]
	mov r0, #1
	mov r2, #0
	str r0, [sp, #4]
	str r2, [sp, #8]
	ldr r0, [r4]
	add r1, sp, #0x14
	add r3, r2, #0
	bl MOD84_021D8260
	str r0, [r4, #0x14]
	mov r0, #4
	str r0, [sp]
	mov r0, #1
	mov r2, #0
	str r0, [sp, #4]
	str r2, [sp, #8]
	ldr r0, [r4]
	add r1, sp, #0x14
	add r3, r2, #0
	bl MOD84_021D8260
	str r0, [r4, #0x18]
	mov r1, #3
	bl FUN_02020238
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_02020398
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA2CE:
	ldr r0, [r4, #0x5c]
	mov r1, #4
	ldr r0, [r0, #0xc]
	mov r2, #3
	str r0, [sp]
	ldr r0, _021DA314 ; =0x021DAD48
	mov r3, #0
	bl MOD84_021DA58C
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x5c]
	mov r1, #4
	ldr r0, [r0, #0xc]
	mov r2, #5
	str r0, [sp]
	ldr r0, _021DA318 ; =0x021DAD44
	mov r3, #1
	bl MOD84_021DA58C
	str r0, [r4, #0x64]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021DA304
_021DA2FE:
	add sp, #0x38
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DA304:
	mov r0, #0
	add sp, #0x38
	pop {r3, r4, r5, pc}
	nop
_021DA30C: .word 0x021DAD68
_021DA310: .word 0x021DAD4C
_021DA314: .word 0x021DAD48
_021DA318: .word 0x021DAD44
	thumb_func_end MOD84_021DA078

	thumb_func_start MOD84_021DA31C
MOD84_021DA31C: ; 0x021DA31C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x60]
	cmp r0, #0
	beq _021DA32A
	bl MOD84_021DA5D8
_021DA32A:
	ldr r0, [r4, #0x64]
	cmp r0, #0
	beq _021DA334
	bl MOD84_021DA5D8
_021DA334:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021DA33E
	bl FUN_0201FFC8
_021DA33E:
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021DA348
	bl FUN_0201FFC8
_021DA348:
	ldr r0, [r4, #0x54]
	cmp r0, #0
	beq _021DA352
	bl MOD84_021D821C
_021DA352:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _021DA35C
	bl MOD84_021D81D4
_021DA35C:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DA366
	bl MOD84_021D81D4
_021DA366:
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #3
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD84_021DA31C

	thumb_func_start MOD84_021DA388
MOD84_021DA388: ; 0x021DA388
	mov r1, #0
	add r0, #0xe4
	str r1, [r0]
	bx lr
	thumb_func_end MOD84_021DA388

	thumb_func_start MOD84_021DA390
MOD84_021DA390: ; 0x021DA390
	push {r3, lr}
	add r0, #0xe4
	ldr r0, [r0]
	cmp r0, #0
	beq _021DA39E
	bl FUN_0200CAB4
_021DA39E:
	pop {r3, pc}
	thumb_func_end MOD84_021DA390

	thumb_func_start MOD84_021DA3A0
MOD84_021DA3A0: ; 0x021DA3A0
	push {r4, lr}
	add r4, r0, #0
	mov r2, #0
	add r4, #0x68
	str r2, [r0, #0x68]
	str r2, [r4, #4]
	str r2, [r4, #8]
	add r1, r4, #0
	str r2, [r4, #0x74]
	add r1, #0x80
	str r0, [r1]
	ldr r0, _021DA3C4 ; =MOD84_021DA3D8
	add r1, r4, #0
	bl FUN_0200CA60
	str r0, [r4, #0x7c]
	pop {r4, pc}
	nop
_021DA3C4: .word MOD84_021DA3D8
	thumb_func_end MOD84_021DA3A0

	thumb_func_start MOD84_021DA3C8
MOD84_021DA3C8: ; 0x021DA3C8
	add r0, #0xe4
	ldr r0, [r0]
	cmp r0, #0
	bne _021DA3D4
	mov r0, #1
	bx lr
_021DA3D4:
	mov r0, #0
	bx lr
	thumb_func_end MOD84_021DA3C8

	thumb_func_start MOD84_021DA3D8
MOD84_021DA3D8: ; 0x021DA3D8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, #0x80
	ldr r5, [r1]
	ldr r1, [r4]
	cmp r1, #3
	bls _021DA3EA
	b _021DA56C
_021DA3EA:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021DA3F6: ; jump table
	.short _021DA3FE - _021DA3F6 - 2 ; case 0
	.short _021DA4B8 - _021DA3F6 - 2 ; case 1
	.short _021DA50A - _021DA3F6 - 2 ; case 2
	.short _021DA544 - _021DA3F6 - 2 ; case 3
_021DA3FE:
	ldr r2, [r4, #4]
	mov r0, #0x18
	add r1, r2, #0
	ldr r2, _021DA570 ; =0x021DAD84
	mul r1, r0
	ldr r2, [r2, r1]
	ldr r3, _021DA574 ; =0x021DAD88
	lsl r2, r2, #0xc
	ldr r1, [r3, r1]
	str r2, [r4, #0x14]
	lsl r6, r1, #0xc
	str r6, [r4, #0x18]
	mov r1, #0
	str r1, [r4, #0x1c]
	ldr r3, [r4, #4]
	add r1, r3, #0
	ldr r3, _021DA578 ; =0x021DAD94
	mul r1, r0
	ldr r1, [r3, r1]
	str r1, [r4, #0xc]
	ldr r3, [r4, #4]
	add r1, r3, #0
	ldr r3, _021DA57C ; =0x021DAD98
	mul r1, r0
	ldr r1, [r3, r1]
	str r1, [r4, #0x10]
	ldr r1, [r4, #4]
	add r3, r1, #0
	mul r3, r0
	ldr r0, _021DA580 ; =0x021DAD8C
	ldr r1, [r4, #0xc]
	ldr r0, [r0, r3]
	lsl r0, r0, #0xc
	sub r0, r0, r2
	bl _s32_div_f
	str r0, [r4, #0x20]
	ldr r1, [r4, #4]
	mov r0, #0x18
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021DA584 ; =0x021DAD90
	ldr r1, [r4, #0xc]
	ldr r0, [r0, r2]
	lsl r0, r0, #0xc
	sub r0, r0, r6
	bl _s32_div_f
	str r0, [r4, #0x24]
	mov r0, #0
	str r0, [r4, #0x28]
	add r1, r4, #0
	ldr r0, [r5, #0x14]
	add r1, #0x14
	bl FUN_02020044
	ldr r0, [r5, #0x14]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r5, #0x14]
	mov r1, #1
	bl FUN_02020130
	add r0, r4, #0
	add r0, #0x20
	add r1, sp, #0
	bl VEC_Normalize
	add r2, r4, #0
	add r3, r4, #0
	ldr r0, _021DA588 ; =0xFFFD8000
	add r1, sp, #0
	add r2, #0x14
	add r3, #0x2c
	bl VEC_MultAdd
	add r1, r4, #0
	ldr r0, [r5, #0x18]
	add r1, #0x2c
	bl FUN_02020044
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0
	str r0, [r4, #0x74]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021DA4B8:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DA4F8
	add r0, r4, #0
	add r0, #0x14
	add r1, r4, #0
	add r1, #0x20
	add r2, r0, #0
	bl VEC_Add
	add r0, r4, #0
	add r0, #0x2c
	add r1, r4, #0
	add r1, #0x20
	add r2, r0, #0
	bl VEC_Add
	add r1, r4, #0
	ldr r0, [r5, #0x14]
	add r1, #0x14
	bl FUN_02020044
	add r1, r4, #0
	ldr r0, [r5, #0x18]
	add r1, #0x2c
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	add sp, #0xc
	sub r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, pc}
_021DA4F8:
	mov r0, #0x14
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x14]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
_021DA50A:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DA532
	add r0, r4, #0
	add r0, #0x2c
	add r1, r4, #0
	add r1, #0x20
	add r2, r0, #0
	bl VEC_Add
	add r1, r4, #0
	ldr r0, [r5, #0x18]
	add r1, #0x2c
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	add sp, #0xc
	sub r0, r0, #1
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, pc}
_021DA532:
	ldr r0, [r5, #0x18]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021DA544:
	ldr r1, [r4, #0x10]
	cmp r1, #0
	beq _021DA552
	sub r0, r1, #1
	add sp, #0xc
	str r0, [r4, #0x10]
	pop {r3, r4, r5, r6, pc}
_021DA552:
	ldr r1, [r4, #4]
	add r1, r1, #1
	str r1, [r4, #4]
	cmp r1, #4
	bhs _021DA564
	mov r0, #0
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021DA564:
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x7c]
_021DA56C:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021DA570: .word 0x021DAD84
_021DA574: .word 0x021DAD88
_021DA578: .word 0x021DAD94
_021DA57C: .word 0x021DAD98
_021DA580: .word 0x021DAD8C
_021DA584: .word 0x021DAD90
_021DA588: .word 0xFFFD8000
	thumb_func_end MOD84_021DA3D8

	thumb_func_start MOD84_021DA58C
MOD84_021DA58C: ; 0x021DA58C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x4b
	mov r1, #0x1c
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _021DA5CE
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #8]
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	str r0, [r4, #0x18]
	str r5, [r4, #0x14]
	str r6, [r4, #0xc]
	ldr r0, [sp]
	str r7, [r4, #4]
	str r0, [r4, #0x10]
	ldr r0, _021DA5D4 ; =MOD84_021DA5F0
	mov r2, #2
	bl FUN_0200CA98
	add r5, r0, #0
	bne _021DA5CA
	add r0, r4, #0
	bl FreeToHeap
_021DA5CA:
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_021DA5CE:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DA5D4: .word MOD84_021DA5F0
	thumb_func_end MOD84_021DA58C

	thumb_func_start MOD84_021DA5D8
MOD84_021DA5D8: ; 0x021DA5D8
	push {r4, lr}
	add r4, r0, #0
	beq _021DA5EC
	bl FUN_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
_021DA5EC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021DA5D8

	thumb_func_start MOD84_021DA5F0
MOD84_021DA5F0: ; 0x021DA5F0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	add r1, r0, #1
	str r1, [r4]
	ldr r0, [r4, #4]
	cmp r1, r0
	ble _021DA644
	ldr r1, [r4, #0x14]
	ldr r0, [r4, #8]
	ldrb r0, [r1, r0]
	ldr r1, [r4, #0x18]
	sub r0, r0, #4
	lsl r2, r0, #4
	ldr r0, [r4, #0x10]
	cmp r0, #0
	bne _021DA622
	lsl r0, r2, #1
	add r0, r1, r0
	mov r1, #5
	lsl r1, r1, #6
	mov r2, #0x20
	bl GX_LoadBGPltt
	b _021DA630
_021DA622:
	lsl r0, r2, #1
	add r0, r1, r0
	mov r1, #6
	lsl r1, r1, #6
	mov r2, #0x20
	bl GXS_LoadBGPltt
_021DA630:
	ldr r0, [r4, #8]
	add r1, r0, #1
	str r1, [r4, #8]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	blt _021DA640
	mov r0, #0
	str r0, [r4, #8]
_021DA640:
	mov r0, #0
	str r0, [r4]
_021DA644:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD84_021DA5F0

	.section .rodata
	; 0x021DA648
	.byte 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x30, 0x00, 0x2D, 0x00, 0x2E, 0x00
	.byte 0x33, 0x00, 0x34, 0x00, 0x31, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1F, 0x06, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x75, 0x88, 0x1D, 0x02
	.byte 0xA5, 0x88, 0x1D, 0x02, 0xDD, 0x88, 0x1D, 0x02, 0xC9, 0x88, 0x1D, 0x02, 0x8D, 0x8A, 0x1D, 0x02
	.byte 0xAD, 0x8A, 0x1D, 0x02, 0xD5, 0x8A, 0x1D, 0x02, 0xC1, 0x8A, 0x1D, 0x02, 0x55, 0x8C, 0x1D, 0x02
	.byte 0xD9, 0x8C, 0x1D, 0x02, 0x0D, 0x8D, 0x1D, 0x02, 0xED, 0x8C, 0x1D, 0x02, 0x95, 0x93, 0x1D, 0x02
	.byte 0xB5, 0x93, 0x1D, 0x02, 0xDD, 0x93, 0x1D, 0x02, 0xC9, 0x93, 0x1D, 0x02, 0x5D, 0x95, 0x1D, 0x02
	.byte 0x95, 0x95, 0x1D, 0x02, 0xCD, 0x95, 0x1D, 0x02, 0xB9, 0x95, 0x1D, 0x02, 0x55, 0x9A, 0x1D, 0x02
	.byte 0x75, 0x9A, 0x1D, 0x02, 0x9D, 0x9A, 0x1D, 0x02, 0x89, 0x9A, 0x1D, 0x02, 0x1D, 0x9C, 0x1D, 0x02
	.byte 0x81, 0x9C, 0x1D, 0x02, 0xD5, 0x9C, 0x1D, 0x02, 0xA5, 0x9C, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x02, 0x00, 0x10, 0x00, 0x01, 0x00, 0x03, 0x00, 0xC2, 0x00, 0x00, 0x00, 0x04, 0x00
	.byte 0xD7, 0x00, 0x00, 0x00, 0x05, 0x00, 0x89, 0x01, 0x00, 0x00, 0x06, 0x00, 0x9E, 0x01, 0x00, 0x00
	.byte 0x07, 0x00, 0x50, 0x02, 0x00, 0x00, 0x08, 0x00, 0x65, 0x02, 0x00, 0x00, 0x09, 0x00, 0x17, 0x03
	.byte 0x00, 0x00, 0x0A, 0x00, 0x2C, 0x03, 0x00, 0x00, 0x0B, 0x00, 0x64, 0x03, 0x00, 0x00, 0x0C, 0x00
	.byte 0x79, 0x03, 0x00, 0x00, 0x0D, 0x00, 0xB1, 0x03, 0x00, 0x00, 0x0E, 0x00, 0xC6, 0x03, 0x00, 0x00
	.byte 0x0F, 0x00, 0xFE, 0x03, 0x00, 0x00, 0x10, 0x00, 0x13, 0x04, 0x00, 0x00, 0x11, 0x00, 0x4B, 0x04
	.byte 0x00, 0x00, 0x12, 0x00, 0x60, 0x04, 0x00, 0x00, 0x13, 0x00, 0x75, 0x04, 0x00, 0x00, 0x14, 0x00
	.byte 0x8A, 0x04, 0x00, 0x00, 0x15, 0x00, 0x9F, 0x04, 0x00, 0x00, 0x16, 0x00, 0xB4, 0x04, 0x00, 0x00
	.byte 0x17, 0x00, 0xC9, 0x04, 0x00, 0x00, 0x18, 0x00, 0xDE, 0x04, 0x00, 0x00, 0x19, 0x00, 0xF3, 0x04
	.byte 0x00, 0x00, 0x1A, 0x00, 0x08, 0x05, 0x00, 0x00, 0x1B, 0x00, 0x1D, 0x05, 0x00, 0x00, 0x1C, 0x00
	.byte 0x32, 0x05, 0x00, 0x00, 0x1D, 0x00, 0x47, 0x05, 0x00, 0x00, 0x1E, 0x00, 0xF9, 0x05, 0x00, 0x00
	.byte 0x1F, 0x00, 0x0E, 0x06, 0x00, 0x00, 0x20, 0x00, 0x46, 0x06, 0x00, 0x00, 0x21, 0x00, 0x56, 0x06
	.byte 0x00, 0x00, 0x22, 0x00, 0x66, 0x06, 0x00, 0x00, 0x23, 0x00, 0x7B, 0x06, 0x00, 0x00, 0x24, 0x00
	.byte 0x90, 0x06, 0x00, 0x00, 0x25, 0x00, 0xA5, 0x06, 0x00, 0x00, 0x26, 0x00, 0xBA, 0x06, 0x00, 0x00
	.byte 0x27, 0x00, 0xCF, 0x06, 0x00, 0x00, 0x28, 0x00, 0xE4, 0x06, 0x00, 0x00, 0x29, 0x00, 0xF9, 0x06
	.byte 0x00, 0x00, 0x2A, 0x00, 0x0E, 0x07, 0x00, 0x00, 0x2B, 0x00, 0x23, 0x07, 0x00, 0x00, 0x2C, 0x00
	.byte 0x38, 0x07, 0x00, 0x00, 0x2D, 0x00, 0x4D, 0x07, 0x00, 0x00, 0x2E, 0x00, 0x62, 0x07, 0x00, 0x00
	.byte 0x2F, 0x00, 0x9A, 0x07, 0x00, 0x00, 0x30, 0x00, 0xAF, 0x07, 0x00, 0x00, 0x31, 0x00, 0xE7, 0x07
	.byte 0x00, 0x00, 0x32, 0x00, 0xFC, 0x07, 0x00, 0x00, 0x33, 0x00, 0xAE, 0x08, 0x00, 0x00, 0x34, 0x00
	.byte 0xC3, 0x08, 0x00, 0x00, 0x35, 0x00, 0xFB, 0x08, 0x00, 0x00, 0x36, 0x00, 0x10, 0x09, 0x00, 0x00
	.byte 0x37, 0x00, 0x25, 0x09, 0x00, 0x00, 0x38, 0x00, 0x5D, 0x09, 0x00, 0x00, 0x39, 0x00, 0x72, 0x09
	.byte 0x00, 0x00, 0x3A, 0x00, 0xAA, 0x09, 0x00, 0x00, 0x3B, 0x00, 0xBF, 0x09, 0x00, 0x00, 0x3C, 0x00
	.byte 0x71, 0x0A, 0x00, 0x00, 0x3D, 0x00, 0x86, 0x0A, 0x00, 0x00, 0x3E, 0x00, 0xBE, 0x0A, 0x00, 0x00
	.byte 0x3F, 0x00, 0xD3, 0x0A, 0x00, 0x00, 0x40, 0x00, 0xE8, 0x0A, 0x00, 0x00, 0x41, 0x00, 0xFD, 0x0A
	.byte 0x00, 0x00, 0x42, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x43, 0x00, 0x27, 0x0B, 0x00, 0x00, 0x44, 0x00
	.byte 0x3C, 0x0B, 0x00, 0x00, 0x45, 0x00, 0x51, 0x0B, 0x00, 0x00, 0x46, 0x00, 0x66, 0x0B, 0x00, 0x00
	.byte 0x47, 0x00, 0x7B, 0x0B, 0x00, 0x00, 0x48, 0x00, 0x90, 0x0B, 0x00, 0x00, 0x49, 0x00, 0xC8, 0x0B
	.byte 0x00, 0x00, 0x4A, 0x00, 0xDD, 0x0B, 0x00, 0x00, 0x4B, 0x00, 0xF2, 0x0B, 0x00, 0x00, 0x4C, 0x00
	.byte 0x07, 0x0C, 0x00, 0x00, 0x4D, 0x00, 0x1C, 0x0C, 0x00, 0x00, 0x4E, 0x00, 0x54, 0x0C, 0x00, 0x00
	.byte 0x4F, 0x00, 0x69, 0x0C, 0x00, 0x00, 0x50, 0x00, 0x7E, 0x0C, 0x00, 0x00, 0x51, 0x00, 0x93, 0x0C
	.byte 0x00, 0x00, 0x52, 0x00, 0xA8, 0x0C, 0x00, 0x00, 0x53, 0x00, 0xE0, 0x0C, 0x00, 0x00, 0x54, 0x00
	.byte 0xF5, 0x0C, 0x00, 0x00, 0x55, 0x00, 0x0A, 0x0D, 0x00, 0x00, 0x56, 0x00, 0x1F, 0x0D, 0x00, 0x00
	.byte 0x57, 0x00, 0x34, 0x0D, 0x00, 0x00, 0x58, 0x00, 0x49, 0x0D, 0x00, 0x00, 0x59, 0x00, 0x5E, 0x0D
	.byte 0x00, 0x00, 0x5A, 0x00, 0x73, 0x0D, 0x00, 0x00, 0x5B, 0x00, 0xAB, 0x0D, 0x00, 0x00, 0x5C, 0x00
	.byte 0xC0, 0x0D, 0x00, 0x00, 0x5D, 0x00, 0xF8, 0x0D, 0x00, 0x00, 0x5E, 0x00, 0x0D, 0x0E, 0x00, 0x00
	.byte 0x5F, 0x00, 0x22, 0x0E, 0x00, 0x00, 0x60, 0x00, 0x37, 0x0E, 0x00, 0x00, 0x61, 0x00, 0x4C, 0x0E
	.byte 0x00, 0x00, 0x62, 0x00, 0x84, 0x0E, 0x00, 0x00, 0x63, 0x00, 0x99, 0x0E, 0x00, 0x00, 0x64, 0x00
	.byte 0xAE, 0x0E, 0x00, 0x00, 0x65, 0x00, 0xC3, 0x0E, 0x00, 0x00, 0x66, 0x00, 0xD8, 0x0E, 0x00, 0x00
	.byte 0x67, 0x00, 0xED, 0x0E, 0x00, 0x00, 0x68, 0x00, 0x02, 0x0F, 0x00, 0x00, 0x69, 0x00, 0x17, 0x0F
	.byte 0x00, 0x00, 0x6A, 0x00, 0x2C, 0x0F, 0x00, 0x00, 0x6B, 0x00, 0xDE, 0x0F, 0x00, 0x00, 0x6C, 0x00
	.byte 0xF3, 0x0F, 0x00, 0x00, 0x6D, 0x00, 0x08, 0x10, 0x00, 0x00, 0x6E, 0x00, 0x1D, 0x10, 0x00, 0x00
	.byte 0x6F, 0x00, 0x32, 0x10, 0x00, 0x00, 0x70, 0x00, 0x6A, 0x10, 0x00, 0x00, 0x71, 0x00, 0x7F, 0x10
	.byte 0x00, 0x00, 0x72, 0x00, 0x94, 0x10, 0x00, 0x00, 0x73, 0x00, 0xA9, 0x10, 0x00, 0x00, 0x74, 0x00
	.byte 0xBE, 0x10, 0x00, 0x00, 0x75, 0x00, 0xD3, 0x10, 0x00, 0x00, 0x76, 0x00, 0x0B, 0x11, 0x00, 0x00
	.byte 0x77, 0x00, 0x2B, 0x11, 0x00, 0x00, 0x78, 0x00, 0x40, 0x11, 0x00, 0x00, 0x79, 0x00, 0x60, 0x11
	.byte 0x00, 0x00, 0x7A, 0x00, 0x75, 0x11, 0x00, 0x00, 0x7B, 0x00, 0x8A, 0x11, 0x00, 0x00, 0x7C, 0x00
	.byte 0x9F, 0x11, 0x00, 0x00, 0x7D, 0x00, 0xBF, 0x11, 0x00, 0x00, 0x7E, 0x00, 0xD4, 0x11, 0x00, 0x00
	.byte 0x7F, 0x00, 0x0C, 0x12, 0x00, 0x00, 0x80, 0x00, 0x21, 0x12, 0x00, 0x00, 0x81, 0x00, 0x36, 0x12
	.byte 0x00, 0x00, 0x82, 0x00, 0xE8, 0x12, 0x00, 0x00, 0x83, 0x00, 0xFD, 0x12, 0x00, 0x00, 0x84, 0x00
	.byte 0x12, 0x13, 0x00, 0x00, 0x85, 0x00, 0x27, 0x13, 0x00, 0x00, 0x86, 0x00, 0x3C, 0x13, 0x00, 0x00
	.byte 0x87, 0x00, 0x51, 0x13, 0x00, 0x00, 0x88, 0x00, 0x66, 0x13, 0x00, 0x00, 0x89, 0x00, 0x7B, 0x13
	.byte 0x00, 0x00, 0x8A, 0x00, 0x90, 0x13, 0x00, 0x00, 0x8B, 0x00, 0xA5, 0x13, 0x00, 0x00, 0x8C, 0x00
	.byte 0xBA, 0x13, 0x00, 0x00, 0x8D, 0x00, 0xCF, 0x13, 0x00, 0x00, 0x8E, 0x00, 0xE4, 0x13, 0x00, 0x00
	.byte 0x8F, 0x00, 0xF9, 0x13, 0x00, 0x00, 0x90, 0x00, 0x0E, 0x14, 0x00, 0x00, 0x91, 0x00, 0x23, 0x14
	.byte 0x00, 0x00, 0x92, 0x00, 0x38, 0x14, 0x00, 0x00, 0x93, 0x00, 0x4D, 0x14, 0x00, 0x00, 0x94, 0x00
	.byte 0x62, 0x14, 0x00, 0x00, 0x95, 0x00, 0x77, 0x14, 0x00, 0x00, 0x96, 0x00, 0x8C, 0x14, 0x00, 0x00
	.byte 0x97, 0x00, 0xA1, 0x14, 0x00, 0x00, 0x98, 0x00, 0xB6, 0x14, 0x00, 0x00, 0x99, 0x00, 0xCB, 0x14
	.byte 0x00, 0x00, 0x9A, 0x00, 0xE0, 0x14, 0x00, 0x00, 0x9B, 0x00, 0xF5, 0x14, 0x00, 0x00, 0x9C, 0x00
	.byte 0x0A, 0x15, 0x00, 0x00, 0x9D, 0x00, 0x1F, 0x15, 0x00, 0x00, 0x9E, 0x00, 0x34, 0x15, 0x00, 0x00
	.byte 0x9F, 0x00, 0xE6, 0x15, 0x00, 0x00, 0xA0, 0x00, 0xFB, 0x15, 0x00, 0x00, 0xA1, 0x00, 0x10, 0x16
	.byte 0x00, 0x00, 0xA2, 0x00, 0x25, 0x16, 0x00, 0x00, 0xA3, 0x00, 0x5D, 0x16, 0x00, 0x00, 0xA4, 0x00
	.byte 0x72, 0x16, 0x00, 0x00, 0xA5, 0x00, 0x87, 0x16, 0x00, 0x00, 0xA6, 0x00, 0x9C, 0x16, 0x00, 0x00
	.byte 0xA7, 0x00, 0xD4, 0x16, 0x00, 0x00, 0xA8, 0x00, 0xE9, 0x16, 0x00, 0x00, 0xA9, 0x00, 0xFE, 0x16
	.byte 0x00, 0x00, 0xAA, 0x00, 0x13, 0x17, 0x00, 0x00, 0xAB, 0x00, 0xC5, 0x17, 0x00, 0x00, 0xAC, 0x00
	.byte 0xDA, 0x17, 0x00, 0x00, 0xAD, 0x00, 0xEF, 0x17, 0x00, 0x00, 0xAE, 0x00, 0x27, 0x18, 0x00, 0x00
	.byte 0xAF, 0x00, 0x3C, 0x18, 0x00, 0x00, 0xB0, 0x00, 0x74, 0x18, 0x00, 0x00, 0xB1, 0x00, 0x89, 0x18
	.byte 0x00, 0x00, 0xB2, 0x00, 0xC1, 0x18, 0x00, 0x00, 0xB3, 0x00, 0xD6, 0x18, 0x00, 0x00, 0xB4, 0x00
	.byte 0xEB, 0x18, 0x00, 0x00, 0xB5, 0x00, 0x23, 0x19, 0x00, 0x00, 0xB6, 0x00, 0x38, 0x19, 0x00, 0x00
	.byte 0xB7, 0x00, 0x4D, 0x19, 0x00, 0x00, 0xB8, 0x00, 0x62, 0x19, 0x00, 0x00, 0xB9, 0x00, 0x77, 0x19
	.byte 0x00, 0x00, 0xBA, 0x00, 0xAF, 0x19, 0x00, 0x00, 0xBB, 0x00, 0xC4, 0x19, 0x00, 0x00, 0xBC, 0x00
	.byte 0xD9, 0x19, 0x00, 0x00, 0xBD, 0x00, 0xEE, 0x19, 0x00, 0x00, 0xBE, 0x00, 0x03, 0x1A, 0x00, 0x00
	.byte 0xBF, 0x00, 0x18, 0x1A, 0x00, 0x00, 0xC0, 0x00, 0x50, 0x1A, 0x00, 0x00, 0xC1, 0x00, 0x65, 0x1A
	.byte 0x00, 0x00, 0xC2, 0x00, 0x7A, 0x1A, 0x00, 0x00, 0xC3, 0x00, 0x8F, 0x1A, 0x00, 0x00, 0xC4, 0x00
	.byte 0xA4, 0x1A, 0x00, 0x00, 0xC5, 0x00, 0xB9, 0x1A, 0x00, 0x00, 0xC6, 0x00, 0xCE, 0x1A, 0x00, 0x00
	.byte 0xC7, 0x00, 0xE3, 0x1A, 0x00, 0x00, 0xC8, 0x00, 0xF8, 0x1A, 0x00, 0x00, 0xC9, 0x00, 0x0D, 0x1B
	.byte 0x00, 0x00, 0xCA, 0x00, 0x22, 0x1B, 0x00, 0x00, 0xCB, 0x00, 0x37, 0x1B, 0x00, 0x00, 0xCC, 0x00
	.byte 0x4C, 0x1B, 0x00, 0x00, 0xCD, 0x00, 0x61, 0x1B, 0x00, 0x00, 0xCE, 0x00, 0x13, 0x1C, 0x00, 0x00
	.byte 0xCF, 0x00, 0x28, 0x1C, 0x00, 0x00, 0xD0, 0x00, 0x3D, 0x1C, 0x00, 0x00, 0xD1, 0x00, 0x52, 0x1C
	.byte 0x00, 0x00, 0xD2, 0x00, 0x67, 0x1C, 0x00, 0x00, 0xD3, 0x00, 0x19, 0x1D, 0x00, 0x00, 0xD4, 0x00
	.byte 0x2E, 0x1D, 0x00, 0x00, 0xD5, 0x00, 0x43, 0x1D, 0x00, 0x00, 0xD6, 0x00, 0x58, 0x1D, 0x00, 0x00
	.byte 0xD7, 0x00, 0x68, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1B, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x05, 0x06, 0x05
	.byte 0x09, 0x08, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA7, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xC5, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00
	.byte 0x5A, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00
	.byte 0x81, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00
	.byte 0x28, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x34, 0x01, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00
	.byte 0x78, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00
	.byte 0x55, 0x01, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00
