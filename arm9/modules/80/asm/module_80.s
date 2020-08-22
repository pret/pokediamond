	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD80_0222D5C0
MOD80_0222D5C0: ; 0x0222D5C0
	push {r3, r4}
	ldr r3, _0222D5D8 ; =0x02237CE0
	mov r4, #1
	str r4, [r3]
	mov r4, #0
	str r4, [r3, #4]
	str r0, [r3, #8]
	str r1, [r3, #0xc]
	str r2, [r3, #0x10]
	pop {r3, r4}
	bx lr
	nop
_0222D5D8: .word MOD80_02237CE0
	thumb_func_end MOD80_0222D5C0

	thumb_func_start MOD80_0222D5DC
MOD80_0222D5DC: ; 0x0222D5DC
	push {r3, lr}
	ldr r1, _0222D8D4 ; =0x02237CE0
	ldr r0, [r1]
	cmp r0, #0x16
	bls _0222D5E8
	b _0222DB8A
_0222D5E8:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222D5F4: ; jump table
	.short _0222DB8A - _0222D5F4 - 2 ; case 0
	.short _0222DB8A - _0222D5F4 - 2 ; case 1
	.short _0222D622 - _0222D5F4 - 2 ; case 2
	.short _0222DB7E - _0222D5F4 - 2 ; case 3
	.short _0222D6D0 - _0222D5F4 - 2 ; case 4
	.short _0222DB7E - _0222D5F4 - 2 ; case 5
	.short _0222D756 - _0222D5F4 - 2 ; case 6
	.short _0222DB7E - _0222D5F4 - 2 ; case 7
	.short _0222D7D6 - _0222D5F4 - 2 ; case 8
	.short _0222DB7E - _0222D5F4 - 2 ; case 9
	.short _0222D86A - _0222D5F4 - 2 ; case 10
	.short _0222DB7E - _0222D5F4 - 2 ; case 11
	.short _0222D8EA - _0222D5F4 - 2 ; case 12
	.short _0222DB7E - _0222D5F4 - 2 ; case 13
	.short _0222D970 - _0222D5F4 - 2 ; case 14
	.short _0222DB7E - _0222D5F4 - 2 ; case 15
	.short _0222D9E8 - _0222D5F4 - 2 ; case 16
	.short _0222DB7E - _0222D5F4 - 2 ; case 17
	.short _0222DABA - _0222D5F4 - 2 ; case 18
	.short _0222DB7E - _0222D5F4 - 2 ; case 19
	.short _0222DB0E - _0222D5F4 - 2 ; case 20
	.short _0222DB7E - _0222D5F4 - 2 ; case 21
	.short _0222DB8A - _0222D5F4 - 2 ; case 22
_0222D622:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D630
	cmp r0, #7
	beq _0222D648
	pop {r3, pc}
_0222D630:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222D8D4 ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D648:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	ldr r2, _0222D8D8 ; =0x02237E00
	str r1, [r0]
	ldrb r2, [r2, #0x1c]
	cmp r2, #0xe
	bhi _0222D6C2
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_0222D662: ; jump table
	.short _0222D6C2 - _0222D662 - 2 ; case 0
	.short _0222D680 - _0222D662 - 2 ; case 1
	.short _0222D686 - _0222D662 - 2 ; case 2
	.short _0222D68C - _0222D662 - 2 ; case 3
	.short _0222D6C2 - _0222D662 - 2 ; case 4
	.short _0222D6C2 - _0222D662 - 2 ; case 5
	.short _0222D6C2 - _0222D662 - 2 ; case 6
	.short _0222D692 - _0222D662 - 2 ; case 7
	.short _0222D6A4 - _0222D662 - 2 ; case 8
	.short _0222D6AA - _0222D662 - 2 ; case 9
	.short _0222D6B0 - _0222D662 - 2 ; case 10
	.short _0222D6B6 - _0222D662 - 2 ; case 11
	.short _0222D698 - _0222D662 - 2 ; case 12
	.short _0222D69E - _0222D662 - 2 ; case 13
	.short _0222D6BC - _0222D662 - 2 ; case 14
_0222D680:
	mov r1, #0
	str r1, [r0, #4]
	b _0222D6CA
_0222D686:
	sub r1, #0x1b
	str r1, [r0, #4]
	b _0222D6CA
_0222D68C:
	sub r1, #0x1a
	str r1, [r0, #4]
	b _0222D6CA
_0222D692:
	sub r1, #0x17
	str r1, [r0, #4]
	b _0222D6CA
_0222D698:
	sub r1, #0x1c
	str r1, [r0, #4]
	b _0222D6CA
_0222D69E:
	sub r1, #0x1d
	str r1, [r0, #4]
	b _0222D6CA
_0222D6A4:
	sub r1, #0x1e
	str r1, [r0, #4]
	b _0222D6CA
_0222D6AA:
	sub r1, #0x1f
	str r1, [r0, #4]
	b _0222D6CA
_0222D6B0:
	sub r1, #0x20
	str r1, [r0, #4]
	b _0222D6CA
_0222D6B6:
	sub r1, #0x21
	str r1, [r0, #4]
	b _0222D6CA
_0222D6BC:
	sub r1, #0x18
	str r1, [r0, #4]
	b _0222D6CA
_0222D6C2:
	mov r1, #0xc
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222D6CA:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D6D0:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D6DE
	cmp r0, #7
	beq _0222D6F6
	pop {r3, pc}
_0222D6DE:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222D8D4 ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D6F6:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r2, #0x16
	ldr r1, _0222D8D8 ; =0x02237E00
	str r2, [r0]
	ldrb r1, [r1, #0x1c]
	cmp r1, #5
	bgt _0222D720
	cmp r1, #0
	blt _0222D748
	add r3, r1, r1
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0222D714: ; jump table
	.short _0222D748 - _0222D714 - 2 ; case 0
	.short _0222D726 - _0222D714 - 2 ; case 1
	.short _0222D72C - _0222D714 - 2 ; case 2
	.short _0222D732 - _0222D714 - 2 ; case 3
	.short _0222D748 - _0222D714 - 2 ; case 4
	.short _0222D738 - _0222D714 - 2 ; case 5
_0222D720:
	cmp r1, #0xe
	beq _0222D73E
	b _0222D748
_0222D726:
	mov r1, #0
	str r1, [r0, #4]
	b _0222D750
_0222D72C:
	sub r2, #0x1b
	str r2, [r0, #4]
	b _0222D750
_0222D732:
	sub r2, #0x1a
	str r2, [r0, #4]
	b _0222D750
_0222D738:
	sub r2, #0x19
	str r2, [r0, #4]
	b _0222D750
_0222D73E:
	mov r1, #1
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D750
_0222D748:
	mov r1, #0xc
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222D750:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D756:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D764
	cmp r0, #7
	beq _0222D77C
	pop {r3, pc}
_0222D764:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222D8D4 ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D77C:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212480
	mov r1, #0x49
	lsl r1, r1, #2
	cmp r0, r1
	bne _0222D796
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0
	str r1, [r0, #4]
	b _0222D7D0
_0222D796:
	ldr r0, _0222D8DC ; =0x02237DE0
	ldr r0, [r0, #0x40]
	ldrb r0, [r0]
	cmp r0, #3
	beq _0222D7B4
	cmp r0, #5
	beq _0222D7AA
	cmp r0, #0xe
	beq _0222D7BE
	b _0222D7C8
_0222D7AA:
	mov r1, #2
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D7D0
_0222D7B4:
	mov r1, #3
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D7D0
_0222D7BE:
	mov r1, #1
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D7D0
_0222D7C8:
	mov r1, #0xc
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222D7D0:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D7D6:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D7E4
	cmp r0, #7
	beq _0222D7FC
	pop {r3, pc}
_0222D7E4:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222D8D4 ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D7FC:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212480
	mov r1, #0x49
	lsl r1, r1, #2
	cmp r0, r1
	bne _0222D816
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #1
	str r1, [r0, #4]
	b _0222D864
_0222D816:
	ldr r0, _0222D8DC ; =0x02237DE0
	ldr r0, [r0, #0x40]
	ldrb r0, [r0]
	cmp r0, #5
	bgt _0222D830
	cmp r0, #3
	blt _0222D85C
	beq _0222D840
	cmp r0, #4
	beq _0222D84A
	cmp r0, #5
	beq _0222D836
	b _0222D85C
_0222D830:
	cmp r0, #0xe
	beq _0222D852
	b _0222D85C
_0222D836:
	mov r1, #2
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D864
_0222D840:
	mov r1, #3
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D864
_0222D84A:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0
	str r1, [r0, #4]
	b _0222D864
_0222D852:
	mov r1, #1
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D864
_0222D85C:
	mov r1, #0xc
	ldr r0, _0222D8D4 ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222D864:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D86A:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D878
	cmp r0, #7
	beq _0222D890
	pop {r3, pc}
_0222D878:
	ldr r0, _0222D8D4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222D8D4 ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D890:
	ldr r1, _0222D8D4 ; =0x02237CE0
	mov r2, #0x16
	ldr r0, _0222D8D8 ; =0x02237E00
	str r2, [r1]
	ldrb r0, [r0, #0x1c]
	cmp r0, #5
	bgt _0222D8AE
	cmp r0, #1
	blt _0222D8CC
	beq _0222D8B4
	cmp r0, #3
	beq _0222D8C0
	cmp r0, #5
	beq _0222D8BA
	b _0222D8CC
_0222D8AE:
	cmp r0, #0xe
	beq _0222D8C6
	b _0222D8CC
_0222D8B4:
	mov r0, #0
	str r0, [r1, #4]
	b _0222D8E4
_0222D8BA:
	sub r2, #0x19
	str r2, [r1, #4]
	b _0222D8E4
_0222D8C0:
	sub r2, #0x1a
	str r2, [r1, #4]
	b _0222D8E4
_0222D8C6:
	sub r2, #0x18
	str r2, [r1, #4]
	b _0222D8E4
_0222D8CC:
	mov r1, #0xc
	ldr r0, _0222D8D4 ; =0x02237CE0
	b _0222D8E0
	nop
_0222D8D4: .word MOD80_02237CE0
_0222D8D8: .word MOD80_02237E00
_0222D8DC: .word MOD80_02237DE0
_0222D8E0:
	mvn r1, r1
	str r1, [r0, #4]
_0222D8E4:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D8EA:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D8F8
	cmp r0, #7
	beq _0222D910
	pop {r3, pc}
_0222D8F8:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222DB8C ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D910:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r2, #0x16
	ldr r1, _0222DB90 ; =0x02237E00
	str r2, [r0]
	ldrb r1, [r1, #0x1c]
	cmp r1, #5
	bgt _0222D93A
	cmp r1, #0
	blt _0222D962
	add r3, r1, r1
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0222D92E: ; jump table
	.short _0222D962 - _0222D92E - 2 ; case 0
	.short _0222D940 - _0222D92E - 2 ; case 1
	.short _0222D94C - _0222D92E - 2 ; case 2
	.short _0222D952 - _0222D92E - 2 ; case 3
	.short _0222D962 - _0222D92E - 2 ; case 4
	.short _0222D946 - _0222D92E - 2 ; case 5
_0222D93A:
	cmp r1, #0xe
	beq _0222D958
	b _0222D962
_0222D940:
	mov r1, #0
	str r1, [r0, #4]
	b _0222D96A
_0222D946:
	sub r2, #0x19
	str r2, [r0, #4]
	b _0222D96A
_0222D94C:
	sub r2, #0x1b
	str r2, [r0, #4]
	b _0222D96A
_0222D952:
	sub r2, #0x1a
	str r2, [r0, #4]
	b _0222D96A
_0222D958:
	mov r1, #1
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D96A
_0222D962:
	mov r1, #0xc
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222D96A:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D970:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D97E
	cmp r0, #7
	beq _0222D996
	pop {r3, pc}
_0222D97E:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222DB8C ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222D996:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212480
	mov r1, #0x49
	lsl r1, r1, #2
	cmp r0, r1
	blo _0222D9BA
	bl MOD79_02212480
	mov r1, #0x49
	lsl r1, r1, #2
	bl _u32_div_f
	ldr r1, _0222DB8C ; =0x02237CE0
	str r0, [r1, #4]
	b _0222D9E2
_0222D9BA:
	cmp r0, #0
	bne _0222D9C6
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0
	str r1, [r0, #4]
	b _0222D9E2
_0222D9C6:
	ldr r0, _0222DB94 ; =0x02237DE0
	ldr r0, [r0, #0x40]
	ldrb r0, [r0]
	cmp r0, #0xe
	bne _0222D9DA
	mov r1, #1
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222D9E2
_0222D9DA:
	mov r1, #0xc
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222D9E2:
	bl MOD56_0221244C
	pop {r3, pc}
_0222D9E8:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222D9F6
	cmp r0, #7
	beq _0222DA0E
	pop {r3, pc}
_0222D9F6:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222DB8C ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222DA0E:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212480
	mov r1, #0x49
	lsl r1, r1, #2
	cmp r0, r1
	bne _0222DA28
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0
	str r1, [r0, #4]
	b _0222DAB4
_0222DA28:
	ldr r0, _0222DB94 ; =0x02237DE0
	ldr r0, [r0, #0x40]
	ldrb r0, [r0]
	cmp r0, #0xe
	bhi _0222DAAC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222DA3E: ; jump table
	.short _0222DAAC - _0222DA3E - 2 ; case 0
	.short _0222DAAC - _0222DA3E - 2 ; case 1
	.short _0222DA5C - _0222DA3E - 2 ; case 2
	.short _0222DAAC - _0222DA3E - 2 ; case 3
	.short _0222DAAC - _0222DA3E - 2 ; case 4
	.short _0222DAAC - _0222DA3E - 2 ; case 5
	.short _0222DAAC - _0222DA3E - 2 ; case 6
	.short _0222DAAC - _0222DA3E - 2 ; case 7
	.short _0222DA7A - _0222DA3E - 2 ; case 8
	.short _0222DA84 - _0222DA3E - 2 ; case 9
	.short _0222DA8E - _0222DA3E - 2 ; case 10
	.short _0222DA98 - _0222DA3E - 2 ; case 11
	.short _0222DA66 - _0222DA3E - 2 ; case 12
	.short _0222DA70 - _0222DA3E - 2 ; case 13
	.short _0222DAA2 - _0222DA3E - 2 ; case 14
_0222DA5C:
	mov r1, #4
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DA66:
	mov r1, #5
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DA70:
	mov r1, #6
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DA7A:
	mov r1, #7
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DA84:
	mov r1, #8
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DA8E:
	mov r1, #9
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DA98:
	mov r1, #0xa
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DAA2:
	mov r1, #1
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
	b _0222DAB4
_0222DAAC:
	mov r1, #0xc
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222DAB4:
	bl MOD56_0221244C
	pop {r3, pc}
_0222DABA:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222DAC8
	cmp r0, #7
	beq _0222DAE0
	pop {r3, pc}
_0222DAC8:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222DB8C ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222DAE0:
	ldr r1, _0222DB8C ; =0x02237CE0
	mov r2, #0x16
	ldr r0, _0222DB90 ; =0x02237E00
	str r2, [r1]
	ldrb r0, [r0, #0x1c]
	cmp r0, #1
	beq _0222DAF8
	cmp r0, #2
	beq _0222DB04
	cmp r0, #0xe
	beq _0222DAFE
	b _0222DB08
_0222DAF8:
	mov r0, #0
	str r0, [r1, #4]
	b _0222DB08
_0222DAFE:
	sub r2, #0x18
	str r2, [r1, #4]
	b _0222DB08
_0222DB04:
	sub r2, #0x1b
	str r2, [r1, #4]
_0222DB08:
	bl MOD56_0221244C
	pop {r3, pc}
_0222DB0E:
	bl MOD79_022123A8
	cmp r0, #1
	beq _0222DB1C
	cmp r0, #7
	beq _0222DB34
	pop {r3, pc}
_0222DB1C:
	ldr r0, _0222DB8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	bl MOD79_02212474
	bl MOD80_0222DF38
	ldr r1, _0222DB8C ; =0x02237CE0
	str r0, [r1, #4]
	bl MOD56_0221244C
	pop {r3, pc}
_0222DB34:
	ldr r1, _0222DB8C ; =0x02237CE0
	mov r2, #0x16
	ldr r0, _0222DB90 ; =0x02237E00
	str r2, [r1]
	ldrb r0, [r0, #0x1c]
	cmp r0, #7
	bgt _0222DB52
	cmp r0, #1
	blt _0222DB70
	beq _0222DB58
	cmp r0, #6
	beq _0222DB5E
	cmp r0, #7
	beq _0222DB64
	b _0222DB70
_0222DB52:
	cmp r0, #0xe
	beq _0222DB6A
	b _0222DB70
_0222DB58:
	mov r0, #0
	str r0, [r1, #4]
	b _0222DB78
_0222DB5E:
	mov r0, #1
	str r0, [r1, #4]
	b _0222DB78
_0222DB64:
	mov r0, #2
	str r0, [r1, #4]
	b _0222DB78
_0222DB6A:
	sub r2, #0x18
	str r2, [r1, #4]
	b _0222DB78
_0222DB70:
	mov r1, #0xc
	ldr r0, _0222DB8C ; =0x02237CE0
	mvn r1, r1
	str r1, [r0, #4]
_0222DB78:
	bl MOD56_0221244C
	pop {r3, pc}
_0222DB7E:
	mov r0, #0x16
	str r0, [r1]
	sub r0, #0x22
	str r0, [r1, #4]
	bl MOD56_0221244C
_0222DB8A:
	pop {r3, pc}
	.align 2, 0
_0222DB8C: .word MOD80_02237CE0
_0222DB90: .word MOD80_02237E00
_0222DB94: .word MOD80_02237DE0
	thumb_func_end MOD80_0222D5DC

	thumb_func_start MOD80_0222DB98
MOD80_0222DB98: ; 0x0222DB98
	ldr r1, _0222DBB4 ; =0x02237CE0
	ldr r0, [r1]
	cmp r0, #1
	beq _0222DBA6
	cmp r0, #0x16
	beq _0222DBAA
	b _0222DBB0
_0222DBA6:
	mov r0, #1
	bx lr
_0222DBAA:
	mov r0, #1
	str r0, [r1]
	bx lr
_0222DBB0:
	mov r0, #0
	bx lr
	.align 2, 0
_0222DBB4: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DB98

	thumb_func_start MOD80_0222DBB8
MOD80_0222DBB8: ; 0x0222DBB8
	ldr r0, _0222DBC0 ; =0x02237CE0
	ldr r0, [r0, #4]
	bx lr
	nop
_0222DBC0: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DBB8

	thumb_func_start MOD80_0222DBC4
MOD80_0222DBC4: ; 0x0222DBC4
	push {r3, lr}
	add r1, r0, #0
	mov r2, #0x49
	ldr r0, _0222DC04 ; =0x02237CF4
	lsl r2, r2, #2
	bl memcpy
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	mov r2, #0x49
	ldr r0, _0222DC08 ; =0x02237680
	ldr r1, _0222DC04 ; =0x02237CF4
	ldr r3, _0222DC0C ; =0x02237E1C
	lsl r2, r2, #2
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DBF4
	ldr r0, _0222DC10 ; =0x02237CE0
	mov r1, #2
	str r1, [r0]
	pop {r3, pc}
_0222DBF4:
	ldr r0, _0222DC10 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	.align 2, 0
_0222DC04: .word MOD80_02237CF4
_0222DC08: .word MOD80_02237680
_0222DC0C: .word MOD80_02237E1C
_0222DC10: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DBC4

	thumb_func_start MOD80_0222DC14
MOD80_0222DC14: ; 0x0222DC14
	push {r3, lr}
	ldr r0, _0222DC54 ; =0x02237CEC
	ldr r2, _0222DC58 ; =0x02237CF4
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [r2]
	str r0, [r2, #4]
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222DC5C ; =0x022376CC
	ldr r1, _0222DC58 ; =0x02237CF4
	ldr r3, _0222DC60 ; =0x02237E1C
	mov r2, #8
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DC42
	ldr r0, _0222DC64 ; =0x02237CE0
	mov r1, #4
	str r1, [r0]
	pop {r3, pc}
_0222DC42:
	ldr r0, _0222DC64 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	nop
_0222DC54: .word MOD80_02237CEC
_0222DC58: .word MOD80_02237CF4
_0222DC5C: .word MOD80_022376CC
_0222DC60: .word MOD80_02237E1C
_0222DC64: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DC14

	thumb_func_start MOD80_0222DC68
MOD80_0222DC68: ; 0x0222DC68
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _0222DCA8 ; =0x02237DE0
	str r4, [r0, #0x40]
	bl MOD79_022122E4
	mov r0, #0x49
	lsl r0, r0, #2
	str r0, [sp]
	ldr r0, _0222DCAC ; =0x0223771C
	ldr r1, _0222DCB0 ; =0x02237CF4
	mov r2, #0
	add r3, r4, #0
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DC96
	ldr r0, _0222DCB4 ; =0x02237CE0
	mov r1, #6
	str r1, [r0]
	add sp, #4
	pop {r3, r4, pc}
_0222DC96:
	ldr r0, _0222DCB4 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222DCA8: .word MOD80_02237DE0
_0222DCAC: .word MOD80_0223771C
_0222DCB0: .word MOD80_02237CF4
_0222DCB4: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DC68

	thumb_func_start MOD80_0222DCB8
MOD80_0222DCB8: ; 0x0222DCB8
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _0222DCF8 ; =0x02237DE0
	str r4, [r0, #0x40]
	bl MOD79_022122E4
	mov r0, #0x49
	lsl r0, r0, #2
	str r0, [sp]
	ldr r0, _0222DCFC ; =0x02237764
	ldr r1, _0222DD00 ; =0x02237CF4
	mov r2, #0
	add r3, r4, #0
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DCE6
	ldr r0, _0222DD04 ; =0x02237CE0
	mov r1, #8
	str r1, [r0]
	add sp, #4
	pop {r3, r4, pc}
_0222DCE6:
	ldr r0, _0222DD04 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222DCF8: .word MOD80_02237DE0
_0222DCFC: .word MOD80_02237764
_0222DD00: .word MOD80_02237CF4
_0222DD04: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DCB8

	thumb_func_start MOD80_0222DD08
MOD80_0222DD08: ; 0x0222DD08
	push {r3, lr}
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222DD3C ; =0x022377B0
	ldr r1, _0222DD40 ; =0x02237CF4
	ldr r3, _0222DD44 ; =0x02237E1C
	mov r2, #0
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DD2A
	ldr r0, _0222DD48 ; =0x02237CE0
	mov r1, #0xa
	str r1, [r0]
	pop {r3, pc}
_0222DD2A:
	ldr r0, _0222DD48 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	nop
_0222DD3C: .word MOD80_022377B0
_0222DD40: .word MOD80_02237CF4
_0222DD44: .word MOD80_02237E1C
_0222DD48: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DD08

	thumb_func_start MOD80_0222DD4C
MOD80_0222DD4C: ; 0x0222DD4C
	push {r3, lr}
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222DD80 ; =0x022377FC
	ldr r1, _0222DD84 ; =0x02237CF4
	ldr r3, _0222DD88 ; =0x02237E1C
	mov r2, #0
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DD6E
	ldr r0, _0222DD8C ; =0x02237CE0
	mov r1, #0xc
	str r1, [r0]
	pop {r3, pc}
_0222DD6E:
	ldr r0, _0222DD8C ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	nop
_0222DD80: .word MOD80_022377FC
_0222DD84: .word MOD80_02237CF4
_0222DD88: .word MOD80_02237E1C
_0222DD8C: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DD4C

	thumb_func_start MOD80_0222DD90
MOD80_0222DD90: ; 0x0222DD90
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, _0222DDF4 ; =0x02237DE0
	add r6, r2, #0
	str r6, [r0, #0x40]
	add r4, r1, #0
	bl MOD79_022122E4
	ldrb r0, [r5]
	ldr r1, _0222DDF8 ; =0x02237CF4
	mov r2, #7
	strb r0, [r1]
	ldrb r0, [r5, #1]
	add r3, r6, #0
	strb r0, [r1, #1]
	ldrb r0, [r5, #2]
	strb r0, [r1, #2]
	ldrb r0, [r5, #3]
	strb r0, [r1, #3]
	ldrb r0, [r5, #4]
	strb r0, [r1, #4]
	ldrb r0, [r5, #5]
	strb r0, [r1, #5]
	ldr r0, _0222DDFC ; =0x02237CE0
	strb r4, [r0, #0x1a]
	mov r0, #0x49
	lsl r0, r0, #2
	mul r0, r4
	str r0, [sp]
	ldr r0, _0222DE00 ; =0x02237848
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DDE0
	ldr r0, _0222DDFC ; =0x02237CE0
	mov r1, #0xe
	str r1, [r0]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0222DDE0:
	ldr r0, _0222DDFC ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0222DDF4: .word MOD80_02237DE0
_0222DDF8: .word MOD80_02237CF4
_0222DDFC: .word MOD80_02237CE0
_0222DE00: .word MOD80_02237848
	thumb_func_end MOD80_0222DD90

	thumb_func_start MOD80_0222DE04
MOD80_0222DE04: ; 0x0222DE04
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, _0222DE58 ; =0x02237DE0
	add r6, r2, #0
	add r4, r1, #0
	str r6, [r0, #0x40]
	bl MOD79_022122E4
	mov r2, #0x49
	ldr r0, _0222DE5C ; =0x02237CF4
	add r1, r4, #0
	lsl r2, r2, #2
	bl memcpy
	ldr r0, _0222DE58 ; =0x02237DE0
	mov r2, #0x49
	str r5, [r0, #0x38]
	lsl r2, r2, #2
	str r2, [sp]
	ldr r0, _0222DE60 ; =0x02237894
	ldr r1, _0222DE5C ; =0x02237CF4
	add r2, r2, #4
	add r3, r6, #0
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DE46
	ldr r0, _0222DE64 ; =0x02237CE0
	mov r1, #0x10
	str r1, [r0]
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0222DE46:
	ldr r0, _0222DE64 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222DE58: .word MOD80_02237DE0
_0222DE5C: .word MOD80_02237CF4
_0222DE60: .word MOD80_02237894
_0222DE64: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DE04

	thumb_func_start MOD80_0222DE68
MOD80_0222DE68: ; 0x0222DE68
	push {r3, lr}
	ldr r0, _0222DEA8 ; =0x02237CEC
	ldr r2, _0222DEAC ; =0x02237CF4
	ldr r1, [r0]
	ldr r0, [r0, #4]
	str r1, [r2]
	str r0, [r2, #4]
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222DEB0 ; =0x022378E4
	ldr r1, _0222DEAC ; =0x02237CF4
	ldr r3, _0222DEB4 ; =0x02237E1C
	mov r2, #8
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DE96
	ldr r0, _0222DEB8 ; =0x02237CE0
	mov r1, #0x12
	str r1, [r0]
	pop {r3, pc}
_0222DE96:
	ldr r0, _0222DEB8 ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	nop
_0222DEA8: .word MOD80_02237CEC
_0222DEAC: .word MOD80_02237CF4
_0222DEB0: .word MOD80_022378E4
_0222DEB4: .word MOD80_02237E1C
_0222DEB8: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DE68

	thumb_func_start MOD80_0222DEBC
MOD80_0222DEBC: ; 0x0222DEBC
	push {r3, lr}
	bl MOD79_022122E4
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222DEF0 ; =0x02237938
	ldr r1, _0222DEF4 ; =0x02237CF4
	ldr r3, _0222DEF8 ; =0x02237E1C
	mov r2, #0
	bl MOD80_0222DF00
	cmp r0, #0
	beq _0222DEDE
	ldr r0, _0222DEFC ; =0x02237CE0
	mov r1, #0x14
	str r1, [r0]
	pop {r3, pc}
_0222DEDE:
	ldr r0, _0222DEFC ; =0x02237CE0
	mov r1, #0x16
	str r1, [r0]
	sub r1, #0x23
	str r1, [r0, #4]
	bl MOD56_0221244C
	pop {r3, pc}
	nop
_0222DEF0: .word MOD80_02237938
_0222DEF4: .word MOD80_02237CF4
_0222DEF8: .word MOD80_02237E1C
_0222DEFC: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DEBC

	thumb_func_start MOD80_0222DF00
MOD80_0222DF00: ; 0x0222DF00
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r1, #0
	ldr r1, [sp, #0x18]
	str r3, [sp]
	str r1, [sp, #4]
	add r4, r2, #0
	ldr r1, _0222DF34 ; =0x02237CE0
	add r2, r5, #0
	ldr r1, [r1, #8]
	add r3, r4, #0
	bl MOD79_02212308
	cmp r0, #0
	beq _0222DF26
	cmp r0, #1
	beq _0222DF2C
	cmp r0, #2
	b _0222DF2C
_0222DF26:
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, pc}
_0222DF2C:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_0222DF34: .word MOD80_02237CE0
	thumb_func_end MOD80_0222DF00

	thumb_func_start MOD80_0222DF38
MOD80_0222DF38: ; 0x0222DF38
	push {r4, lr}
	cmp r0, #0x20
	bhi _0222DFB0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222DF4A: ; jump table
	.short _0222DF8C - _0222DF4A - 2 ; case 0
	.short _0222DF8C - _0222DF4A - 2 ; case 1
	.short _0222DF92 - _0222DF4A - 2 ; case 2
	.short _0222DF8C - _0222DF4A - 2 ; case 3
	.short _0222DF8C - _0222DF4A - 2 ; case 4
	.short _0222DF8C - _0222DF4A - 2 ; case 5
	.short _0222DF8C - _0222DF4A - 2 ; case 6
	.short _0222DFB0 - _0222DF4A - 2 ; case 7
	.short _0222DF92 - _0222DF4A - 2 ; case 8
	.short _0222DF8C - _0222DF4A - 2 ; case 9
	.short _0222DF8C - _0222DF4A - 2 ; case 10
	.short _0222DF98 - _0222DF4A - 2 ; case 11
	.short _0222DF9E - _0222DF4A - 2 ; case 12
	.short _0222DF9E - _0222DF4A - 2 ; case 13
	.short _0222DF8C - _0222DF4A - 2 ; case 14
	.short _0222DFAA - _0222DF4A - 2 ; case 15
	.short _0222DFA4 - _0222DF4A - 2 ; case 16
	.short _0222DFA4 - _0222DF4A - 2 ; case 17
	.short _0222DFA4 - _0222DF4A - 2 ; case 18
	.short _0222DFA4 - _0222DF4A - 2 ; case 19
	.short _0222DF8C - _0222DF4A - 2 ; case 20
	.short _0222DF8C - _0222DF4A - 2 ; case 21
	.short _0222DF8C - _0222DF4A - 2 ; case 22
	.short _0222DF8C - _0222DF4A - 2 ; case 23
	.short _0222DFB0 - _0222DF4A - 2 ; case 24
	.short _0222DF92 - _0222DF4A - 2 ; case 25
	.short _0222DFA4 - _0222DF4A - 2 ; case 26
	.short _0222DFA4 - _0222DF4A - 2 ; case 27
	.short _0222DFA4 - _0222DF4A - 2 ; case 28
	.short _0222DFA4 - _0222DF4A - 2 ; case 29
	.short _0222DFAA - _0222DF4A - 2 ; case 30
	.short _0222DFA4 - _0222DF4A - 2 ; case 31
	.short _0222DF8C - _0222DF4A - 2 ; case 32
_0222DF8C:
	mov r4, #0xc
	mvn r4, r4
	b _0222DFB4
_0222DF92:
	mov r4, #0xc
	mvn r4, r4
	b _0222DFB4
_0222DF98:
	mov r4, #0xe
	mvn r4, r4
	b _0222DFB4
_0222DF9E:
	mov r4, #0xe
	mvn r4, r4
	b _0222DFB4
_0222DFA4:
	mov r4, #1
	mvn r4, r4
	b _0222DFB4
_0222DFAA:
	mov r4, #1
	mvn r4, r4
	b _0222DFB4
_0222DFB0:
	mov r4, #0xc
	mvn r4, r4
_0222DFB4:
	mov r0, #0xc
	mvn r0, r0
	cmp r4, r0
	beq _0222DFCC
	bl WCM_GetPhase
	cmp r0, #9
	beq _0222DFC8
	mov r4, #0xd
	mvn r4, r4
_0222DFC8:
	bl MOD04_021DD6F0
_0222DFCC:
	add r0, r4, #0
	pop {r4, pc}
	thumb_func_end MOD80_0222DF38

	thumb_func_start MOD80_0222DFD0
MOD80_0222DFD0: ; 0x0222DFD0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	cmp r0, #0
	beq _0222DFE4
	cmp r0, #1
	beq _0222E0E2
	b _0222E0F8
_0222DFE4:
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	bl FUN_02015F1C
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _0222E100 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2]
	ldr r2, _0222E104 ; =0x04001000
	ldr r1, [r2]
	and r0, r1
	str r0, [r2]
	mov r2, #7
	mov r0, #3
	mov r1, #0x3e
	lsl r2, r2, #0x10
	bl FUN_0201681C
	ldr r1, _0222E108 ; =0x00001044
	add r0, r6, #0
	mov r2, #0x3e
	bl OverlayManager_CreateAndGetData
	ldr r2, _0222E108 ; =0x00001044
	mov r1, #0
	add r4, r0, #0
	bl memset
	mov r0, #0x3e
	bl FUN_02016B94
	str r0, [r4, #4]
	ldr r0, _0222E10C ; =0x02237E24
	add r2, sp, #0
	ldr r3, _0222E110 ; =0x02236E50
	str r4, [r0, #4]
	add r7, r2, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r7, #0
	bl FUN_02016BBC
	mov r0, #0xb
	mov r1, #0x40
	mov r2, #0x3e
	bl ScrStrBufs_new_custom
	mov r1, #0xb3
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r2, _0222E114 ; =0x0000024F
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x3e
	bl NewMsgDataFromNarc
	ldr r1, _0222E118 ; =0x00000B34
	mov r2, #0x25
	str r0, [r4, r1]
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #4
	mov r3, #0x3e
	bl NewMsgDataFromNarc
	ldr r1, _0222E11C ; =0x00000B3C
	ldr r2, _0222E120 ; =0x00000265
	str r0, [r4, r1]
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x3e
	bl NewMsgDataFromNarc
	mov r1, #0x2d
	lsl r1, r1, #6
	str r0, [r4, r1]
	ldr r2, _0222E124 ; =0x0000016A
	mov r0, #0
	mov r1, #0x1a
	mov r3, #0x3e
	bl NewMsgDataFromNarc
	ldr r1, _0222E128 ; =0x00000B38
	str r0, [r4, r1]
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	add r0, r4, #0
	add r1, r6, #0
	bl MOD80_0222E338
	add r0, r4, #0
	bl MOD80_0222E7C8
	ldr r1, _0222E12C ; =0x00000449
	mov r0, #4
	mov r2, #1
	bl FUN_0200433C
	ldr r1, _0222E130 ; =0x00020020
	mov r0, #0x3e
	bl AllocFromHeap
	str r0, [r4, #0x48]
	add r0, #0x1f
	mov r1, #0x1f
	bic r0, r1
	mov r1, #2
	lsl r1, r1, #0x10
	mov r2, #0
	bl tempName_NNS_FndCreateExpHeapEx
	str r0, [r4, #0x4c]
	mov r0, #1
	str r0, [r5]
	b _0222E0F8
_0222E0E2:
	bl FUN_02088858
	bl FUN_020888BC
	bl FUN_0202E49C
	mov r0, #0
	str r0, [r5]
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0222E0F8:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E100: .word 0xFFFFE0FF
_0222E104: .word 0x04001000
_0222E108: .word 0x00001044
_0222E10C: .word MOD80_02237E24
_0222E110: .word MOD80_02236E50
_0222E114: .word 0x0000024F
_0222E118: .word 0x00000B34
_0222E11C: .word 0x00000B3C
_0222E120: .word 0x00000265
_0222E124: .word 0x0000016A
_0222E128: .word 0x00000B38
_0222E12C: .word 0x00000449
_0222E130: .word 0x00020020
	thumb_func_end MOD80_0222DFD0

	thumb_func_start MOD80_0222E134
MOD80_0222E134: ; 0x0222E134
	push {r4, r5, r6, lr}
	add r5, r1, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	bl MOD04_021DD984
	bl MOD80_0222D5DC
	ldr r1, [r5]
	cmp r1, #5
	bhi _0222E224
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0222E158: ; jump table
	.short _0222E164 - _0222E158 - 2 ; case 0
	.short _0222E180 - _0222E158 - 2 ; case 1
	.short _0222E1A4 - _0222E158 - 2 ; case 2
	.short _0222E1B2 - _0222E158 - 2 ; case 3
	.short _0222E1C6 - _0222E158 - 2 ; case 4
	.short _0222E220 - _0222E158 - 2 ; case 5
_0222E164:
	bl FUN_0202E4C8
	cmp r0, #0
	beq _0222E224
	ldr r1, [r4, #0x4c]
	ldr r0, _0222E240 ; =0x02237E24
	str r1, [r0]
	ldr r0, _0222E244 ; =MOD80_0222E750
	ldr r1, _0222E248 ; =MOD80_0222E778
	bl MOD04_021DD968
	mov r0, #1
	str r0, [r5]
	b _0222E224
_0222E180:
	ldr r3, [r4, #0x14]
	mov r2, #0xc
	add r6, r3, #0
	mul r6, r2
	ldr r2, _0222E24C ; =0x02237984
	add r0, r4, #0
	ldr r2, [r2, r6]
	blx r2
	str r0, [r5]
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _0222E224
	add r0, r4, #0
	bl MOD80_0222E7F0
	b _0222E224
_0222E1A4:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222E224
	mov r0, #3
	str r0, [r5]
	b _0222E224
_0222E1B2:
	ldr r3, [r4, #0x14]
	mov r2, #0xc
	add r6, r3, #0
	mul r6, r2
	ldr r2, _0222E250 ; =0x02237988
	add r0, r4, #0
	ldr r2, [r2, r6]
	blx r2
	str r0, [r5]
	b _0222E224
_0222E1C6:
	bl FUN_0200E308
	cmp r0, #0
	beq _0222E224
	add r0, r4, #0
	add r0, #0xac
	ldr r0, [r0]
	cmp r0, #0
	beq _0222E20A
	add r0, r4, #0
	bl MOD80_0222E7C8
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0
	add r0, r4, #0
	bl MOD80_02235850
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r0, r4, #0
	mov r2, #0
	bl MOD80_02235B90
	add r0, r4, #0
	bl MOD80_0222F338
	add r0, r4, #0
	mov r1, #0
	add r0, #0xac
	str r1, [r0]
_0222E20A:
	ldr r3, [r4, #0x14]
	mov r2, #0xc
	add r6, r3, #0
	mul r6, r2
	ldr r2, _0222E254 ; =0x0223798C
	ldr r1, [r5]
	ldr r2, [r2, r6]
	add r0, r4, #0
	blx r2
	str r0, [r5]
	b _0222E224
_0222E220:
	mov r0, #1
	pop {r4, r5, r6, pc}
_0222E224:
	add r0, r4, #0
	bl MOD80_0222E85C
	add r0, r4, #0
	bl MOD80_0222E87C
	ldr r0, _0222E258 ; =0x00000B84
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222E23C
	bl FUN_0201FDEC
_0222E23C:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E240: .word MOD80_02237E24
_0222E244: .word MOD80_0222E750
_0222E248: .word MOD80_0222E778
_0222E24C: .word MOD80_02237984
_0222E250: .word MOD80_02237988
_0222E254: .word MOD80_0223798C
_0222E258: .word 0x00000B84
	thumb_func_end MOD80_0222E134

	thumb_func_start MOD80_0222E25C
MOD80_0222E25C: ; 0x0222E25C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl OverlayManager_GetData
	add r4, r0, #0
	ldr r0, [r4, #0x48]
	bl FreeToHeap
	bl FUN_020888CC
	bl FUN_02088868
	add r0, r4, #0
	bl MOD80_0222E7F0
	ldr r0, _0222E2D4 ; =0x00000B38
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0x2d
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl DestroyMsgData
	ldr r0, _0222E2D8 ; =0x00000B3C
	ldr r0, [r4, r0]
	bl DestroyMsgData
	ldr r0, _0222E2DC ; =0x00000B34
	ldr r0, [r4, r0]
	bl DestroyMsgData
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl ScrStrBufs_delete
	add r0, r4, #0
	bl MOD80_0222E398
	bl FUN_0202E4F0
	ldr r0, [r4, #4]
	bl FreeToHeap
	ldr r0, [r4]
	bl FreeToHeap
	add r0, r5, #0
	bl OverlayManager_FreeData
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	mov r0, #0x3e
	bl FUN_020168D0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222E2D4: .word 0x00000B38
_0222E2D8: .word 0x00000B3C
_0222E2DC: .word 0x00000B34
	thumb_func_end MOD80_0222E25C

	thumb_func_start MOD80_0222E2E0
MOD80_0222E2E0: ; 0x0222E2E0
	push {r4, lr}
	ldr r1, _0222E30C ; =0x00001014
	add r4, r0, #0
	ldr r1, [r4, r1]
	cmp r1, #0
	beq _0222E2F4
	blx r1
	ldr r0, _0222E30C ; =0x00001014
	mov r1, #0
	str r1, [r4, r0]
_0222E2F4:
	bl FUN_0201C30C
	bl FUN_02009F80
	ldr r3, _0222E310 ; =0x027E0000
	ldr r1, _0222E314 ; =0x00003FF8
	mov r0, #1
	ldr r2, [r3, r1]
	orr r0, r2
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_0222E30C: .word 0x00001014
_0222E310: .word 0x027E0000
_0222E314: .word 0x00003FF8
	thumb_func_end MOD80_0222E2E0

	thumb_func_start MOD80_0222E318
MOD80_0222E318: ; 0x0222E318
	push {r4, lr}
	sub sp, #0x28
	ldr r4, _0222E334 ; =0x02236E70
	add r3, sp, #0
	mov r2, #5
_0222E322:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0222E322
	add r0, sp, #0
	bl FUN_0201E66C
	add sp, #0x28
	pop {r4, pc}
	.align 2, 0
_0222E334: .word MOD80_02236E70
	thumb_func_end MOD80_0222E318

	thumb_func_start MOD80_0222E338
MOD80_0222E338: ; 0x0222E338
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl OverlayManager_GetField18
	mov r1, #0
	str r0, [r4]
	add r0, r4, #0
	add r2, r1, #0
	str r1, [r4, #0x14]
	bl MOD80_0222E7A8
	add r1, r4, #0
	mov r0, #0
	add r1, #0xb4
	strh r0, [r1]
	ldr r1, _0222E390 ; =0x00000B22
	mov r3, #3
	strh r0, [r4, r1]
	add r2, r1, #2
	strb r3, [r4, r2]
	add r2, r1, #3
	strb r0, [r4, r2]
	add r2, r1, #4
	strb r0, [r4, r2]
	add r1, r1, #6
	strh r0, [r4, r1]
	ldr r2, _0222E394 ; =0x00000FEC
	add r1, r4, #0
	strh r0, [r4, r2]
	mov r3, #0x12
	add r1, #0xb8
	strh r3, [r1]
	add r1, r2, #0
	add r1, #0x1c
	strh r0, [r4, r1]
	add r1, r2, #0
	add r1, #0x1e
	strh r0, [r4, r1]
	add r1, r2, #2
	strh r0, [r4, r1]
	sub r2, #0x14
	str r0, [r4, r2]
	pop {r4, pc}
	.align 2, 0
_0222E390: .word 0x00000B22
_0222E394: .word 0x00000FEC
	thumb_func_end MOD80_0222E338

	thumb_func_start MOD80_0222E398
MOD80_0222E398: ; 0x0222E398
	bx lr
	.align 2, 0
	thumb_func_end MOD80_0222E398

	thumb_func_start MOD80_0222E39C
MOD80_0222E39C: ; 0x0222E39C
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _0222E3C8 ; =0x02236E60
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_0201D040
	mov r0, #0x14
	mov r1, #0x3e
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0222E3C8: .word MOD80_02236E60
	thumb_func_end MOD80_0222E39C

	thumb_func_start MOD80_0222E3CC
MOD80_0222E3CC: ; 0x0222E3CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r5, r0, #0
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7e
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x20
	str r3, [sp, #0xc]
	mov r2, #0x3e
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	ldr r1, _0222E5C8 ; =0x00000B88
	mov r0, #0x4e
	add r1, r5, r1
	mov r2, #0x3e
	bl FUN_02008C9C
	ldr r1, _0222E5CC ; =0x00000B84
	mov r2, #1
	str r0, [r5, r1]
	add r0, r1, #4
	add r0, r5, r0
	mov r1, #0
	lsl r2, r2, #0x14
	bl FUN_02008D24
	mov r7, #0xcb
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #4
_0222E414:
	mov r0, #3
	add r1, r6, #0
	mov r2, #0x3e
	bl FUN_02008DEC
	str r0, [r4, r7]
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _0222E414
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0xcb
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0x68
	mov r2, #0x12
	bl FUN_02008F34
	mov r1, #0x33
	lsl r1, r1, #6
	str r0, [r5, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0x3e
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r2, #9
	bl FUN_02008FEC
	ldr r1, _0222E5D0 ; =0x00000CC4
	mov r2, #0x13
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x3e
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r3, #1
	bl FUN_020090AC
	ldr r1, _0222E5D4 ; =0x00000CC8
	mov r2, #0x14
	str r0, [r5, r1]
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x3e
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r3, #1
	bl FUN_020090AC
	ldr r1, _0222E5D8 ; =0x00000CCC
	mov r3, #1
	str r0, [r5, r1]
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x3e
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r2, #0x20
	bl FUN_02008F34
	mov r1, #0xcd
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #1
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #9
	str r0, [sp, #8]
	mov r0, #0x3e
	sub r1, #0x1c
	str r0, [sp, #0xc]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r2, #8
	mov r3, #0
	bl FUN_02008FEC
	ldr r1, _0222E5DC ; =0x00000CD4
	mov r3, #1
	str r0, [r5, r1]
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x3e
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r2, #0x21
	bl FUN_020090AC
	ldr r1, _0222E5E0 ; =0x00000CD8
	mov r3, #1
	str r0, [r5, r1]
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x3e
	sub r1, #0x1c
	str r0, [sp, #8]
	ldr r0, [r5, r1]
	mov r1, #0x68
	mov r2, #0x22
	bl FUN_020090AC
	ldr r1, _0222E5E4 ; =0x00000CDC
	str r0, [r5, r1]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	bl FUN_02009A50
	mov r0, #0xcd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02009A50
	ldr r0, _0222E5D0 ; =0x00000CC4
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	ldr r0, _0222E5DC ; =0x00000CD4
	ldr r0, [r5, r0]
	bl FUN_02009CF0
	bl FUN_0206B888
	add r1, r0, #0
	mov r0, #0x13
	add r2, sp, #0x18
	mov r3, #0x3e
	bl FUN_02006C08
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x18]
	mov r1, #0x60
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [sp, #0x18]
	mov r1, #0x60
	ldr r0, [r0, #0xc]
	add r2, r1, #0
	bl GX_LoadOBJPltt
	ldr r0, [sp, #0x18]
	mov r7, #0x1f
	ldr r4, [r0, #0xc]
	mov r3, #0
	add r5, r7, #0
_0222E570:
	ldrh r2, [r4]
	mov r0, #0x1f
	add r3, r3, #1
	add r1, r2, #0
	and r1, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r1, r0, #1
	asr r0, r2, #0xa
	add r6, r0, #0
	and r6, r7
	lsr r0, r6, #0x1f
	add r0, r6, r0
	asr r2, r2, #5
	add r6, r2, #0
	and r6, r5
	lsr r2, r6, #0x1f
	add r2, r6, r2
	asr r0, r0, #1
	asr r2, r2, #1
	lsl r0, r0, #0xa
	lsl r2, r2, #5
	orr r0, r2
	orr r0, r1
	strh r0, [r4]
	add r4, r4, #2
	cmp r3, #0x30
	blt _0222E570
	ldr r0, [sp, #0x18]
	mov r1, #0x60
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [sp, #0x18]
	mov r1, #0xc0
	ldr r0, [r0, #0xc]
	mov r2, #0x60
	bl GX_LoadOBJPltt
	ldr r0, [sp, #0x14]
	bl FreeToHeap
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222E5C8: .word 0x00000B88
_0222E5CC: .word 0x00000B84
_0222E5D0: .word 0x00000CC4
_0222E5D4: .word 0x00000CC8
_0222E5D8: .word 0x00000CCC
_0222E5DC: .word 0x00000CD4
_0222E5E0: .word 0x00000CD8
_0222E5E4: .word 0x00000CDC
	thumb_func_end MOD80_0222E3CC

	thumb_func_start MOD80_0222E5E8
MOD80_0222E5E8: ; 0x0222E5E8
	push {r3, r4}
	ldr r4, _0222E610 ; =0x00000B84
	ldr r1, [r1, r4]
	str r1, [r0]
	str r2, [r0, #4]
	mov r2, #0
	mov r1, #1
	str r2, [r0, #0x10]
	lsl r1, r1, #0xc
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	strh r2, [r0, #0x20]
	mov r1, #1
	str r1, [r0, #0x24]
	str r3, [r0, #0x28]
	mov r1, #0x3e
	str r1, [r0, #0x2c]
	pop {r3, r4}
	bx lr
	.align 2, 0
_0222E610: .word 0x00000B84
	thumb_func_end MOD80_0222E5E8

	thumb_func_start MOD80_0222E614
MOD80_0222E614: ; 0x0222E614
	push {r3, r4, lr}
	sub sp, #0x2c
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	sub r0, r1, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r2, #0xcb
	str r1, [sp, #0x10]
	lsl r2, r2, #4
	ldr r0, [r4, r2]
	add r3, r1, #0
	str r0, [sp, #0x14]
	add r0, r2, #4
	ldr r0, [r4, r0]
	str r0, [sp, #0x18]
	add r0, r2, #0
	add r0, #8
	ldr r0, [r4, r0]
	str r0, [sp, #0x1c]
	add r0, r2, #0
	add r0, #0xc
	ldr r0, [r4, r0]
	add r2, #0x40
	str r0, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r4, r2
	add r2, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	mov r1, #1
	mov r3, #0xcb
	str r1, [sp]
	sub r0, r1, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #4
	ldr r2, [r4, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r4, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r4, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r4, r2]
	add r3, #0x64
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r4, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x2c
	pop {r3, r4, pc}
	thumb_func_end MOD80_0222E614

	thumb_func_start MOD80_0222E6A8
MOD80_0222E6A8: ; 0x0222E6A8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	ldr r5, _0222E6D8 ; =0x02236E48
	add r4, sp, #4
	ldrh r6, [r5]
	add r3, sp, #4
	strh r6, [r4]
	ldrh r6, [r5, #2]
	strh r6, [r4, #2]
	ldrh r6, [r5, #4]
	ldrh r5, [r5, #6]
	strh r6, [r4, #4]
	strh r5, [r4, #6]
	strb r1, [r4, #2]
	strh r2, [r4, #6]
	mov r1, #0x3e
	str r1, [sp]
	add r1, r3, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_02002198
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222E6D8: .word MOD80_02236E48
	thumb_func_end MOD80_0222E6A8

	thumb_func_start MOD80_0222E6DC
MOD80_0222E6DC: ; 0x0222E6DC
	str r1, [r0, #0x2c]
	str r2, [r0, #0x30]
	bx lr
	.align 2, 0
	thumb_func_end MOD80_0222E6DC

	thumb_func_start MOD80_0222E6E4
MOD80_0222E6E4: ; 0x0222E6E4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r5, r2, #0
	cmp r1, #0
	ble _0222E702
	lsl r0, r1, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0222E710
_0222E702:
	lsl r0, r1, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0222E710:
	bl _ffix
	str r0, [sp]
	cmp r5, #0
	ble _0222E72C
	lsl r0, r5, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _0222E73A
_0222E72C:
	lsl r0, r5, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_0222E73A:
	bl _ffix
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD80_0222E6E4

	thumb_func_start MOD80_0222E750
MOD80_0222E750: ; 0x0222E750
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl OS_DisableInterrupts
	add r6, r0, #0
	ldr r0, _0222E774 ; =0x02237E24
	add r1, r5, #0
	ldr r0, [r0]
	add r2, r4, #0
	bl tempName_NNS_FndAllocFromExpHeapEx
	add r4, r0, #0
	add r0, r6, #0
	bl OS_RestoreInterrupts
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0222E774: .word MOD80_02237E24
	thumb_func_end MOD80_0222E750

	thumb_func_start MOD80_0222E778
MOD80_0222E778: ; 0x0222E778
	push {r3, r4, r5, lr}
	add r5, r1, #0
	beq _0222E794
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0222E798 ; =0x02237E24
	add r1, r5, #0
	ldr r0, [r0]
	bl FUN_020ADDF0
	add r0, r4, #0
	bl OS_RestoreInterrupts
_0222E794:
	pop {r3, r4, r5, pc}
	nop
_0222E798: .word MOD80_02237E24
	thumb_func_end MOD80_0222E778

	thumb_func_start MOD80_0222E79C
MOD80_0222E79C: ; 0x0222E79C
	push {r3, lr}
	bl MOD04_021DDB08
	mov r1, #3
	sub r0, r1, r0
	pop {r3, pc}
	thumb_func_end MOD80_0222E79C

	thumb_func_start MOD80_0222E7A8
MOD80_0222E7A8: ; 0x0222E7A8
	str r1, [r0, #0x18]
	str r2, [r0, #0x24]
	bx lr
	.align 2, 0
	thumb_func_end MOD80_0222E7A8

	thumb_func_start MOD80_0222E7B0
MOD80_0222E7B0: ; 0x0222E7B0
	ldr r1, [r0, #0x14]
	str r1, [r0, #0x20]
	ldr r1, [r0, #0x18]
	str r1, [r0, #0x14]
	bx lr
	.align 2, 0
	thumb_func_end MOD80_0222E7B0

	thumb_func_start MOD80_0222E7BC
MOD80_0222E7BC: ; 0x0222E7BC
	ldr r0, [r0]
	ldr r3, _0222E7C4 ; =FUN_02024FF4
	ldr r0, [r0, #0x24]
	bx r3
	.align 2, 0
_0222E7C4: .word FUN_02024FF4
	thumb_func_end MOD80_0222E7BC

	thumb_func_start MOD80_0222E7C8
MOD80_0222E7C8: ; 0x0222E7C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222E318
	bl MOD80_0222E39C
	add r0, r4, #0
	bl MOD80_0222E3CC
	add r0, r4, #0
	bl MOD80_0222E614
	ldr r0, _0222E7EC ; =MOD80_0222E2E0
	add r1, r4, #0
	bl Main_SetVBlankIntrCB
	pop {r4, pc}
	nop
_0222E7EC: .word MOD80_0222E2E0
	thumb_func_end MOD80_0222E7C8

	thumb_func_start MOD80_0222E7F0
MOD80_0222E7F0: ; 0x0222E7F0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl MOD80_02235D10
	mov r0, #0x33
	lsl r0, r0, #6
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	mov r0, #0xcd
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	bl FUN_02009C0C
	ldr r0, _0222E850 ; =0x00000CC4
	ldr r0, [r6, r0]
	bl FUN_02009E04
	ldr r0, _0222E854 ; =0x00000CD4
	ldr r0, [r6, r0]
	bl FUN_02009E04
	mov r7, #0xcb
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #4
_0222E824:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0222E824
	ldr r0, _0222E858 ; =0x00000B84
	ldr r0, [r6, r0]
	bl FUN_0201FD58
	ldr r0, _0222E858 ; =0x00000B84
	mov r1, #0
	str r1, [r6, r0]
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222E850: .word 0x00000CC4
_0222E854: .word 0x00000CD4
_0222E858: .word 0x00000B84
	thumb_func_end MOD80_0222E7F0

	thumb_func_start MOD80_0222E85C
MOD80_0222E85C: ; 0x0222E85C
	ldrh r1, [r0, #0x3a]
	cmp r1, #0
	beq _0222E866
	sub r1, r1, #1
	strh r1, [r0, #0x3a]
_0222E866:
	bx lr
	thumb_func_end MOD80_0222E85C

	thumb_func_start MOD80_0222E868
MOD80_0222E868: ; 0x0222E868
	ldr r1, _0222E878 ; =0x0000100A
	mov r2, #1
	strh r2, [r0, r1]
	mov r2, #0
	sub r1, r1, #2
	strh r2, [r0, r1]
	bx lr
	nop
_0222E878: .word 0x0000100A
	thumb_func_end MOD80_0222E868

	thumb_func_start MOD80_0222E87C
MOD80_0222E87C: ; 0x0222E87C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222E8B4 ; =0x0000100A
	ldrh r1, [r4, r0]
	cmp r1, #0
	beq _0222E8B0
	ldr r0, [r4]
	sub r1, r1, #1
	ldr r0, [r0, #0xc]
	bl PCStorage_CountMonsAndEggsInBox
	ldr r1, _0222E8B8 ; =0x00001008
	ldrh r2, [r4, r1]
	add r0, r2, r0
	strh r0, [r4, r1]
	add r0, r1, #2
	ldrh r0, [r4, r0]
	add r2, r0, #1
	add r0, r1, #2
	strh r2, [r4, r0]
	ldrh r0, [r4, r0]
	cmp r0, #0x13
	bne _0222E8B0
	mov r2, #0
	add r0, r1, #2
	strh r2, [r4, r0]
_0222E8B0:
	pop {r4, pc}
	nop
_0222E8B4: .word 0x0000100A
_0222E8B8: .word 0x00001008
	thumb_func_end MOD80_0222E87C

	thumb_func_start MOD80_0222E8BC
MOD80_0222E8BC: ; 0x0222E8BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222E8D0 ; =0x00000E98
	mov r1, #1
	add r0, r4, r0
	bl FUN_0200D858
	ldr r1, _0222E8D4 ; =0x00000FD8
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_0222E8D0: .word 0x00000E98
_0222E8D4: .word 0x00000FD8
	thumb_func_end MOD80_0222E8BC

	thumb_func_start MOD80_0222E8D8
MOD80_0222E8D8: ; 0x0222E8D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222E8F0 ; =0x00000FD8
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _0222E8EE
	bl FUN_0200DBFC
	ldr r0, _0222E8F0 ; =0x00000FD8
	mov r1, #0
	str r1, [r4, r0]
_0222E8EE:
	pop {r4, pc}
	.align 2, 0
_0222E8F0: .word 0x00000FD8
	thumb_func_end MOD80_0222E8D8

	thumb_func_start MOD80_0222E8F4
MOD80_0222E8F4: ; 0x0222E8F4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_0222EDE0
	ldr r0, [r4, #4]
	bl MOD80_0222EA04
	add r0, r4, #0
	bl MOD80_0222EB6C
	add r0, r4, #0
	bl MOD80_0222EC98
	add r0, r4, #0
	bl MOD80_0222EC24
	add r0, r4, #0
	bl MOD80_02236D84
	add r0, r4, #0
	bl MOD80_0222F20C
	ldr r1, _0222E9B0 ; =0x00000449
	mov r0, #4
	mov r2, #1
	bl FUN_0200433C
	ldrh r0, [r4, #0x34]
	cmp r0, #0
	bne _0222E968
	add r0, r4, #0
	bl MOD80_0222EB40
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #1
	strh r0, [r4, #0x34]
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0
	add r0, r4, #0
	bl MOD80_02235900
	b _0222E9A2
_0222E968:
	ldr r0, _0222E9B4 ; =0x0000100C
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _0222E988
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _0222E99E
_0222E988:
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
_0222E99E:
	mov r0, #5
	str r0, [r4, #0x2c]
_0222E9A2:
	ldr r0, _0222E9B4 ; =0x0000100C
	mov r1, #0
	str r1, [r4, r0]
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0222E9B0: .word 0x00000449
_0222E9B4: .word 0x0000100C
	thumb_func_end MOD80_0222E8F4

	thumb_func_start MOD80_0222E9B8
MOD80_0222E9B8: ; 0x0222E9B8
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222E79C
	bl FUN_02033EEC
	ldr r1, [r4, #0x2c]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _0222E9D4 ; =0x022379FC
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0222E9D4: .word MOD80_022379FC
	thumb_func_end MOD80_0222E9B8

	thumb_func_start MOD80_0222E9D8
MOD80_0222E9D8: ; 0x0222E9D8
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02033ED0
	add r0, r4, #0
	bl MOD80_0222EC88
	add r0, r4, #0
	bl MOD80_0222EE08
	add r0, r4, #0
	bl MOD80_0222ED9C
	ldr r0, [r4, #4]
	bl MOD80_0222EB14
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_0222E9D8

	thumb_func_start MOD80_0222EA04
MOD80_0222EA04: ; 0x0222EA04
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _0222EAFC ; =0x02236EA4
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _0222EB00 ; =0x02236F04
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _0222EB04 ; =0x02236EE8
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _0222EB08 ; =0x02236F20
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _0222EB0C ; =0x02236F3C
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _0222EB10 ; =0x02236ECC
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_0222EAFC: .word MOD80_02236EA4
_0222EB00: .word MOD80_02236F04
_0222EB04: .word MOD80_02236EE8
_0222EB08: .word MOD80_02236F20
_0222EB0C: .word MOD80_02236F3C
_0222EB10: .word MOD80_02236ECC
	thumb_func_end MOD80_0222EA04

	thumb_func_start MOD80_0222EB14
MOD80_0222EB14: ; 0x0222EB14
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_0222EB14

	thumb_func_start MOD80_0222EB40
MOD80_0222EB40: ; 0x0222EB40
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	ldr r0, _0222EB68 ; =0x00000D5C
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200A0
	pop {r4, pc}
	.align 2, 0
_0222EB68: .word 0x00000D5C
	thumb_func_end MOD80_0222EB40

	thumb_func_start MOD80_0222EB6C
MOD80_0222EB6C: ; 0x0222EB6C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #4
	add r3, r2, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0xe
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x1e
	add r2, r4, #0
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x1d
	add r2, r4, #0
	mov r3, #2
	bl FUN_020068C8
	add r0, r5, #0
	bl MOD80_0222F338
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD80_0222EB6C

	thumb_func_start MOD80_0222EC24
MOD80_0222EC24: ; 0x0222EC24
	push {r4, lr}
	sub sp, #0x30
	mov r2, #0xcf
	add r4, r0, #0
	lsl r2, r2, #4
	add r0, sp, #0
	add r1, r4, #0
	add r2, r4, r2
	mov r3, #1
	bl MOD80_0222E5E8
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	lsl r1, r0, #2
	ldr r0, _0222EC7C ; =0x02236E98
	ldrh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	lsl r1, r0, #2
	ldr r0, _0222EC80 ; =0x02236E9A
	ldrh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _0222EC84 ; =0x00000D5C
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _0222EC84 ; =0x00000D5C
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_02020130
	add sp, #0x30
	pop {r4, pc}
	nop
_0222EC7C: .word MOD80_02236E98
_0222EC80: .word MOD80_02236E9A
_0222EC84: .word 0x00000D5C
	thumb_func_end MOD80_0222EC24

	thumb_func_start MOD80_0222EC88
MOD80_0222EC88: ; 0x0222EC88
	ldr r1, _0222EC90 ; =0x00000D5C
	ldr r3, _0222EC94 ; =FUN_0201FFC8
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_0222EC90: .word 0x00000D5C
_0222EC94: .word FUN_0201FFC8
	thumb_func_end MOD80_0222EC88

	thumb_func_start MOD80_0222EC98
MOD80_0222EC98: ; 0x0222EC98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r3, #1
	add r7, r0, #0
	str r3, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	ldr r1, _0222ED88 ; =0x00000EB8
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	add r1, r7, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _0222ED88 ; =0x00000EB8
	mov r1, #0
	add r0, r7, r0
	bl FUN_02019620
	mov r0, #2
	str r0, [sp]
	mov r3, #0
	mov r2, #0xb5
	ldr r0, _0222ED8C ; =0x000F0400
	str r3, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _0222ED88 ; =0x00000EB8
	str r3, [sp, #0xc]
	lsl r2, r2, #4
	ldr r2, [r7, r2]
	add r0, r7, r0
	mov r1, #1
	bl AddTextPrinterParameterized2
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, _0222ED90 ; =0x00000ED8
	mov r6, #0x61
	mov r4, #6
	add r5, r7, r0
_0222ECF2:
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xf
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	add r1, r5, #0
	mov r2, #1
	mov r3, #9
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	ldr r0, [sp, #0x14]
	add r6, #0x1e
	add r0, r0, #1
	add r4, r4, #5
	add r5, #0x10
	str r0, [sp, #0x14]
	cmp r0, #3
	blt _0222ECF2
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	ldr r1, _0222ED94 ; =0x00000E98
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x60
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	add r1, r7, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _0222ED94 ; =0x00000E98
	mov r1, #0xf
	add r0, r7, r0
	bl FUN_02019620
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x96
	ldr r1, _0222ED98 ; =0x00000FB8
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	add r1, r7, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	ldr r0, _0222ED98 ; =0x00000FB8
	mov r1, #0xf
	add r0, r7, r0
	bl FUN_02019620
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222ED88: .word 0x00000EB8
_0222ED8C: .word 0x000F0400
_0222ED90: .word 0x00000ED8
_0222ED94: .word 0x00000E98
_0222ED98: .word 0x00000FB8
	thumb_func_end MOD80_0222EC98

	thumb_func_start MOD80_0222ED9C
MOD80_0222ED9C: ; 0x0222ED9C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _0222EDD0 ; =0x00000FB8
	add r0, r6, r0
	bl FUN_02019178
	ldr r0, _0222EDD4 ; =0x00000E98
	add r0, r6, r0
	bl FUN_02019178
	ldr r0, _0222EDD8 ; =0x00000ED8
	mov r4, #0
	add r5, r6, r0
_0222EDB6:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #3
	blt _0222EDB6
	ldr r0, _0222EDDC ; =0x00000EB8
	add r0, r6, r0
	bl FUN_02019178
	pop {r4, r5, r6, pc}
	nop
_0222EDD0: .word 0x00000FB8
_0222EDD4: .word 0x00000E98
_0222EDD8: .word 0x00000ED8
_0222EDDC: .word 0x00000EB8
	thumb_func_end MOD80_0222ED9C

	thumb_func_start MOD80_0222EDE0
MOD80_0222EDE0: ; 0x0222EDE0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _0222EE04 ; =0x00000B4C
	str r0, [r4, r1]
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0x27
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_0222EE04: .word 0x00000B4C
	thumb_func_end MOD80_0222EDE0

	thumb_func_start MOD80_0222EE08
MOD80_0222EE08: ; 0x0222EE08
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222EE20 ; =0x00000B4C
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0xb5
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	.align 2, 0
_0222EE20: .word 0x00000B4C
	thumb_func_end MOD80_0222EE08

	thumb_func_start MOD80_0222EE24
MOD80_0222EE24: ; 0x0222EE24
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222EE60 ; =0x00000FEC
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _0222EE5A
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	mov r0, #4
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r4, #0
	mov r1, #7
	mov r2, #0xb
	bl MOD80_0222E7A8
	mov r0, #1
	str r0, [r4, #0x1c]
	mov r0, #9
	str r0, [r4, #0x2c]
_0222EE5A:
	mov r0, #3
	pop {r4, pc}
	nop
_0222EE60: .word 0x00000FEC
	thumb_func_end MOD80_0222EE24

	thumb_func_start MOD80_0222EE64
MOD80_0222EE64: ; 0x0222EE64
	push {r3, lr}
	mov r1, #0xa
	mov r2, #2
	bl MOD80_0222E6DC
	mov r0, #3
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD80_0222EE64

	thumb_func_start MOD80_0222EE74
MOD80_0222EE74: ; 0x0222EE74
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #3
	str r0, [r4, #0x2c]
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD80_0222EE74

	thumb_func_start MOD80_0222EE98
MOD80_0222EE98: ; 0x0222EE98
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _0222EEA8
	mov r0, #5
	str r0, [r4, #0x2c]
_0222EEA8:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_0222EE98

	thumb_func_start MOD80_0222EEAC
MOD80_0222EEAC: ; 0x0222EEAC
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _0222EEBC
	mov r0, #5
	str r0, [r4, #0x2c]
_0222EEBC:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_0222EEAC

	thumb_func_start MOD80_0222EEC0
MOD80_0222EEC0: ; 0x0222EEC0
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222EEF4 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #4
	mov r2, #1
	mov r3, #0
	bl MOD80_0222F250
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #6
	bl MOD80_0222E6DC
	ldr r0, _0222EEF8 ; =0x00000D5C
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_020200BC
	add r0, r4, #0
	bl MOD80_0222E868
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0222EEF4: .word 0x00000F0F
_0222EEF8: .word 0x00000D5C
	thumb_func_end MOD80_0222EEC0

	thumb_func_start MOD80_0222EEFC
MOD80_0222EEFC: ; 0x0222EEFC
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0222F084 ; =gMain
	mov r2, #2
	ldr r1, [r1, #0x48]
	add r4, r0, #0
	tst r2, r1
	beq _0222EF36
	bl MOD80_0222E7BC
	add r2, r0, #0
	ldr r0, _0222F088 ; =0x00000F0F
	mov r1, #7
	str r0, [sp]
	add r0, r4, #0
	mov r3, #0
	bl MOD80_0222F2A8
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0xc
	bl MOD80_0222E6DC
	ldr r0, _0222F08C ; =0x00000D5C
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200BC
	b _0222F07C
_0222EF36:
	mov r2, #1
	tst r2, r1
	beq _0222F002
	add r1, r4, #0
	add r1, #0xb4
	ldrh r1, [r1]
	cmp r1, #0
	beq _0222EF50
	cmp r1, #1
	beq _0222EFBE
	cmp r1, #2
	beq _0222EFD2
	b _0222F07C
_0222EF50:
	ldrh r1, [r4, #0x36]
	cmp r1, #0
	bne _0222EF6A
	mov r1, #5
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
	ldr r0, _0222F090 ; =0x000005DC
	bl FUN_020054C8
	b _0222F07C
_0222EF6A:
	ldrh r1, [r4, #0x3a]
	cmp r1, #0
	bne _0222EF8C
	mov r1, #7
	mov r2, #0xb
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r4, #0x1c]
	mov r0, #9
	str r0, [r4, #0x2c]
	ldr r0, _0222F094 ; =0x00000708
	strh r0, [r4, #0x3a]
	ldr r0, _0222F090 ; =0x000005DC
	bl FUN_020054C8
	b _0222F07C
_0222EF8C:
	ldr r0, _0222F08C ; =0x00000D5C
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200BC
	ldr r0, _0222F088 ; =0x00000F0F
	mov r1, #0x22
	str r0, [sp]
	add r0, r4, #0
	mov r2, #1
	mov r3, #0
	bl MOD80_0222F250
	add r0, r4, #0
	mov r1, #0xb
	mov r2, #5
	bl MOD80_0222E6DC
	ldr r0, _0222F098 ; =0x000005F3
	bl FUN_020054C8
	ldr r0, _0222F09C ; =0x00000FDC
	mov r1, #0
	str r1, [r4, r0]
	b _0222F07C
_0222EFBE:
	mov r1, #4
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
	ldr r0, _0222F090 ; =0x000005DC
	bl FUN_020054C8
	b _0222F07C
_0222EFD2:
	bl MOD80_0222E7BC
	add r2, r0, #0
	ldr r0, _0222F088 ; =0x00000F0F
	mov r1, #7
	str r0, [sp]
	add r0, r4, #0
	mov r3, #0
	bl MOD80_0222F2A8
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0xc
	bl MOD80_0222E6DC
	ldr r0, _0222F08C ; =0x00000D5C
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_020200BC
	ldr r0, _0222F090 ; =0x000005DC
	bl FUN_020054C8
	b _0222F07C
_0222F002:
	mov r0, #0x40
	tst r0, r1
	beq _0222F040
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	cmp r0, #0
	beq _0222F07C
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	sub r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	strh r1, [r0]
	ldr r0, _0222F090 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	ldr r1, _0222F0A0 ; =0x02236E98
	ldr r2, _0222F0A4 ; =0x02236E9A
	lsl r3, r0, #2
	ldr r0, _0222F08C ; =0x00000D5C
	ldrh r1, [r1, r3]
	ldrh r2, [r2, r3]
	ldr r0, [r4, r0]
	bl MOD80_0222E6E4
	b _0222F07C
_0222F040:
	mov r0, #0x80
	tst r0, r1
	beq _0222F07C
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	cmp r0, #2
	bhs _0222F07C
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xb4
	strh r1, [r0]
	ldr r0, _0222F090 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	add r0, #0xb4
	ldrh r0, [r0]
	ldr r1, _0222F0A0 ; =0x02236E98
	ldr r2, _0222F0A4 ; =0x02236E9A
	lsl r3, r0, #2
	ldr r0, _0222F08C ; =0x00000D5C
	ldrh r1, [r1, r3]
	ldrh r2, [r2, r3]
	ldr r0, [r4, r0]
	bl MOD80_0222E6E4
_0222F07C:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0222F084: .word gMain
_0222F088: .word 0x00000F0F
_0222F08C: .word 0x00000D5C
_0222F090: .word 0x000005DC
_0222F094: .word 0x00000708
_0222F098: .word 0x000005F3
_0222F09C: .word 0x00000FDC
_0222F0A0: .word MOD80_02236E98
_0222F0A4: .word MOD80_02236E9A
	thumb_func_end MOD80_0222EEFC

	thumb_func_start MOD80_0222F0A8
MOD80_0222F0A8: ; 0x0222F0A8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl PlayerProfile_GetTrainerGender
	add r1, r0, #0
	add r0, r4, #0
	bl MOD80_02235A10
	mov r0, #8
	str r0, [r4, #0x2c]
	ldr r0, _0222F0CC ; =0x00000FEC
	mov r1, #0
	strh r1, [r4, r0]
	mov r0, #3
	pop {r4, pc}
	nop
_0222F0CC: .word 0x00000FEC
	thumb_func_end MOD80_0222F0A8

	thumb_func_start MOD80_0222F0D0
MOD80_0222F0D0: ; 0x0222F0D0
	ldr r1, _0222F0E0 ; =0x00000FEC
	ldrh r1, [r0, r1]
	cmp r1, #0
	beq _0222F0DC
	mov r1, #9
	str r1, [r0, #0x2c]
_0222F0DC:
	mov r0, #3
	bx lr
	.align 2, 0
_0222F0E0: .word 0x00000FEC
	thumb_func_end MOD80_0222F0D0

	thumb_func_start MOD80_0222F0E4
MOD80_0222F0E4: ; 0x0222F0E4
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _0222F10A
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _0222F122
_0222F10A:
	mov r0, #6
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
_0222F122:
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD80_0222F0E4

	thumb_func_start MOD80_0222F12C
MOD80_0222F12C: ; 0x0222F12C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0xd
	add r2, r1, #0
	ldr r0, [r4, #4]
	add r2, #0xf5
	bl MOD80_0222E6A8
	ldr r1, _0222F148 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #0xd
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F148: .word 0x00000FCC
	thumb_func_end MOD80_0222F12C

	thumb_func_start MOD80_0222F14C
MOD80_0222F14C: ; 0x0222F14C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F1AC ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222F1A8
	sub r1, r1, #1
	cmp r0, r1
	ldr r0, _0222F1B0 ; =0x00000FB8
	bne _0222F18A
	add r0, r4, r0
	mov r1, #1
	bl FUN_0200D0E0
	ldr r0, _0222F1B0 ; =0x00000FB8
	add r0, r4, r0
	bl FUN_02019570
	ldr r0, _0222F1B4 ; =0x00000D5C
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_020200BC
	mov r0, #5
	str r0, [r4, #0x2c]
	b _0222F1A8
_0222F18A:
	add r0, r4, r0
	mov r1, #1
	bl FUN_0200D0E0
	ldr r0, _0222F1B0 ; =0x00000FB8
	add r0, r4, r0
	bl FUN_02019570
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #7
	str r0, [r4, #0x2c]
_0222F1A8:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F1AC: .word 0x00000FCC
_0222F1B0: .word 0x00000FB8
_0222F1B4: .word 0x00000D5C
	thumb_func_end MOD80_0222F14C

	thumb_func_start MOD80_0222F1B8
MOD80_0222F1B8: ; 0x0222F1B8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222F1D2
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_0222F1D2:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_0222F1B8

	thumb_func_start MOD80_0222F1D8
MOD80_0222F1D8: ; 0x0222F1D8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222F204
	ldr r0, _0222F208 ; =0x00000FDC
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0x2d
	ble _0222F204
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_0222F204:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F208: .word 0x00000FDC
	thumb_func_end MOD80_0222F1D8

	thumb_func_start MOD80_0222F20C
MOD80_0222F20C: ; 0x0222F20C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldrh r1, [r7, #0x36]
	mov r0, #0xc
	ldr r2, _0222F240 ; =0x02236EB4
	mul r0, r1
	add r4, r2, r0
	ldr r0, _0222F244 ; =0x00000ED8
	mov r6, #0
	add r5, r7, r0
_0222F220:
	ldr r1, _0222F248 ; =0x00000B34
	ldr r2, [r4]
	ldr r1, [r7, r1]
	ldr r3, _0222F24C ; =0x00000F0F
	add r0, r5, #0
	bl MOD80_0222F300
	add r0, r5, #0
	bl FUN_020191D0
	add r6, r6, #1
	add r4, r4, #4
	add r5, #0x10
	cmp r6, #3
	blt _0222F220
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F240: .word MOD80_02236EB4
_0222F244: .word 0x00000ED8
_0222F248: .word 0x00000B34
_0222F24C: .word 0x00000F0F
	thumb_func_end MOD80_0222F20C

	thumb_func_start MOD80_0222F250
MOD80_0222F250: ; 0x0222F250
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r2, _0222F29C ; =0x00000B34
	add r5, r0, #0
	ldr r0, [r5, r2]
	add r2, #0x18
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	ldr r0, _0222F2A0 ; =0x00000E98
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _0222F2A0 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _0222F2A0 ; =0x00000E98
	ldr r2, _0222F2A4 ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0222F29C: .word 0x00000B34
_0222F2A0: .word 0x00000E98
_0222F2A4: .word 0x00000B4C
	thumb_func_end MOD80_0222F250

	thumb_func_start MOD80_0222F2A8
MOD80_0222F2A8: ; 0x0222F2A8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r2, _0222F2F4 ; =0x00000B34
	add r5, r0, #0
	ldr r0, [r5, r2]
	add r2, #0x18
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	ldr r0, _0222F2F8 ; =0x00000FB8
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _0222F2F8 ; =0x00000FB8
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _0222F2F8 ; =0x00000FB8
	ldr r2, _0222F2FC ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_0222F2F4: .word 0x00000B34
_0222F2F8: .word 0x00000FB8
_0222F2FC: .word 0x00000B4C
	thumb_func_end MOD80_0222F2A8

	thumb_func_start MOD80_0222F300
MOD80_0222F300: ; 0x0222F300
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, r1, #0
	add r4, r3, #0
	add r1, r2, #0
	bl NewString_ReadMsgData
	lsl r1, r4, #0x18
	add r6, r0, #0
	add r0, r5, #0
	lsr r1, r1, #0x18
	bl FUN_02019620
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r0, r5, #0
	mov r1, #1
	add r2, r6, #0
	str r3, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD80_0222F300

	thumb_func_start MOD80_0222F338
MOD80_0222F338: ; 0x0222F338
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [r0, #4]
	mov r0, #2
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #5
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r0, #0
	str r0, [sp]
	mov r0, #0x2a
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0xf
	add r2, r4, #0
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x1f
	add r2, r4, #0
	mov r3, #5
	bl FUN_020068C8
	add sp, #0x10
	pop {r4, pc}
	thumb_func_end MOD80_0222F338

	thumb_func_start MOD80_0222F394
MOD80_0222F394: ; 0x0222F394
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_0222F7F0
	ldr r0, [r4, #4]
	bl MOD80_0222F494
	add r0, r4, #0
	bl MOD80_0222F5A8
	add r0, r4, #0
	bl MOD80_0222F6EC
	add r0, r4, #0
	bl MOD80_0222F690
	add r0, r4, #0
	add r0, #0xd4
	bl FUN_020690E4
	str r0, [sp]
	mov r0, #7
	lsl r0, r0, #6
	ldr r2, _0222F448 ; =0x00000B34
	add r0, r4, r0
	str r0, [sp, #4]
	add r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, r2, #4
	ldr r3, _0222F44C ; =0x00000F08
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r3, r4, r3
	bl MOD80_0222FBC0
	ldr r0, _0222F448 ; =0x00000B34
	ldr r1, _0222F450 ; =0x00000F58
	mov r2, #0x1e
	lsl r2, r2, #4
	ldr r0, [r4, r0]
	add r1, r4, r1
	add r2, r4, r2
	bl MOD80_0222FD28
	ldr r1, _0222F454 ; =0x000001C7
	ldrsb r0, [r4, r1]
	add r1, r1, #1
	ldrsb r1, [r4, r1]
	bl MOD80_02234668
	mov r1, #0x71
	lsl r1, r1, #2
	ldrsh r2, [r4, r1]
	ldr r3, _0222F458 ; =0x00000F78
	add r1, r1, #2
	str r2, [sp]
	ldrsb r1, [r4, r1]
	ldr r2, _0222F448 ; =0x00000B34
	add r3, r4, r3
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, r2, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	bl MOD80_02234048
	add r0, r4, #0
	add r0, #0xd4
	bl MOD80_0222FD88
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0222F448: .word 0x00000B34
_0222F44C: .word 0x00000F08
_0222F450: .word 0x00000F58
_0222F454: .word 0x000001C7
_0222F458: .word 0x00000F78
	thumb_func_end MOD80_0222F394

	thumb_func_start MOD80_0222F45C
MOD80_0222F45C: ; 0x0222F45C
	push {r3, lr}
	ldr r1, [r0, #0x2c]
	lsl r2, r1, #2
	ldr r1, _0222F46C ; =0x02237A40
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_0222F46C: .word MOD80_02237A40
	thumb_func_end MOD80_0222F45C

	thumb_func_start MOD80_0222F470
MOD80_0222F470: ; 0x0222F470
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222F6DC
	add r0, r4, #0
	bl MOD80_0222F830
	add r0, r4, #0
	bl MOD80_0222F7B8
	ldr r0, [r4, #4]
	bl MOD80_0222F57C
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_0222F470

	thumb_func_start MOD80_0222F494
MOD80_0222F494: ; 0x0222F494
	push {r4, r5, lr}
	sub sp, #0x8c
	ldr r5, _0222F568 ; =0x02236FC8
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x70
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _0222F56C ; =0x02236FAC
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _0222F570 ; =0x02236F90
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _0222F574 ; =0x02236F74
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _0222F578 ; =0x02236F58
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	add sp, #0x8c
	pop {r4, r5, pc}
	nop
_0222F568: .word MOD80_02236FC8
_0222F56C: .word MOD80_02236FAC
_0222F570: .word MOD80_02236F90
_0222F574: .word MOD80_02236F74
_0222F578: .word MOD80_02236F58
	thumb_func_end MOD80_0222F494

	thumb_func_start MOD80_0222F57C
MOD80_0222F57C: ; 0x0222F57C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_0222F57C

	thumb_func_start MOD80_0222F5A8
MOD80_0222F5A8: ; 0x0222F5A8
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #7
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #5
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x11
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x19
	add r2, r4, #0
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #0x2a
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0xf
	add r2, r4, #0
	mov r3, #5
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x1f
	add r2, r4, #0
	mov r3, #5
	bl FUN_020068C8
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_0222F5A8

	thumb_func_start MOD80_0222F690
MOD80_0222F690: ; 0x0222F690
	push {r4, lr}
	sub sp, #0x30
	mov r2, #0xcf
	add r4, r0, #0
	lsl r2, r2, #4
	add r0, sp, #0
	add r1, r4, #0
	add r2, r4, r2
	mov r3, #1
	bl MOD80_0222E5E8
	mov r0, #0x32
	lsl r0, r0, #0xe
	str r0, [sp, #8]
	mov r0, #0x3a
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _0222F6D8 ; =0x00000E6C
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _0222F6D8 ; =0x00000E6C
	mov r1, #0x25
	ldr r0, [r4, r0]
	bl FUN_02020130
	bl FUN_02033E74
	add sp, #0x30
	pop {r4, pc}
	nop
_0222F6D8: .word 0x00000E6C
	thumb_func_end MOD80_0222F690

	thumb_func_start MOD80_0222F6DC
MOD80_0222F6DC: ; 0x0222F6DC
	ldr r1, _0222F6E4 ; =0x00000E6C
	ldr r3, _0222F6E8 ; =FUN_0201FFC8
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_0222F6E4: .word 0x00000E6C
_0222F6E8: .word FUN_0201FFC8
	thumb_func_end MOD80_0222F6DC

	thumb_func_start MOD80_0222F6EC
MOD80_0222F6EC: ; 0x0222F6EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x14]
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, _0222F7A8 ; =0x00000E98
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #4]
	add r1, r1, r2
	mov r2, #0
	bl FUN_02019064
	ldr r1, _0222F7A8 ; =0x00000E98
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	mov r1, #0
	bl FUN_02019620
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x5e
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, _0222F7AC ; =0x00000ED8
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #4]
	add r1, r1, r2
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	ldr r1, _0222F7B0 ; =0x00000F08
	ldr r0, [sp, #0x14]
	ldr r4, _0222F7B4 ; =0x02236FE4
	mov r6, #0x86
	mov r7, #0
	add r5, r0, r1
_0222F754:
	ldr r0, [r4, #4]
	add r1, r5, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4, #8]
	mov r2, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r3, [r4]
	ldr r0, [r0, #4]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r7, r7, #1
	mul r0, r1
	add r6, r6, r0
	add r4, #0x10
	add r5, #0x10
	cmp r7, #0xa
	blt _0222F754
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F7A8: .word 0x00000E98
_0222F7AC: .word 0x00000ED8
_0222F7B0: .word 0x00000F08
_0222F7B4: .word MOD80_02236FE4
	thumb_func_end MOD80_0222F6EC

	thumb_func_start MOD80_0222F7B8
MOD80_0222F7B8: ; 0x0222F7B8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _0222F7E4 ; =0x00000E98
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _0222F7E8 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _0222F7EC ; =0x00000F08
	mov r4, #0
	add r5, r5, r0
_0222F7D2:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0xa
	blt _0222F7D2
	pop {r3, r4, r5, pc}
	nop
_0222F7E4: .word 0x00000E98
_0222F7E8: .word 0x00000ED8
_0222F7EC: .word 0x00000F08
	thumb_func_end MOD80_0222F7B8

	thumb_func_start MOD80_0222F7F0
MOD80_0222F7F0: ; 0x0222F7F0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _0222F82C ; =0x00000B4C
	str r0, [r5, r1]
	sub r1, #0x18
	ldr r0, [r5, r1]
	mov r1, #0x27
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r4, #0
	mov r7, #0x14
	add r6, r1, #4
_0222F816:
	add r0, r7, #0
	mov r1, #0x3e
	bl String_ctor
	str r0, [r5, r6]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa
	blt _0222F816
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0222F82C: .word 0x00000B4C
	thumb_func_end MOD80_0222F7F0

	thumb_func_start MOD80_0222F830
MOD80_0222F830: ; 0x0222F830
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r6, _0222F85C ; =0x00000B54
	mov r4, #0
	add r5, r7, #0
_0222F83A:
	ldr r0, [r5, r6]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xa
	blt _0222F83A
	ldr r0, _0222F860 ; =0x00000B4C
	ldr r0, [r7, r0]
	bl String_dtor
	mov r0, #0xb5
	lsl r0, r0, #4
	ldr r0, [r7, r0]
	bl String_dtor
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222F85C: .word 0x00000B54
_0222F860: .word 0x00000B4C
	thumb_func_end MOD80_0222F830

	thumb_func_start MOD80_0222F864
MOD80_0222F864: ; 0x0222F864
	mov r1, #1
	str r1, [r0, #0x2c]
	mov r0, #3
	bx lr
	thumb_func_end MOD80_0222F864

	thumb_func_start MOD80_0222F86C
MOD80_0222F86C: ; 0x0222F86C
	push {r4, lr}
	sub sp, #8
	ldr r1, _0222F8C0 ; =gMain
	mov r2, #1
	ldr r3, [r1, #0x48]
	add r4, r0, #0
	add r1, r3, #0
	tst r1, r2
	beq _0222F8A2
	ldr r1, _0222F8C4 ; =0x00000F0F
	mov r3, #0
	str r1, [sp]
	add r1, r4, #0
	add r1, #0xd4
	str r1, [sp, #4]
	mov r1, #5
	bl MOD80_0222FB3C
	add r0, r4, #0
	mov r1, #3
	mov r2, #7
	bl MOD80_0222E6DC
	ldr r0, _0222F8C8 ; =0x000005DC
	bl FUN_020054C8
	b _0222F8B8
_0222F8A2:
	mov r1, #2
	tst r3, r1
	beq _0222F8B8
	str r1, [r4, #0x2c]
	add r1, r2, #0
	mov r2, #0
	bl MOD80_0222E7A8
	ldr r0, _0222F8C8 ; =0x000005DC
	bl FUN_020054C8
_0222F8B8:
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	nop
_0222F8C0: .word gMain
_0222F8C4: .word 0x00000F0F
_0222F8C8: .word 0x000005DC
	thumb_func_end MOD80_0222F86C

	thumb_func_start MOD80_0222F8CC
MOD80_0222F8CC: ; 0x0222F8CC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #6
	mov r1, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD80_0222F8CC

	thumb_func_start MOD80_0222F8F4
MOD80_0222F8F4: ; 0x0222F8F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _0222F910 ; =0x0000014E
	mov r1, #0xf
	bl MOD80_0222E6A8
	ldr r1, _0222F914 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #6
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	nop
_0222F910: .word 0x0000014E
_0222F914: .word 0x00000FCC
	thumb_func_end MOD80_0222F8F4

	thumb_func_start MOD80_0222F918
MOD80_0222F918: ; 0x0222F918
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0222F960 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0222F95C
	sub r1, r1, #1
	cmp r0, r1
	bne _0222F942
	ldr r0, _0222F964 ; =0x00000E98
	mov r1, #0
	add r0, r4, r0
	str r1, [r4, #0x2c]
	bl FUN_0200D0E0
	b _0222F956
_0222F942:
	mov r0, #2
	str r0, [r4, #0x2c]
	ldr r0, _0222F968 ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #7
	mov r2, #8
	bl MOD80_0222E7A8
_0222F956:
	add r0, r4, #0
	bl MOD80_0222FE18
_0222F95C:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222F960: .word 0x00000FCC
_0222F964: .word 0x00000E98
_0222F968: .word 0x0000100C
	thumb_func_end MOD80_0222F918

	thumb_func_start MOD80_0222F96C
MOD80_0222F96C: ; 0x0222F96C
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0
	add r2, sp, #8
	strb r0, [r2, #8]
	mov r0, #1
	strb r0, [r2, #9]
	mov r0, #2
	strb r0, [r2, #0xa]
	ldrb r3, [r2, #0xb]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0x30
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0xc0
	bic r3, r1
	mov r1, #0x3e
	strb r3, [r2, #0xb]
	bl ListMenu_ctor
	ldr r1, _0222F9FC ; =0x00000FC8
	mov r2, #0x36
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldr r1, _0222FA00 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl ListMenu_ItemFromMsgData
	ldr r0, _0222F9FC ; =0x00000FC8
	ldr r1, _0222FA00 ; =0x00000B34
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x37
	mov r3, #2
	bl ListMenu_ItemFromMsgData
	ldr r0, _0222F9FC ; =0x00000FC8
	mov r2, #0x1f
	ldr r1, [r4, r0]
	sub r0, #0xf0
	str r1, [sp, #8]
	add r0, r4, r0
	mov r1, #0
	mov r3, #0xb
	str r0, [sp, #0xc]
	bl FUN_0200CCA4
	mov r0, #0x3e
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #8
	mov r1, #9
	add r3, r2, #0
	bl FUN_02001C14
	mov r1, #0xfd
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #8
	str r0, [r4, #0x2c]
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_0222F9FC: .word 0x00000FC8
_0222FA00: .word 0x00000B34
	thumb_func_end MOD80_0222F96C

	thumb_func_start MOD80_0222FA04
MOD80_0222FA04: ; 0x0222FA04
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02001C78
	cmp r0, #1
	beq _0222FA26
	cmp r0, #2
	beq _0222FAA4
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0222FAA4
	b _0222FAD6
_0222FA26:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0222FADC ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _0222FAE0 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	add r4, r5, #0
	add r4, #0xd4
	add r0, r4, #0
	bl MOD80_022331F8
	cmp r0, #0
	beq _0222FA80
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl GetPartyCount
	cmp r0, #6
	bne _0222FA80
	ldr r0, _0222FAE4 ; =0x00000F0F
	mov r1, #0x24
	str r0, [sp]
	add r0, r5, #0
	mov r2, #1
	mov r3, #0
	str r4, [sp, #4]
	bl MOD80_0222FB3C
	add r0, r5, #0
	mov r1, #3
	mov r2, #1
	bl MOD80_0222E6DC
	add sp, #8
	mov r0, #3
	pop {r3, r4, r5, pc}
_0222FA80:
	ldr r0, _0222FAE4 ; =0x00000F0F
	mov r1, #6
	str r0, [sp]
	add r0, r5, #0
	mov r2, #1
	mov r3, #0
	str r4, [sp, #4]
	bl MOD80_0222FB3C
	add r0, r5, #0
	mov r1, #3
	mov r2, #5
	bl MOD80_0222E6DC
	add r0, r5, #0
	bl MOD80_0222FE18
	b _0222FAD6
_0222FAA4:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0222FADC ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _0222FAE0 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	mov r0, #2
	str r0, [r5, #0x2c]
	add r0, r5, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	add r0, r5, #0
	bl MOD80_0222FE18
_0222FAD6:
	mov r0, #3
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0222FADC: .word 0x00000FC8
_0222FAE0: .word 0x00000ED8
_0222FAE4: .word 0x00000F0F
	thumb_func_end MOD80_0222FA04

	thumb_func_start MOD80_0222FAE8
MOD80_0222FAE8: ; 0x0222FAE8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222FB02
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_0222FB02:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_0222FAE8

	thumb_func_start MOD80_0222FB08
MOD80_0222FB08: ; 0x0222FB08
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0222FB34
	ldr r0, _0222FB38 ; =0x00000FDC
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0x2d
	ble _0222FB34
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_0222FB34:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_0222FB38: .word 0x00000FDC
	thumb_func_end MOD80_0222FB08

	thumb_func_start MOD80_0222FB3C
MOD80_0222FB3C: ; 0x0222FB3C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, [sp, #0x24]
	add r6, r1, #0
	add r4, r2, #0
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl BufferBoxMonSpeciesName
	ldr r0, _0222FBB4 ; =0x00000B34
	add r1, r6, #0
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0xb3
	add r6, r0, #0
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #0x1c
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	ldr r0, _0222FBB8 ; =0x00000E98
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _0222FBB8 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _0222FBB8 ; =0x00000E98
	ldr r2, _0222FBBC ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0222FBB4: .word 0x00000B34
_0222FBB8: .word 0x00000E98
_0222FBBC: .word 0x00000B4C
	thumb_func_end MOD80_0222FB3C

	thumb_func_start MOD80_0222FBC0
MOD80_0222FBC0: ; 0x0222FBC0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	str r1, [sp, #8]
	mov r0, #0x16
	mov r1, #0x3e
	add r7, r2, #0
	add r6, r3, #0
	ldr r4, [sp, #0x4c]
	bl String_ctor
	str r0, [sp, #0x1c]
	mov r0, #0x12
	mov r1, #0x3e
	bl String_ctor
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x1c]
	mov r1, #0x76
	bl GetBoxMonData
	mov r2, #0
	ldrsh r0, [r4, r2]
	mov r1, #6
	str r0, [sp, #0x10]
	mov r0, #2
	ldrsb r0, [r4, r0]
	str r0, [sp, #0x14]
	mov r0, #3
	ldrsb r4, [r4, r0]
	ldr r0, [sp, #0x48]
	bl GetBoxMonData
	str r0, [sp, #0x30]
	add r0, r5, #0
	mov r1, #0x46
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x14]
	ldr r2, _0222FD1C ; =0x022373C0
	lsl r0, r0, #2
	str r0, [sp, #0xc]
	ldr r1, [sp, #0xc]
	add r0, r5, #0
	ldr r1, [r2, r1]
	bl NewString_ReadMsgData
	str r0, [sp, #0x28]
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	mov r1, #3
	str r0, [sp, #4]
	add r0, r7, #0
	add r2, r4, #0
	add r3, r1, #0
	bl BufferIntegerAsString
	add r0, r7, #0
	add r1, r5, #0
	mov r2, #0x66
	mov r3, #0x3e
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x24]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x10]
	bl NewString_ReadMsgData
	ldr r1, [sp, #0x30]
	str r0, [sp, #0x2c]
	lsl r1, r1, #0x10
	ldr r0, [sp, #0x18]
	lsr r1, r1, #0x10
	mov r2, #0x3e
	bl GetItemNameIntoString
	mov r4, #0
	add r5, r6, #0
	add r7, r4, #0
_0222FC64:
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_02019620
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #5
	blt _0222FC64
	mov r2, #0
	ldr r0, _0222FD20 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	ldr r1, [sp, #0x1c]
	add r0, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	ldr r0, [sp, #0x14]
	cmp r0, #3
	beq _0222FCA2
	mov r3, #0
	ldr r1, _0222FD24 ; =0x02237A34
	ldr r0, [sp, #0xc]
	str r3, [sp]
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x28]
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #0x46
	bl MOD80_02236D50
_0222FCA2:
	mov r2, #0
	ldr r0, _0222FD20 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r1, [sp, #0x2c]
	add r0, #0x10
	add r3, r2, #0
	bl MOD80_02236D50
	mov r0, #2
	str r0, [sp]
	ldr r0, _0222FD20 ; =0x000F0200
	mov r2, #0
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r1, [sp, #0x24]
	add r0, #0x20
	add r3, r2, #0
	bl MOD80_02236D50
	mov r2, #0
	ldr r0, _0222FD20 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r1, [sp, #0x20]
	add r0, #0x30
	add r3, r2, #0
	bl MOD80_02236D50
	mov r2, #0
	ldr r0, _0222FD20 ; =0x000F0200
	str r2, [sp]
	add r6, #0x40
	str r0, [sp, #4]
	ldr r1, [sp, #0x18]
	add r0, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	ldr r0, [sp, #0x20]
	bl String_dtor
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x24]
	bl String_dtor
	ldr r0, [sp, #0x28]
	bl String_dtor
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x2c]
	bl String_dtor
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0222FD1C: .word MOD80_022373C0
_0222FD20: .word 0x000F0200
_0222FD24: .word MOD80_02237A34
	thumb_func_end MOD80_0222FBC0

	thumb_func_start MOD80_0222FD28
MOD80_0222FD28: ; 0x0222FD28
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #0x10
	mov r1, #0x3e
	add r7, r2, #0
	bl String_ctor
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0x30
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl CopyU16ArrayToString
	mov r2, #0
	ldr r0, _0222FD84 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	mov r2, #0
	ldr r0, _0222FD84 ; =0x000F0200
	str r2, [sp]
	add r5, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD80_02236D50
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0222FD84: .word 0x000F0200
	thumb_func_end MOD80_0222FD28

	thumb_func_start MOD80_0222FD88
MOD80_0222FD88: ; 0x0222FD88
	push {r4, r5, r6, lr}
	sub sp, #0x30
	mov r1, #0x32
	add r5, r0, #0
	mov r0, #0x3e
	lsl r1, r1, #6
	bl AllocFromHeap
	add r4, r0, #0
	add r0, sp, #0x20
	add r1, r5, #0
	mov r2, #2
	bl FUN_02068B68
	mov r1, #0
	add r0, r5, #0
	add r2, r1, #0
	bl GetMonData
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	mov r3, #0
	str r3, [sp]
	mov r1, #0xa
	str r1, [sp, #4]
	str r1, [sp, #8]
	str r4, [sp, #0xc]
	str r6, [sp, #0x10]
	str r3, [sp, #0x14]
	mov r1, #2
	str r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	add r1, sp, #0x20
	ldrh r0, [r1]
	ldrh r1, [r1, #2]
	mov r2, #0x3e
	bl FUN_020124B4
	mov r1, #0x32
	add r0, r4, #0
	lsl r1, r1, #6
	bl DC_FlushRange
	mov r1, #0x4a
	mov r2, #0x32
	add r0, r4, #0
	lsl r1, r1, #8
	lsl r2, r2, #6
	bl GX_LoadOBJ
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x3e
	mov r3, #0x1a
	str r0, [sp, #4]
	add r1, sp, #0x20
	ldrh r0, [r1]
	ldrh r1, [r1, #4]
	mov r2, #1
	lsl r3, r3, #4
	bl FUN_02006930
	add r0, r4, #0
	bl FreeToHeap
	add sp, #0x30
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD80_0222FD88

	thumb_func_start MOD80_0222FE18
MOD80_0222FE18: ; 0x0222FE18
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r1, _0222FE54 ; =0x000001C7
	add r4, r0, #0
	ldrsb r0, [r4, r1]
	add r1, r1, #1
	ldrsb r1, [r4, r1]
	bl MOD80_02234668
	mov r1, #0x71
	lsl r1, r1, #2
	ldrsh r2, [r4, r1]
	add r1, r1, #2
	ldr r3, _0222FE58 ; =0x00000F78
	str r2, [sp]
	ldrsb r1, [r4, r1]
	ldr r2, _0222FE5C ; =0x00000B34
	add r3, r4, r3
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, r2, #4
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	bl MOD80_02234048
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0222FE54: .word 0x000001C7
_0222FE58: .word 0x00000F78
_0222FE5C: .word 0x00000B34
	thumb_func_end MOD80_0222FE18

	thumb_func_start MOD80_0222FE60
MOD80_0222FE60: ; 0x0222FE60
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_0223022C
	ldr r0, [r4, #4]
	bl MOD80_0222FF6C
	add r0, r4, #0
	bl MOD80_02230054
	add r0, r4, #0
	bl MOD80_02230128
	add r0, r4, #0
	bl MOD80_022300CC
	add r0, r4, #0
	add r0, #0xc4
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	add r5, r1, #0
	mul r5, r0
	add r0, #0xd4
	add r0, r4, r0
	add r0, r0, r5
	bl FUN_020690E4
	str r0, [sp]
	mov r0, #0xb9
	lsl r0, r0, #2
	add r0, r4, r0
	ldr r2, _0222FF24 ; =0x00000B34
	add r0, r0, r5
	str r0, [sp, #4]
	add r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, r2, #4
	ldr r3, _0222FF28 ; =0x00000F08
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r3, r4, r3
	bl MOD80_0222FBC0
	add r3, r4, #0
	add r3, #0xc4
	ldr r0, _0222FF24 ; =0x00000B34
	mov r2, #0xc1
	ldr r5, [r3]
	mov r3, #0x49
	ldr r1, _0222FF2C ; =0x00000F58
	lsl r2, r2, #2
	lsl r3, r3, #2
	ldr r0, [r4, r0]
	add r2, r4, r2
	mul r3, r5
	add r1, r4, r1
	add r2, r2, r3
	bl MOD80_0222FD28
	add r0, r4, #0
	mov r1, #0x7e
	add r0, #0xc4
	lsl r1, r1, #2
	add r2, r4, r1
	ldr r0, [r0]
	sub r1, #0xd4
	mul r1, r0
	add r0, r2, r1
	bl MOD80_0222FD88
	ldr r0, _0222FF24 ; =0x00000B34
	ldr r1, _0222FF30 ; =0x00000F78
	ldr r0, [r4, r0]
	add r1, r4, r1
	bl MOD80_02230550
	add r0, r4, #0
	bl MOD80_0223043C
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #2
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0222FF24: .word 0x00000B34
_0222FF28: .word 0x00000F08
_0222FF2C: .word 0x00000F58
_0222FF30: .word 0x00000F78
	thumb_func_end MOD80_0222FE60

	thumb_func_start MOD80_0222FF34
MOD80_0222FF34: ; 0x0222FF34
	push {r3, lr}
	ldr r1, [r0, #0x2c]
	lsl r2, r1, #2
	ldr r1, _0222FF44 ; =0x02237A64
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_0222FF44: .word MOD80_02237A64
	thumb_func_end MOD80_0222FF34

	thumb_func_start MOD80_0222FF48
MOD80_0222FF48: ; 0x0222FF48
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_02230118
	add r0, r4, #0
	bl MOD80_022302C4
	add r0, r4, #0
	bl MOD80_022301F4
	ldr r0, [r4, #4]
	bl MOD80_02230030
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_0222FF48

	thumb_func_start MOD80_0222FF6C
MOD80_0222FF6C: ; 0x0222FF6C
	push {r3, r4, r5, lr}
	sub sp, #0x70
	ldr r5, _02230020 ; =0x022370D8
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x54
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02230024 ; =0x022370BC
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _02230028 ; =0x022370A0
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _0223002C ; =0x02237084
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	add sp, #0x70
	pop {r3, r4, r5, pc}
	nop
_02230020: .word MOD80_022370D8
_02230024: .word MOD80_022370BC
_02230028: .word MOD80_022370A0
_0223002C: .word MOD80_02237084
	thumb_func_end MOD80_0222FF6C

	thumb_func_start MOD80_02230030
MOD80_02230030: ; 0x02230030
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_02230030

	thumb_func_start MOD80_02230054
MOD80_02230054: ; 0x02230054
	push {r3, r4, r5, lr}
	sub sp, #0x10
	mov r1, #0x1a
	add r5, r0, #0
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	ldr r4, [r5, #4]
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x11
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #7
	add r3, r2, #0
	bl FUN_02006930
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD80_02230054

	thumb_func_start MOD80_022300CC
MOD80_022300CC: ; 0x022300CC
	push {r4, lr}
	sub sp, #0x30
	mov r2, #0xcf
	add r4, r0, #0
	lsl r2, r2, #4
	add r0, sp, #0
	add r1, r4, #0
	add r2, r4, r2
	mov r3, #1
	bl MOD80_0222E5E8
	mov r0, #0x32
	lsl r0, r0, #0xe
	str r0, [sp, #8]
	mov r0, #0x3a
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _02230114 ; =0x00000E6C
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _02230114 ; =0x00000E6C
	mov r1, #0x25
	ldr r0, [r4, r0]
	bl FUN_02020130
	bl FUN_02033E74
	add sp, #0x30
	pop {r4, pc}
	nop
_02230114: .word 0x00000E6C
	thumb_func_end MOD80_022300CC

	thumb_func_start MOD80_02230118
MOD80_02230118: ; 0x02230118
	ldr r1, _02230120 ; =0x00000E6C
	ldr r3, _02230124 ; =FUN_0201FFC8
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_02230120: .word 0x00000E6C
_02230124: .word FUN_0201FFC8
	thumb_func_end MOD80_02230118

	thumb_func_start MOD80_02230128
MOD80_02230128: ; 0x02230128
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r0, [sp, #0x14]
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, _022301E4 ; =0x00000E98
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #4]
	add r1, r1, r2
	mov r2, #0
	bl FUN_02019064
	ldr r1, _022301E4 ; =0x00000E98
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	mov r1, #0
	bl FUN_02019620
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x5e
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, _022301E8 ; =0x00000ED8
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #4]
	add r1, r1, r2
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	ldr r1, _022301EC ; =0x00000F08
	ldr r0, [sp, #0x14]
	ldr r4, _022301F0 ; =0x022370F4
	mov r6, #0x86
	mov r7, #0
	add r5, r0, r1
_02230190:
	ldr r0, [r4, #4]
	add r1, r5, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [r4, #8]
	mov r2, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r3, [r4]
	ldr r0, [r0, #4]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	add r7, r7, #1
	mul r0, r1
	add r6, r6, r0
	add r4, #0x10
	add r5, #0x10
	cmp r7, #0xa
	blo _02230190
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022301E4: .word 0x00000E98
_022301E8: .word 0x00000ED8
_022301EC: .word 0x00000F08
_022301F0: .word MOD80_022370F4
	thumb_func_end MOD80_02230128

	thumb_func_start MOD80_022301F4
MOD80_022301F4: ; 0x022301F4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02230220 ; =0x00000E98
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02230224 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02230228 ; =0x00000F08
	mov r4, #0
	add r5, r5, r0
_0223020E:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #0xa
	blo _0223020E
	pop {r3, r4, r5, pc}
	nop
_02230220: .word 0x00000E98
_02230224: .word 0x00000ED8
_02230228: .word 0x00000F08
	thumb_func_end MOD80_022301F4

	thumb_func_start MOD80_0223022C
MOD80_0223022C: ; 0x0223022C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r1, #0x7e
	add r0, #0xc4
	lsl r1, r1, #2
	add r2, r5, r1
	ldr r0, [r0]
	sub r1, #0xd4
	mul r1, r0
	add r4, r2, r1
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _022302B0 ; =0x00000B4C
	str r0, [r5, r1]
	sub r1, #0x1c
	ldr r0, [r5, r1]
	bl FUN_0200B84C
	ldr r0, _022302B4 ; =0x0000011E
	ldrb r2, [r4, r0]
	cmp r2, #0
	beq _02230268
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #8
	bl BufferCountryName
_02230268:
	ldr r2, _022302B8 ; =0x0000011F
	ldrb r3, [r4, r2]
	cmp r3, #0
	beq _02230280
	mov r0, #0xb3
	sub r2, r2, #1
	lsl r0, r0, #4
	ldrb r2, [r4, r2]
	ldr r0, [r5, r0]
	mov r1, #9
	bl BufferCityName
_02230280:
	mov r1, #0xb3
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, r1, #4
	ldr r1, [r5, r1]
	mov r2, #0x4f
	mov r3, #0x3e
	bl ReadMsgData_ExpandPlaceholders
	ldr r1, _022302BC ; =0x00000B54
	mov r2, #0x50
	str r0, [r5, r1]
	add r0, r1, #0
	sub r0, #0x24
	sub r1, #0x20
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	mov r3, #0x3e
	bl ReadMsgData_ExpandPlaceholders
	ldr r1, _022302C0 ; =0x00000B58
	str r0, [r5, r1]
	pop {r3, r4, r5, pc}
	nop
_022302B0: .word 0x00000B4C
_022302B4: .word 0x0000011E
_022302B8: .word 0x0000011F
_022302BC: .word 0x00000B54
_022302C0: .word 0x00000B58
	thumb_func_end MOD80_0223022C

	thumb_func_start MOD80_022302C4
MOD80_022302C4: ; 0x022302C4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022302E4 ; =0x00000B54
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _022302E8 ; =0x00000B58
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _022302EC ; =0x00000B4C
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	nop
_022302E4: .word 0x00000B54
_022302E8: .word 0x00000B58
_022302EC: .word 0x00000B4C
	thumb_func_end MOD80_022302C4

	thumb_func_start MOD80_022302F0
MOD80_022302F0: ; 0x022302F0
	mov r1, #1
	str r1, [r0, #0x2c]
	mov r0, #3
	bx lr
	thumb_func_end MOD80_022302F0

	thumb_func_start MOD80_022302F8
MOD80_022302F8: ; 0x022302F8
	push {r3, r4, r5, lr}
	ldr r1, _02230388 ; =gMain
	mov r2, #1
	ldr r1, [r1, #0x48]
	add r4, r0, #0
	add r3, r1, #0
	tst r3, r2
	beq _02230326
	ldr r1, _0223038C ; =0x00000F0F
	mov r3, #0
	str r1, [sp]
	mov r1, #0x10
	bl MOD80_022304F8
	add r0, r4, #0
	mov r1, #3
	mov r2, #4
	bl MOD80_0222E6DC
	ldr r0, _02230390 ; =0x000005DC
	bl FUN_020054C8
	b _02230384
_02230326:
	mov r3, #2
	add r5, r1, #0
	tst r5, r3
	beq _02230340
	mov r1, #4
	mov r2, #0
	str r3, [r4, #0x2c]
	bl MOD80_0222E7A8
	ldr r0, _02230390 ; =0x000005DC
	bl FUN_020054C8
	b _02230384
_02230340:
	mov r0, #0x10
	tst r0, r1
	beq _02230362
	add r0, r4, #0
	add r0, #0xb6
	ldrh r0, [r0]
	cmp r0, #0
	bne _02230384
	add r0, r4, #0
	add r0, #0xb6
	strh r2, [r0]
	mov r0, #6
	str r0, [r4, #0x2c]
	ldr r0, _02230390 ; =0x000005DC
	bl FUN_020054C8
	b _02230384
_02230362:
	mov r0, #0x20
	tst r0, r1
	beq _02230384
	add r0, r4, #0
	add r0, #0xb6
	ldrh r0, [r0]
	cmp r0, #0
	beq _02230384
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb6
	strh r1, [r0]
	mov r0, #6
	str r0, [r4, #0x2c]
	ldr r0, _02230390 ; =0x000005DC
	bl FUN_020054C8
_02230384:
	mov r0, #3
	pop {r3, r4, r5, pc}
	.align 2, 0
_02230388: .word gMain
_0223038C: .word 0x00000F0F
_02230390: .word 0x000005DC
	thumb_func_end MOD80_022302F8

	thumb_func_start MOD80_02230394
MOD80_02230394: ; 0x02230394
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _022303D0 ; =0x00000B34
	ldr r1, _022303D4 ; =0x00000F78
	ldr r0, [r4, r0]
	add r1, r4, r1
	bl MOD80_02230550
	add r0, r4, #0
	bl MOD80_0223043C
	mov r1, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_022303D0: .word 0x00000B34
_022303D4: .word 0x00000F78
	thumb_func_end MOD80_02230394

	thumb_func_start MOD80_022303D8
MOD80_022303D8: ; 0x022303D8
	push {r4, lr}
	add r4, r0, #0
	mov r2, #0x73
	ldr r0, [r4, #4]
	mov r1, #0xf
	lsl r2, r2, #2
	bl MOD80_0222E6A8
	ldr r1, _022303F4 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #5
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022303F4: .word 0x00000FCC
	thumb_func_end MOD80_022303D8

	thumb_func_start MOD80_022303F8
MOD80_022303F8: ; 0x022303F8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02230438 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02230432
	sub r1, r1, #1
	cmp r0, r1
	bne _02230424
	mov r0, #2
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #4
	mov r2, #0
	bl MOD80_0222E7A8
	b _02230432
_02230424:
	mov r0, #2
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #5
	mov r2, #6
	bl MOD80_0222E7A8
_02230432:
	mov r0, #3
	pop {r4, pc}
	nop
_02230438: .word 0x00000FCC
	thumb_func_end MOD80_022303F8

	thumb_func_start MOD80_0223043C
MOD80_0223043C: ; 0x0223043C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r4, r0, #0
	add r0, #0xb6
	ldrh r0, [r0]
	cmp r0, #0
	bne _0223048C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x68
	mov r1, #0x1b
	bl FUN_020068C8
	ldr r2, _022304BC ; =0x00000B34
	ldr r0, _022304C0 ; =0x00000F98
	mov r3, #0xba
	ldr r1, [r4, r2]
	add r2, r2, #4
	lsl r3, r3, #2
	add r0, r4, r0
	ldr r2, [r4, r2]
	add r3, r4, r3
	add r4, #0xc4
	ldr r5, [r4]
	mov r4, #0x49
	lsl r4, r4, #2
	mul r4, r5
	add r3, r3, r4
	bl MOD80_022305A8
	add sp, #0x10
	pop {r3, r4, r5, pc}
_0223048C:
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0x68
	mov r1, #0x1c
	bl FUN_020068C8
	ldr r2, _022304C4 ; =0x00000B54
	ldr r0, _022304C0 ; =0x00000F98
	ldr r1, [r4, r2]
	add r2, r2, #4
	ldr r2, [r4, r2]
	add r0, r4, r0
	bl MOD80_02230614
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
_022304BC: .word 0x00000B34
_022304C0: .word 0x00000F98
_022304C4: .word 0x00000B54
	thumb_func_end MOD80_0223043C

	thumb_func_start MOD80_022304C8
MOD80_022304C8: ; 0x022304C8
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0223043C
	mov r0, #1
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_022304C8

	thumb_func_start MOD80_022304D8
MOD80_022304D8: ; 0x022304D8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _022304F2
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_022304F2:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_022304D8

	thumb_func_start MOD80_022304F8
MOD80_022304F8: ; 0x022304F8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r2, _02230544 ; =0x00000B34
	add r5, r0, #0
	ldr r0, [r5, r2]
	add r2, #0x18
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	ldr r0, _02230548 ; =0x00000E98
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _02230548 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _02230548 ; =0x00000E98
	ldr r2, _0223054C ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02230544: .word 0x00000B34
_02230548: .word 0x00000E98
_0223054C: .word 0x00000B4C
	thumb_func_end MOD80_022304F8

	thumb_func_start MOD80_02230550
MOD80_02230550: ; 0x02230550
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	mov r1, #0x4a
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r0, r6, #0
	mov r1, #0x4e
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r2, #0
	ldr r0, _022305A4 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	mov r3, #2
	bl MOD80_02236D50
	mov r0, #1
	str r0, [sp]
	ldr r0, _022305A4 ; =0x000F0200
	add r5, #0x10
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	mov r3, #2
	bl MOD80_02236D50
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_022305A4: .word 0x000F0200
	thumb_func_end MOD80_02230550

	thumb_func_start MOD80_022305A8
MOD80_022305A8: ; 0x022305A8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	mov r1, #0
	add r5, r0, #0
	add r7, r2, #0
	add r4, r3, #0
	bl FUN_02019620
	mov r0, #3
	str r0, [sp]
	ldr r0, _02230610 ; =0x000F0200
	mov r3, #0
	str r0, [sp, #4]
	ldrsh r2, [r4, r3]
	add r0, r5, #0
	add r1, r7, #0
	bl MOD80_02233EA4
	mov r0, #3
	str r0, [sp]
	mov r0, #0x46
	str r0, [sp, #4]
	ldr r0, _02230610 ; =0x000F0200
	mov r2, #2
	str r0, [sp, #8]
	ldrsb r2, [r4, r2]
	add r0, r5, #0
	add r1, r6, #0
	mov r3, #0
	bl MOD80_02233EF4
	mov r0, #3
	mov r1, #4
	ldrsb r0, [r4, r0]
	ldrsb r1, [r4, r1]
	bl MOD80_02234668
	add r2, r0, #0
	mov r0, #0x13
	str r0, [sp]
	ldr r0, _02230610 ; =0x000F0200
	add r1, r6, #0
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	add r0, r5, #0
	mov r3, #0
	bl MOD80_02233F5C
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02230610: .word 0x000F0200
	thumb_func_end MOD80_022305A8

	thumb_func_start MOD80_02230614
MOD80_02230614: ; 0x02230614
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	mov r1, #0
	add r6, r0, #0
	add r4, r2, #0
	bl FUN_02019620
	cmp r5, #0
	beq _0223063A
	mov r2, #0
	ldr r0, _02230658 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	add r1, r5, #0
	mov r3, #3
	bl MOD80_02236D50
_0223063A:
	cmp r4, #0
	beq _02230652
	mov r0, #0
	str r0, [sp]
	ldr r0, _02230658 ; =0x000F0200
	add r1, r4, #0
	str r0, [sp, #4]
	add r0, r6, #0
	mov r2, #8
	mov r3, #0x13
	bl MOD80_02236D50
_02230652:
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02230658: .word 0x000F0200
	thumb_func_end MOD80_02230614

	thumb_func_start MOD80_0223065C
MOD80_0223065C: ; 0x0223065C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_02230AC0
	ldr r0, [r4, #4]
	bl MOD80_02230760
	add r0, r4, #0
	bl MOD80_02230840
	add r0, r4, #0
	bl MOD80_02230944
	add r0, r4, #0
	bl MOD80_022308EC
	ldr r1, _02230708 ; =0x00000B34
	ldr r0, _0223070C ; =0x00000F08
	ldr r1, [r4, r1]
	add r0, r4, r0
	bl MOD80_022318D4
	mov r0, #0
	str r0, [sp]
	ldr r0, _02230710 ; =0x00010200
	ldr r2, _02230714 ; =0x00000B38
	str r0, [sp, #4]
	ldr r1, [r4, r2]
	sub r2, #0x16
	ldr r0, _02230718 ; =0x00000F18
	ldrsh r2, [r4, r2]
	add r0, r4, r0
	mov r3, #2
	bl MOD80_02233EA4
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02230710 ; =0x00010200
	ldr r2, _02230708 ; =0x00000B34
	str r0, [sp, #8]
	ldr r1, [r4, r2]
	sub r2, #0x10
	ldr r0, _0223071C ; =0x00000F38
	ldrsb r2, [r4, r2]
	add r0, r4, r0
	mov r3, #1
	bl MOD80_02233EF4
	ldr r1, _02230720 ; =0x00000B25
	ldrsb r0, [r4, r1]
	add r1, r1, #1
	ldrsb r1, [r4, r1]
	bl MOD80_02234668
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, _02230710 ; =0x00010200
	ldr r1, _02230708 ; =0x00000B34
	str r0, [sp, #4]
	ldr r0, _02230724 ; =0x00000F58
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r3, #2
	bl MOD80_02233F9C
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02230708: .word 0x00000B34
_0223070C: .word 0x00000F08
_02230710: .word 0x00010200
_02230714: .word 0x00000B38
_02230718: .word 0x00000F18
_0223071C: .word 0x00000F38
_02230720: .word 0x00000B25
_02230724: .word 0x00000F58
	thumb_func_end MOD80_0223065C

	thumb_func_start MOD80_02230728
MOD80_02230728: ; 0x02230728
	push {r3, lr}
	ldr r1, [r0, #0x2c]
	lsl r2, r1, #2
	ldr r1, _02230738 ; =0x02237A94
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	nop
_02230738: .word MOD80_02237A94
	thumb_func_end MOD80_02230728

	thumb_func_start MOD80_0223073C
MOD80_0223073C: ; 0x0223073C
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_02230934
	add r0, r4, #0
	bl MOD80_02230B2C
	add r0, r4, #0
	bl MOD80_02230A88
	ldr r0, [r4, #4]
	bl MOD80_02230814
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_0223073C

	thumb_func_start MOD80_02230760
MOD80_02230760: ; 0x02230760
	push {r4, r5, lr}
	sub sp, #0x54
	ldr r5, _02230808 ; =0x022371D0
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x38
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _0223080C ; =0x022371EC
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _02230810 ; =0x022371B4
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	add sp, #0x54
	pop {r4, r5, pc}
	nop
_02230808: .word MOD80_022371D0
_0223080C: .word MOD80_022371EC
_02230810: .word MOD80_022371B4
	thumb_func_end MOD80_02230760

	thumb_func_start MOD80_02230814
MOD80_02230814: ; 0x02230814
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_02230814

	thumb_func_start MOD80_02230840
MOD80_02230840: ; 0x02230840
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #3
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #5
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0xd
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x1a
	add r2, r4, #0
	bl FUN_020068C8
	add sp, #0x10
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_02230840

	thumb_func_start MOD80_022308EC
MOD80_022308EC: ; 0x022308EC
	push {r4, lr}
	sub sp, #0x30
	mov r2, #0xcf
	add r4, r0, #0
	lsl r2, r2, #4
	add r0, sp, #0
	add r1, r4, #0
	add r2, r4, r2
	mov r3, #1
	bl MOD80_0222E5E8
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _02230930 ; =0x00000D5C
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _02230930 ; =0x00000D5C
	mov r1, #0
	ldr r0, [r4, r0]
	bl FUN_02020130
	bl FUN_02033E74
	add sp, #0x30
	pop {r4, pc}
	nop
_02230930: .word 0x00000D5C
	thumb_func_end MOD80_022308EC

	thumb_func_start MOD80_02230934
MOD80_02230934: ; 0x02230934
	ldr r1, _0223093C ; =0x00000D5C
	ldr r3, _02230940 ; =FUN_0201FFC8
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_0223093C: .word 0x00000D5C
_02230940: .word FUN_0201FFC8
	thumb_func_end MOD80_02230934

	thumb_func_start MOD80_02230944
MOD80_02230944: ; 0x02230944
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	mov r3, #1
	str r0, [sp, #0x14]
	str r3, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, _02230A6C ; =0x00000EB8
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #4]
	add r1, r1, r2
	mov r2, #0
	bl FUN_02019064
	ldr r1, _02230A6C ; =0x00000EB8
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	mov r1, #0
	bl FUN_02019620
	mov r2, #0
	mov r3, #0xb5
	ldr r0, _02230A70 ; =0x000F0D00
	str r2, [sp]
	str r0, [sp, #4]
	ldr r1, _02230A6C ; =0x00000EB8
	ldr r0, [sp, #0x14]
	lsl r3, r3, #4
	add r0, r0, r1
	ldr r1, [sp, #0x14]
	ldr r1, [r1, r3]
	mov r3, #1
	bl MOD80_02236D1C
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x60
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	ldr r2, _02230A74 ; =0x00000E98
	ldr r1, [sp, #0x14]
	ldr r0, [r0, #4]
	add r1, r1, r2
	mov r2, #0
	bl FUN_02019064
	ldr r1, _02230A74 ; =0x00000E98
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	mov r1, #0
	bl FUN_02019620
	ldr r1, _02230A78 ; =0x00000F08
	ldr r0, [sp, #0x14]
	ldr r4, _02230A7C ; =0x0223719C
	mov r7, #0
	mov r6, #0x96
	add r5, r0, r1
_022309D2:
	ldrh r0, [r4, #2]
	add r1, r5, #0
	mov r2, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldrh r3, [r4]
	ldr r0, [sp, #0x14]
	lsl r3, r3, #0x18
	ldr r0, [r0, #4]
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	add r7, r7, #1
	add r6, #0x16
	add r4, r4, #4
	add r5, #0x10
	cmp r7, #6
	blt _022309D2
	ldr r1, _02230A78 ; =0x00000F08
	ldr r0, [sp, #0x14]
	ldr r6, _02230A80 ; =0x0000011A
	add r0, r0, r1
	ldr r4, _02230A84 ; =0x02237194
	mov r5, #0
	str r0, [sp, #0x18]
_02230A20:
	add r0, r5, #6
	lsl r7, r0, #4
	ldrh r0, [r4, #2]
	ldr r1, [sp, #0x18]
	mov r2, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldrh r3, [r4]
	ldr r0, [sp, #0x14]
	add r1, r1, r7
	lsl r3, r3, #0x18
	ldr r0, [r0, #4]
	lsr r3, r3, #0x18
	bl FUN_02019064
	ldr r0, [sp, #0x18]
	mov r1, #0
	add r0, r0, r7
	bl FUN_02019620
	add r5, r5, #1
	add r6, #0x10
	add r4, r4, #4
	cmp r5, #2
	blt _02230A20
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02230A6C: .word 0x00000EB8
_02230A70: .word 0x000F0D00
_02230A74: .word 0x00000E98
_02230A78: .word 0x00000F08
_02230A7C: .word MOD80_0223719C
_02230A80: .word 0x0000011A
_02230A84: .word MOD80_02237194
	thumb_func_end MOD80_02230944

	thumb_func_start MOD80_02230A88
MOD80_02230A88: ; 0x02230A88
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _02230AB4 ; =0x00000E98
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02230AB8 ; =0x00000EB8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02230ABC ; =0x00000F08
	mov r4, #0
	add r5, r5, r0
_02230AA2:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #8
	blt _02230AA2
	pop {r3, r4, r5, pc}
	nop
_02230AB4: .word 0x00000E98
_02230AB8: .word 0x00000EB8
_02230ABC: .word 0x00000F08
	thumb_func_end MOD80_02230A88

	thumb_func_start MOD80_02230AC0
MOD80_02230AC0: ; 0x02230AC0
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _02230B28 ; =0x00000B4C
	str r0, [r4, r1]
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0x29
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #0x3e
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0xfe
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0
	mov r2, #0x30
	bl MIi_CpuClearFast
	mov r2, #0xfe
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	mov r0, #0x3e
	mov r1, #0
	add r2, #0x1c
	bl MOD80_02234204
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	str r0, [r1, #0x18]
	mov r0, #0x3e
	bl MOD80_02234228
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	add r1, #0x38
	str r0, [r2, #0x14]
	add r0, r4, r1
	bl MOD80_022346D8
	pop {r4, pc}
	.align 2, 0
_02230B28: .word 0x00000B4C
	thumb_func_end MOD80_02230AC0

	thumb_func_start MOD80_02230B2C
MOD80_02230B2C: ; 0x02230B2C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x14]
	bl FreeToHeap
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x18]
	bl FreeToHeap
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _02230B68 ; =0x00000B4C
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0xb5
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	nop
_02230B68: .word 0x00000B4C
	thumb_func_end MOD80_02230B2C

	thumb_func_start MOD80_02230B6C
MOD80_02230B6C: ; 0x02230B6C
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02230B90 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #8
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02230B90: .word 0x00000F0F
	thumb_func_end MOD80_02230B6C

	thumb_func_start MOD80_02230B94
MOD80_02230B94: ; 0x02230B94
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD80_02231008
	ldr r0, _02230CB4 ; =gMain
	mov r2, #1
	ldr r1, [r0, #0x48]
	add r0, r1, #0
	tst r0, r2
	beq _02230C44
	add r0, r4, #0
	bl MOD80_02230FF0
	cmp r0, #4
	bhi _02230CAE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02230BBE: ; jump table
	.short _02230BC8 - _02230BBE - 2 ; case 0
	.short _02230BD4 - _02230BBE - 2 ; case 1
	.short _02230C10 - _02230BBE - 2 ; case 2
	.short _02230C1C - _02230BBE - 2 ; case 3
	.short _02230C22 - _02230BBE - 2 ; case 4
_02230BC8:
	mov r0, #3
	str r0, [r4, #0x2c]
	ldr r0, _02230CB8 ; =0x000005DC
	bl FUN_020054C8
	b _02230CAE
_02230BD4:
	ldr r0, _02230CBC ; =0x00000B22
	ldrsh r0, [r4, r0]
	cmp r0, #0
	beq _02230C04
	mov r1, #0x12 ; BASE_GENDER_RATIO
	bl GetMonBaseStat
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	str r0, [r2, #0x20]
	ldr r1, [r4, r1]
	ldr r0, _02230CBC ; =0x00000B22
	ldr r1, [r1, #0x20]
	add r0, r4, r0
	bl MOD80_022338E0
	cmp r0, #0
	beq _02230C04
	ldr r0, _02230CB8 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #3
	pop {r3, r4, r5, pc}
_02230C04:
	mov r0, #8
	str r0, [r4, #0x2c]
	ldr r0, _02230CB8 ; =0x000005DC
	bl FUN_020054C8
	b _02230CAE
_02230C10:
	mov r0, #0xb
	str r0, [r4, #0x2c]
	ldr r0, _02230CB8 ; =0x000005DC
	bl FUN_020054C8
	b _02230CAE
_02230C1C:
	mov r0, #0xe
	str r0, [r4, #0x2c]
	b _02230CAE
_02230C22:
	ldr r0, _02230CC0 ; =0x00000F0F
	mov r1, #0xf
	str r0, [sp]
	add r0, r4, #0
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #0x16
	bl MOD80_0222E6DC
	ldr r0, _02230CB8 ; =0x000005DC
	bl FUN_020054C8
	b _02230CAE
_02230C44:
	mov r0, #2
	tst r0, r1
	beq _02230C6A
	ldr r0, _02230CC0 ; =0x00000F0F
	mov r1, #0xf
	str r0, [sp]
	add r0, r4, #0
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #0x16
	bl MOD80_0222E6DC
	ldr r0, _02230CB8 ; =0x000005DC
	bl FUN_020054C8
	b _02230CAE
_02230C6A:
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	bl MOD80_02235B70
	add r5, r0, #0
	ldr r0, _02230CC4 ; =0x00000FEE
	ldrh r0, [r4, r0]
	cmp r0, #0
	beq _02230CAE
	cmp r5, #0
	blt _02230CAE
	add r0, r5, #1
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0xe7
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r1, r5, #2
	add r1, #0x10
	bl FUN_02020130
	mov r0, #2
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #3
	mov r2, #0
	bl MOD80_0222E7A8
	add r4, #0xc4
	ldr r0, _02230CB8 ; =0x000005DC
	str r5, [r4]
	bl FUN_020054C8
_02230CAE:
	mov r0, #3
	pop {r3, r4, r5, pc}
	nop
_02230CB4: .word gMain
_02230CB8: .word 0x000005DC
_02230CBC: .word 0x00000B22
_02230CC0: .word 0x00000F0F
_02230CC4: .word 0x00000FEE
	thumb_func_end MOD80_02230B94

	thumb_func_start MOD80_02230CC8
MOD80_02230CC8: ; 0x02230CC8
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02230D54 ; =0x00000B22
	add r4, r0, #0
	ldrsh r2, [r4, r1]
	cmp r2, #0
	bne _02230CF6
	ldr r1, _02230D58 ; =0x00000F0F
	mov r2, #1
	str r1, [sp]
	mov r1, #0xc
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	ldr r0, _02230D5C ; =0x000005F3
	bl FUN_020054C8
	b _02230D4C
_02230CF6:
	add r0, r4, r1
	add r1, r1, #6
	add r1, r4, r1
	bl MOD80_022319C0
	cmp r0, #0
	beq _02230D26
	ldr r0, _02230D58 ; =0x00000F0F
	mov r1, #0x21
	str r0, [sp]
	add r0, r4, #0
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	ldr r0, _02230D5C ; =0x000005F3
	bl FUN_020054C8
	b _02230D4C
_02230D26:
	ldr r0, _02230D60 ; =0x000005FF
	bl FUN_020054C8
	ldr r0, _02230D58 ; =0x00000F0F
	mov r1, #0xd
	str r0, [sp]
	add r0, r4, #0
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #0xf
	bl MOD80_0222E6DC
	add r0, r4, #0
	bl MOD80_02235C40
_02230D4C:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_02230D54: .word 0x00000B22
_02230D58: .word 0x00000F0F
_02230D5C: .word 0x000005F3
_02230D60: .word 0x000005FF
	thumb_func_end MOD80_02230CC8

	thumb_func_start MOD80_02230D64
MOD80_02230D64: ; 0x02230D64
	push {r3, r4, lr}
	sub sp, #0x2c
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_0202AC08
	lsr r1, r0, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x1c]
	lsr r1, r0, #0x10
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x20]
	lsr r1, r0, #8
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	str r1, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, sp, #0xc
	add r1, sp, #0
	bl MOD04_021DE1F8
	add r0, sp, #0xc
	bl RTC_ConvertDateToDay
	add r4, r0, #0
	add r0, sp, #0x1c
	bl RTC_ConvertDateToDay
	sub r0, r4, r0
	bmi _02230DB2
	cmp r0, #3
	bge _02230DB2
	add sp, #0x2c
	mov r0, #1
	pop {r3, r4, pc}
_02230DB2:
	mov r0, #0
	add sp, #0x2c
	pop {r3, r4, pc}
	thumb_func_end MOD80_02230D64

	thumb_func_start MOD80_02230DB8
MOD80_02230DB8: ; 0x02230DB8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrh r0, [r5, #0x36]
	mov r4, #3
	cmp r0, #0
	beq _02230DC6
	add r4, r4, #2
_02230DC6:
	add r0, r5, #0
	bl MOD80_02230D64
	cmp r0, #0
	beq _02230DD2
	add r4, r4, #2
_02230DD2:
	ldr r0, _02230E0C ; =0x00000B22
	mov r2, #0x7e
	lsl r2, r2, #2
	add r0, r5, r0
	add r1, r4, #0
	add r2, r5, r2
	bl MOD80_0222DD90
	ldr r1, _02230E0C ; =0x00000B22
	ldrh r2, [r5, r1]
	add r0, r1, #6
	strh r2, [r5, r0]
	add r0, r1, #2
	ldrh r2, [r5, r0]
	add r0, r1, #0
	add r0, #8
	strh r2, [r5, r0]
	add r0, r1, #4
	ldrh r0, [r5, r0]
	add r1, #0xa
	strh r0, [r5, r1]
	mov r0, #0x10
	str r0, [r5, #0x2c]
	ldr r0, _02230E10 ; =0x00000FEE
	mov r1, #0
	strh r1, [r5, r0]
	mov r0, #3
	pop {r3, r4, r5, pc}
	nop
_02230E0C: .word 0x00000B22
_02230E10: .word 0x00000FEE
	thumb_func_end MOD80_02230DB8

	thumb_func_start MOD80_02230E14
MOD80_02230E14: ; 0x02230E14
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02230E94
	bl MOD80_0222DBB8
	add r5, r0, #0
	add r0, #0xf
	cmp r0, #0x16
	bhi _02230E94
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02230E38: ; jump table
	.short _02230E90 - _02230E38 - 2 ; case 0
	.short _02230E84 - _02230E38 - 2 ; case 1
	.short _02230E8A - _02230E38 - 2 ; case 2
	.short _02230E90 - _02230E38 - 2 ; case 3
	.short _02230E94 - _02230E38 - 2 ; case 4
	.short _02230E94 - _02230E38 - 2 ; case 5
	.short _02230E94 - _02230E38 - 2 ; case 6
	.short _02230E94 - _02230E38 - 2 ; case 7
	.short _02230E94 - _02230E38 - 2 ; case 8
	.short _02230E94 - _02230E38 - 2 ; case 9
	.short _02230E94 - _02230E38 - 2 ; case 10
	.short _02230E94 - _02230E38 - 2 ; case 11
	.short _02230E94 - _02230E38 - 2 ; case 12
	.short _02230E84 - _02230E38 - 2 ; case 13
	.short _02230E94 - _02230E38 - 2 ; case 14
	.short _02230E66 - _02230E38 - 2 ; case 15
	.short _02230E66 - _02230E38 - 2 ; case 16
	.short _02230E66 - _02230E38 - 2 ; case 17
	.short _02230E66 - _02230E38 - 2 ; case 18
	.short _02230E66 - _02230E38 - 2 ; case 19
	.short _02230E66 - _02230E38 - 2 ; case 20
	.short _02230E66 - _02230E38 - 2 ; case 21
	.short _02230E66 - _02230E38 - 2 ; case 22
_02230E66:
	add r0, r4, #0
	add r0, #0xc0
	str r5, [r0]
	ldr r0, _02230E98 ; =0x000005FF
	mov r1, #0
	bl FUN_020054F0
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #1
	bl MOD80_02235B90
	mov r0, #0x11
	str r0, [r4, #0x2c]
	b _02230E94
_02230E84:
	mov r0, #0x1a
	str r0, [r4, #0x2c]
	b _02230E94
_02230E8A:
	bl FUN_020335E0
	b _02230E94
_02230E90:
	mov r0, #0x13
	str r0, [r4, #0x2c]
_02230E94:
	mov r0, #3
	pop {r3, r4, r5, pc}
	.align 2, 0
_02230E98: .word 0x000005FF
	thumb_func_end MOD80_02230E14

	thumb_func_start MOD80_02230E9C
MOD80_02230E9C: ; 0x02230E9C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0xc0
	ldr r1, [r1]
	cmp r1, #0
	ldr r1, _02230EF0 ; =0x00000F0F
	bne _02230ECC
	str r1, [sp]
	mov r1, #0xe
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	ldr r0, _02230EF4 ; =0x000005F3
	bl FUN_020054C8
	b _02230EE8
_02230ECC:
	str r1, [sp]
	mov r1, #0x1e
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #0x12
	bl MOD80_0222E6DC
	ldr r0, _02230EF8 ; =0x00000FDC
	mov r1, #0
	str r1, [r4, r0]
_02230EE8:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_02230EF0: .word 0x00000F0F
_02230EF4: .word 0x000005F3
_02230EF8: .word 0x00000FDC
	thumb_func_end MOD80_02230E9C

	thumb_func_start MOD80_02230EFC
MOD80_02230EFC: ; 0x02230EFC
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02230F34 ; =0x00000FDC
	add r4, r0, #0
	ldr r2, [r4, r1]
	add r2, r2, #1
	str r2, [r4, r1]
	ldr r2, [r4, r1]
	cmp r2, #0x2d
	ble _02230F2E
	sub r1, #0xcd
	str r1, [sp]
	mov r1, #0x20
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	ldr r0, _02230F38 ; =0x00000FEE
	mov r1, #1
	strh r1, [r4, r0]
_02230F2E:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02230F34: .word 0x00000FDC
_02230F38: .word 0x00000FEE
	thumb_func_end MOD80_02230EFC

	thumb_func_start MOD80_02230F3C
MOD80_02230F3C: ; 0x02230F3C
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02230F6C ; =0x00000B28
	add r4, r0, #0
	mov r3, #0
	strh r3, [r4, r1]
	ldr r1, _02230F70 ; =0x00000F0F
	mov r2, #1
	str r1, [sp]
	mov r1, #0x26
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	ldr r0, _02230F74 ; =0x000005F3
	bl FUN_020054C8
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_02230F6C: .word 0x00000B28
_02230F70: .word 0x00000F0F
_02230F74: .word 0x000005F3
	thumb_func_end MOD80_02230F3C

	thumb_func_start MOD80_02230F78
MOD80_02230F78: ; 0x02230F78
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02230FA8 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x8f
	mov r2, #4
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x15
	mov r2, #0x1b
	bl MOD80_0222E6DC
	ldr r0, _02230FAC ; =0x00000FDC
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, _02230FB0 ; =0x000005F3
	bl FUN_020054C8
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02230FA8: .word 0x00000F0F
_02230FAC: .word 0x00000FDC
_02230FB0: .word 0x000005F3
	thumb_func_end MOD80_02230F78

	thumb_func_start MOD80_02230FB4
MOD80_02230FB4: ; 0x02230FB4
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02230FE8 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x94
	mov r2, #4
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x15
	mov r2, #2
	bl MOD80_0222E6DC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	ldr r0, _02230FEC ; =0x000005F3
	bl FUN_020054C8
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02230FE8: .word 0x00000F0F
_02230FEC: .word 0x000005F3
	thumb_func_end MOD80_02230FB4

	thumb_func_start MOD80_02230FF0
MOD80_02230FF0: ; 0x02230FF0
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r1, [r0, r1]
	ldr r0, [r1, #0x24]
	cmp r0, #0
	bne _02231000
	ldr r0, [r1, #0x28]
	bx lr
_02231000:
	ldr r0, [r1, #0x2c]
	add r0, r0, #3
	bx lr
	.align 2, 0
	thumb_func_end MOD80_02230FF0

	thumb_func_start MOD80_02231008
MOD80_02231008: ; 0x02231008
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _02231100 ; =gMain
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _0223104E
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	ldr r0, [r1, #0x24]
	cmp r0, #0
	bne _02231036
	ldr r0, [r1, #0x28]
	cmp r0, #0
	ble _022310D0
	sub r0, r0, #1
	str r0, [r1, #0x28]
	ldr r0, _02231104 ; =0x000005DC
	bl FUN_020054C8
	b _022310D0
_02231036:
	ldr r0, [r1, #0x2c]
	cmp r0, #0
	beq _02231042
	ldr r0, _02231104 ; =0x000005DC
	bl FUN_020054C8
_02231042:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	str r1, [r0, #0x2c]
	b _022310D0
_0223104E:
	mov r1, #0x80
	tst r1, r0
	beq _0223108A
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	ldr r0, [r1, #0x24]
	cmp r0, #0
	bne _02231072
	ldr r0, [r1, #0x28]
	cmp r0, #2
	bge _022310D0
	add r0, r0, #1
	str r0, [r1, #0x28]
	ldr r0, _02231104 ; =0x000005DC
	bl FUN_020054C8
	b _022310D0
_02231072:
	ldr r0, [r1, #0x2c]
	cmp r0, #1
	beq _0223107E
	ldr r0, _02231104 ; =0x000005DC
	bl FUN_020054C8
_0223107E:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	str r1, [r0, #0x2c]
	b _022310D0
_0223108A:
	mov r1, #0x10
	tst r1, r0
	beq _022310AE
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x24]
	cmp r0, #1
	beq _022310A2
	ldr r0, _02231104 ; =0x000005DC
	bl FUN_020054C8
_022310A2:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	str r1, [r0, #0x24]
	b _022310D0
_022310AE:
	mov r1, #0x20
	tst r0, r1
	beq _022310D0
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	beq _022310C6
	ldr r0, _02231104 ; =0x000005DC
	bl FUN_020054C8
_022310C6:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	str r1, [r0, #0x24]
_022310D0:
	add r0, r4, #0
	bl MOD80_02230FF0
	lsl r1, r0, #2
	ldr r0, _02231108 ; =0x02237A80
	ldrh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	bl MOD80_02230FF0
	lsl r1, r0, #2
	ldr r0, _0223110C ; =0x02237A82
	ldrh r0, [r0, r1]
	add r1, sp, #0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r0, _02231110 ; =0x00000D5C
	ldr r0, [r4, r0]
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02231100: .word gMain
_02231104: .word 0x000005DC
_02231108: .word MOD80_02237A80
_0223110C: .word MOD80_02237A82
_02231110: .word 0x00000D5C
	thumb_func_end MOD80_02231008

	thumb_func_start MOD80_02231114
MOD80_02231114: ; 0x02231114
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	mov r0, #6
	mov r1, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD80_02231114

	thumb_func_start MOD80_0223113C
MOD80_0223113C: ; 0x0223113C
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r1, _022311B4 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #9
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #4
	bl MOD80_0222E6DC
	mov r0, #5
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _022311B8 ; =0x0000013A
	ldr r1, _022311BC ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0xf
	bl FUN_02019064
	ldr r0, _022311BC ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #5
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _022311C0 ; =0x0000016E
	ldr r1, _022311C4 ; =0x00000EE8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	ldr r0, _022311C4 ; =0x00000EE8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_022311B4: .word 0x00000F0F
_022311B8: .word 0x0000013A
_022311BC: .word 0x00000ED8
_022311C0: .word 0x0000016E
_022311C4: .word 0x00000EE8
	thumb_func_end MOD80_0223113C

	thumb_func_start MOD80_022311C8
MOD80_022311C8: ; 0x022311C8
	push {r4, lr}
	ldr r2, _022311F0 ; =0x00000FC8
	add r4, r0, #0
	ldr r3, _022311F4 ; =0x00000B34
	add r1, r4, r2
	sub r2, #0xf0
	ldr r3, [r4, r3]
	add r2, r4, r2
	bl MOD80_02234370
	ldr r1, _022311F8 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _022311FC ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #5
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022311F0: .word 0x00000FC8
_022311F4: .word 0x00000B34
_022311F8: .word 0x00000FD4
_022311FC: .word 0x0000FFFF
	thumb_func_end MOD80_022311C8

	thumb_func_start MOD80_02231200
MOD80_02231200: ; 0x02231200
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022312B4 ; =0x00000FD4
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0xb0
	bl MOD80_02234698
	cmp r0, #0xa
	bhi _02231236
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02231220: ; jump table
	.short _022312AE - _02231220 - 2 ; case 0
	.short _02231240 - _02231220 - 2 ; case 1
	.short _02231240 - _02231220 - 2 ; case 2
	.short _02231240 - _02231220 - 2 ; case 3
	.short _02231240 - _02231220 - 2 ; case 4
	.short _02231240 - _02231220 - 2 ; case 5
	.short _02231240 - _02231220 - 2 ; case 6
	.short _02231240 - _02231220 - 2 ; case 7
	.short _02231240 - _02231220 - 2 ; case 8
	.short _02231240 - _02231220 - 2 ; case 9
	.short _02231240 - _02231220 - 2 ; case 10
_02231236:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _02231266
	b _022312AE
_02231240:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #6
	ldr r0, [r4, r0]
	add r2, r2, #4
	bl FUN_02001300
	ldr r0, _022312B8 ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _022312BC ; =0x000005DC
	bl FUN_020054C8
	mov r0, #6
	str r0, [r4, #0x2c]
	b _022312AE
_02231266:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #6
	ldr r0, [r4, r0]
	add r2, r2, #4
	bl FUN_02001300
	ldr r0, _022312B8 ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _022312C0 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _022312C4 ; =0x00000E98
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200D0E0
	ldr r0, _022312C0 ; =0x00000ED8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _022312C8 ; =0x00000EE8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _022312BC ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0
	str r0, [r4, #0x2c]
_022312AE:
	mov r0, #3
	pop {r4, pc}
	nop
_022312B4: .word 0x00000FD4
_022312B8: .word 0x00000FC8
_022312BC: .word 0x000005DC
_022312C0: .word 0x00000ED8
_022312C4: .word 0x00000E98
_022312C8: .word 0x00000EE8
	thumb_func_end MOD80_02231200

	thumb_func_start MOD80_022312CC
MOD80_022312CC: ; 0x022312CC
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r3, _02231310 ; =0x00000B38
	add r4, r0, #0
	ldr r1, [r4, r3]
	mov r2, #0xfe
	lsl r2, r2, #4
	str r1, [sp]
	ldr r1, [r4, r2]
	sub r3, r3, #4
	str r1, [sp, #4]
	ldr r1, [r4]
	ldr r1, [r1, #0x10]
	str r1, [sp, #8]
	add r1, r2, #0
	sub r1, #0x18
	sub r2, #0xf8
	ldr r3, [r4, r3]
	add r1, r4, r1
	add r2, r4, r2
	bl MOD80_022344DC
	ldr r1, _02231314 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _02231318 ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #7
	str r0, [r4, #0x2c]
	mov r0, #3
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02231310: .word 0x00000B38
_02231314: .word 0x00000FD4
_02231318: .word 0x0000FFFF
	thumb_func_end MOD80_022312CC

	thumb_func_start MOD80_0223131C
MOD80_0223131C: ; 0x0223131C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _02231464 ; =0x00000FD4
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0xb0
	bl MOD80_02234698
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _02231342
	add r0, r0, #1
	cmp r5, r0
	bne _02231340
	b _0223145C
_02231340:
	b _0223138C
_02231342:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #0
	ldr r0, [r4, r0]
	add r1, #0xa
	add r2, #8
	bl FUN_02001300
	ldr r0, _02231468 ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _0223146C ; =0x00000EE8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _02231470 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #4
	str r0, [r4, #0x2c]
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r3, [r4, r0]
	add r0, #0x38
	ldrh r2, [r3, #6]
	ldrh r1, [r3, #4]
	add r0, r4, r0
	add r1, r2, r1
	ldrh r2, [r3, #0xa]
	ldrh r3, [r3, #8]
	bl MOD80_022346F0
	b _0223145C
_0223138C:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #0
	ldr r0, [r4, r0]
	add r1, #0xa
	add r2, #8
	bl FUN_02001300
	ldr r0, _02231468 ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _02231474 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _0223146C ; =0x00000EE8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _02231474 ; =0x00000ED8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _0223146C ; =0x00000EE8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02231478 ; =0x00000B22
	strh r5, [r4, r0]
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r0, _02231470 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0223147C ; =0x00000F18
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #0
	str r0, [sp]
	ldr r0, _02231480 ; =0x00010200
	ldr r1, _02231484 ; =0x00000B38
	str r0, [sp, #4]
	ldr r0, _0223147C ; =0x00000F18
	ldr r1, [r4, r1]
	add r0, r4, r0
	add r2, r5, #0
	mov r3, #2
	bl MOD80_02233EA4
	add r0, r5, #0
	mov r1, #0x12 ; BASE_GENDER_RATIO
	bl GetMonBaseStat
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	str r0, [r2, #0x20]
	ldr r3, [r4, r1]
	add r1, #0x38
	add r0, r4, r1
	ldrh r2, [r3, #6]
	ldrh r1, [r3, #4]
	add r1, r2, r1
	ldrh r2, [r3, #0xa]
	ldrh r3, [r3, #8]
	bl MOD80_022346F0
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	ldr r0, _02231478 ; =0x00000B22
	ldr r1, [r1, #0x20]
	add r0, r4, r0
	bl MOD80_022338E0
	cmp r0, #0
	beq _0223145C
	ldr r0, _02231488 ; =0x00000F38
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _02231480 ; =0x00010200
	ldr r2, _0223148C ; =0x00000B34
	str r0, [sp, #8]
	ldr r1, [r4, r2]
	sub r2, #0x10
	ldr r0, _02231488 ; =0x00000F38
	ldrsb r2, [r4, r2]
	add r0, r4, r0
	mov r3, #1
	bl MOD80_02233EF4
_0223145C:
	mov r0, #3
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02231464: .word 0x00000FD4
_02231468: .word 0x00000FC8
_0223146C: .word 0x00000EE8
_02231470: .word 0x000005DC
_02231474: .word 0x00000ED8
_02231478: .word 0x00000B22
_0223147C: .word 0x00000F18
_02231480: .word 0x00010200
_02231484: .word 0x00000B38
_02231488: .word 0x00000F38
_0223148C: .word 0x00000B34
	thumb_func_end MOD80_0223131C

	thumb_func_start MOD80_02231490
MOD80_02231490: ; 0x02231490
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r1, _022314E0 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #9
	bl MOD80_0222E6DC
	mov r0, #0xa
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _022314E4 ; =0x0000013A
	ldr r1, _022314E8 ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	ldr r0, _022314E8 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_022314E0: .word 0x00000F0F
_022314E4: .word 0x0000013A
_022314E8: .word 0x00000ED8
	thumb_func_end MOD80_02231490

	thumb_func_start MOD80_022314EC
MOD80_022314EC: ; 0x022314EC
	push {r4, lr}
	ldr r1, _02231514 ; =0x00000FC8
	add r4, r0, #0
	ldr r2, _02231518 ; =0x00000B34
	add r0, r4, r1
	sub r1, #0xf0
	ldr r2, [r4, r2]
	add r1, r4, r1
	bl MOD80_02234560
	ldr r1, _0223151C ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _02231520 ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #0xa
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02231514: .word 0x00000FC8
_02231518: .word 0x00000B34
_0223151C: .word 0x00000FD4
_02231520: .word 0x0000FFFF
	thumb_func_end MOD80_022314EC

	thumb_func_start MOD80_02231524
MOD80_02231524: ; 0x02231524
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _022315F0 ; =0x00000FD4
	add r1, r5, #0
	ldr r0, [r5, r0]
	add r1, #0xb0
	bl MOD80_02234698
	add r4, r0, #0
	cmp r4, #2
	bhi _0223154A
	cmp r4, #0
	beq _0223158E
	cmp r4, #1
	beq _0223158E
	cmp r4, #2
	beq _0223158E
	b _022315EA
_0223154A:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _022315EA
	ldr r0, _022315F0 ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _022315F4 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _022315F8 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _022315FC ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200D0E0
	ldr r0, _022315F8 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02231600 ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0
	str r0, [r5, #0x2c]
	b _022315EA
_0223158E:
	ldr r0, _022315F0 ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _022315F4 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _022315F8 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _022315F8 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02231600 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02231604 ; =0x00000B24
	add r1, r4, #1
	strb r1, [r5, r0]
	ldr r0, _02231608 ; =0x00000F38
	mov r1, #0
	add r0, r5, r0
	str r1, [r5, #0x2c]
	bl FUN_02019620
	mov r0, #0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	ldr r0, _0223160C ; =0x00010200
	ldr r2, _02231610 ; =0x00000B34
	str r0, [sp, #8]
	ldr r1, [r5, r2]
	sub r2, #0x10
	ldr r0, _02231608 ; =0x00000F38
	ldrsb r2, [r5, r2]
	add r0, r5, r0
	mov r3, #1
	bl MOD80_02233EF4
_022315EA:
	mov r0, #3
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022315F0: .word 0x00000FD4
_022315F4: .word 0x00000FC8
_022315F8: .word 0x00000ED8
_022315FC: .word 0x00000E98
_02231600: .word 0x000005DC
_02231604: .word 0x00000B24
_02231608: .word 0x00000F38
_0223160C: .word 0x00010200
_02231610: .word 0x00000B34
	thumb_func_end MOD80_02231524

	thumb_func_start MOD80_02231614
MOD80_02231614: ; 0x02231614
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r1, _02231664 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0xb
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #0xc
	bl MOD80_0222E6DC
	mov r0, #5
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _02231668 ; =0x0000013A
	ldr r1, _0223166C ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0xf
	bl FUN_02019064
	ldr r0, _0223166C ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02231664: .word 0x00000F0F
_02231668: .word 0x0000013A
_0223166C: .word 0x00000ED8
	thumb_func_end MOD80_02231614

	thumb_func_start MOD80_02231670
MOD80_02231670: ; 0x02231670
	push {r4, lr}
	ldr r1, _02231698 ; =0x00000FC8
	add r4, r0, #0
	ldr r2, _0223169C ; =0x00000B34
	add r0, r4, r1
	sub r1, #0xf0
	ldr r2, [r4, r2]
	add r1, r4, r1
	bl MOD80_022345D0
	ldr r1, _022316A0 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _022316A4 ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #0xd
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02231698: .word 0x00000FC8
_0223169C: .word 0x00000B34
_022316A0: .word 0x00000FD4
_022316A4: .word 0x0000FFFF
	thumb_func_end MOD80_02231670

	thumb_func_start MOD80_022316A8
MOD80_022316A8: ; 0x022316A8
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _0223176C ; =0x00000FD4
	add r1, r5, #0
	ldr r0, [r5, r0]
	add r1, #0xb0
	bl MOD80_02234698
	add r4, r0, #0
	cmp r4, #0xc
	beq _022316D0
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _022316D0
	add r0, r0, #1
	cmp r4, r0
	beq _02231766
	b _0223170C
_022316D0:
	ldr r0, _0223176C ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _02231770 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02231774 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02231778 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200D0E0
	ldr r0, _02231774 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _0223177C ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0
	str r0, [r5, #0x2c]
	b _02231766
_0223170C:
	ldr r0, _0223176C ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _02231770 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02231774 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02231774 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _0223177C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02231780 ; =0x00000B22
	add r1, r4, #0
	add r0, r5, r0
	bl MOD80_02234640
	ldr r0, _02231784 ; =0x00000F58
	mov r1, #0
	add r0, r5, r0
	str r1, [r5, #0x2c]
	bl FUN_02019620
	mov r0, #0
	str r0, [sp]
	ldr r0, _02231788 ; =0x00010200
	ldr r1, _0223178C ; =0x00000B34
	str r0, [sp, #4]
	ldr r0, _02231784 ; =0x00000F58
	ldr r1, [r5, r1]
	add r0, r5, r0
	add r2, r4, #0
	mov r3, #2
	bl MOD80_02233F9C
_02231766:
	mov r0, #3
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223176C: .word 0x00000FD4
_02231770: .word 0x00000FC8
_02231774: .word 0x00000ED8
_02231778: .word 0x00000E98
_0223177C: .word 0x000005DC
_02231780: .word 0x00000B22
_02231784: .word 0x00000F58
_02231788: .word 0x00010200
_0223178C: .word 0x00000B34
	thumb_func_end MOD80_022316A8

	thumb_func_start MOD80_02231790
MOD80_02231790: ; 0x02231790
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _022317AC ; =0x0000020A
	mov r1, #0xf
	bl MOD80_0222E6A8
	ldr r1, _022317B0 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #0x17
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	nop
_022317AC: .word 0x0000020A
_022317B0: .word 0x00000FCC
	thumb_func_end MOD80_02231790

	thumb_func_start MOD80_022317B4
MOD80_022317B4: ; 0x022317B4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022317F4 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _022317F0
	sub r1, r1, #1
	cmp r0, r1
	bne _022317D6
	mov r0, #0
	str r0, [r4, #0x2c]
	b _022317F0
_022317D6:
	mov r0, #2
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	add r0, r4, #0
	bl MOD80_02235C40
	mov r0, #0
	add r4, #0xc0
	str r0, [r4]
_022317F0:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022317F4: .word 0x00000FCC
	thumb_func_end MOD80_022317B4

	thumb_func_start MOD80_022317F8
MOD80_022317F8: ; 0x022317F8
	mov r1, #1
	str r1, [r0, #0x2c]
	mov r0, #3
	bx lr
	thumb_func_end MOD80_022317F8

	thumb_func_start MOD80_02231800
MOD80_02231800: ; 0x02231800
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02231824 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x8e
	mov r2, #1
	mov r3, #0
	bl MOD80_0223187C
	add r0, r4, #0
	mov r1, #0x14
	mov r2, #1
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02231824: .word 0x00000F0F
	thumb_func_end MOD80_02231800

	thumb_func_start MOD80_02231828
MOD80_02231828: ; 0x02231828
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02231842
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02231842:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02231828

	thumb_func_start MOD80_02231848
MOD80_02231848: ; 0x02231848
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02231874
	ldr r0, _02231878 ; =0x00000FDC
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0x2d
	ble _02231874
	mov r1, #0
	str r1, [r4, r0]
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02231874:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02231878: .word 0x00000FDC
	thumb_func_end MOD80_02231848

	thumb_func_start MOD80_0223187C
MOD80_0223187C: ; 0x0223187C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r2, #0
	ldr r2, _022318C8 ; =0x00000B34
	add r5, r0, #0
	ldr r0, [r5, r2]
	add r2, #0x18
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
	ldr r0, _022318CC ; =0x00000E98
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _022318CC ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _022318CC ; =0x00000E98
	ldr r2, _022318D0 ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022318C8: .word 0x00000B34
_022318CC: .word 0x00000E98
_022318D0: .word 0x00000B4C
	thumb_func_end MOD80_0223187C

	thumb_func_start MOD80_022318D4
MOD80_022318D4: ; 0x022318D4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x3b
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r2, #0
	ldr r0, _022319B8 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	mov r1, #0x3d
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r2, #0
	ldr r0, _022319B8 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x20
	add r1, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	mov r1, #0x3f
	bl NewString_ReadMsgData
	add r6, r0, #0
	mov r2, #0
	ldr r0, _022319B8 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x40
	add r1, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	mov r1, #0x41
	bl NewString_ReadMsgData
	add r6, r0, #0
	add r3, r5, #0
	add r3, #0x67
	ldrb r3, [r3]
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	lsl r3, r3, #3
	bl FUN_02002F40
	add r2, r0, #0
	mov r3, #0
	ldr r0, _022319BC ; =0x00010200
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x60
	add r1, r6, #0
	bl MOD80_02236D50
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	mov r1, #0x42
	bl NewString_ReadMsgData
	add r4, r0, #0
	add r3, r5, #0
	add r3, #0x77
	ldrb r3, [r3]
	mov r0, #0
	add r1, r4, #0
	add r2, r0, #0
	lsl r3, r3, #3
	bl FUN_02002F40
	add r2, r0, #0
	mov r3, #0
	ldr r0, _022319BC ; =0x00010200
	str r3, [sp]
	add r5, #0x70
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD80_02236D50
	add r0, r4, #0
	bl String_dtor
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_022319B8: .word 0x000F0200
_022319BC: .word 0x00010200
	thumb_func_end MOD80_022318D4

	thumb_func_start MOD80_022319C0
MOD80_022319C0: ; 0x022319C0
	mov r2, #0
	ldrsh r3, [r0, r2]
	ldrsh r2, [r1, r2]
	cmp r3, r2
	bne _022319EC
	mov r2, #2
	ldrsb r3, [r0, r2]
	ldrsb r2, [r1, r2]
	cmp r3, r2
	bne _022319EC
	mov r2, #3
	ldrsb r3, [r0, r2]
	ldrsb r2, [r1, r2]
	cmp r3, r2
	bne _022319EC
	mov r2, #4
	ldrsb r3, [r0, r2]
	ldrsb r0, [r1, r2]
	cmp r3, r0
	bne _022319EC
	mov r0, #1
	bx lr
_022319EC:
	mov r0, #0
	bx lr
	thumb_func_end MOD80_022319C0

	thumb_func_start MOD80_022319F0
MOD80_022319F0: ; 0x022319F0
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_0223205C
	ldr r0, [r4, #4]
	bl MOD80_02231AB0
	add r0, r4, #0
	bl MOD80_02231BF4
	add r0, r4, #0
	bl MOD80_02231EA8
	add r0, r4, #0
	bl MOD80_02231CBC
	ldr r0, [r4, #0x20]
	cmp r0, #8
	bne _02231A30
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _02231A46
_02231A30:
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
_02231A46:
	add r1, r4, #0
	add r1, #0xb8
	ldrh r1, [r1]
	add r0, r4, #0
	bl MOD80_02232D7C
	add r0, r4, #0
	bl MOD80_02236D84
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD80_022319F0

	thumb_func_start MOD80_02231A64
MOD80_02231A64: ; 0x02231A64
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222E79C
	bl FUN_02033EEC
	ldr r1, [r4, #0x2c]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02231A80 ; =0x02237B04
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_02231A80: .word MOD80_02237B04
	thumb_func_end MOD80_02231A64

	thumb_func_start MOD80_02231A84
MOD80_02231A84: ; 0x02231A84
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02033ED0
	add r0, r4, #0
	bl MOD80_02231E44
	add r0, r4, #0
	bl MOD80_022320E8
	add r0, r4, #0
	bl MOD80_0223200C
	ldr r0, [r4, #4]
	bl MOD80_02231BC8
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02231A84

	thumb_func_start MOD80_02231AB0
MOD80_02231AB0: ; 0x02231AB0
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _02231BB0 ; =0x02237210
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _02231BB4 ; =0x02237288
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02231BB8 ; =0x022372A4
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _02231BBC ; =0x0223726C
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _02231BC0 ; =0x02237234
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _02231BC4 ; =0x02237250
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	str r0, [r3]
	add r0, r4, #0
	mov r1, #5
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_02231BB0: .word MOD80_02237210
_02231BB4: .word MOD80_02237288
_02231BB8: .word MOD80_022372A4
_02231BBC: .word MOD80_0223726C
_02231BC0: .word MOD80_02237234
_02231BC4: .word MOD80_02237250
	thumb_func_end MOD80_02231AB0

	thumb_func_start MOD80_02231BC8
MOD80_02231BC8: ; 0x02231BC8
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_02231BC8

	thumb_func_start MOD80_02231BF4
MOD80_02231BF4: ; 0x02231BF4
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #2
	add r3, r2, #0
	bl FUN_02006930
	mov r0, #1
	lsl r0, r0, #8
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #5
	mov r2, #4
	mov r3, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0xc
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x18
	add r2, r4, #0
	bl FUN_020068C8
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x1d
	add r2, r4, #0
	mov r3, #2
	bl FUN_020068C8
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD80_02231BF4

	thumb_func_start MOD80_02231CBC
MOD80_02231CBC: ; 0x02231CBC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	mov r2, #0xcf
	add r5, r0, #0
	lsl r2, r2, #4
	add r0, sp, #0
	add r1, r5, #0
	add r2, r5, r2
	mov r3, #1
	bl MOD80_0222E5E8
	add r0, r5, #0
	add r0, #0xba
	ldrh r0, [r0]
	lsl r1, r0, #2
	ldr r0, _02231E28 ; =0x022372C0
	ldrh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xba
	ldrh r0, [r0]
	lsl r1, r0, #2
	ldr r0, _02231E2C ; =0x022372C2
	ldrh r0, [r0, r1]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _02231E30 ; =0x00000D5C
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _02231E30 ; =0x00000D5C
	mov r1, #4
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _02231E30 ; =0x00000D5C
	mov r1, #1
	ldr r0, [r5, r0]
	bl FUN_02020238
	ldr r6, _02231E28 ; =0x022372C0
	mov r7, #0
	add r4, r5, #0
_02231D1E:
	ldrh r0, [r6]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldrh r0, [r6, #2]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0x14
	str r0, [sp, #0x24]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _02231E34 ; =0x00000D64
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	add r1, r7, #6
	bl FUN_02020130
	ldr r0, _02231E34 ; =0x00000D64
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_02020238
	add r7, r7, #1
	add r6, r6, #4
	add r4, r4, #4
	cmp r7, #0x1e
	blt _02231D1E
	ldr r6, _02231E28 ; =0x022372C0
	mov r7, #0
	add r4, r5, #0
_02231D5C:
	ldrh r0, [r6]
	add r0, r0, #4
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldrh r0, [r6, #2]
	add r0, r0, #6
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x24]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _02231E38 ; =0x00000DDC
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #0x28
	bl FUN_02020130
	ldr r0, _02231E38 ; =0x00000DDC
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_02020238
	add r7, r7, #1
	add r6, r6, #4
	add r4, r4, #4
	cmp r7, #0x1e
	blt _02231D5C
	ldr r6, _02231E28 ; =0x022372C0
	mov r7, #0
	add r4, r5, #0
_02231D9E:
	ldrh r0, [r6]
	add r0, #0xc
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldrh r0, [r6, #2]
	add r0, r0, #6
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	mov r0, #0xa
	str r0, [sp, #0x24]
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _02231E3C ; =0x00000E54
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r0, [r4, r0]
	mov r1, #0x2a
	bl FUN_02020130
	ldr r0, _02231E3C ; =0x00000E54
	mov r1, #1
	ldr r0, [r4, r0]
	bl FUN_02020238
	add r7, r7, #1
	add r6, r6, #4
	add r4, r4, #4
	cmp r7, #6
	blt _02231D9E
	mov r7, #0xe9
	ldr r4, _02231E40 ; =0x02237208
	mov r6, #0
	lsl r7, r7, #4
_02231DE2:
	ldrh r0, [r4]
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldrh r0, [r4, #2]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	mov r1, #0xe9
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0xe9
	lsl r0, r0, #4
	add r1, r6, #0
	ldr r0, [r5, r0]
	add r1, #0x26
	bl FUN_02020130
	ldr r0, [r5, r7]
	mov r1, #1
	bl FUN_02020238
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r6, #2
	blt _02231DE2
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02231E28: .word MOD80_022372C0
_02231E2C: .word MOD80_022372C2
_02231E30: .word 0x00000D5C
_02231E34: .word 0x00000D64
_02231E38: .word 0x00000DDC
_02231E3C: .word 0x00000E54
_02231E40: .word MOD80_02237208
	thumb_func_end MOD80_02231CBC

	thumb_func_start MOD80_02231E44
MOD80_02231E44: ; 0x02231E44
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r7, #0xe9
	mov r6, #0
	add r4, r5, #0
	lsl r7, r7, #4
_02231E50:
	ldr r0, [r4, r7]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #2
	blt _02231E50
	ldr r0, _02231E98 ; =0x00000D5C
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	ldr r7, _02231E9C ; =0x00000DDC
	mov r6, #0
	add r4, r5, #0
_02231E6C:
	ldr r0, _02231EA0 ; =0x00000D64
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	ldr r0, [r4, r7]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #0x1e
	blt _02231E6C
	ldr r6, _02231EA4 ; =0x00000E54
	mov r4, #0
_02231E86:
	ldr r0, [r5, r6]
	bl FUN_0201FFC8
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #6
	blt _02231E86
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02231E98: .word 0x00000D5C
_02231E9C: .word 0x00000DDC
_02231EA0: .word 0x00000D64
_02231EA4: .word 0x00000E54
	thumb_func_end MOD80_02231E44

	thumb_func_start MOD80_02231EA8
MOD80_02231EA8: ; 0x02231EA8
	push {r3, r4, lr}
	sub sp, #0x14
	mov r3, #1
	add r4, r0, #0
	str r3, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	ldr r1, _02231FDC ; =0x00000EB8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _02231FDC ; =0x00000EB8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r2, #0
	mov r1, #0xb5
	ldr r0, _02231FE0 ; =0x000F0E00
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, _02231FDC ; =0x00000EB8
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r3, #1
	bl MOD80_02236D50
	mov r1, #3
	str r1, [sp]
	mov r0, #0xd
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	mov r0, #0x60
	ldr r1, _02231FE4 ; =0x00000EC8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #5
	bl FUN_02019064
	ldr r0, _02231FE4 ; =0x00000EC8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	ldr r0, _02231FE4 ; =0x00000EC8
	add r0, r4, r0
	bl FUN_020191D0
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	ldr r1, _02231FE8 ; =0x00000E98
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	add r0, #0xfc
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _02231FE8 ; =0x00000E98
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02231FEC ; =0x0000013F
	ldr r1, _02231FF0 ; =0x00000FB8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	ldr r0, _02231FF0 ; =0x00000FB8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #0x15
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldr r0, _02231FF4 ; =0x00000165
	ldr r1, _02231FF8 ; =0x00000EE8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #1
	mov r3, #0x19
	bl FUN_02019064
	ldr r0, _02231FF8 ; =0x00000EE8
	mov r1, #6
	add r0, r4, r0
	bl FUN_02019620
	mov r3, #1
	ldr r0, _02231FFC ; =0x00010306
	str r3, [sp]
	str r0, [sp, #4]
	ldr r1, _02232000 ; =0x00000B48
	ldr r0, _02231FF8 ; =0x00000EE8
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r2, #0
	bl MOD80_02236D50
	mov r1, #0xd
	str r1, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, _02232004 ; =0x00000171
	ldr r1, _02232008 ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_02231FDC: .word 0x00000EB8
_02231FE0: .word 0x000F0E00
_02231FE4: .word 0x00000EC8
_02231FE8: .word 0x00000E98
_02231FEC: .word 0x0000013F
_02231FF0: .word 0x00000FB8
_02231FF4: .word 0x00000165
_02231FF8: .word 0x00000EE8
_02231FFC: .word 0x00010306
_02232000: .word 0x00000B48
_02232004: .word 0x00000171
_02232008: .word 0x00000ED8
	thumb_func_end MOD80_02231EA8

	thumb_func_start MOD80_0223200C
MOD80_0223200C: ; 0x0223200C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02232044 ; =0x00000FB8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02232048 ; =0x00000EE8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _0223204C ; =0x00000ED8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02232050 ; =0x00000E98
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02232054 ; =0x00000EC8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02232058 ; =0x00000EB8
	add r0, r4, r0
	bl FUN_02019178
	pop {r4, pc}
	nop
_02232044: .word 0x00000FB8
_02232048: .word 0x00000EE8
_0223204C: .word 0x00000ED8
_02232050: .word 0x00000E98
_02232054: .word 0x00000EC8
_02232058: .word 0x00000EB8
	thumb_func_end MOD80_0223200C

	thumb_func_start MOD80_0223205C
MOD80_0223205C: ; 0x0223205C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x12
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _022320D4 ; =0x00000B44
	str r0, [r4, r1]
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _022320D8 ; =0x00000B4C
	str r0, [r4, r1]
	ldr r0, [r4, #0x24]
	cmp r0, #5
	bne _02232090
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0x15
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r4, r1]
	b _022320A4
_02232090:
	cmp r0, #6
	bne _022320A4
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0x11
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r4, r1]
_022320A4:
	ldr r0, _022320DC ; =0x00000B34
	mov r1, #0x67
	ldr r0, [r4, r0]
	bl NewString_ReadMsgData
	ldr r1, _022320E0 ; =0x00000B48
	str r0, [r4, r1]
	add r0, r4, #0
	add r0, #0xba
	ldrh r0, [r0]
	cmp r0, #0x1e
	bne _022320C4
	add r0, r4, #0
	mov r1, #0
	add r0, #0xba
	strh r1, [r0]
_022320C4:
	mov r0, #0x3e
	mov r1, #0x78
	bl AllocFromHeap
	ldr r1, _022320E4 ; =0x00001004
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_022320D4: .word 0x00000B44
_022320D8: .word 0x00000B4C
_022320DC: .word 0x00000B34
_022320E0: .word 0x00000B48
_022320E4: .word 0x00001004
	thumb_func_end MOD80_0223205C

	thumb_func_start MOD80_022320E8
MOD80_022320E8: ; 0x022320E8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02232118 ; =0x00001004
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _0223211C ; =0x00000B44
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _02232120 ; =0x00000B4C
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _02232124 ; =0x00000B48
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0xb5
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	.align 2, 0
_02232118: .word 0x00001004
_0223211C: .word 0x00000B44
_02232120: .word 0x00000B4C
_02232124: .word 0x00000B48
	thumb_func_end MOD80_022320E8

	thumb_func_start MOD80_02232128
MOD80_02232128: ; 0x02232128
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _02232138
	mov r0, #1
	str r0, [r4, #0x2c]
_02232138:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02232128

	thumb_func_start MOD80_0223213C
MOD80_0223213C: ; 0x0223213C
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	bl MOD80_0223237C
	ldr r0, [r5, #0x24]
	cmp r0, #5
	beq _0223214E
	b _02232250
_0223214E:
	ldr r0, _02232370 ; =gMain
	ldr r2, [r0, #0x48]
	mov r0, #2
	tst r0, r2
	beq _02232168
	add r0, r5, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r5, #0x2c]
	b _02232368
_02232168:
	mov r1, #1
	add r0, r2, #0
	tst r0, r1
	beq _022321B6
	add r0, r5, #0
	add r0, #0xba
	ldrh r0, [r0]
	cmp r0, #0x1e
	bne _0223218E
	add r0, r5, #0
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r5, #0x2c]
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
	b _02232368
_0223218E:
	cmp r0, #0x1f
	beq _022321B6
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02233054
	cmp r0, #1
	beq _022321B8
	cmp r0, #2
	beq _02232232
_022321B6:
	b _02232368
_022321B8:
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FF8
	cmp r0, #0
	beq _02232214
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	add r2, r0, #0
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl BufferBoxMonNickname
	ldr r0, _02232378 ; =0x00000F0F
	mov r3, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x16
	mov r2, #1
	str r3, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #3
	mov r2, #7
	bl MOD80_0222E6DC
	b _02232368
_02232214:
	ldr r0, _02232378 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x1a
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #4
	mov r2, #1
	bl MOD80_0222E6DC
	b _02232368
_02232232:
	ldr r0, _02232378 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x1b
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #4
	mov r2, #1
	bl MOD80_0222E6DC
	b _02232368
_02232250:
	cmp r0, #6
	bne _022322BA
	ldr r0, _02232370 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _02232274
	add r0, r5, #0
	mov r1, #3
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r5, #0x2c]
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
	b _02232368
_02232274:
	mov r0, #1
	tst r0, r1
	beq _02232368
	add r0, r5, #0
	add r0, #0xba
	ldrh r3, [r0]
	cmp r3, #0x1e
	bne _0223229A
	add r0, r5, #0
	mov r1, #3
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r5, #0x2c]
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
	b _02232368
_0223229A:
	cmp r3, #0x1f
	beq _02232368
	add r2, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldr r1, [r1, #0xc]
	bl MOD80_02233054
	cmp r0, #0
	beq _02232362
	cmp r0, #1
	beq _022322BC
	cmp r0, #2
	beq _02232362
_022322BA:
	b _02232368
_022322BC:
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	add r2, r5, #0
	add r2, #0xc4
	mov r1, #0xba
	ldr r3, [r2]
	mov r2, #0x49
	lsl r1, r1, #2
	lsl r2, r2, #2
	add r1, r5, r1
	mul r2, r3
	add r1, r1, r2
	add r4, r0, #0
	bl MOD80_022330E4
	cmp r0, #0
	beq _0223235A
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FF8
	cmp r0, #0
	beq _0223233C
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	add r2, r4, #0
	bl BufferBoxMonNickname
	ldr r0, _02232378 ; =0x00000F0F
	mov r3, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x12
	mov r2, #1
	str r3, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #3
	mov r2, #9
	bl MOD80_0222E6DC
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
	b _02232368
_0223233C:
	ldr r0, _02232378 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x1a
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #4
	mov r2, #1
	bl MOD80_0222E6DC
	b _02232368
_0223235A:
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
	b _02232368
_02232362:
	ldr r0, _02232374 ; =0x000005DC
	bl FUN_020054C8
_02232368:
	mov r0, #3
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02232370: .word gMain
_02232374: .word 0x000005DC
_02232378: .word 0x00000F0F
	thumb_func_end MOD80_0223213C

	thumb_func_start MOD80_0223237C
MOD80_0223237C: ; 0x0223237C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _02232448 ; =gMain
	mov r4, #0
	ldr r0, [r0, #0x48]
	mov r2, #0x40
	add r1, r4, #0
	tst r2, r0
	beq _02232392
	mov r1, #1
	b _022323AE
_02232392:
	mov r2, #0x80
	tst r2, r0
	beq _0223239C
	mov r1, #2
	b _022323AE
_0223239C:
	mov r2, #0x20
	tst r2, r0
	beq _022323A6
	mov r1, #3
	b _022323AE
_022323A6:
	mov r2, #0x10
	tst r0, r2
	beq _022323AE
	mov r1, #4
_022323AE:
	cmp r1, #0
	beq _022323FE
	add r0, r5, #0
	add r0, #0xba
	ldrh r0, [r0]
	ldr r3, _0223244C ; =0x02237340
	sub r2, r1, #1
	lsl r6, r0, #2
	add r1, r3, r6
	ldrb r2, [r2, r1]
	cmp r2, r0
	beq _022323FE
	cmp r2, #0x63
	beq _022323CE
	cmp r2, #0x65
	bne _022323F6
_022323CE:
	add r0, r5, #0
	add r0, #0xb8
	ldrh r0, [r0]
	mov r1, #0x13
	sub r2, #0x64
	bl MOD80_02232460
	add r1, r5, #0
	add r1, #0xb8
	strh r0, [r1]
	add r1, r5, #0
	add r1, #0xb8
	ldrh r1, [r1]
	add r0, r5, #0
	bl MOD80_02232D7C
	ldr r0, _02232450 ; =0x000005DC
	bl FUN_020054C8
	b _022323FE
_022323F6:
	add r0, r5, #0
	add r0, #0xba
	mov r4, #1
	strh r2, [r0]
_022323FE:
	cmp r4, #0
	beq _02232420
	ldr r0, _02232450 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #0xba
	ldrh r0, [r0]
	ldr r1, _02232454 ; =0x022372C0
	ldr r2, _02232458 ; =0x022372C2
	lsl r3, r0, #2
	ldr r0, _0223245C ; =0x00000D5C
	ldrh r1, [r1, r3]
	ldrh r2, [r2, r3]
	ldr r0, [r5, r0]
	bl MOD80_0222E6E4
_02232420:
	add r0, r5, #0
	add r0, #0xba
	ldrh r0, [r0]
	cmp r0, #0x1f
	beq _0223242E
	cmp r0, #5
	bhi _0223243A
_0223242E:
	ldr r0, _0223245C ; =0x00000D5C
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_02020238
	pop {r4, r5, r6, pc}
_0223243A:
	ldr r0, _0223245C ; =0x00000D5C
	mov r1, #1
	ldr r0, [r5, r0]
	bl FUN_02020238
	pop {r4, r5, r6, pc}
	nop
_02232448: .word gMain
_0223244C: .word MOD80_02237340
_02232450: .word 0x000005DC
_02232454: .word MOD80_022372C0
_02232458: .word MOD80_022372C2
_0223245C: .word 0x00000D5C
	thumb_func_end MOD80_0223237C

	thumb_func_start MOD80_02232460
MOD80_02232460: ; 0x02232460
	add r0, r0, r2
	bpl _02232468
	sub r0, r1, #1
	bx lr
_02232468:
	cmp r0, r1
	bne _0223246E
	mov r0, #0
_0223246E:
	bx lr
	thumb_func_end MOD80_02232460

	thumb_func_start MOD80_02232470
MOD80_02232470: ; 0x02232470
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0
	add r2, sp, #8
	strb r0, [r2, #8]
	mov r0, #1
	strb r0, [r2, #9]
	mov r0, #3
	strb r0, [r2, #0xa]
	ldrb r3, [r2, #0xb]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0x30
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0xc0
	bic r3, r1
	mov r1, #0x3e
	strb r3, [r2, #0xb]
	bl ListMenu_ctor
	ldr r1, _02232510 ; =0x00000FC8
	mov r2, #0x5e
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldr r1, _02232514 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl ListMenu_ItemFromMsgData
	ldr r0, _02232510 ; =0x00000FC8
	ldr r1, _02232514 ; =0x00000B34
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x5f
	mov r3, #2
	bl ListMenu_ItemFromMsgData
	ldr r0, _02232510 ; =0x00000FC8
	ldr r1, _02232514 ; =0x00000B34
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x60
	mov r3, #3
	bl ListMenu_ItemFromMsgData
	ldr r0, _02232510 ; =0x00000FC8
	mov r2, #0x1f
	ldr r1, [r4, r0]
	sub r0, #0xf0
	str r1, [sp, #8]
	add r0, r4, r0
	mov r1, #1
	mov r3, #0xb
	str r0, [sp, #0xc]
	bl FUN_0200CCA4
	mov r0, #0x3e
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #8
	mov r1, #9
	add r3, r2, #0
	bl FUN_02001C14
	mov r1, #0xfd
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #8
	str r0, [r4, #0x2c]
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02232510: .word 0x00000FC8
_02232514: .word 0x00000B34
	thumb_func_end MOD80_02232470

	thumb_func_start MOD80_02232518
MOD80_02232518: ; 0x02232518
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02001C78
	cmp r0, #3
	bhi _0223253C
	cmp r0, #1
	blo _0223253A
	beq _02232546
	cmp r0, #2
	beq _02232574
	cmp r0, #3
	beq _0223262E
_0223253A:
	b _0223265A
_0223253C:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0223262E
	b _0223265A
_02232546:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _02232660 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02232664 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	mov r0, #2
	str r0, [r5, #0x2c]
	add r0, r5, #0
	mov r1, #8
	mov r2, #5
	bl MOD80_0222E7A8
	b _0223265A
_02232574:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _02232660 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02232664 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	bl MOD80_02233018
	cmp r0, #0
	beq _022325CE
	ldr r0, _02232668 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x25
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #4
	mov r2, #1
	bl MOD80_0222E6DC
	b _0223265A
_022325CE:
	add r0, r5, #0
	add r0, #0xb8
	ldrh r0, [r0]
	mov r4, #0
	bl MOD80_02232FAC
	cmp r0, #0
	beq _022325FE
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0xba
	ldrh r1, [r1]
	ldr r0, [r0, #8]
	bl GetPartyMonByIndex
	mov r1, #0xa1
	add r2, r4, #0
	bl GetMonData
	cmp r0, #0
	beq _022325FE
	mov r0, #0xe
	mov r4, #1
	str r0, [r5, #0x2c]
_022325FE:
	cmp r4, #0
	bne _0223265A
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	add r1, r5, #0
	add r1, #0xbc
	str r0, [r1]
	mov r0, #2
	str r0, [r5, #0x2c]
	add r0, r5, #0
	mov r1, #6
	mov r2, #0
	bl MOD80_0222E7A8
	b _0223265A
_0223262E:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _02232660 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02232664 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _0223266C ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200D0E0
	mov r0, #1
	str r0, [r5, #0x2c]
_0223265A:
	mov r0, #3
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02232660: .word 0x00000FC8
_02232664: .word 0x00000ED8
_02232668: .word 0x00000F0F
_0223266C: .word 0x00000E98
	thumb_func_end MOD80_02232518

	thumb_func_start MOD80_02232670
MOD80_02232670: ; 0x02232670
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0
	add r2, sp, #8
	strb r0, [r2, #8]
	mov r0, #1
	strb r0, [r2, #9]
	mov r0, #3
	strb r0, [r2, #0xa]
	ldrb r3, [r2, #0xb]
	mov r1, #0xf
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0x30
	bic r3, r1
	strb r3, [r2, #0xb]
	ldrb r3, [r2, #0xb]
	mov r1, #0xc0
	bic r3, r1
	mov r1, #0x3e
	strb r3, [r2, #0xb]
	bl ListMenu_ctor
	ldr r1, _02232710 ; =0x00000FC8
	mov r2, #0x54
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	ldr r1, _02232714 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl ListMenu_ItemFromMsgData
	ldr r0, _02232710 ; =0x00000FC8
	ldr r1, _02232714 ; =0x00000B34
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x55
	mov r3, #2
	bl ListMenu_ItemFromMsgData
	ldr r0, _02232710 ; =0x00000FC8
	ldr r1, _02232714 ; =0x00000B34
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	mov r2, #0x56
	mov r3, #3
	bl ListMenu_ItemFromMsgData
	ldr r0, _02232710 ; =0x00000FC8
	mov r2, #0x1f
	ldr r1, [r4, r0]
	sub r0, #0xf0
	str r1, [sp, #8]
	add r0, r4, r0
	mov r1, #0
	mov r3, #0xb
	str r0, [sp, #0xc]
	bl FUN_0200CCA4
	mov r0, #0x3e
	str r0, [sp]
	mov r0, #2
	mov r2, #0
	str r0, [sp, #4]
	add r0, sp, #8
	mov r1, #9
	add r3, r2, #0
	bl FUN_02001C14
	mov r1, #0xfd
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #0xa
	str r0, [r4, #0x2c]
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02232710: .word 0x00000FC8
_02232714: .word 0x00000B34
	thumb_func_end MOD80_02232670

	thumb_func_start MOD80_02232718
MOD80_02232718: ; 0x02232718
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02001C78
	cmp r0, #3
	bhi _0223273C
	cmp r0, #1
	blo _0223273A
	beq _02232746
	cmp r0, #2
	beq _02232774
	cmp r0, #3
	beq _0223280A
_0223273A:
	b _02232836
_0223273C:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _0223280A
	b _02232836
_02232746:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0223283C ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02232840 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	mov r0, #2
	str r0, [r5, #0x2c]
	add r0, r5, #0
	mov r1, #8
	mov r2, #6
	bl MOD80_0222E7A8
	b _02232836
_02232774:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0223283C ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02232840 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	add r2, r5, #0
	add r3, r5, #0
	ldr r1, [r5]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	bl MOD80_02233018
	cmp r0, #0
	beq _022327CE
	ldr r0, _02232844 ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x25
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r5, #0
	mov r1, #4
	mov r2, #1
	bl MOD80_0222E6DC
	b _02232836
_022327CE:
	add r0, r5, #0
	add r0, #0xb8
	ldrh r0, [r0]
	mov r4, #0
	bl MOD80_02232FAC
	cmp r0, #0
	beq _022327FE
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0xba
	ldrh r1, [r1]
	ldr r0, [r0, #8]
	bl GetPartyMonByIndex
	mov r1, #0xa1
	add r2, r4, #0
	bl GetMonData
	cmp r0, #0
	beq _022327FE
	mov r0, #0xb
	mov r4, #1
	str r0, [r5, #0x2c]
_022327FE:
	cmp r4, #0
	bne _02232836
	add r0, r5, #0
	bl MOD80_02232990
	b _02232836
_0223280A:
	mov r0, #0xfd
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02001C5C
	ldr r0, _0223283C ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02232840 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02232848 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200D0E0
	mov r0, #1
	str r0, [r5, #0x2c]
_02232836:
	mov r0, #3
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223283C: .word 0x00000FC8
_02232840: .word 0x00000ED8
_02232844: .word 0x00000F0F
_02232848: .word 0x00000E98
	thumb_func_end MOD80_02232718

	thumb_func_start MOD80_0223284C
MOD80_0223284C: ; 0x0223284C
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _0223285C
	cmp r0, #8
	bne _0223287C
_0223285C:
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, _022328A0 ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	b _02232894
_0223287C:
	mov r0, #6
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
_02232894:
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_022328A0: .word 0x0000100C
	thumb_func_end MOD80_0223284C

	thumb_func_start MOD80_022328A4
MOD80_022328A4: ; 0x022328A4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _022328C0 ; =0x000001AD
	mov r1, #0xf
	bl MOD80_0222E6A8
	ldr r1, _022328C4 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #6
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	nop
_022328C0: .word 0x000001AD
_022328C4: .word 0x00000FCC
	thumb_func_end MOD80_022328A4

	thumb_func_start MOD80_022328C8
MOD80_022328C8: ; 0x022328C8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022328FC ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _022328F8
	sub r1, r1, #1
	cmp r0, r1
	bne _022328EA
	mov r0, #0
	str r0, [r4, #0x2c]
	b _022328F8
_022328EA:
	mov r0, #2
	mov r1, #0
	str r0, [r4, #0x2c]
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
_022328F8:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022328FC: .word 0x00000FCC
	thumb_func_end MOD80_022328C8

	thumb_func_start MOD80_02232900
MOD80_02232900: ; 0x02232900
	push {r4, lr}
	sub sp, #8
	ldr r1, _02232928 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r2, #1
	mov r1, #0x19
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r4, #0
	mov r1, #3
	mov r2, #0xc
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	nop
_02232928: .word 0x00000F0F
	thumb_func_end MOD80_02232900

	thumb_func_start MOD80_0223292C
MOD80_0223292C: ; 0x0223292C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _02232948 ; =0x000001AD
	mov r1, #0xd
	bl MOD80_0222E6A8
	ldr r1, _0223294C ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #0xd
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	nop
_02232948: .word 0x000001AD
_0223294C: .word 0x00000FCC
	thumb_func_end MOD80_0223292C

	thumb_func_start MOD80_02232950
MOD80_02232950: ; 0x02232950
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02232988 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02232982
	sub r1, r1, #1
	cmp r0, r1
	bne _0223297C
	ldr r0, _0223298C ; =0x00000FB8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200D0E0
	mov r0, #1
	str r0, [r4, #0x2c]
	b _02232982
_0223297C:
	add r0, r4, #0
	bl MOD80_02232990
_02232982:
	mov r0, #3
	pop {r4, pc}
	nop
_02232988: .word 0x00000FCC
_0223298C: .word 0x00000FB8
	thumb_func_end MOD80_02232950

	thumb_func_start MOD80_02232990
MOD80_02232990: ; 0x02232990
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r1, #0x7e
	add r0, #0xc4
	lsl r1, r1, #2
	add r2, r4, r1
	ldr r0, [r0]
	sub r1, #0xd4
	mul r1, r0
	add r0, r2, r1
	bl MOD80_022331F8
	cmp r0, #0
	beq _022329E6
	add r0, r4, #0
	add r0, #0xb8
	ldrh r0, [r0]
	cmp r0, #0x12
	beq _022329E6
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl GetPartyCount
	cmp r0, #6
	bne _022329E6
	ldr r0, _02232A2C ; =0x00000F0F
	mov r2, #1
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x1c
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r4, #0
	mov r1, #4
	mov r2, #1
	bl MOD80_0222E6DC
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_022329E6:
	add r2, r4, #0
	add r3, r4, #0
	ldr r1, [r4]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	add r1, r4, #0
	add r1, #0xbc
	str r0, [r1]
	mov r0, #2
	str r0, [r4, #0x2c]
	ldr r0, _02232A30 ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #7
	mov r2, #9
	bl MOD80_0222E7A8
	add r0, r4, #0
	add r0, #0xd4
	add r1, r4, #0
	bl MOD80_0223311C
	mov r0, #0
	add r4, #0xc0
	str r0, [r4]
	mov r0, #1
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_02232A2C: .word 0x00000F0F
_02232A30: .word 0x0000100C
	thumb_func_end MOD80_02232990

	thumb_func_start MOD80_02232A34
MOD80_02232A34: ; 0x02232A34
	push {r4, lr}
	sub sp, #8
	ldr r1, _02232A5C ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r2, #1
	mov r1, #0x19
	mov r3, #0
	str r2, [sp, #4]
	bl MOD80_02232B34
	add r0, r4, #0
	mov r1, #3
	mov r2, #0xf
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	nop
_02232A5C: .word 0x00000F0F
	thumb_func_end MOD80_02232A34

	thumb_func_start MOD80_02232A60
MOD80_02232A60: ; 0x02232A60
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _02232A7C ; =0x000001AD
	mov r1, #0xd
	bl MOD80_0222E6A8
	ldr r1, _02232A80 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #0x10
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	nop
_02232A7C: .word 0x000001AD
_02232A80: .word 0x00000FCC
	thumb_func_end MOD80_02232A60

	thumb_func_start MOD80_02232A84
MOD80_02232A84: ; 0x02232A84
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02232AE0 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02232ADA
	sub r1, r1, #1
	cmp r0, r1
	bne _02232AB0
	ldr r0, _02232AE4 ; =0x00000FB8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200D0E0
	mov r0, #1
	str r0, [r4, #0x2c]
	b _02232ADA
_02232AB0:
	add r2, r4, #0
	add r3, r4, #0
	ldr r1, [r4]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	add r1, r4, #0
	add r1, #0xbc
	str r0, [r1]
	mov r0, #2
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	bl MOD80_0222E7A8
_02232ADA:
	mov r0, #3
	pop {r4, pc}
	nop
_02232AE0: .word 0x00000FCC
_02232AE4: .word 0x00000FB8
	thumb_func_end MOD80_02232A84

	thumb_func_start MOD80_02232AE8
MOD80_02232AE8: ; 0x02232AE8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02232B02
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02232B02:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02232AE8

	thumb_func_start MOD80_02232B08
MOD80_02232B08: ; 0x02232B08
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02232B2C
	ldr r0, _02232B30 ; =0x00000FB8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200D0E0
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02232B2C:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02232B30: .word 0x00000FB8
	thumb_func_end MOD80_02232B08

	thumb_func_start MOD80_02232B34
MOD80_02232B34: ; 0x02232B34
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02232B9C ; =0x00000B34
	add r6, r2, #0
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0xb3
	add r7, r0, #0
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #0x1c
	ldr r1, [r5, r1]
	add r2, r7, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x24]
	cmp r0, #0
	bne _02232B60
	ldr r0, _02232BA0 ; =0x00000E98
	b _02232B62
_02232B60:
	ldr r0, _02232BA4 ; =0x00000FB8
_02232B62:
	add r4, r5, r0
	add r0, r4, #0
	mov r1, #0xf
	bl FUN_02019620
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r6, [sp, #4]
	ldr r2, _02232BA8 ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r4, #0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r7, #0
	bl String_dtor
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02232B9C: .word 0x00000B34
_02232BA0: .word 0x00000E98
_02232BA4: .word 0x00000FB8
_02232BA8: .word 0x00000B4C
	thumb_func_end MOD80_02232B34

	thumb_func_start MOD80_02232BAC
MOD80_02232BAC: ; 0x02232BAC
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r2, r3, #0
	bl NARC_AllocAndReadWholeMember
	add r4, r0, #0
	beq _02232BCE
	add r1, r5, #0
	bl FUN_020B0030
	cmp r0, #0
	bne _02232BCE
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #0
	pop {r3, r4, r5, pc}
_02232BCE:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_02232BAC

	thumb_func_start MOD80_02232BD4
MOD80_02232BD4: ; 0x02232BD4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r6, r2, #0
	add r1, r6, #0
	add r2, r5, #0
	str r0, [sp]
	add r7, r3, #0
	ldr r4, [sp, #0x28]
	bl FUN_0206B6D4
	add r1, r0, #0
	ldr r0, [sp, #0x24]
	add r2, sp, #8
	mov r3, #0x3e
	bl MOD80_02232BAC
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	add r1, r4, #0
	mov r2, #2
	ldr r0, [r0, #0x14]
	add r1, #0xc
	lsl r2, r2, #8
	bl MIi_CpuCopyFast
	lsl r0, r7, #4
	add r0, #0xc
	lsl r0, r0, #5
	str r0, [r4]
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	str r0, [r4, #8]
	ldr r0, [sp]
	add r2, r6, #0
	bl FUN_0206B7BC
	add r0, r0, #3
	str r0, [r4, #4]
	ldr r0, [sp, #4]
	bl FreeToHeap
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD80_02232BD4

	thumb_func_start MOD80_02232C2C
MOD80_02232C2C: ; 0x02232C2C
	push {r4, lr}
	add r4, r1, #0
	bl CalcBoxMonLevel
	strb r0, [r4, #3]
	pop {r4, pc}
	thumb_func_end MOD80_02232C2C

	thumb_func_start MOD80_02232C38
MOD80_02232C38: ; 0x02232C38
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _02232C84 ; =0x00001010
	mov r6, #2
	lsl r6, r6, #8
	add r7, r6, #0
	ldr r5, [r0, r1]
	str r0, [sp]
	mov r4, #0
	add r7, #0xc
_02232C4A:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _02232C6E
	add r0, r5, #0
	add r0, #0xc
	add r1, r6, #0
	bl DC_FlushRange
	add r0, r5, #0
	ldr r1, [r5]
	add r0, #0xc
	add r2, r6, #0
	bl GX_LoadOBJ
	ldr r0, [r5, #8]
	ldr r1, [r5, #4]
	bl FUN_02020248
_02232C6E:
	add r4, r4, #1
	add r5, r5, r7
	cmp r4, #0x1e
	blt _02232C4A
	ldr r1, _02232C84 ; =0x00001010
	ldr r0, [sp]
	ldr r0, [r0, r1]
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02232C84: .word 0x00001010
	thumb_func_end MOD80_02232C38

	thumb_func_start MOD80_02232C88
MOD80_02232C88: ; 0x02232C88
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	str r1, [sp, #0xc]
	add r7, r2, #0
	add r6, r3, #0
	ldr r4, [sp, #0x40]
	bl AcquireBoxMonLock
	add r0, r5, #0
	mov r1, #0xab
	mov r2, #0
	bl GetBoxMonData
	str r0, [sp, #0x1c]
	add r0, r5, #0
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	strh r0, [r6]
	add r0, r5, #0
	mov r1, #0x70
	mov r2, #0
	bl GetBoxMonData
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r1, #0x4c
	mov r2, #0
	bl GetBoxMonData
	str r0, [sp, #0x14]
	add r0, r5, #0
	mov r1, #6
	mov r2, #0
	bl GetBoxMonData
	str r0, [sp, #0x18]
	ldrh r0, [r6]
	mov r1, #0x6f
	mov r2, #0
	strh r0, [r4]
	add r0, r5, #0
	bl GetBoxMonData
	add r0, r0, #1
	strb r0, [r4, #2]
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02232CF2
	mov r0, #0
	strb r0, [r4, #3]
_02232CF2:
	add r0, r5, #0
	mov r1, #1
	bl ReleaseBoxMonLock
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _02232D60
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x10]
	str r0, [sp]
	ldr r0, [sp, #0x3c]
	ldr r2, [sp, #0x14]
	str r0, [sp, #4]
	ldr r0, [sp, #0x44]
	ldr r3, [sp, #0x38]
	str r0, [sp, #8]
	ldrh r0, [r6]
	bl MOD80_02232BD4
	ldr r0, [sp, #0xc]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _02232D54
	add r0, r7, #0
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [sp, #0x18]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl ItemIdIsMail
	cmp r0, #0
	beq _02232D48
	add r0, r7, #0
	mov r1, #0x29
	bl FUN_02020130
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_02232D48:
	add r0, r7, #0
	mov r1, #0x28
	bl FUN_02020130
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_02232D54:
	add r0, r7, #0
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_02232D60:
	ldr r0, [sp, #0xc]
	mov r1, #0
	bl FUN_020200A0
	add r0, r7, #0
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [sp, #0x44]
	mov r1, #0
	str r1, [r0, #8]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD80_02232C88

	thumb_func_start MOD80_02232D7C
MOD80_02232D7C: ; 0x02232D7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x68
	add r5, r0, #0
	ldr r0, [r5]
	str r1, [sp, #0x10]
	ldr r0, [r0, #0xc]
	ldr r1, _02232F7C ; =0x00003D68
	str r0, [sp, #0x20]
	mov r0, #3
	bl AllocFromHeapAtEnd
	ldr r1, _02232F80 ; =0x00001010
	str r0, [sp, #0x18]
	str r0, [r5, r1]
	mov r0, #0x13
	mov r1, #0x3e
	bl NARC_ctor
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	cmp r0, #0
	blt _02232E3A
	cmp r0, #0x12
	bge _02232E3A
	ldr r6, _02232F84 ; =0x00001004
	mov r4, #0
_02232DB0:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	add r2, r4, #0
	bl PCStorage_GetMonByIndexPair
	ldr r2, [r5, r6]
	lsl r1, r4, #2
	add r1, r2, r1
	bl MOD80_02232C2C
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x1e
	blo _02232DB0
	mov r4, #0
_02232DD0:
	ldr r0, _02232F84 ; =0x00001004
	lsl r6, r4, #2
	ldr r1, [r5, r0]
	mov r0, #0
	strh r0, [r1, r6]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	add r2, r4, #0
	add r7, r5, r6
	bl PCStorage_GetMonByIndexPair
	ldr r1, [sp, #0x1c]
	str r4, [sp]
	str r1, [sp, #4]
	ldr r1, _02232F84 ; =0x00001004
	add r2, r4, #0
	ldr r1, [r5, r1]
	add r3, sp, #0x2c
	add r1, r1, r6
	str r1, [sp, #8]
	mov r1, #0x83
	lsl r1, r1, #2
	mul r2, r1
	ldr r1, [sp, #0x18]
	lsl r6, r4, #1
	add r1, r1, r2
	str r1, [sp, #0xc]
	ldr r1, _02232F88 ; =0x00000D64
	ldr r2, _02232F8C ; =0x00000DDC
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	add r3, r3, r6
	bl MOD80_02232C88
	cmp r4, #6
	bhs _02232E22
	ldr r0, _02232F90 ; =0x00000E54
	mov r1, #0
	ldr r0, [r7, r0]
	bl FUN_020200A0
_02232E22:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x1e
	blo _02232DD0
	ldr r2, _02232F94 ; =0x00000B44
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x10]
	ldr r2, [r5, r2]
	bl PCStorage_GetBoxName
	b _02232F22
_02232E3A:
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl GetPartyCount
	mov r4, #0
	str r0, [sp, #0x14]
	cmp r0, #0
	ble _02232EC8
_02232E4A:
	ldr r0, [r5]
	add r1, r4, #0
	ldr r0, [r0, #8]
	bl GetPartyMonByIndex
	str r0, [sp, #0x24]
	bl FUN_020690E4
	ldr r1, _02232F84 ; =0x00001004
	lsl r6, r4, #2
	ldr r1, [r5, r1]
	str r0, [sp, #0x28]
	add r1, r1, r6
	bl MOD80_02232C2C
	ldr r0, [sp, #0x1c]
	str r4, [sp]
	str r0, [sp, #4]
	ldr r0, _02232F84 ; =0x00001004
	add r1, r4, #0
	ldr r0, [r5, r0]
	ldr r2, _02232F8C ; =0x00000DDC
	add r0, r0, r6
	str r0, [sp, #8]
	mov r0, #0x83
	lsl r0, r0, #2
	mul r1, r0
	ldr r0, [sp, #0x18]
	add r7, r5, r6
	add r0, r0, r1
	str r0, [sp, #0xc]
	ldr r1, _02232F88 ; =0x00000D64
	ldr r0, [sp, #0x28]
	ldr r1, [r7, r1]
	ldr r2, [r7, r2]
	lsl r6, r4, #1
	add r3, sp, #0x2c
	add r3, r3, r6
	bl MOD80_02232C88
	ldr r0, [sp, #0x24]
	mov r1, #0xa1
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	ldr r0, _02232F90 ; =0x00000E54
	beq _02232EB4
	ldr r0, [r7, r0]
	mov r1, #1
	bl FUN_020200A0
	b _02232EBC
_02232EB4:
	ldr r0, [r7, r0]
	mov r1, #0
	bl FUN_020200A0
_02232EBC:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [sp, #0x14]
	cmp r4, r0
	blt _02232E4A
_02232EC8:
	cmp r4, #0x1e
	bhs _02232F14
	mov r7, #0
_02232ECE:
	ldr r0, _02232F84 ; =0x00001004
	lsl r1, r4, #2
	ldr r0, [r5, r0]
	add r6, r5, r1
	strh r7, [r0, r1]
	ldr r0, _02232F88 ; =0x00000D64
	add r1, r7, #0
	ldr r0, [r6, r0]
	bl FUN_020200A0
	ldr r0, _02232F8C ; =0x00000DDC
	mov r1, #0
	ldr r0, [r6, r0]
	bl FUN_020200A0
	mov r0, #0x83
	lsl r0, r0, #2
	add r1, r4, #0
	mul r1, r0
	ldr r0, [sp, #0x18]
	add r1, r0, r1
	mov r0, #0
	str r0, [r1, #8]
	cmp r4, #6
	bhs _02232F0A
	ldr r0, _02232F90 ; =0x00000E54
	mov r1, #0
	ldr r0, [r6, r0]
	bl FUN_020200A0
_02232F0A:
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	cmp r4, #0x1e
	blo _02232ECE
_02232F14:
	ldr r2, _02232F98 ; =0x00000B34
	mov r1, #0x59
	ldr r0, [r5, r2]
	add r2, #0x10
	ldr r2, [r5, r2]
	bl ReadMsgDataIntoString
_02232F22:
	ldr r0, [sp, #0x1c]
	bl NARC_dtor
	ldr r0, _02232F9C ; =0x00000EC8
	mov r1, #0
	add r0, r5, r0
	bl FUN_02019620
	mov r0, #1
	str r0, [sp]
	ldr r0, _02232FA0 ; =0x00010200
	ldr r1, _02232F94 ; =0x00000B44
	str r0, [sp, #4]
	ldr r0, _02232F9C ; =0x00000EC8
	ldr r1, [r5, r1]
	add r0, r5, r0
	mov r2, #0
	mov r3, #5
	bl MOD80_02236D50
	ldr r0, [r5, #0x24]
	cmp r0, #6
	bne _02232F72
	add r3, r5, #0
	add r3, #0xc4
	mov r2, #0xba
	ldr r4, [r3]
	mov r3, #0x49
	ldr r0, _02232F84 ; =0x00001004
	lsl r2, r2, #2
	lsl r3, r3, #2
	ldr r1, _02232F88 ; =0x00000D64
	add r2, r5, r2
	mul r3, r4
	add r2, r2, r3
	ldr r0, [r5, r0]
	ldr r3, [sp, #0x18]
	add r1, r5, r1
	bl MOD80_022331C4
_02232F72:
	ldr r1, _02232FA4 ; =MOD80_02232C38
	ldr r0, _02232FA8 ; =0x00001014
	str r1, [r5, r0]
	add sp, #0x68
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02232F7C: .word 0x00003D68
_02232F80: .word 0x00001010
_02232F84: .word 0x00001004
_02232F88: .word 0x00000D64
_02232F8C: .word 0x00000DDC
_02232F90: .word 0x00000E54
_02232F94: .word 0x00000B44
_02232F98: .word 0x00000B34
_02232F9C: .word 0x00000EC8
_02232FA0: .word 0x00010200
_02232FA4: .word MOD80_02232C38
_02232FA8: .word 0x00001014
	thumb_func_end MOD80_02232D7C

	thumb_func_start MOD80_02232FAC
MOD80_02232FAC: ; 0x02232FAC
	cmp r0, #0x12
	bne _02232FB4
	mov r0, #1
	bx lr
_02232FB4:
	mov r0, #0
	bx lr
	thumb_func_end MOD80_02232FAC

	thumb_func_start MOD80_02232FB8
MOD80_02232FB8: ; 0x02232FB8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r7, r1, #0
	add r4, r3, #0
	bl MOD80_02232FAC
	cmp r0, #0
	beq _02232FEA
	add r0, r5, #0
	bl GetPartyCount
	sub r0, r0, #1
	cmp r4, r0
	ble _02232FDC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02232FDC:
	add r0, r5, #0
	add r1, r4, #0
	bl GetPartyMonByIndex
	bl FUN_020690E4
	pop {r3, r4, r5, r6, r7, pc}
_02232FEA:
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl PCStorage_GetMonByIndexPair
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD80_02232FB8

	thumb_func_start MOD80_02232FF8
MOD80_02232FF8: ; 0x02232FF8
	push {r4, lr}
	add r4, r0, #0
	add r0, r2, #0
	bl MOD80_02232FAC
	cmp r0, #0
	beq _02233014
	add r0, r4, #0
	bl GetPartyCount
	cmp r0, #2
	bge _02233014
	mov r0, #0
	pop {r4, pc}
_02233014:
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_02232FF8

	thumb_func_start MOD80_02233018
MOD80_02233018: ; 0x02233018
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	mov r4, #0
	bl AcquireBoxMonLock
	ldr r5, _02233050 ; =0x02237220
	str r0, [sp]
	add r6, r4, #0
_02233028:
	ldrh r1, [r5]
	add r0, r7, #0
	mov r2, #0
	bl GetBoxMonData
	add r6, r6, #1
	add r4, r4, r0
	add r5, r5, #2
	cmp r6, #0xa
	blt _02233028
	ldr r1, [sp]
	add r0, r7, #0
	bl ReleaseBoxMonLock
	cmp r4, #0
	beq _0223304C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223304C:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02233050: .word MOD80_02237220
	thumb_func_end MOD80_02233018

	thumb_func_start MOD80_02233054
MOD80_02233054: ; 0x02233054
	push {r4, lr}
	bl MOD80_02232FB8
	add r4, r0, #0
	bne _02233062
	mov r0, #0
	pop {r4, pc}
_02233062:
	mov r1, #0xab
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	bne _02233072
	mov r0, #0
	pop {r4, pc}
_02233072:
	add r0, r4, #0
	mov r1, #0xac
	mov r2, #0
	bl GetBoxMonData
	cmp r0, #0
	beq _02233084
	mov r0, #2
	pop {r4, pc}
_02233084:
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_02233054

	thumb_func_start MOD80_02233088
MOD80_02233088: ; 0x02233088
	push {r3, r4}
	mov r4, #0
	ldrsh r3, [r0, r4]
	ldrsh r2, [r1, r4]
	cmp r3, r2
	beq _0223309A
	add r0, r4, #0
	pop {r3, r4}
	bx lr
_0223309A:
	mov r2, #2
	ldrsb r3, [r1, r2]
	cmp r3, #3
	beq _022330AE
	ldrsb r2, [r0, r2]
	cmp r3, r2
	beq _022330AE
	add r0, r4, #0
	pop {r3, r4}
	bx lr
_022330AE:
	mov r2, #3
	ldrsb r3, [r0, r2]
	cmp r3, #0
	bne _022330BC
	mov r0, #0
	pop {r3, r4}
	bx lr
_022330BC:
	ldrsb r0, [r1, r2]
	cmp r0, #0
	beq _022330CC
	cmp r0, r3
	ble _022330CC
	mov r0, #0
	pop {r3, r4}
	bx lr
_022330CC:
	mov r0, #4
	ldrsb r0, [r1, r0]
	cmp r0, #0
	beq _022330DE
	cmp r0, r3
	bge _022330DE
	mov r0, #0
	pop {r3, r4}
	bx lr
_022330DE:
	mov r0, #1
	pop {r3, r4}
	bx lr
	thumb_func_end MOD80_02233088

	thumb_func_start MOD80_022330E4
MOD80_022330E4: ; 0x022330E4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #5
	mov r2, #0
	add r5, r0, #0
	bl GetBoxMonData
	add r1, sp, #0
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #0x6f
	mov r2, #0
	bl GetBoxMonData
	add r1, r0, #1
	add r0, sp, #0
	strb r1, [r0, #2]
	add r0, r5, #0
	bl CalcBoxMonLevel
	add r1, sp, #0
	strb r0, [r1, #3]
	add r0, sp, #0
	add r1, r4, #0
	bl MOD80_02233088
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_022330E4

	thumb_func_start MOD80_0223311C
MOD80_0223311C: ; 0x0223311C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	add r1, sp, #0
	strh r0, [r1, #6]
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	mov r1, #0x6f
	mov r2, #0
	bl GetBoxMonData
	add r1, r0, #1
	add r0, sp, #0
	strb r1, [r0, #8]
	add r0, r5, #0
	add r0, #0xbc
	ldr r0, [r0]
	bl CalcBoxMonLevel
	add r1, sp, #0
	strb r0, [r1, #9]
	add r0, r4, #0
	ldrh r2, [r1, #6]
	add r0, #0xec
	strh r2, [r0]
	add r0, r4, #0
	ldrh r1, [r1, #8]
	add r0, #0xee
	strh r1, [r0]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD80_02234288
	mov r0, #0x7e
	lsl r0, r0, #2
	add r2, r5, r0
	add r5, #0xc4
	ldr r1, [r5]
	sub r0, #0xd4
	mul r0, r1
	add r0, r2, r0
	bl FUN_020690E4
	mov r1, #5
	mov r2, #0
	add r5, r0, #0
	bl GetBoxMonData
	add r1, sp, #0
	strh r0, [r1]
	add r0, r5, #0
	mov r1, #0x6f
	mov r2, #0
	bl GetBoxMonData
	add r0, r0, #1
	add r1, sp, #0
	strb r0, [r1, #2]
	mov r0, #0
	strb r0, [r1, #3]
	strb r0, [r1, #4]
	add r0, r4, #0
	ldrh r2, [r1]
	add r0, #0xf0
	strh r2, [r0]
	add r0, r4, #0
	ldrh r2, [r1, #2]
	add r0, #0xf2
	add r4, #0xf4
	strh r2, [r0]
	ldrh r0, [r1, #4]
	strh r0, [r4]
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_0223311C

	thumb_func_start MOD80_022331C4
MOD80_022331C4: ; 0x022331C4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r7, r2, #0
	add r4, r3, #0
	mov r6, #0
_022331CE:
	mov r0, #0
	ldrsh r0, [r5, r0]
	cmp r0, #0
	beq _022331E8
	add r0, r5, #0
	add r1, r7, #0
	bl MOD80_02233088
	cmp r0, #0
	bne _022331E8
	ldr r0, [r4, #4]
	add r0, r0, #3
	str r0, [r4, #4]
_022331E8:
	mov r0, #0x83
	lsl r0, r0, #2
	add r6, r6, #1
	add r5, r5, #4
	add r4, r4, r0
	cmp r6, #0x1e
	blt _022331CE
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD80_022331C4

	thumb_func_start MOD80_022331F8
MOD80_022331F8: ; 0x022331F8
	push {r3, lr}
	mov r1, #6
	mov r2, #0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl ItemIdIsMail
	cmp r0, #0
	beq _02233212
	mov r0, #1
	pop {r3, pc}
_02233212:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD80_022331F8

	thumb_func_start MOD80_02233218
MOD80_02233218: ; 0x02233218
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_02233618
	ldr r0, [r4, #4]
	bl MOD80_02233358
	add r0, r4, #0
	bl MOD80_0223346C
	add r0, r4, #0
	bl MOD80_02233500
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD80_02236D84
	mov r0, #0
	str r0, [sp]
	mov r0, #3
	ldr r2, _02233298 ; =0x00000B34
	str r0, [sp, #4]
	sub r0, r0, #4
	str r0, [sp, #8]
	add r1, r2, #4
	ldr r0, [r4, r2]
	sub r2, r2, #4
	ldr r3, _0223329C ; =0x00000F08
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	add r3, r4, r3
	bl MOD80_02233FB4
	ldr r1, _022332A0 ; =0x00000B18
	add r3, r4, #0
	add r0, r4, r1
	str r0, [sp]
	add r0, r1, #0
	add r0, #0x1c
	add r1, #0x18
	ldr r2, _022332A4 ; =0x00000F38
	add r3, #0xbc
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	ldr r3, [r3]
	add r2, r4, r2
	bl MOD80_022340DC
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02233298: .word 0x00000B34
_0223329C: .word 0x00000F08
_022332A0: .word 0x00000B18
_022332A4: .word 0x00000F38
	thumb_func_end MOD80_02233218

	thumb_func_start MOD80_022332A8
MOD80_022332A8: ; 0x022332A8
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222E79C
	bl FUN_02033EEC
	ldr r1, [r4, #0x2c]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _022332C4 ; =0x02237B84
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_022332C4: .word MOD80_02237B84
	thumb_func_end MOD80_022332A8

	thumb_func_start MOD80_022332C8
MOD80_022332C8: ; 0x022332C8
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02033ED0
	add r0, r4, #0
	bl MOD80_02233684
	add r0, r4, #0
	bl MOD80_022335E0
	ldr r0, [r4, #4]
	bl MOD80_02233440
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_022332C8

	thumb_func_start MOD80_022332EC
MOD80_022332EC: ; 0x022332EC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _0223334C ; =0x00000B34
	add r4, r2, #0
	ldr r0, [r5, r0]
	bl NewString_ReadMsgData
	mov r1, #0xb3
	add r6, r0, #0
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #0x1c
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	ldr r0, _02233350 ; =0x00000E98
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _02233350 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _02233350 ; =0x00000E98
	ldr r2, _02233354 ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r6, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223334C: .word 0x00000B34
_02233350: .word 0x00000E98
_02233354: .word 0x00000B4C
	thumb_func_end MOD80_022332EC

	thumb_func_start MOD80_02233358
MOD80_02233358: ; 0x02233358
	push {r4, r5, lr}
	sub sp, #0x8c
	ldr r5, _0223342C ; =0x02237420
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x70
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02233430 ; =0x0223743C
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _02233434 ; =0x02237458
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	ldr r5, _02233438 ; =0x02237404
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _0223343C ; =0x022373E8
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	add sp, #0x8c
	pop {r4, r5, pc}
	nop
_0223342C: .word MOD80_02237420
_02233430: .word MOD80_0223743C
_02233434: .word MOD80_02237458
_02233438: .word MOD80_02237404
_0223343C: .word MOD80_022373E8
	thumb_func_end MOD80_02233358

	thumb_func_start MOD80_02233440
MOD80_02233440: ; 0x02233440
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_02233440

	thumb_func_start MOD80_0223346C
MOD80_0223346C: ; 0x0223346C
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x3e
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x68
	mov r1, #1
	add r3, r2, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r0, #0
	str r0, [sp]
	mov r0, #0xa
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0xb
	add r2, r4, #0
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	lsl r0, r0, #8
	str r0, [sp, #4]
	mov r3, #1
	str r3, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x68
	mov r1, #0x17
	add r2, r4, #0
	bl FUN_020068C8
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD80_0223346C

	thumb_func_start MOD80_02233500
MOD80_02233500: ; 0x02233500
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	mov r3, #1
	add r7, r0, #0
	str r3, [sp]
	mov r0, #0x1c
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	ldr r1, _022335CC ; =0x00000EB8
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	add r1, r7, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _022335CC ; =0x00000EB8
	mov r1, #0
	add r0, r7, r0
	bl FUN_02019620
	mov r2, #0
	mov r1, #0xb5
	ldr r0, _022335D0 ; =0x000F0E00
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, _022335CC ; =0x00000EB8
	lsl r1, r1, #4
	ldr r1, [r7, r1]
	add r0, r7, r0
	mov r3, #1
	bl MOD80_02236D1C
	mov r0, #0x15
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r3, #2
	ldr r1, _022335D4 ; =0x00000E98
	str r3, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x60
	str r0, [sp, #0x10]
	ldr r0, [r7, #4]
	add r1, r7, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _022335D4 ; =0x00000E98
	mov r1, #0
	add r0, r7, r0
	bl FUN_02019620
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, _022335D8 ; =0x00000F08
	ldr r4, _022335DC ; =0x022373D0
	mov r6, #0x96
	add r5, r7, r0
_0223357E:
	ldrh r0, [r4, #2]
	add r1, r5, #0
	mov r2, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0x10]
	ldrh r3, [r4]
	ldr r0, [r7, #4]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	add r0, r5, #0
	bl FUN_020191D0
	ldr r0, [sp, #0x14]
	add r6, #0x16
	add r0, r0, #1
	add r4, r4, #4
	add r5, #0x10
	str r0, [sp, #0x14]
	cmp r0, #6
	blt _0223357E
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022335CC: .word 0x00000EB8
_022335D0: .word 0x000F0E00
_022335D4: .word 0x00000E98
_022335D8: .word 0x00000F08
_022335DC: .word MOD80_022373D0
	thumb_func_end MOD80_02233500

	thumb_func_start MOD80_022335E0
MOD80_022335E0: ; 0x022335E0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _0223360C ; =0x00000F08
	mov r4, #0
	add r5, r6, r0
_022335EA:
	add r0, r5, #0
	bl FUN_02019178
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #6
	blt _022335EA
	ldr r0, _02233610 ; =0x00000E98
	add r0, r6, r0
	bl FUN_02019178
	ldr r0, _02233614 ; =0x00000EB8
	add r0, r6, r0
	bl FUN_02019178
	pop {r4, r5, r6, pc}
	nop
_0223360C: .word 0x00000F08
_02233610: .word 0x00000E98
_02233614: .word 0x00000EB8
	thumb_func_end MOD80_022335E0

	thumb_func_start MOD80_02233618
MOD80_02233618: ; 0x02233618
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _02233680 ; =0x00000B4C
	str r0, [r4, r1]
	sub r1, #0x18
	ldr r0, [r4, r1]
	mov r1, #0x5a
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r4, r1]
	mov r0, #0x3e
	mov r1, #0x30
	bl AllocFromHeap
	mov r1, #0xfe
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0
	mov r2, #0x30
	bl MIi_CpuClearFast
	mov r2, #0xfe
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	mov r0, #0x3e
	mov r1, #0
	add r2, #0x1c
	bl MOD80_02234204
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	str r0, [r1, #0x18]
	mov r0, #0x3e
	bl MOD80_02234228
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	add r1, #0x38
	str r0, [r2, #0x14]
	add r0, r4, r1
	bl MOD80_022346D8
	pop {r4, pc}
	.align 2, 0
_02233680: .word 0x00000B4C
	thumb_func_end MOD80_02233618

	thumb_func_start MOD80_02233684
MOD80_02233684: ; 0x02233684
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x14]
	bl FreeToHeap
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x18]
	bl FreeToHeap
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FreeToHeap
	ldr r0, _022336C0 ; =0x00000B4C
	ldr r0, [r4, r0]
	bl String_dtor
	mov r0, #0xb5
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	nop
_022336C0: .word 0x00000B4C
	thumb_func_end MOD80_02233684

	thumb_func_start MOD80_022336C4
MOD80_022336C4: ; 0x022336C4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl FUN_0200E308
	cmp r0, #0
	beq _022336EC
	ldr r0, _022336F4 ; =0x00000F0F
	mov r1, #9
	str r0, [sp]
	add r0, r4, #0
	mov r2, #1
	mov r3, #0
	bl MOD80_022332EC
	add r0, r4, #0
	mov r1, #0x10
	mov r2, #1
	bl MOD80_0222E6DC
_022336EC:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_022336F4: .word 0x00000F0F
	thumb_func_end MOD80_022336C4

	thumb_func_start MOD80_022336F8
MOD80_022336F8: ; 0x022336F8
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r1, _02233770 ; =gMain
	add r4, r0, #0
	ldr r2, [r1, #0x48]
	mov r1, #2
	tst r1, r2
	beq _02233714
	mov r1, #5
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r4, #0x2c]
_02233714:
	mov r0, #5
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _02233774 ; =0x0000011A
	ldr r1, _02233778 ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0xf
	bl FUN_02019064
	ldr r0, _02233778 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #5
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _0223377C ; =0x0000014E
	ldr r1, _02233780 ; =0x00000EE8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	ldr r0, _02233780 ; =0x00000EE8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #3
	str r0, [r4, #0x2c]
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_02233770: .word gMain
_02233774: .word 0x0000011A
_02233778: .word 0x00000ED8
_0223377C: .word 0x0000014E
_02233780: .word 0x00000EE8
	thumb_func_end MOD80_022336F8

	thumb_func_start MOD80_02233784
MOD80_02233784: ; 0x02233784
	push {r4, lr}
	ldr r2, _022337AC ; =0x00000FC8
	add r4, r0, #0
	ldr r3, _022337B0 ; =0x00000B34
	add r1, r4, r2
	sub r2, #0xf0
	ldr r3, [r4, r3]
	add r2, r4, r2
	bl MOD80_02234370
	ldr r1, _022337B4 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _022337B8 ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #4
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022337AC: .word 0x00000FC8
_022337B0: .word 0x00000B34
_022337B4: .word 0x00000FD4
_022337B8: .word 0x0000FFFF
	thumb_func_end MOD80_02233784

	thumb_func_start MOD80_022337BC
MOD80_022337BC: ; 0x022337BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02233878 ; =0x00000FD4
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0xb0
	bl MOD80_02234698
	cmp r0, #9
	bhi _022337F0
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022337DC: ; jump table
	.short _02233872 - _022337DC - 2 ; case 0
	.short _022337FA - _022337DC - 2 ; case 1
	.short _022337FA - _022337DC - 2 ; case 2
	.short _022337FA - _022337DC - 2 ; case 3
	.short _022337FA - _022337DC - 2 ; case 4
	.short _022337FA - _022337DC - 2 ; case 5
	.short _022337FA - _022337DC - 2 ; case 6
	.short _022337FA - _022337DC - 2 ; case 7
	.short _022337FA - _022337DC - 2 ; case 8
	.short _022337FA - _022337DC - 2 ; case 9
_022337F0:
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	beq _02233820
	b _02233872
_022337FA:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #6
	ldr r0, [r4, r0]
	add r2, r2, #4
	bl FUN_02001300
	ldr r0, _0223387C ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	mov r0, #5
	str r0, [r4, #0x2c]
	ldr r0, _02233880 ; =0x000005DC
	bl FUN_020054C8
	b _02233872
_02233820:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #6
	ldr r0, [r4, r0]
	add r2, r2, #4
	bl FUN_02001300
	ldr r0, _0223387C ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _02233884 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _02233888 ; =0x00000E98
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200D0E0
	ldr r0, _02233884 ; =0x00000ED8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _0223388C ; =0x00000EE8
	add r0, r4, r0
	bl FUN_02019178
	mov r1, #5
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r4, #0x2c]
	ldr r0, _02233880 ; =0x000005DC
	bl FUN_020054C8
_02233872:
	mov r0, #3
	pop {r4, pc}
	nop
_02233878: .word 0x00000FD4
_0223387C: .word 0x00000FC8
_02233880: .word 0x000005DC
_02233884: .word 0x00000ED8
_02233888: .word 0x00000E98
_0223388C: .word 0x00000EE8
	thumb_func_end MOD80_022337BC

	thumb_func_start MOD80_02233890
MOD80_02233890: ; 0x02233890
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r3, _022338D4 ; =0x00000B38
	add r4, r0, #0
	ldr r1, [r4, r3]
	mov r2, #0xfe
	lsl r2, r2, #4
	str r1, [sp]
	ldr r1, [r4, r2]
	sub r3, r3, #4
	str r1, [sp, #4]
	ldr r1, [r4]
	ldr r1, [r1, #0x10]
	str r1, [sp, #8]
	add r1, r2, #0
	sub r1, #0x18
	sub r2, #0xf8
	ldr r3, [r4, r3]
	add r1, r4, r1
	add r2, r4, r2
	bl MOD80_022344DC
	ldr r1, _022338D8 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _022338DC ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #6
	str r0, [r4, #0x2c]
	mov r0, #3
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_022338D4: .word 0x00000B38
_022338D8: .word 0x00000FD4
_022338DC: .word 0x0000FFFF
	thumb_func_end MOD80_02233890

	thumb_func_start MOD80_022338E0
MOD80_022338E0: ; 0x022338E0
	cmp r1, #0
	beq _022338EE
	cmp r1, #0xfe
	beq _022338F6
	cmp r1, #0xff
	beq _022338FE
	b _02233906
_022338EE:
	mov r1, #1
	strb r1, [r0, #2]
	add r0, r1, #0
	bx lr
_022338F6:
	mov r1, #2
	strb r1, [r0, #2]
	mov r0, #1
	bx lr
_022338FE:
	mov r1, #3
	strb r1, [r0, #2]
	mov r0, #1
	bx lr
_02233906:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD80_022338E0

	thumb_func_start MOD80_0223390C
MOD80_0223390C: ; 0x0223390C
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _02233A4C ; =0x00000FD4
	add r1, r4, #0
	ldr r0, [r4, r0]
	add r1, #0xb0
	bl MOD80_02234698
	add r5, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _02233932
	add r0, r0, #1
	cmp r5, r0
	bne _02233930
	b _02233A44
_02233930:
	b _0223398C
_02233932:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #0
	ldr r0, [r4, r0]
	add r1, #0xa
	add r2, #8
	bl FUN_02001300
	ldr r0, _02233A50 ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _02233A54 ; =0x00000EE8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _02233A58 ; =0x00000ED8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02233A54 ; =0x00000EE8
	add r0, r4, r0
	bl FUN_02019178
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r0, _02233A5C ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r3, [r4, r0]
	add r0, #0x38
	ldrh r2, [r3, #6]
	ldrh r1, [r3, #4]
	add r0, r4, r0
	add r1, r2, r1
	ldrh r2, [r3, #0xa]
	ldrh r3, [r3, #8]
	bl MOD80_022346F0
	b _02233A44
_0223398C:
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	sub r0, #0xc
	add r1, r2, #0
	ldr r0, [r4, r0]
	add r1, #0xa
	add r2, #8
	bl FUN_02001300
	ldr r0, _02233A50 ; =0x00000FC8
	ldr r0, [r4, r0]
	bl ListMenu_dtor
	ldr r0, _02233A58 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _02233A54 ; =0x00000EE8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	ldr r0, _02233A58 ; =0x00000ED8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02233A54 ; =0x00000EE8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02233A60 ; =0x00000B1C
	strh r5, [r4, r0]
	ldr r0, _02233A5C ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	mov r1, #0x12 ; BASE_GENDER_RATIO
	bl GetMonBaseStat
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	str r0, [r2, #0x20]
	ldr r1, [r4, r1]
	ldr r0, _02233A60 ; =0x00000B1C
	ldr r1, [r1, #0x20]
	add r0, r4, r0
	bl MOD80_022338E0
	cmp r0, #0
	beq _02233A00
	mov r0, #0xa
	str r0, [r4, #0x2c]
	ldr r0, _02233A64 ; =0x00000B1E
	ldrsb r1, [r4, r0]
	b _02233A06
_02233A00:
	mov r0, #7
	str r0, [r4, #0x2c]
	mov r1, #3
_02233A06:
	ldr r2, _02233A60 ; =0x00000B1C
	ldr r3, _02233A68 ; =0x00000F08
	ldrsh r0, [r4, r2]
	add r3, r4, r3
	str r0, [sp]
	mov r0, #0
	str r1, [sp, #4]
	mvn r0, r0
	str r0, [sp, #8]
	add r0, r2, #0
	add r1, r2, #0
	add r0, #0x18
	add r1, #0x1c
	add r2, #0x14
	ldr r0, [r4, r0]
	ldr r1, [r4, r1]
	ldr r2, [r4, r2]
	bl MOD80_02233FB4
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r3, [r4, r0]
	add r0, #0x38
	ldrh r2, [r3, #6]
	ldrh r1, [r3, #4]
	add r0, r4, r0
	add r1, r2, r1
	ldrh r2, [r3, #0xa]
	ldrh r3, [r3, #8]
	bl MOD80_022346F0
_02233A44:
	mov r0, #3
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_02233A4C: .word 0x00000FD4
_02233A50: .word 0x00000FC8
_02233A54: .word 0x00000EE8
_02233A58: .word 0x00000ED8
_02233A5C: .word 0x000005DC
_02233A60: .word 0x00000B1C
_02233A64: .word 0x00000B1E
_02233A68: .word 0x00000F08
	thumb_func_end MOD80_0223390C

	thumb_func_start MOD80_02233A6C
MOD80_02233A6C: ; 0x02233A6C
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r1, _02233ABC ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0xa
	mov r2, #1
	mov r3, #0
	bl MOD80_022332EC
	add r0, r4, #0
	mov r1, #0x10
	mov r2, #8
	bl MOD80_0222E6DC
	mov r0, #0xa
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02233AC0 ; =0x0000011A
	ldr r1, _02233AC4 ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0x15
	bl FUN_02019064
	ldr r0, _02233AC4 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02233ABC: .word 0x00000F0F
_02233AC0: .word 0x0000011A
_02233AC4: .word 0x00000ED8
	thumb_func_end MOD80_02233A6C

	thumb_func_start MOD80_02233AC8
MOD80_02233AC8: ; 0x02233AC8
	push {r4, lr}
	ldr r1, _02233AF0 ; =0x00000FC8
	add r4, r0, #0
	ldr r2, _02233AF4 ; =0x00000B34
	add r0, r4, r1
	sub r1, #0xf0
	ldr r2, [r4, r2]
	add r1, r4, r1
	bl MOD80_02234560
	ldr r1, _02233AF8 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _02233AFC ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #9
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02233AF0: .word 0x00000FC8
_02233AF4: .word 0x00000B34
_02233AF8: .word 0x00000FD4
_02233AFC: .word 0x0000FFFF
	thumb_func_end MOD80_02233AC8

	thumb_func_start MOD80_02233B00
MOD80_02233B00: ; 0x02233B00
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02233BCC ; =0x00000FD4
	add r1, r5, #0
	ldr r0, [r5, r0]
	add r1, #0xb0
	bl MOD80_02234698
	add r4, r0, #0
	cmp r4, #2
	bhi _02233B26
	cmp r4, #0
	beq _02233B6A
	cmp r4, #1
	beq _02233B6A
	cmp r4, #2
	beq _02233B6A
	b _02233BC6
_02233B26:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _02233BC6
	ldr r0, _02233BCC ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _02233BD0 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02233BD4 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02233BD8 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200D0E0
	ldr r0, _02233BD4 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02233BDC ; =0x000005DC
	bl FUN_020054C8
	mov r0, #0
	str r0, [r5, #0x2c]
	b _02233BC6
_02233B6A:
	ldr r0, _02233BCC ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _02233BD0 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02233BD4 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02233BD4 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02233BDC ; =0x000005DC
	bl FUN_020054C8
	ldr r3, _02233BE0 ; =0x00000F08
	ldr r2, _02233BE4 ; =0x00000B1E
	add r0, r4, #1
	strb r0, [r5, r2]
	mov r1, #0xa
	str r1, [r5, #0x2c]
	sub r0, r2, #2
	ldrsh r0, [r5, r0]
	sub r1, #0xb
	add r3, r5, r3
	str r0, [sp]
	ldrsb r0, [r5, r2]
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r2, #0
	add r1, r2, #0
	add r0, #0x16
	add r1, #0x1a
	add r2, #0x12
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl MOD80_02233FB4
_02233BC6:
	mov r0, #3
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02233BCC: .word 0x00000FD4
_02233BD0: .word 0x00000FC8
_02233BD4: .word 0x00000ED8
_02233BD8: .word 0x00000E98
_02233BDC: .word 0x000005DC
_02233BE0: .word 0x00000F08
_02233BE4: .word 0x00000B1E
	thumb_func_end MOD80_02233B00

	thumb_func_start MOD80_02233BE8
MOD80_02233BE8: ; 0x02233BE8
	push {r3, r4, lr}
	sub sp, #0x14
	ldr r1, _02233C38 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0xb
	mov r2, #1
	mov r3, #0
	bl MOD80_022332EC
	add r0, r4, #0
	mov r1, #0x10
	mov r2, #0xb
	bl MOD80_0222E6DC
	mov r0, #5
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0xd
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, _02233C3C ; =0x0000011A
	ldr r1, _02233C40 ; =0x00000ED8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #0xf
	bl FUN_02019064
	ldr r0, _02233C40 ; =0x00000ED8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #3
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02233C38: .word 0x00000F0F
_02233C3C: .word 0x0000011A
_02233C40: .word 0x00000ED8
	thumb_func_end MOD80_02233BE8

	thumb_func_start MOD80_02233C44
MOD80_02233C44: ; 0x02233C44
	push {r4, lr}
	ldr r1, _02233C6C ; =0x00000FC8
	add r4, r0, #0
	ldr r2, _02233C70 ; =0x00000B34
	add r0, r4, r1
	sub r1, #0xf0
	ldr r2, [r4, r2]
	add r1, r4, r1
	bl MOD80_022345D0
	ldr r1, _02233C74 ; =0x00000FD4
	str r0, [r4, r1]
	add r0, r4, #0
	ldr r1, _02233C78 ; =0x0000FFFF
	add r0, #0xb0
	strh r1, [r0]
	mov r0, #0xc
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02233C6C: .word 0x00000FC8
_02233C70: .word 0x00000B34
_02233C74: .word 0x00000FD4
_02233C78: .word 0x0000FFFF
	thumb_func_end MOD80_02233C44

	thumb_func_start MOD80_02233C7C
MOD80_02233C7C: ; 0x02233C7C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _02233D6C ; =0x00000FD4
	add r1, r5, #0
	ldr r0, [r5, r0]
	add r1, #0xb0
	bl MOD80_02234698
	add r4, r0, #0
	cmp r4, #0xc
	beq _02233CA4
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02233CA4
	add r0, r0, #1
	cmp r4, r0
	beq _02233D66
	b _02233CFA
_02233CA4:
	ldr r0, _02233D6C ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _02233D70 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02233D74 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02233D78 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200D0E0
	ldr r0, _02233D74 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02233D7C ; =0x000005DC
	bl FUN_020054C8
	mov r1, #0xfe
	lsl r1, r1, #4
	ldr r1, [r5, r1]
	ldr r0, _02233D80 ; =0x00000B1C
	ldr r1, [r1, #0x20]
	add r0, r5, r0
	bl MOD80_022338E0
	cmp r0, #0
	beq _02233CF4
	mov r0, #0
	str r0, [r5, #0x2c]
	b _02233D66
_02233CF4:
	mov r0, #7
	str r0, [r5, #0x2c]
	b _02233D66
_02233CFA:
	ldr r0, _02233D7C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02233D6C ; =0x00000FD4
	mov r1, #0
	ldr r0, [r5, r0]
	add r2, r1, #0
	bl FUN_02001300
	ldr r0, _02233D70 ; =0x00000FC8
	ldr r0, [r5, r0]
	bl ListMenu_dtor
	ldr r0, _02233D74 ; =0x00000ED8
	mov r1, #0
	add r0, r5, r0
	bl FUN_0200CCF8
	ldr r0, _02233D74 ; =0x00000ED8
	add r0, r5, r0
	bl FUN_02019178
	ldr r0, _02233D80 ; =0x00000B1C
	add r1, r4, #0
	add r0, r5, r0
	bl MOD80_02234640
	mov r0, #0xd
	ldr r1, _02233D84 ; =0x00000B1F
	str r0, [r5, #0x2c]
	ldrsb r0, [r5, r1]
	add r1, r1, #1
	ldrsb r1, [r5, r1]
	bl MOD80_02234668
	ldr r2, _02233D80 ; =0x00000B1C
	ldr r3, _02233D88 ; =0x00000F08
	ldrsh r1, [r5, r2]
	add r3, r5, r3
	str r1, [sp]
	add r1, r2, #2
	ldrsb r1, [r5, r1]
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r2, #0
	add r1, r2, #0
	add r0, #0x18
	add r1, #0x1c
	add r2, #0x14
	ldr r0, [r5, r0]
	ldr r1, [r5, r1]
	ldr r2, [r5, r2]
	bl MOD80_02233FB4
_02233D66:
	mov r0, #3
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_02233D6C: .word 0x00000FD4
_02233D70: .word 0x00000FC8
_02233D74: .word 0x00000ED8
_02233D78: .word 0x00000E98
_02233D7C: .word 0x000005DC
_02233D80: .word 0x00000B1C
_02233D84: .word 0x00000B1F
_02233D88: .word 0x00000F08
	thumb_func_end MOD80_02233C7C

	thumb_func_start MOD80_02233D8C
MOD80_02233D8C: ; 0x02233D8C
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02233DB0 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x17
	mov r2, #1
	mov r3, #0
	bl MOD80_022332EC
	add r0, r4, #0
	mov r1, #0x10
	mov r2, #0xe
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02233DB0: .word 0x00000F0F
	thumb_func_end MOD80_02233D8C

	thumb_func_start MOD80_02233DB4
MOD80_02233DB4: ; 0x02233DB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _02233DD0 ; =0x000001EA
	mov r1, #0xf
	bl MOD80_0222E6A8
	ldr r1, _02233DD4 ; =0x00000FCC
	str r0, [r4, r1]
	mov r0, #0xf
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	nop
_02233DD0: .word 0x000001EA
_02233DD4: .word 0x00000FCC
	thumb_func_end MOD80_02233DB4

	thumb_func_start MOD80_02233DD8
MOD80_02233DD8: ; 0x02233DD8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02233E28 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02233E22
	sub r1, r1, #1
	cmp r0, r1
	bne _02233E04
	mov r1, #5
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r4, #0x2c]
	b _02233E22
_02233E04:
	mov r1, #7
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #2
	str r0, [r4, #0x2c]
	ldr r0, _02233E2C ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0xd4
	add r1, r4, #0
	bl MOD80_02234330
_02233E22:
	mov r0, #3
	pop {r4, pc}
	nop
_02233E28: .word 0x00000FCC
_02233E2C: .word 0x0000100C
	thumb_func_end MOD80_02233DD8

	thumb_func_start MOD80_02233E30
MOD80_02233E30: ; 0x02233E30
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	bne _02233E5C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, _02233E80 ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	b _02233E74
_02233E5C:
	mov r0, #6
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
_02233E74:
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02233E80: .word 0x0000100C
	thumb_func_end MOD80_02233E30

	thumb_func_start MOD80_02233E84
MOD80_02233E84: ; 0x02233E84
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02233E9E
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02233E9E:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02233E84

	thumb_func_start MOD80_02233EA4
MOD80_02233EA4: ; 0x02233EA4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	add r5, r3, #0
	cmp r2, #0
	beq _02233ED2
	add r0, r1, #0
	add r1, r2, #0
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [sp, #0x1c]
	str r5, [sp]
	str r0, [sp, #4]
	ldr r3, [sp, #0x18]
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD80_02236D50
	add r0, r4, #0
	bl String_dtor
_02233ED2:
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD80_02233EA4

	thumb_func_start MOD80_02233ED8
MOD80_02233ED8: ; 0x02233ED8
	cmp r0, #1
	bne _02233EE2
	ldr r0, _02233EF0 ; =0x02237B48
	ldr r0, [r0]
	bx lr
_02233EE2:
	cmp r0, #2
	bne _02233EEA
	ldr r0, _02233EF0 ; =0x02237B48
	ldr r1, [r0, #4]
_02233EEA:
	add r0, r1, #0
	bx lr
	nop
_02233EF0: .word MOD80_02237B48
	thumb_func_end MOD80_02233ED8

	thumb_func_start MOD80_02233EF4
MOD80_02233EF4: ; 0x02233EF4
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	add r5, r2, #0
	cmp r3, #0
	bne _02233F04
	cmp r5, #3
	beq _02233F54
_02233F04:
	add r0, r1, #0
	ldr r1, _02233F58 ; =0x022373C0
	lsl r2, r5, #2
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [sp, #0x1c]
	cmp r0, #3
	ble _02233F34
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl MOD80_02233ED8
	mov r1, #0
	str r1, [sp]
	str r0, [sp, #4]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x18]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD80_02236D50
	b _02233F4E
_02233F34:
	ldr r1, [sp, #0x20]
	add r0, r5, #0
	bl MOD80_02233ED8
	ldr r1, [sp, #0x1c]
	ldr r3, [sp, #0x18]
	str r1, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD80_02236D50
_02233F4E:
	add r0, r4, #0
	bl String_dtor
_02233F54:
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_02233F58: .word MOD80_022373C0
	thumb_func_end MOD80_02233EF4

	thumb_func_start MOD80_02233F5C
MOD80_02233F5C: ; 0x02233F5C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0
	mvn r0, r0
	add r5, r3, #0
	cmp r2, r0
	beq _02233F92
	add r0, r1, #0
	ldr r1, _02233F98 ; =0x02237494
	lsl r2, r2, #3
	ldr r1, [r1, r2]
	bl NewString_ReadMsgData
	add r4, r0, #0
	ldr r0, [sp, #0x1c]
	str r5, [sp]
	str r0, [sp, #4]
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x18]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD80_02236D50
	add r0, r4, #0
	bl String_dtor
_02233F92:
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_02233F98: .word MOD80_02237494
	thumb_func_end MOD80_02233F5C

	thumb_func_start MOD80_02233F9C
MOD80_02233F9C: ; 0x02233F9C
	push {r3, r4, lr}
	sub sp, #0xc
	ldr r4, [sp, #0x18]
	str r4, [sp]
	ldr r4, [sp, #0x1c]
	str r4, [sp, #4]
	mov r4, #0
	str r4, [sp, #8]
	bl MOD80_02233F5C
	add sp, #0xc
	pop {r3, r4, pc}
	thumb_func_end MOD80_02233F9C

	thumb_func_start MOD80_02233FB4
MOD80_02233FB4: ; 0x02233FB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	mov r1, #0x61
	str r0, [sp, #0xc]
	add r6, r3, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, _02234044 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	ldr r1, [sp, #0x14]
	add r0, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	add r5, r6, #0
	mov r4, #1
	add r5, #0x10
	mov r7, #0
_02233FE0:
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_02019620
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #3
	blt _02233FE0
	mov r3, #0
	ldr r0, _02234044 ; =0x000F0200
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x30]
	add r0, #0x10
	bl MOD80_02233EA4
	ldr r2, [sp, #0x34]
	sub r0, r2, #1
	cmp r0, #1
	bhi _02234022
	mov r3, #0
	str r3, [sp]
	mov r0, #0x46
	str r0, [sp, #4]
	ldr r0, _02234044 ; =0x000F0200
	ldr r1, [sp, #0xc]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x10
	bl MOD80_02233EF4
_02234022:
	mov r0, #0
	str r0, [sp]
	ldr r0, _02234044 ; =0x000F0200
	add r6, #0x20
	str r0, [sp, #4]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x38]
	add r0, r6, #0
	mov r3, #2
	bl MOD80_02233F9C
	ldr r0, [sp, #0x14]
	bl String_dtor
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02234044: .word 0x000F0200
	thumb_func_end MOD80_02233FB4

	thumb_func_start MOD80_02234048
MOD80_02234048: ; 0x02234048
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x10]
	mov r1, #0x61
	str r0, [sp, #0xc]
	add r6, r3, #0
	bl NewString_ReadMsgData
	str r0, [sp, #0x14]
	mov r2, #0
	ldr r0, _022340D8 ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	ldr r1, [sp, #0x14]
	add r0, r6, #0
	add r3, r2, #0
	bl MOD80_02236D50
	add r5, r6, #0
	mov r4, #1
	add r5, #0x10
	mov r7, #0
_02234074:
	add r0, r5, #0
	add r1, r7, #0
	bl FUN_02019620
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #3
	blt _02234074
	mov r3, #0
	ldr r0, _022340D8 ; =0x000F0200
	str r3, [sp]
	str r0, [sp, #4]
	add r0, r6, #0
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x30]
	add r0, #0x10
	bl MOD80_02233EA4
	ldr r2, [sp, #0x34]
	sub r0, r2, #1
	cmp r0, #1
	bhi _022340B6
	mov r3, #0
	str r3, [sp]
	mov r0, #0x46
	str r0, [sp, #4]
	ldr r0, _022340D8 ; =0x000F0200
	ldr r1, [sp, #0xc]
	str r0, [sp, #8]
	add r0, r6, #0
	add r0, #0x10
	bl MOD80_02233EF4
_022340B6:
	mov r0, #0
	str r0, [sp]
	ldr r0, _022340D8 ; =0x000F0200
	add r6, #0x20
	str r0, [sp, #4]
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x38]
	add r0, r6, #0
	mov r3, #2
	bl MOD80_02233F9C
	ldr r0, [sp, #0x14]
	bl String_dtor
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022340D8: .word 0x000F0200
	thumb_func_end MOD80_02234048

	thumb_func_start MOD80_022340DC
MOD80_022340DC: ; 0x022340DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r0, #0
	add r5, r1, #0
	mov r0, #0xb
	mov r1, #0x3e
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	ldr r7, [sp, #0x38]
	bl String_ctor
	str r0, [sp, #0x18]
	mov r0, #0xb
	mov r1, #0x3e
	bl String_ctor
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x18]
	mov r1, #0x76
	bl GetBoxMonData
	ldr r0, [sp, #0xc]
	mov r1, #0x6f
	mov r2, #0
	bl GetBoxMonData
	add r6, r0, #1
	ldr r0, [sp, #0xc]
	bl CalcBoxMonLevel
	str r0, [sp, #0x10]
	add r0, r4, #0
	mov r1, #0x64
	bl NewString_ReadMsgData
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	mov r1, #3
	str r0, [sp, #4]
	ldr r2, [sp, #0x10]
	add r0, r5, #0
	add r3, r1, #0
	bl BufferIntegerAsString
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x66
	mov r3, #0x3e
	bl ReadMsgData_ExpandPlaceholders
	str r0, [sp, #0x1c]
	cmp r6, #3
	beq _0223415A
	ldr r1, _022341F8 ; =0x022373C0
	lsl r2, r6, #2
	ldr r1, [r1, r2]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	bl ReadMsgDataIntoString
_0223415A:
	ldr r5, [sp, #8]
	mov r4, #0
_0223415E:
	add r0, r5, #0
	mov r1, #0
	bl FUN_02019620
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #3
	blt _0223415E
	mov r2, #0
	ldr r0, _022341FC ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x20]
	add r3, r2, #0
	bl MOD80_02236D50
	mov r2, #0
	ldr r0, _022341FC ; =0x000F0200
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x18]
	add r0, #0x10
	add r3, r2, #0
	bl MOD80_02236D50
	mov r0, #2
	str r0, [sp]
	ldr r0, _022341FC ; =0x000F0200
	mov r2, #0
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	ldr r1, [sp, #0x1c]
	add r0, #0x20
	add r3, r2, #0
	bl MOD80_02236D50
	cmp r6, #3
	beq _022341CA
	sub r0, r6, #1
	mov r3, #0
	lsl r1, r0, #2
	ldr r0, _02234200 ; =0x02237B48
	str r3, [sp]
	ldr r0, [r0, r1]
	ldr r1, [sp, #0x14]
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	mov r2, #0x46
	add r0, #0x10
	str r0, [sp, #8]
	bl MOD80_02236D50
_022341CA:
	ldr r0, [sp, #0xc]
	mov r1, #5
	mov r2, #0
	bl GetBoxMonData
	strh r0, [r7]
	ldr r0, [sp, #0x10]
	strb r6, [r7, #2]
	strb r0, [r7, #3]
	ldr r0, [sp, #0x1c]
	bl String_dtor
	ldr r0, [sp, #0x14]
	bl String_dtor
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x20]
	bl String_dtor
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022341F8: .word MOD80_022373C0
_022341FC: .word 0x000F0200
_02234200: .word MOD80_02237B48
	thumb_func_end MOD80_022340DC

	thumb_func_start MOD80_02234204
MOD80_02234204: ; 0x02234204
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r2, #0
	mov r2, #0
	add r3, r0, #0
	str r2, [sp]
	add r0, sp, #8
	str r0, [sp, #4]
	mov r0, #0x4b
	mov r1, #0xd
	bl FUN_02006D18
	ldr r1, [sp, #8]
	lsr r1, r1, #1
	str r1, [r4]
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02234204

	thumb_func_start MOD80_02234228
MOD80_02234228: ; 0x02234228
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r1, _02234280 ; =0x000001EE
	add r5, r0, #0
	mov r0, #0x3e
	bl AllocFromHeap
	add r4, r0, #0
	ldr r2, _02234280 ; =0x000001EE
	mov r0, #0
	add r1, r4, #0
	bl MIi_CpuClearFast
	mov r2, #0
	str r2, [sp]
	add r0, sp, #8
	str r0, [sp, #4]
	mov r0, #0x4b
	mov r1, #0xc
	add r3, r5, #0
	bl FUN_02006D18
	add r7, r0, #0
	ldr r0, [sp, #8]
	ldr r5, _02234284 ; =0x00000000
	lsr r3, r0, #1
	beq _02234274
	ldr r0, _02234280 ; =0x000001EE
	add r6, r7, #0
	mov r1, #1
_02234264:
	ldrh r2, [r6]
	cmp r2, r0
	bhs _0223426C
	strb r1, [r4, r2]
_0223426C:
	add r5, r5, #1
	add r6, r6, #2
	cmp r5, r3
	blo _02234264
_02234274:
	add r0, r7, #0
	bl FreeToHeap
	add r0, r4, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02234280: .word 0x000001EE
_02234284: .word 0x00000000
	thumb_func_end MOD80_02234228

	thumb_func_start MOD80_02234288
MOD80_02234288: ; 0x02234288
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xb8
	ldrh r0, [r0]
	bl MOD80_02232FAC
	cmp r0, #0
	beq _022342B0
	bl SizeOfStructPokemon
	add r2, r0, #0
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	add r1, r5, #0
	bl MIi_CpuCopyFast
	b _022342BC
_022342B0:
	add r0, r4, #0
	add r0, #0xbc
	ldr r0, [r0]
	add r1, r5, #0
	bl FUN_02069A64
_022342BC:
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl PlayerProfile_GetNamePtr
	add r1, r0, #0
	mov r0, #0x43
	lsl r0, r0, #2
	add r0, r5, r0
	mov r2, #8
	bl CopyU16StringArrayN
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl PlayerProfile_GetTrainerID_VisibleHalf
	mov r1, #0x47
	lsl r1, r1, #2
	strh r0, [r5, r1]
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	bl FUN_02029B38
	ldr r1, _02234324 ; =0x0000011E
	strb r0, [r5, r1]
	ldr r0, [r4]
	ldr r0, [r0, #0x18]
	bl FUN_02029B3C
	ldr r1, _02234328 ; =0x0000011F
	strb r0, [r5, r1]
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl FUN_02023A28
	mov r1, #0x12
	lsl r1, r1, #4
	strb r0, [r5, r1]
	ldr r0, [r4]
	ldr r0, [r0, #0x1c]
	bl PlayerProfile_GetTrainerGender
	add r1, r5, #0
	add r1, #0xf6
	strb r0, [r1]
	ldr r0, _0223432C ; =0x00000122
	mov r1, #GAME_VERSION
	strb r1, [r5, r0]
	mov r1, #2
	add r0, r0, #1
	strb r1, [r5, r0]
	pop {r3, r4, r5, pc}
	nop
_02234324: .word 0x0000011E
_02234328: .word 0x0000011F
_0223432C: .word 0x00000122
	thumb_func_end MOD80_02234288

	thumb_func_start MOD80_02234330
MOD80_02234330: ; 0x02234330
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD80_02234288
	ldr r0, _0223436C ; =0x00000B18
	add r1, r5, #0
	ldrh r2, [r4, r0]
	add r1, #0xec
	strh r2, [r1]
	add r1, r0, #2
	ldrh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xee
	strh r2, [r1]
	add r1, r0, #4
	ldrh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xf0
	strh r2, [r1]
	add r1, r0, #6
	ldrh r2, [r4, r1]
	add r1, r5, #0
	add r1, #0xf2
	strh r2, [r1]
	add r0, #8
	ldrh r0, [r4, r0]
	add r5, #0xf4
	strh r0, [r5]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223436C: .word 0x00000B18
	thumb_func_end MOD80_02234330

	thumb_func_start MOD80_02234370
MOD80_02234370: ; 0x02234370
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r0, #0
	add r5, r1, #0
	mov r0, #9
	mov r1, #0x3e
	str r2, [sp]
	add r6, r3, #0
	bl ListMenu_ctor
	str r0, [r5]
	mov r4, #0
_02234388:
	add r2, r4, #0
	ldr r0, [r5]
	add r1, r6, #0
	add r2, #0x68
	add r3, r4, #1
	bl ListMenu_ItemFromMsgData
	add r4, r4, #1
	cmp r4, #9
	blt _02234388
	ldr r3, _022343D8 ; =0x02237474
	add r2, sp, #4
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [sp]
	mov r2, #0x1f
	mov r3, #0xb
	str r0, [sp, #0x10]
	bl FUN_0200CCA4
	mov r0, #0xfe
	lsl r0, r0, #4
	ldr r2, [r7, r0]
	add r0, sp, #4
	ldrh r1, [r2, #6]
	ldrh r2, [r2, #4]
	mov r3, #0x3e
	bl FUN_020010A8
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022343D8: .word MOD80_02237474
	thumb_func_end MOD80_02234370

	thumb_func_start MOD80_022343DC
MOD80_022343DC: ; 0x022343DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp]
	ldr r0, [sp, #0x38]
	str r1, [sp, #4]
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x40]
	ldr r4, [sp, #0x44]
	lsl r5, r0, #1
	add r0, r0, #1
	lsl r1, r0, #1
	ldr r0, _022344D8 ; =0x02237B50
	str r2, [sp, #8]
	ldrh r1, [r0, r1]
	ldrh r0, [r0, r5]
	str r3, [sp, #0xc]
	mov r6, #0
	sub r7, r1, r0
	add r0, r4, #0
	bl FUN_02024CA4
	str r0, [sp, #0x14]
	ldr r0, _022344D8 ; =0x02237B50
	ldrh r0, [r0, r5]
	str r0, [sp, #0x18]
	add r0, r6, #0
	str r0, [sp, #0x1c]
	cmp r7, #0
	ble _02234456
	ldr r0, [sp, #0x18]
	lsl r1, r0, #1
	ldr r0, [sp, #0xc]
	add r5, r0, r1
_0223441E:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02234434
	ldrh r1, [r5]
	add r0, r4, #0
	bl FUN_020245F0
	cmp r0, #0
	beq _0223444A
	add r6, r6, #1
	b _0223444A
_02234434:
	ldrh r1, [r5]
	ldr r0, [sp, #0x38]
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _0223444A
	add r0, r4, #0
	bl FUN_020245F0
	cmp r0, #0
	beq _0223444A
	add r6, r6, #1
_0223444A:
	ldr r0, [sp, #0x1c]
	add r5, r5, #2
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, r7
	blt _0223441E
_02234456:
	add r0, r6, #1
	mov r1, #0x3e
	bl ListMenu_ctor
	ldr r1, [sp]
	str r0, [r1]
	mov r0, #0
	str r0, [sp, #0x10]
	cmp r7, #0
	ble _022344C2
	ldr r0, [sp, #0x18]
	lsl r1, r0, #1
	ldr r0, [sp, #0xc]
	add r5, r0, r1
_02234472:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02234494
	ldrh r1, [r5]
	add r0, r4, #0
	bl FUN_020245F0
	cmp r0, #0
	beq _022344B6
	ldrh r2, [r5]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	add r3, r2, #0
	bl ListMenu_ItemFromMsgData
	b _022344B6
_02234494:
	ldrh r1, [r5]
	ldr r0, [sp, #0x38]
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _022344B6
	add r0, r4, #0
	bl FUN_020245F0
	cmp r0, #0
	beq _022344B6
	ldrh r2, [r5]
	ldr r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	add r3, r2, #0
	bl ListMenu_ItemFromMsgData
_022344B6:
	ldr r0, [sp, #0x10]
	add r5, r5, #2
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, r7
	blt _02234472
_022344C2:
	ldr r0, [sp]
	mov r2, #0x75
	add r3, r2, #0
	ldr r0, [r0]
	ldr r1, [sp, #8]
	sub r3, #0x77
	bl ListMenu_ItemFromMsgData
	add r0, r6, #1
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022344D8: .word MOD80_02237B50
	thumb_func_end MOD80_022343DC

	thumb_func_start MOD80_022344DC
MOD80_022344DC: ; 0x022344DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	ldr r5, [sp, #0x54]
	add r7, r0, #0
	add r6, r1, #0
	add r0, r2, #0
	mov r1, #0xf
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	bl FUN_02019620
	ldrh r1, [r5, #6]
	ldrh r0, [r5, #4]
	ldr r2, [sp, #0x14]
	add r4, r1, r0
	ldr r0, [r5, #0x14]
	ldr r1, [sp, #0x50]
	str r0, [sp]
	ldr r0, [r5, #0x1c]
	str r0, [sp, #4]
	ldr r0, [sp, #0x58]
	str r4, [sp, #8]
	str r0, [sp, #0xc]
	ldr r3, [r5, #0x18]
	add r0, r6, #0
	bl MOD80_022343DC
	ldr r3, _02234558 ; =0x02237474
	add r5, r0, #0
	add r2, sp, #0x18
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, sp, #0x18
	strh r5, [r0, #0x10]
	ldr r0, [r6]
	mov r1, #0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x10]
	mov r2, #0x1f
	mov r3, #0xb
	str r0, [sp, #0x24]
	bl FUN_0200CCA4
	lsl r1, r4, #1
	ldr r2, _0223455C ; =0x0000101C
	add r3, r7, r1
	ldrh r1, [r3, r2]
	add r2, #0x14
	ldrh r2, [r3, r2]
	add r0, sp, #0x18
	mov r3, #0x3e
	bl FUN_020010A8
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02234558: .word MOD80_02237474
_0223455C: .word 0x0000101C
	thumb_func_end MOD80_022344DC

	thumb_func_start MOD80_02234560
MOD80_02234560: ; 0x02234560
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r0, #0
	str r1, [sp]
	mov r0, #4
	mov r1, #0x3e
	add r7, r2, #0
	bl ListMenu_ctor
	ldr r5, _022345C8 ; =0x02237B64
	str r0, [r6]
	mov r4, #0
_02234578:
	ldr r0, [r6]
	ldr r2, [r5]
	ldr r3, [r5, #4]
	add r1, r7, #0
	bl ListMenu_ItemFromMsgData
	add r4, r4, #1
	add r5, #8
	cmp r4, #4
	blt _02234578
	ldr r3, _022345CC ; =0x02237474
	add r2, sp, #4
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r1, #4
	add r0, sp, #4
	strh r1, [r0, #0x10]
	ldr r0, [r6]
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [sp]
	mov r2, #0x1f
	mov r3, #0xb
	str r0, [sp, #0x10]
	bl FUN_0200CCA4
	mov r1, #0
	add r0, sp, #4
	add r2, r1, #0
	mov r3, #0x3e
	bl FUN_020010A8
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022345C8: .word MOD80_02237B64
_022345CC: .word MOD80_02237474
	thumb_func_end MOD80_02234560

	thumb_func_start MOD80_022345D0
MOD80_022345D0: ; 0x022345D0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r0, #0
	str r1, [sp]
	mov r0, #0xd
	mov r1, #0x3e
	add r7, r2, #0
	bl ListMenu_ctor
	ldr r5, _02234638 ; =0x02237494
	str r0, [r6]
	mov r4, #0
_022345E8:
	ldr r0, [r6]
	ldr r2, [r5]
	add r1, r7, #0
	add r3, r4, #0
	bl ListMenu_ItemFromMsgData
	add r4, r4, #1
	add r5, #8
	cmp r4, #0xd
	blt _022345E8
	ldr r3, _0223463C ; =0x02237474
	add r2, sp, #4
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r1, #0xd
	add r0, sp, #4
	strh r1, [r0, #0x10]
	ldr r0, [r6]
	mov r1, #0
	str r0, [sp, #4]
	ldr r0, [sp]
	mov r2, #0x1f
	mov r3, #0xb
	str r0, [sp, #0x10]
	bl FUN_0200CCA4
	mov r1, #0
	add r0, sp, #4
	add r2, r1, #0
	mov r3, #0x3e
	bl FUN_020010A8
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02234638: .word MOD80_02237494
_0223463C: .word MOD80_02237474
	thumb_func_end MOD80_022345D0

	thumb_func_start MOD80_02234640
MOD80_02234640: ; 0x02234640
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #0xc
	blt _0223464E
	bl ErrorHandling
_0223464E:
	ldr r0, _02234660 ; =0x02237498
	lsl r1, r5, #3
	ldrsh r0, [r0, r1]
	strb r0, [r4, #3]
	ldr r0, _02234664 ; =0x0223749A
	ldrsh r0, [r0, r1]
	strb r0, [r4, #4]
	pop {r3, r4, r5, pc}
	nop
_02234660: .word MOD80_02237498
_02234664: .word MOD80_0223749A
	thumb_func_end MOD80_02234640

	thumb_func_start MOD80_02234668
MOD80_02234668: ; 0x02234668
	push {r3, r4, r5, r6}
	ldr r6, _02234694 ; =0x02237494
	mov r5, #0
	mov r2, #6
	mov r3, #4
_02234672:
	ldrsh r4, [r6, r3]
	cmp r0, r4
	bne _02234684
	ldrsh r4, [r6, r2]
	cmp r1, r4
	bne _02234684
	add r0, r5, #0
	pop {r3, r4, r5, r6}
	bx lr
_02234684:
	add r5, r5, #1
	add r6, #8
	cmp r5, #0xd
	blt _02234672
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
	nop
_02234694: .word MOD80_02237494
	thumb_func_end MOD80_02234668

	thumb_func_start MOD80_02234698
MOD80_02234698: ; 0x02234698
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02001204
	add r6, r0, #0
	add r0, r5, #0
	add r1, sp, #0
	bl FUN_0200143C
	add r0, sp, #0
	ldrh r1, [r4]
	ldrh r0, [r0]
	cmp r1, r0
	beq _022346CA
	ldr r0, _022346D0 ; =0x0000FFFF
	cmp r1, r0
	beq _022346C4
	ldr r0, _022346D4 ; =0x000005DC
	bl FUN_020054C8
_022346C4:
	add r0, sp, #0
	ldrh r0, [r0]
	strh r0, [r4]
_022346CA:
	add r0, r6, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022346D0: .word 0x0000FFFF
_022346D4: .word 0x000005DC
	thumb_func_end MOD80_02234698

	thumb_func_start MOD80_022346D8
MOD80_022346D8: ; 0x022346D8
	mov r2, #0
	add r3, r0, #0
	add r1, r2, #0
_022346DE:
	strh r1, [r3, #4]
	strh r1, [r3, #0x18]
	add r2, r2, #1
	add r3, r3, #2
	cmp r2, #0xa
	blt _022346DE
	strh r1, [r0]
	strh r1, [r0, #2]
	bx lr
	thumb_func_end MOD80_022346D8

	thumb_func_start MOD80_022346F0
MOD80_022346F0: ; 0x022346F0
	lsl r1, r1, #1
	add r0, r0, r1
	strh r2, [r0, #4]
	strh r3, [r0, #0x18]
	bx lr
	.align 2, 0
	thumb_func_end MOD80_022346F0

	thumb_func_start MOD80_022346FC
MOD80_022346FC: ; 0x022346FC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_022349A4
	ldr r0, [r4, #4]
	bl MOD80_02234780
	add r0, r4, #0
	bl MOD80_022348CC
	add r0, r4, #0
	bl MOD80_02234958
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	add r0, r4, #0
	bl MOD80_02236D84
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD80_022346FC

	thumb_func_start MOD80_02234740
MOD80_02234740: ; 0x02234740
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222E79C
	bl FUN_02033EEC
	ldr r1, [r4, #0x2c]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _0223475C ; =0x02237BC8
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0223475C: .word MOD80_02237BC8
	thumb_func_end MOD80_02234740

	thumb_func_start MOD80_02234760
MOD80_02234760: ; 0x02234760
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_022349BC
	add r0, r4, #0
	bl MOD80_02234994
	ldr r0, [r4, #4]
	bl MOD80_022348A0
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02234760

	thumb_func_start MOD80_02234780
MOD80_02234780: ; 0x02234780
	push {r4, r5, lr}
	sub sp, #0x9c
	ldr r5, _02234888 ; =0x022374FC
	add r3, sp, #0x8c
	add r4, r0, #0
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _0223488C ; =0x02237544
	add r3, sp, #0x70
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02234890 ; =0x02237528
	add r3, sp, #0x54
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _02234894 ; =0x0223757C
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #2
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _02234898 ; =0x02237560
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _0223489C ; =0x0223750C
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #0x10
	mov r1, #1
	bl FUN_0201E74C
	add sp, #0x9c
	pop {r4, r5, pc}
	nop
_02234888: .word MOD80_022374FC
_0223488C: .word MOD80_02237544
_02234890: .word MOD80_02237528
_02234894: .word MOD80_0223757C
_02234898: .word MOD80_02237560
_0223489C: .word MOD80_0223750C
	thumb_func_end MOD80_02234780

	thumb_func_start MOD80_022348A0
MOD80_022348A0: ; 0x022348A0
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #2
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_022348A0

	thumb_func_start MOD80_022348CC
MOD80_022348CC: ; 0x022348CC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r0, #0x60
	mov r1, #0
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x68
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	ldr r0, _02234954 ; =0x00000FEC
	ldrh r0, [r5, r0]
	cmp r0, #0
	bne _02234944
	mov r0, #4
	mov r1, #0
	bl FUN_0201797C
	mov r0, #5
	mov r1, #0
	bl FUN_0201797C
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E74C
_02234944:
	ldr r0, [r5, #0x20]
	cmp r0, #9
	bne _02234950
	add r0, r5, #0
	bl MOD80_0222F338
_02234950:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02234954: .word 0x00000FEC
	thumb_func_end MOD80_022348CC

	thumb_func_start MOD80_02234958
MOD80_02234958: ; 0x02234958
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	ldr r1, _02234990 ; =0x00000E98
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	ldr r0, _02234990 ; =0x00000E98
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02234990: .word 0x00000E98
	thumb_func_end MOD80_02234958

	thumb_func_start MOD80_02234994
MOD80_02234994: ; 0x02234994
	ldr r1, _0223499C ; =0x00000E98
	ldr r3, _022349A0 ; =FUN_02019178
	add r0, r0, r1
	bx r3
	.align 2, 0
_0223499C: .word 0x00000E98
_022349A0: .word FUN_02019178
	thumb_func_end MOD80_02234994

	thumb_func_start MOD80_022349A4
MOD80_022349A4: ; 0x022349A4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _022349B8 ; =0x00000B4C
	str r0, [r4, r1]
	pop {r4, pc}
	nop
_022349B8: .word 0x00000B4C
	thumb_func_end MOD80_022349A4

	thumb_func_start MOD80_022349BC
MOD80_022349BC: ; 0x022349BC
	ldr r1, _022349C4 ; =0x00000B4C
	ldr r3, _022349C8 ; =String_dtor
	ldr r0, [r0, r1]
	bx r3
	.align 2, 0
_022349C4: .word 0x00000B4C
_022349C8: .word String_dtor
	thumb_func_end MOD80_022349BC

	thumb_func_start MOD80_022349CC
MOD80_022349CC: ; 0x022349CC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r1, [r4, #0x24]
	cmp r1, #0xc
	bhi _02234AA4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022349E4: ; jump table
	.short _02234AA4 - _022349E4 - 2 ; case 0
	.short _02234AA4 - _022349E4 - 2 ; case 1
	.short _02234AA4 - _022349E4 - 2 ; case 2
	.short _02234AA4 - _022349E4 - 2 ; case 3
	.short _02234AA4 - _022349E4 - 2 ; case 4
	.short _02234AA4 - _022349E4 - 2 ; case 5
	.short _02234AA4 - _022349E4 - 2 ; case 6
	.short _022349FE - _022349E4 - 2 ; case 7
	.short _02234A1A - _022349E4 - 2 ; case 8
	.short _02234A36 - _022349E4 - 2 ; case 9
	.short _02234A52 - _022349E4 - 2 ; case 10
	.short _02234A74 - _022349E4 - 2 ; case 11
	.short _02234A8A - _022349E4 - 2 ; case 12
_022349FE:
	ldr r1, _02234AB4 ; =0x00000F0F
	mov r2, #0x18
	str r1, [sp]
	ldr r1, _02234AB8 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #2
	bl MOD80_0222E6DC
	b _02234AA8
_02234A1A:
	ldr r1, _02234AB4 ; =0x00000F0F
	mov r2, #0x18
	str r1, [sp]
	ldr r1, _02234AB8 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #7
	bl MOD80_0222E6DC
	b _02234AA8
_02234A36:
	ldr r1, _02234AB4 ; =0x00000F0F
	mov r2, #0x18
	str r1, [sp]
	ldr r1, _02234AB8 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0xc
	bl MOD80_0222E6DC
	b _02234AA8
_02234A52:
	ldr r1, _02234AB4 ; =0x00000F0F
	mov r2, #0x18
	str r1, [sp]
	ldr r1, _02234AB8 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x12
	bl MOD80_0222E6DC
	ldr r0, _02234ABC ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	b _02234AA8
_02234A74:
	ldr r1, _02234AB4 ; =0x00000F0F
	mov r2, #0x18
	str r1, [sp]
	ldr r1, _02234AB8 ; =0x00000B34
	mov r3, #0
	ldr r1, [r4, r1]
	bl MOD80_02236C70
	mov r0, #0x18
	str r0, [r4, #0x2c]
	b _02234AA8
_02234A8A:
	ldr r1, _02234AB4 ; =0x00000F0F
	mov r2, #0x8a
	str r1, [sp]
	ldr r1, _02234AB8 ; =0x00000B34
	mov r3, #1
	ldr r1, [r4, r1]
	bl MOD80_02236C70
	mov r0, #1
	str r0, [r4, #0x18]
	mov r0, #0x1d
	str r0, [r4, #0x2c]
	b _02234AA8
_02234AA4:
	bl ErrorHandling
_02234AA8:
	add r0, r4, #0
	bl MOD80_0222E8BC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02234AB4: .word 0x00000F0F
_02234AB8: .word 0x00000B34
_02234ABC: .word 0x0000100C
	thumb_func_end MOD80_022349CC

	thumb_func_start MOD80_02234AC0
MOD80_02234AC0: ; 0x02234AC0
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	bl FUN_0206AA84
	add r0, r4, #0
	add r0, #0xd4
	bl MOD80_0222DBC4
	mov r0, #3
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #4
	mov r2, #6
	bl MOD80_02235820
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234AC0

	thumb_func_start MOD80_02234AE4
MOD80_02234AE4: ; 0x02234AE4
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234B5A
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0xf
	bhi _02234B5A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234B08: ; jump table
	.short _02234B4E - _02234B08 - 2 ; case 0
	.short _02234B4E - _02234B08 - 2 ; case 1
	.short _02234B56 - _02234B08 - 2 ; case 2
	.short _02234B46 - _02234B08 - 2 ; case 3
	.short _02234B3E - _02234B08 - 2 ; case 4
	.short _02234B3E - _02234B08 - 2 ; case 5
	.short _02234B3E - _02234B08 - 2 ; case 6
	.short _02234B3E - _02234B08 - 2 ; case 7
	.short _02234B3E - _02234B08 - 2 ; case 8
	.short _02234B3E - _02234B08 - 2 ; case 9
	.short _02234B3E - _02234B08 - 2 ; case 10
	.short _02234B46 - _02234B08 - 2 ; case 11
	.short _02234B5A - _02234B08 - 2 ; case 12
	.short _02234B4E - _02234B08 - 2 ; case 13
	.short _02234B36 - _02234B08 - 2 ; case 14
	.short _02234B28 - _02234B08 - 2 ; case 15
_02234B28:
	add r0, r4, #0
	mov r1, #1
	bl MOD80_02235534
	mov r0, #0x1e
	str r0, [r4, #0x2c]
	b _02234B5A
_02234B36:
	str r0, [r4, #0x3c]
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02234B5A
_02234B3E:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _02234B5A
_02234B46:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _02234B5A
_02234B4E:
	str r0, [r4, #0x3c]
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02234B5A
_02234B56:
	bl FUN_020335E0
_02234B5A:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02234AE4

	thumb_func_start MOD80_02234B60
MOD80_02234B60: ; 0x02234B60
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DC14
	mov r0, #5
	str r0, [r4, #0x2c]
	mov r0, #1
	strh r0, [r4, #0x36]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234B60

	thumb_func_start MOD80_02234B74
MOD80_02234B74: ; 0x02234B74
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234BD2
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0xf
	bhi _02234BD2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234B98: ; jump table
	.short _02234BC6 - _02234B98 - 2 ; case 0
	.short _02234BC6 - _02234B98 - 2 ; case 1
	.short _02234BCE - _02234B98 - 2 ; case 2
	.short _02234BBE - _02234B98 - 2 ; case 3
	.short _02234BD2 - _02234B98 - 2 ; case 4
	.short _02234BD2 - _02234B98 - 2 ; case 5
	.short _02234BD2 - _02234B98 - 2 ; case 6
	.short _02234BD2 - _02234B98 - 2 ; case 7
	.short _02234BD2 - _02234B98 - 2 ; case 8
	.short _02234BD2 - _02234B98 - 2 ; case 9
	.short _02234BC6 - _02234B98 - 2 ; case 10
	.short _02234BBE - _02234B98 - 2 ; case 11
	.short _02234BC6 - _02234B98 - 2 ; case 12
	.short _02234BC6 - _02234B98 - 2 ; case 13
	.short _02234BC6 - _02234B98 - 2 ; case 14
	.short _02234BB8 - _02234B98 - 2 ; case 15
_02234BB8:
	mov r0, #0x21
	str r0, [r4, #0x2c]
	b _02234BD2
_02234BBE:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _02234BD2
_02234BC6:
	mov r0, #4
	bl FUN_020336A0
	b _02234BD2
_02234BCE:
	bl FUN_020335E0
_02234BD2:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02234B74

	thumb_func_start MOD80_02234BD8
MOD80_02234BD8: ; 0x02234BD8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	bl MOD80_0222DC68
	mov r0, #8
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #9
	mov r2, #0xb
	bl MOD80_02235820
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234BD8

	thumb_func_start MOD80_02234BF4
MOD80_02234BF4: ; 0x02234BF4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234C82
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0xf
	bhi _02234C82
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234C18: ; jump table
	.short _02234C76 - _02234C18 - 2 ; case 0
	.short _02234C76 - _02234C18 - 2 ; case 1
	.short _02234C7E - _02234C18 - 2 ; case 2
	.short _02234C6E - _02234C18 - 2 ; case 3
	.short _02234C82 - _02234C18 - 2 ; case 4
	.short _02234C82 - _02234C18 - 2 ; case 5
	.short _02234C82 - _02234C18 - 2 ; case 6
	.short _02234C82 - _02234C18 - 2 ; case 7
	.short _02234C82 - _02234C18 - 2 ; case 8
	.short _02234C82 - _02234C18 - 2 ; case 9
	.short _02234C82 - _02234C18 - 2 ; case 10
	.short _02234C68 - _02234C18 - 2 ; case 11
	.short _02234C62 - _02234C18 - 2 ; case 12
	.short _02234C76 - _02234C18 - 2 ; case 13
	.short _02234C82 - _02234C18 - 2 ; case 14
	.short _02234C38 - _02234C18 - 2 ; case 15
_02234C38:
	ldr r0, _02234C88 ; =0x000001F5
	ldrsb r5, [r4, r0]
	cmp r5, #0
	beq _02234C46
	mov r0, #0x18
	str r0, [r4, #0x2c]
	b _02234C82
_02234C46:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0202AC18
	add r1, r4, #0
	add r2, r0, #0
	add r0, r4, #0
	add r1, #0xd4
	add r3, r5, #0
	bl MOD80_022355F0
	mov r0, #0x1e
	str r0, [r4, #0x2c]
	b _02234C82
_02234C62:
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02234C82
_02234C68:
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02234C82
_02234C6E:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _02234C82
_02234C76:
	str r0, [r4, #0x3c]
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02234C82
_02234C7E:
	bl FUN_020335E0
_02234C82:
	mov r0, #3
	pop {r3, r4, r5, pc}
	nop
_02234C88: .word 0x000001F5
	thumb_func_end MOD80_02234BF4

	thumb_func_start MOD80_02234C8C
MOD80_02234C8C: ; 0x02234C8C
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DD4C
	mov r0, #0xa
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234C8C

	thumb_func_start MOD80_02234C9C
MOD80_02234C9C: ; 0x02234C9C
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234CF8
	bl MOD80_0222DBB8
	add r0, #0xf
	cmp r0, #0xf
	bhi _02234CF8
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02234CBE: ; jump table
	.short _02234CEC - _02234CBE - 2 ; case 0
	.short _02234CEC - _02234CBE - 2 ; case 1
	.short _02234CF4 - _02234CBE - 2 ; case 2
	.short _02234CEC - _02234CBE - 2 ; case 3
	.short _02234CF8 - _02234CBE - 2 ; case 4
	.short _02234CF8 - _02234CBE - 2 ; case 5
	.short _02234CF8 - _02234CBE - 2 ; case 6
	.short _02234CF8 - _02234CBE - 2 ; case 7
	.short _02234CF8 - _02234CBE - 2 ; case 8
	.short _02234CF8 - _02234CBE - 2 ; case 9
	.short _02234CE4 - _02234CBE - 2 ; case 10
	.short _02234CE4 - _02234CBE - 2 ; case 11
	.short _02234CE4 - _02234CBE - 2 ; case 12
	.short _02234CEC - _02234CBE - 2 ; case 13
	.short _02234CF8 - _02234CBE - 2 ; case 14
	.short _02234CDE - _02234CBE - 2 ; case 15
_02234CDE:
	mov r0, #0x21
	str r0, [r4, #0x2c]
	b _02234CF8
_02234CE4:
	mov r0, #3
	bl FUN_020336A0
	b _02234CF8
_02234CEC:
	mov r0, #4
	bl FUN_020336A0
	b _02234CF8
_02234CF4:
	bl FUN_020335E0
_02234CF8:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234C9C

	thumb_func_start MOD80_02234CFC
MOD80_02234CFC: ; 0x02234CFC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	bl FUN_0206AA84
	add r0, r4, #0
	add r0, #0xc4
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	mul r0, r1
	add r1, r4, r0
	mov r0, #3
	lsl r0, r0, #8
	ldr r2, _02234D38 ; =0x000009F4
	ldr r0, [r1, r0]
	add r1, r4, #0
	add r1, #0xd4
	add r2, r4, r2
	bl MOD80_0222DE04
	add r0, r4, #0
	mov r1, #0xe
	mov r2, #0x10
	bl MOD80_02235820
	mov r0, #0xd
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02234D38: .word 0x000009F4
	thumb_func_end MOD80_02234CFC

	thumb_func_start MOD80_02234D3C
MOD80_02234D3C: ; 0x02234D3C
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234DEE
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0xf
	bhi _02234DEE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234D60: ; jump table
	.short _02234DE2 - _02234D60 - 2 ; case 0
	.short _02234DE2 - _02234D60 - 2 ; case 1
	.short _02234DEA - _02234D60 - 2 ; case 2
	.short _02234DDA - _02234D60 - 2 ; case 3
	.short _02234DD2 - _02234D60 - 2 ; case 4
	.short _02234DD2 - _02234D60 - 2 ; case 5
	.short _02234DD2 - _02234D60 - 2 ; case 6
	.short _02234DD2 - _02234D60 - 2 ; case 7
	.short _02234DD2 - _02234D60 - 2 ; case 8
	.short _02234DD2 - _02234D60 - 2 ; case 9
	.short _02234DCA - _02234D60 - 2 ; case 10
	.short _02234DEE - _02234D60 - 2 ; case 11
	.short _02234DEE - _02234D60 - 2 ; case 12
	.short _02234DE2 - _02234D60 - 2 ; case 13
	.short _02234DEE - _02234D60 - 2 ; case 14
	.short _02234D80 - _02234D60 - 2 ; case 15
_02234D80:
	mov r0, #0x1e
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #0
	bl MOD80_02235534
	add r2, r4, #0
	add r2, #0xb8
	ldr r1, _02234DF4 ; =0x000009F4
	ldrh r2, [r2]
	add r0, r4, #0
	add r1, r4, r1
	bl MOD80_022356AC
	ldr r0, [r4]
	ldr r1, _02234DF4 ; =0x000009F4
	ldr r0, [r0, #0x18]
	add r1, r4, r1
	bl MOD80_02235784
	ldr r0, [r4]
	mov r1, #0x19
	ldr r0, [r0, #0x28]
	bl FUN_0202A170
	ldr r0, [r4]
	ldr r1, _02234DF4 ; =0x000009F4
	ldr r0, [r0, #0x2c]
	add r1, r4, r1
	bl MOD80_022357A0
	ldr r0, [r4]
	mov r1, #0x18
	ldr r0, [r0, #0x28]
	bl FUN_0202A0E8
	b _02234DEE
_02234DCA:
	str r0, [r4, #0x3c]
	mov r0, #0x11
	str r0, [r4, #0x2c]
	b _02234DEE
_02234DD2:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _02234DEE
_02234DDA:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _02234DEE
_02234DE2:
	str r0, [r4, #0x3c]
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02234DEE
_02234DEA:
	bl FUN_020335E0
_02234DEE:
	mov r0, #3
	pop {r4, pc}
	nop
_02234DF4: .word 0x000009F4
	thumb_func_end MOD80_02234D3C

	thumb_func_start MOD80_02234DF8
MOD80_02234DF8: ; 0x02234DF8
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DE68
	mov r0, #0xf
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234DF8

	thumb_func_start MOD80_02234E08
MOD80_02234E08: ; 0x02234E08
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234E64
	bl MOD80_0222DBB8
	add r0, #0xf
	cmp r0, #0xf
	bhi _02234E64
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02234E2A: ; jump table
	.short _02234E58 - _02234E2A - 2 ; case 0
	.short _02234E58 - _02234E2A - 2 ; case 1
	.short _02234E60 - _02234E2A - 2 ; case 2
	.short _02234E58 - _02234E2A - 2 ; case 3
	.short _02234E64 - _02234E2A - 2 ; case 4
	.short _02234E64 - _02234E2A - 2 ; case 5
	.short _02234E64 - _02234E2A - 2 ; case 6
	.short _02234E64 - _02234E2A - 2 ; case 7
	.short _02234E64 - _02234E2A - 2 ; case 8
	.short _02234E64 - _02234E2A - 2 ; case 9
	.short _02234E50 - _02234E2A - 2 ; case 10
	.short _02234E64 - _02234E2A - 2 ; case 11
	.short _02234E64 - _02234E2A - 2 ; case 12
	.short _02234E58 - _02234E2A - 2 ; case 13
	.short _02234E64 - _02234E2A - 2 ; case 14
	.short _02234E4A - _02234E2A - 2 ; case 15
_02234E4A:
	mov r0, #0x21
	str r0, [r4, #0x2c]
	b _02234E64
_02234E50:
	mov r0, #3
	bl FUN_020336A0
	b _02234E64
_02234E58:
	mov r0, #4
	bl FUN_020336A0
	b _02234E64
_02234E60:
	bl FUN_020335E0
_02234E64:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02234E08

	thumb_func_start MOD80_02234E68
MOD80_02234E68: ; 0x02234E68
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	bl MOD80_0222DCB8
	mov r0, #0x19
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02234E68

	thumb_func_start MOD80_02234E7C
MOD80_02234E7C: ; 0x02234E7C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02234EE2
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0x10
	bhi _02234EE2
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02234EA0: ; jump table
	.short _02234FF4 - _02234EA0 - 2 ; case 0
	.short _02234FF4 - _02234EA0 - 2 ; case 1
	.short _02234FFC - _02234EA0 - 2 ; case 2
	.short _02234FF4 - _02234EA0 - 2 ; case 3
	.short _02235006 - _02234EA0 - 2 ; case 4
	.short _02235006 - _02234EA0 - 2 ; case 5
	.short _02235006 - _02234EA0 - 2 ; case 6
	.short _02235006 - _02234EA0 - 2 ; case 7
	.short _02235006 - _02234EA0 - 2 ; case 8
	.short _02235006 - _02234EA0 - 2 ; case 9
	.short _02235006 - _02234EA0 - 2 ; case 10
	.short _02234FA4 - _02234EA0 - 2 ; case 11
	.short _02234F38 - _02234EA0 - 2 ; case 12
	.short _02234FF4 - _02234EA0 - 2 ; case 13
	.short _02235006 - _02234EA0 - 2 ; case 14
	.short _02234EC2 - _02234EA0 - 2 ; case 15
	.short _02234EC8 - _02234EA0 - 2 ; case 16
_02234EC2:
	mov r0, #0x1a
	str r0, [r4, #0x2c]
	b _02235006
_02234EC8:
	mov r0, #1
	add r1, r4, #0
	strh r0, [r4, #0x36]
	add r0, r4, #0
	add r1, #0xd4
	bl MOD80_022357DC
	cmp r0, #0
	beq _02234F2C
	cmp r0, #1
	beq _02234EE4
	cmp r0, #2
	beq _02234F08
_02234EE2:
	b _02235006
_02234EE4:
	add r0, r4, #0
	bl MOD80_0222E8D8
	ldr r0, _0223500C ; =0x00000F0F
	ldr r1, _02235010 ; =0x00000B34
	str r0, [sp]
	ldr r1, [r4, r1]
	add r0, r4, #0
	mov r2, #0x1d
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x1c
	bl MOD80_0222E6DC
	b _02235006
_02234F08:
	add r0, r4, #0
	bl MOD80_0222E8D8
	ldr r0, _0223500C ; =0x00000F0F
	ldr r1, _02235010 ; =0x00000B34
	str r0, [sp]
	ldr r1, [r4, r1]
	add r0, r4, #0
	mov r2, #0x23
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x1c
	bl MOD80_0222E6DC
	b _02235006
_02234F2C:
	mov r0, #0x12
	str r0, [r4, #0x2c]
	ldr r0, _02235014 ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	b _02235006
_02234F38:
	mov r0, #0
	strh r0, [r4, #0x36]
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0202ABDC
	cmp r0, #0
	beq _02234F9C
	mov r0, #0x3e
	bl AllocMonZeroed
	add r5, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	ldr r0, [r0]
	bl FUN_0202ABEC
	add r0, r5, #0
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl BufferBoxMonNickname
	mov r0, #2
	str r0, [r4, #0x28]
	mov r0, #0x22
	str r0, [r4, #0x2c]
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0202AC18
	add r2, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	mov r3, #0
	bl MOD80_022355F0
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0202ABE4
	add r0, r5, #0
	bl FreeToHeap
	b _02235006
_02234F9C:
	add r0, r4, #0
	bl MOD80_022350C4
	b _02235006
_02234FA4:
	mov r0, #0
	strh r0, [r4, #0x36]
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0202ABDC
	cmp r0, #0
	beq _02235006
	mov r0, #0x3e
	bl AllocMonZeroed
	add r5, r0, #0
	ldr r0, [r4]
	add r1, r5, #0
	ldr r0, [r0]
	bl FUN_0202ABEC
	add r0, r5, #0
	bl FUN_020690E4
	add r2, r0, #0
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #0
	bl BufferBoxMonNickname
	mov r0, #3
	str r0, [r4, #0x28]
	mov r0, #0x22
	str r0, [r4, #0x2c]
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0202ABE4
	add r0, r5, #0
	bl FreeToHeap
	b _02235006
_02234FF4:
	str r0, [r4, #0x3c]
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _02235006
_02234FFC:
	mov r0, #3
	mov r1, #1
	mov r2, #0
	bl FUN_02033F70
_02235006:
	mov r0, #3
	pop {r3, r4, r5, pc}
	nop
_0223500C: .word 0x00000F0F
_02235010: .word 0x00000B34
_02235014: .word 0x0000100C
	thumb_func_end MOD80_02234E7C

	thumb_func_start MOD80_02235018
MOD80_02235018: ; 0x02235018
	push {r4, lr}
	mov r1, #1
	mov r2, #0
	add r4, r0, #0
	bl MOD80_0222E7A8
	mov r0, #0x24
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02235018

	thumb_func_start MOD80_0223502C
MOD80_0223502C: ; 0x0223502C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xd4
	bl MOD80_0222DC68
	mov r0, #0x1b
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_0223502C

	thumb_func_start MOD80_02235040
MOD80_02235040: ; 0x02235040
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _022350BE
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0xf
	bhi _022350B8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02235064: ; jump table
	.short _022350AC - _02235064 - 2 ; case 0
	.short _022350AC - _02235064 - 2 ; case 1
	.short _022350B4 - _02235064 - 2 ; case 2
	.short _022350A4 - _02235064 - 2 ; case 3
	.short _022350B8 - _02235064 - 2 ; case 4
	.short _022350B8 - _02235064 - 2 ; case 5
	.short _022350B8 - _02235064 - 2 ; case 6
	.short _022350B8 - _02235064 - 2 ; case 7
	.short _022350B8 - _02235064 - 2 ; case 8
	.short _022350B8 - _02235064 - 2 ; case 9
	.short _022350B8 - _02235064 - 2 ; case 10
	.short _022350B8 - _02235064 - 2 ; case 11
	.short _0223509E - _02235064 - 2 ; case 12
	.short _022350AC - _02235064 - 2 ; case 13
	.short _022350B8 - _02235064 - 2 ; case 14
	.short _02235084 - _02235064 - 2 ; case 15
_02235084:
	add r0, r4, #0
	bl MOD80_02235830
	cmp r0, #0
	beq _02235098
	mov r0, #0x16
	str r0, [r4, #0x2c]
	mov r0, #0
	strh r0, [r4, #0x36]
	b _022350B8
_02235098:
	mov r0, #1
	strh r0, [r4, #0x36]
	b _022350B8
_0223509E:
	mov r0, #0
	strh r0, [r4, #0x36]
	b _022350B8
_022350A4:
	str r0, [r4, #0x3c]
	mov r0, #0x27
	str r0, [r4, #0x2c]
	b _022350B8
_022350AC:
	str r0, [r4, #0x3c]
	mov r0, #0x26
	str r0, [r4, #0x2c]
	b _022350B8
_022350B4:
	bl FUN_020335E0
_022350B8:
	add r0, r4, #0
	bl MOD80_022350C4
_022350BE:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235040

	thumb_func_start MOD80_022350C4
MOD80_022350C4: ; 0x022350C4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x1c]
	cmp r1, #1
	beq _022350D4
	cmp r1, #2
	beq _022350E2
	pop {r4, pc}
_022350D4:
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #0x24
	str r0, [r4, #0x2c]
	pop {r4, pc}
_022350E2:
	mov r1, #2
	mov r2, #3
	bl MOD80_0222E7A8
	mov r0, #0x24
	str r0, [r4, #0x2c]
	pop {r4, pc}
	thumb_func_end MOD80_022350C4

	thumb_func_start MOD80_022350F0
MOD80_022350F0: ; 0x022350F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0202AC18
	ldr r3, _02235154 ; =0x000001F5
	add r1, r4, #0
	add r2, r0, #0
	ldrsb r3, [r4, r3]
	add r0, r4, #0
	add r1, #0xd4
	bl MOD80_022355F0
	ldr r0, [r4]
	add r1, r4, #0
	ldr r0, [r0, #0x18]
	add r1, #0xd4
	bl MOD80_02235784
	ldr r0, [r4]
	mov r1, #0x19
	ldr r0, [r0, #0x28]
	bl FUN_0202A170
	ldr r0, [r4]
	add r1, r4, #0
	ldr r0, [r0, #0x2c]
	add r1, #0xd4
	bl MOD80_022357A0
	ldr r0, [r4]
	mov r1, #0x18
	ldr r0, [r0, #0x28]
	bl FUN_0202A0E8
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0202ABE4
	mov r0, #0x1e
	str r0, [r4, #0x2c]
	add r0, r4, #0
	mov r1, #0x13
	mov r2, #0xb
	bl MOD80_02235820
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02235154: .word 0x000001F5
	thumb_func_end MOD80_022350F0

	thumb_func_start MOD80_02235158
MOD80_02235158: ; 0x02235158
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DD08
	mov r0, #0x14
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02235158

	thumb_func_start MOD80_02235168
MOD80_02235168: ; 0x02235168
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _022351C8
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0xf
	bhi _022351C8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223518C: ; jump table
	.short _022351BC - _0223518C - 2 ; case 0
	.short _022351BC - _0223518C - 2 ; case 1
	.short _022351C4 - _0223518C - 2 ; case 2
	.short _022351BA - _0223518C - 2 ; case 3
	.short _022351C8 - _0223518C - 2 ; case 4
	.short _022351C8 - _0223518C - 2 ; case 5
	.short _022351C8 - _0223518C - 2 ; case 6
	.short _022351C8 - _0223518C - 2 ; case 7
	.short _022351C8 - _0223518C - 2 ; case 8
	.short _022351C8 - _0223518C - 2 ; case 9
	.short _022351C8 - _0223518C - 2 ; case 10
	.short _022351BA - _0223518C - 2 ; case 11
	.short _022351B2 - _0223518C - 2 ; case 12
	.short _022351BC - _0223518C - 2 ; case 13
	.short _022351C8 - _0223518C - 2 ; case 14
	.short _022351AC - _0223518C - 2 ; case 15
_022351AC:
	mov r0, #0x21
	str r0, [r4, #0x2c]
	b _022351C8
_022351B2:
	mov r0, #3
	bl FUN_020336A0
	b _022351C8
_022351BA:
	str r0, [r4, #0x3c]
_022351BC:
	mov r0, #4
	bl FUN_020336A0
	b _022351C8
_022351C4:
	bl FUN_020335E0
_022351C8:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02235168

	thumb_func_start MOD80_022351CC
MOD80_022351CC: ; 0x022351CC
	mov r0, #3
	bx lr
	thumb_func_end MOD80_022351CC

	thumb_func_start MOD80_022351D0
MOD80_022351D0: ; 0x022351D0
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	strh r1, [r4, #0x36]
	mov r1, #9
	mov r2, #7
	bl MOD80_0222E7A8
	mov r0, #0x24
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_022351D0

	thumb_func_start MOD80_022351E8
MOD80_022351E8: ; 0x022351E8
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	strh r1, [r4, #0x36]
	mov r1, #9
	mov r2, #8
	bl MOD80_0222E7A8
	mov r0, #0x24
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_022351E8

	thumb_func_start MOD80_02235200
MOD80_02235200: ; 0x02235200
	push {r4, lr}
	mov r1, #9
	add r2, r1, #0
	add r4, r0, #0
	bl MOD80_0222E7A8
	mov r0, #0x24
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02235200

	thumb_func_start MOD80_02235214
MOD80_02235214: ; 0x02235214
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	strh r1, [r4, #0x36]
	mov r1, #9
	mov r2, #0xa
	bl MOD80_0222E7A8
	mov r0, #0x1e
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02235214

	thumb_func_start MOD80_0223522C
MOD80_0223522C: ; 0x0223522C
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DD4C
	mov r0, #0x17
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_0223522C

	thumb_func_start MOD80_0223523C
MOD80_0223523C: ; 0x0223523C
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _022352A6
	bl MOD80_0222DBB8
	add r0, #0xf
	cmp r0, #0xf
	bhi _022352A6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223525E: ; jump table
	.short _0223529A - _0223525E - 2 ; case 0
	.short _0223529A - _0223525E - 2 ; case 1
	.short _022352A2 - _0223525E - 2 ; case 2
	.short _0223529A - _0223525E - 2 ; case 3
	.short _022352A6 - _0223525E - 2 ; case 4
	.short _022352A6 - _0223525E - 2 ; case 5
	.short _022352A6 - _0223525E - 2 ; case 6
	.short _022352A6 - _0223525E - 2 ; case 7
	.short _022352A6 - _0223525E - 2 ; case 8
	.short _022352A6 - _0223525E - 2 ; case 9
	.short _02235292 - _0223525E - 2 ; case 10
	.short _0223528C - _0223525E - 2 ; case 11
	.short _02235286 - _0223525E - 2 ; case 12
	.short _0223529A - _0223525E - 2 ; case 13
	.short _022352A6 - _0223525E - 2 ; case 14
	.short _0223527E - _0223525E - 2 ; case 15
_0223527E:
	add r0, r4, #0
	bl MOD80_022350C4
	b _022352A6
_02235286:
	add r0, r4, #0
	bl MOD80_022350C4
_0223528C:
	add r0, r4, #0
	bl MOD80_022350C4
_02235292:
	mov r0, #3
	bl FUN_020336A0
	b _022352A6
_0223529A:
	mov r0, #4
	bl FUN_020336A0
	b _022352A6
_022352A2:
	bl FUN_020335E0
_022352A6:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_0223523C

	thumb_func_start MOD80_022352AC
MOD80_022352AC: ; 0x022352AC
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _022352E8 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _022352EC ; =0x00000B34
	mov r2, #0x89
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x24
	bl MOD80_0222E6DC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	add r0, r4, #0
	bl MOD80_0222E8D8
	add r0, r4, #0
	bl MOD80_02235C40
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_022352E8: .word 0x00000F0F
_022352EC: .word 0x00000B34
	thumb_func_end MOD80_022352AC

	thumb_func_start MOD80_022352F0
MOD80_022352F0: ; 0x022352F0
	push {r3, lr}
	ldr r1, [r0, #0x3c]
	mov r2, #0x90
	add r1, #0xf
	cmp r1, #0xe
	bhi _02235330
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02235308: ; jump table
	.short _02235330 - _02235308 - 2 ; case 0
	.short _0223532E - _02235308 - 2 ; case 1
	.short _02235330 - _02235308 - 2 ; case 2
	.short _02235330 - _02235308 - 2 ; case 3
	.short _02235326 - _02235308 - 2 ; case 4
	.short _02235326 - _02235308 - 2 ; case 5
	.short _02235326 - _02235308 - 2 ; case 6
	.short _02235326 - _02235308 - 2 ; case 7
	.short _02235326 - _02235308 - 2 ; case 8
	.short _02235326 - _02235308 - 2 ; case 9
	.short _02235330 - _02235308 - 2 ; case 10
	.short _02235330 - _02235308 - 2 ; case 11
	.short _02235330 - _02235308 - 2 ; case 12
	.short _0223532E - _02235308 - 2 ; case 13
	.short _0223532A - _02235308 - 2 ; case 14
_02235326:
	mov r2, #0x1a
	b _02235330
_0223532A:
	mov r2, #0x8d
	b _02235330
_0223532E:
	mov r2, #0x92
_02235330:
	ldr r1, _02235340 ; =0x00000F0F
	mov r3, #1
	str r1, [sp]
	ldr r1, _02235344 ; =0x00000B34
	ldr r1, [r0, r1]
	bl MOD80_02236C70
	pop {r3, pc}
	.align 2, 0
_02235340: .word 0x00000F0F
_02235344: .word 0x00000B34
	thumb_func_end MOD80_022352F0

	thumb_func_start MOD80_02235348
MOD80_02235348: ; 0x02235348
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_022352F0
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x24
	bl MOD80_0222E6DC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	add r0, r4, #0
	bl MOD80_0222E8D8
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235348

	thumb_func_start MOD80_02235370
MOD80_02235370: ; 0x02235370
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_022352F0
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x24
	bl MOD80_0222E6DC
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	add r0, r4, #0
	bl MOD80_0222E8D8
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235370

	thumb_func_start MOD80_02235398
MOD80_02235398: ; 0x02235398
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0x25
	mov r2, #0x1e
	bl MOD80_0222E6DC
	add r0, r4, #0
	mov r1, #0x21
	mov r2, #0x24
	bl MOD80_02235820
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235398

	thumb_func_start MOD80_022353B4
MOD80_022353B4: ; 0x022353B4
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl SaveSetDirtyBit
	ldr r0, [r4]
	mov r1, #2
	ldr r0, [r0, #0x20]
	bl FUN_02022840
	mov r0, #0x1f
	str r0, [r4, #0x2c]
	bl LCRandom
	ldr r1, _022353EC ; =0x00000445
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	cmp r5, #0x3c
	blo _022353E0
	bl ErrorHandling
_022353E0:
	ldr r0, _022353F0 ; =0x00000FDC
	add r1, r5, #2
	str r1, [r4, r0]
	mov r0, #3
	pop {r3, r4, r5, pc}
	nop
_022353EC: .word 0x00000445
_022353F0: .word 0x00000FDC
	thumb_func_end MOD80_022353B4

	thumb_func_start MOD80_022353F4
MOD80_022353F4: ; 0x022353F4
	ldr r1, _0223540C ; =0x00000FDC
	ldr r2, [r0, r1]
	sub r2, r2, #1
	str r2, [r0, r1]
	ldr r1, [r0, r1]
	cmp r1, #0
	bne _02235406
	mov r1, #0x20
	str r1, [r0, #0x2c]
_02235406:
	mov r0, #3
	bx lr
	nop
_0223540C: .word 0x00000FDC
	thumb_func_end MOD80_022353F4

	thumb_func_start MOD80_02235410
MOD80_02235410: ; 0x02235410
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #0x20]
	bl FUN_02022854
	cmp r0, #1
	bne _02235426
	ldr r0, _0223542C ; =0x00000FE4
	ldrh r0, [r4, r0]
	str r0, [r4, #0x2c]
_02235426:
	mov r0, #3
	pop {r4, pc}
	nop
_0223542C: .word 0x00000FE4
	thumb_func_end MOD80_02235410

	thumb_func_start MOD80_02235430
MOD80_02235430: ; 0x02235430
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #0x20]
	bl FUN_02022854
	cmp r0, #2
	bne _0223544C
	ldr r0, _02235450 ; =0x00000FE6
	ldrh r0, [r4, r0]
	str r0, [r4, #0x2c]
	add r0, r4, #0
	bl MOD80_0222E8D8
_0223544C:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02235450: .word 0x00000FE6
	thumb_func_end MOD80_02235430

	thumb_func_start MOD80_02235454
MOD80_02235454: ; 0x02235454
	push {r4, lr}
	add r4, r0, #0
	bl SaveSetDirtyBit
	ldr r0, [r4]
	mov r1, #2
	ldr r0, [r0, #0x20]
	bl FUN_02022840
	mov r0, #0x23
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235454

	thumb_func_start MOD80_02235470
MOD80_02235470: ; 0x02235470
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #0x20]
	bl FUN_02022854
	cmp r0, #2
	bne _022354AE
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	add r0, r4, #0
	bl MOD80_0222E8D8
	ldr r0, _022354B4 ; =0x00000F0F
	ldr r1, _022354B8 ; =0x00000B34
	str r0, [sp]
	ldr r1, [r4, r1]
	ldr r2, [r4, #0x28]
	add r0, r4, #0
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x25
	mov r2, #0x1c
	bl MOD80_0222E6DC
_022354AE:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_022354B4: .word 0x00000F0F
_022354B8: .word 0x00000B34
	thumb_func_end MOD80_02235470

	thumb_func_start MOD80_022354BC
MOD80_022354BC: ; 0x022354BC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_0222E8D8
	bl FUN_02033ED0
	ldr r0, _02235510 ; =0x0000100C
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _022354EC
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	b _02235504
_022354EC:
	mov r0, #6
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
_02235504:
	mov r0, #0
	str r0, [r4, #0x2c]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02235510: .word 0x0000100C
	thumb_func_end MOD80_022354BC

	thumb_func_start MOD80_02235514
MOD80_02235514: ; 0x02235514
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223552E
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_0223552E:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235514

	thumb_func_start MOD80_02235534
MOD80_02235534: ; 0x02235534
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xb8
	ldrh r0, [r0]
	add r6, r1, #0
	cmp r0, #0x12
	beq _02235590
	mov r0, #0x3e
	bl AllocMonZeroed
	add r1, r5, #0
	add r2, r5, #0
	add r4, r0, #0
	ldr r0, [r5]
	add r1, #0xb8
	add r2, #0xba
	ldrh r1, [r1]
	ldrh r2, [r2]
	ldr r0, [r0, #0xc]
	bl PCStorage_GetMonByIndexPair
	add r1, r4, #0
	bl FUN_02069A64
	add r2, r5, #0
	ldr r0, [r5]
	add r2, #0xb8
	ldrh r2, [r2]
	ldr r0, [r0]
	add r1, r4, #0
	bl FUN_0202ABF8
	add r1, r5, #0
	add r2, r5, #0
	ldr r0, [r5]
	add r1, #0xb8
	add r2, #0xba
	ldrh r1, [r1]
	ldrh r2, [r2]
	ldr r0, [r0, #0xc]
	bl PCStorage_DeleteBoxMonByIndexPair
	add r0, r4, #0
	bl FreeToHeap
	b _022355DC
_02235590:
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0xba
	ldrh r1, [r1]
	ldr r0, [r0, #8]
	bl GetPartyMonByIndex
	add r4, r0, #0
	bl FUN_0206AA84
	add r2, r5, #0
	ldr r0, [r5]
	add r2, #0xb8
	ldrh r2, [r2]
	ldr r0, [r0]
	add r1, r4, #0
	bl FUN_0202ABF8
	add r1, r5, #0
	ldr r0, [r5]
	add r1, #0xba
	ldrh r1, [r1]
	ldr r0, [r0, #8]
	bl RemoveMonFromParty
	ldr r0, [r5]
	ldr r1, _022355EC ; =0x000001B9
	ldr r0, [r0, #8]
	bl PartyHasMon
	cmp r0, #0
	bne _022355DC
	ldr r0, [r5]
	ldr r0, [r0, #0x20]
	bl FUN_02029EF8
	bl FUN_02029F08
_022355DC:
	cmp r6, #0
	beq _022355EA
	ldr r0, [r5]
	mov r1, #1
	ldr r0, [r0]
	bl FUN_0202ABE4
_022355EA:
	pop {r4, r5, r6, pc}
	.align 2, 0
_022355EC: .word 0x000001B9
	thumb_func_end MOD80_02235534

	thumb_func_start MOD80_022355F0
MOD80_022355F0: ; 0x022355F0
	push {r0, r1, r2, r3}
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #6
	mov r2, #0
	add r6, r3, #0
	bl GetMonData
	ldr r0, [r5]
	add r1, r4, #0
	ldr r0, [r0, #0x20]
	bl FUN_0202C144
	mov r0, #0x12
	str r0, [sp, #0x20]
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl GetPartyCount
	cmp r0, #6
	bne _02235624
	mov r0, #0
	str r0, [sp, #0x20]
_02235624:
	cmp r6, #0
	beq _02235640
	mov r1, #0x46
	add r0, sp, #0
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #9
	add r2, sp, #0
	bl SetMonData
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD80_02235754
_02235640:
	ldr r0, [sp, #0x20]
	cmp r0, #0x12
	bne _02235664
	ldr r0, [r5]
	add r1, r4, #0
	ldr r0, [r0, #8]
	bl AddMonToParty
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl GetPartyCount
	add r1, r5, #0
	mov r2, #0x12
	add r1, #0xcc
	str r2, [r1]
	sub r1, r0, #1
	b _02235690
_02235664:
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r5]
	add r1, sp, #0x20
	ldr r0, [r0, #0xc]
	add r2, sp, #4
	bl PCStorage_FindFirstEmptySlot
	add r0, r4, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r5]
	ldr r1, [sp, #0x20]
	ldr r0, [r0, #0xc]
	bl PCStorage_PlaceMonInBoxFirstEmptySlot
	add r0, r5, #0
	ldr r1, [sp, #0x20]
	add r0, #0xcc
	str r1, [r0]
	ldr r1, [sp, #4]
_02235690:
	add r0, r5, #0
	add r0, #0xd0
	str r1, [r0]
	ldr r0, [r5]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0202ABE4
	add sp, #8
	pop {r4, r5, r6}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0
	thumb_func_end MOD80_022355F0

	thumb_func_start MOD80_022356AC
MOD80_022356AC: ; 0x022356AC
	push {r0, r1, r2, r3}
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	ldr r0, [r0, #0x20]
	bl FUN_0202C144
	mov r0, #0x12
	str r0, [sp, #0x20]
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl GetPartyCount
	cmp r0, #6
	bne _022356D2
	mov r0, #0
	str r0, [sp, #0x20]
_022356D2:
	mov r1, #0x46
	add r0, sp, #0
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #9
	add r2, sp, #0
	bl SetMonData
	ldr r0, [sp, #0x20]
	cmp r0, #0x12
	bne _02235706
	ldr r0, [r5]
	add r1, r4, #0
	ldr r0, [r0, #8]
	bl AddMonToParty
	ldr r0, [r5]
	ldr r0, [r0, #8]
	bl GetPartyCount
	add r1, r5, #0
	mov r2, #0x12
	add r1, #0xcc
	str r2, [r1]
	sub r1, r0, #1
	b _02235732
_02235706:
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [r5]
	add r1, sp, #0x20
	ldr r0, [r0, #0xc]
	add r2, sp, #4
	bl PCStorage_FindFirstEmptySlot
	add r0, r4, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r5]
	ldr r1, [sp, #0x20]
	ldr r0, [r0, #0xc]
	bl PCStorage_PlaceMonInBoxFirstEmptySlot
	add r0, r5, #0
	ldr r1, [sp, #0x20]
	add r0, #0xcc
	str r1, [r0]
	ldr r1, [sp, #4]
_02235732:
	add r0, r5, #0
	add r0, #0xd0
	str r1, [r0]
	ldr r0, [r5]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0202ABE4
	ldr r0, [r5]
	ldr r0, [r0]
	bl MOD80_02235754
	add sp, #8
	pop {r3, r4, r5}
	pop {r3}
	add sp, #0x10
	bx r3
	thumb_func_end MOD80_022356AC

	thumb_func_start MOD80_02235754
MOD80_02235754: ; 0x02235754
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r0, #0
	add r0, sp, #0xc
	add r1, sp, #0
	bl MOD04_021DE1F8
	ldr r1, [sp, #0x14]
	ldr r3, [sp, #0xc]
	add r0, r4, #0
	lsl r4, r3, #0x18
	ldr r3, [sp, #0x10]
	lsl r1, r1, #0x18
	lsl r3, r3, #0x18
	lsr r3, r3, #8
	ldr r2, [sp, #0x18]
	lsr r1, r1, #0x10
	orr r3, r4
	orr r1, r3
	orr r1, r2
	bl FUN_0202AC10
	add sp, #0x1c
	pop {r3, r4, pc}
	thumb_func_end MOD80_02235754

	thumb_func_start MOD80_02235784
MOD80_02235784: ; 0x02235784
	push {r4, lr}
	ldr r3, _0223579C ; =0x0000011E
	add r4, r1, #0
	add r2, r3, #1
	ldrb r1, [r4, r3]
	add r3, r3, #5
	ldrb r2, [r4, r2]
	ldrb r3, [r4, r3]
	bl FUN_020337C8
	pop {r4, pc}
	nop
_0223579C: .word 0x0000011E
	thumb_func_end MOD80_02235784

	thumb_func_start MOD80_022357A0
MOD80_022357A0: ; 0x022357A0
	push {r4, r5, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0x74
	add r2, sp, #4
	bl GetMonData
	add r0, r4, #0
	bl GetMonGender
	add r3, r0, #0
	mov r0, #0x3e
	str r0, [sp]
	add r0, #0xce
	add r0, r4, r0
	add r4, #0xf6
	ldrb r1, [r4]
	add r2, sp, #4
	bl FUN_0202952C
	add r1, r0, #0
	add r0, r5, #0
	mov r2, #4
	bl FUN_02028AD4
	add sp, #0x1c
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_022357A0

	thumb_func_start MOD80_022357DC
MOD80_022357DC: ; 0x022357DC
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl MOD80_022331F8
	cmp r0, #0
	beq _022357FA
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl GetPartyCount
	cmp r0, #6
	bne _022357FA
	mov r0, #2
	pop {r4, pc}
_022357FA:
	ldr r0, _0223581C ; =0x00001008
	ldrh r1, [r4, r0]
	mov r0, #0x87
	lsl r0, r0, #2
	cmp r1, r0
	bne _02235816
	ldr r0, [r4]
	ldr r0, [r0, #8]
	bl GetPartyCount
	cmp r0, #6
	bne _02235816
	mov r0, #1
	pop {r4, pc}
_02235816:
	mov r0, #0
	pop {r4, pc}
	nop
_0223581C: .word 0x00001008
	thumb_func_end MOD80_022357DC

	thumb_func_start MOD80_02235820
MOD80_02235820: ; 0x02235820
	ldr r3, _0223582C ; =0x00000FE4
	strh r1, [r0, r3]
	add r1, r3, #2
	strh r2, [r0, r1]
	bx lr
	nop
_0223582C: .word 0x00000FE4
	thumb_func_end MOD80_02235820

	thumb_func_start MOD80_02235830
MOD80_02235830: ; 0x02235830
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0202ABDC
	cmp r0, #0
	bne _0223584A
	ldrh r0, [r4, #0x36]
	cmp r0, #0
	beq _0223584A
	mov r0, #1
	pop {r4, pc}
_0223584A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02235830

	thumb_func_start MOD80_02235850
MOD80_02235850: ; 0x02235850
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r0, #0
	add r4, r1, #0
	bl MOD80_02235C88
	ldr r2, _022358F0 ; =0x00000D14
	add r0, sp, #0
	add r1, r5, #0
	add r2, r5, r2
	mov r3, #2
	bl MOD80_0222E5E8
	mov r0, #2
	str r0, [sp, #0x28]
	lsl r0, r0, #0x12
	str r0, [sp, #8]
	ldr r0, _022358F4 ; =0x00182000
	str r0, [sp, #0xc]
	add r0, sp, #0
	bl FUN_0201FE94
	mov r1, #0xe7
	lsl r1, r1, #4
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0xe7
	lsl r0, r0, #4
	mov r1, #7
	mul r1, r4
	ldr r0, [r5, r0]
	add r1, r1, #3
	bl FUN_02020130
	mov r0, #0xe7
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r4, _022358F8 ; =0x022375A6
	mov r7, #0
	mov r6, #0xe
_022358AC:
	add r0, sp, #0
	bl FUN_0201FE94
	ldr r1, _022358FC ; =0x00000E74
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _022358FC ; =0x00000E74
	add r1, r6, #0
	ldr r0, [r5, r0]
	bl FUN_02020130
	ldr r0, _022358FC ; =0x00000E74
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
	ldr r0, _022358FC ; =0x00000E74
	ldrh r1, [r4]
	ldrh r2, [r4, #2]
	ldr r0, [r5, r0]
	bl MOD80_02235AFC
	add r7, r7, #1
	add r5, r5, #4
	add r6, r6, #4
	add r4, r4, #4
	cmp r7, #7
	blt _022358AC
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022358F0: .word 0x00000D14
_022358F4: .word 0x00182000
_022358F8: .word MOD80_022375A6
_022358FC: .word 0x00000E74
	thumb_func_end MOD80_02235850

	thumb_func_start MOD80_02235900
MOD80_02235900: ; 0x02235900
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD80_02235850
	ldr r0, _0223593C ; =MOD80_02235964
	mov r1, #0x10
	mov r2, #5
	mov r3, #0x3e
	bl FUN_020061E8
	ldr r1, _02235940 ; =0x00000FE8
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	bl FUN_0201B6C8
	mov r1, #0
	add r2, r1, #0
	str r1, [r0]
	sub r2, #0x28
	str r2, [r0, #4]
	str r4, [r0, #8]
	str r5, [r0, #0xc]
	bl MOD80_02235948
	ldr r0, _02235944 ; =0x0000062F
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	nop
_0223593C: .word MOD80_02235964
_02235940: .word 0x00000FE8
_02235944: .word 0x0000062F
	thumb_func_end MOD80_02235900

	thumb_func_start MOD80_02235948
MOD80_02235948: ; 0x02235948
	add r3, r0, #0
	ldr r2, [r3, #0xc]
	mov r0, #0xe7
	lsl r0, r0, #4
	ldr r0, [r2, r0]
	ldr r3, [r3, #8]
	mov r2, #7
	mul r2, r3
	ldr r3, _02235960 ; =FUN_02020130
	add r1, r1, r2
	bx r3
	nop
_02235960: .word FUN_02020130
	thumb_func_end MOD80_02235948

	thumb_func_start MOD80_02235964
MOD80_02235964: ; 0x02235964
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #3
	bhi _02235A06
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223597E: ; jump table
	.short _02235986 - _0223597E - 2 ; case 0
	.short _022359AE - _0223597E - 2 ; case 1
	.short _022359CA - _0223597E - 2 ; case 2
	.short _022359F2 - _0223597E - 2 ; case 3
_02235986:
	ldr r0, [r4, #4]
	cmp r0, #0xa0
	ble _0223599A
	mov r0, #0xa0
	str r0, [r4, #4]
	mov r1, #1
	add r0, r4, #0
	str r1, [r4]
	bl MOD80_02235948
_0223599A:
	ldr r0, [r4, #4]
	mov r1, #0x80
	add r2, r0, #5
	mov r0, #0xe7
	str r2, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD80_02235AFC
	pop {r4, r5, r6, pc}
_022359AE:
	mov r0, #0xe7
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02020388
	cmp r0, #0
	bne _02235A06
	add r0, r4, #0
	mov r1, #2
	bl MOD80_02235948
	mov r0, #2
	str r0, [r4]
	pop {r4, r5, r6, pc}
_022359CA:
	ldr r0, [r4, #4]
	cmp r0, #0x82
	bge _022359DE
	mov r0, #0x82
	str r0, [r4, #4]
	mov r1, #3
	add r0, r4, #0
	str r1, [r4]
	bl MOD80_02235948
_022359DE:
	ldr r0, [r4, #4]
	mov r1, #0x80
	sub r2, r0, #2
	mov r0, #0xe7
	str r2, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD80_02235AFC
	pop {r4, r5, r6, pc}
_022359F2:
	ldr r0, _02235A08 ; =0x0000060D
	bl FUN_020054C8
	ldr r1, [r4, #0xc]
	ldr r0, _02235A0C ; =0x00000FEC
	mov r2, #1
	strh r2, [r1, r0]
	add r0, r6, #0
	bl FUN_0200621C
_02235A06:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02235A08: .word 0x0000060D
_02235A0C: .word 0x00000FEC
	thumb_func_end MOD80_02235964

	thumb_func_start MOD80_02235A10
MOD80_02235A10: ; 0x02235A10
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r0, _02235A48 ; =MOD80_02235A54
	mov r1, #0x10
	mov r2, #5
	mov r3, #0x3e
	bl FUN_020061E8
	ldr r1, _02235A4C ; =0x00000FE8
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	bl FUN_0201B6C8
	mov r1, #0
	str r1, [r0]
	mov r1, #0x82
	str r1, [r0, #4]
	str r4, [r0, #8]
	mov r1, #5
	str r5, [r0, #0xc]
	bl MOD80_02235948
	ldr r0, _02235A50 ; =0x0000060E
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	nop
_02235A48: .word MOD80_02235A54
_02235A4C: .word 0x00000FE8
_02235A50: .word 0x0000060E
	thumb_func_end MOD80_02235A10

	thumb_func_start MOD80_02235A54
MOD80_02235A54: ; 0x02235A54
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4]
	ldr r5, [r4, #0xc]
	cmp r1, #3
	bhi _02235AF4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02235A6C: ; jump table
	.short _02235A74 - _02235A6C - 2 ; case 0
	.short _02235A9E - _02235A6C - 2 ; case 1
	.short _02235AC2 - _02235A6C - 2 ; case 2
	.short _02235AEA - _02235A6C - 2 ; case 3
_02235A74:
	ldr r0, [r4, #4]
	cmp r0, #0xa0
	ble _02235A8A
	mov r0, #0xa0
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4]
	add r0, r4, #0
	mov r1, #6
	bl MOD80_02235948
_02235A8A:
	ldr r0, [r4, #4]
	mov r1, #0x80
	add r2, r0, #2
	mov r0, #0xe7
	str r2, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD80_02235AFC
	pop {r3, r4, r5, pc}
_02235A9E:
	mov r0, #0xe7
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02020388
	cmp r0, #0
	bne _02235AF4
	add r0, r4, #0
	mov r1, #0
	bl MOD80_02235948
	mov r0, #2
	str r0, [r4]
	mov r0, #0x63
	lsl r0, r0, #4
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_02235AC2:
	mov r0, #0x13
	ldr r1, [r4, #4]
	mvn r0, r0
	cmp r1, r0
	bge _02235AD6
	mov r1, #3
	add r0, r4, #0
	str r1, [r4]
	bl MOD80_02235948
_02235AD6:
	ldr r0, [r4, #4]
	mov r1, #0x80
	sub r2, r0, #5
	mov r0, #0xe7
	str r2, [r4, #4]
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl MOD80_02235AFC
	pop {r3, r4, r5, pc}
_02235AEA:
	ldr r1, _02235AF8 ; =0x00000FEC
	mov r2, #1
	strh r2, [r5, r1]
	bl FUN_0200621C
_02235AF4:
	pop {r3, r4, r5, pc}
	nop
_02235AF8: .word 0x00000FEC
	thumb_func_end MOD80_02235A54

	thumb_func_start MOD80_02235AFC
MOD80_02235AFC: ; 0x02235AFC
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	add r5, r2, #0
	cmp r1, #0
	ble _02235B1A
	lsl r0, r1, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _02235B28
_02235B1A:
	lsl r0, r1, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_02235B28:
	bl _ffix
	sub r5, #8
	str r0, [sp]
	cmp r5, #0
	ble _02235B46
	lsl r0, r5, #0xc
	bl _fflt
	add r1, r0, #0
	mov r0, #0x3f
	lsl r0, r0, #0x18
	bl _fadd
	b _02235B54
_02235B46:
	lsl r0, r5, #0xc
	bl _fflt
	mov r1, #0x3f
	lsl r1, r1, #0x18
	bl _fsub
_02235B54:
	bl _ffix
	mov r1, #1
	lsl r1, r1, #0x14
	add r0, r0, r1
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r4, #0
	add r1, sp, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r4, r5, pc}
	thumb_func_end MOD80_02235AFC

	thumb_func_start MOD80_02235B70
MOD80_02235B70: ; 0x02235B70
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02235B8C ; =0x022375C2
	bl FUN_02020988
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02235B86
	cmp r0, r4
	blt _02235B8A
_02235B86:
	mov r0, #0
	mvn r0, r0
_02235B8A:
	pop {r4, pc}
	.align 2, 0
_02235B8C: .word MOD80_022375C2
	thumb_func_end MOD80_02235B70

	thumb_func_start MOD80_02235B90
MOD80_02235B90: ; 0x02235B90
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	add r0, r1, #0
	beq _02235BAA
	add r0, r2, #0
	cmp r0, #1
	bne _02235BAA
	ldr r0, _02235C24 ; =0x0000064F
	bl FUN_020054C8
_02235BAA:
	ldr r4, [sp, #4]
	mov r0, #0xe
	mov r6, #0
	str r0, [sp, #0x10]
	add r5, r4, #0
	mov r7, #0x11
_02235BB6:
	ldr r0, [sp, #8]
	cmp r6, r0
	bge _02235C00
	ldr r0, _02235C28 ; =0x000002EE
	ldr r1, [sp, #4]
	ldrb r0, [r4, r0]
	mov r3, #0xc6
	add r2, r1, #0
	str r0, [sp]
	ldr r0, _02235C2C ; =0x00000FF4
	lsl r3, r3, #2
	ldr r0, [r1, r0]
	ldr r1, _02235C30 ; =0x00000FFC
	ldrb r3, [r4, r3]
	ldr r1, [r2, r1]
	add r2, r6, #0
	bl MOD80_02235CD0
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ldr r0, _02235C34 ; =0x00000E74
	beq _02235BEC
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x10]
	bl FUN_02020130
	b _02235BF4
_02235BEC:
	ldr r0, [r5, r0]
	add r1, r7, #0
	bl FUN_02020130
_02235BF4:
	ldr r0, _02235C34 ; =0x00000E74
	mov r1, #1
	ldr r0, [r5, r0]
	bl FUN_020200A0
	b _02235C0A
_02235C00:
	ldr r0, _02235C34 ; =0x00000E74
	mov r1, #0
	ldr r0, [r5, r0]
	bl FUN_020200A0
_02235C0A:
	mov r0, #0x49
	lsl r0, r0, #2
	add r4, r4, r0
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r0, r0, #4
	str r0, [sp, #0x10]
	add r5, r5, #4
	add r7, r7, #4
	cmp r6, #7
	blt _02235BB6
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02235C24: .word 0x0000064F
_02235C28: .word 0x000002EE
_02235C2C: .word 0x00000FF4
_02235C30: .word 0x00000FFC
_02235C34: .word 0x00000E74
	thumb_func_end MOD80_02235B90

	thumb_func_start MOD80_02235C38
MOD80_02235C38: ; 0x02235C38
	lsl r0, r0, #2
	add r0, #0xe
	bx lr
	.align 2, 0
	thumb_func_end MOD80_02235C38

	thumb_func_start MOD80_02235C40
MOD80_02235C40: ; 0x02235C40
	push {r3, r4, r5, r6, r7, lr}
	ldr r7, _02235C84 ; =0x00000E74
	add r5, r0, #0
	mov r4, #0
_02235C48:
	ldr r0, [r5, r7]
	bl FUN_02020128
	cmp r0, #0
	beq _02235C7A
	ldr r0, _02235C84 ; =0x00000E74
	ldr r0, [r5, r0]
	bl FUN_020201DC
	add r6, r0, #0
	add r0, r4, #0
	bl MOD80_02235C38
	add r0, r0, #1
	cmp r6, r0
	beq _02235C7A
	add r0, r4, #0
	bl MOD80_02235C38
	add r1, r0, #0
	ldr r0, _02235C84 ; =0x00000E74
	add r1, r1, #1
	ldr r0, [r5, r0]
	bl FUN_02020130
_02235C7A:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	blt _02235C48
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235C84: .word 0x00000E74
	thumb_func_end MOD80_02235C40

	thumb_func_start MOD80_02235C88
MOD80_02235C88: ; 0x02235C88
	push {r3, r4, lr}
	sub sp, #4
	ldr r2, _02235CC8 ; =0x00000FFC
	add r4, r0, #0
	mov r0, #0x56
	mov r1, #7
	add r2, r4, r2
	mov r3, #0x3e
	bl FUN_02006C08
	ldr r3, _02235CCC ; =0x00000FF8
	mov r1, #9
	str r0, [r4, r3]
	mov r0, #0x3e
	sub r3, r3, #4
	str r0, [sp]
	mov r0, #0x56
	mov r2, #1
	add r3, r4, r3
	bl FUN_02006BB0
	mov r1, #0xff
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #4
	mov r1, #2
	ldr r0, [r4, r0]
	lsl r1, r1, #0xe
	bl DC_FlushRange
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02235CC8: .word 0x00000FFC
_02235CCC: .word 0x00000FF8
	thumb_func_end MOD80_02235C88

	thumb_func_start MOD80_02235CD0
MOD80_02235CD0: ; 0x02235CD0
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r6, r1, #0
	ldr r0, [sp, #0x18]
	add r1, r3, #0
	add r5, r2, #0
	bl FUN_020536C8
	add r4, r0, #0
	mov r0, #6
	lsl r0, r0, #8
	ldr r1, [r7, #0x14]
	mul r0, r4
	add r0, r1, r0
	ldr r1, _02235D0C ; =0x02237598
	lsl r2, r5, #1
	ldrh r1, [r1, r2]
	mov r2, #2
	ldr r6, [r6, #0xc]
	lsl r2, r2, #8
	bl GXS_LoadOBJ
	lsl r0, r4, #5
	add r1, r5, #2
	add r0, r6, r0
	lsl r1, r1, #5
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02235D0C: .word MOD80_02237598
	thumb_func_end MOD80_02235CD0

	thumb_func_start MOD80_02235D10
MOD80_02235D10: ; 0x02235D10
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02235D30 ; =0x00000FEC
	ldrh r1, [r4, r0]
	cmp r1, #0
	beq _02235D2E
	add r0, #0xc
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0xff
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl FreeToHeap
_02235D2E:
	pop {r4, pc}
	.align 2, 0
_02235D30: .word 0x00000FEC
	thumb_func_end MOD80_02235D10

	thumb_func_start MOD80_02235D34
MOD80_02235D34: ; 0x02235D34
	push {r4, lr}
	add r4, r0, #0
	add r2, r4, #0
	add r3, r4, #0
	ldr r1, [r4]
	add r2, #0xb8
	add r3, #0xba
	ldr r0, [r1, #8]
	ldrh r2, [r2]
	ldrh r3, [r3]
	ldr r1, [r1, #0xc]
	bl MOD80_02232FB8
	str r0, [r4, #0x60]
	add r0, r4, #0
	mov r1, #2
	add r0, #0x71
	strb r1, [r0]
	add r0, r4, #0
	mov r2, #1
	add r0, #0x73
	strb r2, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x74
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x72
	strb r2, [r0]
	add r0, r4, #0
	add r0, #0x78
	strh r1, [r0]
	ldr r0, [r4]
	ldr r0, [r0, #0x20]
	bl FUN_02079C70
	add r1, r4, #0
	add r1, #0x8c
	str r0, [r1]
	ldr r0, [r4]
	ldr r0, [r0, #0x34]
	str r0, [r4, #0x7c]
	ldr r0, [r4]
	ldr r0, [r0, #0x24]
	str r0, [r4, #0x64]
	ldr r0, [r4]
	ldr r0, [r0, #0x20]
	bl FUN_0202A918
	add r1, r4, #0
	add r1, #0x80
	str r0, [r1]
	add r0, r4, #0
	ldr r1, _02235DCC ; =0x022375E4
	add r0, #0x60
	bl FUN_0207B000
	ldr r1, [r4]
	add r0, r4, #0
	ldr r1, [r1, #0x1c]
	add r0, #0x60
	bl FUN_0207C2A4
	add r1, r4, #0
	ldr r0, _02235DD0 ; =UNK_020FA6E8
	add r1, #0x60
	mov r2, #0x3e
	bl OverlayManager_new
	str r0, [r4, #0x5c]
	mov r0, #1
	add r4, #0xac
	str r0, [r4]
	mov r0, #2
	pop {r4, pc}
	nop
_02235DCC: .word MOD80_022375E4
_02235DD0: .word UNK_020FA6E8
	thumb_func_end MOD80_02235D34

	thumb_func_start MOD80_02235DD4
MOD80_02235DD4: ; 0x02235DD4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x5c]
	mov r4, #3
	bl OverlayManager_Run
	cmp r0, #0
	beq _02235DF6
	ldr r0, [r5, #0x5c]
	bl OverlayManager_delete
	ldr r2, [r5, #0x24]
	add r0, r5, #0
	mov r1, #5
	bl MOD80_0222E7A8
	mov r4, #4
_02235DF6:
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD80_02235DD4

	thumb_func_start MOD80_02235DFC
MOD80_02235DFC: ; 0x02235DFC
	push {r3, lr}
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD80_02235DFC

	thumb_func_start MOD80_02235E08
MOD80_02235E08: ; 0x02235E08
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x3e
	bl AllocMonZeroed
	mov r1, #1
	lsl r1, r1, #0xc
	str r0, [r4, r1]
	ldr r0, [r4, #0x24]
	cmp r0, #0xa
	bls _02235E20
	b _02235F94
_02235E20:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02235E2C: ; jump table
	.short _02235F94 - _02235E2C - 2 ; case 0
	.short _02235F94 - _02235E2C - 2 ; case 1
	.short _02235F94 - _02235E2C - 2 ; case 2
	.short _02235F94 - _02235E2C - 2 ; case 3
	.short _02235F94 - _02235E2C - 2 ; case 4
	.short _02235F94 - _02235E2C - 2 ; case 5
	.short _02235F94 - _02235E2C - 2 ; case 6
	.short _02235E42 - _02235E2C - 2 ; case 7
	.short _02235E88 - _02235E2C - 2 ; case 8
	.short _02235F26 - _02235E2C - 2 ; case 9
	.short _02235ECE - _02235E2C - 2 ; case 10
_02235E42:
	add r0, r4, #0
	add r0, #0xd4
	bl FUN_020690E4
	add r1, r4, #0
	add r1, #0x90
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x90
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x94
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xd4
	bl MOD80_022361AC
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc8
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r4, #0
	mov r1, #3
	add r0, #0x9c
	str r1, [r0]
	add r0, r4, #0
	mov r1, #2
	add r0, #0xa0
	str r1, [r0]
	b _02235F94
_02235E88:
	add r0, r4, #0
	add r0, #0xd4
	bl FUN_020690E4
	add r1, r4, #0
	add r1, #0x94
	str r0, [r1]
	add r0, r4, #0
	add r0, #0x94
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x90
	str r1, [r0]
	add r0, r4, #0
	add r0, #0xd4
	bl MOD80_022361AC
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc8
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r4, #0
	mov r1, #3
	add r0, #0x9c
	str r1, [r0]
	add r0, r4, #0
	mov r1, #4
	add r0, #0xa0
	str r1, [r0]
	b _02235F94
_02235ECE:
	add r0, r4, #0
	add r0, #0xd4
	bl FUN_020690E4
	add r1, r4, #0
	add r1, #0x94
	str r0, [r1]
	ldr r0, [r4]
	mov r1, #1
	lsl r1, r1, #0xc
	ldr r0, [r0]
	ldr r1, [r4, r1]
	bl FUN_0202ABEC
	mov r0, #1
	lsl r0, r0, #0xc
	ldr r0, [r4, r0]
	bl FUN_020690E4
	add r1, r4, #0
	add r1, #0x90
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xd4
	bl MOD80_022361AC
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc8
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r4, #0
	mov r1, #3
	add r0, #0x9c
	str r1, [r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
	b _02235F94
_02235F26:
	ldr r0, [r4]
	ldr r1, [r4, r1]
	ldr r0, [r0]
	bl FUN_0202ABEC
	mov r0, #1
	lsl r0, r0, #0xc
	ldr r0, [r4, r0]
	bl FUN_020690E4
	add r1, r4, #0
	add r1, #0x90
	str r0, [r1]
	add r0, r4, #0
	mov r1, #0x7e
	add r0, #0xc4
	lsl r1, r1, #2
	add r2, r4, r1
	ldr r0, [r0]
	sub r1, #0xd4
	mul r1, r0
	add r0, r2, r1
	bl FUN_020690E4
	add r1, r4, #0
	add r1, #0x94
	str r0, [r1]
	add r0, r4, #0
	mov r1, #0x7e
	add r0, #0xc4
	lsl r1, r1, #2
	add r2, r4, r1
	ldr r0, [r0]
	sub r1, #0xd4
	mul r1, r0
	add r0, r2, r1
	bl MOD80_022361AC
	add r1, r4, #0
	add r1, #0xc8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc8
	ldr r1, [r0]
	add r0, r4, #0
	add r0, #0x98
	str r1, [r0]
	add r0, r4, #0
	mov r1, #3
	add r0, #0x9c
	str r1, [r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xa0
	str r1, [r0]
_02235F94:
	ldr r0, [r4]
	mov r2, #0x3e
	ldr r1, [r0, #0x24]
	add r0, r4, #0
	add r0, #0xa4
	str r1, [r0]
	add r1, r4, #0
	ldr r0, _02235FB8 ; =0x022375F0
	add r1, #0x90
	bl OverlayManager_new
	str r0, [r4, #0x5c]
	mov r0, #1
	add r4, #0xac
	str r0, [r4]
	mov r0, #2
	pop {r4, pc}
	nop
_02235FB8: .word MOD80_022375F0
	thumb_func_end MOD80_02235E08

	thumb_func_start MOD80_02235FBC
MOD80_02235FBC: ; 0x02235FBC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r4, r0, #0
	ldr r0, [r4, #0x2c]
	mov r6, #3
	cmp r0, #0
	beq _02235FD2
	cmp r0, #1
	bne _02235FD0
	b _02236148
_02235FD0:
	b _0223617E
_02235FD2:
	ldr r0, [r4, #0x5c]
	bl OverlayManager_Run
	cmp r0, #0
	bne _02235FDE
	b _0223617E
_02235FDE:
	ldr r0, [r4, #0x5c]
	bl OverlayManager_delete
	ldr r1, [r4, #0x24]
	cmp r1, #9
	bne _02236060
	add r0, r4, #0
	bl MOD80_022361E8
	mov r1, #6
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	add r3, r0, #0
	add r0, sp, #0x30
	lsl r3, r3, #0x10
	str r0, [sp]
	mov r0, #0
	add r1, r7, #0
	mov r2, #1
	lsr r3, r3, #0x10
	bl GetMonEvolution
	str r0, [sp, #0x24]
	cmp r0, #0
	beq _02236052
	ldr r5, [r4]
	ldr r0, [r5, #0x20]
	bl FUN_0204C1A8
	ldr r1, [r5, #0x3c]
	ldr r2, [sp, #0x24]
	str r1, [sp]
	ldr r1, [r5, #0x10]
	str r1, [sp, #4]
	ldr r1, [r5, #0x30]
	str r1, [sp, #8]
	ldr r1, [r5, #0x28]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x30]
	add r1, r7, #0
	str r0, [sp, #0x14]
	mov r0, #4
	str r0, [sp, #0x18]
	mov r0, #0x3e
	str r0, [sp, #0x1c]
	ldr r3, [r5, #0x24]
	mov r0, #0
	bl FUN_0206C700
	add r1, r4, #0
	add r1, #0xa8
	str r0, [r1]
	mov r0, #1
	str r0, [r4, #0x2c]
	b _0223617E
_02236052:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r6, #4
	b _0223617E
_02236060:
	cmp r1, #8
	beq _02236068
	cmp r1, #0xa
	bne _0223613A
_02236068:
	add r0, r4, #0
	bl MOD80_022361E8
	add r7, r0, #0
	mov r0, #0x3e
	bl AllocMonZeroed
	str r0, [sp, #0x20]
	ldr r0, [r4]
	ldr r1, [sp, #0x20]
	ldr r0, [r0]
	bl FUN_0202ABEC
	add r0, r7, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r5, r0, #0
	ldr r0, [sp, #0x20]
	mov r1, #5
	mov r2, #0
	bl GetMonData
	cmp r5, r0
	bne _022360B6
	mov r1, #0
	add r0, r7, #0
	add r2, r1, #0
	bl GetMonData
	add r5, r0, #0
	mov r1, #0
	ldr r0, [sp, #0x20]
	add r2, r1, #0
	bl GetMonData
	cmp r5, r0
	beq _02236126
_022360B6:
	add r0, r7, #0
	mov r1, #6
	mov r2, #0
	bl GetMonData
	add r3, r0, #0
	add r0, sp, #0x2c
	lsl r3, r3, #0x10
	str r0, [sp]
	mov r0, #0
	add r1, r7, #0
	mov r2, #1
	lsr r3, r3, #0x10
	bl GetMonEvolution
	str r0, [sp, #0x28]
	cmp r0, #0
	beq _02236118
	ldr r5, [r4]
	ldr r0, [r5, #0x20]
	bl FUN_0204C1A8
	ldr r1, [r5, #0x3c]
	ldr r2, [sp, #0x28]
	str r1, [sp]
	ldr r1, [r5, #0x10]
	str r1, [sp, #4]
	ldr r1, [r5, #0x30]
	str r1, [sp, #8]
	ldr r1, [r5, #0x28]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	add r1, r7, #0
	str r0, [sp, #0x14]
	mov r0, #4
	str r0, [sp, #0x18]
	mov r0, #0x3e
	str r0, [sp, #0x1c]
	ldr r3, [r5, #0x24]
	mov r0, #0
	bl FUN_0206C700
	add r1, r4, #0
	add r1, #0xa8
	str r0, [r1]
	mov r0, #1
	str r0, [r4, #0x2c]
	b _02236132
_02236118:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r6, #4
	b _02236132
_02236126:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r6, #4
_02236132:
	ldr r0, [sp, #0x20]
	bl FreeToHeap
	b _0223617E
_0223613A:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r6, #4
	b _0223617E
_02236148:
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl FUN_0206C91C
	cmp r0, #0
	beq _0223617E
	add r0, r4, #0
	add r0, #0xa8
	ldr r0, [r0]
	bl FUN_0206C92C
	add r0, r4, #0
	bl MOD80_02236218
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _02236184 ; =0xFFFF1FFF
	and r0, r1
	str r0, [r2]
	add r0, r4, #0
	mov r1, #7
	mov r2, #0xc
	bl MOD80_0222E7A8
	mov r6, #4
_0223617E:
	add r0, r6, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02236184: .word 0xFFFF1FFF
	thumb_func_end MOD80_02235FBC

	thumb_func_start MOD80_02236188
MOD80_02236188: ; 0x02236188
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	lsl r0, r0, #0xc
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0
	add r0, #0xc8
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r4, #0
	bl MOD80_0222E7B0
	mov r0, #1
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02236188

	thumb_func_start MOD80_022361AC
MOD80_022361AC: ; 0x022361AC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x3e
	bl PlayerProfile_init
	add r4, r0, #0
	bl PlayerProfile_Clear
	mov r1, #0x43
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r5, r1
	bl CopyPlayerName
	ldr r1, _022361E0 ; =0x00000122
	add r0, r4, #0
	ldrb r1, [r5, r1]
	bl FUN_02023A6C
	ldr r1, _022361E4 ; =0x00000123
	add r0, r4, #0
	ldrb r1, [r5, r1]
	bl FUN_02023A74
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022361E0: .word 0x00000122
_022361E4: .word 0x00000123
	thumb_func_end MOD80_022361AC

	thumb_func_start MOD80_022361E8
MOD80_022361E8: ; 0x022361E8
	push {r3, lr}
	cmp r1, #9
	bne _02236200
	mov r1, #0x7e
	lsl r1, r1, #2
	add r2, r0, r1
	add r0, #0xc4
	ldr r0, [r0]
	sub r1, #0xd4
	mul r1, r0
	add r0, r2, r1
	pop {r3, pc}
_02236200:
	cmp r1, #0xa
	bne _02236208
	add r0, #0xd4
	pop {r3, pc}
_02236208:
	cmp r1, #8
	bne _02236210
	add r0, #0xd4
	pop {r3, pc}
_02236210:
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	thumb_func_end MOD80_022361E8

	thumb_func_start MOD80_02236218
MOD80_02236218: ; 0x02236218
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r1, [r5, #0x24]
	bl MOD80_022361E8
	add r4, r0, #0
	add r0, r5, #0
	add r0, #0xcc
	ldr r0, [r0]
	cmp r0, #0x12
	bne _02236248
	ldr r0, [r5]
	add r5, #0xd0
	ldr r0, [r0, #8]
	ldr r1, [r5]
	bl GetPartyMonByIndex
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_02069B88
	add sp, #8
	pop {r3, r4, r5, pc}
_02236248:
	mov r0, #0
	add r1, r5, #0
	add r2, r5, #0
	str r0, [sp, #4]
	str r0, [sp]
	ldr r0, [r5]
	add r1, #0xcc
	add r2, #0xd0
	ldr r0, [r0, #0xc]
	ldr r1, [r1]
	ldr r2, [r2]
	bl PCStorage_DeleteBoxMonByIndexPair
	ldr r0, [r5]
	add r1, sp, #4
	ldr r0, [r0, #0xc]
	add r2, sp, #0
	bl PCStorage_FindFirstEmptySlot
	add r0, r4, #0
	bl FUN_020690E4
	add r2, r0, #0
	ldr r0, [r5]
	ldr r1, [sp, #4]
	ldr r0, [r0, #0xc]
	bl PCStorage_PlaceMonInBoxFirstEmptySlot
	add sp, #8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD80_02236218

	thumb_func_start MOD80_02236284
MOD80_02236284: ; 0x02236284
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD80_02236664
	mov r0, #6
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r2, r1, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #4]
	bl MOD80_02236378
	add r0, r4, #0
	bl MOD80_02236488
	add r0, r4, #0
	bl MOD80_02236580
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E6E4
	mov r0, #2
	mov r1, #1
	bl FUN_0201E6E4
	mov r0, #1
	add r1, r0, #0
	bl FUN_0201E74C
	mov r0, #2
	mov r1, #1
	bl FUN_0201E74C
	ldr r0, [r4]
	ldr r0, [r0, #0x20]
	bl FUN_02033288
	add r0, r4, #0
	bl MOD80_02236D84
	bl MOD04_021DDD7C
	cmp r0, #0
	bne _0223631E
	ldr r0, [r4]
	ldr r0, [r0, #0x40]
	cmp r0, #0
	beq _02236318
	ldr r0, _02236328 ; =0x00000F0F
	ldr r1, _0223632C ; =0x00000B3C
	str r0, [sp]
	mov r2, #1
	ldr r1, [r4, r1]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #2
	bl MOD80_0222E6DC
	add r0, r4, #0
	bl MOD80_0222E8BC
	b _02236322
_02236318:
	mov r0, #0
	str r0, [r4, #0x2c]
	b _02236322
_0223631E:
	mov r0, #0xf
	str r0, [r4, #0x2c]
_02236322:
	mov r0, #2
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02236328: .word 0x00000F0F
_0223632C: .word 0x00000B3C
	thumb_func_end MOD80_02236284

	thumb_func_start MOD80_02236330
MOD80_02236330: ; 0x02236330
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222E79C
	bl FUN_02033EEC
	ldr r1, [r4, #0x2c]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _0223634C ; =0x02237C68
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_0223634C: .word MOD80_02237C68
	thumb_func_end MOD80_02236330

	thumb_func_start MOD80_02236350
MOD80_02236350: ; 0x02236350
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0223669C
	add r0, r4, #0
	bl MOD80_02236638
	ldr r0, [r4, #4]
	bl MOD80_02236464
	add r0, r4, #0
	bl MOD80_0222E7B0
	ldr r0, [r4, #0x14]
	cmp r0, #0
	bne _02236374
	mov r0, #5
	pop {r4, pc}
_02236374:
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD80_02236350

	thumb_func_start MOD80_02236378
MOD80_02236378: ; 0x02236378
	push {r3, r4, r5, lr}
	sub sp, #0x70
	ldr r5, _02236454 ; =0x02237638
	add r4, r0, #0
	ldmia r5!, {r0, r1}
	add r3, sp, #0x54
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #0
	str r0, [r3]
	add r0, r4, #0
	add r3, r1, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0
	bl FUN_0201E6E4
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _02236458 ; =0x0223761C
	add r3, sp, #0x38
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #1
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #2
	mov r1, #0
	bl FUN_0201E6E4
	ldr r5, _0223645C ; =0x02237654
	add r3, sp, #0x1c
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #4
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0
	bl FUN_0201E74C
	add r0, r4, #0
	mov r1, #4
	bl FUN_02018744
	ldr r5, _02236460 ; =0x02237600
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #5
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #2
	mov r1, #0
	bl FUN_0201E74C
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x3e
	bl FUN_02017F18
	mov r0, #0x10
	mov r1, #0
	bl FUN_0201E74C
	add sp, #0x70
	pop {r3, r4, r5, pc}
	nop
_02236454: .word MOD80_02237638
_02236458: .word MOD80_0223761C
_0223645C: .word MOD80_02237654
_02236460: .word MOD80_02237600
	thumb_func_end MOD80_02236378

	thumb_func_start MOD80_02236464
MOD80_02236464: ; 0x02236464
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #1
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #0
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD80_02236464

	thumb_func_start MOD80_02236488
MOD80_02236488: ; 0x02236488
	push {r3, r4, r5, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r4, [r5, #4]
	mov r2, #0
	str r2, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x5c
	mov r1, #3
	add r3, r2, #0
	bl FUN_02006930
	mov r3, #0
	str r3, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	mov r0, #0x5c
	mov r1, #3
	mov r2, #4
	bl FUN_02006930
	mov r1, #0x1a
	mov r0, #0
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	mov r1, #0x1a
	mov r0, #4
	lsl r1, r1, #4
	mov r2, #0x3e
	bl FUN_02002EEC
	ldr r0, [r5]
	ldr r0, [r0, #0x24]
	bl FUN_02025084
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r1, #0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200CD68
	mov r1, #0
	str r1, [sp]
	mov r0, #0x3e
	str r0, [sp, #4]
	add r0, r4, #0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CB00
	mov r1, #0
	mov r0, #0x36
	str r1, [sp]
	lsl r0, r0, #6
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #2
	add r2, r4, #0
	mov r3, #1
	bl FUN_0200687C
	mov r1, #0
	mov r0, #6
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #4
	add r2, r4, #0
	mov r3, #1
	bl FUN_020068C8
	mov r1, #0
	mov r0, #0x36
	str r1, [sp]
	lsl r0, r0, #6
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #9
	add r2, r4, #0
	mov r3, #5
	bl FUN_0200687C
	mov r1, #0
	mov r0, #6
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x3e
	str r0, [sp, #0xc]
	mov r0, #0x5c
	mov r1, #0xa
	add r2, r4, #0
	mov r3, #5
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl FUN_02017FE4
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	add sp, #0x10
	pop {r3, r4, r5, pc}
	thumb_func_end MOD80_02236488

	thumb_func_start MOD80_02236580
MOD80_02236580: ; 0x02236580
	push {r3, r4, lr}
	sub sp, #0x14
	mov r3, #4
	add r4, r0, #0
	str r3, [sp]
	mov r0, #0x17
	str r0, [sp, #4]
	mov r0, #0x10
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x94
	ldr r1, _02236628 ; =0x00000EC8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	bl FUN_02019064
	ldr r0, _02236628 ; =0x00000EC8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r0, #1
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r1, _0223662C ; =0x00000EB8
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #4
	bl FUN_02019064
	ldr r0, _0223662C ; =0x00000EB8
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	mov r3, #1
	mov r1, #0xb5
	ldr r0, _02236630 ; =0x000F0E00
	str r3, [sp]
	str r0, [sp, #4]
	ldr r0, _0223662C ; =0x00000EB8
	lsl r1, r1, #4
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r2, #0
	bl MOD80_02236D1C
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x28
	ldr r1, _02236634 ; =0x00000E98
	str r0, [sp, #0x10]
	ldr r0, [r4, #4]
	add r1, r4, r1
	mov r2, #0
	mov r3, #2
	bl FUN_02019064
	ldr r0, _02236634 ; =0x00000E98
	mov r1, #0
	add r0, r4, r0
	bl FUN_02019620
	add sp, #0x14
	pop {r3, r4, pc}
	nop
_02236628: .word 0x00000EC8
_0223662C: .word 0x00000EB8
_02236630: .word 0x000F0E00
_02236634: .word 0x00000E98
	thumb_func_end MOD80_02236580

	thumb_func_start MOD80_02236638
MOD80_02236638: ; 0x02236638
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02236658 ; =0x00000E98
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _0223665C ; =0x00000EB8
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, _02236660 ; =0x00000EC8
	add r0, r4, r0
	bl FUN_02019178
	pop {r4, pc}
	nop
_02236658: .word 0x00000E98
_0223665C: .word 0x00000EB8
_02236660: .word 0x00000EC8
	thumb_func_end MOD80_02236638

	thumb_func_start MOD80_02236664
MOD80_02236664: ; 0x02236664
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb4
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _02236694 ; =0x00000B4C
	str r0, [r4, r1]
	mov r0, #1
	lsl r0, r0, #8
	mov r1, #0x3e
	bl String_ctor
	ldr r1, _02236698 ; =0x00000B7C
	str r0, [r4, r1]
	sub r1, #0x48
	ldr r0, [r4, r1]
	mov r1, #0x1f
	bl NewString_ReadMsgData
	mov r1, #0xb5
	lsl r1, r1, #4
	str r0, [r4, r1]
	pop {r4, pc}
	.align 2, 0
_02236694: .word 0x00000B4C
_02236698: .word 0x00000B7C
	thumb_func_end MOD80_02236664

	thumb_func_start MOD80_0223669C
MOD80_0223669C: ; 0x0223669C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb5
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _022366BC ; =0x00000B7C
	ldr r0, [r4, r0]
	bl String_dtor
	ldr r0, _022366C0 ; =0x00000B4C
	ldr r0, [r4, r0]
	bl String_dtor
	pop {r4, pc}
	.align 2, 0
_022366BC: .word 0x00000B7C
_022366C0: .word 0x00000B4C
	thumb_func_end MOD80_0223669C

	thumb_func_start MOD80_022366C4
MOD80_022366C4: ; 0x022366C4
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _022366F4 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x2d
	lsl r1, r1, #6
	ldr r1, [r4, r1]
	mov r2, #0x10
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0xb
	mov r2, #1
	bl MOD80_0222E6DC
	ldr r0, _022366F8 ; =0x0000100A
	mov r1, #1
	strh r1, [r4, r0]
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_022366F4: .word 0x00000F0F
_022366F8: .word 0x0000100A
	thumb_func_end MOD80_022366C4

	thumb_func_start MOD80_022366FC
MOD80_022366FC: ; 0x022366FC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, _02236758 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02236750
	sub r1, r1, #1
	cmp r0, r1
	bne _0223672E
	bl FUN_020332DC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
	b _02236750
_0223672E:
	ldr r0, _0223675C ; =0x00000F0F
	ldr r1, _02236760 ; =0x00000B3C
	str r0, [sp]
	mov r2, #1
	ldr r1, [r4, r1]
	add r0, r4, #0
	add r3, r2, #0
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #2
	bl MOD80_0222E6DC
	add r0, r4, #0
	bl MOD80_0222E8BC
_02236750:
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_02236758: .word 0x00000FCC
_0223675C: .word 0x00000F0F
_02236760: .word 0x00000B3C
	thumb_func_end MOD80_022366FC

	thumb_func_start MOD80_02236764
MOD80_02236764: ; 0x02236764
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0223678C ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	ldr r1, _02236790 ; =0x00000B34
	mov r2, #7
	ldr r1, [r4, r1]
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0xb
	mov r2, #0xe
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_0223678C: .word 0x00000F0F
_02236790: .word 0x00000B34
	thumb_func_end MOD80_02236764

	thumb_func_start MOD80_02236794
MOD80_02236794: ; 0x02236794
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _022367F4 ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _022367F0
	sub r1, r1, #1
	cmp r0, r1
	bne _022367D2
	bl MOD04_021DDD7C
	cmp r0, #0
	bne _022367BE
	mov r0, #0
	str r0, [r4, #0x2c]
	b _022367F0
_022367BE:
	add r0, r4, #0
	mov r1, #7
	mov r2, #0xb
	bl MOD80_0222E7A8
	mov r0, #1
	str r0, [r4, #0x1c]
	mov r0, #9
	str r0, [r4, #0x2c]
	b _022367F0
_022367D2:
	bl MOD04_021DDD7C
	cmp r0, #0
	beq _022367DE
	bl MOD04_021DDBBC
_022367DE:
	bl FUN_020332DC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
_022367F0:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_022367F4: .word 0x00000FCC
	thumb_func_end MOD80_02236794

	thumb_func_start MOD80_022367F8
MOD80_022367F8: ; 0x022367F8
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _02236820 ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x2d
	lsl r1, r1, #6
	ldr r1, [r4, r1]
	mov r2, #0x19
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0x10
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02236820: .word 0x00000F0F
	thumb_func_end MOD80_022367F8

	thumb_func_start MOD80_02236824
MOD80_02236824: ; 0x02236824
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020332DC
	bl MOD04_021DDBBC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #0x11
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02236824

	thumb_func_start MOD80_02236844
MOD80_02236844: ; 0x02236844
	push {r3, r4, lr}
	sub sp, #4
	ldr r1, _0223686C ; =0x00000F0F
	add r4, r0, #0
	str r1, [sp]
	mov r1, #0x2d
	lsl r1, r1, #6
	ldr r1, [r4, r1]
	mov r2, #0x1a
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0x12
	mov r2, #9
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0223686C: .word 0x00000F0F
	thumb_func_end MOD80_02236844

	thumb_func_start MOD80_02236870
MOD80_02236870: ; 0x02236870
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x50
	mov r1, #2
	mov r2, #1
	mov r3, #0x14
	bl MOD04_021DDEE0
	mov r0, #2
	bl MOD04_021DDE7C
	bl MOD04_021DDDCC
	mov r0, #3
	str r0, [r4, #0x2c]
	pop {r4, pc}
	thumb_func_end MOD80_02236870

	thumb_func_start MOD80_02236890
MOD80_02236890: ; 0x02236890
	push {r3, r4, lr}
	sub sp, #0x44
	add r4, r0, #0
	bl MOD04_021DDCE8
	bl MOD04_021DDD7C
	cmp r0, #0
	beq _022368F4
	bl MOD04_021DDC1C
	cmp r0, #4
	beq _022368EA
	cmp r0, #7
	beq _022368B4
	cmp r0, #8
	beq _022368D4
	b _022368F4
_022368B4:
	add r0, sp, #4
	bl MOD04_021DD808
	str r0, [r4, #0x40]
	ldr r0, [sp, #4]
	str r0, [r4, #0x44]
	bl MOD04_021DD6F0
	bl MOD04_021DDBBC
	add r0, r4, #0
	bl MOD80_0222E8D8
	mov r0, #0x15
	str r0, [r4, #0x2c]
	b _022368F4
_022368D4:
	add r0, sp, #0
	bl MOD04_021DD808
	add r0, r4, #0
	bl MOD80_0222E8D8
	mov r0, #0x13
	str r0, [r4, #0x2c]
	sub r0, #0x15
	str r0, [r4, #0x3c]
	b _022368F4
_022368EA:
	add r0, sp, #8
	bl MOD04_021DD9DC
	mov r0, #4
	str r0, [r4, #0x2c]
_022368F4:
	mov r0, #3
	add sp, #0x44
	pop {r3, r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02236890

	thumb_func_start MOD80_022368FC
MOD80_022368FC: ; 0x022368FC
	push {r4, lr}
	add r4, r0, #0
	bl MOD04_021DE05C
	cmp r0, #0
	beq _0223690C
	mov r0, #5
	str r0, [r4, #0x2c]
_0223690C:
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_022368FC

	thumb_func_start MOD80_02236910
MOD80_02236910: ; 0x02236910
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	bl MOD04_021DDF4C
	cmp r0, #3
	beq _02236928
	cmp r0, #4
	beq _0223692E
	cmp r0, #5
	beq _0223692E
	b _02236998
_02236928:
	mov r0, #6
	str r0, [r4, #0x2c]
	b _02236998
_0223692E:
	add r0, r4, #0
	bl MOD80_0222E8D8
	add r0, sp, #4
	add r1, sp, #0
	bl MOD04_021DD718
	str r0, [r4, #0x40]
	ldr r0, [sp, #4]
	str r0, [r4, #0x44]
	bl MOD04_021DD6F0
	bl MOD04_021DDBBC
	ldr r0, [sp]
	cmp r0, #7
	bhi _02236986
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223695C: ; jump table
	.short _02236986 - _0223695C - 2 ; case 0
	.short _0223696C - _0223695C - 2 ; case 1
	.short _0223696C - _0223695C - 2 ; case 2
	.short _02236986 - _0223695C - 2 ; case 3
	.short _02236972 - _0223695C - 2 ; case 4
	.short _02236986 - _0223695C - 2 ; case 5
	.short _0223697C - _0223695C - 2 ; case 6
	.short _02236982 - _0223695C - 2 ; case 7
_0223696C:
	mov r0, #0x15
	str r0, [r4, #0x2c]
	b _02236986
_02236972:
	bl MOD04_021EB550
	mov r0, #0x15
	str r0, [r4, #0x2c]
	b _02236986
_0223697C:
	mov r0, #0x15
	str r0, [r4, #0x2c]
	b _02236986
_02236982:
	bl FUN_020335E0
_02236986:
	ldr r1, [sp, #4]
	ldr r0, _022369A0 ; =0xFFFFB1E0
	cmp r1, r0
	bge _02236998
	ldr r0, _022369A4 ; =0xFFFF8AD1
	cmp r1, r0
	blt _02236998
	mov r0, #0x15
	str r0, [r4, #0x2c]
_02236998:
	mov r0, #3
	add sp, #8
	pop {r4, pc}
	nop
_022369A0: .word 0xFFFFB1E0
_022369A4: .word 0xFFFF8AD1
	thumb_func_end MOD80_02236910

	thumb_func_start MOD80_022369A8
MOD80_022369A8: ; 0x022369A8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #0x14]
	bl FUN_02028228
	add r4, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #4]
	bl FUN_02023830
	cmp r0, #0
	bne _022369CC
	ldr r1, [r5]
	ldr r0, [r1, #4]
	ldr r1, [r1, #0x38]
	bl FUN_02023834
_022369CC:
	ldr r0, [r5]
	ldr r0, [r0, #4]
	bl FUN_02023830
	add r6, r0, #0
	add r0, r4, #0
	bl DWC_CreateFriendKey
	add r3, r0, #0
	add r2, r1, #0
	add r0, r6, #0
	add r1, r3, #0
	bl MOD80_0222D5C0
	mov r0, #7
	str r0, [r5, #0x2c]
	mov r0, #3
	pop {r4, r5, r6, pc}
	thumb_func_end MOD80_022369A8

	thumb_func_start MOD80_022369F0
MOD80_022369F0: ; 0x022369F0
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DEBC
	mov r0, #8
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_022369F0

	thumb_func_start MOD80_02236A00
MOD80_02236A00: ; 0x02236A00
	push {r4, lr}
	add r4, r0, #0
	bl MOD80_0222DB98
	cmp r0, #0
	beq _02236A82
	bl MOD80_0222DBB8
	add r1, r0, #0
	add r1, #0xf
	cmp r1, #0x11
	bhi _02236A82
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02236A24: ; jump table
	.short _02236A68 - _02236A24 - 2 ; case 0
	.short _02236A70 - _02236A24 - 2 ; case 1
	.short _02236A78 - _02236A24 - 2 ; case 2
	.short _02236A68 - _02236A24 - 2 ; case 3
	.short _02236A82 - _02236A24 - 2 ; case 4
	.short _02236A82 - _02236A24 - 2 ; case 5
	.short _02236A82 - _02236A24 - 2 ; case 6
	.short _02236A82 - _02236A24 - 2 ; case 7
	.short _02236A82 - _02236A24 - 2 ; case 8
	.short _02236A82 - _02236A24 - 2 ; case 9
	.short _02236A82 - _02236A24 - 2 ; case 10
	.short _02236A82 - _02236A24 - 2 ; case 11
	.short _02236A82 - _02236A24 - 2 ; case 12
	.short _02236A70 - _02236A24 - 2 ; case 13
	.short _02236A60 - _02236A24 - 2 ; case 14
	.short _02236A48 - _02236A24 - 2 ; case 15
	.short _02236A58 - _02236A24 - 2 ; case 16
	.short _02236A60 - _02236A24 - 2 ; case 17
_02236A48:
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
	b _02236A82
_02236A58:
	str r0, [r4, #0x3c]
	mov r0, #0x13
	str r0, [r4, #0x2c]
	b _02236A82
_02236A60:
	str r0, [r4, #0x3c]
	mov r0, #0x13
	str r0, [r4, #0x2c]
	b _02236A82
_02236A68:
	str r0, [r4, #0x3c]
	mov r0, #0x13
	str r0, [r4, #0x2c]
	b _02236A82
_02236A70:
	str r0, [r4, #0x3c]
	mov r0, #0x13
	str r0, [r4, #0x2c]
	b _02236A82
_02236A78:
	add r0, r4, #0
	bl MOD80_0222E8D8
	bl FUN_020335E0
_02236A82:
	add r0, r4, #0
	bl MOD80_0222E8D8
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02236A00

	thumb_func_start MOD80_02236A8C
MOD80_02236A8C: ; 0x02236A8C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x44]
	neg r0, r0
	bl MOD04_021D80E0
	ldr r2, [r4, #0x44]
	add r1, r0, #0
	add r0, r4, #0
	neg r2, r2
	bl MOD80_02236E04
	mov r0, #0x16
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	thumb_func_end MOD80_02236A8C

	thumb_func_start MOD80_02236AAC
MOD80_02236AAC: ; 0x02236AAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02236AD4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _02236AC0
	mov r0, #2
	tst r0, r1
	beq _02236ACE
_02236AC0:
	ldr r0, _02236AD8 ; =0x00000EC8
	mov r1, #0
	add r0, r4, r0
	bl FUN_0200CCF8
	mov r0, #0
	str r0, [r4, #0x2c]
_02236ACE:
	mov r0, #3
	pop {r4, pc}
	nop
_02236AD4: .word gMain
_02236AD8: .word 0x00000EC8
	thumb_func_end MOD80_02236AAC

	thumb_func_start MOD80_02236ADC
MOD80_02236ADC: ; 0x02236ADC
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl FUN_02033ED0
	add r0, r4, #0
	bl MOD80_0222E8D8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x3e
	str r0, [sp, #8]
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
	bl FUN_0200E1D0
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r0, _02236B14 ; =0x0000100C
	mov r1, #1
	str r1, [r4, r0]
	mov r0, #4
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0
_02236B14: .word 0x0000100C
	thumb_func_end MOD80_02236ADC

	thumb_func_start MOD80_02236B18
MOD80_02236B18: ; 0x02236B18
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02236B4C ; =0x00000FCC
	mov r1, #0x3e
	ldr r0, [r4, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02236B48
	sub r1, r1, #1
	cmp r0, r1
	bne _02236B3A
	mov r0, #0
	str r0, [r4, #0x2c]
	b _02236B48
_02236B3A:
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
_02236B48:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
_02236B4C: .word 0x00000FCC
	thumb_func_end MOD80_02236B18

	thumb_func_start MOD80_02236B50
MOD80_02236B50: ; 0x02236B50
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	ldr r0, [r4, #0x3c]
	mov r2, #0
	add r0, #0xf
	cmp r0, #0x11
	bhi _02236B9E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02236B6C: ; jump table
	.short _02236B9C - _02236B6C - 2 ; case 0
	.short _02236B98 - _02236B6C - 2 ; case 1
	.short _02236B9E - _02236B6C - 2 ; case 2
	.short _02236B9C - _02236B6C - 2 ; case 3
	.short _02236B9E - _02236B6C - 2 ; case 4
	.short _02236B9E - _02236B6C - 2 ; case 5
	.short _02236B9E - _02236B6C - 2 ; case 6
	.short _02236B9E - _02236B6C - 2 ; case 7
	.short _02236B9E - _02236B6C - 2 ; case 8
	.short _02236B9E - _02236B6C - 2 ; case 9
	.short _02236B9C - _02236B6C - 2 ; case 10
	.short _02236B9E - _02236B6C - 2 ; case 11
	.short _02236B9C - _02236B6C - 2 ; case 12
	.short _02236B98 - _02236B6C - 2 ; case 13
	.short _02236B94 - _02236B6C - 2 ; case 14
	.short _02236B9E - _02236B6C - 2 ; case 15
	.short _02236B90 - _02236B6C - 2 ; case 16
	.short _02236B94 - _02236B6C - 2 ; case 17
_02236B90:
	mov r2, #0x8c
	b _02236B9E
_02236B94:
	mov r2, #0x8d
	b _02236B9E
_02236B98:
	mov r2, #0x92
	b _02236B9E
_02236B9C:
	mov r2, #0x91
_02236B9E:
	ldr r0, _02236BC0 ; =0x00000F0F
	ldr r1, _02236BC4 ; =0x00000B34
	str r0, [sp]
	ldr r1, [r4, r1]
	add r0, r4, #0
	mov r3, #1
	bl MOD80_02236C70
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0x14
	bl MOD80_0222E6DC
	mov r0, #3
	add sp, #4
	pop {r3, r4, pc}
	nop
_02236BC0: .word 0x00000F0F
_02236BC4: .word 0x00000B34
	thumb_func_end MOD80_02236B50

	thumb_func_start MOD80_02236BC8
MOD80_02236BC8: ; 0x02236BC8
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020332DC
	bl MOD04_021DDBBC
	mov r1, #0
	add r0, r4, #0
	add r2, r1, #0
	bl MOD80_0222E7A8
	mov r0, #9
	str r0, [r4, #0x2c]
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02236BC8

	thumb_func_start MOD80_02236BE8
MOD80_02236BE8: ; 0x02236BE8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02236C02
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02236C02:
	mov r0, #3
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02236BE8

	thumb_func_start MOD80_02236C08
MOD80_02236C08: ; 0x02236C08
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02236C32
	ldr r0, _02236C38 ; =0x00000FDC
	ldr r0, [r4, r0]
	cmp r0, #0x1e
	ble _02236C2A
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02236C2A:
	ldr r0, _02236C38 ; =0x00000FDC
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
_02236C32:
	mov r0, #3
	pop {r4, pc}
	nop
_02236C38: .word 0x00000FDC
	thumb_func_end MOD80_02236C08

	thumb_func_start MOD80_02236C3C
MOD80_02236C3C: ; 0x02236C3C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x2e
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _02236C66
	mov r2, #0x8d
	ldr r0, [r4, #4]
	mov r1, #0xd
	lsl r2, r2, #2
	bl MOD80_0222E6A8
	ldr r1, _02236C6C ; =0x00000FCC
	str r0, [r4, r1]
	ldr r0, [r4, #0x30]
	str r0, [r4, #0x2c]
_02236C66:
	mov r0, #3
	pop {r4, pc}
	nop
_02236C6C: .word 0x00000FCC
	thumb_func_end MOD80_02236C3C

	thumb_func_start MOD80_02236C70
MOD80_02236C70: ; 0x02236C70
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r0, r1, #0
	add r1, r2, #0
	add r4, r3, #0
	bl NewString_ReadMsgData
	mov r1, #0xb3
	add r6, r0, #0
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #0x1c
	ldr r1, [r5, r1]
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	ldr r0, _02236CD8 ; =0x00000E98
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _02236CD8 ; =0x00000E98
	mov r1, #0
	add r0, r5, r0
	mov r2, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	mov r3, #0
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _02236CD8 ; =0x00000E98
	ldr r2, _02236CDC ; =0x00000B4C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	ldr r0, _02236CE0 ; =0x00000FDC
	mov r1, #0
	str r1, [r5, r0]
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02236CD8: .word 0x00000E98
_02236CDC: .word 0x00000B4C
_02236CE0: .word 0x00000FDC
	thumb_func_end MOD80_02236C70

	thumb_func_start MOD80_02236CE4
MOD80_02236CE4: ; 0x02236CE4
	push {r4, lr}
	add r4, r0, #0
	cmp r3, #1
	beq _02236CF2
	cmp r3, #2
	beq _02236D08
	b _02236D16
_02236CF2:
	ldr r0, [sp, #0xc]
	mov r2, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r1, r1, r0
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r2, r0, #1
	b _02236D16
_02236D08:
	ldr r0, [sp, #0xc]
	mov r2, #0
	bl FUN_02002E14
	ldrb r1, [r4, #7]
	lsl r1, r1, #3
	sub r2, r1, r0
_02236D16:
	add r0, r2, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD80_02236CE4

	thumb_func_start MOD80_02236D1C
MOD80_02236D1C: ; 0x02236D1C
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r3, #0
	ldr r3, [sp, #0x24]
	add r5, r0, #0
	str r3, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r3, [sp, #0x20]
	add r6, r1, #0
	bl MOD80_02236CE4
	add r3, r0, #0
	str r4, [sp]
	mov r1, #0
	ldr r0, [sp, #0x24]
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	add r0, r5, #0
	mov r1, #1
	add r2, r6, #0
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r4, r5, r6, pc}
	thumb_func_end MOD80_02236D1C

	thumb_func_start MOD80_02236D50
MOD80_02236D50: ; 0x02236D50
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r4, r3, #0
	ldr r3, [sp, #0x24]
	add r5, r0, #0
	str r3, [sp]
	mov r3, #0
	str r3, [sp, #4]
	ldr r3, [sp, #0x20]
	add r6, r1, #0
	bl MOD80_02236CE4
	add r3, r0, #0
	str r4, [sp]
	mov r1, #0
	ldr r0, [sp, #0x24]
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r5, #0
	add r2, r6, #0
	str r1, [sp, #0xc]
	bl AddTextPrinterParameterized2
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD80_02236D50

	thumb_func_start MOD80_02236D84
MOD80_02236D84: ; 0x02236D84
	ldr r3, _02236D88 ; =FUN_02033E74
	bx r3
	.align 2, 0
_02236D88: .word FUN_02033E74
	thumb_func_end MOD80_02236D84

	thumb_func_start MOD80_02236D8C
MOD80_02236D8C: ; 0x02236D8C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #1
	add r6, r1, #0
	lsl r0, r0, #8
	mov r1, #0x3e
	bl String_ctor
	add r4, r0, #0
	mov r0, #0x2d
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	add r1, r6, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r1, #0xb3
	lsl r1, r1, #4
	ldr r0, [r5, r1]
	add r1, #0x4c
	ldr r1, [r5, r1]
	add r2, r4, #0
	bl StringExpandPlaceholders
	ldr r0, _02236DFC ; =0x00000EC8
	mov r1, #0xf
	add r0, r5, r0
	bl FUN_02019620
	ldr r0, _02236DFC ; =0x00000EC8
	mov r1, #1
	add r0, r5, r0
	mov r2, #0x1f
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	ldr r0, _02236DFC ; =0x00000EC8
	ldr r2, _02236E00 ; =0x00000B7C
	str r3, [sp, #8]
	ldr r2, [r5, r2]
	add r0, r5, r0
	mov r1, #1
	bl AddTextPrinterParameterized
	mov r1, #0x2e
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r4, #0
	bl String_dtor
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02236DFC: .word 0x00000EC8
_02236E00: .word 0x00000B7C
	thumb_func_end MOD80_02236D8C

	thumb_func_start MOD80_02236E04
MOD80_02236E04: ; 0x02236E04
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	mvn r0, r0
	cmp r4, r0
	bne _02236E16
	mov r4, #0xb
_02236E16:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xb3
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #0
	mov r3, #5
	bl BufferIntegerAsString
	ldr r0, _02236E44 ; =0x00000E98
	mov r1, #1
	add r0, r5, r0
	bl FUN_0200D0E0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD80_02236D8C
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02236E44: .word 0x00000E98
	thumb_func_end MOD80_02236E04

	.rodata
	.global MOD80_02236E48
MOD80_02236E48: ; 0x02236E48
	.byte 0x00, 0x17, 0x0D, 0x07, 0x04, 0x0D, 0x00, 0x00

	.global MOD80_02236E50
MOD80_02236E50: ; 0x02236E50
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236E60
MOD80_02236E60: ; 0x02236E60
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00

	.global MOD80_02236E70
MOD80_02236E70: ; 0x02236E70
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD80_02236E98
MOD80_02236E98: ; 0x02236E98
	.byte 0x32, 0x00

	.global MOD80_02236E9A
MOD80_02236E9A: ; 0x02236E9A
	.byte 0x38, 0x00, 0x32, 0x00, 0x60, 0x00, 0x32, 0x00, 0x88, 0x00

	.global MOD80_02236EA4
MOD80_02236EA4: ; 0x02236EA4
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236EB4
MOD80_02236EB4: ; 0x02236EB4
	.byte 0x5A, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00
	.byte 0x29, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00

	.global MOD80_02236ECC
MOD80_02236ECC: ; 0x02236ECC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236EE8
MOD80_02236EE8: ; 0x02236EE8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236F04
MOD80_02236F04: ; 0x02236F04
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236F20
MOD80_02236F20: ; 0x02236F20
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236F3C
MOD80_02236F3C: ; 0x02236F3C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236F58
MOD80_02236F58: ; 0x02236F58
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236F74
MOD80_02236F74: ; 0x02236F74
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236F90
MOD80_02236F90: ; 0x02236F90
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236FAC
MOD80_02236FAC: ; 0x02236FAC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236FC8
MOD80_02236FC8: ; 0x02236FC8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02236FE4
MOD80_02236FE4: ; 0x02236FE4
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00

	.global MOD80_02237084
MOD80_02237084: ; 0x02237084
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022370A0
MOD80_022370A0: ; 0x022370A0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022370BC
MOD80_022370BC: ; 0x022370BC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022370D8
MOD80_022370D8: ; 0x022370D8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022370F4
MOD80_022370F4: ; 0x022370F4
	.byte 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0C, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x0B, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x02, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD80_02237194
MOD80_02237194: ; 0x02237194
	.byte 0x14, 0x00, 0x07, 0x00, 0x14, 0x00, 0x0E, 0x00

	.global MOD80_0223719C
MOD80_0223719C: ; 0x0223719C
	.byte 0x03, 0x00, 0x04, 0x00, 0x02, 0x00, 0x06, 0x00, 0x03, 0x00, 0x09, 0x00, 0x02, 0x00, 0x0B, 0x00
	.byte 0x03, 0x00, 0x0E, 0x00, 0x02, 0x00, 0x10, 0x00

	.global MOD80_022371B4
MOD80_022371B4: ; 0x022371B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022371D0
MOD80_022371D0: ; 0x022371D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022371EC
MOD80_022371EC: ; 0x022371EC
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237208
MOD80_02237208: ; 0x02237208
	.byte 0xA2, 0x00, 0x24, 0x00, 0x16, 0x00, 0x24, 0x00

	.global MOD80_02237210
MOD80_02237210: ; 0x02237210
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237220
MOD80_02237220: ; 0x02237220
	.byte 0x67, 0x00, 0x68, 0x00, 0x69, 0x00, 0x2E, 0x00, 0x2F, 0x00, 0x30, 0x00, 0x31, 0x00, 0x32, 0x00
	.byte 0x33, 0x00, 0x34, 0x00

	.global MOD80_02237234
MOD80_02237234: ; 0x02237234
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237250
MOD80_02237250: ; 0x02237250
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_0223726C
MOD80_0223726C: ; 0x0223726C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237288
MOD80_02237288: ; 0x02237288
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022372A4
MOD80_022372A4: ; 0x022372A4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022372C0
MOD80_022372C0: ; 0x022372C0
	.byte 0x19, 0x00

	.global MOD80_022372C2
MOD80_022372C2: ; 0x022372C2
	.byte 0x3C, 0x00, 0x33, 0x00, 0x3C, 0x00, 0x4D, 0x00, 0x3C, 0x00, 0x67, 0x00, 0x3C, 0x00, 0x81, 0x00
	.byte 0x3C, 0x00, 0x9B, 0x00, 0x3C, 0x00, 0x19, 0x00, 0x54, 0x00, 0x33, 0x00, 0x54, 0x00, 0x4D, 0x00
	.byte 0x54, 0x00, 0x67, 0x00, 0x54, 0x00, 0x81, 0x00, 0x54, 0x00, 0x9B, 0x00, 0x54, 0x00, 0x19, 0x00
	.byte 0x6C, 0x00, 0x33, 0x00, 0x6C, 0x00, 0x4D, 0x00, 0x6C, 0x00, 0x67, 0x00, 0x6C, 0x00, 0x81, 0x00
	.byte 0x6C, 0x00, 0x9B, 0x00, 0x6C, 0x00, 0x19, 0x00, 0x84, 0x00, 0x33, 0x00, 0x84, 0x00, 0x4D, 0x00
	.byte 0x84, 0x00, 0x67, 0x00, 0x84, 0x00, 0x81, 0x00, 0x84, 0x00, 0x9B, 0x00, 0x84, 0x00, 0x19, 0x00
	.byte 0x9C, 0x00, 0x33, 0x00, 0x9C, 0x00, 0x4D, 0x00, 0x9C, 0x00, 0x67, 0x00, 0x9C, 0x00, 0x81, 0x00
	.byte 0x9C, 0x00, 0x9B, 0x00, 0x9C, 0x00, 0xE0, 0x00, 0xAF, 0x00, 0x62, 0x00, 0x20, 0x00

	.global MOD80_02237340
MOD80_02237340: ; 0x02237340
	.byte 0x1F, 0x06, 0x05, 0x01, 0x1F, 0x07, 0x00, 0x02, 0x1F, 0x08, 0x01, 0x03, 0x1F, 0x09, 0x02, 0x04
	.byte 0x1F, 0x0A, 0x03, 0x05, 0x1F, 0x0B, 0x04, 0x00, 0x00, 0x0C, 0x0B, 0x07, 0x01, 0x0D, 0x06, 0x08
	.byte 0x02, 0x0E, 0x07, 0x09, 0x03, 0x0F, 0x08, 0x0A, 0x04, 0x10, 0x09, 0x0B, 0x05, 0x11, 0x0A, 0x06
	.byte 0x06, 0x12, 0x11, 0x0D, 0x07, 0x13, 0x0C, 0x0E, 0x08, 0x14, 0x0D, 0x0F, 0x09, 0x15, 0x0E, 0x10
	.byte 0x0A, 0x16, 0x0F, 0x11, 0x0B, 0x17, 0x10, 0x0C, 0x0C, 0x18, 0x17, 0x13, 0x0D, 0x19, 0x12, 0x14
	.byte 0x0E, 0x1A, 0x13, 0x15, 0x0F, 0x1B, 0x14, 0x16, 0x10, 0x1C, 0x15, 0x17, 0x11, 0x1D, 0x16, 0x12
	.byte 0x12, 0x1F, 0x1E, 0x19, 0x13, 0x1F, 0x18, 0x1A, 0x14, 0x1F, 0x19, 0x1B, 0x15, 0x1F, 0x1A, 0x1C
	.byte 0x16, 0x1F, 0x1B, 0x1D, 0x17, 0x1F, 0x1C, 0x1E, 0x1E, 0x1E, 0x1D, 0x18, 0x1A, 0x02, 0x63, 0x65

	.global MOD80_022373C0
MOD80_022373C0: ; 0x022373C0
	.byte 0x72, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00

	.global MOD80_022373D0
MOD80_022373D0: ; 0x022373D0
	.byte 0x01, 0x00, 0x04, 0x00, 0x03, 0x00, 0x06, 0x00, 0x01, 0x00, 0x08, 0x00, 0x01, 0x00, 0x0D, 0x00
	.byte 0x03, 0x00, 0x0F, 0x00, 0x01, 0x00, 0x11, 0x00

	.global MOD80_022373E8
MOD80_022373E8: ; 0x022373E8
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237404
MOD80_02237404: ; 0x02237404
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237420
MOD80_02237420: ; 0x02237420
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_0223743C
MOD80_0223743C: ; 0x0223743C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237458
MOD80_02237458: ; 0x02237458
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237474
MOD80_02237474: ; 0x02237474
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x06, 0x00, 0x04, 0x08, 0x00, 0x12, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237494
MOD80_02237494: ; 0x02237494
	.byte 0x76, 0x00, 0x00, 0x00

	.global MOD80_02237498
MOD80_02237498: ; 0x02237498
	.byte 0x00, 0x00

	.global MOD80_0223749A
MOD80_0223749A: ; 0x0223749A
	.byte 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x78, 0x00, 0x00, 0x00, 0x0A, 0x00
	.byte 0x00, 0x00, 0x79, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x1E, 0x00
	.byte 0x00, 0x00, 0x7B, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x32, 0x00
	.byte 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x46, 0x00
	.byte 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x5A, 0x00
	.byte 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x64, 0x00, 0x64, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD80_022374FC
MOD80_022374FC: ; 0x022374FC
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_0223750C
MOD80_0223750C: ; 0x0223750C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237528
MOD80_02237528: ; 0x02237528
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237544
MOD80_02237544: ; 0x02237544
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237560
MOD80_02237560: ; 0x02237560
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_0223757C
MOD80_0223757C: ; 0x0223757C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237598
MOD80_02237598: ; 0x02237598
	.byte 0x00, 0x24, 0x00, 0x26, 0x00, 0x28, 0x00, 0x2A, 0x00, 0x2C, 0x00, 0x2E, 0x00, 0x30

	.global MOD80_022375A6
MOD80_022375A6: ; 0x022375A6
	.byte 0x80, 0x00, 0x36, 0x00, 0x60, 0x00, 0x37, 0x00, 0xA0, 0x00, 0x37, 0x00, 0x40, 0x00, 0x46, 0x00
	.byte 0xC0, 0x00, 0x46, 0x00, 0x30, 0x00, 0x66, 0x00, 0xD0, 0x00, 0x66, 0x00

	.global MOD80_022375C2
MOD80_022375C2: ; 0x022375C2
	.byte 0x26, 0x46, 0x70, 0x90, 0x27, 0x47, 0x50, 0x70, 0x27, 0x47, 0x90, 0xB0, 0x36, 0x56, 0x30, 0x50
	.byte 0x36, 0x56, 0xB0, 0xD0, 0x56, 0x76, 0x20, 0x40, 0x56, 0x76, 0xC0, 0xE0, 0xFF, 0x00, 0x00, 0x00
	.byte 0x00, 0x00

	.global MOD80_022375E4
MOD80_022375E4: ; 0x022375E4
	.byte 0x00, 0x01, 0x02, 0x04, 0x03, 0x05, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00

	.global MOD80_022375F0
MOD80_022375F0: ; 0x022375F0
	.word MOD81_02237E40, MOD81_02238064, MOD81_02238004, 0x00000051

	.global MOD80_02237600
MOD80_02237600: ; 0x02237600
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_0223761C
MOD80_0223761C: ; 0x0223761C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237638
MOD80_02237638: ; 0x02237638
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237654
MOD80_02237654: ; 0x02237654
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.data
	.global MOD80_02237680
MOD80_02237680: ; 0x02237680
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x70, 0x6F, 0x73, 0x74, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022376CC
MOD80_022376CC: ; 0x022376CC
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x70, 0x6F, 0x73, 0x74, 0x5F, 0x66, 0x69, 0x6E, 0x69, 0x73, 0x68, 0x2E, 0x61, 0x73, 0x70, 0x00

	.global MOD80_0223771C
MOD80_0223771C: ; 0x0223771C
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x67, 0x65, 0x74, 0x2E, 0x61, 0x73, 0x70, 0x00

	.global MOD80_02237764
MOD80_02237764: ; 0x02237764
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00

	.global MOD80_022377B0
MOD80_022377B0: ; 0x022377B0
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x64, 0x65, 0x6C, 0x65, 0x74, 0x65, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00

	.global MOD80_022377FC
MOD80_022377FC: ; 0x022377FC
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x72, 0x65, 0x74, 0x75, 0x72, 0x6E, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00

	.global MOD80_02237848
MOD80_02237848: ; 0x02237848
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00

	.global MOD80_02237894
MOD80_02237894: ; 0x02237894
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00, 0x00, 0x00

	.global MOD80_022378E4
MOD80_022378E4: ; 0x022378E4
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x5F, 0x66, 0x69, 0x6E, 0x69, 0x73, 0x68, 0x2E
	.byte 0x61, 0x73, 0x70, 0x00

	.global MOD80_02237938
MOD80_02237938: ; 0x02237938
	.byte 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x67, 0x61, 0x6D, 0x65, 0x73, 0x74, 0x61, 0x74, 0x73
	.byte 0x32, 0x2E, 0x67, 0x73, 0x2E, 0x6E, 0x69, 0x6E, 0x74, 0x65, 0x6E, 0x64, 0x6F, 0x77, 0x69, 0x66
	.byte 0x69, 0x2E, 0x6E, 0x65, 0x74, 0x2F, 0x70, 0x6F, 0x6B, 0x65, 0x6D, 0x6F, 0x6E, 0x64, 0x70, 0x64
	.byte 0x73, 0x2F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x65, 0x78, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x2F
	.byte 0x69, 0x6E, 0x66, 0x6F, 0x2E, 0x61, 0x73, 0x70, 0x00, 0x00, 0x00, 0x00

	.global MOD80_02237984
MOD80_02237984: ; 0x02237984
	.word MOD80_02236284

	.global MOD80_02237988
MOD80_02237988: ; 0x02237988
	.word MOD80_02236330

	.global MOD80_0223798C
MOD80_0223798C: ; 0x0223798C
	.word MOD80_02236350, MOD80_0222E8F4, MOD80_0222E9B8, MOD80_0222E9D8
	.word MOD80_0222F394, MOD80_0222F45C, MOD80_0222F470, MOD80_0222FE60
	.word MOD80_0222FF34, MOD80_0222FF48, MOD80_0223065C, MOD80_02230728
	.word MOD80_0223073C, MOD80_022319F0, MOD80_02231A64, MOD80_02231A84
	.word MOD80_02233218, MOD80_022332A8, MOD80_022332C8, MOD80_022346FC
	.word MOD80_02234740, MOD80_02234760, MOD80_02235D34, MOD80_02235DD4
	.word MOD80_02235DFC, MOD80_02235E08, MOD80_02235FBC, MOD80_02236188

	.global MOD80_022379FC
MOD80_022379FC: ; 0x022379FC
	.word MOD80_0222EE24, MOD80_0222EE64, MOD80_0222EE74, MOD80_0222EE98
	.word MOD80_0222EEAC, MOD80_0222EEC0, MOD80_0222EEFC, MOD80_0222F0A8
	.word MOD80_0222F0D0, MOD80_0222F0E4, MOD80_0222F1B8, MOD80_0222F1D8
	.word MOD80_0222F12C, MOD80_0222F14C

	.global MOD80_02237A34
MOD80_02237A34: ; 0x02237A34
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x05, 0x00, 0x00, 0x04, 0x03, 0x00

	.global MOD80_02237A40
MOD80_02237A40: ; 0x02237A40
	.word MOD80_0222F864, MOD80_0222F86C, MOD80_0222F8CC, MOD80_0222FAE8
	.word MOD80_0222FB08, MOD80_0222F8F4, MOD80_0222F918, MOD80_0222F96C
	.word MOD80_0222FA04

	.global MOD80_02237A64
MOD80_02237A64: ; 0x02237A64
	.word MOD80_022302F0, MOD80_022302F8, MOD80_02230394, MOD80_022304D8
	.word MOD80_022303D8, MOD80_022303F8, MOD80_022304C8

	.global MOD80_02237A80
MOD80_02237A80: ; 0x02237A80
	.byte 0x14, 0x00

	.global MOD80_02237A82
MOD80_02237A82: ; 0x02237A82
	.byte 0x27, 0x00, 0x14, 0x00, 0x4F, 0x00, 0x14, 0x00, 0x77, 0x00, 0x8C, 0x00, 0x40, 0x00, 0x8C, 0x00
	.byte 0x78, 0x00

	.global MOD80_02237A94
MOD80_02237A94: ; 0x02237A94
	.word MOD80_02230B6C, MOD80_02230B94, MOD80_02231114, MOD80_0223113C
	.word MOD80_022311C8, MOD80_02231200, MOD80_022312CC, MOD80_0223131C
	.word MOD80_02231490, MOD80_022314EC, MOD80_02231524, MOD80_02231614
	.word MOD80_02231670, MOD80_022316A8, MOD80_02230CC8, MOD80_02230DB8
	.word MOD80_02230E14, MOD80_02230E9C, MOD80_02230EFC, MOD80_02230F3C
	.word MOD80_02231828, MOD80_02231848, MOD80_02231790, MOD80_022317B4
	.word MOD80_022317F8, MOD80_02231800, MOD80_02230F78, MOD80_02230FB4

	.global MOD80_02237B04
MOD80_02237B04: ; 0x02237B04
	.word MOD80_02232128, MOD80_0223213C, MOD80_0223284C, MOD80_02232AE8
	.word MOD80_02232B08, MOD80_022328A4, MOD80_022328C8, MOD80_02232470
	.word MOD80_02232518, MOD80_02232670, MOD80_02232718, MOD80_02232900
	.word MOD80_0223292C, MOD80_02232950, MOD80_02232A34, MOD80_02232A60
	.word MOD80_02232A84

	.global MOD80_02237B48
MOD80_02237B48: ; 0x02237B48
	.byte 0x00, 0x06, 0x05, 0x00, 0x00, 0x04, 0x03, 0x00

	.global MOD80_02237B50
MOD80_02237B50: ; 0x02237B50
	.byte 0x00, 0x00, 0x57, 0x00, 0x88, 0x00, 0xBF, 0x00, 0xEB, 0x00, 0x2F, 0x01, 0x68, 0x01, 0xC9, 0x01
	.byte 0xE7, 0x01, 0xED, 0x01

	.global MOD80_02237B64
MOD80_02237B64: ; 0x02237B64
	.byte 0x72, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x74, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD80_02237B84
MOD80_02237B84: ; 0x02237B84
	.word MOD80_022336C4, MOD80_022336F8, MOD80_02233E30, MOD80_02233784
	.word MOD80_022337BC, MOD80_02233890, MOD80_0223390C, MOD80_02233A6C
	.word MOD80_02233AC8, MOD80_02233B00, MOD80_02233BE8, MOD80_02233C44
	.word MOD80_02233C7C, MOD80_02233D8C, MOD80_02233DB4, MOD80_02233DD8
	.word MOD80_02233E84

	.global MOD80_02237BC8
MOD80_02237BC8: ; 0x02237BC8
	.word MOD80_022349CC, MOD80_022351CC, MOD80_02234AC0, MOD80_02234AE4
	.word MOD80_02234B60, MOD80_02234B74, MOD80_022351D0, MOD80_02234BD8
	.word MOD80_02234BF4, MOD80_02234C8C, MOD80_02234C9C, MOD80_022351E8
	.word MOD80_02234CFC, MOD80_02234D3C, MOD80_02234DF8, MOD80_02234E08
	.word MOD80_02235200, MOD80_022352AC, MOD80_022350F0, MOD80_02235158
	.word MOD80_02235168, MOD80_02235214, MOD80_0223522C, MOD80_0223523C
	.word MOD80_02234E68, MOD80_02234E7C, MOD80_0223502C, MOD80_02235040
	.word MOD80_02235018, MOD80_02235398, MOD80_022353B4, MOD80_022353F4
	.word MOD80_02235410, MOD80_02235430, MOD80_02235454, MOD80_02235470
	.word MOD80_022354BC, MOD80_02235514, MOD80_02235348, MOD80_02235370

	.global MOD80_02237C68
MOD80_02237C68: ; 0x02237C68
	.word MOD80_022366C4, MOD80_022366FC, MOD80_02236870, MOD80_02236890
	.word MOD80_022368FC, MOD80_02236910, MOD80_022369A8, MOD80_022369F0
	.word MOD80_02236A00, MOD80_02236ADC, MOD80_02236BE8, MOD80_02236C3C
	.word MOD80_02236B18, MOD80_02236764, MOD80_02236794, MOD80_022367F8
	.word MOD80_02236824, MOD80_02236844, MOD80_02236C08, MOD80_02236B50
	.word MOD80_02236BC8, MOD80_02236A8C, MOD80_02236AAC, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000

	.bss
	.global MOD80_02237CE0
MOD80_02237CE0: ; 0x02237CE0
	.space 0xC

	.global MOD80_02237CEC
MOD80_02237CEC: ; 0x02237CEC
	.space 0x8

	.global MOD80_02237CF4
MOD80_02237CF4: ; 0x02237CF4
	.space 0xEC

	.global MOD80_02237DE0
MOD80_02237DE0: ; 0x02237DE0
	.space 0x20

	.global MOD80_02237E00
MOD80_02237E00: ; 0x02237E00
	.space 0x1C

	.global MOD80_02237E1C
MOD80_02237E1C: ; 0x02237E1C
	.space 0x8

	.global MOD80_02237E24
MOD80_02237E24: ; 0x02237E24
	.space 0x1C

