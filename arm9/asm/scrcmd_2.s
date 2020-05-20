    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0203FCF4
FUN_0203FCF4: ; 0x0203FCF4
	push {r4-r7, lr}
	sub sp, #0x84
	add r7, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	mov r4, #0x0
	add r6, r4, #0x0
	add r5, r4, #0x0
_0203FD10:
	add r0, r7, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r5, #0x0
	bl FUN_020239D0
	cmp r0, #0x1
	bne _0203FD2C
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_0203FD2C:
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0203FD10
	cmp r6, #0x8
	bhi _0203FD70
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0203FD46: ; jump table (using 16-bit offset)
	.short _0203FD58 - _0203FD46 - 2; case 0
	.short _0203FD5C - _0203FD46 - 2; case 1
	.short _0203FD5C - _0203FD46 - 2; case 2
	.short _0203FD60 - _0203FD46 - 2; case 3
	.short _0203FD60 - _0203FD46 - 2; case 4
	.short _0203FD64 - _0203FD46 - 2; case 5
	.short _0203FD64 - _0203FD46 - 2; case 6
	.short _0203FD68 - _0203FD46 - 2; case 7
	.short _0203FD6C - _0203FD46 - 2; case 8
_0203FD58:
	mov r1, #0x1
	b _0203FD72
_0203FD5C:
	mov r1, #0x2
	b _0203FD72
_0203FD60:
	mov r1, #0x3
	b _0203FD72
_0203FD64:
	mov r1, #0x4
	b _0203FD72
_0203FD68:
	mov r1, #0x5
	b _0203FD72
_0203FD6C:
	mov r1, #0x6
	b _0203FD72
_0203FD70:
	mov r1, #0x1
_0203FD72:
	ldr r0, _0203FDB4 ; =0x020F4218
	mov r2, #0x0
	add r6, sp, #0x4
_0203FD78:
	lsl r3, r2, #0x2
	add r5, r0, r3
	ldrh r3, [r5, #0x2]
	cmp r1, r3
	blt _0203FD8E
	ldrh r5, [r5, #0x0]
	lsl r3, r4, #0x1
	strh r5, [r6, r3]
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	lsr r4, r3, #0x18
_0203FD8E:
	add r2, r2, #0x1
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	cmp r2, #0x13
	blo _0203FD78
	ldr r1, _0203FDB8 ; =0x0000FFFF
	lsl r0, r4, #0x1
	add r2, sp, #0x4
	strh r1, [r2, r0]
	mov r3, #0x0
	str r3, [sp, #0x0]
	ldr r0, [r7, #0x74]
	add r7, #0x80
	ldr r1, [r7, #0x0]
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x84
	pop {r4-r7, pc}
	.balign 4
_0203FDB4: .word 0x020F4218
_0203FDB8: .word 0x0000FFFF

	thumb_func_start FUN_0203FDBC
FUN_0203FDBC: ; 0x0203FDBC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	ldr r0, _0203FE00 ; =0x0000FFF8
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x5
	bhi _0203FDE4
	mov r0, #0x1
	b _0203FDE6
_0203FDE4:
	mov r0, #0x0
_0203FDE6:
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE04 ; =0x02105E10
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x0
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE00: .word 0x0000FFF8
_0203FE04: .word 0x02105E10

	thumb_func_start FUN_0203FE08
FUN_0203FE08: ; 0x0203FE08
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	cmp r2, #0x1
	bhi _0203FE28
	mov r0, #0x1
	b _0203FE2A
_0203FE28:
	mov r0, #0x0
_0203FE2A:
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE44 ; =0x02105DEC
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x1
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE44: .word 0x02105DEC

	thumb_func_start FUN_0203FE48
FUN_0203FE48: ; 0x0203FE48
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r2, r0, #0x0
	mov r0, #0x0
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE7C ; =0x02105DF4
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x2
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE7C: .word 0x02105DF4

	thumb_func_start FUN_0203FE80
FUN_0203FE80: ; 0x0203FE80
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02038AD0
	mov r0, #0x1
	pop {r3, pc}
