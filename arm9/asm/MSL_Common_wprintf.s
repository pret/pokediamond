	.include "asm/macros.inc"
	.include "global.inc"

	.data

wstr$6DE4: ; 0x02106DE4
	; L"0x0p0"
	.short 0x0030, 0x0078, 0x0030, 0x0070, 0x0030, 0x0000

wstr$6DF0: ; 0x02106DF0
	; L"-INF"
	.short 0x002D, 0x0049, 0x004E, 0x0046, 0x0000, 0x0000

wstr$6DFC: ; 0x02106DFC
	; L"-inf"
	.short 0x002D, 0x0069, 0x006E, 0x0066, 0x0000, 0x0000

wstr$6E08: ; 0x02106E08
	; L"INF"
	.short 0x0049, 0x004E, 0x0046, 0x0000

wstr$6E10: ; 0x02106E10
	; L"inf"
	.short 0x0069, 0x006E, 0x0066, 0x0000

wstr$6E18: ; 0x02106E18
	; L"-NAN"
	.short 0x002D, 0x004E, 0x0041, 0x004E, 0x0000, 0x0000

wstr$6E24: ; 0x02106E24
	; L"-nan"
	.short 0x002D, 0x006E, 0x0061, 0x006E, 0x0000, 0x0000

wstr$6E30: ; 0x02106E30
	; L"NAN"
	.short 0x004E, 0x0041, 0x004E, 0x0000

wstr$6E38: ; 0x02106E38
	; L"nan"
	.short 0x006E, 0x0061, 0x006E, 0x0000

buff_ptr$6E40: ; 0x02106E40
	.short 0x0000, 0x0000

strptr$6E44: ; 0x02106E44
	.asciz ""

	.text

	arm_func_start parse_format__wide
