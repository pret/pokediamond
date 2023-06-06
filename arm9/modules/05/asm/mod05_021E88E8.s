	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021E88E8
MOD05_021E88E8: ; 0x021E88E8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bls _021E88FA
	b _021E8A56
_021E88FA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8906: ; jump table
	.short _021E8912 - _021E8906 - 2 ; case 0
	.short _021E8936 - _021E8906 - 2 ; case 1
	.short _021E8952 - _021E8906 - 2 ; case 2
	.short _021E899C - _021E8906 - 2 ; case 3
	.short _021E89F4 - _021E8906 - 2 ; case 4
	.short _021E8A1C - _021E8906 - 2 ; case 5
_021E8912:
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r1, #0
	mov r2, #0x20
	bl memset
	ldr r5, [r4, #0xc]
	bl MOD05_021E3768
	str r0, [r5, #0x1c]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8936:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8952:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021E8A56
	mov r1, #0
	str r1, [r4, #4]
	ldr r0, [r4]
	mov r2, #2
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8A5C ; =0xFFFFD000
	str r1, [sp]
	str r0, [sp, #4]
	lsl r0, r0, #2
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	mov r3, #7
	bl MOD05_021E37CC
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl Camera_GetDistance
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	mov r3, #0x1e
	str r0, [sp]
	add r0, r5, #4
	add r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E899C:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl Camera_SetDistance
	cmp r6, #1
	bne _021E8A56
	ldr r0, [r4]
	mov r2, #2
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8A5C ; =0xFFFFD000
	mov r3, #6
	str r0, [sp]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl MOD05_021E3888
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl Camera_GetDistance
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	str r0, [sp]
	ldr r3, _021E8A60 ; =0xFFF01000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E89F4:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl Camera_SetDistance
	cmp r6, #1
	bne _021E8A56
	add r0, r4, #0
	bl MOD05_021E35AC
	cmp r0, #1
	bne _021E8A56
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8A1C:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, _021E8A64 ; =0x04000010
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8A42
	mov r0, #1
	str r0, [r1]
_021E8A42:
	ldr r0, [r5, #0x1c]
	bl MOD05_021E37A4
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021E8A56:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E8A5C: .word 0xFFFFD000
_021E8A60: .word 0xFFF01000
_021E8A64: .word 0x04000010

	thumb_func_start MOD05_021E8A68
MOD05_021E8A68: ; 0x021E8A68
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bls _021E8A7A
	b _021E8BD6
_021E8A7A:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8A86: ; jump table
	.short _021E8A92 - _021E8A86 - 2 ; case 0
	.short _021E8AB6 - _021E8A86 - 2 ; case 1
	.short _021E8AD2 - _021E8A86 - 2 ; case 2
	.short _021E8B1C - _021E8A86 - 2 ; case 3
	.short _021E8B74 - _021E8A86 - 2 ; case 4
	.short _021E8B9C - _021E8A86 - 2 ; case 5
_021E8A92:
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r1, #0
	mov r2, #0x20
	bl memset
	ldr r5, [r4, #0xc]
	bl MOD05_021E3768
	str r0, [r5, #0x1c]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8AB6:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8AD2:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021E8BD6
	mov r1, #0
	str r1, [r4, #4]
	ldr r0, [r4]
	mov r2, #5
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8BDC ; =0xFFFFE000
	str r1, [sp]
	str r0, [sp, #4]
	ldr r0, _021E8BE0 ; =0xFFFF4000
	mov r3, #7
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl MOD05_021E37CC
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl Camera_GetDistance
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	mov r3, #0x1e
	str r0, [sp]
	add r0, r5, #4
	add r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E8B1C:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl Camera_SetDistance
	cmp r6, #1
	bne _021E8BD6
	ldr r0, [r4]
	mov r2, #5
	add r0, r0, #1
	str r0, [r4]
	ldr r0, _021E8BDC ; =0xFFFFE000
	mov r3, #6
	str r0, [sp]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0x1e
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r1, [r5, #0x1c]
	add r0, r4, #0
	bl MOD05_021E3888
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl Camera_GetDistance
	mov r2, #0x1e
	add r1, r0, #0
	mov r0, #6
	lsl r2, r2, #0xc
	str r0, [sp]
	ldr r3, _021E8BE4 ; =0xFFF9C000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_021E8B74:
	add r0, r5, #4
	bl MOD05_021E36A4
	add r6, r0, #0
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl Camera_SetDistance
	cmp r6, #1
	bne _021E8BD6
	add r0, r4, #0
	bl MOD05_021E35AC
	cmp r0, #1
	bne _021E8BD6
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8B9C:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, _021E8BE8 ; =0x04000010
	mov r1, #0
	str r1, [r0]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8BC2
	mov r0, #1
	str r0, [r1]
_021E8BC2:
	ldr r0, [r5, #0x1c]
	bl MOD05_021E37A4
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021E8BD6:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E8BDC: .word 0xFFFFE000
_021E8BE0: .word 0xFFFF4000
_021E8BE4: .word 0xFFF9C000
_021E8BE8: .word 0x04000010

	thumb_func_start MOD05_021E8BEC
MOD05_021E8BEC: ; 0x021E8BEC
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #6
	bls _021E8BFE
	b _021E8D16
_021E8BFE:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8C0A: ; jump table
	.short _021E8C18 - _021E8C0A - 2 ; case 0
	.short _021E8C4A - _021E8C0A - 2 ; case 1
	.short _021E8C6A - _021E8C0A - 2 ; case 2
	.short _021E8CA0 - _021E8C0A - 2 ; case 3
	.short _021E8CB2 - _021E8C0A - 2 ; case 4
	.short _021E8CD4 - _021E8C0A - 2 ; case 5
	.short _021E8CE6 - _021E8C0A - 2 ; case 6
_021E8C18:
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x10
	mov r1, #0
_021E8C26:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E8C26
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl MOD05_021E8E8C
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8C4A:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	mov r0, #0xa
	str r0, [r5, #0xc]
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8C6A:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8D16
	ldr r0, [r4]
	mov r3, #0x32
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0xc
	str r0, [r5, #0xc]
	lsl r0, r0, #0xc
	str r0, [sp]
	lsl r3, r3, #4
	str r3, [sp, #4]
	ldr r0, _021E8D1C ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r2, #0xbf
	sub r3, #0x76
	bl MOD05_021E8EC0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
_021E8CA0:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8D16
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8CB2:
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x1e
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8CD4:
	bl FUN_0200E308
	cmp r0, #0
	beq _021E8D16
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8CE6:
	add r0, r5, #0
	bl MOD05_021E8EA8
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8D00
	mov r0, #1
	str r0, [r1]
_021E8D00:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E8D16:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	nop
_021E8D1C: .word 0x04000010

	thumb_func_start MOD05_021E8D20
MOD05_021E8D20: ; 0x021E8D20
	push {r3, r4, r5, r6, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #6
	bls _021E8D32
	b _021E8E4C
_021E8D32:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E8D3E: ; jump table
	.short _021E8D4C - _021E8D3E - 2 ; case 0
	.short _021E8D7E - _021E8D3E - 2 ; case 1
	.short _021E8D9E - _021E8D3E - 2 ; case 2
	.short _021E8DD6 - _021E8D3E - 2 ; case 3
	.short _021E8DE8 - _021E8D3E - 2 ; case 4
	.short _021E8E0A - _021E8D3E - 2 ; case 5
	.short _021E8E1C - _021E8D3E - 2 ; case 6
_021E8D4C:
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x10
	mov r1, #0
_021E8D5A:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E8D5A
	ldr r0, [r4, #0xc]
	mov r1, #4
	bl MOD05_021E8E8C
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8D7E:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	mov r0, #0xa
	str r0, [r5, #0xc]
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8D9E:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8E4C
	ldr r0, [r4]
	mov r3, #0x32
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0xc
	str r0, [r5, #0xc]
	mov r0, #0xf
	lsl r0, r0, #0xc
	str r0, [sp]
	lsl r3, r3, #4
	str r3, [sp, #4]
	ldr r0, _021E8E50 ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r5, #0
	mov r2, #0xbf
	add r3, #0xdf
	bl MOD05_021E8EC0
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
_021E8DD6:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021E8E4C
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8DE8:
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x1e
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8E0A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021E8E4C
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8E1C:
	add r0, r5, #0
	bl MOD05_021E8EA8
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E8E36
	mov r0, #1
	str r0, [r1]
_021E8E36:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E8E4C:
	add sp, #0x14
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021E8E50: .word 0x04000010

	thumb_func_start MOD05_021E8E54
MOD05_021E8E54: ; 0x021E8E54
	ldr r3, _021E8E60 ; =FUN_0200CA60
	mov r2, #1
	add r1, r0, #0
	ldr r0, _021E8E64 ; =MOD05_021E8E68
	lsl r2, r2, #0xa
	bx r3
	.balign 4, 0
_021E8E60: .word FUN_0200CA60
_021E8E64: .word MOD05_021E8E68

	thumb_func_start MOD05_021E8E68
MOD05_021E8E68: ; 0x021E8E68
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #8]
	cmp r0, #2
	blo _021E8E7C
	ldr r0, [r4]
	bl FUN_02012B30
	mov r0, #0
	str r0, [r4, #8]
_021E8E7C:
	ldr r0, [r4]
	bl FUN_02012B68
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8E8C
MOD05_021E8E8C: ; 0x021E8E8C
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl FUN_02012A00
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	add r0, r4, #0
	bl MOD05_021E8E54
	str r0, [r4, #4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8EA8
MOD05_021E8EA8: ; 0x021E8EA8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FUN_0200CAB4
	ldr r0, [r4]
	bl FUN_02012AC4
	ldr r0, [r4]
	bl FUN_02012B00
	pop {r4, pc}

	thumb_func_start MOD05_021E8EC0
MOD05_021E8EC0: ; 0x021E8EC0
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r4, [sp, #0x20]
	add r5, sp, #0x10
	str r4, [sp]
	mov r4, #0x14
	ldrsh r4, [r5, r4]
	str r4, [sp, #4]
	ldr r4, [sp, #0x28]
	str r4, [sp, #8]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x10]
	ldr r0, [r0]
	bl FUN_02012A30
	add sp, #0x14
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021E8EE8
MOD05_021E8EE8: ; 0x021E8EE8
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, [r0]
	add r7, r1, #0
	bl FUN_02012B20
	add r5, r0, #0
	mov r6, #0
_021E8EF6:
	ldr r0, [r5]
	add r1, r7, #0
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, r6, #0
	bl _u32_div_f
	mov r1, #1
	tst r0, r1
	bne _021E8F0E
	lsl r0, r4, #0x10
	b _021E8F12
_021E8F0E:
	neg r0, r4
	lsl r0, r0, #0x10
_021E8F12:
	lsr r0, r0, #0x10
	str r0, [r5]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #0xc0
	blt _021E8EF6
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021E8F20
MOD05_021E8F20: ; 0x021E8F20
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bhi _021E9026
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E8F3C: ; jump table
	.short _021E8F48 - _021E8F3C - 2 ; case 0
	.short _021E8F68 - _021E8F3C - 2 ; case 1
	.short _021E8F84 - _021E8F3C - 2 ; case 2
	.short _021E8F92 - _021E8F3C - 2 ; case 3
	.short _021E8FDC - _021E8F3C - 2 ; case 4
	.short _021E8FFC - _021E8F3C - 2 ; case 5
_021E8F48:
	mov r0, #4
	mov r1, #0x1c
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x1c
	mov r1, #0
_021E8F56:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E8F56
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8F68:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8F84:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021E9026
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8F92:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl Camera_GetDistance
	mov r2, #0x19
	add r1, r0, #0
	mov r0, #0xc
	lsl r2, r2, #0x10
	str r0, [sp]
	ldr r3, _021E902C ; =0xFFFFE000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8FDC:
	add r0, r5, #4
	bl MOD05_021E36A4
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl Camera_SetDistance
	bl FUN_0200E308
	cmp r0, #0
	beq _021E9026
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E8FFC:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E9010
	mov r0, #1
	str r0, [r1]
_021E9010:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E9026:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E902C: .word 0xFFFFE000

	thumb_func_start MOD05_021E9030
MOD05_021E9030: ; 0x021E9030
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #5
	bhi _021E9136
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E904C: ; jump table
	.short _021E9058 - _021E904C - 2 ; case 0
	.short _021E9078 - _021E904C - 2 ; case 1
	.short _021E9094 - _021E904C - 2 ; case 2
	.short _021E90A2 - _021E904C - 2 ; case 3
	.short _021E90EC - _021E904C - 2 ; case 4
	.short _021E910C - _021E904C - 2 ; case 5
_021E9058:
	mov r0, #4
	mov r1, #0x1c
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x1c
	mov r1, #0
_021E9066:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021E9066
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E9078:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E9094:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021E9136
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E90A2:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	str r0, [r5]
	bl Camera_GetDistance
	mov r2, #0x32
	add r1, r0, #0
	mov r0, #0xc
	lsl r2, r2, #0x10
	str r0, [sp]
	ldr r3, _021E913C ; =0xFFFFB000
	add r0, r5, #4
	sub r2, r1, r2
	bl MOD05_021E3644
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E90EC:
	add r0, r5, #4
	bl MOD05_021E36A4
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl Camera_SetDistance
	bl FUN_0200E308
	cmp r0, #0
	beq _021E9136
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021E910C:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021E9120
	mov r0, #1
	str r0, [r1]
_021E9120:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021E9136:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_021E913C: .word 0xFFFFB000

	thumb_func_start MOD05_021E9140
MOD05_021E9140: ; 0x021E9140
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	add r7, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r7]
	ldr r4, [r7, #0xc]
	cmp r0, #7
	bls _021E9152
	b _021E948A
_021E9152:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E915E: ; jump table
	.short _021E916E - _021E915E - 2 ; case 0
	.short _021E9228 - _021E915E - 2 ; case 1
	.short _021E9242 - _021E915E - 2 ; case 2
	.short _021E924E - _021E915E - 2 ; case 3
	.short _021E92B2 - _021E915E - 2 ; case 4
	.short _021E931A - _021E915E - 2 ; case 5
	.short _021E93A6 - _021E915E - 2 ; case 6
	.short _021E9430 - _021E915E - 2 ; case 7
_021E916E:
	mov r1, #0x1e
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1e
	str r0, [r7, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, [r7, #0x10]
	ldr r4, [r7, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #7
	lsl r0, r0, #6
	str r1, [r4, r0]
	bl MOD05_021E3768
	str r0, [r4, #0x44]
	add r0, r4, #0
	add r0, #0x48
	mov r1, #2
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #5
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	ldr r0, _021E949C ; =0x000927C0
	mov r1, #0x61
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x48
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp, #0x14]
	add r6, r0, #0
	add r0, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0x48
	add r5, r4, #0
	str r0, [sp, #0x1c]
_021E91D4:
	mov r0, #0
	str r0, [sp]
	mov r1, #0x61
	str r0, [sp, #4]
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	ldr r0, [sp, #0x1c]
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x6e
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02020310
	ldr r0, [sp, #0x14]
	add r5, r5, #4
	add r0, r0, #1
	add r6, r6, #2
	str r0, [sp, #0x14]
	cmp r0, #2
	blt _021E91D4
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E9228:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r7, #4
	bl MOD05_021E3474
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E9242:
	ldr r1, [r7, #4]
	cmp r1, #0
	beq _021E9310
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E924E:
	mov r0, #0xa
	mov r2, #1
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0x29
	lsl r2, r2, #0xc
	mov r3, #2
	bl MOD05_021E3644
	ldr r1, [r4]
	add r0, sp, #0x50
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	mov r6, #0
	add r5, r4, #0
_021E9270:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0x50
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9270
	add r0, r4, #0
	ldr r2, _021E94A0 ; =0x0000FFFF
	add r0, #0x18
	mov r1, #0
	mov r3, #0xa
	bl MOD05_021E35B0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E92B2:
	add r0, r4, #0
	bl MOD05_021E36A4
	ldr r1, [r4]
	str r0, [sp, #0x18]
	add r0, sp, #0x50
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	mov r6, #0
	add r5, r4, #0
_021E92D2:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	add r1, sp, #0x50
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E92D2
	mov r0, #0x6e
	ldr r1, [r4, #0x18]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r1, #0x6f
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	ldr r2, [r4, #0x18]
	sub r1, #0xbc
	sub r1, r2, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_02020088
	ldr r0, [sp, #0x18]
	cmp r0, #1
	beq _021E9312
_021E9310:
	b _021E948A
_021E9312:
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E931A:
	mov r0, #0
	str r0, [sp]
	mov r0, #0xff
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	mov r0, #0xa
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	ldr r1, [r4, #0x44]
	add r0, r7, #0
	mov r2, #0x60
	mov r3, #6
	bl MOD05_021E37CC
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_02020130
	mov r0, #6
	str r0, [sp]
	add r0, r4, #0
	mov r2, #0xff
	mov r3, #0xa
	add r0, #0x2c
	mov r1, #0
	lsl r2, r2, #0xc
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #0x71
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E94A4 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E93A6:
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E36A4
	mov r1, #2
	ldr r2, [r4, #0x2c]
	lsl r1, r1, #0x12
	sub r1, r1, r2
	mov r2, #6
	add r0, sp, #0x2c
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x2c
	ldmia r3!, {r0, r1}
	add r2, sp, #0x44
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, #2
	str r0, [r2]
	ldr r2, [r4, #0x2c]
	lsl r1, r1, #0x12
	add r1, r2, r1
	mov r2, #6
	add r0, sp, #0x20
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x20
	ldmia r3!, {r0, r1}
	add r2, sp, #0x38
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x44
	str r0, [r2]
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x71
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x71
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	add r0, r7, #0
	bl MOD05_021E35AC
	cmp r0, #0
	beq _021E948A
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E948A
_021E9430:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, [r7, #0x14]
	cmp r1, #0
	beq _021E944A
	mov r0, #1
	str r0, [r1]
_021E944A:
	mov r6, #0
	add r5, r4, #0
_021E944E:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E944E
	mov r1, #0x61
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x48
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #0x48
	bl MOD05_021E3E44
	ldr r0, [r4, #0x44]
	bl MOD05_021E37A4
	ldr r1, [r7, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021E948A:
	ldr r0, [r7]
	cmp r0, #7
	beq _021E9496
	ldr r0, [r4, #0x48]
	bl FUN_0201FDEC
_021E9496:
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_021E949C: .word 0x000927C0
_021E94A0: .word 0x0000FFFF
_021E94A4: .word 0xFFFF6000

	thumb_func_start MOD05_021E94A8
MOD05_021E94A8: ; 0x021E94A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x78
	add r6, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r6]
	ldr r4, [r6, #0xc]
	cmp r0, #7
	bhi _021E95A2
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E94C4: ; jump table
	.short _021E94D4 - _021E94C4 - 2 ; case 0
	.short _021E9582 - _021E94C4 - 2 ; case 1
	.short _021E959C - _021E94C4 - 2 ; case 2
	.short _021E95AA - _021E94C4 - 2 ; case 3
	.short _021E9638 - _021E94C4 - 2 ; case 4
	.short _021E96C8 - _021E94C4 - 2 ; case 5
	.short _021E9702 - _021E94C4 - 2 ; case 6
	.short _021E972C - _021E94C4 - 2 ; case 7
_021E94D4:
	mov r1, #0x71
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x71
	str r0, [r6, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r0, [r6, #0x10]
	ldr r4, [r6, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #0x69
	lsl r0, r0, #2
	str r1, [r4, r0]
	bl MOD05_021E39FC
	str r0, [r4, #0x28]
	add r0, r4, #0
	add r0, #0x2c
	mov r1, #2
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021E9798 ; =0x000927C0
	mov r1, #0x5a
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	add r0, r4, #0
	str r0, [sp, #0x14]
	add r0, #0x2c
	mov r7, #0
	add r5, r4, #0
	str r0, [sp, #0x14]
_021E9536:
	mov r0, #0
	str r0, [sp]
	mov r1, #0x5a
	str r0, [sp, #4]
	lsl r1, r1, #2
	mov r2, #2
	ldr r0, [sp, #0x14]
	add r1, r4, r1
	lsl r2, r2, #0x12
	mov r3, #0
	bl MOD05_021E3FC4
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #2
	blt _021E9536
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E9582:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r6, #4
	bl MOD05_021E3474
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E959C:
	ldr r1, [r6, #4]
	cmp r1, #0
	bne _021E95A4
_021E95A2:
	b _021E9786
_021E95A4:
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E95AA:
	mov r2, #3
	ldr r1, _021E979C ; =0xFFF40000
	add r0, r4, #0
	lsl r2, r2, #0x12
	mov r3, #8
	bl MOD05_021E35EC
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r2, #2
	ldr r1, [r4]
	lsl r2, r2, #0x12
	sub r1, r2, r1
	add r0, sp, #0x3c
	lsr r2, r2, #1
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x3c
	ldmia r3!, {r0, r1}
	add r2, sp, #0x6c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r3, #0
	str r0, [r2]
	mov r2, #2
	ldr r1, [r4]
	lsl r2, r2, #0x12
	add r0, sp, #0x30
	add r1, r1, r2
	bl MOD05_021E3FF8
	add r3, sp, #0x30
	ldmia r3!, {r0, r1}
	add r2, sp, #0x60
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x6c
	str r0, [r2]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x60
	bl FUN_02020044
	add r0, r4, #0
	ldr r2, _021E97A0 ; =0x0001FFFE
	add r0, #0x14
	mov r1, #0
	mov r3, #8
	bl MOD05_021E35B0
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E9638:
	add r0, r4, #0
	bl MOD05_021E35FC
	mov r2, #2
	add r5, r0, #0
	ldr r1, [r4]
	lsl r2, r2, #0x12
	sub r1, r2, r1
	add r0, sp, #0x24
	lsr r2, r2, #1
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x24
	ldmia r3!, {r0, r1}
	add r2, sp, #0x54
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r3, #0
	str r0, [r2]
	mov r2, #2
	ldr r1, [r4]
	lsl r2, r2, #0x12
	add r0, sp, #0x18
	add r1, r1, r2
	bl MOD05_021E3FF8
	add r3, sp, #0x18
	ldmia r3!, {r0, r1}
	add r2, sp, #0x48
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, sp, #0x54
	str r0, [r2]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x48
	bl FUN_02020044
	add r0, r4, #0
	add r0, #0x14
	bl MOD05_021E35C0
	mov r0, #0x67
	ldr r1, [r4, #0x14]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	ldr r1, [r4, #0x14]
	mov r0, #0x1a
	lsl r0, r0, #4
	neg r1, r1
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	cmp r5, #1
	bne _021E9786
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E96C8:
	mov r3, #1
	lsl r3, r3, #0xc
	str r3, [sp]
	ldr r1, [r4, #0x28]
	add r0, r6, #0
	mov r2, #8
	bl MOD05_021E3A70
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0x6a
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E97A4 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E9702:
	mov r0, #0x6a
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x6a
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	add r0, r6, #0
	bl MOD05_021E35AC
	cmp r0, #1
	bne _021E9786
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021E9786
_021E972C:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, [r6, #0x14]
	cmp r1, #0
	beq _021E9746
	mov r0, #1
	str r0, [r1]
_021E9746:
	mov r7, #0
	add r5, r4, #0
_021E974A:
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #2
	blt _021E974A
	mov r1, #0x5a
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E3E44
	ldr r0, [r4, #0x28]
	bl MOD05_021E3A48
	ldr r1, [r6, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021E9786:
	ldr r0, [r6]
	cmp r0, #7
	beq _021E9792
	ldr r0, [r4, #0x2c]
	bl FUN_0201FDEC
_021E9792:
	add sp, #0x78
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E9798: .word 0x000927C0
_021E979C: .word 0xFFF40000
_021E97A0: .word 0x0001FFFE
_021E97A4: .word 0xFFFF6000

	thumb_func_start MOD05_021E97A8
MOD05_021E97A8: ; 0x021E97A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	add r7, r1, #0
	str r0, [sp, #0x14]
	ldr r0, [r7]
	ldr r4, [r7, #0xc]
	cmp r0, #7
	bls _021E97BA
	b _021E9B2A
_021E97BA:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E97C6: ; jump table
	.short _021E97D6 - _021E97C6 - 2 ; case 0
	.short _021E9892 - _021E97C6 - 2 ; case 1
	.short _021E98AC - _021E97C6 - 2 ; case 2
	.short _021E98F2 - _021E97C6 - 2 ; case 3
	.short _021E9958 - _021E97C6 - 2 ; case 4
	.short _021E99E4 - _021E97C6 - 2 ; case 5
	.short _021E9A68 - _021E97C6 - 2 ; case 6
	.short _021E9AD0 - _021E97C6 - 2 ; case 7
_021E97D6:
	mov r1, #0x7a
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x7a
	str r0, [r7, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r0, [r7, #0x10]
	ldr r4, [r7, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #0x72
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x40
	mov r1, #4
	bl MOD05_021E8E8C
	mov r0, #0x79
	mov r1, #0xc
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	add r0, #0x50
	mov r1, #2
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #5
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	ldr r0, _021E9B4C ; =0x000927C0
	mov r1, #0x63
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x50
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	add r0, r4, #0
	str r0, [sp, #0x1c]
	add r0, #0x50
	mov r6, #0
	add r5, r4, #0
	str r0, [sp, #0x1c]
_021E9844:
	mov r0, #0
	str r0, [sp]
	mov r1, #0x63
	str r0, [sp, #4]
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	ldr r0, [sp, #0x1c]
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #7
	lsl r1, r1, #6
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	add r1, r6, #0
	bl FUN_02020310
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9844
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9892:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r7, #4
	bl MOD05_021E3474
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E98AC:
	mov r0, #0x79
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021E98E4
	mov r0, #3
	lsl r0, r0, #0xe
	mov r3, #0x32
	str r0, [sp]
	lsl r3, r3, #4
	str r3, [sp, #4]
	ldr r0, _021E9B50 ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r4, #0
	add r0, #0x40
	mov r2, #0xbf
	sub r3, #0x76
	bl MOD05_021E8EC0
	mov r0, #1
	str r0, [r4, #0x4c]
_021E98E4:
	ldr r0, [r7, #4]
	cmp r0, #0
	beq _021E99BE
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E98F2:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	mov r2, #0x10
	mov r3, #8
	bl MOD05_021E35B0
	ldr r3, [r4, #0x18]
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021E9B54 ; =0x04000050
	mov r1, #0
	mov r2, #0xf
	bl G2x_SetBlendAlpha_
	mov r6, #0
	add r5, r4, #0
_021E9916:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020398
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9916
	add r0, r4, #0
	ldr r2, _021E9B58 ; =0x0000FFFF
	add r0, #0x2c
	mov r1, #0
	mov r3, #8
	bl MOD05_021E35B0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9958:
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	add r6, r0, #0
	ldr r1, [r4, #0x18]
	mov r0, #0x10
	sub r0, r0, r1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _021E9B5C ; =0x04000052
	strh r1, [r0]
	ldr r0, [r4, #0x2c]
	lsl r0, r0, #0x10
	lsr r5, r0, #0x10
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E35C0
	cmp r0, #0
	bne _021E99A2
	mov r0, #7
	ldr r1, [r4, #0x2c]
	lsl r0, r0, #6
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r0, #0x71
	lsl r0, r0, #2
	lsl r1, r5, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	b _021E99BA
_021E99A2:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020088
_021E99BA:
	cmp r6, #1
	beq _021E99C0
_021E99BE:
	b _021E9B2A
_021E99C0:
	ldr r0, _021E9B54 ; =0x04000050
	mov r6, #0
	strh r6, [r0]
	add r5, r4, #0
_021E99C8:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_02020398
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E99C8
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E99E4:
	mov r1, #8
	str r1, [sp]
	ldr r3, _021E9B60 ; =0x0000019A
	add r0, r4, #0
	lsl r1, r1, #9
	mov r2, #0x29
	bl MOD05_021E3644
	ldr r1, [r4]
	add r0, sp, #0x34
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x34
	add r2, sp, #0x4c
	ldmia r3!, {r0, r1}
	str r2, [sp, #0x20]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r6, #0
	str r0, [r2]
	add r5, r4, #0
_021E9A12:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x20]
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9A12
	mov r0, #0x72
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0x73
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E9B64 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x18
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9A68:
	add r0, r4, #0
	bl MOD05_021E36A4
	ldr r1, [r4]
	str r0, [sp, #0x18]
	add r0, sp, #0x28
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x28
	add r2, sp, #0x40
	ldmia r3!, {r0, r1}
	str r2, [sp, #0x24]
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r6, #0
	str r0, [r2]
	add r5, r4, #0
_021E9A8E:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	ldr r1, [sp, #0x24]
	bl FUN_02020064
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9A8E
	mov r0, #0x73
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x73
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	ldr r0, [sp, #0x18]
	cmp r0, #1
	bne _021E9B2A
	bl FUN_0200E308
	cmp r0, #1
	bne _021E9B2A
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	b _021E9B2A
_021E9AD0:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r1, [r7, #0x14]
	cmp r1, #0
	beq _021E9AE2
	mov r0, #1
	str r0, [r1]
_021E9AE2:
	add r0, r4, #0
	add r0, #0x40
	bl MOD05_021E8EA8
	mov r6, #0
	str r6, [r4, #0x4c]
	add r5, r4, #0
_021E9AF0:
	mov r0, #7
	lsl r0, r0, #6
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #2
	blt _021E9AF0
	mov r1, #0x63
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x50
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r4, #0x50
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [r7, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x14]
	bl FUN_0200621C
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
_021E9B2A:
	ldr r0, [r4, #0x4c]
	cmp r0, #1
	bne _021E9B3A
	add r0, r4, #0
	add r0, #0x40
	mov r1, #2
	bl MOD05_021E8EE8
_021E9B3A:
	ldr r0, [r7]
	cmp r0, #7
	beq _021E9B46
	ldr r0, [r4, #0x50]
	bl FUN_0201FDEC
_021E9B46:
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E9B4C: .word 0x000927C0
_021E9B50: .word 0x04000010
_021E9B54: .word 0x04000050
_021E9B58: .word 0x0000FFFF
_021E9B5C: .word 0x04000052
_021E9B60: .word 0x0000019A
_021E9B64: .word 0xFFFF6000

	thumb_func_start MOD05_021E9B68
MOD05_021E9B68: ; 0x021E9B68
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #0x18]
	add r0, r1, #0
	ldr r0, [r0]
	str r1, [sp, #0x1c]
	ldr r4, [r1, #0xc]
	cmp r0, #7
	bls _021E9B7C
	b _021EA01A
_021E9B7C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E9B88: ; jump table
	.short _021E9B98 - _021E9B88 - 2 ; case 0
	.short _021E9CAA - _021E9B88 - 2 ; case 1
	.short _021E9CCA - _021E9B88 - 2 ; case 2
	.short _021E9D24 - _021E9B88 - 2 ; case 3
	.short _021E9DE4 - _021E9B88 - 2 ; case 4
	.short _021E9E82 - _021E9B88 - 2 ; case 5
	.short _021E9F1C - _021E9B88 - 2 ; case 6
	.short _021E9F70 - _021E9B88 - 2 ; case 7
_021E9B98:
	mov r1, #9
	mov r0, #4
	lsl r1, r1, #6
	bl AllocFromHeap
	ldr r1, [sp, #0x1c]
	mov r2, #9
	str r0, [r1, #0xc]
	mov r1, #0
	lsl r2, r2, #6
	bl memset
	ldr r0, [sp, #0x1c]
	ldr r4, [r0, #0xc]
	ldr r0, [r0, #0x10]
	ldr r1, [r0, #0x20]
	mov r0, #0x22
	lsl r0, r0, #4
	str r1, [r4, r0]
	sub r0, #0x10
	add r0, r4, r0
	mov r1, #4
	bl MOD05_021E8E8C
	mov r0, #0x8f
	mov r1, #0xe
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #3
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021E9F5C ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0x4f
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_021E9C02:
	mov r0, #0
	str r0, [sp]
	mov r2, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r7
	add r3, r2, #0
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #4
	bl MOD05_021E4140
	mov r1, #0x7d
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021E9C02
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	mov r1, #0x83
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [sp, #0x1c]
	ldr r1, [r4, r1]
	ldr r0, [r0, #0x10]
	mov r2, #3
	ldr r0, [r0, #8]
	bl AddWindowParameterized
	mov r1, #0
	add r0, sp, #0x28
	strh r1, [r0]
	mov r0, #3
	add r1, sp, #0x28
	mov r2, #2
	mov r3, #0x1e
	bl BG_LoadPlttData
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ScheduleWindowCopyToVram
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9CAA:
	mov r1, #0x10
	ldr r3, [sp, #0x1c]
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r3, #4
	bl MOD05_021E3474
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9CCA:
	mov r3, #0x8f
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	sub r0, r0, #1
	str r0, [r4, r3]
	ldr r0, [r4, r3]
	cmp r0, #0
	bne _021E9D08
	mov r0, #3
	lsl r0, r0, #0xe
	str r0, [sp]
	add r0, r3, #0
	add r0, #0xe4
	str r0, [sp, #4]
	ldr r0, _021E9F60 ; =0x04000010
	mov r1, #0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	mov r0, #4
	str r0, [sp, #0x10]
	add r0, r3, #0
	sub r0, #0x2c
	add r0, r4, r0
	mov r2, #0xbf
	add r3, #0x6e
	bl MOD05_021E8EC0
	mov r0, #0x87
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
_021E9D08:
	ldr r0, [sp, #0x1c]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _021E9D34
	mov r0, #0x8f
	mov r1, #6
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9D24:
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	blt _021E9D36
_021E9D34:
	b _021EA01A
_021E9D36:
	sub r0, #0x1c
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x89
	mov r2, #0x7d
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	ldr r3, _021E9F64 ; =0xFFFF6000
	add r0, r4, r0
	sub r2, r1, r2
	bl MOD05_021E3644
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r2, _021E9F68 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0x5f
	lsl r0, r0, #2
	mov r2, #0x1f
	add r0, r4, r0
	mov r1, #0xe7
	mvn r2, r2
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	mov r3, #0x40
	str r1, [sp, #8]
	mov r1, #0x56
	str r1, [sp, #0xc]
	str r3, [sp, #0x10]
	mov r1, #0xf
	str r1, [sp, #0x14]
	sub r0, #0x18
	mov r1, #0x2b
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, #0xf8
	bl MOD05_021E4160
	mov r1, #0x2b
	mov r2, #0xe7
	add r0, sp, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #1
	lsl r0, r1, #9
	str r1, [r4, r0]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	mov r0, #0x8f
	mov r1, #4
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EA01A
_021E9DE4:
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	bge _021E9E92
	sub r0, #0xac
	mov r2, #0x1f
	add r0, r4, r0
	mov r1, #0xe7
	mvn r2, r2
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r2, _021E9F6C ; =0xFFFF0001
	add r0, r4, r0
	mov r1, #0
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r0, #0x14
	str r1, [sp, #8]
	mov r1, #0x56
	str r1, [sp, #0xc]
	mov r1, #0x40
	str r1, [sp, #0x10]
	mov r1, #0xf
	str r1, [sp, #0x14]
	mov r1, #0xd7
	add r3, r1, #0
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, #0x61
	bl MOD05_021E4160
	mov r1, #0xd7
	mov r2, #0xe7
	add r0, sp, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	mov r3, #1
	bl MOD05_021E3FF8
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #0x81
	mov r0, #1
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x1c]
	add r1, #0x38
	ldr r0, [r0]
	add r2, r0, #1
	ldr r0, [sp, #0x1c]
	str r2, [r0]
	mov r0, #2
	str r0, [r4, r1]
	b _021EA01A
_021E9E82:
	mov r0, #0x8f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	blt _021E9E94
_021E9E92:
	b _021EA01A
_021E9E94:
	sub r0, #0x98
	mov r2, #0x1f
	add r0, r4, r0
	mov r1, #0xe7
	mvn r2, r2
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r2, _021E9F68 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #6
	bl MOD05_021E35B0
	mov r0, #0
	str r0, [sp]
	mov r0, #6
	str r0, [sp, #4]
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r0, #0x10
	str r1, [sp, #8]
	mov r1, #0x56
	str r1, [sp, #0xc]
	mov r1, #0x40
	str r1, [sp, #0x10]
	mov r1, #0xf
	str r1, [sp, #0x14]
	mov r1, #0x81
	add r3, r1, #0
	ldr r0, [r4, r0]
	add r2, r1, #0
	add r3, #0xb7
	bl MOD05_021E4160
	mov r1, #0x81
	mov r2, #0xe7
	add r0, sp, #0x38
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	mov r3, #2
	bl MOD05_021E3FF8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x82
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
_021E9F1C:
	mov r0, #0x89
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x89
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	mov r1, #2
	lsl r1, r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021EA01A
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021EA01A
	add r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021EA01A
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [r0]
	b _021EA01A
	nop
_021E9F5C: .word 0x000927C0
_021E9F60: .word 0x04000010
_021E9F64: .word 0xFFFF6000
_021E9F68: .word 0x0000FFFF
_021E9F6C: .word 0xFFFF0001
_021E9F70:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [sp, #0x1c]
	ldr r1, [r0, #0x14]
	cmp r1, #0
	beq _021E9F8C
	mov r0, #1
	str r0, [r1]
_021E9F8C:
	mov r0, #0x21
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E8EA8
	mov r0, #0x87
	lsl r0, r0, #2
	mov r6, #0
	add r7, r0, #0
	str r6, [r4, r0]
	add r5, r4, #0
	sub r7, #0x28
_021E9FA4:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	ldr r0, [r5, r7]
	bl MOD05_021E4158
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021E9FA4
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ClearWindowTilemapAndCopyToVram
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl RemoveWindow
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl WindowArray_Delete
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl BG_ClearCharDataRange
	ldr r0, [sp, #0x1c]
	mov r1, #3
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #8]
	bl BgClearTilemapBufferAndCommit
	ldr r1, [sp, #0x1c]
	mov r0, #4
	ldr r1, [r1, #0xc]
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x18]
	bl FUN_0200621C
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
_021EA01A:
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #1
	bne _021EA02E
	sub r0, #0xc
	add r0, r4, r0
	mov r1, #2
	bl MOD05_021E8EE8
_021EA02E:
	mov r1, #0x5f
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #0x20]
	add r0, r4, r1
	add r1, #0x3c
	add r5, r4, #0
	str r0, [sp, #0x24]
	add r7, r4, r1
	add r6, r4, #0
_021EA042:
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _021EA0B0
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl MOD05_021E41B8
	cmp r0, #0
	beq _021EA062
	mov r0, #2
	mov r1, #0
	lsl r0, r0, #8
	str r1, [r5, r0]
_021EA062:
	ldr r0, [sp, #0x24]
	bl MOD05_021E35C0
	add r0, r7, #0
	bl MOD05_021E35C0
	mov r1, #0x6e
	lsl r1, r1, #2
	mov r0, #0x17
	ldr r1, [r6, r1]
	lsl r0, r0, #4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0x2c
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, ip
	str r0, [r2]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02020044
_021EA0B0:
	ldr r0, [sp, #0x24]
	add r5, r5, #4
	add r0, #0x14
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	str r0, [sp, #0x20]
	cmp r0, #3
	blt _021EA042
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ScheduleWindowCopyToVram
	ldr r0, [sp, #0x1c]
	ldr r0, [r0]
	cmp r0, #7
	beq _021EA0DE
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EA0DE:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EA0E4
MOD05_021EA0E4: ; 0x021EA0E4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r4, [r5, #0xc]
	cmp r0, #7
	bhi _021EA1B8
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EA100: ; jump table
	.short _021EA110 - _021EA100 - 2 ; case 0
	.short _021EA198 - _021EA100 - 2 ; case 1
	.short _021EA1B2 - _021EA100 - 2 ; case 2
	.short _021EA1C0 - _021EA100 - 2 ; case 3
	.short _021EA236 - _021EA100 - 2 ; case 4
	.short _021EA2C2 - _021EA100 - 2 ; case 5
	.short _021EA310 - _021EA100 - 2 ; case 6
	.short _021EA338 - _021EA100 - 2 ; case 7
_021EA110:
	mov r1, #0x1f
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1f
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, [r5, #0x10]
	ldr r4, [r5, #0xc]
	ldr r1, [r0, #0x20]
	mov r0, #0x1d
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	add r0, #0x5c
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EA394 ; =0x000927C0
	mov r1, #0x66
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x5c
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #0x66
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #2
	ldr r3, _021EA398 ; =0xFFFE0000
	add r0, #0x5c
	add r1, r4, r1
	lsl r2, r2, #0x12
	bl MOD05_021E3FC4
	mov r1, #0x73
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA198:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA1B2:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021EA1BA
_021EA1B8:
	b _021EA382
_021EA1BA:
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA1C0:
	mov r2, #1
	mov r0, #0xc
	lsl r2, r2, #0x14
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	lsr r3, r2, #7
	bl MOD05_021E3644
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	mov r2, #2
	ldr r1, _021EA39C ; =0x0000019A
	add r0, #0x18
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3644
	mov r0, #0xc
	str r0, [sp]
	add r0, r4, #0
	mov r2, #2
	ldr r1, _021EA39C ; =0x0000019A
	add r0, #0x30
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3644
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x30]
	add r0, sp, #0x28
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x28
	mov r2, #2
	bl FUN_02020074
	add r0, r4, #0
	ldr r2, _021EA3A0 ; =0x0000FFFF
	add r0, #0x48
	mov r1, #0
	mov r3, #0xc
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA236:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r1, #2
	lsl r1, r1, #0x12
	add r6, r0, #0
	ldr r3, [r4]
	lsr r2, r1, #2
	sub r2, r3, r2
	add r0, sp, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x10
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r7, #0
	str r0, [r2]
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02020044
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E36A4
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E36A4
	ldr r1, [r4, #0x18]
	ldr r2, [r4, #0x30]
	add r0, sp, #0x28
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x28
	bl FUN_02020064
	add r0, r4, #0
	add r0, #0x48
	bl MOD05_021E35C0
	mov r0, #0x73
	ldr r1, [r4, #0x48]
	lsl r0, r0, #2
	lsl r1, r1, #0x10
	ldr r0, [r4, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
	cmp r6, #1
	bne _021EA382
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA2C2:
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0x1d
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #8
	str r0, [sp]
	mov r0, #0x75
	mov r2, #0xfa
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	mov r3, #0xa
	add r0, r4, r0
	sub r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x12
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA310:
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x75
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	bl FUN_0200E308
	cmp r0, #0
	beq _021EA382
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EA382
_021EA338:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EA354
	mov r0, #1
	str r0, [r1]
_021EA354:
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r1, #0x66
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x5c
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #0x5c
	bl MOD05_021E3E44
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021EA382:
	ldr r0, [r5]
	cmp r0, #7
	beq _021EA38E
	ldr r0, [r4, #0x5c]
	bl FUN_0201FDEC
_021EA38E:
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021EA394: .word 0x000927C0
_021EA398: .word 0xFFFE0000
_021EA39C: .word 0x0000019A
_021EA3A0: .word 0x0000FFFF

	thumb_func_start MOD05_021EA3A4
MOD05_021EA3A4: ; 0x021EA3A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #0x14]
	add r0, r1, #0
	ldr r0, [r0]
	str r1, [sp, #0x18]
	ldr r4, [r1, #0xc]
	cmp r0, #9
	bls _021EA3B8
	b _021EA7DE
_021EA3B8:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EA3C4: ; jump table
	.short _021EA3D8 - _021EA3C4 - 2 ; case 0
	.short _021EA4CE - _021EA3C4 - 2 ; case 1
	.short _021EA4EE - _021EA3C4 - 2 ; case 2
	.short _021EA506 - _021EA3C4 - 2 ; case 3
	.short _021EA582 - _021EA3C4 - 2 ; case 4
	.short _021EA5FE - _021EA3C4 - 2 ; case 5
	.short _021EA674 - _021EA3C4 - 2 ; case 6
	.short _021EA6B4 - _021EA3C4 - 2 ; case 7
	.short _021EA6FA - _021EA3C4 - 2 ; case 8
	.short _021EA748 - _021EA3C4 - 2 ; case 9
_021EA3D8:
	mov r1, #0x8a
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	ldr r1, [sp, #0x18]
	mov r2, #0x8a
	str r0, [r1, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r0, [sp, #0x18]
	mov r2, #1
	ldr r4, [r0, #0xc]
	ldr r0, [r0, #0x10]
	ldr r1, [r0, #0x20]
	mov r0, #0x82
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r4, #0
	mov r1, #3
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EA738 ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0x4f
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_021EA430:
	mov r0, #0
	mov r2, #0
	str r0, [sp]
	add r3, r2, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r7
	sub r3, #0x20
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021EA430
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	mov r1, #2
	lsl r1, r1, #8
	str r0, [r4, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [sp, #0x18]
	ldr r1, [r4, r1]
	ldr r0, [r0, #0x10]
	mov r2, #3
	ldr r0, [r0, #8]
	bl AddWindowParameterized
	mov r1, #0
	add r0, sp, #0x28
	strh r1, [r0]
	mov r0, #3
	add r1, sp, #0x28
	mov r2, #2
	mov r3, #0x1e
	bl BG_LoadPlttData
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl ScheduleWindowCopyToVram
	mov r0, #4
	bl MOD05_021E4394
	mov r1, #0x81
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA4CE:
	mov r1, #0x10
	ldr r3, [sp, #0x18]
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r3, #4
	bl MOD05_021E3474
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA4EE:
	ldr r1, [sp, #0x18]
	ldr r1, [r1, #4]
	cmp r1, #0
	beq _021EA516
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	mov r0, #0x89
	mov r1, #0
	lsl r0, r0, #2
	strh r1, [r4, r0]
	b _021EA7DE
_021EA506:
	mov r0, #0x89
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldrsh r1, [r4, r0]
	cmp r1, #0
	ble _021EA518
_021EA516:
	b _021EA7DE
_021EA518:
	sub r0, #0xa8
	mov r1, #0x1f
	add r0, r4, r0
	mvn r1, r1
	mov r2, #0xe0
	mov r3, #5
	bl MOD05_021E35B0
	mov r1, #2
	ldr r2, _021EA73C ; =0xFFFE0000
	add r0, sp, #0x38
	lsl r1, r1, #0x12
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r2, _021EA740 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #5
	bl MOD05_021E35B0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r1, #0x7d
	mov r3, #1
	lsl r1, r1, #2
	str r3, [r4, r1]
	ldr r0, [sp, #0x18]
	add r1, #0x30
	ldr r0, [r0]
	add r2, r0, #1
	ldr r0, [sp, #0x18]
	str r2, [r0]
	strh r3, [r4, r1]
	b _021EA7DE
_021EA582:
	mov r0, #0x89
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldrsh r1, [r4, r0]
	cmp r1, #0
	bgt _021EA68E
	sub r0, #0x94
	mov r1, #0x1f
	add r0, r4, r0
	mvn r1, r1
	mov r2, #0xe0
	mov r3, #5
	bl MOD05_021E35B0
	mov r1, #0xd
	ldr r2, _021EA73C ; =0xFFFE0000
	add r0, sp, #0x38
	lsl r1, r1, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x73
	lsl r0, r0, #2
	ldr r2, _021EA744 ; =0xFFFF0001
	add r0, r4, r0
	mov r1, #0
	mov r3, #5
	bl MOD05_021E35B0
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r1, #0x7e
	mov r0, #1
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [sp, #0x18]
	add r1, #0x2c
	ldr r0, [r0]
	add r2, r0, #1
	ldr r0, [sp, #0x18]
	str r2, [r0]
	mov r0, #3
	strh r0, [r4, r1]
	b _021EA7DE
_021EA5FE:
	mov r0, #0x89
	lsl r0, r0, #2
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, r0]
	ldrsh r1, [r4, r0]
	cmp r1, #0
	bgt _021EA68E
	sub r0, #0x80
	mov r1, #0x1f
	add r0, r4, r0
	mvn r1, r1
	mov r2, #0xe0
	mov r3, #5
	bl MOD05_021E35B0
	mov r1, #3
	ldr r2, _021EA73C ; =0xFFFE0000
	add r0, sp, #0x38
	lsl r1, r1, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x38
	bl FUN_02020044
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x1e
	lsl r0, r0, #4
	ldr r2, _021EA740 ; =0x0000FFFF
	add r0, r4, r0
	mov r1, #0
	mov r3, #5
	bl MOD05_021E35B0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x7f
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA674:
	mov r1, #0x7d
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	cmp r0, #0
	bne _021EA68E
	add r0, r1, #4
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _021EA68E
	add r1, #8
	ldr r0, [r4, r1]
	cmp r0, #0
	beq _021EA690
_021EA68E:
	b _021EA7DE
_021EA690:
	mov r7, #0x17
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_021EA698:
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021EA698
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA6B4:
	mov r0, #0xf
	mov r1, #1
	str r0, [sp]
	mov r0, #0x81
	lsl r0, r0, #2
	lsl r3, r1, #9
	ldr r0, [r4, r0]
	ldr r3, [r4, r3]
	add r2, r1, #0
	bl MOD05_021E43E4
	mov r0, #0x82
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #0x40
	str r0, [sp]
	mov r0, #0x83
	mov r2, #0xfa
	lsl r0, r0, #2
	lsl r2, r2, #0xe
	mov r3, #0xa
	add r0, r4, r0
	sub r2, r1, r2
	lsl r3, r3, #0xc
	bl MOD05_021E3644
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
_021EA6FA:
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD05_021E4424
	add r5, r0, #0
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl ScheduleWindowCopyToVram
	mov r0, #0x83
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E36A4
	mov r1, #0x83
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	cmp r5, #1
	bne _021EA7DE
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x18]
	str r1, [r0]
	b _021EA7DE
	.balign 4, 0
_021EA738: .word 0x000927C0
_021EA73C: .word 0xFFFE0000
_021EA740: .word 0x0000FFFF
_021EA744: .word 0xFFFF0001
_021EA748:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [sp, #0x18]
	ldr r1, [r0, #0x14]
	cmp r1, #0
	beq _021EA764
	mov r0, #1
	str r0, [r1]
_021EA764:
	mov r7, #0x17
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_021EA76C:
	ldr r0, [r5, r7]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #3
	blt _021EA76C
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	mov r0, #0x81
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl MOD05_021E43C4
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl ClearWindowTilemapAndCopyToVram
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	bl RemoveWindow
	mov r0, #2
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	mov r1, #1
	bl WindowArray_Delete
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl BG_ClearCharDataRange
	ldr r0, [sp, #0x18]
	mov r1, #3
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #8]
	bl BgClearTilemapBufferAndCommit
	ldr r1, [sp, #0x18]
	mov r0, #4
	ldr r1, [r1, #0xc]
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x14]
	bl FUN_0200621C
_021EA7DE:
	mov r1, #0x5f
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #0x1c]
	add r0, r4, r1
	add r1, #0x3c
	add r5, r4, #0
	str r0, [sp, #0x20]
	add r7, r4, r1
	add r6, r4, #0
_021EA7F2:
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _021EA85A
	ldr r0, [sp, #0x20]
	bl MOD05_021E35C0
	str r0, [sp, #0x24]
	add r0, r7, #0
	bl MOD05_021E35C0
	ldr r0, [sp, #0x24]
	cmp r0, #0
	beq _021EA818
	mov r0, #0x7d
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_021EA818:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0202011C
	add r3, r0, #0
	add r2, sp, #0x2c
	ldmia r3!, {r0, r1}
	mov ip, r2
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	mov r1, ip
	str r0, [r2]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0x30]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_02020044
	mov r1, #0x6e
	lsl r1, r1, #2
	mov r0, #0x17
	ldr r1, [r6, r1]
	lsl r0, r0, #4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
_021EA85A:
	ldr r0, [sp, #0x20]
	add r5, r5, #4
	add r0, #0x14
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r7, #0x14
	add r0, r0, #1
	add r6, #0x14
	str r0, [sp, #0x1c]
	cmp r0, #3
	blt _021EA7F2
	ldr r0, [sp, #0x18]
	ldr r0, [r0]
	cmp r0, #9
	beq _021EA87E
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EA87E:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EA884
MOD05_021EA884: ; 0x021EA884
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #7
	bls _021EA896
	b _021EAAC6
_021EA896:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EA8A2: ; jump table
	.short _021EA8B2 - _021EA8A2 - 2 ; case 0
	.short _021EA93E - _021EA8A2 - 2 ; case 1
	.short _021EA958 - _021EA8A2 - 2 ; case 2
	.short _021EA964 - _021EA8A2 - 2 ; case 3
	.short _021EA996 - _021EA8A2 - 2 ; case 4
	.short _021EA9C8 - _021EA8A2 - 2 ; case 5
	.short _021EAA38 - _021EA8A2 - 2 ; case 6
	.short _021EAA7C - _021EA8A2 - 2 ; case 7
_021EA8B2:
	mov r1, #0x69
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x69
	str r0, [r4, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r5, [r4, #0xc]
	mov r1, #1
	add r0, r5, #0
	add r0, #0x2c
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #5
	str r0, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #6
	str r0, [sp, #8]
	ldr r0, _021EAAD8 ; =0x000927C0
	mov r1, #0x5a
	str r0, [sp, #0xc]
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r5, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #0x5a
	str r0, [sp, #4]
	add r0, r5, #0
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	add r0, #0x2c
	add r1, r5, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020398
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA93E:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA958:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021EA9AE
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA964:
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x10
	mov r3, #0xc
	bl MOD05_021E35B0
	ldr r3, [r5]
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021EAADC ; =0x04000050
	mov r1, #0
	mov r2, #0xf
	bl G2x_SetBlendAlpha_
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA996:
	add r0, r5, #0
	bl MOD05_021E35C0
	ldr r2, [r5]
	mov r1, #0x10
	sub r1, r1, r2
	lsl r1, r1, #8
	orr r1, r2
	ldr r2, _021EAAE0 ; =0x04000052
	cmp r0, #1
	strh r1, [r2]
	beq _021EA9B0
_021EA9AE:
	b _021EAAC6
_021EA9B0:
	mov r1, #0
	sub r0, r2, #2
	strh r1, [r0]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02020398
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EA9C8:
	mov r0, #6
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	ldr r2, _021EAAE4 ; =0x0000019A
	add r0, #0x14
	lsl r1, r1, #0xc
	mov r3, #1
	bl MOD05_021E3644
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #2
	bl FUN_020200EC
	ldr r1, [r5, #0x14]
	add r0, sp, #0x1c
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r6, sp, #0x1c
	add r3, sp, #0x34
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02020064
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x10
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EAA38:
	add r0, r5, #0
	add r0, #0x14
	bl MOD05_021E36A4
	ldr r1, [r5, #0x14]
	add r6, r0, #0
	add r0, sp, #0x10
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E3FF8
	add r3, sp, #0x10
	add r2, sp, #0x28
	ldmia r3!, {r0, r1}
	add r7, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r7, #0
	str r0, [r2]
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_02020064
	cmp r6, #1
	bne _021EAAC6
	bl FUN_0200E308
	cmp r0, #1
	bne _021EAAC6
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021EAAC6
_021EAA7C:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021EAA98
	mov r0, #1
	str r0, [r1]
_021EAA98:
	mov r0, #0x67
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	mov r1, #0x5a
	add r0, r5, #0
	lsl r1, r1, #2
	add r0, #0x2c
	add r1, r5, r1
	bl MOD05_021E3F3C
	add r0, r5, #0
	add r0, #0x2c
	bl MOD05_021E3E44
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021EAAC6:
	ldr r0, [r4]
	cmp r0, #7
	beq _021EAAD2
	ldr r0, [r5, #0x2c]
	bl FUN_0201FDEC
_021EAAD2:
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EAAD8: .word 0x000927C0
_021EAADC: .word 0x04000050
_021EAAE0: .word 0x04000052
_021EAAE4: .word 0x0000019A

	thumb_func_start MOD05_021EAAE8
MOD05_021EAAE8: ; 0x021EAAE8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r6, r1, #0
	str r0, [sp, #0x10]
	ldr r0, [r6]
	ldr r4, [r6, #0xc]
	cmp r0, #7
	bhi _021EABBC
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EAB04: ; jump table
	.short _021EAB14 - _021EAB04 - 2 ; case 0
	.short _021EAB9C - _021EAB04 - 2 ; case 1
	.short _021EABB6 - _021EAB04 - 2 ; case 2
	.short _021EABC4 - _021EAB04 - 2 ; case 3
	.short _021EAC0E - _021EAB04 - 2 ; case 4
	.short _021EACC0 - _021EAB04 - 2 ; case 5
	.short _021EACEA - _021EAB04 - 2 ; case 6
	.short _021EACFA - _021EAB04 - 2 ; case 7
_021EAB14:
	mov r1, #0x1b
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1b
	str r0, [r6, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r4, [r6, #0xc]
	mov r1, #4
	add r0, r4, #0
	mov r2, #1
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EAD5C ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0
	add r5, r4, #0
_021EAB5A:
	mov r0, #0
	mov r1, #0x4f
	str r0, [sp]
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _021EAB5A
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EAB9C:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r6, #4
	bl MOD05_021E3474
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EABB6:
	ldr r1, [r6, #4]
	cmp r1, #0
	bne _021EABBE
_021EABBC:
	b _021EAD4C
_021EABBE:
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EABC4:
	mov r3, #6
	mov r2, #4
	lsl r3, r3, #6
	str r2, [sp]
	add r0, r4, r3
	mov r1, #0
	lsl r2, r2, #0x11
	add r3, #0x1a
	bl MOD05_021E3644
	mov r3, #0x66
	mov r0, #4
	mov r2, #0xa
	lsl r3, r3, #2
	str r0, [sp]
	add r0, r4, r3
	mov r1, #0
	lsl r2, r2, #0x10
	add r3, r3, #2
	bl MOD05_021E3644
	mov r7, #0
	add r5, r4, #0
_021EABF2:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200A0
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _021EABF2
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EAC0E:
	mov r0, #6
	lsl r0, r0, #6
	mov r7, #0
	add r5, r4, r0
_021EAC16:
	add r0, r5, #0
	bl MOD05_021E36A4
	add r7, r7, #1
	add r5, #0x18
	str r0, [sp, #0x14]
	cmp r7, #2
	blt _021EAC16
	mov r2, #6
	lsl r2, r2, #6
	ldr r3, [r4, r2]
	mov r1, #2
	lsl r2, r2, #0xa
	sub r2, r2, r3
	add r0, sp, #0x18
	lsl r1, r1, #0x12
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	mov r2, #6
	lsl r2, r2, #6
	ldr r3, [r4, r2]
	mov r1, #2
	lsl r2, r2, #0xa
	add r2, r3, r2
	add r0, sp, #0x18
	lsl r1, r1, #0x12
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	mov r1, #0x66
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r1, #2
	lsl r1, r1, #0x12
	sub r1, r1, r2
	mov r2, #6
	add r0, sp, #0x18
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	mov r1, #0x66
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	mov r1, #2
	lsl r1, r1, #0x12
	add r1, r2, r1
	mov r2, #6
	add r0, sp, #0x18
	lsl r2, r2, #0x10
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020044
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bne _021EAD4C
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EACC0:
	ldr r0, [r6, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #8
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x22
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EACEA:
	bl FUN_0200E308
	cmp r0, #1
	bne _021EAD4C
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	b _021EAD4C
_021EACFA:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r6, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r1, [r6, #0x14]
	cmp r1, #0
	beq _021EAD16
	mov r0, #1
	str r0, [r1]
_021EAD16:
	mov r7, #0
	add r5, r4, #0
_021EAD1A:
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_0201FFC8
	add r7, r7, #1
	add r5, r5, #4
	cmp r7, #4
	blt _021EAD1A
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [r6, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021EAD4C:
	ldr r0, [r6]
	cmp r0, #7
	beq _021EAD58
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EAD58:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021EAD5C: .word 0x000927C0

	thumb_func_start MOD05_021EAD60
MOD05_021EAD60: ; 0x021EAD60
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	str r0, [sp, #0x10]
	add r0, r1, #0
	ldr r0, [r0]
	str r1, [sp, #0x14]
	ldr r4, [r1, #0xc]
	cmp r0, #7
	bhi _021EAE6E
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EAD7E: ; jump table
	.short _021EAD8E - _021EAD7E - 2 ; case 0
	.short _021EAE1A - _021EAD7E - 2 ; case 1
	.short _021EAE3A - _021EAD7E - 2 ; case 2
	.short _021EAE5E - _021EAD7E - 2 ; case 3
	.short _021EAF9C - _021EAD7E - 2 ; case 4
	.short _021EAFAE - _021EAD7E - 2 ; case 5
	.short _021EAFDE - _021EAD7E - 2 ; case 6
	.short _021EAFF2 - _021EAD7E - 2 ; case 7
_021EAD8E:
	mov r1, #0x3d
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	ldr r1, [sp, #0x14]
	mov r2, #0x3d
	str r0, [r1, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r0, [sp, #0x14]
	mov r1, #6
	ldr r4, [r0, #0xc]
	mov r2, #1
	add r0, r4, #0
	bl MOD05_021E3E14
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	ldr r0, _021EB138 ; =0x000927C0
	mov r1, #0x4f
	lsl r1, r1, #2
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r1, r4, r1
	mov r2, #0
	mov r3, #1
	bl MOD05_021E3E64
	mov r7, #0x4f
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_021EADDC:
	mov r0, #0
	str r0, [sp]
	mov r2, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r1, r4, r7
	add r3, r2, #0
	bl MOD05_021E3FC4
	mov r1, #0x17
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _021EADDC
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAE1A:
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	add r1, r0, #0
	ldr r3, [sp, #0x14]
	sub r1, #0x11
	add r2, r1, #0
	add r3, r3, #4
	bl MOD05_021E3474
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAE3A:
	ldr r1, [sp, #0x14]
	ldr r1, [r1, #4]
	cmp r1, #0
	beq _021EAE6E
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	mov r0, #0xf2
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	add r0, r0, #4
	lsl r2, r1, #5
	ldr r1, _021EB13C ; =UNK05_021F7A50
	ldr r1, [r1, r2]
	str r1, [r4, r0]
	b _021EB04A
_021EAE5E:
	mov r0, #0xf3
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	blt _021EAE70
_021EAE6E:
	b _021EB04A
_021EAE70:
	sub r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #8
	str r1, [sp]
	mov r1, #0x86
	lsl r1, r1, #2
	add r2, r4, r1
	mov r1, #0x18
	mul r1, r0
	lsl r3, r0, #5
	add r0, r2, r1
	ldr r1, _021EB140 ; =UNK05_021F7A38
	ldr r2, _021EB144 ; =UNK05_021F7A3C
	ldr r5, _021EB148 ; =UNK05_021F7A40
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	ldr r3, [r5, r3]
	bl MOD05_021E3644
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #8
	str r1, [sp]
	mov r1, #0xaa
	lsl r1, r1, #2
	add r2, r4, r1
	mov r1, #0x18
	mul r1, r0
	lsl r3, r0, #5
	add r0, r2, r1
	ldr r1, _021EB14C ; =UNK05_021F7A44
	ldr r2, _021EB150 ; =UNK05_021F7A48
	ldr r5, _021EB154 ; =UNK05_021F7A4C
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	ldr r3, [r5, r3]
	bl MOD05_021E3644
	mov r0, #0x62
	lsl r0, r0, #2
	mov r1, #8
	add r3, r4, r0
	mov r0, #0xf2
	str r1, [sp]
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	mov r0, #0x18
	mul r0, r2
	add r0, r3, r0
	ldr r3, _021EB158 ; =0xFFFFF99A
	lsl r1, r1, #0xa
	mov r2, #0x29
	bl MOD05_021E3644
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r2, [r4, r0]
	sub r0, #0x90
	add r1, r4, r0
	mov r0, #0x14
	mul r0, r2
	lsl r3, r2, #5
	ldr r2, _021EB15C ; =UNK05_021F7A54
	add r0, r1, r0
	ldr r2, [r2, r3]
	mov r1, #0
	mov r3, #8
	bl MOD05_021E35B0
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, _021EB140 ; =UNK05_021F7A38
	lsl r3, r0, #5
	ldr r2, _021EB14C ; =UNK05_021F7A44
	ldr r1, [r1, r3]
	ldr r2, [r2, r3]
	add r0, sp, #0x3c
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #0x3c
	bl FUN_02020044
	mov r1, #2
	lsl r1, r1, #0xc
	add r0, sp, #0x30
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0xf2
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r2, #2
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #0x30
	bl FUN_02020074
	mov r1, #0xf2
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	mov r3, #1
	lsl r0, r0, #2
	add r2, r4, r0
	add r0, r1, #0
	sub r0, #0x18
	str r3, [r2, r0]
	ldr r0, [r4, r1]
	add r0, r0, #1
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	cmp r0, #6
	blt _021EAF90
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAF90:
	lsl r2, r0, #5
	ldr r0, _021EB13C ; =UNK05_021F7A50
	ldr r2, [r0, r2]
	add r0, r1, #4
	str r2, [r4, r0]
	b _021EB04A
_021EAF9C:
	mov r1, #0xf1
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	cmp r1, #0
	bne _021EB04A
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAFAE:
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #0xc
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #8]
	mov r0, #3
	mov r1, #0x22
	add r3, r2, #0
	bl FUN_0200E1D0
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAFDE:
	bl FUN_0200E308
	cmp r0, #0
	beq _021EB04A
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	add r1, r0, #1
	ldr r0, [sp, #0x14]
	str r1, [r0]
	b _021EB04A
_021EAFF2:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	ldr r0, [sp, #0x14]
	ldr r1, [r0, #0x14]
	cmp r1, #0
	beq _021EB012
	mov r0, #1
	str r0, [r1]
_021EB012:
	mov r7, #0x17
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #4
_021EB01A:
	ldr r0, [r5, r7]
	bl FUN_0201FFC8
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #6
	blt _021EB01A
	mov r1, #0x4f
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [sp, #0x14]
	mov r0, #4
	ldr r1, [r1, #0xc]
	bl FreeToHeapExplicit
	ldr r0, [sp, #0x10]
	bl FUN_0200621C
_021EB04A:
	mov r1, #0x86
	mov r0, #0
	lsl r1, r1, #2
	str r0, [sp, #0x18]
	add r0, r4, r1
	str r0, [sp, #0x28]
	add r0, r1, #0
	add r0, #0x90
	add r0, r4, r0
	sub r1, #0x90
	str r0, [sp, #0x24]
	add r0, r4, r1
	str r0, [sp, #0x20]
	mov r0, #0xce
	lsl r0, r0, #2
	add r0, r4, r0
	add r5, r4, #0
	str r0, [sp, #0x1c]
	add r6, r4, #0
	add r7, r4, #0
_021EB072:
	mov r0, #0x3b
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	cmp r0, #1
	bne _021EB0FE
	ldr r0, [sp, #0x28]
	bl MOD05_021E36A4
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x24]
	bl MOD05_021E36A4
	ldr r0, [sp, #0x20]
	bl MOD05_021E36A4
	ldr r0, [sp, #0x1c]
	bl MOD05_021E35C0
	ldr r0, [sp, #0x2c]
	cmp r0, #0
	beq _021EB0AE
	mov r0, #0x3b
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r5, r0]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	bl FUN_020200A0
_021EB0AE:
	mov r1, #0x86
	mov r2, #0xaa
	lsl r1, r1, #2
	lsl r2, r2, #2
	ldr r1, [r6, r1]
	ldr r2, [r6, r2]
	add r0, sp, #0x3c
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, sp, #0x3c
	bl FUN_02020044
	mov r0, #0x62
	lsl r0, r0, #2
	ldr r1, [r6, r0]
	add r0, sp, #0x30
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r5, r0]
	add r1, sp, #0x30
	bl FUN_02020064
	mov r1, #0xce
	lsl r1, r1, #2
	mov r0, #0x17
	ldr r1, [r7, r1]
	lsl r0, r0, #4
	lsl r1, r1, #0x10
	ldr r0, [r5, r0]
	lsr r1, r1, #0x10
	bl FUN_02020088
_021EB0FE:
	ldr r0, [sp, #0x28]
	add r5, r5, #4
	add r0, #0x18
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	add r6, #0x18
	add r0, #0x18
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x20]
	add r7, #0x14
	add r0, #0x18
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x1c]
	add r0, #0x14
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #6
	blt _021EB072
	ldr r0, [sp, #0x14]
	ldr r0, [r0]
	cmp r0, #7
	beq _021EB134
	ldr r0, [r4]
	bl FUN_0201FDEC
_021EB134:
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EB138: .word 0x000927C0
_021EB13C: .word UNK05_021F7A50
_021EB140: .word UNK05_021F7A38
_021EB144: .word UNK05_021F7A3C
_021EB148: .word UNK05_021F7A40
_021EB14C: .word UNK05_021F7A44
_021EB150: .word UNK05_021F7A48
_021EB154: .word UNK05_021F7A4C
_021EB158: .word 0xFFFFF99A
_021EB15C: .word UNK05_021F7A54

	thumb_func_start MOD05_021EB160
MOD05_021EB160: ; 0x021EB160
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5]
	ldr r4, [r5, #0xc]
	cmp r0, #7
	bls _021EB172
	b _021EB3F2
_021EB172:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EB17E: ; jump table
	.short _021EB18E - _021EB17E - 2 ; case 0
	.short _021EB272 - _021EB17E - 2 ; case 1
	.short _021EB28C - _021EB17E - 2 ; case 2
	.short _021EB29A - _021EB17E - 2 ; case 3
	.short _021EB2D4 - _021EB17E - 2 ; case 4
	.short _021EB312 - _021EB17E - 2 ; case 5
	.short _021EB344 - _021EB17E - 2 ; case 6
	.short _021EB374 - _021EB17E - 2 ; case 7
_021EB18E:
	mov r1, #0x6f
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x6f
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r4, [r5, #0xc]
	mov r1, #1
	add r0, r4, #0
	add r0, #8
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #8
	str r0, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #9
	str r0, [sp, #8]
	ldr r0, _021EB404 ; =0x000927C0
	mov r1, #0x51
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #1
	add r0, #8
	add r1, r4, r1
	add r3, r2, #0
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #0x51
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #2
	mov r2, #2
	mov r3, #6
	add r0, #8
	add r1, r4, r1
	lsl r2, r2, #0x12
	lsl r3, r3, #0x10
	bl MOD05_021E3FC4
	mov r1, #0x5e
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020398
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_02020238
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	bl MOD05_021E4688
	str r0, [r4, #4]
	mov r0, #4
	mov r1, #1
	bl AllocWindows
	str r0, [r4]
	mov r3, #0
	str r3, [sp]
	mov r0, #0x20
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	ldr r0, [r5, #0x10]
	ldr r1, [r4]
	ldr r0, [r0, #8]
	mov r2, #3
	bl AddWindowParameterized
	mov r1, #0
	add r0, sp, #0x14
	strh r1, [r0]
	mov r0, #3
	add r1, sp, #0x14
	mov r2, #2
	mov r3, #0x1e
	bl BG_LoadPlttData
	ldr r0, [r4]
	mov r1, #0
	bl FillWindowPixelBuffer
	ldr r0, [r4]
	bl ScheduleWindowCopyToVram
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB272:
	mov r1, #0x10
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #1
	sub r2, #0x20
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB28C:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021EB294
	b _021EB3F2
_021EB294:
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB29A:
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	mov r2, #0x10
	mov r3, #0xf
	bl MOD05_021E35B0
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r3, [r4, r0]
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _021EB408 ; =0x04000050
	mov r1, #0
	mov r2, #0xf
	bl G2x_SetBlendAlpha_
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB2D4:
	mov r0, #0x19
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E35C0
	mov r2, #0x19
	lsl r2, r2, #4
	ldr r1, [r4, r2]
	mov r3, #0x10
	sub r3, r3, r1
	lsl r3, r3, #8
	orr r1, r3
	ldr r3, _021EB40C ; =0x04000052
	cmp r0, #1
	strh r1, [r3]
	bne _021EB3F2
	mov r1, #0
	sub r0, r3, #2
	sub r2, #0x18
	strh r1, [r0]
	ldr r0, [r4, r2]
	bl FUN_02020398
	ldr r0, [r5]
	mov r1, #0x10
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x6e
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EB3F2
_021EB312:
	mov r0, #0x6e
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r1, [r4, r0]
	cmp r1, #0
	bgt _021EB3F2
	sub r0, #0x3c
	add r0, r4, r0
	mov r1, #0
	mov r2, #0xe
	mov r3, #0x10
	bl MOD05_021E35B0
	ldr r0, [r4, #4]
	ldr r2, [r4]
	mov r1, #0x10
	mov r3, #0xf
	bl MOD05_021E46D4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EB3F2
_021EB344:
	mov r0, #0x5f
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD05_021E35C0
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	lsl r0, r1, #4
	orr r1, r0
	ldr r0, _021EB410 ; =0x0400004D
	strb r1, [r0]
	ldr r0, [r4, #4]
	bl MOD05_021E4754
	cmp r0, #0
	beq _021EB36C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
_021EB36C:
	ldr r0, [r4]
	bl ScheduleWindowCopyToVram
	b _021EB3F2
_021EB374:
	mov r0, #0
	add r1, r0, #0
	bl FUN_0200E3A0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	ldr r0, [r4, #4]
	bl MOD05_021E46B4
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EB394
	mov r0, #1
	str r0, [r1]
_021EB394:
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r1, #0x51
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #8
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r0, r4, #0
	add r0, #8
	bl MOD05_021E3E44
	ldr r0, [r4]
	bl ClearWindowTilemapAndCopyToVram
	ldr r0, [r4]
	bl RemoveWindow
	ldr r0, [r4]
	mov r1, #1
	bl WindowArray_Delete
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl BG_ClearCharDataRange
	ldr r0, [r5, #0x10]
	mov r1, #3
	ldr r0, [r0, #8]
	bl BgClearTilemapBufferAndCommit
	ldr r0, _021EB410 ; =0x0400004D
	mov r1, #0
	strb r1, [r0]
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
_021EB3F2:
	ldr r0, [r5]
	cmp r0, #7
	beq _021EB3FE
	ldr r0, [r4, #8]
	bl FUN_0201FDEC
_021EB3FE:
	add sp, #0x18
	pop {r4, r5, r6, pc}
	nop
_021EB404: .word 0x000927C0
_021EB408: .word 0x04000050
_021EB40C: .word 0x04000052
_021EB410: .word 0x0400004D

	thumb_func_start MOD05_021EB414
MOD05_021EB414: ; 0x021EB414
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #8]
	ldr r1, [r5, #0x20]
	bl Camera_SetPerspectiveAngle
	ldr r0, [r4]
	ldr r1, [r5, #0x20]
	bl Camera_SetDistance
	ldrh r1, [r4, #4]
	add r0, sp, #0
	strh r1, [r0]
	ldrh r1, [r4, #6]
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0, #4]
	ldr r1, [r5, #0x20]
	add r0, sp, #0
	bl Camera_SetAngle
	add sp, #8
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EB448
MOD05_021EB448: ; 0x021EB448
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #7
	bls _021EB45A
	b _021EB5A0
_021EB45A:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EB466: ; jump table
	.short _021EB476 - _021EB466 - 2 ; case 0
	.short _021EB4AE - _021EB466 - 2 ; case 1
	.short _021EB4C6 - _021EB466 - 2 ; case 2
	.short _021EB4D4 - _021EB466 - 2 ; case 3
	.short _021EB4F8 - _021EB466 - 2 ; case 4
	.short _021EB534 - _021EB466 - 2 ; case 5
	.short _021EB556 - _021EB466 - 2 ; case 6
	.short _021EB56C - _021EB466 - 2 ; case 7
_021EB476:
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0xc]
	mov r2, #0x10
	mov r1, #0
_021EB484:
	strb r1, [r0]
	add r0, r0, #1
	sub r2, r2, #1
	bne _021EB484
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4AE:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4C6:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021EB5A0
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4D4:
	mov r0, #3
	mov r1, #0xf
	bl MOD05_021E8860
	mov r2, #0
	str r0, [r5]
	mov r0, #0xc
	add r1, r2, #0
	mul r1, r0
	ldr r0, _021EB5A4 ; =UNK05_021F7982
	str r2, [r5, #8]
	ldrh r0, [r0, r1]
	add sp, #0xc
	str r0, [r5, #0xc]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB4F8:
	ldr r0, [r5, #0xc]
	sub r0, r0, #1
	str r0, [r5, #0xc]
	bpl _021EB5A0
	ldr r2, [r5, #8]
	mov r1, #0xc
	ldr r3, _021EB5A8 ; =UNK05_021F7978
	mul r1, r2
	ldr r0, [r4, #0x10]
	add r1, r3, r1
	bl MOD05_021EB414
	ldr r0, [r5, #8]
	add r2, r0, #1
	str r2, [r5, #8]
	cmp r2, #0x10
	blo _021EB524
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB524:
	mov r0, #0xc
	add r1, r2, #0
	mul r1, r0
	ldr r0, _021EB5A4 ; =UNK05_021F7982
	add sp, #0xc
	ldrh r0, [r0, r1]
	str r0, [r5, #0xc]
	pop {r3, r4, r5, r6, pc}
_021EB534:
	mov r0, #0xa
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EB5AC ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB556:
	bl FUN_0200E308
	cmp r0, #0
	beq _021EB5A0
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB56C:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl MOD05_021E88C0
	ldr r0, _021EB5B0 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021EB58A
	mov r0, #1
	str r0, [r1]
_021EB58A:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021EB5A0:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021EB5A4: .word UNK05_021F7982
_021EB5A8: .word UNK05_021F7978
_021EB5AC: .word 0x00007FFF
_021EB5B0: .word 0x04000050

	thumb_func_start MOD05_021EB5B4
MOD05_021EB5B4: ; 0x021EB5B4
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0xc]
	cmp r0, #9
	bhi _021EB636
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EB5D0: ; jump table
	.short _021EB5E4 - _021EB5D0 - 2 ; case 0
	.short _021EB618 - _021EB5D0 - 2 ; case 1
	.short _021EB630 - _021EB5D0 - 2 ; case 2
	.short _021EB640 - _021EB5D0 - 2 ; case 3
	.short _021EB66E - _021EB5D0 - 2 ; case 4
	.short _021EB698 - _021EB5D0 - 2 ; case 5
	.short _021EB6C6 - _021EB5D0 - 2 ; case 6
	.short _021EB6E8 - _021EB5D0 - 2 ; case 7
	.short _021EB70A - _021EB5D0 - 2 ; case 8
	.short _021EB720 - _021EB5D0 - 2 ; case 9
_021EB5E4:
	mov r0, #4
	mov r1, #0x38
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x38
	str r0, [r4, #0xc]
	bl memset
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB618:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r4, #4
	bl MOD05_021E3474
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB630:
	ldr r1, [r4, #4]
	cmp r1, #0
	bne _021EB638
_021EB636:
	b _021EB754
_021EB638:
	add r0, r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB640:
	mov r0, #5
	mov r1, #0xd
	bl MOD05_021E8860
	str r0, [r5]
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	bl Camera_GetPerspectiveAngle
	mov r2, #1
	add r1, r0, #0
	add r5, #8
	lsl r2, r2, #8
	add r0, r5, #0
	add r2, r1, r2
	mov r3, #0x28
	bl MOD05_021E35B0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB66E:
	add r0, r5, #0
	add r0, #8
	bl MOD05_021E35C0
	add r6, r0, #0
	ldr r0, [r5, #8]
	ldr r1, [r4, #0x10]
	lsl r0, r0, #0x10
	ldr r1, [r1, #0x20]
	lsr r0, r0, #0x10
	bl Camera_SetPerspectiveAngle
	cmp r6, #1
	bne _021EB754
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	mov r0, #5
	str r0, [r5, #0x34]
	pop {r3, r4, r5, r6, pc}
_021EB698:
	ldr r0, [r5, #0x34]
	sub r0, r0, #1
	str r0, [r5, #0x34]
	bpl _021EB754
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x20]
	bl Camera_GetDistance
	mov r3, #8
	str r3, [sp]
	ldr r2, _021EB758 ; =0x0092E000
	add r1, r0, #0
	add r5, #0x1c
	add r0, r5, #0
	sub r2, r1, r2
	lsl r3, r3, #8
	bl MOD05_021E3644
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB6C6:
	add r0, r5, #0
	add r0, #0x1c
	bl MOD05_021E36A4
	ldr r1, [r4, #0x10]
	add r6, r0, #0
	ldr r0, [r5, #0x1c]
	ldr r1, [r1, #0x20]
	bl Camera_SetDistance
	cmp r6, #1
	bne _021EB754
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB6E8:
	mov r0, #0x3c
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EB75C ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB70A:
	bl FUN_0200E308
	cmp r0, #0
	beq _021EB754
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, pc}
_021EB720:
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl MOD05_021E88C0
	ldr r0, _021EB760 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _021EB73E
	mov r0, #1
	str r0, [r1]
_021EB73E:
	ldr r1, [r4, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add r0, r6, #0
	bl FUN_0200621C
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
_021EB754:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.balign 4, 0
_021EB758: .word 0x0092E000
_021EB75C: .word 0x00007FFF
_021EB760: .word 0x04000050

	thumb_func_start MOD05_021EB764
MOD05_021EB764: ; 0x021EB764
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r0, #0
	str r1, [sp, #0x14]
	ldr r1, [r5]
	add r6, r2, #0
	ldr r4, [r5, #0xc]
	cmp r1, #0xe
	bls _021EB778
	b _021EBB72
_021EB778:
	add r2, r1, r1
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021EB784: ; jump table
	.short _021EB7A2 - _021EB784 - 2 ; case 0
	.short _021EB848 - _021EB784 - 2 ; case 1
	.short _021EB85E - _021EB784 - 2 ; case 2
	.short _021EB86A - _021EB784 - 2 ; case 3
	.short _021EB8B8 - _021EB784 - 2 ; case 4
	.short _021EB8D6 - _021EB784 - 2 ; case 5
	.short _021EB99C - _021EB784 - 2 ; case 6
	.short _021EB9EE - _021EB784 - 2 ; case 7
	.short _021EBA04 - _021EB784 - 2 ; case 8
	.short _021EBA34 - _021EB784 - 2 ; case 9
	.short _021EBA4A - _021EB784 - 2 ; case 10
	.short _021EBA72 - _021EB784 - 2 ; case 11
	.short _021EBA8A - _021EB784 - 2 ; case 12
	.short _021EBAAA - _021EB784 - 2 ; case 13
	.short _021EBB0E - _021EB784 - 2 ; case 14
_021EB7A2:
	mov r1, #0x1f
	ldr r0, [sp, #0x14]
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x1f
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #4
	bl memset
	ldr r4, [r5, #0xc]
	mov r1, #1
	add r0, r4, #0
	add r0, #0x44
	add r2, r1, #0
	bl MOD05_021E3E14
	mov r0, #0x17
	str r0, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	ldr r0, _021EBB4C ; =0x000927C0
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x44
	add r1, r4, r1
	mov r2, #0x16
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0
	str r0, [sp]
	mov r1, #6
	str r0, [sp, #4]
	add r0, r4, #0
	lsl r1, r1, #6
	mov r3, #0x11
	ldr r2, _021EBB50 ; =0xFFFE0000
	add r0, #0x44
	add r1, r4, r1
	lsl r3, r3, #0xe
	bl MOD05_021E3FC4
	mov r1, #0x6d
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0
	str r0, [sp]
	ldrh r0, [r6, #6]
	ldr r1, [sp, #0x14]
	mov r3, #0xa
	str r0, [sp, #4]
	mov r0, #0x6d
	lsl r0, r0, #2
	ldrh r2, [r6, #4]
	ldr r0, [r4, r0]
	bl MOD05_021E4014
	ldr r0, [r5, #0x10]
	ldr r0, [r0, #8]
	bl MOD05_021E3C00
	bl MOD05_021E4788
	str r0, [r4, #0x40]
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB848:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB85E:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _021EB8E6
	add r0, r1, #1
	str r0, [r5]
	b _021EBB72
_021EB86A:
	ldr r3, [r5, #0x10]
	mov r0, #0xd
	ldr r3, [r3, #8]
	mov r1, #0xc
	mov r2, #0xb
	bl MOD05_021E3D20
	mov r0, #0x79
	mov r2, #8
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x1f
	str r0, [sp, #4]
	mov r0, #0x17
	str r0, [sp, #8]
	ldr r1, [r4, #0x40]
	add r0, r5, #0
	add r3, r2, #0
	bl MOD05_021E47BC
	mov r1, #1
	add r0, r4, #0
	lsl r1, r1, #0xc
	add r0, #0x2c
	add r2, r1, #0
	mov r3, #0xf
	bl MOD05_021E35EC
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB8B8:
	bl MOD05_021E35AC
	cmp r0, #0
	beq _021EB8E6
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	ldr r0, [r4, #0x40]
	bl MOD05_021E47A0
	mov r0, #0x7b
	mov r1, #0xa
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EBB72
_021EB8D6:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	blt _021EB8E8
_021EB8E6:
	b _021EBB72
_021EB8E8:
	mov r1, #2
	lsl r1, r1, #0xc
	add r0, sp, #0x18
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020064
	mov r0, #0
	str r0, [sp]
	mov r0, #0x6e
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #4]
	mov r0, #0x11
	mov r2, #2
	lsl r0, r0, #0xe
	mov r1, #0x62
	lsl r2, r2, #0xc
	mov r3, #0x40
	bl MOD05_021E49F0
	ldr r3, _021EBB54 ; =0x04000048
	mov r0, #0x3f
	ldrh r2, [r3]
	mov r1, #0x1f
	bic r2, r0
	orr r2, r1
	mov r1, #0x20
	orr r2, r1
	strh r2, [r3]
	ldrh r2, [r3, #2]
	bic r2, r0
	mov r0, #0xf
	orr r0, r2
	orr r0, r1
	strh r0, [r3, #2]
	lsl r0, r1, #0x15
	ldr r3, [r0]
	ldr r2, _021EBB58 ; =0xFFFF1FFF
	lsl r1, r1, #8
	and r2, r3
	orr r1, r2
	str r1, [r0]
	mov r3, #4
	str r3, [sp]
	ldr r1, _021EBB50 ; =0xFFFE0000
	ldr r2, [r6]
	add r0, r4, #0
	lsl r3, r3, #0x10
	bl MOD05_021E3644
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #0
	bl FUN_02020238
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r2, #0x11
	ldr r1, [r4]
	add r0, sp, #0x24
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x24
	bl FUN_02020044
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB99C:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r2, #0x11
	add r6, r0, #0
	ldr r1, [r4]
	add r0, sp, #0x24
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x24
	bl FUN_02020044
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	mov r1, #0
	str r1, [sp]
	mov r1, #0x6e
	lsl r1, r1, #2
	add r1, r4, r1
	str r1, [sp, #4]
	mov r2, #2
	ldr r0, [r0, #4]
	mov r1, #0x62
	lsl r2, r2, #0xc
	mov r3, #0x40
	bl MOD05_021E49F0
	cmp r6, #1
	bne _021EBA60
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EB9EE:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0
	mov r2, #0x10
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA04:
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	add r7, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E4AD0
	cmp r7, #1
	bne _021EBA60
	mov r3, #0
	str r3, [sp]
	mov r0, #0x6d
	lsl r0, r0, #2
	ldrh r2, [r6, #4]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x14]
	bl MOD05_021E3F68
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA34:
	add r0, r4, #0
	add r0, #0x18
	mov r1, #0x10
	mov r2, #0
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA4A:
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E4AD0
	cmp r6, #1
	beq _021EBA62
_021EBA60:
	b _021EBB72
_021EBA62:
	ldr r0, [r5]
	mov r1, #0x1a
	add r0, r0, #1
	str r0, [r5]
	mov r0, #0x7b
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021EBB72
_021EBA72:
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	sub r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0
	bge _021EBB72
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBA8A:
	mov r0, #0xf
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EBB5C ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBAAA:
	add r0, r4, #0
	add r0, #0x2c
	bl MOD05_021E35FC
	mov r2, #1
	ldr r3, [r4, #0x2c]
	lsl r2, r2, #0xc
	add r1, r3, r2
	add r2, r3, r2
	add r0, sp, #0x18
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x18
	bl FUN_02020064
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0202011C
	add r6, r0, #0
	ldr r0, [r4, #0x2c]
	mov r1, #0x44
	mov r2, #0x1e
	bl MOD05_021E4A3C
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #0x6e
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #4]
	ldr r0, [r6, #4]
	ldr r2, [sp, #0x1c]
	mov r3, #0x40
	bl MOD05_021E49F0
	bl FUN_0200E308
	cmp r0, #0
	beq _021EBB72
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EBB72
_021EBB0E:
	ldr r1, _021EBB5C ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EBB20
	mov r0, #1
	str r0, [r1]
_021EBB20:
	mov r0, #0x6d
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FFC8
	mov r1, #6
	add r0, r4, #0
	lsl r1, r1, #6
	add r0, #0x44
	add r1, r4, r1
	bl MOD05_021E3F3C
	add r4, #0x44
	add r0, r4, #0
	bl MOD05_021E3E44
	mov r2, #1
	lsl r2, r2, #0x1a
	ldr r1, [r2]
	ldr r0, _021EBB58 ; =0xFFFF1FFF
	b _021EBB60
	nop
_021EBB4C: .word 0x000927C0
_021EBB50: .word 0xFFFE0000
_021EBB54: .word 0x04000048
_021EBB58: .word 0xFFFF1FFF
_021EBB5C: .word 0x00007FFF
_021EBB60:
	and r0, r1
	str r0, [r2]
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add sp, #0x30
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021EBB72:
	mov r1, #0x79
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	cmp r0, #1
	bne _021EBBB6
	ldr r3, [r4, #0x2c]
	mov r0, #0
	str r3, [sp]
	str r0, [sp, #4]
	mov r0, #0x80
	str r0, [sp, #8]
	mov r0, #0x44
	str r0, [sp, #0xc]
	add r0, r1, #4
	ldr r0, [r4, r0]
	sub r1, #0x24
	str r0, [sp, #0x10]
	add r0, r4, r1
	ldr r1, [r5, #0x10]
	mov r2, #3
	ldr r1, [r1, #8]
	bl MOD05_021E3DA0
	mov r3, #0x7a
	lsl r3, r3, #2
	ldr r0, [r4, r3]
	sub r0, #0xf
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x17
	sub r1, r1, r2
	mov r0, #0x17
	ror r1, r0
	add r0, r2, r1
	str r0, [r4, r3]
_021EBBB6:
	ldr r0, [r5]
	cmp r0, #0xe
	beq _021EBBC2
	ldr r0, [r4, #0x44]
	bl FUN_0201FDEC
_021EBBC2:
	mov r0, #0
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start MOD05_021EBBC8
MOD05_021EBBC8: ; 0x021EBBC8
	push {r4, lr}
	ldr r2, _021EBBE4 ; =UNK05_021F7938
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBBE0
	add r0, r4, #0
	bl FUN_0200621C
_021EBBE0:
	pop {r4, pc}
	nop
_021EBBE4: .word UNK05_021F7938

	thumb_func_start MOD05_021EBBE8
MOD05_021EBBE8: ; 0x021EBBE8
	push {r4, lr}
	ldr r2, _021EBC04 ; =UNK05_021F7940
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC00
	add r0, r4, #0
	bl FUN_0200621C
_021EBC00:
	pop {r4, pc}
	nop
_021EBC04: .word UNK05_021F7940

	thumb_func_start MOD05_021EBC08
MOD05_021EBC08: ; 0x021EBC08
	push {r4, lr}
	ldr r2, _021EBC24 ; =UNK05_021F7948
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC20
	add r0, r4, #0
	bl FUN_0200621C
_021EBC20:
	pop {r4, pc}
	nop
_021EBC24: .word UNK05_021F7948

	thumb_func_start MOD05_021EBC28
MOD05_021EBC28: ; 0x021EBC28
	push {r4, lr}
	ldr r2, _021EBC44 ; =UNK05_021F7950
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC40
	add r0, r4, #0
	bl FUN_0200621C
_021EBC40:
	pop {r4, pc}
	nop
_021EBC44: .word UNK05_021F7950

	thumb_func_start MOD05_021EBC48
MOD05_021EBC48: ; 0x021EBC48
	push {r4, lr}
	ldr r2, _021EBC64 ; =UNK05_021F7958
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC60
	add r0, r4, #0
	bl FUN_0200621C
_021EBC60:
	pop {r4, pc}
	nop
_021EBC64: .word UNK05_021F7958

	thumb_func_start MOD05_021EBC68
MOD05_021EBC68: ; 0x021EBC68
	push {r4, lr}
	ldr r2, _021EBC84 ; =UNK05_021F7960
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBC80
	add r0, r4, #0
	bl FUN_0200621C
_021EBC80:
	pop {r4, pc}
	nop
_021EBC84: .word UNK05_021F7960

	thumb_func_start MOD05_021EBC88
MOD05_021EBC88: ; 0x021EBC88
	push {r4, lr}
	ldr r2, _021EBCA4 ; =UNK05_021F7968
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBCA0
	add r0, r4, #0
	bl FUN_0200621C
_021EBCA0:
	pop {r4, pc}
	nop
_021EBCA4: .word UNK05_021F7968

	thumb_func_start MOD05_021EBCA8
MOD05_021EBCA8: ; 0x021EBCA8
	push {r4, lr}
	ldr r2, _021EBCC4 ; =UNK05_021F7970
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EB764
	cmp r0, #1
	bne _021EBCC0
	add r0, r4, #0
	bl FUN_0200621C
_021EBCC0:
	pop {r4, pc}
	nop
_021EBCC4: .word UNK05_021F7970

	thumb_func_start MOD05_021EBCC8
MOD05_021EBCC8: ; 0x021EBCC8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl Save_PlayerData_GetProfileAddr
	bl PlayerProfile_GetTrainerGender
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EBCD8
MOD05_021EBCD8: ; 0x021EBCD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	add r5, r0, #0
	ldr r0, [r5]
	str r1, [sp, #0x10]
	str r2, [sp, #0x14]
	ldr r4, [r5, #0xc]
	cmp r0, #0x13
	bls _021EBCEC
	b _021EC3A0
_021EBCEC:
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021EBCF8: ; jump table
	.short _021EBD20 - _021EBCF8 - 2 ; case 0
	.short _021EBEC0 - _021EBCF8 - 2 ; case 1
	.short _021EBED6 - _021EBCF8 - 2 ; case 2
	.short _021EBEE4 - _021EBCF8 - 2 ; case 3
	.short _021EBF6C - _021EBCF8 - 2 ; case 4
	.short _021EBFBA - _021EBCF8 - 2 ; case 5
	.short _021EBFD0 - _021EBCF8 - 2 ; case 6
	.short _021EC002 - _021EBCF8 - 2 ; case 7
	.short _021EC018 - _021EBCF8 - 2 ; case 8
	.short _021EC038 - _021EBCF8 - 2 ; case 9
	.short _021EC0D4 - _021EBCF8 - 2 ; case 10
	.short _021EC122 - _021EBCF8 - 2 ; case 11
	.short _021EC138 - _021EBCF8 - 2 ; case 12
	.short _021EC16A - _021EBCF8 - 2 ; case 13
	.short _021EC180 - _021EBCF8 - 2 ; case 14
	.short _021EC19E - _021EBCF8 - 2 ; case 15
	.short _021EC1E8 - _021EBCF8 - 2 ; case 16
	.short _021EC21C - _021EBCF8 - 2 ; case 17
	.short _021EC284 - _021EBCF8 - 2 ; case 18
	.short _021EC342 - _021EBCF8 - 2 ; case 19
_021EBD20:
	mov r1, #0x9b
	ldr r0, [sp, #0x10]
	lsl r1, r1, #2
	bl AllocFromHeap
	mov r2, #0x9b
	str r0, [r5, #0xc]
	mov r1, #0
	lsl r2, r2, #2
	bl memset
	ldr r4, [r5, #0xc]
	mov r1, #4
	add r0, r4, #0
	add r0, #0x44
	mov r2, #3
	bl MOD05_021E3E14
	mov r0, #0x17
	str r0, [sp]
	mov r1, #0x18
	str r1, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	ldr r0, _021EC0C0 ; =0x000927C0
	lsl r1, r1, #4
	str r0, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x44
	add r1, r4, r1
	mov r2, #0x16
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0x17
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x19
	str r0, [sp, #8]
	ldr r0, _021EC0C4 ; =0x000927C1
	mov r1, #0x6d
	str r0, [sp, #0xc]
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x44
	add r1, r4, r1
	mov r2, #0x16
	mov r3, #1
	bl MOD05_021E3E64
	mov r0, #0xf
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0x11
	str r0, [sp, #8]
	ldr r0, _021EC0C8 ; =0x000927C2
	mov r1, #0x7a
	str r0, [sp, #0xc]
	ldr r2, [sp, #0x14]
	add r0, r4, #0
	lsl r1, r1, #2
	ldrb r2, [r2, #6]
	add r0, #0x44
	add r1, r4, r1
	mov r3, #0xc
	bl MOD05_021E3E64
	mov r1, #2
	lsl r1, r1, #0xc
	add r0, sp, #0x34
	add r2, r1, #0
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #6
	lsl r0, r0, #6
	add r0, r4, r0
	str r0, [sp, #0x18]
	str r0, [sp, #0x20]
	add r0, r4, #0
	str r0, [sp, #0x24]
	add r0, #0x44
	mov r7, #0
	add r6, r4, #0
	str r0, [sp, #0x24]
_021EBDCE:
	cmp r7, #3
	bge _021EBDDA
	mov r0, #0
	ldr r1, [sp, #0x18]
	str r0, [sp, #0x1c]
	b _021EBDEA
_021EBDDA:
	sub r1, r7, #1
	mov r0, #0x34
	add r2, r1, #0
	mul r2, r0
	ldr r0, [sp, #0x20]
	add r1, r0, r2
	mov r0, #1
	str r0, [sp, #0x1c]
_021EBDEA:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r2, #0
	ldr r0, [sp, #0x24]
	add r3, r2, #0
	bl MOD05_021E3FC4
	mov r1, #0x87
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r0, r1, #0
	ldr r0, [r6, r0]
	mov r1, #0
	bl FUN_020200A0
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x1c]
	bl FUN_02020130
	ldr r0, [sp, #0x18]
	add r7, r7, #1
	add r0, #0x34
	add r6, r6, #4
	str r0, [sp, #0x18]
	cmp r7, #4
	blt _021EBDCE
	ldr r0, [r5, #0x10]
	bl MOD05_021EBCC8
	cmp r0, #0
	bne _021EBE48
	mov r2, #0
	str r2, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	mov r3, #0xa
	bl MOD05_021E4014
	mov r1, #0
	b _021EBE60
_021EBE48:
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	mov r0, #0x87
	str r2, [sp, #4]
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	mov r3, #0xa
	bl MOD05_021E4014
	mov r1, #1
_021EBE60:
	mov r0, #0x99
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x34
	bl FUN_02020064
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r2, [sp, #0x14]
	mov r0, #0x22
	lsl r0, r0, #4
	ldrb r2, [r2, #5]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	mov r3, #0xa
	bl MOD05_021E4014
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #2
	bl FUN_020200EC
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x34
	bl FUN_02020064
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBEC0:
	mov r0, #1
	mov r1, #0x10
	str r0, [sp]
	add r2, r1, #0
	add r3, r5, #4
	bl MOD05_021E3474
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBED6:
	ldr r1, [r5, #4]
	cmp r1, #0
	bne _021EBEDE
	b _021EC3A0
_021EBEDE:
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBEE4:
	mov r0, #6
	mov r2, #0x2e
	mov r3, #1
	str r0, [sp]
	ldr r1, _021EC0CC ; =0xFFFB0000
	add r0, r4, #0
	lsl r2, r2, #0xc
	lsl r3, r3, #0x12
	bl MOD05_021E3644
	mov r2, #0x72
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x89
	lsl r0, r0, #2
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBF6C:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r2, #0x72
	add r6, r0, #0
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xc
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	cmp r6, #1
	bne _021EC02E
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBFBA:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0
	mov r2, #0x10
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EBFD0:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	bne _021EC02E
	mov r3, #0
	mov r2, #0x87
	str r3, [sp]
	lsl r2, r2, #2
	ldr r0, [r4, r2]
	add r2, #0x48
	ldr r1, [sp, #0x10]
	ldr r2, [r4, r2]
	bl MOD05_021E3F68
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC002:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0x10
	mov r2, #0
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC018:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	beq _021EC030
_021EC02E:
	b _021EC3A0
_021EC030:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC038:
	mov r0, #6
	mov r1, #0x15
	mov r2, #0xd
	str r0, [sp]
	ldr r3, _021EC0D0 ; =0xFFFC0000
	add r0, r4, #0
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	bl MOD05_021E3644
	mov r2, #0x11
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x8a
	lsl r0, r0, #2
	mov r1, #1
	ldr r0, [r4, r0]
	lsl r1, r1, #0xc
	bl FUN_020200D8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
	.balign 4, 0
_021EC0C0: .word 0x000927C0
_021EC0C4: .word 0x000927C1
_021EC0C8: .word 0x000927C2
_021EC0CC: .word 0xFFFB0000
_021EC0D0: .word 0xFFFC0000
_021EC0D4:
	add r0, r4, #0
	bl MOD05_021E36A4
	mov r2, #0x11
	add r6, r0, #0
	ldr r1, [r4]
	add r0, sp, #0x40
	lsl r2, r2, #0xe
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	cmp r6, #1
	bne _021EC212
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC122:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0
	mov r2, #0x10
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC138:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	bne _021EC212
	mov r3, #0
	mov r0, #0x22
	ldr r2, [sp, #0x14]
	str r3, [sp]
	lsl r0, r0, #4
	ldrb r2, [r2, #5]
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	bl MOD05_021E3F68
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC16A:
	add r0, r4, #0
	add r0, #0x30
	mov r1, #0x10
	mov r2, #0
	mov r3, #3
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC180:
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E35C0
	add r6, r0, #0
	add r0, r4, #0
	add r0, #0x30
	bl MOD05_021E4AD0
	cmp r6, #1
	bne _021EC212
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC19E:
	ldr r0, [r5, #0x10]
	mov r1, #0x8b
	ldr r0, [r0, #0x20]
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	add r0, sp, #0x2c
	bl Camera_GetAngle
	add r1, sp, #0x2c
	mov r2, #0x92
	ldrh r0, [r1]
	lsl r2, r2, #2
	strh r0, [r4, r2]
	ldrh r3, [r1, #2]
	add r0, r2, #2
	strh r3, [r4, r0]
	ldrh r3, [r1, #4]
	add r0, r2, #4
	strh r3, [r4, r0]
	ldrh r1, [r1, #6]
	add r0, r2, #6
	ldr r3, [sp, #0x14]
	strh r1, [r4, r0]
	ldrh r1, [r4, r2]
	add r2, #8
	add r0, r4, r2
	ldr r2, [sp, #0x14]
	ldrb r3, [r3, #4]
	ldr r2, [r2]
	add r2, r1, r2
	bl MOD05_021E35B0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC1E8:
	mov r0, #0x25
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E35C0
	mov r1, #0x25
	lsl r1, r1, #4
	add r6, r0, #0
	add r0, r1, #0
	ldr r2, [r4, r1]
	sub r0, #8
	strh r2, [r4, r0]
	add r0, r1, #0
	sub r1, #0x24
	sub r0, #8
	ldr r1, [r4, r1]
	add r0, r4, r0
	bl Camera_SetAngle
	cmp r6, #1
	beq _021EC214
_021EC212:
	b _021EC3A0
_021EC214:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC21C:
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl Camera_GetDistance
	add r1, r0, #0
	mov r0, #0x1e
	str r0, [sp]
	mov r0, #0x23
	mov r2, #0xfa
	lsl r0, r0, #4
	lsl r2, r2, #0xc
	add r0, r4, r0
	sub r2, r1, r2
	mov r3, #0
	bl MOD05_021E3644
	mov r0, #0x1e
	mov r1, #0
	mov r2, #6
	str r0, [sp]
	add r0, r4, #0
	lsl r2, r2, #0x10
	add r3, r1, #0
	bl MOD05_021E3644
	mov r0, #0x1e
	str r0, [sp]
	add r0, r4, #0
	mov r1, #0
	mov r2, #6
	add r0, #0x18
	lsl r2, r2, #0x10
	add r3, r1, #0
	bl MOD05_021E3644
	mov r0, #0x1e
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0
	str r0, [sp, #8]
	ldr r3, _021EC3B4 ; =0x00007FFF
	mov r0, #3
	add r2, r1, #0
	bl FUN_0200E1D0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC284:
	mov r0, #0x23
	lsl r0, r0, #4
	add r0, r4, r0
	bl MOD05_021E36A4
	add r0, r4, #0
	bl MOD05_021E36A4
	add r0, r4, #0
	add r0, #0x18
	bl MOD05_021E36A4
	mov r1, #0x23
	lsl r1, r1, #4
	ldr r0, [r4, r1]
	sub r1, r1, #4
	ldr r1, [r4, r1]
	bl Camera_SetDistance
	mov r1, #0x2e
	ldr r2, [r4]
	lsl r1, r1, #0xc
	sub r1, r1, r2
	mov r2, #0x72
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xc
	add r2, r3, r2
	add r0, sp, #0x40
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r1, #0xd
	ldr r2, [r4]
	lsl r1, r1, #0x10
	add r1, r2, r1
	mov r2, #0x11
	ldr r3, [r4, #0x18]
	lsl r2, r2, #0xe
	sub r2, r2, r3
	add r0, sp, #0x40
	mov r3, #0
	bl MOD05_021E3FF8
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	mov r0, #9
	ldr r1, [sp, #0x44]
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x44]
	mov r0, #1
	ldr r1, [sp, #0x40]
	lsl r0, r0, #0x10
	sub r0, r1, r0
	str r0, [sp, #0x40]
	mov r0, #0x8a
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	add r1, sp, #0x40
	bl FUN_02020044
	bl FUN_0200E308
	cmp r0, #0
	beq _021EC3A0
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	b _021EC3A0
_021EC342:
	ldr r1, _021EC3B4 ; =0x00007FFF
	mov r0, #1
	bl FUN_0200E3A0
	ldr r1, [r5, #0x14]
	cmp r1, #0
	beq _021EC354
	mov r0, #1
	str r0, [r1]
_021EC354:
	mov r7, #0
	add r6, r4, #0
_021EC358:
	mov r0, #0x87
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_0201FFC8
	add r7, r7, #1
	add r6, r6, #4
	cmp r7, #4
	blt _021EC358
	mov r0, #6
	lsl r0, r0, #6
	add r6, r4, r0
	add r0, r4, #0
	str r0, [sp, #0x28]
	add r0, #0x44
	mov r7, #0
	str r0, [sp, #0x28]
_021EC37A:
	ldr r0, [sp, #0x28]
	add r1, r6, #0
	bl MOD05_021E3F3C
	add r7, r7, #1
	add r6, #0x34
	cmp r7, #3
	blt _021EC37A
	add r4, #0x44
	add r0, r4, #0
	bl MOD05_021E3E44
	ldr r1, [r5, #0xc]
	mov r0, #4
	bl FreeToHeapExplicit
	add sp, #0x4c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_021EC3A0:
	ldr r0, [r5]
	cmp r0, #0x13
	beq _021EC3AC
	ldr r0, [r4, #0x44]
	bl FUN_0201FDEC
_021EC3AC:
	mov r0, #0
	add sp, #0x4c
	pop {r4, r5, r6, r7, pc}
	nop
_021EC3B4: .word 0x00007FFF

	thumb_func_start MOD05_021EC3B8
MOD05_021EC3B8: ; 0x021EC3B8
	push {r4, lr}
	ldr r2, _021EC3D4 ; =UNK05_021F7910
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC3D0
	add r0, r4, #0
	bl FUN_0200621C
_021EC3D0:
	pop {r4, pc}
	nop
_021EC3D4: .word UNK05_021F7910

	thumb_func_start MOD05_021EC3D8
MOD05_021EC3D8: ; 0x021EC3D8
	push {r4, lr}
	ldr r2, _021EC3F4 ; =UNK05_021F7918
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC3F0
	add r0, r4, #0
	bl FUN_0200621C
_021EC3F0:
	pop {r4, pc}
	nop
_021EC3F4: .word UNK05_021F7918

	thumb_func_start MOD05_021EC3F8
MOD05_021EC3F8: ; 0x021EC3F8
	push {r4, lr}
	ldr r2, _021EC414 ; =UNK05_021F7920
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC410
	add r0, r4, #0
	bl FUN_0200621C
_021EC410:
	pop {r4, pc}
	nop
_021EC414: .word UNK05_021F7920

	thumb_func_start MOD05_021EC418
MOD05_021EC418: ; 0x021EC418
	push {r4, lr}
	ldr r2, _021EC434 ; =UNK05_021F7928
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC430
	add r0, r4, #0
	bl FUN_0200621C
_021EC430:
	pop {r4, pc}
	nop
_021EC434: .word UNK05_021F7928

	thumb_func_start MOD05_021EC438
MOD05_021EC438: ; 0x021EC438
	push {r4, lr}
	ldr r2, _021EC454 ; =UNK05_021F7930
	add r4, r0, #0
	add r0, r1, #0
	mov r1, #4
	bl MOD05_021EBCD8
	cmp r0, #1
	bne _021EC450
	add r0, r4, #0
	bl FUN_0200621C
_021EC450:
	pop {r4, pc}
	nop
_021EC454: .word UNK05_021F7930

	.section .rodata

	.global UNK05_021F7910
UNK05_021F7910: ; 0x021F7910
	.byte 0xDC, 0x05, 0x00, 0x00, 0x0F, 0x41, 0x0E, 0x00

	.global UNK05_021F7918
UNK05_021F7918: ; 0x021F7918
	.byte 0xDC, 0x05, 0x00, 0x00
	.byte 0x0F, 0x42, 0x12, 0x00

	.global UNK05_021F7920
UNK05_021F7920: ; 0x021F7920
	.byte 0xDC, 0x05, 0x00, 0x00, 0x0F, 0x43, 0x13, 0x00

	.global UNK05_021F7928
UNK05_021F7928: ; 0x021F7928
	.byte 0xDC, 0x05, 0x00, 0x00
	.byte 0x0F, 0x44, 0x14, 0x00

	.global UNK05_021F7930
UNK05_021F7930: ; 0x021F7930
	.byte 0xB8, 0x0B, 0x00, 0x00, 0x1E, 0x45, 0x15, 0x00

	.global UNK05_021F7938
UNK05_021F7938: ; 0x021F7938
	.byte 0x00, 0x00, 0x0B, 0x00
	.byte 0x3E, 0x00, 0x01, 0x00

	.global UNK05_021F7940
UNK05_021F7940: ; 0x021F7940
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4A, 0x00, 0x01, 0x00

	.global UNK05_021F7948
UNK05_021F7948: ; 0x021F7948
	.byte 0x00, 0x00, 0x0C, 0x00
	.byte 0x4B, 0x00, 0x00, 0x00

	.global UNK05_021F7950
UNK05_021F7950: ; 0x021F7950
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4C, 0x00, 0x01, 0x00

	.global UNK05_021F7958
UNK05_021F7958: ; 0x021F7958
	.byte 0x00, 0x00, 0x0C, 0x00
	.byte 0x4D, 0x00, 0x01, 0x00

	.global UNK05_021F7960
UNK05_021F7960: ; 0x021F7960
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4E, 0x00, 0x01, 0x00

	.global UNK05_021F7968
UNK05_021F7968: ; 0x021F7968
	.byte 0x00, 0x00, 0x0B, 0x00
	.byte 0x40, 0x00, 0x01, 0x00

	.global UNK05_021F7970
UNK05_021F7970: ; 0x021F7970
	.byte 0x00, 0x00, 0x0B, 0x00, 0x4F, 0x00, 0x01, 0x00

	.global UNK05_021F7978
UNK05_021F7978: ; 0x021F7978
	.byte 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD6, 0x00, 0x00, 0xC1, 0x05

	.global UNK05_021F7982
UNK05_021F7982: ; 0x021F7982
	.byte 0x04, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xCF, 0x00, 0xFF
	.byte 0x01, 0x06, 0x04, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE6, 0x00, 0x10, 0x91, 0x06, 0x04, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD6, 0x00, 0x0A, 0x11, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xE1, 0x00, 0xF0, 0x80, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xC6, 0x00, 0x00
	.byte 0x51, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE0, 0x00, 0xF0, 0x00, 0x08, 0x03, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD6, 0x00, 0x00, 0x02, 0x08, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD0, 0x00, 0x10, 0x00, 0x08, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD9, 0x00, 0xF5
	.byte 0x51, 0x07, 0x03, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD0, 0x00, 0x0A, 0xC1, 0x04, 0x02, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE0, 0x00, 0xF0, 0xC1, 0x03, 0x02, 0x00, 0xC1, 0xAE, 0x29, 0x00
	.byte 0x02, 0xD0, 0x00, 0xF0, 0x50, 0x06, 0x01, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xE0, 0x00, 0xA0
	.byte 0x41, 0x02, 0x01, 0x00, 0xC1, 0xAE, 0x29, 0x00, 0xA2, 0xE1, 0x00, 0x05, 0x00, 0x05, 0x01, 0x00
	.byte 0xC1, 0xAE, 0x29, 0x00, 0x02, 0xD6, 0x00, 0x00, 0x41, 0x02, 0x01, 0x00

	.global UNK05_021F7A38
UNK05_021F7A38: ; 0x021F7A38
	.byte 0x00, 0x40, 0x10, 0x00

	.global UNK05_021F7A3C
UNK05_021F7A3C: ; 0x021F7A3C
	.byte 0x00, 0x00, 0x08, 0x00

	.global UNK05_021F7A40
UNK05_021F7A40: ; 0x021F7A40
	.byte 0x00, 0x20, 0xFE, 0xFF

	.global UNK05_021F7A44
UNK05_021F7A44: ; 0x021F7A44
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK05_021F7A48
UNK05_021F7A48: ; 0x021F7A48
	.byte 0x00, 0x40, 0x06, 0x00

	.global UNK05_021F7A4C
UNK05_021F7A4C: ; 0x021F7A4C
	.byte 0x00, 0x40, 0x01, 0x00

	.global UNK05_021F7A50
UNK05_021F7A50: ; 0x021F7A50
	.byte 0x04, 0x00, 0x00, 0x00

	.global UNK05_021F7A54
UNK05_021F7A54: ; 0x021F7A54
	.byte 0xFE, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0xC0, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0x40, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0xFD, 0xFF, 0x00, 0xC0, 0x08, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x60, 0xFF, 0xFF, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0xC0, 0xFE, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0xFE, 0xFF, 0x00, 0x40, 0x10, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0xFE, 0xFF, 0x00, 0x00, 0x05, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0xFD, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x08, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x40, 0x06, 0x00
	.byte 0x00, 0xC0, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00
