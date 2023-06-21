	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F828C
UNK_020F828C: ; 0x020F828C
	.word sub_0206C64C, sub_0202DA80, 0x00000000, sub_0206C154
	.word sub_0202DA78, 0x00000000, sub_0206C1E0, sub_0206C004
	.word 0x00000000, sub_0206C258, sub_0206C008, sub_0206C024
	.word sub_0206C2C4, sub_0206C020, sub_0206C044, sub_0206C32C
	.word sub_0206C010, sub_0206C064, sub_0206C428, sub_0206C018
	.word sub_0206C080, sub_0206C4B4, sub_0206C020, sub_0206C0A0
	.word sub_0206C4B4, sub_0206C020, sub_0206C0A8, sub_0206C540
	.word sub_0206C010, sub_0206C0B0, sub_0206C540, sub_0206C010
	.word sub_0206C0B8, sub_0206C6CC, sub_0206C6FC, sub_0206C0C0

	.text

	thumb_func_start sub_0206BF90
sub_0206BF90: ; 0x0206BF90
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x5
	mov r1, #0x8
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x5
	mov r1, #0x8
	bl AllocFromHeap
	add r6, r0, #0x0
	ldr r0, _0206BFE4 ; =UNK_020F828C
	mov r1, #0xc
	add r2, r5, #0x0
	bl sub_0202D8D0
	str r5, [r4, #0x0]
	mov r0, #0x0
	strb r0, [r4, #0x4]
	str r5, [r6, #0x0]
	strb r0, [r6, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x4
	bl MOD11_02231344
	add r0, r5, #0x0
	add r1, r6, #0x4
	bl MOD11_02231350
	ldr r0, _0206BFE8 ; =sub_0206C550
	add r1, r4, #0x0
	mov r2, #0x0
	bl sub_0200CA44
	ldr r0, _0206BFEC ; =sub_0206C5DC
	add r1, r6, #0x0
	mov r2, #0x0
	bl sub_0200CA44
	pop {r4-r6, pc}
	nop
_0206BFE4: .word UNK_020F828C
_0206BFE8: .word sub_0206C550
_0206BFEC: .word sub_0206C5DC

	thumb_func_start sub_0206BFF0
sub_0206BFF0: ; 0x0206BFF0
	ldr r3, _0206BFFC ; =sub_0202D8D0
	add r2, r0, #0x0
	ldr r0, _0206C000 ; =UNK_020F828C
	mov r1, #0xc
	bx r3
	nop
_0206BFFC: .word sub_0202D8D0
_0206C000: .word UNK_020F828C

	thumb_func_start sub_0206C004
sub_0206C004: ; 0x0206C004
	mov r0, #0x4
	bx lr

	thumb_func_start sub_0206C008
sub_0206C008: ; 0x0206C008
	ldr r3, _0206C00C ; =PlayerProfile_sizeof
	bx r3
	.balign 4
_0206C00C: .word PlayerProfile_sizeof

	thumb_func_start sub_0206C010
sub_0206C010: ; 0x0206C010
	ldr r3, _0206C014 ; =SaveArray_Party_sizeof
	bx r3
	.balign 4
_0206C014: .word SaveArray_Party_sizeof

	thumb_func_start sub_0206C018
sub_0206C018: ; 0x0206C018
	mov r0, #0xfa
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start sub_0206C020
sub_0206C020: ; 0x0206C020
	mov r0, #0x34
	bx lr

	thumb_func_start sub_0206C024
sub_0206C024: ; 0x0206C024
	ldr r3, [r1, #0x0]
	mov r1, #0x80
	ldr r2, [r3, #0x0]
	tst r1, r2
	beq _0206C038
	lsl r0, r0, #0x3
	add r0, r3, r0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bx lr
_0206C038:
	lsl r0, r0, #0x2
	add r0, r3, r0
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_0206C044
sub_0206C044: ; 0x0206C044
	ldr r1, [r1, #0x0]
	mov r2, #0x80
	ldr r3, [r1, #0x0]
	tst r2, r3
	beq _0206C05A
	lsl r2, r0, #0x1
	mov r0, #0x34
	add r1, #0x28
	mul r0, r2
	add r0, r1, r0
	bx lr
_0206C05A:
	mov r2, #0x34
	add r1, #0x28
	mul r2, r0
	add r0, r1, r2
	bx lr

	thumb_func_start sub_0206C064
sub_0206C064: ; 0x0206C064
	ldr r3, [r1, #0x0]
	mov r1, #0x80
	ldr r2, [r3, #0x0]
	tst r1, r2
	beq _0206C076
	lsl r0, r0, #0x3
	add r0, r3, r0
	ldr r0, [r0, #0x4]
	bx lr
_0206C076:
	lsl r0, r0, #0x2
	add r0, r3, r0
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start sub_0206C080
sub_0206C080: ; 0x0206C080
	ldr r3, [r1, #0x0]
	mov r1, #0x80
	ldr r2, [r3, #0x0]
	tst r2, r1
	beq _0206C094
	lsl r0, r0, #0x3
	add r0, r3, r0
	add r1, #0x98
	ldr r0, [r0, r1]
	bx lr
_0206C094:
	lsl r0, r0, #0x2
	add r0, r3, r0
	add r1, #0x98
	ldr r0, [r0, r1]
	bx lr
	.balign 4

	thumb_func_start sub_0206C0A0
sub_0206C0A0: ; 0x0206C0A0
	ldr r0, [r1, #0x0]
	add r0, #0x5c
	bx lr
	.balign 4

	thumb_func_start sub_0206C0A8
sub_0206C0A8: ; 0x0206C0A8
	ldr r0, [r1, #0x0]
	add r0, #0xc4
	bx lr
	.balign 4

	thumb_func_start sub_0206C0B0
sub_0206C0B0: ; 0x0206C0B0
	ldr r0, [r1, #0x0]
	ldr r0, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start sub_0206C0B8
sub_0206C0B8: ; 0x0206C0B8
	ldr r0, [r1, #0x0]
	ldr r0, [r0, #0x10]
	bx lr
	.balign 4

	thumb_func_start sub_0206C0C0
sub_0206C0C0: ; 0x0206C0C0
	lsl r0, r0, #0x2
	add r0, r1, r0
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start sub_0206C0C8
sub_0206C0C8: ; 0x0206C0C8
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r0, #0x5
	mov r1, #0x4
	str r2, [sp, #0x8]
	add r7, r3, #0x0
	bl AllocFromHeap
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MOD11_022300D4
	add r5, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MOD11_022300F4
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MOD11_02230100
	mov r12, r0
	add r0, sp, #0x10
	ldrh r3, [r4, #0x0]
	ldrb r0, [r0, #0x10]
	add r1, r3, #0x5
	add r2, r1, r0
	mov r1, #0x1
	lsl r1, r1, #0xc
	cmp r2, r1
	bls _0206C110
	mov r1, r12
	strh r3, [r1, #0x0]
	mov r1, #0x0
	strh r1, [r4, #0x0]
_0206C110:
	ldr r1, [sp, #0x4]
	mov r3, #0x0
	strb r1, [r6, #0x0]
	ldr r1, [sp, #0x8]
	strb r1, [r6, #0x1]
	add r1, sp, #0x10
	ldrb r1, [r1, #0x10]
	strh r1, [r6, #0x2]
_0206C120:
	ldrb r2, [r6, r3]
	ldrh r1, [r4, #0x0]
	add r3, r3, #0x1
	strb r2, [r5, r1]
	ldrh r1, [r4, #0x0]
	add r1, r1, #0x1
	strh r1, [r4, #0x0]
	cmp r3, #0x4
	blo _0206C120
	mov r3, #0x0
	cmp r0, #0x0
	ble _0206C14A
_0206C138:
	ldrb r2, [r7, r3]
	ldrh r1, [r4, #0x0]
	add r3, r3, #0x1
	strb r2, [r5, r1]
	ldrh r1, [r4, #0x0]
	add r1, r1, #0x1
	strh r1, [r4, #0x0]
	cmp r3, r0
	blt _0206C138
_0206C14A:
	add r0, r6, #0x0
	bl FreeToHeap
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start sub_0206C154
sub_0206C154: ; 0x0206C154
	push {r3-r7, lr}
	str r3, [sp, #0x0]
	add r0, r3, #0x0
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl MOD11_022300DC
	add r7, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MOD11_02230118
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	bl MOD11_02230124
	ldrh r1, [r4, #0x0]
	add r2, r1, r5
	add r3, r2, #0x1
	mov r2, #0x1
	lsl r2, r2, #0xc
	cmp r3, r2
	ble _0206C186
	strh r1, [r0, #0x0]
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0206C186:
	mov r0, #0x0
	cmp r5, #0x0
	ble _0206C19E
_0206C18C:
	ldrb r2, [r6, r0]
	ldrh r1, [r4, #0x0]
	add r0, r0, #0x1
	strb r2, [r7, r1]
	ldrh r1, [r4, #0x0]
	add r1, r1, #0x1
	strh r1, [r4, #0x0]
	cmp r0, r5
	blt _0206C18C
_0206C19E:
	pop {r3-r7, pc}

	thumb_func_start sub_0206C1A0
sub_0206C1A0: ; 0x0206C1A0
	push {r0-r3}
	push {r3, lr}
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C1BA
	mov r0, #0x0
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
_0206C1BA:
	mov r0, #0x33
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C1CE
	mov r0, #0x0
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
_0206C1CE:
	mov r0, #0x18
	add r1, sp, #0xc
	mov r2, #0x4
	bl sub_02030ADC
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start sub_0206C1E0
sub_0206C1E0: ; 0x0206C1E0
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x2
	add r1, r1, r0
	mov r0, #0x5f
	ldr r2, [r2, #0x0]
	lsl r0, r0, #0x2
	str r2, [r1, r0]
	ldr r0, _0206C1F8 ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	.balign 4
_0206C1F8: .word 0x00001020

	thumb_func_start sub_0206C1FC
sub_0206C1FC: ; 0x0206C1FC
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C210
	mov r0, #0x0
	pop {r4, pc}
_0206C210:
	ldr r0, [r4, #0x0]
	add r4, #0x20
	add r0, #0xf8
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	bl PlayerProfile_Copy
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0206C224
sub_0206C224: ; 0x0206C224
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C238
	mov r0, #0x0
	pop {r4, pc}
_0206C238:
	mov r0, #0x34
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C246
	mov r0, #0x0
	pop {r4, pc}
_0206C246:
	bl PlayerProfile_sizeof
	add r4, #0x20
	add r2, r0, #0x0
	mov r0, #0x19
	add r1, r4, #0x0
	bl sub_02030A78
	pop {r4, pc}

	thumb_func_start sub_0206C258
sub_0206C258: ; 0x0206C258
	ldr r0, _0206C264 ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	nop
_0206C264: .word 0x00001020

	thumb_func_start sub_0206C268
sub_0206C268: ; 0x0206C268
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C27C
	mov r0, #0x0
	pop {r4, pc}
_0206C27C:
	ldr r3, [r4, #0x0]
	add r4, #0x20
	add r3, #0x28
	mov r2, #0x6
_0206C284:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206C284
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start sub_0206C294
sub_0206C294: ; 0x0206C294
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C2A8
	mov r0, #0x0
	pop {r4, pc}
_0206C2A8:
	mov r0, #0x35
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C2B6
	mov r0, #0x0
	pop {r4, pc}
_0206C2B6:
	add r4, #0x20
	mov r0, #0x1a
	add r1, r4, #0x0
	mov r2, #0x34
	bl sub_02030A78
	pop {r4, pc}

	thumb_func_start sub_0206C2C4
sub_0206C2C4: ; 0x0206C2C4
	ldr r0, _0206C2D0 ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	nop
_0206C2D0: .word 0x00001020

	thumb_func_start sub_0206C2D4
sub_0206C2D4: ; 0x0206C2D4
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C2E8
	mov r0, #0x0
	pop {r4, pc}
_0206C2E8:
	ldr r0, [r4, #0x0]
	add r4, #0x20
	ldr r0, [r0, #0x4]
	add r1, r4, #0x0
	bl CopyPlayerParty
	mov r0, #0x1
	pop {r4, pc}

	thumb_func_start sub_0206C2F8
sub_0206C2F8: ; 0x0206C2F8
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C30C
	mov r0, #0x0
	pop {r4, pc}
_0206C30C:
	mov r0, #0x36
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C31A
	mov r0, #0x0
	pop {r4, pc}
_0206C31A:
	bl SaveArray_Party_sizeof
	add r4, #0x20
	add r2, r0, #0x0
	mov r0, #0x1b
	add r1, r4, #0x0
	bl sub_02030A78
	pop {r4, pc}

	thumb_func_start sub_0206C32C
sub_0206C32C: ; 0x0206C32C
	ldr r0, _0206C338 ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	nop
_0206C338: .word 0x00001020

	thumb_func_start sub_0206C33C
sub_0206C33C: ; 0x0206C33C
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C350
	mov r0, #0x0
	pop {r4, pc}
_0206C350:
	ldr r2, [r4, #0x0]
	add r1, #0x10
	add r0, r4, #0x0
	ldr r1, [r2, r1]
	add r0, #0x20
	bl Chatot_Copy
	mov r0, #0x1
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0206C364
sub_0206C364: ; 0x0206C364
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C378
	mov r0, #0x0
	pop {r4, pc}
_0206C378:
	mov r0, #0x37
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C386
	mov r0, #0x0
	pop {r4, pc}
_0206C386:
	add r4, #0x20
	mov r2, #0xfa
	mov r0, #0x1c
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl sub_02030A78
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0206C398
sub_0206C398: ; 0x0206C398
	push {r3-r7, lr}
	add r5, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C3AC
	mov r0, #0x0
	pop {r3-r7, pc}
_0206C3AC:
	ldr r4, [r5, #0x0]
	mov r0, #0x80
	ldr r1, [r4, #0x0]
	tst r0, r1
	beq _0206C3BE
	bl sub_02031190
	lsl r0, r0, #0x3
	b _0206C3C4
_0206C3BE:
	bl sub_02031190
	lsl r0, r0, #0x2
_0206C3C4:
	add r0, r4, r0
	mov r1, #0x53
	add r0, #0xf8
	lsl r1, r1, #0x2
	add r2, r5, #0x0
	ldr r0, [r0, #0x0]
	ldr r1, [r4, r1]
	add r2, #0x20
	bl sub_0206C66C
	mov r4, #0x0
	mov r6, #0x5
	mov r7, #0x88
_0206C3DE:
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl AllocFromHeap
	str r0, [r5, #0x10]
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _0206C3DE
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start sub_0206C3F4
sub_0206C3F4: ; 0x0206C3F4
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C408
	mov r0, #0x0
	pop {r4, pc}
_0206C408:
	mov r0, #0x38
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C416
	mov r0, #0x0
	pop {r4, pc}
_0206C416:
	add r4, #0x20
	mov r2, #0xfa
	mov r0, #0x21
	add r1, r4, #0x0
	lsl r2, r2, #0x2
	bl sub_02030A78
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0206C428
sub_0206C428: ; 0x0206C428
	ldr r0, _0206C434 ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	nop
_0206C434: .word 0x00001020

	thumb_func_start sub_0206C438
sub_0206C438: ; 0x0206C438
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C44E
	mov r0, #0x0
	pop {r3-r5, pc}
_0206C44E:
	ldr r1, [r5, #0x0]
	mov r0, #0x34
	mul r0, r4
	add r3, r1, r0
	add r3, #0x28
	add r5, #0x20
	mov r2, #0x6
_0206C45C:
	ldmia r3!, {r0-r1}
	stmia r5!, {r0-r1}
	sub r2, r2, #0x1
	bne _0206C45C
	ldr r0, [r3, #0x0]
	str r0, [r5, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start sub_0206C46C
sub_0206C46C: ; 0x0206C46C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C484
	mov r0, #0x0
	pop {r4-r6, pc}
_0206C484:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C494
	mov r0, #0x0
	pop {r4-r6, pc}
_0206C494:
	cmp r4, #0x1
	bne _0206C4A6
	add r5, #0x20
	mov r0, #0x1d
	add r1, r5, #0x0
	mov r2, #0x34
	bl sub_02030A78
	pop {r4-r6, pc}
_0206C4A6:
	add r5, #0x20
	mov r0, #0x1e
	add r1, r5, #0x0
	mov r2, #0x34
	bl sub_02030A78
	pop {r4-r6, pc}

	thumb_func_start sub_0206C4B4
sub_0206C4B4: ; 0x0206C4B4
	ldr r0, _0206C4C0 ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	nop
_0206C4C0: .word 0x00001020

	thumb_func_start sub_0206C4C4
sub_0206C4C4: ; 0x0206C4C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C4DA
	mov r0, #0x0
	pop {r3-r5, pc}
_0206C4DA:
	ldr r1, [r5, #0x0]
	lsl r0, r4, #0x2
	add r0, r1, r0
	add r5, #0x20
	ldr r0, [r0, #0x4]
	add r1, r5, #0x0
	bl CopyPlayerParty
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_0206C4F0
sub_0206C4F0: ; 0x0206C4F0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _0206C508
	mov r0, #0x0
	pop {r4-r6, pc}
_0206C508:
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	bl sub_020315D8
	cmp r0, #0x0
	bne _0206C518
	mov r0, #0x0
	pop {r4-r6, pc}
_0206C518:
	cmp r4, #0x1
	bne _0206C52E
	bl SaveArray_Party_sizeof
	add r5, #0x20
	add r2, r0, #0x0
	mov r0, #0x1f
	add r1, r5, #0x0
	bl sub_02030A78
	pop {r4-r6, pc}
_0206C52E:
	bl SaveArray_Party_sizeof
	add r5, #0x20
	add r2, r0, #0x0
	mov r0, #0x20
	add r1, r5, #0x0
	bl sub_02030A78
	pop {r4-r6, pc}

	thumb_func_start sub_0206C540
sub_0206C540: ; 0x0206C540
	ldr r0, _0206C54C ; =0x00001020
	ldrb r1, [r3, r0]
	add r1, r1, #0x1
	strb r1, [r3, r0]
	bx lr
	nop
_0206C54C: .word 0x00001020

	thumb_func_start sub_0206C550
sub_0206C550: ; 0x0206C550
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	bl MOD11_022300D4
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl MOD11_022300E8
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl MOD11_022300F4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	bl MOD11_02230100
	add r7, r0, #0x0
	ldrb r0, [r5, #0x4]
	cmp r0, #0x0
	beq _0206C582
	cmp r0, #0xff
	b _0206C5CC
_0206C582:
	bl sub_02030C58
	mov r1, #0x42
	lsl r1, r1, #0x2
	cmp r0, r1
	bne _0206C5D8
	ldr r0, [sp, #0x4]
	ldrh r1, [r4, #0x0]
	ldrh r0, [r0, #0x0]
	cmp r1, r0
	beq _0206C5D8
	ldrh r0, [r7, #0x0]
	cmp r1, r0
	bne _0206C5A4
	mov r0, #0x0
	strh r0, [r4, #0x0]
	strh r0, [r7, #0x0]
_0206C5A4:
	ldrh r1, [r4, #0x0]
	add r0, r1, #0x2
	ldrb r2, [r6, r0]
	add r0, r1, #0x3
	ldrb r0, [r6, r0]
	add r1, r6, r1
	lsl r0, r0, #0x8
	orr r0, r2
	add r5, r0, #0x4
	mov r0, #0x17
	add r2, r5, #0x0
	bl sub_02030ADC
	cmp r0, #0x1
	bne _0206C5D8
	ldrh r0, [r4, #0x0]
	add sp, #0x8
	add r0, r0, r5
	strh r0, [r4, #0x0]
	pop {r3-r7, pc}
_0206C5CC:
	add r0, r5, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x0]
	bl sub_0200CAB4
_0206C5D8:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start sub_0206C5DC
sub_0206C5DC: ; 0x0206C5DC
	push {r3-r7, lr}
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x0]
	bl MOD11_022300DC
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	bl MOD11_0223010C
	add r4, r0, #0x0
	ldr r0, [r5, #0x0]
	bl MOD11_02230118
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	bl MOD11_02230124
	ldrb r1, [r5, #0x4]
	cmp r1, #0x0
	beq _0206C60A
	cmp r1, #0xff
	b _0206C63E
_0206C60A:
	ldrh r1, [r4, #0x0]
	ldrh r2, [r7, #0x0]
	cmp r1, r2
	beq _0206C64A
	ldrh r2, [r0, #0x0]
	cmp r1, r2
	bne _0206C61E
	mov r1, #0x0
	strh r1, [r4, #0x0]
	strh r1, [r0, #0x0]
_0206C61E:
	ldrh r1, [r4, #0x0]
	ldr r0, [r5, #0x0]
	add r1, r6, r1
	bl MOD11_022567E0
	ldrh r0, [r4, #0x0]
	add r1, r0, #0x2
	ldrb r2, [r6, r1]
	add r1, r0, #0x3
	ldrb r1, [r6, r1]
	lsl r1, r1, #0x8
	orr r1, r2
	add r1, r1, #0x4
	add r0, r0, r1
	strh r0, [r4, #0x0]
	pop {r3-r7, pc}
_0206C63E:
	add r0, r5, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x0]
	bl sub_0200CAB4
_0206C64A:
	pop {r3-r7, pc}

	thumb_func_start sub_0206C64C
sub_0206C64C: ; 0x0206C64C
	push {r4, lr}
	add r4, r3, #0x0
	add r0, r4, #0x0
	mov r1, #0xff
	bl MOD11_0223135C
	add r0, r4, #0x0
	mov r1, #0xff
	bl MOD11_02231368
	add r0, r4, #0x0
	mov r1, #0x1
	bl MOD11_02231374
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_0206C66C
sub_0206C66C: ; 0x0206C66C
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r6, r0, #0x0
	add r5, r1, #0x0
	bl PlayerProfile_GetNamePtr
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl CopyU16StringArray
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerID
	str r0, [r4, #0x10]
	add r0, r6, #0x0
	bl PlayerProfile_GetLanguage
	strb r0, [r4, #0x14]
	add r0, r6, #0x0
	bl PlayerProfile_GetVersion
	strb r0, [r4, #0x15]
	add r0, r6, #0x0
	bl PlayerProfile_GetTrainerGender
	strb r0, [r4, #0x16]
	mov r0, #0x0
	add r1, r4, #0x0
_0206C6A4:
	ldr r2, [r5, #0x10]
	str r2, [r1, #0x18]
	ldrb r3, [r5, #0x15]
	add r2, r4, r0
	add r2, #0x58
	strb r3, [r2, #0x0]
	add r2, r4, r0
	ldrb r3, [r5, #0x14]
	add r2, #0x68
	add r1, r1, #0x4
	strb r3, [r2, #0x0]
	add r2, r4, r0
	ldrb r3, [r5, #0x16]
	add r2, #0x78
	add r0, r0, #0x1
	add r5, #0x88
	strb r3, [r2, #0x0]
	cmp r0, #0x10
	blt _0206C6A4
	pop {r4-r6, pc}

	thumb_func_start sub_0206C6CC
sub_0206C6CC: ; 0x0206C6CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r4, r3, #0x0
	bl sub_02031190
	cmp r5, r0
	beq _0206C6EE
	mov r0, #0x53
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r1, r6, #0x0
	mov r2, #0x1
	mov r3, #0x5
	bl sub_02025520
_0206C6EE:
	ldr r0, _0206C6F8 ; =0x00001020
	ldrb r1, [r4, r0]
	add r1, r1, #0x1
	strb r1, [r4, r0]
	pop {r4-r6, pc}
	.balign 4
_0206C6F8: .word 0x00001020

	thumb_func_start sub_0206C6FC
sub_0206C6FC: ; 0x0206C6FC
	mov r0, #0x88
	bx lr
