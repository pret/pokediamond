	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202D8D0
FUN_0202D8D0: ; 0x0202D8D0
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0202D914 ; =0x021C59E0
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	cmp r0, #0x0
	bne _0202D8EC
	mov r0, #0xf
	mov r1, #0x18
	bl FUN_02016998
	ldr r1, _0202D914 ; =0x021C59E0
	str r0, [r1, #0x0]
_0202D8EC:
	ldr r0, _0202D914 ; =0x021C59E0
	mov r3, #0x0
	ldr r1, [r0, #0x0]
	add r2, r3, #0x0
	str r5, [r1, #0x0]
	ldr r1, [r0, #0x0]
	str r4, [r1, #0x4]
	ldr r1, [r0, #0x0]
	str r6, [r1, #0x8]
_0202D8FE:
	ldr r1, [r0, #0x0]
	add r1, r1, r3
	add r3, r3, #0x1
	strb r2, [r1, #0xc]
	cmp r3, #0x8
	blt _0202D8FE
	ldr r0, _0202D914 ; =0x021C59E0
	ldr r0, [r0, #0x0]
	strb r2, [r0, #0x14]
	pop {r4-r6, pc}
	nop
_0202D914: .word 0x021C59E0

	thumb_func_start FUN_0202D918
FUN_0202D918: ; 0x0202D918
	push {r3, lr}
	ldr r0, _0202D930 ; =0x021C59E0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0202D92C
	bl FUN_02016A18
	ldr r0, _0202D930 ; =0x021C59E0
	mov r1, #0x0
	str r1, [r0, #0x0]
_0202D92C:
	pop {r3, pc}
	nop
_0202D930: .word 0x021C59E0

	thumb_func_start FUN_0202D934
FUN_0202D934: ; 0x0202D934
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r4, #0x16
	bge _0202D94C
	mov r0, #0xc
	mul r1, r0
	ldr r0, _0202D998 ; =0x020EEB38
	ldr r4, [r0, r1]
	b _0202D974
_0202D94C:
	ldr r0, _0202D99C ; =0x021C59E0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202D958
	bl ErrorHandling
_0202D958:
	ldr r0, _0202D99C ; =0x021C59E0
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x4]
	add r0, #0x16
	cmp r4, r0
	ble _0202D96A
	bl FUN_02031454
	pop {r3-r7, pc}
_0202D96A:
	ldr r1, [r1, #0x0]
	sub r4, #0x16
	mov r0, #0xc
	mul r0, r4
	ldr r4, [r1, r0]
_0202D974:
	cmp r4, #0x0
	beq _0202D996
	ldr r0, _0202D99C ; =0x021C59E0
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _0202D98C
	ldr r3, [r3, #0x8]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	blx r4
	pop {r3-r7, pc}
_0202D98C:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	mov r3, #0x0
	blx r4
_0202D996:
	pop {r3-r7, pc}
	.balign 4
_0202D998: .word 0x020EEB38
_0202D99C: .word 0x021C59E0

	thumb_func_start FUN_0202D9A0
FUN_0202D9A0: ; 0x0202D9A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	cmp r5, #0x16
	bge _0202D9B6
	mov r0, #0xc
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, _0202D9FC ; =0x020EEB3C
	ldr r0, [r0, r1]
	b _0202D9EE
_0202D9B6:
	ldr r0, _0202DA00 ; =0x021C59E0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0202D9C2
	bl ErrorHandling
_0202D9C2:
	ldr r0, _0202DA00 ; =0x021C59E0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _0202D9D2
	bl FUN_02031454
	mov r0, #0x0
	pop {r3-r5, pc}
_0202D9D2:
	ldr r0, [r1, #0x4]
	add r0, #0x16
	cmp r5, r0
	ble _0202D9E2
	bl FUN_02031454
	mov r0, #0x0
	pop {r3-r5, pc}
_0202D9E2:
	ldr r1, [r1, #0x0]
	sub r5, #0x16
	mov r0, #0xc
	mul r0, r5
	add r0, r1, r0
	ldr r0, [r0, #0x4]
_0202D9EE:
	cmp r0, #0x0
	beq _0202D9F6
	blx r0
	add r4, r0, #0x0
_0202D9F6:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	nop
_0202D9FC: .word 0x020EEB3C
_0202DA00: .word 0x021C59E0

	thumb_func_start FUN_0202DA04
FUN_0202DA04: ; 0x0202DA04
	cmp r0, #0x16
	bge _0202DA1C
	mov r1, #0xc
	mul r1, r0
	ldr r0, _0202DA38 ; =0x020EEB40
	ldr r0, [r0, r1]
	cmp r0, #0x0
	beq _0202DA18
	mov r0, #0x1
	bx lr
_0202DA18:
	mov r0, #0x0
	bx lr
_0202DA1C:
	ldr r1, _0202DA3C ; =0x021C59E0
	sub r0, #0x16
	ldr r1, [r1, #0x0]
	ldr r2, [r1, #0x0]
	mov r1, #0xc
	mul r1, r0
	add r0, r2, r1
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0202DA34
	mov r0, #0x1
	bx lr
_0202DA34:
	mov r0, #0x0
	bx lr
	.balign 4
_0202DA38: .word 0x020EEB40
_0202DA3C: .word 0x021C59E0

	thumb_func_start FUN_0202DA40
FUN_0202DA40: ; 0x0202DA40
	push {r3-r5, lr}
	add r3, r0, #0x0
	cmp r3, #0x16
	bge _0202DA58
	mov r4, #0xc
	mul r4, r3
	ldr r3, _0202DA70 ; =0x020EEB40
	add r0, r1, #0x0
	ldr r3, [r3, r4]
	mov r1, #0x0
	blx r3
	pop {r3-r5, pc}
_0202DA58:
	ldr r0, _0202DA74 ; =0x021C59E0
	sub r3, #0x16
	ldr r4, [r0, #0x0]
	add r0, r1, #0x0
	ldr r1, [r4, #0x8]
	ldr r5, [r4, #0x0]
	mov r4, #0xc
	mul r4, r3
	add r3, r5, r4
	ldr r3, [r3, #0x8]
	blx r3
	pop {r3-r5, pc}
	.balign 4
_0202DA70: .word 0x020EEB40
_0202DA74: .word 0x021C59E0

	thumb_func_start FUN_0202DA78
FUN_0202DA78: ; 0x0202DA78
	ldr r0, _0202DA7C ; =0x0000FFFF
	bx lr
	.balign 4
_0202DA7C: .word 0x0000FFFF

	thumb_func_start FUN_0202DA80
FUN_0202DA80: ; 0x0202DA80
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_0202DA84
FUN_0202DA84: ; 0x0202DA84
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0202DA88
FUN_0202DA88: ; 0x0202DA88
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_0202DA8C
FUN_0202DA8C: ; 0x0202DA8C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202DACA
	ldr r4, _0202DACC ; =0x021C59E0
	mov r1, #0x1
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	strb r1, [r0, #0xc]
	mov r5, #0x0
_0202DAA4:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0202DABA
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	ldrb r0, [r0, #0xc]
	cmp r0, #0x0
	beq _0202DACA
_0202DABA:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0202DAA4
	mov r1, #0x0
	mov r0, #0xe
	add r2, r1, #0x0
	bl FUN_02030BC4
_0202DACA:
	pop {r3-r5, pc}
	.balign 4
_0202DACC: .word 0x021C59E0

	thumb_func_start FUN_0202DAD0
FUN_0202DAD0: ; 0x0202DAD0
	ldr r0, _0202DAF0 ; =0x021C59E0
	mov r3, #0x0
	ldr r1, [r0, #0x0]
	str r3, [r1, #0x0]
	ldr r1, [r0, #0x0]
	str r3, [r1, #0x4]
	ldr r1, [r0, #0x0]
	str r3, [r1, #0x8]
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	strb r1, [r0, #0x14]
	ldr r3, _0202DAF4 ; =FUN_020311D0
	mov r0, #0xf
	add r1, r2, #0x0
	bx r3
	nop
_0202DAF0: .word 0x021C59E0
_0202DAF4: .word FUN_020311D0

	thumb_func_start FUN_0202DAF8
FUN_0202DAF8: ; 0x0202DAF8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _0202DB0E
	ldr r0, _0202DB10 ; =0x021C59E0
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	strb r1, [r0, #0xc]
_0202DB0E:
	pop {r4, pc}
	.balign 4
_0202DB10: .word 0x021C59E0
