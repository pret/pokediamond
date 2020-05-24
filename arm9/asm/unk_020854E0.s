    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020FCAA8
UNK_020FCAA8: ; 0x020FCAA8
	.word MOD61_021D74E0, MOD61_021D7550, MOD61_021D7568, SDK_OVERLAY_MODULE_61_ID

	.global UNK_020FCAB8
UNK_020FCAB8: ; 0x020FCAB8
	.word MOD15_021D74E0, MOD15_021D7558, MOD15_021D7608, SDK_OVERLAY_MODULE_15_ID

	.global UNK_020FCAC8
UNK_020FCAC8: ; 0x020FCAC8
	.word FUN_020857F8, FUN_0208585C, FUN_020859A0, 0xFFFFFFFF

	.text

	thumb_func_start FUN_020854E0
FUN_020854E0: ; 0x020854E0
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_02025838
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x20]
	mov r1, #0x1c
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [sp, #0x0]
	strb r0, [r4, #0xf]
	ldr r0, [sp, #0x4]
	strb r6, [r4, #0xe]
	str r0, [r4, #0x18]
	mov r0, #0x1
	strh r0, [r4, #0x0]
	str r7, [r4, #0x8]
	mov r0, #0x0
	strh r0, [r4, #0xc]
	ldr r0, [sp, #0x20]
	str r5, [r4, #0x10]
	bl FUN_020256BC
	str r0, [r4, #0x14]
	bl FUN_02025658
	ldr r0, [r4, #0x14]
	mov r1, #0xff
	add r2, r6, #0x0
	add r3, r5, #0x0
	bl FUN_020256DC
	add r0, r4, #0x0
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02085538
FUN_02085538: ; 0x02085538
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0x1c
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	str r5, [r4, #0x8]
	strh r6, [r4, #0xc]
	add r0, r7, #0x0
	str r7, [r4, #0x10]
	bl FUN_02025838
	ldr r3, [sp, #0x0]
	add r1, r5, #0x0
	add r2, r6, #0x0
	str r0, [r4, #0x18]
	bl FUN_020258B0
	str r0, [r4, #0x14]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02085578
FUN_02085578: ; 0x02085578
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x1c
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	str r5, [r4, #0x10]
	add r0, r7, #0x0
	bl FUN_020256BC
	str r0, [r4, #0x14]
	ldr r2, [r4, #0x14]
	add r0, r6, #0x0
	mov r1, #0xa9
	bl FUN_020671BC
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020855B0
FUN_020855B0: ; 0x020855B0
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x1c
	bl FUN_020169D8
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r4, #0x0]
	add r0, r7, #0x0
	str r5, [r4, #0x10]
	bl FUN_020256BC
	add r1, r6, #0x0
	str r0, [r4, #0x14]
	bl FUN_020257D0
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020855E4
FUN_020855E4: ; 0x020855E4
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_020855E8
FUN_020855E8: ; 0x020855E8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020855E4
	cmp r0, #0x0
	bne _020855FC
	mov r0, #0x0
	pop {r4-r6, pc}
_020855FC:
	ldr r0, [r5, #0x18]
	ldr r3, [r5, #0x14]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02025888
	mov r0, #0x1
	pop {r4-r6, pc}

	thumb_func_start FUN_0208560C
FUN_0208560C: ; 0x0208560C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020855E4
	cmp r0, #0x0
	bne _0208561E
	mov r0, #0x0
	pop {r3-r5, pc}
_0208561E:
	ldr r2, [r5, #0x14]
	add r0, r4, #0x0
	mov r1, #0xa9
	bl FUN_02067830
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_0208562C
FUN_0208562C: ; 0x0208562C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	beq _0208563A
	bl FUN_02016A18
_0208563A:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02085644
FUN_02085644: ; 0x02085644
	push {r3-r7, lr}
	add r5, r1, #0x0
	mov r1, #0x0
	add r7, r0, #0x0
	add r4, r2, #0x0
	str r1, [sp, #0x0]
	bl FUN_02025864
	add r6, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r6, r0
	beq _0208569E
	add r0, r4, #0x0
	bl FUN_020256BC
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xa9
	add r2, r4, #0x0
	bl FUN_020671BC
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_02025888
	add r0, r4, #0x0
	bl FUN_02025658
	add r0, r5, #0x0
	mov r1, #0xa9
	add r2, r4, #0x0
	bl FUN_02067830
	add r0, r5, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r6, #0x0
_0208569E:
	pop {r3-r7, pc}

	thumb_func_start FUN_020856A0
FUN_020856A0: ; 0x020856A0
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_020258B0
	add r6, r0, #0x0
	bne _020856BC
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
_020856BC:
	bl FUN_020257CC
	bl FUN_0206EAD8
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r1, #0xa9
	add r2, r6, #0x0
	bl FUN_02067830
	add r0, r4, #0x0
	mov r1, #0x6
	add r2, sp, #0x0
	bl FUN_02067830
	add r0, r7, #0x0
	mov r1, #0x0
	add r2, r5, #0x0
	bl FUN_02025878
	add r0, r6, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020856F0
FUN_020856F0: ; 0x020856F0
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x34
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x34
	add r6, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x0
	strh r0, [r6, #0x0]
	add r0, r4, #0x0
	bl FUN_020257C0
	str r0, [r6, #0x8]
	mov r0, #0x8
	add r1, r5, #0x0
	bl FUN_020219F4
	str r0, [r6, #0x10]
	add r0, r4, #0x0
	bl FUN_020257C4
	add r1, r0, #0x0
	ldr r0, [r6, #0x10]
	bl FUN_02021E28
	add r0, r4, #0x0
	bl FUN_020257CC
	strb r0, [r6, #0xf]
	add r0, r4, #0x0
	bl FUN_020257D8
	strb r0, [r6, #0xd]
	add r0, r4, #0x0
	bl FUN_020257DC
	strb r0, [r6, #0xe]
	mov r5, #0x0
	mov r7, #0x2
_02085748:
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	add r2, r7, #0x0
	bl FUN_020257E0
	lsl r1, r5, #0x1
	add r1, r6, r1
	strh r0, [r1, #0x14]
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3
	blo _02085748
	add r7, r6, #0x0
	mov r5, #0x0
	add r7, #0x1a
_0208576A:
	lsl r1, r5, #0x18
	add r0, r4, #0x0
	lsr r1, r1, #0x18
	bl FUN_02025814
	add r1, r0, #0x0
	lsl r0, r5, #0x3
	add r0, r7, r0
	bl FUN_02013960
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3
	blo _0208576A
	add r0, r6, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_0208578C
FUN_0208578C: ; 0x0208578C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	beq _0208579A
	bl FUN_02021A20
_0208579A:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020857A4
FUN_020857A4: ; 0x020857A4
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r4, r7, #0x0
	add r6, r0, #0x0
	mov r5, #0x0
	add r4, #0x1a
_020857B0:
	lsl r1, r5, #0x3
	lsl r2, r5, #0x18
	add r0, r6, #0x0
	add r1, r4, r1
	lsr r2, r2, #0x18
	bl FUN_02025824
	add r0, r5, #0x1
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3
	blo _020857B0
	ldrb r1, [r7, #0xf]
	add r0, r6, #0x0
	bl FUN_020257D0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020857D4
FUN_020857D4: ; 0x020857D4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020857F4
	bl FUN_02006290
	cmp r0, #0x0
	beq _020857F4
	ldr r0, [r4, #0x0]
	bl FUN_02006260
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_020857F4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020857F8
FUN_020857F8: ; 0x020857F8
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_0200628C
	mov r2, #0x1
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x28
	lsl r2, r2, #0xc
	bl FUN_0201681C
	add r0, r4, #0x0
	mov r1, #0x1c
	mov r2, #0x28
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x1c
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r1, #0x28
	str r1, [r4, #0x0]
	ldr r0, [r5, #0x14]
	bl FUN_020856F0
	str r0, [r4, #0x10]
	ldr r0, [r5, #0x10]
	bl LoadPlayerDataAddress
	ldr r1, [r4, #0x10]
	str r0, [r1, #0x4]
	ldrh r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02085844
	ldrb r1, [r5, #0xf]
	ldr r0, [r4, #0x10]
	strb r1, [r0, #0xf]
_02085844:
	ldr r1, [r4, #0x10]
	ldrb r0, [r1, #0xf]
	cmp r0, #0xc
	blo _02085850
	mov r0, #0x0
	strb r0, [r1, #0xf]
_02085850:
	ldrh r1, [r5, #0x0]
	ldr r0, [r4, #0x10]
	strh r1, [r0, #0x0]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0208585C
FUN_0208585C: ; 0x0208585C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0200628C
	add r6, r0, #0x0
	ldr r0, [r5, #0x0]
	cmp r0, #0x4
	bls _02085878
	b _02085990
_02085878:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02085884: ; jump table (using 16-bit offset)
	.short _0208588E - _02085884 - 2; case 0
	.short _020858A6 - _02085884 - 2; case 1
	.short _020858D2 - _02085884 - 2; case 2
	.short _02085900 - _02085884 - 2; case 3
	.short _0208595E - _02085884 - 2; case 4
_0208588E:
	ldrh r1, [r6, #0x0]
	ldr r0, [r4, #0x10]
	strh r1, [r0, #0x0]
	ldr r0, _02085994 ; =UNK_020FCAA8
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x0]
	bl FUN_02006234
	str r0, [r4, #0xc]
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _02085990
_020858A6:
	add r0, r4, #0x0
	add r0, #0xc
	bl FUN_020857D4
	cmp r0, #0x0
	beq _02085990
	ldr r0, [r4, #0x10]
	ldrh r1, [r0, #0x0]
	cmp r1, #0x3
	beq _020858C6
	ldr r0, _02085998 ; =0x0000FFFF
	cmp r1, r0
	bne _020858CC
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02085990
_020858C6:
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _02085990
_020858CC:
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _02085990
_020858D2:
	ldrh r0, [r6, #0x0]
	cmp r0, #0x1
	bne _020858FC
	ldr r1, [r4, #0x10]
	ldrh r0, [r1, #0x0]
	cmp r0, #0x3
	bne _020858F8
	ldr r0, [r6, #0x14]
	bl FUN_020857A4
	ldr r0, [r6, #0x10]
	bl FUN_02029FC8
	mov r1, #0x2
	bl FUN_0202A170
	mov r0, #0x1
	str r0, [r6, #0x4]
	b _020858FC
_020858F8:
	mov r0, #0x0
	str r0, [r6, #0x4]
_020858FC:
	mov r0, #0x1
	pop {r4-r6, pc}
_02085900:
	ldr r2, [r6, #0x10]
	ldr r3, [r4, #0x0]
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_02085338
	str r0, [r4, #0x8]
	ldr r0, [r4, #0x10]
	add r1, r0, #0x0
	ldrb r0, [r0, #0x2]
	add r1, #0x1a
	lsl r0, r0, #0x3
	add r0, r1, r0
	bl FUN_0201385C
	cmp r0, #0x0
	beq _02085938
	ldr r1, [r4, #0x10]
	add r0, r4, #0x0
	add r2, r1, #0x0
	ldrb r1, [r1, #0x2]
	add r2, #0x1a
	add r0, #0x14
	lsl r1, r1, #0x3
	add r1, r2, r1
	bl FUN_02013960
	b _02085942
_02085938:
	add r0, r4, #0x0
	add r0, #0x14
	mov r1, #0x3
	bl FUN_0201373C
_02085942:
	add r1, r4, #0x0
	ldr r0, [r4, #0x8]
	add r1, #0x14
	bl FUN_020853BC
	ldr r0, _0208599C ; =UNK_020FCAB8
	ldr r1, [r4, #0x8]
	ldr r2, [r4, #0x0]
	bl FUN_02006234
	str r0, [r4, #0xc]
	mov r0, #0x4
	str r0, [r5, #0x0]
	b _02085990
_0208595E:
	add r0, r4, #0x0
	add r0, #0xc
	bl FUN_020857D4
	cmp r0, #0x0
	beq _02085990
	ldr r0, [r4, #0x8]
	bl FUN_020853E4
	cmp r0, #0x0
	bne _02085986
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x8]
	add r2, r1, #0x0
	ldrb r1, [r1, #0x2]
	add r2, #0x1a
	lsl r1, r1, #0x3
	add r1, r2, r1
	bl FUN_020853FC
_02085986:
	ldr r0, [r4, #0x8]
	bl FUN_020853A8
	mov r0, #0x0
	str r0, [r5, #0x0]
_02085990:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_02085994: .word UNK_020FCAA8
_02085998: .word 0x0000FFFF
_0208599C: .word UNK_020FCAB8

	thumb_func_start FUN_020859A0
FUN_020859A0: ; 0x020859A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	ldr r0, [r4, #0x10]
	bl FUN_0208578C
	add r0, r5, #0x0
	bl FUN_0200627C
	ldr r0, [r4, #0x0]
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}
