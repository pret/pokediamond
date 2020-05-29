	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD77_021D74E0
MOD77_021D74E0: ; 0x021D74E0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021D75D4 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _021D75D8 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r0, #3
	mov r1, #0x32
	lsl r2, r2, #7
	bl FUN_0201681C
	ldr r1, _021D75DC ; =0x0000C32C
	add r0, r4, #0
	mov r2, #0x32
	bl FUN_02006268
	ldr r2, _021D75DC ; =0x0000C32C
	mov r1, #0
	add r5, r0, #0
	bl memset
	mov r0, #0x32
	str r0, [r5]
	ldr r0, _021D75E0 ; =0x020ECAC4
	ldrb r0, [r0]
	cmp r0, #1
	bne _021D753E
	mov r1, #1
	b _021D7540
_021D753E:
	mov r1, #0
_021D7540:
	ldr r0, _021D75E4 ; =0x0000C2F0
	str r1, [r5, r0]
	add r0, r4, #0
	bl FUN_0200628C
	add r4, r0, #0
	bl FUN_02029AFC
	str r0, [r5, #4]
	bl FUN_02029B38
	ldr r1, _021D75E8 ; =0x0000C314
	str r0, [r5, r1]
	ldr r0, [r5, #4]
	bl FUN_02029B3C
	ldr r1, _021D75EC ; =0x0000C318
	str r0, [r5, r1]
	ldr r0, [r5, #4]
	bl FUN_02029C00
	ldr r1, _021D75F0 ; =0x0000C324
	str r0, [r5, r1]
	add r0, r4, #0
	bl LoadPlayerDataAddress
	str r0, [r5, #8]
	bl MOD77_021D7C24
	bl MOD77_021D7C44
	ldr r0, [r5]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201B2EC
	ldr r0, [r5]
	bl FUN_02016B94
	ldr r1, _021D75F4 ; =0x0000C010
	str r0, [r5, r1]
	bl FUN_0201E788
	bl FUN_0201BD5C
	ldr r2, [r5]
	mov r0, #8
	mov r1, #0x40
	bl FUN_0200AA90
	ldr r1, _021D75F8 ; =0x0000C070
	str r0, [r5, r1]
	ldr r0, [r5]
	bl FUN_0201EB64
	ldr r1, _021D75FC ; =0x0000C2CC
	str r0, [r5, r1]
	mov r0, #0
	add r1, #0x1c
	str r0, [r5, r1]
	ldr r0, _021D7600 ; =0x021C4918
	mov r1, #1
	strb r1, [r0, #5]
	bl FUN_0201E7A0
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	add r0, r5, #0
	bl MOD77_021D7C64
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D75D4: .word 0xFFFFE0FF
_021D75D8: .word 0x04001000
_021D75DC: .word 0x0000C32C
_021D75E0: .word 0x020ECAC4
_021D75E4: .word 0x0000C2F0
_021D75E8: .word 0x0000C314
_021D75EC: .word 0x0000C318
_021D75F0: .word 0x0000C324
_021D75F4: .word 0x0000C010
_021D75F8: .word 0x0000C070
_021D75FC: .word 0x0000C2CC
_021D7600: .word 0x021C4918
	thumb_func_end MOD77_021D74E0

	thumb_func_start MOD77_021D7604
MOD77_021D7604: ; 0x021D7604
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	bl FUN_02006278
	ldr r1, [r5]
	add r4, r0, #0
	mov r7, #0
	cmp r1, #0x12
	bls _021D761A
	b _021D7B66
_021D761A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021D7626: ; jump table
	.short _021D764C - _021D7626 - 2 ; case 0
	.short _021D76A8 - _021D7626 - 2 ; case 1
	.short _021D76B6 - _021D7626 - 2 ; case 2
	.short _021D76D6 - _021D7626 - 2 ; case 3
	.short _021D76FA - _021D7626 - 2 ; case 4
	.short _021D7744 - _021D7626 - 2 ; case 5
	.short _021D776C - _021D7626 - 2 ; case 6
	.short _021D77A2 - _021D7626 - 2 ; case 7
	.short _021D77DE - _021D7626 - 2 ; case 8
	.short _021D7838 - _021D7626 - 2 ; case 9
	.short _021D7886 - _021D7626 - 2 ; case 10
	.short _021D78DC - _021D7626 - 2 ; case 11
	.short _021D78EE - _021D7626 - 2 ; case 12
	.short _021D7916 - _021D7626 - 2 ; case 13
	.short _021D7964 - _021D7626 - 2 ; case 14
	.short _021D7A32 - _021D7626 - 2 ; case 15
	.short _021D7B0E - _021D7626 - 2 ; case 16
	.short _021D7B1C - _021D7626 - 2 ; case 17
	.short _021D7B3E - _021D7626 - 2 ; case 18
_021D764C:
	ldr r2, _021D7968 ; =0x0000013E
	ldr r3, [r4]
	mov r0, #1
	mov r1, #0x1a
	bl FUN_0200A86C
	ldr r1, _021D796C ; =0x0000C060
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD77_021D8814
	add r0, r4, #0
	bl MOD77_021D7FAC
	add r0, r7, #0
	ldr r1, _021D7970 ; =0x0000C2EC
	add r3, r0, #0
	str r0, [r4, r1]
	mov r1, #6
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	ldr r2, [r4]
	str r2, [sp, #8]
	add r2, r1, #0
	bl FUN_0200E1D0
	mov r0, #4
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #8
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #1
	bl FUN_0201E74C
	mov r0, #1
	str r0, [r5]
	b _021D7B66
_021D76A8:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7780
	mov r0, #2
	str r0, [r5]
	b _021D7B66
_021D76B6:
	add r1, r7, #0
	mov r2, #1
	bl MOD77_021D8294
	cmp r0, #1
	bne _021D7780
	ldr r0, _021D7974 ; =0x0000C314
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D76D0
	mov r0, #3
	str r0, [r5]
	b _021D7B66
_021D76D0:
	mov r0, #0xe
	str r0, [r5]
	b _021D7B66
_021D76D6:
	mov r1, #1
	add r2, r1, #0
	bl MOD77_021D8294
	cmp r0, #1
	bne _021D7780
	ldr r0, _021D7978 ; =0x021D8F64
	ldr r1, _021D797C ; =0x0000C024
	str r0, [sp]
	ldr r2, _021D7980 ; =0x021D8F18
	ldr r3, _021D7984 ; =0x021D8FB4
	add r0, r4, #0
	add r1, r4, r1
	bl MOD77_021D8370
	mov r0, #4
	str r0, [r5]
	b _021D7B66
_021D76FA:
	ldr r0, _021D7988 ; =0x0000C054
	ldr r0, [r4, r0]
	bl FUN_02001204
	add r6, r0, #0
	sub r0, r7, #1
	cmp r6, r0
	beq _021D7780
	add r0, r4, #0
	bl MOD77_021D84D8
	ldr r0, _021D798C ; =0x000005DC
	bl FUN_020054C8
	add r0, r6, #2
	cmp r0, #4
	bhi _021D7732
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021D7728: ; jump table
	.short _021D773E - _021D7728 - 2 ; case 0
	.short _021D7732 - _021D7728 - 2 ; case 1
	.short _021D7732 - _021D7728 - 2 ; case 2
	.short _021D7738 - _021D7728 - 2 ; case 3
	.short _021D773E - _021D7728 - 2 ; case 4
_021D7732:
	mov r0, #0xe
	str r0, [r5]
	b _021D7B66
_021D7738:
	mov r0, #5
	str r0, [r5]
	b _021D7B66
_021D773E:
	mov r0, #0x11
	str r0, [r5]
	b _021D7B66
_021D7744:
	mov r1, #2
	mov r2, #1
	bl MOD77_021D8294
	cmp r0, #1
	bne _021D7780
	ldr r0, [r4]
	ldr r1, _021D7990 ; =0x021D8F38
	str r0, [sp]
	ldr r0, _021D7994 ; =0x0000C010
	ldr r2, _021D7998 ; =0x000001D9
	ldr r0, [r4, r0]
	mov r3, #7
	bl FUN_02002198
	ldr r1, _021D799C ; =0x0000C05C
	str r0, [r4, r1]
	mov r0, #6
	str r0, [r5]
	b _021D7B66
_021D776C:
	ldr r0, _021D799C ; =0x0000C05C
	ldr r1, [r4]
	ldr r0, [r4, r0]
	bl FUN_020021AC
	cmp r0, #0
	beq _021D7782
	sub r1, r7, #2
	cmp r0, r1
	beq _021D779C
_021D7780:
	b _021D7B66
_021D7782:
	ldr r0, _021D79A0 ; =0x0000C2F0
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _021D7796
	mov r1, #0x67
	add r0, #0x2c
	str r1, [r4, r0]
	mov r0, #9
	str r0, [r5]
	b _021D7B66
_021D7796:
	mov r0, #7
	str r0, [r5]
	b _021D7B66
_021D779C:
	mov r0, #3
	str r0, [r5]
	b _021D7B66
_021D77A2:
	mov r1, #3
	mov r2, #1
	bl MOD77_021D8294
	cmp r0, #1
	bne _021D77EE
	ldr r1, _021D79A4 ; =0x0000C31C
	add r0, r7, #0
	str r0, [r4, r1]
	bl FUN_02088DA0
	add r6, r0, #0
	add r0, r7, #0
	bl FUN_02088DBC
	mov r1, #0x99
	lsl r1, r1, #2
	str r1, [sp]
	ldr r1, _021D797C ; =0x0000C024
	str r6, [sp, #4]
	str r0, [sp, #8]
	ldr r2, _021D79A8 ; =0x021D8F20
	ldr r3, _021D79AC ; =0x021D8FD4
	add r0, r4, #0
	add r1, r4, r1
	bl MOD77_021D8418
	mov r0, #8
	str r0, [r5]
	b _021D7B66
_021D77DE:
	ldr r0, _021D7988 ; =0x0000C054
	ldr r0, [r4, r0]
	bl FUN_02001204
	add r6, r0, #0
	sub r0, r7, #1
	cmp r6, r0
	bne _021D77F0
_021D77EE:
	b _021D7B66
_021D77F0:
	add r0, r4, #0
	bl MOD77_021D84D8
	ldr r0, _021D798C ; =0x000005DC
	bl FUN_020054C8
	sub r0, r7, #2
	cmp r6, r0
	beq _021D780A
	add r0, r7, #0
	bl FUN_02088DA0
	ldrb r6, [r0, r6]
_021D780A:
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _021D7832
	ldr r0, _021D79A4 ; =0x0000C31C
	str r6, [r4, r0]
	ldr r0, [r4, r0]
	bl MOD77_021D8F04
	cmp r0, #1
	bne _021D7826
	mov r0, #9
	str r0, [r5]
	b _021D7B66
_021D7826:
	ldr r0, _021D79B0 ; =0x0000C320
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #0xb
	str r0, [r5]
	b _021D7B66
_021D7832:
	mov r0, #3
	str r0, [r5]
	b _021D7B66
_021D7838:
	mov r1, #4
	mov r2, #1
	bl MOD77_021D8294
	cmp r0, #1
	bne _021D792A
	ldr r0, _021D79B0 ; =0x0000C320
	add r1, r7, #0
	str r1, [r4, r0]
	sub r0, r0, #4
	ldr r0, [r4, r0]
	bl FUN_02088D20
	add r6, r0, #0
	bl FUN_02088D4C
	str r0, [sp, #0xc]
	add r0, r6, #0
	bl FUN_02088DA0
	str r0, [sp, #0x10]
	add r0, r6, #0
	bl FUN_02088DBC
	ldr r1, [sp, #0xc]
	ldr r2, _021D79A8 ; =0x021D8F20
	str r1, [sp]
	ldr r1, [sp, #0x10]
	ldr r3, _021D79AC ; =0x021D8FD4
	str r1, [sp, #4]
	ldr r1, _021D797C ; =0x0000C024
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, r4, r1
	bl MOD77_021D8418
	mov r0, #0xa
	str r0, [r5]
	b _021D7B66
_021D7886:
	ldr r0, _021D7988 ; =0x0000C054
	ldr r0, [r4, r0]
	bl FUN_02001204
	add r6, r0, #0
	sub r0, r7, #1
	cmp r6, r0
	beq _021D792A
	add r0, r4, #0
	bl MOD77_021D84D8
	ldr r0, _021D798C ; =0x000005DC
	bl FUN_020054C8
	sub r0, r7, #2
	cmp r6, r0
	beq _021D78B6
	ldr r0, _021D79A4 ; =0x0000C31C
	ldr r0, [r4, r0]
	bl FUN_02088D20
	bl FUN_02088DA0
	ldrb r6, [r0, r6]
_021D78B6:
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _021D78C8
	ldr r0, _021D79B0 ; =0x0000C320
	str r6, [r4, r0]
	mov r0, #0xb
	str r0, [r5]
	b _021D7B66
_021D78C8:
	ldr r0, _021D79A0 ; =0x0000C2F0
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D78D6
	mov r0, #3
	str r0, [r5]
	b _021D7B66
_021D78D6:
	mov r0, #7
	str r0, [r5]
	b _021D7B66
_021D78DC:
	ldr r2, _021D79A4 ; =0x0000C31C
	ldr r1, [r4, r2]
	add r2, r2, #4
	ldr r2, [r4, r2]
	bl MOD77_021D85E0
	mov r0, #0xc
	str r0, [r5]
	b _021D7B66
_021D78EE:
	mov r1, #5
	mov r2, #1
	bl MOD77_021D8294
	cmp r0, #1
	bne _021D792A
	ldr r0, [r4]
	ldr r1, _021D7990 ; =0x021D8F38
	str r0, [sp]
	ldr r0, _021D7994 ; =0x0000C010
	ldr r2, _021D7998 ; =0x000001D9
	ldr r0, [r4, r0]
	mov r3, #7
	bl FUN_02002198
	ldr r1, _021D799C ; =0x0000C05C
	str r0, [r4, r1]
	mov r0, #0xd
	str r0, [r5]
	b _021D7B66
_021D7916:
	ldr r0, _021D799C ; =0x0000C05C
	ldr r1, [r4]
	ldr r0, [r4, r0]
	bl FUN_020021AC
	cmp r0, #0
	beq _021D792C
	sub r1, r7, #2
	cmp r0, r1
	beq _021D7958
_021D792A:
	b _021D7B66
_021D792C:
	add r0, r4, #0
	bl MOD77_021D8698
	ldr r2, _021D79A4 ; =0x0000C31C
	ldr r0, [r4, #4]
	ldr r1, [r4, r2]
	add r2, r2, #4
	ldr r2, [r4, r2]
	bl FUN_02029B08
	ldr r0, _021D79A4 ; =0x0000C31C
	add r1, r0, #0
	ldr r2, [r4, r0]
	sub r1, #8
	str r2, [r4, r1]
	add r1, r0, #4
	ldr r1, [r4, r1]
	sub r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0xe
	str r0, [r5]
	b _021D7B66
_021D7958:
	add r0, r4, #0
	bl MOD77_021D8698
	mov r0, #3
	str r0, [r5]
	b _021D7B66
_021D7964:
	ldr r1, _021D79A0 ; =0x0000C2F0
	b _021D79B4
	.align 2, 0
_021D7968: .word 0x0000013E
_021D796C: .word 0x0000C060
_021D7970: .word 0x0000C2EC
_021D7974: .word 0x0000C314
_021D7978: .word 0x021D8F64
_021D797C: .word 0x0000C024
_021D7980: .word 0x021D8F18
_021D7984: .word 0x021D8FB4
_021D7988: .word 0x0000C054
_021D798C: .word 0x000005DC
_021D7990: .word 0x021D8F38
_021D7994: .word 0x0000C010
_021D7998: .word 0x000001D9
_021D799C: .word 0x0000C05C
_021D79A0: .word 0x0000C2F0
_021D79A4: .word 0x0000C31C
_021D79A8: .word 0x021D8F20
_021D79AC: .word 0x021D8FD4
_021D79B0: .word 0x0000C320
_021D79B4:
	ldr r0, [r4, r1]
	cmp r0, #1
	bne _021D79CA
	add r0, r1, #0
	add r0, #0x34
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D79CA
	add r0, r1, #4
	strh r7, [r4, r0]
	b _021D79D0
_021D79CA:
	ldr r0, _021D7B74 ; =0x0000C2F4
	mov r1, #1
	strh r1, [r4, r0]
_021D79D0:
	add r0, r4, #0
	bl MOD77_021D8914
	add r0, r4, #0
	bl MOD77_021D7DCC
	add r0, r4, #0
	bl MOD77_021D8970
	add r0, r4, #0
	bl MOD77_021D89F4
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	ldr r0, _021D7B78 ; =0x0000C014
	mov r2, #0
	add r0, r4, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D7B7C ; =0x0000C034
	ldr r2, _021D7B80 ; =0x000001D9
	add r0, r4, r0
	mov r1, #0
	mov r3, #7
	bl FUN_0200CCA4
	ldr r0, _021D7B84 ; =0x0000C314
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _021D7A1A
	add r0, r4, #0
	bl MOD77_021D8510
_021D7A1A:
	add r0, r4, #0
	bl MOD77_021D86B4
	ldr r0, _021D7B88 ; =0x0000C328
	mov r1, #0
	str r1, [r4, r0]
	mov r1, #1
	sub r0, #0x40
	str r1, [r4, r0]
	mov r0, #0xf
	str r0, [r5]
	b _021D7B66
_021D7A32:
	ldr r1, _021D7B8C ; =0x0000C2D8
	ldrh r6, [r4, r1]
	bl MOD77_021D7E24
	ldr r0, _021D7B90 ; =0x021C48B8
	mov r3, #2
	ldr r1, [r0, #0x48]
	add r0, r1, #0
	tst r0, r3
	bne _021D7A4E
	ldr r0, _021D7B94 ; =0x0000C2F8
	ldr r2, [r4, r0]
	tst r2, r3
	beq _021D7A94
_021D7A4E:
	ldr r0, _021D7B7C ; =0x0000C034
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _021D7B98 ; =0x000005DD
	bl FUN_020054C8
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	ldr r0, _021D7B78 ; =0x0000C014
	mov r2, #0
	add r0, r4, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D7B84 ; =0x0000C314
	ldr r1, [r4, r0]
	cmp r1, #0
	bne _021D7A88
	mov r1, #2
	sub r0, #0x2c
	str r1, [r4, r0]
	mov r0, #3
	str r0, [r5]
	b _021D7B66
_021D7A88:
	add r0, r4, #0
	bl MOD77_021D8698
	mov r0, #0x11
	str r0, [r5]
	b _021D7B66
_021D7A94:
	lsl r2, r3, #9
	tst r2, r1
	beq _021D7AC0
	add r2, r0, #0
	add r2, #0x30
	ldr r2, [r4, r2]
	cmp r2, #0
	bne _021D7AC0
	mov r1, #1
	add r0, #0x30
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD77_021D86B4
	ldr r0, _021D7B88 ; =0x0000C328
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021D7B66
	ldr r0, _021D7B98 ; =0x000005DD
	bl FUN_020054C8
	b _021D7B66
_021D7AC0:
	ldr r0, _021D7B9C ; =0x00000403
	tst r0, r1
	beq _021D7ADA
	ldr r0, _021D7B88 ; =0x0000C328
	ldr r2, [r4, r0]
	cmp r2, #1
	bne _021D7ADA
	mov r1, #0
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD77_021D86B4
	b _021D7B66
_021D7ADA:
	ldr r2, _021D7B90 ; =0x021C48B8
	add r0, r4, #0
	ldr r2, [r2, #0x44]
	bl MOD77_021D8B20
	cmp r0, #1
	bne _021D7AFA
	ldr r0, _021D7B88 ; =0x0000C328
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _021D7AFA
	mov r1, #0
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD77_021D86B4
_021D7AFA:
	ldr r0, _021D7B8C ; =0x0000C2D8
	ldrh r0, [r4, r0]
	cmp r6, r0
	beq _021D7B66
	mov r0, #0x10
	str r0, [r5]
	ldr r0, _021D7B98 ; =0x000005DD
	bl FUN_020054C8
	b _021D7B66
_021D7B0E:
	bl MOD77_021D8CF8
	cmp r0, #1
	bne _021D7B66
	mov r0, #0xf
	str r0, [r5]
	b _021D7B66
_021D7B1C:
	ldr r0, _021D7BA0 ; =0x0000C2EC
	add r1, r7, #0
	str r7, [r4, r0]
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4]
	add r2, r7, #0
	str r0, [sp, #8]
	add r0, r7, #0
	add r3, r7, #0
	bl FUN_0200E1D0
	mov r0, #0x12
	str r0, [r5]
	b _021D7B66
_021D7B3E:
	bl FUN_0200E308
	cmp r0, #1
	bne _021D7B66
	ldr r0, _021D7BA4 ; =0x0000C2E8
	mov r1, #1
	str r1, [r4, r0]
	add r0, r4, #0
	bl MOD77_021D8248
	add r0, r4, #0
	bl MOD77_021D88D0
	ldr r0, _021D7BA8 ; =0x0000C060
	ldr r0, [r4, r0]
	bl FUN_0200A8B8
	add r0, r7, #0
	str r0, [r5]
	mov r7, #1
_021D7B66:
	add r0, r4, #0
	bl MOD77_021D8D84
	add r0, r7, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021D7B74: .word 0x0000C2F4
_021D7B78: .word 0x0000C014
_021D7B7C: .word 0x0000C034
_021D7B80: .word 0x000001D9
_021D7B84: .word 0x0000C314
_021D7B88: .word 0x0000C328
_021D7B8C: .word 0x0000C2D8
_021D7B90: .word 0x021C48B8
_021D7B94: .word 0x0000C2F8
_021D7B98: .word 0x000005DD
_021D7B9C: .word 0x00000403
_021D7BA0: .word 0x0000C2EC
_021D7BA4: .word 0x0000C2E8
_021D7BA8: .word 0x0000C060
	thumb_func_end MOD77_021D7604

	thumb_func_start MOD77_021D7BAC
MOD77_021D7BAC: ; 0x021D7BAC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl FUN_02006278
	add r4, r0, #0
	mov r0, #4
	mov r1, #0
	ldr r5, [r4]
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #8
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #8
	mov r1, #0
	bl FUN_0201E74C
	ldr r0, _021D7C14 ; =0x0000C2CC
	ldr r0, [r4, r0]
	bl FUN_0201EB70
	ldr r0, _021D7C18 ; =0x0000C070
	ldr r0, [r4, r0]
	bl FUN_0200AB18
	bl FUN_0201B398
	ldr r0, _021D7C1C ; =0x0000C010
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0
	add r1, r0, #0
	bl FUN_02015F10
	add r0, r6, #0
	bl FUN_0200627C
	add r0, r5, #0
	bl FUN_020168D0
	ldr r0, _021D7C20 ; =0x021C4918
	mov r1, #0
	strb r1, [r0, #5]
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_021D7C14: .word 0x0000C2CC
_021D7C18: .word 0x0000C070
_021D7C1C: .word 0x0000C010
_021D7C20: .word 0x021C4918
	thumb_func_end MOD77_021D7BAC

	thumb_func_start MOD77_021D7C24
MOD77_021D7C24: ; 0x021D7C24
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _021D7C40 ; =0x021D9084
	add r3, sp, #0
	mov r2, #5
_021D7C2E:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7C2E
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_021D7C40: .word 0x021D9084
	thumb_func_end MOD77_021D7C24

	thumb_func_start MOD77_021D7C44
MOD77_021D7C44: ; 0x021D7C44
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _021D7C60 ; =0x021D8F54
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_021D7C60: .word 0x021D8F54
	thumb_func_end MOD77_021D7C44

	thumb_func_start MOD77_021D7C64
MOD77_021D7C64: ; 0x021D7C64
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	mov r2, #0
	str r0, [sp, #8]
	str r2, [r0, #0xc]
	str r2, [sp]
	add r0, sp, #0x20
	str r0, [sp, #4]
	ldr r3, [sp, #8]
	mov r0, #0x66
	ldr r3, [r3]
	mov r1, #0x12
	bl FUN_02006D18
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	mov r1, #6
	bl _u32_div_f
	add r7, r0, #0
	ldr r0, [sp, #0x18]
	mov r5, #1
	add r4, r0, #6
	cmp r7, #1
	ble _021D7CCA
	ldr r6, [sp, #8]
	add r6, #0xc
_021D7C9A:
	ldrh r0, [r4]
	cmp r0, #2
	beq _021D7CC2
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	mov r2, #2
	mov r3, #4
	add r1, r0, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r1, #0xc]
	bl MOD77_021D7D58
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
_021D7CC2:
	add r5, r5, #1
	add r4, r4, #6
	cmp r5, r7
	blt _021D7C9A
_021D7CCA:
	ldr r0, [sp, #0x18]
	bl FreeToHeap
	mov r7, #1
	bl FUN_02088D1C
	str r0, [sp, #0x10]
	cmp r0, #1
	ble _021D7D52
	ldr r6, [sp, #8]
	add r6, #0xc
_021D7CE0:
	add r0, r7, #0
	bl FUN_02088D84
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	add r0, sp, #0x1c
	str r0, [sp, #4]
	ldr r3, [sp, #8]
	mov r0, #0x66
	ldr r3, [r3]
	mov r2, #0
	bl FUN_02006D18
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	mov r5, #1
	lsr r0, r0, #2
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r4, r0, #4
	ldr r0, [sp, #0xc]
	cmp r0, #1
	ble _021D7D44
_021D7D10:
	add r0, r7, #0
	bl FUN_02088D68
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	mov r2, #0
	mov r3, #2
	add r1, r0, #0
	ldrsh r2, [r4, r2]
	ldrsh r3, [r4, r3]
	ldr r1, [r1, #0xc]
	bl MOD77_021D7D58
	ldr r0, [r6]
	add r5, r5, #1
	add r0, r0, #1
	str r0, [r6]
	ldr r0, [sp, #0xc]
	add r4, r4, #4
	cmp r5, r0
	blt _021D7D10
_021D7D44:
	ldr r0, [sp, #0x14]
	bl FreeToHeap
	ldr r0, [sp, #0x10]
	add r7, r7, #1
	cmp r7, r0
	blt _021D7CE0
_021D7D52:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD77_021D7C64

	thumb_func_start MOD77_021D7D58
MOD77_021D7D58: ; 0x021D7D58
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	ldr r5, _021D7DC8 ; =0x021D903C
	add r7, r2, #0
	add r6, r3, #0
	add r4, r0, #0
	mov ip, r1
	add r3, sp, #0xc
	mov r2, #4
_021D7D6A:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7D6A
	ldr r0, [r5]
	mov r1, #0x30
	str r0, [r3]
	mov r0, ip
	add r5, r0, #0
	mul r5, r1
	add r0, r4, r5
	strh r7, [r0, #0x10]
	strh r6, [r0, #0x12]
	mov r0, #0
	str r0, [sp, #8]
	add r0, sp, #0xc
	add r1, sp, #0
	str r7, [sp]
	str r6, [sp, #4]
	bl MOD77_021D8AA8
	add r3, r4, r5
	add r6, sp, #0xc
	add r3, #0x14
	mov r2, #4
_021D7D9C:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D7D9C
	ldr r0, [r6]
	add r2, sp, #0x38
	str r0, [r3]
	ldrh r1, [r2, #0x10]
	ldrh r2, [r2, #0x14]
	ldr r0, [r4, #4]
	bl FUN_02029B40
	add r2, r4, r5
	strh r0, [r2, #0x38]
	add r0, sp, #0x38
	ldrh r1, [r0, #0x10]
	strh r1, [r2, #0x3a]
	ldrh r0, [r0, #0x14]
	strh r0, [r2, #0x3c]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D7DC8: .word 0x021D903C
	thumb_func_end MOD77_021D7D58

	thumb_func_start MOD77_021D7DCC
MOD77_021D7DCC: ; 0x021D7DCC
	push {r4, r5, r6, r7}
	ldr r1, [r0, #0xc]
	mov r4, #0
	cmp r1, #0
	bls _021D7E0A
	ldr r1, _021D7E10 ; =0x0000C318
	add r5, r0, #0
	mov r3, #3
	sub r2, r1, #4
_021D7DDE:
	ldrh r6, [r5, #0x3a]
	ldr r7, [r0, r2]
	cmp r7, r6
	bne _021D7E00
	ldrh r6, [r5, #0x3c]
	ldr r7, [r0, r1]
	cmp r7, r6
	bne _021D7E00
	strh r3, [r5, #0x38]
	mov r6, #0x10
	ldrsh r7, [r5, r6]
	ldr r6, _021D7E14 ; =0x0000C2B4
	str r7, [r0, r6]
	mov r6, #0x12
	ldrsh r7, [r5, r6]
	ldr r6, _021D7E18 ; =0x0000C2B8
	str r7, [r0, r6]
_021D7E00:
	ldr r6, [r0, #0xc]
	add r4, r4, #1
	add r5, #0x30
	cmp r4, r6
	blo _021D7DDE
_021D7E0A:
	pop {r4, r5, r6, r7}
	bx lr
	nop
_021D7E10: .word 0x0000C318
_021D7E14: .word 0x0000C2B4
_021D7E18: .word 0x0000C2B8
	thumb_func_end MOD77_021D7DCC

	thumb_func_start MOD77_021D7E1C
MOD77_021D7E1C: ; 0x021D7E1C
	ldr r3, _021D7E20 ; =FUN_02088D20
	bx r3
	.align 2, 0
_021D7E20: .word FUN_02088D20
	thumb_func_end MOD77_021D7E1C

	thumb_func_start MOD77_021D7E24
MOD77_021D7E24: ; 0x021D7E24
	push {r4, lr}
	sub sp, #0x18
	add r4, r0, #0
	ldr r0, _021D7F2C ; =0x0000C2F8
	mov r1, #0
	str r1, [r4, r0]
	ldr r1, _021D7F30 ; =0x021C48F8
	ldrh r2, [r1, #0x20]
	cmp r2, #0
	beq _021D7E86
	ldrh r2, [r1, #0x1c]
	cmp r2, #0xc8
	blo _021D7E54
	cmp r2, #0xf8
	bhi _021D7E54
	ldrh r1, [r1, #0x1e]
	cmp r1, #0xa8
	blo _021D7E54
	cmp r1, #0xb8
	bhi _021D7E54
	mov r1, #2
	add sp, #0x18
	str r1, [r4, r0]
	pop {r4, pc}
_021D7E54:
	ldr r0, _021D7F34 ; =0x0000C2FC
	mov r2, #0
	add r1, r0, #0
	str r2, [r4, r0]
	add r1, #0xc
	str r2, [r4, r1]
	add r1, r0, #0
	add r1, #0x10
	str r2, [r4, r1]
	add r1, r0, #0
	add r1, #0x14
	str r2, [r4, r1]
	sub r1, r0, #4
	str r2, [r4, r1]
	ldr r2, _021D7F30 ; =0x021C48F8
	add r1, r0, #4
	ldrh r3, [r2, #0x1c]
	str r3, [r4, r1]
	add r1, r0, #0
	ldrh r2, [r2, #0x1e]
	add r1, #8
	add r0, #0x14
	str r2, [r4, r1]
	mov r1, #4
	str r1, [r4, r0]
_021D7E86:
	ldr r0, _021D7F30 ; =0x021C48F8
	ldrh r0, [r0, #0x22]
	cmp r0, #0
	beq _021D7F02
	ldr r1, _021D7F34 ; =0x0000C2FC
	ldr r2, [r4, r1]
	cmp r2, #0
	beq _021D7E9E
	cmp r2, #1
	beq _021D7EBA
	add sp, #0x18
	pop {r4, pc}
_021D7E9E:
	add r0, r1, #0
	add r0, #0x14
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021D7EAE
	add r0, r2, #1
	str r0, [r4, r1]
	b _021D7EBA
_021D7EAE:
	add r0, r1, #0
	add r0, #0x14
	ldr r0, [r4, r0]
	add r1, #0x14
	sub r0, r0, #1
	str r0, [r4, r1]
_021D7EBA:
	add r0, sp, #0xc
	mov r1, #0xc3
	str r0, [sp]
	add r0, sp, #8
	lsl r1, r1, #8
	str r0, [sp, #4]
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	add r2, sp, #0x14
	add r3, sp, #0x10
	bl MOD77_021D7F3C
	ldr r1, [sp, #0x14]
	ldr r0, [sp, #0xc]
	orr r0, r1
	ldr r1, _021D7F2C ; =0x0000C2F8
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r2, [sp, #0x10]
	add r0, #0x10
	str r2, [r4, r0]
	ldr r2, [sp, #8]
	add r0, r1, #0
	add r0, #0x14
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, _021D7F30 ; =0x021C48F8
	add r0, #8
	ldrh r3, [r2, #0x1c]
	add r1, #0xc
	add sp, #0x18
	str r3, [r4, r0]
	ldrh r0, [r2, #0x1e]
	str r0, [r4, r1]
	pop {r4, pc}
_021D7F02:
	ldr r0, _021D7F38 ; =0x0000C310
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _021D7F10
	mov r1, #1
	sub r0, #0x18
	str r1, [r4, r0]
_021D7F10:
	ldr r1, _021D7F34 ; =0x0000C2FC
	mov r2, #0
	add r0, r1, #0
	str r2, [r4, r1]
	add r0, #0xc
	str r2, [r4, r0]
	add r0, r1, #0
	add r0, #0x10
	str r2, [r4, r0]
	add r1, #0x14
	str r2, [r4, r1]
	add sp, #0x18
	pop {r4, pc}
	nop
_021D7F2C: .word 0x0000C2F8
_021D7F30: .word 0x021C48F8
_021D7F34: .word 0x0000C2FC
_021D7F38: .word 0x0000C310
	thumb_func_end MOD77_021D7E24

	thumb_func_start MOD77_021D7F3C
MOD77_021D7F3C: ; 0x021D7F3C
	push {r3, r4, r5, r6, r7, lr}
	mov lr, r0
	ldr r0, _021D7FA4 ; =0x021C48F8
	mov ip, r1
	ldrh r5, [r0, #0x1c]
	mov r1, #0
	add r7, r2, #0
	add r6, r3, #0
	ldr r0, _021D7FA8 ; =0x0000FFFF
	add r2, r1, #0
	add r3, r1, #0
	add r4, r1, #0
	cmp r5, r0
	beq _021D7F6C
	mov r0, lr
	sub r3, r5, r0
	bpl _021D7F66
	sub r0, r1, #1
	eor r3, r0
	mov r1, #0x10
	b _021D7F6C
_021D7F66:
	cmp r3, #0
	ble _021D7F6C
	mov r1, #0x20
_021D7F6C:
	str r1, [r7]
	mov r1, #0x3f
	add r0, r3, #0
	and r0, r1
	str r0, [r6]
	ldr r0, _021D7FA4 ; =0x021C48F8
	ldrh r3, [r0, #0x1e]
	ldr r0, _021D7FA8 ; =0x0000FFFF
	cmp r3, r0
	beq _021D7F94
	mov r0, ip
	sub r4, r3, r0
	bpl _021D7F8E
	sub r1, #0x40
	eor r4, r1
	mov r2, #0x80
	b _021D7F94
_021D7F8E:
	cmp r4, #0
	ble _021D7F94
	mov r2, #0x40
_021D7F94:
	ldr r0, [sp, #0x18]
	add r1, r4, #0
	str r2, [r0]
	mov r0, #0x3f
	and r1, r0
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7FA4: .word 0x021C48F8
_021D7FA8: .word 0x0000FFFF
	thumb_func_end MOD77_021D7F3C

	thumb_func_start MOD77_021D7FAC
MOD77_021D7FAC: ; 0x021D7FAC
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	ldr r0, _021D8208 ; =0x0000C010
	ldr r2, _021D820C ; =0x021D8F7C
	ldr r0, [r5, r0]
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, _021D8208 ; =0x0000C010
	mov r1, #6
	ldr r0, [r5, r0]
	bl FUN_02018744
	ldr r0, _021D8208 ; =0x0000C010
	ldr r2, _021D8210 ; =0x021D8F98
	ldr r0, [r5, r0]
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	ldr r2, _021D8208 ; =0x0000C010
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x81
	mov r1, #5
	mov r3, #7
	bl FUN_0200687C
	mov r0, #0x80
	str r0, [sp]
	ldr r0, [r5]
	mov r1, #6
	str r0, [sp, #4]
	mov r0, #0x81
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	mov r1, #7
	str r0, [sp, #0xc]
	ldr r2, _021D8208 ; =0x0000C010
	mov r0, #0x81
	ldr r2, [r5, r2]
	add r3, r1, #0
	bl FUN_020068C8
	ldr r0, [r5, #8]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r5]
	mov r1, #6
	str r0, [sp, #4]
	ldr r0, _021D8208 ; =0x0000C010
	ldr r2, _021D8214 ; =0x000001E2
	ldr r0, [r5, r0]
	add r3, r1, #0
	bl FUN_0200CD68
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5]
	ldr r2, _021D8218 ; =0x000001D9
	str r0, [sp, #4]
	ldr r0, _021D8208 ; =0x0000C010
	mov r1, #6
	ldr r0, [r5, r0]
	mov r3, #7
	bl FUN_0200CB00
	ldr r2, [r5]
	mov r0, #4
	mov r1, #0x80
	bl FUN_02002ED0
	ldr r3, [r5]
	mov r0, #6
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	ldr r1, _021D821C ; =0x00004753
	mov r0, #6
	bl FUN_02017FE4
	ldr r1, _021D8208 ; =0x0000C010
	ldr r2, _021D8220 ; =0x021D8F40
	ldr r0, [r5, r1]
	add r1, r1, #4
	add r1, r5, r1
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	ldr r0, _021D8224 ; =0x0000C014
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D8224 ; =0x0000C014
	ldr r2, _021D8214 ; =0x000001E2
	add r0, r5, r0
	mov r1, #0
	mov r3, #6
	bl FUN_0200D0BC
	ldr r0, _021D8228 ; =0x0000C064
	mov r3, #0
	str r3, [r5, r0]
	sub r0, #0x54
	ldr r0, [r5, r0]
	ldr r2, _021D820C ; =0x021D8F7C
	mov r1, #2
	bl FUN_02016C18
	ldr r0, _021D8208 ; =0x0000C010
	mov r1, #2
	ldr r0, [r5, r0]
	bl FUN_02018744
	ldr r0, _021D8208 ; =0x0000C010
	ldr r2, _021D8210 ; =0x021D8F98
	ldr r0, [r5, r0]
	mov r1, #3
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	ldr r2, _021D8208 ; =0x0000C010
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x81
	mov r1, #5
	mov r3, #3
	bl FUN_0200687C
	mov r0, #0x80
	str r0, [sp]
	ldr r0, [r5]
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x81
	mov r1, #6
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r5]
	ldr r2, _021D8208 ; =0x0000C010
	str r0, [sp, #0xc]
	ldr r2, [r5, r2]
	mov r0, #0x81
	mov r1, #7
	mov r3, #3
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5]
	ldr r2, _021D8218 ; =0x000001D9
	str r0, [sp, #4]
	ldr r0, _021D8208 ; =0x0000C010
	mov r1, #2
	ldr r0, [r5, r0]
	mov r3, #7
	bl FUN_0200CB00
	ldr r2, [r5]
	mov r0, #0
	mov r1, #0x80
	bl FUN_02002ED0
	ldr r3, [r5]
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	bl FUN_02017F18
	mov r0, #2
	mov r1, #0
	bl FUN_02017FE4
	ldr r1, [r5]
	mov r0, #0x10
	bl FUN_020219F4
	add r4, r0, #0
	ldr r1, [r5]
	mov r0, #2
	bl FUN_02002C50
	ldr r1, _021D822C ; =0x00004E56
	add r0, sp, #0x10
	strh r1, [r0, #6]
	ldr r1, _021D8230 ; =0x00003571
	mov r3, #0x82
	strh r1, [r0, #4]
	ldr r1, _021D8234 ; =0x0000208C
	strh r1, [r0, #2]
	ldr r1, _021D8238 ; =0x00007FFF
	strh r1, [r0]
	mov r0, #2
	add r1, sp, #0x14
	add r1, #2
	add r2, r0, #0
	bl FUN_02017FB4
	mov r0, #2
	add r1, sp, #0x14
	add r2, r0, #0
	mov r3, #0x84
	bl FUN_02017FB4
	mov r0, #2
	add r1, sp, #0x10
	add r1, #2
	add r2, r0, #0
	mov r3, #0x86
	bl FUN_02017FB4
	mov r0, #2
	add r1, sp, #0x10
	add r2, r0, #0
	mov r3, #0x9e
	bl FUN_02017FB4
	ldr r1, _021D8208 ; =0x0000C010
	ldr r2, _021D823C ; =0x021D8F30
	ldr r0, [r5, r1]
	add r1, #0x24
	add r1, r5, r1
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	ldr r0, _021D8240 ; =0x0000C034
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D8244 ; =0x0000C060
	mov r1, #0xc
	ldr r0, [r5, r0]
	add r2, r4, #0
	bl FUN_0200A8E0
	mov r0, #2
	add r1, r4, #0
	mov r2, #0
	mov r3, #0x30
	bl FUN_02002F40
	mov r1, #0
	add r3, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	ldr r0, _021D8240 ; =0x0000C034
	str r1, [sp, #8]
	add r0, r5, r0
	mov r1, #2
	add r2, r4, #0
	bl FUN_0201BD84
	add r0, r4, #0
	bl FUN_02021A20
	mov r0, #2
	bl FUN_02002CF8
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_021D8208: .word 0x0000C010
_021D820C: .word 0x021D8F7C
_021D8210: .word 0x021D8F98
_021D8214: .word 0x000001E2
_021D8218: .word 0x000001D9
_021D821C: .word 0x00004753
_021D8220: .word 0x021D8F40
_021D8224: .word 0x0000C014
_021D8228: .word 0x0000C064
_021D822C: .word 0x00004E56
_021D8230: .word 0x00003571
_021D8234: .word 0x0000208C
_021D8238: .word 0x00007FFF
_021D823C: .word 0x021D8F30
_021D8240: .word 0x0000C034
_021D8244: .word 0x0000C060
	thumb_func_end MOD77_021D7FAC

	thumb_func_start MOD77_021D8248
MOD77_021D8248: ; 0x021D8248
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D8288 ; =0x0000C034
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _021D828C ; =0x0000C014
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _021D8290 ; =0x0000C010
	mov r1, #2
	ldr r0, [r4, r0]
	bl FUN_020178A0
	ldr r0, _021D8290 ; =0x0000C010
	mov r1, #6
	ldr r0, [r4, r0]
	bl FUN_020178A0
	ldr r0, _021D8290 ; =0x0000C010
	mov r1, #3
	ldr r0, [r4, r0]
	bl FUN_020178A0
	ldr r0, _021D8290 ; =0x0000C010
	mov r1, #7
	ldr r0, [r4, r0]
	bl FUN_020178A0
	pop {r4, pc}
	nop
_021D8288: .word 0x0000C034
_021D828C: .word 0x0000C014
_021D8290: .word 0x0000C010
	thumb_func_end MOD77_021D8248

	thumb_func_start MOD77_021D8294
MOD77_021D8294: ; 0x021D8294
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _021D8348 ; =0x0000C064
	add r6, r1, #0
	ldr r1, [r5, r0]
	mov r4, #0
	cmp r1, #0
	beq _021D82B0
	cmp r1, #1
	beq _021D830A
	cmp r1, #2
	beq _021D832A
	b _021D8340
_021D82B0:
	mov r1, #0xd8
	str r1, [sp]
	mov r1, #0x20
	sub r0, #0x50
	str r1, [sp, #4]
	add r0, r5, r0
	mov r1, #0xf
	add r2, r4, #0
	add r3, r4, #0
	bl FUN_020196F4
	mov r0, #1
	ldr r1, [r5]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	ldr r2, _021D834C ; =0x0000C06C
	add r1, r6, #0
	str r0, [r5, r2]
	add r0, r2, #0
	sub r0, #0xc
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	bl FUN_0200A8E0
	ldr r0, [r5, #8]
	bl FUN_02024FF4
	add r3, r4, #0
	str r3, [sp]
	str r0, [sp, #4]
	ldr r2, _021D8350 ; =0x0000C014
	str r3, [sp, #8]
	add r0, r5, r2
	add r2, #0x58
	ldr r2, [r5, r2]
	mov r1, #1
	bl FUN_0201BD84
	ldr r1, _021D8354 ; =0x0000C068
	mov r2, #1
	str r0, [r5, r1]
	sub r0, r1, #4
	str r2, [r5, r0]
	b _021D8340
_021D830A:
	add r0, r0, #4
	ldr r0, [r5, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _021D8340
	ldr r0, _021D834C ; =0x0000C06C
	ldr r0, [r5, r0]
	bl FUN_02021A20
	ldr r0, _021D8348 ; =0x0000C064
	mov r1, #2
	str r1, [r5, r0]
	b _021D8340
_021D832A:
	cmp r2, #0
	bne _021D8338
	ldr r0, _021D8358 ; =0x021C48B8
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _021D8340
_021D8338:
	ldr r0, _021D8348 ; =0x0000C064
	mov r1, #0
	str r1, [r5, r0]
	mov r4, #1
_021D8340:
	add r0, r4, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021D8348: .word 0x0000C064
_021D834C: .word 0x0000C06C
_021D8350: .word 0x0000C014
_021D8354: .word 0x0000C068
_021D8358: .word 0x021C48B8
	thumb_func_end MOD77_021D8294

	thumb_func_start MOD77_021D835C
MOD77_021D835C: ; 0x021D835C
	push {r3, lr}
	cmp r2, #0
	bne _021D8368
	ldr r0, _021D836C ; =0x000005DC
	bl FUN_020054C8
_021D8368:
	pop {r3, pc}
	nop
_021D836C: .word 0x000005DC
	thumb_func_end MOD77_021D835C

	thumb_func_start MOD77_021D8370
MOD77_021D8370: ; 0x021D8370
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, _021D8400 ; =0x0000C010
	add r6, r3, #0
	ldr r0, [r5, r0]
	str r1, [sp]
	bl FUN_02019150
	ldrh r0, [r6, #0x10]
	ldr r1, [r5]
	bl FUN_02012838
	ldr r1, _021D8404 ; =0x0000C058
	mov r7, #0
	str r0, [r5, r1]
	ldrh r0, [r6, #0x10]
	cmp r0, #0
	ble _021D83B2
	ldr r4, [sp, #0x38]
_021D8398:
	ldr r0, _021D8404 ; =0x0000C058
	ldr r1, _021D8408 ; =0x0000C060
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl FUN_02012880
	ldrh r0, [r6, #0x10]
	add r7, r7, #1
	add r4, #8
	cmp r7, r0
	blt _021D8398
_021D83B2:
	add r3, sp, #4
	add r2, r3, #0
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, _021D8404 ; =0x0000C058
	mov r1, #0
	ldr r0, [r5, r0]
	str r0, [sp, #4]
	ldr r0, [sp]
	str r0, [sp, #0x10]
	ldr r0, _021D840C ; =MOD77_021D835C
	str r0, [sp, #8]
	ldr r3, [r5]
	add r0, r2, #0
	lsl r3, r3, #0x18
	add r2, r1, #0
	lsr r3, r3, #0x18
	bl FUN_020010A8
	ldr r1, _021D8410 ; =0x0000C054
	ldr r2, _021D8414 ; =0x000001D9
	str r0, [r5, r1]
	ldr r0, [sp, #0x10]
	mov r1, #1
	mov r3, #7
	bl FUN_0200CCA4
	ldr r0, [sp]
	bl FUN_020191D0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_021D8400: .word 0x0000C010
_021D8404: .word 0x0000C058
_021D8408: .word 0x0000C060
_021D840C: .word MOD77_021D835C
_021D8410: .word 0x0000C054
_021D8414: .word 0x000001D9
	thumb_func_end MOD77_021D8370

	thumb_func_start MOD77_021D8418
MOD77_021D8418: ; 0x021D8418
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	ldr r0, _021D84C4 ; =0x0000C010
	str r1, [sp]
	ldr r0, [r5, r0]
	str r3, [sp, #4]
	ldr r7, [sp, #0x44]
	ldr r6, [sp, #0x48]
	bl FUN_02019150
	ldr r2, [sp, #0x40]
	ldr r3, [r5]
	mov r0, #0
	mov r1, #0x1a
	bl FUN_0200A86C
	str r0, [sp, #8]
	ldr r1, [r5]
	add r0, r6, #0
	bl FUN_02012838
	ldr r1, _021D84C8 ; =0x0000C058
	mov r4, #0
	str r0, [r5, r1]
	cmp r6, #0
	bls _021D8462
_021D844E:
	ldr r0, _021D84C8 ; =0x0000C058
	ldrb r2, [r7, r4]
	ldr r0, [r5, r0]
	ldr r1, [sp, #8]
	add r3, r4, #0
	bl FUN_02012880
	add r4, r4, #1
	cmp r4, r6
	blo _021D844E
_021D8462:
	ldr r0, [sp, #8]
	bl FUN_0200A8B8
	ldr r4, [sp, #4]
	add r3, sp, #0xc
	ldmia r4!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	str r4, [sp, #4]
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	str r4, [sp, #4]
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	str r4, [sp, #4]
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, _021D84C8 ; =0x0000C058
	mov r1, #0
	ldr r0, [r5, r0]
	str r4, [sp, #4]
	str r0, [sp, #0xc]
	add r0, sp, #0xc
	strh r6, [r0, #0x10]
	ldr r0, [sp]
	str r0, [sp, #0x18]
	ldr r0, _021D84CC ; =MOD77_021D835C
	str r0, [sp, #0x10]
	ldr r3, [r5]
	add r0, r2, #0
	lsl r3, r3, #0x18
	add r2, r1, #0
	lsr r3, r3, #0x18
	bl FUN_020010A8
	ldr r1, _021D84D0 ; =0x0000C054
	ldr r2, _021D84D4 ; =0x000001D9
	str r0, [r5, r1]
	ldr r0, [sp, #0x18]
	mov r1, #1
	mov r3, #7
	bl FUN_0200CCA4
	ldr r0, [sp]
	bl FUN_020191D0
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021D84C4: .word 0x0000C010
_021D84C8: .word 0x0000C058
_021D84CC: .word MOD77_021D835C
_021D84D0: .word 0x0000C054
_021D84D4: .word 0x000001D9
	thumb_func_end MOD77_021D8418

	thumb_func_start MOD77_021D84D8
MOD77_021D84D8: ; 0x021D84D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D8504 ; =0x0000C024
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _021D8504 ; =0x0000C024
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _021D8508 ; =0x0000C054
	mov r1, #0
	ldr r0, [r4, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _021D850C ; =0x0000C058
	ldr r0, [r4, r0]
	bl FUN_02012870
	pop {r4, pc}
	.align 2, 0
_021D8504: .word 0x0000C024
_021D8508: .word 0x0000C054
_021D850C: .word 0x0000C058
	thumb_func_end MOD77_021D84D8

	thumb_func_start MOD77_021D8510
MOD77_021D8510: ; 0x021D8510
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #1
	ldr r1, [r5]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	add r4, r0, #0
	mov r0, #1
	ldr r1, [r5]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	ldr r1, _021D85C4 ; =0x0000C010
	add r6, r0, #0
	ldr r0, [r5, r1]
	add r1, #0x34
	ldr r2, _021D85C8 ; =0x021D8F28
	add r1, r5, r1
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x30
	str r0, [sp, #4]
	ldr r0, _021D85CC ; =0x0000C044
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D85CC ; =0x0000C044
	ldr r2, _021D85D0 ; =0x000001D9
	add r0, r5, r0
	mov r1, #0
	mov r3, #7
	bl FUN_0200CCA4
	ldr r0, _021D85D4 ; =0x0000C070
	ldr r2, _021D85D8 ; =0x0000C314
	ldr r0, [r5, r0]
	ldr r2, [r5, r2]
	mov r1, #0
	bl FUN_0200B4A0
	ldr r3, _021D85D8 ; =0x0000C314
	ldr r0, _021D85D4 ; =0x0000C070
	ldr r2, [r5, r3]
	add r3, r3, #4
	ldr r0, [r5, r0]
	ldr r3, [r5, r3]
	mov r1, #1
	bl FUN_0200B4D8
	ldr r0, _021D85DC ; =0x0000C060
	mov r1, #0xd
	ldr r0, [r5, r0]
	add r2, r6, #0
	bl FUN_0200A8E0
	ldr r0, _021D85D4 ; =0x0000C070
	add r1, r4, #0
	ldr r0, [r5, r0]
	add r2, r6, #0
	bl FUN_0200B7B8
	mov r1, #0
	ldr r0, _021D85CC ; =0x0000C044
	str r1, [sp]
	str r1, [sp, #4]
	add r0, r5, r0
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl FUN_0201BD84
	add r0, r6, #0
	bl FUN_02021A20
	add r0, r4, #0
	bl FUN_02021A20
	ldr r0, _021D85CC ; =0x0000C044
	add r0, r5, r0
	bl FUN_020191D0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_021D85C4: .word 0x0000C010
_021D85C8: .word 0x021D8F28
_021D85CC: .word 0x0000C044
_021D85D0: .word 0x000001D9
_021D85D4: .word 0x0000C070
_021D85D8: .word 0x0000C314
_021D85DC: .word 0x0000C060
	thumb_func_end MOD77_021D8510

	thumb_func_start MOD77_021D85E0
MOD77_021D85E0: ; 0x021D85E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	str r1, [sp, #0xc]
	ldr r1, [r5]
	mov r0, #0x40
	add r4, r2, #0
	bl FUN_020219F4
	add r7, r0, #0
	ldr r1, [r5]
	mov r0, #0x40
	bl FUN_020219F4
	ldr r1, _021D8688 ; =0x0000C010
	add r6, r0, #0
	ldr r0, [r5, r1]
	add r1, #0x34
	ldr r2, _021D868C ; =0x021D8F28
	add r1, r5, r1
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x30
	str r0, [sp, #4]
	ldr r0, _021D8690 ; =0x0000C044
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D8690 ; =0x0000C044
	ldr r2, _021D8694 ; =0x000001D9
	add r0, r5, r0
	mov r1, #0
	mov r3, #7
	bl FUN_0200CCA4
	ldr r0, [r5]
	add r1, r4, #0
	str r0, [sp]
	ldr r0, [sp, #0xc]
	add r2, r7, #0
	add r3, r6, #0
	bl MOD77_021D8E9C
	cmp r4, #0
	beq _021D865C
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, _021D8690 ; =0x0000C044
	add r2, r6, #0
	add r0, r5, r0
	add r3, r1, #0
	str r1, [sp, #8]
	bl FUN_0201BD84
_021D865C:
	mov r1, #0
	ldr r0, _021D8690 ; =0x0000C044
	str r1, [sp]
	str r1, [sp, #4]
	add r0, r5, r0
	add r2, r7, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl FUN_0201BD84
	add r0, r6, #0
	bl FUN_02021A20
	add r0, r7, #0
	bl FUN_02021A20
	ldr r0, _021D8690 ; =0x0000C044
	add r0, r5, r0
	bl FUN_020191D0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8688: .word 0x0000C010
_021D868C: .word 0x021D8F28
_021D8690: .word 0x0000C044
_021D8694: .word 0x000001D9
	thumb_func_end MOD77_021D85E0

	thumb_func_start MOD77_021D8698
MOD77_021D8698: ; 0x021D8698
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D86B0 ; =0x0000C044
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _021D86B0 ; =0x0000C044
	add r0, r4, r0
	bl FUN_02019178
	pop {r4, pc}
	.align 2, 0
_021D86B0: .word 0x0000C044
	thumb_func_end MOD77_021D8698

	thumb_func_start MOD77_021D86B4
MOD77_021D86B4: ; 0x021D86B4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	ldr r0, _021D8808 ; =0x0000C328
	ldr r1, [r5, r0]
	cmp r1, #0
	bne _021D870E
	mov r0, #1
	ldr r1, [r5]
	lsl r0, r0, #0xa
	bl FUN_020219F4
	add r4, r0, #0
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x30
	str r0, [sp, #4]
	ldr r0, _021D880C ; =0x0000C014
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, _021D8810 ; =0x0000C060
	mov r1, #0xe
	ldr r0, [r5, r0]
	add r2, r4, #0
	bl FUN_0200A8E0
	mov r3, #0
	ldr r0, _021D880C ; =0x0000C014
	str r3, [sp]
	str r3, [sp, #4]
	add r0, r5, r0
	mov r1, #1
	add r2, r4, #0
	str r3, [sp, #8]
	bl FUN_0201BD84
	add r0, r4, #0
	bl FUN_02021A20
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_021D870E:
	add r2, r0, #0
	sub r2, #0x74
	ldr r3, [r5, r2]
	mov r1, #0
	add r2, r3, #0
	sub r2, #0x30
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add r3, #0x30
	str r2, [sp, #0x18]
	lsl r2, r3, #0x10
	asr r2, r2, #0x10
	sub r0, #0x70
	str r2, [sp, #0x14]
	ldr r2, [r5, r0]
	str r1, [sp, #0x1c]
	add r0, r2, #0
	sub r0, #0x30
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r2, #0x30
	str r0, [sp, #0x10]
	lsl r0, r2, #0x10
	asr r0, r0, #0x10
	str r0, [sp, #0xc]
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bls _021D87FA
	add r4, r5, #0
_021D8748:
	mov r0, #0x10
	ldrsh r2, [r4, r0]
	ldr r0, [sp, #0x18]
	cmp r2, r0
	ble _021D87EC
	ldr r0, [sp, #0x14]
	cmp r2, r0
	bge _021D87EC
	mov r0, #0x12
	ldrsh r2, [r4, r0]
	ldr r0, [sp, #0x10]
	cmp r2, r0
	ble _021D87EC
	ldr r0, [sp, #0xc]
	cmp r2, r0
	bge _021D87EC
	ldrh r0, [r4, #0x38]
	cmp r0, #0
	beq _021D87EC
	ldr r1, [r5]
	mov r0, #0x40
	bl FUN_020219F4
	add r7, r0, #0
	ldr r1, [r5]
	mov r0, #0x40
	bl FUN_020219F4
	add r6, r0, #0
	mov r0, #0xd8
	str r0, [sp]
	mov r0, #0x30
	str r0, [sp, #4]
	ldr r0, _021D880C ; =0x0000C014
	mov r2, #0
	add r0, r5, r0
	mov r1, #0xf
	add r3, r2, #0
	bl FUN_020196F4
	ldr r0, [r5]
	add r2, r7, #0
	str r0, [sp]
	ldrh r0, [r4, #0x3a]
	ldrh r1, [r4, #0x3c]
	add r3, r6, #0
	bl MOD77_021D8E9C
	ldrh r0, [r4, #0x3c]
	cmp r0, #0
	beq _021D87C8
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, _021D880C ; =0x0000C014
	mov r1, #1
	add r0, r5, r0
	add r2, r6, #0
	mov r3, #0
	bl FUN_0201BD84
_021D87C8:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _021D880C ; =0x0000C014
	mov r1, #1
	add r0, r5, r0
	add r2, r7, #0
	mov r3, #0
	bl FUN_0201BD84
	add r0, r6, #0
	bl FUN_02021A20
	add r0, r7, #0
	bl FUN_02021A20
	mov r1, #1
_021D87EC:
	ldr r0, [sp, #0x1c]
	ldr r2, [r5, #0xc]
	add r0, r0, #1
	add r4, #0x30
	str r0, [sp, #0x1c]
	cmp r0, r2
	blo _021D8748
_021D87FA:
	cmp r1, #0
	bne _021D8804
	ldr r0, _021D8808 ; =0x0000C328
	mov r1, #0
	str r1, [r5, r0]
_021D8804:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D8808: .word 0x0000C328
_021D880C: .word 0x0000C014
_021D8810: .word 0x0000C060
	thumb_func_end MOD77_021D86B4

	thumb_func_start MOD77_021D8814
MOD77_021D8814: ; 0x021D8814
	push {r4, lr}
	add r4, r0, #0
	ldr r2, [r4]
	mov r0, #0x81
	mov r1, #0
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r2, _021D88B4 ; =0x0000C0CC
	str r0, [r4, r2]
	add r0, r2, #0
	sub r1, r2, #4
	sub r0, #0x58
	add r0, r4, r0
	add r1, r4, r1
	add r2, r4, r2
	bl FUN_0201B234
	ldr r2, [r4]
	mov r0, #0x81
	mov r1, #1
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r2, _021D88B8 ; =0x0000C294
	str r0, [r4, r2]
	add r0, r2, #0
	add r1, r2, #0
	sub r0, #0xc8
	sub r1, #0x14
	add r0, r4, r0
	add r1, r4, r1
	add r2, r4, r2
	bl FUN_0201B234
	ldr r2, [r4]
	mov r0, #0x81
	mov r1, #2
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r2, _021D88BC ; =0x0000C298
	str r0, [r4, r2]
	add r0, r2, #0
	add r1, r2, #0
	sub r0, #0x78
	sub r1, #0x14
	add r0, r4, r0
	add r1, r4, r1
	add r2, r4, r2
	bl FUN_0201B234
	ldr r2, [r4]
	mov r0, #0x81
	mov r1, #3
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r2, _021D88C0 ; =0x0000C28C
	str r0, [r4, r2]
	add r1, r2, #0
	ldr r0, _021D88C4 ; =0x0000C124
	sub r1, #0x14
	add r0, r4, r0
	add r1, r4, r1
	add r2, r4, r2
	bl FUN_0201B234
	ldr r2, [r4]
	mov r0, #0x81
	mov r1, #4
	bl AllocAndReadWholeNarcMemberByIdPair
	ldr r2, _021D88C8 ; =0x0000C290
	str r0, [r4, r2]
	add r1, r2, #0
	ldr r0, _021D88CC ; =0x0000C178
	sub r1, #0x14
	add r0, r4, r0
	add r1, r4, r1
	add r2, r4, r2
	bl FUN_0201B234
	pop {r4, pc}
	.align 2, 0
_021D88B4: .word 0x0000C0CC
_021D88B8: .word 0x0000C294
_021D88BC: .word 0x0000C298
_021D88C0: .word 0x0000C28C
_021D88C4: .word 0x0000C124
_021D88C8: .word 0x0000C290
_021D88CC: .word 0x0000C178
	thumb_func_end MOD77_021D8814

	thumb_func_start MOD77_021D88D0
MOD77_021D88D0: ; 0x021D88D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021D8900 ; =0x0000C290
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021D8904 ; =0x0000C28C
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021D8908 ; =0x0000C298
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021D890C ; =0x0000C294
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _021D8910 ; =0x0000C0CC
	ldr r0, [r4, r0]
	bl FreeToHeap
	pop {r4, pc}
	nop
_021D8900: .word 0x0000C290
_021D8904: .word 0x0000C28C
_021D8908: .word 0x0000C298
_021D890C: .word 0x0000C294
_021D8910: .word 0x0000C0CC
	thumb_func_end MOD77_021D88D0

	thumb_func_start MOD77_021D8914
MOD77_021D8914: ; 0x021D8914
	push {r4, r5}
	ldr r1, _021D896C ; =0x0000C29C
	mov r3, #0
	str r3, [r0, r1]
	add r2, r1, #4
	str r3, [r0, r2]
	add r2, r1, #0
	add r2, #8
	str r3, [r0, r2]
	mov r2, #1
	add r4, r1, #0
	lsl r2, r2, #0xc
	add r4, #0xc
	str r2, [r0, r4]
	add r4, r1, #0
	add r4, #0x10
	str r2, [r0, r4]
	add r4, r1, #0
	add r4, #0x14
	str r2, [r0, r4]
	mov r5, #0x69
	add r4, r1, #0
	lsl r5, r5, #6
	add r4, #0x18
	str r5, [r0, r4]
	mov r5, #0x1f
	add r4, r1, #0
	lsl r5, r5, #0xa
	add r4, #0x1c
	str r5, [r0, r4]
	add r4, r1, #0
	add r4, #0x20
	str r3, [r0, r4]
	add r3, r1, #0
	add r3, #0x24
	str r2, [r0, r3]
	add r3, r1, #0
	add r3, #0x28
	str r2, [r0, r3]
	add r1, #0x2c
	str r2, [r0, r1]
	pop {r4, r5}
	bx lr
	nop
_021D896C: .word 0x0000C29C
	thumb_func_end MOD77_021D8914

	thumb_func_start MOD77_021D8970
MOD77_021D8970: ; 0x021D8970
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r6, _021D89E4 ; =0x021D8F48
	add r4, r0, #0
	ldmia r6!, {r0, r1}
	add r5, sp, #8
	add r2, r5, #0
	stmia r5!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r5]
	add r7, sp, #0x14
	mov r3, #0
	str r3, [r7]
	str r3, [r7, #4]
	str r3, [r7, #8]
	ldr r0, _021D89E8 ; =0x0000C2CC
	str r3, [sp]
	ldr r0, [r4, r0]
	ldr r2, _021D89EC ; =0x000005C1
	str r0, [sp, #4]
	add r0, r7, #0
	bl FUN_0201ED5C
	ldr r2, _021D89E8 ; =0x0000C2CC
	mov r1, #0x19
	ldr r2, [r4, r2]
	mov r0, #0
	lsl r1, r1, #0xe
	bl FUN_0201EC94
	ldr r1, _021D89E8 ; =0x0000C2CC
	mov r0, #0
	ldr r1, [r4, r1]
	bl FUN_0201EE2C
	ldr r0, _021D89E8 ; =0x0000C2CC
	ldr r0, [r4, r0]
	bl FUN_0201EB8C
	ldr r0, _021D89F0 ; =0x0000C2F4
	ldrh r1, [r4, r0]
	cmp r1, #0
	bne _021D89D0
	mov r1, #1
	sub r0, #0x1c
	strh r1, [r4, r0]
	b _021D89D6
_021D89D0:
	mov r1, #0
	sub r0, #0x1c
	strh r1, [r4, r0]
_021D89D6:
	add r0, r4, #0
	bl MOD77_021D8CF8
	cmp r0, #1
	bne _021D89D6
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D89E4: .word 0x021D8F48
_021D89E8: .word 0x0000C2CC
_021D89EC: .word 0x000005C1
_021D89F0: .word 0x0000C2F4
	thumb_func_end MOD77_021D8970

	thumb_func_start MOD77_021D89F4
MOD77_021D89F4: ; 0x021D89F4
	push {r4, lr}
	ldr r3, _021D8A28 ; =0x0000C2DC
	add r4, r0, #0
	mov r0, #0
	str r0, [r4, r3]
	add r1, r3, #4
	str r0, [r4, r1]
	add r1, r3, #0
	ldr r2, _021D8A2C ; =0xFFFFF001
	add r1, #8
	str r2, [r4, r1]
	ldr r1, [r4, r3]
	add r2, r3, #4
	add r3, #8
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	asr r1, r1, #0x10
	asr r2, r2, #0x10
	asr r3, r3, #0x10
	bl FUN_020B8418
	pop {r4, pc}
	nop
_021D8A28: .word 0x0000C2DC
_021D8A2C: .word 0xFFFFF001
	thumb_func_end MOD77_021D89F4

	thumb_func_start MOD77_021D8A30
MOD77_021D8A30: ; 0x021D8A30
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r1, #0
	ldr r1, [r4, #4]
	ldr r3, _021D8AA4 ; =0x020FFA38
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	asr r1, r1, #4
	lsl r2, r1, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r5, r0, #0
	bl MTX_RotY33_
	ldr r0, [r4]
	ldr r3, _021D8AA4 ; =0x020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotX33_
	add r0, r5, #0
	add r1, sp, #0
	add r2, r5, #0
	bl MTX_Concat33
	ldr r0, [r4, #8]
	ldr r3, _021D8AA4 ; =0x020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotZ33_
	add r0, r5, #0
	add r1, sp, #0
	add r2, r5, #0
	bl MTX_Concat33
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_021D8AA4: .word 0x020FFA38
	thumb_func_end MOD77_021D8A30

	thumb_func_start MOD77_021D8AA8
MOD77_021D8AA8: ; 0x021D8AA8
	push {r4, r5, lr}
	sub sp, #0x24
	add r4, r1, #0
	ldr r1, [r4]
	ldr r3, _021D8B1C ; =0x020FFA38
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	asr r1, r1, #4
	lsl r2, r1, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r5, r0, #0
	bl MTX_RotY33_
	ldr r0, [r4, #4]
	ldr r3, _021D8B1C ; =0x020FFA38
	neg r0, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r2, r0, #1
	lsl r1, r2, #1
	add r2, r2, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotX33_
	add r0, r5, #0
	add r1, sp, #0
	add r2, r5, #0
	bl MTX_Concat33
	ldr r0, [r4, #8]
	ldr r3, _021D8B1C ; =0x020FFA38
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r2, r0, #1
	add r1, r2, #1
	lsl r1, r1, #1
	lsl r2, r2, #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	add r0, sp, #0
	bl MTX_RotZ33_
	add r0, r5, #0
	add r1, sp, #0
	add r2, r5, #0
	bl MTX_Concat33
	add sp, #0x24
	pop {r4, r5, pc}
	.align 2, 0
_021D8B1C: .word 0x020FFA38
	thumb_func_end MOD77_021D8AA8

	thumb_func_start MOD77_021D8B20
MOD77_021D8B20: ; 0x021D8B20
	push {r3, r4, r5, r6, r7, lr}
	add r3, r0, #0
	ldr r0, _021D8CD8 ; =0x0000C2B4
	add r7, r2, #0
	add r4, r0, #4
	ldr r4, [r3, r4]
	ldr r2, [r3, r0]
	lsl r4, r4, #0x10
	asr r4, r4, #0x10
	lsl r2, r2, #0x10
	mov lr, r4
	mov r4, #1
	mov r6, #0
	asr r2, r2, #0x10
	tst r1, r4
	bne _021D8B4E
	add r1, r0, #0
	add r1, #0x44
	ldr r4, [r3, r1]
	mov r1, #1
	mov ip, r4
	tst r1, r4
	beq _021D8B72
_021D8B4E:
	ldr r1, _021D8CDC ; =0x0000C2F4
	ldrh r0, [r3, r1]
	cmp r0, #1
	bne _021D8B6E
	add r0, r1, #0
	sub r0, #0x1c
	ldrh r0, [r3, r0]
	cmp r0, #0
	bne _021D8B68
	mov r0, #1
	sub r1, #0x1c
	strh r0, [r3, r1]
	b _021D8B6E
_021D8B68:
	mov r0, #0
	sub r1, #0x1c
	strh r0, [r3, r1]
_021D8B6E:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021D8B72:
	add r1, r0, #0
	add r1, #0x24
	ldrh r1, [r3, r1]
	cmp r1, #0
	bne _021D8BA4
	add r1, r0, #0
	add r1, #0x54
	ldr r1, [r3, r1]
	cmp r1, #0
	bne _021D8B8E
	add r0, #0x58
	ldr r0, [r3, r0]
	cmp r0, #0
	beq _021D8B9C
_021D8B8E:
	lsl r0, r1, #0x16
	ldr r1, _021D8CE0 ; =0x0000C30C
	lsr r0, r0, #0x10
	ldr r1, [r3, r1]
	lsl r1, r1, #0x16
	lsr r1, r1, #0x10
	b _021D8BC8
_021D8B9C:
	mov r0, #1
	lsl r0, r0, #9
	add r1, r0, #0
	b _021D8BC8
_021D8BA4:
	add r1, r0, #0
	add r1, #0x54
	ldr r1, [r3, r1]
	cmp r1, #0
	bne _021D8BB6
	add r0, #0x58
	ldr r0, [r3, r0]
	cmp r0, #0
	beq _021D8BC4
_021D8BB6:
	lsl r0, r1, #0x12
	ldr r1, _021D8CE0 ; =0x0000C30C
	lsr r0, r0, #0x10
	ldr r1, [r3, r1]
	lsl r1, r1, #0x12
	lsr r1, r1, #0x10
	b _021D8BC8
_021D8BC4:
	mov r0, #0x20
	add r1, r0, #0
_021D8BC8:
	mov r4, #0x20
	tst r4, r7
	bne _021D8BD6
	mov r5, ip
	mov r4, #0x20
	tst r4, r5
	beq _021D8C02
_021D8BD6:
	ldr r6, _021D8CDC ; =0x0000C2F4
	ldrh r4, [r3, r6]
	cmp r4, #1
	bne _021D8BEC
	add r4, r6, #0
	sub r4, #0x3c
	ldr r4, [r3, r4]
	sub r6, #0x3c
	add r4, r4, r0
	str r4, [r3, r6]
	b _021D8C00
_021D8BEC:
	ldr r5, _021D8CE4 ; =0xFFFFD820
	mov r4, lr
	cmp r4, r5
	bge _021D8C00
	add r4, r6, #0
	sub r4, #0x3c
	ldr r4, [r3, r4]
	sub r6, #0x3c
	add r4, r4, r0
	str r4, [r3, r6]
_021D8C00:
	mov r6, #1
_021D8C02:
	mov r4, #0x10
	tst r4, r7
	bne _021D8C12
	ldr r4, _021D8CE8 ; =0x0000C2F8
	ldr r5, [r3, r4]
	mov r4, #0x10
	tst r4, r5
	beq _021D8C3E
_021D8C12:
	ldr r5, _021D8CDC ; =0x0000C2F4
	ldrh r4, [r3, r5]
	cmp r4, #1
	bne _021D8C28
	add r4, r5, #0
	sub r4, #0x3c
	ldr r4, [r3, r4]
	sub r5, #0x3c
	sub r0, r4, r0
	str r0, [r3, r5]
	b _021D8C3C
_021D8C28:
	ldr r4, _021D8CEC ; =0xFFFFCC80
	mov r6, lr
	cmp r6, r4
	ble _021D8C3C
	add r4, r5, #0
	sub r4, #0x3c
	ldr r4, [r3, r4]
	sub r5, #0x3c
	sub r0, r4, r0
	str r0, [r3, r5]
_021D8C3C:
	mov r6, #1
_021D8C3E:
	mov r4, #0x40
	add r0, r7, #0
	tst r0, r4
	bne _021D8C4E
	ldr r0, _021D8CE8 ; =0x0000C2F8
	ldr r0, [r3, r0]
	tst r0, r4
	beq _021D8C88
_021D8C4E:
	ldr r4, _021D8CDC ; =0x0000C2F4
	ldrh r0, [r3, r4]
	cmp r0, #1
	bne _021D8C74
	mov r0, #0x3e
	add r5, r2, r1
	lsl r0, r0, #8
	cmp r5, r0
	bge _021D8C6E
	add r0, r4, #0
	sub r0, #0x40
	ldr r0, [r3, r0]
	sub r4, #0x40
	add r0, r0, r1
	str r0, [r3, r4]
	b _021D8C86
_021D8C6E:
	sub r4, #0x40
	str r0, [r3, r4]
	b _021D8C86
_021D8C74:
	ldr r0, _021D8CF0 ; =0x00002020
	cmp r2, r0
	bge _021D8C86
	add r0, r4, #0
	sub r0, #0x40
	ldr r0, [r3, r0]
	sub r4, #0x40
	add r0, r0, r1
	str r0, [r3, r4]
_021D8C86:
	mov r6, #1
_021D8C88:
	mov r4, #0x80
	add r0, r7, #0
	tst r0, r4
	bne _021D8C98
	ldr r0, _021D8CE8 ; =0x0000C2F8
	ldr r0, [r3, r0]
	tst r0, r4
	beq _021D8CD2
_021D8C98:
	ldr r4, _021D8CDC ; =0x0000C2F4
	ldrh r0, [r3, r4]
	cmp r0, #1
	bne _021D8CBC
	ldr r0, _021D8CF4 ; =0xFFFFC200
	sub r2, r2, r1
	cmp r2, r0
	ble _021D8CB6
	add r0, r4, #0
	sub r0, #0x40
	ldr r0, [r3, r0]
	sub r4, #0x40
	sub r0, r0, r1
	str r0, [r3, r4]
	b _021D8CD0
_021D8CB6:
	sub r4, #0x40
	str r0, [r3, r4]
	b _021D8CD0
_021D8CBC:
	mov r0, #0x13
	lsl r0, r0, #8
	cmp r2, r0
	ble _021D8CD0
	add r0, r4, #0
	sub r0, #0x40
	ldr r0, [r3, r0]
	sub r4, #0x40
	sub r0, r0, r1
	str r0, [r3, r4]
_021D8CD0:
	mov r6, #1
_021D8CD2:
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8CD8: .word 0x0000C2B4
_021D8CDC: .word 0x0000C2F4
_021D8CE0: .word 0x0000C30C
_021D8CE4: .word 0xFFFFD820
_021D8CE8: .word 0x0000C2F8
_021D8CEC: .word 0xFFFFCC80
_021D8CF0: .word 0x00002020
_021D8CF4: .word 0xFFFFC200
	thumb_func_end MOD77_021D8B20

	thumb_func_start MOD77_021D8CF8
MOD77_021D8CF8: ; 0x021D8CF8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _021D8D7C ; =0x0000C2CC
	ldr r0, [r5, r0]
	bl FUN_0201F010
	ldr r1, _021D8D80 ; =0x0000C2D8
	mov r4, #0
	ldrh r2, [r5, r1]
	cmp r2, #0
	beq _021D8D42
	cmp r2, #1
	bne _021D8D70
	mov r2, #0x16
	lsl r2, r2, #0xe
	cmp r0, r2
	ble _021D8D3A
	mov r2, #2
	lsl r2, r2, #0xe
	sub r0, r0, r2
	add r2, r1, #0
	sub r2, #0x18
	ldr r3, [r5, r2]
	add r2, r1, #0
	sub r3, #0x80
	sub r2, #0x18
	str r3, [r5, r2]
	add r2, r1, #0
	sub r2, #0x18
	ldr r2, [r5, r2]
	sub r1, #0x14
	str r2, [r5, r1]
	b _021D8D70
_021D8D3A:
	mov r0, #5
	lsl r0, r0, #0x10
	mov r4, #1
	b _021D8D70
_021D8D42:
	mov r2, #0x12
	lsl r2, r2, #0x10
	cmp r0, r2
	bge _021D8D6A
	mov r2, #2
	lsl r2, r2, #0xe
	add r0, r0, r2
	add r2, r1, #0
	sub r2, #0x18
	ldr r3, [r5, r2]
	add r2, r1, #0
	add r3, #0x80
	sub r2, #0x18
	str r3, [r5, r2]
	add r2, r1, #0
	sub r2, #0x18
	ldr r2, [r5, r2]
	sub r1, #0x14
	str r2, [r5, r1]
	b _021D8D70
_021D8D6A:
	mov r0, #0x4a
	lsl r0, r0, #0xe
	mov r4, #1
_021D8D70:
	ldr r1, _021D8D7C ; =0x0000C2CC
	ldr r1, [r5, r1]
	bl FUN_0201EFE0
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_021D8D7C: .word 0x0000C2CC
_021D8D80: .word 0x0000C2D8
	thumb_func_end MOD77_021D8CF8

	thumb_func_start MOD77_021D8D84
MOD77_021D8D84: ; 0x021D8D84
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x70
	ldr r4, _021D8E74 ; =0x021D8FF4
	add r5, r0, #0
	add r3, sp, #0x4c
	mov r2, #4
_021D8D90:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D8D90
	ldr r0, [r4]
	str r0, [r3]
	ldr r0, _021D8E78 ; =0x0000C2E8
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _021D8E6E
	cmp r0, #1
	beq _021D8DC2
	cmp r0, #2
	bne _021D8E6E
	bl FUN_020222AC
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
	ldr r0, _021D8E78 ; =0x0000C2E8
	mov r1, #0
	add sp, #0x70
	str r1, [r5, r0]
	pop {r3, r4, r5, r6, r7, pc}
_021D8DC2:
	bl FUN_020222AC
	bl FUN_0201EBA4
	ldr r1, _021D8E7C ; =0x0000C2B4
	add r0, sp, #0x4c
	add r1, r5, r1
	bl MOD77_021D8A30
	ldr r3, _021D8E80 ; =0x0000C29C
	ldr r0, _021D8E84 ; =0x0000C074
	add r1, r5, r3
	add r3, #0xc
	add r0, r5, r0
	add r2, sp, #0x4c
	add r3, r5, r3
	bl FUN_0201B26C
	ldr r4, _021D8E88 ; =0x021D9060
	add r3, sp, #0x28
	mov r2, #4
_021D8DEC:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D8DEC
	ldr r0, [r4]
	add r2, sp, #0x28
	str r0, [r3]
	ldr r3, _021D8E8C ; =0x0000C220
	add r1, r3, #0
	add r0, r5, r3
	add r1, #0x7c
	add r3, #0xa0
	add r1, r5, r1
	add r3, r5, r3
	bl FUN_0201B26C
	ldr r4, _021D8E90 ; =0x021D9018
	add r3, sp, #4
	mov r2, #4
_021D8E12:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _021D8E12
	ldr r0, [r4]
	mov r7, #0
	str r0, [r3]
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bls _021D8E66
	ldr r0, _021D8E94 ; =0x0000C0D0
	add r6, r5, #0
	add r0, r5, r0
	add r6, #0x14
	add r4, r5, #0
	str r0, [sp]
_021D8E32:
	add r0, r6, #0
	add r1, sp, #0x4c
	add r2, sp, #4
	bl MTX_Concat33
	ldrh r2, [r4, #0x38]
	cmp r2, #0
	beq _021D8E5A
	add r1, r2, #0
	mov r0, #0x54
	mul r1, r0
	ldr r0, [sp]
	ldr r3, _021D8E98 ; =0x0000C2C0
	add r0, r0, r1
	ldr r1, _021D8E80 ; =0x0000C29C
	add r2, sp, #4
	add r1, r5, r1
	add r3, r5, r3
	bl FUN_0201B26C
_021D8E5A:
	ldr r0, [r5, #0xc]
	add r7, r7, #1
	add r6, #0x30
	add r4, #0x30
	cmp r7, r0
	blo _021D8E32
_021D8E66:
	mov r0, #0
	mov r1, #1
	bl FUN_020222B4
_021D8E6E:
	add sp, #0x70
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021D8E74: .word 0x021D8FF4
_021D8E78: .word 0x0000C2E8
_021D8E7C: .word 0x0000C2B4
_021D8E80: .word 0x0000C29C
_021D8E84: .word 0x0000C074
_021D8E88: .word 0x021D9060
_021D8E8C: .word 0x0000C220
_021D8E90: .word 0x021D9018
_021D8E94: .word 0x0000C0D0
_021D8E98: .word 0x0000C2C0
	thumb_func_end MOD77_021D8D84

	thumb_func_start MOD77_021D8E9C
MOD77_021D8E9C: ; 0x021D8E9C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	str r1, [sp]
	add r6, r2, #0
	str r3, [sp, #4]
	bl MOD77_021D7E1C
	ldr r7, [sp, #0x20]
	mov r2, #0x99
	add r4, r0, #0
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	add r3, r7, #0
	bl FUN_0200A86C
	str r0, [sp, #8]
	add r1, r5, #0
	add r2, r6, #0
	bl FUN_0200A8E0
	ldr r0, [sp, #8]
	bl FUN_0200A8B8
	cmp r4, #0
	bne _021D8EDA
	mov r5, #0
	mov r4, #1
	str r5, [sp]
	b _021D8EDC
_021D8EDA:
	mov r5, #1
_021D8EDC:
	add r0, r4, #0
	bl FUN_02088D4C
	add r2, r0, #0
	mov r0, #0
	mov r1, #0x1a
	add r3, r7, #0
	bl FUN_0200A86C
	ldr r1, [sp]
	ldr r2, [sp, #4]
	add r4, r0, #0
	bl FUN_0200A8E0
	add r0, r4, #0
	bl FUN_0200A8B8
	add r0, r5, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD77_021D8E9C

	thumb_func_start MOD77_021D8F04
MOD77_021D8F04: ; 0x021D8F04
	push {r3, lr}
	bl MOD77_021D7E1C
	cmp r0, #0
	beq _021D8F12
	mov r0, #1
	pop {r3, pc}
_021D8F12:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD77_021D8F04

	.section .rodata
	; 0x021D8F18
	.byte 0x06, 0x13, 0x0B, 0x0C, 0x06, 0x04, 0x25, 0x01, 0x06, 0x03, 0x02, 0x1A, 0x0E, 0x04, 0x01, 0x00
	.byte 0x06, 0x02, 0x01, 0x1B, 0x06, 0x04, 0xB3, 0x00, 0x02, 0x19, 0x15, 0x06, 0x02, 0x04, 0xCD, 0x01
	.byte 0x06, 0x19, 0x0D, 0x06, 0x04, 0x04, 0x55, 0x01, 0x06, 0x02, 0x13, 0x1B, 0x04, 0x04, 0x6D, 0x01
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x12, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0F, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00
	.byte 0x00, 0x0C, 0x00, 0x10, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00
	.byte 0x00, 0x0C, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00
