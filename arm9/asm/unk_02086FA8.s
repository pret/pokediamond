    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FD118

	.text

	thumb_func_start FUN_02086FA8
FUN_02086FA8: ; 0x02086FA8
	push {r3, lr}
	ldr r1, [r0, #0x58]
	lsl r2, r1, #0x2
	ldr r1, _02086FB8 ; =UNK_020FD118
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02086FB8: .word UNK_020FD118

	thumb_func_start FUN_02086FBC
FUN_02086FBC: ; 0x02086FBC
	push {r3-r5, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	ldr r1, [r4, #0x5c]
	mov r5, #0x1
	cmp r1, #0x11
	bls _02086FCC
	b _0208720E
_02086FCC:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02086FD8: ; jump table (using 16-bit offset)
	.short _02086FFC - _02086FD8 - 2; case 0
	.short _0208706A - _02086FD8 - 2; case 1
	.short _02087074 - _02086FD8 - 2; case 2
	.short _02087092 - _02086FD8 - 2; case 3
	.short _020870A2 - _02086FD8 - 2; case 4
	.short _020870B2 - _02086FD8 - 2; case 5
	.short _020870C2 - _02086FD8 - 2; case 6
	.short _020870D2 - _02086FD8 - 2; case 7
	.short _0208710E - _02086FD8 - 2; case 8
	.short _02087122 - _02086FD8 - 2; case 9
	.short _02087132 - _02086FD8 - 2; case 10
	.short _02087158 - _02086FD8 - 2; case 11
	.short _020871AA - _02086FD8 - 2; case 12
	.short _020871E2 - _02086FD8 - 2; case 13
	.short _020871EE - _02086FD8 - 2; case 14
	.short _020871F4 - _02086FD8 - 2; case 15
	.short _020871FE - _02086FD8 - 2; case 16
	.short _0208720E - _02086FD8 - 2; case 17
_02086FFC:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_0208699C
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_020869F0
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x14]
	bl FUN_020866FC
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x3b
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	add r1, r4, #0x0
	ldr r0, [r4, #0x4]
	add r1, #0x18
	add r2, r5, #0x0
	mov r3, #0x2
	bl FUN_02086784
	add r0, r4, #0x0
	bl FUN_02086BA8
	add r0, r4, #0x0
	bl FUN_02086CB0
	add r0, r4, #0x0
	bl FUN_02086EE8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02086F98
	mov r0, #0x47
	str r0, [sp, #0x18]
	mov r0, #0x0
	str r0, [sp, #0x1c]
	add r0, sp, #0x18
	bl FUN_02086B40
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_0208706A:
	bl FUN_020866BC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087074:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0208712A
	bl FUN_0200541C
	ldr r1, _02087240 ; =0x00000475
	mov r0, #0xd
	mov r2, #0x1
	bl FUN_0200433C
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_02087092:
	bl FUN_0208749C
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870A2:
	bl FUN_020874E4
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870B2:
	bl FUN_02087554
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870C2:
	bl FUN_020875AC
	cmp r0, #0x0
	bne _0208712A
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020870D2:
	bl FUN_02087610
	cmp r0, #0x0
	bne _0208712A
	add r0, r4, #0x0
	bl FUN_02086F4C
	ldr r0, [r4, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x0
	bl FUN_020867EC
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_0208710E:
	bl FUN_02005670
	cmp r0, #0x0
	bne _0208712A
	ldr r0, _02087244 ; =0x00000484
	bl FUN_02005C28
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087122:
	bl FUN_02005CBC
	cmp r0, #0x0
	beq _0208712C
_0208712A:
	b _02087232
_0208712C:
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087132:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087232
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x1
	bl FUN_020867EC
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087158:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087232
	ldr r0, [r4, #0x54]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _02087232
	ldr r0, [r4, #0x68]
	bl FUN_02007390
	cmp r0, #0x0
	bne _02087232
	mov r0, #0x19
	str r0, [sp, #0x0]
	mov r0, #0xd
	str r0, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	mov r0, #0xa7
	str r0, [sp, #0x10]
	mov r0, #0xe
	str r0, [sp, #0x14]
	add r2, r4, #0x0
	ldr r1, [r4, #0x4]
	add r0, r4, #0x0
	add r2, #0x28
	mov r3, #0x1
	bl FUN_02086878
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871AA:
	ldr r0, [r4, #0x48]
	bl FUN_02001C78
	sub r1, r5, #0x3
	cmp r0, r1
	beq _020871BE
	add r1, r1, #0x1
	cmp r0, r1
	beq _02087232
	b _020871CC
_020871BE:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871CC:
	cmp r0, #0x0
	bne _020871D4
	add r1, r5, #0x0
	b _020871D6
_020871D4:
	mov r1, #0x0
_020871D6:
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871E2:
	bl FUN_02086960
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871EE:
	add r0, r1, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_020871F4:
	bl FUN_020866DC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_020871FE:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02087232
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087232
_0208720E:
	add r0, r4, #0x0
	bl FUN_02086F8C
	add r0, r4, #0x0
	bl FUN_02086E30
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_0208698C
	ldr r0, [r4, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02086AF0
	ldr r0, [r4, #0x40]
	bl FUN_02086BA0
	mov r5, #0x0
_02087232:
	ldr r0, [r4, #0x4c]
	bl FUN_0200BC1C
	add r0, r5, #0x0
	add sp, #0x20
	pop {r3-r5, pc}
	nop
_02087240: .word 0x00000475
_02087244: .word 0x00000484

	thumb_func_start FUN_02087248
FUN_02087248: ; 0x02087248
	push {r3-r5, lr}
	sub sp, #0x20
	add r4, r0, #0x0
	ldr r1, [r4, #0x5c]
	mov r5, #0x1
	cmp r1, #0x11
	bls _02087258
	b _02087462
_02087258:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_02087264: ; jump table (using 16-bit offset)
	.short _02087288 - _02087264 - 2; case 0
	.short _020872FE - _02087264 - 2; case 1
	.short _02087308 - _02087264 - 2; case 2
	.short _02087322 - _02087264 - 2; case 3
	.short _0208735C - _02087264 - 2; case 4
	.short _0208735C - _02087264 - 2; case 5
	.short _0208735C - _02087264 - 2; case 6
	.short _0208735C - _02087264 - 2; case 7
	.short _02087362 - _02087264 - 2; case 8
	.short _02087376 - _02087264 - 2; case 9
	.short _02087386 - _02087264 - 2; case 10
	.short _020873AC - _02087264 - 2; case 11
	.short _020873FE - _02087264 - 2; case 12
	.short _02087436 - _02087264 - 2; case 13
	.short _02087442 - _02087264 - 2; case 14
	.short _02087448 - _02087264 - 2; case 15
	.short _02087452 - _02087264 - 2; case 16
	.short _02087462 - _02087264 - 2; case 17
_02087288:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_0208699C
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	bl FUN_020869F0
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x14]
	bl FUN_020866FC
	mov r0, #0x13
	str r0, [sp, #0x0]
	mov r0, #0x1b
	str r0, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	mov r0, #0x3b
	str r0, [sp, #0xc]
	mov r0, #0xe
	str r0, [sp, #0x10]
	add r1, r4, #0x0
	ldr r0, [r4, #0x4]
	add r1, #0x18
	add r2, r5, #0x0
	mov r3, #0x2
	bl FUN_02086784
	add r0, r4, #0x0
	bl FUN_02086BA8
	add r0, r4, #0x0
	bl FUN_02086CB0
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	add r0, r4, #0x0
	bl FUN_02086EE8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_02086F98
	mov r0, #0x47
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	str r0, [sp, #0x1c]
	add r0, sp, #0x18
	bl FUN_02086B40
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_020872FE:
	bl FUN_020866BC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087308:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0208737E
	ldr r1, _02087494 ; =0x00000475
	mov r0, #0xd
	mov r2, #0x1
	bl FUN_0200433C
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087322:
	bl FUN_02087820
	cmp r0, #0x0
	bne _0208737E
	add r0, r4, #0x0
	bl FUN_02086F4C
	ldr r0, [r4, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02005578
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x0
	bl FUN_020867EC
	str r0, [r4, #0xc]
	mov r0, #0x8
	str r0, [r4, #0x5c]
	b _02087486
_0208735C:
	bl ErrorHandling
	b _02087486
_02087362:
	bl FUN_02005670
	cmp r0, #0x0
	bne _0208737E
	ldr r0, _02087498 ; =0x00000484
	bl FUN_02005C28
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087376:
	bl FUN_02005CBC
	cmp r0, #0x0
	beq _02087380
_0208737E:
	b _02087486
_02087380:
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087386:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087486
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	ldr r2, [r2, #0xc]
	ldr r3, [r4, #0x10]
	add r0, #0x18
	mov r1, #0x1
	bl FUN_020867EC
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_020873AC:
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02087486
	ldr r0, [r4, #0x54]
	mov r1, #0x0
	bl FUN_02014D7C
	cmp r0, #0x1
	bne _02087486
	ldr r0, [r4, #0x68]
	bl FUN_02007390
	cmp r0, #0x0
	bne _02087486
	mov r0, #0x19
	str r0, [sp, #0x0]
	mov r0, #0xd
	str r0, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	mov r0, #0x4
	str r0, [sp, #0xc]
	mov r0, #0xa7
	str r0, [sp, #0x10]
	mov r0, #0xe
	str r0, [sp, #0x14]
	add r2, r4, #0x0
	ldr r1, [r4, #0x4]
	add r0, r4, #0x0
	add r2, #0x28
	mov r3, #0x1
	bl FUN_02086878
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_020873FE:
	ldr r0, [r4, #0x48]
	bl FUN_02001C78
	sub r1, r5, #0x3
	cmp r0, r1
	beq _02087412
	add r1, r1, #0x1
	cmp r0, r1
	beq _02087486
	b _02087420
_02087412:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087420:
	cmp r0, #0x0
	bne _02087428
	add r1, r5, #0x0
	b _0208742A
_02087428:
	mov r1, #0x0
_0208742A:
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087436:
	bl FUN_02086960
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087442:
	add r0, r1, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087448:
	bl FUN_020866DC
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
_02087452:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _02087486
	ldr r0, [r4, #0x5c]
	add r0, r0, #0x1
	str r0, [r4, #0x5c]
	b _02087486
_02087462:
	add r0, r4, #0x0
	bl FUN_02086F8C
	add r0, r4, #0x0
	bl FUN_02086E30
	add r0, r4, #0x0
	add r0, #0x18
	bl FUN_0208698C
	ldr r0, [r4, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02086AF0
	ldr r0, [r4, #0x40]
	bl FUN_02086BA0
	mov r5, #0x0
_02087486:
	ldr r0, [r4, #0x4c]
	bl FUN_0200BC1C
	add r0, r5, #0x0
	add sp, #0x20
	pop {r3-r5, pc}
	nop
_02087494: .word 0x00000475
_02087498: .word 0x00000484

	thumb_func_start FUN_0208749C
FUN_0208749C: ; 0x0208749C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x64]
	cmp r0, #0x0
	beq _020874AC
	cmp r0, #0x1
	beq _020874BC
	b _020874D4
_020874AC:
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C61C
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _020874DC
_020874BC:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0x19
	blt _020874DC
	ldr r0, _020874E0 ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _020874DC
_020874D4:
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r4, pc}
_020874DC:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_020874E0: .word 0x00000714

	thumb_func_start FUN_020874E4
FUN_020874E4: ; 0x020874E4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _020874F4
	cmp r1, #0x1
	beq _0208750E
	b _02087532
_020874F4:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _0208754C
	ldr r0, [r4, #0x6c]
	mov r1, #0x1
	bl FUN_0200C61C
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _0208754C
_0208750E:
	mov r1, #0x0
	bl FUN_02086E04
	cmp r0, #0x2
	bne _0208754C
	ldr r0, _02087550 ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x6c]
	mov r1, #0x2
	bl FUN_0200C61C
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	mov r0, #0x0
	str r0, [r4, #0x60]
	b _0208754C
_02087532:
	mov r1, #0x0
	bl FUN_02086E04
	cmp r0, #0x2
	bne _0208754C
	ldr r0, [r4, #0x6c]
	mov r1, #0x2
	bl FUN_0200C61C
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r4, pc}
_0208754C:
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02087550: .word 0x00000714

	thumb_func_start FUN_02087554
FUN_02087554: ; 0x02087554
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _02087564
	cmp r1, #0x1
	beq _0208756A
	b _0208759C
_02087564:
	add r0, r1, #0x1
	str r0, [r4, #0x64]
	b _020875A4
_0208756A:
	mov r1, #0x1
	bl FUN_02086E04
	add r5, r0, #0x0
	cmp r5, #0x1
	bne _0208758C
	ldr r0, _020875A8 ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x6c]
	mov r1, #0x3
	bl FUN_0200C61C
	ldr r0, [r4, #0x40]
	mov r1, #0x0
	bl FUN_02086B70
_0208758C:
	cmp r5, #0x2
	bne _020875A4
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _020875A4
_0208759C:
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r3-r5, pc}
_020875A4:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_020875A8: .word 0x00000714

	thumb_func_start FUN_020875AC
FUN_020875AC: ; 0x020875AC
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _020875BC
	cmp r1, #0x1
	beq _020875CE
	b _02087600
_020875BC:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _02087608
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087608
_020875CE:
	mov r1, #0x2
	bl FUN_02086E04
	add r5, r0, #0x0
	cmp r5, #0x1
	bne _020875F0
	ldr r0, _0208760C ; =0x00000714
	bl FUN_020054C8
	ldr r0, [r4, #0x6c]
	mov r1, #0x4
	bl FUN_0200C61C
	ldr r0, [r4, #0x40]
	mov r1, #0x1
	bl FUN_02086B70
_020875F0:
	cmp r5, #0x2
	bne _02087608
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087608
_02087600:
	mov r0, #0x0
	str r0, [r4, #0x64]
	str r0, [r4, #0x60]
	pop {r3-r5, pc}
_02087608:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_0208760C: .word 0x00000714

	thumb_func_start FUN_02087610
FUN_02087610: ; 0x02087610
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0x64]
	cmp r1, #0x5
	bls _0208761E
	b _020877FC
_0208761E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0208762A: ; jump table (using 16-bit offset)
	.short _02087636 - _0208762A - 2; case 0
	.short _02087658 - _0208762A - 2; case 1
	.short _0208769A - _0208762A - 2; case 2
	.short _02087702 - _0208762A - 2; case 3
	.short _02087794 - _0208762A - 2; case 4
	.short _020877E0 - _0208762A - 2; case 5
_02087636:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _020876A4
	ldr r0, [r4, #0x6c]
	mov r1, #0x4
	bl FUN_0200C61C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_02087658:
	mov r1, #0x3
	bl FUN_02086E04
	add r5, r0, #0x0
	cmp r5, #0x1
	bne _02087682
	ldr r0, [r4, #0x6c]
	mov r1, #0x5
	bl FUN_0200C61C
	ldr r0, _02087818 ; =0x00000707
	bl FUN_020054C8
	ldr r0, [r4, #0x40]
	mov r1, #0x2
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x3
	bl FUN_02086B70
_02087682:
	cmp r5, #0x2
	bne _020876A4
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_0208769A:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0xa
	bge _020876A6
_020876A4:
	b _02087810
_020876A6:
	mov r3, #0x0
	str r3, [r4, #0x60]
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _0208781C ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	bl FUN_02020354
	mov r1, #0x1
	bl FUN_0201E28C
	add r5, r0, #0x0
	mov r3, #0x0
	mov r6, #0x1
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _0208781C ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	lsl r6, r5
	eor r2, r6
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	lsr r2, r2, #0x10
	bl FUN_02003210
	ldr r0, _0208781C ; =0x0000FFFF
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E68
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_02087702:
	add r1, sp, #0xc
	ldr r0, [r4, #0x70]
	mov r5, #0x0
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	add r1, r5, #0x0
	ldrsh r2, [r0, r1]
	add r0, r1, #0x0
	sub r0, #0x30
	cmp r2, r0
	ble _02087728
	ldr r0, [r4, #0x70]
	sub r2, r1, #0x4
	bl FUN_0200C82C
	b _0208772A
_02087728:
	add r5, r5, #0x1
_0208772A:
	add r1, sp, #0xc
	ldr r0, [r4, #0x74]
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, #0xc0
	bge _0208774A
	ldr r0, [r4, #0x74]
	mov r2, #0x4
	bl FUN_0200C82C
	b _0208774C
_0208774A:
	add r5, r5, #0x1
_0208774C:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087810
	cmp r5, #0x2
	bne _02087810
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087810
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_0201E6E4
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02086F98
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x70]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x74]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_02087794:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0x19
	blt _02087810
	mov r2, #0x0
	ldr r0, _0208781C ; =0x0000FFFF
	str r2, [r4, #0x60]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E68
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _0208781C ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _0208781C ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_02003210
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_020877E0:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087810
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087810
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087810
_020877FC:
	ldr r0, [r4, #0x40]
	bl FUN_02086B8C
	cmp r0, #0x1
	beq _02087810
	mov r0, #0x0
	str r0, [r4, #0x64]
	add sp, #0x10
	str r0, [r4, #0x60]
	pop {r4-r6, pc}
_02087810:
	mov r0, #0x1
	add sp, #0x10
	pop {r4-r6, pc}
	nop
_02087818: .word 0x00000707
_0208781C: .word 0x0000FFFF

	thumb_func_start FUN_02087820
FUN_02087820: ; 0x02087820
	push {r4-r6, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r0, [r4, #0x64]
	cmp r0, #0x4
	bls _0208782E
	b _020879FC
_0208782E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0208783A: ; jump table (using 16-bit offset)
	.short _02087844 - _0208783A - 2; case 0
	.short _02087874 - _0208783A - 2; case 1
	.short _02087902 - _0208783A - 2; case 2
	.short _02087994 - _0208783A - 2; case 3
	.short _020879E0 - _0208783A - 2; case 4
_02087844:
	ldr r0, [r4, #0x40]
	mov r1, #0x0
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x1
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x2
	bl FUN_02086B70
	ldr r0, [r4, #0x40]
	mov r1, #0x3
	bl FUN_02086B70
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_02087874:
	ldr r0, [r4, #0x60]
	cmp r0, #0x19
	beq _02087884
	cmp r0, #0x50
	beq _0208788C
	cmp r0, #0x8e
	beq _02087894
	b _0208789A
_02087884:
	ldr r0, _02087A0C ; =0x00000806
	bl FUN_020054C8
	b _0208789A
_0208788C:
	ldr r0, _02087A10 ; =0x000007AA
	bl FUN_020054C8
	b _0208789A
_02087894:
	ldr r0, _02087A14 ; =0x00000815
	bl FUN_020054C8
_0208789A:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0xa0
	bge _020878A6
	b _02087A06
_020878A6:
	mov r3, #0x0
	str r3, [r4, #0x60]
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _02087A18 ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	ldr r0, [r4, #0x70]
	ldr r0, [r0, #0x0]
	bl FUN_02020354
	mov r1, #0x1
	bl FUN_0201E28C
	add r5, r0, #0x0
	mov r3, #0x0
	mov r6, #0x1
	str r3, [sp, #0x0]
	mov r0, #0x10
	ldr r2, _02087A18 ; =0x0000FFFF
	str r0, [sp, #0x4]
	str r2, [sp, #0x8]
	lsl r6, r5
	eor r2, r6
	lsl r2, r2, #0x10
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	lsr r2, r2, #0x10
	bl FUN_02003210
	ldr r0, _02087A18 ; =0x0000FFFF
	mov r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r2, #0x10
	add r3, r1, #0x0
	bl FUN_02007E68
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_02087902:
	add r1, sp, #0xc
	ldr r0, [r4, #0x70]
	mov r5, #0x0
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	add r1, r5, #0x0
	ldrsh r2, [r0, r1]
	add r0, r1, #0x0
	sub r0, #0x30
	cmp r2, r0
	ble _02087928
	ldr r0, [r4, #0x70]
	sub r2, r1, #0x4
	bl FUN_0200C82C
	b _0208792A
_02087928:
	add r5, r5, #0x1
_0208792A:
	add r1, sp, #0xc
	ldr r0, [r4, #0x74]
	add r1, #0x2
	add r2, sp, #0xc
	bl FUN_0200C7A0
	add r0, sp, #0xc
	mov r1, #0x0
	ldrsh r0, [r0, r1]
	cmp r0, #0xc0
	bge _0208794A
	ldr r0, [r4, #0x74]
	mov r2, #0x4
	bl FUN_0200C82C
	b _0208794C
_0208794A:
	add r5, r5, #0x1
_0208794C:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087A06
	cmp r5, #0x2
	bne _02087A06
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087A06
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02086F98
	mov r0, #0x2
	mov r1, #0x1
	bl FUN_0201E6E4
	ldr r0, [r4, #0x6c]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x70]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x74]
	mov r1, #0x0
	bl FUN_0200C644
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_02087994:
	ldr r0, [r4, #0x60]
	add r0, r0, #0x1
	str r0, [r4, #0x60]
	cmp r0, #0x19
	blt _02087A06
	mov r2, #0x0
	ldr r0, _02087A18 ; =0x0000FFFF
	str r2, [r4, #0x60]
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x68]
	mov r1, #0x10
	add r3, r2, #0x0
	bl FUN_02007E68
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _02087A18 ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003210
	mov r0, #0x10
	str r0, [sp, #0x0]
	mov r3, #0x0
	ldr r2, _02087A18 ; =0x0000FFFF
	str r3, [sp, #0x4]
	str r2, [sp, #0x8]
	ldr r0, [r4, #0x8]
	mov r1, #0x4
	bl FUN_02003210
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_020879E0:
	ldr r0, [r4, #0x8]
	bl FUN_020038E4
	cmp r0, #0x0
	bne _02087A06
	ldr r0, [r4, #0x68]
	bl FUN_02007F20
	cmp r0, #0x0
	bne _02087A06
	ldr r0, [r4, #0x64]
	add r0, r0, #0x1
	str r0, [r4, #0x64]
	b _02087A06
_020879FC:
	mov r0, #0x0
	str r0, [r4, #0x64]
	add sp, #0x10
	str r0, [r4, #0x60]
	pop {r4-r6, pc}
_02087A06:
	mov r0, #0x1
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02087A0C: .word 0x00000806
_02087A10: .word 0x000007AA
_02087A14: .word 0x00000815
_02087A18: .word 0x0000FFFF
