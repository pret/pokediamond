	.include "asm/macros.inc"
    .include "global.inc"

	.text

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
	bl AllocFromHeapAtEnd
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
