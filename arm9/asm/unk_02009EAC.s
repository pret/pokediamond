    .include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C4670
UNK_021C4670: ; 0x021C4670
	.space 0x4

	.global UNK_021C4674
UNK_021C4674: ; 0x021C4674
	.space 0x20

	.global UNK_021C4694
UNK_021C4694: ; 0x021C4694
	.space 0x20

	.text

	thumb_func_start FUN_02009EAC
FUN_02009EAC: ; 0x02009EAC
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	cmp r4, #0x4
	bge _02009EC0
	mov r0, #0x4
	cmp r1, #0x7c
	ble _02009EC0
	sub r4, r0, r4
	sub r1, r1, r4
_02009EC0:
	cmp r2, #0x1
	bge _02009ED0
	mov r4, #0x1
	cmp r3, #0x1e
	ble _02009ED2
	sub r2, r4, r2
	sub r3, r3, r2
	b _02009ED2
_02009ED0:
	add r4, r2, #0x0
_02009ED2:
	ldr r2, [sp, #0x20]
	str r2, [sp, #0x0]
	ldr r2, [sp, #0x24]
	str r2, [sp, #0x4]
	ldr r2, [sp, #0x28]
	str r2, [sp, #0x8]
	ldr r2, [sp, #0x2c]
	str r2, [sp, #0xc]
	ldr r2, [sp, #0x30]
	str r2, [sp, #0x10]
	add r2, r4, #0x0
	bl FUN_02009EF0
	add sp, #0x14
	pop {r3-r4, pc}

	thumb_func_start FUN_02009EF0
FUN_02009EF0: ; 0x02009EF0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _02009F7C ; =UNK_021C4670
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	beq _02009F08
	bl ErrorHandling
_02009F08:
	ldr r0, [sp, #0x30]
	mov r1, #0x3c
	bl AllocFromHeap
	ldr r1, _02009F7C ; =UNK_021C4670
	cmp r0, #0x0
	str r0, [r1, #0x0]
	bne _02009F1C
	bl ErrorHandling
_02009F1C:
	ldr r1, _02009F7C ; =UNK_021C4670
	lsl r3, r6, #0x10
	ldr r2, [sp, #0x30]
	ldr r0, [r1, #0x0]
	lsr r3, r3, #0x10
	str r2, [r0, #0x38]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r1, #0x0]
	lsl r1, r5, #0x10
	lsl r2, r4, #0x10
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl NNS_G2dGetNewOamManagerInstance
	cmp r0, #0x0
	bne _02009F48
	bl ErrorHandling
_02009F48:
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x20]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, _02009F7C ; =UNK_021C4670
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r0, #0x1c
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl NNS_G2dGetNewOamManagerInstance
	cmp r0, #0x0
	bne _02009F78
	bl ErrorHandling
_02009F78:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02009F7C: .word UNK_021C4670

	thumb_func_start FUN_02009F80
FUN_02009F80: ; 0x02009F80
	push {r3, lr}
	ldr r0, _02009F9C ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02009F98
	bl NNS_G2dApplyAndResetOamManagerBuffer
	ldr r0, _02009F9C ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	add r0, #0x1c
	bl NNS_G2dApplyAndResetOamManagerBuffer
_02009F98:
	pop {r3, pc}
	nop
_02009F9C: .word UNK_021C4670

	thumb_func_start FUN_02009FA0
FUN_02009FA0: ; 0x02009FA0
	push {r3, lr}
	ldr r0, _02009FD4 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02009FAE
	bl ErrorHandling
_02009FAE:
	ldr r0, _02009FD4 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0200A064
	ldr r0, _02009FD4 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0200A06C
	ldr r0, _02009FD4 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _02009FD4 ; =UNK_021C4670
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3, pc}
	nop
_02009FD4: .word UNK_021C4670

	thumb_func_start FUN_02009FD8
FUN_02009FD8: ; 0x02009FD8
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	ldr r0, _0200A024 ; =UNK_021C4670
	add r7, r1, #0x0
	ldr r0, [r0, #0x0]
	add r5, r2, #0x0
	add r4, r3, #0x0
	cmp r0, #0x0
	bne _02009FF0
	bl ErrorHandling
_02009FF0:
	cmp r5, #0x1
	bne _0200A00C
	ldr r0, _0200A028 ; =FUN_020213A0
	ldr r2, _0200A02C ; =FUN_0200A074
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldr r3, _0200A030 ; =FUN_0200A0B8
	add r0, r6, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0x8]
	bl FUN_0202135C
	add sp, #0xc
	pop {r4-r7, pc}
_0200A00C:
	ldr r0, _0200A028 ; =FUN_020213A0
	ldr r2, _0200A034 ; =FUN_0200A094
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldr r3, _0200A038 ; =FUN_0200A0DC
	add r0, r6, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0x8]
	bl FUN_0202135C
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0200A024: .word UNK_021C4670
_0200A028: .word FUN_020213A0
_0200A02C: .word FUN_0200A074
_0200A030: .word FUN_0200A0B8
_0200A034: .word FUN_0200A094
_0200A038: .word FUN_0200A0DC

	thumb_func_start FUN_0200A03C
FUN_0200A03C: ; 0x0200A03C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0200A060 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0200A04C
	bl ErrorHandling
_0200A04C:
	cmp r4, #0x0
	bne _0200A056
	ldr r0, _0200A060 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	pop {r4, pc}
_0200A056:
	ldr r0, _0200A060 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	add r0, #0x1c
	pop {r4, pc}
	nop
_0200A060: .word UNK_021C4670

	thumb_func_start FUN_0200A064
FUN_0200A064: ; 0x0200A064
	ldr r3, _0200A068 ; =FUN_020203CC
	bx r3
	.balign 4
_0200A068: .word FUN_020203CC

	thumb_func_start FUN_0200A06C
FUN_0200A06C: ; 0x0200A06C
	ldr r3, _0200A070 ; =FUN_02020404
	bx r3
	.balign 4
_0200A070: .word FUN_02020404

	thumb_func_start FUN_0200A074
FUN_0200A074: ; 0x0200A074
	push {r4, lr}
	add r3, r0, #0x0
	ldr r0, _0200A090 ; =UNK_021C4670
	add r2, r1, #0x0
	ldr r0, [r0, #0x0]
	add r1, r3, #0x0
	bl NNS_G2dEntryOamManagerOamWithAffineIdx
	add r4, r0, #0x0
	bne _0200A08C
	bl ErrorHandling
_0200A08C:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_0200A090: .word UNK_021C4670

	thumb_func_start FUN_0200A094
FUN_0200A094: ; 0x0200A094
	push {r4, lr}
	add r3, r0, #0x0
	ldr r0, _0200A0B4 ; =UNK_021C4670
	add r2, r1, #0x0
	ldr r0, [r0, #0x0]
	add r1, r3, #0x0
	add r0, #0x1c
	bl NNS_G2dEntryOamManagerOamWithAffineIdx
	add r4, r0, #0x0
	bne _0200A0AE
	bl ErrorHandling
_0200A0AE:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0200A0B4: .word UNK_021C4670

	thumb_func_start FUN_0200A0B8
FUN_0200A0B8: ; 0x0200A0B8
	push {r4, lr}
	add r1, r0, #0x0
	ldr r0, _0200A0D4 ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	bl NNS_G2dEntryOamManagerAffine
	add r4, r0, #0x0
	ldr r0, _0200A0D8 ; =0x0000FFFE
	cmp r4, r0
	bne _0200A0D0
	bl ErrorHandling
_0200A0D0:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_0200A0D4: .word UNK_021C4670
_0200A0D8: .word 0x0000FFFE

	thumb_func_start FUN_0200A0DC
FUN_0200A0DC: ; 0x0200A0DC
	push {r4, lr}
	add r1, r0, #0x0
	ldr r0, _0200A0FC ; =UNK_021C4670
	ldr r0, [r0, #0x0]
	add r0, #0x1c
	bl NNS_G2dEntryOamManagerAffine
	add r4, r0, #0x0
	ldr r0, _0200A100 ; =0x0000FFFE
	cmp r4, r0
	bne _0200A0F6
	bl ErrorHandling
_0200A0F6:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0200A0FC: .word UNK_021C4670
_0200A100: .word 0x0000FFFE

	thumb_func_start FUN_0200A104
FUN_0200A104: ; 0x0200A104
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x10
	ldrsb r2, [r5, r0]
	mov r0, #0x14
	ldrsh r0, [r5, r0]
	add r1, r2, #0x0
	mov r7, #0x1a
	ldrsh r2, [r5, r7]
	mul r1, r0
	mov r6, #0xa
	ldrsh r0, [r5, r6]
	add r1, r2, r1
	mov r4, #0x0
	cmp r0, r1
	beq _0200A162
	cmp r2, r0
	beq _0200A162
	strh r1, [r5, #0x1a]
	ldrh r3, [r5, #0x18]
	ldrh r0, [r5, #0x16]
	add r2, r5, #0x0
	add r1, r5, #0x0
	add r0, r3, r0
	strh r0, [r5, #0x18]
	ldrh r3, [r5, #0x18]
	ldrh r0, [r5, #0x8]
	add r2, #0x1a
	add r1, #0x18
	cmp r3, r0
	blo _0200A166
	mov r3, #0x10
	ldrsh r0, [r2, r4]
	ldrsb r3, [r5, r3]
	add r0, r0, r3
	strh r0, [r2, #0x0]
	ldrsh r2, [r5, r7]
	ldrsh r0, [r5, r6]
	cmp r2, r0
	beq _0200A15E
	ldrh r2, [r1, #0x0]
	ldrh r0, [r5, #0x8]
	sub r0, r2, r0
	strh r0, [r1, #0x0]
	b _0200A166
_0200A15E:
	mov r4, #0x1
	b _0200A166
_0200A162:
	strh r0, [r5, #0x1a]
	mov r4, #0x1
_0200A166:
	ldr r1, [r5, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0200A17C
	mov r2, #0x1a
	ldrsh r2, [r5, r2]
	ldr r0, _0200A198 ; =0x04000050
	ldr r1, [r5, #0x0]
	bl G2x_SetBlendBrightness_
	b _0200A18E
_0200A17C:
	mov r0, #0x2
	tst r0, r1
	beq _0200A18E
	mov r2, #0x1a
	ldrsh r2, [r5, r2]
	ldr r0, _0200A19C ; =0x04001050
	ldr r1, [r5, #0x0]
	bl G2x_SetBlendBrightness_
_0200A18E:
	cmp r4, #0x1
	bne _0200A196
	mov r0, #0x0
	str r0, [r5, #0x1c]
_0200A196:
	pop {r3-r7, pc}
	.balign 4
_0200A198: .word 0x04000050
_0200A19C: .word 0x04001050

	thumb_func_start FUN_0200A1A0
FUN_0200A1A0: ; 0x0200A1A0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x1c]
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	beq _0200A1B4
	bl ErrorHandling
_0200A1B4:
	ldr r1, [sp, #0x18]
	mov r0, #0x1
	lsl r1, r1, #0x18
	str r0, [r5, #0x1c]
	lsr r1, r1, #0x18
	str r1, [r5, #0x0]
	ldr r1, [sp, #0x1c]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [r5, #0x4]
	strh r4, [r5, #0x8]
	strh r6, [r5, #0xa]
	strh r7, [r5, #0x1a]
	sub r1, r7, r6
	strh r1, [r5, #0x12]
	mov r1, #0x12
	ldrsh r2, [r5, r1]
	cmp r2, #0x0
	ble _0200A1E0
	sub r1, #0x13
	strb r1, [r5, #0x10]
	b _0200A1EA
_0200A1E0:
	strb r0, [r5, #0x10]
	ldrsh r0, [r5, r1]
	sub r1, #0x13
	mul r1, r0
	strh r1, [r5, #0x12]
_0200A1EA:
	mov r0, #0x12
	ldrsh r0, [r5, r0]
	add r1, r4, #0x0
	bl _s32_div_f
	strh r0, [r5, #0x14]
	mov r0, #0x12
	ldrsh r0, [r5, r0]
	add r1, r4, #0x0
	bl _s32_div_f
	strh r1, [r5, #0x16]
	mov r0, #0x0
	strh r0, [r5, #0x18]
	pop {r3-r7, pc}

	thumb_func_start FUN_0200A208
FUN_0200A208: ; 0x0200A208
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	cmp r5, #0x0
	beq _0200A25E
	ldr r1, [sp, #0x20]
	mov r0, #0x1
	tst r0, r1
	beq _0200A23A
	ldr r0, _0200A264 ; =0x04000050
	add r1, r4, #0x0
	bl G2x_SetBlendBrightness_
	str r4, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, _0200A268 ; =UNK_021C4694
	add r1, r5, #0x0
	add r2, r7, #0x0
	add r3, r6, #0x0
	bl FUN_0200A1A0
_0200A23A:
	ldr r1, [sp, #0x20]
	mov r0, #0x2
	tst r0, r1
	beq _0200A25E
	ldr r0, _0200A26C ; =0x04001050
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl G2x_SetBlendBrightness_
	str r4, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	ldr r0, _0200A270 ; =UNK_021C4674
	add r1, r5, #0x0
	add r2, r7, #0x0
	add r3, r6, #0x0
	bl FUN_0200A1A0
_0200A25E:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0200A264: .word 0x04000050
_0200A268: .word UNK_021C4694
_0200A26C: .word 0x04001050
_0200A270: .word UNK_021C4674

	thumb_func_start FUN_0200A274
FUN_0200A274: ; 0x0200A274
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	mov r0, #0x1
	add r6, r1, #0x0
	tst r0, r4
	beq _0200A28A
	ldr r0, _0200A2A4 ; =0x04000050
	add r2, r5, #0x0
	bl G2x_SetBlendBrightness_
_0200A28A:
	mov r0, #0x2
	tst r0, r4
	beq _0200A29A
	ldr r0, _0200A2A8 ; =0x04001050
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl G2x_SetBlendBrightness_
_0200A29A:
	add r0, r4, #0x0
	bl FUN_0200A2D8
	pop {r4-r6, pc}
	nop
_0200A2A4: .word 0x04000050
_0200A2A8: .word 0x04001050

	thumb_func_start FUN_0200A2AC
FUN_0200A2AC: ; 0x0200A2AC
	push {r3, lr}
	ldr r0, _0200A2CC ; =UNK_021C4694
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r0, _0200A2D0 ; =UNK_021C4674
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r0, _0200A2D4 ; =UNK_021C4674
	mov r1, #0x0
	str r1, [r0, #0x3c]
	str r1, [r0, #0x1c]
	pop {r3, pc}
	.balign 4
_0200A2CC: .word UNK_021C4694
_0200A2D0: .word UNK_021C4674
_0200A2D4: .word UNK_021C4674

	thumb_func_start FUN_0200A2D8
FUN_0200A2D8: ; 0x0200A2D8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	tst r0, r4
	beq _0200A2F2
	ldr r0, _0200A30C ; =UNK_021C4694
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r0, _0200A310 ; =UNK_021C4674
	mov r1, #0x0
	str r1, [r0, #0x3c]
_0200A2F2:
	mov r0, #0x2
	tst r0, r4
	beq _0200A308
	ldr r0, _0200A314 ; =UNK_021C4674
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r0, _0200A310 ; =UNK_021C4674
	mov r1, #0x0
	str r1, [r0, #0x1c]
_0200A308:
	pop {r4, pc}
	nop
_0200A30C: .word UNK_021C4694
_0200A310: .word UNK_021C4674
_0200A314: .word UNK_021C4674

	thumb_func_start FUN_0200A318
FUN_0200A318: ; 0x0200A318
	push {r3, lr}
	ldr r0, _0200A338 ; =UNK_021C4674
	ldr r0, [r0, #0x3c]
	cmp r0, #0x0
	beq _0200A328
	ldr r0, _0200A33C ; =UNK_021C4694
	bl FUN_0200A104
_0200A328:
	ldr r0, _0200A338 ; =UNK_021C4674
	ldr r0, [r0, #0x1c]
	cmp r0, #0x0
	beq _0200A336
	ldr r0, _0200A340 ; =UNK_021C4674
	bl FUN_0200A104
_0200A336:
	pop {r3, pc}
	.balign 4
_0200A338: .word UNK_021C4674
_0200A33C: .word UNK_021C4694
_0200A340: .word UNK_021C4674

	thumb_func_start FUN_0200A344
FUN_0200A344: ; 0x0200A344
	cmp r0, #0x3
	bne _0200A35A
	ldr r0, _0200A380 ; =UNK_021C4674
	ldr r1, [r0, #0x3c]
	cmp r1, #0x0
	bne _0200A37A
	ldr r0, [r0, #0x1c]
	cmp r0, #0x0
	bne _0200A37A
	mov r0, #0x1
	bx lr
_0200A35A:
	cmp r0, #0x1
	bne _0200A36A
	ldr r0, _0200A380 ; =UNK_021C4674
	ldr r0, [r0, #0x3c]
	cmp r0, #0x0
	bne _0200A37A
	mov r0, #0x1
	bx lr
_0200A36A:
	cmp r0, #0x2
	bne _0200A37A
	ldr r0, _0200A380 ; =UNK_021C4674
	ldr r0, [r0, #0x1c]
	cmp r0, #0x0
	bne _0200A37A
	mov r0, #0x1
	bx lr
_0200A37A:
	mov r0, #0x0
	bx lr
	nop
_0200A380: .word UNK_021C4674
