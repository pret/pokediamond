    .include "asm/macros.inc"
    .include "global.inc"

	.text

.extern LoadSingleElementFromNarc
.extern FreeMsgDataRawData
.extern DecryptMessageDirect
.extern DecryptMessageViaNewNarcHandle
.extern CopyEncryptedMessage16
.extern FUN_0200A4D4
.extern FUN_0200A584
.extern FUN_0200A648
.extern FUN_0200A670
.extern FUN_0200A76C

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
