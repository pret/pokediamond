	.include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F96DC
	.section .rodata

	.global UNK_020F2A8C
UNK_020F2A8C: ; 0x020F2A8C
	.byte 0x03, 0x05, 0x08, 0x00

	.global UNK_020F2A90
UNK_020F2A90: ; 0x020F2A90
	.byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF

	.balign 4, 0
	.global UNK_020F2A9C
UNK_020F2A9C: ; 0x020F2A9C
	.byte 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00

	.global UNK_020F2AA8
UNK_020F2AA8: ; 0x020F2AA8
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global UNK_020F2AB4
UNK_020F2AB4: ; 0x020F2AB4
	.byte 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020F2ACC
UNK_020F2ACC: ; 0x020F2ACC
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F2AD0
UNK_020F2AD0: ; 0x020F2AD0
	.word FUN_02035D10, 0x00000001, FUN_02035DF8, 0x00000002
	.word FUN_02036284, 0x00000003, FUN_02036510, 0x00000004
	.word FUN_020365BC, 0x00000005, FUN_02036684, 0x00000006
	.word 0xFFFFFFFE, 0x00000007, FUN_02036700, 0x00000008
	.word FUN_020367E8

	.global UNK_020F2B14
UNK_020F2B14: ; 0x020F2B14
	.byte 0xCC, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00
	.byte 0xD8, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F2B48
UNK_020F2B48: ; 0x020F2B48
	.byte 0xAE, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xD9, 0x34, 0x00, 0x00, 0xD8, 0x34, 0x00, 0x00, 0xD9, 0x34, 0x00, 0x00
	.byte 0xD9, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020F2B7C
UNK_020F2B7C: ; 0x020F2B7C
	.word FUN_02037304, FUN_0203731C, FUN_02037334, 0xFFFFFFFF

	.global UNK_020F2B8C
UNK_020F2B8C: ; 0x020F2B8C
	.word FUN_020372D4, FUN_0203731C, FUN_02037334, 0xFFFFFFFF

	.text

	thumb_func_start FUN_02035068
FUN_02035068: ; 0x02035068
	push {r3, lr}
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	cmp r0, #0x0
	beq _0203507A
	mov r0, #0x1
	pop {r3, pc}
