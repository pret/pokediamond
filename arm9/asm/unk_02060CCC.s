    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_02105FBC

	.section .rodata

	.global UNK_020F7650
UNK_020F7650: ; 0x020F7650
	.byte 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00

	.global UNK_020F7658
UNK_020F7658: ; 0x020F7658
	.short 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007
	.short 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F
	.short 0x0010, 0x0011

	.global UNK_020F767C
UNK_020F767C: ; 0x020F767C
	.word 1
	.byte 0x6D, 0x01, 0x0E
	.word UNK_020F76F4
	.word 2
	.byte 0x6E, 0x01, 0x19
	.word UNK_020F77E4
	.word 3
	.byte 0x6F, 0x01, 0x0A
	.word UNK_020F76AC
	.word 4
	.byte 0x70, 0x01, 0x12
	.word UNK_020F775C

	.global UNK_020F76AC
UNK_020F76AC: ; 0x020F76AC
	.word FUN_0206193C, FUN_02061990, 0x00000000, 0x00000000
	.word FUN_020619F0, FUN_02061A70, FUN_02061AB0, 0x00000000
	.word 0x00000000, 0x00000000, FUN_02061750, 0x00000000
	.word 0x00000000, 0x00000000, FUN_02061B24, FUN_02061BB4
	.word FUN_02061B80, FUN_02061BB4

	.global UNK_020F76F4
UNK_020F76F4: ; 0x020F76F4
	.word 0x00000000, 0x00000000, FUN_02061C00, FUN_02061C48
	.word 0x00000000, 0x00000000, FUN_02061CA8, FUN_02061D30
	.word 0x00000000, 0x00000000, FUN_02061D74, 0x00000000
	.word FUN_02061DE4, FUN_02061E60, 0x00000000, 0x00000000
	.word FUN_02061EAC, FUN_02061EDC, FUN_02061F0C, 0x00000000
	.word FUN_02061F60, 0x00000000, 0x00000000, 0x00000000
	.word FUN_02061FF8, 0x00000000

	.global UNK_020F775C
UNK_020F775C: ; 0x020F775C
	.word FUN_020620A0, FUN_02062158, FUN_02062170, FUN_0206223C
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word FUN_02062240, FUN_02062280, 0x00000000, 0x00000000
	.word FUN_020622C4, FUN_02062348, 0x00000000, 0x00000000
	.word FUN_020623F4, FUN_02062460, 0x00000000, 0x00000000
	.word FUN_02062474, FUN_02062508, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word FUN_0206252C, FUN_020625D4

	.global UNK_020F77E4
UNK_020F77E4: ; 0x020F77E4
	.word FUN_020610F8, FUN_020611E8, FUN_020611A8, 0x00000000
	.word FUN_0206123C, FUN_02061288, FUN_02061304, 0x00000000
	.word 0x00000000, 0x00000000, FUN_0206139C, 0x00000000
	.word 0x00000000, 0x00000000, FUN_02061404, FUN_02061444
	.word 0x00000000, 0x00000000, FUN_02061498, FUN_020614FC
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word FUN_02061534, FUN_020618EC, 0x00000000, 0x00000000
	.word FUN_020615B0, FUN_020615F8, 0x00000000, 0x00000000
	.word FUN_02061648, FUN_02061688, FUN_020616E8, 0x00000000
	.word FUN_02061728, 0x00000000, FUN_0206133C, 0x00000000
	.word FUN_020617D8, FUN_02061834, FUN_020618D4, FUN_020618EC
	.word FUN_020618E0, FUN_020618EC, 0x00000000, 0x00000000

	.global UNK_020F78A4
UNK_020F78A4: ; 0x020F78A4
	.byte 0x00, 0x05

	.global UNK_020F78A6
UNK_020F78A6: ; 0x020F78A6
	.byte 0x01, 0x00, 0x08, 0x01, 0x0A, 0x0A, 0x01, 0x0A, 0x0B, 0x01, 0x0A, 0x0C, 0x02, 0x0A, 0x0F, 0x02
	.byte 0x0A, 0x06, 0x02, 0x0A, 0x05, 0x01, 0x0A, 0x10, 0x01, 0x0A, 0x08, 0x02, 0x0B, 0x0A, 0x02, 0x0B
	.byte 0x0B, 0x01, 0x0B, 0x0C, 0x01, 0x0B, 0x04, 0x02, 0x0B, 0x05, 0x02, 0x0B, 0x10, 0x01, 0x0D, 0x0B
	.byte 0x02, 0x0D, 0x0D, 0x01, 0x0D, 0x0C, 0x01, 0x0D, 0x04, 0x00, 0x0D, 0x02, 0x02, 0x0D, 0x10, 0x01
	.byte 0x0C, 0x0A, 0x01, 0x0C, 0x0B, 0x02, 0x0C, 0x0C, 0x01, 0x0C, 0x03, 0x01, 0x0C, 0x04, 0x02, 0x0C
	.byte 0x02, 0x01, 0x0C, 0x06, 0x01, 0x0C, 0x05, 0x02, 0x0C, 0x10, 0x01, 0x0C, 0x08, 0x01, 0x0F, 0x0B
	.byte 0x01, 0x0F, 0x0C, 0x02, 0x0F, 0x0F, 0x01, 0x0F, 0x04, 0x02, 0x0F, 0x02, 0x02, 0x0F, 0x10, 0x02
	.byte 0x0F, 0x08, 0x01, 0x0F, 0x0A, 0x01, 0x01, 0x00, 0x02, 0x01, 0x0F, 0x02, 0x01, 0x03, 0x01, 0x01
	.byte 0x02, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x06, 0x01, 0x01, 0x05, 0x02, 0x01, 0x11, 0x02, 0x01, 0x08
	.byte 0x02, 0x03, 0x0C, 0x02, 0x03, 0x03, 0x01, 0x03, 0x04, 0x01, 0x03, 0x05, 0x01, 0x03, 0x07, 0x01
	.byte 0x03, 0x08, 0x00, 0x04, 0x0A, 0x02, 0x04, 0x0D, 0x02, 0x04, 0x0C, 0x01, 0x04, 0x03, 0x02, 0x04
	.byte 0x02, 0x00, 0x04, 0x06, 0x01, 0x04, 0x05, 0x02, 0x04, 0x08, 0x02, 0x02, 0x0D, 0x01, 0x02, 0x0C
	.byte 0x02, 0x02, 0x01, 0x02, 0x02, 0x06, 0x02, 0x02, 0x05, 0x01, 0x02, 0x08, 0x01, 0x0E, 0x01, 0x02
	.byte 0x0E, 0x03, 0x02, 0x0E, 0x0E, 0x01, 0x0E, 0x11, 0x00, 0x0E, 0x08, 0x01, 0x06, 0x0A, 0x01, 0x06
	.byte 0x0C, 0x02, 0x06, 0x01, 0x01, 0x06, 0x03, 0x01, 0x06, 0x02, 0x01, 0x06, 0x0E, 0x02, 0x06, 0x07
	.byte 0x01, 0x06, 0x11, 0x02, 0x06, 0x08, 0x01, 0x05, 0x0A, 0x02, 0x05, 0x0F, 0x02, 0x05, 0x01, 0x01
	.byte 0x05, 0x04, 0x01, 0x05, 0x02, 0x02, 0x05, 0x06, 0x02, 0x05, 0x08, 0x01, 0x07, 0x00, 0x00, 0x07
	.byte 0x0E, 0x02, 0x07, 0x11, 0x01, 0x07, 0x08, 0x01, 0x07, 0x07, 0x02, 0x10, 0x10, 0x02, 0x10, 0x08
	.byte 0x01, 0x11, 0x01, 0x01, 0x11, 0x0E, 0x02, 0x11, 0x07, 0x02, 0x11, 0x11, 0x01, 0x11, 0x08, 0x01
	.byte 0x08, 0x0A, 0x01, 0x08, 0x0B, 0x01, 0x08, 0x0D, 0x01, 0x08, 0x0F, 0x02, 0x08, 0x05, 0x02, 0x08
	.byte 0x08, 0x01, 0x00, 0x07, 0x00, 0x01, 0x07, 0x00

	.global UNK_020F79EE
