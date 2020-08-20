	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD57_021D74E0
MOD57_021D74E0: ; 0x021D74E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D76E8 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D76EC ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	mov r2, #0xa
	mov r0, #3
	mov r1, #0x19
	lsl r2, r2, #0xe
	bl FUN_0201681C
	ldr r1, _021D76F0 ; =0x00003320
	add r0, r5, #0
	mov r2, #0x19
	bl OverlayManager_CreateAndGetData
	ldr r2, _021D76F0 ; =0x00003320
	mov r1, #0
	add r4, r0, #0
	bl memset
	add r0, r5, #0
	bl OverlayManager_GetField18
	add r1, r4, #0
	add r1, #0xb4
	str r0, [r1]
	mov r0, #0x19
	bl FUN_02016B94
	str r0, [r4]
	add r0, r4, #0
	bl MOD57_021D79AC
	bl MOD57_021D7A14
	ldr r0, [r4]
	bl MOD57_021D7B94
	add r0, r4, #0
	bl MOD57_021D7CA4
	bl FUN_0201CC08
	mov r0, #4
	bl FUN_0201CC24
	mov r1, #0
	mov r0, #0x38
	add r2, r1, #0
	bl FUN_0200433C
	ldr r0, _021D76F4 ; =0x000032F0
	add r0, r4, r0
	bl MOD57_021D95A8
	ldr r0, _021D76F8 ; =0x00000695
	bl FUN_020054C8
	ldr r0, _021D76FC ; =0x000030E4
	add r0, r4, r0
	bl MOD57_021D9184
	mov r0, #0
	add r1, r0, #0
	add r2, sp, #0xc
	add r5, r0, #0
	mov r6, #1
