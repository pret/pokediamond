	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD04_021D868C
MOD04_021D868C: ; 0x021D868C
	push {r3, r4, r5, lr}
	bl MIC_Init
	bl PM_Init
	mov r0, #1
	bl PM_SetAmp
	mov r0, #3
	bl PM_SetAmpGain
	ldr r0, _021D8718 ; =UNK04_0220FBC8
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r3, _021D871C ; =0x00003584
	add r5, r2, #0
	str r2, [r1, r3]
	add r1, r3, #0
	ldr r4, [r0, #4]
	add r1, #0xc
	str r2, [r4, r1]
	ldr r4, [r0, #4]
	add r1, r3, #4
	str r2, [r4, r1]
	add r1, r3, #0
	ldr r4, [r0, #4]
	add r1, #8
	str r2, [r4, r1]
	ldr r1, [r0, #4]
	add r3, #0x10
	str r2, [r1, r3]
	ldr r3, _021D8720 ; =0x00003598
	add r1, r2, #0
_021D86CE:
	ldr r4, [r0, #4]
	add r2, r2, #1
	add r4, r4, r5
	add r5, r5, #2
	strh r1, [r4, r3]
	cmp r2, #0x10
	blt _021D86CE
	ldr r0, _021D8718 ; =UNK04_0220FBC8
	ldr r2, [r0, #4]
	ldr r0, _021D8724 ; =0x000035B8
	str r1, [r2, r0]
	mov r0, #1
	bl FUN_020AA770
	bl NNS_SndInit
	ldr r0, _021D8718 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D8728 ; =0x00003504
	add r0, r1, r0
	bl NNS_SndStrmInit
	ldr r1, _021D8718 ; =UNK04_0220FBC8
	mov r0, #0
	ldr r2, [r1, #4]
	mov r1, #0xb1
	lsl r1, r1, #6
	add r1, r2, r1
	mov r2, #0x22
	lsl r2, r2, #6
	bl MIi_CpuClearFast
	ldr r0, _021D8718 ; =UNK04_0220FBC8
	mov r1, #0
	str r1, [r0, #8]
	pop {r3, r4, r5, pc}
	nop
_021D8718: .word UNK04_0220FBC8
_021D871C: .word 0x00003584
_021D8720: .word 0x00003598
_021D8724: .word 0x000035B8
_021D8728: .word 0x00003504

	thumb_func_start MOD04_021D872C
MOD04_021D872C: ; 0x021D872C
	bx lr
	.align 2, 0

	thumb_func_start MOD04_021D8730
MOD04_021D8730: ; 0x021D8730
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r3, #0
	ldr r4, [sp, #0x14]
	cmp r0, #0
	bne _021D8748
	ldr r0, [r6]
	mov r1, #0
	add r2, r5, #0
	bl MI_CpuFill8
	pop {r4, r5, r6, pc}
_021D8748:
	ldr r0, _021D87B8 ; =UNK04_0220FBC8
	ldr r2, [r0, #4]
	ldr r0, _021D87BC ; =0x00003565
	ldrb r1, [r2, r0]
	cmp r1, #0
	beq _021D876A
	add r0, r0, #3
	add r0, r2, r0
	ldr r1, _021D87C0 ; =MOD04_021D872C
	mov r2, #0
	bl MIC_StartAutoSamplingAsync
	ldr r0, _021D87B8 ; =UNK04_0220FBC8
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _021D87BC ; =0x00003565
	strb r2, [r1, r0]
_021D876A:
	bl MIC_GetLastSamplingAddress
	sub r0, r0, r4
	cmp r0, r5
	bhs _021D8776
	add r4, r4, r5
_021D8776:
	ldr r0, _021D87C4 ; =0x027FFFA8
	ldrh r1, [r0]
	mov r0, #2
	lsl r0, r0, #0xe
	and r0, r1
	asr r0, r0, #0xf
	beq _021D878E
	ldr r0, _021D87B8 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	mov r0, #0xb1
	lsl r0, r0, #6
	add r4, r1, r0
_021D878E:
	ldr r0, _021D87B8 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D87C8 ; =0x000034FC
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _021D87A2
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_020AABDC
_021D87A2:
	ldr r0, [r6]
	add r1, r5, #0
	mov r2, #0
	bl FUN_020AA824
	ldr r0, _021D87B8 ; =UNK04_0220FBC8
	mov r2, #2
	ldr r1, [r0, #4]
	ldr r0, _021D87CC ; =0x00003564
	strb r2, [r1, r0]
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D87B8: .word UNK04_0220FBC8
_021D87BC: .word 0x00003565
_021D87C0: .word MOD04_021D872C
_021D87C4: .word 0x027FFFA8
_021D87C8: .word 0x000034FC
_021D87CC: .word 0x00003564

	thumb_func_start MOD04_021D87D0
MOD04_021D87D0: ; 0x021D87D0
	push {r4, lr}
	ldr r1, _021D8810 ; =UNK04_0220FBC8
	ldr r2, [r1, #4]
	ldr r1, _021D8814 ; =0x00003560
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _021D880A
	bl FUN_020ACD54
	add r4, r0, #0
	bne _021D87EA
	mov r0, #0
	pop {r4, pc}
_021D87EA:
	mov r1, #0
	bl FUN_020ACBA0
	cmp r0, #0
	beq _021D87FE
	add r0, r4, #0
	bl FUN_020ACC84
	mov r0, #0
	pop {r4, pc}
_021D87FE:
	ldr r0, _021D8810 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D8814 ; =0x00003560
	str r4, [r1, r0]
	mov r0, #1
	pop {r4, pc}
_021D880A:
	mov r0, #0
	pop {r4, pc}
	nop
_021D8810: .word UNK04_0220FBC8
_021D8814: .word 0x00003560

	thumb_func_start MOD04_021D8818
MOD04_021D8818: ; 0x021D8818
	push {r3, lr}
	ldr r0, _021D8858 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D885C ; =0x00003560
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021D8852
	ldr r1, [r0, #0xc]
	cmp r1, #4
	bne _021D8852
	mov r1, #0
	bl FUN_020ACAB0
	cmp r0, #0
	beq _021D883A
	mov r0, #0
	pop {r3, pc}
_021D883A:
	ldr r0, _021D8858 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D885C ; =0x00003560
	ldr r0, [r1, r0]
	bl FUN_020AADCC
	cmp r0, #0
	beq _021D884E
	mov r0, #1
	pop {r3, pc}
_021D884E:
	mov r0, #0
	pop {r3, pc}
_021D8852:
	mov r0, #0
	pop {r3, pc}
	nop
_021D8858: .word UNK04_0220FBC8
_021D885C: .word 0x00003560

	thumb_func_start MOD04_021D8860
MOD04_021D8860: ; 0x021D8860
	push {r4, lr}
	add r4, r2, #0
	cmp r1, #0xc
	bhi _021D8902
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D8874: ; jump table
	.short _021D8902 - _021D8874 - 2 ; case 0
	.short _021D888E - _021D8874 - 2 ; case 1
	.short _021D88F4 - _021D8874 - 2 ; case 2
	.short _021D88FC - _021D8874 - 2 ; case 3
	.short _021D88CE - _021D8874 - 2 ; case 4
	.short _021D8902 - _021D8874 - 2 ; case 5
	.short _021D8902 - _021D8874 - 2 ; case 6
	.short _021D88DE - _021D8874 - 2 ; case 7
	.short _021D88AE - _021D8874 - 2 ; case 8
	.short _021D88C2 - _021D8874 - 2 ; case 9
	.short _021D8902 - _021D8874 - 2 ; case 10
	.short _021D88FC - _021D8874 - 2 ; case 11
	.short _021D88FC - _021D8874 - 2 ; case 12
_021D888E:
	ldr r0, _021D8904 ; =UNK04_0220FBC8
	ldr r2, [r0, #4]
	ldr r0, _021D8908 ; =0x00003560
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _021D88AA
	add r0, r4, #0
	mov r1, #3
	bl FUN_020ACAB0
	add r0, r4, #0
	bl FUN_020ACC84
	pop {r4, pc}
_021D88AA:
	str r4, [r2, r0]
	pop {r4, pc}
_021D88AE:
	add r0, r4, #0
	mov r1, #0
	bl FUN_020ACAB0
	add r0, r4, #0
	bl MOD04_021D8910
	bl MOD04_021D8C6C
	pop {r4, pc}
_021D88C2:
	add r0, r4, #0
	bl MOD04_021D8910
	bl MOD04_021D8C6C
	pop {r4, pc}
_021D88CE:
	add r0, r4, #0
	mov r1, #4
	bl FUN_020ACAB0
	add r0, r4, #0
	bl MOD04_021D8910
	pop {r4, pc}
_021D88DE:
	add r0, r4, #0
	bl FUN_020AADCC
	cmp r0, #0
	beq _021D8902
	ldr r0, _021D8904 ; =UNK04_0220FBC8
	mov r2, #2
	ldr r1, [r0, #4]
	ldr r0, _021D890C ; =0x000034F8
	str r2, [r1, r0]
	pop {r4, pc}
_021D88F4:
	add r0, r4, #0
	bl MOD04_021D8910
	pop {r4, pc}
_021D88FC:
	add r0, r4, #0
	bl MOD04_021D8910
_021D8902:
	pop {r4, pc}
	.align 2, 0
_021D8904: .word UNK04_0220FBC8
_021D8908: .word 0x00003560
_021D890C: .word 0x000034F8

	thumb_func_start MOD04_021D8910
MOD04_021D8910: ; 0x021D8910
	push {r4, lr}
	ldr r1, _021D893C ; =UNK04_0220FBC8
	add r4, r0, #0
	ldr r2, [r1, #4]
	ldr r1, _021D8940 ; =0x00003560
	ldr r1, [r2, r1]
	cmp r4, r1
	bne _021D8936
	bl FUN_020AACFC
	add r0, r4, #0
	bl FUN_020ACC84
	ldr r0, _021D893C ; =UNK04_0220FBC8
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _021D8940 ; =0x00003560
	str r2, [r1, r0]
	pop {r4, pc}
_021D8936:
	bl FUN_020ACC84
	pop {r4, pc}
	.align 2, 0
_021D893C: .word UNK04_0220FBC8
_021D8940: .word 0x00003560

	thumb_func_start MOD04_021D8944
MOD04_021D8944: ; 0x021D8944
	push {r4, r5, r6, lr}
	bl OS_GetTick
	add r4, r0, #0
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	add r5, r1, #0
	ldr r0, [r0, #0xc]
	sub r1, r4, r0
	mov r0, #0xfa
	lsl r0, r0, #8
	mul r0, r1
	ldr r1, _021D8A40 ; =0x000082EA
	bl _u32_div_f
	ldr r1, _021D8A3C ; =UNK04_0220FBC8
	ldr r3, _021D8A44 ; =0x0000411A
	ldr r2, [r1, #8]
	sub r0, r0, r3
	add r2, r2, r0
	ldr r0, _021D8A48 ; =0xFFFFD8F0
	str r2, [r1, #8]
	cmp r2, r0
	bge _021D8976
	mov r0, #0
	str r0, [r1, #8]
_021D8976:
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	str r4, [r0, #0xc]
	str r5, [r0, #0x10]
	bl VCT_Main
	ldr r4, _021D8A3C ; =UNK04_0220FBC8
	ldr r0, _021D8A44 ; =0x0000411A
	ldr r1, [r4, #8]
	cmp r1, r0
	blt _021D899C
	add r6, r0, #0
	add r5, r0, #0
_021D898E:
	bl VCT_Main
	ldr r0, [r4, #8]
	sub r0, r0, r6
	str r0, [r4, #8]
	cmp r0, r5
	bge _021D898E
_021D899C:
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	ldr r2, [r0, #4]
	ldr r0, _021D8A4C ; =0x0000358C
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _021D89EC
	sub r0, r0, #4
	ldr r0, [r2, r0]
	cmp r0, #3
	bhi _021D89E2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D89BC: ; jump table
	.short _021D89C4 - _021D89BC - 2 ; case 0
	.short _021D89CC - _021D89BC - 2 ; case 1
	.short _021D89D4 - _021D89BC - 2 ; case 2
	.short _021D89DC - _021D89BC - 2 ; case 3
_021D89C4:
	mov r0, #3
	bl PM_SetAmpGain
	b _021D89E2
_021D89CC:
	mov r0, #2
	bl PM_SetAmpGain
	b _021D89E2
_021D89D4:
	mov r0, #1
	bl PM_SetAmpGain
	b _021D89E2
_021D89DC:
	mov r0, #0
	bl PM_SetAmpGain
_021D89E2:
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _021D8A4C ; =0x0000358C
	str r2, [r1, r0]
_021D89EC:
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D8A50 ; =0x000034F8
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021D8A00
	cmp r0, #1
	beq _021D8A3A
	cmp r0, #2
	pop {r4, r5, r6, pc}
_021D8A00:
	bl MOD04_021D8018
	cmp r0, #0
	bne _021D8A1E
	mov r0, #1
	bl MOD04_021D87D0
	cmp r0, #0
	beq _021D8A3A
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	mov r2, #1
	ldr r1, [r0, #4]
	ldr r0, _021D8A50 ; =0x000034F8
	str r2, [r1, r0]
	pop {r4, r5, r6, pc}
_021D8A1E:
	bl MOD04_021D8018
	cmp r0, #1
	bne _021D8A3A
	mov r0, #0
	bl MOD04_021D8818
	cmp r0, #0
	beq _021D8A3A
	ldr r0, _021D8A3C ; =UNK04_0220FBC8
	mov r2, #2
	ldr r1, [r0, #4]
	ldr r0, _021D8A50 ; =0x000034F8
	str r2, [r1, r0]
_021D8A3A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8A3C: .word UNK04_0220FBC8
_021D8A40: .word 0x000082EA
_021D8A44: .word 0x0000411A
_021D8A48: .word 0xFFFFD8F0
_021D8A4C: .word 0x0000358C
_021D8A50: .word 0x000034F8

	thumb_func_start MOD04_021D8A54
MOD04_021D8A54: ; 0x021D8A54
	push {r3, lr}
	ldr r3, _021D8A78 ; =UNK04_0220FBC8
	ldr r3, [r3, #4]
	cmp r3, #0
	bne _021D8A62
	mov r0, #0
	pop {r3, pc}
_021D8A62:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl VCT_HandleData
	cmp r0, #0
	beq _021D8A72
	mov r0, #1
	pop {r3, pc}
_021D8A72:
	mov r0, #0
	pop {r3, pc}
	nop
_021D8A78: .word UNK04_0220FBC8

	thumb_func_start MOD04_021D8A7C
MOD04_021D8A7C: ; 0x021D8A7C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	ldr r2, _021D8BC8 ; =UNK04_0220BAC0
	add r4, r1, #0
	ldrb r3, [r2]
	add r1, sp, #0x10
	add r5, r0, #0
	strb r3, [r1]
	ldrb r3, [r2, #1]
	ldrb r2, [r2, #2]
	strb r3, [r1, #1]
	strb r2, [r1, #2]
	ldr r1, _021D8BCC ; =UNK04_0220FBC8
	ldr r1, [r1, #4]
	cmp r1, #0
	bne _021D8ACA
	ldr r1, _021D8BD0 ; =0x000035DC
	bl AllocFromHeap
	ldr r2, _021D8BCC ; =UNK04_0220FBC8
	mov r1, #0x35
	str r0, [r2]
	add r0, #0x1f
	lsr r0, r0, #5
	lsl r0, r0, #5
	str r0, [r2, #4]
	lsl r1, r1, #8
	str r5, [r0, r1]
	add r0, r1, #0
	ldr r5, _021D8BD4 ; =UNK04_0220FBE0
	ldr r3, [r2, #4]
	sub r0, #0x40
	str r5, [r3, r0]
	ldr r0, [r2, #4]
	mov r3, #0
	sub r1, #0x3c
	str r3, [r0, r1]
	bl MOD04_021D868C
_021D8ACA:
	ldr r5, _021D8BCC ; =UNK04_0220FBC8
	mov r7, #0x11
	ldr r0, [r5, #4]
	ldr r3, _021D8BD8 ; =0x00003568
	mov r1, #3
	str r1, [r0, r3]
	add r1, r3, #0
	ldr r0, [r5, #4]
	sub r1, #0xa8
	ldr r2, [r0, r1]
	add r1, r3, #4
	str r2, [r0, r1]
	lsl r7, r7, #6
	add r0, r3, #0
	ldr r1, [r5, #4]
	lsl r2, r7, #1
	add r0, #8
	str r2, [r1, r0]
	mov r2, #0x41
	add r0, r3, #0
	ldr r1, [r5, #4]
	lsl r2, r2, #6
	add r0, #0xc
	str r2, [r1, r0]
	add r0, r3, #0
	ldr r2, [r5, #4]
	mov r1, #1
	add r0, #0x10
	str r1, [r2, r0]
	add r2, r3, #0
	ldr r6, [r5, #4]
	mov r0, #0
	add r2, #0x14
	str r0, [r6, r2]
	add r2, r3, #0
	ldr r6, [r5, #4]
	add r2, #0x18
	str r0, [r6, r2]
	sub r0, r3, #3
	ldr r2, [r5, #4]
	sub r3, #0x64
	strb r1, [r2, r0]
	ldr r0, [r5, #4]
	add r2, sp, #0x10
	add r0, r0, r3
	bl NNS_SndStrmAllocChannel
	add r0, r5, #0
	ldr r1, [r0, #4]
	ldr r0, _021D8BDC ; =0x00003504
	add r0, r1, r0
	mov r1, #0
	bl NNS_SndStrmSetVolume
	mov r0, #0x41
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _021D8BE0 ; =MOD04_021D8730
	add r1, r5, #0
	str r0, [sp, #8]
	mov r0, #0xd3
	ldr r2, [r1, #4]
	lsl r0, r0, #6
	ldr r2, [r2, r0]
	add r0, #0x44
	str r2, [sp, #0xc]
	ldr r3, [r1, #4]
	mov r2, #0x8f
	lsl r2, r2, #6
	add r0, r3, r0
	add r2, r3, r2
	mov r1, #1
	lsl r3, r7, #1
	bl NNS_SndStrmSetup
	ldr r2, _021D8BCC ; =UNK04_0220FBC8
	ldr r1, _021D8BE4 ; =0x000034F8
	ldr r0, [r2, #4]
	mov r5, #0
	str r5, [r0, r1]
	add r0, r1, #0
	ldr r3, [r2, #4]
	add r0, #0x68
	str r5, [r3, r0]
	mov r0, #1
	str r0, [sp, #0x1c]
	ldr r0, [r2, #4]
	sub r1, #0x30
	add r0, r0, r1
	str r0, [sp, #0x14]
	mov r0, #2
	str r0, [sp, #0x18]
	bl MOD04_021D8018
	add r1, sp, #0x10
	strb r0, [r1, #0x10]
	ldr r0, _021D8BE8 ; =MOD04_021D8860
	str r0, [sp, #0x2c]
	add r0, r5, #0
	str r0, [sp, #0x30]
	ldr r0, _021D8BCC ; =UNK04_0220FBC8
	ldr r0, [r0, #4]
	str r0, [sp, #0x24]
	mov r0, #0x8f
	lsl r0, r0, #6
	str r0, [sp, #0x28]
	add r0, sp, #0x14
	bl VCT_Init
	cmp r0, #0
	ldr r0, _021D8BCC ; =UNK04_0220FBC8
	add r2, r5, #0
	ldr r1, [r0, #4]
	ldr r0, _021D8BEC ; =0x000034FC
	str r2, [r1, r0]
	add r0, r4, #0
	bl FUN_020AA7A0
	bl MOD04_021D8BF0
	mov r0, #1
	bl FUN_020AA760
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021D8BC8: .word UNK04_0220BAC0
_021D8BCC: .word UNK04_0220FBC8
_021D8BD0: .word 0x000035DC
_021D8BD4: .word UNK04_0220FBE0
_021D8BD8: .word 0x00003568
_021D8BDC: .word 0x00003504
_021D8BE0: .word MOD04_021D8730
_021D8BE4: .word 0x000034F8
_021D8BE8: .word MOD04_021D8860
_021D8BEC: .word 0x000034FC

	thumb_func_start MOD04_021D8BF0
MOD04_021D8BF0: ; 0x021D8BF0
	ldr r0, _021D8BFC ; =UNK04_0220FBC8
	ldr r3, _021D8C00 ; =NNS_SndStrmStart
	ldr r1, [r0, #4]
	ldr r0, _021D8C04 ; =0x00003504
	add r0, r1, r0
	bx r3
	.align 2, 0
_021D8BFC: .word UNK04_0220FBC8
_021D8C00: .word NNS_SndStrmStart
_021D8C04: .word 0x00003504

	thumb_func_start MOD04_021D8C08
MOD04_021D8C08: ; 0x021D8C08
	push {r3, lr}
	ldr r0, _021D8C50 ; =UNK04_0220FBC8
	ldr r1, _021D8C54 ; =0x00003560
	ldr r2, [r0, #4]
	ldr r0, [r2, r1]
	cmp r0, #0
	beq _021D8C1E
	sub r1, #0x68
	ldr r1, [r2, r1]
	cmp r1, #0
	bne _021D8C24
_021D8C1E:
	bl MOD04_021D8C6C
	pop {r3, pc}
_021D8C24:
	cmp r1, #1
	bne _021D8C38
	mov r1, #2
	bl FUN_020ACBA0
	cmp r0, #0
	beq _021D8C38
	bl MOD04_021D8C6C
	pop {r3, pc}
_021D8C38:
	ldr r0, _021D8C50 ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D8C54 ; =0x00003560
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020ACBA0
	cmp r0, #0
	beq _021D8C4E
	bl MOD04_021D8C6C
_021D8C4E:
	pop {r3, pc}
	.align 2, 0
_021D8C50: .word UNK04_0220FBC8
_021D8C54: .word 0x00003560

	thumb_func_start MOD04_021D8C58
MOD04_021D8C58: ; 0x021D8C58
	ldr r1, _021D8C64 ; =UNK04_0220FBC8
	ldr r2, [r1, #4]
	ldr r1, _021D8C68 ; =0x000034C4
	str r0, [r2, r1]
	bx lr
	nop
_021D8C64: .word UNK04_0220FBC8
_021D8C68: .word 0x000034C4

	thumb_func_start MOD04_021D8C6C
MOD04_021D8C6C: ; 0x021D8C6C
	push {r4, lr}
	ldr r0, _021D8CBC ; =UNK04_0220FBC8
	ldr r1, [r0]
	cmp r1, #0
	beq _021D8CBA
	ldr r1, [r0, #4]
	ldr r0, _021D8CC0 ; =0x000034C4
	ldr r4, [r1, r0]
	bl MIC_StopAutoSampling
	ldr r0, _021D8CBC ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D8CC4 ; =0x00003504
	add r0, r1, r0
	bl NNS_SndStrmStop
	ldr r0, _021D8CBC ; =UNK04_0220FBC8
	ldr r1, [r0, #4]
	ldr r0, _021D8CC4 ; =0x00003504
	add r0, r1, r0
	bl NNS_SndStrmFreeChannel
	bl VCT_Cleanup
	ldr r1, _021D8CBC ; =UNK04_0220FBC8
	mov r0, #0x35
	ldr r2, [r1, #4]
	lsl r0, r0, #8
	ldr r0, [r2, r0]
	ldr r1, [r1]
	bl FreeToHeapExplicit
	mov r1, #0
	ldr r0, _021D8CBC ; =UNK04_0220FBC8
	cmp r4, #0
	str r1, [r0]
	str r1, [r0, #4]
	beq _021D8CBA
	blx r4
_021D8CBA:
	pop {r4, pc}
	.align 2, 0
_021D8CBC: .word UNK04_0220FBC8
_021D8CC0: .word 0x000034C4
_021D8CC4: .word 0x00003504

	thumb_func_start MOD04_021D8CC8
MOD04_021D8CC8: ; 0x021D8CC8
	push {r3, lr}
	sub sp, #0x10
	ldr r0, _021D8CEC ; =UNK04_0220FBC8
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021D8CE6
	add r0, sp, #0
	bl FUN_020AD144
	ldr r0, [sp, #4]
	cmp r0, #2
	ble _021D8CE6
	ldr r0, [sp]
	add sp, #0x10
	pop {r3, pc}
_021D8CE6:
	mov r0, #0
	add sp, #0x10
	pop {r3, pc}
	.align 2, 0
_021D8CEC: .word UNK04_0220FBC8

	thumb_func_start MOD04_021D8CF0
MOD04_021D8CF0: ; 0x021D8CF0
	ldr r0, _021D8CFC ; =UNK04_0220FBC8
	mov r2, #1
	ldr r1, [r0, #4]
	ldr r0, _021D8D00 ; =0x000034FC
	str r2, [r1, r0]
	bx lr
	.align 2, 0
_021D8CFC: .word UNK04_0220FBC8
_021D8D00: .word 0x000034FC

	thumb_func_start MOD04_021D8D04
MOD04_021D8D04: ; 0x021D8D04
	ldr r0, _021D8D10 ; =UNK04_0220FBC8
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _021D8D14 ; =0x000034FC
	str r2, [r1, r0]
	bx lr
	.align 2, 0
_021D8D10: .word UNK04_0220FBC8
_021D8D14: .word 0x000034FC

	.section .rodata

	.global UNK04_0220BAC0
UNK04_0220BAC0: ; 0x0220BAC0
	.byte 0x0D, 0x0D, 0x0D

	.section .bss

	.global UNK04_0220FBC8
UNK04_0220FBC8: ; 0x0220FBC8
	.space 0x18

	.global UNK04_0220FBE0
UNK04_0220FBE0: ; 0x0220FBE0
	.space 0x880