_0203507A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02035080
FUN_02035080: ; 0x02035080
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02035254
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F214
	cmp r0, #0x1
	bne _020350A6
	add r0, r5, #0x0
	bl FUN_020352C4
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _020350E6
_020350A6:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F244
	cmp r0, #0x1
	bne _020350C2
	add r0, r5, #0x0
	bl FUN_020352C8
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _020350E6
_020350C2:
	add r0, r5, #0x0
	bl FUN_02060144
	cmp r0, #0x1
	bne _020350DA
	add r0, r5, #0x0
	bl FUN_020352CC
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _020350E6
_020350DA:
	add r0, r5, #0x0
	bl FUN_02035270
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
_020350E6:
	mov r0, #0x71
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	ldr r0, [r5, #0x38]
	bl FUN_02055B30
	cmp r0, #0x1
	bne _02035106
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055B8C
_02035106:
	ldr r1, _02035114 ; =FUN_020352E4
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463CC
	pop {r3-r5, pc}
	nop
_02035114: .word FUN_020352E4

	thumb_func_start FUN_02035118
FUN_02035118: ; 0x02035118
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02035254
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020352D4
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	mov r2, #0x1
	add r0, r1, #0x4
	str r2, [r4, r0]
	ldr r0, [r5, #0x38]
	bl FUN_02055B30
	cmp r0, #0x1
	bne _0203514C
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055B8C
_0203514C:
	ldr r1, _02035158 ; =FUN_020352E4
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463CC
	pop {r3-r5, pc}
	.balign 4
_02035158: .word FUN_020352E4

	thumb_func_start FUN_0203515C
FUN_0203515C: ; 0x0203515C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02035254
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020352DC
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	mov r2, #0x0
	add r0, r1, #0x4
	str r2, [r4, r0]
	ldr r0, [r5, #0x38]
	bl FUN_02055B30
	cmp r0, #0x1
	bne _02035190
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	add r1, r0, #0x0
	ldr r0, [r5, #0x38]
	bl FUN_02055B8C
_02035190:
	ldr r1, _0203519C ; =FUN_020352E4
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463CC
	pop {r3-r5, pc}
	.balign 4
_0203519C: .word FUN_020352E4

	thumb_func_start FUN_020351A0
FUN_020351A0: ; 0x020351A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0203524C ; =0x000005FD
	bl FUN_020054C8
	bl FUN_02035254
	add r4, r0, #0x0
	mov r0, #0x71
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F214
	cmp r0, #0x1
	bne _020351D4
	add r0, r5, #0x0
	bl FUN_020352C4
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _02035240
_020351D4:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F244
	cmp r0, #0x1
	bne _020351F0
	add r0, r5, #0x0
	bl FUN_020352C8
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _02035240
_020351F0:
	add r0, r5, #0x0
	bl FUN_02060144
	cmp r0, #0x1
	bne _02035208
	add r0, r5, #0x0
	bl FUN_020352CC
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _02035240
_02035208:
	ldr r0, [r5, #0x6c]
	cmp r0, #0x3
	bne _0203521C
	add r0, r5, #0x0
	bl FUN_020352DC
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	b _02035240
_0203521C:
	cmp r0, #0x2
	bne _02035234
	add r0, r5, #0x0
	bl FUN_020352D4
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
	mov r2, #0x1
	add r0, r1, #0x4
	str r2, [r4, r0]
	b _02035240
_02035234:
	add r0, r5, #0x0
	bl FUN_02035270
	mov r1, #0x7
	lsl r1, r1, #0x6
	str r0, [r4, r1]
_02035240:
	ldr r0, [r5, #0x10]
	ldr r1, _02035250 ; =FUN_020352E4
	add r2, r4, #0x0
	bl FUN_020463EC
	pop {r3-r5, pc}
	.balign 4
_0203524C: .word 0x000005FD
_02035250: .word FUN_020352E4

	thumb_func_start FUN_02035254
FUN_02035254: ; 0x02035254
	push {r3, lr}
	mov r1, #0x2
	mov r0, #0xb
	lsl r1, r1, #0x8
	bl AllocFromHeap
	mov r2, #0x0
	strh r2, [r0, #0x2a]
	mov r1, #0x7e
	strh r2, [r0, #0x28]
	lsl r1, r1, #0x2
	str r2, [r0, r1]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02035270
FUN_02035270: ; 0x02035270
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r4, #0x0
	bl FUN_02024DA0
	bl FUN_02024D64
	cmp r0, #0x0
	bne _02035288
	mov r0, #0x1
	orr r4, r0
_02035288:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F388
	cmp r0, #0x0
	bne _0203529A
	mov r0, #0x2
	orr r4, r0
_0203529A:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205ECE0
	cmp r0, #0x0
	bne _020352AC
	mov r0, #0x4
	orr r4, r0
_020352AC:
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_020349CC
	cmp r0, #0x1
	bne _020352BC
	mov r0, #0x6
	orr r4, r0
_020352BC:
	mov r0, #0x6
	lsl r0, r0, #0x6
	orr r0, r4
	pop {r3-r5, pc}

	thumb_func_start FUN_020352C4
FUN_020352C4: ; 0x020352C4
	mov r0, #0x90
	bx lr

	thumb_func_start FUN_020352C8
FUN_020352C8: ; 0x020352C8
	mov r0, #0x94
	bx lr

	thumb_func_start FUN_020352CC
FUN_020352CC: ; 0x020352CC
	ldr r0, _020352D0 ; =0x00000195
	bx lr
	.balign 4
_020352D0: .word 0x00000195

	thumb_func_start FUN_020352D4
FUN_020352D4: ; 0x020352D4
	mov r0, #0x11
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_020352DC
FUN_020352DC: ; 0x020352DC
	ldr r0, _020352E0 ; =0x00000191
	bx lr
	.balign 4
_020352E0: .word 0x00000191

	thumb_func_start FUN_020352E4
FUN_020352E4: ; 0x020352E4
	push {r4-r6, lr}
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldrh r1, [r4, #0x2a]
	cmp r1, #0xf
	bhi _02035362
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02035308: ; jump table (using 16-bit offset)
	.short _02035328 - _02035308 - 2; case 0
	.short _02035358 - _02035308 - 2; case 1
	.short _02035368 - _02035308 - 2; case 2
	.short _02035370 - _02035308 - 2; case 3
	.short _02035378 - _02035308 - 2; case 4
	.short _02035380 - _02035308 - 2; case 5
	.short _02035388 - _02035308 - 2; case 6
	.short _02035390 - _02035308 - 2; case 7
	.short _020353C0 - _02035308 - 2; case 8
	.short _020353D6 - _02035308 - 2; case 9
	.short _020353F6 - _02035308 - 2; case 10
	.short _02035412 - _02035308 - 2; case 11
	.short _02035398 - _02035308 - 2; case 12
	.short _02035440 - _02035308 - 2; case 13
	.short _02035478 - _02035308 - 2; case 14
	.short _02035432 - _02035308 - 2; case 15
_02035328:
	ldr r0, [r5, #0x34]
	bl FUN_02058780
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_0205CE80
	mov r1, #0x7a
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02063964
	add r0, r6, #0x0
	bl FUN_0203549C
	add r0, r6, #0x0
	bl FUN_02035734
	mov r0, #0x1
	strh r0, [r4, #0x2a]
	b _02035484
_02035358:
	add r0, r6, #0x0
	bl FUN_020358E4
	cmp r0, #0x0
	beq _02035364
_02035362:
	b _02035484
_02035364:
	mov r0, #0x0
	pop {r4-r6, pc}
_02035368:
	add r0, r6, #0x0
	bl FUN_02035CA0
	b _02035484
_02035370:
	add r0, r6, #0x0
	bl FUN_02035CDC
	b _02035484
_02035378:
	add r0, r6, #0x0
	bl FUN_020365F0
	b _02035484
_02035380:
	add r0, r6, #0x0
	bl FUN_02036644
	b _02035484
_02035388:
	add r0, r6, #0x0
	bl FUN_02036E08
	b _02035484
_02035390:
	add r0, r6, #0x0
	bl FUN_02036F1C
	b _02035484
_02035398:
	add r0, r5, #0x0
	bl FUN_020464A4
	cmp r0, #0x0
	beq _02035484
	ldr r0, [r5, #0x34]
	bl FUN_02058780
	add r0, r6, #0x0
	bl FUN_0203549C
	add r0, r6, #0x0
	bl FUN_02035734
	mov r0, #0x1
	bl MOD05_021D7CA4
	mov r0, #0xe
	strh r0, [r4, #0x2a]
	b _02035484
_020353C0:
	add r0, r5, #0x0
	bl FUN_020464A4
	cmp r0, #0x0
	beq _02035484
	mov r0, #0x1
	bl MOD05_021D7CA4
	mov r0, #0x9
	strh r0, [r4, #0x2a]
	b _02035484
_020353D6:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02035484
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0203598C
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [r5, #0x34]
	bl FUN_020587B0
	mov r0, #0x1
	pop {r4-r6, pc}
_020353F6:
	add r0, r5, #0x0
	bl FUN_020464A4
	cmp r0, #0x0
	beq _02035484
	ldr r0, [r5, #0x34]
	bl FUN_02058780
	mov r0, #0x1
	bl MOD05_021D7CA4
	mov r0, #0xb
	strh r0, [r4, #0x2a]
	b _02035484
_02035412:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02035484
	mov r2, #0x72
	lsl r2, r2, #0x2
	ldr r1, [r4, r2]
	add r2, #0x30
	ldr r2, [r4, r2]
	add r0, r6, #0x0
	bl FUN_020463EC
	add r0, r4, #0x0
	bl FreeToHeap
	b _02035484
_02035432:
	bl FreeToHeap
	ldr r0, [r5, #0x34]
	bl FUN_020587B0
	mov r0, #0x1
	pop {r4-r6, pc}
_02035440:
	add r1, r5, #0x0
	bl FUN_0203598C
	add r0, r4, #0x0
	bl FUN_02035718
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200CCF8
	add r0, r4, #0x0
	bl FUN_02019178
	add r0, r6, #0x0
	bl FUN_020358A0
	ldr r0, [r5, #0x8]
	mov r1, #0x3
	bl FUN_0201AC68
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [r5, #0x34]
	bl FUN_020587B0
	mov r0, #0x1
	pop {r4-r6, pc}
_02035478:
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02035484
	mov r0, #0x1
	strh r0, [r4, #0x2a]
_02035484:
	ldr r0, [r4, #0x20]
	cmp r0, #0x0
	beq _02035496
	add r0, r4, #0x0
	bl FUN_02035BB0
	ldr r0, [r4, #0x38]
	bl FUN_0201FDEC
_02035496:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0203549C
FUN_0203549C: ; 0x0203549C
	push {r3-r7, lr}
	sub sp, #0x30
	add r4, r0, #0x0
	bl FUN_02046528
	str r0, [sp, #0x1c]
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x30
	bl FUN_0203566C
	str r0, [sp, #0x14]
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0xb
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x14]
	mov r2, #0x3
	lsl r1, r0, #0x1
	add r0, r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02035658 ; =0x0000023B
	add r1, r4, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x1c]
	mov r3, #0x14
	ldr r0, [r0, #0x8]
	bl FUN_02019064
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r3, #0xb
	ldr r0, [sp, #0x1c]
	str r3, [sp, #0x4]
	ldr r0, [r0, #0x8]
	ldr r2, _0203565C ; =0x000003D9
	mov r1, #0x3
	bl FUN_0200CB00
	ldr r2, _0203565C ; =0x000003D9
	add r0, r4, #0x0
	mov r1, #0x1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _02035660 ; =0x00000143
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	mov r1, #0xb
	bl ListMenu_ctor
	str r0, [r4, #0x24]
	mov r5, #0x0
	ldr r0, [sp, #0x14]
	strh r5, [r4, #0x28]
	cmp r0, #0x0
	bls _020355BC
_02035526:
	add r0, r4, r5
	add r0, #0x30
	ldrb r3, [r0, #0x0]
	cmp r3, #0x3
	bne _02035594
	mov r0, #0xb
	bl ScrStrBufs_new
	add r6, r0, #0x0
	mov r0, #0x8
	mov r1, #0xb
	bl String_ctor
	add r1, r4, r5
	add r1, #0x30
	ldrb r1, [r1, #0x0]
	add r7, r0, #0x0
	ldr r0, [sp, #0x18]
	lsl r2, r1, #0x3
	ldr r1, _02035664 ; =UNK_020F2ACC
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r2, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x0
	bl BufferPlayersName
	ldr r2, [sp, #0x20]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl StringExpandPlaceholders
	add r2, r4, r5
	add r2, #0x30
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x24]
	add r1, r7, #0x0
	bl ListMenu_AddItem
	ldr r0, [sp, #0x20]
	bl String_dtor
	add r0, r7, #0x0
	bl String_dtor
	add r0, r6, #0x0
	bl ScrStrBufs_delete
	b _020355A2
_02035594:
	ldr r2, _02035664 ; =UNK_020F2ACC
	lsl r6, r3, #0x3
	ldr r0, [r4, #0x24]
	ldr r1, [sp, #0x18]
	ldr r2, [r2, r6]
	bl ListMenu_ItemFromMsgData
_020355A2:
	ldr r0, [sp, #0x1c]
	add r0, #0x8c
	ldr r1, [r0, #0x0]
	add r0, r4, r5
	add r0, #0x30
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	bne _020355B4
	strh r5, [r4, #0x28]
_020355B4:
	ldr r0, [sp, #0x14]
	add r5, r5, #0x1
	cmp r5, r0
	blo _02035526
_020355BC:
	ldrh r0, [r4, #0x28]
	add r0, r4, r0
	add r0, #0x30
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x1c]
	add r0, #0x8c
	str r1, [r0, #0x0]
	ldr r0, [sp, #0x18]
	bl DestroyMsgData
	ldr r0, [r4, #0x24]
	mov r1, #0x1
	str r0, [sp, #0x24]
	str r4, [sp, #0x28]
	add r0, sp, #0x24
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	ldr r1, [sp, #0x14]
	strb r1, [r0, #0xa]
	ldrb r2, [r0, #0xb]
	mov r1, #0xf
	bic r2, r1
	mov r1, #0x8
	orr r1, r2
	strb r1, [r0, #0xb]
	ldrb r2, [r0, #0xb]
	mov r1, #0x30
	bic r2, r1
	mov r1, #0x10
	orr r1, r2
	strb r1, [r0, #0xb]
	ldr r1, [sp, #0x14]
	ldrb r2, [r0, #0xb]
	cmp r1, #0x4
	blo _0203560E
	mov r1, #0xc0
	bic r2, r1
	mov r1, #0x40
	orr r1, r2
	strb r1, [r0, #0xb]
	b _02035614
_0203560E:
	mov r1, #0xc0
	bic r2, r1
	strb r2, [r0, #0xb]
_02035614:
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r0, _02035668 ; =0x00000402
	mov r1, #0x1c
	str r0, [sp, #0x4]
	ldrh r3, [r4, #0x28]
	add r0, sp, #0x24
	mov r2, #0x4
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02001B8C
	str r0, [r4, #0x20]
	add r0, r4, #0x0
	bl FUN_02019220
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r4, #0x30
	lsl r3, r3, #0x18
	ldr r2, [sp, #0x14]
	add r1, r4, #0x0
	lsr r3, r3, #0x18
	bl FUN_020359B8
	add sp, #0x30
	pop {r3-r7, pc}
	nop
_02035658: .word 0x0000023B
_0203565C: .word 0x000003D9
_02035660: .word 0x00000143
_02035664: .word UNK_020F2ACC
_02035668: .word 0x00000402

	thumb_func_start FUN_0203566C
FUN_0203566C: ; 0x0203566C
	push {r3-r4}
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	sub r3, #0xc0
	mov r2, #0x0
	tst r3, r4
	bne _02035682
	mov r3, #0x8
	strb r3, [r1, #0x0]
	add r2, r2, #0x1
_02035682:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x80
	tst r3, r4
	bne _02035694
	mov r3, #0x7
	strb r3, [r1, r2]
	add r2, r2, #0x1
_02035694:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x1
	tst r3, r4
	bne _020356A6
	mov r3, #0x0
	strb r3, [r1, r2]
	add r2, r2, #0x1
_020356A6:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x2
	tst r3, r4
	bne _020356B8
	mov r3, #0x1
	strb r3, [r1, r2]
	add r2, r2, #0x1
_020356B8:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x4
	tst r3, r4
	bne _020356CA
	mov r3, #0x2
	strb r3, [r1, r2]
	add r2, r2, #0x1
_020356CA:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x8
	tst r3, r4
	bne _020356DC
	mov r3, #0x3
	strb r3, [r1, r2]
	add r2, r2, #0x1
_020356DC:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x10
	tst r3, r4
	bne _020356EE
	mov r3, #0x4
	strb r3, [r1, r2]
	add r2, r2, #0x1
_020356EE:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r4, [r0, r3]
	mov r3, #0x20
	tst r3, r4
	bne _02035700
	mov r3, #0x5
	strb r3, [r1, r2]
	add r2, r2, #0x1
_02035700:
	mov r3, #0x7
	lsl r3, r3, #0x6
	ldr r3, [r0, r3]
	mov r0, #0x40
	tst r0, r3
	bne _02035712
	mov r0, #0x6
	strb r0, [r1, r2]
	add r2, r2, #0x1
_02035712:
	add r0, r2, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02035718
FUN_02035718: ; 0x02035718
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02035B78
	ldr r0, [r4, #0x20]
	mov r1, #0x0
	bl FUN_02001C5C
	ldr r0, [r4, #0x24]
	bl ListMenu_dtor
	mov r0, #0x0
	str r0, [r4, #0x20]
	pop {r4, pc}

	thumb_func_start FUN_02035734
FUN_02035734: ; 0x02035734
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F214
	cmp r0, #0x1
	bne _0203575A
	mov r6, #0x0
	b _0203576C
_0203575A:
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F244
	cmp r0, #0x1
	beq _0203576A
	b _0203588E
_0203576A:
	mov r6, #0x1
_0203576C:
	mov r3, #0x1
	str r3, [sp, #0x0]
	mov r0, #0xc
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02035894 ; =0x0000032D
	add r1, r5, #0x0
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x8]
	add r1, #0x10
	mov r2, #0x3
	bl FUN_02019064
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r3, #0xb
	str r3, [sp, #0x4]
	ldr r0, [r4, #0x8]
	ldr r2, _02035898 ; =0x000003D9
	mov r1, #0x3
	bl FUN_0200CB00
	add r0, r5, #0x0
	ldr r2, _02035898 ; =0x000003D9
	add r0, #0x10
	mov r1, #0x1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0x0
	add r0, #0x10
	mov r1, #0xf
	bl FUN_02019620
	ldr r2, _0203589C ; =0x00000143
	mov r0, #0x0
	mov r1, #0x1a
	mov r3, #0xb
	bl NewMsgDataFromNarc
	str r0, [sp, #0x1c]
	cmp r6, #0x0
	bne _020357D0
	mov r1, #0x9
	bl NewString_ReadMsgData
	b _020357D6
_020357D0:
	mov r1, #0xa
	bl NewString_ReadMsgData
_020357D6:
	mov r1, #0x0
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x10
	add r2, r7, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl AddTextPrinterParameterized
	add r0, r7, #0x0
	bl String_dtor
	mov r0, #0xb
	bl ScrStrBufs_new
	add r7, r0, #0x0
	mov r0, #0x20
	mov r1, #0xb
	bl String_ctor
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	mov r1, #0xb
	bl NewString_ReadMsgData
	str r0, [sp, #0x14]
	cmp r6, #0x0
	bne _02035834
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034E24
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrh r2, [r2, #0x0]
	add r0, r7, #0x0
	mov r3, #0x2
	bl BufferIntegerAsString
	b _0203584C
_02035834:
	add r0, r4, #0x0
	bl FUN_0204BAB0
	mov r1, #0x0
	add r2, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r3, #0x2
	bl BufferIntegerAsString
_0203584C:
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r7, #0x0
	bl StringExpandPlaceholders
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0xff
	str r0, [sp, #0x4]
	mov r1, #0x0
	add r0, r5, #0x0
	ldr r2, [sp, #0x18]
	add r0, #0x10
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x14]
	bl String_dtor
	add r0, r7, #0x0
	bl ScrStrBufs_delete
	ldr r0, [sp, #0x1c]
	bl DestroyMsgData
	add r5, #0x10
	add r0, r5, #0x0
	bl FUN_02019220
_0203588E:
	add sp, #0x20
	pop {r3-r7, pc}
	nop
_02035894: .word 0x0000032D
_02035898: .word 0x000003D9
_0203589C: .word 0x00000143

	thumb_func_start FUN_020358A0
FUN_020358A0: ; 0x020358A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F214
	cmp r0, #0x0
	bne _020358CE
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F244
	cmp r0, #0x0
	beq _020358E0
_020358CE:
	add r0, r5, #0x0
	add r0, #0x10
	mov r1, #0x1
	bl FUN_0200CCF8
	add r5, #0x10
	add r0, r5, #0x0
	bl FUN_02019178
_020358E0:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020358E4
FUN_020358E4: ; 0x020358E4
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	ldr r0, [r5, #0x20]
	bl FUN_02001E5C
	add r6, r0, #0x0
	mov r1, #0x5e
	ldr r0, [r5, #0x20]
	lsl r1, r1, #0x4
	bl FUN_02001D2C
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x20]
	bl FUN_02001E5C
	strh r0, [r5, #0x28]
	ldrh r1, [r5, #0x28]
	cmp r6, r1
	beq _0203593A
	mov r0, #0x67
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x0]
	bl FUN_02035BE8
	ldrh r2, [r5, #0x28]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02035C44
	ldrh r0, [r5, #0x28]
	add r4, #0x8c
	add r0, r5, r0
	add r0, #0x30
	ldrb r0, [r0, #0x0]
	str r0, [r4, #0x0]
_0203593A:
	ldrh r0, [r5, #0x28]
	add r0, r0, #0x1
	lsl r0, r0, #0x2
	add r1, r5, r0
	mov r0, #0x67
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	ldr r0, [r0, #0x0]
	bl FUN_02035C78
	mov r1, #0x1
	ldr r2, [r5, #0x2c]
	mvn r1, r1
	cmp r2, r1
	beq _02035960
	add r0, r1, #0x1
	cmp r2, r0
	beq _02035982
	b _02035966
_02035960:
	mov r0, #0xd
	strh r0, [r5, #0x2a]
	b _02035982
_02035966:
	ldr r0, _02035988 ; =UNK_020F2AD0
	lsl r2, r2, #0x3
	ldr r2, [r0, r2]
	cmp r2, r1
	bne _02035976
	mov r0, #0xd
	strh r0, [r5, #0x2a]
	b _02035982
_02035976:
	add r0, r1, #0x1
	cmp r2, r0
	beq _02035982
	add r0, r7, #0x0
	blx r2
	pop {r3-r7, pc}
_02035982:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_02035988: .word UNK_020F2AD0

	thumb_func_start FUN_0203598C
FUN_0203598C: ; 0x0203598C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0202EDF8
	cmp r0, #0x0
	beq _020359B4
	mov r0, #0x71
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _020359B4
	ldr r0, [r4, #0x7c]
	bl FUN_02052F74
	bl FUN_02031B50
	mov r0, #0x0
	bl FUN_02052B74
_020359B4:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020359B8
FUN_020359B8: ; 0x020359B8
	push {r4-r7, lr}
	sub sp, #0xb4
	ldr r4, _02035B60 ; =UNK_020F2AB4
	str r3, [sp, #0x18]
	add r3, sp, #0x9c
	str r2, [sp, #0x14]
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [sp, #0xc]
	add r1, r2, #0x0
	add r0, #0x38
	mov r2, #0x8
	mov r3, #0xb
	bl MOD05_021D959C
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, _02035B64 ; =0x000034D8
	mov r1, #0x42
	str r0, [sp, #0x8]
	ldr r0, [sp, #0xc]
	mov r2, #0x5
	add r0, #0x38
	mov r3, #0x0
	bl MOD05_021D967C
	ldr r0, _02035B64 ; =0x000034D8
	mov r1, #0x42
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	mov r2, #0x1
	add r0, #0x38
	mov r3, #0x0
	bl MOD05_021D96F4
	ldr r0, _02035B64 ; =0x000034D8
	mov r2, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	mov r1, #0x42
	add r0, #0x38
	add r3, r2, #0x0
	bl MOD05_021D9708
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _02035B64 ; =0x000034D8
	mov r1, #0x42
	str r0, [sp, #0x4]
	ldr r0, [sp, #0xc]
	mov r2, #0x2
	add r0, #0x38
	mov r3, #0x0
	bl MOD05_021D971C
	ldr r0, [sp, #0xc]
	ldr r1, _02035B68 ; =UNK_020F2B14
	add r0, #0x38
	bl MOD05_021D9820
	mov r2, #0x67
	ldr r1, [sp, #0xc]
	lsl r2, r2, #0x2
	str r0, [r1, r2]
	add r0, r1, #0x0
	ldr r0, [r0, r2]
	ldrh r1, [r1, #0x28]
	ldr r0, [r0, #0x0]
	bl FUN_02035BE8
	ldr r0, _02035B6C ; =0x000034D9
	mov r1, #0x42
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	mov r2, #0x4
	add r0, #0x38
	mov r3, #0x0
	bl MOD05_021D96F4
	ldr r0, _02035B6C ; =0x000034D9
	mov r1, #0x42
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	mov r2, #0x3
	add r0, #0x38
	mov r3, #0x0
	bl MOD05_021D9708
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, _02035B6C ; =0x000034D9
	mov r1, #0x42
	str r0, [sp, #0x4]
	ldr r0, [sp, #0xc]
	mov r2, #0x6
	add r0, #0x38
	mov r3, #0x0
	bl MOD05_021D971C
	ldr r0, [sp, #0x14]
	mov r4, #0x0
	cmp r0, #0x0
	bls _02035B2C
	ldr r5, [sp, #0xc]
	ldr r3, _02035B70 ; =UNK_020F2B48
	add r7, r4, #0x0
	add r2, sp, #0x28
	mov r6, #0x6
_02035AA2:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r6, r6, #0x1
	bne _02035AA2
	ldr r0, [r3, #0x0]
	ldr r3, _02035B74 ; =UNK_020F2AA8
	str r0, [r2, #0x0]
	ldmia r3!, {r0-r1}
	add r2, sp, #0x1c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
_02035ABA:
	add r6, sp, #0x28
	add r3, sp, #0x68
	mov r2, #0x6
_02035AC0:
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02035AC0
	ldr r0, [r6, #0x0]
	add r1, sp, #0x68
	str r0, [r3, #0x0]
	mov r0, #0x2
	ldrsh r0, [r1, r0]
	add r0, r0, r7
	strh r0, [r1, #0x2]
	ldr r0, [sp, #0x10]
	ldrb r2, [r0, r4]
	cmp r2, #0x2
	bne _02035AEA
	ldr r0, [sp, #0x18]
	cmp r0, #0x1
	bne _02035AEA
	mov r0, #0x1b
	strh r0, [r1, #0x6]
	b _02035AF2
_02035AEA:
	lsl r0, r2, #0x1
	add r1, r2, r0
	add r0, sp, #0x68
	strh r1, [r0, #0x6]
_02035AF2:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x68
	add r0, #0x38
	bl MOD05_021D9820
	mov r1, #0x1a
	lsl r1, r1, #0x4
	add r2, sp, #0x5c
	add r3, sp, #0x1c
	str r0, [r5, r1]
	ldmia r3!, {r0-r1}
	add r6, r2, #0x0
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r6, #0x0
	str r0, [r2, #0x0]
	mov r0, #0x1a
	lsl r0, r0, #0x4
	ldr r0, [r5, r0]
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	bl FUN_02020074
	ldr r0, [sp, #0x14]
	add r4, r4, #0x1
	add r7, #0x18
	add r5, r5, #0x4
	cmp r4, r0
	blo _02035ABA
_02035B2C:
	ldr r0, [sp, #0xc]
	mov r2, #0x1
	ldrh r0, [r0, #0x28]
	add r0, r0, #0x1
	lsl r1, r0, #0x2
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	mov r0, #0x67
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	bl FUN_02035C18
	ldr r0, [sp, #0x14]
	mov r1, #0x6f
	add r2, r0, #0x1
	ldr r0, [sp, #0xc]
	lsl r1, r1, #0x2
	str r2, [r0, r1]
	mov r0, #0x10
	mov r1, #0x1
	bl FUN_0201E6E4
	add sp, #0xb4
	pop {r4-r7, pc}
	.balign 4
_02035B60: .word UNK_020F2AB4
_02035B64: .word 0x000034D8
_02035B68: .word UNK_020F2B14
_02035B6C: .word 0x000034D9
_02035B70: .word UNK_020F2B48
_02035B74: .word UNK_020F2AA8

	thumb_func_start FUN_02035B78
FUN_02035B78: ; 0x02035B78
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x6f
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r4, #0x0
	cmp r0, #0x0
	bls _02035BA6
	mov r7, #0x67
	lsl r7, r7, #0x2
	add r6, r7, #0x0
	add r6, #0x20
_02035B90:
	lsl r0, r4, #0x2
	add r0, r5, r0
	ldr r0, [r0, r7]
	bl FUN_0200C3DC
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r6]
	cmp r4, r0
	blo _02035B90
_02035BA6:
	add r5, #0x38
	add r0, r5, #0x0
	bl MOD05_021D99F8
	pop {r3-r7, pc}

	thumb_func_start FUN_02035BB0
FUN_02035BB0: ; 0x02035BB0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x6f
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	mov r4, #0x0
	cmp r0, #0x0
	bls _02035BE4
	mov r7, #0x67
	lsl r7, r7, #0x2
	add r6, r7, #0x0
	add r6, #0x20
_02035BC8:
	lsl r0, r4, #0x2
	add r0, r5, r0
	ldr r0, [r0, r7]
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r6]
	cmp r4, r0
	blo _02035BC8
_02035BE4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02035BE8
FUN_02035BE8: ; 0x02035BE8
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0202011C
	add r6, r0, #0x0
	add r3, sp, #0x0
	ldmia r6!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r1, r2, #0x0
	str r0, [r3, #0x0]
	mov r0, #0x18
	mul r0, r4
	add r0, #0x14
	lsl r0, r0, #0xc
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02020044
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_02035C18
FUN_02035C18: ; 0x02035C18
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020201DC
	mov r1, #0x3
	bl _u32_div_f
	add r2, r0, #0x0
	lsl r1, r2, #0x1
	add r1, r2, r1
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02020130
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0202027C
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02035C44
FUN_02035C44: ; 0x02035C44
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x1
	lsl r0, r0, #0x2
	add r1, r5, r0
	mov r0, #0x67
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	mov r1, #0x0
	add r4, r2, #0x0
	ldr r0, [r0, #0x0]
	add r2, r1, #0x0
	bl FUN_02035C18
	add r0, r4, #0x1
	lsl r0, r0, #0x2
	add r1, r5, r0
	mov r0, #0x67
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r2, r1, #0x0
	bl FUN_02035C18
	pop {r3-r5, pc}

	thumb_func_start FUN_02035C78
FUN_02035C78: ; 0x02035C78
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020201DC
	mov r1, #0x3
	bl _u32_div_f
	cmp r1, #0x1
	bne _02035C9E
	add r0, r4, #0x0
	bl FUN_02020388
	cmp r0, #0x0
	bne _02035C9E
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x1
	bl FUN_02035C18
_02035C9E:
	pop {r4, pc}

	thumb_func_start FUN_02035CA0
FUN_02035CA0: ; 0x02035CA0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0200E308
	cmp r0, #0x0
	beq _02035CD8
	add r0, r5, #0x0
	bl FUN_02046528
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	bl FUN_02035718
	add r0, r4, #0x0
	bl FUN_02019178
	add r0, r5, #0x0
	bl FUN_020358A0
	mov r1, #0x72
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	blx r1
	mov r0, #0x3
	strh r0, [r4, #0x2a]
_02035CD8:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02035CDC
FUN_02035CDC: ; 0x02035CDC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _02035D02
	mov r1, #0x72
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	blx r1
_02035D02:
	pop {r4-r6, pc}

	thumb_func_start FUN_02035D04
FUN_02035D04: ; 0x02035D04
	mov r2, #0x72
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	mov r1, #0x3
	strh r1, [r0, #0x2a]
	bx lr

	thumb_func_start FUN_02035D10
FUN_02035D10: ; 0x02035D10
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x72
	ldr r1, _02035D30 ; =FUN_02035D34
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x2
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r4, pc}
	nop
_02035D30: .word FUN_02035D34

	thumb_func_start FUN_02035D34
FUN_02035D34: ; 0x02035D34
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	mov r0, #0xb
	mov r1, #0x20
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl Script_GetTimeOfDay
	str r0, [r4, #0x8]
	add r0, r7, #0x0
	mov r1, #0x0
	bl FUN_0205F524
	str r0, [r4, #0xc]
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0205F524
	str r0, [r4, #0x10]
	add r0, r7, #0x0
	mov r1, #0x2
	bl FUN_0205F524
	str r0, [r4, #0x14]
	add r0, r7, #0x0
	mov r1, #0x3
	bl FUN_0205F524
	str r0, [r4, #0x18]
	add r0, r5, #0x0
	add r0, #0xb0
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	str r0, [r4, #0x1c]
	add r0, r5, #0x0
	bl FUN_02038690
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r4, [r6, r0]
	ldr r1, _02035DC4 ; =FUN_02035DC8
	sub r0, #0x30
	str r1, [r6, r0]
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02035DC4: .word FUN_02035DC8

	thumb_func_start FUN_02035DC8
FUN_02035DC8: ; 0x02035DC8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204649C
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	cmp r1, #0x0
	beq _02035DF0
	mov r0, #0xb
	bl FUN_02016A8C
_02035DF0:
	mov r0, #0xc
	strh r0, [r4, #0x2a]
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02035DF8
FUN_02035DF8: ; 0x02035DF8
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x72
	ldr r1, _02035E18 ; =FUN_02035E1C
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x2
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r4, pc}
	nop
_02035E18: .word FUN_02035E1C

	thumb_func_start FUN_02035E1C
FUN_02035E1C: ; 0x02035E1C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	mov r1, #0x7a
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	mov r2, #0x0
	bl FUN_020379C8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, _02035E4C ; =FUN_02035E50
	sub r1, #0x30
	str r0, [r4, r1]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02035E4C: .word FUN_02035E50

	thumb_func_start FUN_02035E50
FUN_02035E50: ; 0x02035E50
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x40
	add r6, r0, #0x0
	bl memcpy
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r6, #0x0
	add r0, #0x23
	ldrb r0, [r0, #0x0]
	cmp r0, #0x17
	bls _02035E90
	b _020361E6
_02035E90:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02035E9C: ; jump table (using 16-bit offset)
	.short _020361E6 - _02035E9C - 2; case 0
	.short _02035ECC - _02035E9C - 2; case 1
	.short _020361E6 - _02035E9C - 2; case 2
	.short _020360EA - _02035E9C - 2; case 3
	.short _02035F4A - _02035E9C - 2; case 4
	.short _02035FD0 - _02035E9C - 2; case 5
	.short _02036056 - _02035E9C - 2; case 6
	.short _020360AC - _02035E9C - 2; case 7
	.short _02036144 - _02035E9C - 2; case 8
	.short _02036170 - _02035E9C - 2; case 9
	.short _020361CA - _02035E9C - 2; case 10
	.short _020361A4 - _02035E9C - 2; case 11
	.short _020361A4 - _02035E9C - 2; case 12
	.short _020361A4 - _02035E9C - 2; case 13
	.short _020361A4 - _02035E9C - 2; case 14
	.short _020361A4 - _02035E9C - 2; case 15
	.short _020361A4 - _02035E9C - 2; case 16
	.short _020361A4 - _02035E9C - 2; case 17
	.short _020361A4 - _02035E9C - 2; case 18
	.short _020361A4 - _02035E9C - 2; case 19
	.short _020361A4 - _02035E9C - 2; case 20
	.short _020361A4 - _02035E9C - 2; case 21
	.short _020361A4 - _02035E9C - 2; case 22
	.short _020361A4 - _02035E9C - 2; case 23
_02035ECC:
	mov r0, #0xb
	mov r1, #0x30
	bl AllocFromHeap
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r7, #0x0]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r7, #0x4]
	mov r0, #0x1
	strb r0, [r7, #0x11]
	add r0, r6, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strb r0, [r7, #0x14]
	ldr r0, [r7, #0x0]
	bl GetPartyCount
	strb r0, [r7, #0x13]
	mov r0, #0x0
	strh r0, [r7, #0x18]
	strb r0, [r7, #0x12]
	ldr r0, [r5, #0xc]
	bl FUN_0202A918
	str r0, [r7, #0x20]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB28
	str r0, [r7, #0x1c]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	str r0, [r7, #0x2c]
	mov r0, #0x0
	str r0, [r7, #0x28]
	ldr r1, _0203626C ; =UNK_020F2A9C
	add r0, r7, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0207C2A4
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0203796C
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r7, [r4, r0]
	ldr r1, _02036270 ; =FUN_0203684C
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_02035F4A:
	mov r0, #0xb
	mov r1, #0x30
	bl AllocFromHeap
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r7, #0x0]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r7, #0x4]
	mov r1, #0x1
	add r0, r6, #0x0
	strb r1, [r7, #0x11]
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strb r0, [r7, #0x14]
	strb r1, [r7, #0x13]
	ldrh r0, [r6, #0x26]
	strh r0, [r7, #0x18]
	mov r0, #0x2
	strb r0, [r7, #0x12]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB28
	str r0, [r7, #0x1c]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	str r0, [r7, #0x2c]
	mov r0, #0x0
	str r0, [r7, #0x28]
	ldr r1, _02036274 ; =UNK_020F2A8C
	add r0, r7, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0207C2A4
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0203796C
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeap
	ldrh r1, [r6, #0x24]
	strh r1, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x2]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	sub r0, r1, #0x4
	str r7, [r4, r0]
	ldr r1, _02036270 ; =FUN_0203684C
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_02035FD0:
	mov r0, #0xb
	mov r1, #0x30
	bl AllocFromHeap
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r7, #0x0]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r7, #0x4]
	mov r1, #0x1
	add r0, r6, #0x0
	strb r1, [r7, #0x11]
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strb r0, [r7, #0x14]
	strb r1, [r7, #0x13]
	ldrh r0, [r6, #0x26]
	strh r0, [r7, #0x18]
	mov r0, #0x2
	strb r0, [r7, #0x12]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB28
	str r0, [r7, #0x1c]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	str r0, [r7, #0x2c]
	mov r0, #0x0
	str r0, [r7, #0x28]
	ldr r1, _02036274 ; =UNK_020F2A8C
	add r0, r7, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0207C2A4
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0203796C
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeap
	mov r1, #0x0
	strh r1, [r0, #0x0]
	ldr r1, [r6, #0x34]
	strh r1, [r0, #0x2]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	sub r0, r1, #0x4
	str r7, [r4, r0]
	ldr r1, _02036270 ; =FUN_0203684C
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_02036056:
	ldrh r0, [r6, #0x24]
	bl ItemToMailId
	add r3, r0, #0x0
	mov r0, #0xb
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	add r2, #0x22
	ldrb r2, [r2, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02037F2C
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r0, r6, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0xa
	ldrh r0, [r6, #0x24]
	bne _02036090
	add r2, r6, #0x0
	add r2, #0x22
	ldrb r2, [r2, #0x0]
	mov r1, #0x0
	bl FUN_02036BC4
	b _0203609C
_02036090:
	add r2, r6, #0x0
	add r2, #0x22
	ldrb r2, [r2, #0x0]
	mov r1, #0x1
	bl FUN_02036BC4
_0203609C:
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036278 ; =FUN_02036BDC
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_020360AC:
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r6, #0x0
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0xb
	bl FUN_02037F90
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r2, r6, #0x0
	add r2, #0x22
	ldrh r0, [r6, #0x24]
	ldrb r2, [r2, #0x0]
	mov r1, #0x2
	bl FUN_02036BC4
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036278 ; =FUN_02036BDC
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_020360EA:
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeap
	add r1, r6, #0x0
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	str r1, [r0, #0x0]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r5, #0xc]
	bl Sav2_Bag_get
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetProfileAddr
	ldr r1, _0203627C ; =UNK_020F2A90
	add r0, r7, #0x0
	mov r2, #0xb
	bl CreateBagView
	mov r1, #0x7e
	lsl r1, r1, #0x2
	add r3, r5, #0x0
	str r0, [r4, r1]
	add r3, #0x94
	ldr r0, [r4, r1]
	ldr r1, [r5, #0xc]
	ldr r3, [r3, #0x0]
	mov r2, #0x1
	bl FUN_0206E314
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_0203781C
	ldr r1, _02036280 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_02036144:
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeap
	ldrh r1, [r6, #0x24]
	strh r1, [r0, #0x2]
	mov r1, #0x3
	strb r1, [r0, #0x1]
	add r1, r6, #0x0
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	strb r1, [r0, #0x0]
	ldrh r1, [r6, #0x38]
	strh r1, [r0, #0x4]
	ldr r1, [r6, #0x3c]
	str r1, [r0, #0x8]
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	mov r0, #0x6
	strh r0, [r4, #0x2a]
	b _0203625E
_02036170:
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeap
	add r7, r0, #0x0
	ldr r0, [r5, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034A04
	strh r0, [r7, #0x2]
	mov r0, #0x0
	strb r0, [r7, #0x1]
	add r0, r6, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strb r0, [r7, #0x0]
	ldrh r0, [r6, #0x38]
	strh r0, [r7, #0x4]
	ldr r0, [r6, #0x3c]
	str r0, [r7, #0x8]
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r7, [r4, r0]
	mov r0, #0x6
	strh r0, [r4, #0x2a]
	b _0203625E
_020361A4:
	sub r0, #0xb
	add r1, sp, #0x4
	strh r0, [r1, #0x6]
	add r0, r6, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strh r0, [r1, #0x4]
	str r7, [sp, #0x4]
	ldrh r1, [r1, #0x6]
	mov r0, #0x0
	bl FUN_02063948
	mov r1, #0x7a
	lsl r1, r1, #0x2
	add r2, r0, #0x0
	add r0, sp, #0x4
	add r1, r4, r1
	blx r2
	b _0203625E
_020361CA:
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036280 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_020361E6:
	add r0, r6, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x5
	beq _02036200
	cmp r0, #0x6
	beq _02036200
	cmp r0, #0x7
	beq _02036200
	cmp r0, #0x10
	beq _02036200
	cmp r0, #0x8
	bne _02036234
_02036200:
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r2, #0x7e
	lsl r2, r2, #0x2
	str r0, [r4, r2]
	add r0, r6, #0x0
	add r0, #0x22
	ldrb r1, [r0, #0x0]
	ldr r0, [r4, r2]
	cmp r1, #0x6
	blo _02036226
	mov r1, #0x0
	bl FUN_0206E358
	b _0203622A
_02036226:
	bl FUN_0206E358
_0203622A:
	ldr r1, _02036280 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_02036234:
	cmp r0, #0x9
	bne _02036254
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036280 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203625E
_02036254:
	add r0, r5, #0x0
	bl FUN_0204649C
	mov r0, #0xc
	strh r0, [r4, #0x2a]
_0203625E:
	add r0, r6, #0x0
	bl FreeToHeap
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0203626C: .word UNK_020F2A9C
_02036270: .word FUN_0203684C
_02036274: .word UNK_020F2A8C
_02036278: .word FUN_02036BDC
_0203627C: .word UNK_020F2A90
_02036280: .word FUN_020362E4

	thumb_func_start FUN_02036284
FUN_02036284: ; 0x02036284
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x72
	ldr r1, _020362A4 ; =FUN_020362A8
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x2
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r4, pc}
	nop
_020362A4: .word FUN_020362A8

	thumb_func_start FUN_020362A8
FUN_020362A8: ; 0x020362A8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	mov r1, #0x73
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0x0
	bl FUN_0206E358
	mov r0, #0x72
	ldr r1, _020362E0 ; =FUN_020362E4
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020362E0: .word FUN_020362E4

	thumb_func_start FUN_020362E4
FUN_020362E4: ; 0x020362E4
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0xb
	bl BagView_new
	str r0, [sp, #0x8]
	bl FUN_0206E308
	mov r1, #0x7e
	lsl r1, r1, #0x2
	add r2, r0, #0x0
	ldr r0, [sp, #0x8]
	ldr r1, [r4, r1]
	bl memcpy
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, [sp, #0x8]
	bl FUN_0206E384
	cmp r0, #0x5
	bls _02036328
	b _020364EE
_02036328:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02036334: ; jump table (using 16-bit offset)
	.short _02036340 - _02036334 - 2; case 0
	.short _0203637A - _02036334 - 2; case 1
	.short _0203638A - _02036334 - 2; case 2
	.short _020364EE - _02036334 - 2; case 3
	.short _020363F6 - _02036334 - 2; case 4
	.short _020364EE - _02036334 - 2; case 5
_02036340:
	ldr r0, [sp, #0x8]
	bl FUN_0206E37C
	add r1, sp, #0x10
	strh r0, [r1, #0x4]
	ldr r0, [sp, #0x8]
	bl FUN_0206E38C
	add r1, sp, #0x10
	strb r0, [r1, #0x6]
	str r5, [sp, #0x10]
	ldrh r0, [r1, #0x4]
	mov r1, #0x6
	mov r2, #0xb
	bl GetItemAttr
	add r1, r0, #0x0
	lsl r1, r1, #0x10
	mov r0, #0x0
	lsr r1, r1, #0x10
	bl FUN_0205CE48
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r2, r0, #0x0
	add r0, sp, #0x10
	add r1, r4, r1
	blx r2
	b _020364F8
_0203637A:
	ldr r0, [sp, #0x8]
	bl FUN_0206E37C
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0203695C
	b _020364F8
_0203638A:
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r5, r0, #0x0
	bl memset
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r5, #0x0]
	ldr r0, [r6, #0xc]
	bl Sav2_Bag_get
	str r0, [r5, #0x4]
	ldr r0, [r6, #0xc]
	bl FUN_02025838
	str r0, [r5, #0x8]
	ldr r0, [r6, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r5, #0xc]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r0, [r5, #0x18]
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x9
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	bl FUN_0206E37C
	strh r0, [r5, #0x24]
	ldr r1, _02036504 ; =UNK_020F96DC
	add r0, r6, #0x0
	add r2, r5, #0x0
	bl FUN_020373D4
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r5, [r4, r0]
	ldr r1, _02036508 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
	b _020364F8
_020363F6:
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [sp, #0x4]
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	ldr r7, [r0, #0x0]
	ldr r0, [sp, #0x8]
	bl FUN_0206E37C
	add r5, r0, #0x0
	ldr r0, [sp, #0x4]
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	str r0, [sp, #0xc]
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r5, #0x0
	bl ItemIdIsMail
	cmp r0, #0x1
	bne _02036474
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	bne _02036474
	add r0, r5, #0x0
	bl ItemToMailId
	add r3, r0, #0x0
	mov r0, #0xb
	lsl r2, r7, #0x18
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	mov r1, #0x2
	lsr r2, r2, #0x18
	bl FUN_02037F2C
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	lsl r2, r7, #0x18
	add r0, r5, #0x0
	mov r1, #0x0
	lsr r2, r2, #0x18
	bl FUN_02036BC4
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _0203650C ; =FUN_02036BDC
	add r0, r4, #0x0
	bl FUN_02035D04
	b _020364F8
_02036474:
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r5, r0, #0x0
	bl memset
	ldr r0, [sp, #0x4]
	str r0, [r5, #0x0]
	ldr r0, [r6, #0xc]
	bl Sav2_Bag_get
	str r0, [r5, #0x4]
	ldr r0, [r6, #0xc]
	bl FUN_02025838
	str r0, [r5, #0x8]
	ldr r0, [r6, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r5, #0xc]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r4, r0
	str r0, [r5, #0x18]
	add r0, r5, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	bl FUN_0206E37C
	strh r0, [r5, #0x24]
	add r0, r5, #0x0
	add r0, #0x22
	strb r7, [r0, #0x0]
	str r6, [r5, #0x1c]
	ldrh r0, [r5, #0x24]
	cmp r0, #0x0
	bne _020364CC
	mov r1, #0x0
	b _020364CE
_020364CC:
	mov r1, #0xa
_020364CE:
	add r0, r5, #0x0
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r1, _02036504 ; =UNK_020F96DC
	add r0, r6, #0x0
	add r2, r5, #0x0
	bl FUN_020373D4
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r5, [r4, r0]
	ldr r1, _02036508 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
	b _020364F8
_020364EE:
	add r0, r6, #0x0
	bl FUN_0204649C
	mov r0, #0xc
	strh r0, [r4, #0x2a]
_020364F8:
	ldr r0, [sp, #0x8]
	bl FreeToHeap
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_02036504: .word UNK_020F96DC
_02036508: .word FUN_02035E50
_0203650C: .word FUN_02036BDC

	thumb_func_start FUN_02036510
FUN_02036510: ; 0x02036510
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x72
	ldr r1, _02036530 ; =FUN_02036534
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x2
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r4, pc}
	nop
_02036530: .word FUN_02036534

	thumb_func_start FUN_02036534
FUN_02036534: ; 0x02036534
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0xb
	bl FUN_02065054
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	str r5, [sp, #0x0]
	ldr r0, [r4, r1]
	mov r2, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x1
	add r1, r0, #0x0
	mov r3, #0xff
	bl FUN_02064E90
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02038680
	mov r0, #0x72
	ldr r1, _02036580 ; =FUN_02036584
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02036580: .word FUN_02036584

	thumb_func_start FUN_02036584
FUN_02036584: ; 0x02036584
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	mov r1, #0x7e
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02065314
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02065070
	add r0, r5, #0x0
	bl FUN_0204649C
	mov r0, #0xc
	strh r0, [r4, #0x2a]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020365BC
FUN_020365BC: ; 0x020365BC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	bl FUN_02035718
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200CCF8
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	add r0, r4, #0x0
	bl FUN_02019178
	add r0, r5, #0x0
	bl FUN_020358A0
	mov r0, #0x4
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020365F0
FUN_020365F0: ; 0x020365F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046528
	ldr r0, [r0, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	beq _02036618
	mov r2, #0x0
	ldr r1, _0203663C ; =0x000007F2
	add r0, r5, #0x0
	add r3, r2, #0x0
	bl FUN_02038CD8
	b _02036636
_02036618:
	mov r0, #0x20
	mov r1, #0x8
	bl AllocFromHeap
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r3, [r4, r1]
	mov r2, #0x0
	strh r2, [r3, #0x4]
	ldr r1, _02036640 ; =0x000007D5
	add r0, r5, #0x0
	add r3, r3, #0x4
	bl FUN_02038CD8
_02036636:
	mov r0, #0x5
	strh r0, [r4, #0x2a]
	pop {r3-r5, pc}
	.balign 4
_0203663C: .word 0x000007F2
_02036640: .word 0x000007D5

	thumb_func_start FUN_02036644
FUN_02036644: ; 0x02036644
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r5, [r4, r0]
	ldr r0, [r6, #0xc]
	bl FUN_0202280C
	cmp r0, #0x0
	beq _0203666C
	mov r0, #0x0
	strh r0, [r4, #0x2a]
	pop {r4-r6, pc}
_0203666C:
	ldrh r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02036676
	mov r0, #0x0
	b _02036678
_02036676:
	mov r0, #0xf
_02036678:
	strh r0, [r4, #0x2a]
	add r0, r5, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02036684
FUN_02036684: ; 0x02036684
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x72
	ldr r1, _020366A4 ; =FUN_020366A8
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x2
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r4, pc}
	nop
_020366A4: .word FUN_020366A8

	thumb_func_start FUN_020366A8
FUN_020366A8: ; 0x020366A8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02037EF8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, _020366D0 ; =FUN_020366D4
	sub r1, #0x30
	str r0, [r4, r1]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020366D0: .word FUN_020366D4

	thumb_func_start FUN_020366D4
FUN_020366D4: ; 0x020366D4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r5, #0x0
	bl FUN_0204649C
	mov r0, #0xc
	strh r0, [r4, #0x2a]
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02036700
FUN_02036700: ; 0x02036700
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x0
	bl MOD05_021D7CA4
	mov r0, #0x72
	ldr r1, _02036720 ; =FUN_02036724
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x2
	strh r0, [r4, #0x2a]
	mov r0, #0x1
	pop {r4, pc}
	nop
_02036720: .word FUN_02036724

	thumb_func_start FUN_02036724
FUN_02036724: ; 0x02036724
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r2, [r5, #0xc]
	mov r0, #0x2
	mov r1, #0x0
	mov r3, #0xb
	bl FUN_02085338
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r0, sp, #0x0
	mov r1, #0x4
	bl FUN_0201373C
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	add r1, sp, #0x0
	bl FUN_020853BC
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	bl FUN_02037E80
	mov r0, #0x72
	ldr r1, _02036778 ; =FUN_0203677C
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02036778: .word FUN_0203677C

	thumb_func_start FUN_0203677C
FUN_0203677C: ; 0x0203677C
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020853E4
	cmp r0, #0x0
	bne _020367C6
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r1, sp, #0x0
	bl FUN_020853FC
	bl FUN_0202EDF8
	cmp r0, #0x0
	beq _020367C0
	add r0, sp, #0x0
	bl FUN_02052DE8
	ldr r0, [r4, #0x78]
	add r1, sp, #0x0
	bl FUN_02052CD8
_020367C0:
	mov r0, #0x8
	strh r0, [r5, #0x2a]
	b _020367CA
_020367C6:
	mov r0, #0xc
	strh r0, [r5, #0x2a]
_020367CA:
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	bl FUN_020853A8
	add r0, r4, #0x0
	bl FUN_0204649C
	ldr r0, [r4, #0x7c]
	bl FUN_02052F74
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020367E8
FUN_020367E8: ; 0x020367E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	bl FUN_02035718
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_0200CCF8
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	add r0, r4, #0x0
	bl FUN_02019178
	add r0, r5, #0x0
	bl FUN_020358A0
	ldr r0, [r6, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205F214
	cmp r0, #0x1
	bne _02036834
	ldr r1, _02036848 ; =0x00002275
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_02038D10
	b _0203683E
_02036834:
	add r0, r5, #0x0
	mov r1, #0x4
	mov r2, #0x0
	bl FUN_02038D10
_0203683E:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_02036848: .word 0x00002275

	thumb_func_start FUN_0203684C
FUN_0203684C: ; 0x0203684C
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x30
	add r7, r0, #0x0
	bl memcpy
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldrb r0, [r7, #0x12]
	cmp r0, #0x2
	bne _0203692E
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x7f
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x40
	str r1, [sp, #0x0]
	mov r1, #0x0
	add r5, r0, #0x0
	bl memset
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r5, #0x0]
	ldr r0, [r6, #0xc]
	bl Sav2_Bag_get
	str r0, [r5, #0x4]
	ldr r0, [r6, #0xc]
	bl FUN_02025838
	str r0, [r5, #0x8]
	ldr r0, [r6, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r5, #0xc]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r4, r0
	add r1, r5, #0x0
	str r0, [r5, #0x18]
	mov r0, #0x0
	add r1, #0x21
	strb r0, [r1, #0x0]
	ldr r1, [sp, #0x0]
	str r6, [r5, #0x1c]
	ldrh r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020368E2
	add r1, r5, #0x0
	mov r2, #0x7
	add r1, #0x20
	strb r2, [r1, #0x0]
	b _020368EE
_020368E2:
	add r0, r5, #0x0
	mov r1, #0x8
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldrh r0, [r0, #0x2]
_020368EE:
	str r0, [r5, #0x34]
	ldr r0, [sp, #0x0]
	add r2, r5, #0x0
	ldrh r0, [r0, #0x0]
	strh r0, [r5, #0x24]
	add r0, r5, #0x0
	ldrb r1, [r7, #0x14]
	add r0, #0x22
	strb r1, [r0, #0x0]
	ldrh r0, [r7, #0x18]
	strh r0, [r5, #0x26]
	add r0, r5, #0x0
	ldrb r1, [r7, #0x16]
	add r0, #0x28
	strb r1, [r0, #0x0]
	ldr r1, _02036954 ; =UNK_020F96DC
	add r0, r6, #0x0
	bl FUN_020373D4
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r5, [r4, r0]
	ldr r1, _02036958 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
	b _0203694A
_0203692E:
	mov r1, #0x7a
	lsl r1, r1, #0x2
	ldrb r2, [r7, #0x14]
	add r0, r6, #0x0
	add r1, r4, r1
	bl FUN_020379C8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036958 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
_0203694A:
	add r0, r7, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02036954: .word UNK_020F96DC
_02036958: .word FUN_02035E50

	thumb_func_start FUN_0203695C
FUN_0203695C: ; 0x0203695C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02046528
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	mov r0, #0xb
	bl FUN_020851B8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	bl Sav2_Bag_get
	str r0, [sp, #0x0]
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_020851DC
	mov r5, #0x0
	add r4, r5, #0x0
_0203699A:
	add r0, r4, #0x0
	bl BerryToItemId
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	mov r2, #0x1
	mov r3, #0xb
	bl Bag_HasItem
	cmp r0, #0x1
	bne _020369C6
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_020851DC
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_020369C6:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x40
	blo _0203699A
	ldr r0, [sp, #0x4]
	add r3, sp, #0x8
	add r0, #0x94
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	add r2, sp, #0x8
	add r3, #0x1
	bl FUN_0206F17C
	mov r0, #0x7e
	add r2, sp, #0x8
	lsl r0, r0, #0x2
	ldrb r1, [r2, #0x1]
	add r3, r5, #0x3
	lsl r3, r3, #0x18
	ldrb r2, [r2, #0x0]
	ldr r0, [r6, r0]
	lsr r3, r3, #0x18
	bl FUN_020851F8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r0, [sp, #0x4]
	ldr r1, [r6, r1]
	bl FUN_0203791C
	ldr r1, _02036A10 ; =FUN_02036A14
	add r0, r6, #0x0
	bl FUN_02035D04
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02036A10: .word FUN_02036A14

	thumb_func_start FUN_02036A14
FUN_02036A14: ; 0x02036A14
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	add r1, sp, #0x0
	ldr r0, [r4, r0]
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_0208524C
	add r0, r5, #0x0
	add r3, sp, #0x0
	add r0, #0x94
	ldrb r2, [r3, #0x0]
	ldrb r3, [r3, #0x1]
	ldr r0, [r0, #0x0]
	mov r1, #0x4
	bl FUN_0206F190
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r0, #0xb
	bl FUN_02016A8C
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036A74 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02036A74: .word FUN_020362E4

	thumb_func_start FUN_02036A78
FUN_02036A78: ; 0x02036A78
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	mov r1, #0x7e
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r0, #0xb
	bl FUN_02016A8C
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036AB4 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02036AB4: .word FUN_020362E4

	thumb_func_start FUN_02036AB8
FUN_02036AB8: ; 0x02036AB8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r1, [r4, r0]
	mov r0, #0xb
	ldr r7, [r1, #0x0]
	bl FUN_02016A8C
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r5, [r4, r0]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _02036B0E
	mov r0, #0xb
	add r1, r5, #0x0
	bl FUN_02016A8C
	mov r1, #0x7a
	lsl r1, r1, #0x2
	lsl r2, r7, #0x18
	add r0, r6, #0x0
	add r1, r4, r1
	lsr r2, r2, #0x18
	bl FUN_020379C8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036B88 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
	b _02036B82
_02036B0E:
	ldr r0, [r6, #0xc]
	bl SavArray_PlayerParty_get
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	add r2, r0, #0x0
	ldr r0, [r5, #0x14]
	add r1, r6, #0x0
	lsl r0, r0, #0x5
	add r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x18]
	lsl r0, r0, #0x5
	add r0, #0x10
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0x4]
	ldr r3, [r5, #0x1c]
	mov r0, #0xb
	lsl r3, r3, #0x10
	lsr r3, r3, #0x10
	bl FUN_02063888
	ldr r1, [r5, #0x1c]
	add r7, r0, #0x0
	lsl r1, r1, #0x10
	mov r0, #0x1
	lsr r1, r1, #0x10
	mov r2, #0xb
	bl FUN_0202914C
	add r1, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	bl FUN_02028AD4
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r0, #0xb
	bl FUN_02016A8C
	add r0, r6, #0x0
	bl FUN_0204649C
	mov r0, #0x72
	ldr r1, _02036B8C ; =FUN_020638BC
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, #0x30
	str r7, [r4, r0]
	mov r0, #0xa
	strh r0, [r4, #0x2a]
_02036B82:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02036B88: .word FUN_02035E50
_02036B8C: .word FUN_020638BC

	thumb_func_start FUN_02036B90
FUN_02036B90: ; 0x02036B90
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	mov r1, #0x73
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036BC0 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02036BC0: .word FUN_020362E4

	thumb_func_start FUN_02036BC4
FUN_02036BC4: ; 0x02036BC4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xb
	mov r1, #0x4
	add r6, r2, #0x0
	bl AllocFromHeap
	strh r5, [r0, #0x0]
	strb r6, [r0, #0x2]
	strb r4, [r0, #0x3]
	pop {r4-r6, pc}

	thumb_func_start FUN_02036BDC
FUN_02036BDC: ; 0x02036BDC
	push {r4-r6, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r6, [r4, r0]
	ldrb r1, [r6, #0x3]
	cmp r1, #0x3
	bhi _02036CD4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02036C06: ; jump table (using 16-bit offset)
	.short _02036C58 - _02036C06 - 2; case 0
	.short _02036C98 - _02036C06 - 2; case 1
	.short _02036C32 - _02036C06 - 2; case 2
	.short _02036C0E - _02036C06 - 2; case 3
_02036C0E:
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_0208562C
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036CE4 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	b _02036CD4
_02036C32:
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_0208562C
	mov r1, #0x7a
	lsl r1, r1, #0x2
	ldrb r2, [r6, #0x2]
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_020379C8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036CE8 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
	b _02036CD4
_02036C58:
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_020855E4
	cmp r0, #0x1
	bne _02036C70
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0xc
	bl FUN_02036CEC
	b _02036CD4
_02036C70:
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0208562C
	mov r1, #0x7a
	lsl r1, r1, #0x2
	ldrb r2, [r6, #0x2]
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_020379C8
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036CE8 ; =FUN_02035E50
	add r0, r4, #0x0
	bl FUN_02035D04
	b _02036CD4
_02036C98:
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_020855E4
	cmp r0, #0x1
	bne _02036CB0
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0xb
	bl FUN_02036CEC
	b _02036CD4
_02036CB0:
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0208562C
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036CE4 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
_02036CD4:
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02036CE4: .word FUN_020362E4
_02036CE8: .word FUN_02035E50

	thumb_func_start FUN_02036CEC
FUN_02036CEC: ; 0x02036CEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x7f
	add r6, r1, #0x0
	str r2, [sp, #0x0]
	lsl r0, r0, #0x2
	ldr r7, [r6, r0]
	mov r0, #0xb
	mov r1, #0x40
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl SavArray_PlayerParty_get
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl Sav2_Bag_get
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl FUN_02025838
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0xc]
	mov r0, #0x7a
	lsl r0, r0, #0x2
	add r0, r6, r0
	str r0, [r4, #0x18]
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	ldrh r0, [r7, #0x0]
	strh r0, [r4, #0x24]
	add r0, r4, #0x0
	ldrb r1, [r7, #0x2]
	add r0, #0x22
	strb r1, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x20
	strb r0, [r1, #0x0]
	str r5, [r4, #0x1c]
	ldrb r1, [r7, #0x2]
	ldr r0, [r4, #0x0]
	bl GetPartyMonByIndex
	add r1, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_0208560C
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_0208562C
	ldr r1, _02036D8C ; =UNK_020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r4, [r6, r0]
	ldr r1, _02036D90 ; =FUN_02035E50
	add r0, r6, #0x0
	bl FUN_02035D04
	pop {r3-r7, pc}
	nop
_02036D8C: .word UNK_020F96DC
_02036D90: .word FUN_02035E50

	thumb_func_start FUN_02036D94
FUN_02036D94: ; 0x02036D94
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02087E14
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036DD0 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_02036DD0: .word FUN_020362E4

	thumb_func_start FUN_02036DD4
FUN_02036DD4: ; 0x02036DD4
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	mov r1, #0x73
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, _02036E04 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02036E04: .word FUN_020362E4

	thumb_func_start FUN_02036E08
FUN_02036E08: ; 0x02036E08
	push {r3-r7, lr}
	sub sp, #0x48
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r6, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r5, [r6, r0]
	bl FUN_0200541C
	mov r0, #0x3
	mov r1, #0x49
	lsl r2, r0, #0x10
	bl FUN_0201681C
	ldr r0, [r4, #0xc]
	bl SavArray_PlayerParty_get
	ldrb r1, [r5, #0x0]
	str r0, [sp, #0x20]
	bl GetPartyMonByIndex
	str r0, [sp, #0x24]
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	ldr r0, [r4, #0xc]
	bne _02036E9E
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [sp, #0x28]
	ldr r0, [r4, #0xc]
	bl FUN_02079C70
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02024DA0
	str r0, [sp, #0x2c]
	ldr r0, [r4, #0xc]
	bl Sav2_Bag_get
	str r0, [sp, #0x30]
	ldr r0, [r4, #0xc]
	bl FUN_02029FC8
	str r0, [sp, #0x34]
	ldr r0, [r4, #0xc]
	bl FUN_0204C1A8
	ldr r1, [sp, #0x2c]
	str r7, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x30]
	ldr r3, [sp, #0x28]
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x34]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x8]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x14]
	mov r0, #0x1
	str r0, [sp, #0x18]
	mov r0, #0x49
	str r0, [sp, #0x1c]
	ldrh r2, [r5, #0x4]
	ldr r0, [sp, #0x20]
	bl FUN_0206C700
	b _02036EF2
_02036E9E:
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [sp, #0x38]
	ldr r0, [r4, #0xc]
	bl FUN_02079C70
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02024DA0
	str r0, [sp, #0x3c]
	ldr r0, [r4, #0xc]
	bl Sav2_Bag_get
	str r0, [sp, #0x40]
	ldr r0, [r4, #0xc]
	bl FUN_02029FC8
	str r0, [sp, #0x44]
	ldr r0, [r4, #0xc]
	bl FUN_0204C1A8
	ldr r1, [sp, #0x3c]
	str r7, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x40]
	ldr r3, [sp, #0x38]
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x44]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x8]
	ldr r1, [sp, #0x24]
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r0, [sp, #0x18]
	mov r0, #0x49
	str r0, [sp, #0x1c]
	ldrh r2, [r5, #0x4]
	ldr r0, [sp, #0x20]
	bl FUN_0206C700
_02036EF2:
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x4
	bl AllocFromHeap
	ldrb r1, [r5, #0x0]
	str r1, [r0, #0x0]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	sub r0, r1, #0x4
	ldr r0, [r6, r0]
	bl FreeToHeap
	mov r0, #0x7e
	lsl r0, r0, #0x2
	str r4, [r6, r0]
	mov r0, #0x7
	strh r0, [r6, #0x2a]
	add sp, #0x48
	pop {r3-r7, pc}

	thumb_func_start FUN_02036F1C
FUN_02036F1C: ; 0x02036F1C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0206C91C
	cmp r0, #0x1
	bne _02036F98
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_0206C92C
	mov r0, #0x49
	bl FUN_020168D0
	ldr r0, _02036F9C ; =0x00000475
	mov r1, #0x0
	bl FUN_02005350
	mov r0, #0x0
	bl FUN_0200415C
	ldr r1, [r5, #0x1c]
	add r0, r5, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_0204ADBC
	mov r1, #0x73
	lsl r1, r1, #0x2
	add r0, r5, #0x0
	add r1, r4, r1
	bl FUN_02037844
	mov r1, #0x7e
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	add r1, r1, #0x4
	ldr r1, [r4, r1]
	ldr r1, [r1, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0206E358
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r1, _02036FA0 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
_02036F98:
	pop {r3-r5, pc}
	nop
_02036F9C: .word 0x00000475
_02036FA0: .word FUN_020362E4
