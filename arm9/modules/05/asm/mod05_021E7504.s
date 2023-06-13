	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E7504
MOD05_021E7504: ; 0x021E7504
	add r1, r0, #0
	ldr r0, [r1, #0x10]
	cmp r0, #3
	bhi _021E7536
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E7518: ; jump table
	.short _021E7520 - _021E7518 - 2 ; case 0
	.short _021E752C - _021E7518 - 2 ; case 1
	.short _021E7526 - _021E7518 - 2 ; case 2
	.short _021E7532 - _021E7518 - 2 ; case 3
_021E7520:
	mov r0, #2
	str r0, [r1, #0x10]
	b _021E7536
_021E7526:
	mov r0, #1
	str r0, [r1, #0x10]
	b _021E7536
_021E752C:
	mov r0, #3
	str r0, [r1, #0x10]
	b _021E7536
_021E7532:
	mov r0, #0
	str r0, [r1, #0x10]
_021E7536:
	ldr r0, [r1]
	ldr r3, _021E7540 ; =FUN_02055304
	ldr r0, [r0, #0x38]
	ldr r1, [r1, #0x10]
	bx r3
	.balign 4, 0
_021E7540: .word FUN_02055304

	thumb_func_start MOD05_021E7544
MOD05_021E7544: ; 0x021E7544
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	add r7, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	add r6, r0, #0
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _021E7564
	cmp r0, #1
	beq _021E756E
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_021E7564:
	mov r0, #1
	str r0, [r5, #8]
	ldr r0, _021E760C ; =0x0000064F
	bl PlaySE
_021E756E:
	ldr r0, [r5, #0xc]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _021E7584
	add r0, r5, #0
	bl MOD05_021E7504
_021E7584:
	add r0, r6, #0
	add r1, sp, #0x18
	bl FUN_02058BA4
	ldr r4, [r5, #0xc]
	add r0, r4, #0
	bl _dflt
	str r0, [sp, #0x14]
	lsl r0, r4, #0xb
	str r1, [sp, #0x10]
	bl _dflt
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, _021E7610 ; =0x9999999A
	ldr r1, _021E7614 ; =0x40C19999
	bl _dadd
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	bl _dmul
	bl _dfix
	str r0, [sp, #0x1c]
	add r0, r6, #0
	add r1, sp, #0x18
	bl FUN_02058BB4
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #0x14
	bne _021E75EA
	mov r0, #6
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	add r3, r1, #0
	bl BeginNormalPaletteFade
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
_021E75EA:
	ble _021E7606
	bl IsPaletteFadeFinished
	cmp r0, #0
	beq _021E7606
	ldr r0, [r5, #4]
	mov r1, #1
	str r1, [r0]
	add r0, r5, #0
	bl FreeToHeap
	add r0, r7, #0
	bl FUN_0200CAB4
_021E7606:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021E760C: .word 0x0000064F
_021E7610: .word 0x9999999A
_021E7614: .word 0x40C19999

	thumb_func_start MOD05_021E7618
MOD05_021E7618: ; 0x021E7618
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #0x38]
	bl FUN_020553A0
	ldr r1, [r5, #8]
	add r4, r0, #0
	cmp r1, #0
	beq _021E763C
	cmp r1, #1
	beq _021E7694
	cmp r1, #2
	beq _021E771C
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_021E763C:
	bl FUN_02058914
	add r0, r4, #0
	add r1, sp, #0x14
	bl FUN_02058BA4
	ldr r1, [r5, #0xc]
	mov r0, #0x14
	sub r6, r0, r1
	add r0, r6, #0
	bl _dflt
	str r0, [sp, #0xc]
	lsl r0, r6, #0xb
	add r7, r1, #0
	bl _dflt
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, _021E7744 ; =0x9999999A
	ldr r1, _021E7748 ; =0x40C19999
	bl _dadd
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [sp, #0xc]
	add r1, r7, #0
	bl _dmul
	bl _dfix
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r1, sp, #0x14
	bl FUN_02058BB4
	add r0, r4, #0
	bl MOD05_021F1D8C
	ldr r0, _021E774C ; =0x0000064F
	bl PlaySE
	mov r0, #1
	str r0, [r5, #8]
_021E7694:
	ldr r0, [r5, #0xc]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	beq _021E76AA
	add r0, r5, #0
	bl MOD05_021E7504
_021E76AA:
	add r0, r4, #0
	add r1, sp, #0x14
	bl FUN_02058BA4
	ldr r1, [r5, #0xc]
	mov r0, #0x14
	sub r6, r0, r1
	add r0, r6, #0
	bl _dflt
	str r0, [sp, #0x10]
	lsl r0, r6, #0xb
	add r7, r1, #0
	bl _dflt
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, _021E7744 ; =0x9999999A
	ldr r1, _021E7748 ; =0x40C19999
	bl _dadd
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [sp, #0x10]
	add r1, r7, #0
	bl _dmul
	bl _dfix
	str r0, [sp, #0x18]
	add r0, r4, #0
	add r1, sp, #0x14
	bl FUN_02058BB4
	ldr r0, [r5, #0xc]
	add r0, r0, #1
	str r0, [r5, #0xc]
	cmp r0, #2
	bne _021E770E
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	add r1, r0, #0
	add r2, r0, #0
	mov r3, #0
	bl BeginNormalPaletteFade
_021E770E:
	ldr r0, [r5, #0xc]
	cmp r0, #0x14
	ble _021E7740
	mov r0, #2
	add sp, #0x20
	str r0, [r5, #8]
	pop {r3, r4, r5, r6, r7, pc}
_021E771C:
	bl IsPaletteFadeFinished
	cmp r0, #0
	beq _021E7740
	ldr r0, [r5]
	mov r1, #1
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	ldr r0, [r5, #4]
	mov r1, #1
	str r1, [r0]
	add r0, r5, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
_021E7740:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021E7744: .word 0x9999999A
_021E7748: .word 0x40C19999
_021E774C: .word 0x0000064F

	thumb_func_start MOD05_021E7750
MOD05_021E7750: ; 0x021E7750
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #4
	mov r1, #0x14
	add r7, r2, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	str r5, [r4]
	str r7, [r4, #4]
	ldr r0, [r5, #0x38]
	bl PlayerAvatar_GetFacingDirection
	str r0, [r4, #0x10]
	cmp r6, #0
	beq _021E7786
	ldr r0, _021E7794 ; =MOD05_021E7544
	add r1, r4, #0
	mov r2, #0x64
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
_021E7786:
	ldr r0, _021E7798 ; =MOD05_021E7618
	add r1, r4, #0
	mov r2, #0x64
	bl FUN_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E7794: .word MOD05_021E7544
_021E7798: .word MOD05_021E7618
