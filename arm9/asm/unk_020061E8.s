	.include "asm/macros.inc"
	.include "global.inc"
	.section .text

	thumb_func_start FUN_020061E8
FUN_020061E8: ; 0x020061E8
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r7, r2, #0x0
	cmp r5, #0x0
	beq _0200620C
	add r0, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02006202
	mov r0, #0x0
	pop {r3-r7, pc}
_02006202:
	mov r1, #0x0
	add r2, r5, #0x0
	bl Call_FillMemWithValue
	b _0200620E
_0200620C:
	mov r4, #0x0
_0200620E:
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0200CA44
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200621C
FUN_0200621C: ; 0x0200621C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201B6C8
	cmp r0, #0x0
	beq _0200622C
	bl FUN_02016A18
_0200622C:
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start FUN_02006234
FUN_02006234: ; 0x02006234
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x28
	bl FUN_02016998
	add r3, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	str r0, [r3, #0x10]
	str r0, [r3, #0x14]
	str r4, [r3, #0x18]
	str r0, [r3, #0x1c]
	str r0, [r3, #0x20]
	str r0, [r3, #0x24]
	add r0, r3, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02006260
FUN_02006260: ; 0x02006260
	ldr r3, _02006264 ; =FUN_02016A18
	bx r3
	.balign 4
_02006264: .word FUN_02016A18

	thumb_func_start FUN_02006268
FUN_02006268: ; 0x02006268
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r2, #0x0
	bl FUN_02016998
	str r0, [r4, #0x1c]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02006278
FUN_02006278: ; 0x02006278
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_0200627C
FUN_0200627C: ; 0x0200627C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x1c]
	pop {r4, pc}

	thumb_func_start FUN_0200628C
FUN_0200628C: ; 0x0200628C
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02006290
FUN_02006290: ; 0x02006290
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x10]
	cmp r1, #0x3
	bhi _0200630E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020062A6: ; jump table (using 16-bit offset)
	.short _020062AE - _020062A6 - 2; case 0
	.short _020062C2 - _020062A6 - 2; case 1
	.short _020062DA - _020062A6 - 2; case 2
	.short _020062F0 - _020062A6 - 2; case 3
_020062AE:
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	mvn r1, r1
	cmp r0, r1
	beq _020062BE
	mov r1, #0x2
	bl HandleLoadOverlay
_020062BE:
	mov r0, #0x1
	str r0, [r4, #0x10]
_020062C2:
	add r1, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	add r1, #0x14
	blx r2
	cmp r0, #0x1
	bne _0200630E
	mov r0, #0x2
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	b _0200630E
_020062DA:
	add r1, r4, #0x0
	ldr r2, [r4, #0x4]
	add r1, #0x14
	blx r2
	cmp r0, #0x1
	bne _0200630E
	mov r0, #0x3
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	b _0200630E
_020062F0:
	add r1, r4, #0x0
	ldr r2, [r4, #0x8]
	add r1, #0x14
	blx r2
	cmp r0, #0x1
	bne _0200630E
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	mvn r1, r1
	cmp r0, r1
	beq _0200630A
	bl UnloadOverlayByID
_0200630A:
	mov r0, #0x1
	pop {r4, pc}
_0200630E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
