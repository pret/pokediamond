    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020023C0
FUN_020023C0: ; 0x020023C0
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r1, r4, #0x0
	add r1, #0x24
	ldrb r1, [r1, #0x0]
	add r6, r4, #0x0
	add r6, #0x1c
	cmp r1, #0x6
	bls _020023D6
	b _02002838
_020023D6:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020023E2: ; jump table (using 16-bit offset)
	.short _020023F0 - _020023E2 - 2; case 0
	.short _02002742 - _020023E2 - 2; case 1
	.short _0200275C - _020023E2 - 2; case 2
	.short _02002786 - _020023E2 - 2; case 3
	.short _020027B6 - _020023E2 - 2; case 4
	.short _0200280C - _020023E2 - 2; case 5
	.short _02002818 - _020023E2 - 2; case 6
_020023F0:
	ldr r0, _02002658 ; =0x021C48B8
	ldr r1, [r0, #0x44]
	mov r0, #0x3
	tst r0, r1
	beq _02002402
	ldrb r0, [r6, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bne _02002414
_02002402:
	ldr r0, _0200265C ; =0x021C48F8
	ldrh r0, [r0, #0x22]
	cmp r0, #0x0
	beq _02002432
	ldr r0, _02002660 ; =0x02106FC4
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _02002432
_02002414:
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0x26
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	beq _02002432
	ldr r1, _02002660 ; =0x02106FC4
	mov r0, #0x40
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
_02002432:
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0200248C
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x19
	beq _0200248C
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x26
	strb r1, [r0, #0x0]
	ldr r0, _02002660 ; =0x02106FC4
	ldrb r0, [r0, #0x0]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	beq _02002486
	ldr r1, _02002658 ; =0x021C48B8
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	bne _02002478
	ldr r1, _0200265C ; =0x021C48F8
	ldrh r1, [r1, #0x20]
	cmp r1, #0x0
	beq _02002486
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _02002486
_02002478:
	ldrb r1, [r6, #0x0]
	mov r0, #0x10
	add r4, #0x26
	orr r0, r1
	strb r0, [r6, #0x0]
	mov r0, #0x0
	strb r0, [r4, #0x0]
_02002486:
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_0200248C:
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r1, r0, #0x19
	add r0, r4, #0x0
	add r0, #0x26
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	ldrh r5, [r0, #0x0]
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	mov r0, #0xf1
	lsl r0, r0, #0x8
	cmp r5, r0
	bne _020024B0
	bl ErrorHandling
_020024B0:
	ldr r0, _02002664 ; =0x0000F0FD
	cmp r5, r0
	bgt _020024DA
	bge _0200250E
	ldr r1, _02002668 ; =0x000025BD
	cmp r5, r1
	bgt _020024D0
	sub r0, r1, #0x1
	cmp r5, r0
	blt _020024CE
	bne _020024C8
	b _020026D8
_020024C8:
	cmp r5, r1
	bne _020024CE
	b _020026EC
_020024CE:
	b _02002700
_020024D0:
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r5, r0
	beq _020024F2
	b _02002700
_020024DA:
	ldr r0, _0200266C ; =0x0000FFFE
	cmp r5, r0
	bgt _020024E4
	beq _0200251A
	b _02002700
_020024E4:
	add r0, r0, #0x1
	cmp r5, r0
	beq _020024EC
	b _02002700
_020024EC:
	add sp, #0xc
	mov r0, #0x1
	pop {r3-r6, pc}
_020024F2:
	ldrb r0, [r4, #0xa]
	mov r1, #0x1
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0x9]
	bl FUN_02002E4C
	ldrb r1, [r4, #0xf]
	ldrb r2, [r4, #0xd]
	add sp, #0xc
	add r0, r1, r0
	add r0, r2, r0
	strb r0, [r4, #0xd]
	mov r0, #0x2
	pop {r3-r6, pc}
_0200250E:
	ldr r0, [r4, #0x0]
	add sp, #0xc
	add r0, r0, #0x2
	str r0, [r4, #0x0]
	mov r0, #0x2
	pop {r3-r6, pc}
_0200251A:
	ldr r0, [r4, #0x0]
	sub r0, r0, #0x2
	str r0, [r4, #0x0]
	bl FUN_0201B8E0
	lsl r0, r0, #0x10
	ldr r1, _02002670 ; =0x0000FE06
	lsr r0, r0, #0x10
	cmp r0, r1
	bgt _02002552
	blt _02002532
	b _02002678
_02002532:
	mov r1, #0x2
	lsl r1, r1, #0x8
	sub r1, r0, r1
	cmp r1, #0x4
	bhi _0200255C
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02002548: ; jump table (using 16-bit offset)
	.short _020025B4 - _02002548 - 2; case 0
	.short _020025DE - _02002548 - 2; case 1
	.short _02002600 - _02002548 - 2; case 2
	.short _02002618 - _02002548 - 2; case 3
	.short _02002624 - _02002548 - 2; case 4
_02002552:
	mov r1, #0xff
	lsl r1, r1, #0x8
	cmp r0, r1
	bgt _0200255E
	beq _02002566
_0200255C:
	b _020026CA
_0200255E:
	add r1, r1, #0x1
	cmp r0, r1
	beq _02002630
	b _020026CA
_02002566:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0xff
	bne _02002596
	ldrb r0, [r4, #0x11]
	ldrb r2, [r4, #0x17]
	sub r1, r0, #0x1
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r0, r0, #0x1
	add r0, #0x64
	strb r0, [r4, #0x17]
	cmp r2, #0x64
	blo _02002644
	cmp r2, #0x6b
	bhs _02002644
	sub r2, #0x64
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	b _0200259E
_02002596:
	cmp r0, #0x64
	blo _0200259E
	strb r0, [r4, #0x17]
	b _020026CA
_0200259E:
	lsl r1, r0, #0x1
	add r0, r1, #0x1
	strb r0, [r4, #0x11]
	add r0, r1, #0x2
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x11]
	ldrb r1, [r4, #0x12]
	ldrb r2, [r4, #0x13]
	bl FUN_0201C05C
	b _020026CA
_020025B4:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	ldrb r1, [r4, #0xc]
	ldrb r2, [r4, #0xd]
	add r0, r4, #0x0
	bl FUN_0201C1EC
	add r0, r4, #0x0
	add r0, #0x25
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	beq _020026CA
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
	b _020026CA
_020025DE:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	add r1, r4, #0x0
	add r1, #0x26
	strb r0, [r1, #0x0]
	ldr r0, [r4, #0x0]
	bl FUN_0201B8B8
	str r0, [r4, #0x0]
	mov r0, #0x6
	add r4, #0x24
	strb r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_02002600:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	strh r0, [r4, #0x2a]
	ldr r0, [r4, #0x0]
	bl FUN_0201B8B8
	str r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_02002618:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	strb r0, [r4, #0xc]
	b _020026CA
_02002624:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	strb r0, [r4, #0xd]
	b _020026CA
_02002630:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x64
	beq _02002646
	cmp r0, #0xc8
	beq _0200264E
_02002644:
	b _020026CA
_02002646:
	mov r0, #0x0
	strh r0, [r4, #0x14]
	strb r0, [r4, #0x16]
	b _020026CA
_0200264E:
	ldr r0, _02002674 ; =0x0000FFFC
	strh r0, [r4, #0x14]
	mov r0, #0x0
	strb r0, [r4, #0x16]
	b _020026CA
	.balign 4
_02002658: .word 0x021C48B8
_0200265C: .word 0x021C48F8
_02002660: .word 0x02106FC4
_02002664: .word 0x0000F0FD
_02002668: .word 0x000025BD
_0200266C: .word 0x0000FFFE
_02002670: .word 0x0000FE06
_02002674: .word 0x0000FFFC
_02002678:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_0201B914
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	mov r0, #0xfe
	lsl r0, r0, #0x8
	cmp r1, r0
	beq _020026AE
	add r0, r0, #0x1
	cmp r1, r0
	bne _020026CA
	add r0, r4, #0x0
	mov r1, #0x2
	add r0, #0x24
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0200284C
	ldr r0, [r4, #0x0]
	bl FUN_0201B8B8
	str r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_020026AE:
	add r0, r4, #0x0
	mov r1, #0x3
	add r0, #0x24
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0200284C
	ldr r0, [r4, #0x0]
	bl FUN_0201B8B8
	str r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_020026CA:
	ldr r0, [r4, #0x0]
	bl FUN_0201B8B8
	str r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x2
	pop {r3-r6, pc}
_020026D8:
	add r0, r4, #0x0
	mov r1, #0x2
	add r0, #0x24
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0200284C
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_020026EC:
	add r0, r4, #0x0
	mov r1, #0x3
	add r0, #0x24
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0200284C
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_02002700:
	ldrb r0, [r6, #0x0]
	add r1, r5, #0x0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bl FUN_02002D94
	add r5, r0, #0x0
	ldrb r0, [r4, #0xc]
	add r2, r5, #0x0
	add r3, r5, #0x0
	str r0, [sp, #0x0]
	ldrb r0, [r4, #0xd]
	add r2, #0x80
	add r3, #0x81
	str r0, [sp, #0x4]
	ldrh r0, [r4, #0x14]
	add r1, r5, #0x0
	str r0, [sp, #0x8]
	ldrb r2, [r2, #0x0]
	ldrb r3, [r3, #0x0]
	ldr r0, [r4, #0x4]
	bl FUN_0201974C
	add r5, #0x80
	ldrb r1, [r5, #0x0]
	ldrb r0, [r4, #0xe]
	ldrb r2, [r4, #0xc]
	add sp, #0xc
	add r0, r1, r0
	add r0, r2, r0
	strb r0, [r4, #0xc]
	mov r0, #0x0
	pop {r3-r6, pc}
_02002742:
	bl FUN_02002B3C
	cmp r0, #0x0
	beq _02002756
	add r0, r4, #0x0
	bl FUN_02002A00
	mov r0, #0x0
	add r4, #0x24
	strb r0, [r4, #0x0]
_02002756:
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_0200275C:
	bl FUN_02002B18
	cmp r0, #0x0
	beq _02002780
	add r0, r4, #0x0
	bl FUN_02002A00
	ldrb r1, [r4, #0x12]
	ldr r0, [r4, #0x4]
	bl FUN_02019620
	ldrb r0, [r4, #0xa]
	strb r0, [r4, #0xc]
	ldrb r0, [r4, #0xb]
	strb r0, [r4, #0xd]
	mov r0, #0x0
	add r4, #0x24
	strb r0, [r4, #0x0]
_02002780:
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_02002786:
	bl FUN_02002B18
	cmp r0, #0x0
	beq _020027B0
	add r0, r4, #0x0
	bl FUN_02002A00
	ldrb r0, [r4, #0x9]
	mov r1, #0x1
	bl FUN_02002E4C
	ldrb r1, [r4, #0xf]
	add r1, r1, r0
	add r0, r4, #0x0
	add r0, #0x27
	strb r1, [r0, #0x0]
	ldrb r0, [r4, #0xa]
	strb r0, [r4, #0xc]
	mov r0, #0x4
	add r4, #0x24
	strb r0, [r4, #0x0]
_020027B0:
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_020027B6:
	add r0, #0x27
	ldrb r2, [r0, #0x0]
	cmp r2, #0x0
	beq _02002800
	cmp r2, #0x4
	ldrb r5, [r4, #0x12]
	bge _020027D8
	lsl r3, r5, #0x4
	orr r3, r5
	lsl r3, r3, #0x18
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	lsr r3, r3, #0x18
	bl FUN_0201A8C8
	mov r1, #0x0
	b _020027F2
_020027D8:
	lsl r3, r5, #0x4
	orr r3, r5
	lsl r3, r3, #0x18
	ldr r0, [r4, #0x4]
	mov r1, #0x0
	mov r2, #0x4
	lsr r3, r3, #0x18
	bl FUN_0201A8C8
	add r0, r4, #0x0
	add r0, #0x27
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x4
_020027F2:
	add r0, r4, #0x0
	add r0, #0x27
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x4]
	bl FUN_020191D0
	b _02002806
_02002800:
	mov r0, #0x0
	add r4, #0x24
	strb r0, [r4, #0x0]
_02002806:
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_0200280C:
	mov r0, #0x0
	add r4, #0x24
	strb r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_02002818:
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0200282C
	add r0, r4, #0x0
	add r0, #0x26
	ldrb r0, [r0, #0x0]
	add r4, #0x26
	sub r0, r0, #0x1
	b _02002830
_0200282C:
	mov r0, #0x0
	add r4, #0x24
_02002830:
	add sp, #0xc
	strb r0, [r4, #0x0]
	mov r0, #0x3
	pop {r3-r6, pc}
_02002838:
	mov r0, #0x1
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02002840
FUN_02002840: ; 0x02002840
	ldr r1, _02002848 ; =0x02106FC4
	strh r0, [r1, #0x2]
	bx lr
	nop
_02002848: .word 0x02106FC4

	thumb_func_start FUN_0200284C
FUN_0200284C: ; 0x0200284C
	ldr r1, _02002874 ; =0x02106FC4
	add r0, #0x1c
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1f
	beq _02002862
	ldrb r2, [r0, #0x2]
	mov r1, #0xff
	bic r2, r1
	strb r2, [r0, #0x2]
	bx lr
_02002862:
	ldrb r2, [r0, #0x1]
	mov r1, #0x60
	bic r2, r1
	strb r2, [r0, #0x1]
	ldrb r2, [r0, #0x1]
	mov r1, #0x1f
	bic r2, r1
	strb r2, [r0, #0x1]
	bx lr
	.balign 4
_02002874: .word 0x02106FC4

	thumb_func_start FUN_02002878
FUN_02002878: ; 0x02002878
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	ldr r0, _020029F8 ; =0x02106FC4
	add r4, r5, #0x0
	ldrb r0, [r0, #0x0]
	add r4, #0x1c
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _0200288E
	b _020029F4
_0200288E:
	ldrb r0, [r4, #0x1]
	lsl r1, r0, #0x1b
	lsr r2, r1, #0x1b
	beq _020028AC
	mov r1, #0x1f
	add r2, #0xff
	bic r0, r1
	lsl r1, r2, #0x18
	lsr r2, r1, #0x18
	mov r1, #0x1f
	and r1, r2
	orr r0, r1
	add sp, #0x2c
	strb r0, [r4, #0x1]
	pop {r4-r7, pc}
_020028AC:
	ldr r0, [r5, #0x4]
	bl FUN_0201AB08
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x4]
	bl FUN_0201AB14
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x4]
	bl FUN_0201AB18
	str r0, [sp, #0x28]
	ldr r0, [r5, #0x4]
	bl FUN_0201AB0C
	ldr r1, _020029F8 ; =0x02106FC4
	ldrh r6, [r1, #0x2]
	ldr r1, [sp, #0x28]
	add r7, r1, #0x2
	ldr r1, [sp, #0x24]
	add r2, r6, #0x0
	add r0, r1, r0
	str r0, [sp, #0x1c]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	add r2, #0x12
	mov r12, r2
	ldrb r2, [r4, #0x1]
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x20]
	lsl r2, r2, #0x19
	lsr r3, r2, #0x1e
	ldr r2, _020029FC ; =0x020ECB50
	ldr r0, [r0, #0x0]
	ldrb r2, [r2, r3]
	mov r3, r12
	lsl r2, r2, #0x2
	add r2, r3, r2
	ldr r3, [sp, #0x18]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r0, r0, #0x2
	str r0, [sp, #0x10]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldrb r2, [r4, #0x1]
	add r7, r6, #0x0
	ldr r0, [r5, #0x4]
	lsl r2, r2, #0x19
	lsr r3, r2, #0x1e
	ldr r2, _020029FC ; =0x020ECB50
	add r7, #0x13
	ldrb r2, [r2, r3]
	ldr r3, [sp, #0x10]
	ldr r0, [r0, #0x0]
	lsl r2, r2, #0x2
	add r2, r7, r2
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x28]
	add r7, r6, #0x0
	add r0, r0, #0x3
	str r0, [sp, #0x14]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldrb r2, [r4, #0x1]
	ldr r0, [r5, #0x4]
	add r7, #0x14
	lsl r2, r2, #0x19
	lsr r3, r2, #0x1e
	ldr r2, _020029FC ; =0x020ECB50
	ldr r0, [r0, #0x0]
	ldrb r2, [r2, r3]
	ldr r3, [sp, #0x18]
	ldr r1, [sp, #0x20]
	lsl r2, r2, #0x2
	add r2, r7, r2
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [sp, #0x14]
	add r6, #0x15
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldrb r2, [r4, #0x1]
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x20]
	lsl r2, r2, #0x19
	lsr r3, r2, #0x1e
	ldr r2, _020029FC ; =0x020ECB50
	ldr r0, [r0, #0x0]
	ldrb r2, [r2, r3]
	ldr r3, [sp, #0x10]
	lsl r2, r2, #0x2
	add r2, r6, r2
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x20]
	ldr r0, [r0, #0x0]
	bl FUN_02017CD0
	ldrb r1, [r4, #0x1]
	mov r0, #0x1f
	bic r1, r0
	mov r0, #0x8
	orr r0, r1
	strb r0, [r4, #0x1]
	ldrb r2, [r4, #0x1]
	mov r1, #0x60
	add r0, r2, #0x0
	bic r0, r1
	lsl r1, r2, #0x19
	lsr r1, r1, #0x1e
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x19
	orr r0, r1
	strb r0, [r4, #0x1]
_020029F4:
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4
_020029F8: .word 0x02106FC4
_020029FC: .word 0x020ECB50

	thumb_func_start FUN_02002A00
FUN_02002A00: ; 0x02002A00
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FUN_0201AB08
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x4]
	bl FUN_0201AB14
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4]
	bl FUN_0201AB18
	add r6, r0, #0x0
	ldr r0, [r5, #0x4]
	bl FUN_0201AB0C
	ldr r1, _02002A90 ; =0x02106FC4
	add r7, r6, #0x2
	ldrh r4, [r1, #0x2]
	ldr r1, [sp, #0x14]
	add r6, r1, r0
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x4]
	add r2, r4, #0x0
	add r2, #0xa
	add r3, r6, #0x1
	lsl r2, r2, #0x10
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x0]
	ldr r1, [sp, #0x10]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x4]
	add r4, #0xb
	add r3, r6, #0x2
	lsl r2, r4, #0x10
	lsl r3, r3, #0x18
	ldr r0, [r0, #0x0]
	ldr r1, [sp, #0x10]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x18
	bl FUN_02018540
	ldr r0, [r5, #0x4]
	ldr r1, [sp, #0x10]
	ldr r0, [r0, #0x0]
	bl FUN_02017CD0
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_02002A90: .word 0x02106FC4

	thumb_func_start FUN_02002A94
FUN_02002A94: ; 0x02002A94
	push {r3, lr}
	ldr r0, _02002ACC ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	bne _02002AB2
	ldr r0, _02002AD0 ; =0x021C48F8
	ldrh r0, [r0, #0x20]
	cmp r0, #0x0
	beq _02002AC6
	ldr r0, _02002AD4 ; =0x02106FC4
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _02002AC6
_02002AB2:
	ldr r0, _02002AD8 ; =0x000005DC
	bl FUN_020054C8
	ldr r1, _02002AD4 ; =0x02106FC4
	mov r0, #0x80
	ldrb r2, [r1, #0x0]
	orr r0, r2
	strb r0, [r1, #0x0]
	mov r0, #0x1
	pop {r3, pc}
_02002AC6:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02002ACC: .word 0x021C48B8
_02002AD0: .word 0x021C48F8
_02002AD4: .word 0x02106FC4
_02002AD8: .word 0x000005DC

	thumb_func_start FUN_02002ADC
FUN_02002ADC: ; 0x02002ADC
	push {r4, lr}
	add r2, r0, #0x0
	add r2, #0x1c
	ldrb r1, [r2, #0x2]
	add r4, r1, #0x0
	cmp r4, #0x64
	bne _02002AEE
	mov r0, #0x1
	pop {r4, pc}
_02002AEE:
	mov r3, #0xff
	bic r1, r3
	add r3, r4, #0x1
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	orr r1, r3
	strb r1, [r2, #0x2]
	ldr r1, _02002B14 ; =0x02106FC4
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	beq _02002B10
	bl FUN_02002A94
	pop {r4, pc}
_02002B10:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02002B14: .word 0x02106FC4

	thumb_func_start FUN_02002B18
FUN_02002B18: ; 0x02002B18
	push {r4, lr}
	ldr r1, _02002B38 ; =0x02106FC4
	add r4, r0, #0x0
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1f
	beq _02002B2C
	bl FUN_02002ADC
	pop {r4, pc}
_02002B2C:
	bl FUN_02002878
	add r0, r4, #0x0
	bl FUN_02002A94
	pop {r4, pc}
	.balign 4
_02002B38: .word 0x02106FC4

	thumb_func_start FUN_02002B3C
FUN_02002B3C: ; 0x02002B3C
	push {r3, lr}
	ldr r1, _02002B5C ; =0x02106FC4
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1d
	lsr r1, r1, #0x1f
	beq _02002B52
	bl FUN_02002ADC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
_02002B52:
	bl FUN_02002A94
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4
_02002B5C: .word 0x02106FC4

	thumb_func_start FUN_02002B60
FUN_02002B60: ; 0x02002B60
	ldr r2, _02002B78 ; =0x02106FC4
	mov r1, #0x1
	ldrb r3, [r2, #0x0]
	lsl r0, r0, #0x18
	bic r3, r1
	lsr r1, r0, #0x18
	mov r0, #0x1
	and r0, r1
	orr r0, r3
	strb r0, [r2, #0x0]
	bx lr
	nop
_02002B78: .word 0x02106FC4

	thumb_func_start FUN_02002B7C
FUN_02002B7C: ; 0x02002B7C
	push {r3-r4}
	ldr r1, _02002BB4 ; =0x02106FC4
	mov r3, #0x4
	ldrb r2, [r1, #0x0]
	mov r4, #0x1
	bic r2, r3
	add r3, r0, #0x0
	and r3, r4
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	lsl r3, r3, #0x1f
	lsr r3, r3, #0x1d
	orr r2, r3
	asr r0, r0, #0x1
	and r0, r4
	strb r2, [r1, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1f
	ldrb r2, [r1, #0x0]
	mov r3, #0x20
	lsr r0, r0, #0x1a
	bic r2, r3
	orr r0, r2
	strb r0, [r1, #0x0]
	pop {r3-r4}
	bx lr
	nop
_02002BB4: .word 0x02106FC4

	thumb_func_start FUN_02002BB8
FUN_02002BB8: ; 0x02002BB8
	ldr r2, _02002BD0 ; =0x02106FC4
	lsl r0, r0, #0x18
	ldrb r3, [r2, #0x0]
	lsr r0, r0, #0x18
	mov r1, #0x10
	lsl r0, r0, #0x1f
	bic r3, r1
	lsr r0, r0, #0x1b
	orr r0, r3
	strb r0, [r2, #0x0]
	bx lr
	nop
_02002BD0: .word 0x02106FC4

	thumb_func_start FUN_02002BD4
FUN_02002BD4: ; 0x02002BD4
	ldr r0, _02002BE0 ; =0x02106FC4
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr
	nop
_02002BE0: .word 0x02106FC4

	thumb_func_start FUN_02002BE4
FUN_02002BE4: ; 0x02002BE4
	ldr r1, _02002BF0 ; =0x02106FC4
	mov r0, #0x40
	ldrb r2, [r1, #0x0]
	bic r2, r0
	strb r2, [r1, #0x0]
	bx lr
	.balign 4
_02002BF0: .word 0x02106FC4

	thumb_func_start FUN_02002BF4
FUN_02002BF4: ; 0x02002BF4
	ldr r0, _02002C00 ; =0x02106FC4
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr
	nop
_02002C00: .word 0x02106FC4

	thumb_func_start FUN_02002C04
FUN_02002C04: ; 0x02002C04
	ldr r1, _02002C10 ; =0x02106FC4
	mov r0, #0x80
	ldrb r2, [r1, #0x0]
	bic r2, r0
	strb r2, [r1, #0x0]
	bx lr
	.balign 4
_02002C10: .word 0x02106FC4

	thumb_func_start FUN_02002C14
FUN_02002C14: ; 0x02002C14
	push {r4, lr}
	ldr r0, _02002C44 ; =0x02106FCC
	ldr r4, _02002C48 ; =0x02106FC8
	mov r1, #0x0
	str r0, [r4, #0x0]
	add r2, r1, #0x0
	add r0, r1, #0x0
_02002C22:
	ldr r3, [r4, #0x0]
	add r1, r1, #0x1
	add r3, r3, r2
	add r3, #0x84
	str r0, [r3, #0x0]
	ldr r3, [r4, #0x0]
	add r3, r3, r2
	add r3, #0x94
	add r2, r2, #0x4
	str r0, [r3, #0x0]
	cmp r1, #0x4
	blo _02002C22
	ldr r0, _02002C4C ; =0x020ECB64
	bl FUN_0201BCBC
	pop {r4, pc}
	nop
_02002C44: .word 0x02106FCC
_02002C48: .word 0x02106FC8
_02002C4C: .word 0x020ECB64

	thumb_func_start FUN_02002C50
FUN_02002C50: ; 0x02002C50
	push {r3-r4, lr}
	sub sp, #0x4
	str r1, [sp, #0x0]
	lsl r4, r0, #0x2
	ldr r1, _02002C78 ; =0x020ECB54
	ldr r3, _02002C7C ; =0x020ECB56
	ldrh r1, [r1, r4]
	ldrh r3, [r3, r4]
	mov r0, #0xe
	mov r2, #0x1
	bl FUN_02021590
	ldr r1, _02002C80 ; =0x02106FC8
	ldr r1, [r1, #0x0]
	add r1, r1, r4
	add r1, #0x94
	str r0, [r1, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}
	nop
_02002C78: .word 0x020ECB54
_02002C7C: .word 0x020ECB56
_02002C80: .word 0x02106FC8

	thumb_func_start FUN_02002C84
FUN_02002C84: ; 0x02002C84
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x4
	blt _02002C92
	bl ErrorHandling
_02002C92:
	ldr r0, _02002CBC ; =0x02106FC8
	lsl r4, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002CA6
	bl ErrorHandling
_02002CA6:
	ldr r0, _02002CBC ; =0x02106FC8
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r2, r5, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020215E0
	pop {r3-r5, pc}
	nop
_02002CBC: .word 0x02106FC8

	thumb_func_start FUN_02002CC0
FUN_02002CC0: ; 0x02002CC0
	push {r4, lr}
	add r4, r0, #0x0
	cmp r4, #0x4
	blt _02002CCC
	bl ErrorHandling
_02002CCC:
	ldr r0, _02002CF4 ; =0x02106FC8
	lsl r4, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002CE0
	bl ErrorHandling
_02002CE0:
	ldr r0, _02002CF4 ; =0x02106FC8
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	mov r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020215E0
	pop {r4, pc}
	.balign 4
_02002CF4: .word 0x02106FC8

	thumb_func_start FUN_02002CF8
FUN_02002CF8: ; 0x02002CF8
	push {r3-r7, lr}
	add r4, r0, #0x0
	cmp r4, #0x4
	blt _02002D04
	bl ErrorHandling
_02002D04:
	ldr r0, _02002D8C ; =0x02106FC8
	lsl r6, r4, #0x2
	ldr r7, [r0, #0x0]
	add r0, r7, r6
	add r0, #0x84
	ldr r0, [r0, #0x0]
	mov r12, r0
	cmp r0, #0x0
	beq _02002D68
	ldr r2, _02002D90 ; =0x020ECB54
	mov r1, #0x0
	ldrh r0, [r2, r6]
	add r3, r7, #0x0
_02002D1E:
	cmp r1, r4
	beq _02002D3E
	ldrh r5, [r2, #0x0]
	cmp r5, r0
	bne _02002D3E
	add r5, r3, #0x0
	add r5, #0x94
	ldr r5, [r5, #0x0]
	cmp r5, #0x0
	beq _02002D3E
	lsl r0, r1, #0x2
	add r2, r7, r0
	add r2, #0x84
	mov r0, r12
	str r0, [r2, #0x0]
	b _02002D48
_02002D3E:
	add r1, r1, #0x1
	add r2, r2, #0x4
	add r3, r3, #0x4
	cmp r1, #0x4
	blo _02002D1E
_02002D48:
	cmp r1, #0x4
	bne _02002D68
	ldr r0, _02002D8C ; =0x02106FC8
	lsl r5, r4, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0x84
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _02002D8C ; =0x02106FC8
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r5
	add r0, #0x84
	str r1, [r0, #0x0]
_02002D68:
	ldr r0, _02002D8C ; =0x02106FC8
	ldr r0, [r0, #0x0]
	add r0, r0, r6
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02002D88
	bl FUN_020215C8
	ldr r0, _02002D8C ; =0x02106FC8
	mov r2, #0x0
	ldr r1, [r0, #0x0]
	lsl r0, r4, #0x2
	add r0, r1, r0
	add r0, #0x94
	str r2, [r0, #0x0]
_02002D88:
	pop {r3-r7, pc}
	nop
_02002D8C: .word 0x02106FC8
_02002D90: .word 0x020ECB54

	thumb_func_start FUN_02002D94
FUN_02002D94: ; 0x02002D94
	push {r3, lr}
	ldr r2, _02002DAC ; =0x02106FC8
	lsl r0, r0, #0x2
	ldr r2, [r2, #0x0]
	add r0, r2, r0
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_02021750
	ldr r0, _02002DAC ; =0x02106FC8
	ldr r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_02002DAC: .word 0x02106FC8

	thumb_func_start FUN_02002DB0
FUN_02002DB0: ; 0x02002DB0
	push {r4, lr}
	add r3, r1, #0x0
	add r3, #0x1c
	ldrb r2, [r3, #0x1]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x1f
	bne _02002DD8
	ldrb r2, [r3, #0x0]
	mov r4, #0xf
	lsl r0, r0, #0x18
	bic r2, r4
	lsr r4, r0, #0x18
	mov r0, #0xf
	and r0, r4
	orr r0, r2
	strb r0, [r3, #0x0]
	ldrb r2, [r3, #0x1]
	mov r0, #0x80
	orr r0, r2
	strb r0, [r3, #0x1]
_02002DD8:
	add r0, r1, #0x0
	bl FUN_020023C0
	pop {r4, pc}

	thumb_func_start FUN_02002DE0
FUN_02002DE0: ; 0x02002DE0
	push {r4-r6, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002E10 ; =0x02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002DFA
	bl ErrorHandling
_02002DFA:
	ldr r0, _02002E10 ; =0x02106FC8
	add r1, r5, #0x0
	ldr r0, [r0, #0x0]
	add r2, r6, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020218D8
	pop {r4-r6, pc}
	nop
_02002E10: .word 0x02106FC8

	thumb_func_start FUN_02002E14
FUN_02002E14: ; 0x02002E14
	push {r4-r6, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002E48 ; =0x02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002E2E
	bl ErrorHandling
_02002E2E:
	add r0, r5, #0x0
	bl FUN_02021F2C
	add r1, r0, #0x0
	ldr r0, _02002E48 ; =0x02106FC8
	add r2, r6, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_020218D8
	pop {r4-r6, pc}
	.balign 4
_02002E48: .word 0x02106FC8

	thumb_func_start FUN_02002E4C
FUN_02002E4C: ; 0x02002E4C
	mov r2, #0x0
	cmp r1, #0x7
	bhi _02002EAC
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02002E5E: ; jump table (using 16-bit offset)
	.short _02002E6E - _02002E5E - 2; case 0
	.short _02002E76 - _02002E5E - 2; case 1
	.short _02002E7E - _02002E5E - 2; case 2
	.short _02002E86 - _02002E5E - 2; case 3
	.short _02002E8E - _02002E5E - 2; case 4
	.short _02002E96 - _02002E5E - 2; case 5
	.short _02002E9E - _02002E5E - 2; case 6
	.short _02002EA6 - _02002E5E - 2; case 7
_02002E6E:
	lsl r1, r0, #0x3
	ldr r0, _02002EB0 ; =0x020ECB64
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E76:
	lsl r1, r0, #0x3
	ldr r0, _02002EB4 ; =0x020ECB65
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E7E:
	lsl r1, r0, #0x3
	ldr r0, _02002EB8 ; =0x020ECB66
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E86:
	lsl r1, r0, #0x3
	ldr r0, _02002EBC ; =0x020ECB67
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E8E:
	lsl r1, r0, #0x3
	ldr r0, _02002EC0 ; =0x020ECB68
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E96:
	lsl r1, r0, #0x3
	ldr r0, _02002EC4 ; =0x020ECB69
	ldrb r2, [r0, r1]
	b _02002EAC
_02002E9E:
	lsl r1, r0, #0x3
	ldr r0, _02002EC8 ; =0x020ECB6A
	ldrb r2, [r0, r1]
	b _02002EAC
_02002EA6:
	lsl r1, r0, #0x3
	ldr r0, _02002ECC ; =0x020ECB6B
	ldrb r2, [r0, r1]
_02002EAC:
	add r0, r2, #0x0
	bx lr
	.balign 4
_02002EB0: .word 0x020ECB64
_02002EB4: .word 0x020ECB65
_02002EB8: .word 0x020ECB66
_02002EBC: .word 0x020ECB67
_02002EC0: .word 0x020ECB68
_02002EC4: .word 0x020ECB69
_02002EC8: .word 0x020ECB6A
_02002ECC: .word 0x020ECB6B

	thumb_func_start FUN_02002ED0
FUN_02002ED0: ; 0x02002ED0
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	add r3, r1, #0x0
	str r2, [sp, #0x4]
	mov r0, #0xe
	mov r1, #0x6
	add r2, r4, #0x0
	bl FUN_02006930
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02002EEC
FUN_02002EEC: ; 0x02002EEC
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0x20
	str r0, [sp, #0x0]
	add r3, r1, #0x0
	str r2, [sp, #0x4]
	mov r0, #0xe
	mov r1, #0x7
	add r2, r4, #0x0
	bl FUN_02006930
	add sp, #0x8
	pop {r4, pc}

	thumb_func_start FUN_02002F08
FUN_02002F08: ; 0x02002F08
	push {r4-r6, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002F3C ; =0x02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002F22
	bl ErrorHandling
_02002F22:
	add r0, r5, #0x0
	bl FUN_02021F2C
	add r1, r0, #0x0
	ldr r0, _02002F3C ; =0x02106FC8
	add r2, r6, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_02021934
	pop {r4-r6, pc}
	.balign 4
_02002F3C: .word 0x02106FC8

	thumb_func_start FUN_02002F40
FUN_02002F40: ; 0x02002F40
	push {r4, lr}
	add r4, r3, #0x0
	bl FUN_02002E14
	cmp r0, r4
	bhs _02002F52
	sub r0, r4, r0
	lsr r0, r0, #0x1
	pop {r4, pc}
_02002F52:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02002F58
FUN_02002F58: ; 0x02002F58
	push {r3-r7, lr}
	ldrh r2, [r0, #0x0]
	ldr r1, _02002F8C ; =0x0000FFFF
	mov r5, #0x1
	cmp r2, r1
	beq _02002F88
	mov r6, #0xe
	lsl r6, r6, #0xc
	add r7, r1, #0x0
	sub r4, r1, #0x1
_02002F6C:
	cmp r2, r4
	bne _02002F76
	bl FUN_0201B8B8
	b _02002F82
_02002F76:
	cmp r2, r6
	bne _02002F80
	add r5, r5, #0x1
	add r0, r0, #0x2
	b _02002F82
_02002F80:
	add r0, r0, #0x2
_02002F82:
	ldrh r2, [r0, #0x0]
	cmp r2, r7
	bne _02002F6C
_02002F88:
	add r0, r5, #0x0
	pop {r3-r7, pc}
	.balign 4
_02002F8C: .word 0x0000FFFF

	thumb_func_start FUN_02002F90
FUN_02002F90: ; 0x02002F90
	push {r3, lr}
	bl FUN_02021F2C
	bl FUN_02002F58
	pop {r3, pc}

	thumb_func_start FUN_02002F9C
FUN_02002F9C: ; 0x02002F9C
	push {r3-r5, lr}
	lsl r4, r0, #0x2
	ldr r0, _02002FCC ; =0x02106FC8
	add r5, r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02002FB4
	bl ErrorHandling
_02002FB4:
	add r0, r5, #0x0
	bl FUN_02021F2C
	add r1, r0, #0x0
	ldr r0, _02002FCC ; =0x02106FC8
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FUN_0202199C
	pop {r3-r5, pc}
	.balign 4
_02002FCC: .word 0x02106FC8

	thumb_func_start FUN_02002FD0
FUN_02002FD0: ; 0x02002FD0
	push {r4, lr}
	mov r1, #0x12
	lsl r1, r1, #0x4
	bl FUN_02016998
	mov r2, #0x12
	mov r1, #0x0
	lsl r2, r2, #0x4
	add r4, r0, #0x0
	blx MI_CpuFill8
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02002FEC
FUN_02002FEC: ; 0x02002FEC
	ldr r3, _02002FF0 ; =FUN_02016A18
	bx r3
	.balign 4
_02002FF0: .word FUN_02016A18 

	thumb_func_start FUN_02002FF4
FUN_02002FF4: ; 0x02002FF4
	push {r3-r4}
	mov r4, #0x14
	mul r4, r1
	str r2, [r0, r4]
	add r1, r0, r4
	ldr r0, [sp, #0x8]
	str r3, [r1, #0x4]
	str r0, [r1, #0x8]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02003008
FUN_02003008: ; 0x02003008
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	str r3, [sp, #0x4]
	add r0, r3, #0x0
	add r1, r4, #0x0
	bl FUN_02016998
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	add r1, r4, #0x0
	bl FUN_02016998
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	str r4, [sp, #0x0]
	bl FUN_02002FF4
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003038
FUN_02003038: ; 0x02003038
	push {r3-r5, lr}
	add r4, r0, #0x0
	mov r0, #0x14
	add r5, r1, #0x0
	mul r5, r0
	ldr r0, [r4, r5]
	bl FUN_02016A18
	add r0, r4, r5
	ldr r0, [r0, #0x4]
	bl FUN_02016A18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02003054
FUN_02003054: ; 0x02003054
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, sp, #0x8
	ldrh r7, [r0, #0x10]
	add r6, r2, #0x0
	mov r0, #0x14
	mul r6, r0
	str r1, [sp, #0x0]
	add r0, r1, #0x0
	ldr r1, [r5, r6]
	lsl r4, r3, #0x1
	add r1, r1, r4
	add r2, r7, #0x0
	blx MIi_CpuCopy16
	add r1, r5, r6
	ldr r1, [r1, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r1, r4
	add r2, r7, #0x0
	blx MIi_CpuCopy16
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02003084
FUN_02003084: ; 0x02003084
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, sp, #0x4
	ldr r4, [sp, #0x1c]
	bl FUN_02006C08
	add r6, r0, #0x0
	bne _0200309E
	bl ErrorHandling
_0200309E:
	cmp r4, #0x0
	bne _020030A6
	ldr r0, [sp, #0x4]
	ldr r4, [r0, #0x8]
_020030A6:
	add r0, sp, #0x8
	ldrh r0, [r0, #0x18]
	ldr r2, [sp, #0x18]
	mov r1, #0x14
	mul r1, r2
	add r1, r5, r1
	lsl r0, r0, #0x1
	ldr r1, [r1, #0x8]
	add r0, r4, r0
	cmp r0, r1
	bls _020030C0
	bl ErrorHandling
_020030C0:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r3, sp, #0x8
	ldr r2, [r1, #0xc]
	ldrh r1, [r3, #0x1c]
	ldrh r3, [r3, #0x18]
	add r0, r5, #0x0
	lsl r1, r1, #0x1
	add r1, r2, r1
	ldr r2, [sp, #0x18]
	bl FUN_02003054
	add r0, r6, #0x0
	bl FUN_02016A18
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020030E8
FUN_020030E8: ; 0x020030E8
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #0x4]
	add r4, sp, #0x8
	ldrh r4, [r4, #0x18]
	str r4, [sp, #0x8]
	mov r4, #0x0
	str r4, [sp, #0xc]
	bl FUN_02003084
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003108
FUN_02003108: ; 0x02003108
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x14
	add r6, r0, #0x0
	mul r1, r4
	add r5, r2, #0x0
	add r1, r6, r1
	add r7, r3, #0x0
	lsl r0, r5, #0x1
	ldr r1, [r1, #0x8]
	add r0, r7, r0
	cmp r0, r1
	bls _02003126
	bl ErrorHandling
_02003126:
	cmp r4, #0x3
	bhi _0200315E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02003136: ; jump table (using 16-bit offset)
	.short _0200313E - _02003136 - 2; case 0
	.short _02003146 - _02003136 - 2; case 1
	.short _0200314E - _02003136 - 2; case 2
	.short _02003156 - _02003136 - 2; case 3
_0200313E:
	bl FUN_020222E8
	add r1, r0, #0x0
	b _02003164
_02003146:
	bl FUN_020222F8
	add r1, r0, #0x0
	b _02003164
_0200314E:
	bl FUN_02022308
	add r1, r0, #0x0
	b _02003164
_02003156:
	bl FUN_02022310
	add r1, r0, #0x0
	b _02003164
_0200315E:
	bl ErrorHandling
	pop {r3-r7, pc}
_02003164:
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	lsl r2, r5, #0x1
	str r0, [sp, #0x0]
	add r1, r1, r2
	add r0, r6, #0x0
	add r2, r4, #0x0
	add r3, r5, #0x0
	bl FUN_02003054
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200317C
FUN_0200317C: ; 0x0200317C
	push {r3-r5, lr}
	add r4, r2, #0x0
	add r5, r3, #0x0
	add r2, sp, #0x0
	add r3, r4, #0x0
	bl FUN_02006C08
	add r4, r0, #0x0
	bne _02003192
	bl ErrorHandling
_02003192:
	cmp r5, #0x0
	bne _0200319A
	ldr r0, [sp, #0x0]
	ldr r5, [r0, #0x8]
_0200319A:
	ldr r0, [sp, #0x0]
	add r2, r5, #0x0
	ldr r1, [r0, #0xc]
	add r0, sp, #0x0
	ldrh r0, [r0, #0x10]
	lsl r0, r0, #0x1
	add r0, r1, r0
	ldr r1, [sp, #0x14]
	blx MIi_CpuCopy16
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020031B8
FUN_020031B8: ; 0x020031B8
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, sp, #0x10
	add r5, r0, #0x0
	add r0, r1, #0x0
	ldrh r1, [r4, #0x14]
	add r6, r3, #0x0
	str r1, [sp, #0x0]
	ldrh r1, [r4, #0x10]
	lsl r4, r2, #0x1
	ldr r2, [sp, #0x0]
	lsl r7, r1, #0x1
	mov r1, #0x14
	mul r6, r1
	mul r1, r0
	ldr r0, [r5, r1]
	str r1, [sp, #0x4]
	ldr r1, [r5, r6]
	add r0, r0, r4
	add r1, r1, r7
	blx MIi_CpuCopy16
	ldr r0, [sp, #0x4]
	add r1, r5, r6
	ldr r0, [r5, r0]
	ldr r1, [r1, #0x4]
	ldr r2, [sp, #0x0]
	add r0, r0, r4
	add r1, r1, r7
	blx MIi_CpuCopy16
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020031FC
FUN_020031FC: ; 0x020031FC
	mov r2, #0x14
	mul r2, r1
	ldr r0, [r0, r2]
	bx lr

	thumb_func_start FUN_02003204
FUN_02003204: ; 0x02003204
	mov r2, #0x14
	mul r2, r1
	add r0, r0, r2
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_02003210
FUN_02003210: ; 0x02003210
	push {r0-r3}
	push {r3-r7, lr}
	sub sp, #0x10
	str r3, [sp, #0x8]
	add r5, r0, #0x0
	ldr r0, [sp, #0x38]
	mov r6, #0x0
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	add r7, r1, #0x0
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x40]
	add r4, r6, #0x0
	str r0, [sp, #0x40]
	add r0, sp, #0x28
	ldrh r0, [r0, #0x8]
	str r0, [sp, #0xc]
_02003232:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02003314
	cmp r0, #0x1
	bne _020032A6
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldrh r0, [r5, r0]
	add r1, r4, #0x0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bl FUN_02003314
	cmp r0, #0x0
	bne _020032A6
	mov r0, #0x14
	add r6, r4, #0x0
	mul r6, r0
	add r0, r4, #0x0
	add r1, r5, r6
	add r2, sp, #0x30
	bl FUN_02003368
	ldr r0, [sp, #0x3c]
	add r1, sp, #0x28
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x40]
	str r0, [sp, #0x4]
	add r0, r5, r6
	ldrh r1, [r1, #0x8]
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0x38]
	add r0, #0xc
	bl FUN_020033A4
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02003328
	cmp r4, #0x4
	blo _02003294
	mov r2, #0x1
	add r0, r5, #0x0
	add r1, r4, #0x0
	lsl r2, r2, #0x8
	bl FUN_0200359C
	b _0200329E
_02003294:
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x10
	bl FUN_0200359C
_0200329E:
	ldr r1, [sp, #0xc]
	add r0, sp, #0x28
	strh r1, [r0, #0x8]
	mov r6, #0x1
_020032A6:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xe
	blo _02003232
	cmp r6, #0x1
	bne _02003300
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldrh r2, [r5, r0]
	ldr r1, _0200330C ; =0xFFFF0003
	and r1, r2
	lsl r2, r2, #0x10
	lsr r2, r2, #0x12
	orr r2, r7
	lsl r2, r2, #0x12
	lsr r2, r2, #0x10
	orr r1, r2
	strh r1, [r5, r0]
	add r1, r0, #0x2
	ldrh r1, [r5, r1]
	lsl r1, r1, #0x11
	lsr r1, r1, #0x1f
	bne _02003300
	add r1, r0, #0x2
	ldrh r2, [r5, r1]
	mov r1, #0x1
	lsl r1, r1, #0xe
	orr r2, r1
	add r1, r0, #0x2
	strh r2, [r5, r1]
	ldrh r2, [r5, r0]
	mov r1, #0x3
	bic r2, r1
	mov r1, #0x1
	orr r1, r2
	strh r1, [r5, r0]
	mov r2, #0x0
	add r0, r0, #0x4
	strb r2, [r5, r0]
	ldr r0, _02003310 ; =FUN_02003464
	add r1, r5, #0x0
	sub r2, r2, #0x2
	bl FUN_0200CA44
_02003300:
	add r0, r6, #0x0
	add sp, #0x10
	pop {r3-r7}
	pop {r3}
	add sp, #0x10
	bx r3
	.balign 4
_0200330C: .word 0xFFFF0003
_02003310: .word FUN_02003464 

	thumb_func_start FUN_02003314
FUN_02003314: ; 0x02003314
	mov r3, #0x1
	add r2, r3, #0x0
	lsl r2, r1
	tst r0, r2
	bne _02003320
	mov r3, #0x0
_02003320:
	lsl r0, r3, #0x18
	lsr r0, r0, #0x18
	bx lr
	.balign 4

	thumb_func_start FUN_02003328
FUN_02003328: ; 0x02003328
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, _02003360 ; =0x0000011A
	add r4, r1, #0x0
	ldrh r0, [r5, r0]
	lsl r0, r0, #0x12
	lsr r0, r0, #0x12
	bl FUN_02003314
	cmp r0, #0x1
	beq _0200335E
	ldr r3, _02003360 ; =0x0000011A
	ldr r1, _02003364 ; =0xFFFFC000
	ldrh r2, [r5, r3]
	add r0, r2, #0x0
	lsl r2, r2, #0x12
	lsr r6, r2, #0x12
	mov r2, #0x1
	lsl r2, r4
	orr r2, r6
	lsl r2, r2, #0x10
	and r0, r1
	lsr r2, r2, #0x10
	lsr r1, r1, #0x12
	and r1, r2
	orr r0, r1
	strh r0, [r5, r3]
_0200335E:
	pop {r4-r6, pc}
	.balign 4
_02003360: .word 0x0000011A
_02003364: .word 0xFFFFC000

	thumb_func_start FUN_02003368
FUN_02003368: ; 0x02003368
	push {r4-r5}
	cmp r0, #0x4
	ldr r0, [r1, #0x8]
	bge _02003374
	lsl r0, r0, #0x13
	b _02003378
_02003374:
	lsr r0, r0, #0x9
	lsl r0, r0, #0x18
_02003378:
	mov r4, #0x0
	lsr r0, r0, #0x18
	add r5, r4, #0x0
	cmp r0, #0x0
	bls _02003398
	mov r3, #0x1
_02003384:
	add r1, r3, #0x0
	lsl r1, r5
	add r1, r4, r1
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	add r1, r5, #0x1
	lsl r1, r1, #0x18
	lsr r5, r1, #0x18
	cmp r5, r0
	blo _02003384
_02003398:
	ldrh r0, [r2, #0x0]
	and r0, r4
	strh r0, [r2, #0x0]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_020033A4
FUN_020033A4: ; 0x020033A4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r3, #0x0
	cmp r2, #0x0
	bge _020033D4
	add r0, r2, #0x0
	blx abs
	add r0, r0, #0x2
	ldrh r1, [r5, #0x6]
	mov r2, #0xf
	lsl r0, r0, #0x10
	bic r1, r2
	lsr r2, r0, #0x10
	mov r0, #0xf
	and r0, r2
	orr r0, r1
	strh r0, [r5, #0x6]
	ldrh r1, [r5, #0x2]
	mov r0, #0x3f
	bic r1, r0
	strh r1, [r5, #0x2]
	b _020033F2
_020033D4:
	ldrh r1, [r5, #0x6]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x2
	orr r0, r1
	strh r0, [r5, #0x6]
	ldrh r0, [r5, #0x2]
	mov r1, #0x3f
	bic r0, r1
	lsl r1, r2, #0x10
	lsr r2, r1, #0x10
	mov r1, #0x3f
	and r1, r2
	orr r0, r1
	strh r0, [r5, #0x2]
_020033F2:
	strh r6, [r5, #0x0]
	ldrh r1, [r5, #0x2]
	ldr r0, _02003454 ; =0xFFFFF83F
	add r3, sp, #0x0
	and r1, r0
	lsl r0, r4, #0x1b
	lsr r0, r0, #0x15
	orr r0, r1
	strh r0, [r5, #0x2]
	ldrh r1, [r5, #0x2]
	ldr r0, _02003458 ; =0xFFFF07FF
	add r2, r1, #0x0
	ldrb r1, [r3, #0x10]
	and r2, r0
	lsl r0, r1, #0x1b
	lsr r0, r0, #0x10
	orr r0, r2
	strh r0, [r5, #0x2]
	ldrh r0, [r5, #0x4]
	ldr r2, _0200345C ; =0xFFFF8000
	ldrh r6, [r3, #0x14]
	lsr r3, r2, #0x11
	and r0, r2
	and r3, r6
	orr r0, r3
	strh r0, [r5, #0x4]
	ldrh r3, [r5, #0x6]
	ldr r0, _02003460 ; =0xFFFFFC0F
	and r0, r3
	ldrh r3, [r5, #0x2]
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x1a
	lsl r3, r3, #0x1a
	lsr r3, r3, #0x16
	orr r0, r3
	strh r0, [r5, #0x6]
	cmp r4, r1
	ldrh r1, [r5, #0x4]
	bhs _02003448
	sub r0, r2, #0x1
	and r0, r1
	strh r0, [r5, #0x4]
	pop {r4-r6, pc}
_02003448:
	mov r0, #0x2
	lsl r0, r0, #0xe
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r4-r6, pc}
	nop
_02003454: .word 0xFFFFF83F
_02003458: .word 0xFFFF07FF
_0200345C: .word 0xFFFF8000
_02003460: .word 0xFFFFFC0F

	thumb_func_start FUN_02003464
FUN_02003464: ; 0x02003464
	push {r4-r6, lr}
	add r4, r1, #0x0
	mov r1, #0x47
	lsl r1, r1, #0x2
	ldrb r2, [r4, r1]
	add r5, r0, #0x0
	cmp r2, #0x1
	bne _020034A4
	mov r2, #0x0
	strb r2, [r4, r1]
	sub r2, r1, #0x2
	ldrh r3, [r4, r2]
	ldr r2, _020034F4 ; =0xFFFFC000
	add r5, r3, #0x0
	and r5, r2
	sub r3, r1, #0x2
	strh r5, [r4, r3]
	sub r3, r1, #0x4
	ldrh r5, [r4, r3]
	ldr r3, _020034F8 ; =0xFFFF0003
	sub r2, r2, #0x1
	and r5, r3
	sub r3, r1, #0x4
	strh r5, [r4, r3]
	sub r3, r1, #0x2
	ldrh r3, [r4, r3]
	sub r1, r1, #0x2
	and r2, r3
	strh r2, [r4, r1]
	bl FUN_0200CAB4
	pop {r4-r6, pc}
_020034A4:
	sub r0, r1, #0x4
	ldrh r2, [r4, r0]
	lsl r0, r2, #0x1e
	lsr r0, r0, #0x1e
	cmp r0, #0x1
	bne _020034F0
	sub r0, r1, #0x2
	ldrh r0, [r4, r0]
	ldr r3, _020034F4 ; =0xFFFFC000
	lsl r2, r2, #0x10
	lsr r6, r2, #0x12
	lsr r2, r3, #0x12
	and r0, r3
	and r2, r6
	orr r2, r0
	sub r0, r1, #0x2
	strh r2, [r4, r0]
	add r0, r4, #0x0
	bl FUN_02003500
	add r0, r4, #0x0
	bl FUN_02003520
	mov r1, #0x46
	lsl r1, r1, #0x2
	ldrh r0, [r4, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bne _020034F0
	add r0, r1, #0x2
	ldrh r2, [r4, r0]
	ldr r0, _020034FC ; =0xFFFFBFFF
	and r2, r0
	add r0, r1, #0x2
	strh r2, [r4, r0]
	add r0, r5, #0x0
	bl FUN_0200CAB4
_020034F0:
	pop {r4-r6, pc}
	nop
_020034F4: .word 0xFFFFC000
_020034F8: .word 0xFFFF0003
_020034FC: .word 0xFFFFBFFF

	thumb_func_start FUN_02003500
FUN_02003500: ; 0x02003500
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r4, #0x0
	mov r6, #0x10
_02003508:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02003540
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x4
	blo _02003508
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02003520
FUN_02003520: ; 0x02003520
	push {r4-r6, lr}
	mov r4, #0x4
	add r6, r4, #0x0
	add r5, r0, #0x0
	add r6, #0xfc
_0200352A:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02003540
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0xe
	blo _0200352A
	pop {r4-r6, pc}

	thumb_func_start FUN_02003540
FUN_02003540: ; 0x02003540
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x46
	lsl r0, r0, #0x2
	ldrh r0, [r5, r0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bl FUN_02003314
	cmp r0, #0x0
	beq _02003594
	mov r0, #0x14
	mul r0, r4
	add r2, r5, r0
	ldrh r0, [r2, #0x12]
	ldrh r3, [r2, #0xe]
	lsl r1, r0, #0x16
	lsl r3, r3, #0x1a
	lsr r1, r1, #0x1a
	lsr r3, r3, #0x1a
	cmp r1, r3
	bhs _02003584
	ldr r3, _02003598 ; =0xFFFFFC0F
	and r3, r0
	add r0, r1, #0x1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x16
	orr r0, r3
	strh r0, [r2, #0x12]
	pop {r4-r6, pc}
_02003584:
	ldr r1, _02003598 ; =0xFFFFFC0F
	and r0, r1
	strh r0, [r2, #0x12]
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0200359C
_02003594:
	pop {r4-r6, pc}
	nop
_02003598: .word 0xFFFFFC0F

	thumb_func_start FUN_0200359C
FUN_0200359C: ; 0x0200359C
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x4]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	mov r1, #0x14
	mul r1, r0
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	add r5, r0, r1
	add r0, r5, #0x0
	str r0, [sp, #0x8]
	add r0, #0xc
	add r7, r2, #0x0
	add r4, r6, #0x0
	str r0, [sp, #0x8]
_020035BC:
	ldrh r0, [r5, #0xc]
	lsl r1, r6, #0x10
	lsr r1, r1, #0x10
	bl FUN_02003314
	cmp r0, #0x0
	beq _020035DC
	ldr r0, [r5, #0x0]
	lsl r1, r4, #0x1
	ldr r2, [r5, #0x4]
	add r0, r0, r1
	add r1, r2, r1
	ldr r2, [sp, #0x8]
	add r3, r7, #0x0
	bl FUN_020035F8
_020035DC:
	add r6, r6, #0x1
	add r4, r4, r7
	cmp r6, #0x10
	blo _020035BC
	ldr r1, [sp, #0x4]
	add r5, #0xc
	lsl r1, r1, #0x18
	ldr r0, [sp, #0x0]
	lsr r1, r1, #0x18
	add r2, r5, #0x0
	bl FUN_02003684
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_020035F8
FUN_020035F8: ; 0x020035F8
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x4]
	mov r0, #0x0
	add r6, r1, #0x0
	mov r12, r0
	str r2, [sp, #0x0]
	mov lr, r3
	add r0, r3, #0x0
	beq _02003680
_0200360C:
	ldr r0, [sp, #0x4]
	mov r1, #0x1f
	ldrh r0, [r0, #0x0]
	asr r2, r0, #0x5
	add r5, r2, #0x0
	and r5, r1
	ldr r1, [sp, #0x0]
	asr r4, r0, #0xa
	ldrh r1, [r1, #0x4]
	lsl r1, r1, #0x11
	lsr r3, r1, #0x11
	ldr r1, [sp, #0x0]
	ldrh r1, [r1, #0x2]
	lsl r1, r1, #0x15
	lsr r2, r1, #0x1b
	mov r1, #0x1f
	and r1, r4
	mov r4, #0x1f
	and r0, r4
	and r4, r3
	sub r4, r4, r0
	mul r4, r2
	asr r4, r4, #0x4
	add r0, r0, r4
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	asr r4, r3, #0xa
	mov r0, #0x1f
	and r0, r4
	sub r0, r0, r1
	mul r0, r2
	asr r0, r0, #0x4
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	asr r3, r3, #0x5
	mov r1, #0x1f
	and r1, r3
	sub r1, r1, r5
	mul r1, r2
	asr r1, r1, #0x4
	add r1, r5, r1
	lsl r1, r1, #0x18
	lsl r0, r0, #0xa
	lsr r1, r1, #0x13
	orr r0, r1
	orr r0, r7
	strh r0, [r6, #0x0]
	ldr r0, [sp, #0x4]
	add r6, r6, #0x2
	add r0, r0, #0x2
	str r0, [sp, #0x4]
	mov r0, r12
	add r1, r0, #0x1
	mov r0, lr
	mov r12, r1
	cmp r1, r0
	blo _0200360C
_02003680:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003684
FUN_02003684: ; 0x02003684
	push {r4-r5}
	ldrh r4, [r2, #0x2]
	lsl r3, r4, #0x10
	lsl r4, r4, #0x15
	lsr r3, r3, #0x1b
	lsr r4, r4, #0x1b
	cmp r4, r3
	bne _020036BE
	mov r3, #0x46
	lsl r3, r3, #0x2
	ldrh r4, [r0, r3]
	mov r2, #0x1
	lsl r2, r1
	lsl r1, r4, #0x10
	lsr r5, r1, #0x12
	add r1, r5, #0x0
	tst r1, r2
	beq _0200371E
	eor r2, r5
	lsl r2, r2, #0x10
	ldr r1, _02003724 ; =0xFFFF0003
	lsr r2, r2, #0x10
	lsl r2, r2, #0x12
	and r1, r4
	lsr r2, r2, #0x10
	orr r1, r2
	strh r1, [r0, r3]
	pop {r4-r5}
	bx lr
_020036BE:
	ldrh r0, [r2, #0x4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	bne _020036F4
	lsl r0, r4, #0x10
	asr r1, r0, #0x10
	ldrh r0, [r2, #0x6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	add r0, r1, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r4, r3
	ble _020036DE
	lsl r0, r3, #0x10
	asr r4, r0, #0x10
_020036DE:
	ldrh r1, [r2, #0x2]
	ldr r0, _02003728 ; =0xFFFFF83F
	and r1, r0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x15
	orr r0, r1
	strh r0, [r2, #0x2]
	pop {r4-r5}
	bx lr
_020036F4:
	lsl r0, r4, #0x10
	asr r1, r0, #0x10
	ldrh r0, [r2, #0x6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	sub r0, r1, r0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	cmp r4, r3
	bge _0200370C
	lsl r0, r3, #0x10
	asr r4, r0, #0x10
_0200370C:
	ldrh r1, [r2, #0x2]
	ldr r0, _02003728 ; =0xFFFFF83F
	and r1, r0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x15
	orr r0, r1
	strh r0, [r2, #0x2]
_0200371E:
	pop {r4-r5}
	bx lr
	nop
_02003724: .word 0xFFFF0003
_02003728: .word 0xFFFFF83F

	thumb_func_start FUN_0200372C
FUN_0200372C: ; 0x0200372C
	push {r3-r7, lr}
	add r6, r0, #0x0
	ldr r0, _020038DC ; =0x0000011A
	ldrh r1, [r6, r0]
	lsl r1, r1, #0x10
	lsr r1, r1, #0x1f
	bne _02003748
	sub r0, r0, #0x2
	ldrh r0, [r6, r0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	cmp r0, #0x1
	beq _02003748
	b _020038DA
_02003748:
	mov r7, #0x2
	mov r5, #0x0
	add r4, r6, #0x0
	lsl r7, r7, #0xc
_02003750:
	ldr r0, _020038DC ; =0x0000011A
	ldrh r1, [r6, r0]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x1f
	bne _02003770
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0200377C
	lsl r0, r1, #0x12
	lsl r1, r5, #0x10
	lsr r0, r0, #0x12
	lsr r1, r1, #0x10
	bl FUN_02003314
	cmp r0, #0x0
	beq _0200377C
_02003770:
	ldr r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	blx DC_FlushRange
	cmp r5, #0xd
	bls _0200377E
_0200377C:
	b _020038A4
_0200377E:
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200378A: ; jump table (using 16-bit offset)
	.short _020037A6 - _0200378A - 2; case 0
	.short _020037B2 - _0200378A - 2; case 1
	.short _020037BE - _0200378A - 2; case 2
	.short _020037CA - _0200378A - 2; case 3
	.short _020037D6 - _0200378A - 2; case 4
	.short _020037EA - _0200378A - 2; case 5
	.short _020037FE - _0200378A - 2; case 6
	.short _02003814 - _0200378A - 2; case 7
	.short _0200382A - _0200378A - 2; case 8
	.short _0200383E - _0200378A - 2; case 9
	.short _02003852 - _0200378A - 2; case 10
	.short _02003868 - _0200378A - 2; case 11
	.short _0200387E - _0200378A - 2; case 12
	.short _02003892 - _0200378A - 2; case 13
_020037A6:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C9550
	b _020038A4
_020037B2:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C94E8
	b _020038A4
_020037BE:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C9480
	b _020038A4
_020037CA:
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C9418
	b _020038A4
_020037D6:
	blx FUN_020C8B10
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C8A90
	blx FUN_020C8A2C
	b _020038A4
_020037EA:
	blx FUN_020C8B10
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r1, r7, #0x0
	blx FUN_020C8A90
	blx FUN_020C8A2C
	b _020038A4
_020037FE:
	blx FUN_020C8B10
	mov r1, #0x1
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xe
	blx FUN_020C8A90
	blx FUN_020C8A2C
	b _020038A4
_02003814:
	blx FUN_020C8B10
	mov r1, #0x6
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xc
	blx FUN_020C8A90
	blx FUN_020C8A2C
	b _020038A4
_0200382A:
	blx FUN_020C88CC
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C8858
	blx FUN_020C880C
	b _020038A4
_0200383E:
	blx FUN_020C88CC
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	add r1, r7, #0x0
	blx FUN_020C8858
	blx FUN_020C880C
	b _020038A4
_02003852:
	blx FUN_020C88CC
	mov r1, #0x1
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xe
	blx FUN_020C8858
	blx FUN_020C880C
	b _020038A4
_02003868:
	blx FUN_020C88CC
	mov r1, #0x6
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	lsl r1, r1, #0xc
	blx FUN_020C8858
	blx FUN_020C880C
	b _020038A4
_0200387E:
	blx FUN_020C89BC
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C8948
	blx FUN_020C88F0
	b _020038A4
_02003892:
	blx FUN_020C87E8
	ldr r0, [r4, #0x4]
	ldr r2, [r4, #0x8]
	mov r1, #0x0
	blx FUN_020C8774
	blx FUN_020C8728
_020038A4:
	add r5, r5, #0x1
	add r4, #0x14
	cmp r5, #0xe
	bge _020038AE
	b _02003750
_020038AE:
	ldr r3, _020038DC ; =0x0000011A
	ldr r1, _020038E0 ; =0xFFFFC000
	sub r2, r3, #0x2
	ldrh r2, [r6, r2]
	ldrh r0, [r6, r3]
	lsl r2, r2, #0x10
	and r0, r1
	lsr r2, r2, #0x12
	lsr r1, r1, #0x12
	and r1, r2
	orr r0, r1
	strh r0, [r6, r3]
	ldrh r0, [r6, r3]
	lsl r0, r0, #0x12
	lsr r0, r0, #0x12
	bne _020038DA
	sub r0, r3, #0x2
	ldrh r1, [r6, r0]
	mov r0, #0x3
	bic r1, r0
	sub r0, r3, #0x2
	strh r1, [r6, r0]
_020038DA:
	pop {r3-r7, pc}
	.balign 4
_020038DC: .word 0x0000011A
_020038E0: .word 0xFFFFC000

	thumb_func_start FUN_020038E4
FUN_020038E4: ; 0x020038E4
	mov r1, #0x46
	lsl r1, r1, #0x2
	ldrh r0, [r0, r1]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x12
	bx lr

	thumb_func_start FUN_020038F0
FUN_020038F0: ; 0x020038F0
	push {r3-r4}
	ldr r3, _0200390C ; =0x0000011A
	lsl r1, r1, #0x10
	ldrh r4, [r0, r3]
	ldr r2, _02003910 ; =0xFFFF7FFF
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	and r2, r4
	lsr r1, r1, #0x10
	orr r1, r2
	strh r1, [r0, r3]
	pop {r3-r4}
	bx lr
	nop
_0200390C: .word 0x0000011A
_02003910: .word 0xFFFF7FFF

	thumb_func_start FUN_02003914
FUN_02003914: ; 0x02003914
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	str r3, [sp, #0x0]
	mov r0, #0x14
	add r4, r1, #0x0
	mul r4, r0
	add r0, sp, #0x10
	ldrh r0, [r0, #0x14]
	add r7, r2, #0x0
	ldr r5, [sp, #0x20]
	str r0, [sp, #0x4]
	lsl r1, r0, #0x1
	add r0, r6, r4
	ldr r0, [r0, #0x8]
	cmp r1, r0
	bls _0200393A
	bl ErrorHandling
_0200393A:
	sub r0, r7, #0x1
	cmp r0, #0x1
	bhi _02003952
	ldr r2, [r6, r4]
	lsl r1, r5, #0x1
	add r1, r2, r1
	ldr r2, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r2, r2, r5
	lsl r2, r2, #0x1
	blx MIi_CpuClear16
_02003952:
	cmp r7, #0x0
	beq _0200395A
	cmp r7, #0x2
	bne _0200396E
_0200395A:
	add r1, r6, r4
	ldr r2, [r1, #0x4]
	lsl r1, r5, #0x1
	add r1, r2, r1
	ldr r2, [sp, #0x4]
	ldr r0, [sp, #0x0]
	sub r2, r2, r5
	lsl r2, r2, #0x1
	blx MIi_CpuClear16
_0200396E:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02003974
FUN_02003974: ; 0x02003974
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	mov r12, r1
	lsl r1, r0, #0x16
	lsl r0, r0, #0x11
	lsr r1, r1, #0x1b
	lsr r0, r0, #0x1b
	mov r2, #0x0
	mov lr, r1
	str r0, [sp, #0x8]
	cmp r7, #0x0
	bls _020039E2
_0200399A:
	ldr r0, [sp, #0x0]
	lsl r6, r2, #0x1
	ldrh r4, [r0, r6]
	lsl r0, r4, #0x1b
	lsr r1, r0, #0x1b
	lsl r0, r4, #0x16
	lsl r4, r4, #0x11
	lsr r5, r4, #0x1b
	ldr r4, [sp, #0x8]
	lsr r0, r0, #0x1b
	sub r4, r4, r5
	mul r4, r3
	asr r4, r4, #0x4
	add r4, r5, r4
	lsl r5, r4, #0xa
	mov r4, r12
	sub r4, r4, r1
	mul r4, r3
	asr r4, r4, #0x4
	add r1, r1, r4
	mov r4, lr
	sub r4, r4, r0
	mul r4, r3
	asr r4, r4, #0x4
	add r0, r0, r4
	lsl r0, r0, #0x5
	orr r0, r1
	add r1, r5, #0x0
	orr r1, r0
	ldr r0, [sp, #0x4]
	strh r1, [r0, r6]
	add r0, r2, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, r7
	blo _0200399A
_020039E2:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020039E8
FUN_020039E8: ; 0x020039E8
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r2, #0x0
	add r5, r0, #0x0
	mov r2, #0x14
	add r6, r1, #0x0
	mul r6, r2
	str r3, [sp, #0x4]
	ldr r1, [r5, r6]
	mov r0, #0x0
	add r4, r5, r6
	cmp r1, #0x0
	beq _02003A0A
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _02003A0A
	mov r0, #0x1
_02003A0A:
	cmp r0, #0x0
	bne _02003A12
	bl ErrorHandling
_02003A12:
	add r3, sp, #0x10
	ldrh r0, [r3, #0x14]
	add r2, r5, r6
	lsl r1, r7, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, [r2, #0x4]
	add r0, r0, r1
	add r1, r2, r1
	ldrb r3, [r3, #0x10]
	ldr r2, [sp, #0x4]
	bl FUN_02003974
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003A30
FUN_02003A30: ; 0x02003A30
	push {r3-r7, lr}
	sub sp, #0x8
	str r3, [sp, #0x4]
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	ldr r7, [sp, #0x20]
	beq _02003A60
_02003A40:
	mov r0, #0x1
	tst r0, r4
	beq _02003A54
	str r7, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x10
	bl FUN_02003974
_02003A54:
	lsl r0, r4, #0xf
	lsr r4, r0, #0x10
	add r6, #0x20
	add r5, #0x20
	cmp r4, #0x0
	bne _02003A40
_02003A60:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02003A64
FUN_02003A64: ; 0x02003A64
	push {r4-r7, lr}
	sub sp, #0xc
	str r3, [sp, #0x8]
	add r6, r0, #0x0
	add r7, r1, #0x0
	ldr r0, [sp, #0x20]
	add r5, r2, #0x0
	mov r1, #0x14
	add r2, r7, #0x0
	str r0, [sp, #0x20]
	mul r2, r1
	mov r4, #0x0
	ldr r1, [r6, r2]
	add r0, r4, #0x0
	cmp r1, #0x0
	beq _02003A8E
	add r1, r6, r2
	ldr r1, [r1, #0x4]
	cmp r1, #0x0
	beq _02003A8E
	mov r0, #0x1
_02003A8E:
	cmp r0, #0x0
	bne _02003A96
	bl ErrorHandling
_02003A96:
	cmp r5, #0x0
	beq _02003AC0
_02003A9A:
	mov r0, #0x1
	tst r0, r5
	beq _02003AB6
	ldr r0, [sp, #0x8]
	lsl r2, r4, #0x10
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	lsr r2, r2, #0x10
	mov r3, #0x10
	bl FUN_020039E8
_02003AB6:
	lsl r0, r5, #0xf
	lsr r5, r0, #0x10
	add r4, #0x10
	cmp r5, #0x0
	bne _02003A9A
_02003AC0:
	add sp, #0xc
	pop {r4-r7, pc}

	thumb_func_start FUN_02003AC4
FUN_02003AC4: ; 0x02003AC4
	push {r3-r7, lr}
	mov lr, r1
	mov r12, r2
	add r7, r3, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	ble _02003B3C
	ldr r6, [sp, #0x18]
_02003AD4:
	ldrh r3, [r0, #0x0]
	mov r1, #0x1f
	add r2, r3, #0x0
	asr r5, r3, #0xa
	and r2, r1
	and r5, r1
	mov r1, #0x1d
	mul r1, r5
	mov r5, #0x4c
	mul r5, r2
	asr r3, r3, #0x5
	mov r2, #0x1f
	and r3, r2
	mov r2, #0x97
	mul r2, r3
	add r2, r5, r2
	add r1, r1, r2
	asr r3, r1, #0x8
	mov r1, r12
	add r2, r1, #0x0
	mul r2, r3
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	asr r2, r1, #0x8
	add r1, r7, #0x0
	mul r1, r3
	mul r3, r6
	lsl r1, r1, #0x10
	lsl r3, r3, #0x10
	lsr r1, r1, #0x10
	lsr r3, r3, #0x10
	asr r1, r1, #0x8
	asr r3, r3, #0x8
	cmp r2, #0x1f
	ble _02003B1C
	mov r2, #0x1f
_02003B1C:
	cmp r1, #0x1f
	ble _02003B22
	mov r1, #0x1f
_02003B22:
	cmp r3, #0x1f
	ble _02003B28
	mov r3, #0x1f
_02003B28:
	lsl r3, r3, #0xa
	lsl r1, r1, #0x5
	orr r1, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	add r4, r4, #0x1
	mov r1, lr
	add r0, r0, #0x2
	cmp r4, r1
	blt _02003AD4
_02003B3C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02003B40
FUN_02003B40: ; 0x02003B40
	push {r3-r5, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	add r2, sp, #0x4
	bl FUN_02006C08
	add r4, r0, #0x0
	bne _02003B58
	bl ErrorHandling
_02003B58:
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _02003B64
	ldr r0, [sp, #0x4]
	ldr r0, [r0, #0x8]
	str r0, [sp, #0x1c]
_02003B64:
	ldr r0, [sp, #0x2c]
	ldr r2, [sp, #0x24]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	ldr r3, [sp, #0x28]
	ldr r0, [r0, #0xc]
	mov r1, #0x10
	bl FUN_02003AC4
	ldr r0, [sp, #0x1c]
	add r3, sp, #0x8
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldrh r3, [r3, #0x18]
	ldr r1, [r1, #0xc]
	ldr r2, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_02003054
	add r0, r4, #0x0
	bl FUN_02016A18
	add sp, #0x8
	pop {r3-r5, pc}

	thumb_func_start FUN_02003B98
FUN_02003B98: ; 0x02003B98
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	bl FUN_02003D30
	add r4, r0, #0x0
	blx FUN_020C01D0
	bl FUN_020040C8
	add r0, r4, #0x0
	bl FUN_02004064
	add r0, r4, #0x0
	ldr r1, _02003C00 ; =0x000BBC00
	add r0, #0x94
	blx FUN_020C2A94
	add r1, r4, #0x0
	add r1, #0x90
	str r0, [r1, #0x0]
	add r2, r4, #0x0
	add r2, #0x90
	ldr r1, _02003C04 ; =0x02104780
	ldr r2, [r2, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	blx FUN_020C26F8
	add r0, r4, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	blx FUN_020C39CC
	add r0, r4, #0x0
	bl FUN_02004088
	add r0, r4, #0x0
	bl FUN_020040A4
	ldr r0, _02003C08 ; =0x02107070
	mov r1, #0x0
	str r1, [r0, #0x4]
	ldr r0, _02003C0C ; =0x000BCD4C
	str r5, [r4, r0]
	ldrh r0, [r6, #0x0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	bl FUN_02004D60
	pop {r4-r6, pc}
	nop
_02003C00: .word 0x000BBC00
_02003C04: .word 0x02104780
_02003C08: .word 0x02107070
_02003C0C: .word 0x000BCD4C

	thumb_func_start FUN_02003C10
FUN_02003C10: ; 0x02003C10
	push {r4, lr}
	bl FUN_02003D30
	add r4, r0, #0x0
	bl FUN_02003D04
	cmp r0, #0x0
	bne _02003C30
	ldr r0, _02003C3C ; =0x000BCD00
	ldr r1, [r4, r0]
	cmp r1, #0x0
	ble _02003C2C
	sub r1, r1, #0x1
	str r1, [r4, r0]
_02003C2C:
	bl FUN_02003C40
_02003C30:
	bl FUN_02005CFC
	blx FUN_020C01A0
	pop {r4, pc}
	nop
_02003C3C: .word 0x000BCD00

	thumb_func_start FUN_02003C40
FUN_02003C40: ; 0x02003C40
	push {r4, lr}
	bl FUN_02003D30
	add r4, r0, #0x0
	ldr r0, _02003CDC ; =0x02107070
	ldr r0, [r0, #0x0]
	cmp r0, #0x6
	bhi _02003CD8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02003C5C: ; jump table (using 16-bit offset)
	.short _02003CD8 - _02003C5C - 2; case 0
	.short _02003C6A - _02003C5C - 2; case 1
	.short _02003CD8 - _02003C5C - 2; case 2
	.short _02003C72 - _02003C5C - 2; case 3
	.short _02003C82 - _02003C5C - 2; case 4
	.short _02003C92 - _02003C5C - 2; case 5
	.short _02003CB0 - _02003C5C - 2; case 6
_02003C6A:
	mov r0, #0x2
	bl FUN_02003CE8
	pop {r4, pc}
_02003C72:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	mov r0, #0x2
	bl FUN_02003CE8
	pop {r4, pc}
_02003C82:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	mov r0, #0x2
	bl FUN_02003CE8
	pop {r4, pc}
_02003C92:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_02004D94
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_020040DC
	ldr r0, _02003CE0 ; =0x000BCD0E
	ldrh r0, [r4, r0]
	bl FUN_0200521C
	pop {r4, pc}
_02003CB0:
	bl FUN_02005404
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_02004D94
	cmp r0, #0x0
	bne _02003CD8
	bl FUN_020040DC
	ldr r0, _02003CE0 ; =0x000BCD0E
	ldrh r0, [r4, r0]
	bl FUN_0200521C
	ldr r1, _02003CE4 ; =0x000BCD08
	mov r0, #0x7f
	ldr r1, [r4, r1]
	mov r2, #0x0
	bl FUN_0200538C
_02003CD8:
	pop {r4, pc}
	nop
_02003CDC: .word 0x02107070
_02003CE0: .word 0x000BCD0E
_02003CE4: .word 0x000BCD08

	thumb_func_start FUN_02003CE8
FUN_02003CE8: ; 0x02003CE8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	ldr r1, _02003CFC ; =0x000BCCFC
	mov r2, #0x0
	strh r2, [r0, r1]
	ldr r0, _02003D00 ; =0x02107070
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4
_02003CFC: .word 0x000BCCFC
_02003D00: .word 0x02107070

	thumb_func_start FUN_02003D04
FUN_02003D04: ; 0x02003D04
	push {r4, lr}
	bl FUN_02003D30
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_020048BC
	cmp r0, #0x0
	beq _02003D1A
	mov r0, #0x1
	pop {r4, pc}
_02003D1A:
	ldr r0, _02003D2C ; =0x000BCD12
	ldrh r0, [r4, r0]
	cmp r0, #0x0
	beq _02003D26
	mov r0, #0x1
	pop {r4, pc}
_02003D26:
	mov r0, #0x0
	pop {r4, pc}
	nop
_02003D2C: .word 0x000BCD12

	thumb_func_start FUN_02003D30
FUN_02003D30: ; 0x02003D30
	ldr r0, _02003D34 ; =0x02107078
	bx lr
	.balign 4
_02003D34: .word 0x02107078

	thumb_func_start FUN_02003D38
FUN_02003D38: ; 0x02003D38
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	cmp r4, #0x27
	bls _02003D46
	b _02003E92
_02003D46:
	add r1, r4, r4
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02003D52: ; jump table (using 16-bit offset)
	.short _02003DA8 - _02003D52 - 2; case 0
	.short _02003DAE - _02003D52 - 2; case 1
	.short _02003DB4 - _02003D52 - 2; case 2
	.short _02003DBA - _02003D52 - 2; case 3
	.short _02003DC0 - _02003D52 - 2; case 4
	.short _02003DA2 - _02003D52 - 2; case 5
	.short _02003DC6 - _02003D52 - 2; case 6
	.short _02003DCC - _02003D52 - 2; case 7
	.short _02003DD2 - _02003D52 - 2; case 8
	.short _02003DD8 - _02003D52 - 2; case 9
	.short _02003DDE - _02003D52 - 2; case 10
	.short _02003DE4 - _02003D52 - 2; case 11
	.short _02003DEA - _02003D52 - 2; case 12
	.short _02003DF0 - _02003D52 - 2; case 13
	.short _02003DF6 - _02003D52 - 2; case 14
	.short _02003DFC - _02003D52 - 2; case 15
	.short _02003E02 - _02003D52 - 2; case 16
	.short _02003E08 - _02003D52 - 2; case 17
	.short _02003E0E - _02003D52 - 2; case 18
	.short _02003E14 - _02003D52 - 2; case 19
	.short _02003E1A - _02003D52 - 2; case 20
	.short _02003E20 - _02003D52 - 2; case 21
	.short _02003E26 - _02003D52 - 2; case 22
	.short _02003E2C - _02003D52 - 2; case 23
	.short _02003E32 - _02003D52 - 2; case 24
	.short _02003E38 - _02003D52 - 2; case 25
	.short _02003E3E - _02003D52 - 2; case 26
	.short _02003E44 - _02003D52 - 2; case 27
	.short _02003E4A - _02003D52 - 2; case 28
	.short _02003E50 - _02003D52 - 2; case 29
	.short _02003E56 - _02003D52 - 2; case 30
	.short _02003E5C - _02003D52 - 2; case 31
	.short _02003E62 - _02003D52 - 2; case 32
	.short _02003E68 - _02003D52 - 2; case 33
	.short _02003E6E - _02003D52 - 2; case 34
	.short _02003E74 - _02003D52 - 2; case 35
	.short _02003E7A - _02003D52 - 2; case 36
	.short _02003E80 - _02003D52 - 2; case 37
	.short _02003E86 - _02003D52 - 2; case 38
	.short _02003E8C - _02003D52 - 2; case 39
_02003DA2:
	ldr r1, _02003E9C ; =0x000BCCFE
	add r0, r0, r1
	pop {r4, pc}
_02003DA8:
	ldr r1, _02003EA0 ; =0x000BBCB8
	add r0, r0, r1
	pop {r4, pc}
_02003DAE:
	ldr r1, _02003EA4 ; =0x000BBCBC
	add r0, r0, r1
	pop {r4, pc}
_02003DB4:
	ldr r1, _02003EA8 ; =0x000BBCC0
	add r0, r0, r1
	pop {r4, pc}
_02003DBA:
	ldr r1, _02003EAC ; =0x000BBCE0
	add r0, r0, r1
	pop {r4, pc}
_02003DC0:
	ldr r1, _02003EB0 ; =0x000BCCE0
	add r0, r0, r1
	pop {r4, pc}
_02003DC6:
	ldr r1, _02003EB4 ; =0x000BCD00
	add r0, r0, r1
	pop {r4, pc}
_02003DCC:
	ldr r1, _02003EB8 ; =0x000BCD04
	add r0, r0, r1
	pop {r4, pc}
_02003DD2:
	ldr r1, _02003EBC ; =0x000BCD08
	add r0, r0, r1
	pop {r4, pc}
_02003DD8:
	ldr r1, _02003EC0 ; =0x000BCD0C
	add r0, r0, r1
	pop {r4, pc}
_02003DDE:
	ldr r1, _02003EC4 ; =0x000BCD0E
	add r0, r0, r1
	pop {r4, pc}
_02003DE4:
	ldr r1, _02003EC8 ; =0x000BCD10
	add r0, r0, r1
	pop {r4, pc}
_02003DEA:
	ldr r1, _02003ECC ; =0x000BCD11
	add r0, r0, r1
	pop {r4, pc}
_02003DF0:
	ldr r1, _02003ED0 ; =0x000BCD12
	add r0, r0, r1
	pop {r4, pc}
_02003DF6:
	ldr r1, _02003ED4 ; =0x000BCD14
	add r0, r0, r1
	pop {r4, pc}
_02003DFC:
	ldr r1, _02003ED8 ; =0x000BCD15
	add r0, r0, r1
	pop {r4, pc}
_02003E02:
	ldr r1, _02003EDC ; =0x000BCD16
	add r0, r0, r1
	pop {r4, pc}
_02003E08:
	ldr r1, _02003EE0 ; =0x000BCD17
	add r0, r0, r1
	pop {r4, pc}
_02003E0E:
	ldr r1, _02003EE4 ; =0x000BCD18
	add r0, r0, r1
	pop {r4, pc}
_02003E14:
	ldr r1, _02003EE8 ; =0x000BCD19
	add r0, r0, r1
	pop {r4, pc}
_02003E1A:
	ldr r1, _02003EEC ; =0x000BCD1A
	add r0, r0, r1
	pop {r4, pc}
_02003E20:
	ldr r1, _02003EF0 ; =0x000BCD1B
	add r0, r0, r1
	pop {r4, pc}
_02003E26:
	ldr r1, _02003EF4 ; =0x000BCD1C
	add r0, r0, r1
	pop {r4, pc}
_02003E2C:
	ldr r1, _02003EF8 ; =0x000BCD20
	add r0, r0, r1
	pop {r4, pc}
_02003E32:
	ldr r1, _02003EFC ; =0x000BCD24
	add r0, r0, r1
	pop {r4, pc}
_02003E38:
	ldr r1, _02003F00 ; =0x000BCD28
	add r0, r0, r1
	pop {r4, pc}
_02003E3E:
	ldr r1, _02003F04 ; =0x000BCD2C
	add r0, r0, r1
	pop {r4, pc}
_02003E44:
	ldr r1, _02003F08 ; =0x000BCD30
	add r0, r0, r1
	pop {r4, pc}
_02003E4A:
	ldr r1, _02003F0C ; =0x000BCD34
	add r0, r0, r1
	pop {r4, pc}
_02003E50:
	ldr r1, _02003F10 ; =0x000BCD38
	add r0, r0, r1
	pop {r4, pc}
_02003E56:
	ldr r1, _02003F14 ; =0x000BCD39
	add r0, r0, r1
	pop {r4, pc}
_02003E5C:
	ldr r1, _02003F18 ; =0x000BCD3A
	add r0, r0, r1
	pop {r4, pc}
_02003E62:
	ldr r1, _02003F1C ; =0x000BCD3C
	add r0, r0, r1
	pop {r4, pc}
_02003E68:
	ldr r1, _02003F20 ; =0x000BCD40
	add r0, r0, r1
	pop {r4, pc}
_02003E6E:
	ldr r1, _02003F24 ; =0x000BCD48
	add r0, r0, r1
	pop {r4, pc}
_02003E74:
	ldr r1, _02003F28 ; =0x000BCD4C
	add r0, r0, r1
	pop {r4, pc}
_02003E7A:
	ldr r1, _02003F2C ; =0x000BCD50
	add r0, r0, r1
	pop {r4, pc}
_02003E80:
	ldr r1, _02003F30 ; =0x000BCD54
	add r0, r0, r1
	pop {r4, pc}
_02003E86:
	ldr r1, _02003F34 ; =0x000BCD58
	add r0, r0, r1
	pop {r4, pc}
_02003E8C:
	ldr r1, _02003F38 ; =0x000BCD5C
	add r0, r0, r1
	pop {r4, pc}
_02003E92:
	bl ErrorHandling
	mov r0, #0x0
	pop {r4, pc}
	nop
_02003E9C: .word 0x000BCCFE
_02003EA0: .word 0x000BBCB8
_02003EA4: .word 0x000BBCBC
_02003EA8: .word 0x000BBCC0
_02003EAC: .word 0x000BBCE0
_02003EB0: .word 0x000BCCE0
_02003EB4: .word 0x000BCD00
_02003EB8: .word 0x000BCD04
_02003EBC: .word 0x000BCD08
_02003EC0: .word 0x000BCD0C
_02003EC4: .word 0x000BCD0E
_02003EC8: .word 0x000BCD10
_02003ECC: .word 0x000BCD11
_02003ED0: .word 0x000BCD12
_02003ED4: .word 0x000BCD14
_02003ED8: .word 0x000BCD15
_02003EDC: .word 0x000BCD16
_02003EE0: .word 0x000BCD17
_02003EE4: .word 0x000BCD18
_02003EE8: .word 0x000BCD19
_02003EEC: .word 0x000BCD1A
_02003EF0: .word 0x000BCD1B
_02003EF4: .word 0x000BCD1C
_02003EF8: .word 0x000BCD20
_02003EFC: .word 0x000BCD24
_02003F00: .word 0x000BCD28
_02003F04: .word 0x000BCD2C
_02003F08: .word 0x000BCD30
_02003F0C: .word 0x000BCD34
_02003F10: .word 0x000BCD38
_02003F14: .word 0x000BCD39
_02003F18: .word 0x000BCD3A
_02003F1C: .word 0x000BCD3C
_02003F20: .word 0x000BCD40
_02003F24: .word 0x000BCD48
_02003F28: .word 0x000BCD4C
_02003F2C: .word 0x000BCD50
_02003F30: .word 0x000BCD54
_02003F34: .word 0x000BCD58
_02003F38: .word 0x000BCD5C

	thumb_func_start FUN_02003F3C
FUN_02003F3C: ; 0x02003F3C
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	add r0, #0x90
	ldr r0, [r0, #0x0]
	blx FUN_020C290C
	add r4, r0, #0x0
	mov r0, #0x0
	mvn r0, r0
	cmp r4, r0
	bne _02003F5A
	bl ErrorHandling
_02003F5A:
	cmp r5, #0x0
	beq _02003F60
	str r4, [r5, #0x0]
_02003F60:
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02003F64
FUN_02003F64: ; 0x02003F64
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r0, #0x90
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	blx FUN_020C2828
	pop {r4, pc}

	thumb_func_start FUN_02003F78
FUN_02003F78: ; 0x02003F78
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	blx FUN_020C36A8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003F90
FUN_02003F90: ; 0x02003F90
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	blx FUN_020C3674
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003FA8
FUN_02003FA8: ; 0x02003FA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02003D30
	add r2, r0, #0x0
	add r2, #0x90
	ldr r2, [r2, #0x0]
	add r0, r5, #0x0
	add r1, r4, #0x0
	blx FUN_020C35E0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02003FC4
FUN_02003FC4: ; 0x02003FC4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	blx FUN_020C360C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003FDC
FUN_02003FDC: ; 0x02003FDC
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	add r1, r0, #0x0
	add r1, #0x90
	ldr r1, [r1, #0x0]
	add r0, r4, #0x0
	blx FUN_020C3640
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02003FF4
FUN_02003FF4: ; 0x02003FF4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	add r4, r0, #0x0
	cmp r5, #0x9
	blt _02004008
	bl ErrorHandling
	mov r5, #0x0
_02004008:
	ldr r0, _02004014 ; =0x000BBC94
	add r1, r4, r0
	lsl r0, r5, #0x2
	add r0, r1, r0
	pop {r3-r5, pc}
	nop
_02004014: .word 0x000BBC94

	thumb_func_start FUN_02004018
FUN_02004018: ; 0x02004018
	push {r3, lr}
	cmp r0, #0x7
	bhi _0200405A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200402A: ; jump table (using 16-bit offset)
	.short _0200403E - _0200402A - 2; case 0
	.short _0200403A - _0200402A - 2; case 1
	.short _02004042 - _0200402A - 2; case 2
	.short _02004046 - _0200402A - 2; case 3
	.short _0200404A - _0200402A - 2; case 4
	.short _0200404E - _0200402A - 2; case 5
	.short _02004052 - _0200402A - 2; case 6
	.short _02004056 - _0200402A - 2; case 7
_0200403A:
	mov r0, #0x0
	pop {r3, pc}
_0200403E:
	mov r0, #0x1
	pop {r3, pc}
_02004042:
	mov r0, #0x2
	pop {r3, pc}
_02004046:
	mov r0, #0x3
	pop {r3, pc}
_0200404A:
	mov r0, #0x4
	pop {r3, pc}
_0200404E:
	mov r0, #0x5
	pop {r3, pc}
_02004052:
	mov r0, #0x6
	pop {r3, pc}
_02004056:
	mov r0, #0x7
	pop {r3, pc}
_0200405A:
	bl ErrorHandling
	mov r0, #0x3
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004064
FUN_02004064: ; 0x02004064
	push {r4, lr}
	ldr r2, _02004080 ; =0x000BCD60
	mov r1, #0x0
	add r4, r0, #0x0
	blx Call_FillMemWithValue
	ldr r0, _02004084 ; =0x000BCD1C
	mov r1, #0x0
_02004074:
	add r1, r1, #0x1
	str r1, [r4, r0]
	add r4, r4, #0x4
	cmp r1, #0x7
	blt _02004074
	pop {r4, pc}
	.balign 4
_02004080: .word 0x000BCD60
_02004084: .word 0x000BCD1C

	thumb_func_start FUN_02004088
FUN_02004088: ; 0x02004088
	push {r3-r5, lr}
	ldr r1, _020040A0 ; =0x000BBC94
	mov r4, #0x0
	add r5, r0, r1
_02004090:
	add r0, r5, #0x0
	blx FUN_020C0F80
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x9
	blt _02004090
	pop {r3-r5, pc}
	.balign 4
_020040A0: .word 0x000BBC94

	thumb_func_start FUN_020040A4
FUN_020040A4: ; 0x020040A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020040C0 ; =0x000BCD1C
	add r0, r4, r0
	bl FUN_02003F3C
	mov r0, #0x0
	bl FUN_02003F78
	ldr r0, _020040C4 ; =0x000BCD20
	add r0, r4, r0
	bl FUN_02003F3C
	pop {r4, pc}
	.balign 4
_020040C0: .word 0x000BCD1C
_020040C4: .word 0x000BCD20

	thumb_func_start FUN_020040C8
FUN_020040C8: ; 0x020040C8
	push {r3, lr}
	blx MIC_Init
	mov r0, #0x1
	blx PM_SetAmp
	mov r0, #0x2
	blx PM_SetAmpGain
	pop {r3, pc}

	thumb_func_start FUN_020040DC
FUN_020040DC: ; 0x020040DC
	push {r3, lr}
	mov r0, #0x7
	mov r1, #0x0
	blx FUN_020C1040
	mov r0, #0x7
	bl FUN_02003FF4
	blx FUN_020C0F68
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020040F4
FUN_020040F4: ; 0x020040F4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x5
	bl FUN_02003D38
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004104
FUN_02004104: ; 0x02004104
	push {r3, lr}
	mov r0, #0x5
	bl FUN_02003D38
	ldrb r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02004110
FUN_02004110: ; 0x02004110
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x9
	bl FUN_02003D38
	strh r4, [r0, #0x0]
	mov r0, #0x0
	bl FUN_02004130
	pop {r4, pc}

	thumb_func_start FUN_02004124
FUN_02004124: ; 0x02004124
	push {r3, lr}
	mov r0, #0x9
	bl FUN_02003D38
	ldrh r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02004130
FUN_02004130: ; 0x02004130
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xa
	bl FUN_02003D38
	strh r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004140
FUN_02004140: ; 0x02004140
	push {r3, lr}
	mov r0, #0xa
	bl FUN_02003D38
	ldrh r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_0200414C
FUN_0200414C: ; 0x0200414C
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1f
	bl FUN_02003D38
	strh r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200415C
FUN_0200415C: ; 0x0200415C
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x14
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x15
	bl FUN_02003D38
	cmp r5, #0x33
	bhs _0200417A
	strb r5, [r4, #0x0]
	mov r1, #0x0
	strb r1, [r0, #0x0]
	pop {r3-r5, pc}
_0200417A:
	strb r5, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02004180
FUN_02004180: ; 0x02004180
	push {r3, lr}
	cmp r0, #0x39
	bgt _020041DE
	blt _0200418A
	b _020042C8
_0200418A:
	cmp r0, #0x35
	bgt _020041CC
	blt _02004192
	b _0200429A
_02004192:
	cmp r0, #0x33
	bgt _020041C6
	bge _0200427C
	cmp r0, #0xe
	bhi _020041CA
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #0x6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_020041A8: ; jump table (using 16-bit offset)
	.short _0200432C - _020041A8 - 2; case 0
	.short _02004222 - _020041A8 - 2; case 1
	.short _0200422C - _020041A8 - 2; case 2
	.short _02004236 - _020041A8 - 2; case 3
	.short _02004240 - _020041A8 - 2; case 4
	.short _0200424A - _020041A8 - 2; case 5
	.short _0200425E - _020041A8 - 2; case 6
	.short _0200429A - _020041A8 - 2; case 7
	.short _02004268 - _020041A8 - 2; case 8
	.short _02004222 - _020041A8 - 2; case 9
	.short _02004222 - _020041A8 - 2; case 10
	.short _02004254 - _020041A8 - 2; case 11
	.short _02004272 - _020041A8 - 2; case 12
	.short _0200422C - _020041A8 - 2; case 13
	.short _02004222 - _020041A8 - 2; case 14
_020041C6:
	cmp r0, #0x34
	beq _02004290
_020041CA:
	b _0200432C
_020041CC:
	cmp r0, #0x37
	bgt _020041D8
	bge _020042AE
	cmp r0, #0x36
	beq _020042A4
	b _0200432C
_020041D8:
	cmp r0, #0x38
	beq _020042BE
	b _0200432C
_020041DE:
	cmp r0, #0x3d
	bgt _020041F8
	blt _020041E6
	b _020042F0
_020041E6:
	cmp r0, #0x3b
	bgt _020041F2
	bge _020042DC
	cmp r0, #0x3a
	beq _020042D2
	b _0200432C
_020041F2:
	cmp r0, #0x3c
	beq _020042E6
	b _0200432C
_020041F8:
	cmp r0, #0x3f
	bgt _02004206
	blt _02004200
	b _02004304
_02004200:
	cmp r0, #0x3e
	beq _020042FA
	b _0200432C
_02004206:
	sub r0, #0x40
	cmp r0, #0x3
	bls _0200420E
	b _0200432C
_0200420E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0200421A: ; jump table (using 16-bit offset)
	.short _0200430E - _0200421A - 2; case 0
	.short _0200431E - _0200421A - 2; case 1
	.short _02004286 - _0200421A - 2; case 2
	.short _020042AE - _0200421A - 2; case 3
_02004222:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200422C:
	mov r0, #0x2
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004236:
	mov r0, #0xd
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004240:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200424A:
	mov r0, #0x2
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004254:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200425E:
	mov r0, #0xb
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004268:
	mov r0, #0x1
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004272:
	mov r0, #0xe
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200427C:
	mov r0, #0x3
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004286:
	mov r0, #0x6
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004290:
	mov r0, #0x5
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200429A:
	mov r0, #0x9
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042A4:
	mov r0, #0xa
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042AE:
	ldr r0, _02004330 ; =0x000005E5
	bl FUN_02003FDC
	ldr r0, _02004330 ; =0x000005E5
	bl FUN_02003FC4
	add r1, r0, #0x0
	b _0200432C
_020042BE:
	mov r0, #0xc
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042C8:
	mov r0, #0x7
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042D2:
	mov r0, #0x8
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042DC:
	mov r0, #0xf
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042E6:
	mov r0, #0x3
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042F0:
	mov r0, #0x5
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_020042FA:
	mov r0, #0xf
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_02004304:
	mov r0, #0x4
	bl FUN_02003F78
	add r1, r0, #0x0
	b _0200432C
_0200430E:
	ldr r0, _02004334 ; =0x000005ED
	bl FUN_02003FDC
	ldr r0, _02004334 ; =0x000005ED
	bl FUN_02003FC4
	add r1, r0, #0x0
	b _0200432C
_0200431E:
	ldr r0, _02004338 ; =0x000005EC
	bl FUN_02003FDC
	ldr r0, _02004338 ; =0x000005EC
	bl FUN_02003FC4
	add r1, r0, #0x0
_0200432C:
	add r0, r1, #0x0
	pop {r3, pc}
	.balign 4
_02004330: .word 0x000005E5
_02004334: .word 0x000005ED
_02004338: .word 0x000005EC

	thumb_func_start FUN_0200433C
FUN_0200433C: ; 0x0200433C
	push {r3-r7, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	mov r0, #0x14
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02003D38
	str r0, [sp, #0x0]
	mov r0, #0x15
	bl FUN_02003D38
	str r0, [sp, #0x4]
	mov r0, #0xd
	bl FUN_02003D38
	add r7, r0, #0x0
	cmp r4, #0x33
	bhs _02004370
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, #0x0]
	cmp r0, r4
	bne _0200437E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_02004370:
	ldr r0, [sp, #0x4]
	ldrb r0, [r0, #0x0]
	cmp r0, r4
	bne _0200437E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_0200437E:
	add r0, r4, #0x0
	bl FUN_0200415C
	cmp r4, #0x39
	bgt _020043DC
	bge _02004458
	cmp r4, #0x35
	bgt _020043CA
	bge _02004458
	cmp r4, #0x33
	bgt _020043C4
	bge _02004458
	cmp r4, #0xe
	bhi _020043C8
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020043A6: ; jump table (using 16-bit offset)
	.short _020044A0 - _020043A6 - 2; case 0
	.short _02004460 - _020043A6 - 2; case 1
	.short _02004484 - _020043A6 - 2; case 2
	.short _02004496 - _020043A6 - 2; case 3
	.short _0200441C - _020043A6 - 2; case 4
	.short _02004430 - _020043A6 - 2; case 5
	.short _02004444 - _020043A6 - 2; case 6
	.short _0200444E - _020043A6 - 2; case 7
	.short _02004496 - _020043A6 - 2; case 8
	.short _02004496 - _020043A6 - 2; case 9
	.short _02004496 - _020043A6 - 2; case 10
	.short _0200443A - _020043A6 - 2; case 11
	.short _02004496 - _020043A6 - 2; case 12
	.short _02004496 - _020043A6 - 2; case 13
	.short _02004472 - _020043A6 - 2; case 14
_020043C4:
	cmp r4, #0x34
	beq _02004458
_020043C8:
	b _020044A0
_020043CA:
	cmp r4, #0x37
	bgt _020043D6
	bge _02004458
	cmp r4, #0x36
	beq _02004458
	b _020044A0
_020043D6:
	cmp r4, #0x38
	beq _02004458
	b _020044A0
_020043DC:
	cmp r4, #0x3d
	bgt _020043F4
	bge _02004458
	cmp r4, #0x3b
	bgt _020043EE
	bge _02004458
	cmp r4, #0x3a
	beq _02004458
	b _020044A0
_020043EE:
	cmp r4, #0x3c
	beq _02004458
	b _020044A0
_020043F4:
	cmp r4, #0x3f
	bgt _02004400
	bge _02004458
	cmp r4, #0x3e
	beq _02004458
	b _020044A0
_02004400:
	add r0, r4, #0x0
	sub r0, #0x40
	cmp r0, #0x3
	bhi _020044A0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02004414: ; jump table (using 16-bit offset)
	.short _02004458 - _02004414 - 2; case 0
	.short _02004458 - _02004414 - 2; case 1
	.short _02004458 - _02004414 - 2; case 2
	.short _02004458 - _02004414 - 2; case 3
_0200441C:
	mov r0, #0x0
	bl FUN_0200516C
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020044D4
	mov r0, #0x0
	strh r0, [r7, #0x0]
	b _020044A0
_02004430:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02004648
	b _020044A0
_0200443A:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02004680
	b _020044A0
_02004444:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020046A0
	b _020044A0
_0200444E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_020046C4
	b _020044A0
_02004458:
	add r0, r4, #0x0
	bl FUN_020046E8
	b _020044A0
_02004460:
	mov r0, #0x1
	bl FUN_0200516C
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
	b _020044A0
_02004472:
	mov r0, #0x2
	bl FUN_0200516C
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
	b _020044A0
_02004484:
	mov r0, #0x0
	bl FUN_0200516C
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
	b _020044A0
_02004496:
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r6, #0x0
	bl FUN_02004704
_020044A0:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020044A8
FUN_020044A8: ; 0x020044A8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	ldr r0, [r0, #0x0]
	bl FUN_02003F64
	mov r0, #0x18
	bl FUN_02003D38
	bl FUN_02003F3C
	add r0, r4, #0x0
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	pop {r4, pc}

	thumb_func_start FUN_020044D4
FUN_020044D4: ; 0x020044D4
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0xb
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	mov r0, #0x1f
	bl FUN_02003D38
	mov r0, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	add r4, r0, #0x0
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	bne _0200450E
	cmp r4, r5
	bne _0200450E
	bl FUN_02004140
	mov r1, #0x12
	lsl r1, r1, #0x6
	cmp r0, r1
	bne _02004566
_0200450E:
	mov r0, #0x1
	bl FUN_02004DBC
	bl FUN_02005454
	cmp r4, r5
	beq _02004528
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020047C8
	bl FUN_0200541C
_02004528:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02004560
	mov r0, #0x2
	bl FUN_02004748
	bl FUN_02003F64
	mov r0, #0x4
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	cmp r4, r5
	beq _02004554
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020047C8
_02004554:
	lsl r1, r4, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	bl FUN_02004568
	pop {r4-r6, pc}
_02004560:
	add r0, r5, #0x0
	bl FUN_0200521C
_02004566:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004568
FUN_02004568: ; 0x02004568
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1f
	bl FUN_02003D38
	add r4, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_02004900
	ldr r1, _020045C0 ; =0x000003E9
	cmp r0, r1
	beq _02004594
	add r1, r1, #0x2
	cmp r0, r1
	beq _02004594
	add r0, r5, #0x0
	mov r1, #0x4
	bl FUN_02003FA8
	bl ErrorHandling
	b _0200459C
_02004594:
	ldrh r0, [r4, #0x0]
	mov r1, #0x6
	bl FUN_02003FA8
_0200459C:
	mov r0, #0x1a
	bl FUN_02003D38
	bl FUN_02003F3C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_020047C8
	mov r0, #0x7f
	mov r1, #0x28
	mov r2, #0x0
	bl FUN_0200538C
	mov r0, #0x0
	bl FUN_02004DBC
	pop {r3-r5, pc}
	.balign 4
_020045C0: .word 0x000003E9

	thumb_func_start FUN_020045C4
FUN_020045C4: ; 0x020045C4
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r0, #0x12
	add r5, r1, #0x0
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x1f
	bl FUN_02003D38
	add r4, r0, #0x0
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	beq _020045E4
	cmp r5, #0x0
	bne _02004642
_020045E4:
	mov r0, #0x1
	bl FUN_02004748
	bl FUN_02003F64
	ldrh r0, [r4, #0x0]
	mov r1, #0x2
	bl FUN_02003FA8
	mov r0, #0x18
	bl FUN_02003D38
	bl FUN_02003F3C
	mov r0, #0x4
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	ldrh r0, [r4, #0x0]
	bl FUN_02004900
	ldr r1, _02004644 ; =0x000003E9
	cmp r0, r1
	beq _02004630
	add r1, r1, #0x2
	cmp r0, r1
	beq _02004630
	add r0, r7, #0x0
	mov r1, #0x4
	bl FUN_02003FA8
	bl ErrorHandling
	b _02004638
_02004630:
	ldrh r0, [r4, #0x0]
	mov r1, #0x4
	bl FUN_02003FA8
_02004638:
	mov r0, #0x1a
	bl FUN_02003D38
	bl FUN_02003F3C
_02004642:
	pop {r3-r7, pc}
	.balign 4
_02004644: .word 0x000003E9

	thumb_func_start FUN_02004648
FUN_02004648: ; 0x02004648
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_020051AC
	mov r0, #0x2
	bl FUN_02004748
	bl FUN_02003F64
	mov r0, #0x5
	bl FUN_02004180
	mov r0, #0x19
	bl FUN_02003D38
	bl FUN_02003F3C
	mov r0, #0x1
	bl FUN_02004DBC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004680
FUN_02004680: ; 0x02004680
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_0200541C
	bl FUN_02004810
	mov r0, #0x4
	bl FUN_020044A8
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}

	thumb_func_start FUN_020046A0
FUN_020046A0: ; 0x020046A0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_0200541C
	mov r0, #0x6
	bl FUN_020044A8
	mov r0, #0x1
	bl FUN_02004DBC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020046C4
FUN_020046C4: ; 0x020046C4
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x17
	bl FUN_02003D38
	bl FUN_0200541C
	mov r0, #0x7
	bl FUN_020044A8
	mov r0, #0x1
	bl FUN_02004DBC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020046E8
FUN_020046E8: ; 0x020046E8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02004738
	add r0, r4, #0x0
	bl FUN_02004180
	mov r0, #0x1b
	bl FUN_02003D38
	bl FUN_02003F3C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004704
FUN_02004704: ; 0x02004704
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x17
	add r4, r1, #0x0
	bl FUN_02003D38
	bl FUN_0200541C
	add r0, r5, #0x0
	bl FUN_020044A8
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02004724
FUN_02004724: ; 0x02004724
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	bl FUN_020051AC
	add r0, r4, #0x0
	bl FUN_0200521C
	pop {r4, pc}

	thumb_func_start FUN_02004738
FUN_02004738: ; 0x02004738
	push {r3, lr}
	mov r0, #0x4
	bl FUN_02004748
	bl FUN_02003F64
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004748
FUN_02004748: ; 0x02004748
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02003D30
	cmp r4, #0x7
	blt _02004762
	bl ErrorHandling
	mov r0, #0x1a
	bl FUN_02003D38
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
_02004762:
	cmp r4, #0x6
	bhi _020047C4
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02004772: ; jump table (using 16-bit offset)
	.short _02004780 - _02004772 - 2; case 0
	.short _0200478A - _02004772 - 2; case 1
	.short _02004794 - _02004772 - 2; case 2
	.short _0200479E - _02004772 - 2; case 3
	.short _020047A8 - _02004772 - 2; case 4
	.short _020047B2 - _02004772 - 2; case 5
	.short _020047BC - _02004772 - 2; case 6
_02004780:
	mov r0, #0x16
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_0200478A:
	mov r0, #0x17
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_02004794:
	mov r0, #0x18
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_0200479E:
	mov r0, #0x19
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_020047A8:
	mov r0, #0x1a
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_020047B2:
	mov r0, #0x1b
	bl FUN_02003D38
	add r5, r0, #0x0
	b _020047C4
_020047BC:
	mov r0, #0x1c
	bl FUN_02003D38
	add r5, r0, #0x0
_020047C4:
	ldr r0, [r5, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_020047C8
FUN_020047C8: ; 0x020047C8
	push {r4-r6, lr}
	add r5, r1, #0x0
	cmp r0, #0x1
	bne _020047DC
	mov r0, #0xb
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r4, #0x0
	b _020047EA
_020047DC:
	cmp r0, #0x7
	bne _0200480E
	mov r0, #0xc
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r4, #0x7
_020047EA:
	cmp r5, #0x0
	bne _02004800
	add r0, r4, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl FUN_02004110
_02004800:
	add r0, r4, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C0F8C
	strb r5, [r6, #0x0]
_0200480E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004810
FUN_02004810: ; 0x02004810
	push {r4, lr}
	mov r0, #0xb
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0xc
	bl FUN_02003D38
	mov r1, #0x0
	strb r1, [r4, #0x0]
	strb r1, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02004828
FUN_02004828: ; 0x02004828
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	blx FUN_020C0EF4
	pop {r3-r5, pc}

	thumb_func_start FUN_0200483C
FUN_0200483C: ; 0x0200483C
	push {r4, lr}
	add r4, r1, #0x0
	bpl _02004844
	mov r4, #0x0
_02004844:
	cmp r4, #0x7f
	ble _0200484A
	mov r4, #0x7f
_0200484A:
	bl FUN_02003FF4
	add r1, r4, #0x0
	blx FUN_020C0F30
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004858
FUN_02004858: ; 0x02004858
	push {r3-r5, lr}
	add r5, r1, #0x0
	blx FUN_020C23FC
	cmp r5, #0x1
	beq _02004868
	cmp r5, #0x8
	bne _0200486C
_02004868:
	mov r4, #0x7f
	b _02004872
_0200486C:
	cmp r0, #0x0
	beq _0200488A
	ldrb r4, [r0, #0x2]
_02004872:
	bl FUN_020313EC
	cmp r0, #0x1
	bne _0200488A
	add r0, r4, #0x0
	mov r1, #0x5
	blx _s32_div_f
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200483C
_0200488A:
	pop {r3-r5, pc}

	thumb_func_start FUN_0200488C
FUN_0200488C: ; 0x0200488C
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r1, r4, #0x0
	bl FUN_0200483C
	pop {r4, pc}

	thumb_func_start FUN_020048A0
FUN_020048A0: ; 0x020048A0
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	mov r2, #0x0
	mvn r2, r2
	add r1, r5, #0x0
	add r3, r2, #0x0
	str r4, [sp, #0x0]
	blx FUN_020C3910
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020048BC
FUN_020048BC: ; 0x020048BC
	push {r4, lr}
	add r4, r0, #0x0
	bpl _020048C6
	bl ErrorHandling
_020048C6:
	add r0, r4, #0x0
	blx FUN_020C0F50
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020048D0
FUN_020048D0: ; 0x020048D0
	push {r3, lr}
	cmp r0, #0x0
	bne _020048DA
	mov r0, #0xff
	pop {r3, pc}
_020048DA:
	blx FUN_020C23FC
	cmp r0, #0x0
	bne _020048E6
	mov r0, #0xff
	pop {r3, pc}
_020048E6:
	ldrb r0, [r0, #0x5]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020048EC
FUN_020048EC: ; 0x020048EC
	ldr r3, _020048F0 ; =FUN_020C0E14
	bx r3
	.balign 4
_020048F0: .word FUN_020C0E14

	thumb_func_start FUN_020048F4
FUN_020048F4: ; 0x020048F4
	push {r3, lr}
	bl FUN_02004900
	blx FUN_020C22D0
	pop {r3, pc}

	thumb_func_start FUN_02004900
FUN_02004900: ; 0x02004900
	push {r3, lr}
	blx FUN_020C23FC
	cmp r0, #0x0
	bne _0200490E
	mov r0, #0x0
	pop {r3, pc}
_0200490E:
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004914
FUN_02004914: ; 0x02004914
	ldr r3, _02004918 ; =MIC_StartAutoSampling
	bx r3
	.balign 4
_02004918: .word MIC_StartAutoSampling

	thumb_func_start FUN_0200491C
FUN_0200491C: ; 0x0200491C
	push {r3, lr}
	bl FUN_02003D30
	blx MIC_StopAutoSampling
	pop {r3, pc}

	thumb_func_start FUN_02004928
FUN_02004928: ; 0x02004928
	push {r3, lr}
	blx MIC_DoSamplingAsync
	pop {r3, pc}

	thumb_func_start FUN_02004930
FUN_02004930: ; 0x02004930
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _02004954
	cmp r5, #0xf
	beq _02004954
	bl ErrorHandling
_02004954:
	cmp r5, #0xe
	bne _02004962
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02004962
	bl ErrorHandling
_02004962:
	cmp r5, #0xf
	bne _02004970
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02004970
	bl ErrorHandling
_02004970:
	cmp r5, #0xe
	bne _0200497C
	mov r0, #0x0
	bl FUN_02003D38
	pop {r4-r6, pc}
_0200497C:
	mov r0, #0x1
	bl FUN_02003D38
	pop {r4-r6, pc}

	thumb_func_start FUN_02004984
FUN_02004984: ; 0x02004984
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _020049A8
	cmp r5, #0xf
	beq _020049A8
	bl ErrorHandling
_020049A8:
	cmp r5, #0xe
	bne _020049D6
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	bne _020049D0
	mov r0, #0x0
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, r5, #0x0
	blx FUN_020C0688
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020049CA
	mov r0, #0x0
	pop {r4-r6, pc}
_020049CA:
	mov r0, #0x1
	strb r0, [r6, #0x0]
	b _020049FE
_020049D0:
	bl ErrorHandling
	b _020049FE
_020049D6:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020049FA
	mov r0, #0x1
	bl FUN_02003D38
	add r6, r0, #0x0
	add r0, r5, #0x0
	blx FUN_020C0688
	str r0, [r6, #0x0]
	cmp r0, #0x0
	bne _020049F4
	mov r0, #0x0
	pop {r4-r6, pc}
_020049F4:
	mov r0, #0x1
	strb r0, [r4, #0x0]
	b _020049FE
_020049FA:
	bl ErrorHandling
_020049FE:
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02004A04
FUN_02004A04: ; 0x02004A04
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _02004A2A
	cmp r5, #0xf
	beq _02004A2A
	bl ErrorHandling
	pop {r4-r6, pc}
_02004A2A:
	cmp r5, #0xe
	bne _02004A4C
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02004A46
	add r0, r5, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	blx FUN_020C0670
	mov r0, #0x0
	strb r0, [r6, #0x0]
	pop {r4-r6, pc}
_02004A46:
	bl ErrorHandling
	pop {r4-r6, pc}
_02004A4C:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _02004A64
	add r0, r5, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	blx FUN_020C0670
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r4-r6, pc}
_02004A64:
	bl ErrorHandling
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02004A6C
FUN_02004A6C: ; 0x02004A6C
	push {r3-r5, lr}
	sub sp, #0x18
	add r3, r0, #0x0
	ldr r0, [r3, #0x10]
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r3, #0x14]
	str r0, [sp, #0x4]
	ldr r0, [r3, #0x18]
	str r0, [sp, #0x8]
	ldr r0, [r3, #0x1c]
	str r0, [sp, #0xc]
	ldr r0, [r3, #0x20]
	str r0, [sp, #0x10]
	ldr r0, [r3, #0x24]
	str r0, [sp, #0x14]
	ldr r0, [r3, #0x0]
	ldr r1, [r3, #0x4]
	ldr r2, [r3, #0x8]
	ldr r0, [r0, #0x0]
	ldr r3, [r3, #0xc]
	blx FUN_020C054C
	add r5, r0, #0x0
	bne _02004AA4
	add r0, r4, #0x0
	bl FUN_02004A04
_02004AA4:
	add r0, r5, #0x0
	add sp, #0x18
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02004AAC
FUN_02004AAC: ; 0x02004AAC
	push {r3, lr}
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	blx FUN_020C0510
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004ABC
FUN_02004ABC: ; 0x02004ABC
	push {r3, lr}
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	blx FUN_020C03B8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004ACC
FUN_02004ACC: ; 0x02004ACC
	push {r4, lr}
	add r4, r1, #0x0
	cmp r4, #0x7f
	bls _02004AD6
	mov r4, #0x7f
_02004AD6:
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	blx FUN_020C041C
	pop {r4, pc}

	thumb_func_start FUN_02004AE4
FUN_02004AE4: ; 0x02004AE4
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	blx FUN_020C044C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004AF8
FUN_02004AF8: ; 0x02004AF8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	bl FUN_020313EC
	cmp r0, #0x1
	bne _02004B20
	add r0, r4, #0x0
	bl FUN_02004930
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x5
	blx _s32_div_f
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	blx FUN_020C04DC
	pop {r3-r5, pc}
_02004B20:
	add r0, r4, #0x0
	bl FUN_02004930
	ldr r0, [r0, #0x0]
	add r1, r5, #0x0
	blx FUN_020C04DC
	pop {r3-r5, pc}

	thumb_func_start FUN_02004B30
FUN_02004B30: ; 0x02004B30
	push {r3-r7, lr}
	sub sp, #0x30
	add r6, r0, #0x0
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r5, r3, #0x0
	bl FUN_02003D30
	mov r0, #0x21
	bl FUN_02003D38
	add r4, r0, #0x0
	cmp r5, #0xe
	beq _02004B54
	cmp r5, #0xf
	beq _02004B54
	bl ErrorHandling
_02004B54:
	add r0, r6, #0x0
	blx FUN_020C226C
	add r7, r0, #0x0
	bne _02004B68
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004B68:
	ldr r0, [r7, #0x0]
	lsl r0, r0, #0x8
	lsr r0, r0, #0x8
	blx FUN_020C217C
	add r6, r0, #0x0
	bne _02004B80
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004B80:
	cmp r5, #0xe
	bne _02004BCE
	ldr r0, [sp, #0x48]
	add r1, r6, #0x0
	bl FUN_02016998
	str r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02004B9C
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004B9C:
	mov r1, #0x0
	add r2, r6, #0x0
	blx Call_FillMemWithValue
	ldr r0, [r7, #0x0]
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x8
	lsr r0, r0, #0x8
	add r2, r6, #0x0
	mov r3, #0x0
	blx FUN_020C2104
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	bne _02004BC6
	bl ErrorHandling
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02004BC6:
	ldr r0, [r4, #0x0]
	add r1, r6, #0x0
	bl FUN_02004C1C
_02004BCE:
	add r0, r5, #0x0
	bl FUN_02004930
	mov r1, #0x0
	str r1, [sp, #0xc]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x10]
	ldr r0, _02004C18 ; =0x00003443
	str r1, [sp, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x18]
	str r0, [sp, #0x24]
	mov r0, #0x6
	lsl r0, r0, #0xc
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x4]
	add r1, r5, #0x0
	str r0, [sp, #0x2c]
	add r0, sp, #0x8
	str r6, [sp, #0x1c]
	bl FUN_02004A6C
	add r4, r0, #0x0
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02004AF8
	mov r0, #0xe
	bl FUN_02003D38
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02004C18: .word 0x00003443

	thumb_func_start FUN_02004C1C
FUN_02004C1C: ; 0x02004C1C
	push {r3-r6}
	mov r5, #0x0
	lsr r6, r1, #0x1
	beq _02004C36
	sub r2, r1, #0x1
_02004C26:
	sub r3, r2, r5
	ldrb r4, [r0, r5]
	ldrb r1, [r0, r3]
	strb r1, [r0, r5]
	add r5, r5, #0x1
	strb r4, [r0, r3]
	cmp r5, r6
	blo _02004C26
_02004C36:
	pop {r3-r6}
	bx lr
	.balign 4

	thumb_func_start FUN_02004C3C
FUN_02004C3C: ; 0x02004C3C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_02003D30
	mov r0, #0xe
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x21
	bl FUN_02003D38
	add r6, r0, #0x0
	cmp r5, #0xe
	beq _02004C60
	cmp r5, #0xf
	beq _02004C60
	bl ErrorHandling
_02004C60:
	add r0, r5, #0x0
	bl FUN_02004AAC
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _02004C76
	mov r0, #0x0
	strb r0, [r4, #0x0]
	ldr r0, [r6, #0x0]
	bl FUN_02016A18
_02004C76:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004C78
FUN_02004C78: ; 0x02004C78
	ldr r3, _02004C7C ; =FUN_020C1E58
	bx r3
	.balign 4
_02004C7C: .word FUN_020C1E58

	thumb_func_start FUN_02004C80
FUN_02004C80: ; 0x02004C80
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_02003D30
	mov r0, #0x3
	bl FUN_02003D38
	mov r1, #0x1
	mov r3, #0xfa
	lsl r1, r1, #0xc
	mov r2, #0x0
	lsl r3, r3, #0x6
	str r4, [sp, #0x0]
	blx FUN_020C1FF0
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_02004CA4
FUN_02004CA4: ; 0x02004CA4
	ldr r3, _02004CA8 ; =FUN_020C1F54
	bx r3
	.balign 4
_02004CA8: .word FUN_020C1F54

	thumb_func_start FUN_02004CAC
FUN_02004CAC: ; 0x02004CAC
	ldr r3, _02004CB0 ; =FUN_020C1FA4
	bx r3
	.balign 4
_02004CB0: .word FUN_020C1FA4

	thumb_func_start FUN_02004CB4
FUN_02004CB4: ; 0x02004CB4
	push {r3-r4, lr}
	sub sp, #0xc
	bl FUN_02003D30
	mov r0, #0x4
	bl FUN_02003D38
	mov r1, #0x0
	mov r2, #0x1c
	blx MI_CpuFill8
	mov r0, #0x3
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x4
	bl FUN_02003D38
	mov r2, #0x2
	ldr r1, _02004CF4 ; =FUN_02005068
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	lsl r1, r2, #0xb
	ldr r3, _02004CF8 ; =0x000055F0
	add r0, r4, #0x0
	mov r2, #0x0
	blx FUN_020C1EA4
	add sp, #0xc
	pop {r3-r4, pc}
	nop
_02004CF4: .word FUN_02005068 
_02004CF8: .word 0x000055F0

	thumb_func_start FUN_02004CFC
FUN_02004CFC: ; 0x02004CFC
	ldr r3, _02004D00 ; =FUN_020C1E68
	bx r3
	.balign 4
_02004D00: .word FUN_020C1E68

	thumb_func_start FUN_02004D04
FUN_02004D04: ; 0x02004D04
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x13
	bl FUN_02003D38
	cmp r4, #0x8
	ble _02004D16
	mov r4, #0x8
	b _02004D1C
_02004D16:
	cmp r4, #0x0
	bge _02004D1C
	mov r4, #0x0
_02004D1C:
	strb r4, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02004D20
FUN_02004D20: ; 0x02004D20
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	blx FUN_020C0EA4
	pop {r3-r5, pc}

	thumb_func_start FUN_02004D34
FUN_02004D34: ; 0x02004D34
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02004D20
	pop {r3-r5, pc}

	thumb_func_start FUN_02004D4C
FUN_02004D4C: ; 0x02004D4C
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	blx FUN_020C0E7C
	pop {r3-r5, pc}

	thumb_func_start FUN_02004D60
FUN_02004D60: ; 0x02004D60
	push {r4, lr}
	add r4, r0, #0x0
	blx FUN_020C0174
	ldr r0, _02004D70 ; =0x021C3DD8
	str r4, [r0, #0x0]
	pop {r4, pc}
	nop
_02004D70: .word 0x021C3DD8

	thumb_func_start FUN_02004D74
FUN_02004D74: ; 0x02004D74
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x6
	bl FUN_02003D38
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004D84
FUN_02004D84: ; 0x02004D84
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x7
	bl FUN_02003D38
	str r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004D94
FUN_02004D94: ; 0x02004D94
	push {r3, lr}
	mov r0, #0x7
	bl FUN_02003D38
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	bne _02004DAA
	mov r1, #0x0
	strh r1, [r0, #0x0]
	add r0, r1, #0x0
	pop {r3, pc}
_02004DAA:
	sub r1, r1, #0x1
	strh r1, [r0, #0x0]
	ldrh r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02004DB4
FUN_02004DB4: ; 0x02004DB4
	ldr r0, _02004DB8 ; =0x021C3DE0
	bx lr
	.balign 4
_02004DB8: .word 0x021C3DE0

	thumb_func_start FUN_02004DBC
FUN_02004DBC: ; 0x02004DBC
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x12
	bl FUN_02003D38
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02004DCC
FUN_02004DCC: ; 0x02004DCC
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x15
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02004E44
	mov r0, #0x0
	strb r0, [r4, #0x0]
	mov r0, #0x5
	bl FUN_02003CE8
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02004E08
FUN_02004E08: ; 0x02004E08
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	mov r0, #0x8
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x8]
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x14]
	ldr r3, [sp, #0x8]
	add r1, r6, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x28]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02004E44
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x0]
	mov r0, #0x6
	bl FUN_02003CE8
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02004E44
FUN_02004E44: ; 0x02004E44
	push {r3-r7, lr}
	add r6, r2, #0x0
	mov r0, #0x2
	add r5, r1, #0x0
	add r7, r3, #0x0
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	bl FUN_020053CC
	mov r0, #0x0
	bl FUN_02004110
	add r0, r5, #0x0
	bl FUN_02004130
	add r0, r7, #0x0
	bl FUN_02004D84
	add r0, r5, #0x0
	bl FUN_020048F4
	str r0, [r4, #0x0]
	add r0, sp, #0x8
	ldrb r0, [r0, #0x10]
	bl FUN_02004DBC
	pop {r3-r7, pc}

	thumb_func_start FUN_02004E80
FUN_02004E80: ; 0x02004E80
	cmp r0, #0x0
	bne _02004E88
	mov r0, #0x0
	bx lr
_02004E88:
	add r0, #0xc
	bx lr

	thumb_func_start FUN_02004E8C
FUN_02004E8C: ; 0x02004E8C
	cmp r0, #0x0
	bne _02004E94
	mov r0, #0x0
	bx lr
_02004E94:
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_02004E98
FUN_02004E98: ; 0x02004E98
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x5
	bl FUN_02004748
	bl FUN_02003F64
	lsl r0, r5, #0x10
	lsr r4, r0, #0x10
	ldr r0, _02004ECC ; =0x000001B9
	cmp r4, r0
	beq _02004EBC
	add r0, #0x36
	cmp r5, r0
	bgt _02004EBA
	cmp r5, #0x0
	bne _02004EBC
_02004EBA:
	mov r4, #0x1
_02004EBC:
	add r0, r4, #0x0
	bl FUN_02003FC4
	add r0, r4, #0x0
	bl FUN_02004ED0
	pop {r3-r5, pc}
	nop
_02004ECC: .word 0x000001B9

	thumb_func_start FUN_02004ED0
FUN_02004ED0: ; 0x02004ED0
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x20
	bl FUN_02003D38
	add r4, r0, #0x0
	lsl r0, r5, #0x10
	ldr r1, _02004F24 ; =0x000001B9
	lsr r0, r0, #0x10
	cmp r0, r1
	beq _02004EF2
	add r1, #0x36
	cmp r5, r1
	bgt _02004EF0
	cmp r5, #0x0
	bne _02004EF2
_02004EF0:
	mov r0, #0x1
_02004EF2:
	blx FUN_020C226C
	cmp r0, #0x0
	bne _02004F02
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_02004F02:
	ldr r0, [r0, #0x0]
	lsl r0, r0, #0x8
	lsr r0, r0, #0x8
	blx FUN_020C20DC
	cmp r0, #0x0
	bne _02004F18
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_02004F18:
	mov r1, #0x0
	blx SND_GetWaveDataAddress
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	nop
_02004F24: .word 0x000001B9

	thumb_func_start FUN_02004F28
FUN_02004F28: ; 0x02004F28
	push {r4-r6, lr}
	mov r0, #0x1
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02004F64
	mov r1, #0x3
	add r4, r0, #0x0
	add r0, r6, #0x0
	lsl r1, r1, #0x8
	ldr r5, [r5, #0x8]
	blx _s32_div_f
	lsl r1, r0, #0x1
	bpl _02004F50
	mov r0, #0x20
	blx _s32_div_f
	neg r0, r0
	b _02004F5A
_02004F50:
	cmp r1, #0x0
	bne _02004F58
	mov r0, #0x20
	b _02004F5A
_02004F58:
	lsl r0, r1, #0x5
_02004F5A:
	mul r0, r4
	cmp r0, r5
	blo _02004F62
	mov r0, #0x0
_02004F62:
	pop {r4-r6, pc}

	thumb_func_start FUN_02004F64
FUN_02004F64: ; 0x02004F64
	push {r3, lr}
	bl FUN_02003FF4
	blx FUN_020C0DD4
	pop {r3, pc}

	thumb_func_start FUN_02004F70
FUN_02004F70: ; 0x02004F70
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r4, r1, #0x0
	add r6, r2, #0x0
	ldr r1, [sp, #0x0]
	mov r0, #0x1
	add r2, r3, #0x0
	bl FUN_02004F28
	add r1, r0, #0x0
	mov r12, r0
	sub r1, #0x64
	bpl _02004F8E
	mov r1, #0x0
_02004F8E:
	ldr r0, [sp, #0x0]
	mov r3, #0x0
	add r0, r0, r1
	ldrb r0, [r0, #0xc]
	add r7, r3, #0x0
	cmp r0, #0x80
	bhs _02004FA0
	mov r0, #0x1
	b _02004FA2
_02004FA0:
	sub r0, r3, #0x1
_02004FA2:
	lsl r0, r0, #0x18
	asr r5, r0, #0x18
	mov r0, r12
	cmp r1, r0
	bhs _02005022
_02004FAC:
	mov r0, #0x0
	cmp r5, #0x0
	ble _02004FC6
	ldr r2, [sp, #0x0]
	add r2, r2, r1
	str r2, [sp, #0x4]
	ldrb r2, [r2, #0xc]
	cmp r2, #0x80
	bls _02004FC2
	mov r0, #0x1
	b _02004FD8
_02004FC2:
	add r3, r3, #0x1
	b _02004FD8
_02004FC6:
	ldr r2, [sp, #0x0]
	add r2, r2, r1
	str r2, [sp, #0x4]
	ldrb r2, [r2, #0xc]
	cmp r2, #0x80
	bhs _02004FD6
	mov r0, #0x1
	b _02004FD8
_02004FD6:
	add r3, r3, #0x1
_02004FD8:
	cmp r0, #0x1
	bne _0200501A
	ldr r5, _02005064 ; =0x020ECB8C
	mov r2, #0x0
_02004FE0:
	ldrb r0, [r5, #0x0]
	cmp r3, r0
	bge _02004FEA
	add r7, r2, #0x0
	b _02004FF2
_02004FEA:
	add r2, r2, #0x1
	add r5, r5, #0x1
	cmp r2, #0x9
	blt _02004FE0
_02004FF2:
	cmp r7, r6
	blt _02004FF8
	sub r7, r6, #0x1
_02004FF8:
	cmp r3, #0x0
	beq _02005006
	sub r0, r6, #0x1
	sub r0, r0, r7
	ldrb r2, [r4, r0]
	add r2, r2, #0x1
	strb r2, [r4, r0]
_02005006:
	ldr r0, [sp, #0x4]
	mov r3, #0x0
	ldrb r0, [r0, #0xc]
	cmp r0, #0x80
	bhs _02005014
	mov r0, #0x1
	b _02005016
_02005014:
	sub r0, r3, #0x1
_02005016:
	lsl r0, r0, #0x18
	asr r5, r0, #0x18
_0200501A:
	add r1, r1, #0x2
	mov r0, r12
	cmp r1, r0
	blo _02004FAC
_02005022:
	mov r2, #0x0
	cmp r6, #0x0
	ble _02005038
	mov r0, #0x9
_0200502A:
	ldrb r1, [r4, r2]
	cmp r1, #0xa
	blo _02005032
	strb r0, [r4, r2]
_02005032:
	add r2, r2, #0x1
	cmp r2, r6
	blt _0200502A
_02005038:
	sub r2, r6, #0x1
	mov r3, #0x0
	cmp r2, #0x0
	ble _02005060
_02005040:
	ldrb r0, [r4, r3]
	add r1, r4, r3
	cmp r0, #0x0
	bne _0200505A
	ldrb r0, [r1, #0x1]
	cmp r0, #0x0
	beq _0200505A
	add r0, r3, #0x1
	ldrb r0, [r4, r0]
	add sp, #0x8
	lsr r0, r0, #0x1
	strb r0, [r1, #0x0]
	pop {r3-r7, pc}
_0200505A:
	add r3, r3, #0x1
	cmp r3, r2
	blt _02005040
_02005060:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02005064: .word 0x020ECB8C

	thumb_func_start FUN_02005068
FUN_02005068: ; 0x02005068
	push {r3-r7, lr}
	sub sp, #0x30
	add r5, r0, #0x0
	ldr r0, [sp, #0x48]
	add r6, r1, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x13
	str r2, [sp, #0x0]
	add r4, r3, #0x0
	bl FUN_02003D38
	add r7, r0, #0x0
	cmp r4, #0x1
	beq _0200508A
	ldr r0, [sp, #0x0]
	lsr r0, r0, #0x1
	str r0, [sp, #0x0]
_0200508A:
	ldrb r2, [r7, #0x0]
	cmp r2, #0x0
	beq _0200515A
	mov r0, #0x0
	cmp r2, #0x0
	ble _020050BC
	add r1, sp, #0x10
_02005098:
	ldr r3, [sp, #0x0]
	sub r2, r3, r2
	add r2, r0, r2
	lsl r2, r2, #0x1
	ldrsh r2, [r5, r2]
	strh r2, [r1, #0x0]
	ldrb r3, [r7, #0x0]
	ldr r2, [sp, #0x0]
	sub r2, r2, r3
	add r2, r0, r2
	lsl r2, r2, #0x1
	ldrsh r2, [r6, r2]
	add r0, r0, #0x1
	strh r2, [r1, #0x2]
	ldrb r2, [r7, #0x0]
	add r1, r1, #0x4
	cmp r0, r2
	blt _02005098
_020050BC:
	ldr r0, [sp, #0x0]
	sub r4, r0, #0x1
	sub r0, r2, #0x1
	cmp r4, r0
	blt _02005126
	lsl r1, r4, #0x1
	add r0, r5, r1
	str r0, [sp, #0x8]
	add r0, r6, r1
	str r0, [sp, #0x4]
_020050D0:
	mov r0, #0x0
	add r1, r0, #0x0
	cmp r2, #0x0
	ble _020050E6
_020050D8:
	sub r3, r4, r1
	lsl r3, r3, #0x1
	ldrsh r3, [r5, r3]
	add r1, r1, #0x1
	add r0, r0, r3
	cmp r1, r2
	blt _020050D8
_020050E6:
	add r1, r2, #0x0
	blx _s32_div_f
	ldr r1, [sp, #0x8]
	strh r0, [r1, #0x0]
	mov r0, #0x0
	ldrb r1, [r7, #0x0]
	add r2, r0, #0x0
	cmp r1, #0x0
	ble _02005108
_020050FA:
	sub r3, r4, r2
	lsl r3, r3, #0x1
	ldrsh r3, [r6, r3]
	add r2, r2, #0x1
	add r0, r0, r3
	cmp r2, r1
	blt _020050FA
_02005108:
	blx _s32_div_f
	ldr r1, [sp, #0x4]
	sub r4, r4, #0x1
	strh r0, [r1, #0x0]
	ldr r0, [sp, #0x8]
	ldrb r2, [r7, #0x0]
	sub r0, r0, #0x2
	str r0, [sp, #0x8]
	add r0, r1, #0x0
	sub r0, r0, #0x2
	str r0, [sp, #0x4]
	sub r0, r2, #0x1
	cmp r4, r0
	bge _020050D0
_02005126:
	mov r1, #0x0
	cmp r2, #0x0
	ble _0200514A
	add r0, sp, #0x10
	mov r4, #0x2
_02005130:
	mov r2, #0x0
	ldrsh r3, [r0, r2]
	ldr r2, [sp, #0xc]
	add r1, r1, #0x1
	strh r3, [r2, #0x0]
	ldrsh r3, [r0, r4]
	add r0, r0, #0x4
	strh r3, [r2, #0x2]
	add r2, r2, #0x4
	str r2, [sp, #0xc]
	ldrb r2, [r7, #0x0]
	cmp r1, r2
	blt _02005130
_0200514A:
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	blx DC_FlushRange
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	blx DC_FlushRange
_0200515A:
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02005160
FUN_02005160: ; 0x02005160
	ldr r3, _02005168 ; =FUN_020C1148
	add r1, r0, #0x0
	mov r0, #0x7
	bx r3
	.balign 4
_02005168: .word FUN_020C1148

	thumb_func_start FUN_0200516C
FUN_0200516C: ; 0x0200516C
	push {r3, lr}
	cmp r0, #0x0
	bne _02005180
	ldr r0, _020051A4 ; =0x000007FF
	bl FUN_02005160
	mov r0, #0x0
	bl FUN_02004CA4
	b _0200519C
_02005180:
	cmp r0, #0x1
	ldr r0, _020051A8 ; =0x00007FFF
	bne _02005192
	bl FUN_02005160
	mov r0, #0x1e
	bl FUN_02004C80
	b _0200519C
_02005192:
	bl FUN_02005160
	mov r0, #0xf
	bl FUN_02004C80
_0200519C:
	bl FUN_02004C78
	pop {r3, pc}
	nop
_020051A4: .word 0x000007FF
_020051A8: .word 0x00007FFF

	thumb_func_start FUN_020051AC
FUN_020051AC: ; 0x020051AC
	push {r3, lr}
	bl FUN_02005404
	cmp r0, #0x0
	bne _020051E0
	mov r0, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _020051E0
	bl FUN_02004124
	ldr r1, _020051E8 ; =0x0000047E
	cmp r0, r1
	beq _020051E0
	bl FUN_02005454
	mov r0, #0x1
	add r1, r0, #0x0
	bl FUN_020047C8
	pop {r3, pc}
_020051E0:
	bl FUN_0200541C
	pop {r3, pc}
	nop
_020051E8: .word 0x0000047E

	thumb_func_start FUN_020051EC
FUN_020051EC: ; 0x020051EC
	ldr r3, _020051F0 ; =FUN_020C1180
	bx r3
	.balign 4
_020051F0: .word FUN_020C1180

	thumb_func_start FUN_020051F4
FUN_020051F4: ; 0x020051F4
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r4, r0, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C3980
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_0200526C
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200521C
FUN_0200521C: ; 0x0200521C
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020048D0
	add r4, r0, #0x0
	bl FUN_02004018
	add r6, r0, #0x0
	cmp r4, #0x7
	bne _0200523E
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02005288
	add r4, r0, #0x0
	b _02005258
_0200523E:
	cmp r4, #0x1
	bne _02005250
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020052B8
	add r4, r0, #0x0
	b _02005258
_02005250:
	bl ErrorHandling
	mov r0, #0x0
	pop {r4-r6, pc}
_02005258:
	mov r0, #0x0
	bl FUN_02004DBC
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_0200526C
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200526C
FUN_0200526C: ; 0x0200526C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02004110
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02004858
	mov r0, #0x1
	bl FUN_02003CE8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02005288
FUN_02005288: ; 0x02005288
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x3
	add r4, r2, #0x0
	bl FUN_02004748
	bl FUN_02003F64
	add r0, r5, #0x0
	bl FUN_02003F90
	mov r0, #0x1a
	bl FUN_02003D38
	bl FUN_02003F3C
	add r0, r4, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C3980
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020052B8
FUN_020052B8: ; 0x020052B8
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x12
	add r6, r2, #0x0
	bl FUN_02003D38
	mov r0, #0x1f
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x0
	bl FUN_02003FF4
	bl FUN_020048EC
	bl FUN_02004900
	add r1, r0, #0x0
	add r0, r5, #0x0
	bl FUN_020045C4
	add r0, r6, #0x0
	bl FUN_02003FF4
	add r6, r0, #0x0
	ldrh r0, [r4, #0x0]
	bl FUN_02004900
	mov r1, #0x0
	mvn r1, r1
	add r2, r0, #0x0
	add r0, r6, #0x0
	add r3, r1, #0x0
	str r5, [sp, #0x0]
	blx FUN_020C3910
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02005308
FUN_02005308: ; 0x02005308
	push {r3-r5, lr}
	add r5, r1, #0x0
	cmp r0, #0x4
	beq _02005318
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_02005318:
	add r0, r5, #0x0
	bl FUN_020048D0
	cmp r0, #0x7
	beq _0200532A
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r5, pc}
_0200532A:
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02003FA8
	mov r0, #0x7
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C3980
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02004110
	mov r0, #0x1
	bl FUN_02003CE8
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02005350
FUN_02005350: ; 0x02005350
	push {r4, lr}
	add r4, r0, #0x0
	blx FUN_020C0FDC
	add r0, r4, #0x0
	bl FUN_020048D0
	cmp r0, #0xff
	beq _0200536E
	bl FUN_02004018
	bl FUN_02003FF4
	blx FUN_020C0F68
_0200536E:
	bl FUN_02005374
	pop {r4, pc}

	thumb_func_start FUN_02005374
FUN_02005374: ; 0x02005374
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02004110
	mov r0, #0x0
	bl FUN_02004130
	mov r0, #0x0
	bl FUN_02003CE8
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0200538C
FUN_0200538C: ; 0x0200538C
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_02004124
	bl FUN_020048D0
	cmp r0, #0xff
	beq _020053C8
	bl FUN_02004018
	add r7, r0, #0x0
	cmp r4, #0x0
	bne _020053B2
	mov r1, #0x0
	add r2, r1, #0x0
	bl FUN_02004828
_020053B2:
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02004828
	add r0, r5, #0x0
	bl FUN_02004D74
	mov r0, #0x3
	bl FUN_02003CE8
_020053C8:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020053CC
FUN_020053CC: ; 0x020053CC
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02004124
	bl FUN_020048D0
	add r6, r0, #0x0
	cmp r6, #0xff
	beq _02005402
	bl FUN_02005404
	cmp r0, #0x0
	bne _020053FC
	add r0, r6, #0x0
	bl FUN_02004018
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02004828
	add r0, r4, #0x0
	bl FUN_02004D74
_020053FC:
	mov r0, #0x4
	bl FUN_02003CE8
_02005402:
	pop {r4-r6, pc}

	thumb_func_start FUN_02005404
FUN_02005404: ; 0x02005404
	push {r3, lr}
	mov r0, #0x6
	bl FUN_02003D38
	ldrh r0, [r0, #0x0]
	pop {r3, pc}

	thumb_func_start FUN_02005410
FUN_02005410: ; 0x02005410
	push {r3, lr}
	bl FUN_020048D0
	bl FUN_020048BC
	pop {r3, pc}

	thumb_func_start FUN_0200541C
FUN_0200541C: ; 0x0200541C
	push {r3-r5, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r5, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x0
	blx FUN_020C0F9C
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02005440
	mov r0, #0xe
	bl FUN_02004AAC
_02005440:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _0200544C
	mov r0, #0xf
	bl FUN_02004AAC
_0200544C:
	mov r0, #0x0
	bl FUN_02003CE8
	pop {r3-r5, pc}

	thumb_func_start FUN_02005454
FUN_02005454: ; 0x02005454
	push {r3-r7, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r7, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x7
	bl FUN_02003FF4
	mov r1, #0x0
	blx FUN_020C10A4
	bl FUN_02005374
	mov r5, #0x0
	add r4, r5, #0x0
_0200547A:
	add r0, r5, #0x3
	add r1, r4, #0x0
	bl FUN_020054F8
	add r5, r5, #0x1
	cmp r5, #0x4
	blt _0200547A
	mov r0, #0x0
	bl FUN_02005614
	ldrb r0, [r7, #0x0]
	cmp r0, #0x1
	bne _0200549A
	mov r0, #0xe
	bl FUN_02004AAC
_0200549A:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _020054A6
	mov r0, #0xf
	bl FUN_02004AAC
_020054A6:
	pop {r3-r7, pc}

	thumb_func_start FUN_020054A8
FUN_020054A8: ; 0x020054A8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020054C8
	add r6, r0, #0x0
	ldr r1, _020054C4 ; =0x0000FFFF
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02005530
	add r0, r6, #0x0
	pop {r4-r6, pc}
	nop
_020054C4: .word 0x0000FFFF

	thumb_func_start FUN_020054C8
FUN_020054C8: ; 0x020054C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	add r4, r0, #0x0
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C3980
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02004858
	add r0, r6, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020054F0
FUN_020054F0: ; 0x020054F0
	ldr r3, _020054F4 ; =FUN_020C0FDC
	bx r3
	.balign 4
_020054F4: .word FUN_020C0FDC

	thumb_func_start FUN_020054F8
FUN_020054F8: ; 0x020054F8
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02003FF4
	add r1, r4, #0x0
	blx FUN_020C10A4
	pop {r4, pc}

	thumb_func_start FUN_02005508
FUN_02005508: ; 0x02005508
	push {r3, lr}
	bl FUN_020048D0
	bl FUN_020048BC
	pop {r3, pc}

	thumb_func_start FUN_02005514
FUN_02005514: ; 0x02005514
	push {r4, lr}
	mov r4, #0x0
_02005518:
	add r0, r4, #0x3
	bl FUN_020048BC
	cmp r0, #0x1
	bne _02005526
	mov r0, #0x1
	pop {r4, pc}
_02005526:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02005518
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02005530
FUN_02005530: ; 0x02005530
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020048D0
	bl FUN_02004018
	bl FUN_02003FF4
	add r1, r5, #0x0
	add r2, r4, #0x0
	blx FUN_020C0E7C
	pop {r3-r5, pc}

	thumb_func_start FUN_0200554C
FUN_0200554C: ; 0x0200554C
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x3
	bl FUN_02004018
	ldr r7, _02005574 ; =0x0000FFFF
	add r4, r0, #0x0
	mov r5, #0x0
_0200555C:
	add r0, r4, r5
	bl FUN_02003FF4
	add r1, r7, #0x0
	add r2, r6, #0x0
	blx FUN_020C0E7C
	add r5, r5, #0x1
	cmp r5, #0x4
	blt _0200555C
	pop {r3-r7, pc}
	nop
_02005574: .word 0x0000FFFF

	thumb_func_start FUN_02005578
FUN_02005578: ; 0x02005578
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x11
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x23
	bl FUN_02003D38
	ldr r1, _02005610 ; =0x000001B9
	cmp r5, r1
	beq _0200559C
	add r1, #0x36
	cmp r5, r1
	bhi _0200559A
	cmp r5, #0x0
	bne _0200559C
_0200559A:
	mov r5, #0x1
_0200559C:
	ldr r1, _02005610 ; =0x000001B9
	cmp r5, r1
	bne _020055BC
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	mov r2, #0x7f
	add r3, r1, #0x0
	bl FUN_02005D48
	cmp r0, #0x1
	bne _020055BC
	mov r0, #0x0
	bl FUN_02005E80
	mov r0, #0x1
	pop {r3-r5, pc}
_020055BC:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	bne _020055E8
	mov r0, #0x0
	bl FUN_02005614
	mov r0, #0x1
	bl FUN_02003FF4
	mov r1, #0x2
	str r1, [sp, #0x0]
	sub r1, r1, #0x3
	add r2, r5, #0x0
	add r3, r1, #0x0
	blx FUN_020C3910
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02004858
	b _02005606
_020055E8:
	mov r0, #0x8
	bl FUN_02003FF4
	mov r1, #0x2
	str r1, [sp, #0x0]
	sub r1, r1, #0x3
	add r2, r5, #0x0
	add r3, r1, #0x0
	blx FUN_020C3910
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl FUN_02004858
_02005606:
	mov r0, #0x0
	bl FUN_02005E80
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02005610: .word 0x000001B9

	thumb_func_start FUN_02005614
FUN_02005614: ; 0x02005614
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0xf
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0xe
	bl FUN_02003D38
	mov r0, #0x1
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C10A4
	mov r0, #0x8
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C10A4
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02005658
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005658:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _0200566A
	mov r0, #0xf
	bl FUN_02004C3C
	mov r0, #0xf
	bl FUN_02004A04
_0200566A:
	bl FUN_02005DFC
	pop {r4-r6, pc}

	thumb_func_start FUN_02005670
FUN_02005670: ; 0x02005670
	push {r3-r5, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r5, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0xe
	bl FUN_02003D38
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02005696
	mov r0, #0xe
	bl FUN_02004ABC
	pop {r3-r5, pc}
_02005696:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _020056A4
	mov r0, #0xf
	bl FUN_02004ABC
	pop {r3-r5, pc}
_020056A4:
	mov r0, #0x0
	bl FUN_020048BC
	pop {r3-r5, pc}

	thumb_func_start FUN_020056AC
FUN_020056AC: ; 0x020056AC
	push {r3-r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x4]
	mov r0, #0xf
	str r1, [sp, #0x8]
	add r5, r2, #0x0
	add r6, r3, #0x0
	ldr r7, [sp, #0x38]
	bl FUN_02003D38
	str r0, [sp, #0x14]
	mov r0, #0x10
	bl FUN_02003D38
	str r0, [sp, #0x10]
	mov r0, #0x11
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x1d
	bl FUN_02003D38
	str r0, [sp, #0xc]
	mov r0, #0x23
	bl FUN_02003D38
	lsr r0, r5, #0x1f
	add r0, r5, r0
	asr r0, r0, #0x1
	str r0, [sp, #0x1c]
	add r0, #0x40
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	str r0, [sp, #0x18]
	sub r0, #0x1e
	str r0, [sp, #0x18]
	cmp r0, #0x0
	bgt _020056FC
	mov r0, #0x1
	str r0, [sp, #0x18]
_020056FC:
	mov r0, #0x0
	strb r0, [r4, #0x0]
	ldr r0, [sp, #0x14]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02005714
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005714:
	ldr r0, [sp, #0x10]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02005728
	mov r0, #0xf
	bl FUN_02004C3C
	mov r0, #0xf
	bl FUN_02004A04
_02005728:
	ldr r4, [sp, #0x8]
	ldr r0, _02005AB4 ; =0x000001B9
	add r1, r4, #0x0
	cmp r1, r0
	beq _0200573E
	add r0, #0x36
	cmp r1, r0
	bhi _0200573C
	add r0, r4, #0x0
	bne _0200573E
_0200573C:
	mov r4, #0x1
_0200573E:
	ldr r0, _02005AB4 ; =0x000001B9
	ldr r1, [sp, #0x8]
	cmp r1, r0
	bne _020057B4
	ldr r1, [sp, #0x4]
	cmp r1, #0xc
	bhi _020057AE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02005758: ; jump table (using 16-bit offset)
	.short _02005772 - _02005758 - 2; case 0
	.short _02005772 - _02005758 - 2; case 1
	.short _02005772 - _02005758 - 2; case 2
	.short _020057AE - _02005758 - 2; case 3
	.short _020057AE - _02005758 - 2; case 4
	.short _02005772 - _02005758 - 2; case 5
	.short _020057AE - _02005758 - 2; case 6
	.short _020057AE - _02005758 - 2; case 7
	.short _020057AE - _02005758 - 2; case 8
	.short _020057AE - _02005758 - 2; case 9
	.short _020057AE - _02005758 - 2; case 10
	.short _02005772 - _02005758 - 2; case 11
	.short _02005772 - _02005758 - 2; case 12
_02005772:
	bl FUN_02005578
	ldr r0, [sp, #0xc]
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02005794
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	b _020057A8
_02005794:
	ldr r1, [sp, #0x1c]
	mov r0, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02004ACC
	mov r0, #0xe
	add r1, r6, #0x0
	bl FUN_02004AF8
_020057A8:
	add sp, #0x20
	mov r0, #0x1
	pop {r3-r7, pc}
_020057AE:
	mov r0, #0x1
	bl FUN_02005E80
_020057B4:
	ldr r0, [sp, #0x4]
	cmp r0, #0xe
	bls _020057BC
	b _02005AC2
_020057BC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020057C8: ; jump table (using 16-bit offset)
	.short _020057E6 - _020057C8 - 2; case 0
	.short _02005802 - _020057C8 - 2; case 1
	.short _02005826 - _020057C8 - 2; case 2
	.short _02005868 - _020057C8 - 2; case 3
	.short _020058B2 - _020057C8 - 2; case 4
	.short _02005900 - _020057C8 - 2; case 5
	.short _02005928 - _020057C8 - 2; case 6
	.short _0200596C - _020057C8 - 2; case 7
	.short _0200599C - _020057C8 - 2; case 8
	.short _020059CA - _020057C8 - 2; case 9
	.short _020059FE - _020057C8 - 2; case 10
	.short _02005A2E - _020057C8 - 2; case 11
	.short _02005A56 - _020057C8 - 2; case 12
	.short _02005A86 - _020057C8 - 2; case 13
	.short _02005ABC - _020057C8 - 2; case 14
_020057E6:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	b _02005AC2
_02005802:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x14
	add r1, r7, #0x0
	bl FUN_02005AE0
	b _02005AC2
_02005826:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0x40
	bl FUN_02004D20
	add r0, r4, #0x0
	mov r1, #0x14
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	ldr r2, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02005AC8
	b _02005AC2
_02005868:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x1e
	add r1, r7, #0x0
	bl FUN_02005AE0
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0xc0
	bl FUN_02004D20
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	ldr r2, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02005AC8
	b _02005AC2
_020058B2:
	mov r0, #0xe
	bl FUN_02004984
	ldr r2, [sp, #0x1c]
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0xe
	str r7, [sp, #0x0]
	bl FUN_02004B30
	ldr r1, [sp, #0x1c]
	mov r0, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02004ACC
	mov r0, #0xf
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r1, #0x86
	mov r0, #0xe
	lsl r1, r1, #0x8
	bl FUN_02004AE4
	mov r1, #0x3f
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r4, #0x0
	mvn r1, r1
	str r7, [sp, #0x0]
	bl FUN_02005BF8
	mov r1, #0x86
	mov r0, #0xf
	lsl r1, r1, #0x8
	bl FUN_02004AE4
	b _02005AC2
_02005900:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0xe1
	bl FUN_02004D20
	b _02005AC2
_02005928:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0x2c
	bl FUN_02004D20
	mov r1, #0x3f
	add r0, r4, #0x0
	mvn r1, r1
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	ldr r2, [sp, #0x18]
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02005AC8
	b _02005AC2
_0200596C:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0xb
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x81
	bl FUN_02004D20
	b _02005AC2
_0200599C:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x3c
	add r1, r7, #0x0
	bl FUN_02005AE0
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	mov r2, #0x3c
	bl FUN_02004D20
	b _02005AC2
_020059CA:
	mov r0, #0xe
	bl FUN_02004984
	ldr r2, [sp, #0x1c]
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r3, #0xe
	str r7, [sp, #0x0]
	bl FUN_02004B30
	ldr r1, [sp, #0x1c]
	mov r0, #0xe
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl FUN_02004ACC
	mov r0, #0xd
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r1, #0x1a
	mov r0, #0xe
	lsl r1, r1, #0xa
	bl FUN_02004AE4
	b _02005AC2
_020059FE:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x64
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x2d
	bl FUN_02004D20
	b _02005AC2
_02005A2E:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x61
	bl FUN_02004D20
	b _02005AC2
_02005A56:
	add r0, r4, #0x0
	bl FUN_02005578
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x1
	add r2, r5, #0x0
	bl FUN_02004D4C
	add r0, r4, #0x0
	mov r1, #0x1
	add r2, r6, #0x0
	bl FUN_02005AC8
	mov r0, #0x14
	add r1, r7, #0x0
	bl FUN_02005AE0
	mov r0, #0x1
	add r2, r0, #0x0
	ldr r1, _02005AB8 ; =0x0000FFFF
	sub r2, #0x61
	bl FUN_02004D20
	b _02005AC2
_02005A86:
	add r0, r4, #0x0
	bl FUN_02005578
	add r0, r4, #0x0
	mov r1, #0x1
	mov r2, #0x7f
	bl FUN_02005AC8
	add r0, r4, #0x0
	mov r1, #0x14
	bl FUN_02005BC8
	ldr r1, _02005AB8 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r5, #0x0
	bl FUN_02004D4C
	mov r0, #0x8
	add r1, r6, #0x0
	mov r2, #0x0
	bl FUN_02004828
	b _02005AC2
	.balign 4
_02005AB4: .word 0x000001B9
_02005AB8: .word 0x0000FFFF
_02005ABC:
	add r0, r4, #0x0
	bl FUN_02005578
_02005AC2:
	mov r0, #0x1
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02005AC8
FUN_02005AC8: ; 0x02005AC8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r1, r2, #0x0
	bl FUN_0200483C
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02004858
	pop {r3-r5, pc}

	thumb_func_start FUN_02005AE0
FUN_02005AE0: ; 0x02005AE0
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0x22
	bl FUN_02003D38
	add r6, r0, #0x0
	bl FUN_02005BA0
	add r0, r4, #0x0
	mov r1, #0x8
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02005B04
	bl ErrorHandling
	pop {r4-r6, pc}
_02005B04:
	mov r2, #0x0
	strb r2, [r4, #0x0]
	strb r2, [r4, #0x1]
	strb r2, [r4, #0x2]
	strb r2, [r4, #0x3]
	strb r2, [r4, #0x4]
	strb r2, [r4, #0x5]
	strb r2, [r4, #0x6]
	strb r2, [r4, #0x7]
	ldr r0, _02005B28 ; =FUN_02005B2C
	add r1, r4, #0x0
	str r5, [r4, #0x0]
	bl FUN_0200CA44
	str r0, [r4, #0x4]
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	nop
_02005B28: .word FUN_02005B2C 

	thumb_func_start FUN_02005B2C
FUN_02005B2C: ; 0x02005B2C
	push {r4-r6, lr}
	mov r0, #0xf
	add r5, r1, #0x0
	bl FUN_02003D38
	add r6, r0, #0x0
	mov r0, #0x10
	bl FUN_02003D38
	ldr r2, [r5, #0x0]
	add r4, r0, #0x0
	cmp r2, #0xa
	bne _02005B58
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_02004828
	ldr r2, [r5, #0x0]
	mov r0, #0x8
	mov r1, #0x0
	bl FUN_02004828
_02005B58:
	ldr r0, [r5, #0x0]
	sub r0, r0, #0x1
	str r0, [r5, #0x0]
	bl FUN_02005670
	cmp r0, #0x0
	bne _02005B6A
	mov r0, #0x0
	str r0, [r5, #0x0]
_02005B6A:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bgt _02005B9E
	mov r0, #0x0
	bl FUN_02005614
	ldrb r0, [r6, #0x0]
	cmp r0, #0x1
	bne _02005B88
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005B88:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	bne _02005B9A
	mov r0, #0xf
	bl FUN_02004C3C
	mov r0, #0xf
	bl FUN_02004A04
_02005B9A:
	bl FUN_02005BA0
_02005B9E:
	pop {r4-r6, pc}

	thumb_func_start FUN_02005BA0
FUN_02005BA0: ; 0x02005BA0
	push {r3-r5, lr}
	mov r0, #0x22
	bl FUN_02003D38
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02005BC2
	bl FUN_0201B6C8
	add r5, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0200CAB4
	add r0, r5, #0x0
	bl FUN_02016A18
_02005BC2:
	mov r0, #0x0
	str r0, [r4, #0x0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02005BC8
FUN_02005BC8: ; 0x02005BC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x11
	add r4, r1, #0x0
	bl FUN_02003D38
	mov r1, #0x1
	strb r1, [r0, #0x0]
	add r0, r1, #0x0
	bl FUN_02005E80
	add r0, r5, #0x0
	bl FUN_02005578
	add r5, r0, #0x0
	ldr r1, _02005BF4 ; =0x0000FFFF
	mov r0, #0x8
	add r2, r4, #0x0
	bl FUN_02004D20
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_02005BF4: .word 0x0000FFFF

	thumb_func_start FUN_02005BF8
FUN_02005BF8: ; 0x02005BF8
	push {r3-r6, lr}
	sub sp, #0x4
	add r5, r0, #0x0
	mov r0, #0x11
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02003D38
	mov r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0xf
	bl FUN_02004984
	ldr r0, [sp, #0x18]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0xf
	bl FUN_02004B30
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02005C28
FUN_02005C28: ; 0x02005C28
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_020048F4
	add r0, r5, #0x0
	bl FUN_02005CEC
	bl FUN_02004124
	bl FUN_020048D0
	cmp r0, #0xff
	beq _02005C48
	mov r1, #0x1
	bl FUN_020047C8
_02005C48:
	mov r0, #0x1c
	bl FUN_02003D38
	bl FUN_02003F3C
	add r0, r5, #0x0
	mov r1, #0x3
	bl FUN_02003FA8
	mov r0, #0x2
	bl FUN_02003FF4
	add r1, r5, #0x0
	blx FUN_020C3980
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x2
	bl FUN_02004858
	add r0, r4, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02005C74
FUN_02005C74: ; 0x02005C74
	push {r4, lr}
	mov r0, #0xd
	bl FUN_02003D38
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_020048BC
	cmp r0, #0x0
	beq _02005C8C
	mov r0, #0x1
	pop {r4, pc}
_02005C8C:
	ldrh r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02005C9A
	sub r0, r0, #0x1
	strh r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_02005C9A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02005CA0
FUN_02005CA0: ; 0x02005CA0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x2
	bl FUN_02003FF4
	add r1, r4, #0x0
	blx FUN_020C10A4
	mov r0, #0x6
	bl FUN_02004748
	bl FUN_02003F64
	pop {r4, pc}

	thumb_func_start FUN_02005CBC
FUN_02005CBC: ; 0x02005CBC
	push {r3, lr}
	mov r0, #0xd
	bl FUN_02003D38
	bl FUN_02005C74
	cmp r0, #0x1
	bne _02005CD0
	mov r0, #0x1
	pop {r3, pc}
_02005CD0:
	mov r0, #0x0
	bl FUN_02005CA0
	bl FUN_02004124
	bl FUN_020048D0
	cmp r0, #0xff
	beq _02005CE8
	mov r1, #0x0
	bl FUN_020047C8
_02005CE8:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02005CEC
FUN_02005CEC: ; 0x02005CEC
	push {r3, lr}
	mov r0, #0xd
	bl FUN_02003D38
	mov r1, #0xf
	strh r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02005CFC
FUN_02005CFC: ; 0x02005CFC
	push {r3, lr}
	mov r0, #0x1d
	bl FUN_02003D38
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02005D1C
	mov r0, #0xe
	bl FUN_02004ABC
	cmp r0, #0x0
	bne _02005D1C
	bl FUN_02005DFC
	mov r0, #0x1
	pop {r3, pc}
_02005D1C:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_02005D20
FUN_02005D20: ; 0x02005D20
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x1e
	bl FUN_02003D38
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02029F04
	cmp r0, #0x0
	bne _02005D3A
	mov r0, #0x0
	pop {r3-r5, pc}
_02005D3A:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x1
	beq _02005D44
	mov r0, #0x1
	pop {r3-r5, pc}
_02005D44:
	mov r0, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02005D48
FUN_02005D48: ; 0x02005D48
	push {r3-r7, lr}
	sub sp, #0x30
	add r6, r0, #0x0
	add r5, r2, #0x0
	add r7, r3, #0x0
	bl FUN_02004DB4
	str r0, [sp, #0x0]
	mov r0, #0x1d
	bl FUN_02003D38
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	bl FUN_02005D20
	cmp r0, #0x0
	bne _02005D70
	add sp, #0x30
	mov r0, #0x0
	pop {r3-r7, pc}
_02005D70:
	mov r0, #0x0
	bl FUN_02005614
	bl FUN_02005DFC
	mov r0, #0xe
	bl FUN_02004984
	bl FUN_0201B9EC
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x13
	sub r1, r1, r2
	mov r0, #0x13
	ror r1, r0
	add r0, r2, r1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r6, #0x0
	bl FUN_02029F10
	add r1, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_02029F14
	mov r0, #0xe
	bl FUN_02004930
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	bl FUN_02004DB4
	str r0, [sp, #0x10]
	mov r0, #0x0
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	mov r0, #0x7d
	lsl r0, r0, #0x4
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
	mov r0, #0x2
	lsl r0, r0, #0xe
	add r0, r4, r0
	str r0, [sp, #0x28]
	lsr r0, r7, #0x1f
	add r0, r7, r0
	asr r0, r0, #0x1
	add r0, #0x40
	str r0, [sp, #0x2c]
	add r0, sp, #0x8
	mov r1, #0xe
	str r5, [sp, #0x24]
	bl FUN_02004A6C
	add r4, r0, #0x0
	mov r0, #0xe
	add r1, r5, #0x0
	bl FUN_02004AF8
	ldr r0, [sp, #0x4]
	mov r1, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x0
	bl FUN_02005E80
	add r0, r4, #0x0
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02005DFC
FUN_02005DFC: ; 0x02005DFC
	push {r3-r5, lr}
	mov r0, #0xf
	bl FUN_02003D38
	add r5, r0, #0x0
	mov r0, #0x1d
	bl FUN_02003D38
	add r4, r0, #0x0
	ldrb r0, [r5, #0x0]
	cmp r0, #0x1
	bne _02005E20
	mov r0, #0xe
	bl FUN_02004C3C
	mov r0, #0xe
	bl FUN_02004A04
_02005E20:
	mov r0, #0x0
	strb r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02005E28
FUN_02005E28: ; 0x02005E28
	push {lr}
	sub sp, #0x1c
	mov r0, #0x2
	str r0, [sp, #0x0]
	bl FUN_02004DB4
	mov r1, #0x7d
	str r0, [sp, #0x4]
	lsl r1, r1, #0x4
	mov r0, #0x1f
	str r1, [sp, #0x8]
	tst r0, r1
	beq _02005E48
	mov r0, #0x1f
	bic r1, r0
	str r1, [sp, #0x8]
_02005E48:
	ldr r0, _02005E60 ; =0x00004174
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	add r0, sp, #0x0
	bl FUN_02004914
	add sp, #0x1c
	pop {pc}
	nop
_02005E60: .word 0x00004174

	thumb_func_start FUN_02005E64
FUN_02005E64: ; 0x02005E64
	ldr r3, _02005E68 ; =FUN_0200491C
	bx r3
	.balign 4
_02005E68: .word FUN_0200491C 

	thumb_func_start FUN_02005E6C
FUN_02005E6C: ; 0x02005E6C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02004DB4
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02029F4C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02005E80
FUN_02005E80: ; 0x02005E80
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1e
	bl FUN_02003D38
	strb r4, [r0, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02005E90
FUN_02005E90: ; 0x02005E90
	push {r3-r7, lr}
	add r5, r0, #0x0
	mov r0, #0x23
	add r7, r1, #0x0
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl FUN_02003D38
	cmp r5, #0x0
	bne _02005EB2
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02005D48
	b _02005EBE
_02005EB2:
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl FUN_02005D48
_02005EBE:
	cmp r0, #0x0
	bne _02005ED8
	mov r0, #0x1
	bl FUN_02005E80
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r1, _02005EDC ; =0x000001B9
	mov r0, #0x0
	add r2, r6, #0x0
	add r3, r4, #0x0
	bl FUN_020056AC
_02005ED8:
	pop {r3-r7, pc}
	nop
_02005EDC: .word 0x000001B9

	thumb_func_start FUN_02005EE0
FUN_02005EE0: ; 0x02005EE0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02029F04
	cmp r0, #0x0
	bne _02005EF0
	mov r0, #0x0
	pop {r4, pc}
_02005EF0:
	add r0, r4, #0x0
	bl FUN_02029F10
	mov r1, #0xf
	ldrsb r0, [r0, r1]
	sub r1, #0x2d
	cmp r0, r1
	bge _02005F04
	mov r0, #0x1
	pop {r4, pc}
_02005F04:
	cmp r0, #0x1e
	blt _02005F10
	cmp r0, #0x80
	bge _02005F10
	mov r0, #0x2
	pop {r4, pc}
_02005F10:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02005F14
FUN_02005F14: ; 0x02005F14
	cmp r0, #0xb
	bgt _02005F2E
	bge _02005F32
	cmp r0, #0x5
	bgt _02005F36
	cmp r0, #0x0
	blt _02005F36
	beq _02005F32
	cmp r0, #0x1
	beq _02005F32
	cmp r0, #0x5
	beq _02005F32
	b _02005F36
_02005F2E:
	cmp r0, #0xc
	bne _02005F36
_02005F32:
	mov r0, #0x1
	bx lr
_02005F36:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02005F3C
FUN_02005F3C: ; 0x02005F3C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	beq _02005F4A
	bl ErrorHandling
_02005F4A:
	ldr r1, [r4, #0x0]
	mov r0, #0x0
	blx FS_UnloadOverlay
	cmp r0, #0x1
	beq _02005F5A
	bl ErrorHandling
_02005F5A:
	mov r0, #0x0
	str r0, [r4, #0x4]
	pop {r4, pc}

	thumb_func_start FUN_02005F60
FUN_02005F60: ; 0x02005F60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02005F90
	bl FUN_0200610C
	mov r2, #0x0
	add r3, r0, #0x0
_02005F70:
	ldr r1, [r3, #0x4]
	cmp r1, #0x1
	bne _02005F86
	ldr r1, [r3, #0x0]
	cmp r4, r1
	bne _02005F86
	lsl r1, r2, #0x3
	add r0, r0, r1
	bl FUN_02005F3C
	pop {r4, pc}
_02005F86:
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, #0x8
	blt _02005F70
	pop {r4, pc}

	thumb_func_start FUN_02005F90
FUN_02005F90: ; 0x02005F90
	push {lr}
	sub sp, #0x2c
	add r2, r0, #0x0
	add r0, sp, #0x0
	mov r1, #0x0
	blx FS_LoadOverlayInfo
	cmp r0, #0x1
	beq _02005FA6
	bl ErrorHandling
_02005FA6:
	mov r0, #0x2
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0x18
	cmp r2, r0
	bhi _02005FBC
	lsr r0, r0, #0x1
	cmp r2, r0
	blo _02005FBC
	add sp, #0x2c
	mov r0, #0x1
	pop {pc}
_02005FBC:
	mov r0, #0x1
	ldr r1, _02005FD8 ; =0x027E0000
	lsl r0, r0, #0xe
	add r0, r1, r0
	cmp r2, r0
	bhi _02005FD2
	cmp r2, r1
	blo _02005FD2
	add sp, #0x2c
	mov r0, #0x2
	pop {pc}
_02005FD2:
	mov r0, #0x0
	add sp, #0x2c
	pop {pc}
	.balign 4
_02005FD8: .word 0x027E0000

	thumb_func_start FUN_02005FDC
FUN_02005FDC: ; 0x02005FDC
	push {r3-r7, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	mvn r1, r1
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	bl FUN_02006090
	cmp r0, #0x0
	bne _02005FF4
	mov r0, #0x0
	pop {r3-r7, pc}
_02005FF4:
	add r0, r5, #0x0
	bl FUN_02005F90
	add r7, r0, #0x0
	bl FUN_0200610C
	add r3, r0, #0x0
	mov r6, #0x0
	add r1, r3, #0x0
_02006006:
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	bne _02006018
	lsl r1, r6, #0x3
	add r2, r3, r1
	mov r0, #0x1
	str r0, [r2, #0x4]
	str r5, [r3, r1]
	b _02006020
_02006018:
	add r6, r6, #0x1
	add r1, #0x8
	cmp r6, #0x8
	blt _02006006
_02006020:
	cmp r6, #0x8
	blt _0200602C
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_0200602C:
	sub r6, r7, #0x1
	cmp r6, #0x1
	bhi _0200603C
	mov r0, #0x0
	mvn r0, r0
	blx FS_SetDefaultDMA
	str r0, [sp, #0x0]
_0200603C:
	cmp r4, #0x0
	beq _0200604A
	cmp r4, #0x1
	beq _02006056
	cmp r4, #0x2
	beq _02006062
	b _0200606E
_0200604A:
	mov r0, #0x0
	add r1, r5, #0x0
	bl FUN_02006168
	add r4, r0, #0x0
	b _02006076
_02006056:
	mov r0, #0x0
	add r1, r5, #0x0
	bl FUN_02006170
	add r4, r0, #0x0
	b _02006076
_02006062:
	mov r0, #0x0
	add r1, r5, #0x0
	bl FUN_020061A8
	add r4, r0, #0x0
	b _02006076
_0200606E:
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_02006076:
	cmp r6, #0x1
	bhi _02006080
	ldr r0, [sp, #0x0]
	blx FS_SetDefaultDMA
_02006080:
	cmp r4, #0x0
	bne _0200608C
	bl ErrorHandling
	mov r0, #0x0
	pop {r3-r7, pc}
_0200608C:
	mov r0, #0x1
	pop {r3-r7, pc}

	thumb_func_start FUN_02006090
FUN_02006090: ; 0x02006090
	push {r3-r7, lr}
	sub sp, #0x10
	add r1, sp, #0xc
	add r2, sp, #0x8
	add r4, r0, #0x0
	bl FUN_02006130
	cmp r0, #0x0
	bne _020060A8
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_020060A8:
	add r0, r4, #0x0
	bl FUN_02005F90
	bl FUN_0200610C
	add r5, r0, #0x0
	mov r4, #0x0
	add r6, sp, #0x4
	add r7, sp, #0x0
_020060BA:
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _020060FC
	ldr r0, [r5, #0x0]
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02006130
	cmp r0, #0x1
	bne _020060FC
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0xc]
	cmp r2, r1
	blo _020060DC
	ldr r0, [sp, #0x0]
	cmp r2, r0
	blo _020060F2
_020060DC:
	ldr r3, [sp, #0x8]
	cmp r3, r1
	bls _020060E8
	ldr r0, [sp, #0x0]
	cmp r3, r0
	bls _020060F2
_020060E8:
	cmp r2, r1
	bhi _020060FC
	ldr r0, [sp, #0x0]
	cmp r3, r0
	blo _020060FC
_020060F2:
	bl ErrorHandling
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
_020060FC:
	add r4, r4, #0x1
	add r5, #0x8
	cmp r4, #0x8
	blt _020060BA
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200610C
FUN_0200610C: ; 0x0200610C
	cmp r0, #0x0
	beq _02006118
	cmp r0, #0x1
	beq _0200611C
	cmp r0, #0x2
	beq _02006120
_02006118:
	ldr r0, _02006124 ; =0x021C45B0
	bx lr
_0200611C:
	ldr r0, _02006128 ; =0x021C45F0
	bx lr
_02006120:
	ldr r0, _0200612C ; =0x021C4630
	bx lr
	.balign 4
_02006124: .word 0x021C45B0
_02006128: .word 0x021C45F0
_0200612C: .word 0x021C4630

	thumb_func_start FUN_02006130
FUN_02006130: ; 0x02006130
	push {r4-r5, lr}
	sub sp, #0x2c
	add r3, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r0, sp, #0x0
	mov r1, #0x0
	add r2, r3, #0x0
	blx FS_LoadOverlayInfo
	cmp r0, #0x0
	bne _02006152
	bl ErrorHandling
	add sp, #0x2c
	mov r0, #0x0
	pop {r4-r5, pc}
_02006152:
	ldr r2, [sp, #0x4]
	str r2, [r5, #0x0]
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [r4, #0x0]
	mov r0, #0x1
	add sp, #0x2c
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02006168
FUN_02006168: ; 0x02006168
	ldr r3, _0200616C ; =FS_LoadOverlay
	bx r3
	.balign 4
_0200616C: .word FS_LoadOverlay

	thumb_func_start FUN_02006170
FUN_02006170: ; 0x02006170
	push {lr}
	sub sp, #0x2c
	add r3, r0, #0x0
	add r2, r1, #0x0
	add r0, sp, #0x0
	add r1, r3, #0x0
	blx FS_LoadOverlayInfo
	cmp r0, #0x0
	bne _0200618A
	add sp, #0x2c
	mov r0, #0x0
	pop {pc}
_0200618A:
	add r0, sp, #0x0
	blx FS_LoadOverlayImage
	cmp r0, #0x0
	bne _0200619A
	add sp, #0x2c
	mov r0, #0x0
	pop {pc}
_0200619A:
	add r0, sp, #0x0
	blx FS_StartOverlay
	mov r0, #0x1
	add sp, #0x2c
	pop {pc}
	.balign 4

	thumb_func_start FUN_020061A8
FUN_020061A8: ; 0x020061A8
	push {lr}
	sub sp, #0x74
	add r3, r0, #0x0
	add r2, r1, #0x0
	add r0, sp, #0x0
	add r1, r3, #0x0
	blx FS_LoadOverlayInfo
	cmp r0, #0x0
	bne _020061C2
	add sp, #0x74
	mov r0, #0x0
	pop {pc}
_020061C2:
	add r0, sp, #0x2c
	blx FS_InitFile
	add r0, sp, #0x0
	add r1, sp, #0x2c
	blx FS_LoadOverlayImageAsync
	add r0, sp, #0x2c
	blx FS_WaitAsync
	add r0, sp, #0x2c
	blx FS_CloseFile
	add r0, sp, #0x0
	blx FS_StartOverlay
	mov r0, #0x1
	add sp, #0x74
	pop {pc}

	thumb_func_start FUN_020061E8
FUN_020061E8: ; 0x020061E8
	push {r3-r7, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r7, r2, #0x0
	cmp r5, #0x0
	beq _0200620C
	add r0, r3, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	bne _02006202
	mov r0, #0x0
	pop {r3-r7, pc}
_02006202:
	mov r1, #0x0
	add r2, r5, #0x0
	blx Call_FillMemWithValue
	b _0200620E
_0200620C:
	mov r4, #0x0
_0200620E:
	add r0, r6, #0x0
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_0200CA44
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200621C
FUN_0200621C: ; 0x0200621C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201B6C8
	cmp r0, #0x0
	beq _0200622C
	bl FUN_02016A18
_0200622C:
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start FUN_02006234
FUN_02006234: ; 0x02006234
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x28
	bl FUN_02016998
	add r3, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	str r0, [r3, #0x10]
	str r0, [r3, #0x14]
	str r4, [r3, #0x18]
	str r0, [r3, #0x1c]
	str r0, [r3, #0x20]
	str r0, [r3, #0x24]
	add r0, r3, #0x0
	pop {r3-r5, pc}

	thumb_func_start FUN_02006260
FUN_02006260: ; 0x02006260
	ldr r3, _02006264 ; =FUN_02016A18
	bx r3
	.balign 4
_02006264: .word FUN_02016A18 

	thumb_func_start FUN_02006268
FUN_02006268: ; 0x02006268
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r2, #0x0
	bl FUN_02016998
	str r0, [r4, #0x1c]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02006278
FUN_02006278: ; 0x02006278
	ldr r0, [r0, #0x1c]
	bx lr

	thumb_func_start FUN_0200627C
FUN_0200627C: ; 0x0200627C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x1c]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x1c]
	pop {r4, pc}

	thumb_func_start FUN_0200628C
FUN_0200628C: ; 0x0200628C
	ldr r0, [r0, #0x18]
	bx lr

	thumb_func_start FUN_02006290
FUN_02006290: ; 0x02006290
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x10]
	cmp r1, #0x3
	bhi _0200630E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020062A6: ; jump table (using 16-bit offset)
	.short _020062AE - _020062A6 - 2; case 0
	.short _020062C2 - _020062A6 - 2; case 1
	.short _020062DA - _020062A6 - 2; case 2
	.short _020062F0 - _020062A6 - 2; case 3
_020062AE:
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	mvn r1, r1
	cmp r0, r1
	beq _020062BE
	mov r1, #0x2
	bl FUN_02005FDC
_020062BE:
	mov r0, #0x1
	str r0, [r4, #0x10]
_020062C2:
	add r1, r4, #0x0
	ldr r2, [r4, #0x0]
	add r0, r4, #0x0
	add r1, #0x14
	blx r2
	cmp r0, #0x1
	bne _0200630E
	mov r0, #0x2
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	b _0200630E
_020062DA:
	add r1, r4, #0x0
	ldr r2, [r4, #0x4]
	add r1, #0x14
	blx r2
	cmp r0, #0x1
	bne _0200630E
	mov r0, #0x3
	str r0, [r4, #0x10]
	mov r0, #0x0
	str r0, [r4, #0x14]
	b _0200630E
_020062F0:
	add r1, r4, #0x0
	ldr r2, [r4, #0x8]
	add r1, #0x14
	blx r2
	cmp r0, #0x1
	bne _0200630E
	mov r1, #0x0
	ldr r0, [r4, #0xc]
	mvn r1, r1
	cmp r0, r1
	beq _0200630A
	bl FUN_02005F60
_0200630A:
	mov r0, #0x1
	pop {r4, pc}
_0200630E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
