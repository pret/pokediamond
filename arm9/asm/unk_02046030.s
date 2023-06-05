	.include "asm/macros.inc"
	.include "global.inc"

	.extern gSystem

	.text

	thumb_func_start FUN_02046030
FUN_02046030: ; 0x02046030
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeapAtEnd
	add r2, r0, #0x0
	mov r0, #0x0
	strb r0, [r2, #0x0]
	strb r0, [r2, #0x1]
	strb r0, [r2, #0x2]
	strb r0, [r2, #0x3]
	strb r0, [r2, #0x4]
	strb r0, [r2, #0x5]
	strb r0, [r2, #0x6]
	strb r0, [r2, #0x7]
	strb r0, [r2, #0x8]
	strb r0, [r2, #0x9]
	strb r0, [r2, #0xa]
	strb r0, [r2, #0xb]
	ldr r0, [r4, #0x10]
	ldr r1, _02046064 ; =FUN_02046068
	bl FUN_0204640C
	pop {r4, pc}
	nop
_02046064: .word FUN_02046068 

	thumb_func_start FUN_02046068
FUN_02046068: ; 0x02046068
	push {r4-r6, lr}
	sub sp, #0x38
	add r6, r0, #0x0
	bl FUN_02046528
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl SaveArray_Flags_Get
	ldrb r1, [r4, #0x8]
	cmp r1, #0xb
	bls _0204608A
	b _020461F8
_0204608A:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02046096: ; jump table (using 16-bit offset)
	.short _020460AE - _02046096 - 2; case 0
	.short _020460D4 - _02046096 - 2; case 1
	.short _020460E2 - _02046096 - 2; case 2
	.short _0204610A - _02046096 - 2; case 3
	.short _02046118 - _02046096 - 2; case 4
	.short _02046150 - _02046096 - 2; case 5
	.short _02046160 - _02046096 - 2; case 6
	.short _0204618A - _02046096 - 2; case 7
	.short _02046198 - _02046096 - 2; case 8
	.short _020461C0 - _02046096 - 2; case 9
	.short _020461CE - _02046096 - 2; case 10
	.short _020461E4 - _02046096 - 2; case 11
_020460AE:
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	strh r0, [r4, #0x4]
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	strh r0, [r4, #0x6]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0206367C
	add r0, r6, #0x0
	bl FUN_0204AFC8
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020460D4:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020460E2:
	bl FUN_0205F1C4
	mov r0, #0xac
	str r0, [sp, #0x24]
	sub r0, #0xad
	str r0, [sp, #0x28]
	ldr r0, _02046200 ; =0x0000034F
	add r1, sp, #0x24
	str r0, [sp, #0x2c]
	ldr r0, _02046204 ; =0x00000231
	str r0, [sp, #0x30]
	mov r0, #0x1
	str r0, [sp, #0x34]
	add r0, r6, #0x0
	bl FUN_02049160
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_0204610A:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046118:
	ldr r0, [r5, #0x38]
	mov r1, #0x1
	bl FUN_02046214
	add r0, r5, #0x0
	bl FUN_02046224
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r3, _02046208 ; =0x0000FFFF
	add r0, r6, #0x0
	mov r1, #0x3
	mov r2, #0x11
	bl FUN_0204C1B4
	ldr r0, _0204620C ; =0x00000679
	bl PlaySE
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046150:
	ldr r0, _02046210 ; =gSystem
	ldr r2, [r0, #0x48]
	mov r0, #0x3
	tst r0, r2
	beq _020461F8
	add r0, r1, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046160:
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x6
	str r0, [sp, #0x4]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0xb
	str r0, [sp, #0xc]
	ldr r3, _02046208 ; =0x0000FFFF
	add r0, r6, #0x0
	mov r1, #0x3
	mov r2, #0x10
	bl FUN_0204C1B4
	ldr r0, _0204620C ; =0x00000679
	bl PlaySE
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_0204618A:
	add r0, r6, #0x0
	bl FUN_0204AF3C
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_02046198:
	bl FUN_0205F1D4
	ldrh r2, [r4, #0x6]
	ldrh r1, [r4, #0x4]
	mov r0, #0xa4
	str r0, [sp, #0x10]
	sub r0, #0xa5
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r1, [sp, #0x18]
	str r0, [sp, #0x20]
	str r2, [sp, #0x1c]
	add r0, r6, #0x0
	add r1, sp, #0x10
	bl FUN_02049160
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020461C0:
	add r0, r6, #0x0
	bl FUN_0204AF84
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020461CE:
	ldr r0, [r5, #0x38]
	mov r1, #0x0
	bl FUN_02046214
	add r0, r6, #0x0
	bl FUN_0204B00C
	ldrb r0, [r4, #0x8]
	add r0, r0, #0x1
	strb r0, [r4, #0x8]
	b _020461F8
_020461E4:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0206367C
	add sp, #0x38
	mov r0, #0x1
	pop {r4-r6, pc}
_020461F8:
	mov r0, #0x0
	add sp, #0x38
	pop {r4-r6, pc}
	nop
_02046200: .word 0x0000034F
_02046204: .word 0x00000231
_02046208: .word 0x0000FFFF
_0204620C: .word 0x00000679
_02046210: .word gSystem

	thumb_func_start FUN_02046214
FUN_02046214: ; 0x02046214
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020553A0
	add r1, r4, #0x0
	bl FUN_0205889C
	pop {r4, pc}

	thumb_func_start FUN_02046224
FUN_02046224: ; 0x02046224
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r0, #0x0
	ldr r0, _02046278 ; =0x000008C1
	ldr r1, [r4, #0x20]
	bl Camera_SetPerspectiveAngle
	ldr r0, _0204627C ; =0x000F81B8
	ldr r1, [r4, #0x20]
	bl Camera_SetDistance
	ldr r0, _02046280 ; =0x0350523D
	str r0, [sp, #0x8]
	ldr r0, _02046284 ; =0x0015EDB7
	str r0, [sp, #0xc]
	ldr r0, _02046288 ; =0x023DA40E
	str r0, [sp, #0x10]
	ldr r1, [r4, #0x20]
	add r0, sp, #0x8
	bl Camera_SetLookAtCamTarget
	ldr r1, _0204628C ; =0x00000823
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	mov r1, #0x52
	lsl r1, r1, #0x4
	strh r1, [r0, #0x2]
	mov r1, #0x0
	strh r1, [r0, #0x4]
	ldr r1, [r4, #0x20]
	add r0, sp, #0x0
	bl Camera_SetAngle
	mov r0, #0x3
	ldr r1, _02046290 ; =0x0061C000
	ldr r2, [r4, #0x20]
	lsl r0, r0, #0xe
	bl Camera_SetPerspectiveClippingPlane
	add sp, #0x14
	pop {r3-r4, pc}
	nop
_02046278: .word 0x000008C1
_0204627C: .word 0x000F81B8
_02046280: .word 0x0350523D
_02046284: .word 0x0015EDB7
_02046288: .word 0x023DA40E
_0204628C: .word 0x00000823
_02046290: .word 0x0061C000
