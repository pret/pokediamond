	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global UNK_02106154
UNK_02106154: ; 0x02106154
	.word -1

	.section .bss

	.global UNK_021C5C58
UNK_021C5C58: ; 0x021C5C58
	.space 0x3000

	.text

	thumb_func_start sub_020893E0
sub_020893E0: ; 0x020893E0
	mov r1, #0x0
	ldr r0, _020893EC ; =UNK_02106154
	mvn r1, r1
	str r1, [r0, #0x0]
	bx lr
	nop
_020893EC: .word UNK_02106154

	thumb_func_start sub_020893F0
sub_020893F0: ; 0x020893F0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x3
	lsl r0, r0, #0xc
	cmp r2, r0
	bhs _0208940A
	add r0, r1, #0x0
	ldr r1, _02089410 ; =UNK_021C5C58
	bl MIi_CpuCopy32
	ldr r0, _02089414 ; =UNK_02106154
	str r4, [r0, #0x0]
	pop {r4, pc}
_0208940A:
	bl GF_AssertFail
	pop {r4, pc}
	.balign 4
_02089410: .word UNK_021C5C58
_02089414: .word UNK_02106154

	thumb_func_start sub_02089418
sub_02089418: ; 0x02089418
	push {r3, lr}
	mov r3, #0x3
	lsl r3, r3, #0xc
	cmp r2, r3
	bhs _02089434
	ldr r3, _0208943C ; =UNK_02106154
	ldr r3, [r3, #0x0]
	cmp r0, r3
	bne _02089438
	ldr r0, _02089440 ; =UNK_021C5C58
	bl MIi_CpuCopy32
	mov r0, #0x1
	pop {r3, pc}
_02089434:
	bl GF_AssertFail
_02089438:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_0208943C: .word UNK_02106154
_02089440: .word UNK_021C5C58

	thumb_func_start sub_02089444
sub_02089444: ; 0x02089444
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x3
	lsl r0, r0, #0xc
	cmp r2, r0
	bhs _0208945E
	add r0, r1, #0x0
	ldr r1, _02089464 ; =UNK_021C5C58
	bl MIi_CpuCopyFast
	ldr r0, _02089468 ; =UNK_02106154
	str r4, [r0, #0x0]
	pop {r4, pc}
_0208945E:
	bl GF_AssertFail
	pop {r4, pc}
	.balign 4
_02089464: .word UNK_021C5C58
_02089468: .word UNK_02106154

	thumb_func_start sub_0208946C
sub_0208946C: ; 0x0208946C
	push {r3, lr}
	mov r3, #0x3
	lsl r3, r3, #0xc
	cmp r2, r3
	bhs _02089488
	ldr r3, _02089490 ; =UNK_02106154
	ldr r3, [r3, #0x0]
	cmp r0, r3
	bne _0208948C
	ldr r0, _02089494 ; =UNK_021C5C58
	bl MIi_CpuCopyFast
	mov r0, #0x1
	pop {r3, pc}
_02089488:
	bl GF_AssertFail
_0208948C:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_02089490: .word UNK_02106154
_02089494: .word UNK_021C5C58
