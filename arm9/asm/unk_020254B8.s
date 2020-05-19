	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020254B8
FUN_020254B8: ; 0x020254B8
	mov r0, #0x22
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_020254C0
FUN_020254C0: ; 0x020254C0
	ldr r3, _020254C8 ; =FUN_02022610
	mov r1, #0x9
	bx r3
	nop
_020254C8: .word FUN_02022610

	thumb_func_start FUN_020254CC
FUN_020254CC: ; 0x020254CC
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r6, _020254EC ; =0x0000FFFF
	add r5, r0, #0x0
	add r7, r4, #0x0
_020254D6:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x88
	bl memset
	strh r6, [r5, #0x0]
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	blt _020254D6
	pop {r3-r7, pc}
	.balign 4
_020254EC: .word 0x0000FFFF

	thumb_func_start FUN_020254F0
FUN_020254F0: ; 0x020254F0
	mov r2, #0x88
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_020254F8
FUN_020254F8: ; 0x020254F8
	add r0, r0, r1
	add r0, #0x68
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025500
FUN_02025500: ; 0x02025500
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl StringNotEqual
	cmp r0, #0x0
	bne _0202551A
	ldr r1, [r5, #0x10]
	ldr r0, [r4, #0x10]
	cmp r1, r0
	bne _0202551A
	mov r0, #0x1
	pop {r3-r5, pc}
_0202551A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025520
FUN_02025520: ; 0x02025520
	push {r4-r7, lr}
	sub sp, #0x2c
	str r1, [sp, #0x4]
	mov r1, #0x22
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	lsl r1, r1, #0x6
	str r2, [sp, #0x8]
	bl FUN_02016998
	str r0, [sp, #0x10]
	bl FUN_020254CC
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02025578
	ldr r7, [sp, #0x4]
	add r6, sp, #0x18
_02025548:
	mov r0, #0x0
	mvn r0, r0
	ldr r5, [sp, #0x0]
	str r0, [r6, #0x0]
	mov r4, #0x0
_02025552:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02025500
	cmp r0, #0x0
	beq _02025560
	str r4, [r6, #0x0]
_02025560:
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	blt _02025552
	ldr r0, [sp, #0x14]
	add r6, r6, #0x4
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	add r7, #0x88
	str r1, [sp, #0x14]
	cmp r1, r0
	blt _02025548
_02025578:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	str r4, [sp, #0xc]
	cmp r0, #0x0
	ble _020255BE
	ldr r5, [sp, #0x10]
	add r6, sp, #0x18
_02025586:
	ldr r3, [sp, #0x4]
	add r7, r5, #0x0
	mov r2, #0x11
_0202558C:
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202558C
	ldr r1, [r6, #0x0]
	cmp r1, #0x0
	blt _020255A6
	add r2, r1, #0x0
	mov r0, #0x88
	mul r2, r0
	ldr r1, _02025610 ; =0x0000FFFF
	ldr r0, [sp, #0x0]
	strh r1, [r0, r2]
_020255A6:
	ldr r0, [sp, #0x4]
	add r5, #0x88
	add r0, #0x88
	str r0, [sp, #0x4]
	ldr r0, [sp, #0xc]
	add r4, r4, #0x1
	add r1, r0, #0x1
	ldr r0, [sp, #0x8]
	add r6, r6, #0x4
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _02025586
_020255BE:
	mov r0, #0x0
	mov r12, r0
	mov r0, #0x88
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x0]
	add r5, r0, r1
_020255CE:
	ldrh r1, [r3, #0x0]
	ldr r0, _02025610 ; =0x0000FFFF
	cmp r1, r0
	beq _020255EC
	add r6, r3, #0x0
	add r7, r5, #0x0
	mov r2, #0x11
_020255DC:
	ldmia r6!, {r0-r1}
	stmia r7!, {r0-r1}
	sub r2, r2, #0x1
	bne _020255DC
	add r4, r4, #0x1
	add r5, #0x88
	cmp r4, #0x10
	bge _020255F8
_020255EC:
	mov r0, r12
	add r0, r0, #0x1
	add r3, #0x88
	mov r12, r0
	cmp r0, #0x10
	blt _020255CE
_020255F8:
	mov r2, #0x22
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x10]
	lsl r2, r2, #0x6
	bl memcpy
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	add sp, #0x2c
	pop {r4-r7, pc}
	nop
_02025610: .word 0x0000FFFF

	thumb_func_start FUN_02025614
FUN_02025614: ; 0x02025614
	push {r3-r6}
	mov r3, #0x0
	add r4, r0, #0x0
_0202561A:
	ldr r2, [r4, #0x10]
	cmp r1, r2
	bne _02025626
	mov r0, #0x1
	pop {r3-r6}
	bx lr
_02025626:
	add r3, r3, #0x1
	add r4, #0x88
	cmp r3, #0x10
	blt _0202561A
	mov r6, #0x0
	add r3, r6, #0x0
_02025632:
	add r4, r3, #0x0
	add r5, r0, #0x0
_02025636:
	ldr r2, [r5, #0x18]
	cmp r1, r2
	bne _02025642
	add r0, r6, #0x2
	pop {r3-r6}
	bx lr
_02025642:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x10
	blt _02025636
	add r6, r6, #0x1
	add r0, #0x88
	cmp r6, #0x10
	blt _02025632
	mov r0, #0x0
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_02025658
FUN_02025658: ; 0x02025658
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	strb r0, [r4, #0x4]
	ldr r0, _020256A0 ; =0x020ECAC4
	mov r1, #0x8
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x5]
	ldr r0, _020256A4 ; =0x020ECAC0
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x6]
	mov r0, #0xff
	strb r0, [r4, #0x7]
	add r0, r4, #0x0
	add r0, #0x8
	bl StringFillEOS
	ldr r0, _020256A8 ; =0x0000FFFF
	mov r1, #0x0
	add r2, r4, #0x0
_02025682:
	add r1, r1, #0x1
	strh r0, [r2, #0x18]
	add r2, r2, #0x2
	cmp r1, #0x3
	blt _02025682
	mov r5, #0x0
	add r4, #0x20
_02025690:
	add r0, r4, #0x0
	bl FUN_02013724
	add r5, r5, #0x1
	add r4, #0x8
	cmp r5, #0x3
	blt _02025690
	pop {r3-r5, pc}
	.balign 4
_020256A0: .word 0x020ECAC4
_020256A4: .word 0x020ECAC0
_020256A8: .word 0x0000FFFF

	thumb_func_start FUN_020256AC
FUN_020256AC: ; 0x020256AC
	ldrb r0, [r0, #0x7]
	cmp r0, #0xb
	bhi _020256B6
	mov r0, #0x1
	bx lr
_020256B6:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020256BC
FUN_020256BC: ; 0x020256BC
	push {r4, lr}
	mov r1, #0x38
	bl FUN_020169D8
	add r4, r0, #0x0
	bl FUN_02025658
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020256D0
FUN_020256D0: ; 0x020256D0
	ldr r3, _020256D8 ; =MI_CpuCopy8
	mov r2, #0x38
	bx r3
	nop
_020256D8: .word MI_CpuCopy8

	thumb_func_start FUN_020256DC
FUN_020256DC: ; 0x020256DC
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02025658
	add r0, r7, #0x0
	strb r6, [r5, #0x7]
	bl FUN_0206BB1C
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	bl FUN_020238F4
	add r6, r0, #0x0
	bl FUN_0202398C
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x8
	bl StringCopy
	add r0, r6, #0x0
	bl FUN_020239CC
	strb r0, [r5, #0x4]
	add r0, r6, #0x0
	bl FUN_020239BC
	str r0, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	bl FUN_0206B9AC
	cmp r4, r0
	bge _020257AE
	add r5, #0x18
_0202572A:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	bl FUN_0206B9B0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r0, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	bl FUN_0206B6C8
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x8]
	bl FUN_0206B7BC
	lsl r3, r6, #0x1
	ldrh r1, [r5, r3]
	add r7, r0, #0x0
	ldr r0, _020257B4 ; =0xFFFFF000
	add r2, r1, #0x0
	and r2, r0
	ldr r0, [sp, #0x10]
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _020257B8 ; =0x00000FFF
	and r0, r1
	orr r0, r2
	strh r0, [r5, r3]
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrh r1, [r5, r3]
	ldr r0, _020257BC ; =0xFFFF0FFF
	and r0, r1
	lsl r1, r7, #0x1c
	lsr r1, r1, #0x10
	orr r0, r1
	strh r0, [r5, r3]
	cmp r6, #0x3
	bhs _020257AE
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, [sp, #0x0]
	bl FUN_0206B9AC
	cmp r4, r0
	blt _0202572A
_020257AE:
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_020257B4: .word 0xFFFFF000
_020257B8: .word 0x00000FFF
_020257BC: .word 0xFFFF0FFF

	thumb_func_start FUN_020257C0
FUN_020257C0: ; 0x020257C0
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020257C4
FUN_020257C4: ; 0x020257C4
	add r0, #0x8
	bx lr

	thumb_func_start FUN_020257C8
FUN_020257C8: ; 0x020257C8
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020257CC
FUN_020257CC: ; 0x020257CC
	ldrb r0, [r0, #0x7]
	bx lr

	thumb_func_start FUN_020257D0
FUN_020257D0: ; 0x020257D0
	cmp r1, #0xc
	bhs _020257D6
	strb r1, [r0, #0x7]
_020257D6:
	bx lr

	thumb_func_start FUN_020257D8
FUN_020257D8: ; 0x020257D8
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_020257DC
FUN_020257DC: ; 0x020257DC
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_020257E0
FUN_020257E0: ; 0x020257E0
	cmp r1, #0x3
	bhs _02025810
	cmp r2, #0x0
	beq _020257F0
	cmp r2, #0x1
	beq _020257FC
	cmp r2, #0x2
	b _02025808
_020257F0:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x18]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x14
	bx lr
_020257FC:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x18]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1c
	bx lr
_02025808:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0x18]
	bx lr
_02025810:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02025814
FUN_02025814: ; 0x02025814
	cmp r1, #0x3
	bhs _02025820
	add r0, #0x20
	lsl r1, r1, #0x3
	add r0, r0, r1
	bx lr
_02025820:
	add r0, #0x20
	bx lr

	thumb_func_start FUN_02025824
FUN_02025824: ; 0x02025824
	push {r3, lr}
	cmp r2, #0x3
	bhs _02025834
	add r0, #0x20
	lsl r2, r2, #0x3
	add r0, r0, r2
	bl FUN_02013960
_02025834:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025838
FUN_02025838: ; 0x02025838
	ldr r3, _02025840 ; =FUN_02022610
	mov r1, #0xf
	bx r3
	nop
_02025840: .word FUN_02022610

	thumb_func_start FUN_02025844
FUN_02025844: ; 0x02025844
	mov r0, #0x46
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_0202584C
FUN_0202584C: ; 0x0202584C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_02025852:
	add r0, r5, #0x0
	bl FUN_02025658
	add r4, r4, #0x1
	add r5, #0x38
	cmp r4, #0x14
	blt _02025852
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025864
FUN_02025864: ; 0x02025864
	push {r3, lr}
	cmp r1, #0x0
	bne _02025872
	mov r1, #0x14
	bl FUN_020258F0
	pop {r3, pc}
_02025872:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}

	thumb_func_start FUN_02025878
FUN_02025878: ; 0x02025878
	push {r3, lr}
	bl FUN_02025940
	cmp r0, #0x0
	beq _02025886
	bl FUN_02025658
_02025886:
	pop {r3, pc}

	thumb_func_start FUN_02025888
FUN_02025888: ; 0x02025888
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02025940
	add r1, r0, #0x0
	beq _0202589A
	add r0, r4, #0x0
	bl FUN_020256D0
_0202589A:
	pop {r4, pc}

	thumb_func_start FUN_0202589C
FUN_0202589C: ; 0x0202589C
	push {r3, lr}
	cmp r1, #0x0
	bne _020258AA
	mov r1, #0x14
	bl FUN_02025918
	pop {r3, pc}
_020258AA:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020258B0
FUN_020258B0: ; 0x020258B0
	push {r3-r5, lr}
	add r5, r3, #0x0
	bl FUN_02025940
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020256BC
	add r5, r0, #0x0
	cmp r4, #0x0
	beq _020258CE
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020256D0
_020258CE:
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020258D4
FUN_020258D4: ; 0x020258D4
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02025940
	cmp r0, #0x0
	bne _020258E8
	add r0, r4, #0x0
	bl FUN_02025658
	pop {r4, pc}
_020258E8:
	add r1, r4, #0x0
	bl FUN_020256D0
	pop {r4, pc}

	thumb_func_start FUN_020258F0
FUN_020258F0: ; 0x020258F0
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r6, #0x0
	ble _02025912
_020258FC:
	add r0, r5, #0x0
	bl FUN_020256AC
	cmp r0, #0x0
	bne _0202590A
	add r0, r4, #0x0
	pop {r4-r6, pc}
_0202590A:
	add r4, r4, #0x1
	add r5, #0x38
	cmp r4, r6
	blt _020258FC
_02025912:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r6, pc}

	thumb_func_start FUN_02025918
FUN_02025918: ; 0x02025918
	push {r3-r7, lr}
	mov r4, #0x0
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	cmp r7, #0x0
	ble _0202593A
_02025926:
	add r0, r5, #0x0
	bl FUN_020256AC
	cmp r0, #0x0
	beq _02025932
	add r4, r4, #0x1
_02025932:
	add r6, r6, #0x1
	add r5, #0x38
	cmp r6, r7
	blt _02025926
_0202593A:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02025940
FUN_02025940: ; 0x02025940
	mov r3, #0x0
	cmp r1, #0x0
	bne _02025950
	cmp r2, #0x14
	bge _02025950
	mov r1, #0x38
	mul r1, r2
	add r3, r0, r1
_02025950:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025954
FUN_02025954: ; 0x02025954
	ldr r0, _02025958 ; =0x000009B4
	bx lr
	.balign 4
_02025958: .word 0x000009B4

	thumb_func_start FUN_0202595C
FUN_0202595C: ; 0x0202595C
	mov r0, #0x94
	bx lr

	thumb_func_start FUN_02025960
FUN_02025960: ; 0x02025960
	mov r0, #0x3c
	bx lr

	thumb_func_start FUN_02025964
FUN_02025964: ; 0x02025964
	push {r4, lr}
	mov r1, #0x3c
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x3c
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202597C
FUN_0202597C: ; 0x0202597C
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	add r0, sp, #0xc
	add r1, sp, #0x0
	bl FUN_0201265C
	ldr r0, _020259D8 ; =0x021C48B8
	ldr r6, [sp, #0xc]
	ldr r1, [sp, #0x8]
	ldr r0, [r0, #0x2c]
	lsl r6, r6, #0x5
	add r5, r1, r0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r0, r0, r6
	lsl r0, r0, #0x5
	add r0, r1, r0
	mov r7, #0x0
	ldr r2, [sp, #0x0]
	lsl r0, r0, #0x5
	add r0, r2, r0
	ldr r3, [sp, #0x4]
	lsl r0, r0, #0x5
	add r0, r3, r0
	lsl r0, r0, #0x5
	add r5, r5, r0
	ldr r2, _020259DC ; =0x000009B4
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r0, #0x94
	mov r1, #0x9b
	str r5, [r0, #0x0]
	lsl r1, r1, #0x4
	ldrb r2, [r4, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r4, r1]
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_020259D8: .word 0x021C48B8
_020259DC: .word 0x000009B4

	thumb_func_start FUN_020259E0
FUN_020259E0: ; 0x020259E0
	mov r1, #0x9
	mov r3, #0x0
	lsl r1, r1, #0x8
_020259E6:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _020259F2
	add r0, r3, #0x0
	bx lr
_020259F2:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _020259E6
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02025A00
FUN_02025A00: ; 0x02025A00
	mov r1, #0x95
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025A06:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A12
	add r0, r3, #0x0
	bx lr
_02025A12:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A06
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02025A20
FUN_02025A20: ; 0x02025A20
	ldr r1, _02025A3C ; =0x00000928
	mov r3, #0x0
_02025A24:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A30
	add r0, r3, #0x0
	bx lr
_02025A30:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A24
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4
_02025A3C: .word 0x00000928

	thumb_func_start FUN_02025A40
FUN_02025A40: ; 0x02025A40
	ldr r1, _02025A5C ; =0x000008D8
	mov r3, #0x0
_02025A44:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025A50
	add r0, r3, #0x0
	bx lr
_02025A50:
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025A44
	mov r0, #0x0
	mvn r0, r0
	bx lr
	.balign 4
_02025A5C: .word 0x000008D8

	thumb_func_start FUN_02025A60
FUN_02025A60: ; 0x02025A60
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	bl FUN_02026CC4
	ldr r1, _02025B50 ; =0x020EE958
	add r6, r0, #0x0
	ldrb r2, [r1, #0x0]
	add r0, sp, #0x8
	strb r2, [r0, #0x6]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x7]
	ldrb r2, [r1, #0x2]
	strb r2, [r0, #0x8]
	ldrb r2, [r1, #0x3]
	strb r2, [r0, #0x9]
	ldrb r2, [r1, #0x4]
	strb r2, [r0, #0xa]
	ldrb r2, [r1, #0x5]
	strb r2, [r0, #0xb]
	ldrb r2, [r1, #0x6]
	strb r2, [r0, #0x0]
	ldrb r2, [r1, #0x7]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x8]
	strb r2, [r0, #0x2]
	ldrb r2, [r1, #0x9]
	strb r2, [r0, #0x3]
	ldrb r2, [r1, #0xa]
	strb r2, [r0, #0x4]
	ldrb r1, [r1, #0xb]
	strb r1, [r0, #0x5]
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ble _02025B4C
	str r0, [sp, #0x4]
	cmp r0, #0x63
	ble _02025AB0
	mov r0, #0x63
	str r0, [sp, #0x4]
_02025AB0:
	add r0, r6, #0x0
	add r0, #0x94
	ldr r3, [r0, #0x0]
	mov r0, #0x0
	mov r12, r0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _02025B28
	add r7, sp, #0xc
	add r7, #0x2
_02025AC4:
	mov r2, #0x0
_02025AC6:
	ldr r0, _02025B54 ; =0x0000055C
	add r4, r6, r2
	ldrb r5, [r4, r0]
	cmp r5, #0x0
	beq _02025B16
	ldr r0, _02025B58 ; =0x5D588B65
	ldrb r1, [r7, r5]
	mul r0, r3
	ldr r3, _02025B5C ; =0x00269EC3
	add r3, r0, r3
	cmp r1, #0x0
	bne _02025AE2
	lsr r0, r3, #0x10
	b _02025AE8
_02025AE2:
	lsr r0, r3, #0x10
	mul r1, r0
	lsr r0, r1, #0x10
_02025AE8:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x8
	ldrb r0, [r0, r5]
	add r0, r0, r1
	mov r1, #0x17
	lsl r1, r1, #0x6
	ldrb r1, [r4, r1]
	add r1, r0, r1
	cmp r1, #0x63
	bge _02025B0E
	mov r1, #0x17
	lsl r1, r1, #0x6
	ldrb r1, [r4, r1]
	add r1, r1, r0
	mov r0, #0x17
	lsl r0, r0, #0x6
	strb r1, [r4, r0]
	b _02025B16
_02025B0E:
	mov r0, #0x17
	mov r1, #0x63
	lsl r0, r0, #0x6
	strb r1, [r4, r0]
_02025B16:
	add r2, r2, #0x1
	cmp r2, #0x64
	blt _02025AC6
	mov r0, r12
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	mov r12, r1
	cmp r1, r0
	blt _02025AC4
_02025B28:
	add r0, r6, #0x0
	add r0, #0x94
	ldr r1, [r0, #0x0]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	bl rand_ALT
	add r1, r6, #0x0
	add r1, #0x94
	str r0, [r1, #0x0]
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r2, [r6, r1]
	mov r0, #0xf
	bic r2, r0
	mov r0, #0x1
	orr r0, r2
	strb r0, [r6, r1]
_02025B4C:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02025B50: .word 0x020EE958
_02025B54: .word 0x0000055C
_02025B58: .word 0x5D588B65
_02025B5C: .word 0x00269EC3

	thumb_func_start FUN_02025B60
FUN_02025B60: ; 0x02025B60
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r2, #0x0
	bl FUN_02026CC4
	cmp r4, #0x0
	blt _02025B90
	cmp r5, #0x0
	bne _02025B90
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, r4
	bge _02025B84
	mov r1, #0x0
	add r0, #0x98
	str r1, [r0, #0x0]
	pop {r3-r5, pc}
_02025B84:
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	add r0, #0x98
	sub r1, r1, r4
	str r1, [r0, #0x0]
_02025B90:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025B94
FUN_02025B94: ; 0x02025B94
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BB6
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x2
	bne _02025BB6
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x9c
	strb r2, [r1, #0x0]
_02025BB6:
	add r1, r0, #0x0
	add r1, #0x98
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BD4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025BD4
	mov r2, #0x5a
	add r1, r0, #0x0
	lsl r2, r2, #0x4
	add r1, #0x98
	str r2, [r1, #0x0]
_02025BD4:
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025BE4
	mov r1, #0x2
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025BE4:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025BE8
FUN_02025BE8: ; 0x02025BE8
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02025BFE
	mov r1, #0x1
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025BFE:
	pop {r3, pc}

	thumb_func_start FUN_02025C00
FUN_02025C00: ; 0x02025C00
	push {r3, lr}
	bl FUN_02026CC4
	add r1, r0, #0x0
	add r1, #0x9c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _02025C16
	mov r1, #0x0
	add r0, #0x9c
	strb r1, [r0, #0x0]
_02025C16:
	pop {r3, pc}

	thumb_func_start FUN_02025C18
FUN_02025C18: ; 0x02025C18
	push {r3, lr}
	bl FUN_02026CC4
	add r0, #0x9c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	beq _02025C2A
	mov r0, #0x1
	pop {r3, pc}
_02025C2A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025C30
FUN_02025C30: ; 0x02025C30
	mov r1, #0x1
	add r0, #0x9d
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025C38
FUN_02025C38: ; 0x02025C38
	add r0, #0x9d
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025C40
FUN_02025C40: ; 0x02025C40
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _02025CD0 ; =0x0000010E
	add r6, r1, #0x0
	ldrb r0, [r7, r0]
	mov r4, #0x0
	add r5, r7, #0x0
	str r0, [sp, #0x0]
_02025C50:
	add r0, r6, #0x0
	bl FUN_020239BC
	add r1, r5, #0x0
	add r1, #0xa0
	ldr r1, [r1, #0x0]
	cmp r1, r0
	beq _02025CCC
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x5
	blt _02025C50
	ldr r0, [sp, #0x0]
	cmp r0, #0x5
	blt _02025C72
	bl ErrorHandling
_02025C72:
	add r0, r6, #0x0
	bl FUN_0202398C
	ldr r1, [sp, #0x0]
	add r2, r7, #0x0
	add r2, #0xb4
	lsl r1, r1, #0x4
	add r1, r2, r1
	mov r2, #0x10
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl FUN_020239BC
	ldr r1, [sp, #0x0]
	lsl r1, r1, #0x2
	add r1, r7, r1
	add r1, #0xa0
	str r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02023A70
	ldr r1, [sp, #0x0]
	add r2, r7, r1
	mov r1, #0x41
	lsl r1, r1, #0x2
	strb r0, [r2, r1]
	add r0, r6, #0x0
	bl FUN_02023A68
	ldr r1, [sp, #0x0]
	add r2, r7, r1
	ldr r1, _02025CD4 ; =0x00000109
	strb r0, [r2, r1]
	add r0, r1, #0x5
	ldrb r0, [r7, r0]
	add r2, r0, #0x1
	add r0, r1, #0x5
	strb r2, [r7, r0]
	ldrb r0, [r7, r0]
	cmp r0, #0x5
	blo _02025CCC
	mov r2, #0x0
	add r0, r1, #0x5
	strb r2, [r7, r0]
_02025CCC:
	pop {r3-r7, pc}
	nop
_02025CD0: .word 0x0000010E
_02025CD4: .word 0x00000109

	thumb_func_start FUN_02025CD8
FUN_02025CD8: ; 0x02025CD8
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02025D38 ; =0x0000010E
	ldrb r0, [r5, r0]
	sub r0, r0, r2
	sub r4, r0, #0x1
	bpl _02025CE8
	add r4, r4, #0x5
_02025CE8:
	add r7, r5, #0x0
	lsl r0, r4, #0x4
	add r7, #0xb4
	str r0, [sp, #0x0]
	ldrh r0, [r7, r0]
	cmp r0, #0x0
	beq _02025D32
	add r0, r1, #0x0
	bl FUN_02023928
	ldr r1, [sp, #0x0]
	add r6, r0, #0x0
	add r1, r7, r1
	bl FUN_0202395C
	ldr r1, _02025D3C ; =0x00000109
	add r2, r5, r4
	ldrb r1, [r2, r1]
	add r0, r6, #0x0
	bl FUN_02023A6C
	mov r1, #0x41
	add r2, r5, r4
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	add r0, r6, #0x0
	bl FUN_02023A74
	lsl r1, r4, #0x2
	add r1, r5, r1
	add r1, #0xa0
	ldr r1, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_020239B8
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02025D32:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_02025D38: .word 0x0000010E
_02025D3C: .word 0x00000109

	thumb_func_start FUN_02025D40
FUN_02025D40: ; 0x02025D40
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025D48
FUN_02025D48: ; 0x02025D48
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0xb
	bge _02025D54
	bl ErrorHandling
_02025D54:
	cmp r4, #0x3c
	blt _02025D5C
	bl ErrorHandling
_02025D5C:
	sub r4, #0xb
	ldr r0, _02025D68 ; =0x02105C74
	lsl r1, r4, #0x1
	ldrh r0, [r0, r1]
	pop {r4, pc}
	nop
_02025D68: .word 0x02105C74

	thumb_func_start FUN_02025D6C
FUN_02025D6C: ; 0x02025D6C
	push {r4-r5}
	mov r2, #0x81
	mov r5, #0x0
	lsl r2, r2, #0x4
_02025D74:
	add r4, r0, r5
	ldrb r3, [r4, r2]
	cmp r3, #0x0
	bne _02025D88
	mov r0, #0x81
	lsl r0, r0, #0x4
	strb r1, [r4, r0]
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02025D88:
	add r5, r5, #0x1
	cmp r5, #0xc8
	blt _02025D74
	mov r0, #0x0
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_02025D94
FUN_02025D94: ; 0x02025D94
	mov r1, #0x81
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025D9A:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	bne _02025DA6
	mov r0, #0x1
	bx lr
_02025DA6:
	add r3, r3, #0x1
	cmp r3, #0xc8
	blt _02025D9A
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02025DB0
FUN_02025DB0: ; 0x02025DB0
	mov r1, #0x81
	mov r3, #0x0
	lsl r1, r1, #0x4
_02025DB6:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02025DC4
	add r3, r3, #0x1
	cmp r3, #0xc8
	blt _02025DB6
_02025DC4:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025DC8
FUN_02025DC8: ; 0x02025DC8
	add r1, r0, r1
	mov r0, #0x81
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025DD4
FUN_02025DD4: ; 0x02025DD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025F0C
	cmp r0, #0x0
	beq _02025DE6
	bl ErrorHandling
_02025DE6:
	mov r0, #0x81
	add r1, r5, r4
	lsl r0, r0, #0x4
	add r6, r4, #0x0
	ldrb r7, [r1, r0]
	cmp r4, #0xc7
	bge _02025E06
	mov r1, #0x81
	add r0, r0, #0x1
	lsl r1, r1, #0x4
_02025DFA:
	add r3, r5, r6
	ldrb r2, [r3, r0]
	add r6, r6, #0x1
	cmp r6, #0xc7
	strb r2, [r3, r1]
	blt _02025DFA
_02025E06:
	ldr r0, _02025E1C ; =0x000008D7
	mov r2, #0x0
	strb r2, [r5, r0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	sub r2, r2, #0x1
	bl FUN_02025F58
	add r0, r7, #0x0
	pop {r3-r7, pc}
	nop
_02025E1C: .word 0x000008D7

	thumb_func_start FUN_02025E20
FUN_02025E20: ; 0x02025E20
	push {r4-r7, lr}
	sub sp, #0xd4
	mov r4, #0x0
	add r5, r0, #0x0
	sub r0, r4, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x81
	lsl r0, r0, #0x4
	str r1, [sp, #0x8]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0xc
	mov r2, #0xc8
	bl MI_CpuCopy8
	ldr r2, [sp, #0x8]
	add r1, sp, #0xc
	add r0, r4, #0x0
	add r7, r1, r2
_02025E46:
	ldr r2, [sp, #0x8]
	cmp r0, r2
	beq _02025E58
	ldrb r6, [r1, #0x0]
	mov r2, #0x81
	add r3, r5, r4
	lsl r2, r2, #0x4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02025E58:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _02025E6A
	ldrb r6, [r7, #0x0]
	mov r2, #0x81
	add r3, r5, r4
	lsl r2, r2, #0x4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02025E6A:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0xc8
	blt _02025E46
	ldr r0, [sp, #0x8]
	mov r3, #0x0
	add r2, r0, #0x1
	mov r0, #0x9a
	lsl r0, r0, #0x4
_02025E7C:
	add r1, r5, r3
	ldrb r1, [r1, r0]
	cmp r2, r1
	bne _02025E88
	str r3, [sp, #0x4]
	b _02025E8E
_02025E88:
	add r3, r3, #0x1
	cmp r3, #0xf
	blt _02025E7C
_02025E8E:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02025F58
	mov r2, #0x0
	ldr r1, [sp, #0x8]
	add r0, r5, #0x0
	mvn r2, r2
	bl FUN_02025F58
	mov r1, #0x0
	ldr r0, [sp, #0x4]
	mvn r1, r1
	cmp r0, r1
	beq _02025ED6
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x8]
	cmp r0, r1
	bge _02025EC8
	add r0, r1, #0x0
	add r2, r0, #0x1
	ldr r0, [sp, #0x4]
	add sp, #0xd4
	add r1, r5, r0
	mov r0, #0x9a
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	pop {r4-r7, pc}
_02025EC8:
	add r0, r1, #0x0
	add r2, r0, #0x2
	ldr r0, [sp, #0x4]
	add r1, r5, r0
	mov r0, #0x9a
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02025ED6:
	add sp, #0xd4
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02025EDC
FUN_02025EDC: ; 0x02025EDC
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0x1
	bge _02025EEC
	bl ErrorHandling
_02025EEC:
	cmp r6, #0xf
	ble _02025EF4
	bl ErrorHandling
_02025EF4:
	sub r0, r6, #0x1
	add r1, r5, r0
	mov r0, #0x9a
	add r2, r4, #0x1
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	mov r0, #0x81
	add r1, r5, r4
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02025F0C
FUN_02025F0C: ; 0x02025F0C
	push {r3-r4}
	add r3, r1, #0x1
	mov r1, #0x9a
	mov r4, #0x0
	lsl r1, r1, #0x4
_02025F16:
	add r2, r0, r4
	ldrb r2, [r2, r1]
	cmp r3, r2
	bne _02025F24
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_02025F24:
	add r4, r4, #0x1
	cmp r4, #0xf
	blt _02025F16
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02025F30
FUN_02025F30: ; 0x02025F30
	sub r1, r1, #0x1
	cmp r1, #0xf
	bge _02025F40
	add r1, r0, r1
	mov r0, #0x9a
	mov r2, #0x0
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02025F40:
	bx lr
	.balign 4

	thumb_func_start FUN_02025F44
FUN_02025F44: ; 0x02025F44
	mov r1, #0x9a
	lsl r1, r1, #0x4
	add r0, r0, r1
	ldr r3, _02025F54 ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0xf
	bx r3
	nop
_02025F54: .word MI_CpuFill8

	thumb_func_start FUN_02025F58
FUN_02025F58: ; 0x02025F58
	push {r4-r7}
	mov r6, #0x9a
	lsl r6, r6, #0x4
	mov r4, #0x0
	add r1, r1, #0x1
	add r7, r6, #0x0
_02025F64:
	add r3, r0, r4
	ldrb r5, [r3, r7]
	cmp r5, r1
	ble _02025F76
	mov r5, #0x9a
	lsl r5, r5, #0x4
	ldrb r5, [r3, r5]
	add r5, r5, r2
	strb r5, [r3, r6]
_02025F76:
	add r4, r4, #0x1
	cmp r4, #0xf
	blt _02025F64
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02025F80
FUN_02025F80: ; 0x02025F80
	mov r1, #0x9
	mov r3, #0x0
	lsl r1, r1, #0x8
_02025F86:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02025F94
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02025F86
_02025F94:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02025F98
FUN_02025F98: ; 0x02025F98
	add r1, r0, r1
	mov r0, #0x9
	lsl r0, r0, #0x8
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02025FA4
FUN_02025FA4: ; 0x02025FA4
	push {r3-r6}
	mov r2, #0x9
	add r3, r0, r1
	lsl r2, r2, #0x8
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _02025FC2
	ldr r3, _02025FD0 ; =0x00000901
	sub r4, r3, #0x1
_02025FB6:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _02025FB6
_02025FC2:
	ldr r1, _02025FD4 ; =0x00000927
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	nop
_02025FD0: .word 0x00000901
_02025FD4: .word 0x00000927

	thumb_func_start FUN_02025FD8
FUN_02025FD8: ; 0x02025FD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020259E0
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02025FF6
	add r1, r5, r0
	mov r0, #0x9
	lsl r0, r0, #0x8
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_02025FF6:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02025FFC
FUN_02025FFC: ; 0x02025FFC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	mov r0, #0x9
	lsl r0, r0, #0x8
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_0202601E:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _02026030
	ldrb r6, [r1, #0x0]
	mov r2, #0x9
	add r3, r5, r4
	lsl r2, r2, #0x8
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02026030:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _02026042
	ldrb r6, [r7, #0x0]
	mov r2, #0x9
	add r3, r5, r4
	lsl r2, r2, #0x8
	strb r6, [r3, r2]
	add r4, r4, #0x1
_02026042:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _0202601E
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026050
FUN_02026050: ; 0x02026050
	mov r1, #0x95
	mov r3, #0x0
	lsl r1, r1, #0x4
_02026056:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _02026064
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026056
_02026064:
	add r0, r3, #0x0
	bx lr

	thumb_func_start FUN_02026068
FUN_02026068: ; 0x02026068
	add r1, r0, r1
	mov r0, #0x95
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026074
FUN_02026074: ; 0x02026074
	add r1, r0, r1
	ldr r0, _0202607C ; =0x00000978
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202607C: .word 0x00000978

	thumb_func_start FUN_02026080
FUN_02026080: ; 0x02026080
	push {r4-r7}
	add r2, r0, #0x0
	mov r0, #0x95
	add r3, r2, r1
	lsl r0, r0, #0x4
	ldrb r0, [r3, r0]
	cmp r1, #0x27
	mov r12, r0
	bge _020260AE
	ldr r7, _020260BC ; =0x00000951
	add r4, r7, #0x0
	add r5, r7, #0x0
	sub r3, r7, #0x1
	add r4, #0x28
	add r5, #0x27
_0202609E:
	add r0, r2, r1
	ldrb r6, [r0, r7]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r6, [r0, r3]
	ldrb r6, [r0, r4]
	strb r6, [r0, r5]
	blt _0202609E
_020260AE:
	ldr r0, _020260C0 ; =0x00000977
	mov r1, #0x0
	strb r1, [r2, r0]
	mov r0, r12
	pop {r4-r7}
	bx lr
	nop
_020260BC: .word 0x00000951
_020260C0: .word 0x00000977

	thumb_func_start FUN_020260C4
FUN_020260C4: ; 0x020260C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02025A00
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020260E8
	add r1, r5, r0
	mov r0, #0x95
	lsl r0, r0, #0x4
	strb r4, [r1, r0]
	add r0, #0x28
	strb r6, [r1, r0]
	mov r0, #0x1
	pop {r4-r6, pc}
_020260E8:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020260EC
FUN_020260EC: ; 0x020260EC
	push {r4-r7, lr}
	sub sp, #0x5c
	add r7, r0, #0x0
	mov r0, #0x95
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r0, r7, r0
	add r1, sp, #0x34
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r0, _02026168 ; =0x00000978
	add r1, sp, #0xc
	add r0, r7, r0
	mov r2, #0x28
	bl MI_CpuCopy8
	ldr r3, [sp, #0x0]
	add r1, sp, #0x34
	add r3, r1, r3
	mov r12, r3
	ldr r3, [sp, #0x0]
	add r2, sp, #0xc
	add r3, r2, r3
	add r0, r4, #0x0
	str r3, [sp, #0x8]
_02026124:
	ldr r3, [sp, #0x0]
	cmp r0, r3
	beq _0202613C
	ldrb r5, [r1, #0x0]
	mov r3, #0x95
	add r6, r7, r4
	lsl r3, r3, #0x4
	strb r5, [r6, r3]
	ldrb r5, [r2, #0x0]
	add r3, #0x28
	add r4, r4, #0x1
	strb r5, [r6, r3]
_0202613C:
	ldr r3, [sp, #0x4]
	cmp r0, r3
	bne _02026158
	mov r3, r12
	ldrb r5, [r3, #0x0]
	mov r3, #0x95
	add r6, r7, r4
	lsl r3, r3, #0x4
	strb r5, [r6, r3]
	ldr r3, [sp, #0x8]
	add r4, r4, #0x1
	ldrb r5, [r3, #0x0]
	ldr r3, _02026168 ; =0x00000978
	strb r5, [r6, r3]
_02026158:
	add r0, r0, #0x1
	add r1, r1, #0x1
	add r2, r2, #0x1
	cmp r0, #0x28
	blt _02026124
	add sp, #0x5c
	pop {r4-r7, pc}
	nop
_02026168: .word 0x00000978

	thumb_func_start FUN_0202616C
FUN_0202616C: ; 0x0202616C
	ldr r1, _02026184 ; =0x00000928
	mov r3, #0x0
_02026170:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _0202617E
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026170
_0202617E:
	add r0, r3, #0x0
	bx lr
	nop
_02026184: .word 0x00000928

	thumb_func_start FUN_02026188
FUN_02026188: ; 0x02026188
	add r1, r0, r1
	ldr r0, _02026190 ; =0x00000928
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026190: .word 0x00000928

	thumb_func_start FUN_02026194
FUN_02026194: ; 0x02026194
	push {r3-r6}
	ldr r2, _020261BC ; =0x00000928
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _020261B0
	ldr r3, _020261C0 ; =0x00000929
	sub r4, r3, #0x1
_020261A4:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _020261A4
_020261B0:
	ldr r1, _020261C4 ; =0x0000094F
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_020261BC: .word 0x00000928
_020261C0: .word 0x00000929
_020261C4: .word 0x0000094F

	thumb_func_start FUN_020261C8
FUN_020261C8: ; 0x020261C8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025A20
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020261E4
	add r1, r5, r0
	ldr r0, _020261E8 ; =0x00000928
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_020261E4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020261E8: .word 0x00000928

	thumb_func_start FUN_020261EC
FUN_020261EC: ; 0x020261EC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, _02026238 ; =0x00000928
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_0202620C:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _0202621C
	ldrb r6, [r1, #0x0]
	ldr r2, _02026238 ; =0x00000928
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_0202621C:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _0202622C
	ldrb r6, [r7, #0x0]
	ldr r2, _02026238 ; =0x00000928
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_0202622C:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _0202620C
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02026238: .word 0x00000928

	thumb_func_start FUN_0202623C
FUN_0202623C: ; 0x0202623C
	ldr r1, _02026254 ; =0x000008D8
	mov r3, #0x0
_02026240:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	cmp r2, #0x0
	beq _0202624E
	add r3, r3, #0x1
	cmp r3, #0x28
	blt _02026240
_0202624E:
	add r0, r3, #0x0
	bx lr
	nop
_02026254: .word 0x000008D8

	thumb_func_start FUN_02026258
FUN_02026258: ; 0x02026258
	add r1, r0, r1
	ldr r0, _02026260 ; =0x000008D8
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026260: .word 0x000008D8

	thumb_func_start FUN_02026264
FUN_02026264: ; 0x02026264
	push {r3-r6}
	ldr r2, _0202628C ; =0x000008D8
	add r3, r0, r1
	ldrb r2, [r3, r2]
	cmp r1, #0x27
	bge _02026280
	ldr r3, _02026290 ; =0x000008D9
	sub r4, r3, #0x1
_02026274:
	add r6, r0, r1
	ldrb r5, [r6, r3]
	add r1, r1, #0x1
	cmp r1, #0x27
	strb r5, [r6, r4]
	blt _02026274
_02026280:
	ldr r1, _02026294 ; =0x000008FF
	mov r3, #0x0
	strb r3, [r0, r1]
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_0202628C: .word 0x000008D8
_02026290: .word 0x000008D9
_02026294: .word 0x000008FF

	thumb_func_start FUN_02026298
FUN_02026298: ; 0x02026298
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02025A40
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020262B4
	add r1, r5, r0
	ldr r0, _020262B8 ; =0x000008D8
	strb r4, [r1, r0]
	mov r0, #0x1
	pop {r3-r5, pc}
_020262B4:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_020262B8: .word 0x000008D8

	thumb_func_start FUN_020262BC
FUN_020262BC: ; 0x020262BC
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, _02026308 ; =0x000008D8
	str r1, [sp, #0x4]
	str r2, [sp, #0x0]
	add r0, r5, r0
	add r1, sp, #0x8
	mov r2, #0x28
	mov r4, #0x0
	bl MI_CpuCopy8
	ldr r2, [sp, #0x4]
	add r1, sp, #0x8
	add r0, r4, #0x0
	add r7, r1, r2
_020262DC:
	ldr r2, [sp, #0x4]
	cmp r0, r2
	beq _020262EC
	ldrb r6, [r1, #0x0]
	ldr r2, _02026308 ; =0x000008D8
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_020262EC:
	ldr r2, [sp, #0x0]
	cmp r0, r2
	bne _020262FC
	ldrb r6, [r7, #0x0]
	ldr r2, _02026308 ; =0x000008D8
	add r3, r5, r4
	strb r6, [r3, r2]
	add r4, r4, #0x1
_020262FC:
	add r0, r0, #0x1
	add r1, r1, #0x1
	cmp r0, #0x28
	blt _020262DC
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02026308: .word 0x000008D8

	thumb_func_start FUN_0202630C
FUN_0202630C: ; 0x0202630C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	cmp r4, #0x40
	blt _0202631E
	bl ErrorHandling
_0202631E:
	ldr r0, _02026350 ; =0x0000010F
	add r1, r5, r4
	strb r7, [r1, r0]
	lsl r1, r4, #0x1
	add r1, r4, r1
	add r2, r0, #0x0
	add r1, r5, r1
	add r2, #0x40
	strb r6, [r1, r2]
	mov r2, #0xf
	lsl r2, r2, #0x8
	add r3, r6, #0x0
	and r3, r2
	asr r4, r3, #0x8
	ldr r3, [sp, #0x18]
	and r2, r3
	asr r2, r2, #0x4
	add r4, r4, r2
	add r2, r0, #0x0
	add r2, #0x41
	strb r4, [r1, r2]
	add r0, #0x42
	strb r3, [r1, r0]
	pop {r3-r7, pc}
	nop
_02026350: .word 0x0000010F

	thumb_func_start FUN_02026354
FUN_02026354: ; 0x02026354
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _02026362
	bl ErrorHandling
_02026362:
	ldr r0, _0202636C ; =0x0000010F
	add r1, r5, r4
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_0202636C: .word 0x0000010F

	thumb_func_start FUN_02026370
FUN_02026370: ; 0x02026370
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _0202637E
	bl ErrorHandling
_0202637E:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r1, r5, r0
	ldr r0, _02026398 ; =0x0000014F
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_02026398: .word 0x0000014F

	thumb_func_start FUN_0202639C
FUN_0202639C: ; 0x0202639C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _020263AA
	bl ErrorHandling
_020263AA:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r1, r5, r0
	ldr r0, _020263C4 ; =0x00000151
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_020263C4: .word 0x00000151

	thumb_func_start FUN_020263C8
FUN_020263C8: ; 0x020263C8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x40
	blt _020263D6
	bl ErrorHandling
_020263D6:
	ldr r0, _020263F0 ; =0x0000010F
	mov r1, #0x0
	add r2, r5, r4
	strb r1, [r2, r0]
	add r0, #0x40
	add r2, r5, r0
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r2, r0
	mov r2, #0x3
	bl MI_CpuFill8
	pop {r3-r5, pc}
	.balign 4
_020263F0: .word 0x0000010F

	thumb_func_start FUN_020263F4
FUN_020263F4: ; 0x020263F4
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	cmp r4, #0x10
	blt _02026406
	bl ErrorHandling
_02026406:
	lsl r2, r4, #0x1
	ldr r1, _02026440 ; =0x0000050C
	add r0, r5, r4
	add r2, r4, r2
	add r4, r5, r2
	add r2, r1, #0x0
	mov r5, #0xf
	strb r7, [r0, r1]
	add r2, #0x10
	strb r6, [r4, r2]
	lsl r5, r5, #0x8
	add r2, r6, #0x0
	and r2, r5
	asr r3, r2, #0x8
	ldr r2, [sp, #0x18]
	and r5, r2
	asr r5, r5, #0x4
	add r5, r3, r5
	add r3, r1, #0x0
	add r3, #0x11
	strb r5, [r4, r3]
	add r3, r1, #0x0
	add r3, #0x12
	strb r2, [r4, r3]
	ldr r2, [sp, #0x1c]
	add r1, #0x40
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	nop
_02026440: .word 0x0000050C

	thumb_func_start FUN_02026444
FUN_02026444: ; 0x02026444
	add r1, r0, r1
	ldr r0, _0202644C ; =0x0000050C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202644C: .word 0x0000050C

	thumb_func_start FUN_02026450
FUN_02026450: ; 0x02026450
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202646C ; =0x0000051C
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202646C: .word 0x0000051C

	thumb_func_start FUN_02026470
FUN_02026470: ; 0x02026470
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202648C ; =0x0000051E
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202648C: .word 0x0000051E

	thumb_func_start FUN_02026490
FUN_02026490: ; 0x02026490
	add r1, r0, r1
	ldr r0, _02026498 ; =0x0000054C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026498: .word 0x0000054C

	thumb_func_start FUN_0202649C
FUN_0202649C: ; 0x0202649C
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r3, #0x0
	cmp r4, #0x64
	blt _020264AE
	bl ErrorHandling
_020264AE:
	ldr r1, _020264E8 ; =0x0000055C
	add r0, r5, r4
	strb r6, [r0, r1]
	lsl r1, r4, #0x1
	add r1, r4, r1
	add r4, r5, r1
	mov r5, #0xf
	lsl r5, r5, #0x8
	add r2, r7, #0x0
	and r2, r5
	asr r3, r2, #0x8
	ldr r2, [sp, #0x18]
	ldr r1, _020264EC ; =0x00000688
	and r5, r2
	asr r5, r5, #0x4
	add r5, r3, r5
	strb r7, [r4, r1]
	add r3, r1, #0x1
	strb r5, [r4, r3]
	add r3, r1, #0x2
	strb r2, [r4, r3]
	add r2, r1, #0x0
	ldr r3, [sp, #0x1c]
	sub r2, #0x64
	strb r3, [r0, r2]
	ldr r2, [sp, #0x20]
	sub r1, #0xc8
	strb r2, [r0, r1]
	pop {r3-r7, pc}
	.balign 4
_020264E8: .word 0x0000055C
_020264EC: .word 0x00000688

	thumb_func_start FUN_020264F0
FUN_020264F0: ; 0x020264F0
	add r1, r0, r1
	ldr r0, _020264F8 ; =0x0000055C
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_020264F8: .word 0x0000055C

	thumb_func_start FUN_020264FC
FUN_020264FC: ; 0x020264FC
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _02026518 ; =0x00000688
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_02026518: .word 0x00000688

	thumb_func_start FUN_0202651C
FUN_0202651C: ; 0x0202651C
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _02026538 ; =0x0000068A
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_02026538: .word 0x0000068A

	thumb_func_start FUN_0202653C
FUN_0202653C: ; 0x0202653C
	add r1, r0, r1
	ldr r0, _02026544 ; =0x00000624
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_02026544: .word 0x00000624

	thumb_func_start FUN_02026548
FUN_02026548: ; 0x02026548
	add r1, r0, r1
	mov r0, #0x17
	lsl r0, r0, #0x6
	ldrb r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026554
FUN_02026554: ; 0x02026554
	push {r4-r7}
	ldr r3, _020265B0 ; =0x00000211
	add r7, r0, #0x0
	mov r12, r1
	mov r0, #0x0
	add r1, r7, #0x0
	sub r4, r3, #0x1
	sub r5, r3, #0x2
_02026564:
	ldrb r6, [r1, r5]
	cmp r6, #0x0
	bne _020265A0
	ldrb r6, [r1, r4]
	cmp r6, #0x0
	bne _020265A0
	ldrb r6, [r1, r3]
	cmp r6, #0x0
	bne _020265A0
	lsl r1, r0, #0x1
	add r1, r0, r1
	mov r5, #0xf
	ldr r4, _020265B4 ; =0x0000020F
	add r1, r7, r1
	mov r3, r12
	strb r3, [r1, r4]
	lsl r5, r5, #0x8
	mov r3, r12
	and r3, r5
	asr r6, r3, #0x8
	add r3, r2, #0x0
	and r3, r5
	asr r3, r3, #0x4
	add r5, r6, r3
	add r3, r4, #0x1
	strb r5, [r1, r3]
	add r3, r4, #0x2
	strb r2, [r1, r3]
	pop {r4-r7}
	bx lr
_020265A0:
	add r0, r0, #0x1
	add r1, r1, #0x3
	cmp r0, #0xff
	blt _02026564
	mov r0, #0x0
	pop {r4-r7}
	bx lr
	nop
_020265B0: .word 0x00000211
_020265B4: .word 0x0000020F

	thumb_func_start FUN_020265B8
FUN_020265B8: ; 0x020265B8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xff
	blt _020265C6
	bl ErrorHandling
_020265C6:
	ldr r0, _020265DC ; =0x0000020F
	mov r2, #0x3
	add r1, r5, r0
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r1, r0
	mov r1, #0x0
	bl MI_CpuFill8
	pop {r3-r5, pc}
	nop
_020265DC: .word 0x0000020F

	thumb_func_start FUN_020265E0
FUN_020265E0: ; 0x020265E0
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _020265FC ; =0x0000020F
	ldrb r2, [r1, r0]
	add r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x8
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_020265FC: .word 0x0000020F

	thumb_func_start FUN_02026600
FUN_02026600: ; 0x02026600
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, _0202661C ; =0x00000211
	ldrb r2, [r1, r0]
	sub r0, r0, #0x1
	ldrb r0, [r1, r0]
	lsl r1, r0, #0x4
	mov r0, #0xf
	lsl r0, r0, #0x8
	and r0, r1
	add r0, r2, r0
	bx lr
	nop
_0202661C: .word 0x00000211

	thumb_func_start FUN_02026620
FUN_02026620: ; 0x02026620
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bne _02026630
	mov r0, #0x1
	bx lr
_02026630:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02026634
FUN_02026634: ; 0x02026634
	mov r2, #0x9b
	lsl r2, r2, #0x4
	ldrb r3, [r0, r2]
	mov r1, #0xf0
	bic r3, r1
	mov r1, #0x10
	orr r1, r3
	strb r1, [r0, r2]
	bx lr
	.balign 4

	thumb_func_start FUN_02026648
FUN_02026648: ; 0x02026648
	mov r1, #0x9b
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr

	thumb_func_start FUN_02026654
FUN_02026654: ; 0x02026654
	mov r2, #0x9b
	lsl r2, r2, #0x4
	ldrb r3, [r0, r2]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r0, r2]
	bx lr
	.balign 4

	thumb_func_start FUN_02026664
FUN_02026664: ; 0x02026664
	push {r3-r4}
	cmp r1, #0x2c
	blt _0202667E
	cmp r1, #0x3b
	bgt _0202667E
	ldr r2, _02026684 ; =0x0000080C
	mov r3, #0x1
	sub r1, #0x2c
	ldr r4, [r0, r2]
	lsl r3, r1
	add r1, r4, #0x0
	orr r1, r3
	str r1, [r0, r2]
_0202667E:
	pop {r3-r4}
	bx lr
	nop
_02026684: .word 0x0000080C

	thumb_func_start FUN_02026688
FUN_02026688: ; 0x02026688
	cmp r1, #0x2c
	blt _02026690
	cmp r1, #0x3b
	ble _02026694
_02026690:
	mov r0, #0x1
	bx lr
_02026694:
	ldr r2, _020266AC ; =0x0000080C
	sub r1, #0x2c
	ldr r3, [r0, r2]
	mov r0, #0x1
	add r2, r0, #0x0
	lsl r2, r1
	add r1, r3, #0x0
	tst r1, r2
	beq _020266A8
	mov r0, #0x0
_020266A8:
	bx lr
	nop
_020266AC: .word 0x0000080C

	thumb_func_start FUN_020266B0
FUN_020266B0: ; 0x020266B0
	ldr r1, _020266C4 ; =0x000009AF
	ldrb r2, [r0, r1]
	cmp r2, #0x63
	blo _020266BE
	mov r2, #0x0
	strb r2, [r0, r1]
	bx lr
_020266BE:
	add r2, r2, #0x1
	strb r2, [r0, r1]
	bx lr
	.balign 4
_020266C4: .word 0x000009AF

	thumb_func_start FUN_020266C8
FUN_020266C8: ; 0x020266C8
	ldr r1, _020266D0 ; =0x000009AF
	ldrb r0, [r0, r1]
	bx lr
	nop
_020266D0: .word 0x000009AF

	thumb_func_start FUN_020266D4
FUN_020266D4: ; 0x020266D4
	ldr r3, _020266DC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x94
	bx r3
	.balign 4
_020266DC: .word MI_CpuFill8

	thumb_func_start FUN_020266E0
FUN_020266E0: ; 0x020266E0
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x2d
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r0, #0x2d
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x8c
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x8e
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x90
	strb r1, [r0, #0x0]
	add r4, #0x91
	strb r1, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02026714
FUN_02026714: ; 0x02026714
	mov r1, #0x0
	add r0, #0x91
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202671C
FUN_0202671C: ; 0x0202671C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, #0x20
	blt _0202672E
	bl ErrorHandling
_0202672E:
	cmp r6, #0x20
	blt _02026736
	bl ErrorHandling
_02026736:
	ldr r0, [sp, #0x18]
	cmp r0, #0x20
	blt _02026740
	bl ErrorHandling
_02026740:
	cmp r5, #0x0
	bne _02026748
	bl ErrorHandling
_02026748:
	cmp r4, #0x0
	beq _02026774
	cmp r4, #0x10
	bge _02026762
	sub r1, r4, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	strb r6, [r5, r0]
	ldr r1, [sp, #0x18]
	add r0, r5, r0
	strb r1, [r0, #0x1]
	strb r7, [r0, #0x2]
	pop {r3-r7, pc}
_02026762:
	sub r4, #0x10
	lsl r2, r4, #0x1
	add r0, r5, r2
	add r0, #0x2d
	strb r6, [r0, #0x0]
	add r0, r5, r2
	ldr r1, [sp, #0x18]
	add r0, #0x2e
	strb r1, [r0, #0x0]
_02026774:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026778
FUN_02026778: ; 0x02026778
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_020267C4
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r3, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_0202671C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026798
FUN_02026798: ; 0x02026798
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blt _020267A8
	mov r0, #0x5
	bx lr
_020267A8:
	cmp r0, #0xa
	blt _020267B0
	mov r0, #0x4
	bx lr
_020267B0:
	cmp r0, #0x3
	blt _020267B8
	mov r0, #0x3
	bx lr
_020267B8:
	cmp r0, #0x1
	blt _020267C0
	mov r0, #0x2
	bx lr
_020267C0:
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020267C4
FUN_020267C4: ; 0x020267C4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _020267D2
	bl ErrorHandling
_020267D2:
	cmp r5, #0x0
	bne _020267DE
	add r0, r4, #0x0
	bl FUN_02026798
	pop {r3-r5, pc}
_020267DE:
	cmp r5, #0x10
	bge _020267EE
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	add r0, r4, r0
	ldrb r0, [r0, #0x2]
	pop {r3-r5, pc}
_020267EE:
	sub r5, #0x10
	lsl r1, r5, #0x1
	add r0, r4, r1
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202680A
	add r0, r4, r1
	add r0, #0x2e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202680A
	mov r0, #0x6
	pop {r3-r5, pc}
_0202680A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026810
FUN_02026810: ; 0x02026810
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0202681E
	bl ErrorHandling
_0202681E:
	cmp r5, #0x0
	bne _02026826
	mov r0, #0xf
	pop {r3-r5, pc}
_02026826:
	cmp r5, #0x10
	bge _02026834
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	ldrb r0, [r4, r0]
	pop {r3-r5, pc}
_02026834:
	sub r5, #0x10
	lsl r0, r5, #0x1
	add r0, r4, r0
	add r0, #0x2d
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02026840
FUN_02026840: ; 0x02026840
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x20
	blt _0202684E
	bl ErrorHandling
_0202684E:
	cmp r5, #0x0
	bne _02026856
	mov r0, #0xc
	pop {r3-r5, pc}
_02026856:
	cmp r5, #0x10
	bge _02026866
	sub r1, r5, #0x1
	lsl r0, r1, #0x1
	add r0, r1, r0
	add r0, r4, r0
	ldrb r0, [r0, #0x1]
	pop {r3-r5, pc}
_02026866:
	sub r5, #0x10
	lsl r0, r5, #0x1
	add r0, r4, r0
	add r0, #0x2e
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026874
FUN_02026874: ; 0x02026874
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blo _02026884
	mov r0, #0x0
	bx lr
_02026884:
	cmp r0, #0xa
	blo _0202688C
	mov r0, #0x6
	bx lr
_0202688C:
	cmp r0, #0x3
	blo _02026894
	mov r0, #0xb
	bx lr
_02026894:
	cmp r0, #0x1
	blo _0202689C
	mov r0, #0xf
	bx lr
_0202689C:
	mov r0, #0x10
	bx lr

	thumb_func_start FUN_020268A0
FUN_020268A0: ; 0x020268A0
	add r0, #0x88
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blo _020268B0
	mov r0, #0xf
	bx lr
_020268B0:
	cmp r0, #0xa
	blo _020268B8
	mov r0, #0xf
	bx lr
_020268B8:
	cmp r0, #0x3
	blo _020268C0
	mov r0, #0xf
	bx lr
_020268C0:
	cmp r0, #0x1
	blo _020268C8
	mov r0, #0xc
	bx lr
_020268C8:
	mov r0, #0xa
	bx lr

	thumb_func_start FUN_020268CC
FUN_020268CC: ; 0x020268CC
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_020268D4
FUN_020268D4: ; 0x020268D4
	push {r3, lr}
	bl FUN_020269A0
	cmp r0, #0x4
	bne _020268E2
	mov r0, #0x1
	pop {r3, pc}
_020268E2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020268E8
FUN_020268E8: ; 0x020268E8
	ldr r3, [r0, #0x0]
	ldr r2, _020268F8 ; =0xFFF00000
	and r3, r2
	ldr r2, _020268FC ; =0x000FFFFF
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020268F8: .word 0xFFF00000
_020268FC: .word 0x000FFFFF

	thumb_func_start FUN_02026900
FUN_02026900: ; 0x02026900
	ldr r0, [r0, #0x4]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026908
FUN_02026908: ; 0x02026908
	push {r3-r4}
	ldr r2, [r0, #0x4]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _0202692C ; =0x000F423F
	cmp r4, r1
	bhs _02026926
	ldr r1, _02026930 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026934 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x4]
_02026926:
	pop {r3-r4}
	bx lr
	nop
_0202692C: .word 0x000F423F
_02026930: .word 0xFFF00000
_02026934: .word 0x000FFFFF

	thumb_func_start FUN_02026938
FUN_02026938: ; 0x02026938
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026940
FUN_02026940: ; 0x02026940
	push {r3-r4}
	ldr r2, [r0, #0x8]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026964 ; =0x000F423F
	cmp r4, r1
	bhs _0202695E
	ldr r1, _02026968 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _0202696C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x8]
_0202695E:
	pop {r3-r4}
	bx lr
	nop
_02026964: .word 0x000F423F
_02026968: .word 0xFFF00000
_0202696C: .word 0x000FFFFF

	thumb_func_start FUN_02026970
FUN_02026970: ; 0x02026970
	push {r3-r4}
	ldr r2, [r0, #0xc]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026994 ; =0x000F423F
	cmp r4, r1
	bhs _0202698E
	ldr r1, _02026998 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _0202699C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0xc]
_0202698E:
	pop {r3-r4}
	bx lr
	nop
_02026994: .word 0x000F423F
_02026998: .word 0xFFF00000
_0202699C: .word 0x000FFFFF

	thumb_func_start FUN_020269A0
FUN_020269A0: ; 0x020269A0
	ldr r0, [r0, #0x38]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	cmp r0, #0x32
	blt _020269AE
	mov r0, #0x4
	bx lr
_020269AE:
	cmp r0, #0xa
	blt _020269B6
	mov r0, #0x3
	bx lr
_020269B6:
	cmp r0, #0x3
	blt _020269BE
	mov r0, #0x2
	bx lr
_020269BE:
	cmp r0, #0x1
	blt _020269C6
	mov r0, #0x1
	bx lr
_020269C6:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020269CC
FUN_020269CC: ; 0x020269CC
	ldr r0, [r0, #0x38]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_020269D4
FUN_020269D4: ; 0x020269D4
	push {r3-r4}
	ldr r2, [r0, #0x38]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _020269F8 ; =0x000F423F
	cmp r4, r1
	bhs _020269F2
	ldr r1, _020269FC ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026A00 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x38]
_020269F2:
	pop {r3-r4}
	bx lr
	nop
_020269F8: .word 0x000F423F
_020269FC: .word 0xFFF00000
_02026A00: .word 0x000FFFFF

	thumb_func_start FUN_02026A04
FUN_02026A04: ; 0x02026A04
	ldr r0, [r0, #0x10]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026A0C
FUN_02026A0C: ; 0x02026A0C
	push {r4-r5}
	cmp r1, #0x0
	ble _02026A2C
	ldr r4, [r0, #0x10]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026A44 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026A2C
	ldr r1, _02026A48 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x10]
	pop {r4-r5}
	bx lr
_02026A2C:
	ldr r3, [r0, #0x10]
	ldr r2, _02026A48 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026A4C ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x10]
	pop {r4-r5}
	bx lr
	.balign 4
_02026A44: .word 0x000F423F
_02026A48: .word 0xFFF00000
_02026A4C: .word 0x000FFFFF

	thumb_func_start FUN_02026A50
FUN_02026A50: ; 0x02026A50
	ldr r0, [r0, #0x14]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026A58
FUN_02026A58: ; 0x02026A58
	push {r4-r5}
	cmp r1, #0x0
	ble _02026A78
	ldr r4, [r0, #0x14]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026A90 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026A78
	ldr r1, _02026A94 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x14]
	pop {r4-r5}
	bx lr
_02026A78:
	ldr r3, [r0, #0x14]
	ldr r2, _02026A94 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026A98 ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x14]
	pop {r4-r5}
	bx lr
	.balign 4
_02026A90: .word 0x000F423F
_02026A94: .word 0xFFF00000
_02026A98: .word 0x000FFFFF

	thumb_func_start FUN_02026A9C
FUN_02026A9C: ; 0x02026A9C
	push {r4-r5}
	cmp r1, #0x0
	ble _02026ABC
	ldr r4, [r0, #0x18]
	lsl r2, r4, #0xc
	lsr r5, r2, #0xc
	ldr r2, _02026AD4 ; =0x000F423F
	sub r3, r2, r1
	cmp r5, r3
	bls _02026ABC
	ldr r1, _02026AD8 ; =0xFFF00000
	and r1, r4
	orr r1, r2
	str r1, [r0, #0x18]
	pop {r4-r5}
	bx lr
_02026ABC:
	ldr r3, [r0, #0x18]
	ldr r2, _02026AD8 ; =0xFFF00000
	and r2, r3
	lsl r3, r3, #0xc
	lsr r3, r3, #0xc
	add r3, r3, r1
	ldr r1, _02026ADC ; =0x000FFFFF
	and r1, r3
	orr r1, r2
	str r1, [r0, #0x18]
	pop {r4-r5}
	bx lr
	.balign 4
_02026AD4: .word 0x000F423F
_02026AD8: .word 0xFFF00000
_02026ADC: .word 0x000FFFFF

	thumb_func_start FUN_02026AE0
FUN_02026AE0: ; 0x02026AE0
	ldr r0, [r0, #0x1c]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026AE8
FUN_02026AE8: ; 0x02026AE8
	push {r3-r4}
	ldr r2, [r0, #0x1c]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B0C ; =0x000F423F
	cmp r4, r1
	bhs _02026B06
	ldr r1, _02026B10 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B14 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x1c]
_02026B06:
	pop {r3-r4}
	bx lr
	nop
_02026B0C: .word 0x000F423F
_02026B10: .word 0xFFF00000
_02026B14: .word 0x000FFFFF

	thumb_func_start FUN_02026B18
FUN_02026B18: ; 0x02026B18
	ldr r0, [r0, #0x20]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B20
FUN_02026B20: ; 0x02026B20
	push {r3-r4}
	ldr r2, [r0, #0x20]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B44 ; =0x000F423F
	cmp r4, r1
	bhs _02026B3E
	ldr r1, _02026B48 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B4C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x20]
_02026B3E:
	pop {r3-r4}
	bx lr
	nop
_02026B44: .word 0x000F423F
_02026B48: .word 0xFFF00000
_02026B4C: .word 0x000FFFFF

	thumb_func_start FUN_02026B50
FUN_02026B50: ; 0x02026B50
	ldr r0, [r0, #0x24]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B58
FUN_02026B58: ; 0x02026B58
	push {r3-r4}
	ldr r2, [r0, #0x24]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026B7C ; =0x000F423F
	cmp r4, r1
	bhs _02026B76
	ldr r1, _02026B80 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026B84 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x24]
_02026B76:
	pop {r3-r4}
	bx lr
	nop
_02026B7C: .word 0x000F423F
_02026B80: .word 0xFFF00000
_02026B84: .word 0x000FFFFF

	thumb_func_start FUN_02026B88
FUN_02026B88: ; 0x02026B88
	ldr r0, [r0, #0x28]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026B90
FUN_02026B90: ; 0x02026B90
	push {r3-r4}
	ldr r2, [r0, #0x28]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026BB4 ; =0x000F423F
	cmp r4, r1
	bhs _02026BAE
	ldr r1, _02026BB8 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026BBC ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x28]
_02026BAE:
	pop {r3-r4}
	bx lr
	nop
_02026BB4: .word 0x000F423F
_02026BB8: .word 0xFFF00000
_02026BBC: .word 0x000FFFFF

	thumb_func_start FUN_02026BC0
FUN_02026BC0: ; 0x02026BC0
	ldr r0, [r0, #0x2c]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026BC8
FUN_02026BC8: ; 0x02026BC8
	push {r3-r4}
	ldr r2, [r0, #0x2c]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026BEC ; =0x000F423F
	cmp r4, r1
	bhs _02026BE6
	ldr r1, _02026BF0 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026BF4 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x2c]
_02026BE6:
	pop {r3-r4}
	bx lr
	nop
_02026BEC: .word 0x000F423F
_02026BF0: .word 0xFFF00000
_02026BF4: .word 0x000FFFFF

	thumb_func_start FUN_02026BF8
FUN_02026BF8: ; 0x02026BF8
	ldr r0, [r0, #0x30]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026C00
FUN_02026C00: ; 0x02026C00
	push {r3-r4}
	ldr r2, [r0, #0x30]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026C24 ; =0x000F423F
	cmp r4, r1
	bhs _02026C1E
	ldr r1, _02026C28 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026C2C ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x30]
_02026C1E:
	pop {r3-r4}
	bx lr
	nop
_02026C24: .word 0x000F423F
_02026C28: .word 0xFFF00000
_02026C2C: .word 0x000FFFFF

	thumb_func_start FUN_02026C30
FUN_02026C30: ; 0x02026C30
	ldr r0, [r0, #0x34]
	lsl r0, r0, #0xc
	lsr r0, r0, #0xc
	bx lr

	thumb_func_start FUN_02026C38
FUN_02026C38: ; 0x02026C38
	push {r3-r4}
	ldr r2, [r0, #0x34]
	lsl r1, r2, #0xc
	lsr r4, r1, #0xc
	ldr r1, _02026C5C ; =0x000F423F
	cmp r4, r1
	bhs _02026C56
	ldr r1, _02026C60 ; =0xFFF00000
	add r3, r2, #0x0
	and r3, r1
	ldr r1, _02026C64 ; =0x000FFFFF
	add r2, r4, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x34]
_02026C56:
	pop {r3-r4}
	bx lr
	nop
_02026C5C: .word 0x000F423F
_02026C60: .word 0xFFF00000
_02026C64: .word 0x000FFFFF

	thumb_func_start FUN_02026C68
FUN_02026C68: ; 0x02026C68
	push {r3-r4}
	add r4, r0, #0x0
	add r4, #0x8c
	strh r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x8e
	strh r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x90
	strb r3, [r1, #0x0]
	mov r1, #0x1
	add r0, #0x91
	strb r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02026C88
FUN_02026C88: ; 0x02026C88
	add r0, #0x8c
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026C90
FUN_02026C90: ; 0x02026C90
	add r0, #0x8e
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026C98
FUN_02026C98: ; 0x02026C98
	add r0, #0x90
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026CA0
FUN_02026CA0: ; 0x02026CA0
	add r0, #0x91
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02026CA8
FUN_02026CA8: ; 0x02026CA8
	ldr r3, _02026CB0 ; =FUN_02022610
	mov r1, #0xc
	bx r3
	nop
_02026CB0: .word FUN_02022610

	thumb_func_start FUN_02026CB4
FUN_02026CB4: ; 0x02026CB4
	push {r3, lr}
	mov r1, #0xc
	bl FUN_02022610
	add r0, #0x50
	pop {r3, pc}

	thumb_func_start FUN_02026CC0
FUN_02026CC0: ; 0x02026CC0
	add r0, #0x50
	bx lr

	thumb_func_start FUN_02026CC4
FUN_02026CC4: ; 0x02026CC4
	ldr r3, _02026CCC ; =FUN_02022610
	mov r1, #0xc
	bx r3
	nop
_02026CCC: .word FUN_02022610

	thumb_func_start FUN_02026CD0
FUN_02026CD0: ; 0x02026CD0
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r3, #0x0
	bl FUN_020671BC
	add r2, r5, #0x0
	strh r0, [r5, #0x8]
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0xa
	bl FUN_020671BC
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r1, #0x33
	strb r0, [r1, #0x0]
	add r0, r5, #0x0
	add r0, #0x31
	strb r6, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x32
	strb r7, [r0, #0x0]
	add r1, sp, #0x8
	mov r0, #0x10
	ldrsb r0, [r1, r0]
	add r5, #0x30
	strb r0, [r5, #0x0]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02026D34
FUN_02026D34: ; 0x02026D34
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x8
	bl MOD17_021DB858
	add r0, r4, #0x0
	bl MOD17_021DB7E8
	add r4, r0, #0x0
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02026D5E
	bl ErrorHandling
_02026D5E:
	mov r0, #0x1
	ldr r1, [sp, #0x8]
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _02026D6C
	bl ErrorHandling
_02026D6C:
	mov r0, #0x7f
	mvn r0, r0
	cmp r4, r0
	bgt _02026D78
	bl ErrorHandling
_02026D78:
	lsl r0, r4, #0x18
	asr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026CD0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02026D98
FUN_02026D98: ; 0x02026D98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r5, #0x0
	add r4, r2, #0x0
	add r1, #0x20
	mov r2, #0x8
	bl FUN_02021EF0
	add r5, #0x34
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02026DB0
FUN_02026DB0: ; 0x02026DB0
	strb r1, [r0, #0x0]
	ldr r1, _02026DC0 ; =0xFFFFFFF0
	strb r2, [r0, #0x1]
	strb r3, [r0, #0x2]
	add r1, sp
	ldrb r1, [r1, #0x10]
	strb r1, [r0, #0x3]
	bx lr
	.balign 4
_02026DC0: .word 0xFFFFFFF0

	thumb_func_start FUN_02026DC4
FUN_02026DC4: ; 0x02026DC4
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	cmp r4, #0x3d
	blo _02026DD4
	bl ErrorHandling
_02026DD4:
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1d
	sub r1, r1, r2
	mov r0, #0x1d
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1a
	lsr r1, r0, #0x18
	lsr r0, r4, #0x3
	lsl r0, r0, #0x18
	mov r2, #0xf
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r6, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026E08
FUN_02026E08: ; 0x02026E08
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3d
	blo _02026E16
	bl ErrorHandling
_02026E16:
	lsr r3, r4, #0x1f
	lsl r2, r4, #0x1d
	lsr r0, r4, #0x3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x16
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	ldr r0, [r5, r0]
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1a
	add r2, r0, #0x0
	lsr r1, r1, #0x18
	lsr r2, r1
	mov r0, #0xf
	and r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x9
	bls _02026E44
	mov r0, #0x9
_02026E44:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026E48
FUN_02026E48: ; 0x02026E48
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x2
	blo _02026E58
	bl ErrorHandling
_02026E58:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsr r0, r6, #0x5
	lsl r0, r0, #0x18
	mov r2, #0x1
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r4, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026E88
FUN_02026E88: ; 0x02026E88
	lsr r2, r1, #0x5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	ldr r3, [r0, r2]
	lsr r2, r1, #0x1f
	lsl r1, r1, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r3, #0x0
	lsr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_02026EB0
FUN_02026EB0: ; 0x02026EB0
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x12
	bls _02026EC0
	bl ErrorHandling
_02026EC0:
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x18
	lsr r0, r6, #0x2
	lsl r0, r0, #0x18
	mov r2, #0xff
	lsr r0, r0, #0x16
	lsl r2, r1
	ldr r3, [r5, r0]
	mvn r2, r2
	and r2, r3
	str r2, [r5, r0]
	add r2, r4, #0x0
	ldr r3, [r5, r0]
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	str r1, [r5, r0]
	pop {r4-r6, pc}

	thumb_func_start FUN_02026EF4
FUN_02026EF4: ; 0x02026EF4
	lsr r2, r1, #0x2
	lsl r2, r2, #0x18
	lsr r2, r2, #0x16
	ldr r0, [r0, r2]
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1e
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x18
	lsr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_02026F18
FUN_02026F18: ; 0x02026F18
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02026F20:
	lsl r1, r4, #0x18
	add r0, r6, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	cmp r0, #0x12
	beq _02026F30
	add r5, r5, #0x1
_02026F30:
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _02026F20
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	pop {r4-r6, pc}

	thumb_func_start FUN_02026F3C
FUN_02026F3C: ; 0x02026F3C
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x2
	add r4, r2, #0x0
	bl FUN_02068E14
	mov r1, #0x80
	strb r1, [r5, #0x0]
	mov r1, #0x28
	sub r1, r1, r0
	mov r0, #0x8d
	sub r0, r0, r1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	add r0, #0x28
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02026F60
FUN_02026F60: ; 0x02026F60
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r6, _02026FC8 ; =0x00001234
	mov r4, #0x0
	add r5, r7, #0x0
_02026F6A:
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x74
	bl memset
	str r6, [r5, #0x0]
	add r4, r4, #0x1
	add r5, #0x74
	cmp r4, #0xb
	blt _02026F6A
	ldr r0, _02026FCC ; =0x000004FC
	mov r6, #0x0
	add r4, r7, r0
	add r5, r7, #0x0
_02026F86:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x98
	bl memset
	ldr r1, _02026FC8 ; =0x00001234
	ldr r0, _02026FCC ; =0x000004FC
	add r6, r6, #0x1
	str r1, [r5, r0]
	add r4, #0x98
	add r5, #0x98
	cmp r6, #0x5
	blt _02026F86
	ldr r0, _02026FD0 ; =0x000007F4
	mov r1, #0x0
	add r0, r7, r0
	mov r2, #0x40
	bl memset
	ldr r5, _02026FD4 ; =0x0000081C
	mov r4, #0x0
	mov r6, #0x12
_02026FB2:
	lsl r2, r4, #0x18
	add r0, r7, r5
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026EB0
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _02026FB2
	pop {r3-r7, pc}
	nop
_02026FC8: .word 0x00001234
_02026FCC: .word 0x000004FC
_02026FD0: .word 0x000007F4
_02026FD4: .word 0x0000081C

	thumb_func_start FUN_02026FD8
FUN_02026FD8: ; 0x02026FD8
	ldr r0, _02026FDC ; =0x00000834
	bx lr
	.balign 4
_02026FDC: .word 0x00000834

	thumb_func_start FUN_02026FE0
FUN_02026FE0: ; 0x02026FE0
	mov r0, #0x74
	bx lr

	thumb_func_start FUN_02026FE4
FUN_02026FE4: ; 0x02026FE4
	mov r0, #0x98
	bx lr

	thumb_func_start FUN_02026FE8
FUN_02026FE8: ; 0x02026FE8
	push {r4, lr}
	mov r1, #0x98
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x98
	add r4, r0, #0x0
	bl memset
	ldr r0, _02027004 ; =0x00001234
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02027004: .word 0x00001234

	thumb_func_start FUN_02027008
FUN_02027008: ; 0x02027008
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0xb
	blt _02027016
	bl ErrorHandling
_02027016:
	mov r0, #0x74
	add r4, r6, #0x0
	mul r4, r0
	ldr r1, [r5, r4]
	ldr r0, _0202703C ; =0x00001234
	cmp r1, r0
	beq _0202702A
	ldr r0, _02027040 ; =0x00002345
	cmp r1, r0
	bne _0202702E
_0202702A:
	mov r0, #0x1
	b _02027030
_0202702E:
	mov r0, #0x0
_02027030:
	cmp r0, #0x0
	bne _02027038
	bl ErrorHandling
_02027038:
	add r0, r5, r4
	pop {r4-r6, pc}
	.balign 4
_0202703C: .word 0x00001234
_02027040: .word 0x00002345

	thumb_func_start FUN_02027044
FUN_02027044: ; 0x02027044
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	cmp r6, #0x5
	blt _02027052
	bl ErrorHandling
_02027052:
	mov r0, #0x98
	add r4, r6, #0x0
	mul r4, r0
	ldr r0, _02027080 ; =0x000004FC
	add r1, r5, r4
	ldr r1, [r1, r0]
	ldr r0, _02027084 ; =0x00001234
	cmp r1, r0
	beq _0202706A
	ldr r0, _02027088 ; =0x00002345
	cmp r1, r0
	bne _0202706E
_0202706A:
	mov r0, #0x1
	b _02027070
_0202706E:
	mov r0, #0x0
_02027070:
	cmp r0, #0x0
	bne _02027078
	bl ErrorHandling
_02027078:
	ldr r0, _02027080 ; =0x000004FC
	add r0, r5, r0
	add r0, r0, r4
	pop {r4-r6, pc}
	.balign 4
_02027080: .word 0x000004FC
_02027084: .word 0x00001234
_02027088: .word 0x00002345

	thumb_func_start FUN_0202708C
FUN_0202708C: ; 0x0202708C
	ldr r1, _02027094 ; =0x000007F4
	add r0, r0, r1
	bx lr
	nop
_02027094: .word 0x000007F4

	thumb_func_start FUN_02027098
FUN_02027098: ; 0x02027098
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xb
	blt _020270A6
	bl ErrorHandling
_020270A6:
	mov r0, #0x74
	mul r0, r4
	add r0, r5, r0
	bl FUN_0202729C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020270B4
FUN_020270B4: ; 0x020270B4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x5
	blt _020270C2
	bl ErrorHandling
_020270C2:
	ldr r0, _020270D4 ; =0x000004FC
	add r1, r5, r0
	mov r0, #0x98
	mul r0, r4
	add r0, r1, r0
	bl FUN_020276D8
	pop {r3-r5, pc}
	nop
_020270D4: .word 0x000004FC

	thumb_func_start FUN_020270D8
FUN_020270D8: ; 0x020270D8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r2, #0x0
	mov r4, #0x1
	bl FUN_02027114
	cmp r6, #0x3d
	bhs _020270F2
	add r0, r0, r5
	cmp r0, #0x9
	bls _020270FA
	mov r4, #0x0
	b _020270FA
_020270F2:
	add r0, r0, r5
	cmp r0, #0x1
	bls _020270FA
	mov r4, #0x0
_020270FA:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02027100
FUN_02027100: ; 0x02027100
	push {r3, lr}
	bl FUN_0202714C
	cmp r0, #0x12
	beq _0202710E
	mov r0, #0x1
	pop {r3, pc}
_0202710E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02027114
FUN_02027114: ; 0x02027114
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x64
	blo _02027122
	bl ErrorHandling
_02027122:
	cmp r5, #0x3d
	bhs _02027132
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	pop {r3-r5, pc}
_02027132:
	bhs _02027138
	bl ErrorHandling
_02027138:
	sub r5, #0x3d
	lsl r0, r5, #0x18
	lsr r1, r0, #0x18
	add r4, #0x20
	lsl r1, r1, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E88
	pop {r3-r5, pc}

	thumb_func_start FUN_0202714C
FUN_0202714C: ; 0x0202714C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x12
	blo _0202715A
	bl ErrorHandling
_0202715A:
	add r5, #0x28
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	pop {r3-r5, pc}

	thumb_func_start FUN_02027168
FUN_02027168: ; 0x02027168
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02027170:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02027114
	add r4, r4, #0x1
	add r5, r5, r0
	cmp r4, #0x64
	blt _02027170
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02027184
FUN_02027184: ; 0x02027184
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_0202718C:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202714C
	cmp r0, #0x12
	beq _0202719A
	add r5, r5, #0x1
_0202719A:
	add r4, r4, #0x1
	cmp r4, #0x12
	blt _0202718C
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020271A4
FUN_020271A4: ; 0x020271A4
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x64
	blo _020271B4
	bl ErrorHandling
_020271B4:
	cmp r4, #0x3d
	bhs _020271DA
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	add r0, r0, r6
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	cmp r1, #0x9
	bls _020271CE
	mov r1, #0x9
_020271CE:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026DC4
	pop {r4-r6, pc}
_020271DA:
	add r0, r5, #0x0
	lsl r1, r4, #0x18
	add r0, #0x20
	lsr r1, r1, #0x18
	bl FUN_02026E88
	add r0, r0, r6
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x1
	bls _020271F2
	mov r6, #0x1
_020271F2:
	cmp r4, #0x3d
	bhs _020271FA
	bl ErrorHandling
_020271FA:
	sub r4, #0x3d
	lsl r0, r4, #0x18
	lsr r2, r0, #0x18
	add r5, #0x20
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026E48
	pop {r4-r6, pc}

	thumb_func_start FUN_02027210
FUN_02027210: ; 0x02027210
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x64
	blo _02027220
	bl ErrorHandling
_02027220:
	cmp r4, #0x3d
	bhs _02027248
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_02026E08
	cmp r0, r6
	bls _0202723A
	sub r0, r0, r6
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	b _0202723C
_0202723A:
	mov r1, #0x0
_0202723C:
	lsl r2, r4, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026DC4
	pop {r4-r6, pc}
_02027248:
	bhs _0202724E
	bl ErrorHandling
_0202724E:
	sub r4, #0x3d
	lsl r0, r4, #0x18
	lsr r2, r0, #0x18
	add r5, #0x20
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	mov r1, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026E48
	pop {r4-r6, pc}

	thumb_func_start FUN_02027264
FUN_02027264: ; 0x02027264
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x12
	blo _02027272
	bl ErrorHandling
_02027272:
	add r0, r5, #0x0
	lsl r1, r4, #0x18
	add r0, #0x28
	lsr r1, r1, #0x18
	bl FUN_02026EF4
	cmp r0, #0x12
	bne _02027298
	add r0, r5, #0x0
	add r0, #0x28
	bl FUN_02026F18
	lsl r2, r4, #0x18
	add r5, #0x28
	add r1, r0, #0x0
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02026EB0
_02027298:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202729C
FUN_0202729C: ; 0x0202729C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020272CC ; =0x00001234
	cmp r1, r0
	beq _020272AE
	ldr r0, _020272D0 ; =0x00002345
	cmp r1, r0
	bne _020272B2
_020272AE:
	mov r0, #0x1
	b _020272B4
_020272B2:
	mov r0, #0x0
_020272B4:
	cmp r0, #0x0
	bne _020272BC
	bl ErrorHandling
_020272BC:
	ldr r1, [r4, #0x0]
	ldr r0, _020272D0 ; =0x00002345
	cmp r1, r0
	bne _020272C8
	mov r0, #0x1
	pop {r4, pc}
_020272C8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020272CC: .word 0x00001234
_020272D0: .word 0x00002345

	thumb_func_start FUN_020272D4
FUN_020272D4: ; 0x020272D4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027304 ; =0x00001234
	cmp r1, r0
	beq _020272E6
	ldr r0, _02027308 ; =0x00002345
	cmp r1, r0
	bne _020272EA
_020272E6:
	mov r0, #0x1
	b _020272EC
_020272EA:
	mov r0, #0x0
_020272EC:
	cmp r0, #0x0
	bne _020272F4
	bl ErrorHandling
_020272F4:
	ldr r0, _02027308 ; =0x00002345
	str r0, [r4, #0x0]
	ldr r0, _0202730C ; =0x020ECAC4
	add r4, #0x71
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027304: .word 0x00001234
_02027308: .word 0x00002345
_0202730C: .word 0x020ECAC4

	thumb_func_start FUN_02027310
FUN_02027310: ; 0x02027310
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027340 ; =0x00001234
	cmp r1, r0
	beq _02027322
	ldr r0, _02027344 ; =0x00002345
	cmp r1, r0
	bne _02027326
_02027322:
	mov r0, #0x1
	b _02027328
_02027326:
	mov r0, #0x0
_02027328:
	cmp r0, #0x0
	bne _02027330
	bl ErrorHandling
_02027330:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x74
	bl memset
	ldr r0, _02027340 ; =0x00001234
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02027340: .word 0x00001234
_02027344: .word 0x00002345

	thumb_func_start FUN_02027348
FUN_02027348: ; 0x02027348
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027378 ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202735E
	ldr r0, _0202737C ; =0x00002345
	cmp r1, r0
	bne _02027362
_0202735E:
	mov r0, #0x1
	b _02027364
_02027362:
	mov r0, #0x0
_02027364:
	cmp r0, #0x0
	bne _0202736C
	bl ErrorHandling
_0202736C:
	add r0, r5, #0x4
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D34
	pop {r4-r6, pc}
	.balign 4
_02027378: .word 0x00001234
_0202737C: .word 0x00002345

	thumb_func_start FUN_02027380
FUN_02027380: ; 0x02027380
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r2, #0x0
	bl FUN_02013ECC
	add r1, sp, #0xc
	strh r0, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	strh r0, [r1, #0x4]
	ldrh r0, [r1, #0x2]
	strh r0, [r1, #0x6]
	ldr r0, [r4, #0x4]
	bl FUN_02013F00
	str r0, [sp, #0x8]
	cmp r6, #0xa
	blt _020273B0
	bl ErrorHandling
_020273B0:
	add r1, sp, #0xc
	mov r0, #0x4
	ldrsh r1, [r1, r0]
	add r0, #0xfc
	cmp r1, r0
	blt _020273C0
	bl ErrorHandling
_020273C0:
	add r1, sp, #0xc
	mov r0, #0x6
	ldrsh r7, [r1, r0]
	add r0, #0xfa
	cmp r7, r0
	blt _020273D0
	bl ErrorHandling
_020273D0:
	mov r1, #0x7f
	ldr r0, [sp, #0x8]
	mvn r1, r1
	cmp r0, r1
	bgt _020273DE
	bl ErrorHandling
_020273DE:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x3c]
	str r0, [sp, #0x4]
	tst r0, r1
	beq _020273EE
	bl ErrorHandling
_020273EE:
	ldr r1, [r5, #0x0]
	ldr r0, _02027440 ; =0x00001234
	cmp r1, r0
	beq _020273FC
	ldr r0, _02027444 ; =0x00002345
	cmp r1, r0
	bne _02027400
_020273FC:
	mov r0, #0x1
	b _02027402
_02027400:
	mov r0, #0x0
_02027402:
	cmp r0, #0x0
	bne _0202740A
	bl ErrorHandling
_0202740A:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0xc
	mov r2, #0x4
	ldrsh r2, [r3, r2]
	lsl r3, r7, #0x18
	add r1, #0x48
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026DB0
	ldr r1, [r5, #0x3c]
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r5, #0x3c]
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02027440: .word 0x00001234
_02027444: .word 0x00002345

	thumb_func_start FUN_02027448
FUN_02027448: ; 0x02027448
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027470 ; =0x00001234
	cmp r1, r0
	beq _0202745C
	ldr r0, _02027474 ; =0x00002345
	cmp r1, r0
	bne _02027460
_0202745C:
	mov r0, #0x1
	b _02027462
_02027460:
	mov r0, #0x0
_02027462:
	cmp r0, #0x0
	bne _0202746A
	bl ErrorHandling
_0202746A:
	add r5, #0x70
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02027470: .word 0x00001234
_02027474: .word 0x00002345

	thumb_func_start FUN_02027478
FUN_02027478: ; 0x02027478
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020274B0 ; =0x00001234
	cmp r1, r0
	beq _0202748C
	ldr r0, _020274B4 ; =0x00002345
	cmp r1, r0
	bne _02027490
_0202748C:
	mov r0, #0x1
	b _02027492
_02027490:
	mov r0, #0x0
_02027492:
	cmp r0, #0x0
	bne _0202749A
	bl ErrorHandling
_0202749A:
	add r0, r5, #0x0
	add r0, #0x40
	bl FUN_02013724
	add r5, #0x40
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02013998
	pop {r3-r5, pc}
	.balign 4
_020274B0: .word 0x00001234
_020274B4: .word 0x00002345

	thumb_func_start FUN_020274B8
FUN_020274B8: ; 0x020274B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020274E8 ; =0x00001234
	cmp r1, r0
	beq _020274CC
	ldr r0, _020274EC ; =0x00002345
	cmp r1, r0
	bne _020274D0
_020274CC:
	mov r0, #0x1
	b _020274D2
_020274D0:
	mov r0, #0x0
_020274D2:
	cmp r0, #0x0
	bne _020274DA
	bl ErrorHandling
_020274DA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x74
	bl memcpy
	pop {r3-r5, pc}
	nop
_020274E8: .word 0x00001234
_020274EC: .word 0x00002345

	thumb_func_start FUN_020274F0
FUN_020274F0: ; 0x020274F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027520 ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _02027506
	ldr r0, _02027524 ; =0x00002345
	cmp r1, r0
	bne _0202750A
_02027506:
	mov r0, #0x1
	b _0202750C
_0202750A:
	mov r0, #0x0
_0202750C:
	cmp r0, #0x0
	bne _02027514
	bl ErrorHandling
_02027514:
	add r0, r5, #0x4
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D98
	pop {r4-r6, pc}
	.balign 4
_02027520: .word 0x00001234
_02027524: .word 0x00002345

	thumb_func_start FUN_02027528
FUN_02027528: ; 0x02027528
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xa
	blt _02027536
	bl ErrorHandling
_02027536:
	ldr r1, [r5, #0x0]
	ldr r0, _0202755C ; =0x00001234
	cmp r1, r0
	beq _02027544
	ldr r0, _02027560 ; =0x00002345
	cmp r1, r0
	bne _02027548
_02027544:
	mov r0, #0x1
	b _0202754A
_02027548:
	mov r0, #0x0
_0202754A:
	cmp r0, #0x0
	bne _02027552
	bl ErrorHandling
_02027552:
	mov r0, #0x1
	ldr r1, [r5, #0x3c]
	lsl r0, r4
	and r0, r1
	pop {r3-r5, pc}
	.balign 4
_0202755C: .word 0x00001234
_02027560: .word 0x00002345

	thumb_func_start FUN_02027564
FUN_02027564: ; 0x02027564
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027588 ; =0x00001234
	cmp r1, r0
	beq _02027576
	ldr r0, _0202758C ; =0x00002345
	cmp r1, r0
	bne _0202757A
_02027576:
	mov r0, #0x1
	b _0202757C
_0202757A:
	mov r0, #0x0
_0202757C:
	cmp r0, #0x0
	bne _02027584
	bl ErrorHandling
_02027584:
	add r0, r4, #0x4
	pop {r4, pc}
	.balign 4
_02027588: .word 0x00001234
_0202758C: .word 0x00002345

	thumb_func_start FUN_02027590
FUN_02027590: ; 0x02027590
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xa
	blt _0202759E
	bl ErrorHandling
_0202759E:
	mov r0, #0x1
	ldr r1, [r5, #0x3c]
	lsl r0, r4
	tst r0, r1
	bne _020275AC
	bl ErrorHandling
_020275AC:
	ldr r1, [r5, #0x0]
	ldr r0, _020275D0 ; =0x00001234
	cmp r1, r0
	beq _020275BA
	ldr r0, _020275D4 ; =0x00002345
	cmp r1, r0
	bne _020275BE
_020275BA:
	mov r0, #0x1
	b _020275C0
_020275BE:
	mov r0, #0x0
_020275C0:
	cmp r0, #0x0
	bne _020275C8
	bl ErrorHandling
_020275C8:
	add r5, #0x48
	lsl r0, r4, #0x2
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4
_020275D0: .word 0x00001234
_020275D4: .word 0x00002345

	thumb_func_start FUN_020275D8
FUN_020275D8: ; 0x020275D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027600 ; =0x00001234
	cmp r1, r0
	beq _020275EA
	ldr r0, _02027604 ; =0x00002345
	cmp r1, r0
	bne _020275EE
_020275EA:
	mov r0, #0x1
	b _020275F0
_020275EE:
	mov r0, #0x0
_020275F0:
	cmp r0, #0x0
	bne _020275F8
	bl ErrorHandling
_020275F8:
	add r0, r4, #0x4
	bl FUN_02027C84
	pop {r4, pc}
	.balign 4
_02027600: .word 0x00001234
_02027604: .word 0x00002345

	thumb_func_start FUN_02027608
FUN_02027608: ; 0x02027608
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027634 ; =0x00001234
	cmp r1, r0
	beq _0202761C
	ldr r0, _02027638 ; =0x00002345
	cmp r1, r0
	bne _02027620
_0202761C:
	mov r0, #0x1
	b _02027622
_02027620:
	mov r0, #0x0
_02027622:
	cmp r0, #0x0
	bne _0202762A
	bl ErrorHandling
_0202762A:
	add r0, r5, #0x4
	add r1, r4, #0x0
	bl FUN_02027C88
	pop {r3-r5, pc}
	.balign 4
_02027634: .word 0x00001234
_02027638: .word 0x00002345

	thumb_func_start FUN_0202763C
FUN_0202763C: ; 0x0202763C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027664 ; =0x00001234
	cmp r1, r0
	beq _0202764E
	ldr r0, _02027668 ; =0x00002345
	cmp r1, r0
	bne _02027652
_0202764E:
	mov r0, #0x1
	b _02027654
_02027652:
	mov r0, #0x0
_02027654:
	cmp r0, #0x0
	bne _0202765C
	bl ErrorHandling
_0202765C:
	add r0, r4, #0x4
	bl FUN_02027C98
	pop {r4, pc}
	.balign 4
_02027664: .word 0x00001234
_02027668: .word 0x00002345

	thumb_func_start FUN_0202766C
FUN_0202766C: ; 0x0202766C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027694 ; =0x00001234
	cmp r1, r0
	beq _0202767E
	ldr r0, _02027698 ; =0x00002345
	cmp r1, r0
	bne _02027682
_0202767E:
	mov r0, #0x1
	b _02027684
_02027682:
	mov r0, #0x0
_02027684:
	cmp r0, #0x0
	bne _0202768C
	bl ErrorHandling
_0202768C:
	add r4, #0x70
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027694: .word 0x00001234
_02027698: .word 0x00002345

	thumb_func_start FUN_0202769C
FUN_0202769C: ; 0x0202769C
	ldr r3, _020276A4 ; =FUN_02013918
	add r0, #0x40
	mov r1, #0x0
	bx r3
	.balign 4
_020276A4: .word FUN_02013918

	thumb_func_start FUN_020276A8
FUN_020276A8: ; 0x020276A8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _020276D0 ; =0x00001234
	cmp r1, r0
	beq _020276BA
	ldr r0, _020276D4 ; =0x00002345
	cmp r1, r0
	bne _020276BE
_020276BA:
	mov r0, #0x1
	b _020276C0
_020276BE:
	mov r0, #0x0
_020276C0:
	cmp r0, #0x0
	bne _020276C8
	bl ErrorHandling
_020276C8:
	add r4, #0x71
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_020276D0: .word 0x00001234
_020276D4: .word 0x00002345

	thumb_func_start FUN_020276D8
FUN_020276D8: ; 0x020276D8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027708 ; =0x00001234
	cmp r1, r0
	beq _020276EA
	ldr r0, _0202770C ; =0x00002345
	cmp r1, r0
	bne _020276EE
_020276EA:
	mov r0, #0x1
	b _020276F0
_020276EE:
	mov r0, #0x0
_020276F0:
	cmp r0, #0x0
	bne _020276F8
	bl ErrorHandling
_020276F8:
	ldr r1, [r4, #0x0]
	ldr r0, _0202770C ; =0x00002345
	cmp r1, r0
	bne _02027704
	mov r0, #0x1
	pop {r4, pc}
_02027704:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02027708: .word 0x00001234
_0202770C: .word 0x00002345

	thumb_func_start FUN_02027710
FUN_02027710: ; 0x02027710
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027738 ; =0x00001234
	cmp r1, r0
	beq _02027722
	ldr r0, _0202773C ; =0x00002345
	cmp r1, r0
	bne _02027726
_02027722:
	mov r0, #0x1
	b _02027728
_02027726:
	mov r0, #0x0
_02027728:
	cmp r0, #0x0
	bne _02027730
	bl ErrorHandling
_02027730:
	ldr r0, _0202773C ; =0x00002345
	str r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027738: .word 0x00001234
_0202773C: .word 0x00002345

	thumb_func_start FUN_02027740
FUN_02027740: ; 0x02027740
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027770 ; =0x00001234
	cmp r1, r0
	beq _02027752
	ldr r0, _02027774 ; =0x00002345
	cmp r1, r0
	bne _02027756
_02027752:
	mov r0, #0x1
	b _02027758
_02027756:
	mov r0, #0x0
_02027758:
	cmp r0, #0x0
	bne _02027760
	bl ErrorHandling
_02027760:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x98
	bl memset
	ldr r0, _02027770 ; =0x00001234
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02027770: .word 0x00001234
_02027774: .word 0x00002345

	thumb_func_start FUN_02027778
FUN_02027778: ; 0x02027778
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020277AC ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202778E
	ldr r0, _020277B0 ; =0x00002345
	cmp r1, r0
	bne _02027792
_0202778E:
	mov r0, #0x1
	b _02027794
_02027792:
	mov r0, #0x0
_02027794:
	cmp r0, #0x0
	bne _0202779C
	bl ErrorHandling
_0202779C:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D34
	pop {r4-r6, pc}
	nop
_020277AC: .word 0x00001234
_020277B0: .word 0x00002345

	thumb_func_start FUN_020277B4
FUN_020277B4: ; 0x020277B4
	push {r4-r7, lr}
	sub sp, #0x14
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	add r6, r2, #0x0
	bl FUN_02013ECC
	add r1, sp, #0xc
	strh r0, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	ldrh r0, [r1, #0x0]
	strh r0, [r1, #0x4]
	ldrh r0, [r1, #0x2]
	strh r0, [r1, #0x6]
	ldr r0, [r4, #0x4]
	bl FUN_02013F00
	str r0, [sp, #0x8]
	cmp r6, #0x14
	blt _020277E4
	bl ErrorHandling
_020277E4:
	add r1, sp, #0xc
	mov r0, #0x4
	ldrsh r1, [r1, r0]
	add r0, #0xfc
	cmp r1, r0
	blt _020277F4
	bl ErrorHandling
_020277F4:
	add r1, sp, #0xc
	mov r0, #0x6
	ldrsh r7, [r1, r0]
	add r0, #0xfa
	cmp r7, r0
	blt _02027804
	bl ErrorHandling
_02027804:
	mov r1, #0x7f
	ldr r0, [sp, #0x8]
	mvn r1, r1
	cmp r0, r1
	bgt _02027812
	bl ErrorHandling
_02027812:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x40]
	str r0, [sp, #0x4]
	tst r0, r1
	beq _02027822
	bl ErrorHandling
_02027822:
	ldr r1, [r5, #0x0]
	ldr r0, _02027874 ; =0x00001234
	cmp r1, r0
	beq _02027830
	ldr r0, _02027878 ; =0x00002345
	cmp r1, r0
	bne _02027834
_02027830:
	mov r0, #0x1
	b _02027836
_02027834:
	mov r0, #0x0
_02027836:
	cmp r0, #0x0
	bne _0202783E
	bl ErrorHandling
_0202783E:
	ldr r0, [sp, #0x8]
	add r1, r5, #0x0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0xc
	mov r2, #0x4
	ldrsh r2, [r3, r2]
	lsl r3, r7, #0x18
	add r1, #0x44
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_02026DB0
	ldr r1, [r5, #0x40]
	ldr r0, [sp, #0x4]
	orr r0, r1
	str r0, [r5, #0x40]
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02027874: .word 0x00001234
_02027878: .word 0x00002345

	thumb_func_start FUN_0202787C
FUN_0202787C: ; 0x0202787C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020278A4 ; =0x00001234
	cmp r1, r0
	beq _02027890
	ldr r0, _020278A8 ; =0x00002345
	cmp r1, r0
	bne _02027894
_02027890:
	mov r0, #0x1
	b _02027896
_02027894:
	mov r0, #0x0
_02027896:
	cmp r0, #0x0
	bne _0202789E
	bl ErrorHandling
_0202789E:
	add r5, #0x94
	strb r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020278A4: .word 0x00001234
_020278A8: .word 0x00002345

	thumb_func_start FUN_020278AC
FUN_020278AC: ; 0x020278AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _020278D4 ; =0x00001234
	cmp r1, r0
	beq _020278C0
	ldr r0, _020278D8 ; =0x00002345
	cmp r1, r0
	bne _020278C4
_020278C0:
	mov r0, #0x1
	b _020278C6
_020278C4:
	mov r0, #0x0
_020278C6:
	cmp r0, #0x0
	bne _020278CE
	bl ErrorHandling
_020278CE:
	str r4, [r5, #0x4]
	pop {r3-r5, pc}
	nop
_020278D4: .word 0x00001234
_020278D8: .word 0x00002345

	thumb_func_start FUN_020278DC
FUN_020278DC: ; 0x020278DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202790C ; =0x00001234
	cmp r1, r0
	beq _020278F0
	ldr r0, _02027910 ; =0x00002345
	cmp r1, r0
	bne _020278F4
_020278F0:
	mov r0, #0x1
	b _020278F6
_020278F4:
	mov r0, #0x0
_020278F6:
	cmp r0, #0x0
	bne _020278FE
	bl ErrorHandling
_020278FE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x98
	bl memcpy
	pop {r3-r5, pc}
	nop
_0202790C: .word 0x00001234
_02027910: .word 0x00002345

	thumb_func_start FUN_02027914
FUN_02027914: ; 0x02027914
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _0202795C ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _0202792C
	ldr r0, _02027960 ; =0x00002345
	cmp r1, r0
	bne _02027930
_0202792C:
	mov r0, #0x1
	b _02027932
_02027930:
	mov r0, #0x0
_02027932:
	cmp r0, #0x0
	bne _0202793A
	bl ErrorHandling
_0202793A:
	add r1, sp, #0x4
	add r0, r4, #0x0
	add r1, #0x1
	add r2, sp, #0x4
	bl FUN_02026F3C
	add r5, #0x8
	str r6, [sp, #0x0]
	add r3, sp, #0x4
	ldrb r2, [r3, #0x1]
	ldrb r3, [r3, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02026CD0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0202795C: .word 0x00001234
_02027960: .word 0x00002345

	thumb_func_start FUN_02027964
FUN_02027964: ; 0x02027964
	push {r4-r7, lr}
	sub sp, #0xc
	str r3, [sp, #0x4]
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	ldr r4, [sp, #0x24]
	cmp r6, #0x14
	blo _0202797A
	bl ErrorHandling
_0202797A:
	cmp r7, #0x64
	blo _02027982
	bl ErrorHandling
_02027982:
	mov r1, #0x1
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x8
	cmp r0, r1
	blt _02027990
	bl ErrorHandling
_02027990:
	add r0, sp, #0x10
	ldrb r1, [r0, #0x10]
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	blt _020279A0
	bl ErrorHandling
_020279A0:
	mov r0, #0x7f
	mvn r0, r0
	cmp r4, r0
	bgt _020279AC
	bl ErrorHandling
_020279AC:
	mov r0, #0x1
	lsl r0, r6
	ldr r1, [r5, #0x40]
	str r0, [sp, #0x8]
	tst r0, r1
	beq _020279BC
	bl ErrorHandling
_020279BC:
	ldr r1, [r5, #0x0]
	ldr r0, _02027A0C ; =0x00001234
	cmp r1, r0
	beq _020279CA
	ldr r0, _02027A10 ; =0x00002345
	cmp r1, r0
	bne _020279CE
_020279CA:
	mov r0, #0x1
	b _020279D0
_020279CE:
	mov r0, #0x0
_020279D0:
	cmp r0, #0x0
	bne _020279D8
	bl ErrorHandling
_020279D8:
	mov r0, #0x38
	ldrsb r0, [r5, r0]
	cmp r0, r4
	blt _020279E6
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	asr r4, r0, #0x18
_020279E6:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r3, sp, #0x10
	add r1, r5, #0x0
	ldrb r3, [r3, #0x10]
	add r1, #0x44
	lsl r0, r6, #0x2
	add r0, r1, r0
	ldr r2, [sp, #0x4]
	add r1, r7, #0x0
	bl FUN_02026DB0
	ldr r1, [r5, #0x40]
	ldr r0, [sp, #0x8]
	orr r0, r1
	str r0, [r5, #0x40]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02027A0C: .word 0x00001234
_02027A10: .word 0x00002345

	thumb_func_start FUN_02027A14
FUN_02027A14: ; 0x02027A14
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027A22
	bl ErrorHandling
_02027A22:
	ldr r1, [r5, #0x0]
	ldr r0, _02027A50 ; =0x00001234
	cmp r1, r0
	beq _02027A30
	ldr r0, _02027A54 ; =0x00002345
	cmp r1, r0
	bne _02027A34
_02027A30:
	mov r0, #0x1
	b _02027A36
_02027A34:
	mov r0, #0x0
_02027A36:
	cmp r0, #0x0
	bne _02027A3E
	bl ErrorHandling
_02027A3E:
	mov r0, #0x1
	add r1, r0, #0x0
	ldr r2, [r5, #0x40]
	lsl r1, r4
	tst r1, r2
	bne _02027A4C
	mov r0, #0x0
_02027A4C:
	pop {r3-r5, pc}
	nop
_02027A50: .word 0x00001234
_02027A54: .word 0x00002345

	thumb_func_start FUN_02027A58
FUN_02027A58: ; 0x02027A58
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027A8C ; =0x00001234
	add r6, r2, #0x0
	cmp r1, r0
	beq _02027A6E
	ldr r0, _02027A90 ; =0x00002345
	cmp r1, r0
	bne _02027A72
_02027A6E:
	mov r0, #0x1
	b _02027A74
_02027A72:
	mov r0, #0x0
_02027A74:
	cmp r0, #0x0
	bne _02027A7C
	bl ErrorHandling
_02027A7C:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02026D98
	pop {r4-r6, pc}
	nop
_02027A8C: .word 0x00001234
_02027A90: .word 0x00002345

	thumb_func_start FUN_02027A94
FUN_02027A94: ; 0x02027A94
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027ABC ; =0x00001234
	cmp r1, r0
	beq _02027AA6
	ldr r0, _02027AC0 ; =0x00002345
	cmp r1, r0
	bne _02027AAA
_02027AA6:
	mov r0, #0x1
	b _02027AAC
_02027AAA:
	mov r0, #0x0
_02027AAC:
	cmp r0, #0x0
	bne _02027AB4
	bl ErrorHandling
_02027AB4:
	add r4, #0x8
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_02027ABC: .word 0x00001234
_02027AC0: .word 0x00002345

	thumb_func_start FUN_02027AC4
FUN_02027AC4: ; 0x02027AC4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027AD2
	bl ErrorHandling
_02027AD2:
	mov r0, #0x1
	ldr r1, [r5, #0x40]
	lsl r0, r4
	tst r0, r1
	bne _02027AE0
	bl ErrorHandling
_02027AE0:
	ldr r1, [r5, #0x0]
	ldr r0, _02027B04 ; =0x00001234
	cmp r1, r0
	beq _02027AEE
	ldr r0, _02027B08 ; =0x00002345
	cmp r1, r0
	bne _02027AF2
_02027AEE:
	mov r0, #0x1
	b _02027AF4
_02027AF2:
	mov r0, #0x0
_02027AF4:
	cmp r0, #0x0
	bne _02027AFC
	bl ErrorHandling
_02027AFC:
	add r5, #0x44
	lsl r0, r4, #0x2
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4
_02027B04: .word 0x00001234
_02027B08: .word 0x00002345

	thumb_func_start FUN_02027B0C
FUN_02027B0C: ; 0x02027B0C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027B3C ; =0x00001234
	cmp r1, r0
	beq _02027B20
	ldr r0, _02027B40 ; =0x00002345
	cmp r1, r0
	bne _02027B24
_02027B20:
	mov r0, #0x1
	b _02027B26
_02027B24:
	mov r0, #0x0
_02027B26:
	cmp r0, #0x0
	bne _02027B2E
	bl ErrorHandling
_02027B2E:
	add r5, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02027C88
	pop {r3-r5, pc}
	nop
_02027B3C: .word 0x00001234
_02027B40: .word 0x00002345

	thumb_func_start FUN_02027B44
FUN_02027B44: ; 0x02027B44
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027B70 ; =0x00001234
	cmp r1, r0
	beq _02027B56
	ldr r0, _02027B74 ; =0x00002345
	cmp r1, r0
	bne _02027B5A
_02027B56:
	mov r0, #0x1
	b _02027B5C
_02027B5A:
	mov r0, #0x0
_02027B5C:
	cmp r0, #0x0
	bne _02027B64
	bl ErrorHandling
_02027B64:
	add r4, #0x8
	add r0, r4, #0x0
	bl FUN_02027C98
	pop {r4, pc}
	nop
_02027B70: .word 0x00001234
_02027B74: .word 0x00002345

	thumb_func_start FUN_02027B78
FUN_02027B78: ; 0x02027B78
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldr r1, [r5, #0x0]
	ldr r0, _02027BD4 ; =0x00001234
	cmp r1, r0
	beq _02027B8E
	ldr r0, _02027BD8 ; =0x00002345
	cmp r1, r0
	bne _02027B92
_02027B8E:
	mov r0, #0x1
	b _02027B94
_02027B92:
	mov r0, #0x0
_02027B94:
	cmp r0, #0x0
	bne _02027B9C
	bl ErrorHandling
_02027B9C:
	mov r1, #0x1
	str r1, [sp, #0x0]
	ldr r0, [r5, #0x8]
	mov r2, #0x0
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r5, #0xc]
	add r3, r2, #0x0
	str r0, [sp, #0xc]
	ldrh r1, [r5, #0x10]
	add r0, r4, #0x0
	bl FUN_02066ACC
	add r2, r5, #0x0
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0x12
	bl FUN_02067830
	add r5, #0x3b
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, r5, #0x0
	bl FUN_02067830
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02027BD4: .word 0x00001234
_02027BD8: .word 0x00002345

	thumb_func_start FUN_02027BDC
FUN_02027BDC: ; 0x02027BDC
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x14
	blt _02027BEA
	bl ErrorHandling
_02027BEA:
	mov r0, #0x1
	ldr r1, [r5, #0x40]
	lsl r0, r4
	tst r0, r1
	bne _02027BF8
	bl ErrorHandling
_02027BF8:
	ldr r1, [r5, #0x0]
	ldr r0, _02027C20 ; =0x00001234
	cmp r1, r0
	beq _02027C06
	ldr r0, _02027C24 ; =0x00002345
	cmp r1, r0
	bne _02027C0A
_02027C06:
	mov r0, #0x1
	b _02027C0C
_02027C0A:
	mov r0, #0x0
_02027C0C:
	cmp r0, #0x0
	bne _02027C14
	bl ErrorHandling
_02027C14:
	add r5, #0x44
	lsl r0, r4, #0x2
	add r0, r5, r0
	bl FUN_02027CF8
	pop {r3-r5, pc}
	.balign 4
_02027C20: .word 0x00001234
_02027C24: .word 0x00002345

	thumb_func_start FUN_02027C28
FUN_02027C28: ; 0x02027C28
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027C50 ; =0x00001234
	cmp r1, r0
	beq _02027C3A
	ldr r0, _02027C54 ; =0x00002345
	cmp r1, r0
	bne _02027C3E
_02027C3A:
	mov r0, #0x1
	b _02027C40
_02027C3E:
	mov r0, #0x0
_02027C40:
	cmp r0, #0x0
	bne _02027C48
	bl ErrorHandling
_02027C48:
	add r4, #0x94
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02027C50: .word 0x00001234
_02027C54: .word 0x00002345

	thumb_func_start FUN_02027C58
FUN_02027C58: ; 0x02027C58
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	ldr r0, _02027C7C ; =0x00001234
	cmp r1, r0
	beq _02027C6A
	ldr r0, _02027C80 ; =0x00002345
	cmp r1, r0
	bne _02027C6E
_02027C6A:
	mov r0, #0x1
	b _02027C70
_02027C6E:
	mov r0, #0x0
_02027C70:
	cmp r0, #0x0
	bne _02027C78
	bl ErrorHandling
_02027C78:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4
_02027C7C: .word 0x00001234
_02027C80: .word 0x00002345

	thumb_func_start FUN_02027C84
FUN_02027C84: ; 0x02027C84
	ldrh r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02027C88
FUN_02027C88: ; 0x02027C88
	add r2, r0, #0x0
	ldr r3, _02027C94 ; =FUN_02021E28
	add r2, #0x20
	add r0, r1, #0x0
	add r1, r2, #0x0
	bx r3
	.balign 4
_02027C94: .word FUN_02021E28

	thumb_func_start FUN_02027C98
FUN_02027C98: ; 0x02027C98
	add r0, #0x34
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CA0
FUN_02027CA0: ; 0x02027CA0
	mov r1, #0x30
	ldrsb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CA8
FUN_02027CA8: ; 0x02027CA8
	add r0, #0x31
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CB0
FUN_02027CB0: ; 0x02027CB0
	add r0, #0x32
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02027CB8
FUN_02027CB8: ; 0x02027CB8
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r5, #0x0]
	mov r2, #0x0
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r5, #0x4]
	add r3, r2, #0x0
	str r0, [sp, #0xc]
	ldrh r1, [r5, #0x8]
	add r0, r4, #0x0
	bl FUN_02066ACC
	add r2, r5, #0x0
	add r0, r4, #0x0
	mov r1, #0x74
	add r2, #0xa
	bl FUN_02067830
	add r5, #0x33
	add r0, r4, #0x0
	mov r1, #0x70
	add r2, r5, #0x0
	bl FUN_02067830
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02027CF8
FUN_02027CF8: ; 0x02027CF8
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02027CFC
FUN_02027CFC: ; 0x02027CFC
	ldrb r0, [r0, #0x1]
	bx lr

	thumb_func_start FUN_02027D00
FUN_02027D00: ; 0x02027D00
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02027D04
FUN_02027D04: ; 0x02027D04
	mov r1, #0x3
	ldrsb r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start FUN_02027D0C
FUN_02027D0C: ; 0x02027D0C
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0xc
	add r7, r0, #0x0
	mov r0, #0x1
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_0202729C
	cmp r0, #0x1
	bne _02027D6A
	ldr r1, _02027D78 ; =0xEDB88320
	add r0, sp, #0x4
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x4
	add r1, r4, #0x0
	mov r2, #0x74
	bl MATH_CalcCRC32
	add r6, r0, #0x0
	mov r5, #0x0
_02027D3C:
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02027008
	add r4, r0, #0x0
	ldr r1, _02027D78 ; =0xEDB88320
	add r0, sp, #0x4
	bl MATHi_CRC32InitTableRev
	add r0, sp, #0x4
	add r1, r4, #0x0
	mov r2, #0x74
	bl MATH_CalcCRC32
	cmp r0, r6
	bne _02027D62
	mov r0, #0x0
	str r0, [sp, #0x0]
	b _02027D6E
_02027D62:
	add r5, r5, #0x1
	cmp r5, #0xb
	blt _02027D3C
	b _02027D6E
_02027D6A:
	mov r0, #0x0
	str r0, [sp, #0x0]
_02027D6E:
	ldr r0, [sp, #0x0]
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02027D78: .word 0xEDB88320

	thumb_func_start FUN_02027D7C
FUN_02027D7C: ; 0x02027D7C
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	mov r7, #0x0
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r6, r7, #0x0
	str r3, [sp, #0x8]
	cmp r0, #0x0
	ble _02027DB6
	add r4, r3, #0x0
_02027D94:
	ldr r0, [sp, #0x4]
	cmp r6, r0
	beq _02027DAC
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02027DAC
	add r0, r5, #0x0
	bl FUN_02027D0C
	cmp r0, #0x1
	bne _02027DAC
	add r7, r7, #0x1
_02027DAC:
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02027D94
_02027DB6:
	mov r4, #0xa
_02027DB8:
	add r1, r4, r7
	cmp r1, #0xb
	bge _02027DD6
	add r0, r5, #0x0
	bl FUN_02027008
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02027008
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020274B8
_02027DD6:
	sub r4, r4, #0x1
	cmp r4, #0x1
	bge _02027DB8
	ldr r0, [sp, #0x0]
	mov r6, #0x1
	mov r4, #0x0
	cmp r0, #0x0
	ble _02027E1E
_02027DE6:
	ldr r0, [sp, #0x4]
	cmp r4, r0
	beq _02027E10
	ldr r0, [sp, #0x8]
	ldr r7, [r0, #0x0]
	cmp r7, #0x0
	beq _02027E10
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_02027D0C
	cmp r0, #0x1
	bne _02027E10
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02027008
	add r1, r7, #0x0
	add r6, r6, #0x1
	bl FUN_020274B8
_02027E10:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r0, r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x0]
	cmp r4, r0
	blt _02027DE6
_02027E1E:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02027E24
FUN_02027E24: ; 0x02027E24
	ldr r3, _02027E2C ; =FUN_02022610
	mov r1, #0xe
	bx r3
	nop
_02027E2C: .word FUN_02022610

	thumb_func_start FUN_02027E30
FUN_02027E30: ; 0x02027E30
	mov r0, #0x8
	bx lr

	thumb_func_start FUN_02027E34
FUN_02027E34: ; 0x02027E34
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1e
	beq _02027E3E
	mov r0, #0x1
	bx lr
_02027E3E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02027E44
FUN_02027E44: ; 0x02027E44
	mov r1, #0x1e
	strb r1, [r0, #0x0]
	mov r1, #0x0
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	bx lr
	.balign 4

	thumb_func_start FUN_02027E5C
FUN_02027E5C: ; 0x02027E5C
	push {r4, lr}
	mov r1, #0x8
	bl FUN_020169D8
	add r4, r0, #0x0
	bl FUN_02027E44
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02027E70
FUN_02027E70: ; 0x02027E70
	ldrb r2, [r0, #0x0]
	strb r2, [r1, #0x0]
	ldrb r2, [r0, #0x1]
	strb r2, [r1, #0x1]
	ldrb r2, [r0, #0x2]
	strb r2, [r1, #0x2]
	ldrb r2, [r0, #0x3]
	strb r2, [r1, #0x3]
	ldrb r2, [r0, #0x4]
	strb r2, [r1, #0x4]
	ldrb r2, [r0, #0x5]
	strb r2, [r1, #0x5]
	ldrb r2, [r0, #0x6]
	strb r2, [r1, #0x6]
	ldrb r0, [r0, #0x7]
	strb r0, [r1, #0x7]
	bx lr
	.balign 4

	thumb_func_start FUN_02027E94
FUN_02027E94: ; 0x02027E94
	cmp r1, #0x6
	bhi _02027ECA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02027EA4: ; jump table (using 16-bit offset)
	.short _02027EB2 - _02027EA4 - 2; case 0
	.short _02027EB6 - _02027EA4 - 2; case 1
	.short _02027EBA - _02027EA4 - 2; case 2
	.short _02027EBE - _02027EA4 - 2; case 3
	.short _02027EC2 - _02027EA4 - 2; case 4
	.short _02027EC6 - _02027EA4 - 2; case 5
	.short _02027ECA - _02027EA4 - 2; case 6
_02027EB2:
	ldrb r0, [r0, #0x0]
	bx lr
_02027EB6:
	ldrb r0, [r0, #0x1]
	bx lr
_02027EBA:
	ldrb r0, [r0, #0x2]
	bx lr
_02027EBE:
	ldrb r0, [r0, #0x3]
	bx lr
_02027EC2:
	ldrb r0, [r0, #0x4]
	bx lr
_02027EC6:
	ldrb r0, [r0, #0x5]
	bx lr
_02027ECA:
	ldrb r0, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_02027ED0
FUN_02027ED0: ; 0x02027ED0
	push {r3-r7, lr}
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	mov r4, #0x0
	mov r6, #0x2
	mov r7, #0x5
_02027EDC:
	bl rand_LC
	add r1, r7, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	add r1, r5, r0
	ldrb r0, [r1, #0x1]
	cmp r0, #0x0
	bne _02027EF6
	strb r6, [r1, #0x1]
	add r4, r4, #0x1
_02027EF6:
	cmp r4, #0x3
	blt _02027EDC
	mov r0, #0x1b
	strb r0, [r5, #0x0]
	ldr r0, [sp, #0x0]
	strb r0, [r5, #0x6]
	pop {r3-r7, pc}

	thumb_func_start FUN_02027F04
FUN_02027F04: ; 0x02027F04
	push {r3-r7, lr}
	sub sp, #0x8
	mov r12, r2
	mov r2, #0x0
	add r6, r2, #0x0
	mov r5, #0x1b
	cmp r3, #0x0
	beq _02027F20
	mov r1, r12
	bl FUN_02027ED0
	add sp, #0x8
	add r0, r5, #0x0
	pop {r3-r7, pc}
_02027F20:
	add r4, r2, #0x0
	add r7, sp, #0x0
_02027F24:
	ldrb r3, [r1, r4]
	cmp r3, #0x0
	beq _02027F34
	cmp r3, #0x32
	blo _02027F30
	mov r6, #0x1
_02027F30:
	strb r4, [r7, r2]
	add r2, r2, #0x1
_02027F34:
	add r4, r4, #0x1
	cmp r4, #0x5
	blt _02027F24
	cmp r2, #0x5
	bhi _02027F9C
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02027F4A: ; jump table (using 16-bit offset)
	.short _02027F56 - _02027F4A - 2; case 0
	.short _02027F62 - _02027F4A - 2; case 1
	.short _02027F70 - _02027F4A - 2; case 2
	.short _02027F96 - _02027F4A - 2; case 3
	.short _02027F9A - _02027F4A - 2; case 4
	.short _02027F9A - _02027F4A - 2; case 5
_02027F56:
	mov r1, r12
	bl FUN_02027ED0
	add sp, #0x8
	mov r0, #0x1b
	pop {r3-r7, pc}
_02027F62:
	add r2, sp, #0x0
	ldrb r3, [r2, #0x0]
	mov r2, #0x6
	mul r2, r3
	lsl r2, r2, #0x18
	lsr r5, r2, #0x18
	b _02027F9C
_02027F70:
	add r2, sp, #0x0
	ldrb r3, [r2, #0x1]
	ldrb r2, [r2, #0x0]
	ldrb r4, [r1, r3]
	ldrb r5, [r1, r2]
	cmp r5, r4
	blo _02027F8A
	lsl r4, r2, #0x2
	add r2, r2, r4
	add r2, r3, r2
	lsl r2, r2, #0x18
	lsr r5, r2, #0x18
	b _02027F9C
_02027F8A:
	lsl r4, r3, #0x2
	add r3, r3, r4
	add r2, r2, r3
	lsl r2, r2, #0x18
	lsr r5, r2, #0x18
	b _02027F9C
_02027F96:
	mov r5, #0x19
	b _02027F9C
_02027F9A:
	mov r5, #0x1a
_02027F9C:
	cmp r6, #0x0
	beq _02027FA2
	mov r5, #0x1c
_02027FA2:
	mov r4, #0x0
_02027FA4:
	ldrb r3, [r1, r4]
	add r2, r0, r4
	add r4, r4, #0x1
	strb r3, [r2, #0x1]
	cmp r4, #0x5
	blt _02027FA4
	strb r5, [r0, #0x0]
	mov r1, r12
	strb r1, [r0, #0x6]
	add r0, r5, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02027FBC
FUN_02027FBC: ; 0x02027FBC
	ldrb r2, [r0, #0x0]
	strb r2, [r1, #0x0]
	ldrb r2, [r0, #0x1]
	strb r2, [r1, #0x1]
	ldrb r2, [r0, #0x2]
	strb r2, [r1, #0x2]
	ldrb r2, [r0, #0x3]
	strb r2, [r1, #0x3]
	ldrb r2, [r0, #0x4]
	strb r2, [r1, #0x4]
	ldrb r2, [r0, #0x5]
	strb r2, [r1, #0x5]
	ldrb r0, [r0, #0x6]
	strb r0, [r1, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_02027FDC
FUN_02027FDC: ; 0x02027FDC
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r0, [r4, #0x0]
	mov r1, #0x5
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x5
	bhi _0202801C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02027FFC: ; jump table (using 16-bit offset)
	.short _02028008 - _02027FFC - 2; case 0
	.short _0202800C - _02027FFC - 2; case 1
	.short _02028010 - _02027FFC - 2; case 2
	.short _02028014 - _02027FFC - 2; case 3
	.short _02028018 - _02027FFC - 2; case 4
	.short _0202801C - _02027FFC - 2; case 5
_02028008:
	ldrb r0, [r4, #0x1]
	b _0202803E
_0202800C:
	ldrb r0, [r4, #0x2]
	b _0202803E
_02028010:
	ldrb r0, [r4, #0x3]
	b _0202803E
_02028014:
	ldrb r0, [r4, #0x4]
	b _0202803E
_02028018:
	ldrb r0, [r4, #0x5]
	b _0202803E
_0202801C:
	ldrb r0, [r4, #0x1]
	ldrb r1, [r4, #0x2]
	cmp r0, r1
	bhs _02028026
	add r0, r1, #0x0
_02028026:
	ldrb r1, [r4, #0x3]
	cmp r0, r1
	bhs _0202802E
	add r0, r1, #0x0
_0202802E:
	ldrb r1, [r4, #0x4]
	cmp r0, r1
	bhs _02028036
	add r0, r1, #0x0
_02028036:
	ldrb r1, [r4, #0x5]
	cmp r0, r1
	bhs _0202803E
	add r0, r1, #0x0
_0202803E:
	cmp r0, #0x63
	bls _02028044
	mov r0, #0x63
_02028044:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028048
FUN_02028048: ; 0x02028048
	ldr r3, _02028050 ; =FUN_02022610
	mov r1, #0x10
	bx r3
	nop
_02028050: .word FUN_02022610

	thumb_func_start FUN_02028054
FUN_02028054: ; 0x02028054
	mov r0, #0x32
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_0202805C
FUN_0202805C: ; 0x0202805C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_02028062:
	add r0, r5, #0x0
	bl FUN_02027E44
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x64
	blt _02028062
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02028074
FUN_02028074: ; 0x02028074
	mov r2, #0x0
_02028076:
	lsl r1, r2, #0x3
	ldrb r1, [r0, r1]
	cmp r1, #0x1e
	bne _02028082
	add r0, r2, #0x0
	bx lr
_02028082:
	add r1, r2, #0x1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	cmp r2, #0x64
	blo _02028076
	ldr r0, _02028090 ; =0x0000FFFF
	bx lr
	.balign 4
_02028090: .word 0x0000FFFF

	thumb_func_start FUN_02028094
FUN_02028094: ; 0x02028094
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02028074
	ldr r1, _020280B4 ; =0x0000FFFF
	add r4, r0, #0x0
	cmp r4, r1
	beq _020280B2
	lsl r1, r4, #0x3
	add r0, r6, #0x0
	add r1, r5, r1
	bl FUN_02027E70
	add r0, r4, #0x0
_020280B2:
	pop {r4-r6, pc}
	.balign 4
_020280B4: .word 0x0000FFFF

	thumb_func_start FUN_020280B8
FUN_020280B8: ; 0x020280B8
	push {r3, lr}
	cmp r1, #0x64
	blo _020280C2
	mov r0, #0x0
	pop {r3, pc}
_020280C2:
	lsl r1, r1, #0x3
	add r0, r0, r1
	bl FUN_02027E44
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020280D0
FUN_020280D0: ; 0x020280D0
	cmp r1, #0x64
	bhs _020280EA
_020280D4:
	lsl r2, r1, #0x3
	ldrb r2, [r0, r2]
	cmp r2, #0x1e
	beq _020280E0
	add r0, r1, #0x0
	bx lr
_020280E0:
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	cmp r1, #0x64
	blo _020280D4
_020280EA:
	ldr r0, _020280F0 ; =0x0000FFFF
	bx lr
	nop
_020280F0: .word 0x0000FFFF

	thumb_func_start FUN_020280F4
FUN_020280F4: ; 0x020280F4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x0
	mov r7, #0x64
	str r0, [sp, #0x4]
_02028100:
	ldr r0, [sp, #0x4]
	lsl r0, r0, #0x3
	ldrb r0, [r5, r0]
	cmp r0, #0x1e
	bne _0202815C
	ldr r6, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020280D0
	add r4, r0, #0x0
	ldr r0, _02028170 ; =0x0000FFFF
	cmp r4, r0
	beq _0202816A
	ldr r0, [sp, #0x4]
	sub r0, r4, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	cmp r4, r7
	bhs _02028154
	cmp r4, r7
	bhs _02028154
_0202812E:
	lsl r0, r4, #0x3
	lsl r1, r6, #0x3
	str r0, [sp, #0x8]
	add r0, r5, r0
	add r1, r5, r1
	bl FUN_02027E70
	ldr r0, [sp, #0x8]
	add r0, r5, r0
	bl FUN_02027E44
	add r0, r6, #0x1
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, r7
	blo _0202812E
_02028154:
	ldr r0, [sp, #0x0]
	sub r0, r7, r0
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
_0202815C:
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	cmp r0, r7
	blo _02028100
_0202816A:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02028170: .word 0x0000FFFF

	thumb_func_start FUN_02028174
FUN_02028174: ; 0x02028174
	push {r3, lr}
	cmp r1, #0x64
	blo _02028182
	add r0, r2, #0x0
	bl FUN_02027E44
	pop {r3, pc}
_02028182:
	lsl r1, r1, #0x3
	add r0, r0, r1
	add r1, r2, #0x0
	bl FUN_02027E70
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02028190
FUN_02028190: ; 0x02028190
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_02027E5C
	add r6, r0, #0x0
	cmp r4, #0x64
	blo _020281AA
	bl FUN_02027E44
	mov r0, #0x0
	pop {r4-r6, pc}
_020281AA:
	lsl r0, r4, #0x3
	add r0, r5, r0
	add r1, r6, #0x0
	bl FUN_02027E70
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020281B8
FUN_020281B8: ; 0x020281B8
	push {r4-r6, lr}
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r4, #0x0
_020281C0:
	lsl r0, r5, #0x3
	add r0, r6, r0
	bl FUN_02027E34
	cmp r0, #0x0
	beq _020281D2
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020281D2:
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x64
	blo _020281C0
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_020281E0
FUN_020281E0: ; 0x020281E0
	mov r0, #0x1f
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_020281E8
FUN_020281E8: ; 0x020281E8
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r2, #0x1f
	mov r0, #0x0
	add r1, r7, #0x0
	lsl r2, r2, #0x6
	bl MIi_CpuClearFast
	mov r0, #0x1d
	lsl r0, r0, #0x4
	add r1, r0, #0x0
	add r2, r0, #0x0
	ldr r4, _02028224 ; =0x0000FFFF
	mov r5, #0x0
	add r6, r7, #0x0
	mov r3, #0x2
	sub r1, #0x10
	add r2, #0x1e
_0202820C:
	strh r4, [r6, r0]
	strh r4, [r6, r1]
	strb r3, [r6, r2]
	add r5, r5, #0x1
	add r6, #0x30
	cmp r5, #0x20
	blt _0202820C
	add r0, r7, #0x0
	bl FUN_0203380C
	pop {r3-r7, pc}
	nop
_02028224: .word 0x0000FFFF

	thumb_func_start FUN_02028228
FUN_02028228: ; 0x02028228
	bx lr
	.balign 4

	thumb_func_start FUN_0202822C
FUN_0202822C: ; 0x0202822C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	cmp r4, #0x20
	blt _0202823C
	bl ErrorHandling
_0202823C:
	cmp r7, #0x8
	bhi _020282D0
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202824C: ; jump table (using 16-bit offset)
	.short _0202825E - _0202824C - 2; case 0
	.short _0202826C - _0202824C - 2; case 1
	.short _0202827A - _0202824C - 2; case 2
	.short _02028286 - _0202824C - 2; case 3
	.short _02028294 - _0202824C - 2; case 4
	.short _020282A0 - _0202824C - 2; case 5
	.short _020282AE - _0202824C - 2; case 6
	.short _020282C6 - _0202824C - 2; case 7
	.short _020282BA - _0202824C - 2; case 8
_0202825E:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x1e
	lsl r0, r0, #0x4
	ldr r6, [r1, r0]
	b _020282D0
_0202826C:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x79
	lsl r0, r0, #0x2
	ldrh r6, [r1, r0]
	b _020282D0
_0202827A:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282D4 ; =0x000001E6
	ldrh r6, [r1, r0]
	b _020282D0
_02028286:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x7a
	lsl r0, r0, #0x2
	ldrh r6, [r1, r0]
	b _020282D0
_02028294:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282D8 ; =0x000001EA
	ldrh r6, [r1, r0]
	b _020282D0
_020282A0:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x7b
	lsl r0, r0, #0x2
	ldrb r6, [r1, r0]
	b _020282D0
_020282AE:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282DC ; =0x000001ED
	ldrb r6, [r1, r0]
	b _020282D0
_020282BA:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282E0 ; =0x000001EE
	ldrb r6, [r1, r0]
	b _020282D0
_020282C6:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282E4 ; =0x000001EF
	ldrb r6, [r1, r0]
_020282D0:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4
_020282D4: .word 0x000001E6
_020282D8: .word 0x000001EA
_020282DC: .word 0x000001ED
_020282E0: .word 0x000001EE
_020282E4: .word 0x000001EF

	thumb_func_start FUN_020282E8
FUN_020282E8: ; 0x020282E8
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, #0x20
	blt _020282FA
	bl ErrorHandling
_020282FA:
	cmp r7, #0x8
	bhi _02028378
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202830A: ; jump table (using 16-bit offset)
	.short _0202831C - _0202830A - 2; case 0
	.short _0202832A - _0202830A - 2; case 1
	.short _02028330 - _0202830A - 2; case 2
	.short _02028336 - _0202830A - 2; case 3
	.short _0202833C - _0202830A - 2; case 4
	.short _02028348 - _0202830A - 2; case 5
	.short _02028356 - _0202830A - 2; case 6
	.short _0202836E - _0202830A - 2; case 7
	.short _02028362 - _0202830A - 2; case 8
_0202831C:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x1e
	lsl r0, r0, #0x4
	str r6, [r1, r0]
	pop {r3-r7, pc}
_0202832A:
	bl ErrorHandling
	pop {r3-r7, pc}
_02028330:
	bl ErrorHandling
	pop {r3-r7, pc}
_02028336:
	bl ErrorHandling
	pop {r3-r7, pc}
_0202833C:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _0202837C ; =0x000001EA
	strh r6, [r1, r0]
	pop {r3-r7, pc}
_02028348:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x7b
	lsl r0, r0, #0x2
	strb r6, [r1, r0]
	pop {r3-r7, pc}
_02028356:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02028380 ; =0x000001ED
	strb r6, [r1, r0]
	pop {r3-r7, pc}
_02028362:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02028384 ; =0x000001EE
	strb r6, [r1, r0]
	pop {r3-r7, pc}
_0202836E:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02028388 ; =0x000001EF
	strb r6, [r1, r0]
_02028378:
	pop {r3-r7, pc}
	nop
_0202837C: .word 0x000001EA
_02028380: .word 0x000001ED
_02028384: .word 0x000001EE
_02028388: .word 0x000001EF

	thumb_func_start FUN_0202838C
FUN_0202838C: ; 0x0202838C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _0202839A
	bl ErrorHandling
_0202839A:
	mov r0, #0xc
	add r5, #0x40
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_020283A4
FUN_020283A4: ; 0x020283A4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _020283B2
	bl ErrorHandling
_020283B2:
	mov r0, #0x1d
	lsl r0, r0, #0x4
	add r1, r5, r0
	mov r0, #0x30
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_020283C0
FUN_020283C0: ; 0x020283C0
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x20
	blt _020283D0
	bl ErrorHandling
_020283D0:
	mov r1, #0x1d
	lsl r1, r1, #0x4
	add r2, r5, r1
	mov r1, #0x30
	mul r1, r4
	add r1, r2, r1
	add r0, r6, #0x0
	mov r2, #0x10
	bl FUN_02021EF0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020283E8
FUN_020283E8: ; 0x020283E8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _020283F6
	bl ErrorHandling
_020283F6:
	mov r0, #0x7
	lsl r0, r0, #0x6
	add r1, r5, r0
	mov r0, #0x30
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_02028404
FUN_02028404: ; 0x02028404
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x20
	blt _02028414
	bl ErrorHandling
_02028414:
	mov r1, #0x7
	lsl r1, r1, #0x6
	add r2, r5, r1
	mov r1, #0x30
	mul r1, r4
	add r1, r2, r1
	add r0, r6, #0x0
	mov r2, #0x10
	bl FUN_02021EF0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202842C
FUN_0202842C: ; 0x0202842C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _0202843A
	bl ErrorHandling
_0202843A:
	mov r0, #0xc
	add r5, #0x40
	mul r0, r4
	add r0, r5, r0
	bl FUN_0209700C
	pop {r3-r5, pc}

	thumb_func_start FUN_02028448
FUN_02028448: ; 0x02028448
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02028450:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202842C
	cmp r0, #0x0
	beq _0202845E
	add r5, r5, #0x1
_0202845E:
	add r4, r4, #0x1
	cmp r4, #0x20
	blt _02028450
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02028468
FUN_02028468: ; 0x02028468
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	cmp r5, #0x20
	blt _02028478
	bl ErrorHandling
_02028478:
	cmp r5, #0x1f
	bge _020284D2
	mov r1, #0x7
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x6
	add r0, r0, r1
	str r0, [sp, #0x4]
	mov r0, #0x30
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	add r6, r0, r1
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	str r0, [sp, #0x8]
	add r0, #0x40
	str r0, [sp, #0x8]
	mov r0, #0xc
	mul r1, r0
	ldr r0, [sp, #0x8]
	add r4, r0, r1
_020284A2:
	add r7, r5, #0x1
	mov r0, #0x30
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	mov r2, #0x30
	add r0, r0, r1
	add r1, r6, #0x0
	bl MI_CpuCopy8
	mov r0, #0xc
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x8]
	mov r2, #0xc
	add r0, r0, r1
	add r1, r4, #0x0
	bl MI_CpuCopy8
	add r5, r5, #0x1
	add r6, #0x30
	add r4, #0xc
	cmp r5, #0x1f
	blt _020284A2
_020284D2:
	mov r2, #0x7
	ldr r1, [sp, #0x0]
	lsl r2, r2, #0x6
	add r2, r1, r2
	mov r1, #0x5d
	lsl r1, r1, #0x4
	add r1, r2, r1
	mov r0, #0x0
	mov r2, #0x30
	bl MIi_CpuClearFast
	ldr r2, [sp, #0x0]
	mov r1, #0x5d
	add r2, #0x40
	lsl r1, r1, #0x2
	add r1, r2, r1
	mov r0, #0x0
	mov r2, #0xc
	bl MIi_CpuClearFast
	mov r2, #0x7a
	lsl r2, r2, #0x4
	add r1, r2, #0x0
	ldr r3, _02028514 ; =0x0000FFFF
	ldr r0, [sp, #0x0]
	sub r1, #0x10
	strh r3, [r0, r2]
	strh r3, [r0, r1]
	mov r1, #0x2
	add r2, #0x1e
	strb r1, [r0, r2]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02028514: .word 0x0000FFFF

	thumb_func_start FUN_02028518
FUN_02028518: ; 0x02028518
	push {r4-r7, lr}
	sub sp, #0xc
	str r2, [sp, #0x4]
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	mov r2, #0x30
	add r5, r0, #0x0
	mov r0, #0x7
	lsl r0, r0, #0x6
	add r3, r1, #0x0
	mul r5, r2
	add r4, r7, r0
	mul r3, r2
	str r1, [sp, #0x0]
	add r0, r4, r5
	add r1, r4, r3
	bl MI_CpuCopy8
	ldr r0, [sp, #0x4]
	add r6, r7, #0x0
	mov r3, #0xc
	add r1, r0, #0x0
	mul r1, r3
	add r6, #0x40
	str r1, [sp, #0x8]
	add r0, r6, r1
	ldr r1, [sp, #0x0]
	add r2, r1, #0x0
	mul r2, r3
	add r1, r6, r2
	add r2, r3, #0x0
	bl MI_CpuCopy8
	mov r0, #0x0
	add r1, r4, r5
	mov r2, #0x30
	bl MIi_CpuClearFast
	ldr r1, [sp, #0x8]
	mov r0, #0x0
	add r1, r6, r1
	mov r2, #0xc
	bl MIi_CpuClearFast
	mov r0, #0x1d
	ldr r1, _02028588 ; =0x0000FFFF
	add r2, r7, r5
	lsl r0, r0, #0x4
	strh r1, [r2, r0]
	strh r1, [r4, r5]
	mov r1, #0x2
	add r0, #0x1e
	strb r1, [r2, r0]
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02028588: .word 0x0000FFFF

	thumb_func_start FUN_0202858C
FUN_0202858C: ; 0x0202858C
	push {r3-r7, lr}
	mov r5, #0x0
	mvn r5, r5
	add r6, r0, #0x0
	mov r4, #0x0
	add r7, r5, #0x0
_02028598:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202842C
	cmp r0, #0x0
	beq _020285BC
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	beq _020285C6
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02028518
	add r4, r7, #0x0
	add r5, r7, #0x0
	b _020285C6
_020285BC:
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	bne _020285C6
	add r5, r4, #0x0
_020285C6:
	add r4, r4, #0x1
	cmp r4, #0x20
	blt _02028598
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020285D0
FUN_020285D0: ; 0x020285D0
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, sp, #0x0
	bl FUN_020126B4
	mov r0, #0x30
	add r2, r4, #0x0
	mul r2, r0
	mov r0, #0x7d
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x4
	add r1, r1, r0
	ldr r0, _02028604 ; =0x000001EA
	add r3, r5, r2
	strh r1, [r3, r0]
	add r1, r0, #0x2
	ldr r2, [sp, #0x4]
	add r0, r0, #0x3
	strb r2, [r3, r1]
	ldr r1, [sp, #0x8]
	strb r1, [r3, r0]
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02028604: .word 0x000001EA

	thumb_func_start FUN_02028608
FUN_02028608: ; 0x02028608
	push {r4-r6, lr}
	mov r5, #0x79
	add r4, r0, #0x0
	mov r0, #0x30
	lsl r5, r5, #0x2
	mul r0, r1
	add r5, r4, r5
	ldrh r6, [r5, r0]
	add r2, r6, r2
	strh r2, [r5, r0]
	ldrh r6, [r5, r0]
	ldr r2, _0202865C ; =0x0000270F
	cmp r6, r2
	bls _02028626
	strh r2, [r5, r0]
_02028626:
	ldr r2, _02028660 ; =0x000001E6
	add r2, r4, r2
	ldrh r5, [r2, r0]
	add r3, r5, r3
	strh r3, [r2, r0]
	ldrh r5, [r2, r0]
	ldr r3, _0202865C ; =0x0000270F
	cmp r5, r3
	bls _0202863A
	strh r3, [r2, r0]
_0202863A:
	mov r2, #0x7a
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldrh r5, [r2, r0]
	ldr r3, [sp, #0x10]
	add r3, r5, r3
	strh r3, [r2, r0]
	ldrh r5, [r2, r0]
	ldr r3, _0202865C ; =0x0000270F
	cmp r5, r3
	bls _02028652
	strh r3, [r2, r0]
_02028652:
	add r0, r4, #0x0
	bl FUN_020285D0
	pop {r4-r6, pc}
	nop
_0202865C: .word 0x0000270F
_02028660: .word 0x000001E6

	thumb_func_start FUN_02028664
FUN_02028664: ; 0x02028664
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r3, #0x79
	mov r0, #0x30
	add r4, r1, #0x0
	mul r4, r0
	lsl r3, r3, #0x2
	mul r0, r2
	add r2, r5, r3
	add r6, r5, r4
	ldrh r1, [r2, r0]
	ldrh r3, [r6, r3]
	add r1, r1, r3
	strh r1, [r2, r0]
	ldrh r3, [r2, r0]
	ldr r1, _020286E0 ; =0x0000270F
	cmp r3, r1
	bls _0202868A
	strh r1, [r2, r0]
_0202868A:
	ldr r3, _020286E4 ; =0x000001E6
	add r6, r5, r4
	add r2, r5, r3
	ldrh r1, [r2, r0]
	ldrh r3, [r6, r3]
	add r1, r1, r3
	strh r1, [r2, r0]
	ldrh r3, [r2, r0]
	ldr r1, _020286E0 ; =0x0000270F
	cmp r3, r1
	bls _020286A2
	strh r1, [r2, r0]
_020286A2:
	mov r3, #0x7a
	lsl r3, r3, #0x2
	add r2, r5, r3
	add r6, r5, r4
	ldrh r1, [r2, r0]
	ldrh r3, [r6, r3]
	add r1, r1, r3
	strh r1, [r2, r0]
	ldrh r3, [r2, r0]
	ldr r1, _020286E0 ; =0x0000270F
	cmp r3, r1
	bls _020286BC
	strh r1, [r2, r0]
_020286BC:
	mov r0, #0x7
	lsl r0, r0, #0x6
	add r6, r5, r0
	mov r0, #0x0
	add r1, r6, r4
	mov r2, #0x30
	bl MIi_CpuClearFast
	mov r0, #0x1d
	ldr r1, _020286E8 ; =0x0000FFFF
	add r2, r5, r4
	lsl r0, r0, #0x4
	strh r1, [r2, r0]
	strh r1, [r6, r4]
	mov r1, #0x2
	add r0, #0x1e
	strb r1, [r2, r0]
	pop {r4-r6, pc}
	.balign 4
_020286E0: .word 0x0000270F
_020286E4: .word 0x000001E6
_020286E8: .word 0x0000FFFF

	thumb_func_start FUN_020286EC
FUN_020286EC: ; 0x020286EC
	ldr r3, _020286F4 ; =FUN_02022610
	mov r1, #0x1d
	bx r3
	nop
_020286F4: .word FUN_02022610

	thumb_func_start FUN_020286F8
FUN_020286F8: ; 0x020286F8
	mov r0, #0x42
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02028700
FUN_02028700: ; 0x02028700
	push {r4-r5}
	add r5, r2, #0x0
	mov r3, #0x2c
	add r2, r1, #0x0
	mul r2, r3
	mul r5, r3
	add r4, r0, r2
	add r3, r0, r5
	mov r2, #0x5
_02028712:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02028712
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02028724
FUN_02028724: ; 0x02028724
	push {r4, lr}
	add r4, r0, #0x0
	mov r2, #0x42
	mov r0, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl MIi_CpuClearFast
	ldr r0, _0202874C ; =0x0000FFFF
	mov r1, #0x0
	add r2, r4, #0x0
_0202873A:
	strh r0, [r2, #0x0]
	strh r0, [r2, #0x10]
	add r1, r1, #0x1
	add r2, #0x2c
	cmp r1, #0x6
	blt _0202873A
	ldr r0, _02028750 ; =0x021C59D0
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_0202874C: .word 0x0000FFFF
_02028750: .word 0x021C59D0

	thumb_func_start FUN_02028754
FUN_02028754: ; 0x02028754
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	mov r7, #0x0
_0202875C:
	mov r4, #0x0
	cmp r6, #0x0
	bls _02028770
_02028762:
	ldr r0, [r5, #0x28]
	bl rand_ALT
	add r4, r4, #0x1
	str r0, [r5, #0x28]
	cmp r4, r6
	blo _02028762
_02028770:
	add r7, r7, #0x1
	add r5, #0x2c
	cmp r7, #0x6
	blo _0202875C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202877C
FUN_0202877C: ; 0x0202877C
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x24]
	bx lr
	.balign 4

	thumb_func_start FUN_02028788
FUN_02028788: ; 0x02028788
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x2c
	add r4, r1, #0x0
	mul r4, r0
	add r0, r5, r4
	str r2, [r0, #0x24]
	add r0, r2, #0x0
	bl rand_ALT
	add r1, r5, r4
	str r0, [r1, #0x28]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020287A4
FUN_020287A4: ; 0x020287A4
	ldr r0, [r0, #0x54]
	bx lr

	thumb_func_start FUN_020287A8
FUN_020287A8: ; 0x020287A8
	cmp r2, #0x0
	bne _020287B4
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	bx lr
_020287B4:
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	add r0, #0x10
	bx lr
	.balign 4

	thumb_func_start FUN_020287C0
FUN_020287C0: ; 0x020287C0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r2, #0x0
	bne _020287D8
	mov r2, #0x2c
	mul r2, r1
	add r1, r4, r2
	add r0, r3, #0x0
	mov r2, #0x8
	bl FUN_02021EF0
	pop {r4, pc}
_020287D8:
	mov r2, #0x2c
	mul r2, r1
	add r1, r4, r2
	add r0, r3, #0x0
	add r1, #0x10
	mov r2, #0x8
	bl FUN_02021EF0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020287EC
FUN_020287EC: ; 0x020287EC
	mov r3, #0x2c
	mul r3, r1
	add r0, r0, r3
	add r0, #0x20
	strb r2, [r0, #0x0]
	bx lr

	thumb_func_start FUN_020287F8
FUN_020287F8: ; 0x020287F8
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02028804
FUN_02028804: ; 0x02028804
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02028810
FUN_02028810: ; 0x02028810
	mov r3, #0x2c
	mul r3, r1
	add r0, r0, r3
	add r0, #0x21
	strb r2, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202881C
FUN_0202881C: ; 0x0202881C
	ldr r3, _02028824 ; =FUN_02022610
	mov r1, #0x11
	bx r3
	nop
_02028824: .word FUN_02022610

	thumb_func_start FUN_02028828
FUN_02028828: ; 0x02028828
	push {r3, lr}
	mov r2, #0x2c
	mul r2, r1
	add r0, r0, r2
	bl FUN_0202888C
	cmp r0, #0x0
	bne _0202883C
	mov r0, #0x1
	pop {r3, pc}
_0202883C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02028840
FUN_02028840: ; 0x02028840
	mov r2, #0x2c
	add r3, r0, #0x0
	mul r2, r1
	add r1, r3, r2
	ldr r3, _02028850 ; =FUN_020288AC
	add r0, #0x2c
	bx r3
	nop
_02028850: .word FUN_020288AC

	thumb_func_start FUN_02028854
FUN_02028854: ; 0x02028854
	push {r3-r7, lr}
	add r6, r1, #0x0
	ldrh r1, [r6, #0x0]
	add r5, r0, #0x0
	ldr r0, _02028888 ; =0x0000FFFF
	cmp r1, r0
	bne _02028866
	mov r0, #0x0
	pop {r3-r7, pc}
_02028866:
	mov r4, #0x0
	mov r7, #0x8
_0202886A:
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl StringNotEqualN
	cmp r0, #0x0
	bne _0202887C
	mov r0, #0x1
	pop {r3-r7, pc}
_0202887C:
	add r4, r4, #0x1
	add r5, #0x2c
	cmp r4, #0x6
	blt _0202886A
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02028888: .word 0x0000FFFF

	thumb_func_start FUN_0202888C
FUN_0202888C: ; 0x0202888C
	ldrh r2, [r0, #0x0]
	ldr r1, _020288A8 ; =0x0000FFFF
	cmp r2, r1
	bne _02028898
	mov r0, #0x1
	bx lr
_02028898:
	ldrh r0, [r0, #0x10]
	cmp r0, r1
	bne _020288A2
	mov r0, #0x1
	bx lr
_020288A2:
	mov r0, #0x0
	bx lr
	nop
_020288A8: .word 0x0000FFFF

	thumb_func_start FUN_020288AC
FUN_020288AC: ; 0x020288AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, #0x10
	add r1, #0x10
	mov r2, #0x8
	bl StringNotEqualN
	cmp r0, #0x0
	beq _020288C4
	mov r0, #0x0
	pop {r3-r5, pc}
_020288C4:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x8
	bl StringNotEqualN
	cmp r0, #0x0
	beq _020288D6
	mov r0, #0x0
	pop {r3-r5, pc}
_020288D6:
	add r0, r5, #0x0
	add r0, #0x20
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	beq _020288EA
	mov r0, #0x0
	pop {r3-r5, pc}
_020288EA:
	add r0, r5, #0x0
	add r0, #0x21
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x21
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	beq _020288FE
	mov r0, #0x0
	pop {r3-r5, pc}
_020288FE:
	ldr r1, [r5, #0x24]
	ldr r0, [r4, #0x24]
	cmp r1, r0
	bne _0202890A
	mov r0, #0x1
	pop {r3-r5, pc}
_0202890A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02028910
FUN_02028910: ; 0x02028910
	mov r1, #0x0
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02028918
FUN_02028918: ; 0x02028918
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202892C ; =0x0000C350
	add r4, r1, #0x0
	cmp r4, r0
	bls _02028928
	bl ErrorHandling
_02028928:
	strh r4, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4
_0202892C: .word 0x0000C350

	thumb_func_start FUN_02028930
FUN_02028930: ; 0x02028930
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02028934
FUN_02028934: ; 0x02028934
	ldrh r3, [r0, #0x0]
	ldr r2, _02028950 ; =0x0000C350
	cmp r3, r2
	blo _02028940
	mov r0, #0x0
	bx lr
_02028940:
	add r1, r3, r1
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	cmp r1, r2
	bls _0202894C
	strh r2, [r0, #0x0]
_0202894C:
	mov r0, #0x1
	bx lr
	.balign 4
_02028950: .word 0x0000C350

	thumb_func_start FUN_02028954
FUN_02028954: ; 0x02028954
	ldrh r0, [r0, #0x0]
	add r1, r1, r0
	ldr r0, _02028968 ; =0x0000C350
	cmp r1, r0
	bhi _02028962
	mov r0, #0x1
	bx lr
_02028962:
	mov r0, #0x0
	bx lr
	nop
_02028968: .word 0x0000C350

	thumb_func_start FUN_0202896C
FUN_0202896C: ; 0x0202896C
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	bhs _02028976
	mov r0, #0x0
	bx lr
_02028976:
	sub r1, r2, r1
	strh r1, [r0, #0x0]
	mov r0, #0x1
	bx lr
	.balign 4

	thumb_func_start FUN_02028980
FUN_02028980: ; 0x02028980
	mov r0, #0x46
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02028988
FUN_02028988: ; 0x02028988
	ldr r3, _02028990 ; =memset
	mov r1, #0x0
	mov r2, #0x70
	bx r3
	.balign 4
_02028990: .word memset

	thumb_func_start FUN_02028994
FUN_02028994: ; 0x02028994
	ldr r3, _020289A0 ; =memset
	mov r2, #0x46
	mov r1, #0x0
	lsl r2, r2, #0x4
	bx r3
	nop
_020289A0: .word memset

	thumb_func_start FUN_020289A4
FUN_020289A4: ; 0x020289A4
	ldr r3, _020289AC ; =FUN_02022610
	mov r1, #0x12
	bx r3
	nop
_020289AC: .word FUN_02022610

	thumb_func_start FUN_020289B0
FUN_020289B0: ; 0x020289B0
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r0, #0x0
	cmp r1, #0x1
	beq _020289C0
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_020289C0:
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r0, [r7, #0x0]
	lsl r1, r0, #0x15
	lsr r3, r1, #0x1c
	beq _02028A18
	lsl r1, r0, #0x19
	lsr r2, r1, #0x19
	ldr r1, [sp, #0x0]
	cmp r2, r1
	bne _020289F2
	ldr r1, [sp, #0x4]
	cmp r3, r1
	bne _020289F2
	lsl r1, r0, #0xd
	lsr r2, r1, #0x1b
	ldr r1, [sp, #0x8]
	cmp r2, r1
	bne _020289F2
	lsl r0, r0, #0x12
	lsr r1, r0, #0x1d
	ldr r0, [sp, #0xc]
	cmp r1, r0
	beq _02028A18
_020289F2:
	mov r0, #0x3f
	lsl r0, r0, #0x4
	mov r5, #0x9
	add r6, r7, r0
_020289FA:
	add r4, r6, #0x0
	sub r4, #0x70
	add r3, r6, #0x0
	mov r2, #0xe
_02028A02:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02028A02
	sub r5, r5, #0x1
	sub r6, #0x70
	cmp r5, #0x1
	bge _020289FA
	add r0, r7, #0x0
	bl FUN_02028988
_02028A18:
	add r0, r7, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02028A20
FUN_02028A20: ; 0x02028A20
	push {r4, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	cmp r1, #0x1
	beq _02028A30
	add sp, #0x20
	mov r0, #0x0
	pop {r4, pc}
_02028A30:
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1c
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0xd
	lsr r0, r0, #0x1b
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x12
	lsr r0, r0, #0x1d
	str r0, [sp, #0x1c]
	add r0, sp, #0x0
	bl FUN_02012710
	add r4, r0, #0x0
	add r0, sp, #0x10
	bl FUN_02012710
	ldr r2, [sp, #0x4]
	sub r0, r4, r0
	cmp r2, #0xc
	bne _02028A7E
	ldr r1, [sp, #0x8]
	cmp r1, #0x1f
	bne _02028A7E
	ldr r1, [sp, #0x14]
	cmp r1, #0x1
	bne _02028A7E
	ldr r1, [sp, #0x18]
	cmp r1, #0x1
	beq _02028A94
_02028A7E:
	cmp r2, #0x1
	bne _02028AAC
	ldr r1, [sp, #0x8]
	cmp r1, #0x1
	bne _02028AAC
	ldr r1, [sp, #0x14]
	cmp r1, #0xc
	bne _02028AAC
	ldr r1, [sp, #0x18]
	cmp r1, #0x1f
	bne _02028AAC
_02028A94:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	sub r1, r1, r0
	cmp r1, #0x2
	bge _02028AA6
	mov r0, #0x1
	mvn r0, r0
	cmp r1, r0
	bgt _02028ACC
_02028AA6:
	add sp, #0x20
	mov r0, #0x1
	pop {r4, pc}
_02028AAC:
	mov r1, #0x1
	mvn r1, r1
	cmp r0, r1
	ble _02028AB8
	cmp r0, #0x2
	blt _02028ABE
_02028AB8:
	add sp, #0x20
	mov r0, #0x1
	pop {r4, pc}
_02028ABE:
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	beq _02028ACC
	add sp, #0x20
	mov r0, #0x1
	pop {r4, pc}
_02028ACC:
	mov r0, #0x0
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028AD4
FUN_02028AD4: ; 0x02028AD4
	push {r4, lr}
	add r4, r1, #0x0
	cmp r0, #0x0
	beq _02028B12
	cmp r2, #0x4
	bhi _02028B12
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02028AEC: ; jump table (using 16-bit offset)
	.short _02028AF6 - _02028AEC - 2; case 0
	.short _02028AFC - _02028AEC - 2; case 1
	.short _02028B02 - _02028AEC - 2; case 2
	.short _02028B08 - _02028AEC - 2; case 3
	.short _02028B0E - _02028AEC - 2; case 4
_02028AF6:
	bl FUN_02028B1C
	b _02028B12
_02028AFC:
	bl FUN_02028B5C
	b _02028B12
_02028B02:
	bl FUN_02028BF0
	b _02028B12
_02028B08:
	bl FUN_02028BFC
	b _02028B12
_02028B0E:
	bl FUN_02028C08
_02028B12:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028B1C
FUN_02028B1C: ; 0x02028B1C
	push {r4-r5}
	ldr r3, [r0, #0x0]
	lsl r2, r3, #0x19
	lsr r5, r2, #0x19
	ldr r2, [r1, #0x0]
	lsl r4, r2, #0x19
	lsr r4, r4, #0x19
	cmp r5, r4
	bne _02028B52
	lsl r4, r3, #0x15
	lsr r5, r4, #0x1c
	lsl r4, r2, #0x15
	lsr r4, r4, #0x1c
	cmp r5, r4
	bne _02028B52
	lsl r4, r3, #0xd
	lsr r5, r4, #0x1b
	lsl r4, r2, #0xd
	lsr r4, r4, #0x1b
	cmp r5, r4
	bne _02028B52
	lsl r3, r3, #0x12
	lsl r2, r2, #0x12
	lsr r3, r3, #0x1d
	lsr r2, r2, #0x1d
	cmp r3, r2
	beq _02028B56
_02028B52:
	ldr r1, [r1, #0x0]
	str r1, [r0, #0x0]
_02028B56:
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02028B5C
FUN_02028B5C: ; 0x02028B5C
	push {r3, lr}
	ldrb r2, [r1, #0x0]
	cmp r2, #0x23
	bhi _02028BEE
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02028B70: ; jump table (using 16-bit offset)
	.short _02028BEE - _02028B70 - 2; case 0
	.short _02028BB8 - _02028B70 - 2; case 1
	.short _02028BB8 - _02028B70 - 2; case 2
	.short _02028BB8 - _02028B70 - 2; case 3
	.short _02028BB8 - _02028B70 - 2; case 4
	.short _02028BB8 - _02028B70 - 2; case 5
	.short _02028BB8 - _02028B70 - 2; case 6
	.short _02028BB8 - _02028B70 - 2; case 7
	.short _02028BB8 - _02028B70 - 2; case 8
	.short _02028BC0 - _02028B70 - 2; case 9
	.short _02028BC0 - _02028B70 - 2; case 10
	.short _02028BC8 - _02028B70 - 2; case 11
	.short _02028BD0 - _02028B70 - 2; case 12
	.short _02028BD8 - _02028B70 - 2; case 13
	.short _02028BD8 - _02028B70 - 2; case 14
	.short _02028BD8 - _02028B70 - 2; case 15
	.short _02028BB8 - _02028B70 - 2; case 16
	.short _02028BB8 - _02028B70 - 2; case 17
	.short _02028BE0 - _02028B70 - 2; case 18
	.short _02028BE8 - _02028B70 - 2; case 19
	.short _02028BE8 - _02028B70 - 2; case 20
	.short _02028BE8 - _02028B70 - 2; case 21
	.short _02028BE8 - _02028B70 - 2; case 22
	.short _02028BE8 - _02028B70 - 2; case 23
	.short _02028BE8 - _02028B70 - 2; case 24
	.short _02028BE8 - _02028B70 - 2; case 25
	.short _02028BE8 - _02028B70 - 2; case 26
	.short _02028BE8 - _02028B70 - 2; case 27
	.short _02028BE8 - _02028B70 - 2; case 28
	.short _02028BE8 - _02028B70 - 2; case 29
	.short _02028BE8 - _02028B70 - 2; case 30
	.short _02028BEE - _02028B70 - 2; case 31
	.short _02028BE8 - _02028B70 - 2; case 32
	.short _02028BE8 - _02028B70 - 2; case 33
	.short _02028BB8 - _02028B70 - 2; case 34
	.short _02028BB8 - _02028B70 - 2; case 35
_02028BB8:
	add r0, r0, #0x4
	bl FUN_02028CE8
	pop {r3, pc}
_02028BC0:
	add r0, r0, #0x4
	bl FUN_02028D98
	pop {r3, pc}
_02028BC8:
	add r0, r0, #0x4
	bl FUN_02028D44
	pop {r3, pc}
_02028BD0:
	add r0, r0, #0x4
	bl FUN_02028D24
	pop {r3, pc}
_02028BD8:
	add r0, r0, #0x4
	bl FUN_02028DFC
	pop {r3, pc}
_02028BE0:
	add r0, r0, #0x4
	bl FUN_02028E44
	pop {r3, pc}
_02028BE8:
	add r0, r0, #0x4
	bl FUN_02028E8C
_02028BEE:
	pop {r3, pc}

	thumb_func_start FUN_02028BF0
FUN_02028BF0: ; 0x02028BF0
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x14]
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x16]
	bx lr
	.balign 4

	thumb_func_start FUN_02028BFC
FUN_02028BFC: ; 0x02028BFC
	ldrh r2, [r1, #0x0]
	strh r2, [r0, #0x18]
	ldrh r1, [r1, #0x2]
	strh r1, [r0, #0x1a]
	bx lr
	.balign 4

	thumb_func_start FUN_02028C08
FUN_02028C08: ; 0x02028C08
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl FUN_02028CA8
	ldrb r1, [r4, #0x0]
	cmp r1, #0x10
	bhi _02028C6E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02028C24: ; jump table (using 16-bit offset)
	.short _02028C6E - _02028C24 - 2; case 0
	.short _02028C46 - _02028C24 - 2; case 1
	.short _02028C46 - _02028C24 - 2; case 2
	.short _02028C46 - _02028C24 - 2; case 3
	.short _02028C46 - _02028C24 - 2; case 4
	.short _02028C46 - _02028C24 - 2; case 5
	.short _02028C4E - _02028C24 - 2; case 6
	.short _02028C56 - _02028C24 - 2; case 7
	.short _02028C5E - _02028C24 - 2; case 8
	.short _02028C56 - _02028C24 - 2; case 9
	.short _02028C5E - _02028C24 - 2; case 10
	.short _02028C46 - _02028C24 - 2; case 11
	.short _02028C5E - _02028C24 - 2; case 12
	.short _02028C68 - _02028C24 - 2; case 13
	.short _02028C5E - _02028C24 - 2; case 14
	.short _02028C56 - _02028C24 - 2; case 15
	.short _02028C5E - _02028C24 - 2; case 16
_02028C46:
	add r1, r4, #0x0
	bl FUN_02028ED4
	pop {r3-r5, pc}
_02028C4E:
	add r1, r4, #0x0
	bl FUN_02028F10
	pop {r3-r5, pc}
_02028C56:
	add r1, r4, #0x0
	bl FUN_02028F2C
	pop {r3-r5, pc}
_02028C5E:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02028F60
	pop {r3-r5, pc}
_02028C68:
	add r1, r4, #0x0
	bl FUN_02028F94
_02028C6E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02028C70
FUN_02028C70: ; 0x02028C70
	push {r3-r4}
	mov r3, #0x0
	add r4, r0, #0x0
	mov r1, #0x3f
_02028C78:
	ldr r2, [r4, #0x0]
	tst r2, r1
	bne _02028C86
	lsl r1, r3, #0x2
	add r0, r0, r1
	pop {r3-r4}
	bx lr
_02028C86:
	add r3, r3, #0x1
	add r4, r4, #0x4
	cmp r3, #0x4
	blo _02028C78
	mov r3, #0x0
	add r2, r0, #0x0
_02028C92:
	ldr r1, [r2, #0x4]
	add r3, r3, #0x1
	stmia r2!, {r1}
	cmp r3, #0x3
	blo _02028C92
	lsl r2, r3, #0x2
	mov r1, #0x0
	str r1, [r0, r2]
	add r0, r0, r2
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02028CA8
FUN_02028CA8: ; 0x02028CA8
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
_02028CB0:
	ldrb r0, [r2, #0x1c]
	cmp r0, #0x0
	bne _02028CC0
	mov r0, #0x2a
	add r4, #0x1c
	mul r0, r1
	add r0, r4, r0
	pop {r4, pc}
_02028CC0:
	add r1, r1, #0x1
	add r2, #0x2a
	cmp r1, #0x2
	blo _02028CB0
	add r0, r4, #0x0
	add r1, r4, #0x0
	add r0, #0x1c
	add r1, #0x46
	mov r2, #0x2a
	bl memcpy
	add r4, #0x46
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x2a
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028CE8
FUN_02028CE8: ; 0x02028CE8
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028CF0:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028CFE
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028CF0
_02028CFE:
	cmp r2, #0x0
	beq _02028D14
	lsl r2, r2, #0x2
	add r2, r0, r2
	sub r2, r2, #0x4
	ldr r3, [r2, #0x0]
	mov r2, #0x3f
	ldrb r1, [r4, #0x0]
	and r2, r3
	cmp r1, r2
	beq _02028D20
_02028D14:
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	str r1, [r0, #0x0]
_02028D20:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02028D24
FUN_02028D24: ; 0x02028D24
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	ldrh r2, [r4, #0x2]
	lsl r3, r2, #0x10
	ldrh r2, [r4, #0x4]
	lsl r2, r2, #0x16
	lsr r2, r2, #0x10
	orr r2, r3
	orr r1, r2
	str r1, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02028D44
FUN_02028D44: ; 0x02028D44
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	mov r3, #0x3f
_02028D4C:
	lsl r1, r2, #0x2
	ldr r5, [r0, r1]
	and r5, r3
	cmp r5, #0xb
	bne _02028D72
	mov r3, #0x0
	str r3, [r0, r1]
	cmp r2, #0x3
	bhs _02028D7C
_02028D5E:
	lsl r3, r2, #0x2
	add r1, r0, r3
	ldr r1, [r1, #0x4]
	str r1, [r0, r3]
	add r1, r2, #0x1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	cmp r2, #0x3
	blo _02028D5E
	b _02028D7C
_02028D72:
	add r1, r2, #0x1
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	cmp r2, #0x4
	blo _02028D4C
_02028D7C:
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	ldrh r2, [r4, #0x2]
	lsl r3, r2, #0x10
	ldrh r2, [r4, #0x4]
	lsl r2, r2, #0x16
	lsr r2, r2, #0x10
	orr r2, r3
	orr r1, r2
	str r1, [r0, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02028D98
FUN_02028D98: ; 0x02028D98
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r6, #0x0
	mov r1, #0x3f
_02028DA0:
	lsl r5, r6, #0x2
	ldr r3, [r0, r5]
	add r2, r3, #0x0
	and r2, r1
	cmp r2, #0x9
	bne _02028DD4
	lsr r3, r3, #0x10
	lsl r3, r3, #0x10
	ldrh r2, [r4, #0x2]
	lsr r3, r3, #0x10
	cmp r2, r3
	bne _02028DD4
	mov r1, #0x0
	str r1, [r0, r5]
	cmp r6, #0x3
	bhs _02028DDE
_02028DC0:
	lsl r2, r6, #0x2
	add r1, r0, r2
	ldr r1, [r1, #0x4]
	str r1, [r0, r2]
	add r1, r6, #0x1
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	cmp r6, #0x3
	blo _02028DC0
	b _02028DDE
_02028DD4:
	add r2, r6, #0x1
	lsl r2, r2, #0x10
	lsr r6, r2, #0x10
	cmp r6, #0x4
	blo _02028DA0
_02028DDE:
	bl FUN_02028C70
	ldrb r2, [r4, #0x0]
	mov r1, #0x3f
	and r1, r2
	ldrh r2, [r4, #0x2]
	lsl r3, r2, #0x10
	ldrh r2, [r4, #0x4]
	lsl r2, r2, #0x16
	lsr r2, r2, #0x10
	orr r2, r3
	orr r1, r2
	str r1, [r0, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02028DFC
FUN_02028DFC: ; 0x02028DFC
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028E04:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028E12
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028E04
_02028E12:
	cmp r2, #0x0
	beq _02028E30
	lsl r1, r2, #0x2
	add r1, r0, r1
	sub r1, r1, #0x4
	ldr r3, [r1, #0x0]
	mov r1, #0x3f
	ldrb r2, [r4, #0x0]
	and r1, r3
	cmp r2, r1
	bne _02028E30
	ldrh r2, [r4, #0x2]
	lsr r1, r3, #0x10
	cmp r2, r1
	beq _02028E42
_02028E30:
	bl FUN_02028C70
	ldrh r1, [r4, #0x2]
	ldrb r2, [r4, #0x0]
	lsl r3, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
_02028E42:
	pop {r4, pc}

	thumb_func_start FUN_02028E44
FUN_02028E44: ; 0x02028E44
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028E4C:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028E5A
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028E4C
_02028E5A:
	cmp r2, #0x0
	beq _02028E78
	lsl r1, r2, #0x2
	add r1, r0, r1
	sub r1, r1, #0x4
	ldr r3, [r1, #0x0]
	mov r1, #0x3f
	ldrb r2, [r4, #0x0]
	and r1, r3
	cmp r2, r1
	bne _02028E78
	ldrh r2, [r4, #0x6]
	lsr r1, r3, #0x10
	cmp r2, r1
	beq _02028E8A
_02028E78:
	bl FUN_02028C70
	ldrh r1, [r4, #0x6]
	ldrb r2, [r4, #0x0]
	lsl r3, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
_02028E8A:
	pop {r4, pc}

	thumb_func_start FUN_02028E8C
FUN_02028E8C: ; 0x02028E8C
	push {r4, lr}
	add r4, r1, #0x0
	mov r2, #0x0
	add r3, r0, #0x0
_02028E94:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _02028EA2
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, #0x4
	blo _02028E94
_02028EA2:
	cmp r2, #0x0
	beq _02028EC0
	lsl r1, r2, #0x2
	add r1, r0, r1
	sub r1, r1, #0x4
	ldr r3, [r1, #0x0]
	mov r1, #0x3f
	ldrb r2, [r4, #0x0]
	and r1, r3
	cmp r2, r1
	bne _02028EC0
	ldrh r2, [r4, #0x2]
	lsr r1, r3, #0x10
	cmp r2, r1
	beq _02028ED2
_02028EC0:
	bl FUN_02028C70
	ldrh r1, [r4, #0x2]
	ldrb r2, [r4, #0x0]
	lsl r3, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x0]
_02028ED2:
	pop {r4, pc}

	thumb_func_start FUN_02028ED4
FUN_02028ED4: ; 0x02028ED4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrb r0, [r4, #0x0]
	strb r0, [r5, #0x0]
	ldrb r3, [r4, #0x1]
	lsl r1, r3, #0x1c
	lsr r2, r1, #0x1a
	lsl r1, r3, #0x1b
	lsr r1, r1, #0x1f
	lsl r0, r3, #0x1a
	lsl r1, r1, #0x1
	orr r1, r2
	lsr r0, r0, #0x1f
	orr r0, r1
	strb r0, [r5, #0x1]
	add r0, r4, #0x2
	add r1, r5, #0x2
	mov r2, #0x8
	bl FUN_020292D4
	add r4, #0x12
	add r5, #0x12
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_020292D4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02028F10
FUN_02028F10: ; 0x02028F10
	add r2, r0, #0x0
	ldrb r0, [r1, #0x0]
	ldr r3, _02028F28 ; =FUN_020292D4
	strb r0, [r2, #0x0]
	ldrb r0, [r1, #0x1]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	strb r0, [r2, #0x1]
	add r0, r1, #0x2
	add r1, r2, #0x2
	mov r2, #0x8
	bx r3
	.balign 4
_02028F28: .word FUN_020292D4

	thumb_func_start FUN_02028F2C
FUN_02028F2C: ; 0x02028F2C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrb r0, [r4, #0x0]
	mov r2, #0x8
	strb r0, [r5, #0x0]
	ldrb r0, [r4, #0x1]
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1f
	lsl r0, r0, #0x18
	lsl r1, r1, #0x2
	lsr r0, r0, #0x1e
	orr r0, r1
	strb r0, [r5, #0x1]
	add r0, r4, #0x2
	add r1, r5, #0x2
	bl FUN_020292D4
	add r4, #0x22
	add r5, #0x12
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0xc
	bl FUN_020292D4
	pop {r3-r5, pc}

	thumb_func_start FUN_02028F60
FUN_02028F60: ; 0x02028F60
	push {r4, lr}
	add r4, r1, #0x0
	mov r3, #0x0
	add r2, r0, #0x0
_02028F68:
	ldrb r1, [r2, #0x1c]
	cmp r1, #0x0
	beq _02028F76
	add r3, r3, #0x1
	add r2, #0x2a
	cmp r3, #0x2
	blo _02028F68
_02028F76:
	cmp r3, #0x0
	beq _02028F8A
	mov r1, #0x2a
	mul r1, r3
	add r1, r0, r1
	sub r1, #0xe
	ldrb r2, [r4, #0x0]
	ldrb r1, [r1, #0x0]
	cmp r2, r1
	beq _02028F92
_02028F8A:
	bl FUN_02028CA8
	ldrb r1, [r4, #0x0]
	strb r1, [r0, #0x0]
_02028F92:
	pop {r4, pc}

	thumb_func_start FUN_02028F94
FUN_02028F94: ; 0x02028F94
	ldrb r2, [r1, #0x0]
	strb r2, [r0, #0x0]
	ldrb r1, [r1, #0x1]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	strb r1, [r0, #0x1]
	bx lr
	.balign 4

	thumb_func_start FUN_02028FA4
FUN_02028FA4: ; 0x02028FA4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x4
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_020126B4
	ldr r2, [r4, #0x0]
	mov r0, #0x7f
	bic r2, r0
	ldr r1, [sp, #0x0]
	mov r0, #0x7f
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	str r1, [r4, #0x0]
	add r2, r1, #0x0
	ldr r1, [sp, #0x4]
	ldr r0, _02029008 ; =0xFFFFF87F
	lsl r1, r1, #0x1c
	and r2, r0
	lsr r1, r1, #0x15
	orr r2, r1
	ldr r1, _0202900C ; =0xFFF83FFF
	str r2, [r4, #0x0]
	and r2, r1
	ldr r1, [sp, #0x8]
	lsr r0, r0, #0xd
	lsl r1, r1, #0x1b
	lsr r1, r1, #0xd
	orr r2, r1
	ldr r1, _02029010 ; =0xFFFFC7FF
	str r2, [r4, #0x0]
	and r2, r1
	ldr r1, [sp, #0xc]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x12
	orr r1, r2
	and r1, r0
	lsl r0, r5, #0x13
	orr r0, r1
	str r0, [r4, #0x0]
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02029008: .word 0xFFFFF87F
_0202900C: .word 0xFFF83FFF
_02029010: .word 0xFFFFC7FF

	thumb_func_start FUN_02029014
FUN_02029014: ; 0x02029014
	push {r3, lr}
	mov r1, #0x8
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	pop {r3, pc}

	thumb_func_start FUN_02029030
FUN_02029030: ; 0x02029030
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x1
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202903C
FUN_0202903C: ; 0x0202903C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x2
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029048
FUN_02029048: ; 0x02029048
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x3
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029054
FUN_02029054: ; 0x02029054
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x4
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029060
FUN_02029060: ; 0x02029060
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x5
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202906C
FUN_0202906C: ; 0x0202906C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x6
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029078
FUN_02029078: ; 0x02029078
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x7
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029084
FUN_02029084: ; 0x02029084
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x8
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029090
FUN_02029090: ; 0x02029090
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0x9
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290A4
FUN_020290A4: ; 0x020290A4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_02029014
	mov r1, #0xa
	strb r1, [r0, #0x0]
	strh r5, [r0, #0x2]
	strh r4, [r0, #0x4]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020290BC
FUN_020290BC: ; 0x020290BC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xb
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290D0
FUN_020290D0: ; 0x020290D0
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xc
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290E4
FUN_020290E4: ; 0x020290E4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xd
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020290F8
FUN_020290F8: ; 0x020290F8
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xe
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202910C
FUN_0202910C: ; 0x0202910C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0xf
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02029120
FUN_02029120: ; 0x02029120
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x10
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202912C
FUN_0202912C: ; 0x0202912C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x11
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029138
FUN_02029138: ; 0x02029138
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02029014
	mov r1, #0x12
	strb r1, [r0, #0x0]
	strh r4, [r0, #0x6]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202914C
FUN_0202914C: ; 0x0202914C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r2, #0x0
	add r4, r1, #0x0
	bl FUN_02029014
	add r5, #0x13
	strb r5, [r0, #0x0]
	strh r4, [r0, #0x2]
	pop {r3-r5, pc}

	thumb_func_start FUN_02029160
FUN_02029160: ; 0x02029160
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x22
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202916C
FUN_0202916C: ; 0x0202916C
	push {r3, lr}
	bl FUN_02029014
	mov r1, #0x23
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029178
FUN_02029178: ; 0x02029178
	push {r3, lr}
	mov r1, #0x4
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	pop {r3, pc}

	thumb_func_start FUN_0202918C
FUN_0202918C: ; 0x0202918C
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02029178
	add r4, r0, #0x0
	mov r0, #0x1
	strb r0, [r4, #0x0]
	strh r5, [r4, #0x2]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x3c
	bic r1, r0
	lsl r0, r7, #0x1c
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	ldr r0, [sp, #0x0]
	bl FUN_02029EC0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	beq _020291DA
	cmp r0, #0x2
	beq _020291DA
	cmp r0, #0x4
	bne _020291E4
_020291DA:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	strb r1, [r4, #0x1]
	b _02029206
_020291E4:
	cmp r0, #0x1
	beq _020291EC
	cmp r0, #0x3
	bne _020291FA
_020291EC:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r4, #0x1]
	b _02029206
_020291FA:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0x1]
_02029206:
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202920C
FUN_0202920C: ; 0x0202920C
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02029178
	add r4, r0, #0x0
	mov r0, #0x2
	strb r0, [r4, #0x0]
	strh r5, [r4, #0x2]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x3c
	bic r1, r0
	lsl r0, r7, #0x1c
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	ldr r0, [sp, #0x0]
	bl FUN_02029EC0
	mov r1, #0xa
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	beq _0202925C
	cmp r0, #0x3
	beq _0202925C
	cmp r0, #0x5
	bne _02029266
_0202925C:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	strb r1, [r4, #0x1]
	b _02029288
_02029266:
	cmp r0, #0x2
	beq _0202926E
	cmp r0, #0x4
	bne _0202927C
_0202926E:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r4, #0x1]
	b _02029288
_0202927C:
	ldrb r1, [r4, #0x1]
	mov r0, #0x3
	bic r1, r0
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0x1]
_02029288:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0202928C
FUN_0202928C: ; 0x0202928C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x4
	bl FUN_02016998
	ldrh r2, [r0, #0x0]
	mov r1, #0x1
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r0, #0x0]
	strh r5, [r0, #0x2]
	ldrh r2, [r0, #0x0]
	ldr r1, _020292B8 ; =0xFFFF0001
	and r2, r1
	lsl r1, r4, #0x11
	lsr r1, r1, #0x10
	orr r1, r2
	strh r1, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020292B8: .word 0xFFFF0001

	thumb_func_start FUN_020292BC
FUN_020292BC: ; 0x020292BC
	push {r4, lr}
	mov r1, #0x3a
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x3a
	add r4, r0, #0x0
	bl memset
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020292D4
FUN_020292D4: ; 0x020292D4
	push {r4-r5}
	mov r4, #0x0
	cmp r2, #0x0
	bls _020292EA
	ldr r3, _02029308 ; =0x0000FFFF
	add r5, r1, #0x0
_020292E0:
	add r4, r4, #0x1
	strh r3, [r5, #0x0]
	add r5, r5, #0x2
	cmp r4, r2
	blo _020292E0
_020292EA:
	mov r5, #0x0
	cmp r2, #0x0
	bls _02029304
	ldr r3, _02029308 ; =0x0000FFFF
_020292F2:
	ldrh r4, [r0, #0x0]
	cmp r4, r3
	beq _02029304
	add r5, r5, #0x1
	strh r4, [r1, #0x0]
	add r0, r0, #0x2
	add r1, r1, #0x2
	cmp r5, r2
	blo _020292F2
_02029304:
	pop {r4-r5}
	bx lr
	.balign 4
_02029308: .word 0x0000FFFF

	thumb_func_start FUN_0202930C
FUN_0202930C: ; 0x0202930C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202934C
FUN_0202934C: ; 0x0202934C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x2
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202938C
FUN_0202938C: ; 0x0202938C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [sp, #0x1c]
	str r1, [sp, #0x0]
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x3
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	bic r0, r1
	add r1, sp, #0x8
	ldrb r2, [r1, #0x10]
	mov r1, #0xf
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x8
	bic r0, r1
	lsl r1, r5, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x20
	bic r1, r0
	lsl r0, r6, #0x1f
	lsr r0, r0, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x12
	mov r2, #0x8
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020293EC
FUN_020293EC: ; 0x020293EC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x4
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202942C
FUN_0202942C: ; 0x0202942C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r0, r2, #0x0
	add r5, r1, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x6
	strb r0, [r4, #0x0]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	mov r2, #0x8
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r6, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202945C
FUN_0202945C: ; 0x0202945C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0x7
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x8
	bic r0, r1
	lsl r1, r5, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x22
	mov r2, #0xc
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020294A8
FUN_020294A8: ; 0x020294A8
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0x8
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_020294B4
FUN_020294B4: ; 0x020294B4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0xb
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0xf
	mov r2, #0x8
	bic r0, r1
	mov r1, #0xf
	and r1, r6
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0x10
	bic r1, r0
	lsl r0, r5, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020294F4
FUN_020294F4: ; 0x020294F4
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0xc
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029500
FUN_02029500: ; 0x02029500
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	bl FUN_020292BC
	mov r1, #0xd
	strb r1, [r0, #0x0]
	ldrb r2, [r0, #0x1]
	mov r1, #0xf
	bic r2, r1
	mov r1, #0xf
	and r1, r4
	orr r1, r2
	strb r1, [r0, #0x1]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02029520
FUN_02029520: ; 0x02029520
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0xe
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202952C
FUN_0202952C: ; 0x0202952C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, [sp, #0x18]
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	add r6, r3, #0x0
	bl FUN_020292BC
	add r4, r0, #0x0
	mov r0, #0xf
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x8
	bic r0, r1
	lsl r1, r5, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r1, [r4, #0x1]
	mov r0, #0xc0
	bic r1, r0
	lsl r0, r6, #0x1e
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r7, #0x0
	add r1, r4, #0x2
	bl FUN_020292D4
	add r1, r4, #0x0
	ldr r0, [sp, #0x0]
	add r1, #0x22
	mov r2, #0xc
	bl FUN_020292D4
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02029578
FUN_02029578: ; 0x02029578
	push {r3, lr}
	bl FUN_020292BC
	mov r1, #0x10
	strb r1, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02029584
FUN_02029584: ; 0x02029584
	push {r3, lr}
	cmp r2, #0x4
	bhi _020295DA
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02029596: ; jump table (using 16-bit offset)
	.short _020295A0 - _02029596 - 2; case 0
	.short _020295AC - _02029596 - 2; case 1
	.short _020295B8 - _02029596 - 2; case 2
	.short _020295C4 - _02029596 - 2; case 3
	.short _020295D0 - _02029596 - 2; case 4
_020295A0:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_020295DC
	pop {r3, pc}
_020295AC:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_020295E4
	pop {r3, pc}
_020295B8:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_02029690
	pop {r3, pc}
_020295C4:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_0202969C
	pop {r3, pc}
_020295D0:
	mov r2, #0x70
	mul r2, r3
	add r0, r0, r2
	bl FUN_020296A8
_020295DA:
	pop {r3, pc}

	thumb_func_start FUN_020295DC
FUN_020295DC: ; 0x020295DC
	ldr r0, [r0, #0x0]
	str r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020295E4
FUN_020295E4: ; 0x020295E4
	push {r3-r7, lr}
	mov r6, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r6, #0x0
_020295EE:
	strb r7, [r4, #0x0]
	strb r7, [r4, #0x1]
	strb r7, [r4, #0x2]
	strb r7, [r4, #0x3]
	strb r7, [r4, #0x4]
	strb r7, [r4, #0x5]
	strb r7, [r4, #0x6]
	strb r7, [r4, #0x7]
	ldr r0, [r5, #0x4]
	mov r1, #0x3f
	and r1, r0
	cmp r1, #0x23
	bhi _02029682
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02029614: ; jump table (using 16-bit offset)
	.short _02029682 - _02029614 - 2; case 0
	.short _0202965C - _02029614 - 2; case 1
	.short _0202965C - _02029614 - 2; case 2
	.short _0202965C - _02029614 - 2; case 3
	.short _0202965C - _02029614 - 2; case 4
	.short _0202965C - _02029614 - 2; case 5
	.short _0202965C - _02029614 - 2; case 6
	.short _0202965C - _02029614 - 2; case 7
	.short _0202965C - _02029614 - 2; case 8
	.short _02029664 - _02029614 - 2; case 9
	.short _02029664 - _02029614 - 2; case 10
	.short _02029664 - _02029614 - 2; case 11
	.short _02029664 - _02029614 - 2; case 12
	.short _0202966C - _02029614 - 2; case 13
	.short _0202966C - _02029614 - 2; case 14
	.short _0202966C - _02029614 - 2; case 15
	.short _0202965C - _02029614 - 2; case 16
	.short _0202965C - _02029614 - 2; case 17
	.short _02029674 - _02029614 - 2; case 18
	.short _0202967C - _02029614 - 2; case 19
	.short _0202967C - _02029614 - 2; case 20
	.short _0202967C - _02029614 - 2; case 21
	.short _0202967C - _02029614 - 2; case 22
	.short _0202967C - _02029614 - 2; case 23
	.short _0202967C - _02029614 - 2; case 24
	.short _0202967C - _02029614 - 2; case 25
	.short _0202967C - _02029614 - 2; case 26
	.short _0202967C - _02029614 - 2; case 27
	.short _0202967C - _02029614 - 2; case 28
	.short _0202967C - _02029614 - 2; case 29
	.short _0202967C - _02029614 - 2; case 30
	.short _02029682 - _02029614 - 2; case 31
	.short _0202967C - _02029614 - 2; case 32
	.short _0202967C - _02029614 - 2; case 33
	.short _0202965C - _02029614 - 2; case 34
	.short _0202965C - _02029614 - 2; case 35
_0202965C:
	add r1, r4, #0x0
	bl FUN_02029730
	b _02029682
_02029664:
	add r1, r4, #0x0
	bl FUN_02029738
	b _02029682
_0202966C:
	add r1, r4, #0x0
	bl FUN_02029750
	b _02029682
_02029674:
	add r1, r4, #0x0
	bl FUN_0202975C
	b _02029682
_0202967C:
	add r1, r4, #0x0
	bl FUN_02029768
_02029682:
	add r6, r6, #0x1
	add r4, #0x8
	add r5, r5, #0x4
	cmp r6, #0x4
	blo _020295EE
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02029690
FUN_02029690: ; 0x02029690
	ldrh r2, [r0, #0x14]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x16]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_0202969C
FUN_0202969C: ; 0x0202969C
	ldrh r2, [r0, #0x18]
	strh r2, [r1, #0x0]
	ldrh r0, [r0, #0x1a]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4

	thumb_func_start FUN_020296A8
FUN_020296A8: ; 0x020296A8
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r6, #0x0
	add r4, r1, #0x0
	mov r7, #0x0
	add r5, #0x1c
_020296B4:
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x3a
	bl memset
	ldrb r0, [r6, #0x1c]
	cmp r0, #0x10
	bhi _02029722
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020296D0: ; jump table (using 16-bit offset)
	.short _02029722 - _020296D0 - 2; case 0
	.short _020296F2 - _020296D0 - 2; case 1
	.short _020296F2 - _020296D0 - 2; case 2
	.short _020296F2 - _020296D0 - 2; case 3
	.short _020296F2 - _020296D0 - 2; case 4
	.short _020296F2 - _020296D0 - 2; case 5
	.short _020296FC - _020296D0 - 2; case 6
	.short _02029706 - _020296D0 - 2; case 7
	.short _02029710 - _020296D0 - 2; case 8
	.short _02029706 - _020296D0 - 2; case 9
	.short _02029710 - _020296D0 - 2; case 10
	.short _020296F2 - _020296D0 - 2; case 11
	.short _02029710 - _020296D0 - 2; case 12
	.short _0202971A - _020296D0 - 2; case 13
	.short _02029710 - _020296D0 - 2; case 14
	.short _02029706 - _020296D0 - 2; case 15
	.short _02029710 - _020296D0 - 2; case 16
_020296F2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029774
	b _02029722
_020296FC:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020297E4
	b _02029722
_02029706:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029808
	b _02029722
_02029710:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029860
	b _02029722
_0202971A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029868
_02029722:
	add r7, r7, #0x1
	add r4, #0x3a
	add r6, #0x2a
	add r5, #0x2a
	cmp r7, #0x2
	blo _020296B4
	pop {r3-r7, pc}

	thumb_func_start FUN_02029730
FUN_02029730: ; 0x02029730
	mov r2, #0x3f
	and r0, r2
	strb r0, [r1, #0x0]
	bx lr

	thumb_func_start FUN_02029738
FUN_02029738: ; 0x02029738
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r3, r0, #0x6
	ldr r2, _0202974C ; =0x000003FF
	lsr r0, r0, #0x10
	and r2, r3
	strh r2, [r1, #0x4]
	strh r0, [r1, #0x2]
	bx lr
	.balign 4
_0202974C: .word 0x000003FF

	thumb_func_start FUN_02029750
FUN_02029750: ; 0x02029750
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	bx lr

	thumb_func_start FUN_0202975C
FUN_0202975C: ; 0x0202975C
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x6]
	bx lr

	thumb_func_start FUN_02029768
FUN_02029768: ; 0x02029768
	mov r2, #0x3f
	and r2, r0
	strb r2, [r1, #0x0]
	lsr r0, r0, #0x10
	strh r0, [r1, #0x2]
	bx lr

	thumb_func_start FUN_02029774
FUN_02029774: ; 0x02029774
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x0]
	add r4, r1, #0x0
	mov r1, #0xf
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	bic r0, r1
	ldrb r1, [r5, #0x1]
	asr r2, r1, #0x2
	mov r1, #0x1f
	and r1, r2
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0xf
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0x10
	mov r2, #0x1
	bic r0, r1
	ldrb r1, [r5, #0x1]
	asr r1, r1, #0x1
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0x20
	bic r0, r1
	ldrb r1, [r5, #0x1]
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1a
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r5, #0x2
	add r1, r4, #0x2
	mov r2, #0x8
	bl FUN_020292D4
	add r5, #0x12
	add r4, #0x12
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x8
	bl FUN_020292D4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020297E4
FUN_020297E4: ; 0x020297E4
	ldrb r2, [r0, #0x0]
	strb r2, [r1, #0x0]
	ldrb r3, [r1, #0x1]
	mov r2, #0x10
	bic r3, r2
	ldrb r2, [r0, #0x1]
	add r0, r0, #0x2
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1b
	orr r2, r3
	strb r2, [r1, #0x1]
	ldr r3, _02029804 ; =FUN_020292D4
	add r1, r1, #0x2
	mov r2, #0x8
	bx r3
	nop
_02029804: .word FUN_020292D4

	thumb_func_start FUN_02029808
FUN_02029808: ; 0x02029808
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x0]
	add r4, r1, #0x0
	mov r1, #0x10
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	bic r0, r1
	ldrb r1, [r5, #0x1]
	asr r2, r1, #0x2
	mov r1, #0x1
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1b
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x1]
	mov r1, #0xc0
	ldrb r2, [r5, #0x1]
	bic r0, r1
	mov r1, #0x3
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r4, #0x1]
	add r0, r5, #0x2
	add r1, r4, #0x2
	mov r2, #0x8
	bl FUN_020292D4
	add r5, #0x12
	add r4, #0x22
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0xc
	bl FUN_020292D4
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029860
FUN_02029860: ; 0x02029860
	ldrb r0, [r0, #0x0]
	strb r0, [r1, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029868
FUN_02029868: ; 0x02029868
	ldrb r2, [r0, #0x0]
	strb r2, [r1, #0x0]
	ldrb r3, [r1, #0x1]
	mov r2, #0xf
	bic r3, r2
	ldrb r2, [r0, #0x1]
	mov r0, #0xf
	and r0, r2
	orr r0, r3
	strb r0, [r1, #0x1]
	bx lr
	.balign 4

	thumb_func_start FUN_02029880
FUN_02029880: ; 0x02029880
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	mov r0, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	str r1, [sp, #0x0]
	add r5, r2, #0x0
	ldr r6, [sp, #0x20]
	bl FUN_02034930
	cmp r0, #0x1
	bne _020298BA
	add r0, r5, #0x0
	bl FUN_02034964
	cmp r0, #0x1
	bne _02029942
	add r0, r4, #0x0
	bl FUN_02034824
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r1, r6, #0x0
	bl FUN_020290F8
	str r0, [sp, #0x4]
	b _02029942
_020298BA:
	add r0, r4, #0x0
	bl FUN_02034944
	cmp r0, #0x1
	bne _0202991A
	add r0, r5, #0x0
	bl FUN_02034964
	cmp r0, #0x1
	bne _02029942
	ldr r0, _02029958 ; =0x0000019E
	cmp r4, r0
	bne _020298DE
	add r0, r6, #0x0
	bl FUN_02029030
	str r0, [sp, #0x4]
	b _02029942
_020298DE:
	add r0, #0x8
	cmp r4, r0
	bne _020298EE
	add r0, r6, #0x0
	bl FUN_0202903C
	str r0, [sp, #0x4]
	b _02029942
_020298EE:
	add r0, r4, #0x0
	bl FUN_02034824
	add r7, r0, #0x0
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	ldr r5, _0202995C ; =0x020EE9A4
	mov r4, #0x0
	str r0, [sp, #0x8]
_02029900:
	ldr r0, [r5, #0x0]
	cmp r7, r0
	bne _02029910
	ldr r0, [sp, #0x8]
	add r1, r6, #0x0
	bl FUN_0202910C
	str r0, [sp, #0x4]
_02029910:
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x1b
	blo _02029900
	b _02029942
_0202991A:
	add r0, r4, #0x0
	bl FUN_02034964
	cmp r0, #0x1
	bne _02029942
	add r0, r5, #0x0
	bl FUN_02034944
	cmp r0, #0x1
	bne _02029942
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02029988
	cmp r0, #0xff
	beq _02029942
	add r1, r6, #0x0
	bl FUN_02029090
	str r0, [sp, #0x4]
_02029942:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02029952
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	mov r2, #0x1
	bl FUN_02028AD4
_02029952:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02029958: .word 0x0000019E
_0202995C: .word 0x020EE9A4

	thumb_func_start FUN_02029960
FUN_02029960: ; 0x02029960
	ldr r3, _02029980 ; =0x020EE9A4
	mov r2, #0x0
_02029964:
	ldr r1, [r3, #0x0]
	cmp r0, r1
	bne _02029972
	ldr r0, _02029984 ; =0x020EE9A8
	lsl r1, r2, #0x3
	ldr r0, [r0, r1]
	bx lr
_02029972:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x1b
	blo _02029964
	mov r0, #0x0
	bx lr
	nop
_02029980: .word 0x020EE9A4
_02029984: .word 0x020EE9A8

	thumb_func_start FUN_02029988
FUN_02029988: ; 0x02029988
	push {r3-r5, lr}
	ldr r2, _020299B8 ; =0x020EE964
	mov r4, #0x0
_0202998E:
	lsl r3, r4, #0x3
	add r5, r2, r3
	ldrh r5, [r5, #0x4]
	cmp r1, r5
	bne _020299A8
	ldr r1, _020299BC ; =0x020EE96A
	ldrh r1, [r1, r3]
	bl FUN_020239D0
	cmp r0, #0x0
	bne _020299B2
	add r0, r4, #0x0
	pop {r3-r5, pc}
_020299A8:
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	lsr r4, r3, #0x18
	cmp r4, #0x8
	blo _0202998E
_020299B2:
	mov r0, #0xff
	pop {r3-r5, pc}
	nop
_020299B8: .word 0x020EE964
_020299BC: .word 0x020EE96A

	thumb_func_start FUN_020299C0
FUN_020299C0: ; 0x020299C0
	push {r4, lr}
	add r4, r0, #0x0
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	add r1, r2, #0x0
	bl FUN_020290E4
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020299DC
FUN_020299DC: ; 0x020299DC
	push {r3-r7, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r7, r1, #0x0
	add r6, r3, #0x0
	bl FUN_02029A48
	cmp r0, #0x8
	bhs _02029A04
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020290A4
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r3-r7, pc}
_02029A04:
	bne _02029A1A
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020290BC
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r3-r7, pc}
_02029A1A:
	cmp r0, #0x9
	bne _02029A32
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_020290D0
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02028AD4
	pop {r3-r7, pc}
_02029A32:
	add r0, r7, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0202928C
	add r1, r0, #0x0
	add r0, r5, #0x0
	mov r2, #0x3
	bl FUN_02028AD4
	pop {r3-r7, pc}

	thumb_func_start FUN_02029A48
FUN_02029A48: ; 0x02029A48
	ldr r2, _02029A7C ; =0x020EE964
	mov r3, #0x0
_02029A4C:
	lsl r1, r3, #0x3
	ldr r1, [r2, r1]
	cmp r0, r1
	bne _02029A58
	add r0, r3, #0x0
	bx lr
_02029A58:
	add r1, r3, #0x1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #0x8
	blo _02029A4C
	ldr r1, _02029A80 ; =0x00000105
	sub r2, r0, r1
	cmp r2, #0x3
	bhi _02029A6E
	mov r0, #0x8
	bx lr
_02029A6E:
	add r1, r1, #0x6
	cmp r0, r1
	bne _02029A78
	mov r0, #0x9
	bx lr
_02029A78:
	mov r0, #0xa
	bx lr
	.balign 4
_02029A7C: .word 0x020EE964
_02029A80: .word 0x00000105

	thumb_func_start FUN_02029A84
FUN_02029A84: ; 0x02029A84
	mov r0, #0x62
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02029A8C
FUN_02029A8C: ; 0x02029A8C
	push {r4-r6, lr}
	mov r2, #0x62
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl memset
	add r0, r4, #0x0
	bl FUN_02029ACC
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0x8c
_02029AA6:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02029AD8
	add r4, r4, #0x1
	cmp r4, #0x8
	blt _02029AA6
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029ABC
FUN_02029ABC: ; 0x02029ABC
	ldr r3, _02029AC4 ; =FUN_02022610
	mov r1, #0x13
	bx r3
	nop
_02029AC4: .word FUN_02022610

	thumb_func_start FUN_02029AC8
FUN_02029AC8: ; 0x02029AC8
	add r0, #0x20
	bx lr

	thumb_func_start FUN_02029ACC
FUN_02029ACC: ; 0x02029ACC
	bx lr
	.balign 4

	thumb_func_start FUN_02029AD0
FUN_02029AD0: ; 0x02029AD0
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029AD8
FUN_02029AD8: ; 0x02029AD8
	lsl r0, r0, #0x2
	str r1, [r2, r0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029AE0
FUN_02029AE0: ; 0x02029AE0
	ldr r0, _02029AE4 ; =0x00000FF8
	bx lr
	.balign 4
_02029AE4: .word 0x00000FF8

	thumb_func_start FUN_02029AE8
FUN_02029AE8: ; 0x02029AE8
	ldr r3, _02029AF4 ; =MIi_CpuClear32
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _02029AF8 ; =0x00000FF8
	bx r3
	nop
_02029AF4: .word MIi_CpuClear32
_02029AF8: .word 0x00000FF8

	thumb_func_start FUN_02029AFC
FUN_02029AFC: ; 0x02029AFC
	ldr r3, _02029B04 ; =FUN_02022610
	mov r1, #0x1e
	bx r3
	nop
_02029B04: .word FUN_02022610

	thumb_func_start FUN_02029B08
FUN_02029B08: ; 0x02029B08
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x1
	add r5, r1, #0x0
	lsl r0, r0, #0x8
	add r4, r2, #0x0
	cmp r5, r0
	blt _02029B1C
	bl ErrorHandling
_02029B1C:
	cmp r4, #0x40
	blt _02029B24
	bl ErrorHandling
_02029B24:
	strb r5, [r6, #0x5]
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x3
	strb r4, [r6, #0x6]
	bl FUN_02029B90
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029B38
FUN_02029B38: ; 0x02029B38
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_02029B3C
FUN_02029B3C: ; 0x02029B3C
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_02029B40
FUN_02029B40: ; 0x02029B40
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r0, #0x1
	add r5, r1, #0x0
	lsl r0, r0, #0x8
	add r4, r2, #0x0
	cmp r5, r0
	blt _02029B54
	bl ErrorHandling
_02029B54:
	cmp r4, #0x40
	blt _02029B5C
	bl ErrorHandling
_02029B5C:
	cmp r5, #0x0
	bne _02029B64
	mov r0, #0x0
	pop {r4-r6, pc}
_02029B64:
	asr r0, r4, #0x1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	asr r1, r0, #0x2
	sub r0, r5, #0x1
	lsl r0, r0, #0x4
	add r0, r1, r0
	add r0, r6, r0
	ldrb r3, [r0, #0x7]
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x1
	add r1, r3, #0x0
	asr r1, r0
	mov r0, #0x3
	and r0, r1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029B90
FUN_02029B90: ; 0x02029B90
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	str r3, [sp, #0x0]
	cmp r3, #0x4
	blt _02029BA2
	bl ErrorHandling
_02029BA2:
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r5, r0
	blt _02029BAE
	bl ErrorHandling
_02029BAE:
	cmp r4, #0x40
	blt _02029BB6
	bl ErrorHandling
_02029BB6:
	cmp r5, #0x0
	beq _02029BFE
	asr r0, r4, #0x1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	asr r2, r0, #0x2
	sub r0, r5, #0x1
	lsl r0, r0, #0x4
	add r0, r2, r0
	lsr r2, r4, #0x1f
	lsl r4, r4, #0x1e
	sub r4, r4, r2
	mov r3, #0x1e
	ror r4, r3
	add r2, r2, r4
	lsl r6, r2, #0x1
	mov r2, #0x3
	add r3, r2, #0x0
	add r1, r7, #0x7
	ldrb r4, [r1, r0]
	lsl r3, r6
	mov r2, #0xff
	eor r2, r3
	and r2, r4
	ldr r3, [sp, #0x0]
	strb r2, [r1, r0]
	ldrb r2, [r1, r0]
	lsl r3, r6
	orr r2, r3
	strb r2, [r1, r0]
	cmp r5, #0x67
	beq _02029BFE
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_02029C04
_02029BFE:
	pop {r3-r7, pc}

	thumb_func_start FUN_02029C00
FUN_02029C00: ; 0x02029C00
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02029C04
FUN_02029C04: ; 0x02029C04
	strb r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02029C08
FUN_02029C08: ; 0x02029C08
	push {r3-r7, lr}
	mov lr, r0
	mov r0, #0x3
	mov r7, #0x0
	mov r4, #0x2
	mov r6, #0xff
	add r3, r0, #0x0
_02029C16:
	mov r1, lr
	add r1, r1, r7
	ldrb r2, [r1, #0x7]
	mov r12, r1
	mov r1, #0x0
_02029C20:
	add r5, r2, #0x0
	asr r5, r1
	and r5, r3
	cmp r5, #0x1
	bne _02029C40
	add r5, r0, #0x0
	lsl r5, r1
	eor r5, r6
	and r2, r5
	lsl r2, r2, #0x18
	lsr r5, r2, #0x18
	add r2, r4, #0x0
	lsl r2, r1
	orr r2, r5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
_02029C40:
	add r1, r1, #0x2
	cmp r1, #0x8
	blt _02029C20
	mov r1, r12
	strb r2, [r1, #0x7]
	mov r1, #0xff
	add r7, r7, #0x1
	lsl r1, r1, #0x4
	cmp r7, r1
	blt _02029C16
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02029C58
FUN_02029C58: ; 0x02029C58
	mov r0, #0x17
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_02029C60
FUN_02029C60: ; 0x02029C60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02029C58
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl MI_CpuFill8
	pop {r4, pc}

	thumb_func_start FUN_02029C74
FUN_02029C74: ; 0x02029C74
	ldr r3, _02029C7C ; =MI_CpuCopy8
	mov r2, #0x18
	bx r3
	nop
_02029C7C: .word MI_CpuCopy8

	thumb_func_start FUN_02029C80
FUN_02029C80: ; 0x02029C80
	ldr r3, _02029C88 ; =FUN_02022610
	mov r1, #0x15
	bx r3
	nop
_02029C88: .word FUN_02022610

	thumb_func_start FUN_02029C8C
FUN_02029C8C: ; 0x02029C8C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0xc
	blt _02029C9A
	bl ErrorHandling
_02029C9A:
	mov r0, #0x18
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029CA4
FUN_02029CA4: ; 0x02029CA4
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r6, #0xc
	blt _02029CB4
	bl ErrorHandling
_02029CB4:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029C8C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02029C74
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029CC8
FUN_02029CC8: ; 0x02029CC8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x8
	blt _02029CD6
	bl ErrorHandling
_02029CD6:
	lsl r0, r4, #0x1
	add r0, r4, r0
	add r0, r5, r0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029CE0
FUN_02029CE0: ; 0x02029CE0
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02029CE4
FUN_02029CE4: ; 0x02029CE4
	ldrb r0, [r0, #0x1]
	bx lr

	thumb_func_start FUN_02029CE8
FUN_02029CE8: ; 0x02029CE8
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02029CEC
FUN_02029CEC: ; 0x02029CEC
	mov r1, #0x12
	lsl r1, r1, #0x4
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_02029CF4
FUN_02029CF4: ; 0x02029CF4
	ldrb r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02029CF8
FUN_02029CF8: ; 0x02029CF8
	mov r3, #0x0
	add r2, r1, #0x1
_02029CFC:
	ldrb r1, [r0, #0x0]
	cmp r2, r1
	bne _02029D06
	mov r0, #0x1
	bx lr
_02029D06:
	add r3, r3, #0x1
	add r0, r0, #0x3
	cmp r3, #0x8
	blt _02029CFC
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02029D14
FUN_02029D14: ; 0x02029D14
	push {r4-r7}
	mov r6, #0x0
	add r4, r6, #0x0
	add r2, r1, #0x1
	add r3, r6, #0x0
_02029D1E:
	add r5, r3, #0x0
	add r7, r0, #0x0
_02029D22:
	ldrb r1, [r7, #0x0]
	cmp r2, r1
	bne _02029D2A
	add r6, r6, #0x1
_02029D2A:
	add r5, r5, #0x1
	add r7, r7, #0x3
	cmp r5, #0x8
	blt _02029D22
	add r4, r4, #0x1
	add r0, #0x18
	cmp r4, #0xc
	blt _02029D1E
	add r0, r6, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02029D40
FUN_02029D40: ; 0x02029D40
	strb r2, [r0, r1]
	bx lr

	thumb_func_start FUN_02029D44
FUN_02029D44: ; 0x02029D44
	push {r4-r6, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02029D14
	mov r1, #0x12
	lsl r1, r1, #0x4
	add r2, r6, r1
	sub r1, r5, #0x1
	ldrb r3, [r2, r1]
	add r0, r0, r3
	cmp r4, #0x0
	bge _02029D6E
	add r0, r4, r3
	bmi _02029D6A
	strb r0, [r2, r1]
	b _02029D7E
_02029D6A:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029D6E:
	add r0, r0, r4
	cmp r0, #0x63
	bgt _02029D7A
	add r0, r3, r4
	strb r0, [r2, r1]
	b _02029D7E
_02029D7A:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029D7E:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02029D84
FUN_02029D84: ; 0x02029D84
	push {r4-r6, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02029D14
	cmp r4, #0x0
	bge _02029DAC
	mov r0, #0x12
	lsl r0, r0, #0x4
	add r2, r6, r0
	sub r1, r5, #0x1
	ldrb r0, [r2, r1]
	add r0, r4, r0
	bmi _02029DA8
	strb r0, [r2, r1]
	b _02029DD0
_02029DA8:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029DAC:
	add r0, r0, r4
	cmp r0, #0x63
	bgt _02029DCC
	mov r0, #0x12
	lsl r0, r0, #0x4
	add r2, r6, r0
	sub r1, r5, #0x1
	ldrb r0, [r2, r1]
	add r0, r0, r4
	strb r0, [r2, r1]
	ldrb r0, [r2, r1]
	cmp r0, #0x63
	blo _02029DD0
	mov r0, #0x63
	strb r0, [r2, r1]
	b _02029DD0
_02029DCC:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029DD0:
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_02029DD4
FUN_02029DD4: ; 0x02029DD4
	push {r4-r6, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r6, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02029D14
	sub r1, r5, #0x1
	add r2, r6, r1
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	add r0, r0, r1
	cmp r4, #0x0
	bge _02029DFE
	add r0, r4, r1
	bmi _02029DFA
	mov r0, #0x1
	pop {r4-r6, pc}
_02029DFA:
	mov r0, #0x0
	pop {r4-r6, pc}
_02029DFE:
	add r0, r0, r4
	cmp r0, #0x63
	bgt _02029E08
	mov r0, #0x1
	pop {r4-r6, pc}
_02029E08:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02029E0C
FUN_02029E0C: ; 0x02029E0C
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r5, #0x0
	mov r4, #0x1
_02029E14:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02029E2C
	cmp r0, #0x0
	beq _02029E22
	add r5, r5, #0x1
_02029E22:
	add r4, r4, #0x1
	cmp r4, #0x51
	blt _02029E14
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02029E2C
FUN_02029E2C: ; 0x02029E2C
	push {r3-r5, lr}
	add r5, r1, #0x0
	sub r1, r5, #0x1
	add r4, r0, #0x0
	bl FUN_02029D14
	sub r1, r5, #0x1
	add r2, r4, r1
	mov r1, #0x12
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	add r0, r0, r1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02029E48
FUN_02029E48: ; 0x02029E48
	mov r1, #0x0
	strh r1, [r0, #0x0]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_02029E54
FUN_02029E54: ; 0x02029E54
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrh r6, [r5, #0x0]
	ldr r0, _02029EB8 ; =0x000003E7
	cmp r6, r0
	bne _02029E6C
	ldrb r0, [r5, #0x2]
	cmp r0, #0x3b
	bne _02029E6C
	ldrb r0, [r5, #0x3]
	cmp r0, #0x3b
	beq _02029EB4
_02029E6C:
	ldrb r0, [r5, #0x3]
	ldrb r4, [r5, #0x2]
	add r7, r0, r1
	cmp r7, #0x3b
	bls _02029EAE
	add r0, r7, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	add r4, r4, r0
	add r0, r7, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	add r7, r1, #0x0
	cmp r4, #0x3b
	bls _02029EAE
	add r0, r4, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	add r6, r6, r0
	add r0, r4, #0x0
	mov r1, #0x3c
	bl _u32_div_f
	ldr r0, _02029EB8 ; =0x000003E7
	add r4, r1, #0x0
	cmp r6, r0
	blo _02029EAE
	mov r4, #0x3b
	add r6, r0, #0x0
	add r7, r4, #0x0
_02029EAE:
	strh r6, [r5, #0x0]
	strb r4, [r5, #0x2]
	strb r7, [r5, #0x3]
_02029EB4:
	pop {r3-r7, pc}
	nop
_02029EB8: .word 0x000003E7

	thumb_func_start FUN_02029EBC
FUN_02029EBC: ; 0x02029EBC
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02029EC0
FUN_02029EC0: ; 0x02029EC0
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02029EC4
FUN_02029EC4: ; 0x02029EC4
	mov r0, #0xfb
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02029ECC
FUN_02029ECC: ; 0x02029ECC
	push {r4, lr}
	add r4, r0, #0x0
	mov r2, #0xfb
	mov r0, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl MIi_CpuClear32
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02029EE4
FUN_02029EE4: ; 0x02029EE4
	push {r4, lr}
	mov r1, #0xfb
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	bl FUN_02029ECC
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02029EF8
FUN_02029EF8: ; 0x02029EF8
	ldr r3, _02029F00 ; =FUN_02022610
	mov r1, #0x16
	bx r3
	nop
_02029F00: .word FUN_02022610

	thumb_func_start FUN_02029F04
FUN_02029F04: ; 0x02029F04
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02029F08
FUN_02029F08: ; 0x02029F08
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02029F10
FUN_02029F10: ; 0x02029F10
	add r0, r0, #0x4
	bx lr

	thumb_func_start FUN_02029F14
FUN_02029F14: ; 0x02029F14
	push {r4-r7}
	mov r5, #0x0
	mov r2, #0xfa
	add r4, r5, #0x0
	mov r6, #0xf
	lsl r2, r2, #0x2
_02029F20:
	ldrsb r7, [r1, r4]
	add r3, r0, r5
	and r7, r6
	lsl r7, r7, #0x18
	lsr r7, r7, #0x18
	sub r7, #0x8
	lsl r7, r7, #0x18
	asr r7, r7, #0x14
	strb r7, [r0, r5]
	ldrsb r7, [r1, r4]
	add r4, r4, #0x1
	add r5, r5, #0x2
	lsl r7, r7, #0x14
	lsr r7, r7, #0x18
	sub r7, #0x8
	lsl r7, r7, #0x18
	asr r7, r7, #0x14
	strb r7, [r3, #0x1]
	cmp r4, r2
	blt _02029F20
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02029F4C
FUN_02029F4C: ; 0x02029F4C
	push {r4-r7}
	add r3, r0, #0x0
	add r2, r1, #0x0
	mov r0, #0x1
	mov r1, #0x0
	str r0, [r3, #0x0]
	add r0, r1, #0x0
_02029F5A:
	ldrsb r4, [r2, r0]
	add r6, r3, r1
	add r7, r2, r0
	asr r5, r4, #0x3
	lsr r5, r5, #0x1c
	add r5, r4, r5
	lsl r4, r5, #0x14
	asr r4, r4, #0x18
	add r4, #0x8
	strb r4, [r6, #0x4]
	mov r4, #0x4
	ldrsb r5, [r6, r4]
	mov r4, #0x1
	ldrsb r4, [r7, r4]
	add r0, r0, #0x2
	add r1, r1, #0x1
	asr r7, r4, #0x3
	lsr r7, r7, #0x1c
	add r7, r4, r7
	lsl r4, r7, #0x14
	asr r4, r4, #0x18
	add r4, #0x8
	lsl r4, r4, #0x18
	lsr r4, r4, #0x14
	orr r4, r5
	strb r4, [r6, #0x4]
	mov r4, #0x7d
	lsl r4, r4, #0x4
	cmp r0, r4
	blt _02029F5A
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02029F9C
FUN_02029F9C: ; 0x02029F9C
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0xfb
	ldr r3, _02029FAC ; =MIi_CpuCopyFast
	lsl r2, r2, #0x2
	bx r3
	nop
_02029FAC: .word MIi_CpuCopyFast

	thumb_func_start FUN_02029FB0
FUN_02029FB0: ; 0x02029FB0
	mov r0, #0x53
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_02029FB8
FUN_02029FB8: ; 0x02029FB8
	ldr r3, _02029FC4 ; =MIi_CpuClear32
	mov r2, #0x53
	add r1, r0, #0x0
	mov r0, #0x0
	lsl r2, r2, #0x2
	bx r3
	.balign 4
_02029FC4: .word MIi_CpuClear32

	thumb_func_start FUN_02029FC8
FUN_02029FC8: ; 0x02029FC8
	ldr r3, _02029FD0 ; =FUN_02022610
	mov r1, #0x14
	bx r3
	nop
_02029FD0: .word FUN_02022610

	thumb_func_start FUN_02029FD4
FUN_02029FD4: ; 0x02029FD4
	push {r3, lr}
	cmp r1, #0x2c
	bge _02029FE0
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
_02029FE0:
	cmp r1, #0x79
	bge _02029FF0
	sub r1, #0x2c
	lsl r1, r1, #0x1
	add r0, r0, r1
	add r0, #0xb0
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
_02029FF0:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02029FF8
FUN_02029FF8: ; 0x02029FF8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x2c
	bge _0202A008
	lsl r0, r4, #0x2
	str r2, [r5, r0]
	b _0202A01E
_0202A008:
	cmp r4, #0x79
	bge _0202A01A
	add r0, r4, #0x0
	sub r0, #0x2c
	lsl r0, r0, #0x1
	add r0, r5, r0
	add r0, #0xb0
	strh r2, [r0, #0x0]
	b _0202A01E
_0202A01A:
	bl ErrorHandling
_0202A01E:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FD4
	pop {r3-r5, pc}

	thumb_func_start FUN_0202A028
FUN_0202A028: ; 0x0202A028
	push {r3, lr}
	cmp r0, #0x2c
	bge _0202A03E
	ldr r1, _0202A05C ; =0x02105CD8
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202A03A
	ldr r0, _0202A060 ; =0x3B9AC9FF
	pop {r3, pc}
_0202A03A:
	ldr r0, _0202A064 ; =0x000F423F
	pop {r3, pc}
_0202A03E:
	cmp r0, #0x79
	bge _0202A052
	ldr r1, _0202A05C ; =0x02105CD8
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202A04E
	ldr r0, _0202A068 ; =0x0000FFFF
	pop {r3, pc}
_0202A04E:
	ldr r0, _0202A06C ; =0x0000270F
	pop {r3, pc}
_0202A052:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	nop
_0202A05C: .word 0x02105CD8
_0202A060: .word 0x3B9AC9FF
_0202A064: .word 0x000F423F
_0202A068: .word 0x0000FFFF
_0202A06C: .word 0x0000270F

	thumb_func_start FUN_0202A070
FUN_0202A070: ; 0x0202A070
	lsl r1, r0, #0x1
	ldr r0, _0202A078 ; =0x020EEA7C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_0202A078: .word 0x020EEA7C

	thumb_func_start FUN_0202A07C
FUN_0202A07C: ; 0x0202A07C
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r4, r2, #0x0
	bl FUN_0202A028
	add r2, r0, #0x0
	cmp r4, r2
	bhs _0202A09C
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
_0202A09C:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202A0A8
FUN_0202A0A8: ; 0x0202A0A8
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r5, r2, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	cmp r5, r4
	bls _0202A0C6
	add r5, r4, #0x0
_0202A0C6:
	cmp r0, r5
	bhs _0202A0D6
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}
_0202A0D6:
	cmp r0, r4
	bls _0202A0E4
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
_0202A0E4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202A0E8
FUN_0202A0E8: ; 0x0202A0E8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	add r2, r0, #0x1
	cmp r2, r4
	bhs _0202A10E
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
_0202A10E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202A11C
FUN_0202A11C: ; 0x0202A11C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r7, r2, #0x0
	bl FUN_0202A028
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FD4
	add r2, r0, r7
	cmp r2, r6
	bhs _0202A144
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}
_0202A144:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}

	thumb_func_start FUN_0202A150
FUN_0202A150: ; 0x0202A150
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	cmp r0, r4
	bhi _0202A16C
	add r4, r0, #0x0
_0202A16C:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0202A170
FUN_0202A170: ; 0x0202A170
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x26
	blt _0202A17E
	bl ErrorHandling
_0202A17E:
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A150
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A070
	ldr r2, _0202A1B4 ; =0x05F5E0FF
	add r0, r6, r0
	cmp r0, r2
	bls _0202A1A0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A07C
	pop {r4-r6, pc}
_0202A1A0:
	add r0, r4, #0x0
	bl FUN_0202A070
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A11C
	pop {r4-r6, pc}
	nop
_0202A1B4: .word 0x05F5E0FF

	thumb_func_start FUN_0202A1B8
FUN_0202A1B8: ; 0x0202A1B8
	ldr r3, _0202A1C0 ; =FUN_0202A150
	mov r1, #0x0
	bx r3
	nop
_0202A1C0: .word FUN_0202A150

	thumb_func_start FUN_0202A1C4
FUN_0202A1C4: ; 0x0202A1C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_02024594
	cmp r0, #0x0
	bne _0202A1DC
	add r0, r4, #0x0
	mov r1, #0x16
	bl FUN_0202A170
_0202A1DC:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A1E0
FUN_0202A1E0: ; 0x0202A1E0
	mov r0, #0xe4
	bx lr

	thumb_func_start FUN_0202A1E4
FUN_0202A1E4: ; 0x0202A1E4
	ldr r3, _0202A1EC ; =MI_CpuFill8
	mov r1, #0x0
	mov r2, #0x3c
	bx r3
	.balign 4
_0202A1EC: .word MI_CpuFill8

	thumb_func_start FUN_0202A1F0
FUN_0202A1F0: ; 0x0202A1F0
	push {r4, lr}
	mov r2, #0x5a
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x1
	strb r0, [r4, #0x3]
	pop {r4, pc}

	thumb_func_start FUN_0202A204
FUN_0202A204: ; 0x0202A204
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_02013764
	add r0, r4, #0x0
	add r0, #0x8
	mov r1, #0x1
	bl FUN_02013764
	add r0, r4, #0x0
	add r0, #0x10
	mov r1, #0x2
	bl FUN_02013764
	add r4, #0x18
	add r0, r4, #0x0
	mov r1, #0x3
	bl FUN_02013764
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A230
FUN_0202A230: ; 0x0202A230
	ldr r3, _0202A238 ; =MI_CpuFill8
	mov r1, #0x0
	ldr r2, _0202A23C ; =0x00000B3C
	bx r3
	.balign 4
_0202A238: .word MI_CpuFill8
_0202A23C: .word 0x00000B3C

	thumb_func_start FUN_0202A240
FUN_0202A240: ; 0x0202A240
	push {r3, lr}
	cmp r1, #0xa
	bhi _0202A2BE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202A252: ; jump table (using 16-bit offset)
	.short _0202A268 - _0202A252 - 2; case 0
	.short _0202A270 - _0202A252 - 2; case 1
	.short _0202A274 - _0202A252 - 2; case 2
	.short _0202A278 - _0202A252 - 2; case 3
	.short _0202A27C - _0202A252 - 2; case 4
	.short _0202A280 - _0202A252 - 2; case 5
	.short _0202A28E - _0202A252 - 2; case 6
	.short _0202A29C - _0202A252 - 2; case 7
	.short _0202A2A4 - _0202A252 - 2; case 8
	.short _0202A2B2 - _0202A252 - 2; case 9
	.short _0202A2BA - _0202A252 - 2; case 10
_0202A268:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1d
	pop {r3, pc}
_0202A270:
	ldrb r0, [r0, #0x2]
	pop {r3, pc}
_0202A274:
	ldrb r0, [r0, #0x3]
	pop {r3, pc}
_0202A278:
	ldrh r0, [r0, #0x4]
	pop {r3, pc}
_0202A27C:
	ldrh r0, [r0, #0x6]
	pop {r3, pc}
_0202A280:
	add r1, r2, #0x0
	add r0, #0x8
	mov r2, #0x4
	bl MI_CpuCopy8
	mov r0, #0x0
	pop {r3, pc}
_0202A28E:
	add r1, r2, #0x0
	add r0, #0x2c
	mov r2, #0x10
	bl MI_CpuCopy8
	mov r0, #0x0
	pop {r3, pc}
_0202A29C:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	pop {r3, pc}
_0202A2A4:
	add r1, r2, #0x0
	add r0, #0xc
	mov r2, #0x1c
	bl MI_CpuCopy8
	mov r0, #0x0
	pop {r3, pc}
_0202A2B2:
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	pop {r3, pc}
_0202A2BA:
	ldr r0, [r0, #0x28]
	pop {r3, pc}
_0202A2BE:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202A2C4
FUN_0202A2C4: ; 0x0202A2C4
	push {r4, lr}
	add r3, r0, #0x0
	cmp r1, #0xa
	bhi _0202A36A
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202A2D8: ; jump table (using 16-bit offset)
	.short _0202A2EE - _0202A2D8 - 2; case 0
	.short _0202A300 - _0202A2D8 - 2; case 1
	.short _0202A306 - _0202A2D8 - 2; case 2
	.short _0202A30C - _0202A2D8 - 2; case 3
	.short _0202A312 - _0202A2D8 - 2; case 4
	.short _0202A318 - _0202A2D8 - 2; case 5
	.short _0202A326 - _0202A2D8 - 2; case 6
	.short _0202A334 - _0202A2D8 - 2; case 7
	.short _0202A346 - _0202A2D8 - 2; case 8
	.short _0202A35A - _0202A2D8 - 2; case 9
	.short _0202A354 - _0202A2D8 - 2; case 10
_0202A2EE:
	ldrb r1, [r3, #0x0]
	mov r0, #0x1c
	bic r1, r0
	ldrb r0, [r2, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1b
	orr r0, r1
	strb r0, [r3, #0x0]
	pop {r4, pc}
_0202A300:
	ldrb r0, [r2, #0x0]
	strb r0, [r3, #0x2]
	pop {r4, pc}
_0202A306:
	ldrb r0, [r2, #0x0]
	strb r0, [r3, #0x3]
	pop {r4, pc}
_0202A30C:
	ldrh r0, [r2, #0x0]
	strh r0, [r3, #0x4]
	pop {r4, pc}
_0202A312:
	ldrh r0, [r2, #0x0]
	strh r0, [r3, #0x6]
	pop {r4, pc}
_0202A318:
	add r3, #0x8
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x4
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A326:
	add r3, #0x2c
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x10
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A334:
	ldrb r4, [r3, #0x0]
	ldrb r1, [r2, #0x0]
	mov r0, #0x1
	bic r4, r0
	mov r0, #0x1
	and r0, r1
	orr r0, r4
	strb r0, [r3, #0x0]
	pop {r4, pc}
_0202A346:
	add r3, #0xc
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x1c
	bl MI_CpuCopy8
	pop {r4, pc}
_0202A354:
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x28]
	pop {r4, pc}
_0202A35A:
	ldrb r1, [r3, #0x0]
	mov r0, #0xe0
	bic r1, r0
	ldrb r0, [r2, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x18
	orr r0, r1
	strb r0, [r3, #0x0]
_0202A36A:
	pop {r4, pc}

	thumb_func_start FUN_0202A36C
FUN_0202A36C: ; 0x0202A36C
	push {r3-r4}
	ldrb r4, [r0, #0x3]
	add r1, r4, r1
	cmp r1, #0xff
	bge _0202A378
	strb r1, [r0, #0x3]
_0202A378:
	ldrh r1, [r0, #0x4]
	add r2, r1, r2
	ldr r1, _0202A394 ; =0x0000FFFF
	cmp r2, r1
	bge _0202A384
	strh r2, [r0, #0x4]
_0202A384:
	ldrh r1, [r0, #0x6]
	add r2, r1, r3
	ldr r1, _0202A394 ; =0x0000FFFF
	cmp r2, r1
	bge _0202A390
	strh r2, [r0, #0x6]
_0202A390:
	pop {r3-r4}
	bx lr
	.balign 4
_0202A394: .word 0x0000FFFF

	thumb_func_start FUN_0202A398
FUN_0202A398: ; 0x0202A398
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_0202A3A0
FUN_0202A3A0: ; 0x0202A3A0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1f
	ldrb r3, [r0, #0x0]
	mov r2, #0x2
	lsr r1, r1, #0x1e
	bic r3, r2
	orr r1, r3
	strb r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202A3B4
FUN_0202A3B4: ; 0x0202A3B4
	cmp r2, #0x6
	bhi _0202A402
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0202A3C4: ; jump table (using 16-bit offset)
	.short _0202A402 - _0202A3C4 - 2; case 0
	.short _0202A3D2 - _0202A3C4 - 2; case 1
	.short _0202A402 - _0202A3C4 - 2; case 2
	.short _0202A402 - _0202A3C4 - 2; case 3
	.short _0202A402 - _0202A3C4 - 2; case 4
	.short _0202A3E0 - _0202A3C4 - 2; case 5
	.short _0202A3F2 - _0202A3C4 - 2; case 6
_0202A3D2:
	ldr r2, _0202A408 ; =0x0000270F
	cmp r1, r2
	bls _0202A3DC
	strh r2, [r0, #0x0]
	b _0202A402
_0202A3DC:
	strh r1, [r0, #0x0]
	b _0202A402
_0202A3E0:
	ldrh r2, [r0, #0x0]
	add r2, r2, r1
	ldr r1, _0202A408 ; =0x0000270F
	cmp r2, r1
	ble _0202A3EE
	strh r1, [r0, #0x0]
	b _0202A402
_0202A3EE:
	strh r2, [r0, #0x0]
	b _0202A402
_0202A3F2:
	ldrh r2, [r0, #0x0]
	cmp r2, r1
	bhs _0202A3FE
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _0202A402
_0202A3FE:
	sub r1, r2, r1
	strh r1, [r0, #0x0]
_0202A402:
	ldrh r0, [r0, #0x0]
	bx lr
	nop
_0202A408: .word 0x0000270F

	thumb_func_start FUN_0202A40C
FUN_0202A40C: ; 0x0202A40C
	cmp r1, #0x2
	beq _0202A416
	cmp r1, #0x3
	beq _0202A424
	b _0202A440
_0202A416:
	mov r1, #0x0
	strb r1, [r0, #0x2]
	ldrh r2, [r0, #0x8]
	mov r1, #0x10
	bic r2, r1
	strh r2, [r0, #0x8]
	b _0202A440
_0202A424:
	ldrh r1, [r0, #0x8]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1f
	beq _0202A434
	ldrb r1, [r0, #0x2]
	add r1, r1, #0x1
	strb r1, [r0, #0x2]
	b _0202A440
_0202A434:
	mov r1, #0x1
	strb r1, [r0, #0x2]
	ldrh r2, [r0, #0x8]
	mov r1, #0x10
	orr r1, r2
	strh r1, [r0, #0x8]
_0202A440:
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_0202A444
FUN_0202A444: ; 0x0202A444
	cmp r1, #0x2
	beq _0202A452
	cmp r1, #0x3
	beq _0202A458
	cmp r1, #0x4
	beq _0202A464
	b _0202A46E
_0202A452:
	mov r1, #0x1
	strb r1, [r0, #0x3]
	b _0202A46E
_0202A458:
	ldrb r1, [r0, #0x3]
	cmp r1, #0xa
	bhs _0202A46E
	add r1, r1, #0x1
	strb r1, [r0, #0x3]
	b _0202A46E
_0202A464:
	ldrb r1, [r0, #0x3]
	cmp r1, #0x1
	bls _0202A46E
	sub r1, r1, #0x1
	strb r1, [r0, #0x3]
_0202A46E:
	ldrb r0, [r0, #0x3]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A474
FUN_0202A474: ; 0x0202A474
	push {r3, lr}
	add r3, r0, #0x0
	cmp r1, #0x0
	bne _0202A48A
	add r3, #0xc0
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}
_0202A48A:
	add r3, #0x18
	add r0, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}

	thumb_func_start FUN_0202A498
FUN_0202A498: ; 0x0202A498
	push {r3, lr}
	cmp r1, #0x0
	bne _0202A4AA
	add r1, r2, #0x0
	add r0, #0xc0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}
_0202A4AA:
	add r1, r2, #0x0
	add r0, #0x18
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202A4B8
FUN_0202A4B8: ; 0x0202A4B8
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldrb r0, [r1, #0x2]
	mov r2, #0xfa
	lsl r2, r2, #0x2
	sub r0, r0, #0x1
	add r3, r0, #0x0
	mul r3, r2
	lsl r0, r3, #0x10
	lsr r4, r0, #0x10
	ldrh r3, [r1, #0x4]
	mov r0, #0xa
	ldrb r5, [r1, #0x3]
	mul r0, r3
	mov r3, #0x14
	mul r3, r5
	lsl r0, r0, #0x10
	lsl r3, r3, #0x10
	lsr r0, r0, #0x10
	lsr r3, r3, #0x10
	add r3, r0, r3
	add r0, r2, #0x0
	sub r0, #0x32
	cmp r3, r0
	ble _0202A4EE
	mov r5, #0x0
	b _0202A4F6
_0202A4EE:
	sub r2, #0x32
	sub r0, r2, r3
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
_0202A4F6:
	ldrh r1, [r1, #0x6]
	ldr r0, _0202A51C ; =0x000003CA
	cmp r1, r0
	bls _0202A502
	mov r1, #0x0
	b _0202A510
_0202A502:
	add r0, #0x1e
	sub r0, r0, r1
	mov r1, #0x1e
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_0202A510:
	add r0, r4, r5
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	strh r0, [r6, #0x16]
	pop {r4-r6, pc}
	.balign 4
_0202A51C: .word 0x000003CA

	thumb_func_start FUN_0202A520
FUN_0202A520: ; 0x0202A520
	ldrh r0, [r0, #0x16]
	bx lr

	thumb_func_start FUN_0202A524
FUN_0202A524: ; 0x0202A524
	push {r3, lr}
	ldrh r0, [r0, #0x16]
	mov r1, #0xfa
	lsl r1, r1, #0x2
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202A538
FUN_0202A538: ; 0x0202A538
	push {r4-r5}
	cmp r1, #0x5
	bne _0202A544
	mov r0, #0x0
	pop {r4-r5}
	bx lr
_0202A544:
	cmp r2, #0x2
	beq _0202A54E
	cmp r2, #0x3
	beq _0202A558
	b _0202A56A
_0202A54E:
	lsl r2, r1, #0x1
	mov r3, #0x0
	add r2, r0, r2
	strh r3, [r2, #0xc]
	b _0202A56A
_0202A558:
	add r5, r0, #0x0
	add r5, #0xc
	lsl r4, r1, #0x1
	ldrh r3, [r5, r4]
	ldr r2, _0202A574 ; =0x0000FFFE
	cmp r3, r2
	bhs _0202A56A
	add r2, r3, #0x1
	strh r2, [r5, r4]
_0202A56A:
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, #0xc]
	pop {r4-r5}
	bx lr
	.balign 4
_0202A574: .word 0x0000FFFE

	thumb_func_start FUN_0202A578
FUN_0202A578: ; 0x0202A578
	push {r3-r4}
	mov r3, #0x1
	mov r4, #0x0
	cmp r1, #0x0
	bls _0202A590
_0202A582:
	add r4, r4, #0x1
	lsl r4, r4, #0x10
	lsl r3, r3, #0x11
	lsr r4, r4, #0x10
	lsr r3, r3, #0x10
	cmp r4, r1
	blo _0202A582
_0202A590:
	cmp r2, #0x0
	beq _0202A5B4
	cmp r2, #0x1
	beq _0202A5AC
	cmp r2, #0x2
	bne _0202A5C2
	ldr r1, _0202A5C8 ; =0x0000FFFF
	eor r1, r3
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldrh r1, [r0, #0x8]
	and r1, r2
	strh r1, [r0, #0x8]
	b _0202A5C2
_0202A5AC:
	ldrh r1, [r0, #0x8]
	orr r1, r3
	strh r1, [r0, #0x8]
	b _0202A5C2
_0202A5B4:
	ldrh r0, [r0, #0x8]
	add r2, r0, #0x0
	asr r2, r1
	mov r0, #0x1
	and r0, r2
	pop {r3-r4}
	bx lr
_0202A5C2:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
_0202A5C8: .word 0x0000FFFF

	thumb_func_start FUN_0202A5CC
FUN_0202A5CC: ; 0x0202A5CC
	str r1, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0202A5D0
FUN_0202A5D0: ; 0x0202A5D0
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0202A5D4
FUN_0202A5D4: ; 0x0202A5D4
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x17
	add r4, r2, #0x0
	bl FUN_02022610
	mov r1, #0x69
	lsl r1, r1, #0x2
	add r1, r0, r1
	lsl r0, r5, #0x3
	add r0, r1, r0
	add r1, r4, #0x0
	bl FUN_02013960
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202A5F4
FUN_0202A5F4: ; 0x0202A5F4
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x17
	bl FUN_02022610
	mov r1, #0x69
	lsl r1, r1, #0x2
	add r1, r0, r1
	lsl r0, r4, #0x3
	add r0, r1, r0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A60C
FUN_0202A60C: ; 0x0202A60C
	push {r3-r6}
	add r4, r3, #0x0
	mov r3, #0x1
	cmp r2, #0x0
	beq _0202A66C
	cmp r2, #0xc8
	bhi _0202A66C
	cmp r1, #0x0
	beq _0202A66C
	cmp r1, #0xa
	bhi _0202A66C
	sub r5, r2, #0x1
	sub r2, r1, #0x1
	mov r1, #0xc8
	mul r1, r2
	add r1, r5, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsr r6, r1, #0x1f
	lsl r5, r1, #0x1d
	sub r5, r5, r6
	mov r2, #0x1d
	ror r5, r2
	add r2, r6, r5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	lsl r3, r2
	lsl r2, r3, #0x18
	lsl r1, r1, #0x15
	lsr r5, r2, #0x18
	add r3, r0, #0x4
	lsr r2, r1, #0x18
	ldrb r1, [r3, r2]
	orr r1, r5
	strb r1, [r3, r2]
	ldr r3, [r4, #0x0]
	ldr r1, [r4, #0x8]
	lsl r5, r3, #0x18
	ldr r3, [r4, #0x4]
	lsl r1, r1, #0x18
	lsl r3, r3, #0x18
	lsr r3, r3, #0x8
	ldr r2, [r4, #0xc]
	lsr r1, r1, #0x10
	orr r3, r5
	orr r1, r3
	orr r1, r2
	str r1, [r0, #0x0]
_0202A66C:
	pop {r3-r6}
	bx lr

	thumb_func_start FUN_0202A670
FUN_0202A670: ; 0x0202A670
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r4, #0x4
	mov r1, #0x0
	mov r2, #0xfa
	bl MI_CpuFill8
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A68C
FUN_0202A68C: ; 0x0202A68C
	ldr r3, [r0, #0x0]
	ldr r2, [r1, #0x0]
	cmp r3, r2
	bls _0202A698
	mov r0, #0x1
	bx lr
_0202A698:
	ldr r3, [r0, #0x4]
	ldr r2, [r1, #0x4]
	cmp r3, r2
	bls _0202A6A4
	mov r0, #0x1
	bx lr
_0202A6A4:
	ldr r2, [r0, #0x8]
	ldr r0, [r1, #0x8]
	cmp r2, r0
	bls _0202A6B0
	mov r0, #0x1
	bx lr
_0202A6B0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202A6B4
FUN_0202A6B4: ; 0x0202A6B4
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r7, #0x1
	cmp r6, #0xc8
	bhi _0202A6C8
	cmp r4, #0xa
	bls _0202A6CE
_0202A6C8:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0202A6CE:
	ldr r0, [r5, #0x0]
	lsr r1, r0, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	lsr r1, r0, #0x10
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x4]
	lsr r1, r0, #0x8
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r3, #0x0
	add r1, sp, #0x0
	bl FUN_0202A68C
	cmp r0, #0x0
	beq _0202A706
	add r0, r5, #0x0
	bl FUN_0202A670
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0202A706:
	sub r1, r4, #0x1
	mov r0, #0xc8
	mul r0, r1
	sub r2, r6, #0x1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1d
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	add r0, r5, r0
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r7, #0x0
	lsl r2, r1
	lsl r1, r2, #0x18
	ldrb r0, [r0, #0x4]
	lsr r1, r1, #0x18
	tst r0, r1
	beq _0202A73E
	add sp, #0x10
	add r0, r7, #0x0
	pop {r3-r7, pc}
_0202A73E:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_0202A744
FUN_0202A744: ; 0x0202A744
	add r0, #0xfe
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A74C
FUN_0202A74C: ; 0x0202A74C
	add r0, #0xff
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A754
FUN_0202A754: ; 0x0202A754
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x41
	add r4, r2, #0x0
	lsl r1, r1, #0x2
	ldr r2, _0202A77C ; =0x0000063C
	add r1, r5, r1
	add r6, r3, #0x0
	bl MI_CpuCopy8
	ldr r0, _0202A780 ; =0x00000101
	strb r4, [r5, r0]
	sub r0, r0, #0x1
	strb r6, [r5, r0]
	mov r0, #0x1
	add r5, #0xfe
	strb r0, [r5, #0x0]
	pop {r4-r6, pc}
	nop
_0202A77C: .word 0x0000063C
_0202A780: .word 0x00000101

	thumb_func_start FUN_0202A784
FUN_0202A784: ; 0x0202A784
	ldr r2, _0202A794 ; =0x00000101
	ldrb r3, [r0, r2]
	sub r2, r2, #0x1
	strb r3, [r1, #0x0]
	ldrb r0, [r0, r2]
	strb r0, [r1, #0x1]
	bx lr
	nop
_0202A794: .word 0x00000101

	thumb_func_start FUN_0202A798
FUN_0202A798: ; 0x0202A798
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x41
	lsl r1, r1, #0x2
	add r5, r0, r1
	mov r0, #0xe4
	add r4, r2, #0x0
	mul r4, r0
	ldr r0, _0202A834 ; =0x00002710
	add r7, r6, #0x0
	str r0, [r6, #0x0]
	add r0, r5, r4
	add r0, #0xc9
	ldrb r0, [r0, #0x0]
	add r7, #0x30
	strh r0, [r6, #0x4]
	add r0, r5, r4
	add r0, #0xc8
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0202A7EE
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0x11
	mov r3, #0xb
	bl FUN_0200A86C
	add r1, r5, r4
	add r1, #0xc8
	ldrb r1, [r1, #0x0]
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x1f
	add r1, #0x16
	add r2, #0x8
	bl FUN_0200A968
	ldr r0, [sp, #0x0]
	bl FUN_0200A8B8
	b _0202A7FC
_0202A7EE:
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xa8
	add r1, #0x8
	mov r2, #0x10
	bl MI_CpuCopy8
_0202A7FC:
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xca
	add r1, #0x18
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xd2
	add r1, #0x20
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r6, #0x28
	add r0, #0xda
	add r1, r6, #0x0
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r1, r7, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	pop {r3-r7, pc}
	nop
_0202A834: .word 0x00002710

	thumb_func_start FUN_0202A838
FUN_0202A838: ; 0x0202A838
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x1d
	add r4, r2, #0x0
	lsl r1, r1, #0x6
	mov r2, #0xff
	add r1, r5, r1
	lsl r2, r2, #0x2
	add r6, r3, #0x0
	bl MI_CpuCopy8
	ldr r0, _0202A860 ; =0x00000103
	strb r4, [r5, r0]
	sub r0, r0, #0x1
	strb r6, [r5, r0]
	mov r0, #0x1
	add r5, #0xff
	strb r0, [r5, #0x0]
	pop {r4-r6, pc}
	.balign 4
_0202A860: .word 0x00000103

	thumb_func_start FUN_0202A864
FUN_0202A864: ; 0x0202A864
	ldr r2, _0202A874 ; =0x00000103
	ldrb r3, [r0, r2]
	sub r2, r2, #0x1
	strb r3, [r1, #0x0]
	ldrb r0, [r0, r2]
	strb r0, [r1, #0x1]
	bx lr
	nop
_0202A874: .word 0x00000103

	thumb_func_start FUN_0202A878
FUN_0202A878: ; 0x0202A878
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0xff
	lsl r1, r1, #0x2
	bl FUN_02016998
	add r4, r0, #0x0
	mov r0, #0x1d
	lsl r0, r0, #0x6
	mov r2, #0xff
	add r0, r5, r0
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuCopy8
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202A89C
FUN_0202A89C: ; 0x0202A89C
	mov r0, #0xd
	lsl r0, r0, #0x8
	bx lr
	.balign 4

	thumb_func_start FUN_0202A8A4
FUN_0202A8A4: ; 0x0202A8A4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0202A1E4
	add r0, r4, #0x0
	add r0, #0x3c
	bl FUN_0202A1F0
	mov r0, #0x69
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0202A204
	mov r0, #0x71
	lsl r0, r0, #0x2
	add r0, r4, r0
	bl FUN_0202A230
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202A8CC
FUN_0202A8CC: ; 0x0202A8CC
	ldr r3, _0202A8D4 ; =FUN_02022610
	mov r1, #0x17
	bx r3
	nop
_0202A8D4: .word FUN_02022610

	thumb_func_start FUN_0202A8D8
FUN_0202A8D8: ; 0x0202A8D8
	push {r3, lr}
	mov r1, #0x17
	bl FUN_02022610
	add r0, #0x3c
	pop {r3, pc}

	thumb_func_start FUN_0202A8E4
FUN_0202A8E4: ; 0x0202A8E4
	push {r3, lr}
	mov r1, #0x17
	bl FUN_02022610
	mov r1, #0x71
	lsl r1, r1, #0x2
	add r0, r0, r1
	pop {r3, pc}

	thumb_func_start FUN_0202A8F4
FUN_0202A8F4: ; 0x0202A8F4
	mov r0, #0xe
	bx lr

	thumb_func_start FUN_0202A8F8
FUN_0202A8F8: ; 0x0202A8F8
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	strb r1, [r0, #0xc]
	strb r1, [r0, #0xd]
	bx lr

	thumb_func_start FUN_0202A918
FUN_0202A918: ; 0x0202A918
	ldr r3, _0202A920 ; =FUN_02022610
	mov r1, #0x18
	bx r3
	nop
_0202A920: .word FUN_02022610

	thumb_func_start FUN_0202A924
FUN_0202A924: ; 0x0202A924
	mov r0, #0x45
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0202A92C
FUN_0202A92C: ; 0x0202A92C
	push {r4, lr}
	mov r2, #0x45
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl memset
	bl rand_MT
	str r0, [r4, #0x0]
	bl rand_MT
	str r0, [r4, #0x4]
	mov r1, #0x0
	add r3, r4, #0x0
	ldr r0, _0202A980 ; =0x0000FFFF
	str r1, [r4, #0x8]
	strh r0, [r4, #0xc]
	strh r0, [r4, #0xe]
	mov r0, #0x15
	add r3, #0x10
	strb r0, [r4, #0x10]
	add r2, r1, #0x0
_0202A95A:
	str r2, [r3, #0x4]
	strb r2, [r3, #0x8]
	strb r2, [r3, #0x9]
	strb r2, [r3, #0xa]
	strb r2, [r3, #0xb]
	add r1, r1, #0x1
	add r3, #0x8
	cmp r1, #0x15
	blt _0202A95A
	ldr r0, _0202A984 ; =0x0000010F
	strb r2, [r4, r0]
	add r1, r0, #0x1
	strb r2, [r4, r1]
	add r1, r0, #0x2
	strb r2, [r4, r1]
	add r0, r0, #0x3
	strb r2, [r4, r0]
	pop {r4, pc}
	nop
_0202A980: .word 0x0000FFFF
_0202A984: .word 0x0000010F

	thumb_func_start FUN_0202A988
FUN_0202A988: ; 0x0202A988
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_0202A990
FUN_0202A990: ; 0x0202A990
	push {r3, lr}
	cmp r1, #0x1
	beq _0202A99C
	cmp r1, #0x2
	beq _0202A9A0
	b _0202A9A4
_0202A99C:
	ldr r0, [r0, #0x0]
	pop {r3, pc}
_0202A9A0:
	ldr r0, [r0, #0x4]
	pop {r3, pc}
_0202A9A4:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0202A9AC
FUN_0202A9AC: ; 0x0202A9AC
	add r0, #0xbc
	bx lr

	thumb_func_start FUN_0202A9B0
FUN_0202A9B0: ; 0x0202A9B0
	ldr r3, _0202A9B8 ; =FUN_02022610
	mov r1, #0x19
	bx r3
	nop
_0202A9B8: .word FUN_02022610

	thumb_func_start FUN_0202A9BC
FUN_0202A9BC: ; 0x0202A9BC
	add r0, #0x10
	bx lr

	thumb_func_start FUN_0202A9C0
FUN_0202A9C0: ; 0x0202A9C0
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202A9C4
FUN_0202A9C4: ; 0x0202A9C4
	strb r0, [r1, #0x0]
	bx lr

	thumb_func_start FUN_0202A9C8
FUN_0202A9C8: ; 0x0202A9C8
	add r1, r1, #0x4
	lsl r0, r0, #0x3
	add r0, r1, r0
	bx lr

	thumb_func_start FUN_0202A9D0
FUN_0202A9D0: ; 0x0202A9D0
	push {r3-r7, lr}
	add r5, r1, #0x0
	bl FUN_0202A9B0
	add r6, r0, #0x0
	mov r4, #0x0
	add r6, #0x10
	add r7, r4, #0x0
_0202A9E0:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r6, #0x0
	bl FUN_0202A9C8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202A9F8
	sub r1, r1, r5
	str r1, [r0, #0x0]
	bpl _0202A9F8
	str r7, [r0, #0x0]
_0202A9F8:
	add r4, r4, #0x1
	cmp r4, #0x15
	blt _0202A9E0
	pop {r3-r7, pc}

	thumb_func_start FUN_0202AA00
FUN_0202AA00: ; 0x0202AA00
	push {r3, lr}
	bl FUN_0202A9B0
	ldr r1, _0202AA10 ; =0x0000010F
	mov r2, #0x1
	strb r2, [r0, r1]
	pop {r3, pc}
	nop
_0202AA10: .word 0x0000010F

	thumb_func_start FUN_0202AA14
FUN_0202AA14: ; 0x0202AA14
	ldr r1, _0202AA1C ; =0x0000010F
	ldrb r0, [r0, r1]
	bx lr
	nop
_0202AA1C: .word 0x0000010F

	thumb_func_start FUN_0202AA20
FUN_0202AA20: ; 0x0202AA20
	add r2, r0, #0x0
	add r2, #0xc8
	ldr r3, [r2, #0x0]
	cmp r3, r1
	beq _0202AA34
	add r2, r0, #0x0
	add r2, #0xcc
	str r3, [r2, #0x0]
	add r0, #0xc8
	str r1, [r0, #0x0]
_0202AA34:
	bx lr
	.balign 4

	thumb_func_start FUN_0202AA38
FUN_0202AA38: ; 0x0202AA38
	add r0, #0xcc
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AA40
FUN_0202AA40: ; 0x0202AA40
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blo _0202AA4E
	bl ErrorHandling
_0202AA4E:
	mov r0, #0x43
	add r1, r5, r4
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AA58
FUN_0202AA58: ; 0x0202AA58
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x3
	blo _0202AA68
	bl ErrorHandling
_0202AA68:
	mov r0, #0x43
	add r1, r5, r4
	lsl r0, r0, #0x2
	strb r6, [r1, r0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202AA74
FUN_0202AA74: ; 0x0202AA74
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blo _0202AA82
	bl ErrorHandling
_0202AA82:
	mov r0, #0x14
	mul r0, r4
	add r0, r5, r0
	add r0, #0xe2
	ldrb r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202AA90
FUN_0202AA90: ; 0x0202AA90
	ldr r2, [r0, #0x0]
	mov r1, #0x14
	mov r0, #0x0
_0202AA96:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0202AA96
	bx lr

	thumb_func_start FUN_0202AAA0
FUN_0202AAA0: ; 0x0202AAA0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blo _0202AAAE
	bl ErrorHandling
_0202AAAE:
	mov r0, #0x14
	add r5, #0xd0
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AAB8
FUN_0202AAB8: ; 0x0202AAB8
	cmp r1, #0x8
	bhi _0202AAF8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202AAC8: ; jump table (using 16-bit offset)
	.short _0202AAF8 - _0202AAC8 - 2; case 0
	.short _0202AADA - _0202AAC8 - 2; case 1
	.short _0202AADE - _0202AAC8 - 2; case 2
	.short _0202AAE2 - _0202AAC8 - 2; case 3
	.short _0202AAE6 - _0202AAC8 - 2; case 4
	.short _0202AAEA - _0202AAC8 - 2; case 5
	.short _0202AAEE - _0202AAC8 - 2; case 6
	.short _0202AAF2 - _0202AAC8 - 2; case 7
	.short _0202AAF6 - _0202AAC8 - 2; case 8
_0202AADA:
	ldr r0, [r0, #0x0]
	bx lr
_0202AADE:
	ldr r0, [r0, #0x4]
	bx lr
_0202AAE2:
	ldr r0, [r0, #0x8]
	bx lr
_0202AAE6:
	ldrh r0, [r0, #0xc]
	bx lr
_0202AAEA:
	ldrh r0, [r0, #0xe]
	bx lr
_0202AAEE:
	ldrb r0, [r0, #0x10]
	bx lr
_0202AAF2:
	ldrb r0, [r0, #0x11]
	bx lr
_0202AAF6:
	ldrb r0, [r0, #0x12]
_0202AAF8:
	bx lr
	.balign 4

	thumb_func_start FUN_0202AAFC
FUN_0202AAFC: ; 0x0202AAFC
	cmp r1, #0x8
	bhi _0202AB3C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202AB0C: ; jump table (using 16-bit offset)
	.short _0202AB3C - _0202AB0C - 2; case 0
	.short _0202AB1E - _0202AB0C - 2; case 1
	.short _0202AB22 - _0202AB0C - 2; case 2
	.short _0202AB26 - _0202AB0C - 2; case 3
	.short _0202AB2A - _0202AB0C - 2; case 4
	.short _0202AB2E - _0202AB0C - 2; case 5
	.short _0202AB32 - _0202AB0C - 2; case 6
	.short _0202AB36 - _0202AB0C - 2; case 7
	.short _0202AB3A - _0202AB0C - 2; case 8
_0202AB1E:
	str r2, [r0, #0x0]
	bx lr
_0202AB22:
	str r2, [r0, #0x4]
	bx lr
_0202AB26:
	str r2, [r0, #0x8]
	bx lr
_0202AB2A:
	strh r2, [r0, #0xc]
	bx lr
_0202AB2E:
	strh r2, [r0, #0xe]
	bx lr
_0202AB32:
	strb r2, [r0, #0x10]
	bx lr
_0202AB36:
	strb r2, [r0, #0x11]
	bx lr
_0202AB3A:
	strb r2, [r0, #0x12]
_0202AB3C:
	bx lr
	.balign 4

	thumb_func_start FUN_0202AB40
FUN_0202AB40: ; 0x0202AB40
	ldr r1, _0202AB48 ; =0x00000111
	add r0, r0, r1
	bx lr
	nop
_0202AB48: .word 0x00000111

	thumb_func_start FUN_0202AB4C
FUN_0202AB4C: ; 0x0202AB4C
	mov r1, #0x11
	lsl r1, r1, #0x4
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_0202AB54
FUN_0202AB54: ; 0x0202AB54
	mov r1, #0x11
	lsl r1, r1, #0x4
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _0202AB62
	mov r0, #0x1
	bx lr
_0202AB62:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202AB68
FUN_0202AB68: ; 0x0202AB68
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x2
	bls _0202AB76
	bl ErrorHandling
_0202AB76:
	ldr r0, _0202AB7C ; =0x00000112
	strb r4, [r5, r0]
	pop {r3-r5, pc}
	.balign 4
_0202AB7C: .word 0x00000112

	thumb_func_start FUN_0202AB80
FUN_0202AB80: ; 0x0202AB80
	ldr r1, _0202AB88 ; =0x00000112
	ldrb r0, [r0, r1]
	bx lr
	nop
_0202AB88: .word 0x00000112

	thumb_func_start FUN_0202AB8C
FUN_0202AB8C: ; 0x0202AB8C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0202A9B0
	ldrh r1, [r0, #0xc]
	strh r1, [r5, #0x0]
	ldrh r0, [r0, #0xe]
	strh r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202ABA0
FUN_0202ABA0: ; 0x0202ABA0
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_0202A9B0
	add r4, r0, #0x0
	cmp r5, #0x10
	blo _0202ABB2
	bl ErrorHandling
_0202ABB2:
	ldrh r0, [r4, #0xc]
	strh r0, [r4, #0xe]
	strh r5, [r4, #0xc]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202ABBC
FUN_0202ABBC: ; 0x0202ABBC
	ldr r3, _0202ABC4 ; =FUN_02022610
	mov r1, #0x1a
	bx r3
	nop
_0202ABC4: .word FUN_02022610

	thumb_func_start FUN_0202ABC8
FUN_0202ABC8: ; 0x0202ABC8
	mov r0, #0xf4
	bx lr

	thumb_func_start FUN_0202ABCC
FUN_0202ABCC: ; 0x0202ABCC
	ldr r3, _0202ABD8 ; =MIi_CpuClearFast
	add r1, r0, #0x0
	mov r0, #0x0
	mov r2, #0xf4
	bx r3
	nop
_0202ABD8: .word MIi_CpuClearFast

	thumb_func_start FUN_0202ABDC
FUN_0202ABDC: ; 0x0202ABDC
	add r0, #0xec
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202ABE4
FUN_0202ABE4: ; 0x0202ABE4
	add r0, #0xec
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202ABEC
FUN_0202ABEC: ; 0x0202ABEC
	ldr r3, _0202ABF4 ; =MIi_CpuCopyFast
	mov r2, #0xec
	bx r3
	nop
_0202ABF4: .word MIi_CpuCopyFast

	thumb_func_start FUN_0202ABF8
FUN_0202ABF8: ; 0x0202ABF8
	ldr r3, _0202AC04 ; =MIi_CpuCopyFast
	add r2, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0xec
	bx r3
	.balign 4
_0202AC04: .word MIi_CpuCopyFast

	thumb_func_start FUN_0202AC08
FUN_0202AC08: ; 0x0202AC08
	add r0, #0xf0
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC10
FUN_0202AC10: ; 0x0202AC10
	add r0, #0xf0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC18
FUN_0202AC18: ; 0x0202AC18
	add r0, #0xee
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC20
FUN_0202AC20: ; 0x0202AC20
	ldr r0, _0202AC24 ; =0x00001354
	bx lr
	.balign 4
_0202AC24: .word 0x00001354

	thumb_func_start FUN_0202AC28
FUN_0202AC28: ; 0x0202AC28
	bx lr
	.balign 4

	thumb_func_start FUN_0202AC2C
FUN_0202AC2C: ; 0x0202AC2C
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x8
	blt _0202AC3A
	bl ErrorHandling
_0202AC3A:
	mov r0, #0x1
	lsl r0, r0, #0x8
	add r6, r5, r0
	lsl r3, r4, #0x2
	ldr r2, [r6, r3]
	ldr r1, _0202AC60 ; =0xEDB88320
	cmp r2, r1
	bne _0202AC58
	add r0, #0x2c
	add r1, r5, r0
	lsl r0, r4, #0x6
	add r0, r4, r0
	lsl r0, r0, #0x2
	add r0, r1, r0
	pop {r4-r6, pc}
_0202AC58:
	mov r0, #0x0
	str r0, [r6, r3]
	pop {r4-r6, pc}
	nop
_0202AC60: .word 0xEDB88320

	thumb_func_start FUN_0202AC64
FUN_0202AC64: ; 0x0202AC64
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blt _0202AC72
	bl ErrorHandling
_0202AC72:
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0202AC8E
	ldr r0, _0202AC94 ; =0x0000094C
	add r1, r5, r0
	mov r0, #0xd6
	lsl r0, r0, #0x2
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}
_0202AC8E:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0202AC94: .word 0x0000094C

	thumb_func_start FUN_0202AC98
FUN_0202AC98: ; 0x0202AC98
	push {r3-r7, lr}
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r7, r2, #0x0
	bl FUN_0202ADF0
	cmp r0, #0x0
	bne _0202ACAC
	mov r0, #0x0
	pop {r3-r7, pc}
_0202ACAC:
	mov r0, #0x1
	mov r4, #0x0
	add r2, r5, #0x0
	lsl r0, r0, #0x8
_0202ACB4:
	ldr r1, [r2, r0]
	cmp r1, #0x0
	bne _0202ACF6
	lsl r0, r4, #0x6
	mov r2, #0x4b
	add r0, r4, r0
	lsl r2, r2, #0x2
	lsl r6, r0, #0x2
	add r1, r5, r2
	ldr r0, [sp, #0x0]
	add r1, r1, r6
	sub r2, #0x28
	bl MI_CpuCopy8
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x1
	ldr r2, _0202AD04 ; =0xEDB88320
	lsl r0, r0, #0x8
	str r2, [r1, r0]
	add r0, #0x2e
	add r1, r5, r0
	ldrh r0, [r1, r6]
	mov r2, #0x3
	bic r0, r2
	lsl r2, r7, #0x10
	lsr r3, r2, #0x10
	mov r2, #0x3
	and r2, r3
	orr r0, r2
	strh r0, [r1, r6]
	mov r0, #0x1
	pop {r3-r7, pc}
_0202ACF6:
	add r4, r4, #0x1
	add r2, r2, #0x4
	cmp r4, #0x8
	blt _0202ACB4
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0202AD04: .word 0xEDB88320

	thumb_func_start FUN_0202AD08
FUN_0202AD08: ; 0x0202AD08
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_0202AE0C
	cmp r0, #0x0
	bne _0202AD1A
	mov r0, #0x0
	pop {r4-r6, pc}
_0202AD1A:
	ldr r0, _0202AD88 ; =0x00000152
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _0202AD34
	add r0, r5, #0x0
	bl FUN_0202ADF0
	cmp r0, #0x0
	bne _0202AD34
	mov r0, #0x0
	pop {r4-r6, pc}
_0202AD34:
	mov r0, #0x12
	mov r4, #0x0
	add r2, r5, #0x0
	lsl r0, r0, #0x4
_0202AD3C:
	ldr r1, [r2, r0]
	cmp r1, #0x0
	bne _0202AD7C
	ldr r1, _0202AD8C ; =0x0000094C
	mov r2, #0xd6
	add r3, r5, r1
	lsl r2, r2, #0x2
	add r1, r4, #0x0
	mul r1, r2
	add r0, r6, #0x0
	add r1, r3, r1
	bl MI_CpuCopy8
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	ldr r2, _0202AD90 ; =0xEDB88320
	lsl r0, r0, #0x4
	str r2, [r1, r0]
	add r0, #0x32
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _0202AD78
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x1
	bl FUN_0202AC98
_0202AD78:
	mov r0, #0x1
	pop {r4-r6, pc}
_0202AD7C:
	add r4, r4, #0x1
	add r2, r2, #0x4
	cmp r4, #0x3
	blt _0202AD3C
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0202AD88: .word 0x00000152
_0202AD8C: .word 0x0000094C
_0202AD90: .word 0xEDB88320

	thumb_func_start FUN_0202AD94
FUN_0202AD94: ; 0x0202AD94
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	sub r0, r4, #0x1
	cmp r0, #0x8
	blt _0202ADA4
	bl ErrorHandling
_0202ADA4:
	sub r4, r4, #0x1
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x1
	mov r2, #0x0
	lsl r0, r0, #0x8
	str r2, [r1, r0]
	add r0, #0x2e
	add r3, r5, r0
	lsl r0, r4, #0x6
	add r0, r4, r0
	lsl r2, r0, #0x2
	ldrh r1, [r3, r2]
	mov r0, #0x3
	bic r1, r0
	strh r1, [r3, r2]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0202ADC8
FUN_0202ADC8: ; 0x0202ADC8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x3
	blt _0202ADD6
	bl ErrorHandling
_0202ADD6:
	lsl r0, r4, #0x2
	add r1, r5, r0
	mov r0, #0x12
	mov r2, #0x0
	lsl r0, r0, #0x4
	str r2, [r1, r0]
	add r0, r5, #0x0
	add r1, r4, #0x1
	bl FUN_0202AEC4
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202ADF0
FUN_0202ADF0: ; 0x0202ADF0
	mov r1, #0x1
	mov r3, #0x0
	lsl r1, r1, #0x8
_0202ADF6:
	ldr r2, [r0, r1]
	cmp r2, #0x0
	bne _0202AE00
	mov r0, #0x1
	bx lr
_0202AE00:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, #0x8
	blt _0202ADF6
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202AE0C
FUN_0202AE0C: ; 0x0202AE0C
	mov r1, #0x12
	mov r3, #0x0
	lsl r1, r1, #0x4
_0202AE12:
	ldr r2, [r0, r1]
	cmp r2, #0x0
	bne _0202AE1C
	mov r0, #0x1
	bx lr
_0202AE1C:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, #0x3
	blt _0202AE12
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202AE28
FUN_0202AE28: ; 0x0202AE28
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x8
	blt _0202AE36
	bl ErrorHandling
_0202AE36:
	lsl r0, r5, #0x2
	add r1, r4, r0
	mov r0, #0x1
	lsl r0, r0, #0x8
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0202AE48
	mov r0, #0x0
	pop {r3-r5, pc}
_0202AE48:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AE4C
FUN_0202AE4C: ; 0x0202AE4C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	cmp r5, #0x3
	blt _0202AE5A
	bl ErrorHandling
_0202AE5A:
	lsl r0, r5, #0x2
	add r1, r4, r0
	mov r0, #0x12
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0202AE6C
	mov r0, #0x0
	pop {r3-r5, pc}
_0202AE6C:
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AE70
FUN_0202AE70: ; 0x0202AE70
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_0202AE76:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202AE4C
	cmp r0, #0x1
	bne _0202AE86
	mov r0, #0x1
	pop {r3-r5, pc}
_0202AE86:
	add r4, r4, #0x1
	cmp r4, #0x3
	blt _0202AE76
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AE90
FUN_0202AE90: ; 0x0202AE90
	push {r3-r4}
	cmp r1, #0x0
	beq _0202AEB8
	ldr r2, _0202AEC0 ; =0x0000012E
	mov r3, #0x0
	add r4, r0, r2
	add r0, r2, #0x0
	sub r0, #0x2a
_0202AEA0:
	ldrh r2, [r4, #0x0]
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1e
	cmp r1, r2
	bne _0202AEB0
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0202AEB0:
	add r3, r3, #0x1
	add r4, r4, r0
	cmp r3, #0x8
	blt _0202AEA0
_0202AEB8:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0202AEC0: .word 0x0000012E

	thumb_func_start FUN_0202AEC4
FUN_0202AEC4: ; 0x0202AEC4
	push {r3-r5, lr}
	cmp r1, #0x0
	beq _0202AEEE
	ldr r3, _0202AEF0 ; =0x0000012E
	mov r4, #0x41
	mov r2, #0x0
	add r3, r0, r3
	lsl r4, r4, #0x2
_0202AED4:
	ldrh r5, [r3, #0x0]
	lsl r5, r5, #0x1e
	lsr r5, r5, #0x1e
	cmp r1, r5
	bne _0202AEE6
	add r1, r2, #0x1
	bl FUN_0202AD94
	pop {r3-r5, pc}
_0202AEE6:
	add r2, r2, #0x1
	add r3, r3, r4
	cmp r2, #0x8
	blt _0202AED4
_0202AEEE:
	pop {r3-r5, pc}
	.balign 4
_0202AEF0: .word 0x0000012E

	thumb_func_start FUN_0202AEF4
FUN_0202AEF4: ; 0x0202AEF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x2
	add r4, r1, #0x0
	lsl r0, r0, #0xa
	cmp r4, r0
	blt _0202AF06
	bl ErrorHandling
_0202AF06:
	mov r0, #0x1
	mov r1, #0x7
	add r2, r4, #0x0
	and r2, r1
	add r1, r0, #0x0
	lsl r1, r2
	asr r2, r4, #0x2
	lsr r2, r2, #0x1d
	add r2, r4, r2
	asr r2, r2, #0x3
	ldrb r2, [r5, r2]
	tst r1, r2
	bne _0202AF22
	mov r0, #0x0
_0202AF22:
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AF24
FUN_0202AF24: ; 0x0202AF24
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x2
	add r4, r1, #0x0
	lsl r0, r0, #0xa
	cmp r4, r0
	blt _0202AF36
	bl ErrorHandling
_0202AF36:
	asr r0, r4, #0x2
	lsr r0, r0, #0x1d
	add r0, r4, r0
	asr r0, r0, #0x3
	mov r1, #0x7
	ldrb r3, [r5, r0]
	mov r2, #0x1
	and r1, r4
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strb r1, [r5, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_0202AF50
FUN_0202AF50: ; 0x0202AF50
	ldr r3, _0202AF58 ; =FUN_0202AEF4
	ldr r1, _0202AF5C ; =0x000007FF
	bx r3
	nop
_0202AF58: .word FUN_0202AEF4
_0202AF5C: .word 0x000007FF

	thumb_func_start FUN_0202AF60
FUN_0202AF60: ; 0x0202AF60
	ldr r3, _0202AF68 ; =FUN_0202AF24
	ldr r1, _0202AF6C ; =0x000007FF
	bx r3
	nop
_0202AF68: .word FUN_0202AF24
_0202AF6C: .word 0x000007FF

	thumb_func_start FUN_0202AF70
FUN_0202AF70: ; 0x0202AF70
	push {r3, lr}
	ldr r1, _0202AF84 ; =0x021C59D4
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0202AF82
	bl FUN_0202251C
	ldr r1, _0202AF84 ; =0x021C59D4
	str r0, [r1, #0x0]
_0202AF82:
	pop {r3, pc}
	.balign 4
_0202AF84: .word 0x021C59D4

	thumb_func_start FUN_0202AF88
FUN_0202AF88: ; 0x0202AF88
	ldr r0, _0202AF98 ; =0x021C59D4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202AF94
	mov r1, #0x0
	str r1, [r0, #0x0]
_0202AF94:
	bx lr
	nop
_0202AF98: .word 0x021C59D4

	thumb_func_start FUN_0202AF9C
FUN_0202AF9C: ; 0x0202AF9C
	push {r3-r5, lr}
	ldr r4, _0202AFBC ; =0x021C59D4
	mov r5, #0x0
_0202AFA2:
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_0202AE28
	cmp r0, #0x1
	bne _0202AFB2
	add r0, r5, #0x1
	pop {r3-r5, pc}
_0202AFB2:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202AFA2
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0202AFBC: .word 0x021C59D4

	thumb_func_start FUN_0202AFC0
FUN_0202AFC0: ; 0x0202AFC0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202AFCA
	mov r0, #0x0
	pop {r4, pc}
_0202AFCA:
	sub r0, r4, #0x1
	cmp r0, #0x8
	blt _0202AFD4
	bl ErrorHandling
_0202AFD4:
	ldr r0, _0202AFF8 ; =0x021C59D4
	sub r1, r4, #0x1
	ldr r0, [r0, #0x0]
	bl FUN_0202AE28
	cmp r0, #0x1
	bne _0202AFF4
	ldr r0, _0202AFF8 ; =0x021C59D4
	sub r1, r4, #0x1
	ldr r0, [r0, #0x0]
	bl FUN_0202AC2C
	cmp r0, #0x0
	beq _0202AFF4
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0202AFF4:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0202AFF8: .word 0x021C59D4

	thumb_func_start FUN_0202AFFC
FUN_0202AFFC: ; 0x0202AFFC
	cmp r0, #0x0
	beq _0202B016
	ldr r1, _0202B01C ; =0x021C59D4
	ldr r2, [r1, #0x0]
	mov r1, #0x13
	lsl r1, r1, #0x4
	add r2, r2, r1
	sub r1, r0, #0x1
	lsl r0, r1, #0x6
	add r0, r1, r0
	lsl r0, r0, #0x2
	add r0, r2, r0
	bx lr
_0202B016:
	mov r0, #0x0
	bx lr
	nop
_0202B01C: .word 0x021C59D4

	thumb_func_start FUN_0202B020
FUN_0202B020: ; 0x0202B020
	add r1, r0, #0x0
	ldr r0, _0202B02C ; =0x021C59D4
	ldr r3, _0202B030 ; =FUN_0202AD94
	ldr r0, [r0, #0x0]
	bx r3
	nop
_0202B02C: .word 0x021C59D4
_0202B030: .word FUN_0202AD94

	thumb_func_start FUN_0202B034
FUN_0202B034: ; 0x0202B034
	ldr r0, _0202B038 ; =0x00002AB0
	bx lr
	.balign 4
_0202B038: .word 0x00002AB0

	thumb_func_start FUN_0202B03C
FUN_0202B03C: ; 0x0202B03C
	ldr r3, _0202B048 ; =MIi_CpuClear32
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _0202B04C ; =0x00002AB0
	bx r3
	nop
_0202B048: .word MIi_CpuClear32
_0202B04C: .word 0x00002AB0

	thumb_func_start FUN_0202B050
FUN_0202B050: ; 0x0202B050
	push {r3-r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	cmp r0, #0x0
	bne _0202B062
	bl ErrorHandling
_0202B062:
	ldr r1, _0202B1E0 ; =0x00002AA8
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	cmp r0, #0x1e
	blo _0202B070
	bl ErrorHandling
_0202B070:
	ldr r1, _0202B1E4 ; =0x00002AAC
	ldr r0, [sp, #0x0]
	ldr r2, [r0, r1]
	ldr r0, _0202B1E8 ; =0x0000270F
	cmp r2, r0
	blo _0202B07E
	b _0202B1DC
_0202B07E:
	ldr r0, [sp, #0x0]
	sub r1, r1, #0x4
	ldr r1, [r0, r1]
	mov r0, #0x5b
	lsl r0, r0, #0x2
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x0]
	add r0, r0, r2
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4]
	bl FUN_0206B9AC
	str r0, [sp, #0x10]
	mov r0, #0xb
	mov r1, #0x0
	bl FUN_020219F4
	mov r2, #0x5a
	add r6, r0, #0x0
	ldr r1, [sp, #0x14]
	mov r0, #0x0
	lsl r2, r2, #0x2
	bl MIi_CpuClear16
	ldr r0, [sp, #0x10]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0202B18E
	ldr r5, [sp, #0x14]
_0202B0BA:
	ldr r0, [sp, #0x4]
	add r1, r7, #0x0
	bl FUN_0206B9B0
	add r4, r0, #0x0
	bl FUN_020669D4
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _0202B17E
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl FUN_020671BC
	strb r0, [r5, #0x2]
	add r0, r4, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl FUN_020671BC
	mov r1, #0x0
	strb r0, [r5, #0x3]
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl FUN_020671BC
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x32]
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x34]
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x36]
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl FUN_020671BC
	strh r0, [r5, #0x38]
	cmp r6, #0x0
	beq _0202B176
	add r0, r4, #0x0
	mov r1, #0x76
	add r2, r6, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r0, r6, #0x0
	add r1, #0xc
	mov r2, #0xb
	bl FUN_02021EF0
	add r0, r4, #0x0
	mov r1, #0x90
	add r2, r6, #0x0
	bl FUN_020671BC
	add r1, r5, #0x0
	add r0, r6, #0x0
	add r1, #0x22
	mov r2, #0x8
	bl FUN_02021EF0
	b _0202B17C
_0202B176:
	ldr r0, _0202B1EC ; =0x0000FFFF
	strh r0, [r5, #0xc]
	strh r0, [r5, #0x22]
_0202B17C:
	add r5, #0x3c
_0202B17E:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02066A20
	ldr r0, [sp, #0x10]
	add r7, r7, #0x1
	cmp r7, r0
	blt _0202B0BA
_0202B18E:
	ldr r0, [sp, #0x8]
	mov r1, #0x5a
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x2
	strh r2, [r0, r1]
	ldr r0, [sp, #0x8]
	add r2, r1, #0x2
	ldr r3, [r0, #0x4]
	ldr r0, [sp, #0x14]
	add r1, r1, #0x3
	strb r3, [r0, r2]
	ldr r0, [sp, #0x8]
	ldr r2, [r0, #0x8]
	ldr r0, [sp, #0x14]
	strb r2, [r0, r1]
	ldr r1, _0202B1E0 ; =0x00002AA8
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	str r2, [r0, r1]
	ldr r0, [r0, r1]
	cmp r0, #0x1e
	blo _0202B1C6
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	str r2, [r0, r1]
_0202B1C6:
	ldr r1, _0202B1E4 ; =0x00002AAC
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	cmp r6, #0x0
	str r2, [r0, r1]
	beq _0202B1DC
	add r0, r6, #0x0
	bl FUN_02021A20
_0202B1DC:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_0202B1E0: .word 0x00002AA8
_0202B1E4: .word 0x00002AAC
_0202B1E8: .word 0x0000270F
_0202B1EC: .word 0x0000FFFF

	thumb_func_start FUN_0202B1F0
FUN_0202B1F0: ; 0x0202B1F0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202B1FA
	bl ErrorHandling
_0202B1FA:
	ldr r0, _0202B214 ; =0x00002AA8
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	blo _0202B206
	bl ErrorHandling
_0202B206:
	ldr r0, _0202B218 ; =0x00002AAC
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	blo _0202B210
	mov r0, #0x1e
_0202B210:
	pop {r4, pc}
	nop
_0202B214: .word 0x00002AA8
_0202B218: .word 0x00002AAC

	thumb_func_start FUN_0202B21C
FUN_0202B21C: ; 0x0202B21C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0202B22A
	bl ErrorHandling
_0202B22A:
	ldr r0, _0202B248 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B236
	bl ErrorHandling
_0202B236:
	cmp r4, #0x1e
	blt _0202B23E
	bl ErrorHandling
_0202B23E:
	ldr r0, _0202B24C ; =0x00002AAC
	ldr r0, [r5, r0]
	sub r0, r0, r4
	pop {r3-r5, pc}
	nop
_0202B248: .word 0x00002AA8
_0202B24C: .word 0x00002AAC

	thumb_func_start FUN_0202B250
FUN_0202B250: ; 0x0202B250
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0202B25E
	bl ErrorHandling
_0202B25E:
	ldr r0, _0202B298 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B26A
	bl ErrorHandling
_0202B26A:
	cmp r4, #0x1e
	blt _0202B272
	bl ErrorHandling
_0202B272:
	ldr r0, _0202B298 ; =0x00002AA8
	ldr r0, [r5, r0]
	sub r0, r0, #0x1
	sub r2, r0, r4
	bpl _0202B27E
	add r2, #0x1e
_0202B27E:
	mov r1, #0x5b
	lsl r1, r1, #0x2
	mul r1, r2
	mov r0, #0x0
	add r2, r5, r1
_0202B288:
	ldrh r1, [r2, #0x0]
	cmp r1, #0x0
	beq _0202B296
	add r0, r0, #0x1
	add r2, #0x3c
	cmp r0, #0x6
	blo _0202B288
_0202B296:
	pop {r3-r5, pc}
	.balign 4
_0202B298: .word 0x00002AA8

	thumb_func_start FUN_0202B29C
FUN_0202B29C: ; 0x0202B29C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	cmp r5, #0x0
	bne _0202B2AE
	bl ErrorHandling
_0202B2AE:
	ldr r0, _0202B318 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B2BA
	bl ErrorHandling
_0202B2BA:
	cmp r6, #0x1e
	blt _0202B2C2
	bl ErrorHandling
_0202B2C2:
	ldr r0, _0202B318 ; =0x00002AA8
	ldr r0, [r5, r0]
	sub r0, r0, #0x1
	sub r1, r0, r6
	bpl _0202B2CE
	add r1, #0x1e
_0202B2CE:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	mul r0, r1
	add r1, r5, r0
	mov r0, #0x3c
	mul r0, r7
	add r5, r1, r0
	ldrh r0, [r1, r0]
	add r1, r5, #0x0
	add r1, #0xc
	strh r0, [r4, #0x10]
	ldrb r0, [r5, #0x2]
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0x4]
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x8]
	str r0, [r4, #0xc]
	ldrb r0, [r5, #0x3]
	strb r0, [r4, #0x13]
	ldr r0, [r4, #0x0]
	bl FUN_02021E28
	add r1, r5, #0x0
	ldr r0, [r4, #0x4]
	add r1, #0x22
	bl FUN_02021E28
	mov r1, #0x0
_0202B306:
	ldrh r0, [r5, #0x32]
	add r1, r1, #0x1
	add r5, r5, #0x2
	strh r0, [r4, #0x14]
	add r4, r4, #0x2
	cmp r1, #0x4
	blt _0202B306
	pop {r3-r7, pc}
	nop
_0202B318: .word 0x00002AA8

	thumb_func_start FUN_0202B31C
FUN_0202B31C: ; 0x0202B31C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _0202B32C
	bl ErrorHandling
_0202B32C:
	ldr r0, _0202B370 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B338
	bl ErrorHandling
_0202B338:
	cmp r6, #0x1e
	blt _0202B340
	bl ErrorHandling
_0202B340:
	ldr r0, _0202B370 ; =0x00002AA8
	ldr r0, [r5, r0]
	sub r0, r0, #0x1
	sub r2, r0, r6
	bpl _0202B34C
	add r2, #0x1e
_0202B34C:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	add r1, r2, #0x0
	mul r1, r0
	add r2, r5, r1
	sub r1, r0, #0x4
	ldrh r1, [r2, r1]
	str r1, [r4, #0x0]
	sub r1, r0, #0x2
	ldrb r1, [r2, r1]
	sub r0, r0, #0x1
	str r1, [r4, #0x4]
	ldrb r0, [r2, r0]
	str r0, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0xc]
	pop {r4-r6, pc}
	nop
_0202B370: .word 0x00002AA8

	thumb_func_start FUN_0202B374
FUN_0202B374: ; 0x0202B374
	ldr r0, _0202B378 ; =0x00000B88
	bx lr
	.balign 4
_0202B378: .word 0x00000B88

	thumb_func_start FUN_0202B37C
FUN_0202B37C: ; 0x0202B37C
	ldr r3, _0202B388 ; =MIi_CpuClearFast
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _0202B38C ; =0x00000B88
	bx r3
	nop
_0202B388: .word MIi_CpuClearFast
_0202B38C: .word 0x00000B88

	thumb_func_start FUN_0202B390
FUN_0202B390: ; 0x0202B390
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	mov r0, #0x0
	add r1, #0xc
	mov r2, #0xc0
	bl MIi_CpuClearFast
	add r1, r4, #0x0
	mov r0, #0x0
	add r1, #0xcc
	mov r2, #0xc0
	bl MIi_CpuClearFast
	mov r1, #0x63
	lsl r1, r1, #0x2
	mov r0, #0x0
	add r1, r4, r1
	mov r2, #0xc0
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl FUN_0202B3F8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202B3C4
FUN_0202B3C4: ; 0x0202B3C4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, r1
	ble _0202B3D4
	sub r0, r0, r1
	str r0, [r4, #0x4]
	pop {r4, pc}
_0202B3D4:
	add r0, r2, #0x0
	mov r1, #0xf
	bl _s32_div_f
	mov r0, #0xf
	sub r1, r0, r1
	str r1, [r4, #0x4]
	bne _0202B3E6
	str r0, [r4, #0x4]
_0202B3E6:
	mov r1, #0x0
	strb r1, [r4, #0x8]
	add r0, r1, #0x0
_0202B3EC:
	strb r0, [r4, r1]
	add r1, r1, #0x1
	cmp r1, #0x4
	blt _0202B3EC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202B3F8
FUN_0202B3F8: ; 0x0202B3F8
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	bl FUN_0202B40C
	add r0, r4, #0x0
	bl FUN_0202B430
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202B40C
FUN_0202B40C: ; 0x0202B40C
	strb r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0202B410
FUN_0202B410: ; 0x0202B410
	ldrb r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0202B414
FUN_0202B414: ; 0x0202B414
	push {r3, lr}
	mov r3, #0x0
_0202B418:
	ldrb r2, [r0, r3]
	cmp r2, #0x0
	bne _0202B422
	strb r1, [r0, r3]
	pop {r3, pc}
_0202B422:
	add r3, r3, #0x1
	cmp r3, #0x4
	blt _0202B418
	bl ErrorHandling
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202B430
FUN_0202B430: ; 0x0202B430
	mov r2, #0x0
	add r1, r2, #0x0
_0202B434:
	strb r1, [r0, r2]
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _0202B434
	bx lr
	.balign 4

	thumb_func_start FUN_0202B440
FUN_0202B440: ; 0x0202B440
	mov r3, #0x0
_0202B442:
	ldrb r2, [r0, r3]
	cmp r1, r2
	bne _0202B44C
	mov r0, #0x1
	bx lr
_0202B44C:
	add r3, r3, #0x1
	cmp r3, #0x4
	blt _0202B442
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202B458
FUN_0202B458: ; 0x0202B458
	mov r2, #0x0
	add r3, r2, #0x0
_0202B45C:
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	beq _0202B464
	add r3, r3, #0x1
_0202B464:
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _0202B45C
	add r0, r3, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202B470
FUN_0202B470: ; 0x0202B470
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r0, sp, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020126B4
	ldr r0, [sp, #0x8]
	ldr r3, [sp, #0x4]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x0]
	lsl r3, r3, #0x18
	lsl r0, r0, #0x18
	lsr r3, r3, #0x8
	orr r0, r3
	ldr r2, [sp, #0xc]
	orr r0, r1
	orr r0, r2
	str r0, [r5, #0x4]
	strb r4, [r5, #0x0]
	mov r0, #0x0
	strb r0, [r5, #0x1]
	add r5, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x28
	bl MIi_CpuCopyFast
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_0202B4B0
FUN_0202B4B0: ; 0x0202B4B0
	push {r3-r5, lr}
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0202B548
	mov r2, #0x0
	add r3, r0, #0x0
_0202B4BE:
	ldrb r1, [r3, #0x0]
	cmp r5, r1
	bne _0202B4E0
	mov r1, #0x30
	mul r1, r2
	add r0, r0, r1
	ldrb r1, [r0, #0x1]
	cmp r1, #0x3
	blo _0202B4DC
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202B470
	mov r0, #0x1
	pop {r3-r5, pc}
_0202B4DC:
	mov r0, #0x0
	pop {r3-r5, pc}
_0202B4E0:
	add r2, r2, #0x1
	add r3, #0x30
	cmp r2, #0x4
	blt _0202B4BE
	mov r1, #0x0
	add r3, r0, #0x0
_0202B4EC:
	ldrb r2, [r3, #0x0]
	cmp r2, #0x0
	bne _0202B504
	mov r2, #0x30
	mul r2, r1
	add r0, r0, r2
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202B470
	mov r0, #0x1
	pop {r3-r5, pc}
_0202B504:
	add r1, r1, #0x1
	add r3, #0x30
	cmp r1, #0x4
	blt _0202B4EC
	mov r1, #0x0
	add r3, r0, #0x0
_0202B510:
	ldrb r2, [r3, #0x1]
	cmp r2, #0x3
	blo _0202B528
	mov r2, #0x30
	mul r2, r1
	add r0, r0, r2
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202B470
	mov r0, #0x1
	pop {r3-r5, pc}
_0202B528:
	add r1, r1, #0x1
	add r3, #0x30
	cmp r1, #0x4
	blt _0202B510
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202B534
FUN_0202B534: ; 0x0202B534
	add r0, #0x8
	bx lr

	thumb_func_start FUN_0202B538
FUN_0202B538: ; 0x0202B538
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0202B53C
FUN_0202B53C: ; 0x0202B53C
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_0202B540
FUN_0202B540: ; 0x0202B540
	add r0, #0x18
	bx lr

	thumb_func_start FUN_0202B544
FUN_0202B544: ; 0x0202B544
	bx lr
	.balign 4

	thumb_func_start FUN_0202B548
FUN_0202B548: ; 0x0202B548
	push {r4, lr}
	mov r4, #0x0
	cmp r1, #0x4
	bhi _0202B57E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202B55C: ; jump table (using 16-bit offset)
	.short _0202B57E - _0202B55C - 2; case 0
	.short _0202B566 - _0202B55C - 2; case 1
	.short _0202B56E - _0202B55C - 2; case 2
	.short _0202B574 - _0202B55C - 2; case 3
	.short _0202B57A - _0202B55C - 2; case 4
_0202B566:
	mov r1, #0x63
	lsl r1, r1, #0x2
	add r4, r0, r1
	b _0202B57E
_0202B56E:
	add r4, r0, #0x0
	add r4, #0xc
	b _0202B57E
_0202B574:
	add r4, r0, #0x0
	add r4, #0xcc
	b _0202B57E
_0202B57A:
	bl ErrorHandling
_0202B57E:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202B584
FUN_0202B584: ; 0x0202B584
	push {r4, lr}
	mov r4, #0x0
	cmp r1, #0x4
	bhi _0202B5BA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202B598: ; jump table (using 16-bit offset)
	.short _0202B5BA - _0202B598 - 2; case 0
	.short _0202B5B0 - _0202B598 - 2; case 1
	.short _0202B5A2 - _0202B598 - 2; case 2
	.short _0202B5AA - _0202B598 - 2; case 3
	.short _0202B5B6 - _0202B598 - 2; case 4
_0202B5A2:
	mov r1, #0x93
	lsl r1, r1, #0x2
	add r4, r0, r1
	b _0202B5BA
_0202B5AA:
	ldr r1, _0202B5C0 ; =0x000006CC
	add r4, r0, r1
	b _0202B5BA
_0202B5B0:
	ldr r1, _0202B5C4 ; =0x0000090C
	add r4, r0, r1
	b _0202B5BA
_0202B5B6:
	bl ErrorHandling
_0202B5BA:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_0202B5C0: .word 0x000006CC
_0202B5C4: .word 0x0000090C

	thumb_func_start FUN_0202B5C8
FUN_0202B5C8: ; 0x0202B5C8
	ldrb r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202B5CC
FUN_0202B5CC: ; 0x0202B5CC
	ldrb r1, [r0, #0x1]
	cmp r1, #0x3
	bhs _0202B5D6
	add r1, r1, #0x1
	strb r1, [r0, #0x1]
_0202B5D6:
	bx lr

	thumb_func_start FUN_0202B5D8
FUN_0202B5D8: ; 0x0202B5D8
	add r0, #0x8
	bx lr

	thumb_func_start FUN_0202B5DC
FUN_0202B5DC: ; 0x0202B5DC
	push {r4-r7}
	mov r5, #0x0
	add r4, r5, #0x0
	ldr r6, [sp, #0x10]
	cmp r1, #0x0
	ble _0202B616
_0202B5E8:
	ldrb r7, [r0, #0x0]
	cmp r2, r7
	bne _0202B60E
	ldrb r7, [r0, #0x1]
	cmp r3, #0x0
	beq _0202B600
	cmp r7, #0x0
	beq _0202B600
	add r7, r4, #0x1
	strb r7, [r6, r5]
	add r5, r5, #0x1
	b _0202B60E
_0202B600:
	cmp r3, #0x0
	bne _0202B60E
	cmp r7, #0x0
	bne _0202B60E
	add r7, r4, #0x1
	strb r7, [r6, r5]
	add r5, r5, #0x1
_0202B60E:
	add r4, r4, #0x1
	add r0, #0x30
	cmp r4, r1
	blt _0202B5E8
_0202B616:
	add r0, r5, #0x0
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0202B61C
FUN_0202B61C: ; 0x0202B61C
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	mov r5, #0x0
	add r0, r1, #0x0
	add r4, r5, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	ldr r7, [sp, #0x20]
	cmp r0, #0x0
	ble _0202B672
_0202B634:
	ldrb r2, [r6, #0x18]
	ldr r1, [sp, #0x4]
	ldrb r0, [r6, #0x19]
	cmp r1, r2
	bne _0202B668
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	beq _0202B654
	cmp r0, #0x0
	beq _0202B654
	add r0, r4, #0x1
	bl FUN_0202B830
	strb r0, [r7, r5]
	add r5, r5, #0x1
	b _0202B668
_0202B654:
	ldr r1, [sp, #0x8]
	cmp r1, #0x0
	bne _0202B668
	cmp r0, #0x0
	bne _0202B668
	add r0, r4, #0x1
	bl FUN_0202B830
	strb r0, [r7, r5]
	add r5, r5, #0x1
_0202B668:
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r6, #0x48
	cmp r4, r0
	blt _0202B634
_0202B672:
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0202B678
FUN_0202B678: ; 0x0202B678
	push {r3-r5, lr}
	ldr r5, [sp, #0x10]
	ldr r4, [sp, #0x14]
	cmp r1, #0x4
	bhi _0202B702
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0202B68E: ; jump table (using 16-bit offset)
	.short _0202B702 - _0202B68E - 2; case 0
	.short _0202B6DA - _0202B68E - 2; case 1
	.short _0202B698 - _0202B68E - 2; case 2
	.short _0202B6BA - _0202B68E - 2; case 3
	.short _0202B6FE - _0202B68E - 2; case 4
_0202B698:
	cmp r3, #0x0
	str r4, [sp, #0x0]
	beq _0202B6AA
	add r0, #0xc
	mov r1, #0x4
	add r3, r5, #0x0
	bl FUN_0202B5DC
	pop {r3-r5, pc}
_0202B6AA:
	mov r1, #0x93
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r1, #0x10
	add r3, r5, #0x0
	bl FUN_0202B61C
	pop {r3-r5, pc}
_0202B6BA:
	cmp r3, #0x0
	str r4, [sp, #0x0]
	beq _0202B6CC
	add r0, #0xcc
	mov r1, #0x4
	add r3, r5, #0x0
	bl FUN_0202B5DC
	pop {r3-r5, pc}
_0202B6CC:
	ldr r1, _0202B708 ; =0x000006CC
	add r3, r5, #0x0
	add r0, r0, r1
	mov r1, #0x8
	bl FUN_0202B61C
	pop {r3-r5, pc}
_0202B6DA:
	cmp r3, #0x0
	str r4, [sp, #0x0]
	beq _0202B6F0
	mov r1, #0x63
	lsl r1, r1, #0x2
	add r0, r0, r1
	mov r1, #0x4
	add r3, r5, #0x0
	bl FUN_0202B5DC
	pop {r3-r5, pc}
_0202B6F0:
	ldr r1, _0202B70C ; =0x0000090C
	add r3, r5, #0x0
	add r0, r0, r1
	mov r1, #0x8
	bl FUN_0202B61C
	pop {r3-r5, pc}
_0202B6FE:
	mov r0, #0x0
	pop {r3-r5, pc}
_0202B702:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0202B708: .word 0x000006CC
_0202B70C: .word 0x0000090C

	thumb_func_start FUN_0202B710
FUN_0202B710: ; 0x0202B710
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r6, r1, #0x0
	add r5, r2, #0x0
	add r0, sp, #0x8
	mov r1, #0x0
	mov r2, #0x4
	bl MI_CpuFill8
	mov r0, #0x0
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	mov r3, #0x1
	bl FUN_0202B678
	cmp r0, #0x0
	beq _0202B742
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0202B742:
	mov r3, #0x1
	str r3, [sp, #0x0]
	add r0, sp, #0x8
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_0202B678
	cmp r0, #0x0
	beq _0202B79E
	add r0, sp, #0x8
	ldrb r0, [r0, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	beq _0202B798
	add r5, sp, #0x8
_0202B764:
	ldrb r2, [r5, #0x0]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0202B7C8
	ldrb r0, [r0, #0x1]
	cmp r0, #0x3
	blo _0202B77A
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0202B77A:
	add r7, r7, #0x1
	add r5, r5, #0x1
	cmp r7, #0x4
	bge _0202B786
	mov r1, #0x1
	b _0202B788
_0202B786:
	mov r1, #0x0
_0202B788:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0202B792
	mov r0, #0x1
	b _0202B794
_0202B792:
	mov r0, #0x0
_0202B794:
	tst r0, r1
	bne _0202B764
_0202B798:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_0202B79E:
	mov r5, #0x1
_0202B7A0:
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_0202B7C8
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202B7B6
	ldrb r0, [r0, #0x1]
	cmp r0, #0x3
	blo _0202B7BC
_0202B7B6:
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0202B7BC:
	add r5, r5, #0x1
	cmp r5, #0x4
	ble _0202B7A0
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0202B7C8
FUN_0202B7C8: ; 0x0202B7C8
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r1, #0x0
	bl FUN_0202B820
	cmp r0, #0x1
	beq _0202B7DE
	bl ErrorHandling
_0202B7DE:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0202B548
	mov r1, #0x80
	bic r4, r1
	sub r2, r4, #0x1
	mov r1, #0x30
	mul r1, r2
	add r0, r0, r1
	pop {r4-r6, pc}

	thumb_func_start FUN_0202B7F4
FUN_0202B7F4: ; 0x0202B7F4
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r6, r1, #0x0
	bl FUN_0202B820
	cmp r0, #0x0
	beq _0202B80A
	bl ErrorHandling
_0202B80A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0202B584
	mov r1, #0x80
	bic r4, r1
	sub r2, r4, #0x1
	mov r1, #0x48
	mul r1, r2
	add r0, r0, r1
	pop {r4-r6, pc}

	thumb_func_start FUN_0202B820
FUN_0202B820: ; 0x0202B820
	mov r1, #0x80
	tst r0, r1
	bne _0202B82A
	mov r0, #0x1
	bx lr
_0202B82A:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202B830
FUN_0202B830: ; 0x0202B830
	mov r1, #0x80
	orr r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_0202B838
FUN_0202B838: ; 0x0202B838
	ldr r1, _0202B840 ; =0x00000B4C
	add r0, r0, r1
	bx lr
	nop
_0202B840: .word 0x00000B4C

	thumb_func_start FUN_0202B844
FUN_0202B844: ; 0x0202B844
	ldr r1, _0202B84C ; =0x00000B56
	add r0, r0, r1
	bx lr
	nop
_0202B84C: .word 0x00000B56

	thumb_func_start FUN_0202B850
FUN_0202B850: ; 0x0202B850
	ldr r1, _0202B858 ; =0x00000B7A
	add r0, r0, r1
	bx lr
	nop
_0202B858: .word 0x00000B7A

	thumb_func_start FUN_0202B85C
FUN_0202B85C: ; 0x0202B85C
	ldr r1, _0202B864 ; =0x00000B7C
	add r0, r0, r1
	bx lr
	nop
_0202B864: .word 0x00000B7C

	thumb_func_start FUN_0202B868
FUN_0202B868: ; 0x0202B868
	mov r1, #0x2e
	lsl r1, r1, #0x6
	add r0, r0, r1
	bx lr

	thumb_func_start FUN_0202B870
FUN_0202B870: ; 0x0202B870
	lsl r1, r0, #0x1
	ldr r0, _0202B878 ; =0x020EEAC8
	ldrb r0, [r0, r1]
	bx lr
	.balign 4
_0202B878: .word 0x020EEAC8

	thumb_func_start FUN_0202B87C
FUN_0202B87C: ; 0x0202B87C
	lsl r1, r0, #0x1
	ldr r0, _0202B884 ; =0x020EEAC9
	ldrb r0, [r0, r1]
	bx lr
	.balign 4
_0202B884: .word 0x020EEAC9

	thumb_func_start FUN_0202B888
FUN_0202B888: ; 0x0202B888
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	ldr r3, _0202B898 ; =StringFillEOS
	add r0, #0x8
	mov r1, #0x8
	bx r3
	nop
_0202B898: .word StringFillEOS

	thumb_func_start FUN_0202B89C
FUN_0202B89C: ; 0x0202B89C
	push {r3, lr}
	add r0, #0x8
	bl StringLength
	cmp r0, #0x0
	beq _0202B8AC
	mov r0, #0x1
	pop {r3, pc}
_0202B8AC:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0202B8B0
FUN_0202B8B0: ; 0x0202B8B0
	mov r0, #0xea
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start FUN_0202B8B8
FUN_0202B8B8: ; 0x0202B8B8
	push {r3-r7, lr}
	mov r2, #0xea
	mov r1, #0x0
	lsl r2, r2, #0x4
	add r6, r0, #0x0
	bl MI_CpuFill8
	mov r7, #0x0
_0202B8C8:
	mov r4, #0x0
	add r5, r6, #0x0
_0202B8CC:
	add r0, r5, #0x0
	bl FUN_0202B888
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, #0x6
	blt _0202B8CC
	add r7, r7, #0x1
	add r6, #0x90
	cmp r7, #0x1a
	blt _0202B8C8
	pop {r3-r7, pc}

	thumb_func_start FUN_0202B8E4
FUN_0202B8E4: ; 0x0202B8E4
	ldr r3, _0202B8EC ; =FUN_02022610
	mov r1, #0x1c
	bx r3
	nop
_0202B8EC: .word FUN_02022610

	thumb_func_start FUN_0202B8F0
FUN_0202B8F0: ; 0x0202B8F0
	push {r4-r6, lr}
	cmp r2, #0x6
	blo _0202B8FE
	blo _0202B930
	bl ErrorHandling
	pop {r4-r6, pc}
_0202B8FE:
	mov r3, #0x90
	mul r3, r1
	add r3, r0, r3
	cmp r2, #0x5
	bge _0202B928
	mov r0, #0x18
	mul r0, r2
	add r6, r3, r0
_0202B90E:
	add r5, r6, #0x0
	add r5, #0x18
	add r4, r6, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	add r2, r2, #0x1
	add r6, #0x18
	stmia r4!, {r0-r1}
	cmp r2, #0x5
	blt _0202B90E
_0202B928:
	add r3, #0x78
	add r0, r3, #0x0
	bl FUN_0202B888
_0202B930:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202B934
FUN_0202B934: ; 0x0202B934
	mov r0, #0x4e
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0202B93C
FUN_0202B93C: ; 0x0202B93C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	bl FUN_02029FC8
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x34
	bl FUN_020169D8
	str r0, [sp, #0x4]
	add r5, r0, #0x0
	ldr r0, _0202B9E8 ; =0x020EEAD0
	mov r6, #0x0
	str r0, [sp, #0x0]
_0202B95A:
	cmp r6, #0x5
	beq _0202B968
	cmp r6, #0xa
	beq _0202B988
	cmp r6, #0xb
	beq _0202B9A0
	b _0202B9C8
_0202B968:
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_0202A150
	add r7, r0, #0x0
	beq _0202B984
	add r0, r4, #0x0
	mov r1, #0x1d
	bl FUN_0202A150
	add r1, r7, #0x0
	bl _u32_div_f
	add r7, r0, #0x0
_0202B984:
	str r7, [r5, #0x0]
	b _0202B9D4
_0202B988:
	add r0, r4, #0x0
	mov r1, #0x41
	bl FUN_0202A150
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x42
	bl FUN_0202A150
	add r0, r7, r0
	str r0, [r5, #0x0]
	b _0202B9D4
_0202B9A0:
	add r0, r4, #0x0
	mov r1, #0x3f
	bl FUN_0202A150
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x40
	bl FUN_0202A150
	add r1, r7, r0
	beq _0202B9C4
	ldr r0, [sp, #0x4]
	ldr r2, [r0, #0x28]
	mov r0, #0x64
	mul r0, r2
	bl _u32_div_f
	add r1, r0, #0x0
_0202B9C4:
	str r1, [r5, #0x0]
	b _0202B9D4
_0202B9C8:
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_0202A150
	str r0, [r5, #0x0]
_0202B9D4:
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r0, #0x4
	add r5, r5, #0x4
	str r0, [sp, #0x0]
	cmp r6, #0xd
	blt _0202B95A
	ldr r0, [sp, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0202B9E8: .word 0x020EEAD0

	thumb_func_start FUN_0202B9EC
FUN_0202B9EC: ; 0x0202B9EC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020238F4
	mov r1, #0x4e
	add r6, r0, #0x0
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl FUN_020169D8
	mov r2, #0x4e
	mov r1, #0x0
	lsl r2, r2, #0x2
	str r0, [sp, #0x4]
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl FUN_0202881C
	mov r1, #0x1
	bl FUN_0202877C
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020239A0
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202B93C
	ldr r4, [sp, #0x4]
	str r0, [sp, #0x0]
	mov r6, #0x0
	add r5, r0, #0x0
_0202BA38:
	ldr r0, [sp, #0x8]
	add r1, r4, #0x0
	str r0, [r4, #0x0]
	add r0, r7, #0x0
	add r1, #0x8
	mov r2, #0x8
	bl FUN_02021EF0
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	str r0, [r4, #0x4]
	add r4, #0x18
	add r5, r5, #0x4
	cmp r6, #0xd
	blt _0202BA38
	ldr r0, [sp, #0x0]
	bl FUN_02016A18
	add r0, r7, #0x0
	bl FUN_02021A20
	ldr r0, [sp, #0x4]
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BA68
FUN_0202BA68: ; 0x0202BA68
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_0202BA6E:
	add r0, r5, #0x0
	bl FUN_0202B888
	add r4, r4, #0x1
	add r5, #0x18
	cmp r4, #0x6
	blt _0202BA6E
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202BA80
FUN_0202BA80: ; 0x0202BA80
	push {r3, lr}
	ldr r3, [r0, #0x0]
	ldr r2, [r1, #0x0]
	cmp r3, r2
	beq _0202BA8E
	mov r0, #0x0
	pop {r3, pc}
_0202BA8E:
	add r0, #0x8
	add r1, #0x8
	bl StringNotEqual
	cmp r0, #0x0
	bne _0202BA9E
	mov r0, #0x1
	pop {r3, pc}
_0202BA9E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202BAA4
FUN_0202BAA4: ; 0x0202BAA4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x4]
	add r7, r1, #0x0
	mov r4, #0x0
	cmp r0, #0x0
	ble _0202BACE
	add r5, r6, #0x0
_0202BAB4:
	ldr r0, [r5, #0xc]
	add r1, r7, #0x0
	bl FUN_0202BA80
	cmp r0, #0x0
	beq _0202BAC4
	mov r0, #0x1
	pop {r3-r7, pc}
_0202BAC4:
	ldr r0, [r6, #0x4]
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r0
	blt _0202BAB4
_0202BACE:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202BAD4
FUN_0202BAD4: ; 0x0202BAD4
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r1, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x0]
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0xe0
	add r4, r3, #0x0
	bl MI_CpuFill8
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	cmp r0, #0x0
	bne _0202BB64
	mov r2, #0x90
	add r0, r4, #0x0
	mul r0, r2
	add r1, r6, #0x0
	add r0, r5, r0
	add r1, #0x50
	str r0, [sp, #0x8]
	bl MI_CpuCopy8
	add r1, sp, #0x10
	ldrb r3, [r1, #0x18]
	mov r0, #0x0
	cmp r3, #0x0
	ble _0202BB2E
	mov r2, #0x18
	ldr r1, [sp, #0x24]
	mul r2, r4
_0202BB14:
	ldr r5, [r6, #0x4]
	add r0, r0, #0x1
	add r4, r5, #0x0
	add r4, r4, #0x1
	str r4, [r6, #0x4]
	ldr r4, [r1, #0x0]
	lsl r5, r5, #0x2
	add r4, r4, r2
	add r5, r6, r5
	str r4, [r5, #0xc]
	add r1, r1, #0x4
	cmp r0, r3
	blt _0202BB14
_0202BB2E:
	add r4, r6, #0x0
	add r4, #0x50
	mov r7, #0x0
	add r5, r4, #0x0
_0202BB36:
	add r0, r4, #0x0
	bl FUN_0202B89C
	cmp r0, #0x0
	beq _0202BB58
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0202BAA4
	cmp r0, #0x0
	bne _0202BB58
	ldr r1, [r6, #0x0]
	add r0, r1, #0x1
	str r0, [r6, #0x0]
	lsl r0, r1, #0x2
	add r0, r6, r0
	str r4, [r0, #0x38]
_0202BB58:
	add r7, r7, #0x1
	add r4, #0x18
	add r5, #0x18
	cmp r7, #0x6
	blt _0202BB36
	b _0202BBF8
_0202BB64:
	add r0, r4, #0x0
	add r0, #0xd
	mov r2, #0x90
	add r1, r0, #0x0
	mul r1, r2
	add r0, r5, r1
	add r1, r6, #0x0
	add r1, #0x50
	str r0, [sp, #0x8]
	bl MI_CpuCopy8
	add r0, sp, #0x10
	ldrb r2, [r0, #0x18]
	mov r3, #0x0
	cmp r2, #0x0
	ble _0202BBB2
	mov r1, #0x18
	ldr r0, [sp, #0x24]
	mul r1, r4
_0202BB8A:
	ldr r4, [r0, #0x0]
	ldr r5, [r1, r4]
	cmp r5, #0x0
	beq _0202BBAA
	ldr r4, [sp, #0x0]
	cmp r4, r5
	bne _0202BBAA
	ldr r5, [r6, #0x4]
	add r4, r5, #0x0
	add r4, r4, #0x1
	str r4, [r6, #0x4]
	ldr r4, [r0, #0x0]
	lsl r5, r5, #0x2
	add r4, r4, r1
	add r5, r6, r5
	str r4, [r5, #0xc]
_0202BBAA:
	add r3, r3, #0x1
	add r0, r0, #0x4
	cmp r3, r2
	blt _0202BB8A
_0202BBB2:
	add r4, r6, #0x0
	mov r0, #0x0
	add r4, #0x50
	str r0, [sp, #0x4]
	add r5, r6, #0x0
	add r7, r4, #0x0
_0202BBBE:
	add r0, r4, #0x0
	bl FUN_0202B89C
	cmp r0, #0x0
	beq _0202BBE8
	ldr r1, [r5, #0x50]
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _0202BBE8
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_0202BAA4
	cmp r0, #0x0
	bne _0202BBE8
	ldr r1, [r6, #0x0]
	add r0, r1, #0x1
	str r0, [r6, #0x0]
	lsl r0, r1, #0x2
	add r0, r6, r0
	str r4, [r0, #0x38]
_0202BBE8:
	ldr r0, [sp, #0x4]
	add r4, #0x18
	add r0, r0, #0x1
	add r5, #0x18
	add r7, #0x18
	str r0, [sp, #0x4]
	cmp r0, #0x6
	blt _0202BBBE
_0202BBF8:
	ldr r1, [r6, #0x4]
	ldr r0, [r6, #0x0]
	mov r2, #0x0
	add r0, r1, r0
	str r0, [r6, #0x8]
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	ble _0202BC20
	add r1, r6, #0x0
_0202BC0A:
	ldr r3, [r6, #0x4]
	ldr r0, [r1, #0x38]
	add r3, r2, r3
	lsl r3, r3, #0x2
	add r3, r6, r3
	str r0, [r3, #0xc]
	ldr r0, [r6, #0x0]
	add r2, r2, #0x1
	add r1, r1, #0x4
	cmp r2, r0
	blt _0202BC0A
_0202BC20:
	mov r0, #0x0
	mov r12, r0
	ldr r0, [r6, #0x8]
	sub r5, r0, #0x1
	cmp r5, #0x0
	ble _0202BC64
	add r3, r6, #0x0
_0202BC2E:
	mov r0, r12
	cmp r5, r0
	ble _0202BC52
	lsl r0, r5, #0x2
	add r4, r6, r0
_0202BC38:
	ldr r2, [r4, #0xc]
	ldr r7, [r3, #0xc]
	ldr r0, [r2, #0x4]
	ldr r1, [r7, #0x4]
	cmp r1, r0
	bhs _0202BC48
	str r2, [r3, #0xc]
	str r7, [r4, #0xc]
_0202BC48:
	sub r5, r5, #0x1
	mov r0, r12
	sub r4, r4, #0x4
	cmp r5, r0
	bgt _0202BC38
_0202BC52:
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	ldr r0, [r6, #0x8]
	add r3, r3, #0x4
	sub r5, r0, #0x1
	mov r0, r12
	cmp r0, r5
	blt _0202BC2E
_0202BC64:
	ldr r0, [sp, #0x8]
	bl FUN_0202BA68
	mov r3, #0x0
	add r2, r6, #0x0
	b _0202BC8A
_0202BC70:
	ldr r5, [r2, #0xc]
	ldr r4, [sp, #0x8]
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [sp, #0x8]
	add r2, r2, #0x4
	add r0, #0x18
	str r0, [sp, #0x8]
	add r3, r3, #0x1
_0202BC8A:
	cmp r3, #0x6
	bge _0202BC94
	ldr r0, [r6, #0x8]
	cmp r3, r0
	blt _0202BC70
_0202BC94:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BC98
FUN_0202BC98: ; 0x0202BC98
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r0, #0x0
	add r5, r1, #0x0
	ldr r0, [sp, #0x2c]
	mov r1, #0xe0
	str r2, [sp, #0x10]
	add r4, r3, #0x0
	bl FUN_020169D8
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	add r0, sp, #0x18
	ldrb r0, [r0, #0x10]
	add r1, r6, #0x0
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_0202BAD4
	cmp r5, #0x0
	beq _0202BCEA
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	add r0, sp, #0x18
	ldrb r0, [r0, #0x10]
	add r1, r6, #0x0
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x2c]
	str r0, [sp, #0xc]
	ldr r3, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_0202BAD4
_0202BCEA:
	add r0, r6, #0x0
	bl FUN_02016A18
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BCF4
FUN_0202BCF4: ; 0x0202BCF4
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r1, #0x0
	ldr r1, [sp, #0x38]
	add r4, r0, #0x0
	add r5, r2, #0x0
	add r7, r3, #0x0
	str r1, [sp, #0x38]
	bl FUN_0202B8E4
	str r0, [sp, #0x8]
	add r0, r4, #0x0
	bl FUN_0202881C
	mov r1, #0x1
	bl FUN_0202877C
	mov r4, #0x0
	add r3, r4, #0x0
	str r0, [sp, #0xc]
	cmp r5, #0x0
	bls _0202BD44
_0202BD20:
	cmp r3, r6
	beq _0202BD3A
	lsl r0, r3, #0x2
	ldr r2, [r7, r0]
	cmp r2, #0x0
	beq _0202BD3A
	add r1, r4, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	lsl r1, r0, #0x2
	add r0, sp, #0x10
	str r2, [r0, r1]
_0202BD3A:
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, r5
	blo _0202BD20
_0202BD44:
	cmp r4, #0x0
	beq _0202BD68
	mov r5, #0x0
	add r6, sp, #0x10
_0202BD4C:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add r2, r5, #0x0
	add r3, r6, #0x0
	bl FUN_0202BC98
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0xd
	blo _0202BD4C
_0202BD68:
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_0202BD6C
FUN_0202BD6C: ; 0x0202BD6C
	push {r3-r7, lr}
	sub sp, #0x10
	str r2, [sp, #0x0]
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020238F4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r1, #0x4c
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x4c
	add r7, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl FUN_0202881C
	mov r1, #0x1
	bl FUN_0202877C
	str r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_0202B93C
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0202B870
	str r0, [r7, #0x0]
	add r0, r5, #0x0
	bl FUN_0202B87C
	ldr r1, [r7, #0x0]
	mov r6, #0x0
	cmp r1, #0x0
	ble _0202BDE2
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x8]
	add r4, r7, #0x0
	add r5, r0, r1
_0202BDC4:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	bl FUN_020239A0
	str r0, [r4, #0xc]
	ldr r0, [r7, #0x0]
	add r6, r6, #0x1
	add r4, #0xc
	add r5, r5, #0x4
	cmp r6, r0
	blt _0202BDC4
_0202BDE2:
	ldr r0, [sp, #0x8]
	bl FUN_02016A18
	add r0, r7, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202BDF0
FUN_0202BDF0: ; 0x0202BDF0
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	add r0, r7, #0x0
	mov r1, #0x4c
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x4c
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	mov r1, #0x90
	mul r1, r0
	mov r6, #0x0
	add r5, r5, r1
_0202BE14:
	add r0, r5, #0x0
	bl FUN_0202B89C
	cmp r0, #0x0
	beq _0202BE60
	ldr r2, [r4, #0x0]
	mov r1, #0xc
	mul r1, r2
	ldr r0, [r5, #0x0]
	add r1, r4, r1
	str r0, [r1, #0x4]
	ldr r2, [r4, #0x0]
	mov r1, #0xc
	mul r1, r2
	ldr r0, [r5, #0x4]
	add r1, r4, r1
	str r0, [r1, #0x8]
	mov r0, #0x8
	add r1, r7, #0x0
	bl FUN_020219F4
	ldr r2, [r4, #0x0]
	mov r1, #0xc
	mul r1, r2
	add r1, r4, r1
	str r0, [r1, #0xc]
	ldr r1, [r4, #0x0]
	mov r0, #0xc
	mul r0, r1
	add r0, r4, r0
	add r1, r5, #0x0
	ldr r0, [r0, #0xc]
	add r1, #0x8
	bl FUN_02021E28
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_0202BE60:
	add r6, r6, #0x1
	add r5, #0x18
	cmp r6, #0x6
	blt _0202BE14
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0202BE6C
FUN_0202BE6C: ; 0x0202BE6C
	push {r4-r6, lr}
	add r6, r0, #0x0
	mov r4, #0x0
	add r5, r6, #0x0
_0202BE74:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	beq _0202BE7E
	bl FUN_02021A20
_0202BE7E:
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, #0x6
	blt _0202BE74
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0x4c
	bl MI_CpuFill8
	add r0, r6, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}

	thumb_func_start FUN_0202BE98
FUN_0202BE98: ; 0x0202BE98
	ldr r0, _0202BE9C ; =0x00000688
	bx lr
	.balign 4
_0202BE9C: .word 0x00000688

	thumb_func_start FUN_0202BEA0
FUN_0202BEA0: ; 0x0202BEA0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r2, _0202BED8 ; =0x00000688
	mov r0, #0x0
	add r1, r5, #0x0
	bl MIi_CpuClearFast
	mov r4, #0x0
	mov r6, #0xab
	add r7, r4, #0x0
_0202BEB4:
	add r0, r5, #0x0
	bl FUN_02066978
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0202BECC
	bl ErrorHandling
_0202BECC:
	add r4, r4, #0x1
	add r5, #0xec
	cmp r4, #0x6
	blt _0202BEB4
	pop {r3-r7, pc}
	nop
_0202BED8: .word 0x00000688

	thumb_func_start FUN_0202BEDC
FUN_0202BEDC: ; 0x0202BEDC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r2, _0202BF14 ; =0x00000588
	mov r0, #0x0
	add r1, r5, #0x0
	bl MIi_CpuClearFast
	mov r4, #0x0
	mov r6, #0xab
	add r7, r4, #0x0
_0202BEF0:
	add r0, r5, #0x0
	bl FUN_02066978
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0202BF08
	bl ErrorHandling
_0202BF08:
	add r4, r4, #0x1
	add r5, #0xec
	cmp r4, #0x6
	blt _0202BEF0
	pop {r3-r7, pc}
	nop
_0202BF14: .word 0x00000588

	thumb_func_start FUN_0202BF18
FUN_0202BF18: ; 0x0202BF18
	push {r4-r7}
	add r2, r0, #0x0
	ldr r3, _0202BF70 ; =0x00000588
	mov r0, #0x0
	add r5, r2, #0x0
_0202BF22:
	ldr r4, [r5, r3]
	cmp r1, r4
	beq _0202BF6C
	add r0, r0, #0x1
	add r5, r5, #0x4
	cmp r0, #0x14
	blt _0202BF22
	ldr r1, _0202BF70 ; =0x00000588
	mov r0, #0x0
	add r4, r2, #0x0
_0202BF36:
	ldr r3, [r4, r1]
	cmp r3, #0x0
	beq _0202BF6C
	add r0, r0, #0x1
	add r4, r4, #0x4
	cmp r0, #0x14
	blt _0202BF36
	mov r3, #0x0
	ldr r4, _0202BF74 ; =0x7FFFFFFF
	add r5, r3, #0x0
_0202BF4A:
	ldr r0, _0202BF78 ; =0x000005D8
	ldr r1, [r2, r0]
	add r0, r0, #0x4
	ldr r0, [r2, r0]
	sub r6, r1, r4
	mov r12, r0
	mov r6, r12
	sbc r6, r3
	bge _0202BF62
	add r4, r1, #0x0
	add r3, r0, #0x0
	add r7, r5, #0x0
_0202BF62:
	add r5, r5, #0x1
	add r2, #0x8
	cmp r5, #0x14
	blt _0202BF4A
	add r0, r7, #0x0
_0202BF6C:
	pop {r4-r7}
	bx lr
	.balign 4
_0202BF70: .word 0x00000588
_0202BF74: .word 0x7FFFFFFF
_0202BF78: .word 0x000005D8

	thumb_func_start FUN_0202BF7C
FUN_0202BF7C: ; 0x0202BF7C
	add r3, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0xec
	mul r1, r2
	add r1, r3, r1
	ldr r3, _0202BF8C ; =FUN_02069A64
	bx r3
	nop
_0202BF8C: .word FUN_02069A64

	thumb_func_start FUN_0202BF90
FUN_0202BF90: ; 0x0202BF90
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0202BF18
	add r6, r0, #0x0
	lsl r0, r6, #0x2
	add r1, r5, r0
	ldr r0, _0202BFCC ; =0x00000588
	str r4, [r1, r0]
	bl FUN_020126FC
	lsl r2, r6, #0x3
	add r3, r5, r2
	ldr r2, _0202BFD0 ; =0x000005D8
	str r0, [r3, r2]
	add r0, r2, #0x4
	str r1, [r3, r0]
	bl OS_GetOwnerRtcOffset
	ldr r2, _0202BFD4 ; =0x00000678
	str r0, [r5, r2]
	add r0, r2, #0x4
	add r2, #0x8
	str r1, [r5, r0]
	add r0, r5, r2
	bl OS_GetMacAddress
	pop {r4-r6, pc}
	nop
_0202BFCC: .word 0x00000588
_0202BFD0: .word 0x000005D8
_0202BFD4: .word 0x00000678

	thumb_func_start FUN_0202BFD8
FUN_0202BFD8: ; 0x0202BFD8
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, r2, #0x0
	cmp r5, #0x6
	blt _0202BFE8
	bl ErrorHandling
_0202BFE8:
	mov r0, #0xec
	mul r0, r5
	add r3, r6, r0
	mov r2, #0x1d
_0202BFF0:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202BFF0
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202C000
FUN_0202C000: ; 0x0202C000
	push {r3-r7, lr}
	mov r4, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	mov r7, #0xab
_0202C00A:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	beq _0202C01A
	add r4, r4, #0x1
_0202C01A:
	add r6, r6, #0x1
	add r5, #0xec
	cmp r6, #0x6
	blt _0202C00A
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202C028
FUN_0202C028: ; 0x0202C028
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020126FC
	ldr r1, _0202C058 ; =0x00000588
	mov r3, #0x0
	add r6, r5, #0x0
_0202C038:
	ldr r2, [r6, r1]
	cmp r4, r2
	bne _0202C04A
	lsl r1, r3, #0x3
	add r2, r5, r1
	ldr r1, _0202C05C ; =0x000005D8
	ldr r1, [r2, r1]
	sub r0, r0, r1
	pop {r4-r6, pc}
_0202C04A:
	add r3, r3, #0x1
	add r6, r6, #0x4
	cmp r3, #0x14
	blt _0202C038
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0202C058: .word 0x00000588
_0202C05C: .word 0x000005D8

	thumb_func_start FUN_0202C060
FUN_0202C060: ; 0x0202C060
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl OS_GetMacAddress
	mov r0, #0x1a
	mov r3, #0x0
	add r5, sp, #0x0
	lsl r0, r0, #0x6
_0202C074:
	add r1, r4, r3
	ldrb r2, [r5, #0x0]
	ldrb r1, [r1, r0]
	cmp r2, r1
	beq _0202C084
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0202C084:
	add r3, r3, #0x1
	add r5, r5, #0x1
	cmp r3, #0x6
	blt _0202C074
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202C094
FUN_0202C094: ; 0x0202C094
	push {r4, lr}
	add r4, r0, #0x0
	bl OS_GetOwnerRtcOffset
	ldr r2, _0202C0B4 ; =0x00000678
	ldr r3, [r4, r2]
	add r2, r2, #0x4
	ldr r2, [r4, r2]
	eor r0, r3
	eor r1, r2
	orr r0, r1
	bne _0202C0B0
	mov r0, #0x1
	pop {r4, pc}
_0202C0B0:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0202C0B4: .word 0x00000678

	thumb_func_start FUN_0202C0B8
FUN_0202C0B8: ; 0x0202C0B8
	push {r3-r4}
	mov r4, #0x0
	mov r1, #0x1a
	add r3, r4, #0x0
	lsl r1, r1, #0x6
_0202C0C2:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	add r3, r3, #0x1
	orr r4, r2
	cmp r3, #0x6
	blt _0202C0C2
	cmp r4, #0x0
	bne _0202C0D8
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0202C0D8:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0202C0E0
FUN_0202C0E0: ; 0x0202C0E0
	mov r0, #0x28
	bx lr

	thumb_func_start FUN_0202C0E4
FUN_0202C0E4: ; 0x0202C0E4
	push {r4-r5}
	mov r4, #0x0
	add r1, r4, #0x0
	add r2, r4, #0x0
_0202C0EC:
	add r3, r2, #0x0
	add r5, r0, #0x0
_0202C0F0:
	add r3, r3, #0x1
	strh r1, [r5, #0x0]
	add r5, r5, #0x2
	cmp r3, #0x4
	blt _0202C0F0
	add r4, r4, #0x1
	add r0, #0x8
	cmp r4, #0x5
	blt _0202C0EC
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_0202C108
FUN_0202C108: ; 0x0202C108
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x21
	add r4, r2, #0x0
	bl FUN_02022610
	lsl r1, r5, #0x3
	add r3, r0, r1
	lsl r2, r4, #0x1
	ldrh r1, [r3, r2]
	ldr r0, _0202C128 ; =0x0000270F
	cmp r1, r0
	bhs _0202C126
	add r0, r1, #0x1
	strh r0, [r3, r2]
_0202C126:
	pop {r3-r5, pc}
	.balign 4
_0202C128: .word 0x0000270F

	thumb_func_start FUN_0202C12C
FUN_0202C12C: ; 0x0202C12C
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0x21
	add r4, r2, #0x0
	bl FUN_02022610
	lsl r2, r5, #0x3
	lsl r1, r4, #0x1
	add r0, r0, r2
	ldrh r0, [r1, r0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202C144
FUN_0202C144: ; 0x0202C144
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _0202C194
	add r0, r5, #0x0
	bl FUN_02024DA0
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02029FC8
	add r7, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r2, r0, #0x0
	lsl r2, r2, #0x10
	add r0, r7, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x10
	bl FUN_0202A1C4
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02024AF0
	add r0, r5, #0x0
	bl FUN_0204C1A8
	add r1, r4, #0x0
	bl FUN_0204C104
_0202C194:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202C198
FUN_0202C198: ; 0x0202C198
	ldr r1, _0202C1A4 ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202C1A8 ; =0x00001310
	str r0, [r2, r1]
	bx lr
	nop
_0202C1A4: .word 0x021C59D8
_0202C1A8: .word 0x00001310

	thumb_func_start FUN_0202C1AC
FUN_0202C1AC: ; 0x0202C1AC
	ldr r1, _0202C1C0 ; =0x021C59D8
	ldr r3, [r1, #0x4]
	ldr r1, _0202C1C4 ; =0x00001310
	ldr r2, [r3, r1]
	sub r2, #0x9
	cmp r2, #0x1
	bls _0202C1BE
	add r1, #0x20
	str r0, [r3, r1]
_0202C1BE:
	bx lr
	.balign 4
_0202C1C0: .word 0x021C59D8
_0202C1C4: .word 0x00001310

	thumb_func_start FUN_0202C1C8
FUN_0202C1C8: ; 0x0202C1C8
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r1, _0202C1F0 ; =0x021C59D8
	ldr r0, _0202C1F4 ; =FUN_0202C1F8
	ldr r1, [r1, #0x4]
	bl WM_SetParentParameter
	cmp r0, #0x2
	beq _0202C1EC
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3, pc}
_0202C1EC:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C1F0: .word 0x021C59D8
_0202C1F4: .word FUN_0202C1F8

	thumb_func_start FUN_0202C1F8
FUN_0202C1F8: ; 0x0202C1F8
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C20C
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r3, pc}
_0202C20C:
	bl FUN_0202C21C
	cmp r0, #0x0
	bne _0202C21A
	mov r0, #0x9
	bl FUN_0202C198
_0202C21A:
	pop {r3, pc}

	thumb_func_start FUN_0202C21C
FUN_0202C21C: ; 0x0202C21C
	push {r4, lr}
	ldr r0, _0202C278 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C27C ; =0x00001310
	ldr r0, [r1, r0]
	sub r0, r0, #0x4
	cmp r0, #0x2
	bhi _0202C230
	mov r0, #0x1
	pop {r4, pc}
_0202C230:
	bl WMi_GetStatusAddress
	add r4, r0, #0x0
	mov r0, #0x66
	lsl r0, r0, #0x2
	add r0, r4, r0
	mov r1, #0x4
	bl DC_InvalidateRange
	mov r0, #0x66
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r4, r0
	mov r1, #0x4
	bl DC_FlushRange
	ldr r0, _0202C280 ; =FUN_0202C288
	bl WM_StartParent
	cmp r0, #0x2
	beq _0202C264
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r4, pc}
_0202C264:
	ldr r2, _0202C278 ; =0x021C59D8
	ldr r1, _0202C284 ; =0x0000132C
	ldr r0, [r2, #0x4]
	mov r3, #0x0
	strh r3, [r0, r1]
	ldr r2, [r2, #0x4]
	mov r0, #0x1
	add r1, r1, #0x2
	strh r0, [r2, r1]
	pop {r4, pc}
	.balign 4
_0202C278: .word 0x021C59D8
_0202C27C: .word 0x00001310
_0202C280: .word FUN_0202C288
_0202C284: .word 0x0000132C

	thumb_func_start FUN_0202C288
FUN_0202C288: ; 0x0202C288
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x10]
	mov r1, #0x1
	lsl r1, r0
	lsl r0, r1, #0x10
	lsr r4, r0, #0x10
	ldrh r0, [r5, #0x2]
	cmp r0, #0x0
	beq _0202C2A8
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4-r6, pc}
_0202C2A8:
	ldrh r0, [r5, #0x8]
	cmp r0, #0x7
	bgt _0202C2C0
	bge _0202C2DA
	cmp r0, #0x2
	bgt _0202C378
	cmp r0, #0x0
	blt _0202C378
	beq _0202C36A
	cmp r0, #0x2
	beq _0202C2CC
	pop {r4-r6, pc}
_0202C2C0:
	cmp r0, #0x9
	bgt _0202C2C8
	beq _0202C34C
	pop {r4-r6, pc}
_0202C2C8:
	cmp r0, #0x1a
	pop {r4-r6, pc}
_0202C2CC:
	ldr r0, _0202C37C ; =0x021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C380 ; =0x00001345
	ldrb r1, [r2, r0]
	add r1, r1, #0x1
	strb r1, [r2, r0]
	pop {r4-r6, pc}
_0202C2DA:
	ldr r0, _0202C37C ; =0x021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C384 ; =0x00001343
	ldrb r1, [r2, r0]
	cmp r1, #0x1
	beq _0202C318
	sub r0, r0, #0x1
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	beq _0202C318
	bl FUN_0202CBA0
	ldr r1, _0202C37C ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202C388 ; =0x00001334
	ldrb r1, [r2, r1]
	cmp r0, r1
	bge _0202C318
	bl FUN_02033534
	ldrb r1, [r5, #0x14]
	cmp r1, r0
	bne _0202C318
	add r1, r5, #0x0
	ldr r0, _0202C38C ; =0x02105D54
	add r1, #0x15
	mov r2, #0x3
	bl memcmp
	cmp r0, #0x0
	beq _0202C330
_0202C318:
	ldrh r1, [r5, #0x10]
	mov r0, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	beq _0202C378
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4-r6, pc}
_0202C330:
	ldr r1, _0202C37C ; =0x021C59D8
	ldr r0, _0202C390 ; =0x0000132E
	ldr r3, [r1, #0x4]
	ldrh r2, [r3, r0]
	orr r2, r4
	strh r2, [r3, r0]
	ldr r1, [r1, #0x4]
	sub r0, r0, #0x6
	ldr r1, [r1, r0]
	cmp r1, #0x0
	beq _0202C378
	ldrh r0, [r5, #0x10]
	blx r1
	pop {r4-r6, pc}
_0202C34C:
	ldr r2, _0202C37C ; =0x021C59D8
	ldr r1, _0202C390 ; =0x0000132E
	ldr r0, [r2, #0x4]
	mvn r3, r4
	ldrh r6, [r0, r1]
	and r3, r6
	strh r3, [r0, r1]
	ldr r0, [r2, #0x4]
	sub r1, #0xa
	ldr r1, [r0, r1]
	cmp r1, #0x0
	beq _0202C378
	ldrh r0, [r5, #0x10]
	blx r1
	pop {r4-r6, pc}
_0202C36A:
	bl FUN_0202C394
	cmp r0, #0x0
	bne _0202C378
	mov r0, #0x9
	bl FUN_0202C198
_0202C378:
	pop {r4-r6, pc}
	nop
_0202C37C: .word 0x021C59D8
_0202C380: .word 0x00001345
_0202C384: .word 0x00001343
_0202C388: .word 0x00001334
_0202C38C: .word 0x02105D54
_0202C390: .word 0x0000132E

	thumb_func_start FUN_0202C394
FUN_0202C394: ; 0x0202C394
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _0202C3F0 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C3F4 ; =0x00001310
	ldr r0, [r1, r0]
	sub r0, r0, #0x4
	cmp r0, #0x2
	bhi _0202C3AC
	add sp, #0x8
	mov r0, #0x1
	pop {r4, pc}
_0202C3AC:
	mov r0, #0x4
	bl FUN_0202C198
	ldr r0, _0202C3F0 ; =0x021C59D8
	ldr r2, _0202C3F8 ; =0x00001304
	ldr r4, [r0, #0x4]
	ldr r3, _0202C3FC ; =0x00001020
	ldr r0, [r4, r2]
	add r2, r2, #0x4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r2, [r4, r2]
	add r1, r4, r3
	lsl r2, r2, #0x10
	sub r3, #0xe0
	ldr r0, _0202C400 ; =FUN_0202C404
	lsr r2, r2, #0x10
	add r3, r4, r3
	bl WM_StartMP
	cmp r0, #0x2
	beq _0202C3E8
	bl FUN_0202C1AC
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0202C3E8:
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	nop
_0202C3F0: .word 0x021C59D8
_0202C3F4: .word 0x00001310
_0202C3F8: .word 0x00001304
_0202C3FC: .word 0x00001020
_0202C400: .word FUN_0202C404

	thumb_func_start FUN_0202C404
FUN_0202C404: ; 0x0202C404
	push {r3, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202C41A
	add r0, r1, #0x0
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r3, pc}
_0202C41A:
	ldrh r0, [r0, #0x4]
	sub r0, #0xa
	cmp r0, #0x3
	bhi _0202C454
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202C42E: ; jump table (using 16-bit offset)
	.short _0202C436 - _0202C42E - 2; case 0
	.short _0202C454 - _0202C42E - 2; case 1
	.short _0202C454 - _0202C42E - 2; case 2
	.short _0202C454 - _0202C42E - 2; case 3
_0202C436:
	ldr r0, _0202C458 ; =0x021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C45C ; =0x00001314
	ldr r1, [r2, r0]
	cmp r1, #0x2
	bne _0202C44E
	sub r0, r0, #0x4
	ldr r0, [r2, r0]
	cmp r0, #0x4
	beq _0202C44E
	cmp r0, #0x6
	beq _0202C454
_0202C44E:
	mov r0, #0x4
	bl FUN_0202C198
_0202C454:
	pop {r3, pc}
	nop
_0202C458: .word 0x021C59D8
_0202C45C: .word 0x00001314

	thumb_func_start FUN_0202C460
FUN_0202C460: ; 0x0202C460
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202C480 ; =FUN_0202C484
	bl WM_EndMP
	cmp r0, #0x2
	beq _0202C47A
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C47A:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0202C480: .word FUN_0202C484

	thumb_func_start FUN_0202C484
FUN_0202C484: ; 0x0202C484
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C496
	bl FUN_0202C1AC
	bl FUN_0202D0D8
	pop {r3, pc}
_0202C496:
	bl FUN_0202C4A4
	cmp r0, #0x0
	bne _0202C4A2
	bl FUN_0202D0D8
_0202C4A2:
	pop {r3, pc}

	thumb_func_start FUN_0202C4A4
FUN_0202C4A4: ; 0x0202C4A4
	push {r3, lr}
	ldr r0, _0202C4BC ; =FUN_0202C4C0
	bl WM_EndParent
	cmp r0, #0x2
	beq _0202C4B8
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C4B8:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C4BC: .word FUN_0202C4C0

	thumb_func_start FUN_0202C4C0
FUN_0202C4C0: ; 0x0202C4C0
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C4CE
	bl FUN_0202C1AC
	pop {r3, pc}
_0202C4CE:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202C4D8
FUN_0202C4D8: ; 0x0202C4D8
	push {r3-r7, lr}
	add r6, r2, #0x0
	ldr r2, _0202C564 ; =0x021C59D8
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r3, #0x2
	ldr r0, [r2, #0x4]
	ldr r1, _0202C568 ; =0x00001308
	lsl r3, r3, #0x8
	str r3, [r0, r1]
	ldr r2, [r2, #0x4]
	mov r0, #0x40
	sub r1, r1, #0x4
	str r0, [r2, r1]
	mov r0, #0x2
	bl FUN_0202C198
	ldr r1, _0202C564 ; =0x021C59D8
	ldr r0, _0202C56C ; =0x00001256
	ldr r3, [r1, #0x4]
	mov r2, #0x1
	strh r2, [r3, r0]
	add r7, r0, #0x0
	ldrh r3, [r4, #0x4]
	ldr r2, [r1, #0x4]
	add r7, #0x96
	strh r3, [r2, r7]
	add r7, r0, #0x0
	ldrh r3, [r4, #0x2]
	ldr r2, [r1, #0x4]
	add r7, #0x94
	strh r3, [r2, r7]
	add r2, r0, #0x0
	ldrh r4, [r4, #0x0]
	ldr r3, [r1, #0x4]
	add r2, #0x92
	strh r4, [r3, r2]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	add r2, #0xbe
	str r5, [r3, r2]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	mov r2, #0x0
	add r3, #0xaa
	str r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0xb6
	strh r6, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0x8e
	strh r2, [r4, r3]
	ldr r2, [r1, #0x4]
	add r0, #0xb8
	mov r1, #0x1
	strh r1, [r2, r0]
	bl FUN_0202C5D8
	cmp r0, #0x0
	bne _0202C55E
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C55E:
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0202C564: .word 0x021C59D8
_0202C568: .word 0x00001308
_0202C56C: .word 0x00001256

	thumb_func_start FUN_0202C570
FUN_0202C570: ; 0x0202C570
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x2
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0202C198
	ldr r1, _0202C5D4 ; =0x021C59D8
	mov r0, #0x13
	ldr r2, [r1, #0x4]
	lsl r0, r0, #0x8
	str r5, [r2, r0]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	add r2, #0xc
	strh r6, [r3, r2]
	add r3, r0, #0x0
	ldr r5, [r1, #0x4]
	mov r2, #0x0
	sub r3, #0x1c
	strh r2, [r5, r3]
	add r3, r0, #0x0
	ldr r5, [r1, #0x4]
	add r3, #0xe
	strh r2, [r5, r3]
	add r2, r0, #0x0
	ldrh r5, [r4, #0x4]
	ldr r3, [r1, #0x4]
	sub r2, #0x14
	strh r5, [r3, r2]
	add r2, r0, #0x0
	ldrh r5, [r4, #0x2]
	ldr r3, [r1, #0x4]
	sub r2, #0x16
	strh r5, [r3, r2]
	ldrh r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	sub r0, #0x18
	strh r2, [r1, r0]
	bl FUN_0202C5D8
	cmp r0, #0x0
	bne _0202C5D0
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r4-r6, pc}
_0202C5D0:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0202C5D4: .word 0x021C59D8

	thumb_func_start FUN_0202C5D8
FUN_0202C5D8: ; 0x0202C5D8
	push {r3-r7, lr}
	bl WM_GetAllowedChannel
	add r5, r0, #0x0
	mov r0, #0x2
	lsl r0, r0, #0xe
	cmp r5, r0
	bne _0202C5F8
	mov r0, #0x3
	bl FUN_0202C1AC
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C5F8:
	cmp r5, #0x0
	bne _0202C60C
	mov r0, #0x16
	bl FUN_0202C1AC
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C60C:
	ldr r1, _0202C684 ; =0x021C59D8
	ldr r0, _0202C688 ; =0x0000130C
	ldr r3, [r1, #0x4]
	ldrh r2, [r3, r0]
	cmp r2, #0x0
	bne _0202C64C
	add r7, r0, #0x0
	mov r3, #0x1
	add r2, r3, #0x0
	sub r7, #0x28
	sub r0, #0x28
_0202C622:
	ldr r4, [r1, #0x4]
	ldr r6, _0202C68C ; =0x000012E4
	ldrh r6, [r4, r6]
	add r6, r6, #0x1
	strh r6, [r4, r7]
	ldr r4, [r1, #0x4]
	ldrh r6, [r4, r0]
	cmp r6, #0x10
	bls _0202C638
	ldr r6, _0202C68C ; =0x000012E4
	strh r3, [r4, r6]
_0202C638:
	ldr r6, [r1, #0x4]
	ldr r4, _0202C68C ; =0x000012E4
	ldrh r4, [r6, r4]
	add r6, r2, #0x0
	sub r4, r4, #0x1
	lsl r6, r4
	add r4, r5, #0x0
	tst r4, r6
	bne _0202C650
	b _0202C622
_0202C64C:
	sub r0, #0x28
	strh r2, [r3, r0]
_0202C650:
	bl WM_GetDispersionScanPeriod
	ldr r2, _0202C684 ; =0x021C59D8
	ldr r1, _0202C690 ; =0x000012E6
	ldr r3, [r2, #0x4]
	strh r0, [r3, r1]
	add r0, r1, #0x0
	ldr r3, [r2, #0x4]
	sub r0, #0xc6
	add r4, r3, r0
	sub r0, r1, #0x6
	str r4, [r3, r0]
	ldr r2, [r2, #0x4]
	sub r1, r1, #0x6
	ldr r0, _0202C694 ; =FUN_0202C698
	add r1, r2, r1
	bl WM_StartScan
	cmp r0, #0x2
	beq _0202C680
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3-r7, pc}
_0202C680:
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0202C684: .word 0x021C59D8
_0202C688: .word 0x0000130C
_0202C68C: .word 0x000012E4
_0202C690: .word 0x000012E6
_0202C694: .word FUN_0202C698

	thumb_func_start FUN_0202C698
FUN_0202C698: ; 0x0202C698
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0202C6AE
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C6AE:
	ldr r0, _0202C760 ; =0x021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C764 ; =0x00001310
	ldr r1, [r2, r0]
	cmp r1, #0x2
	beq _0202C6D0
	mov r1, #0x0
	sub r0, r0, #0x2
	strh r1, [r2, r0]
	bl FUN_0202C794
	cmp r0, #0x0
	bne _0202C75C
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C6D0:
	ldrh r1, [r4, #0x8]
	cmp r1, #0x3
	beq _0202C75C
	cmp r1, #0x4
	beq _0202C74E
	cmp r1, #0x5
	bne _0202C74E
	sub r0, #0xf0
	add r0, r2, r0
	mov r1, #0xc0
	bl DC_InvalidateRange
	ldr r0, _0202C760 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C768 ; =0x00001320
	ldr r2, [r1, r0]
	cmp r2, #0x0
	beq _0202C704
	ldrh r0, [r4, #0x36]
	cmp r0, #0x8
	blo _0202C704
	add r1, r4, #0x0
	add r1, #0x48
	ldrb r1, [r1, #0x4]
	ldr r0, [r4, #0x3c]
	blx r2
_0202C704:
	ldrh r0, [r4, #0x36]
	cmp r0, #0x8
	blo _0202C74E
	ldr r0, _0202C760 ; =0x021C59D8
	ldr r2, [r4, #0x3c]
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0x8]
	cmp r2, r1
	bne _0202C74E
	add r4, #0x43
	ldrb r2, [r4, #0x0]
	mov r1, #0x3
	and r1, r2
	cmp r1, #0x1
	bne _0202C74E
	mov r1, #0x13
	lsl r1, r1, #0x8
	ldr r2, [r0, r1]
	cmp r2, #0x0
	beq _0202C732
	sub r1, #0xe0
	add r0, r0, r1
	blx r2
_0202C732:
	ldr r0, _0202C760 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C76C ; =0x0000130E
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	beq _0202C74E
	bl FUN_0202C794
	cmp r0, #0x0
	bne _0202C75C
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C74E:
	bl FUN_0202C5D8
	cmp r0, #0x0
	bne _0202C75C
	mov r0, #0x9
	bl FUN_0202C198
_0202C75C:
	pop {r4, pc}
	nop
_0202C760: .word 0x021C59D8
_0202C764: .word 0x00001310
_0202C768: .word 0x00001320
_0202C76C: .word 0x0000130E

	thumb_func_start FUN_0202C770
FUN_0202C770: ; 0x0202C770
	push {r3, lr}
	ldr r0, _0202C78C ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C790 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x2
	beq _0202C782
	mov r0, #0x0
	pop {r3, pc}
_0202C782:
	mov r0, #0x3
	bl FUN_0202C198
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C78C: .word 0x021C59D8
_0202C790: .word 0x00001310

	thumb_func_start FUN_0202C794
FUN_0202C794: ; 0x0202C794
	push {r3, lr}
	ldr r0, _0202C7AC ; =FUN_0202C7B0
	bl WM_EndScan
	cmp r0, #0x2
	beq _0202C7A8
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C7A8:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202C7AC: .word FUN_0202C7B0

	thumb_func_start FUN_0202C7B0
FUN_0202C7B0: ; 0x0202C7B0
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C7BE
	bl FUN_0202C1AC
	pop {r3, pc}
_0202C7BE:
	mov r0, #0x1
	bl FUN_0202C198
	ldr r0, _0202C7E0 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C7E4 ; =0x0000130E
	ldrh r0, [r1, r0]
	cmp r0, #0x0
	beq _0202C7DE
	bl FUN_0202C7E8
	cmp r0, #0x0
	bne _0202C7DE
	mov r0, #0x9
	bl FUN_0202C198
_0202C7DE:
	pop {r3, pc}
	.balign 4
_0202C7E0: .word 0x021C59D8
_0202C7E4: .word 0x0000130E

	thumb_func_start FUN_0202C7E8
FUN_0202C7E8: ; 0x0202C7E8
	push {lr}
	sub sp, #0x24
	ldr r0, _0202C844 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C848 ; =0x00001310
	ldr r0, [r1, r0]
	sub r0, r0, #0x4
	cmp r0, #0x2
	bhi _0202C800
	add sp, #0x24
	mov r0, #0x1
	pop {pc}
_0202C800:
	mov r0, #0x3
	bl FUN_0202C198
	add r1, sp, #0x4
	ldr r0, _0202C84C ; =0x02105D54
	add r1, #0x1
	mov r2, #0x3
	bl MI_CpuCopy8
	bl FUN_02033534
	add r1, sp, #0x4
	strb r0, [r1, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, _0202C844 ; =0x021C59D8
	ldr r0, _0202C850 ; =FUN_0202C858
	ldr r2, [r1, #0x4]
	ldr r1, _0202C854 ; =0x00001220
	mov r3, #0x1
	add r1, r2, r1
	add r2, sp, #0x4
	bl WM_StartConnectEx
	cmp r0, #0x2
	beq _0202C83E
	bl FUN_0202C1AC
	add sp, #0x24
	mov r0, #0x0
	pop {pc}
_0202C83E:
	mov r0, #0x1
	add sp, #0x24
	pop {pc}
	.balign 4
_0202C844: .word 0x021C59D8
_0202C848: .word 0x00001310
_0202C84C: .word 0x02105D54
_0202C850: .word FUN_0202C858
_0202C854: .word 0x00001220

	thumb_func_start FUN_0202C858
FUN_0202C858: ; 0x0202C858
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0202C894
	bl FUN_0202C1AC
	ldrh r0, [r4, #0x2]
	cmp r0, #0xc
	bne _0202C874
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C874:
	cmp r0, #0xb
	bne _0202C880
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C880:
	cmp r0, #0x1
	bne _0202C88C
	mov r0, #0x8
	bl FUN_0202C198
	pop {r4, pc}
_0202C88C:
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C894:
	ldrh r0, [r4, #0x8]
	cmp r0, #0x8
	beq _0202C8FA
	cmp r0, #0x7
	bne _0202C8DA
	ldr r0, _0202C8FC ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202C900 ; =0x00001335
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202C8B8
	mov r0, #0x14
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C8B8:
	mov r0, #0x4
	bl FUN_0202C198
	bl FUN_0202C908
	cmp r0, #0x0
	bne _0202C8CE
	mov r0, #0x3
	bl FUN_0202C198
	pop {r4, pc}
_0202C8CE:
	ldr r0, _0202C8FC ; =0x021C59D8
	ldrh r2, [r4, #0xa]
	ldr r1, [r0, #0x4]
	ldr r0, _0202C904 ; =0x0000132C
	strh r2, [r1, r0]
	pop {r4, pc}
_0202C8DA:
	cmp r0, #0x6
	beq _0202C8FA
	cmp r0, #0x9
	bne _0202C8F0
	mov r0, #0x14
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r4, pc}
_0202C8F0:
	cmp r0, #0x1a
	beq _0202C8FA
	mov r0, #0x9
	bl FUN_0202C198
_0202C8FA:
	pop {r4, pc}
	.balign 4
_0202C8FC: .word 0x021C59D8
_0202C900: .word 0x00001335
_0202C904: .word 0x0000132C

	thumb_func_start FUN_0202C908
FUN_0202C908: ; 0x0202C908
	push {r4, lr}
	sub sp, #0x8
	ldr r0, _0202C948 ; =0x021C59D8
	ldr r2, _0202C94C ; =0x00001304
	ldr r4, [r0, #0x4]
	ldr r3, _0202C950 ; =0x00001020
	ldr r0, [r4, r2]
	add r1, r4, r3
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r2, r2, #0x4
	ldr r2, [r4, r2]
	sub r3, #0xe0
	lsl r2, r2, #0x10
	ldr r0, _0202C954 ; =FUN_0202C958
	lsr r2, r2, #0x10
	add r3, r4, r3
	bl WM_StartMP
	cmp r0, #0x2
	beq _0202C942
	bl FUN_0202C1AC
	add sp, #0x8
	mov r0, #0x0
	pop {r4, pc}
_0202C942:
	mov r0, #0x1
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_0202C948: .word 0x021C59D8
_0202C94C: .word 0x00001304
_0202C950: .word 0x00001020
_0202C954: .word FUN_0202C958

	thumb_func_start FUN_0202C958
FUN_0202C958: ; 0x0202C958
	push {r3, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202C97A
	cmp r1, #0xf
	beq _0202C9B0
	cmp r1, #0x9
	beq _0202C9B0
	cmp r1, #0xd
	beq _0202C9B0
	add r0, r1, #0x0
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	pop {r3, pc}
_0202C97A:
	ldrh r0, [r0, #0x4]
	sub r0, #0xa
	cmp r0, #0x3
	bhi _0202C9B0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202C98E: ; jump table (using 16-bit offset)
	.short _0202C996 - _0202C98E - 2; case 0
	.short _0202C9B0 - _0202C98E - 2; case 1
	.short _0202C9B0 - _0202C98E - 2; case 2
	.short _0202C9B0 - _0202C98E - 2; case 3
_0202C996:
	ldr r0, _0202C9B4 ; =0x021C59D8
	ldr r2, [r0, #0x4]
	ldr r0, _0202C9B8 ; =0x00001314
	ldr r1, [r2, r0]
	cmp r1, #0x3
	bne _0202C9AA
	sub r0, r0, #0x4
	ldr r0, [r2, r0]
	cmp r0, #0x6
	beq _0202C9B0
_0202C9AA:
	mov r0, #0x4
	bl FUN_0202C198
_0202C9B0:
	pop {r3, pc}
	nop
_0202C9B4: .word 0x021C59D8
_0202C9B8: .word 0x00001314

	thumb_func_start FUN_0202C9BC
FUN_0202C9BC: ; 0x0202C9BC
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202C9DC ; =FUN_0202C9E0
	bl WM_EndMP
	cmp r0, #0x2
	beq _0202C9D6
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202C9D6:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0202C9DC: .word FUN_0202C9E0

	thumb_func_start FUN_0202C9E0
FUN_0202C9E0: ; 0x0202C9E0
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202C9F2
	bl FUN_0202C1AC
	bl FUN_0202D100
	pop {r3, pc}
_0202C9F2:
	bl FUN_0202CA04
	cmp r0, #0x0
	bne _0202CA00
	mov r0, #0x9
	bl FUN_0202C198
_0202CA00:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CA04
FUN_0202CA04: ; 0x0202CA04
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202CA28 ; =FUN_0202CA2C
	mov r1, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	beq _0202CA24
	bl FUN_0202C1AC
	bl FUN_0202D0D8
	mov r0, #0x0
	pop {r3, pc}
_0202CA24:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202CA28: .word FUN_0202CA2C

	thumb_func_start FUN_0202CA2C
FUN_0202CA2C: ; 0x0202CA2C
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202CA3A
	bl FUN_0202C1AC
	pop {r3, pc}
_0202CA3A:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CA44
FUN_0202CA44: ; 0x0202CA44
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202CA64 ; =FUN_0202CA68
	bl WM_Reset
	cmp r0, #0x2
	beq _0202CA5E
	bl FUN_0202C1AC
	mov r0, #0x0
	pop {r3, pc}
_0202CA5E:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0202CA64: .word FUN_0202CA68

	thumb_func_start FUN_0202CA68
FUN_0202CA68: ; 0x0202CA68
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _0202CA80
	mov r0, #0x9
	bl FUN_0202C198
	ldrh r0, [r4, #0x2]
	bl FUN_0202C1AC
	pop {r4, pc}
_0202CA80:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r4, pc}

	thumb_func_start FUN_0202CA88
FUN_0202CA88: ; 0x0202CA88
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, _0202CAD0 ; =0x021C59D8
	add r6, r1, #0x0
	add r4, r2, #0x0
	ldr r1, [r0, #0x4]
	mov r0, #0x3d
	lsl r0, r0, #0x6
	ldr r2, _0202CAD4 ; =0x00001304
	add r0, r1, r0
	ldr r1, [r1, r2]
	add r7, r3, #0x0
	bl DC_FlushRange
	ldr r0, _0202CAD8 ; =0x0000FFFF
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	ldr r0, _0202CADC ; =FUN_0202CAE0
	add r2, r5, #0x0
	add r3, r6, #0x0
	bl WM_SetMPDataToPortEx
	cmp r0, #0x2
	bne _0202CACA
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_0202CACA:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_0202CAD0: .word 0x021C59D8
_0202CAD4: .word 0x00001304
_0202CAD8: .word 0x0000FFFF
_0202CADC: .word FUN_0202CAE0

	thumb_func_start FUN_0202CAE0
FUN_0202CAE0: ; 0x0202CAE0
	push {r3, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202CAF4
	cmp r1, #0xf
	beq _0202CAF4
	add r0, r1, #0x0
	bl FUN_0202C1AC
	pop {r3, pc}
_0202CAF4:
	ldr r2, [r0, #0x20]
	cmp r2, #0x0
	beq _0202CB06
	cmp r1, #0x0
	bne _0202CB02
	mov r0, #0x1
	b _0202CB04
_0202CB02:
	mov r0, #0x0
_0202CB04:
	blx r2
_0202CB06:
	pop {r3, pc}

	thumb_func_start FUN_0202CB08
FUN_0202CB08: ; 0x0202CB08
	push {r3, lr}
	add r2, r0, #0x0
	ldrh r0, [r2, #0x2]
	cmp r0, #0x0
	beq _0202CB18
	bl FUN_0202C1AC
	pop {r3, pc}
_0202CB18:
	ldr r0, _0202CB48 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CB4C ; =0x00001318
	ldr r3, [r1, r0]
	cmp r3, #0x0
	beq _0202CB44
	ldrh r0, [r2, #0x4]
	cmp r0, #0x19
	beq _0202CB44
	cmp r0, #0x15
	bne _0202CB38
	ldrh r0, [r2, #0x12]
	ldr r1, [r2, #0xc]
	ldrh r2, [r2, #0x10]
	blx r3
	pop {r3, pc}
_0202CB38:
	cmp r0, #0x9
	bne _0202CB44
	ldrh r0, [r2, #0x12]
	mov r1, #0x0
	add r2, r1, #0x0
	blx r3
_0202CB44:
	pop {r3, pc}
	nop
_0202CB48: .word 0x021C59D8
_0202CB4C: .word 0x00001318

	thumb_func_start FUN_0202CB50
FUN_0202CB50: ; 0x0202CB50
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202CB60
	mov r0, #0xa
	bl FUN_0202C198
	pop {r3, pc}
_0202CB60:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02090CC8
	mov r0, #0x0
	bl FUN_0202C198
	pop {r3, pc}

	thumb_func_start FUN_0202CB70
FUN_0202CB70: ; 0x0202CB70
	ldr r1, _0202CB78 ; =0x021C59D8
	ldr r1, [r1, #0x4]
	str r0, [r1, #0x8]
	bx lr
	.balign 4
_0202CB78: .word 0x021C59D8

	thumb_func_start FUN_0202CB7C
FUN_0202CB7C: ; 0x0202CB7C
	ldr r2, _0202CB88 ; =0x021C59D8
	ldr r3, [r2, #0x4]
	str r0, [r3, #0x0]
	ldr r0, [r2, #0x4]
	strh r1, [r0, #0x4]
	bx lr
	.balign 4
_0202CB88: .word 0x021C59D8

	thumb_func_start FUN_0202CB8C
FUN_0202CB8C: ; 0x0202CB8C
	ldr r0, _0202CB98 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CB9C ; =0x0000132E
	ldrh r0, [r1, r0]
	bx lr
	nop
_0202CB98: .word 0x021C59D8
_0202CB9C: .word 0x0000132E

	thumb_func_start FUN_0202CBA0
FUN_0202CBA0: ; 0x0202CBA0
	push {r3-r4}
	ldr r0, _0202CBCC ; =0x021C59D8
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202CBD0 ; =0x0000132E
	add r3, r2, #0x0
	ldrh r4, [r1, r0]
	mov r1, #0x1
_0202CBB0:
	add r0, r4, #0x0
	tst r0, r1
	beq _0202CBB8
	add r2, r2, #0x1
_0202CBB8:
	lsl r0, r4, #0xf
	add r3, r3, #0x1
	lsr r4, r0, #0x10
	cmp r3, #0x10
	blt _0202CBB0
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	pop {r3-r4}
	bx lr
	nop
_0202CBCC: .word 0x021C59D8
_0202CBD0: .word 0x0000132E

	thumb_func_start FUN_0202CBD4
FUN_0202CBD4: ; 0x0202CBD4
	ldr r0, _0202CBE0 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CBE4 ; =0x00001310
	ldr r0, [r1, r0]
	bx lr
	nop
_0202CBE0: .word 0x021C59D8
_0202CBE4: .word 0x00001310

	thumb_func_start FUN_0202CBE8
FUN_0202CBE8: ; 0x0202CBE8
	ldr r0, _0202CBF4 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202CBF8 ; =0x00001330
	ldr r0, [r1, r0]
	bx lr
	nop
_0202CBF4: .word 0x021C59D8
_0202CBF8: .word 0x00001330

	thumb_func_start FUN_0202CBFC
FUN_0202CBFC: ; 0x0202CBFC
	push {r3-r5, lr}
	sub sp, #0x8
	add r0, sp, #0x0
	bl OS_GetMacAddress
	ldr r0, _0202CC84 ; =0x027FFC3C
	ldr r3, [r0, #0x0]
	add r0, sp, #0x0
	ldrh r2, [r0, #0x4]
	ldrh r1, [r0, #0x2]
	ldrh r0, [r0, #0x0]
	add r0, r0, r3
	add r0, r1, r0
	add r1, r2, r0
	ldr r3, _0202CC88 ; =0x021C59D8
	ldr r2, _0202CC8C ; =0x00001338
	ldr r0, [r3, #0x4]
	str r1, [r0, r2]
	ldr r0, [r3, #0x4]
	ldr r1, _0202CC90 ; =0x00010DCD
	ldr r4, [r0, r2]
	add r5, r4, #0x0
	mul r5, r1
	ldr r1, _0202CC94 ; =0x00003039
	mov r4, #0x0
	add r1, r5, r1
	str r1, [r0, r2]
	ldr r1, [r3, #0x4]
	add r0, r2, #0x4
	strh r4, [r1, r0]
	ldr r1, [r3, #0x4]
	mov r4, #0x65
	add r0, r2, #0x6
	strh r4, [r1, r0]
	mov r0, #0x3
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_0202CC98
	cmp r0, #0x18
	bne _0202CC68
	mov r0, #0x18
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0202CC68:
	cmp r0, #0x2
	beq _0202CC7C
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0202CC7C:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_0202CC84: .word 0x027FFC3C
_0202CC88: .word 0x021C59D8
_0202CC8C: .word 0x00001338
_0202CC90: .word 0x00010DCD
_0202CC94: .word 0x00003039

	thumb_func_start FUN_0202CC98
FUN_0202CC98: ; 0x0202CC98
	push {r4, lr}
	add r4, r0, #0x0
	bl WM_GetAllowedChannel
	mov r1, #0x2
	lsl r1, r1, #0xe
	cmp r0, r1
	bne _0202CCBE
	mov r0, #0x3
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x3
	pop {r4, pc}
_0202CCBE:
	cmp r0, #0x0
	bne _0202CCD8
	mov r0, #0x16
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	mov r0, #0x18
	pop {r4, pc}
_0202CCD8:
	mov r2, #0x1
	sub r1, r4, #0x1
	lsl r2, r1
	add r1, r2, #0x0
	tst r1, r0
	bne _0202CD00
	mov r2, #0x1
_0202CCE6:
	add r1, r4, #0x1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	cmp r4, #0x10
	bls _0202CCF4
	mov r0, #0x18
	pop {r4, pc}
_0202CCF4:
	sub r1, r4, #0x1
	add r3, r2, #0x0
	lsl r3, r1
	add r1, r3, #0x0
	tst r1, r0
	beq _0202CCE6
_0202CD00:
	ldr r0, _0202CD10 ; =FUN_0202CD14
	add r1, r4, #0x0
	bl FUN_0202CD90
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r4, pc}
	nop
_0202CD10: .word FUN_0202CD14

	thumb_func_start FUN_0202CD14
FUN_0202CD14: ; 0x0202CD14
	push {r3-r5, lr}
	ldrh r1, [r0, #0x2]
	cmp r1, #0x0
	beq _0202CD30
	add r0, r1, #0x0
	bl FUN_0202C1AC
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	pop {r3-r5, pc}
_0202CD30:
	ldr r2, _0202CD88 ; =0x021C59D8
	ldrh r1, [r0, #0x8]
	ldrh r5, [r0, #0xa]
	ldr r0, [r2, #0x4]
	ldr r3, _0202CD8C ; =0x0000133E
	ldrh r4, [r0, r3]
	cmp r4, r5
	bls _0202CD50
	strh r5, [r0, r3]
	mov r4, #0x1
	sub r0, r1, #0x1
	lsl r4, r0
	ldr r2, [r2, #0x4]
	add r0, r3, #0x2
	strh r4, [r2, r0]
	b _0202CD64
_0202CD50:
	cmp r4, r5
	bne _0202CD64
	add r2, r3, #0x2
	ldrh r5, [r0, r2]
	mov r4, #0x1
	sub r2, r1, #0x1
	lsl r4, r2
	orr r4, r5
	add r2, r3, #0x2
	strh r4, [r0, r2]
_0202CD64:
	add r0, r1, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202CC98
	cmp r0, #0x18
	bne _0202CD7A
	mov r0, #0x7
	bl FUN_0202C198
	pop {r3-r5, pc}
_0202CD7A:
	cmp r0, #0x2
	beq _0202CD84
	mov r0, #0x9
	bl FUN_0202C198
_0202CD84:
	pop {r3-r5, pc}
	nop
_0202CD88: .word 0x021C59D8
_0202CD8C: .word 0x0000133E

	thumb_func_start FUN_0202CD90
FUN_0202CD90: ; 0x0202CD90
	push {r3, lr}
	add r3, r1, #0x0
	mov r1, #0x1e
	str r1, [sp, #0x0]
	mov r1, #0x3
	mov r2, #0x11
	bl WM_MeasureChannel
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CDA4
FUN_0202CDA4: ; 0x0202CDA4
	push {r3, lr}
	mov r0, #0x1
	bl FUN_0202C198
	ldr r0, _0202CDC8 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	mov r0, #0x4d
	lsl r0, r0, #0x6
	ldrh r0, [r1, r0]
	bl FUN_0202CDD0
	ldr r2, _0202CDC8 ; =0x021C59D8
	ldr r1, _0202CDCC ; =0x0000133C
	ldr r3, [r2, #0x4]
	strh r0, [r3, r1]
	ldr r0, [r2, #0x4]
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0202CDC8: .word 0x021C59D8
_0202CDCC: .word 0x0000133C

	thumb_func_start FUN_0202CDD0
FUN_0202CDD0: ; 0x0202CDD0
	push {r4-r7}
	add r4, r0, #0x0
	mov r0, #0x0
	add r3, r0, #0x0
	add r2, r0, #0x0
	mov r1, #0x1
_0202CDDC:
	add r5, r1, #0x0
	lsl r5, r2
	tst r5, r4
	beq _0202CDF0
	add r0, r2, #0x1
	add r3, r3, #0x1
	lsl r0, r0, #0x10
	lsl r3, r3, #0x10
	asr r0, r0, #0x10
	lsr r3, r3, #0x10
_0202CDF0:
	add r2, r2, #0x1
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	cmp r2, #0x10
	blt _0202CDDC
	cmp r3, #0x1
	bls _0202CE4E
	ldr r5, _0202CE54 ; =0x021C59D8
	ldr r2, _0202CE58 ; =0x00001338
	ldr r0, [r5, #0x4]
	ldr r1, _0202CE5C ; =0x00010DCD
	ldr r6, [r0, r2]
	add r7, r6, #0x0
	mul r7, r1
	ldr r1, _0202CE60 ; =0x00003039
	add r1, r7, r1
	str r1, [r0, r2]
	ldr r0, [r5, #0x4]
	mov r1, #0x1
	ldr r0, [r0, r2]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	mul r0, r3
	lsl r0, r0, #0x8
	lsr r2, r0, #0x10
	mov r3, #0x0
_0202CE24:
	add r0, r4, #0x0
	tst r0, r1
	beq _0202CE3E
	cmp r2, #0x0
	bne _0202CE38
	add r0, r3, #0x1
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	pop {r4-r7}
	bx lr
_0202CE38:
	sub r0, r2, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
_0202CE3E:
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
	add r0, r3, #0x1
	lsl r0, r0, #0x10
	asr r3, r0, #0x10
	cmp r3, #0x10
	blt _0202CE24
	mov r0, #0x0
_0202CE4E:
	pop {r4-r7}
	bx lr
	nop
_0202CE54: .word 0x021C59D8
_0202CE58: .word 0x00001338
_0202CE5C: .word 0x00010DCD
_0202CE60: .word 0x00003039

	thumb_func_start FUN_0202CE64
FUN_0202CE64: ; 0x0202CE64
	push {r3-r5, lr}
	lsl r1, r0, #0x1b
	lsr r2, r1, #0x1b
	beq _0202CE72
	mov r1, #0x20
	sub r1, r1, r2
	add r0, r0, r1
_0202CE72:
	ldr r2, _0202CEE4 ; =0x021C59D8
	ldr r1, _0202CEE8 ; =0x00001308
	str r0, [r2, #0x4]
	mov r3, #0x0
	str r3, [r0, r1]
	ldr r4, [r2, #0x4]
	sub r0, r1, #0x4
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x10
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x24
	strh r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	mov r5, #0x1
	add r0, #0x26
	strh r5, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x28
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x8
	str r3, [r4, r0]
	ldr r0, [r2, #0x4]
	mov r5, #0x8
	str r3, [r0, #0x0]
	ldr r0, [r2, #0x4]
	strh r3, [r0, #0x4]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x14
	str r3, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x2c
	strb r5, [r4, r0]
	add r0, r1, #0x0
	ldr r4, [r2, #0x4]
	add r0, #0x2d
	strb r3, [r4, r0]
	ldr r0, [r2, #0x4]
	add r1, #0x3a
	strb r3, [r0, r1]
	bl FUN_0202CF0C
	cmp r0, #0x0
	bne _0202CEE0
	mov r0, #0x0
	pop {r3-r5, pc}
_0202CEE0:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0202CEE4: .word 0x021C59D8
_0202CEE8: .word 0x00001308

	thumb_func_start FUN_0202CEEC
FUN_0202CEEC: ; 0x0202CEEC
	mov r0, #0x4e
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_0202CEF4
FUN_0202CEF4: ; 0x0202CEF4
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x8
	bne _0202CF08
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x19
	bl FUN_0202C1AC
_0202CF08:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202CF0C
FUN_0202CF0C: ; 0x0202CF0C
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202CF38 ; =0x021C59D8
	ldr r1, _0202CF3C ; =FUN_0202CF40
	ldr r0, [r0, #0x4]
	mov r2, #0x2
	add r0, #0x40
	bl WM_Initialize
	cmp r0, #0x2
	beq _0202CF34
	bl FUN_0202C1AC
	mov r0, #0xa
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3, pc}
_0202CF34:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202CF38: .word 0x021C59D8
_0202CF3C: .word FUN_0202CF40

	thumb_func_start FUN_0202CF40
FUN_0202CF40: ; 0x0202CF40
	push {r3, lr}
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	beq _0202CF5A
	bl FUN_0202C1AC
	mov r0, #0xa
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	pop {r3, pc}
_0202CF5A:
	ldr r0, _0202CF80 ; =FUN_0202CEF4
	bl WM_SetIndCallback
	cmp r0, #0x0
	beq _0202CF76
	bl FUN_0202C1AC
	mov r0, #0xa
	bl FUN_0202C198
	mov r0, #0x1
	bl FUN_020336A0
	pop {r3, pc}
_0202CF76:
	mov r0, #0x1
	bl FUN_0202C198
	pop {r3, pc}
	nop
_0202CF80: .word FUN_0202CEF4

	thumb_func_start FUN_0202CF84
FUN_0202CF84: ; 0x0202CF84
	push {r3-r7, lr}
	add r6, r1, #0x0
	ldr r1, _0202D02C ; =0x021C59D8
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r0, #0x7
	ldr r2, [r1, #0x4]
	ldr r1, _0202D030 ; =0x00001308
	lsl r0, r0, #0x6
	str r0, [r2, r1]
	ldr r0, _0202D02C ; =0x021C59D8
	add r4, r3, #0x0
	ldr r2, [r0, #0x4]
	sub r0, r1, #0x4
	mov r3, #0xe0
	str r3, [r2, r0]
	ldr r0, _0202D02C ; =0x021C59D8
	add r1, #0xc
	ldr r0, [r0, #0x4]
	str r5, [r0, r1]
	mov r0, #0x3
	bl FUN_0202C198
	ldr r1, _0202D02C ; =0x021C59D8
	cmp r5, #0x0
	ldr r0, [r1, #0x4]
	strh r6, [r0, #0xc]
	ldr r0, [r1, #0x4]
	strh r7, [r0, #0x32]
	add r0, sp, #0x8
	ldrh r2, [r0, #0x10]
	ldr r0, [r1, #0x4]
	strh r2, [r0, #0x18]
	beq _0202CFCE
	cmp r5, #0x4
	beq _0202CFE8
	b _0202CFF4
_0202CFCE:
	ldr r0, [r1, #0x4]
	mov r2, #0xc0
	strh r2, [r0, #0x34]
	cmp r4, #0x5
	blo _0202CFE0
	ldr r0, [r1, #0x4]
	mov r2, #0xc
	strh r2, [r0, #0x36]
	b _0202CFF4
_0202CFE0:
	ldr r0, [r1, #0x4]
	mov r2, #0x26
	strh r2, [r0, #0x36]
	b _0202CFF4
_0202CFE8:
	ldr r0, [r1, #0x4]
	mov r2, #0x64
	strh r2, [r0, #0x34]
	ldr r0, [r1, #0x4]
	mov r2, #0xc
	strh r2, [r0, #0x36]
_0202CFF4:
	ldr r1, _0202D02C ; =0x021C59D8
	ldr r0, [r1, #0x4]
	strh r4, [r0, #0x10]
	ldr r2, [r1, #0x4]
	mov r0, #0x0
	strh r0, [r2, #0x16]
	ldr r2, [r1, #0x4]
	cmp r5, #0x2
	strh r0, [r2, #0x12]
	ldr r2, [sp, #0x1c]
	ldr r1, [r1, #0x4]
	strh r2, [r1, #0xe]
	bne _0202D010
	mov r0, #0x1
_0202D010:
	ldr r1, _0202D02C ; =0x021C59D8
	cmp r5, #0x0
	ldr r1, [r1, #0x4]
	strh r0, [r1, #0x14]
	beq _0202D022
	cmp r5, #0x2
	beq _0202D022
	cmp r5, #0x4
	bne _0202D028
_0202D022:
	bl FUN_0202C1C8
	pop {r3-r7, pc}
_0202D028:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0202D02C: .word 0x021C59D8
_0202D030: .word 0x00001308

	thumb_func_start FUN_0202D034
FUN_0202D034: ; 0x0202D034
	push {r4-r6, lr}
	ldr r2, _0202D094 ; =0x021C59D8
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r3, #0x2
	ldr r0, [r2, #0x4]
	ldr r1, _0202D098 ; =0x00001308
	lsl r3, r3, #0x8
	str r3, [r0, r1]
	sub r0, r1, #0x4
	ldr r3, [r2, #0x4]
	mov r6, #0x40
	str r6, [r3, r0]
	ldr r0, [r2, #0x4]
	add r1, #0xc
	str r5, [r0, r1]
	mov r0, #0x3
	bl FUN_0202C198
	cmp r5, #0x1
	beq _0202D066
	cmp r5, #0x3
	beq _0202D066
	cmp r5, #0x5
	bne _0202D08E
_0202D066:
	ldr r1, _0202D094 ; =0x021C59D8
	add r0, r4, #0x0
	ldr r2, [r1, #0x4]
	ldr r1, _0202D09C ; =0x00001220
	add r1, r2, r1
	mov r2, #0xc0
	bl MI_CpuCopy8
	ldr r0, _0202D094 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D09C ; =0x00001220
	add r0, r1, r0
	mov r1, #0xc0
	bl DC_FlushRange
	bl DC_WaitWriteBufferEmpty
	bl FUN_0202C7E8
	pop {r4-r6, pc}
_0202D08E:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0202D094: .word 0x021C59D8
_0202D098: .word 0x00001308
_0202D09C: .word 0x00001220

	thumb_func_start FUN_0202D0A0
FUN_0202D0A0: ; 0x0202D0A0
	push {r3, lr}
	ldr r2, _0202D0C4 ; =0x021C59D8
	ldr r3, [r2, #0x4]
	ldr r2, _0202D0C8 ; =0x00001318
	str r0, [r3, r2]
	lsl r0, r1, #0x10
	ldr r1, _0202D0CC ; =FUN_0202CB08
	lsr r0, r0, #0x10
	mov r2, #0x0
	bl WM_SetPortCallback
	cmp r0, #0x0
	beq _0202D0C2
	mov r0, #0x9
	bl FUN_0202C198
_0202D0C0:
	b _0202D0C0
_0202D0C2:
	pop {r3, pc}
	.balign 4
_0202D0C4: .word 0x021C59D8
_0202D0C8: .word 0x00001318
_0202D0CC: .word FUN_0202CB08

	thumb_func_start FUN_0202D0D0
FUN_0202D0D0: ; 0x0202D0D0
	push {r3, lr}
	bl FUN_0202CA88
	pop {r3, pc}

	thumb_func_start FUN_0202D0D8
FUN_0202D0D8: ; 0x0202D0D8
	push {r3, lr}
	ldr r0, _0202D0F8 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D0FC ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x2
	bne _0202D0E8
_0202D0E6:
	b _0202D0E6
_0202D0E8:
	bl FUN_0202CA44
	cmp r0, #0x0
	bne _0202D0F6
	mov r0, #0xa
	bl FUN_0202C198
_0202D0F6:
	pop {r3, pc}
	.balign 4
_0202D0F8: .word 0x021C59D8
_0202D0FC: .word 0x00001310

	thumb_func_start FUN_0202D100
FUN_0202D100: ; 0x0202D100
	push {r3, lr}
	ldr r0, _0202D16C ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D170 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x1
	beq _0202D16A
	cmp r0, #0x6
	beq _0202D126
	cmp r0, #0x5
	beq _0202D126
	cmp r0, #0x4
	beq _0202D126
	mov r0, #0x3
	bl FUN_0202C198
	bl FUN_0202D0D8
	pop {r3, pc}
_0202D126:
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202D16C ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D174 ; =0x00001314
	ldr r0, [r1, r0]
	cmp r0, #0x5
	bhi _0202D16A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202D144: ; jump table (using 16-bit offset)
	.short _0202D15E - _0202D144 - 2; case 0
	.short _0202D150 - _0202D144 - 2; case 1
	.short _0202D16A - _0202D144 - 2; case 2
	.short _0202D16A - _0202D144 - 2; case 3
	.short _0202D15E - _0202D144 - 2; case 4
	.short _0202D150 - _0202D144 - 2; case 5
_0202D150:
	bl FUN_0202C9BC
	cmp r0, #0x0
	bne _0202D16A
	bl FUN_0202D0D8
	pop {r3, pc}
_0202D15E:
	bl FUN_0202C460
	cmp r0, #0x0
	bne _0202D16A
	bl FUN_0202D0D8
_0202D16A:
	pop {r3, pc}
	.balign 4
_0202D16C: .word 0x021C59D8
_0202D170: .word 0x00001310
_0202D174: .word 0x00001314

	thumb_func_start FUN_0202D178
FUN_0202D178: ; 0x0202D178
	push {r3, lr}
	mov r0, #0x3
	bl FUN_0202C198
	ldr r0, _0202D198 ; =FUN_0202CB50
	bl WM_End
	cmp r0, #0x2
	beq _0202D194
	mov r0, #0x9
	bl FUN_0202C198
	mov r0, #0x0
	pop {r3, pc}
_0202D194:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202D198: .word FUN_0202CB50

	thumb_func_start FUN_0202D19C
FUN_0202D19C: ; 0x0202D19C
	ldr r0, _0202D1A8 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D1AC ; =0x0000132C
	ldrh r0, [r1, r0]
	bx lr
	nop
_0202D1A8: .word 0x021C59D8
_0202D1AC: .word 0x0000132C

	thumb_func_start FUN_0202D1B0
FUN_0202D1B0: ; 0x0202D1B0
	ldr r1, _0202D1C0 ; =0x021C59D8
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _0202D1BC
	ldr r1, _0202D1C4 ; =0x00001334
	strb r0, [r2, r1]
_0202D1BC:
	bx lr
	nop
_0202D1C0: .word 0x021C59D8
_0202D1C4: .word 0x00001334

	thumb_func_start FUN_0202D1C8
FUN_0202D1C8: ; 0x0202D1C8
	ldr r0, _0202D1DC ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D1E0 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x1
	bne _0202D1D8
	mov r0, #0x1
	bx lr
_0202D1D8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D1DC: .word 0x021C59D8
_0202D1E0: .word 0x00001310

	thumb_func_start FUN_0202D1E4
FUN_0202D1E4: ; 0x0202D1E4
	ldr r0, _0202D1F8 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D1FC ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x3
	bne _0202D1F4
	mov r0, #0x1
	bx lr
_0202D1F4:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D1F8: .word 0x021C59D8
_0202D1FC: .word 0x00001310

	thumb_func_start FUN_0202D200
FUN_0202D200: ; 0x0202D200
	ldr r0, _0202D214 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D218 ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x9
	bne _0202D210
	mov r0, #0x1
	bx lr
_0202D210:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D214: .word 0x021C59D8
_0202D218: .word 0x00001310

	thumb_func_start FUN_0202D21C
FUN_0202D21C: ; 0x0202D21C
	ldr r0, _0202D238 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0202D234
	ldr r0, _0202D23C ; =0x00001310
	ldr r0, [r1, r0]
	cmp r0, #0x2
	bne _0202D230
	mov r0, #0x1
	bx lr
_0202D230:
	mov r0, #0x0
	bx lr
_0202D234:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D238: .word 0x021C59D8
_0202D23C: .word 0x00001310

	thumb_func_start FUN_0202D240
FUN_0202D240: ; 0x0202D240
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	ldr r0, _0202D274 ; =0x021C59D8
	add r5, r1, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202D278 ; =0x00001310
	add r4, r2, #0x0
	ldr r0, [r1, r0]
	cmp r0, #0x4
	bne _0202D26E
	lsl r0, r3, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r2, r5, #0x10
	str r0, [sp, #0x4]
	mov r0, #0x0
	add r1, r6, #0x0
	lsr r2, r2, #0x10
	add r3, r4, #0x0
	bl WM_SetGameInfo
_0202D26E:
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0202D274: .word 0x021C59D8
_0202D278: .word 0x00001310

	thumb_func_start FUN_0202D27C
FUN_0202D27C: ; 0x0202D27C
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _0202D28C
	ldr r0, _0202D290 ; =0x021C59D8
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _0202D294 ; =0x00001344
	strb r2, [r1, r0]
_0202D28C:
	bx lr
	nop
_0202D290: .word 0x021C59D8
_0202D294: .word 0x00001344

	thumb_func_start FUN_0202D298
FUN_0202D298: ; 0x0202D298
	push {r4, lr}
	ldr r2, _0202D2C4 ; =0x021C59D8
	add r1, r0, #0x0
	ldr r3, [r2, #0x4]
	ldr r0, _0202D2C8 ; =0x00001344
	mov r4, #0x0
	strb r4, [r3, r0]
	ldr r2, [r2, #0x4]
	sub r0, #0x34
	ldr r0, [r2, r0]
	cmp r0, #0x4
	bne _0202D2BE
	ldr r0, _0202D2CC ; =FUN_0202D27C
	bl WM_SetEntry
	cmp r0, #0x2
	bne _0202D2BE
	mov r0, #0x1
	pop {r4, pc}
_0202D2BE:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0202D2C4: .word 0x021C59D8
_0202D2C8: .word 0x00001344
_0202D2CC: .word FUN_0202D27C

	thumb_func_start FUN_0202D2D0
FUN_0202D2D0: ; 0x0202D2D0
	ldr r0, _0202D2EC ; =0x021C59D8
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0202D2E8
	ldr r0, _0202D2F0 ; =0x00001345
	ldrb r0, [r1, r0]
	cmp r0, #0x6
	blo _0202D2E4
	mov r0, #0x1
	bx lr
_0202D2E4:
	mov r0, #0x0
	bx lr
_0202D2E8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202D2EC: .word 0x021C59D8
_0202D2F0: .word 0x00001345

	thumb_func_start FUN_0202D2F4
FUN_0202D2F4: ; 0x0202D2F4
	ldr r0, _0202D300 ; =0x021C59D8
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202D304 ; =0x00001345
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202D300: .word 0x021C59D8
_0202D304: .word 0x00001345

	thumb_func_start FUN_0202D308
FUN_0202D308: ; 0x0202D308
	ldr r1, _0202D314 ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D318 ; =0x00001320
	str r0, [r2, r1]
	bx lr
	nop
_0202D314: .word 0x021C59D8
_0202D318: .word 0x00001320

	thumb_func_start FUN_0202D31C
FUN_0202D31C: ; 0x0202D31C
	ldr r1, _0202D328 ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D32C ; =0x00001324
	str r0, [r2, r1]
	bx lr
	nop
_0202D328: .word 0x021C59D8
_0202D32C: .word 0x00001324

	thumb_func_start FUN_0202D330
FUN_0202D330: ; 0x0202D330
	ldr r1, _0202D33C ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D340 ; =0x00001328
	str r0, [r2, r1]
	bx lr
	nop
_0202D33C: .word 0x021C59D8
_0202D340: .word 0x00001328

	thumb_func_start FUN_0202D344
FUN_0202D344: ; 0x0202D344
	ldr r1, _0202D350 ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D354 ; =0x00001342
	strb r0, [r2, r1]
	bx lr
	nop
_0202D350: .word 0x021C59D8
_0202D354: .word 0x00001342

	thumb_func_start FUN_0202D358
FUN_0202D358: ; 0x0202D358
	ldr r0, _0202D364 ; =0x021C59D8
	ldr r1, [r0, #0x4]
	ldr r0, _0202D368 ; =0x00001342
	ldrb r0, [r1, r0]
	bx lr
	nop
_0202D364: .word 0x021C59D8
_0202D368: .word 0x00001342

	thumb_func_start FUN_0202D36C
FUN_0202D36C: ; 0x0202D36C
	ldr r1, _0202D378 ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D37C ; =0x00001343
	strb r0, [r2, r1]
	bx lr
	nop
_0202D378: .word 0x021C59D8
_0202D37C: .word 0x00001343

	thumb_func_start FUN_0202D380
FUN_0202D380: ; 0x0202D380
	ldr r1, _0202D38C ; =0x021C59D8
	ldr r2, [r1, #0x4]
	ldr r1, _0202D390 ; =0x00001335
	strb r0, [r2, r1]
	bx lr
	nop
_0202D38C: .word 0x021C59D8
_0202D390: .word 0x00001335

	thumb_func_start FUN_0202D394
FUN_0202D394: ; 0x0202D394
	str r1, [r0, #0x0]
	strh r2, [r0, #0xa]
	mov r1, #0x0
	strh r1, [r0, #0x4]
	strh r1, [r0, #0x6]
	strh r1, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_0202D3A4
FUN_0202D3A4: ; 0x0202D3A4
	push {r3-r7, lr}
	str r2, [sp, #0x0]
	add r5, r0, #0x0
	add r7, r1, #0x0
	bl FUN_0202D498
	ldr r1, [sp, #0x0]
	cmp r0, r1
	bgt _0202D3BC
	bl FUN_02031454
	pop {r3-r7, pc}
_0202D3BC:
	mov r0, #0x8
	ldrsh r4, [r5, r0]
	ldrsh r1, [r5, r0]
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	add r0, r1, r0
	cmp r4, r0
	bge _0202D3F2
_0202D3CC:
	cmp r7, #0x0
	bne _0202D3D4
	bl ErrorHandling
_0202D3D4:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	ldrb r2, [r7, r6]
	ldr r1, [r5, #0x0]
	add r4, r4, #0x1
	strb r2, [r1, r0]
	mov r0, #0x8
	ldrsh r1, [r5, r0]
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r1, r0
	cmp r4, r0
	blt _0202D3CC
_0202D3F2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	strh r0, [r5, #0x8]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D400
FUN_0202D400: ; 0x0202D400
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0202D42C
	mov r1, #0x4
	add r4, r0, #0x0
	ldrsh r1, [r5, r1]
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_0202D4A8
	strh r0, [r5, #0x4]
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0202D41C
FUN_0202D41C: ; 0x0202D41C
	push {r3, lr}
	add r1, sp, #0x0
	mov r2, #0x1
	bl FUN_0202D400
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0202D42C
FUN_0202D42C: ; 0x0202D42C
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x4
	ldrsh r4, [r5, r0]
	add r7, r2, #0x0
	str r1, [sp, #0x0]
	add r0, r4, r7
	mov r6, #0x0
	cmp r4, r0
	bge _0202D472
_0202D440:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	mov r1, #0x6
	ldrsh r1, [r5, r1]
	cmp r1, r0
	bne _0202D454
	add r0, r6, #0x0
	pop {r3-r7, pc}
_0202D454:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D4A8
	ldr r1, [r5, #0x0]
	add r4, r4, #0x1
	ldrb r1, [r1, r0]
	ldr r0, [sp, #0x0]
	strb r1, [r0, r6]
	mov r0, #0x4
	ldrsh r0, [r5, r0]
	add r6, r6, #0x1
	add r0, r0, r7
	cmp r4, r0
	blt _0202D440
_0202D472:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D478
FUN_0202D478: ; 0x0202D478
	mov r1, #0x4
	mov r3, #0x6
	ldrsh r1, [r0, r1]
	ldrsh r2, [r0, r3]
	cmp r1, r2
	ble _0202D490
	mov r2, #0xa
	ldrsh r2, [r0, r2]
	ldrsh r0, [r0, r3]
	add r0, r2, r0
	sub r0, r0, r1
	bx lr
_0202D490:
	ldrsh r0, [r0, r3]
	sub r0, r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_0202D498
FUN_0202D498: ; 0x0202D498
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0202D478
	mov r1, #0xa
	ldrsh r1, [r4, r1]
	sub r0, r1, r0
	pop {r4, pc}

	thumb_func_start FUN_0202D4A8
FUN_0202D4A8: ; 0x0202D4A8
	push {r3, lr}
	add r2, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0xa
	ldrsh r1, [r2, r1]
	bl _s32_div_f
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202D4BC
FUN_0202D4BC: ; 0x0202D4BC
	mov r1, #0x8
	ldrsh r1, [r0, r1]
	strh r1, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0202D4C4
FUN_0202D4C4: ; 0x0202D4C4
	ldr r3, [r0, #0x1c]
	mov r2, #0x0
	ldr r1, [r0, #0x18]
	cmp r3, #0x0
	ble _0202D4E0
_0202D4CE:
	ldrb r0, [r1, #0xe]
	cmp r0, #0x0
	bne _0202D4D8
	add r0, r1, #0x0
	bx lr
_0202D4D8:
	add r2, r2, #0x1
	add r1, #0x10
	cmp r2, r3
	blt _0202D4CE
_0202D4E0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202D4E4
FUN_0202D4E4: ; 0x0202D4E4
	ldr r3, [r0, #0x1c]
	mov r2, #0x0
	ldr r1, [r0, #0x18]
	cmp r3, #0x0
	ble _0202D500
_0202D4EE:
	ldrb r0, [r1, #0xe]
	cmp r0, #0x0
	beq _0202D4F8
	mov r0, #0x0
	bx lr
_0202D4F8:
	add r2, r2, #0x1
	add r1, #0x10
	cmp r2, r3
	blt _0202D4EE
_0202D500:
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0202D504
FUN_0202D504: ; 0x0202D504
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202D522
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	beq _0202D518
	str r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r1, #0x4]
	b _0202D51E
_0202D518:
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
_0202D51E:
	mov r0, #0x1
	bx lr
_0202D522:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202D528
FUN_0202D528: ; 0x0202D528
	ldr r2, [r0, #0x0]
	strb r1, [r2, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	sub r1, r1, #0x1
	str r1, [r0, #0x4]
	bne _0202D53E
	mov r0, #0x1
	bx lr
_0202D53E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0202D544
FUN_0202D544: ; 0x0202D544
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0xe]
	add r4, r1, #0x0
	bl FUN_0202D9A0
	add r6, r0, #0x0
	ldr r0, _0202D5B8 ; =0x0000FFFF
	cmp r6, r0
	ldr r0, [r4, #0x4]
	bne _0202D56A
	cmp r0, #0x3
	bge _0202D57A
	ldrb r1, [r5, #0xf]
	mov r0, #0x1
	bic r1, r0
	strb r1, [r5, #0xf]
	mov r0, #0x1
	pop {r4-r6, pc}
_0202D56A:
	cmp r0, #0x1
	bge _0202D57A
	ldrb r1, [r5, #0xf]
	mov r0, #0x1
	bic r1, r0
	strb r1, [r5, #0xf]
	mov r0, #0x1
	pop {r4-r6, pc}
_0202D57A:
	ldrb r1, [r5, #0xe]
	add r0, r4, #0x0
	bl FUN_0202D528
	ldr r0, _0202D5B8 ; =0x0000FFFF
	cmp r6, r0
	bne _0202D5A4
	ldrh r1, [r5, #0xc]
	add r0, r4, #0x0
	asr r1, r1, #0x8
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0202D528
	ldrh r1, [r5, #0xc]
	add r0, r4, #0x0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0202D528
	b _0202D5A6
_0202D5A4:
	strh r6, [r5, #0xc]
_0202D5A6:
	ldrb r1, [r5, #0xf]
	mov r0, #0x1
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strb r0, [r5, #0xf]
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0202D5B8: .word 0x0000FFFF

	thumb_func_start FUN_0202D5BC
FUN_0202D5BC: ; 0x0202D5BC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0xe]
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0202D9A0
	ldr r1, _0202D680 ; =0x0000FFFF
	cmp r0, r1
	bne _0202D5D6
	mov r2, #0x3
	b _0202D5D8
_0202D5D6:
	mov r2, #0x1
_0202D5D8:
	ldrh r0, [r5, #0xc]
	ldr r1, [r4, #0x4]
	add r0, r0, r2
	cmp r1, r0
	bge _0202D5EA
	cmp r7, #0x0
	bne _0202D5EA
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D5EA:
	ldrb r0, [r5, #0xf]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	beq _0202D604
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0202D544
	cmp r0, #0x0
	beq _0202D604
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D604:
	ldrh r3, [r5, #0xc]
	ldr r2, [r4, #0x4]
	cmp r2, r3
	ldrb r0, [r5, #0xf]
	bge _0202D64E
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _0202D61E
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	bl FUN_0202D400
	b _0202D634
_0202D61E:
	mov r3, #0x0
	cmp r2, #0x0
	ble _0202D634
_0202D624:
	ldr r0, [r5, #0x0]
	ldrb r1, [r0, r3]
	ldr r0, [r4, #0x0]
	strb r1, [r0, r3]
	ldr r0, [r4, #0x4]
	add r3, r3, #0x1
	cmp r3, r0
	blt _0202D624
_0202D634:
	ldr r1, [r5, #0x0]
	ldr r0, [r4, #0x4]
	add r0, r1, r0
	str r0, [r5, #0x0]
	ldrh r1, [r5, #0xc]
	ldr r0, [r4, #0x4]
	sub r0, r1, r0
	strh r0, [r5, #0xc]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r3-r7, pc}
_0202D64E:
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _0202D660
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	add r2, r3, #0x0
	bl FUN_0202D400
	b _0202D66A
_0202D660:
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	add r2, r3, #0x0
	bl MI_CpuCopy8
_0202D66A:
	ldrh r0, [r5, #0xc]
	ldr r1, [r4, #0x0]
	add r0, r1, r0
	str r0, [r4, #0x0]
	ldrh r0, [r5, #0xc]
	ldr r1, [r4, #0x4]
	sub r0, r1, r0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_0202D680: .word 0x0000FFFF

	thumb_func_start FUN_0202D684
FUN_0202D684: ; 0x0202D684
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r7, r3, #0x0
	bl FUN_0202D4C4
	add r4, r0, #0x0
	bne _0202D69E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D69E:
	ldr r0, _0202D710 ; =0x0000FFFE
	cmp r7, r0
	blt _0202D6A8
	bl ErrorHandling
_0202D6A8:
	ldr r0, [sp, #0x0]
	bl FUN_0202D9A0
	add r6, r0, #0x0
	ldr r0, _0202D714 ; =0x0000FFFF
	cmp r6, r0
	bne _0202D6B8
	add r6, r7, #0x0
_0202D6B8:
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	beq _0202D6EA
	ldr r0, [r5, #0x14]
	bl FUN_0202D498
	add r1, r6, #0x3
	cmp r1, r0
	blt _0202D6D0
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D6D0:
	ldr r0, [r5, #0x14]
	ldr r1, [sp, #0x4]
	ldr r3, _0202D718 ; =0x00000109
	add r2, r6, #0x0
	bl FUN_0202D3A4
	ldr r0, [r5, #0x14]
	bl FUN_0202D4BC
	ldrb r1, [r4, #0xf]
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0xf]
_0202D6EA:
	ldr r0, [sp, #0x0]
	strh r6, [r4, #0xc]
	strb r0, [r4, #0xe]
	ldr r0, [sp, #0x4]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _0202D700
	str r4, [r5, #0x4]
	str r4, [r5, #0x0]
	b _0202D708
_0202D700:
	str r4, [r0, #0x8]
	ldr r0, [r5, #0x4]
	str r0, [r4, #0x4]
	str r4, [r5, #0x4]
_0202D708:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0202D710: .word 0x0000FFFE
_0202D714: .word 0x0000FFFF
_0202D718: .word 0x00000109

	thumb_func_start FUN_0202D71C
FUN_0202D71C: ; 0x0202D71C
	ldr r1, [r0, #0x10]
	cmp r1, #0x0
	beq _0202D726
	add r0, r1, #0x0
	bx lr
_0202D726:
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202D730
	add r0, r1, #0x0
	bx lr
_0202D730:
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0202D738
	mov r0, #0x0
_0202D738:
	bx lr
	.balign 4

	thumb_func_start FUN_0202D73C
FUN_0202D73C: ; 0x0202D73C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	beq _0202D74C
	mov r0, #0x0
	str r0, [r4, #0x10]
	pop {r4, pc}
_0202D74C:
	bl FUN_0202D504
	cmp r0, #0x0
	bne _0202D75C
	add r4, #0x8
	add r0, r4, #0x0
	bl FUN_0202D504
_0202D75C:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202D760
FUN_0202D760: ; 0x0202D760
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x4]
	mov r7, #0x1
	str r2, [sp, #0x0]
	cmp r0, #0x0
	ble _0202D7B6
_0202D770:
	add r0, r5, #0x0
	bl FUN_0202D71C
	add r6, r0, #0x0
	beq _0202D7B6
	add r0, r5, #0x0
	bl FUN_0202D73C
	ldr r2, [r5, #0x14]
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r3, r7, #0x0
	bl FUN_0202D5BC
	cmp r0, #0x0
	bne _0202D794
	str r6, [r5, #0x10]
	b _0202D7B6
_0202D794:
	mov r0, #0x0
	ldr r1, [r4, #0x4]
	mvn r0, r0
	cmp r1, r0
	bne _0202D7A4
	str r6, [r5, #0x10]
	mov r0, #0x0
	pop {r3-r7, pc}
_0202D7A4:
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0x10
	bl MI_CpuFill8
	ldr r0, [r4, #0x4]
	ldr r7, [sp, #0x0]
	cmp r0, #0x0
	bgt _0202D770
_0202D7B6:
	ldr r0, [r4, #0x4]
	mov r2, #0x0
	cmp r0, #0x0
	ble _0202D7D2
	mov r1, #0xee
_0202D7C0:
	ldr r0, [r4, #0x0]
	add r2, r2, #0x1
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x4]
	cmp r2, r0
	blt _0202D7C0
_0202D7D2:
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D7D8
FUN_0202D7D8: ; 0x0202D7D8
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r1, #0x0
	mov r2, #0x20
	add r5, r0, #0x0
	bl MI_CpuFill8
	lsl r7, r4, #0x4
	mov r0, #0xf
	add r1, r7, #0x0
	bl FUN_02016998
	mov r1, #0x0
	add r2, r7, #0x0
	str r0, [r5, #0x18]
	bl MI_CpuFill8
	str r4, [r5, #0x1c]
	str r6, [r5, #0x14]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202D804
FUN_0202D804: ; 0x0202D804
	push {r4, lr}
	add r4, r0, #0x0
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	str r0, [r4, #0x8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202D824
FUN_0202D824: ; 0x0202D824
	ldr r3, _0202D82C ; =FUN_02016A18
	ldr r0, [r0, #0x18]
	bx r3
	nop
_0202D82C: .word FUN_02016A18

	thumb_func_start FUN_0202D830
FUN_0202D830: ; 0x0202D830
	push {r3-r4}
	ldr r4, [r0, #0x1c]
	mov r2, #0x0
	ldr r3, [r0, #0x18]
	cmp r4, #0x0
	ble _0202D850
_0202D83C:
	ldrb r0, [r3, #0xe]
	cmp r0, r1
	bne _0202D848
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0202D848:
	add r2, r2, #0x1
	add r3, #0x10
	cmp r2, r4
	blt _0202D83C
_0202D850:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0202D858
FUN_0202D858: ; 0x0202D858
	push {r3-r4, lr}
	sub sp, #0x1c
	ldr r3, _0202D880 ; =0x020EEB04
	add r4, r0, #0x0
	add r2, sp, #0x0
	mov r1, #0x1a
_0202D864:
	ldrb r0, [r3, #0x0]
	add r3, r3, #0x1
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0202D864
	cmp r4, #0x1a
	blo _0202D878
	bl ErrorHandling
_0202D878:
	add r0, sp, #0x0
	ldrb r0, [r0, r4]
	add sp, #0x1c
	pop {r3-r4, pc}
	.balign 4
_0202D880: .word 0x020EEB04

	thumb_func_start FUN_0202D884
FUN_0202D884: ; 0x0202D884
	push {r3-r4, lr}
	sub sp, #0x1c
	ldr r3, _0202D8AC ; =0x020EEB1E
	add r4, r0, #0x0
	add r2, sp, #0x0
	mov r1, #0x1a
_0202D890:
	ldrb r0, [r3, #0x0]
	add r3, r3, #0x1
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _0202D890
	cmp r4, #0x1a
	blo _0202D8A4
	bl ErrorHandling
_0202D8A4:
	add r0, sp, #0x0
	ldrb r0, [r0, r4]
	add sp, #0x1c
	pop {r3-r4, pc}
	.balign 4
_0202D8AC: .word 0x020EEB1E

	thumb_func_start FUN_0202D8B0
FUN_0202D8B0: ; 0x0202D8B0
	cmp r0, #0xd
	bgt _0202D8C4
	cmp r0, #0x7
	blt _0202D8CC
	beq _0202D8C8
	cmp r0, #0x9
	beq _0202D8C8
	cmp r0, #0xd
	beq _0202D8C8
	b _0202D8CC
_0202D8C4:
	cmp r0, #0x12
	bne _0202D8CC
_0202D8C8:
	mov r0, #0x1
	bx lr
_0202D8CC:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202D8D0
FUN_0202D8D0: ; 0x0202D8D0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0202D914 ; =0x021C59E0
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	cmp r0, #0x0
	bne _0202D8EC
	mov r0, #0xf
	mov r1, #0x18
	bl FUN_02016998
	ldr r1, _0202D914 ; =0x021C59E0
	str r0, [r1, #0x0]
_0202D8EC:
	ldr r0, _0202D914 ; =0x021C59E0
	mov r3, #0x0
	ldr r1, [r0, #0x0]
	add r2, r3, #0x0
	str r5, [r1, #0x0]
	ldr r1, [r0, #0x0]
	str r4, [r1, #0x4]
	ldr r1, [r0, #0x0]
	str r6, [r1, #0x8]
_0202D8FE:
	ldr r1, [r0, #0x0]
	add r1, r1, r3
	add r3, r3, #0x1
	strb r2, [r1, #0xc]
	cmp r3, #0x8
	blt _0202D8FE
	ldr r0, _0202D914 ; =0x021C59E0
	ldr r0, [r0, #0x0]
	strb r2, [r0, #0x14]
	pop {r4-r6, pc}
	nop
_0202D914: .word 0x021C59E0

	thumb_func_start FUN_0202D918
FUN_0202D918: ; 0x0202D918
	push {r3, lr}
	ldr r0, _0202D930 ; =0x021C59E0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202D92C
	bl FUN_02016A18
	ldr r0, _0202D930 ; =0x021C59E0
	mov r1, #0x0
	str r1, [r0, #0x0]
_0202D92C:
	pop {r3, pc}
	nop
_0202D930: .word 0x021C59E0

	thumb_func_start FUN_0202D934
FUN_0202D934: ; 0x0202D934
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r4, #0x16
	bge _0202D94C
	mov r0, #0xc
	mul r1, r0
	ldr r0, _0202D998 ; =0x020EEB38
	ldr r4, [r0, r1]
	b _0202D974
_0202D94C:
	ldr r0, _0202D99C ; =0x021C59E0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202D958
	bl ErrorHandling
_0202D958:
	ldr r0, _0202D99C ; =0x021C59E0
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x4]
	add r0, #0x16
	cmp r4, r0
	ble _0202D96A
	bl FUN_02031454
	pop {r3-r7, pc}
_0202D96A:
	ldr r1, [r1, #0x0]
	sub r4, #0x16
	mov r0, #0xc
	mul r0, r4
	ldr r4, [r1, r0]
_0202D974:
	cmp r4, #0x0
	beq _0202D996
	ldr r0, _0202D99C ; =0x021C59E0
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _0202D98C
	ldr r3, [r3, #0x8]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	blx r4
	pop {r3-r7, pc}
_0202D98C:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x0
	blx r4
_0202D996:
	pop {r3-r7, pc}
	.balign 4
_0202D998: .word 0x020EEB38
_0202D99C: .word 0x021C59E0

	thumb_func_start FUN_0202D9A0
FUN_0202D9A0: ; 0x0202D9A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r5, #0x16
	bge _0202D9B6
	mov r0, #0xc
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, _0202D9FC ; =0x020EEB3C
	ldr r0, [r0, r1]
	b _0202D9EE
_0202D9B6:
	ldr r0, _0202DA00 ; =0x021C59E0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202D9C2
	bl ErrorHandling
_0202D9C2:
	ldr r0, _0202DA00 ; =0x021C59E0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _0202D9D2
	bl FUN_02031454
	mov r0, #0x0
	pop {r3-r5, pc}
_0202D9D2:
	ldr r0, [r1, #0x4]
	add r0, #0x16
	cmp r5, r0
	ble _0202D9E2
	bl FUN_02031454
	mov r0, #0x0
	pop {r3-r5, pc}
_0202D9E2:
	ldr r1, [r1, #0x0]
	sub r5, #0x16
	mov r0, #0xc
	mul r0, r5
	add r0, r1, r0
	ldr r0, [r0, #0x4]
_0202D9EE:
	cmp r0, #0x0
	beq _0202D9F6
	blx r0
	add r4, r0, #0x0
_0202D9F6:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_0202D9FC: .word 0x020EEB3C
_0202DA00: .word 0x021C59E0

	thumb_func_start FUN_0202DA04
FUN_0202DA04: ; 0x0202DA04
	cmp r0, #0x16
	bge _0202DA1C
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0202DA38 ; =0x020EEB40
	ldr r0, [r0, r1]
	cmp r0, #0x0
	beq _0202DA18
	mov r0, #0x1
	bx lr
_0202DA18:
	mov r0, #0x0
	bx lr
_0202DA1C:
	ldr r1, _0202DA3C ; =0x021C59E0
	sub r0, #0x16
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x0]
	mov r1, #0xc
	mul r1, r0
	add r0, r2, r1
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202DA34
	mov r0, #0x1
	bx lr
_0202DA34:
	mov r0, #0x0
	bx lr
	.balign 4
_0202DA38: .word 0x020EEB40
_0202DA3C: .word 0x021C59E0

	thumb_func_start FUN_0202DA40
FUN_0202DA40: ; 0x0202DA40
	push {r3-r5, lr}
	add r3, r0, #0x0
	cmp r3, #0x16
	bge _0202DA58
	mov r4, #0xc
	mul r4, r3
	ldr r3, _0202DA70 ; =0x020EEB40
	add r0, r1, #0x0
	ldr r3, [r3, r4]
	mov r1, #0x0
	blx r3
	pop {r3-r5, pc}
_0202DA58:
	ldr r0, _0202DA74 ; =0x021C59E0
	sub r3, #0x16
	ldr r4, [r0, #0x0]
	add r0, r1, #0x0
	ldr r1, [r4, #0x8]
	ldr r5, [r4, #0x0]
	mov r4, #0xc
	mul r4, r3
	add r3, r5, r4
	ldr r3, [r3, #0x8]
	blx r3
	pop {r3-r5, pc}
	.balign 4
_0202DA70: .word 0x020EEB40
_0202DA74: .word 0x021C59E0

	thumb_func_start FUN_0202DA78
FUN_0202DA78: ; 0x0202DA78
	ldr r0, _0202DA7C ; =0x0000FFFF
	bx lr
	.balign 4
_0202DA7C: .word 0x0000FFFF

	thumb_func_start FUN_0202DA80
FUN_0202DA80: ; 0x0202DA80
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202DA84
FUN_0202DA84: ; 0x0202DA84
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0202DA88
FUN_0202DA88: ; 0x0202DA88
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_0202DA8C
FUN_0202DA8C: ; 0x0202DA8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202DACA
	ldr r4, _0202DACC ; =0x021C59E0
	mov r1, #0x1
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	strb r1, [r0, #0xc]
	mov r5, #0x0
_0202DAA4:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202DABA
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	ldrb r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0202DACA
_0202DABA:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202DAA4
	mov r1, #0x0
	mov r0, #0xe
	add r2, r1, #0x0
	bl FUN_02030BC4
_0202DACA:
	pop {r3-r5, pc}
	.balign 4
_0202DACC: .word 0x021C59E0

	thumb_func_start FUN_0202DAD0
FUN_0202DAD0: ; 0x0202DAD0
	ldr r0, _0202DAF0 ; =0x021C59E0
	mov r3, #0x0
	ldr r1, [r0, #0x0]
	str r3, [r1, #0x0]
	ldr r1, [r0, #0x0]
	str r3, [r1, #0x4]
	ldr r1, [r0, #0x0]
	str r3, [r1, #0x8]
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	strb r1, [r0, #0x14]
	ldr r3, _0202DAF4 ; =FUN_020311D0
	mov r0, #0xf
	add r1, r2, #0x0
	bx r3
	nop
_0202DAF0: .word 0x021C59E0
_0202DAF4: .word FUN_020311D0

	thumb_func_start FUN_0202DAF8
FUN_0202DAF8: ; 0x0202DAF8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202DB0E
	ldr r0, _0202DB10 ; =0x021C59E0
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	strb r1, [r0, #0xc]
_0202DB0E:
	pop {r4, pc}
	.balign 4
_0202DB10: .word 0x021C59E0

	thumb_func_start FUN_0202DB14
FUN_0202DB14: ; 0x0202DB14
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	bl FUN_020238F4
	str r0, [sp, #0x8]
	ldr r0, _0202DBA0 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202DB9A
	mov r1, #0xe9
	mov r0, #0xf
	lsl r1, r1, #0x2
	bl FUN_02016998
	ldr r1, _0202DBA0 ; =0x021C59E4
	mov r2, #0xe9
	str r0, [r1, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	mov r6, #0x0
	ldr r7, _0202DBA0 ; =0x021C59E4
	add r4, r6, #0x0
	add r5, r6, #0x0
_0202DB4A:
	ldr r1, [r7, #0x0]
	add r0, r1, #0x0
	add r0, #0x28
	add r2, r0, r4
	mov r0, #0xd2
	add r1, r1, r5
	lsl r0, r0, #0x2
	str r2, [r1, r0]
	add r0, r6, #0x0
	bl FUN_0202DE78
	add r6, r6, #0x1
	add r4, #0x68
	add r5, r5, #0x4
	cmp r6, #0x8
	blt _0202DB4A
	ldr r2, _0202DBA0 ; =0x021C59E4
	mov r1, #0x3a
	ldr r3, [r2, #0x0]
	mov r0, #0x0
	lsl r1, r1, #0x4
	strb r0, [r3, r1]
	ldr r4, [r2, #0x0]
	add r3, r1, #0x1
	strb r0, [r4, r3]
	add r3, r1, #0x2
	ldr r4, [r2, #0x0]
	sub r1, #0x58
	strb r0, [r4, r3]
	ldr r3, [r2, #0x0]
	ldr r0, [sp, #0x0]
	str r0, [r3, #0x4]
	ldr r3, [r2, #0x0]
	ldr r0, [sp, #0x4]
	str r0, [r3, #0x0]
	ldr r2, [r2, #0x0]
	ldr r0, [sp, #0x8]
	ldr r1, [r2, r1]
	bl FUN_0202393C
_0202DB9A:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0202DBA0: .word 0x021C59E4

	thumb_func_start FUN_0202DBA4
FUN_0202DBA4: ; 0x0202DBA4
	push {r3-r5, lr}
	ldr r1, _0202DBDC ; =0x021C59E4
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0202DBD8
	mov r4, #0x0
	mov r0, #0xd2
	add r5, r4, #0x0
	add r3, r4, #0x0
	lsl r0, r0, #0x2
_0202DBB8:
	ldr r2, [r1, #0x0]
	add r4, r4, #0x1
	add r2, r2, r5
	add r5, r5, #0x4
	str r3, [r2, r0]
	cmp r4, #0x8
	blt _0202DBB8
	ldr r0, _0202DBDC ; =0x021C59E4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202DBD2
	bl FUN_02016A18
_0202DBD2:
	ldr r0, _0202DBDC ; =0x021C59E4
	mov r1, #0x0
	str r1, [r0, #0x0]
_0202DBD8:
	pop {r3-r5, pc}
	nop
_0202DBDC: .word 0x021C59E4

	thumb_func_start FUN_0202DBE0
FUN_0202DBE0: ; 0x0202DBE0
	push {r3-r7, lr}
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0202DCD8 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_0202881C
	add r7, r0, #0x0
	ldr r0, _0202DCD8 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_020286EC
	str r0, [sp, #0x0]
	ldr r0, _0202DCD8 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_02029AFC
	add r6, r0, #0x0
	ldr r0, _0202DCD8 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_020238F4
	ldr r1, _0202DCD8 ; =0x021C59E4
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x2
	add r2, r2, r1
	mov r1, #0xd2
	lsl r1, r1, #0x2
	ldr r1, [r2, r1]
	bl FUN_0202393C
	mov r0, #0x68
	add r5, r4, #0x0
	mul r5, r0
	ldr r0, _0202DCD8 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	add r0, #0x64
	add r0, r0, r5
	bl OS_GetMacAddress
	add r0, r7, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_020287A8
	ldr r1, _0202DCD8 ; =0x021C59E4
	mov r2, #0x10
	ldr r1, [r1, #0x0]
	add r1, #0x54
	add r1, r1, r5
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl FUN_02029B38
	ldr r1, _0202DCD8 ; =0x021C59E4
	ldr r1, [r1, #0x0]
	add r1, r1, r5
	add r1, #0x6b
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	bl FUN_02029B3C
	ldr r2, _0202DCD8 ; =0x021C59E4
	ldr r1, [r2, #0x0]
	add r1, r1, r5
	add r1, #0x6c
	strb r0, [r1, #0x0]
	ldr r0, [r2, #0x0]
	ldr r0, [r0, #0x4]
	bl FUN_02025C18
	ldr r2, _0202DCD8 ; =0x021C59E4
	ldr r1, [r2, #0x0]
	add r1, r1, r5
	add r1, #0x6d
	strb r0, [r1, #0x0]
	ldr r2, [r2, #0x0]
	mov r0, #0x1
	add r2, #0x6d
	ldrb r1, [r2, r5]
	sub r0, r0, r1
	strb r0, [r2, r5]
	ldr r0, [sp, #0x0]
	bl FUN_02028228
	ldr r1, _0202DCD8 ; =0x021C59E4
	ldr r1, [r1, #0x0]
	add r1, #0x48
	add r1, r1, r5
	bl FUN_02096CCC
	ldr r0, _0202DCD8 ; =0x021C59E4
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	mov r2, #0x20
	add r0, #0x8
	add r0, r0, r5
	bl MI_CpuFill8
	ldr r0, _0202DCD8 ; =0x021C59E4
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0202DCC4
	add r1, #0x8
	add r1, r1, r5
	bl FUN_02023ACC
_0202DCC4:
	ldr r1, _0202DCD8 ; =0x021C59E4
	mov r0, #0x3
	ldr r1, [r1, #0x0]
	mov r2, #0x68
	add r1, #0x8
	add r1, r1, r5
	bl FUN_02030ADC
	pop {r3-r7, pc}
	nop
_0202DCD8: .word 0x021C59E4

	thumb_func_start FUN_0202DCDC
FUN_0202DCDC: ; 0x0202DCDC
	mov r0, #0x68
	bx lr

	thumb_func_start FUN_0202DCE0
FUN_0202DCE0: ; 0x0202DCE0
	ldr r0, _0202DCF4 ; =0x021C59E4
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0202DCF0
	mov r0, #0x3a
	mov r1, #0x1
	lsl r0, r0, #0x4
	strb r1, [r2, r0]
_0202DCF0:
	bx lr
	nop
_0202DCF4: .word 0x021C59E4

	thumb_func_start FUN_0202DCF8
FUN_0202DCF8: ; 0x0202DCF8
	ldr r0, _0202DD04 ; =0x021C59E4
	ldr r1, [r0, #0x0]
	mov r0, #0x3a
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0202DD04: .word 0x021C59E4

	thumb_func_start FUN_0202DD08
FUN_0202DD08: ; 0x0202DD08
	push {r3-r5, lr}
	ldr r1, _0202DD78 ; =0x021C59E4
	add r4, r2, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0202DD74
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202DD74
	ldr r1, _0202DD78 ; =0x021C59E4
	mov r2, #0x68
	ldr r5, [r1, #0x0]
	add r1, r4, #0x0
	add r1, #0x62
	ldrb r1, [r1, #0x0]
	add r5, #0x8
	add r0, r4, #0x0
	add r3, r1, #0x0
	mul r3, r2
	add r1, r5, r3
	bl MI_CpuCopy8
	add r4, #0x62
	ldr r2, _0202DD78 ; =0x021C59E4
	ldrb r3, [r4, #0x0]
	ldr r0, [r2, #0x0]
	ldr r1, _0202DD7C ; =0x000003A2
	strb r3, [r0, r1]
	add r0, r1, #0x0
	ldr r3, [r2, #0x0]
	sub r0, #0xa
	add r4, r3, r0
	ldrb r3, [r3, r1]
	ldrb r0, [r4, r3]
	cmp r0, #0x2
	bhs _0202DD74
	mov r0, #0x1
	strb r0, [r4, r3]
	ldr r0, [r2, #0x0]
	ldrb r4, [r0, r1]
	bl FUN_02031190
	cmp r4, r0
	bne _0202DD74
	ldr r0, _0202DD78 ; =0x021C59E4
	mov r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
_0202DD74:
	pop {r3-r5, pc}
	nop
_0202DD78: .word 0x021C59E4
_0202DD7C: .word 0x000003A2

	thumb_func_start FUN_0202DD80
FUN_0202DD80: ; 0x0202DD80
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202DDE0 ; =0x021C59E4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0202DDDC
	mov r3, #0x68
	add r4, r5, #0x0
	add r0, r2, #0x0
	mul r4, r3
	add r1, #0x8
	add r1, r1, r4
	add r2, r3, #0x0
	bl MI_CpuCopy8
	ldr r0, _0202DDE0 ; =0x021C59E4
	add r1, r5, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x64
	add r0, r0, r4
	bl FUN_0202EFAC
	ldr r0, _0202DDE0 ; =0x021C59E4
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bl FUN_02031190
	cmp r5, r0
	bne _0202DDD2
	ldr r0, _0202DDE0 ; =0x021C59E4
	mov r2, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	pop {r3-r5, pc}
_0202DDD2:
	ldr r0, _0202DDE0 ; =0x021C59E4
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0202DDE4 ; =0x000003A1
	strb r2, [r1, r0]
_0202DDDC:
	pop {r3-r5, pc}
	nop
_0202DDE0: .word 0x021C59E4
_0202DDE4: .word 0x000003A1

	thumb_func_start FUN_0202DDE8
FUN_0202DDE8: ; 0x0202DDE8
	push {r3-r7, lr}
	ldr r0, _0202DE70 ; =0x021C59E4
	ldr r1, [r0, #0x0]
	ldr r0, _0202DE74 ; =0x000003A1
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0202DDFA
	mov r0, #0x0
	pop {r3-r7, pc}
_0202DDFA:
	mov r0, #0x5
	bl FUN_02031354
	cmp r0, #0x0
	bne _0202DE6C
	mov r4, #0x0
	add r5, r4, #0x0
	add r7, r4, #0x0
_0202DE0A:
	ldr r0, _0202DE70 ; =0x021C59E4
	ldr r2, [r0, #0x0]
	mov r0, #0xe6
	add r1, r2, r4
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202DE4A
	add r0, r2, r5
	add r0, #0x6a
	strb r4, [r0, #0x0]
	ldr r0, _0202DE70 ; =0x021C59E4
	ldr r6, [r0, #0x0]
	bl FUN_02023924
	add r2, r0, #0x0
	mov r0, #0xd2
	add r1, r6, r7
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r6, #0x28
	add r1, r6, r5
	bl MI_CpuCopy8
	ldr r1, _0202DE70 ; =0x021C59E4
	mov r0, #0x4
	ldr r1, [r1, #0x0]
	mov r2, #0x68
	add r1, #0x8
	add r1, r1, r5
	bl FUN_02031000
_0202DE4A:
	add r4, r4, #0x1
	add r5, #0x68
	add r7, r7, #0x4
	cmp r4, #0x8
	blt _0202DE0A
	mov r1, #0x0
	mov r0, #0x5
	add r2, r1, #0x0
	bl FUN_02031000
	ldr r0, _0202DE70 ; =0x021C59E4
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0202DE74 ; =0x000003A1
	strb r2, [r1, r0]
	mov r0, #0x1
	pop {r3-r7, pc}
_0202DE6C:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0202DE70: .word 0x021C59E4
_0202DE74: .word 0x000003A1

	thumb_func_start FUN_0202DE78
FUN_0202DE78: ; 0x0202DE78
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0202DEA0 ; =0x021C59E4
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r1, r1, r0
	mov r0, #0xd2
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bl FUN_02023948
	ldr r0, _0202DEA0 ; =0x021C59E4
	mov r2, #0x0
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	pop {r4, pc}
	nop
_0202DEA0: .word 0x021C59E4

	thumb_func_start FUN_0202DEA4
FUN_0202DEA4: ; 0x0202DEA4
	ldr r1, _0202DEBC ; =0x021C59E4
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _0202DEB8
	mov r0, #0x1
	bx lr
_0202DEB8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202DEBC: .word 0x021C59E4

	thumb_func_start FUN_0202DEC0
FUN_0202DEC0: ; 0x0202DEC0
	ldr r1, _0202DEDC ; =0x021C59E4
	mov r2, #0x1
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x2
	beq _0202DED8
	cmp r0, #0x1
	beq _0202DED8
	mov r2, #0x0
_0202DED8:
	add r0, r2, #0x0
	bx lr
	.balign 4
_0202DEDC: .word 0x021C59E4

	thumb_func_start FUN_0202DEE0
FUN_0202DEE0: ; 0x0202DEE0
	ldr r1, _0202DEF0 ; =0x021C59E4
	mov r2, #0x2
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202DEF0: .word 0x021C59E4

	thumb_func_start FUN_0202DEF4
FUN_0202DEF4: ; 0x0202DEF4
	ldr r1, _0202DF04 ; =0x021C59E4
	mov r2, #0x3
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xe6
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202DF04: .word 0x021C59E4

	thumb_func_start FUN_0202DF08
FUN_0202DF08: ; 0x0202DF08
	ldr r1, _0202DF24 ; =0x021C59E4
	mov r0, #0x0
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	lsl r1, r1, #0x2
_0202DF12:
	ldrb r2, [r3, r1]
	cmp r2, #0x1
	beq _0202DF22
	add r0, r0, #0x1
	add r3, r3, #0x1
	cmp r0, #0x8
	blt _0202DF12
	mov r0, #0xff
_0202DF22:
	bx lr
	.balign 4
_0202DF24: .word 0x021C59E4

	thumb_func_start FUN_0202DF28
FUN_0202DF28: ; 0x0202DF28
	push {r3-r4}
	ldr r1, _0202DF50 ; =0x021C59E4
	mov r0, #0x0
	ldr r4, [r1, #0x0]
	mov r1, #0xe6
	add r3, r0, #0x0
	lsl r1, r1, #0x2
_0202DF36:
	ldrb r2, [r4, r1]
	cmp r2, #0x2
	beq _0202DF40
	cmp r2, #0x3
	bne _0202DF42
_0202DF40:
	add r0, r0, #0x1
_0202DF42:
	add r3, r3, #0x1
	add r4, r4, #0x1
	cmp r3, #0x8
	blt _0202DF36
	pop {r3-r4}
	bx lr
	nop
_0202DF50: .word 0x021C59E4

	thumb_func_start FUN_0202DF54
FUN_0202DF54: ; 0x0202DF54
	push {r4-r6, lr}
	ldr r0, _0202DFA0 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202DF9C
	bl FUN_02030F20
	cmp r0, #0x0
	beq _0202DF9C
	mov r6, #0xe6
	ldr r4, _0202DFA0 ; =0x021C59E4
	mov r5, #0x0
	lsl r6, r6, #0x2
_0202DF6E:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202DF96
	cmp r5, #0x0
	bne _0202DF86
	bl FUN_02031280
	cmp r0, #0x0
	bne _0202DF96
_0202DF86:
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	ldrb r0, [r0, r6]
	cmp r0, #0x0
	beq _0202DF96
	add r0, r5, #0x0
	bl FUN_0202DE78
_0202DF96:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202DF6E
_0202DF9C:
	pop {r4-r6, pc}
	nop
_0202DFA0: .word 0x021C59E4

	thumb_func_start FUN_0202DFA4
FUN_0202DFA4: ; 0x0202DFA4
	ldr r1, _0202DFD4 ; =0x021C59E4
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	bne _0202DFB0
	mov r0, #0x0
	bx lr
_0202DFB0:
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x1
	beq _0202DFC4
	cmp r1, #0x2
	beq _0202DFC4
	cmp r1, #0x3
	bne _0202DFD0
_0202DFC4:
	lsl r0, r0, #0x2
	add r1, r3, r0
	mov r0, #0xd2
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	bx lr
_0202DFD0:
	mov r0, #0x0
	bx lr
	.balign 4
_0202DFD4: .word 0x021C59E4

	thumb_func_start FUN_0202DFD8
FUN_0202DFD8: ; 0x0202DFD8
	ldr r1, _0202DFF8 ; =0x021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202DFF2
	mov r1, #0x68
	add r3, #0x48
	mul r1, r0
	add r0, r3, r1
	bx lr
_0202DFF2:
	mov r0, #0x0
	bx lr
	nop
_0202DFF8: .word 0x021C59E4

	thumb_func_start FUN_0202DFFC
FUN_0202DFFC: ; 0x0202DFFC
	ldr r1, _0202E01C ; =0x021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E016
	mov r1, #0x68
	add r3, #0x54
	mul r1, r0
	add r0, r3, r1
	bx lr
_0202E016:
	mov r0, #0x0
	bx lr
	nop
_0202E01C: .word 0x021C59E4

	thumb_func_start FUN_0202E020
FUN_0202E020: ; 0x0202E020
	ldr r1, _0202E040 ; =0x021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E03C
	mov r1, #0x68
	mul r1, r0
	add r0, r3, r1
	add r0, #0x6b
	ldrb r0, [r0, #0x0]
	bx lr
_0202E03C:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E040: .word 0x021C59E4

	thumb_func_start FUN_0202E044
FUN_0202E044: ; 0x0202E044
	ldr r1, _0202E064 ; =0x021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E060
	mov r1, #0x68
	mul r1, r0
	add r0, r3, r1
	add r0, #0x6c
	ldrb r0, [r0, #0x0]
	bx lr
_0202E060:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E064: .word 0x021C59E4

	thumb_func_start FUN_0202E068
FUN_0202E068: ; 0x0202E068
	ldr r1, _0202E088 ; =0x021C59E4
	ldr r3, [r1, #0x0]
	mov r1, #0xe6
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E084
	mov r1, #0x68
	mul r1, r0
	add r0, r3, r1
	add r0, #0x6d
	ldrb r0, [r0, #0x0]
	bx lr
_0202E084:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E088: .word 0x021C59E4

	thumb_func_start FUN_0202E08C
FUN_0202E08C: ; 0x0202E08C
	push {r4-r6, lr}
	mov r4, #0x0
	add r5, r4, #0x0
	add r6, r4, #0x0
_0202E094:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202E0E8
	ldr r0, _0202E0F4 ; =0x021C59E4
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xe6
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202E0E8
	add r0, r4, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202E0E8
	ldr r0, _0202E0F4 ; =0x021C59E4
	ldr r1, _0202E0F8 ; =0x00000399
	ldr r0, [r0, #0x0]
	add r2, r0, r4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E0E8
	add r1, r6, #0x0
	add r2, r0, r5
_0202E0D0:
	add r3, r2, #0x0
	add r3, #0x70
	ldrb r0, [r2, #0x8]
	ldrb r3, [r3, #0x0]
	cmp r0, r3
	beq _0202E0E0
	mov r0, #0x0
	pop {r4-r6, pc}
_0202E0E0:
	add r1, r1, #0x1
	add r2, r2, #0x1
	cmp r1, #0x20
	blt _0202E0D0
_0202E0E8:
	add r4, r4, #0x1
	add r5, #0x68
	cmp r4, #0x7
	blt _0202E094
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0202E0F4: .word 0x021C59E4
_0202E0F8: .word 0x00000399

	thumb_func_start FUN_0202E0FC
FUN_0202E0FC: ; 0x0202E0FC
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldr r0, _0202E1B4 ; =0x021C59E4
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202E1B0
	cmp r7, #0x2
	beq _0202E11C
	bl FUN_02031190
	bl FUN_020313CC
	mov r1, #0x1
	and r0, r1
	str r0, [sp, #0x0]
_0202E11C:
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _0202E1B0
	add r5, r4, #0x0
_0202E128:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202E1A4
	ldr r0, _0202E1B4 ; =0x021C59E4
	mov r1, #0xe6
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x2
	add r2, r0, r4
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0202E1A4
	cmp r7, #0x0
	bne _0202E16E
	add r0, r4, #0x0
	bl FUN_020313CC
	mov r1, #0x1
	and r1, r0
	ldr r0, [sp, #0x0]
	cmp r0, r1
	beq _0202E1A4
	ldr r0, _0202E1B4 ; =0x021C59E4
	mov r1, #0xda
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x2
	add r0, r0, r5
	ldrh r1, [r0, r1]
	add r2, r1, r6
	mov r1, #0xda
	lsl r1, r1, #0x2
	strh r2, [r0, r1]
	b _0202E1A4
_0202E16E:
	cmp r7, #0x1
	bne _0202E194
	add r0, r4, #0x0
	bl FUN_020313CC
	mov r1, #0x1
	and r1, r0
	ldr r0, [sp, #0x0]
	cmp r0, r1
	beq _0202E1A4
	ldr r0, _0202E1B4 ; =0x021C59E4
	ldr r1, _0202E1B8 ; =0x0000036A
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	ldrh r1, [r0, r1]
	add r2, r1, r6
	ldr r1, _0202E1B8 ; =0x0000036A
	strh r2, [r0, r1]
	b _0202E1A4
_0202E194:
	mov r1, #0xdb
	add r0, r0, r5
	lsl r1, r1, #0x2
	ldrh r1, [r0, r1]
	add r2, r1, r6
	mov r1, #0xdb
	lsl r1, r1, #0x2
	strh r2, [r0, r1]
_0202E1A4:
	add r5, r5, #0x6
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _0202E128
_0202E1B0:
	pop {r3-r7, pc}
	nop
_0202E1B4: .word 0x021C59E4
_0202E1B8: .word 0x0000036A

	thumb_func_start FUN_0202E1BC
FUN_0202E1BC: ; 0x0202E1BC
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r0, #0x0
	bl FUN_020286EC
	str r0, [sp, #0x4]
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _0202E224
	add r5, r4, #0x0
_0202E1D4:
	add r0, r4, #0x0
	bl FUN_0202DFD8
	add r1, r0, #0x0
	beq _0202E218
	add r0, r7, #0x0
	add r2, sp, #0x8
	bl FUN_02033874
	cmp r0, #0x0
	beq _0202E1EE
	cmp r0, #0x1
	bne _0202E218
_0202E1EE:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bge _0202E1F8
	bl ErrorHandling
_0202E1F8:
	ldr r0, _0202E254 ; =0x021C59E4
	mov r2, #0xda
	ldr r0, [r0, #0x0]
	ldr r3, _0202E258 ; =0x0000036A
	add r6, r0, r5
	mov r0, #0xdb
	lsl r0, r0, #0x2
	ldrh r0, [r6, r0]
	lsl r2, r2, #0x2
	str r0, [sp, #0x0]
	ldrh r2, [r6, r2]
	ldrh r3, [r6, r3]
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	bl FUN_02028608
_0202E218:
	add r5, r5, #0x6
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _0202E1D4
_0202E224:
	mov r3, #0xda
	mov r2, #0x0
	lsl r3, r3, #0x2
	ldr r6, _0202E254 ; =0x021C59E4
	add r1, r2, #0x0
	add r0, r2, #0x0
	add r4, r3, #0x2
	add r5, r3, #0x4
_0202E234:
	ldr r7, [r6, #0x0]
	add r2, r2, #0x1
	add r7, r7, r1
	strh r0, [r7, r3]
	ldr r7, [r6, #0x0]
	add r7, r7, r1
	strh r0, [r7, r4]
	ldr r7, [r6, #0x0]
	add r7, r7, r1
	add r1, r1, #0x6
	strh r0, [r7, r5]
	cmp r2, #0x8
	blt _0202E234
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0202E254: .word 0x021C59E4
_0202E258: .word 0x0000036A

	thumb_func_start FUN_0202E25C
FUN_0202E25C: ; 0x0202E25C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x1
	bne _0202E26E
	mov r0, #0x0
	mov r1, #0x1
	bl FUN_0202E0FC
	b _0202E27E
_0202E26E:
	mov r0, #0x0
	mvn r0, r0
	cmp r1, r0
	bne _0202E27E
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0202E0FC
_0202E27E:
	add r0, r4, #0x0
	bl FUN_0202E1BC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202E288
FUN_0202E288: ; 0x0202E288
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_0202E0FC
	add r0, r4, #0x0
	bl FUN_0202E1BC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202E29C
FUN_0202E29C: ; 0x0202E29C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0202E334 ; =0x021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0202E332
	mov r1, #0xdb
	mov r0, #0xf
	lsl r1, r1, #0x4
	bl FUN_02016998
	ldr r1, _0202E334 ; =0x021C59E8
	mov r2, #0xdb
	str r0, [r1, #0x8]
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl MI_CpuFill8
	bl FUN_0202CEEC
	add r1, r0, #0x0
	mov r0, #0xf
	bl FUN_02016998
	ldr r1, _0202E334 ; =0x021C59E8
	ldr r2, [r1, #0x8]
	ldr r1, _0202E338 ; =0x00000CA4
	str r0, [r2, r1]
	bl FUN_0202CEEC
	add r2, r0, #0x0
	ldr r0, _0202E334 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E338 ; =0x00000CA4
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl MI_CpuFill8
	bl FUN_02023AC4
	add r1, r0, #0x0
	mov r0, #0xf
	bl FUN_02016998
	ldr r1, _0202E334 ; =0x021C59E8
	ldr r2, [r1, #0x8]
	ldr r1, _0202E33C ; =0x00000CBC
	str r0, [r2, r1]
	bl FUN_02023AC4
	add r2, r0, #0x0
	ldr r0, _0202E334 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E33C ; =0x00000CBC
	ldr r0, [r1, r0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r2, _0202E334 ; =0x021C59E8
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
_0202E334: .word 0x021C59E8
_0202E338: .word 0x00000CA4
_0202E33C: .word 0x00000CBC
_0202E340: .word 0x00000333

	thumb_func_start FUN_0202E344
FUN_0202E344: ; 0x0202E344
	ldr r0, _0202E354 ; =0x021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202E350
	mov r0, #0x1
	bx lr
_0202E350:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E354: .word 0x021C59E8

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
	ldr r0, _0202E464 ; =0x021C59E8
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
	ldr r2, _0202E464 ; =0x021C59E8
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
	ldr r0, _0202E464 ; =0x021C59E8
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
	ldr r2, _0202E464 ; =0x021C59E8
	add r3, r1, #0x0
	ldr r4, [r2, #0x8]
	mov r2, #0xc0
	add r4, #0x54
	mul r3, r2
	add r0, r7, #0x0
	add r1, r4, r3
	bl MI_CpuCopy8
	ldr r0, _0202E464 ; =0x021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E46C ; =0x00000CB4
	strb r2, [r1, r0]
_0202E460:
	pop {r3-r7, pc}
	nop
_0202E464: .word 0x021C59E8
_0202E468: .word 0x00000C84
_0202E46C: .word 0x00000CB4

	thumb_func_start FUN_0202E470
FUN_0202E470: ; 0x0202E470
	push {r3, lr}
	cmp r1, #0x0
	beq _0202E47A
	bl OS_Terminate
_0202E47A:
	ldr r0, _0202E484 ; =0x021C59E8
	mov r1, #0x2
	str r1, [r0, #0x4]
	pop {r3, pc}
	nop
_0202E484: .word 0x021C59E8

	thumb_func_start FUN_0202E488
FUN_0202E488: ; 0x0202E488
	ldr r0, _0202E494 ; =0x021C59E8
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r3, _0202E498 ; =FUN_02016454
	mov r0, #0x4
	bx r3
	.balign 4
_0202E494: .word 0x021C59E8
_0202E498: .word FUN_02016454

	thumb_func_start FUN_0202E49C
FUN_0202E49C: ; 0x0202E49C
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02016444
	ldr r0, _0202E4C0 ; =0x021C59E8
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
_0202E4C0: .word 0x021C59E8
_0202E4C4: .word FUN_0202E470

	thumb_func_start FUN_0202E4C8
FUN_0202E4C8: ; 0x0202E4C8
	ldr r0, _0202E4D8 ; =0x021C59E8
	ldr r0, [r0, #0x4]
	cmp r0, #0x2
	bne _0202E4D4
	mov r0, #0x1
	bx lr
_0202E4D4:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E4D8: .word 0x021C59E8

	thumb_func_start FUN_0202E4DC
FUN_0202E4DC: ; 0x0202E4DC
	ldr r0, _0202E4EC ; =0x021C59E8
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202E4E8
	mov r0, #0x1
	bx lr
_0202E4E8:
	mov r0, #0x0
	bx lr
	.balign 4
_0202E4EC: .word 0x021C59E8

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
	ldr r1, _0202E534 ; =0x021C59E8
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
	ldr r0, _0202E534 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	mov r0, #0x33
	lsl r0, r0, #0x6
	ldr r0, [r1, r0]
	bl FUN_0202CB70
	pop {r3, pc}
	.balign 4
_0202E534: .word 0x021C59E8

	thumb_func_start FUN_0202E538
FUN_0202E538: ; 0x0202E538
	push {r3-r5, lr}
	mov r4, #0x0
	ldr r2, _0202E564 ; =0x021C59E8
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
	ldr r0, _0202E564 ; =0x021C59E8
	mov r2, #0x3
	ldr r0, [r0, #0x8]
	lsl r2, r2, #0xa
	add r0, #0x54
	bl MI_CpuFill8
	pop {r3-r5, pc}
	nop
_0202E564: .word 0x021C59E8
_0202E568: .word 0x00000C84

	thumb_func_start FUN_0202E56C
FUN_0202E56C: ; 0x0202E56C
	push {r3-r4}
	ldr r1, _0202E58C ; =0x021C59E8
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
_0202E58C: .word 0x021C59E8
_0202E590: .word 0x00000DAD

	thumb_func_start FUN_0202E594
FUN_0202E594: ; 0x0202E594
	push {r4-r5}
	ldr r1, _0202E5F0 ; =0x021C59E8
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
_0202E5F0: .word 0x021C59E8
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
	ldr r0, _0202E65C ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E660 ; =0x00000DAB
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0202E62A
	ldr r0, _0202E664 ; =FUN_020303BC
	mov r1, #0xe
	bl FUN_0202D0A0
	ldr r0, _0202E65C ; =0x021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E660 ; =0x00000DAB
	strb r2, [r1, r0]
_0202E62A:
	ldr r0, _0202E65C ; =0x021C59E8
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
_0202E65C: .word 0x021C59E8
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
	ldr r0, _0202E6DC ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E6E0 ; =0x00000DAB
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0202E69C
	ldr r0, _0202E6E4 ; =FUN_02030238
	mov r1, #0xe
	bl FUN_0202D0A0
	ldr r0, _0202E6DC ; =0x021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E6E0 ; =0x00000DAB
	strb r2, [r1, r0]
_0202E69C:
	bl FUN_0202CBD4
	cmp r0, #0x1
	bne _0202E6D4
	ldr r2, _0202E6E8 ; =0x020EEC40
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
_0202E6DC: .word 0x021C59E8
_0202E6E0: .word 0x00000DAB
_0202E6E4: .word FUN_02030238
_0202E6E8: .word 0x020EEC40
_0202E6EC: .word FUN_0202E380

	thumb_func_start FUN_0202E6F0
FUN_0202E6F0: ; 0x0202E6F0
	push {r3, lr}
	ldr r0, _0202E77C ; =0x021C59E8
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
	ldr r0, _0202E77C ; =0x021C59E8
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
	ldr r0, _0202E77C ; =0x021C59E8
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
	ldr r0, _0202E77C ; =0x021C59E8
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
	ldr r0, _0202E77C ; =0x021C59E8
	mov r2, #0x1
	ldr r1, [r0, #0x8]
	ldr r0, _0202E780 ; =0x00000DAC
	strb r2, [r1, r0]
_0202E776:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0202E77C: .word 0x021C59E8
_0202E780: .word 0x00000DAC

	thumb_func_start FUN_0202E784
FUN_0202E784: ; 0x0202E784
	push {r3, lr}
	ldr r0, _0202E7A8 ; =0x021C59E8
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
_0202E7A8: .word 0x021C59E8
_0202E7AC: .word 0x00000DAA

	thumb_func_start FUN_0202E7B0
FUN_0202E7B0: ; 0x0202E7B0
	push {r3, lr}
	ldr r1, _0202E7D0 ; =0x021C59E8
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
_0202E7D0: .word 0x021C59E8
_0202E7D4: .word 0x00000DAA

	thumb_func_start FUN_0202E7D8
FUN_0202E7D8: ; 0x0202E7D8
	push {r3, lr}
	ldr r0, _0202E804 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E808 ; =0x00000CBC
	ldr r0, [r1, r0]
	bl FUN_02016A18
	ldr r0, _0202E804 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E80C ; =0x00000CA4
	ldr r0, [r1, r0]
	bl FUN_02016A18
	ldr r0, _0202E804 ; =0x021C59E8
	ldr r0, [r0, #0x8]
	bl FUN_02016A18
	ldr r0, _0202E804 ; =0x021C59E8
	mov r1, #0x0
	str r1, [r0, #0x8]
	pop {r3, pc}
	nop
_0202E804: .word 0x021C59E8
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
	ldr r1, _0202E83C ; =0x021C59E8
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
_0202E83C: .word 0x021C59E8
_0202E840: .word 0x00000C84

	thumb_func_start FUN_0202E844
FUN_0202E844: ; 0x0202E844
	push {r3-r5, lr}
	ldr r1, _0202E870 ; =0x021C59E8
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
_0202E870: .word 0x021C59E8
_0202E874: .word 0x00000C84

	thumb_func_start FUN_0202E878
FUN_0202E878: ; 0x0202E878
	ldr r0, _0202E884 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202E888 ; =0x00000CB4
	ldrb r0, [r1, r0]
	bx lr
	nop
_0202E884: .word 0x021C59E8
_0202E888: .word 0x00000CB4

	thumb_func_start FUN_0202E88C
FUN_0202E88C: ; 0x0202E88C
	ldr r0, _0202E898 ; =0x021C59E8
	mov r2, #0x0
	ldr r1, [r0, #0x8]
	ldr r0, _0202E89C ; =0x00000CB4
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0202E898: .word 0x021C59E8
_0202E89C: .word 0x00000CB4

	thumb_func_start FUN_0202E8A0
FUN_0202E8A0: ; 0x0202E8A0
	ldr r1, _0202E8C8 ; =0x021C59E8
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
_0202E8C8: .word 0x021C59E8
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
	ldr r7, _0202E948 ; =0x021C59E8
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
_0202E948: .word 0x021C59E8
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
	ldr r7, _0202E9A4 ; =0x021C59E8
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
_0202E9A4: .word 0x021C59E8
_0202E9A8: .word 0x00000C84

	thumb_func_start FUN_0202E9AC
FUN_0202E9AC: ; 0x0202E9AC
	push {r4-r6, lr}
	add r4, r1, #0x0
	ldr r1, _0202E9E0 ; =0x021C59E8
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
	bl FUN_0202393C
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
_0202E9E0: .word 0x021C59E8
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
	ldr r1, _0202EA4C ; =0x021C59E8
	ldr r3, [r1, #0x8]
	add r1, r3, r4
	add r1, #0x8a
	ldrh r2, [r1, #0x0]
	ldr r1, _0202EA50 ; =0x00000DA8
	strb r2, [r3, r1]
	bl FUN_0202D8B0
	cmp r0, #0x0
	beq _0202EA36
	ldr r1, _0202EA4C ; =0x021C59E8
	mov r0, #0x1
	ldr r1, [r1, #0x8]
	mov r2, #0x0
	add r1, #0x58
	add r1, r1, r4
	bl FUN_0202C4D8
	b _0202EA44
_0202EA36:
	ldr r1, _0202EA4C ; =0x021C59E8
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
_0202EA4C: .word 0x021C59E8
_0202EA50: .word 0x00000DA8

	thumb_func_start FUN_0202EA54
FUN_0202EA54: ; 0x0202EA54
	push {r4-r7}
	mov r4, #0x0
	ldr r1, _0202EA90 ; =0x021C59E8
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
_0202EA90: .word 0x021C59E8
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
	ldr r0, _0202EB6C ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB70 ; =0x00000CC4
	add r5, r1, r0
	bl FUN_02023AC4
	cmp r0, #0x20
	ble _0202EAC2
	bl ErrorHandling
_0202EAC2:
	bl FUN_02023924
	cmp r0, #0x20
	beq _0202EACE
	bl ErrorHandling
_0202EACE:
	bl FUN_02023924
	add r1, r5, #0x0
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r1, #0x10
	bl MI_CpuCopy8
	bl FUN_02023AC4
	add r2, r0, #0x0
	ldr r0, _0202EB6C ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB74 ; =0x00000CBC
	ldr r0, [r1, r0]
	add r1, r5, #0x0
	add r1, #0x30
	bl MI_CpuCopy8
	add r0, r4, #0x0
	bl FUN_020239BC
	str r0, [r5, #0x0]
	bl FUN_02033534
	strb r0, [r5, #0x4]
	bl FUN_0203354C
	strb r0, [r5, #0x5]
	ldr r0, _0202EB6C ; =0x021C59E8
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
	ldr r1, _0202EB6C ; =0x021C59E8
	ldr r4, [r1, #0x8]
	ldr r1, _0202EB70 ; =0x00000CC4
	add r5, r4, r1
	bl FUN_020239BC
	ldr r1, _0202EB70 ; =0x00000CC4
	str r0, [r4, r1]
	bl FUN_02033534
	strb r0, [r5, #0x4]
	bl FUN_0203354C
	strb r0, [r5, #0x5]
	ldr r0, _0202EB6C ; =0x021C59E8
	add r5, #0x8
	ldr r0, [r0, #0x8]
	add r1, r5, #0x0
	mov r2, #0x54
	bl MI_CpuCopy8
_0202EB4E:
	ldr r0, _0202EB6C ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB70 ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl DC_FlushRange
	ldr r0, _0202EB6C ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EB70 ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl FUN_0202CB7C
	pop {r3-r5, pc}
	.balign 4
_0202EB6C: .word 0x021C59E8
_0202EB70: .word 0x00000CC4
_0202EB74: .word 0x00000CBC
_0202EB78: .word 0x00000CA8

	thumb_func_start FUN_0202EB7C
FUN_0202EB7C: ; 0x0202EB7C
	push {r4, lr}
	ldr r0, _0202EBC8 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EBCC ; =0x00000CC4
	add r4, r1, r0
	bl FUN_0202EDB8
	ldrb r1, [r4, #0x6]
	cmp r1, r0
	beq _0202EBC6
	bl FUN_0202EDB8
	strb r0, [r4, #0x6]
	ldr r0, _0202EBC8 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EBCC ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl DC_FlushRange
	ldr r0, _0202EBC8 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EBCC ; =0x00000CC4
	add r0, r1, r0
	mov r1, #0x5c
	bl FUN_0202CB7C
	ldr r3, _0202EBC8 ; =0x021C59E8
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
_0202EBC8: .word 0x021C59E8
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
	ldr r0, _0202ED50 ; =0x021C59E8
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
	ldr r0, _0202ED50 ; =0x021C59E8
	ldr r1, _0202ED58 ; =0x0000FFFF
	ldr r3, [r0, #0x8]
	ldr r0, _0202ED5C ; =0x00000DA6
	ldrh r2, [r3, r0]
	cmp r2, r1
	bne _0202EC1C
	strh r4, [r3, r0]
_0202EC1C:
	ldr r0, _0202ED50 ; =0x021C59E8
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
	ldr r0, _0202ED50 ; =0x021C59E8
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
	ldr r0, _0202ED50 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202ED60 ; =0x00000DAA
	ldrb r0, [r1, r0]
	cmp r0, #0x1
	bne _0202ECA2
	bl FUN_0202D178
	cmp r0, #0x0
	bne _0202ED4C
_0202ECA2:
	ldr r0, _0202ED50 ; =0x021C59E8
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
	ldr r0, _0202ED50 ; =0x021C59E8
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
	ldr r3, _0202ED50 ; =0x021C59E8
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
	ldr r1, _0202ED50 ; =0x021C59E8
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
	ldr r1, _0202ED50 ; =0x021C59E8
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
	ldr r0, _0202ED50 ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202ED6C ; =0x00000DA8
	strb r5, [r1, r0]
_0202ED4C:
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_0202ED50: .word 0x021C59E8
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
	ldr r1, _0202ED80 ; =0x021C59E8
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	beq _0202ED7E
	bl FUN_0202EBD0
_0202ED7E:
	pop {r3, pc}
	.balign 4
_0202ED80: .word 0x021C59E8

	thumb_func_start FUN_0202ED84
FUN_0202ED84: ; 0x0202ED84
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0202EDB4 ; =0x021C59E8
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
_0202EDB4: .word 0x021C59E8

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
	ldr r0, _0202EDF0 ; =0x021C59E8
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
_0202EDF0: .word 0x021C59E8
_0202EDF4: .word 0x00000DAA

	thumb_func_start FUN_0202EDF8
FUN_0202EDF8: ; 0x0202EDF8
	ldr r0, _0202EE08 ; =0x021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EE04
	mov r0, #0x1
	bx lr
_0202EE04:
	mov r0, #0x0
	bx lr
	.balign 4
_0202EE08: .word 0x021C59E8

	thumb_func_start FUN_0202EE0C
FUN_0202EE0C: ; 0x0202EE0C
	push {r3, lr}
	ldr r0, _0202EE20 ; =0x021C59E8
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EE1C
	bl FUN_0202D1C8
	pop {r3, pc}
_0202EE1C:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4
_0202EE20: .word 0x021C59E8

	thumb_func_start FUN_0202EE24
FUN_0202EE24: ; 0x0202EE24
	push {r3, lr}
	ldr r0, _0202EE3C ; =0x021C59E8
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
_0202EE3C: .word 0x021C59E8
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
	ldr r0, _0202EE7C ; =0x021C59E8
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
_0202EE7C: .word 0x021C59E8
_0202EE80: .word 0x00000DAD

	thumb_func_start FUN_0202EE84
FUN_0202EE84: ; 0x0202EE84
	push {r3-r4}
	ldr r1, _0202EEA8 ; =0x021C59E8
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
_0202EEA8: .word 0x021C59E8
_0202EEAC: .word 0x00000DAD

	thumb_func_start FUN_0202EEB0
FUN_0202EEB0: ; 0x0202EEB0
	push {r4-r5}
	ldr r5, _0202EEDC ; =0x021C59E8
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
_0202EEDC: .word 0x021C59E8
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
	ldr r1, _0202EF3C ; =0x021C59E8
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
_0202EF3C: .word 0x021C59E8
_0202EF40: .word 0x00000C84

	thumb_func_start FUN_0202EF44
FUN_0202EF44: ; 0x0202EF44
	ldr r1, _0202EF68 ; =0x021C59E8
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
_0202EF68: .word 0x021C59E8
_0202EF6C: .word 0x00000C84

	thumb_func_start FUN_0202EF70
FUN_0202EF70: ; 0x0202EF70
	ldr r0, _0202EF7C ; =0x021C59E8
	ldr r1, [r0, #0x8]
	ldr r0, _0202EF80 ; =0x00000CB8
	ldr r0, [r1, r0]
	bx lr
	nop
_0202EF7C: .word 0x021C59E8
_0202EF80: .word 0x00000CB8

	thumb_func_start FUN_0202EF84
FUN_0202EF84: ; 0x0202EF84
	ldr r1, _0202EFA4 ; =0x021C59E8
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
_0202EFA4: .word 0x021C59E8
_0202EFA8: .word 0x00000C84

	thumb_func_start FUN_0202EFAC
FUN_0202EFAC: ; 0x0202EFAC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202EFDC ; =0x021C59E8
	add r4, r1, #0x0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202EFD8
	cmp r4, #0x8
	blt _0202EFC2
	bl ErrorHandling
_0202EFC2:
	ldr r1, _0202EFDC ; =0x021C59E8
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
_0202EFDC: .word 0x021C59E8
_0202EFE0: .word 0x00000C54

	thumb_func_start FUN_0202EFE4
FUN_0202EFE4: ; 0x0202EFE4
	push {r4-r5}
	ldr r2, _0202F034 ; =0x021C59E8
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
_0202F034: .word 0x021C59E8
_0202F038: .word 0x00000C54

	thumb_func_start FUN_0202F03C
FUN_0202F03C: ; 0x0202F03C
	ldr r0, _0202F054 ; =0x021C59E8
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
_0202F054: .word 0x021C59E8
_0202F058: .word 0x00000DAD

	thumb_func_start FUN_0202F05C
FUN_0202F05C: ; 0x0202F05C
	ldr r0, _0202F070 ; =0x021C59E8
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
_0202F070: .word 0x021C59E8
_0202F074: .word 0x00000DAD

	thumb_func_start FUN_0202F078
FUN_0202F078: ; 0x0202F078
	ldr r1, _0202F088 ; =0x021C59E8
	ldr r3, _0202F08C ; =MI_CpuCopy8
	ldr r2, [r1, #0x8]
	ldr r1, _0202F090 ; =0x00000CA8
	add r1, r2, r1
	mov r2, #0x8
	bx r3
	nop
_0202F088: .word 0x021C59E8
_0202F08C: .word MI_CpuCopy8
_0202F090: .word 0x00000CA8

	thumb_func_start FUN_0202F094
FUN_0202F094: ; 0x0202F094
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02023AC4
	ldr r1, _0202F0B0 ; =0x021C59E8
	add r2, r0, #0x0
	ldr r3, [r1, #0x8]
	ldr r1, _0202F0B4 ; =0x00000CBC
	add r0, r4, #0x0
	ldr r1, [r3, r1]
	bl MI_CpuCopy8
	pop {r4, pc}
	nop
_0202F0B0: .word 0x021C59E8
_0202F0B4: .word 0x00000CBC

	thumb_func_start FUN_0202F0B8
FUN_0202F0B8: ; 0x0202F0B8
	push {r4, lr}
	bl FUN_0202EA9C
	ldr r3, _0202F0D4 ; =0x021C59E8
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
_0202F0D4: .word 0x021C59E8
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
	ldr r1, _0202F120 ; =0x021C59E8
	mov r2, #0x54
	ldr r1, [r1, #0x8]
	bl MI_CpuCopy8
	bl FUN_0202F0B8
	pop {r3, pc}
	nop
_0202F120: .word 0x021C59E8

	thumb_func_start FUN_0202F124
FUN_0202F124: ; 0x0202F124
	ldr r1, _0202F148 ; =0x021C59E8
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
_0202F148: .word 0x021C59E8
_0202F14C: .word 0x00000C84

	thumb_func_start FUN_0202F150
FUN_0202F150: ; 0x0202F150
	push {r4-r6, lr}
	add r6, r1, #0x0
	mov r4, #0x0
	ldr r1, _0202F2BC ; =0x021C59F4
	cmp r0, #0x0
	strb r4, [r1, #0x0]
	beq _0202F25C
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r5, r0, #0x1
	ldr r0, _0202F2BC ; =0x021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202F178
	mov r0, #0x1
	pop {r4-r6, pc}
_0202F178:
	mov r0, #0xf
	bl FUN_02031480
	ldr r1, _0202F2C0 ; =0x0000068C
	mov r0, #0xf
	bl FUN_02016998
	ldr r1, _0202F2BC ; =0x021C59F4
	ldr r2, _0202F2C0 ; =0x0000068C
	str r0, [r1, #0x4]
	add r1, r4, #0x0
	bl MI_CpuFill8
	ldr r2, _0202F2BC ; =0x021C59F4
	ldr r1, _0202F2C4 ; =0x00000658
	ldr r0, [r2, #0x4]
	add r6, #0x40
	str r6, [r0, r1]
	add r0, r1, #0x0
	ldr r3, [r2, #0x4]
	add r6, r4, #0x0
	add r0, #0x25
	strb r6, [r3, r0]
	add r0, r1, #0x0
	ldr r3, [r2, #0x4]
	mov r6, #0x1b
	add r0, #0x26
	strb r6, [r3, r0]
	ldr r2, [r2, #0x4]
	mov r0, #0xf
	ldr r1, [r2, r1]
	lsl r1, r1, #0x1
	bl FUN_02016998
	ldr r2, _0202F2BC ; =0x021C59F4
	ldr r1, _0202F2C8 ; =0x0000045C
	ldr r3, [r2, #0x4]
	str r0, [r3, r1]
	ldr r2, [r2, #0x4]
	ldr r1, _0202F2C4 ; =0x00000658
	mov r0, #0xf
	ldr r1, [r2, r1]
	bl FUN_02016998
	ldr r2, _0202F2BC ; =0x021C59F4
	mov r1, #0x46
	ldr r3, [r2, #0x4]
	lsl r1, r1, #0x4
	str r0, [r3, r1]
	ldr r2, [r2, #0x4]
	ldr r1, _0202F2C4 ; =0x00000658
	mov r0, #0xf
	ldr r1, [r2, r1]
	mul r1, r5
	bl FUN_02016998
	ldr r2, _0202F2BC ; =0x021C59F4
	ldr r1, _0202F2CC ; =0x00000458
	ldr r3, [r2, #0x4]
	str r0, [r3, r1]
	ldr r2, [r2, #0x4]
	ldr r1, _0202F2C4 ; =0x00000658
	mov r0, #0xf
	ldr r1, [r2, r1]
	mul r1, r5
	bl FUN_02016998
	ldr r1, _0202F2BC ; =0x021C59F4
	ldr r2, [r1, #0x4]
	ldr r1, _0202F2D0 ; =0x00000454
	str r0, [r2, r1]
	bl FUN_02033534
	cmp r0, #0xa
	ldr r2, _0202F2D4 ; =0x0000054C
	bne _0202F236
	ldr r0, _0202F2BC ; =0x021C59F4
	mov r1, #0x64
	ldr r3, [r0, #0x4]
	add r0, r3, r2
	sub r2, #0xe8
	add r2, r3, r2
	bl FUN_0202D7D8
	ldr r0, _0202F2BC ; =0x021C59F4
	mov r1, #0x32
	ldr r3, [r0, #0x4]
	ldr r2, _0202F2D8 ; =0x0000056C
	lsl r1, r1, #0x4
	add r0, r3, r2
	sub r2, #0x90
	add r2, r3, r2
	bl FUN_0202D7D8
	b _0202F268
_0202F236:
	ldr r0, _0202F2BC ; =0x021C59F4
	mov r1, #0x14
	ldr r3, [r0, #0x4]
	add r0, r3, r2
	sub r2, #0xe8
	add r2, r3, r2
	bl FUN_0202D7D8
	ldr r0, _0202F2BC ; =0x021C59F4
	add r1, r6, #0x0
	ldr r3, [r0, #0x4]
	ldr r2, _0202F2D8 ; =0x0000056C
	add r1, #0xfd
	add r0, r3, r2
	sub r2, #0x90
	add r2, r3, r2
	bl FUN_0202D7D8
	b _0202F268
_0202F25C:
	ldr r0, [r1, #0x4]
	mov r4, #0x1
	cmp r0, #0x0
	bne _0202F268
	bl ErrorHandling
_0202F268:
	ldr r2, _0202F2BC ; =0x021C59F4
	ldr r1, _0202F2DC ; =0x0000065C
	ldr r3, [r2, #0x4]
	mov r0, #0x0
	strh r0, [r3, r1]
	mov r5, #0xff
	add r1, #0x1b
_0202F276:
	ldr r3, [r2, #0x4]
	add r3, r3, r0
	add r0, r0, #0x1
	strb r5, [r3, r1]
	cmp r0, #0x4
	blt _0202F276
	cmp r4, #0x0
	bne _0202F28A
	bl FUN_0202F2F0
_0202F28A:
	ldr r0, _0202F2BC ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202F2E0 ; =0x000005F8
	add r0, r1, r0
	bl FUN_020312BC
	cmp r4, #0x0
	bne _0202F2AC
	mov r1, #0x0
	ldr r0, _0202F2E4 ; =FUN_0202FB20
	add r2, r1, #0x0
	bl FUN_0200CA60
	ldr r1, _0202F2BC ; =0x021C59F4
	ldr r2, [r1, #0x4]
	ldr r1, _0202F2E8 ; =0x00000548
	str r0, [r2, r1]
_0202F2AC:
	ldr r0, _0202F2BC ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202F2EC ; =0x00000687
	strb r2, [r1, r0]
	mov r0, #0x1
	pop {r4-r6, pc}
	nop
_0202F2BC: .word 0x021C59F4
_0202F2C0: .word 0x0000068C
_0202F2C4: .word 0x00000658
_0202F2C8: .word 0x0000045C
_0202F2CC: .word 0x00000458
_0202F2D0: .word 0x00000454
_0202F2D4: .word 0x0000054C
_0202F2D8: .word 0x0000056C
_0202F2DC: .word 0x0000065C
_0202F2E0: .word 0x000005F8
_0202F2E4: .word FUN_0202FB20
_0202F2E8: .word 0x00000548
_0202F2EC: .word 0x00000687

	thumb_func_start FUN_0202F2F0
FUN_0202F2F0: ; 0x0202F2F0
	push {r3-r7, lr}
	ldr r3, _0202F54C ; =0x021C59F4
	ldr r2, _0202F550 ; =0x0000062C
	ldr r1, [r3, #0x4]
	mov r0, #0x0
	strb r0, [r1, r2]
	ldr r4, [r3, #0x4]
	add r1, r2, #0x1
	strb r0, [r4, r1]
	add r1, r2, #0x0
	ldr r4, [r3, #0x4]
	add r1, #0x53
	strb r0, [r4, r1]
	ldr r1, [r3, #0x4]
	add r2, #0x54
	strb r0, [r1, r2]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r6, r0, #0x1
	ldr r0, _0202F54C ; =0x021C59F4
	ldr r2, _0202F554 ; =0x00000658
	ldr r3, [r0, #0x4]
	ldr r0, _0202F558 ; =0x00000458
	mov r1, #0x0
	ldr r0, [r3, r0]
	ldr r3, [r3, r2]
	add r2, r3, #0x0
	mul r2, r6
	bl MI_CpuFill8
	mov r4, #0x0
	cmp r6, #0x0
	ble _0202F360
	ldr r7, _0202F54C ; =0x021C59F4
	add r5, r4, #0x0
_0202F33E:
	ldr r3, [r7, #0x4]
	ldr r0, _0202F554 ; =0x00000658
	ldr r1, _0202F558 ; =0x00000458
	ldr r2, [r3, r0]
	ldr r0, _0202F55C ; =0x000004E8
	add r0, r3, r0
	ldr r3, [r3, r1]
	add r1, r4, #0x0
	mul r1, r2
	add r0, r0, r5
	add r1, r3, r1
	bl FUN_0202D394
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, r6
	blt _0202F33E
_0202F360:
	ldr r0, _0202F54C ; =0x021C59F4
	ldr r2, _0202F554 ; =0x00000658
	ldr r3, [r0, #0x4]
	ldr r0, _0202F560 ; =0x00000454
	mov r1, #0x0
	ldr r0, [r3, r0]
	ldr r3, [r3, r2]
	add r2, r3, #0x0
	mul r2, r6
	bl MI_CpuFill8
	mov r5, #0x0
	cmp r6, #0x0
	ble _0202F3A2
	ldr r7, _0202F54C ; =0x021C59F4
	add r4, r5, #0x0
_0202F380:
	ldr r3, [r7, #0x4]
	ldr r0, _0202F554 ; =0x00000658
	ldr r1, _0202F560 ; =0x00000454
	ldr r2, [r3, r0]
	ldr r0, _0202F564 ; =0x0000047C
	add r0, r3, r0
	ldr r3, [r3, r1]
	add r1, r5, #0x0
	mul r1, r2
	add r0, r0, r4
	add r1, r3, r1
	bl FUN_0202D394
	add r5, r5, #0x1
	add r4, #0xc
	cmp r5, r6
	blt _0202F380
_0202F3A2:
	ldr r0, _0202F54C ; =0x021C59F4
	mov r2, #0x6
	ldr r1, [r0, #0x4]
	mov r0, #0xb5
	lsl r0, r0, #0x2
	add r0, r1, r0
	mov r1, #0x0
	lsl r2, r2, #0x6
	bl MI_CpuFill8
	ldr r0, _0202F54C ; =0x021C59F4
	mov r1, #0xb5
	ldr r2, [r0, #0x4]
	ldr r0, _0202F568 ; =0x000004DC
	lsl r1, r1, #0x2
	add r0, r2, r0
	add r1, r2, r1
	mov r2, #0x6
	lsl r2, r2, #0x6
	bl FUN_0202D394
	mov r0, #0xee
	add r2, r0, #0x0
	mov r3, #0x85
	ldr r4, _0202F54C ; =0x021C59F4
	mov r1, #0x0
	add r2, #0x66
	lsl r3, r3, #0x2
_0202F3DA:
	ldr r5, [r4, #0x4]
	add r5, r5, r1
	strb r0, [r5, r2]
	ldr r5, [r4, #0x4]
	add r5, r5, r1
	add r1, r1, #0x1
	strb r0, [r5, r3]
	cmp r1, #0xc0
	blt _0202F3DA
	ldr r0, _0202F54C ; =0x021C59F4
	mov r2, #0x42
	ldr r0, [r0, #0x4]
	mov r1, #0x0
	add r0, #0x4c
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	ldr r0, _0202F54C ; =0x021C59F4
	mov r2, #0x42
	ldr r1, [r0, #0x4]
	ldr r0, _0202F56C ; =0x00000464
	lsl r2, r2, #0x2
	add r0, r1, r0
	add r1, #0x4c
	bl FUN_0202D394
	ldr r1, _0202F54C ; =0x021C59F4
	mov r2, #0xff
	ldr r0, [r1, #0x4]
	mov r3, #0x1
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x4]
	add r0, #0x26
	strb r2, [r0, #0x0]
	mov r2, #0xee
_0202F420:
	ldr r0, [r1, #0x4]
	strb r2, [r0, r3]
	ldr r0, [r1, #0x4]
	add r0, r0, r3
	add r0, #0x26
	add r3, r3, #0x1
	strb r2, [r0, #0x0]
	cmp r3, #0x26
	blt _0202F420
	ldr r0, _0202F54C ; =0x021C59F4
	ldr r2, _0202F554 ; =0x00000658
	ldr r3, [r0, #0x4]
	ldr r0, _0202F570 ; =0x0000045C
	ldr r2, [r3, r2]
	ldr r0, [r3, r0]
	mov r1, #0x0
	lsl r2, r2, #0x1
	bl MI_CpuFill8
	ldr r0, _0202F54C ; =0x021C59F4
	mov r1, #0x47
	ldr r3, [r0, #0x4]
	ldr r2, _0202F554 ; =0x00000658
	lsl r1, r1, #0x4
	add r0, r3, r1
	sub r1, #0x14
	ldr r2, [r3, r2]
	ldr r1, [r3, r1]
	lsl r2, r2, #0x1
	bl FUN_0202D394
	mov r2, #0x0
	ldr r0, _0202F54C ; =0x021C59F4
	ldr r1, _0202F574 ; =0x00000684
	ldr r3, [r0, #0x4]
	mov r12, r2
	strb r2, [r3, r1]
	ldr r3, [r0, #0x4]
	add r1, r1, #0x1
	strb r2, [r3, r1]
	add r1, r2, #0x0
	add r7, r2, #0x0
	add r6, r2, #0x0
_0202F476:
	ldr r3, [r0, #0x4]
	add r4, r3, r2
	ldr r3, _0202F578 ; =0x0000065F
	strb r6, [r4, r3]
	ldr r3, [r0, #0x4]
	ldr r4, _0202F57C ; =0x00000667
	add r5, r3, r2
	mov r3, #0x1
	strb r3, [r5, r4]
	ldr r3, [r0, #0x4]
	add r4, #0x8
	add r5, r3, r2
	mov r3, #0x1
	strb r3, [r5, r4]
	ldr r4, [r0, #0x4]
	mov r3, r12
	add r4, r4, r3
	mov r3, #0x61
	lsl r3, r3, #0x4
	strh r6, [r4, r3]
	ldr r3, [r0, #0x4]
	mov r4, #0xee
	add r5, r3, r1
	ldr r3, _0202F580 ; =0x00000596
	add r2, r2, #0x1
	strb r4, [r5, r3]
	ldr r3, [r0, #0x4]
	ldr r4, _0202F584 ; =0x0000FFFF
	add r5, r3, r1
	ldr r3, _0202F588 ; =0x00000594
	strh r4, [r5, r3]
	ldr r3, [r0, #0x4]
	add r4, r3, r1
	mov r3, #0x59
	lsl r3, r3, #0x4
	str r6, [r4, r3]
	ldr r3, [r0, #0x4]
	add r4, r3, r1
	ldr r3, _0202F58C ; =0x0000058C
	add r1, #0xc
	str r6, [r4, r3]
	ldr r3, [r0, #0x4]
	add r4, r3, r7
	ldr r3, _0202F590 ; =0x00000638
	add r7, r7, #0x4
	str r6, [r4, r3]
	mov r3, r12
	add r3, r3, #0x2
	mov r12, r3
	cmp r2, #0x8
	blt _0202F476
	ldr r1, _0202F54C ; =0x021C59F4
	ldr r0, _0202F594 ; =0x00000634
	ldr r2, [r1, #0x4]
	sub r3, r0, #0x4
	str r6, [r2, r0]
	ldr r4, [r1, #0x4]
	mov r2, #0x1
	str r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	sub r3, #0x3e
	mov r2, #0xee
	strb r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	ldr r2, _0202F584 ; =0x0000FFFF
	sub r3, #0x40
	strh r2, [r4, r3]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	sub r2, #0x44
	str r6, [r3, r2]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	sub r2, #0x48
	str r6, [r3, r2]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0x4e
	mov r2, #0x1
	strb r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0x4f
	strb r2, [r4, r3]
	ldr r2, _0202F598 ; =0x02105D58
	mov r3, #0x4
	strb r3, [r2, #0x1]
	strb r3, [r2, #0x0]
	ldr r1, [r1, #0x4]
	sub r0, #0xe8
	add r0, r1, r0
	bl FUN_0202D804
	ldr r0, _0202F54C ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202F59C ; =0x0000056C
	add r0, r1, r0
	bl FUN_0202D804
	ldr r0, _0202F54C ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202F5A0 ; =0x00000688
	strb r2, [r1, r0]
	pop {r3-r7, pc}
	.balign 4
_0202F54C: .word 0x021C59F4
_0202F550: .word 0x0000062C
_0202F554: .word 0x00000658
_0202F558: .word 0x00000458
_0202F55C: .word 0x000004E8
_0202F560: .word 0x00000454
_0202F564: .word 0x0000047C
_0202F568: .word 0x000004DC
_0202F56C: .word 0x00000464
_0202F570: .word 0x0000045C
_0202F574: .word 0x00000684
_0202F578: .word 0x0000065F
_0202F57C: .word 0x00000667
_0202F580: .word 0x00000596
_0202F584: .word 0x0000FFFF
_0202F588: .word 0x00000594
_0202F58C: .word 0x0000058C
_0202F590: .word 0x00000638
_0202F594: .word 0x00000634
_0202F598: .word 0x02105D58
_0202F59C: .word 0x0000056C
_0202F5A0: .word 0x00000688

	thumb_func_start FUN_0202F5A4
FUN_0202F5A4: ; 0x0202F5A4
	push {r3-r7, lr}
	ldr r1, _0202F7D4 ; =0x021C59F4
	ldr r0, _0202F7D8 ; =0x0000062C
	ldr r2, [r1, #0x4]
	mov r3, #0x0
	strb r3, [r2, r0]
	ldr r1, [r1, #0x4]
	add r0, r0, #0x1
	strb r3, [r1, r0]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r6, r0, #0x1
	ldr r0, _0202F7D4 ; =0x021C59F4
	ldr r2, _0202F7DC ; =0x00000658
	ldr r3, [r0, #0x4]
	ldr r0, _0202F7E0 ; =0x00000458
	mov r1, #0x0
	ldr r0, [r3, r0]
	ldr r3, [r3, r2]
	add r2, r3, #0x0
	mul r2, r6
	bl MI_CpuFill8
	mov r4, #0x0
	cmp r6, #0x0
	ble _0202F606
	ldr r7, _0202F7D4 ; =0x021C59F4
	add r5, r4, #0x0
_0202F5E4:
	ldr r3, [r7, #0x4]
	ldr r0, _0202F7DC ; =0x00000658
	ldr r1, _0202F7E0 ; =0x00000458
	ldr r2, [r3, r0]
	ldr r0, _0202F7E4 ; =0x000004E8
	add r0, r3, r0
	ldr r3, [r3, r1]
	add r1, r4, #0x0
	mul r1, r2
	add r0, r0, r5
	add r1, r3, r1
	bl FUN_0202D394
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, r6
	blt _0202F5E4
_0202F606:
	ldr r0, _0202F7D4 ; =0x021C59F4
	ldr r2, _0202F7DC ; =0x00000658
	ldr r3, [r0, #0x4]
	ldr r0, _0202F7E8 ; =0x00000454
	mov r1, #0x0
	ldr r0, [r3, r0]
	ldr r3, [r3, r2]
	add r2, r3, #0x0
	mul r2, r6
	bl MI_CpuFill8
	mov r5, #0x0
	cmp r6, #0x0
	ble _0202F648
	ldr r7, _0202F7D4 ; =0x021C59F4
	add r4, r5, #0x0
_0202F626:
	ldr r3, [r7, #0x4]
	ldr r0, _0202F7DC ; =0x00000658
	ldr r1, _0202F7E8 ; =0x00000454
	ldr r2, [r3, r0]
	ldr r0, _0202F7EC ; =0x0000047C
	add r0, r3, r0
	ldr r3, [r3, r1]
	add r1, r5, #0x0
	mul r1, r2
	add r0, r0, r4
	add r1, r3, r1
	bl FUN_0202D394
	add r5, r5, #0x1
	add r4, #0xc
	cmp r5, r6
	blt _0202F626
_0202F648:
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r2, #0x6
	ldr r1, [r0, #0x4]
	mov r0, #0xb5
	lsl r0, r0, #0x2
	add r0, r1, r0
	mov r1, #0x0
	lsl r2, r2, #0x6
	bl MI_CpuFill8
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r1, #0xb5
	ldr r2, [r0, #0x4]
	ldr r0, _0202F7F0 ; =0x000004DC
	lsl r1, r1, #0x2
	add r0, r2, r0
	add r1, r2, r1
	mov r2, #0x6
	lsl r2, r2, #0x6
	bl FUN_0202D394
	mov r0, #0xee
	add r2, r0, #0x0
	mov r3, #0x85
	ldr r4, _0202F7D4 ; =0x021C59F4
	mov r1, #0x0
	add r2, #0x66
	lsl r3, r3, #0x2
_0202F680:
	ldr r5, [r4, #0x4]
	add r5, r5, r1
	strb r0, [r5, r2]
	ldr r5, [r4, #0x4]
	add r5, r5, r1
	add r1, r1, #0x1
	strb r0, [r5, r3]
	cmp r1, #0xc0
	blt _0202F680
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r2, #0x42
	ldr r0, [r0, #0x4]
	mov r1, #0x0
	add r0, #0x4c
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r2, #0x42
	ldr r1, [r0, #0x4]
	ldr r0, _0202F7F4 ; =0x00000464
	lsl r2, r2, #0x2
	add r0, r1, r0
	add r1, #0x4c
	bl FUN_0202D394
	ldr r1, _0202F7D4 ; =0x021C59F4
	mov r2, #0xff
	ldr r0, [r1, #0x4]
	mov r3, #0x1
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x4]
	add r0, #0x26
	strb r2, [r0, #0x0]
	mov r2, #0xee
_0202F6C6:
	ldr r0, [r1, #0x4]
	strb r2, [r0, r3]
	ldr r0, [r1, #0x4]
	add r0, r0, r3
	add r0, #0x26
	add r3, r3, #0x1
	strb r2, [r0, #0x0]
	cmp r3, #0x26
	blt _0202F6C6
	ldr r0, _0202F7D4 ; =0x021C59F4
	ldr r2, _0202F7DC ; =0x00000658
	ldr r3, [r0, #0x4]
	ldr r0, _0202F7F8 ; =0x0000045C
	ldr r2, [r3, r2]
	ldr r0, [r3, r0]
	mov r1, #0x0
	lsl r2, r2, #0x1
	bl MI_CpuFill8
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r1, #0x47
	ldr r3, [r0, #0x4]
	ldr r2, _0202F7DC ; =0x00000658
	lsl r1, r1, #0x4
	add r0, r3, r1
	sub r1, #0x14
	ldr r2, [r3, r2]
	ldr r1, [r3, r1]
	lsl r2, r2, #0x1
	bl FUN_0202D394
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r3, #0x0
	ldr r2, [r0, #0x4]
	ldr r1, _0202F7FC ; =0x00000684
	add r7, r3, #0x0
	strb r3, [r2, r1]
	ldr r2, [r0, #0x4]
	add r1, r1, #0x1
	strb r3, [r2, r1]
	add r1, r3, #0x0
	add r2, r3, #0x0
_0202F71A:
	ldr r4, [r0, #0x4]
	add r5, r4, r3
	ldr r4, _0202F800 ; =0x0000065F
	strb r7, [r5, r4]
	ldr r4, [r0, #0x4]
	ldr r5, _0202F804 ; =0x00000667
	add r6, r4, r3
	mov r4, #0x1
	strb r4, [r6, r5]
	ldr r4, [r0, #0x4]
	add r5, #0x8
	add r6, r4, r3
	mov r4, #0x1
	strb r4, [r6, r5]
	ldr r4, [r0, #0x4]
	add r3, r3, #0x1
	add r5, r4, r1
	mov r4, #0x61
	lsl r4, r4, #0x4
	strh r7, [r5, r4]
	ldr r4, [r0, #0x4]
	ldr r5, _0202F808 ; =0x00000596
	add r6, r4, r2
	mov r4, #0xee
	strb r4, [r6, r5]
	ldr r4, [r0, #0x4]
	ldr r5, _0202F80C ; =0x0000FFFF
	add r6, r4, r2
	ldr r4, _0202F810 ; =0x00000594
	add r1, r1, #0x2
	strh r5, [r6, r4]
	ldr r4, [r0, #0x4]
	add r5, r4, r2
	mov r4, #0x59
	lsl r4, r4, #0x4
	str r7, [r5, r4]
	ldr r4, [r0, #0x4]
	add r5, r4, r2
	ldr r4, _0202F814 ; =0x0000058C
	add r2, #0xc
	str r7, [r5, r4]
	cmp r3, #0x8
	blt _0202F71A
	ldr r1, _0202F7D4 ; =0x021C59F4
	add r0, r4, #0x0
	ldr r3, [r1, #0x4]
	add r0, #0xa4
	mov r2, #0x1
	str r2, [r3, r0]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	sub r3, #0x3a
	mov r2, #0xee
	strb r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	ldr r2, _0202F80C ; =0x0000FFFF
	sub r3, #0x3c
	strh r2, [r4, r3]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	sub r2, #0x40
	str r7, [r3, r2]
	add r2, r0, #0x0
	ldr r3, [r1, #0x4]
	sub r2, #0x44
	str r7, [r3, r2]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0x52
	mov r2, #0x1
	strb r2, [r4, r3]
	add r3, r0, #0x0
	ldr r4, [r1, #0x4]
	add r3, #0x53
	strb r2, [r4, r3]
	ldr r1, [r1, #0x4]
	sub r0, #0xe4
	add r0, r1, r0
	bl FUN_0202D804
	ldr r0, _0202F7D4 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202F818 ; =0x0000056C
	add r0, r1, r0
	bl FUN_0202D804
	ldr r0, _0202F7D4 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202F81C ; =0x00000688
	strb r2, [r1, r0]
	pop {r3-r7, pc}
	.balign 4
_0202F7D4: .word 0x021C59F4
_0202F7D8: .word 0x0000062C
_0202F7DC: .word 0x00000658
_0202F7E0: .word 0x00000458
_0202F7E4: .word 0x000004E8
_0202F7E8: .word 0x00000454
_0202F7EC: .word 0x0000047C
_0202F7F0: .word 0x000004DC
_0202F7F4: .word 0x00000464
_0202F7F8: .word 0x0000045C
_0202F7FC: .word 0x00000684
_0202F800: .word 0x0000065F
_0202F804: .word 0x00000667
_0202F808: .word 0x00000596
_0202F80C: .word 0x0000FFFF
_0202F810: .word 0x00000594
_0202F814: .word 0x0000058C
_0202F818: .word 0x0000056C
_0202F81C: .word 0x00000688

	thumb_func_start FUN_0202F820
FUN_0202F820: ; 0x0202F820
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0202F8B8 ; =0x021C59F4
	ldr r3, _0202F8BC ; =0x0000065F
	ldr r1, [r0, #0x4]
	mov r2, #0x0
	add r1, r1, r5
	strb r2, [r1, r3]
	ldr r4, [r0, #0x4]
	mov r1, #0x1
	add r6, r4, r5
	add r4, r3, #0x0
	add r4, #0x8
	strb r1, [r6, r4]
	ldr r6, [r0, #0x4]
	lsl r4, r5, #0x2
	add r6, r6, r4
	add r4, r3, #0x0
	sub r4, #0x27
	str r2, [r6, r4]
	ldr r2, [r0, #0x4]
	add r4, r2, r5
	add r2, r3, #0x0
	add r2, #0x10
	strb r1, [r4, r2]
	ldr r1, [r0, #0x4]
	sub r0, r3, #0x7
	ldr r2, [r1, r0]
	ldr r3, _0202F8C0 ; =0x0000047C
	mov r0, #0xc
	add r4, r5, #0x0
	mul r4, r0
	add r0, r1, r3
	sub r3, #0x28
	ldr r3, [r1, r3]
	add r1, r5, #0x0
	mul r1, r2
	add r0, r0, r4
	add r1, r3, r1
	bl FUN_0202D394
	ldr r0, _0202F8B8 ; =0x021C59F4
	ldr r3, _0202F8C4 ; =0x000004E8
	ldr r1, [r0, #0x4]
	ldr r0, _0202F8C8 ; =0x00000658
	ldr r2, [r1, r0]
	add r0, r1, r3
	sub r3, #0x90
	ldr r3, [r1, r3]
	add r1, r5, #0x0
	mul r1, r2
	add r0, r0, r4
	add r1, r3, r1
	bl FUN_0202D394
	ldr r3, _0202F8B8 ; =0x021C59F4
	ldr r2, _0202F8CC ; =0x00000596
	ldr r0, [r3, #0x4]
	mov r1, #0xee
	add r0, r0, r4
	strb r1, [r0, r2]
	ldr r0, [r3, #0x4]
	ldr r5, _0202F8D0 ; =0x0000FFFF
	add r1, r0, r4
	sub r0, r2, #0x2
	strh r5, [r1, r0]
	ldr r1, [r3, #0x4]
	mov r0, #0x0
	add r5, r1, r4
	sub r1, r2, #0x6
	str r0, [r5, r1]
	ldr r1, [r3, #0x4]
	sub r2, #0xa
	add r1, r1, r4
	str r0, [r1, r2]
	pop {r4-r6, pc}
	.balign 4
_0202F8B8: .word 0x021C59F4
_0202F8BC: .word 0x0000065F
_0202F8C0: .word 0x0000047C
_0202F8C4: .word 0x000004E8
_0202F8C8: .word 0x00000658
_0202F8CC: .word 0x00000596
_0202F8D0: .word 0x0000FFFF

	thumb_func_start FUN_0202F8D4
FUN_0202F8D4: ; 0x0202F8D4
	push {r4-r6, lr}
	ldr r4, _0202F908 ; =0x021C59F4
	ldr r6, _0202F90C ; =0x00000667
	mov r5, #0x1
_0202F8DC:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202F900
	ldr r0, [r4, #0x4]
	add r0, r0, r5
	ldrb r0, [r0, r6]
	cmp r0, #0x0
	bne _0202F900
	bl FUN_02031280
	cmp r0, #0x0
	bne _0202F900
	add r0, r5, #0x0
	bl FUN_0202F820
_0202F900:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202F8DC
	pop {r4-r6, pc}
	.balign 4
_0202F908: .word 0x021C59F4
_0202F90C: .word 0x00000667

	thumb_func_start FUN_0202F910
FUN_0202F910: ; 0x0202F910
	ldr r3, _0202F914 ; =FUN_0202F820
	bx r3
	.balign 4
_0202F914: .word FUN_0202F820

	thumb_func_start FUN_0202F918
FUN_0202F918: ; 0x0202F918
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	mov r4, #0x1
	bl FUN_02033534
	cmp r0, #0x13
	bge _0202F93E
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0202E5F8
	add r4, r0, #0x0
	ldr r0, _0202F94C ; =FUN_0202F910
	bl FUN_0202D330
_0202F93E:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0202F150
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_0202F94C: .word FUN_0202F910

	thumb_func_start FUN_0202F950
FUN_0202F950: ; 0x0202F950
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	mov r4, #0x1
	bl FUN_02033534
	cmp r0, #0x13
	bge _0202F96C
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0202E66C
	add r4, r0, #0x0
_0202F96C:
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0202F150
	ldr r0, _0202F980 ; =0x02105D58
	mov r1, #0x4
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_0202F980: .word 0x02105D58

	thumb_func_start FUN_0202F984
FUN_0202F984: ; 0x0202F984
	push {r4, lr}
	mov r4, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202F99A
	ldr r0, _0202F9D4 ; =0x02105D58
	ldrb r0, [r0, #0x1]
	cmp r0, #0x4
	beq _0202F9A2
	pop {r4, pc}
_0202F99A:
	ldr r0, _0202F9D4 ; =0x02105D58
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4
	bne _0202F9D0
_0202F9A2:
	ldr r0, _0202F9D8 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _0202F9DC ; =0x0000067D
	ldrb r1, [r2, r0]
	cmp r1, #0x2
	bne _0202F9B4
	mov r1, #0x0
	strb r1, [r2, r0]
	mov r4, #0x1
_0202F9B4:
	ldr r0, _0202F9D8 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _0202F9DC ; =0x0000067D
	ldrb r1, [r2, r0]
	cmp r1, #0x3
	bne _0202F9C4
	mov r4, #0x1
	strb r4, [r2, r0]
_0202F9C4:
	cmp r4, #0x0
	beq _0202F9CC
	bl FUN_0202F5A4
_0202F9CC:
	bl FUN_02031088
_0202F9D0:
	pop {r4, pc}
	nop
_0202F9D4: .word 0x02105D58
_0202F9D8: .word 0x021C59F4
_0202F9DC: .word 0x0000067D

	thumb_func_start FUN_0202F9E0
FUN_0202F9E0: ; 0x0202F9E0
	ldr r1, _0202FA08 ; =0x021C59F4
	ldr r3, [r1, #0x4]
	ldr r1, _0202FA0C ; =0x0000067D
	ldrb r2, [r3, r1]
	cmp r2, #0x0
	bne _0202F9F6
	cmp r0, #0x1
	bne _0202F9F6
	mov r0, #0x3
	strb r0, [r3, r1]
	bx lr
_0202F9F6:
	cmp r2, #0x1
	bne _0202FA04
	cmp r0, #0x0
	bne _0202FA04
	ldr r0, _0202FA0C ; =0x0000067D
	mov r1, #0x2
	strb r1, [r3, r0]
_0202FA04:
	bx lr
	nop
_0202FA08: .word 0x021C59F4
_0202FA0C: .word 0x0000067D

	thumb_func_start FUN_0202FA10
FUN_0202FA10: ; 0x0202FA10
	ldr r3, _0202FA18 ; =FUN_0202F9E0
	mov r0, #0x1
	bx r3
	nop
_0202FA18: .word FUN_0202F9E0

	thumb_func_start FUN_0202FA1C
FUN_0202FA1C: ; 0x0202FA1C
	ldr r3, _0202FA24 ; =FUN_0202F9E0
	mov r0, #0x0
	bx r3
	nop
_0202FA24: .word FUN_0202F9E0

	thumb_func_start FUN_0202FA28
FUN_0202FA28: ; 0x0202FA28
	ldr r0, _0202FA40 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FA44 ; =0x0000067D
	ldrb r0, [r1, r0]
	cmp r0, #0x2
	bne _0202FA38
	mov r0, #0x1
	bx lr
_0202FA38:
	cmp r0, #0x3
	bne _0202FA3E
	mov r0, #0x0
_0202FA3E:
	bx lr
	.balign 4
_0202FA40: .word 0x021C59F4
_0202FA44: .word 0x0000067D

	thumb_func_start FUN_0202FA48
FUN_0202FA48: ; 0x0202FA48
	push {r3, lr}
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _0202FA56
	mov r0, #0x1
	pop {r3, pc}
_0202FA56:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202FA5C
FUN_0202FA5C: ; 0x0202FA5C
	push {r4, lr}
	ldr r0, _0202FB00 ; =0x021C59F4
	mov r4, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202FA82
	bl FUN_02033534
	cmp r0, #0x13
	blt _0202FA78
	bl MOD04_021D83C0
	mov r4, #0x1
	b _0202FA82
_0202FA78:
	bl FUN_0202E784
	cmp r0, #0x0
	beq _0202FA82
	mov r4, #0x1
_0202FA82:
	cmp r4, #0x0
	beq _0202FAFE
	bl FUN_020314D0
	bl FUN_0202DBA4
	ldr r0, _0202FB00 ; =0x021C59F4
	mov r1, #0x0
	strb r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	ldr r0, _0202FB04 ; =0x00000548
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	ldr r1, _0202FB00 ; =0x021C59F4
	ldr r0, _0202FB04 ; =0x00000548
	ldr r2, [r1, #0x4]
	mov r3, #0x0
	str r3, [r2, r0]
	ldr r1, [r1, #0x4]
	sub r0, #0xec
	ldr r0, [r1, r0]
	bl FUN_02016A18
	ldr r0, _0202FB00 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x46
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	bl FUN_02016A18
	ldr r0, _0202FB00 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FB08 ; =0x00000458
	ldr r0, [r1, r0]
	bl FUN_02016A18
	ldr r0, _0202FB00 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FB0C ; =0x00000454
	ldr r0, [r1, r0]
	bl FUN_02016A18
	ldr r0, _0202FB00 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FB10 ; =0x0000056C
	add r0, r1, r0
	bl FUN_0202D824
	ldr r0, _0202FB00 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FB14 ; =0x0000054C
	add r0, r1, r0
	bl FUN_0202D824
	ldr r0, _0202FB00 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	bl FUN_02016A18
	ldr r0, _0202FB00 ; =0x021C59F4
	mov r1, #0x0
	str r1, [r0, #0x4]
_0202FAFE:
	pop {r4, pc}
	.balign 4
_0202FB00: .word 0x021C59F4
_0202FB04: .word 0x00000548
_0202FB08: .word 0x00000458
_0202FB0C: .word 0x00000454
_0202FB10: .word 0x0000056C
_0202FB14: .word 0x0000054C

	thumb_func_start FUN_0202FB18
FUN_0202FB18: ; 0x0202FB18
	ldr r3, _0202FB1C ; =FUN_0202E9E8
	bx r3
	.balign 4
_0202FB1C: .word FUN_0202E9E8

	thumb_func_start FUN_0202FB20
FUN_0202FB20: ; 0x0202FB20
	push {r3, lr}
	ldr r0, _0202FB54 ; =0x021C59F4
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202FB52
	bl FUN_0203050C
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202FB40
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202FB48
_0202FB40:
	bl FUN_02031280
	cmp r0, #0x0
	beq _0202FB4C
_0202FB48:
	bl FUN_0202FEEC
_0202FB4C:
	ldr r0, _0202FB54 ; =0x021C59F4
	mov r1, #0x0
	strb r1, [r0, #0x0]
_0202FB52:
	pop {r3, pc}
	.balign 4
_0202FB54: .word 0x021C59F4

	thumb_func_start FUN_0202FB58
FUN_0202FB58: ; 0x0202FB58
	push {r3, lr}
	bl FUN_0202F03C
	cmp r0, #0x0
	beq _0202FB7C
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202FB78
	bl FUN_0202EE24
	cmp r0, #0x0
	bne _0202FB7C
	bl FUN_0202FA5C
	pop {r3, pc}
_0202FB78:
	bl FUN_0202FA5C
_0202FB7C:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0202FB80
FUN_0202FB80: ; 0x0202FB80
	push {r4, lr}
	bl FUN_02031CDC
	ldr r1, _0202FC48 ; =0x021C59F4
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _0202FC34
	ldr r0, _0202FC4C ; =0x0000068A
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _0202FC16
	mov r0, #0x0
	strb r0, [r1, #0x0]
	bl FUN_0202F984
	ldr r0, _0202FC48 ; =0x021C59F4
	ldr r1, _0202FC50 ; =0x021C48B8
	ldr r0, [r0, #0x4]
	ldr r2, _0202FC54 ; =0x00000628
	ldr r3, [r1, #0x44]
	ldr r1, _0202FC58 ; =0x00007FFF
	ldrh r4, [r0, r2]
	and r1, r3
	orr r1, r4
	strh r1, [r0, r2]
	bl FUN_02030674
	bl FUN_0202FCCC
	ldr r0, _0202FC48 ; =0x021C59F4
	ldr r1, _0202FC54 ; =0x00000628
	ldr r3, [r0, #0x4]
	mov r0, #0x2
	ldrh r2, [r3, r1]
	lsl r0, r0, #0xe
	and r0, r2
	strh r0, [r3, r1]
	bl FUN_0202FA28
	cmp r0, #0x0
	bne _0202FBD6
	bl FUN_02030DA4
_0202FBD6:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202FBE8
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202FBF0
_0202FBE8:
	bl FUN_02031280
	cmp r0, #0x0
	beq _0202FBF4
_0202FBF0:
	bl FUN_02030074
_0202FBF4:
	bl FUN_02031190
	cmp r0, #0x0
	beq _0202FC0C
	bl FUN_0202FA28
	cmp r0, #0x1
	beq _0202FC0C
	bl FUN_02031280
	cmp r0, #0x0
	beq _0202FC10
_0202FC0C:
	bl FUN_02030DFC
_0202FC10:
	ldr r0, _0202FC48 ; =0x021C59F4
	mov r1, #0x1
	strb r1, [r0, #0x0]
_0202FC16:
	ldr r0, _0202FC48 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FC5C ; =0x0000065C
	ldrh r0, [r1, r0]
	bl FUN_0202ED70
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202FC2E
	bl FUN_0202F8D4
_0202FC2E:
	bl FUN_0202FB58
	b _0202FC3A
_0202FC34:
	mov r0, #0x0
	bl FUN_0202ED70
_0202FC3A:
	mov r0, #0x0
	bl FUN_020335F4
	bl FUN_020315A4
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_0202FC48: .word 0x021C59F4
_0202FC4C: .word 0x0000068A
_0202FC50: .word 0x021C48B8
_0202FC54: .word 0x00000628
_0202FC58: .word 0x00007FFF
_0202FC5C: .word 0x0000065C

	thumb_func_start FUN_0202FC60
FUN_0202FC60: ; 0x0202FC60
	push {r4, lr}
	ldr r0, _0202FC7C ; =0x021C59F4
	mov r1, #0x0
	ldrb r4, [r0, #0x0]
	strb r1, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202FC74
	bl FUN_0202F2F0
_0202FC74:
	ldr r0, _0202FC7C ; =0x021C59F4
	strb r4, [r0, #0x0]
	pop {r4, pc}
	nop
_0202FC7C: .word 0x021C59F4

	thumb_func_start FUN_0202FC80
FUN_0202FC80: ; 0x0202FC80
	push {r4, lr}
	ldr r0, _0202FCA0 ; =0x021C59F4
	mov r1, #0x0
	ldrb r4, [r0, #0x0]
	strb r1, [r0, #0x0]
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _0202FC9A
	ldr r0, _0202FCA4 ; =0x0000067D
	mov r1, #0x1
	strb r1, [r2, r0]
	bl FUN_0202F2F0
_0202FC9A:
	ldr r0, _0202FCA0 ; =0x021C59F4
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_0202FCA0: .word 0x021C59F4
_0202FCA4: .word 0x0000067D

	thumb_func_start FUN_0202FCA8
FUN_0202FCA8: ; 0x0202FCA8
	push {r4, lr}
	ldr r0, _0202FCC8 ; =0x021C59F4
	mov r1, #0x0
	ldrb r4, [r0, #0x0]
	strb r1, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202FCC0
	bl FUN_0202F2F0
	bl FUN_0202E538
_0202FCC0:
	ldr r0, _0202FCC8 ; =0x021C59F4
	strb r4, [r0, #0x0]
	pop {r4, pc}
	nop
_0202FCC8: .word 0x021C59F4

	thumb_func_start FUN_0202FCCC
FUN_0202FCCC: ; 0x0202FCCC
	push {r3, lr}
	ldr r0, _0202FE14 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FE18 ; =0x00000683
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0202FD40
	bl FUN_02033534
	cmp r0, #0x13
	blt _0202FD06
	ldr r0, _0202FE14 ; =0x021C59F4
	ldr r1, _0202FE1C ; =0x00000687
	ldr r0, [r0, #0x4]
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _0202FCF8
	mov r1, #0x26
	bl MOD04_021D78FC
	cmp r0, #0x0
	bne _0202FCFA
_0202FCF8:
	b _0202FE10
_0202FCFA:
	ldr r0, _0202FE14 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202FE18 ; =0x00000683
	strb r2, [r1, r0]
	pop {r3, pc}
_0202FD06:
	bl FUN_0202CBD4
	cmp r0, #0x4
	bne _0202FD1A
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202FD22
_0202FD1A:
	bl FUN_02031280
	cmp r0, #0x0
	beq _0202FE10
_0202FD22:
	ldr r0, _0202FE20 ; =0x02105D58
	mov r1, #0x0
	strb r1, [r0, #0x0]
	bl FUN_0203050C
	ldr r0, _0202FE20 ; =0x02105D58
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202FE10
	ldr r0, _0202FE14 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0202FE18 ; =0x00000683
	strb r2, [r1, r0]
	pop {r3, pc}
_0202FD40:
	bl FUN_02033534
	cmp r0, #0x13
	blt _0202FDB2
	ldr r0, _0202FE14 ; =0x021C59F4
	ldr r2, _0202FE1C ; =0x00000687
	ldr r0, [r0, #0x4]
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	beq _0202FE10
	add r1, r2, #0x0
	sub r1, #0x57
	ldr r1, [r0, r1]
	cmp r1, #0x0
	beq _0202FD7A
	sub r2, #0x53
	ldr r1, [r0, r2]
	cmp r1, #0x3
	bgt _0202FE10
	ldr r1, _0202FE20 ; =0x02105D58
	ldrb r1, [r1, #0x0]
	cmp r1, #0x4
	bne _0202FD90
	bl FUN_02030930
	ldr r0, _0202FE20 ; =0x02105D58
	mov r1, #0x2
	strb r1, [r0, #0x0]
	b _0202FD90
_0202FD7A:
	ldr r1, _0202FE20 ; =0x02105D58
	ldrb r1, [r1, #0x0]
	cmp r1, #0x4
	bne _0202FD90
	bl FUN_02030930
	cmp r0, #0x0
	beq _0202FE10
	ldr r0, _0202FE20 ; =0x02105D58
	mov r1, #0x2
	strb r1, [r0, #0x0]
_0202FD90:
	ldr r0, _0202FE14 ; =0x021C59F4
	mov r1, #0x26
	ldr r0, [r0, #0x4]
	bl MOD04_021D78FC
	cmp r0, #0x0
	beq _0202FE10
	ldr r0, _0202FE20 ; =0x02105D58
	mov r1, #0x4
	strb r1, [r0, #0x0]
	ldr r0, _0202FE14 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _0202FE24 ; =0x00000634
	ldr r1, [r2, r0]
	add r1, r1, #0x1
	str r1, [r2, r0]
	pop {r3, pc}
_0202FDB2:
	bl FUN_0202CBD4
	cmp r0, #0x4
	bne _0202FDC6
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0202FDCE
_0202FDC6:
	bl FUN_02031280
	cmp r0, #0x0
	beq _0202FE10
_0202FDCE:
	ldr r0, _0202FE20 ; =0x02105D58
	ldrb r0, [r0, #0x0]
	cmp r0, #0x4
	bne _0202FE10
	ldr r0, _0202FE14 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _0202FE24 ; =0x00000634
	ldr r1, [r2, r0]
	cmp r1, #0x3
	bgt _0202FE10
	add r0, #0x4b
	ldrb r1, [r2, r0]
	mov r0, #0x26
	mul r0, r1
	add r0, r2, r0
	bl FUN_02030930
	ldr r0, _0202FE14 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _0202FE28 ; =0x0000067F
	ldrb r1, [r2, r0]
	mov r0, #0x1
	sub r1, r0, r1
	mov r0, #0x26
	mul r0, r1
	add r0, r2, r0
	bl FUN_02030930
	ldr r0, _0202FE20 ; =0x02105D58
	mov r1, #0x0
	strb r1, [r0, #0x0]
	bl FUN_0203050C
_0202FE10:
	pop {r3, pc}
	nop
_0202FE14: .word 0x021C59F4
_0202FE18: .word 0x00000683
_0202FE1C: .word 0x00000687
_0202FE20: .word 0x02105D58
_0202FE24: .word 0x00000634
_0202FE28: .word 0x0000067F

	thumb_func_start FUN_0202FE2C
FUN_0202FE2C: ; 0x0202FE2C
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	str r0, [sp, #0xc]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r0, r0, #0x1
	mov r7, #0x0
	str r0, [sp, #0x8]
	cmp r0, #0x0
	ble _0202FED0
	ldr r0, [sp, #0x0]
	mov r1, #0xc0
	add r6, r0, #0x0
	add r4, r7, #0x0
	add r5, r7, #0x0
	mul r6, r1
_0202FE66:
	ldr r0, _0202FEE4 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0202FEE8 ; =0x0000047C
	add r0, r1, r0
	add r0, r0, r4
	bl FUN_0202D4BC
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202FE90
	ldr r0, _0202FEE4 ; =0x021C59F4
	mov r1, #0xe
	ldr r0, [r0, #0x4]
	add r0, r6, r0
	add r2, r5, r0
	mov r0, #0x55
	lsl r0, r0, #0x2
	strb r1, [r2, r0]
_0202FE90:
	ldr r0, _0202FEE4 ; =0x021C59F4
	mov r2, #0x55
	ldr r1, [r0, #0x4]
	ldr r0, _0202FEE8 ; =0x0000047C
	lsl r2, r2, #0x2
	add r0, r1, r0
	add r1, r1, r2
	add r1, r1, r6
	ldr r2, [sp, #0xc]
	add r0, r0, r4
	add r1, r1, r5
	bl FUN_0202D400
	ldr r0, _0202FEE4 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	add r0, r6, r0
	add r1, r5, r0
	mov r0, #0x55
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0xe
	bne _0202FEC2
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0202FEC2:
	ldr r0, [sp, #0xc]
	add r7, r7, #0x1
	add r5, r5, r0
	ldr r0, [sp, #0x8]
	add r4, #0xc
	cmp r7, r0
	blt _0202FE66
_0202FED0:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	cmp r1, r0
	bne _0202FEDE
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0202FEDE:
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0202FEE4: .word 0x021C59F4
_0202FEE8: .word 0x0000047C

	thumb_func_start FUN_0202FEEC
FUN_0202FEEC: ; 0x0202FEEC
	push {r3-r7, lr}
	ldr r0, _02030064 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0202FEFE
	bl FUN_02033534
	cmp r0, #0x13
	blt _0202FF00
_0202FEFE:
	b _02030062
_0202FF00:
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	str r0, [sp, #0x0]
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r6, r0, #0x1
	ldr r0, _02030068 ; =0x02105D58
	ldrb r1, [r0, #0x1]
	cmp r1, #0x2
	beq _0202FF2C
	ldrb r0, [r0, #0x1]
	cmp r0, #0x0
	beq _0202FF2C
	b _02030062
_0202FF2C:
	ldr r0, _02030068 ; =0x02105D58
	ldrb r1, [r0, #0x1]
	add r1, r1, #0x1
	strb r1, [r0, #0x1]
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _0202FF4A
	ldr r0, _02030064 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x1a
	lsl r0, r0, #0x6
	ldrb r0, [r1, r0]
	bl FUN_0202FE2C
_0202FF4A:
	bl FUN_0202CBD4
	cmp r0, #0x4
	bne _0202FF86
	bl FUN_02031280
	cmp r0, #0x0
	bne _0202FF86
	ldr r0, _02030064 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x55
	lsl r0, r0, #0x2
	add r3, r1, r0
	mov r0, #0x1a
	lsl r0, r0, #0x6
	ldrb r0, [r1, r0]
	mov r1, #0xc0
	add r2, r0, #0x0
	mul r2, r1
	add r0, r3, r2
	ldr r3, _0203006C ; =FUN_020304F0
	mov r2, #0xe
	bl FUN_0202D0D0
	cmp r0, #0x0
	bne _0202FF86
	ldr r0, _02030068 ; =0x02105D58
	ldrb r1, [r0, #0x1]
	sub r1, r1, #0x1
	strb r1, [r0, #0x1]
_0202FF86:
	ldr r0, _02030068 ; =0x02105D58
	ldrb r1, [r0, #0x1]
	cmp r1, #0x1
	beq _0202FF94
	ldrb r0, [r0, #0x1]
	cmp r0, #0x3
	bne _0203000A
_0202FF94:
	mov r4, #0x0
	cmp r6, #0x0
	ble _0202FFDC
	ldr r7, _02030064 ; =0x021C59F4
	add r5, r4, #0x0
_0202FF9E:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202FFBA
	ldr r0, [r7, #0x4]
	ldr r1, _02030070 ; =0x00000638
	add r0, r0, r5
	ldr r1, [r0, r1]
	add r2, r1, #0x1
	ldr r1, _02030070 ; =0x00000638
	str r2, [r0, r1]
	b _0202FFD4
_0202FFBA:
	bl FUN_02031280
	cmp r0, #0x0
	beq _0202FFD4
	cmp r4, #0x0
	bne _0202FFD4
	ldr r0, [r7, #0x4]
	ldr r1, _02030070 ; =0x00000638
	add r0, r0, r5
	ldr r1, [r0, r1]
	add r2, r1, #0x1
	ldr r1, _02030070 ; =0x00000638
	str r2, [r0, r1]
_0202FFD4:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _0202FF9E
_0202FFDC:
	ldr r0, _02030064 ; =0x021C59F4
	mov r1, #0x55
	ldr r2, [r0, #0x4]
	lsl r1, r1, #0x2
	add r4, r2, r1
	mov r1, #0x1a
	lsl r1, r1, #0x6
	ldrb r1, [r2, r1]
	mov r2, #0xc0
	mov r0, #0x0
	add r3, r1, #0x0
	mul r3, r2
	add r1, r4, r3
	bl FUN_0203026C
	ldr r0, _02030064 ; =0x021C59F4
	mov r1, #0x1a
	ldr r3, [r0, #0x4]
	lsl r1, r1, #0x6
	ldrb r2, [r3, r1]
	mov r0, #0x1
	sub r0, r0, r2
	strb r0, [r3, r1]
_0203000A:
	mov r5, #0x0
	cmp r6, #0x0
	ble _0203004A
	add r4, r5, #0x0
	mov r7, #0xff
_02030014:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030040
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030040
	ldr r0, _02030064 ; =0x021C59F4
	mov r1, #0x1a
	ldr r0, [r0, #0x4]
	lsl r1, r1, #0x6
	ldrb r2, [r0, r1]
	mov r1, #0xc0
	mul r1, r2
	add r0, r0, r1
	add r1, r4, r0
	mov r0, #0x55
	lsl r0, r0, #0x2
	strb r7, [r1, r0]
_02030040:
	ldr r0, [sp, #0x0]
	add r5, r5, #0x1
	add r4, r4, r0
	cmp r5, r6
	blt _02030014
_0203004A:
	bl FUN_0202CBD4
	cmp r0, #0x4
	bne _0203005A
	bl FUN_02031280
	cmp r0, #0x0
	beq _02030062
_0203005A:
	ldr r0, _02030068 ; =0x02105D58
	ldrb r1, [r0, #0x1]
	add r1, r1, #0x1
	strb r1, [r0, #0x1]
_02030062:
	pop {r3-r7, pc}
	.balign 4
_02030064: .word 0x021C59F4
_02030068: .word 0x02105D58
_0203006C: .word FUN_020304F0
_02030070: .word 0x00000638

	thumb_func_start FUN_02030074
FUN_02030074: ; 0x02030074
	push {r3-r7, lr}
	ldr r0, _02030228 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0203022C ; =0x00000683
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _020300DC
	bl FUN_02033534
	cmp r0, #0x13
	blt _020300B4
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _020300DC
	ldr r0, _02030228 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x55
	lsl r0, r0, #0x2
	add r0, r1, r0
	mov r1, #0x4c
	bl MOD04_021D79B4
	cmp r0, #0x0
	beq _020300DC
	ldr r0, _02030228 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0203022C ; =0x00000683
	strb r2, [r1, r0]
	pop {r3-r7, pc}
_020300B4:
	bl FUN_0202CBD4
	cmp r0, #0x4
	beq _020300C4
	bl FUN_02031280
	cmp r0, #0x0
	beq _020300DC
_020300C4:
	bl FUN_0202FEEC
	ldr r0, _02030230 ; =0x02105D58
	ldrb r0, [r0, #0x1]
	cmp r0, #0x2
	bne _020300DC
	ldr r0, _02030228 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0203022C ; =0x00000683
	strb r2, [r1, r0]
	pop {r3-r7, pc}
_020300DC:
	bl FUN_02033534
	cmp r0, #0x13
	blt _02030184
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _020300F0
	b _02030224
_020300F0:
	ldr r0, _02030228 ; =0x021C59F4
	mov r1, #0x63
	ldr r2, [r0, #0x4]
	lsl r1, r1, #0x4
	ldr r0, [r2, r1]
	cmp r0, #0x0
	beq _02030130
	add r0, r1, #0x0
	add r0, #0xc
	ldr r0, [r2, r0]
	cmp r0, #0x3
	bgt _02030110
	add r1, #0x8
	ldr r0, [r2, r1]
	cmp r0, #0x3
	ble _02030112
_02030110:
	b _02030224
_02030112:
	ldr r0, _02030230 ; =0x02105D58
	ldrb r0, [r0, #0x1]
	cmp r0, #0x4
	bne _02030150
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030128
	mov r0, #0x0
	bl FUN_0202FE2C
_02030128:
	ldr r0, _02030230 ; =0x02105D58
	mov r1, #0x2
	strb r1, [r0, #0x1]
	b _02030150
_02030130:
	ldr r0, _02030230 ; =0x02105D58
	ldrb r0, [r0, #0x1]
	cmp r0, #0x4
	bne _0203014A
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _0203014A
	mov r0, #0x0
	bl FUN_0202FE2C
	cmp r0, #0x0
	beq _02030224
_0203014A:
	ldr r0, _02030230 ; =0x02105D58
	mov r1, #0x2
	strb r1, [r0, #0x1]
_02030150:
	ldr r0, _02030228 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x55
	lsl r0, r0, #0x2
	add r0, r1, r0
	mov r1, #0x4c
	bl MOD04_021D79B4
	cmp r0, #0x0
	beq _02030224
	ldr r0, _02030230 ; =0x02105D58
	mov r1, #0x4
	strb r1, [r0, #0x1]
	ldr r1, _02030228 ; =0x021C59F4
	ldr r0, _02030234 ; =0x00000638
	ldr r3, [r1, #0x4]
	ldr r2, [r3, r0]
	add r2, r2, #0x1
	str r2, [r3, r0]
	ldr r2, [r1, #0x4]
	add r1, r0, #0x4
	ldr r1, [r2, r1]
	add r0, r0, #0x4
	add r1, r1, #0x1
	str r1, [r2, r0]
	pop {r3-r7, pc}
_02030184:
	bl FUN_0202CBD4
	cmp r0, #0x4
	beq _02030194
	bl FUN_02031280
	cmp r0, #0x0
	beq _02030224
_02030194:
	ldr r0, _02030230 ; =0x02105D58
	ldrb r0, [r0, #0x1]
	cmp r0, #0x4
	bne _02030224
	ldr r6, _02030228 ; =0x021C59F4
	ldr r7, _02030234 ; =0x00000638
	mov r4, #0x1
	mov r5, #0x4
_020301A4:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _020301BC
	ldr r0, [r6, #0x4]
	add r0, r0, r5
	ldr r0, [r0, r7]
	cmp r0, #0x3
	ble _020301D2
	pop {r3-r7, pc}
_020301BC:
	cmp r4, #0x0
	bne _020301D2
	bl FUN_02031280
	cmp r0, #0x0
	beq _020301D2
	ldr r1, [r6, #0x4]
	ldr r0, _02030234 ; =0x00000638
	ldr r0, [r1, r0]
	cmp r0, #0x3
	bgt _02030224
_020301D2:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x8
	blt _020301A4
	bl FUN_0202FA28
	cmp r0, #0x0
	bne _0203021A
	ldr r0, _02030228 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x55
	lsl r0, r0, #0x2
	add r2, r1, r0
	mov r0, #0x1a
	lsl r0, r0, #0x6
	ldrb r1, [r1, r0]
	mov r0, #0xc0
	mul r0, r1
	add r0, r2, r0
	bl FUN_02030A00
	ldr r0, _02030228 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x55
	lsl r0, r0, #0x2
	add r2, r1, r0
	mov r0, #0x1a
	lsl r0, r0, #0x6
	ldrb r1, [r1, r0]
	mov r0, #0x1
	sub r1, r0, r1
	mov r0, #0xc0
	mul r0, r1
	add r0, r2, r0
	bl FUN_02030A00
_0203021A:
	ldr r0, _02030230 ; =0x02105D58
	mov r1, #0x0
	strb r1, [r0, #0x1]
	bl FUN_0202FEEC
_02030224:
	pop {r3-r7, pc}
	nop
_02030228: .word 0x021C59F4
_0203022C: .word 0x00000683
_02030230: .word 0x02105D58
_02030234: .word 0x00000638

	thumb_func_start FUN_02030238
FUN_02030238: ; 0x02030238
	push {r4-r6, lr}
	ldr r4, _02030264 ; =0x021C59F4
	ldr r3, _02030268 ; =0x0000066F
	ldr r5, [r4, #0x4]
	ldrb r6, [r5, r3]
	cmp r6, #0x0
	beq _0203025C
	add r0, r3, #0x0
	sub r0, #0x3b
	ldr r0, [r5, r0]
	sub r1, r0, #0x1
	add r0, r3, #0x0
	sub r0, #0x3b
	str r1, [r5, r0]
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	strb r1, [r0, r3]
	pop {r4-r6, pc}
_0203025C:
	bl FUN_0203026C
	pop {r4-r6, pc}
	nop
_02030264: .word 0x021C59F4
_02030268: .word 0x0000066F

	thumb_func_start FUN_0203026C
FUN_0203026C: ; 0x0203026C
	push {r3-r7, lr}
	sub sp, #0x8
	ldr r0, _020303A0 ; =0x021C59F4
	add r5, r1, #0x0
	ldr r2, [r0, #0x4]
	ldr r0, _020303A4 ; =0x00000634
	ldr r1, [r2, r0]
	sub r1, r1, #0x1
	str r1, [r2, r0]
	cmp r5, #0x0
	beq _02030290
	ldrb r0, [r5, #0x0]
	cmp r0, #0xb
	bne _02030296
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030292
_02030290:
	b _0203039C
_02030292:
	add r5, r5, #0x1
	b _0203029E
_02030296:
	bl FUN_0202FA28
	cmp r0, #0x0
	beq _0203039C
_0203029E:
	ldr r0, _020303A0 ; =0x021C59F4
	ldr r1, _020303A8 ; =0x00000682
	ldr r0, [r0, #0x4]
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _020302B2
	ldrb r2, [r5, #0x0]
	mov r1, #0x1
	tst r1, r2
	bne _0203039C
_020302B2:
	ldr r1, _020303A8 ; =0x00000682
	mov r2, #0x0
	strb r2, [r0, r1]
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _0203036E
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	add r6, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r0, r0, #0x1
	mov r4, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0203039C
	sub r0, r6, #0x1
	add r7, r4, #0x0
	str r0, [sp, #0x0]
_020302EA:
	ldrb r0, [r5, #0x0]
	cmp r0, #0xff
	bne _02030302
	ldr r0, _020303A0 ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020303AC ; =0x0000065C
	lsl r2, r4
	ldrh r0, [r1, r0]
	mvn r2, r2
	and r2, r0
	b _02030310
_02030302:
	ldr r0, _020303A0 ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020303AC ; =0x0000065C
	lsl r2, r4
	ldrh r0, [r1, r0]
	orr r2, r0
_02030310:
	ldr r0, _020303AC ; =0x0000065C
	strh r2, [r1, r0]
	ldrb r2, [r5, #0x0]
	cmp r2, #0xff
	bne _0203031E
	add r5, r5, r6
	b _02030360
_0203031E:
	cmp r2, #0xe
	bne _02030326
	add r5, r5, r6
	b _02030360
_02030326:
	ldr r0, _020303A0 ; =0x021C59F4
	ldr r3, [r0, #0x4]
	ldr r0, _020303B0 ; =0x00000667
	add r1, r3, r4
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0203033E
	mov r0, #0x1
	tst r0, r2
	beq _0203033E
	add r5, r5, r6
	b _02030360
_0203033E:
	ldr r0, _020303B4 ; =0x000004E8
	add r5, r5, #0x1
	add r0, r3, r0
	ldr r2, [sp, #0x0]
	ldr r3, _020303B8 ; =0x000005E6
	add r0, r0, r7
	add r1, r5, #0x0
	bl FUN_0202D3A4
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	add r5, r5, r0
	ldr r0, _020303A0 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	add r2, r0, r4
	ldr r0, _020303B0 ; =0x00000667
	strb r1, [r2, r0]
_02030360:
	ldr r0, [sp, #0x4]
	add r4, r4, #0x1
	add r7, #0xc
	cmp r4, r0
	blt _020302EA
	add sp, #0x8
	pop {r3-r7, pc}
_0203036E:
	ldr r0, _020303A0 ; =0x021C59F4
	ldrb r2, [r5, #0x1]
	ldr r1, [r0, #0x4]
	ldr r3, _020303AC ; =0x0000065C
	strh r2, [r1, r3]
	ldr r2, [r0, #0x4]
	ldrh r1, [r2, r3]
	lsl r1, r1, #0x8
	strh r1, [r2, r3]
	ldr r4, [r0, #0x4]
	ldrb r1, [r5, #0x2]
	ldrh r2, [r4, r3]
	add r1, r2, r1
	strh r1, [r4, r3]
	ldr r1, [r0, #0x4]
	mov r0, #0x47
	lsl r0, r0, #0x4
	add r0, r1, r0
	ldrb r2, [r5, #0x3]
	add r1, r5, #0x4
	sub r3, #0x5d
	bl FUN_0202D3A4
_0203039C:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020303A0: .word 0x021C59F4
_020303A4: .word 0x00000634
_020303A8: .word 0x00000682
_020303AC: .word 0x0000065C
_020303B0: .word 0x00000667
_020303B4: .word 0x000004E8
_020303B8: .word 0x000005E6

	thumb_func_start FUN_020303BC
FUN_020303BC: ; 0x020303BC
	push {r4-r6, lr}
	ldr r3, _020303EC ; =0x021C59F4
	ldr r6, _020303F0 ; =0x0000066F
	ldr r5, [r3, #0x4]
	add r4, r5, r0
	ldrb r4, [r4, r6]
	cmp r4, #0x0
	beq _020303E4
	add r1, r6, #0x0
	sub r1, #0x37
	add r4, r5, r1
	lsl r2, r0, #0x2
	ldr r1, [r4, r2]
	sub r1, r1, #0x1
	str r1, [r4, r2]
	ldr r1, [r3, #0x4]
	mov r2, #0x0
	add r0, r1, r0
	strb r2, [r0, r6]
	pop {r4-r6, pc}
_020303E4:
	bl FUN_020303F4
	pop {r4-r6, pc}
	nop
_020303EC: .word 0x021C59F4
_020303F0: .word 0x0000066F

	thumb_func_start FUN_020303F4
FUN_020303F4: ; 0x020303F4
	push {r4-r6, lr}
	ldr r3, _020304B8 ; =0x021C59F4
	add r5, r0, #0x0
	ldr r0, [r3, #0x4]
	ldr r2, _020304BC ; =0x00000638
	add r4, r1, #0x0
	add r1, r0, r2
	lsl r0, r5, #0x2
	ldr r6, [r1, r0]
	sub r6, r6, #0x1
	str r6, [r1, r0]
	cmp r4, #0x0
	beq _020304B4
	ldr r0, [r3, #0x4]
	add r2, #0x2f
	add r0, r0, r2
	ldrb r1, [r0, r5]
	cmp r1, #0x0
	beq _02030422
	ldrb r2, [r4, #0x0]
	mov r1, #0x1
	tst r1, r2
	bne _020304B4
_02030422:
	mov r1, #0x0
	strb r1, [r0, r5]
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030478
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	add r6, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	ldrb r1, [r4, #0x0]
	mov r0, #0x2
	tst r0, r1
	bne _02030468
	ldr r0, _020304B8 ; =0x021C59F4
	ldr r3, _020304C0 ; =0x0000065E
	ldr r1, [r0, #0x4]
	ldr r0, _020304C4 ; =0x0000047C
	add r2, r6, #0x0
	add r1, r1, r0
	mov r0, #0xc
	mul r0, r5
	add r0, r1, r0
	add r1, r4, #0x0
	bl FUN_0202D3A4
_02030468:
	ldr r0, _020304B8 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _020304C8 ; =0x0000065F
	add r1, r1, r0
	ldrb r0, [r1, r5]
	add r0, r0, #0x1
	strb r0, [r1, r5]
	pop {r4-r6, pc}
_02030478:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020307E4
	ldrb r1, [r4, #0x0]
	mov r0, #0x2
	tst r0, r1
	bne _020304B4
	mov r0, #0xc
	add r6, r5, #0x0
	mul r6, r0
	ldr r0, _020304B8 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _020304CC ; =0x000004E8
	add r0, r1, r0
	add r0, r0, r6
	bl FUN_0202D498
	cmp r0, #0xb
	blt _020304B4
	ldr r0, _020304B8 ; =0x021C59F4
	ldr r3, _020304D0 ; =0x0000066E
	ldr r1, [r0, #0x4]
	ldr r0, _020304CC ; =0x000004E8
	mov r2, #0xb
	add r0, r1, r0
	add r0, r0, r6
	add r1, r4, #0x1
	bl FUN_0202D3A4
_020304B4:
	pop {r4-r6, pc}
	nop
_020304B8: .word 0x021C59F4
_020304BC: .word 0x00000638
_020304C0: .word 0x0000065E
_020304C4: .word 0x0000047C
_020304C8: .word 0x0000065F
_020304CC: .word 0x000004E8
_020304D0: .word 0x0000066E

	thumb_func_start FUN_020304D4
FUN_020304D4: ; 0x020304D4
	push {r3, lr}
	cmp r0, #0x0
	beq _020304E4
	ldr r0, _020304EC ; =0x02105D58
	ldrb r1, [r0, #0x0]
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	pop {r3, pc}
_020304E4:
	bl ErrorHandling
	pop {r3, pc}
	nop
_020304EC: .word 0x02105D58

	thumb_func_start FUN_020304F0
FUN_020304F0: ; 0x020304F0
	push {r3, lr}
	cmp r0, #0x0
	beq _02030500
	ldr r0, _02030508 ; =0x02105D58
	ldrb r1, [r0, #0x1]
	add r1, r1, #0x1
	strb r1, [r0, #0x1]
	pop {r3, pc}
_02030500:
	bl ErrorHandling
	pop {r3, pc}
	nop
_02030508: .word 0x02105D58

	thumb_func_start FUN_0203050C
FUN_0203050C: ; 0x0203050C
	push {r4, lr}
	ldr r0, _02030660 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0203051E
	bl FUN_02033534
	cmp r0, #0x13
	blt _02030520
_0203051E:
	b _0203065E
_02030520:
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	add r4, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	bl FUN_02031280
	cmp r0, #0x0
	beq _02030594
	ldr r0, _02030664 ; =0x02105D58
	ldrb r1, [r0, #0x0]
	cmp r1, #0x2
	beq _02030550
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02030594
_02030550:
	ldr r0, _02030664 ; =0x02105D58
	ldrb r1, [r0, #0x0]
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x1
	bl FUN_020304D4
	ldr r0, _02030660 ; =0x021C59F4
	ldr r1, _02030668 ; =0x0000067F
	ldr r3, [r0, #0x4]
	mov r0, #0x0
	ldrb r2, [r3, r1]
	mov r1, #0x26
	mul r1, r2
	lsl r2, r4, #0x10
	add r1, r3, r1
	lsr r2, r2, #0x10
	bl FUN_020303F4
	ldr r2, _02030660 ; =0x021C59F4
	ldr r1, _02030668 ; =0x0000067F
	ldr r4, [r2, #0x4]
	mov r0, #0x1
	ldrb r3, [r4, r1]
	sub r0, r0, r3
	strb r0, [r4, r1]
	add r0, r1, #0x0
	ldr r2, [r2, #0x4]
	sub r0, #0x4b
	ldr r0, [r2, r0]
	sub r1, #0x4b
	add r0, r0, #0x1
	str r0, [r2, r1]
	pop {r4, pc}
_02030594:
	bl FUN_0202CBD4
	cmp r0, #0x4
	bne _0203065E
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _020305AE
	bl FUN_02031190
	pop {r4, pc}
_020305AE:
	ldr r0, _02030664 ; =0x02105D58
	ldrb r1, [r0, #0x0]
	cmp r1, #0x2
	beq _020305BC
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203065E
_020305BC:
	bl FUN_02031190
	cmp r0, #0x0
	beq _02030612
	ldr r0, _02030664 ; =0x02105D58
	ldr r3, _0203066C ; =FUN_020304D4
	ldrb r1, [r0, #0x0]
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldr r0, _02030660 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _02030668 ; =0x0000067F
	ldrb r1, [r2, r0]
	mov r0, #0x26
	mul r0, r1
	lsl r1, r4, #0x10
	add r0, r2, r0
	lsr r1, r1, #0x10
	mov r2, #0xe
	bl FUN_0202D0D0
	cmp r0, #0x0
	bne _020305F4
	ldr r0, _02030664 ; =0x02105D58
	ldrb r1, [r0, #0x0]
	sub r1, r1, #0x1
	strb r1, [r0, #0x0]
	pop {r4, pc}
_020305F4:
	ldr r2, _02030660 ; =0x021C59F4
	ldr r1, _02030668 ; =0x0000067F
	ldr r4, [r2, #0x4]
	mov r0, #0x1
	ldrb r3, [r4, r1]
	sub r0, r0, r3
	strb r0, [r4, r1]
	add r0, r1, #0x0
	ldr r2, [r2, #0x4]
	sub r0, #0x4b
	ldr r0, [r2, r0]
	sub r1, #0x4b
	add r0, r0, #0x1
	str r0, [r2, r1]
	pop {r4, pc}
_02030612:
	bl FUN_0202CB8C
	ldr r1, _02030670 ; =0x0000FFFE
	tst r0, r1
	beq _0203065E
	ldr r0, _02030664 ; =0x02105D58
	ldrb r1, [r0, #0x0]
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x1
	bl FUN_020304D4
	ldr r0, _02030660 ; =0x021C59F4
	ldr r1, _02030668 ; =0x0000067F
	ldr r3, [r0, #0x4]
	mov r0, #0x0
	ldrb r2, [r3, r1]
	mov r1, #0x26
	mul r1, r2
	lsl r2, r4, #0x10
	add r1, r3, r1
	lsr r2, r2, #0x10
	bl FUN_020303F4
	ldr r2, _02030660 ; =0x021C59F4
	ldr r1, _02030668 ; =0x0000067F
	ldr r4, [r2, #0x4]
	mov r0, #0x1
	ldrb r3, [r4, r1]
	sub r0, r0, r3
	strb r0, [r4, r1]
	add r0, r1, #0x0
	ldr r2, [r2, #0x4]
	sub r0, #0x4b
	ldr r0, [r2, r0]
	sub r1, #0x4b
	add r0, r0, #0x1
	str r0, [r2, r1]
_0203065E:
	pop {r4, pc}
	.balign 4
_02030660: .word 0x021C59F4
_02030664: .word 0x02105D58
_02030668: .word 0x0000067F
_0203066C: .word FUN_020304D4
_02030670: .word 0x0000FFFE

	thumb_func_start FUN_02030674
FUN_02030674: ; 0x02030674
	push {r3-r7, lr}
	ldr r7, _02030798 ; =0x021C59F4
	mov r6, #0x0
	ldr r5, [r7, #0x4]
	ldr r2, _0203079C ; =0x0000062C
	add r4, r6, #0x0
	ldrb r0, [r5, r2]
	cmp r0, #0x0
	beq _02030690
	sub r1, r2, #0x4
	ldrh r1, [r5, r1]
	mov r3, #0xf0
	tst r3, r1
	bne _02030692
_02030690:
	b _02030794
_02030692:
	cmp r0, #0x2
	bne _020306D0
	mov r0, #0x20
	tst r0, r1
	beq _020306A4
	mov r0, #0x10
	orr r0, r6
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306A4:
	mov r0, #0x10
	tst r0, r1
	beq _020306B2
	mov r0, #0x20
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306B2:
	mov r0, #0x40
	tst r0, r1
	beq _020306C0
	mov r0, #0x80
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
_020306C0:
	mov r0, #0x80
	tst r0, r1
	beq _0203077E
	mov r0, #0x40
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	b _0203077E
_020306D0:
	add r0, r2, #0x2
	ldrh r0, [r5, r0]
	cmp r0, #0x0
	beq _020306F2
	add r4, r0, #0x0
	add r0, r2, #0x1
	ldrsb r0, [r5, r0]
	sub r1, r0, #0x1
	add r0, r2, #0x1
	strb r1, [r5, r0]
	ldr r1, [r7, #0x4]
	ldrsb r0, [r1, r0]
	cmp r0, #0x0
	bge _0203077E
	add r0, r2, #0x2
	strh r6, [r1, r0]
	b _0203077E
_020306F2:
	add r0, r2, #0x0
	sub r0, #0x34
	add r6, r5, r0
	sub r2, #0x34
	ldr r0, [r6, #0x8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, r2]
	ldr r3, [r6, #0x4]
	bl _ll_mul
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldr r0, [r6, #0x10]
	ldr r1, [r6, #0x14]
	add r0, r0, r3
	adc r1, r2
	ldr r2, _020307A0 ; =0x000005F8
	str r0, [r5, r2]
	mov r2, #0x0
	str r1, [r6, #0x4]
	lsr r0, r1, #0x1e
	lsl r1, r2, #0x2
	orr r1, r0
	cmp r1, #0x3
	bhi _02030746
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02030730: ; jump table (using 16-bit offset)
	.short _02030738 - _02030730 - 2; case 0
	.short _0203073C - _02030730 - 2; case 1
	.short _02030740 - _02030730 - 2; case 2
	.short _02030744 - _02030730 - 2; case 3
_02030738:
	mov r4, #0x20
	b _02030746
_0203073C:
	mov r4, #0x10
	b _02030746
_02030740:
	mov r4, #0x40
	b _02030746
_02030744:
	mov r4, #0x80
_02030746:
	ldr r0, _02030798 ; =0x021C59F4
	ldr r5, [r0, #0x4]
	ldr r0, _020307A0 ; =0x000005F8
	add r6, r5, r0
	ldr r0, [r6, #0x8]
	ldr r1, [r6, #0xc]
	ldr r2, [r6, #0x0]
	ldr r3, [r6, #0x4]
	bl _ll_mul
	ldr r3, [r6, #0x10]
	ldr r2, [r6, #0x14]
	add r0, r3, r0
	adc r2, r1
	ldr r1, _020307A0 ; =0x000005F8
	mov r3, #0x0
	str r0, [r5, r1]
	str r2, [r6, #0x4]
	lsr r0, r2, #0x1c
	lsl r2, r3, #0x4
	orr r2, r0
	add r0, r1, #0x0
	add r0, #0x35
	strb r2, [r5, r0]
	ldr r0, _02030798 ; =0x021C59F4
	add r1, #0x36
	ldr r0, [r0, #0x4]
	strh r4, [r0, r1]
_0203077E:
	ldr r2, _02030798 ; =0x021C59F4
	ldr r1, _020307A4 ; =0x00000628
	ldr r5, [r2, #0x4]
	mov r0, #0xf0
	ldrh r3, [r5, r1]
	bic r3, r0
	strh r3, [r5, r1]
	ldr r2, [r2, #0x4]
	ldrh r0, [r2, r1]
	add r0, r0, r4
	strh r0, [r2, r1]
_02030794:
	pop {r3-r7, pc}
	nop
_02030798: .word 0x021C59F4
_0203079C: .word 0x0000062C
_020307A0: .word 0x000005F8
_020307A4: .word 0x00000628

	thumb_func_start FUN_020307A8
FUN_020307A8: ; 0x020307A8
	ldr r0, _020307B4 ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020307B8 ; =0x0000062C
	strb r2, [r1, r0]
	bx lr
	.balign 4
_020307B4: .word 0x021C59F4
_020307B8: .word 0x0000062C

	thumb_func_start FUN_020307BC
FUN_020307BC: ; 0x020307BC
	ldr r0, _020307C8 ; =0x021C59F4
	mov r2, #0x2
	ldr r1, [r0, #0x4]
	ldr r0, _020307CC ; =0x0000062C
	strb r2, [r1, r0]
	bx lr
	.balign 4
_020307C8: .word 0x021C59F4
_020307CC: .word 0x0000062C

	thumb_func_start FUN_020307D0
FUN_020307D0: ; 0x020307D0
	ldr r0, _020307DC ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _020307E0 ; =0x0000062C
	strb r2, [r1, r0]
	bx lr
	.balign 4
_020307DC: .word 0x021C59F4
_020307E0: .word 0x0000062C

	thumb_func_start FUN_020307E4
FUN_020307E4: ; 0x020307E4
	push {r4-r7}
	ldr r4, _02030868 ; =0x021C59F4
	lsl r6, r1, #0x1
	ldr r2, [r4, #0x4]
	mov r5, #0x0
	add r3, r2, r6
	mov r2, #0x61
	lsl r2, r2, #0x4
	strh r5, [r3, r2]
	ldrb r5, [r0, #0x0]
	mov r3, #0x10
	add r7, r5, #0x0
	and r7, r3
	cmp r7, #0x10
	bne _02030860
	mov r7, #0xc
	and r5, r7
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	bne _0203081A
	ldr r3, [r4, #0x4]
	add r4, r3, r2
	ldrh r3, [r4, r6]
	mov r2, #0x40
	orr r2, r3
	strh r2, [r4, r6]
	b _0203084C
_0203081A:
	cmp r5, #0x4
	bne _0203082C
	ldr r3, [r4, #0x4]
	add r4, r3, r2
	ldrh r3, [r4, r6]
	mov r2, #0x80
	orr r2, r3
	strh r2, [r4, r6]
	b _0203084C
_0203082C:
	cmp r5, #0x8
	bne _0203083E
	ldr r3, [r4, #0x4]
	add r4, r3, r2
	ldrh r3, [r4, r6]
	mov r2, #0x20
	orr r2, r3
	strh r2, [r4, r6]
	b _0203084C
_0203083E:
	cmp r5, #0xc
	bne _0203084C
	ldr r4, [r4, #0x4]
	add r4, r4, r2
	ldrh r2, [r4, r6]
	orr r2, r3
	strh r2, [r4, r6]
_0203084C:
	ldrb r0, [r0, #0x0]
	asr r2, r0, #0x5
	mov r0, #0x7
	and r2, r0
	ldr r0, _02030868 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	add r1, r0, r1
	mov r0, #0x62
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
_02030860:
	mov r0, #0x1
	pop {r4-r7}
	bx lr
	nop
_02030868: .word 0x021C59F4

	thumb_func_start FUN_0203086C
FUN_0203086C: ; 0x0203086C
	bx lr
	.balign 4

	thumb_func_start FUN_02030870
FUN_02030870: ; 0x02030870
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0203091C ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030920 ; =0x0000062A
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02030884
	mov r0, #0x0
	pop {r4, pc}
_02030884:
	bl FUN_02030FE0
	cmp r0, #0x0
	bne _02030890
	mov r0, #0x0
	pop {r4, pc}
_02030890:
	ldr r0, _0203091C ; =0x021C59F4
	ldr r2, [r0, #0x4]
	ldr r0, _02030924 ; =0x00000681
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	beq _020308A0
	sub r1, r1, #0x1
	strb r1, [r2, r0]
_020308A0:
	ldr r1, _0203091C ; =0x021C59F4
	ldr r0, _02030928 ; =0x00000628
	ldr r2, [r1, #0x4]
	mov r3, #0x40
	ldrh r2, [r2, r0]
	tst r3, r2
	beq _020308C0
	ldrb r3, [r4, #0x0]
	mov r2, #0x10
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
	b _02030906
_020308C0:
	mov r3, #0x80
	tst r3, r2
	beq _020308D8
	ldrb r3, [r4, #0x0]
	mov r2, #0x14
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
	b _02030906
_020308D8:
	mov r3, #0x20
	tst r3, r2
	beq _020308F0
	ldrb r3, [r4, #0x0]
	mov r2, #0x18
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
	b _02030906
_020308F0:
	mov r3, #0x10
	tst r2, r3
	beq _02030906
	ldrb r3, [r4, #0x0]
	mov r2, #0x1c
	add r0, #0x59
	orr r2, r3
	strb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	mov r2, #0x8
	strb r2, [r1, r0]
_02030906:
	ldr r0, _0203091C ; =0x021C59F4
	ldrb r2, [r4, #0x0]
	ldr r1, [r0, #0x4]
	ldr r0, _0203092C ; =0x0000062B
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x5
	orr r0, r2
	strb r0, [r4, #0x0]
	mov r0, #0x0
	pop {r4, pc}
	nop
_0203091C: .word 0x021C59F4
_02030920: .word 0x0000062A
_02030924: .word 0x00000681
_02030928: .word 0x00000628
_0203092C: .word 0x0000062B

	thumb_func_start FUN_02030930
FUN_02030930: ; 0x02030930
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02031228
	add r5, r0, #0x0
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	ldr r0, _020309F0 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _020309F4 ; =0x00000684
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030960
	mov r0, #0x0
	b _02030962
_02030960:
	mov r0, #0x1
_02030962:
	strb r0, [r4, #0x0]
	bl FUN_0202FA28
	cmp r0, #0x0
	bne _02030972
	add r0, r4, #0x0
	bl FUN_02030870
_02030972:
	ldr r1, _020309F0 ; =0x021C59F4
	ldr r0, _020309F4 ; =0x00000684
	ldr r2, [r1, #0x4]
	mov r3, #0x0
	strb r3, [r2, r0]
	ldr r1, [r1, #0x4]
	ldr r0, _020309F8 ; =0x0000054C
	add r0, r1, r0
	bl FUN_0202D4E4
	cmp r0, #0x0
	beq _0203099E
	ldrb r1, [r4, #0x0]
	mov r0, #0x2
	orr r0, r1
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r0, #0x2
	bne _020309E8
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0203099E:
	sub r0, r5, #0x1
	str r0, [sp, #0x4]
	add r0, r4, #0x1
	str r0, [sp, #0x0]
	ldr r0, _020309F0 ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020309F8 ; =0x0000054C
	add r0, r1, r0
	add r1, sp, #0x0
	bl FUN_0202D760
	cmp r0, #0x0
	bne _020309C4
	ldr r0, _020309F0 ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _020309F4 ; =0x00000684
	strb r2, [r1, r0]
_020309C4:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _020309E8
	ldr r2, _020309F0 ; =0x021C59F4
	ldr r1, _020309FC ; =0x0000065E
	ldr r3, [r2, #0x4]
	ldrb r0, [r3, r1]
	add r0, r0, #0x1
	strb r0, [r3, r1]
	ldr r2, [r2, #0x4]
	ldrb r0, [r4, #0x0]
	ldrb r1, [r2, r1]
	lsl r2, r1, #0x4
	mov r1, #0xf0
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x0]
_020309E8:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_020309F0: .word 0x021C59F4
_020309F4: .word 0x00000684
_020309F8: .word 0x0000054C
_020309FC: .word 0x0000065E

	thumb_func_start FUN_02030A00
FUN_02030A00: ; 0x02030A00
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0xb
	strb r0, [r4, #0x0]
	ldr r0, _02030A6C ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030A70 ; =0x00000685
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030A1A
	mov r0, #0x0
	b _02030A1C
_02030A1A:
	mov r0, #0x1
_02030A1C:
	strb r0, [r4, #0x1]
	bl FUN_0202CB8C
	asr r1, r0, #0x8
	strb r1, [r4, #0x2]
	strb r0, [r4, #0x3]
	mov r0, #0xbb
	str r0, [sp, #0x4]
	add r0, r4, #0x5
	str r0, [sp, #0x0]
	ldr r0, _02030A6C ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030A74 ; =0x0000056C
	add r0, r1, r0
	add r1, sp, #0x0
	bl FUN_0202D760
	cmp r0, #0x0
	beq _02030A5A
	ldr r0, _02030A6C ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030A70 ; =0x00000685
	strb r2, [r1, r0]
	ldr r1, [sp, #0x4]
	mov r0, #0xbb
	sub r0, r0, r1
	add sp, #0x8
	strb r0, [r4, #0x4]
	pop {r4, pc}
_02030A5A:
	ldr r0, _02030A6C ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _02030A70 ; =0x00000685
	strb r2, [r1, r0]
	mov r0, #0xbb
	strb r0, [r4, #0x4]
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_02030A6C: .word 0x021C59F4
_02030A70: .word 0x00000685
_02030A74: .word 0x0000056C

	thumb_func_start FUN_02030A78
FUN_02030A78: ; 0x02030A78
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030A9C
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030A9C
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030A9C:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02030AD4 ; =0x021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030AD8 ; =0x0000054C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030AC0
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030AC0:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030ACC
	bl FUN_02031454
_02030ACC:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02030AD4: .word 0x021C59F4
_02030AD8: .word 0x0000054C

	thumb_func_start FUN_02030ADC
FUN_02030ADC: ; 0x02030ADC
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030B00
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030B00
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030B00:
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02030B34 ; =0x021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030B38 ; =0x0000054C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030B22
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030B22:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030B2E
	bl FUN_02031454
_02030B2E:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02030B34: .word 0x021C59F4
_02030B38: .word 0x0000054C

	thumb_func_start FUN_02030B3C
FUN_02030B3C: ; 0x02030B3C
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02030B58
	bl ErrorHandling
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030B58:
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030B70
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030B70
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030B70:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030B86
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02030A78
	add sp, #0x8
	pop {r4-r6, pc}
_02030B86:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02030BBC ; =0x021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030BC0 ; =0x0000056C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030BAA
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030BAA:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030BB6
	bl FUN_02031454
_02030BB6:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02030BBC: .word 0x021C59F4
_02030BC0: .word 0x0000056C

	thumb_func_start FUN_02030BC4
FUN_02030BC4: ; 0x02030BC4
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02030BE0
	bl FUN_02031454
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030BE0:
	mov r0, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _02030BF8
	bl FUN_02031280
	cmp r0, #0x0
	bne _02030BF8
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02030BF8:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02030C0E
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02030ADC
	add sp, #0x8
	pop {r4-r6, pc}
_02030C0E:
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02030C44 ; =0x021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02030C48 ; =0x0000056C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	cmp r0, #0x0
	beq _02030C30
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_02030C30:
	bl FUN_02033534
	cmp r0, #0xa
	bne _02030C3C
	bl FUN_02031454
_02030C3C:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02030C44: .word 0x021C59F4
_02030C48: .word 0x0000056C

	thumb_func_start FUN_02030C4C
FUN_02030C4C: ; 0x02030C4C
	ldr r3, _02030C54 ; =FUN_02030BC4
	mov r2, #0x0
	bx r3
	nop
_02030C54: .word FUN_02030BC4

	thumb_func_start FUN_02030C58
FUN_02030C58: ; 0x02030C58
	ldr r0, _02030C64 ; =0x021C59F4
	ldr r3, _02030C68 ; =FUN_0202D498
	ldr r1, [r0, #0x4]
	ldr r0, _02030C6C ; =0x00000464
	add r0, r1, r0
	bx r3
	.balign 4
_02030C64: .word 0x021C59F4
_02030C68: .word FUN_0202D498
_02030C6C: .word 0x00000464

	thumb_func_start FUN_02030C70
FUN_02030C70: ; 0x02030C70
	push {r4, lr}
	ldr r4, [sp, #0x8]
	bl FUN_0202D934
	mov r0, #0xee
	strb r0, [r4, #0xa]
	ldr r0, _02030C88 ; =0x0000FFFF
	strh r0, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_02030C88: .word 0x0000FFFF

	thumb_func_start FUN_02030C8C
FUN_02030C8C: ; 0x02030C8C
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r0, #0x0
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r5, [sp, #0x28]
	bl FUN_0202D478
	cmp r0, #0x0
	beq _02030D94
_02030CA0:
	ldrb r7, [r5, #0xa]
	cmp r7, #0xee
	bne _02030CB2
	add r0, r6, #0x0
	bl FUN_0202D41C
	add r7, r0, #0x0
	cmp r7, #0xee
	beq _02030D8A
_02030CB2:
	mov r0, #0x4
	ldrsh r0, [r6, r0]
	strb r7, [r5, #0xa]
	ldrh r4, [r5, #0x8]
	str r0, [sp, #0x10]
	ldr r0, _02030D98 ; =0x0000FFFF
	cmp r4, r0
	bne _02030D06
	add r0, r7, #0x0
	bl FUN_0202D9A0
	add r4, r0, #0x0
	ldr r0, _02030D9C ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030DA0 ; =0x00000689
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030D94
	ldr r0, _02030D98 ; =0x0000FFFF
	cmp r4, r0
	bne _02030D04
	add r0, r6, #0x0
	bl FUN_0202D478
	cmp r0, #0x1
	bge _02030CEE
	ldr r0, [sp, #0x10]
	add sp, #0x14
	strh r0, [r6, #0x4]
	pop {r4-r7, pc}
_02030CEE:
	add r0, r6, #0x0
	bl FUN_0202D41C
	lsl r4, r0, #0x8
	add r0, r6, #0x0
	bl FUN_0202D41C
	add r4, r4, r0
	mov r0, #0x4
	ldrsh r0, [r6, r0]
	str r0, [sp, #0x10]
_02030D04:
	strh r4, [r5, #0x8]
_02030D06:
	add r0, r7, #0x0
	bl FUN_0202DA04
	cmp r0, #0x0
	beq _02030D5E
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02030D22
	ldrh r2, [r5, #0x8]
	ldr r1, [sp, #0x4]
	add r0, r7, #0x0
	bl FUN_0202DA40
	str r0, [r5, #0x4]
_02030D22:
	ldr r2, [r5, #0x0]
	ldr r1, [sp, #0x8]
	add r0, r6, #0x0
	sub r2, r4, r2
	bl FUN_0202D400
	ldr r2, [r5, #0x4]
	str r0, [sp, #0xc]
	cmp r2, #0x0
	beq _02030D42
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x8]
	add r1, r2, r1
	ldr r2, [sp, #0xc]
	bl MI_CpuCopy8
_02030D42:
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	str r0, [r5, #0x0]
	cmp r0, r4
	blt _02030D8A
	str r5, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r3, [r5, #0x4]
	add r1, r7, #0x0
	add r2, r4, #0x0
	bl FUN_02030C70
	b _02030D8A
_02030D5E:
	add r0, r6, #0x0
	bl FUN_0202D478
	cmp r0, r4
	blt _02030D82
	ldr r1, [sp, #0x8]
	add r0, r6, #0x0
	add r2, r4, #0x0
	bl FUN_0202D400
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r1, r7, #0x0
	add r2, r4, #0x0
	str r5, [sp, #0x0]
	bl FUN_02030C70
	b _02030D8A
_02030D82:
	ldr r0, [sp, #0x10]
	add sp, #0x14
	strh r0, [r6, #0x4]
	pop {r4-r7, pc}
_02030D8A:
	add r0, r6, #0x0
	bl FUN_0202D478
	cmp r0, #0x0
	bne _02030CA0
_02030D94:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02030D98: .word 0x0000FFFF
_02030D9C: .word 0x021C59F4
_02030DA0: .word 0x00000689

	thumb_func_start FUN_02030DA4
FUN_02030DA4: ; 0x02030DA4
	push {r3, lr}
	ldr r0, _02030DF0 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02030DEE
	ldr r0, _02030DF4 ; =0x0000068B
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030DEE
	mov r0, #0x47
	lsl r0, r0, #0x4
	add r0, r1, r0
	bl FUN_0202D4BC
	ldr r0, _02030DF0 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	mov r0, #0x47
	lsl r0, r0, #0x4
	add r0, r1, r0
	bl FUN_0202D478
	cmp r0, #0x0
	ble _02030DEE
	ldr r0, _02030DF0 ; =0x021C59F4
	mov r2, #0x47
	ldr r3, [r0, #0x4]
	ldr r0, _02030DF8 ; =0x000005EC
	lsl r2, r2, #0x4
	add r0, r3, r0
	str r0, [sp, #0x0]
	add r0, r3, r2
	sub r2, #0x10
	ldr r2, [r3, r2]
	mov r1, #0x0
	mov r3, #0x1
	bl FUN_02030C8C
_02030DEE:
	pop {r3, pc}
	.balign 4
_02030DF0: .word 0x021C59F4
_02030DF4: .word 0x0000068B
_02030DF8: .word 0x000005EC

	thumb_func_start FUN_02030DFC
FUN_02030DFC: ; 0x02030DFC
	push {r3-r7, lr}
	ldr r0, _02030E6C ; =0x021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02030E68
	ldr r0, _02030E70 ; =0x0000068B
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _02030E68
	bl FUN_02033534
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r7, r0, #0x1
	mov r4, #0x0
	cmp r7, #0x0
	ble _02030E68
	ldr r6, _02030E6C ; =0x021C59F4
	add r5, r4, #0x0
_02030E26:
	ldr r1, [r6, #0x4]
	ldr r0, _02030E74 ; =0x000004E8
	add r0, r1, r0
	add r0, r0, r5
	bl FUN_0202D4BC
	ldr r1, [r6, #0x4]
	ldr r0, _02030E74 ; =0x000004E8
	add r0, r1, r0
	add r0, r0, r5
	bl FUN_0202D478
	cmp r0, #0x0
	ble _02030E60
	ldr r3, [r6, #0x4]
	ldr r0, _02030E78 ; =0x0000058C
	mov r2, #0x46
	add r0, r3, r0
	add r0, r0, r5
	str r0, [sp, #0x0]
	ldr r0, _02030E74 ; =0x000004E8
	lsl r2, r2, #0x4
	add r0, r3, r0
	ldr r2, [r3, r2]
	add r0, r0, r5
	add r1, r4, #0x0
	mov r3, #0x0
	bl FUN_02030C8C
_02030E60:
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, r7
	blt _02030E26
_02030E68:
	pop {r3-r7, pc}
	nop
_02030E6C: .word 0x021C59F4
_02030E70: .word 0x0000068B
_02030E74: .word 0x000004E8
_02030E78: .word 0x0000058C

	thumb_func_start FUN_02030E7C
FUN_02030E7C: ; 0x02030E7C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02030F14 ; =0x021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _02030E8C
	mov r0, #0x0
	pop {r4, pc}
_02030E8C:
	bl FUN_02033534
	cmp r0, #0x13
	blt _02030EC0
	ldr r0, _02030F14 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030F18 ; =0x00000687
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02030EBC
	bl MOD04_021D8018
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02030EBC
	cmp r4, #0x0
	bne _02030EB4
	mov r0, #0x1
	pop {r4, pc}
_02030EB4:
	cmp r4, #0x1
	bne _02030EBC
	mov r0, #0x1
	pop {r4, pc}
_02030EBC:
	mov r0, #0x0
	pop {r4, pc}
_02030EC0:
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02030ECC
	mov r0, #0x0
	pop {r4, pc}
_02030ECC:
	bl FUN_0202CBD4
	cmp r0, #0x4
	beq _02030ED8
	mov r0, #0x0
	pop {r4, pc}
_02030ED8:
	bl FUN_02031190
	cmp r4, r0
	bne _02030EE4
	mov r0, #0x1
	pop {r4, pc}
_02030EE4:
	bl FUN_02031190
	cmp r0, #0x0
	bne _02030EFE
	bl FUN_0202CB8C
	mov r1, #0x1
	add r2, r1, #0x0
	lsl r2, r4
	tst r0, r2
	beq _02030F10
	add r0, r1, #0x0
	pop {r4, pc}
_02030EFE:
	ldr r0, _02030F14 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02030F1C ; =0x0000065C
	ldrh r2, [r1, r0]
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r1, r4
	tst r1, r2
	bne _02030F12
_02030F10:
	mov r0, #0x0
_02030F12:
	pop {r4, pc}
	.balign 4
_02030F14: .word 0x021C59F4
_02030F18: .word 0x00000687
_02030F1C: .word 0x0000065C

	thumb_func_start FUN_02030F20
FUN_02030F20: ; 0x02030F20
	push {r3-r5, lr}
	mov r4, #0x0
	add r5, r4, #0x0
_02030F26:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02030F34
	add r4, r4, #0x1
_02030F34:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _02030F26
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02030F40
FUN_02030F40: ; 0x02030F40
	push {r3, lr}
	ldr r0, _02030F5C ; =0x021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02030F56
	bl FUN_02033534
	cmp r0, #0x13
	blt _02030F56
	mov r0, #0x1
	pop {r3, pc}
_02030F56:
	bl FUN_0202EDF8
	pop {r3, pc}
	.balign 4
_02030F5C: .word 0x021C59F4

	thumb_func_start FUN_02030F60
FUN_02030F60: ; 0x02030F60
	ldr r1, _02030F6C ; =0x021C59F4
	ldr r2, [r1, #0x4]
	ldr r1, _02030F70 ; =0x0000062B
	strb r0, [r2, r1]
	bx lr
	nop
_02030F6C: .word 0x021C59F4
_02030F70: .word 0x0000062B

	thumb_func_start FUN_02030F74
FUN_02030F74: ; 0x02030F74
	ldr r1, _02030F84 ; =0x021C59F4
	ldr r1, [r1, #0x4]
	add r1, r1, r0
	mov r0, #0x62
	lsl r0, r0, #0x4
	ldrb r0, [r1, r0]
	bx lr
	nop
_02030F84: .word 0x021C59F4

	thumb_func_start FUN_02030F88
FUN_02030F88: ; 0x02030F88
	ldr r1, _02030FA4 ; =0x021C59F4
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	bne _02030F94
	mov r0, #0x0
	bx lr
_02030F94:
	mov r1, #0x61
	lsl r1, r1, #0x4
	add r3, r2, r1
	lsl r2, r0, #0x1
	ldrh r0, [r3, r2]
	mov r1, #0x0
	strh r1, [r3, r2]
	bx lr
	.balign 4
_02030FA4: .word 0x021C59F4

	thumb_func_start FUN_02030FA8
FUN_02030FA8: ; 0x02030FA8
	ldr r0, _02030FC0 ; =0x021C59F4
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	beq _02030FBC
	ldr r1, _02030FC4 ; =0x00000628
	mov r0, #0x2
	ldrh r2, [r3, r1]
	lsl r0, r0, #0xe
	orr r0, r2
	strh r0, [r3, r1]
_02030FBC:
	bx lr
	nop
_02030FC0: .word 0x021C59F4
_02030FC4: .word 0x00000628

	thumb_func_start FUN_02030FC8
FUN_02030FC8: ; 0x02030FC8
	ldr r0, _02030FD8 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _02030FD6
	ldr r0, _02030FDC ; =0x00000628
	mov r1, #0x0
	strh r1, [r2, r0]
_02030FD6:
	bx lr
	.balign 4
_02030FD8: .word 0x021C59F4
_02030FDC: .word 0x00000628

	thumb_func_start FUN_02030FE0
FUN_02030FE0: ; 0x02030FE0
	ldr r0, _02030FF8 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _02030FF4
	ldr r0, _02030FFC ; =0x00000628
	ldrh r1, [r1, r0]
	mov r0, #0x2
	lsl r0, r0, #0xe
	and r0, r1
	bx lr
_02030FF4:
	mov r0, #0x1
	bx lr
	.balign 4
_02030FF8: .word 0x021C59F4
_02030FFC: .word 0x00000628

	thumb_func_start FUN_02031000
FUN_02031000: ; 0x02031000
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _02031030
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02031050 ; =0x021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031054 ; =0x0000054C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	add sp, #0x8
	pop {r4-r6, pc}
_02031030:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, _02031050 ; =0x021C59F4
	add r2, r4, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031058 ; =0x0000056C
	add r3, r6, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	bl FUN_0202D684
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02031050: .word 0x021C59F4
_02031054: .word 0x0000054C
_02031058: .word 0x0000056C

	thumb_func_start FUN_0203105C
FUN_0203105C: ; 0x0203105C
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, _02031080 ; =0x021C59F4
	add r4, r1, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031084 ; =0x0000054C
	add r3, r2, #0x0
	add r0, r1, r0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202D684
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02031080: .word 0x021C59F4
_02031084: .word 0x0000054C

	thumb_func_start FUN_02031088
FUN_02031088: ; 0x02031088
	push {r3, lr}
	ldr r0, _02031100 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _020310FC
	ldr r1, _02031104 ; =0x0000067B
	ldrb r0, [r2, r1]
	cmp r0, #0x1
	beq _020310A0
	cmp r0, #0x3
	beq _020310D8
	pop {r3, pc}
_020310A0:
	bl FUN_0202FA28
	cmp r0, #0x1
	bne _020310B8
	ldr r1, _02031100 ; =0x021C59F4
	mov r0, #0xb
	ldr r2, [r1, #0x4]
	ldr r1, _02031108 ; =0x0000067C
	add r1, r2, r1
	bl FUN_020311D0
	b _020310C8
_020310B8:
	ldr r1, _02031100 ; =0x021C59F4
	mov r0, #0xb
	ldr r2, [r1, #0x4]
	ldr r1, _02031108 ; =0x0000067C
	add r1, r2, r1
	mov r2, #0x1
	bl FUN_02030BC4
_020310C8:
	cmp r0, #0x0
	beq _020310FC
	ldr r0, _02031100 ; =0x021C59F4
	mov r2, #0x2
	ldr r1, [r0, #0x4]
	ldr r0, _02031104 ; =0x0000067B
	strb r2, [r1, r0]
	pop {r3, pc}
_020310D8:
	add r1, r1, #0x1
	mov r0, #0xc
	add r1, r2, r1
	bl FUN_020311D0
	cmp r0, #0x0
	beq _020310FC
	ldr r0, _02031100 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02031108 ; =0x0000067C
	ldrb r0, [r1, r0]
	bl FUN_0202F9E0
	ldr r0, _02031100 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _02031104 ; =0x0000067B
	strb r2, [r1, r0]
_020310FC:
	pop {r3, pc}
	nop
_02031100: .word 0x021C59F4
_02031104: .word 0x0000067B
_02031108: .word 0x0000067C

	thumb_func_start FUN_0203110C
FUN_0203110C: ; 0x0203110C
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203112A
	ldr r1, _0203112C ; =0x021C59F4
	ldr r0, _02031130 ; =0x0000067B
	ldr r2, [r1, #0x4]
	mov r3, #0x1
	strb r3, [r2, r0]
	ldrb r2, [r4, #0x0]
	ldr r1, [r1, #0x4]
	add r0, r0, #0x1
	strb r2, [r1, r0]
_0203112A:
	pop {r4, pc}
	.balign 4
_0203112C: .word 0x021C59F4
_02031130: .word 0x0000067B

	thumb_func_start FUN_02031134
FUN_02031134: ; 0x02031134
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	beq _02031152
	ldr r1, _02031154 ; =0x021C59F4
	ldrb r3, [r4, #0x0]
	ldr r2, [r1, #0x4]
	ldr r0, _02031158 ; =0x0000067C
	strb r3, [r2, r0]
	ldr r1, [r1, #0x4]
	mov r2, #0x3
	sub r0, r0, #0x1
	strb r2, [r1, r0]
_02031152:
	pop {r4, pc}
	.balign 4
_02031154: .word 0x021C59F4
_02031158: .word 0x0000067C

	thumb_func_start FUN_0203115C
FUN_0203115C: ; 0x0203115C
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _02031184
	ldr r0, _02031188 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _0203118C ; =0x0000067B
	ldrb r0, [r1, r0]
	cmp r0, #0x2
	bne _02031184
	ldrb r0, [r4, #0x0]
	bl FUN_0202F9E0
	ldr r0, _02031188 ; =0x021C59F4
	mov r2, #0x0
	ldr r1, [r0, #0x4]
	ldr r0, _0203118C ; =0x0000067B
	strb r2, [r1, r0]
_02031184:
	pop {r4, pc}
	nop
_02031188: .word 0x021C59F4
_0203118C: .word 0x0000067B

	thumb_func_start FUN_02031190
FUN_02031190: ; 0x02031190
	push {r3, lr}
	ldr r0, _020311CC ; =0x021C59F4
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020311C6
	bl FUN_02033534
	cmp r0, #0x13
	blt _020311B4
	bl MOD04_021D8018
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020311C6
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	pop {r3, pc}
_020311B4:
	bl FUN_02031280
	cmp r0, #0x0
	beq _020311C0
	mov r0, #0x0
	pop {r3, pc}
_020311C0:
	bl FUN_0202D19C
	pop {r3, pc}
_020311C6:
	mov r0, #0x0
	pop {r3, pc}
	nop
_020311CC: .word 0x021C59F4

	thumb_func_start FUN_020311D0
FUN_020311D0: ; 0x020311D0
	ldr r3, _020311D8 ; =FUN_02030ADC
	mov r2, #0x0
	bx r3
	nop
_020311D8: .word FUN_02030ADC

	thumb_func_start FUN_020311DC
FUN_020311DC: ; 0x020311DC
	ldr r3, _020311E4 ; =FUN_02030ADC
	mov r1, #0x0
	add r2, r1, #0x0
	bx r3
	.balign 4
_020311E4: .word FUN_02030ADC

	thumb_func_start FUN_020311E8
FUN_020311E8: ; 0x020311E8
	ldr r3, _020311EC ; =FUN_0202EE24
	bx r3
	.balign 4
_020311EC: .word FUN_0202EE24

	thumb_func_start FUN_020311F0
FUN_020311F0: ; 0x020311F0
	push {r3, lr}
	bl FUN_02031280
	cmp r0, #0x0
	beq _020311FE
	mov r0, #0x0
	pop {r3, pc}
_020311FE:
	ldr r0, _02031220 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0203121A
	ldr r0, _02031224 ; =0x00000689
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0203121A
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	pop {r3, pc}
_0203121A:
	bl FUN_0202EE60
	pop {r3, pc}
	.balign 4
_02031220: .word 0x021C59F4
_02031224: .word 0x00000689

	thumb_func_start FUN_02031228
FUN_02031228: ; 0x02031228
	push {r3, lr}
	bl FUN_0202D858
	cmp r0, #0x5
	blo _02031236
	mov r0, #0xc
	pop {r3, pc}
_02031236:
	bl FUN_0202FA28
	cmp r0, #0x0
	bne _02031242
	mov r0, #0xc
	pop {r3, pc}
_02031242:
	mov r0, #0x26
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031248
FUN_02031248: ; 0x02031248
	push {r3, lr}
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D858
	add r0, r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031258
FUN_02031258: ; 0x02031258
	push {r3, lr}
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_0202D884
	add r0, r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031268
FUN_02031268: ; 0x02031268
	ldr r1, _02031278 ; =0x021C59F4
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _02031274
	ldr r1, _0203127C ; =0x00000686
	strb r0, [r2, r1]
_02031274:
	bx lr
	nop
_02031278: .word 0x021C59F4
_0203127C: .word 0x00000686

	thumb_func_start FUN_02031280
FUN_02031280: ; 0x02031280
	ldr r0, _02031294 ; =0x021C59F4
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0203128E
	ldr r0, _02031298 ; =0x00000686
	ldrb r0, [r1, r0]
	bx lr
_0203128E:
	mov r0, #0x0
	bx lr
	nop
_02031294: .word 0x021C59F4
_02031298: .word 0x00000686

	thumb_func_start FUN_0203129C
FUN_0203129C: ; 0x0203129C
	push {r3, lr}
	bl FUN_0202F03C
	cmp r0, #0x0
	bne _020312B6
	bl FUN_02031190
	cmp r0, #0x0
	bne _020312B6
	mov r0, #0x2
	add r1, sp, #0x0
	bl FUN_02030C4C
_020312B6:
	bl FUN_0202F05C
	pop {r3, pc}

	thumb_func_start FUN_020312BC
FUN_020312BC: ; 0x020312BC
	push {r3-r7, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	add r0, sp, #0x10
	add r1, sp, #0x4
	bl FUN_0201265C
	ldr r0, _02031340 ; =0x021C48B8
	ldr r6, [sp, #0x10]
	mov r5, #0x0
	lsr r7, r6, #0x1c
	lsl r5, r5, #0x4
	ldr r1, [sp, #0xc]
	ldr r0, [r0, #0x2c]
	lsl r6, r6, #0x4
	add r3, r1, r0
	ldr r0, [sp, #0x18]
	orr r5, r7
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	add r6, r0, r6
	ldr r0, _02031344 ; =0x00000000
	ldr r2, [sp, #0x8]
	adc r0, r5
	lsr r5, r6, #0x1b
	lsl r0, r0, #0x5
	orr r0, r5
	ldr r5, [sp, #0x0]
	lsl r6, r6, #0x5
	add r6, r5, r6
	ldr r5, _02031344 ; =0x00000000
	adc r5, r0
	lsr r0, r6, #0x1b
	lsl r5, r5, #0x5
	orr r5, r0
	lsl r0, r6, #0x5
	add r6, r1, r0
	ldr r1, _02031344 ; =0x00000000
	adc r1, r5
	lsr r0, r6, #0x1a
	lsl r1, r1, #0x6
	orr r1, r0
	lsl r0, r6, #0x6
	add r5, r2, r0
	ldr r2, _02031344 ; =0x00000000
	adc r2, r1
	lsr r0, r5, #0x1a
	lsl r1, r2, #0x6
	orr r1, r0
	lsl r0, r5, #0x6
	add r2, r3, r0
	ldr r0, _02031344 ; =0x00000000
	str r2, [r4, #0x0]
	adc r0, r1
	str r0, [r4, #0x4]
	ldr r1, _02031348 ; =0x6C078965
	ldr r0, _0203134C ; =0x5D588B65
	str r1, [r4, #0x8]
	str r0, [r4, #0xc]
	ldr r0, _02031350 ; =0x00269EC3
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_02031340: .word 0x021C48B8
_02031344: .word 0x00000000
_02031348: .word 0x6C078965
_0203134C: .word 0x5D588B65
_02031350: .word 0x00269EC3

	thumb_func_start FUN_02031354
FUN_02031354: ; 0x02031354
	add r1, r0, #0x0
	ldr r0, _02031364 ; =0x021C59F4
	ldr r3, _02031368 ; =FUN_0202D830
	ldr r2, [r0, #0x4]
	ldr r0, _0203136C ; =0x0000056C
	add r0, r2, r0
	bx r3
	nop
_02031364: .word 0x021C59F4
_02031368: .word FUN_0202D830
_0203136C: .word 0x0000056C

	thumb_func_start FUN_02031370
FUN_02031370: ; 0x02031370
	ldr r0, _0203137C ; =0x021C59F4
	ldr r3, _02031380 ; =FUN_0202D4E4
	ldr r1, [r0, #0x4]
	ldr r0, _02031384 ; =0x0000056C
	add r0, r1, r0
	bx r3
	.balign 4
_0203137C: .word 0x021C59F4
_02031380: .word FUN_0202D4E4
_02031384: .word 0x0000056C

	thumb_func_start FUN_02031388
FUN_02031388: ; 0x02031388
	ldr r0, _02031394 ; =0x021C59F4
	ldr r3, _02031398 ; =FUN_0202D4E4
	ldr r1, [r0, #0x4]
	ldr r0, _0203139C ; =0x0000054C
	add r0, r1, r0
	bx r3
	.balign 4
_02031394: .word 0x021C59F4
_02031398: .word FUN_0202D4E4
_0203139C: .word 0x0000054C

	thumb_func_start FUN_020313A0
FUN_020313A0: ; 0x020313A0
	ldr r1, _020313AC ; =0x021C59F4
	ldr r2, [r1, #0x4]
	ldr r1, _020313B0 ; =0x00000687
	strb r0, [r2, r1]
	bx lr
	nop
_020313AC: .word 0x021C59F4
_020313B0: .word 0x00000687

	thumb_func_start FUN_020313B4
FUN_020313B4: ; 0x020313B4
	ldr r2, _020313C4 ; =0x021C59F4
	ldr r2, [r2, #0x4]
	cmp r2, #0x0
	beq _020313C2
	add r2, r2, r1
	ldr r1, _020313C8 ; =0x00000677
	strb r0, [r2, r1]
_020313C2:
	bx lr
	.balign 4
_020313C4: .word 0x021C59F4
_020313C8: .word 0x00000677

	thumb_func_start FUN_020313CC
FUN_020313CC: ; 0x020313CC
	ldr r1, _020313E4 ; =0x021C59F4
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _020313E0
	add r2, r1, r0
	ldr r1, _020313E8 ; =0x00000677
	ldrb r1, [r2, r1]
	cmp r1, #0xff
	beq _020313E0
	add r0, r1, #0x0
_020313E0:
	bx lr
	nop
_020313E4: .word 0x021C59F4
_020313E8: .word 0x00000677

	thumb_func_start FUN_020313EC
FUN_020313EC: ; 0x020313EC
	push {r3, lr}
	bl FUN_02033534
	cmp r0, #0x13
	bge _020313FA
	mov r0, #0x0
	pop {r3, pc}
_020313FA:
	bl MOD04_021D8624
	pop {r3, pc}

	thumb_func_start FUN_02031400
FUN_02031400: ; 0x02031400
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02033534
	cmp r0, #0x13
	blt _02031430
	ldr r2, _02031434 ; =0x021C59F4
	mov r1, #0x63
	ldr r0, [r2, #0x4]
	lsl r1, r1, #0x4
	str r4, [r0, r1]
	cmp r4, #0x0
	beq _02031430
	ldr r3, [r2, #0x4]
	mov r4, #0x0
	add r0, r1, #0x4
	str r4, [r3, r0]
	add r0, r1, #0x0
	ldr r3, [r2, #0x4]
	add r0, #0x8
	str r4, [r3, r0]
	ldr r0, [r2, #0x4]
	add r1, #0xc
	str r4, [r0, r1]
_02031430:
	pop {r4, pc}
	nop
_02031434: .word 0x021C59F4

	thumb_func_start FUN_02031438
FUN_02031438: ; 0x02031438
	ldr r0, _0203144C ; =0x021C59F4
	ldr r1, [r0, #0x4]
	ldr r0, _02031450 ; =0x00000681
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _02031448
	mov r0, #0x1
	bx lr
_02031448:
	mov r0, #0x0
	bx lr
	.balign 4
_0203144C: .word 0x021C59F4
_02031450: .word 0x00000681

	thumb_func_start FUN_02031454
FUN_02031454: ; 0x02031454
	ldr r0, _02031460 ; =0x021C59F4
	mov r2, #0x1
	ldr r1, [r0, #0x4]
	ldr r0, _02031464 ; =0x00000689
	strb r2, [r1, r0]
	bx lr
	.balign 4
_02031460: .word 0x021C59F4
_02031464: .word 0x00000689

	thumb_func_start FUN_02031468
FUN_02031468: ; 0x02031468
	ldr r0, _02031478 ; =0x021C59F4
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _02031476
	ldr r0, _0203147C ; =0x0000068A
	mov r1, #0x1
	strb r1, [r2, r0]
_02031476:
	bx lr
	.balign 4
_02031478: .word 0x021C59F4
_0203147C: .word 0x0000068A

	thumb_func_start FUN_02031480
FUN_02031480: ; 0x02031480
	push {r4, lr}
	ldr r1, _020314C8 ; =0x021C59FC
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _0203149C
	ldr r1, _020314CC ; =0x00000253
	bl FUN_02016998
	ldr r1, _020314C8 ; =0x021C59FC
	ldr r2, _020314CC ; =0x00000253
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
_0203149C:
	ldr r1, _020314C8 ; =0x021C59FC
	mov r3, #0x0
	mov r0, #0xff
_020314A2:
	ldr r2, [r1, #0x0]
	add r2, r2, r3
	add r3, r3, #0x1
	strb r0, [r2, #0x10]
	cmp r3, #0x8
	blt _020314A2
	ldr r3, _020314C8 ; =0x021C59FC
	mov r1, #0x25
	ldr r2, [r3, #0x0]
	lsl r1, r1, #0x4
	strb r0, [r2, r1]
	ldr r4, [r3, #0x0]
	add r2, r1, #0x1
	strb r0, [r4, r2]
	ldr r2, [r3, #0x0]
	mov r4, #0x0
	add r0, r1, #0x2
	strb r4, [r2, r0]
	pop {r4, pc}
	.balign 4
_020314C8: .word 0x021C59FC
_020314CC: .word 0x00000253

	thumb_func_start FUN_020314D0
FUN_020314D0: ; 0x020314D0
	push {r3, lr}
	ldr r0, _020314E4 ; =0x021C59FC
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _020314E4 ; =0x021C59FC
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3, pc}
	nop
_020314E4: .word 0x021C59FC

	thumb_func_start FUN_020314E8
FUN_020314E8: ; 0x020314E8
	ldr r0, _020314F8 ; =0x021C59FC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020314F4
	mov r0, #0x1
	bx lr
_020314F4:
	mov r0, #0x0
	bx lr
	.balign 4
_020314F8: .word 0x021C59FC

	thumb_func_start FUN_020314FC
FUN_020314FC: ; 0x020314FC
	push {r3-r6, lr}
	sub sp, #0x4
	ldrb r1, [r2, #0x0]
	add r5, r0, #0x0
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	bl FUN_02031190
	cmp r0, #0x0
	bne _02031556
	add r0, sp, #0x0
	strb r5, [r0, #0x1]
	ldrb r1, [r0, #0x0]
	strb r1, [r0, #0x2]
	add r1, sp, #0x0
	mov r0, #0x12
	add r1, #0x1
	bl FUN_02030C4C
	ldr r6, _0203155C ; =0x021C59FC
	add r4, sp, #0x0
	ldr r0, [r6, #0x0]
	ldrb r1, [r4, #0x0]
	add r0, r0, r5
	mov r5, #0x0
	strb r1, [r0, #0x10]
_02031530:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02031548
	ldr r0, [r6, #0x0]
	ldrb r1, [r4, #0x0]
	add r0, r0, r5
	ldrb r0, [r0, #0x10]
	cmp r1, r0
	bne _02031556
_02031548:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _02031530
	mov r0, #0x11
	add r1, sp, #0x0
	bl FUN_02030C4C
_02031556:
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_0203155C: .word 0x021C59FC

	thumb_func_start FUN_02031560
FUN_02031560: ; 0x02031560
	ldr r0, _02031570 ; =0x021C59FC
	ldrb r3, [r2, #0x1]
	ldr r1, [r0, #0x0]
	ldrb r0, [r2, #0x0]
	add r0, r1, r0
	strb r3, [r0, #0x10]
	bx lr
	nop
_02031570: .word 0x021C59FC

	thumb_func_start FUN_02031574
FUN_02031574: ; 0x02031574
	ldr r0, _02031584 ; =0x021C59FC
	ldrb r2, [r2, #0x0]
	ldr r1, [r0, #0x0]
	mov r0, #0x25
	lsl r0, r0, #0x4
	strb r2, [r1, r0]
	bx lr
	nop
_02031584: .word 0x021C59FC

	thumb_func_start FUN_02031588
FUN_02031588: ; 0x02031588
	ldr r2, _0203159C ; =0x021C59FC
	ldr r1, _020315A0 ; =0x00000251
	ldr r3, [r2, #0x0]
	strb r0, [r3, r1]
	ldr r2, [r2, #0x0]
	mov r3, #0x1
	add r0, r1, #0x1
	strb r3, [r2, r0]
	bx lr
	nop
_0203159C: .word 0x021C59FC
_020315A0: .word 0x00000251

	thumb_func_start FUN_020315A4
FUN_020315A4: ; 0x020315A4
	push {r3, lr}
	ldr r0, _020315D0 ; =0x021C59FC
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020315CE
	ldr r1, _020315D4 ; =0x00000252
	ldrb r0, [r2, r1]
	cmp r0, #0x0
	beq _020315CE
	sub r1, r1, #0x1
	mov r0, #0x10
	add r1, r2, r1
	bl FUN_020311D0
	cmp r0, #0x0
	beq _020315CE
	ldr r0, _020315D0 ; =0x021C59FC
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _020315D4 ; =0x00000252
	strb r2, [r1, r0]
_020315CE:
	pop {r3, pc}
	.balign 4
_020315D0: .word 0x021C59FC
_020315D4: .word 0x00000252

	thumb_func_start FUN_020315D8
FUN_020315D8: ; 0x020315D8
	ldr r1, _020315F8 ; =0x021C59FC
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	bne _020315E4
	mov r0, #0x1
	bx lr
_020315E4:
	mov r1, #0x25
	lsl r1, r1, #0x4
	ldrb r1, [r2, r1]
	cmp r1, r0
	bne _020315F2
	mov r0, #0x1
	bx lr
_020315F2:
	mov r0, #0x0
	bx lr
	nop
_020315F8: .word 0x021C59FC

	thumb_func_start FUN_020315FC
FUN_020315FC: ; 0x020315FC
	ldr r1, _02031608 ; =0x021C59FC
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	ldrb r0, [r0, #0x10]
	bx lr
	nop
_02031608: .word 0x021C59FC

	thumb_func_start FUN_0203160C
FUN_0203160C: ; 0x0203160C
	push {r3-r4}
	lsl r4, r0, #0x1
	ldr r0, _02031624 ; =0x021C59FC
	ldrb r3, [r2, #0x0]
	ldr r1, [r0, #0x0]
	strb r3, [r1, r4]
	ldr r0, [r0, #0x0]
	ldrb r1, [r2, #0x1]
	add r0, r0, r4
	strb r1, [r0, #0x1]
	pop {r3-r4}
	bx lr
	.balign 4
_02031624: .word 0x021C59FC

	thumb_func_start FUN_02031628
FUN_02031628: ; 0x02031628
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_0203162C
FUN_0203162C: ; 0x0203162C
	push {r3, lr}
	add r2, sp, #0x0
	strb r0, [r2, #0x0]
	strb r1, [r2, #0x1]
	mov r0, #0x13
	add r1, sp, #0x0
	bl FUN_020311D0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02031640
FUN_02031640: ; 0x02031640
	ldr r2, _02031664 ; =0x021C59FC
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	bne _0203164E
	mov r0, #0x0
	mvn r0, r0
	bx lr
_0203164E:
	lsl r2, r0, #0x1
	ldrb r0, [r3, r2]
	cmp r1, r0
	bne _0203165C
	add r0, r3, r2
	ldrb r0, [r0, #0x1]
	bx lr
_0203165C:
	mov r0, #0x0
	mvn r0, r0
	bx lr
	nop
_02031664: .word 0x021C59FC

	thumb_func_start FUN_02031668
FUN_02031668: ; 0x02031668
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r6, _02031688 ; =0x021C59FC
	add r5, r4, #0x0
	add r7, r4, #0x0
_02031672:
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	add r0, r0, r5
	mov r2, #0x2
	bl MI_CpuFill8
	add r4, r4, #0x1
	add r5, r5, #0x2
	cmp r4, #0x8
	blt _02031672
	pop {r3-r7, pc}
	.balign 4
_02031688: .word 0x021C59FC

	thumb_func_start FUN_0203168C
FUN_0203168C: ; 0x0203168C
	push {r3-r4}
	mov r4, #0x0
	mov r0, #0x92
	ldr r1, _020316A8 ; =0x021C59FC
	add r3, r4, #0x0
	lsl r0, r0, #0x2
_02031698:
	ldr r2, [r1, #0x0]
	add r2, r2, r4
	add r4, r4, #0x1
	strb r3, [r2, r0]
	cmp r4, #0x8
	blt _02031698
	pop {r3-r4}
	bx lr
	.balign 4
_020316A8: .word 0x021C59FC

	thumb_func_start FUN_020316AC
FUN_020316AC: ; 0x020316AC
	push {r4, lr}
	ldr r2, _020316DC ; =0x021C59FC
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	beq _020316D8
	add r4, r0, #0x0
	mov r2, #0x46
	mul r4, r2
	add r3, #0x18
	add r0, r1, #0x0
	add r1, r3, r4
	bl MI_CpuCopy8
	ldr r1, _020316DC ; =0x021C59FC
	mov r0, #0x14
	ldr r1, [r1, #0x0]
	add r1, #0x18
	add r1, r1, r4
	bl FUN_020311D0
	mov r0, #0x1
	pop {r4, pc}
_020316D8:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_020316DC: .word 0x021C59FC

	thumb_func_start FUN_020316E0
FUN_020316E0: ; 0x020316E0
	ldr r1, _02031700 ; =0x021C59FC
	ldr r3, [r1, #0x0]
	mov r1, #0x92
	add r2, r3, r0
	lsl r1, r1, #0x2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _020316FA
	mov r1, #0x46
	add r3, #0x18
	mul r1, r0
	add r0, r3, r1
	bx lr
_020316FA:
	mov r0, #0x0
	bx lr
	nop
_02031700: .word 0x021C59FC

	thumb_func_start FUN_02031704
FUN_02031704: ; 0x02031704
	push {r3-r5, lr}
	ldr r3, _0203172C ; =0x021C59FC
	add r1, r0, #0x0
	ldr r0, [r3, #0x0]
	mov r5, #0x1
	add r4, r0, r1
	mov r0, #0x92
	lsl r0, r0, #0x2
	strb r5, [r4, r0]
	ldr r4, [r3, #0x0]
	add r0, r2, #0x0
	mov r2, #0x46
	add r3, r1, #0x0
	add r4, #0x18
	mul r3, r2
	add r1, r4, r3
	bl MI_CpuCopy8
	pop {r3-r5, pc}
	nop
_0203172C: .word 0x021C59FC

	thumb_func_start FUN_02031730
FUN_02031730: ; 0x02031730
	mov r0, #0x46
	bx lr

	thumb_func_start FUN_02031734
FUN_02031734: ; 0x02031734
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020317BC ; =0x021C5A00
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020317B8
	bl FUN_0202E49C
	mov r0, #0xf
	mov r1, #0x50
	bl FUN_02016998
	ldr r1, _020317BC ; =0x021C5A00
	mov r2, #0x50
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _020317BC ; =0x021C5A00
	mov r2, #0x32
	ldr r1, [r0, #0x0]
	strh r2, [r1, #0x3a]
	ldr r1, [r0, #0x0]
	mov r2, #0x1
	add r1, #0x43
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	str r5, [r0, #0x28]
	add r0, r5, #0x0
	bl FUN_020238F4
	ldr r1, _020317BC ; =0x021C5A00
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x2c]
	ldr r0, [r1, #0x0]
	mov r2, #0x2
	add r0, #0x3c
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, #0x3d
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, #0x48
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, #0x3f
	strb r4, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, #0xc
	bl FUN_020312BC
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_0202D8D0
	cmp r4, #0x9
	beq _020317B8
	cmp r4, #0x11
	beq _020317B8
	cmp r4, #0xf
	beq _020317B8
	bl FUN_02033E74
_020317B8:
	pop {r3-r5, pc}
	nop
_020317BC: .word 0x021C5A00

	thumb_func_start FUN_020317C0
FUN_020317C0: ; 0x020317C0
	push {r3, lr}
	ldr r0, _0203180C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203180A
	bl FUN_0202D918
	ldr r0, _0203180C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020317DC
	bl FUN_02016A18
_020317DC:
	ldr r0, _0203180C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x13
	blo _020317EE
	mov r0, #0x31
	bl FUN_020168D0
_020317EE:
	bl FUN_02033ED0
	bl FUN_0202E4F0
	ldr r0, _0203180C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	mov r0, #0xf
	bl FUN_020168D0
	ldr r0, _0203180C ; =0x021C5A00
	mov r1, #0x0
	str r1, [r0, #0x0]
_0203180A:
	pop {r3, pc}
	.balign 4
_0203180C: .word 0x021C5A00

	thumb_func_start FUN_02031810
FUN_02031810: ; 0x02031810
	ldr r0, _02031820 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203181C
	mov r0, #0x1
	bx lr
_0203181C:
	mov r0, #0x0
	bx lr
	.balign 4
_02031820: .word 0x021C5A00

	thumb_func_start FUN_02031824
FUN_02031824: ; 0x02031824
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02031858 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031856
	mov r2, #0xe
	mov r0, #0x3
	mov r1, #0xf
	lsl r2, r2, #0xc
	bl FUN_02016828
	add r0, r4, #0x0
	mov r1, #0xa
	bl FUN_02031734
	ldr r0, _02031858 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _0203185C ; =FUN_02031D30
	mov r1, #0x32
	bl FUN_02031D20
_02031856:
	pop {r4, pc}
	.balign 4
_02031858: .word 0x021C5A00
_0203185C: .word FUN_02031D30

	thumb_func_start FUN_02031860
FUN_02031860: ; 0x02031860
	push {r3, lr}
	ldr r0, _02031878 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031876
	bl FUN_02031468
	ldr r0, _0203187C ; =FUN_020323CC
	mov r1, #0x0
	bl FUN_02031D20
_02031876:
	pop {r3, pc}
	.balign 4
_02031878: .word 0x021C5A00
_0203187C: .word FUN_020323CC

	thumb_func_start FUN_02031880
FUN_02031880: ; 0x02031880
	push {r3, lr}
	bl FUN_0202FC60
	bl FUN_02031190
	ldr r1, _0203189C ; =0x021C5A00
	ldr r1, [r1, #0x0]
	strh r0, [r1, #0x38]
	ldr r0, _020318A0 ; =FUN_020321B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_0203189C: .word 0x021C5A00
_020318A0: .word FUN_020321B8

	thumb_func_start FUN_020318A4
FUN_020318A4: ; 0x020318A4
	ldr r1, _020318B0 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	add r1, #0x4f
	strb r0, [r1, #0x0]
	bx lr
	nop
_020318B0: .word 0x021C5A00

	thumb_func_start FUN_020318B4
FUN_020318B4: ; 0x020318B4
	ldr r3, _020318BC ; =FUN_02031D20
	ldr r0, _020318C0 ; =FUN_02032028
	mov r1, #0x0
	bx r3
	.balign 4
_020318BC: .word FUN_02031D20
_020318C0: .word FUN_02032028

	thumb_func_start FUN_020318C4
FUN_020318C4: ; 0x020318C4
	push {r4}
	sub sp, #0xc
	ldr r4, _0203190C ; =0x020EEC50
	add r3, sp, #0x0
	ldmia r4!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	ldr r0, _02031910 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	cmp r0, #0x0
	bne _020318E8
	add sp, #0xc
	mov r0, #0x0
	pop {r4}
	bx lr
_020318E8:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02031904
_020318EE:
	ldr r0, [r2, #0x0]
	cmp r1, r0
	bne _020318FC
	add sp, #0xc
	mov r0, #0x1
	pop {r4}
	bx lr
_020318FC:
	add r2, r2, #0x4
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _020318EE
_02031904:
	mov r0, #0x0
	add sp, #0xc
	pop {r4}
	bx lr
	.balign 4
_0203190C: .word 0x020EEC50
_02031910: .word 0x021C5A00

	thumb_func_start FUN_02031914
FUN_02031914: ; 0x02031914
	ldr r3, _0203191C ; =FUN_02031D20
	ldr r0, _02031920 ; =FUN_02032178
	mov r1, #0x0
	bx r3
	.balign 4
_0203191C: .word FUN_02031D20
_02031920: .word FUN_02032178

	thumb_func_start FUN_02031924
FUN_02031924: ; 0x02031924
	ldr r0, _02031930 ; =0x021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x4c
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_02031930: .word 0x021C5A00

	thumb_func_start FUN_02031934
FUN_02031934: ; 0x02031934
	push {r3, lr}
	bl FUN_0202E49C
	ldr r0, _02031944 ; =FUN_02032194
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031944: .word FUN_02032194

	thumb_func_start FUN_02031948
FUN_02031948: ; 0x02031948
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02031980
	ldr r2, _02031984 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02031734
	ldr r0, _02031988 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	add r1, #0x40
	strb r5, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r4, [r0, #0x30]
	ldr r0, _0203198C ; =FUN_020321D0
	bl FUN_02031D20
_02031980:
	pop {r3-r7, pc}
	nop
_02031984: .word 0x00007080
_02031988: .word 0x021C5A00
_0203198C: .word FUN_020321D0

	thumb_func_start FUN_02031990
FUN_02031990: ; 0x02031990
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _020319C8
	ldr r2, _020319CC ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02031734
	ldr r0, _020319D0 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	add r1, #0x40
	strb r5, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r4, [r0, #0x30]
	ldr r0, _020319D4 ; =FUN_0203224C
	bl FUN_02031D20
_020319C8:
	pop {r3-r7, pc}
	nop
_020319CC: .word 0x00007080
_020319D0: .word 0x021C5A00
_020319D4: .word FUN_0203224C

	thumb_func_start FUN_020319D8
FUN_020319D8: ; 0x020319D8
	ldr r1, _020319E8 ; =0x021C5A00
	ldr r3, _020319EC ; =FUN_02031D20
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _020319F0 ; =FUN_02032298
	mov r1, #0x0
	bx r3
	.balign 4
_020319E8: .word 0x021C5A00
_020319EC: .word FUN_02031D20
_020319F0: .word FUN_02032298

	thumb_func_start FUN_020319F4
FUN_020319F4: ; 0x020319F4
	push {r3, lr}
	bl FUN_0202FCA8
	ldr r0, _02031A04 ; =FUN_02032364
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031A04: .word FUN_02032364

	thumb_func_start FUN_02031A08
FUN_02031A08: ; 0x02031A08
	push {r3, lr}
	ldr r0, _02031A1C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031A1A
	ldr r0, _02031A20 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02031A1A:
	pop {r3, pc}
	.balign 4
_02031A1C: .word 0x021C5A00
_02031A20: .word FUN_02032440

	thumb_func_start FUN_02031A24
FUN_02031A24: ; 0x02031A24
	ldr r3, _02031A28 ; =FUN_0202D298
	bx r3
	.balign 4
_02031A28: .word FUN_0202D298

	thumb_func_start FUN_02031A2C
FUN_02031A2C: ; 0x02031A2C
	push {r4}
	sub sp, #0xc
	ldr r4, _02031A74 ; =0x020EEC5C
	add r3, sp, #0x0
	ldmia r4!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	ldr r0, _02031A78 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	cmp r0, #0x0
	bne _02031A50
	add sp, #0xc
	mov r0, #0x0
	pop {r4}
	bx lr
_02031A50:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02031A6C
_02031A56:
	ldr r0, [r2, #0x0]
	cmp r1, r0
	bne _02031A64
	add sp, #0xc
	mov r0, #0x1
	pop {r4}
	bx lr
_02031A64:
	add r2, r2, #0x4
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _02031A56
_02031A6C:
	mov r0, #0x0
	add sp, #0xc
	pop {r4}
	bx lr
	.balign 4
_02031A74: .word 0x020EEC5C
_02031A78: .word 0x021C5A00

	thumb_func_start FUN_02031A7C
FUN_02031A7C: ; 0x02031A7C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02031ABC ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031ABA
	ldr r2, _02031AC0 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	cmp r0, #0x0
	bne _02031A9A
	bl FUN_020335E0
_02031A9A:
	add r0, r4, #0x0
	mov r1, #0x9
	bl FUN_02031734
	ldr r0, _02031ABC ; =0x021C5A00
	mov r2, #0x9
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _02031AC4 ; =FUN_02032478
	bl FUN_02031D20
_02031ABA:
	pop {r4, pc}
	.balign 4
_02031ABC: .word 0x021C5A00
_02031AC0: .word 0x00007080
_02031AC4: .word FUN_02032478

	thumb_func_start FUN_02031AC8
FUN_02031AC8: ; 0x02031AC8
	push {r3, lr}
	ldr r1, _02031AEC ; =0x021C5A00
	ldr r2, [r1, #0x0]
	add r2, #0x3e
	strb r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x3
	strh r2, [r0, #0x38]
	mov r0, #0x1
	bl FUN_0202D344
	bl FUN_02033E74
	ldr r0, _02031AF0 ; =FUN_02032628
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031AEC: .word 0x021C5A00
_02031AF0: .word FUN_02032628

	thumb_func_start FUN_02031AF4
FUN_02031AF4: ; 0x02031AF4
	ldr r0, _02031B20 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031B02
	mov r0, #0x0
	mvn r0, r0
	bx lr
_02031B02:
	ldr r1, [r0, #0x24]
	ldr r0, _02031B24 ; =FUN_0203279C
	cmp r1, r0
	bne _02031B0E
	mov r0, #0x1
	bx lr
_02031B0E:
	ldr r0, _02031B28 ; =FUN_020327B4
	cmp r1, r0
	bne _02031B18
	mov r0, #0x1
	b _02031B1A
_02031B18:
	mov r0, #0x0
_02031B1A:
	neg r0, r0
	bx lr
	nop
_02031B20: .word 0x021C5A00
_02031B24: .word FUN_0203279C
_02031B28: .word FUN_020327B4

	thumb_func_start FUN_02031B2C
FUN_02031B2C: ; 0x02031B2C
	ldr r0, _02031B48 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031B38
	mov r0, #0x0
	bx lr
_02031B38:
	ldr r1, [r0, #0x24]
	ldr r0, _02031B4C ; =FUN_020327FC
	cmp r1, r0
	bne _02031B44
	mov r0, #0x1
	bx lr
_02031B44:
	mov r0, #0x0
	bx lr
	.balign 4
_02031B48: .word 0x021C5A00
_02031B4C: .word FUN_020327FC

	thumb_func_start FUN_02031B50
FUN_02031B50: ; 0x02031B50
	push {r3, lr}
	mov r0, #0x0
	bl FUN_0202D344
	ldr r0, _02031BC4 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02031B78
	add r0, r1, #0x0
	add r0, #0x45
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02031B78
	add r1, #0x3f
	ldrb r0, [r1, #0x0]
	cmp r0, #0x9
	bne _02031B80
_02031B78:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
_02031B80:
	bl FUN_02033ED0
	ldr r0, _02031BC4 ; =0x021C5A00
	mov r2, #0x9
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r1, #0x48
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	bl FUN_0202D1B0
	bl FUN_02031190
	cmp r0, #0x0
	bne _02031BB8
	mov r0, #0x1
	bl FUN_0202D36C
	ldr r0, _02031BC8 ; =FUN_020323DC
	mov r1, #0xf
	bl FUN_02031D20
	pop {r3, pc}
_02031BB8:
	ldr r0, _02031BCC ; =FUN_02032424
	mov r1, #0x5
	bl FUN_02031D20
	pop {r3, pc}
	nop
_02031BC4: .word 0x021C5A00
_02031BC8: .word FUN_020323DC
_02031BCC: .word FUN_02032424

	thumb_func_start FUN_02031BD0
FUN_02031BD0: ; 0x02031BD0
	ldr r0, _02031BEC ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031BDC
	mov r0, #0x1
	bx lr
_02031BDC:
	ldr r1, [r0, #0x24]
	ldr r0, _02031BF0 ; =FUN_020324F8
	cmp r1, r0
	beq _02031BE8
	mov r0, #0x1
	bx lr
_02031BE8:
	mov r0, #0x0
	bx lr
	.balign 4
_02031BEC: .word 0x021C5A00
_02031BF0: .word FUN_020324F8

	thumb_func_start FUN_02031BF4
FUN_02031BF4: ; 0x02031BF4
	push {r3, lr}
	ldr r0, _02031C08 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031C06
	ldr r0, _02031C0C ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02031C06:
	pop {r3, pc}
	.balign 4
_02031C08: .word 0x021C5A00
_02031C0C: .word FUN_02032440

	thumb_func_start FUN_02031C10
FUN_02031C10: ; 0x02031C10
	push {r3, lr}
	ldr r0, _02031C28 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02031C24
	mov r0, #0x1
	add r1, #0x48
	strb r0, [r1, #0x0]
	bl FUN_0202D344
_02031C24:
	pop {r3, pc}
	nop
_02031C28: .word 0x021C5A00

	thumb_func_start FUN_02031C2C
FUN_02031C2C: ; 0x02031C2C
	push {r3, lr}
	ldr r0, _02031C4C ; =0x021C5A00
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02031C48
	mov r0, #0x1
	add r1, #0x48
	strb r0, [r1, #0x0]
	bl FUN_0202D344
	ldr r0, _02031C50 ; =FUN_02032850
	mov r1, #0x0
	bl FUN_02031D20
_02031C48:
	pop {r3, pc}
	nop
_02031C4C: .word 0x021C5A00
_02031C50: .word FUN_02032850

	thumb_func_start FUN_02031C54
FUN_02031C54: ; 0x02031C54
	ldr r0, _02031C60 ; =0x021C5A00
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_02031C60: .word 0x021C5A00

	thumb_func_start FUN_02031C64
FUN_02031C64: ; 0x02031C64
	ldr r0, _02031C70 ; =0x021C5A00
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_02031C70: .word 0x021C5A00

	thumb_func_start FUN_02031C74
FUN_02031C74: ; 0x02031C74
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02031C9C
	ldr r2, _02031CA0 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02031734
	ldr r0, _02031CA4 ; =FUN_02032E00
	mov r1, #0x0
	bl FUN_02031D20
_02031C9C:
	pop {r3-r5, pc}
	nop
_02031CA0: .word 0x00007080
_02031CA4: .word FUN_02032E00

	thumb_func_start FUN_02031CA8
FUN_02031CA8: ; 0x02031CA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02031CD0
	ldr r2, _02031CD4 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02031734
	ldr r0, _02031CD8 ; =FUN_02032E48
	mov r1, #0x0
	bl FUN_02031D20
_02031CD0:
	pop {r3-r5, pc}
	nop
_02031CD4: .word 0x00007080
_02031CD8: .word FUN_02032E48

	thumb_func_start FUN_02031CDC
FUN_02031CDC: ; 0x02031CDC
	push {r3, lr}
	ldr r0, _02031D1C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031CEE
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _02031CEE
	blx r0
_02031CEE:
	bl FUN_02033590
	cmp r0, #0x0
	beq _02031D04
	bl MOD04_021DDB08
	mov r1, #0x3
	sub r0, r1, r0
	bl FUN_02033EEC
	pop {r3, pc}
_02031D04:
	bl FUN_0202EDF8
	cmp r0, #0x0
	beq _02031D18
	bl WM_GetLinkLevel
	mov r1, #0x3
	sub r0, r1, r0
	bl FUN_02033EEC
_02031D18:
	pop {r3, pc}
	nop
_02031D1C: .word 0x021C5A00

	thumb_func_start FUN_02031D20
FUN_02031D20: ; 0x02031D20
	ldr r2, _02031D2C ; =0x021C5A00
	ldr r3, [r2, #0x0]
	str r0, [r3, #0x24]
	ldr r0, [r2, #0x0]
	strh r1, [r0, #0x3a]
	bx lr
	.balign 4
_02031D2C: .word 0x021C5A00

	thumb_func_start FUN_02031D30
FUN_02031D30: ; 0x02031D30
	push {r3-r5, lr}
	ldr r0, _02031DF8 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02031D42
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3-r5, pc}
_02031D42:
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02031DF6
	ldr r0, _02031DF8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02031DF8 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	bl FUN_02031268
	bl FUN_02030FA8
	ldr r0, _02031DF8 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031DC8
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	mov r0, #0x1
	mov r2, #0x7d
	lsl r2, r2, #0x2
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _02031DF6
	ldr r0, _02031DF8 ; =0x021C5A00
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
	add r4, #0xc
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #0xc]
	ldr r3, [r4, #0x4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #0xc]
	str r3, [r4, #0x4]
	add r0, r3, #0x0
	mov r1, #0x0
	mov r2, #0x14
	mov r3, #0x0
	bl _ll_mul
	mov r0, #0x0
	add r5, #0x43
	strb r0, [r5, #0x0]
	ldr r0, _02031DFC ; =FUN_020320C4
	add r1, #0x14
	bl FUN_02031D20
	pop {r3-r5, pc}
_02031DC8:
	mov r0, #0x1
	mov r2, #0x7d
	add r1, r0, #0x0
	lsl r2, r2, #0x2
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02031DF6
	ldr r0, _02031DF8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031DEE
	ldr r0, _02031E00 ; =FUN_020323B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3-r5, pc}
_02031DEE:
	ldr r0, _02031E04 ; =FUN_02031EE0
	mov r1, #0x40
	bl FUN_02031D20
_02031DF6:
	pop {r3-r5, pc}
	.balign 4
_02031DF8: .word 0x021C5A00
_02031DFC: .word FUN_020320C4
_02031E00: .word FUN_020323B8
_02031E04: .word FUN_02031EE0

	thumb_func_start FUN_02031E08
FUN_02031E08: ; 0x02031E08
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02031E7C
	mov r0, #0x1
	bl FUN_02031268
	bl FUN_02030FA8
	ldr r0, _02031E80 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031E32
	ldr r0, _02031E84 ; =FUN_02032058
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3-r5, pc}
_02031E32:
	mov r2, #0x7d
	mov r0, #0x0
	mov r1, #0x1
	lsl r2, r2, #0x2
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02031E7C
	ldr r0, _02031E80 ; =0x021C5A00
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
	add r4, #0xc
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #0xc]
	ldr r3, [r4, #0x4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #0xc]
	mov r1, #0x0
	str r3, [r4, #0x4]
	lsr r0, r3, #0x1a
	lsl r1, r1, #0x6
	orr r1, r0
	ldrh r0, [r5, #0x38]
	cmp r0, #0x0
	beq _02031E76
	lsl r1, r0, #0x6
	mov r0, #0x0
	strh r0, [r5, #0x38]
_02031E76:
	ldr r0, _02031E88 ; =FUN_02031EE0
	bl FUN_02031D20
_02031E7C:
	pop {r3-r5, pc}
	nop
_02031E80: .word 0x021C5A00
_02031E84: .word FUN_02032058
_02031E88: .word FUN_02031EE0

	thumb_func_start FUN_02031E8C
FUN_02031E8C: ; 0x02031E8C
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02031ED6
	mov r0, #0x0
	mov r2, #0x7d
	add r1, r0, #0x0
	lsl r2, r2, #0x2
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02031ED6
	ldr r0, _02031ED8 ; =0x021C5A00
	ldr r4, [r0, #0x0]
	add r5, r4, #0x0
	add r5, #0xc
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #0xc]
	ldr r3, [r5, #0x4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	mov r1, #0x0
	lsr r2, r3, #0x1b
	lsl r1, r1, #0x5
	orr r1, r2
	ldr r0, _02031EDC ; =FUN_02031EE0
	add r1, #0x10
	str r3, [r5, #0x4]
	bl FUN_02031D20
_02031ED6:
	pop {r3-r5, pc}
	.balign 4
_02031ED8: .word 0x021C5A00
_02031EDC: .word FUN_02031EE0

	thumb_func_start FUN_02031EE0
FUN_02031EE0: ; 0x02031EE0
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _02031F54 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x4f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031F50
	add r1, #0x4b
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	bne _02031F50
	bl FUN_0202E8F4
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02031F1A
	ldr r1, _02031F54 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _02031F58 ; =FUN_02031F60
	mov r1, #0x20
	bl FUN_02031D20
	pop {r3, pc}
_02031F1A:
	ldr r0, _02031F54 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02031F2A
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02031F2A:
	bl FUN_0202E950
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02031F48
	ldr r1, _02031F54 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _02031F58 ; =FUN_02031F60
	mov r1, #0x20
	bl FUN_02031D20
	pop {r3, pc}
_02031F48:
	ldr r0, _02031F5C ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
_02031F50:
	pop {r3, pc}
	nop
_02031F54: .word 0x021C5A00
_02031F58: .word FUN_02031F60
_02031F5C: .word FUN_02032028

	thumb_func_start FUN_02031F60
FUN_02031F60: ; 0x02031F60
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _02031FBC ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202E8A0
	cmp r0, #0x0
	beq _02031F90
	ldr r0, _02031FBC ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _02031F90
	ldr r0, _02031FC0 ; =FUN_02031FC8
	mov r1, #0x64
	bl FUN_02031D20
	pop {r3, pc}
_02031F90:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02031FA2
	ldr r0, _02031FC4 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02031FA2:
	ldr r0, _02031FBC ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02031FB2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02031FB2:
	ldr r0, _02031FC4 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031FBC: .word 0x021C5A00
_02031FC0: .word FUN_02031FC8
_02031FC4: .word FUN_02032028

	thumb_func_start FUN_02031FC8
FUN_02031FC8: ; 0x02031FC8
	push {r3, lr}
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02031FEE
	bl FUN_0202FC60
	mov r0, #0x0
	bl FUN_02031268
	bl FUN_02030FA8
	ldr r0, _0203201C ; =FUN_0203213C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02031FEE:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02032000
	ldr r0, _02032020 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032000:
	ldr r0, _02032024 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032010
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032010:
	ldr r0, _02032020 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_0203201C: .word FUN_0203213C
_02032020: .word FUN_02032028
_02032024: .word 0x021C5A00

	thumb_func_start FUN_02032028
FUN_02032028: ; 0x02032028
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203203A
	ldr r0, _0203203C ; =FUN_02032058
	mov r1, #0x0
	bl FUN_02031D20
_0203203A:
	pop {r3, pc}
	.balign 4
_0203203C: .word FUN_02032058

	thumb_func_start FUN_02032040
FUN_02032040: ; 0x02032040
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _02032052
	ldr r0, _02032054 ; =FUN_02031E8C
	mov r1, #0x0
	bl FUN_02031D20
_02032052:
	pop {r3, pc}
	.balign 4
_02032054: .word FUN_02031E8C

	thumb_func_start FUN_02032058
FUN_02032058: ; 0x02032058
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _020320BA
	mov r0, #0x1
	bl FUN_02031268
	ldr r1, _020320BC ; =0x021C5A00
	mov r2, #0x7d
	ldr r1, [r1, #0x0]
	mov r0, #0x0
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	lsl r2, r2, #0x2
	mov r3, #0x1
	bl FUN_0202F918
	cmp r0, #0x0
	beq _020320BA
	ldr r0, _020320BC ; =0x021C5A00
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
	add r4, #0xc
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #0xc]
	ldr r3, [r4, #0x4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #0xc]
	str r3, [r4, #0x4]
	add r0, r3, #0x0
	mov r1, #0x0
	mov r2, #0x14
	mov r3, #0x0
	bl _ll_mul
	mov r0, #0x0
	add r5, #0x43
	strb r0, [r5, #0x0]
	ldr r0, _020320C0 ; =FUN_020320C4
	add r1, #0x14
	bl FUN_02031D20
_020320BA:
	pop {r3-r5, pc}
	.balign 4
_020320BC: .word 0x021C5A00
_020320C0: .word FUN_020320C4

	thumb_func_start FUN_020320C4
FUN_020320C4: ; 0x020320C4
	push {r3, lr}
	bl FUN_020311E8
	cmp r0, #0x0
	beq _020320E2
	ldr r0, _0203210C ; =0x021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	ldr r0, _02032110 ; =FUN_02032118
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020320E2:
	ldr r0, _0203210C ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020320F2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020320F2:
	add r1, #0x4a
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0203210A
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203210A
	ldr r0, _02032114 ; =FUN_02032040
	mov r1, #0x2
	bl FUN_02031D20
_0203210A:
	pop {r3, pc}
	.balign 4
_0203210C: .word 0x021C5A00
_02032110: .word FUN_02032118
_02032114: .word FUN_02032040

	thumb_func_start FUN_02032118
FUN_02032118: ; 0x02032118
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02031268
	mov r0, #0x1
	bl FUN_0202EE84
	bl FUN_02030FA8
	ldr r0, _02032134 ; =FUN_02032138
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032134: .word FUN_02032138

	thumb_func_start FUN_02032138
FUN_02032138: ; 0x02032138
	bx lr
	.balign 4

	thumb_func_start FUN_0203213C
FUN_0203213C: ; 0x0203213C
	bx lr
	.balign 4

	thumb_func_start FUN_02032140
FUN_02032140: ; 0x02032140
	push {r3, lr}
	ldr r0, _02032170 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x13
	bhs _02032166
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203216E
	mov r0, #0x1
	bl FUN_02031268
	bl FUN_02030FA8
	mov r0, #0x1
	bl FUN_0202E7B0
_02032166:
	ldr r0, _02032174 ; =FUN_020323B8
	mov r1, #0x0
	bl FUN_02031D20
_0203216E:
	pop {r3, pc}
	.balign 4
_02032170: .word 0x021C5A00
_02032174: .word FUN_020323B8

	thumb_func_start FUN_02032178
FUN_02032178: ; 0x02032178
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203218E
	bl FUN_0202FC60
	ldr r0, _02032190 ; =FUN_02032140
	mov r1, #0x0
	bl FUN_02031D20
_0203218E:
	pop {r3, pc}
	.balign 4
_02032190: .word FUN_02032140

	thumb_func_start FUN_02032194
FUN_02032194: ; 0x02032194
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _020321B0
	mov r0, #0x0
	bl FUN_0202E7B0
	bl FUN_0202FC60
	ldr r0, _020321B4 ; =FUN_02031E08
	mov r1, #0x0
	bl FUN_02031D20
_020321B0:
	pop {r3, pc}
	nop
_020321B4: .word FUN_02031E08

	thumb_func_start FUN_020321B8
FUN_020321B8: ; 0x020321B8
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020321CA
	ldr r0, _020321CC ; =FUN_02031E08
	mov r1, #0x0
	bl FUN_02031D20
_020321CA:
	pop {r3, pc}
	.balign 4
_020321CC: .word FUN_02031E08

	thumb_func_start FUN_020321D0
FUN_020321D0: ; 0x020321D0
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _0203220C
	ldr r0, _02032210 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032210 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _0203220C
	bl FUN_0202FA10
	ldr r0, _02032214 ; =FUN_02032218
	mov r1, #0x0
	bl FUN_02031D20
_0203220C:
	pop {r3, pc}
	nop
_02032210: .word 0x021C5A00
_02032214: .word FUN_02032218

	thumb_func_start FUN_02032218
FUN_02032218: ; 0x02032218
	push {r3, lr}
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0203222E
	ldr r0, _02032230 ; =FUN_02032234
	mov r1, #0x0
	bl FUN_02031D20
_0203222E:
	pop {r3, pc}
	.balign 4
_02032230: .word FUN_02032234

	thumb_func_start FUN_02032234
FUN_02032234: ; 0x02032234
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02032246
	ldr r0, _02032248 ; =FUN_020323BC
	mov r1, #0x0
	bl FUN_02031D20
_02032246:
	pop {r3, pc}
	.balign 4
_02032248: .word FUN_020323BC

	thumb_func_start FUN_0203224C
FUN_0203224C: ; 0x0203224C
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032286
	ldr r0, _02032288 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032288 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032286
	bl FUN_0202FA10
	ldr r0, _0203228C ; =FUN_02032290
	mov r1, #0x0
	bl FUN_02031D20
_02032286:
	pop {r3, pc}
	.balign 4
_02032288: .word 0x021C5A00
_0203228C: .word FUN_02032290

	thumb_func_start FUN_02032290
FUN_02032290: ; 0x02032290
	ldr r3, _02032294 ; =FUN_0202EA54
	bx r3
	.balign 4
_02032294: .word FUN_0202EA54

	thumb_func_start FUN_02032298
FUN_02032298: ; 0x02032298
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _020322B8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _020322B6
	ldr r0, _020322BC ; =FUN_020322C0
	mov r1, #0xa
	bl FUN_02031D20
_020322B6:
	pop {r3, pc}
	.balign 4
_020322B8: .word 0x021C5A00
_020322BC: .word FUN_020322C0

	thumb_func_start FUN_020322C0
FUN_020322C0: ; 0x020322C0
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020322D2
	ldr r0, _020322F0 ; =FUN_020322F8
	mov r1, #0x0
	bl FUN_02031D20
_020322D2:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _020322EE
	bl FUN_02031190
	cmp r0, #0x0
	beq _020322EE
	ldr r0, _020322F4 ; =FUN_0203234C
	mov r1, #0x0
	bl FUN_02031D20
_020322EE:
	pop {r3, pc}
	.balign 4
_020322F0: .word FUN_020322F8
_020322F4: .word FUN_0203234C

	thumb_func_start FUN_020322F8
FUN_020322F8: ; 0x020322F8
	push {r3, lr}
	bl FUN_0202E6F0
	ldr r0, _02032308 ; =FUN_0203230C
	mov r1, #0x2
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032308: .word FUN_0203230C

	thumb_func_start FUN_0203230C
FUN_0203230C: ; 0x0203230C
	push {r3, lr}
	ldr r0, _02032344 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _0203231E
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_0203231E:
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02032340
	mov r1, #0x1
	mov r0, #0x0
	lsl r2, r1, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032340
	bl FUN_0202FA10
	ldr r0, _02032348 ; =FUN_02032298
	mov r1, #0xa
	bl FUN_02031D20
_02032340:
	pop {r3, pc}
	nop
_02032344: .word 0x021C5A00
_02032348: .word FUN_02032298

	thumb_func_start FUN_0203234C
FUN_0203234C: ; 0x0203234C
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0203235E
	ldr r0, _02032360 ; =FUN_020323BC
	mov r1, #0x0
	bl FUN_02031D20
_0203235E:
	pop {r3, pc}
	.balign 4
_02032360: .word FUN_020323BC

	thumb_func_start FUN_02032364
FUN_02032364: ; 0x02032364
	push {r3, lr}
	bl FUN_0202E6F0
	ldr r0, _02032374 ; =FUN_02032378
	mov r1, #0x2
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032374: .word FUN_02032378

	thumb_func_start FUN_02032378
FUN_02032378: ; 0x02032378
	push {r3, lr}
	ldr r0, _020323B0 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _0203238A
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_0203238A:
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _020323AC
	mov r1, #0x1
	mov r0, #0x0
	lsl r2, r1, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _020323AC
	bl FUN_0202FA10
	ldr r0, _020323B4 ; =FUN_02032290
	mov r1, #0xa
	bl FUN_02031D20
_020323AC:
	pop {r3, pc}
	nop
_020323B0: .word 0x021C5A00
_020323B4: .word FUN_02032290

	thumb_func_start FUN_020323B8
FUN_020323B8: ; 0x020323B8
	bx lr
	.balign 4

	thumb_func_start FUN_020323BC
FUN_020323BC: ; 0x020323BC
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _020323CA
	bl FUN_020317C0
_020323CA:
	pop {r3, pc}

	thumb_func_start FUN_020323CC
FUN_020323CC: ; 0x020323CC
	ldr r3, _020323D4 ; =FUN_02031D20
	ldr r0, _020323D8 ; =FUN_02032440
	mov r1, #0x5
	bx r3
	.balign 4
_020323D4: .word FUN_02031D20
_020323D8: .word FUN_02032440

	thumb_func_start FUN_020323DC
FUN_020323DC: ; 0x020323DC
	push {r3, lr}
	bl FUN_02030F20
	cmp r0, #0x1
	bgt _020323F8
	mov r0, #0x0
	bl FUN_0202D36C
	bl FUN_0202FC80
	ldr r0, _0203241C ; =FUN_020324F8
	mov r1, #0x0
	bl FUN_02031D20
_020323F8:
	ldr r0, _02032420 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032408
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032408:
	mov r0, #0x0
	bl FUN_0202D36C
	bl FUN_0202FC80
	ldr r0, _0203241C ; =FUN_020324F8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_0203241C: .word FUN_020324F8
_02032420: .word 0x021C5A00

	thumb_func_start FUN_02032424
FUN_02032424: ; 0x02032424
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203243A
	bl FUN_0202FC60
	ldr r0, _0203243C ; =FUN_020324F8
	mov r1, #0x0
	bl FUN_02031D20
_0203243A:
	pop {r3, pc}
	.balign 4
_0203243C: .word FUN_020324F8

	thumb_func_start FUN_02032440
FUN_02032440: ; 0x02032440
	push {r3, lr}
	ldr r0, _02032470 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032450
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
_02032450:
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203246E
	ldr r0, _02032470 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3a]
	cmp r0, #0x0
	bne _0203246E
	bl FUN_0202FA5C
	ldr r0, _02032474 ; =FUN_020323BC
	mov r1, #0x0
	bl FUN_02031D20
_0203246E:
	pop {r3, pc}
	.balign 4
_02032470: .word 0x021C5A00
_02032474: .word FUN_020323BC

	thumb_func_start FUN_02032478
FUN_02032478: ; 0x02032478
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _020324BE
	ldr r0, _020324C0 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _020324C0 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	bl FUN_0202D1B0
	ldr r0, _020324C0 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _020324BE
	bl FUN_0202FA10
	ldr r0, _020324C4 ; =FUN_020324C8
	mov r1, #0x40
	bl FUN_02031D20
_020324BE:
	pop {r3, pc}
	.balign 4
_020324C0: .word 0x021C5A00
_020324C4: .word FUN_020324C8

	thumb_func_start FUN_020324C8
FUN_020324C8: ; 0x020324C8
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _020324F0 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020324DE
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020324DE:
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020324EE
	ldr r0, _020324F4 ; =FUN_02032510
	mov r1, #0x0
	bl FUN_02031D20
_020324EE:
	pop {r3, pc}
	.balign 4
_020324F0: .word 0x021C5A00
_020324F4: .word FUN_02032510

	thumb_func_start FUN_020324F8
FUN_020324F8: ; 0x020324F8
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203250A
	ldr r0, _0203250C ; =FUN_02032510
	mov r1, #0x0
	bl FUN_02031D20
_0203250A:
	pop {r3, pc}
	.balign 4
_0203250C: .word FUN_02032510

	thumb_func_start FUN_02032510
FUN_02032510: ; 0x02032510
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02032568
	ldr r1, _0203256C ; =0x021C5A00
	mov r2, #0x2
	ldr r1, [r1, #0x0]
	mov r0, #0x0
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	lsl r2, r2, #0x8
	mov r3, #0x1
	bl FUN_0202F918
	cmp r0, #0x0
	beq _02032568
	ldr r0, _0203256C ; =0x021C5A00
	ldr r4, [r0, #0x0]
	add r5, r4, #0x0
	add r5, #0xc
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #0xc]
	ldr r3, [r5, #0x4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	str r3, [r5, #0x4]
	bl FUN_0202FA10
	ldr r0, _0203256C ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	ldr r0, _02032570 ; =FUN_02032578
	ldr r1, _02032574 ; =0x00002710
	bl FUN_02031D20
_02032568:
	pop {r3-r5, pc}
	nop
_0203256C: .word 0x021C5A00
_02032570: .word FUN_02032578
_02032574: .word 0x00002710

	thumb_func_start FUN_02032578
FUN_02032578: ; 0x02032578
	push {r3, lr}
	bl FUN_0202F104
	cmp r0, #0x0
	bne _020325B2
	bl FUN_020311E8
	cmp r0, #0x0
	beq _020325A2
	ldr r0, _020325C4 ; =0x021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	bl FUN_02033E74
	ldr r0, _020325C8 ; =FUN_020327FC
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020325A2:
	ldr r0, _020325C4 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020325B2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020325B2:
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020325C2
	ldr r0, _020325CC ; =FUN_020325D0
	mov r1, #0x0
	bl FUN_02031D20
_020325C2:
	pop {r3, pc}
	.balign 4
_020325C4: .word 0x021C5A00
_020325C8: .word FUN_020327FC
_020325CC: .word FUN_020325D0

	thumb_func_start FUN_020325D0
FUN_020325D0: ; 0x020325D0
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203261C
	mov r0, #0x0
	mov r2, #0x2
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	bl FUN_0202F950
	cmp r0, #0x0
	beq _0203261C
	bl FUN_0202FA10
	ldr r0, _02032620 ; =0x021C5A00
	ldr r4, [r0, #0x0]
	add r5, r4, #0x0
	add r5, #0xc
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #0xc]
	ldr r3, [r5, #0x4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	mov r1, #0x0
	ldr r0, _02032624 ; =FUN_020324C8
	lsr r2, r3, #0x1b
	lsl r1, r1, #0x5
	orr r1, r2
	str r3, [r5, #0x4]
	bl FUN_02031D20
_0203261C:
	pop {r3-r5, pc}
	nop
_02032620: .word 0x021C5A00
_02032624: .word FUN_020324C8

	thumb_func_start FUN_02032628
FUN_02032628: ; 0x02032628
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203263A
	ldr r0, _0203263C ; =FUN_02032640
	mov r1, #0x0
	bl FUN_02031D20
_0203263A:
	pop {r3, pc}
	.balign 4
_0203263C: .word FUN_02032640

	thumb_func_start FUN_02032640
FUN_02032640: ; 0x02032640
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02032666
	mov r0, #0x0
	mov r2, #0x2
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032666
	bl FUN_0202FA10
	ldr r0, _02032668 ; =FUN_0203266C
	mov r1, #0x64
	bl FUN_02031D20
_02032666:
	pop {r3, pc}
	.balign 4
_02032668: .word FUN_0203266C

	thumb_func_start FUN_0203266C
FUN_0203266C: ; 0x0203266C
	push {r3, lr}
	ldr r0, _020326C4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202E8A0
	cmp r0, #0x0
	beq _02032698
	ldr r0, _020326C4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _02032698
	ldr r0, _020326C8 ; =FUN_020326D0
	mov r1, #0x64
	bl FUN_02031D20
	pop {r3, pc}
_02032698:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020326AA
	ldr r0, _020326CC ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020326AA:
	ldr r0, _020326C4 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020326BA
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020326BA:
	ldr r0, _020326CC ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_020326C4: .word 0x021C5A00
_020326C8: .word FUN_020326D0
_020326CC: .word FUN_020327B8

	thumb_func_start FUN_020326D0
FUN_020326D0: ; 0x020326D0
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020326E4
	ldr r0, _02032728 ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020326E4:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0203270C
	ldr r0, _0203272C ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
	ldr r1, _02032730 ; =0x02105D5C
	mov r0, #0x6
	bl FUN_020311D0
	ldr r0, _02032734 ; =FUN_02032738
	mov r1, #0x78
	bl FUN_02031D20
	pop {r3, pc}
_0203270C:
	ldr r0, _0203272C ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _0203271C
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_0203271C:
	ldr r0, _02032728 ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_02032728: .word FUN_020327B8
_0203272C: .word 0x021C5A00
_02032730: .word 0x02105D5C
_02032734: .word FUN_02032738

	thumb_func_start FUN_02032738
FUN_02032738: ; 0x02032738
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _0203274C
	ldr r0, _0203278C ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_0203274C:
	ldr r0, _02032790 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x3d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _02032764
	ldr r0, _02032794 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032764:
	cmp r0, #0x1
	bne _02032776
	bl FUN_0202DBE0
	ldr r0, _02032798 ; =FUN_0203279C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032776:
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032782
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032782:
	ldr r0, _0203278C ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_0203278C: .word FUN_020327B8
_02032790: .word 0x021C5A00
_02032794: .word FUN_020327B4
_02032798: .word FUN_0203279C

	thumb_func_start FUN_0203279C
FUN_0203279C: ; 0x0203279C
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020327AE
	ldr r0, _020327B0 ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
_020327AE:
	pop {r3, pc}
	.balign 4
_020327B0: .word FUN_020327B8

	thumb_func_start FUN_020327B4
FUN_020327B4: ; 0x020327B4
	bx lr
	.balign 4

	thumb_func_start FUN_020327B8
FUN_020327B8: ; 0x020327B8
	push {r3, lr}
	ldr r0, _020327F0 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020327EC
	ldr r0, _020327F0 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x38]
	cmp r0, #0x0
	beq _020327E4
	sub r0, r0, #0x1
	strh r0, [r1, #0x38]
	ldr r0, _020327F4 ; =FUN_02032640
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020327E4:
	ldr r0, _020327F8 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
_020327EC:
	pop {r3, pc}
	nop
_020327F0: .word 0x021C5A00
_020327F4: .word FUN_02032640
_020327F8: .word FUN_020327B4

	thumb_func_start FUN_020327FC
FUN_020327FC: ; 0x020327FC
	push {r3, lr}
	bl FUN_020311E8
	cmp r0, #0x0
	bne _02032820
	bl FUN_02033510
	cmp r0, #0x0
	bne _0203282C
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203282C
	ldr r0, _02032848 ; =FUN_020325D0
	mov r1, #0x0
	bl FUN_02031D20
	b _0203282C
_02032820:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203282C
	bl FUN_0202DDE8
_0203282C:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02032844
	bl FUN_02033510
	cmp r0, #0x0
	bne _02032844
	ldr r0, _0203284C ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
_02032844:
	pop {r3, pc}
	nop
_02032848: .word FUN_020325D0
_0203284C: .word FUN_020327B8

	thumb_func_start FUN_02032850
FUN_02032850: ; 0x02032850
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203287E
	ldr r1, _02032880 ; =0x021C5A00
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	mov r2, #0x2
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	lsl r2, r2, #0x8
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _0203287E
	bl FUN_0202FA10
	ldr r0, _02032884 ; =FUN_020323B8
	mov r1, #0x0
	bl FUN_02031D20
_0203287E:
	pop {r3, pc}
	.balign 4
_02032880: .word 0x021C5A00
_02032884: .word FUN_020323B8

	thumb_func_start FUN_02032888
FUN_02032888: ; 0x02032888
	push {r3, lr}
	ldr r0, _020328BC ; =0x021C5A00
	mov r1, #0xd
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bl FUN_02031190
	cmp r0, #0x0
	add r0, sp, #0x0
	bne _020328AE
	mov r1, #0x0
	strb r1, [r0, #0x1]
	add r1, sp, #0x0
	mov r0, #0xa
	add r1, #0x1
	bl FUN_020311D0
	pop {r3, pc}
_020328AE:
	mov r1, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0xa
	add r1, sp, #0x0
	bl FUN_020311D0
	pop {r3, pc}
	.balign 4
_020328BC: .word 0x021C5A00

	thumb_func_start FUN_020328C0
FUN_020328C0: ; 0x020328C0
	ldr r1, _020328D8 ; =0x021C5A00
	ldr r3, _020328DC ; =FUN_02031D20
	ldr r2, [r1, #0x0]
	add r2, #0x3e
	strb r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x3
	strh r2, [r0, #0x38]
	ldr r0, _020328E0 ; =FUN_02032924
	mov r1, #0x0
	bx r3
	nop
_020328D8: .word 0x021C5A00
_020328DC: .word FUN_02031D20
_020328E0: .word FUN_02032924

	thumb_func_start FUN_020328E4
FUN_020328E4: ; 0x020328E4
	ldr r0, _020328F0 ; =0x021C5A00
	mov r1, #0x7
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_020328F0: .word 0x021C5A00

	thumb_func_start FUN_020328F4
FUN_020328F4: ; 0x020328F4
	push {r3, lr}
	ldr r1, _0203291C ; =0x021C5A00
	ldr r2, [r1, #0x0]
	add r2, #0x3e
	strb r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x7
	add r0, #0x3f
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x3
	strh r2, [r0, #0x38]
	bl FUN_02033E74
	ldr r0, _02032920 ; =FUN_02032628
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_0203291C: .word 0x021C5A00
_02032920: .word FUN_02032628

	thumb_func_start FUN_02032924
FUN_02032924: ; 0x02032924
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _02032936
	ldr r0, _02032938 ; =FUN_0203293C
	mov r1, #0x0
	bl FUN_02031D20
_02032936:
	pop {r3, pc}
	.balign 4
_02032938: .word FUN_0203293C

	thumb_func_start FUN_0203293C
FUN_0203293C: ; 0x0203293C
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203296C
	ldr r0, _02032970 ; =0x021C5A00
	mov r2, #0x2
	ldr r0, [r0, #0x0]
	mov r1, #0xd
	add r0, #0x3f
	strb r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	bl FUN_0202F950
	cmp r0, #0x0
	beq _0203296C
	bl FUN_0202FA1C
	ldr r0, _02032974 ; =FUN_02032978
	mov r1, #0x64
	bl FUN_02031D20
_0203296C:
	pop {r3, pc}
	nop
_02032970: .word 0x021C5A00
_02032974: .word FUN_02032978

	thumb_func_start FUN_02032978
FUN_02032978: ; 0x02032978
	push {r3, lr}
	ldr r0, _020329E4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202E8A0
	cmp r0, #0x0
	beq _020329A4
	ldr r0, _020329E4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _020329A4
	ldr r0, _020329E8 ; =FUN_020329F4
	mov r1, #0x64
	bl FUN_02031D20
	pop {r3, pc}
_020329A4:
	bl FUN_020311F0
	cmp r0, #0x0
	bne _020329B6
	ldr r0, _020329E4 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	bne _020329DC
_020329B6:
	ldr r0, _020329E4 ; =0x021C5A00
	ldr r2, [r0, #0x0]
	ldrh r1, [r2, #0x38]
	sub r1, r1, #0x1
	strh r1, [r2, #0x38]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x38]
	cmp r0, #0x0
	bne _020329D2
	ldr r0, _020329EC ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020329D2:
	ldr r0, _020329F0 ; =FUN_02032924
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020329DC:
	beq _020329E2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
_020329E2:
	pop {r3, pc}
	.balign 4
_020329E4: .word 0x021C5A00
_020329E8: .word FUN_020329F4
_020329EC: .word FUN_020327B4
_020329F0: .word FUN_02032924

	thumb_func_start FUN_020329F4
FUN_020329F4: ; 0x020329F4
	push {r3, lr}
	ldr r0, _02032A7C ; =0x021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x5a
	bls _02032A06
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032A06:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02032A34
	ldr r0, _02032A7C ; =0x021C5A00
	ldr r2, [r0, #0x0]
	ldrh r1, [r2, #0x38]
	sub r1, r1, #0x1
	strh r1, [r2, #0x38]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x38]
	cmp r0, #0x0
	bne _02032A2A
	ldr r0, _02032A80 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A2A:
	ldr r0, _02032A84 ; =FUN_02032924
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A34:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02032A4A
	ldr r0, _02032A88 ; =FUN_0203279C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A4A:
	ldr r0, _02032A7C ; =0x021C5A00
	ldr r2, [r0, #0x0]
	ldrh r1, [r2, #0x3a]
	cmp r1, #0x0
	beq _02032A5A
	sub r0, r1, #0x1
	strh r0, [r2, #0x3a]
	pop {r3, pc}
_02032A5A:
	ldrh r1, [r2, #0x38]
	sub r1, r1, #0x1
	strh r1, [r2, #0x38]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x38]
	cmp r0, #0x0
	bne _02032A72
	ldr r0, _02032A80 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A72:
	ldr r0, _02032A84 ; =FUN_02032924
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032A7C: .word 0x021C5A00
_02032A80: .word FUN_020327B4
_02032A84: .word FUN_02032924
_02032A88: .word FUN_0203279C

	thumb_func_start FUN_02032A8C
FUN_02032A8C: ; 0x02032A8C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _02032ADA
	ldr r6, _02032ADC ; =0x02105D5C
	mov r3, #0x1
	mov r2, #0x0
_02032AA0:
	ldrb r1, [r6, #0x0]
	ldrb r0, [r4, r2]
	cmp r1, r0
	beq _02032AAC
	mov r3, #0x0
	b _02032AB4
_02032AAC:
	add r2, r2, #0x1
	add r6, r6, #0x1
	cmp r2, #0x6
	blo _02032AA0
_02032AB4:
	cmp r3, #0x0
	beq _02032AD0
	ldr r0, _02032AE0 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02032AD0
	ldr r1, _02032AE4 ; =0x02105D6C
	mov r0, #0x7
	strb r5, [r1, #0x0]
	bl FUN_02030C4C
	pop {r4-r6, pc}
_02032AD0:
	ldr r1, _02032AE8 ; =0x02105D64
	mov r0, #0x7
	strb r5, [r1, #0x0]
	bl FUN_02030C4C
_02032ADA:
	pop {r4-r6, pc}
	.balign 4
_02032ADC: .word 0x02105D5C
_02032AE0: .word 0x021C5A00
_02032AE4: .word 0x02105D6C
_02032AE8: .word 0x02105D64

	thumb_func_start FUN_02032AEC
FUN_02032AEC: ; 0x02032AEC
	push {r3-r5, lr}
	mov r4, #0x1
	ldr r5, _02032B5C ; =0x02105D6D
	add r3, r4, #0x0
_02032AF4:
	ldrb r1, [r5, #0x0]
	ldrb r0, [r2, r3]
	cmp r1, r0
	beq _02032B00
	mov r4, #0x0
	b _02032B08
_02032B00:
	add r3, r3, #0x1
	add r5, r5, #0x1
	cmp r3, #0x6
	blo _02032AF4
_02032B08:
	cmp r4, #0x0
	beq _02032B22
	ldrb r4, [r2, #0x0]
	bl FUN_02031190
	cmp r4, r0
	bne _02032B58
	ldr r0, _02032B60 ; =0x021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
	pop {r3-r5, pc}
_02032B22:
	mov r4, #0x1
	ldr r3, _02032B64 ; =0x02105D65
	add r5, r4, #0x0
_02032B28:
	ldrb r1, [r3, #0x0]
	ldrb r0, [r2, r5]
	cmp r1, r0
	beq _02032B34
	mov r4, #0x0
	b _02032B3C
_02032B34:
	add r5, r5, #0x1
	add r3, r3, #0x1
	cmp r5, #0x6
	blo _02032B28
_02032B3C:
	cmp r4, #0x0
	beq _02032B58
	ldrb r4, [r2, #0x0]
	bl FUN_02031190
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r4, r0
	bne _02032B58
	ldr r0, _02032B60 ; =0x021C5A00
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
_02032B58:
	pop {r3-r5, pc}
	nop
_02032B5C: .word 0x02105D6D
_02032B60: .word 0x021C5A00
_02032B64: .word 0x02105D65

	thumb_func_start FUN_02032B68
FUN_02032B68: ; 0x02032B68
	mov r0, #0x6
	bx lr

	thumb_func_start FUN_02032B6C
FUN_02032B6C: ; 0x02032B6C
	push {r3, lr}
	ldr r1, _02032B80 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02032B7E
	add r1, #0x3c
	strb r0, [r1, #0x0]
	bl FUN_0202D1B0
_02032B7E:
	pop {r3, pc}
	.balign 4
_02032B80: .word 0x021C5A00

	thumb_func_start FUN_02032B84
FUN_02032B84: ; 0x02032B84
	ldr r3, _02032B88 ; =FUN_0202EA54
	bx r3
	.balign 4
_02032B88: .word FUN_0202EA54

	thumb_func_start FUN_02032B8C
FUN_02032B8C: ; 0x02032B8C
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032BC6
	ldr r0, _02032BC8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032BC8 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	mov r2, #0x20
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032BC6
	bl FUN_0202FA10
	ldr r0, _02032BCC ; =FUN_02032B84
	mov r1, #0x0
	bl FUN_02031D20
_02032BC6:
	pop {r3, pc}
	.balign 4
_02032BC8: .word 0x021C5A00
_02032BCC: .word FUN_02032B84

	thumb_func_start FUN_02032BD0
FUN_02032BD0: ; 0x02032BD0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02032C00
	mov r2, #0x7
	mov r0, #0x3
	mov r1, #0xf
	lsl r2, r2, #0xc
	bl FUN_02016828
	add r0, r4, #0x0
	mov r1, #0xe
	bl FUN_02031734
	ldr r0, _02032C04 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _02032C08 ; =FUN_02032B8C
	bl FUN_02031D20
_02032C00:
	pop {r4, pc}
	nop
_02032C04: .word 0x021C5A00
_02032C08: .word FUN_02032B8C

	thumb_func_start FUN_02032C0C
FUN_02032C0C: ; 0x02032C0C
	push {r3, lr}
	ldr r0, _02032C20 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02032C1E
	ldr r0, _02032C24 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02032C1E:
	pop {r3, pc}
	.balign 4
_02032C20: .word 0x021C5A00
_02032C24: .word FUN_02032440

	thumb_func_start FUN_02032C28
FUN_02032C28: ; 0x02032C28
	sub sp, #0x8
	ldr r1, _02032C64 ; =0x020EEC48
	add r0, sp, #0x0
	ldr r2, [r1, #0x0]
	ldr r1, [r1, #0x4]
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, _02032C68 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0x24]
	cmp r1, #0x0
	bne _02032C46
	mov r0, #0x0
	add sp, #0x8
	bx lr
_02032C46:
	cmp r2, #0x0
	beq _02032C5E
_02032C4A:
	ldr r1, [r0, #0x0]
	cmp r3, r1
	bne _02032C56
	mov r0, #0x1
	add sp, #0x8
	bx lr
_02032C56:
	add r0, r0, #0x4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _02032C4A
_02032C5E:
	mov r0, #0x0
	add sp, #0x8
	bx lr
	.balign 4
_02032C64: .word 0x020EEC48
_02032C68: .word 0x021C5A00

	thumb_func_start FUN_02032C6C
FUN_02032C6C: ; 0x02032C6C
	ldr r2, _02032CE4 ; =0x00400131
	cmp r0, r2
	bhi _02032C7C
	bhs _02032CBA
	ldr r2, _02032CE8 ; =0x00000333
	cmp r0, r2
	beq _02032C8E
	bx lr
_02032C7C:
	ldr r1, _02032CEC ; =0x00400286
	cmp r0, r1
	bhi _02032C86
	beq _02032CCE
	bx lr
_02032C86:
	add r1, #0x92
	cmp r0, r1
	beq _02032CA6
	bx lr
_02032C8E:
	cmp r1, #0xf
	bne _02032CE0
	ldr r0, _02032CF0 ; =0x021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
	bx lr
_02032CA6:
	ldr r0, _02032CF0 ; =0x021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
	bx lr
_02032CBA:
	ldr r0, _02032CF0 ; =0x021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
	bx lr
_02032CCE:
	ldr r0, _02032CF0 ; =0x021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
_02032CE0:
	bx lr
	nop
_02032CE4: .word 0x00400131
_02032CE8: .word 0x00000333
_02032CEC: .word 0x00400286
_02032CF0: .word 0x021C5A00

	thumb_func_start FUN_02032CF4
FUN_02032CF4: ; 0x02032CF4
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032D34
	ldr r0, _02032D38 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032D38 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	ldr r0, _02032D3C ; =FUN_02032C6C
	bl FUN_0202D308
	mov r0, #0x1
	add r1, r0, #0x0
	mov r2, #0x20
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032D34
	bl FUN_0202FA10
	ldr r0, _02032D40 ; =FUN_02032B84
	mov r1, #0x0
	bl FUN_02031D20
_02032D34:
	pop {r3, pc}
	nop
_02032D38: .word 0x021C5A00
_02032D3C: .word FUN_02032C6C
_02032D40: .word FUN_02032B84

	thumb_func_start FUN_02032D44
FUN_02032D44: ; 0x02032D44
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02032D74
	mov r2, #0x7
	mov r0, #0x3
	mov r1, #0xf
	lsl r2, r2, #0xc
	bl FUN_02016828
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_02031734
	ldr r0, _02032D78 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _02032D7C ; =FUN_02032CF4
	bl FUN_02031D20
_02032D74:
	pop {r4, pc}
	nop
_02032D78: .word 0x021C5A00
_02032D7C: .word FUN_02032CF4

	thumb_func_start FUN_02032D80
FUN_02032D80: ; 0x02032D80
	push {r3, lr}
	ldr r0, _02032D94 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02032D92
	ldr r0, _02032D98 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02032D92:
	pop {r3, pc}
	.balign 4
_02032D94: .word 0x021C5A00
_02032D98: .word FUN_02032440

	thumb_func_start FUN_02032D9C
FUN_02032D9C: ; 0x02032D9C
	ldr r0, _02032DA8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x49
	ldrb r0, [r0, #0x0]
	bx lr
	nop
_02032DA8: .word 0x021C5A00

	thumb_func_start FUN_02032DAC
FUN_02032DAC: ; 0x02032DAC
	push {r3, lr}
	bl FUN_02031468
	ldr r0, _02032DF4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02032DBE
	mov r0, #0x1
	pop {r3, pc}
_02032DBE:
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	add r0, #0xe8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _02032DD4
	bl MOD04_021D83C0
	mov r0, #0x1
	pop {r3, pc}
_02032DD4:
	bl FUN_02033590
	cmp r0, #0x0
	beq _02032DE6
	ldr r0, _02032DF8 ; =FUN_0203318C
	mov r1, #0x0
	bl FUN_02031D20
	b _02032DEE
_02032DE6:
	ldr r0, _02032DFC ; =FUN_02032178
	mov r1, #0x0
	bl FUN_02031D20
_02032DEE:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02032DF4: .word 0x021C5A00
_02032DF8: .word FUN_0203318C
_02032DFC: .word FUN_02032178

	thumb_func_start FUN_02032E00
FUN_02032E00: ; 0x02032E00
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032E3C
	ldr r0, _02032E40 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032E40 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _02032E3C
	bl FUN_0202FA10
	ldr r0, _02032E44 ; =FUN_02032218
	mov r1, #0x0
	bl FUN_02031D20
_02032E3C:
	pop {r3, pc}
	nop
_02032E40: .word 0x021C5A00
_02032E44: .word FUN_02032218

	thumb_func_start FUN_02032E48
FUN_02032E48: ; 0x02032E48
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032E82
	ldr r0, _02032E84 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032E84 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032E82
	bl FUN_0202FA10
	ldr r0, _02032E88 ; =FUN_02032290
	mov r1, #0x0
	bl FUN_02031D20
_02032E82:
	pop {r3, pc}
	.balign 4
_02032E84: .word 0x021C5A00
_02032E88: .word FUN_02032290

	thumb_func_start FUN_02032E8C
FUN_02032E8C: ; 0x02032E8C
	bx lr
	.balign 4

	thumb_func_start FUN_02032E90
FUN_02032E90: ; 0x02032E90
	push {r3, lr}
	bl MOD04_021D7F8C
	cmp r0, #0x0
	bge _02032EA2
	ldr r0, _02032EA4 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
_02032EA2:
	pop {r3, pc}
	.balign 4
_02032EA4: .word FUN_02032E8C

	thumb_func_start FUN_02032EA8
FUN_02032EA8: ; 0x02032EA8
	bx lr
	.balign 4

	thumb_func_start FUN_02032EAC
FUN_02032EAC: ; 0x02032EAC
	bx lr
	.balign 4

	thumb_func_start FUN_02032EB0
FUN_02032EB0: ; 0x02032EB0
	push {r3, lr}
	mov r0, #0x1
	bl FUN_020313A0
	bl MOD04_021D7F8C
	cmp r0, #0xa
	blt _02032ECA
	ldr r0, _02032F0C ; =FUN_02032EAC
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032ECA:
	cmp r0, #0x0
	bge _02032ED8
	ldr r0, _02032F10 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032ED8:
	cmp r0, #0x1
	bne _02032EE6
	ldr r0, _02032F14 ; =FUN_02032E90
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032EE6:
	cmp r0, #0x2
	bne _02032F08
	ldr r0, _02032F18 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02032F00
	ldr r0, _02032F10 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F00:
	ldr r0, _02032F1C ; =FUN_02032EA8
	mov r1, #0x0
	bl FUN_02031D20
_02032F08:
	pop {r3, pc}
	nop
_02032F0C: .word FUN_02032EAC
_02032F10: .word FUN_02032E8C
_02032F14: .word FUN_02032E90
_02032F18: .word 0x021C5A00
_02032F1C: .word FUN_02032EA8

	thumb_func_start FUN_02032F20
FUN_02032F20: ; 0x02032F20
	add r1, r0, #0x2
	cmp r1, #0x1
	bls _02032F28
	neg r0, r0
_02032F28:
	ldr r1, _02032F30 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x34]
	bx lr
	.balign 4
_02032F30: .word 0x021C5A00

	thumb_func_start FUN_02032F34
FUN_02032F34: ; 0x02032F34
	push {r3, lr}
	mov r0, #0x0
	bl MOD04_021D7800
	cmp r0, #0xa
	blt _02032F4A
	ldr r0, _02032F88 ; =FUN_02032EAC
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F4A:
	cmp r0, #0x0
	bge _02032F5C
	bl FUN_02032F20
	ldr r0, _02032F8C ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F5C:
	cmp r0, #0x1
	bne _02032F6A
	ldr r0, _02032F90 ; =FUN_02032EB0
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F6A:
	cmp r0, #0x2
	bne _02032F78
	ldr r0, _02032F94 ; =FUN_02032EA8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F78:
	cmp r0, #0x3
	bne _02032F84
	ldr r0, _02032F88 ; =FUN_02032EAC
	mov r1, #0x0
	bl FUN_02031D20
_02032F84:
	pop {r3, pc}
	nop
_02032F88: .word FUN_02032EAC
_02032F8C: .word FUN_02032E8C
_02032F90: .word FUN_02032EB0
_02032F94: .word FUN_02032EA8

	thumb_func_start FUN_02032F98
FUN_02032F98: ; 0x02032F98
	push {r3, lr}
	mov r0, #0x1
	bl MOD04_021D7800
	cmp r0, #0x0
	bge _02032FB2
	bl FUN_02032F20
	ldr r0, _02032FD0 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032FB2:
	ldr r0, _02032FD4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x42
	ldrb r0, [r0, #0x0]
	bl MOD04_021D8494
	cmp r0, #0x0
	beq _02032FCE
	bl FUN_0202FC60
	ldr r0, _02032FD8 ; =FUN_02032F34
	mov r1, #0x0
	bl FUN_02031D20
_02032FCE:
	pop {r3, pc}
	.balign 4
_02032FD0: .word FUN_02032E8C
_02032FD4: .word 0x021C5A00
_02032FD8: .word FUN_02032F34

	thumb_func_start FUN_02032FDC
FUN_02032FDC: ; 0x02032FDC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02032FFC ; =FUN_020303BC
	ldr r1, _02033000 ; =FUN_02030238
	bl MOD04_021D77C4
	ldr r0, _02033004 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x42
	strb r4, [r0, #0x0]
	ldr r0, _02033008 ; =FUN_02032F98
	bl FUN_02031D20
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02032FFC: .word FUN_020303BC
_02033000: .word FUN_02030238
_02033004: .word 0x021C5A00
_02033008: .word FUN_02032F98

	thumb_func_start FUN_0203300C
FUN_0203300C: ; 0x0203300C
	ldr r0, _02033048 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	ldr r0, _0203304C ; =FUN_02032F34
	cmp r1, r0
	bne _0203301C
	mov r0, #0x0
	bx lr
_0203301C:
	ldr r0, _02033050 ; =FUN_02032EB0
	cmp r1, r0
	bne _02033026
	mov r0, #0x1
	bx lr
_02033026:
	ldr r0, _02033054 ; =FUN_02032E90
	cmp r1, r0
	bne _02033030
	mov r0, #0x3
	bx lr
_02033030:
	ldr r0, _02033058 ; =FUN_02032EA8
	cmp r1, r0
	bne _0203303A
	mov r0, #0x4
	bx lr
_0203303A:
	ldr r0, _0203305C ; =FUN_02032EAC
	cmp r1, r0
	bne _02033044
	mov r0, #0x5
	bx lr
_02033044:
	mov r0, #0x2
	bx lr
	.balign 4
_02033048: .word 0x021C5A00
_0203304C: .word FUN_02032F34
_02033050: .word FUN_02032EB0
_02033054: .word FUN_02032E90
_02033058: .word FUN_02032EA8
_0203305C: .word FUN_02032EAC

	thumb_func_start FUN_02033060
FUN_02033060: ; 0x02033060
	push {r3, lr}
	ldr r0, _02033090 ; =FUN_020303BC
	ldr r1, _02033094 ; =FUN_02030238
	bl MOD04_021D77C4
	mov r0, #0x0
	mvn r0, r0
	bl MOD04_021D8494
	cmp r0, #0x0
	beq _0203308C
	ldr r0, _02033098 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x4d
	strb r1, [r0, #0x0]
	bl FUN_0202FC60
	ldr r0, _0203309C ; =FUN_02032F34
	mov r1, #0x0
	bl FUN_02031D20
_0203308C:
	pop {r3, pc}
	nop
_02033090: .word FUN_020303BC
_02033094: .word FUN_02030238
_02033098: .word 0x021C5A00
_0203309C: .word FUN_02032F34

	thumb_func_start FUN_020330A0
FUN_020330A0: ; 0x020330A0
	push {r3, lr}
	mov r0, #0x0
	bl FUN_020313A0
	ldr r0, _020330D8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x41
	ldrb r0, [r0, #0x0]
	bl MOD04_021D82BC
	cmp r0, #0x0
	beq _020330C6
	bl MOD04_021D836C
	ldr r0, _020330DC ; =FUN_02033060
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020330C6:
	bl MOD04_021D7F8C
	cmp r0, #0x0
	bge _020330D6
	ldr r0, _020330E0 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
_020330D6:
	pop {r3, pc}
	.balign 4
_020330D8: .word 0x021C5A00
_020330DC: .word FUN_02033060
_020330E0: .word FUN_02032E8C

	thumb_func_start FUN_020330E4
FUN_020330E4: ; 0x020330E4
	push {r3, lr}
	bl FUN_02031190
	cmp r0, #0x0
	bne _02033100
	ldr r0, _02033120 ; =0x021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033124 ; =FUN_020330A0
	bl FUN_02031D20
	b _02033112
_02033100:
	ldr r0, _02033120 ; =0x021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033124 ; =FUN_020330A0
	mov r1, #0x0
	bl FUN_02031D20
_02033112:
	ldr r0, _02033120 ; =0x021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x4d
	strb r1, [r0, #0x0]
	pop {r3, pc}
	nop
_02033120: .word 0x021C5A00
_02033124: .word FUN_020330A0

	thumb_func_start FUN_02033128
FUN_02033128: ; 0x02033128
	ldr r0, _02033134 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4d
	ldrb r0, [r0, #0x0]
	bx lr
	nop
_02033134: .word 0x021C5A00

	thumb_func_start FUN_02033138
FUN_02033138: ; 0x02033138
	ldr r0, _0203314C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	ldr r0, _02033150 ; =FUN_02033060
	cmp r1, r0
	bne _02033148
	mov r0, #0x1
	bx lr
_02033148:
	mov r0, #0x0
	bx lr
	.balign 4
_0203314C: .word 0x021C5A00
_02033150: .word FUN_02033060

	thumb_func_start FUN_02033154
FUN_02033154: ; 0x02033154
	ldr r0, _02033174 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	ldr r0, _02033178 ; =FUN_02032F34
	cmp r1, r0
	bne _02033164
	mov r0, #0x1
	bx lr
_02033164:
	ldr r0, _0203317C ; =FUN_02033060
	cmp r1, r0
	bne _0203316E
	mov r0, #0x1
	bx lr
_0203316E:
	mov r0, #0x0
	bx lr
	nop
_02033174: .word 0x021C5A00
_02033178: .word FUN_02032F34
_0203317C: .word FUN_02033060

	thumb_func_start FUN_02033180
FUN_02033180: ; 0x02033180
	ldr r0, _02033188 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bx lr
	.balign 4
_02033188: .word 0x021C5A00

	thumb_func_start FUN_0203318C
FUN_0203318C: ; 0x0203318C
	push {r3, lr}
	mov r0, #0x0
	bl FUN_020313A0
	mov r0, #0x0
	bl MOD04_021D82BC
	cmp r0, #0x0
	beq _020331AA
	bl MOD04_021D836C
	ldr r0, _020331BC ; =FUN_02032440
	mov r1, #0x0
	bl FUN_02031D20
_020331AA:
	bl MOD04_021D7F8C
	cmp r0, #0x0
	bge _020331BA
	ldr r0, _020331C0 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
_020331BA:
	pop {r3, pc}
	.balign 4
_020331BC: .word FUN_02032440
_020331C0: .word FUN_02032E8C

	thumb_func_start FUN_020331C4
FUN_020331C4: ; 0x020331C4
	push {r3, lr}
	ldr r0, _020331E0 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020331DC
	mov r0, #0x1
	bl FUN_020166B8
	ldr r0, _020331E4 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_020331DC:
	pop {r3, pc}
	nop
_020331E0: .word 0x021C5A00
_020331E4: .word FUN_02032440

	thumb_func_start FUN_020331E8
FUN_020331E8: ; 0x020331E8
	push {r3, lr}
	ldr r0, _02033200 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020331FE
	mov r1, #0x0
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033204 ; =FUN_020330A0
	bl FUN_02031D20
_020331FE:
	pop {r3, pc}
	.balign 4
_02033200: .word 0x021C5A00
_02033204: .word FUN_020330A0

	thumb_func_start FUN_02033208
FUN_02033208: ; 0x02033208
	push {r3, lr}
	ldr r0, _02033234 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033232
	bl FUN_02031190
	cmp r0, #0x0
	bne _02033220
	mov r1, #0x0
	ldr r0, _02033234 ; =0x021C5A00
	b _02033224
_02033220:
	ldr r0, _02033234 ; =0x021C5A00
	mov r1, #0x1
_02033224:
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033238 ; =FUN_020330A0
	mov r1, #0x0
	bl FUN_02031D20
_02033232:
	pop {r3, pc}
	.balign 4
_02033234: .word 0x021C5A00
_02033238: .word FUN_020330A0

	thumb_func_start FUN_0203323C
FUN_0203323C: ; 0x0203323C
	push {r3, lr}
	bl FUN_02031190
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	mov r0, #0x15
	add r1, sp, #0x0
	bl FUN_020311D0
	pop {r3, pc}

	thumb_func_start FUN_02033250
FUN_02033250: ; 0x02033250
	ldr r0, _0203327C ; =0x021C5A00
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _02033276
	ldr r1, [r2, #0x24]
	ldr r0, _02033280 ; =FUN_02032E8C
	cmp r1, r0
	bne _02033264
	mov r0, #0x1
	bx lr
_02033264:
	ldr r0, _02033284 ; =FUN_02032E90
	cmp r1, r0
	bne _02033276
	add r2, #0x44
	ldrb r0, [r2, #0x0]
	cmp r0, #0x0
	beq _02033276
	mov r0, #0x1
	bx lr
_02033276:
	mov r0, #0x0
	bx lr
	nop
_0203327C: .word 0x021C5A00
_02033280: .word FUN_02032E8C
_02033284: .word FUN_02032E90

	thumb_func_start FUN_02033288
FUN_02033288: ; 0x02033288
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020332D8 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020332D6
	mov r1, #0xf
	add r2, r1, #0x0
	mov r0, #0x3
	add r2, #0xf1
	bl FUN_02016828
	mov r0, #0xf
	mov r1, #0x50
	bl FUN_02016998
	ldr r1, _020332D8 ; =0x021C5A00
	mov r2, #0x50
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _020332D8 ; =0x021C5A00
	mov r2, #0x18
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, #0x1
	add r2, #0x46
	strb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	str r4, [r0, #0x28]
	mov r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	bl FUN_020166A8
_020332D6:
	pop {r4, pc}
	.balign 4
_020332D8: .word 0x021C5A00

	thumb_func_start FUN_020332DC
FUN_020332DC: ; 0x020332DC
	push {r3, lr}
	ldr r0, _0203330C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033308
	mov r0, #0x1
	bl FUN_020166B8
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _0203330C ; =0x021C5A00
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0203330C ; =0x021C5A00
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, #0xf
	bl FUN_020168D0
_02033308:
	pop {r3, pc}
	nop
_0203330C: .word 0x021C5A00

	thumb_func_start FUN_02033310
FUN_02033310: ; 0x02033310
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02033360 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203335E
	mov r1, #0xf
	add r2, r1, #0x0
	mov r0, #0x3
	add r2, #0xf1
	bl FUN_02016828
	mov r0, #0xf
	mov r1, #0x50
	bl FUN_02016998
	ldr r1, _02033360 ; =0x021C5A00
	mov r2, #0x50
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _02033360 ; =0x021C5A00
	mov r2, #0x19
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, #0x1
	add r2, #0x46
	strb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	str r4, [r0, #0x28]
	mov r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	bl FUN_020166A8
_0203335E:
	pop {r4, pc}
	.balign 4
_02033360: .word 0x021C5A00

	thumb_func_start FUN_02033364
FUN_02033364: ; 0x02033364
	push {r3, lr}
	ldr r0, _02033394 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033390
	mov r0, #0x1
	bl FUN_020166B8
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _02033394 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _02033394 ; =0x021C5A00
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, #0xf
	bl FUN_020168D0
_02033390:
	pop {r3, pc}
	nop
_02033394: .word 0x021C5A00

	thumb_func_start FUN_02033398
FUN_02033398: ; 0x02033398
	push {r3, lr}
	sub sp, #0x8
	ldr r0, _020333EC ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020333AA
	add sp, #0x8
	mov r0, #0x0
	pop {r3, pc}
_020333AA:
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x18
	bne _020333C8
	add r0, sp, #0x4
	add r1, sp, #0x0
	bl MOD04_021DD718
	cmp r0, #0x0
	beq _020333E4
	bl MOD04_021DD6F0
	add sp, #0x8
	mov r0, #0x1
	pop {r3, pc}
_020333C8:
	cmp r0, #0x19
	bne _020333E4
	add r0, sp, #0x4
	add r1, sp, #0x0
	bl MOD04_021DD718
	cmp r0, #0x0
	beq _020333E4
	ldr r0, [sp, #0x0]
	cmp r0, #0x7
	bne _020333E4
	add sp, #0x8
	mov r0, #0x1
	pop {r3, pc}
_020333E4:
	mov r0, #0x0
	add sp, #0x8
	pop {r3, pc}
	nop
_020333EC: .word 0x021C5A00

	thumb_func_start FUN_020333F0
FUN_020333F0: ; 0x020333F0
	push {r3, lr}
	bl MOD04_021D76AC
	cmp r0, #0x0
	bge _02033408
	bl FUN_02032F20
	ldr r0, _02033414 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02033408:
	ble _02033412
	ldr r0, _02033418 ; =FUN_02033060
	mov r1, #0x0
	bl FUN_02031D20
_02033412:
	pop {r3, pc}
	.balign 4
_02033414: .word FUN_02032E8C
_02033418: .word FUN_02033060

	thumb_func_start FUN_0203341C
FUN_0203341C: ; 0x0203341C
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _0203345E
	mov r1, #0x31
	mov r0, #0x3
	lsl r2, r1, #0xc
	bl FUN_02016828
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _0203345E
	ldr r0, _02033460 ; =0x021C5A00
	mov r1, #0x31
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl MOD05_021D74E0
	ldr r0, _02033464 ; =FUN_020335D0
	bl MOD04_021D83A8
	bl FUN_0202FA10
	ldr r0, _02033468 ; =FUN_020333F0
	mov r1, #0x0
	bl FUN_02031D20
_0203345E:
	pop {r3, pc}
	.balign 4
_02033460: .word 0x021C5A00
_02033464: .word FUN_020335D0
_02033468: .word FUN_020333F0

	thumb_func_start FUN_0203346C
FUN_0203346C: ; 0x0203346C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020238F4
	bl FUN_02030F40
	cmp r0, #0x0
	beq _02033482
	mov r0, #0x0
	pop {r3-r5, pc}
_02033482:
	mov r0, #0x1
	bl FUN_020166A8
	ldr r2, _020334D0 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r5, #0x0
	mov r1, #0x17
	bl FUN_02031734
	mov r0, #0xf
	add r1, r4, #0x0
	bl FUN_02016998
	ldr r1, _020334D4 ; =0x021C5A00
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r2, r4, #0x0
	bl MI_CpuFill8
	ldr r0, _020334D4 ; =0x021C5A00
	mov r1, #0x0
	ldr r2, [r0, #0x0]
	add r2, #0x40
	strb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	str r5, [r0, #0x28]
	ldr r0, _020334D8 ; =FUN_0203341C
	bl FUN_02031D20
	ldr r0, _020334D4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020334D0: .word 0x00007080
_020334D4: .word 0x021C5A00
_020334D8: .word FUN_0203341C

	thumb_func_start FUN_020334DC
FUN_020334DC: ; 0x020334DC
	ldr r0, _020334E4 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020334E4: .word 0x021C5A00

	thumb_func_start FUN_020334E8
FUN_020334E8: ; 0x020334E8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0203350C ; =0x021C5A00
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020334FE
	add r2, #0x44
	strb r4, [r2, #0x0]
	ldr r0, [r0, #0x0]
	add r0, #0x45
	strb r1, [r0, #0x0]
_020334FE:
	add r0, r4, #0x0
	bl FUN_0202EE84
	add r0, r4, #0x0
	bl FUN_0202EEB0
	pop {r4, pc}
	.balign 4
_0203350C: .word 0x021C5A00

	thumb_func_start FUN_02033510
FUN_02033510: ; 0x02033510
	ldr r0, _02033530 ; =0x021C5A00
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0203352C
	add r0, r1, #0x0
	add r0, #0x4e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033526
	mov r0, #0x1
	bx lr
_02033526:
	add r1, #0x45
	ldrb r0, [r1, #0x0]
	bx lr
_0203352C:
	mov r0, #0x0
	bx lr
	.balign 4
_02033530: .word 0x021C5A00

	thumb_func_start FUN_02033534
FUN_02033534: ; 0x02033534
	ldr r0, _02033548 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033542
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	bx lr
_02033542:
	mov r0, #0x1
	bx lr
	nop
_02033548: .word 0x021C5A00

	thumb_func_start FUN_0203354C
FUN_0203354C: ; 0x0203354C
	ldr r0, _02033560 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203355A
	add r0, #0x40
	ldrb r0, [r0, #0x0]
	bx lr
_0203355A:
	mov r0, #0x0
	bx lr
	nop
_02033560: .word 0x021C5A00

	thumb_func_start FUN_02033564
FUN_02033564: ; 0x02033564
	ldr r1, _02033570 ; =0x021C5A00
	ldr r3, _02033574 ; =MI_CpuCopy8
	ldr r1, [r1, #0x0]
	mov r2, #0x6
	add r1, r1, #0x4
	bx r3
	.balign 4
_02033570: .word 0x021C5A00
_02033574: .word MI_CpuCopy8

	thumb_func_start FUN_02033578
FUN_02033578: ; 0x02033578
	add r1, r0, #0x0
	ldr r0, _02033588 ; =0x021C5A00
	ldr r3, _0203358C ; =MI_CpuCopy8
	ldr r0, [r0, #0x0]
	mov r2, #0x6
	add r0, r0, #0x4
	bx r3
	nop
_02033588: .word 0x021C5A00
_0203358C: .word MI_CpuCopy8

	thumb_func_start FUN_02033590
FUN_02033590: ; 0x02033590
	push {r3, lr}
	bl FUN_02033534
	cmp r0, #0x13
	blt _0203359E
	mov r0, #0x1
	pop {r3, pc}
_0203359E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020335A4
FUN_020335A4: ; 0x020335A4
	ldr r1, _020335B4 ; =0x021C5A00
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020335B0
	add r1, #0x47
	strb r0, [r1, #0x0]
_020335B0:
	bx lr
	nop
_020335B4: .word 0x021C5A00

	thumb_func_start FUN_020335B8
FUN_020335B8: ; 0x020335B8
	ldr r0, _020335CC ; =0x021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020335C6
	add r0, #0x47
	ldrb r0, [r0, #0x0]
	bx lr
_020335C6:
	mov r0, #0x0
	bx lr
	nop
_020335CC: .word 0x021C5A00

	thumb_func_start FUN_020335D0
FUN_020335D0: ; 0x020335D0
	push {r3, lr}
	add r2, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1
	bl FUN_02033F70
_020335DC:
	b _020335DC
	.balign 4

	thumb_func_start FUN_020335E0
FUN_020335E0: ; 0x020335E0
	push {r3, lr}
	mov r0, #0x0
	mov r1, #0x4
	add r2, r0, #0x0
	bl FUN_02033F70
_020335EC:
	b _020335EC
	.balign 4

	thumb_func_start FUN_020335F0
FUN_020335F0: ; 0x020335F0
	bx lr
	.balign 4

	thumb_func_start FUN_020335F4
FUN_020335F4: ; 0x020335F4
	push {r3, lr}
	bl FUN_02033510
	cmp r0, #0x0
	beq _0203366C
	bl FUN_020311F0
	cmp r0, #0x0
	bne _02033622
	bl FUN_02033250
	cmp r0, #0x0
	bne _02033622
	bl FUN_02033398
	cmp r0, #0x0
	bne _02033622
	ldr r0, _02033670 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203366C
_02033622:
	bl FUN_020335B8
	cmp r0, #0x0
	bne _0203366C
	bl FUN_0200541C
	ldr r0, _02033670 ; =0x021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202287C
	ldr r1, _02033674 ; =0x021C4918
	mov r0, #0x1
	strb r0, [r1, #0x4]
	ldr r1, _02033670 ; =0x021C5A00
	ldr r2, [r1, #0x0]
	add r1, r2, #0x0
	add r1, #0x4e
	ldrb r1, [r1, #0x0]
	cmp r1, #0x3
	bne _02033654
	mov r0, #0x3
	bl FUN_020335A4
	pop {r3, pc}
_02033654:
	add r2, #0x3f
	ldrb r1, [r2, #0x0]
	cmp r1, #0x19
	beq _02033660
	cmp r1, #0xf
	bne _02033668
_02033660:
	mov r0, #0x2
	bl FUN_020335A4
	pop {r3, pc}
_02033668:
	bl FUN_020335A4
_0203366C:
	pop {r3, pc}
	nop
_02033670: .word 0x021C5A00
_02033674: .word 0x021C4918

	thumb_func_start FUN_02033678
FUN_02033678: ; 0x02033678
	push {r3, lr}
	bl FUN_0202EDD8
	cmp r0, #0x0
	bne _0203368A
	bl FUN_02031810
	cmp r0, #0x0
	bne _0203368E
_0203368A:
	mov r0, #0x1
	pop {r3, pc}
_0203368E:
	bl FUN_0202E344
	cmp r0, #0x0
	bne _0203369A
	mov r0, #0x1
	pop {r3, pc}
_0203369A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020336A0
FUN_020336A0: ; 0x020336A0
	push {r3, lr}
	ldr r1, _020336BC ; =0x021C5A00
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020336B6
	add r1, #0x4e
	strb r0, [r1, #0x0]
	bl FUN_02031468
	mov r0, #0x1
	pop {r3, pc}
_020336B6:
	mov r0, #0x0
	pop {r3, pc}
	nop
_020336BC: .word 0x021C5A00

	thumb_func_start FUN_020336C0
FUN_020336C0: ; 0x020336C0
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020336C8
FUN_020336C8: ; 0x020336C8
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r6, r1, #0x0
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	cmp r1, #0x6
	bhi _02033774
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020336E2: ; jump table (using 16-bit offset)
	.short _020336F0 - _020336E2 - 2; case 0
	.short _020336FC - _020336E2 - 2; case 1
	.short _02033714 - _020336E2 - 2; case 2
	.short _0203373A - _020336E2 - 2; case 3
	.short _0203374A - _020336E2 - 2; case 4
	.short _0203376A - _020336E2 - 2; case 5
	.short _02033770 - _020336E2 - 2; case 6
_020336F0:
	mov r0, #0x6f
	bl FUN_02031588
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02033774
_020336FC:
	mov r0, #0x6f
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02033774
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02022840
	mov r0, #0x2
	str r0, [r4, #0x0]
	b _02033774
_02033714:
	bl FUN_02022854
	add r5, r0, #0x0
	cmp r5, #0x2
	bne _02033722
	bl ErrorHandling
_02033722:
	cmp r5, #0x3
	bne _0203372A
	bl ErrorHandling
_0203372A:
	cmp r5, #0x1
	bne _02033774
	mov r0, #0x3
	str r0, [r4, #0x0]
	mov r0, #0x70
	bl FUN_02031588
	b _02033774
_0203373A:
	mov r0, #0x70
	bl FUN_020315D8
	cmp r0, #0x0
	beq _02033774
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _02033774
_0203374A:
	bl FUN_02022854
	add r5, r0, #0x0
	cmp r5, #0x3
	bne _02033758
	bl ErrorHandling
_02033758:
	cmp r5, #0x1
	bne _02033760
	bl ErrorHandling
_02033760:
	cmp r5, #0x2
	bne _02033774
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _02033774
_0203376A:
	mov r0, #0x6
	str r0, [r4, #0x0]
	b _02033774
_02033770:
	mov r0, #0x1
	pop {r4-r6, pc}
_02033774:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02033778
FUN_02033778: ; 0x02033778
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	bl FUN_02030F20
	add r7, r0, #0x0
	mov r0, #0x0
	bl FUN_0202DFA4
	cmp r0, #0x0
	beq _020337C6
	mov r5, #0x0
	cmp r7, #0x0
	ble _020337C6
_02033792:
	bl FUN_02031190
	cmp r5, r0
	beq _020337C0
	add r0, r5, #0x0
	bl FUN_0202E020
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202E044
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202DFA4
	bl FUN_02023A70
	add r3, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020337C8
_020337C0:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02033792
_020337C6:
	pop {r3-r7, pc}

	thumb_func_start FUN_020337C8
FUN_020337C8: ; 0x020337C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02029B40
	cmp r0, #0x0
	bne _020337E4
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	mov r3, #0x1
	bl FUN_02029B90
_020337E4:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020337E8
FUN_020337E8: ; 0x020337E8
	push {r3-r5, lr}
	mov r1, #0x72
	lsl r1, r1, #0x4
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, #0x1f
	mov r1, #0x1f
	bic r0, r1
	bl FUN_02096B14
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203380C
FUN_0203380C: ; 0x0203380C
	push {r4, lr}
	bl FUN_02028228
	add r4, r0, #0x0
	bl FUN_02096FB0
	cmp r0, #0x0
	bne _0203382A
	ldr r1, _0203382C ; =0x4144414A
	add r0, r4, #0x0
	bl thunk_FUN_02097190
	add r0, r4, #0x0
	bl thunk_FUN_02096e4c
_0203382A:
	pop {r4, pc}
	.balign 4
_0203382C: .word 0x4144414A

	thumb_func_start FUN_02033830
FUN_02033830: ; 0x02033830
	push {r3-r4, lr}
	sub sp, #0xc
	bl FUN_02028228
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl FUN_02096CCC
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl FUN_02096DA0
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0203384C
FUN_0203384C: ; 0x0203384C
	push {r4, lr}
	bl FUN_020286EC
	bl FUN_02028228
	add r4, r0, #0x0
	bl FUN_02096F80
	cmp r0, #0x0
	beq _0203386E
	add r0, r4, #0x0
	bl FUN_02096F18
	cmp r0, #0x0
	beq _0203386E
	mov r0, #0x1
	pop {r4, pc}
_0203386E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02033874
FUN_02033874: ; 0x02033874
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	bl FUN_020286EC
	bl FUN_02028228
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020286EC
	mov r1, #0x0
	bl FUN_0202838C
	add r4, r0, #0x0
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	mvn r1, r1
	str r1, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_0209700C
	cmp r0, #0x0
	bne _020338AE
	add sp, #0x8
	mov r0, #0x3
	pop {r3-r7, pc}
_020338AE:
	mov r7, #0x0
_020338B0:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02096B78
	cmp r0, #0x0
	beq _020338C6
	ldr r0, [sp, #0x0]
	add sp, #0x8
	str r7, [r0, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_020338C6:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02096DA0
	cmp r0, #0x0
	ble _020338F4
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02096DA0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02096DA0
	ldr r1, [sp, #0x4]
	cmp r1, r0
	bne _020338F4
	ldr r0, [sp, #0x0]
	add sp, #0x8
	str r7, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_020338F4:
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bge _0203390A
	add r0, r4, #0x0
	bl FUN_0209700C
	cmp r0, #0x0
	bne _0203390A
	ldr r0, [sp, #0x0]
	str r7, [r0, #0x0]
_0203390A:
	add r7, r7, #0x1
	add r4, #0xc
	cmp r7, #0x20
	blt _020338B0
	mov r0, #0x2
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02033918
FUN_02033918: ; 0x02033918
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r6, r3, #0x0
	bl FUN_020286EC
	bl FUN_02028228
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020286EC
	mov r1, #0x0
	bl FUN_0202838C
	add r5, r0, #0x0
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r7, #0x0
	bl FUN_020973B4
	cmp r0, #0x0
	bne _02033950
	add sp, #0x18
	mov r0, #0x3
	pop {r3-r7, pc}
_02033950:
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, sp, #0xc
	bl FUN_02096D2C
	add r0, r7, #0x0
	add r1, sp, #0xc
	bl FUN_02096DA0
	cmp r0, #0x0
	bgt _0203396C
	add sp, #0x18
	mov r0, #0x3
	pop {r3-r7, pc}
_0203396C:
	mov r0, #0x0
	mvn r0, r0
	str r0, [r6, #0x0]
	mov r4, #0x0
_02033974:
	add r0, r7, #0x0
	add r1, sp, #0xc
	bl FUN_02096DA0
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	add r1, r5, #0x0
	bl FUN_02096DA0
	ldr r1, [sp, #0x8]
	cmp r1, r0
	bne _02033994
	add sp, #0x18
	str r4, [r6, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
_02033994:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	bge _020339A6
	add r0, r5, #0x0
	bl FUN_0209700C
	cmp r0, #0x0
	bne _020339A6
	str r4, [r6, #0x0]
_020339A6:
	add r4, r4, #0x1
	add r5, #0xc
	cmp r4, #0x20
	blt _02033974
	mov r0, #0x2
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_020339B4
FUN_020339B4: ; 0x020339B4
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r1, #0x0
	mov r1, #0x0
	add r5, r0, #0x0
	str r2, [sp, #0x4]
	str r1, [sp, #0xc]
	bl FUN_020286EC
	mov r1, #0x0
	bl FUN_0202838C
	str r0, [sp, #0x8]
	mov r4, #0x0
	bl FUN_02030F20
	cmp r0, #0x0
	ble _02033A68
_020339D8:
	bl FUN_02031190
	cmp r4, r0
	beq _02033A5C
	add r0, r4, #0x0
	bl FUN_0202DFD8
	add r7, r0, #0x0
	beq _02033A5C
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x10
	bl FUN_02033874
	str r0, [r6, #0x0]
	cmp r0, #0x3
	bne _020339FE
	bl ErrorHandling
_020339FE:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02033A1C
	mov r0, #0x2
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02033A70
	add r0, r5, #0x0
	bl FUN_0202E1BC
	b _02033A5C
_02033A1C:
	cmp r0, #0x1
	bne _02033A54
	bl FUN_02033590
	cmp r0, #0x0
	bne _02033A5C
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02033A70
	ldr r2, [sp, #0x10]
	mov r1, #0xc
	add r3, r2, #0x0
	mul r3, r1
	ldr r1, [sp, #0x8]
	add r0, r7, #0x0
	add r1, r1, r3
	mov r2, #0xc
	bl MI_CpuCopy8
	add r0, r5, #0x0
	bl FUN_0202E1BC
	b _02033A5C
_02033A54:
	cmp r0, #0x2
	bne _02033A5C
	mov r0, #0x1
	str r0, [sp, #0xc]
_02033A5C:
	add r6, r6, #0x4
	add r4, r4, #0x1
	bl FUN_02030F20
	cmp r4, r0
	blt _020339D8
_02033A68:
	ldr r0, [sp, #0xc]
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02033A70
FUN_02033A70: ; 0x02033A70
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r2, #0x0
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	str r3, [sp, #0x4]
	bl FUN_020286EC
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_0202838C
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	bl FUN_0202DFA4
	add r6, r0, #0x0
	ldr r0, [sp, #0x28]
	cmp r0, #0x2
	beq _02033AA6
	add r0, r7, #0x0
	bl FUN_0202DFD8
	ldr r1, [sp, #0x8]
	mov r2, #0xc
	bl MI_CpuCopy8
_02033AA6:
	ldr r0, [sp, #0x28]
	cmp r0, #0x0
	bne _02033AEC
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	bl FUN_020239A0
	str r0, [sp, #0xc]
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020283C0
	ldr r0, [sp, #0xc]
	bl FUN_02021A20
	add r0, r6, #0x0
	bl FUN_020239CC
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_020282E8
	add r0, r6, #0x0
	bl FUN_020239BC
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_020282E8
	b _02033B22
_02033AEC:
	cmp r0, #0x1
	bne _02033B22
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_0202822C
	cmp r0, #0x2
	bne _02033B22
	add r0, r6, #0x0
	bl FUN_020239CC
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x8
	bl FUN_020282E8
	add r0, r6, #0x0
	bl FUN_020239BC
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl FUN_020282E8
_02033B22:
	ldr r1, [sp, #0x4]
	mov r0, #0x78
	bl FUN_020219F4
	str r0, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_0202DFFC
	add r1, r0, #0x0
	ldr r0, [sp, #0x10]
	bl FUN_02021E28
	ldr r2, [sp, #0x10]
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02028404
	ldr r0, [sp, #0x10]
	bl FUN_02021A20
	add r0, r6, #0x0
	bl FUN_02023A28
	add r3, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0x7
	bl FUN_020282E8
	ldr r0, [sp, #0x0]
	bl FUN_0202E1BC
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02033B68
FUN_02033B68: ; 0x02033B68
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r2, #0x0
	mov r2, #0x7
	add r6, r3, #0x0
	ldr r1, [sp, #0x10]
	mov r0, #0x1
	lsl r2, r2, #0x6
	add r3, r4, #0x0
	bl FUN_02033D3C
	ldr r1, [sp, #0x10]
	mov r0, #0x1
	add r2, r4, #0x0
	bl FUN_02033D9C
	add r0, r4, #0x0
	mov r1, #0x20
	bl FUN_020169D8
	add r4, r0, #0x0
	ldr r0, _02033BC4 ; =FUN_02033BC8
	add r1, r4, #0x0
	mov r2, #0x5
	bl FUN_0200CA98
	str r0, [r4, #0x18]
	strh r5, [r4, #0xc]
	strh r6, [r4, #0xe]
	mov r1, #0x0
	str r1, [r4, #0x0]
	mov r0, #0x3
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x10]
	str r1, [r4, #0x8]
	strb r0, [r4, #0x10]
	strb r1, [r4, #0x12]
	mov r0, #0x7
	strb r1, [r4, #0x11]
	lsl r0, r0, #0x18
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	pop {r4-r6, pc}
	nop
_02033BC4: .word FUN_02033BC8

	thumb_func_start FUN_02033BC8
FUN_02033BC8: ; 0x02033BC8
	push {r3-r7, lr}
	add r5, r1, #0x0
	ldrb r0, [r5, #0x11]
	cmp r0, #0x1
	beq _02033BD8
	cmp r0, #0x2
	beq _02033BEE
	b _02033C04
_02033BD8:
	ldr r0, _02033CB0 ; =0x04000304
	ldrh r1, [r0, #0x0]
	lsr r0, r0, #0xb
	and r0, r1
	asr r0, r0, #0xf
	cmp r0, #0x1
	bne _02033BEA
	mov r6, #0x1
	b _02033C06
_02033BEA:
	mov r6, #0x2
	b _02033C06
_02033BEE:
	ldr r0, _02033CB0 ; =0x04000304
	ldrh r1, [r0, #0x0]
	lsr r0, r0, #0xb
	and r0, r1
	asr r0, r0, #0xf
	cmp r0, #0x1
	bne _02033C00
	mov r6, #0x2
	b _02033C06
_02033C00:
	mov r6, #0x1
	b _02033C06
_02033C04:
	mov r6, #0x1
_02033C06:
	ldr r4, [r5, #0x4]
	cmp r6, #0x1
	bne _02033C1E
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	ldr r0, _02033CB4 ; =0x00300010
	add r7, r1, #0x0
	and r7, r0
	bl GX_GetBankForOBJ
	b _02033C2C
_02033C1E:
	ldr r0, _02033CB8 ; =0x04001000
	ldr r1, [r0, #0x0]
	ldr r0, _02033CB4 ; =0x00300010
	add r7, r1, #0x0
	and r7, r0
	bl GX_GetBankForSubOBJ
_02033C2C:
	cmp r7, #0x10
	beq _02033C38
	ldr r1, _02033CBC ; =0x00200010
	cmp r7, r1
	beq _02033C54
	b _02033C6C
_02033C38:
	cmp r0, #0x40
	beq _02033C40
	cmp r0, #0x20
	bne _02033C4A
_02033C40:
	mov r0, #0x1f
	lsl r1, r4, #0x2
	lsl r0, r0, #0x4
	add r1, r1, r0
	b _02033C74
_02033C4A:
	mov r0, #0x3f
	lsl r1, r4, #0x2
	lsl r0, r0, #0x4
	add r1, r1, r0
	b _02033C74
_02033C54:
	cmp r0, #0x30
	beq _02033C5C
	cmp r0, #0x50
	bne _02033C64
_02033C5C:
	mov r0, #0x9f
	lsl r0, r0, #0x2
	add r1, r4, r0
	b _02033C74
_02033C64:
	mov r0, #0xff
	lsl r0, r0, #0x2
	add r1, r4, r0
	b _02033C74
_02033C6C:
	mov r0, #0xfe
	lsl r1, r4, #0x1
	lsl r0, r0, #0x2
	add r1, r1, r0
_02033C74:
	cmp r6, #0x1
	bne _02033C7E
	mov r2, #0x7
	lsl r2, r2, #0x18
	b _02033C80
_02033C7E:
	ldr r2, _02033CC0 ; =0x07000400
_02033C80:
	ldrh r3, [r5, #0xe]
	ldrh r0, [r5, #0xc]
	lsl r3, r3, #0x18
	lsr r4, r3, #0x18
	mov r3, #0x1
	lsl r0, r0, #0x17
	lsl r3, r3, #0x1e
	lsr r0, r0, #0x7
	orr r3, r4
	orr r0, r3
	str r0, [r2, #0x0]
	mov r0, #0xe
	lsl r0, r0, #0xc
	orr r0, r1
	strh r0, [r2, #0x4]
	ldr r1, [r5, #0x1c]
	cmp r2, r1
	beq _02033CAE
	ldr r0, _02033CC4 ; =0x40000200
	str r0, [r1, #0x0]
	mov r0, #0x0
	strh r0, [r1, #0x4]
	str r2, [r5, #0x1c]
_02033CAE:
	pop {r3-r7, pc}
	.balign 4
_02033CB0: .word 0x04000304
_02033CB4: .word 0x00300010
_02033CB8: .word 0x04001000
_02033CBC: .word 0x00200010
_02033CC0: .word 0x07000400
_02033CC4: .word 0x40000200

	thumb_func_start FUN_02033CC8
FUN_02033CC8: ; 0x02033CC8
	cmp r1, #0x4
	bge _02033CD2
	str r1, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x8]
_02033CD2:
	bx lr

	thumb_func_start FUN_02033CD4
FUN_02033CD4: ; 0x02033CD4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x18]
	bl FUN_0200CAB4
	mov r0, #0x7
	ldr r2, _02033D00 ; =0x40000200
	lsl r0, r0, #0x18
	str r2, [r0, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x4]
	ldrb r0, [r4, #0x12]
	cmp r0, #0x0
	beq _02033CF6
	ldr r0, _02033D04 ; =0x07000400
	str r2, [r0, #0x0]
	strh r1, [r0, #0x4]
_02033CF6:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	nop
_02033D00: .word 0x40000200
_02033D04: .word 0x07000400

	thumb_func_start FUN_02033D08
FUN_02033D08: ; 0x02033D08
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r2, #0x7
	ldrb r1, [r5, #0x10]
	mov r0, #0x2
	lsl r2, r2, #0x6
	add r3, r6, #0x0
	bl FUN_02033D3C
	ldrb r1, [r5, #0x10]
	mov r0, #0x2
	add r2, r6, #0x0
	bl FUN_02033D9C
	cmp r4, #0x0
	beq _02033D30
	mov r0, #0x1
	b _02033D32
_02033D30:
	mov r0, #0x2
_02033D32:
	strb r0, [r5, #0x11]
	mov r0, #0x1
	strb r0, [r5, #0x12]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02033D3C
FUN_02033D3C: ; 0x02033D3C
	push {r3-r5, lr}
	sub sp, #0x8
	mov r1, #0x96
	add r5, r0, #0x0
	add r0, r3, #0x0
	lsl r1, r1, #0x2
	add r4, r2, #0x0
	bl FUN_020169D8
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02033D92
	ldr r0, _02033D98 ; =0x02105D88
	add r1, sp, #0x4
	bl FUN_020161F8
	mov r1, #0x96
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x2
	bl DC_FlushRange
	ldr r0, [sp, #0x4]
	add r1, sp, #0x0
	bl FUN_020B0138
	cmp r5, #0x1
	bne _02033D80
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl GX_LoadOBJPltt
	b _02033D8C
_02033D80:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl GXS_LoadOBJPltt
_02033D8C:
	ldr r0, [sp, #0x4]
	bl FUN_02016A18
_02033D92:
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_02033D98: .word 0x02105D88

	thumb_func_start FUN_02033D9C
FUN_02033D9C: ; 0x02033D9C
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	mov r1, #0x96
	add r5, r0, #0x0
	add r0, r2, #0x0
	lsl r1, r1, #0x2
	bl FUN_020169D8
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02033E58
	cmp r4, #0x0
	add r1, sp, #0x4
	beq _02033DC2
	ldr r0, _02033E5C ; =0x02105D98
	bl FUN_020161F8
	b _02033DC8
_02033DC2:
	ldr r0, _02033E60 ; =0x02105DA8
	bl FUN_020161F8
_02033DC8:
	mov r1, #0x96
	ldr r0, [sp, #0x4]
	lsl r1, r1, #0x2
	bl DC_FlushRange
	ldr r0, [sp, #0x4]
	add r1, sp, #0x0
	bl FUN_020B0088
	cmp r5, #0x1
	bne _02033DF0
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	ldr r0, _02033E64 ; =0x00300010
	add r4, r1, #0x0
	and r4, r0
	bl GX_GetBankForOBJ
	b _02033E00
_02033DF0:
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	ldr r0, _02033E64 ; =0x00300010
	add r4, r1, #0x0
	and r4, r0
	bl GX_GetBankForOBJ
_02033E00:
	cmp r4, #0x10
	beq _02033E0C
	ldr r1, _02033E68 ; =0x00200010
	cmp r4, r1
	beq _02033E20
	b _02033E30
_02033E0C:
	cmp r0, #0x40
	beq _02033E14
	cmp r0, #0x20
	bne _02033E1A
_02033E14:
	mov r1, #0x3e
	lsl r1, r1, #0x8
	b _02033E34
_02033E1A:
	mov r1, #0x7e
	lsl r1, r1, #0x8
	b _02033E34
_02033E20:
	cmp r0, #0x30
	beq _02033E28
	cmp r0, #0x50
	bne _02033E2C
_02033E28:
	ldr r1, _02033E6C ; =0x00013E00
	b _02033E34
_02033E2C:
	ldr r1, _02033E70 ; =0x0001FE00
	b _02033E34
_02033E30:
	mov r1, #0xfe
	lsl r1, r1, #0x8
_02033E34:
	cmp r5, #0x1
	bne _02033E46
	ldr r0, [sp, #0x0]
	mov r2, #0x2
	ldr r0, [r0, #0x14]
	lsl r2, r2, #0x8
	bl GX_LoadOBJ
	b _02033E52
_02033E46:
	ldr r0, [sp, #0x0]
	mov r2, #0x2
	ldr r0, [r0, #0x14]
	lsl r2, r2, #0x8
	bl GXS_LoadOBJ
_02033E52:
	ldr r0, [sp, #0x4]
	bl FUN_02016A18
_02033E58:
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
_02033E5C: .word 0x02105D98
_02033E60: .word 0x02105DA8
_02033E64: .word 0x00300010
_02033E68: .word 0x00200010
_02033E6C: .word 0x00013E00
_02033E70: .word 0x0001FE00

	thumb_func_start FUN_02033E74
FUN_02033E74: ; 0x02033E74
	push {r4, lr}
	mov r4, #0x0
	bl FUN_02033590
	cmp r0, #0x0
	beq _02033E82
	mov r4, #0x1
_02033E82:
	mov r0, #0xf0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02033E90
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02033E90
FUN_02033E90: ; 0x02033E90
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0202E4DC
	cmp r0, #0x0
	beq _02033EC4
	ldr r0, _02033EC8 ; =0x021C5A04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033EAE
	bl FUN_02033ED0
_02033EAE:
	ldr r0, _02033ECC ; =0x02105D74
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x0
	mov r1, #0x5b
	add r2, r5, #0x0
	add r3, r6, #0x0
	bl FUN_02033B68
	ldr r1, _02033EC8 ; =0x021C5A04
	str r0, [r1, #0x0]
_02033EC4:
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02033EC8: .word 0x021C5A04
_02033ECC: .word 0x02105D74

	thumb_func_start FUN_02033ED0
FUN_02033ED0: ; 0x02033ED0
	push {r3, lr}
	ldr r0, _02033EE8 ; =0x021C5A04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033EE4
	bl FUN_02033CD4
	ldr r0, _02033EE8 ; =0x021C5A04
	mov r1, #0x0
	str r1, [r0, #0x0]
_02033EE4:
	pop {r3, pc}
	nop
_02033EE8: .word 0x021C5A04

	thumb_func_start FUN_02033EEC
FUN_02033EEC: ; 0x02033EEC
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, _02033F00 ; =0x021C5A04
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033EFC
	bl FUN_02033CC8
_02033EFC:
	pop {r3, pc}
	nop
_02033F00: .word 0x021C5A04

	thumb_func_start FUN_02033F04
FUN_02033F04: ; 0x02033F04
	push {r3, lr}
	add r3, r0, #0x0
	ldr r0, _02033F1C ; =0x021C5A04
	add r2, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033F18
	add r1, r3, #0x0
	bl FUN_02033D08
_02033F18:
	pop {r3, pc}
	nop
_02033F1C: .word 0x021C5A04

	thumb_func_start FUN_02033F20
FUN_02033F20: ; 0x02033F20
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	beq _02033F40
	bl FUN_02030F20
	cmp r0, #0x1
	bgt _02033F3A
	bl FUN_02033590
	cmp r0, #0x0
	beq _02033F4C
_02033F3A:
	bl FUN_02033E74
	pop {r3, pc}
_02033F40:
	bl FUN_02033590
	cmp r0, #0x0
	beq _02033F4C
	bl FUN_02033E74
_02033F4C:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02033F50
FUN_02033F50: ; 0x02033F50
	ldr r3, _02033F64 ; =0x027E0000
	ldr r1, _02033F68 ; =0x00003FF8
	mov r0, #0x1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	ldr r3, _02033F6C ; =MI_WaitDma
	mov r0, #0x3
	bx r3
	nop
_02033F64: .word 0x027E0000
_02033F68: .word 0x00003FF8
_02033F6C: .word MI_WaitDma

	thumb_func_start FUN_02033F70
FUN_02033F70: ; 0x02033F70
	push {r3-r7, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	str r2, [sp, #0xc]
	cmp r1, #0x4
	bhi _02033F92
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02033F88: ; jump table (using 16-bit offset)
	.short _02033F92 - _02033F88 - 2; case 0
	.short _02033F96 - _02033F88 - 2; case 1
	.short _02033F9A - _02033F88 - 2; case 2
	.short _02033F9E - _02033F88 - 2; case 3
	.short _02033FA2 - _02033F88 - 2; case 4
_02033F92:
	mov r5, #0x1
	b _02033FA4
_02033F96:
	mov r5, #0x2
	b _02033FA4
_02033F9A:
	mov r5, #0x3
	b _02033FA4
_02033F9E:
	mov r5, #0x4
	b _02033FA4
_02033FA2:
	mov r5, #0x5
_02033FA4:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	bl OS_DisableIrqMask
	ldr r1, _02034154 ; =FUN_02033F50
	mov r0, #0x1
	bl OS_SetIrqFunction
	mov r0, #0x1
	bl OS_EnableIrqMask
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02034158 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0203415C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _02034160 ; =0x021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _02034164 ; =0x04000050
	mov r1, #0x0
	strh r1, [r3, #0x0]
	ldr r0, _02034168 ; =0x04001050
	sub r3, #0x50
	strh r1, [r0, #0x0]
	ldr r2, [r3, #0x0]
	ldr r1, _0203416C ; =0xFFFF1FFF
	sub r0, #0x50
	and r2, r1
	str r2, [r3, #0x0]
	ldr r2, [r0, #0x0]
	and r1, r2
	str r1, [r0, #0x0]
	ldr r0, _02034170 ; =0x020EECD0
	bl FUN_0201E66C
	add r0, r4, #0x0
	bl FUN_02016B94
	add r6, r0, #0x0
	ldr r0, _02034174 ; =0x020EECA4
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r2, _02034178 ; =0x020EECB4
	add r0, r6, #0x0
	add r3, r1, #0x0
	bl FUN_02016C18
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r2, _0203417C ; =0x000001F7
	add r0, r6, #0x0
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _02034180 ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _02034180 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0xc8
	add r3, r4, #0x0
	bl FUN_0200A86C
	str r0, [sp, #0x10]
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	add r7, r0, #0x0
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	str r0, [sp, #0x14]
	bl FUN_0201BD5C
	add r0, r4, #0x0
	bl FUN_0200AA80
	add r4, r0, #0x0
	ldr r2, _02034184 ; =0x020EEC9C
	add r0, r6, #0x0
	add r1, sp, #0x18
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x18
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _0203417C ; =0x000001F7
	add r0, sp, #0x18
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r2, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x0
	mov r3, #0x5
	bl FUN_0200AD38
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x14]
	add r1, r5, #0x0
	bl FUN_0200A8E0
	ldr r2, [sp, #0x14]
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_0200B7B8
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0x18
	add r2, r7, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r7, #0x0
	bl FUN_02021A20
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	add r0, sp, #0x18
	bl FUN_02019178
	ldr r0, [sp, #0x10]
	bl FUN_0200A8B8
	add r0, r4, #0x0
	bl FUN_0200AB18
	add r0, r6, #0x0
	bl FUN_02016A18
	add sp, #0x28
	pop {r3-r7, pc}
	nop
_02034154: .word FUN_02033F50
_02034158: .word 0xFFFFE0FF
_0203415C: .word 0x04001000
_02034160: .word 0x021C4918
_02034164: .word 0x04000050
_02034168: .word 0x04001050
_0203416C: .word 0xFFFF1FFF
_02034170: .word 0x020EECD0
_02034174: .word 0x020EECA4
_02034178: .word 0x020EECB4
_0203417C: .word 0x000001F7
_02034180: .word 0x00006C21
_02034184: .word 0x020EEC9C

	thumb_func_start FUN_02034188
FUN_02034188: ; 0x02034188
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	bl FUN_02015EF4
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02034368 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0203436C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _02034370 ; =0x021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _02034374 ; =0x04000050
	mov r0, #0x0
	strh r0, [r3, #0x0]
	ldr r2, _02034378 ; =0x04001050
	sub r3, #0x50
	strh r0, [r2, #0x0]
	ldr r1, [r3, #0x0]
	ldr r0, _0203437C ; =0xFFFF1FFF
	sub r2, #0x50
	and r1, r0
	str r1, [r3, #0x0]
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r0, _02034380 ; =0x020EED2C
	bl FUN_0201E66C
	add r0, r4, #0x0
	bl FUN_02016B94
	str r0, [sp, #0x10]
	ldr r0, _02034384 ; =0x020EED00
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r0, [sp, #0x10]
	ldr r2, _02034388 ; =0x020EED10
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r2, _0203438C ; =0x000001F7
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _02034390 ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _02034390 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	ldr r2, _02034394 ; =0x00000265
	mov r0, #0x1
	mov r1, #0x1a
	add r3, r4, #0x0
	bl FUN_0200A86C
	str r0, [sp, #0xc]
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r0, [sp, #0x10]
	ldr r2, _02034398 ; =0x020EECF8
	add r1, sp, #0x14
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x14
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _0203438C ; =0x000001F7
	add r0, sp, #0x14
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	ldr r0, [sp, #0xc]
	mov r1, #0xf
	add r2, r4, #0x0
	bl FUN_0200A8E0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0x14
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl FUN_02021A20
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	ldr r4, _0203439C ; =0x04000130
	ldr r6, _020343A0 ; =0x027FFFA8
	mov r7, #0x1
_020342E4:
	ldrh r1, [r4, #0x0]
	ldrh r0, [r6, #0x0]
	orr r1, r0
	ldr r0, _020343A4 ; =0x00002FFF
	eor r1, r0
	and r0, r1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	bl FUN_02000FE8
	add r0, r5, #0x0
	tst r0, r7
	bne _02034308
	mov r0, #0x1
	add r1, r0, #0x0
	bl OS_WaitIrq
	b _020342E4
_02034308:
	add r0, sp, #0x14
	bl FUN_02019178
	ldr r0, [sp, #0xc]
	bl FUN_0200A8B8
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0201797C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x5
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x6
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x7
	mov r1, #0x0
	bl FUN_0201797C
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	bl FUN_020178A0
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_02034368: .word 0xFFFFE0FF
_0203436C: .word 0x04001000
_02034370: .word 0x021C4918
_02034374: .word 0x04000050
_02034378: .word 0x04001050
_0203437C: .word 0xFFFF1FFF
_02034380: .word 0x020EED2C
_02034384: .word 0x020EED00
_02034388: .word 0x020EED10
_0203438C: .word 0x000001F7
_02034390: .word 0x00006C21
_02034394: .word 0x00000265
_02034398: .word 0x020EECF8
_0203439C: .word 0x04000130
_020343A0: .word 0x027FFFA8
_020343A4: .word 0x00002FFF

	thumb_func_start FUN_020343A8
FUN_020343A8: ; 0x020343A8
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x0
	strb r2, [r4, #0x1]
	mov r0, #0xe1
	ldr r7, _02034488 ; =0x0000070A
	ldr r6, _0203448C ; =0x00000A8E
	mov r12, r1
	strb r2, [r4, #0x0]
	add r3, r4, #0x0
	add r5, r2, #0x0
	lsl r0, r0, #0x2
_020343C4:
	add r1, r4, r2
	strh r5, [r3, #0x2]
	strb r5, [r1, r7]
	strh r5, [r3, r6]
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, r0
	blt _020343C4
	ldr r0, _02034490 ; =0x00001196
	mov r2, #0x0
_020343D8:
	add r1, r4, r5
	add r5, r5, #0x1
	strb r2, [r1, r0]
	cmp r5, #0x10
	blt _020343D8
	mov r0, #0x29
	mov r1, r12
	mov r2, #0xb
	bl FUN_02006528
	add r6, r0, #0x0
	ldrb r0, [r6, #0x0]
	add r5, r6, #0x5
	strb r0, [r4, #0x1]
	ldrb r0, [r6, #0x1]
	strb r0, [r4, #0x0]
	ldrb r0, [r6, #0x2]
	str r0, [sp, #0x8]
	ldrb r0, [r6, #0x3]
	str r0, [sp, #0x4]
	ldrb r7, [r6, #0x4]
	cmp r7, #0x10
	bls _0203440A
	bl ErrorHandling
_0203440A:
	ldr r1, _02034490 ; =0x00001196
	add r0, r5, #0x0
	add r1, r4, r1
	add r2, r7, #0x0
	bl MI_CpuCopy8
	ldr r0, [sp, #0x8]
	add r5, r5, r7
	cmp r0, #0x0
	beq _0203443A
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x2
	mul r2, r3
	lsl r2, r2, #0x1
	bl MI_CpuCopy8
	ldrb r1, [r4, #0x1]
	ldrb r0, [r4, #0x0]
	mul r0, r1
	lsl r0, r0, #0x1
	add r5, r5, r0
	b _0203444E
_0203443A:
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	ldr r0, [sp, #0x0]
	add r1, r4, #0x2
	lsl r0, r0, #0x10
	mul r2, r3
	lsr r0, r0, #0x10
	lsl r2, r2, #0x1
	bl MIi_CpuClear16
_0203444E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0203446C
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	ldr r1, _02034488 ; =0x0000070A
	add r0, r5, #0x0
	add r1, r4, r1
	mul r2, r3
	bl MI_CpuCopy8
	ldrb r1, [r4, #0x1]
	ldrb r0, [r4, #0x0]
	mul r0, r1
	add r5, r5, r0
_0203446C:
	ldrb r3, [r4, #0x1]
	ldrb r2, [r4, #0x0]
	ldr r1, _0203448C ; =0x00000A8E
	add r0, r5, #0x0
	mul r2, r3
	add r1, r4, r1
	lsl r2, r2, #0x1
	bl MI_CpuCopy8
	add r0, r6, #0x0
	bl FUN_02016A18
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02034488: .word 0x0000070A
_0203448C: .word 0x00000A8E
_02034490: .word 0x00001196

	thumb_func_start FUN_02034494
FUN_02034494: ; 0x02034494
	push {r3, lr}
	ldr r1, _020344A8 ; =0x000011AA
	mov r0, #0xb
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	pop {r3, pc}
	.balign 4
_020344A8: .word 0x000011AA

	thumb_func_start FUN_020344AC
FUN_020344AC: ; 0x020344AC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0203474C
	add r6, r0, #0x0
	add r0, r4, #0x4
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_020343A8
	strb r6, [r4, #0x2]
	ldrb r0, [r4, #0x4]
	strb r0, [r4, #0x1]
	ldrb r0, [r4, #0x5]
	strb r0, [r4, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020344D0
FUN_020344D0: ; 0x020344D0
	ldr r3, _020344D4 ; =FUN_02016A18
	bx r3
	.balign 4
_020344D4: .word FUN_02016A18

	thumb_func_start FUN_020344D8
FUN_020344D8: ; 0x020344D8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldrb r1, [r4, #0x0]
	ldrb r0, [r4, #0x1]
	mul r0, r1
	cmp r5, r0
	blt _020344EC
	bl ErrorHandling
_020344EC:
	lsl r0, r5, #0x1
	add r1, r4, r0
	ldr r0, _020344F8 ; =0x00000A92
	ldrh r0, [r1, r0]
	pop {r3-r5, pc}
	nop
_020344F8: .word 0x00000A92

	thumb_func_start FUN_020344FC
FUN_020344FC: ; 0x020344FC
	push {r4, lr}
	add r4, r0, #0x0
	bne _02034506
	bl ErrorHandling
_02034506:
	ldrb r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203450C
FUN_0203450C: ; 0x0203450C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02034516
	bl ErrorHandling
_02034516:
	ldrb r0, [r4, #0x1]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0203451C
FUN_0203451C: ; 0x0203451C
	push {r3-r7, lr}
	add r7, r0, #0x0
	ldrb r0, [r7, #0x1]
	add r5, r1, #0x0
	add r4, r2, #0x0
	ldrb r6, [r7, #0x0]
	str r0, [sp, #0x0]
	cmp r5, #0x0
	blt _02034532
	cmp r5, r6
	blt _02034536
_02034532:
	bl ErrorHandling
_02034536:
	cmp r4, #0x0
	blt _02034540
	ldr r0, [sp, #0x0]
	cmp r4, r0
	blt _02034544
_02034540:
	bl ErrorHandling
_02034544:
	add r0, r4, #0x0
	mul r0, r6
	add r0, r5, r0
	lsl r0, r0, #0x1
	add r0, r7, r0
	ldrh r0, [r0, #0x6]
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02034554
FUN_02034554: ; 0x02034554
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldrb r1, [r5, #0x0]
	ldrb r0, [r5, #0x1]
	mul r0, r1
	cmp r4, #0x0
	blt _02034568
	cmp r4, r0
	blt _0203456C
_02034568:
	bl ErrorHandling
_0203456C:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, #0x6]
	pop {r3-r5, pc}

	thumb_func_start FUN_02034574
FUN_02034574: ; 0x02034574
	ldrb r0, [r0, #0x2]
	bx lr

	thumb_func_start FUN_02034578
FUN_02034578: ; 0x02034578
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x10]
	add r4, r2, #0x0
	add r6, r3, #0x0
	cmp r4, r0
	blt _0203458A
	bl ErrorHandling
_0203458A:
	ldr r0, [sp, #0x10]
	mul r0, r6
	add r4, r4, r0
	mov r0, #0xe1
	lsl r0, r0, #0x2
	cmp r4, r0
	blt _0203459C
	bl ErrorHandling
_0203459C:
	ldr r0, _020345A4 ; =0x0000070E
	add r1, r5, r4
	ldrb r0, [r1, r0]
	pop {r4-r6, pc}
	.balign 4
_020345A4: .word 0x0000070E

	thumb_func_start FUN_020345A8
FUN_020345A8: ; 0x020345A8
	push {r3-r5, lr}
	ldr r1, _020345D8 ; =0x00000708
	add r4, r0, #0x0
	bl FUN_02016998
	add r5, r0, #0x0
	mov r0, #0x29
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02006528
	add r4, r0, #0x0
	ldrb r1, [r4, #0x4]
	add r0, r4, #0x5
	ldr r2, _020345D8 ; =0x00000708
	add r0, r0, r1
	add r1, r5, #0x0
	bl MI_CpuCopy8
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_020345D8: .word 0x00000708

	thumb_func_start FUN_020345DC
FUN_020345DC: ; 0x020345DC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020345E6
	bl ErrorHandling
_020345E6:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020345F0
FUN_020345F0: ; 0x020345F0
	mov r3, #0x1e
	mul r3, r2
	add r1, r1, r3
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
	bx lr

	thumb_func_start FUN_020345FC
FUN_020345FC: ; 0x020345FC
	push {r3-r5, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1c8
	add r3, r0, #0x0
	add r5, r1, #0x0
	lsl r1, r3, #0x10
	add r4, r2, #0x0
	add r0, sp, #0x0
	lsr r1, r1, #0x10
	mov r2, #0x0
	bl FUN_020343A8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	cmp r5, r0
	blt _0203462E
	bl ErrorHandling
_0203462E:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r4, r0
	blt _0203463A
	bl ErrorHandling
_0203463A:
	add r0, sp, #0x0
	ldrb r0, [r0, #0x1]
	mul r0, r4
	add r0, r5, r0
	lsl r1, r0, #0x1
	add r0, sp, #0x0
	add r0, #0x2
	ldrh r0, [r0, r1]
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1c8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034660
FUN_02034660: ; 0x02034660
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bne _0203466C
	bl ErrorHandling
_0203466C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020344D8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034678
FUN_02034678: ; 0x02034678
	push {r4-r7}
	ldr r1, _020346C4 ; =0x00000A92
	ldrb r7, [r0, #0x0]
	add r2, r0, r1
	ldr r1, _020346C8 ; =0x0000070E
	add r1, r0, r1
	ldrb r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020346BE
	mov r0, #0x15
	add r6, r7, #0x0
	mul r6, r0
	add r5, r6, #0x0
	add r5, #0x17
	mov r4, #0xb0
	lsl r0, r5, #0x1
	add r6, #0x18
	strh r4, [r2, r0]
	lsl r0, r6, #0x1
	strh r4, [r2, r0]
	mov r0, #0x16
	add r3, r7, #0x0
	mul r3, r0
	add r0, r3, #0x0
	add r0, #0x17
	lsl r7, r0, #0x1
	add r3, #0x18
	strh r4, [r2, r7]
	lsl r7, r3, #0x1
	strh r4, [r2, r7]
	mov r2, #0x2
	strb r2, [r1, r5]
	strb r2, [r1, r6]
	strb r2, [r1, r0]
	strb r2, [r1, r3]
_020346BE:
	pop {r4-r7}
	bx lr
	nop
_020346C4: .word 0x00000A92
_020346C8: .word 0x0000070E

	thumb_func_start FUN_020346CC
FUN_020346CC: ; 0x020346CC
	push {r3-r4}
	ldr r1, _0203470C ; =0x00000A92
	add r2, r0, r1
	ldrb r1, [r0, #0x0]
	ldrb r0, [r0, #0x2]
	cmp r0, #0x0
	bne _02034706
	mov r0, #0xf
	mul r0, r1
	add r0, #0x1c
	mov r3, #0x77
	lsl r0, r0, #0x1
	strh r3, [r2, r0]
	lsl r0, r1, #0x4
	add r3, r0, #0x0
	add r3, #0x1b
	mov r4, #0x78
	lsl r3, r3, #0x1
	strh r4, [r2, r3]
	add r3, r0, #0x0
	add r3, #0x1c
	add r0, r1, r0
	add r0, #0x1b
	mov r4, #0x79
	lsl r3, r3, #0x1
	strh r4, [r2, r3]
	mov r3, #0x7a
	lsl r0, r0, #0x1
	strh r3, [r2, r0]
_02034706:
	pop {r3-r4}
	bx lr
	nop
_0203470C: .word 0x00000A92

	thumb_func_start FUN_02034710
FUN_02034710: ; 0x02034710
	push {r3, lr}
	ldr r1, _02034720 ; =0x0000022F
	cmp r0, r1
	blo _0203471E
	bl ErrorHandling
	mov r0, #0x3
_0203471E:
	pop {r3, pc}
	.balign 4
_02034720: .word 0x0000022F

	thumb_func_start FUN_02034724
FUN_02034724: ; 0x02034724
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034734 ; =0x020EEDBC
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034734: .word 0x020EEDBC

	thumb_func_start FUN_02034738
FUN_02034738: ; 0x02034738
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034748 ; =0x020EEDBD
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034748: .word 0x020EEDBD

	thumb_func_start FUN_0203474C
FUN_0203474C: ; 0x0203474C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _0203476C ; =0x020EEDBE
	ldrh r0, [r0, r1]
	cmp r0, #0x16
	bne _02034768
	ldr r1, _02034770 ; =0x020ECAC0
	ldrb r1, [r1, #0x0]
	cmp r1, #0xb
	bne _02034768
	mov r0, #0x17
_02034768:
	pop {r3, pc}
	nop
_0203476C: .word 0x020EEDBE
_02034770: .word 0x020ECAC0

	thumb_func_start FUN_02034774
FUN_02034774: ; 0x02034774
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034784 ; =0x020EEDC4
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034784: .word 0x020EEDC4

	thumb_func_start FUN_02034788
FUN_02034788: ; 0x02034788
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034798 ; =0x020EEDC0
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034798: .word 0x020EEDC0

	thumb_func_start FUN_0203479C
FUN_0203479C: ; 0x0203479C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347AC ; =0x020EEDC2
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020347AC: .word 0x020EEDC2

	thumb_func_start FUN_020347B0
FUN_020347B0: ; 0x020347B0
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347C0 ; =0x020EEDC6
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020347C0: .word 0x020EEDC6

	thumb_func_start FUN_020347C4
FUN_020347C4: ; 0x020347C4
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347D4 ; =0x020EEDC8
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020347D4: .word 0x020EEDC8

	thumb_func_start FUN_020347D8
FUN_020347D8: ; 0x020347D8
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347F4 ; =0x020EEDCA
	ldrh r1, [r0, r1]
	ldr r0, _020347F8 ; =0x0000FFFF
	cmp r1, r0
	beq _020347F0
	mov r0, #0x1
	pop {r3, pc}
_020347F0:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_020347F4: .word 0x020EEDCA
_020347F8: .word 0x0000FFFF

	thumb_func_start FUN_020347FC
FUN_020347FC: ; 0x020347FC
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _0203480C ; =0x020EEDCA
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0203480C: .word 0x020EEDCA

	thumb_func_start FUN_02034810
FUN_02034810: ; 0x02034810
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034820 ; =0x020EEDCC
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034820: .word 0x020EEDCC

	thumb_func_start FUN_02034824
FUN_02034824: ; 0x02034824
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034834 ; =0x020EEDCE
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034834: .word 0x020EEDCE

	thumb_func_start FUN_02034838
FUN_02034838: ; 0x02034838
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034848 ; =0x020EEDD0
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034848: .word 0x020EEDD0

	thumb_func_start FUN_0203484C
FUN_0203484C: ; 0x0203484C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _0203485C ; =0x020EEDD1
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0203485C: .word 0x020EEDD1

	thumb_func_start FUN_02034860
FUN_02034860: ; 0x02034860
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034878 ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	pop {r3, pc}
	nop
_02034878: .word 0x020EEDBC

	thumb_func_start FUN_0203487C
FUN_0203487C: ; 0x0203487C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034894 ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	pop {r3, pc}
	nop
_02034894: .word 0x020EEDBC

	thumb_func_start FUN_02034898
FUN_02034898: ; 0x02034898
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020348B0 ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	pop {r3, pc}
	nop
_020348B0: .word 0x020EEDBC

	thumb_func_start FUN_020348B4
FUN_020348B4: ; 0x020348B4
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020348CC ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	pop {r3, pc}
	nop
_020348CC: .word 0x020EEDBC

	thumb_func_start FUN_020348D0
FUN_020348D0: ; 0x020348D0
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020348E0 ; =0x020EEDD2
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020348E0: .word 0x020EEDD2

	thumb_func_start FUN_020348E4
FUN_020348E4: ; 0x020348E4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02034898
	cmp r0, #0x0
	bne _020348F4
	mov r0, #0x0
	pop {r4, pc}
_020348F4:
	add r0, r4, #0x0
	bl FUN_020348D0
	cmp r0, #0x1
	beq _02034902
	mov r0, #0x1
	pop {r4, pc}
_02034902:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034908
FUN_02034908: ; 0x02034908
	push {r3, lr}
	bl FUN_0203474C
	cmp r0, #0x0
	bne _02034916
	mov r0, #0x1
	pop {r3, pc}
_02034916:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203491C
FUN_0203491C: ; 0x0203491C
	push {r3, lr}
	bl FUN_020348D0
	cmp r0, #0x5
	bne _0203492A
	mov r0, #0x1
	pop {r3, pc}
_0203492A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02034930
FUN_02034930: ; 0x02034930
	push {r3, lr}
	bl FUN_020348D0
	cmp r0, #0x3
	bne _0203493E
	mov r0, #0x1
	pop {r3, pc}
_0203493E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02034944
FUN_02034944: ; 0x02034944
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020348D0
	cmp r0, #0x4
	beq _0203495A
	add r0, r4, #0x0
	bl FUN_020348D0
	cmp r0, #0x5
	bne _0203495E
_0203495A:
	mov r0, #0x1
	pop {r4, pc}
_0203495E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034964
FUN_02034964: ; 0x02034964
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020348D0
	cmp r0, #0x1
	beq _0203497A
	add r0, r4, #0x0
	bl FUN_020348D0
	cmp r0, #0x2
	bne _0203497E
_0203497A:
	mov r0, #0x1
	pop {r4, pc}
_0203497E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034984
FUN_02034984: ; 0x02034984
	push {r3, lr}
	bl FUN_0203491C
	cmp r0, #0x0
	beq _02034992
	mov r0, #0x1
	pop {r3, pc}
_02034992:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02034998
FUN_02034998: ; 0x02034998
	ldr r1, _020349A8 ; =0x000001D2
	cmp r0, r1
	bne _020349A2
	mov r0, #0x1
	bx lr
_020349A2:
	mov r0, #0x0
	bx lr
	nop
_020349A8: .word 0x000001D2

	thumb_func_start FUN_020349AC
FUN_020349AC: ; 0x020349AC
	cmp r0, #0xdb
	bne _020349B4
	mov r0, #0x1
	bx lr
_020349B4:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020349B8
FUN_020349B8: ; 0x020349B8
	ldr r1, _020349C8 ; =0x0000011F
	cmp r0, r1
	bne _020349C2
	mov r0, #0x1
	bx lr
_020349C2:
	mov r0, #0x0
	bx lr
	nop
_020349C8: .word 0x0000011F

	thumb_func_start FUN_020349CC
FUN_020349CC: ; 0x020349CC
	cmp r0, #0xfd
	bne _020349D4
	mov r0, #0x1
	bx lr
_020349D4:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020349D8
FUN_020349D8: ; 0x020349D8
	cmp r0, #0xdc
	bne _020349E0
	mov r0, #0x1
	bx lr
_020349E0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020349E4
FUN_020349E4: ; 0x020349E4
	ldr r3, _02034A00 ; =0x020EED54
	mov r2, #0x0
_020349E8:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _020349F2
	mov r0, #0x1
	bx lr
_020349F2:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x12
	blo _020349E8
	mov r0, #0x0
	bx lr
	nop
_02034A00: .word 0x020EED54

	thumb_func_start FUN_02034A04
FUN_02034A04: ; 0x02034A04
	ldr r3, _02034A24 ; =0x020EED78
	mov r2, #0x0
_02034A08:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _02034A18
	add r0, r2, #0x1
	lsl r1, r0, #0x1
	ldr r0, _02034A24 ; =0x020EED78
	ldrh r0, [r0, r1]
	bx lr
_02034A18:
	add r2, r2, #0x2
	add r3, r3, #0x4
	cmp r2, #0x22
	blo _02034A08
	mov r0, #0x0
	bx lr
	.balign 4
_02034A24: .word 0x020EED78

	thumb_func_start FUN_02034A28
FUN_02034A28: ; 0x02034A28
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	add r4, r1, #0x0
	cmp r0, #0x0
	beq _02034A38
	bl ErrorHandling
_02034A38:
	ldr r1, _02034A44 ; =0x00000AC8
	add r0, r4, #0x0
	bl FUN_02016998
	str r0, [r5, #0x14]
	pop {r3-r5, pc}
	.balign 4
_02034A44: .word 0x00000AC8

	thumb_func_start FUN_02034A48
FUN_02034A48: ; 0x02034A48
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02034A56
	bl ErrorHandling
_02034A56:
	ldr r0, [r4, #0x14]
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034A60
FUN_02034A60: ; 0x02034A60
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	add r4, r1, #0x0
	cmp r0, #0x0
	bne _02034A70
	bl ErrorHandling
_02034A70:
	ldr r0, [r5, #0x14]
	add r1, r4, #0x0
	bl FUN_02034A98
	ldr r0, [r5, #0x14]
	bl FUN_02034C50
	mov r0, #0x92
	ldr r1, [r5, #0x14]
	lsl r0, r0, #0x4
	add r0, r1, r0
	add r1, r4, #0x0
	bl FUN_02034CB4
	ldr r0, [r5, #0x14]
	add r1, r4, #0x0
	bl FUN_02034CEC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034A98
FUN_02034A98: ; 0x02034A98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02034810
	add r4, r0, #0x0
	mov r0, #0x20
	add r1, r4, #0x0
	bl LoadFromNARC_7
	mov r1, #0x2
	lsl r1, r1, #0xa
	cmp r0, r1
	blo _02034AB8
	bl ErrorHandling
_02034AB8:
	add r5, #0x20
	add r0, r5, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl LoadFromNARC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034AC8
FUN_02034AC8: ; 0x02034AC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x14]
	ldr r4, [r0, #0x4]
	cmp r0, #0x0
	bne _02034AD8
	bl ErrorHandling
_02034AD8:
	cmp r4, #0x0
	beq _02034AEC
	ldr r1, [r5, #0x1c]
	ldr r3, [r5, #0x14]
	ldr r0, [r5, #0x34]
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x14]
	add r2, r4, #0x0
	bl FUN_02057BAC
_02034AEC:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02034AF0
FUN_02034AF0: ; 0x02034AF0
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x10]
	bx lr
	.balign 4

	thumb_func_start FUN_02034AF8
FUN_02034AF8: ; 0x02034AF8
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034B00
FUN_02034B00: ; 0x02034B00
	ldr r2, [r0, #0x14]
	ldr r0, [r2, #0x8]
	cmp r1, r0
	blo _02034B0C
	mov r0, #0x0
	bx lr
_02034B0C:
	mov r0, #0xc
	ldr r2, [r2, #0x18]
	mul r0, r1
	add r0, r2, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02034B18
FUN_02034B18: ; 0x02034B18
	push {r4-r7}
	ldr r5, [r0, #0x14]
	mov r3, #0x0
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bls _02034B4A
	ldr r6, [r5, #0x18]
	add r4, r3, #0x0
	add r0, r6, #0x0
_02034B2A:
	ldrh r7, [r0, #0x0]
	cmp r1, r7
	bne _02034B3E
	add r7, r6, r4
	ldrh r7, [r7, #0x2]
	cmp r2, r7
	bne _02034B3E
	add r0, r3, #0x0
	pop {r4-r7}
	bx lr
_02034B3E:
	ldr r7, [r5, #0x8]
	add r3, r3, #0x1
	add r0, #0xc
	add r4, #0xc
	cmp r3, r7
	blo _02034B2A
_02034B4A:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02034B54
FUN_02034B54: ; 0x02034B54
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_02034B5C
FUN_02034B5C: ; 0x02034B5C
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x1c]
	bx lr
	.balign 4

	thumb_func_start FUN_02034B64
FUN_02034B64: ; 0x02034B64
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_02034B6C
FUN_02034B6C: ; 0x02034B6C
	ldr r0, [r0, #0x14]
	ldr r0, [r0, #0x14]
	bx lr
	.balign 4

	thumb_func_start FUN_02034B74
FUN_02034B74: ; 0x02034B74
	push {r3-r7, lr}
	ldr r0, [r0, #0x14]
	add r4, r1, #0x0
	ldr r5, [r0, #0x4]
	add r7, r2, #0x0
	add r1, r3, #0x0
	mov r2, #0x0
	ldr r3, [r0, #0x14]
	cmp r5, #0x0
	bls _02034BA4
	add r6, r3, #0x0
_02034B8A:
	ldrh r0, [r6, #0x0]
	cmp r4, r0
	bne _02034B9C
	lsl r0, r2, #0x5
	add r0, r3, r0
	strh r7, [r0, #0x18]
	strh r1, [r0, #0x1a]
	mov r0, #0x1
	pop {r3-r7, pc}
_02034B9C:
	add r2, r2, #0x1
	add r6, #0x20
	cmp r2, r5
	blo _02034B8A
_02034BA4:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02034BAC
FUN_02034BAC: ; 0x02034BAC
	push {r4-r6, lr}
	ldr r0, [r0, #0x14]
	mov r3, #0x0
	ldr r5, [r0, #0x4]
	ldr r4, [r0, #0x14]
	cmp r5, #0x0
	bls _02034BD4
	add r6, r4, #0x0
_02034BBC:
	ldrh r0, [r6, #0x0]
	cmp r1, r0
	bne _02034BCC
	lsl r0, r3, #0x5
	add r0, r4, r0
	strh r2, [r0, #0xc]
	mov r0, #0x1
	pop {r4-r6, pc}
_02034BCC:
	add r3, r3, #0x1
	add r6, #0x20
	cmp r3, r5
	blo _02034BBC
_02034BD4:
	bl ErrorHandling
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02034BDC
FUN_02034BDC: ; 0x02034BDC
	push {r4-r6, lr}
	ldr r0, [r0, #0x14]
	mov r3, #0x0
	ldr r5, [r0, #0x4]
	ldr r4, [r0, #0x14]
	cmp r5, #0x0
	bls _02034C04
	add r6, r4, #0x0
_02034BEC:
	ldrh r0, [r6, #0x0]
	cmp r1, r0
	bne _02034BFC
	lsl r0, r3, #0x5
	add r0, r4, r0
	strh r2, [r0, #0x4]
	mov r0, #0x1
	pop {r4-r6, pc}
_02034BFC:
	add r3, r3, #0x1
	add r6, #0x20
	cmp r3, r5
	blo _02034BEC
_02034C04:
	bl ErrorHandling
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02034C0C
FUN_02034C0C: ; 0x02034C0C
	push {r3-r4}
	ldr r0, [r0, #0x14]
	ldr r4, [r0, #0x18]
	mov r0, #0xc
	mul r0, r1
	strh r2, [r4, r0]
	add r0, r4, r0
	strh r3, [r0, #0x2]
	mov r0, #0x1
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_02034C24
FUN_02034C24: ; 0x02034C24
	ldr r0, [r0, #0x14]
	ldr r3, [r0, #0x18]
	mov r0, #0xc
	mul r0, r1
	add r0, r3, r0
	strh r2, [r0, #0x4]
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02034C34
FUN_02034C34: ; 0x02034C34
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02034AF0
	mov r1, #0x14
	mul r1, r5
	add r0, r0, r1
	str r4, [r0, #0x4]
	str r6, [r0, #0x8]
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02034C50
FUN_02034C50: ; 0x02034C50
	add r1, r0, #0x0
	ldr r2, [r0, #0x20]
	add r1, #0x20
	add r1, r1, #0x4
	str r2, [r0, #0x0]
	cmp r2, #0x0
	beq _02034C62
	str r1, [r0, #0x10]
	b _02034C66
_02034C62:
	mov r2, #0x0
	str r2, [r0, #0x10]
_02034C66:
	ldr r3, [r0, #0x0]
	mov r2, #0x14
	mul r2, r3
	add r3, r1, r2
	ldr r2, [r1, r2]
	add r1, r3, #0x4
	str r2, [r0, #0x4]
	cmp r2, #0x0
	beq _02034C7C
	str r1, [r0, #0x14]
	b _02034C80
_02034C7C:
	mov r2, #0x0
	str r2, [r0, #0x14]
_02034C80:
	ldr r2, [r0, #0x4]
	lsl r2, r2, #0x5
	add r3, r1, r2
	ldr r2, [r1, r2]
	add r1, r3, #0x4
	str r2, [r0, #0x8]
	cmp r2, #0x0
	beq _02034C94
	str r1, [r0, #0x18]
	b _02034C98
_02034C94:
	mov r2, #0x0
	str r2, [r0, #0x18]
_02034C98:
	ldr r3, [r0, #0x8]
	mov r2, #0xc
	mul r2, r3
	add r3, r1, r2
	ldr r1, [r1, r2]
	str r1, [r0, #0xc]
	cmp r1, #0x0
	beq _02034CAE
	add r1, r3, #0x4
	str r1, [r0, #0x1c]
	bx lr
_02034CAE:
	mov r1, #0x0
	str r1, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_02034CB4
FUN_02034CB4: ; 0x02034CB4
	push {r3-r5, lr}
	mov r2, #0x6a
	add r4, r1, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r5, r0, #0x0
	bl memset
	add r0, r4, #0x0
	bl FUN_020347D8
	cmp r0, #0x0
	beq _02034CDE
	add r0, r4, #0x0
	bl FUN_020347FC
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x25
	bl LoadFromNARC
_02034CDE:
	pop {r3-r5, pc}

	thumb_func_start FUN_02034CE0
FUN_02034CE0: ; 0x02034CE0
	ldr r1, [r0, #0x14]
	mov r0, #0x92
	lsl r0, r0, #0x4
	add r0, r1, r0
	bx lr
	.balign 4

	thumb_func_start FUN_02034CEC
FUN_02034CEC: ; 0x02034CEC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_0203479C
	mov r1, #0x82
	lsl r1, r1, #0x4
	mov r2, #0x1
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r5, r1
	lsl r2, r2, #0x8
	bl MIi_CpuClearFast
	mov r0, #0xa
	add r1, r4, #0x0
	bl LoadFromNARC_7
	mov r1, #0x1
	lsl r1, r1, #0x8
	cmp r0, r1
	blo _02034D1C
	bl ErrorHandling
_02034D1C:
	mov r0, #0x82
	lsl r0, r0, #0x4
	add r0, r5, r0
	mov r1, #0xa
	add r2, r4, #0x0
	bl LoadFromNARC
	pop {r3-r5, pc}

	thumb_func_start FUN_02034D2C
FUN_02034D2C: ; 0x02034D2C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02034D3A
	bl ErrorHandling
_02034D3A:
	mov r0, #0x82
	ldr r1, [r4, #0x14]
	lsl r0, r0, #0x4
	add r0, r1, r0
	pop {r4, pc}

	thumb_func_start FUN_02034D44
FUN_02034D44: ; 0x02034D44
	push {r4-r7}
	ldr r0, [r0, #0x14]
	mov r3, #0x0
	ldr r4, [r0, #0x4]
	cmp r4, #0x0
	bls _02034D76
	ldr r6, [r0, #0x14]
	add r5, r3, #0x0
	add r4, r6, #0x0
_02034D56:
	ldrh r7, [r4, #0x18]
	cmp r1, r7
	bne _02034D6A
	add r7, r6, r5
	ldrh r7, [r7, #0x1a]
	cmp r2, r7
	bne _02034D6A
	mov r0, #0x0
	pop {r4-r7}
	bx lr
_02034D6A:
	ldr r7, [r0, #0x4]
	add r3, r3, #0x1
	add r4, #0x20
	add r5, #0x20
	cmp r3, r7
	blo _02034D56
_02034D76:
	mov r0, #0x1
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_02034D7C
FUN_02034D7C: ; 0x02034D7C
	mov r0, #0xa0
	bx lr

	thumb_func_start FUN_02034D80
FUN_02034D80: ; 0x02034D80
	mov r0, #0x5
	lsl r0, r0, #0xa
	bx lr
	.balign 4

	thumb_func_start FUN_02034D88
FUN_02034D88: ; 0x02034D88
	ldr r3, _02034D94 ; =MIi_CpuClear32
	mov r2, #0x5
	add r1, r0, #0x0
	mov r0, #0x0
	lsl r2, r2, #0xa
	bx r3
	.balign 4
_02034D94: .word MIi_CpuClear32

	thumb_func_start FUN_02034D98
FUN_02034D98: ; 0x02034D98
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0xa0
	bl memset
	add r0, r4, #0x0
	add r0, #0x6c
	bl FUN_0204ADE0
	add r0, r4, #0x0
	add r0, #0x8c
	bl FUN_02055468
	bl FUN_02034E8C
	add r4, #0x68
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034DC0
FUN_02034DC0: ; 0x02034DC0
	bx lr
	.balign 4

	thumb_func_start FUN_02034DC4
FUN_02034DC4: ; 0x02034DC4
	add r0, #0x14
	bx lr

	thumb_func_start FUN_02034DC8
FUN_02034DC8: ; 0x02034DC8
	add r0, #0x28
	bx lr

	thumb_func_start FUN_02034DCC
FUN_02034DCC: ; 0x02034DCC
	add r0, #0x50
	bx lr

	thumb_func_start FUN_02034DD0
FUN_02034DD0: ; 0x02034DD0
	add r0, #0x3c
	bx lr

	thumb_func_start FUN_02034DD4
FUN_02034DD4: ; 0x02034DD4
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x3c
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_02034DE8
FUN_02034DE8: ; 0x02034DE8
	add r0, #0x64
	bx lr

	thumb_func_start FUN_02034DEC
FUN_02034DEC: ; 0x02034DEC
	add r0, #0x66
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034DF4
FUN_02034DF4: ; 0x02034DF4
	add r0, #0x66
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034DFC
FUN_02034DFC: ; 0x02034DFC
	add r0, #0x68
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034E04
FUN_02034E04: ; 0x02034E04
	add r0, #0x68
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034E0C
FUN_02034E0C: ; 0x02034E0C
	add r0, #0x6c
	bx lr

	thumb_func_start FUN_02034E10
FUN_02034E10: ; 0x02034E10
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034E18
FUN_02034E18: ; 0x02034E18
	add r0, #0x6a
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02034E20
FUN_02034E20: ; 0x02034E20
	add r0, #0x8c
	bx lr

	thumb_func_start FUN_02034E24
FUN_02034E24: ; 0x02034E24
	add r0, #0x98
	bx lr

	thumb_func_start FUN_02034E28
FUN_02034E28: ; 0x02034E28
	add r0, #0x96
	bx lr

	thumb_func_start FUN_02034E2C
FUN_02034E2C: ; 0x02034E2C
	add r0, #0x94
	bx lr

	thumb_func_start FUN_02034E30
FUN_02034E30: ; 0x02034E30
	ldr r3, _02034E38 ; =FUN_02022610
	mov r1, #0x6
	bx r3
	nop
_02034E38: .word FUN_02022610

	thumb_func_start FUN_02034E3C
FUN_02034E3C: ; 0x02034E3C
	ldr r3, _02034E44 ; =FUN_02022610
	mov r1, #0xb
	bx r3
	nop
_02034E44: .word FUN_02022610

	thumb_func_start FUN_02034E48
FUN_02034E48: ; 0x02034E48
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02034E3C
	add r2, r0, #0x0
	ldr r1, [r4, #0x34]
	add r0, r4, #0x0
	mov r3, #0x40
	bl FUN_02057800
	pop {r4, pc}

	thumb_func_start FUN_02034E60
FUN_02034E60: ; 0x02034E60
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02034E3C
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	mov r2, #0x40
	bl FUN_0205785C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034E78
FUN_02034E78: ; 0x02034E78
	push {r3, lr}
	cmp r0, #0x0
	ble _02034E82
	cmp r0, #0x14
	bls _02034E88
_02034E82:
	bl ErrorHandling
	mov r0, #0x1
_02034E88:
	sub r0, r0, #0x1
	pop {r3, pc}

	thumb_func_start FUN_02034E8C
FUN_02034E8C: ; 0x02034E8C
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02034E90
FUN_02034E90: ; 0x02034E90
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02034E78
	lsl r1, r0, #0x4
	ldr r0, _02034EB8 ; =0x020F222A
	ldrh r0, [r0, r1]
	str r0, [r4, #0x0]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	ldr r0, _02034EBC ; =0x020F222C
	ldrh r0, [r0, r1]
	str r0, [r4, #0x8]
	ldr r0, _02034EC0 ; =0x020F222E
	ldrh r0, [r0, r1]
	str r0, [r4, #0xc]
	mov r0, #0x1
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4
_02034EB8: .word 0x020F222A
_02034EBC: .word 0x020F222C
_02034EC0: .word 0x020F222E

	thumb_func_start FUN_02034EC4
FUN_02034EC4: ; 0x02034EC4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02034E78
	lsl r1, r0, #0x4
	ldr r0, _02034EEC ; =0x020F2224
	ldrh r0, [r0, r1]
	str r0, [r4, #0x0]
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0x4]
	ldr r0, _02034EF0 ; =0x020F2226
	ldrh r0, [r0, r1]
	str r0, [r4, #0x8]
	ldr r0, _02034EF4 ; =0x020F2228
	ldrh r0, [r0, r1]
	str r0, [r4, #0xc]
	mov r0, #0x0
	str r0, [r4, #0x10]
	pop {r4, pc}
	.balign 4
_02034EEC: .word 0x020F2224
_02034EF0: .word 0x020F2226
_02034EF4: .word 0x020F2228

	thumb_func_start FUN_02034EF8
FUN_02034EF8: ; 0x02034EF8
	ldr r3, _02034F18 ; =0x020F2224
	mov r2, #0x0
_02034EFC:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _02034F0C
	ldrb r1, [r3, #0xc]
	cmp r1, #0x0
	beq _02034F0C
	add r0, r2, #0x1
	bx lr
_02034F0C:
	add r2, r2, #0x1
	add r3, #0x10
	cmp r2, #0x14
	blo _02034EFC
	mov r0, #0x0
	bx lr
	.balign 4
_02034F18: .word 0x020F2224

	thumb_func_start FUN_02034F1C
FUN_02034F1C: ; 0x02034F1C
	ldr r3, _02034F3C ; =0x020F2224
	mov r2, #0x0
_02034F20:
	ldrh r1, [r3, #0x6]
	cmp r0, r1
	bne _02034F30
	ldrb r1, [r3, #0xc]
	cmp r1, #0x0
	beq _02034F30
	add r0, r2, #0x1
	bx lr
_02034F30:
	add r2, r2, #0x1
	add r3, #0x10
	cmp r2, #0x14
	blo _02034F20
	mov r0, #0x0
	bx lr
	.balign 4
_02034F3C: .word 0x020F2224

	thumb_func_start FUN_02034F40
FUN_02034F40: ; 0x02034F40
	push {r3-r6}
	asr r3, r1, #0x4
	lsr r3, r3, #0x1b
	add r3, r1, r3
	asr r1, r2, #0x4
	lsr r1, r1, #0x1b
	add r1, r2, r1
	mov r4, #0x0
	asr r2, r1, #0x5
	ldr r5, _02034F84 ; =0x020F2224
	asr r3, r3, #0x5
	add r1, r4, #0x0
_02034F58:
	ldrh r6, [r5, #0x6]
	cmp r0, r6
	bne _02034F76
	ldrh r6, [r5, #0x8]
	add r4, r1, #0x1
	lsr r6, r6, #0x5
	cmp r3, r6
	bne _02034F76
	ldrh r6, [r5, #0xa]
	lsr r6, r6, #0x5
	cmp r2, r6
	bne _02034F76
	add r0, r4, #0x0
	pop {r3-r6}
	bx lr
_02034F76:
	add r1, r1, #0x1
	add r5, #0x10
	cmp r1, #0x14
	blo _02034F58
	add r0, r4, #0x0
	pop {r3-r6}
	bx lr
	.balign 4
_02034F84: .word 0x020F2224

	thumb_func_start FUN_02034F88
FUN_02034F88: ; 0x02034F88
	push {r4, lr}
	ldr r3, _02034FB8 ; =0x020F2224
	mov r4, #0x0
_02034F8E:
	ldrh r2, [r3, #0x6]
	cmp r1, r2
	bne _02034FAE
	ldrb r2, [r3, #0xd]
	cmp r2, #0x0
	beq _02034FAE
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	ldr r2, _02034FBC ; =0x020F2232
	lsl r3, r4, #0x4
	ldrh r2, [r2, r3]
	mov r1, #0x1
	bl FUN_0205F2E4
	pop {r4, pc}
_02034FAE:
	add r4, r4, #0x1
	add r3, #0x10
	cmp r4, #0x14
	blo _02034F8E
	pop {r4, pc}
	.balign 4
_02034FB8: .word 0x020F2224
_02034FBC: .word 0x020F2232

	thumb_func_start FUN_02034FC0
FUN_02034FC0: ; 0x02034FC0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02034E78
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
	ldr r2, _02034FE0 ; =0x020F2232
	lsl r3, r4, #0x4
	ldrh r2, [r2, r3]
	mov r1, #0x2
	bl FUN_0205F2E4
	pop {r3-r5, pc}
	.balign 4
_02034FE0: .word 0x020F2232

	thumb_func_start FUN_02034FE4
FUN_02034FE4: ; 0x02034FE4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02034838
	add r4, r0, #0x0
	cmp r4, #0x18
	blt _0203505C
	ldr r0, [r7, #0xc]
	bl FUN_02023794
	add r6, r0, #0x0
	add r0, r6, #0x4
	bl FUN_02012710
	sub r5, r0, #0x1
	bmi _0203500C
	ldr r0, _02035060 ; =0x0000016E
	cmp r5, r0
	blt _02035010
_0203500C:
	bl ErrorHandling
_02035010:
	ldr r0, [r6, #0x8]
	cmp r0, #0x2
	bls _02035044
	ldr r6, [r6, #0x4]
	mov r0, #0x3
	tst r0, r6
	bne _0203502A
	add r0, r6, #0x0
	mov r1, #0x64
	bl _u32_div_f
	cmp r1, #0x0
	bne _02035038
_0203502A:
	mov r1, #0x19
	add r0, r6, #0x0
	lsl r1, r1, #0x4
	bl _u32_div_f
	cmp r1, #0x0
	bne _0203503C
_02035038:
	mov r0, #0x1
	b _0203503E
_0203503C:
	mov r0, #0x0
_0203503E:
	cmp r0, #0x0
	bne _02035044
	add r5, r5, #0x1
_02035044:
	add r0, r7, #0x0
	bl FUN_0204B33C
	cmp r0, #0x0
	beq _02035050
	mov r5, #0x1
_02035050:
	lsl r0, r5, #0x2
	sub r4, #0x18
	add r0, r5, r0
	add r1, r4, r0
	ldr r0, _02035064 ; =0x020F2364
	ldrb r0, [r0, r1]
_0203505C:
	pop {r3-r7, pc}
	nop
_02035060: .word 0x0000016E
_02035064: .word 0x020F2364

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
	bl FUN_020462AC
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
	bl FUN_020462AC
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
	bl FUN_020462AC
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
	bl FUN_020462AC
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
	bl FUN_02016998
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
	bl FUN_020462AC
	bl FUN_0205F388
	cmp r0, #0x0
	bne _0203529A
	mov r0, #0x2
	orr r4, r0
_0203529A:
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
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
	bl FUN_02016A18
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
	bl FUN_02016A18
	b _02035484
_02035432:
	bl FUN_02016A18
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
	bl FUN_02016A18
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
	bl FUN_0200A86C
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	mov r1, #0xb
	bl FUN_02012838
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
	bl FUN_0200AA80
	add r6, r0, #0x0
	mov r0, #0x8
	mov r1, #0xb
	bl FUN_020219F4
	add r1, r4, r5
	add r1, #0x30
	ldrb r1, [r1, #0x0]
	add r7, r0, #0x0
	ldr r0, [sp, #0x18]
	lsl r2, r1, #0x3
	ldr r1, _02035664 ; =0x020F2ACC
	ldr r1, [r1, r2]
	bl FUN_0200A914
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r2, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_0200ABC0
	ldr r2, [sp, #0x20]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_0200B7B8
	add r2, r4, r5
	add r2, #0x30
	ldrb r2, [r2, #0x0]
	ldr r0, [r4, #0x24]
	add r1, r7, #0x0
	bl FUN_020128A0
	ldr r0, [sp, #0x20]
	bl FUN_02021A20
	add r0, r7, #0x0
	bl FUN_02021A20
	add r0, r6, #0x0
	bl FUN_0200AB18
	b _020355A2
_02035594:
	ldr r2, _02035664 ; =0x020F2ACC
	lsl r6, r3, #0x3
	ldr r0, [r4, #0x24]
	ldr r1, [sp, #0x18]
	ldr r2, [r2, r6]
	bl FUN_02012880
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
	bl FUN_0200A8B8
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
	bl FUN_020238F4
	bl FUN_020239CC
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
_02035664: .word 0x020F2ACC
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
	bl FUN_02012870
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
	bl FUN_020462AC
	bl FUN_0205F214
	cmp r0, #0x1
	bne _0203575A
	mov r6, #0x0
	b _0203576C
_0203575A:
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
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
	bl FUN_0200A86C
	str r0, [sp, #0x1c]
	cmp r6, #0x0
	bne _020357D0
	mov r1, #0x9
	bl FUN_0200A914
	b _020357D6
_020357D0:
	mov r1, #0xa
	bl FUN_0200A914
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
	bl FUN_0201BD84
	add r0, r7, #0x0
	bl FUN_02021A20
	mov r0, #0xb
	bl FUN_0200AA80
	add r7, r0, #0x0
	mov r0, #0x20
	mov r1, #0xb
	bl FUN_020219F4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	mov r1, #0xb
	bl FUN_0200A914
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
	bl FUN_0200AD38
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
	bl FUN_0200AD38
_0203584C:
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r0, r7, #0x0
	bl FUN_0200B7B8
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
	bl FUN_0201BD84
	ldr r0, [sp, #0x18]
	bl FUN_02021A20
	ldr r0, [sp, #0x14]
	bl FUN_02021A20
	add r0, r7, #0x0
	bl FUN_0200AB18
	ldr r0, [sp, #0x1c]
	bl FUN_0200A8B8
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
	bl FUN_020462AC
	bl FUN_0205F214
	cmp r0, #0x0
	bne _020358CE
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
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
	ldr r0, _02035988 ; =0x020F2AD0
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
_02035988: .word 0x020F2AD0

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
	ldr r4, _02035B60 ; =0x020F2AB4
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
	ldr r1, _02035B68 ; =0x020F2B14
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
	ldr r3, _02035B70 ; =0x020F2B48
	add r7, r4, #0x0
	add r2, sp, #0x28
	mov r6, #0x6
_02035AA2:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r6, r6, #0x1
	bne _02035AA2
	ldr r0, [r3, #0x0]
	ldr r3, _02035B74 ; =0x020F2AA8
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
_02035B60: .word 0x020F2AB4
_02035B64: .word 0x000034D8
_02035B68: .word 0x020F2B14
_02035B6C: .word 0x000034D9
_02035B70: .word 0x020F2B48
_02035B74: .word 0x020F2AA8

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
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0xc]
	bl FUN_020462AC
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0204B2A4
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
	bl FUN_02016998
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x40
	add r6, r0, #0x0
	bl memcpy
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02016A18
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
	bl FUN_02016998
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r7, #0x0]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r7, #0x4]
	mov r0, #0x1
	strb r0, [r7, #0x11]
	add r0, r6, #0x0
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	strb r0, [r7, #0x14]
	ldr r0, [r7, #0x0]
	bl FUN_0206B9AC
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
	ldr r1, _0203626C ; =0x020F2A9C
	add r0, r7, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
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
	bl FUN_02016998
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r7, #0x0]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
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
	ldr r1, _02036274 ; =0x020F2A8C
	add r0, r7, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0207C2A4
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0203796C
	mov r0, #0xb
	mov r1, #0x4
	bl FUN_02016998
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
	bl FUN_02016998
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r7, #0x0]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
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
	ldr r1, _02036274 ; =0x020F2A8C
	add r0, r7, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	add r1, r0, #0x0
	add r0, r7, #0x0
	bl FUN_0207C2A4
	add r0, r5, #0x0
	add r1, r7, #0x0
	bl FUN_0203796C
	mov r0, #0xb
	mov r1, #0x4
	bl FUN_02016998
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
	bl FUN_0206EAB8
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
	bl FUN_0206BB1C
	add r1, r6, #0x0
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	bl FUN_0206B9B0
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
	bl FUN_02016998
	add r1, r6, #0x0
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	str r1, [r0, #0x0]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	ldr r1, _0203627C ; =0x020F2A90
	add r0, r7, #0x0
	mov r2, #0xb
	bl FUN_0206EFEC
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
	bl FUN_02016998
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
	bl FUN_02016998
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
	bl FUN_02016A18
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_0203626C: .word 0x020F2A9C
_02036270: .word FUN_0203684C
_02036274: .word 0x020F2A8C
_02036278: .word FUN_02036BDC
_0203627C: .word 0x020F2A90
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
	bl FUN_0206E2F0
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
	bl FUN_02016A18
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
	bl FUN_0206E7B8
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
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	add r5, r0, #0x0
	bl memset
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	str r0, [r5, #0x0]
	ldr r0, [r6, #0xc]
	bl FUN_0206F158
	str r0, [r5, #0x4]
	ldr r0, [r6, #0xc]
	bl FUN_02025838
	str r0, [r5, #0x8]
	ldr r0, [r6, #0xc]
	bl LoadPlayerDataAddress
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
	ldr r1, _02036504 ; =0x020F96DC
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
	bl FUN_0206BB1C
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
	bl FUN_0206B9B0
	str r0, [sp, #0xc]
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	add r0, r5, #0x0
	bl FUN_0206EA98
	cmp r0, #0x1
	bne _02036474
	ldr r0, [sp, #0xc]
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	cmp r0, #0x0
	bne _02036474
	add r0, r5, #0x0
	bl FUN_0206EAB8
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
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	add r5, r0, #0x0
	bl memset
	ldr r0, [sp, #0x4]
	str r0, [r5, #0x0]
	ldr r0, [r6, #0xc]
	bl FUN_0206F158
	str r0, [r5, #0x4]
	ldr r0, [r6, #0xc]
	bl FUN_02025838
	str r0, [r5, #0x8]
	ldr r0, [r6, #0xc]
	bl LoadPlayerDataAddress
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
	ldr r1, _02036504 ; =0x020F96DC
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
	bl FUN_02016A18
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_02036504: .word 0x020F96DC
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
	bl FUN_02016998
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
	bl FUN_02016A18
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
	bl FUN_02016A18
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
	bl FUN_020462AC
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
	bl FUN_02016A18
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
	bl FUN_02016998
	mov r1, #0x7e
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x30
	add r7, r0, #0x0
	bl memcpy
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02016A18
	ldrb r0, [r7, #0x12]
	cmp r0, #0x2
	bne _0203692E
	mov r0, #0xb
	mov r1, #0x40
	bl FUN_02016998
	mov r1, #0x7f
	lsl r1, r1, #0x2
	ldr r1, [r4, r1]
	mov r2, #0x40
	str r1, [sp, #0x0]
	mov r1, #0x0
	add r5, r0, #0x0
	bl memset
	ldr r0, [r6, #0xc]
	bl FUN_0206BB1C
	str r0, [r5, #0x0]
	ldr r0, [r6, #0xc]
	bl FUN_0206F158
	str r0, [r5, #0x4]
	ldr r0, [r6, #0xc]
	bl FUN_02025838
	str r0, [r5, #0x8]
	ldr r0, [r6, #0xc]
	bl LoadPlayerDataAddress
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
	ldr r1, _02036954 ; =0x020F96DC
	add r0, r6, #0x0
	bl FUN_020373D4
	mov r0, #0x7f
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FUN_02016A18
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
	bl FUN_02016A18
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02036954: .word 0x020F96DC
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
	bl FUN_0206F158
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
	bl FUN_0206EB1C
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	mov r2, #0x1
	mov r3, #0xb
	bl FUN_0206EE50
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
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
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
	bl FUN_02016998
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
	bl FUN_02016A18
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
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl FUN_02025838
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
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
	bl FUN_0206B9B0
	add r1, r0, #0x0
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_0208560C
	mov r0, #0x7e
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	bl FUN_0208562C
	ldr r1, _02036D8C ; =0x020F96DC
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
_02036D8C: .word 0x020F96DC
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
	bl FUN_0206BB1C
	ldrb r1, [r5, #0x0]
	str r0, [sp, #0x20]
	bl FUN_0206B9B0
	str r0, [sp, #0x24]
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	ldr r0, [r4, #0xc]
	bne _02036E9E
	bl LoadPlayerDataAddress
	str r0, [sp, #0x28]
	ldr r0, [r4, #0xc]
	bl FUN_02079C70
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02024DA0
	str r0, [sp, #0x2c]
	ldr r0, [r4, #0xc]
	bl FUN_0206F158
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
	bl LoadPlayerDataAddress
	str r0, [sp, #0x38]
	ldr r0, [r4, #0xc]
	bl FUN_02079C70
	add r7, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02024DA0
	str r0, [sp, #0x3c]
	ldr r0, [r4, #0xc]
	bl FUN_0206F158
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
	bl FUN_02016998
	ldrb r1, [r5, #0x0]
	str r1, [r0, #0x0]
	mov r1, #0x7f
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	sub r0, r1, #0x4
	ldr r0, [r6, r0]
	bl FUN_02016A18
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
	bl FUN_02016A18
	ldr r1, _02036FA0 ; =FUN_020362E4
	add r0, r4, #0x0
	bl FUN_02035D04
_02036F98:
	pop {r3-r5, pc}
	nop
_02036F9C: .word 0x00000475
_02036FA0: .word FUN_020362E4

	thumb_func_start FUN_02036FA4
FUN_02036FA4: ; 0x02036FA4
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x38]
	add r4, r1, #0x0
	add r5, r2, #0x0
	bl FUN_020552F8
	add r7, r0, #0x0
	ldr r0, [r6, #0x38]
	bl FUN_02055320
	str r0, [r4, #0x0]
	ldr r0, [r6, #0x38]
	bl FUN_0205532C
	str r0, [r5, #0x0]
	cmp r7, #0x3
	bhi _02036FFA
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02036FD4: ; jump table (using 16-bit offset)
	.short _02036FDC - _02036FD4 - 2; case 0
	.short _02036FE4 - _02036FD4 - 2; case 1
	.short _02036FEC - _02036FD4 - 2; case 2
	.short _02036FF4 - _02036FD4 - 2; case 3
_02036FDC:
	ldr r0, [r5, #0x0]
	sub r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02036FFA
_02036FE4:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _02036FFA
_02036FEC:
	ldr r0, [r4, #0x0]
	sub r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02036FFA
_02036FF4:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02036FFA:
	add r0, r7, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02037000
FUN_02037000: ; 0x02037000
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_020553A0
	bl FUN_02058BE4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02058BE4
	cmp r4, r0
	bne _0203701C
	mov r0, #0x1
	b _0203701E
_0203701C:
	mov r0, #0x0
_0203701E:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r5, pc}

	thumb_func_start FUN_02037024
FUN_02037024: ; 0x02037024
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r1, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	add r5, r0, #0x0
	bl FUN_02036FA4
	add r4, r0, #0x0
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_0204A6E0
	bl FUN_020547A4
	cmp r0, #0x1
	bne _0203707E
	cmp r4, #0x3
	bhi _0203707E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02037058: ; jump table (using 16-bit offset)
	.short _02037060 - _02037058 - 2; case 0
	.short _02037068 - _02037058 - 2; case 1
	.short _02037070 - _02037058 - 2; case 2
	.short _02037078 - _02037058 - 2; case 3
_02037060:
	ldr r0, [sp, #0x0]
	sub r0, r0, #0x1
	str r0, [sp, #0x0]
	b _0203707E
_02037068:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	b _0203707E
_02037070:
	ldr r0, [sp, #0x4]
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
	b _0203707E
_02037078:
	ldr r0, [sp, #0x4]
	add r0, r0, #0x1
	str r0, [sp, #0x4]
_0203707E:
	ldr r0, [r5, #0x34]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x0]
	bl FUN_02058D74
	str r0, [r6, #0x0]
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02037090
FUN_02037090: ; 0x02037090
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl FUN_02037024
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020370B8
	bl FUN_020588D4
	cmp r0, #0x1
	bne _020370B8
	ldr r0, [r5, #0x38]
	ldr r1, [r4, #0x0]
	bl FUN_02037000
	cmp r0, #0x1
	bne _020370B8
	mov r0, #0x1
	pop {r3-r5, pc}
_020370B8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020370BC
FUN_020370BC: ; 0x020370BC
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r1, sp, #0xc
	add r2, sp, #0x8
	add r6, r0, #0x0
	bl FUN_02036FA4
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	cmp r0, #0x0
	ble _02037130
	ldr r4, [sp, #0x0]
	add r5, r4, #0x0
_020370DA:
	ldr r1, [sp, #0xc]
	ldr r0, [r4, #0x4]
	cmp r1, r0
	bne _02037124
	ldr r1, [sp, #0x8]
	ldr r0, [r4, #0x8]
	cmp r1, r0
	bne _02037124
	ldrh r0, [r4, #0x2]
	cmp r0, #0x2
	bne _0203710A
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_0203713C
	cmp r0, #0x1
	bne _02037124
	mov r0, #0x14
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x10
	ldrh r0, [r0, r1]
	pop {r3-r7, pc}
_0203710A:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02037168
	cmp r0, #0x1
	bne _02037124
	mov r0, #0x14
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x0]
	add sp, #0x10
	ldrh r0, [r0, r1]
	pop {r3-r7, pc}
_02037124:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r4, #0x14
	add r5, #0x14
	cmp r7, r0
	blt _020370DA
_02037130:
	ldr r0, _02037138 ; =0x0000FFFF
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02037138: .word 0x0000FFFF

	thumb_func_start FUN_0203713C
FUN_0203713C: ; 0x0203713C
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r0, [r1, #0x2]
	cmp r0, #0x2
	beq _0203714A
	mov r0, #0x0
	pop {r4, pc}
_0203714A:
	ldrh r0, [r1, #0x0]
	bl FUN_02039694
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02039528
	cmp r0, #0x1
	beq _02037160
	mov r0, #0x1
	b _02037162
_02037160:
	mov r0, #0x0
_02037162:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}

	thumb_func_start FUN_02037168
FUN_02037168: ; 0x02037168
	push {r4, lr}
	add r4, r1, #0x0
	ldrh r1, [r4, #0x10]
	cmp r1, #0x4
	bne _02037176
	mov r0, #0x1
	pop {r4, pc}
_02037176:
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	cmp r0, #0x3
	bhi _020371CC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203718C: ; jump table (using 16-bit offset)
	.short _02037194 - _0203718C - 2; case 0
	.short _020371A2 - _0203718C - 2; case 1
	.short _020371B0 - _0203718C - 2; case 2
	.short _020371BE - _0203718C - 2; case 3
_02037194:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0203719E
	cmp r0, #0x6
	bne _020371CC
_0203719E:
	mov r0, #0x1
	pop {r4, pc}
_020371A2:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x3
	beq _020371AC
	cmp r0, #0x6
	bne _020371CC
_020371AC:
	mov r0, #0x1
	pop {r4, pc}
_020371B0:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x2
	beq _020371BA
	cmp r0, #0x5
	bne _020371CC
_020371BA:
	mov r0, #0x1
	pop {r4, pc}
_020371BE:
	ldrh r0, [r4, #0x10]
	cmp r0, #0x1
	beq _020371C8
	cmp r0, #0x5
	bne _020371CC
_020371C8:
	mov r0, #0x1
	pop {r4, pc}
_020371CC:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020371D0
FUN_020371D0: ; 0x020371D0
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020552F8
	cmp r0, #0x0
	beq _020371EA
	add sp, #0x8
	ldr r0, _0203722C ; =0x0000FFFF
	pop {r4-r6, pc}
_020371EA:
	add r0, r5, #0x0
	add r1, sp, #0x4
	add r2, sp, #0x0
	bl FUN_02036FA4
	mov r0, #0x0
	cmp r4, #0x0
	ble _02037224
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x0]
	add r1, r6, #0x0
_02037200:
	ldr r5, [r1, #0x4]
	cmp r2, r5
	bne _0203721C
	ldr r5, [r1, #0x8]
	cmp r3, r5
	bne _0203721C
	ldrh r5, [r1, #0x2]
	cmp r5, #0x1
	bne _0203721C
	mov r1, #0x14
	mul r1, r0
	add sp, #0x8
	ldrh r0, [r6, r1]
	pop {r4-r6, pc}
_0203721C:
	add r0, r0, #0x1
	add r1, #0x14
	cmp r0, r4
	blt _02037200
_02037224:
	ldr r0, _0203722C ; =0x0000FFFF
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0203722C: .word 0x0000FFFF

	thumb_func_start FUN_02037230
FUN_02037230: ; 0x02037230
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x38]
	add r4, r1, #0x0
	bl FUN_020552F8
	cmp r0, #0x0
	beq _02037244
	mov r0, #0x0
	pop {r3-r5, pc}
_02037244:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02037090
	cmp r0, #0x1
	bne _02037260
	ldr r0, [r4, #0x0]
	bl FUN_02058458
	sub r0, #0x5b
	cmp r0, #0x5
	bhi _02037260
	mov r0, #0x1
	pop {r3-r5, pc}
_02037260:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02037264
FUN_02037264: ; 0x02037264
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x38]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	bl FUN_02055320
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r4, r0, #0x0
	ldr r0, [sp, #0x8]
	mov r7, #0x0
	cmp r0, #0x0
	ble _020372C8
	ldr r5, [sp, #0x4]
_0203728A:
	ldrh r1, [r5, #0x2]
	cmp r6, r1
	blt _020372BE
	ldrh r0, [r5, #0x6]
	add r0, r1, r0
	cmp r6, r0
	bge _020372BE
	ldrh r1, [r5, #0x4]
	cmp r4, r1
	blt _020372BE
	ldrh r0, [r5, #0x8]
	add r0, r1, r0
	cmp r4, r0
	bge _020372BE
	ldrh r1, [r5, #0xe]
	ldr r0, [sp, #0x0]
	bl FUN_020394F0
	ldrh r1, [r5, #0xc]
	cmp r1, r0
	bne _020372BE
	ldr r0, [sp, #0x4]
	lsl r1, r7, #0x4
	add sp, #0xc
	ldrh r0, [r0, r1]
	pop {r4-r7, pc}
_020372BE:
	ldr r0, [sp, #0x8]
	add r7, r7, #0x1
	add r5, #0x10
	cmp r7, r0
	blt _0203728A
_020372C8:
	ldr r0, _020372D0 ; =0x0000FFFF
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_020372D0: .word 0x0000FFFF

	thumb_func_start FUN_020372D4
FUN_020372D4: ; 0x020372D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0200628C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02037400
	ldr r1, _02037300 ; =0x021C5A08
	str r0, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _020372F4
	bl FUN_02048FC8
	b _020372F8
_020372F4:
	bl FUN_02048EC8
_020372F8:
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02037300: .word 0x021C5A08

	thumb_func_start FUN_02037304
FUN_02037304: ; 0x02037304
	push {r3, lr}
	bl FUN_02037400
	ldr r1, _02037318 ; =0x021C5A08
	str r0, [r1, #0x0]
	bl FUN_02048D90
	mov r0, #0x1
	pop {r3, pc}
	nop
_02037318: .word 0x021C5A08

	thumb_func_start FUN_0203731C
FUN_0203731C: ; 0x0203731C
	push {r3, lr}
	bl FUN_02006278
	bl FUN_02037524
	cmp r0, #0x0
	beq _0203732E
	mov r0, #0x1
	pop {r3, pc}
_0203732E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02037334
FUN_02037334: ; 0x02037334
	push {r3, lr}
	bl FUN_020374B0
	ldr r0, _02037348 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _0203734C ; =0x021DBAB8
	bl FUN_02000E7C
	mov r0, #0x1
	pop {r3, pc}
	nop
_02037348: .word SDK_OVERLAY_MODULE_63_ID
_0203734C: .word 0x021DBAB8

	thumb_func_start LoadOverlay_MODULE_05
LoadOverlay_MODULE_05: ; 0x02037350
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02037360
	bl ErrorHandling
_02037360:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203736C
	bl ErrorHandling
_0203736C:
	ldr r0, _0203738C ; =SDK_OVERLAY_MODULE_05_ID
	mov r1, #0x2
	bl HandleLoadOverlay
	mov r1, #0x0
	str r1, [r4, #0x64]
	ldr r0, [r4, #0x0]
	mov r2, #0xb
	str r1, [r0, #0x8]
	ldr r0, _02037390 ; =0x021F64C8
	add r1, r4, #0x0
	bl FUN_02006234
	ldr r1, [r4, #0x0]
	str r0, [r1, #0x0]
	pop {r4, pc}
	.balign 4
_0203738C: .word SDK_OVERLAY_MODULE_05_ID
_02037390: .word 0x021F64C8

	thumb_func_start FUN_02037394
FUN_02037394: ; 0x02037394
	mov r1, #0x0
	str r1, [r0, #0x64]
	bx lr
	.balign 4

	thumb_func_start FUN_0203739C
FUN_0203739C: ; 0x0203739C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020373A8
	mov r0, #0x1
	bx lr
_020373A8:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020373AC
FUN_020373AC: ; 0x020373AC
	ldr r1, [r0, #0x0]
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020373BE
	ldr r0, [r0, #0x64]
	cmp r0, #0x0
	beq _020373BE
	mov r0, #0x1
	bx lr
_020373BE:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_020373C4
FUN_020373C4: ; 0x020373C4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020373D0
	mov r0, #0x1
	bx lr
_020373D0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020373D4
FUN_020373D4: ; 0x020373D4
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	ldr r0, [r0, #0x4]
	add r6, r2, #0x0
	cmp r0, #0x0
	beq _020373E8
	bl ErrorHandling
_020373E8:
	add r0, r5, #0x0
	bl FUN_02037394
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r2, #0xb
	bl FUN_02006234
	ldr r1, [r5, #0x0]
	str r0, [r1, #0x4]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02037400
FUN_02037400: ; 0x02037400
	push {r3-r5, lr}
	mov r2, #0x7
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0xb
	lsl r2, r2, #0xe
	bl FUN_0201681C
	mov r1, #0x20
	mov r0, #0x3
	lsl r2, r1, #0x9
	bl FUN_0201681C
	mov r2, #0x3
	mov r0, #0x0
	mov r1, #0x5b
	lsl r2, r2, #0x8
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0xb8
	mov r2, #0xb
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0xb8
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0xb
	mov r1, #0x10
	bl FUN_02016998
	str r0, [r4, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x8]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0xc]
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r0, [r0, #0x8]
	str r0, [r4, #0xc]
	mov r0, #0x0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	bl FUN_02034E30
	bl FUN_02034DC0
	str r0, [r4, #0x1c]
	bl FUN_02034494
	str r0, [r4, #0x28]
	add r0, r4, #0x0
	mov r1, #0xb
	bl FUN_02034A28
	mov r0, #0xb
	bl FUN_0206F164
	add r1, r4, #0x0
	add r1, #0x94
	str r0, [r1, #0x0]
	mov r0, #0xb
	bl FUN_0205DD18
	add r1, r4, #0x0
	add r1, #0x90
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD40
	mov r0, #0xb
	bl FUN_0208A300
	add r1, r4, #0x0
	add r1, #0xb0
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020374B0
FUN_020374B0: ; 0x020374B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	ldr r0, [r4, #0x28]
	bl FUN_020344D0
	add r0, r4, #0x0
	bl FUN_02034A48
	add r0, r4, #0x0
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl FUN_0205DD38
	add r0, r4, #0x0
	add r0, #0xb0
	ldr r0, [r0, #0x0]
	bl FUN_0208A320
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r5, #0x0
	bl FUN_0200627C
	mov r0, #0x5b
	bl FUN_020168D0
	mov r0, #0xb
	bl FUN_020168D0
	mov r0, #0x20
	bl FUN_020168D0
	pop {r3-r5, pc}

	thumb_func_start FUN_02037504
FUN_02037504: ; 0x02037504
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02037520
	bl FUN_02006290
	cmp r0, #0x0
	beq _02037520
	ldr r0, [r4, #0x0]
	bl FUN_02006260
	mov r0, #0x0
	str r0, [r4, #0x0]
_02037520:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02037524
FUN_02037524: ; 0x02037524
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02037594
	add r0, r4, #0x0
	bl FUN_02046420
	cmp r0, #0x1
	bne _02037546
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02037546
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl MOD05_021EFA9C
_02037546:
	ldr r0, [r4, #0x0]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02037562
	bl FUN_02037504
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203756E
	ldr r0, _02037590 ; =SDK_OVERLAY_MODULE_05_ID
	bl UnloadOverlayByID
	b _0203756E
_02037562:
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0203756E
	add r0, r0, #0x4
	bl FUN_02037504
_0203756E:
	ldr r1, [r4, #0x0]
	ldr r0, [r1, #0xc]
	cmp r0, #0x0
	beq _0203758C
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	bne _0203758C
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0203758C
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	bne _0203758C
	mov r0, #0x1
	pop {r4, pc}
_0203758C:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02037590: .word SDK_OVERLAY_MODULE_05_ID

	thumb_func_start FUN_02037594
FUN_02037594: ; 0x02037594
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	mov r5, #0x0
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	bne _020375B4
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _020375B4
	bl FUN_0204646C
	cmp r0, #0x0
	bne _020375B4
	mov r5, #0x1
_020375B4:
	cmp r5, #0x0
	beq _020375D4
	ldr r0, [r4, #0x38]
	bl FUN_02055A38
	ldr r3, _02037758 ; =0x021C48B8
	add r0, sp, #0x8
	ldr r2, [r3, #0x48]
	ldr r3, [r3, #0x44]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl MOD05_021D8164
_020375D4:
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x6c]
	ldr r1, [r0, #0x0]
	ldr r0, _0203775C ; =0x00000146
	cmp r1, r0
	bne _020375E2
	mov r2, #0x0
_020375E2:
	cmp r2, #0x4
	bhi _020376E2
	add r0, r2, r2
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020375F2: ; jump table (using 16-bit offset)
	.short _020376E2 - _020375F2 - 2; case 0
	.short _020375FC - _020375F2 - 2; case 1
	.short _02037646 - _020375F2 - 2; case 2
	.short _0203761C - _020375F2 - 2; case 3
	.short _02037672 - _020375F2 - 2; case 4
_020375FC:
	cmp r5, #0x0
	beq _02037610
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _02037610
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D85FC
_02037610:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0204D6C0
	add sp, #0x10
	pop {r3-r5, pc}
_0203761C:
	cmp r5, #0x0
	beq _0203763A
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _02037638
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD04_021D865C
	cmp r0, #0x1
	bne _0203763A
	mov r5, #0x0
	b _0203763A
_02037638:
	mov r5, #0x0
_0203763A:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_0204D6C0
	add sp, #0x10
	pop {r3-r5, pc}
_02037646:
	cmp r5, #0x0
	bne _0203764C
	b _02037754
_0203764C:
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D8758
	cmp r0, #0x1
	beq _02037754
	add r3, sp, #0x8
	ldrh r0, [r3, #0x6]
	mov r2, #0x0
	str r0, [sp, #0x0]
	str r2, [sp, #0x4]
	ldrh r3, [r3, #0x4]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x24]
	sub r2, r2, #0x1
	bl FUN_020557F4
	add sp, #0x10
	pop {r3-r5, pc}
_02037672:
	cmp r5, #0x0
	beq _02037754
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D8820
	cmp r0, #0x1
	bne _020376A6
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
	add r0, r4, #0x0
	mov r1, #0x4
	bl MOD05_021E81BC
	ldr r0, [r4, #0x38]
	bl MOD05_021E7138
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl MOD05_021EFA9C
	add sp, #0x10
	pop {r3-r5, pc}
_020376A6:
	ldr r0, _02037758 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _020376B8
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
_020376B8:
	mov r5, #0x0
	bl FUN_02037790
	cmp r0, #0x0
	beq _020376C8
	bl MOD20_02252534
	add r5, r0, #0x0
_020376C8:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x6]
	mov r2, #0x0
	mvn r2, r2
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x4]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x24]
	bl FUN_020557F4
	add sp, #0x10
	pop {r3-r5, pc}
_020376E2:
	cmp r5, #0x0
	beq _02037754
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D8320
	cmp r0, #0x1
	bne _0203771C
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
	add r0, r4, #0x0
	mov r1, #0x4
	bl MOD05_021E81BC
	ldr r0, [r4, #0x38]
	bl FUN_02055B14
	ldr r0, [r4, #0x38]
	bl MOD05_021E7138
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl MOD05_021EFA9C
	add sp, #0x10
	pop {r3-r5, pc}
_0203771C:
	ldr r0, _02037758 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _0203772E
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
_0203772E:
	mov r5, #0x0
	bl FUN_02037790
	cmp r0, #0x0
	beq _0203773E
	bl MOD20_02252534
	add r5, r0, #0x0
_0203773E:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x6]
	mov r2, #0x0
	mvn r2, r2
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x4]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x24]
	bl FUN_020557F4
_02037754:
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_02037758: .word 0x021C48B8
_0203775C: .word 0x00000146

	thumb_func_start FUN_02037760
FUN_02037760: ; 0x02037760
	ldr r0, _02037770 ; =0x021C5A08
	ldr r3, _02037774 ; =FUN_02030FC8
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x8]
	bx r3
	nop
_02037770: .word 0x021C5A08
_02037774: .word FUN_02030FC8

	thumb_func_start FUN_02037778
FUN_02037778: ; 0x02037778
	ldr r0, _02037788 ; =0x021C5A08
	ldr r3, _0203778C ; =FUN_02030FA8
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x8]
	bx r3
	nop
_02037788: .word 0x021C5A08
_0203778C: .word FUN_02030FA8

	thumb_func_start FUN_02037790
FUN_02037790: ; 0x02037790
	ldr r0, _020377A4 ; =0x021C5A08
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _0203779E
	mov r0, #0x0
	bx lr
_0203779E:
	ldr r0, [r0, #0x14]
	bx lr
	nop
_020377A4: .word 0x021C5A08

	thumb_func_start FUN_020377A8
FUN_020377A8: ; 0x020377A8
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_020377AC
FUN_020377AC: ; 0x020377AC
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_020377B0
FUN_020377B0: ; 0x020377B0
	ldr r2, _020377C4 ; =0x020F2B9C
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	nop
_020377C4: .word 0x020F2B9C

	thumb_func_start FUN_020377C8
FUN_020377C8: ; 0x020377C8
	ldr r2, _020377DC ; =0x020F2BB0
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr
	nop
_020377DC: .word 0x020F2BB0

	thumb_func_start FUN_020377E0
FUN_020377E0: ; 0x020377E0
	push {r3, lr}
	bl FUN_02034E30
	bl FUN_02034DC0
	bl FUN_020377B0
	pop {r3, pc}

	thumb_func_start FUN_020377F0
FUN_020377F0: ; 0x020377F0
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_020377F4
FUN_020377F4: ; 0x020377F4
	push {r3, lr}
	bl MOD11_0222D5C0
	cmp r0, #0x0
	beq _02037802
	mov r0, #0x1
	pop {r3, pc}
_02037802:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02037808
FUN_02037808: ; 0x02037808
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0203780C
FUN_0203780C: ; 0x0203780C
	ldr r3, _02037814 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037818 ; =0x020F2D94
	bx r3
	.balign 4
_02037814: .word FUN_020373D4
_02037818: .word 0x020F2D94

	thumb_func_start FUN_0203781C
FUN_0203781C: ; 0x0203781C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02037840 ; =0x020F2D74
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02037840: .word 0x020F2D74

	thumb_func_start FUN_02037844
FUN_02037844: ; 0x02037844
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r6, r1, #0x0
	bl FUN_0206F158
	ldr r1, _02037898 ; =0x020F2BDC
	mov r2, #0xb
	bl FUN_0206EFEC
	add r3, r5, #0x0
	add r3, #0x94
	ldr r1, [r5, #0xc]
	ldr r3, [r3, #0x0]
	mov r2, #0x0
	add r4, r0, #0x0
	bl FUN_0206E314
	ldr r1, [r5, #0x6c]
	add r0, r4, #0x0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_0206E360
	ldr r0, [r5, #0x38]
	bl FUN_020553C4
	cmp r0, #0x1
	bne _02037884
	add r0, r4, #0x0
	bl FUN_0206E340
_02037884:
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0206E354
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0203781C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037898: .word 0x020F2BDC

	thumb_func_start FUN_0203789C
FUN_0203789C: ; 0x0203789C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_0206F158
	add r6, r0, #0x0
	cmp r4, #0x0
	beq _020378B4
	cmp r4, #0x1
	beq _020378BC
	b _020378C4
_020378B4:
	ldr r1, _020378F0 ; =0x020F2BC8
	ldr r0, _020378F4 ; =0x02105DB8
	str r1, [r0, #0x0]
	b _020378C8
_020378BC:
	ldr r1, _020378F8 ; =0x020F2BC4
	ldr r0, _020378F4 ; =0x02105DB8
	str r1, [r0, #0x0]
	b _020378C8
_020378C4:
	bl ErrorHandling
_020378C8:
	ldr r1, _020378F4 ; =0x02105DB8
	add r0, r6, #0x0
	ldr r1, [r1, #0x0]
	mov r2, #0x20
	bl FUN_0206EFEC
	add r3, r5, #0x0
	add r3, #0x94
	ldr r1, [r5, #0xc]
	ldr r3, [r3, #0x0]
	add r4, r0, #0x0
	mov r2, #0x3
	bl FUN_0206E314
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0203781C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_020378F0: .word 0x020F2BC8
_020378F4: .word 0x02105DB8
_020378F8: .word 0x020F2BC4

	thumb_func_start FUN_020378FC
FUN_020378FC: ; 0x020378FC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0206E37C
	add r4, r0, #0x0
	beq _02037916
	add r0, r5, #0x0
	bl FUN_0206E384
	cmp r0, #0x5
	bne _02037916
	bl ErrorHandling
_02037916:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203791C
FUN_0203791C: ; 0x0203791C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02037940 ; =0x020F2D44
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02037940: .word 0x020F2D44

	thumb_func_start FUN_02037944
FUN_02037944: ; 0x02037944
	push {r3-r5, lr}
	sub sp, #0x10
	ldr r4, _02037968 ; =0x020F2D24
	add r3, sp, #0x0
	add r5, r0, #0x0
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r1, r2, #0x0
	ldr r2, [r5, #0xc]
	add r0, r5, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02037968: .word 0x020F2D24

	thumb_func_start FUN_0203796C
FUN_0203796C: ; 0x0203796C
	ldr r3, _02037974 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037978 ; =0x020FA6E8
	bx r3
	.balign 4
_02037974: .word FUN_020373D4
_02037978: .word 0x020FA6E8

	thumb_func_start FUN_0203797C
FUN_0203797C: ; 0x0203797C
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x40
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x40
	bl MIi_CpuClearFast
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl FUN_02025838
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0xc]
	add r0, r4, #0x0
	add r0, #0x21
	strb r6, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x20
	strb r7, [r0, #0x0]
	str r5, [r4, #0x1c]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020379C8
FUN_020379C8: ; 0x020379C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r2, #0x0
	add r6, r1, #0x0
	mov r0, #0xb
	add r1, r5, #0x0
	add r3, r2, #0x0
	bl FUN_0203797C
	add r4, r0, #0x0
	str r6, [r4, #0x18]
	add r0, #0x22
	strb r7, [r0, #0x0]
	ldr r1, _020379F4 ; =0x020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	nop
_020379F4: .word 0x020F96DC

	thumb_func_start FUN_020379F8
FUN_020379F8: ; 0x020379F8
	push {r3-r5, lr}
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0x3
	add r5, r1, #0x0
	bl FUN_0203797C
	add r4, r0, #0x0
	ldr r1, _02037A18 ; =0x020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02037A18: .word 0x020F96DC

	thumb_func_start FUN_02037A1C
FUN_02037A1C: ; 0x02037A1C
	push {r3-r5, lr}
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0x13
	add r5, r1, #0x0
	bl FUN_0203797C
	add r4, r0, #0x0
	ldr r1, _02037A3C ; =0x020F96DC
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_02037A3C: .word 0x020F96DC

	thumb_func_start FUN_02037A40
FUN_02037A40: ; 0x02037A40
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02037A48
FUN_02037A48: ; 0x02037A48
	push {r4-r6, lr}
	add r4, r2, #0x0
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0x12
	add r5, r1, #0x0
	bl FUN_0203797C
	add r6, r0, #0x0
	add r0, #0x22
	strb r4, [r0, #0x0]
	ldr r1, _02037A6C ; =0x020F96DC
	add r0, r5, #0x0
	add r2, r6, #0x0
	bl FUN_020373D4
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037A6C: .word 0x020F96DC

	thumb_func_start FUN_02037A70
FUN_02037A70: ; 0x02037A70
	add r0, #0x23
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02037A78
FUN_02037A78: ; 0x02037A78
	ldrb r0, [r0, #0x14]
	bx lr

	thumb_func_start FUN_02037A7C
FUN_02037A7C: ; 0x02037A7C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046530
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x4
	bhi _02037B3A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02037AA8: ; jump table (using 16-bit offset)
	.short _02037AB2 - _02037AA8 - 2; case 0
	.short _02037AC2 - _02037AA8 - 2; case 1
	.short _02037AF8 - _02037AA8 - 2; case 2
	.short _02037B1A - _02037AA8 - 2; case 3
	.short _02037B30 - _02037AA8 - 2; case 4
_02037AB2:
	ldr r1, _02037B40 ; =0x020F96DC
	ldr r2, [r4, #0x4]
	add r0, r6, #0x0
	bl FUN_020373D4
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02037B3A
_02037AC2:
	add r0, r6, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _02037B3A
	ldr r0, [r4, #0x4]
	add r0, #0x22
	ldrb r0, [r0, #0x0]
	cmp r0, #0x6
	beq _02037AE6
	cmp r0, #0x7
	bne _02037AF2
	mov r0, #0x2
	bl FUN_020527D8
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02037B3A
_02037AE6:
	mov r0, #0x1
	bl FUN_020527D8
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02037B3A
_02037AF2:
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02037B3A
_02037AF8:
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	mov r2, #0x0
	bl FUN_02037C7C
	str r0, [r4, #0x8]
	ldr r1, [r4, #0x4]
	add r1, #0x22
	ldrb r1, [r1, #0x0]
	strb r1, [r0, #0x14]
	ldr r1, [r4, #0x8]
	add r0, r6, #0x0
	bl FUN_0203796C
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _02037B3A
_02037B1A:
	add r0, r6, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _02037B3A
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r5, #0x0]
	b _02037B3A
_02037B30:
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r4-r6, pc}
_02037B3A:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02037B40: .word 0x020F96DC

	thumb_func_start FUN_02037B44
FUN_02037B44: ; 0x02037B44
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xc
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x0
	mov r3, #0x2
	str r5, [r4, #0x0]
	bl FUN_0203797C
	add r5, r0, #0x0
	add r0, #0x32
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	add r2, r4, #0x0
	bic r1, r0
	mov r0, #0x2
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x32
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x20
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x32
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1e
	add r0, #0x33
	strb r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x14]
	ldr r1, _02037BAC ; =FUN_02037A7C
	add r0, r7, #0x0
	str r5, [r4, #0x4]
	bl FUN_0204640C
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_02037BAC: .word FUN_02037A7C

	thumb_func_start FUN_02037BB0
FUN_02037BB0: ; 0x02037BB0
	push {r3-r7, lr}
	add r5, r2, #0x0
	add r6, r3, #0x0
	mov r0, #0xb
	mov r2, #0x0
	mov r3, #0xd
	add r7, r1, #0x0
	bl FUN_0203797C
	add r4, r0, #0x0
	ldr r1, [sp, #0x1c]
	add r0, #0x22
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x2
	add r0, #0x29
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x2a
	strb r5, [r0, #0x0]
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bne _02037BE6
	add r0, r4, #0x0
	add r0, #0x2b
	strb r6, [r0, #0x0]
	b _02037BEE
_02037BE6:
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x2b
	strb r1, [r0, #0x0]
_02037BEE:
	ldr r1, _02037BFC ; =0x020F96DC
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_02037BFC: .word 0x020F96DC

	thumb_func_start FUN_02037C00
FUN_02037C00: ; 0x02037C00
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r0, #0xb
	mov r1, #0x30
	add r6, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	strb r6, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9AC
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0xc]
	bl FUN_0202A918
	str r0, [r4, #0x20]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB28
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	str r0, [r4, #0x2c]
	mov r0, #0x0
	str r0, [r4, #0x28]
	ldr r1, _02037C74 ; =0x020F2A9C
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0207C2A4
	ldr r1, _02037C78 ; =0x020FA6E8
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037C74: .word 0x020F2A9C
_02037C78: .word 0x020FA6E8

	thumb_func_start FUN_02037C7C
FUN_02037C7C: ; 0x02037C7C
	push {r4-r6, lr}
	ldr r5, [r0, #0xc]
	add r0, r1, #0x0
	mov r1, #0x30
	add r6, r2, #0x0
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl LoadPlayerDataAddress
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0206BB1C
	str r0, [r4, #0x0]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	mov r0, #0x0
	strb r0, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9AC
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	strb r6, [r4, #0x12]
	add r0, r5, #0x0
	bl FUN_0206BB28
	str r0, [r4, #0x1c]
	add r0, r5, #0x0
	bl FUN_02079C70
	str r0, [r4, #0x2c]
	add r0, r5, #0x0
	bl FUN_0202A918
	str r0, [r4, #0x20]
	ldr r1, _02037CEC ; =0x020F2BD0
	add r0, r4, #0x0
	bl FUN_0207B000
	add r0, r5, #0x0
	bl FUN_020238F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0207C2A4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037CEC: .word 0x020F2BD0

	thumb_func_start FUN_02037CF0
FUN_02037CF0: ; 0x02037CF0
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r1, #0x30
	add r6, r2, #0x0
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl memset
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	strb r6, [r4, #0x14]
	strb r0, [r4, #0x13]
	mov r0, #0x0
	strh r0, [r4, #0x18]
	mov r0, #0x2
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB28
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	str r0, [r4, #0x2c]
	ldr r1, _02037D58 ; =0x020F2BCC
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0207C2A4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0203796C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02037D58: .word 0x020F2BCC

	thumb_func_start FUN_02037D5C
FUN_02037D5C: ; 0x02037D5C
	ldrb r0, [r0, #0x16]
	bx lr

	thumb_func_start FUN_02037D60
FUN_02037D60: ; 0x02037D60
	ldr r3, _02037D68 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037D6C ; =0x020F2CF4
	bx r3
	.balign 4
_02037D68: .word FUN_020373D4
_02037D6C: .word 0x020F2CF4

	thumb_func_start FUN_02037D70
FUN_02037D70: ; 0x02037D70
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046528
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02037D9A
	cmp r1, #0x1
	beq _02037DA8
	cmp r1, #0x2
	beq _02037DB8
	b _02037E12
_02037D9A:
	ldr r1, [r5, #0xc]
	bl FUN_02037E80
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02037E12
_02037DA8:
	bl FUN_0204647C
	cmp r0, #0x0
	bne _02037E12
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02037E12
_02037DB8:
	ldr r0, [r5, #0xc]
	bl FUN_020853E4
	cmp r0, #0x0
	bne _02037DCC
	ldr r0, [r5, #0xc]
	bl FUN_020853E8
	cmp r0, #0x0
	bne _02037DD4
_02037DCC:
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	strh r1, [r0, #0x0]
	b _02037E00
_02037DD4:
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	ldr r0, [r5, #0xc]
	bne _02037DEC
	bl FUN_020853EC
	ldr r1, [r5, #0x4]
	strh r0, [r1, #0x0]
	b _02037E00
_02037DEC:
	add r1, sp, #0x0
	bl FUN_020853F0
	add r0, sp, #0x0
	ldrh r2, [r0, #0x0]
	ldr r1, [r5, #0x4]
	strh r2, [r1, #0x0]
	ldrh r1, [r0, #0x2]
	ldr r0, [r5, #0x8]
	strh r1, [r0, #0x0]
_02037E00:
	ldr r0, [r5, #0xc]
	bl FUN_020853A8
	add r0, r5, #0x0
	bl FUN_02016A18
	add sp, #0x4
	mov r0, #0x1
	pop {r3-r6, pc}
_02037E12:
	mov r0, #0x0
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_02037E18
FUN_02037E18: ; 0x02037E18
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02046528
	add r7, r0, #0x0
	mov r0, #0x20
	mov r1, #0x10
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0x4]
	cmp r6, #0x0
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
	str r6, [r4, #0x8]
	bne _02037E56
	mov r0, #0x0
	ldr r2, [r7, #0xc]
	add r1, r0, #0x0
	mov r3, #0x20
	bl FUN_02085338
	str r0, [r4, #0xc]
	ldrh r1, [r5, #0x0]
	bl FUN_020853B0
	b _02037E6C
_02037E56:
	ldr r2, [r7, #0xc]
	mov r0, #0x1
	mov r1, #0x0
	mov r3, #0x20
	bl FUN_02085338
	str r0, [r4, #0xc]
	ldrh r1, [r5, #0x0]
	ldrh r2, [r6, #0x0]
	bl FUN_020853B4
_02037E6C:
	ldr r0, [sp, #0x0]
	ldr r1, _02037E7C ; =FUN_02037D70
	add r2, r4, #0x0
	bl FUN_0204640C
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02037E7C: .word FUN_02037D70

	thumb_func_start FUN_02037E80
FUN_02037E80: ; 0x02037E80
	ldr r3, _02037E88 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037E8C ; =0x020F2CE4
	bx r3
	.balign 4
_02037E88: .word FUN_020373D4
_02037E8C: .word 0x020F2CE4

	thumb_func_start FUN_02037E90
FUN_02037E90: ; 0x02037E90
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02037EB4 ; =0x020F2CD4
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02037EB4: .word 0x020F2CD4

	thumb_func_start FUN_02037EB8
FUN_02037EB8: ; 0x02037EB8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02034E30
	bl FUN_02034E0C
	mov r1, #0x5
	mov r0, #0xb
	lsl r1, r1, #0x6
	bl FUN_020169D8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_0205F7A0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02037E90
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02037EE8
FUN_02037EE8: ; 0x02037EE8
	ldr r3, _02037EF0 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037EF4 ; =0x020F2CC4
	bx r3
	.balign 4
_02037EF0: .word FUN_020373D4
_02037EF4: .word 0x020F2CC4

	thumb_func_start FUN_02037EF8
FUN_02037EF8: ; 0x02037EF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x2
	bl FUN_020169D8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020377AC
	bl LoadPlayerDataAddress
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02037EE8
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02037F1C
FUN_02037F1C: ; 0x02037F1C
	ldr r3, _02037F24 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037F28 ; =0x020FCAC8
	bx r3
	.balign 4
_02037F24: .word FUN_020373D4
_02037F28: .word 0x020FCAC8

	thumb_func_start FUN_02037F2C
FUN_02037F2C: ; 0x02037F2C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_020377AC
	mov r1, #0xb
	str r1, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl FUN_020854E0
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02037F1C
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02037F58
FUN_02037F58: ; 0x02037F58
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r7, r0, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	cmp r5, #0x3
	bne _02037F74
	bl FUN_020377AC
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020855B0
	b _02037F82
_02037F74:
	bl FUN_020377AC
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02085538
_02037F82:
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02037F1C
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02037F90
FUN_02037F90: ; 0x02037F90
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	bl FUN_020377AC
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02085578
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02037F1C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02037FB4
FUN_02037FB4: ; 0x02037FB4
	ldr r3, _02037FBC ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02037FC0 ; =0x020FD1B0
	bx r3
	.balign 4
_02037FBC: .word FUN_020373D4
_02037FC0: .word 0x020FD1B0

	thumb_func_start FUN_02037FC4
FUN_02037FC4: ; 0x02037FC4
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	bl FUN_020377AC
	add r1, r5, #0x0
	bl FUN_02087D00
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02037FB4
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02037FE4
FUN_02037FE4: ; 0x02037FE4
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02038008 ; =0x020F2CB4
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02038008: .word 0x020F2CB4

	thumb_func_start FUN_0203800C
FUN_0203800C: ; 0x0203800C
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x20
	add r7, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x20
	add r4, r0, #0x0
	bl memset
	add r0, r5, #0x0
	bl FUN_0206BB1C
	add r1, r7, #0x0
	bl FUN_0206B9B0
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_02027E24
	str r0, [sp, #0x0]
	mov r1, #0x0
	bl FUN_02027008
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_0202708C
	str r7, [r4, #0x4]
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl LoadPlayerDataAddress
	str r0, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_02029FC8
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	bl FUN_020238F4
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0x18]
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02038070
FUN_02038070: ; 0x02038070
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0203808E
	cmp r0, #0x1
	beq _0203809E
	b _020380C8
_0203808E:
	ldr r1, [r5, #0xc]
	add r0, r4, #0x0
	bl FUN_0203811C
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _020380C8
_0203809E:
	add r0, r4, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _020380C8
	ldr r0, [r5, #0x8]
	cmp r0, #0x1
	bne _020380B2
	mov r1, #0x1
	b _020380B4
_020380B2:
	mov r1, #0x0
_020380B4:
	ldr r0, [r5, #0x4]
	strh r1, [r0, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_02016A18
	add r0, r5, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_020380C8:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_020380CC
FUN_020380CC: ; 0x020380CC
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x20
	mov r1, #0x10
	add r7, r2, #0x0
	str r3, [sp, #0x4]
	bl FUN_02016998
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x10
	mov r0, #0x0
_020380E8:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _020380E8
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	add r3, r4, #0x0
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x4]
	mov r0, #0x20
	add r3, #0x8
	bl FUN_0203800C
	str r0, [r4, #0xc]
	ldr r1, _02038118 ; =FUN_02038070
	add r0, r6, #0x0
	add r2, r4, #0x0
	str r5, [r4, #0x4]
	bl FUN_0204640C
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02038118: .word FUN_02038070

	thumb_func_start FUN_0203811C
FUN_0203811C: ; 0x0203811C
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _0203812C ; =0x02105DDC
	bl FUN_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_0203812C: .word 0x02105DDC

	thumb_func_start FUN_02038130
FUN_02038130: ; 0x02038130
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _02038140 ; =0x02105DCC
	bl FUN_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_02038140: .word 0x02105DCC

	thumb_func_start FUN_02038144
FUN_02038144: ; 0x02038144
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_020238F4
	str r0, [r5, #0x4]
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	str r0, [r5, #0x8]
	ldr r0, [r4, #0xc]
	mov r1, #0x9
	bl FUN_02022610
	str r0, [r5, #0xc]
	ldr r0, [r4, #0xc]
	bl FUN_02029AFC
	str r0, [r5, #0x14]
	ldr r0, [r4, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r5, #0x18]
	ldr r0, [r4, #0xc]
	bl FUN_02024DA0
	str r0, [r5, #0x24]
	ldr r0, [r4, #0xc]
	bl FUN_0206BB28
	str r0, [r5, #0x30]
	ldr r0, [r4, #0xc]
	str r0, [r5, #0x10]
	add r0, r4, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	str r0, [r5, #0x1c]
	ldr r0, [r4, #0xc]
	bl FUN_02029FC8
	str r0, [r5, #0x20]
	bl FUN_02023924
	add r1, r0, #0x0
	mov r0, #0x20
	bl FUN_02016998
	str r0, [r5, #0x38]
	bl FUN_020690C4
	add r1, r0, #0x0
	mov r0, #0x20
	bl FUN_02016998
	str r0, [r5, #0x3c]
	bl FUN_020690C4
	add r1, r0, #0x0
	mov r0, #0x20
	bl FUN_02016998
	str r0, [r5, #0x40]
	str r4, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x34]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020381CC
FUN_020381CC: ; 0x020381CC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x38]
	cmp r0, #0x0
	beq _020381DE
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x38]
_020381DE:
	ldr r0, [r4, #0x3c]
	cmp r0, #0x0
	beq _020381EC
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x3c]
_020381EC:
	ldr r0, [r4, #0x40]
	cmp r0, #0x0
	beq _020381FA
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x40]
_020381FA:
	pop {r4, pc}

	thumb_func_start FUN_020381FC
FUN_020381FC: ; 0x020381FC
	push {r4-r7, lr}
	sub sp, #0x34
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x7
	bls _02038218
	b _020383C8
_02038218:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02038224: ; jump table (using 16-bit offset)
	.short _02038234 - _02038224 - 2; case 0
	.short _0203824A - _02038224 - 2; case 1
	.short _02038258 - _02038224 - 2; case 2
	.short _0203826A - _02038224 - 2; case 3
	.short _02038288 - _02038224 - 2; case 4
	.short _020382F6 - _02038224 - 2; case 5
	.short _02038386 - _02038224 - 2; case 6
	.short _020383B2 - _02038224 - 2; case 7
_02038234:
	bl FUN_02033590
	cmp r0, #0x0
	bne _02038242
	add r0, r6, #0x0
	bl FUN_0204AF3C
_02038242:
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020383C8
_0203824A:
	add r0, r4, #0x4
	add r1, r5, #0x0
	bl FUN_02038144
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
_02038258:
	ldr r1, _020383D0 ; =0x02105DBC
	add r0, r6, #0x0
	add r2, r4, #0x4
	bl FUN_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020383C8
_0203826A:
	ldr r1, [r4, #0x2c]
	cmp r1, #0x0
	bne _02038282
	add r0, r4, #0x4
	bl FUN_020381CC
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x34
	mov r0, #0x1
	pop {r4-r7, pc}
_02038282:
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020383C8
_02038288:
	ldr r0, [r4, #0x3c]
	str r0, [r4, #0x50]
	ldr r0, [r4, #0x40]
	bl FUN_020690E4
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x44]
	bl FUN_020690E4
	str r0, [r4, #0x4c]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x5c]
	mov r0, #0x1
	str r0, [r4, #0x58]
	add r0, r5, #0x0
	bl FUN_0204B2A4
	cmp r0, #0x4
	bhi _020382C8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020382BE: ; jump table (using 16-bit offset)
	.short _020382C8 - _020382BE - 2; case 0
	.short _020382C8 - _020382BE - 2; case 1
	.short _020382CE - _020382BE - 2; case 2
	.short _020382D4 - _020382BE - 2; case 3
	.short _020382D4 - _020382BE - 2; case 4
_020382C8:
	mov r0, #0x0
	str r0, [r4, #0x54]
	b _020382D8
_020382CE:
	mov r0, #0x1
	str r0, [r4, #0x54]
	b _020382D8
_020382D4:
	mov r0, #0x2
	str r0, [r4, #0x54]
_020382D8:
	bl FUN_02033590
	cmp r0, #0x0
	beq _020382E4
	mov r0, #0x3
	str r0, [r4, #0x54]
_020382E4:
	add r2, r4, #0x0
	ldr r1, _020383D4 ; =0x020F2CA4
	add r0, r6, #0x0
	add r2, #0x48
	bl FUN_02046500
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _020383C8
_020382F6:
	ldr r0, [r4, #0x44]
	mov r1, #0x6
	mov r2, #0x0
	bl FUN_020671BC
	add r3, r0, #0x0
	add r0, sp, #0x30
	str r0, [sp, #0x0]
	lsl r3, r3, #0x10
	ldr r1, [r4, #0x44]
	mov r0, #0x0
	mov r2, #0x1
	lsr r3, r3, #0x10
	bl FUN_02069168
	str r0, [sp, #0x20]
	cmp r0, #0x0
	beq _02038380
	mov r0, #0x3
	mov r1, #0x1a
	lsl r2, r0, #0x10
	bl FUN_0201681C
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [sp, #0x24]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	add r7, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	str r0, [sp, #0x28]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0xc]
	bl FUN_0204C1A8
	str r6, [sp, #0x0]
	ldr r1, [sp, #0x28]
	str r7, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x20]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x30]
	ldr r3, [sp, #0x24]
	str r0, [sp, #0x14]
	mov r0, #0x4
	str r0, [sp, #0x18]
	mov r0, #0x1a
	str r0, [sp, #0x1c]
	ldr r1, [r4, #0x44]
	mov r0, #0x0
	bl FUN_0206C700
	str r0, [r4, #0x60]
	mov r0, #0x6
	str r0, [r4, #0x0]
	b _020383C8
_02038380:
	mov r0, #0x7
	str r0, [r4, #0x0]
	b _020383C8
_02038386:
	ldr r0, [r4, #0x60]
	bl FUN_0206C91C
	cmp r0, #0x0
	beq _020383C8
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x30]
	bl FUN_0206B9B0
	add r1, r0, #0x0
	ldr r0, [r4, #0x44]
	bl FUN_02069B88
	ldr r0, [r4, #0x60]
	bl FUN_0206C92C
	mov r0, #0x1a
	bl FUN_020168D0
	mov r0, #0x7
	str r0, [r4, #0x0]
	b _020383C8
_020383B2:
	ldr r0, [r4, #0x38]
	add r0, r0, #0x1
	str r0, [r4, #0x38]
	mov r0, #0x2
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	mov r1, #0x10
	bl FUN_0202A170
_020383C8:
	mov r0, #0x0
	add sp, #0x34
	pop {r4-r7, pc}
	nop
_020383D0: .word 0x02105DBC
_020383D4: .word 0x020F2CA4

	thumb_func_start FUN_020383D8
FUN_020383D8: ; 0x020383D8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x20
	mov r1, #0x68
	bl FUN_02016998
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	ldr r1, _020383F4 ; =FUN_020381FC
	add r0, r4, #0x0
	bl FUN_0204640C
	pop {r4, pc}
	.balign 4
_020383F4: .word FUN_020381FC

	thumb_func_start FUN_020383F8
FUN_020383F8: ; 0x020383F8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	mov r1, #0xc
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0x7c]
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x8]
	ldr r1, _02038428 ; =0x020F2C94
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	pop {r3-r5, pc}
	nop
_02038428: .word 0x020F2C94

	thumb_func_start FUN_0203842C
FUN_0203842C: ; 0x0203842C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	mov r1, #0x14
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x7c]
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	str r0, [r4, #0xc]
	add r0, r5, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	ldr r1, _02038468 ; =0x020F2D04
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02038468: .word 0x020F2D04

	thumb_func_start FUN_0203846C
FUN_0203846C: ; 0x0203846C
	ldr r3, _02038474 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02038478 ; =0x020F2D54
	bx r3
	.balign 4
_02038474: .word FUN_020373D4
_02038478: .word 0x020F2D54

	thumb_func_start FUN_0203847C
FUN_0203847C: ; 0x0203847C
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x3
	bhi _02038544
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020384A0: ; jump table (using 16-bit offset)
	.short _020384A8 - _020384A0 - 2; case 0
	.short _020384B6 - _020384A0 - 2; case 1
	.short _020384C8 - _020384A0 - 2; case 2
	.short _020384D6 - _020384A0 - 2; case 3
_020384A8:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02038544
_020384B6:
	ldr r1, _02038548 ; =0x020FA5FC
	ldr r2, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02038544
_020384C8:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _02038544
_020384D6:
	ldr r1, [r4, #0xc]
	ldr r0, [r1, #0x0]
	cmp r0, #0x1
	bne _020384F2
	ldr r0, [r1, #0x18]
	ldr r1, [r4, #0x10]
	bl FUN_02021CE0
	cmp r0, #0x0
	bne _02038514
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	str r1, [r0, #0x14]
	b _02038514
_020384F2:
	cmp r0, #0x5
	bne _02038514
	ldr r0, [r1, #0x18]
	bl FUN_02021F2C
	add r7, r0, #0x0
	ldr r0, [r6, #0xc]
	bl FUN_0202881C
	add r1, r7, #0x0
	bl FUN_02028854
	cmp r0, #0x0
	beq _02038514
	ldr r0, [r4, #0xc]
	mov r1, #0x2
	str r1, [r0, #0x14]
_02038514:
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x14]
	cmp r0, #0x0
	bne _02038522
	add r0, r5, #0x0
	bl FUN_0203854C
_02038522:
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _0203852E
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x14]
	strh r0, [r1, #0x0]
_0203852E:
	ldr r0, [r4, #0xc]
	bl FUN_02077AC4
	ldr r0, [r4, #0x10]
	bl FUN_02021A20
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r7, pc}
_02038544:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02038548: .word 0x020FA5FC

	thumb_func_start FUN_0203854C
FUN_0203854C: ; 0x0203854C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x0]
	cmp r0, #0x6
	bhi _020385CA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02038572: ; jump table (using 16-bit offset)
	.short _02038580 - _02038572 - 2; case 0
	.short _02038590 - _02038572 - 2; case 1
	.short _020385CA - _02038572 - 2; case 2
	.short _020385CA - _02038572 - 2; case 3
	.short _020385CA - _02038572 - 2; case 4
	.short _020385A8 - _02038572 - 2; case 5
	.short _020385BC - _02038572 - 2; case 6
_02038580:
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	ldr r1, [r4, #0xc]
	add r1, #0x1c
	bl FUN_0202395C
	pop {r3-r5, pc}
_02038590:
	ldr r0, [r5, #0xc]
	bl FUN_0206BB1C
	ldr r1, [r4, #0x4]
	bl FUN_0206B9B0
	ldr r2, [r4, #0xc]
	mov r1, #0x75
	add r2, #0x1c
	bl FUN_02067830
	pop {r3-r5, pc}
_020385A8:
	ldr r0, [r5, #0xc]
	bl FUN_0202881C
	ldr r3, [r4, #0xc]
	mov r1, #0x0
	ldr r3, [r3, #0x18]
	add r2, r1, #0x0
	bl FUN_020287C0
	pop {r3-r5, pc}
_020385BC:
	ldr r0, [r5, #0xc]
	bl FUN_02024EB4
	ldr r1, [r4, #0xc]
	ldr r1, [r1, #0x18]
	bl FUN_02024F18
_020385CA:
	pop {r3-r5, pc}

	thumb_func_start FUN_020385CC
FUN_020385CC: ; 0x020385CC
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x4]
	add r6, r1, #0x0
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	ldr r5, [sp, #0x2c]
	bl FUN_02046528
	add r7, r0, #0x0
	mov r0, #0xb
	mov r1, #0x14
	bl FUN_020169D8
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x28]
	str r0, [r4, #0x4]
	ldr r0, [sp, #0x30]
	str r0, [r4, #0x8]
	ldr r0, [r7, #0xc]
	bl LoadPlayerDataAddress
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r0, #0xb
	add r1, r6, #0x0
	bl FUN_02077A84
	str r0, [r4, #0xc]
	mov r0, #0xc
	mov r1, #0xb
	bl FUN_020219F4
	str r0, [r4, #0x10]
	cmp r6, #0x1
	beq _02038620
	cmp r6, #0x5
	beq _02038656
	b _02038660
_02038620:
	ldr r0, [r7, #0xc]
	bl FUN_0206BB1C
	ldr r1, [r4, #0x4]
	bl FUN_0206B9B0
	mov r1, #0x6f
	mov r2, #0x0
	add r6, r0, #0x0
	bl FUN_020671BC
	ldr r1, [r4, #0xc]
	mov r2, #0x0
	str r0, [r1, #0x10]
	add r0, r6, #0x0
	mov r1, #0x70
	bl FUN_020671BC
	ldr r1, [r4, #0xc]
	cmp r5, #0x0
	str r0, [r1, #0x8]
	beq _0203866E
	ldr r0, [r4, #0x10]
	add r1, r5, #0x0
	bl FUN_02021E28
	b _0203866E
_02038656:
	ldr r0, [r4, #0x10]
	add r1, r5, #0x0
	bl FUN_02021E28
	b _0203866E
_02038660:
	cmp r5, #0x0
	beq _0203866E
	ldr r0, [r4, #0xc]
	add r1, r5, #0x0
	ldr r0, [r0, #0x18]
	bl FUN_02021E28
_0203866E:
	ldr r0, [sp, #0x4]
	ldr r1, _0203867C ; =FUN_0203847C
	add r2, r4, #0x0
	bl FUN_0204640C
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0203867C: .word FUN_0203847C

	thumb_func_start FUN_02038680
FUN_02038680: ; 0x02038680
	ldr r3, _02038688 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _0203868C ; =0x020F2C54
	bx r3
	.balign 4
_02038688: .word FUN_020373D4
_0203868C: .word 0x020F2C54

	thumb_func_start FUN_02038690
FUN_02038690: ; 0x02038690
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _020386A0 ; =0x020F2C44
	bl FUN_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_020386A0: .word 0x020F2C44

	thumb_func_start FUN_020386A4
FUN_020386A4: ; 0x020386A4
	ldr r3, _020386AC ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _020386B0 ; =0x020F2C34
	bx r3
	.balign 4
_020386AC: .word FUN_020373D4
_020386B0: .word 0x020F2C34

	thumb_func_start FUN_020386B4
FUN_020386B4: ; 0x020386B4
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_02029ABC
	ldr r5, _020386DC ; =0x020F2C24
	add r3, sp, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r1, r2, #0x0
	ldr r2, [r4, #0xc]
	add r0, r4, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_020386DC: .word 0x020F2C24

	thumb_func_start FUN_020386E0
FUN_020386E0: ; 0x020386E0
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r3, _0203878C ; =0x020F2C64
	add r2, sp, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0xb
	mov r1, #0x44
	bl FUN_020169D8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202ABBC
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_02023788
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	mov r1, #0x2
	bl FUN_02022610
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl FUN_02022510
	str r0, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl FUN_020286EC
	str r0, [r4, #0x14]
	ldr r0, [r5, #0xc]
	bl FUN_02029AFC
	str r0, [r4, #0x18]
	ldr r0, [r5, #0xc]
	bl FUN_020238F4
	str r0, [r4, #0x1c]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x24]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	str r0, [r4, #0x28]
	add r0, r5, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	str r0, [r4, #0x2c]
	ldr r0, [r5, #0xc]
	bl FUN_02079C70
	str r0, [r4, #0x3c]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x20]
	ldr r0, [r5, #0xc]
	bl FUN_0206BB28
	str r0, [r4, #0x34]
	ldr r0, [r4, #0x14]
	bl FUN_02033830
	str r0, [r4, #0x38]
	ldr r0, [r5, #0xc]
	bl FUN_0206F158
	str r0, [r4, #0x30]
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r4, #0x0
	str r6, [r4, #0x40]
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_0203878C: .word 0x020F2C64

	thumb_func_start FUN_02038790
FUN_02038790: ; 0x02038790
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r3, _02038800 ; =0x020F2C74
	add r7, r2, #0x0
	add r2, sp, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0xb
	mov r1, #0x28
	bl FUN_020169D8
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0202A8D8
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0202A8E4
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	bl FUN_02023788
	str r0, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl FUN_020286EC
	bl FUN_02028228
	str r0, [r4, #0x14]
	ldr r0, [r5, #0xc]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl FUN_020286EC
	bl FUN_02033830
	str r0, [r4, #0x1c]
	str r6, [r4, #0x18]
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r4, #0x0
	str r7, [r4, #0x24]
	bl FUN_020373D4
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02038800: .word 0x020F2C74

	thumb_func_start FUN_02038804
FUN_02038804: ; 0x02038804
	ldr r3, _0203880C ; =FUN_020373D4
	ldr r1, _02038810 ; =0x020F2D14
	ldr r2, [r0, #0xc]
	bx r3
	.balign 4
_0203880C: .word FUN_020373D4
_02038810: .word 0x020F2D14

	thumb_func_start FUN_02038814
FUN_02038814: ; 0x02038814
	ldr r3, _0203881C ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02038820 ; =0x020F2D64
	bx r3
	.balign 4
_0203881C: .word FUN_020373D4
_02038820: .word 0x020F2D64

	thumb_func_start FUN_02038824
FUN_02038824: ; 0x02038824
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	mov r1, #0xb
	add r2, sp, #0x0
	bl FUN_02022534
	ldr r1, [sp, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x2
	bne _02038842
	bl FUN_02016A18
	mov r0, #0x0
	pop {r3-r5, pc}
_02038842:
	ldr r1, _02038850 ; =0x020F2BF4
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02038850: .word 0x020F2BF4

	thumb_func_start FUN_02038854
FUN_02038854: ; 0x02038854
	ldr r3, _0203885C ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _02038860 ; =0x020F2C04
	bx r3
	.balign 4
_0203885C: .word FUN_020373D4
_02038860: .word 0x020F2C04

	thumb_func_start FUN_02038864
FUN_02038864: ; 0x02038864
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _02038888 ; =0x020F2C84
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02038888: .word 0x020F2C84

	thumb_func_start FUN_0203888C
FUN_0203888C: ; 0x0203888C
	push {r4-r6, lr}
	sub sp, #0x10
	ldr r5, _020388B0 ; =0x020F2D84
	add r4, sp, #0x0
	add r6, r0, #0x0
	add r2, r1, #0x0
	add r3, r4, #0x0
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r4!, {r0-r1}
	add r0, r6, #0x0
	add r1, r3, #0x0
	bl FUN_020373D4
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_020388B0: .word 0x020F2D84

	thumb_func_start FUN_020388B4
FUN_020388B4: ; 0x020388B4
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206BB1C
	bl MOD05_021ED49C
	add r5, r0, #0x0
	bne _020388CC
	bl ErrorHandling
_020388CC:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020613CC
	str r5, [sp, #0x0]
	ldr r0, [r4, #0xc]
	bl LoadPlayerDataAddress
	str r0, [sp, #0x4]
	ldr r0, [r4, #0xc]
	bl FUN_020238F4
	str r0, [sp, #0x8]
	ldr r1, [r4, #0x1c]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_0204AB58
	add r1, sp, #0x0
	strh r0, [r1, #0xc]
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020863DC
	add sp, #0x10
	pop {r3-r5, pc}

	thumb_func_start FUN_02038900
FUN_02038900: ; 0x02038900
	push {r3, lr}
	add r2, r1, #0x0
	ldr r1, _02038910 ; =0x020F2C14
	bl FUN_020373D4
	mov r0, #0x1
	pop {r3, pc}
	nop
_02038910: .word 0x020F2C14

	thumb_func_start FUN_02038914
FUN_02038914: ; 0x02038914
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_020462AC
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02046530
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _02038944
	cmp r0, #0x1
	beq _02038956
	b _020389C6
_02038944:
	add r5, #0xc
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02038900
	ldr r0, [r6, #0x0]
	add r0, r0, #0x1
	str r0, [r6, #0x0]
	b _020389C6
_02038956:
	add r0, r4, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _020389C6
	ldr r0, [r4, #0xc]
	bl FUN_0202390C
	str r0, [sp, #0x0]
	bl FUN_020126FC
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	add r6, r1, #0x0
	bl FUN_02028930
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0x8]
	ldr r2, [sp, #0x4]
	add r3, r6, #0x0
	bl FUN_020127C0
	mov r2, #0x3c
	mov r3, #0x0
	bl _ll_sdiv
	add r3, r0, #0x0
	ldr r1, [sp, #0x8]
	ldr r2, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02061A8C
	ldr r0, [r4, #0xc]
	bl FUN_0202390C
	ldr r1, [r5, #0x0]
	bl FUN_02028918
	add r0, r7, #0x0
	bl FUN_0205F6C8
	ldr r1, [r5, #0x18]
	cmp r1, r0
	ble _020389BA
	lsl r1, r1, #0x10
	add r0, r7, #0x0
	lsr r1, r1, #0x10
	bl FUN_0205F6D8
_020389BA:
	add r0, r5, #0x0
	bl FUN_02016A18
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_020389C6:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_020389CC
FUN_020389CC: ; 0x020389CC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	bl LoadPlayerDataAddress
	str r0, [sp, #0x0]
	mov r0, #0x20
	add r1, r0, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	str r4, [r4, #0xc]
	ldr r0, [r5, #0xc]
	bl FUN_0202390C
	bl FUN_02028930
	str r0, [r4, #0x0]
	bl FUN_020126FC
	str r0, [r4, #0x4]
	str r1, [r4, #0x8]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	str r0, [r4, #0x14]
	mov r0, #0x0
	str r0, [r4, #0x18]
	ldr r0, [sp, #0x0]
	bl FUN_02025084
	str r0, [r4, #0x1c]
	lsl r1, r6, #0x18
	ldr r0, [r5, #0xc]
	lsr r1, r1, #0x18
	bl FUN_02038A3C
	str r0, [r4, #0x10]
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	mov r1, #0x5
	bl FUN_0202A170
	ldr r1, _02038A38 ; =FUN_02038914
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl FUN_0204640C
	pop {r3-r7, pc}
	.balign 4
_02038A38: .word FUN_02038914

	thumb_func_start FUN_02038A3C
FUN_02038A3C: ; 0x02038A3C
	push {r4-r7, lr}
	sub sp, #0x14
	str r1, [sp, #0x0]
	bl FUN_0202881C
	add r4, r0, #0x0
	bl getseed_LC
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_020287A4
	bl seedr_LC
	ldr r0, _02038AAC ; =0x020F2BE8
	add r1, sp, #0x8
	mov r2, #0xc
	bl MI_CpuCopy8
	mov r4, #0x0
	mov r7, #0xc
	add r6, sp, #0x8
_02038A68:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0xc
	bhs _02038A92
_02038A72:
	bl rand_LC
	add r1, r7, #0x0
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r2, r0, #0x18
	ldrb r1, [r6, r4]
	ldrb r0, [r6, r2]
	strb r0, [r6, r4]
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	strb r1, [r6, r2]
	cmp r5, #0xc
	blo _02038A72
_02038A92:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xc
	blo _02038A68
	ldr r0, [sp, #0x4]
	bl seedr_LC
	ldr r0, [sp, #0x0]
	add r1, sp, #0x8
	ldrb r0, [r1, r0]
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02038AAC: .word 0x020F2BE8

	thumb_func_start FUN_02038AB0
FUN_02038AB0: ; 0x02038AB0
	push {r4, lr}
	bl FUN_0204652C
	add r4, r0, #0x0
	bl MOD06_0224D79C
	cmp r0, #0x1
	bne _02038ACA
	add r0, r4, #0x0
	bl MOD06_0224D76C
	mov r0, #0x1
	pop {r4, pc}
_02038ACA:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02038AD0
FUN_02038AD0: ; 0x02038AD0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r2, r0, #0x0
	ldr r1, [r2, #0xc]
	ldr r2, [r2, #0x8]
	mov r0, #0x4
	bl MOD06_0224D70C
	add r2, r0, #0x0
	ldr r1, _02038AF0 ; =FUN_02038AB0
	add r0, r4, #0x0
	bl FUN_0204640C
	pop {r4, pc}
	.balign 4
_02038AF0: .word FUN_02038AB0

	thumb_func_start FUN_02038AF4
FUN_02038AF4: ; 0x02038AF4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x8
	add r6, r2, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	str r6, [r4, #0x4]
	ldr r0, [r5, #0xc]
	ldr r1, _02038B18 ; =0x020F2DA4
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020373D4
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02038B18: .word 0x020F2DA4
