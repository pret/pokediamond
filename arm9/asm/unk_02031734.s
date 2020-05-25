	.include "asm/macros.inc"
    .include "global.inc"

	.extern gUnk021C4918
	.section .rodata
	.global UNK_020EEC48
UNK_020EEC48: ; 0x020EEC48
	.word FUN_02032B84, 0x00000000

	.global UNK_020EEC50
UNK_020EEC50: ; 0x020EEC50
	.word FUN_0203213C, FUN_02032138, 0x00000000

	.global UNK_020EEC5C
UNK_020EEC5C: ; 0x020EEC5C
	.word FUN_02032234, FUN_0203234C, 0x00000000

	.section .data

	.balign 4
	.global UNK_02105D5C
UNK_02105D5C: ; 0x02105D5C
	.asciz "FREAK"

	.balign 4
	.global UNK_02105D64
UNK_02105D64: ; 0x02105D64
	.asciz " FULL"

	.balign 4
	.global UNK_02105D6C
UNK_02105D6C: ; 0x02105D6C
	.asciz " GAME"

	.section .bss

	.global UNK_021C5A00
UNK_021C5A00: ; 0x021C5A00
	.space 0x4

	.text

	thumb_func_start FUN_02031734
FUN_02031734: ; 0x02031734
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020317BC ; =UNK_021C5A00
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020317B8
	bl FUN_0202E49C
	mov r0, #0xf
	mov r1, #0x50
	bl FUN_02016998
	ldr r1, _020317BC ; =UNK_021C5A00
	mov r2, #0x50
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _020317BC ; =UNK_021C5A00
	mov r2, #0x32
	ldr r1, [r0, #0x0]
	strh r2, [r1, #0x3a]
	ldr r1, [r0, #0x0]
	mov r2, #0x1
	add r1, #0x43
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	str r5, [r0, #0x28]
	add r0, r5, #0x0
	bl FUN_020238F4
	ldr r1, _020317BC ; =UNK_021C5A00
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x2c]
	ldr r0, [r1, #0x0]
	mov r2, #0x2
	add r0, #0x3c
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, #0x3d
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, #0x48
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, #0x3f
	strb r4, [r0, #0x0]
	ldr r0, [r1, #0x0]
	add r0, #0xc
	bl FUN_020312BC
	mov r0, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	bl FUN_0202D8D0
	cmp r4, #0x9
	beq _020317B8
	cmp r4, #0x11
	beq _020317B8
	cmp r4, #0xf
	beq _020317B8
	bl FUN_02033E74
_020317B8:
	pop {r3-r5, pc}
	nop
_020317BC: .word UNK_021C5A00

	thumb_func_start FUN_020317C0
FUN_020317C0: ; 0x020317C0
	push {r3, lr}
	ldr r0, _0203180C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203180A
	bl FUN_0202D918
	ldr r0, _0203180C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020317DC
	bl FUN_02016A18
_020317DC:
	ldr r0, _0203180C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x13
	blo _020317EE
	mov r0, #0x31
	bl FUN_020168D0
_020317EE:
	bl FUN_02033ED0
	bl FUN_0202E4F0
	ldr r0, _0203180C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	mov r0, #0xf
	bl FUN_020168D0
	ldr r0, _0203180C ; =UNK_021C5A00
	mov r1, #0x0
	str r1, [r0, #0x0]
_0203180A:
	pop {r3, pc}
	.balign 4
_0203180C: .word UNK_021C5A00

	thumb_func_start FUN_02031810
FUN_02031810: ; 0x02031810
	ldr r0, _02031820 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203181C
	mov r0, #0x1
	bx lr
_0203181C:
	mov r0, #0x0
	bx lr
	.balign 4
_02031820: .word UNK_021C5A00

	thumb_func_start FUN_02031824
FUN_02031824: ; 0x02031824
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02031858 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031856
	mov r2, #0xe
	mov r0, #0x3
	mov r1, #0xf
	lsl r2, r2, #0xc
	bl FUN_02016828
	add r0, r4, #0x0
	mov r1, #0xa
	bl FUN_02031734
	ldr r0, _02031858 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _0203185C ; =FUN_02031D30
	mov r1, #0x32
	bl FUN_02031D20
_02031856:
	pop {r4, pc}
	.balign 4
_02031858: .word UNK_021C5A00
_0203185C: .word FUN_02031D30

	thumb_func_start FUN_02031860
FUN_02031860: ; 0x02031860
	push {r3, lr}
	ldr r0, _02031878 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031876
	bl FUN_02031468
	ldr r0, _0203187C ; =FUN_020323CC
	mov r1, #0x0
	bl FUN_02031D20
_02031876:
	pop {r3, pc}
	.balign 4
_02031878: .word UNK_021C5A00
_0203187C: .word FUN_020323CC

	thumb_func_start FUN_02031880
FUN_02031880: ; 0x02031880
	push {r3, lr}
	bl FUN_0202FC60
	bl FUN_02031190
	ldr r1, _0203189C ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	strh r0, [r1, #0x38]
	ldr r0, _020318A0 ; =FUN_020321B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_0203189C: .word UNK_021C5A00
_020318A0: .word FUN_020321B8

	thumb_func_start FUN_020318A4
FUN_020318A4: ; 0x020318A4
	ldr r1, _020318B0 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	add r1, #0x4f
	strb r0, [r1, #0x0]
	bx lr
	nop
_020318B0: .word UNK_021C5A00

	thumb_func_start FUN_020318B4
FUN_020318B4: ; 0x020318B4
	ldr r3, _020318BC ; =FUN_02031D20
	ldr r0, _020318C0 ; =FUN_02032028
	mov r1, #0x0
	bx r3
	.balign 4
_020318BC: .word FUN_02031D20
_020318C0: .word FUN_02032028

	thumb_func_start FUN_020318C4
FUN_020318C4: ; 0x020318C4
	push {r4}
	sub sp, #0xc
	ldr r4, _0203190C ; =UNK_020EEC50
	add r3, sp, #0x0
	ldmia r4!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	ldr r0, _02031910 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	cmp r0, #0x0
	bne _020318E8
	add sp, #0xc
	mov r0, #0x0
	pop {r4}
	bx lr
_020318E8:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02031904
_020318EE:
	ldr r0, [r2, #0x0]
	cmp r1, r0
	bne _020318FC
	add sp, #0xc
	mov r0, #0x1
	pop {r4}
	bx lr
_020318FC:
	add r2, r2, #0x4
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _020318EE
_02031904:
	mov r0, #0x0
	add sp, #0xc
	pop {r4}
	bx lr
	.balign 4
_0203190C: .word UNK_020EEC50
_02031910: .word UNK_021C5A00

	thumb_func_start FUN_02031914
FUN_02031914: ; 0x02031914
	ldr r3, _0203191C ; =FUN_02031D20
	ldr r0, _02031920 ; =FUN_02032178
	mov r1, #0x0
	bx r3
	.balign 4
_0203191C: .word FUN_02031D20
_02031920: .word FUN_02032178

	thumb_func_start FUN_02031924
FUN_02031924: ; 0x02031924
	ldr r0, _02031930 ; =UNK_021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x4c
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_02031930: .word UNK_021C5A00

	thumb_func_start FUN_02031934
FUN_02031934: ; 0x02031934
	push {r3, lr}
	bl FUN_0202E49C
	ldr r0, _02031944 ; =FUN_02032194
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031944: .word FUN_02032194

	thumb_func_start FUN_02031948
FUN_02031948: ; 0x02031948
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02031980
	ldr r2, _02031984 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02031734
	ldr r0, _02031988 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	add r1, #0x40
	strb r5, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r4, [r0, #0x30]
	ldr r0, _0203198C ; =FUN_020321D0
	bl FUN_02031D20
_02031980:
	pop {r3-r7, pc}
	nop
_02031984: .word 0x00007080
_02031988: .word UNK_021C5A00
_0203198C: .word FUN_020321D0

	thumb_func_start FUN_02031990
FUN_02031990: ; 0x02031990
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _020319C8
	ldr r2, _020319CC ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02031734
	ldr r0, _020319D0 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	add r1, #0x40
	strb r5, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	str r4, [r0, #0x30]
	ldr r0, _020319D4 ; =FUN_0203224C
	bl FUN_02031D20
_020319C8:
	pop {r3-r7, pc}
	nop
_020319CC: .word 0x00007080
_020319D0: .word UNK_021C5A00
_020319D4: .word FUN_0203224C

	thumb_func_start FUN_020319D8
FUN_020319D8: ; 0x020319D8
	ldr r1, _020319E8 ; =UNK_021C5A00
	ldr r3, _020319EC ; =FUN_02031D20
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _020319F0 ; =FUN_02032298
	mov r1, #0x0
	bx r3
	.balign 4
_020319E8: .word UNK_021C5A00
_020319EC: .word FUN_02031D20
_020319F0: .word FUN_02032298

	thumb_func_start FUN_020319F4
FUN_020319F4: ; 0x020319F4
	push {r3, lr}
	bl FUN_0202FCA8
	ldr r0, _02031A04 ; =FUN_02032364
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031A04: .word FUN_02032364

	thumb_func_start FUN_02031A08
FUN_02031A08: ; 0x02031A08
	push {r3, lr}
	ldr r0, _02031A1C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031A1A
	ldr r0, _02031A20 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02031A1A:
	pop {r3, pc}
	.balign 4
_02031A1C: .word UNK_021C5A00
_02031A20: .word FUN_02032440

	thumb_func_start FUN_02031A24
FUN_02031A24: ; 0x02031A24
	ldr r3, _02031A28 ; =FUN_0202D298
	bx r3
	.balign 4
_02031A28: .word FUN_0202D298

	thumb_func_start FUN_02031A2C
FUN_02031A2C: ; 0x02031A2C
	push {r4}
	sub sp, #0xc
	ldr r4, _02031A74 ; =UNK_020EEC5C
	add r3, sp, #0x0
	ldmia r4!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r3, #0x0]
	ldr r0, _02031A78 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	cmp r0, #0x0
	bne _02031A50
	add sp, #0xc
	mov r0, #0x0
	pop {r4}
	bx lr
_02031A50:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02031A6C
_02031A56:
	ldr r0, [r2, #0x0]
	cmp r1, r0
	bne _02031A64
	add sp, #0xc
	mov r0, #0x1
	pop {r4}
	bx lr
_02031A64:
	add r2, r2, #0x4
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _02031A56
_02031A6C:
	mov r0, #0x0
	add sp, #0xc
	pop {r4}
	bx lr
	.balign 4
_02031A74: .word UNK_020EEC5C
_02031A78: .word UNK_021C5A00

	thumb_func_start FUN_02031A7C
FUN_02031A7C: ; 0x02031A7C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02031ABC ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031ABA
	ldr r2, _02031AC0 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	cmp r0, #0x0
	bne _02031A9A
	bl FUN_020335E0
_02031A9A:
	add r0, r4, #0x0
	mov r1, #0x9
	bl FUN_02031734
	ldr r0, _02031ABC ; =UNK_021C5A00
	mov r2, #0x9
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _02031AC4 ; =FUN_02032478
	bl FUN_02031D20
_02031ABA:
	pop {r4, pc}
	.balign 4
_02031ABC: .word UNK_021C5A00
_02031AC0: .word 0x00007080
_02031AC4: .word FUN_02032478

	thumb_func_start FUN_02031AC8
FUN_02031AC8: ; 0x02031AC8
	push {r3, lr}
	ldr r1, _02031AEC ; =UNK_021C5A00
	ldr r2, [r1, #0x0]
	add r2, #0x3e
	strb r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x3
	strh r2, [r0, #0x38]
	mov r0, #0x1
	bl FUN_0202D344
	bl FUN_02033E74
	ldr r0, _02031AF0 ; =FUN_02032628
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031AEC: .word UNK_021C5A00
_02031AF0: .word FUN_02032628

	thumb_func_start FUN_02031AF4
FUN_02031AF4: ; 0x02031AF4
	ldr r0, _02031B20 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031B02
	mov r0, #0x0
	mvn r0, r0
	bx lr
_02031B02:
	ldr r1, [r0, #0x24]
	ldr r0, _02031B24 ; =FUN_0203279C
	cmp r1, r0
	bne _02031B0E
	mov r0, #0x1
	bx lr
_02031B0E:
	ldr r0, _02031B28 ; =FUN_020327B4
	cmp r1, r0
	bne _02031B18
	mov r0, #0x1
	b _02031B1A
_02031B18:
	mov r0, #0x0
_02031B1A:
	neg r0, r0
	bx lr
	nop
_02031B20: .word UNK_021C5A00
_02031B24: .word FUN_0203279C
_02031B28: .word FUN_020327B4

	thumb_func_start FUN_02031B2C
FUN_02031B2C: ; 0x02031B2C
	ldr r0, _02031B48 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031B38
	mov r0, #0x0
	bx lr
_02031B38:
	ldr r1, [r0, #0x24]
	ldr r0, _02031B4C ; =FUN_020327FC
	cmp r1, r0
	bne _02031B44
	mov r0, #0x1
	bx lr
_02031B44:
	mov r0, #0x0
	bx lr
	.balign 4
_02031B48: .word UNK_021C5A00
_02031B4C: .word FUN_020327FC

	thumb_func_start FUN_02031B50
FUN_02031B50: ; 0x02031B50
	push {r3, lr}
	mov r0, #0x0
	bl FUN_0202D344
	ldr r0, _02031BC4 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02031B78
	add r0, r1, #0x0
	add r0, #0x45
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02031B78
	add r1, #0x3f
	ldrb r0, [r1, #0x0]
	cmp r0, #0x9
	bne _02031B80
_02031B78:
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
_02031B80:
	bl FUN_02033ED0
	ldr r0, _02031BC4 ; =UNK_021C5A00
	mov r2, #0x9
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r1, #0x48
	strb r2, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	bl FUN_0202D1B0
	bl FUN_02031190
	cmp r0, #0x0
	bne _02031BB8
	mov r0, #0x1
	bl FUN_0202D36C
	ldr r0, _02031BC8 ; =FUN_020323DC
	mov r1, #0xf
	bl FUN_02031D20
	pop {r3, pc}
_02031BB8:
	ldr r0, _02031BCC ; =FUN_02032424
	mov r1, #0x5
	bl FUN_02031D20
	pop {r3, pc}
	nop
_02031BC4: .word UNK_021C5A00
_02031BC8: .word FUN_020323DC
_02031BCC: .word FUN_02032424

	thumb_func_start FUN_02031BD0
FUN_02031BD0: ; 0x02031BD0
	ldr r0, _02031BEC ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031BDC
	mov r0, #0x1
	bx lr
_02031BDC:
	ldr r1, [r0, #0x24]
	ldr r0, _02031BF0 ; =FUN_020324F8
	cmp r1, r0
	beq _02031BE8
	mov r0, #0x1
	bx lr
_02031BE8:
	mov r0, #0x0
	bx lr
	.balign 4
_02031BEC: .word UNK_021C5A00
_02031BF0: .word FUN_020324F8

	thumb_func_start FUN_02031BF4
FUN_02031BF4: ; 0x02031BF4
	push {r3, lr}
	ldr r0, _02031C08 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031C06
	ldr r0, _02031C0C ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02031C06:
	pop {r3, pc}
	.balign 4
_02031C08: .word UNK_021C5A00
_02031C0C: .word FUN_02032440

	thumb_func_start FUN_02031C10
FUN_02031C10: ; 0x02031C10
	push {r3, lr}
	ldr r0, _02031C28 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02031C24
	mov r0, #0x1
	add r1, #0x48
	strb r0, [r1, #0x0]
	bl FUN_0202D344
_02031C24:
	pop {r3, pc}
	nop
_02031C28: .word UNK_021C5A00

	thumb_func_start FUN_02031C2C
FUN_02031C2C: ; 0x02031C2C
	push {r3, lr}
	ldr r0, _02031C4C ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02031C48
	mov r0, #0x1
	add r1, #0x48
	strb r0, [r1, #0x0]
	bl FUN_0202D344
	ldr r0, _02031C50 ; =FUN_02032850
	mov r1, #0x0
	bl FUN_02031D20
_02031C48:
	pop {r3, pc}
	nop
_02031C4C: .word UNK_021C5A00
_02031C50: .word FUN_02032850

	thumb_func_start FUN_02031C54
FUN_02031C54: ; 0x02031C54
	ldr r0, _02031C60 ; =UNK_021C5A00
	mov r1, #0x12
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_02031C60: .word UNK_021C5A00

	thumb_func_start FUN_02031C64
FUN_02031C64: ; 0x02031C64
	ldr r0, _02031C70 ; =UNK_021C5A00
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_02031C70: .word UNK_021C5A00

	thumb_func_start FUN_02031C74
FUN_02031C74: ; 0x02031C74
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02031C9C
	ldr r2, _02031CA0 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02031734
	ldr r0, _02031CA4 ; =FUN_02032E00
	mov r1, #0x0
	bl FUN_02031D20
_02031C9C:
	pop {r3-r5, pc}
	nop
_02031CA0: .word 0x00007080
_02031CA4: .word FUN_02032E00

	thumb_func_start FUN_02031CA8
FUN_02031CA8: ; 0x02031CA8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02031CD0
	ldr r2, _02031CD4 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02031734
	ldr r0, _02031CD8 ; =FUN_02032E48
	mov r1, #0x0
	bl FUN_02031D20
_02031CD0:
	pop {r3-r5, pc}
	nop
_02031CD4: .word 0x00007080
_02031CD8: .word FUN_02032E48

	thumb_func_start FUN_02031CDC
FUN_02031CDC: ; 0x02031CDC
	push {r3, lr}
	ldr r0, _02031D1C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031CEE
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _02031CEE
	blx r0
_02031CEE:
	bl FUN_02033590
	cmp r0, #0x0
	beq _02031D04
	bl MOD04_021DDB08
	mov r1, #0x3
	sub r0, r1, r0
	bl FUN_02033EEC
	pop {r3, pc}
_02031D04:
	bl FUN_0202EDF8
	cmp r0, #0x0
	beq _02031D18
	bl WM_GetLinkLevel
	mov r1, #0x3
	sub r0, r1, r0
	bl FUN_02033EEC
_02031D18:
	pop {r3, pc}
	nop
_02031D1C: .word UNK_021C5A00

	thumb_func_start FUN_02031D20
FUN_02031D20: ; 0x02031D20
	ldr r2, _02031D2C ; =UNK_021C5A00
	ldr r3, [r2, #0x0]
	str r0, [r3, #0x24]
	ldr r0, [r2, #0x0]
	strh r1, [r0, #0x3a]
	bx lr
	.balign 4
_02031D2C: .word UNK_021C5A00

	thumb_func_start FUN_02031D30
FUN_02031D30: ; 0x02031D30
	push {r3-r5, lr}
	ldr r0, _02031DF8 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02031D42
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3-r5, pc}
_02031D42:
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02031DF6
	ldr r0, _02031DF8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02031DF8 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	bl FUN_02031268
	bl FUN_02030FA8
	ldr r0, _02031DF8 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031DC8
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	mov r0, #0x1
	mov r2, #0x7d
	lsl r2, r2, #0x2
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _02031DF6
	ldr r0, _02031DF8 ; =UNK_021C5A00
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
	add r4, #0xc
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #0xc]
	ldr r3, [r4, #0x4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #0xc]
	str r3, [r4, #0x4]
	add r0, r3, #0x0
	mov r1, #0x0
	mov r2, #0x14
	mov r3, #0x0
	bl _ll_mul
	mov r0, #0x0
	add r5, #0x43
	strb r0, [r5, #0x0]
	ldr r0, _02031DFC ; =FUN_020320C4
	add r1, #0x14
	bl FUN_02031D20
	pop {r3-r5, pc}
_02031DC8:
	mov r0, #0x1
	mov r2, #0x7d
	add r1, r0, #0x0
	lsl r2, r2, #0x2
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02031DF6
	ldr r0, _02031DF8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4c
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031DEE
	ldr r0, _02031E00 ; =FUN_020323B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3-r5, pc}
_02031DEE:
	ldr r0, _02031E04 ; =FUN_02031EE0
	mov r1, #0x40
	bl FUN_02031D20
_02031DF6:
	pop {r3-r5, pc}
	.balign 4
_02031DF8: .word UNK_021C5A00
_02031DFC: .word FUN_020320C4
_02031E00: .word FUN_020323B8
_02031E04: .word FUN_02031EE0

	thumb_func_start FUN_02031E08
FUN_02031E08: ; 0x02031E08
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02031E7C
	mov r0, #0x1
	bl FUN_02031268
	bl FUN_02030FA8
	ldr r0, _02031E80 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02031E32
	ldr r0, _02031E84 ; =FUN_02032058
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3-r5, pc}
_02031E32:
	mov r2, #0x7d
	mov r0, #0x0
	mov r1, #0x1
	lsl r2, r2, #0x2
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02031E7C
	ldr r0, _02031E80 ; =UNK_021C5A00
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
	add r4, #0xc
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #0xc]
	ldr r3, [r4, #0x4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #0xc]
	mov r1, #0x0
	str r3, [r4, #0x4]
	lsr r0, r3, #0x1a
	lsl r1, r1, #0x6
	orr r1, r0
	ldrh r0, [r5, #0x38]
	cmp r0, #0x0
	beq _02031E76
	lsl r1, r0, #0x6
	mov r0, #0x0
	strh r0, [r5, #0x38]
_02031E76:
	ldr r0, _02031E88 ; =FUN_02031EE0
	bl FUN_02031D20
_02031E7C:
	pop {r3-r5, pc}
	nop
_02031E80: .word UNK_021C5A00
_02031E84: .word FUN_02032058
_02031E88: .word FUN_02031EE0

	thumb_func_start FUN_02031E8C
FUN_02031E8C: ; 0x02031E8C
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02031ED6
	mov r0, #0x0
	mov r2, #0x7d
	add r1, r0, #0x0
	lsl r2, r2, #0x2
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02031ED6
	ldr r0, _02031ED8 ; =UNK_021C5A00
	ldr r4, [r0, #0x0]
	add r5, r4, #0x0
	add r5, #0xc
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #0xc]
	ldr r3, [r5, #0x4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	mov r1, #0x0
	lsr r2, r3, #0x1b
	lsl r1, r1, #0x5
	orr r1, r2
	ldr r0, _02031EDC ; =FUN_02031EE0
	add r1, #0x10
	str r3, [r5, #0x4]
	bl FUN_02031D20
_02031ED6:
	pop {r3-r5, pc}
	.balign 4
_02031ED8: .word UNK_021C5A00
_02031EDC: .word FUN_02031EE0

	thumb_func_start FUN_02031EE0
FUN_02031EE0: ; 0x02031EE0
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _02031F54 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x4f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02031F50
	add r1, #0x4b
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	bne _02031F50
	bl FUN_0202E8F4
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02031F1A
	ldr r1, _02031F54 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _02031F58 ; =FUN_02031F60
	mov r1, #0x20
	bl FUN_02031D20
	pop {r3, pc}
_02031F1A:
	ldr r0, _02031F54 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02031F2A
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02031F2A:
	bl FUN_0202E950
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02031F48
	ldr r1, _02031F54 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	add r1, #0x3e
	strb r0, [r1, #0x0]
	ldr r0, _02031F58 ; =FUN_02031F60
	mov r1, #0x20
	bl FUN_02031D20
	pop {r3, pc}
_02031F48:
	ldr r0, _02031F5C ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
_02031F50:
	pop {r3, pc}
	nop
_02031F54: .word UNK_021C5A00
_02031F58: .word FUN_02031F60
_02031F5C: .word FUN_02032028

	thumb_func_start FUN_02031F60
FUN_02031F60: ; 0x02031F60
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _02031FBC ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202E8A0
	cmp r0, #0x0
	beq _02031F90
	ldr r0, _02031FBC ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _02031F90
	ldr r0, _02031FC0 ; =FUN_02031FC8
	mov r1, #0x64
	bl FUN_02031D20
	pop {r3, pc}
_02031F90:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02031FA2
	ldr r0, _02031FC4 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02031FA2:
	ldr r0, _02031FBC ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02031FB2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02031FB2:
	ldr r0, _02031FC4 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02031FBC: .word UNK_021C5A00
_02031FC0: .word FUN_02031FC8
_02031FC4: .word FUN_02032028

	thumb_func_start FUN_02031FC8
FUN_02031FC8: ; 0x02031FC8
	push {r3, lr}
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02031FEE
	bl FUN_0202FC60
	mov r0, #0x0
	bl FUN_02031268
	bl FUN_02030FA8
	ldr r0, _0203201C ; =FUN_0203213C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02031FEE:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02032000
	ldr r0, _02032020 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032000:
	ldr r0, _02032024 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032010
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032010:
	ldr r0, _02032020 ; =FUN_02032028
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_0203201C: .word FUN_0203213C
_02032020: .word FUN_02032028
_02032024: .word UNK_021C5A00

	thumb_func_start FUN_02032028
FUN_02032028: ; 0x02032028
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203203A
	ldr r0, _0203203C ; =FUN_02032058
	mov r1, #0x0
	bl FUN_02031D20
_0203203A:
	pop {r3, pc}
	.balign 4
_0203203C: .word FUN_02032058

	thumb_func_start FUN_02032040
FUN_02032040: ; 0x02032040
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _02032052
	ldr r0, _02032054 ; =FUN_02031E8C
	mov r1, #0x0
	bl FUN_02031D20
_02032052:
	pop {r3, pc}
	.balign 4
_02032054: .word FUN_02031E8C

	thumb_func_start FUN_02032058
FUN_02032058: ; 0x02032058
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _020320BA
	mov r0, #0x1
	bl FUN_02031268
	ldr r1, _020320BC ; =UNK_021C5A00
	mov r2, #0x7d
	ldr r1, [r1, #0x0]
	mov r0, #0x0
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	lsl r2, r2, #0x2
	mov r3, #0x1
	bl FUN_0202F918
	cmp r0, #0x0
	beq _020320BA
	ldr r0, _020320BC ; =UNK_021C5A00
	ldr r5, [r0, #0x0]
	add r4, r5, #0x0
	add r4, #0xc
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #0xc]
	ldr r3, [r4, #0x4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #0xc]
	str r3, [r4, #0x4]
	add r0, r3, #0x0
	mov r1, #0x0
	mov r2, #0x14
	mov r3, #0x0
	bl _ll_mul
	mov r0, #0x0
	add r5, #0x43
	strb r0, [r5, #0x0]
	ldr r0, _020320C0 ; =FUN_020320C4
	add r1, #0x14
	bl FUN_02031D20
_020320BA:
	pop {r3-r5, pc}
	.balign 4
_020320BC: .word UNK_021C5A00
_020320C0: .word FUN_020320C4

	thumb_func_start FUN_020320C4
FUN_020320C4: ; 0x020320C4
	push {r3, lr}
	bl FUN_020311E8
	cmp r0, #0x0
	beq _020320E2
	ldr r0, _0203210C ; =UNK_021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	ldr r0, _02032110 ; =FUN_02032118
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020320E2:
	ldr r0, _0203210C ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020320F2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020320F2:
	add r1, #0x4a
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0203210A
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203210A
	ldr r0, _02032114 ; =FUN_02032040
	mov r1, #0x2
	bl FUN_02031D20
_0203210A:
	pop {r3, pc}
	.balign 4
_0203210C: .word UNK_021C5A00
_02032110: .word FUN_02032118
_02032114: .word FUN_02032040

	thumb_func_start FUN_02032118
FUN_02032118: ; 0x02032118
	push {r3, lr}
	mov r0, #0x0
	bl FUN_02031268
	mov r0, #0x1
	bl FUN_0202EE84
	bl FUN_02030FA8
	ldr r0, _02032134 ; =FUN_02032138
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032134: .word FUN_02032138

	thumb_func_start FUN_02032138
FUN_02032138: ; 0x02032138
	bx lr
	.balign 4

	thumb_func_start FUN_0203213C
FUN_0203213C: ; 0x0203213C
	bx lr
	.balign 4

	thumb_func_start FUN_02032140
FUN_02032140: ; 0x02032140
	push {r3, lr}
	ldr r0, _02032170 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x13
	bhs _02032166
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203216E
	mov r0, #0x1
	bl FUN_02031268
	bl FUN_02030FA8
	mov r0, #0x1
	bl FUN_0202E7B0
_02032166:
	ldr r0, _02032174 ; =FUN_020323B8
	mov r1, #0x0
	bl FUN_02031D20
_0203216E:
	pop {r3, pc}
	.balign 4
_02032170: .word UNK_021C5A00
_02032174: .word FUN_020323B8

	thumb_func_start FUN_02032178
FUN_02032178: ; 0x02032178
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203218E
	bl FUN_0202FC60
	ldr r0, _02032190 ; =FUN_02032140
	mov r1, #0x0
	bl FUN_02031D20
_0203218E:
	pop {r3, pc}
	.balign 4
_02032190: .word FUN_02032140

	thumb_func_start FUN_02032194
FUN_02032194: ; 0x02032194
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _020321B0
	mov r0, #0x0
	bl FUN_0202E7B0
	bl FUN_0202FC60
	ldr r0, _020321B4 ; =FUN_02031E08
	mov r1, #0x0
	bl FUN_02031D20
_020321B0:
	pop {r3, pc}
	nop
_020321B4: .word FUN_02031E08

	thumb_func_start FUN_020321B8
FUN_020321B8: ; 0x020321B8
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020321CA
	ldr r0, _020321CC ; =FUN_02031E08
	mov r1, #0x0
	bl FUN_02031D20
_020321CA:
	pop {r3, pc}
	.balign 4
_020321CC: .word FUN_02031E08

	thumb_func_start FUN_020321D0
FUN_020321D0: ; 0x020321D0
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _0203220C
	ldr r0, _02032210 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032210 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _0203220C
	bl FUN_0202FA10
	ldr r0, _02032214 ; =FUN_02032218
	mov r1, #0x0
	bl FUN_02031D20
_0203220C:
	pop {r3, pc}
	nop
_02032210: .word UNK_021C5A00
_02032214: .word FUN_02032218

	thumb_func_start FUN_02032218
FUN_02032218: ; 0x02032218
	push {r3, lr}
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0203222E
	ldr r0, _02032230 ; =FUN_02032234
	mov r1, #0x0
	bl FUN_02031D20
_0203222E:
	pop {r3, pc}
	.balign 4
_02032230: .word FUN_02032234

	thumb_func_start FUN_02032234
FUN_02032234: ; 0x02032234
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02032246
	ldr r0, _02032248 ; =FUN_020323BC
	mov r1, #0x0
	bl FUN_02031D20
_02032246:
	pop {r3, pc}
	.balign 4
_02032248: .word FUN_020323BC

	thumb_func_start FUN_0203224C
FUN_0203224C: ; 0x0203224C
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032286
	ldr r0, _02032288 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032288 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldr r0, [r1, #0x28]
	ldr r1, [r1, #0x30]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032286
	bl FUN_0202FA10
	ldr r0, _0203228C ; =FUN_02032290
	mov r1, #0x0
	bl FUN_02031D20
_02032286:
	pop {r3, pc}
	.balign 4
_02032288: .word UNK_021C5A00
_0203228C: .word FUN_02032290

	thumb_func_start FUN_02032290
FUN_02032290: ; 0x02032290
	ldr r3, _02032294 ; =FUN_0202EA54
	bx r3
	.balign 4
_02032294: .word FUN_0202EA54

	thumb_func_start FUN_02032298
FUN_02032298: ; 0x02032298
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _020322B8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _020322B6
	ldr r0, _020322BC ; =FUN_020322C0
	mov r1, #0xa
	bl FUN_02031D20
_020322B6:
	pop {r3, pc}
	.balign 4
_020322B8: .word UNK_021C5A00
_020322BC: .word FUN_020322C0

	thumb_func_start FUN_020322C0
FUN_020322C0: ; 0x020322C0
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020322D2
	ldr r0, _020322F0 ; =FUN_020322F8
	mov r1, #0x0
	bl FUN_02031D20
_020322D2:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _020322EE
	bl FUN_02031190
	cmp r0, #0x0
	beq _020322EE
	ldr r0, _020322F4 ; =FUN_0203234C
	mov r1, #0x0
	bl FUN_02031D20
_020322EE:
	pop {r3, pc}
	.balign 4
_020322F0: .word FUN_020322F8
_020322F4: .word FUN_0203234C

	thumb_func_start FUN_020322F8
FUN_020322F8: ; 0x020322F8
	push {r3, lr}
	bl FUN_0202E6F0
	ldr r0, _02032308 ; =FUN_0203230C
	mov r1, #0x2
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032308: .word FUN_0203230C

	thumb_func_start FUN_0203230C
FUN_0203230C: ; 0x0203230C
	push {r3, lr}
	ldr r0, _02032344 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _0203231E
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_0203231E:
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02032340
	mov r1, #0x1
	mov r0, #0x0
	lsl r2, r1, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032340
	bl FUN_0202FA10
	ldr r0, _02032348 ; =FUN_02032298
	mov r1, #0xa
	bl FUN_02031D20
_02032340:
	pop {r3, pc}
	nop
_02032344: .word UNK_021C5A00
_02032348: .word FUN_02032298

	thumb_func_start FUN_0203234C
FUN_0203234C: ; 0x0203234C
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _0203235E
	ldr r0, _02032360 ; =FUN_020323BC
	mov r1, #0x0
	bl FUN_02031D20
_0203235E:
	pop {r3, pc}
	.balign 4
_02032360: .word FUN_020323BC

	thumb_func_start FUN_02032364
FUN_02032364: ; 0x02032364
	push {r3, lr}
	bl FUN_0202E6F0
	ldr r0, _02032374 ; =FUN_02032378
	mov r1, #0x2
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032374: .word FUN_02032378

	thumb_func_start FUN_02032378
FUN_02032378: ; 0x02032378
	push {r3, lr}
	ldr r0, _020323B0 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _0203238A
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_0203238A:
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _020323AC
	mov r1, #0x1
	mov r0, #0x0
	lsl r2, r1, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _020323AC
	bl FUN_0202FA10
	ldr r0, _020323B4 ; =FUN_02032290
	mov r1, #0xa
	bl FUN_02031D20
_020323AC:
	pop {r3, pc}
	nop
_020323B0: .word UNK_021C5A00
_020323B4: .word FUN_02032290

	thumb_func_start FUN_020323B8
FUN_020323B8: ; 0x020323B8
	bx lr
	.balign 4

	thumb_func_start FUN_020323BC
FUN_020323BC: ; 0x020323BC
	push {r3, lr}
	bl FUN_02030F40
	cmp r0, #0x0
	bne _020323CA
	bl FUN_020317C0
_020323CA:
	pop {r3, pc}

	thumb_func_start FUN_020323CC
FUN_020323CC: ; 0x020323CC
	ldr r3, _020323D4 ; =FUN_02031D20
	ldr r0, _020323D8 ; =FUN_02032440
	mov r1, #0x5
	bx r3
	.balign 4
_020323D4: .word FUN_02031D20
_020323D8: .word FUN_02032440

	thumb_func_start FUN_020323DC
FUN_020323DC: ; 0x020323DC
	push {r3, lr}
	bl FUN_02030F20
	cmp r0, #0x1
	bgt _020323F8
	mov r0, #0x0
	bl FUN_0202D36C
	bl FUN_0202FC80
	ldr r0, _0203241C ; =FUN_020324F8
	mov r1, #0x0
	bl FUN_02031D20
_020323F8:
	ldr r0, _02032420 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032408
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032408:
	mov r0, #0x0
	bl FUN_0202D36C
	bl FUN_0202FC80
	ldr r0, _0203241C ; =FUN_020324F8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_0203241C: .word FUN_020324F8
_02032420: .word UNK_021C5A00

	thumb_func_start FUN_02032424
FUN_02032424: ; 0x02032424
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203243A
	bl FUN_0202FC60
	ldr r0, _0203243C ; =FUN_020324F8
	mov r1, #0x0
	bl FUN_02031D20
_0203243A:
	pop {r3, pc}
	.balign 4
_0203243C: .word FUN_020324F8

	thumb_func_start FUN_02032440
FUN_02032440: ; 0x02032440
	push {r3, lr}
	ldr r0, _02032470 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032450
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
_02032450:
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203246E
	ldr r0, _02032470 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x3a]
	cmp r0, #0x0
	bne _0203246E
	bl FUN_0202FA5C
	ldr r0, _02032474 ; =FUN_020323BC
	mov r1, #0x0
	bl FUN_02031D20
_0203246E:
	pop {r3, pc}
	.balign 4
_02032470: .word UNK_021C5A00
_02032474: .word FUN_020323BC

	thumb_func_start FUN_02032478
FUN_02032478: ; 0x02032478
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _020324BE
	ldr r0, _020324C0 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _020324C0 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3c
	ldrb r0, [r0, #0x0]
	bl FUN_0202D1B0
	ldr r0, _020324C0 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _020324BE
	bl FUN_0202FA10
	ldr r0, _020324C4 ; =FUN_020324C8
	mov r1, #0x40
	bl FUN_02031D20
_020324BE:
	pop {r3, pc}
	.balign 4
_020324C0: .word UNK_021C5A00
_020324C4: .word FUN_020324C8

	thumb_func_start FUN_020324C8
FUN_020324C8: ; 0x020324C8
	push {r3, lr}
	bl FUN_0202EA54
	ldr r0, _020324F0 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020324DE
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020324DE:
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020324EE
	ldr r0, _020324F4 ; =FUN_02032510
	mov r1, #0x0
	bl FUN_02031D20
_020324EE:
	pop {r3, pc}
	.balign 4
_020324F0: .word UNK_021C5A00
_020324F4: .word FUN_02032510

	thumb_func_start FUN_020324F8
FUN_020324F8: ; 0x020324F8
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203250A
	ldr r0, _0203250C ; =FUN_02032510
	mov r1, #0x0
	bl FUN_02031D20
_0203250A:
	pop {r3, pc}
	.balign 4
_0203250C: .word FUN_02032510

	thumb_func_start FUN_02032510
FUN_02032510: ; 0x02032510
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02032568
	ldr r1, _0203256C ; =UNK_021C5A00
	mov r2, #0x2
	ldr r1, [r1, #0x0]
	mov r0, #0x0
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	lsl r2, r2, #0x8
	mov r3, #0x1
	bl FUN_0202F918
	cmp r0, #0x0
	beq _02032568
	ldr r0, _0203256C ; =UNK_021C5A00
	ldr r4, [r0, #0x0]
	add r5, r4, #0x0
	add r5, #0xc
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #0xc]
	ldr r3, [r5, #0x4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	str r3, [r5, #0x4]
	bl FUN_0202FA10
	ldr r0, _0203256C ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	ldr r0, _02032570 ; =FUN_02032578
	ldr r1, _02032574 ; =0x00002710
	bl FUN_02031D20
_02032568:
	pop {r3-r5, pc}
	nop
_0203256C: .word UNK_021C5A00
_02032570: .word FUN_02032578
_02032574: .word 0x00002710

	thumb_func_start FUN_02032578
FUN_02032578: ; 0x02032578
	push {r3, lr}
	bl FUN_0202F104
	cmp r0, #0x0
	bne _020325B2
	bl FUN_020311E8
	cmp r0, #0x0
	beq _020325A2
	ldr r0, _020325C4 ; =UNK_021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x43
	strb r1, [r0, #0x0]
	bl FUN_02033E74
	ldr r0, _020325C8 ; =FUN_020327FC
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020325A2:
	ldr r0, _020325C4 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020325B2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020325B2:
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020325C2
	ldr r0, _020325CC ; =FUN_020325D0
	mov r1, #0x0
	bl FUN_02031D20
_020325C2:
	pop {r3, pc}
	.balign 4
_020325C4: .word UNK_021C5A00
_020325C8: .word FUN_020327FC
_020325CC: .word FUN_020325D0

	thumb_func_start FUN_020325D0
FUN_020325D0: ; 0x020325D0
	push {r3-r5, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203261C
	mov r0, #0x0
	mov r2, #0x2
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	bl FUN_0202F950
	cmp r0, #0x0
	beq _0203261C
	bl FUN_0202FA10
	ldr r0, _02032620 ; =UNK_021C5A00
	ldr r4, [r0, #0x0]
	add r5, r4, #0x0
	add r5, #0xc
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #0xc]
	ldr r3, [r5, #0x4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #0xc]
	mov r1, #0x0
	ldr r0, _02032624 ; =FUN_020324C8
	lsr r2, r3, #0x1b
	lsl r1, r1, #0x5
	orr r1, r2
	str r3, [r5, #0x4]
	bl FUN_02031D20
_0203261C:
	pop {r3-r5, pc}
	nop
_02032620: .word UNK_021C5A00
_02032624: .word FUN_020324C8

	thumb_func_start FUN_02032628
FUN_02032628: ; 0x02032628
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203263A
	ldr r0, _0203263C ; =FUN_02032640
	mov r1, #0x0
	bl FUN_02031D20
_0203263A:
	pop {r3, pc}
	.balign 4
_0203263C: .word FUN_02032640

	thumb_func_start FUN_02032640
FUN_02032640: ; 0x02032640
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _02032666
	mov r0, #0x0
	mov r2, #0x2
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032666
	bl FUN_0202FA10
	ldr r0, _02032668 ; =FUN_0203266C
	mov r1, #0x64
	bl FUN_02031D20
_02032666:
	pop {r3, pc}
	.balign 4
_02032668: .word FUN_0203266C

	thumb_func_start FUN_0203266C
FUN_0203266C: ; 0x0203266C
	push {r3, lr}
	ldr r0, _020326C4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202E8A0
	cmp r0, #0x0
	beq _02032698
	ldr r0, _020326C4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _02032698
	ldr r0, _020326C8 ; =FUN_020326D0
	mov r1, #0x64
	bl FUN_02031D20
	pop {r3, pc}
_02032698:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020326AA
	ldr r0, _020326CC ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020326AA:
	ldr r0, _020326C4 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _020326BA
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_020326BA:
	ldr r0, _020326CC ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_020326C4: .word UNK_021C5A00
_020326C8: .word FUN_020326D0
_020326CC: .word FUN_020327B8

	thumb_func_start FUN_020326D0
FUN_020326D0: ; 0x020326D0
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020326E4
	ldr r0, _02032728 ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020326E4:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _0203270C
	ldr r0, _0203272C ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
	ldr r1, _02032730 ; =UNK_02105D5C
	mov r0, #0x6
	bl FUN_020311D0
	ldr r0, _02032734 ; =FUN_02032738
	mov r1, #0x78
	bl FUN_02031D20
	pop {r3, pc}
_0203270C:
	ldr r0, _0203272C ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _0203271C
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_0203271C:
	ldr r0, _02032728 ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_02032728: .word FUN_020327B8
_0203272C: .word UNK_021C5A00
_02032730: .word UNK_02105D5C
_02032734: .word FUN_02032738

	thumb_func_start FUN_02032738
FUN_02032738: ; 0x02032738
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _0203274C
	ldr r0, _0203278C ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_0203274C:
	ldr r0, _02032790 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x3d
	ldrb r0, [r0, #0x0]
	cmp r0, #0x2
	bne _02032764
	ldr r0, _02032794 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032764:
	cmp r0, #0x1
	bne _02032776
	bl FUN_0202DBE0
	ldr r0, _02032798 ; =FUN_0203279C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032776:
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	beq _02032782
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032782:
	ldr r0, _0203278C ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_0203278C: .word FUN_020327B8
_02032790: .word UNK_021C5A00
_02032794: .word FUN_020327B4
_02032798: .word FUN_0203279C

	thumb_func_start FUN_0203279C
FUN_0203279C: ; 0x0203279C
	push {r3, lr}
	bl FUN_020311F0
	cmp r0, #0x0
	beq _020327AE
	ldr r0, _020327B0 ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
_020327AE:
	pop {r3, pc}
	.balign 4
_020327B0: .word FUN_020327B8

	thumb_func_start FUN_020327B4
FUN_020327B4: ; 0x020327B4
	bx lr
	.balign 4

	thumb_func_start FUN_020327B8
FUN_020327B8: ; 0x020327B8
	push {r3, lr}
	ldr r0, _020327F0 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _020327EC
	ldr r0, _020327F0 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x38]
	cmp r0, #0x0
	beq _020327E4
	sub r0, r0, #0x1
	strh r0, [r1, #0x38]
	ldr r0, _020327F4 ; =FUN_02032640
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020327E4:
	ldr r0, _020327F8 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
_020327EC:
	pop {r3, pc}
	nop
_020327F0: .word UNK_021C5A00
_020327F4: .word FUN_02032640
_020327F8: .word FUN_020327B4

	thumb_func_start FUN_020327FC
FUN_020327FC: ; 0x020327FC
	push {r3, lr}
	bl FUN_020311E8
	cmp r0, #0x0
	bne _02032820
	bl FUN_02033510
	cmp r0, #0x0
	bne _0203282C
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _0203282C
	ldr r0, _02032848 ; =FUN_020325D0
	mov r1, #0x0
	bl FUN_02031D20
	b _0203282C
_02032820:
	bl FUN_02031190
	cmp r0, #0x0
	bne _0203282C
	bl FUN_0202DDE8
_0203282C:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02032844
	bl FUN_02033510
	cmp r0, #0x0
	bne _02032844
	ldr r0, _0203284C ; =FUN_020327B8
	mov r1, #0x0
	bl FUN_02031D20
_02032844:
	pop {r3, pc}
	nop
_02032848: .word FUN_020325D0
_0203284C: .word FUN_020327B8

	thumb_func_start FUN_02032850
FUN_02032850: ; 0x02032850
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203287E
	ldr r1, _02032880 ; =UNK_021C5A00
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	mov r2, #0x2
	add r1, #0x43
	ldrb r1, [r1, #0x0]
	lsl r2, r2, #0x8
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _0203287E
	bl FUN_0202FA10
	ldr r0, _02032884 ; =FUN_020323B8
	mov r1, #0x0
	bl FUN_02031D20
_0203287E:
	pop {r3, pc}
	.balign 4
_02032880: .word UNK_021C5A00
_02032884: .word FUN_020323B8

	thumb_func_start FUN_02032888
FUN_02032888: ; 0x02032888
	push {r3, lr}
	ldr r0, _020328BC ; =UNK_021C5A00
	mov r1, #0xd
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bl FUN_02031190
	cmp r0, #0x0
	add r0, sp, #0x0
	bne _020328AE
	mov r1, #0x0
	strb r1, [r0, #0x1]
	add r1, sp, #0x0
	mov r0, #0xa
	add r1, #0x1
	bl FUN_020311D0
	pop {r3, pc}
_020328AE:
	mov r1, #0x0
	strb r1, [r0, #0x0]
	mov r0, #0xa
	add r1, sp, #0x0
	bl FUN_020311D0
	pop {r3, pc}
	.balign 4
_020328BC: .word UNK_021C5A00

	thumb_func_start FUN_020328C0
FUN_020328C0: ; 0x020328C0
	ldr r1, _020328D8 ; =UNK_021C5A00
	ldr r3, _020328DC ; =FUN_02031D20
	ldr r2, [r1, #0x0]
	add r2, #0x3e
	strb r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x3
	strh r2, [r0, #0x38]
	ldr r0, _020328E0 ; =FUN_02032924
	mov r1, #0x0
	bx r3
	nop
_020328D8: .word UNK_021C5A00
_020328DC: .word FUN_02031D20
_020328E0: .word FUN_02032924

	thumb_func_start FUN_020328E4
FUN_020328E4: ; 0x020328E4
	ldr r0, _020328F0 ; =UNK_021C5A00
	mov r1, #0x7
	ldr r0, [r0, #0x0]
	add r0, #0x3f
	strb r1, [r0, #0x0]
	bx lr
	.balign 4
_020328F0: .word UNK_021C5A00

	thumb_func_start FUN_020328F4
FUN_020328F4: ; 0x020328F4
	push {r3, lr}
	ldr r1, _0203291C ; =UNK_021C5A00
	ldr r2, [r1, #0x0]
	add r2, #0x3e
	strb r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x7
	add r0, #0x3f
	strb r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	mov r2, #0x3
	strh r2, [r0, #0x38]
	bl FUN_02033E74
	ldr r0, _02032920 ; =FUN_02032628
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	nop
_0203291C: .word UNK_021C5A00
_02032920: .word FUN_02032628

	thumb_func_start FUN_02032924
FUN_02032924: ; 0x02032924
	push {r3, lr}
	bl FUN_0202E6F0
	cmp r0, #0x0
	beq _02032936
	ldr r0, _02032938 ; =FUN_0203293C
	mov r1, #0x0
	bl FUN_02031D20
_02032936:
	pop {r3, pc}
	.balign 4
_02032938: .word FUN_0203293C

	thumb_func_start FUN_0203293C
FUN_0203293C: ; 0x0203293C
	push {r3, lr}
	bl FUN_0202EE0C
	cmp r0, #0x0
	beq _0203296C
	ldr r0, _02032970 ; =UNK_021C5A00
	mov r2, #0x2
	ldr r0, [r0, #0x0]
	mov r1, #0xd
	add r0, #0x3f
	strb r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r0, #0x0
	lsl r2, r2, #0x8
	bl FUN_0202F950
	cmp r0, #0x0
	beq _0203296C
	bl FUN_0202FA1C
	ldr r0, _02032974 ; =FUN_02032978
	mov r1, #0x64
	bl FUN_02031D20
_0203296C:
	pop {r3, pc}
	nop
_02032970: .word UNK_021C5A00
_02032974: .word FUN_02032978

	thumb_func_start FUN_02032978
FUN_02032978: ; 0x02032978
	push {r3, lr}
	ldr r0, _020329E4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202E8A0
	cmp r0, #0x0
	beq _020329A4
	ldr r0, _020329E4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x3e
	ldrb r0, [r0, #0x0]
	bl FUN_0202FB18
	cmp r0, #0x0
	beq _020329A4
	ldr r0, _020329E8 ; =FUN_020329F4
	mov r1, #0x64
	bl FUN_02031D20
	pop {r3, pc}
_020329A4:
	bl FUN_020311F0
	cmp r0, #0x0
	bne _020329B6
	ldr r0, _020329E4 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x0
	bne _020329DC
_020329B6:
	ldr r0, _020329E4 ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	ldrh r1, [r2, #0x38]
	sub r1, r1, #0x1
	strh r1, [r2, #0x38]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x38]
	cmp r0, #0x0
	bne _020329D2
	ldr r0, _020329EC ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020329D2:
	ldr r0, _020329F0 ; =FUN_02032924
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020329DC:
	beq _020329E2
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
_020329E2:
	pop {r3, pc}
	.balign 4
_020329E4: .word UNK_021C5A00
_020329E8: .word FUN_020329F4
_020329EC: .word FUN_020327B4
_020329F0: .word FUN_02032924

	thumb_func_start FUN_020329F4
FUN_020329F4: ; 0x020329F4
	push {r3, lr}
	ldr r0, _02032A7C ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	ldrh r0, [r1, #0x3a]
	cmp r0, #0x5a
	bls _02032A06
	sub r0, r0, #0x1
	strh r0, [r1, #0x3a]
	pop {r3, pc}
_02032A06:
	bl FUN_020311F0
	cmp r0, #0x0
	beq _02032A34
	ldr r0, _02032A7C ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	ldrh r1, [r2, #0x38]
	sub r1, r1, #0x1
	strh r1, [r2, #0x38]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x38]
	cmp r0, #0x0
	bne _02032A2A
	ldr r0, _02032A80 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A2A:
	ldr r0, _02032A84 ; =FUN_02032924
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A34:
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0x0
	beq _02032A4A
	ldr r0, _02032A88 ; =FUN_0203279C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A4A:
	ldr r0, _02032A7C ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	ldrh r1, [r2, #0x3a]
	cmp r1, #0x0
	beq _02032A5A
	sub r0, r1, #0x1
	strh r0, [r2, #0x3a]
	pop {r3, pc}
_02032A5A:
	ldrh r1, [r2, #0x38]
	sub r1, r1, #0x1
	strh r1, [r2, #0x38]
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x38]
	cmp r0, #0x0
	bne _02032A72
	ldr r0, _02032A80 ; =FUN_020327B4
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032A72:
	ldr r0, _02032A84 ; =FUN_02032924
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
	.balign 4
_02032A7C: .word UNK_021C5A00
_02032A80: .word FUN_020327B4
_02032A84: .word FUN_02032924
_02032A88: .word FUN_0203279C

	thumb_func_start FUN_02032A8C
FUN_02032A8C: ; 0x02032A8C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r2, #0x0
	bl FUN_02031190
	cmp r0, #0x0
	bne _02032ADA
	ldr r6, _02032ADC ; =UNK_02105D5C
	mov r3, #0x1
	mov r2, #0x0
_02032AA0:
	ldrb r1, [r6, #0x0]
	ldrb r0, [r4, r2]
	cmp r1, r0
	beq _02032AAC
	mov r3, #0x0
	b _02032AB4
_02032AAC:
	add r2, r2, #0x1
	add r6, r6, #0x1
	cmp r2, #0x6
	blo _02032AA0
_02032AB4:
	cmp r3, #0x0
	beq _02032AD0
	ldr r0, _02032AE0 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02032AD0
	ldr r1, _02032AE4 ; =UNK_02105D6C
	mov r0, #0x7
	strb r5, [r1, #0x0]
	bl FUN_02030C4C
	pop {r4-r6, pc}
_02032AD0:
	ldr r1, _02032AE8 ; =UNK_02105D64
	mov r0, #0x7
	strb r5, [r1, #0x0]
	bl FUN_02030C4C
_02032ADA:
	pop {r4-r6, pc}
	.balign 4
_02032ADC: .word UNK_02105D5C
_02032AE0: .word UNK_021C5A00
_02032AE4: .word UNK_02105D6C
_02032AE8: .word UNK_02105D64

	thumb_func_start FUN_02032AEC
FUN_02032AEC: ; 0x02032AEC
	push {r3-r5, lr}
	mov r4, #0x1
	ldr r5, _02032B5C ; =UNK_02105D6C + 1
	add r3, r4, #0x0
_02032AF4:
	ldrb r1, [r5, #0x0]
	ldrb r0, [r2, r3]
	cmp r1, r0
	beq _02032B00
	mov r4, #0x0
	b _02032B08
_02032B00:
	add r3, r3, #0x1
	add r5, r5, #0x1
	cmp r3, #0x6
	blo _02032AF4
_02032B08:
	cmp r4, #0x0
	beq _02032B22
	ldrb r4, [r2, #0x0]
	bl FUN_02031190
	cmp r4, r0
	bne _02032B58
	ldr r0, _02032B60 ; =UNK_021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
	pop {r3-r5, pc}
_02032B22:
	mov r4, #0x1
	ldr r3, _02032B64 ; =UNK_02105D64 + 1
	add r5, r4, #0x0
_02032B28:
	ldrb r1, [r3, #0x0]
	ldrb r0, [r2, r5]
	cmp r1, r0
	beq _02032B34
	mov r4, #0x0
	b _02032B3C
_02032B34:
	add r5, r5, #0x1
	add r3, r3, #0x1
	cmp r5, #0x6
	blo _02032B28
_02032B3C:
	cmp r4, #0x0
	beq _02032B58
	ldrb r4, [r2, #0x0]
	bl FUN_02031190
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r4, r0
	bne _02032B58
	ldr r0, _02032B60 ; =UNK_021C5A00
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, #0x3d
	strb r1, [r0, #0x0]
_02032B58:
	pop {r3-r5, pc}
	nop
_02032B5C: .word UNK_02105D6C + 1
_02032B60: .word UNK_021C5A00
_02032B64: .word UNK_02105D64 + 1

	thumb_func_start FUN_02032B68
FUN_02032B68: ; 0x02032B68
	mov r0, #0x6
	bx lr

	thumb_func_start FUN_02032B6C
FUN_02032B6C: ; 0x02032B6C
	push {r3, lr}
	ldr r1, _02032B80 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _02032B7E
	add r1, #0x3c
	strb r0, [r1, #0x0]
	bl FUN_0202D1B0
_02032B7E:
	pop {r3, pc}
	.balign 4
_02032B80: .word UNK_021C5A00

	thumb_func_start FUN_02032B84
FUN_02032B84: ; 0x02032B84
	ldr r3, _02032B88 ; =FUN_0202EA54
	bx r3
	.balign 4
_02032B88: .word FUN_0202EA54

	thumb_func_start FUN_02032B8C
FUN_02032B8C: ; 0x02032B8C
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032BC6
	ldr r0, _02032BC8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032BC8 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	mov r2, #0x20
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032BC6
	bl FUN_0202FA10
	ldr r0, _02032BCC ; =FUN_02032B84
	mov r1, #0x0
	bl FUN_02031D20
_02032BC6:
	pop {r3, pc}
	.balign 4
_02032BC8: .word UNK_021C5A00
_02032BCC: .word FUN_02032B84

	thumb_func_start FUN_02032BD0
FUN_02032BD0: ; 0x02032BD0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02032C00
	mov r2, #0x7
	mov r0, #0x3
	mov r1, #0xf
	lsl r2, r2, #0xc
	bl FUN_02016828
	add r0, r4, #0x0
	mov r1, #0xe
	bl FUN_02031734
	ldr r0, _02032C04 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _02032C08 ; =FUN_02032B8C
	bl FUN_02031D20
_02032C00:
	pop {r4, pc}
	nop
_02032C04: .word UNK_021C5A00
_02032C08: .word FUN_02032B8C

	thumb_func_start FUN_02032C0C
FUN_02032C0C: ; 0x02032C0C
	push {r3, lr}
	ldr r0, _02032C20 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02032C1E
	ldr r0, _02032C24 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02032C1E:
	pop {r3, pc}
	.balign 4
_02032C20: .word UNK_021C5A00
_02032C24: .word FUN_02032440

	thumb_func_start FUN_02032C28
FUN_02032C28: ; 0x02032C28
	sub sp, #0x8
	ldr r1, _02032C64 ; =UNK_020EEC48
	add r0, sp, #0x0
	ldr r2, [r1, #0x0]
	ldr r1, [r1, #0x4]
	str r2, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r1, _02032C68 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0x24]
	cmp r1, #0x0
	bne _02032C46
	mov r0, #0x0
	add sp, #0x8
	bx lr
_02032C46:
	cmp r2, #0x0
	beq _02032C5E
_02032C4A:
	ldr r1, [r0, #0x0]
	cmp r3, r1
	bne _02032C56
	mov r0, #0x1
	add sp, #0x8
	bx lr
_02032C56:
	add r0, r0, #0x4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	bne _02032C4A
_02032C5E:
	mov r0, #0x0
	add sp, #0x8
	bx lr
	.balign 4
_02032C64: .word UNK_020EEC48
_02032C68: .word UNK_021C5A00

	thumb_func_start FUN_02032C6C
FUN_02032C6C: ; 0x02032C6C
	ldr r2, _02032CE4 ; =0x00400131
	cmp r0, r2
	bhi _02032C7C
	bhs _02032CBA
	ldr r2, _02032CE8 ; =0x00000333
	cmp r0, r2
	beq _02032C8E
	bx lr
_02032C7C:
	ldr r1, _02032CEC ; =0x00400286
	cmp r0, r1
	bhi _02032C86
	beq _02032CCE
	bx lr
_02032C86:
	add r1, #0x92
	cmp r0, r1
	beq _02032CA6
	bx lr
_02032C8E:
	cmp r1, #0xf
	bne _02032CE0
	ldr r0, _02032CF0 ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
	bx lr
_02032CA6:
	ldr r0, _02032CF0 ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x1
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
	bx lr
_02032CBA:
	ldr r0, _02032CF0 ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x2
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
	bx lr
_02032CCE:
	ldr r0, _02032CF0 ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	mov r0, #0x4
	add r2, #0x49
	orr r0, r1
	strb r0, [r2, #0x0]
_02032CE0:
	bx lr
	nop
_02032CE4: .word 0x00400131
_02032CE8: .word 0x00000333
_02032CEC: .word 0x00400286
_02032CF0: .word UNK_021C5A00

	thumb_func_start FUN_02032CF4
FUN_02032CF4: ; 0x02032CF4
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032D34
	ldr r0, _02032D38 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032D38 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	ldr r0, _02032D3C ; =FUN_02032C6C
	bl FUN_0202D308
	mov r0, #0x1
	add r1, r0, #0x0
	mov r2, #0x20
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032D34
	bl FUN_0202FA10
	ldr r0, _02032D40 ; =FUN_02032B84
	mov r1, #0x0
	bl FUN_02031D20
_02032D34:
	pop {r3, pc}
	nop
_02032D38: .word UNK_021C5A00
_02032D3C: .word FUN_02032C6C
_02032D40: .word FUN_02032B84

	thumb_func_start FUN_02032D44
FUN_02032D44: ; 0x02032D44
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02030F40
	cmp r0, #0x0
	bne _02032D74
	mov r2, #0x7
	mov r0, #0x3
	mov r1, #0xf
	lsl r2, r2, #0xc
	bl FUN_02016828
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_02031734
	ldr r0, _02032D78 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x40
	strb r1, [r0, #0x0]
	ldr r0, _02032D7C ; =FUN_02032CF4
	bl FUN_02031D20
_02032D74:
	pop {r4, pc}
	nop
_02032D78: .word UNK_021C5A00
_02032D7C: .word FUN_02032CF4

	thumb_func_start FUN_02032D80
FUN_02032D80: ; 0x02032D80
	push {r3, lr}
	ldr r0, _02032D94 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02032D92
	ldr r0, _02032D98 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_02032D92:
	pop {r3, pc}
	.balign 4
_02032D94: .word UNK_021C5A00
_02032D98: .word FUN_02032440

	thumb_func_start FUN_02032D9C
FUN_02032D9C: ; 0x02032D9C
	ldr r0, _02032DA8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x49
	ldrb r0, [r0, #0x0]
	bx lr
	nop
_02032DA8: .word UNK_021C5A00

	thumb_func_start FUN_02032DAC
FUN_02032DAC: ; 0x02032DAC
	push {r3, lr}
	bl FUN_02031468
	ldr r0, _02032DF4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02032DBE
	mov r0, #0x1
	pop {r3, pc}
_02032DBE:
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	add r0, #0xe8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bhi _02032DD4
	bl MOD04_021D83C0
	mov r0, #0x1
	pop {r3, pc}
_02032DD4:
	bl FUN_02033590
	cmp r0, #0x0
	beq _02032DE6
	ldr r0, _02032DF8 ; =FUN_0203318C
	mov r1, #0x0
	bl FUN_02031D20
	b _02032DEE
_02032DE6:
	ldr r0, _02032DFC ; =FUN_02032178
	mov r1, #0x0
	bl FUN_02031D20
_02032DEE:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02032DF4: .word UNK_021C5A00
_02032DF8: .word FUN_0203318C
_02032DFC: .word FUN_02032178

	thumb_func_start FUN_02032E00
FUN_02032E00: ; 0x02032E00
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032E3C
	ldr r0, _02032E40 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032E40 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _02032E3C
	bl FUN_0202FA10
	ldr r0, _02032E44 ; =FUN_02032218
	mov r1, #0x0
	bl FUN_02031D20
_02032E3C:
	pop {r3, pc}
	nop
_02032E40: .word UNK_021C5A00
_02032E44: .word FUN_02032218

	thumb_func_start FUN_02032E48
FUN_02032E48: ; 0x02032E48
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _02032E82
	ldr r0, _02032E84 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x2c]
	bl FUN_0202E29C
	ldr r0, _02032E84 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202DB14
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	bl FUN_0202F950
	cmp r0, #0x0
	beq _02032E82
	bl FUN_0202FA10
	ldr r0, _02032E88 ; =FUN_02032290
	mov r1, #0x0
	bl FUN_02031D20
_02032E82:
	pop {r3, pc}
	.balign 4
_02032E84: .word UNK_021C5A00
_02032E88: .word FUN_02032290

	thumb_func_start FUN_02032E8C
FUN_02032E8C: ; 0x02032E8C
	bx lr
	.balign 4

	thumb_func_start FUN_02032E90
FUN_02032E90: ; 0x02032E90
	push {r3, lr}
	bl MOD04_021D7F8C
	cmp r0, #0x0
	bge _02032EA2
	ldr r0, _02032EA4 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
_02032EA2:
	pop {r3, pc}
	.balign 4
_02032EA4: .word FUN_02032E8C

	thumb_func_start FUN_02032EA8
FUN_02032EA8: ; 0x02032EA8
	bx lr
	.balign 4

	thumb_func_start FUN_02032EAC
FUN_02032EAC: ; 0x02032EAC
	bx lr
	.balign 4

	thumb_func_start FUN_02032EB0
FUN_02032EB0: ; 0x02032EB0
	push {r3, lr}
	mov r0, #0x1
	bl FUN_020313A0
	bl MOD04_021D7F8C
	cmp r0, #0xa
	blt _02032ECA
	ldr r0, _02032F0C ; =FUN_02032EAC
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032ECA:
	cmp r0, #0x0
	bge _02032ED8
	ldr r0, _02032F10 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032ED8:
	cmp r0, #0x1
	bne _02032EE6
	ldr r0, _02032F14 ; =FUN_02032E90
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032EE6:
	cmp r0, #0x2
	bne _02032F08
	ldr r0, _02032F18 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02032F00
	ldr r0, _02032F10 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F00:
	ldr r0, _02032F1C ; =FUN_02032EA8
	mov r1, #0x0
	bl FUN_02031D20
_02032F08:
	pop {r3, pc}
	nop
_02032F0C: .word FUN_02032EAC
_02032F10: .word FUN_02032E8C
_02032F14: .word FUN_02032E90
_02032F18: .word UNK_021C5A00
_02032F1C: .word FUN_02032EA8

	thumb_func_start FUN_02032F20
FUN_02032F20: ; 0x02032F20
	add r1, r0, #0x2
	cmp r1, #0x1
	bls _02032F28
	neg r0, r0
_02032F28:
	ldr r1, _02032F30 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	str r0, [r1, #0x34]
	bx lr
	.balign 4
_02032F30: .word UNK_021C5A00

	thumb_func_start FUN_02032F34
FUN_02032F34: ; 0x02032F34
	push {r3, lr}
	mov r0, #0x0
	bl MOD04_021D7800
	cmp r0, #0xa
	blt _02032F4A
	ldr r0, _02032F88 ; =FUN_02032EAC
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F4A:
	cmp r0, #0x0
	bge _02032F5C
	bl FUN_02032F20
	ldr r0, _02032F8C ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F5C:
	cmp r0, #0x1
	bne _02032F6A
	ldr r0, _02032F90 ; =FUN_02032EB0
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F6A:
	cmp r0, #0x2
	bne _02032F78
	ldr r0, _02032F94 ; =FUN_02032EA8
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032F78:
	cmp r0, #0x3
	bne _02032F84
	ldr r0, _02032F88 ; =FUN_02032EAC
	mov r1, #0x0
	bl FUN_02031D20
_02032F84:
	pop {r3, pc}
	nop
_02032F88: .word FUN_02032EAC
_02032F8C: .word FUN_02032E8C
_02032F90: .word FUN_02032EB0
_02032F94: .word FUN_02032EA8

	thumb_func_start FUN_02032F98
FUN_02032F98: ; 0x02032F98
	push {r3, lr}
	mov r0, #0x1
	bl MOD04_021D7800
	cmp r0, #0x0
	bge _02032FB2
	bl FUN_02032F20
	ldr r0, _02032FD0 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02032FB2:
	ldr r0, _02032FD4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x42
	ldrb r0, [r0, #0x0]
	bl MOD04_021D8494
	cmp r0, #0x0
	beq _02032FCE
	bl FUN_0202FC60
	ldr r0, _02032FD8 ; =FUN_02032F34
	mov r1, #0x0
	bl FUN_02031D20
_02032FCE:
	pop {r3, pc}
	.balign 4
_02032FD0: .word FUN_02032E8C
_02032FD4: .word UNK_021C5A00
_02032FD8: .word FUN_02032F34

	thumb_func_start FUN_02032FDC
FUN_02032FDC: ; 0x02032FDC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02032FFC ; =FUN_020303BC
	ldr r1, _02033000 ; =FUN_02030238
	bl MOD04_021D77C4
	ldr r0, _02033004 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x42
	strb r4, [r0, #0x0]
	ldr r0, _02033008 ; =FUN_02032F98
	bl FUN_02031D20
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02032FFC: .word FUN_020303BC
_02033000: .word FUN_02030238
_02033004: .word UNK_021C5A00
_02033008: .word FUN_02032F98

	thumb_func_start FUN_0203300C
FUN_0203300C: ; 0x0203300C
	ldr r0, _02033048 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	ldr r0, _0203304C ; =FUN_02032F34
	cmp r1, r0
	bne _0203301C
	mov r0, #0x0
	bx lr
_0203301C:
	ldr r0, _02033050 ; =FUN_02032EB0
	cmp r1, r0
	bne _02033026
	mov r0, #0x1
	bx lr
_02033026:
	ldr r0, _02033054 ; =FUN_02032E90
	cmp r1, r0
	bne _02033030
	mov r0, #0x3
	bx lr
_02033030:
	ldr r0, _02033058 ; =FUN_02032EA8
	cmp r1, r0
	bne _0203303A
	mov r0, #0x4
	bx lr
_0203303A:
	ldr r0, _0203305C ; =FUN_02032EAC
	cmp r1, r0
	bne _02033044
	mov r0, #0x5
	bx lr
_02033044:
	mov r0, #0x2
	bx lr
	.balign 4
_02033048: .word UNK_021C5A00
_0203304C: .word FUN_02032F34
_02033050: .word FUN_02032EB0
_02033054: .word FUN_02032E90
_02033058: .word FUN_02032EA8
_0203305C: .word FUN_02032EAC

	thumb_func_start FUN_02033060
FUN_02033060: ; 0x02033060
	push {r3, lr}
	ldr r0, _02033090 ; =FUN_020303BC
	ldr r1, _02033094 ; =FUN_02030238
	bl MOD04_021D77C4
	mov r0, #0x0
	mvn r0, r0
	bl MOD04_021D8494
	cmp r0, #0x0
	beq _0203308C
	ldr r0, _02033098 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x4d
	strb r1, [r0, #0x0]
	bl FUN_0202FC60
	ldr r0, _0203309C ; =FUN_02032F34
	mov r1, #0x0
	bl FUN_02031D20
_0203308C:
	pop {r3, pc}
	nop
_02033090: .word FUN_020303BC
_02033094: .word FUN_02030238
_02033098: .word UNK_021C5A00
_0203309C: .word FUN_02032F34

	thumb_func_start FUN_020330A0
FUN_020330A0: ; 0x020330A0
	push {r3, lr}
	mov r0, #0x0
	bl FUN_020313A0
	ldr r0, _020330D8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x41
	ldrb r0, [r0, #0x0]
	bl MOD04_021D82BC
	cmp r0, #0x0
	beq _020330C6
	bl MOD04_021D836C
	ldr r0, _020330DC ; =FUN_02033060
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_020330C6:
	bl MOD04_021D7F8C
	cmp r0, #0x0
	bge _020330D6
	ldr r0, _020330E0 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
_020330D6:
	pop {r3, pc}
	.balign 4
_020330D8: .word UNK_021C5A00
_020330DC: .word FUN_02033060
_020330E0: .word FUN_02032E8C

	thumb_func_start FUN_020330E4
FUN_020330E4: ; 0x020330E4
	push {r3, lr}
	bl FUN_02031190
	cmp r0, #0x0
	bne _02033100
	ldr r0, _02033120 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033124 ; =FUN_020330A0
	bl FUN_02031D20
	b _02033112
_02033100:
	ldr r0, _02033120 ; =UNK_021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033124 ; =FUN_020330A0
	mov r1, #0x0
	bl FUN_02031D20
_02033112:
	ldr r0, _02033120 ; =UNK_021C5A00
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, #0x4d
	strb r1, [r0, #0x0]
	pop {r3, pc}
	nop
_02033120: .word UNK_021C5A00
_02033124: .word FUN_020330A0

	thumb_func_start FUN_02033128
FUN_02033128: ; 0x02033128
	ldr r0, _02033134 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4d
	ldrb r0, [r0, #0x0]
	bx lr
	nop
_02033134: .word UNK_021C5A00

	thumb_func_start FUN_02033138
FUN_02033138: ; 0x02033138
	ldr r0, _0203314C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	ldr r0, _02033150 ; =FUN_02033060
	cmp r1, r0
	bne _02033148
	mov r0, #0x1
	bx lr
_02033148:
	mov r0, #0x0
	bx lr
	.balign 4
_0203314C: .word UNK_021C5A00
_02033150: .word FUN_02033060

	thumb_func_start FUN_02033154
FUN_02033154: ; 0x02033154
	ldr r0, _02033174 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r1, [r0, #0x24]
	ldr r0, _02033178 ; =FUN_02032F34
	cmp r1, r0
	bne _02033164
	mov r0, #0x1
	bx lr
_02033164:
	ldr r0, _0203317C ; =FUN_02033060
	cmp r1, r0
	bne _0203316E
	mov r0, #0x1
	bx lr
_0203316E:
	mov r0, #0x0
	bx lr
	nop
_02033174: .word UNK_021C5A00
_02033178: .word FUN_02032F34
_0203317C: .word FUN_02033060

	thumb_func_start FUN_02033180
FUN_02033180: ; 0x02033180
	ldr r0, _02033188 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x34]
	bx lr
	.balign 4
_02033188: .word UNK_021C5A00

	thumb_func_start FUN_0203318C
FUN_0203318C: ; 0x0203318C
	push {r3, lr}
	mov r0, #0x0
	bl FUN_020313A0
	mov r0, #0x0
	bl MOD04_021D82BC
	cmp r0, #0x0
	beq _020331AA
	bl MOD04_021D836C
	ldr r0, _020331BC ; =FUN_02032440
	mov r1, #0x0
	bl FUN_02031D20
_020331AA:
	bl MOD04_021D7F8C
	cmp r0, #0x0
	bge _020331BA
	ldr r0, _020331C0 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
_020331BA:
	pop {r3, pc}
	.balign 4
_020331BC: .word FUN_02032440
_020331C0: .word FUN_02032E8C

	thumb_func_start FUN_020331C4
FUN_020331C4: ; 0x020331C4
	push {r3, lr}
	ldr r0, _020331E0 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020331DC
	mov r0, #0x1
	bl FUN_020166B8
	ldr r0, _020331E4 ; =FUN_02032440
	mov r1, #0x5
	bl FUN_02031D20
_020331DC:
	pop {r3, pc}
	nop
_020331E0: .word UNK_021C5A00
_020331E4: .word FUN_02032440

	thumb_func_start FUN_020331E8
FUN_020331E8: ; 0x020331E8
	push {r3, lr}
	ldr r0, _02033200 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020331FE
	mov r1, #0x0
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033204 ; =FUN_020330A0
	bl FUN_02031D20
_020331FE:
	pop {r3, pc}
	.balign 4
_02033200: .word UNK_021C5A00
_02033204: .word FUN_020330A0

	thumb_func_start FUN_02033208
FUN_02033208: ; 0x02033208
	push {r3, lr}
	ldr r0, _02033234 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033232
	bl FUN_02031190
	cmp r0, #0x0
	bne _02033220
	mov r1, #0x0
	ldr r0, _02033234 ; =UNK_021C5A00
	b _02033224
_02033220:
	ldr r0, _02033234 ; =UNK_021C5A00
	mov r1, #0x1
_02033224:
	ldr r0, [r0, #0x0]
	add r0, #0x41
	strb r1, [r0, #0x0]
	ldr r0, _02033238 ; =FUN_020330A0
	mov r1, #0x0
	bl FUN_02031D20
_02033232:
	pop {r3, pc}
	.balign 4
_02033234: .word UNK_021C5A00
_02033238: .word FUN_020330A0

	thumb_func_start FUN_0203323C
FUN_0203323C: ; 0x0203323C
	push {r3, lr}
	bl FUN_02031190
	add r1, sp, #0x0
	strb r0, [r1, #0x0]
	mov r0, #0x15
	add r1, sp, #0x0
	bl FUN_020311D0
	pop {r3, pc}

	thumb_func_start FUN_02033250
FUN_02033250: ; 0x02033250
	ldr r0, _0203327C ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _02033276
	ldr r1, [r2, #0x24]
	ldr r0, _02033280 ; =FUN_02032E8C
	cmp r1, r0
	bne _02033264
	mov r0, #0x1
	bx lr
_02033264:
	ldr r0, _02033284 ; =FUN_02032E90
	cmp r1, r0
	bne _02033276
	add r2, #0x44
	ldrb r0, [r2, #0x0]
	cmp r0, #0x0
	beq _02033276
	mov r0, #0x1
	bx lr
_02033276:
	mov r0, #0x0
	bx lr
	nop
_0203327C: .word UNK_021C5A00
_02033280: .word FUN_02032E8C
_02033284: .word FUN_02032E90

	thumb_func_start FUN_02033288
FUN_02033288: ; 0x02033288
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020332D8 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020332D6
	mov r1, #0xf
	add r2, r1, #0x0
	mov r0, #0x3
	add r2, #0xf1
	bl FUN_02016828
	mov r0, #0xf
	mov r1, #0x50
	bl FUN_02016998
	ldr r1, _020332D8 ; =UNK_021C5A00
	mov r2, #0x50
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _020332D8 ; =UNK_021C5A00
	mov r2, #0x18
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, #0x1
	add r2, #0x46
	strb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	str r4, [r0, #0x28]
	mov r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	bl FUN_020166A8
_020332D6:
	pop {r4, pc}
	.balign 4
_020332D8: .word UNK_021C5A00

	thumb_func_start FUN_020332DC
FUN_020332DC: ; 0x020332DC
	push {r3, lr}
	ldr r0, _0203330C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033308
	mov r0, #0x1
	bl FUN_020166B8
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _0203330C ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _0203330C ; =UNK_021C5A00
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, #0xf
	bl FUN_020168D0
_02033308:
	pop {r3, pc}
	nop
_0203330C: .word UNK_021C5A00

	thumb_func_start FUN_02033310
FUN_02033310: ; 0x02033310
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02033360 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203335E
	mov r1, #0xf
	add r2, r1, #0x0
	mov r0, #0x3
	add r2, #0xf1
	bl FUN_02016828
	mov r0, #0xf
	mov r1, #0x50
	bl FUN_02016998
	ldr r1, _02033360 ; =UNK_021C5A00
	mov r2, #0x50
	str r0, [r1, #0x0]
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _02033360 ; =UNK_021C5A00
	mov r2, #0x19
	ldr r1, [r0, #0x0]
	add r1, #0x3f
	strb r2, [r1, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, #0x1
	add r2, #0x46
	strb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	str r4, [r0, #0x28]
	mov r0, #0x0
	bl FUN_020334E8
	mov r0, #0x1
	bl FUN_020166A8
_0203335E:
	pop {r4, pc}
	.balign 4
_02033360: .word UNK_021C5A00

	thumb_func_start FUN_02033364
FUN_02033364: ; 0x02033364
	push {r3, lr}
	ldr r0, _02033394 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033390
	mov r0, #0x1
	bl FUN_020166B8
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_020334E8
	ldr r0, _02033394 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	bl FUN_02016A18
	ldr r0, _02033394 ; =UNK_021C5A00
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, #0xf
	bl FUN_020168D0
_02033390:
	pop {r3, pc}
	nop
_02033394: .word UNK_021C5A00

	thumb_func_start FUN_02033398
FUN_02033398: ; 0x02033398
	push {r3, lr}
	sub sp, #0x8
	ldr r0, _020333EC ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020333AA
	add sp, #0x8
	mov r0, #0x0
	pop {r3, pc}
_020333AA:
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	cmp r0, #0x18
	bne _020333C8
	add r0, sp, #0x4
	add r1, sp, #0x0
	bl MOD04_021DD718
	cmp r0, #0x0
	beq _020333E4
	bl MOD04_021DD6F0
	add sp, #0x8
	mov r0, #0x1
	pop {r3, pc}
_020333C8:
	cmp r0, #0x19
	bne _020333E4
	add r0, sp, #0x4
	add r1, sp, #0x0
	bl MOD04_021DD718
	cmp r0, #0x0
	beq _020333E4
	ldr r0, [sp, #0x0]
	cmp r0, #0x7
	bne _020333E4
	add sp, #0x8
	mov r0, #0x1
	pop {r3, pc}
_020333E4:
	mov r0, #0x0
	add sp, #0x8
	pop {r3, pc}
	nop
_020333EC: .word UNK_021C5A00

	thumb_func_start FUN_020333F0
FUN_020333F0: ; 0x020333F0
	push {r3, lr}
	bl MOD04_021D76AC
	cmp r0, #0x0
	bge _02033408
	bl FUN_02032F20
	ldr r0, _02033414 ; =FUN_02032E8C
	mov r1, #0x0
	bl FUN_02031D20
	pop {r3, pc}
_02033408:
	ble _02033412
	ldr r0, _02033418 ; =FUN_02033060
	mov r1, #0x0
	bl FUN_02031D20
_02033412:
	pop {r3, pc}
	.balign 4
_02033414: .word FUN_02032E8C
_02033418: .word FUN_02033060

	thumb_func_start FUN_0203341C
FUN_0203341C: ; 0x0203341C
	push {r3, lr}
	bl FUN_0202E4C8
	cmp r0, #0x0
	beq _0203345E
	mov r1, #0x31
	mov r0, #0x3
	lsl r2, r1, #0xc
	bl FUN_02016828
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r2, r0, #0x9
	add r3, r0, #0x0
	bl FUN_0202F918
	cmp r0, #0x0
	beq _0203345E
	ldr r0, _02033460 ; =UNK_021C5A00
	mov r1, #0x31
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl MOD05_021D74E0
	ldr r0, _02033464 ; =FUN_020335D0
	bl MOD04_021D83A8
	bl FUN_0202FA10
	ldr r0, _02033468 ; =FUN_020333F0
	mov r1, #0x0
	bl FUN_02031D20
_0203345E:
	pop {r3, pc}
	.balign 4
_02033460: .word UNK_021C5A00
_02033464: .word FUN_020335D0
_02033468: .word FUN_020333F0

	thumb_func_start FUN_0203346C
FUN_0203346C: ; 0x0203346C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_020238F4
	bl FUN_02030F40
	cmp r0, #0x0
	beq _02033482
	mov r0, #0x0
	pop {r3-r5, pc}
_02033482:
	mov r0, #0x1
	bl FUN_020166A8
	ldr r2, _020334D0 ; =0x00007080
	mov r0, #0x3
	mov r1, #0xf
	bl FUN_02016828
	add r0, r5, #0x0
	mov r1, #0x17
	bl FUN_02031734
	mov r0, #0xf
	add r1, r4, #0x0
	bl FUN_02016998
	ldr r1, _020334D4 ; =UNK_021C5A00
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r2, r4, #0x0
	bl MI_CpuFill8
	ldr r0, _020334D4 ; =UNK_021C5A00
	mov r1, #0x0
	ldr r2, [r0, #0x0]
	add r2, #0x40
	strb r1, [r2, #0x0]
	ldr r0, [r0, #0x0]
	str r5, [r0, #0x28]
	ldr r0, _020334D8 ; =FUN_0203341C
	bl FUN_02031D20
	ldr r0, _020334D4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	pop {r3-r5, pc}
	.balign 4
_020334D0: .word 0x00007080
_020334D4: .word UNK_021C5A00
_020334D8: .word FUN_0203341C

	thumb_func_start FUN_020334DC
FUN_020334DC: ; 0x020334DC
	ldr r0, _020334E4 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020334E4: .word UNK_021C5A00

	thumb_func_start FUN_020334E8
FUN_020334E8: ; 0x020334E8
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _0203350C ; =UNK_021C5A00
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020334FE
	add r2, #0x44
	strb r4, [r2, #0x0]
	ldr r0, [r0, #0x0]
	add r0, #0x45
	strb r1, [r0, #0x0]
_020334FE:
	add r0, r4, #0x0
	bl FUN_0202EE84
	add r0, r4, #0x0
	bl FUN_0202EEB0
	pop {r4, pc}
	.balign 4
_0203350C: .word UNK_021C5A00

	thumb_func_start FUN_02033510
FUN_02033510: ; 0x02033510
	ldr r0, _02033530 ; =UNK_021C5A00
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0203352C
	add r0, r1, #0x0
	add r0, #0x4e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033526
	mov r0, #0x1
	bx lr
_02033526:
	add r1, #0x45
	ldrb r0, [r1, #0x0]
	bx lr
_0203352C:
	mov r0, #0x0
	bx lr
	.balign 4
_02033530: .word UNK_021C5A00

	thumb_func_start FUN_02033534
FUN_02033534: ; 0x02033534
	ldr r0, _02033548 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02033542
	add r0, #0x3f
	ldrb r0, [r0, #0x0]
	bx lr
_02033542:
	mov r0, #0x1
	bx lr
	nop
_02033548: .word UNK_021C5A00

	thumb_func_start FUN_0203354C
FUN_0203354C: ; 0x0203354C
	ldr r0, _02033560 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203355A
	add r0, #0x40
	ldrb r0, [r0, #0x0]
	bx lr
_0203355A:
	mov r0, #0x0
	bx lr
	nop
_02033560: .word UNK_021C5A00

	thumb_func_start FUN_02033564
FUN_02033564: ; 0x02033564
	ldr r1, _02033570 ; =UNK_021C5A00
	ldr r3, _02033574 ; =MI_CpuCopy8
	ldr r1, [r1, #0x0]
	mov r2, #0x6
	add r1, r1, #0x4
	bx r3
	.balign 4
_02033570: .word UNK_021C5A00
_02033574: .word MI_CpuCopy8

	thumb_func_start FUN_02033578
FUN_02033578: ; 0x02033578
	add r1, r0, #0x0
	ldr r0, _02033588 ; =UNK_021C5A00
	ldr r3, _0203358C ; =MI_CpuCopy8
	ldr r0, [r0, #0x0]
	mov r2, #0x6
	add r0, r0, #0x4
	bx r3
	nop
_02033588: .word UNK_021C5A00
_0203358C: .word MI_CpuCopy8

	thumb_func_start FUN_02033590
FUN_02033590: ; 0x02033590
	push {r3, lr}
	bl FUN_02033534
	cmp r0, #0x13
	blt _0203359E
	mov r0, #0x1
	pop {r3, pc}
_0203359E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020335A4
FUN_020335A4: ; 0x020335A4
	ldr r1, _020335B4 ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020335B0
	add r1, #0x47
	strb r0, [r1, #0x0]
_020335B0:
	bx lr
	nop
_020335B4: .word UNK_021C5A00

	thumb_func_start FUN_020335B8
FUN_020335B8: ; 0x020335B8
	ldr r0, _020335CC ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020335C6
	add r0, #0x47
	ldrb r0, [r0, #0x0]
	bx lr
_020335C6:
	mov r0, #0x0
	bx lr
	nop
_020335CC: .word UNK_021C5A00

	thumb_func_start FUN_020335D0
FUN_020335D0: ; 0x020335D0
	push {r3, lr}
	add r2, r0, #0x0
	mov r0, #0x0
	mov r1, #0x1
	bl FUN_02033F70
_020335DC:
	b _020335DC
	.balign 4

	thumb_func_start FUN_020335E0
FUN_020335E0: ; 0x020335E0
	push {r3, lr}
	mov r0, #0x0
	mov r1, #0x4
	add r2, r0, #0x0
	bl FUN_02033F70
_020335EC:
	b _020335EC
	.balign 4

	thumb_func_start FUN_020335F0
FUN_020335F0: ; 0x020335F0
	bx lr
	.balign 4

	thumb_func_start FUN_020335F4
FUN_020335F4: ; 0x020335F4
	push {r3, lr}
	bl FUN_02033510
	cmp r0, #0x0
	beq _0203366C
	bl FUN_020311F0
	cmp r0, #0x0
	bne _02033622
	bl FUN_02033250
	cmp r0, #0x0
	bne _02033622
	bl FUN_02033398
	cmp r0, #0x0
	bne _02033622
	ldr r0, _02033670 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	add r0, #0x4e
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203366C
_02033622:
	bl FUN_020335B8
	cmp r0, #0x0
	bne _0203366C
	bl FUN_0200541C
	ldr r0, _02033670 ; =UNK_021C5A00
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x28]
	bl FUN_0202287C
	ldr r1, _02033674 ; =gUnk021C4918
	mov r0, #0x1
	strb r0, [r1, #0x4]
	ldr r1, _02033670 ; =UNK_021C5A00
	ldr r2, [r1, #0x0]
	add r1, r2, #0x0
	add r1, #0x4e
	ldrb r1, [r1, #0x0]
	cmp r1, #0x3
	bne _02033654
	mov r0, #0x3
	bl FUN_020335A4
	pop {r3, pc}
_02033654:
	add r2, #0x3f
	ldrb r1, [r2, #0x0]
	cmp r1, #0x19
	beq _02033660
	cmp r1, #0xf
	bne _02033668
_02033660:
	mov r0, #0x2
	bl FUN_020335A4
	pop {r3, pc}
_02033668:
	bl FUN_020335A4
_0203366C:
	pop {r3, pc}
	nop
_02033670: .word UNK_021C5A00
_02033674: .word gUnk021C4918

	thumb_func_start FUN_02033678
FUN_02033678: ; 0x02033678
	push {r3, lr}
	bl FUN_0202EDD8
	cmp r0, #0x0
	bne _0203368A
	bl FUN_02031810
	cmp r0, #0x0
	bne _0203368E
_0203368A:
	mov r0, #0x1
	pop {r3, pc}
_0203368E:
	bl FUN_0202E344
	cmp r0, #0x0
	bne _0203369A
	mov r0, #0x1
	pop {r3, pc}
_0203369A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020336A0
FUN_020336A0: ; 0x020336A0
	push {r3, lr}
	ldr r1, _020336BC ; =UNK_021C5A00
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020336B6
	add r1, #0x4e
	strb r0, [r1, #0x0]
	bl FUN_02031468
	mov r0, #0x1
	pop {r3, pc}
_020336B6:
	mov r0, #0x0
	pop {r3, pc}
	nop
_020336BC: .word UNK_021C5A00
