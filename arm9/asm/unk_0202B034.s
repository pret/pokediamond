	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0202B034
FUN_0202B034: ; 0x0202B034
	ldr r0, _0202B038 ; =0x00002AB0
	bx lr
	.balign 4
_0202B038: .word 0x00002AB0

	thumb_func_start FUN_0202B03C
FUN_0202B03C: ; 0x0202B03C
	ldr r3, _0202B048 ; =MIi_CpuClear32
	add r1, r0, #0x0
	mov r0, #0x0
	ldr r2, _0202B04C ; =0x00002AB0
	bx r3
	nop
_0202B048: .word MIi_CpuClear32
_0202B04C: .word 0x00002AB0

	thumb_func_start FUN_0202B050
FUN_0202B050: ; 0x0202B050
	push {r3-r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	cmp r0, #0x0
	bne _0202B062
	bl ErrorHandling
_0202B062:
	ldr r1, _0202B1E0 ; =0x00002AA8
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	cmp r0, #0x1e
	blo _0202B070
	bl ErrorHandling
_0202B070:
	ldr r1, _0202B1E4 ; =0x00002AAC
	ldr r0, [sp, #0x0]
	ldr r2, [r0, r1]
	ldr r0, _0202B1E8 ; =0x0000270F
	cmp r2, r0
	blo _0202B07E
	b _0202B1DC
_0202B07E:
	ldr r0, [sp, #0x0]
	sub r1, r1, #0x4
	ldr r1, [r0, r1]
	mov r0, #0x5b
	lsl r0, r0, #0x2
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x0]
	add r0, r0, r2
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4]
	bl FUN_0206B9AC
	str r0, [sp, #0x10]
	mov r0, #0xb
	mov r1, #0x0
	bl FUN_020219F4
	mov r2, #0x5a
	add r6, r0, #0x0
	ldr r1, [sp, #0x14]
	mov r0, #0x0
	lsl r2, r2, #0x2
	bl MIi_CpuClear16
	ldr r0, [sp, #0x10]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0202B18E
	ldr r5, [sp, #0x14]
_0202B0BA:
	ldr r0, [sp, #0x4]
	add r1, r7, #0x0
	bl FUN_0206B9B0
	add r4, r0, #0x0
	bl FUN_020669D4
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonDataEncrypted
	cmp r0, #0x0
	bne _0202B17E
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonDataEncrypted
	strh r0, [r5, #0x0]
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonDataEncrypted
	strb r0, [r5, #0x2]
	add r0, r4, #0x0
	mov r1, #0x70
	mov r2, #0x0
	bl GetMonDataEncrypted
	mov r1, #0x0
	strb r0, [r5, #0x3]
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl GetMonDataEncrypted
	str r0, [r5, #0x4]
	add r0, r4, #0x0
	mov r1, #0x7
	mov r2, #0x0
	bl GetMonDataEncrypted
	str r0, [r5, #0x8]
	add r0, r4, #0x0
	mov r1, #0x36
	mov r2, #0x0
	bl GetMonDataEncrypted
	strh r0, [r5, #0x32]
	add r0, r4, #0x0
	mov r1, #0x37
	mov r2, #0x0
	bl GetMonDataEncrypted
	strh r0, [r5, #0x34]
	add r0, r4, #0x0
	mov r1, #0x38
	mov r2, #0x0
	bl GetMonDataEncrypted
	strh r0, [r5, #0x36]
	add r0, r4, #0x0
	mov r1, #0x39
	mov r2, #0x0
	bl GetMonDataEncrypted
	strh r0, [r5, #0x38]
	cmp r6, #0x0
	beq _0202B176
	add r0, r4, #0x0
	mov r1, #0x76
	add r2, r6, #0x0
	bl GetMonDataEncrypted
	add r1, r5, #0x0
	add r0, r6, #0x0
	add r1, #0xc
	mov r2, #0xb
	bl FUN_02021EF0
	add r0, r4, #0x0
	mov r1, #0x90
	add r2, r6, #0x0
	bl GetMonDataEncrypted
	add r1, r5, #0x0
	add r0, r6, #0x0
	add r1, #0x22
	mov r2, #0x8
	bl FUN_02021EF0
	b _0202B17C
_0202B176:
	ldr r0, _0202B1EC ; =0x0000FFFF
	strh r0, [r5, #0xc]
	strh r0, [r5, #0x22]
_0202B17C:
	add r5, #0x3c
_0202B17E:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02066A20
	ldr r0, [sp, #0x10]
	add r7, r7, #0x1
	cmp r7, r0
	blt _0202B0BA
_0202B18E:
	ldr r0, [sp, #0x8]
	mov r1, #0x5a
	ldr r2, [r0, #0x0]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x2
	strh r2, [r0, r1]
	ldr r0, [sp, #0x8]
	add r2, r1, #0x2
	ldr r3, [r0, #0x4]
	ldr r0, [sp, #0x14]
	add r1, r1, #0x3
	strb r3, [r0, r2]
	ldr r0, [sp, #0x8]
	ldr r2, [r0, #0x8]
	ldr r0, [sp, #0x14]
	strb r2, [r0, r1]
	ldr r1, _0202B1E0 ; =0x00002AA8
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	str r2, [r0, r1]
	ldr r0, [r0, r1]
	cmp r0, #0x1e
	blo _0202B1C6
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	str r2, [r0, r1]
_0202B1C6:
	ldr r1, _0202B1E4 ; =0x00002AAC
	ldr r0, [sp, #0x0]
	ldr r0, [r0, r1]
	add r2, r0, #0x1
	ldr r0, [sp, #0x0]
	cmp r6, #0x0
	str r2, [r0, r1]
	beq _0202B1DC
	add r0, r6, #0x0
	bl FUN_02021A20
_0202B1DC:
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_0202B1E0: .word 0x00002AA8
_0202B1E4: .word 0x00002AAC
_0202B1E8: .word 0x0000270F
_0202B1EC: .word 0x0000FFFF

	thumb_func_start FUN_0202B1F0
FUN_0202B1F0: ; 0x0202B1F0
	push {r4, lr}
	add r4, r0, #0x0
	bne _0202B1FA
	bl ErrorHandling
_0202B1FA:
	ldr r0, _0202B214 ; =0x00002AA8
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	blo _0202B206
	bl ErrorHandling
_0202B206:
	ldr r0, _0202B218 ; =0x00002AAC
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	blo _0202B210
	mov r0, #0x1e
_0202B210:
	pop {r4, pc}
	nop
_0202B214: .word 0x00002AA8
_0202B218: .word 0x00002AAC

	thumb_func_start FUN_0202B21C
FUN_0202B21C: ; 0x0202B21C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0202B22A
	bl ErrorHandling
_0202B22A:
	ldr r0, _0202B248 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B236
	bl ErrorHandling
_0202B236:
	cmp r4, #0x1e
	blt _0202B23E
	bl ErrorHandling
_0202B23E:
	ldr r0, _0202B24C ; =0x00002AAC
	ldr r0, [r5, r0]
	sub r0, r0, r4
	pop {r3-r5, pc}
	nop
_0202B248: .word 0x00002AA8
_0202B24C: .word 0x00002AAC

	thumb_func_start FUN_0202B250
FUN_0202B250: ; 0x0202B250
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0202B25E
	bl ErrorHandling
_0202B25E:
	ldr r0, _0202B298 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B26A
	bl ErrorHandling
_0202B26A:
	cmp r4, #0x1e
	blt _0202B272
	bl ErrorHandling
_0202B272:
	ldr r0, _0202B298 ; =0x00002AA8
	ldr r0, [r5, r0]
	sub r0, r0, #0x1
	sub r2, r0, r4
	bpl _0202B27E
	add r2, #0x1e
_0202B27E:
	mov r1, #0x5b
	lsl r1, r1, #0x2
	mul r1, r2
	mov r0, #0x0
	add r2, r5, r1
_0202B288:
	ldrh r1, [r2, #0x0]
	cmp r1, #0x0
	beq _0202B296
	add r0, r0, #0x1
	add r2, #0x3c
	cmp r0, #0x6
	blo _0202B288
_0202B296:
	pop {r3-r5, pc}
	.balign 4
_0202B298: .word 0x00002AA8

	thumb_func_start FUN_0202B29C
FUN_0202B29C: ; 0x0202B29C
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	cmp r5, #0x0
	bne _0202B2AE
	bl ErrorHandling
_0202B2AE:
	ldr r0, _0202B318 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B2BA
	bl ErrorHandling
_0202B2BA:
	cmp r6, #0x1e
	blt _0202B2C2
	bl ErrorHandling
_0202B2C2:
	ldr r0, _0202B318 ; =0x00002AA8
	ldr r0, [r5, r0]
	sub r0, r0, #0x1
	sub r1, r0, r6
	bpl _0202B2CE
	add r1, #0x1e
_0202B2CE:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	mul r0, r1
	add r1, r5, r0
	mov r0, #0x3c
	mul r0, r7
	add r5, r1, r0
	ldrh r0, [r1, r0]
	add r1, r5, #0x0
	add r1, #0xc
	strh r0, [r4, #0x10]
	ldrb r0, [r5, #0x2]
	strb r0, [r4, #0x12]
	ldr r0, [r5, #0x4]
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x8]
	str r0, [r4, #0xc]
	ldrb r0, [r5, #0x3]
	strb r0, [r4, #0x13]
	ldr r0, [r4, #0x0]
	bl FUN_02021E28
	add r1, r5, #0x0
	ldr r0, [r4, #0x4]
	add r1, #0x22
	bl FUN_02021E28
	mov r1, #0x0
_0202B306:
	ldrh r0, [r5, #0x32]
	add r1, r1, #0x1
	add r5, r5, #0x2
	strh r0, [r4, #0x14]
	add r4, r4, #0x2
	cmp r1, #0x4
	blt _0202B306
	pop {r3-r7, pc}
	nop
_0202B318: .word 0x00002AA8

	thumb_func_start FUN_0202B31C
FUN_0202B31C: ; 0x0202B31C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _0202B32C
	bl ErrorHandling
_0202B32C:
	ldr r0, _0202B370 ; =0x00002AA8
	ldr r0, [r5, r0]
	cmp r0, #0x1e
	blo _0202B338
	bl ErrorHandling
_0202B338:
	cmp r6, #0x1e
	blt _0202B340
	bl ErrorHandling
_0202B340:
	ldr r0, _0202B370 ; =0x00002AA8
	ldr r0, [r5, r0]
	sub r0, r0, #0x1
	sub r2, r0, r6
	bpl _0202B34C
	add r2, #0x1e
_0202B34C:
	mov r0, #0x5b
	lsl r0, r0, #0x2
	add r1, r2, #0x0
	mul r1, r0
	add r2, r5, r1
	sub r1, r0, #0x4
	ldrh r1, [r2, r1]
	str r1, [r4, #0x0]
	sub r1, r0, #0x2
	ldrb r1, [r2, r1]
	sub r0, r0, #0x1
	str r1, [r4, #0x4]
	ldrb r0, [r2, r0]
	str r0, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0xc]
	pop {r4-r6, pc}
	nop
_0202B370: .word 0x00002AA8
