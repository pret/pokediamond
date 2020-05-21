    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021058A0

	.text

	thumb_func_start ReadNARCFile
ReadNARCFile: ; 0x02006314
	push {r3-r7, lr}
	sub sp, #0x60
	add r4, r1, #0x0
	mov r1, #0x0
	str r0, [sp, #0x0]
	str r1, [sp, #0x14]
	str r1, [sp, #0x10]
	str r1, [sp, #0xc]
	add r0, sp, #0x8
	strh r1, [r0, #0x0]
	add r0, sp, #0x18
	add r5, r2, #0x0
	str r3, [sp, #0x4]
	bl FS_InitFile
	add r0, sp, #0x18
	add r1, r4, #0x0
	bl FS_OpenFile
	add r0, sp, #0x18
	mov r1, #0xc
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x14
	mov r2, #0x2
	bl FS_ReadFile
	ldr r4, [sp, #0x14]
	add r0, sp, #0x18
	add r1, r4, #0x4
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x14
	mov r2, #0x4
	bl FS_ReadFile
	add r0, sp, #0x18
	add r1, sp, #0x8
	mov r2, #0x2
	bl FS_ReadFile
	add r0, sp, #0x8
	ldrh r0, [r0, #0x0]
	cmp r0, r5
	bgt _0200637A
	bl ErrorHandling
_0200637A:
	ldr r0, [sp, #0x14]
	mov r2, #0x0
	add r6, r4, r0
	add r0, sp, #0x18
	add r1, r6, #0x4
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x14
	mov r2, #0x4
	bl FS_ReadFile
	add r4, #0xc
	lsl r1, r5, #0x3
	add r0, sp, #0x18
	add r1, r4, r1
	mov r2, #0x0
	ldr r7, [sp, #0x14]
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x10
	mov r2, #0x4
	bl FS_ReadFile
	add r0, sp, #0x18
	add r1, sp, #0xc
	mov r2, #0x4
	bl FS_ReadFile
	add r2, r6, r7
	ldr r1, [sp, #0x10]
	add r2, #0x8
	add r2, r2, r1
	ldr r1, [sp, #0x4]
	add r0, sp, #0x18
	add r1, r1, r2
	mov r2, #0x0
	bl FS_SeekFile
	ldr r0, [sp, #0x78]
	cmp r0, #0x0
	bne _020063D6
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	sub r0, r1, r0
_020063D6:
	str r0, [sp, #0x14]
	cmp r0, #0x0
	bne _020063E0
	bl ErrorHandling
_020063E0:
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x14]
	add r0, sp, #0x18
	bl FS_ReadFile
	add r0, sp, #0x18
	bl FS_CloseFile
	add sp, #0x60
	pop {r3-r7, pc}

	thumb_func_start LoadFileIntoMemory
LoadFileIntoMemory: ; 0x020063F4
	push {r3-r7, lr}
	sub sp, #0x60
	add r5, r1, #0x0
	mov r1, #0x0
	add r4, r0, #0x0
	str r1, [sp, #0x14]
	str r1, [sp, #0x10]
	str r1, [sp, #0xc]
	add r0, sp, #0x8
	strh r1, [r0, #0x0]
	add r0, sp, #0x18
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	bl FS_InitFile
	add r0, sp, #0x18
	add r1, r4, #0x0
	bl FS_OpenFile
	add r0, sp, #0x18
	mov r1, #0xc
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x14
	mov r2, #0x2
	bl FS_ReadFile
	ldr r4, [sp, #0x14]
	add r0, sp, #0x18
	add r1, r4, #0x4
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x14
	mov r2, #0x4
	bl FS_ReadFile
	add r0, sp, #0x18
	add r1, sp, #0x8
	mov r2, #0x2
	bl FS_ReadFile
	add r0, sp, #0x8
	ldrh r0, [r0, #0x0]
	cmp r0, r5
	bgt _0200645A
	bl ErrorHandling
_0200645A:
	ldr r0, [sp, #0x14]
	mov r2, #0x0
	add r6, r4, r0
	add r0, sp, #0x18
	add r1, r6, #0x4
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x14
	mov r2, #0x4
	bl FS_ReadFile
	add r4, #0xc
	lsl r1, r5, #0x3
	add r0, sp, #0x18
	add r1, r4, r1
	mov r2, #0x0
	ldr r7, [sp, #0x14]
	bl FS_SeekFile
	add r0, sp, #0x18
	add r1, sp, #0x10
	mov r2, #0x4
	bl FS_ReadFile
	add r0, sp, #0x18
	add r1, sp, #0xc
	mov r2, #0x4
	bl FS_ReadFile
	add r2, r6, r7
	ldr r1, [sp, #0x10]
	add r2, #0x8
	add r2, r2, r1
	ldr r1, [sp, #0x4]
	add r0, sp, #0x18
	add r1, r1, r2
	mov r2, #0x0
	bl FS_SeekFile
	ldr r0, [sp, #0x78]
	cmp r0, #0x0
	bne _020064B6
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	sub r0, r1, r0
_020064B6:
	str r0, [sp, #0x14]
	cmp r0, #0x0
	bne _020064C0
	bl ErrorHandling
_020064C0:
	ldr r0, [sp, #0x7c]
	cmp r0, #0x0
	bne _020064D0
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x14]
	bl FUN_02016998
	b _020064D8
_020064D0:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x14]
	bl FUN_020169D8
_020064D8:
	add r4, r0, #0x0
	ldr r2, [sp, #0x14]
	add r0, sp, #0x18
	add r1, r4, #0x0
	bl FS_ReadFile
	add r0, sp, #0x18
	bl FS_CloseFile
	add r0, r4, #0x0
	add sp, #0x60
	pop {r3-r7, pc}

	thumb_func_start LoadFromNARC
LoadFromNARC: ; 0x020064F0
	push {r3-r4, lr}
	sub sp, #0x4
	mov r3, #0x0
	lsl r4, r1, #0x2
	ldr r1, _02006508 ; =UNK_021058A0
	str r3, [sp, #0x0]
	ldr r1, [r1, r4]
	bl ReadNARCFile
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_02006508: .word UNK_021058A0

	thumb_func_start LoadFromNarc_2
LoadFromNarc_2: ; 0x0200650C
	push {r4, lr}
	sub sp, #0x8
	mov r3, #0x0
	str r3, [sp, #0x0]
	lsl r4, r0, #0x2
	ldr r0, _02006524 ; =UNK_021058A0
	str r3, [sp, #0x4]
	ldr r0, [r0, r4]
	bl LoadFileIntoMemory
	add sp, #0x8
	pop {r4, pc}
	.balign 4
_02006524: .word UNK_021058A0

	thumb_func_start FUN_02006528
FUN_02006528: ; 0x02006528
	push {r4, lr}
	sub sp, #0x8
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r4, #0x1
	str r4, [sp, #0x4]
	lsl r4, r0, #0x2
	ldr r0, _02006544 ; =UNK_021058A0
	ldr r0, [r0, r4]
	bl LoadFileIntoMemory
	add sp, #0x8
	pop {r4, pc}
	nop
_02006544: .word UNK_021058A0

	thumb_func_start FUN_02006548
FUN_02006548: ; 0x02006548
	push {r3-r4, lr}
	sub sp, #0x4
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	lsl r4, r1, #0x2
	ldr r1, _02006560 ; =UNK_021058A0
	ldr r1, [r1, r4]
	bl ReadNARCFile
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_02006560: .word UNK_021058A0

	thumb_func_start FUN_02006564
FUN_02006564: ; 0x02006564
	push {r4, lr}
	sub sp, #0x8
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	mov r4, #0x0
	str r4, [sp, #0x4]
	lsl r4, r0, #0x2
	ldr r0, _02006580 ; =UNK_021058A0
	ldr r0, [r0, r4]
	bl LoadFileIntoMemory
	add sp, #0x8
	pop {r4, pc}
	nop
_02006580: .word UNK_021058A0

	thumb_func_start FUN_02006584
FUN_02006584: ; 0x02006584
	push {r4, lr}
	sub sp, #0x8
	ldr r4, [sp, #0x10]
	str r4, [sp, #0x0]
	mov r4, #0x1
	str r4, [sp, #0x4]
	lsl r4, r0, #0x2
	ldr r0, _020065A0 ; =UNK_021058A0
	ldr r0, [r0, r4]
	bl LoadFileIntoMemory
	add sp, #0x8
	pop {r4, pc}
	nop
_020065A0: .word UNK_021058A0

	thumb_func_start LoadFromNARC_7
LoadFromNARC_7: ; 0x020065A4
	push {r3-r7, lr}
	sub sp, #0x58
	add r5, r1, #0x0
	mov r1, #0x0
	add r4, r0, #0x0
	str r1, [sp, #0xc]
	str r1, [sp, #0x8]
	str r1, [sp, #0x4]
	add r0, sp, #0x0
	strh r1, [r0, #0x0]
	add r0, sp, #0x10
	bl FS_InitFile
	ldr r1, _0200666C ; =UNK_021058A0
	lsl r2, r4, #0x2
	ldr r1, [r1, r2]
	add r0, sp, #0x10
	bl FS_OpenFile
	add r0, sp, #0x10
	mov r1, #0xc
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x10
	add r1, sp, #0xc
	mov r2, #0x2
	bl FS_ReadFile
	ldr r4, [sp, #0xc]
	add r0, sp, #0x10
	add r1, r4, #0x4
	mov r2, #0x0
	bl FS_SeekFile
	add r0, sp, #0x10
	add r1, sp, #0xc
	mov r2, #0x4
	bl FS_ReadFile
	add r0, sp, #0x10
	add r1, sp, #0x0
	mov r2, #0x2
	bl FS_ReadFile
	add r0, sp, #0x0
	ldrh r0, [r0, #0x0]
	cmp r0, r5
	bgt _0200660A
	bl ErrorHandling
_0200660A:
	ldr r0, [sp, #0xc]
	mov r2, #0x0
	add r6, r4, r0
	add r0, sp, #0x10
	add r1, r6, #0x4
	bl FS_SeekFile
	add r0, sp, #0x10
	add r1, sp, #0xc
	mov r2, #0x4
	bl FS_ReadFile
	add r4, #0xc
	lsl r1, r5, #0x3
	add r0, sp, #0x10
	add r1, r4, r1
	mov r2, #0x0
	ldr r7, [sp, #0xc]
	bl FS_SeekFile
	add r0, sp, #0x10
	add r1, sp, #0x8
	mov r2, #0x4
	bl FS_ReadFile
	add r0, sp, #0x10
	add r1, sp, #0x4
	mov r2, #0x4
	bl FS_ReadFile
	add r2, r6, r7
	ldr r1, [sp, #0x8]
	add r2, #0x8
	add r1, r2, r1
	add r0, sp, #0x10
	mov r2, #0x0
	bl FS_SeekFile
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	sub r0, r1, r0
	str r0, [sp, #0xc]
	bne _02006664
	bl ErrorHandling
_02006664:
	ldr r0, [sp, #0xc]
	add sp, #0x58
	pop {r3-r7, pc}
	nop
_0200666C: .word UNK_021058A0

	thumb_func_start FUN_02006670
FUN_02006670: ; 0x02006670
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x54
	bl FUN_02016998
	add r4, r0, #0x0
	beq _020066EC
	mov r1, #0x0
	str r1, [r4, #0x48]
	bl FS_InitFile
	ldr r1, _020066F0 ; =UNK_021058A0
	lsl r2, r5, #0x2
	ldr r1, [r1, r2]
	add r0, r4, #0x0
	bl FS_OpenFile
	add r0, r4, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl FS_SeekFile
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0x48
	mov r2, #0x2
	bl FS_ReadFile
	ldr r1, [r4, #0x48]
	add r0, r4, #0x0
	add r1, r1, #0x4
	mov r2, #0x0
	bl FS_SeekFile
	add r0, r4, #0x0
	add r1, sp, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0x50
	mov r2, #0x2
	bl FS_ReadFile
	ldr r1, [r4, #0x48]
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r5, r1, r0
	add r0, r4, #0x0
	add r1, r5, #0x4
	bl FS_SeekFile
	add r0, r4, #0x0
	add r1, sp, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	ldr r0, [sp, #0x0]
	add r0, r5, r0
	str r0, [r4, #0x4c]
_020066EC:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_020066F0: .word UNK_021058A0

	thumb_func_start FUN_020066F4
FUN_020066F4: ; 0x020066F4
	push {r4, lr}
	add r4, r0, #0x0
	bl FS_CloseFile
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02006704
FUN_02006704: ; 0x02006704
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x50
	ldrh r0, [r0, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r0, r4
	bhi _0200671A
	bl ErrorHandling
_0200671A:
	ldr r2, [r5, #0x48]
	lsl r1, r4, #0x3
	add r2, #0xc
	add r1, r2, r1
	add r0, r5, #0x0
	mov r2, #0x0
	bl FS_SeekFile
	add r0, r5, #0x0
	add r1, sp, #0x4
	mov r2, #0x4
	bl FS_ReadFile
	add r0, r5, #0x0
	add r1, sp, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	ldr r2, [r5, #0x4c]
	ldr r1, [sp, #0x4]
	add r2, #0x8
	add r1, r2, r1
	add r0, r5, #0x0
	mov r2, #0x0
	bl FS_SeekFile
	ldr r2, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r6, #0x0
	sub r1, r2, r1
	bl FUN_02016998
	add r4, r0, #0x0
	beq _0200676C
	ldr r3, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	sub r2, r3, r2
	bl FS_ReadFile
_0200676C:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02006774
FUN_02006774: ; 0x02006774
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x50
	ldrh r0, [r0, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r0, r4
	bhi _0200678A
	bl ErrorHandling
_0200678A:
	ldr r2, [r5, #0x48]
	lsl r1, r4, #0x3
	add r2, #0xc
	add r1, r2, r1
	add r0, r5, #0x0
	mov r2, #0x0
	bl FS_SeekFile
	add r0, r5, #0x0
	add r1, sp, #0x4
	mov r2, #0x4
	bl FS_ReadFile
	add r0, r5, #0x0
	add r1, sp, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	ldr r2, [r5, #0x4c]
	ldr r1, [sp, #0x4]
	add r2, #0x8
	add r1, r2, r1
	add r0, r5, #0x0
	mov r2, #0x0
	bl FS_SeekFile
	ldr r3, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r6, #0x0
	sub r2, r3, r2
	bl FS_ReadFile
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start FUN_020067D0
FUN_020067D0: ; 0x020067D0
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, #0x50
	ldrh r0, [r0, #0x0]
	add r4, r1, #0x0
	cmp r0, r4
	bhi _020067E4
	bl ErrorHandling
_020067E4:
	ldr r2, [r5, #0x48]
	lsl r1, r4, #0x3
	add r2, #0xc
	add r1, r2, r1
	add r0, r5, #0x0
	mov r2, #0x0
	bl FS_SeekFile
	add r0, r5, #0x0
	add r1, sp, #0x4
	mov r2, #0x4
	bl FS_ReadFile
	add r0, r5, #0x0
	add r1, sp, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	sub r0, r1, r0
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02006814
FUN_02006814: ; 0x02006814
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x50
	ldrh r0, [r0, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r0, r4
	bhi _0200682A
	bl ErrorHandling
_0200682A:
	ldr r2, [r5, #0x48]
	lsl r1, r4, #0x3
	add r2, #0xc
	add r1, r2, r1
	add r0, r5, #0x0
	mov r2, #0x0
	bl FS_SeekFile
	add r0, r5, #0x0
	add r1, sp, #0x0
	mov r2, #0x4
	bl FS_ReadFile
	ldr r2, [r5, #0x4c]
	ldr r1, [sp, #0x0]
	add r2, #0x8
	add r1, r2, r1
	add r0, r5, #0x0
	add r1, r6, r1
	mov r2, #0x0
	bl FS_SeekFile
	ldr r1, [sp, #0x18]
	add r0, r5, #0x0
	add r2, r7, #0x0
	bl FS_ReadFile
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02006864
FUN_02006864: ; 0x02006864
	add r3, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r3, _02006870 ; =FS_ReadFile
	bx r3
	nop
_02006870: .word FS_ReadFile

	thumb_func_start FUN_02006874
FUN_02006874: ; 0x02006874
	add r0, #0x50
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
