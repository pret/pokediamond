	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02034188
FUN_02034188: ; 0x02034188
	push {r4-r7, lr}
	sub sp, #0x24
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0200E3A0
	bl FUN_02015EF4
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _02034368 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _0203436C ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	ldr r0, _02034370 ; =0x021C4918
	mov r1, #0x0
	strb r1, [r0, #0x5]
	bl FUN_0201E7A0
	ldr r3, _02034374 ; =0x04000050
	mov r0, #0x0
	strh r0, [r3, #0x0]
	ldr r2, _02034378 ; =0x04001050
	sub r3, #0x50
	strh r0, [r2, #0x0]
	ldr r1, [r3, #0x0]
	ldr r0, _0203437C ; =0xFFFF1FFF
	sub r2, #0x50
	and r1, r0
	str r1, [r3, #0x0]
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	ldr r0, _02034380 ; =0x020EED2C
	bl FUN_0201E66C
	add r0, r4, #0x0
	bl FUN_02016B94
	str r0, [sp, #0x10]
	ldr r0, _02034384 ; =0x020EED00
	bl FUN_02016BBC
	mov r1, #0x0
	ldr r0, [sp, #0x10]
	ldr r2, _02034388 ; =0x020EED10
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [sp, #0x10]
	ldr r2, _0203438C ; =0x000001F7
	mov r3, #0x2
	str r4, [sp, #0x4]
	bl FUN_0200CB00
	mov r0, #0x0
	mov r1, #0x20
	add r2, r4, #0x0
	bl FUN_02002ED0
	mov r0, #0x0
	mov r1, #0x20
	add r2, r0, #0x0
	add r3, r4, #0x0
	bl FUN_02017F18
	ldr r1, _02034390 ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _02034390 ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	ldr r2, _02034394 ; =0x00000265
	mov r0, #0x1
	mov r1, #0x1a
	add r3, r4, #0x0
	bl FUN_0200A86C
	str r0, [sp, #0xc]
	mov r0, #0x6
	lsl r0, r0, #0x6
	add r1, r4, #0x0
	bl FUN_020219F4
	add r4, r0, #0x0
	bl FUN_0201BD5C
	ldr r0, [sp, #0x10]
	ldr r2, _02034398 ; =0x020EECF8
	add r1, sp, #0x14
	bl FUN_02019150
	mov r0, #0xd0
	str r0, [sp, #0x0]
	mov r0, #0x90
	mov r2, #0x0
	str r0, [sp, #0x4]
	add r0, sp, #0x14
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	ldr r2, _0203438C ; =0x000001F7
	add r0, sp, #0x14
	mov r1, #0x0
	mov r3, #0x2
	bl FUN_0200CCA4
	ldr r0, [sp, #0xc]
	mov r1, #0xf
	add r2, r4, #0x0
	bl FUN_0200A8E0
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	add r0, sp, #0x14
	add r2, r4, #0x0
	add r3, r1, #0x0
	str r1, [sp, #0x8]
	bl FUN_0201BD84
	add r0, r4, #0x0
	bl FUN_02021A20
	bl FUN_0201E788
	mov r0, #0x0
	bl FUN_0200E394
	mov r0, #0x1
	bl FUN_0200E394
	mov r0, #0x0
	mov r1, #0x3f
	mov r2, #0x3
	bl FUN_0200A274
	ldr r4, _0203439C ; =0x04000130
	ldr r6, _020343A0 ; =0x027FFFA8
	mov r7, #0x1
_020342E4:
	ldrh r1, [r4, #0x0]
	ldrh r0, [r6, #0x0]
	orr r1, r0
	ldr r0, _020343A4 ; =0x00002FFF
	eor r1, r0
	and r0, r1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	bl FUN_02000FE8
	add r0, r5, #0x0
	tst r0, r7
	bne _02034308
	mov r0, #0x1
	add r1, r0, #0x0
	bl OS_WaitIrq
	b _020342E4
_02034308:
	add r0, sp, #0x14
	bl FUN_02019178
	ldr r0, [sp, #0xc]
	bl FUN_0200A8B8
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
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	bl FUN_020178A0
	ldr r0, [sp, #0x10]
	bl FUN_02016A18
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_02034368: .word 0xFFFFE0FF
_0203436C: .word 0x04001000
_02034370: .word 0x021C4918
_02034374: .word 0x04000050
_02034378: .word 0x04001050
_0203437C: .word 0xFFFF1FFF
_02034380: .word 0x020EED2C
_02034384: .word 0x020EED00
_02034388: .word 0x020EED10
_0203438C: .word 0x000001F7
_02034390: .word 0x00006C21
_02034394: .word 0x00000265
_02034398: .word 0x020EECF8
_0203439C: .word 0x04000130
_020343A0: .word 0x027FFFA8
_020343A4: .word 0x00002FFF
