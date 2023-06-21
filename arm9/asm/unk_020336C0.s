	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_020336C0
sub_020336C0: ; 0x020336C0
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_020336C8
sub_020336C8: ; 0x020336C8
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r6, r1, #0x0
	ldr r1, [r4, #0x0]
	add r5, r0, #0x0
	cmp r1, #0x6
	bhi _02033774
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020336E2: ; jump table (using 16-bit offset)
	.short _020336F0 - _020336E2 - 2; case 0
	.short _020336FC - _020336E2 - 2; case 1
	.short _02033714 - _020336E2 - 2; case 2
	.short _0203373A - _020336E2 - 2; case 3
	.short _0203374A - _020336E2 - 2; case 4
	.short _0203376A - _020336E2 - 2; case 5
	.short _02033770 - _020336E2 - 2; case 6
_020336F0:
	mov r0, #0x6f
	bl sub_02031588
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02033774
_020336FC:
	mov r0, #0x6f
	bl sub_020315D8
	cmp r0, #0x0
	beq _02033774
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl sub_02022840
	mov r0, #0x2
	str r0, [r4, #0x0]
	b _02033774
_02033714:
	bl sub_02022854
	add r5, r0, #0x0
	cmp r5, #0x2
	bne _02033722
	bl GF_AssertFail
_02033722:
	cmp r5, #0x3
	bne _0203372A
	bl GF_AssertFail
_0203372A:
	cmp r5, #0x1
	bne _02033774
	mov r0, #0x3
	str r0, [r4, #0x0]
	mov r0, #0x70
	bl sub_02031588
	b _02033774
_0203373A:
	mov r0, #0x70
	bl sub_020315D8
	cmp r0, #0x0
	beq _02033774
	mov r0, #0x4
	str r0, [r4, #0x0]
	b _02033774
_0203374A:
	bl sub_02022854
	add r5, r0, #0x0
	cmp r5, #0x3
	bne _02033758
	bl GF_AssertFail
_02033758:
	cmp r5, #0x1
	bne _02033760
	bl GF_AssertFail
_02033760:
	cmp r5, #0x2
	bne _02033774
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _02033774
_0203376A:
	mov r0, #0x6
	str r0, [r4, #0x0]
	b _02033774
_02033770:
	mov r0, #0x1
	pop {r4-r6, pc}
_02033774:
	mov r0, #0x0
	pop {r4-r6, pc}
