	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02002248
FUN_02002248: ; 0x02002248
	ldrh r3, [r1, #0x0]
	ldr r2, _02002264 ; =0x0000FFFF
	cmp r3, r2
	beq _0200225C
_02002250:
	add r1, r1, #0x2
	strh r3, [r0, #0x0]
	ldrh r3, [r1, #0x0]
	add r0, r0, #0x2
	cmp r3, r2
	bne _02002250
_0200225C:
	ldr r1, _02002264 ; =0x0000FFFF
	strh r1, [r0, #0x0]
	bx lr
	nop
_02002264: .word 0x0000FFFF

	thumb_func_start FUN_02002268
FUN_02002268: ; 0x02002268
	push {r4-r5}
	mov r4, #0x0
	cmp r2, #0x0
	bls _02002280
	add r5, r0, #0x0
_02002272:
	ldrh r3, [r1, #0x0]
	add r4, r4, #0x1
	add r1, r1, #0x2
	strh r3, [r5, #0x0]
	add r5, r5, #0x2
	cmp r4, r2
	blo _02002272
_02002280:
	lsl r1, r2, #0x1
	add r0, r0, r1
	pop {r4-r5}
	bx lr

	thumb_func_start FUN_02002288
FUN_02002288: ; 0x02002288
	ldrh r2, [r0, #0x0]
	ldr r1, _020022A0 ; =0x0000FFFF
	mov r3, #0x0
	cmp r2, r1
	beq _0200229C
_02002292:
	add r0, r0, #0x2
	ldrh r2, [r0, #0x0]
	add r3, r3, #0x1
	cmp r2, r1
	bne _02002292
_0200229C:
	add r0, r3, #0x0
	bx lr
	.balign 4
_020022A0: .word 0x0000FFFF

	thumb_func_start FUN_020022A4
FUN_020022A4: ; 0x020022A4
	push {r3-r4}
	ldrh r4, [r0, #0x0]
	ldrh r2, [r1, #0x0]
	cmp r4, r2
	bne _020022C6
	ldr r2, _020022CC ; =0x0000FFFF
_020022B0:
	cmp r4, r2
	bne _020022BA
	mov r0, #0x0
	pop {r3-r4}
	bx lr
_020022BA:
	add r0, r0, #0x2
	add r1, r1, #0x2
	ldrh r4, [r0, #0x0]
	ldrh r3, [r1, #0x0]
	cmp r4, r3
	beq _020022B0
_020022C6:
	mov r0, #0x1
	pop {r3-r4}
	bx lr
	.balign 4
_020022CC: .word 0x0000FFFF

	thumb_func_start FUN_020022D0
FUN_020022D0: ; 0x020022D0
	push {r3-r6}
	ldrh r6, [r1, #0x0]
	ldrh r5, [r0, #0x0]
	cmp r5, r6
	bne _02002304
	ldr r3, _0200230C ; =0x0000FFFF
	add r4, r3, #0x0
_020022DE:
	cmp r2, #0x0
	bne _020022E8
	mov r0, #0x0
	pop {r3-r6}
	bx lr
_020022E8:
	cmp r5, r4
	bne _020022F6
	cmp r6, r3
	bne _020022F6
	mov r0, #0x0
	pop {r3-r6}
	bx lr
_020022F6:
	add r0, r0, #0x2
	add r1, r1, #0x2
	ldrh r6, [r1, #0x0]
	ldrh r5, [r0, #0x0]
	sub r2, r2, #0x1
	cmp r5, r6
	beq _020022DE
_02002304:
	mov r0, #0x1
	pop {r3-r6}
	bx lr
	nop
_0200230C: .word 0x0000FFFF

	thumb_func_start FUN_02002310
FUN_02002310: ; 0x02002310
	push {r3-r4}
	mov r3, #0x0
	cmp r2, #0x0
	bls _02002324
	add r4, r0, #0x0
_0200231A:
	add r3, r3, #0x1
	strh r1, [r4, #0x0]
	add r4, r4, #0x2
	cmp r3, r2
	blo _0200231A
_02002324:
	lsl r1, r3, #0x1
	add r0, r0, r1
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0200232C
FUN_0200232C: ; 0x0200232C
	ldr r3, _02002334 ; =FUN_02002310
	add r2, r1, #0x0
	ldr r1, _02002338 ; =0x0000FFFF
	bx r3
	.balign 4
_02002334: .word FUN_02002310 
_02002338: .word 0x0000FFFF

	thumb_func_start FUN_0200233C
FUN_0200233C: ; 0x0200233C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	ldr r0, _020023B4 ; =0x020ECB24
	lsl r1, r3, #0x2
	ldr r4, [r0, r1]
	add r6, r2, #0x0
	cmp r4, #0x0
	beq _020023AC
_0200234E:
	add r0, r7, #0x0
	add r1, r4, #0x0
	blx FUN_020EBE8C
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, r4, #0x0
	mul r0, r1
	sub r7, r7, r0
	cmp r6, #0x2
	bne _02002378
	cmp r1, #0xa
	blo _0200236C
	mov r0, #0xe2
	b _02002372
_0200236C:
	ldr r0, _020023B8 ; =0x020ECB08
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
_02002372:
	strh r0, [r5, #0x0]
	add r5, r5, #0x2
	b _020023A0
_02002378:
	cmp r1, #0x0
	bne _02002380
	cmp r4, #0x1
	bne _02002396
_02002380:
	mov r6, #0x2
	cmp r1, #0xa
	blo _0200238A
	mov r0, #0xe2
	b _02002390
_0200238A:
	ldr r0, _020023B8 ; =0x020ECB08
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
_02002390:
	strh r0, [r5, #0x0]
	add r5, r5, #0x2
	b _020023A0
_02002396:
	cmp r6, #0x1
	bne _020023A0
	mov r0, #0x1
	strh r0, [r5, #0x0]
	add r5, r5, #0x2
_020023A0:
	add r0, r4, #0x0
	mov r1, #0xa
	blx FUN_020EBE8C
	add r4, r0, #0x0
	bne _0200234E
_020023AC:
	ldr r0, _020023BC ; =0x0000FFFF
	strh r0, [r5, #0x0]
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_020023B4: .word 0x020ECB24
_020023B8: .word 0x020ECB08
_020023BC: .word 0x0000FFFF