parse_format__wide: ; 0x020E50A0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldrh r3, [r0, #0x2]
	mov r4, #0x0
	mov r5, #0x1
	mov lr, r2
	strb r5, [sp, #0x0]
	strb r4, [sp, #0x1]
	strb r4, [sp, #0x2]
	strb r4, [sp, #0x3]
	strb r4, [sp, #0x4]
	str r4, [sp, #0x8]
	str r4, [sp, #0xc]
	cmp r3, #0x25
	add r12, r0, #0x2
	bne _020E50FC
	add r0, sp, #0x0
	strh r3, [sp, #0x6]
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add sp, sp, #0x10
	add r0, r12, #0x2
	ldmia sp!, {r4-r8,pc}
_020E50FC:
	mov r2, #0x2
	mov r0, r4
	mov r5, r2
	mov r6, r4
	mov r7, #0x1
_020E5110:
	mov r8, r7
	cmp r3, #0x2b
	bgt _020E5140
	bge _020E5168
	cmp r3, #0x23
	bgt _020E5198
	cmp r3, #0x20
	blt _020E5198
	beq _020E5170
	cmp r3, #0x23
	beq _020E5180
	b _020E5198
_020E5140:
	cmp r3, #0x30
	bgt _020E5198
	cmp r3, #0x2d
	blt _020E5198
	beq _020E5160
	cmp r3, #0x30
	beq _020E5188
	b _020E5198
_020E5160:
	strb r6, [sp, #0x0]
	b _020E519C
_020E5168:
	strb r7, [sp, #0x1]
	b _020E519C
_020E5170:
	ldrb r4, [sp, #0x1]
	cmp r4, #0x1
	strneb r5, [sp, #0x1]
	b _020E519C
_020E5180:
	strb r7, [sp, #0x3]
	b _020E519C
_020E5188:
	ldrb r4, [sp, #0x0]
	cmp r4, #0x0
	strneb r2, [sp, #0x0]
	b _020E519C
_020E5198:
	mov r8, r0
_020E519C:
	cmp r8, #0x0
	ldrneh r3, [r12, #0x2]!
	bne _020E5110
	cmp r3, #0x2a
	bne _020E51E4
	ldr r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x0]
	ldr r0, [r0, #-0x4]
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bge _020E51DC
	rsb r0, r0, #0x0
	mov r2, #0x0
	strb r2, [sp, #0x0]
	str r0, [sp, #0x8]
_020E51DC:
	ldrh r3, [r12, #0x2]!
	b _020E5228
_020E51E4:
	mov r2, #0x0
	ldr r5, _020E560C ; =__wctype_mapC
	mov r0, #0xa
	b _020E5208
_020E51F4:
	ldr r4, [sp, #0x8]
	sub r3, r3, #0x30
	mla r6, r4, r0, r3
	ldrh r3, [r12, #0x2]!
	str r6, [sp, #0x8]
_020E5208:
	cmp r3, #0x80
	movcs r4, r2
	bhs _020E5220
	mov r4, r3, lsl #0x1
	ldrh r4, [r5, r4]
	and r4, r4, #0x8
_020E5220:
	cmp r4, #0x0
	bne _020E51F4
_020E5228:
	ldr r2, [sp, #0x8]
	ldr r0, _020E5610 ; =0x000001FD
	cmp r2, r0
	ble _020E5258
	ldr r1, _020E5614 ; =0x0000FFFF
	add r0, sp, #0x0
	strh r1, [sp, #0x6]
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add sp, sp, #0x10
	add r0, r12, #0x2
	ldmia sp!, {r4-r8,pc}
_020E5258:
	cmp r3, #0x2e
	bne _020E52E0
	ldrh r3, [r12, #0x2]!
	mov r0, #0x1
	strb r0, [sp, #0x2]
	cmp r3, #0x2a
	bne _020E529C
	ldr r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x0]
	ldr r0, [r0, #-0x4]
	ldrh r3, [r12, #0x2]!
	str r0, [sp, #0xc]
	cmp r0, #0x0
	movlt r0, #0x0
	strltb r0, [sp, #0x2]
	b _020E52E0
_020E529C:
	mov r1, #0x0
	ldr r4, _020E560C ; =__wctype_mapC
	mov r0, #0xa
	b _020E52C0
_020E52AC:
	ldr r2, [sp, #0xc]
	sub r3, r3, #0x30
	mla r5, r2, r0, r3
	ldrh r3, [r12, #0x2]!
	str r5, [sp, #0xc]
_020E52C0:
	cmp r3, #0x80
	movcs r2, r1
	bhs _020E52D8
	mov r2, r3, lsl #0x1
	ldrh r2, [r4, r2]
	and r2, r2, #0x8
_020E52D8:
	cmp r2, #0x0
	bne _020E52AC
_020E52E0:
	cmp r3, #0x6c
	mov r0, #0x1
	bgt _020E5318
	cmp r3, #0x68
	blt _020E530C
	beq _020E5334
	cmp r3, #0x6a
	beq _020E5380
	cmp r3, #0x6c
	beq _020E5350
	b _020E53A4
_020E530C:
	cmp r3, #0x4c
	beq _020E5374
	b _020E53A4
_020E5318:
	cmp r3, #0x74
	bgt _020E5328
	beq _020E538C
	b _020E53A4
_020E5328:
	cmp r3, #0x7a
	beq _020E5398
	b _020E53A4
_020E5334:
	ldrh r1, [r12, #0x2]
	mov r2, #0x2
	strb r2, [sp, #0x4]
	cmp r1, #0x68
	streqb r0, [sp, #0x4]
	ldreqh r3, [r12, #0x2]!
	b _020E53A8
_020E5350:
	ldrh r1, [r12, #0x2]
	mov r2, #0x3
	strb r2, [sp, #0x4]
	cmp r1, #0x6c
	bne _020E53A8
	mov r1, #0x4
	strb r1, [sp, #0x4]
	ldrh r3, [r12, #0x2]!
	b _020E53A8
_020E5374:
	mov r1, #0x9
	strb r1, [sp, #0x4]
	b _020E53A8
_020E5380:
	mov r1, #0x6
	strb r1, [sp, #0x4]
	b _020E53A8
_020E538C:
	mov r1, #0x8
	strb r1, [sp, #0x4]
	b _020E53A8
_020E5398:
	mov r1, #0x7
	strb r1, [sp, #0x4]
	b _020E53A8
_020E53A4:
	mov r0, #0x0
_020E53A8:
	cmp r0, #0x0
	ldrneh r3, [r12, #0x2]!
	strh r3, [sp, #0x6]
	cmp r3, #0x61
	bgt _020E53FC
	bge _020E54E0
	cmp r3, #0x47
	bgt _020E53F0
	subs r0, r3, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020E55EC
	b _020E54E0
	b _020E55EC
	b _020E55EC
	b _020E55EC
	b _020E5528
	b _020E54A8
	b _020E5518
_020E53F0:
	cmp r3, #0x58
	beq _020E5470
	b _020E55EC
_020E53FC:
	cmp r3, #0x63
	bgt _020E540C
	beq _020E5588
	b _020E55EC
_020E540C:
	sub r0, r3, #0x64
	cmp r0, #0x14
	addls pc, pc, r0, lsl #0x2
	b _020E55EC
	b _020E5470 ; case
	b _020E5528 ; case
	b _020E54A8 ; case
	b _020E5518 ; case
	b _020E55EC ; case
	b _020E5470 ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55D8 ; case
	b _020E5470 ; case
	b _020E5564 ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55B4 ; case
	b _020E55EC ; case
	b _020E5470 ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E5470 ; case
_020E5470:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x9
	moveq r0, #0x4
	streqb r0, [sp, #0x4]
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0xc]
	beq _020E55F4
	ldrb r0, [sp, #0x0]
	cmp r0, #0x2
	moveq r0, #0x1
	streqb r0, [sp, #0x0]
	b _020E55F4
_020E54A8:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	ldreq r0, _020E5614 ; =0x0000FFFF
	streqh r0, [sp, #0x6]
	beq _020E55F4
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x6
	streq r0, [sp, #0xc]
	b _020E55F4
_020E54E0:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0xd
	streq r0, [sp, #0xc]
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	cmpne r0, #0x1
	ldreq r0, _020E5614 ; =0x0000FFFF
	streqh r0, [sp, #0x6]
	b _020E55F4
_020E5518:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0xc]
_020E5528:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	cmpne r0, #0x1
	ldreq r0, _020E5614 ; =0x0000FFFF
	streqh r0, [sp, #0x6]
	beq _020E55F4
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x6
	streq r0, [sp, #0xc]
	b _020E55F4
_020E5564:
	mov r3, #0x3
	mov r2, #0x1
	mov r1, #0x78
	mov r0, #0x8
	strb r3, [sp, #0x4]
	strb r2, [sp, #0x3]
	strh r1, [sp, #0x6]
	str r0, [sp, #0xc]
	b _020E55F4
_020E5588:
	ldrb r1, [sp, #0x4]
	cmp r1, #0x3
	moveq r0, #0x5
	streqb r0, [sp, #0x4]
	beq _020E55F4
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	cmpeq r1, #0x0
	ldrne r0, _020E5614 ; =0x0000FFFF
	strneh r0, [sp, #0x6]
	b _020E55F4
_020E55B4:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x3
	moveq r0, #0x5
	streqb r0, [sp, #0x4]
	beq _020E55F4
	cmp r0, #0x0
	ldrne r0, _020E5614 ; =0x0000FFFF
	strneh r0, [sp, #0x6]
	b _020E55F4
_020E55D8:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x9
	moveq r0, #0x4
	streqb r0, [sp, #0x4]
	b _020E55F4
_020E55EC:
	ldr r0, _020E5614 ; =0x0000FFFF
	strh r0, [sp, #0x6]
_020E55F4:
	add r0, sp, #0x0
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add r0, r12, #0x2
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020E560C: .word __wctype_mapC
_020E5610: .word 0x000001FD
_020E5614: .word 0x0000FFFF
	arm_func_end parse_format__wide

	arm_func_start long2str__wide
long2str__wide: ; 0x020E5618
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x10
	movs r10, r0
	mov r0, #0x0
	mov r5, r1
	str r0, [sp, #0xc]
	ldr r7, [sp, #0x4c]
	mov r6, r0
	strh r0, [r5, #-0x2]!
	ldrb r0, [sp, #0x43]
	str r1, [sp, #0x0]
	ldrh r8, [sp, #0x46]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x48]
	ldrb r11, [sp, #0x41]
	str r0, [sp, #0x8]
	cmpeq r7, #0x0
	bne _020E568C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E5678
	cmp r8, #0x6f
	beq _020E568C
_020E5678:
	add sp, sp, #0x10
	mov r0, r5
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E568C:
	cmp r8, #0x69
	bgt _020E56B4
	bge _020E56E8
	cmp r8, #0x58
	bgt _020E56A8
	beq _020E5714
	b _020E571C
_020E56A8:
	cmp r8, #0x64
	beq _020E56E8
	b _020E571C
_020E56B4:
	cmp r8, #0x6f
	bgt _020E56C8
	moveq r4, #0x8
	moveq r11, #0x0
	b _020E571C
_020E56C8:
	cmp r8, #0x78
	bgt _020E571C
	cmp r8, #0x75
	blt _020E571C
	beq _020E5708
	cmp r8, #0x78
	beq _020E5714
	b _020E571C
_020E56E8:
	cmp r10, #0x0
	mov r4, #0xa
	bge _020E571C
	mov r0, #0x1
	cmp r10, #0x80000000
	rsbne r10, r10, #0x0
	str r0, [sp, #0xc]
	b _020E571C
_020E5708:
	mov r4, #0xa
	mov r11, #0x0
	b _020E571C
_020E5714:
	mov r4, #0x10
	mov r11, #0x0
_020E571C:
	mov r0, r10
	mov r1, r4
	bl _u32_div_f
	mov r9, r1
	mov r0, r10
	mov r1, r4
	bl _u32_div_f
	cmp r9, #0xa
	mov r10, r0
	addlt r9, r9, #0x30
	blt _020E5754
	cmp r8, #0x78
	addeq r9, r9, #0x57
	addne r9, r9, #0x37
_020E5754:
	cmp r10, #0x0
	strh r9, [r5, #-0x2]!
	add r6, r6, #0x1
	bne _020E571C
	cmp r4, #0x8
	bne _020E5788
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrneh r0, [r5, #0x0]
	cmpne r0, #0x30
	movne r0, #0x30
	strneh r0, [r5, #-0x2]!
	addne r6, r6, #0x1
_020E5788:
	ldrb r0, [sp, #0x40]
	cmp r0, #0x2
	bne _020E57BC
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x8]
	cmp r0, #0x0
	cmpeq r11, #0x0
	subne r7, r7, #0x1
	cmp r4, #0x10
	bne _020E57BC
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	subne r7, r7, #0x2
_020E57BC:
	ldr r0, [sp, #0x0]
	ldr r1, _020E5864 ; =0x000001FD
	sub r0, r0, r5
	add r0, r0, r0, lsr #0x1f
	add r0, r7, r0, asr #0x1
	cmp r0, r1
	addgt sp, sp, #0x10
	movgt r0, #0x0
	ldmgtia sp!, {r3-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	cmp r6, r7
	bge _020E5804
	mov r0, #0x30
_020E57F4:
	add r6, r6, #0x1
	cmp r6, r7
	strh r0, [r5, #-0x2]!
	blt _020E57F4
_020E5804:
	cmp r4, #0x10
	bne _020E5820
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x30
	strneh r8, [r5, #-0x2]
	strneh r0, [r5, #-0x4]!
_020E5820:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	movne r0, #0x2d
	strneh r0, [r5, #-0x2]!
	bne _020E5850
	cmp r11, #0x1
	moveq r0, #0x2b
	streqh r0, [r5, #-0x2]!
	beq _020E5850
	cmp r11, #0x2
	moveq r0, #0x20
	streqh r0, [r5, #-0x2]!
_020E5850:
	mov r0, r5
	add sp, sp, #0x10
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E5864: .word 0x000001FD
	; arm_func_end long2str__wide

	arm_func_start longlong2str__wide
longlong2str__wide: ; 0x020E5868
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x18
	mov r9, r1
	mov r1, #0x0
	mov r10, r0
	mov r6, r2
	mov r0, r1
	strh r0, [r6, #-0x2]!
	ldr r0, [sp, #0x58]
	cmp r9, #0x0
	str r0, [sp, #0x10]
	ldrb r0, [sp, #0x4f]
	cmpeq r10, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x54]
	str r1, [sp, #0x14]
	str r0, [sp, #0x8]
	ldrb r0, [sp, #0x4d]
	mov r7, r1
	ldrh r8, [sp, #0x52]
	str r0, [sp, #0xc]
	ldreq r0, [sp, #0x10]
	cmpeq r0, #0x0
	bne _020E58F8
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E58E4
	cmp r8, #0x6f
	beq _020E58F8
_020E58E4:
	add sp, sp, #0x18
	mov r0, r6
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E58F8:
	cmp r8, #0x69
	bgt _020E5920
	bge _020E5950
	cmp r8, #0x58
	bgt _020E5914
	beq _020E59A4
	b _020E59B0
_020E5914:
	cmp r8, #0x64
	beq _020E5950
	b _020E59B0
_020E5920:
	cmp r8, #0x6f
	bgt _020E5930
	beq _020E5984
	b _020E59B0
_020E5930:
	cmp r8, #0x78
	bgt _020E59B0
	cmp r8, #0x75
	blt _020E59B0
	beq _020E5994
	cmp r8, #0x78
	beq _020E59A4
	b _020E59B0
_020E5950:
	subs r0, r10, #0x0
	sbcs r0, r9, #0x0
	mov r11, #0xa
	mov r5, #0x0
	bge _020E59B0
	cmp r9, #0x80000000
	cmpeq r10, r5
	beq _020E5978
	rsbs r10, r10, #0x0
	rsc r9, r9, #0x0
_020E5978:
	mov r0, #0x1
	str r0, [sp, #0x14]
	b _020E59B0
_020E5984:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0x8
	b _020E59B0
_020E5994:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0xa
	b _020E59B0
_020E59A4:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0x10
_020E59B0:
	mov r0, r10
	mov r1, r9
	mov r2, r11
	mov r3, r5
	bl _ull_mod
	mov r4, r0
	mov r0, r10
	mov r1, r9
	mov r2, r11
	mov r3, r5
	bl _ll_udiv
	mov r10, r0
	cmp r4, #0xa
	mov r9, r1
	addlt r0, r4, #0x30
	blt _020E59FC
	cmp r8, #0x78
	addeq r0, r4, #0x57
	addne r0, r4, #0x37
_020E59FC:
	strh r0, [r6, #-0x2]!
	mov r0, #0x0
	cmp r9, r0
	cmpeq r10, r0
	add r7, r7, #0x1
	bne _020E59B0
	cmp r5, #0x0
	cmpeq r11, #0x8
	bne _020E5A3C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrneh r0, [r6, #0x0]
	cmpne r0, #0x30
	movne r0, #0x30
	strneh r0, [r6, #-0x2]!
	addne r7, r7, #0x1
_020E5A3C:
	ldrb r0, [sp, #0x4c]
	cmp r0, #0x2
	bne _020E5A8C
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	ldreq r0, [sp, #0xc]
	cmpeq r0, #0x0
	ldrne r0, [sp, #0x10]
	subne r0, r0, #0x1
	strne r0, [sp, #0x10]
	cmp r5, #0x0
	cmpeq r11, #0x10
	bne _020E5A8C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrne r0, [sp, #0x10]
	subne r0, r0, #0x2
	strne r0, [sp, #0x10]
_020E5A8C:
	ldr r0, [sp, #0x0]
	ldr r2, _020E5B48 ; =0x000001FD
	sub r0, r0, r6
	add r1, r0, r0, lsr #0x1f
	ldr r0, [sp, #0x10]
	add r0, r0, r1, asr #0x1
	cmp r0, r2
	addgt sp, sp, #0x18
	movgt r0, #0x0
	ldmgtia sp!, {r3-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	ldr r0, [sp, #0x10]
	cmp r7, r0
	bge _020E5AE0
	mov r1, #0x30
_020E5ACC:
	ldr r0, [sp, #0x10]
	add r7, r7, #0x1
	cmp r7, r0
	strh r1, [r6, #-0x2]!
	blt _020E5ACC
_020E5AE0:
	cmp r5, #0x0
	cmpeq r11, #0x10
	bne _020E5B00
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x30
	strneh r8, [r6, #-0x2]
	strneh r0, [r6, #-0x4]!
_020E5B00:
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	movne r0, #0x2d
	strneh r0, [r6, #-0x2]!
	bne _020E5B34
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	moveq r0, #0x2b
	streqh r0, [r6, #-0x2]!
	beq _020E5B34
	cmp r0, #0x2
	moveq r0, #0x20
	streqh r0, [r6, #-0x2]!
_020E5B34:
	mov r0, r6
	add sp, sp, #0x18
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E5B48: .word 0x000001FD
	; arm_func_end longlong2str__wide

	arm_func_start double2hex__wide
double2hex__wide: ; 0x020E5B4C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r10,lr}
	sub sp, sp, #0x44
	ldr r7, [sp, #0x80]
	ldr r0, _020E5EB8 ; =0x000001FD
	mov r8, r2
	cmp r7, r0
	ldrh r6, [sp, #0x7a]
	ldrb r5, [sp, #0x77]
	ldrb r4, [sp, #0x75]
	ldr r1, [sp, #0x68]
	ldr r2, [sp, #0x6c]
	addgt sp, sp, #0x44
	movgt r0, #0x0
	ldmgtia sp!, {r3-r10,lr}
	addgt sp, sp, #0x10
	bxgt lr
	mov r10, #0x0
	mov r9, #0x20
	add r0, sp, #0x8
	add r3, sp, #0xc
	strb r10, [sp, #0x8]
	strh r9, [sp, #0xa]
	bl __num2dec
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x6c]
	bl fabs
	mov r2, r0
	mov r0, r10
	mov r3, r1
	mov r1, r0
	bl _deq
	bne _020E5BF4
	sub r4, r8, #0xc
	ldr r1, _020E5EBC ; =wstr$6DE4
	mov r0, r4
	bl wcscpy
	add sp, sp, #0x44
	mov r0, r4
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E5BF4:
	ldrb r0, [sp, #0x11]
	cmp r0, #0x49
	bne _020E5C74
	ldrsb r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020E5C38
	cmp r6, #0x41
	sub r4, r8, #0xa
	bne _020E5C28
	ldr r1, _020E5EC0 ; =wstr$6DF0
	mov r0, r4
	bl wcscpy
	b _020E5C60
_020E5C28:
	ldr r1, _020E5EC4 ; =wstr$6DFC
	mov r0, r4
	bl wcscpy
	b _020E5C60
_020E5C38:
	cmp r6, #0x41
	sub r4, r8, #0x8
	bne _020E5C54
	ldr r1, _020E5EC8 ; =wstr$6E08
	mov r0, r4
	bl wcscpy
	b _020E5C60
_020E5C54:
	ldr r1, _020E5ECC ; =wstr$6E10
	mov r0, r4
	bl wcscpy
_020E5C60:
	add sp, sp, #0x44
	mov r0, r4
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E5C74:
	cmp r0, #0x4e
	bne _020E5CF0
	ldrsb r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020E5CB4
	cmp r6, #0x41
	sub r4, r8, #0xa
	bne _020E5CA4
	ldr r1, _020E5ED0 ; =wstr$6E18
	mov r0, r4
	bl wcscpy
	b _020E5CDC
_020E5CA4:
	ldr r1, _020E5ED4 ; =wstr$6E24
	mov r0, r4
	bl wcscpy
	b _020E5CDC
_020E5CB4:
	cmp r6, #0x41
	sub r4, r8, #0x8
	bne _020E5CD0
	ldr r1, _020E5ED8 ; =wstr$6E30
	mov r0, r4
	bl wcscpy
	b _020E5CDC
_020E5CD0:
	ldr r1, _020E5EDC ; =wstr$6E38
	mov r0, r4
	bl wcscpy
_020E5CDC:
	add sp, sp, #0x44
	mov r0, r4
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E5CF0:
	mov r3, r10
	mov r1, #0x1
	mov r0, #0x64
	add r9, sp, #0x68
	strb r1, [sp, #0x34]
	strb r1, [sp, #0x35]
	strb r3, [sp, #0x36]
	strb r3, [sp, #0x37]
	strb r3, [sp, #0x38]
	str r3, [sp, #0x3c]
	str r1, [sp, #0x40]
	strh r0, [sp, #0x3a]
_020E5D20:
	rsb r1, r3, #0x7
	ldrsb r2, [r9, r3]
	ldrsb r0, [r9, r1]
	strb r0, [r9, r3]
	add r3, r3, #0x1
	strb r2, [r9, r1]
	cmp r3, #0x4
	blt _020E5D20
	ldrb r0, [sp, #0x69]
	ldrb r1, [sp, #0x68]
	ldr sb, _020E5EE0 ; =0x000007FF
	mov r0, r0, lsl #0x11
	orr r1, r0, r1, lsl #0x19
	add r0, sp, #0x34
	and lr, r9, r1, lsr #0x15
	sub r12, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r12, {r0-r3}
	rsb r0, r9, #0x400
	mov r1, r8
	add r0, lr, r0
	ldmia r12, {r2-r3}
	bl long2str__wide
	cmp r6, #0x61
	moveq r1, #0x70
	movne r1, #0x50
	strh r1, [r0, #-0x2]!
	mov r1, r7, lsl #0x2
	mov lr, r7
	cmp r7, #0x1
	add r8, r1, #0xb
	add r12, sp, #0x68
	blt _020E5E30
	mov r9, #0x30
_020E5DA8:
	cmp r8, #0x40
	bge _020E5E18
	ldrb r1, [r12, r8, asr #0x3]
	and r2, r8, #0x7
	rsb r3, r2, #0x7
	mov r2, r1, asr r3
	sub r10, r8, #0x4
	bic r1, r8, #0x7
	bic r10, r10, #0x7
	cmp r1, r10
	add r10, r12, r8, asr #0x3
	and r1, r2, #0xff
	beq _020E5DEC
	ldrb r2, [r10, #-0x1]
	mov r2, r2, lsl #0x8
	orr r1, r1, r2, asr r3
	and r1, r1, #0xff
_020E5DEC:
	and r1, r1, #0xf
	cmp r1, #0xa
	addcc r1, r1, #0x30
	andcc r1, r1, #0xff
	blo _020E5E1C
	cmp r6, #0x61
	addeq r1, r1, #0x57
	andeq r1, r1, #0xff
	addne r1, r1, #0x37
	andne r1, r1, #0xff
	b _020E5E1C
_020E5E18:
	mov r1, r9
_020E5E1C:
	sub lr, lr, #0x1
	cmp lr, #0x1
	strh r1, [r0, #-0x2]!
	sub r8, r8, #0x4
	bge _020E5DA8
_020E5E30:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r1, #0x2e
	strneh r1, [r0, #-0x2]!
	mov r1, #0x31
	strh r1, [r0, #-0x2]
	cmp r6, #0x61
	moveq r1, #0x78
	movne r1, #0x58
	strh r1, [r0, #-0x4]!
	mov r1, #0x30
	strh r1, [r0, #-0x2]!
	ldrsb r1, [sp, #0xc]
	cmp r1, #0x0
	movne r1, #0x2d
	strneh r1, [r0, #-0x2]!
	addne sp, sp, #0x44
	ldmneia sp!, {r3-r10,lr}
	addne sp, sp, #0x10
	bxne lr
	cmp r4, #0x1
	moveq r1, #0x2b
	streqh r1, [r0, #-0x2]!
	addeq sp, sp, #0x44
	ldmeqia sp!, {r3-r10,lr}
	addeq sp, sp, #0x10
	bxeq lr
	cmp r4, #0x2
	moveq r1, #0x20
	streqh r1, [r0, #-0x2]!
	add sp, sp, #0x44
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E5EB8: .word 0x000001FD
_020E5EBC: .word wstr$6DE4
_020E5EC0: .word wstr$6DF0
_020E5EC4: .word wstr$6DFC
_020E5EC8: .word wstr$6E08
_020E5ECC: .word wstr$6E10
_020E5ED0: .word wstr$6E18
_020E5ED4: .word wstr$6E24
_020E5ED8: .word wstr$6E30
_020E5EDC: .word wstr$6E38
_020E5EE0: .word 0x000007FF
	; arm_func_end double2hex__wide

	arm_func_start round_decimal__wide
round_decimal__wide: ; 0x020E5EE4
	stmdb sp!, {r4,lr}
	cmp r1, #0x0
	bge _020E5F0C
_020E5EF0:
	mov r1, #0x0
	strh r1, [r0, #0x2]
	mov r1, #0x1
	strb r1, [r0, #0x4]
	mov r1, #0x30
	strb r1, [r0, #0x5]
	ldmia sp!, {r4,pc}
_020E5F0C:
	ldrb lr, [r0, #0x4]
	cmp r1, lr
	ldmgeia sp!, {r4,pc}
	add r12, r0, #0x5
	add r2, r12, r1
	add r2, r2, #0x1
	ldrsb r3, [r2, #-0x1]!
	sub r3, r3, #0x30
	mov r3, r3, lsl #0x18
	mov r3, r3, asr #0x18
	cmp r3, #0x5
	bne _020E5F6C
	add r12, r12, lr
_020E5F40:
	sub r12, r12, #0x1
	cmp r12, r2
	bls _020E5F58
	ldrsb r3, [r12, #0x0]
	cmp r3, #0x30
	beq _020E5F40
_020E5F58:
	cmp r12, r2
	ldreqsb r3, [r2, #-0x1]
	andeq r4, r3, #0x1
	movne r4, #0x1
	b _020E5F74
_020E5F6C:
	movgt r4, #0x1
	movle r4, #0x0
_020E5F74:
	cmp r1, #0x0
	beq _020E5FD0
	mov r12, #0x0
	mov lr, #0x1
_020E5F84:
	ldrsb r3, [r2, #-0x1]!
	sub r3, r3, #0x30
	add r3, r3, r4
	mov r3, r3, lsl #0x18
	mov r3, r3, asr #0x18
	cmp r3, #0x9
	movgt r4, lr
	movle r4, r12
	cmp r4, #0x0
	bne _020E5FB4
	cmp r3, #0x0
	bne _020E5FBC
_020E5FB4:
	sub r1, r1, #0x1
	b _020E5FC8
_020E5FBC:
	add r3, r3, #0x30
	strb r3, [r2, #0x0]
	b _020E5FD0
_020E5FC8:
	cmp r1, #0x0
	bne _020E5F84
_020E5FD0:
	cmp r4, #0x0
	beq _020E5FF8
	ldrsh r3, [r0, #0x2]
	mov r2, #0x1
	mov r1, #0x31
	add r3, r3, #0x1
	strh r3, [r0, #0x2]
	strb r2, [r0, #0x4]
	strb r1, [r0, #0x5]
	ldmia sp!, {r4,pc}
_020E5FF8:
	cmp r1, #0x0
	beq _020E5EF0
	strb r1, [r0, #0x4]
	ldmia sp!, {r4,pc}
	arm_func_end round_decimal__wide

	arm_func_start float2str__wide
float2str__wide: ; 0x020E6008
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x22c
	mov r10, r0
	add r0, sp, #0x250
	ldr r7, [sp, #0x268]
	ldr r3, _020E6628 ; =0x000001FD
	ldrh r6, [r0, #0x12]
	cmp r7, r3
	ldrb r5, [sp, #0x25f]
	ldrb r4, [sp, #0x25d]
	mov r8, r1
	mov r9, r2
	addgt sp, sp, #0x22c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	mov r12, #0x0
	mov r11, #0x20
	add r0, sp, #0x0
	add r3, sp, #0x4
	mov r1, r10
	mov r2, r8
	strb r12, [sp, #0x0]
	strh r11, [sp, #0x2]
	bl __num2dec
	ldrb r0, [sp, #0x8]
	add r1, sp, #0x9
	add r0, r1, r0
	b _020E609C
_020E6084:
	ldrb r2, [sp, #0x8]
	ldrsh r1, [sp, #0x6]
	sub r2, r2, #0x1
	add r1, r1, #0x1
	strb r2, [sp, #0x8]
	strh r1, [sp, #0x6]
_020E609C:
	ldrb r1, [sp, #0x8]
	cmp r1, #0x1
	bls _020E60B4
	ldrsb r1, [r0, #-0x1]!
	cmp r1, #0x30
	beq _020E6084
_020E60B4:
	ldrb r0, [sp, #0x9]
	cmp r0, #0x30
	beq _020E60D4
	cmp r0, #0x49
	beq _020E60E0
	cmp r0, #0x4e
	beq _020E6198
	b _020E6244
_020E60D4:
	mov r0, #0x0
	strh r0, [sp, #0x6]
	b _020E6244
_020E60E0:
	mov r2, #0x0
	mov r0, r10
	mov r1, r8
	mov r3, r2
	bl _dls
	bhs _020E6140
	cmp r6, #0x80
	sub r4, r9, #0xa
	movcs r0, #0x0
	bhs _020E6118
	ldr r0, _020E662C ; =__wctype_mapC
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E6118:
	cmp r0, #0x0
	beq _020E6130
	ldr r1, _020E6630 ; =wstr$6DF0
	mov r0, r4
	bl wcscpy
	b _020E6184
_020E6130:
	ldr r1, _020E6634 ; =wstr$6DFC
	mov r0, r4
	bl wcscpy
	b _020E6184
_020E6140:
	cmp r6, #0x80
	sub r4, r9, #0x8
	movcs r0, #0x0
	bhs _020E6160
	ldr r0, _020E662C ; =__wctype_mapC
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E6160:
	cmp r0, #0x0
	beq _020E6178
	ldr r1, _020E6638 ; =wstr$6E08
	mov r0, r4
	bl wcscpy
	b _020E6184
_020E6178:
	ldr r1, _020E663C ; =wstr$6E10
	mov r0, r4
	bl wcscpy
_020E6184:
	add sp, sp, #0x22c
	mov r0, r4
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E6198:
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E61EC
	cmp r6, #0x80
	sub r4, r9, #0xa
	movcs r0, #0x0
	bhs _020E61C4
	ldr r0, _020E662C ; =__wctype_mapC
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E61C4:
	cmp r0, #0x0
	beq _020E61DC
	ldr r1, _020E6640 ; =wstr$6E18
	mov r0, r4
	bl wcscpy
	b _020E6230
_020E61DC:
	ldr r1, _020E6644 ; =wstr$6E24
	mov r0, r4
	bl wcscpy
	b _020E6230
_020E61EC:
	cmp r6, #0x80
	sub r4, r9, #0x8
	movcs r0, #0x0
	bhs _020E620C
	ldr r0, _020E662C ; =__wctype_mapC
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E620C:
	cmp r0, #0x0
	beq _020E6224
	ldr r1, _020E6648 ; =wstr$6E30
	mov r0, r4
	bl wcscpy
	b _020E6230
_020E6224:
	ldr r1, _020E664C ; =wstr$6E38
	mov r0, r4
	bl wcscpy
_020E6230:
	add sp, sp, #0x22c
	mov r0, r4
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E6244:
	ldrb r1, [sp, #0x8]
	ldrsh r2, [sp, #0x6]
	add r0, sp, #0x200
	sub r1, r1, #0x1
	add r0, r0, #0x2a
	add r1, r2, r1
	sub r8, r0, #0x1
	strh r1, [sp, #0x6]
	mov r0, #0x0
	strb r0, [r8, #0x0]
	cmp r6, #0x65
	bgt _020E62A0
	bge _020E632C
	cmp r6, #0x47
	bgt _020E65EC
	cmp r6, #0x45
	blt _020E65EC
	beq _020E632C
	cmp r6, #0x46
	beq _020E6478
	cmp r6, #0x47
	beq _020E62B8
	b _020E65EC
_020E62A0:
	cmp r6, #0x66
	bgt _020E62B0
	beq _020E6478
	b _020E65EC
_020E62B0:
	cmp r6, #0x67
	bne _020E65EC
_020E62B8:
	ldrb r0, [sp, #0x8]
	cmp r0, r7
	ble _020E62D0
	add r0, sp, #0x4
	mov r1, r7
	bl round_decimal__wide
_020E62D0:
	ldrsh r2, [sp, #0x6]
	mvn r0, #0x3
	cmp r2, r0
	blt _020E62E8
	cmp r2, r7
	blt _020E6308
_020E62E8:
	cmp r5, #0x0
	ldreqb r0, [sp, #0x8]
	subne r7, r7, #0x1
	subeq r7, r0, #0x1
	cmp r6, #0x67
	moveq r6, #0x65
	movne r6, #0x45
	b _020E632C
_020E6308:
	cmp r5, #0x0
	addne r0, r2, #0x1
	subne r7, r7, r0
	bne _020E6478
	ldrb r1, [sp, #0x8]
	add r0, r2, #0x1
	subs r7, r1, r0
	movmi r7, #0x0
	b _020E6478
_020E632C:
	ldrb r0, [sp, #0x8]
	add r1, r7, #0x1
	cmp r0, r1
	ble _020E6344
	add r0, sp, #0x4
	bl round_decimal__wide
_020E6344:
	ldrsh lr, [sp, #0x6]
	mov r11, #0x2b
	mov r10, #0x0
	cmp lr, #0x0
	rsblt lr, lr, #0x0
	movlt r11, #0x2d
	ldr r3, _020E6650 ; =0x66666667
	mov r0, #0xa
	b _020E6398
_020E6368:
	mov r1, lr, lsr #0x1f
	smull r2, r12, r3, lr
	add r12, r1, r12, asr #0x2
	smull r1, r2, r0, r12
	sub r12, lr, r1
	add r1, r12, #0x30
	strb r1, [r8, #-0x1]!
	mov r2, lr
	smull r1, lr, r3, r2
	mov r1, r2, lsr #0x1f
	add lr, r1, lr, asr #0x2
	add r10, r10, #0x1
_020E6398:
	cmp lr, #0x0
	bne _020E6368
	cmp r10, #0x2
	blt _020E6368
	add r0, sp, #0x2a
	strb r11, [r8, #-0x1]
	strb r6, [r8, #-0x2]!
	sub r1, r0, r8
	ldr r0, _020E6628 ; =0x000001FD
	add r1, r1, r7
	cmp r1, r0
	addgt sp, sp, #0x22c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	ldrb r1, [sp, #0x8]
	add r0, r7, #0x1
	cmp r1, r0
	bge _020E6408
	add r0, r7, #0x2
	sub r0, r0, r1
	subs r1, r0, #0x1
	beq _020E6408
	mov r0, #0x30
_020E63FC:
	strb r0, [r8, #-0x1]!
	subs r1, r1, #0x1
	bne _020E63FC
_020E6408:
	ldrb r1, [sp, #0x8]
	add r0, sp, #0x9
	add r2, r0, r1
	subs r1, r1, #0x1
	beq _020E642C
_020E641C:
	ldrsb r0, [r2, #-0x1]!
	subs r1, r1, #0x1
	strb r0, [r8, #-0x1]!
	bne _020E641C
_020E642C:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r0, #0x2e
	strneb r0, [r8, #-0x1]!
	ldrb r0, [sp, #0x9]
	strb r0, [r8, #-0x1]!
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r8, #-0x1]!
	bne _020E65EC
	cmp r4, #0x1
	moveq r0, #0x2b
	streqb r0, [r8, #-0x1]!
	beq _020E65EC
	cmp r4, #0x2
	moveq r0, #0x20
	streqb r0, [r8, #-0x1]!
	b _020E65EC
_020E6478:
	ldrsh r3, [sp, #0x6]
	ldrb r2, [sp, #0x8]
	sub r0, r2, r3
	subs r1, r0, #0x1
	movmi r1, #0x0
	cmp r1, r7
	ble _020E64B8
	sub r1, r1, r7
	add r0, sp, #0x4
	sub r1, r2, r1
	bl round_decimal__wide
	ldrsh r3, [sp, #0x6]
	ldrb r2, [sp, #0x8]
	sub r0, r2, r3
	subs r1, r0, #0x1
	movmi r1, #0x0
_020E64B8:
	adds r0, r3, #0x1
	movmi r0, #0x0
	ldr r3, _020E6628 ; =0x000001FD
	add r6, r0, r1
	cmp r6, r3
	addgt sp, sp, #0x22c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	add r3, sp, #0x9
	sub r6, r7, r1
	cmp r6, #0x0
	add r2, r3, r2
	mov r10, #0x0
	ble _020E650C
	mov r3, #0x30
_020E64FC:
	add r10, r10, #0x1
	cmp r10, r6
	strb r3, [r8, #-0x1]!
	blt _020E64FC
_020E650C:
	mov r6, #0x0
	b _020E6520
_020E6514:
	ldrsb r3, [r2, #-0x1]!
	add r6, r6, #0x1
	strb r3, [r8, #-0x1]!
_020E6520:
	cmp r6, r1
	ldrltb r3, [sp, #0x8]
	cmplt r6, r3
	blt _020E6514
	cmp r6, r1
	bge _020E654C
	mov r3, #0x30
_020E653C:
	add r6, r6, #0x1
	cmp r6, r1
	strb r3, [r8, #-0x1]!
	blt _020E653C
_020E654C:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r1, #0x2e
	strneb r1, [r8, #-0x1]!
	cmp r0, #0x0
	beq _020E65B4
	ldrb r1, [sp, #0x8]
	mov r5, #0x0
	sub r1, r0, r1
	cmp r1, #0x0
	ble _020E6594
	mov r3, #0x30
_020E657C:
	strb r3, [r8, #-0x1]!
	ldrb r1, [sp, #0x8]
	add r5, r5, #0x1
	sub r1, r0, r1
	cmp r5, r1
	blt _020E657C
_020E6594:
	cmp r5, r0
	bge _020E65BC
_020E659C:
	ldrsb r1, [r2, #-0x1]!
	add r5, r5, #0x1
	cmp r5, r0
	strb r1, [r8, #-0x1]!
	blt _020E659C
	b _020E65BC
_020E65B4:
	mov r0, #0x30
	strb r0, [r8, #-0x1]!
_020E65BC:
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r8, #-0x1]!
	bne _020E65EC
	cmp r4, #0x1
	moveq r0, #0x2b
	streqb r0, [r8, #-0x1]!
	beq _020E65EC
	cmp r4, #0x2
	moveq r0, #0x20
	streqb r0, [r8, #-0x1]!
_020E65EC:
	mov r0, r8
	bl strlen
	sub r1, r9, r0, lsl #0x1
	mov r0, r8
	sub r4, r1, #0x2
	bl strlen
	mov r2, r0
	mov r0, r4
	mov r1, r8
	bl mbstowcs
	mov r0, r4
	add sp, sp, #0x22c
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E6628: .word 0x000001FD
_020E662C: .word __wctype_mapC
_020E6630: .word wstr$6DF0
_020E6634: .word wstr$6DFC
_020E6638: .word wstr$6E08
_020E663C: .word wstr$6E10
_020E6640: .word wstr$6E18
_020E6644: .word wstr$6E24
_020E6648: .word wstr$6E30
_020E664C: .word wstr$6E38
_020E6650: .word 0x66666667
	; arm_func_end float2str__wide

	arm_func_start __wpformatter
__wpformatter:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x430
	mov r3, #0x20
	mov r11, r2
	strh r3, [sp, #0x1c]
	ldrh r2, [r11, #0x0]
	mov r9, r0
	mov r8, r1
	cmp r2, #0x0
	mov r4, #0x0
	beq _020E6F24
_020E6684:
	mov r0, r11
	mov r1, #0x25
	bl wcschr
	str r0, [sp, #0xc]
	cmp r0, #0x0
	bne _020E66D8
	mov r0, r11
	bl wcslen
	movs r2, r0
	add r4, r4, r2
	beq _020E6F24
	mov r0, r8
	mov r1, r11
	blx r9
	cmp r0, #0x0
	bne _020E6F24
	add sp, sp, #0x430
	mvn r0, #0x0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E66D8:
	sub r0, r0, r11
	add r0, r0, r0, lsr #0x1f
	movs r2, r0, asr #0x1
	add r4, r4, r2
	beq _020E6710
	mov r0, r8
	mov r1, r11
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E6710:
	add r1, sp, #0x400
	ldr r0, [sp, #0xc]
	add r1, r1, #0x64
	add r2, sp, #0x20
	bl parse_format__wide
	ldrh r1, [sp, #0x26]
	mov r11, r0
	cmp r1, #0x61
	bgt _020E6780
	bge _020E6AEC
	cmp r1, #0x47
	bgt _020E6774
	subs r0, r1, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020E6768
	b _020E6AEC
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6A7C
	b _020E6A7C
	b _020E6A7C
_020E6768:
	cmp r1, #0x25
	beq _020E6D7C
	b _020E6D90
_020E6774:
	cmp r1, #0x58
	beq _020E6940
	b _020E6D90
_020E6780:
	cmp r1, #0x75
	bgt _020E67E8
	subs r0, r1, #0x64
	addpl pc, pc, r0, lsl #0x2
	b _020E67DC
	b _020E6804
	b _020E6A7C
	b _020E6A7C
	b _020E6A7C
	b _020E6D90
	b _020E6804
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6C98
	b _020E6940
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6B5C
	b _020E6D90
	b _020E6940
_020E67DC:
	cmp r1, #0x63
	beq _020E6D24
	b _020E6D90
_020E67E8:
	cmp r1, #0x78
	bgt _020E67F8
	beq _020E6940
	b _020E6D90
_020E67F8:
	ldr r0, _020E6F38 ; =0x0000FFFF
	cmp r1, r0
	b _020E6D90
_020E6804:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x3
	bne _020E6824
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E68BC
_020E6824:
	cmp r0, #0x4
	bne _020E684C
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E68BC
_020E684C:
	cmp r0, #0x6
	bne _020E6874
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E68BC
_020E6874:
	cmp r0, #0x7
	bne _020E6890
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E68BC
_020E6890:
	cmp r0, #0x8
	bne _020E68AC
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E68BC
_020E68AC:
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
_020E68BC:
	cmp r0, #0x2
	moveq r1, r10, lsl #0x10
	moveq r10, r1, asr #0x10
	cmp r0, #0x4
	cmpne r0, #0x6
	add r0, sp, #0x20
	bne _020E6904
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x430
	bl longlong2str__wide
	movs r6, r0
	beq _020E6D90
	b _020E6928
_020E6904:
	sub r5, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	add r1, sp, #0x430
	mov r0, r10
	ldmia r5, {r2-r3}
	bl long2str__wide
	movs r6, r0
	beq _020E6D90
_020E6928:
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6940:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x3
	bne _020E6960
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E69F8
_020E6960:
	cmp r0, #0x4
	bne _020E6988
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E69F8
_020E6988:
	cmp r0, #0x6
	bne _020E69B0
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E69F8
_020E69B0:
	cmp r0, #0x7
	bne _020E69CC
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E69F8
_020E69CC:
	cmp r0, #0x8
	bne _020E69E8
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E69F8
_020E69E8:
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
_020E69F8:
	cmp r0, #0x2
	moveq r1, r10, lsl #0x10
	moveq r10, r1, lsr #0x10
	cmp r0, #0x4
	cmpne r0, #0x6
	add r0, sp, #0x20
	bne _020E6A40
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x430
	bl longlong2str__wide
	movs r6, r0
	beq _020E6D90
	b _020E6A64
_020E6A40:
	sub r5, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	add r1, sp, #0x430
	mov r0, r10
	ldmia r5, {r2-r3}
	bl long2str__wide
	movs r6, r0
	beq _020E6D90
_020E6A64:
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6A7C:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x9
	ldrne r0, [sp, #0x464]
	addne r0, r0, #0x8
	strne r0, [sp, #0x464]
	bne _020E6AA0
	ldr r0, [sp, #0x464]
	add r0, r0, #0x8
	str r0, [sp, #0x464]
_020E6AA0:
	ldr r7, [r0, #-0x8]
	ldr r6, [r0, #-0x4]
	add r0, sp, #0x20
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	mov r0, r7
	mov r1, r6
	add r2, sp, #0x430
	bl float2str__wide
	movs r6, r0
	beq _020E6D90
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6AEC:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x9
	ldrne r0, [sp, #0x464]
	addne r0, r0, #0x8
	strne r0, [sp, #0x464]
	bne _020E6B10
	ldr r0, [sp, #0x464]
	add r0, r0, #0x8
	str r0, [sp, #0x464]
_020E6B10:
	ldr r7, [r0, #-0x8]
	ldr r6, [r0, #-0x4]
	add r0, sp, #0x20
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	mov r0, r7
	mov r1, r6
	add r2, sp, #0x430
	bl double2hex__wide
	movs r6, r0
	beq _020E6D90
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6B5C:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x5
	bne _020E6BF8
	ldr r0, [sp, #0x464]
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r6, [r0, #-0x4]
	ldrb r0, [sp, #0x23]
	cmp r6, #0x0
	ldreq r6, _020E6F3C ; =buff_ptr$6E40
	cmp r0, #0x0
	beq _020E6BB0
	ldrh r1, [r6], #0x2
	ldrb r0, [sp, #0x22]
	and r7, r1, #0xff
	cmp r0, #0x0
	beq _020E6DDC
	ldr r0, [sp, #0x2c]
	cmp r7, r0
	movgt r7, r0
	b _020E6DDC
_020E6BB0:
	ldrb r0, [sp, #0x22]
	cmp r0, #0x0
	beq _020E6BE8
	ldr r7, [sp, #0x2c]
	mov r0, r6
	mov r2, r7
	mov r1, #0x0
	bl wmemchr
	cmp r0, #0x0
	beq _020E6DDC
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6BE8:
	mov r0, r6
	bl wcslen
	mov r7, r0
	b _020E6DDC
_020E6BF8:
	ldr r0, [sp, #0x464]
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r5, [r0, #-0x4]
	ldrb r0, [sp, #0x23]
	cmp r5, #0x0
	ldreq r5, _020E6F40 ; =strptr$6E44
	cmp r0, #0x0
	beq _020E6C40
	ldrh r1, [r6, #0x0]
	ldrb r0, [sp, #0x22]
	and r6, r1, #0xff
	cmp r0, #0x0
	beq _020E6C78
	ldr r0, [sp, #0x2c]
	cmp r6, r0
	movgt r6, r0
	b _020E6C78
_020E6C40:
	ldrb r0, [sp, #0x22]
	cmp r0, #0x0
	beq _020E6C6C
	ldr r6, [sp, #0x2c]
	mov r0, r5
	mov r2, r6
	mov r1, #0x0
	bl memchr
	cmp r0, #0x0
	subne r6, r0, r5
	b _020E6C78
_020E6C6C:
	mov r0, r5
	bl strlen
	mov r6, r0
_020E6C78:
	add r0, sp, #0x30
	mov r1, r5
	mov r2, r6
	bl mbstowcs
	movs r7, r0
	bmi _020E6D90
	add r6, sp, #0x30
	b _020E6DDC
_020E6C98:
	ldr r1, [sp, #0x464]
	ldrb r0, [sp, #0x24]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r6, [r1, #-0x4]
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020E6F18
	b _020E6CDC ; case
	b _020E6F18 ; case
	b _020E6CE4 ; case
	b _020E6CEC ; case
	b _020E6D14 ; case
	b _020E6F18 ; case
	b _020E6CF4 ; case
	b _020E6D04 ; case
	b _020E6D0C ; case
_020E6CDC:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6CE4:
	strh r4, [r6, #0x0]
	b _020E6F18
_020E6CEC:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6CF4:
	str r4, [r6, #0x0]
	mov r0, r4, asr #0x1f
	str r0, [r6, #0x4]
	b _020E6F18
_020E6D04:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6D0C:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6D14:
	str r4, [r6, #0x0]
	mov r0, r4, asr #0x1f
	str r0, [r6, #0x4]
	b _020E6F18
_020E6D24:
	ldrb r0, [sp, #0x24]
	add r6, sp, #0x30
	cmp r0, #0x5
	bne _020E6D50
	ldr r0, [sp, #0x464]
	mov r7, #0x1
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r0, [r0, #-0x4]
	strh r0, [r6, #0x0]
	b _020E6DDC
_020E6D50:
	ldr r0, [sp, #0x464]
	add r1, sp, #0x18
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r3, [r0, #-0x4]
	mov r0, r6
	mov r2, #0x1
	strb r3, [sp, #0x18]
	bl mbtowc
	mov r7, r0
	b _020E6DDC
_020E6D7C:
	mov r0, #0x25
	strh r0, [sp, #0x30]
	add r6, sp, #0x30
	mov r7, #0x1
	b _020E6DDC
_020E6D90:
	ldr r0, [sp, #0xc]
	bl wcslen
	movs r5, r0
	beq _020E6DC8
	ldr r1, [sp, #0xc]
	mov r0, r8
	mov r2, r5
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E6DC8:
	add sp, sp, #0x430
	add r0, r4, r5
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E6DDC:
	ldrb r0, [sp, #0x20]
	mov r5, r7
	cmp r0, #0x0
	beq _020E6E8C
	cmp r0, #0x2
	moveq r1, #0x30
	movne r1, #0x20
	strh r1, [sp, #0x1c]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x2b
	cmpne r0, #0x2d
	cmpne r0, #0x20
	bne _020E6E48
	cmp r1, #0x30
	bne _020E6E48
	mov r0, r8
	mov r1, r6
	mov r2, #0x1
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r6, r6, #0x2
	sub r7, r7, #0x1
_020E6E48:
	ldr r0, [sp, #0x28]
	cmp r5, r0
	bge _020E6E8C
_020E6E54:
	mov r0, r8
	add r1, sp, #0x1c
	mov r2, #0x1
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x28]
	add r5, r5, #0x1
	cmp r5, r0
	blt _020E6E54
_020E6E8C:
	cmp r7, #0x0
	beq _020E6EBC
	mov r0, r8
	mov r1, r6
	mov r2, r7
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E6EBC:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x0
	bne _020E6F14
	ldr r0, [sp, #0x28]
	cmp r5, r0
	bge _020E6F14
	mov r7, #0x20
_020E6ED8:
	mov r0, r8
	add r1, sp, #0x1a
	mov r2, #0x1
	strh r7, [sp, #0x1a]
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x28]
	add r5, r5, #0x1
	cmp r5, r0
	blt _020E6ED8
_020E6F14:
	add r4, r4, r5
_020E6F18:
	ldrh r0, [r11, #0x0]
	cmp r0, #0x0
	bne _020E6684
_020E6F24:
	mov r0, r4
	add sp, sp, #0x430
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E6F38: .word 0x0000FFFF
_020E6F3C: .word buff_ptr$6E40
_020E6F40: .word strptr$6E44
	arm_func_end __wpformatter

	arm_func_start __wStringWrite
__wStringWrite: ; 0x020E6F44
	stmdb sp!, {r3-r5,lr}
	mov r4, r0
	ldr r3, [r4, #0x8]
	mov r5, r2
	ldr r2, [r4, #0x4]
	add r0, r3, r5
	cmp r0, r2
	ldr r0, [r4, #0x0]
	subhi r5, r2, r3
	mov r2, r5
	add r0, r0, r3, lsl #0x1
	bl wmemcpy
	ldr r1, [r4, #0x8]
	add r1, r1, r5
	str r1, [r4, #0x8]
	ldmia sp!, {r3-r5,pc}
	arm_func_end __wStringWrite

	arm_func_start swprintf
swprintf: ; 0x020E6F84
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3,lr}
	add r3, sp, #0x10
	bic r3, r3, #0x3
	ldr r2, [sp, #0x10]
	add r3, r3, #0x4
	bl vswprintf
	ldmia sp!, {r3,lr}
	add sp, sp, #0x10
	bx lr
	arm_func_end swprintf

	arm_func_start vswprintf
vswprintf: ; 0x020E6FAC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	mov r12, #0x0
	ldr r0, _020E7018 ; =__wStringWrite
	add r1, sp, #0x0
	str r5, [sp, #0x0]
	str r4, [sp, #0x4]
	str r12, [sp, #0x8]
	bl __wpformatter
	cmp r0, #0x0
	addlt sp, sp, #0xc
	ldmltia sp!, {r4-r5,pc}
	cmp r0, r4
	bhs _020E7000
	mov r1, r0, lsl #0x1
	mov r2, #0x0
	add sp, sp, #0xc
	strh r2, [r5, r1]
	ldmia sp!, {r4-r5,pc}
_020E7000:
	mov r1, #0x0
	add r0, r5, r4, lsl #0x1
	strh r1, [r0, #-0x2]
	sub r0, r1, #0x1
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020E7018: .word __wStringWrite
	arm_func_end vswprintf

	exception long2str__wide, 593, 0x0090FF20
	exception longlong2str__wide, 741, 0x00A0FF20
	exception double2hex__wide, 921, 0x00F07F20
	exception float2str__wide, 1612, float2str__wide_exception
	exception __wpformatter, 2288, __wpformatter_exception
	exception __wStringWrite, 65, 0x00200300
	exception swprintf, 41, 0x00300020
	exception vswprintf, 113, 0x00300300

	.section .exception,8

float2str__wide_exception: ; 0x020EC728
	.byte 0x20, 0xFF, 0x09, 0x60, 0x00, 0x00, 0x00, 0x00

__wpformatter_exception: ; 0x020EC730
	.byte 0x20, 0xFF, 0x11, 0x68, 0x00, 0x00, 0x00, 0x00
