	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_0222FF68
MOD11_0222FF68: ; 0x0222FF68
	ldr r0, [r0, #4]
	bx lr

	thumb_func_start MOD11_0222FF6C
MOD11_0222FF6C: ; 0x0222FF6C
	ldr r2, [r0, #8]
	lsl r0, r1, #4
	add r0, r2, r0
	bx lr

	thumb_func_start MOD11_0222FF74
MOD11_0222FF74: ; 0x0222FF74
	ldr r0, [r0, #0x2c]
	bx lr

	thumb_func_start MOD11_0222FF78
MOD11_0222FF78: ; 0x0222FF78
	ldr r0, [r0, #0x30]
	bx lr

	thumb_func_start MOD11_0222FF7C
MOD11_0222FF7C: ; 0x0222FF7C
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r0, [r0, #0x34]
	bx lr

	thumb_func_start MOD11_0222FF84
MOD11_0222FF84: ; 0x0222FF84
	ldr r0, [r0, #0x44]
	bx lr

	thumb_func_start MOD11_0222FF88
MOD11_0222FF88: ; 0x0222FF88
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _0222FFA6
	mov r3, #0x10
	tst r2, r3
	beq _0222FFAE
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _0222FFAE
_0222FFA6:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	pop {r3, r4, r5, pc}
_0222FFAE:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _0222FFC0
	lsl r0, r4, #0x1f
	lsr r0, r0, #0x1d
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	pop {r3, r4, r5, pc}
_0222FFC0:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_0222FFC8
MOD11_0222FFC8: ; 0x0222FFC8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _0222FFE6
	mov r3, #0x10
	tst r2, r3
	beq _0222FFF2
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _0222FFF2
_0222FFE6:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	bl GetPartyCount
	pop {r3, r4, r5, pc}
_0222FFF2:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _02230008
	lsl r0, r4, #0x1f
	lsr r0, r0, #0x1d
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	bl GetPartyCount
	pop {r3, r4, r5, pc}
_02230008:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	bl GetPartyCount
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_02230014
MOD11_02230014: ; 0x02230014
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r2, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _02230034
	mov r3, #0x10
	tst r2, r3
	beq _02230042
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _02230042
_02230034:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	add r1, r6, #0
	bl GetPartyMonByIndex
	pop {r4, r5, r6, pc}
_02230042:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _0223005A
	lsl r0, r4, #0x1f
	lsr r0, r0, #0x1d
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	add r1, r6, #0
	bl GetPartyMonByIndex
	pop {r4, r5, r6, pc}
_0223005A:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x68]
	add r1, r6, #0
	bl GetPartyMonByIndex
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02230068
MOD11_02230068: ; 0x02230068
	add r0, #0x88
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD11_02230070
MOD11_02230070: ; 0x02230070
	add r0, #0x8c
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD11_02230078
MOD11_02230078: ; 0x02230078
	add r0, #0x90
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD11_02230080
MOD11_02230080: ; 0x02230080
	add r0, #0x94
	ldr r0, [r0]
	bx lr
	.align 2, 0

	thumb_func_start MOD11_02230088
MOD11_02230088: ; 0x02230088
	mov r2, #0x5f
	lsl r2, r2, #2
	add r2, r0, r2
	lsl r0, r1, #4
	add r0, r2, r0
	bx lr

	thumb_func_start MOD11_02230094
MOD11_02230094: ; 0x02230094
	mov r1, #0x67
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_0223009C
MOD11_0223009C: ; 0x0223009C
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bx lr

	thumb_func_start MOD11_022300A8
MOD11_022300A8: ; 0x022300A8
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #0x1a
	lsl r0, r0, #4
	str r2, [r1, r0]
	bx lr

	thumb_func_start MOD11_022300B4
MOD11_022300B4: ; 0x022300B4
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_022300BC
MOD11_022300BC: ; 0x022300BC
	mov r1, #0x6b
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_022300C4
MOD11_022300C4: ; 0x022300C4
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start MOD11_022300C8
MOD11_022300C8: ; 0x022300C8
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start MOD11_022300CC
MOD11_022300CC: ; 0x022300CC
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start MOD11_022300D0
MOD11_022300D0: ; 0x022300D0
	ldr r0, [r0, #0x60]
	bx lr

	thumb_func_start MOD11_022300D4
MOD11_022300D4: ; 0x022300D4
	mov r1, #0x89
	lsl r1, r1, #2
	add r0, r0, r1
	bx lr

	thumb_func_start MOD11_022300DC
MOD11_022300DC: ; 0x022300DC
	ldr r1, _022300E4 ; =0x00001224
	add r0, r0, r1
	bx lr
	nop
_022300E4: .word 0x00001224

	thumb_func_start MOD11_022300E8
MOD11_022300E8: ; 0x022300E8
	ldr r1, _022300F0 ; =0x000023E4
	add r0, r0, r1
	bx lr
	nop
_022300F0: .word 0x000023E4

	thumb_func_start MOD11_022300F4
MOD11_022300F4: ; 0x022300F4
	ldr r1, _022300FC ; =0x000023E6
	add r0, r0, r1
	bx lr
	nop
_022300FC: .word 0x000023E6

	thumb_func_start MOD11_02230100
MOD11_02230100: ; 0x02230100
	ldr r1, _02230108 ; =0x000023E8
	add r0, r0, r1
	bx lr
	nop
_02230108: .word 0x000023E8

	thumb_func_start MOD11_0223010C
MOD11_0223010C: ; 0x0223010C
	ldr r1, _02230114 ; =0x000023EA
	add r0, r0, r1
	bx lr
	nop
_02230114: .word 0x000023EA

	thumb_func_start MOD11_02230118
MOD11_02230118: ; 0x02230118
	ldr r1, _02230120 ; =0x000023EC
	add r0, r0, r1
	bx lr
	nop
_02230120: .word 0x000023EC

	thumb_func_start MOD11_02230124
MOD11_02230124: ; 0x02230124
	ldr r1, _0223012C ; =0x000023EE
	add r0, r0, r1
	bx lr
	nop
_0223012C: .word 0x000023EE

	thumb_func_start MOD11_02230130
MOD11_02230130: ; 0x02230130
	mov r1, #0x73
	lsl r1, r1, #2
	add r0, r0, r1
	bx lr

	thumb_func_start MOD11_02230138
MOD11_02230138: ; 0x02230138
	ldr r0, [r0, #0x14]
	bx lr

	thumb_func_start MOD11_0223013C
MOD11_0223013C: ; 0x0223013C
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start MOD11_02230140
MOD11_02230140: ; 0x02230140
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _0223015E
	mov r3, #0x10
	tst r2, r3
	beq _02230168
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _02230168
_0223015E:
	lsl r0, r4, #1
	add r0, r5, r0
	add r0, #0xa0
	ldrh r0, [r0]
	pop {r3, r4, r5, pc}
_02230168:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _0223017C
	lsl r0, r4, #0x1f
	lsr r0, r0, #0x1e
	add r0, r5, r0
	add r0, #0xa0
	ldrh r0, [r0]
	pop {r3, r4, r5, pc}
_0223017C:
	lsl r0, r4, #1
	add r0, r5, r0
	add r0, #0xa0
	ldrh r0, [r0]
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_02230188
MOD11_02230188: ; 0x02230188
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _022301A6
	mov r3, #0x10
	tst r2, r3
	beq _022301B0
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _022301B0
_022301A6:
	mov r0, #0x34
	add r5, #0xac
	mul r0, r4
	add r0, r5, r0
	pop {r3, r4, r5, pc}
_022301B0:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _022301C8
	mov r0, #1
	add r1, r4, #0
	and r1, r0
	mov r0, #0x34
	add r5, #0xac
	mul r0, r1
	add r0, r5, r0
	pop {r3, r4, r5, pc}
_022301C8:
	mov r0, #0x34
	add r5, #0xac
	mul r0, r4
	add r0, r5, r0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_022301D4
MOD11_022301D4: ; 0x022301D4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _022301F2
	mov r3, #0x10
	tst r2, r3
	beq _022301FA
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _022301FA
_022301F2:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x48]
	pop {r3, r4, r5, pc}
_022301FA:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _0223020C
	lsl r0, r4, #0x1f
	lsr r0, r0, #0x1d
	add r0, r5, r0
	ldr r0, [r0, #0x48]
	pop {r3, r4, r5, pc}
_0223020C:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x48]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_02230214
MOD11_02230214: ; 0x02230214
	ldr r0, [r0, #0x58]
	bx lr

	thumb_func_start MOD11_02230218
MOD11_02230218: ; 0x02230218
	ldr r0, [r0, #0x5c]
	bx lr

	thumb_func_start MOD11_0223021C
MOD11_0223021C: ; 0x0223021C
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r3, _02230228 ; =PlayerProfile_GetTrainerGender
	ldr r0, [r0, #0x48]
	bx r3
	nop
_02230228: .word PlayerProfile_GetTrainerGender

	thumb_func_start MOD11_0223022C
MOD11_0223022C: ; 0x0223022C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	add r7, r1, #0
	mov r4, #0
	cmp r0, #0
	ble _02230250
	add r5, r6, #0
_0223023C:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A4C
	cmp r7, r0
	beq _02230250
	ldr r0, [r6, #0x44]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _0223023C
_02230250:
	ldr r0, [r6, #0x44]
	cmp r4, r0
	blt _0223025A
	bl GF_AssertFail
_0223025A:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_02230260
MOD11_02230260: ; 0x02230260
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r3, _0223026C ; =MOD11_02253A4C
	ldr r0, [r0, #0x34]
	bx r3
	nop
_0223026C: .word MOD11_02253A4C

	thumb_func_start MOD11_02230270
MOD11_02230270: ; 0x02230270
	push {r3, lr}
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r0, [r0, #0x34]
	bl MOD11_02253A4C
	mov r1, #1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD11_02230288
MOD11_02230288: ; 0x02230288
	mov r1, #0x1b
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_02230290
MOD11_02230290: ; 0x02230290
	ldr r0, [r0, #0x64]
	bx lr

	thumb_func_start MOD11_02230294
MOD11_02230294: ; 0x02230294
	ldr r1, _022302A4 ; =0x000023FC
	ldr r0, [r0, r1]
	cmp r0, #0xc
	bgt _022302A0
	cmp r0, #0
	bge _022302A2
_022302A0:
	mov r0, #0xc
_022302A2:
	bx lr
	.align 2, 0
_022302A4: .word 0x000023FC

	thumb_func_start MOD11_022302A8
MOD11_022302A8: ; 0x022302A8
	mov r1, #9
	lsl r1, r1, #0xa
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_022302B0
MOD11_022302B0: ; 0x022302B0
	ldr r1, _022302B8 ; =0x00002404
	ldr r0, [r0, r1]
	bx lr
	nop
_022302B8: .word 0x00002404

	thumb_func_start MOD11_022302BC
MOD11_022302BC: ; 0x022302BC
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	bl MOD11_0222FF84
	str r0, [sp]
	add r0, r6, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _022302D8
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_022302D8:
	ldr r0, [sp]
	mov r4, #0
	cmp r0, #0
	ble _02230302
_022302E0:
	cmp r4, r5
	beq _022302FA
	add r0, r6, #0
	add r1, r4, #0
	bl MOD11_02230270
	add r7, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl MOD11_02230270
	cmp r7, r0
	beq _02230302
_022302FA:
	ldr r0, [sp]
	add r4, r4, #1
	cmp r4, r0
	blt _022302E0
_02230302:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_02230308
MOD11_02230308: ; 0x02230308
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	str r2, [sp]
	bl MOD11_0222FF84
	str r0, [sp, #4]
	add r0, r5, #0
	bl MOD11_0222FF74
	mov r1, #2
	tst r0, r1
	bne _0223032C
	mov r0, #1
	add sp, #8
	eor r0, r6
	pop {r3, r4, r5, r6, r7, pc}
_0223032C:
	ldr r0, [sp, #4]
	mov r4, #0
	cmp r0, #0
	ble _02230368
_02230334:
	cmp r4, r6
	beq _02230360
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02230260
	mov r1, #2
	and r1, r0
	ldr r0, [sp]
	cmp r0, r1
	bne _02230360
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02230270
	add r7, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02230270
	cmp r7, r0
	bne _02230368
_02230360:
	ldr r0, [sp, #4]
	add r4, r4, #1
	cmp r4, r0
	blt _02230334
_02230368:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_02230370
MOD11_02230370: ; 0x02230370
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r1, #0
	ldr r1, [sp, #0x38]
	add r5, r2, #0
	str r1, [sp, #0x38]
	add r1, r0, #0
	ldr r1, [r1, #0x30]
	add r4, r3, #0
	str r1, [sp, #0x1c]
	mov r1, #0
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #4]
	mov r2, #2
	add r3, r6, #0
	bl MOD11_0224C474
	str r0, [sp, #0x10]
	ldr r0, [sp, #4]
	bl MOD11_0222FF74
	cmp r0, #3
	beq _022303BA
	ldr r0, [sp, #4]
	bl MOD11_0222FF74
	mov r1, #0x10
	tst r0, r1
	beq _022303E0
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	bne _022303E0
_022303BA:
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl MOD11_022302BC
	add r3, r0, #0
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x1c]
	mov r2, #2
	bl MOD11_0224C474
	str r0, [sp, #0xc]
	cmp r0, r5
	bne _022303E4
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl MOD11_022302BC
	add r6, r0, #0
	b _022303E4
_022303E0:
	ldr r0, [sp, #0x10]
	str r0, [sp, #0xc]
_022303E4:
	ldr r0, [sp, #4]
	add r1, r6, #0
	add r2, r5, #0
	bl MOD11_02230014
	str r0, [sp, #0x18]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0x38]
	mov r1, #0xf
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230478
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	mov r1, #7
	str r0, [sp, #0x20]
	tst r1, r0
	beq _02230478
	mov r1, #7
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	add r2, sp, #0x20
	bl SetMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230434
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230474
_02230434:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	mov r1, #7
	str r0, [sp, #0x20]
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	add r3, sp, #0x20
	bl MOD11_0224379C
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	mov r3, #0
	bl MOD11_02243420
	ldr r1, _02230688 ; =0xF7FFFFFF
	str r0, [sp, #0x20]
	and r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	add r3, sp, #0x20
	bl MOD11_0224379C
_02230474:
	mov r0, #1
	str r0, [sp, #0x14]
_02230478:
	ldr r0, [sp, #0x38]
	mov r1, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022304DC
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	ldr r1, _0223068C ; =0x00000F88
	str r0, [sp, #0x20]
	tst r1, r0
	beq _022304DC
	ldr r1, _02230690 ; =0xFFFFF077
	add r2, sp, #0x20
	and r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	bl SetMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _022304B8
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022304D8
_022304B8:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	ldr r1, _02230690 ; =0xFFFFF077
	str r0, [sp, #0x20]
	and r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	add r3, sp, #0x20
	bl MOD11_0224379C
_022304D8:
	mov r0, #1
	str r0, [sp, #0x14]
_022304DC:
	ldr r0, [sp, #0x38]
	mov r1, #0x11
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230540
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	mov r1, #0x10
	str r0, [sp, #0x20]
	tst r1, r0
	beq _02230540
	mov r1, #0x10
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	add r2, sp, #0x20
	bl SetMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _0223051C
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _0223053C
_0223051C:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	mov r1, #0x10
	str r0, [sp, #0x20]
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	add r3, sp, #0x20
	bl MOD11_0224379C
_0223053C:
	mov r0, #1
	str r0, [sp, #0x14]
_02230540:
	ldr r0, [sp, #0x38]
	mov r1, #0x12
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022305A4
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	mov r1, #0x20
	str r0, [sp, #0x20]
	tst r1, r0
	beq _022305A4
	mov r1, #0x20
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	add r2, sp, #0x20
	bl SetMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230580
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022305A0
_02230580:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	mov r1, #0x20
	str r0, [sp, #0x20]
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	add r3, sp, #0x20
	bl MOD11_0224379C
_022305A0:
	mov r0, #1
	str r0, [sp, #0x14]
_022305A4:
	ldr r0, [sp, #0x38]
	mov r1, #0x13
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230608
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	mov r1, #0x40
	str r0, [sp, #0x20]
	tst r1, r0
	beq _02230608
	mov r1, #0x40
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	add r2, sp, #0x20
	bl SetMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _022305E4
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230604
_022305E4:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	mov r3, #0
	bl MOD11_02243420
	mov r1, #0x40
	str r0, [sp, #0x20]
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x34
	add r3, sp, #0x20
	bl MOD11_0224379C
_02230604:
	mov r0, #1
	str r0, [sp, #0x14]
_02230608:
	ldr r0, [sp, #0x38]
	mov r1, #0x14
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230650
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230626
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230650
_02230626:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	mov r3, #0
	bl MOD11_02243420
	mov r1, #7
	str r0, [sp, #0x20]
	tst r1, r0
	beq _02230650
	mov r1, #7
	bic r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	add r3, sp, #0x20
	bl MOD11_0224379C
	mov r0, #1
	str r0, [sp, #0x14]
_02230650:
	ldr r0, [sp, #0x38]
	mov r1, #0x15
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022306AC
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _0223066E
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022306AC
_0223066E:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	mov r3, #0
	bl MOD11_02243420
	mov r1, #0xf
	lsl r1, r1, #0x10
	str r0, [sp, #0x20]
	tst r1, r0
	beq _022306AC
	ldr r1, _02230694 ; =0xFFF0FFFF
	b _02230698
	.align 2, 0
_02230688: .word 0xF7FFFFFF
_0223068C: .word 0x00000F88
_02230690: .word 0xFFFFF077
_02230694: .word 0xFFF0FFFF
_02230698:
	mov r2, #0x35
	and r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	add r3, sp, #0x20
	bl MOD11_0224379C
	mov r0, #1
	str r0, [sp, #0x14]
_022306AC:
	ldr r0, [sp, #0x38]
	mov r1, #0x16
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230706
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x1c]
	mov r2, #1
	add r3, r6, #0
	bl MOD11_0224C474
	str r0, [sp, #0x20]
	cmp r0, #0
	bne _02230706
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x1c]
	mov r2, #0
	add r3, r6, #0
	bl MOD11_0224C474
	mov r1, #0x40
	str r0, [sp, #0x20]
	orr r0, r1
	str r0, [sp, #0x20]
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x1c]
	mov r2, #0
	add r3, r6, #0
	bl MOD11_0224C54C
	mov r0, #5
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x1c]
	mov r2, #1
	add r3, r6, #0
	bl MOD11_0224C54C
	mov r0, #1
	str r0, [sp, #0x14]
_02230706:
	ldr r0, [sp, #0x38]
	mov r1, #0x1b
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230744
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230724
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230744
_02230724:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x13
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0xc
	bge _02230744
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x13
	mov r3, #1
	bl MOD11_02243DB0
	mov r0, #1
	str r0, [sp, #0x14]
_02230744:
	ldr r0, [sp, #0x38]
	mov r1, #0x1c
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230782
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230762
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230782
_02230762:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x14
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0xc
	bge _02230782
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x14
	mov r3, #1
	bl MOD11_02243DB0
	mov r0, #1
	str r0, [sp, #0x14]
_02230782:
	ldr r0, [sp, #0x38]
	mov r1, #0x1d
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022307C0
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _022307A0
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022307C0
_022307A0:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x16
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0xc
	bge _022307C0
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x16
	mov r3, #1
	bl MOD11_02243DB0
	mov r0, #1
	str r0, [sp, #0x14]
_022307C0:
	ldr r0, [sp, #0x38]
	mov r1, #0x1e
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022307FE
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _022307DE
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022307FE
_022307DE:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x17
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0xc
	bge _022307FE
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x17
	mov r3, #1
	bl MOD11_02243DB0
	mov r0, #1
	str r0, [sp, #0x14]
_022307FE:
	ldr r0, [sp, #0x38]
	mov r1, #0x1f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _0223083C
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _0223081C
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _0223083C
_0223081C:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x15
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0xc
	bge _0223083C
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x15
	mov r3, #1
	bl MOD11_02243DB0
	mov r0, #1
	str r0, [sp, #0x14]
_0223083C:
	ldr r0, [sp, #0x38]
	mov r1, #0x20
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _0223087A
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _0223085A
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _0223087A
_0223085A:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x18
	mov r3, #0
	bl MOD11_02243420
	cmp r0, #0xc
	bge _0223087A
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x18
	mov r3, #1
	bl MOD11_02243DB0
	mov r0, #1
	str r0, [sp, #0x14]
_0223087A:
	ldr r0, [sp, #0x38]
	mov r1, #0x21
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022308C4
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230898
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022308C4
_02230898:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	mov r3, #0
	bl MOD11_02243420
	mov r1, #1
	lsl r1, r1, #0x14
	add r2, r0, #0
	str r0, [sp, #0x20]
	tst r2, r1
	bne _022308C4
	orr r0, r1
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	add r3, sp, #0x20
	bl MOD11_0224379C
	mov r0, #1
	str r0, [sp, #0x14]
_022308C4:
	ldr r0, [sp, #0x38]
	mov r1, #0x24
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _0223095A
	ldr r0, [sp, #0x38]
	mov r1, #0x37
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #0x20]
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x42
	mov r2, #0
	bl GetMonData
	cmp r7, r0
	beq _0223095A
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x20]
	add r1, #0x3a
	bl AddMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _0223091C
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230956
_0223091C:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	mov r3, #0
	bl MOD11_02243420
	mov r1, #2
	lsl r1, r1, #0x14
	tst r0, r1
	bne _02230956
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x4b
	mov r3, #0
	bl MOD11_02243420
	add r7, r0, #0
	add r0, r4, #0
	bl MaskOfFlagNo
	tst r0, r7
	bne _02230956
	add r4, #0x1f
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r1, r6, #0
	add r2, r4, #0
	bl MOD11_02243DB0
_02230956:
	mov r0, #1
	str r0, [sp, #0x14]
_0223095A:
	ldr r0, [sp, #0x38]
	mov r1, #0x25
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _022309F8
	ldr r0, [sp, #0x38]
	mov r1, #0x37
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #0x20]
	mov r4, #0
_0223097E:
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x3a
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	add r1, #0x42
	mov r2, #0
	bl GetMonData
	cmp r7, r0
	beq _022309F2
	add r1, r4, #0
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x20]
	add r1, #0x3a
	bl AddMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _022309B4
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _022309EE
_022309B4:
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x35
	mov r3, #0
	bl MOD11_02243420
	mov r1, #2
	lsl r1, r1, #0x14
	tst r0, r1
	bne _022309EE
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x4b
	mov r3, #0
	bl MOD11_02243420
	add r7, r0, #0
	add r0, r4, #0
	bl MaskOfFlagNo
	tst r0, r7
	bne _022309EE
	add r2, r4, #0
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r1, r6, #0
	add r2, #0x1f
	bl MOD11_02243DB0
_022309EE:
	mov r0, #1
	str r0, [sp, #0x14]
_022309F2:
	add r4, r4, #1
	cmp r4, #4
	blt _0223097E
_022309F8:
	ldr r0, [sp, #0x38]
	mov r1, #0x26
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	bne _02230A0C
	b _02230B14
_02230A0C:
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x38]
	mov r1, #0x17
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230A36
	ldr r0, [sp, #0x18]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	bne _02230A42
	mov r0, #1
	str r0, [sp, #0x20]
	b _02230A42
_02230A36:
	ldr r0, [sp, #0x18]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x20]
_02230A42:
	ldr r0, [sp, #0x20]
	cmp r0, #0
	beq _02230B14
	ldr r0, [sp, #0x18]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	add r4, r0, #0
	ldr r0, [sp, #0x18]
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	cmp r4, r0
	beq _02230B14
	ldr r0, [sp, #0x38]
	mov r1, #0x36
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #0x20]
	cmp r0, #0xfd
	beq _02230AA2
	cmp r0, #0xfe
	beq _02230A8C
	cmp r0, #0xff
	bne _02230AC2
	ldr r0, [sp, #0x18]
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x20]
	b _02230AC2
_02230A8C:
	ldr r0, [sp, #0x18]
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	lsr r0, r0, #1
	str r0, [sp, #0x20]
	bne _02230AC2
	mov r0, #1
	str r0, [sp, #0x20]
	b _02230AC2
_02230AA2:
	ldr r0, [sp, #0x18]
	mov r1, #0xa3
	mov r2, #0
	bl GetMonData
	mov r1, #0x19
	mul r1, r0
	add r0, r1, #0
	mov r1, #0x64
	bl _u32_div_f
	str r0, [sp, #0x20]
	cmp r0, #0
	bne _02230AC2
	mov r0, #1
	str r0, [sp, #0x20]
_02230AC2:
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #0x20]
	mov r1, #0xa2
	bl AddMonData
	ldr r0, [sp, #0x38]
	mov r1, #0x17
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	bne _02230B10
	ldr r0, [sp, #4]
	add r1, r6, #0
	bl MOD11_02230270
	cmp r0, #0
	beq _02230AF8
	ldr r0, [sp, #0x1c]
	add r1, r6, #0
	mov r2, #0x5f
	add r3, sp, #0x20
	bl MOD11_0224379C
	b _02230B10
_02230AF8:
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230B04
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230B10
_02230B04:
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r1, r6, #0
	mov r2, #0x2f
	bl MOD11_02243DB0
_02230B10:
	mov r0, #1
	str r0, [sp, #0x14]
_02230B14:
	ldr r0, [sp, #0x38]
	mov r1, #0x2d
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230B4A
	ldr r0, [sp, #0x18]
	mov r1, #9
	mov r2, #0
	bl GetMonData
	cmp r0, #0x64
	bhs _02230B4A
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _02230B4A
	ldr r0, [sp, #0x38]
	mov r1, #0x38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #8]
_02230B4A:
	ldr r0, [sp, #0x38]
	mov r1, #0x2e
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230B8E
	ldr r0, [sp, #0x18]
	mov r1, #9
	mov r2, #0
	bl GetMonData
	cmp r0, #0x64
	blo _02230B8E
	ldr r0, [sp, #0x18]
	mov r1, #9
	mov r2, #0
	bl GetMonData
	cmp r0, #0xc8
	bhs _02230B8E
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _02230B8E
	ldr r0, [sp, #0x38]
	mov r1, #0x39
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #8]
_02230B8E:
	ldr r0, [sp, #0x38]
	mov r1, #0x2f
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0
	beq _02230BC4
	ldr r0, [sp, #0x18]
	mov r1, #9
	mov r2, #0
	bl GetMonData
	cmp r0, #0xc8
	blo _02230BC4
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _02230BC4
	ldr r0, [sp, #0x38]
	mov r1, #0x3a
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	str r0, [sp, #8]
_02230BC4:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _02230C4A
	ble _02230C28
	ldr r0, [sp, #0x18]
	mov r1, #0x9a
	mov r2, #0
	bl GetMonData
	cmp r0, #0xb
	bne _02230BE0
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_02230BE0:
	ldr r0, [sp, #0x18]
	mov r1, #0x97
	mov r2, #0
	bl GetMonData
	add r4, r0, #0
	ldr r0, [sp, #4]
	bl MOD11_022302B0
	cmp r4, r0
	bne _02230BFC
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
_02230BFC:
	ldr r0, [sp, #0x18]
	mov r1, #6
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x38]
	mov r1, #1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #5
	bl GetItemAttr
	cmp r0, #0x34
	bne _02230C28
	ldr r1, [sp, #8]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #8]
_02230C28:
	ldr r0, [sp, #0x18]
	ldr r2, [sp, #8]
	mov r1, #9
	bl AddMonData
	ldr r0, [sp, #0x10]
	cmp r0, r5
	beq _02230C3E
	ldr r0, [sp, #0xc]
	cmp r0, r5
	bne _02230C4A
_02230C3E:
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #8]
	add r1, r6, #0
	mov r2, #0x2c
	bl MOD11_02243DB0
_02230C4A:
	ldr r0, [sp, #0x14]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}

	thumb_func_start MOD11_02230C50
MOD11_02230C50: ; 0x02230C50
	ldr r1, _02230C58 ; =0x00002408
	ldr r0, [r0, r1]
	bx lr
	nop
_02230C58: .word 0x00002408

	thumb_func_start MOD11_02230C5C
MOD11_02230C5C: ; 0x02230C5C
	ldr r1, _02230C64 ; =0x0000240C
	ldr r0, [r0, r1]
	bx lr
	nop
_02230C64: .word 0x0000240C

	thumb_func_start MOD11_02230C68
MOD11_02230C68: ; 0x02230C68
	mov r2, #9
	lsl r2, r2, #0xa
	ldr r1, [r0, r2]
	cmp r1, #5
	bhi _02230CB4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02230C7E: ; jump table
	.short _02230C8A - _02230C7E - 2 ; case 0
	.short _02230C8A - _02230C7E - 2 ; case 1
	.short _02230C8A - _02230C7E - 2 ; case 2
	.short _02230C8A - _02230C7E - 2 ; case 3
	.short _02230C8A - _02230C7E - 2 ; case 4
	.short _02230C8A - _02230C7E - 2 ; case 5
_02230C8A:
	add r2, #0xc
	ldr r1, [r0, r2]
	cmp r1, #4
	bhi _02230CB6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02230C9E: ; jump table
	.short _02230CA8 - _02230C9E - 2 ; case 0
	.short _02230CA8 - _02230C9E - 2 ; case 1
	.short _02230CAC - _02230C9E - 2 ; case 2
	.short _02230CB0 - _02230C9E - 2 ; case 3
	.short _02230CB0 - _02230C9E - 2 ; case 4
_02230CA8:
	mov r0, #0
	bx lr
_02230CAC:
	mov r0, #1
	bx lr
_02230CB0:
	mov r0, #2
	bx lr
_02230CB4:
	mov r0, #0
_02230CB6:
	bx lr

	thumb_func_start MOD11_02230CB8
MOD11_02230CB8: ; 0x02230CB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD11_02230260
	cmp r0, #4
	bne _02230D32
	ldr r1, [r5, #0x2c]
	mov r0, #8
	tst r0, r1
	bne _02230D32
	mov r0, #4
	tst r0, r1
	beq _02230CEE
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_022302BC
	bl MaskOfFlagNo
	mov r1, #0x91
	lsl r1, r1, #6
	ldrb r1, [r5, r1]
	tst r0, r1
	bne _02230D32
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230CEE:
	ldr r1, [r5, #0x30]
	add r0, r5, #0
	mov r2, #0xc
	mov r3, #0
	bl MOD11_0224C474
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r1, [r5, #0x30]
	add r0, r5, #0
	mov r2, #8
	mov r3, #0
	bl MOD11_0224C474
	cmp r0, #0xe
	bne _02230D12
	cmp r4, #0x10
	bhi _02230D2A
_02230D12:
	ldr r1, [r5, #0x30]
	add r0, r5, #0
	mov r2, #0xa
	mov r3, #0
	bl MOD11_0224C474
	add r4, r0, #0
	mov r0, #0
	bl MaskOfFlagNo
	tst r0, r4
	beq _02230D2E
_02230D2A:
	mov r0, #0
	pop {r3, r4, r5, pc}
_02230D2E:
	mov r0, #1
	pop {r3, r4, r5, pc}
_02230D32:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_02230D38
MOD11_02230D38: ; 0x02230D38
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r5, #0x14]
	add r4, r1, #0
	add r7, r2, #0
	cmp r0, #1
	beq _02230D5A
	cmp r0, #4
	beq _02230D5A
	cmp r0, #5
	beq _02230D5A
	ldr r0, [sp, #4]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02230D5A:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _02230DCE
_02230D64:
	mov r0, #0
	str r0, [r4]
	cmp r0, #6
	bge _02230D9C
	mov r6, #0x5e
	lsl r6, r6, #2
_02230D70:
	bl MaskOfFlagNo
	ldr r1, [r5, r6]
	tst r0, r1
	beq _02230D92
	ldr r0, [r4]
	bl MaskOfFlagNo
	mov r3, #0x5e
	lsl r3, r3, #2
	mov r2, #0
	mvn r2, r2
	ldr r1, [r5, r3]
	eor r0, r2
	and r0, r1
	str r0, [r5, r3]
	b _02230D9C
_02230D92:
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	cmp r0, #6
	blt _02230D70
_02230D9C:
	ldr r1, [r4]
	cmp r1, #6
	bge _02230DC4
	ldr r0, [r5, #4]
	bl GetPartyMonByIndex
	mov r3, #0x59
	str r7, [sp]
	lsl r3, r3, #2
	ldr r3, [r5, r3]
	add r1, r0, #0
	lsl r3, r3, #0x10
	ldr r0, [r5, #4]
	mov r2, #0
	lsr r3, r3, #0x10
	bl GetMonEvolution
	str r0, [sp, #4]
	cmp r0, #0
	bne _02230DD0
_02230DC4:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	bne _02230D64
_02230DCE:
	ldr r0, [sp, #4]
_02230DD0:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_02230DD4
MOD11_02230DD4: ; 0x02230DD4
	ldr r1, _02230DDC ; =0x000023F8
	ldrb r0, [r0, r1]
	bx lr
	nop
_02230DDC: .word 0x000023F8

	thumb_func_start MOD11_02230DE0
MOD11_02230DE0: ; 0x02230DE0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #0
	bne _02230DEE
	bl GF_AssertFail
_02230DEE:
	ldr r1, [r4, #0x30]
	add r0, r4, #0
	mov r2, #5
	mov r3, #0
	bl MOD11_0224C474
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r4, pc}

	thumb_func_start MOD11_02230E00
MOD11_02230E00: ; 0x02230E00
	ldr r1, _02230E08 ; =0x00002410
	ldr r0, [r0, r1]
	bx lr
	nop
_02230E08: .word 0x00002410

	thumb_func_start MOD11_02230E0C
MOD11_02230E0C: ; 0x02230E0C
	ldr r2, _02230E14 ; =0x00002410
	str r1, [r0, r2]
	bx lr
	nop
_02230E14: .word 0x00002410

	thumb_func_start MOD11_02230E18
MOD11_02230E18: ; 0x02230E18
	mov r1, #0x6d
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_02230E20
MOD11_02230E20: ; 0x02230E20
	push {r3, lr}
	ldr r2, [r0, #0x2c]
	mov r1, #4
	tst r1, r2
	beq _02230E2E
	mov r0, #1
	pop {r3, pc}
_02230E2E:
	mov r1, #0x6d
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl Options_GetBattleScene
	cmp r0, #0
	bne _02230E40
	mov r0, #1
	pop {r3, pc}
_02230E40:
	mov r0, #0
	pop {r3, pc}

	thumb_func_start MOD11_02230E44
MOD11_02230E44: ; 0x02230E44
	mov r1, #0x6d
	lsl r1, r1, #2
	ldr r3, _02230E50 ; =Options_GetFrame
	ldr r0, [r0, r1]
	bx r3
	nop
_02230E50: .word Options_GetFrame

	thumb_func_start MOD11_02230E54
MOD11_02230E54: ; 0x02230E54
	push {r3, lr}
	ldr r2, [r0, #0x2c]
	mov r1, #4
	tst r1, r2
	beq _02230E62
	mov r0, #1
	pop {r3, pc}
_02230E62:
	mov r1, #0x6d
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl Options_GetTextFrameDelay
	pop {r3, pc}
	.align 2, 0

	thumb_func_start MOD11_02230E70
MOD11_02230E70: ; 0x02230E70
	mov r1, #0x6d
	lsl r1, r1, #2
	ldr r3, _02230E7C ; =Options_GetBattleStyle
	ldr r0, [r0, r1]
	bx r3
	nop
_02230E7C: .word Options_GetBattleStyle

	thumb_func_start MOD11_02230E80
MOD11_02230E80: ; 0x02230E80
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_02230E88
MOD11_02230E88: ; 0x02230E88
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r2, [r5, #0x2c]
	mov r3, #8
	add r4, r1, #0
	tst r3, r2
	bne _02230EA6
	mov r3, #0x10
	tst r2, r3
	beq _02230EAE
	bl MOD11_02230260
	mov r1, #1
	tst r0, r1
	beq _02230EAE
_02230EA6:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x78]
	pop {r3, r4, r5, pc}
_02230EAE:
	ldr r1, [r5, #0x2c]
	mov r0, #2
	tst r0, r1
	beq _02230EC0
	lsl r0, r4, #0x1f
	lsr r0, r0, #0x1d
	add r0, r5, r0
	ldr r0, [r0, #0x78]
	pop {r3, r4, r5, pc}
_02230EC0:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x78]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_02230EC8
MOD11_02230EC8: ; 0x02230EC8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r1, #0xa9
	ldr r2, [r5, #0x2c]
	lsl r1, r1, #2
	tst r1, r2
	bne _02230F66
	mov r4, #0
	add r1, r4, #0
	bl MOD11_0222FFC8
	cmp r0, #0
	ble _02230F66
	add r7, r4, #0
_02230EE4:
	add r0, r5, #0
	mov r1, #0
	add r2, r4, #0
	bl MOD11_02230014
	mov r1, #0xad
	mov r2, #0
	add r6, r0, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0x67
	lsl r0, r0, #2
	cmp r1, r0
	bne _02230F58
	add r0, r4, #0
	bl MaskOfFlagNo
	ldr r1, _02230F68 ; =0x00002414
	ldrb r1, [r5, r1]
	tst r0, r1
	beq _02230F58
	add r0, r5, #0
	bl MOD11_02230294
	cmp r0, #0xb
	bhi _02230F40
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02230F28: ; jump table
	.short _02230F44 - _02230F28 - 2 ; case 0
	.short _02230F44 - _02230F28 - 2 ; case 1
	.short _02230F40 - _02230F28 - 2 ; case 2
	.short _02230F40 - _02230F28 - 2 ; case 3
	.short _02230F44 - _02230F28 - 2 ; case 4
	.short _02230F44 - _02230F28 - 2 ; case 5
	.short _02230F40 - _02230F28 - 2 ; case 6
	.short _02230F40 - _02230F28 - 2 ; case 7
	.short _02230F40 - _02230F28 - 2 ; case 8
	.short _02230F4A - _02230F28 - 2 ; case 9
	.short _02230F40 - _02230F28 - 2 ; case 10
	.short _02230F4A - _02230F28 - 2 ; case 11
_02230F40:
	str r7, [sp]
	b _02230F4E
_02230F44:
	mov r0, #1
	str r0, [sp]
	b _02230F4E
_02230F4A:
	mov r0, #2
	str r0, [sp]
_02230F4E:
	add r0, r6, #0
	mov r1, #0x70
	add r2, sp, #0
	bl SetMonData
_02230F58:
	add r0, r5, #0
	mov r1, #0
	add r4, r4, #1
	bl MOD11_0222FFC8
	cmp r4, r0
	blt _02230EE4
_02230F66:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02230F68: .word 0x00002414

	thumb_func_start MOD11_02230F6C
MOD11_02230F6C: ; 0x02230F6C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r2, #0
	add r4, r1, #0
	bl MaskOfFlagNo
	ldr r1, _02230F84 ; =0x00002414
	add r2, r5, r1
	ldrb r1, [r2, r4]
	orr r0, r1
	strb r0, [r2, r4]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02230F84: .word 0x00002414

	thumb_func_start MOD11_02230F88
MOD11_02230F88: ; 0x02230F88
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x98
	ldr r0, [r0]
	cmp r0, #0
	beq _02230FA4
	add r0, r1, #0
	bl FUN_020690E4
	add r4, #0x98
	add r1, r0, #0
	ldr r0, [r4]
	bl Save_Poketch_PokemonHistoryAddMon
_02230FA4:
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_02230FA8
MOD11_02230FA8: ; 0x02230FA8
	push {r3, r4, lr}
	sub sp, #4
	add r3, r0, #0
	mov r0, #5
	str r0, [sp]
	ldr r4, _02230FC8 ; =0x0000241C
	add r0, r3, #0
	ldrb r2, [r3, r4]
	add r4, r4, #2
	add r0, #0x9c
	ldrh r3, [r3, r4]
	ldr r0, [r0]
	bl FUN_02061028
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02230FC8: .word 0x0000241C

	thumb_func_start MOD11_02230FCC
MOD11_02230FCC: ; 0x02230FCC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	mov r1, #1
	add r4, r0, #0
	mov r0, #5
	lsl r1, r1, #0x10
	bl AllocFromHeap
	mov r1, #0x87
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #5
	sub r1, #0x1c
	bl AllocFromHeap
	mov r1, #0x22
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r1, r1, #4
	mov r2, #1
	ldr r0, _02231224 ; =0x06010000
	ldr r1, [r4, r1]
	lsl r2, r2, #0x10
	bl MIi_CpuCopy32
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r5, [r4, r0]
	ldr r0, [r4, #0x28]
	mov r1, #0
	bl PaletteData_GetUnfadedBuf
	mov r2, #2
	add r1, r5, #0
	lsl r2, r2, #8
	bl MIi_CpuCopy32
	mov r0, #0x19
	lsl r0, r0, #0x16
	str r0, [sp, #0x24]
	mov r0, #0x63
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r0, [r0]
	bl FUN_02020350
	ldr r1, [r0, #4]
	ldr r0, [sp, #0x24]
	add r0, r0, r1
	str r0, [sp, #0x24]
	mov r0, #0x14
	str r0, [sp, #0x28]
	lsl r0, r0, #0xb
	str r0, [sp, #0xc]
_02231038:
	mov r0, #0x10
	mov ip, r0
	lsl r0, r0, #6
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x28]
	mov r7, #1
	sub r0, #0x14
	lsl r1, r0, #8
	ldr r0, [sp, #0x24]
	add r0, r0, r1
	str r0, [sp, #0x10]
_0223104E:
	mov r0, ip
	sub r0, #0x10
	ldr r1, [sp, #0x10]
	lsl r3, r0, #5
	add r3, r1, r3
	ldr r5, [sp, #0xc]
	ldr r1, [sp, #0x14]
	mov r2, #0
	add r6, r5, r1
_02231060:
	cmp r0, #8
	bge _02231088
	add r1, r2, #0
	tst r1, r7
	beq _0223107A
	lsr r1, r2, #0x1f
	add r1, r2, r1
	asr r1, r1, #1
	ldrb r5, [r3, r1]
	mov r1, #0xf0
	and r1, r5
	asr r1, r1, #4
	b _022310B6
_0223107A:
	lsr r1, r2, #0x1f
	add r1, r2, r1
	asr r1, r1, #1
	ldrb r5, [r3, r1]
	mov r1, #0xf
	and r1, r5
	b _022310B6
_02231088:
	mov r1, #1
	tst r1, r2
	beq _022310A4
	lsr r1, r2, #0x1f
	add r1, r2, r1
	asr r1, r1, #1
	add r5, r3, r1
	mov r1, #7
	lsl r1, r1, #8
	ldrb r5, [r5, r1]
	mov r1, #0xf0
	and r1, r5
	asr r1, r1, #4
	b _022310B6
_022310A4:
	lsr r1, r2, #0x1f
	add r1, r2, r1
	asr r1, r1, #1
	add r5, r3, r1
	mov r1, #7
	lsl r1, r1, #8
	ldrb r5, [r5, r1]
	mov r1, #0xf
	and r1, r5
_022310B6:
	cmp r1, #0
	beq _022310C6
	mov r5, #0x87
	lsl r5, r5, #2
	ldr r5, [r4, r5]
	add r1, #0x70
	add r5, r6, r5
	strb r1, [r2, r5]
_022310C6:
	add r2, r2, #1
	cmp r2, #0x40
	blt _02231060
	ldr r0, [sp, #0x14]
	add r0, #0x40
	str r0, [sp, #0x14]
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #0x20
	blt _0223104E
	mov r1, #2
	ldr r0, [sp, #0xc]
	lsl r1, r1, #0xa
	add r0, r0, r1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x28]
	add r0, r0, #1
	str r0, [sp, #0x28]
	cmp r0, #0x1c
	blt _02231038
	mov r0, #0x19
	lsl r0, r0, #0x16
	str r0, [sp, #8]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r0, [r0]
	bl FUN_02020350
	ldr r1, [r0, #4]
	ldr r0, [sp, #8]
	mov r7, #0x26
	add r0, r0, r1
	str r0, [sp, #8]
	mov r3, #0
	mov r0, #0xf
	mov r1, #0xf0
	lsl r7, r7, #0xa
	mov r2, #1
_02231116:
	add r5, r3, #0
	tst r5, r2
	beq _0223112C
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r6, r5, #1
	ldr r5, [sp, #8]
	ldrb r5, [r5, r6]
	and r5, r1
	asr r5, r5, #4
	b _02231138
_0223112C:
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r6, r5, #1
	ldr r5, [sp, #8]
	ldrb r5, [r5, r6]
	and r5, r0
_02231138:
	cmp r5, #0
	beq _02231148
	mov r6, #0x87
	lsl r6, r6, #2
	ldr r6, [r4, r6]
	add r5, #0x70
	add r6, r6, r3
	strb r5, [r6, r7]
_02231148:
	mov r5, #2
	add r3, r3, #1
	lsl r5, r5, #0xa
	cmp r3, r5
	blt _02231116
	mov r0, #0x1c
	str r0, [sp, #4]
	lsl r0, r0, #0xb
	str r0, [sp, #0x18]
_0223115A:
	ldr r0, [sp, #4]
	mov r2, #0
	sub r0, #0x1c
	lsl r1, r0, #8
	ldr r0, [sp, #8]
	str r2, [sp, #0x20]
	add r0, r0, r1
	str r0, [sp, #0x1c]
	mov r7, #1
_0223116C:
	asr r0, r2, #2
	lsr r0, r0, #0x1d
	add r0, r2, r0
	asr r0, r0, #3
	lsl r1, r0, #0xa
	ldr r0, [sp, #0x1c]
	lsr r5, r2, #0x1f
	add r6, r0, r1
	lsl r1, r2, #0x1d
	sub r1, r1, r5
	mov r0, #0x1d
	ror r1, r0
	add r0, r5, r1
	lsl r0, r0, #5
	ldr r5, [sp, #0x18]
	ldr r1, [sp, #0x20]
	mov r3, #0
	add r0, r6, r0
	add r1, r5, r1
_02231192:
	add r5, r3, #0
	tst r5, r7
	beq _022311AE
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r5, r5, #1
	add r6, r0, r5
	mov r5, #1
	lsl r5, r5, #0xa
	ldrb r6, [r6, r5]
	mov r5, #0xf0
	and r5, r6
	asr r5, r5, #4
	b _022311C0
_022311AE:
	lsr r5, r3, #0x1f
	add r5, r3, r5
	asr r5, r5, #1
	add r6, r0, r5
	mov r5, #1
	lsl r5, r5, #0xa
	ldrb r6, [r6, r5]
	mov r5, #0xf
	and r5, r6
_022311C0:
	cmp r5, #0
	beq _022311D0
	mov r6, #0x87
	lsl r6, r6, #2
	ldr r6, [r4, r6]
	add r5, #0x70
	add r6, r1, r6
	strb r5, [r3, r6]
_022311D0:
	add r3, r3, #1
	cmp r3, #0x40
	blt _02231192
	ldr r0, [sp, #0x20]
	add r2, r2, #1
	add r0, #0x40
	str r0, [sp, #0x20]
	cmp r2, #0x18
	blt _0223116C
	mov r3, #2
	ldr r0, [sp, #0x18]
	lsl r3, r3, #0xa
	add r0, r0, r3
	str r0, [sp, #0x18]
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #0x20
	blt _0223115A
	mov r0, #0
	mov r2, #0x87
	str r0, [sp]
	lsl r2, r2, #2
	ldr r0, [r4, #4]
	ldr r2, [r4, r2]
	mov r1, #3
	lsl r3, r3, #5
	bl BG_LoadCharTilesData
	mov r0, #0x5f
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD11_0225840C
	mov r0, #0x63
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD11_0225840C
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_02231224: .word 0x06010000

	thumb_func_start MOD11_02231228
MOD11_02231228: ; 0x02231228
	mov r1, #0x87
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_02231230
MOD11_02231230: ; 0x02231230
	mov r1, #0x22
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_02231238
MOD11_02231238: ; 0x02231238
	ldr r1, _02231240 ; =0x00002424
	ldr r0, [r0, r1]
	bx lr
	nop
_02231240: .word 0x00002424

	thumb_func_start MOD11_02231244
MOD11_02231244: ; 0x02231244
	ldr r1, _0223124C ; =0x00002224
	add r0, r0, r1
	bx lr
	nop
_0223124C: .word 0x00002224

	thumb_func_start MOD11_02231250
MOD11_02231250: ; 0x02231250
	ldr r1, _02231258 ; =0x00002304
	add r0, r0, r1
	bx lr
	nop
_02231258: .word 0x00002304

	thumb_func_start MOD11_0223125C
MOD11_0223125C: ; 0x0223125C
	ldr r1, _02231264 ; =0x00002428
	ldr r0, [r0, r1]
	bx lr
	nop
_02231264: .word 0x00002428

	thumb_func_start MOD11_02231268
MOD11_02231268: ; 0x02231268
	ldr r1, _02231270 ; =0x0000241D
	ldrb r0, [r0, r1]
	bx lr
	nop
_02231270: .word 0x0000241D

	thumb_func_start MOD11_02231274
MOD11_02231274: ; 0x02231274
	ldr r2, _0223127C ; =0x0000241D
	strb r1, [r0, r2]
	bx lr
	nop
_0223127C: .word 0x0000241D

	thumb_func_start MOD11_02231280
MOD11_02231280: ; 0x02231280
	ldr r1, _02231288 ; =0x0000242C
	ldr r0, [r0, r1]
	bx lr
	nop
_02231288: .word 0x0000242C

	thumb_func_start MOD11_0223128C
MOD11_0223128C: ; 0x0223128C
	mov r2, #0x86
	lsl r2, r2, #2
	ldr r3, _02231298 ; =FUN_0202A0E8
	ldr r0, [r0, r2]
	bx r3
	nop
_02231298: .word GameStats_Inc

	thumb_func_start MOD11_0223129C
MOD11_0223129C: ; 0x0223129C
	mov r1, #0x86
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	ldr r3, _022312A8 ; =FUN_0202A170
	mov r1, #0x16
	bx r3
	.align 2, 0
_022312A8: .word GameStats_AddSpecial

	thumb_func_start MOD11_022312AC
MOD11_022312AC: ; 0x022312AC
	ldr r2, _022312B4 ; =0x0000243C
	str r1, [r0, r2]
	bx lr
	nop
_022312B4: .word 0x0000243C

	thumb_func_start MOD11_022312B8
MOD11_022312B8: ; 0x022312B8
	mov r2, #0x91
	lsl r2, r2, #6
	strb r1, [r0, r2]
	bx lr

	thumb_func_start MOD11_022312C0
MOD11_022312C0: ; 0x022312C0
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start MOD11_022312C8
MOD11_022312C8: ; 0x022312C8
	mov r2, #0x6f
	lsl r2, r2, #2
	str r1, [r0, r2]
	bx lr

	thumb_func_start MOD11_022312D0
MOD11_022312D0: ; 0x022312D0
	mov r2, #0x73
	lsl r2, r2, #2
	add r2, r0, r2
	lsl r0, r1, #4
	add r0, r2, r0
	bx lr

	thumb_func_start MOD11_022312DC
MOD11_022312DC: ; 0x022312DC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blt _022312EA
	bl GF_AssertFail
_022312EA:
	lsl r0, r5, #4
	ldr r0, [r4, r0]
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_022312F0
MOD11_022312F0: ; 0x022312F0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #4
	blt _02231300
	bl GF_AssertFail
_02231300:
	lsl r0, r4, #4
	add r0, r5, r0
	str r6, [r0, #4]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02231308
MOD11_02231308: ; 0x02231308
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #4
	blt _02231318
	bl GF_AssertFail
_02231318:
	lsl r0, r4, #4
	add r0, r5, r0
	str r6, [r0, #8]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02231320
MOD11_02231320: ; 0x02231320
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r6, r2, #0
	cmp r4, #4
	blt _02231330
	bl GF_AssertFail
_02231330:
	lsl r0, r4, #4
	add r0, r5, r0
	str r6, [r0, #0xc]
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02231338
MOD11_02231338: ; 0x02231338
	ldr r2, _02231340 ; =0x000023F9
	strb r1, [r0, r2]
	bx lr
	nop
_02231340: .word 0x000023F9

	thumb_func_start MOD11_02231344
MOD11_02231344: ; 0x02231344
	ldr r2, _0223134C ; =0x000023F0
	str r1, [r0, r2]
	bx lr
	nop
_0223134C: .word 0x000023F0

	thumb_func_start MOD11_02231350
MOD11_02231350: ; 0x02231350
	ldr r2, _02231358 ; =0x000023F4
	str r1, [r0, r2]
	bx lr
	nop
_02231358: .word 0x000023F4

	thumb_func_start MOD11_0223135C
MOD11_0223135C: ; 0x0223135C
	ldr r2, _02231364 ; =0x000023F0
	ldr r0, [r0, r2]
	strb r1, [r0]
	bx lr
	.align 2, 0
_02231364: .word 0x000023F0

	thumb_func_start MOD11_02231368
MOD11_02231368: ; 0x02231368
	ldr r2, _02231370 ; =0x000023F4
	ldr r0, [r0, r2]
	strb r1, [r0]
	bx lr
	.align 2, 0
_02231370: .word 0x000023F4

	thumb_func_start MOD11_02231374
MOD11_02231374: ; 0x02231374
	ldr r2, _0223137C ; =0x000023FA
	strb r1, [r0, r2]
	bx lr
	nop
_0223137C: .word 0x000023FA

	thumb_func_start MOD11_02231380
MOD11_02231380: ; 0x02231380
	lsl r1, r1, #2
	add r0, r0, r1
	ldr r3, _0223138C ; =MOD11_02253A70
	ldr r0, [r0, #0x34]
	bx r3
	nop
_0223138C: .word MOD11_02253A70

	thumb_func_start MOD11_02231390
MOD11_02231390: ; 0x02231390
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	mov r7, #0
	cmp r0, #0
	ble _022313DC
	add r5, r6, #0
_0223139E:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A70
	add r4, r0, #0
	str r6, [r4, #0xc]
	ldr r0, [r5, #0x34]
	bl MOD11_02253A4C
	str r0, [sp]
	add r0, r6, #0
	bl MOD11_0222FF74
	add r1, r0, #0
	ldr r0, [sp]
	bl MOD11_02257F6C
	add r1, r4, #0
	add r1, #0x25
	strb r0, [r1]
	add r0, r4, #0
	bl MOD11_02256FB0
	add r0, r4, #0
	mov r1, #0
	bl MOD11_022572AC
	ldr r0, [r6, #0x44]
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, r0
	blt _0223139E
_022313DC:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_022313E0
MOD11_022313E0: ; 0x022313E0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	mov r4, #0
	cmp r0, #0
	ble _0223140C
	add r5, r6, #0
	mov r7, #1
_022313F0:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A70
	ldr r1, [r0, #0x28]
	cmp r1, #0
	beq _02231402
	add r1, r7, #0
	bl MOD11_022572AC
_02231402:
	ldr r0, [r6, #0x44]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _022313F0
_0223140C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_02231410
MOD11_02231410: ; 0x02231410
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	mov r4, #0
	cmp r0, #0
	ble _02231436
	add r5, r6, #0
	add r7, r4, #0
_02231420:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A70
	add r1, r7, #0
	bl MOD11_022572AC
	ldr r0, [r6, #0x44]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _02231420
_02231436:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_02231438
MOD11_02231438: ; 0x02231438
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	mov r4, #0
	cmp r0, #0
	ble _0223145A
	add r5, r6, #0
_02231446:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A70
	bl MOD11_02257030
	ldr r0, [r6, #0x44]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _02231446
_0223145A:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_0223145C
MOD11_0223145C: ; 0x0223145C
	ldr r1, _02231464 ; =0x0000241C
	ldrb r0, [r0, r1]
	bx lr
	nop
_02231464: .word 0x0000241C

	thumb_func_start MOD11_02231468
MOD11_02231468: ; 0x02231468
	ldr r2, _02231470 ; =0x0000241C
	strb r1, [r0, r2]
	bx lr
	nop
_02231470: .word 0x0000241C

	thumb_func_start MOD11_02231474
MOD11_02231474: ; 0x02231474
	ldr r1, _02231480 ; =0x000023FB
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1e
	bx lr
	nop
_02231480: .word 0x000023FB

	thumb_func_start MOD11_02231484
MOD11_02231484: ; 0x02231484
	push {r3, r4}
	ldr r3, _0223149C ; =0x000023FB
	lsl r1, r1, #0x1e
	ldrb r4, [r0, r3]
	mov r2, #0x18
	lsr r1, r1, #0x1b
	bic r4, r2
	orr r1, r4
	strb r1, [r0, r3]
	pop {r3, r4}
	bx lr
	nop
_0223149C: .word 0x000023FB

	thumb_func_start MOD11_022314A0
MOD11_022314A0: ; 0x022314A0
	ldr r1, _022314AC ; =0x000023FB
	ldrb r0, [r0, r1]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1d
	bx lr
	nop
_022314AC: .word 0x000023FB

	thumb_func_start MOD11_022314B0
MOD11_022314B0: ; 0x022314B0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #0xf
	blo _022314BE
	bl GF_AssertFail
_022314BE:
	ldr r1, _022314D0 ; =0x000023FB
	mov r0, #0xe0
	ldrb r2, [r5, r1]
	bic r2, r0
	lsl r0, r4, #0x1d
	lsr r0, r0, #0x18
	orr r0, r2
	strb r0, [r5, r1]
	pop {r3, r4, r5, pc}
	.align 2, 0
_022314D0: .word 0x000023FB

	thumb_func_start MOD11_022314D4
MOD11_022314D4: ; 0x022314D4
	ldr r2, _022314DC ; =0x00002438
	str r1, [r0, r2]
	bx lr
	nop
_022314DC: .word 0x00002438

	thumb_func_start MOD11_022314E0
MOD11_022314E0: ; 0x022314E0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	add r7, r1, #0
	mov r4, #0
	cmp r0, #0
	ble _02231502
	add r5, r6, #0
_022314F0:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A4C
	strb r4, [r7, r0]
	ldr r0, [r6, #0x44]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _022314F0
_02231502:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_02231504
MOD11_02231504: ; 0x02231504
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	mov r1, #0
	mov r0, #0xff
_0223150E:
	strb r0, [r6, r1]
	add r1, r1, #1
	cmp r1, #4
	blt _0223150E
	ldr r0, [r7, #0x44]
	mov r5, #0
	cmp r0, #0
	ble _02231532
	add r4, r7, #0
_02231520:
	ldr r0, [r4, #0x34]
	bl MOD11_02253A4C
	strb r0, [r6, r5]
	ldr r0, [r7, #0x44]
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, r0
	blt _02231520
_02231532:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_02231534
MOD11_02231534: ; 0x02231534
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r0, #0
	add r6, r1, #0
	add r5, r0, #0
_0223153E:
	add r0, r0, #1
	stmia r1!, {r5}
	cmp r0, #4
	blt _0223153E
	ldr r0, [r7, #0x44]
	cmp r0, #0
	ble _02231560
	add r4, r7, #0
_0223154E:
	ldr r0, [r4, #0x34]
	bl MOD11_02253A64
	stmia r6!, {r0}
	ldr r0, [r7, #0x44]
	add r5, r5, #1
	add r4, r4, #4
	cmp r5, r0
	blt _0223154E
_02231560:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_02231564
MOD11_02231564: ; 0x02231564
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x44]
	add r7, r1, #0
	mov r4, #0
	cmp r0, #0
	ble _0223158A
	add r5, r6, #0
_02231574:
	ldr r0, [r5, #0x34]
	bl MOD11_02253A70
	add r1, r7, #0
	bl MOD11_02257264
	ldr r0, [r6, #0x44]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _02231574
_0223158A:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD11_0223158C
MOD11_0223158C: ; 0x0223158C
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	bl PlayerProfile_CountBadges
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	add r0, r5, #0
	bl Party_GetMaxLevel
	ldr r1, _022315BC ; =MOD11_0225DC1C
	lsl r0, r0, #2
	ldrb r1, [r1, r4]
	add r4, r1, #0
	mul r4, r0
	add r0, r6, #0
	bl PlayerProfile_GetMoney
	cmp r4, r0
	bls _022315B8
	add r4, r0, #0
_022315B8:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_022315BC: .word MOD11_0225DC1C

	thumb_func_start MOD11_022315C0
MOD11_022315C0: ; 0x022315C0
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	lsl r0, r6, #2
	add r0, r5, r0
	ldr r0, [r0, #0x34]
	bl MOD11_02253A4C
	add r4, r0, #0
	ldr r1, [r5, #0x30]
	add r0, r5, #0
	mov r2, #2
	add r3, r6, #0
	bl MOD11_0224C474
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl MOD11_02230014
	add r6, r0, #0
	ldr r0, [r5, #0x2c]
	mov r1, #0x84
	tst r1, r0
	bne _02231606
	mov r1, #1
	tst r1, r4
	bne _022315FE
	sub r0, #0x4a
	cmp r0, #1
	bhi _02231606
_022315FE:
	ldr r0, [r5, #0x60]
	add r1, r6, #0
	bl Pokedex_SetMonSeenFlag
_02231606:
	mov r0, #1
	tst r0, r4
	bne _02231626
	add r0, r6, #0
	mov r1, #0xad
	mov r2, #0
	bl GetMonData
	mov r1, #0x67
	lsl r1, r1, #2
	cmp r0, r1
	bne _02231626
	ldr r0, [r5, #0x60]
	add r1, r6, #0
	bl Pokedex_SetMonCaughtFlag
_02231626:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02231628
MOD11_02231628: ; 0x02231628
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, #0x34]
	bl MOD11_02253A4C
	ldr r2, [r5, #0x2c]
	mov r1, #0x84
	tst r1, r2
	bne _02231664
	mov r1, #1
	tst r0, r1
	beq _02231664
	ldr r1, [r5, #0x30]
	add r0, r5, #0
	mov r2, #2
	add r3, r4, #0
	bl MOD11_0224C474
	add r2, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02230014
	add r1, r0, #0
	ldr r0, [r5, #0x60]
	bl Pokedex_SetMonCaughtFlag
_02231664:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_02231668
MOD11_02231668: ; 0x02231668
	ldr r3, _02231674 ; =Pokedex_CheckMonCaughtFlag
	lsl r1, r1, #0x10
	ldr r0, [r0, #0x60]
	lsr r1, r1, #0x10
	bx r3
	nop
_02231674: .word Pokedex_CheckMonCaughtFlag

	thumb_func_start MOD11_02231678
MOD11_02231678: ; 0x02231678
	ldr r0, _02231680 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	bx lr
	.align 2, 0
_02231680: .word 0x04000050

	thumb_func_start MOD11_02231684
MOD11_02231684: ; 0x02231684
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	str r2, [sp, #0xc]
	add r7, r3, #0
	bl MOD11_0222FF6C
	add r6, r0, #0
	ldr r1, [r5, #0x2c]
	mov r0, #0x80
	tst r0, r1
	beq _0223174C
	ldr r0, _02231780 ; =0x00002710
	cmp r4, r0
	bne _022316F6
	cmp r7, #0x64
	bne _022316BC
	ldr r0, [sp, #0xc]
	mov r1, #0x34
	add r5, #0xd0
	mul r1, r0
	add r0, r5, r1
	mov r1, #5
	bl MailMsg_GetExpandedString
	b _022316CC
_022316BC:
	ldr r0, [sp, #0xc]
	mov r1, #0x34
	add r5, #0xd8
	mul r1, r0
	add r0, r5, r1
	mov r1, #5
	bl MailMsg_GetExpandedString
_022316CC:
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	ldr r0, [sp, #0x28]
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _02231784 ; =MOD11_0223220C
	mov r1, #1
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	bl AddTextPrinterParameterized
	add r5, r0, #0
	add r0, r4, #0
	bl String_Delete
	b _02231778
_022316F6:
	cmp r7, #0x64
	bne _02231702
	lsl r0, r4, #1
	add r0, r4, r0
	add r4, r0, #1
	b _02231708
_02231702:
	lsl r0, r4, #1
	add r0, r4, r0
	add r4, r0, #2
_02231708:
	ldr r2, _02231788 ; =0x0000022B
	mov r0, #0
	mov r1, #0x1a
	mov r3, #5
	bl NewMsgDataFromNarc
	add r1, r4, #0
	add r7, r0, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	ldr r0, [sp, #0x28]
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _02231784 ; =MOD11_0223220C
	mov r1, #1
	str r0, [sp, #8]
	add r0, r6, #0
	add r2, r4, #0
	bl AddTextPrinterParameterized
	add r5, r0, #0
	add r0, r4, #0
	bl String_Delete
	add r0, r7, #0
	bl DestroyMsgData
	b _02231778
_0223174C:
	ldr r2, [r5, #0x18]
	add r0, r4, #0
	add r1, r7, #0
	mov r3, #5
	bl GetTrainerMessageByIdPair
	add r0, r6, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	ldr r0, [sp, #0x28]
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _02231784 ; =MOD11_0223220C
	mov r1, #1
	str r0, [sp, #8]
	ldr r2, [r5, #0x18]
	add r0, r6, #0
	bl AddTextPrinterParameterized
	add r5, r0, #0
_02231778:
	lsl r0, r5, #0x18
	lsr r0, r0, #0x18
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02231780: .word 0x00002710
_02231784: .word MOD11_0223220C
_02231788: .word 0x0000022B

	thumb_func_start MOD11_0223178C
MOD11_0223178C: ; 0x0223178C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r1, [sp, #0xc]
	add r5, r0, #0
	add r4, r2, #0
	mov r1, #0
	add r6, r3, #0
	bl MOD11_0222FF6C
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02231850
	add r0, r5, #0
	add r1, r4, #0
	bl MOD11_02231A4C
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	add r2, r4, #0
	bl MOD11_022321EC
	add r0, r7, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	ldr r0, _022317DC ; =MOD11_0223220C
	str r6, [sp, #4]
	str r0, [sp, #8]
	ldr r2, [r5, #0x18]
	add r0, r7, #0
	mov r1, #1
	bl AddTextPrinterParameterized
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022317DC: .word MOD11_0223220C

	thumb_func_start MOD11_022317E0
MOD11_022317E0: ; 0x022317E0
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r3, #0
	add r4, r1, #0
	add r5, r0, #0
	add r1, r7, #0
	add r6, r2, #0
	bl MOD11_02231850
	add r0, r5, #0
	add r1, r7, #0
	bl MOD11_02231A4C
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD11_022321EC
	ldr r1, [sp, #0x28]
	mov r0, #1
	tst r0, r1
	beq _02231814
	add r0, r4, #0
	mov r1, #0xff
	bl FillWindowPixelBuffer
_02231814:
	ldr r1, [sp, #0x28]
	mov r0, #2
	tst r0, r1
	beq _0223182C
	mov r0, #0
	ldr r1, [r5, #0x18]
	add r2, r0, #0
	bl FUN_02002E14
	ldr r1, [sp, #0x2c]
	sub r3, r1, r0
	b _0223182E
_0223182C:
	mov r3, #0
_0223182E:
	ldr r0, [sp, #0x24]
	mov r1, #0
	str r0, [sp]
	ldr r0, [sp, #0x30]
	str r0, [sp, #4]
	ldr r0, _0223184C ; =MOD11_0223220C
	str r0, [sp, #8]
	add r0, r4, #0
	ldr r4, [sp, #0x20]
	ldr r2, [r5, #0x18]
	add r3, r4, r3
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223184C: .word MOD11_0223220C

	thumb_func_start MOD11_02231850
MOD11_02231850: ; 0x02231850
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	bl MOD11_0222FF74
	add r5, r0, #0
	ldrb r0, [r4, #1]
	mov r1, #0x80
	tst r1, r0
	bne _02231876
	mov r1, #0x40
	tst r1, r0
	beq _02231880
	ldr r1, [r4, #0x20]
	add r0, r6, #0
	bl MOD11_02230270
	cmp r0, #0
	bne _02231878
_02231876:
	b _02231A4A
_02231878:
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02231880:
	mov r1, #0x3f
	and r0, r1
	cmp r0, #0x3c
	bls _0223188A
	b _02231A46
_0223188A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02231896: ; jump table
	.short _02231A4A - _02231896 - 2 ; case 0
	.short _02231910 - _02231896 - 2 ; case 1
	.short _02231928 - _02231896 - 2 ; case 2
	.short _02231A4A - _02231896 - 2 ; case 3
	.short _02231A4A - _02231896 - 2 ; case 4
	.short _02231A4A - _02231896 - 2 ; case 5
	.short _02231A4A - _02231896 - 2 ; case 6
	.short _02231A4A - _02231896 - 2 ; case 7
	.short _02231A4A - _02231896 - 2 ; case 8
	.short _0223198A - _02231896 - 2 ; case 9
	.short _02231928 - _02231896 - 2 ; case 10
	.short _02231928 - _02231896 - 2 ; case 11
	.short _02231928 - _02231896 - 2 ; case 12
	.short _02231928 - _02231896 - 2 ; case 13
	.short _02231928 - _02231896 - 2 ; case 14
	.short _02231928 - _02231896 - 2 ; case 15
	.short _02231928 - _02231896 - 2 ; case 16
	.short _02231928 - _02231896 - 2 ; case 17
	.short _02231928 - _02231896 - 2 ; case 18
	.short _02231928 - _02231896 - 2 ; case 19
	.short _0223194E - _02231896 - 2 ; case 20
	.short _02231966 - _02231896 - 2 ; case 21
	.short _02231A4A - _02231896 - 2 ; case 22
	.short _02231966 - _02231896 - 2 ; case 23
	.short _02231A4A - _02231896 - 2 ; case 24
	.short _02231A4A - _02231896 - 2 ; case 25
	.short _02231A4A - _02231896 - 2 ; case 26
	.short _02231A4A - _02231896 - 2 ; case 27
	.short _02231A4A - _02231896 - 2 ; case 28
	.short _02231A4A - _02231896 - 2 ; case 29
	.short _02231A4A - _02231896 - 2 ; case 30
	.short _0223198A - _02231896 - 2 ; case 31
	.short _0223198A - _02231896 - 2 ; case 32
	.short _0223198A - _02231896 - 2 ; case 33
	.short _02231928 - _02231896 - 2 ; case 34
	.short _02231928 - _02231896 - 2 ; case 35
	.short _022319E8 - _02231896 - 2 ; case 36
	.short _02231928 - _02231896 - 2 ; case 37
	.short _02231928 - _02231896 - 2 ; case 38
	.short _02231928 - _02231896 - 2 ; case 39
	.short _02231928 - _02231896 - 2 ; case 40
	.short _02231928 - _02231896 - 2 ; case 41
	.short _02231928 - _02231896 - 2 ; case 42
	.short _022319E8 - _02231896 - 2 ; case 43
	.short _02231928 - _02231896 - 2 ; case 44
	.short _02231928 - _02231896 - 2 ; case 45
	.short _02231928 - _02231896 - 2 ; case 46
	.short _02231928 - _02231896 - 2 ; case 47
	.short _02231966 - _02231896 - 2 ; case 48
	.short _02231A4A - _02231896 - 2 ; case 49
	.short _02231A4A - _02231896 - 2 ; case 50
	.short _02231A4A - _02231896 - 2 ; case 51
	.short _022319E8 - _02231896 - 2 ; case 52
	.short _022319E8 - _02231896 - 2 ; case 53
	.short _022319E8 - _02231896 - 2 ; case 54
	.short _022319E8 - _02231896 - 2 ; case 55
	.short _02231A4A - _02231896 - 2 ; case 56
	.short _02231A4A - _02231896 - 2 ; case 57
	.short _02231A4A - _02231896 - 2 ; case 58
	.short _02231A4A - _02231896 - 2 ; case 59
	.short _02231A4A - _02231896 - 2 ; case 60
_02231910:
	ldr r1, [r4, #4]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231944
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02231928:
	ldr r1, [r4, #4]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231944
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	mov r0, #1
	tst r0, r5
	bne _02231946
_02231944:
	b _02231A4A
_02231946:
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_0223194E:
	ldr r1, [r4, #8]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02231966:
	ldr r1, [r4, #8]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	mov r0, #1
	tst r0, r5
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_0223198A:
	ldr r1, [r4, #4]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _022319C4
	ldrh r0, [r4, #2]
	add r0, r0, #3
	strh r0, [r4, #2]
	mov r0, #1
	tst r0, r5
	beq _022319AC
	ldrh r0, [r4, #2]
	add r0, r0, #2
	strh r0, [r4, #2]
_022319AC:
	ldr r1, [r4, #8]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_022319C4:
	ldr r1, [r4, #8]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	mov r0, #1
	tst r0, r5
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_022319E8:
	ldr r1, [r4, #4]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A22
	ldrh r0, [r4, #2]
	add r0, r0, #3
	strh r0, [r4, #2]
	mov r0, #1
	tst r0, r5
	beq _02231A0A
	ldrh r0, [r4, #2]
	add r0, r0, #2
	strh r0, [r4, #2]
_02231A0A:
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02231A22:
	ldr r1, [r4, #0xc]
	add r0, r6, #0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl MOD11_02230270
	cmp r0, #0
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	mov r0, #1
	tst r0, r5
	beq _02231A4A
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	pop {r4, r5, r6, pc}
_02231A46:
	bl GF_AssertFail
_02231A4A:
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_02231A4C
MOD11_02231A4C: ; 0x02231A4C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r2, [r4, #1]
	mov r1, #0x3f
	add r5, r0, #0
	and r1, r2
	cmp r1, #0x3c
	bls _02231A5E
	b _022320C2
_02231A5E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02231A6A: ; jump table
	.short _022320C6 - _02231A6A - 2 ; case 0
	.short _022320C6 - _02231A6A - 2 ; case 1
	.short _02231AE4 - _02231A6A - 2 ; case 2
	.short _02231AEE - _02231A6A - 2 ; case 3
	.short _02231AF8 - _02231A6A - 2 ; case 4
	.short _02231B02 - _02231A6A - 2 ; case 5
	.short _02231B0C - _02231A6A - 2 ; case 6
	.short _02231B16 - _02231A6A - 2 ; case 7
	.short _02231B22 - _02231A6A - 2 ; case 8
	.short _02231B2C - _02231A6A - 2 ; case 9
	.short _02231B40 - _02231A6A - 2 ; case 10
	.short _02231B54 - _02231A6A - 2 ; case 11
	.short _02231B68 - _02231A6A - 2 ; case 12
	.short _02231B7C - _02231A6A - 2 ; case 13
	.short _02231B90 - _02231A6A - 2 ; case 14
	.short _02231BA4 - _02231A6A - 2 ; case 15
	.short _02231BB8 - _02231A6A - 2 ; case 16
	.short _02231BCC - _02231A6A - 2 ; case 17
	.short _02231BE0 - _02231A6A - 2 ; case 18
	.short _02231BF4 - _02231A6A - 2 ; case 19
	.short _02231AEE - _02231A6A - 2 ; case 20
	.short _02231C08 - _02231A6A - 2 ; case 21
	.short _02231C1C - _02231A6A - 2 ; case 22
	.short _02231C30 - _02231A6A - 2 ; case 23
	.short _02231C44 - _02231A6A - 2 ; case 24
	.short _02231C58 - _02231A6A - 2 ; case 25
	.short _02231C6C - _02231A6A - 2 ; case 26
	.short _02231C80 - _02231A6A - 2 ; case 27
	.short _02231C94 - _02231A6A - 2 ; case 28
	.short _02231CA8 - _02231A6A - 2 ; case 29
	.short _02231CBC - _02231A6A - 2 ; case 30
	.short _02231CD0 - _02231A6A - 2 ; case 31
	.short _02231CEE - _02231A6A - 2 ; case 32
	.short _02231D0C - _02231A6A - 2 ; case 33
	.short _02231D2A - _02231A6A - 2 ; case 34
	.short _02231D48 - _02231A6A - 2 ; case 35
	.short _02231D66 - _02231A6A - 2 ; case 36
	.short _02231D84 - _02231A6A - 2 ; case 37
	.short _02231DA2 - _02231A6A - 2 ; case 38
	.short _02231DC0 - _02231A6A - 2 ; case 39
	.short _02231DDE - _02231A6A - 2 ; case 40
	.short _02231DFC - _02231A6A - 2 ; case 41
	.short _02231E1A - _02231A6A - 2 ; case 42
	.short _02231E38 - _02231A6A - 2 ; case 43
	.short _02231E56 - _02231A6A - 2 ; case 44
	.short _02231E74 - _02231A6A - 2 ; case 45
	.short _02231E92 - _02231A6A - 2 ; case 46
	.short _02231EB0 - _02231A6A - 2 ; case 47
	.short _02231ECE - _02231A6A - 2 ; case 48
	.short _02231EEC - _02231A6A - 2 ; case 49
	.short _02231F0A - _02231A6A - 2 ; case 50
	.short _02231F28 - _02231A6A - 2 ; case 51
	.short _02231F46 - _02231A6A - 2 ; case 52
	.short _02231F6E - _02231A6A - 2 ; case 53
	.short _02231F96 - _02231A6A - 2 ; case 54
	.short _02231FBE - _02231A6A - 2 ; case 55
	.short _02231FE6 - _02231A6A - 2 ; case 56
	.short _0223200E - _02231A6A - 2 ; case 57
	.short _02232036 - _02231A6A - 2 ; case 58
	.short _0223205E - _02231A6A - 2 ; case 59
	.short _02232086 - _02231A6A - 2 ; case 60
_02231AE4:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231AEE:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231AF8:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_02232160
	pop {r3, r4, r5, pc}
_02231B02:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231B0C:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_02232104
	pop {r3, r4, r5, pc}
_02231B16:
	ldr r2, [r4, #4]
	ldr r3, [r4, #0x1c]
	mov r1, #0
	bl MOD11_0223211C
	pop {r3, r4, r5, pc}
_02231B22:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	pop {r3, r4, r5, pc}
_02231B2C:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231B40:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231B54:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	pop {r3, r4, r5, pc}
_02231B68:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232160
	pop {r3, r4, r5, pc}
_02231B7C:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232148
	pop {r3, r4, r5, pc}
_02231B90:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232178
	pop {r3, r4, r5, pc}
_02231BA4:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231BB8:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_0223219C
	pop {r3, r4, r5, pc}
_02231BCC:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232104
	pop {r3, r4, r5, pc}
_02231BE0:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	pop {r3, r4, r5, pc}
_02231BF4:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321DC
	pop {r3, r4, r5, pc}
_02231C08:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320EC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231C1C:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320EC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231C30:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_02232154
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231C44:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320F8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231C58:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_02232104
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232104
	pop {r3, r4, r5, pc}
_02231C6C:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	pop {r3, r4, r5, pc}
_02231C80:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231C94:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231CA8:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232104
	pop {r3, r4, r5, pc}
_02231CBC:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	pop {r3, r4, r5, pc}
_02231CD0:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231CEE:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_02232154
	pop {r3, r4, r5, pc}
_02231D0C:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231D2A:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320EC
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231D48:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320EC
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_02232104
	pop {r3, r4, r5, pc}
_02231D66:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231D84:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231DA2:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231DC0:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_02232160
	pop {r3, r4, r5, pc}
_02231DDE:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_02232148
	pop {r3, r4, r5, pc}
_02231DFC:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_0223216C
	pop {r3, r4, r5, pc}
_02231E1A:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_02232104
	pop {r3, r4, r5, pc}
_02231E38:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231E56:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231E74:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_02232160
	pop {r3, r4, r5, pc}
_02231E92:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_0223216C
	pop {r3, r4, r5, pc}
_02231EB0:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321DC
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022321DC
	pop {r3, r4, r5, pc}
_02231ECE:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320F8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022321A0
	pop {r3, r4, r5, pc}
_02231EEC:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231F0A:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02231F28:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231F46:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022320EC
	pop {r3, r4, r5, pc}
_02231F6E:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_02232154
	pop {r3, r4, r5, pc}
_02231F96:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_02232154
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_02232160
	pop {r3, r4, r5, pc}
_02231FBE:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022320C8
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320F8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022320F8
	pop {r3, r4, r5, pc}
_02231FE6:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321C4
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022320C8
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022321C4
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_0223200E:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_02232036:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022321C4
	pop {r3, r4, r5, pc}
_0223205E:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022321AC
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022321C4
	pop {r3, r4, r5, pc}
_02232086:
	ldr r2, [r4, #4]
	mov r1, #0
	bl MOD11_022321AC
	ldr r2, [r4, #8]
	add r0, r5, #0
	mov r1, #1
	bl MOD11_022321C4
	ldr r2, [r4, #0xc]
	add r0, r5, #0
	mov r1, #2
	bl MOD11_022320C8
	ldr r2, [r4, #0x10]
	add r0, r5, #0
	mov r1, #3
	bl MOD11_022321AC
	ldr r2, [r4, #0x14]
	add r0, r5, #0
	mov r1, #4
	bl MOD11_022321C4
	ldr r2, [r4, #0x18]
	add r0, r5, #0
	mov r1, #5
	bl MOD11_022320C8
	pop {r3, r4, r5, pc}
_022320C2:
	bl GF_AssertFail
_022320C6:
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_022320C8
MOD11_022320C8: ; 0x022320C8
	push {r3, r4, r5, lr}
	mov r3, #0xff
	lsl r3, r3, #8
	add r4, r1, #0
	lsl r1, r2, #0x18
	and r2, r3
	add r5, r0, #0
	lsr r1, r1, #0x18
	asr r2, r2, #8
	bl MOD11_02230014
	add r2, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl BufferBoxMonNickname
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_022320EC
MOD11_022320EC: ; 0x022320EC
	ldr r3, _022320F4 ; =BufferMoveName
	ldr r0, [r0, #0x14]
	bx r3
	nop
_022320F4: .word BufferMoveName

	thumb_func_start MOD11_022320F8
MOD11_022320F8: ; 0x022320F8
	ldr r3, _02232100 ; =BufferItemName
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02232100: .word BufferItemName

	thumb_func_start MOD11_02232104
MOD11_02232104: ; 0x02232104
	push {r3, lr}
	sub sp, #8
	mov r3, #0
	str r3, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r0, [r0, #0x14]
	mov r3, #5
	bl BufferIntegerAsString
	add sp, #8
	pop {r3, pc}

	thumb_func_start MOD11_0223211C
MOD11_0223211C: ; 0x0223211C
	push {r4, lr}
	sub sp, #8
	cmp r3, #0
	beq _02232134
	mov r4, #1
	str r4, [sp]
	str r4, [sp, #4]
	ldr r0, [r0, #0x14]
	bl BufferIntegerAsString
	add sp, #8
	pop {r4, pc}
_02232134:
	mov r3, #1
	str r3, [sp]
	str r3, [sp, #4]
	ldr r0, [r0, #0x14]
	mov r3, #5
	bl BufferIntegerAsString
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_02232148
MOD11_02232148: ; 0x02232148
	ldr r3, _02232150 ; =BufferTypeName
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02232150: .word BufferTypeName

	thumb_func_start MOD11_02232154
MOD11_02232154: ; 0x02232154
	ldr r3, _0223215C ; =BufferAbilityName
	ldr r0, [r0, #0x14]
	bx r3
	nop
_0223215C: .word BufferAbilityName

	thumb_func_start MOD11_02232160
MOD11_02232160: ; 0x02232160
	ldr r3, _02232168 ; =BufferStatName
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02232168: .word BufferStatName

	thumb_func_start MOD11_0223216C
MOD11_0223216C: ; 0x0223216C
	ldr r3, _02232174 ; =BufferStatusName
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02232174: .word BufferStatusName

	thumb_func_start MOD11_02232178
MOD11_02232178: ; 0x02232178
	push {r3, r4, r5, lr}
	mov r3, #0xff
	lsl r3, r3, #8
	add r4, r1, #0
	lsl r1, r2, #0x18
	and r2, r3
	add r5, r0, #0
	lsr r1, r1, #0x18
	asr r2, r2, #8
	bl MOD11_02230014
	add r2, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl BufferBoxMonSpeciesName
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_0223219C
MOD11_0223219C: ; 0x0223219C
	bx lr
	.align 2, 0

	thumb_func_start MOD11_022321A0
MOD11_022321A0: ; 0x022321A0
	ldr r3, _022321A8 ; =BufferFlavorDislikeText
	ldr r0, [r0, #0x14]
	bx r3
	nop
_022321A8: .word BufferFlavorDislikeText

	thumb_func_start MOD11_022321AC
MOD11_022321AC: ; 0x022321AC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r1, r2, #0
	bl MOD11_02230188
	add r2, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl BufferTrainerClassNameFromDataStruct
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_022321C4
MOD11_022321C4: ; 0x022321C4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r1, r2, #0
	bl MOD11_02230188
	add r2, r0, #0
	ldr r0, [r5, #0x14]
	add r1, r4, #0
	bl BufferTrainerNameFromDataStruct
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_022321DC
MOD11_022321DC: ; 0x022321DC
	push {r4, lr}
	add r4, r0, #0
	add r3, r2, #0
	ldr r0, [r4, #0x14]
	ldr r2, [r4, #0x64]
	bl BufferBoxName
	pop {r4, pc}

	thumb_func_start MOD11_022321EC
MOD11_022321EC: ; 0x022321EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #0
	ldrh r1, [r2, #2]
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r4, #0
	bl String_Delete
	pop {r3, r4, r5, pc}

	thumb_func_start MOD11_0223220C
MOD11_0223220C: ; 0x0223220C
	push {r4, lr}
	mov r4, #0
	cmp r1, #5
	bhi _02232252
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02232220: ; jump table
	.short _02232252 - _02232220 - 2 ; case 0
	.short _0223222C - _02232220 - 2 ; case 1
	.short _02232234 - _02232220 - 2 ; case 2
	.short _0223223C - _02232220 - 2 ; case 3
	.short _02232244 - _02232220 - 2 ; case 4
	.short _0223224C - _02232220 - 2 ; case 5
_0223222C:
	bl FUN_02005514
	add r4, r0, #0
	b _02232252
_02232234:
	bl FUN_02005CBC
	add r4, r0, #0
	b _02232252
_0223223C:
	ldr r0, _02232258 ; =0x00000484
	bl PlaySound
	b _02232252
_02232244:
	ldr r0, _0223225C ; =0x000005E6
	bl PlaySE
	b _02232252
_0223224C:
	ldr r0, _02232260 ; =0x00000483
	bl PlaySound
_02232252:
	add r0, r4, #0
	pop {r4, pc}
	nop
_02232258: .word 0x00000484
_0223225C: .word 0x000005E6
_02232260: .word 0x00000483

	.section .rodata

	.global MOD11_0225DC1C
MOD11_0225DC1C: ; 0x0225DC1C
	.byte 0x02, 0x04, 0x06, 0x09, 0x0C, 0x10, 0x14, 0x19, 0x1E, 0x00, 0x00, 0x00
