	.include "asm/macros.inc"
    .include "global.inc"

	.extern gGameLanguage
	.extern gGameVersion

	.text

	thumb_func_start FUN_02025658
FUN_02025658: ; 0x02025658
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	strb r0, [r4, #0x4]
	ldr r0, _020256A0 ; =gGameLanguage
	mov r1, #0x8
	ldrb r0, [r0, #0x0]
	strb r0, [r4, #0x5]
	ldr r0, _020256A4 ; =gGameVersion
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
_020256A0: .word gGameLanguage
_020256A4: .word gGameVersion
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
	bl AllocFromHeapAtEnd
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
	bl GetMonDataEncrypted
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonDataEncrypted
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonDataEncrypted
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
