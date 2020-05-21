    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FD8CC
	.extern UNK_020FD8C9
	.extern UNK_020FD8CA
	.extern UNK_020FD8C8
	.extern UNK_020FD8D0

	.text

	thumb_func_start FUN_02088D1C
FUN_02088D1C: ; 0x02088D1C
	mov r0, #0x13
	bx lr

	thumb_func_start FUN_02088D20
FUN_02088D20: ; 0x02088D20
	ldr r3, _02088D3C ; =UNK_020FD8C8
	mov r2, #0x0
_02088D24:
	ldrb r1, [r3, #0x0]
	cmp r0, r1
	bne _02088D2E
	add r0, r2, #0x0
	bx lr
_02088D2E:
	add r2, r2, #0x1
	add r3, #0xc
	cmp r2, #0x13
	blo _02088D24
	mov r0, #0x0
	bx lr
	nop
_02088D3C: .word UNK_020FD8C8

	thumb_func_start FUN_02088D40
FUN_02088D40: ; 0x02088D40
	push {r3, lr}
	bl FUN_02088D20
	bl FUN_02088D4C
	pop {r3, pc}

	thumb_func_start FUN_02088D4C
FUN_02088D4C: ; 0x02088D4C
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088D58
	bl ErrorHandling
_02088D58:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088D64 ; =UNK_020FD8CA
	ldrh r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088D64: .word UNK_020FD8CA

	thumb_func_start FUN_02088D68
FUN_02088D68: ; 0x02088D68
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088D74
	bl ErrorHandling
_02088D74:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088D80 ; =UNK_020FD8C8
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088D80: .word UNK_020FD8C8

	thumb_func_start FUN_02088D84
FUN_02088D84: ; 0x02088D84
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088D90
	bl ErrorHandling
_02088D90:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088D9C ; =UNK_020FD8C9
	ldrb r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088D9C: .word UNK_020FD8C9

	thumb_func_start FUN_02088DA0
FUN_02088DA0: ; 0x02088DA0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088DAC
	bl ErrorHandling
_02088DAC:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088DB8 ; =UNK_020FD8CC
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088DB8: .word UNK_020FD8CC

	thumb_func_start FUN_02088DBC
FUN_02088DBC: ; 0x02088DBC
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x13
	blo _02088DC8
	bl ErrorHandling
_02088DC8:
	mov r0, #0xc
	add r1, r4, #0x0
	mul r1, r0
	ldr r0, _02088DD4 ; =UNK_020FD8D0
	ldr r0, [r0, r1]
	pop {r4, pc}
	.balign 4
_02088DD4: .word UNK_020FD8D0
