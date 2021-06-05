	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.extern gMain
	.extern gMain

	.global gTextFlags
gTextFlags: ; 0x02106FC4
	.space 0x4

	.section .rodata

	.global UNK_020ECB50
UNK_020ECB50: ; 0x020ECB50
	.byte 0x00, 0x01, 0x02, 0x01

	.text

	thumb_func_start RenderText
RenderText: ; 0x020023C0
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
	ldr r0, _02002658 ; =gMain
	ldr r1, [r0, #0x44]
	mov r0, #0x3
	tst r0, r1
	beq _02002402
	ldrb r0, [r6, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	bne _02002414
_02002402:
	ldr r0, _0200265C ; =gMain + 0x40
	ldrh r0, [r0, #0x22]
	cmp r0, #0x0
	beq _02002432
	ldr r0, _02002660 ; =gTextFlags
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
	ldr r1, _02002660 ; =gTextFlags
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
	ldr r0, _02002660 ; =gTextFlags
	ldrb r0, [r0, #0x0]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	beq _02002486
	ldr r1, _02002658 ; =gMain
	ldr r2, [r1, #0x48]
	mov r1, #0x3
	tst r1, r2
	bne _02002478
	ldr r1, _0200265C ; =gMain + 0x40
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
	bl GF_AssertFail
_020024B0:
	ldr r0, _02002664 ; =0x0000F0FD
	cmp r5, r0
	bgt _020024DA
	bge _0200250E
	ldr r1, _02002668 ; =0x000025BD \f
	cmp r5, r1
	bgt _020024D0
	sub r0, r1, #0x1 ; \r
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
	ldr r0, _0200266C ; =0x0000FFFE EXT_CTRL_CODE_BEGIN
	cmp r5, r0
	bgt _020024E4
	beq _0200251A
	b _02002700
_020024E4:
	add r0, r0, #0x1 ; =0x0000FFFF EOS
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
	bl GetFontAttribute
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
	bl MsgArray_GetControlCode
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
	.short _020025B4 - _02002548 - 2; case 0x200
	.short _020025DE - _02002548 - 2; case 0x201
	.short _02002600 - _02002548 - 2; case 0x202
	.short _02002618 - _02002548 - 2; case 0x203
	.short _02002624 - _02002548 - 2; case 0x204
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
	bl MsgArray_ControlCodeGetField
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
	bl GenerateFontHalfRowLookupTable
	b _020026CA
_020025B4:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl MsgArray_ControlCodeGetField
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
	bl CopyWindowToVram
	b _020026CA
_020025DE:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl MsgArray_ControlCodeGetField
	add r1, r4, #0x0
	add r1, #0x26
	strb r0, [r1, #0x0]
	ldr r0, [r4, #0x0]
	bl MsgArray_SkipControlCode
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
	bl MsgArray_ControlCodeGetField
	strh r0, [r4, #0x2a]
	ldr r0, [r4, #0x0]
	bl MsgArray_SkipControlCode
	str r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_02002618:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl MsgArray_ControlCodeGetField
	strb r0, [r4, #0xc]
	b _020026CA
_02002624:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl MsgArray_ControlCodeGetField
	strb r0, [r4, #0xd]
	b _020026CA
_02002630:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl MsgArray_ControlCodeGetField
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
_02002658: .word gMain
_0200265C: .word gMain + 0x40
_02002660: .word gTextFlags
_02002664: .word 0x0000F0FD
_02002668: .word 0x000025BD
_0200266C: .word 0x0000FFFE
_02002670: .word 0x0000FE06
_02002674: .word 0x0000FFFC
_02002678:
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl MsgArray_ControlCodeGetField
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
	bl MsgArray_SkipControlCode
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
	bl MsgArray_SkipControlCode
	str r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x3
	pop {r3-r6, pc}
_020026CA:
	ldr r0, [r4, #0x0]
	bl MsgArray_SkipControlCode
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
	bl FillWindowPixelBuffer
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
	bl GetFontAttribute
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
	bl ScrollWindow
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
	bl ScrollWindow
	add r0, r4, #0x0
	add r0, #0x27
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x4
_020027F2:
	add r0, r4, #0x0
	add r0, #0x27
	strb r1, [r0, #0x0]
	ldr r0, [r4, #0x4]
	bl CopyWindowToVram
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
	ldr r1, _02002848 ; =gTextFlags
	strh r0, [r1, #0x2]
	bx lr
	nop
_02002848: .word gTextFlags

	thumb_func_start FUN_0200284C
FUN_0200284C: ; 0x0200284C
	ldr r1, _02002874 ; =gTextFlags
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
_02002874: .word gTextFlags

	thumb_func_start FUN_02002878
FUN_02002878: ; 0x02002878
	push {r4-r7, lr}
	sub sp, #0x2c
	add r5, r0, #0x0
	ldr r0, _020029F8 ; =gTextFlags
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
	bl GetWindowBgId
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x4]
	bl GetWindowX
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x4]
	bl GetWindowY
	str r0, [sp, #0x28]
	ldr r0, [r5, #0x4]
	bl GetWindowWidth
	ldr r1, _020029F8 ; =gTextFlags
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
	ldr r2, _020029FC ; =UNK_020ECB50
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
	ldr r2, _020029FC ; =UNK_020ECB50
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
	ldr r2, _020029FC ; =UNK_020ECB50
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
	ldr r2, _020029FC ; =UNK_020ECB50
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
_020029F8: .word gTextFlags
_020029FC: .word UNK_020ECB50

	thumb_func_start FUN_02002A00
FUN_02002A00: ; 0x02002A00
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	bl GetWindowBgId
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x4]
	bl GetWindowX
	str r0, [sp, #0x14]
	ldr r0, [r5, #0x4]
	bl GetWindowY
	add r6, r0, #0x0
	ldr r0, [r5, #0x4]
	bl GetWindowWidth
	ldr r1, _02002A90 ; =gTextFlags
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
_02002A90: .word gTextFlags

	thumb_func_start FUN_02002A94
FUN_02002A94: ; 0x02002A94
	push {r3, lr}
	ldr r0, _02002ACC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #0x3
	tst r0, r1
	bne _02002AB2
	ldr r0, _02002AD0 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0x0
	beq _02002AC6
	ldr r0, _02002AD4 ; =gTextFlags
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _02002AC6
_02002AB2:
	ldr r0, _02002AD8 ; =0x000005DC
	bl FUN_020054C8
	ldr r1, _02002AD4 ; =gTextFlags
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
_02002ACC: .word gMain
_02002AD0: .word gMain + 0x40
_02002AD4: .word gTextFlags
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
	ldr r1, _02002B14 ; =gTextFlags
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
_02002B14: .word gTextFlags

	thumb_func_start FUN_02002B18
FUN_02002B18: ; 0x02002B18
	push {r4, lr}
	ldr r1, _02002B38 ; =gTextFlags
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
_02002B38: .word gTextFlags

	thumb_func_start FUN_02002B3C
FUN_02002B3C: ; 0x02002B3C
	push {r3, lr}
	ldr r1, _02002B5C ; =gTextFlags
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
_02002B5C: .word gTextFlags

	thumb_func_start FUN_02002B60
FUN_02002B60: ; 0x02002B60
	ldr r2, _02002B78 ; =gTextFlags
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
_02002B78: .word gTextFlags

	thumb_func_start FUN_02002B7C
FUN_02002B7C: ; 0x02002B7C
	push {r3-r4}
	ldr r1, _02002BB4 ; =gTextFlags
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
_02002BB4: .word gTextFlags

	thumb_func_start FUN_02002BB8
FUN_02002BB8: ; 0x02002BB8
	ldr r2, _02002BD0 ; =gTextFlags
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
_02002BD0: .word gTextFlags

	thumb_func_start FUN_02002BD4
FUN_02002BD4: ; 0x02002BD4
	ldr r0, _02002BE0 ; =gTextFlags
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr
	nop
_02002BE0: .word gTextFlags

	thumb_func_start FUN_02002BE4
FUN_02002BE4: ; 0x02002BE4
	ldr r1, _02002BF0 ; =gTextFlags
	mov r0, #0x40
	ldrb r2, [r1, #0x0]
	bic r2, r0
	strb r2, [r1, #0x0]
	bx lr
	.balign 4
_02002BF0: .word gTextFlags

	thumb_func_start FUN_02002BF4
FUN_02002BF4: ; 0x02002BF4
	ldr r0, _02002C00 ; =gTextFlags
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr
	nop
_02002C00: .word gTextFlags

	thumb_func_start FUN_02002C04
FUN_02002C04: ; 0x02002C04
	ldr r1, _02002C10 ; =gTextFlags
	mov r0, #0x80
	ldrb r2, [r1, #0x0]
	bic r2, r0
	strb r2, [r1, #0x0]
	bx lr
	.balign 4
_02002C10: .word gTextFlags