_021D7598:
	add r3, r4, #0
	add r3, #0xb4
	ldr r3, [r3]
	add r3, r3, r1
	ldr r3, [r3, #0x48]
	lsl r3, r3, #0x1f
	asr r3, r3, #0x1f
	beq _021D75AC
	strb r6, [r2]
	b _021D75AE
_021D75AC:
	strb r5, [r2]
_021D75AE:
	add r0, r0, #1
	add r1, r1, #4
	add r2, r2, #1
	cmp r0, #8
	blt _021D7598
	ldr r0, _021D76FC ; =0x000030E4
	add r1, sp, #0xc
	add r0, r4, r0
	bl MOD57_021D92F4
	ldr r0, [r4]
	add r1, r4, #4
	bl MOD57_021D899C
	mov r5, #0
	mov r6, #1
_021D75CE:
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldrb r0, [r0, #2]
	asr r0, r5
	tst r0, r6
	beq _021D75E4
	add r0, r4, #0
	add r1, r5, #0
	bl MOD57_021D8428
_021D75E4:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #8
	blo _021D75CE
	ldr r0, [r4]
	mov r1, #3
	bl FUN_02017CD0
	add r1, r4, #0
	add r1, #0xb4
	ldr r1, [r1]
	add r0, r4, #4
	bl MOD57_021D89F0
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldrb r0, [r0, #4]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _021D761E
	ldr r2, _021D7700 ; =0x0000330C
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x54
	mov r1, #1
	bl MOD57_021D9144
_021D761E:
	mov r1, #0xc3
	mov r5, #0
	lsl r1, r1, #6
	str r5, [r4, r1]
	ldr r0, _021D7704 ; =0x00003318
	sub r2, r5, #1
	strb r5, [r4, r0]
	add r1, #0x14
	str r2, [r4, r1]
	add r1, r0, #0
	sub r1, #0x2c
	str r5, [r4, r1]
	add r0, r0, #5
	ldr r7, _021D76FC ; =0x000030E4
	strb r5, [r4, r0]
_021D763C:
	ldr r0, _021D7708 ; =0x00003310
	add r2, r4, r5
	mov r1, #0
	strb r1, [r2, r0]
	add r0, r4, #0
	add r0, #0xb4
	ldr r1, [r0]
	lsl r0, r5, #2
	add r1, #0x48
	ldr r0, [r1, r0]
	lsl r1, r0, #0x1f
	asr r1, r1, #0x1f
	beq _021D76A8
	asr r0, r0, #1
	bl MOD57_021D870C
	add r6, r0, #0
	cmp r6, #4
	bhi _021D7680
	bne _021D7670
	add r0, r4, r7
	add r1, r5, #0
	mov r2, #0
	bl MOD57_021D951C
	b _021D7680
_021D7670:
	mov r2, #3
	sub r2, r2, r6
	lsl r2, r2, #0x18
	add r0, r4, r7
	add r1, r5, #0
	lsr r2, r2, #0x18
	bl MOD57_021D951C
_021D7680:
	cmp r6, #3
	bne _021D7694
	lsl r0, r5, #2
	add r1, r4, r0
	ldr r0, _021D770C ; =0x00003260
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	b _021D76A8
_021D7694:
	cmp r6, #4
	bne _021D76A8
	lsl r0, r5, #2
	add r1, r4, r0
	mov r0, #0xca
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
_021D76A8:
	add r0, r5, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #8
	blo _021D763C
	bl MOD57_021D8588
	ldr r0, _021D7710 ; =MOD57_021D848C
	mov r1, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02033F20
	mov r0, #1
	mov r1, #0x2a
	bl FUN_020051EC
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x19
	mov r1, #3
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #1
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D76E8: .word 0xFFFFE0FF
_021D76EC: .word 0x04001000
_021D76F0: .word 0x00003320
_021D76F4: .word 0x000032F0
_021D76F8: .word 0x00000695
_021D76FC: .word 0x000030E4
_021D7700: .word 0x0000330C
_021D7704: .word 0x00003318
_021D7708: .word 0x00003310
_021D770C: .word 0x00003260
_021D7710: .word MOD57_021D848C
	thumb_func_end MOD57_021D74E0

	thumb_func_start MOD57_021D7714
MOD57_021D7714: ; 0x021D7714
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	bl OverlayManager_GetData
	ldr r1, [r5]
	add r4, r0, #0
	cmp r1, #4
	bhi _021D7744
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7732: ; jump table
	.short _021D773C - _021D7732 - 2 ; case 0
	.short _021D774C - _021D7732 - 2 ; case 1
	.short _021D786A - _021D7732 - 2 ; case 2
	.short _021D7878 - _021D7732 - 2 ; case 3
	.short _021D7886 - _021D7732 - 2 ; case 4
_021D773C:
	bl FUN_0200E308
	cmp r0, #0
	bne _021D7746
_021D7744:
	b _021D790C
_021D7746:
	mov r0, #1
	str r0, [r5]
	b _021D790C
_021D774C:
	bl MOD57_021D81F8
	add r6, r0, #0
	cmp r6, #1
	bne _021D77CA
	ldr r0, _021D7920 ; =0x000030D4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D779E
	ldr r2, _021D7924 ; =0x000032EC
	mov r1, #1
	add r0, r2, #0
	str r1, [r4, r2]
	add r0, #0x31
	sub r2, #0x4c
	strb r1, [r4, r0]
	ldr r0, [r4, r2]
	bl FUN_020200A0
	ldr r0, _021D7928 ; =0x000032A0
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_020200BC
	ldr r0, _021D7928 ; =0x000032A0
	mov r1, #0xa
	ldr r0, [r4, r0]
	bl FUN_02020130
	ldr r0, _021D792C ; =0x0000331A
	mov r2, #0
	strb r2, [r4, r0]
	add r1, r0, #2
	strb r2, [r4, r1]
	add r0, r0, #1
	strb r2, [r4, r0]
	ldr r0, _021D7930 ; =0x000030D8
	str r2, [r4, r0]
	mov r0, #4
	str r0, [r5]
	b _021D7856
_021D779E:
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	add r0, r4, #0
	add r0, #0xb4
	ldr r1, [r0]
	lsl r0, r5, #2
	add r1, #0x48
	ldr r0, [r1, r0]
	lsl r1, r0, #0x1f
	asr r1, r1, #0x1f
	beq _021D7856
	asr r0, r0, #1
	bl MOD57_021D870C
	add r2, r0, #0
	ldr r0, _021D7934 ; =0x000032F0
	add r1, r5, #0
	add r0, r4, r0
	bl MOD57_021D95BC
	b _021D7856
_021D77CA:
	cmp r6, #2
	ldr r1, _021D7924 ; =0x000032EC
	bne _021D77F0
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021D77E8
	ldr r0, _021D7920 ; =0x000030D4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D77E8
	mov r0, #0
	str r0, [r4, r1]
	mov r0, #2
	add r1, #0x31
	strb r0, [r4, r1]
_021D77E8:
	add r0, r4, #0
	bl MOD57_021D82BC
	b _021D7856
_021D77F0:
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021D780A
	add r0, r1, #0
	add r0, #0x31
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _021D780A
	mov r0, #0
	str r0, [r4, r1]
	mov r0, #2
	add r1, #0x31
	strb r0, [r4, r1]
_021D780A:
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldrb r0, [r0, #4]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _021D7822
	mov r0, #0x33
	lsl r0, r0, #8
	add r0, r4, r0
	bl MOD57_021D874C
_021D7822:
	cmp r6, #3
	bne _021D7832
	ldr r0, _021D792C ; =0x0000331A
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #3
	str r0, [r5]
	b _021D7856
_021D7832:
	cmp r6, #4
	bne _021D7856
	ldr r0, _021D7938 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #0x19
	str r1, [sp, #8]
	mov r1, #4
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #2
	str r0, [r5]
_021D7856:
	add r1, r4, #0
	add r1, #0xb4
	ldr r1, [r1]
	add r0, r4, #0
	ldrb r1, [r1, #4]
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x1f
	bl MOD57_021D88A4
	b _021D790C
_021D786A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D790C
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7878:
	bl MOD57_021D7F20
	cmp r0, #0
	beq _021D790C
	mov r0, #1
	str r0, [r5]
	b _021D790C
_021D7886:
	ldr r1, _021D793C ; =0x0000331D
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _021D78EA
	bl MOD57_021D81F8
	cmp r0, #1
	bne _021D78B8
	ldr r0, _021D7920 ; =0x000030D4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D78EA
	ldr r1, _021D7924 ; =0x000032EC
	mov r2, #1
	add r0, r1, #0
	str r2, [r4, r1]
	add r0, #0x31
	strb r2, [r4, r0]
	add r0, r1, #0
	mov r2, #0
	add r0, #0x30
	strb r2, [r4, r0]
	add r1, #0x2f
	strb r2, [r4, r1]
	b _021D78EA
_021D78B8:
	cmp r0, #2
	bne _021D78D8
	ldr r1, _021D7924 ; =0x000032EC
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021D78EA
	ldr r0, _021D7920 ; =0x000030D4
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D78EA
	mov r0, #0
	str r0, [r4, r1]
	mov r0, #2
	add r1, #0x31
	strb r0, [r4, r1]
	b _021D78EA
_021D78D8:
	ldr r0, _021D7924 ; =0x000032EC
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D78EA
	mov r1, #0
	str r1, [r4, r0]
	mov r1, #2
	add r0, #0x31
	strb r1, [r4, r0]
_021D78EA:
	ldr r0, _021D7930 ; =0x000030D8
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D78FC
	add r0, r4, #0
	bl MOD57_021D80F8
	ldr r1, _021D7930 ; =0x000030D8
	str r0, [r4, r1]
_021D78FC:
	ldr r0, _021D7930 ; =0x000030D8
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D790C
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #1
	str r0, [r5]
_021D790C:
	add r0, r4, #0
	bl MOD57_021D85F4
	ldr r0, _021D7940 ; =0x000030E4
	ldr r0, [r4, r0]
	bl FUN_0201FDEC
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D7920: .word 0x000030D4
_021D7924: .word 0x000032EC
_021D7928: .word 0x000032A0
_021D792C: .word 0x0000331A
_021D7930: .word 0x000030D8
_021D7934: .word 0x000032F0
_021D7938: .word 0x000005DC
_021D793C: .word 0x0000331D
_021D7940: .word 0x000030E4
	thumb_func_end MOD57_021D7714

	thumb_func_start MOD57_021D7944
MOD57_021D7944: ; 0x021D7944
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD57_021D8588
	add r0, r4, #0
	bl MOD57_021D79F4
	ldr r0, _021D79A0 ; =0x000030E4
	add r0, r4, r0
	bl MOD57_021D94BC
	ldr r0, _021D79A4 ; =0x000030B8
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021D79A8 ; =0x000032F8
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #4
	bl MOD57_021D89D4
	ldr r0, [r4]
	bl MOD57_021D7EDC
	bl FUN_0201CD04
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x19
	bl FUN_020168D0
	mov r0, #1
	mov r1, #0x7f
	bl FUN_020051EC
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D79A0: .word 0x000030E4
_021D79A4: .word 0x000030B8
_021D79A8: .word 0x000032F8
	thumb_func_end MOD57_021D7944

	thumb_func_start MOD57_021D79AC
MOD57_021D79AC: ; 0x021D79AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x19
	bl String_ctor
	ldr r1, _021D79E8 ; =0x00003308
	str r0, [r5, r1]
	mov r0, #5
	mov r1, #0x19
	bl String_ctor
	ldr r1, _021D79EC ; =0x0000330C
	ldr r2, _021D79F0 ; =0x0000022D
	str r0, [r5, r1]
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x19
	bl NewMsgDataFromNarc
	ldr r2, _021D79EC ; =0x0000330C
	add r4, r0, #0
	ldr r2, [r5, r2]
	mov r1, #0xb
	bl ReadMsgDataIntoString
	add r0, r4, #0
	bl DestroyMsgData
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D79E8: .word 0x00003308
_021D79EC: .word 0x0000330C
_021D79F0: .word 0x0000022D
	thumb_func_end MOD57_021D79AC

	thumb_func_start MOD57_021D79F4
MOD57_021D79F4: ; 0x021D79F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D7A0C ; =0x00003308
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _021D7A10 ; =0x0000330C
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	nop
_021D7A0C: .word 0x00003308
_021D7A10: .word 0x0000330C
	thumb_func_end MOD57_021D79F4

	thumb_func_start MOD57_021D7A14
MOD57_021D7A14: ; 0x021D7A14
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7A30 ; =0x021D9800
	add r3, sp, #0
	mov r2, #5
_021D7A1E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7A1E
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7A30: .word MOD57_021D9800
	thumb_func_end MOD57_021D7A14

	thumb_func_start MOD57_021D7A34
MOD57_021D7A34: ; 0x021D7A34
	push {r3, r4, r5, lr}
	cmp r1, #0
	beq _021D7AB6
	cmp r0, #5
	bhi _021D7AC4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7A4A: ; jump table
	.short _021D7A56 - _021D7A4A - 2 ; case 0
	.short _021D7A66 - _021D7A4A - 2 ; case 1
	.short _021D7A76 - _021D7A4A - 2 ; case 2
	.short _021D7A86 - _021D7A4A - 2 ; case 3
	.short _021D7A96 - _021D7A4A - 2 ; case 4
	.short _021D7AA6 - _021D7A4A - 2 ; case 5
_021D7A56:
	mov r0, #0x33
	mov r1, #0
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7AC4
_021D7A66:
	mov r0, #0x33
	mov r1, #1
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7AC4
_021D7A76:
	mov r0, #0x33
	mov r1, #2
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7AC4
_021D7A86:
	mov r0, #0x33
	mov r1, #3
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7AC4
_021D7A96:
	mov r0, #0x33
	mov r1, #4
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7AC4
_021D7AA6:
	mov r0, #0x33
	mov r1, #5
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7AC4
_021D7AB6:
	mov r0, #0x33
	mov r1, #6
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
_021D7AC4:
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0, #0xc]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp]
	mov r1, #0x20
	ldr r5, [r0, #0xc]
	mov r2, #0x60
	add r0, r5, #0
	add r0, #0x20
	bl GXS_LoadBGPltt
	mov r1, #0x1e
	lsl r1, r1, #4
	add r0, r5, r1
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	thumb_func_end MOD57_021D7A34

	thumb_func_start MOD57_021D7AF4
MOD57_021D7AF4: ; 0x021D7AF4
	push {r3, r4, lr}
	sub sp, #4
	cmp r0, #0xa
	beq _021D7B02
	cmp r0, #0xb
	beq _021D7B12
	b _021D7B22
_021D7B02:
	mov r0, #0x33
	mov r1, #7
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7B30
_021D7B12:
	mov r0, #0x33
	mov r1, #8
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
	b _021D7B30
_021D7B22:
	mov r0, #0x33
	mov r1, #9
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r4, r0, #0
_021D7B30:
	ldr r0, [sp]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [sp]
	mov r1, #0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl GX_LoadBGPltt
	ldr r0, [sp]
	mov r1, #0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r4, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, pc}
	thumb_func_end MOD57_021D7AF4

	thumb_func_start MOD57_021D7B5C
MOD57_021D7B5C: ; 0x021D7B5C
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	mov r0, #0x33
	mov r1, #0x29
	add r2, sp, #0
	mov r3, #0x19
	bl FUN_02006C08
	add r6, r0, #0
	ldr r0, [sp]
	lsl r4, r4, #5
	ldr r5, [r0, #0xc]
	mov r1, #0x20
	add r0, r5, r4
	bl DC_FlushRange
	add r0, r5, r4
	mov r1, #0x80
	mov r2, #0x20
	bl GXS_LoadBGPltt
	add r0, r6, #0
	bl FreeToHeap
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD57_021D7B5C

	thumb_func_start MOD57_021D7B94
MOD57_021D7B94: ; 0x021D7B94
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r2, _021D7C84 ; =0x04000304
	add r4, r0, #0
	ldrh r1, [r2]
	ldr r0, _021D7C88 ; =0xFFFF7FFF
	ldr r5, _021D7C8C ; =0x021D9764
	and r0, r1
	strh r0, [r2]
	add r3, sp, #0x8c
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _021D7C90 ; =0x021D9774
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #7
	str r0, [r3]
	add r0, r4, #0
	mov r3, #2
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #7
	bl FUN_02018744
	ldr r5, _021D7C94 ; =0x021D9790
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #5
	bl FUN_02018744
	ldr r5, _021D7C98 ; =0x021D97C8
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #6
	str r0, [r3]
	add r0, r4, #0
	mov r3, #1
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #6
	bl FUN_02018744
	ldr r5, _021D7C9C ; =0x021D97E4
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
	ldr r5, _021D7CA0 ; =0x021D97AC
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
	mov r3, #1
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	add sp, #0x9c
	pop {r4, r5, pc}
	.align 2, 0
_021D7C84: .word 0x04000304
_021D7C88: .word 0xFFFF7FFF
_021D7C8C: .word MOD57_021D9764
_021D7C90: .word MOD57_021D9774
_021D7C94: .word MOD57_021D9790
_021D7C98: .word MOD57_021D97C8
_021D7C9C: .word MOD57_021D97E4
_021D7CA0: .word MOD57_021D97AC
	thumb_func_end MOD57_021D7B94

	thumb_func_start MOD57_021D7CA4
MOD57_021D7CA4: ; 0x021D7CA4
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r0, #0
	mov r0, #0x33
	mov r1, #0
	add r2, sp, #0x14
	mov r3, #0x19
	bl FUN_02006C08
	add r5, r0, #0
	ldr r0, [sp, #0x14]
	mov r1, #2
	ldr r0, [r0, #0xc]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #0x14]
	mov r2, #2
	ldr r0, [r0, #0xc]
	mov r1, #0
	lsl r2, r2, #8
	bl GXS_LoadBGPltt
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xb4
	ldr r1, [r0]
	ldrb r0, [r1, #3]
	ldrb r1, [r1, #4]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1f
	bl MOD57_021D7A34
	mov r0, #0x33
	mov r1, #0xa
	add r2, sp, #0x10
	mov r3, #0x19
	bl FUN_02006C08
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	mov r1, #2
	ldr r0, [r0, #0xc]
	lsl r1, r1, #8
	bl DC_FlushRange
	ldr r0, [sp, #0x10]
	mov r2, #2
	ldr r0, [r0, #0xc]
	mov r1, #0
	lsl r2, r2, #8
	bl GX_LoadBGPltt
	add r0, r5, #0
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldrb r0, [r0]
	bl MOD57_021D7AF4
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldrb r1, [r0, #5]
	cmp r1, #0xff
	bne _021D7D9C
	mov r2, #0
	mov r0, #0x33
	mov r1, #0x1b
	mov r3, #0x19
	str r2, [sp]
	bl UncompressFromNarc
	ldr r1, _021D7ECC ; =0x000030B8
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021D7D4C
	bl ErrorHandling
_021D7D4C:
	ldr r1, _021D7ECC ; =0x000030B8
	ldr r0, [r4, r1]
	add r1, r1, #4
	add r1, r4, r1
	bl FUN_020B0030
	cmp r0, #0
	bne _021D7D60
	bl ErrorHandling
_021D7D60:
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldr r3, _021D7ED0 ; =0x000032FC
	ldrb r0, [r0, #4]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	bne _021D7D86
	mov r0, #0x19
	str r0, [sp]
	mov r0, #0x33
	mov r1, #0x23
	mov r2, #0
	add r3, r4, r3
	bl FUN_02006BDC
	ldr r1, _021D7ED4 ; =0x000032F8
	str r0, [r4, r1]
	b _021D7DF2
_021D7D86:
	mov r0, #0x19
	str r0, [sp]
	mov r0, #0x33
	mov r1, #0x24
	mov r2, #0
	add r3, r4, r3
	bl FUN_02006BDC
	ldr r1, _021D7ED4 ; =0x000032F8
	str r0, [r4, r1]
	b _021D7DF2
_021D7D9C:
	lsl r3, r1, #2
	ldr r1, _021D7ED8 ; =0x021D9888
	mov r2, #0
	ldr r1, [r1, r3]
	mov r0, #0x33
	mov r3, #0x19
	str r2, [sp]
	bl UncompressFromNarc
	ldr r1, _021D7ECC ; =0x000030B8
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021D7DBC
	bl ErrorHandling
_021D7DBC:
	ldr r1, _021D7ECC ; =0x000030B8
	ldr r0, [r4, r1]
	add r1, r1, #4
	add r1, r4, r1
	bl FUN_020B0030
	cmp r0, #0
	bne _021D7DD0
	bl ErrorHandling
_021D7DD0:
	ldr r3, _021D7ED0 ; =0x000032FC
	mov r0, #0x19
	str r0, [sp]
	mov r0, #0x33
	mov r1, #0x2a
	mov r2, #0
	add r3, r4, r3
	bl FUN_02006BDC
	ldr r1, _021D7ED4 ; =0x000032F8
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	ldrb r0, [r0, #5]
	bl MOD57_021D7B5C
_021D7DF2:
	add r0, r4, #0
	bl MOD57_021D8690
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x17
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x1e
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x18
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x20
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r1, #0x19
	str r1, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r3, #2
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x21
	mov r3, #2
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x1a
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x22
	mov r3, #3
	bl FUN_020068C8
	add r0, r4, #0
	add r0, #0xb4
	ldr r0, [r0]
	add r4, #0xb8
	add r0, #0x68
	add r1, r4, #0
	bl MOD57_021D87DC
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021D7ECC: .word 0x000030B8
_021D7ED0: .word 0x000032FC
_021D7ED4: .word 0x000032F8
_021D7ED8: .word MOD57_021D9888
	thumb_func_end MOD57_021D7CA4

	thumb_func_start MOD57_021D7EDC
MOD57_021D7EDC: ; 0x021D7EDC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x1f
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #0x13
	mov r1, #0
	bl FUN_0201E74C
	add r0, r4, #0
	mov r1, #7
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #3
	bl FUN_020178A0
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD57_021D7EDC

	thumb_func_start MOD57_021D7F20
MOD57_021D7F20: ; 0x021D7F20
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r2, _021D80DC ; =0x0000331A
	add r4, r0, #0
	ldrb r0, [r4, r2]
	mov r5, #0
	cmp r0, #3
	bls _021D7F32
	b _021D8092
_021D7F32:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7F3E: ; jump table
	.short _021D7F46 - _021D7F3E - 2 ; case 0
	.short _021D7F74 - _021D7F3E - 2 ; case 1
	.short _021D7FB0 - _021D7F3E - 2 ; case 2
	.short _021D804C - _021D7F3E - 2 ; case 3
_021D7F46:
	mov r0, #8
	sub r2, #0x36
	str r0, [r4, r2]
	ldr r1, _021D80E0 ; =0x000030C8
	lsl r2, r0, #9
	str r2, [r4, r1]
	add r0, r1, #4
	str r2, [r4, r0]
	ldr r0, [r4, r1]
	add r0, #0x80
	str r0, [r4, r1]
	add r0, r1, #4
	ldr r2, [r4, r0]
	add r2, #0x80
	str r2, [r4, r0]
	ldr r0, _021D80E4 ; =0x00000696
	bl FUN_020054C8
	ldr r0, _021D80DC ; =0x0000331A
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _021D8092
_021D7F74:
	add r0, r2, #0
	sub r0, #0x36
	ldr r3, [r4, r0]
	ldr r1, _021D80E0 ; =0x000030C8
	mov r0, #0xc
	mov r7, #2
	sub r0, r0, r3
	add r3, r7, #0
	ldr r6, [r4, r1]
	lsl r3, r0
	sub r0, r6, r3
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #0
	bgt _021D7F9C
	mov r0, #0x24
	str r0, [r4, r1]
	ldrb r0, [r4, r2]
	add r0, r0, #1
	strb r0, [r4, r2]
_021D7F9C:
	ldr r0, _021D80E8 ; =0x000032E4
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #1
	bgt _021D8092
	mov r1, #1
	str r1, [r4, r0]
	b _021D8092
_021D7FB0:
	mov r0, #0xc3
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	cmp r1, #0
	bne _021D8006
	mov r1, #1
	str r1, [r4, r0]
	str r5, [sp]
	str r5, [sp, #4]
	str r5, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x1f
	mov r3, #6
	bl FUN_020068C8
	add r0, r4, #4
	add r1, r5, #0
	mov r2, #6
	bl MOD57_021D8FB8
	add r0, r4, #0
	bl MOD57_021D86E8
	ldr r0, [r4]
	mov r1, #7
	bl FUN_02018744
	add r1, r4, #0
	add r1, #0xb4
	ldr r1, [r1]
	add r0, r4, #4
	bl MOD57_021D8CF8
	add r2, r4, #0
	ldr r0, [r4]
	mov r1, #7
	add r2, #0xb8
	bl MOD57_021D8830
	b _021D8042
_021D8006:
	str r5, [r4, r0]
	str r5, [sp]
	str r5, [sp, #4]
	str r5, [sp, #8]
	mov r0, #0x19
	str r0, [sp, #0xc]
	ldr r2, [r4]
	mov r0, #0x33
	mov r1, #0x1e
	mov r3, #6
	bl FUN_020068C8
	add r0, r4, #4
	mov r1, #7
	mov r2, #0xa
	bl MOD57_021D8FB8
	ldr r0, [r4]
	mov r1, #7
	bl FUN_02018744
	add r0, r4, #0
	bl MOD57_021D8690
	add r1, r4, #0
	add r1, #0xb4
	ldr r1, [r1]
	add r0, r4, #4
	bl MOD57_021D89F0
_021D8042:
	ldr r0, _021D80DC ; =0x0000331A
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	b _021D8092
_021D804C:
	add r0, r2, #0
	sub r0, #0x36
	ldr r0, [r4, r0]
	add r1, r0, #1
	add r0, r2, #0
	sub r0, #0x36
	str r1, [r4, r0]
	add r0, r2, #0
	sub r0, #0x36
	ldr r0, [r4, r0]
	cmp r0, #8
	ble _021D806A
	mov r0, #8
	sub r2, #0x36
	str r0, [r4, r2]
_021D806A:
	ldr r2, _021D80E8 ; =0x000032E4
	ldr r3, _021D80E0 ; =0x000030C8
	ldr r6, [r4, r2]
	mov r2, #0xc
	mov r0, #2
	sub r2, r2, r6
	add r6, r0, #0
	ldr r1, [r4, r3]
	lsl r6, r2
	add r1, r1, r6
	str r1, [r4, r3]
	ldr r2, [r4, r3]
	lsl r1, r0, #0xb
	cmp r2, r1
	blt _021D8092
	str r1, [r4, r3]
	str r1, [r4, r3]
	add r0, r3, #4
	str r1, [r4, r0]
	mov r5, #1
_021D8092:
	ldr r0, _021D80E0 ; =0x000030C8
	ldr r0, [r4, r0]
	bl FX_Inv
	add r6, r0, #0
	ldr r0, _021D80EC ; =0x000030CC
	ldr r0, [r4, r0]
	bl FX_Inv
	mov r1, #0
	str r6, [sp, #0x10]
	str r1, [sp, #0x14]
	str r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	bl OS_WaitVBlankIntr
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D80F0 ; =0x04001020
	add r1, sp, #0x10
	mov r2, #0x80
	mov r3, #0x60
	bl G2x_SetBGyAffine_
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D80F4 ; =0x04001030
	add r1, sp, #0x10
	mov r2, #0x80
	mov r3, #0x60
	bl G2x_SetBGyAffine_
	add r0, r5, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D80DC: .word 0x0000331A
_021D80E0: .word 0x000030C8
_021D80E4: .word 0x00000696
_021D80E8: .word 0x000032E4
_021D80EC: .word 0x000030CC
_021D80F0: .word 0x04001020
_021D80F4: .word 0x04001030
	thumb_func_end MOD57_021D7F20

	thumb_func_start MOD57_021D80F8
MOD57_021D80F8: ; 0x021D80F8
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, _021D81E4 ; =0x0000331A
	ldrb r1, [r4, r0]
	cmp r1, #3
	bhi _021D81AE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8112: ; jump table
	.short _021D811A - _021D8112 - 2 ; case 0
	.short _021D8142 - _021D8112 - 2 ; case 1
	.short _021D8170 - _021D8112 - 2 ; case 2
	.short _021D81A8 - _021D8112 - 2 ; case 3
_021D811A:
	mov r2, #0
	sub r1, r0, #1
	strb r2, [r4, r1]
	sub r1, r0, #2
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _021D8134
	mov r2, #1
	ldr r1, _021D81E8 ; =0x000030D0
	lsl r2, r2, #0xc
	str r2, [r4, r1]
	mov r1, #1
	b _021D8136
_021D8134:
	mov r1, #2
_021D8136:
	strb r1, [r4, r0]
	ldr r0, _021D81EC ; =0x00003318
	ldrb r0, [r4, r0]
	bl MOD57_021D8894
	b _021D81AE
_021D8142:
	sub r1, r0, #1
	ldrb r2, [r4, r1]
	add r1, r2, #0
	add r3, r1, #1
	sub r1, r0, #1
	strb r3, [r4, r1]
	ldr r3, _021D81E8 ; =0x000030D0
	lsl r5, r2, #2
	ldr r2, _021D81F0 ; =0x021D9850
	ldr r1, [r4, r3]
	ldr r2, [r2, r5]
	sub r1, r1, r2
	str r1, [r4, r3]
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	cmp r1, #0xe
	bne _021D81AE
	mov r2, #1
	sub r1, r0, #2
	strb r2, [r4, r1]
	mov r1, #3
	strb r1, [r4, r0]
	b _021D81AE
_021D8170:
	sub r1, r0, #1
	ldrb r2, [r4, r1]
	ldr r5, _021D81E8 ; =0x000030D0
	add r1, r2, #0
	add r3, r1, #1
	sub r1, r0, #1
	strb r3, [r4, r1]
	mov r3, #0xd
	sub r2, r3, r2
	lsl r3, r2, #2
	ldr r2, _021D81F0 ; =0x021D9850
	ldr r1, [r4, r5]
	ldr r2, [r2, r3]
	add r1, r1, r2
	str r1, [r4, r5]
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	cmp r1, #0xe
	bne _021D81AE
	mov r2, #0
	sub r1, r0, #2
	strb r2, [r4, r1]
	mov r1, #1
	lsl r1, r1, #0xc
	str r1, [r4, r5]
	mov r1, #3
	strb r1, [r4, r0]
	b _021D81AE
_021D81A8:
	add sp, #0x18
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D81AE:
	mov r0, #1
	lsl r0, r0, #0xc
	bl FX_Inv
	add r5, r0, #0
	ldr r0, _021D81E8 ; =0x000030D0
	ldr r0, [r4, r0]
	bl FX_Inv
	mov r1, #0
	str r5, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	bl OS_WaitVBlankIntr
	mov r3, #0
	str r3, [sp]
	ldr r0, _021D81F4 ; =0x04000030
	add r1, sp, #8
	mov r2, #0x80
	str r3, [sp, #4]
	bl G2x_SetBGyAffine_
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D81E4: .word 0x0000331A
_021D81E8: .word 0x000030D0
_021D81EC: .word 0x00003318
_021D81F0: .word MOD57_021D9850
_021D81F4: .word 0x04000030
	thumb_func_end MOD57_021D80F8

	thumb_func_start MOD57_021D81F8
MOD57_021D81F8: ; 0x021D81F8
	push {r4, r5, r6, lr}
	mov r6, #0
	add r5, r0, #0
	ldr r0, _021D82A8 ; =0x000030D4
	sub r1, r6, #1
	str r1, [r5, r0]
	ldr r1, _021D82AC ; =gMain + 0x40
	add r4, r6, #0
	ldrh r1, [r1, #0x20]
	cmp r1, #0
	beq _021D8214
	mov r1, #1
	sub r0, #0x10
	str r1, [r5, r0]
_021D8214:
	add r1, r5, #0
	add r1, #0xb4
	ldr r1, [r1]
	ldr r2, _021D82B0 ; =0x021D9754
	ldrb r1, [r1, #4]
	ldr r0, [r5]
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1f
	lsl r3, r1, #3
	ldr r1, _021D82B4 ; =0x00003318
	add r2, r2, r3
	ldrb r1, [r5, r1]
	lsl r1, r1, #2
	ldr r1, [r1, r2]
	bl MOD57_021D890C
	ldr r1, _021D82A8 ; =0x000030D4
	str r0, [r5, r1]
	mov r0, #0
	ldr r2, [r5, r1]
	mvn r0, r0
	cmp r2, r0
	beq _021D8248
	mov r6, #1
	add r4, r6, #0
	b _021D8288
_021D8248:
	ldr r0, _021D82AC ; =gMain + 0x40
	ldrh r0, [r0, #0x22]
	cmp r0, #0
	beq _021D8282
	add r1, r5, #0
	add r1, #0xb4
	ldr r1, [r1]
	ldr r2, _021D82B0 ; =0x021D9754
	ldrb r1, [r1, #4]
	ldr r0, [r5]
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1f
	lsl r3, r1, #3
	ldr r1, _021D82B4 ; =0x00003318
	add r2, r2, r3
	ldrb r1, [r5, r1]
	lsl r1, r1, #2
	ldr r1, [r1, r2]
	bl MOD57_021D8954
	ldr r1, _021D82A8 ; =0x000030D4
	str r0, [r5, r1]
	sub r1, #0x10
	ldr r0, [r5, r1]
	cmp r0, #0
	beq _021D8288
	mov r6, #1
	mov r4, #2
	b _021D8288
_021D8282:
	mov r0, #0
	sub r1, #0x10
	str r0, [r5, r1]
_021D8288:
	cmp r6, #0
	bne _021D82A2
	ldr r0, _021D82B8 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021D829A
	mov r4, #3
	b _021D82A2
_021D829A:
	mov r0, #2
	tst r0, r1
	beq _021D82A2
	mov r4, #4
_021D82A2:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_021D82A8: .word 0x000030D4
_021D82AC: .word gMain + 0x40
_021D82B0: .word MOD57_021D9754
_021D82B4: .word 0x00003318
_021D82B8: .word gMain
	thumb_func_end MOD57_021D81F8

	thumb_func_start MOD57_021D82BC
MOD57_021D82BC: ; 0x021D82BC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021D83BC ; =gMain + 0x40
	ldr r6, _021D83C0 ; =0x0000FFFF
	ldrh r3, [r0, #0x1c]
	mov r4, #0
	cmp r3, r6
	beq _021D83AC
	ldrh r0, [r0, #0x1e]
	cmp r0, r6
	beq _021D83AC
	ldr r1, _021D83C4 ; =0x000030DC
	ldr r2, [r5, r1]
	cmp r2, r6
	beq _021D83AC
	add r0, r1, #4
	ldr r0, [r5, r0]
	cmp r0, r6
	beq _021D83AC
	sub r1, #8
	ldr r1, [r5, r1]
	sub r0, r4, #1
	cmp r1, r0
	beq _021D83AC
	cmp r1, #0
	beq _021D83AC
	add r0, r5, #0
	add r0, #0xb4
	sub r1, r1, #1
	ldr r0, [r0]
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r0, [r0, #0x48]
	lsl r0, r0, #0x1f
	asr r0, r0, #0x1f
	beq _021D83AC
	cmp r2, r3
	ble _021D830E
	sub r2, r2, r3
	sub r1, r4, #1
	b _021D8312
_021D830E:
	sub r2, r3, r2
	mov r1, #1
_021D8312:
	ldr r0, _021D83C8 ; =0x00003302
	cmp r2, #3
	strb r1, [r5, r0]
	blt _021D8358
	cmp r2, #0x28
	bgt _021D8358
	ldr r0, _021D83BC ; =gMain + 0x40
	ldrh r1, [r0, #0x1e]
	ldr r0, _021D83CC ; =0x000030E0
	ldr r0, [r5, r0]
	cmp r0, r1
	ble _021D8332
	sub r2, r0, r1
	mov r1, #0
	mvn r1, r1
	b _021D8336
_021D8332:
	sub r2, r1, r0
	mov r1, #1
_021D8336:
	ldr r0, _021D83D0 ; =0x00003303
	cmp r2, #0x28
	strb r1, [r5, r0]
	bgt _021D834C
	mov r0, #0x33
	lsl r0, r0, #8
	add r0, r5, r0
	mov r4, #1
	bl MOD57_021D875C
	b _021D8398
_021D834C:
	mov r0, #0x33
	lsl r0, r0, #8
	add r0, r5, r0
	bl MOD57_021D8744
	b _021D8398
_021D8358:
	cmp r2, #0x28
	bgt _021D8398
	ldr r0, _021D83BC ; =gMain + 0x40
	ldrh r1, [r0, #0x1e]
	ldr r0, _021D83CC ; =0x000030E0
	ldr r0, [r5, r0]
	cmp r0, r1
	ble _021D8370
	sub r2, r0, r1
	mov r1, #0
	mvn r1, r1
	b _021D8374
_021D8370:
	sub r2, r1, r0
	mov r1, #1
_021D8374:
	ldr r0, _021D83D0 ; =0x00003303
	cmp r2, #3
	strb r1, [r5, r0]
	blt _021D838E
	cmp r2, #0x28
	bgt _021D838E
	mov r0, #0x33
	lsl r0, r0, #8
	add r0, r5, r0
	mov r4, #1
	bl MOD57_021D875C
	b _021D8398
_021D838E:
	mov r0, #0x33
	lsl r0, r0, #8
	add r0, r5, r0
	bl MOD57_021D8744
_021D8398:
	cmp r4, #0
	beq _021D83AC
	ldr r1, _021D83D4 ; =0x000030D4
	add r0, r5, #0
	ldr r1, [r5, r1]
	sub r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD57_021D84AC
_021D83AC:
	ldr r1, _021D83BC ; =gMain + 0x40
	ldr r0, _021D83C4 ; =0x000030DC
	ldrh r2, [r1, #0x1c]
	str r2, [r5, r0]
	ldrh r1, [r1, #0x1e]
	add r0, r0, #4
	str r1, [r5, r0]
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D83BC: .word gMain + 0x40
_021D83C0: .word 0x0000FFFF
_021D83C4: .word 0x000030DC
_021D83C8: .word 0x00003302
_021D83CC: .word 0x000030E0
_021D83D0: .word 0x00003303
_021D83D4: .word 0x000030D4
	thumb_func_end MOD57_021D82BC

	thumb_func_start MOD57_021D83D8
MOD57_021D83D8: ; 0x021D83D8
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	add r4, r1, #0
	ldr r0, [r0]
	mov r1, #2
	bl FUN_0201886C
	add r7, r0, #0
	lsl r0, r4, #2
	add r0, #0x80
	lsl r0, r0, #0x10
	mov r2, #0
	lsr r3, r0, #0x10
_021D83F2:
	lsl r0, r2, #5
	add r4, r3, r0
	add r0, r2, #0
	add r0, #0x13
	lsl r0, r0, #6
	mov r1, #0
	add r5, r7, r0
_021D8400:
	lsl r6, r1, #1
	add r0, r1, r4
	add r6, r5, r6
	strh r0, [r6, #0x1c]
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #4
	blo _021D8400
	add r0, r2, #1
	lsl r0, r0, #0x18
	lsr r2, r0, #0x18
	cmp r2, #4
	blo _021D83F2
	ldr r0, [sp]
	mov r1, #2
	ldr r0, [r0]
	bl FUN_02017CD0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD57_021D83D8

	thumb_func_start MOD57_021D8428
MOD57_021D8428: ; 0x021D8428
	push {r3, r4, r5, r6, r7, lr}
	lsr r5, r1, #0x1f
	lsl r4, r1, #0x1e
	sub r4, r4, r5
	mov r2, #0x1e
	ror r4, r2
	add r2, r5, r4
	lsl r2, r2, #0x18
	lsr r4, r2, #0x18
	lsl r1, r1, #0x16
	mov r2, #7
	add r5, r4, #0
	lsr r1, r1, #0x18
	mul r5, r2
	mov r6, #3
	add r4, r6, r5
	lsl r4, r4, #0x18
	mov r3, #4
	mul r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	ldr r0, [r0]
	add r1, r6, #0
	lsr r4, r4, #0x18
	bl FUN_0201886C
	mov r2, #0
	add r3, r0, r4
	add r0, r2, #0
_021D8464:
	add r6, r2, r5
	lsl r4, r2, #4
	lsl r6, r6, #5
	add r1, r0, #0
	add r4, #0xba
	add r6, r3, r6
_021D8470:
	add r7, r1, r4
	strb r7, [r6, r1]
	add r1, r1, #1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #5
	blo _021D8470
	add r1, r2, #1
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	cmp r2, #5
	blo _021D8464
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD57_021D8428

	thumb_func_start MOD57_021D848C
MOD57_021D848C: ; 0x021D848C
	push {r3, lr}
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r3, _021D84A4 ; =0x027E0000
	ldr r1, _021D84A8 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r3, pc}
	.align 2, 0
_021D84A4: .word 0x027E0000
_021D84A8: .word 0x00003FF8
	thumb_func_end MOD57_021D848C

	thumb_func_start MOD57_021D84AC
MOD57_021D84AC: ; 0x021D84AC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, #0xb4
	add r4, r1, #0
	ldr r0, [r0]
	lsl r6, r4, #2
	add r0, r0, r6
	ldr r0, [r0, #0x48]
	asr r0, r0, #1
	add r1, r0, #1
	str r1, [sp]
	cmp r1, #0xc8
	bge _021D8578
	bl MOD57_021D870C
	add r7, r0, #0
	ldr r0, _021D857C ; =0x00003310
	ldr r2, _021D8580 ; =0x021D9734
	add r1, r5, r0
	ldrb r0, [r1, r4]
	ldrb r2, [r2, r7]
	add r0, r0, #1
	strb r0, [r1, r4]
	ldrb r0, [r1, r4]
	cmp r0, r2
	blo _021D8578
	mov r0, #0
	strb r0, [r1, r4]
	add r0, r5, #0
	add r0, #0xb4
	ldr r2, [r0]
	mov r1, #1
	add r2, #0x48
	ldr r0, [r2, r6]
	and r1, r0
	asr r0, r0, #1
	add r0, r0, #1
	lsl r0, r0, #1
	orr r0, r1
	str r0, [r2, r6]
	ldr r0, [sp]
	bl MOD57_021D870C
	add r6, r0, #0
	cmp r7, r6
	bls _021D850C
	bl ErrorHandling
_021D850C:
	cmp r7, r6
	bhs _021D8578
	cmp r6, #4
	bhi _021D8536
	cmp r6, #4
	ldr r0, _021D8584 ; =0x000030E4
	bne _021D8526
	add r0, r5, r0
	add r1, r4, #0
	mov r2, #0
	bl MOD57_021D951C
	b _021D8536
_021D8526:
	mov r2, #3
	sub r2, r2, r6
	lsl r2, r2, #0x18
	add r0, r5, r0
	add r1, r4, #0
	lsr r2, r2, #0x18
	bl MOD57_021D951C
_021D8536:
	cmp r6, #3
	bne _021D854E
	add r4, #8
	lsl r0, r4, #2
	add r1, r5, r0
	mov r0, #0xc9
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	pop {r3, r4, r5, r6, r7, pc}
_021D854E:
	cmp r6, #4
	bne _021D8578
	add r0, r4, #0
	add r0, #8
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0xc9
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add r4, #0x10
	lsl r0, r4, #2
	add r1, r5, r0
	mov r0, #0xc9
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
_021D8578:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D857C: .word 0x00003310
_021D8580: .word MOD57_021D9734
_021D8584: .word 0x000030E4
	thumb_func_end MOD57_021D84AC

	thumb_func_start MOD57_021D8588
MOD57_021D8588: ; 0x021D8588
	push {r4, lr}
	sub sp, #0x18
	mov r0, #1
	lsl r0, r0, #0xc
	bl FX_Inv
	add r4, r0, #0
	mov r0, #1
	lsl r0, r0, #0xc
	bl FX_Inv
	mov r1, #0
	str r4, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	bl OS_WaitVBlankIntr
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D85E8 ; =0x04001020
	add r1, sp, #8
	mov r2, #0x80
	mov r3, #0x60
	bl G2x_SetBGyAffine_
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D85EC ; =0x04001030
	add r1, sp, #8
	mov r2, #0x80
	mov r3, #0x60
	bl G2x_SetBGyAffine_
	bl OS_WaitVBlankIntr
	mov r3, #0
	str r3, [sp]
	ldr r0, _021D85F0 ; =0x04000030
	add r1, sp, #8
	mov r2, #0x80
	str r3, [sp, #4]
	bl G2x_SetBGyAffine_
	add sp, #0x18
	pop {r4, pc}
	.align 2, 0
_021D85E8: .word 0x04001020
_021D85EC: .word 0x04001030
_021D85F0: .word 0x04000030
	thumb_func_end MOD57_021D8588

	thumb_func_start MOD57_021D85F4
MOD57_021D85F4: ; 0x021D85F4
	push {r4, lr}
	ldr r1, _021D862C ; =0x0000331D
	add r4, r0, #0
	ldrb r1, [r4, r1]
	cmp r1, #1
	bne _021D8614
	ldr r1, _021D8630 ; =0x021D973C
	ldr r1, [r1, #0x10]
	bl MOD57_021D8634
	cmp r0, #0
	beq _021D862A
	ldr r0, _021D862C ; =0x0000331D
	mov r1, #0
	strb r1, [r4, r0]
	pop {r4, pc}
_021D8614:
	cmp r1, #2
	bne _021D862A
	ldr r1, _021D8630 ; =0x021D973C
	ldr r1, [r1, #0x14]
	bl MOD57_021D8634
	cmp r0, #0
	beq _021D862A
	ldr r0, _021D862C ; =0x0000331D
	mov r1, #0
	strb r1, [r4, r0]
_021D862A:
	pop {r4, pc}
	.align 2, 0
_021D862C: .word 0x0000331D
_021D8630: .word MOD57_021D973C
	thumb_func_end MOD57_021D85F4

	thumb_func_start MOD57_021D8634
MOD57_021D8634: ; 0x021D8634
	push {r4, lr}
	ldr r2, _021D8688 ; =0x0000331C
	add r4, r0, #0
	ldrb r0, [r4, r2]
	lsl r0, r0, #1
	ldrb r3, [r1, r0]
	cmp r3, #0
	bne _021D8650
	mov r1, #0
	sub r0, r2, #1
	strb r1, [r4, r0]
	strb r1, [r4, r2]
	mov r0, #1
	pop {r4, pc}
_021D8650:
	sub r0, r2, #1
	ldrb r0, [r4, r0]
	cmp r0, r3
	blo _021D8664
	mov r3, #0
	sub r0, r2, #1
	strb r3, [r4, r0]
	ldrb r0, [r4, r2]
	add r0, r0, #1
	strb r0, [r4, r2]
_021D8664:
	ldr r0, _021D8688 ; =0x0000331C
	ldrb r2, [r4, r0]
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	lsl r2, r2, #1
	add r2, r2, #1
	ldrb r1, [r1, r2]
	cmp r0, #0
	bne _021D867C
	add r0, r4, #0
	bl MOD57_021D83D8
_021D867C:
	ldr r0, _021D868C ; =0x0000331B
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_021D8688: .word 0x0000331C
_021D868C: .word 0x0000331B
	thumb_func_end MOD57_021D8634

	thumb_func_start MOD57_021D8690
MOD57_021D8690: ; 0x021D8690
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D86E0 ; =0x000032FC
	mov r1, #7
	ldr r0, [r5, r0]
	ldr r4, [r0, #8]
	ldr r0, _021D86E4 ; =0x000030BC
	ldr r3, [r5, r0]
	mov r0, #0
	str r0, [sp]
	ldr r2, [r3, #0x14]
	ldr r0, [r5]
	ldr r3, [r3, #0x10]
	bl FUN_02017E14
	ldr r0, [r5]
	mov r1, #7
	bl FUN_0201886C
	cmp r0, #0
	beq _021D86CA
	ldr r2, _021D86E0 ; =0x000032FC
	ldr r0, [r5]
	ldr r2, [r5, r2]
	mov r1, #7
	add r2, #0xc
	add r3, r4, #0
	bl FUN_02017DFC
_021D86CA:
	mov r0, #0
	str r0, [sp]
	ldr r2, _021D86E0 ; =0x000032FC
	ldr r0, [r5]
	ldr r2, [r5, r2]
	mov r1, #7
	add r2, #0xc
	add r3, r4, #0
	bl FUN_02017CE8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D86E0: .word 0x000032FC
_021D86E4: .word 0x000030BC
	thumb_func_end MOD57_021D8690

	thumb_func_start MOD57_021D86E8
MOD57_021D86E8: ; 0x021D86E8
	push {r3, lr}
	sub sp, #0x10
	mov r1, #6
	str r1, [sp]
	str r1, [sp, #4]
	mov r1, #9
	str r1, [sp, #8]
	mov r1, #0x10
	str r1, [sp, #0xc]
	ldr r0, [r0]
	mov r1, #7
	mov r2, #0
	mov r3, #0x14
	bl FUN_02018540
	add sp, #0x10
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD57_021D86E8

	thumb_func_start MOD57_021D870C
MOD57_021D870C: ; 0x021D870C
	push {r3, lr}
	cmp r0, #0
	blt _021D871A
	cmp r0, #0x64
	bge _021D871A
	mov r0, #0
	pop {r3, pc}
_021D871A:
	cmp r0, #0x8c
	bge _021D8722
	mov r0, #1
	pop {r3, pc}
_021D8722:
	cmp r0, #0xaa
	bge _021D872A
	mov r0, #2
	pop {r3, pc}
_021D872A:
	cmp r0, #0xbe
	bge _021D8732
	mov r0, #3
	pop {r3, pc}
_021D8732:
	cmp r0, #0xc8
	bge _021D873A
	mov r0, #4
	pop {r3, pc}
_021D873A:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD57_021D870C

	thumb_func_start MOD57_021D8744
MOD57_021D8744: ; 0x021D8744
	mov r1, #0
	strb r1, [r0, #2]
	strb r1, [r0, #3]
	bx lr
	thumb_func_end MOD57_021D8744

	thumb_func_start MOD57_021D874C
MOD57_021D874C: ; 0x021D874C
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #1]
	strb r1, [r0, #2]
	strb r1, [r0, #3]
	strb r1, [r0, #4]
	bx lr
	.align 2, 0
	thumb_func_end MOD57_021D874C

	thumb_func_start MOD57_021D875C
MOD57_021D875C: ; 0x021D875C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _021D87D4 ; =0x021D973C
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #0
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bne _021D8782
	mov r0, #1
	ldrsb r0, [r4, r0]
	cmp r0, #0
	bne _021D8782
	ldr r0, _021D87D8 ; =0x00000692
	bl FUN_020054C8
_021D8782:
	mov r0, #0
	ldrsb r1, [r4, r0]
	mov r0, #2
	ldrsb r0, [r4, r0]
	mul r0, r1
	bmi _021D879A
	mov r0, #1
	ldrsb r1, [r4, r0]
	mov r0, #3
	ldrsb r0, [r4, r0]
	mul r0, r1
	bpl _021D87BC
_021D879A:
	ldrb r0, [r4, #4]
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	strb r0, [r4, #4]
	ldrb r0, [r4, #4]
	lsl r1, r0, #2
	add r0, sp, #0
	ldr r0, [r0, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020054C8
_021D87BC:
	mov r0, #2
	ldrsb r0, [r4, r0]
	strb r0, [r4]
	mov r0, #3
	ldrsb r0, [r4, r0]
	strb r0, [r4, #1]
	mov r0, #0
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	add sp, #8
	pop {r4, pc}
	nop
_021D87D4: .word MOD57_021D973C
_021D87D8: .word 0x00000692
	thumb_func_end MOD57_021D875C

	thumb_func_start MOD57_021D87DC
MOD57_021D87DC: ; 0x021D87DC
	push {r4, r5, r6, r7}
	mov r2, #3
	mov r4, #0
	lsl r2, r2, #0xc
_021D87E4:
	asr r3, r4, #2
	lsr r3, r3, #0x1d
	add r3, r4, r3
	asr r3, r3, #3
	lsr r6, r3, #0x1f
	lsl r5, r3, #0x1d
	sub r5, r5, r6
	mov r3, #0x1d
	ror r5, r3
	add r3, r6, r5
	asr r5, r4, #5
	lsr r5, r5, #0x1a
	lsl r3, r3, #0x18
	add r5, r4, r5
	lsr r3, r3, #0x18
	asr r5, r5, #6
	lsl r5, r5, #3
	add r3, r0, r3
	ldrb r3, [r5, r3]
	lsr r7, r4, #0x1f
	lsl r6, r4, #0x1d
	sub r6, r6, r7
	mov r5, #0x1d
	ror r6, r5
	add r5, r7, r6
	lsl r5, r5, #0x18
	add r6, r3, #0
	lsr r5, r5, #0x18
	asr r6, r5
	mov r3, #1
	and r3, r6
	strb r3, [r1, r4]
	add r4, r4, #1
	cmp r4, r2
	blt _021D87E4
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
	thumb_func_end MOD57_021D87DC

	thumb_func_start MOD57_021D8830
MOD57_021D8830: ; 0x021D8830
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	mov r1, #1
	str r1, [sp]
	lsl r1, r7, #0x18
	mov r3, #3
	str r0, [sp, #4]
	lsr r1, r1, #0x18
	lsl r3, r3, #0xc
	bl FUN_02017E14
	lsl r1, r7, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl FUN_0201886C
	mov r4, #0
	add r1, r0, #0
	add r3, r4, #0
	add r0, r4, #0
_021D885A:
	add r5, r3, #0
	add r5, #0xe
	lsl r5, r5, #6
	add r2, r0, #0
	add r5, r1, r5
_021D8864:
	lsl r6, r2, #1
	add r4, r4, #1
	add r2, r2, #1
	lsl r4, r4, #0x10
	lsl r2, r2, #0x18
	lsr r4, r4, #0x10
	add r6, r5, r6
	lsr r2, r2, #0x18
	strh r4, [r6, #8]
	cmp r2, #0x18
	blo _021D8864
	add r2, r3, #1
	lsl r2, r2, #0x18
	lsr r3, r2, #0x18
	cmp r3, #8
	blo _021D885A
	lsl r1, r7, #0x18
	ldr r0, [sp, #4]
	lsr r1, r1, #0x18
	bl FUN_02017CD0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD57_021D8830

	thumb_func_start MOD57_021D8894
MOD57_021D8894: ; 0x021D8894
	ldr r3, _021D889C ; =FUN_020054C8
	ldr r0, _021D88A0 ; =0x00000699
	bx r3
	nop
_021D889C: .word FUN_020054C8
_021D88A0: .word 0x00000699
	thumb_func_end MOD57_021D8894

	thumb_func_start MOD57_021D88A4
MOD57_021D88A4: ; 0x021D88A4
	push {r4, lr}
	add r4, r0, #0
	cmp r1, #0
	beq _021D8900
	mov r0, #0xc3
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D88F0
	ldr r2, _021D8904 ; =0x0000331E
	ldrb r0, [r4, r2]
	cmp r0, #0xf
	bne _021D88DE
	add r1, r4, #0
	add r1, #0xb4
	sub r2, #0x16
	ldr r1, [r1]
	ldr r2, [r4, r2]
	add r0, r4, #4
	bl MOD57_021D905C
	ldr r2, _021D8908 ; =0x0000330C
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x54
	mov r1, #1
	bl MOD57_021D9144
	b _021D88F0
_021D88DE:
	cmp r0, #0
	bne _021D88F0
	sub r2, #0x12
	add r0, r4, #0
	ldr r2, [r4, r2]
	add r0, #0x54
	mov r1, #0
	bl MOD57_021D9144
_021D88F0:
	ldr r0, _021D8904 ; =0x0000331E
	mov r1, #0x1e
	ldrb r0, [r4, r0]
	add r0, r0, #1
	bl _s32_div_f
	ldr r0, _021D8904 ; =0x0000331E
	strb r1, [r4, r0]
_021D8900:
	pop {r4, pc}
	nop
_021D8904: .word 0x0000331E
_021D8908: .word 0x0000330C
	thumb_func_end MOD57_021D88A4

	thumb_func_start MOD57_021D890C
MOD57_021D890C: ; 0x021D890C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, r1, #0
	bl FUN_02020988
	mov r1, #0
	add r4, r0, #0
	mvn r1, r1
	cmp r4, r1
	beq _021D894A
	cmp r4, #0
	beq _021D894C
	mov r1, #0x40
	add r0, sp, #4
	strh r1, [r0]
	add r0, sp, #4
	str r0, [sp]
	ldr r3, _021D8950 ; =gMain + 0x40
	add r0, r5, #0
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #2
	bl FUN_0201AFBC
	cmp r0, #0
	bne _021D894A
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r3, r4, r5, pc}
_021D894A:
	add r0, r4, #0
_021D894C:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8950: .word gMain + 0x40
	thumb_func_end MOD57_021D890C

	thumb_func_start MOD57_021D8954
MOD57_021D8954: ; 0x021D8954
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, r1, #0
	bl FUN_02020968
	mov r1, #0
	add r4, r0, #0
	mvn r1, r1
	cmp r4, r1
	beq _021D8992
	cmp r4, #0
	beq _021D8994
	mov r1, #0x40
	add r0, sp, #4
	strh r1, [r0]
	add r0, sp, #4
	str r0, [sp]
	ldr r3, _021D8998 ; =gMain + 0x40
	add r0, r5, #0
	ldrh r2, [r3, #0x1c]
	ldrh r3, [r3, #0x1e]
	mov r1, #2
	bl FUN_0201AFBC
	cmp r0, #0
	bne _021D8992
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r3, r4, r5, pc}
_021D8992:
	add r0, r4, #0
_021D8994:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8998: .word gMain + 0x40
	thumb_func_end MOD57_021D8954

	thumb_func_start MOD57_021D899C
MOD57_021D899C: ; 0x021D899C
	push {r3, r4, r5, r6, r7, lr}
	ldr r7, _021D89D0 ; =0x021D98F4
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #0
_021D89A6:
	lsl r1, r4, #4
	lsl r2, r4, #3
	add r0, r5, #0
	add r1, r6, r1
	add r2, r7, r2
	bl FUN_02019150
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xb
	blo _021D89A6
	mov r2, #0
	add r0, r5, #0
	mov r1, #7
	mov r3, #1
	str r2, [sp]
	bl FUN_02017F48
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D89D0: .word MOD57_021D98F4
	thumb_func_end MOD57_021D899C

	thumb_func_start MOD57_021D89D4
MOD57_021D89D4: ; 0x021D89D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
_021D89DA:
	lsl r0, r4, #4
	add r0, r5, r0
	bl FUN_02019178
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0xb
	blo _021D89DA
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD57_021D89D4

	thumb_func_start MOD57_021D89F0
MOD57_021D89F0: ; 0x021D89F0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r1, #0
	mov r1, #0x88
	str r1, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	mov r1, #0
	add r2, r1, #0
	add r3, r1, #0
	add r7, r0, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0x88
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	add r0, #0x10
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0x88
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	add r0, #0x20
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0x88
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	add r0, #0x30
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0x88
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	add r0, #0x40
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	add r0, #0x50
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	add r0, #0x60
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	ldr r2, _021D8CEC ; =0x0000022D
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x19
	bl NewMsgDataFromNarc
	str r0, [sp, #0x14]
	mov r0, #0x20
	mov r1, #0x19
	bl String_ctor
	add r5, r0, #0
	mov r4, #0
_021D8AA8:
	cmp r4, #3
	bne _021D8AB6
	bne _021D8AE0
	ldrb r0, [r6, #4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _021D8AE0
_021D8AB6:
	ldr r1, _021D8CF0 ; =0x021D98C8
	lsl r2, r4, #2
	ldr r1, [r1, r2]
	ldr r0, [sp, #0x14]
	add r2, r5, #0
	bl ReadMsgDataIntoString
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D8CF4 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r0, r4, #4
	add r0, r7, r0
	add r2, r5, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
_021D8AE0:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #7
	blo _021D8AA8
	mov r0, #0x20
	mov r1, #0x19
	bl String_ctor
	str r0, [sp, #0x10]
	mov r0, #6
	mov r1, #0x20
	mov r2, #0x19
	bl FUN_0200AA90
	mov r2, #0
	str r5, [sp]
	add r4, r0, #0
	ldrh r0, [r6, #0x28]
	mov r1, #0x88
	add r3, r2, #0
	str r0, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	mov r0, #2
	str r0, [sp, #0xc]
	add r0, r7, #0
	bl MOD57_021D8FD8
	add r1, r6, #0
	add r0, r5, #0
	add r1, #8
	bl CopyU16ArrayToString
	add r0, r7, #0
	mov r2, #0
	add r0, #0x10
	mov r1, #0x88
	add r3, r2, #0
	str r5, [sp]
	bl MOD57_021D9024
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [r6, #0x1c]
	add r0, r4, #0
	mov r1, #5
	mov r3, #6
	bl FUN_0200AD38
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	mov r1, #0xe
	bl ReadMsgDataIntoString
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	add r1, r5, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0x88
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8CF4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r7, #0
	str r1, [sp, #0xc]
	add r0, #0x20
	add r2, r5, #0
	bl AddTextPrinterParameterized2
	ldrb r0, [r6, #4]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _021D8BA4
	str r5, [sp]
	ldr r0, [r6, #0x20]
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r7, #0
	add r0, #0x30
	mov r1, #0x88
	add r3, r2, #0
	bl MOD57_021D8FD8
_021D8BA4:
	str r5, [sp]
	ldr r0, [r6, #0x24]
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #9
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r7, #0
	add r0, #0x40
	mov r1, #0x88
	add r3, r2, #0
	bl MOD57_021D8FD8
	ldrb r0, [r6, #4]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _021D8C02
	ldr r0, [r6, #0x18]
	bl GetIGTHours
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	ldr r0, [r6, #0x18]
	bl GetIGTMinutes
	mov r3, #2
	add r2, r0, #0
	str r3, [sp]
	mov r1, #1
	add r0, r4, #0
	str r1, [sp, #4]
	bl FUN_0200AD38
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	mov r1, #0x10
	bl ReadMsgDataIntoString
	b _021D8C32
_021D8C02:
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldrh r2, [r6, #0x2a]
	add r0, r4, #0
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r3, #2
	add r2, r6, #0
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r2, #0x2e
	ldrb r2, [r2]
	add r0, r4, #0
	bl FUN_0200AD38
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	mov r1, #0xf
	bl ReadMsgDataIntoString
_021D8C32:
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	add r1, r5, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xe0
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8CF4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r7, #0
	add r0, #0x50
	add r2, r5, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	mov r1, #2
	add r2, r6, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r2, #0x2f
	ldrb r2, [r2]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_0200AD38
	add r2, r6, #0
	add r2, #0x30
	ldrb r2, [r2]
	add r0, r4, #0
	mov r1, #3
	bl FUN_0200B764
	mov r3, #2
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r6, #0x31
	ldrb r2, [r6]
	add r0, r4, #0
	mov r1, #4
	bl FUN_0200AD38
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	mov r1, #0x11
	bl ReadMsgDataIntoString
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	add r1, r5, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xe0
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8CF4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r7, #0x60
	add r0, r7, #0
	add r2, r5, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl String_dtor
	add r0, r4, #0
	bl FUN_0200AB18
	add r0, r5, #0
	bl String_dtor
	ldr r0, [sp, #0x14]
	bl DestroyMsgData
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8CEC: .word 0x0000022D
_021D8CF0: .word MOD57_021D98C8
_021D8CF4: .word 0x00010200
	thumb_func_end MOD57_021D89F0

	thumb_func_start MOD57_021D8CF8
MOD57_021D8CF8: ; 0x021D8CF8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r0, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x20
	str r1, [sp, #0x10]
	mov r1, #0
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0x70
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0x80
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0x90
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	mov r1, #0
	mov r0, #0xe0
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_020196F4
	ldr r2, _021D8FAC ; =0x0000022D
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x19
	bl NewMsgDataFromNarc
	add r7, r0, #0
	mov r0, #0x20
	mov r1, #0x19
	bl String_ctor
	add r5, r0, #0
	mov r4, #7
_021D8D72:
	ldr r1, _021D8FB0 ; =0x021D98C8
	lsl r2, r4, #2
	ldr r1, [r1, r2]
	add r0, r7, #0
	add r2, r5, #0
	bl ReadMsgDataIntoString
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _021D8FB4 ; =0x00010200
	mov r1, #0
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	lsl r0, r4, #4
	add r0, r6, r0
	add r2, r5, #0
	add r3, r1, #0
	bl AddTextPrinterParameterized2
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xb
	blo _021D8D72
	mov r0, #0x20
	mov r1, #0x19
	bl String_ctor
	str r0, [sp, #0x14]
	mov r0, #5
	mov r1, #0x20
	mov r2, #0x19
	bl FUN_0200AA90
	ldr r1, [sp, #0x10]
	add r4, r0, #0
	add r1, #0x33
	ldrb r1, [r1]
	cmp r1, #0
	beq _021D8E3C
	mov r1, #2
	str r1, [sp]
	mov r2, #1
	str r2, [sp, #4]
	ldr r2, [sp, #0x10]
	add r3, r1, #0
	add r2, #0x32
	ldrb r2, [r2]
	bl FUN_0200AD38
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	add r2, #0x33
	ldrb r2, [r2]
	mov r1, #3
	bl FUN_0200B764
	mov r3, #2
	ldr r2, [sp, #0x10]
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r2, #0x34
	ldrb r2, [r2]
	add r0, r4, #0
	mov r1, #4
	bl FUN_0200AD38
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r2, [sp, #0x10]
	add r0, r4, #0
	ldrh r2, [r2, #0x2c]
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	mov r3, #2
	ldr r2, [sp, #0x10]
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	add r2, #0x35
	ldrb r2, [r2]
	add r0, r4, #0
	bl FUN_0200AD38
	ldr r2, [sp, #0x14]
	add r0, r7, #0
	mov r1, #0x11
	bl ReadMsgDataIntoString
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	add r1, r5, #0
	bl StringExpandPlaceholders
	b _021D8E74
_021D8E3C:
	ldr r2, [sp, #0x14]
	add r0, r7, #0
	mov r1, #0xc
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_0200ABB4
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	mov r1, #1
	bl FUN_0200ABB4
	add r0, r7, #0
	mov r1, #0x14
	add r2, r5, #0
	bl ReadMsgDataIntoString
_021D8E74:
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xe0
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8FB4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x70
	add r2, r5, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r2, [sp, #0x14]
	add r0, r7, #0
	mov r1, #0xf
	bl ReadMsgDataIntoString
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	add r1, r5, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r5, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xe0
	sub r3, r1, r0
	mov r0, #0x10
	str r0, [sp]
	mov r1, #0
	ldr r0, _021D8FB4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x70
	add r2, r5, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	mov r2, #0
	ldr r0, [sp, #0x10]
	str r5, [sp]
	ldr r0, [r0, #0x38]
	mov r1, #0xe0
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0x80
	add r3, r2, #0
	bl MOD57_021D8FD8
	add r0, r7, #0
	mov r1, #0x12
	add r2, r5, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8FB4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x90
	add r2, r5, #0
	mov r3, #0x70
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	mov r2, #0
	ldr r0, [sp, #0x10]
	str r5, [sp]
	ldr r0, [r0, #0x40]
	mov r1, #0xe0
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0x90
	add r3, r2, #0
	bl MOD57_021D8FD8
	add r0, r7, #0
	mov r1, #0x13
	add r2, r5, #0
	bl ReadMsgDataIntoString
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D8FB4 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x90
	add r2, r5, #0
	mov r3, #0xb0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	str r5, [sp]
	ldr r0, [r0, #0x3c]
	mov r1, #0xe0
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0x90
	mov r2, #0x40
	mov r3, #0
	bl MOD57_021D8FD8
	mov r2, #0
	ldr r0, [sp, #0x10]
	str r5, [sp]
	ldr r0, [r0, #0x44]
	add r6, #0xa0
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r6, #0
	mov r1, #0xe0
	add r3, r2, #0
	bl MOD57_021D8FD8
	ldr r0, [sp, #0x14]
	bl String_dtor
	add r0, r4, #0
	bl FUN_0200AB18
	add r0, r5, #0
	bl String_dtor
	add r0, r7, #0
	bl DestroyMsgData
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8FAC: .word 0x0000022D
_021D8FB0: .word MOD57_021D98C8
_021D8FB4: .word 0x00010200
	thumb_func_end MOD57_021D8CF8

	thumb_func_start MOD57_021D8FB8
MOD57_021D8FB8: ; 0x021D8FB8
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	cmp r4, r6
	bhi _021D8FD6
_021D8FC4:
	lsl r0, r4, #4
	add r0, r5, r0
	bl FUN_02019570
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, r6
	bls _021D8FC4
_021D8FD6:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD57_021D8FB8

	thumb_func_start MOD57_021D8FD8
MOD57_021D8FD8: ; 0x021D8FD8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	mov r0, #1
	add r4, r2, #0
	str r0, [sp]
	add r2, sp, #0x18
	add r5, r1, #0
	add r6, r3, #0
	ldrb r2, [r2, #0x18]
	ldr r0, [sp, #0x28]
	ldr r1, [sp, #0x2c]
	ldr r3, [sp, #0x34]
	bl String16_FormatInteger
	mov r0, #0
	ldr r1, [sp, #0x28]
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	add r3, r3, r4
	str r6, [sp]
	mov r1, #0
	ldr r0, _021D9020 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r2, [sp, #0x28]
	add r0, r7, #0
	sub r3, r5, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9020: .word 0x00010200
	thumb_func_end MOD57_021D8FD8

	thumb_func_start MOD57_021D9024
MOD57_021D9024: ; 0x021D9024
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #0
	add r4, r2, #0
	ldr r1, [sp, #0x28]
	add r6, r3, #0
	add r2, r0, #0
	bl FUN_02002E14
	add r3, r0, #0
	add r3, r3, r4
	str r6, [sp]
	mov r1, #0
	ldr r0, _021D9058 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r2, [sp, #0x28]
	add r0, r7, #0
	sub r3, r5, r3
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9058: .word 0x00010200
	thumb_func_end MOD57_021D9024

	thumb_func_start MOD57_021D905C
MOD57_021D905C: ; 0x021D905C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r7, r0, #0
	ldr r0, [r5, #0x18]
	cmp r0, #0
	bne _021D906E
	bl ErrorHandling
_021D906E:
	ldr r0, [r5, #0x18]
	bl GetIGTHours
	mov r0, #0x28
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	add r0, r7, #0
	mov r1, #0
	add r0, #0x50
	mov r2, #0xb8
	add r3, r1, #0
	bl FUN_020196F4
	ldr r2, _021D913C ; =0x0000022D
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x19
	bl NewMsgDataFromNarc
	str r0, [sp, #0x10]
	mov r0, #0x20
	mov r1, #0x19
	bl String_ctor
	add r4, r0, #0
	mov r0, #0x20
	mov r1, #0x19
	bl String_ctor
	str r0, [sp, #0x14]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0x19
	bl FUN_0200AA90
	add r6, r0, #0
	ldr r0, [r5, #0x18]
	bl GetIGTHours
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	mov r1, #0
	mov r3, #3
	bl FUN_0200AD38
	ldr r0, [r5, #0x18]
	bl GetIGTMinutes
	mov r3, #2
	add r2, r0, #0
	str r3, [sp]
	mov r1, #1
	add r0, r6, #0
	str r1, [sp, #4]
	bl FUN_0200AD38
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x14]
	mov r1, #0x10
	bl ReadMsgDataIntoString
	ldr r2, [sp, #0x14]
	add r0, r6, #0
	add r1, r4, #0
	bl StringExpandPlaceholders
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	bl FUN_02002E14
	mov r1, #0xe0
	sub r3, r1, r0
	mov r1, #0
	str r1, [sp]
	ldr r0, _021D9140 ; =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r7, #0x50
	add r0, r7, #0
	add r2, r4, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	ldr r0, [sp, #0x10]
	bl DestroyMsgData
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #0x14]
	bl String_dtor
	add r0, r6, #0
	bl FUN_0200AB18
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D913C: .word 0x0000022D
_021D9140: .word 0x00010200
	thumb_func_end MOD57_021D905C

	thumb_func_start MOD57_021D9144
MOD57_021D9144: ; 0x021D9144
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	cmp r1, #0
	beq _021D9164
	mov r1, #0
	str r1, [sp]
	ldr r3, _021D9180 ; =0x00010200
	str r1, [sp, #4]
	str r3, [sp, #8]
	mov r3, #0xcd
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r4, pc}
_021D9164:
	mov r1, #5
	str r1, [sp]
	mov r1, #0x10
	str r1, [sp, #4]
	mov r1, #0
	mov r2, #0xcd
	add r3, r1, #0
	bl FUN_020196F4
	add r0, r4, #0
	bl FUN_020191D0
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D9180: .word 0x00010200
	thumb_func_end MOD57_021D9144

	thumb_func_start MOD57_021D9184
MOD57_021D9184: ; 0x021D9184
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r7, r0, #0
	bl MOD57_021D9578
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x19
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	mov r0, #0x19
	add r1, r7, #4
	add r2, r0, #0
	bl FUN_02008C9C
	ldr r4, _021D92EC ; =0x021D994C
	str r0, [r7]
	mov r6, #0
	add r5, r7, #0
_021D91BC:
	ldrb r0, [r4]
	add r1, r6, #0
	mov r2, #0x19
	bl FUN_02008DEC
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r6, r6, #1
	add r4, r4, #1
	add r5, r5, #4
	cmp r6, #4
	blt _021D91BC
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	add r0, r1, #0
	ldr r0, [r7, r0]
	mov r1, #0x33
	mov r2, #0x1c
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #9
	str r0, [sp, #8]
	mov r0, #0x19
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r7, r1]
	mov r1, #0x33
	mov r2, #0xb
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #5
	lsl r1, r1, #6
	str r0, [r7, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x19
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r7, r1]
	mov r1, #0x33
	mov r2, #0x25
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x51
	lsl r1, r1, #2
	str r0, [r7, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x19
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r7, r1]
	mov r1, #0x33
	mov r2, #0x27
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0x52
	lsl r1, r1, #2
	str r0, [r7, r1]
	sub r1, #0xc
	ldr r0, [r7, r1]
	bl FUN_02009A50
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r7, r0]
	bl FUN_02009CF0
	ldr r3, _021D92F0 ; =0x021D9960
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #0x33
	mov r1, #0x19
	bl NARC_ctor
	str r0, [sp, #0x14]
	mov r0, #0x1e
	lsl r0, r0, #4
	add r0, r7, r0
	mov r4, #0
	str r0, [sp, #0x18]
_021D9290:
	lsl r6, r4, #2
	add r1, sp, #0x1c
	ldr r0, [sp, #0x14]
	ldr r1, [r1, r6]
	mov r2, #0x19
	add r5, r7, r6
	bl NARC_AllocAndReadWholeMember
	mov r1, #7
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D92CA
	ldr r1, [sp, #0x18]
	add r1, r1, r6
	bl FUN_020B0138
	cmp r0, #0
	bne _021D92CE
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FreeToHeap
	bl ErrorHandling
	b _021D92CE
_021D92CA:
	bl ErrorHandling
_021D92CE:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #8
	blo _021D9290
	ldr r0, [sp, #0x14]
	bl NARC_dtor
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_021D92EC: .word MOD57_021D994C
_021D92F0: .word MOD57_021D9960
	thumb_func_end MOD57_021D9184

	thumb_func_start MOD57_021D92F4
MOD57_021D92F4: ; 0x021D92F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x88
	add r7, r1, #0
	mov r1, #1
	str r0, [sp, #0x2c]
	str r1, [sp]
	sub r0, r1, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r3, [sp, #0x2c]
	str r1, [sp, #0x10]
	ldr r3, [r3, r0]
	add r4, r0, #4
	str r3, [sp, #0x14]
	ldr r3, [sp, #0x2c]
	ldr r3, [r3, r4]
	add r4, r0, #0
	str r3, [sp, #0x18]
	ldr r3, [sp, #0x2c]
	add r4, #8
	ldr r3, [r3, r4]
	add r0, #0xc
	str r3, [sp, #0x1c]
	ldr r3, [sp, #0x2c]
	ldr r0, [r3, r0]
	add r3, r1, #0
	str r0, [sp, #0x20]
	str r2, [sp, #0x24]
	str r2, [sp, #0x28]
	add r0, sp, #0x64
	add r2, r1, #0
	bl FUN_02008AA4
	ldr r0, [sp, #0x2c]
	mov r4, #0
	ldr r0, [r0]
	ldr r6, _021D94B4 ; =0x021D99C0
	str r0, [sp, #0x34]
	add r0, sp, #0x64
	str r0, [sp, #0x38]
	mov r0, #1
	lsl r0, r0, #0xc
	str r4, [sp, #0x3c]
	str r4, [sp, #0x40]
	str r4, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x50]
	add r0, sp, #0x34
	strh r4, [r0, #0x20]
	mov r0, #2
	str r0, [sp, #0x58]
	mov r0, #1
	str r0, [sp, #0x5c]
	mov r0, #0x19
	ldr r5, [sp, #0x2c]
	str r0, [sp, #0x60]
_021D936E:
	ldr r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #0x3c]
	ldr r0, [r6, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x40]
	add r0, sp, #0x34
	bl FUN_0201FE94
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200BC
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r4, #0
	bl FUN_02020130
	ldrb r0, [r7, r4]
	cmp r0, #0
	bne _021D93AE
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
_021D93AE:
	add r4, r4, #1
	add r6, #8
	add r5, r5, #4
	cmp r4, #8
	blt _021D936E
	mov r0, #8
	ldr r4, _021D94B8 ; =0x021D9980
	ldr r5, [sp, #0x2c]
	str r0, [sp, #0x30]
	mov r6, #0
	mov r7, #1
_021D93C4:
	ldr r0, [r4]
	str r7, [sp, #0x58]
	lsl r0, r0, #0xc
	str r0, [sp, #0x3c]
	ldr r0, [r4, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x40]
	add r0, sp, #0x34
	bl FUN_0201FE94
	mov r1, #0x5f
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #8
	bl FUN_02020130
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, #8
	add r5, r5, #4
	cmp r6, #8
	blt _021D93C4
	ldr r0, [sp, #0x30]
	ldr r4, _021D94B8 ; =0x021D9980
	add r0, #8
	str r0, [sp, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x30]
	mov r6, #0
	lsl r1, r0, #2
	ldr r0, [sp, #0x2c]
	mov r7, #1
	add r5, r0, r1
_021D9424:
	ldr r0, [r4]
	str r7, [sp, #0x58]
	lsl r0, r0, #0xc
	str r0, [sp, #0x3c]
	ldr r0, [r4, #4]
	lsl r0, r0, #0xc
	str r0, [sp, #0x40]
	add r0, sp, #0x34
	bl FUN_0201FE94
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #9
	bl FUN_02020130
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r4, #8
	add r5, r5, #4
	cmp r6, #8
	blt _021D9424
	mov r1, #0
	add r0, sp, #0x84
	strb r1, [r0]
	mov r0, #6
	lsl r0, r0, #0x10
	str r0, [sp, #0x3c]
	mov r0, #0x22
	lsl r0, r0, #0xe
	str r0, [sp, #0x40]
	str r1, [sp, #0x58]
	mov r1, #0x57
	ldr r0, [sp, #0x2c]
	lsl r1, r1, #2
	add r4, r0, r1
	ldr r0, [sp, #0x30]
	add r0, #8
	str r0, [sp, #0x30]
	lsl r0, r0, #0x18
	lsr r5, r0, #0x16
	add r0, sp, #0x34
	bl FUN_0201FE94
	str r0, [r4, r5]
	ldr r0, [r4, r5]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, [r4, r5]
	mov r1, #0xa
	bl FUN_02020130
	ldr r0, [r4, r5]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x88
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D94B4: .word MOD57_021D99C0
_021D94B8: .word MOD57_021D9980
	thumb_func_end MOD57_021D92F4

	thumb_func_start MOD57_021D94BC
MOD57_021D94BC: ; 0x021D94BC
	push {r4, r5, r6, lr}
	mov r6, #7
	add r5, r0, #0
	mov r4, #0
	lsl r6, r6, #6
_021D94C6:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl FreeToHeap
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #8
	blo _021D94C6
	mov r0, #0x4f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02009C0C
	mov r0, #5
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_02009E04
	mov r6, #0x4b
	mov r4, #0
	lsl r6, r6, #2
_021D94F4:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r6]
	bl FUN_02008E2C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021D94F4
	ldr r0, [r5]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r4, r5, r6, pc}
	thumb_func_end MOD57_021D94BC

	thumb_func_start MOD57_021D951C
MOD57_021D951C: ; 0x021D951C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #8
	blo _021D952E
	bl ErrorHandling
_021D952E:
	cmp r6, #3
	bls _021D9536
	bl ErrorHandling
_021D9536:
	lsl r7, r4, #2
	mov r0, #0x57
	add r1, r5, r7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02020354
	mov r1, #1
	bl FUN_020B19C4
	str r0, [sp]
	lsl r0, r4, #5
	str r0, [sp, #4]
	mov r0, #0x1e
	add r1, r5, r7
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r5, r6, #5
	ldr r4, [r0, #0xc]
	mov r1, #0x20
	add r0, r4, r5
	bl DC_FlushRange
	ldr r2, [sp]
	ldr r1, [sp, #4]
	add r0, r4, r5
	add r1, r2, r1
	mov r2, #0x20
	bl GX_LoadOBJPltt
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD57_021D951C

	thumb_func_start MOD57_021D9578
MOD57_021D9578: ; 0x021D9578
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D95A4 ; =0x021D9950
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #2
	mov r1, #0x19
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D95A4: .word MOD57_021D9950
	thumb_func_end MOD57_021D9578

	thumb_func_start MOD57_021D95A8
MOD57_021D95A8: ; 0x021D95A8
	mov r2, #0
	mov r1, #0xff
_021D95AC:
	strb r2, [r0]
	strb r1, [r0, #1]
	add r2, r2, #1
	add r0, r0, #2
	cmp r2, #4
	blt _021D95AC
	bx lr
	.align 2, 0
	thumb_func_end MOD57_021D95A8

	thumb_func_start MOD57_021D95BC
MOD57_021D95BC: ; 0x021D95BC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl MOD57_021D95F4
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD57_021D9624
	cmp r0, #1
	beq _021D95F0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD57_021D965C
	cmp r0, #1
	beq _021D95F0
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD57_021D9694
	cmp r0, #1
_021D95F0:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD57_021D95BC

	thumb_func_start MOD57_021D95F4
MOD57_021D95F4: ; 0x021D95F4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r4, #0
	add r5, r7, #0
	mov r6, #0xff
_021D95FE:
	ldrb r0, [r5, #1]
	cmp r0, #0xff
	beq _021D9612
	ldrb r0, [r5]
	add r0, r0, #3
	bl FUN_020048BC
	cmp r0, #0
	bne _021D9612
	strb r6, [r5, #1]
_021D9612:
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _021D95FE
	add r0, r7, #0
	bl MOD57_021D96D8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD57_021D95F4

	thumb_func_start MOD57_021D9624
MOD57_021D9624: ; 0x021D9624
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r4, #0
	add r1, r6, #0
_021D962E:
	ldrb r0, [r1, #1]
	cmp r5, r0
	bne _021D964E
	lsl r7, r4, #1
	ldrb r0, [r6, r7]
	add r1, r5, #0
	bl MOD57_021D96F4
	ldrb r2, [r6, r7]
	add r0, r6, #0
	add r1, r4, #0
	add r3, r5, #0
	bl MOD57_021D96B0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D964E:
	add r4, r4, #1
	add r1, r1, #2
	cmp r4, #4
	blt _021D962E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD57_021D9624

	thumb_func_start MOD57_021D965C
MOD57_021D965C: ; 0x021D965C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r1, #0
	mov r4, #0
	add r1, r5, #0
_021D9666:
	ldrb r0, [r1, #1]
	cmp r0, #0xff
	bne _021D9686
	lsl r6, r4, #1
	ldrb r0, [r5, r6]
	add r1, r7, #0
	bl MOD57_021D96F4
	ldrb r2, [r5, r6]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r7, #0
	bl MOD57_021D96B0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D9686:
	add r4, r4, #1
	add r1, r1, #2
	cmp r4, #4
	blt _021D9666
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD57_021D965C

	thumb_func_start MOD57_021D9694
MOD57_021D9694: ; 0x021D9694
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrb r0, [r5, #6]
	add r4, r1, #0
	bl MOD57_021D96F4
	ldrb r2, [r5, #6]
	add r0, r5, #0
	mov r1, #3
	add r3, r4, #0
	bl MOD57_021D96B0
	mov r0, #1
	pop {r3, r4, r5, pc}
	thumb_func_end MOD57_021D9694

	thumb_func_start MOD57_021D96B0
MOD57_021D96B0: ; 0x021D96B0
	push {r4, r5}
	cmp r1, #0
	ble _021D96CE
	lsl r4, r1, #1
	add r4, r0, r4
_021D96BA:
	sub r5, r4, #2
	ldrb r5, [r5]
	sub r1, r1, #1
	strb r5, [r4]
	sub r5, r4, #1
	ldrb r5, [r5]
	strb r5, [r4, #1]
	sub r4, r4, #2
	cmp r1, #0
	bgt _021D96BA
_021D96CE:
	strb r2, [r0]
	strb r3, [r0, #1]
	pop {r4, r5}
	bx lr
	.align 2, 0
	thumb_func_end MOD57_021D96B0

	thumb_func_start MOD57_021D96D8
MOD57_021D96D8: ; 0x021D96D8
	mov r3, #0
	mov r1, #0xff
_021D96DC:
	ldrb r2, [r0]
	cmp r2, #0xff
	bne _021D96E8
	ldrb r2, [r0, #2]
	strb r2, [r0]
	strb r1, [r0, #2]
_021D96E8:
	add r3, r3, #1
	add r0, r0, #2
	cmp r3, #4
	blt _021D96DC
	bx lr
	.align 2, 0
	thumb_func_end MOD57_021D96D8

	thumb_func_start MOD57_021D96F4
MOD57_021D96F4: ; 0x021D96F4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r2, #0
	add r0, r5, #3
	add r4, r1, #0
	ldr r2, _021D9720 ; =0x00000694
	add r1, r0, #0
	bl FUN_020048A0
	ldr r2, _021D9724 ; =0x021D9A00
	lsl r3, r4, #1
	ldrh r2, [r2, r3]
	mov r3, #4
	sub r4, r3, r6
	mov r3, #0x98
	mul r3, r4
	ldr r1, _021D9728 ; =0x0000FFFF
	add r0, r5, #3
	sub r2, r2, r3
	bl FUN_02004D20
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D9720: .word 0x00000694
_021D9724: .word MOD57_021D9A00
_021D9728: .word 0x0000FFFF
	thumb_func_end MOD57_021D96F4

	.rodata
	.global MOD57_021D972C
MOD57_021D972C: ; 0x021D972C
	.byte 0x01, 0x01, 0x00, 0x02

	.global MOD57_021D9730
MOD57_021D9730: ; 0x021D9730
	.byte 0x01, 0x01, 0x00, 0x00

	.global MOD57_021D9734
MOD57_021D9734: ; 0x021D9734
	.byte 0x01, 0x03, 0x04, 0x0F, 0x0F, 0x00, 0x00, 0x00

	.global MOD57_021D973C
MOD57_021D973C: ; 0x021D973C
	.byte 0x92, 0x06, 0x00, 0x00, 0x93, 0x06, 0x00, 0x00

	.global MOD57_021D9744
MOD57_021D9744: ; 0x021D9744
	.byte 0x98, 0xB7, 0x78, 0x97, 0xFF, 0x00, 0x00, 0x00
	.word MOD57_021D972C, MOD57_021D9730

	.global MOD57_021D9754
MOD57_021D9754: ; 0x021D9754
	.word MOD57_021D9744, MOD57_021D9744, MOD57_021D9744, MOD57_021D9828

	.global MOD57_021D9764
MOD57_021D9764: ; 0x021D9764
	.byte 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D9774
MOD57_021D9774: ; 0x021D9774
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D9790
MOD57_021D9790: ; 0x021D9790
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D97AC
MOD57_021D97AC: ; 0x021D97AC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1D, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D97C8
MOD57_021D97C8: ; 0x021D97C8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1D, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D97E4
MOD57_021D97E4: ; 0x021D97E4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D9800
MOD57_021D9800: ; 0x021D9800
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD57_021D9828
MOD57_021D9828: ; 0x021D9828
	.byte 0x98, 0xB7, 0x78, 0x97, 0x28, 0x4F, 0x18, 0x3F
	.byte 0x28, 0x4F, 0x50, 0x77, 0x28, 0x4F, 0x88, 0xA7, 0x28, 0x4F, 0xC0, 0xE7, 0x60, 0x87, 0x18, 0x3F
	.byte 0x60, 0x87, 0x50, 0x77, 0x60, 0x87, 0x88, 0xA7, 0x60, 0x87, 0xC0, 0xE7, 0xFF, 0x00, 0x00, 0x00

	.global MOD57_021D9850
MOD57_021D9850: ; 0x021D9850
	.byte 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00

	.global MOD57_021D9888
MOD57_021D9888: ; 0x021D9888
	.byte 0x39, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00
	.byte 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00
	.byte 0x35, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00
	.byte 0x31, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00

	.global MOD57_021D98C8
MOD57_021D98C8: ; 0x021D98C8
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00

	.global MOD57_021D98F4
MOD57_021D98F4: ; 0x021D98F4
	.byte 0x07, 0x02, 0x04, 0x11, 0x02, 0x0F, 0x6F, 0x00, 0x07, 0x02, 0x06, 0x11, 0x02, 0x0F, 0x91, 0x00
	.byte 0x07, 0x02, 0x09, 0x11, 0x02, 0x0F, 0xB3, 0x00, 0x07, 0x02, 0x0C, 0x11, 0x02, 0x0F, 0xD5, 0x00
	.byte 0x07, 0x02, 0x0F, 0x11, 0x02, 0x0F, 0xF7, 0x00, 0x07, 0x02, 0x12, 0x1C, 0x02, 0x0F, 0x19, 0x01
	.byte 0x07, 0x02, 0x14, 0x1C, 0x02, 0x0F, 0x51, 0x01, 0x07, 0x02, 0x02, 0x1C, 0x04, 0x0F, 0xC1, 0x00
	.byte 0x07, 0x02, 0x07, 0x1C, 0x02, 0x0F, 0x31, 0x01, 0x07, 0x02, 0x09, 0x1C, 0x02, 0x0F, 0x69, 0x01
	.byte 0x07, 0x02, 0x0B, 0x1C, 0x02, 0x0F, 0xA1, 0x01

	.global MOD57_021D994C
MOD57_021D994C: ; 0x021D994C
	.byte 0x01, 0x02, 0x01, 0x01

	.global MOD57_021D9950
MOD57_021D9950: ; 0x021D9950
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00

	.global MOD57_021D9960
MOD57_021D9960: ; 0x021D9960
	.byte 0x0D, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00

	.global MOD57_021D9980
MOD57_021D9980: ; 0x021D9980
	.byte 0x18, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD57_021D99C0
MOD57_021D99C0: ; 0x021D99C0
	.byte 0x18, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x18, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00
	.byte 0x88, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00

	.global MOD57_021D9A00
MOD57_021D9A00: ; 0x021D9A00
	.byte 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x40, 0x01, 0xC0, 0x01, 0x40, 0x02, 0xC0, 0x02, 0x00, 0x03

	.data
	.bss