UNK_020F79EE: ; 0x020F79EE
	.byte 0x02, 0x00, 0xAA, 0x01, 0x02, 0x00, 0xAA, 0x01, 0x02, 0x00, 0x5B, 0x01, 0x02, 0x00, 0x5B, 0x01
	.byte 0x02, 0x00, 0x5B, 0x01, 0x02, 0x00, 0x5B, 0x01, 0x02, 0x00, 0xCA, 0x00, 0x02, 0x00, 0xCA, 0x00
	.byte 0x02, 0x00, 0xCA, 0x00, 0x02, 0x00, 0xCA, 0x00, 0x04, 0x00, 0xCC, 0x00, 0x04, 0x00, 0xCC, 0x00
	.byte 0x04, 0x00, 0xCC, 0x00, 0x04, 0x00, 0xCC, 0x00, 0x02, 0x00, 0x5D, 0x01, 0x02, 0x00, 0x5D, 0x01
	.byte 0x02, 0x00, 0x5D, 0x01, 0x02, 0x00, 0x5D, 0x01, 0x09, 0x00, 0x5E, 0x01, 0x09, 0x00, 0x5E, 0x01
	.byte 0x09, 0x00, 0x5E, 0x01, 0x09, 0x00, 0x5E, 0x01, 0x09, 0x00, 0x61, 0x01, 0x09, 0x00, 0x61, 0x01
	.byte 0x09, 0x00, 0x61, 0x01, 0x09, 0x00, 0x61, 0x01, 0x09, 0x00, 0x62, 0x01, 0x09, 0x00, 0x62, 0x01
	.byte 0x09, 0x00, 0x62, 0x01, 0x09, 0x00, 0x62, 0x01, 0x0B, 0x00, 0x64, 0x01, 0x0B, 0x00, 0x64, 0x01
	.byte 0x0B, 0x00, 0x64, 0x01, 0x0B, 0x00, 0x64, 0x01, 0x03, 0x00, 0xB1, 0x01, 0x03, 0x00, 0xB1, 0x01
	.byte 0x03, 0x00, 0xB1, 0x01, 0x03, 0x00, 0xB1, 0x01, 0x03, 0x00, 0x6A, 0x01, 0x03, 0x00, 0x6A, 0x01
	.byte 0x03, 0x00, 0x6A, 0x01, 0x03, 0x00, 0x6A, 0x01, 0x04, 0x00, 0x6B, 0x01, 0x04, 0x00, 0x6B, 0x01
	.byte 0x04, 0x00, 0x6B, 0x01, 0x04, 0x00, 0x6B, 0x01, 0x04, 0x00, 0x6E, 0x01, 0x04, 0x00, 0x6E, 0x01
	.byte 0x04, 0x00, 0x6E, 0x01, 0x04, 0x00, 0x6E, 0x01, 0x0B, 0x00, 0x6F, 0x01, 0x0B, 0x00, 0x6F, 0x01
	.byte 0x0B, 0x00, 0x6F, 0x01, 0x0B, 0x00, 0x6F, 0x01, 0x0C, 0x00, 0x73, 0x01, 0x0C, 0x00, 0x73, 0x01
	.byte 0x0C, 0x00, 0x73, 0x01, 0x0C, 0x00, 0x73, 0x01, 0x0C, 0x00, 0x78, 0x00, 0x0C, 0x00, 0x78, 0x00
	.byte 0x0C, 0x00, 0x78, 0x00, 0x0C, 0x00, 0x78, 0x00, 0x0C, 0x00, 0x75, 0x01, 0x0C, 0x00, 0x75, 0x01
	.byte 0x0C, 0x00, 0x75, 0x01, 0x0C, 0x00, 0x75, 0x01, 0x0D, 0x00, 0x7C, 0x01, 0x0D, 0x00, 0x7C, 0x01
	.byte 0x0D, 0x00, 0x7C, 0x01, 0x0D, 0x00, 0x7C, 0x01, 0x0D, 0x00, 0x7E, 0x01, 0x0D, 0x00, 0x7E, 0x01
	.byte 0x0D, 0x00, 0x7E, 0x01, 0x0D, 0x00, 0x7E, 0x01, 0x04, 0x00, 0x84, 0x01, 0x04, 0x00, 0x84, 0x01
	.byte 0x04, 0x00, 0x84, 0x01, 0x04, 0x00, 0x84, 0x01, 0x04, 0x00, 0x88, 0x01, 0x04, 0x00, 0x88, 0x01
	.byte 0x04, 0x00, 0x88, 0x01, 0x04, 0x00, 0x88, 0x01, 0x0D, 0x00, 0x8B, 0x01, 0x0D, 0x00, 0x8B, 0x01
	.byte 0x0D, 0x00, 0x8B, 0x01, 0x0D, 0x00, 0x8B, 0x01, 0x10, 0x00, 0x8F, 0x01, 0x10, 0x00, 0x8F, 0x01
	.byte 0x10, 0x00, 0x8F, 0x01, 0x10, 0x00, 0x8F, 0x01, 0x11, 0x00, 0xBC, 0x00, 0x11, 0x00, 0xBC, 0x00
	.byte 0x11, 0x00, 0xBC, 0x00, 0x11, 0x00, 0xBC, 0x00, 0x11, 0x00, 0x90, 0x01, 0x11, 0x00, 0x90, 0x01
	.byte 0x11, 0x00, 0x90, 0x01, 0x11, 0x00, 0x90, 0x01, 0x05, 0x00, 0xD5, 0x01, 0x05, 0x00, 0xD5, 0x01
	.byte 0x05, 0x00, 0xD5, 0x01, 0x05, 0x00, 0xD5, 0x01, 0x05, 0x00, 0x96, 0x01, 0x05, 0x00, 0x96, 0x01
	.byte 0x05, 0x00, 0x96, 0x01, 0x05, 0x00, 0x96, 0x01, 0x05, 0x00, 0x97, 0x01, 0x05, 0x00, 0x97, 0x01
	.byte 0x05, 0x00, 0x97, 0x01, 0x05, 0x00, 0x97, 0x01, 0x06, 0x00, 0xC9, 0x01, 0x06, 0x00, 0xC9, 0x01
	.byte 0x06, 0x00, 0xC9, 0x01, 0x06, 0x00, 0xC9, 0x01, 0x05, 0x00, 0xD7, 0x01, 0x05, 0x00, 0xD7, 0x01
	.byte 0x05, 0x00, 0xD7, 0x01, 0x05, 0x00, 0xD7, 0x01, 0x00, 0x00

	.section .data

	.global UNK_02105FBC
UNK_02105FBC: ; 0x02105FBC
	.byte 0x73, 0x01, 0x75, 0x01, 0x7F, 0x01, 0x54, 0x01, 0xA5, 0x00, 0x00, 0x00

	.text

	thumb_func_start FUN_02060CCC
FUN_02060CCC: ; 0x02060CCC
	push {r4-r6, lr}
	add r5, r0, #0x0
	cmp r5, #0x0
	ble _02060CD8
	cmp r5, #0x5
	blt _02060CDC
_02060CD8:
	bl ErrorHandling
_02060CDC:
	sub r1, r5, #0x1
	ldr r6, _02060CF4 ; =UNK_020F767C
	mov r0, #0xc
	add r4, r1, #0x0
	mul r4, r0
	ldr r0, [r6, r4]
	cmp r0, r5
	beq _02060CF0
	bl ErrorHandling
_02060CF0:
	add r0, r6, r4
	pop {r4-r6, pc}
	.balign 4
_02060CF4: .word UNK_020F767C

	thumb_func_start FUN_02060CF8
