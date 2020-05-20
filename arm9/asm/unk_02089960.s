    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FF3AC
	.extern UNK_020FF378
	.extern UNK_020FF390
	.extern UNK_020FF380
	.extern gUnknown21C48B8

	.text

	thumb_func_start FUN_02089960
FUN_02089960: ; 0x02089960
	push {r3-r5, lr}
	mov r2, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x58
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0x3c
	mov r2, #0x58
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x3c
	add r4, r0, #0x0
	bl memset
	mov r0, #0x58
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r0, [r0, #0x8]
	str r0, [r4, #0x34]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0208999C
FUN_0208999C: ; 0x0208999C
	push {r4-r6, lr}
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r6, r0, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	beq _020899B8
	cmp r1, #0x1
	beq _02089A12
	cmp r1, #0x2
	beq _02089A20
	b _02089A34
_020899B8:
	add r0, r4, #0x0
	add r1, r4, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	add r1, r4, #0x0
	bl FUN_0200E3A0
	add r0, r4, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	add r0, r4, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02089A38 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _02089A3C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	add r0, r6, #0x0
	bl FUN_02089A6C
	add r0, r6, #0x0
	bl FUN_02089B80
	bl FUN_0201E788
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02089A34
_02089A12:
	bl FUN_02089BE0
	cmp r0, #0x1
	bne _02089A34
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02089A34
_02089A20:
	bl FUN_02089BCC
	add r0, r6, #0x0
	bl FUN_02089B2C
	add r0, r4, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r4, #0x1
_02089A34:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02089A38: .word 0xFFFFE0FF
_02089A3C: .word 0x04001000

	thumb_func_start FUN_02089A40
FUN_02089A40: ; 0x02089A40
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	ldr r4, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_0200627C
	add r0, r4, #0x0
	bl FUN_020168D0
	ldr r0, _02089A64 ; =SDK_OVERLAY_MODULE_83_ID
	ldr r1, _02089A68 ; =0x0223A360
	bl FUN_02000E7C
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02089A64: .word SDK_OVERLAY_MODULE_83_ID
_02089A68: .word 0x0223A360

	thumb_func_start FUN_02089A6C
FUN_02089A6C: ; 0x02089A6C
	push {r4-r5, lr}
	sub sp, #0x5c
	ldr r5, _02089B18 ; =UNK_020FF3AC
	add r4, r0, #0x0
	add r3, sp, #0x34
	mov r2, #0x5
_02089A78:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02089A78
	add r0, sp, #0x34
	bl FUN_0201E66C
	ldr r0, [r4, #0x0]
	bl FUN_02016B94
	add r3, sp, #0x24
	ldr r5, _02089B1C ; =UNK_020FF380
	str r0, [r4, #0x18]
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _02089B20 ; =UNK_020FF390
	add r3, sp, #0x8
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	ldr r0, [r4, #0x18]
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _02089B24 ; =0x000001E2
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x18]
	mov r3, #0x2
	bl FUN_0200CD68
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _02089B28 ; =0x000001D9
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x18]
	mov r3, #0x3
	bl FUN_0200CB00
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	mov r1, #0x20
	bl FUN_02002ED0
	mov r0, #0x0
	ldr r3, [r4, #0x0]
	mov r1, #0x20
	add r2, r0, #0x0
	bl FUN_02017F18
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02017FE4
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_02017FE4
	add sp, #0x5c
	pop {r4-r5, pc}
	.balign 4
_02089B18: .word UNK_020FF3AC
_02089B1C: .word UNK_020FF380
_02089B20: .word UNK_020FF390
_02089B24: .word 0x000001E2
_02089B28: .word 0x000001D9

	thumb_func_start FUN_02089B2C
FUN_02089B2C: ; 0x02089B2C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0201797C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x5
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x6
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x7
	mov r1, #0x0
	bl FUN_0201797C
	ldr r0, [r4, #0x18]
	mov r1, #0x0
	bl FUN_020178A0
	ldr r0, [r4, #0x18]
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02089B80
FUN_02089B80: ; 0x02089B80
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r2, _02089BC4 ; =0x00000167
	ldr r3, [r4, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	bl FUN_0200A86C
	str r0, [r4, #0x1c]
	bl FUN_0201BD5C
	mov r0, #0x0
	str r0, [r4, #0xc]
	add r1, r4, #0x0
	ldr r0, [r4, #0x18]
	ldr r2, _02089BC8 ; =UNK_020FF378
	add r1, #0x20
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	mov r2, #0x0
	add r4, #0x20
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	add sp, #0x8
	pop {r4, pc}
	nop
_02089BC4: .word 0x00000167
_02089BC8: .word UNK_020FF378

	thumb_func_start FUN_02089BCC
FUN_02089BCC: ; 0x02089BCC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x20
	bl FUN_02019178
	ldr r0, [r4, #0x1c]
	bl FUN_0200A8B8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02089BE0
FUN_02089BE0: ; 0x02089BE0
	push {r4-r5, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r5, #0x0
	cmp r1, #0x5
	bhi _02089CC2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02089BFA: ; jump table (using 16-bit offset)
	.short _02089C06 - _02089BFA - 2; case 0
	.short _02089C3C - _02089BFA - 2; case 1
	.short _02089C68 - _02089BFA - 2; case 2
	.short _02089C76 - _02089BFA - 2; case 3
	.short _02089CA2 - _02089BFA - 2; case 4
	.short _02089CC0 - _02089BFA - 2; case 5
_02089C06:
	ldr r0, [r4, #0x34]
	bl FUN_02022800
	cmp r0, #0x3
	bhi _02089CC2
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02089C1C: ; jump table (using 16-bit offset)
	.short _02089C24 - _02089C1C - 2; case 0
	.short _02089C24 - _02089C1C - 2; case 1
	.short _02089C2A - _02089C1C - 2; case 2
	.short _02089C34 - _02089C1C - 2; case 3
_02089C24:
	mov r0, #0x5
	str r0, [r4, #0x4]
	b _02089CC2
_02089C2A:
	add r0, r5, #0x0
	str r0, [r4, #0x8]
	mov r0, #0x1
	str r0, [r4, #0x4]
	b _02089CC2
_02089C34:
	mov r0, #0x1
	str r0, [r4, #0x8]
	str r0, [r4, #0x4]
	b _02089CC2
_02089C3C:
	ldr r1, _02089CC8 ; =0x00006C21
	add r0, r5, #0x0
	bl FUN_02017FE4
	ldr r1, _02089CC8 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	mov r0, #0x6
	mov r1, #0x1
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x2
	str r0, [r4, #0x4]
	b _02089CC2
_02089C68:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02089CC2
	mov r0, #0x3
	str r0, [r4, #0x4]
	b _02089CC2
_02089C76:
	ldr r1, [r4, #0x8]
	add r2, r5, #0x0
	mov r3, #0x4
	bl FUN_02089CCC
	cmp r0, #0x1
	bne _02089CC2
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _02089CC2
_02089CA2:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02089CC2
	add r0, r5, #0x0
	add r1, r0, #0x0
	bl FUN_02017FE4
	mov r0, #0x4
	add r1, r5, #0x0
	bl FUN_02017FE4
	mov r0, #0x5
	str r0, [r4, #0x4]
	b _02089CC2
_02089CC0:
	mov r5, #0x1
_02089CC2:
	add r0, r5, #0x0
	add sp, #0xc
	pop {r4-r5, pc}
	.balign 4
_02089CC8: .word 0x00006C21

	thumb_func_start FUN_02089CCC
FUN_02089CCC: ; 0x02089CCC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	add r7, r1, #0x0
	add r4, r3, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	beq _02089CE8
	cmp r0, #0x1
	beq _02089D50
	cmp r0, #0x2
	beq _02089D6C
	b _02089D80
_02089CE8:
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x20
	mov r1, #0xf
	add r2, r6, #0x0
	add r3, r6, #0x0
	bl FUN_020196F4
	add r0, r5, #0x0
	ldr r2, _02089D88 ; =0x000001E2
	add r0, #0x20
	add r1, r6, #0x0
	mov r3, #0x2
	bl FUN_0200D0BC
	mov r0, #0x1
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	str r0, [r5, #0x14]
	ldr r0, [r5, #0x1c]
	ldr r2, [r5, #0x14]
	add r1, r7, #0x0
	bl FUN_0200A8E0
	add r3, r6, #0x0
	str r3, [sp, #0x0]
	str r4, [sp, #0x4]
	str r3, [sp, #0x8]
	add r0, r5, #0x0
	ldr r2, [r5, #0x14]
	add r0, #0x20
	mov r1, #0x1
	bl FUN_0201BD84
	str r0, [r5, #0x10]
	cmp r4, #0x0
	bne _02089D48
	ldr r0, [r5, #0x14]
	bl FUN_02021A20
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
_02089D48:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02089D80
_02089D50:
	ldr r0, [r5, #0x10]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02089D80
	ldr r0, [r5, #0x14]
	bl FUN_02021A20
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	b _02089D80
_02089D6C:
	cmp r2, #0x0
	bne _02089D7A
	ldr r0, _02089D8C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _02089D80
_02089D7A:
	mov r0, #0x0
	str r0, [r5, #0xc]
	mov r6, #0x1
_02089D80:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02089D88: .word 0x000001E2
_02089D8C: .word gUnknown21C48B8
