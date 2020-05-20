    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206E0F0
FUN_0206E0F0: ; 0x0206E0F0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x17
	blo _0206E0FC
	bl ErrorHandling
_0206E0FC:
	ldr r0, _0206E104 ; =0x020F83E0
	lsl r1, r4, #0x2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_0206E104: .word 0x020F83E0

	thumb_func_start FUN_0206E108
FUN_0206E108: ; 0x0206E108
	mov r0, #0x26
	bx lr

	thumb_func_start FUN_0206E10C
FUN_0206E10C: ; 0x0206E10C
	mov r0, #0xb2
	bx lr

	thumb_func_start FUN_0206E110
FUN_0206E110: ; 0x0206E110
	mov r0, #0xb3
	bx lr

	thumb_func_start FUN_0206E114
FUN_0206E114: ; 0x0206E114
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x17
	blo _0206E120
	bl ErrorHandling
_0206E120:
	ldr r0, _0206E128 ; =0x020F843C
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_0206E128: .word 0x020F843C

	thumb_func_start FUN_0206E12C
FUN_0206E12C: ; 0x0206E12C
	mov r0, #0x1b
	bx lr

	thumb_func_start FUN_0206E130
FUN_0206E130: ; 0x0206E130
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0206E12C
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	bl FUN_0206E0F0
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x28]
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0200C00C
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206E164
FUN_0206E164: ; 0x0206E164
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0206E12C
	str r0, [sp, #0x10]
	bl FUN_0206E108
	add r3, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x3
	str r0, [sp, #0x4]
	str r5, [sp, #0x8]
	ldr r2, [sp, #0x10]
	add r0, r6, #0x0
	add r1, r7, #0x0
	str r4, [sp, #0xc]
	bl FUN_0200C06C
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0206E198
FUN_0206E198: ; 0x0206E198
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x18]
	bl FUN_0206E12C
	add r4, r0, #0x0
	bl FUN_0206E108
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x3
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x30]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x34]
	add r1, r6, #0x0
	str r0, [sp, #0x14]
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl FUN_0200C0DC
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0206E1D4
FUN_0206E1D4: ; 0x0206E1D4
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	bl FUN_0206E12C
	str r0, [sp, #0x8]
	bl FUN_0206E10C
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r4, #0x0
	str r6, [sp, #0x4]
	bl FUN_0200C124
	bl FUN_0206E12C
	add r6, r0, #0x0
	bl FUN_0206E110
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	str r7, [sp, #0x4]
	bl FUN_0200C13C
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_0206E21C
FUN_0206E21C: ; 0x0206E21C
	ldr r3, _0206E220 ; =FUN_0200C358
	bx r3
	.balign 4
_0206E220: .word FUN_0200C358

	thumb_func_start FUN_0206E224
FUN_0206E224: ; 0x0206E224
	ldr r3, _0206E228 ; =FUN_0200C368
	bx r3
	.balign 4
_0206E228: .word FUN_0200C368

	thumb_func_start FUN_0206E22C
FUN_0206E22C: ; 0x0206E22C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_0200C378
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200C388
	pop {r3-r5, pc}

	thumb_func_start FUN_0206E240
FUN_0206E240: ; 0x0206E240
	push {r4-r7, lr}
	sub sp, #0x34
	add r6, r3, #0x0
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, sp, #0x0
	mov r3, #0x6
_0206E24E:
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	sub r3, r3, #0x1
	bne _0206E24E
	ldr r0, [r6, #0x0]
	str r0, [r5, #0x0]
	add r0, r2, #0x0
	bl FUN_0206E114
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r7, #0x0
	add r2, sp, #0x0
	bl FUN_0200C154
	add sp, #0x34
	pop {r4-r7, pc}

	thumb_func_start FUN_0206E270
FUN_0206E270: ; 0x0206E270
	ldr r3, _0206E274 ; =FUN_0200C3DC
	bx r3
	.balign 4
_0206E274: .word FUN_0200C3DC

	thumb_func_start FUN_0206E278
FUN_0206E278: ; 0x0206E278
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x3
	blo _0206E284
	bl ErrorHandling
_0206E284:
	ldr r0, _0206E28C ; =0x020F83D4
	lsl r1, r4, #0x2
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_0206E28C: .word 0x020F83D4

	thumb_func_start FUN_0206E290
FUN_0206E290: ; 0x0206E290
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x3
	blo _0206E29C
	bl ErrorHandling
_0206E29C:
	ldr r0, _0206E2A4 ; =0x020F83D0
	ldrb r0, [r0, r4]
	pop {r4, pc}
	nop
_0206E2A4: .word 0x020F83D0

	thumb_func_start FUN_0206E2A8
FUN_0206E2A8: ; 0x0206E2A8
	mov r0, #0x1b
	bx lr

	thumb_func_start FUN_0206E2AC
FUN_0206E2AC: ; 0x0206E2AC
	push {r3-r7, lr}
	sub sp, #0x10
	add r7, r3, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0206E2A8
	str r0, [sp, #0xc]
	add r0, r7, #0x0
	bl FUN_0206E278
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x28]
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0200C00C
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206E2E0
FUN_0206E2E0: ; 0x0206E2E0
	ldr r3, _0206E2E4 ; =FUN_0200C358
	bx r3
	.balign 4
_0206E2E4: .word FUN_0200C358

	thumb_func_start FUN_0206E2E8
FUN_0206E2E8: ; 0x0206E2E8
	ldr r3, _0206E2EC ; =FUN_0200C3DC
	bx r3
	.balign 4
_0206E2EC: .word FUN_0200C3DC
