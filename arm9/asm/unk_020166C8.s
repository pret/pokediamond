    .include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C4D28
UNK_021C4D28: ; 0x021C4D28
	.space 0x1c

	.text

	thumb_func_start FUN_020166C8
FUN_020166C8: ; 0x020166C8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	str r0, [sp, #0x4]
	add r0, #0x18
	add r6, r2, #0x0
	str r0, [sp, #0x4]
	cmp r6, r0
	bhs _020166E0
	add r6, r0, #0x0
_020166E0:
	cmp r3, #0x0
	beq _020166FE
	mov r0, #0x3
	tst r0, r3
	beq _020166F4
	mov r0, #0x3
_020166EC:
	add r3, r3, #0x1
	add r1, r3, #0x0
	tst r1, r0
	bne _020166EC
_020166F4:
	mov r0, #0x0
	add r1, r3, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
_020166FE:
	ldr r1, [sp, #0x4]
	lsl r7, r6, #0x1
	lsl r2, r1, #0x1
	add r1, r1, r2
	add r1, r1, #0x1
	lsl r1, r1, #0x2
	add r1, r7, r1
	mov r0, #0x0
	add r1, r6, r1
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	ldr r1, _020167F0 ; =UNK_021C4D28
	str r0, [r1, #0x0]
	ldr r1, [sp, #0x4]
	add r1, r1, #0x1
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r0, _020167F0 ; =UNK_021C4D28
	str r1, [r0, #0x4]
	ldr r0, [sp, #0x4]
	lsl r0, r0, #0x2
	add r2, r1, r0
	ldr r1, _020167F0 ; =UNK_021C4D28
	str r2, [r1, #0x8]
	add r1, r2, r0
	ldr r0, _020167F0 ; =UNK_021C4D28
	str r1, [r0, #0xc]
	add r1, r1, r7
	str r1, [r0, #0x10]
	strh r6, [r0, #0x14]
	strh r4, [r0, #0x16]
	ldr r0, [sp, #0x4]
	mov r7, #0x0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, _020167F0 ; =UNK_021C4D28
	cmp r4, #0x0
	strh r1, [r0, #0x1a]
	strh r1, [r0, #0x18]
	bls _020167A0
	str r7, [sp, #0x0]
_02016752:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _0201675C
	cmp r0, #0x2
	beq _02016768
_0201675C:
	ldr r1, [r5, #0x0]
	mov r0, #0x0
	mov r2, #0x4
	bl OS_AllocFromArenaLo
	b _02016772
_02016768:
	ldr r1, [r5, #0x0]
	mov r0, #0x2
	mov r2, #0x4
	bl OS_AllocFromArenaHi
_02016772:
	cmp r0, #0x0
	beq _0201678E
	ldr r1, [r5, #0x0]
	mov r2, #0x0
	bl tempName_NNS_FndCreateExpHeapEx
	ldr r1, _020167F0 ; =UNK_021C4D28
	ldr r2, [r1, #0x0]
	ldr r1, [sp, #0x0]
	str r0, [r2, r1]
	ldr r0, _020167F0 ; =UNK_021C4D28
	ldr r0, [r0, #0x10]
	strb r7, [r0, r7]
	b _02016792
_0201678E:
	bl ErrorHandling
_02016792:
	ldr r0, [sp, #0x0]
	add r7, r7, #0x1
	add r0, r0, #0x4
	add r5, #0x8
	str r0, [sp, #0x0]
	cmp r7, r4
	blo _02016752
_020167A0:
	ldr r0, [sp, #0x4]
	add r1, r0, #0x1
	cmp r4, r1
	bhs _020167C0
	ldr r3, _020167F0 ; =UNK_021C4D28
	lsl r2, r4, #0x2
	mov r0, #0x0
_020167AE:
	ldr r5, [r3, #0x0]
	str r0, [r5, r2]
	ldrh r7, [r3, #0x1a]
	ldr r5, [r3, #0x10]
	add r2, r2, #0x4
	strb r7, [r5, r4]
	add r4, r4, #0x1
	cmp r4, r1
	blo _020167AE
_020167C0:
	cmp r4, r6
	bhs _020167D2
	ldr r0, _020167F0 ; =UNK_021C4D28
_020167C6:
	ldrh r2, [r0, #0x1a]
	ldr r1, [r0, #0x10]
	strb r2, [r1, r4]
	add r4, r4, #0x1
	cmp r4, r6
	blo _020167C6
_020167D2:
	mov r4, #0x0
	cmp r6, #0x0
	bls _020167EA
	ldr r0, _020167F0 ; =UNK_021C4D28
	add r3, r4, #0x0
	add r2, r4, #0x0
_020167DE:
	ldr r1, [r0, #0xc]
	add r4, r4, #0x1
	strh r2, [r1, r3]
	add r3, r3, #0x2
	cmp r4, r6
	blo _020167DE
_020167EA:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_020167F0: .word UNK_021C4D28

	thumb_func_start FUN_020167F4
FUN_020167F4: ; 0x020167F4
	ldr r1, _02016818 ; =UNK_021C4D28
	ldrh r0, [r1, #0x16]
	ldrh r3, [r1, #0x18]
	cmp r0, r3
	bge _02016812
	ldr r2, [r1, #0x0]
	lsl r1, r0, #0x2
	add r2, r2, r1
_02016804:
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _02016816
	add r0, r0, #0x1
	add r2, r2, #0x4
	cmp r0, r3
	blt _02016804
_02016812:
	mov r0, #0x0
	mvn r0, r0
_02016816:
	bx lr
	.balign 4
_02016818: .word UNK_021C4D28

	thumb_func_start FUN_0201681C
FUN_0201681C: ; 0x0201681C
	push {r3, lr}
	mov r3, #0x4
	bl FUN_02016834
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02016828
FUN_02016828: ; 0x02016828
	push {r3, lr}
	mov r3, #0x3
	mvn r3, r3
	bl FUN_02016834
	pop {r3, pc}

	thumb_func_start FUN_02016834
FUN_02016834: ; 0x02016834
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r5, r1, #0x0
	str r2, [sp, #0x0]
	add r7, r3, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _0201684C
	bl ErrorHandling
_0201684C:
	ldr r1, _020168CC ; =UNK_021C4D28
	ldr r0, [r1, #0x10]
	ldrh r3, [r1, #0x1a]
	ldrb r2, [r0, r5]
	cmp r3, r2
	bne _020168C2
	ldrb r0, [r0, r4]
	ldr r1, [r1, #0x0]
	lsl r0, r0, #0x2
	ldr r6, [r1, r0]
	cmp r6, #0x0
	beq _020168BC
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	add r2, r7, #0x0
	bl tempName_NNS_FndAllocFromExpHeapEx
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020168B6
	bl FUN_020167F4
	add r7, r0, #0x0
	bmi _020168B0
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x0]
	mov r2, #0x0
	lsl r4, r7, #0x2
	bl tempName_NNS_FndCreateExpHeapEx
	ldr r1, _020168CC ; =UNK_021C4D28
	ldr r2, [r1, #0x0]
	str r0, [r2, r4]
	ldr r0, [r1, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _020168AA
	ldr r0, [r1, #0x4]
	str r6, [r0, r4]
	ldr r0, [sp, #0x4]
	ldr r2, [r1, #0x8]
	add sp, #0x8
	str r0, [r2, r4]
	ldr r0, [r1, #0x10]
	strb r7, [r0, r5]
	mov r0, #0x1
	pop {r3-r7, pc}
_020168AA:
	bl ErrorHandling
	b _020168C6
_020168B0:
	bl ErrorHandling
	b _020168C6
_020168B6:
	bl ErrorHandling
	b _020168C6
_020168BC:
	bl ErrorHandling
	b _020168C6
_020168C2:
	bl ErrorHandling
_020168C6:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020168CC: .word UNK_021C4D28

	thumb_func_start FUN_020168D0
FUN_020168D0: ; 0x020168D0
	push {r4, lr}
	add r4, r0, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _020168E0
	bl ErrorHandling
_020168E0:
	ldr r0, _02016940 ; =UNK_021C4D28
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x10]
	ldrb r0, [r0, r4]
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0201693E
	bl thunk_FUN_020adc8c
	ldr r1, _02016940 ; =UNK_021C4D28
	ldr r0, [r1, #0x10]
	ldrb r0, [r0, r4]
	lsl r2, r0, #0x2
	ldr r0, [r1, #0x4]
	ldr r1, [r1, #0x8]
	ldr r0, [r0, r2]
	ldr r1, [r1, r2]
	cmp r0, #0x0
	beq _02016912
	cmp r1, #0x0
	beq _02016912
	bl FUN_020ADDF0
	b _02016916
_02016912:
	bl ErrorHandling
_02016916:
	ldr r1, _02016940 ; =UNK_021C4D28
	mov r0, #0x0
	ldr r2, [r1, #0x10]
	ldr r3, [r1, #0x0]
	ldrb r2, [r2, r4]
	lsl r2, r2, #0x2
	str r0, [r3, r2]
	ldr r2, [r1, #0x10]
	ldr r3, [r1, #0x4]
	ldrb r2, [r2, r4]
	lsl r2, r2, #0x2
	str r0, [r3, r2]
	ldr r2, [r1, #0x10]
	ldr r3, [r1, #0x8]
	ldrb r2, [r2, r4]
	lsl r2, r2, #0x2
	str r0, [r3, r2]
	ldrh r2, [r1, #0x1a]
	ldr r0, [r1, #0x10]
	strb r2, [r0, r4]
_0201693E:
	pop {r4, pc}
	.balign 4
_02016940: .word UNK_021C4D28

	thumb_func_start FUN_02016944
FUN_02016944: ; 0x02016944
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r5, #0x0
	bne _02016956
	bl ErrorHandling
_02016956:
	bl OS_DisableInterrupts
	add r4, #0x10
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl tempName_NNS_FndAllocFromExpHeapEx
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	beq _02016984
	ldr r1, [r4, #0xc]
	mov r0, #0xff
	bic r1, r0
	lsl r0, r6, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	str r0, [r4, #0xc]
	add r4, #0x10
_02016984:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02016988
FUN_02016988: ; 0x02016988
	push {r3, lr}
	bl FUN_02031810
	cmp r0, #0x0
	beq _02016996
	bl FUN_0208A9B8
_02016996:
	pop {r3, pc}

	thumb_func_start AllocFromHeap
AllocFromHeap: ; 0x02016998
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020169D4 ; =UNK_021C4D28
	mov r4, #0x0
	ldrh r2, [r0, #0x14]
	cmp r5, r2
	bhs _020169BA
	ldr r2, [r0, #0x0]
	ldr r0, [r0, #0x10]
	add r3, r5, #0x0
	ldrb r0, [r0, r5]
	lsl r0, r0, #0x2
	ldr r0, [r2, r0]
	mov r2, #0x4
	bl FUN_02016944
	add r4, r0, #0x0
_020169BA:
	cmp r4, #0x0
	beq _020169CC
	ldr r0, _020169D4 ; =UNK_021C4D28
	lsl r1, r5, #0x1
	ldr r2, [r0, #0xc]
	ldrh r0, [r2, r1]
	add r0, r0, #0x1
	strh r0, [r2, r1]
	b _020169D0
_020169CC:
	bl FUN_02016988
_020169D0:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_020169D4: .word UNK_021C4D28

	thumb_func_start AllocFromHeapAtEnd
AllocFromHeapAtEnd: ; 0x020169D8
	push {r3-r5, lr}
	ldr r2, _02016A14 ; =UNK_021C4D28
	add r5, r0, #0x0
	ldrh r0, [r2, #0x14]
	mov r4, #0x0
	cmp r5, r0
	bhs _020169FA
	ldr r0, [r2, #0x0]
	ldr r2, [r2, #0x10]
	add r3, r5, #0x0
	ldrb r2, [r2, r5]
	lsl r2, r2, #0x2
	ldr r0, [r0, r2]
	sub r2, r4, #0x4
	bl FUN_02016944
	add r4, r0, #0x0
_020169FA:
	cmp r4, #0x0
	beq _02016A0C
	ldr r0, _02016A14 ; =UNK_021C4D28
	lsl r1, r5, #0x1
	ldr r2, [r0, #0xc]
	ldrh r0, [r2, r1]
	add r0, r0, #0x1
	strh r0, [r2, r1]
	b _02016A10
_02016A0C:
	bl FUN_02016988
_02016A10:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02016A14: .word UNK_021C4D28

	thumb_func_start FreeToHeap
FreeToHeap: ; 0x02016A18
	push {r3-r7, lr}
	add r6, r0, #0x0
	sub r0, r6, #0x4
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	ldr r0, _02016A88 ; =UNK_021C4D28
	ldrh r1, [r0, #0x14]
	cmp r4, r1
	bhs _02016A80
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x10]
	ldrb r0, [r0, r4]
	lsl r0, r0, #0x2
	ldr r7, [r1, r0]
	cmp r7, #0x0
	bne _02016A3E
	bl ErrorHandling
_02016A3E:
	ldr r0, _02016A88 ; =UNK_021C4D28
	lsl r5, r4, #0x1
	ldr r0, [r0, #0xc]
	ldrh r0, [r0, r5]
	cmp r0, #0x0
	bne _02016A50
	add r0, r4, #0x0
	bl FUN_02016B90
_02016A50:
	ldr r0, _02016A88 ; =UNK_021C4D28
	ldr r0, [r0, #0xc]
	ldrh r0, [r0, r5]
	cmp r0, #0x0
	bne _02016A5E
	bl ErrorHandling
_02016A5E:
	ldr r0, _02016A88 ; =UNK_021C4D28
	ldr r1, [r0, #0xc]
	ldrh r0, [r1, r5]
	sub r0, r0, #0x1
	strh r0, [r1, r5]
	bl OS_DisableInterrupts
	sub r6, #0x10
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_020ADDF0
	add r0, r4, #0x0
	bl OS_RestoreInterrupts
	pop {r3-r7, pc}
_02016A80:
	bl ErrorHandling
	pop {r3-r7, pc}
	nop
_02016A88: .word UNK_021C4D28

	thumb_func_start FUN_02016A8C
FUN_02016A8C: ; 0x02016A8C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _02016A9E
	bl ErrorHandling
_02016A9E:
	ldr r0, _02016AF4 ; =UNK_021C4D28
	ldrh r1, [r0, #0x14]
	cmp r5, r1
	bhs _02016AEE
	ldr r1, [r0, #0x0]
	ldr r0, [r0, #0x10]
	ldrb r0, [r0, r5]
	lsl r0, r0, #0x2
	ldr r6, [r1, r0]
	cmp r6, #0x0
	bne _02016AB8
	bl ErrorHandling
_02016AB8:
	sub r0, r4, #0x4
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, r5
	beq _02016AC8
	bl ErrorHandling
_02016AC8:
	sub r4, #0x10
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020ADDF0
	ldr r0, _02016AF4 ; =UNK_021C4D28
	lsl r4, r5, #0x1
	ldr r0, [r0, #0xc]
	ldrh r0, [r0, r4]
	cmp r0, #0x0
	bne _02016AE2
	bl ErrorHandling
_02016AE2:
	ldr r0, _02016AF4 ; =UNK_021C4D28
	ldr r1, [r0, #0xc]
	ldrh r0, [r1, r4]
	sub r0, r0, #0x1
	strh r0, [r1, r4]
	pop {r4-r6, pc}
_02016AEE:
	bl ErrorHandling
	pop {r4-r6, pc}
	.balign 4
_02016AF4: .word UNK_021C4D28

	thumb_func_start FUN_02016AF8
FUN_02016AF8: ; 0x02016AF8
	push {r3, lr}
	ldr r1, _02016B1C ; =UNK_021C4D28
	ldrh r2, [r1, #0x14]
	cmp r0, r2
	bhs _02016B12
	ldr r2, [r1, #0x0]
	ldr r1, [r1, #0x10]
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x2
	ldr r0, [r2, r0]
	bl FUN_020ADDC8
	pop {r3, pc}
_02016B12:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3, pc}
	nop
_02016B1C: .word UNK_021C4D28

	thumb_func_start FUN_02016B20
FUN_02016B20: ; 0x02016B20
	push {r4, lr}
	ldr r4, _02016B40 ; =UNK_021C4D28
	ldrh r3, [r4, #0x14]
	cmp r1, r3
	bhs _02016B3A
	ldr r3, [r4, #0x0]
	ldr r4, [r4, #0x10]
	ldrb r1, [r4, r1]
	lsl r1, r1, #0x2
	ldr r1, [r3, r1]
	bl FUN_020AE82C
	pop {r4, pc}
_02016B3A:
	bl ErrorHandling
	pop {r4, pc}
	.balign 4
_02016B40: .word UNK_021C4D28

	thumb_func_start FUN_02016B44
FUN_02016B44: ; 0x02016B44
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _02016B56
	bl ErrorHandling
_02016B56:
	add r0, r5, #0x0
	sub r0, #0x10
	bl FUN_020ADDC0
	add r4, #0x10
	cmp r0, r4
	blo _02016B84
	sub r2, r5, #0x4
	ldr r0, _02016B8C ; =UNK_021C4D28
	ldr r2, [r2, #0x0]
	ldr r1, [r0, #0x0]
	lsl r2, r2, #0x18
	ldr r0, [r0, #0x10]
	lsr r2, r2, #0x18
	ldrb r0, [r0, r2]
	sub r5, #0x10
	add r2, r4, #0x0
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r1, r5, #0x0
	bl FUN_020ADE2C
	pop {r3-r5, pc}
_02016B84:
	bl ErrorHandling
	pop {r3-r5, pc}
	nop
_02016B8C: .word UNK_021C4D28

	thumb_func_start FUN_02016B90
FUN_02016B90: ; 0x02016B90
	mov r0, #0x1
	bx lr
