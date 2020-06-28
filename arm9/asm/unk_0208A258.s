    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0208A258
FUN_0208A258: ; 0x0208A258
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, _0208A290 ; =0x0000022F
	ldrb r0, [r4, r0]
	cmp r0, #0x10
	beq _0208A278
	cmp r0, #0x11
	beq _0208A286
	b _0208A28C
_0208A278:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0208A294
	ldr r1, _0208A290 ; =0x0000022F
	strb r0, [r4, r1]
	b _0208A28C
_0208A286:
	add r0, r5, #0x0
	bl FUN_0208A2C4
_0208A28C:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_0208A290: .word 0x0000022F

	thumb_func_start FUN_0208A294
FUN_0208A294: ; 0x0208A294
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0204647C
	cmp r0, #0x0
	beq _0208A2A6
	mov r0, #0x10
	pop {r3-r5, pc}
_0208A2A6:
	ldr r0, [r4, #0x4]
	bl FUN_0206E394
	mov r1, #0x9
	lsl r1, r1, #0x6
	strb r0, [r4, r1]
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	add r0, r5, #0x0
	bl FUN_0204649C
	mov r0, #0x11
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0208A2C4
FUN_0208A2C4: ; 0x0208A2C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020464A4
	cmp r0, #0x0
	beq _0208A2F6
	mov r0, #0x1
	bl MOD05_021D7CA4
	ldr r1, _0208A2F8 ; =0x0223D4AD
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020463EC
	ldr r0, _0208A2FC ; =0x0000022F
	mov r1, #0x12
	strb r1, [r4, r0]
_0208A2F6:
	pop {r4-r6, pc}
	.balign 4
_0208A2F8: .word MOD06_0223D4AC
_0208A2FC: .word 0x0000022F
