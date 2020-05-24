	.include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global UNK_021C5998
UNK_021C5998: ; 0x021C5998
	.space 0x4

	.text

	thumb_func_start FUN_0201E00C
FUN_0201E00C: ; 0x0201E00C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _0201E064 ; =UNK_021C5998
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201E060
	add r0, r4, #0x0
	mov r1, #0x28
	bl FUN_02016998
	add r1, r0, #0x0
	ldr r0, _0201E064 ; =UNK_021C5998
	mov r2, #0x28
	str r1, [r0, #0x0]
	mov r0, #0x0
	bl MIi_CpuClear32
	ldr r0, _0201E064 ; =UNK_021C5998
	mov r1, #0x30
	ldr r0, [r0, #0x0]
	mul r1, r6
	str r6, [r0, #0x4]
	add r0, r4, #0x0
	bl FUN_02016998
	ldr r7, _0201E064 ; =UNK_021C5998
	mov r4, #0x0
	ldr r1, [r7, #0x0]
	cmp r6, #0x0
	str r0, [r1, #0x0]
	ble _0201E060
	add r5, r4, #0x0
_0201E04E:
	ldr r0, [r7, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	bl FUN_0201E2F8
	add r4, r4, #0x1
	add r5, #0x30
	cmp r4, r6
	blt _0201E04E
_0201E060:
	pop {r3-r7, pc}
	nop
_0201E064: .word UNK_021C5998

	thumb_func_start FUN_0201E068
FUN_0201E068: ; 0x0201E068
	cmp r1, #0x1
	bne _0201E078
	ldr r1, _0201E088 ; =UNK_021C5998
	ldr r2, [r1, #0x0]
	ldrh r1, [r2, #0x24]
	orr r0, r1
	strh r0, [r2, #0x24]
	bx lr
_0201E078:
	cmp r1, #0x2
	bne _0201E086
	ldr r1, _0201E088 ; =UNK_021C5998
	ldr r2, [r1, #0x0]
	ldrh r1, [r2, #0x26]
	orr r0, r1
	strh r0, [r2, #0x26]
_0201E086:
	bx lr
	.balign 4
_0201E088: .word UNK_021C5998

	thumb_func_start FUN_0201E08C
FUN_0201E08C: ; 0x0201E08C
	push {r3, lr}
	ldr r0, _0201E0B4 ; =UNK_021C5998
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201E0B2
	bl FUN_0201E1F0
	ldr r0, _0201E0B4 ; =UNK_021C5998
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201E0B4 ; =UNK_021C5998
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0201E0B4 ; =UNK_021C5998
	mov r1, #0x0
	str r1, [r0, #0x0]
_0201E0B2:
	pop {r3, pc}
	.balign 4
_0201E0B4: .word UNK_021C5998

	thumb_func_start FUN_0201E0B8
FUN_0201E0B8: ; 0x0201E0B8
	bx lr
	.balign 4

	thumb_func_start FUN_0201E0BC
FUN_0201E0BC: ; 0x0201E0BC
	push {r3, lr}
	ldr r0, _0201E0E0 ; =UNK_021C5998
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	str r2, [r1, #0xc]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x10]
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x14]
	ldr r0, [r0, #0x0]
	str r2, [r0, #0x18]
	bl FUN_0201E464
	ldr r0, _0201E0E0 ; =UNK_021C5998
	ldr r0, [r0, #0x0]
	bl FUN_0201E574
	pop {r3, pc}
	.balign 4
_0201E0E0: .word UNK_021C5998

	thumb_func_start FUN_0201E0E4
FUN_0201E0E4: ; 0x0201E0E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0201E428
	add r4, r0, #0x0
	bne _0201E0F8
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E0F8:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E2C4
	cmp r0, #0x0
	bne _0201E108
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E108:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E314
	cmp r0, #0x0
	bne _0201E11E
	ldr r0, [r5, #0xc]
	bl FUN_0201E1C8
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E11E:
	add r0, r4, #0x0
	bl FUN_0201E57C
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0201E128
FUN_0201E128: ; 0x0201E128
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_0201E428
	add r4, r0, #0x0
	bne _0201E13C
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E13C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E2C4
	cmp r0, #0x0
	bne _0201E14C
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E14C:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0201E36C
	cmp r0, #0x0
	bne _0201E162
	ldr r0, [r5, #0xc]
	bl FUN_0201E1C8
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E162:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E168
FUN_0201E168: ; 0x0201E168
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bne _0201E174
	bl ErrorHandling
_0201E174:
	add r0, r4, #0x0
	bl FUN_0201E3F0
	add r4, r0, #0x0
	bne _0201E182
	bl ErrorHandling
_0201E182:
	str r5, [r4, #0x0]
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E19A
	ldr r3, [r4, #0x8]
	ldr r1, [r4, #0x24]
	ldr r2, [r5, #0xc]
	mov r0, #0xe
	lsl r3, r3, #0x5
	bl FUN_0201C2C8
_0201E19A:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E1B0
	ldr r3, [r4, #0x8]
	ldr r1, [r4, #0x28]
	ldr r2, [r5, #0xc]
	mov r0, #0x1e
	lsl r3, r3, #0x5
	bl FUN_0201C2C8
_0201E1B0:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E1B4
FUN_0201E1B4: ; 0x0201E1B4
	push {r3, lr}
	bl FUN_0201E3F0
	cmp r0, #0x0
	beq _0201E1C2
	mov r0, #0x1
	pop {r3, pc}
_0201E1C2:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201E1C8
FUN_0201E1C8: ; 0x0201E1C8
	push {r4, lr}
	bl FUN_0201E3F0
	add r4, r0, #0x0
	bne _0201E1D6
	bl ErrorHandling
_0201E1D6:
	add r0, r4, #0x0
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201E1EC
	add r0, r4, #0x0
	bl FUN_0201E5B8
	add r0, r4, #0x0
	bl FUN_0201E2BC
_0201E1EC:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201E1F0
FUN_0201E1F0: ; 0x0201E1F0
	push {r4-r6, lr}
	ldr r6, _0201E22C ; =UNK_021C5998
	mov r4, #0x0
	ldr r1, [r6, #0x0]
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	ble _0201E228
	add r5, r4, #0x0
_0201E200:
	ldr r1, [r1, #0x0]
	add r0, r1, r5
	add r0, #0x2c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0201E21C
	add r0, r1, r5
	bl FUN_0201E5B8
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	bl FUN_0201E2BC
_0201E21C:
	ldr r1, [r6, #0x0]
	add r4, r4, #0x1
	ldr r0, [r1, #0x4]
	add r5, #0x30
	cmp r4, r0
	blt _0201E200
_0201E228:
	pop {r4-r6, pc}
	nop
_0201E22C: .word UNK_021C5998

	thumb_func_start FUN_0201E230
FUN_0201E230: ; 0x0201E230
	push {r3, lr}
	bl FUN_0201E3F0
	cmp r0, #0x0
	bne _0201E244
	bne _0201E240
	bl ErrorHandling
_0201E240:
	mov r0, #0x0
	pop {r3, pc}
_0201E244:
	add r1, r0, #0x0
	add r1, #0x2c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	bne _0201E252
	add r0, #0x10
	pop {r3, pc}
_0201E252:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0201E258
FUN_0201E258: ; 0x0201E258
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_0201E3F0
	cmp r0, #0x0
	bne _0201E26E
	bne _0201E26A
	bl ErrorHandling
_0201E26A:
	mov r0, #0x0
	pop {r4, pc}
_0201E26E:
	add r1, r0, #0x0
	add r1, #0x2c
	ldrb r1, [r1, #0x0]
	cmp r1, #0x1
	beq _0201E27C
	mov r0, #0x0
	pop {r4, pc}
_0201E27C:
	ldr r1, [r0, #0x0]
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _0201E288
	mov r1, #0x1
	str r1, [r4, #0x18]
_0201E288:
	add r0, #0x10
	pop {r4, pc}

	thumb_func_start FUN_0201E28C
FUN_0201E28C: ; 0x0201E28C
	push {r4, lr}
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	beq _0201E29A
	mov r4, #0x2
	lsl r4, r4, #0x8
	b _0201E2A6
_0201E29A:
	ldr r2, [r0, #0x0]
	cmp r2, #0x4
	bne _0201E2A4
	mov r4, #0x0
	b _0201E2A6
_0201E2A4:
	mov r4, #0x20
_0201E2A6:
	cmp r4, #0x0
	beq _0201E2B6
	bl FUN_020B19C4
	add r1, r4, #0x0
	bl _u32_div_f
	pop {r4, pc}
_0201E2B6:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201E2BC
FUN_0201E2BC: ; 0x0201E2BC
	ldr r3, _0201E2C0 ; =FUN_0201E2F8
	bx r3
	.balign 4
_0201E2C0: .word FUN_0201E2F8

	thumb_func_start FUN_0201E2C4
FUN_0201E2C4: ; 0x0201E2C4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	bl FUN_0201E1B4
	cmp r0, #0x1
	bne _0201E2E0
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E2E0:
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x4]
	add r1, #0x2c
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r1, #0x0]
	ldr r1, [r5, #0x8]
	str r1, [r4, #0x8]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E2F8
FUN_0201E2F8: ; 0x0201E2F8
	push {r4, lr}
	mov r1, #0x0
	mov r2, #0x30
	add r4, r0, #0x0
	bl memset
	mov r0, #0x0
	mvn r0, r0
	str r0, [r4, #0xc]
	add r4, #0x10
	add r0, r4, #0x0
	bl FUN_020B19DC
	pop {r4, pc}

	thumb_func_start FUN_0201E314
FUN_0201E314: ; 0x0201E314
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r1, #0x0
	ldr r0, [r6, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0201E334
	ldr r0, _0201E368 ; =UNK_021C5998
	ldr r0, [r0, #0x0]
	add r4, r0, #0x0
	add r5, r0, #0x0
	ldr r3, [r0, #0x1c]
	add r4, #0x14
	add r5, #0x18
	ldr r0, [r0, #0x20]
	b _0201E344
_0201E334:
	ldr r0, _0201E368 ; =UNK_021C5998
	mov r3, #0x2
	ldr r5, [r0, #0x0]
	lsl r3, r3, #0x8
	add r4, r5, #0x0
	add r4, #0xc
	add r5, #0x10
	add r0, r3, #0x0
_0201E344:
	str r0, [sp, #0x0]
	ldr r1, [r4, #0x0]
	ldr r2, [r5, #0x0]
	add r0, r6, #0x0
	bl FUN_0201E5F4
	add r0, r6, #0x0
	bl FUN_0201E4AC
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_0201E640
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r6, pc}
	nop
_0201E368: .word UNK_021C5998

	thumb_func_start FUN_0201E36C
FUN_0201E36C: ; 0x0201E36C
	push {r4-r6, lr}
	add r5, r1, #0x0
	ldr r0, [r5, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _0201E37C
	bl ErrorHandling
_0201E37C:
	ldr r1, [r5, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E39E
	ldr r0, _0201E3EC ; =UNK_021C5998
	ldr r1, [r5, #0x8]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x24]
	bl FUN_0201E534
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	bne _0201E39E
	mov r0, #0x0
	pop {r4-r6, pc}
_0201E39E:
	ldr r1, [r5, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E3C0
	ldr r0, _0201E3EC ; =UNK_021C5998
	ldr r1, [r5, #0x8]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x26]
	bl FUN_0201E534
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _0201E3C0
	mov r0, #0x0
	pop {r4-r6, pc}
_0201E3C0:
	ldr r1, [r5, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E3CA
	str r6, [r5, #0x24]
_0201E3CA:
	ldr r1, [r5, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E3D4
	str r4, [r5, #0x28]
_0201E3D4:
	ldr r0, [r5, #0x8]
	lsl r1, r0, #0x5
	ldr r0, [r5, #0x0]
	str r1, [r0, #0x8]
	add r0, r5, #0x0
	bl FUN_0201E4BC
	add r0, r5, #0x0
	bl FUN_0201E57C
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
_0201E3EC: .word UNK_021C5998

	thumb_func_start FUN_0201E3F0
FUN_0201E3F0: ; 0x0201E3F0
	push {r4-r5}
	ldr r2, _0201E424 ; =UNK_021C5998
	mov r1, #0x0
	ldr r5, [r2, #0x0]
	ldr r2, [r5, #0x4]
	cmp r2, #0x0
	ble _0201E41C
	ldr r2, [r5, #0x0]
	add r4, r2, #0x0
_0201E402:
	ldr r3, [r4, #0xc]
	cmp r0, r3
	bne _0201E412
	mov r0, #0x30
	mul r0, r1
	add r0, r2, r0
	pop {r4-r5}
	bx lr
_0201E412:
	ldr r3, [r5, #0x4]
	add r1, r1, #0x1
	add r4, #0x30
	cmp r1, r3
	blt _0201E402
_0201E41C:
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	nop
_0201E424: .word UNK_021C5998

	thumb_func_start FUN_0201E428
FUN_0201E428: ; 0x0201E428
	push {r3-r4}
	ldr r1, _0201E460 ; =UNK_021C5998
	mov r0, #0x0
	ldr r4, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	ble _0201E458
	ldr r1, [r4, #0x0]
	add r3, r1, #0x0
_0201E43A:
	add r2, r3, #0x0
	add r2, #0x2c
	ldrb r2, [r2, #0x0]
	cmp r2, #0x0
	bne _0201E44E
	mov r2, #0x30
	mul r2, r0
	add r0, r1, r2
	pop {r3-r4}
	bx lr
_0201E44E:
	ldr r2, [r4, #0x4]
	add r0, r0, #0x1
	add r3, #0x30
	cmp r0, r2
	blt _0201E43A
_0201E458:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	nop
_0201E460: .word UNK_021C5998

	thumb_func_start FUN_0201E464
FUN_0201E464: ; 0x0201E464
	push {r3, lr}
	bl GX_GetBankForOBJExtPltt
	cmp r0, #0x20
	beq _0201E472
	cmp r0, #0x40
	bne _0201E47E
_0201E472:
	ldr r0, _0201E4A8 ; =UNK_021C5998
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	lsl r1, r1, #0xc
	str r1, [r0, #0x1c]
	b _0201E486
_0201E47E:
	ldr r0, _0201E4A8 ; =UNK_021C5998
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x1c]
_0201E486:
	bl GX_GetBankForSubOBJExtPltt
	mov r1, #0x1
	lsl r1, r1, #0x8
	cmp r0, r1
	bne _0201E49C
	ldr r0, _0201E4A8 ; =UNK_021C5998
	lsl r1, r1, #0x5
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x20]
	pop {r3, pc}
_0201E49C:
	ldr r0, _0201E4A8 ; =UNK_021C5998
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x20]
	pop {r3, pc}
	nop
_0201E4A8: .word UNK_021C5998

	thumb_func_start FUN_0201E4AC
FUN_0201E4AC: ; 0x0201E4AC
	ldr r1, [r0, #0x8]
	ldr r3, _0201E4B8 ; =FUN_0201E4BC
	lsl r2, r1, #0x5
	ldr r1, [r0, #0x0]
	str r2, [r1, #0x8]
	bx r3
	.balign 4
_0201E4B8: .word FUN_0201E4BC

	thumb_func_start FUN_0201E4BC
FUN_0201E4BC: ; 0x0201E4BC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x10
	bl FUN_020B19DC
	ldr r0, [r4, #0x4]
	mov r2, #0x1
	tst r0, r2
	beq _0201E4DA
	add r3, r4, #0x0
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x24]
	add r3, #0x10
	bl FUN_020B1240
_0201E4DA:
	ldr r0, [r4, #0x4]
	mov r2, #0x2
	tst r0, r2
	beq _0201E4EE
	ldr r0, [r4, #0x0]
	ldr r1, [r4, #0x28]
	add r4, #0x10
	add r3, r4, #0x0
	bl FUN_020B1240
_0201E4EE:
	pop {r4, pc}

	thumb_func_start FUN_0201E4F0
FUN_0201E4F0: ; 0x0201E4F0
	push {r4-r7}
	mov r3, #0x0
	cmp r1, #0x0
	ble _0201E50E
	mov r5, #0x1
_0201E4FA:
	ldrh r7, [r0, #0x0]
	add r4, r2, r3
	add r6, r5, #0x0
	lsl r6, r4
	add r4, r7, #0x0
	orr r4, r6
	add r3, r3, #0x1
	strh r4, [r0, #0x0]
	cmp r3, r1
	blt _0201E4FA
_0201E50E:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_0201E514
FUN_0201E514: ; 0x0201E514
	push {r4-r7}
	mov r4, #0x0
	cmp r1, #0x0
	ble _0201E530
	mov r6, #0x1
_0201E51E:
	add r5, r2, r4
	add r7, r6, #0x0
	ldrh r3, [r0, #0x0]
	lsl r7, r5
	bic r3, r7
	add r4, r4, #0x1
	strh r3, [r0, #0x0]
	cmp r4, r1
	blt _0201E51E
_0201E530:
	pop {r4-r7}
	bx lr

	thumb_func_start FUN_0201E534
FUN_0201E534: ; 0x0201E534
	push {r4-r7}
	mov r3, #0x0
	mov r6, #0x1
	add r2, r3, #0x0
_0201E53C:
	add r4, r2, #0x0
	b _0201E546
_0201E540:
	cmp r5, #0x10
	bge _0201E554
	add r4, r4, #0x1
_0201E546:
	add r5, r3, r4
	add r7, r6, #0x0
	lsl r7, r5
	tst r7, r0
	bne _0201E554
	cmp r4, r1
	blt _0201E540
_0201E554:
	cmp r4, r1
	bge _0201E560
	add r3, r3, r4
	add r3, r3, #0x1
	cmp r3, #0x10
	blt _0201E53C
_0201E560:
	cmp r3, #0x10
	blt _0201E56C
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
_0201E56C:
	lsl r0, r3, #0x5
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_0201E574
FUN_0201E574: ; 0x0201E574
	mov r1, #0x0
	strh r1, [r0, #0x24]
	strh r1, [r0, #0x26]
	bx lr

	thumb_func_start FUN_0201E57C
FUN_0201E57C: ; 0x0201E57C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E598
	ldr r0, _0201E5B4 ; =UNK_021C5998
	ldr r2, [r4, #0x24]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x24
	lsr r2, r2, #0x5
	bl FUN_0201E4F0
_0201E598:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E5B0
	ldr r0, _0201E5B4 ; =UNK_021C5998
	ldr r2, [r4, #0x28]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x26
	lsr r2, r2, #0x5
	bl FUN_0201E4F0
_0201E5B0:
	pop {r4, pc}
	nop
_0201E5B4: .word UNK_021C5998

	thumb_func_start FUN_0201E5B8
FUN_0201E5B8: ; 0x0201E5B8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201E5D4
	ldr r0, _0201E5F0 ; =UNK_021C5998
	ldr r2, [r4, #0x24]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x24
	lsr r2, r2, #0x5
	bl FUN_0201E514
_0201E5D4:
	ldr r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201E5EC
	ldr r0, _0201E5F0 ; =UNK_021C5998
	ldr r2, [r4, #0x28]
	ldr r0, [r0, #0x0]
	ldr r1, [r4, #0x8]
	add r0, #0x26
	lsr r2, r2, #0x5
	bl FUN_0201E514
_0201E5EC:
	pop {r4, pc}
	nop
_0201E5F0: .word UNK_021C5998

	thumb_func_start FUN_0201E5F4
FUN_0201E5F4: ; 0x0201E5F4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	ldr r2, [r5, #0x4]
	mov r0, #0x1
	tst r2, r0
	beq _0201E61A
	ldr r2, [r5, #0x8]
	lsl r2, r2, #0x5
	add r2, r1, r2
	cmp r2, r3
	bls _0201E618
	bl ErrorHandling
	bl FUN_0201E0B8
	mov r0, #0x0
	b _0201E61A
_0201E618:
	str r1, [r5, #0x24]
_0201E61A:
	ldr r2, [r5, #0x4]
	mov r1, #0x2
	tst r1, r2
	beq _0201E63C
	ldr r1, [r5, #0x8]
	lsl r1, r1, #0x5
	add r2, r4, r1
	ldr r1, [sp, #0x10]
	cmp r2, r1
	bls _0201E63A
	bl ErrorHandling
	bl FUN_0201E0B8
	mov r0, #0x0
	pop {r3-r5, pc}
_0201E63A:
	str r4, [r5, #0x28]
_0201E63C:
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201E640
FUN_0201E640: ; 0x0201E640
	push {r3-r4}
	ldr r4, [r0, #0x4]
	mov r3, #0x1
	tst r3, r4
	beq _0201E654
	ldr r3, [r0, #0x8]
	ldr r4, [r1, #0x0]
	lsl r3, r3, #0x5
	add r3, r4, r3
	str r3, [r1, #0x0]
_0201E654:
	ldr r3, [r0, #0x4]
	mov r1, #0x2
	tst r1, r3
	beq _0201E666
	ldr r0, [r0, #0x8]
	ldr r1, [r2, #0x0]
	lsl r0, r0, #0x5
	add r0, r1, r0
	str r0, [r2, #0x0]
_0201E666:
	pop {r3-r4}
	bx lr
	.balign 4