FUN_02060CF8: ; 0x02060CF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B6C
	add r4, r0, #0x0
	cmp r4, #0x0
	ble _02060D0E
	ldrh r0, [r5, #0x6]
	cmp r4, r0
	blt _02060D12
_02060D0E:
	bl ErrorHandling
_02060D12:
	sub r0, r4, #0x1
	ldr r1, [r5, #0x8]
	lsl r0, r0, #0x3
	add r0, r1, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_02060D1C
FUN_02060D1C: ; 0x02060D1C
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r5, r3, #0x0
	bl FUN_02060CCC
	ldrh r2, [r0, #0x4]
	ldr r1, [sp, #0x18]
	strh r2, [r1, #0x0]
	add r1, r5, #0x0
	bl FUN_02060CF8
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	bne _02060D3E
	bl ErrorHandling
_02060D3E:
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, r5, #0x0
	blx r4
	pop {r3-r7, pc}

	thumb_func_start FUN_02060D48
FUN_02060D48: ; 0x02060D48
	push {r3-r5, lr}
	add r4, r2, #0x0
	add r5, r1, #0x0
	bl FUN_02060CCC
	add r1, r4, #0x0
	bl FUN_02060CF8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _02060D62
	mov r0, #0x0
	pop {r3-r5, pc}
_02060D62:
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	bne _02060D6C
	mov r0, #0x1
	pop {r3-r5, pc}
_02060D6C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	blx r2
	pop {r3-r5, pc}

	thumb_func_start FUN_02060D74
FUN_02060D74: ; 0x02060D74
	push {r4-r6, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02022504
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_0202B4B0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02060D90
FUN_02060D90: ; 0x02060D90
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	mov r0, #0x40
	mov r1, #0x4
	str r3, [sp, #0x8]
	bl String_ctor
	add r1, r7, #0x0
	add r4, r0, #0x0
	bl CopyU16ArrayToString
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl String_dtor
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02060DCC
FUN_02060DCC: ; 0x02060DCC
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	add r4, r1, #0x0
	bl MOD06_02248B5C
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B54
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	bl MOD06_02248B58
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_02060D90
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02060E04
FUN_02060E04: ; 0x02060E04
	push {r4-r6, lr}
	add r3, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x40
	add r1, r3, #0x0
	add r6, r2, #0x0
	bl String_ctor
	add r4, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x76
	add r2, r4, #0x0
	bl GetMonData
	add r0, r4, #0x0
	add r1, r5, #0x0
	mov r2, #0xb
	bl CopyStringToU16Array
	add r0, r4, #0x0
	bl String_dtor
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02060E34
FUN_02060E34: ; 0x02060E34
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r5, r0, #0x0
	mov r1, #0x5
	mov r2, #0x0
	add r7, r3, #0x0
	bl GetMonData
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x6f
	mov r2, #0x0
	bl GetMonData
	strb r0, [r6, #0x0]
	add r0, r5, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl GetMonData
	strb r0, [r7, #0x0]
	add r0, r5, #0x0
	mov r1, #0x79
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x18]
	strb r0, [r1, #0x0]
	pop {r3-r7, pc}

	thumb_func_start FUN_02060E70
FUN_02060E70: ; 0x02060E70
	push {r4-r6, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x4
	add r2, sp, #0x8
	add r6, r3, #0x0
	bl GetSpeciesNameIntoArray
	add r0, sp, #0x20
	ldrb r0, [r0, #0x10]
	add r1, r4, #0x0
	add r2, sp, #0x8
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r3, r6, #0x0
	bl FUN_02060D90
	add sp, #0x20
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02060EA0
FUN_02060EA0: ; 0x02060EA0
	push {r3-r5, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x4
	add r2, sp, #0x8
	bl GetSpeciesNameIntoArray
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, sp, #0x8
	mov r3, #0x0
	bl FUN_02060D90
	add sp, #0x20
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02060ECC
FUN_02060ECC: ; 0x02060ECC
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, r2, #0x0
	add r0, r5, #0x0
	mov r1, #0x4d
	mov r2, #0x0
	add r7, r3, #0x0
	bl GetMonData
	strb r0, [r4, #0x0]
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02060F0C
	mov r0, #0x40
	add r1, r6, #0x0
	bl String_ctor
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x76
	add r2, r4, #0x0
	bl GetMonData
	add r0, r4, #0x0
	add r1, r7, #0x0
	mov r2, #0xb
	bl CopyStringToU16Array
	add r0, r4, #0x0
	bl String_dtor
_02060F0C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02060F10
FUN_02060F10: ; 0x02060F10
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r6, r3, #0x0
	bl FUN_0202B838
	add r4, r0, #0x0
	mov r0, #0x1
	strb r0, [r4, #0x0]
	add r0, r4, #0x6
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	add r1, r4, #0x2
	add r2, r4, #0x4
	add r3, r4, #0x5
	bl FUN_02060E34
	strb r5, [r4, #0x8]
	ldr r0, [sp, #0x18]
	strb r6, [r4, #0x7]
	strb r0, [r4, #0x9]
	pop {r3-r7, pc}

	thumb_func_start FUN_02060F3C
FUN_02060F3C: ; 0x02060F3C
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_0202B844
	add r4, r0, #0x0
	mov r0, #0x1
	strb r0, [r4, #0x0]
	mov r0, #0x0
	strb r0, [r4, #0x1f]
	add r0, r5, #0x0
	bl GetMonNature
	strb r0, [r4, #0x1e]
	add r0, r4, #0x6
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x2
	add r2, r4, #0x4
	add r3, r4, #0x5
	bl FUN_02060E34
	add r0, r5, #0x0
	mov r1, #0x4d
	mov r2, #0x0
	bl GetMonData
	strb r0, [r4, #0x7]
	add r2, r4, #0x7
	add r4, #0x8
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r3, r4, #0x0
	bl FUN_02060ECC
	add sp, #0x4
	pop {r3-r6, pc}

	thumb_func_start FUN_02060F88
FUN_02060F88: ; 0x02060F88
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0202B844
	mov r1, #0x2
	strb r1, [r0, #0x1f]
	add r0, #0x20
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02060F9C
FUN_02060F9C: ; 0x02060F9C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0202B844
	mov r1, #0x1
	strb r1, [r0, #0x1f]
	strh r4, [r0, #0x22]
	pop {r4, pc}

	thumb_func_start FUN_02060FAC
FUN_02060FAC: ; 0x02060FAC
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0202B850
	mov r1, #0x1
	strb r1, [r0, #0x0]
	strb r4, [r0, #0x1]
	pop {r4, pc}

	thumb_func_start FUN_02060FBC
FUN_02060FBC: ; 0x02060FBC
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_0202B85C
	mov r1, #0x1
	strb r1, [r0, #0x0]
	strb r5, [r0, #0x1]
	strh r4, [r0, #0x2]
	pop {r3-r5, pc}

	thumb_func_start FUN_02060FD0
FUN_02060FD0: ; 0x02060FD0
	push {r3, lr}
	bl FUN_0202B868
	mov r1, #0x1
	strb r1, [r0, #0x0]
	mov r1, #0x0
	strb r1, [r0, #0x7]
	pop {r3, pc}

	thumb_func_start FUN_02060FE0
FUN_02060FE0: ; 0x02060FE0
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_0202B868
	add r4, r0, #0x0
	ldrb r0, [r4, #0x7]
	cmp r0, #0x0
	bne _02061000
	add r0, r4, #0x6
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x2
	add r2, r4, #0x4
	add r3, r4, #0x5
	bl FUN_02060E34
_02061000:
	ldrb r0, [r4, #0x7]
	add r0, r0, #0x1
	strb r0, [r4, #0x7]
	pop {r3-r5, pc}

	thumb_func_start FUN_02061008
FUN_02061008: ; 0x02061008
	push {r4, lr}
	mov r1, #0x24
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r4, #0x0
	mov r2, #0x24
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02061020
FUN_02061020: ; 0x02061020
	ldr r3, _02061024 ; =FreeToHeap
	bx r3
	.balign 4
_02061024: .word FreeToHeap

	thumb_func_start FUN_02061028
FUN_02061028: ; 0x02061028
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	mov r0, #0x0
	add r1, r5, #0x0
	mov r2, #0x24
	add r7, r3, #0x0
	bl MIi_CpuClear32
	str r6, [r5, #0x0]
	add r0, r5, #0x0
	add r2, r5, #0x0
	add r3, r5, #0x0
	strh r7, [r5, #0x4]
	add r0, #0xa
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, r5, #0x6
	add r2, #0x8
	add r3, #0x9
	bl FUN_02060E34
	add r0, r4, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x22]
	ldrh r0, [r5, #0x22]
	cmp r0, #0x0
	bne _0206106C
	bl ErrorHandling
_0206106C:
	add r2, r5, #0x0
	add r5, #0xc
	ldr r0, [sp, #0x18]
	add r1, r4, #0x0
	add r2, #0xb
	add r3, r5, #0x0
	bl FUN_02060ECC
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02061080
FUN_02061080: ; 0x02061080
	push {r3-r7, lr}
	sub sp, #0x28
	add r7, sp, #0x0
	add r5, r2, #0x0
	add r6, r0, #0x0
	add r3, r1, #0x0
	add r4, r7, #0x0
	mov r2, #0x4
_02061090:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _02061090
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	str r5, [sp, #0x0]
	add r0, sp, #0x0
	ldrh r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020610F0
	ldrh r1, [r7, #0x4]
	ldr r0, _020610F4 ; =0x000003E7
	cmp r1, r0
	bls _020610B0
	strh r0, [r7, #0x4]
_020610B0:
	cmp r5, #0x6
	bhi _020610F0
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020610C0: ; jump table (using 16-bit offset)
	.short _020610F0 - _020610C0 - 2; case 0
	.short _020610DE - _020610C0 - 2; case 1
	.short _020610F0 - _020610C0 - 2; case 2
	.short _020610F0 - _020610C0 - 2; case 3
	.short _020610CE - _020610C0 - 2; case 4
	.short _020610DE - _020610C0 - 2; case 5
	.short _020610DE - _020610C0 - 2; case 6
_020610CE:
	add r0, r6, #0x0
	mov r1, #0x2
	mov r2, #0x1
	add r3, r7, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r7, pc}
_020610DE:
	ldrh r0, [r7, #0x4]
	cmp r0, #0x2
	bls _020610F0
	mov r1, #0x2
	add r0, r6, #0x0
	add r2, r1, #0x0
	add r3, r7, #0x0
	bl FUN_02060D74
_020610F0:
	add sp, #0x28
	pop {r3-r7, pc}
	.balign 4
_020610F4: .word 0x000003E7

	thumb_func_start FUN_020610F8
FUN_020610F8: ; 0x020610F8
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldrb r0, [r4, #0xb]
	cmp r0, #0x0
	beq _02061166
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x9]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0xa]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x6]
	ldrb r3, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrh r2, [r4, #0x22]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200AE38
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x3
	ldrh r2, [r4, #0x4]
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_0200AD38
	ldrb r0, [r4, #0x9]
	add r2, r4, #0x0
	mov r1, #0x4
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrb r3, [r4, #0x8]
	add r0, r5, #0x0
	add r2, #0xc
	bl FUN_02060D90
	add sp, #0x8
	mov r0, #0x0
	pop {r4-r6, pc}
_02061166:
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x9]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0xa]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x6]
	ldrb r3, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrh r2, [r4, #0x22]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200AE38
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x3
	ldrh r2, [r4, #0x4]
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_0200AD38
	mov r0, #0x1
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_020611A8
FUN_020611A8: ; 0x020611A8
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	ldrh r2, [r4, #0x4]
	add r0, r5, #0x0
	mov r3, #0x3
	bl FUN_0200AD38
	ldr r0, [r4, #0x0]
	cmp r0, #0x1
	bne _020611E0
	add sp, #0x8
	mov r0, #0x2
	pop {r4-r6, pc}
_020611E0:
	mov r0, #0x3
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020611E8
FUN_020611E8: ; 0x020611E8
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MOD06_02248B60
	add r1, r0, #0x0
	ldrh r1, [r1, #0x6]
	add r0, r4, #0x0
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061208
FUN_02061208: ; 0x02061208
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r1, #0x0
	add r7, r0, #0x0
	add r4, r2, #0x0
	add r6, sp, #0x4
	cmp r5, #0x0
	beq _02061228
	add r0, r6, #0x4
	str r0, [sp, #0x0]
	add r0, r3, #0x0
	add r1, r6, #0x0
	add r2, r6, #0x2
	add r3, r6, #0x3
	bl FUN_02060E34
_02061228:
	strh r4, [r6, #0x6]
	add r0, r7, #0x0
	mov r1, #0x2
	mov r2, #0x3
	add r3, r6, #0x0
	str r5, [r6, #0x8]
	bl FUN_02060D74
	add sp, #0x2c
	pop {r4-r7, pc}

	thumb_func_start FUN_0206123C
FUN_0206123C: ; 0x0206123C
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02061280
	ldrh r2, [r4, #0x6]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200AE38
	ldrb r0, [r4, #0x3]
	mov r1, #0x2
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	add sp, #0x8
	mov r0, #0x4
	pop {r4-r6, pc}
_02061280:
	mov r0, #0x5
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061288
FUN_02061288: ; 0x02061288
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _0206129E
	mov r0, #0x1
	pop {r3-r5, pc}
_0206129E:
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}

	thumb_func_start FUN_020612AC
FUN_020612AC: ; 0x020612AC
	push {r4-r6, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_0202881C
	add r6, r0, #0x0
	mov r0, #0x0
	add r1, sp, #0x0
	mov r2, #0x28
	bl MIi_CpuClearFast
	add r0, r6, #0x0
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_020287A8
	add r1, r0, #0x0
	add r0, sp, #0x0
	mov r2, #0xb
	bl CopyU16StringArrayN
	add r0, r5, #0x0
	mov r1, #0x2
	add r2, r4, #0x0
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020612EC
FUN_020612EC: ; 0x020612EC
	ldr r3, _020612F4 ; =FUN_020612AC
	mov r1, #0x14
	bx r3
	nop
_020612F4: .word FUN_020612AC

	thumb_func_start FUN_020612F8
FUN_020612F8: ; 0x020612F8
	ldr r3, _02061300 ; =FUN_020612AC
	mov r1, #0x4
	bx r3
	nop
_02061300: .word FUN_020612AC

	thumb_func_start FUN_02061304
FUN_02061304: ; 0x02061304
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r0, r4, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl MOD06_02248B58
	str r0, [sp, #0x0]
	mov r1, #0x1
	add r0, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	str r1, [sp, #0x4]
	bl FUN_02060D90
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02060DCC
	mov r0, #0x6
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206133C
FUN_0206133C: ; 0x0206133C
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r0, r4, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl MOD06_02248B58
	str r0, [sp, #0x0]
	mov r1, #0x1
	add r0, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	str r1, [sp, #0x4]
	bl FUN_02060D90
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	bl FUN_02060DCC
	mov r0, #0x20
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061374
FUN_02061374: ; 0x02061374
	push {r4, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	add r1, sp, #0x0
	strh r0, [r1, #0x2]
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x6
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0206139C
FUN_0206139C: ; 0x0206139C
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	mov r1, #0x0
	bl GetLandmarkName
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200AE38
	mov r0, #0xa
	pop {r4-r6, pc}

	thumb_func_start FUN_020613CC
FUN_020613CC: ; 0x020613CC
	push {r3-r4, lr}
	sub sp, #0x2c
	add r4, r0, #0x0
	add r0, sp, #0x8
	add r2, sp, #0x4
	add r3, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r1, #0x0
	add r1, sp, #0x4
	add r2, #0x2
	add r3, #0x3
	bl FUN_02060E34
	ldr r0, [r4, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	add r1, sp, #0x4
	strh r0, [r1, #0x6]
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x8
	add r3, sp, #0x4
	bl FUN_02060D74
	add sp, #0x2c
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02061404
FUN_02061404: ; 0x02061404
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldrh r2, [r4, #0x6]
	add r0, r5, #0x0
	mov r1, #0x1
	bl GetLandmarkName
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x2
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	mov r0, #0xc
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061444
FUN_02061444: ; 0x02061444
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061460
FUN_02061460: ; 0x02061460
	push {r4-r5, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, sp, #0x8
	add r2, sp, #0x4
	add r3, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, #0x2
	add r3, #0x3
	bl FUN_02060E34
	add r1, sp, #0x8
	mov r0, #0x4
	add r1, #0x2
	add r2, r4, #0x0
	bl FUN_02060E04
	add r0, r5, #0x0
	mov r1, #0x2
	mov r2, #0xa
	add r3, sp, #0x4
	bl FUN_02060D74
	add sp, #0x2c
	pop {r4-r5, pc}

	thumb_func_start FUN_02061498
FUN_02061498: ; 0x02061498
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrb r0, [r4, #0x3]
	mov r1, #0x2
	add r2, r4, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060D90
	bl LCRandom
	ldr r1, _020614F8 ; =0x00003334
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x5
	blo _020614F0
	bl ErrorHandling
_020614F0:
	add r4, #0x11
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_020614F8: .word 0x00003334

	thumb_func_start FUN_020614FC
FUN_020614FC: ; 0x020614FC
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MOD06_02248B60
	add r1, r0, #0x0
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0206151C
FUN_0206151C: ; 0x0206151C
	push {r3, lr}
	sub sp, #0x28
	add r3, sp, #0x0
	strh r1, [r3, #0x0]
	strh r2, [r3, #0x2]
	mov r1, #0x2
	mov r2, #0xd
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3, pc}

	thumb_func_start FUN_02061534
FUN_02061534: ; 0x02061534
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200B164
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	mov r1, #0x2
	mov r3, #0x3
	bl FUN_0200AD38
	mov r0, #0x18
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061574
FUN_02061574: ; 0x02061574
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, sp, #0x0
	bl FUN_02022504
	bl FUN_0202B868
	ldrb r1, [r0, #0x7]
	cmp r1, #0x0
	beq _020615AC
	ldrh r1, [r0, #0x2]
	mov r2, #0xf
	add r3, r4, #0x0
	strh r1, [r4, #0x0]
	ldrb r1, [r0, #0x4]
	strb r1, [r4, #0x2]
	ldrb r1, [r0, #0x5]
	strb r1, [r4, #0x3]
	ldrb r1, [r0, #0x6]
	strb r1, [r4, #0x4]
	ldrb r0, [r0, #0x7]
	mov r1, #0x2
	strb r0, [r4, #0x5]
	add r0, r5, #0x0
	bl FUN_02060D74
_020615AC:
	add sp, #0x28
	pop {r3-r5, pc}

	thumb_func_start FUN_020615B0
FUN_020615B0: ; 0x020615B0
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x2
	ldrb r2, [r4, #0x5]
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_0200AD38
	mov r0, #0x1a
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_020615F8
FUN_020615F8: ; 0x020615F8
	push {r3-r5, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0x0
	bl FUN_02024DA0
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl MOD06_02248B60
	add r1, r0, #0x0
	ldrh r1, [r1, #0x0]
	add r0, r4, #0x0
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061618
FUN_02061618: ; 0x02061618
	push {r4-r5, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r4, r2, #0x0
	add r0, sp, #0x8
	add r2, sp, #0x4
	add r3, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r1, #0x0
	add r1, sp, #0x4
	add r2, #0x2
	add r3, #0x3
	bl FUN_02060E34
	add r0, sp, #0x4
	strh r4, [r0, #0x6]
	add r0, r5, #0x0
	mov r1, #0x2
	mov r2, #0x11
	add r3, sp, #0x4
	bl FUN_0202B4B0
	add sp, #0x2c
	pop {r4-r5, pc}

	thumb_func_start FUN_02061648
FUN_02061648: ; 0x02061648
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrh r2, [r4, #0x6]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200AE38
	mov r0, #0x1d
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061688
FUN_02061688: ; 0x02061688
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020616A4
FUN_020616A4: ; 0x020616A4
	push {r3-r5, lr}
	sub sp, #0x28
	add r4, sp, #0x0
	strh r1, [r4, #0x0]
	strb r2, [r4, #0x2]
	add r5, sp, #0x0
	strh r3, [r4, #0x4]
	cmp r2, #0x5
	bne _020616C4
	mov r1, #0x3
	mov r2, #0x6
	add r3, r5, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r5, pc}
_020616C4:
	cmp r2, #0x4
	bne _020616D6
	mov r1, #0x2
	mov r2, #0x12
	add r3, r5, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r5, pc}
_020616D6:
	cmp r2, #0x0
	bne _020616E4
	mov r1, #0x2
	mov r2, #0x13
	add r3, r5, #0x0
	bl FUN_02060D74
_020616E4:
	add sp, #0x28
	pop {r3-r5, pc}

	thumb_func_start FUN_020616E8
FUN_020616E8: ; 0x020616E8
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200AE38
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r1, #0x2
	ldrh r2, [r4, #0x4]
	add r0, r5, #0x0
	add r3, r1, #0x0
	bl FUN_0200AD38
	mov r0, #0x1e
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061728
FUN_02061728: ; 0x02061728
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200AE38
	mov r0, #0x1f
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061750
FUN_02061750: ; 0x02061750
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r0, [r4, #0x0]
	mov r1, #0x4
	sub r0, #0x95
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl GetNutName
	add r4, r0, #0x0
	mov r1, #0x1
	str r1, [sp, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl String_dtor
	mov r0, #0x5
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02061798
FUN_02061798: ; 0x02061798
	push {r4-r5, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, sp, #0x4
	add r4, r1, #0x0
	strb r2, [r0, #0x6]
	bl MTRandom
	mov r1, #0x3
	bl _u32_div_f
	add r0, sp, #0x4
	strb r1, [r0, #0x5]
	add r0, sp, #0x8
	add r2, sp, #0x4
	add r3, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r1, sp, #0x4
	add r2, #0x2
	add r3, #0x3
	bl FUN_02060E34
	add r0, r5, #0x0
	mov r1, #0x2
	mov r2, #0x15
	add r3, sp, #0x4
	bl FUN_0202B4B0
	add sp, #0x2c
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_020617D8
FUN_020617D8: ; 0x020617D8
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r2, [r4, #0x6]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200B534
	ldrb r0, [r4, #0x3]
	mov r1, #0x2
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	bl LCRandom
	ldr r1, _02061830 ; =0x00005556
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x3
	blo _02061826
	bl ErrorHandling
_02061826:
	add r4, #0x21
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	nop
_02061830: .word 0x00005556

	thumb_func_start FUN_02061834
FUN_02061834: ; 0x02061834
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061850
FUN_02061850: ; 0x02061850
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl PlayerData_sizeof
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	add r1, r5, #0x4
	bl FUN_0202393C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061868
FUN_02061868: ; 0x02061868
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	bl PlayerData_sizeof
	ldr r1, [r4, #0x0]
	cmp r1, r0
	beq _02061884
	bl ErrorHandling
_02061884:
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r4, #0x4
	bl FUN_0200ABC0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0206189C
FUN_0206189C: ; 0x0206189C
	push {r4, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_02061850
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x16
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r4, pc}

	thumb_func_start FUN_020618B8
FUN_020618B8: ; 0x020618B8
	push {r4, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_02061850
	add r0, r4, #0x0
	mov r1, #0x2
	mov r2, #0x17
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r4, pc}

	thumb_func_start FUN_020618D4
FUN_020618D4: ; 0x020618D4
	push {r3, lr}
	bl FUN_02061868
	mov r0, #0x24
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020618E0
FUN_020618E0: ; 0x020618E0
	push {r3, lr}
	bl FUN_02061868
	mov r0, #0x25
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020618EC
FUN_020618EC: ; 0x020618EC
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0206F158
	mov r1, #0x6b
	lsl r1, r1, #0x2
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206EE50
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02061904
FUN_02061904: ; 0x02061904
	push {r3-r6, lr}
	sub sp, #0x2c
	add r6, r0, #0x0
	add r0, sp, #0x8
	add r5, r1, #0x0
	add r4, r3, #0x0
	add r0, #0x2
	add r1, sp, #0x4
	add r3, sp, #0x8
	str r0, [sp, #0x0]
	add r0, r2, #0x0
	add r1, #0x2
	add r2, sp, #0x8
	add r3, #0x1
	bl FUN_02060E34
	add r0, sp, #0x4
	strh r5, [r0, #0x0]
	strb r4, [r0, #0x7]
	add r0, r6, #0x0
	mov r1, #0x3
	mov r2, #0x1
	add r3, sp, #0x4
	bl FUN_02060D74
	add sp, #0x2c
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_0206193C
FUN_0206193C: ; 0x0206193C
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x5]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x6]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	ldrb r3, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_02060E70
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2
	mov r3, #0x4
	bl FUN_0200AD38
	ldrb r0, [r4, #0x7]
	cmp r0, #0x0
	bne _0206198A
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_0206198A:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02061990
FUN_02061990: ; 0x02061990
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x2]
	bl FUN_020245F0
	cmp r0, #0x0
	bne _020619B0
	mov r0, #0x0
	pop {r3-r5, pc}
_020619B0:
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x2
	mov r2, #0x11
	bl FUN_0205F2E4
	pop {r3-r5, pc}

	thumb_func_start FUN_020619C0
FUN_020619C0: ; 0x020619C0
	push {r4-r5, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	add r0, sp, #0x8
	str r0, [sp, #0x0]
	add r0, r2, #0x0
	add r2, sp, #0x4
	add r3, sp, #0x4
	add r4, r1, #0x0
	add r1, sp, #0x4
	add r2, #0x2
	add r3, #0x3
	bl FUN_02060E34
	mov r1, #0x3
	add r0, r5, #0x0
	add r2, r1, #0x0
	add r3, sp, #0x4
	str r4, [sp, #0xc]
	bl FUN_02060D74
	add sp, #0x2c
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_020619F0
FUN_020619F0: ; 0x020619F0
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	mov r0, #0xfa
	ldr r1, [r4, #0x8]
	lsl r0, r0, #0x2
	mul r0, r1
	mov r1, #0xfe
	bl _u32_div_f
	add r0, r0, #0x5
	mov r1, #0xa
	bl _u32_div_f
	mov r1, #0xa
	add r4, r0, #0x0
	bl _u32_div_f
	add r2, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x2
	mov r3, #0x3
	bl FUN_0200AD38
	add r0, r4, #0x0
	mov r1, #0xa
	bl _u32_div_f
	mov r0, #0x0
	add r2, r1, #0x0
	str r0, [sp, #0x0]
	mov r3, #0x1
	add r0, r5, #0x0
	mov r1, #0x3
	str r3, [sp, #0x4]
	bl FUN_0200AD38
	mov r0, #0x2
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02061A70
FUN_02061A70: ; 0x02061A70
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061A8C
FUN_02061A8C: ; 0x02061A8C
	push {r3-r5, lr}
	sub sp, #0x28
	mov r4, #0xfa
	lsl r4, r4, #0x2
	add r4, r1, r4
	add r5, sp, #0x0
	cmp r2, r4
	blo _02061AAC
	str r1, [r5, #0x0]
	str r2, [r5, #0x4]
	str r3, [r5, #0x8]
	mov r1, #0x3
	mov r2, #0x4
	add r3, r5, #0x0
	bl FUN_02060D74
_02061AAC:
	add sp, #0x28
	pop {r3-r5, pc}

	thumb_func_start FUN_02061AB0
FUN_02061AB0: ; 0x02061AB0
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	ldr r2, [r4, #0x8]
	add r0, r5, #0x0
	mov r3, #0xa
	bl FUN_0200AD38
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x2
	mov r3, #0x6
	bl FUN_0200AD38
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r2, [r4, #0x4]
	add r0, r5, #0x0
	mov r1, #0x3
	mov r3, #0x6
	bl FUN_0200AD38
	mov r0, #0x3
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061B0C
FUN_02061B0C: ; 0x02061B0C
	push {r3, lr}
	sub sp, #0x28
	add r3, sp, #0x0
	strh r1, [r3, #0x0]
	strh r2, [r3, #0x2]
	mov r1, #0x3
	mov r2, #0x8
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3, pc}

	thumb_func_start FUN_02061B24
FUN_02061B24: ; 0x02061B24
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200B1D4
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	mov r1, #0x2
	mov r3, #0x3
	bl FUN_0200AD38
	mov r0, #0x7
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061B64
FUN_02061B64: ; 0x02061B64
	push {r3, lr}
	sub sp, #0x28
	add r2, sp, #0x0
	add r3, sp, #0x0
	strh r1, [r2, #0x0]
	cmp r1, #0x1
	bls _02061B7A
	mov r1, #0x3
	mov r2, #0x9
	bl FUN_02060D74
_02061B7A:
	add sp, #0x28
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02061B80
FUN_02061B80: ; 0x02061B80
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r3, #0x3
	bl FUN_0200AD38
	mov r0, #0x8
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061BB4
FUN_02061BB4: ; 0x02061BB4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0206F158
	mov r1, #0x6b
	lsl r1, r1, #0x2
	mov r2, #0x1
	mov r3, #0x20
	bl FUN_0206EE50
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02061BCC
FUN_02061BCC: ; 0x02061BCC
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_02022504
	bl FUN_0202B85C
	ldrh r2, [r0, #0x0]
	add r1, sp, #0x0
	add r3, sp, #0x0
	strh r2, [r1, #0x0]
	ldrh r2, [r0, #0x2]
	strh r2, [r1, #0x2]
	mov r2, #0x0
	strb r2, [r0, #0x0]
	strh r4, [r1, #0x4]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x2
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061C00
FUN_02061C00: ; 0x02061C00
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	mov r1, #0x0
	add r4, r0, #0x0
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	mov r3, #0x4
	bl FUN_0200AD38
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x4]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	ldrb r0, [r4, #0x1]
	cmp r0, #0x1
	bne _02061C42
	add sp, #0x8
	mov r0, #0x8
	pop {r4-r6, pc}
_02061C42:
	mov r0, #0x9
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02061C48
FUN_02061C48: ; 0x02061C48
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x2
	mov r2, #0x11
	bl FUN_0205F2E4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02061C5C
FUN_02061C5C: ; 0x02061C5C
	push {r3-r6, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl SavArray_PlayerParty_get
	bl FUN_0204A20C
	add r1, sp, #0x8
	add r2, sp, #0x4
	add r3, sp, #0x4
	str r1, [sp, #0x0]
	add r1, sp, #0x4
	add r2, #0x2
	add r3, #0x3
	add r6, r0, #0x0
	bl FUN_02060E34
	add r2, sp, #0x8
	add r3, sp, #0x8
	mov r0, #0x20
	add r1, r6, #0x0
	add r2, #0x1
	add r3, #0x2
	bl FUN_02060ECC
	add r0, sp, #0x4
	strh r4, [r0, #0x1c]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x4
	add r3, sp, #0x4
	bl FUN_02060D74
	add sp, #0x2c
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02061CA8
FUN_02061CA8: ; 0x02061CA8
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldrb r0, [r4, #0x5]
	cmp r0, #0x0
	beq _02061D00
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrb r0, [r4, #0x3]
	mov r1, #0x2
	add r2, r4, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060D90
	ldrh r2, [r4, #0x1c]
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0200B518
	add sp, #0x8
	mov r0, #0xa
	pop {r4-r6, pc}
_02061D00:
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x3]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x4]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x0]
	ldrb r3, [r4, #0x2]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrh r2, [r4, #0x1c]
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0200B518
	mov r0, #0xb
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061D30
FUN_02061D30: ; 0x02061D30
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061D4C
FUN_02061D4C: ; 0x02061D4C
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	add r4, r1, #0x0
	ldr r0, [r0, #0x14]
	bl MOD20_02252538
	str r0, [sp, #0x0]
	add r0, sp, #0x0
	strh r4, [r0, #0x4]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x6
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061D74
FUN_02061D74: ; 0x02061D74
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldr r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200B02C
	ldrh r2, [r4, #0x4]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	mov r0, #0x10
	pop {r4-r6, pc}

	thumb_func_start FUN_02061DA4
FUN_02061DA4: ; 0x02061DA4
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_02022504
	bl FUN_0202B838
	ldrh r2, [r0, #0x0]
	add r1, sp, #0x0
	add r3, sp, #0x0
	strh r2, [r1, #0x0]
	ldrh r2, [r0, #0x2]
	strh r2, [r1, #0x2]
	ldrh r2, [r0, #0x4]
	strh r2, [r1, #0x4]
	ldrh r2, [r0, #0x6]
	strh r2, [r1, #0x6]
	ldrh r2, [r0, #0x8]
	strh r2, [r1, #0x8]
	mov r2, #0x0
	strb r2, [r0, #0x0]
	strh r4, [r1, #0xa]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0x7
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061DE4
FUN_02061DE4: ; 0x02061DE4
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r0, r6, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldrb r0, [r4, #0x5]
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x6]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	ldrb r3, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrb r0, [r4, #0x8]
	bl FUN_02083298
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_0200B2AC
	ldrb r0, [r4, #0x7]
	bl FUN_02083268
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200B278
	mov r0, #0x0
	str r0, [sp, #0x0]
	mov r3, #0x1
	str r3, [sp, #0x4]
	ldrb r2, [r4, #0x9]
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0200AD38
	add r0, r5, #0x0
	mov r1, #0x4
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0xa]
	add r0, r5, #0x0
	mov r1, #0x5
	bl FUN_0200B518
	ldrb r0, [r4, #0x9]
	cmp r0, #0x1
	bne _02061E5A
	add sp, #0x8
	mov r0, #0x12
	pop {r4-r6, pc}
_02061E5A:
	mov r0, #0x11
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02061E60
FUN_02061E60: ; 0x02061E60
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x2]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061E7C
FUN_02061E7C: ; 0x02061E7C
	push {r4, lr}
	sub sp, #0x28
	add r4, r0, #0x0
	add r0, sp, #0x0
	strh r1, [r0, #0x2]
	ldr r0, [r4, #0xc]
	bl FUN_02027E24
	mov r1, #0x0
	bl FUN_02027008
	bl FUN_020275D8
	add r1, sp, #0x0
	strh r0, [r1, #0x0]
	add r0, r4, #0x0
	mov r1, #0x1
	mov r2, #0x9
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02061EAC
FUN_02061EAC: ; 0x02061EAC
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrh r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02060EA0
	ldrh r2, [r4, #0x2]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	mov r0, #0x14
	pop {r4-r6, pc}

	thumb_func_start FUN_02061EDC
FUN_02061EDC: ; 0x02061EDC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_02024DA0
	ldrh r1, [r4, #0x0]
	bl FUN_020245F0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061EF8
FUN_02061EF8: ; 0x02061EF8
	push {r3, lr}
	sub sp, #0x28
	str r1, [sp, #0x0]
	mov r1, #0x1
	mov r2, #0xa
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r3, pc}

	thumb_func_start FUN_02061F0C
FUN_02061F0C: ; 0x02061F0C
	push {r4-r6, lr}
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldr r0, [r4, #0x0]
	add r0, #0x14
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02061F2C
FUN_02061F2C: ; 0x02061F2C
	push {r3-r5, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_02022504
	bl FUN_0202B850
	ldrb r2, [r0, #0x0]
	add r1, sp, #0x0
	add r3, sp, #0x0
	strb r2, [r1, #0x0]
	ldrb r2, [r0, #0x1]
	strb r2, [r1, #0x1]
	strh r4, [r1, #0x2]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0xb
	bl FUN_02060D74
	add sp, #0x28
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02061F60
FUN_02061F60: ; 0x02061F60
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r0, r7, #0x0
	add r5, r1, #0x0
	bl MOD06_02248B60
	add r6, r0, #0x0
	ldrb r4, [r6, #0x1]
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r7, #0x0
	bl FUN_02060DCC
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0200B628
	ldrh r2, [r6, #0x2]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200B518
	sub r4, #0x19
	cmp r4, #0x3
	bhi _02061FB8
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02061FA0: ; jump table (using 16-bit offset)
	.short _02061FA8 - _02061FA0 - 2; case 0
	.short _02061FAC - _02061FA0 - 2; case 1
	.short _02061FB0 - _02061FA0 - 2; case 2
	.short _02061FB4 - _02061FA0 - 2; case 3
_02061FA8:
	mov r0, #0x27
	pop {r3-r7, pc}
_02061FAC:
	mov r0, #0x28
	pop {r3-r7, pc}
_02061FB0:
	mov r0, #0x29
	pop {r3-r7, pc}
_02061FB4:
	mov r0, #0x2a
	pop {r3-r7, pc}
_02061FB8:
	mov r0, #0x26
	pop {r3-r7, pc}

	thumb_func_start FUN_02061FBC
FUN_02061FBC: ; 0x02061FBC
	push {r4-r6, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r4, r1, #0x0
	bl FUN_02022504
	bl FUN_0202B844
	add r6, r0, #0x0
	add r3, sp, #0x0
	mov r2, #0x12
_02061FD4:
	ldrh r1, [r6, #0x0]
	add r6, r6, #0x2
	strh r1, [r3, #0x0]
	add r3, r3, #0x2
	sub r2, r2, #0x1
	bne _02061FD4
	add r1, sp, #0x0
	strh r4, [r1, #0x24]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	mov r2, #0xd
	add r3, sp, #0x0
	bl FUN_02060D74
	add sp, #0x28
	pop {r4-r6, pc}

	thumb_func_start FUN_02061FF8
FUN_02061FF8: ; 0x02061FF8
	push {r4-r6, lr}
	sub sp, #0x8
	add r6, r2, #0x0
	add r5, r1, #0x0
	add r0, r6, #0x0
	bl MOD06_02248B60
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	bl FUN_02060DCC
	ldrb r0, [r4, #0x5]
	mov r1, #0x1
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0x6]
	str r0, [sp, #0x4]
	ldrh r2, [r4, #0x2]
	ldrb r3, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_02060E70
	ldrb r2, [r4, #0x1e]
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_0200AE04
	ldrh r2, [r4, #0x24]
	add r0, r5, #0x0
	mov r1, #0x5
	bl FUN_0200B518
	ldrb r0, [r4, #0x1f]
	cmp r0, #0x0
	beq _0206204A
	cmp r0, #0x1
	beq _02062062
	cmp r0, #0x2
	beq _02062050
	b _02062072
_0206204A:
	add sp, #0x8
	mov r0, #0x2d
	pop {r4-r6, pc}
_02062050:
	add r4, #0x20
	ldrb r2, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0200B660
	add sp, #0x8
	mov r0, #0x2c
	pop {r4-r6, pc}
_02062062:
	ldrh r2, [r4, #0x22]
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_0200AE38
	add sp, #0x8
	mov r0, #0x2e
	pop {r4-r6, pc}
_02062072:
	mov r0, #0x2d
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_02062078
FUN_02062078: ; 0x02062078
	push {r3-r7, lr}
	mov r6, #0x0
	ldr r5, _0206209C ; =UNK_020F7650
	add r7, r0, #0x0
	add r4, r6, #0x0
_02062082:
	ldrb r1, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_02028828
	cmp r0, #0x0
	beq _02062090
	add r4, r4, #0x1
_02062090:
	add r6, r6, #0x1
	add r5, r5, #0x1
	cmp r6, #0x5
	blo _02062082
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4
_0206209C: .word UNK_020F7650

	thumb_func_start FUN_020620A0
FUN_020620A0: ; 0x020620A0
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x4]
	ldr r0, [r0, #0xc]
	str r1, [sp, #0x8]
	bl FUN_0202881C
	add r7, r0, #0x0
	bl FUN_02062078
	add r4, r0, #0x0
	cmp r4, #0x0
	bgt _020620BE
	bl ErrorHandling
_020620BE:
	cmp r4, #0x1
	ble _020620D0
	bl MTRandom
	add r1, r4, #0x0
	bl _u32_div_f
	add r5, r1, #0x0
	b _020620D2
_020620D0:
	mov r5, #0x0
_020620D2:
	ldr r4, _02062154 ; =UNK_020F7650
	mov r6, #0x0
_020620D6:
	ldrb r1, [r4, #0x0]
	add r0, r7, #0x0
	bl FUN_02028828
	cmp r0, #0x0
	beq _020620F0
	cmp r5, #0x0
	bne _020620EE
	ldr r0, _02062154 ; =UNK_020F7650
	ldrb r0, [r0, r6]
	str r0, [sp, #0xc]
	b _020620F8
_020620EE:
	sub r5, r5, #0x1
_020620F0:
	add r6, r6, #0x1
	add r4, r4, #0x1
	cmp r6, #0x5
	blo _020620D6
_020620F8:
	cmp r5, #0x0
	beq _02062100
	bl ErrorHandling
_02062100:
	bl LCRandom
	mov r1, #0xf1
	lsl r1, r1, #0x4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x11
	blo _02062118
	bl ErrorHandling
_02062118:
	cmp r4, #0x9
	blt _0206211E
	add r4, r4, #0x1
_0206211E:
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r1, [r1, #0xc]
	ldr r2, [sp, #0xc]
	mov r3, #0x0
	bl FUN_0200B708
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r1, [r1, #0xc]
	ldr r2, [sp, #0xc]
	mov r3, #0x1
	bl FUN_0200B708
	ldr r0, [sp, #0x8]
	mov r1, #0x2
	add r2, r4, #0x0
	bl FUN_0200AF18
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_02062154: .word UNK_020F7650

	thumb_func_start FUN_02062158
FUN_02062158: ; 0x02062158
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0202881C
	bl FUN_02062078
	cmp r0, #0x0
	beq _0206216C
	mov r0, #0x1
	pop {r3, pc}
_0206216C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02062170
FUN_02062170: ; 0x02062170
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	bl LCRandom
	ldr r1, _02062234 ; =0x00003334
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x5
	blo _0206218C
	bl ErrorHandling
_0206218C:
	ldr r0, _02062238 ; =UNK_02105FBC
	lsl r1, r4, #0x1
	ldrh r5, [r0, r1]
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02034FE4
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02034824
	add r2, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x0
	bl GetLandmarkName
	cmp r4, #0xb
	bhi _0206222C
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020621BC: ; jump table (using 16-bit offset)
	.short _020621D4 - _020621BC - 2; case 0
	.short _0206220C - _020621BC - 2; case 1
	.short _02062210 - _020621BC - 2; case 2
	.short _02062214 - _020621BC - 2; case 3
	.short _02062224 - _020621BC - 2; case 4
	.short _02062218 - _020621BC - 2; case 5
	.short _0206221C - _020621BC - 2; case 6
	.short _02062220 - _020621BC - 2; case 7
	.short _0206222C - _020621BC - 2; case 8
	.short _0206222C - _020621BC - 2; case 9
	.short _0206222C - _020621BC - 2; case 10
	.short _02062228 - _020621BC - 2; case 11
_020621D4:
	bl LCRandom
	lsl r0, r0, #0x2
	lsr r4, r0, #0x10
	cmp r4, #0x4
	blo _020621E4
	bl ErrorHandling
_020621E4:
	cmp r4, #0x3
	bhi _0206220C
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020621F4: ; jump table (using 16-bit offset)
	.short _020621FC - _020621F4 - 2; case 0
	.short _02062200 - _020621F4 - 2; case 1
	.short _02062204 - _020621F4 - 2; case 2
	.short _02062208 - _020621F4 - 2; case 3
_020621FC:
	mov r0, #0x1
	pop {r3-r7, pc}
_02062200:
	mov r0, #0x2
	pop {r3-r7, pc}
_02062204:
	mov r0, #0x3
	pop {r3-r7, pc}
_02062208:
	mov r0, #0x4
	pop {r3-r7, pc}
_0206220C:
	mov r0, #0x5
	pop {r3-r7, pc}
_02062210:
	mov r0, #0x6
	pop {r3-r7, pc}
_02062214:
	mov r0, #0x7
	pop {r3-r7, pc}
_02062218:
	mov r0, #0x8
	pop {r3-r7, pc}
_0206221C:
	mov r0, #0x9
	pop {r3-r7, pc}
_02062220:
	mov r0, #0xa
	pop {r3-r7, pc}
_02062224:
	mov r0, #0xb
	pop {r3-r7, pc}
_02062228:
	mov r0, #0xc
	pop {r3-r7, pc}
_0206222C:
	bl ErrorHandling
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_02062234: .word 0x00003334
_02062238: .word UNK_02105FBC

	thumb_func_start FUN_0206223C
FUN_0206223C: ; 0x0206223C
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_02062240
FUN_02062240: ; 0x02062240
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r0, [r0, #0xc]
	add r4, r1, #0x0
	bl FUN_0202A9B0
	mov r1, #0x2
	bl FUN_0202A990
	add r1, sp, #0x0
	add r1, #0x2
	add r2, sp, #0x0
	bl MOD06_02245910
	add r0, sp, #0x0
	ldrh r0, [r0, #0x2]
	bl FUN_02034824
	add r2, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x0
	bl GetLandmarkName
	add r2, sp, #0x0
	ldrh r2, [r2, #0x0]
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02060EA0
	mov r0, #0x1c
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02062280
FUN_02062280: ; 0x02062280
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_0202A9B0
	bl FUN_0202AA14
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02062290
FUN_02062290: ; 0x02062290
	push {r3-r4}
	ldr r4, _020622BC ; =UNK_020F78A4
	mov r3, #0x0
_02062296:
	ldrb r2, [r4, #0x0]
	cmp r0, r2
	bne _020622AE
	ldrb r2, [r4, #0x1]
	cmp r1, r2
	bne _020622AE
	lsl r0, r3, #0x1
	add r1, r3, r0
	ldr r0, _020622C0 ; =UNK_020F78A6
	ldrb r0, [r0, r1]
	pop {r3-r4}
	bx lr
_020622AE:
	add r3, r3, #0x1
	add r4, r4, #0x3
	cmp r3, #0x6e
	blo _02062296
	mov r0, #0x3
	pop {r3-r4}
	bx lr
	.balign 4
_020622BC: .word UNK_020F78A4
_020622C0: .word UNK_020F78A6

	thumb_func_start FUN_020622C4
FUN_020622C4: ; 0x020622C4
	push {r4-r6, lr}
	add r6, r1, #0x0
	bl LCRandom
	mov r1, #0xf1
	lsl r1, r1, #0x4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x11
	blo _020622E0
	bl ErrorHandling
_020622E0:
	cmp r5, #0x9
	blt _020622E6
	add r5, r5, #0x1
_020622E6:
	bl LCRandom
	mov r1, #0xf1
	lsl r1, r1, #0x4
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x11
	blo _020622FE
	bl ErrorHandling
_020622FE:
	cmp r4, #0x9
	blt _02062304
	add r4, r4, #0x1
_02062304:
	add r0, r6, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	bl FUN_0200AF18
	add r0, r6, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	bl FUN_0200AF18
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02062290
	cmp r0, #0x3
	bhi _0206233C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02062330: ; jump table (using 16-bit offset)
	.short _02062344 - _02062330 - 2; case 0
	.short _02062340 - _02062330 - 2; case 1
	.short _02062338 - _02062330 - 2; case 2
	.short _0206233C - _02062330 - 2; case 3
_02062338:
	mov r0, #0x1e
	pop {r4-r6, pc}
_0206233C:
	mov r0, #0x1f
	pop {r4-r6, pc}
_02062340:
	mov r0, #0x20
	pop {r4-r6, pc}
_02062344:
	mov r0, #0x21
	pop {r4-r6, pc}

	thumb_func_start FUN_02062348
FUN_02062348: ; 0x02062348
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0206234C
FUN_0206234C: ; 0x0206234C
	push {r3-r7, lr}
	sub sp, #0x88
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	ldr r4, _020623E8 ; =UNK_020F7658
	add r7, r0, #0x0
	mov r6, #0x0
	add r5, sp, #0x0
_0206235E:
	ldrh r2, [r4, #0x0]
	add r0, r7, #0x0
	mov r1, #0x2
	bl FUN_0205F2E4
	strb r0, [r5, #0x0]
	add r6, r6, #0x1
	add r4, r4, #0x2
	add r5, r5, #0x1
	cmp r6, #0x12
	blo _0206235E
	mov r3, #0x0
	add r2, sp, #0x10
	ldr r0, _020623EC ; =UNK_020F79EE
	add r4, r3, #0x0
	add r1, r3, #0x0
	add r2, #0x2
	add r6, sp, #0x0
_02062382:
	lsl r5, r1, #0x1
	ldrh r5, [r0, r5]
	ldrb r5, [r6, r5]
	cmp r5, #0x0
	beq _02062392
	strb r3, [r2, #0x0]
	add r2, r2, #0x1
	add r4, r4, #0x1
_02062392:
	add r3, r3, #0x1
	add r1, r1, #0x2
	cmp r3, #0x76
	blo _02062382
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bne _020623A4
	bl ErrorHandling
_020623A4:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x1
	bhi _020623B0
	mov r5, #0x0
	b _020623DE
_020623B0:
	bl LCRandom
	add r5, r0, #0x0
	lsl r1, r4, #0x10
	ldr r0, _020623F0 ; =0x0000FFFF
	lsr r1, r1, #0x10
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	cmp r5, r0
	blo _020623DE
	bl ErrorHandling
_020623DE:
	add r0, sp, #0x10
	add r0, #0x2
	ldrb r0, [r0, r5]
	add sp, #0x88
	pop {r3-r7, pc}
	.balign 4
_020623E8: .word UNK_020F7658
_020623EC: .word UNK_020F79EE
_020623F0: .word 0x0000FFFF

	thumb_func_start FUN_020623F4
FUN_020623F4: ; 0x020623F4
	push {r4-r6, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	add r5, r1, #0x0
	bl FUN_02024ECC
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0206234C
	add r4, r0, #0x0
	lsl r0, r4, #0x1
	add r0, r0, #0x1
	lsl r1, r0, #0x1
	ldr r0, _0206245C ; =UNK_020F79EE
	ldrh r0, [r0, r1]
	bl FUN_02034824
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl GetLandmarkName
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02025238
	cmp r0, #0x5
	bhi _02062456
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0206243A: ; jump table (using 16-bit offset)
	.short _02062456 - _0206243A - 2; case 0
	.short _02062456 - _0206243A - 2; case 1
	.short _02062452 - _0206243A - 2; case 2
	.short _0206244E - _0206243A - 2; case 3
	.short _0206244A - _0206243A - 2; case 4
	.short _02062446 - _0206243A - 2; case 5
_02062446:
	mov r0, #0x23
	pop {r4-r6, pc}
_0206244A:
	mov r0, #0x24
	pop {r4-r6, pc}
_0206244E:
	mov r0, #0x25
	pop {r4-r6, pc}
_02062452:
	mov r0, #0x26
	pop {r4-r6, pc}
_02062456:
	mov r0, #0x27
	pop {r4-r6, pc}
	nop
_0206245C: .word UNK_020F79EE

	thumb_func_start FUN_02062460
FUN_02062460: ; 0x02062460
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	mov r1, #0x2
	mov r2, #0x9
	bl FUN_0205F2E4
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02062474
FUN_02062474: ; 0x02062474
	push {r3-r6, lr}
	sub sp, #0xc
	mov r0, #0x4
	add r6, r1, #0x0
	str r0, [sp, #0x0]
	add r0, sp, #0x8
	mov r1, #0x7e
	mov r2, #0x2
	mov r3, #0x0
	bl ReadFromNarcMemberByIdPair
	ldr r0, [sp, #0x8]
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	bne _02062496
	bl ErrorHandling
_02062496:
	cmp r4, #0x1
	bhi _0206249E
	mov r5, #0x0
	b _020624C6
_0206249E:
	bl LCRandom
	add r5, r0, #0x0
	ldr r0, _02062504 ; =0x0000FFFF
	add r1, r4, #0x0
	bl _s32_div_f
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, r4
	blo _020624C6
	bl ErrorHandling
_020624C6:
	lsl r4, r5, #0x2
	add r0, sp, #0x4
	mov r2, #0x2
	add r0, #0x2
	mov r1, #0x7e
	add r3, r4, #0x4
	str r2, [sp, #0x0]
	bl ReadFromNarcMemberByIdPair
	mov r2, #0x2
	add r0, sp, #0x4
	mov r1, #0x7e
	add r3, r4, #0x6
	str r2, [sp, #0x0]
	bl ReadFromNarcMemberByIdPair
	add r2, sp, #0x4
	ldrh r2, [r2, #0x2]
	add r0, r6, #0x0
	mov r1, #0x0
	bl FUN_02060EA0
	add r2, sp, #0x4
	ldrh r2, [r2, #0x0]
	add r0, r6, #0x0
	mov r1, #0x1
	bl FUN_0200AE38
	mov r0, #0x2a
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_02062504: .word 0x0000FFFF

	thumb_func_start FUN_02062508
FUN_02062508: ; 0x02062508
	mov r0, #0x1
	bx lr

	thumb_func_start FUN_0206250C
FUN_0206250C: ; 0x0206250C
	push {r4-r6, lr}
	mov r4, #0x0
	add r6, r0, #0x0
	add r5, r4, #0x0
_02062514:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02027098
	cmp r0, #0x1
	bne _02062522
	add r5, r5, #0x1
_02062522:
	add r4, r4, #0x1
	cmp r4, #0xb
	blt _02062514
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0206252C
FUN_0206252C: ; 0x0206252C
	push {r4-r7, lr}
	sub sp, #0xc
	ldr r0, [r0, #0xc]
	add r7, r1, #0x0
	bl FUN_02027E24
	add r6, r0, #0x0
	bl FUN_0206250C
	add r4, r0, #0x0
	cmp r4, #0x1
	ble _02062552
	bl MTRandom
	add r1, r4, #0x0
	bl _u32_div_f
	add r5, r1, #0x0
	b _02062554
_02062552:
	mov r5, #0x0
_02062554:
	mov r4, #0x0
_02062556:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02027098
	cmp r0, #0x1
	bne _0206256C
	cmp r5, #0x0
	bne _0206256A
	str r4, [sp, #0x8]
	b _02062572
_0206256A:
	sub r5, r5, #0x1
_0206256C:
	add r4, r4, #0x1
	cmp r4, #0xb
	blt _02062556
_02062572:
	cmp r4, #0xb
	blt _0206257A
	bl ErrorHandling
_0206257A:
	ldr r1, [sp, #0x8]
	add r0, r6, #0x0
	bl FUN_02027008
	add r5, r0, #0x0
	mov r0, #0x8
	mov r1, #0x4
	bl String_ctor
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202763C
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02027608
	add r0, r5, #0x0
	bl FUN_020276A8
	mov r1, #0x1
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_0200ABB4
	add r0, r4, #0x0
	bl String_dtor
	add r0, r5, #0x0
	bl FUN_0202769C
	add r2, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0x1
	bl FUN_0200B518
	mov r0, #0x32
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020625D4
FUN_020625D4: ; 0x020625D4
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_02027E24
	bl FUN_0206250C
	cmp r0, #0x0
	beq _020625E8
	mov r0, #0x1
	pop {r3, pc}
_020625E8:
	mov r0, #0x0
	pop {r3, pc}
