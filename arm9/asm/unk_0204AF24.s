    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0204AF24
FUN_0204AF24: ; 0x0204AF24
	push {r3, lr}
	bl FUN_02046528
	bl FUN_0203739C
	cmp r0, #0x0
	bne _0204AF36
	mov r0, #0x1
	pop {r3, pc}
_0204AF36:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204AF3C
FUN_0204AF3C: ; 0x0204AF3C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	bne _0204AF54
	bl ErrorHandling
	pop {r3-r5, pc}
_0204AF54:
	add r0, r4, #0x0
	bl FUN_02037394
	ldr r1, _0204AF68 ; =FUN_0204AF24
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	nop
_0204AF68: .word FUN_0204AF24

	thumb_func_start FUN_0204AF6C
FUN_0204AF6C: ; 0x0204AF6C
	push {r3, lr}
	bl FUN_02046528
	bl FUN_020464A4
	cmp r0, #0x0
	beq _0204AF7E
	mov r0, #0x1
	pop {r3, pc}
_0204AF7E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204AF84
FUN_0204AF84: ; 0x0204AF84
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046528
	add r4, r0, #0x0
	bl FUN_0203739C
	cmp r0, #0x0
	beq _0204AF9C
	bl ErrorHandling
	pop {r3-r5, pc}
_0204AF9C:
	add r0, r4, #0x0
	bl FUN_0204649C
	ldr r1, _0204AFB0 ; =FUN_0204AF6C
	add r0, r5, #0x0
	mov r2, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	nop
_0204AFB0: .word FUN_0204AF6C

	thumb_func_start FUN_0204AFB4
FUN_0204AFB4: ; 0x0204AFB4
	push {r3, lr}
	bl FUN_0200E308
	cmp r0, #0x0
	beq _0204AFC2
	mov r0, #0x1
	pop {r3, pc}
_0204AFC2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204AFC8
FUN_0204AFC8: ; 0x0204AFC8
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl FUN_02046528
	bl FUN_0203739C
	cmp r0, #0x0
	bne _0204AFE2
	bl ErrorHandling
	add sp, #0xc
	pop {r3-r4, pc}
_0204AFE2:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	ldr r1, _0204B008 ; =FUN_0204AFB4
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_0204640C
	add sp, #0xc
	pop {r3-r4, pc}
	.balign 4
_0204B008: .word FUN_0204AFB4

	thumb_func_start FUN_0204B00C
FUN_0204B00C: ; 0x0204B00C
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	bl FUN_02046528
	bl FUN_0203739C
	cmp r0, #0x0
	bne _0204B026
	bl ErrorHandling
	add sp, #0xc
	pop {r3-r4, pc}
_0204B026:
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x0
	add r2, r1, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	ldr r1, _0204B04C ; =FUN_0204AFB4
	add r0, r4, #0x0
	mov r2, #0x0
	bl FUN_0204640C
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_0204B04C: .word FUN_0204AFB4

	thumb_func_start FUN_0204B050
FUN_0204B050: ; 0x0204B050
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0204B06A
	cmp r0, #0x1
	beq _0204B078
	cmp r0, #0x2
	beq _0204B086
	b _0204B08A
_0204B06A:
	add r0, r5, #0x0
	bl FUN_0204AFC8
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204B08A
_0204B078:
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204B08A
_0204B086:
	mov r0, #0x1
	pop {r3-r5, pc}
_0204B08A:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204B090
FUN_0204B090: ; 0x0204B090
	ldr r3, _0204B098 ; =FUN_0204640C
	ldr r1, _0204B09C ; =FUN_0204B050
	mov r2, #0x0
	bx r3
	.balign 4
_0204B098: .word FUN_0204640C
_0204B09C: .word FUN_0204B050

	thumb_func_start FUN_0204B0A0
FUN_0204B0A0: ; 0x0204B0A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02046530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02046528
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _0204B0C0
	cmp r1, #0x1
	beq _0204B0CE
	cmp r1, #0x2
	beq _0204B0E0
	b _0204B0E4
_0204B0C0:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204B0E4
_0204B0CE:
	bl MOD05_021E331C
	add r0, r5, #0x0
	bl FUN_0204B00C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _0204B0E4
_0204B0E0:
	mov r0, #0x1
	pop {r3-r5, pc}
_0204B0E4:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0204B0E8
FUN_0204B0E8: ; 0x0204B0E8
	ldr r3, _0204B0F0 ; =FUN_0204640C
	ldr r1, _0204B0F4 ; =FUN_0204B0A0
	mov r2, #0x0
	bx r3
	.balign 4
_0204B0F0: .word FUN_0204640C
_0204B0F4: .word FUN_0204B0A0
