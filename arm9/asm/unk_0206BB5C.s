    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0206BB5C
FUN_0206BB5C: ; 0x0206BB5C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02087A6C
	mov r1, #0x0
	add r2, r5, #0x0
	add r4, r0, #0x0
	bl FUN_02087A98
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0206BB74
FUN_0206BB74: ; 0x0206BB74
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02087B0C
	add r0, r4, #0x0
	bl FUN_02087A84
	pop {r4, pc}

	thumb_func_start FUN_0206BB84
FUN_0206BB84: ; 0x0206BB84
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	add r0, r7, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	cmp r4, #0x0
	bne _0206BBA2
	mov r0, #0x1
	pop {r3-r7, pc}
_0206BBA2:
	add r0, r4, #0x0
	mov r1, #0x2
	bl FUN_02023B0C
	add r5, r0, #0x0
	add r0, r7, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	cmp r0, r5
	bls _0206BBBE
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BBBE:
	add r0, r7, #0x0
	mov r1, #0x4c
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0206BBD0
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BBD0:
	add r0, r4, #0x0
	mov r1, #0x4
	bl FUN_02023B0C
	cmp r0, #0x0
	bne _0206BBEA
	add r0, r6, #0x0
	bl GetEggSpecies
	cmp r6, r0
	beq _0206BBEA
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BBEA:
	add r0, r4, #0x0
	mov r1, #0x5
	bl FUN_02023B0C
	add r5, r0, #0x0
	beq _0206BC14
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_02087B58
	cmp r5, #0x0
	ble _0206BC0A
	cmp r0, r5
	bge _0206BC14
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BC0A:
	neg r1, r5
	cmp r0, r1
	ble _0206BC14
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BC14:
	add r0, r4, #0x0
	mov r1, #0x7
	bl FUN_02023B0C
	mov r1, #0xa
	add r5, r0, #0x0
	mul r5, r1
	beq _0206BC42
	ldr r0, [sp, #0x0]
	add r1, r6, #0x0
	bl FUN_02087B78
	cmp r5, #0x0
	ble _0206BC38
	cmp r0, r5
	bge _0206BC42
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BC38:
	neg r1, r5
	cmp r0, r1
	ble _0206BC42
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BC42:
	add r0, r4, #0x0
	mov r1, #0xb
	bl FUN_02023B0C
	cmp r0, #0x0
	bne _0206BC5C
	add r0, r7, #0x0
	bl FUN_0206A998
	cmp r0, #0x0
	beq _0206BC5C
	mov r0, #0x0
	pop {r3-r7, pc}
_0206BC5C:
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start FUN_0206BC60
FUN_0206BC60: ; 0x0206BC60
	push {r3-r7, lr}
	sub sp, #0x30
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x4]
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	cmp r0, #0x0
	bne _0206BC7E
	ldr r0, [sp, #0x14]
	add sp, #0x30
	pop {r3-r7, pc}
_0206BC7E:
	ldr r1, [sp, #0x14]
	add r2, sp, #0x24
	add r3, sp, #0x18
	mov r0, #0x0
_0206BC86:
	ldr r4, [sp, #0xc]
	strh r0, [r2, #0x0]
	strh r0, [r3, #0x0]
	ldrb r4, [r4, r1]
	cmp r4, #0x0
	beq _0206BC98
	ldr r4, [sp, #0x14]
	add r4, r4, #0x1
	str r4, [sp, #0x14]
_0206BC98:
	add r1, r1, #0x1
	add r2, r2, #0x2
	add r3, r3, #0x2
	cmp r1, #0x6
	blt _0206BC86
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	bl FUN_02023B0C
	ldr r1, [sp, #0x14]
	cmp r1, r0
	beq _0206BCB6
	add sp, #0x30
	mov r0, #0x4
	pop {r3-r7, pc}
_0206BCB6:
	mov r5, #0x0
	add r7, sp, #0x24
	add r6, sp, #0x18
_0206BCBC:
	ldr r0, [sp, #0xc]
	ldrb r1, [r0, r5]
	cmp r1, #0x0
	beq _0206BD0A
	ldr r0, [sp, #0x4]
	sub r1, r1, #0x1
	bl GetPartyMonByIndex
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	ldr r2, [sp, #0x8]
	add r1, r4, #0x0
	bl FUN_0206BB84
	cmp r0, #0x0
	bne _0206BCE2
	add sp, #0x30
	mov r0, #0x5
	pop {r3-r7, pc}
_0206BCE2:
	add r0, r4, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	strh r0, [r7, #0x0]
	add r0, r4, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	strh r0, [r6, #0x0]
	add r0, r4, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	ldr r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [sp, #0x10]
_0206BD0A:
	add r5, r5, #0x1
	add r7, r7, #0x2
	add r6, r6, #0x2
	cmp r5, #0x6
	blt _0206BCBC
	ldr r0, [sp, #0x0]
	mov r1, #0x3
	bl FUN_02023B0C
	ldr r1, [sp, #0x10]
	cmp r1, r0
	ble _0206BD2C
	cmp r0, #0x0
	beq _0206BD2C
	add sp, #0x30
	mov r0, #0x1
	pop {r3-r7, pc}
_0206BD2C:
	ldr r0, [sp, #0x0]
	mov r1, #0xa
	bl FUN_02023B0C
	cmp r0, #0x0
	bne _0206BD70
	ldr r0, [sp, #0x14]
	cmp r0, #0x1
	ble _0206BD70
	add r4, sp, #0x24
	mov r0, #0x0
	add r2, r4, #0x0
_0206BD44:
	add r3, r0, #0x1
	cmp r3, #0x6
	bge _0206BD68
	ldrh r6, [r4, #0x0]
	lsl r1, r3, #0x1
	add r5, r2, r1
_0206BD50:
	ldrh r1, [r5, #0x0]
	cmp r6, r1
	bne _0206BD60
	cmp r6, #0x0
	beq _0206BD60
	add sp, #0x30
	mov r0, #0x2
	pop {r3-r7, pc}
_0206BD60:
	add r3, r3, #0x1
	add r5, r5, #0x2
	cmp r3, #0x6
	blt _0206BD50
_0206BD68:
	add r0, r0, #0x1
	add r4, r4, #0x2
	cmp r0, #0x5
	blt _0206BD44
_0206BD70:
	ldr r0, [sp, #0x0]
	mov r1, #0x9
	bl FUN_02023B0C
	cmp r0, #0x0
	bne _0206BDC0
	ldr r0, [sp, #0x14]
	cmp r0, #0x1
	ble _0206BDC0
	add r2, sp, #0x18
	mov r5, #0x0
	add r7, sp, #0x24
	mov r12, r2
_0206BD8A:
	add r6, r5, #0x1
	cmp r6, #0x6
	bge _0206BDB6
	lsl r1, r6, #0x1
	mov r0, r12
	add r3, r0, r1
	ldrh r4, [r2, #0x0]
	ldrh r0, [r7, #0x0]
_0206BD9A:
	ldrh r1, [r3, #0x0]
	cmp r4, r1
	bne _0206BDAE
	cmp r0, #0x0
	beq _0206BDAE
	cmp r4, #0x0
	beq _0206BDAE
	add sp, #0x30
	mov r0, #0x3
	pop {r3-r7, pc}
_0206BDAE:
	add r6, r6, #0x1
	add r3, r3, #0x2
	cmp r6, #0x6
	blt _0206BD9A
_0206BDB6:
	add r5, r5, #0x1
	add r2, r2, #0x2
	add r7, r7, #0x2
	cmp r5, #0x5
	blt _0206BD8A
_0206BDC0:
	mov r0, #0x0
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0206BDC8
FUN_0206BDC8: ; 0x0206BDC8
	push {r4-r7, lr}
	sub sp, #0x1c
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x10]
	lsl r0, r0, #0x1
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x18]
	ldrh r0, [r1, r0]
	add r6, r2, #0x0
	str r3, [sp, #0x14]
	ldr r5, [sp, #0x38]
	ldr r7, [sp, #0x34]
	cmp r0, #0x0
	beq _0206BE12
	ldr r0, [sp, #0x18]
	ldrh r0, [r6, r0]
	cmp r0, #0x0
	bne _0206BE12
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x18]
	ldrh r1, [r1, r0]
	add r0, r3, #0x0
	sub r0, r0, r1
	str r0, [sp, #0x14]
	bpl _0206BE02
	add sp, #0x1c
	mov r0, #0x0
	pop {r4-r7, pc}
_0206BE02:
	sub r7, r7, #0x1
	bne _0206BE0C
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r7, pc}
_0206BE0C:
	ldr r0, [sp, #0x18]
	mov r1, #0x1
	strh r1, [r6, r0]
_0206BE12:
	ldr r0, [sp, #0x30]
	add r4, r0, #0x1
	cmp r4, r5
	bge _0206BE3C
_0206BE1A:
	str r4, [sp, #0x0]
	str r7, [sp, #0x4]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r2, r6, #0x0
	str r5, [sp, #0x8]
	bl FUN_0206BDC8
	cmp r0, #0x0
	beq _0206BE36
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r7, pc}
_0206BE36:
	add r4, r4, #0x1
	cmp r4, r5
	blt _0206BE1A
_0206BE3C:
	ldr r1, [sp, #0x18]
	mov r0, #0x0
	strh r0, [r6, r1]
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0206BE48
FUN_0206BE48: ; 0x0206BE48
	push {r4-r7, lr}
	sub sp, #0x54
	str r0, [sp, #0xc]
	add r0, r1, #0x0
	str r1, [sp, #0x10]
	str r2, [sp, #0x14]
	bl GetPartyCount
	str r0, [sp, #0x20]
	add r6, r0, #0x0
	add r0, sp, #0x30
	mov r1, #0x0
	mov r2, #0xc
	bl MI_CpuFill8
	ldr r0, [sp, #0x20]
	mov r7, #0x0
	cmp r0, #0x0
	ble _0206BEB2
	add r4, sp, #0x48
	add r5, sp, #0x3c
_0206BE72:
	ldr r0, [sp, #0x10]
	add r1, r7, #0x0
	bl GetPartyMonByIndex
	str r0, [sp, #0x24]
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	strh r0, [r4, #0x0]
	ldr r0, [sp, #0x24]
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	strh r0, [r5, #0x0]
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x14]
	bl FUN_0206BB84
	cmp r0, #0x0
	bne _0206BEA6
	mov r0, #0x0
	strh r0, [r4, #0x0]
	sub r6, r6, #0x1
_0206BEA6:
	ldr r0, [sp, #0x20]
	add r7, r7, #0x1
	add r4, r4, #0x2
	add r5, r5, #0x2
	cmp r7, r0
	blt _0206BE72
_0206BEB2:
	ldr r0, [sp, #0xc]
	mov r1, #0xa
	bl FUN_02023B0C
	cmp r0, #0x0
	bne _0206BF32
	ldr r0, [sp, #0x20]
	cmp r0, #0x1
	ble _0206BF32
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	sub r0, r0, #0x1
	str r0, [sp, #0x28]
	cmp r0, #0x0
	ble _0206BF32
	add r0, sp, #0x3c
	add r3, sp, #0x48
	str r0, [sp, #0x1c]
	str r3, [sp, #0x2c]
	mov r12, r0
_0206BEDC:
	ldr r0, [sp, #0x18]
	add r2, r0, #0x1
	ldr r0, [sp, #0x20]
	cmp r2, r0
	bge _0206BF1E
	ldr r1, [sp, #0x2c]
	lsl r0, r2, #0x1
	add r4, r1, r0
	mov r1, r12
	add r5, r1, r0
	ldr r0, [sp, #0x1c]
	ldrh r7, [r0, #0x0]
_0206BEF4:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r1, r0
	bne _0206BF12
	cmp r1, #0x0
	beq _0206BF12
	ldrh r0, [r5, #0x0]
	cmp r7, r0
	bls _0206BF0C
	mov r0, #0x0
	strh r0, [r3, #0x0]
	b _0206BF10
_0206BF0C:
	mov r0, #0x0
	strh r0, [r4, #0x0]
_0206BF10:
	sub r6, r6, #0x1
_0206BF12:
	ldr r0, [sp, #0x20]
	add r2, r2, #0x1
	add r4, r4, #0x2
	add r5, r5, #0x2
	cmp r2, r0
	blt _0206BEF4
_0206BF1E:
	ldr r0, [sp, #0x1c]
	add r3, r3, #0x2
	add r0, r0, #0x2
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r1, r0, #0x1
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x18]
	cmp r1, r0
	blt _0206BEDC
_0206BF32:
	ldr r0, [sp, #0xc]
	mov r1, #0x1
	bl FUN_02023B0C
	add r7, r0, #0x0
	cmp r6, r7
	bge _0206BF46
	add sp, #0x54
	mov r0, #0x4
	pop {r4-r7, pc}
_0206BF46:
	ldr r0, [sp, #0xc]
	mov r1, #0x3
	bl FUN_02023B0C
	add r5, r0, #0x0
	bne _0206BF58
	add sp, #0x54
	mov r0, #0x0
	pop {r4-r7, pc}
_0206BF58:
	ldr r0, [sp, #0x20]
	mov r4, #0x0
	cmp r0, #0x0
	ble _0206BF88
	add r6, sp, #0x48
_0206BF62:
	str r4, [sp, #0x0]
	ldr r0, [sp, #0x20]
	str r7, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r1, sp, #0x3c
	add r2, sp, #0x30
	add r3, r5, #0x0
	bl FUN_0206BDC8
	cmp r0, #0x0
	beq _0206BF80
	add sp, #0x54
	mov r0, #0x0
	pop {r4-r7, pc}
_0206BF80:
	ldr r0, [sp, #0x20]
	add r4, r4, #0x1
	cmp r4, r0
	blt _0206BF62
_0206BF88:
	mov r0, #0x1
	add sp, #0x54
	pop {r4-r7, pc}
	.balign 4
