    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start LoadSingleElementFromNarc
LoadSingleElementFromNarc: ; 0x0200A384
	ldr r3, _0200A388 ; =AllocAndReadWholeNarcMemberByIdPair
	bx r3
	.balign 4
_0200A388: .word AllocAndReadWholeNarcMemberByIdPair

	thumb_func_start FreeMsgDataRawData
FreeMsgDataRawData: ; 0x0200A38C
	ldr r3, _0200A390 ; =FreeToHeap
	bx r3
	.balign 4
_0200A390: .word FreeToHeap

	thumb_func_start DecryptMessageDirect
DecryptMessageDirect: ; 0x0200A394
	push {r3-r7, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	ldrh r0, [r3, #0x0]
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r5, r0
	bhs _0200A404
	lsl r0, r5, #0x3
	add r0, r3, r0
	ldr r2, [r0, #0x4]
	ldr r1, [r0, #0x8]
	ldr r6, _0200A40C ; =0x000002FD
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldrh r0, [r3, #0x2]
	add r7, r5, #0x1
	mul r6, r0
	add r0, r7, #0x0
	mul r0, r6
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	lsl r0, r6, #0x10
	orr r0, r6
	eor r2, r0
	eor r0, r1
	str r0, [sp, #0x4]
	str r2, [sp, #0x0]
	add r1, r3, r2
	add r0, r4, #0x0
	add r2, sp, #0x0
	bl CopyEncryptedMessage16
	ldr r2, [sp, #0x4]
	ldr r0, _0200A410 ; =0x00091BD3
	add r1, r7, #0x0
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	sub r3, r2, #0x1
	cmp r2, #0x0
	beq _0200A408
	ldr r0, _0200A414 ; =0x0000493D
_0200A3EA:
	ldrh r1, [r4, #0x0]
	eor r1, r5
	strh r1, [r4, #0x0]
	add r1, r5, r0
	lsl r1, r1, #0x10
	lsr r5, r1, #0x10
	add r1, r3, #0x0
	add r4, r4, #0x2
	sub r3, r3, #0x1
	cmp r1, #0x0
	bne _0200A3EA
	add sp, #0x8
	pop {r3-r7, pc}
_0200A404:
	bl ErrorHandling
_0200A408:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0200A40C: .word 0x000002FD
_0200A410: .word 0x00091BD3
_0200A414: .word 0x0000493D

	thumb_func_start DecryptMessageViaNewNarcHandle
DecryptMessageViaNewNarcHandle: ; 0x0200A418
	; r0: narc_id
	; r1: ???
	; r2: ???
	; r3: heap_id
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	add r1, r3, #0x0
	add r4, r2, #0x0
	bl NARC_ctor
	add r6, r0, #0x0
	beq _0200A4AE
	add r1, sp, #0xc
	str r1, [sp, #0x0]
	add r1, r5, #0x0
	mov r2, #0x0
	mov r3, #0x4
	bl NARC_ReadFromMember
	add r0, sp, #0x4
	lsl r2, r4, #0x3
	str r0, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r2, #0x4
	mov r3, #0x8
	bl NARC_ReadFromMember
	add r0, sp, #0x4
	ldrh r2, [r0, #0xa]
	ldr r0, _0200A4B4 ; =0x000002FD
	add r1, r4, #0x1
	mul r0, r2
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r0, r1, #0x10
	orr r1, r0
	ldr r0, [sp, #0x4]
	eor r0, r1
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x8]
	eor r0, r1
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x20]
	add r1, r5, #0x0
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x8]
	ldr r2, [sp, #0x4]
	add r0, r6, #0x0
	lsl r3, r3, #0x1
	bl NARC_ReadFromMember
	ldr r2, _0200A4B8 ; =0x00091BD3
	add r3, r4, #0x1
	mul r2, r3
	lsl r2, r2, #0x10
	ldr r0, [sp, #0x8]
	lsr r3, r2, #0x10
	sub r2, r0, #0x1
	ldr r1, [sp, #0x20]
	cmp r0, #0x0
	beq _0200A4A8
	ldr r0, _0200A4BC ; =0x0000493D
_0200A492:
	ldrh r4, [r1, #0x0]
	eor r4, r3
	strh r4, [r1, #0x0]
	add r3, r3, r0
	lsl r3, r3, #0x10
	add r4, r2, #0x0
	add r1, r1, #0x2
	lsr r3, r3, #0x10
	sub r2, r2, #0x1
	cmp r4, #0x0
	bne _0200A492
_0200A4A8:
	add r0, r6, #0x0
	bl NARC_dtor
_0200A4AE:
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_0200A4B4: .word 0x000002FD
_0200A4B8: .word 0x00091BD3
_0200A4BC: .word 0x0000493D

	thumb_func_start CopyEncryptedMessage16
CopyEncryptedMessage16: ; 0x0200A4C0
	add r3, r0, #0x0
	add r0, r1, #0x0
	add r1, r3, #0x0
	ldr r2, [r2, #0x4]
	ldr r3, _0200A4D0 ; =MIi_CpuCopy16
	lsl r2, r2, #0x1
	bx r3
	nop
_0200A4D0: .word MIi_CpuCopy16

	thumb_func_start FUN_0200A4D4
FUN_0200A4D4: ; 0x0200A4D4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldrh r0, [r5, #0x0]
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	cmp r4, r0
	bhs _0200A56A
	lsl r0, r4, #0x3
	add r0, r5, r0
	ldr r3, [r0, #0x4]
	ldr r2, [r0, #0x8]
	ldrh r1, [r5, #0x2]
	ldr r6, _0200A578 ; =0x000002FD
	add r0, r4, #0x1
	mul r6, r1
	add r1, r0, #0x0
	mul r1, r6
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	lsl r0, r1, #0x10
	orr r1, r0
	add r0, r3, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x8]
	eor r0, r1
	eor r6, r1
	str r0, [sp, #0x8]
	lsl r0, r6, #0x1
	str r0, [sp, #0x4]
	str r2, [sp, #0xc]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	str r6, [sp, #0xc]
	bl AllocFromHeapAtEnd
	add r7, r0, #0x0
	beq _0200A574
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x4]
	add r0, r5, r0
	add r1, r7, #0x0
	bl MIi_CpuCopy16
	ldr r1, _0200A57C ; =0x00091BD3
	add r2, r4, #0x1
	mul r1, r2
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	add r0, r7, #0x0
	sub r1, r6, #0x1
	cmp r6, #0x0
	beq _0200A556
	ldr r3, _0200A580 ; =0x0000493D
_0200A540:
	ldrh r4, [r0, #0x0]
	eor r4, r2
	strh r4, [r0, #0x0]
	add r2, r2, r3
	lsl r2, r2, #0x10
	add r4, r1, #0x0
	add r0, r0, #0x2
	lsr r2, r2, #0x10
	sub r1, r1, #0x1
	cmp r4, #0x0
	bne _0200A540
_0200A556:
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02021E8C
	add r0, r7, #0x0
	bl FreeToHeap
	add sp, #0x10
	pop {r3-r7, pc}
_0200A56A:
	bl ErrorHandling
	ldr r0, [sp, #0x0]
	bl FUN_02021A4C
_0200A574:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0200A578: .word 0x000002FD
_0200A57C: .word 0x00091BD3
_0200A580: .word 0x0000493D

	thumb_func_start FUN_0200A584
FUN_0200A584: ; 0x0200A584
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldrh r0, [r5, #0x0]
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	cmp r4, r0
	bhs _0200A62C
	lsl r0, r4, #0x3
	add r0, r5, r0
	ldr r3, [r0, #0x4]
	ldr r2, [r0, #0x8]
	ldrh r1, [r5, #0x2]
	ldr r6, _0200A63C ; =0x000002FD
	add r0, r4, #0x1
	mul r6, r1
	add r1, r0, #0x0
	mul r1, r6
	lsl r0, r1, #0x10
	lsr r1, r0, #0x10
	lsl r0, r1, #0x10
	orr r1, r0
	add r0, r3, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x8]
	eor r0, r1
	eor r6, r1
	str r0, [sp, #0x8]
	lsl r0, r6, #0x1
	str r0, [sp, #0x4]
	str r2, [sp, #0xc]
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	str r6, [sp, #0xc]
	bl AllocFromHeapAtEnd
	add r7, r0, #0x0
	beq _0200A626
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x4]
	add r0, r5, r0
	add r1, r7, #0x0
	bl MIi_CpuCopy16
	ldr r1, _0200A640 ; =0x00091BD3
	add r2, r4, #0x1
	mul r1, r2
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	add r0, r7, #0x0
	sub r1, r6, #0x1
	cmp r6, #0x0
	beq _0200A606
	ldr r3, _0200A644 ; =0x0000493D
_0200A5F0:
	ldrh r4, [r0, #0x0]
	eor r4, r2
	strh r4, [r0, #0x0]
	add r2, r2, r3
	lsl r2, r2, #0x10
	add r4, r1, #0x0
	add r0, r0, #0x2
	lsr r2, r2, #0x10
	sub r1, r1, #0x1
	cmp r4, #0x0
	bne _0200A5F0
_0200A606:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	beq _0200A61A
	add r1, r7, #0x0
	add r2, r6, #0x0
	bl FUN_02021E8C
_0200A61A:
	add r0, r7, #0x0
	bl FreeToHeap
	add sp, #0x10
	add r0, r4, #0x0
	pop {r3-r7, pc}
_0200A626:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0200A62C:
	bl ErrorHandling
	ldr r1, [sp, #0x0]
	mov r0, #0x4
	bl FUN_020219F4
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_0200A63C: .word 0x000002FD
_0200A640: .word 0x00091BD3
_0200A644: .word 0x0000493D

	thumb_func_start FUN_0200A648
FUN_0200A648: ; 0x0200A648
	push {r3-r7, lr}
	add r7, r3, #0x0
	add r5, r1, #0x0
	add r1, r7, #0x0
	add r4, r2, #0x0
	bl NARC_ctor
	add r6, r0, #0x0
	beq _0200A66E
	ldr r1, [sp, #0x18]
	add r2, r4, #0x0
	str r1, [sp, #0x0]
	add r1, r5, #0x0
	add r3, r7, #0x0
	bl FUN_0200A670
	add r0, r6, #0x0
	bl NARC_dtor
_0200A66E:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200A670
FUN_0200A670: ; 0x0200A670
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r2, #0x0
	add r2, sp, #0x10
	add r4, r3, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x0
	mov r3, #0x4
	add r7, r0, #0x0
	str r1, [sp, #0x4]
	bl NARC_ReadFromMember
	add r0, sp, #0x8
	ldrh r0, [r0, #0x8]
	cmp r5, r0
	bhs _0200A71E
	add r0, sp, #0x8
	lsl r2, r5, #0x3
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r7, #0x0
	add r2, r2, #0x4
	mov r3, #0x8
	bl NARC_ReadFromMember
	add r0, sp, #0x8
	ldrh r2, [r0, #0xa]
	ldr r0, _0200A72C ; =0x000002FD
	add r1, r5, #0x1
	mul r0, r2
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r0, r1, #0x10
	orr r1, r0
	ldr r0, [sp, #0x8]
	eor r0, r1
	str r0, [sp, #0x8]
	ldr r0, [sp, #0xc]
	eor r0, r1
	lsl r6, r0, #0x1
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	beq _0200A728
	str r4, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x8]
	add r0, r7, #0x0
	add r3, r6, #0x0
	bl NARC_ReadFromMember
	ldr r2, _0200A730 ; =0x00091BD3
	add r3, r5, #0x1
	mul r2, r3
	lsl r2, r2, #0x10
	ldr r0, [sp, #0xc]
	lsr r3, r2, #0x10
	add r1, r4, #0x0
	sub r2, r0, #0x1
	cmp r0, #0x0
	beq _0200A70A
	ldr r0, _0200A734 ; =0x0000493D
_0200A6F4:
	ldrh r5, [r1, #0x0]
	eor r5, r3
	strh r5, [r1, #0x0]
	add r3, r3, r0
	lsl r3, r3, #0x10
	add r5, r2, #0x0
	add r1, r1, #0x2
	lsr r3, r3, #0x10
	sub r2, r2, #0x1
	cmp r5, #0x0
	bne _0200A6F4
_0200A70A:
	ldr r0, [sp, #0x28]
	ldr r2, [sp, #0xc]
	add r1, r4, #0x0
	bl FUN_02021E8C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x14
	pop {r4-r7, pc}
_0200A71E:
	bl ErrorHandling
	ldr r0, [sp, #0x28]
	bl FUN_02021A4C
_0200A728:
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_0200A72C: .word 0x000002FD
_0200A730: .word 0x00091BD3
_0200A734: .word 0x0000493D

	thumb_func_start FUN_0200A738
FUN_0200A738: ; 0x0200A738
	push {r3-r7, lr}
	add r6, r3, #0x0
	add r5, r1, #0x0
	add r1, r6, #0x0
	add r4, r2, #0x0
	bl NARC_ctor
	add r7, r0, #0x0
	beq _0200A75E
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_0200A76C
	add r4, r0, #0x0
	add r0, r7, #0x0
	bl NARC_dtor
	b _0200A768
_0200A75E:
	mov r0, #0x4
	add r1, r6, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
_0200A768:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0200A76C
FUN_0200A76C: ; 0x0200A76C
	push {r3-r7, lr}
	sub sp, #0x18
	add r4, r2, #0x0
	add r2, sp, #0x14
	add r5, r3, #0x0
	str r2, [sp, #0x0]
	mov r2, #0x0
	mov r3, #0x4
	add r7, r0, #0x0
	str r1, [sp, #0x4]
	bl NARC_ReadFromMember
	add r0, sp, #0xc
	ldrh r0, [r0, #0x8]
	cmp r4, r0
	bhs _0200A82A
	add r0, sp, #0xc
	lsl r2, r4, #0x3
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r7, #0x0
	add r2, r2, #0x4
	mov r3, #0x8
	bl NARC_ReadFromMember
	add r0, sp, #0xc
	ldrh r2, [r0, #0xa]
	ldr r0, _0200A83C ; =0x000002FD
	add r1, r4, #0x1
	mul r0, r2
	mul r0, r1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	lsl r0, r1, #0x10
	orr r1, r0
	ldr r0, [sp, #0xc]
	eor r0, r1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	eor r0, r1
	add r1, r5, #0x0
	str r0, [sp, #0x10]
	bl FUN_020219F4
	str r0, [sp, #0x8]
	cmp r0, #0x0
	beq _0200A824
	ldr r0, [sp, #0x10]
	lsl r6, r0, #0x1
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl AllocFromHeapAtEnd
	add r5, r0, #0x0
	beq _0200A824
	str r5, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0xc]
	add r0, r7, #0x0
	add r3, r6, #0x0
	bl NARC_ReadFromMember
	ldr r2, _0200A840 ; =0x00091BD3
	add r3, r4, #0x1
	mul r2, r3
	lsl r2, r2, #0x10
	ldr r0, [sp, #0x10]
	lsr r3, r2, #0x10
	add r1, r5, #0x0
	sub r2, r0, #0x1
	cmp r0, #0x0
	beq _0200A814
	ldr r0, _0200A844 ; =0x0000493D
_0200A7FE:
	ldrh r4, [r1, #0x0]
	eor r4, r3
	strh r4, [r1, #0x0]
	add r3, r3, r0
	lsl r3, r3, #0x10
	add r4, r2, #0x0
	add r1, r1, #0x2
	lsr r3, r3, #0x10
	sub r2, r2, #0x1
	cmp r4, #0x0
	bne _0200A7FE
_0200A814:
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x10]
	add r1, r5, #0x0
	bl FUN_02021E8C
	add r0, r5, #0x0
	bl FreeToHeap
_0200A824:
	ldr r0, [sp, #0x8]
	add sp, #0x18
	pop {r3-r7, pc}
_0200A82A:
	bl ErrorHandling
	mov r0, #0x4
	add r1, r5, #0x0
	bl FUN_020219F4
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_0200A83C: .word 0x000002FD
_0200A840: .word 0x00091BD3
_0200A844: .word 0x0000493D

	thumb_func_start FUN_0200A848
FUN_0200A848: ; 0x0200A848
	ldrh r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0200A84C
FUN_0200A84C: ; 0x0200A84C
	push {r3, lr}
	sub sp, #0x8
	add r3, r0, #0x0
	mov r0, #0x4
	add r2, r1, #0x0
	str r0, [sp, #0x0]
	add r1, r3, #0x0
	add r0, sp, #0x4
	mov r3, #0x0
	bl ReadFromNarcMemberByIdPair
	add r0, sp, #0x4
	ldrh r0, [r0, #0x0]
	add sp, #0x8
	pop {r3, pc}
	.balign 4

; struct MsgData
; {
; 	u16 unk0;
; 	u16 unk2;
; 	u16 unk4;
; 	u16 unk6;
; 	union {
; 		u16 * raw;
; 		NARC * narc;
; 	} data;
; };

	thumb_func_start NewMsgDataFromNarc
NewMsgDataFromNarc: ; 0x0200A86C
	; r0: msg data type
	; r1: NARC ID
	; r2: File ID
	; r3: heap_id
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0xc
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	beq _0200A8B4
	cmp r5, #0x0
	bne _0200A8A0
	ldr r2, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl LoadSingleElementFromNarc
	str r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0200A8AA
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r3-r7, pc}
_0200A8A0:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl NARC_ctor
	str r0, [r4, #0x8]
_0200A8AA:
	strh r5, [r4, #0x0]
	strh r6, [r4, #0x4]
	ldr r0, [sp, #0x0]
	strh r7, [r4, #0x6]
	strh r0, [r4, #0x2]
_0200A8B4:
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start DestroyMsgData
DestroyMsgData: ; 0x0200A8B8
	push {r4, lr}
	add r4, r0, #0x0
	beq _0200A8DE
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0200A8CA
	cmp r0, #0x1
	beq _0200A8D2
	b _0200A8D8
_0200A8CA:
	ldr r0, [r4, #0x8]
	bl FreeMsgDataRawData
	b _0200A8D8
_0200A8D2:
	ldr r0, [r4, #0x8]
	bl NARC_dtor
_0200A8D8:
	add r0, r4, #0x0
	bl FreeToHeap
_0200A8DE:
	pop {r4, pc}

	thumb_func_start FUN_0200A8E0
FUN_0200A8E0: ; 0x0200A8E0
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	add r3, r1, #0x0
	cmp r0, #0x0
	beq _0200A8F6
	cmp r0, #0x1
	beq _0200A900
	add sp, #0x4
	pop {r3-r4, pc}
_0200A8F6:
	ldr r0, [r4, #0x8]
	bl FUN_0200A4D4
	add sp, #0x4
	pop {r3-r4, pc}
_0200A900:
	str r2, [sp, #0x0]
	add r2, r3, #0x0
	ldrh r1, [r4, #0x6]
	ldrh r3, [r4, #0x2]
	ldr r0, [r4, #0x8]
	bl FUN_0200A670
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0200A914
FUN_0200A914: ; 0x0200A914
	push {r3, lr}
	add r3, r0, #0x0
	ldrh r0, [r3, #0x0]
	add r2, r1, #0x0
	cmp r0, #0x0
	beq _0200A926
	cmp r0, #0x1
	beq _0200A930
	b _0200A93C
_0200A926:
	ldrh r2, [r3, #0x2]
	ldr r0, [r3, #0x8]
	bl FUN_0200A584
	pop {r3, pc}
_0200A930:
	ldr r0, [r3, #0x8]
	ldrh r1, [r3, #0x6]
	ldrh r3, [r3, #0x2]
	bl FUN_0200A76C
	pop {r3, pc}
_0200A93C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0200A940
FUN_0200A940: ; 0x0200A940
	push {r3, lr}
	add r1, r0, #0x0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0200A950
	cmp r0, #0x1
	beq _0200A958
	b _0200A962
_0200A950:
	ldr r0, [r1, #0x8]
	bl FUN_0200A848
	pop {r3, pc}
_0200A958:
	ldrh r0, [r1, #0x4]
	ldrh r1, [r1, #0x6]
	bl FUN_0200A84C
	pop {r3, pc}
_0200A962:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start DecryptCopyString
DecryptCopyString: ; 0x0200A968
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	add r3, r1, #0x0
	cmp r0, #0x0
	beq _0200A97E
	cmp r0, #0x1
	beq _0200A988
	add sp, #0x4
	pop {r3-r4, pc}
_0200A97E:
	ldr r0, [r4, #0x8]
	bl DecryptMessageDirect
	add sp, #0x4
	pop {r3-r4, pc}
_0200A988:
	str r2, [sp, #0x0]
	add r2, r3, #0x0
	ldrh r0, [r4, #0x4]
	ldrh r1, [r4, #0x6]
	ldrh r3, [r4, #0x2]
	bl DecryptMessageViaNewNarcHandle
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start GetSpeciesName
GetSpeciesName: ; 0x0200A99C
	; r0: species
	; r1: heap_id
	; r2: dest
	push {r4-r6, lr}
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r3, r1, #0x0
	ldr r2, _0200A9C0 ; =0x0000016A
	mov r0, #0x1
	mov r1, #0x1a ; NARC_MSGDATA_MSG
	bl NewMsgDataFromNarc
	add r6, r0, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl DecryptCopyString
	add r0, r6, #0x0
	bl DestroyMsgData
	pop {r4-r6, pc}
	.balign 4
_0200A9C0: .word 0x0000016A

	thumb_func_start FUN_0200A9C4
FUN_0200A9C4: ; 0x0200A9C4
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x4]
	add r5, r1, #0x0
	mov r0, #0x1
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0xa
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_020219F4
	add r4, r0, #0x0
	beq _0200AA0E
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0200A914
	add r5, r0, #0x0
	beq _0200AA08
	add r0, r7, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0200B7B8
	ldr r1, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02021ACC
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02021A20
_0200AA08:
	add r0, r4, #0x0
	bl FUN_02021A20
_0200AA0E:
	ldr r0, [sp, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_0200AA14
FUN_0200AA14: ; 0x0200AA14
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r2, #0x93
	add r6, r0, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	lsl r2, r2, #0x2
	add r3, r5, #0x0
	bl NewMsgDataFromNarc
	add r4, r0, #0x0
	beq _0200AA4C
	mov r0, #0x10
	add r1, r5, #0x0
	bl FUN_020219F4
	add r5, r0, #0x0
	beq _0200AA42
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_0200A8E0
_0200AA42:
	add r0, r4, #0x0
	bl DestroyMsgData
	add r0, r5, #0x0
	pop {r4-r6, pc}
_0200AA4C:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0200AA50
FUN_0200AA50: ; 0x0200AA50
	push {r3-r5, lr}
	ldr r2, _0200AA7C ; =0x0000016A
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r0, #0x1
	mov r1, #0x1a
	bl NewMsgDataFromNarc
	add r5, r0, #0x0
	beq _0200AA76
	add r1, r4, #0x0
	bl FUN_0200A914
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl DestroyMsgData
	add r0, r4, #0x0
	pop {r3-r5, pc}
_0200AA76:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_0200AA7C: .word 0x0000016A
