    .include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.section .rodata

	.global UNK_020F5800
UNK_020F5800: ; 0x020F5800
	.byte 0x04, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x07, 0x00

	.global UNK_020F5808
UNK_020F5808: ; 0x020F5808
	.byte 0x14, 0x15, 0x16, 0x17, 0x10, 0x11, 0x12, 0x13, 0x0C, 0x0D, 0x0E, 0x0F

	.global UNK_020F5814
UNK_020F5814: ; 0x020F5814
	.byte 0x04, 0x00, 0x06, 0x00, 0x0B, 0x00, 0x06, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0B, 0x00, 0x08, 0x00

	.global UNK_020F5824
UNK_020F5824: ; 0x020F5824
	.byte 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00

	.section .data

	.global UNK_02105E5C
UNK_02105E5C: ; 0x02105E5C
	.byte 0x04, 0x00, 0x07, 0x00, 0x0B, 0x00, 0x07, 0x00

	.global UNK_02105E64
UNK_02105E64: ; 0x02105E64
	.byte 0x04, 0x00, 0x06, 0x00, 0x0B, 0x00, 0x06, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0B, 0x00, 0x08, 0x00

	.section .bss

	.global UNK_021C5A68
UNK_021C5A68: ; 0x021C5A68
	.space 0x4

	.text

	thumb_func_start FUN_0204CB20
FUN_0204CB20: ; 0x0204CB20
	push {r3-r7, lr}
	add r4, r1, #0x0
	ldr r1, _0204CC34 ; =UNK_021C5A68
	add r5, r2, #0x0
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _0204CB32
	mov r0, #0x0
	pop {r3-r7, pc}
