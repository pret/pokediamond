	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov04_021D74E0
ov04_021D74E0: ; 0x021D74E0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021D7644 ; =ov04_0220FBC0
	add r4, r1, #0
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021D74F2
	bl GF_AssertFail
_021D74F2:
	ldr r1, _021D7648 ; =0x00001FAC
	add r0, r4, #0
	bl AllocFromHeap
	ldr r2, _021D7644 ; =ov04_0220FBC0
	mov r1, #0x1f
	str r0, [r2, #4]
	add r0, #0x1f
	bic r0, r1
	mov r1, #0x1f
	lsl r1, r1, #8
	str r0, [r2]
	str r5, [r0, r1]
	add r3, r1, #0
	ldr r6, [r2]
	mov r0, #0
	add r3, #0xc
	str r0, [r6, r3]
	add r3, r1, #0
	ldr r6, [r2]
	add r3, #0x10
	str r0, [r6, r3]
	add r3, r1, #0
	ldr r6, [r2]
	add r3, #0x14
	str r0, [r6, r3]
	add r3, r1, #0
	ldr r6, [r2]
	add r3, #0x44
	str r0, [r6, r3]
	ldr r0, [r2]
	add r1, #0x54
	str r4, [r0, r1]
	ldr r1, _021D764C ; =0x0002B020
	add r0, r4, #0
	bl AllocFromHeap
	ldr r2, _021D7644 ; =ov04_0220FBC0
	ldr r1, _021D7650 ; =0x00001F04
	ldr r3, [r2]
	str r0, [r3, r1]
	ldr r0, [r2]
	mov r2, #0
	ldr r0, [r0, r1]
	mov r1, #0x1f
	add r0, #0x1f
	bic r0, r1
	mov r1, #0x2b
	lsl r1, r1, #0xc
	bl NNS_FndCreateExpHeapEx
	ldr r1, _021D7644 ; =ov04_0220FBC0
	ldr r3, _021D7654 ; =0x00001F08
	ldr r2, [r1]
	str r0, [r2, r3]
	add r0, r3, #0
	ldr r4, [r1]
	mov r2, #0
	add r0, #0x64
	str r2, [r4, r0]
	add r4, r3, #0
	ldr r6, [r1]
	sub r0, r2, #1
	add r4, #0x54
	str r0, [r6, r4]
	add r4, r3, #0
	ldr r6, [r1]
	add r4, #0x38
	str r2, [r6, r4]
	add r4, r3, #0
	ldr r6, [r1]
	add r4, #0x48
	str r0, [r6, r4]
	add r4, r3, #0
	ldr r6, [r1]
	add r4, #0x58
	str r0, [r6, r4]
	add r0, r3, #0
	ldr r4, [r1]
	add r0, #0x5c
	str r2, [r4, r0]
	add r4, r3, #0
	ldr r6, [r1]
	mov r0, #1
	add r4, #0x60
	str r0, [r6, r4]
	add r4, r3, #0
	ldr r6, [r1]
	add r4, #0x7a
	strb r2, [r6, r4]
	add r4, r3, #0
	ldr r6, [r1]
	add r4, #0x78
	strb r2, [r6, r4]
	add r4, r3, #0
	ldr r6, [r1]
	add r4, #0x79
	strb r2, [r6, r4]
	add r2, r3, #0
	ldr r4, [r1]
	add r2, #0x70
	str r0, [r4, r2]
	add r2, r3, #0
	add r2, #0x74
	ldr r4, [r1]
	cmp r5, #0
	str r0, [r4, r2]
	beq _021D75FA
	ldr r0, [r1]
	sub r3, #8
	ldr r0, [r0, r3]
	bl sub_020286EC
	bl sub_02028228
	ldr r2, _021D7644 ; =ov04_0220FBC0
	ldr r1, _021D7658 ; =0x00001EF0
	ldr r3, [r2]
	str r0, [r3, r1]
	ldr r0, [r2]
	add r1, #0x10
	ldr r0, [r0, r1]
	bl sub_020286EC
	mov r1, #0
	bl sub_0202838C
	ldr r1, _021D7644 ; =ov04_0220FBC0
	ldr r2, [r1]
	mov r1, #0x11
	lsl r1, r1, #8
	str r0, [r2, r1]
_021D75FA:
	ldr r2, _021D7644 ; =ov04_0220FBC0
	mov r0, #0
	ldr r3, [r2]
	ldr r1, _021D765C ; =0x00001F38
	add r4, r0, #0
	str r0, [r3, r1]
	sub r1, #0x20
_021D7608:
	ldr r3, [r2]
	add r3, r3, r0
	add r0, r0, #1
	strb r4, [r3, r1]
	cmp r0, #0x20
	blt _021D7608
	bl ov04_021D85B4
	ldr r0, _021D7644 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7658 ; =0x00001EF0
	ldr r0, [r1, r0]
	bl DWC_CheckHasProfile
	cmp r0, #0
	bne _021D762C
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D762C:
	ldr r0, _021D7644 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7658 ; =0x00001EF0
	ldr r0, [r1, r0]
	bl DWC_CheckValidConsole
	cmp r0, #0
	beq _021D7640
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D7640:
	mov r0, #2
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D7644: .word ov04_0220FBC0
_021D7648: .word 0x00001FAC
_021D764C: .word 0x0002B020
_021D7650: .word 0x00001F04
_021D7654: .word 0x00001F08
_021D7658: .word 0x00001EF0
_021D765C: .word 0x00001F38

	thumb_func_start ov04_021D7660
ov04_021D7660: ; 0x021D7660
	push {r3, lr}
	ldr r0, _021D76A0 ; =ov04_0220FBC0
	ldr r1, [r0]
	cmp r1, #0
	beq _021D7698
	ldr r0, _021D76A4 ; =0x00001F08
	ldr r0, [r1, r0]
	bl NNS_FndDestroyExpHeap
	ldr r0, _021D76A0 ; =ov04_0220FBC0
	ldr r1, _021D76A8 ; =0x00001F54
	ldr r2, [r0]
	ldr r0, [r2, r1]
	sub r1, #0x50
	ldr r1, [r2, r1]
	bl FreeToHeapExplicit
	ldr r1, _021D76A0 ; =ov04_0220FBC0
	ldr r0, _021D76A8 ; =0x00001F54
	ldr r2, [r1]
	ldr r1, [r1, #4]
	ldr r0, [r2, r0]
	bl FreeToHeapExplicit
	ldr r0, _021D76A0 ; =ov04_0220FBC0
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0]
_021D7698:
	bl ov04_021DD6F0
	pop {r3, pc}
	nop
_021D76A0: .word ov04_0220FBC0
_021D76A4: .word 0x00001F08
_021D76A8: .word 0x00001F54

	thumb_func_start ov04_021D76AC
ov04_021D76AC: ; 0x021D76AC
	push {lr}
	sub sp, #0x64
	ldr r0, _021D779C ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D77A0 ; =0x00001F44
	ldr r0, [r1, r0]
	cmp r0, #4
	bhi _021D7794
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D76C8: ; jump table
	.short _021D76D2 - _021D76C8 - 2 ; case 0
	.short _021D7708 - _021D76C8 - 2 ; case 1
	.short _021D7736 - _021D76C8 - 2 ; case 2
	.short _021D7784 - _021D76C8 - 2 ; case 3
	.short _021D778A - _021D76C8 - 2 ; case 4
_021D76D2:
	ldr r0, _021D77A4 ; =ov04_021D7DA8
	ldr r1, _021D77A8 ; =ov04_021D7DEC
	bl ov04_021DD968
	ldr r0, _021D779C ; =ov04_0220FBC0
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _021D77AC ; =0x00001EF4
	mov r3, #0x14
	add r0, r1, r0
	mov r1, #2
	bl ov04_021DDEE0
	mov r0, #2
	bl ov04_021DDE7C
	bl ov04_021DDDCC
	ldr r1, _021D779C ; =ov04_0220FBC0
	ldr r0, _021D77A0 ; =0x00001F44
	ldr r2, [r1]
	mov r3, #1
	str r3, [r2, r0]
	ldr r1, [r1]
	mov r2, #0
	add r0, #0x14
	str r2, [r1, r0]
_021D7708:
	bl ov04_021DDD7C
	cmp r0, #0
	beq _021D7730
	bl ov04_021DDC1C
	cmp r0, #4
	bne _021D7724
	ldr r0, _021D779C ; =ov04_0220FBC0
	mov r2, #2
	ldr r1, [r0]
	ldr r0, _021D77A0 ; =0x00001F44
	str r2, [r1, r0]
	b _021D7736
_021D7724:
	ldr r0, _021D779C ; =ov04_0220FBC0
	mov r2, #0xb
	ldr r1, [r0]
	ldr r0, _021D77A0 ; =0x00001F44
	str r2, [r1, r0]
	b _021D7736
_021D7730:
	bl ov04_021DDCE8
	b _021D7794
_021D7736:
	bl ov04_021D7E18
	cmp r0, #0
	blt _021D7798
	ldr r0, _021D779C ; =ov04_0220FBC0
	ldr r3, _021D77B0 ; =ov04_0220BEA0
	ldr r1, [r0]
	ldr r0, _021D77B4 ; =ov04_0220BEAC
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x11
	lsl r0, r0, #8
	ldr r2, [r1, r0]
	add r0, r0, #4
	str r2, [sp, #0xc]
	mov r2, #0x20
	str r2, [sp, #0x10]
	ldr r2, _021D77B8 ; =0x00001EF0
	add r0, r1, r0
	ldr r1, [r1, r2]
	ldr r2, _021D77BC ; =0x000029E7
	bl ov04_021E0374
	add r0, sp, #0x14
	bl OS_GetOwnerInfo
	mov r1, #0
	ldr r2, _021D77C0 ; =ov04_021D7A7C
	add r0, sp, #0x18
	add r3, r1, #0
	bl ov04_021DFE64
	ldr r0, _021D779C ; =ov04_0220FBC0
	mov r2, #3
	ldr r1, [r0]
	ldr r0, _021D77A0 ; =0x00001F44
	str r2, [r1, r0]
_021D7784:
	bl ov04_021DFF74
	b _021D7794
_021D778A:
	bl ov04_021DFF74
	add sp, #0x64
	mov r0, #1
	pop {pc}
_021D7794:
	bl ov04_021D7E18
_021D7798:
	add sp, #0x64
	pop {pc}
	.align 2, 0
_021D779C: .word ov04_0220FBC0
_021D77A0: .word 0x00001F44
_021D77A4: .word ov04_021D7DA8
_021D77A8: .word ov04_021D7DEC
_021D77AC: .word 0x00001EF4
_021D77B0: .word ov04_0220BEA0
_021D77B4: .word ov04_0220BEAC
_021D77B8: .word 0x00001EF0
_021D77BC: .word 0x000029E7
_021D77C0: .word ov04_021D7A7C

	thumb_func_start ov04_021D77C4
ov04_021D77C4: ; 0x021D77C4
	push {r3, r4}
	ldr r3, _021D77D8 ; =ov04_0220FBC0
	ldr r2, _021D77DC ; =0x00001F0C
	ldr r4, [r3]
	str r0, [r4, r2]
	ldr r3, [r3]
	add r0, r2, #4
	str r1, [r3, r0]
	pop {r3, r4}
	bx lr
	.align 2, 0
_021D77D8: .word ov04_0220FBC0
_021D77DC: .word 0x00001F0C

	thumb_func_start ov04_021D77E0
ov04_021D77E0: ; 0x021D77E0
	ldr r0, _021D77F8 ; =ov04_0220FBC0
	ldr r2, [r0]
	ldr r0, _021D77FC ; =0x00001F44
	ldr r1, [r2, r0]
	cmp r1, #9
	bne _021D77F2
	mov r1, #0xa
	str r1, [r2, r0]
	bx lr
_021D77F2:
	mov r1, #8
	str r1, [r2, r0]
	bx lr
	.align 2, 0
_021D77F8: .word ov04_0220FBC0
_021D77FC: .word 0x00001F44

	thumb_func_start ov04_021D7800
ov04_021D7800: ; 0x021D7800
	push {r3, r4, r5, lr}
	ldr r2, _021D78EC ; =ov04_0220FBC0
	ldr r1, _021D78F0 ; =0x00001F44
	ldr r4, [r2]
	ldr r3, [r4, r1]
	cmp r3, #0xb
	bhi _021D78E4
	add r5, r3, r3
	add r5, pc
	ldrh r5, [r5, #6]
	lsl r5, r5, #0x10
	asr r5, r5, #0x10
	add pc, r5
_021D781A: ; jump table
	.short _021D78E4 - _021D781A - 2 ; case 0
	.short _021D78E4 - _021D781A - 2 ; case 1
	.short _021D78E4 - _021D781A - 2 ; case 2
	.short _021D78E4 - _021D781A - 2 ; case 3
	.short _021D78E4 - _021D781A - 2 ; case 4
	.short _021D7832 - _021D781A - 2 ; case 5
	.short _021D7864 - _021D781A - 2 ; case 6
	.short _021D7886 - _021D781A - 2 ; case 7
	.short _021D78AA - _021D781A - 2 ; case 8
	.short _021D7864 - _021D781A - 2 ; case 9
	.short _021D78C4 - _021D781A - 2 ; case 10
	.short _021D78DE - _021D781A - 2 ; case 11
_021D7832:
	cmp r0, #0
	beq _021D783A
	mov r0, #6
	str r0, [r4, r1]
_021D783A:
	ldr r0, _021D78EC ; =ov04_0220FBC0
	ldr r2, _021D78F4 ; =0x00001F48
	ldr r0, [r0]
	ldr r1, [r0, r2]
	cmp r1, #2
	bne _021D78E4
	add r1, r2, #0
	add r1, #0x14
	ldr r1, [r0, r1]
	cmp r1, #0
	blt _021D78E4
	add r3, r0, r1
	add r1, r2, #0
	sub r1, #0x30
	ldrb r1, [r3, r1]
	cmp r1, #6
	beq _021D78E4
	mov r3, #9
	sub r1, r2, #4
	str r3, [r0, r1]
	b _021D78E4
_021D7864:
	cmp r3, #0
	bne _021D786E
	bl ov04_021EA530
	b _021D78E4
_021D786E:
	bl ov04_021DFA40
	cmp r0, #1
	bne _021D787C
	bl ov04_021D77E0
	b _021D78E4
_021D787C:
	cmp r0, #0
	beq _021D78E4
	bl ov04_021D77E0
	b _021D78E4
_021D7886:
	mov r0, #1
	add r1, #0x40
	strh r0, [r4, r1]
	bl ov04_021D8058
	ldr r0, _021D78EC ; =ov04_0220FBC0
	ldr r2, [r0]
	ldr r0, _021D78F8 ; =0x00001F68
	ldr r1, [r2, r0]
	cmp r1, #0
	beq _021D78A0
	mov r1, #1
	b _021D78A2
_021D78A0:
	mov r1, #0
_021D78A2:
	add r0, #0x10
	str r1, [r2, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D78AA:
	mov r0, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r3, [r2]
	mov r4, #0
	add r0, #8
	str r4, [r3, r0]
	ldr r0, [r2]
	sub r3, r4, #1
	add r1, #0x1c
	str r3, [r0, r1]
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D78C4:
	mov r0, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r3, [r2]
	mov r4, #0
	add r0, #8
	str r4, [r3, r0]
	ldr r0, [r2]
	sub r3, r4, #1
	add r1, #0x1c
	str r3, [r0, r1]
	mov r0, #3
	pop {r3, r4, r5, pc}
_021D78DE:
	bl ov04_021D7E18
	pop {r3, r4, r5, pc}
_021D78E4:
	bl ov04_021D7F8C
	pop {r3, r4, r5, pc}
	nop
_021D78EC: .word ov04_0220FBC0
_021D78F0: .word 0x00001F44
_021D78F4: .word 0x00001F48
_021D78F8: .word 0x00001F68

	thumb_func_start ov04_021D78FC
ov04_021D78FC: ; 0x021D78FC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #1
	add r4, r1, #0
	lsl r0, r0, #8
	cmp r4, r0
	blt _021D790E
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D790E:
	bl ov04_021DF95C
	cmp r0, #0
	bne _021D7930
	ldr r0, _021D79A0 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D79A4 ; =0x00001F0C
	ldr r3, [r1, r0]
	cmp r3, #0
	beq _021D792C
	lsl r2, r4, #0x10
	mov r0, #0
	add r1, r5, #0
	lsr r2, r2, #0x10
	blx r3
_021D792C:
	mov r0, #1
	pop {r4, r5, r6, pc}
_021D7930:
	ldr r0, _021D79A0 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D79A8 ; =0x00001F4C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _021D7946
	mov r0, #0
	bl ov04_021EB0FC
	cmp r0, #0
	bne _021D794A
_021D7946:
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D794A:
	ldr r1, _021D79A0 ; =ov04_0220FBC0
	ldr r0, _021D79AC ; =0x00001F78
	ldr r3, [r1]
	mov r6, #1
	ldr r2, [r3, r0]
	lsl r2, r2, #8
	orr r2, r6
	lsl r6, r6, #0xc
	str r2, [r3, r6]
	add r3, r0, #0
	ldr r2, [r1]
	add r3, #8
	ldrb r3, [r2, r3]
	add r6, r3, #1
	add r3, r0, #0
	add r3, #8
	strb r6, [r2, r3]
	ldr r3, [r1]
	add r0, #8
	ldrb r0, [r3, r0]
	ldr r2, _021D79B0 ; =0x00001002
	strb r0, [r3, r2]
	ldr r3, [r1]
	add r1, r2, #2
	add r0, r5, #0
	add r1, r3, r1
	add r2, r4, #0
	bl MI_CpuCopy8
	ldr r1, _021D79A0 ; =ov04_0220FBC0
	ldr r0, _021D79A8 ; =0x00001F4C
	ldr r2, [r1]
	mov r3, #1
	str r3, [r2, r0]
	ldr r2, [r1]
	lsl r1, r3, #0xc
	add r1, r2, r1
	mov r0, #0
	add r2, r4, #4
	bl ov04_021EB044
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D79A0: .word ov04_0220FBC0
_021D79A4: .word 0x00001F0C
_021D79A8: .word 0x00001F4C
_021D79AC: .word 0x00001F78
_021D79B0: .word 0x00001002

	thumb_func_start ov04_021D79B4
ov04_021D79B4: ; 0x021D79B4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #1
	add r4, r1, #0
	lsl r0, r0, #8
	cmp r4, r0
	blt _021D79C6
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D79C6:
	bl ov04_021DF95C
	cmp r0, #0
	beq _021D79D2
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D79D2:
	ldr r0, _021D7A68 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7A6C ; =0x00001F4C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _021D79E8
	mov r0, #1
	bl ov04_021EB0FC
	cmp r0, #0
	bne _021D79EC
_021D79E8:
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D79EC:
	ldr r1, _021D7A68 ; =ov04_0220FBC0
	ldr r0, _021D7A70 ; =0x00001F78
	ldr r3, [r1]
	mov r6, #1
	ldr r2, [r3, r0]
	lsl r2, r2, #8
	orr r2, r6
	lsl r6, r6, #0xc
	str r2, [r3, r6]
	add r3, r0, #0
	ldr r2, [r1]
	add r3, #8
	ldrb r3, [r2, r3]
	add r6, r3, #1
	add r3, r0, #0
	add r3, #8
	strb r6, [r2, r3]
	ldr r3, [r1]
	add r0, #8
	ldrb r0, [r3, r0]
	ldr r2, _021D7A74 ; =0x00001002
	strb r0, [r3, r2]
	ldr r3, [r1]
	add r1, r2, #2
	add r0, r5, #0
	add r1, r3, r1
	add r2, r4, #0
	bl MI_CpuCopy8
	ldr r2, _021D7A68 ; =ov04_0220FBC0
	ldr r1, _021D7A6C ; =0x00001F4C
	ldr r3, [r2]
	mov r0, #1
	str r0, [r3, r1]
	ldr r2, [r2]
	lsl r1, r0, #0xc
	add r1, r2, r1
	add r2, r4, #4
	bl ov04_021EB044
	cmp r0, #0
	bne _021D7A4C
	ldr r1, _021D7A68 ; =ov04_0220FBC0
	mov r0, #0
	ldr r2, [r1]
	ldr r1, _021D7A6C ; =0x00001F4C
	str r0, [r2, r1]
	pop {r4, r5, r6, pc}
_021D7A4C:
	ldr r0, _021D7A68 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7A78 ; =0x00001F10
	ldr r3, [r1, r0]
	cmp r3, #0
	beq _021D7A62
	lsl r2, r4, #0x10
	mov r0, #0
	add r1, r5, #0
	lsr r2, r2, #0x10
	blx r3
_021D7A62:
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_021D7A68: .word ov04_0220FBC0
_021D7A6C: .word 0x00001F4C
_021D7A70: .word 0x00001F78
_021D7A74: .word 0x00001002
_021D7A78: .word 0x00001F10

	thumb_func_start ov04_021D7A7C
ov04_021D7A7C: ; 0x021D7A7C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _021D7AF8 ; =ov04_0220FBC0
	add r4, r2, #0
	ldr r1, [r0]
	ldr r0, _021D7AFC ; =0x00001EF0
	ldr r0, [r1, r0]
	bl DWC_CheckDirtyFlag
	cmp r0, #0
	beq _021D7AB0
	ldr r0, _021D7AF8 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7AFC ; =0x00001EF0
	ldr r0, [r1, r0]
	bl DWC_ClearDirtyFlag
	ldr r0, _021D7AF8 ; =ov04_0220FBC0
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	mov r1, #0
	bl sub_020227A0
_021D7AB0:
	cmp r5, #0
	bne _021D7AE8
	ldr r0, _021D7B00 ; =ov04_021D7B70
	str r4, [sp]
	str r0, [sp, #4]
	ldr r2, _021D7AF8 ; =ov04_0220FBC0
	str r4, [sp, #8]
	ldr r3, [r2]
	ldr r2, _021D7AFC ; =0x00001EF0
	ldr r1, _021D7B04 ; =ov04_021D7B48
	ldr r2, [r3, r2]
	ldr r3, _021D7B08 ; =ov04_021D7B6C
	mov r0, #0
	bl ov04_021DFDBC
	cmp r0, #0
	bne _021D7ADC
	mov r0, #1
	bl sub_020336A0
	add sp, #0xc
	pop {r4, r5, pc}
_021D7ADC:
	ldr r0, _021D7B0C ; =ov04_021D7BBC
	mov r1, #0
	bl ov04_021E242C
	add sp, #0xc
	pop {r4, r5, pc}
_021D7AE8:
	ldr r0, _021D7AF8 ; =ov04_0220FBC0
	mov r2, #0xb
	ldr r1, [r0]
	ldr r0, _021D7B10 ; =0x00001F44
	str r2, [r1, r0]
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D7AF8: .word ov04_0220FBC0
_021D7AFC: .word 0x00001EF0
_021D7B00: .word ov04_021D7B70
_021D7B04: .word ov04_021D7B48
_021D7B08: .word ov04_021D7B6C
_021D7B0C: .word ov04_021D7BBC
_021D7B10: .word 0x00001F44

	thumb_func_start ov04_021D7B14
ov04_021D7B14: ; 0x021D7B14
	push {r3, lr}
	ldr r0, _021D7B3C ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7B40 ; =0x00001F70
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021D7B3A
	bl ov04_021DFA40
	ldr r1, _021D7B3C ; =ov04_0220FBC0
	mov r3, #0
	ldr r2, [r1]
	ldr r0, _021D7B44 ; =0x00001F60
	mvn r3, r3
	str r3, [r2, r0]
	ldr r1, [r1]
	mov r2, #0x11
	sub r0, #0x1c
	str r2, [r1, r0]
_021D7B3A:
	pop {r3, pc}
	.align 2, 0
_021D7B3C: .word ov04_0220FBC0
_021D7B40: .word 0x00001F70
_021D7B44: .word 0x00001F60

	thumb_func_start ov04_021D7B48
ov04_021D7B48: ; 0x021D7B48
	cmp r0, #0
	bne _021D7B58
	ldr r0, _021D7B64 ; =ov04_0220FBC0
	mov r2, #4
	ldr r1, [r0]
	ldr r0, _021D7B68 ; =0x00001F44
	str r2, [r1, r0]
	bx lr
_021D7B58:
	ldr r0, _021D7B64 ; =ov04_0220FBC0
	mov r2, #0xb
	ldr r1, [r0]
	ldr r0, _021D7B68 ; =0x00001F44
	str r2, [r1, r0]
	bx lr
	.align 2, 0
_021D7B64: .word ov04_0220FBC0
_021D7B68: .word 0x00001F44

	thumb_func_start ov04_021D7B6C
ov04_021D7B6C: ; 0x021D7B6C
	bx lr
	.align 2, 0

	thumb_func_start ov04_021D7B70
ov04_021D7B70: ; 0x021D7B70
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D7BB8 ; =ov04_0220FBC0
	add r4, r1, #0
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	bl sub_020286EC
	mov r1, #0
	bl sub_0202838C
	add r1, r0, #0
	ldr r0, _021D7BB8 ; =ov04_0220FBC0
	ldr r2, [r0]
	mov r0, #0x11
	lsl r0, r0, #8
	ldr r0, [r2, r0]
	mov r2, #6
	lsl r2, r2, #6
	bl MI_CpuCopy8
	ldr r0, _021D7BB8 ; =ov04_0220FBC0
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	bl sub_020286EC
	add r1, r5, #0
	add r2, r4, #0
	bl sub_02028664
	pop {r3, r4, r5, pc}
	nop
_021D7BB8: .word ov04_0220FBC0

	thumb_func_start ov04_021D7BBC
ov04_021D7BBC: ; 0x021D7BBC
	bx lr
	.align 2, 0

	thumb_func_start ov04_021D7BC0
ov04_021D7BC0: ; 0x021D7BC0
	push {r3, lr}
	ldr r0, _021D7C1C ; =ov04_0220FBC0
	mov r2, #7
	ldr r1, [r0]
	ldr r0, _021D7C20 ; =0x00001F44
	str r2, [r1, r0]
	bl ov04_021DF95C
	cmp r0, #0
	bne _021D7BDA
	mov r2, #1
	ldr r0, _021D7C1C ; =ov04_0220FBC0
	b _021D7BDE
_021D7BDA:
	ldr r0, _021D7C1C ; =ov04_0220FBC0
	mov r2, #0
_021D7BDE:
	ldr r1, [r0]
	ldr r0, _021D7C24 ; =0x00001F50
	str r2, [r1, r0]
	ldr r0, _021D7C1C ; =ov04_0220FBC0
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _021D7C24 ; =0x00001F50
	lsl r2, r2, #0xc
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl ov04_021EAE38
	ldr r0, _021D7C1C ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7C24 ; =0x00001F50
	ldr r0, [r1, r0]
	ldr r1, _021D7C28 ; =0x00002710
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl ov04_021EACF8
	ldr r1, _021D7C1C ; =ov04_0220FBC0
	ldr r0, _021D7C2C ; =0x00001F70
	ldr r2, [r1]
	mov r3, #0
	str r3, [r2, r0]
	ldr r1, [r1]
	add r0, r0, #4
	str r3, [r1, r0]
	pop {r3, pc}
	.align 2, 0
_021D7C1C: .word ov04_0220FBC0
_021D7C20: .word 0x00001F44
_021D7C24: .word 0x00001F50
_021D7C28: .word 0x00002710
_021D7C2C: .word 0x00001F70

	thumb_func_start ov04_021D7C30
ov04_021D7C30: ; 0x021D7C30
	ldr r1, _021D7C44 ; =ov04_0220FBC0
	ldr r0, _021D7C48 ; =0x00001F4C
	ldr r2, [r1]
	mov r3, #0
	str r3, [r2, r0]
	ldr r1, [r1]
	add r0, #0x28
	str r3, [r1, r0]
	bx lr
	nop
_021D7C44: .word ov04_0220FBC0
_021D7C48: .word 0x00001F4C

	thumb_func_start ov04_021D7C4C
ov04_021D7C4C: ; 0x021D7C4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	add r4, r1, #0
	ldrb r5, [r4, #1]
	ldrb r3, [r4]
	str r2, [sp, #4]
	lsl r5, r5, #8
	mov ip, r5
	ldrb r5, [r4, #3]
	add r7, r3, #0
	ldr r3, _021D7D54 ; =ov04_0220FBC0
	lsl r6, r5, #0x18
	ldrb r5, [r4, #2]
	lsl r5, r5, #0x10
	orr r5, r6
	mov r6, ip
	orr r5, r6
	orr r7, r5
	ldr r6, [r3]
	ldr r5, _021D7D58 ; =0x00001F70
	mov r3, #1
	str r3, [r6, r5]
	lsl r3, r7, #0x18
	lsr r3, r3, #0x18
	cmp r3, #1
	bne _021D7CB4
	mov r0, #1
	add r0, #0xff
	tst r0, r7
	beq _021D7C96
	ldr r0, _021D7D54 ; =ov04_0220FBC0
	add r5, #0xc
	ldr r1, [r0]
	mov r0, #1
	str r0, [r1, r5]
	b _021D7CA0
_021D7C96:
	ldr r0, _021D7D54 ; =ov04_0220FBC0
	mov r1, #0
	ldr r0, [r0]
	add r5, #0xc
	str r1, [r0, r5]
_021D7CA0:
	ldr r3, _021D7D54 ; =ov04_0220FBC0
	ldr r1, _021D7D5C ; =0x00001F84
	ldr r2, [r3]
	mov r0, #0
	strh r0, [r2, r1]
	ldrb r6, [r4, #2]
	ldr r5, [r3]
	sub r2, r1, #3
	strb r6, [r5, r2]
	b _021D7CE4
_021D7CB4:
	bl ov04_021D8A54
	cmp r0, #0
	bne _021D7D4E
	mov r0, #1
	lsl r0, r0, #8
	tst r0, r7
	beq _021D7CD4
	ldr r0, _021D7D54 ; =ov04_0220FBC0
	mov r2, #1
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc
	str r2, [r1, r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021D7CD4:
	ldr r0, _021D7D54 ; =ov04_0220FBC0
	mov r2, #0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc
	str r2, [r1, r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_021D7CE4:
	ldr r5, [r4]
	ldr r2, [r3]
	add r1, r1, #4
	str r5, [r2, r1]
	ldr r1, [sp, #4]
	mov r2, #4
	sub r6, r1, #4
	add r1, r6, #0
	bl ov04_021D7DA8
	add r5, r0, #0
	beq _021D7D4E
	add r0, r4, #4
	add r1, r5, #0
	add r2, r6, #0
	bl MI_CpuCopy8
	bl ov04_021DF95C
	cmp r0, #0
	bne _021D7D2A
	ldr r0, _021D7D54 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7D60 ; =0x00001F0C
	ldr r3, [r1, r0]
	cmp r3, #0
	beq _021D7D44
	ldr r2, [sp, #4]
	ldr r0, [sp]
	sub r2, r2, #4
	lsl r2, r2, #0x10
	add r1, r5, #0
	lsr r2, r2, #0x10
	blx r3
	b _021D7D44
_021D7D2A:
	ldr r0, _021D7D54 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7D64 ; =0x00001F10
	ldr r3, [r1, r0]
	cmp r3, #0
	beq _021D7D44
	ldr r2, [sp, #4]
	ldr r0, [sp]
	sub r2, r2, #4
	lsl r2, r2, #0x10
	add r1, r5, #0
	lsr r2, r2, #0x10
	blx r3
_021D7D44:
	mov r0, #0
	add r1, r5, #0
	add r2, r6, #0
	bl ov04_021D7DEC
_021D7D4E:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7D54: .word ov04_0220FBC0
_021D7D58: .word 0x00001F70
_021D7D5C: .word 0x00001F84
_021D7D60: .word 0x00001F0C
_021D7D64: .word 0x00001F10

	thumb_func_start ov04_021D7D68
ov04_021D7D68: ; 0x021D7D68
	push {r3, lr}
	cmp r0, #0
	bne _021D7D9A
	bl ov04_021DF978
	cmp r0, #1
	bne _021D7D9A
	ldr r0, _021D7D9C ; =ov04_0220FBC0
	ldr r2, [r0]
	ldr r0, _021D7DA0 ; =0x00001F44
	ldr r1, [r2, r0]
	cmp r1, #6
	bne _021D7D86
	mov r1, #8
	b _021D7D88
_021D7D86:
	mov r1, #0x10
_021D7D88:
	str r1, [r2, r0]
	ldr r0, _021D7D9C ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7DA4 ; =0x00001F58
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021D7D9A
	bl ov04_021D8C6C
_021D7D9A:
	pop {r3, pc}
	.align 2, 0
_021D7D9C: .word ov04_0220FBC0
_021D7DA0: .word 0x00001F44
_021D7DA4: .word 0x00001F58

	thumb_func_start ov04_021D7DA8
ov04_021D7DA8: ; 0x021D7DA8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r2, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _021D7DE4 ; =ov04_0220FBC0
	add r2, r6, #0
	ldr r1, [r0]
	ldr r0, _021D7DE8 ; =0x00001F08
	ldr r0, [r1, r0]
	add r1, r5, #0
	bl NNS_FndAllocFromExpHeapEx
	add r5, r0, #0
	bne _021D7DD8
	mov r0, #1
	bl sub_020336A0
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D7DD8:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	add r0, r5, #0
	pop {r4, r5, r6, pc}
	nop
_021D7DE4: .word ov04_0220FBC0
_021D7DE8: .word 0x00001F08

	thumb_func_start ov04_021D7DEC
ov04_021D7DEC: ; 0x021D7DEC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	beq _021D7E0C
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _021D7E10 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7E14 ; =0x00001F08
	ldr r0, [r1, r0]
	add r1, r5, #0
	bl NNS_FndFreeToExpHeap
	add r0, r4, #0
	bl OS_RestoreInterrupts
_021D7E0C:
	pop {r3, r4, r5, pc}
	nop
_021D7E10: .word ov04_0220FBC0
_021D7E14: .word 0x00001F08

	thumb_func_start ov04_021D7E18
ov04_021D7E18: ; 0x021D7E18
	push {r4, lr}
	sub sp, #8
	add r0, sp, #4
	add r1, sp, #0
	bl ov04_021DD718
	add r4, r0, #0
	beq _021D7EFA
	ldr r0, [sp]
	cmp r0, #7
	bhi _021D7EFA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7E3A: ; jump table
	.short _021D7EFA - _021D7E3A - 2 ; case 0
	.short _021D7E4A - _021D7E3A - 2 ; case 1
	.short _021D7EFA - _021D7E3A - 2 ; case 2
	.short _021D7E66 - _021D7E3A - 2 ; case 3
	.short _021D7EFA - _021D7E3A - 2 ; case 4
	.short _021D7EFA - _021D7E3A - 2 ; case 5
	.short _021D7E66 - _021D7E3A - 2 ; case 6
	.short _021D7ECE - _021D7E3A - 2 ; case 7
_021D7E4A:
	bl ov04_021DD6F0
	cmp r4, #0xa
	blt _021D7E58
	add sp, #8
	add r0, r4, #0
	pop {r4, pc}
_021D7E58:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _021D7EFA
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r4, pc}
_021D7E66:
	ldr r0, _021D7F14 ; =ov04_0220FBC0
	ldr r1, [r0]
	cmp r1, #0
	beq _021D7EB2
	ldr r0, _021D7F18 ; =0x00001F44
	ldr r0, [r1, r0]
	cmp r0, #0x11
	bhi _021D7EAE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7E82: ; jump table
	.short _021D7EAA - _021D7E82 - 2 ; case 0
	.short _021D7EAA - _021D7E82 - 2 ; case 1
	.short _021D7EAA - _021D7E82 - 2 ; case 2
	.short _021D7EA6 - _021D7E82 - 2 ; case 3
	.short _021D7EA6 - _021D7E82 - 2 ; case 4
	.short _021D7EA6 - _021D7E82 - 2 ; case 5
	.short _021D7EA6 - _021D7E82 - 2 ; case 6
	.short _021D7EA6 - _021D7E82 - 2 ; case 7
	.short _021D7EA6 - _021D7E82 - 2 ; case 8
	.short _021D7EAE - _021D7E82 - 2 ; case 9
	.short _021D7EAE - _021D7E82 - 2 ; case 10
	.short _021D7EA6 - _021D7E82 - 2 ; case 11
	.short _021D7EAE - _021D7E82 - 2 ; case 12
	.short _021D7EAE - _021D7E82 - 2 ; case 13
	.short _021D7EAE - _021D7E82 - 2 ; case 14
	.short _021D7EA6 - _021D7E82 - 2 ; case 15
	.short _021D7EA6 - _021D7E82 - 2 ; case 16
	.short _021D7EA6 - _021D7E82 - 2 ; case 17
_021D7EA6:
	bl ov04_021E0200
_021D7EAA:
	bl ov04_021DDBBC
_021D7EAE:
	bl ov04_021DD6F0
_021D7EB2:
	ldr r0, _021D7F14 ; =ov04_0220FBC0
	ldr r2, [r0]
	cmp r2, #0
	beq _021D7EC0
	ldr r0, _021D7F18 ; =0x00001F44
	mov r1, #0xd
	str r1, [r2, r0]
_021D7EC0:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _021D7F10
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r4, pc}
_021D7ECE:
	ldr r1, _021D7F14 ; =ov04_0220FBC0
	ldr r3, [r1]
	cmp r3, #0
	beq _021D7EEC
	ldr r0, _021D7F18 ; =0x00001F44
	mov r2, #0xe
	str r2, [r3, r0]
	ldr r1, [r1]
	sub r0, #0x30
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _021D7EEC
	ldr r0, [sp, #4]
	neg r0, r0
	blx r1
_021D7EEC:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _021D7F10
	mov r0, #0
	add sp, #8
	mvn r0, r0
	pop {r4, pc}
_021D7EFA:
	ldr r0, _021D7F14 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7F1C ; =0x00001F82
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _021D7F0E
	mov r0, #1
	add sp, #8
	mvn r0, r0
	pop {r4, pc}
_021D7F0E:
	mov r0, #0
_021D7F10:
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D7F14: .word ov04_0220FBC0
_021D7F18: .word 0x00001F44
_021D7F1C: .word 0x00001F82

	thumb_func_start ov04_021D7F20
ov04_021D7F20: ; 0x021D7F20
	push {r3, r4, r5, lr}
	ldr r0, _021D7F80 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D7F84 ; =0x00001F4C
	ldr r0, [r1, r0]
	cmp r0, #0
	bne _021D7F7E
	bl ov04_021DF95C
	mov r1, #1
	sub r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl ov04_021EB0FC
	cmp r0, #0
	beq _021D7F7E
	ldr r4, _021D7F80 ; =ov04_0220FBC0
	ldr r2, _021D7F84 ; =0x00001F4C
	ldr r0, [r4]
	mov r1, #1
	str r1, [r0, r2]
	add r1, r2, #0
	ldr r0, [r4]
	add r1, #0x2c
	ldr r1, [r0, r1]
	mov r3, #2
	lsl r1, r1, #8
	add r5, r1, #0
	orr r5, r3
	lsl r1, r3, #0xb
	str r5, [r0, r1]
	add r0, r2, #4
	ldr r1, [r4]
	lsl r2, r3, #0xb
	ldr r0, [r1, r0]
	add r1, r1, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mov r2, #4
	bl ov04_021EB044
	add r0, r4, #0
	ldr r1, [r0]
	ldr r0, _021D7F88 ; =0x00001F74
	mov r2, #0
	str r2, [r1, r0]
_021D7F7E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D7F80: .word ov04_0220FBC0
_021D7F84: .word 0x00001F4C
_021D7F88: .word 0x00001F74

	thumb_func_start ov04_021D7F8C
ov04_021D7F8C: ; 0x021D7F8C
	push {r3, r4, r5, lr}
	bl ov04_021DFF74
	bl ov04_021D83F0
	ldr r0, _021D800C ; =ov04_0220FBC0
	ldr r1, _021D8010 ; =0x00001F58
	ldr r2, [r0]
	ldr r0, [r2, r1]
	cmp r0, #0
	beq _021D7FC2
	add r0, r1, #0
	add r0, #0x20
	ldr r0, [r2, r0]
	cmp r0, #1
	bne _021D7FBA
	add r1, #0x24
	ldr r0, [r2, r1]
	cmp r0, #1
	bne _021D7FBA
	bl ov04_021D8D04
	b _021D7FBE
_021D7FBA:
	bl ov04_021D8CF0
_021D7FBE:
	bl ov04_021D8944
_021D7FC2:
	ldr r4, _021D800C ; =ov04_0220FBC0
	ldr r3, _021D8014 ; =0x00001F44
	ldr r1, [r4]
	ldr r0, [r1, r3]
	cmp r0, #0x11
	bne _021D7FD2
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D7FD2:
	cmp r0, #0x10
	bne _021D7FDA
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D7FDA:
	cmp r0, #7
	bne _021D8004
	add r2, r3, #0
	add r2, #0x30
	add r0, r3, #0
	ldr r2, [r1, r2]
	add r0, #0x30
	add r5, r2, #1
	add r2, r3, #0
	ldr r0, [r1, r0]
	add r2, #0x30
	str r5, [r1, r2]
	cmp r0, #0x78
	blt _021D8004
	ldr r0, [r4]
	add r3, #8
	ldr r0, [r0, r3]
	cmp r0, #0
	bne _021D8004
	bl ov04_021D7F20
_021D8004:
	bl ov04_021D7E18
	pop {r3, r4, r5, pc}
	nop
_021D800C: .word ov04_0220FBC0
_021D8010: .word 0x00001F58
_021D8014: .word 0x00001F44

	thumb_func_start ov04_021D8018
ov04_021D8018: ; 0x021D8018
	push {r3, lr}
	ldr r0, _021D803C ; =ov04_0220FBC0
	ldr r1, [r0]
	cmp r1, #0
	beq _021D8034
	ldr r0, _021D8040 ; =0x00001F44
	ldr r0, [r1, r0]
	cmp r0, #7
	beq _021D802E
	cmp r0, #0xf
	bne _021D8034
_021D802E:
	bl ov04_021DF95C
	pop {r3, pc}
_021D8034:
	mov r0, #0
	mvn r0, r0
	pop {r3, pc}
	nop
_021D803C: .word ov04_0220FBC0
_021D8040: .word 0x00001F44

	thumb_func_start ov04_021D8044
ov04_021D8044: ; 0x021D8044
	ldr r0, _021D8050 ; =ov04_0220FBC0
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _021D8054 ; =0x00001F58
	str r2, [r1, r0]
	bx lr
	.align 2, 0
_021D8050: .word ov04_0220FBC0
_021D8054: .word 0x00001F58

	thumb_func_start ov04_021D8058
ov04_021D8058: ; 0x021D8058
	push {r3, lr}
	ldr r0, _021D80CC ; =ov04_0220FBC0
	ldr r2, _021D80D0 ; =0x00001F6C
	ldr r0, [r0]
	ldr r1, [r0, r2]
	cmp r1, #5
	bhi _021D80AE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D8072: ; jump table
	.short _021D80AE - _021D8072 - 2 ; case 0
	.short _021D80AE - _021D8072 - 2 ; case 1
	.short _021D807E - _021D8072 - 2 ; case 2
	.short _021D808A - _021D8072 - 2 ; case 3
	.short _021D8096 - _021D8072 - 2 ; case 4
	.short _021D80A2 - _021D8072 - 2 ; case 5
_021D807E:
	sub r2, #0x18
	ldr r0, [r0, r2]
	mov r1, #1
	bl ov04_021D8A7C
	b _021D80B8
_021D808A:
	sub r2, #0x18
	ldr r0, [r0, r2]
	mov r1, #2
	bl ov04_021D8A7C
	b _021D80B8
_021D8096:
	sub r2, #0x18
	ldr r0, [r0, r2]
	mov r1, #3
	bl ov04_021D8A7C
	b _021D80B8
_021D80A2:
	sub r2, #0x18
	ldr r0, [r0, r2]
	mov r1, #4
	bl ov04_021D8A7C
	b _021D80B8
_021D80AE:
	ldr r1, _021D80D4 ; =0x00001F54
	ldr r0, [r0, r1]
	mov r1, #4
	bl ov04_021D8A7C
_021D80B8:
	ldr r0, _021D80D8 ; =ov04_021D8044
	bl ov04_021D8C58
	ldr r0, _021D80CC ; =ov04_0220FBC0
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _021D80DC ; =0x00001F58
	str r2, [r1, r0]
	pop {r3, pc}
	nop
_021D80CC: .word ov04_0220FBC0
_021D80D0: .word 0x00001F6C
_021D80D4: .word 0x00001F54
_021D80D8: .word ov04_021D8044
_021D80DC: .word 0x00001F58

	thumb_func_start ov04_021D80E0
ov04_021D80E0: ; 0x021D80E0
	push {r3, r4, r5, lr}
	mov r1, #0x64
	add r5, r0, #0
	bl _s32_div_f
	mov r1, #0xfa
	add r4, r0, #0
	add r0, r5, #0
	lsl r1, r1, #2
	bl _s32_div_f
	ldr r2, _021D8270 ; =0x00004E84
	cmp r5, r2
	bne _021D8100
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8100:
	add r1, r2, #2
	cmp r5, r1
	blt _021D8110
	add r1, r2, #7
	cmp r5, r1
	bgt _021D8110
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8110:
	ldr r1, _021D8274 ; =0x00004E8D
	cmp r5, r1
	bne _021D811A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D811A:
	add r1, r1, #2
	cmp r5, r1
	blt _021D812A
	ldr r1, _021D8278 ; =0x00005207
	cmp r5, r1
	bgt _021D812A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D812A:
	ldr r1, _021D827C ; =0x0000CB24
	cmp r5, r1
	blt _021D813A
	add r1, #0x5f
	cmp r5, r1
	bgt _021D813A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D813A:
	ldr r1, _021D8280 ; =0x0000CB88
	cmp r5, r1
	blt _021D814A
	add r1, #0x5f
	cmp r5, r1
	bgt _021D814A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D814A:
	ldr r1, _021D8284 ; =0x0000CBEC
	cmp r5, r1
	blt _021D815A
	add r1, #0x5f
	cmp r5, r1
	bgt _021D815A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D815A:
	ldr r1, _021D8288 ; =0x0000020B
	cmp r4, r1
	bne _021D8164
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8164:
	add r2, r1, #7
	cmp r4, r2
	bne _021D816E
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D816E:
	add r2, r1, #0
	add r2, #8
	cmp r4, r2
	bne _021D817A
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D817A:
	add r2, r1, #0
	add r2, #9
	cmp r4, r2
	bne _021D8186
	mov r0, #0
	pop {r3, r4, r5, pc}
_021D8186:
	ldr r3, _021D828C ; =0x00004E85
	cmp r5, r3
	bne _021D8190
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8190:
	cmp r0, #0x17
	bne _021D8198
	mov r0, #1
	pop {r3, r4, r5, pc}
_021D8198:
	add r2, r3, #7
	cmp r5, r2
	bne _021D81A2
	mov r0, #2
	pop {r3, r4, r5, pc}
_021D81A2:
	add r3, #9
	cmp r5, r3
	bne _021D81AC
	mov r0, #3
	pop {r3, r4, r5, pc}
_021D81AC:
	add r2, r1, #0
	sub r2, #0xb
	cmp r4, r2
	bne _021D81B8
	mov r0, #4
	pop {r3, r4, r5, pc}
_021D81B8:
	sub r1, #0x17
	cmp r4, r1
	bne _021D81C2
	mov r0, #5
	pop {r3, r4, r5, pc}
_021D81C2:
	ldr r1, _021D8290 ; =0x0000C738
	cmp r5, r1
	blt _021D81D2
	add r1, #0x66
	cmp r5, r1
	bgt _021D81D2
	mov r0, #6
	pop {r3, r4, r5, pc}
_021D81D2:
	ldr r1, _021D8294 ; =0x0000C7A0
	cmp r5, r1
	blt _021D81E2
	add r1, #0x5f
	cmp r5, r1
	bgt _021D81E2
	mov r0, #6
	pop {r3, r4, r5, pc}
_021D81E2:
	ldr r1, _021D8298 ; =0x00000201
	cmp r4, r1
	bne _021D81EC
	mov r0, #6
	pop {r3, r4, r5, pc}
_021D81EC:
	ldr r1, _021D829C ; =0x0000C79F
	cmp r5, r1
	bne _021D81F6
	mov r0, #7
	pop {r3, r4, r5, pc}
_021D81F6:
	ldr r1, _021D82A0 ; =0x0000CB20
	cmp r5, r1
	blt _021D8206
	add r1, r1, #3
	cmp r5, r1
	bgt _021D8206
	mov r0, #8
	pop {r3, r4, r5, pc}
_021D8206:
	ldr r1, _021D82A4 ; =0x0000CB84
	cmp r5, r1
	blt _021D8216
	add r1, r1, #3
	cmp r5, r1
	bgt _021D8216
	mov r0, #8
	pop {r3, r4, r5, pc}
_021D8216:
	ldr r1, _021D82A8 ; =0x0000CBE8
	cmp r5, r1
	blt _021D8226
	add r1, r1, #3
	cmp r5, r1
	bgt _021D8226
	mov r0, #8
	pop {r3, r4, r5, pc}
_021D8226:
	ldr r1, _021D82AC ; =0x00013A2E
	cmp r5, r1
	bne _021D8230
	mov r0, #9
	pop {r3, r4, r5, pc}
_021D8230:
	cmp r0, #0x18
	bne _021D8238
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_021D8238:
	cmp r0, #0x19
	bne _021D8240
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_021D8240:
	cmp r0, #0x1f
	bne _021D8248
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_021D8248:
	cmp r0, #0x36
	bne _021D8250
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_021D8250:
	ldr r0, _021D82B0 ; =0x0000EA60
	cmp r5, r0
	blt _021D8260
	ldr r0, _021D82B4 ; =0x0001869F
	cmp r5, r0
	bgt _021D8260
	mov r0, #0xa
	pop {r3, r4, r5, pc}
_021D8260:
	ldr r0, _021D82B8 ; =0x00002710
	cmp r5, r0
	bge _021D826A
	mov r0, #0xb
	pop {r3, r4, r5, pc}
_021D826A:
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8270: .word 0x00004E84
_021D8274: .word 0x00004E8D
_021D8278: .word 0x00005207
_021D827C: .word 0x0000CB24
_021D8280: .word 0x0000CB88
_021D8284: .word 0x0000CBEC
_021D8288: .word 0x0000020B
_021D828C: .word 0x00004E85
_021D8290: .word 0x0000C738
_021D8294: .word 0x0000C7A0
_021D8298: .word 0x00000201
_021D829C: .word 0x0000C79F
_021D82A0: .word 0x0000CB20
_021D82A4: .word 0x0000CB84
_021D82A8: .word 0x0000CBE8
_021D82AC: .word 0x00013A2E
_021D82B0: .word 0x0000EA60
_021D82B4: .word 0x0001869F
_021D82B8: .word 0x00002710

	thumb_func_start ov04_021D82BC
ov04_021D82BC: ; 0x021D82BC
	push {r3, lr}
	cmp r0, #0
	bne _021D8346
	ldr r0, _021D8364 ; =ov04_0220FBC0
	ldr r2, _021D8368 ; =0x00001F44
	ldr r0, [r0]
	ldr r1, [r0, r2]
	cmp r1, #0x11
	bhi _021D835E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D82DA: ; jump table
	.short _021D835E - _021D82DA - 2 ; case 0
	.short _021D835E - _021D82DA - 2 ; case 1
	.short _021D835E - _021D82DA - 2 ; case 2
	.short _021D835E - _021D82DA - 2 ; case 3
	.short _021D8342 - _021D82DA - 2 ; case 4
	.short _021D82FE - _021D82DA - 2 ; case 5
	.short _021D835E - _021D82DA - 2 ; case 6
	.short _021D82FE - _021D82DA - 2 ; case 7
	.short _021D835E - _021D82DA - 2 ; case 8
	.short _021D835E - _021D82DA - 2 ; case 9
	.short _021D835E - _021D82DA - 2 ; case 10
	.short _021D835E - _021D82DA - 2 ; case 11
	.short _021D835E - _021D82DA - 2 ; case 12
	.short _021D8342 - _021D82DA - 2 ; case 13
	.short _021D835E - _021D82DA - 2 ; case 14
	.short _021D8328 - _021D82DA - 2 ; case 15
	.short _021D8342 - _021D82DA - 2 ; case 16
	.short _021D8342 - _021D82DA - 2 ; case 17
_021D82FE:
	add r2, #0x14
	ldr r0, [r0, r2]
	cmp r0, #0
	beq _021D8316
	bl ov04_021D8C08
	ldr r0, _021D8364 ; =ov04_0220FBC0
	mov r2, #0xf
	ldr r1, [r0]
	ldr r0, _021D8368 ; =0x00001F44
	str r2, [r1, r0]
	b _021D835E
_021D8316:
	bl ov04_021DFA40
	ldr r0, _021D8364 ; =ov04_0220FBC0
	mov r2, #0x10
	ldr r1, [r0]
	ldr r0, _021D8368 ; =0x00001F44
	str r2, [r1, r0]
	mov r0, #1
	pop {r3, pc}
_021D8328:
	add r2, #0x14
	ldr r0, [r0, r2]
	cmp r0, #0
	bne _021D835E
	bl ov04_021DFA40
	ldr r0, _021D8364 ; =ov04_0220FBC0
	mov r2, #0x10
	ldr r1, [r0]
	ldr r0, _021D8368 ; =0x00001F44
	str r2, [r1, r0]
	mov r0, #1
	pop {r3, pc}
_021D8342:
	mov r0, #1
	pop {r3, pc}
_021D8346:
	ldr r0, _021D8364 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D8368 ; =0x00001F44
	ldr r0, [r1, r0]
	cmp r0, #4
	beq _021D835A
	cmp r0, #0x10
	beq _021D835A
	cmp r0, #0x11
	bne _021D835E
_021D835A:
	mov r0, #1
	pop {r3, pc}
_021D835E:
	mov r0, #0
	pop {r3, pc}
	nop
_021D8364: .word ov04_0220FBC0
_021D8368: .word 0x00001F44

	thumb_func_start ov04_021D836C
ov04_021D836C: ; 0x021D836C
	push {r3, r4}
	ldr r2, _021D83A0 ; =ov04_0220FBC0
	ldr r1, _021D83A4 ; =0x00001F44
	ldr r3, [r2]
	ldr r0, [r3, r1]
	sub r0, #0x10
	cmp r0, #1
	bhi _021D8398
	mov r4, #0
	add r0, r1, #0
	mvn r4, r4
	add r0, #0xc
	str r4, [r3, r0]
	ldr r0, [r2]
	mov r3, #4
	str r3, [r0, r1]
	ldr r0, [r2]
	add r1, #0x1c
	str r4, [r0, r1]
	mov r0, #1
	pop {r3, r4}
	bx lr
_021D8398:
	mov r0, #0
	pop {r3, r4}
	bx lr
	nop
_021D83A0: .word ov04_0220FBC0
_021D83A4: .word 0x00001F44

	thumb_func_start ov04_021D83A8
ov04_021D83A8: ; 0x021D83A8
	ldr r1, _021D83B8 ; =ov04_0220FBC0
	ldr r2, [r1]
	cmp r2, #0
	beq _021D83B4
	ldr r1, _021D83BC ; =0x00001F14
	str r0, [r2, r1]
_021D83B4:
	bx lr
	nop
_021D83B8: .word ov04_0220FBC0
_021D83BC: .word 0x00001F14

	thumb_func_start ov04_021D83C0
ov04_021D83C0: ; 0x021D83C0
	push {r3, lr}
	bl ov04_021E0200
	bl ov04_021DDBBC
	bl ov04_021D8C6C
	bl ov04_021D7660
	pop {r3, pc}

	thumb_func_start ov04_021D83D4
ov04_021D83D4: ; 0x021D83D4
	push {r3, r4}
	ldr r3, _021D83E8 ; =ov04_0220FBC0
	ldr r2, _021D83EC ; =0x00001F38
	ldr r4, [r3]
	str r0, [r4, r2]
	ldr r3, [r3]
	add r0, r2, #4
	str r1, [r3, r0]
	pop {r3, r4}
	bx lr
	.align 2, 0
_021D83E8: .word ov04_0220FBC0
_021D83EC: .word 0x00001F38

	thumb_func_start ov04_021D83F0
ov04_021D83F0: ; 0x021D83F0
	push {r3, r4, r5, r6, r7, lr}
	ldr r6, _021D8468 ; =ov04_0220FBC0
	ldr r0, _021D846C ; =0x00001F38
	ldr r1, [r6]
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _021D8464
	mov r7, #0
_021D8400:
	mov r1, #0x7d
	ldr r0, [r6]
	lsl r1, r1, #6
	ldr r2, [r0, r1]
	mov r1, #0x1f
	add r5, r2, #0
	and r5, r1
	mov r1, #0xc
	add r4, r5, #0
	mul r4, r1
	mov r1, #0x11
	lsl r1, r1, #8
	ldr r0, [r0, r1]
	add r0, r0, r4
	bl DWC_IsBuddyFriendData
	cmp r0, #0
	beq _021D844A
	mov r0, #0x11
	ldr r2, [r6]
	ldr r1, _021D846C ; =0x00001F38
	lsl r0, r0, #8
	ldr r0, [r2, r0]
	ldr r3, _021D8470 ; =0x00001F3C
	ldr r1, [r2, r1]
	ldr r2, [r2, r3]
	add r0, r0, r4
	add r3, r2, #0
	mul r3, r5
	add r1, r1, r3
	add r2, sp, #0
	bl ov04_021E2578
	ldr r1, [r6]
	add r2, r1, r5
	ldr r1, _021D8474 ; =0x00001F18
	strb r0, [r2, r1]
_021D844A:
	mov r1, #0x7d
	ldr r0, [r6]
	lsl r1, r1, #6
	ldr r1, [r0, r1]
	add r7, r7, #1
	add r2, r1, #1
	mov r1, #0x1f
	and r2, r1
	mov r1, #0x7d
	lsl r1, r1, #6
	str r2, [r0, r1]
	cmp r7, #4
	blt _021D8400
_021D8464:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8468: .word ov04_0220FBC0
_021D846C: .word 0x00001F38
_021D8470: .word 0x00001F3C
_021D8474: .word 0x00001F18

	thumb_func_start ov04_021D8478
ov04_021D8478: ; 0x021D8478
	ldr r3, _021D847C ; =ov04_021E2454
	bx r3
	.align 2, 0
_021D847C: .word ov04_021E2454

	thumb_func_start ov04_021D8480
ov04_021D8480: ; 0x021D8480
	ldr r1, _021D848C ; =ov04_0220FBC0
	ldr r1, [r1]
	add r1, r1, r0
	ldr r0, _021D8490 ; =0x00001F18
	ldrb r0, [r1, r0]
	bx lr
	.align 2, 0
_021D848C: .word ov04_0220FBC0
_021D8490: .word 0x00001F18

	thumb_func_start ov04_021D8494
ov04_021D8494: ; 0x021D8494
	push {r3, lr}
	ldr r1, _021D8510 ; =ov04_0220FBC0
	ldr r3, [r1]
	ldr r1, _021D8514 ; =0x00001F44
	ldr r2, [r3, r1]
	cmp r2, #4
	beq _021D84A6
	mov r0, #0
	pop {r3, pc}
_021D84A6:
	add r1, #0x18
	str r0, [r3, r1]
	cmp r0, #0
	bge _021D84C2
	ldr r1, _021D8518 ; =ov04_021D8558
	mov r2, #0
	ldr r3, _021D851C ; =ov04_021D85A0
	mov r0, #2
	str r2, [sp]
	bl ov04_021DFD18
	mov r2, #1
	ldr r0, _021D8510 ; =ov04_0220FBC0
	b _021D84D2
_021D84C2:
	ldr r1, _021D8520 ; =ov04_021D8590
	mov r2, #0
	ldr r3, _021D851C ; =ov04_021D85A0
	str r2, [sp]
	bl ov04_021DFB20
	ldr r0, _021D8510 ; =ov04_0220FBC0
	mov r2, #2
_021D84D2:
	ldr r1, [r0]
	ldr r0, _021D8524 ; =0x00001F48
	str r2, [r1, r0]
	ldr r0, _021D8510 ; =ov04_0220FBC0
	mov r2, #5
	ldr r1, [r0]
	ldr r0, _021D8514 ; =0x00001F44
	str r2, [r1, r0]
	ldr r0, _021D8528 ; =ov04_021D7C30
	bl ov04_021EAE18
	ldr r0, _021D852C ; =ov04_021D7C4C
	bl ov04_021EADF8
	ldr r0, _021D8530 ; =ov04_021D7D68
	mov r1, #0
	bl ov04_021DFAF8
	ldr r0, _021D8534 ; =ov04_021D7B14
	bl ov04_021EADD8
	ldr r1, _021D8510 ; =ov04_0220FBC0
	ldr r0, _021D8538 ; =0x00001F4C
	ldr r2, [r1]
	mov r3, #0
	str r3, [r2, r0]
	ldr r1, [r1]
	add r0, #0x3c
	str r3, [r1, r0]
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
_021D8510: .word ov04_0220FBC0
_021D8514: .word 0x00001F44
_021D8518: .word ov04_021D8558
_021D851C: .word ov04_021D85A0
_021D8520: .word ov04_021D8590
_021D8524: .word 0x00001F48
_021D8528: .word ov04_021D7C30
_021D852C: .word ov04_021D7C4C
_021D8530: .word ov04_021D7D68
_021D8534: .word ov04_021D7B14
_021D8538: .word 0x00001F4C

	thumb_func_start ov04_021D853C
ov04_021D853C: ; 0x021D853C
	ldr r0, _021D8550 ; =ov04_0220FBC0
	ldr r1, [r0]
	cmp r1, #0
	beq _021D854A
	ldr r0, _021D8554 ; =0x00001F5C
	ldr r0, [r1, r0]
	bx lr
_021D854A:
	mov r0, #0
	mvn r0, r0
	bx lr
	.align 2, 0
_021D8550: .word ov04_0220FBC0
_021D8554: .word 0x00001F5C

	thumb_func_start ov04_021D8558
ov04_021D8558: ; 0x021D8558
	push {r3, lr}
	cmp r0, #0
	bne _021D8582
	cmp r1, #0
	bne _021D8572
	ldr r0, _021D8584 ; =ov04_0220FBC0
	ldr r2, [sp, #8]
	ldr r1, [r0]
	ldr r0, _021D8588 ; =0x00001F5C
	str r2, [r1, r0]
	bl ov04_021D7BC0
	pop {r3, pc}
_021D8572:
	cmp r2, #0
	bne _021D8582
	ldr r0, _021D8584 ; =ov04_0220FBC0
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _021D858C ; =0x00001F60
	mvn r2, r2
	str r2, [r1, r0]
_021D8582:
	pop {r3, pc}
	.align 2, 0
_021D8584: .word ov04_0220FBC0
_021D8588: .word 0x00001F5C
_021D858C: .word 0x00001F60

	thumb_func_start ov04_021D8590
ov04_021D8590: ; 0x021D8590
	push {r3, lr}
	cmp r0, #0
	bne _021D859E
	cmp r1, #0
	bne _021D859E
	bl ov04_021D7BC0
_021D859E:
	pop {r3, pc}

	thumb_func_start ov04_021D85A0
ov04_021D85A0: ; 0x021D85A0
	ldr r1, _021D85AC ; =ov04_0220FBC0
	ldr r2, [r1]
	ldr r1, _021D85B0 ; =0x00001F60
	str r0, [r2, r1]
	bx lr
	nop
_021D85AC: .word ov04_0220FBC0
_021D85B0: .word 0x00001F60

	thumb_func_start ov04_021D85B4
ov04_021D85B4: ; 0x021D85B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r0, _021D8614 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D8618 ; =0x00001EF0
	ldr r0, [r1, r0]
	bl DWC_CheckHasProfile
	cmp r0, #0
	bne _021D85D8
	ldr r0, _021D8614 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D8618 ; =0x00001EF0
	ldr r0, [r1, r0]
	add r1, sp, #0xc
	bl DWC_CreateExchangeToken
	b _021D85E6
_021D85D8:
	ldr r0, _021D8614 ; =ov04_0220FBC0
	ldr r1, [r0]
	ldr r0, _021D8618 ; =0x00001EF0
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl DWC_CreateExchangeToken
_021D85E6:
	mov r4, #0
	mov r7, #0x11
	ldr r6, _021D8614 ; =ov04_0220FBC0
	add r5, r4, #0
	lsl r7, r7, #8
_021D85F0:
	mov r0, #0x11
	ldr r1, [r6]
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	add r0, r0, r5
	bl DWC_GetFriendDataType
	ldr r0, [r6]
	ldr r0, [r0, r7]
	add r0, r0, r5
	bl DWC_IsBuddyFriendData
	add r4, r4, #1
	add r5, #0xc
	cmp r4, #0x20
	blt _021D85F0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8614: .word ov04_0220FBC0
_021D8618: .word 0x00001EF0

	thumb_func_start ov04_021D861C
ov04_021D861C: ; 0x021D861C
	ldr r3, _021D8620 ; =ov04_021D8CC8
	bx r3
	.align 2, 0
_021D8620: .word ov04_021D8CC8

	thumb_func_start ov04_021D8624
ov04_021D8624: ; 0x021D8624
	ldr r0, _021D8638 ; =ov04_0220FBC0
	ldr r1, [r0]
	cmp r1, #0
	beq _021D8632
	ldr r0, _021D863C ; =0x00001F68
	ldr r0, [r1, r0]
	bx lr
_021D8632:
	mov r0, #0
	bx lr
	nop
_021D8638: .word ov04_0220FBC0
_021D863C: .word 0x00001F68

	thumb_func_start ov04_021D8640
ov04_021D8640: ; 0x021D8640
	ldr r0, _021D8654 ; =ov04_0220FBC0
	ldr r1, [r0]
	cmp r1, #0
	beq _021D864E
	ldr r0, _021D8658 ; =0x00001F60
	ldr r0, [r1, r0]
	bx lr
_021D864E:
	mov r0, #0
	bx lr
	nop
_021D8654: .word ov04_0220FBC0
_021D8658: .word 0x00001F60

	thumb_func_start ov04_021D865C
ov04_021D865C: ; 0x021D865C
	ldr r0, _021D8670 ; =ov04_0220FBC0
	ldr r2, [r0]
	cmp r2, #0
	beq _021D866C
	mov r1, #0
	ldr r0, _021D8674 ; =0x00001F60
	mvn r1, r1
	str r1, [r2, r0]
_021D866C:
	bx lr
	nop
_021D8670: .word ov04_0220FBC0
_021D8674: .word 0x00001F60

	thumb_func_start ov04_021D8678
ov04_021D8678: ; 0x021D8678
	ldr r1, _021D8684 ; =ov04_0220FBC0
	ldr r2, [r1]
	ldr r1, _021D8688 ; =0x00001F68
	str r0, [r2, r1]
	bx lr
	nop
_021D8684: .word ov04_0220FBC0
_021D8688: .word 0x00001F68

	.section .bss

	.global ov04_0220FBC0
ov04_0220FBC0: ; 0x0220FBC0
	.space 0x8

	.section .data

	.balign 4

	.global ov04_0220BEA0
ov04_0220BEA0: ; 0x0220BEA0
	.asciz "pokemondpds"

	.balign 4

	.global ov04_0220BEAC
ov04_0220BEAC: ; 0x0220BEAC
	.asciz "1vTlwb"
