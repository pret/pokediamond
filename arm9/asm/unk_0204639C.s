    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204639C
FUN_0204639C: ; 0x0204639C
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	add r6, r1, #0x0
	add r1, r0, #0x0
	add r7, r2, #0x0
	bl FUN_020169D8
	add r4, r0, #0x0
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r6, [r4, #0x4]
	str r0, [r4, #0x8]
	str r7, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	mov r0, #0x20
	mov r1, #0x4
	str r5, [r4, #0x18]
	bl FUN_020169D8
	str r0, [r4, #0x1c]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_020463CC
FUN_020463CC: ; 0x020463CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r0, #0x0
	beq _020463DE
	bl ErrorHandling
_020463DE:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0204639C
	str r0, [r5, #0x10]
	pop {r4-r6, pc}

	thumb_func_start FUN_020463EC
FUN_020463EC: ; 0x020463EC
	push {r4, lr}
	add r4, r0, #0x0
	str r1, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	str r2, [r4, #0xc]
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _02046400
	beq _0204640A
_02046400:
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
_0204640A:
	pop {r4, pc}

	thumb_func_start FUN_0204640C
FUN_0204640C: ; 0x0204640C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x18]
	bl FUN_0204639C
	str r4, [r0, #0x0]
	ldr r1, [r4, #0x18]
	str r0, [r1, #0x10]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02046420
FUN_02046420: ; 0x02046420
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _0204642E
	mov r0, #0x0
	pop {r3-r5, pc}
_0204642E:
	ldr r1, [r0, #0x4]
	blx r1
	cmp r0, #0x1
	bne _02046466
_02046436:
	ldr r0, [r5, #0x10]
	ldr r4, [r0, #0x0]
	ldr r0, [r0, #0x14]
	cmp r0, #0x0
	beq _02046444
	bl FUN_02016A18
_02046444:
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #0x1c]
	bl FUN_02016A18
	ldr r0, [r5, #0x10]
	bl FUN_02016A18
	str r4, [r5, #0x10]
	cmp r4, #0x0
	bne _0204645C
	mov r0, #0x1
	pop {r3-r5, pc}
_0204645C:
	ldr r0, [r5, #0x10]
	ldr r1, [r0, #0x4]
	blx r1
	cmp r0, #0x1
	beq _02046436
_02046466:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204646C
FUN_0204646C: ; 0x0204646C
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _02046476
	mov r0, #0x1
	bx lr
_02046476:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_0204647C
FUN_0204647C: ; 0x0204647C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	bne _02046492
	add r0, r4, #0x0
	bl FUN_020373C4
	cmp r0, #0x0
	beq _02046496
_02046492:
	mov r0, #0x1
	pop {r4, pc}
_02046496:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0204649C
FUN_0204649C: ; 0x0204649C
	ldr r3, _020464A0 ; =LoadOverlay_MODULE_05
	bx r3
	.balign 4
_020464A0: .word LoadOverlay_MODULE_05

	thumb_func_start FUN_020464A4
FUN_020464A4: ; 0x020464A4
	push {r3, lr}
	bl FUN_020373AC
	cmp r0, #0x0
	beq _020464B2
	mov r0, #0x1
	pop {r3, pc}
_020464B2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020464B8
FUN_020464B8: ; 0x020464B8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020464D6
	cmp r0, #0x1
	beq _020464E8
	b _020464FC
_020464D6:
	ldr r1, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_020373D4
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020464FC
_020464E8:
	add r0, r5, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	bne _020464FC
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x1
	pop {r3-r5, pc}
_020464FC:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02046500
FUN_02046500: ; 0x02046500
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x20
	mov r1, #0xc
	add r4, r2, #0x0
	bl FUN_020169D8
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [r2, #0x0]
	str r5, [r2, #0x4]
	ldr r1, _02046524 ; =FUN_020464B8
	add r0, r6, #0x0
	str r4, [r2, #0x8]
	bl FUN_0204640C
	pop {r4-r6, pc}
	.balign 4
_02046524: .word FUN_020464B8

	thumb_func_start FUN_02046528
FUN_02046528: ; 0x02046528
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start FUN_0204652C
FUN_0204652C: ; 0x0204652C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02046530
FUN_02046530: ; 0x02046530
	add r0, #0x8
	bx lr

	thumb_func_start FUN_02046534
FUN_02046534: ; 0x02046534
	ldr r0, [r0, #0x1c]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
