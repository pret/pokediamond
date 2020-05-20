    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021064C0
	.extern UNK_021064B8

	.text

	thumb_func_start FUN_0206DE24
FUN_0206DE24: ; 0x0206DE24
	push {r3, lr}
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _0206DE44 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0206DE48 ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	pop {r3, pc}
	.balign 4
_0206DE44: .word 0xFFFFE0FF
_0206DE48: .word 0x04001000

	thumb_func_start FUN_0206DE4C
FUN_0206DE4C: ; 0x0206DE4C
	push {r3, lr}
	mov r0, #0x7
	str r0, [sp, #0x0]
	ldr r0, _0206DE70 ; =0x04000050
	mov r1, #0x0
	mov r2, #0xe
	mov r3, #0xb
	bl G2x_SetBlendAlpha_
	mov r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, _0206DE74 ; =0x04001050
	mov r1, #0x0
	mov r2, #0xe
	mov r3, #0x7
	bl G2x_SetBlendAlpha_
	pop {r3, pc}
	.balign 4
_0206DE70: .word 0x04000050
_0206DE74: .word 0x04001050

	thumb_func_start FUN_0206DE78
FUN_0206DE78: ; 0x0206DE78
	push {r3, lr}
	sub sp, #0x8
	mov r2, #0x2
	ldr r1, _0206DE90 ; =FUN_0206DE94
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	mov r1, #0x0
	add r3, r1, #0x0
	bl FUN_02022318
	add sp, #0x8
	pop {r3, pc}
	.balign 4
_0206DE90: .word FUN_0206DE94

	thumb_func_start FUN_0206DE94
FUN_0206DE94: ; 0x0206DE94
	push {r3, lr}
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_0201E6E4
	ldr r0, _0206DF00 ; =0x04000008
	mov r1, #0x3
	ldrh r2, [r0, #0x0]
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r0, #0x0]
	add r0, #0x58
	ldrh r2, [r0, #0x0]
	ldr r1, _0206DF04 ; =0xFFFFCFFD
	and r2, r1
	strh r2, [r0, #0x0]
	add r2, r1, #0x2
	ldrh r3, [r0, #0x0]
	add r1, r1, #0x2
	and r3, r2
	mov r2, #0x10
	orr r2, r3
	strh r2, [r0, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r2, _0206DF08 ; =0x0000CFFB
	and r3, r2
	strh r3, [r0, #0x0]
	ldrh r3, [r0, #0x0]
	sub r2, #0x1c
	and r3, r1
	mov r1, #0x8
	orr r1, r3
	strh r1, [r0, #0x0]
	ldrh r1, [r0, #0x0]
	and r1, r2
	strh r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl G3X_SetFog
	mov r0, #0x0
	ldr r2, _0206DF0C ; =0x00007FFF
	add r1, r0, #0x0
	mov r3, #0x3f
	str r0, [sp, #0x0]
	bl G3X_SetClearColor
	ldr r1, _0206DF10 ; =0xBFFF0000
	ldr r0, _0206DF14 ; =0x04000580
	str r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_0206DF00: .word 0x04000008
_0206DF04: .word 0xFFFFCFFD
_0206DF08: .word 0x0000CFFB
_0206DF0C: .word 0x00007FFF
_0206DF10: .word 0xBFFF0000
_0206DF14: .word 0x04000580

	thumb_func_start FUN_0206DF18
FUN_0206DF18: ; 0x0206DF18
	push {r3-r5, lr}
	ldr r3, _0206DF50 ; =UNK_021064B8
	mov r0, #0x2
	mov r1, #0x0
	ldr r3, [r3, #0x0]
	lsl r0, r0, #0xe
	add r2, r1, #0x0
	blx r3
	ldr r3, _0206DF54 ; =UNK_021064C0
	mov r1, #0x0
	add r4, r0, #0x0
	ldr r3, [r3, #0x0]
	mov r0, #0xa0
	add r2, r1, #0x0
	blx r3
	add r5, r0, #0x0
	cmp r4, #0x0
	bne _0206DF40
	bl ErrorHandling
_0206DF40:
	cmp r5, #0x0
	bne _0206DF48
	bl ErrorHandling
_0206DF48:
	bl FUN_02012CC8
	pop {r3-r5, pc}
	nop
_0206DF50: .word UNK_021064B8
_0206DF54: .word UNK_021064C0

	thumb_func_start FUN_0206DF58
FUN_0206DF58: ; 0x0206DF58
	push {r3, lr}
	bl FUN_020222AC
	bl FUN_02013364
	cmp r0, #0x0
	ble _0206DF6E
	bl FUN_020222AC
	bl FUN_020B02C8
_0206DF6E:
	bl FUN_02013388
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020222B4
	pop {r3, pc}

	thumb_func_start FUN_0206DF7C
FUN_0206DF7C: ; 0x0206DF7C
	push {r4, lr}
	ldr r3, _0206DF94 ; =UNK_021064B8
	mov r2, #0x0
	ldr r3, [r3, #0x0]
	blx r3
	add r4, r0, #0x0
	bl FUN_0201327C
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_0206DF94: .word UNK_021064B8

	thumb_func_start FUN_0206DF98
FUN_0206DF98: ; 0x0206DF98
	push {r4, lr}
	ldr r3, _0206DFB0 ; =UNK_021064C0
	mov r2, #0x0
	ldr r3, [r3, #0x0]
	blx r3
	add r4, r0, #0x0
	bl FUN_020132BC
	lsl r0, r4, #0x10
	lsr r0, r0, #0xd
	pop {r4, pc}
	nop
_0206DFB0: .word UNK_021064C0

	thumb_func_start FUN_0206DFB4
FUN_0206DFB4: ; 0x0206DFB4
	push {r4, lr}
	sub sp, #0x8
	mov r1, #0x12
	lsl r1, r1, #0xa
	add r4, r0, #0x0
	bl FUN_02016998
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	mov r3, #0x12
	ldr r0, _0206DFF4 ; =FUN_0206DF7C
	ldr r1, _0206DFF8 ; =FUN_0206DF98
	lsl r3, r3, #0xa
	str r4, [sp, #0x4]
	bl FUN_02012CDC
	add r4, r0, #0x0
	bl FUN_0201343C
	add r2, r0, #0x0
	beq _0206DFEC
	mov r0, #0x1
	mov r1, #0xe1
	lsl r0, r0, #0xc
	lsl r1, r1, #0xe
	bl FUN_0201EC94
_0206DFEC:
	add r0, r4, #0x0
	add sp, #0x8
	pop {r4, pc}
	nop
_0206DFF4: .word FUN_0206DF7C
_0206DFF8: .word FUN_0206DF98

	thumb_func_start FUN_0206DFFC
FUN_0206DFFC: ; 0x0206DFFC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl FUN_0206DFB4
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0201318C
	add r1, r0, #0x0
	add r0, r4, #0x0
	mov r2, #0xa
	mov r3, #0x1
	bl FUN_02013194
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0206E024
FUN_0206E024: ; 0x0206E024
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020133E8
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02012DE4
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}

	thumb_func_start FUN_0206E03C
FUN_0206E03C: ; 0x0206E03C
	push {r3}
	sub sp, #0xc
	add r1, sp, #0x0
	mov r2, #0x0
	str r2, [r1, #0x0]
	str r2, [r1, #0x4]
	str r2, [r1, #0x8]
	mov r1, #0x56
	lsl r1, r1, #0x4
	str r2, [sp, #0x0]
	str r2, [sp, #0x8]
	str r1, [sp, #0x4]
	ldr r1, [r0, #0x20]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x4]
	add r1, r2, r1
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #0x4]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x8]
	add r1, r2, r1
	str r1, [r0, #0x2c]
	ldr r1, [r0, #0x20]
	ldr r2, [sp, #0x8]
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0xc]
	add r1, r2, r1
	str r1, [r0, #0x30]
	add sp, #0xc
	pop {r3}
	bx lr

	thumb_func_start FUN_0206E07C
FUN_0206E07C: ; 0x0206E07C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x10
	bl FUN_02016998
	add r4, r0, #0x0
	bne _0206E090
	bl ErrorHandling
_0206E090:
	ldr r0, [r5, #0x0]
	ldr r2, [r5, #0x4]
	mov r1, #0x7c
	str r0, [r4, #0x0]
	str r2, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0206DFFC
	mov r1, #0x1
	str r0, [r4, #0xc]
	bl FUN_02013440
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_0206E0AC
FUN_0206E0AC: ; 0x0206E0AC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	ldr r2, _0206E0C4 ; =FUN_0206E03C
	add r3, r4, #0x0
	bl FUN_020133AC
	ldr r0, [r4, #0xc]
	mov r1, #0x1
	bl FUN_02013440
	pop {r4, pc}
	.balign 4
_0206E0C4: .word FUN_0206E03C

	thumb_func_start FUN_0206E0C8
FUN_0206E0C8: ; 0x0206E0C8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl FUN_020133C8
	cmp r0, #0x0
	beq _0206E0D8
	mov r0, #0x1
	pop {r3, pc}
_0206E0D8:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0206E0DC
FUN_0206E0DC: ; 0x0206E0DC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl FUN_0206E024
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4
