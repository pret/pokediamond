	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start NNS_G2dDrawSpriteFast
NNS_G2dDrawSpriteFast: ; 0x020B0250
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _020B02C0 ; =0x04000470
	mov r0, r0, lsl #0xc
	str r0, [r5, #0x0]
	mov r4, r1, lsl #0xc
	ldr r12, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	str r4, [r5, #0x0]
	mov r4, r2, lsl #0xc
	ldr r2, [sp, #0x18]
	ldr lr, _020B02C4 ; =0x0400046C
	str r4, [r5, #0x0]
	mov r4, r3, lsl #0xc
	ldr r3, [sp, #0x20]
	str r4, [lr, #0x0]
	mov r12, r12, lsl #0xc
	str r12, [lr, #0x0]
	mov r12, #0x1000
	mov r0, r0, lsl #0xc
	mov r1, r1, lsl #0xc
	mov r2, r2, lsl #0xc
	mov r3, r3, lsl #0xc
	str r12, [lr, #0x0]
	bl DrawOneQuad_
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020B02C0: .word 0x04000470
_020B02C4: .word 0x0400046C
	arm_func_end NNS_G2dDrawSpriteFast

	arm_func_start NNS_G2dSetupSoftwareSpriteCamera
NNS_G2dSetupSoftwareSpriteCamera: ; 0x020B02C8
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr r2, _020B0330 ; =0xBFFF0000
	ldr r0, _020B0334 ; =0x04000580
	mov r1, #0x400000
	str r2, [r0, #0x0]
	rsb r0, r1, #0x0
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r0, #0x0
	str r1, [sp, #0x8]
	mov r1, #0x1
	str r1, [sp, #0xc]
	mov r2, r0
	mov r1, #0xc0000
	mov r3, #0x100000
	str r0, [sp, #0x10]
	bl G3i_OrthoW_
	ldr r1, _020B0338 ; =0x0400044C
	mov r2, #0x0
	ldr r0, _020B033C ; =0x04000440
	str r2, [r1, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {pc}
	.balign 4
_020B0330: .word 0xBFFF0000
_020B0334: .word 0x04000580
_020B0338: .word 0x0400044C
_020B033C: .word 0x04000440
	arm_func_end NNS_G2dSetupSoftwareSpriteCamera

	arm_func_start DrawOneQuad_
DrawOneQuad_: ; 0x020B0340
	stmdb sp!, {r4-r6,lr}
	mov r3, r3, lsl #0x8
	mov r0, r0, lsl #0x8
	mov r4, r3, asr #0x10
	mov r3, r0, asr #0x10
	mov r0, r4, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r1, r1, lsl #0x8
	mov r1, r1, asr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r2, lsl #0x8
	mov r2, r2, asr #0x10
	mov r2, r2, lsl #0x10
	ldr ip, _020B03F4 ; =0x04000500
	mov lr, #0x1
	mov r6, r0, lsr #0x10
	mov r5, r3, lsr #0x10
	mov r3, r1, lsr #0x10
	mov r1, r2, lsr #0x10
	ldr r4, _020B03F8 ; =0x04000488
	str lr, [r12, #0x0]
	orr r0, r5, r6, lsl #0x10
	ldr lr, _020B03FC ; =0x0400048C
	str r0, [r4, #0x0]
	mov r0, #0x10000000
	str r0, [lr, #0x0]
	mov r12, #0x0
	str r12, [lr, #0x0]
	orr r2, r3, r6, lsl #0x10
	ldr r0, _020B0400 ; =0x10001000
	str r2, [r4, #0x0]
	str r0, [lr, #0x0]
	str r12, [lr, #0x0]
	orr r0, r3, r1, lsl #0x10
	str r0, [r4, #0x0]
	mov r0, #0x1000
	str r0, [lr, #0x0]
	str r12, [lr, #0x0]
	orr r0, r5, r1, lsl #0x10
	str r0, [r4, #0x0]
	str r12, [lr, #0x0]
	ldr r0, _020B0404 ; =0x04000504
	str r12, [lr, #0x0]
	str r12, [r0, #0x0]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020B03F4: .word 0x04000500
_020B03F8: .word 0x04000488
_020B03FC: .word 0x0400048C
_020B0400: .word 0x10001000
_020B0404: .word 0x04000504
	arm_func_end DrawOneQuad_
