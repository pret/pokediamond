	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EEC40
UNK_020EEC40: ; 0x020EEC40
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

	.section .bss

	.global UNK_021C59E8
UNK_021C59E8: ; 0x021C59E8
	.space 0xc

	.text

	thumb_func_start FUN_0202E29C
FUN_0202E29C: ; 0x0202E29C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0202E334 ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0202E332
	mov r1, #0xdb
	mov r0, #0xf
	lsl r1, r1, #0x4
	bl AllocFromHeap
	ldr r1, _0202E334 ; =UNK_021C59E8
	mov r2, #0xdb
	str r0, [r1, #0x8]
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	bl FUN_0202CEEC
	add r1, r0, #0x0
	mov r0, #0xf
	bl AllocFromHeap
	ldr r1, _0202E334 ; =UNK_021C59E8
	ldr r2, [r1, #0x8]
	ldr r1, _0202E338 ; =0x00000CA4
	str r0, [r2, r1]
	bl FUN_0202CEEC
	add r2, r0, #0x0
	ldr r0, _0202E334 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E338 ; =0x00000CA4
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl MI_CpuFill8
	bl FUN_02023AC4
	add r1, r0, #0x0
	mov r0, #0xf
	bl AllocFromHeap
	ldr r1, _0202E334 ; =UNK_021C59E8
	ldr r2, [r1, #0x8]
	ldr r1, _0202E33C ; =0x00000CBC
	str r0, [r2, r1]
	bl FUN_02023AC4
	add r2, r0, #0x0
	ldr r0, _0202E334 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E33C ; =0x00000CBC
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r2, _0202E334 ; =UNK_021C59E8
	mov r1, #0x33
	ldr r3, _0202E340 ; =0x00000333
	ldr r0, [r2, #0x8]
	lsl r1, r1, #0x6
	str r3, [r0, r1]
	add r0, r1, #0x0
	ldr r3, [r2, #0x8]
	sub r0, #0x8
	str r4, [r3, r0]
	ldr r0, [r2, #0x8]
	sub r1, #0x18
	add r0, r0, r1
	bl FUN_02013724
	bl FUN_0202E500
_0202E332:
	pop {r4, pc}
	.balign 4
_0202E334: .word UNK_021C59E8
_0202E338: .word 0x00000CA4
_0202E33C: .word 0x00000CBC
_0202E340: .word 0x00000333

	thumb_func_start FUN_0202E344
FUN_0202E344: ; 0x0202E344
	ldr r0, _0202E354 ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202E350
	mov r0, #0x1
	bx lr
_0202E350:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E354: .word UNK_021C59E8

	thumb_func_start FUN_0202E358
FUN_0202E358: ; 0x0202E358
	push {r4-r5}
	mov r5, #0x0
	cmp r2, #0x0
	ble _0202E378
_0202E360:
	ldrb r4, [r0, #0x0]
	ldrb r3, [r1, #0x0]
	cmp r4, r3
	beq _0202E36E
	mov r0, #0x0
	pop {r4-r5}
	bx lr
_0202E36E:
	add r5, r5, #0x1
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r5, r2
	blt _0202E360
_0202E378:
	mov r0, #0x1
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_0202E380
FUN_0202E380: ; 0x0202E380
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02033534
	add r5, r0, #0x0
	bl FUN_0203354C
	add r4, r7, #0x0
	add r6, r0, #0x0
	add r4, #0x50
	cmp r5, #0xe
	beq _0202E3C2
	ldrb r0, [r4, #0x4]
	bl FUN_0202D8B0
	cmp r0, #0x0
	beq _0202E3AC
	add r0, r5, #0x0
	bl FUN_0202D8B0
	cmp r0, #0x0
	bne _0202E3C2
_0202E3AC:
	add r0, r4, #0x0
	add r0, #0x54
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202E3BC
	ldrb r0, [r4, #0x4]
	cmp r0, #0xa
	beq _0202E460
_0202E3BC:
	ldrb r0, [r4, #0x4]
	cmp r0, r5
	bne _0202E460
_0202E3C2:
	cmp r5, #0xe
	beq _0202E3CC
	ldrb r0, [r4, #0x5]
	cmp r0, r6
	bne _0202E460
_0202E3CC:
	mov r6, #0x0
	add r4, r6, #0x0
	add r5, r6, #0x0
_0202E3D2:
	ldr r0, _0202E464 ; =UNK_021C59E8
	ldr r1, _0202E468 ; =0x00000C84
	ldr r0, [r0, #0x8]
	add r2, r0, r4
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E412
	add r0, #0x58
	add r0, r0, r5
	add r1, r7, #0x4
	mov r2, #0x6
	bl FUN_0202E358
	cmp r0, #0x0
	beq _0202E412
	ldr r2, _0202E464 ; =UNK_021C59E8
	lsl r1, r6, #0x1
	ldr r3, [r2, #0x8]
	mov r0, #0x96
	add r3, r3, r1
	ldr r1, _0202E468 ; =0x00000C84
	strh r0, [r3, r1]
	ldr r3, [r2, #0x8]
	mov r2, #0xc0
	add r1, r6, #0x0
	add r3, #0x54
	mul r1, r2
	add r0, r7, #0x0
	add r1, r3, r1
	bl MI_CpuCopy8
	pop {r3-r7, pc}
_0202E412:
	add r6, r6, #0x1
	add r4, r4, #0x2
	add r5, #0xc0
	cmp r6, #0x10
	blt _0202E3D2
	ldr r0, _0202E464 ; =UNK_021C59E8
	ldr r2, _0202E468 ; =0x00000C84
	ldr r0, [r0, #0x8]
	mov r1, #0x0
	add r4, r0, #0x0
_0202E426:
	ldrh r3, [r4, r2]
	cmp r3, #0x0
	beq _0202E434
	add r1, r1, #0x1
	add r4, r4, #0x2
	cmp r1, #0x10
	blt _0202E426
_0202E434:
	cmp r1, #0x10
	bge _0202E460
	lsl r2, r1, #0x1
	add r2, r0, r2
	ldr r0, _0202E468 ; =0x00000C84
	mov r3, #0x96
	strh r3, [r2, r0]
	ldr r2, _0202E464 ; =UNK_021C59E8
	add r3, r1, #0x0
	ldr r4, [r2, #0x8]
	mov r2, #0xc0
	add r4, #0x54
	mul r3, r2
	add r0, r7, #0x0
	add r1, r4, r3
	bl MI_CpuCopy8
	ldr r0, _0202E464 ; =UNK_021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E46C ; =0x00000CB4
	strb r2, [r1, r0]
_0202E460:
	pop {r3-r7, pc}
	nop
_0202E464: .word UNK_021C59E8
_0202E468: .word 0x00000C84
_0202E46C: .word 0x00000CB4

	thumb_func_start FUN_0202E470
FUN_0202E470: ; 0x0202E470
	push {r3, lr}
	cmp r1, #0x0
	beq _0202E47A
	bl OS_Terminate
_0202E47A:
	ldr r0, _0202E484 ; =UNK_021C59E8
	mov r1, #0x2
	str r1, [r0, #0x4]
	pop {r3, pc}
	nop
_0202E484: .word UNK_021C59E8

	thumb_func_start FUN_0202E488
FUN_0202E488: ; 0x0202E488
	ldr r0, _0202E494 ; =UNK_021C59E8
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r3, _0202E498 ; =FUN_02016454
	mov r0, #0x4
	bx r3
	.balign 4
_0202E494: .word UNK_021C59E8
_0202E498: .word FUN_02016454

	thumb_func_start FUN_0202E49C
FUN_0202E49C: ; 0x0202E49C
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02016444
	ldr r0, _0202E4C0 ; =UNK_021C59E8
	mov r1, #0x1
	str r1, [r0, #0x4]
	ldr r1, _0202E4C4 ; =FUN_0202E470
	mov r0, #0x8
	mov r2, #0x0
	bl FUN_02090DB8
	cmp r0, #0x1
	beq _0202E4BC
	bl OS_Terminate
_0202E4BC:
	pop {r3, pc}
	nop
_0202E4C0: .word UNK_021C59E8
_0202E4C4: .word FUN_0202E470

	thumb_func_start FUN_0202E4C8
FUN_0202E4C8: ; 0x0202E4C8
	ldr r0, _0202E4D8 ; =UNK_021C59E8
	ldr r0, [r0, #0x4]
	cmp r0, #0x2
	bne _0202E4D4
	mov r0, #0x1
	bx lr
_0202E4D4:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E4D8: .word UNK_021C59E8

	thumb_func_start FUN_0202E4DC
FUN_0202E4DC: ; 0x0202E4DC
	ldr r0, _0202E4EC ; =UNK_021C59E8
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202E4E8
	mov r0, #0x1
	bx lr
_0202E4E8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E4EC: .word UNK_021C59E8

	thumb_func_start FUN_0202E4F0
FUN_0202E4F0: ; 0x0202E4F0
	ldr r3, _0202E4F8 ; =FUN_02090CC8
	ldr r0, _0202E4FC ; =FUN_0202E488
	mov r1, #0x0
	bx r3
	.balign 4
_0202E4F8: .word FUN_02090CC8
_0202E4FC: .word FUN_0202E488

	thumb_func_start FUN_0202E500
FUN_0202E500: ; 0x0202E500
	push {r3, lr}
	ldr r1, _0202E534 ; =UNK_021C59E8
	mov r0, #0xcb
	ldr r2, [r1, #0x8]
	mov r3, #0x0
	lsl r0, r0, #0x4
	str r3, [r2, r0]
	ldr r1, [r1, #0x8]
	sub r0, #0xc
	ldr r2, [r1, r0]
	mov r0, #0x1f
	add r1, r2, #0x0
	and r1, r0
	mov r0, #0x20
	sub r0, r0, r1
	add r0, r2, r0
	bl FUN_0202CE64
	ldr r0, _0202E534 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	mov r0, #0x33
	lsl r0, r0, #0x6
	ldr r0, [r1, r0]
	bl FUN_0202CB70
	pop {r3, pc}
	.balign 4
_0202E534: .word UNK_021C59E8

	thumb_func_start FUN_0202E538
FUN_0202E538: ; 0x0202E538
	push {r3-r5, lr}
	mov r4, #0x0
	ldr r2, _0202E564 ; =UNK_021C59E8
	ldr r0, _0202E568 ; =0x00000C84
	add r5, r4, #0x0
	add r1, r4, #0x0
_0202E544:
	ldr r3, [r2, #0x8]
	add r4, r4, #0x1
	add r3, r3, r5
	add r5, r5, #0x2
	strh r1, [r3, r0]
	cmp r4, #0x10
	blt _0202E544
	ldr r0, _0202E564 ; =UNK_021C59E8
	mov r2, #0x3
	ldr r0, [r0, #0x8]
	lsl r2, r2, #0xa
	add r0, #0x54
	bl MI_CpuFill8
	pop {r3-r5, pc}
	nop
_0202E564: .word UNK_021C59E8
_0202E568: .word 0x00000C84

	thumb_func_start FUN_0202E56C
FUN_0202E56C: ; 0x0202E56C
	push {r3-r4}
	ldr r1, _0202E58C ; =UNK_021C59E8
	lsl r0, r0, #0x18
	ldr r2, [r1, #0x8]
	ldr r4, _0202E590 ; =0x00000DAD
	lsr r0, r0, #0x18
	ldrb r1, [r2, r4]
	mov r3, #0x8
	lsl r0, r0, #0x1f
	bic r1, r3
	lsr r0, r0, #0x1c
	orr r0, r1
	strb r0, [r2, r4]
	pop {r3-r4}
	bx lr
	nop
_0202E58C: .word UNK_021C59E8
_0202E590: .word 0x00000DAD

	thumb_func_start FUN_0202E594
FUN_0202E594: ; 0x0202E594
	push {r4-r5}
	ldr r1, _0202E5F0 ; =UNK_021C59E8
	ldr r0, _0202E5F4 ; =0x00000CB4
	ldr r3, [r1, #0x8]
	mov r2, #0x0
	strb r2, [r3, r0]
	add r3, r0, #0x0
	ldr r5, [r1, #0x8]
	add r3, #0xf9
	ldrb r4, [r5, r3]
	mov r3, #0x1
	bic r4, r3
	add r3, r0, #0x0
	add r3, #0xf9
	strb r4, [r5, r3]
	add r3, r0, #0x0
	ldr r5, [r1, #0x8]
	add r3, #0xf9
	ldrb r4, [r5, r3]
	mov r3, #0x4
	bic r4, r3
	add r3, r0, #0x0
	add r3, #0xf9
	strb r4, [r5, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x8]
	add r3, #0xf6
	strb r2, [r4, r3]
	add r3, r0, #0x0
	ldr r5, [r1, #0x8]
	add r3, #0xf9
	ldrb r4, [r5, r3]
	mov r3, #0x10
	bic r4, r3
	add r3, r0, #0x0
	add r3, #0xf9
	strb r4, [r5, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x8]
	add r3, #0xf8
	strb r2, [r4, r3]
	ldr r1, [r1, #0x8]
	add r0, #0xf7
	strb r2, [r1, r0]
	pop {r4-r5}
	bx lr
	.balign 4
_0202E5F0: .word UNK_021C59E8
_0202E5F4: .word 0x00000CB4

	thumb_func_start FUN_0202E5F8
FUN_0202E5F8: ; 0x0202E5F8
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0202E594
	add r0, r5, #0x0
	bl FUN_0202E56C
	bl FUN_0202D2F4
	ldr r0, _0202E65C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E660 ; =0x00000DAB
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0202E62A
	ldr r0, _0202E664 ; =FUN_020303BC
	mov r1, #0xe
	bl FUN_0202D0A0
	ldr r0, _0202E65C ; =UNK_021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E660 ; =0x00000DAB
	strb r2, [r1, r0]
_0202E62A:
	ldr r0, _0202E65C ; =UNK_021C59E8
	ldr r3, _0202E668 ; =0x00000DAD
	ldr r1, [r0, #0x8]
	mov r2, #0x20
	ldrb r0, [r1, r3]
	bic r0, r2
	lsl r2, r4, #0x18
	lsr r2, r2, #0x18
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1a
	orr r0, r2
	strb r0, [r1, r3]
	bl FUN_0202CBD4
	cmp r0, #0x1
	bne _0202E656
	bl FUN_0202CBFC
	cmp r0, #0x0
	beq _0202E656
	mov r0, #0x1
	pop {r3-r5, pc}
_0202E656:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0202E65C: .word UNK_021C59E8
_0202E660: .word 0x00000DAB
_0202E664: .word FUN_020303BC
_0202E668: .word 0x00000DAD

	thumb_func_start FUN_0202E66C
FUN_0202E66C: ; 0x0202E66C
	push {r4, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	bl FUN_0202E594
	cmp r4, #0x0
	beq _0202E67E
	bl FUN_0202E538
_0202E67E:
	ldr r0, _0202E6DC ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E6E0 ; =0x00000DAB
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0202E69C
	ldr r0, _0202E6E4 ; =FUN_02030238
	mov r1, #0xe
	bl FUN_0202D0A0
	ldr r0, _0202E6DC ; =UNK_021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E6E0 ; =0x00000DAB
	strb r2, [r1, r0]
_0202E69C:
	bl FUN_0202CBD4
	cmp r0, #0x1
	bne _0202E6D4
	ldr r2, _0202E6E8 ; =UNK_020EEC40
	add r0, sp, #0x0
	ldrb r3, [r2, #0x0]
	add r1, sp, #0x0
	strb r3, [r0, #0x0]
	ldrb r3, [r2, #0x1]
	strb r3, [r0, #0x1]
	ldrb r3, [r2, #0x2]
	strb r3, [r0, #0x2]
	ldrb r3, [r2, #0x3]
	strb r3, [r0, #0x3]
	ldrb r3, [r2, #0x4]
	ldrb r2, [r2, #0x5]
	strb r3, [r0, #0x4]
	strb r2, [r0, #0x5]
	ldr r0, _0202E6EC ; =FUN_0202E380
	mov r2, #0x0
	bl FUN_0202C570
	cmp r0, #0x0
	beq _0202E6D4
	add sp, #0x8
	mov r0, #0x1
	pop {r4, pc}
_0202E6D4:
	mov r0, #0x0
	add sp, #0x8
	pop {r4, pc}
	nop
_0202E6DC: .word UNK_021C59E8
_0202E6E0: .word 0x00000DAB
_0202E6E4: .word FUN_02030238
_0202E6E8: .word UNK_020EEC40
_0202E6EC: .word FUN_0202E380

	thumb_func_start FUN_0202E6F0
FUN_0202E6F0: ; 0x0202E6F0
	push {r3, lr}
	ldr r0, _0202E77C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	bne _0202E6FE
	mov r0, #0x1
	pop {r3, pc}
_0202E6FE:
	ldr r0, _0202E780 ; =0x00000DAC
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202E710
	cmp r0, #0x1
	beq _0202E740
	cmp r0, #0x2
	beq _0202E758
	b _0202E776
_0202E710:
	bl FUN_0202D21C
	cmp r0, #0x0
	beq _0202E728
	bl FUN_0202C770
	ldr r0, _0202E77C ; =UNK_021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E780 ; =0x00000DAC
	strb r2, [r1, r0]
	b _0202E776
_0202E728:
	bl FUN_0202D1E4
	cmp r0, #0x0
	bne _0202E776
	bl FUN_0202D100
	ldr r0, _0202E77C ; =UNK_021C59E8
	mov r2, #0x2
	ldr r1, [r0, #0x8]
	ldr r0, _0202E780 ; =0x00000DAC
	strb r2, [r1, r0]
	b _0202E776
_0202E740:
	bl FUN_0202D1E4
	cmp r0, #0x0
	bne _0202E776
	bl FUN_0202D100
	ldr r0, _0202E77C ; =UNK_021C59E8
	mov r2, #0x2
	ldr r1, [r0, #0x8]
	ldr r0, _0202E780 ; =0x00000DAC
	strb r2, [r1, r0]
	b _0202E776
_0202E758:
	bl FUN_0202D1C8
	cmp r0, #0x0
	beq _0202E764
	mov r0, #0x1
	pop {r3, pc}
_0202E764:
	bl FUN_0202D200
	cmp r0, #0x0
	beq _0202E776
	ldr r0, _0202E77C ; =UNK_021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E780 ; =0x00000DAC
	strb r2, [r1, r0]
_0202E776:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0202E77C: .word UNK_021C59E8
_0202E780: .word 0x00000DAC

	thumb_func_start FUN_0202E784
FUN_0202E784: ; 0x0202E784
	push {r3, lr}
	ldr r0, _0202E7A8 ; =UNK_021C59E8
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	beq _0202E7A2
	ldr r0, _0202E7AC ; =0x00000DAA
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	bne _0202E7A2
	mov r1, #0x1
	strb r1, [r2, r0]
	bl FUN_0202D100
	mov r0, #0x1
	pop {r3, pc}
_0202E7A2:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0202E7A8: .word UNK_021C59E8
_0202E7AC: .word 0x00000DAA

	thumb_func_start FUN_0202E7B0
FUN_0202E7B0: ; 0x0202E7B0
	push {r3, lr}
	ldr r1, _0202E7D0 ; =UNK_021C59E8
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0202E7CE
	cmp r0, #0x0
	ldr r0, _0202E7D4 ; =0x00000DAA
	beq _0202E7C6
	mov r1, #0x2
	strb r1, [r2, r0]
	pop {r3, pc}
_0202E7C6:
	mov r1, #0x0
	strb r1, [r2, r0]
	bl FUN_0202E500
_0202E7CE:
	pop {r3, pc}
	.balign 4
_0202E7D0: .word UNK_021C59E8
_0202E7D4: .word 0x00000DAA

	thumb_func_start FUN_0202E7D8
FUN_0202E7D8: ; 0x0202E7D8
	push {r3, lr}
	ldr r0, _0202E804 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E808 ; =0x00000CBC
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r0, _0202E804 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E80C ; =0x00000CA4
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r0, _0202E804 ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	bl FreeToHeap
	ldr r0, _0202E804 ; =UNK_021C59E8
	mov r1, #0x0
	str r1, [r0, #0x8]
	pop {r3, pc}
	nop
_0202E804: .word UNK_021C59E8
_0202E808: .word 0x00000CBC
_0202E80C: .word 0x00000CA4

	thumb_func_start FUN_0202E810
FUN_0202E810: ; 0x0202E810
	push {r4, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0202E81E
	mov r0, #0x0
	pop {r4, pc}
_0202E81E:
	ldr r1, _0202E83C ; =UNK_021C59E8
	mov r0, #0x0
	ldr r4, [r1, #0x8]
	ldr r1, _0202E840 ; =0x00000C84
	add r3, r0, #0x0
_0202E828:
	ldrh r2, [r4, r1]
	cmp r2, #0x0
	beq _0202E830
	add r0, r0, #0x1
_0202E830:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, #0x10
	blt _0202E828
	pop {r4, pc}
	nop
_0202E83C: .word UNK_021C59E8
_0202E840: .word 0x00000C84

	thumb_func_start FUN_0202E844
FUN_0202E844: ; 0x0202E844
	push {r3-r5, lr}
	ldr r1, _0202E870 ; =UNK_021C59E8
	mov r4, #0x0
	ldr r5, [r1, #0x8]
	ldr r1, _0202E874 ; =0x00000C84
	add r3, r4, #0x0
_0202E850:
	ldrh r2, [r5, r1]
	cmp r2, #0x0
	beq _0202E860
	cmp r4, r0
	bne _0202E85E
	add r0, r3, #0x0
	pop {r3-r5, pc}
_0202E85E:
	add r4, r4, #0x1
_0202E860:
	add r3, r3, #0x1
	add r5, r5, #0x2
	cmp r3, #0x10
	blt _0202E850
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0202E870: .word UNK_021C59E8
_0202E874: .word 0x00000C84

	thumb_func_start FUN_0202E878
FUN_0202E878: ; 0x0202E878
	ldr r0, _0202E884 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E888 ; =0x00000CB4
	ldrb r0, [r1, r0]
	bx lr
	nop
_0202E884: .word UNK_021C59E8
_0202E888: .word 0x00000CB4

	thumb_func_start FUN_0202E88C
FUN_0202E88C: ; 0x0202E88C
	ldr r0, _0202E898 ; =UNK_021C59E8
	mov r2, #0x0
	ldr r1, [r0, #0x8]
	ldr r0, _0202E89C ; =0x00000CB4
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202E898: .word UNK_021C59E8
_0202E89C: .word 0x00000CB4

	thumb_func_start FUN_0202E8A0
FUN_0202E8A0: ; 0x0202E8A0
	ldr r1, _0202E8C8 ; =UNK_021C59E8
	ldr r3, [r1, #0x8]
	lsl r1, r0, #0x1
	add r2, r3, r1
	ldr r1, _0202E8CC ; =0x00000C84
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E8C2
	mov r1, #0xc0
	mul r1, r0
	add r0, r3, r1
	add r0, #0xaa
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202E8C4
	mov r0, #0x1
	bx lr
_0202E8C2:
	mov r0, #0x0
_0202E8C4:
	bx lr
	nop
_0202E8C8: .word UNK_021C59E8
_0202E8CC: .word 0x00000C84

	thumb_func_start FUN_0202E8D0
FUN_0202E8D0: ; 0x0202E8D0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0xf
_0202E8D6:
	add r0, r4, #0x0
	bl FUN_0202E8A0
	cmp r0, r5
	ble _0202E8E8
	cmp r0, #0x8
	bge _0202E8E8
	add r0, r4, #0x0
	pop {r3-r5, pc}
_0202E8E8:
	sub r4, r4, #0x1
	bpl _0202E8D6
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202E8F4
FUN_0202E8F4: ; 0x0202E8F4
	push {r3-r7, lr}
	bl FUN_0202E810
	cmp r0, #0x0
	bne _0202E904
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0202E904:
	mov r5, #0x2d
	ldr r7, _0202E948 ; =UNK_021C59E8
	mov r6, #0xf
	mov r4, #0x1e
	lsl r5, r5, #0x6
_0202E90E:
	ldr r0, [r7, #0x8]
	ldr r1, _0202E94C ; =0x00000C84
	add r2, r0, r4
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E938
	add r0, #0x58
	add r0, r0, r5
	bl FUN_0202EFE4
	cmp r0, #0x0
	beq _0202E938
	add r0, r6, #0x0
	bl FUN_0202E8A0
	cmp r0, #0x1
	ble _0202E938
	cmp r0, #0x8
	bge _0202E938
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0202E938:
	sub r4, r4, #0x2
	sub r5, #0xc0
	sub r6, r6, #0x1
	bpl _0202E90E
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
	nop
_0202E948: .word UNK_021C59E8
_0202E94C: .word 0x00000C84

	thumb_func_start FUN_0202E950
FUN_0202E950: ; 0x0202E950
	push {r3-r7, lr}
	bl FUN_0202E810
	cmp r0, #0x0
	bne _0202E960
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_0202E960:
	mov r5, #0x2d
	ldr r7, _0202E9A4 ; =UNK_021C59E8
	mov r6, #0xf
	mov r4, #0x1e
	lsl r5, r5, #0x6
_0202E96A:
	ldr r0, [r7, #0x8]
	ldr r1, _0202E9A8 ; =0x00000C84
	add r2, r0, r4
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E986
	add r0, #0x58
	add r0, r0, r5
	bl FUN_0202EFE4
	cmp r0, #0x0
	beq _0202E986
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0202E986:
	sub r4, r4, #0x2
	sub r5, #0xc0
	sub r6, r6, #0x1
	bpl _0202E96A
	mov r0, #0x1
	bl FUN_0202E8D0
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _0202E9A2
	mov r0, #0x0
	bl FUN_0202E8D0
_0202E9A2:
	pop {r3-r7, pc}
	.balign 4
_0202E9A4: .word UNK_021C59E8
_0202E9A8: .word 0x00000C84

	thumb_func_start FUN_0202E9AC
FUN_0202E9AC: ; 0x0202E9AC
	push {r4-r6, lr}
	add r4, r1, #0x0
	ldr r1, _0202E9E0 ; =UNK_021C59E8
	mov r5, #0x0
	ldr r6, [r1, #0x8]
	ldr r1, _0202E9E4 ; =0x00000C84
	add r3, r5, #0x0
_0202E9BA:
	ldrh r2, [r6, r1]
	cmp r2, #0x0
	beq _0202E9D4
	cmp r0, r5
	bne _0202E9D2
	add r0, r3, #0x0
	bl FUN_0202EF84
	add r1, r4, #0x0
	bl PlayerProfile_Copy
	pop {r4-r6, pc}
_0202E9D2:
	add r5, r5, #0x1
_0202E9D4:
	add r3, r3, #0x1
	add r6, r6, #0x2
	cmp r3, #0x10
	blt _0202E9BA
	pop {r4-r6, pc}
	nop
_0202E9E0: .word UNK_021C59E8
_0202E9E4: .word 0x00000C84

	thumb_func_start FUN_0202E9E8
FUN_0202E9E8: ; 0x0202E9E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0202CBD4
	cmp r0, #0x2
	bne _0202E9FC
	bl FUN_0202C770
	mov r0, #0x0
	pop {r3-r5, pc}
_0202E9FC:
	bl FUN_0202CBD4
	cmp r0, #0x1
	bne _0202EA48
	bl FUN_02033534
	mov r1, #0xc0
	add r4, r5, #0x0
	mul r4, r1
	ldr r1, _0202EA4C ; =UNK_021C59E8
	ldr r3, [r1, #0x8]
	add r1, r3, r4
	add r1, #0x8a
	ldrh r2, [r1, #0x0]
	ldr r1, _0202EA50 ; =0x00000DA8
	strb r2, [r3, r1]
	bl FUN_0202D8B0
	cmp r0, #0x0
	beq _0202EA36
	ldr r1, _0202EA4C ; =UNK_021C59E8
	mov r0, #0x1
	ldr r1, [r1, #0x8]
	mov r2, #0x0
	add r1, #0x58
	add r1, r1, r4
	bl FUN_0202C4D8
	b _0202EA44
_0202EA36:
	ldr r1, _0202EA4C ; =UNK_021C59E8
	mov r0, #0x1
	ldr r1, [r1, #0x8]
	add r1, #0x54
	add r1, r1, r4
	bl FUN_0202D034
_0202EA44:
	mov r0, #0x1
	pop {r3-r5, pc}
_0202EA48:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0202EA4C: .word UNK_021C59E8
_0202EA50: .word 0x00000DA8

	thumb_func_start FUN_0202EA54
FUN_0202EA54: ; 0x0202EA54
	push {r4-r7}
	mov r4, #0x0
	ldr r1, _0202EA90 ; =UNK_021C59E8
	ldr r0, _0202EA94 ; =0x00000C84
	add r5, r4, #0x0
	mov r2, #0x1
_0202EA60:
	ldr r3, [r1, #0x8]
	add r3, r3, r5
	ldrh r6, [r3, r0]
	cmp r6, #0x0
	beq _0202EA84
	beq _0202EA84
	ldr r6, _0202EA94 ; =0x00000C84
	ldrh r6, [r3, r6]
	sub r7, r6, #0x1
	ldr r6, _0202EA94 ; =0x00000C84
	strh r7, [r3, r6]
	ldr r3, [r1, #0x8]
	add r7, r3, r5
	ldrh r6, [r7, r6]
	cmp r6, #0x0
	bne _0202EA84
	ldr r6, _0202EA98 ; =0x00000CB4
	strb r2, [r3, r6]
_0202EA84:
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x10
	blt _0202EA60
	pop {r4-r7}
	bx lr
	.balign 4
_0202EA90: .word UNK_021C59E8
_0202EA94: .word 0x00000C84
_0202EA98: .word 0x00000CB4

	thumb_func_start FUN_0202EA9C
FUN_0202EA9C: ; 0x0202EA9C
	push {r3-r5, lr}
	bl FUN_02033534
	add r5, r0, #0x0
	bl FUN_0202EF70
	add r4, r0, #0x0
	cmp r5, #0xf
	beq _0202EB24
	ldr r0, _0202EB6C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB70 ; =0x00000CC4
	add r5, r1, r0
	bl FUN_02023AC4
	cmp r0, #0x20
	ble _0202EAC2
	bl ErrorHandling
_0202EAC2:
	bl PlayerProfile_sizeof
	cmp r0, #0x20
	beq _0202EACE
	bl ErrorHandling
_0202EACE:
	bl PlayerProfile_sizeof
	add r1, r5, #0x0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, #0x10
	bl MI_CpuCopy8
	bl FUN_02023AC4
	add r2, r0, #0x0
	ldr r0, _0202EB6C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB74 ; =0x00000CBC
	ldr r0, [r1, r0]
	add r1, r5, #0x0
	add r1, #0x30
	bl MI_CpuCopy8
	add r0, r4, #0x0
	bl PlayerProfile_GetTrainerID
	str r0, [r5, #0x0]
	bl FUN_02033534
	strb r0, [r5, #0x4]
	bl FUN_0203354C
	strb r0, [r5, #0x5]
	ldr r0, _0202EB6C ; =UNK_021C59E8
	mov r2, #0x8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB78 ; =0x00000CA8
	add r0, r1, r0
	add r1, r5, #0x0
	add r1, #0x8
	bl MI_CpuCopy8
	bl FUN_0202D358
	add r5, #0x54
	strb r0, [r5, #0x0]
	b _0202EB4E
_0202EB24:
	ldr r1, _0202EB6C ; =UNK_021C59E8
	ldr r4, [r1, #0x8]
	ldr r1, _0202EB70 ; =0x00000CC4
	add r5, r4, r1
	bl PlayerProfile_GetTrainerID
	ldr r1, _0202EB70 ; =0x00000CC4
	str r0, [r4, r1]
	bl FUN_02033534
	strb r0, [r5, #0x4]
	bl FUN_0203354C
	strb r0, [r5, #0x5]
	ldr r0, _0202EB6C ; =UNK_021C59E8
	add r5, #0x8
	ldr r0, [r0, #0x8]
	add r1, r5, #0x0
	mov r2, #0x54
	bl MI_CpuCopy8
_0202EB4E:
	ldr r0, _0202EB6C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB70 ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl DC_FlushRange
	ldr r0, _0202EB6C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB70 ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl FUN_0202CB7C
	pop {r3-r5, pc}
	.balign 4
_0202EB6C: .word UNK_021C59E8
_0202EB70: .word 0x00000CC4
_0202EB74: .word 0x00000CBC
_0202EB78: .word 0x00000CA8

	thumb_func_start FUN_0202EB7C
FUN_0202EB7C: ; 0x0202EB7C
	push {r4, lr}
	ldr r0, _0202EBC8 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EBCC ; =0x00000CC4
	add r4, r1, r0
	bl FUN_0202EDB8
	ldrb r1, [r4, #0x6]
	cmp r1, r0
	beq _0202EBC6
	bl FUN_0202EDB8
	strb r0, [r4, #0x6]
	ldr r0, _0202EBC8 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EBCC ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl DC_FlushRange
	ldr r0, _0202EBC8 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EBCC ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl FUN_0202CB7C
	ldr r3, _0202EBC8 ; =UNK_021C59E8
	ldr r2, _0202EBCC ; =0x00000CC4
	ldr r4, [r3, #0x8]
	ldrh r3, [r3, #0x0]
	add r0, r4, r2
	sub r2, r2, #0x4
	ldr r2, [r4, r2]
	mov r1, #0x5c
	bl FUN_0202D240
_0202EBC6:
	pop {r4, pc}
	.balign 4
_0202EBC8: .word UNK_021C59E8
_0202EBCC: .word 0x00000CC4

	thumb_func_start FUN_0202EBD0
FUN_0202EBD0: ; 0x0202EBD0
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_0202CBD4
	add r5, r0, #0x0
	bl FUN_0202DF54
	bl FUN_0202EB7C
	bl FUN_0202D19C
	cmp r0, #0x0
	bne _0202EC0C
	bl FUN_0202EE24
	cmp r0, #0x0
	bne _0202EC0C
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r2, [r0, #0x8]
	ldr r0, _0202ED54 ; =0x00000DAD
	ldrb r1, [r2, r0]
	lsl r3, r1, #0x1d
	lsr r3, r3, #0x1f
	beq _0202EC0C
	mov r3, #0x1
	bic r1, r3
	mov r3, #0x1
	orr r1, r3
	strb r1, [r2, r0]
_0202EC0C:
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r1, _0202ED58 ; =0x0000FFFF
	ldr r3, [r0, #0x8]
	ldr r0, _0202ED5C ; =0x00000DA6
	ldrh r2, [r3, r0]
	cmp r2, r1
	bne _0202EC1C
	strh r4, [r3, r0]
_0202EC1C:
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r2, [r0, #0x8]
	ldr r0, _0202ED54 ; =0x00000DAD
	ldrb r1, [r2, r0]
	lsl r3, r1, #0x1e
	lsr r3, r3, #0x1f
	beq _0202EC3C
	sub r3, r0, #0x7
	ldrh r3, [r2, r3]
	cmp r3, r4
	bls _0202EC3C
	mov r3, #0x1
	bic r1, r3
	mov r3, #0x1
	orr r1, r3
	strb r1, [r2, r0]
_0202EC3C:
	bl FUN_0202CBE8
	cmp r0, #0x19
	bne _0202EC4A
	mov r0, #0x0
	bl FUN_020335D0
_0202EC4A:
	cmp r5, #0x9
	bhi _0202ED4C
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202EC5A: ; jump table (using 16-bit offset)
	.short _0202EC6E - _0202EC5A - 2; case 0
	.short _0202EC8E - _0202EC5A - 2; case 1
	.short _0202ED4C - _0202EC5A - 2; case 2
	.short _0202ED4C - _0202EC5A - 2; case 3
	.short _0202ED4C - _0202EC5A - 2; case 4
	.short _0202ED4C - _0202EC5A - 2; case 5
	.short _0202ED4C - _0202EC5A - 2; case 6
	.short _0202ECD2 - _0202EC5A - 2; case 7
	.short _0202ECB8 - _0202EC5A - 2; case 8
	.short _0202ECB8 - _0202EC5A - 2; case 9
_0202EC6E:
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r2, [r0, #0x8]
	ldr r0, _0202ED60 ; =0x00000DAA
	ldrb r1, [r2, r0]
	cmp r1, #0x1
	bne _0202EC82
	bl FUN_0202E7D8
	add sp, #0x8
	pop {r3-r5, pc}
_0202EC82:
	cmp r1, #0x2
	bne _0202ED4C
	mov r1, #0x3
	strb r1, [r2, r0]
	add sp, #0x8
	pop {r3-r5, pc}
_0202EC8E:
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202ED60 ; =0x00000DAA
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _0202ECA2
	bl FUN_0202D178
	cmp r0, #0x0
	bne _0202ED4C
_0202ECA2:
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202ED60 ; =0x00000DAA
	ldrb r0, [r1, r0]
	cmp r0, #0x2
	bne _0202ED4C
	bl FUN_0202D178
	add sp, #0x8
	cmp r0, #0x0
	pop {r3-r5, pc}
_0202ECB8:
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r3, [r0, #0x8]
	cmp r3, #0x0
	beq _0202ED4C
	ldr r1, _0202ED54 ; =0x00000DAD
	mov r0, #0x1
	ldrb r2, [r3, r1]
	add sp, #0x8
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r3, r1]
	pop {r3-r5, pc}
_0202ECD2:
	bl FUN_0202CDA4
	ldr r3, _0202ED50 ; =UNK_021C59E8
	ldr r2, _0202ED64 ; =0x00000DA9
	ldr r4, [r3, #0x8]
	ldrb r1, [r4, r2]
	cmp r1, #0x0
	bne _0202ECEE
	sub r1, r2, #0x5
	strh r0, [r4, r1]
	ldr r0, [r3, #0x8]
	mov r1, #0x5
	strb r1, [r0, r2]
	b _0202ECF2
_0202ECEE:
	sub r0, r1, #0x1
	strb r0, [r4, r2]
_0202ECF2:
	ldr r1, _0202ED50 ; =UNK_021C59E8
	ldr r0, _0202ED68 ; =0x00000DA4
	ldr r2, [r1, #0x8]
	ldrh r5, [r2, r0]
	add r0, #0x9
	ldrb r0, [r2, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _0202ED0A
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x1
	strh r0, [r1, #0x0]
_0202ED0A:
	bl FUN_0202EA9C
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r4, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202EEE8
	str r0, [sp, #0x0]
	ldr r1, _0202ED50 ; =UNK_021C59E8
	ldr r0, _0202ED54 ; =0x00000DAD
	ldr r2, [r1, #0x8]
	add r3, r4, #0x0
	ldrb r0, [r2, r0]
	add r2, r5, #0x0
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	str r0, [sp, #0x4]
	ldrh r1, [r1, #0x0]
	mov r0, #0x0
	bl FUN_0202CF84
	ldr r0, _0202ED50 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202ED6C ; =0x00000DA8
	strb r5, [r1, r0]
_0202ED4C:
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0202ED50: .word UNK_021C59E8
_0202ED54: .word 0x00000DAD
_0202ED58: .word 0x0000FFFF
_0202ED5C: .word 0x00000DA6
_0202ED60: .word 0x00000DAA
_0202ED64: .word 0x00000DA9
_0202ED68: .word 0x00000DA4
_0202ED6C: .word 0x00000DA8

	thumb_func_start FUN_0202ED70
FUN_0202ED70: ; 0x0202ED70
	push {r3, lr}
	ldr r1, _0202ED80 ; =UNK_021C59E8
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	beq _0202ED7E
	bl FUN_0202EBD0
_0202ED7E:
	pop {r3, pc}
	.balign 4
_0202ED80: .word UNK_021C59E8

	thumb_func_start FUN_0202ED84
FUN_0202ED84: ; 0x0202ED84
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0202EDB4 ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0202ED94
	mov r0, #0x0
	pop {r4, pc}
_0202ED94:
	bl FUN_0202CBD4
	cmp r0, #0x4
	beq _0202EDA0
	mov r0, #0x0
	pop {r4, pc}
_0202EDA0:
	bl FUN_0202CB8C
	mov r2, #0x1
	add r1, r2, #0x0
	lsl r1, r4
	tst r0, r1
	bne _0202EDB0
	mov r2, #0x0
_0202EDB0:
	add r0, r2, #0x0
	pop {r4, pc}
	.balign 4
_0202EDB4: .word UNK_021C59E8

	thumb_func_start FUN_0202EDB8
FUN_0202EDB8: ; 0x0202EDB8
	push {r3-r5, lr}
	mov r4, #0x0
	add r5, r4, #0x0
_0202EDBE:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202ED84
	cmp r0, #0x0
	beq _0202EDCC
	add r4, r4, #0x1
_0202EDCC:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202EDBE
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202EDD8
FUN_0202EDD8: ; 0x0202EDD8
	ldr r0, _0202EDF0 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0202EDEC
	ldr r0, _0202EDF4 ; =0x00000DAA
	ldrb r0, [r1, r0]
	cmp r0, #0x3
	bne _0202EDEC
	mov r0, #0x1
	bx lr
_0202EDEC:
	mov r0, #0x0
	bx lr
	.balign 4
_0202EDF0: .word UNK_021C59E8
_0202EDF4: .word 0x00000DAA

	thumb_func_start FUN_0202EDF8
FUN_0202EDF8: ; 0x0202EDF8
	ldr r0, _0202EE08 ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EE04
	mov r0, #0x1
	bx lr
_0202EE04:
	mov r0, #0x0
	bx lr
	.balign 4
_0202EE08: .word UNK_021C59E8

	thumb_func_start FUN_0202EE0C
FUN_0202EE0C: ; 0x0202EE0C
	push {r3, lr}
	ldr r0, _0202EE20 ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EE1C
	bl FUN_0202D1C8
	pop {r3, pc}
_0202EE1C:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202EE20: .word UNK_021C59E8

	thumb_func_start FUN_0202EE24
FUN_0202EE24: ; 0x0202EE24
	push {r3, lr}
	ldr r0, _0202EE3C ; =UNK_021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EE38
	bl FUN_0202CB8C
	ldr r1, _0202EE40 ; =0x0000FFFE
	and r0, r1
	pop {r3, pc}
_0202EE38:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0202EE3C: .word UNK_021C59E8
_0202EE40: .word 0x0000FFFE

	thumb_func_start FUN_0202EE44
FUN_0202EE44: ; 0x0202EE44
	push {r3, lr}
	bl FUN_0202EE60
	cmp r0, #0x0
	beq _0202EE5A
	bl FUN_0202CBE8
	cmp r0, #0x14
	bne _0202EE5A
	mov r0, #0x1
	pop {r3, pc}
_0202EE5A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202EE60
FUN_0202EE60: ; 0x0202EE60
	ldr r0, _0202EE7C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0202EE76
	ldr r0, _0202EE80 ; =0x00000DAD
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0202EE76
	mov r0, #0x1
	bx lr
_0202EE76:
	mov r0, #0x0
	bx lr
	nop
_0202EE7C: .word UNK_021C59E8
_0202EE80: .word 0x00000DAD

	thumb_func_start FUN_0202EE84
FUN_0202EE84: ; 0x0202EE84
	push {r3-r4}
	ldr r1, _0202EEA8 ; =UNK_021C59E8
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0202EEA2
	ldr r4, _0202EEAC ; =0x00000DAD
	lsl r0, r0, #0x18
	ldrb r1, [r2, r4]
	lsr r0, r0, #0x18
	mov r3, #0x4
	lsl r0, r0, #0x1f
	bic r1, r3
	lsr r0, r0, #0x1d
	orr r0, r1
	strb r0, [r2, r4]
_0202EEA2:
	pop {r3-r4}
	bx lr
	nop
_0202EEA8: .word UNK_021C59E8
_0202EEAC: .word 0x00000DAD

	thumb_func_start FUN_0202EEB0
FUN_0202EEB0: ; 0x0202EEB0
	push {r4-r5}
	ldr r5, _0202EEDC ; =UNK_021C59E8
	ldr r2, [r5, #0x8]
	cmp r2, #0x0
	beq _0202EED6
	ldr r4, _0202EEE0 ; =0x00000DAD
	lsl r0, r0, #0x18
	ldrb r1, [r2, r4]
	lsr r0, r0, #0x18
	mov r3, #0x2
	lsl r0, r0, #0x1f
	bic r1, r3
	lsr r0, r0, #0x1e
	orr r0, r1
	strb r0, [r2, r4]
	ldr r2, _0202EEE4 ; =0x0000FFFF
	ldr r1, [r5, #0x8]
	sub r0, r4, #0x7
	strh r2, [r1, r0]
_0202EED6:
	pop {r4-r5}
	bx lr
	nop
_0202EEDC: .word UNK_021C59E8
_0202EEE0: .word 0x00000DAD
_0202EEE4: .word 0x0000FFFF

	thumb_func_start FUN_0202EEE8
FUN_0202EEE8: ; 0x0202EEE8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl WM_GetDispersionBeaconPeriod
	add r4, r0, #0x0
	cmp r5, #0x1a
	blo _0202EEFA
	bl ErrorHandling
_0202EEFA:
	cmp r5, #0xa
	bne _0202EF04
	lsl r0, r4, #0xe
	lsr r0, r0, #0x10
	pop {r3-r5, pc}
_0202EF04:
	cmp r5, #0x9
	beq _0202EF0C
	cmp r5, #0xd
	bne _0202EF12
_0202EF0C:
	lsl r0, r4, #0xe
	lsr r0, r0, #0x10
	pop {r3-r5, pc}
_0202EF12:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202EF18
FUN_0202EF18: ; 0x0202EF18
	ldr r1, _0202EF3C ; =UNK_021C59E8
	ldr r3, [r1, #0x8]
	cmp r3, #0x0
	beq _0202EF36
	lsl r1, r0, #0x1
	add r2, r3, r1
	ldr r1, _0202EF40 ; =0x00000C84
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202EF36
	mov r1, #0xc0
	add r3, #0x54
	mul r1, r0
	add r0, r3, r1
	bx lr
_0202EF36:
	mov r0, #0x0
	bx lr
	nop
_0202EF3C: .word UNK_021C59E8
_0202EF40: .word 0x00000C84

	thumb_func_start FUN_0202EF44
FUN_0202EF44: ; 0x0202EF44
	ldr r1, _0202EF68 ; =UNK_021C59E8
	ldr r3, [r1, #0x8]
	cmp r3, #0x0
	beq _0202EF62
	lsl r1, r0, #0x1
	add r2, r3, r1
	ldr r1, _0202EF6C ; =0x00000C84
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202EF62
	mov r1, #0xc0
	add r3, #0xa4
	mul r1, r0
	add r0, r3, r1
	bx lr
_0202EF62:
	mov r0, #0x0
	bx lr
	nop
_0202EF68: .word UNK_021C59E8
_0202EF6C: .word 0x00000C84

	thumb_func_start FUN_0202EF70
FUN_0202EF70: ; 0x0202EF70
	ldr r0, _0202EF7C ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EF80 ; =0x00000CB8
	ldr r0, [r1, r0]
	bx lr
	nop
_0202EF7C: .word UNK_021C59E8
_0202EF80: .word 0x00000CB8

	thumb_func_start FUN_0202EF84
FUN_0202EF84: ; 0x0202EF84
	ldr r1, _0202EFA4 ; =UNK_021C59E8
	ldr r3, [r1, #0x8]
	lsl r1, r0, #0x1
	add r2, r3, r1
	ldr r1, _0202EFA8 ; =0x00000C84
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	bne _0202EF98
	mov r0, #0x0
	bx lr
_0202EF98:
	mov r1, #0xc0
	add r3, #0xa4
	mul r1, r0
	add r0, r3, r1
	add r0, #0x10
	bx lr
	.balign 4
_0202EFA4: .word UNK_021C59E8
_0202EFA8: .word 0x00000C84

	thumb_func_start FUN_0202EFAC
FUN_0202EFAC: ; 0x0202EFAC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202EFDC ; =UNK_021C59E8
	add r4, r1, #0x0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EFD8
	cmp r4, #0x8
	blt _0202EFC2
	bl ErrorHandling
_0202EFC2:
	ldr r1, _0202EFDC ; =UNK_021C59E8
	add r0, r5, #0x0
	ldr r2, [r1, #0x8]
	ldr r1, _0202EFE0 ; =0x00000C54
	add r3, r2, r1
	mov r2, #0x6
	add r1, r4, #0x0
	mul r1, r2
	add r1, r3, r1
	bl MI_CpuCopy8
_0202EFD8:
	pop {r3-r5, pc}
	nop
_0202EFDC: .word UNK_021C59E8
_0202EFE0: .word 0x00000C54

	thumb_func_start FUN_0202EFE4
FUN_0202EFE4: ; 0x0202EFE4
	push {r4-r5}
	ldr r2, _0202F034 ; =UNK_021C59E8
	mov r1, #0x0
	ldr r3, [r2, #0x8]
	ldr r2, _0202F038 ; =0x00000C54
	add r2, r3, r2
	ldrb r3, [r0, #0x0]
_0202EFF2:
	ldrb r4, [r2, #0x0]
	cmp r4, r3
	bne _0202F026
	ldrb r5, [r2, #0x1]
	ldrb r4, [r0, #0x1]
	cmp r5, r4
	bne _0202F026
	ldrb r5, [r2, #0x2]
	ldrb r4, [r0, #0x2]
	cmp r5, r4
	bne _0202F026
	ldrb r5, [r2, #0x3]
	ldrb r4, [r0, #0x3]
	cmp r5, r4
	bne _0202F026
	ldrb r5, [r2, #0x4]
	ldrb r4, [r0, #0x4]
	cmp r5, r4
	bne _0202F026
	ldrb r5, [r2, #0x5]
	ldrb r4, [r0, #0x5]
	cmp r5, r4
	bne _0202F026
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_0202F026:
	add r1, r1, #0x1
	add r2, r2, #0x6
	cmp r1, #0x8
	blt _0202EFF2
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	.balign 4
_0202F034: .word UNK_021C59E8
_0202F038: .word 0x00000C54

	thumb_func_start FUN_0202F03C
FUN_0202F03C: ; 0x0202F03C
	ldr r0, _0202F054 ; =UNK_021C59E8
	ldr r1, [r0, #0x8]
	cmp r1, #0x0
	beq _0202F04E
	ldr r0, _0202F058 ; =0x00000DAD
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bx lr
_0202F04E:
	mov r0, #0x0
	bx lr
	nop
_0202F054: .word UNK_021C59E8
_0202F058: .word 0x00000DAD

	thumb_func_start FUN_0202F05C
FUN_0202F05C: ; 0x0202F05C
	ldr r0, _0202F070 ; =UNK_021C59E8
	ldr r3, [r0, #0x8]
	cmp r3, #0x0
	beq _0202F06E
	ldr r1, _0202F074 ; =0x00000DAD
	mov r0, #0x10
	ldrb r2, [r3, r1]
	orr r0, r2
	strb r0, [r3, r1]
_0202F06E:
	bx lr
	.balign 4
_0202F070: .word UNK_021C59E8
_0202F074: .word 0x00000DAD

	thumb_func_start FUN_0202F078
FUN_0202F078: ; 0x0202F078
	ldr r1, _0202F088 ; =UNK_021C59E8
	ldr r3, _0202F08C ; =MI_CpuCopy8
	ldr r2, [r1, #0x8]
	ldr r1, _0202F090 ; =0x00000CA8
	add r1, r2, r1
	mov r2, #0x8
	bx r3
	nop
_0202F088: .word UNK_021C59E8
_0202F08C: .word MI_CpuCopy8
_0202F090: .word 0x00000CA8

	thumb_func_start FUN_0202F094
FUN_0202F094: ; 0x0202F094
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02023AC4
	ldr r1, _0202F0B0 ; =UNK_021C59E8
	add r2, r0, #0x0
	ldr r3, [r1, #0x8]
	ldr r1, _0202F0B4 ; =0x00000CBC
	add r0, r4, #0x0
	ldr r1, [r3, r1]
	bl MI_CpuCopy8
	pop {r4, pc}
	nop
_0202F0B0: .word UNK_021C59E8
_0202F0B4: .word 0x00000CBC

	thumb_func_start FUN_0202F0B8
FUN_0202F0B8: ; 0x0202F0B8
	push {r4, lr}
	bl FUN_0202EA9C
	ldr r3, _0202F0D4 ; =UNK_021C59E8
	ldr r2, _0202F0D8 ; =0x00000CC4
	ldr r4, [r3, #0x8]
	ldrh r3, [r3, #0x0]
	add r0, r4, r2
	sub r2, r2, #0x4
	ldr r2, [r4, r2]
	mov r1, #0x5c
	bl FUN_0202D240
	pop {r4, pc}
	.balign 4
_0202F0D4: .word UNK_021C59E8
_0202F0D8: .word 0x00000CC4

	thumb_func_start FUN_0202F0DC
FUN_0202F0DC: ; 0x0202F0DC
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_0202F0E4:
	add r0, r4, #0x0
	bl FUN_0202EF44
	cmp r0, #0x0
	beq _0202F0F8
	ldrb r1, [r0, #0x4]
	cmp r1, r6
	bne _0202F0F8
	ldrb r0, [r0, #0x6]
	add r5, r5, r0
_0202F0F8:
	add r4, r4, #0x1
	cmp r4, #0x10
	blt _0202F0E4
	add r0, r5, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202F104
FUN_0202F104: ; 0x0202F104
	ldr r3, _0202F108 ; =FUN_0202D2D0
	bx r3
	.balign 4
_0202F108: .word FUN_0202D2D0

	thumb_func_start FUN_0202F10C
FUN_0202F10C: ; 0x0202F10C
	push {r3, lr}
	ldr r1, _0202F120 ; =UNK_021C59E8
	mov r2, #0x54
	ldr r1, [r1, #0x8]
	bl MI_CpuCopy8
	bl FUN_0202F0B8
	pop {r3, pc}
	nop
_0202F120: .word UNK_021C59E8

	thumb_func_start FUN_0202F124
FUN_0202F124: ; 0x0202F124
	ldr r1, _0202F148 ; =UNK_021C59E8
	ldr r3, [r1, #0x8]
	cmp r3, #0x0
	beq _0202F144
	lsl r1, r0, #0x1
	add r2, r3, r1
	ldr r1, _0202F14C ; =0x00000C84
	ldrh r1, [r2, r1]
	cmp r1, #0x0
	beq _0202F144
	mov r1, #0xc0
	add r3, #0xa4
	mul r1, r0
	add r0, r3, r1
	add r0, #0x8
	bx lr
_0202F144:
	mov r0, #0x0
	bx lr
	.balign 4
_0202F148: .word UNK_021C59E8
_0202F14C: .word 0x00000C84
