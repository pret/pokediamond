    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02014590
FUN_02014590: ; 0x02014590
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0x9c
	bl FUN_02016998
	add r1, r5, #0x0
	add r4, r0, #0x0
	bl FUN_020146F0
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020145A8
FUN_020145A8: ; 0x020145A8
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x9b
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, #0x1
	bne _020145BE
	bl FUN_020146C4
_020145BE:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020145C8
FUN_020145C8: ; 0x020145C8
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r2, [r4, #0x0]
	add r5, r0, #0x0
	str r2, [r5, #0x7c]
	add r2, r5, #0x0
	ldr r3, [r4, #0x4]
	add r2, #0x80
	str r3, [r2, #0x0]
	add r2, r5, #0x0
	ldrb r3, [r4, #0x10]
	add r2, #0x98
	strb r3, [r2, #0x0]
	add r2, r5, #0x0
	ldrb r3, [r4, #0x11]
	add r2, #0x99
	strb r3, [r2, #0x0]
	bl FUN_02014730
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014754
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014784
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02014814
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x1
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x9b
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	add r5, #0x9b
	bic r1, r0
	mov r0, #0x80
	orr r0, r1
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014630
FUN_02014630: ; 0x02014630
	push {r4, lr}
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x9b
	ldrb r2, [r1, #0x0]
	mov r1, #0xf0
	bic r2, r1
	mov r1, #0x80
	orr r2, r1
	add r1, r4, #0x0
	add r1, #0x9b
	strb r2, [r1, #0x0]
	bl FUN_0201466C
	cmp r0, #0x0
	bne _0201466A
	add r1, r4, #0x0
	add r1, #0x9b
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x1c
	bne _0201466A
	add r4, #0x9a
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02014668
	mov r0, #0x3
	pop {r4, pc}
_02014668:
	mov r0, #0x4
_0201466A:
	pop {r4, pc}

	thumb_func_start FUN_0201466C
FUN_0201466C: ; 0x0201466C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x9b
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #0x1
	beq _02014680
	bl ErrorHandling
_02014680:
	add r0, r4, #0x0
	add r0, #0x9a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x3
	bne _02014690
	ldr r0, [r4, #0x0]
	bl FUN_02022144
_02014690:
	add r1, r4, #0x0
	add r1, #0x9a
	ldrb r2, [r1, #0x0]
	mov r0, #0x0
	cmp r2, #0x3
	beq _020146AA
	add r1, r4, #0x0
	mov r0, #0x38
	add r1, #0xc
	mul r0, r2
	add r0, r1, r0
	bl FUN_02014930
_020146AA:
	cmp r0, #0x1
	bne _020146BE
	add r4, #0x9a
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020146BA
	mov r0, #0x1
	pop {r4, pc}
_020146BA:
	mov r0, #0x2
	pop {r4, pc}
_020146BE:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020146C4
FUN_020146C4: ; 0x020146C4
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, [r6, #0x0]
	bl FUN_0202212C
	add r5, r6, #0x0
	mov r4, #0x0
	add r5, #0xc
_020146D4:
	add r0, r5, #0x0
	bl FUN_02014970
	add r4, r4, #0x1
	add r5, #0x38
	cmp r4, #0x2
	blt _020146D4
	add r0, r6, #0x0
	add r6, #0x84
	ldr r1, [r6, #0x0]
	bl FUN_020146F0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020146F0
FUN_020146F0: ; 0x020146F0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	mov r1, #0x0
	mov r2, #0x9c
	bl memset
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf
	bic r1, r0
	add r0, r5, #0x0
	add r0, #0x9b
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x84
	str r4, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x3
	add r0, #0x9a
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x9b
	ldrb r1, [r0, #0x0]
	mov r0, #0xf0
	add r5, #0x9b
	bic r1, r0
	mov r0, #0x80
	orr r0, r1
	strb r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02014730
FUN_02014730: ; 0x02014730
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	ldr r0, [r1, #0x8]
	mov r1, #0x1
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	add r0, #0x84
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x4]
	ldr r2, [r3, #0x7c]
	add r3, #0x80
	ldr r3, [r3, #0x0]
	mov r0, #0x54
	bl FUN_02014A3C
	add sp, #0x8
	pop {r3, pc}

	thumb_func_start FUN_02014754
FUN_02014754: ; 0x02014754
	push {r3, lr}
	sub sp, #0x8
	add r3, r1, #0x0
	add r1, r0, #0x0
	add r1, #0x80
	ldr r1, [r1, #0x0]
	cmp r1, #0x4
	bhs _02014768
	mov r2, #0x0
	b _0201476A
_02014768:
	mov r2, #0x4
_0201476A:
	mov r1, #0x40
	str r1, [sp, #0x0]
	add r0, #0x84
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r0, [sp, #0x4]
	ldr r3, [r3, #0xc]
	mov r0, #0x54
	lsl r3, r3, #0x5
	bl FUN_02014A8C
	add sp, #0x8
	pop {r3, pc}

	thumb_func_start FUN_02014784
FUN_02014784: ; 0x02014784
	push {r3-r7, lr}
	sub sp, #0x30
	add r7, r0, #0x0
	mov r3, #0x0
	add r4, r7, #0x0
_0201478E:
	add r0, r4, #0x0
	add r3, r3, #0x1
	lsl r2, r3, #0xc
	add r0, #0x88
	add r4, r4, #0x4
	str r2, [r0, #0x0]
	cmp r3, #0x4
	blt _0201478E
	ldr r0, [r7, #0x7c]
	mov r5, #0x0
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r4, r7, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x54
	str r0, [sp, #0x8]
	ldr r0, [r1, #0x8]
	add r6, r5, #0x0
	str r0, [sp, #0x1c]
	ldr r0, [r1, #0xc]
	add r4, #0xc
	str r0, [sp, #0x20]
	add r0, r7, #0x0
	add r0, #0x88
	str r0, [sp, #0x24]
	mov r0, #0x4
	str r0, [sp, #0x28]
	add r0, r7, #0x0
	add r0, #0x98
	ldrb r1, [r0, #0x0]
	add r0, sp, #0x20
	strb r1, [r0, #0xc]
_020147D2:
	mov r1, #0x0
	mov r2, #0x2
	add r3, sp, #0x0
_020147D8:
	add r0, r5, r2
	str r0, [r3, #0xc]
	add r1, r1, #0x1
	add r2, r2, #0x2
	add r3, r3, #0x4
	cmp r1, #0x4
	blt _020147D8
	add r0, r7, #0x0
	add r0, #0x99
	ldrb r0, [r0, #0x0]
	add r2, r7, #0x0
	add r2, #0x84
	add r1, r0, r6
	add r0, sp, #0x20
	strb r1, [r0, #0xd]
	ldr r0, [sp, #0x20]
	add r1, sp, #0x0
	add r0, r0, r5
	str r0, [sp, #0x20]
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	bl FUN_020148A8
	add r5, r5, #0x1
	add r6, r6, #0x4
	add r4, #0x38
	cmp r5, #0x2
	blt _020147D2
	add sp, #0x30
	pop {r3-r7, pc}

	thumb_func_start FUN_02014814
FUN_02014814: ; 0x02014814
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r4, #0x0
_02014820:
	add r3, r4, #0x0
	add r3, #0x99
	ldrb r3, [r3, #0x0]
	add r0, r0, #0x1
	lsl r3, r3, #0x3
	add r3, r3, r1
	strb r3, [r2, #0x4]
	add r3, r4, #0x0
	add r3, #0x99
	ldrb r3, [r3, #0x0]
	lsl r3, r3, #0x3
	add r3, r3, r1
	add r3, #0x20
	strb r3, [r2, #0x5]
	add r3, r4, #0x0
	add r3, #0x98
	ldrb r3, [r3, #0x0]
	add r1, #0x20
	lsl r3, r3, #0x3
	strb r3, [r2, #0x6]
	add r3, r4, #0x0
	add r3, #0x98
	ldrb r3, [r3, #0x0]
	lsl r3, r3, #0x3
	add r3, #0x30
	strb r3, [r2, #0x7]
	add r2, r2, #0x4
	cmp r0, #0x2
	blt _02014820
	add r0, r4, #0x0
	add r0, #0x84
	ldr r0, [r0, #0x0]
	ldr r2, _02014874 ; =FUN_02014878
	str r0, [sp, #0x0]
	add r0, r4, #0x4
	mov r1, #0x2
	add r3, r4, #0x0
	bl FUN_020220C4
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_02014874: .word FUN_02014878

	thumb_func_start FUN_02014878
FUN_02014878: ; 0x02014878
	push {r4, lr}
	add r3, r2, #0x0
	add r3, #0x9b
	ldrb r3, [r3, #0x0]
	mov r4, #0xf0
	bic r3, r4
	lsl r4, r1, #0x18
	lsr r4, r4, #0x18
	lsl r4, r4, #0x1c
	lsr r4, r4, #0x18
	orr r4, r3
	add r3, r2, #0x0
	add r3, #0x9b
	strb r4, [r3, #0x0]
	cmp r1, #0x0
	bne _020148A2
	add r2, #0x9a
	strb r0, [r2, #0x0]
	ldr r0, _020148A4 ; =0x000005E4
	bl FUN_020054C8
_020148A2:
	pop {r4, pc}
	.balign 4
_020148A4: .word 0x000005E4

	thumb_func_start FUN_020148A8
FUN_020148A8: ; 0x020148A8
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	str r2, [sp, #0x8]
	str r0, [sp, #0x4]
	ldr r1, [r5, #0x24]
	ldr r2, [r5, #0x28]
	add r0, #0x28
	bl FUN_020149FC
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x4]
	ldr r6, [sp, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r5, #0x4]
	ldr r4, [sp, #0x4]
	str r1, [r0, #0x4]
	add r0, r5, #0x0
	add r0, #0x2c
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	add r6, #0x18
	add r0, #0x34
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x2d
	ldrb r1, [r0, #0x0]
	ldr r0, [sp, #0x4]
	add r7, r5, #0x0
	add r0, #0x35
	strb r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [sp, #0xc]
_020148EA:
	ldr r0, [sp, #0x8]
	mov r2, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x8]
	ldr r1, [r7, #0xc]
	add r3, r6, #0x0
	bl FUN_02006BDC
	str r0, [r4, #0x8]
	ldr r0, [r4, #0x18]
	ldr r1, [r5, #0x1c]
	bl FUN_02014BA4
	ldr r0, [r4, #0x18]
	ldr r1, [r5, #0x20]
	bl FUN_02014BC4
	ldr r0, [sp, #0xc]
	add r6, r6, #0x4
	add r0, r0, #0x1
	add r7, r7, #0x4
	add r4, r4, #0x4
	str r0, [sp, #0xc]
	cmp r0, #0x4
	blt _020148EA
	ldr r0, [sp, #0x4]
	bl FUN_020149D0
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	add r0, #0x36
	str r0, [sp, #0x4]
	strb r1, [r0, #0x0]
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start FUN_02014930
FUN_02014930: ; 0x02014930
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x28
	bl FUN_02014A10
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x36
	ldrb r0, [r0, #0x0]
	cmp r0, r4
	beq _02014952
	add r0, r5, #0x0
	bl FUN_020149D0
	add r0, r5, #0x0
	add r0, #0x36
	strb r4, [r0, #0x0]
_02014952:
	ldr r0, [r5, #0x2c]
	sub r0, r0, #0x1
	cmp r4, r0
	bne _0201495E
	mov r0, #0x1
	pop {r3-r5, pc}
_0201495E:
	add r5, #0x28
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0xc
	bl FUN_02014A08
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014970
FUN_02014970: ; 0x02014970
	push {r4-r6, lr}
	sub sp, #0x10
	add r6, r0, #0x0
	add r0, #0x35
	ldrb r0, [r0, #0x0]
	ldr r1, [r6, #0x18]
	add r3, r6, #0x0
	str r0, [sp, #0x0]
	ldrh r0, [r1, #0x0]
	mov r2, #0x0
	add r3, #0x34
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x4]
	ldrh r0, [r1, #0x2]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r1, [r6, #0x4]
	ldrb r3, [r3, #0x0]
	lsl r1, r1, #0x18
	ldr r0, [r6, #0x0]
	lsr r1, r1, #0x18
	bl FUN_02018540
	ldr r1, [r6, #0x4]
	ldr r0, [r6, #0x0]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_0201AC68
	mov r4, #0x0
	add r5, r6, #0x0
_020149B4:
	ldr r0, [r5, #0x8]
	bl FUN_02016A18
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x4
	blt _020149B4
	add r0, r6, #0x0
	mov r1, #0x0
	mov r2, #0x38
	bl memset
	add sp, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_020149D0
FUN_020149D0: ; 0x020149D0
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, #0x28
	bl FUN_02014A10
	add r2, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x35
	ldrb r0, [r0, #0x0]
	lsl r2, r2, #0x2
	add r2, r4, r2
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x4]
	add r4, #0x34
	ldrb r3, [r4, #0x0]
	ldr r2, [r2, #0x18]
	bl FUN_02014B58
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020149FC
FUN_020149FC: ; 0x020149FC
	str r1, [r0, #0x0]
	str r2, [r0, #0x4]
	mov r1, #0x0
	str r1, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_02014A08
FUN_02014A08: ; 0x02014A08
	ldr r2, [r0, #0x8]
	add r1, r2, r1
	str r1, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02014A10
FUN_02014A10: ; 0x02014A10
	push {r4-r5}
	ldr r5, [r0, #0x4]
	mov r2, #0x0
	cmp r5, #0x0
	bls _02014A34
	ldr r3, [r0, #0x0]
	ldr r4, [r0, #0x8]
_02014A1E:
	ldr r1, [r3, #0x0]
	cmp r1, r4
	blt _02014A2A
	add r0, r2, #0x0
	pop {r4-r5}
	bx lr
_02014A2A:
	ldr r1, [r0, #0x4]
	add r2, r2, #0x1
	add r3, r3, #0x4
	cmp r2, r1
	blo _02014A1E
_02014A34:
	sub r0, r5, #0x1
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02014A3C
FUN_02014A3C: ; 0x02014A3C
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x24]
	mov r1, #0x14
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x14
	mov r0, #0x0
_02014A58:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _02014A58
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x4]
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	mov r2, #0x1
	add r3, r4, #0x4
	bl FUN_02006BB0
	str r0, [r4, #0x8]
	str r5, [r4, #0x0]
	ldr r0, [sp, #0x20]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r0, _02014A88 ; =FUN_02014AD4
	add r1, r4, #0x0
	mov r2, #0x80
	bl FUN_0200CA98
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02014A88: .word FUN_02014AD4

	thumb_func_start FUN_02014A8C
FUN_02014A8C: ; 0x02014A8C
	push {r3-r7, lr}
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	mov r1, #0x14
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r2, r4, #0x0
	mov r1, #0x14
	mov r0, #0x0
_02014AA6:
	strb r0, [r2, #0x0]
	add r2, r2, #0x1
	sub r1, r1, #0x1
	bne _02014AA6
	ldr r1, [sp, #0x0]
	ldr r3, [sp, #0x1c]
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl FUN_02006C08
	str r0, [r4, #0x4]
	str r5, [r4, #0x8]
	ldr r0, [sp, #0x18]
	str r6, [r4, #0xc]
	str r0, [r4, #0x10]
	ldr r0, _02014AD0 ; =FUN_02014B10
	add r1, r4, #0x0
	mov r2, #0x80
	bl FUN_0200CA98
	pop {r3-r7, pc}
	.balign 4
_02014AD0: .word FUN_02014B10

	thumb_func_start FUN_02014AD4
FUN_02014AD4: ; 0x02014AD4
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x4]
	add r5, r0, #0x0
	ldr r0, [r1, #0x14]
	ldr r1, [r1, #0x10]
	bl DC_FlushRange
	ldr r3, [r4, #0x4]
	ldr r0, [r4, #0x10]
	str r0, [sp, #0x0]
	ldr r1, [r4, #0xc]
	ldr r2, [r3, #0x14]
	lsl r1, r1, #0x18
	ldr r0, [r4, #0x0]
	ldr r3, [r3, #0x10]
	lsr r1, r1, #0x18
	bl FUN_02017E14
	add r0, r5, #0x0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x8]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02014B10
FUN_02014B10: ; 0x02014B10
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x10]
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02014B34
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0xc]
	ldr r0, [r0, #0xc]
	ldr r2, [r4, #0x10]
	bl GX_LoadBGPltt
	b _02014B44
_02014B34:
	cmp r0, #0x4
	bne _02014B44
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0xc]
	ldr r0, [r0, #0xc]
	ldr r2, [r4, #0x10]
	bl GXS_LoadBGPltt
_02014B44:
	add r0, r5, #0x0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}

	thumb_func_start FUN_02014B58
FUN_02014B58: ; 0x02014B58
	push {r3-r6, lr}
	sub sp, #0x1c
	add r4, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldrh r6, [r1, #0x0]
	ldrh r3, [r1, #0x2]
	lsl r2, r2, #0x18
	lsl r6, r6, #0x15
	lsr r6, r6, #0x18
	lsl r3, r3, #0x15
	str r6, [sp, #0x0]
	lsr r3, r3, #0x18
	str r3, [sp, #0x4]
	add r1, #0xc
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	str r6, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r3, [sp, #0x30]
	lsl r1, r4, #0x18
	lsl r3, r3, #0x18
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	add r5, r0, #0x0
	bl FUN_02018170
	lsl r1, r4, #0x18
	add r0, r5, #0x0
	lsr r1, r1, #0x18
	bl FUN_0201AC68
	add sp, #0x1c
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02014BA4
FUN_02014BA4: ; 0x02014BA4
	push {r3-r4}
	ldr r2, [r0, #0x8]
	add r0, #0xc
	lsr r4, r2, #0x1
	mov r3, #0x0
	cmp r4, #0x0
	ble _02014BC0
_02014BB2:
	ldrh r2, [r0, #0x0]
	add r3, r3, #0x1
	add r2, r2, r1
	strh r2, [r0, #0x0]
	add r0, r0, #0x2
	cmp r3, r4
	blt _02014BB2
_02014BC0:
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02014BC4
FUN_02014BC4: ; 0x02014BC4
	push {r4-r5}
	ldr r2, [r0, #0x8]
	add r0, #0xc
	lsr r3, r2, #0x1
	mov r2, #0x0
	cmp r3, #0x0
	ble _02014BEA
	ldr r4, _02014BF0 ; =0x00000FFF
	lsl r1, r1, #0xc
_02014BD6:
	ldrh r5, [r0, #0x0]
	add r2, r2, #0x1
	and r5, r4
	strh r5, [r0, #0x0]
	ldrh r5, [r0, #0x0]
	orr r5, r1
	strh r5, [r0, #0x0]
	add r0, r0, #0x2
	cmp r2, r3
	blt _02014BD6
_02014BEA:
	pop {r4-r5}
	bx lr
	nop
_02014BF0: .word 0x00000FFF