_0204CB32:
	bne _0204CB40
	mov r2, #0xb1
	str r0, [r1, #0x0]
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuFill8
_0204CB40:
	ldr r1, _0204CC34 ; =UNK_021C5A68
	ldr r0, _0204CC38 ; =0x000002BE
	ldr r2, [r1, #0x0]
	strb r5, [r2, r0]
	mov r2, #0x0
	ldr r0, [r1, #0x0]
	cmp r5, #0x0
	str r2, [r0, #0x4]
	beq _0204CB6C
	bl MOD18_02244D1C
	add r1, r0, #0x0
	mov r0, #0xf
	bl AllocFromHeap
	ldr r1, _0204CC34 ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x4]
	ldr r0, [r1, #0x0]
	ldr r0, [r0, #0x4]
	bl MOD18_02244D20
_0204CB6C:
	ldr r0, _0204CC34 ; =UNK_021C5A68
	ldr r7, _0204CC3C ; =0x0000FFFF
	ldr r1, [r0, #0x0]
	str r4, [r1, #0x54]
	mov r1, #0x0
	add r2, r1, #0x0
	add r3, r1, #0x0
_0204CB7A:
	ldr r4, [r0, #0x0]
	add r5, r4, r2
	mov r4, #0x0
	add r5, #0xa6
	mvn r4, r4
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	add r4, r4, r2
	add r4, #0xa2
	strh r7, [r4, #0x0]
	ldr r4, [r0, #0x0]
	add r4, r4, r2
	add r4, #0xa4
	strh r7, [r4, #0x0]
	ldr r4, [r0, #0x0]
	add r5, r4, r2
	add r5, #0xa7
	mov r4, #0x2
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	add r5, r4, r2
	mov r4, #0x0
	add r5, #0x66
	mvn r4, r4
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	add r4, r4, r2
	add r4, #0x62
	strh r7, [r4, #0x0]
	ldr r4, [r0, #0x0]
	add r4, r4, r2
	add r4, #0x64
	strh r7, [r4, #0x0]
	ldr r4, [r0, #0x0]
	add r5, r4, r2
	add r5, #0x67
	mov r4, #0x2
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	ldr r5, _0204CC40 ; =0x00000102
	add r6, r4, r1
	mov r4, #0x0
	mvn r4, r4
	strb r4, [r6, r5]
	ldr r4, [r0, #0x0]
	add r2, #0x8
	add r5, r4, r1
	add r5, #0xe2
	mov r4, #0x0
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	add r5, r4, r1
	add r5, #0xea
	mov r4, #0x1
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	add r5, r4, r1
	add r5, #0xf2
	mov r4, #0x0
	strb r4, [r5, #0x0]
	ldr r4, [r0, #0x0]
	mov r5, #0xff
	add r6, r4, r3
	add r4, r5, #0x0
	add r4, #0x6b
	add r1, r1, #0x1
	add r3, #0x22
	strh r5, [r6, r4]
	cmp r1, #0x8
	blt _0204CB7A
	ldr r2, _0204CC34 ; =UNK_021C5A68
	mov r1, #0xaf
	ldr r3, [r2, #0x0]
	lsl r1, r1, #0x2
	mov r0, #0x0
	strb r0, [r3, r1]
	ldr r2, [r2, #0x0]
	add r1, r1, #0x3
	strb r0, [r2, r1]
	ldr r0, _0204CC44 ; =FUN_0204D4F0
	mov r1, #0x0
	mov r2, #0xc8
	bl FUN_0200CA44
	ldr r1, _0204CC34 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x50]
	bl FUN_02030FA8
	bl FUN_0204CF60
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_0204CC34: .word UNK_021C5A68
_0204CC38: .word 0x000002BE
_0204CC3C: .word 0x0000FFFF
_0204CC40: .word 0x00000102
_0204CC44: .word FUN_0204D4F0

	thumb_func_start FUN_0204CC48
FUN_0204CC48: ; 0x0204CC48
	push {r3-r7, lr}
	ldr r4, _0204CC94 ; =UNK_021C5A68
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0204CC92
	ldr r6, _0204CC98 ; =0x000002BE
	mov r5, #0x0
	mov r7, #0x1
_0204CC58:
	ldr r0, [r4, #0x0]
	ldrb r0, [r0, r6]
	cmp r0, #0x0
	beq _0204CC6E
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_0204D43C
	b _0204CC7A
_0204CC6E:
	lsl r0, r5, #0x18
	mov r1, #0x1
	lsr r0, r0, #0x18
	add r2, r1, #0x0
	bl FUN_0204D43C
_0204CC7A:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0204CC58
	ldr r0, _0204CC94 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	ldr r0, _0204CC98 ; =0x000002BE
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	beq _0204CC92
	mov r1, #0x1
	sub r0, r0, #0x1
	strb r1, [r2, r0]
_0204CC92:
	pop {r3-r7, pc}
	.balign 4
_0204CC94: .word UNK_021C5A68
_0204CC98: .word 0x000002BE

	thumb_func_start FUN_0204CC9C
FUN_0204CC9C: ; 0x0204CC9C
	push {r3, lr}
	ldr r1, _0204CCD8 ; =UNK_021C5A68
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	beq _0204CCD6
	ldr r0, _0204CCDC ; =0x000002BB
	mov r2, #0x1
	strb r2, [r3, r0]
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2
	strb r2, [r1, r0]
	bl FUN_0204CF60
	mov r0, #0x1
	bl FUN_0204D168
	ldr r0, _0204CCD8 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	ldr r0, _0204CCD8 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
_0204CCD6:
	pop {r3, pc}
	.balign 4
_0204CCD8: .word UNK_021C5A68
_0204CCDC: .word 0x000002BB

	thumb_func_start FUN_0204CCE0
FUN_0204CCE0: ; 0x0204CCE0
	push {r3-r7, lr}
	ldr r7, _0204CD70 ; =UNK_021C5A68
	add r6, r0, #0x0
	ldr r0, [r7, #0x0]
	cmp r0, #0x0
	beq _0204CD6E
	mov r4, #0x0
	add r5, r4, #0x0
_0204CCF0:
	ldr r0, [r7, #0x0]
	add r1, r0, r5
	mov r0, #0x9f
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204CD0E
	bl FreeToHeap
	ldr r0, [r7, #0x0]
	mov r1, #0x0
	add r2, r0, r5
	mov r0, #0x9f
	lsl r0, r0, #0x2
	str r1, [r2, r0]
_0204CD0E:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x5
	blt _0204CCF0
	ldr r0, _0204CD70 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	ldr r0, _0204CD74 ; =0x000002B2
	ldrh r1, [r2, r0]
	cmp r1, #0x5
	blo _0204CD28
	ldr r0, [r2, #0x54]
	bl FUN_02061B64
_0204CD28:
	mov r4, #0x0
	add r5, r4, #0x0
_0204CD2C:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_0204D43C
	add r4, r4, #0x1
	cmp r4, #0x8
	blt _0204CD2C
	ldr r0, _0204CD70 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x50]
	bl FUN_0200CAB4
	ldr r0, _0204CD70 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0204CD60
	bl MOD18_02244D3C
	ldr r0, _0204CD70 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl FreeToHeap
_0204CD60:
	ldr r0, _0204CD70 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _0204CD70 ; =UNK_021C5A68
	mov r1, #0x0
	str r1, [r0, #0x0]
_0204CD6E:
	pop {r3-r7, pc}
	.balign 4
_0204CD70: .word UNK_021C5A68
_0204CD74: .word 0x000002B2

	thumb_func_start FUN_0204CD78
FUN_0204CD78: ; 0x0204CD78
	push {r4, lr}
	lsl r4, r0, #0x2
	ldr r0, _0204CDB0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x28]
	cmp r0, #0x0
	beq _0204CDAC
	bl FUN_020646A0
	cmp r0, #0x0
	beq _0204CD9E
	ldr r0, _0204CDB0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x28]
	bl FUN_02064520
	b _0204CDA2
_0204CD9E:
	bl GF_AssertFail
_0204CDA2:
	ldr r0, _0204CDB0 ; =UNK_021C5A68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	str r1, [r0, #0x28]
_0204CDAC:
	pop {r4, pc}
	nop
_0204CDB0: .word UNK_021C5A68

	thumb_func_start FUN_0204CDB4
FUN_0204CDB4: ; 0x0204CDB4
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r6, _0204CED4 ; =UNK_021C5A68
	add r7, r4, #0x0
	add r5, r4, #0x0
_0204CDBE:
	add r0, r4, #0x0
	bl FUN_0204E778
	add r0, r4, #0x0
	bl FUN_0204CD78
	cmp r4, #0x0
	beq _0204CDD4
	add r0, r4, #0x0
	bl FUN_0204ED9C
_0204CDD4:
	ldr r1, [r6, #0x0]
	add r0, r1, r7
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204CDFA
	ldr r2, [r1, #0x54]
	ldr r2, [r2, #0x38]
	cmp r2, r0
	beq _0204CDF2
	ldr r2, _0204CED8 ; =0x000002BE
	ldrb r1, [r1, r2]
	cmp r1, #0x0
	beq _0204CDF2
	bl FUN_02055168
_0204CDF2:
	ldr r0, [r6, #0x0]
	add r1, r0, r7
	mov r0, #0x0
	str r0, [r1, #0x8]
_0204CDFA:
	ldr r0, [r6, #0x0]
	add r7, r7, #0x4
	add r1, r0, r4
	add r1, #0x48
	mov r0, #0x0
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	mov r0, #0x0
	add r1, #0xa6
	mvn r0, r0
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldr r0, _0204CEDC ; =0x0000FFFF
	add r1, #0xa2
	strh r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldr r0, _0204CEDC ; =0x0000FFFF
	add r1, #0xa4
	strh r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	add r1, #0xa7
	mov r0, #0x2
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	mov r0, #0x0
	add r1, #0x66
	mvn r0, r0
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldr r0, _0204CEDC ; =0x0000FFFF
	add r1, #0x62
	strh r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldr r0, _0204CEDC ; =0x0000FFFF
	add r1, #0x64
	strh r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	add r1, #0x67
	mov r0, #0x2
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	mov r1, #0x0
	add r2, r0, r4
	ldr r0, _0204CEE0 ; =0x00000102
	mvn r1, r1
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	mov r1, #0x0
	add r2, r0, r4
	ldr r0, _0204CEE4 ; =0x0000010A
	add r5, #0x8
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	add r1, r0, r4
	add r1, #0xe2
	mov r0, #0x0
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r4
	add r1, #0xea
	mov r0, #0x1
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r0, r4
	add r1, #0xf2
	mov r0, #0x0
	strb r0, [r1, #0x0]
	ldr r0, [r6, #0x0]
	mov r1, #0x0
	add r2, r0, r4
	ldr r0, _0204CEE8 ; =0x0000013A
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	add r2, r0, r4
	ldr r0, _0204CEEC ; =0x00000142
	add r4, r4, #0x1
	strb r1, [r2, r0]
	cmp r4, #0x8
	blt _0204CDBE
	ldr r0, _0204CED4 ; =UNK_021C5A68
	ldr r1, _0204CEF0 ; =0x000002BF
	ldr r2, [r0, #0x0]
	mov r0, #0x0
	strb r0, [r2, r1]
	bl FUN_0204CF60
	ldr r0, _0204CED4 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x50]
	cmp r0, #0x0
	bne _0204CED0
	ldr r0, _0204CEF4 ; =FUN_0204D4F0
	mov r1, #0x0
	mov r2, #0xc8
	bl FUN_0200CA44
	ldr r1, _0204CED4 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x50]
_0204CED0:
	pop {r3-r7, pc}
	nop
_0204CED4: .word UNK_021C5A68
_0204CED8: .word 0x000002BE
_0204CEDC: .word 0x0000FFFF
_0204CEE0: .word 0x00000102
_0204CEE4: .word 0x0000010A
_0204CEE8: .word 0x0000013A
_0204CEEC: .word 0x00000142
_0204CEF0: .word 0x000002BF
_0204CEF4: .word FUN_0204D4F0

	thumb_func_start FUN_0204CEF8
FUN_0204CEF8: ; 0x0204CEF8
	push {r3, lr}
	ldr r0, _0204CF20 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x50]
	cmp r0, #0x0
	beq _0204CF16
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0204D4F0
	ldr r0, _0204CF20 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x50]
	bl FUN_0200CAB4
_0204CF16:
	ldr r0, _0204CF20 ; =UNK_021C5A68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x50]
	pop {r3, pc}
	.balign 4
_0204CF20: .word UNK_021C5A68

	thumb_func_start FUN_0204CF24
FUN_0204CF24: ; 0x0204CF24
	push {r3-r5, lr}
	ldr r0, _0204CF58 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204CF54
	mov r5, #0x0
	add r4, r5, #0x0
_0204CF32:
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	add r1, r4, #0x0
	add r2, r4, #0x0
	bl FUN_0204D43C
	add r0, r5, #0x0
	bl FUN_0204F69C
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0204CF32
	ldr r0, _0204CF58 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204CF5C ; =0x000002BD
	strb r2, [r1, r0]
_0204CF54:
	pop {r3-r5, pc}
	nop
_0204CF58: .word UNK_021C5A68
_0204CF5C: .word 0x000002BD

	thumb_func_start FUN_0204CF60
FUN_0204CF60: ; 0x0204CF60
	push {r4, lr}
	bl FUN_02031190
	ldr r1, _0204D03C ; =UNK_021C5A68
	lsl r0, r0, #0x2
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x54]
	add r0, r2, r0
	ldr r1, [r1, #0x38]
	str r1, [r0, #0x8]
	bl FUN_02031190
	ldr r1, _0204D03C ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0x48
	strb r2, [r0, #0x0]
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0204D03C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	ldr r1, _0204D03C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0xa2
	strh r0, [r1, #0x0]
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0204D03C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	ldr r1, _0204D03C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0xa4
	strh r0, [r1, #0x0]
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0204D03C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	ldr r1, _0204D03C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0xa6
	strb r0, [r1, #0x0]
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0204D03C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	ldr r1, _0204D03C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0x62
	strh r0, [r1, #0x0]
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0204D03C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	ldr r1, _0204D03C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0x64
	strh r0, [r1, #0x0]
	bl FUN_02031190
	add r4, r0, #0x0
	ldr r0, _0204D03C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	ldr r1, _0204D03C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0x66
	strb r0, [r1, #0x0]
	pop {r4, pc}
	nop
_0204D03C: .word UNK_021C5A68

	thumb_func_start FUN_0204D040
FUN_0204D040: ; 0x0204D040
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, _0204D110 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0204D114 ; =0x000002BF
	strb r2, [r1, r0]
	bl FUN_02031190
	ldr r2, _0204D110 ; =UNK_021C5A68
	add r1, r0, #0x0
	ldr r4, [r2, #0x0]
	lsl r6, r1, #0x2
	ldr r0, [r4, #0x54]
	ldr r3, [r0, #0x38]
	add r0, r4, r6
	str r3, [r0, #0x8]
	ldr r0, [r2, #0x0]
	mov r3, #0x1
	add r0, r0, r1
	add r0, #0x48
	strb r3, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldr r3, [r2, #0x0]
	lsl r5, r0, #0x3
	add r0, r3, r5
	add r0, #0xa2
	lsl r4, r1, #0x3
	add r3, r3, r4
	ldrh r0, [r0, #0x0]
	add r3, #0xa2
	strh r0, [r3, #0x0]
	ldr r3, [r2, #0x0]
	add r0, r3, r5
	add r0, #0xa4
	add r3, r3, r4
	ldrh r0, [r0, #0x0]
	add r3, #0xa4
	strh r0, [r3, #0x0]
	ldr r7, [r2, #0x0]
	mov r0, #0xa6
	add r3, r7, r5
	ldrsb r0, [r3, r0]
	add r3, r7, r4
	add r3, #0xa6
	strb r0, [r3, #0x0]
	ldr r3, [r2, #0x0]
	mov r7, #0x29
	add r0, r3, r5
	add r0, #0x62
	add r3, r3, r4
	ldrh r0, [r0, #0x0]
	add r3, #0x62
	lsl r7, r7, #0x4
	strh r0, [r3, #0x0]
	ldr r3, [r2, #0x0]
	add r0, r3, r5
	add r0, #0x64
	add r3, r3, r4
	ldrh r0, [r0, #0x0]
	add r3, #0x64
	strh r0, [r3, #0x0]
	ldr r0, [r2, #0x0]
	mov r3, #0x66
	add r5, r0, r5
	add r0, r0, r4
	ldrsb r5, [r5, r3]
	add r0, #0x66
	strb r5, [r0, #0x0]
	ldr r0, [sp, #0x0]
	ldr r4, [r2, #0x0]
	lsl r5, r0, #0x2
	add r0, r4, r5
	ldr r0, [r0, r7]
	add r4, r4, r6
	str r0, [r4, r7]
	ldr r0, [r2, #0x0]
	mov r4, #0x0
	add r0, r0, r5
	str r4, [r0, r7]
	ldr r2, [r2, #0x0]
	add r0, r2, r6
	ldr r0, [r0, r7]
	cmp r0, #0x0
	beq _0204D0F8
	add r3, #0xe4
	add r3, r2, r3
	mov r2, #0x22
	mul r2, r1
	add r1, r3, r2
	bl PlayerProfile_Copy
_0204D0F8:
	ldr r1, _0204D110 ; =UNK_021C5A68
	mov r0, #0xff
	ldr r3, [r1, #0x0]
	ldr r1, [sp, #0x0]
	mov r2, #0x22
	mul r2, r1
	add r1, r0, #0x0
	add r2, r3, r2
	add r1, #0x6b
	strh r0, [r2, r1]
	pop {r3-r7, pc}
	nop
_0204D110: .word UNK_021C5A68
_0204D114: .word 0x000002BF

	thumb_func_start FUN_0204D118
FUN_0204D118: ; 0x0204D118
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _0204D160 ; =UNK_021C5A68
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r1, sp, #0x0
	strb r4, [r1, #0x0]
	asr r2, r4, #0x8
	strb r2, [r1, #0x1]
	asr r2, r6, #0x8
	strb r6, [r1, #0x2]
	strb r2, [r1, #0x3]
	strb r0, [r1, #0x4]
	cmp r5, #0x0
	beq _0204D14A
	ldrb r2, [r1, #0x4]
	mov r0, #0x80
	orr r0, r2
	strb r0, [r1, #0x4]
_0204D14A:
	mov r0, #0x16
	add r1, sp, #0x0
	bl FUN_020311D0
	ldr r0, _0204D160 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204D164 ; =0x000002BB
	strb r2, [r1, r0]
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_0204D160: .word UNK_021C5A68
_0204D164: .word 0x000002BB

	thumb_func_start FUN_0204D168
FUN_0204D168: ; 0x0204D168
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0204D194 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	add r4, r0, #0x0
	ldr r0, _0204D194 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r2, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204D118
	pop {r3-r5, pc}
	nop
_0204D194: .word UNK_021C5A68

	thumb_func_start FUN_0204D198
FUN_0204D198: ; 0x0204D198
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02031190
	ldr r1, _0204D1C8 ; =UNK_021C5A68
	lsl r0, r0, #0x3
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0x62
	ldrh r4, [r0, #0x0]
	bl FUN_02031190
	ldr r1, _0204D1C8 ; =UNK_021C5A68
	lsl r0, r0, #0x3
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0x64
	ldrh r2, [r0, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0204D118
	pop {r3-r5, pc}
	nop
_0204D1C8: .word UNK_021C5A68

	thumb_func_start FUN_0204D1CC
FUN_0204D1CC: ; 0x0204D1CC
	push {r3-r5, lr}
	sub sp, #0x8
	ldrh r2, [r1, #0x0]
	mov r4, #0xf
	lsl r4, r4, #0xc
	ldrh r3, [r1, #0x2]
	cmp r2, r4
	blo _0204D1DE
	sub r2, r4, #0x1
_0204D1DE:
	mov r4, #0xf
	lsl r4, r4, #0xc
	cmp r3, r4
	blo _0204D1E8
	sub r3, r4, #0x1
_0204D1E8:
	mov r4, #0xf
	and r0, r4
	add r4, sp, #0x0
	strb r0, [r4, #0x0]
	strb r2, [r4, #0x1]
	asr r2, r2, #0x8
	add r5, r2, #0x0
	mov r0, #0x1
	and r5, r0
	asr r2, r3, #0x7
	mov r0, #0x2
	and r0, r2
	add r0, r5, r0
	strb r0, [r4, #0x2]
	strb r3, [r4, #0x3]
	ldrb r0, [r1, #0x7]
	cmp r0, #0x0
	beq _0204D214
	ldrb r2, [r4, #0x2]
	mov r0, #0x80
	orr r0, r2
	strb r0, [r4, #0x2]
_0204D214:
	mov r2, #0x4
	ldrsb r2, [r1, r2]
	add r5, sp, #0x0
	ldrb r0, [r5, #0x0]
	lsr r4, r2, #0x1f
	lsl r3, r2, #0x1e
	sub r3, r3, r4
	mov r2, #0x1e
	ror r3, r2
	add r2, r4, r3
	lsl r2, r2, #0x4
	add r0, r0, r2
	strb r0, [r5, #0x0]
	ldrb r0, [r1, #0x5]
	ldrb r2, [r5, #0x0]
	add r1, sp, #0x0
	lsl r0, r0, #0x6
	add r0, r2, r0
	strb r0, [r5, #0x0]
	mov r0, #0x17
	mov r2, #0x0
	bl FUN_02030BC4
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0204D248
FUN_0204D248: ; 0x0204D248
	push {r3-r5, lr}
	ldr r0, _0204D2A8 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055370
	add r4, r0, #0x0
	ldr r0, _0204D2A8 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055378
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _0204D292
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0204D292
	ldr r0, _0204D2A8 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204D2AC ; =0x000002BA
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204D292
	mov r0, #0x1
	bl FUN_0204D168
	ldr r0, _0204D2A8 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204D2AC ; =0x000002BA
	strb r2, [r1, r0]
_0204D292:
	cmp r4, #0x1
	bne _0204D2A4
	cmp r5, #0x1
	bne _0204D2A4
	ldr r0, _0204D2A8 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0204D2AC ; =0x000002BA
	strb r2, [r1, r0]
_0204D2A4:
	pop {r3-r5, pc}
	nop
_0204D2A8: .word UNK_021C5A68
_0204D2AC: .word 0x000002BA

	thumb_func_start FUN_0204D2B0
FUN_0204D2B0: ; 0x0204D2B0
	push {r3-r7, lr}
	mov r4, #0x0
	ldr r7, _0204D2FC ; =UNK_021C5A68
	add r5, r4, #0x0
	add r6, r4, #0x0
_0204D2BA:
	ldr r0, [r7, #0x0]
	add r2, r0, r4
	add r1, r2, #0x0
	add r1, #0x48
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204D2E8
	ldr r3, _0204D300 ; =0x00000132
	add r1, r0, #0x0
	ldrb r3, [r2, r3]
	add r1, #0x62
	cmp r3, #0x0
	bne _0204D2DC
	ldr r3, _0204D304 ; =0x000002BB
	ldrb r0, [r0, r3]
	cmp r0, #0x0
	beq _0204D2E8
_0204D2DC:
	ldr r0, _0204D300 ; =0x00000132
	add r1, r1, r5
	strb r6, [r2, r0]
	add r0, r4, #0x0
	bl FUN_0204D1CC
_0204D2E8:
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x8
	blt _0204D2BA
	ldr r0, _0204D2FC ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0204D304 ; =0x000002BB
	strb r2, [r1, r0]
	pop {r3-r7, pc}
	.balign 4
_0204D2FC: .word UNK_021C5A68
_0204D300: .word 0x00000132
_0204D304: .word 0x000002BB

	thumb_func_start FUN_0204D308
FUN_0204D308: ; 0x0204D308
	ldr r0, _0204D31C ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0204D318
	mov r0, #0xae
	mov r1, #0x0
	lsl r0, r0, #0x2
	strb r1, [r2, r0]
_0204D318:
	bx lr
	nop
_0204D31C: .word UNK_021C5A68

	thumb_func_start FUN_0204D320
FUN_0204D320: ; 0x0204D320
	mov r0, #0xb1
	lsl r0, r0, #0x2
	bx lr
	.balign 4

	thumb_func_start FUN_0204D328
FUN_0204D328: ; 0x0204D328
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r1, _0204D430 ; =UNK_021C5A68
	add r5, r0, #0x0
	ldr r2, [r1, #0x0]
	lsl r6, r5, #0x2
	add r1, r2, r6
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	bne _0204D42A
	ldr r1, _0204D434 ; =0x000002BD
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	bne _0204D42A
	bl FUN_0202DFA4
	str r0, [sp, #0xc]
	cmp r0, #0x0
	beq _0204D42A
	ldr r0, _0204D430 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204D438 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204D37C
	bl FUN_02031190
	cmp r5, r0
	beq _0204D37C
	ldr r0, _0204D430 ; =UNK_021C5A68
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x8
	ldr r0, [r0, #0x54]
	add r1, r5, r1
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	cmp r0, #0x0
	beq _0204D37C
	bl FUN_02057654
_0204D37C:
	ldr r0, _0204D430 ; =UNK_021C5A68
	lsl r4, r5, #0x3
	ldr r7, [r0, #0x0]
	ldr r0, [sp, #0xc]
	bl PlayerProfile_GetTrainerGender
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	str r1, [sp, #0x8]
	ldr r0, [r7, #0x54]
	add r7, r7, r4
	add r1, r7, #0x0
	add r2, r7, #0x0
	add r1, #0xa2
	add r2, #0xa4
	mov r3, #0xa6
	ldrh r1, [r1, #0x0]
	ldrh r2, [r2, #0x0]
	ldrsb r3, [r7, r3]
	ldr r0, [r0, #0x34]
	bl FUN_02055068
	add r7, r0, #0x0
	bne _0204D3B2
	bl GF_AssertFail
_0204D3B2:
	ldr r0, _0204D430 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r0, r0, r6
	str r7, [r0, #0x8]
	add r0, r7, #0x0
	bl FUN_020553A0
	mov r1, #0x1
	lsl r1, r1, #0x8
	add r1, r5, r1
	bl FUN_02058444
	ldr r0, _0204D430 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204D438 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204D3DC
	add r0, r5, #0x0
	bl MOD18_0223E4D4
_0204D3DC:
	ldr r0, _0204D430 ; =UNK_021C5A68
	ldr r1, _0204D438 ; =0x000002BE
	ldr r3, [r0, #0x0]
	ldrb r2, [r3, r1]
	cmp r2, #0x0
	beq _0204D41E
	add r0, r3, r5
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204D41E
	sub r0, r1, #0x1
	ldrb r0, [r3, r0]
	cmp r0, #0x0
	bne _0204D40E
	add r1, r3, r4
	ldr r0, [r3, #0x54]
	add r3, r3, r4
	add r1, #0xa2
	add r3, #0xa4
	ldrh r1, [r1, #0x0]
	ldrh r3, [r3, #0x0]
	mov r2, #0x0
	bl MOD05_021E5B30
_0204D40E:
	ldr r0, _0204D430 ; =UNK_021C5A68
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add sp, #0x10
	add r0, r0, r5
	add r0, #0x48
	strb r1, [r0, #0x0]
	pop {r3-r7, pc}
_0204D41E:
	cmp r2, #0x0
	bne _0204D42A
	add r0, r3, r5
	mov r1, #0x1
	add r0, #0x48
	strb r1, [r0, #0x0]
_0204D42A:
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0204D430: .word UNK_021C5A68
_0204D434: .word 0x000002BD
_0204D438: .word 0x000002BE

	thumb_func_start FUN_0204D43C
FUN_0204D43C: ; 0x0204D43C
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0204D4CC ; =UNK_021C5A68
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	add r7, r2, #0x0
	cmp r0, #0x0
	beq _0204D4C8
	add r0, #0x5a
	mov r1, #0x0
	mov r2, #0x8
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl FUN_0204CD78
	ldr r0, _0204D4CC ; =UNK_021C5A68
	lsl r4, r5, #0x2
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204D492
	ldr r2, [r1, #0x54]
	ldr r2, [r2, #0x38]
	cmp r2, r0
	beq _0204D488
	ldr r2, _0204D4D0 ; =0x000002BE
	ldrb r1, [r1, r2]
	cmp r1, #0x0
	bne _0204D47E
	cmp r7, #0x0
	beq _0204D484
_0204D47E:
	bl FUN_02055168
	b _0204D488
_0204D484:
	bl FUN_02055160
_0204D488:
	ldr r0, _0204D4CC ; =UNK_021C5A68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	str r1, [r0, #0x8]
_0204D492:
	ldr r0, _0204D4CC ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r1, #0x48
	ldrb r0, [r1, r5]
	cmp r0, #0x0
	beq _0204D4A6
	cmp r6, #0x0
	bne _0204D4A6
	mov r0, #0x0
	strb r0, [r1, r5]
_0204D4A6:
	ldr r0, _0204D4CC ; =UNK_021C5A68
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204D4D4 ; =0x00000132
	cmp r6, #0x0
	strb r2, [r1, r0]
	bne _0204D4C8
	add r0, r5, #0x0
	bl FUN_0204ED9C
	ldr r0, _0204D4CC ; =UNK_021C5A68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0xfa
	strb r1, [r0, #0x0]
_0204D4C8:
	pop {r3-r7, pc}
	nop
_0204D4CC: .word UNK_021C5A68
_0204D4D0: .word 0x000002BE
_0204D4D4: .word 0x00000132

	thumb_func_start FUN_0204D4D8
FUN_0204D4D8: ; 0x0204D4D8
	ldr r1, _0204D4E8 ; =gMain
	mov r0, #0x2
	ldr r1, [r1, #0x44]
	tst r1, r0
	beq _0204D4E4
	mov r0, #0x1
_0204D4E4:
	ldr r3, _0204D4EC ; =FUN_02030F60
	bx r3
	.balign 4
_0204D4E8: .word gMain
_0204D4EC: .word FUN_02030F60

	thumb_func_start FUN_0204D4F0
FUN_0204D4F0: ; 0x0204D4F0
	push {r4-r6, lr}
	add r4, r1, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	beq _0204D530
	bl FUN_0204D4D8
	bl FUN_02031190
	cmp r0, #0x0
	bne _0204D524
	add r0, r4, #0x0
	bl FUN_0204D2B0
	add r0, r4, #0x0
	bl FUN_0204D248
	ldr r0, _0204D560 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0204D52A
	bl MOD18_02244D58
	b _0204D52A
_0204D524:
	add r0, r4, #0x0
	bl FUN_0204D248
_0204D52A:
	add r0, r4, #0x0
	bl FUN_0204D568
_0204D530:
	ldr r4, _0204D560 ; =UNK_021C5A68
	ldr r6, _0204D564 ; =0x000002BE
	mov r5, #0x0
_0204D536:
	ldr r0, [r4, #0x0]
	ldrb r0, [r0, r6]
	cmp r0, #0x0
	beq _0204D556
	bl FUN_02031190
	cmp r0, #0x0
	bne _0204D556
	add r0, r5, #0x0
	bl FUN_0202DFA4
	cmp r0, #0x0
	bne _0204D556
	add r0, r5, #0x0
	bl MOD18_02245358
_0204D556:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0204D536
	pop {r4-r6, pc}
	nop
_0204D560: .word UNK_021C5A68
_0204D564: .word 0x000002BE

	thumb_func_start FUN_0204D568
FUN_0204D568: ; 0x0204D568
	push {r3-r7, lr}
	ldr r4, _0204D608 ; =UNK_021C5A68
	ldr r7, _0204D60C ; =0x000002BE
	mov r5, #0x0
	add r6, sp, #0x0
_0204D572:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0204D5A0
	bl FUN_02031280
	cmp r0, #0x0
	beq _0204D58A
	cmp r5, #0x0
	beq _0204D5A0
_0204D58A:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0204D5A0
	ldr r0, [r4, #0x0]
	ldrb r0, [r0, r7]
	cmp r0, #0x0
	beq _0204D5A0
	add r0, r5, #0x0
	bl MOD18_02247614
_0204D5A0:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0204D5B8
	bl FUN_02031280
	cmp r0, #0x0
	beq _0204D5C6
	cmp r5, #0x0
	bne _0204D5C6
_0204D5B8:
	add r0, r5, #0x0
	bl FUN_0204DE30
	add r0, r5, #0x0
	bl FUN_0204EFCC
	b _0204D600
_0204D5C6:
	ldr r0, [r4, #0x0]
	add r0, r0, r5
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204D600
	bl FUN_02031190
	cmp r0, #0x0
	bne _0204D5F0
	ldr r1, [r4, #0x0]
	ldr r0, _0204D60C ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204D5F0
	add r0, r5, #0x0
	bl MOD18_0223EB8C
	add r0, r5, #0x0
	bl MOD18_0223CB08
_0204D5F0:
	strb r5, [r6, #0x0]
	ldr r3, [r4, #0x0]
	mov r0, #0x0
	ldr r3, [r3, #0x54]
	mov r1, #0x1
	add r2, sp, #0x0
	bl FUN_0204DBCC
_0204D600:
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0204D572
	pop {r3-r7, pc}
	.balign 4
_0204D608: .word UNK_021C5A68
_0204D60C: .word 0x000002BE

	thumb_func_start FUN_0204D610
FUN_0204D610: ; 0x0204D610
	ldr r0, _0204D624 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0204D620
	mov r0, #0xaf
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	bx lr
_0204D620:
	mov r0, #0x0
	bx lr
	.balign 4
_0204D624: .word UNK_021C5A68

	thumb_func_start FUN_0204D628
FUN_0204D628: ; 0x0204D628
	push {r3, lr}
	ldr r1, _0204D650 ; =UNK_021C5A68
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	beq _0204D64E
	mov r1, #0xaf
	lsl r1, r1, #0x2
	ldrb r2, [r3, r1]
	cmp r2, r0
	beq _0204D63E
	strb r0, [r3, r1]
_0204D63E:
	ldr r1, _0204D650 ; =UNK_021C5A68
	mov r0, #0x3e
	ldr r2, [r1, #0x0]
	mov r1, #0xaf
	lsl r1, r1, #0x2
	add r1, r2, r1
	bl FUN_020311D0
_0204D64E:
	pop {r3, pc}
	.balign 4
_0204D650: .word UNK_021C5A68

	thumb_func_start FUN_0204D654
FUN_0204D654: ; 0x0204D654
	push {r4, lr}
	ldr r2, _0204D678 ; =UNK_021C5A68
	ldr r4, [r2, #0x0]
	cmp r4, #0x0
	beq _0204D674
	mov r1, #0xaf
	lsl r1, r1, #0x2
	ldrb r3, [r4, r1]
	cmp r3, r0
	beq _0204D674
	strb r0, [r4, r1]
	ldr r2, [r2, #0x0]
	mov r0, #0x3e
	add r1, r2, r1
	bl FUN_020311D0
_0204D674:
	pop {r4, pc}
	nop
_0204D678: .word UNK_021C5A68

	thumb_func_start FUN_0204D67C
FUN_0204D67C: ; 0x0204D67C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0204D6BC ; =UNK_021C5A68
	add r4, r2, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204D6B8
	cmp r1, #0x1
	beq _0204D692
	bl GF_AssertFail
_0204D692:
	cmp r5, #0x8
	blt _0204D69A
	bl GF_AssertFail
_0204D69A:
	ldrb r0, [r4, #0x0]
	mov r1, #0x1
	cmp r0, #0x1
	beq _0204D6A8
	cmp r0, #0x0
	beq _0204D6A8
	mov r1, #0x0
_0204D6A8:
	cmp r1, #0x0
	bne _0204D6B0
	bl GF_AssertFail
_0204D6B0:
	ldrb r1, [r4, #0x0]
	add r0, r5, #0x0
	bl FUN_0204EAD8
_0204D6B8:
	pop {r3-r5, pc}
	nop
_0204D6BC: .word UNK_021C5A68

	thumb_func_start FUN_0204D6C0
FUN_0204D6C0: ; 0x0204D6C0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0204D734 ; =UNK_021C5A68
	add r4, r1, #0x0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0204D732
	ldr r0, _0204D738 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204D6E4
	add r0, r4, #0x0
	bl FUN_0204D654
	ldr r0, _0204D734 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204D73C ; =0x000002C1
	strb r4, [r1, r0]
_0204D6E4:
	ldr r4, [r5, #0x38]
	cmp r4, #0x0
	beq _0204D6F8
	bl FUN_02031190
	ldr r1, _0204D734 ; =UNK_021C5A68
	lsl r0, r0, #0x2
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	str r4, [r0, #0x8]
_0204D6F8:
	bl FUN_02030F40
	cmp r0, #0x0
	beq _0204D712
	bl FUN_02031190
	cmp r0, #0x0
	bne _0204D712
	ldr r1, _0204D734 ; =UNK_021C5A68
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_0204D89C
_0204D712:
	bl FUN_02030F40
	cmp r0, #0x0
	beq _0204D732
	bl FUN_02031190
	cmp r0, #0x0
	bne _0204D732
	ldr r0, _0204D734 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204D738 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204D732
	bl FUN_0204EC28
_0204D732:
	pop {r3-r5, pc}
	.balign 4
_0204D734: .word UNK_021C5A68
_0204D738: .word 0x000002BE
_0204D73C: .word 0x000002C1

	thumb_func_start FUN_0204D740
FUN_0204D740: ; 0x0204D740
	mov r0, #0x20
	tst r0, r1
	beq _0204D74A
	mov r0, #0x2
	bx lr
_0204D74A:
	mov r0, #0x10
	tst r0, r1
	beq _0204D754
	mov r0, #0x3
	bx lr
_0204D754:
	mov r0, #0x40
	tst r0, r1
	beq _0204D75E
	mov r0, #0x0
	bx lr
_0204D75E:
	mov r0, #0x80
	tst r1, r0
	beq _0204D768
	mov r0, #0x1
	bx lr
_0204D768:
	sub r0, #0x81
	bx lr

	thumb_func_start FUN_0204D76C
FUN_0204D76C: ; 0x0204D76C
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0204D7AC ; =UNK_021C5A68
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl FUN_02034B64
	add r4, r0, #0x0
	ldr r0, _0204D7AC ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl FUN_02034B6C
	mov r2, #0x0
	cmp r4, #0x0
	ble _0204D7A6
_0204D78E:
	ldrh r1, [r0, #0x18]
	cmp r5, r1
	bne _0204D79E
	ldrh r1, [r0, #0x1a]
	cmp r6, r1
	bne _0204D79E
	mov r0, #0x1
	pop {r4-r6, pc}
_0204D79E:
	add r2, r2, #0x1
	add r0, #0x20
	cmp r2, r4
	blt _0204D78E
_0204D7A6:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0204D7AC: .word UNK_021C5A68

	thumb_func_start FUN_0204D7B0
FUN_0204D7B0: ; 0x0204D7B0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0204D824 ; =0x0000FFFF
	add r6, r1, #0x0
	add r7, r2, #0x0
	cmp r5, r0
	beq _0204D812
	cmp r6, r0
	beq _0204D812
	mov r4, #0x0
_0204D7C4:
	cmp r4, r7
	beq _0204D7E0
	add r0, r4, #0x0
	bl FUN_0204E544
	cmp r5, r0
	bne _0204D7E0
	add r0, r4, #0x0
	bl FUN_0204E598
	cmp r6, r0
	bne _0204D7E0
	mov r0, #0x1
	pop {r3-r7, pc}
_0204D7E0:
	add r4, r4, #0x1
	cmp r4, #0x8
	blt _0204D7C4
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0204D76C
	cmp r0, #0x0
	beq _0204D7F6
	mov r0, #0x1
	pop {r3-r7, pc}
_0204D7F6:
	ldr r0, _0204D828 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204D82C ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204D812
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl MOD18_02246F1C
	cmp r0, #0x0
	bne _0204D812
	mov r0, #0x1
	pop {r3-r7, pc}
_0204D812:
	ldr r0, _0204D828 ; =UNK_021C5A68
	add r1, r5, #0x0
	ldr r0, [r0, #0x0]
	add r2, r6, #0x0
	ldr r0, [r0, #0x54]
	bl FUN_0204A6B4
	pop {r3-r7, pc}
	nop
_0204D824: .word 0x0000FFFF
_0204D828: .word UNK_021C5A68
_0204D82C: .word 0x000002BE

	thumb_func_start FUN_0204D830
FUN_0204D830: ; 0x0204D830
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, _0204D858 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0204D852
	bl MOD18_02244D40
	bl MOD18_02244DA0
	cmp r0, #0x0
	bne _0204D84E
	mov r0, #0x1
	pop {r3, pc}
_0204D84E:
	mov r0, #0x0
	pop {r3, pc}
_0204D852:
	mov r0, #0x0
	pop {r3, pc}
	nop
_0204D858: .word UNK_021C5A68

	thumb_func_start FUN_0204D85C
FUN_0204D85C: ; 0x0204D85C
	cmp r0, #0x5
	bge _0204D864
	mov r0, #0x8
	bx lr
_0204D864:
	cmp r0, #0xa
	bge _0204D86C
	mov r0, #0x4
	bx lr
_0204D86C:
	mov r0, #0x2
	bx lr

	thumb_func_start FUN_0204D870
FUN_0204D870: ; 0x0204D870
	push {r3-r4, lr}
	sub sp, #0x14
	ldr r3, _0204D898 ; =UNK_020F5824
	add r4, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x0
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	cmp r4, #0x5
	str r0, [r2, #0x0]
	blt _0204D88E
	bl GF_AssertFail
_0204D88E:
	lsl r1, r4, #0x2
	add r0, sp, #0x0
	ldr r0, [r0, r1]
	add sp, #0x14
	pop {r3-r4, pc}
	.balign 4
_0204D898: .word UNK_020F5824

	thumb_func_start FUN_0204D89C
FUN_0204D89C: ; 0x0204D89C
	push {r3-r7, lr}
	sub sp, #0x18
	mov r5, #0x0
	add r0, r5, #0x0
	ldr r6, _0204DAF4 ; =UNK_021C5A68
	str r5, [sp, #0x4]
	str r0, [sp, #0x0]
_0204D8AA:
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	add r1, #0x48
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204D976
	add r1, r0, r5
	add r1, #0xe2
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204D976
	add r1, r0, r5
	add r1, #0xea
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204D976
	add r2, r0, #0x0
	ldr r1, [sp, #0x0]
	add r2, #0x62
	ldr r0, [r0, #0x4]
	add r4, r2, r1
	cmp r0, #0x0
	beq _0204D8E0
	add r1, r5, #0x0
	bl MOD18_02244D40
	str r0, [sp, #0x4]
_0204D8E0:
	ldr r1, [r6, #0x0]
	ldr r0, _0204DAF8 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204D8F4
	add r0, r5, #0x0
	bl MOD18_02245F4C
	cmp r0, #0x0
	bne _0204D976
_0204D8F4:
	ldr r0, [r6, #0x0]
	ldr r1, _0204DAFC ; =0x0000013A
	add r0, r0, r5
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _0204D90A
	ldr r1, _0204DAFC ; =0x0000013A
	ldrb r1, [r0, r1]
	sub r2, r1, #0x1
	ldr r1, _0204DAFC ; =0x0000013A
	strb r2, [r0, r1]
_0204D90A:
	ldr r0, [r6, #0x0]
	ldr r1, _0204DAFC ; =0x0000013A
	add r2, r0, r5
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	bne _0204D93C
	ldr r1, _0204DAF8 ; =0x000002BE
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	beq _0204D93C
	add r0, r5, #0x0
	bl MOD18_0223F8D8
	cmp r0, #0x0
	bne _0204D976
	add r0, r5, #0x0
	bl FUN_0204D830
	cmp r0, #0x0
	bne _0204D93C
	add r0, r5, #0x0
	bl MOD18_02247544
	cmp r0, #0x0
	bne _0204D976
_0204D93C:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0204D94A
	bl MOD18_02244DB0
	cmp r0, #0x0
	beq _0204D976
_0204D94A:
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	add r0, #0xf2
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204D95A
	mov r7, #0x0
	b _0204D962
_0204D95A:
	add r0, r5, #0x0
	bl FUN_02030F88
	add r7, r0, #0x0
_0204D962:
	add r0, r5, #0x0
	bl FUN_02030F74
	strb r0, [r4, #0x5]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldr r0, _0204DAFC ; =0x0000013A
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204D978
_0204D976:
	b _0204DAE2
_0204D978:
	ldr r0, _0204DB00 ; =0x0000010A
	ldr r2, _0204DB04 ; =0x0000012A
	ldrb r0, [r1, r0]
	ldrb r1, [r1, r2]
	bl FUN_0204D85C
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_0204E084
	cmp r0, #0x0
	beq _0204D9A8
	ldr r0, [r6, #0x0]
	ldr r1, [sp, #0x10]
	add r2, r0, r5
	ldr r0, _0204DAFC ; =0x0000013A
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	add r2, r0, r5
	ldr r0, _0204DB08 ; =0x00000132
	strb r1, [r2, r0]
	b _0204DAE2
_0204D9A8:
	ldrb r0, [r4, #0x7]
	cmp r0, #0x1
	bne _0204D9B8
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	add r2, r0, r5
	ldr r0, _0204DB08 ; =0x00000132
	strb r1, [r2, r0]
_0204D9B8:
	mov r0, #0x0
	strb r0, [r4, #0x7]
	ldr r0, [r6, #0x0]
	ldr r1, _0204DB0C ; =0x00000122
	add r0, r0, r5
	ldrb r1, [r0, r1]
	cmp r1, #0x2
	bne _0204D9DE
	add r1, sp, #0x14
	strb r5, [r1, #0x1]
	ldr r1, _0204DB0C ; =0x00000122
	mov r2, #0x1
	strb r2, [r0, r1]
	add r1, sp, #0x14
	mov r0, #0x28
	add r1, #0x1
	bl FUN_02030C4C
	b _0204DAE2
_0204D9DE:
	add r0, r7, #0x0
	add r1, r7, #0x0
	bl FUN_0204D740
	add r7, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204E62C
	str r0, [sp, #0xc]
	add r0, r5, #0x0
	bl FUN_0204E664
	str r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldr r0, _0204DB10 ; =0x0000FFFF
	cmp r1, r0
	beq _0204DAE2
	ldr r1, [sp, #0x8]
	cmp r1, r0
	beq _0204DAE2
	mov r0, #0x0
	mvn r0, r0
	cmp r7, r0
	beq _0204DAE2
	mov r0, #0x4
	ldrsb r0, [r4, r0]
	cmp r0, r7
	beq _0204DA44
	strb r7, [r4, #0x4]
	ldr r0, [r6, #0x0]
	mov r1, #0x4
	add r2, r0, r5
	ldr r0, _0204DAFC ; =0x0000013A
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	add r2, r0, r5
	ldr r0, _0204DB08 ; =0x00000132
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	ldr r1, _0204DB0C ; =0x00000122
	add r0, r0, r5
	ldrb r1, [r0, r1]
	cmp r1, #0x2
	bls _0204DAE2
	ldr r1, _0204DB0C ; =0x00000122
	ldrb r1, [r0, r1]
	sub r2, r1, #0x1
	ldr r1, _0204DB0C ; =0x00000122
	strb r2, [r0, r1]
	b _0204DAE2
_0204DA44:
	ldr r0, [r6, #0x0]
	ldr r1, _0204DB0C ; =0x00000122
	add r2, r0, r5
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	bne _0204DAE2
	ldr r1, _0204DAF8 ; =0x000002BE
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	beq _0204DA66
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x8]
	add r0, r5, #0x0
	bl MOD18_0224566C
	cmp r0, #0x1
	beq _0204DAE2
_0204DA66:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x8]
	add r2, r5, #0x0
	bl FUN_0204D7B0
	cmp r0, #0x0
	beq _0204DA8E
	mov r0, #0x1
	strb r0, [r4, #0x7]
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	add r2, r0, r5
	ldr r0, _0204DB08 ; =0x00000132
	strb r1, [r2, r0]
	ldr r0, [r6, #0x0]
	mov r1, #0x4
	add r2, r0, r5
	ldr r0, _0204DAFC ; =0x0000013A
	strb r1, [r2, r0]
	b _0204DAE2
_0204DA8E:
	ldr r0, [r6, #0x0]
	mov r1, #0x1
	add r2, r0, r5
	ldr r0, _0204DB08 ; =0x00000132
	strb r1, [r2, r0]
	ldr r0, [sp, #0xc]
	strh r0, [r4, #0x0]
	ldr r0, [sp, #0x8]
	strh r0, [r4, #0x2]
	strb r7, [r4, #0x4]
	ldrb r0, [r4, #0x5]
	bl FUN_0204D870
	ldr r1, [r6, #0x0]
	add r2, r1, r5
	ldr r1, _0204DAFC ; =0x0000013A
	strb r0, [r2, r1]
	ldr r0, [r6, #0x0]
	sub r1, #0x20
	add r0, r0, r5
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	beq _0204DAE2
	ldr r1, _0204DB14 ; =0x0000011A
	ldrb r1, [r0, r1]
	sub r2, r1, #0x1
	ldr r1, _0204DB14 ; =0x0000011A
	strb r2, [r0, r1]
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldr r0, _0204DB14 ; =0x0000011A
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204DAE2
	mov r1, #0x1
	add r0, sp, #0x14
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r2, sp, #0x14
	mov r3, #0x0
	bl MOD18_0224089C
_0204DAE2:
	ldr r0, [sp, #0x0]
	add r5, r5, #0x1
	add r0, #0x8
	str r0, [sp, #0x0]
	cmp r5, #0x8
	bge _0204DAF0
	b _0204D8AA
_0204DAF0:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_0204DAF4: .word UNK_021C5A68
_0204DAF8: .word 0x000002BE
_0204DAFC: .word 0x0000013A
_0204DB00: .word 0x0000010A
_0204DB04: .word 0x0000012A
_0204DB08: .word 0x00000132
_0204DB0C: .word 0x00000122
_0204DB10: .word 0x0000FFFF
_0204DB14: .word 0x0000011A

	thumb_func_start FUN_0204DB18
FUN_0204DB18: ; 0x0204DB18
	push {r3-r7, lr}
	ldr r5, _0204DBC0 ; =UNK_021C5A68
	add r7, r0, #0x0
	ldr r0, [r5, #0x0]
	add r3, r2, #0x0
	cmp r0, #0x0
	beq _0204DBBC
	add r2, r0, #0x0
	ldrb r4, [r3, #0x4]
	add r2, #0x62
	lsl r1, r7, #0x3
	add r2, r2, r1
	mov r1, #0x80
	tst r1, r4
	beq _0204DB3E
	ldr r1, _0204DBC4 ; =0x000002BB
	mov r2, #0x1
	strb r2, [r0, r1]
	pop {r3-r7, pc}
_0204DB3E:
	mov r0, #0x4
	ldrsb r1, [r2, r0]
	sub r0, r0, #0x5
	cmp r1, r0
	bne _0204DB5A
	ldr r4, _0204DBC8 ; =0x00000132
	mov r1, #0x0
	mov r0, #0x1
_0204DB4E:
	ldr r6, [r5, #0x0]
	add r6, r6, r1
	add r1, r1, #0x1
	strb r0, [r6, r4]
	cmp r1, #0x8
	blt _0204DB4E
_0204DB5A:
	mov r0, #0x0
	strh r0, [r2, #0x0]
	strh r0, [r2, #0x2]
	ldrh r1, [r2, #0x0]
	ldrb r0, [r3, #0x0]
	add r0, r1, r0
	strh r0, [r2, #0x0]
	ldrb r1, [r3, #0x1]
	ldrh r0, [r2, #0x0]
	lsl r4, r1, #0x8
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r4, r1
	add r0, r0, r4
	strh r0, [r2, #0x0]
	ldrh r4, [r2, #0x2]
	ldrb r0, [r3, #0x2]
	add r0, r4, r0
	strh r0, [r2, #0x2]
	ldrb r4, [r3, #0x3]
	ldrh r0, [r2, #0x2]
	lsl r4, r4, #0x8
	and r1, r4
	add r0, r0, r1
	strh r0, [r2, #0x2]
	ldrb r1, [r3, #0x4]
	mov r0, #0xf
	ldr r3, _0204DBC0 ; =UNK_021C5A68
	and r0, r1
	strb r0, [r2, #0x4]
	ldr r1, [r3, #0x0]
	mov r0, #0x1
	add r1, r1, r7
	add r1, #0x48
	strb r0, [r1, #0x0]
	ldr r1, [r3, #0x0]
	add r4, r1, r7
	ldr r1, _0204DBC8 ; =0x00000132
	strb r0, [r4, r1]
	ldr r0, [r3, #0x0]
	ldrh r1, [r2, #0x0]
	ldrh r2, [r2, #0x2]
	ldr r0, [r0, #0x54]
	bl FUN_0204A6B4
	cmp r0, #0x0
	beq _0204DBBC
	bl GF_AssertFail
_0204DBBC:
	pop {r3-r7, pc}
	nop
_0204DBC0: .word UNK_021C5A68
_0204DBC4: .word 0x000002BB
_0204DBC8: .word 0x00000132

	thumb_func_start FUN_0204DBCC
FUN_0204DBCC: ; 0x0204DBCC
	push {r3-r5, lr}
	ldr r0, _0204DC28 ; =UNK_021C5A68
	ldrb r4, [r2, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204DC24
	bl FUN_02031190
	cmp r4, r0
	beq _0204DC24
	ldr r0, _0204DC28 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204DC2C ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204DC14
	add r0, r4, #0x0
	bl MOD18_0223E554
	ldr r0, _0204DC28 ; =UNK_021C5A68
	ldr r3, [r0, #0x0]
	ldr r0, _0204DC30 ; =0x000002BD
	ldrb r0, [r3, r0]
	cmp r0, #0x0
	bne _0204DC14
	lsl r5, r4, #0x3
	add r1, r3, r5
	ldr r0, [r3, #0x54]
	add r3, r3, r5
	add r1, #0xa2
	add r3, #0xa4
	ldrh r1, [r1, #0x0]
	ldrh r3, [r3, #0x0]
	mov r2, #0x0
	bl MOD05_021E5B30
_0204DC14:
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl FUN_0204D43C
	add r0, r4, #0x0
	bl FUN_0202DE78
_0204DC24:
	pop {r3-r5, pc}
	nop
_0204DC28: .word UNK_021C5A68
_0204DC2C: .word 0x000002BE
_0204DC30: .word 0x000002BD

	thumb_func_start FUN_0204DC34
FUN_0204DC34: ; 0x0204DC34
	mov r0, #0x5
	bx lr

	thumb_func_start FUN_0204DC38
FUN_0204DC38: ; 0x0204DC38
	push {r3-r5, lr}
	ldrb r1, [r2, #0x0]
	mov r0, #0xf
	add r3, r1, #0x0
	and r3, r0
	ldr r0, _0204DCB0 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0204DCAC
	ldrb r4, [r2, #0x2]
	add r1, #0xa2
	lsl r0, r3, #0x3
	add r1, r1, r0
	mov r0, #0x80
	tst r0, r4
	beq _0204DC5C
	mov r0, #0x1
	b _0204DC5E
_0204DC5C:
	mov r0, #0x0
_0204DC5E:
	strb r0, [r1, #0x7]
	mov r0, #0x0
	strh r0, [r1, #0x0]
	strh r0, [r1, #0x2]
	ldrh r4, [r1, #0x0]
	ldrb r0, [r2, #0x1]
	add r0, r4, r0
	strh r0, [r1, #0x0]
	ldrb r4, [r2, #0x2]
	ldrh r0, [r1, #0x0]
	lsl r5, r4, #0x8
	mov r4, #0x1
	lsl r4, r4, #0x8
	and r5, r4
	add r0, r0, r5
	strh r0, [r1, #0x0]
	ldrh r5, [r1, #0x2]
	ldrb r0, [r2, #0x3]
	add r0, r5, r0
	strh r0, [r1, #0x2]
	ldrb r5, [r2, #0x2]
	ldrh r0, [r1, #0x2]
	lsl r5, r5, #0x7
	and r4, r5
	add r0, r0, r4
	strh r0, [r1, #0x2]
	ldrb r0, [r2, #0x0]
	asr r4, r0, #0x4
	mov r0, #0x3
	and r4, r0
	strb r4, [r1, #0x4]
	ldrb r2, [r2, #0x0]
	asr r2, r2, #0x6
	and r0, r2
	strb r0, [r1, #0x5]
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	bl FUN_0204D328
_0204DCAC:
	pop {r3-r5, pc}
	nop
_0204DCB0: .word UNK_021C5A68

	thumb_func_start FUN_0204DCB4
FUN_0204DCB4: ; 0x0204DCB4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0204DD10 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r4, r0, #0x0
	ldr r0, _0204DD10 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	ldr r0, _0204DD10 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204DD14 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204DD0C
	bl FUN_02031190
	cmp r5, r0
	bne _0204DD0C
	add r0, r4, #0x0
	bl FUN_020266B0
	add r0, r4, #0x0
	bl FUN_020266C8
	cmp r0, #0x32
	bne _0204DD0C
	ldr r0, _0204DD10 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x25
	bl FUN_0202A170
_0204DD0C:
	pop {r3-r5, pc}
	nop
_0204DD10: .word UNK_021C5A68
_0204DD14: .word 0x000002BE

	thumb_func_start FUN_0204DD18
FUN_0204DD18: ; 0x0204DD18
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r4, _0204DE24 ; =UNK_020F5808
	add r6, r3, #0x0
	add r5, r0, #0x0
	add r3, sp, #0x4
	mov r2, #0xc
_0204DD26:
	ldrb r0, [r4, #0x0]
	add r4, r4, #0x1
	strb r0, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _0204DD26
	ldr r0, _0204DE28 ; =UNK_021C5A68
	ldr r2, _0204DE2C ; =0x00000102
	ldr r0, [r0, #0x0]
	add r3, r0, r5
	ldrsb r3, [r3, r2]
	mov r2, #0x0
	mvn r2, r2
	cmp r3, r2
	beq _0204DD4E
	lsl r7, r5, #0x2
	add r0, r0, r7
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	bne _0204DD54
_0204DD4E:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_0204DD54:
	cmp r1, #0x0
	bne _0204DD5E
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_0204DD5E:
	bl FUN_020553A0
	add r4, r0, #0x0
	ldr r0, _0204DE28 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r7, #0x0
	add r0, r1, r0
	ldr r0, [r0, #0x8]
	bl FUN_020552F8
	str r0, [sp, #0x0]
	ldr r0, _0204DE28 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204DE2C ; =0x00000102
	ldrsb r0, [r1, r0]
	bl FUN_0204F610
	ldr r1, [sp, #0x0]
	cmp r1, r0
	beq _0204DDB4
	add r0, r4, #0x0
	mov r1, #0x80
	bl FUN_02058418
	ldr r0, _0204DE28 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204DE2C ; =0x00000102
	ldrsb r0, [r1, r0]
	bl FUN_0204F610
	add r1, r0, #0x0
	ldr r0, _0204DE28 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r0, r0, r7
	ldr r0, [r0, #0x8]
	bl FUN_02055304
	add r0, r4, #0x0
	mov r1, #0x80
	bl FUN_02058410
_0204DDB4:
	add r0, r4, #0x0
	bl FUN_0205AE28
	add r0, r4, #0x0
	bl FUN_0205AD98
	cmp r0, #0x1
	bne _0204DE1C
	add r0, r5, #0x0
	bl FUN_0204DCB4
	cmp r6, #0x0
	beq _0204DDD8
	cmp r6, #0x1
	beq _0204DDEE
	cmp r6, #0x2
	beq _0204DE06
	b _0204DE1C
_0204DDD8:
	ldr r1, _0204DE28 ; =UNK_021C5A68
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r2, r1, r5
	ldr r1, _0204DE2C ; =0x00000102
	ldrsb r2, [r2, r1]
	add r1, sp, #0x4
	ldrb r1, [r1, r2]
	bl FUN_0205ADDC
	b _0204DE1C
_0204DDEE:
	ldr r1, _0204DE28 ; =UNK_021C5A68
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r2, r1, r5
	ldr r1, _0204DE2C ; =0x00000102
	ldrsb r1, [r2, r1]
	add r2, r1, #0x4
	add r1, sp, #0x4
	ldrb r1, [r1, r2]
	bl FUN_0205ADDC
	b _0204DE1C
_0204DE06:
	ldr r1, _0204DE28 ; =UNK_021C5A68
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	add r2, r1, r5
	ldr r1, _0204DE2C ; =0x00000102
	ldrsb r2, [r2, r1]
	add r1, sp, #0x4
	add r2, #0x8
	ldrb r1, [r1, r2]
	bl FUN_0205ADDC
_0204DE1C:
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0204DE24: .word UNK_020F5808
_0204DE28: .word UNK_021C5A68
_0204DE2C: .word 0x00000102

	thumb_func_start FUN_0204DE30
FUN_0204DE30: ; 0x0204DE30
	push {r4-r7, lr}
	sub sp, #0x1c
	add r4, r0, #0x0
	ldr r0, _0204E06C ; =UNK_021C5A68
	lsl r1, r4, #0x3
	ldr r0, [r0, #0x0]
	add r2, r0, #0x0
	add r2, #0xa2
	add r5, r2, r1
	ldr r1, _0204E070 ; =0x00000142
	add r2, r0, r1
	ldrb r1, [r2, r4]
	cmp r1, #0x0
	beq _0204DE54
	sub r0, r1, #0x1
	add sp, #0x1c
	strb r0, [r2, r4]
	pop {r4-r7, pc}
_0204DE54:
	ldrh r2, [r5, #0x0]
	ldr r1, _0204E074 ; =0x0000FFFF
	cmp r2, r1
	beq _0204DF08
	ldrh r2, [r5, #0x2]
	cmp r2, r1
	beq _0204DF08
	ldr r1, _0204E078 ; =0x000002BD
	ldrb r2, [r0, r1]
	cmp r2, #0x0
	bne _0204DF08
	add r1, r1, #0x1
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _0204DE86
	bl FUN_02031190
	cmp r4, r0
	bne _0204DE86
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E07C ; =0x000002C1
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204DF08
_0204DE86:
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r1, r0
	ldr r0, [r0, #0x8]
	str r0, [sp, #0x18]
	cmp r0, #0x0
	bne _0204DE98
	b _0204E068
_0204DE98:
	bl FUN_02055320
	ldrh r1, [r5, #0x0]
	sub r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x18]
	bl FUN_0205532C
	ldrh r1, [r5, #0x2]
	sub r7, r0, r1
	ldr r0, [sp, #0x18]
	bl FUN_020552F8
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _0204DEC2
	cmp r7, #0x0
	bne _0204DEC2
	mov r6, #0x0
	b _0204DEEC
_0204DEC2:
	ldr r0, [sp, #0x10]
	bl abs
	add r6, r0, #0x0
	add r0, r7, #0x0
	bl abs
	cmp r6, r0
	ble _0204DEE2
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	ble _0204DEDE
	mov r6, #0x20
	b _0204DEEC
_0204DEDE:
	mov r6, #0x10
	b _0204DEEC
_0204DEE2:
	cmp r7, #0x0
	ble _0204DEEA
	mov r6, #0x40
	b _0204DEEC
_0204DEEA:
	mov r6, #0x80
_0204DEEC:
	add r0, r7, #0x0
	bl abs
	ldr r0, [sp, #0x10]
	bl abs
	ldrb r3, [r5, #0x5]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r2, r6, #0x0
	bl FUN_0204DD18
	cmp r0, #0x0
	beq _0204DF0A
_0204DF08:
	b _0204E068
_0204DF0A:
	ldrb r0, [r5, #0x5]
	mov r7, #0xff
	str r0, [sp, #0x14]
	cmp r0, #0x3
	bhi _0204DF46
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204DF20: ; jump table (using 16-bit offset)
	.short _0204DF28 - _0204DF20 - 2; case 0
	.short _0204DF2E - _0204DF20 - 2; case 1
	.short _0204DF3C - _0204DF20 - 2; case 2
	.short _0204DF42 - _0204DF20 - 2; case 3
_0204DF28:
	mov r0, #0x5
	str r0, [sp, #0x8]
	b _0204DF46
_0204DF2E:
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x2
	orr r0, r6
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	b _0204DF46
_0204DF3C:
	mov r0, #0x2
	str r0, [sp, #0x8]
	b _0204DF46
_0204DF42:
	mov r0, #0x1
	str r0, [sp, #0x8]
_0204DF46:
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204DF6C
	bl FUN_02031190
	cmp r4, r0
	bne _0204DF6C
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	mov r0, #0xb
	lsl r0, r0, #0x6
	ldrb r1, [r2, r0]
	sub r1, r1, #0x1
	strb r1, [r2, r0]
	b _0204E00C
_0204DF6C:
	bl FUN_02030FE0
	cmp r0, #0x0
	bne _0204DFA0
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E080 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204DFA0
	bl FUN_02031190
	cmp r4, r0
	bne _0204DFA0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x18]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	add r2, r6, #0x0
	bl FUN_02057194
	add r7, r0, #0x0
	b _0204E00C
_0204DFA0:
	mov r0, #0x2
	add r1, r6, #0x0
	bic r1, r0
	bne _0204DFDE
	ldrb r0, [r5, #0x7]
	cmp r0, #0x0
	beq _0204DFDE
	mov r0, #0x3
	str r0, [sp, #0x14]
	mov r0, #0x4
	ldrsb r0, [r5, r0]
	cmp r0, #0x3
	bhi _0204DFD2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0204DFC6: ; jump table (using 16-bit offset)
	.short _0204DFCE - _0204DFC6 - 2; case 0
	.short _0204DFD2 - _0204DFC6 - 2; case 1
	.short _0204DFD6 - _0204DFC6 - 2; case 2
	.short _0204DFDA - _0204DFC6 - 2; case 3
_0204DFCE:
	mov r7, #0x1c
	b _0204E00C
_0204DFD2:
	mov r7, #0x1d
	b _0204E00C
_0204DFD6:
	mov r7, #0x1e
	b _0204E00C
_0204DFDA:
	mov r7, #0x1f
	b _0204E00C
_0204DFDE:
	cmp r1, #0x0
	bne _0204DFF6
	mov r0, #0x4
	ldrsb r0, [r5, r0]
	ldr r1, [sp, #0xc]
	cmp r0, r1
	beq _0204DFF6
	mov r1, #0x24
	bl FUN_0205AFDC
	add r7, r0, #0x0
	b _0204E00C
_0204DFF6:
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x18]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	add r2, r6, #0x0
	bl FUN_02057194
	add r7, r0, #0x0
_0204E00C:
	ldr r0, [sp, #0x18]
	bl FUN_02057254
	cmp r0, #0x0
	bne _0204E020
	ldr r0, [sp, #0x18]
	bl FUN_020570C4
	cmp r0, #0x0
	beq _0204E068
_0204E020:
	cmp r7, #0xff
	beq _0204E068
	ldr r0, [sp, #0x18]
	add r1, r7, #0x0
	bl FUN_02057260
	mov r0, #0x2
	bic r6, r0
	beq _0204E068
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	ldr r0, _0204E070 ; =0x00000142
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204E050
	ldr r0, [sp, #0x14]
	bl FUN_0204D870
	ldr r1, _0204E06C ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r2, r1, r4
	ldr r1, _0204E070 ; =0x00000142
	strb r0, [r2, r1]
_0204E050:
	ldr r0, _0204E06C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E070 ; =0x00000142
	add r1, r1, r0
	ldrb r0, [r1, r4]
	cmp r0, #0x0
	beq _0204E062
	sub r0, r0, #0x1
	strb r0, [r1, r4]
_0204E062:
	add r0, r4, #0x0
	bl FUN_0204DCB4
_0204E068:
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4
_0204E06C: .word UNK_021C5A68
_0204E070: .word 0x00000142
_0204E074: .word 0x0000FFFF
_0204E078: .word 0x000002BD
_0204E07C: .word 0x000002C1
_0204E080: .word 0x000002BE

	thumb_func_start FUN_0204E084
FUN_0204E084: ; 0x0204E084
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	ldr r1, _0204E16C ; =UNK_021C5A68
	add r5, r0, #0x0
	ldr r2, [r1, #0x0]
	ldr r1, _0204E170 ; =0x0000010A
	add r2, r2, r1
	ldrb r1, [r2, r5]
	cmp r1, #0x0
	bne _0204E0A0
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0204E0A0:
	cmp r1, #0xff
	bne _0204E0AA
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204E0AA:
	sub r1, r1, #0x1
	strb r1, [r2, r5]
	cmp r4, #0x1
	bne _0204E0B8
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204E0B8:
	bl FUN_0204E544
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0204E598
	str r0, [sp, #0x0]
	ldr r0, _0204E16C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204E174 ; =0x00000112
	ldrb r0, [r1, r0]
	bl FUN_02059BF4
	add r7, r6, r0
	ldr r0, _0204E16C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204E174 ; =0x00000112
	ldrb r0, [r1, r0]
	bl FUN_02059C00
	ldr r1, [sp, #0x0]
	add r6, r1, r0
	ldr r0, _0204E16C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204E170 ; =0x0000010A
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204E110
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_0204D7B0
	cmp r0, #0x0
	beq _0204E110
	ldr r1, _0204E16C ; =UNK_021C5A68
	mov r0, #0x1
	ldr r1, [r1, #0x0]
	add r2, r1, r5
	ldr r1, _0204E170 ; =0x0000010A
	strb r0, [r2, r1]
_0204E110:
	ldr r0, _0204E16C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E170 ; =0x0000010A
	add r2, r1, r5
	ldrb r0, [r2, r0]
	cmp r0, #0x1
	bne _0204E124
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204E124:
	cmp r0, #0x0
	bne _0204E13E
	mov r1, #0x1
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	add r2, sp, #0x4
	mov r3, #0x0
	bl MOD18_0224089C
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_0204E13E:
	add r1, #0x62
	lsl r2, r5, #0x3
	add r0, r1, r2
	strh r7, [r1, r2]
	strh r6, [r0, #0x2]
	cmp r4, #0x2
	beq _0204E156
	cmp r4, #0x4
	beq _0204E15C
	cmp r4, #0x8
	beq _0204E162
	b _0204E166
_0204E156:
	mov r1, #0x0
	strb r1, [r0, #0x5]
	b _0204E166
_0204E15C:
	mov r1, #0x1
	strb r1, [r0, #0x5]
	b _0204E166
_0204E162:
	mov r1, #0x2
	strb r1, [r0, #0x5]
_0204E166:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0204E16C: .word UNK_021C5A68
_0204E170: .word 0x0000010A
_0204E174: .word 0x00000112

	thumb_func_start FUN_0204E178
FUN_0204E178: ; 0x0204E178
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0204E1DC ; =UNK_021C5A68
	add r4, r1, #0x0
	ldr r1, [r0, #0x0]
	lsl r0, r5, #0x3
	add r1, #0x62
	add r6, r1, r0
	add r0, r4, #0x0
	add r7, r2, #0x0
	bl FUN_0204F610
	ldr r1, _0204E1DC ; =UNK_021C5A68
	strb r0, [r6, #0x4]
	ldr r0, [r1, #0x0]
	add r2, r0, r5
	ldr r0, _0204E1E0 ; =0x00000112
	cmp r7, #0x0
	strb r4, [r2, r0]
	beq _0204E1B6
	ldr r2, [r1, #0x0]
	mov r3, #0x1
	add r2, r2, r5
	add r0, #0x18
	strb r3, [r2, r0]
	ldr r0, [r1, #0x0]
	mov r2, #0x2d
	add r1, r0, r5
	add r0, r2, #0x0
	add r0, #0xdd
	b _0204E1CA
_0204E1B6:
	ldr r2, [r1, #0x0]
	mov r3, #0x0
	add r2, r2, r5
	add r0, #0x18
	strb r3, [r2, r0]
	ldr r0, [r1, #0x0]
	mov r2, #0x1b
	add r1, r0, r5
	add r0, r2, #0x0
	add r0, #0xef
_0204E1CA:
	strb r2, [r1, r0]
	ldr r0, _0204E1DC ; =UNK_021C5A68
	mov r2, #0x1
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204E1E4 ; =0x00000132
	strb r2, [r1, r0]
	pop {r3-r7, pc}
	nop
_0204E1DC: .word UNK_021C5A68
_0204E1E0: .word 0x00000112
_0204E1E4: .word 0x00000132

	thumb_func_start FUN_0204E1E8
FUN_0204E1E8: ; 0x0204E1E8
	ldr r1, _0204E1F8 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	ldr r0, _0204E1FC ; =0x0000010A
	strb r2, [r1, r0]
	bx lr
	nop
_0204E1F8: .word UNK_021C5A68
_0204E1FC: .word 0x0000010A

	thumb_func_start FUN_0204E200
FUN_0204E200: ; 0x0204E200
	ldr r1, _0204E210 ; =UNK_021C5A68
	mov r2, #0xff
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	add r0, r2, #0x0
	add r0, #0xb
	strb r2, [r1, r0]
	bx lr
	.balign 4
_0204E210: .word UNK_021C5A68

	thumb_func_start FUN_0204E214
FUN_0204E214: ; 0x0204E214
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _0204E24C ; =UNK_021C5A68
	add r4, r1, #0x0
	ldr r1, [r0, #0x0]
	lsl r0, r5, #0x2
	add r0, r1, r0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204E248
	bl FUN_020553A0
	mov r1, #0x80
	add r6, r0, #0x0
	bl FUN_02058410
	mov r1, #0x1
	add r0, r6, #0x0
	lsl r1, r1, #0x8
	bl FUN_02058410
	ldr r0, _0204E24C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r5
	ldr r0, _0204E250 ; =0x00000102
	strb r4, [r1, r0]
_0204E248:
	pop {r4-r6, pc}
	nop
_0204E24C: .word UNK_021C5A68
_0204E250: .word 0x00000102

	thumb_func_start FUN_0204E254
FUN_0204E254: ; 0x0204E254
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r0, _0204E2A0 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r1, r0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204E29E
	add r2, r1, r4
	ldr r1, _0204E2A4 ; =0x00000102
	ldrsb r2, [r2, r1]
	mov r1, #0x0
	mvn r1, r1
	cmp r2, r1
	beq _0204E29E
	bl FUN_020553A0
	add r5, r0, #0x0
	bl FUN_0205AE50
	add r0, r5, #0x0
	mov r1, #0x80
	bl FUN_02058418
	mov r1, #0x1
	add r0, r5, #0x0
	lsl r1, r1, #0x8
	bl FUN_02058418
	ldr r0, _0204E2A0 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r0, [r0, #0x0]
	mvn r2, r2
	add r1, r0, r4
	ldr r0, _0204E2A4 ; =0x00000102
	strb r2, [r1, r0]
_0204E29E:
	pop {r3-r5, pc}
	.balign 4
_0204E2A0: .word UNK_021C5A68
_0204E2A4: .word 0x00000102

	thumb_func_start FUN_0204E2A8
FUN_0204E2A8: ; 0x0204E2A8
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_0204E2AC
FUN_0204E2AC: ; 0x0204E2AC
	ldr r3, _0204E2B0 ; =FUN_0204F7FC
	bx r3
	.balign 4
_0204E2B0: .word FUN_0204F7FC

	thumb_func_start FUN_0204E2B4
FUN_0204E2B4: ; 0x0204E2B4
	ldr r3, _0204E2B8 ; =FUN_0204F7FC
	bx r3
	.balign 4
_0204E2B8: .word FUN_0204F7FC

	thumb_func_start FUN_0204E2BC
FUN_0204E2BC: ; 0x0204E2BC
	ldr r3, _0204E2C4 ; =FUN_0204F774
	mov r0, #0x2
	bx r3
	nop
_0204E2C4: .word FUN_0204F774

	thumb_func_start FUN_0204E2C8
FUN_0204E2C8: ; 0x0204E2C8
	ldr r3, _0204E2D0 ; =FUN_0204F774
	mov r0, #0x20
	bx r3
	nop
_0204E2D0: .word FUN_0204F774

	thumb_func_start FUN_0204E2D4
FUN_0204E2D4: ; 0x0204E2D4
	ldr r3, _0204E2DC ; =FUN_0204F774
	mov r0, #0x1
	bx r3
	nop
_0204E2DC: .word FUN_0204F774

	thumb_func_start FUN_0204E2E0
FUN_0204E2E0: ; 0x0204E2E0
	push {r3, lr}
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	mov r0, #0x1a
	add r1, sp, #0x0
	bl FUN_02030C4C
	pop {r3, pc}

	thumb_func_start FUN_0204E2F0
FUN_0204E2F0: ; 0x0204E2F0
	ldr r3, _0204E2F8 ; =MOD18_0223E4BC
	ldrb r0, [r2, #0x0]
	bx r3
	nop
_0204E2F8: .word MOD18_0223E4BC

	thumb_func_start FUN_0204E2FC
FUN_0204E2FC: ; 0x0204E2FC
	push {r3, lr}
	bl FUN_02031280
	cmp r0, #0x0
	beq _0204E30A
	mov r0, #0x1
	pop {r3, pc}
_0204E30A:
	ldr r0, _0204E344 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E316
	mov r0, #0x0
	pop {r3, pc}
_0204E316:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0204E326
	mov r0, #0x0
	pop {r3, pc}
_0204E326:
	ldr r0, _0204E344 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E348 ; =0x000002BE
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204E33E
	bl FUN_0204FE5C
	cmp r0, #0x0
	bne _0204E33E
	mov r0, #0x0
	pop {r3, pc}
_0204E33E:
	mov r0, #0x1
	pop {r3, pc}
	nop
_0204E344: .word UNK_021C5A68
_0204E348: .word 0x000002BE

	thumb_func_start FUN_0204E34C
FUN_0204E34C: ; 0x0204E34C
	ldr r1, _0204E358 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4
_0204E358: .word UNK_021C5A68

	thumb_func_start FUN_0204E35C
FUN_0204E35C: ; 0x0204E35C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204E39C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E36C
	ldr r0, _0204E3A0 ; =0x0000FFFF
	pop {r4, pc}
_0204E36C:
	bl FUN_02031190
	cmp r4, r0
	bne _0204E382
	ldr r0, _0204E39C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa2
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E382:
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E398
	ldr r0, _0204E39C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa2
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E398:
	ldr r0, _0204E3A0 ; =0x0000FFFF
	pop {r4, pc}
	.balign 4
_0204E39C: .word UNK_021C5A68
_0204E3A0: .word 0x0000FFFF

	thumb_func_start FUN_0204E3A4
FUN_0204E3A4: ; 0x0204E3A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204E3E4 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E3B4
	ldr r0, _0204E3E8 ; =0x0000FFFF
	pop {r4, pc}
_0204E3B4:
	bl FUN_02031190
	cmp r4, r0
	bne _0204E3CA
	ldr r0, _0204E3E4 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa4
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E3CA:
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E3E0
	ldr r0, _0204E3E4 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa4
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E3E0:
	ldr r0, _0204E3E8 ; =0x0000FFFF
	pop {r4, pc}
	.balign 4
_0204E3E4: .word UNK_021C5A68
_0204E3E8: .word 0x0000FFFF

	thumb_func_start FUN_0204E3EC
FUN_0204E3EC: ; 0x0204E3EC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204E438 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E3FC
	ldr r0, _0204E43C ; =0x0000FFFF
	pop {r4, pc}
_0204E3FC:
	bl FUN_02031190
	cmp r4, r0
	bne _0204E412
	ldr r0, _0204E438 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa2
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E412:
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E428
	ldr r0, _0204E438 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E42C
_0204E428:
	ldr r0, _0204E43C ; =0x0000FFFF
	pop {r4, pc}
_0204E42C:
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa2
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
	nop
_0204E438: .word UNK_021C5A68
_0204E43C: .word 0x0000FFFF

	thumb_func_start FUN_0204E440
FUN_0204E440: ; 0x0204E440
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204E48C ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E450
	ldr r0, _0204E490 ; =0x0000FFFF
	pop {r4, pc}
_0204E450:
	bl FUN_02031190
	cmp r4, r0
	bne _0204E466
	ldr r0, _0204E48C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa4
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E466:
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E47C
	ldr r0, _0204E48C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E480
_0204E47C:
	ldr r0, _0204E490 ; =0x0000FFFF
	pop {r4, pc}
_0204E480:
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0xa4
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
	nop
_0204E48C: .word UNK_021C5A68
_0204E490: .word 0x0000FFFF

	thumb_func_start FUN_0204E494
FUN_0204E494: ; 0x0204E494
	ldr r1, _0204E4AC ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204E4A6
	lsl r0, r0, #0x3
	add r0, r1, r0
	add r0, #0xa2
	ldrh r0, [r0, #0x0]
	bx lr
_0204E4A6:
	ldr r0, _0204E4B0 ; =0x0000FFFF
	bx lr
	nop
_0204E4AC: .word UNK_021C5A68
_0204E4B0: .word 0x0000FFFF

	thumb_func_start FUN_0204E4B4
FUN_0204E4B4: ; 0x0204E4B4
	ldr r1, _0204E4CC ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204E4C6
	lsl r0, r0, #0x3
	add r0, r1, r0
	add r0, #0xa4
	ldrh r0, [r0, #0x0]
	bx lr
_0204E4C6:
	ldr r0, _0204E4D0 ; =0x0000FFFF
	bx lr
	nop
_0204E4CC: .word UNK_021C5A68
_0204E4D0: .word 0x0000FFFF

	thumb_func_start FUN_0204E4D4
FUN_0204E4D4: ; 0x0204E4D4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204E3EC
	ldr r1, _0204E504 ; =0x0000FFFF
	cmp r0, r1
	bne _0204E4E6
	add r0, r1, #0x0
	pop {r4, pc}
_0204E4E6:
	ldr r0, _0204E508 ; =UNK_021C5A68
	lsl r4, r4, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xa6
	ldrsb r0, [r1, r0]
	bl FUN_02059BF4
	ldr r1, _0204E508 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0xa2
	ldrh r1, [r1, #0x0]
	add r0, r1, r0
	pop {r4, pc}
	.balign 4
_0204E504: .word 0x0000FFFF
_0204E508: .word UNK_021C5A68

	thumb_func_start FUN_0204E50C
FUN_0204E50C: ; 0x0204E50C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204E440
	ldr r1, _0204E53C ; =0x0000FFFF
	cmp r0, r1
	bne _0204E51E
	add r0, r1, #0x0
	pop {r4, pc}
_0204E51E:
	ldr r0, _0204E540 ; =UNK_021C5A68
	lsl r4, r4, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0xa6
	ldrsb r0, [r1, r0]
	bl FUN_02059C00
	ldr r1, _0204E540 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0xa4
	ldrh r1, [r1, #0x0]
	add r0, r1, r0
	pop {r4, pc}
	.balign 4
_0204E53C: .word 0x0000FFFF
_0204E540: .word UNK_021C5A68

	thumb_func_start FUN_0204E544
FUN_0204E544: ; 0x0204E544
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204E590 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E554
	ldr r0, _0204E594 ; =0x0000FFFF
	pop {r4, pc}
_0204E554:
	bl FUN_02031190
	cmp r4, r0
	bne _0204E56A
	ldr r0, _0204E590 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0x62
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E56A:
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E580
	ldr r0, _0204E590 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E584
_0204E580:
	ldr r0, _0204E594 ; =0x0000FFFF
	pop {r4, pc}
_0204E584:
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0x62
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
	nop
_0204E590: .word UNK_021C5A68
_0204E594: .word 0x0000FFFF

	thumb_func_start FUN_0204E598
FUN_0204E598: ; 0x0204E598
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204E5E4 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E5A8
	ldr r0, _0204E5E8 ; =0x0000FFFF
	pop {r4, pc}
_0204E5A8:
	bl FUN_02031190
	cmp r4, r0
	bne _0204E5BE
	ldr r0, _0204E5E4 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0x64
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
_0204E5BE:
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E5D4
	ldr r0, _0204E5E4 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E5D8
_0204E5D4:
	ldr r0, _0204E5E8 ; =0x0000FFFF
	pop {r4, pc}
_0204E5D8:
	lsl r0, r4, #0x3
	add r0, r1, r0
	add r0, #0x64
	ldrh r0, [r0, #0x0]
	pop {r4, pc}
	nop
_0204E5E4: .word UNK_021C5A68
_0204E5E8: .word 0x0000FFFF

	thumb_func_start FUN_0204E5EC
FUN_0204E5EC: ; 0x0204E5EC
	ldr r1, _0204E604 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204E5FE
	lsl r0, r0, #0x3
	add r0, r1, r0
	add r0, #0x62
	ldrh r0, [r0, #0x0]
	bx lr
_0204E5FE:
	ldr r0, _0204E608 ; =0x0000FFFF
	bx lr
	nop
_0204E604: .word UNK_021C5A68
_0204E608: .word 0x0000FFFF

	thumb_func_start FUN_0204E60C
FUN_0204E60C: ; 0x0204E60C
	ldr r1, _0204E624 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204E61E
	lsl r0, r0, #0x3
	add r0, r1, r0
	add r0, #0x64
	ldrh r0, [r0, #0x0]
	bx lr
_0204E61E:
	ldr r0, _0204E628 ; =0x0000FFFF
	bx lr
	nop
_0204E624: .word UNK_021C5A68
_0204E628: .word 0x0000FFFF

	thumb_func_start FUN_0204E62C
FUN_0204E62C: ; 0x0204E62C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204E544
	ldr r1, _0204E65C ; =0x0000FFFF
	cmp r0, r1
	bne _0204E63E
	add r0, r1, #0x0
	pop {r4, pc}
_0204E63E:
	ldr r0, _0204E660 ; =UNK_021C5A68
	lsl r4, r4, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0x66
	ldrsb r0, [r1, r0]
	bl FUN_02059BF4
	ldr r1, _0204E660 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0x62
	ldrh r1, [r1, #0x0]
	add r0, r1, r0
	pop {r4, pc}
	.balign 4
_0204E65C: .word 0x0000FFFF
_0204E660: .word UNK_021C5A68

	thumb_func_start FUN_0204E664
FUN_0204E664: ; 0x0204E664
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204E598
	ldr r1, _0204E694 ; =0x0000FFFF
	cmp r0, r1
	bne _0204E676
	add r0, r1, #0x0
	pop {r4, pc}
_0204E676:
	ldr r0, _0204E698 ; =UNK_021C5A68
	lsl r4, r4, #0x3
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	mov r0, #0x66
	ldrsb r0, [r1, r0]
	bl FUN_02059C00
	ldr r1, _0204E698 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0x64
	ldrh r1, [r1, #0x0]
	add r0, r1, r0
	pop {r4, pc}
	.balign 4
_0204E694: .word 0x0000FFFF
_0204E698: .word UNK_021C5A68

	thumb_func_start FUN_0204E69C
FUN_0204E69C: ; 0x0204E69C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E6B6
	ldr r0, _0204E6C8 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E6BC
_0204E6B6:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_0204E6BC:
	lsl r0, r4, #0x3
	add r1, r1, r0
	mov r0, #0xa6
	ldrsb r0, [r1, r0]
	pop {r4, pc}
	nop
_0204E6C8: .word UNK_021C5A68

	thumb_func_start FUN_0204E6CC
FUN_0204E6CC: ; 0x0204E6CC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0204E2FC
	cmp r0, #0x0
	beq _0204E6E6
	ldr r0, _0204E6F8 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204E6EC
_0204E6E6:
	mov r0, #0x0
	mvn r0, r0
	pop {r4, pc}
_0204E6EC:
	lsl r0, r4, #0x3
	add r1, r1, r0
	mov r0, #0x66
	ldrsb r0, [r1, r0]
	pop {r4, pc}
	nop
_0204E6F8: .word UNK_021C5A68

	thumb_func_start FUN_0204E6FC
FUN_0204E6FC: ; 0x0204E6FC
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _0204E728 ; =UNK_021C5A68
	lsl r0, r0, #0x3
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0x66
	ldrsb r0, [r1, r0]
	bl FUN_0204F610
	ldr r2, _0204E728 ; =UNK_021C5A68
	lsl r1, r4, #0x3
	ldr r3, [r2, #0x0]
	add r1, r3, r1
	add r1, #0x66
	strb r0, [r1, #0x0]
	ldr r0, [r2, #0x0]
	mov r3, #0x1
	add r1, r0, r4
	ldr r0, _0204E72C ; =0x00000132
	strb r3, [r1, r0]
	pop {r4, pc}
	.balign 4
_0204E728: .word UNK_021C5A68
_0204E72C: .word 0x00000132

	thumb_func_start FUN_0204E730
FUN_0204E730: ; 0x0204E730
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, _0204E754 ; =UNK_021C5A68
	lsl r0, r0, #0x3
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xa6
	ldrsb r0, [r1, r0]
	bl FUN_0204F610
	ldr r1, _0204E754 ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x3
	add r1, r2, r1
	add r1, #0xa6
	strb r0, [r1, #0x0]
	pop {r4, pc}
	nop
_0204E754: .word UNK_021C5A68

	thumb_func_start FUN_0204E758
FUN_0204E758: ; 0x0204E758
	push {r4, lr}
	add r2, r0, #0x0
	ldr r0, _0204E774 ; =UNK_021C5A68
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r1, r2, #0x0
	ldr r0, [r0, #0x4]
	bl MOD18_02244D40
	add r1, r4, #0x0
	bl MOD18_02244D98
	pop {r4, pc}
	nop
_0204E774: .word UNK_021C5A68

	thumb_func_start FUN_0204E778
FUN_0204E778: ; 0x0204E778
	push {r3, lr}
	add r1, r0, #0x0
	ldr r0, _0204E790 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	bl MOD18_02244D40
	mov r1, #0x0
	bl MOD18_02244D98
	pop {r3, pc}
	nop
_0204E790: .word UNK_021C5A68

	thumb_func_start FUN_0204E794
FUN_0204E794: ; 0x0204E794
	push {r3-r7, lr}
	sub sp, #0x8
	str r1, [sp, #0x0]
	ldr r1, _0204E7C8 ; =UNK_021C5A68
	add r6, r3, #0x0
	ldr r4, [r1, #0x0]
	lsl r7, r0, #0x3
	add r4, #0x62
	add r0, r6, #0x0
	str r2, [sp, #0x4]
	add r5, r4, r7
	bl FUN_02059BF4
	ldr r1, [sp, #0x0]
	add r0, r1, r0
	strh r0, [r4, r7]
	add r0, r6, #0x0
	bl FUN_02059C00
	ldr r1, [sp, #0x4]
	add r0, r1, r0
	strh r0, [r5, #0x2]
	strb r6, [r5, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0204E7C8: .word UNK_021C5A68

	thumb_func_start FUN_0204E7CC
FUN_0204E7CC: ; 0x0204E7CC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0204E848 ; =UNK_021C5A68
	add r6, r1, #0x0
	ldr r0, [r0, #0x0]
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	cmp r0, #0x0
	beq _0204E844
	add r2, r0, #0x0
	add r2, #0xa2
	lsl r1, r5, #0x3
	add r4, r2, r1
	ldr r1, _0204E84C ; =0x000002BD
	ldrb r1, [r0, r1]
	cmp r1, #0x0
	bne _0204E7FA
	ldrh r1, [r4, #0x0]
	ldrh r3, [r4, #0x2]
	ldr r0, [r0, #0x54]
	mov r2, #0x0
	bl MOD05_021E5B30
_0204E7FA:
	strh r6, [r4, #0x0]
	ldr r0, [sp, #0x0]
	strh r7, [r4, #0x2]
	strb r0, [r4, #0x4]
	ldr r0, _0204E848 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r5, #0x2
	add r0, r1, r0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204E81A
	ldr r3, [sp, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02055514
_0204E81A:
	ldr r0, _0204E848 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E84C ; =0x000002BD
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204E832
	ldr r0, [r1, #0x54]
	ldrh r1, [r4, #0x0]
	ldrh r3, [r4, #0x2]
	mov r2, #0x0
	bl MOD05_021E5B30
_0204E832:
	ldr r0, _0204E848 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204E84C ; =0x000002BD
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	bne _0204E844
	add r0, r5, #0x0
	bl FUN_0204F0A8
_0204E844:
	pop {r3-r7, pc}
	nop
_0204E848: .word UNK_021C5A68
_0204E84C: .word 0x000002BD

	thumb_func_start FUN_0204E850
FUN_0204E850: ; 0x0204E850
	push {r3-r4, lr}
	sub sp, #0x4
	mov r2, #0x2
	add r1, sp, #0x0
	add r4, r0, #0x0
	strb r2, [r1, #0x0]
	strb r4, [r1, #0x1]
	ldr r1, _0204E8AC ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0xe2
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204E88A
	bl FUN_0204D830
	cmp r0, #0x0
	bne _0204E88A
	add r0, r4, #0x0
	bl FUN_0204EE9C
	cmp r0, #0x0
	add r0, sp, #0x0
	beq _0204E886
	mov r1, #0x3
	strb r1, [r0, #0x0]
	b _0204E88A
_0204E886:
	mov r1, #0x1
	strb r1, [r0, #0x0]
_0204E88A:
	mov r0, #0x1d
	add r1, sp, #0x0
	mov r2, #0x2
	bl FUN_02030BC4
	cmp r0, #0x0
	beq _0204E8A8
	add r0, sp, #0x0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	beq _0204E8A8
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0204EAD8
_0204E8A8:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0204E8AC: .word UNK_021C5A68

	thumb_func_start FUN_0204E8B0
FUN_0204E8B0: ; 0x0204E8B0
	push {r3-r6}
	ldr r2, _0204E8F8 ; =UNK_021C5A68
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	bne _0204E8C0
	mov r0, #0xff
	pop {r3-r6}
	bx lr
_0204E8C0:
	mov r2, #0x0
	add r4, r3, #0x0
_0204E8C4:
	add r5, r3, #0x0
	add r5, #0x48
	ldrb r5, [r5, #0x0]
	cmp r5, #0x0
	beq _0204E8E8
	add r5, r4, #0x0
	add r5, #0x64
	ldrh r6, [r5, #0x0]
	add r5, r4, #0x0
	add r5, #0x62
	ldrh r5, [r5, #0x0]
	cmp r0, r5
	bne _0204E8E8
	cmp r1, r6
	bne _0204E8E8
	add r0, r2, #0x0
	pop {r3-r6}
	bx lr
_0204E8E8:
	add r2, r2, #0x1
	add r3, r3, #0x1
	add r4, #0x8
	cmp r2, #0x8
	blt _0204E8C4
	mov r0, #0xff
	pop {r3-r6}
	bx lr
	.balign 4
_0204E8F8: .word UNK_021C5A68

	thumb_func_start FUN_0204E8FC
FUN_0204E8FC: ; 0x0204E8FC
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02030FE0
	cmp r0, #0x0
	beq _0204E962
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _0204E936
	bl FUN_02031190
	ldrb r1, [r4, #0x1]
	cmp r1, r0
	bne _0204E936
	ldr r1, _0204E964 ; =UNK_021C5A68
	mov r0, #0xae
	ldr r3, [r1, #0x0]
	lsl r0, r0, #0x2
	ldrb r2, [r3, r0]
	cmp r2, #0x0
	bne _0204E962
	mov r2, #0x1
	strb r2, [r3, r0]
	ldr r1, [r1, #0x0]
	ldr r0, _0204E968 ; =FUN_0204D308
	ldr r1, [r1, #0x54]
	bl MOD18_022494C8
	pop {r4, pc}
_0204E936:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x3
	bne _0204E962
	bl FUN_02031190
	ldrb r1, [r4, #0x1]
	cmp r1, r0
	bne _0204E962
	ldr r1, _0204E964 ; =UNK_021C5A68
	mov r0, #0xae
	ldr r3, [r1, #0x0]
	lsl r0, r0, #0x2
	ldrb r2, [r3, r0]
	cmp r2, #0x0
	bne _0204E962
	mov r2, #0x1
	strb r2, [r3, r0]
	ldr r1, [r1, #0x0]
	ldr r0, _0204E968 ; =FUN_0204D308
	ldr r1, [r1, #0x54]
	bl MOD18_0224A7C8
_0204E962:
	pop {r4, pc}
	.balign 4
_0204E964: .word UNK_021C5A68
_0204E968: .word FUN_0204D308

	thumb_func_start FUN_0204E96C
FUN_0204E96C: ; 0x0204E96C
	push {r4-r6, lr}
	ldr r0, _0204EACC ; =UNK_021C5A68
	add r5, r2, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0x0
	ldrb r0, [r5, #0x1]
	cmp r0, #0x8
	blo _0204E988
	bl GF_AssertFail
_0204E988:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x4
	bne _0204E9AA
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204E9AA
	bl FUN_0204F7E4
	bl MOD18_0223D638
	ldr r3, _0204EAD0 ; =FUN_0204E2AC
	mov r1, #0x48
	mov r2, #0x1
	bl MOD18_0224DCB8
_0204E9AA:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0204E9B8
	ldrb r0, [r5, #0x1]
	ldrb r1, [r5, #0x2]
	bl FUN_0204E730
_0204E9B8:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0204EA7C
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204EA7C
	ldr r2, _0204EACC ; =UNK_021C5A68
	ldrb r0, [r5, #0x2]
	ldr r2, [r2, #0x0]
	ldr r1, _0204EAD4 ; =FUN_0204D308
	ldr r2, [r2, #0x54]
	bl MOD18_02247A34
	ldr r0, _0204EACC ; =UNK_021C5A68
	ldrb r4, [r5, #0x1]
	ldr r2, [r0, #0x0]
	mov r3, #0xf
	add r1, r2, #0x0
	add r1, #0x58
	ldrb r1, [r1, #0x0]
	add r2, #0x58
	bic r1, r3
	mov r3, #0xf
	and r3, r4
	orr r1, r3
	strb r1, [r2, #0x0]
	ldr r2, [r0, #0x0]
	mov r3, #0xf0
	add r1, r2, #0x0
	add r1, #0x58
	ldrb r1, [r1, #0x0]
	add r2, #0x58
	bic r1, r3
	ldrb r3, [r5, #0x2]
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x18
	orr r1, r3
	strb r1, [r2, #0x0]
	ldr r3, [r0, #0x0]
	add r1, r3, #0x0
	add r1, #0x59
	ldrb r2, [r1, #0x0]
	mov r1, #0x1
	add r3, #0x59
	bic r2, r1
	strb r2, [r3, #0x0]
	ldr r3, [r0, #0x0]
	add r1, r3, #0x0
	add r1, #0x59
	ldrb r2, [r1, #0x0]
	mov r1, #0x2
	add r3, #0x59
	bic r2, r1
	strb r2, [r3, #0x0]
	ldrb r4, [r5, #0x2]
	ldr r1, [r0, #0x0]
	add r0, r1, r4
	add r0, #0x5a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204EA7C
	ldr r0, [r1, #0x54]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	add r1, r4, #0x0
	bl FUN_02026908
	add r0, r6, #0x0
	bl FUN_0205F688
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_0205F698
	add r0, r6, #0x0
	bl FUN_0205F6A8
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r6, #0x0
	lsr r1, r1, #0x10
	bl FUN_0205F6B8
	ldr r0, _0204EACC ; =UNK_021C5A68
	ldrb r1, [r5, #0x2]
	ldr r2, [r0, #0x0]
	add r2, #0x5a
	ldrb r0, [r2, r1]
	add r0, r0, #0x1
	strb r0, [r2, r1]
_0204EA7C:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0204EA9A
	ldrb r4, [r5, #0x2]
	bl FUN_02031190
	cmp r4, r0
	bne _0204EA9A
	ldr r2, _0204EACC ; =UNK_021C5A68
	ldrb r1, [r5, #0x1]
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0x54]
	bl MOD18_02248DF8
_0204EA9A:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x2
	bne _0204EABC
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204EABC
	bl FUN_0204F7E4
	bl MOD18_0223D638
	ldr r3, _0204EAD0 ; =FUN_0204E2AC
	mov r1, #0x2
	mov r2, #0x1
	bl MOD18_0224DCB8
_0204EABC:
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _0204EACA
	ldrb r0, [r5, #0x1]
	ldrb r1, [r5, #0x2]
	bl MOD18_0223E4A8
_0204EACA:
	pop {r4-r6, pc}
	.balign 4
_0204EACC: .word UNK_021C5A68
_0204EAD0: .word FUN_0204E2AC
_0204EAD4: .word FUN_0204D308

	thumb_func_start FUN_0204EAD8
FUN_0204EAD8: ; 0x0204EAD8
	push {r3-r4}
	ldr r3, _0204EB0C ; =UNK_021C5A68
	ldr r4, [r3, #0x0]
	add r4, #0xe2
	ldrb r2, [r4, r0]
	cmp r1, r2
	beq _0204EB08
	strb r1, [r4, r0]
	ldr r2, [r3, #0x0]
	lsl r1, r0, #0x3
	add r2, r2, r1
	mov r4, #0x0
	add r2, #0x69
	strb r4, [r2, #0x0]
	ldr r2, [r3, #0x0]
	mov r4, #0x1
	add r2, r2, r0
	ldr r0, _0204EB10 ; =0x00000132
	strb r4, [r2, r0]
	ldr r0, [r3, #0x0]
	mov r2, #0x2
	add r0, r0, r1
	add r0, #0x67
	strb r2, [r0, #0x0]
_0204EB08:
	pop {r3-r4}
	bx lr
	.balign 4
_0204EB0C: .word UNK_021C5A68
_0204EB10: .word 0x00000132

	thumb_func_start FUN_0204EB14
FUN_0204EB14: ; 0x0204EB14
	ldr r1, _0204EB3C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	ldr r1, _0204EB40 ; =0x000002C2
	ldrb r1, [r2, r1]
	cmp r1, #0x0
	beq _0204EB24
	mov r0, #0x0
	bx lr
_0204EB24:
	add r1, r2, r0
	add r1, #0xea
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	beq _0204EB36
	add r0, r2, r0
	add r0, #0xe2
	ldrb r0, [r0, #0x0]
	bx lr
_0204EB36:
	mov r0, #0x0
	bx lr
	nop
_0204EB3C: .word UNK_021C5A68
_0204EB40: .word 0x000002C2

	thumb_func_start FUN_0204EB44
FUN_0204EB44: ; 0x0204EB44
	push {r3-r7, lr}
	sub sp, #0x30
	ldr r1, _0204EBF8 ; =UNK_020F5800
	add r0, sp, #0x8
	ldrh r2, [r1, #0x0]
	ldr r3, _0204EBFC ; =UNK_020F5814
	strh r2, [r0, #0x0]
	ldrh r2, [r1, #0x2]
	strh r2, [r0, #0x2]
	ldrh r2, [r1, #0x4]
	ldrh r1, [r1, #0x6]
	strh r2, [r0, #0x4]
	strh r1, [r0, #0x6]
	add r2, sp, #0x20
	mov r1, #0x8
_0204EB62:
	ldrh r0, [r3, #0x0]
	add r3, r3, #0x2
	strh r0, [r2, #0x0]
	add r2, r2, #0x2
	sub r1, r1, #0x1
	bne _0204EB62
	bl FUN_02033534
	bl FUN_02031248
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x4]
	str r0, [sp, #0x0]
	cmp r6, #0x2
	bne _0204EB86
	add r5, sp, #0x8
	b _0204EB88
_0204EB86:
	add r5, sp, #0x20
_0204EB88:
	mov r7, #0x0
	cmp r6, #0x0
	ble _0204EBD4
_0204EB8E:
	mov r4, #0x0
	cmp r6, #0x0
	ble _0204EBCC
_0204EB94:
	add r0, r4, #0x0
	bl FUN_0204E3EC
	ldrh r1, [r5, #0x0]
	cmp r1, r0
	bne _0204EBC6
	add r0, r4, #0x0
	bl FUN_0204E440
	ldrh r1, [r5, #0x2]
	cmp r1, r0
	bne _0204EBC6
	ldr r0, [sp, #0x4]
	lsl r1, r4, #0x2
	add r0, r0, #0x1
	str r0, [sp, #0x4]
	add r0, sp, #0x10
	str r7, [r0, r1]
	bl FUN_02031190
	cmp r4, r0
	bne _0204EBCC
	mov r0, #0x1
	str r0, [sp, #0x0]
	b _0204EBCC
_0204EBC6:
	add r4, r4, #0x1
	cmp r4, r6
	blt _0204EB94
_0204EBCC:
	add r7, r7, #0x1
	add r5, r5, #0x4
	cmp r7, r6
	blt _0204EB8E
_0204EBD4:
	ldr r0, [sp, #0x4]
	cmp r0, r6
	bne _0204EBF2
	mov r5, #0x0
	cmp r6, #0x0
	ble _0204EBF2
	add r4, sp, #0x10
_0204EBE2:
	ldr r0, [r4, #0x0]
	add r1, r5, #0x0
	bl FUN_020313B4
	add r5, r5, #0x1
	add r4, r4, #0x4
	cmp r5, r6
	blt _0204EBE2
_0204EBF2:
	ldr r0, [sp, #0x0]
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_0204EBF8: .word UNK_020F5800
_0204EBFC: .word UNK_020F5814

	thumb_func_start FUN_0204EC00
FUN_0204EC00: ; 0x0204EC00
	ldrb r2, [r2, #0x0]
	cmp r2, #0x3
	bne _0204EC14
	ldr r1, _0204EC24 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0xf2
	strb r2, [r0, #0x0]
	bx lr
_0204EC14:
	ldr r1, _0204EC24 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0xad
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	bx lr
	nop
_0204EC24: .word UNK_021C5A68

	thumb_func_start FUN_0204EC28
FUN_0204EC28: ; 0x0204EC28
	push {r3-r7, lr}
	sub sp, #0x8
	bl FUN_02033534
	bl FUN_02031248
	add r7, r0, #0x0
	cmp r7, #0x2
	bne _0204EC40
	ldr r0, _0204ECB4 ; =UNK_02105E5C
	str r0, [sp, #0x0]
	b _0204EC44
_0204EC40:
	ldr r0, _0204ECB8 ; =UNK_02105E64
	str r0, [sp, #0x0]
_0204EC44:
	mov r1, #0x0
	add r0, sp, #0x4
	strb r1, [r0, #0x0]
	cmp r7, #0x0
	ble _0204ECAE
_0204EC4E:
	ldr r0, _0204ECBC ; =UNK_021C5A68
	add r6, sp, #0x4
	ldr r1, [r0, #0x0]
	ldrb r0, [r6, #0x0]
	add r1, r1, r0
	mov r0, #0xad
	lsl r0, r0, #0x2
	ldrb r0, [r1, r0]
	cmp r0, #0x0
	beq _0204ECA0
	mov r4, #0x0
	cmp r7, #0x0
	ble _0204ECA0
	ldr r5, [sp, #0x0]
_0204EC6A:
	ldrb r0, [r6, #0x0]
	bl FUN_0204E544
	ldrh r1, [r5, #0x0]
	cmp r1, r0
	bne _0204EC98
	ldrb r0, [r6, #0x0]
	bl FUN_0204E598
	ldrh r1, [r5, #0x2]
	cmp r1, r0
	bne _0204EC98
	ldr r0, _0204ECBC ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldrb r0, [r6, #0x0]
	add r1, r1, r0
	add r1, #0xf2
	mov r0, #0x1
	strb r0, [r1, #0x0]
	mov r0, #0x5f
	add r1, sp, #0x4
	bl FUN_02030C4C
_0204EC98:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r7
	blt _0204EC6A
_0204ECA0:
	add r0, sp, #0x4
	ldrb r1, [r0, #0x0]
	add r1, r1, #0x1
	strb r1, [r0, #0x0]
	ldrb r0, [r0, #0x0]
	cmp r0, r7
	blt _0204EC4E
_0204ECAE:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_0204ECB4: .word UNK_02105E5C
_0204ECB8: .word UNK_02105E64
_0204ECBC: .word UNK_021C5A68

	thumb_func_start FUN_0204ECC0
FUN_0204ECC0: ; 0x0204ECC0
	push {r4, lr}
	bl FUN_02031190
	add r4, r0, #0x0
	bl FUN_0204E3EC
	cmp r0, #0x8
	ble _0204ECE0
	mov r0, #0x2
	bl FUN_0204F6DC
	mov r0, #0x2
	mov r1, #0x24
	bl FUN_0205AFDC
	b _0204ECEE
_0204ECE0:
	mov r0, #0x3
	bl FUN_0204F6DC
	mov r0, #0x3
	mov r1, #0x24
	bl FUN_0205AFDC
_0204ECEE:
	add r1, r0, #0x0
	ldr r0, _0204ED04 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r2, r0
	ldr r0, [r0, #0x8]
	bl FUN_02057260
	bl FUN_0204FB14
	pop {r4, pc}
	.balign 4
_0204ED04: .word UNK_021C5A68

	thumb_func_start FUN_0204ED08
FUN_0204ED08: ; 0x0204ED08
	push {r3-r7, lr}
	sub sp, #0x8
	bl FUN_02033534
	bl FUN_02031248
	mov r3, #0x0
	str r0, [sp, #0x0]
	cmp r0, #0x0
	ble _0204ED3C
	ldr r0, _0204ED94 ; =UNK_021C5A68
	mov r1, #0x66
	add r2, r1, #0x0
	ldr r4, [r0, #0x0]
	sub r2, #0x67
_0204ED26:
	ldrsb r0, [r4, r1]
	cmp r0, r2
	bne _0204ED32
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0204ED32:
	ldr r0, [sp, #0x0]
	add r3, r3, #0x1
	add r4, #0x8
	cmp r3, r0
	blt _0204ED26
_0204ED3C:
	ldr r0, [sp, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ble _0204ED8E
	add r4, r5, #0x0
_0204ED46:
	ldr r0, _0204ED94 ; =UNK_021C5A68
	ldr r7, [r0, #0x0]
	mov r0, #0x4
	add r7, #0x62
	add r6, r7, r4
	ldrsb r0, [r6, r0]
	bl FUN_0204F610
	str r0, [sp, #0x4]
	bl FUN_02059BF4
	ldrh r1, [r7, r4]
	add r0, r1, r0
	strh r0, [r7, r4]
	ldr r0, [sp, #0x4]
	bl FUN_02059C00
	ldrh r1, [r6, #0x2]
	add r0, r1, r0
	strh r0, [r6, #0x2]
	mov r0, #0x2
	strb r0, [r6, #0x5]
	ldr r0, _0204ED94 ; =UNK_021C5A68
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r2, r0, r5
	ldr r0, _0204ED98 ; =0x00000132
	strb r1, [r2, r0]
	add r0, r5, #0x0
	bl FUN_0204EAD8
	ldr r0, [sp, #0x0]
	add r5, r5, #0x1
	add r4, #0x8
	cmp r5, r0
	blt _0204ED46
_0204ED8E:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0204ED94: .word UNK_021C5A68
_0204ED98: .word 0x00000132

	thumb_func_start FUN_0204ED9C
FUN_0204ED9C: ; 0x0204ED9C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204EDE8 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204EDE2
	bl FreeToHeap
	ldr r2, _0204EDE8 ; =UNK_021C5A68
	lsl r1, r4, #0x2
	ldr r3, [r2, #0x0]
	mov r0, #0x0
	add r3, r3, r1
	mov r1, #0x29
	lsl r1, r1, #0x4
	str r0, [r3, r1]
	ldr r1, [r2, #0x0]
	mov r3, #0xff
	add r1, r1, r4
	add r1, #0xfa
	strb r0, [r1, #0x0]
	mov r0, #0x22
	ldr r1, [r2, #0x0]
	mul r0, r4
	add r1, r1, r0
	add r0, r3, #0x0
	add r0, #0x6b
	strh r3, [r1, r0]
	mov r0, #0x1
	pop {r4, pc}
_0204EDE2:
	mov r0, #0x0
	pop {r4, pc}
	nop
_0204EDE8: .word UNK_021C5A68

	thumb_func_start FUN_0204EDEC
FUN_0204EDEC: ; 0x0204EDEC
	push {r3-r7, lr}
	add r7, r0, #0x0
	bl FUN_02031190
	cmp r7, r0
	bne _0204EE90
	ldr r0, _0204EE98 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	lsl r0, r7, #0x2
	add r1, r2, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204EE96
	ldr r0, [r2, #0x54]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x1c
	bl FUN_0202A170
	ldr r0, _0204EE98 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	mov r0, #0xa3
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204EE2A
	bl FreeToHeap
_0204EE2A:
	mov r0, #0x9e
	lsl r0, r0, #0x2
	ldr r2, _0204EE98 ; =UNK_021C5A68
	mov r5, #0x4
	mov r6, #0x10
	add r1, r0, #0x4
_0204EE36:
	ldr r3, [r2, #0x0]
	sub r5, r5, #0x1
	add r4, r3, r6
	ldr r3, [r4, r0]
	sub r6, r6, #0x4
	str r3, [r4, r1]
	cmp r5, #0x1
	bge _0204EE36
	ldr r1, _0204EE98 ; =UNK_021C5A68
	mov r0, #0x29
	ldr r3, [r1, #0x0]
	lsl r4, r7, #0x2
	add r2, r3, r4
	lsl r0, r0, #0x4
	ldr r2, [r2, r0]
	sub r0, #0x14
	str r2, [r3, r0]
	ldr r5, [r1, #0x0]
	ldr r0, [r5, #0x54]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	mov r1, #0x29
	add r2, r5, r4
	lsl r1, r1, #0x4
	ldr r1, [r2, r1]
	bl FUN_02025C40
	ldr r1, _0204EE98 ; =UNK_021C5A68
	mov r3, #0x0
	ldr r0, [r1, #0x0]
	add r2, r0, r4
	mov r0, #0x29
	lsl r0, r0, #0x4
	str r3, [r2, r0]
	mov r0, #0x22
	ldr r1, [r1, #0x0]
	mul r0, r7
	mov r2, #0xff
	add r1, r1, r0
	add r0, r2, #0x0
	add r0, #0x6b
	strh r2, [r1, r0]
	pop {r3-r7, pc}
_0204EE90:
	add r0, r7, #0x0
	bl FUN_0204ED9C
_0204EE96:
	pop {r3-r7, pc}
	.balign 4
_0204EE98: .word UNK_021C5A68

	thumb_func_start FUN_0204EE9C
FUN_0204EE9C: ; 0x0204EE9C
	ldr r1, _0204EEB8 ; =UNK_021C5A68
	lsl r0, r0, #0x2
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204EEB2
	mov r0, #0x1
	bx lr
_0204EEB2:
	mov r0, #0x0
	bx lr
	nop
_0204EEB8: .word UNK_021C5A68

	thumb_func_start FUN_0204EEBC
FUN_0204EEBC: ; 0x0204EEBC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0204EF48 ; =UNK_021C5A68
	add r6, r1, #0x0
	ldr r1, [r0, #0x0]
	lsl r0, r5, #0x2
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0204EF44
	add r0, r6, #0x0
	bl FUN_0202DFA4
	add r7, r0, #0x0
	beq _0204EF44
	mov r0, #0xf
	lsl r4, r5, #0x2
	bl PlayerProfile_new
	mov r3, #0x29
	ldr r1, _0204EF48 ; =UNK_021C5A68
	add r2, r0, #0x0
	ldr r0, [r1, #0x0]
	lsl r3, r3, #0x4
	add r0, r0, r4
	str r2, [r0, r3]
	ldr r1, [r1, #0x0]
	add r0, r7, #0x0
	add r1, r1, r4
	ldr r1, [r1, r3]
	bl PlayerProfile_Copy
	ldr r1, _0204EF48 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r0, [r1, #0x0]
	ldr r3, _0204EF4C ; =0x0000016A
	add r0, r0, r5
	add r0, #0xfa
	strb r2, [r0, #0x0]
	mov r0, #0x22
	add r2, r5, #0x0
	mul r2, r0
	ldr r0, [r1, #0x0]
	add r0, r0, r2
	strh r5, [r0, r3]
	ldr r1, [r1, #0x0]
	sub r3, #0x20
	add r1, r1, r3
	add r0, r7, #0x0
	add r1, r1, r2
	bl PlayerProfile_Copy
	bl FUN_02031190
	cmp r6, r0
	bne _0204EF40
	ldr r0, _0204EF48 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0xc]
	bl FUN_02026CB4
	bl FUN_02026BC8
_0204EF40:
	mov r0, #0x1
	pop {r3-r7, pc}
_0204EF44:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_0204EF48: .word UNK_021C5A68
_0204EF4C: .word 0x0000016A

	thumb_func_start FUN_0204EF50
FUN_0204EF50: ; 0x0204EF50
	push {r3-r7, lr}
	ldr r4, _0204EFC4 ; =UNK_021C5A68
	mov r7, #0x29
	ldr r6, [r4, #0x0]
	add r3, r0, #0x0
	lsl r7, r7, #0x4
	add r5, r6, r7
	lsl r0, r3, #0x2
	add r2, r1, #0x0
	ldr r1, [r5, r0]
	cmp r1, #0x0
	bne _0204EFBE
	lsl r1, r2, #0x2
	add r6, r6, r1
	ldr r6, [r6, r7]
	cmp r6, #0x0
	beq _0204EFBE
	str r6, [r5, r0]
	ldr r5, [r4, #0x0]
	mov r6, #0x0
	add r1, r5, r1
	str r6, [r1, r7]
	ldr r1, [r4, #0x0]
	mov r5, #0x1
	add r1, r1, r3
	add r1, #0xfa
	strb r5, [r1, #0x0]
	ldr r1, [r4, #0x0]
	add r1, r1, r2
	add r1, #0xfa
	strb r6, [r1, #0x0]
	mov r1, #0x22
	ldr r5, [r4, #0x0]
	mul r1, r3
	add r6, r5, r1
	ldr r5, _0204EFC8 ; =0x0000016A
	strh r3, [r6, r5]
	mov r6, #0x22
	mov r5, #0xff
	mul r6, r2
	ldr r3, [r4, #0x0]
	add r2, r5, #0x0
	add r3, r3, r6
	add r2, #0x6b
	strh r5, [r3, r2]
	ldr r2, [r4, #0x0]
	add r5, #0x4b
	add r0, r2, r0
	add r2, r2, r5
	ldr r0, [r0, r7]
	add r1, r2, r1
	bl PlayerProfile_Copy
	mov r0, #0x1
	pop {r3-r7, pc}
_0204EFBE:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0204EFC4: .word UNK_021C5A68
_0204EFC8: .word 0x0000016A

	thumb_func_start FUN_0204EFCC
FUN_0204EFCC: ; 0x0204EFCC
	push {r4, lr}
	ldr r1, _0204F06C ; =UNK_021C5A68
	add r4, r0, #0x0
	ldr r3, [r1, #0x0]
	ldr r1, _0204F070 ; =0x000002BD
	ldrb r1, [r3, r1]
	cmp r1, #0x0
	bne _0204F068
	lsl r1, r4, #0x2
	add r2, r3, r1
	ldr r1, [r2, #0x8]
	cmp r1, #0x0
	beq _0204F068
	add r3, r3, r4
	add r3, #0xfa
	ldrb r3, [r3, #0x0]
	cmp r3, #0x3
	bhi _0204F068
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #0x6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0204EFFC: ; jump table (using 16-bit offset)
	.short _0204F064 - _0204EFFC - 2; case 0
	.short _0204F048 - _0204EFFC - 2; case 1
	.short _0204F02C - _0204EFFC - 2; case 2
	.short _0204F004 - _0204EFFC - 2; case 3
_0204F004:
	ldr r0, [r2, #0x28]
	cmp r0, #0x0
	bne _0204F01E
	add r0, r1, #0x0
	bl FUN_020553A0
	bl MOD05_021E5970
	ldr r1, _0204F06C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x2
	add r1, r2, r1
	str r0, [r1, #0x28]
_0204F01E:
	ldr r0, _0204F06C ; =UNK_021C5A68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0xfa
	strb r1, [r0, #0x0]
	pop {r4, pc}
_0204F02C:
	ldr r0, [r2, #0x28]
	cmp r0, #0x0
	bne _0204F068
	add r0, r1, #0x0
	bl FUN_020553A0
	bl MOD05_021E57D4
	ldr r1, _0204F06C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x2
	add r1, r2, r1
	str r0, [r1, #0x28]
	pop {r4, pc}
_0204F048:
	ldr r0, [r2, #0x28]
	cmp r0, #0x0
	bne _0204F068
	add r0, r1, #0x0
	bl FUN_020553A0
	bl MOD05_021E5614
	ldr r1, _0204F06C ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	lsl r1, r4, #0x2
	add r1, r2, r1
	str r0, [r1, #0x28]
	pop {r4, pc}
_0204F064:
	bl FUN_0204CD78
_0204F068:
	pop {r4, pc}
	nop
_0204F06C: .word UNK_021C5A68
_0204F070: .word 0x000002BD

	thumb_func_start FUN_0204F074
FUN_0204F074: ; 0x0204F074
	ldr r1, _0204F088 ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	add r2, #0xfa
	ldrb r1, [r2, r0]
	cmp r1, #0x1
	beq _0204F084
	mov r1, #0x2
	strb r1, [r2, r0]
_0204F084:
	bx lr
	nop
_0204F088: .word UNK_021C5A68

	thumb_func_start FUN_0204F08C
FUN_0204F08C: ; 0x0204F08C
	ldr r1, _0204F0A0 ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	add r2, #0xfa
	ldrb r1, [r2, r0]
	cmp r1, #0x1
	beq _0204F09C
	mov r1, #0x3
	strb r1, [r2, r0]
_0204F09C:
	ldr r3, _0204F0A4 ; =FUN_0204CD78
	bx r3
	.balign 4
_0204F0A0: .word UNK_021C5A68
_0204F0A4: .word FUN_0204CD78

	thumb_func_start FUN_0204F0A8
FUN_0204F0A8: ; 0x0204F0A8
	ldr r1, _0204F0BC ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	add r2, #0xfa
	ldrb r1, [r2, r0]
	cmp r1, #0x1
	beq _0204F0B8
	mov r1, #0x0
	strb r1, [r2, r0]
_0204F0B8:
	ldr r3, _0204F0C0 ; =FUN_0204CD78
	bx r3
	.balign 4
_0204F0BC: .word UNK_021C5A68
_0204F0C0: .word FUN_0204CD78

	thumb_func_start FUN_0204F0C4
FUN_0204F0C4: ; 0x0204F0C4
	mov r0, #0x3
	bx lr

	thumb_func_start FUN_0204F0C8
FUN_0204F0C8: ; 0x0204F0C8
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, sp, #0x0
	strb r4, [r0, #0x1]
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	beq _0204F0E0
	cmp r1, #0x3
	beq _0204F0F0
	add sp, #0x4
	pop {r3-r4, pc}
_0204F0E0:
	mov r1, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0x55
	add r1, sp, #0x0
	bl FUN_02030C4C
	add sp, #0x4
	pop {r3-r4, pc}
_0204F0F0:
	mov r1, #0x3
	strb r1, [r0, #0x0]
	mov r0, #0x55
	add r1, sp, #0x0
	bl FUN_02030C4C
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0204EAD8
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_0204F108
FUN_0204F108: ; 0x0204F108
	push {r3, lr}
	bl FUN_02031190
	bl FUN_0204F0A8
	bl MOD18_0223D648
	bl MOD18_0224DD94
	mov r0, #0x4
	bl FUN_0204F774
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204F124
FUN_0204F124: ; 0x0204F124
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r4, #0x0
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	add r0, r7, #0x0
	bl FUN_02030E7C
	cmp r0, #0x0
	bne _0204F14A
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r6, #0x0
	bl FUN_0200CAB4
	pop {r3-r7, pc}
_0204F14A:
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	cmp r0, #0x3c
	ble _0204F156
	mov r4, #0x1
_0204F156:
	cmp r4, #0x0
	beq _0204F172
	ldr r0, _0204F174 ; =UNK_021C5A68
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, r0, r7
	add r0, #0xea
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r6, #0x0
	bl FUN_0200CAB4
_0204F172:
	pop {r3-r7, pc}
	.balign 4
_0204F174: .word UNK_021C5A68

	thumb_func_start FUN_0204F178
FUN_0204F178: ; 0x0204F178
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xb
	mov r1, #0x8
	bl AllocFromHeap
	add r1, r0, #0x0
	mov r2, #0x0
	str r2, [r1, #0x0]
	ldr r0, _0204F1A8 ; =UNK_021C5A68
	str r4, [r1, #0x4]
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0xea
	strb r2, [r0, #0x0]
	ldr r0, _0204F1AC ; =FUN_0204F124
	mov r2, #0x64
	bl FUN_0200CA44
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_0204EAD8
	pop {r4, pc}
	.balign 4
_0204F1A8: .word UNK_021C5A68
_0204F1AC: .word FUN_0204F124

	thumb_func_start FUN_0204F1B0
FUN_0204F1B0: ; 0x0204F1B0
	push {r3-r5, lr}
	add r4, r1, #0x0
	mov r1, #0x1
	add r5, r0, #0x0
	tst r1, r2
	beq _0204F1C4
	mov r1, #0xb
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	b _0204F1F6
_0204F1C4:
	bl FUN_0204EE9C
	cmp r0, #0x0
	beq _0204F1D4
	mov r1, #0xb
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	b _0204F1F6
_0204F1D4:
	cmp r4, #0xff
	bne _0204F1DC
	mov r0, #0x0
	pop {r3-r5, pc}
_0204F1DC:
	add r0, r4, #0x0
	bl FUN_0204EE9C
	cmp r0, #0x0
	bne _0204F1EA
	mov r0, #0x0
	pop {r3-r5, pc}
_0204F1EA:
	mov r1, #0x5
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0204F178
_0204F1F6:
	add r0, sp, #0x0
	strb r5, [r0, #0x1]
	strb r4, [r0, #0x2]
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0204EAD8
	mov r0, #0x55
	add r1, sp, #0x0
	bl FUN_02030C4C
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0204F210
FUN_0204F210: ; 0x0204F210
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_0204EE9C
	cmp r0, #0x0
	beq _0204F226
	mov r1, #0xc
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	b _0204F22C
_0204F226:
	add sp, #0x4
	mov r0, #0x0
	pop {r3-r4, pc}
_0204F22C:
	strb r4, [r0, #0x1]
	mov r0, #0x55
	add r1, sp, #0x0
	bl FUN_02030C4C
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_0204F23C
FUN_0204F23C: ; 0x0204F23C
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl MOD18_0223E6B8
	mov r0, #0x0
	bl FUN_0204D628
	mov r0, #0x4
	bl FUN_0204F74C
	bl MOD18_0223D648
	add r6, r0, #0x0
	ldrb r0, [r5, #0x1]
	bl FUN_0202DFA4
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl MOD18_0224DDB8
	cmp r4, #0x0
	beq _0204F29C
	bl FUN_02031190
	ldr r1, _0204F2C8 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0xfa
	strb r2, [r0, #0x0]
	bl FUN_02031190
	bl FUN_0204F0A8
	bl FUN_02031190
	bl FUN_0204F074
	bl MOD18_0223D648
	ldr r3, _0204F2CC ; =FUN_0204F108
	mov r1, #0xa
	mov r2, #0x1
	bl MOD18_0224DCB8
	b _0204F2AA
_0204F29C:
	bl MOD18_0223D648
	ldr r3, _0204F2CC ; =FUN_0204F108
	mov r1, #0xb
	mov r2, #0x1
	bl MOD18_0224DCB8
_0204F2AA:
	mov r0, #0xff
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r1, _0204F2D0 ; =0x00000424
	mov r0, #0x4
	mov r2, #0x3c
	str r3, [sp, #0x4]
	bl FUN_02004DCC
	ldr r0, _0204F2D4 ; =0x000005F6
	bl FUN_020054C8
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_0204F2C8: .word UNK_021C5A68
_0204F2CC: .word FUN_0204F108
_0204F2D0: .word 0x00000424
_0204F2D4: .word 0x000005F6

	thumb_func_start FUN_0204F2D8
FUN_0204F2D8: ; 0x0204F2D8
	push {r4-r5, lr}
	sub sp, #0xc
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	add r5, r2, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	add r4, r0, #0x0
	ldrb r0, [r5, #0x0]
	cmp r0, #0x5
	bgt _0204F308
	cmp r0, #0x0
	blt _0204F346
	beq _0204F31E
	cmp r0, #0x3
	bne _0204F300
	b _0204F4D2
_0204F300:
	cmp r0, #0x5
	beq _0204F370
	add sp, #0xc
	pop {r4-r5, pc}
_0204F308:
	cmp r0, #0xc
	bgt _0204F346
	cmp r0, #0xb
	blt _0204F346
	bne _0204F314
	b _0204F48C
_0204F314:
	cmp r0, #0xc
	bne _0204F31A
	b _0204F4AE
_0204F31A:
	add sp, #0xc
	pop {r4-r5, pc}
_0204F31E:
	ldr r1, _0204F5E0 ; =UNK_021C5A68
	ldrb r0, [r5, #0x1]
	ldr r2, [r1, #0x0]
	lsl r1, r0, #0x2
	add r2, r2, r1
	mov r1, #0x29
	lsl r1, r1, #0x4
	ldr r1, [r2, r1]
	cmp r1, #0x0
	beq _0204F346
	bl FUN_0204ED9C
	ldrb r0, [r5, #0x1]
	bl FUN_0204F0A8
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	beq _0204F348
_0204F346:
	b _0204F5DA
_0204F348:
	bl FUN_0204F7E4
	bl MOD18_0223D648
	ldr r3, _0204F5E4 ; =FUN_0204E2B4
	mov r1, #0x2
	mov r2, #0x1
	bl MOD18_0224DCB8
	mov r0, #0xff
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r1, _0204F5E8 ; =0x00000424
	mov r0, #0x4
	mov r2, #0x3c
	str r3, [sp, #0x4]
	bl FUN_02004DCC
	add sp, #0xc
	pop {r4-r5, pc}
_0204F370:
	ldrb r0, [r5, #0x1]
	bl FUN_0202DFA4
	cmp r0, #0x0
	bne _0204F384
	ldrb r0, [r5, #0x2]
	bl FUN_0204ED9C
	add sp, #0xc
	pop {r4-r5, pc}
_0204F384:
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldrb r0, [r5, #0x2]
	lsl r0, r0, #0x2
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	bne _0204F3AC
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	beq _0204F3A4
	b _0204F5DA
_0204F3A4:
	bl FUN_0204F7FC
	add sp, #0xc
	pop {r4-r5, pc}
_0204F3AC:
	ldrb r0, [r5, #0x1]
	bl FUN_0202DFA4
	add r1, r0, #0x0
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	ldrb r0, [r5, #0x2]
	lsl r0, r0, #0x2
	add r2, r2, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r2, r0]
	bl PlayerProfile_NameAndOTIDMatchPlayer
	cmp r0, #0x1
	bne _0204F41A
	ldrb r0, [r5, #0x2]
	bl FUN_0204ED9C
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204F3FC
	add r0, r4, #0x0
	bl FUN_02026C00
	bl FUN_0204F7E4
	bl MOD18_0223D648
	ldr r3, _0204F5EC ; =FUN_0204E2AC
	mov r1, #0xd
	mov r2, #0x1
	bl MOD18_0224DCB8
	ldr r0, _0204F5F0 ; =0x00000625
	bl FUN_020054C8
	b _0204F410
_0204F3FC:
	bl FUN_02031190
	ldrb r1, [r5, #0x2]
	cmp r1, r0
	bne _0204F410
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_0204F23C
_0204F410:
	ldrb r0, [r5, #0x1]
	bl MOD18_022472AC
	add sp, #0xc
	pop {r4-r5, pc}
_0204F41A:
	ldrb r0, [r5, #0x1]
	ldrb r1, [r5, #0x2]
	bl FUN_0204EF50
	cmp r0, #0x0
	beq _0204F4B8
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204F46C
	add r0, r4, #0x0
	bl FUN_02026970
	mov r0, #0x1
	bl FUN_0204F74C
	bl MOD18_0223D648
	add r4, r0, #0x0
	ldrb r0, [r5, #0x2]
	bl FUN_0202DFA4
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl MOD18_0224DDB8
	bl MOD18_0223D648
	ldr r3, _0204F5F4 ; =FUN_0204E2D4
	mov r1, #0xc
	mov r2, #0x1
	bl MOD18_0224DCB8
	ldr r0, _0204F5F8 ; =0x00000425
	bl FUN_0200521C
	ldr r0, _0204F5F0 ; =0x00000625
	bl FUN_020054C8
	b _0204F480
_0204F46C:
	bl FUN_02031190
	ldrb r1, [r5, #0x2]
	cmp r1, r0
	bne _0204F480
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0204F23C
_0204F480:
	ldrb r0, [r5, #0x1]
	ldrb r1, [r5, #0x2]
	bl MOD18_02247294
	add sp, #0xc
	pop {r4-r5, pc}
_0204F48C:
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204F4B8
	mov r0, #0x2
	bl FUN_0204F74C
	bl MOD18_0223D648
	ldr r3, _0204F5FC ; =FUN_0204E2BC
	mov r1, #0x6
	mov r2, #0x1
	bl MOD18_0224DCB8
	add sp, #0xc
	pop {r4-r5, pc}
_0204F4AE:
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	beq _0204F4BA
_0204F4B8:
	b _0204F5DA
_0204F4BA:
	mov r0, #0x20
	bl FUN_0204F74C
	bl MOD18_0223D648
	ldr r3, _0204F600 ; =FUN_0204E2C8
	mov r1, #0x5
	mov r2, #0x1
	bl MOD18_0224DCB8
	add sp, #0xc
	pop {r4-r5, pc}
_0204F4D2:
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldrb r0, [r5, #0x1]
	add r0, r1, r0
	add r0, #0xfa
	strb r2, [r0, #0x0]
	ldrb r0, [r5, #0x1]
	bl FUN_0204F0A8
	bl FUN_02031190
	ldrb r1, [r5, #0x1]
	cmp r1, r0
	bne _0204F58C
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	add r4, r0, #0x0
	bl FUN_020269A0
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020269D4
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205EDF8
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldrb r1, [r5, #0x1]
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0x2
	add r2, r0, r1
	mov r1, #0x29
	lsl r1, r1, #0x4
	ldr r1, [r2, r1]
	cmp r1, #0x0
	beq _0204F54A
	ldr r0, [r0, #0x54]
	bl FUN_0206189C
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r1, _0204F604 ; =0x0000FFFF
	ldr r3, [r0, #0x0]
	ldr r0, _0204F608 ; =0x000002B2
	ldrh r2, [r3, r0]
	cmp r2, r1
	beq _0204F54A
	add r1, r2, #0x1
	strh r1, [r3, r0]
_0204F54A:
	bl FUN_0204F7E4
	ldr r0, _0204F60C ; =0x0000062B
	bl FUN_020054C8
	add r0, r4, #0x0
	bl FUN_020269A0
	add r1, sp, #0x8
	ldrb r1, [r1, #0x0]
	cmp r1, r0
	bne _0204F572
	bl MOD18_0223D648
	ldr r3, _0204F5EC ; =FUN_0204E2AC
	mov r1, #0x7
	mov r2, #0x1
	bl MOD18_0224DCB8
	b _0204F57A
_0204F572:
	mov r0, #0x60
	add r1, sp, #0x8
	bl FUN_020311D0
_0204F57A:
	mov r0, #0xff
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r1, _0204F5E8 ; =0x00000424
	mov r0, #0x4
	mov r2, #0x3c
	str r3, [sp, #0x4]
	bl FUN_02004DCC
_0204F58C:
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldrb r0, [r5, #0x1]
	lsl r0, r0, #0x2
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204F5D4
	bl FUN_02031190
	bl FUN_0202DFA4
	add r1, r0, #0x0
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	ldrb r0, [r5, #0x1]
	lsl r0, r0, #0x2
	add r2, r2, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r2, r0]
	bl PlayerProfile_NameAndOTIDMatchPlayer
	cmp r0, #0x1
	bne _0204F5D4
	ldrb r0, [r5, #0x1]
	bl FUN_0202DFA4
	add r1, r0, #0x0
	ldr r0, _0204F5E0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	bl FUN_020618B8
_0204F5D4:
	ldrb r0, [r5, #0x1]
	bl FUN_0204EDEC
_0204F5DA:
	add sp, #0xc
	pop {r4-r5, pc}
	nop
_0204F5E0: .word UNK_021C5A68
_0204F5E4: .word FUN_0204E2B4
_0204F5E8: .word 0x00000424
_0204F5EC: .word FUN_0204E2AC
_0204F5F0: .word 0x00000625
_0204F5F4: .word FUN_0204E2D4
_0204F5F8: .word 0x00000425
_0204F5FC: .word FUN_0204E2BC
_0204F600: .word FUN_0204E2C8
_0204F604: .word 0x0000FFFF
_0204F608: .word 0x000002B2
_0204F60C: .word 0x0000062B

	thumb_func_start FUN_0204F610
FUN_0204F610: ; 0x0204F610
	push {r3, lr}
	cmp r0, #0x0
	bne _0204F61A
	mov r0, #0x1
	pop {r3, pc}
_0204F61A:
	cmp r0, #0x1
	bne _0204F622
	mov r0, #0x0
	pop {r3, pc}
_0204F622:
	cmp r0, #0x2
	bne _0204F62A
	mov r0, #0x3
	pop {r3, pc}
_0204F62A:
	cmp r0, #0x3
	bne _0204F632
	mov r0, #0x2
	pop {r3, pc}
_0204F632:
	bl GF_AssertFail
	mov r0, #0x2
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204F63C
FUN_0204F63C: ; 0x0204F63C
	push {r3-r4}
	ldr r3, _0204F658 ; =UNK_021C5A68
	ldr r2, [r3, #0x0]
	add r4, r2, r0
	ldr r2, _0204F65C ; =0x0000011A
	strb r1, [r4, r2]
	ldr r1, [r3, #0x0]
	mov r4, #0xf
	add r0, r1, r0
	add r2, #0x20
	strb r4, [r0, r2]
	pop {r3-r4}
	bx lr
	nop
_0204F658: .word UNK_021C5A68
_0204F65C: .word 0x0000011A

	thumb_func_start FUN_0204F660
FUN_0204F660: ; 0x0204F660
	ldr r1, _0204F670 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	ldr r0, _0204F674 ; =0x0000011A
	strb r2, [r1, r0]
	bx lr
	nop
_0204F670: .word UNK_021C5A68
_0204F674: .word 0x0000011A

	thumb_func_start FUN_0204F678
FUN_0204F678: ; 0x0204F678
	push {r3-r4}
	ldr r3, _0204F694 ; =UNK_021C5A68
	ldr r2, [r3, #0x0]
	add r4, r2, r0
	ldr r2, _0204F698 ; =0x00000122
	strb r1, [r4, r2]
	ldr r1, [r3, #0x0]
	mov r4, #0xf
	add r0, r1, r0
	add r2, #0x18
	strb r4, [r0, r2]
	pop {r3-r4}
	bx lr
	nop
_0204F694: .word UNK_021C5A68
_0204F698: .word 0x00000122

	thumb_func_start FUN_0204F69C
FUN_0204F69C: ; 0x0204F69C
	ldr r1, _0204F6AC ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	ldr r0, _0204F6B0 ; =0x00000122
	strb r2, [r1, r0]
	bx lr
	nop
_0204F6AC: .word UNK_021C5A68
_0204F6B0: .word 0x00000122

	thumb_func_start FUN_0204F6B4
FUN_0204F6B4: ; 0x0204F6B4
	ldr r1, _0204F6C0 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	ldr r0, _0204F6C4 ; =0x00000142
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0204F6C0: .word UNK_021C5A68
_0204F6C4: .word 0x00000142

	thumb_func_start FUN_0204F6C8
FUN_0204F6C8: ; 0x0204F6C8
	ldr r1, _0204F6D4 ; =UNK_021C5A68
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	ldr r0, _0204F6D8 ; =0x0000013A
	ldrb r0, [r1, r0]
	bx lr
	.balign 4
_0204F6D4: .word UNK_021C5A68
_0204F6D8: .word 0x0000013A

	thumb_func_start FUN_0204F6DC
FUN_0204F6DC: ; 0x0204F6DC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0204F708 ; =UNK_021C5A68
	add r1, r4, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x54]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	bl FUN_02031190
	ldr r1, _0204F708 ; =UNK_021C5A68
	lsl r0, r0, #0x3
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	add r0, #0xa6
	strb r4, [r0, #0x0]
	mov r0, #0x0
	bl FUN_0204D168
	pop {r4, pc}
	nop
_0204F708: .word UNK_021C5A68

	thumb_func_start FUN_0204F70C
FUN_0204F70C: ; 0x0204F70C
	push {r4, lr}
	ldr r3, _0204F728 ; =UNK_021C5A68
	lsl r2, r0, #0x3
	ldr r4, [r3, #0x0]
	lsl r0, r0, #0x2
	add r2, r4, r2
	add r2, #0xa6
	strb r1, [r2, #0x0]
	ldr r2, [r3, #0x0]
	add r0, r2, r0
	ldr r0, [r0, #0x8]
	bl FUN_02055304
	pop {r4, pc}
	.balign 4
_0204F728: .word UNK_021C5A68

	thumb_func_start FUN_0204F72C
FUN_0204F72C: ; 0x0204F72C
	push {r3, lr}
	ldr r1, _0204F748 ; =UNK_021C5A68
	lsl r0, r0, #0x2
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204F742
	bl FUN_020552F8
	pop {r3, pc}
_0204F742:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
	.balign 4
_0204F748: .word UNK_021C5A68

	thumb_func_start FUN_0204F74C
FUN_0204F74C: ; 0x0204F74C
	push {r3, lr}
	cmp r0, #0x0
	beq _0204F75C
	ldr r1, _0204F770 ; =UNK_021C5A68
	ldr r2, [r1, #0x0]
	ldr r1, [r2, #0x0]
	orr r0, r1
	str r0, [r2, #0x0]
_0204F75C:
	bl FUN_02037760
	ldr r0, _0204F770 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	mov r0, #0xaf
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	pop {r3, pc}
	nop
_0204F770: .word UNK_021C5A68

	thumb_func_start FUN_0204F774
FUN_0204F774: ; 0x0204F774
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	beq _0204F788
	ldr r0, _0204F7D0 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	mvn r0, r4
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
_0204F788:
	ldr r0, _0204F7D0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x10
	bne _0204F7A0
	mov r1, #0x1
	add r0, sp, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0x3e
	add r1, sp, #0x0
	bl FUN_020311D0
_0204F7A0:
	ldr r0, _0204F7D0 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0204F7CC
	cmp r4, #0x10
	beq _0204F7BC
	bl FUN_02037778
	mov r0, #0x1
	bl FUN_0204D628
	add sp, #0x4
	pop {r3-r4, pc}
_0204F7BC:
	bl FUN_02037778
	ldr r0, _0204F7D0 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	mov r0, #0xaf
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
_0204F7CC:
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0204F7D0: .word UNK_021C5A68

	thumb_func_start FUN_0204F7D4
FUN_0204F7D4: ; 0x0204F7D4
	ldr r0, _0204F7E0 ; =UNK_021C5A68
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x0]
	bx lr
	nop
_0204F7E0: .word UNK_021C5A68

	thumb_func_start FUN_0204F7E4
FUN_0204F7E4: ; 0x0204F7E4
	push {r3, lr}
	bl FUN_02037760
	ldr r0, _0204F7F8 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	mov r0, #0xaf
	lsl r0, r0, #0x2
	strb r2, [r1, r0]
	pop {r3, pc}
	.balign 4
_0204F7F8: .word UNK_021C5A68

	thumb_func_start FUN_0204F7FC
FUN_0204F7FC: ; 0x0204F7FC
	push {r3, lr}
	bl FUN_02037778
	mov r0, #0x1
	bl FUN_0204D628
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0204F80C
FUN_0204F80C: ; 0x0204F80C
	push {r3, lr}
	ldr r0, _0204F850 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	ldr r0, _0204F854 ; =0x000002BF
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	bne _0204F84C
	sub r0, r0, #0x1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _0204F832
	bl FUN_0204F7FC
	ldr r0, _0204F850 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204F854 ; =0x000002BF
	strb r2, [r1, r0]
	pop {r3, pc}
_0204F832:
	bl FUN_02031190
	bl MOD12_0223E734
	cmp r0, #0x0
	beq _0204F84C
	bl FUN_0204F7FC
	ldr r0, _0204F850 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204F854 ; =0x000002BF
	strb r2, [r1, r0]
_0204F84C:
	pop {r3, pc}
	nop
_0204F850: .word UNK_021C5A68
_0204F854: .word 0x000002BF

	thumb_func_start FUN_0204F858
FUN_0204F858: ; 0x0204F858
	push {r3, lr}
	ldr r0, _0204F884 ; =UNK_021C5A68
	ldr r2, [r0, #0x0]
	ldr r0, _0204F888 ; =0x000002BF
	ldrb r1, [r2, r0]
	cmp r1, #0x0
	bne _0204F880
	sub r0, r0, #0x1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	beq _0204F880
	bl FUN_02031190
	bl MOD12_0223E734
	cmp r0, #0x0
	bne _0204F880
	mov r0, #0x0
	bl FUN_0204D628
_0204F880:
	pop {r3, pc}
	nop
_0204F884: .word UNK_021C5A68
_0204F888: .word 0x000002BF

	thumb_func_start FUN_0204F88C
FUN_0204F88C: ; 0x0204F88C
	push {r3-r7, lr}
	sub sp, #0x10
	ldr r0, _0204F908 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0204F902
	mov r6, #0x0
	add r4, r6, #0x0
	add r5, r6, #0x0
_0204F89E:
	ldr r0, _0204F908 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	cmp r0, #0x0
	beq _0204F8F8
	bl FUN_02031190
	cmp r6, r0
	beq _0204F8F8
	ldr r0, _0204F908 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	bl FUN_020553A0
	ldr r1, _0204F908 ; =UNK_021C5A68
	str r0, [sp, #0xc]
	ldr r1, [r1, #0x0]
	add r1, r1, r5
	add r2, r1, #0x0
	add r2, #0xa2
	ldrh r2, [r2, #0x0]
	str r2, [sp, #0x8]
	add r2, r1, #0x0
	add r2, #0xa4
	ldrh r7, [r2, #0x0]
	mov r2, #0xa6
	ldrsb r1, [r1, r2]
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x8]
	bl FUN_02058B30
	ldr r0, [sp, #0xc]
	add r1, r7, #0x0
	bl FUN_02058B50
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xc]
	mov r2, #0x0
	add r3, r7, #0x0
	bl FUN_02058E28
_0204F8F8:
	add r6, r6, #0x1
	add r4, r4, #0x4
	add r5, #0x8
	cmp r6, #0x8
	blt _0204F89E
_0204F902:
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_0204F908: .word UNK_021C5A68

	thumb_func_start FUN_0204F90C
FUN_0204F90C: ; 0x0204F90C
	push {r4-r5}
	mov r3, #0xff
	mov r4, #0x0
	add r0, r3, #0x0
	ldr r1, _0204F92C ; =UNK_021C5A68
	add r5, r4, #0x0
	add r0, #0x6b
_0204F91A:
	ldr r2, [r1, #0x0]
	add r4, r4, #0x1
	add r2, r2, r5
	add r5, #0x22
	strh r3, [r2, r0]
	cmp r4, #0x8
	blt _0204F91A
	pop {r4-r5}
	bx lr
	.balign 4
_0204F92C: .word UNK_021C5A68

	thumb_func_start FUN_0204F930
FUN_0204F930: ; 0x0204F930
	push {r3-r5, lr}
	ldr r0, _0204F9B0 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0204F9B4 ; =0x000002B9
	strb r2, [r1, r0]
	bl FUN_02031190
	ldr r1, _0204F9B0 ; =UNK_021C5A68
	lsl r0, r0, #0x2
	ldr r1, [r1, #0x0]
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204F96E
	bl FUN_02031190
	ldr r1, _0204F9B0 ; =UNK_021C5A68
	add r3, r0, #0x0
	ldr r2, [r1, #0x0]
	lsl r1, r3, #0x2
	add r2, r2, r1
	mov r1, #0x29
	lsl r1, r1, #0x4
	ldr r1, [r2, r1]
	mov r0, #0x5b
	bl FUN_020311D0
	pop {r3-r5, pc}
_0204F96E:
	mov r0, #0xf
	bl PlayerProfile_new
	add r4, r0, #0x0
	mov r0, #0x14
	mov r1, #0xf
	bl String_ctor
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _0204F988
	bl GF_AssertFail
_0204F988:
	cmp r5, #0x0
	bne _0204F990
	bl GF_AssertFail
_0204F990:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl PlayerName_StringToFlat
	mov r0, #0x5b
	add r1, r4, #0x0
	bl FUN_020311D0
	add r0, r5, #0x0
	bl String_dtor
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r3-r5, pc}
	nop
_0204F9B0: .word UNK_021C5A68
_0204F9B4: .word 0x000002B9

	thumb_func_start FUN_0204F9B8
FUN_0204F9B8: ; 0x0204F9B8
	mov r0, #0x20
	bx lr

	thumb_func_start FUN_0204F9BC
FUN_0204F9BC: ; 0x0204F9BC
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, sp, #0x4
	strb r5, [r0, #0x0]
	ldr r0, _0204FA54 ; =UNK_021C5A68
	add r6, r2, #0x0
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0204FA4C
	ldr r1, _0204FA58 ; =0x0000014A
	mov r0, #0x22
	add r4, r5, #0x0
	mul r4, r0
	add r1, r2, r1
	add r0, r6, #0x0
	add r1, r1, r4
	bl PlayerProfile_Copy
	add r0, r6, #0x0
	mov r1, #0xf
	bl PlayerProfile_GetPlayerName_NewString
	str r0, [sp, #0x0]
	bl StringGetLength
	cmp r0, #0x0
	beq _0204F9FE
	ldr r0, _0204FA54 ; =UNK_021C5A68
	ldr r0, [r0, #0x0]
	add r1, r0, r4
	ldr r0, _0204FA5C ; =0x0000016A
	strh r5, [r1, r0]
_0204F9FE:
	mov r4, #0x0
	ldr r6, _0204FA54 ; =UNK_021C5A68
	ldr r7, _0204FA5C ; =0x0000016A
	add r5, r4, #0x0
_0204FA06:
	ldr r0, [r6, #0x0]
	add r1, r0, r5
	ldrh r0, [r1, r7]
	cmp r0, #0xff
	beq _0204FA26
	ldr r0, _0204FA5C ; =0x0000016A
	strh r4, [r1, r0]
	mov r0, #0x5c
	add r1, r0, #0x0
	ldr r2, [r6, #0x0]
	add r1, #0xee
	add r1, r2, r1
	add r1, r1, r5
	mov r2, #0x22
	bl FUN_02030B3C
_0204FA26:
	add r4, r4, #0x1
	add r5, #0x22
	cmp r4, #0x8
	blt _0204FA06
	mov r0, #0x5d
	add r1, sp, #0x4
	mov r2, #0x1
	bl FUN_02030BC4
	ldr r0, [sp, #0x0]
	bl String_dtor
	ldr r0, _0204FA54 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204FA60 ; =0x000002C2
	add sp, #0x8
	strb r2, [r1, r0]
	pop {r3-r7, pc}
_0204FA4C:
	bl GF_AssertFail
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_0204FA54: .word UNK_021C5A68
_0204FA58: .word 0x0000014A
_0204FA5C: .word 0x0000016A
_0204FA60: .word 0x000002C2

	thumb_func_start FUN_0204FA64
FUN_0204FA64: ; 0x0204FA64
	ldr r0, _0204FA70 ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204FA74 ; =0x0000025A
	add r0, r1, r0
	bx lr
	nop
_0204FA70: .word UNK_021C5A68
_0204FA74: .word 0x0000025A

	thumb_func_start FUN_0204FA78
FUN_0204FA78: ; 0x0204FA78
	push {r4-r6, lr}
	ldr r0, _0204FAC8 ; =UNK_021C5A68
	add r6, r2, #0x0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0204FAC4
	ldrh r5, [r6, #0x20]
	lsl r0, r5, #0x2
	add r1, r1, r0
	mov r0, #0x29
	lsl r0, r0, #0x4
	ldr r0, [r1, r0]
	cmp r0, #0x0
	beq _0204FA98
	bl FreeToHeap
_0204FA98:
	mov r0, #0xf
	lsl r4, r5, #0x2
	bl PlayerProfile_new
	ldr r2, _0204FAC8 ; =UNK_021C5A68
	ldr r1, [r2, #0x0]
	add r3, r1, r4
	mov r1, #0x29
	lsl r1, r1, #0x4
	str r0, [r3, r1]
	ldr r2, [r2, #0x0]
	add r0, r6, #0x0
	add r2, r2, r4
	ldr r1, [r2, r1]
	bl PlayerProfile_Copy
	ldr r0, _0204FAC8 ; =UNK_021C5A68
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0xfa
	strb r1, [r0, #0x0]
_0204FAC4:
	pop {r4-r6, pc}
	nop
_0204FAC8: .word UNK_021C5A68

	thumb_func_start FUN_0204FACC
FUN_0204FACC: ; 0x0204FACC
	mov r0, #0x22
	bx lr

	thumb_func_start FUN_0204FAD0
FUN_0204FAD0: ; 0x0204FAD0
	push {r4, lr}
	add r4, r2, #0x0
	bl FUN_02031190
	ldrb r1, [r4, #0x0]
	cmp r1, r0
	bne _0204FAE8
	ldr r0, _0204FAF4 ; =UNK_021C5A68
	mov r2, #0x1
	ldr r1, [r0, #0x0]
	ldr r0, _0204FAF8 ; =0x000002B9
	strb r2, [r1, r0]
_0204FAE8:
	ldr r0, _0204FAF4 ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0204FAFC ; =0x000002C2
	strb r2, [r1, r0]
	pop {r4, pc}
	.balign 4
_0204FAF4: .word UNK_021C5A68
_0204FAF8: .word 0x000002B9
_0204FAFC: .word 0x000002C2

	thumb_func_start FUN_0204FB00
FUN_0204FB00: ; 0x0204FB00
	ldr r0, _0204FB0C ; =UNK_021C5A68
	ldr r1, [r0, #0x0]
	ldr r0, _0204FB10 ; =0x000002B9
	ldrb r0, [r1, r0]
	bx lr
	nop
_0204FB0C: .word UNK_021C5A68
_0204FB10: .word 0x000002B9

	thumb_func_start FUN_0204FB14
FUN_0204FB14: ; 0x0204FB14
	ldr r0, _0204FB24 ; =UNK_021C5A68
	mov r2, #0x8
	ldr r1, [r0, #0x0]
	mov r0, #0xb
	lsl r0, r0, #0x6
	strb r2, [r1, r0]
	bx lr
	nop
_0204FB24: .word UNK_021C5A68

	thumb_func_start FUN_0204FB28
FUN_0204FB28: ; 0x0204FB28
	push {r3-r5, lr}
	mov r4, #0x0
	bl FUN_02031190
	ldr r2, _0204FB9C ; =UNK_021C5A68
	lsl r1, r0, #0x2
	ldr r3, [r2, #0x0]
	add r5, r3, r1
	mov r1, #0x29
	lsl r1, r1, #0x4
	ldr r3, [r5, r1]
	cmp r3, #0x0
	beq _0204FB60
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [r5, r1]
	ldr r1, [r2, #0x0]
	add r1, r1, r0
	add r1, #0xfa
	strb r3, [r1, #0x0]
	ldr r3, [r2, #0x0]
	mov r2, #0x22
	mul r2, r0
	mov r1, #0xff
	add r0, r1, #0x0
	add r2, r3, r2
	add r0, #0x6b
	strh r1, [r2, r0]
_0204FB60:
	mov r5, #0x0
_0204FB62:
	add r0, r5, #0x0
	bl FUN_0204ED9C
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _0204FB62
	cmp r4, #0x0
	beq _0204FB9A
	ldr r1, _0204FB9C ; =UNK_021C5A68
	mov r0, #0x29
	ldr r2, [r1, #0x0]
	lsl r0, r0, #0x4
	str r4, [r2, r0]
	ldr r0, [r1, #0x0]
	mov r2, #0x1
	add r0, #0xfa
	strb r2, [r0, #0x0]
	ldr r2, [r1, #0x0]
	ldr r1, _0204FBA0 ; =0x0000014A
	add r0, r4, #0x0
	add r1, r2, r1
	bl PlayerProfile_Copy
	ldr r0, _0204FB9C ; =UNK_021C5A68
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	ldr r0, _0204FBA4 ; =0x0000016A
	strh r2, [r1, r0]
_0204FB9A:
	pop {r3-r5, pc}
	.balign 4
_0204FB9C: .word UNK_021C5A68
_0204FBA0: .word 0x0000014A
_0204FBA4: .word 0x0000016A
