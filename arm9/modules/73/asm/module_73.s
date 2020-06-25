	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD73_021D74E0
MOD73_021D74E0: ; 0x021D74E0
	push {r3, lr}
	ldr r0, [r0, #0x18]
	bl MOD73_021D88B0
	bl FUN_0201C30C
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD73_021D74E0

	thumb_func_start MOD73_021D74F0
MOD73_021D74F0: ; 0x021D74F0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl FUN_0200628C
	mov r2, #2
	add r4, r0, #0
	mov r0, #3
	mov r1, #0x38
	lsl r2, r2, #0x10
	bl FUN_0201681C
	ldr r1, _021D757C ; =0x000015E8
	add r0, r5, #0
	mov r2, #0x38
	bl FUN_02006268
	ldr r2, _021D757C ; =0x000015E8
	add r5, r0, #0
	mov r1, #0
	bl memset
	str r5, [r4, #0x18]
	mov r1, #0x38
	str r1, [r5]
	mov r0, #0x10
	bl FUN_0201C24C
	ldrh r0, [r4, #6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bne _021D7534
	mov r1, #1
	b _021D7536
_021D7534:
	mov r1, #0
_021D7536:
	ldr r0, _021D7580 ; =0x00001428
	str r1, [r5, r0]
	ldr r1, [r4, #0x10]
	add r0, r5, #0
	ldr r1, [r1, #0x10]
	bl MOD73_021D8DF4
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x18]
	bl FUN_02025084
	str r0, [r5, #0x24]
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x18]
	bl FUN_02024FF4
	str r0, [r5, #0x28]
	mov r0, #0xae
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldr r0, _021D7584 ; =MOD73_021D74E0
	add r1, r4, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	ldr r1, _021D7588 ; =0x0000049F
	mov r0, #0xc
	mov r2, #1
	bl FUN_0200433C
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_021D757C: .word 0x000015E8
_021D7580: .word 0x00001428
_021D7584: .word MOD73_021D74E0
_021D7588: .word 0x0000049F
	thumb_func_end MOD73_021D74F0

	thumb_func_start MOD73_021D758C
MOD73_021D758C: ; 0x021D758C
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	add r5, r1, #0
	bl FUN_0200628C
	add r7, r0, #0
	add r0, r4, #0
	bl FUN_02006278
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	ldr r1, _021D763C ; =0x021DBC9C
	str r0, [sp]
	lsl r0, r0, #3
	add r1, r1, r0
	ldr r0, [r5]
	cmp r0, #0
	beq _021D75BA
	cmp r0, #1
	beq _021D75FC
	cmp r0, #2
	beq _021D760C
	b _021D7620
_021D75BA:
	ldr r3, [r1]
	cmp r3, #0
	beq _021D7620
	ldr r6, [r1, #4]
	add r2, r4, #0
	add r0, r7, #0
	add r1, r4, #0
	add r2, #0x10
	blx r3
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021D75DC
	ldr r0, [r4, #0x18]
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4, #0x14]
_021D75DC:
	ldr r1, [r4, #0xc]
	ldr r0, [sp]
	cmp r0, r1
	beq _021D7620
	mov r0, #0
	str r0, [r4, #0x10]
	ldrh r0, [r7, #6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _021D7620
	cmp r6, #0
	beq _021D7620
	str r6, [r4, #8]
	mov r0, #1
	str r0, [r5]
	b _021D7620
_021D75FC:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_02031588
	mov r0, #2
	str r0, [r5]
	b _021D7620
_021D760C:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020315D8
	cmp r0, #0
	beq _021D7620
	mov r0, #0
	str r0, [r5]
	str r0, [r4, #8]
_021D7620:
	add r0, r4, #0
	bl MOD73_021D8858
	ldr r0, [r4]
	ldr r1, [r4, #0x20]
	bl FUN_020335F0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021D7638
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D7638:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D763C: .word MOD73_021DBC9C
	thumb_func_end MOD73_021D758C

	thumb_func_start MOD73_021D7640
MOD73_021D7640: ; 0x021D7640
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl FUN_0200628C
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_02006278
	add r7, r0, #0
	ldr r4, [r7]
	bl MOD73_021D8E90
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	bl FUN_02015F1C
	bl FUN_0201C29C
	ldr r2, _021D7688 ; =0x000015E8
	add r0, r7, #0
	mov r1, #0
	bl MI_CpuFill8
	add r0, r5, #0
	bl FUN_0200627C
	mov r0, #0
	str r0, [r6, #0x18]
	add r0, r4, #0
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7688: .word 0x000015E8
	thumb_func_end MOD73_021D7640

	thumb_func_start MOD73_021D768C
MOD73_021D768C: ; 0x021D768C
	str r1, [r0, #0x18]
	mov r1, #1
	str r1, [r0, #0x14]
	bx lr
	thumb_func_end MOD73_021D768C

	thumb_func_start MOD73_021D7694
MOD73_021D7694: ; 0x021D7694
	mov r1, #1
	str r1, [r0, #4]
	bx lr
	.align 2, 0
	thumb_func_end MOD73_021D7694

	thumb_func_start MOD73_021D769C
MOD73_021D769C: ; 0x021D769C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r0, [r4]
	add r5, r1, #0
	cmp r0, #0
	beq _021D76B8
	cmp r0, #1
	bne _021D76B0
	b _021D77C6
_021D76B0:
	cmp r0, #2
	bne _021D76B6
	b _021D77E4
_021D76B6:
	b _021D77F4
_021D76B8:
	add r0, r5, #0
	bl MOD73_021D852C
	ldr r0, _021D77FC ; =0x00001424
	ldr r0, [r5, r0]
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D76D4
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r5, r0
	bl MOD73_021DB884
_021D76D4:
	ldr r0, [r5, #0x24]
	ldr r2, _021D7800 ; =0x00001574
	str r0, [sp]
	ldr r0, [r5]
	ldr r3, _021D7804 ; =0x00001420
	str r0, [sp, #4]
	ldr r0, _021D7808 ; =0x0000054C
	ldr r1, [r5, r3]
	add r3, #0xc
	add r0, r5, r0
	add r2, r5, r2
	add r3, r5, r3
	bl MOD73_021D9A28
	ldr r0, _021D780C ; =0x000005A4
	add r0, r5, r0
	bl MOD73_021D9E80
	ldr r0, [r5, #0x24]
	ldr r2, _021D7800 ; =0x00001574
	str r0, [sp]
	ldr r0, [r5]
	ldr r3, _021D7804 ; =0x00001420
	str r0, [sp, #4]
	ldr r0, _021D7810 ; =0x0000063C
	ldr r1, [r5, r3]
	add r3, #0xc
	add r0, r5, r0
	add r2, r5, r2
	add r3, r5, r3
	bl MOD73_021DA210
	mov r0, #0x16
	lsl r0, r0, #6
	add r0, r5, r0
	bl MOD73_021D9D84
	ldr r0, _021D7814 ; =0x0000058C
	add r0, r5, r0
	bl MOD73_021D9D84
	ldr r0, _021D7818 ; =0x00000598
	add r0, r5, r0
	bl MOD73_021D9D84
	ldr r3, _021D781C ; =0x0000142C
	ldr r0, _021D7820 ; =0x0000061C
	add r2, r3, #0
	add r1, r5, r3
	sub r2, #0xc
	sub r3, #8
	ldr r2, [r5, r2]
	ldr r3, [r5, r3]
	add r0, r5, r0
	bl MOD73_021DA0E0
	mov r0, #0x67
	lsl r0, r0, #4
	add r0, r5, r0
	bl MOD73_021DA81C
	ldr r0, _021D7824 ; =0x00000A84
	add r0, r5, r0
	bl MOD73_021DAD78
	ldr r1, _021D7804 ; =0x00001420
	ldr r0, _021D7828 ; =0x00000B04
	ldr r1, [r5, r1]
	add r0, r5, r0
	bl MOD73_021DAF70
	mov r0, #0x2d
	lsl r0, r0, #4
	add r0, r5, r0
	bl MOD73_021DB2FC
	add r0, r5, #0
	bl MOD73_021D8630
	bl FUN_02033E74
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	ldr r0, _021D7804 ; =0x00001420
	ldr r0, [r5, r0]
	cmp r0, #1
	ble _021D778E
	ldr r0, _021D7808 ; =0x0000054C
	add r0, r5, r0
	bl MOD73_021D9AC8
_021D778E:
	ldr r0, _021D780C ; =0x000005A4
	mov r1, #3
	add r0, r5, r0
	mov r2, #1
	bl MOD73_021D9FC0
	ldr r0, _021D780C ; =0x000005A4
	mov r1, #4
	add r0, r5, r0
	mov r2, #1
	bl MOD73_021D9FC0
	ldr r0, _021D780C ; =0x000005A4
	mov r1, #5
	add r0, r5, r0
	mov r2, #1
	bl MOD73_021D9FC0
	ldr r0, _021D780C ; =0x000005A4
	mov r1, #6
	add r0, r5, r0
	mov r2, #1
	bl MOD73_021D9FC0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D77F4
_021D77C6:
	mov r0, #6
	mov r1, #1
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r5]
	ldr r3, _021D782C ; =0x0000FFFF
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D77F4
_021D77E4:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D77F4
	ldr r0, [r5, #0xc]
	add sp, #0xc
	add r0, r0, #1
	pop {r4, r5, pc}
_021D77F4:
	ldr r0, [r5, #0xc]
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021D77FC: .word 0x00001424
_021D7800: .word 0x00001574
_021D7804: .word 0x00001420
_021D7808: .word 0x0000054C
_021D780C: .word 0x000005A4
_021D7810: .word 0x0000063C
_021D7814: .word 0x0000058C
_021D7818: .word 0x00000598
_021D781C: .word 0x0000142C
_021D7820: .word 0x0000061C
_021D7824: .word 0x00000A84
_021D7828: .word 0x00000B04
_021D782C: .word 0x0000FFFF
	thumb_func_end MOD73_021D769C

	thumb_func_start MOD73_021D7830
MOD73_021D7830: ; 0x021D7830
	push {r4, lr}
	ldr r0, _021D7854 ; =0x00001424
	add r4, r1, #0
	ldr r0, [r4, r0]
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D784E
	ldr r3, _021D7854 ; =0x00001424
	mov r1, #0
	ldr r3, [r4, r3]
	mov r0, #0x16
	add r2, r1, #0
	bl MOD73_021D90D0
_021D784E:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	pop {r4, pc}
	.align 2, 0
_021D7854: .word 0x00001424
	thumb_func_end MOD73_021D7830

	thumb_func_start MOD73_021D7858
MOD73_021D7858: ; 0x021D7858
	ldr r0, [r1, #0xc]
	bx lr
	thumb_func_end MOD73_021D7858

	thumb_func_start MOD73_021D785C
MOD73_021D785C: ; 0x021D785C
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _021D786E
	cmp r1, #1
	beq _021D7884
	b _021D78AA
_021D786E:
	ldr r1, _021D78B0 ; =0x00001420
	mov r0, #0xd7
	lsl r0, r0, #2
	ldr r1, [r5, r1]
	add r0, r5, r0
	bl MOD73_021D96B0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021D78AA
_021D7884:
	ldr r1, [r0, #8]
	ldr r0, _021D78B4 ; =0x0000142C
	str r1, [r5, r0]
	bl MOD73_021D9088
	ldr r3, _021D78B4 ; =0x0000142C
	add r2, r0, #0
	add r1, r5, r3
	sub r3, #8
	ldr r3, [r5, r3]
	mov r0, #0x19
	bl MOD73_021D90D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	pop {r3, r4, r5, pc}
_021D78AA:
	ldr r0, [r5, #0xc]
	pop {r3, r4, r5, pc}
	nop
_021D78B0: .word 0x00001420
_021D78B4: .word 0x0000142C
	thumb_func_end MOD73_021D785C

	thumb_func_start MOD73_021D78B8
MOD73_021D78B8: ; 0x021D78B8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r2, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r0, #5
	bhi _021D79C4
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D78D0: ; jump table
	.short _021D78DC - _021D78D0 - 2 ; case 0
	.short _021D78F0 - _021D78D0 - 2 ; case 1
	.short _021D7902 - _021D78D0 - 2 ; case 2
	.short _021D7924 - _021D78D0 - 2 ; case 3
	.short _021D7940 - _021D78D0 - 2 ; case 4
	.short _021D7966 - _021D78D0 - 2 ; case 5
_021D78DC:
	ldr r0, _021D79C8 ; =0x00001418
	ldr r1, [r4]
	ldr r2, [r4, #0x20]
	add r0, r4, r0
	bl MOD73_021DB26C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D79C4
_021D78F0:
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD73_021D97F0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D79C4
_021D7902:
	mov r0, #0xd7
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD73_021D98B8
	cmp r0, #1
	bne _021D79C4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, _021D79CC ; =0x0000054C
	add r0, r4, r0
	bl MOD73_021D9AB4
	mov r0, #0x18
	str r0, [r4, #0x1c]
	b _021D79C4
_021D7924:
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	ble _021D7930
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	b _021D79C4
_021D7930:
	ldr r0, _021D79D0 ; =0x00000598
	add r0, r4, r0
	bl MOD73_021D9E3C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D79C4
_021D7940:
	ldr r0, _021D79D0 ; =0x00000598
	add r0, r4, r0
	bl MOD73_021D9E6C
	cmp r0, #0
	beq _021D79C4
	ldr r0, _021D79CC ; =0x0000054C
	add r0, r4, r0
	bl MOD73_021D9AF0
	mov r0, #0x16
	lsl r0, r0, #6
	add r0, r4, r0
	bl MOD73_021D9E24
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D79C4
_021D7966:
	mov r0, #0x16
	lsl r0, r0, #6
	add r0, r4, r0
	bl MOD73_021D9E6C
	add r6, r0, #0
	ldr r0, _021D79D4 ; =0x00000588
	ldr r0, [r4, r0]
	bl FUN_0202022C
	add r7, r0, #0
	add r0, r7, #1
	mov r1, #3
	bl _s32_div_f
	add r5, r0, #0
	mov r0, #0xd6
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, r5
	beq _021D79A8
	cmp r7, #0xa
	bge _021D799C
	ldr r0, _021D79D8 ; =0x000006BD
	bl FUN_020054C8
	b _021D79A2
_021D799C:
	ldr r0, _021D79DC ; =0x000006BE
	bl FUN_020054C8
_021D79A2:
	mov r0, #0xd6
	lsl r0, r0, #2
	str r5, [r4, r0]
_021D79A8:
	cmp r6, #0
	beq _021D79C4
	ldr r0, _021D79E0 ; =0x0000061C
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DA1D8
	ldr r0, _021D79E4 ; =0x000005A4
	add r0, r4, r0
	bl MOD73_021DA03C
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D79C4:
	ldr r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D79C8: .word 0x00001418
_021D79CC: .word 0x0000054C
_021D79D0: .word 0x00000598
_021D79D4: .word 0x00000588
_021D79D8: .word 0x000006BD
_021D79DC: .word 0x000006BE
_021D79E0: .word 0x0000061C
_021D79E4: .word 0x000005A4
	thumb_func_end MOD73_021D78B8

	thumb_func_start MOD73_021D79E8
MOD73_021D79E8: ; 0x021D79E8
	push {r4, lr}
	mov r0, #0x2d
	add r4, r1, #0
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD73_021DB318
	ldr r0, _021D7A98 ; =0x00001430
	mov r1, #0x2d
	lsl r1, r1, #4
	add r0, r4, r0
	add r1, r4, r1
	bl MOD73_021DB368
	ldr r0, _021D7A9C ; =0x00001424
	ldr r0, [r4, r0]
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D7A5C
	ldr r2, _021D7AA0 ; =0x0000142C
	mov r0, #0xba
	add r1, r4, r2
	sub r2, #0xc
	lsl r0, r0, #2
	ldr r2, [r4, r2]
	add r0, r4, r0
	bl MOD73_021DB8AC
	cmp r0, #1
	bne _021D7A40
	ldr r3, _021D7A9C ; =0x00001424
	mov r1, #0
	ldr r3, [r4, r3]
	mov r0, #0x17
	add r2, r1, #0
	bl MOD73_021D90D0
	cmp r0, #0
	bne _021D7A3C
	bl ErrorHandling
_021D7A3C:
	ldr r0, [r4, #0xc]
	pop {r4, pc}
_021D7A40:
	mov r0, #0xba
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD73_021DB9F0
	ldr r2, _021D7AA0 ; =0x0000142C
	mov r0, #0xba
	add r1, r4, r2
	sub r2, #0xc
	lsl r0, r0, #2
	ldr r2, [r4, r2]
	add r0, r4, r0
	bl MOD73_021DB924
_021D7A5C:
	bl MOD73_021D908C
	ldr r3, _021D7A98 ; =0x00001430
	add r2, r0, #0
	add r1, r4, r3
	sub r3, #0xc
	ldr r3, [r4, r3]
	mov r0, #0x1a
	bl MOD73_021D90D0
	add r0, r4, #0
	bl MOD73_021D810C
	mov r0, #0x67
	ldr r1, _021D7AA0 ; =0x0000142C
	lsl r0, r0, #4
	add r0, r4, r0
	add r1, r4, r1
	bl MOD73_021DA884
	ldr r0, _021D7AA4 ; =0x00000A84
	add r0, r4, r0
	bl MOD73_021DAE54
	ldr r0, _021D7AA8 ; =0x00000B04
	add r0, r4, r0
	bl MOD73_021DB008
	ldr r0, [r4, #0xc]
	pop {r4, pc}
	.align 2, 0
_021D7A98: .word 0x00001430
_021D7A9C: .word 0x00001424
_021D7AA0: .word 0x0000142C
_021D7AA4: .word 0x00000A84
_021D7AA8: .word 0x00000B04
	thumb_func_end MOD73_021D79E8

	thumb_func_start MOD73_021D7AAC
MOD73_021D7AAC: ; 0x021D7AAC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r4, r1, #0
	mov r0, #0x67
	ldr r1, _021D7C68 ; =0x0000142C
	lsl r0, r0, #4
	add r5, r2, #0
	add r0, r4, r0
	add r1, r4, r1
	bl MOD73_021DA884
	ldr r0, [r5]
	cmp r0, #4
	bls _021D7ACC
	b _021D7C5C
_021D7ACC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7AD8: ; jump table
	.short _021D7AE2 - _021D7AD8 - 2 ; case 0
	.short _021D7B6C - _021D7AD8 - 2 ; case 1
	.short _021D7B98 - _021D7AD8 - 2 ; case 2
	.short _021D7BA8 - _021D7AD8 - 2 ; case 3
	.short _021D7C1A - _021D7AD8 - 2 ; case 4
_021D7AE2:
	ldr r0, _021D7C6C ; =0x0000063C
	add r0, r4, r0
	bl MOD73_021DA4AC
	ldr r0, _021D7C70 ; =0x00000A84
	mov r1, #0
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D7C70 ; =0x00000A84
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D7C70 ; =0x00000A84
	mov r1, #2
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D7C70 ; =0x00000A84
	mov r1, #3
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D7C74 ; =0x0000058C
	add r0, r4, r0
	bl MOD73_021D9E24
	ldr r0, _021D7C78 ; =0x000006BA
	mov r1, #0
	bl FUN_020054F0
	ldr r0, _021D7C7C ; =0x000006BB
	mov r1, #0
	bl FUN_020054F0
	ldr r0, _021D7C80 ; =0x000006BF
	mov r1, #0
	bl FUN_020054F0
	ldr r0, _021D7C84 ; =0x000006C1
	mov r1, #0
	bl FUN_020054F0
	ldr r0, _021D7C88 ; =0x000006C2
	bl FUN_020054C8
	ldr r0, _021D7C8C ; =0x000005A4
	mov r1, #0
	add r0, r4, r0
	add r2, r1, #0
	bl MOD73_021D9FC0
	ldr r0, _021D7C8C ; =0x000005A4
	mov r1, #1
	add r0, r4, r0
	mov r2, #0
	bl MOD73_021D9FC0
	ldr r0, _021D7C8C ; =0x000005A4
	mov r1, #2
	add r0, r4, r0
	mov r2, #0
	bl MOD73_021D9FC0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7C60
_021D7B6C:
	ldr r0, _021D7C74 ; =0x0000058C
	add r0, r4, r0
	bl MOD73_021D9E6C
	cmp r0, #0
	beq _021D7C60
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r1, #0
	str r0, [sp, #8]
	mov r0, #3
	add r3, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7C60
_021D7B98:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7C60
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7C60
_021D7BA8:
	ldr r0, [r6, #0x10]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	ldr r1, _021D7C90 ; =0x00001428
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _021D7BC0
	mov r1, #0xc
	bl FUN_0202A170
	b _021D7BC6
_021D7BC0:
	mov r1, #0x12
	bl FUN_0202A170
_021D7BC6:
	ldr r0, _021D7C94 ; =0x00001424
	ldr r0, [r4, r0]
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D7C12
	ldr r0, [r4]
	bl FUN_02027E5C
	add r6, r0, #0
	ldr r0, [r4]
	ldr r3, _021D7C68 ; =0x0000142C
	str r0, [sp]
	mov r0, #0xba
	add r2, r4, r3
	sub r3, #0xc
	lsl r0, r0, #2
	ldr r3, [r4, r3]
	add r0, r4, r0
	add r1, r6, #0
	bl MOD73_021DBA24
	bl FUN_02027E30
	ldr r3, _021D7C94 ; =0x00001424
	add r2, r0, #0
	ldr r3, [r4, r3]
	mov r0, #0x1c
	add r1, r6, #0
	bl MOD73_021D90D0
	cmp r0, #0
	bne _021D7C0C
	bl ErrorHandling
_021D7C0C:
	add r0, r6, #0
	bl FreeToHeap
_021D7C12:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7C60
_021D7C1A:
	ldr r0, _021D7C94 ; =0x00001424
	ldr r0, [r4, r0]
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D7C54
	ldr r2, _021D7C68 ; =0x0000142C
	mov r0, #0xba
	add r1, r4, r2
	sub r2, #0xc
	lsl r0, r0, #2
	ldr r2, [r4, r2]
	add r0, r4, r0
	bl MOD73_021DBBFC
	bl MOD73_021D9090
	ldr r3, _021D7C98 ; =0x0000144C
	add r2, r0, #0
	add r1, r4, r3
	sub r3, #0x28
	ldr r3, [r4, r3]
	mov r0, #0x1b
	bl MOD73_021D90D0
	cmp r0, #0
	bne _021D7C54
	bl ErrorHandling
_021D7C54:
	ldr r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7C5C:
	bl ErrorHandling
_021D7C60:
	ldr r0, [r4, #0xc]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D7C68: .word 0x0000142C
_021D7C6C: .word 0x0000063C
_021D7C70: .word 0x00000A84
_021D7C74: .word 0x0000058C
_021D7C78: .word 0x000006BA
_021D7C7C: .word 0x000006BB
_021D7C80: .word 0x000006BF
_021D7C84: .word 0x000006C1
_021D7C88: .word 0x000006C2
_021D7C8C: .word 0x000005A4
_021D7C90: .word 0x00001428
_021D7C94: .word 0x00001424
_021D7C98: .word 0x0000144C
	thumb_func_end MOD73_021D7AAC

	thumb_func_start MOD73_021D7C9C
MOD73_021D7C9C: ; 0x021D7C9C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r2, #0
	add r6, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r0, #0xb
	bls _021D7CAE
	b _021D7F3A
_021D7CAE:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7CBA: ; jump table
	.short _021D7CD2 - _021D7CBA - 2 ; case 0
	.short _021D7D2E - _021D7CBA - 2 ; case 1
	.short _021D7D42 - _021D7CBA - 2 ; case 2
	.short _021D7D66 - _021D7CBA - 2 ; case 3
	.short _021D7D94 - _021D7CBA - 2 ; case 4
	.short _021D7DC0 - _021D7CBA - 2 ; case 5
	.short _021D7DF4 - _021D7CBA - 2 ; case 6
	.short _021D7E1C - _021D7CBA - 2 ; case 7
	.short _021D7E36 - _021D7CBA - 2 ; case 8
	.short _021D7EA8 - _021D7CBA - 2 ; case 9
	.short _021D7ED6 - _021D7CBA - 2 ; case 10
	.short _021D7F0C - _021D7CBA - 2 ; case 11
_021D7CD2:
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #0
	add r0, r4, r0
	bl MOD73_021DA730
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0xae
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [r4]
	ldr r3, _021D7F48 ; =0x00001410
	str r0, [sp]
	add r0, r4, r3
	add r3, #0x80
	ldrb r3, [r4, r3]
	mov r1, #0x80
	mov r2, #0x90
	bl MOD73_021DB20C
	mov r0, #6
	mov r2, #0
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r0, [r4]
	add r3, r2, #0
	str r0, [sp, #8]
	mov r0, #3
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7F3E
_021D7D2E:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D7E12
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x1e
	str r0, [r4, #0x1c]
	b _021D7F3E
_021D7D42:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	bpl _021D7E12
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DA730
	ldr r0, _021D7F4C ; =0x000006C3
	bl FUN_020054C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x1e
	str r0, [r4, #0x1c]
	b _021D7F3E
_021D7D66:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	bpl _021D7E12
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #2
	add r0, r4, r0
	bl MOD73_021DA730
	ldr r0, _021D7F48 ; =0x00001410
	add r0, r4, r0
	bl MOD73_021DB260
	ldr r0, _021D7F4C ; =0x000006C3
	bl FUN_020054C8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x96
	lsl r0, r0, #2
	str r0, [r4, #0x1c]
	b _021D7F3E
_021D7D94:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	bmi _021D7DAE
	ldr r0, _021D7F50 ; =0x021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _021D7DAE
	ldr r0, _021D7F54 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D7DB6
_021D7DAE:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7F3E
_021D7DB6:
	ldr r0, _021D7F48 ; =0x00001410
	add r0, r4, r0
	bl MOD73_021DB260
	b _021D7F3E
_021D7DC0:
	ldr r0, _021D7F48 ; =0x00001410
	add r0, r4, r0
	bl MOD73_021DB24C
	ldr r0, _021D7F44 ; =0x0000063C
	add r0, r4, r0
	bl MOD73_021DA754
	ldr r1, _021D7F58 ; =0x0000152C
	ldr r2, _021D7F5C ; =0x00001420
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r0, r6, #0
	bl MOD73_021D8590
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #0
	add r0, r4, r0
	bl MOD73_021DA770
	mov r0, #0x96
	str r0, [r4, #0x1c]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7F3E
_021D7DF4:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	ldr r0, _021D7F50 ; =0x021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _021D7E14
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	blt _021D7E14
	ldr r0, _021D7F54 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _021D7E14
_021D7E12:
	b _021D7F3E
_021D7E14:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7F3E
_021D7E1C:
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DA770
	ldr r0, _021D7F60 ; =0x00001418
	add r0, r4, r0
	bl MOD73_021DB28C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D7F3E
_021D7E36:
	ldr r0, _021D7F60 ; =0x00001418
	add r0, r4, r0
	bl MOD73_021DB2B8
	sub r1, r0, #1
	cmp r1, #1
	bhi _021D7F3E
	cmp r0, #1
	bne _021D7E90
	ldr r0, [r6, #0x10]
	ldr r0, [r0, #8]
	bl FUN_020281B8
	cmp r0, #0x64
	blo _021D7E68
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #2
	add r0, r4, r0
	bl MOD73_021DA770
	mov r0, #0xa
	str r0, [r5]
	mov r0, #0x96
	str r0, [r4, #0x1c]
	b _021D7F3E
_021D7E68:
	ldr r0, [r6, #0x10]
	mov r1, #4
	ldr r0, [r0, #0x14]
	bl FUN_0206EE64
	cmp r0, #0
	bne _021D7E8A
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #5
	add r0, r4, r0
	bl MOD73_021DA770
	mov r0, #0xa
	str r0, [r5]
	mov r0, #0x96
	str r0, [r4, #0x1c]
	b _021D7F3E
_021D7E8A:
	mov r0, #9
	str r0, [r5]
	b _021D7E94
_021D7E90:
	mov r0, #0xb
	str r0, [r5]
_021D7E94:
	ldr r0, _021D7F5C ; =0x00001420
	ldr r0, [r4, r0]
	cmp r0, #1
	ble _021D7F3E
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #6
	add r0, r4, r0
	bl MOD73_021DA770
	b _021D7F3E
_021D7EA8:
	mov r0, #0x35
	mov r1, #1
	lsl r0, r0, #4
	str r1, [r4, r0]
	bl MOD73_021D9080
	ldr r3, _021D7F64 ; =0x00001424
	mov r1, #0x35
	lsl r1, r1, #4
	add r2, r0, #0
	ldr r3, [r4, r3]
	mov r0, #0x1e
	add r1, r4, r1
	bl MOD73_021D90D0
	cmp r0, #0
	bne _021D7ECE
	bl ErrorHandling
_021D7ECE:
	ldr r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7ED6:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	ldr r0, _021D7F50 ; =0x021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _021D7EF4
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	blt _021D7EF4
	ldr r0, _021D7F54 ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _021D7F3E
_021D7EF4:
	ldr r0, _021D7F5C ; =0x00001420
	ldr r0, [r4, r0]
	cmp r0, #1
	ble _021D7F06
	ldr r0, _021D7F44 ; =0x0000063C
	mov r1, #6
	add r0, r4, r0
	bl MOD73_021DA770
_021D7F06:
	mov r0, #0xb
	str r0, [r5]
	b _021D7F3E
_021D7F0C:
	mov r0, #0x35
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	bl MOD73_021D9080
	ldr r3, _021D7F64 ; =0x00001424
	mov r1, #0x35
	lsl r1, r1, #4
	add r2, r0, #0
	ldr r3, [r4, r3]
	mov r0, #0x1e
	add r1, r4, r1
	bl MOD73_021D90D0
	cmp r0, #0
	bne _021D7F32
	bl ErrorHandling
_021D7F32:
	ldr r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	pop {r3, r4, r5, r6, pc}
_021D7F3A:
	bl ErrorHandling
_021D7F3E:
	ldr r0, [r4, #0xc]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D7F44: .word 0x0000063C
_021D7F48: .word 0x00001410
_021D7F4C: .word 0x000006C3
_021D7F50: .word 0x021C48F8
_021D7F54: .word gUnknown21C48B8
_021D7F58: .word 0x0000152C
_021D7F5C: .word 0x00001420
_021D7F60: .word 0x00001418
_021D7F64: .word 0x00001424
	thumb_func_end MOD73_021D7C9C

	thumb_func_start MOD73_021D7F68
MOD73_021D7F68: ; 0x021D7F68
	ldr r3, _021D7F70 ; =MOD73_021D8810
	add r0, r1, #0
	add r1, r2, #0
	bx r3
	.align 2, 0
_021D7F70: .word MOD73_021D8810
	thumb_func_end MOD73_021D7F68

	thumb_func_start MOD73_021D7F74
MOD73_021D7F74: ; 0x021D7F74
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r2, #0
	add r6, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r0, #4
	bhi _021D8056
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7F90: ; jump table
	.short _021D7F9A - _021D7F90 - 2 ; case 0
	.short _021D8000 - _021D7F90 - 2 ; case 1
	.short _021D8010 - _021D7F90 - 2 ; case 2
	.short _021D8030 - _021D7F90 - 2 ; case 3
	.short _021D8040 - _021D7F90 - 2 ; case 4
_021D7F9A:
	ldr r0, _021D805C ; =0x00001571
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _021D7FB2
	ldr r0, _021D8060 ; =0x0000063C
	mov r1, #3
	add r0, r4, r0
	bl MOD73_021DA770
	mov r0, #1
	str r0, [r6, #0x20]
	b _021D7FF4
_021D7FB2:
	mov r0, #0
	str r0, [r6, #0x20]
	mov r0, #0x35
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D7FCC
	ldr r0, _021D8060 ; =0x0000063C
	mov r1, #4
	add r0, r4, r0
	bl MOD73_021DA770
	b _021D7FDA
_021D7FCC:
	ldr r0, _021D8064 ; =0x00001420
	ldr r0, [r4, r0]
	cmp r0, #1
	bgt _021D7FDA
	mov r0, #2
	str r0, [r5]
	b _021D8056
_021D7FDA:
	ldr r0, _021D8068 ; =0x00001428
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D7FF4
	ldr r0, [r4]
	bl FUN_02029520
	add r1, r0, #0
	ldr r0, [r6, #0x10]
	mov r2, #4
	ldr r0, [r0, #0x1c]
	bl FUN_02028AD4
_021D7FF4:
	mov r0, #0x3c
	str r0, [r4, #0x1c]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8056
_021D8000:
	ldr r0, [r4, #0x1c]
	sub r0, r0, #1
	str r0, [r4, #0x1c]
	bpl _021D8056
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8056
_021D8010:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8056
_021D8030:
	bl FUN_0200E308
	cmp r0, #0
	beq _021D8056
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021D8056
_021D8040:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD73_021D8840
	add r0, r4, #0
	bl MOD73_021D875C
	ldr r0, [r4, #0xc]
	add sp, #0xc
	add r0, r0, #1
	pop {r3, r4, r5, r6, pc}
_021D8056:
	ldr r0, [r4, #0xc]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D805C: .word 0x00001571
_021D8060: .word 0x0000063C
_021D8064: .word 0x00001420
_021D8068: .word 0x00001428
	thumb_func_end MOD73_021D7F74

	thumb_func_start MOD73_021D806C
MOD73_021D806C: ; 0x021D806C
	push {r4, lr}
	mov r0, #0xd7
	add r4, r1, #0
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD73_021D96C8
	ldr r0, _021D80E8 ; =0x0000054C
	add r0, r4, r0
	bl MOD73_021D9A4C
	mov r0, #0x16
	lsl r0, r0, #6
	add r0, r4, r0
	bl MOD73_021D9DA0
	ldr r0, _021D80EC ; =0x0000058C
	add r0, r4, r0
	bl MOD73_021D9DA0
	ldr r0, _021D80F0 ; =0x00000598
	add r0, r4, r0
	bl MOD73_021D9DA0
	ldr r0, _021D80F4 ; =0x000005A4
	add r0, r4, r0
	bl MOD73_021D9E8C
	ldr r0, _021D80F8 ; =0x0000061C
	add r0, r4, r0
	bl MOD73_021DA0FC
	ldr r0, _021D80FC ; =0x0000063C
	add r0, r4, r0
	bl MOD73_021DA234
	mov r0, #0x67
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD73_021DA82C
	ldr r0, _021D8100 ; =0x00000A84
	add r0, r4, r0
	bl MOD73_021DAD84
	ldr r0, _021D8104 ; =0x00000B04
	add r0, r4, r0
	bl MOD73_021DAF88
	ldr r0, _021D8108 ; =0x00001418
	add r0, r4, r0
	bl MOD73_021DB280
	add r0, r4, #0
	bl MOD73_021D856C
	add r0, r4, #0
	bl MOD73_021D7694
	ldr r0, [r4, #0xc]
	pop {r4, pc}
	nop
_021D80E8: .word 0x0000054C
_021D80EC: .word 0x0000058C
_021D80F0: .word 0x00000598
_021D80F4: .word 0x000005A4
_021D80F8: .word 0x0000061C
_021D80FC: .word 0x0000063C
_021D8100: .word 0x00000A84
_021D8104: .word 0x00000B04
_021D8108: .word 0x00001418
	thumb_func_end MOD73_021D806C

	thumb_func_start MOD73_021D810C
MOD73_021D810C: ; 0x021D810C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8170 ; =0x000014C4
	add r4, r5, r0
	ldr r0, _021D8174 ; =0x000005A4
	ldrh r1, [r4, #8]
	add r0, r5, r0
	bl MOD73_021D9FE0
	add r0, r5, #0
	bl MOD73_021D85E4
	ldrh r0, [r4, #0xa]
	ldrb r1, [r4, #0xd]
	bl MOD73_021DB644
	add r1, r0, #0
	ldr r0, _021D8174 ; =0x000005A4
	add r0, r5, r0
	bl MOD73_021D9FFC
	ldr r0, _021D8174 ; =0x000005A4
	ldrb r1, [r4, #0xd]
	add r0, r5, r0
	bl MOD73_021DA058
	ldr r0, _021D8178 ; =0x0000061C
	add r0, r5, r0
	bl MOD73_021DA194
	add r0, r5, #0
	bl MOD73_021D817C
	add r0, r5, #0
	bl MOD73_021D8458
	add r0, r5, #0
	bl MOD73_021D8254
	add r0, r5, #0
	bl MOD73_021D82FC
	add r0, r5, #0
	bl MOD73_021D83D0
	add r0, r5, #0
	bl MOD73_021D84FC
	pop {r3, r4, r5, pc}
	nop
_021D8170: .word 0x000014C4
_021D8174: .word 0x000005A4
_021D8178: .word 0x0000061C
	thumb_func_end MOD73_021D810C

	thumb_func_start MOD73_021D817C
MOD73_021D817C: ; 0x021D817C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021D8230 ; =0x000014C4
	mov r2, #7
	add r4, r5, r0
	ldrb r3, [r4, #0xd]
	ldr r0, _021D8234 ; =0x000005A4
	mov r1, #5
	add r6, r3, #0
	mul r6, r2
	ldr r2, _021D8238 ; =0x021DBC84
	add r0, r5, r0
	ldrb r2, [r2, r6]
	bl MOD73_021D9FC0
	ldrb r3, [r4, #0xd]
	ldr r0, _021D8234 ; =0x000005A4
	mov r2, #7
	add r6, r3, #0
	mul r6, r2
	ldr r2, _021D823C ; =0x021DBC85
	add r0, r5, r0
	ldrb r2, [r2, r6]
	mov r1, #6
	bl MOD73_021D9FC0
	ldrb r2, [r4, #0xd]
	ldr r0, _021D8234 ; =0x000005A4
	mov r1, #7
	add r3, r2, #0
	ldr r2, _021D8240 ; =0x021DBC86
	mul r3, r1
	ldrb r2, [r2, r3]
	add r0, r5, r0
	bl MOD73_021D9FC0
	ldrb r3, [r4, #0xd]
	ldr r0, _021D8234 ; =0x000005A4
	mov r2, #7
	add r6, r3, #0
	mul r6, r2
	ldr r2, _021D8244 ; =0x021DBC87
	add r0, r5, r0
	ldrb r2, [r2, r6]
	mov r1, #0
	bl MOD73_021D9FC0
	ldrb r3, [r4, #0xd]
	ldr r0, _021D8234 ; =0x000005A4
	mov r2, #7
	add r6, r3, #0
	mul r6, r2
	ldr r2, _021D8248 ; =0x021DBC88
	add r0, r5, r0
	ldrb r2, [r2, r6]
	mov r1, #1
	bl MOD73_021D9FC0
	ldrb r3, [r4, #0xd]
	ldr r0, _021D8234 ; =0x000005A4
	mov r2, #7
	add r6, r3, #0
	mul r6, r2
	ldr r2, _021D824C ; =0x021DBC89
	add r0, r5, r0
	ldrb r2, [r2, r6]
	mov r1, #2
	bl MOD73_021D9FC0
	ldrb r1, [r4, #0xd]
	mov r0, #7
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021D8250 ; =0x021DBC8A
	ldrb r1, [r0, r2]
	cmp r1, #8
	beq _021D822E
	ldrb r2, [r4, #0x10]
	ldr r0, _021D8234 ; =0x000005A4
	cmp r2, #0
	beq _021D8226
	add r0, r5, r0
	bl MOD73_021DA01C
	pop {r4, r5, r6, pc}
_021D8226:
	add r0, r5, r0
	mov r2, #0
	bl MOD73_021D9FC0
_021D822E:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021D8230: .word 0x000014C4
_021D8234: .word 0x000005A4
_021D8238: .word MOD73_021DBC84
_021D823C: .word MOD73_021DBC85
_021D8240: .word MOD73_021DBC86
_021D8244: .word MOD73_021DBC87
_021D8248: .word MOD73_021DBC88
_021D824C: .word MOD73_021DBC89
_021D8250: .word MOD73_021DBC8A
	thumb_func_end MOD73_021D817C

	thumb_func_start MOD73_021D8254
MOD73_021D8254: ; 0x021D8254
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D82F0 ; =0x000014C4
	add r1, r4, r0
	ldrb r2, [r1, #0x11]
	ldrb r0, [r1, #0xc]
	cmp r2, r0
	beq _021D8274
	ldrh r0, [r1, #0xa]
	cmp r0, #0
	beq _021D8274
	mov r0, #0xb
	lsl r0, r0, #6
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D8292
_021D8274:
	ldr r0, _021D82F4 ; =0x00000A84
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D82F4 ; =0x00000A84
	mov r1, #3
	add r0, r4, r0
	bl MOD73_021DAEAC
	mov r0, #0xb1
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	pop {r4, pc}
_021D8292:
	cmp r2, #0
	bne _021D82C2
	add r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #1
	beq _021D82EC
	ldr r0, _021D82F4 ; =0x00000A84
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DAE7C
	mov r0, #0xb1
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _021D82F4 ; =0x00000A84
	mov r1, #3
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D82F8 ; =0x000006C1
	bl FUN_020054C8
	pop {r4, pc}
_021D82C2:
	add r0, r0, #4
	ldr r0, [r4, r0]
	cmp r0, #2
	beq _021D82EC
	ldr r0, _021D82F4 ; =0x00000A84
	mov r1, #3
	add r0, r4, r0
	bl MOD73_021DAE7C
	mov r0, #0xb1
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _021D82F4 ; =0x00000A84
	mov r1, #1
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D82F8 ; =0x000006C1
	bl FUN_020054C8
_021D82EC:
	pop {r4, pc}
	nop
_021D82F0: .word 0x000014C4
_021D82F4: .word 0x00000A84
_021D82F8: .word 0x000006C1
	thumb_func_end MOD73_021D8254

	thumb_func_start MOD73_021D82FC
MOD73_021D82FC: ; 0x021D82FC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D83C0 ; =0x000014C4
	mov r1, #0xb1
	lsl r1, r1, #2
	add r4, r5, r0
	ldr r0, [r5, r1]
	cmp r0, #0
	bne _021D8316
	sub r0, r1, #4
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D832C
_021D8316:
	ldr r0, _021D83C4 ; =0x0000063C
	add r0, r5, r0
	bl MOD73_021DA4AC
	mov r0, #0xb3
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	sub r0, r0, #4
	str r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021D832C:
	add r1, #8
	ldr r0, [r5, r1]
	cmp r0, #0
	bne _021D8360
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _021D8374
	ldr r0, _021D83C4 ; =0x0000063C
	add r0, r5, r0
	bl MOD73_021DA4AC
	ldr r0, _021D83C4 ; =0x0000063C
	ldrb r2, [r4, #0xd]
	ldr r1, _021D83C8 ; =0x021DBC58
	add r0, r5, r0
	ldrb r1, [r1, r2]
	bl MOD73_021DA434
	mov r0, #0xb3
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0
	sub r0, r0, #4
	str r1, [r5, r0]
	b _021D8374
_021D8360:
	ldr r0, _021D83C4 ; =0x0000063C
	add r0, r5, r0
	bl MOD73_021DA49C
	cmp r0, #0
	beq _021D8374
	mov r0, #0xb3
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_021D8374:
	mov r0, #0xb2
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _021D83AA
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _021D83BE
	ldr r0, _021D83C4 ; =0x0000063C
	add r0, r5, r0
	bl MOD73_021DA4AC
	ldr r0, _021D83C4 ; =0x0000063C
	ldrb r2, [r4, #0xd]
	ldr r1, _021D83CC ; =0x021DBC5C
	add r0, r5, r0
	ldrb r1, [r1, r2]
	bl MOD73_021DA434
	mov r0, #0xb2
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r5, r0]
	mov r1, #0
	add r0, r0, #4
	str r1, [r5, r0]
	pop {r3, r4, r5, pc}
_021D83AA:
	ldr r0, _021D83C4 ; =0x0000063C
	add r0, r5, r0
	bl MOD73_021DA49C
	cmp r0, #0
	beq _021D83BE
	mov r0, #0xb2
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_021D83BE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D83C0: .word 0x000014C4
_021D83C4: .word 0x0000063C
_021D83C8: .word MOD73_021DBC58
_021D83CC: .word MOD73_021DBC5C
	thumb_func_end MOD73_021D82FC

	thumb_func_start MOD73_021D83D0
MOD73_021D83D0: ; 0x021D83D0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D844C ; =0x000014C4
	add r4, r5, r0
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _021D83FC
	mov r0, #0x67
	lsl r0, r0, #4
	ldrb r1, [r4, #0xd]
	add r0, r5, r0
	mov r2, #2
	bl MOD73_021DA8BC
	ldrb r0, [r4, #0xd]
	lsl r1, r0, #2
	ldr r0, _021D8450 ; =0x021DBC60
	ldr r0, [r0, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020054C8
_021D83FC:
	ldrb r0, [r4, #0x12]
	cmp r0, #1
	bne _021D8422
	mov r0, #0x67
	lsl r0, r0, #4
	ldrb r1, [r4, #0xd]
	add r0, r5, r0
	mov r2, #1
	bl MOD73_021DA8BC
	ldrb r0, [r4, #0xd]
	lsl r1, r0, #2
	ldr r0, _021D8454 ; =0x021DBC6C
	ldr r0, [r0, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020054C8
	b _021D8434
_021D8422:
	cmp r0, #2
	bne _021D8434
	mov r0, #0x67
	lsl r0, r0, #4
	ldrb r1, [r4, #0xd]
	add r0, r5, r0
	mov r2, #0
	bl MOD73_021DA8BC
_021D8434:
	ldrh r0, [r4, #0xa]
	ldrb r1, [r4, #0xd]
	bl MOD73_021DB62C
	cmp r0, #0
	bne _021D844A
	mov r0, #0x67
	lsl r0, r0, #4
	add r0, r5, r0
	bl MOD73_021DAAA8
_021D844A:
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D844C: .word 0x000014C4
_021D8450: .word MOD73_021DBC60
_021D8454: .word MOD73_021DBC6C
	thumb_func_end MOD73_021D83D0

	thumb_func_start MOD73_021D8458
MOD73_021D8458: ; 0x021D8458
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D84F0 ; =0x000014C4
	add r1, r4, r0
	ldrb r0, [r1, #0xe]
	cmp r0, #0
	beq _021D84B0
	ldrb r0, [r1, #0x11]
	cmp r0, #0
	ldr r0, _021D84F4 ; =0x00000A84
	bne _021D8490
	add r0, r4, r0
	mov r1, #0
	bl MOD73_021DAE7C
	ldr r0, _021D84F4 ; =0x00000A84
	mov r1, #2
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D84F8 ; =0x000006C1
	bl FUN_020054C8
	mov r0, #0xb
	mov r1, #1
	lsl r0, r0, #6
	str r1, [r4, r0]
	b _021D84B0
_021D8490:
	add r0, r4, r0
	mov r1, #2
	bl MOD73_021DAE7C
	ldr r0, _021D84F4 ; =0x00000A84
	mov r1, #0
	add r0, r4, r0
	bl MOD73_021DAEAC
	ldr r0, _021D84F8 ; =0x000006C1
	bl FUN_020054C8
	mov r0, #0xb
	mov r1, #2
	lsl r0, r0, #6
	str r1, [r4, r0]
_021D84B0:
	mov r0, #0xb
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D84D2
	ldr r0, _021D84F4 ; =0x00000A84
	mov r1, #0
	add r0, r4, r0
	bl MOD73_021DAECC
	cmp r0, #1
	bne _021D84EC
	mov r0, #0xb
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
	pop {r4, pc}
_021D84D2:
	cmp r0, #2
	bne _021D84EC
	ldr r0, _021D84F4 ; =0x00000A84
	mov r1, #2
	add r0, r4, r0
	bl MOD73_021DAECC
	cmp r0, #1
	bne _021D84EC
	mov r0, #0xb
	mov r1, #0
	lsl r0, r0, #6
	str r1, [r4, r0]
_021D84EC:
	pop {r4, pc}
	nop
_021D84F0: .word 0x000014C4
_021D84F4: .word 0x00000A84
_021D84F8: .word 0x000006C1
	thumb_func_end MOD73_021D8458

	thumb_func_start MOD73_021D84FC
MOD73_021D84FC: ; 0x021D84FC
	push {r3, lr}
	ldr r3, _021D8520 ; =0x00001430
	add r2, r3, #1
	ldrb r1, [r0, r3]
	add r3, #0xa3
	ldrb r3, [r0, r3]
	ldrb r2, [r0, r2]
	cmp r3, #1
	bne _021D851C
	ldr r3, _021D8524 ; =0x00000B04
	add r0, r0, r3
	bl MOD73_021DB020
	ldr r0, _021D8528 ; =0x000006BF
	bl FUN_020054C8
_021D851C:
	pop {r3, pc}
	nop
_021D8520: .word 0x00001430
_021D8524: .word 0x00000B04
_021D8528: .word 0x000006BF
	thumb_func_end MOD73_021D84FC

	thumb_func_start MOD73_021D852C
MOD73_021D852C: ; 0x021D852C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl FUN_02027E5C
	ldr r1, _021D8560 ; =0x0000152C
	str r0, [r4, r1]
	ldr r0, _021D8564 ; =0x00001424
	ldr r0, [r4, r0]
	bl MOD73_021D910C
	ldr r1, _021D8568 ; =0x00001570
	mov r5, #0
	strb r0, [r4, r1]
	add r0, r1, #0
	mov r3, #0x80
	mov r2, #0x60
	sub r0, #0xb4
	sub r1, #0xb3
_021D8552:
	strb r3, [r4, r0]
	strb r2, [r4, r1]
	add r5, r5, #1
	add r4, #0x1c
	cmp r5, #4
	blt _021D8552
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8560: .word 0x0000152C
_021D8564: .word 0x00001424
_021D8568: .word 0x00001570
	thumb_func_end MOD73_021D852C

	thumb_func_start MOD73_021D856C
MOD73_021D856C: ; 0x021D856C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D858C ; =0x0000152C
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D857C
	bl ErrorHandling
_021D857C:
	ldr r0, _021D858C ; =0x0000152C
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021D858C ; =0x0000152C
	mov r1, #0
	str r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021D858C: .word 0x0000152C
	thumb_func_end MOD73_021D856C

	thumb_func_start MOD73_021D8590
MOD73_021D8590: ; 0x021D8590
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0x10]
	add r7, r1, #0
	ldr r0, [r0, #0xc]
	add r6, r2, #0
	bl FUN_02022504
	mov r4, #0
	str r0, [sp]
	cmp r6, #0
	ble _021D85CA
_021D85AE:
	ldr r0, [r5, #0x10]
	add r1, r7, #0
	ldr r0, [r0, #8]
	bl FUN_02028094
	ldr r1, _021D85E0 ; =0x0000FFFF
	cmp r0, r1
	bne _021D85C4
	mov r0, #0
	str r0, [sp, #4]
	b _021D85CA
_021D85C4:
	add r4, r4, #1
	cmp r4, r6
	blt _021D85AE
_021D85CA:
	add r0, r7, #0
	mov r1, #0
	bl FUN_02027E94
	add r1, r0, #0
	ldr r0, [sp]
	bl FUN_02060FAC
	ldr r0, [sp, #4]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D85E0: .word 0x0000FFFF
	thumb_func_end MOD73_021D8590

	thumb_func_start MOD73_021D85E4
MOD73_021D85E4: ; 0x021D85E4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8628 ; =0x000014C4
	add r4, r5, r0
	ldrb r2, [r4, #0xc]
	cmp r2, #0
	bne _021D85FE
	mov r0, #0xd5
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	ldrh r0, [r4, #8]
	cmp r1, r0
	bgt _021D860E
_021D85FE:
	cmp r2, #1
	bne _021D861E
	mov r0, #0xd5
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	ldrh r0, [r4, #8]
	cmp r1, r0
	bge _021D861E
_021D860E:
	ldrb r0, [r4, #0xd]
	lsl r1, r0, #2
	ldr r0, _021D862C ; =0x021DBC78
	ldr r0, [r0, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_020054C8
_021D861E:
	ldrh r1, [r4, #8]
	mov r0, #0xd5
	lsl r0, r0, #2
	str r1, [r5, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8628: .word 0x000014C4
_021D862C: .word MOD73_021DBC78
	thumb_func_end MOD73_021D85E4

	thumb_func_start MOD73_021D8630
MOD73_021D8630: ; 0x021D8630
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	bl MOD73_021D8B4C
	add r0, r4, #0
	ldr r1, [r4]
	add r0, #0x20
	bl MOD73_021D88E4
	add r0, r4, #0
	bl MOD73_021D8A18
	add r0, r4, #0
	bl MOD73_021D89AC
	add r0, r4, #0
	bl MOD73_021D89DC
	add r0, r4, #0
	bl MOD73_021D8A84
	ldr r0, _021D8738 ; =0x0000054C
	ldr r1, [r4, #0x20]
	ldr r2, [r4]
	add r0, r4, r0
	bl MOD73_021D9A68
	ldr r0, _021D873C ; =0x0000063C
	ldr r1, [r4, #0x20]
	ldr r2, [r4]
	add r0, r4, r0
	bl MOD73_021DA254
	mov r1, #0xaf
	ldr r0, _021D8740 ; =0x000005A4
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	ldr r2, [r4]
	add r0, r4, r0
	bl MOD73_021D9EA8
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x16
	mov r2, #0x5a
	lsl r0, r0, #6
	add r1, r4, #0
	lsl r2, r2, #2
	ldr r3, [r4]
	add r0, r4, r0
	add r1, #0x2c
	add r2, r4, r2
	bl MOD73_021D9DCC
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _021D8744 ; =0x00000598
	mov r2, #0x5a
	add r1, r4, #0
	lsl r2, r2, #2
	ldr r3, [r4]
	add r0, r4, r0
	add r1, #0x2c
	add r2, r4, r2
	bl MOD73_021D9DCC
	mov r0, #5
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021D8748 ; =0x0000058C
	mov r2, #0x5a
	add r1, r4, #0
	lsl r2, r2, #2
	ldr r3, [r4]
	add r0, r4, r0
	add r1, #0x2c
	add r2, r4, r2
	bl MOD73_021D9DCC
	ldr r0, _021D874C ; =0x0000061C
	mov r2, #0x5a
	add r1, r4, #0
	lsl r2, r2, #2
	ldr r3, [r4]
	add r0, r4, r0
	add r1, #0x2c
	add r2, r4, r2
	bl MOD73_021DA118
	mov r0, #0x67
	mov r2, #0x5a
	lsl r0, r0, #4
	add r1, r4, #0
	lsl r2, r2, #2
	ldr r3, [r4]
	add r0, r4, r0
	add r1, #0x2c
	add r2, r4, r2
	bl MOD73_021DA84C
	ldr r0, _021D8750 ; =0x00000A84
	add r1, r4, #0
	ldr r2, [r4]
	add r0, r4, r0
	add r1, #0x2c
	bl MOD73_021DADA0
	ldr r0, _021D8754 ; =0x00000B04
	mov r2, #0x5a
	add r1, r4, #0
	lsl r2, r2, #2
	ldr r3, [r4]
	add r0, r4, r0
	add r1, #0x2c
	add r2, r4, r2
	bl MOD73_021DAFA8
	add r0, r4, #0
	bl MOD73_021D8BDC
	ldr r0, _021D8758 ; =0x021C4918
	mov r1, #1
	strb r1, [r0, #5]
	bl FUN_0201E7A0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021D8738: .word 0x0000054C
_021D873C: .word 0x0000063C
_021D8740: .word 0x000005A4
_021D8744: .word 0x00000598
_021D8748: .word 0x0000058C
_021D874C: .word 0x0000061C
_021D8750: .word 0x00000A84
_021D8754: .word 0x00000B04
_021D8758: .word 0x021C4918
	thumb_func_end MOD73_021D8630

	thumb_func_start MOD73_021D875C
MOD73_021D875C: ; 0x021D875C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D87EC ; =0x0000063C
	add r0, r4, r0
	bl MOD73_021DA290
	ldr r0, _021D87F0 ; =0x0000054C
	add r0, r4, r0
	bl MOD73_021D9A94
	ldr r0, _021D87F4 ; =0x000005A4
	add r0, r4, r0
	bl MOD73_021D9F74
	add r0, r4, #0
	bl MOD73_021D8B2C
	mov r0, #0x16
	lsl r0, r0, #6
	add r0, r4, r0
	bl MOD73_021D9E08
	ldr r0, _021D87F8 ; =0x0000058C
	add r0, r4, r0
	bl MOD73_021D9E08
	ldr r0, _021D87FC ; =0x00000598
	add r0, r4, r0
	bl MOD73_021D9E08
	ldr r0, _021D8800 ; =0x0000061C
	add r0, r4, r0
	bl MOD73_021DA178
	mov r0, #0x67
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD73_021DA858
	ldr r0, _021D8804 ; =0x00000A84
	add r0, r4, r0
	bl MOD73_021DAE24
	ldr r0, _021D8808 ; =0x00000B04
	add r0, r4, r0
	bl MOD73_021DAFEC
	add r0, r4, #0
	add r0, #0x20
	bl MOD73_021D8980
	add r0, r4, #0
	bl MOD73_021D89D0
	add r0, r4, #0
	bl MOD73_021D8A74
	add r0, r4, #0
	bl MOD73_021D8A08
	add r0, r4, #0
	bl MOD73_021D8BD0
	add r0, r4, #0
	bl MOD73_021D8D18
	ldr r0, _021D880C ; =0x021C4918
	mov r1, #0
	strb r1, [r0, #5]
	bl FUN_0201E7A0
	pop {r4, pc}
	.align 2, 0
_021D87EC: .word 0x0000063C
_021D87F0: .word 0x0000054C
_021D87F4: .word 0x000005A4
_021D87F8: .word 0x0000058C
_021D87FC: .word 0x00000598
_021D8800: .word 0x0000061C
_021D8804: .word 0x00000A84
_021D8808: .word 0x00000B04
_021D880C: .word 0x021C4918
	thumb_func_end MOD73_021D875C

	thumb_func_start MOD73_021D8810
MOD73_021D8810: ; 0x021D8810
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4]
	ldr r1, _021D883C ; =0x00001498
	str r0, [sp]
	mov r0, #0xd7
	mov r3, #0x5a
	lsl r0, r0, #2
	add r2, r4, #0
	lsl r3, r3, #2
	add r0, r4, r0
	add r1, r4, r1
	add r2, #0x2c
	add r3, r4, r3
	bl MOD73_021D96E4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D883C: .word 0x00001498
	thumb_func_end MOD73_021D8810

	thumb_func_start MOD73_021D8840
MOD73_021D8840: ; 0x021D8840
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xd7
	lsl r0, r0, #2
	add r1, r4, #0
	add r0, r4, r0
	add r1, #0x2c
	bl MOD73_021D97A4
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	pop {r4, pc}
	thumb_func_end MOD73_021D8840

	thumb_func_start MOD73_021D8858
MOD73_021D8858: ; 0x021D8858
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl FUN_020222AC
	mov r1, #0
	mov r0, #0x11
	add r2, r1, #0
	bl FUN_020BB1C0
	bl FUN_020BB394
	bl FUN_020B02C8
	mov r0, #0xaf
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D8882
	bl FUN_02013D5C
_021D8882:
	mov r2, #1
	mov r0, #0x12
	add r1, sp, #0
	str r2, [sp]
	bl FUN_020BB1C0
	mov r0, #0
	add r1, r0, #0
	bl FUN_020222B4
	mov r0, #0xae
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D88AA
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _021D88AA
	bl FUN_0201FDEC
_021D88AA:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D8858

	thumb_func_start MOD73_021D88B0
MOD73_021D88B0: ; 0x021D88B0
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02009F80
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _021D88C2
	bl FUN_0201AB60
_021D88C2:
	pop {r4, pc}
	thumb_func_end MOD73_021D88B0

	thumb_func_start MOD73_021D88C4
MOD73_021D88C4: ; 0x021D88C4
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D88E0 ; =0x021DBD40
	add r3, sp, #0
	mov r2, #5
_021D88CE:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D88CE
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D88E0: .word MOD73_021DBD40
	thumb_func_end MOD73_021D88C4

	thumb_func_start MOD73_021D88E4
MOD73_021D88E4: ; 0x021D88E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x88
	str r1, [sp]
	add r6, r0, #0
	bl MOD73_021D88C4
	ldr r0, [sp]
	bl FUN_02016B94
	add r3, sp, #8
	ldr r4, _021D8974 ; =0x021DBD30
	str r0, [r6]
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #0
	mov r1, #2
	bl FUN_020178BC
	ldr r4, _021D8978 ; =0x021DBD68
	add r3, sp, #0x18
	mov r2, #0xe
_021D8922:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D8922
	ldr r1, _021D897C ; =0x021DBD0C
	add r0, sp, #4
	ldrb r2, [r1]
	mov r7, #0
	add r5, sp, #4
	strb r2, [r0]
	ldrb r2, [r1, #1]
	add r4, sp, #0x18
	strb r2, [r0, #1]
	ldrb r2, [r1, #2]
	ldrb r1, [r1, #3]
	strb r2, [r0, #2]
	strb r1, [r0, #3]
_021D8944:
	ldrb r1, [r5]
	ldr r0, [r6]
	add r2, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldrb r1, [r5]
	ldr r0, [r6]
	bl FUN_02018744
	ldrb r0, [r5]
	ldr r3, [sp]
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	add r7, r7, #1
	add r4, #0x1c
	add r5, r5, #1
	cmp r7, #4
	blt _021D8944
	add sp, #0x88
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8974: .word MOD73_021DBD30
_021D8978: .word MOD73_021DBD68
_021D897C: .word MOD73_021DBD0C
	thumb_func_end MOD73_021D88E4

	thumb_func_start MOD73_021D8980
MOD73_021D8980: ; 0x021D8980
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	mov r1, #5
	bl FUN_020178A0
	ldr r0, [r4]
	mov r1, #4
	bl FUN_020178A0
	ldr r0, [r4]
	mov r1, #2
	bl FUN_020178A0
	ldr r0, [r4]
	mov r1, #1
	bl FUN_020178A0
	ldr r0, [r4]
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD73_021D8980

	thumb_func_start MOD73_021D89AC
MOD73_021D89AC: ; 0x021D89AC
	push {r3, lr}
	add r3, r0, #0
	ldr r3, [r3]
	add r0, #0x2c
	mov r1, #0x48
	mov r2, #0x10
	bl MOD73_021D92EC
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD73_021D89AC

	thumb_func_start MOD73_021D89D0
MOD73_021D89D0: ; 0x021D89D0
	ldr r3, _021D89D8 ; =MOD73_021D931C
	add r0, #0x2c
	bx r3
	nop
_021D89D8: .word MOD73_021D931C
	thumb_func_end MOD73_021D89D0

	thumb_func_start MOD73_021D89DC
MOD73_021D89DC: ; 0x021D89DC
	push {r3, r4, r5, lr}
	sub sp, #0x10
	ldr r5, _021D8A04 ; =0x021DBD10
	add r3, sp, #0
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	str r0, [sp, #0xc]
	add r0, r2, #0
	bl FUN_02013CD4
	mov r1, #0xaf
	lsl r1, r1, #2
	str r0, [r4, r1]
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8A04: .word MOD73_021DBD10
	thumb_func_end MOD73_021D89DC

	thumb_func_start MOD73_021D8A08
MOD73_021D8A08: ; 0x021D8A08
	mov r1, #0xaf
	lsl r1, r1, #2
	ldr r3, _021D8A14 ; =FUN_02013D18
	ldr r0, [r0, r1]
	bx r3
	nop
_021D8A14: .word FUN_02013D18
	thumb_func_end MOD73_021D8A08

	thumb_func_start MOD73_021D8A18
MOD73_021D8A18: ; 0x021D8A18
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x80
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	ldr r2, [r4]
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	ldr r5, _021D8A6C ; =0x021DBD20
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r4]
	ldr r1, _021D8A70 ; =0x00200010
	str r0, [sp, #0x20]
	add r0, r2, #0
	mov r2, #0x10
	bl FUN_0201D060
	ldr r1, [r4]
	mov r0, #0x20
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D8A6C: .word MOD73_021DBD20
_021D8A70: .word 0x00200010
	thumb_func_end MOD73_021D8A18

	thumb_func_start MOD73_021D8A74
MOD73_021D8A74: ; 0x021D8A74
	push {r3, lr}
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, pc}
	thumb_func_end MOD73_021D8A74

	thumb_func_start MOD73_021D8A84
MOD73_021D8A84: ; 0x021D8A84
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r0, [sp, #0x18]
	ldr r0, _021D8B28 ; =0x021DBDD8
	mov r1, #0x5a
	str r0, [sp, #0x20]
	mov r0, #0xc
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x18]
	lsl r1, r1, #2
	add r0, r0, r1
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	mov r4, #0
	str r0, [sp, #0x24]
	add r0, #0x2c
	mov r7, #0xd
	mov r5, #0xe
	str r0, [sp, #0x24]
_021D8AAA:
	cmp r4, #0
	ble _021D8AE0
	ldr r0, [sp, #0x20]
	ldrb r0, [r0]
	cmp r0, #8
	bne _021D8AE0
	str r5, [sp]
	ldr r0, [sp, #0x28]
	str r7, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x7d
	lsl r0, r0, #4
	add r0, r4, r0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x18]
	mov r2, #0x7a
	ldr r0, [r0]
	add r3, r2, #0
	str r0, [sp, #0x10]
	ldr r6, [sp, #0x18]
	add r3, #0xf2
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x1c]
	ldr r3, [r6, r3]
	bl MOD73_021D942C
	b _021D8B08
_021D8AE0:
	mov r0, #2
	str r0, [sp]
	str r5, [sp, #4]
	ldr r0, [sp, #0x28]
	str r7, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #0x7d
	lsl r0, r0, #4
	add r0, r4, r0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	ldr r3, [sp, #0x20]
	ldr r0, [r0]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x14]
	ldrb r3, [r3]
	ldr r0, [sp, #0x24]
	mov r2, #0x7a
	bl MOD73_021D9340
_021D8B08:
	ldr r0, [sp, #0x20]
	add r4, r4, #1
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x28]
	add r7, r7, #3
	add r0, r0, #3
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x1c]
	add r5, r5, #3
	add r0, #0x38
	str r0, [sp, #0x1c]
	cmp r4, #6
	blt _021D8AAA
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021D8B28: .word MOD73_021DBDD8
	thumb_func_end MOD73_021D8A84

	thumb_func_start MOD73_021D8B2C
MOD73_021D8B2C: ; 0x021D8B2C
	push {r4, r5, r6, lr}
	mov r1, #0x5a
	lsl r1, r1, #2
	add r6, r0, #0
	mov r4, #0
	add r5, r0, r1
	add r6, #0x2c
_021D8B3A:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD73_021D94F4
	add r4, r4, #1
	add r5, #0x38
	cmp r4, #6
	blt _021D8B3A
	pop {r4, r5, r6, pc}
	thumb_func_end MOD73_021D8B2C

	thumb_func_start MOD73_021D8B4C
MOD73_021D8B4C: ; 0x021D8B4C
	push {r3, r4, lr}
	sub sp, #4
	bl FUN_020BB7F4
	bl G3X_InitMtxStack
	ldr r0, _021D8BB8 ; =0x04000060
	ldr r2, _021D8BBC ; =0xFFFFCFFD
	ldrh r1, [r0]
	and r1, r2
	strh r1, [r0]
	ldrh r3, [r0]
	add r1, r2, #2
	and r3, r1
	mov r1, #0x10
	orr r1, r3
	strh r1, [r0]
	ldrh r1, [r0]
	ldr r3, _021D8BC0 ; =0x0000CFFB
	and r1, r3
	strh r1, [r0]
	add r1, r2, #2
	ldrh r4, [r0]
	sub r3, #0x1c
	lsr r2, r2, #0x11
	and r4, r1
	mov r1, #8
	orr r1, r4
	strh r1, [r0]
	ldrh r1, [r0]
	and r1, r3
	strh r1, [r0]
	mov r1, #0
	ldr r0, _021D8BC4 ; =0x000043FF
	mov r3, #0x3f
	str r1, [sp]
	bl G3X_SetClearColor
	ldr r2, _021D8BC8 ; =0x04000540
	mov r0, #2
	ldr r1, _021D8BCC ; =0xBFFF0000
	str r0, [r2]
	str r1, [r2, #0x40]
	mov r1, #1
	bl FUN_020AEB70
	mov r0, #2
	lsl r0, r0, #0xe
	mov r1, #1
	bl FUN_020AEDF4
	add sp, #4
	pop {r3, r4, pc}
	nop
_021D8BB8: .word 0x04000060
_021D8BBC: .word 0xFFFFCFFD
_021D8BC0: .word 0x0000CFFB
_021D8BC4: .word 0x000043FF
_021D8BC8: .word 0x04000540
_021D8BCC: .word 0xBFFF0000
	thumb_func_end MOD73_021D8B4C

	thumb_func_start MOD73_021D8BD0
MOD73_021D8BD0: ; 0x021D8BD0
	push {r3, lr}
	bl FUN_020AEAF4
	bl FUN_020AEC60
	pop {r3, pc}
	thumb_func_end MOD73_021D8BD0

	thumb_func_start MOD73_021D8BDC
MOD73_021D8BDC: ; 0x021D8BDC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r2, _021D8CE0 ; =0x0000019D
	ldr r3, [r5]
	mov r0, #0
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	ldr r1, _021D8CE4 ; =0x00001574
	str r0, [r5, r1]
	ldr r2, [r5]
	mov r0, #4
	mov r1, #0x40
	bl FUN_0200AA90
	ldr r1, _021D8CE8 ; =0x00001578
	str r0, [r5, r1]
	ldr r1, [r5]
	mov r0, #0x40
	bl String_ctor
	ldr r1, _021D8CEC ; =0x0000157C
	str r0, [r5, r1]
	sub r1, #8
	ldr r0, [r5, r1]
	mov r1, #0
	bl NewString_ReadMsgData
	mov r1, #0x56
	lsl r1, r1, #6
	str r0, [r5, r1]
	sub r1, #0xc
	ldr r0, [r5, r1]
	mov r1, #1
	bl NewString_ReadMsgData
	ldr r1, _021D8CF0 ; =0x00001584
	str r0, [r5, r1]
	sub r1, #0x10
	ldr r0, [r5, r1]
	mov r1, #2
	bl NewString_ReadMsgData
	ldr r1, _021D8CF4 ; =0x00001588
	str r0, [r5, r1]
	sub r1, #0x14
	ldr r0, [r5, r1]
	mov r1, #0x14
	bl NewString_ReadMsgData
	ldr r1, _021D8CF8 ; =0x0000158C
	str r0, [r5, r1]
	sub r1, #0x18
	ldr r0, [r5, r1]
	mov r1, #0x15
	bl NewString_ReadMsgData
	ldr r1, _021D8CFC ; =0x00001590
	str r0, [r5, r1]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	mov r1, #0x16
	bl NewString_ReadMsgData
	ldr r1, _021D8D00 ; =0x00001594
	str r0, [r5, r1]
	sub r1, #0x20
	ldr r0, [r5, r1]
	mov r1, #0x17
	bl NewString_ReadMsgData
	ldr r1, _021D8D04 ; =0x00001598
	str r0, [r5, r1]
	sub r1, #0x24
	ldr r0, [r5, r1]
	mov r1, #0x18
	bl NewString_ReadMsgData
	ldr r1, _021D8D08 ; =0x0000159C
	str r0, [r5, r1]
	sub r1, #0x28
	ldr r0, [r5, r1]
	mov r1, #0x19
	bl NewString_ReadMsgData
	ldr r1, _021D8D0C ; =0x000015A0
	str r0, [r5, r1]
	sub r1, #0x2c
	ldr r0, [r5, r1]
	mov r1, #8
	bl NewString_ReadMsgData
	ldr r1, _021D8D10 ; =0x000015A4
	str r0, [r5, r1]
	sub r1, #0x30
	ldr r0, [r5, r1]
	mov r1, #9
	bl NewString_ReadMsgData
	ldr r1, _021D8D14 ; =0x000015A8
	mov r4, #0
	str r0, [r5, r1]
	add r6, r5, #0
	add r7, r1, #4
_021D8CAC:
	ldr r0, _021D8CE4 ; =0x00001574
	add r1, r4, #3
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	str r0, [r6, r7]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #5
	blt _021D8CAC
	mov r7, #0x57
	mov r4, #0
	add r6, r5, #0
	lsl r7, r7, #6
_021D8CC8:
	ldr r0, _021D8CE4 ; =0x00001574
	add r1, r4, #0
	ldr r0, [r5, r0]
	add r1, #0xa
	bl NewString_ReadMsgData
	str r0, [r6, r7]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, #0xa
	blt _021D8CC8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8CE0: .word 0x0000019D
_021D8CE4: .word 0x00001574
_021D8CE8: .word 0x00001578
_021D8CEC: .word 0x0000157C
_021D8CF0: .word 0x00001584
_021D8CF4: .word 0x00001588
_021D8CF8: .word 0x0000158C
_021D8CFC: .word 0x00001590
_021D8D00: .word 0x00001594
_021D8D04: .word 0x00001598
_021D8D08: .word 0x0000159C
_021D8D0C: .word 0x000015A0
_021D8D10: .word 0x000015A4
_021D8D14: .word 0x000015A8
	thumb_func_end MOD73_021D8BDC

	thumb_func_start MOD73_021D8D18
MOD73_021D8D18: ; 0x021D8D18
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _021D8DBC ; =0x000015A8
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DC0 ; =0x000015A4
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DC4 ; =0x00001594
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DC8 ; =0x00001590
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DCC ; =0x0000158C
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DD0 ; =0x00001588
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DD4 ; =0x00001584
	ldr r0, [r6, r0]
	bl String_dtor
	mov r0, #0x56
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DD8 ; =0x00001598
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DDC ; =0x0000159C
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DE0 ; =0x000015A0
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r7, _021D8DE4 ; =0x000015AC
	mov r4, #0
	add r5, r6, #0
_021D8D7C:
	ldr r0, [r5, r7]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #5
	blt _021D8D7C
	mov r7, #0x57
	mov r5, #0
	add r4, r6, #0
	lsl r7, r7, #6
_021D8D92:
	ldr r0, [r4, r7]
	bl String_dtor
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #0xa
	blt _021D8D92
	ldr r0, _021D8DE8 ; =0x0000157C
	ldr r0, [r6, r0]
	bl String_dtor
	ldr r0, _021D8DEC ; =0x00001578
	ldr r0, [r6, r0]
	bl FUN_0200AB18
	ldr r0, _021D8DF0 ; =0x00001574
	ldr r0, [r6, r0]
	bl DestroyMsgData
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8DBC: .word 0x000015A8
_021D8DC0: .word 0x000015A4
_021D8DC4: .word 0x00001594
_021D8DC8: .word 0x00001590
_021D8DCC: .word 0x0000158C
_021D8DD0: .word 0x00001588
_021D8DD4: .word 0x00001584
_021D8DD8: .word 0x00001598
_021D8DDC: .word 0x0000159C
_021D8DE0: .word 0x000015A0
_021D8DE4: .word 0x000015AC
_021D8DE8: .word 0x0000157C
_021D8DEC: .word 0x00001578
_021D8DF0: .word 0x00001574
	thumb_func_end MOD73_021D8D18

	thumb_func_start MOD73_021D8DF4
MOD73_021D8DF4: ; 0x021D8DF4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, _021D8E7C ; =0x00001428
	add r4, r1, #0
	ldr r1, [r7, r0]
	cmp r1, #1
	bne _021D8E0C
	bl FUN_02030F20
	ldr r1, _021D8E80 ; =0x00001420
	str r0, [r7, r1]
	b _021D8E12
_021D8E0C:
	mov r1, #1
	sub r0, #8
	str r1, [r7, r0]
_021D8E12:
	bl FUN_020842D0
	add r5, r0, #0
	bl FUN_020842D8
	add r1, r0, #0
	ldr r0, [r7]
	ldr r3, _021D8E7C ; =0x00001428
	str r0, [sp]
	ldr r3, [r7, r3]
	add r0, r5, #0
	add r2, r7, #0
	bl MOD73_021D9094
	ldr r1, _021D8E84 ; =0x00001424
	str r0, [r7, r1]
	ldr r0, _021D8E88 ; =0x0000155C
	mov r1, #4
	add r0, r7, r0
	add r2, r1, #0
	bl memset
	ldr r0, _021D8E7C ; =0x00001428
	ldr r0, [r7, r0]
	cmp r0, #1
	bne _021D8E70
	mov r6, #0
	add r4, r6, #0
	add r5, r7, #0
_021D8E4C:
	add r0, r4, #0
	bl FUN_0202DFA4
	ldr r1, _021D8E8C ; =0x00001560
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D8E66
	ldr r0, _021D8E88 ; =0x0000155C
	add r1, r7, r6
	strb r4, [r1, r0]
	add r6, r6, #1
_021D8E66:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D8E4C
	pop {r3, r4, r5, r6, r7, pc}
_021D8E70:
	ldr r0, _021D8E88 ; =0x0000155C
	mov r1, #0
	strb r1, [r7, r0]
	add r0, r0, #4
	str r4, [r7, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8E7C: .word 0x00001428
_021D8E80: .word 0x00001420
_021D8E84: .word 0x00001424
_021D8E88: .word 0x0000155C
_021D8E8C: .word 0x00001560
	thumb_func_end MOD73_021D8DF4

	thumb_func_start MOD73_021D8E90
MOD73_021D8E90: ; 0x021D8E90
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D8EA4 ; =0x00001424
	ldr r0, [r4, r0]
	bl MOD73_021D90F4
	ldr r0, _021D8EA4 ; =0x00001424
	mov r1, #0
	str r1, [r4, r0]
	pop {r4, pc}
	.align 2, 0
_021D8EA4: .word 0x00001424
	thumb_func_end MOD73_021D8E90

	thumb_func_start MOD73_021D8EA8
MOD73_021D8EA8: ; 0x021D8EA8
	add r0, r3, #0
	ldr r3, _021D8EB0 ; =MOD73_021D768C
	mov r1, #3
	bx r3
	.align 2, 0
_021D8EB0: .word MOD73_021D768C
	thumb_func_end MOD73_021D8EA8

	thumb_func_start MOD73_021D8EB4
MOD73_021D8EB4: ; 0x021D8EB4
	add r0, r3, #0
	ldr r3, _021D8EBC ; =MOD73_021D768C
	mov r1, #8
	bx r3
	.align 2, 0
_021D8EBC: .word MOD73_021D768C
	thumb_func_end MOD73_021D8EB4

	thumb_func_start MOD73_021D8EC0
MOD73_021D8EC0: ; 0x021D8EC0
	push {r3, r4, r5, lr}
	ldr r0, _021D8EF4 ; =0x00001498
	add r5, r1, #0
	add r4, r3, #0
	add r1, r2, #0
	add r0, r4, r0
	add r2, r5, #0
	bl memcpy
	ldr r0, _021D8EF8 ; =0x000014A8
	mov r1, #0xa
	add r3, r4, r0
	add r0, #0x1c
	add r2, r4, r0
_021D8EDC:
	ldrh r0, [r3]
	add r3, r3, #2
	strh r0, [r2]
	add r2, r2, #2
	sub r1, r1, #1
	bne _021D8EDC
	add r0, r4, #0
	mov r1, #5
	bl MOD73_021D768C
	pop {r3, r4, r5, pc}
	nop
_021D8EF4: .word 0x00001498
_021D8EF8: .word 0x000014A8
	thumb_func_end MOD73_021D8EC0

	thumb_func_start MOD73_021D8EFC
MOD73_021D8EFC: ; 0x021D8EFC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	ldr r0, _021D8F7C ; =0x00001424
	add r5, r3, #0
	ldr r0, [r5, r0]
	str r1, [sp]
	str r2, [sp, #4]
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D8F76
	mov r0, #0x55
	lsl r0, r0, #6
	lsl r4, r6, #2
	add r7, r5, r0
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r7, r4
	bl memcpy
	ldr r0, _021D8F80 ; =0x00001550
	mov r2, #1
	add r1, r5, r6
	strb r2, [r1, r0]
	ldr r1, [r7, r4]
	add r2, r5, r4
	sub r0, #0xf0
	str r1, [r2, r0]
	mov r0, #0
	ldr r1, _021D8F80 ; =0x00001550
	add r3, r0, #0
_021D8F3C:
	add r2, r5, r3
	ldrb r2, [r2, r1]
	cmp r2, #1
	bne _021D8F46
	add r0, r0, #1
_021D8F46:
	add r3, r3, #1
	cmp r3, #4
	blt _021D8F3C
	ldr r1, _021D8F84 ; =0x00001420
	ldr r2, [r5, r1]
	cmp r0, r2
	blt _021D8F76
	mov r0, #0xba
	lsl r0, r0, #2
	add r1, #0x50
	add r0, r5, r0
	add r1, r5, r1
	bl MOD73_021DB994
	bl MOD73_021D9084
	ldr r3, _021D8F88 ; =0x00001460
	add r2, r0, #0
	add r1, r5, r3
	sub r3, #0x3c
	ldr r3, [r5, r3]
	mov r0, #0x18
	bl MOD73_021D90D0
_021D8F76:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8F7C: .word 0x00001424
_021D8F80: .word 0x00001550
_021D8F84: .word 0x00001420
_021D8F88: .word 0x00001460
	thumb_func_end MOD73_021D8EFC

	thumb_func_start MOD73_021D8F8C
MOD73_021D8F8C: ; 0x021D8F8C
	push {r4, lr}
	add r4, r1, #0
	ldr r1, _021D8FA4 ; =0x000014BC
	add r3, r3, r1
	mov r1, #0x1c
	mul r1, r0
	add r0, r3, r1
	add r1, r2, #0
	add r2, r4, #0
	bl memcpy
	pop {r4, pc}
	.align 2, 0
_021D8FA4: .word 0x000014BC
	thumb_func_end MOD73_021D8F8C

	thumb_func_start MOD73_021D8FA8
MOD73_021D8FA8: ; 0x021D8FA8
	push {r3, r4, r5, lr}
	ldr r0, _021D8FC4 ; =0x00001484
	add r5, r1, #0
	add r4, r3, #0
	add r1, r2, #0
	add r0, r4, r0
	add r2, r5, #0
	bl memcpy
	add r0, r4, #0
	mov r1, #0xa
	bl MOD73_021D768C
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8FC4: .word 0x00001484
	thumb_func_end MOD73_021D8FA8

	thumb_func_start MOD73_021D8FC8
MOD73_021D8FC8: ; 0x021D8FC8
	push {r4, lr}
	ldr r0, _021D8FDC ; =0x0000152C
	add r4, r1, #0
	ldr r0, [r3, r0]
	add r1, r2, #0
	add r2, r4, #0
	bl memcpy
	pop {r4, pc}
	nop
_021D8FDC: .word 0x0000152C
	thumb_func_end MOD73_021D8FC8

	thumb_func_start MOD73_021D8FE0
MOD73_021D8FE0: ; 0x021D8FE0
	push {r3, r4, r5, lr}
	ldr r0, _021D8FFC ; =0x00001571
	add r5, r1, #0
	add r4, r3, #0
	add r1, r2, #0
	add r0, r4, r0
	add r2, r5, #0
	bl memcpy
	add r0, r4, #0
	mov r1, #0xc
	bl MOD73_021D768C
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8FFC: .word 0x00001571
	thumb_func_end MOD73_021D8FE0

	thumb_func_start MOD73_021D9000
MOD73_021D9000: ; 0x021D9000
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _021D906C ; =0x00001424
	add r4, r3, #0
	ldr r0, [r4, r0]
	add r6, r1, #0
	add r7, r2, #0
	bl MOD73_021D910C
	cmp r0, #0
	bne _021D906A
	ldr r0, _021D9070 ; =0x00001554
	add r1, r7, #0
	add r0, r4, r0
	add r0, r0, r5
	add r2, r6, #0
	bl memcpy
	ldr r0, _021D9074 ; =0x00001558
	add r1, r4, r5
	mov r2, #1
	strb r2, [r1, r0]
	add r6, sp, #0
	mov r3, #0
	strb r2, [r6]
	add r2, r3, #0
	sub r7, r0, #4
	add r5, r0, #0
_021D9038:
	add r1, r4, r2
	ldrb r0, [r1, r5]
	cmp r0, #1
	bne _021D904A
	ldrb r0, [r6]
	ldrb r1, [r1, r7]
	add r3, r3, #1
	and r0, r1
	strb r0, [r6]
_021D904A:
	add r2, r2, #1
	cmp r2, #4
	blt _021D9038
	ldr r0, _021D9078 ; =0x00001420
	ldr r0, [r4, r0]
	cmp r3, r0
	blt _021D906A
	bl MOD73_021D9080
	ldr r3, _021D906C ; =0x00001424
	add r2, r0, #0
	ldr r3, [r4, r3]
	mov r0, #0x1d
	add r1, sp, #0
	bl MOD73_021D90D0
_021D906A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D906C: .word 0x00001424
_021D9070: .word 0x00001554
_021D9074: .word 0x00001558
_021D9078: .word 0x00001420
	thumb_func_end MOD73_021D9000

	thumb_func_start MOD73_021D907C
MOD73_021D907C: ; 0x021D907C
	mov r0, #0
	bx lr
	thumb_func_end MOD73_021D907C

	thumb_func_start MOD73_021D9080
MOD73_021D9080: ; 0x021D9080
	mov r0, #1
	bx lr
	thumb_func_end MOD73_021D9080

	thumb_func_start MOD73_021D9084
MOD73_021D9084: ; 0x021D9084
	mov r0, #0x24
	bx lr
	thumb_func_end MOD73_021D9084

	thumb_func_start MOD73_021D9088
MOD73_021D9088: ; 0x021D9088
	mov r0, #4
	bx lr
	thumb_func_end MOD73_021D9088

	thumb_func_start MOD73_021D908C
MOD73_021D908C: ; 0x021D908C
	mov r0, #0x1c
	bx lr
	thumb_func_end MOD73_021D908C

	thumb_func_start MOD73_021D9090
MOD73_021D9090: ; 0x021D9090
	mov r0, #0x14
	bx lr
	thumb_func_end MOD73_021D9090

	thumb_func_start MOD73_021D9094
MOD73_021D9094: ; 0x021D9094
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	ldr r0, [sp, #0x18]
	mov r1, #8
	str r2, [sp]
	add r5, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	str r5, [r4]
	str r0, [r4, #4]
	cmp r5, #1
	bne _021D90BE
	ldr r2, [sp]
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_0202D8D0
	b _021D90CC
_021D90BE:
	ldr r2, [sp]
	ldr r3, [sp, #0x18]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD73_021D9120
	str r0, [r4, #4]
_021D90CC:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D9094

	thumb_func_start MOD73_021D90D0
MOD73_021D90D0: ; 0x021D90D0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r3, #0
	ldr r3, [r6]
	add r5, r0, #0
	add r4, r1, #0
	add r7, r2, #0
	cmp r3, #1
	bne _021D90E6
	bl FUN_02030ADC
	pop {r3, r4, r5, r6, r7, pc}
_021D90E6:
	ldr r0, [r6, #4]
	add r1, r5, #0
	add r2, r4, #0
	add r3, r7, #0
	bl MOD73_021D91D4
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D90D0

	thumb_func_start MOD73_021D90F4
MOD73_021D90F4: ; 0x021D90F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _021D9104
	ldr r0, [r4, #4]
	bl MOD73_021D91BC
_021D9104:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD73_021D90F4

	thumb_func_start MOD73_021D910C
MOD73_021D910C: ; 0x021D910C
	push {r3, lr}
	ldr r0, [r0]
	cmp r0, #1
	bne _021D911A
	bl FUN_02031190
	pop {r3, pc}
_021D911A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD73_021D910C

	thumb_func_start MOD73_021D9120
MOD73_021D9120: ; 0x021D9120
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x1b
	add r5, r0, #0
	add r0, r3, #0
	lsl r1, r1, #4
	add r7, r2, #0
	bl AllocFromHeap
	mov r2, #0x1b
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl memset
	mov r1, #0x1a
	lsl r1, r1, #4
	str r5, [r4, r1]
	add r0, r1, #4
	str r6, [r4, r0]
	add r1, #8
	str r7, [r4, r1]
	ldr r0, _021D9160 ; =MOD73_021D9168
	ldr r2, _021D9164 ; =0x00001388
	add r1, r4, #0
	bl FUN_0200CA98
	mov r1, #0x6b
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D9160: .word MOD73_021D9168
_021D9164: .word 0x00001388
	thumb_func_end MOD73_021D9120

	thumb_func_start MOD73_021D9168
MOD73_021D9168: ; 0x021D9168
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r1, #0
	mov r0, #0
	str r0, [sp]
	add r6, r7, #0
_021D9174:
	ldr r0, [r6]
	cmp r0, #1
	bne _021D91AA
	mov r4, #0x1a
	lsl r4, r4, #4
	ldr r4, [r7, r4]
	mov r3, #0x6a
	mov ip, r4
	ldr r4, [r6, #4]
	mov r5, #0xc
	mul r5, r4
	str r5, [sp, #4]
	lsl r3, r3, #2
	add r2, r6, #0
	ldr r4, [sp, #4]
	mov r5, ip
	ldr r1, [r6, #0x30]
	ldr r3, [r7, r3]
	ldr r4, [r5, r4]
	mov r0, #0
	add r2, #8
	blx r4
	add r0, r6, #0
	mov r1, #0
	mov r2, #0x34
	bl memset
_021D91AA:
	ldr r0, [sp]
	add r6, #0x34
	add r0, r0, #1
	str r0, [sp]
	cmp r0, #8
	blt _021D9174
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9168

	thumb_func_start MOD73_021D91BC
MOD73_021D91BC: ; 0x021D91BC
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x6b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D91BC

	thumb_func_start MOD73_021D91D4
MOD73_021D91D4: ; 0x021D91D4
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	str r2, [sp]
	add r7, r1, #0
	add r5, r3, #0
	add r0, r4, #0
	add r2, r6, #0
_021D91E4:
	ldr r1, [r2]
	cmp r1, #0
	bne _021D91F2
	mov r1, #0x34
	mul r1, r0
	add r4, r6, r1
	b _021D91FA
_021D91F2:
	add r0, r0, #1
	add r2, #0x34
	cmp r0, #8
	blt _021D91E4
_021D91FA:
	cmp r4, #0
	bne _021D9202
	bl ErrorHandling
_021D9202:
	mov r0, #0x1a
	lsl r0, r0, #4
	add r1, r7, #0
	ldr r2, [r6, r0]
	sub r1, #0x16
	mov r0, #0xc
	mul r0, r1
	add r0, r2, r0
	ldr r0, [r0, #4]
	blx r0
	cmp r0, r5
	beq _021D921E
	bl ErrorHandling
_021D921E:
	cmp r5, #0x26
	blt _021D9226
	bl ErrorHandling
_021D9226:
	sub r7, #0x16
	str r7, [r4, #4]
	cmp r5, #0
	ble _021D923A
	add r0, r4, #0
	ldr r1, [sp]
	add r0, #8
	add r2, r5, #0
	bl memcpy
_021D923A:
	str r5, [r4, #0x30]
	mov r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021D91D4

	thumb_func_start MOD73_021D9244
MOD73_021D9244: ; 0x021D9244
	push {r4, lr}
	add r4, r0, #0
	add r0, r2, #0
	mov r2, #0
	bl FUN_02002E14
	lsr r0, r0, #1
	sub r0, r4, r0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9244

	thumb_func_start MOD73_021D9258
MOD73_021D9258: ; 0x021D9258
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	str r2, [sp]
	mov r0, #0x7a
	mov r2, #0
	add r3, sp, #4
	bl FUN_02006BB0
	add r4, r0, #0
	ldr r0, [sp, #4]
	str r5, [sp, #8]
	str r0, [sp, #0xc]
	add r0, sp, #8
	bl FUN_02013D98
	add r5, r0, #0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9258

	thumb_func_start MOD73_021D9288
MOD73_021D9288: ; 0x021D9288
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r3, r2, #0
	mov r0, #0x7a
	add r2, sp, #0
	bl FUN_02006C08
	add r4, r0, #0
	ldr r0, [sp]
	str r5, [sp, #4]
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, sp, #4
	bl FUN_02013E14
	add r5, r0, #0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021D9288

	thumb_func_start MOD73_021D92B8
MOD73_021D92B8: ; 0x021D92B8
	push {r4, lr}
	sub sp, #0x20
	str r0, [sp]
	str r1, [sp, #4]
	str r2, [sp, #8]
	add r0, sp, #0
	ldr r1, [sp, #0x28]
	strh r3, [r0, #0xc]
	strh r1, [r0, #0xe]
	mov r2, #0
	strh r2, [r0, #0x10]
	mov r1, #0x1f
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x2c]
	str r1, [sp, #0x18]
	strh r2, [r0, #0x1c]
	add r0, sp, #0
	bl FUN_02013E84
	mov r1, #0
	add r4, r0, #0
	bl FUN_02013EB0
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	thumb_func_end MOD73_021D92B8

	thumb_func_start MOD73_021D92EC
MOD73_021D92EC: ; 0x021D92EC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r6, r3, #0
	add r7, r2, #0
	add r1, r5, #4
	add r2, r6, #0
	bl FUN_02008C9C
	str r0, [r5]
	mov r4, #0
_021D9302:
	add r0, r7, #0
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_02008DEC
	mov r1, #0x4b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D9302
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D92EC

	thumb_func_start MOD73_021D931C
MOD73_021D931C: ; 0x021D931C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl FUN_0201FD58
	mov r4, #0
	mov r6, #0x4b
	str r4, [r5]
	lsl r6, r6, #2
_021D932E:
	ldr r0, [r5, r6]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021D932E
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021D931C

	thumb_func_start MOD73_021D9340
MOD73_021D9340: ; 0x021D9340
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	ldr r6, [sp, #0x58]
	add r5, r0, #0
	ldr r7, [sp, #0x5c]
	str r6, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r7, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #0x4b
	lsl r0, r0, #2
	add r4, r1, #0
	str r3, [sp, #0x30]
	str r2, [sp, #0x2c]
	add r1, r2, #0
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x4c]
	mov r3, #0
	bl FUN_02008F90
	str r0, [r4]
	str r6, [sp]
	mov r1, #1
	ldr r0, [sp, #0x48]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r7, [sp, #0xc]
	mov r0, #0x13
	str r1, [sp, #0x10]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	mov r3, #0
	bl FUN_0200904C
	str r0, [r4, #4]
	mov r3, #0
	str r3, [r4, #0x10]
	str r6, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4d
	str r7, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x50]
	bl FUN_020090AC
	str r0, [r4, #8]
	str r6, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4e
	str r7, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x54]
	mov r3, #0
	bl FUN_020090AC
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl FUN_02009B78
	cmp r0, #0
	bne _021D93D0
	bl ErrorHandling
_021D93D0:
	ldr r0, [r4]
	bl FUN_02009474
	ldr r0, [r4, #4]
	bl FUN_02009D68
	cmp r0, #0
	bne _021D93E4
	bl ErrorHandling
_021D93E4:
	ldr r0, [r4, #4]
	bl FUN_02009474
	mov r0, #0
	mov r2, #0x4b
	str r6, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	add r4, #0x14
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	add r3, r6, #0
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r2, #0xc
	str r1, [sp, #0x1c]
	ldr r1, [r5, r2]
	add r2, r6, #0
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_02008AA4
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D9340

	thumb_func_start MOD73_021D942C
MOD73_021D942C: ; 0x021D942C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	ldr r6, [sp, #0x5c]
	add r5, r0, #0
	ldr r7, [sp, #0x60]
	str r6, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r7, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #0x4b
	lsl r0, r0, #2
	add r4, r1, #0
	str r3, [sp, #0x30]
	str r2, [sp, #0x2c]
	add r1, r2, #0
	ldr r0, [r5, r0]
	ldr r2, [sp, #0x50]
	mov r3, #0
	bl FUN_02008F90
	str r0, [r4]
	ldr r0, [sp, #0x30]
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x30]
	bl FUN_02009530
	str r0, [sp, #0x34]
	str r6, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x4d
	str r7, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x54]
	mov r3, #0
	bl FUN_020090AC
	str r0, [r4, #8]
	str r6, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x4e
	str r7, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x58]
	mov r3, #0
	bl FUN_020090AC
	str r0, [r4, #0xc]
	ldr r0, [r4]
	bl FUN_02009B78
	cmp r0, #0
	bne _021D94AA
	bl ErrorHandling
_021D94AA:
	ldr r0, [r4]
	bl FUN_02009474
	mov r0, #0
	mov r2, #0x4b
	str r6, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r2, r2, #2
	ldr r1, [r5, r2]
	add r4, #0x14
	str r1, [sp, #0x14]
	add r1, r2, #4
	ldr r1, [r5, r1]
	add r3, r6, #0
	str r1, [sp, #0x18]
	add r1, r2, #0
	add r1, #8
	ldr r1, [r5, r1]
	add r2, #0xc
	str r1, [sp, #0x1c]
	ldr r1, [r5, r2]
	ldr r2, [sp, #0x34]
	str r1, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r4, #0
	add r1, r6, #0
	bl FUN_02008AA4
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021D942C

	thumb_func_start MOD73_021D94F4
MOD73_021D94F4: ; 0x021D94F4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	ldr r0, [r7]
	bl FUN_02009C0C
	ldr r0, [r7, #0x10]
	cmp r0, #0
	bne _021D950C
	ldr r0, [r7, #4]
	bl FUN_02009E04
_021D950C:
	mov r6, #0
	add r4, r7, #0
_021D9510:
	cmp r6, #1
	beq _021D9522
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r4]
	bl FUN_02009490
	b _021D9534
_021D9522:
	ldr r0, [r7, #0x10]
	cmp r0, #0
	bne _021D9534
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	ldr r1, [r4]
	bl FUN_02009490
_021D9534:
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #4
	blt _021D9510
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D94F4

	thumb_func_start MOD73_021D9540
MOD73_021D9540: ; 0x021D9540
	push {r4, lr}
	sub sp, #0x20
	ldr r0, [r0]
	add r1, #0x14
	str r0, [sp]
	ldr r0, [sp, #0x28]
	str r1, [sp, #4]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	str r2, [sp, #8]
	str r0, [sp, #0x14]
	mov r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x30]
	str r3, [sp, #0xc]
	str r0, [sp, #0x1c]
	add r0, sp, #0
	bl FUN_0201FF84
	add r4, r0, #0
	bne _021D956E
	bl ErrorHandling
_021D956E:
	add r0, r4, #0
	add sp, #0x20
	pop {r4, pc}
	thumb_func_end MOD73_021D9540

	thumb_func_start MOD73_021D9574
MOD73_021D9574: ; 0x021D9574
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr
	thumb_func_end MOD73_021D9574

	thumb_func_start MOD73_021D9584
MOD73_021D9584: ; 0x021D9584
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #8]
	lsl r2, r2, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	ldr r1, [r4, #0x10]
	lsl r1, r1, #0xc
	bl FX_Div
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021D95C4
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021D95C4:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9584

	thumb_func_start MOD73_021D95CC
MOD73_021D95CC: ; 0x021D95CC
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r0, #0
	add r7, r2, #0
	add r0, r3, #0
	add r6, r1, #0
	lsl r2, r4, #0xc
	str r3, [sp]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	add r2, r0, #0
	sub r0, r7, r6
	mov r7, #2
	mov r3, #0
	lsl r7, r7, #0xa
	add r2, r2, r7
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	sub r2, r0, r2
	asr r1, r2, #0x1f
	lsr r0, r2, #0x13
	lsl r1, r1, #0xd
	orr r1, r0
	lsl r0, r2, #0xd
	add r0, r0, r7
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	add r1, r4, #0
	mul r1, r4
	lsl r1, r1, #0xc
	bl FX_Div
	str r6, [r5]
	ldr r1, [sp]
	str r6, [r5, #4]
	str r1, [r5, #8]
	str r0, [r5, #0xc]
	mov r0, #0
	str r0, [r5, #0x10]
	str r4, [r5, #0x14]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021D95CC

	thumb_func_start MOD73_021D962C
MOD73_021D962C: ; 0x021D962C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r6, [r5, #0x10]
	ldr r0, [r5, #8]
	lsl r2, r6, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsr r4, r2, #0xc
	lsl r0, r1, #0x14
	add r2, r6, #0
	orr r4, r0
	ldr r0, [r5, #0xc]
	mul r2, r6
	lsl r2, r2, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	lsl r1, r2, #2
	bl FX_Div
	ldr r1, [r5, #4]
	add r0, r4, r0
	add r0, r1, r0
	str r0, [r5]
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	add r0, r0, #1
	cmp r0, r1
	bgt _021D968C
	str r0, [r5, #0x10]
	mov r0, #0
	pop {r4, r5, r6, pc}
_021D968C:
	str r1, [r5, #0x10]
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021D962C

	thumb_func_start MOD73_021D9694
MOD73_021D9694: ; 0x021D9694
	push {r4}
	sub sp, #0xc
	str r2, [sp, #4]
	str r3, [sp, #8]
	add r2, sp, #0
	add r4, r0, #0
	str r1, [sp]
	ldmia r2!, {r0, r1}
	stmia r4!, {r0, r1}
	ldr r0, [r2]
	str r0, [r4]
	add sp, #0xc
	pop {r4}
	bx lr
	thumb_func_end MOD73_021D9694

	thumb_func_start MOD73_021D96B0
MOD73_021D96B0: ; 0x021D96B0
	push {r3, r4, r5, lr}
	mov r2, #0x1f
	add r4, r1, #0
	mov r1, #0
	lsl r2, r2, #4
	add r5, r0, #0
	bl memset
	mov r0, #0x42
	lsl r0, r0, #2
	str r4, [r5, r0]
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021D96B0

	thumb_func_start MOD73_021D96C8
MOD73_021D96C8: ; 0x021D96C8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D96D6
	bl ErrorHandling
_021D96D6:
	mov r2, #0x1f
	add r0, r4, #0
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	pop {r4, pc}
	thumb_func_end MOD73_021D96C8

	thumb_func_start MOD73_021D96E4
MOD73_021D96E4: ; 0x021D96E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r0, [sp, #0x18]
	ldr r4, [sp, #0x18]
	mov r0, #0
	ldr r6, [sp, #0x40]
	ldr r5, [sp, #0x18]
	str r1, [sp, #0x1c]
	add r7, r2, #0
	str r3, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r4, #0x28
_021D96FE:
	ldr r0, [sp, #0x1c]
	ldr r3, [r0]
	cmp r3, #0
	beq _021D977A
	mov r0, #1
	str r0, [sp]
	add r0, r3, #0
	sub r0, #0x8f
	str r0, [sp, #4]
	mov r0, #5
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	mov r0, #0xfa
	ldr r1, [sp, #0x28]
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, r4, #0
	mov r2, #0x35
	sub r3, #0x4f
	str r6, [sp, #0x14]
	bl MOD73_021D9340
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r2, #0
	add r0, r7, #0
	add r1, r4, #0
	add r3, r2, #0
	str r6, [sp, #8]
	bl MOD73_021D9540
	mov r1, #0
	str r0, [r5, #8]
	bl FUN_020200A0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r2, #0
	ldr r1, [sp, #0x20]
	str r6, [sp, #8]
	add r0, r7, #0
	add r3, r2, #0
	bl MOD73_021D9540
	str r0, [r5, #0x18]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, #0x18]
	mov r1, #1
	bl FUN_02020130
	ldr r0, [sp, #0x24]
	add r4, #0x38
	add r0, r0, #1
	add r5, r5, #4
	str r0, [sp, #0x24]
_021D977A:
	mov r0, #0x42
	ldr r1, [sp, #0x18]
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	ldr r0, [sp, #0x24]
	cmp r1, r0
	beq _021D9798
	ldr r0, [sp, #0x1c]
	add r0, r0, #4
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x28]
	add r0, r0, #1
	str r0, [sp, #0x28]
	cmp r0, #4
	blt _021D96FE
_021D9798:
	ldr r0, [sp, #0x18]
	mov r1, #1
	str r1, [r0]
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021D96E4

	thumb_func_start MOD73_021D97A4
MOD73_021D97A4: ; 0x021D97A4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, [r7]
	str r1, [sp]
	cmp r0, #1
	beq _021D97B4
	bl ErrorHandling
_021D97B4:
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	mov r4, #0
	cmp r0, #0
	ble _021D97EA
	add r6, r7, #0
	add r5, r7, #0
	add r6, #0x28
_021D97C6:
	ldr r0, [r5, #8]
	bl FUN_0201FFC8
	ldr r0, [r5, #0x18]
	bl FUN_0201FFC8
	ldr r0, [sp]
	add r1, r6, #0
	bl MOD73_021D94F4
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r7, r0]
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0x38
	cmp r4, r0
	blt _021D97C6
_021D97EA:
	mov r0, #0
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D97A4

	thumb_func_start MOD73_021D97F0
MOD73_021D97F0: ; 0x021D97F0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r0, [sp, #4]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021D9800
	bl ErrorHandling
_021D9800:
	mov r0, #0
	str r0, [sp, #0xc]
	mov r2, #0x42
	ldr r0, [sp, #4]
	lsl r2, r2, #2
	ldr r0, [r0, r2]
	cmp r0, #0
	ble _021D98A0
	ldr r0, [sp, #4]
	add r1, r2, #4
	add r0, r0, r1
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	add r2, #0x64
	ldr r4, _021D98B4 ; =0x021DBE2C
	add r7, r0, r2
	add r6, r0, #0
	add r5, r0, #0
_021D9824:
	ldrb r0, [r4, #0x10]
	mov r1, #8
	mov r2, #0xa
	str r0, [sp]
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r0, [sp, #8]
	ldr r3, [r4]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD73_021D95CC
	ldrb r0, [r4, #0x10]
	mov r1, #0xc
	mov r2, #0xe
	str r0, [sp]
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	ldr r3, [r4, #4]
	add r0, r7, #0
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD73_021D95CC
	mov r1, #0x43
	mov r2, #0x5b
	lsl r1, r1, #2
	lsl r2, r2, #2
	ldr r1, [r6, r1]
	ldr r2, [r6, r2]
	add r0, sp, #0x10
	mov r3, #0
	bl MOD73_021D9694
	ldr r0, [r5, #8]
	add r1, sp, #0x10
	bl FUN_02020044
	mov r0, #0x73
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
	ldrb r1, [r4, #0x11]
	add r0, #0x10
	add r4, #0x14
	str r1, [r5, r0]
	ldr r0, [sp, #8]
	ldr r1, [sp, #4]
	add r0, #0x18
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r7, #0x18
	add r0, r0, #1
	str r0, [sp, #0xc]
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	ldr r0, [sp, #0xc]
	add r6, #0x18
	add r5, r5, #4
	cmp r0, r1
	blt _021D9824
_021D98A0:
	mov r1, #0x7b
	ldr r0, [sp, #4]
	mov r2, #0
	lsl r1, r1, #2
	str r2, [r0, r1]
	mov r1, #1
	str r1, [r0, #4]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D98B4: .word MOD73_021DBE2C
	thumb_func_end MOD73_021D97F0

	thumb_func_start MOD73_021D98B8
MOD73_021D98B8: ; 0x021D98B8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r6, #4]
	cmp r0, #0
	bne _021D98CE
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D98CE:
	mov r0, #0x7b
	lsl r0, r0, #2
	add r1, r0, #0
	sub r1, #0xe4
	ldr r2, [r6, r0]
	ldr r1, [r6, r1]
	cmp r2, r1
	bge _021D991E
	add r1, r0, #0
	sub r1, #0x10
	add r1, r6, r1
	lsl r3, r2, #2
	ldr r2, [r1, r3]
	sub r2, r2, #1
	str r2, [r1, r3]
	ldr r1, [r6, r0]
	lsl r1, r1, #2
	add r2, r6, r1
	add r1, r0, #0
	sub r1, #0x10
	ldr r1, [r2, r1]
	cmp r1, #0
	bgt _021D991E
	add r3, r0, #0
	mov r1, #1
	sub r3, #0x20
	str r1, [r2, r3]
	ldr r0, [r6, r0]
	lsl r0, r0, #2
	add r0, r6, r0
	ldr r0, [r0, #8]
	bl FUN_020200A0
	mov r1, #0x7b
	lsl r1, r1, #2
	ldr r2, [r6, r1]
	add r0, r2, #2
	str r0, [sp, #4]
	add r0, r2, #1
	str r0, [r6, r1]
_021D991E:
	mov r1, #0x42
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	cmp r0, #0
	ble _021D9A02
	add r0, r1, #4
	add r0, r6, r0
	add r1, #0x64
	add r4, r6, #0
	str r0, [sp]
	add r7, r6, r1
	add r5, r6, #0
_021D993A:
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #3
	bhi _021D99E0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D9950: ; jump table
	.short _021D99E4 - _021D9950 - 2 ; case 0
	.short _021D9958 - _021D9950 - 2 ; case 1
	.short _021D99BE - _021D9950 - 2 ; case 2
	.short _021D99E4 - _021D9950 - 2 ; case 3
_021D9958:
	ldr r0, [sp]
	bl MOD73_021D962C
	str r0, [sp, #0xc]
	add r0, r7, #0
	bl MOD73_021D962C
	mov r1, #0x43
	mov r2, #0x5b
	lsl r1, r1, #2
	lsl r2, r2, #2
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	add r0, sp, #0x10
	mov r3, #0
	bl MOD73_021D9694
	ldr r0, [r4, #8]
	add r1, sp, #0x10
	bl FUN_02020044
	ldr r0, [sp, #0xc]
	cmp r0, #1
	bne _021D99E4
	ldr r0, [r4, #0x18]
	add r1, sp, #0x10
	bl FUN_02020044
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #0x18]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, _021D9A24 ; =0x000006BC
	bl FUN_020054C8
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r0, #1
	mov r0, #0x73
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021D99E4
_021D99BE:
	ldr r0, [r4, #0x18]
	bl FUN_02020388
	cmp r0, #0
	bne _021D99E4
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, r0, #1
	mov r0, #0x73
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021D99E4
_021D99E0:
	bl ErrorHandling
_021D99E4:
	ldr r0, [sp]
	add r4, r4, #4
	add r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #8]
	add r7, #0x18
	add r0, r0, #1
	str r0, [sp, #8]
	mov r0, #0x42
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r1, [sp, #8]
	add r5, #0x18
	cmp r1, r0
	blt _021D993A
_021D9A02:
	sub r0, r0, #1
	lsl r0, r0, #2
	add r1, r6, r0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #3
	bne _021D9A1C
	mov r0, #0
	str r0, [r6, #4]
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021D9A1C:
	ldr r0, [sp, #4]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021D9A24: .word 0x000006BC
	thumb_func_end MOD73_021D98B8

	thumb_func_start MOD73_021D9A28
MOD73_021D9A28: ; 0x021D9A28
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	mov r1, #0
	mov r2, #0x34
	add r7, r3, #0
	bl memset
	str r6, [r5, #0x18]
	ldr r0, [sp, #0x1c]
	str r4, [r5, #0x14]
	str r0, [r5]
	ldr r0, [sp, #0x18]
	str r7, [r5, #0x1c]
	str r0, [r5, #0x10]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9A28

	thumb_func_start MOD73_021D9A4C
MOD73_021D9A4C: ; 0x021D9A4C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _021D9A5A
	bl ErrorHandling
_021D9A5A:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x34
	bl memset
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9A4C

	thumb_func_start MOD73_021D9A68
MOD73_021D9A68: ; 0x021D9A68
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x30]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, #0
	beq _021D9A7A
	bl ErrorHandling
_021D9A7A:
	add r0, r5, #0
	add r1, r6, #0
	str r4, [r5, #4]
	bl MOD73_021D9BE0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD73_021D9CA0
	mov r0, #1
	str r0, [r5, #0x30]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9A68

	thumb_func_start MOD73_021D9A94
MOD73_021D9A94: ; 0x021D9A94
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #1
	beq _021D9AA2
	bl ErrorHandling
_021D9AA2:
	add r0, r4, #0
	bl MOD73_021D9C7C
	add r0, r4, #0
	bl MOD73_021D9D48
	mov r0, #0
	str r0, [r4, #0x30]
	pop {r4, pc}
	thumb_func_end MOD73_021D9A94

	thumb_func_start MOD73_021D9AB4
MOD73_021D9AB4: ; 0x021D9AB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl FUN_02019570
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_02018744
	pop {r4, pc}
	thumb_func_end MOD73_021D9AB4

	thumb_func_start MOD73_021D9AC8
MOD73_021D9AC8: ; 0x021D9AC8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r1, #0xf
	bl FUN_02019620
	ldr r1, [r4, #0x18]
	mov r2, #0
	ldr r0, [r4, #8]
	ldr r1, [r1, #0xc]
	add r3, r2, #0
	bl MOD73_021D9D5C
	mov r1, #0
	ldr r0, [r4, #8]
	mov r2, #1
	add r3, r1, #0
	bl FUN_0200D0BC
	pop {r4, pc}
	thumb_func_end MOD73_021D9AC8

	thumb_func_start MOD73_021D9AF0
MOD73_021D9AF0: ; 0x021D9AF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, [r5, #0x14]
	cmp r0, #1
	beq _021D9BDC
	mov r4, #0
	cmp r0, #0
	ble _021D9BCE
_021D9B02:
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r1, r2, r1
	add r2, r4, r2
	asr r2, r2, #1
	mov r0, #0xc
	add r6, r1, #0
	mul r6, r0
	lsl r0, r2, #2
	add r2, r2, r0
	str r2, [sp, #0x1c]
	mov r2, #0xa
	str r2, [sp]
	mov r2, #4
	str r2, [sp, #4]
	ldr r2, [r5, #0x2c]
	lsl r0, r0, #0x18
	add r2, #0xc
	str r2, [sp, #8]
	mov r2, #0xa
	mul r2, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	lsr r0, r0, #0x18
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x10]
	mov r0, #0x14
	str r0, [sp, #0x14]
	mov r0, #8
	add r2, r6, #5
	add r3, #0xd
	str r0, [sp, #0x18]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #4]
	mov r1, #5
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02018170
	mov r0, #0xa
	ldr r3, [sp, #0x1c]
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #2
	add r2, r6, #5
	add r3, #0xd
	str r0, [sp, #8]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #4]
	mov r1, #5
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_020186B4
	ldr r7, [r5, #0x1c]
	mov r2, #0x13
	ldr r0, [r5, #0x18]
	add r3, r7, r4
	lsl r2, r2, #4
	ldrb r2, [r3, r2]
	ldr r0, [r0, #4]
	mov r1, #0
	lsl r2, r2, #2
	add r3, r7, r2
	mov r2, #0x4d
	lsl r2, r2, #2
	ldr r2, [r3, r2]
	bl FUN_0200ABC0
	ldr r2, [r5, #0x18]
	ldr r0, [r2, #4]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0x14]
	bl StringExpandPlaceholders
	ldr r1, [r5, #0x18]
	lsl r0, r6, #3
	ldr r1, [r1, #8]
	add r0, #0x20
	mov r2, #1
	bl MOD73_021D9244
	ldr r1, [r5, #0x18]
	ldr r3, [sp, #0x1c]
	add r2, r0, #0
	lsl r3, r3, #3
	ldr r0, [r5, #0xc]
	ldr r1, [r1, #8]
	add r3, #8
	bl MOD73_021D9D5C
	ldr r0, [r5, #0x14]
	add r4, r4, #1
	cmp r4, r0
	blt _021D9B02
_021D9BCE:
	ldr r0, [r5, #0xc]
	bl FUN_02019220
	ldr r0, [r5, #4]
	mov r1, #5
	bl FUN_0201AC68
_021D9BDC:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021D9AF0

	thumb_func_start MOD73_021D9BE0
MOD73_021D9BE0: ; 0x021D9BE0
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018FF4
	str r0, [r5, #8]
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018FF4
	str r0, [r5, #0xc]
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r2, #4
	str r2, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	ldr r1, [r5, #8]
	add r3, r2, #0
	bl FUN_02019064
	mov r0, #0xd
	str r0, [sp]
	mov r0, #0x14
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	mov r0, #0x1f
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	ldr r1, [r5, #0xc]
	mov r2, #4
	mov r3, #6
	bl FUN_02019064
	ldr r0, [r5, #8]
	mov r1, #0xf
	bl FUN_02019620
	ldr r0, [r5, #0xc]
	mov r1, #0
	bl FUN_02019620
	ldr r0, [r5, #0x10]
	mov r1, #4
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	str r4, [sp, #4]
	ldr r0, [r5, #4]
	mov r2, #1
	mov r3, #0
	bl FUN_0200CD68
	mov r0, #4
	mov r1, #0x20
	add r2, r4, #0
	bl FUN_02002EEC
	mov r1, #1
	ldr r0, [r5, #8]
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200D0BC
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9BE0

	thumb_func_start MOD73_021D9C7C
MOD73_021D9C7C: ; 0x021D9C7C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl FUN_02019178
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020191A4
	ldr r0, [r4, #0xc]
	bl FUN_02019178
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl FUN_020191A4
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9C7C

	thumb_func_start MOD73_021D9CA0
MOD73_021D9CA0: ; 0x021D9CA0
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r3, #0x40
	add r5, r0, #0
	add r4, r1, #0
	str r3, [sp]
	mov r0, #0x7a
	mov r1, #1
	mov r2, #4
	str r4, [sp, #4]
	bl FUN_02006930
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	str r4, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0x7a
	mov r3, #5
	bl FUN_0200687C
	ldr r0, [r5, #0x14]
	cmp r0, #1
	bne _021D9CD6
	mov r1, #2
	b _021D9CD8
_021D9CD6:
	mov r1, #3
_021D9CD8:
	add r3, r5, #0
	str r4, [sp]
	mov r0, #0x7a
	mov r2, #0
	add r3, #0x24
	bl FUN_02006BDC
	str r0, [r5, #0x20]
	ldr r2, [r5, #0x24]
	mov r3, #0
	str r3, [sp]
	ldrh r0, [r2]
	mov r1, #5
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldrh r0, [r2, #2]
	add r2, #0xc
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_02018148
	ldr r1, [r5, #0x24]
	mov r2, #0
	ldrh r0, [r1]
	add r3, r2, #0
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrh r0, [r1, #2]
	mov r1, #5
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, [r5, #4]
	bl FUN_020186B4
	add r3, r5, #0
	str r4, [sp]
	mov r0, #0x7a
	mov r1, #4
	mov r2, #0
	add r3, #0x2c
	bl FUN_02006BDC
	str r0, [r5, #0x28]
	ldr r0, [r5, #4]
	mov r1, #5
	bl FUN_0201AC68
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021D9CA0

	thumb_func_start MOD73_021D9D48
MOD73_021D9D48: ; 0x021D9D48
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	bl FreeToHeap
	ldr r0, [r4, #0x28]
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9D48

	thumb_func_start MOD73_021D9D5C
MOD73_021D9D5C: ; 0x021D9D5C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r4, r2, #0
	str r3, [sp]
	mov r2, #0
	ldr r1, _021D9D80 ; =0x0001020F
	str r2, [sp, #4]
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	mov r1, #1
	add r2, r5, #0
	add r3, r4, #0
	bl FUN_0201BDE0
	add sp, #0x10
	pop {r3, r4, r5, pc}
	nop
_021D9D80: .word 0x0001020F
	thumb_func_end MOD73_021D9D5C

	thumb_func_start MOD73_021D9D84
MOD73_021D9D84: ; 0x021D9D84
	mov r1, #0
	strb r1, [r0]
	strb r1, [r0, #1]
	strb r1, [r0, #2]
	strb r1, [r0, #3]
	strb r1, [r0, #4]
	strb r1, [r0, #5]
	strb r1, [r0, #6]
	strb r1, [r0, #7]
	strb r1, [r0, #8]
	strb r1, [r0, #9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	bx lr
	thumb_func_end MOD73_021D9D84

	thumb_func_start MOD73_021D9DA0
MOD73_021D9DA0: ; 0x021D9DA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021D9DAE
	bl ErrorHandling
_021D9DAE:
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	strb r0, [r4, #4]
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	strb r0, [r4, #7]
	strb r0, [r4, #8]
	strb r0, [r4, #9]
	strb r0, [r4, #0xa]
	strb r0, [r4, #0xb]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9DA0

	thumb_func_start MOD73_021D9DCC
MOD73_021D9DCC: ; 0x021D9DCC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r3, [sp, #8]
	add r0, r1, #0
	ldr r3, [sp, #0x18]
	mov r1, #0x38
	mul r1, r3
	add r1, r2, r1
	mov r2, #2
	mov r3, #6
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD73_021D9540
	str r0, [r4, #8]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #8]
	ldr r1, [sp, #0x1c]
	bl FUN_02020130
	mov r0, #1
	str r0, [r4]
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD73_021D9DCC

	thumb_func_start MOD73_021D9E08
MOD73_021D9E08: ; 0x021D9E08
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	beq _021D9E16
	bl ErrorHandling
_021D9E16:
	ldr r0, [r4, #8]
	bl FUN_0201FFC8
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9E08

	thumb_func_start MOD73_021D9E24
MOD73_021D9E24: ; 0x021D9E24
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200BC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9E24

	thumb_func_start MOD73_021D9E3C
MOD73_021D9E3C: ; 0x021D9E3C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4, #8]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x2a
	lsl r0, r0, #0xe
	str r0, [sp]
	mov r0, #0xf
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	ldr r0, [r4, #8]
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9E3C

	thumb_func_start MOD73_021D9E6C
MOD73_021D9E6C: ; 0x021D9E6C
	push {r3, lr}
	ldr r0, [r0, #8]
	bl FUN_02020388
	cmp r0, #0
	bne _021D9E7C
	mov r0, #1
	pop {r3, pc}
_021D9E7C:
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD73_021D9E6C

	thumb_func_start MOD73_021D9E80
MOD73_021D9E80: ; 0x021D9E80
	ldr r3, _021D9E88 ; =memset
	mov r1, #0
	mov r2, #0x78
	bx r3
	.align 2, 0
_021D9E88: .word memset
	thumb_func_end MOD73_021D9E80

	thumb_func_start MOD73_021D9E8C
MOD73_021D9E8C: ; 0x021D9E8C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x74]
	cmp r0, #0
	beq _021D9E9A
	bl ErrorHandling
_021D9E9A:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x78
	bl memset
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9E8C

	thumb_func_start MOD73_021D9EA8
MOD73_021D9EA8: ; 0x021D9EA8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp, #8]
	ldr r0, [r0, #0x74]
	add r7, r2, #0
	str r1, [sp, #0xc]
	cmp r0, #0
	beq _021D9EBC
	bl ErrorHandling
_021D9EBC:
	ldr r4, _021D9F5C ; =0x021DBDE4
	ldr r5, [sp, #8]
	mov r6, #0
_021D9EC2:
	ldrb r1, [r4]
	ldr r0, [sp, #0xc]
	add r2, r7, #0
	bl MOD73_021D9258
	add r6, r6, #1
	add r4, r4, #1
	stmia r5!, {r0}
	cmp r6, #6
	blt _021D9EC2
	ldr r4, _021D9F60 ; =0x021DBE04
	ldr r5, [sp, #8]
	mov r6, #0
_021D9EDC:
	ldrb r1, [r4]
	ldr r0, [sp, #0xc]
	add r2, r7, #0
	bl MOD73_021D9288
	str r0, [r5, #0x18]
	add r6, r6, #1
	add r4, r4, #1
	add r5, r5, #4
	cmp r6, #8
	blt _021D9EDC
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, _021D9F64 ; =0x021DBDF4
	ldr r6, _021D9F68 ; =0x021DBDFC
	ldr r4, _021D9F6C ; =0x021DBE0C
	ldr r5, [sp, #8]
	ldr r7, _021D9F70 ; =0x021DBDEC
	str r0, [sp, #0x14]
_021D9F02:
	ldrb r0, [r6]
	str r0, [sp]
	ldr r0, [sp, #0x14]
	ldrb r0, [r0]
	str r0, [sp, #4]
	ldrb r1, [r7]
	ldrb r3, [r4]
	ldr r0, [sp, #0xc]
	lsl r2, r1, #2
	ldr r1, [sp, #8]
	ldr r1, [r1, r2]
	ldr r2, [r5, #0x18]
	bl MOD73_021D92B8
	str r0, [r5, #0x38]
	ldrb r2, [r4]
	mov r1, #0x80
	ldrb r3, [r6]
	sub r1, r1, r2
	mov r2, #0x60
	sub r2, r2, r3
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	bl FUN_02013ED8
	ldr r0, [sp, #0x14]
	add r6, r6, #1
	add r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r4, r4, #1
	add r0, r0, #1
	add r5, r5, #4
	add r7, r7, #1
	str r0, [sp, #0x10]
	cmp r0, #8
	blt _021D9F02
	ldr r0, [sp, #8]
	mov r1, #1
	str r1, [r0, #0x74]
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D9F5C: .word MOD73_021DBDE4
_021D9F60: .word MOD73_021DBE04
_021D9F64: .word MOD73_021DBDF4
_021D9F68: .word MOD73_021DBDFC
_021D9F6C: .word MOD73_021DBE0C
_021D9F70: .word MOD73_021DBDEC
	thumb_func_end MOD73_021D9EA8

	thumb_func_start MOD73_021D9F74
MOD73_021D9F74: ; 0x021D9F74
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x74]
	cmp r0, #1
	beq _021D9F82
	bl ErrorHandling
_021D9F82:
	mov r4, #0
	add r5, r6, #0
_021D9F86:
	ldr r0, [r5, #0x38]
	bl FUN_02013EA8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _021D9F86
	mov r5, #0
	add r4, r6, #0
_021D9F98:
	ldr r0, [r4]
	bl FUN_02013DD4
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #6
	blt _021D9F98
	mov r5, #0
	add r4, r6, #0
_021D9FAA:
	ldr r0, [r4, #0x18]
	bl FUN_02013E44
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, #8
	blt _021D9FAA
	mov r0, #0
	str r0, [r6, #0x74]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9F74

	thumb_func_start MOD73_021D9FC0
MOD73_021D9FC0: ; 0x021D9FC0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #8
	blo _021D9FD0
	bl ErrorHandling
_021D9FD0:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x38]
	add r1, r6, #0
	bl FUN_02013EB0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9FC0

	thumb_func_start MOD73_021D9FE0
MOD73_021D9FE0: ; 0x021D9FE0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #5
	add r5, #0x14
_021D9FEA:
	ldr r0, [r5, #0x38]
	add r1, r6, #0
	bl FUN_02013F2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	ble _021D9FEA
	pop {r4, r5, r6, pc}
	thumb_func_end MOD73_021D9FE0

	thumb_func_start MOD73_021D9FFC
MOD73_021D9FFC: ; 0x021D9FFC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #5
	add r5, #0x14
_021DA006:
	ldr r0, [r5, #0x38]
	add r1, r6, #0
	add r2, r6, #0
	bl FUN_02013EE0
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	ble _021DA006
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021D9FFC

	thumb_func_start MOD73_021DA01C
MOD73_021DA01C: ; 0x021DA01C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #8
	blo _021DA02C
	bl ErrorHandling
_021DA02C:
	lsl r0, r4, #2
	add r0, r5, r0
	lsl r1, r6, #0x18
	ldr r0, [r0, #0x38]
	lsr r1, r1, #0x18
	bl FUN_02013F04
	pop {r4, r5, r6, pc}
	thumb_func_end MOD73_021DA01C

	thumb_func_start MOD73_021DA03C
MOD73_021DA03C: ; 0x021DA03C
	push {r3, lr}
	mov r2, #1
	str r2, [r0, #0x6c]
	mov r1, #0
	str r1, [r0, #0x70]
	lsl r1, r2, #0xc
	ldr r2, _021DA054 ; =0x00000FAE
	add r0, #0x58
	mov r3, #4
	bl MOD73_021D9574
	pop {r3, pc}
	.align 2, 0
_021DA054: .word 0x00000FAE
	thumb_func_end MOD73_021DA03C

	thumb_func_start MOD73_021DA058
MOD73_021DA058: ; 0x021DA058
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x6c]
	add r3, r1, #0
	cmp r0, #0
	beq _021DA06A
	cmp r0, #1
	beq _021DA0A4
	b _021DA0CE
_021DA06A:
	ldr r0, [r5, #0x70]
	cmp r0, #0
	bne _021DA088
	ldr r1, _021DA0D4 ; =0x021DBE14
	lsl r4, r3, #2
	ldr r2, _021DA0D8 ; =0x021DBE20
	ldr r1, [r1, r4]
	ldr r2, [r2, r4]
	ldr r4, _021DA0DC ; =0x021DBDE0
	add r0, r5, #0
	ldrb r3, [r4, r3]
	add r0, #0x58
	bl MOD73_021D9574
	b _021DA09E
_021DA088:
	ldr r1, _021DA0D8 ; =0x021DBE20
	lsl r4, r3, #2
	ldr r2, _021DA0D4 ; =0x021DBE14
	ldr r1, [r1, r4]
	ldr r2, [r2, r4]
	ldr r4, _021DA0DC ; =0x021DBDE0
	add r0, r5, #0
	ldrb r3, [r4, r3]
	add r0, #0x58
	bl MOD73_021D9574
_021DA09E:
	ldr r0, [r5, #0x6c]
	add r0, r0, #1
	str r0, [r5, #0x6c]
_021DA0A4:
	add r0, r5, #0
	add r0, #0x58
	bl MOD73_021D9584
	add r7, r0, #0
	mov r6, #0
	add r4, r5, #0
_021DA0B2:
	ldr r1, [r5, #0x58]
	ldr r0, [r4, #0x38]
	add r2, r1, #0
	bl FUN_02013EE0
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #2
	ble _021DA0B2
	cmp r7, #1
	bne _021DA0D2
	mov r0, #0
	str r0, [r5, #0x6c]
	pop {r3, r4, r5, r6, r7, pc}
_021DA0CE:
	bl ErrorHandling
_021DA0D2:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DA0D4: .word MOD73_021DBE14
_021DA0D8: .word MOD73_021DBE20
_021DA0DC: .word MOD73_021DBDE0
	thumb_func_end MOD73_021DA058

	thumb_func_start MOD73_021DA0E0
MOD73_021DA0E0: ; 0x021DA0E0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r2, #0
	mov r1, #0
	mov r2, #0x20
	add r5, r0, #0
	add r7, r3, #0
	bl memset
	str r4, [r5, #0x14]
	str r6, [r5, #0x18]
	str r7, [r5, #0x1c]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA0E0

	thumb_func_start MOD73_021DA0FC
MOD73_021DA0FC: ; 0x021DA0FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DA10A
	bl ErrorHandling
_021DA10A:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x20
	bl memset
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA0FC

	thumb_func_start MOD73_021DA118
MOD73_021DA118: ; 0x021DA118
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0xc]
	mov r0, #2
	lsl r0, r0, #0x12
	str r0, [sp, #0x14]
	mov r0, #6
	add r6, r2, #0
	lsl r0, r0, #0x10
	ldr r5, [sp, #0xc]
	str r1, [sp, #0x10]
	add r7, r3, #0
	str r0, [sp, #0x18]
	mov r4, #0
	add r6, #0x38
_021DA136:
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, [sp, #0x10]
	str r7, [sp, #8]
	add r1, r6, #0
	mov r2, #0x80
	mov r3, #0x60
	bl MOD73_021D9540
	str r0, [r5, #4]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, #4]
	add r1, r4, #4
	bl FUN_02020130
	ldr r0, [r5, #4]
	add r1, sp, #0x14
	bl FUN_02020044
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021DA136
	ldr r0, [sp, #0xc]
	mov r1, #1
	str r1, [r0]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA118

	thumb_func_start MOD73_021DA178
MOD73_021DA178: ; 0x021DA178
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021DA180:
	ldr r0, [r5, #4]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021DA180
	mov r0, #0
	str r0, [r6]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD73_021DA178

	thumb_func_start MOD73_021DA194
MOD73_021DA194: ; 0x021DA194
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	ldr r7, [r6, #0x14]
	ldr r0, [r6, #0x18]
	add r7, #0x98
	mov r4, #0
	cmp r0, #0
	bls _021DA1D2
	add r5, r6, #0
_021DA1A8:
	ldr r0, [r6, #0x14]
	add r1, r0, r4
	mov r0, #0x13
	lsl r0, r0, #4
	ldrb r1, [r1, r0]
	add r0, r7, r1
	ldrb r1, [r7, r1]
	lsl r1, r1, #0xc
	str r1, [sp]
	ldrb r0, [r0, #4]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r0, [r5, #4]
	bl FUN_02020044
	ldr r0, [r6, #0x18]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blo _021DA1A8
_021DA1D2:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA194

	thumb_func_start MOD73_021DA1D8
MOD73_021DA1D8: ; 0x021DA1D8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x18]
	mov r4, #0
	str r1, [sp]
	cmp r0, #0
	bls _021DA20E
	add r6, r5, #0
_021DA1E8:
	ldr r0, [r5, #0x14]
	add r1, r0, r4
	mov r0, #0x13
	lsl r0, r0, #4
	ldrb r7, [r1, r0]
	ldr r0, [r5, #0x1c]
	bl MOD73_021D910C
	cmp r7, r0
	beq _021DA204
	ldr r0, [r6, #4]
	ldr r1, [sp]
	bl FUN_020200A0
_021DA204:
	ldr r0, [r5, #0x18]
	add r4, r4, #1
	add r6, r6, #4
	cmp r4, r0
	blo _021DA1E8
_021DA20E:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021DA1D8

	thumb_func_start MOD73_021DA210
MOD73_021DA210: ; 0x021DA210
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	add r6, r2, #0
	add r5, r0, #0
	mov r1, #0
	mov r2, #0x34
	add r7, r3, #0
	bl memset
	str r6, [r5, #0x1c]
	ldr r0, [sp, #0x1c]
	str r4, [r5, #0x20]
	str r0, [r5]
	ldr r0, [sp, #0x18]
	str r7, [r5, #0x24]
	str r0, [r5, #0x18]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA210

	thumb_func_start MOD73_021DA234
MOD73_021DA234: ; 0x021DA234
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _021DA242
	bl ErrorHandling
_021DA242:
	add r0, r4, #0
	bl MOD73_021DA4AC
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x34
	bl memset
	pop {r4, pc}
	thumb_func_end MOD73_021DA234

	thumb_func_start MOD73_021DA254
MOD73_021DA254: ; 0x021DA254
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x28]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, #0
	beq _021DA266
	bl ErrorHandling
_021DA266:
	add r0, r5, #0
	add r1, r6, #0
	str r4, [r5, #4]
	bl MOD73_021DA2AC
	add r0, r5, #0
	add r1, r6, #0
	bl MOD73_021DA374
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #1
	str r0, [r5, #0x28]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA254

	thumb_func_start MOD73_021DA290
MOD73_021DA290: ; 0x021DA290
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	cmp r0, #1
	beq _021DA29E
	bl ErrorHandling
_021DA29E:
	add r0, r4, #0
	bl MOD73_021DA354
	mov r0, #0
	str r0, [r4, #0x28]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA290

	thumb_func_start MOD73_021DA2AC
MOD73_021DA2AC: ; 0x021DA2AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	ldr r0, [r7, #0x18]
	str r1, [sp, #0x14]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	add r0, r1, #0
	str r0, [sp, #4]
	ldr r0, [r7, #4]
	mov r1, #2
	mov r2, #1
	mov r3, #0
	bl FUN_0200CD68
	ldr r2, [sp, #0x14]
	mov r0, #0
	mov r1, #0x40
	bl FUN_02002EEC
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x14]
	mov r1, #2
	str r0, [sp, #4]
	ldr r0, [r7, #4]
	mov r2, #0x1f
	mov r3, #1
	bl FUN_0200CB00
	ldr r2, [sp, #0x14]
	mov r0, #0
	mov r1, #0x60
	bl FUN_02002ED0
	ldr r5, _021DA350 ; =0x021DBF80
	mov r6, #0
	add r4, r7, #0
_021DA2FA:
	ldr r0, [sp, #0x14]
	mov r1, #1
	bl FUN_02018FF4
	str r0, [r4, #8]
	ldrh r0, [r5, #2]
	mov r2, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrh r0, [r5, #4]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldrh r0, [r5, #6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldrh r0, [r5, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xc]
	ldrh r0, [r5, #0xa]
	str r0, [sp, #0x10]
	ldrh r3, [r5]
	ldr r0, [r7, #4]
	ldr r1, [r4, #8]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	ldr r0, [r4, #8]
	mov r1, #0
	bl FUN_02019620
	add r6, r6, #1
	add r4, r4, #4
	add r5, #0xc
	cmp r6, #4
	blt _021DA2FA
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DA350: .word MOD73_021DBF80
	thumb_func_end MOD73_021DA2AC

	thumb_func_start MOD73_021DA354
MOD73_021DA354: ; 0x021DA354
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r4, #0
	mov r6, #1
_021DA35C:
	ldr r0, [r5, #8]
	bl FUN_02019178
	ldr r0, [r5, #8]
	add r1, r6, #0
	bl FUN_020191A4
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _021DA35C
	pop {r4, r5, r6, pc}
	thumb_func_end MOD73_021DA354

	thumb_func_start MOD73_021DA374
MOD73_021DA374: ; 0x021DA374
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x20
	add r5, r1, #0
	str r0, [sp]
	mov r0, #0x7a
	mov r1, #6
	mov r2, #0
	mov r3, #0x80
	str r5, [sp, #4]
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x7a
	mov r1, #5
	mov r3, #1
	bl FUN_0200687C
	str r5, [sp]
	mov r0, #0x7a
	mov r1, #7
	mov r2, #0
	add r3, sp, #0x10
	bl FUN_02006BDC
	ldr r2, [sp, #0x10]
	mov r3, #0
	str r3, [sp]
	add r5, r0, #0
	ldrh r0, [r2]
	mov r1, #1
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldrh r0, [r2, #2]
	add r2, #0xc
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_02018148
	ldr r1, [sp, #0x10]
	mov r2, #0
	ldrh r0, [r1]
	add r3, r2, #0
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp]
	ldrh r0, [r1, #2]
	mov r1, #1
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r4, #4]
	bl FUN_020186B4
	add r0, r5, #0
	bl FreeToHeap
	ldr r0, [r4, #4]
	mov r1, #1
	bl FUN_0201AC68
	add sp, #0x14
	pop {r4, r5, pc}
	thumb_func_end MOD73_021DA374

	thumb_func_start MOD73_021DA408
MOD73_021DA408: ; 0x021DA408
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x30]
	add r0, r0, #1
	str r0, [r4, #0x30]
	cmp r0, #0x1e
	blt _021DA432
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x2c]
_021DA432:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021DA408

	thumb_func_start MOD73_021DA434
MOD73_021DA434: ; 0x021DA434
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x2c]
	add r4, r1, #0
	cmp r0, #0
	beq _021DA446
	bl ErrorHandling
_021DA446:
	mov r2, #1
	ldr r0, _021DA494 ; =MOD73_021DA408
	add r1, r5, #0
	lsl r2, r2, #0xa
	bl FUN_0200CA44
	str r0, [r5, #0x2c]
	mov r1, #0
	str r1, [r5, #0x30]
	ldr r0, [r5, #8]
	bl FUN_02019620
	mov r3, #0
	str r3, [sp]
	ldr r0, _021DA498 ; =0x0001020F
	str r3, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r6, [r5, #0x1c]
	lsl r2, r4, #2
	add r2, r6, r2
	ldr r0, [r5, #8]
	ldr r2, [r2, #0x38]
	mov r1, #1
	bl FUN_0201BDE0
	ldr r0, [r5, #8]
	bl FUN_020191D0
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #1
	bl FUN_0201E6E4
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DA494: .word MOD73_021DA408
_021DA498: .word 0x0001020F
	thumb_func_end MOD73_021DA434

	thumb_func_start MOD73_021DA49C
MOD73_021DA49C: ; 0x021DA49C
	ldr r0, [r0, #0x2c]
	cmp r0, #0
	bne _021DA4A6
	mov r0, #1
	bx lr
_021DA4A6:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD73_021DA49C

	thumb_func_start MOD73_021DA4AC
MOD73_021DA4AC: ; 0x021DA4AC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _021DA4D0
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	ldr r0, [r4, #0x2c]
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #0x2c]
_021DA4D0:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA4AC

	thumb_func_start MOD73_021DA4D4
MOD73_021DA4D4: ; 0x021DA4D4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02018744
	ldr r0, [r4, #0xc]
	mov r1, #0xf
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	ldr r0, _021DA54C ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #0x34]
	mov r3, #0x38
	bl FUN_0201BDE0
	ldr r0, [r4, #0xc]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #1
	bl FUN_0200CCA4
	ldr r0, [r4, #0x10]
	mov r1, #0xf
	bl FUN_02019620
	mov r1, #0
	str r1, [sp]
	ldr r0, _021DA54C ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x10]
	ldr r2, [r2, #0x64]
	add r3, r1, #0
	bl FUN_0201BDE0
	ldr r0, [r4, #0x10]
	mov r1, #0
	mov r2, #0x1f
	mov r3, #1
	bl FUN_0200CCA4
	ldr r0, [r4, #0xc]
	bl FUN_02019220
	ldr r0, [r4, #0x10]
	bl FUN_02019220
	add sp, #0x10
	pop {r4, pc}
	nop
_021DA54C: .word 0x0001020F
	thumb_func_end MOD73_021DA4D4

	thumb_func_start MOD73_021DA550
MOD73_021DA550: ; 0x021DA550
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #0x18
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA6B8 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #0x4c]
	add r3, r1, #0
	bl FUN_0201BDE0
	mov r3, #2
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r2, #0x66
	ldrb r2, [r2]
	ldr r0, [r0, #4]
	mov r1, #0
	bl FUN_0200AD38
	mov r3, #2
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r2, #0x67
	ldrb r2, [r2]
	ldr r0, [r0, #4]
	bl FUN_0200AD38
	mov r1, #2
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r2, #0x68
	ldrb r2, [r2]
	ldr r0, [r0, #4]
	add r3, r1, #0
	bl FUN_0200AD38
	ldr r2, [r4, #0x1c]
	ldr r0, [r2, #4]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0x50]
	bl StringExpandPlaceholders
	mov r0, #0x18
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA6B8 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #8]
	mov r3, #0xa0
	bl FUN_0201BDE0
	mov r0, #0x30
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA6B8 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #0x54]
	add r3, r1, #0
	bl FUN_0201BDE0
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x24]
	ldr r0, [r0, #4]
	ldr r2, [r2, #0x58]
	mov r3, #4
	bl FUN_0200AD38
	ldr r0, [r4, #0x24]
	ldr r0, [r0, #0x58]
	cmp r0, #1
	bne _021DA618
	mov r2, #3
	b _021DA61A
_021DA618:
	mov r2, #5
_021DA61A:
	ldr r3, [r4, #0x1c]
	lsl r2, r2, #2
	add r2, r3, r2
	ldr r0, [r3, #4]
	ldr r1, [r3, #8]
	ldr r2, [r2, #0x4c]
	bl StringExpandPlaceholders
	mov r0, #0x30
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA6B8 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #8]
	mov r3, #0xa0
	bl FUN_0201BDE0
	mov r0, #0x44
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA6B8 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #0x5c]
	add r3, r1, #0
	bl FUN_0201BDE0
	mov r1, #0
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x24]
	ldr r0, [r0, #4]
	ldr r2, [r2, #0x5c]
	mov r3, #4
	bl FUN_0200AD38
	ldr r0, [r4, #0x24]
	ldr r0, [r0, #0x5c]
	cmp r0, #1
	bne _021DA680
	mov r2, #3
	b _021DA682
_021DA680:
	mov r2, #5
_021DA682:
	ldr r3, [r4, #0x1c]
	lsl r2, r2, #2
	add r2, r3, r2
	ldr r0, [r3, #4]
	ldr r1, [r3, #8]
	ldr r2, [r2, #0x4c]
	bl StringExpandPlaceholders
	mov r0, #0x44
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA6B8 ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #8]
	mov r3, #0xa0
	bl FUN_0201BDE0
	ldr r0, [r4, #0xc]
	bl FUN_02019220
	add sp, #0x10
	pop {r4, pc}
	nop
_021DA6B8: .word 0x0001020F
	thumb_func_end MOD73_021DA550

	thumb_func_start MOD73_021DA6BC
MOD73_021DA6BC: ; 0x021DA6BC
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r2, #0x64
	ldrb r2, [r2]
	ldr r0, [r0, #4]
	mov r1, #3
	bl FUN_0200B628
	mov r3, #2
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #0x1c]
	add r2, #0x65
	ldrb r2, [r2]
	ldr r0, [r0, #4]
	bl FUN_0200AD38
	mov r1, #2
	str r1, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x20]
	ldr r0, [r0, #4]
	add r3, r1, #0
	bl FUN_0200AD38
	ldr r2, [r4, #0x1c]
	ldr r0, [r2, #4]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0x68]
	bl StringExpandPlaceholders
	mov r0, #0x18
	str r0, [sp]
	mov r1, #0
	ldr r0, _021DA72C ; =0x0001020F
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x10]
	ldr r2, [r2, #8]
	mov r3, #0x10
	bl FUN_0201BDE0
	ldr r0, [r4, #0x10]
	bl FUN_02019220
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021DA72C: .word 0x0001020F
	thumb_func_end MOD73_021DA6BC

	thumb_func_start MOD73_021DA730
MOD73_021DA730: ; 0x021DA730
	push {r3, lr}
	cmp r1, #0
	beq _021DA740
	cmp r1, #1
	beq _021DA746
	cmp r1, #2
	beq _021DA74C
	pop {r3, pc}
_021DA740:
	bl MOD73_021DA4D4
	pop {r3, pc}
_021DA746:
	bl MOD73_021DA550
	pop {r3, pc}
_021DA74C:
	bl MOD73_021DA6BC
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA730

	thumb_func_start MOD73_021DA754
MOD73_021DA754: ; 0x021DA754
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	mov r1, #2
	bl FUN_02018744
	ldr r0, [r4, #0xc]
	bl FUN_02019570
	ldr r0, [r4, #0x10]
	bl FUN_02019570
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA754

	thumb_func_start MOD73_021DA770
MOD73_021DA770: ; 0x021DA770
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	add r6, r1, #0
	mov r1, #0xf
	bl FUN_02019620
	cmp r6, #6
	bhi _021DA7EC
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021DA790: ; jump table
	.short _021DA79E - _021DA790 - 2 ; case 0
	.short _021DA7CA - _021DA790 - 2 ; case 1
	.short _021DA7D0 - _021DA790 - 2 ; case 2
	.short _021DA7D6 - _021DA790 - 2 ; case 3
	.short _021DA7DC - _021DA790 - 2 ; case 4
	.short _021DA7E2 - _021DA790 - 2 ; case 5
	.short _021DA7E8 - _021DA790 - 2 ; case 6
_021DA79E:
	mov r3, #0x51
	ldr r2, [r4, #0x24]
	lsl r3, r3, #2
	ldrb r5, [r2, r3]
	ldr r0, [r4, #0x1c]
	sub r3, #0x10
	lsl r5, r5, #2
	add r2, r2, r5
	ldr r0, [r0, #4]
	ldr r2, [r2, r3]
	mov r1, #0
	bl FUN_0200ABC0
	ldr r2, [r4, #0x1c]
	ldr r0, [r2, #4]
	ldr r1, [r2, #8]
	ldr r2, [r2, #0x18]
	bl StringExpandPlaceholders
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #8]
	b _021DA7EC
_021DA7CA:
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #0x1c]
	b _021DA7EC
_021DA7D0:
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #0x28]
	b _021DA7EC
_021DA7D6:
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #0x24]
	b _021DA7EC
_021DA7DC:
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #0x20]
	b _021DA7EC
_021DA7E2:
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #0x2c]
	b _021DA7EC
_021DA7E8:
	ldr r0, [r4, #0x1c]
	ldr r5, [r0, #0xc]
_021DA7EC:
	mov r3, #0
	str r3, [sp]
	ldr r0, _021DA818 ; =0x0001020F
	str r3, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	ldr r0, [r4, #0x14]
	mov r1, #1
	add r2, r5, #0
	bl FUN_0201BDE0
	mov r1, #0
	ldr r0, [r4, #0x14]
	mov r2, #1
	add r3, r1, #0
	bl FUN_0200D0BC
	ldr r0, [r4, #0x14]
	bl FUN_02019220
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DA818: .word 0x0001020F
	thumb_func_end MOD73_021DA770

	thumb_func_start MOD73_021DA81C
MOD73_021DA81C: ; 0x021DA81C
	ldr r3, _021DA824 ; =memset
	mov r1, #0
	ldr r2, _021DA828 ; =0x00000414
	bx r3
	.align 2, 0
_021DA824: .word memset
_021DA828: .word 0x00000414
	thumb_func_end MOD73_021DA81C

	thumb_func_start MOD73_021DA82C
MOD73_021DA82C: ; 0x021DA82C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DA83A
	bl ErrorHandling
_021DA83A:
	ldr r2, _021DA848 ; =0x00000414
	add r0, r4, #0
	mov r1, #0
	bl memset
	pop {r4, pc}
	nop
_021DA848: .word 0x00000414
	thumb_func_end MOD73_021DA82C

	thumb_func_start MOD73_021DA84C
MOD73_021DA84C: ; 0x021DA84C
	str r1, [r0, #4]
	str r2, [r0, #8]
	str r3, [r0, #0xc]
	mov r1, #1
	str r1, [r0]
	bx lr
	thumb_func_end MOD73_021DA84C

	thumb_func_start MOD73_021DA858
MOD73_021DA858: ; 0x021DA858
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r7, #0
	mov r6, #0
	add r4, r7, #0
	add r5, #0x10
_021DA864:
	add r0, r4, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	beq _021DA874
	add r0, r5, #0
	bl MOD73_021DAB30
_021DA874:
	add r6, r6, #1
	add r4, #0x80
	add r5, #0x80
	cmp r6, #8
	blt _021DA864
	mov r0, #0
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021DA858

	thumb_func_start MOD73_021DA884
MOD73_021DA884: ; 0x021DA884
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r5, #0
	add r7, r1, #0
	mov r6, #0
	add r4, #0x10
_021DA890:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	beq _021DA8AE
	add r0, r4, #0
	bl MOD73_021DAB50
	ldr r0, [r5, #0x20]
	cmp r0, #0
	beq _021DA8AE
	add r0, r4, #0
	add r1, r7, #0
	bl MOD73_021DABD0
_021DA8AE:
	add r6, r6, #1
	add r5, #0x80
	add r4, #0x80
	cmp r6, #8
	blt _021DA890
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DA884

	thumb_func_start MOD73_021DA8BC
MOD73_021DA8BC: ; 0x021DA8BC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xb8
	add r5, r0, #0
	lsl r0, r1, #1
	add r0, r1, r0
	add r1, r2, r0
	mov r0, #0x1c
	add r2, r1, #0
	mul r2, r0
	ldr r0, _021DAA9C ; =0x021DBE7C
	add r3, r0, r2
	ldmia r3!, {r0, r1}
	add r2, sp, #0x9c
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	add r0, r5, #0
	bl MOD73_021DAAD0
	str r0, [sp, #0x60]
	cmp r0, #0
	bne _021DA906
	add r0, r5, #0
	bl MOD73_021DAAF4
	str r0, [sp, #0x60]
	cmp r0, #0
	bne _021DA900
	bl ErrorHandling
_021DA900:
	ldr r0, [sp, #0x60]
	bl MOD73_021DAB30
_021DA906:
	bl MTRandom
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	bl MTRandom
	add r1, sp, #0x9c
	ldrb r1, [r1, #0x11]
	bl _u32_div_f
	add r0, sp, #0x9c
	ldrb r0, [r0, #0x10]
	add r4, r0, r1
	bl MTRandom
	add r1, sp, #0x9c
	ldrb r1, [r1, #0x13]
	bl _u32_div_f
	add r0, sp, #0x9c
	ldrb r0, [r0, #0x12]
	add r0, r0, r1
	add r0, r0, r4
	asr r1, r6, #4
	lsl r2, r1, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x6c]
	asr r0, r0, #0x1f
	lsl r3, r2, #1
	ldr r1, _021DAAA0 ; =0x020FFA38
	str r0, [sp, #0x70]
	ldr r0, [sp, #0xa8]
	ldrsh r6, [r1, r3]
	lsl r3, r4, #0xc
	add r2, r2, #1
	str r3, [sp, #0x64]
	asr r3, r3, #0x1f
	lsl r2, r2, #1
	str r0, [sp, #0x74]
	asr r0, r0, #0x1f
	str r3, [sp, #0x68]
	ldrsh r4, [r1, r2]
	str r0, [sp, #0x78]
	bl MTRandom
	ldr r1, [sp, #0xa0]
	bl _u32_div_f
	ldr r0, [sp, #0x9c]
	ldr r2, [sp, #0x64]
	add r0, r0, r1
	str r0, [sp, #0x5c]
	asr r0, r6, #0x1f
	str r0, [sp, #0x7c]
	ldr r1, [sp, #0x7c]
	ldr r3, [sp, #0x68]
	add r0, r6, #0
	asr r7, r4, #0x1f
	bl _ll_mul
	str r1, [sp, #0x58]
	str r0, [sp, #0x80]
	ldr r1, [sp, #0x7c]
	ldr r2, [sp, #0x6c]
	ldr r3, [sp, #0x70]
	add r0, r6, #0
	bl _ll_mul
	str r1, [sp, #0x50]
	str r0, [sp, #0x84]
	ldr r1, [sp, #0x7c]
	ldr r2, [sp, #0x74]
	ldr r3, [sp, #0x78]
	add r0, r6, #0
	bl _ll_mul
	str r0, [sp, #0x88]
	str r1, [sp, #0x98]
	ldr r2, [sp, #0x64]
	ldr r3, [sp, #0x68]
	add r0, r4, #0
	add r1, r7, #0
	bl _ll_mul
	str r0, [sp, #0x8c]
	str r1, [sp, #0x48]
	ldr r2, [sp, #0x6c]
	ldr r3, [sp, #0x70]
	add r0, r4, #0
	add r1, r7, #0
	bl _ll_mul
	str r0, [sp, #0x90]
	str r1, [sp, #0x40]
	ldr r2, [sp, #0x74]
	ldr r3, [sp, #0x78]
	add r0, r4, #0
	add r1, r7, #0
	bl _ll_mul
	add r2, r0, #0
	mov r4, #2
	ldr r0, [sp, #0x88]
	ldr r3, [sp, #0x98]
	mov r6, #0
	lsl r4, r4, #0xa
	add r0, r0, r4
	adc r3, r6
	str r3, [sp, #0x98]
	lsl r3, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r3
	str r0, [sp]
	ldr r0, [sp, #0x8c]
	ldr r3, [sp, #0x48]
	add r0, r0, r4
	adc r3, r6
	str r3, [sp, #0x48]
	mov r7, #6
	lsl r3, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r3
	lsl r7, r7, #0x10
	add r0, r0, r7
	str r0, [sp, #4]
	ldr r0, [sp, #0x90]
	ldr r3, [sp, #0x40]
	add r0, r0, r4
	adc r3, r6
	str r3, [sp, #0x40]
	lsl r3, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r3
	add r0, r0, r7
	add r2, r2, r4
	adc r1, r6
	str r0, [sp, #8]
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [sp, #0xc]
	ldr r0, _021DAAA4 ; =0x0000019A
	add r2, sp, #0x9c
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x5c]
	mov r1, #0x38
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xa4]
	str r0, [sp, #0x18]
	ldrb r0, [r2, #0x18]
	str r0, [sp, #0x1c]
	ldrb r0, [r2, #0x14]
	str r0, [sp, #0x20]
	ldrb r3, [r2, #0x15]
	ldr r0, [r5, #8]
	mul r1, r3
	add r0, r0, r1
	str r0, [sp, #0x24]
	ldrb r0, [r2, #0x16]
	str r0, [sp, #0x28]
	ldr r0, [r5, #4]
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0xc]
	str r0, [sp, #0x30]
	ldrb r0, [r2, #0x19]
	str r0, [sp, #0x34]
	ldrb r0, [r2, #0x1a]
	str r0, [sp, #0x38]
	ldrb r1, [r2, #0x17]
	ldr r2, [sp, #0x80]
	ldr r0, [sp, #0x60]
	add r3, r2, r4
	ldr r2, [sp, #0x58]
	adc r2, r6
	str r2, [sp, #0x58]
	lsl r2, r2, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	lsl r2, r4, #8
	add r2, r3, r2
	ldr r3, [sp, #0x84]
	add r7, r3, r4
	ldr r3, [sp, #0x50]
	adc r3, r6
	str r3, [sp, #0x50]
	lsl r3, r3, #0x14
	lsr r6, r7, #0xc
	orr r6, r3
	lsl r3, r4, #8
	add r3, r6, r3
	bl MOD73_021DAC9C
	mov r1, #0x41
	lsl r1, r1, #4
	ldr r2, [r5, r1]
	ldr r0, [sp, #0x60]
	str r2, [r0, #0x7c]
	ldr r0, [r5, r1]
	add r0, r0, #1
	str r0, [r5, r1]
	add sp, #0xb8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DAA9C: .word MOD73_021DBE7C
_021DAAA0: .word 0x020FFA38
_021DAAA4: .word 0x0000019A
	thumb_func_end MOD73_021DA8BC

	thumb_func_start MOD73_021DAAA8
MOD73_021DAAA8: ; 0x021DAAA8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r5, #0
	mov r6, #0
	add r4, #0x10
_021DAAB2:
	add r0, r5, #0
	add r0, #0x88
	ldr r0, [r0]
	cmp r0, #0
	beq _021DAAC2
	add r0, r4, #0
	bl MOD73_021DAD44
_021DAAC2:
	add r6, r6, #1
	add r5, #0x80
	add r4, #0x80
	cmp r6, #8
	blt _021DAAB2
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAAA8

	thumb_func_start MOD73_021DAAD0
MOD73_021DAAD0: ; 0x021DAAD0
	mov r2, #0
	add r3, r0, #0
_021DAAD4:
	add r1, r3, #0
	add r1, #0x88
	ldr r1, [r1]
	cmp r1, #0
	bne _021DAAE6
	add r0, #0x10
	lsl r1, r2, #7
	add r0, r0, r1
	bx lr
_021DAAE6:
	add r2, r2, #1
	add r3, #0x80
	cmp r2, #8
	blt _021DAAD4
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD73_021DAAD0

	thumb_func_start MOD73_021DAAF4
MOD73_021DAAF4: ; 0x021DAAF4
	push {r4, r5}
	mov r2, #0
	add r3, r0, #0
	add r1, r2, #0
	add r3, #0x10
_021DAAFE:
	add r4, r0, #0
	add r4, #0x88
	ldr r4, [r4]
	cmp r4, #0
	beq _021DAB1E
	cmp r2, #0
	bne _021DAB10
	add r2, r3, #0
	b _021DAB1E
_021DAB10:
	add r4, r0, #0
	add r4, #0x8c
	ldr r5, [r2, #0x7c]
	ldr r4, [r4]
	cmp r5, r4
	ble _021DAB1E
	add r2, r3, #0
_021DAB1E:
	add r1, r1, #1
	add r0, #0x80
	add r3, #0x80
	cmp r1, #8
	blt _021DAAFE
	add r0, r2, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
	thumb_func_end MOD73_021DAAF4

	thumb_func_start MOD73_021DAB30
MOD73_021DAB30: ; 0x021DAB30
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x78]
	cmp r0, #0
	bne _021DAB3E
	bl ErrorHandling
_021DAB3E:
	ldr r0, [r4, #0x78]
	bl FUN_0201FFC8
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x80
	bl memset
	pop {r4, pc}
	thumb_func_end MOD73_021DAB30

	thumb_func_start MOD73_021DAB50
MOD73_021DAB50: ; 0x021DAB50
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021DABA2
	add r0, r4, #0
	add r0, #0x30
	bl MOD73_021D962C
	str r0, [r4, #4]
	add r0, r4, #0
	add r0, #0x48
	bl MOD73_021D962C
	add r0, r4, #0
	add r0, #0x60
	bl MOD73_021D962C
	ldr r0, [r4, #0x30]
	add r1, r4, #0
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x48]
	add r1, #0x14
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x78]
	bl FUN_02020044
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DABA2
	ldr r0, [r4, #0x60]
	add r1, r4, #0
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x60]
	add r1, #0x20
	str r0, [r4, #0x24]
	ldr r0, [r4, #0x60]
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x78]
	bl FUN_02020064
_021DABA2:
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021DABB6
	ldr r0, [r4, #0x78]
	bl FUN_02020388
	cmp r0, #0
	bne _021DABB6
	mov r0, #1
	str r0, [r4, #8]
_021DABB6:
	ldr r0, [r4]
	cmp r0, #0
	bne _021DABCE
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _021DABCE
	ldr r0, [r4, #8]
	cmp r0, #1
	bne _021DABCE
	add r0, r4, #0
	bl MOD73_021DAB30
_021DABCE:
	pop {r4, pc}
	thumb_func_end MOD73_021DAB50

	thumb_func_start MOD73_021DABD0
MOD73_021DABD0: ; 0x021DABD0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [r5, #4]
	cmp r0, #1
	bne _021DAC94
	ldr r0, [r5, #8]
	cmp r0, #1
	bne _021DAC94
	add r0, r1, #0
	add r0, #0xa4
	ldrb r0, [r0]
	ldr r2, [r5, #0x2c]
	cmp r0, #0
	bne _021DABF6
	add r1, #0xa2
	ldrh r0, [r1]
	add r0, r2, r0
	b _021DABFC
_021DABF6:
	add r1, #0xa2
	ldrh r0, [r1]
	sub r0, r2, r0
_021DABFC:
	str r0, [r5, #0x2c]
	mov r0, #2
	ldr r1, [r5, #0x14]
	lsl r0, r0, #0x12
	sub r4, r1, r0
	mov r0, #6
	mov r2, #0
	ldr r1, [r5, #0x18]
	lsl r0, r0, #0x10
	sub r6, r1, r0
	asr r0, r4, #0xc
	asr r1, r6, #0xc
	add r3, r2, #0
	bl FUN_0201CBEC
	add r7, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl FX_Atan2
	lsl r6, r7, #0xc
	ldr r1, [r5, #0x2c]
	asr r7, r6, #0x1f
	add r0, r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r4, r0, #1
	add r0, r4, #1
	lsl r1, r0, #1
	ldr r0, _021DAC98 ; =0x020FFA38
	add r2, r6, #0
	ldrsh r0, [r0, r1]
	add r3, r7, #0
	asr r1, r0, #0x1f
	bl _ll_mul
	add r2, r0, #0
	mov r0, #2
	mov r3, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [sp]
	ldr r0, _021DAC98 ; =0x020FFA38
	lsl r1, r4, #1
	ldrsh r0, [r0, r1]
	add r2, r6, #0
	add r3, r7, #0
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	ldr r3, [sp]
	lsl r1, r2, #8
	add r1, r3, r1
	str r1, [sp]
	mov r1, #6
	lsl r1, r1, #0x10
	str r0, [sp, #4]
	add r0, r0, r1
	str r0, [sp, #4]
	ldr r0, [r5, #0x78]
	add r1, sp, #0
	bl FUN_02020044
_021DAC94:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_021DAC98: .word 0x020FFA38
	thumb_func_end MOD73_021DABD0

	thumb_func_start MOD73_021DAC9C
MOD73_021DAC9C: ; 0x021DAC9C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [sp, #0x40]
	str r1, [r5]
	add r4, r2, #0
	str r0, [sp]
	add r0, r5, #0
	add r2, r3, #0
	ldr r3, [sp, #0x20]
	add r0, #0x30
	add r1, r4, #0
	ldr r6, [sp, #0x30]
	bl MOD73_021D95CC
	ldr r0, [sp, #0x40]
	ldr r1, [sp, #0x24]
	str r0, [sp]
	add r0, r5, #0
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	add r0, #0x48
	bl MOD73_021D95CC
	ldr r0, [sp, #0x40]
	ldr r2, [sp, #0x34]
	str r0, [sp]
	add r0, r5, #0
	ldr r3, [sp, #0x38]
	add r0, #0x60
	add r1, r6, #0
	bl MOD73_021D95CC
	ldr r3, [sp, #0x24]
	str r4, [r5, #0x14]
	str r3, [r5, #0x18]
	str r6, [r5, #0x20]
	str r6, [r5, #0x24]
	ldr r0, [sp, #0x3c]
	str r6, [r5, #0x28]
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x54]
	ldr r1, [sp, #0x44]
	str r0, [r5, #0x10]
	mov r0, #0
	str r0, [sp]
	add r0, sp, #0x58
	ldrb r0, [r0]
	add r2, r4, #0
	str r0, [sp, #4]
	ldr r0, [sp, #0x50]
	str r0, [sp, #8]
	ldr r0, [sp, #0x4c]
	bl MOD73_021D9540
	str r0, [r5, #0x78]
	cmp r0, #0
	bne _021DAD14
	bl ErrorHandling
_021DAD14:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _021DAD26
	add r1, r5, #0
	ldr r0, [r5, #0x78]
	add r1, #0x20
	mov r2, #2
	bl FUN_02020074
_021DAD26:
	ldr r0, [r5, #0x78]
	ldr r1, [sp, #0x48]
	bl FUN_02020130
	ldr r0, [r5, #0x78]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r5, #0x78]
	mov r1, #2
	bl FUN_02020238
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAC9C

	thumb_func_start MOD73_021DAD44
MOD73_021DAD44: ; 0x021DAD44
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	bne _021DAD72
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	ldr r1, [r4, #0x60]
	add r0, #0x60
	mov r2, #0xcd
	mov r3, #0
	bl MOD73_021D95CC
	mov r0, #0
	str r0, [r4]
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x78]
	mov r1, #2
	bl FUN_020200EC
_021DAD72:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAD44

	thumb_func_start MOD73_021DAD78
MOD73_021DAD78: ; 0x021DAD78
	ldr r3, _021DAD80 ; =memset
	mov r1, #0
	mov r2, #0x80
	bx r3
	.align 2, 0
_021DAD80: .word memset
	thumb_func_end MOD73_021DAD78

	thumb_func_start MOD73_021DAD84
MOD73_021DAD84: ; 0x021DAD84
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x7c]
	cmp r0, #0
	beq _021DAD92
	bl ErrorHandling
_021DAD92:
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x80
	bl memset
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAD84

	thumb_func_start MOD73_021DADA0
MOD73_021DADA0: ; 0x021DADA0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	ldr r0, [r6, #0x7c]
	add r7, r1, #0
	str r2, [sp, #0x18]
	cmp r0, #0
	beq _021DADB4
	bl ErrorHandling
_021DADB4:
	str r7, [r6]
	mov r0, #2
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	mov r0, #0x1f
	str r0, [sp, #8]
	mov r0, #0x1e
	str r0, [sp, #0xc]
	ldr r0, _021DAE20 ; =0x00001B58
	add r1, r6, #4
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	mov r2, #0x7a
	str r0, [sp, #0x14]
	add r0, r7, #0
	mov r3, #0x21
	bl MOD73_021D9340
	mov r4, #0
	add r5, r6, #0
_021DADDE:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	mov r2, #2
	mov r3, #6
	str r0, [sp, #8]
	add r0, r7, #0
	add r1, r6, #4
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD73_021D9540
	str r0, [r5, #0x3c]
	cmp r4, #2
	blt _021DAE06
	ldr r0, [r5, #0x3c]
	mov r1, #1
	bl FUN_02020130
_021DAE06:
	ldr r0, [r5, #0x3c]
	mov r1, #0
	bl FUN_020200A0
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _021DADDE
	mov r0, #1
	str r0, [r6, #0x7c]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021DAE20: .word 0x00001B58
	thumb_func_end MOD73_021DADA0

	thumb_func_start MOD73_021DAE24
MOD73_021DAE24: ; 0x021DAE24
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x7c]
	cmp r0, #1
	beq _021DAE32
	bl ErrorHandling
_021DAE32:
	mov r4, #0
	add r5, r6, #0
_021DAE36:
	ldr r0, [r5, #0x3c]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _021DAE36
	ldr r0, [r6]
	add r1, r6, #4
	bl MOD73_021D94F4
	mov r0, #0
	str r0, [r6, #0x7c]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAE24

	thumb_func_start MOD73_021DAE54
MOD73_021DAE54: ; 0x021DAE54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0x3c
_021DAE5C:
	cmp r4, #2
	beq _021DAE64
	cmp r4, #0
	bne _021DAE6C
_021DAE64:
	add r0, r5, #0
	bl MOD73_021DAEFC
	b _021DAE72
_021DAE6C:
	add r0, r5, #0
	bl MOD73_021DAF34
_021DAE72:
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #4
	blt _021DAE5C
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021DAE54

	thumb_func_start MOD73_021DAE7C
MOD73_021DAE7C: ; 0x021DAE7C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blt _021DAE8A
	bl ErrorHandling
_021DAE8A:
	cmp r5, #2
	beq _021DAE92
	cmp r5, #0
	bne _021DAE9E
_021DAE92:
	add r4, #0x3c
	lsl r0, r5, #4
	add r0, r4, r0
	bl MOD73_021DAEEC
	pop {r3, r4, r5, pc}
_021DAE9E:
	add r4, #0x3c
	lsl r0, r5, #4
	add r0, r4, r0
	bl MOD73_021DAF28
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAE7C

	thumb_func_start MOD73_021DAEAC
MOD73_021DAEAC: ; 0x021DAEAC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blt _021DAEBA
	bl ErrorHandling
_021DAEBA:
	lsl r0, r5, #4
	mov r1, #0
	add r0, r4, r0
	str r1, [r0, #0x48]
	ldr r0, [r0, #0x3c]
	bl FUN_020200A0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAEAC

	thumb_func_start MOD73_021DAECC
MOD73_021DAECC: ; 0x021DAECC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blt _021DAEDA
	bl ErrorHandling
_021DAEDA:
	lsl r0, r5, #4
	add r0, r4, r0
	ldr r0, [r0, #0x48]
	cmp r0, #0
	bne _021DAEE8
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DAEE8:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021DAECC

	thumb_func_start MOD73_021DAEEC
MOD73_021DAEEC: ; 0x021DAEEC
	mov r1, #0
	str r1, [r0, #4]
	mov r1, #3
	str r1, [r0, #8]
	mov r1, #1
	str r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD73_021DAEEC

	thumb_func_start MOD73_021DAEFC
MOD73_021DAEFC: ; 0x021DAEFC
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	cmp r1, #0
	beq _021DAF24
	bl MOD73_021DAF34
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021DAF24
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0
	bgt _021DAF24
	mov r1, #0
	str r1, [r4, #0xc]
	ldr r0, [r4]
	bl FUN_020200A0
_021DAF24:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAEFC

	thumb_func_start MOD73_021DAF28
MOD73_021DAF28: ; 0x021DAF28
	mov r1, #0
	str r1, [r0, #4]
	mov r1, #1
	str r1, [r0, #0xc]
	bx lr
	.align 2, 0
	thumb_func_end MOD73_021DAF28

	thumb_func_start MOD73_021DAF34
MOD73_021DAF34: ; 0x021DAF34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _021DAF6C
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021DAF4E
	ldr r0, [r4]
	mov r1, #1
	bl FUN_020200A0
	b _021DAF66
_021DAF4E:
	cmp r0, #8
	bne _021DAF5C
	ldr r0, [r4]
	mov r1, #0
	bl FUN_020200A0
	b _021DAF66
_021DAF5C:
	cmp r0, #0x10
	bne _021DAF66
	mov r0, #0
	str r0, [r4, #4]
	pop {r4, pc}
_021DAF66:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021DAF6C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAF34

	thumb_func_start MOD73_021DAF70
MOD73_021DAF70: ; 0x021DAF70
	push {r3, r4, r5, lr}
	ldr r2, _021DAF84 ; =0x0000090C
	add r4, r1, #0
	mov r1, #0
	add r5, r0, #0
	bl memset
	str r4, [r5, #4]
	pop {r3, r4, r5, pc}
	nop
_021DAF84: .word 0x0000090C
	thumb_func_end MOD73_021DAF70

	thumb_func_start MOD73_021DAF88
MOD73_021DAF88: ; 0x021DAF88
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DAF96
	bl ErrorHandling
_021DAF96:
	ldr r2, _021DAFA4 ; =0x0000090C
	add r0, r4, #0
	mov r1, #0
	bl memset
	pop {r4, pc}
	nop
_021DAFA4: .word 0x0000090C
	thumb_func_end MOD73_021DAF88

	thumb_func_start MOD73_021DAFA8
MOD73_021DAFA8: ; 0x021DAFA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r2, #0
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	add r7, r3, #0
	mov r4, #0
	add r5, r0, #0
	add r6, #0x38
_021DAFBA:
	mov r0, #0
	str r0, [sp]
	mov r0, #5
	str r0, [sp, #4]
	mov r2, #0
	ldr r0, [sp, #0x10]
	add r1, r6, #0
	add r3, r2, #0
	str r7, [sp, #8]
	bl MOD73_021D9540
	mov r1, #0
	str r0, [r5, #0x50]
	bl FUN_020200A0
	add r4, r4, #1
	add r5, #0x48
	cmp r4, #0x20
	blt _021DAFBA
	ldr r0, [sp, #0xc]
	mov r1, #1
	str r1, [r0]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DAFA8

	thumb_func_start MOD73_021DAFEC
MOD73_021DAFEC: ; 0x021DAFEC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_021DAFF4:
	ldr r0, [r5, #0x50]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, #0x48
	cmp r4, #0x20
	blt _021DAFF4
	mov r0, #0
	str r0, [r6]
	pop {r4, r5, r6, pc}
	thumb_func_end MOD73_021DAFEC

	thumb_func_start MOD73_021DB008
MOD73_021DB008: ; 0x021DB008
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r4, #0
	add r5, #0xc
_021DB010:
	add r0, r5, #0
	bl MOD73_021DB14C
	add r4, r4, #1
	add r5, #0x48
	cmp r4, #0x20
	blt _021DB010
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021DB008

	thumb_func_start MOD73_021DB020
MOD73_021DB020: ; 0x021DB020
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r0, #0
	add r0, r1, #0
	str r1, [sp, #0x10]
	add r1, r2, #0
	sub r0, #0x80
	sub r1, #0x60
	str r2, [sp, #0x14]
	bl FX_Atan2
	asr r0, r0, #4
	lsl r1, r0, #1
	add r0, r1, #1
	ldr r7, _021DB124 ; =0x020FFA38
	lsl r0, r0, #1
	ldrsh r3, [r7, r0]
	asr r6, r3, #0x1f
	lsr r2, r3, #0x10
	lsl r0, r6, #0x10
	orr r0, r2
	mov r2, #2
	lsl r5, r3, #0x10
	lsl r2, r2, #0xa
	add r5, r5, r2
	ldr r2, _021DB128 ; =0x00000000
	adc r0, r2
	lsr r2, r5, #0xc
	lsl r0, r0, #0x14
	str r2, [sp, #0x18]
	orr r2, r0
	lsl r0, r1, #1
	str r2, [sp, #0x18]
	ldrsh r2, [r7, r0]
	asr r0, r2, #0x1f
	mov ip, r0
	lsr r1, r2, #0x10
	lsl r0, r0, #0x10
	orr r0, r1
	mov r1, #2
	lsl r5, r2, #0x10
	lsl r1, r1, #0xa
	add r1, r5, r1
	ldr r5, _021DB128 ; =0x00000000
	adc r0, r5
	lsr r7, r1, #0xc
	lsl r0, r0, #0x14
	orr r7, r0
	lsr r0, r3, #0x14
	lsl r1, r6, #0xc
	orr r1, r0
	mov r0, #2
	lsl r3, r3, #0xc
	lsl r0, r0, #0xa
	add r0, r3, r0
	ldr r3, _021DB128 ; =0x00000000
	adc r1, r3
	lsr r6, r0, #0xc
	lsl r1, r1, #0x14
	orr r6, r1
	mov r1, ip
	lsr r0, r2, #0x14
	lsl r1, r1, #0xc
	orr r1, r0
	mov r0, #2
	lsl r2, r2, #0xc
	lsl r0, r0, #0xa
	add r2, r2, r0
	ldr r0, _021DB128 ; =0x00000000
	adc r1, r0
	lsl r0, r1, #0x14
	lsr r5, r2, #0xc
	orr r5, r0
	add r0, r4, #0
	bl MOD73_021DB12C
	cmp r0, #0
	beq _021DB0E0
	mov r2, #2
	ldr r1, [sp, #0x18]
	lsl r2, r2, #0x12
	add r1, r1, r2
	str r1, [sp]
	mov r1, #6
	lsl r1, r1, #0x10
	add r1, r7, r1
	str r1, [sp, #4]
	str r6, [sp, #8]
	str r5, [sp, #0xc]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	ldr r1, [r4, #8]
	lsl r2, r2, #0xc
	lsl r3, r3, #0xc
	bl MOD73_021DB1A8
_021DB0E0:
	add r0, r4, #0
	bl MOD73_021DB12C
	cmp r0, #0
	beq _021DB112
	mov r2, #2
	ldr r1, [sp, #0x18]
	lsl r2, r2, #0x12
	sub r1, r2, r1
	str r1, [sp]
	mov r1, #6
	lsl r1, r1, #0x10
	sub r1, r1, r7
	str r1, [sp, #4]
	neg r1, r6
	str r1, [sp, #8]
	neg r1, r5
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	str r1, [sp, #0xc]
	ldr r1, [r4, #8]
	lsl r2, r2, #0xc
	lsl r3, r3, #0xc
	bl MOD73_021DB1A8
_021DB112:
	ldr r0, [r4, #8]
	ldr r1, [r4, #4]
	add r0, r0, #1
	bl _s32_div_f
	str r1, [r4, #8]
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021DB124: .word 0x020FFA38
_021DB128: .word 0x00000000
	thumb_func_end MOD73_021DB020

	thumb_func_start MOD73_021DB12C
MOD73_021DB12C: ; 0x021DB12C
	mov r2, #0
	add r3, r0, #0
_021DB130:
	ldr r1, [r3, #0xc]
	cmp r1, #0
	bne _021DB140
	mov r1, #0x48
	add r0, #0xc
	mul r1, r2
	add r0, r0, r1
	bx lr
_021DB140:
	add r2, r2, #1
	add r3, #0x48
	cmp r2, #0x20
	blt _021DB130
	mov r0, #0
	bx lr
	thumb_func_end MOD73_021DB12C

	thumb_func_start MOD73_021DB14C
MOD73_021DB14C: ; 0x021DB14C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DB18C
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021DB180
	add r0, r4, #0
	add r0, #0x14
	bl MOD73_021D962C
	str r0, [r4, #4]
	add r0, r4, #0
	add r0, #0x2c
	bl MOD73_021D962C
	ldr r0, [r4, #0x14]
	add r1, r4, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0x2c]
	add r1, #8
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x44]
	bl FUN_02020044
_021DB180:
	ldr r0, [r4, #4]
	cmp r0, #1
	bne _021DB18C
	add r0, r4, #0
	bl MOD73_021DB190
_021DB18C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB14C

	thumb_func_start MOD73_021DB190
MOD73_021DB190: ; 0x021DB190
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021DB1A6
	ldr r0, [r4, #0x44]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0
	str r0, [r4]
_021DB1A6:
	pop {r4, pc}
	thumb_func_end MOD73_021DB190

	thumb_func_start MOD73_021DB1A8
MOD73_021DB1A8: ; 0x021DB1A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x10
	add r4, r2, #0
	add r6, r3, #0
	str r0, [sp]
	add r0, r5, #0
	add r7, r1, #0
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x20]
	add r0, #0x14
	add r1, r4, #0
	bl MOD73_021D95CC
	mov r0, #0x10
	str r0, [sp]
	add r0, r5, #0
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x24]
	add r0, #0x2c
	add r1, r6, #0
	bl MOD73_021D95CC
	str r4, [r5, #8]
	str r6, [r5, #0xc]
	ldr r0, [r5, #0x44]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r5, #0x44]
	add r1, r7, #0
	bl FUN_02020130
	ldr r0, [r5, #0x44]
	bl FUN_02020198
	ldr r0, [r5, #0x44]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r5, #0x44]
	mov r1, #2
	bl FUN_02020238
	mov r0, #1
	str r0, [r5]
	mov r0, #0
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB1A8

	thumb_func_start MOD73_021DB20C
MOD73_021DB20C: ; 0x021DB20C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #2
	add r4, r1, #0
	str r0, [sp]
	ldr r0, [sp, #0x28]
	mov r1, #1
	add r6, r2, #0
	add r7, r3, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02088320
	str r0, [r5]
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	lsl r2, r4, #0x10
	lsl r3, r6, #0x10
	ldr r0, [r5]
	add r1, r7, #0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_02088490
	str r0, [r5, #4]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB20C

	thumb_func_start MOD73_021DB24C
MOD73_021DB24C: ; 0x021DB24C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r1, [r4, #4]
	bl FUN_02088694
	ldr r0, [r4]
	bl FUN_02088360
	pop {r4, pc}
	thumb_func_end MOD73_021DB24C

	thumb_func_start MOD73_021DB260
MOD73_021DB260: ; 0x021DB260
	ldr r3, _021DB268 ; =FUN_02088484
	ldr r0, [r0]
	bx r3
	nop
_021DB268: .word FUN_02088484
	thumb_func_end MOD73_021DB260

	thumb_func_start MOD73_021DB26C
MOD73_021DB26C: ; 0x021DB26C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r4, r2, #0
	bl FUN_02014590
	str r0, [r5]
	str r4, [r5, #4]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB26C

	thumb_func_start MOD73_021DB280
MOD73_021DB280: ; 0x021DB280
	ldr r3, _021DB288 ; =FUN_020145A8
	ldr r0, [r0]
	bx r3
	nop
_021DB288: .word FUN_020145A8
	thumb_func_end MOD73_021DB280

	thumb_func_start MOD73_021DB28C
MOD73_021DB28C: ; 0x021DB28C
	push {lr}
	sub sp, #0x14
	ldr r1, [r0, #4]
	mov r2, #0x18
	str r1, [sp]
	mov r1, #2
	str r1, [sp, #4]
	mov r1, #0xaf
	str r1, [sp, #8]
	mov r1, #5
	str r1, [sp, #0xc]
	add r1, sp, #0
	strb r2, [r1, #0x10]
	mov r2, #8
	strb r2, [r1, #0x11]
	ldr r0, [r0]
	add r1, sp, #0
	bl FUN_020145C8
	add sp, #0x14
	pop {pc}
	.align 2, 0
	thumb_func_end MOD73_021DB28C

	thumb_func_start MOD73_021DB2B8
MOD73_021DB2B8: ; 0x021DB2B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	bl FUN_0201466C
	add r4, r0, #0
	beq _021DB2CC
	ldr r0, [r5]
	bl FUN_020146C4
_021DB2CC:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD73_021DB2B8

	thumb_func_start MOD73_021DB2D0
MOD73_021DB2D0: ; 0x021DB2D0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r1, r3, #0
	ldr r3, [sp, #0x1c]
	add r5, r0, #0
	ldr r6, [sp, #0x18]
	add r0, r2, #0
	sub r4, r4, r3
	sub r1, r1, r3
	mov r3, #0
	str r3, [sp]
	sub r2, r5, r6
	sub r0, r0, r6
	add r3, r4, #0
	bl CircularDistance
	mov r1, #0xa0
	mul r1, r0
	add r0, r1, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD73_021DB2D0

	thumb_func_start MOD73_021DB2FC
MOD73_021DB2FC: ; 0x021DB2FC
	add r3, r0, #0
	mov r2, #0x18
	mov r1, #0
_021DB302:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021DB302
	mov r2, #0x80
	str r2, [r0]
	mov r1, #0x60
	str r1, [r0, #4]
	str r2, [r0, #8]
	str r1, [r0, #0xc]
	bx lr
	thumb_func_end MOD73_021DB2FC

	thumb_func_start MOD73_021DB318
MOD73_021DB318: ; 0x021DB318
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _021DB364 ; =0x021C48F8
	ldrh r1, [r0, #0x22]
	cmp r1, #0
	beq _021DB33C
	ldrh r1, [r0, #0x1c]
	str r1, [r4]
	ldrh r0, [r0, #0x1e]
	str r0, [r4, #4]
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _021DB33C
	ldr r0, [r4]
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	str r0, [r4, #0xc]
_021DB33C:
	mov r0, #0x80
	str r0, [sp]
	mov r0, #0x60
	str r0, [sp, #4]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl MOD73_021DB2D0
	str r0, [r4, #0x10]
	ldr r0, [r4]
	str r0, [r4, #8]
	ldr r0, [r4, #4]
	str r0, [r4, #0xc]
	ldr r0, _021DB364 ; =0x021C48F8
	ldrh r0, [r0, #0x22]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_021DB364: .word 0x021C48F8
	thumb_func_end MOD73_021DB318

	thumb_func_start MOD73_021DB368
MOD73_021DB368: ; 0x021DB368
	ldr r2, [r1]
	strb r2, [r0]
	ldr r2, [r1, #4]
	strb r2, [r0, #1]
	ldr r1, [r1, #0x10]
	cmp r1, #0
	bge _021DB380
	neg r1, r1
	strh r1, [r0, #2]
	mov r1, #1
	strb r1, [r0, #4]
	bx lr
_021DB380:
	strh r1, [r0, #2]
	mov r1, #0
	strb r1, [r0, #4]
	bx lr
	thumb_func_end MOD73_021DB368

	thumb_func_start MOD73_021DB388
MOD73_021DB388: ; 0x021DB388
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	mov r2, #0x80
	mov r3, #0x60
	bl FUN_0201CBEC
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bge _021DB3A2
	neg r0, r0
_021DB3A2:
	lsl r0, r0, #0x10
	ldr r1, [r5]
	lsr r0, r0, #0x10
	bl MOD73_021DB644
	asr r2, r0, #0x1f
	lsl r3, r2, #0x12
	lsr r1, r0, #0xe
	orr r3, r1
	mov r1, #2
	lsl r2, r0, #0x12
	mov r0, #0
	lsl r1, r1, #0xa
	add r2, r2, r1
	adc r3, r0
	lsl r1, r3, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	asr r1, r2, #0xc
	cmp r4, #0x10
	bhs _021DB3D0
	mov r0, #1
	pop {r3, r4, r5, pc}
_021DB3D0:
	add r1, #8
	cmp r4, r1
	bls _021DB3D8
	mov r0, #2
_021DB3D8:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB388

	thumb_func_start MOD73_021DB3DC
MOD73_021DB3DC: ; 0x021DB3DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	mov r0, #1
	str r0, [r5, #0x10]
	mov r0, #0
	add r4, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r0, r2, #0
	beq _021DB468
_021DB3F6:
	ldr r0, [sp, #0xc]
	add r1, r4, r0
	mov r0, #0x13
	lsl r0, r0, #4
	ldrb r1, [r1, r0]
	mov r0, #0x1c
	add r6, r1, #0
	mul r6, r0
	add r1, r4, r6
	add r2, r4, r6
	add r1, #0x90
	add r2, #0x91
	ldrb r1, [r1]
	ldrb r2, [r2]
	add r0, r5, #0
	bl MOD73_021DB388
	cmp r0, #0
	beq _021DB426
	cmp r0, #1
	beq _021DB42E
	cmp r0, #2
	beq _021DB43E
	b _021DB444
_021DB426:
	add r0, r4, r6
	add r0, #0x92
	ldrh r7, [r0]
	b _021DB444
_021DB42E:
	add r0, r4, r6
	add r0, #0x92
	ldrh r0, [r0]
	lsl r0, r0, #0xf
	lsr r7, r0, #0x10
	mov r0, #0
	str r0, [r5, #0x10]
	b _021DB444
_021DB43E:
	mov r7, #0
	add r0, r7, #0
	str r0, [r5, #0x10]
_021DB444:
	add r0, r4, r6
	add r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	bne _021DB456
	ldr r0, [sp, #8]
	add r0, r0, r7
	str r0, [sp, #8]
	b _021DB45C
_021DB456:
	ldr r0, [sp, #8]
	sub r0, r0, r7
	str r0, [sp, #8]
_021DB45C:
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [sp, #0xc]
	cmp r1, r0
	blo _021DB3F6
_021DB468:
	ldr r0, [sp, #8]
	ldr r1, [sp]
	bl _s32_div_f
	add r4, r0, #0
	ldr r1, [r5]
	ldr r0, _021DB550 ; =0x021DBF5C
	ldrb r0, [r0, r1]
	mov r1, #0x33
	lsl r1, r1, #0xe
	lsl r0, r0, #0xc
	bl FX_Div
	add r2, r0, #0
	lsl r0, r4, #0xc
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r4, #2
	mov r2, #0
	lsl r4, r4, #0xa
	add r4, r0, r4
	adc r1, r2
	lsl r0, r1, #0x14
	lsr r1, r4, #0xc
	orr r1, r0
	ldr r3, [r5, #0xc]
	asr r0, r1, #0xc
	add r0, r3, r0
	str r0, [r5, #0xc]
	cmp r0, #0
	ble _021DB4BC
	ldr r1, [r5]
	lsl r3, r1, #1
	ldr r1, _021DB554 ; =0x021DBF68
	ldrh r1, [r1, r3]
	sub r0, r0, r1
	str r0, [r5, #0xc]
	bpl _021DB4D0
	str r2, [r5, #0xc]
	b _021DB4D0
_021DB4BC:
	bge _021DB4D0
	ldr r1, [r5]
	lsl r3, r1, #1
	ldr r1, _021DB554 ; =0x021DBF68
	ldrh r1, [r1, r3]
	add r0, r0, r1
	str r0, [r5, #0xc]
	cmp r0, #0
	ble _021DB4D0
	str r2, [r5, #0xc]
_021DB4D0:
	ldr r1, [r5, #0xc]
	ldr r0, _021DB558 ; =0x00000E38
	cmp r1, r0
	ble _021DB4DC
	str r0, [r5, #0xc]
	b _021DB4E4
_021DB4DC:
	ldr r0, _021DB55C ; =0xFFFFF1C8
	cmp r1, r0
	bge _021DB4E4
	str r0, [r5, #0xc]
_021DB4E4:
	ldr r0, [r5, #0xc]
	mov r1, #0xa0
	ldr r4, [r5, #8]
	bl _s32_div_f
	add r1, r0, #0
	mov r0, #0x44
	bl MathUtil_0201BC84
	ldr r1, [r5, #8]
	add r0, r1, r0
	str r0, [r5, #8]
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _021DB508
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bge _021DB514
_021DB508:
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _021DB544
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bge _021DB544
_021DB514:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _021DB530
	lsl r0, r4, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r5, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r1, r0
	ble _021DB544
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
	b _021DB544
_021DB530:
	lsl r0, r4, #0x10
	lsr r1, r0, #0x10
	ldr r0, [r5, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r1, r0
	bge _021DB544
	ldr r0, [r5, #4]
	add r0, r0, #1
	str r0, [r5, #4]
_021DB544:
	ldr r0, [r5, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DB550: .word MOD73_021DBF5C
_021DB554: .word MOD73_021DBF68
_021DB558: .word 0x00000E38
_021DB55C: .word 0xFFFFF1C8
	thumb_func_end MOD73_021DB3DC

	thumb_func_start MOD73_021DB560
MOD73_021DB560: ; 0x021DB560
	ldr r0, [r0, #8]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	thumb_func_end MOD73_021DB560

	thumb_func_start MOD73_021DB568
MOD73_021DB568: ; 0x021DB568
	ldr r0, [r0, #4]
	bx lr
	thumb_func_end MOD73_021DB568

	thumb_func_start MOD73_021DB56C
MOD73_021DB56C: ; 0x021DB56C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #3
	blt _021DB57A
	bl ErrorHandling
_021DB57A:
	str r5, [r4]
	mov r0, #0
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB56C

	thumb_func_start MOD73_021DB584
MOD73_021DB584: ; 0x021DB584
	ldr r0, [r0, #0xc]
	bx lr
	thumb_func_end MOD73_021DB584

	thumb_func_start MOD73_021DB588
MOD73_021DB588: ; 0x021DB588
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r0, #0
	str r0, [r5, #0x18]
	add r4, r1, #0
	add r6, r2, #0
	str r0, [r5, #0x10]
	add r0, r4, #0
	add r1, r6, #0
	bl MOD73_021DB60C
	cmp r0, #0
	beq _021DB5C6
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #0x1e
	blo _021DB5C0
	ldr r1, [r5, #4]
	ldr r0, _021DB608 ; =0x0000270F
	cmp r1, r0
	bhs _021DB5B8
	add r0, r1, #1
	str r0, [r5, #4]
_021DB5B8:
	mov r0, #1
	str r0, [r5, #0x18]
	mov r0, #0
	str r0, [r5, #0xc]
_021DB5C0:
	mov r0, #0
	str r0, [r5, #0x14]
	pop {r4, r5, r6, pc}
_021DB5C6:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD73_021DB62C
	cmp r0, #0
	beq _021DB602
	ldr r0, [r5, #8]
	add r0, r0, #1
	str r0, [r5, #8]
	cmp r0, #0x5a
	blo _021DB606
	mov r0, #0
	str r0, [r5, #8]
	ldr r0, [r5, #0x14]
	cmp r0, #0
	bne _021DB5F0
	mov r0, #2
	str r0, [r5, #0x10]
	mov r0, #1
	str r0, [r5, #0x14]
	pop {r4, r5, r6, pc}
_021DB5F0:
	mov r0, #1
	str r0, [r5, #0x10]
	ldr r1, [r5]
	ldr r0, _021DB608 ; =0x0000270F
	cmp r1, r0
	bhs _021DB606
	add r0, r1, #1
	str r0, [r5]
	pop {r4, r5, r6, pc}
_021DB602:
	mov r0, #0
	str r0, [r5, #0x14]
_021DB606:
	pop {r4, r5, r6, pc}
	.align 2, 0
_021DB608: .word 0x0000270F
	thumb_func_end MOD73_021DB588

	thumb_func_start MOD73_021DB60C
MOD73_021DB60C: ; 0x021DB60C
	cmp r1, #2
	bne _021DB614
	mov r0, #0
	bx lr
_021DB614:
	cmp r0, #0
	bge _021DB61A
	neg r0, r0
_021DB61A:
	ldr r1, _021DB628 ; =0x00000E38
	cmp r0, r1
	blt _021DB624
	mov r0, #1
	bx lr
_021DB624:
	mov r0, #0
	bx lr
	.align 2, 0
_021DB628: .word 0x00000E38
	thumb_func_end MOD73_021DB60C

	thumb_func_start MOD73_021DB62C
MOD73_021DB62C: ; 0x021DB62C
	cmp r0, #0
	bge _021DB632
	neg r0, r0
_021DB632:
	ldr r1, _021DB640 ; =0x0000038E
	cmp r0, r1
	bgt _021DB63C
	mov r0, #1
	bx lr
_021DB63C:
	mov r0, #0
	bx lr
	.align 2, 0
_021DB640: .word 0x0000038E
	thumb_func_end MOD73_021DB62C

	thumb_func_start MOD73_021DB644
MOD73_021DB644: ; 0x021DB644
	push {r3, lr}
	ldr r1, _021DB678 ; =0x0000038E
	sub r0, r0, r1
	bpl _021DB64E
	mov r0, #0
_021DB64E:
	lsl r2, r0, #0xc
	asr r1, r2, #0x1f
	lsr r0, r2, #0x16
	lsl r3, r1, #0xa
	orr r3, r0
	mov r0, #2
	lsl r2, r2, #0xa
	mov r1, #0
	lsl r0, r0, #0xa
	add r0, r2, r0
	adc r3, r1
	lsl r1, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	ldr r1, _021DB67C ; =0x00AAA000
	bl FX_Div
	mov r1, #1
	lsl r1, r1, #0xc
	add r0, r0, r1
	pop {r3, pc}
	.align 2, 0
_021DB678: .word 0x0000038E
_021DB67C: .word 0x00AAA000
	thumb_func_end MOD73_021DB644

	thumb_func_start MOD73_021DB680
MOD73_021DB680: ; 0x021DB680
	add r3, r0, #0
	mov r2, #0x10
	mov r1, #0
_021DB686:
	strb r1, [r3]
	add r3, r3, #1
	sub r2, r2, #1
	bne _021DB686
	mov r1, #2
	str r1, [r0, #8]
	sub r1, r1, #3
	str r1, [r0, #4]
	bx lr
	thumb_func_end MOD73_021DB680

	thumb_func_start MOD73_021DB698
MOD73_021DB698: ; 0x021DB698
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	str r1, [r5, #0xc]
	add r1, r2, #0
	add r6, r3, #0
	bl MOD73_021DB718
	cmp r0, #1
	beq _021DB710
	cmp r6, #1
	beq _021DB710
	ldr r0, [r5, #4]
	cmp r0, #0
	bge _021DB70A
	bl MTRandom
	mov r1, #5
	add r6, r0, #0
	bl _u32_div_f
	ldr r0, [r5, #8]
	cmp r1, r0
	bhi _021DB6D0
	mov r1, #1
	str r1, [r5, #0xc]
	b _021DB6D6
_021DB6D0:
	mov r0, #1
	mov r1, #0
	str r0, [r5, #0xc]
_021DB6D6:
	ldr r0, [r5]
	cmp r1, r0
	bne _021DB6F4
	cmp r0, #1
	ldr r0, [r5, #8]
	bne _021DB6EA
	sub r0, r0, #1
	bmi _021DB6FA
	str r0, [r5, #8]
	b _021DB6FA
_021DB6EA:
	add r0, r0, #1
	cmp r0, #5
	bge _021DB6FA
	str r0, [r5, #8]
	b _021DB6FA
_021DB6F4:
	str r1, [r5]
	mov r0, #2
	str r0, [r5, #8]
_021DB6FA:
	add r0, r6, #0
	mov r1, #0x3c
	bl _u32_div_f
	ldr r0, _021DB714 ; =0x021DBFB0
	ldrb r0, [r0, r4]
	add r0, r0, r1
	str r0, [r5, #4]
_021DB70A:
	ldr r0, [r5, #4]
	sub r0, r0, #1
	str r0, [r5, #4]
_021DB710:
	pop {r4, r5, r6, pc}
	nop
_021DB714: .word MOD73_021DBFB0
	thumb_func_end MOD73_021DB698

	thumb_func_start MOD73_021DB718
MOD73_021DB718: ; 0x021DB718
	cmp r1, #0
	bge _021DB722
	ldr r2, [r0]
	cmp r2, #0
	beq _021DB72C
_021DB722:
	cmp r1, #0
	ble _021DB730
	ldr r0, [r0]
	cmp r0, #1
	bne _021DB730
_021DB72C:
	mov r0, #1
	bx lr
_021DB730:
	mov r0, #0
	bx lr
	thumb_func_end MOD73_021DB718

	thumb_func_start MOD73_021DB734
MOD73_021DB734: ; 0x021DB734
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r7, #0x1f
	add r0, r1, #0
	str r1, [sp]
	add r6, r7, #0
	bl MOD73_021DB568
	add r4, r0, #0
	mov r0, #0x96
	ldr r1, [r5]
	lsl r0, r0, #2
	cmp r1, r0
	beq _021DB75A
	ldr r1, [r5, #8]
	ldr r0, _021DB7B8 ; =0x021DBF60
	ldrb r0, [r0, r1]
	cmp r4, r0
	blt _021DB774
_021DB75A:
	ldr r0, [r5, #8]
	mov r4, #0
	add r0, r0, #1
	str r0, [r5, #8]
	str r4, [r5]
	ldr r1, [r5, #8]
	cmp r1, #3
	blt _021DB76E
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021DB76E:
	ldr r0, [sp]
	bl MOD73_021DB56C
_021DB774:
	mov r0, #0x96
	ldr r1, [r5]
	lsl r0, r0, #2
	sub r1, r0, r1
	cmp r1, #0x3c
	bgt _021DB78C
	mov r0, #0x1f
	mul r0, r1
	mov r1, #0x3c
	bl _s32_div_f
	add r7, r0, #0
_021DB78C:
	ldr r1, [r5, #8]
	ldr r0, _021DB7B8 ; =0x021DBF60
	ldrb r0, [r0, r1]
	sub r1, r0, r4
	cmp r1, #5
	bgt _021DB7A4
	mov r0, #0x1f
	mul r0, r1
	mov r1, #5
	bl _s32_div_f
	add r6, r0, #0
_021DB7A4:
	cmp r7, r6
	bge _021DB7AC
	str r7, [r5, #4]
	b _021DB7AE
_021DB7AC:
	str r6, [r5, #4]
_021DB7AE:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DB7B8: .word MOD73_021DBF60
	thumb_func_end MOD73_021DB734

	thumb_func_start MOD73_021DB7BC
MOD73_021DB7BC: ; 0x021DB7BC
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	mov r1, #0
	str r1, [r0, #0xc]
	add r7, r5, #0
	add r4, r3, #0
	str r0, [sp]
	ldr r1, [sp, #0x18]
	add r0, r4, #0
	add r6, r2, #0
	add r7, #0x98
	bl MOD73_021DB62C
	cmp r0, #1
	beq _021DB7EC
	ldr r1, [sp, #0x18]
	add r0, r4, #0
	bl MOD73_021DB60C
	cmp r0, #1
	beq _021DB7EC
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	bne _021DB7F6
_021DB7EC:
	ldr r0, [sp]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021DB7F6:
	cmp r6, #1
	bgt _021DB804
	ldr r0, [sp]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021DB804:
	ldr r0, [sp, #0x20]
	cmp r0, #1
	beq _021DB882
	mov r0, #0
	cmp r6, #0
	ble _021DB832
	mov r2, #0x96
	mov r4, #0x1c
	lsl r2, r2, #2
_021DB816:
	mov r1, #0x13
	add r3, r5, r0
	lsl r1, r1, #4
	ldrb r1, [r3, r1]
	add r3, r1, #0
	mul r3, r4
	add r1, r5, r3
	add r1, #0x92
	ldrh r1, [r1]
	cmp r1, r2
	bls _021DB882
	add r0, r0, #1
	cmp r0, r6
	blt _021DB816
_021DB832:
	mov r4, #1
	cmp r6, #1
	ble _021DB862
_021DB838:
	mov r0, #0x13
	add r1, r5, r4
	lsl r0, r0, #4
	ldrb r2, [r1, r0]
	ldrb r0, [r7]
	ldrb r1, [r7, #4]
	add r3, r7, r2
	ldrb r2, [r7, r2]
	ldrb r3, [r3, #4]
	bl FUN_0201CBEC
	cmp r0, #0x20
	bls _021DB85C
	ldr r0, [sp]
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021DB85C:
	add r4, r4, #1
	cmp r4, r6
	blt _021DB838
_021DB862:
	ldr r0, [sp]
	ldr r0, [r0, #4]
	cmp r0, #4
	bge _021DB872
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [r0, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021DB872:
	ldr r0, [sp]
	mov r2, #1
	str r2, [r0, #0xc]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp]
	str r1, [r0]
	str r2, [r0, #8]
_021DB882:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021DB7BC

	thumb_func_start MOD73_021DB884
MOD73_021DB884: ; 0x021DB884
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x68
	bl memset
	add r0, r4, #0
	add r0, #0xc
	bl MOD73_021DB680
	mov r1, #0
	mov r0, #0x1f
	str r0, [r4, #0x50]
	add r4, #0xc
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD73_021DB698
	pop {r4, pc}
	thumb_func_end MOD73_021DB884

	thumb_func_start MOD73_021DB8AC
MOD73_021DB8AC: ; 0x021DB8AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r6, r1, #0
	add r1, r5, #0
	add r0, #0x4c
	add r1, #0x1c
	add r7, r2, #0
	bl MOD73_021DB734
	cmp r0, #1
	bne _021DB8CA
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021DB8CA:
	add r0, r5, #0
	ldr r3, [r5, #0xc]
	add r0, #0x1c
	add r1, r6, #0
	add r2, r7, #0
	bl MOD73_021DB3DC
	add r0, r5, #0
	add r0, #0x1c
	bl MOD73_021DB584
	add r4, r0, #0
	add r0, r5, #0
	ldr r2, [r5, #0x54]
	add r0, #0x30
	add r1, r4, #0
	bl MOD73_021DB588
	add r0, r5, #0
	add r0, #0xc
	add r1, r4, #0
	bl MOD73_021DB718
	ldr r1, [r5, #0x54]
	add r2, r7, #0
	str r1, [sp]
	ldr r1, [r5, #0x2c]
	add r3, r4, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0x58
	add r1, r6, #0
	bl MOD73_021DB7BC
	add r0, r5, #0
	ldr r1, [r5, #0x54]
	ldr r3, [r5, #0x60]
	add r0, #0xc
	add r2, r4, #0
	bl MOD73_021DB698
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD73_021DB8AC

	thumb_func_start MOD73_021DB924
MOD73_021DB924: ; 0x021DB924
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r4, #0xc
	mov r2, #0
_021DB92E:
	add r3, r1, #0
	add r3, #0x90
	ldrb r3, [r3]
	add r0, r4, r2
	strb r3, [r4, r2]
	add r3, r1, #0
	add r3, #0x91
	ldrb r3, [r3]
	add r2, r2, #1
	add r1, #0x1c
	strb r3, [r0, #4]
	cmp r2, #4
	blt _021DB92E
	add r0, r5, #0
	add r0, #0x1c
	bl MOD73_021DB584
	cmp r0, #0
	blt _021DB95A
	strh r0, [r4, #0xa]
	mov r0, #0
	b _021DB960
_021DB95A:
	neg r0, r0
	strh r0, [r4, #0xa]
	mov r0, #1
_021DB960:
	strb r0, [r4, #0xc]
	add r0, r5, #0
	add r0, #0x1c
	bl MOD73_021DB560
	strh r0, [r4, #8]
	ldr r0, [r5, #0x40]
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0x48]
	strb r0, [r4, #0x13]
	ldr r0, [r5, #0xc]
	strb r0, [r4, #0x11]
	ldr r0, [r5, #0x18]
	strb r0, [r4, #0xe]
	ldr r0, [r5, #0x54]
	cmp r0, #3
	bge _021DB984
	b _021DB986
_021DB984:
	mov r0, #2
_021DB986:
	strb r0, [r4, #0xd]
	ldr r0, [r5, #0x50]
	strb r0, [r4, #0x10]
	ldr r0, [r5, #0x64]
	strb r0, [r4, #0xf]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB924

	thumb_func_start MOD73_021DB994
MOD73_021DB994: ; 0x021DB994
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r3, #0
	mov r1, #0x80
	mov r0, #0x60
_021DB9A0:
	add r2, r4, r3
	strb r1, [r4, r3]
	add r3, r3, #1
	strb r0, [r2, #4]
	cmp r3, #4
	blt _021DB9A0
	add r0, r5, #0
	add r0, #0x1c
	bl MOD73_021DB584
	cmp r0, #0
	blt _021DB9BE
	strh r0, [r4, #0xa]
	mov r0, #0
	b _021DB9C4
_021DB9BE:
	neg r0, r0
	strh r0, [r4, #0xa]
	mov r0, #1
_021DB9C4:
	strb r0, [r4, #0xc]
	add r0, r5, #0
	add r0, #0x1c
	bl MOD73_021DB560
	strh r0, [r4, #8]
	ldr r0, [r5, #0x40]
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0x48]
	strb r0, [r4, #0x13]
	ldr r0, [r5, #0xc]
	strb r0, [r4, #0x11]
	ldr r0, [r5, #0x18]
	strb r0, [r4, #0xe]
	ldr r0, [r5, #0x54]
	strb r0, [r4, #0xd]
	ldr r0, [r5, #0x50]
	strb r0, [r4, #0x10]
	ldr r0, [r5, #0x64]
	strb r0, [r4, #0xf]
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD73_021DB994

	thumb_func_start MOD73_021DB9F0
MOD73_021DB9F0: ; 0x021DB9F0
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	bx lr
	thumb_func_end MOD73_021DB9F0

	thumb_func_start MOD73_021DB9F8
MOD73_021DB9F8: ; 0x021DB9F8
	push {r4, lr}
	add r4, r1, #0
	mov r1, #6
	bl _u32_div_f
	ldr r1, _021DBA1C ; =0x021DBF63
	ldrb r1, [r1, r4]
	mul r1, r0
	add r0, r1, #0
	mov r1, #0xa
	bl _u32_div_f
	ldr r1, _021DBA20 ; =0x0000270F
	cmp r0, r1
	ble _021DBA18
	add r0, r1, #0
_021DBA18:
	pop {r4, pc}
	nop
_021DBA1C: .word MOD73_021DBF63
_021DBA20: .word 0x0000270F
	thumb_func_end MOD73_021DB9F8

	thumb_func_start MOD73_021DBA24
MOD73_021DBA24: ; 0x021DBA24
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	str r0, [sp]
	ldr r0, [sp, #0x78]
	str r1, [sp, #4]
	str r0, [sp, #0x78]
	add r0, r2, #0
	str r0, [sp, #0x24]
	add r0, #0x34
	str r0, [sp, #0x24]
	mov r1, #0
	add r0, sp, #0x4c
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x10]
	add r0, r1, #0
	add r6, r3, #0
	str r2, [sp, #8]
	str r1, [sp, #0x20]
	str r0, [sp, #0x18]
	str r0, [sp, #0x28]
	cmp r6, #0
	bls _021DBAD6
_021DBA56:
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x28]
	add r1, r1, r0
	mov r0, #0x13
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	ldr r1, [sp, #0x78]
	lsl r4, r0, #2
	ldr r0, [sp, #0x24]
	ldr r0, [r0, r4]
	bl LoadNutDataSingleByItemId
	mov r3, #0
	add r7, r0, #0
	add r2, r3, #0
	cmp r6, #0
	bls _021DBA98
	ldr r0, [sp, #0x24]
	mov r5, #0x13
	ldr r4, [r0, r4]
	lsl r5, r5, #4
_021DBA80:
	ldr r0, [sp, #8]
	add r0, r0, r2
	ldrb r0, [r0, r5]
	lsl r1, r0, #2
	ldr r0, [sp, #0x24]
	ldr r0, [r0, r1]
	cmp r4, r0
	bne _021DBA92
	add r3, r3, #1
_021DBA92:
	add r2, r2, #1
	cmp r2, r6
	blo _021DBA80
_021DBA98:
	ldr r0, [sp, #0x18]
	cmp r3, r0
	ble _021DBAA0
	str r3, [sp, #0x18]
_021DBAA0:
	mov r5, #0
	add r4, sp, #0x4c
_021DBAA4:
	add r0, r7, #0
	add r1, r5, #5
	bl GetNutAttr
	ldr r1, [r4]
	add r5, r5, #1
	add r0, r1, r0
	stmia r4!, {r0}
	cmp r5, #5
	blt _021DBAA4
	add r0, r7, #0
	mov r1, #0xa
	bl GetNutAttr
	ldr r1, [sp, #0x20]
	add r0, r1, r0
	str r0, [sp, #0x20]
	add r0, r7, #0
	bl FreeToHeap
	ldr r0, [sp, #0x28]
	add r0, r0, #1
	str r0, [sp, #0x28]
	cmp r0, r6
	blo _021DBA56
_021DBAD6:
	ldr r0, [sp, #0x18]
	cmp r0, #2
	blt _021DBAE6
	cmp r6, #1
	bls _021DBAE6
	mov r0, #1
	str r0, [sp, #0x14]
	b _021DBAEA
_021DBAE6:
	mov r0, #0
	str r0, [sp, #0x14]
_021DBAEA:
	ldr r0, [sp, #0x20]
	add r1, r6, #0
	bl _u32_div_f
	sub r0, r0, r6
	mov r5, #0
	add r4, sp, #0x4c
	str r0, [sp, #0x1c]
	str r5, [sp, #0xc]
	add r7, sp, #0x38
	str r4, [sp, #0x2c]
_021DBB00:
	ldr r0, [sp, #0xc]
	mov r1, #5
	add r0, r0, #1
	bl _s32_div_f
	lsl r2, r1, #2
	ldr r1, [sp, #0x2c]
	ldr r0, [r4]
	ldr r1, [r1, r2]
	sub r0, r0, r1
	str r0, [r7]
	bpl _021DBB1A
	add r5, r5, #1
_021DBB1A:
	ldr r0, [sp, #0xc]
	add r4, r4, #4
	add r0, r0, #1
	add r7, r7, #4
	str r0, [sp, #0xc]
	cmp r0, #5
	blt _021DBB00
	mov r2, #0
	add r1, sp, #0x38
_021DBB2C:
	ldr r0, [r1]
	add r2, r2, #1
	sub r0, r0, r5
	stmia r1!, {r0}
	cmp r2, #5
	blt _021DBB2C
	cmp r5, #4
	blt _021DBB40
	mov r0, #1
	str r0, [sp, #0x14]
_021DBB40:
	ldr r1, [sp]
	ldr r0, _021DBBF8 ; =0x001B7740
	ldr r1, [r1]
	bl _u32_div_f
	mov r1, #0xa
	add r5, r0, #0
	bl _s32_div_f
	cmp r1, #5
	blt _021DBB58
	add r5, #0xa
_021DBB58:
	add r0, r5, #0
	mov r1, #0xa
	mov r7, #0
	add r4, sp, #0x38
	bl _s32_div_f
	str r0, [sp, #0x10]
_021DBB66:
	ldr r0, [sp, #0x10]
	ldr r1, [r4]
	add r5, r0, #0
	mul r5, r1
	add r0, r5, #0
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x32
	blt _021DBB7C
	add r5, #0x64
_021DBB7C:
	add r0, r5, #0
	mov r1, #0x64
	bl _s32_div_f
	ldr r1, [sp]
	ldr r2, [r1, #0x30]
	ldr r1, [r1, #0x34]
	add r1, r2, r1
	sub r0, r0, r1
	str r0, [r4]
	bpl _021DBB96
	mov r0, #0
	str r0, [r4]
_021DBB96:
	add r7, r7, #1
	add r4, r4, #4
	cmp r7, #5
	blt _021DBB66
	cmp r6, #1
	bls _021DBBB8
	ldr r0, [sp]
	add r1, r6, #0
	ldr r0, [r0, #0x58]
	bl MOD73_021DB9F8
	cmp r0, #0xa
	ble _021DBBB2
	mov r0, #0xa
_021DBBB2:
	ldr r1, [sp, #0x1c]
	sub r0, r1, r0
	str r0, [sp, #0x1c]
_021DBBB8:
	ldr r0, [sp, #0x1c]
	cmp r0, #0xf
	bge _021DBBC2
	mov r0, #0xf
	str r0, [sp, #0x1c]
_021DBBC2:
	mov r3, #0
	add r1, sp, #0x38
	add r2, sp, #0x30
_021DBBC8:
	ldr r0, [r1]
	add r3, r3, #1
	strb r0, [r2]
	add r1, r1, #4
	add r2, r2, #1
	cmp r3, #5
	blt _021DBBC8
	ldr r2, [sp, #0x1c]
	ldr r0, [sp, #4]
	lsl r2, r2, #0x18
	ldr r3, [sp, #0x14]
	add r1, sp, #0x30
	lsr r2, r2, #0x18
	bl FUN_02027F04
	ldr r1, [sp]
	str r0, [r1, #4]
	ldr r0, [sp, #4]
	bl FUN_02027FDC
	ldr r1, [sp]
	str r0, [r1, #8]
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021DBBF8: .word 0x001B7740
	thumb_func_end MOD73_021DBA24

	thumb_func_start MOD73_021DBBFC
MOD73_021DBBFC: ; 0x021DBBFC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	add r4, r1, #0
	str r0, [r1, #0x20]
	ldr r0, [r5, #0x30]
	add r4, #0x20
	str r0, [r4, #4]
	ldr r0, [r5, #0x58]
	add r1, r2, #0
	bl MOD73_021DB9F8
	str r0, [r4, #8]
	ldr r0, [r5, #4]
	ldr r1, _021DBC54 ; =0x00000708
	strb r0, [r4, #0xc]
	ldr r0, [r5, #8]
	strb r0, [r4, #0xd]
	ldr r5, [r5]
	add r0, r5, #0
	bl _s32_div_f
	strb r0, [r4, #0xe]
	ldrb r1, [r4, #0xe]
	ldr r0, _021DBC54 ; =0x00000708
	mul r0, r1
	sub r5, r5, r0
	add r0, r5, #0
	mov r1, #0x1e
	bl _s32_div_f
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xf]
	mov r1, #0x1e
	add r2, r0, #0
	mul r2, r1
	sub r2, r5, r2
	mov r0, #0x64
	mul r0, r2
	bl _s32_div_f
	strb r0, [r4, #0x10]
	pop {r3, r4, r5, pc}
	nop
_021DBC54: .word 0x00000708
	thumb_func_end MOD73_021DBBFC

	.rodata
	.global MOD73_021DBC58
MOD73_021DBC58: ; 0x021DBC58
	.byte 0x01, 0x03, 0x00, 0x00

	.global MOD73_021DBC5C
MOD73_021DBC5C: ; 0x021DBC5C
	.byte 0x00, 0x02, 0x04, 0x00

	.global MOD73_021DBC60
MOD73_021DBC60: ; 0x021DBC60
	.byte 0xB2, 0x06, 0x00, 0x00, 0xB8, 0x06, 0x00, 0x00, 0xB8, 0x06, 0x00, 0x00

	.global MOD73_021DBC6C
MOD73_021DBC6C: ; 0x021DBC6C
	.byte 0xB3, 0x06, 0x00, 0x00, 0xB3, 0x06, 0x00, 0x00, 0xBB, 0x06, 0x00, 0x00

	.global MOD73_021DBC78
MOD73_021DBC78: ; 0x021DBC78
	.byte 0xB1, 0x06, 0x00, 0x00, 0xB6, 0x06, 0x00, 0x00, 0xBA, 0x06, 0x00, 0x00

	.global MOD73_021DBC84
MOD73_021DBC84: ; 0x021DBC84
	.byte 0x01

	.global MOD73_021DBC85
MOD73_021DBC85: ; 0x021DBC85
	.byte 0x01

	.global MOD73_021DBC86
MOD73_021DBC86: ; 0x021DBC86
	.byte 0x00

	.global MOD73_021DBC87
MOD73_021DBC87: ; 0x021DBC87
	.byte 0x01

	.global MOD73_021DBC88
MOD73_021DBC88: ; 0x021DBC88
	.byte 0x00

	.global MOD73_021DBC89
MOD73_021DBC89: ; 0x021DBC89
	.byte 0x00

	.global MOD73_021DBC8A
MOD73_021DBC8A: ; 0x021DBC8A
	.byte 0x05, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x08, 0x00
	.byte 0x00, 0x00

	.global MOD73_021DBC9C
MOD73_021DBC9C: ; 0x021DBC9C
	.byte 0x9D, 0x76, 0x1D, 0x02, 0x01, 0x00, 0x00, 0x00, 0x31, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x59, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00, 0x5D, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x59, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00, 0x69, 0x7F, 0x1D, 0x02, 0x02, 0x00, 0x00, 0x00
	.byte 0xB9, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x79, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0xAD, 0x7A, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00, 0x59, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x9D, 0x7C, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00, 0x59, 0x78, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x75, 0x7F, 0x1D, 0x02, 0x03, 0x00, 0x00, 0x00, 0x6D, 0x80, 0x1D, 0x02, 0x00, 0x00, 0x00, 0x00

	.global MOD73_021DBD0C
MOD73_021DBD0C: ; 0x021DBD0C
	.byte 0x01, 0x02, 0x04, 0x05

	.global MOD73_021DBD10
MOD73_021DBD10: ; 0x021DBD10
	.byte 0x30, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD73_021DBD20
MOD73_021DBD20: ; 0x021DBD20
	.byte 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD73_021DBD30
MOD73_021DBD30: ; 0x021DBD30
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

	.global MOD73_021DBD40
MOD73_021DBD40: ; 0x021DBD40
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD73_021DBD68
MOD73_021DBD68: ; 0x021DBD68
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1D, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x15, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD73_021DBDD8
MOD73_021DBDD8: ; 0x021DBDD8
	.byte 0x08, 0x08, 0x09, 0x0A, 0x0B, 0x08, 0x00, 0x00

	.global MOD73_021DBDE0
MOD73_021DBDE0: ; 0x021DBDE0
	.byte 0x04, 0x03, 0x02, 0x00

	.global MOD73_021DBDE4
MOD73_021DBDE4: ; 0x021DBDE4
	.byte 0x22, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x00, 0x00

	.global MOD73_021DBDEC
MOD73_021DBDEC: ; 0x021DBDEC
	.byte 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05

	.global MOD73_021DBDF4
MOD73_021DBDF4: ; 0x021DBDF4
	.byte 0x03, 0x02, 0x01, 0x07, 0x00, 0x06, 0x05, 0x04

	.global MOD73_021DBDFC
MOD73_021DBDFC: ; 0x021DBDFC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20

	.global MOD73_021DBE04
MOD73_021DBE04: ; 0x021DBE04
	.byte 0x23, 0x24, 0x25, 0x27, 0x29, 0x2B, 0x2D, 0x2F

	.global MOD73_021DBE0C
MOD73_021DBE0C: ; 0x021DBE0C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40

	.global MOD73_021DBE14
MOD73_021DBE14: ; 0x021DBE14
	.byte 0xAE, 0x0F, 0x00, 0x00, 0x33, 0x0F, 0x00, 0x00, 0xB8, 0x0E, 0x00, 0x00

	.global MOD73_021DBE20
MOD73_021DBE20: ; 0x021DBE20
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD73_021DBE2C
MOD73_021DBE2C: ; 0x021DBE2C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x60, 0x00, 0xE0, 0xFF, 0x58, 0x00
	.byte 0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x9C, 0x00
	.byte 0xC0, 0x00, 0x80, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0xE0, 0xFF, 0x80, 0x00, 0x20, 0x00, 0x60, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x74, 0x00, 0xE0, 0xFF, 0x60, 0x00, 0x20, 0x20, 0x00, 0x00

	.global MOD73_021DBE7C
MOD73_021DBE7C: ; 0x021DBE7C
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x20, 0x40, 0x00, 0x00, 0x20, 0x02, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x18
	.byte 0x10, 0x02, 0x02, 0x01, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x40, 0x20, 0x40, 0x10, 0x02, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x20, 0x03, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x18, 0x10, 0x03, 0x02, 0x01, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x20, 0x40, 0x20, 0x40
	.byte 0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00
	.byte 0x00, 0x00, 0x05, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x20, 0x04, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00

	.global MOD73_021DBF5C
MOD73_021DBF5C: ; 0x021DBF5C
	.byte 0x08, 0x07, 0x07, 0x00

	.global MOD73_021DBF60
MOD73_021DBF60: ; 0x021DBF60
	.byte 0x10, 0x10, 0x10

	.global MOD73_021DBF63
MOD73_021DBF63: ; 0x021DBF63
	.byte 0x00, 0x00, 0x01, 0x05, 0x0A

	.global MOD73_021DBF68
MOD73_021DBF68: ; 0x021DBF68
	.byte 0x40, 0x00, 0x48, 0x00, 0x50, 0x00, 0x00, 0x00

	.data
	.global MOD73_021DBF80
MOD73_021DBF80: ; 0x021DBF80
	.byte 0x0A, 0x00, 0x0B, 0x00, 0x10, 0x00, 0x04, 0x00, 0x02, 0x00, 0x28, 0x00, 0x02, 0x00, 0x01, 0x00
	.byte 0x1C, 0x00, 0x0F, 0x00, 0x03, 0x00, 0x28, 0x00, 0x02, 0x00, 0x12, 0x00, 0x1C, 0x00, 0x05, 0x00
	.byte 0x03, 0x00, 0xCC, 0x01, 0x02, 0x00, 0x02, 0x00, 0x1B, 0x00, 0x05, 0x00, 0x02, 0x00, 0x28, 0x00

	.global MOD73_021DBFB0
MOD73_021DBFB0: ; 0x021DBFB0
	.byte 0x96, 0x78, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
