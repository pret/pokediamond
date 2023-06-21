	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_020250A4
sub_020250A4: ; 0x020250A4
	push {r4, lr}
	mov r2, #0x7
	mov r1, #0x0
	lsl r2, r2, #0x8
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r1, #0x0
	add r0, r1, #0x0
_020250B6:
	strb r0, [r4, #0x1]
	strb r0, [r4, #0x0]
	add r1, r1, #0x1
	add r4, #0xe
	cmp r1, #0x80
	blt _020250B6
	pop {r4, pc}

	thumb_func_start sub_020250C4
sub_020250C4: ; 0x020250C4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, r1, #0x0
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl sub_02025128
	mov r4, #0x0
	str r0, [sp, #0x8]
	add r6, r4, #0x0
	b _02025112
_020250DC:
	add r0, r5, #0x0
	bl sub_02025184
	ldr r0, [sp, #0x0]
	lsl r1, r6, #0x1
	add r7, r0, r1
	ldrh r0, [r0, r1]
	sub r0, #0x94
	strb r0, [r5, #0x0]
	mov r0, #0x5
	strb r0, [r5, #0x1]
	ldrb r1, [r5, #0x0]
	ldrb r2, [r5, #0xc]
	ldr r0, [sp, #0x8]
	bl sub_020251B0
	lsl r0, r0, #0x2
	strh r0, [r5, #0x2]
	ldrh r0, [r7, #0x2]
	add r6, r6, #0x2
	add r4, r4, #0x1
	strh r0, [r5, #0x8]
	mov r0, #0x64
	strb r0, [r5, #0xa]
	mov r0, #0x3
	strb r0, [r5, #0xb]
	add r5, #0xe
_02025112:
	cmp r4, #0x80
	blt _020250DC
	ldr r0, [sp, #0x4]
	cmp r4, r0
	blt _020250DC
	ldr r0, [sp, #0x8]
	bl FreeToHeap
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start sub_02025128
sub_02025128: ; 0x02025128
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	bl OpenNutsDataNarc
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	mov r1, #0xc0
	bl AllocFromHeap
	str r0, [sp, #0x4]
	mov r6, #0x0
	add r5, r0, #0x0
_02025142:
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl ReadNutDataFromNarc
	add r4, r0, #0x0
	mov r1, #0x3
	bl GetNutAttr
	strb r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0x4
	bl GetNutAttr
	strb r0, [r5, #0x1]
	add r0, r4, #0x0
	mov r1, #0x2
	bl GetNutAttr
	strb r0, [r5, #0x2]
	add r0, r4, #0x0
	bl FreeToHeap
	add r6, r6, #0x1
	add r5, r5, #0x3
	cmp r6, #0x40
	blt _02025142
	ldr r0, [sp, #0x0]
	bl CloseNutsDataNarc
	ldr r0, [sp, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start sub_02025184
sub_02025184: ; 0x02025184
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strh r1, [r0, #0x2]
	strh r1, [r0, #0x4]
	strb r1, [r0, #0x6]
	strh r1, [r0, #0x8]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	strb r1, [r0, #0xc]
	strb r1, [r0, #0xd]
	bx lr

	thumb_func_start sub_0202519C
sub_0202519C: ; 0x0202519C
	ldrb r2, [r0, #0xb]
	ldrb r0, [r0, #0x0]
	sub r3, r0, #0x1
	lsl r0, r3, #0x1
	add r0, r3, r0
	add r0, r1, r0
	ldrb r0, [r0, #0x2]
	mul r0, r2
	bx lr
	.balign 4

	thumb_func_start sub_020251B0
sub_020251B0: ; 0x020251B0
	sub r3, r1, #0x1
	lsl r1, r3, #0x1
	add r1, r3, r1
	ldrb r1, [r0, r1]
	mov r0, #0x3c
	mul r0, r1
	cmp r2, #0x1
	bne _020251CE
	lsl r1, r0, #0x1
	add r1, r0, r1
	asr r0, r1, #0x1
	lsr r0, r0, #0x1e
	add r0, r1, r0
	asr r0, r0, #0x2
	bx lr
_020251CE:
	cmp r2, #0x2
	bne _020251DA
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r1, r1, #0x1
	add r0, r0, r1
_020251DA:
	bx lr

	thumb_func_start sub_020251DC
sub_020251DC: ; 0x020251DC
	sub r3, r1, #0x1
	lsl r1, r3, #0x1
	add r1, r3, r1
	add r0, r0, r1
	ldrb r0, [r0, #0x1]
	cmp r2, #0x2
	bne _020251F2
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r0, r1, #0x1
	bx lr
_020251F2:
	cmp r2, #0x1
	bne _020251FE
	lsr r1, r0, #0x1f
	add r1, r0, r1
	asr r1, r1, #0x1
	add r0, r0, r1
_020251FE:
	bx lr

	thumb_func_start sub_02025200
sub_02025200: ; 0x02025200
	ldrb r0, [r0, #0xc]
	cmp r0, #0x3
	bne _0202520A
	mov r0, #0x6
	bx lr
_0202520A:
	mov r0, #0x4
	bx lr
	.balign 4

	thumb_func_start sub_02025210
sub_02025210: ; 0x02025210
	ldrb r0, [r0, #0xc]
	cmp r0, #0x4
	bne _0202521A
	mov r0, #0xf
	bx lr
_0202521A:
	mov r0, #0xa
	bx lr
	.balign 4

	thumb_func_start sub_02025220
sub_02025220: ; 0x02025220
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl sub_02025200
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02025210
	add r1, r4, #0x3
	mul r0, r1
	add r0, r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start sub_02025238
sub_02025238: ; 0x02025238
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0x1]
	bx lr
	.balign 4

	thumb_func_start sub_02025244
sub_02025244: ; 0x02025244
	mov r2, #0xe
	mul r2, r1
	ldrb r0, [r0, r2]
	bx lr

	thumb_func_start sub_0202524C
sub_0202524C: ; 0x0202524C
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xa]
	cmp r0, #0x0
	bne _0202525C
	mov r0, #0x0
	bx lr
_0202525C:
	cmp r0, #0x32
	bgt _02025264
	mov r0, #0x1
	bx lr
_02025264:
	mov r0, #0x2
	bx lr

	thumb_func_start sub_02025268
sub_02025268: ; 0x02025268
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xb]
	bx lr
	.balign 4

	thumb_func_start sub_02025274
sub_02025274: ; 0x02025274
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xe
	mul r4, r0
	strb r3, [r5, r4]
	mov r0, #0x1
	add r6, r5, r4
	strb r0, [r6, #0x1]
	add r0, r2, #0x0
	ldrb r2, [r6, #0xc]
	add r1, r3, #0x0
	bl sub_020251B0
	add r1, r6, #0x0
	strh r0, [r1, #0x2]
	mov r0, #0x0
	strh r0, [r1, #0x4]
	strb r0, [r1, #0x6]
	strh r0, [r1, #0x8]
	mov r0, #0x64
	strb r0, [r1, #0xa]
	mov r0, #0x5
	strb r0, [r1, #0xb]
	mov r0, #0x1
	strb r0, [r1, #0xd]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_020252AC
sub_020252AC: ; 0x020252AC
	mov r2, #0xe
	mul r2, r1
	mov r3, #0x64
	add r0, r0, r2
	strb r3, [r0, #0xa]
	bx lr

	thumb_func_start sub_020252B8
sub_020252B8: ; 0x020252B8
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xd]
	bx lr
	.balign 4

	thumb_func_start sub_020252C4
sub_020252C4: ; 0x020252C4
	mov r3, #0xe
	mul r3, r1
	add r0, r0, r3
	strb r2, [r0, #0xd]
	bx lr
	.balign 4

	thumb_func_start sub_020252D0
sub_020252D0: ; 0x020252D0
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrb r0, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start sub_020252DC
sub_020252DC: ; 0x020252DC
	mov r3, #0xe
	mul r3, r1
	add r0, r0, r3
	strb r2, [r0, #0xc]
	bx lr
	.balign 4

	thumb_func_start sub_020252E8
sub_020252E8: ; 0x020252E8
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrh r0, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start sub_020252F4
sub_020252F4: ; 0x020252F4
	push {r4, lr}
	mov r2, #0xe
	mul r2, r1
	add r0, r0, r2
	ldrh r4, [r0, #0x8]
	bl sub_02025184
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02025308
sub_02025308: ; 0x02025308
	push {r4, lr}
	add r4, r0, #0x0
	ldrb r2, [r4, #0x1]
	cmp r2, #0x5
	bhi _02025370
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0202531E: ; jump table (using 16-bit offset)
	.short _0202532A - _0202531E - 2; case 0
	.short _02025330 - _0202531E - 2; case 1
	.short _02025330 - _0202531E - 2; case 2
	.short _02025330 - _0202531E - 2; case 3
	.short _02025336 - _0202531E - 2; case 4
	.short _0202534E - _0202531E - 2; case 5
_0202532A:
	bl GF_AssertFail
	pop {r4, pc}
_02025330:
	add r0, r2, #0x1
	strb r0, [r4, #0x1]
	pop {r4, pc}
_02025336:
	bl sub_0202519C
	strh r0, [r4, #0x8]
	ldrh r0, [r4, #0x8]
	cmp r0, #0x2
	bhs _02025346
	mov r0, #0x2
	strh r0, [r4, #0x8]
_02025346:
	ldrb r0, [r4, #0x1]
	add r0, r0, #0x1
	strb r0, [r4, #0x1]
	pop {r4, pc}
_0202534E:
	mov r1, #0x0
	strh r1, [r4, #0x8]
	mov r1, #0x2
	strb r1, [r4, #0x1]
	mov r1, #0x5
	strb r1, [r4, #0xb]
	ldrb r1, [r4, #0x6]
	add r1, r1, #0x1
	strb r1, [r4, #0x6]
	bl sub_02025210
	ldrb r1, [r4, #0x6]
	cmp r1, r0
	bne _02025370
	add r0, r4, #0x0
	bl sub_02025184
_02025370:
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02025374
sub_02025374: ; 0x02025374
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldrb r0, [r5, #0x1]
	add r7, r2, #0x0
	cmp r0, #0x5
	beq _020253DE
	add r0, r1, #0x0
	ldrb r1, [r5, #0x0]
	ldrb r2, [r5, #0xc]
	bl sub_020251DC
	add r6, r0, #0x0
	ldrh r0, [r5, #0x4]
	mov r1, #0x3c
	str r0, [sp, #0x0]
	add r0, r7, r0
	bl _s32_div_f
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x3c
	add r0, r7, r0
	bl _s32_div_f
	strh r1, [r5, #0x4]
	cmp r4, #0x0
	beq _020253DE
	ldrb r1, [r5, #0xa]
	add r0, r6, #0x0
	mul r0, r4
	cmp r1, r0
	blt _020253BA
	sub r0, r1, r0
	strb r0, [r5, #0xa]
	pop {r3-r7, pc}
_020253BA:
	cmp r1, #0x0
	beq _020253CE
	sub r0, r6, #0x1
	add r0, r1, r0
	add r1, r6, #0x0
	bl _s32_div_f
	sub r4, r4, r0
	mov r0, #0x0
	strb r0, [r5, #0xa]
_020253CE:
	ldrb r0, [r5, #0xb]
	cmp r0, r4
	ble _020253DA
	sub r0, r0, r4
	strb r0, [r5, #0xb]
	pop {r3-r7, pc}
_020253DA:
	mov r0, #0x0
	strb r0, [r5, #0xb]
_020253DE:
	pop {r3-r7, pc}

	thumb_func_start sub_020253E0
sub_020253E0: ; 0x020253E0
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r0, [sp, #0x0]
_020253EC:
	ldrb r1, [r5, #0x0]
	cmp r1, #0x0
	beq _02025474
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	beq _02025474
	ldrb r0, [r5, #0xd]
	cmp r0, #0x0
	beq _02025474
	ldrb r2, [r5, #0xc]
	add r0, r6, #0x0
	bl sub_020251B0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02025220
	mul r0, r4
	cmp r7, r0
	blt _0202541C
	add r0, r5, #0x0
	bl sub_02025184
	b _02025474
_0202541C:
	add r4, r7, #0x0
	b _0202546A
_02025420:
	ldrh r2, [r5, #0x2]
	cmp r2, r4
	ble _02025438
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl sub_02025374
	ldrh r0, [r5, #0x2]
	sub r0, r0, r4
	strh r0, [r5, #0x2]
	b _02025474
_02025438:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02025374
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02025308
	ldrh r0, [r5, #0x2]
	ldrb r1, [r5, #0x0]
	ldrb r2, [r5, #0xc]
	sub r4, r4, r0
	add r0, r6, #0x0
	bl sub_020251B0
	strh r0, [r5, #0x2]
	ldrb r0, [r5, #0x1]
	cmp r0, #0x5
	bne _0202546A
	add r0, r5, #0x0
	bl sub_02025200
	ldrh r1, [r5, #0x2]
	mul r0, r1
	strh r0, [r5, #0x2]
_0202546A:
	ldrb r0, [r5, #0x1]
	cmp r0, #0x0
	beq _02025474
	cmp r4, #0x0
	bne _02025420
_02025474:
	ldr r0, [sp, #0x0]
	add r5, #0xe
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, #0x80
	blt _020253EC
	pop {r3-r7, pc}
	.balign 4
