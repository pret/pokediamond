	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD18_022396A0
MOD18_022396A0: ; 0x022396A0
	push {r3, r4, r5, r6, r7, lr}
	ldr r2, _02239730 ; =0x000008CC
	ldr r4, _02239734 ; =0x02251380
	add r3, r2, #0
	mov r1, #0
	mov r0, #0xff
	add r3, #8
_022396AE:
	ldr r5, [r4]
	add r5, r5, r1
	strb r0, [r5, r2]
	ldr r5, [r4]
	add r5, r5, r1
	add r1, r1, #1
	strb r0, [r5, r3]
	cmp r1, #8
	blt _022396AE
	ldr r0, _02239734 ; =0x02251380
	ldr r1, _02239738 ; =0x000009E4
	ldr r2, [r0]
	mov r3, #1
	strb r3, [r2, r1]
	ldr r4, [r0]
	mov r2, #0
	add r3, r1, #1
	strb r2, [r4, r3]
	ldr r3, [r0]
	mov r4, #0xc4
	add r1, r1, #3
	strb r4, [r3, r1]
	mov r3, #0x81
	lsl r3, r3, #4
	add r4, r3, #0
	add r1, r2, #0
	add r5, r2, #0
	add r4, #8
_022396E6:
	ldr r6, [r0]
	add r2, r2, #1
	add r6, r6, r1
	str r5, [r6, r3]
	ldr r6, [r0]
	add r6, r6, r1
	add r1, #0xc
	strb r5, [r6, r4]
	cmp r2, #8
	blt _022396E6
	ldr r6, _02239734 ; =0x02251380
	mov r7, #0
_022396FE:
	add r0, r5, #0
	mov r1, #0xd
	bl _s32_div_f
	add r4, r0, #0
	mov r1, #0xd
	add r0, r5, #0
	mul r4, r1
	bl _s32_div_f
	ldr r0, [r6]
	add r5, r5, #1
	add r0, r0, r4
	add r2, r1, r0
	ldr r0, _0223973C ; =0x000008DC
	strb r7, [r2, r0]
	ldr r0, [r6]
	add r0, r0, r4
	add r2, r1, r0
	mov r1, #2
	ldr r0, _02239740 ; =0x0000095E
	cmp r5, #0x82
	strb r1, [r2, r0]
	blt _022396FE
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239730: .word 0x000008CC
_02239734: .word MOD18_02251380
_02239738: .word 0x000009E4
_0223973C: .word 0x000008DC
_02239740: .word 0x0000095E
	thumb_func_end MOD18_022396A0

	thumb_func_start MOD18_02239744
MOD18_02239744: ; 0x02239744
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r1, _02239834 ; =0x02251380
	ldr r2, [r1]
	cmp r2, #0
	bne _02239830
	mov r2, #0x9f
	str r0, [r1]
	mov r1, #0
	lsl r2, r2, #4
	bl MI_CpuFill8
	ldr r0, _02239834 ; =0x02251380
	ldr r0, [r0]
	add r0, #8
	bl FUN_020312BC
	ldr r5, _02239834 ; =0x02251380
	mov r2, #0
	ldr r0, [r5]
	ldr r7, _02239838 ; =0x0000020A
	str r4, [r0]
	ldr r0, _0223983C ; =0x0000FFFF
	add r3, r2, #0
	mov r1, #0xff
_02239778:
	ldr r4, [r5]
	add r2, r2, #1
	add r6, r4, r3
	mov r4, #0x83
	lsl r4, r4, #2
	strb r1, [r6, r4]
	ldr r4, [r5]
	add r6, r4, r3
	mov r4, #0x82
	lsl r4, r4, #2
	strh r0, [r6, r4]
	ldr r4, [r5]
	add r4, r4, r3
	add r3, r3, #6
	strh r0, [r4, r7]
	cmp r2, #0xfa
	blt _02239778
	bl MOD18_022396A0
	ldr r1, _02239834 ; =0x02251380
	mov r3, #0
	mov r0, #0x9e
	ldr r2, [r1]
	mvn r3, r3
	lsl r0, r0, #4
	str r3, [r2, r0]
	ldr r0, [r1]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r4, r0, #0
	bl FUN_02026648
	cmp r0, #0
	beq _02239828
	add r0, r4, #0
	bl FUN_02025D40
	str r0, [sp, #4]
	ldr r0, _02239840 ; =0x5D588B65
	mov r5, #0
	str r0, [sp, #8]
	ldr r0, _02239844 ; =0x00269EC3
	str r0, [sp, #0xc]
_022397D2:
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_020265B8
	add r5, r5, #1
	cmp r5, #0xff
	blt _022397D2
	mov r5, #0
	add r6, r5, #0
_022397E4:
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	add r3, r6, #0
	str r6, [sp]
	bl FUN_0202630C
	add r5, r5, #1
	cmp r5, #0x40
	blt _022397E4
	add r0, sp, #4
	bl MOD18_0223D298
	mov r1, #0xa
	bl _s32_div_f
	mov r1, #0x18
	sub r6, r1, r0
	mov r5, #0
	cmp r6, #0
	ble _0223981E
	add r7, sp, #4
_02239810:
	add r0, r7, #0
	add r1, r5, #0
	bl MOD18_02239994
	add r5, r5, #1
	cmp r5, r6
	blt _02239810
_0223981E:
	add r0, r4, #0
	bl FUN_02026654
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02239828:
	bl MOD18_02239D94
	bl MOD18_0223F174
_02239830:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239834: .word MOD18_02251380
_02239838: .word 0x0000020A
_0223983C: .word 0x0000FFFF
_02239840: .word 0x5D588B65
_02239844: .word 0x00269EC3
	thumb_func_end MOD18_02239744

	thumb_func_start MOD18_02239848
MOD18_02239848: ; 0x02239848
	mov r0, #0x9f
	lsl r0, r0, #4
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02239848

	thumb_func_start MOD18_02239850
MOD18_02239850: ; 0x02239850
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02239850

	thumb_func_start MOD18_02239854
MOD18_02239854: ; 0x02239854
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02239854

	thumb_func_start MOD18_02239858
MOD18_02239858: ; 0x02239858
	push {r3, lr}
	ldr r0, _022398A8 ; =0x02251380
	ldr r1, [r0]
	cmp r1, #0
	beq _022398A4
	ldr r0, _022398AC ; =0x0000087C
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02239896
	bl FUN_0200CAB4
	ldr r0, _022398A8 ; =0x02251380
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _022398AC ; =0x0000087C
	str r2, [r1, r0]
	bl MOD18_0223D638
	bl MOD18_0224DD94
	ldr r0, _022398A8 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _022398B0 ; =0x000007E4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02239892
	mov r1, #4
	bl FUN_020021EC
_02239892:
	bl FUN_0204F7FC
_02239896:
	ldr r0, _022398A8 ; =0x02251380
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, _022398A8 ; =0x02251380
	mov r1, #0
	str r1, [r0]
_022398A4:
	pop {r3, pc}
	nop
_022398A8: .word MOD18_02251380
_022398AC: .word 0x0000087C
_022398B0: .word 0x000007E4
	thumb_func_end MOD18_02239858

	thumb_func_start MOD18_022398B4
MOD18_022398B4: ; 0x022398B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrh r0, [r1]
	ldrh r1, [r1, #2]
	bl MOD18_02239DEC
	add r4, r0, #0
	add r0, sp, #0
	strb r5, [r0]
	beq _022398FE
	ldrb r0, [r4, #4]
	cmp r0, #0xff
	bne _022398FE
	add r0, r5, #0
	bl FUN_0204F210
	cmp r0, #0
	beq _022398DC
	mov r0, #1
	pop {r3, r4, r5, pc}
_022398DC:
	mov r0, #0x40
	add r1, sp, #0
	mov r2, #1
	bl FUN_02030BC4
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	ldr r0, _02239904 ; =0x02251380
	ldr r1, [r0]
	lsl r0, r5, #2
	add r1, r1, r0
	ldr r0, _02239908 ; =0x000007E8
	str r4, [r1, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022398FE:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02239904: .word MOD18_02251380
_02239908: .word 0x000007E8
	thumb_func_end MOD18_022398B4

	thumb_func_start MOD18_0223990C
MOD18_0223990C: ; 0x0223990C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _02239924
	mov r0, #0
	pop {r4, r5, r6, pc}
_02239924:
	ldr r0, _02239990 ; =0x000001DE
	cmp r4, r0
	ble _0223992E
	mov r0, #0
	pop {r4, r5, r6, pc}
_0223992E:
	cmp r5, r0
	ble _02239936
	mov r0, #0
	pop {r4, r5, r6, pc}
_02239936:
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #0
	bl FUN_0204A6B4
	cmp r0, #0
	beq _0223998C
	add r0, r6, #0
	add r1, r5, #0
	add r2, r4, #1
	bl FUN_0204A6B4
	cmp r0, #0
	bne _02239956
	mov r0, #1
	pop {r4, r5, r6, pc}
_02239956:
	add r0, r6, #0
	add r1, r5, #0
	sub r2, r4, #1
	bl FUN_0204A6B4
	cmp r0, #0
	bne _02239968
	mov r0, #1
	pop {r4, r5, r6, pc}
_02239968:
	add r0, r6, #0
	add r1, r5, #1
	add r2, r4, #0
	bl FUN_0204A6B4
	cmp r0, #0
	bne _0223997A
	mov r0, #1
	pop {r4, r5, r6, pc}
_0223997A:
	add r0, r6, #0
	sub r1, r5, #1
	add r2, r4, #0
	bl FUN_0204A6B4
	cmp r0, #0
	bne _0223998C
	mov r0, #1
	pop {r4, r5, r6, pc}
_0223998C:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02239990: .word 0x000001DE
	thumb_func_end MOD18_0223990C

	thumb_func_start MOD18_02239994
MOD18_02239994: ; 0x02239994
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r5, r0, #0
	ldr r0, _02239BA8 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	str r0, [sp, #0x10]
	ldr r0, _02239BA8 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0x28]
	bl FUN_020344FC
	sub r0, r0, #2
	lsl r0, r0, #0x15
	lsr r6, r0, #0x10
	ldr r0, _02239BA8 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0x28]
	bl FUN_0203450C
	sub r0, r0, #2
	lsl r0, r0, #0x15
	lsr r4, r0, #0x10
_022399CC:
	ldr r1, [r5, #4]
	ldr r0, [r5]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	cmp r6, #0
	ldr r0, [r5]
	bne _022399E2
	lsr r1, r0, #0x10
	b _022399EA
_022399E2:
	lsr r1, r0, #0x10
	add r2, r1, #0
	mul r2, r6
	lsr r1, r2, #0x10
_022399EA:
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	add r1, #0x20
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	str r1, [sp, #0xc]
	ldr r1, [r5, #4]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	cmp r4, #0
	ldr r0, [r5]
	bne _02239A0A
	lsr r0, r0, #0x10
	b _02239A12
_02239A0A:
	lsr r0, r0, #0x10
	add r1, r0, #0
	mul r1, r4
	lsr r0, r1, #0x10
_02239A12:
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r0, #0x40
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	ldr r0, _02239BA8 ; =0x02251380
	ldr r1, [sp, #0xc]
	ldr r0, [r0]
	add r2, r7, #0
	ldr r0, [r0]
	bl MOD18_0223990C
	cmp r0, #0
	beq _022399CC
	ldr r1, [r5, #4]
	ldr r0, [r5]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	lsr r1, r0, #0x10
	mov r0, #6
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r0, r0, #6
	str r0, [sp, #0x20]
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x20]
	cmp r0, #0
	ble _02239AEE
_02239A54:
	mov r0, #0
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
_02239A5A:
	ldr r1, [r5, #4]
	ldr r0, [r5]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	lsr r2, r0, #0x10
	mov r1, #0x14
	mul r1, r2
	lsr r1, r1, #0x10
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldr r1, [sp, #0xc]
	str r0, [r5]
	add r1, r1, r2
	sub r1, #0xa
	lsl r1, r1, #0x10
	lsr r4, r1, #0x10
	ldr r1, [r5, #4]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	lsr r1, r0, #0x10
	mov r0, #0x14
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r0, r7, r0
	sub r0, #0xa
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, _02239BA8 ; =0x02251380
	add r1, r4, #0
	ldr r0, [r0]
	add r2, r6, #0
	ldr r0, [r0]
	bl MOD18_0223990C
	cmp r0, #0
	beq _02239AB2
	mov r0, #1
	str r0, [sp, #0x14]
	b _02239ABC
_02239AB2:
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0x64
	blt _02239A5A
_02239ABC:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _02239AE2
	bl MOD18_02239C58
	cmp r0, #0
	beq _02239AEE
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_02239CA0
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x10]
	add r1, r4, #0
	add r2, r6, #0
	bl FUN_02026554
	ldr r1, [sp, #0x24]
	strb r0, [r1, #5]
_02239AE2:
	ldr r0, [sp, #0x1c]
	add r1, r0, #1
	ldr r0, [sp, #0x20]
	str r1, [sp, #0x1c]
	cmp r1, r0
	blt _02239A54
_02239AEE:
	ldr r1, [r5, #4]
	ldr r0, [r5]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	lsr r1, r0, #0x10
	mov r0, #6
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, [sp, #8]
	cmp r0, #0
	ble _02239BA2
_02239B12:
	mov r0, #0
	str r0, [sp]
_02239B16:
	ldr r1, [r5, #4]
	ldr r0, [r5]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	lsr r2, r0, #0x10
	mov r1, #0x14
	mul r1, r2
	lsr r1, r1, #0x10
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldr r1, [sp, #0xc]
	str r0, [r5]
	add r1, r1, r2
	sub r1, #0xa
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	ldr r1, [r5, #4]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	lsr r1, r0, #0x10
	mov r0, #0x14
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r0, r7, r0
	sub r0, #0xa
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, _02239BA8 ; =0x02251380
	add r1, r6, #0
	ldr r0, [r0]
	add r2, r4, #0
	ldr r0, [r0]
	bl FUN_0204A6B4
	cmp r0, #0
	bne _02239B8C
	ldr r3, _02239BA8 ; =0x02251380
	add r1, r4, #0
	ldr r4, [r3]
	ldr r3, _02239BAC ; =0x000009EC
	add r0, r6, #0
	ldrb r3, [r4, r3]
	add r2, r5, #0
	bl MOD18_0223F0C8
	cmp r0, #0
	beq _02239B8C
	ldr r0, _02239BA8 ; =0x02251380
	ldr r2, [r0]
	ldr r0, _02239BAC ; =0x000009EC
	ldrb r1, [r2, r0]
	add r1, r1, #1
	strb r1, [r2, r0]
	b _02239B96
_02239B8C:
	ldr r0, [sp]
	add r0, r0, #1
	str r0, [sp]
	cmp r0, #0x64
	blt _02239B16
_02239B96:
	ldr r0, [sp, #4]
	add r1, r0, #1
	ldr r0, [sp, #8]
	str r1, [sp, #4]
	cmp r1, r0
	blt _02239B12
_02239BA2:
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239BA8: .word MOD18_02251380
_02239BAC: .word 0x000009EC
	thumb_func_end MOD18_02239994

	thumb_func_start MOD18_02239BB0
MOD18_02239BB0: ; 0x02239BB0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp]
	ldr r0, _02239C54 ; =0x02251380
	str r1, [sp, #4]
	ldr r0, [r0]
	add r5, r2, #0
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	mov r4, #0
	str r0, [sp, #8]
	str r4, [sp, #0xc]
_02239BCC:
	ldr r1, [r5, #4]
	ldr r0, [r5]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	lsr r2, r0, #0x10
	mov r1, #0x14
	mul r1, r2
	lsr r1, r1, #0x10
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldr r1, [sp]
	str r0, [r5]
	add r1, r1, r2
	sub r1, #0xa
	lsl r1, r1, #0x10
	lsr r6, r1, #0x10
	ldr r1, [r5, #4]
	ldr r2, [r5, #8]
	mul r0, r1
	add r0, r2, r0
	str r0, [r5]
	lsr r1, r0, #0x10
	mov r0, #0x14
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #4]
	add r0, r0, r1
	sub r0, #0xa
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	ldr r0, _02239C54 ; =0x02251380
	add r1, r6, #0
	ldr r0, [r0]
	add r2, r7, #0
	ldr r0, [r0]
	bl MOD18_0223990C
	cmp r0, #0
	beq _02239C26
	mov r0, #1
	str r0, [sp, #0xc]
	b _02239C2C
_02239C26:
	add r4, r4, #1
	cmp r4, #0x64
	blt _02239BCC
_02239C2C:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _02239C50
	bl MOD18_02239C58
	cmp r0, #0
	beq _02239C50
	add r0, r6, #0
	add r1, r7, #0
	bl MOD18_02239CA0
	add r4, r0, #0
	ldr r0, [sp, #8]
	add r1, r6, #0
	add r2, r7, #0
	bl FUN_02026554
	strb r0, [r4, #5]
_02239C50:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239C54: .word MOD18_02251380
	thumb_func_end MOD18_02239BB0

	thumb_func_start MOD18_02239C58
MOD18_02239C58: ; 0x02239C58
	push {r4, r5, r6, r7}
	ldr r1, _02239C94 ; =0x02251380
	ldr r3, _02239C98 ; =0x0000020A
	ldr r2, [r1]
	ldr r4, _02239C9C ; =0x0000FFFF
	mov r0, #0
	add r1, r2, #0
	sub r5, r3, #2
	add r6, r4, #0
_02239C6A:
	ldrh r7, [r1, r5]
	cmp r7, r6
	bne _02239C86
	ldrh r7, [r1, r3]
	cmp r7, r4
	bne _02239C86
	mov r1, #0x82
	lsl r1, r1, #2
	add r2, r2, r1
	mov r1, #6
	mul r1, r0
	add r0, r2, r1
	pop {r4, r5, r6, r7}
	bx lr
_02239C86:
	add r0, r0, #1
	add r1, r1, #6
	cmp r0, #0xfa
	blt _02239C6A
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02239C94: .word MOD18_02251380
_02239C98: .word 0x0000020A
_02239C9C: .word 0x0000FFFF
	thumb_func_end MOD18_02239C58

	thumb_func_start MOD18_02239CA0
MOD18_02239CA0: ; 0x02239CA0
	push {r3, r4, r5, r6, r7, lr}
	mov lr, r1
	mov r1, #0xf
	str r0, [sp]
	lsl r1, r1, #6
	mov r0, lr
	mul r1, r0
	ldr r0, [sp]
	mov r6, #0
	add r5, r0, r1
	ldr r0, _02239D80 ; =0x02251380
	mvn r6, r6
	ldr r3, [r0]
	mov r2, #0
	mov ip, r3
	lsr r7, r6, #0x10
_02239CC0:
	mov r0, #0x82
	lsl r0, r0, #2
	ldrh r1, [r3, r0]
	cmp r1, r7
	beq _02239CE4
	add r0, r0, #2
	ldrh r0, [r3, r0]
	ldr r4, _02239D84 ; =0x0000FFFF
	cmp r0, r4
	beq _02239CE4
	mov r4, #0xf
	lsl r4, r4, #6
	mul r4, r0
	add r0, r1, r4
	cmp r5, r0
	bge _02239D08
	add r6, r2, #0
	b _02239D10
_02239CE4:
	mov r0, #6
	mul r0, r2
	mov r1, ip
	add r2, r1, r0
	mov r3, #0x82
	ldr r1, [sp]
	lsl r3, r3, #2
	strh r1, [r2, r3]
	ldr r4, _02239D80 ; =0x02251380
	add r2, r3, #2
	ldr r1, [r4]
	add r5, r1, r0
	mov r1, lr
	strh r1, [r5, r2]
	ldr r1, [r4]
	add r1, r1, r3
	add r0, r1, r0
	pop {r3, r4, r5, r6, r7, pc}
_02239D08:
	add r2, r2, #1
	add r3, r3, #6
	cmp r2, #0xfa
	blt _02239CC0
_02239D10:
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _02239D6E
	mov r1, #0xf8
	cmp r6, #0xf8
	bgt _02239D52
	mov r0, #0x5d
	ldr r3, _02239D80 ; =0x02251380
	ldr r7, _02239D88 ; =0x00000213
	lsl r0, r0, #4
_02239D26:
	ldr r2, [r3]
	sub r1, r1, #1
	add r5, r2, r0
	mov r2, #0x82
	lsl r2, r2, #2
	ldrh r4, [r5, r2]
	add r2, r2, #6
	strh r4, [r5, r2]
	ldr r2, [r3]
	add r5, r2, r0
	ldr r2, _02239D8C ; =0x0000020A
	ldrh r4, [r5, r2]
	add r2, r2, #6
	strh r4, [r5, r2]
	ldr r2, [r3]
	ldr r4, _02239D90 ; =0x0000020D
	add r2, r2, r0
	ldrb r4, [r2, r4]
	sub r0, r0, #6
	strb r4, [r2, r7]
	cmp r1, r6
	bge _02239D26
_02239D52:
	ldr r3, _02239D80 ; =0x02251380
	mov r0, #6
	ldr r1, [r3]
	mul r0, r6
	add r4, r1, r0
	mov r2, #0x82
	ldr r1, [sp]
	lsl r2, r2, #2
	strh r1, [r4, r2]
	ldr r1, [r3]
	add r3, r1, r0
	add r1, r2, #2
	mov r0, lr
	strh r0, [r3, r1]
_02239D6E:
	ldr r0, _02239D80 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x82
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #6
	mul r0, r6
	add r0, r1, r0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02239D80: .word MOD18_02251380
_02239D84: .word 0x0000FFFF
_02239D88: .word 0x00000213
_02239D8C: .word 0x0000020A
_02239D90: .word 0x0000020D
	thumb_func_end MOD18_02239CA0

	thumb_func_start MOD18_02239D94
MOD18_02239D94: ; 0x02239D94
	push {r4, r5, r6, lr}
	ldr r0, _02239DD4 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r6, r0, #0
	mov r5, #0
_02239DA6:
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_020265E0
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_02026600
	add r1, r0, #0
	cmp r4, #0
	beq _02239DCA
	cmp r1, #0
	beq _02239DCA
	add r0, r4, #0
	bl MOD18_02239CA0
	strb r5, [r0, #5]
_02239DCA:
	add r5, r5, #1
	cmp r5, #0xff
	blt _02239DA6
	pop {r4, r5, r6, pc}
	nop
_02239DD4: .word MOD18_02251380
	thumb_func_end MOD18_02239D94

	thumb_func_start MOD18_02239DD8
MOD18_02239DD8: ; 0x02239DD8
	push {r3, lr}
	bl FUN_02031190
	cmp r0, #0
	bne _02239DEA
	bl MOD18_0223C9B8
	bl MOD18_0223C898
_02239DEA:
	pop {r3, pc}
	thumb_func_end MOD18_02239DD8

	thumb_func_start MOD18_02239DEC
MOD18_02239DEC: ; 0x02239DEC
	push {r4, r5, r6, r7}
	ldr r3, _02239E24 ; =0x02251380
	ldr r5, _02239E28 ; =0x0000020A
	ldr r4, [r3]
	mov r2, #0
	add r3, r4, #0
	sub r6, r5, #2
_02239DFA:
	ldrh r7, [r3, r6]
	cmp r0, r7
	bne _02239E16
	ldrh r7, [r3, r5]
	cmp r1, r7
	bne _02239E16
	mov r0, #0x82
	lsl r0, r0, #2
	add r1, r4, r0
	mov r0, #6
	mul r0, r2
	add r0, r1, r0
	pop {r4, r5, r6, r7}
	bx lr
_02239E16:
	add r2, r2, #1
	add r3, r3, #6
	cmp r2, #0xfa
	blt _02239DFA
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_02239E24: .word MOD18_02251380
_02239E28: .word 0x0000020A
	thumb_func_end MOD18_02239DEC

	thumb_func_start MOD18_02239E2C
MOD18_02239E2C: ; 0x02239E2C
	push {r3, r4, r5, r6, r7, lr}
	add r2, r1, #0
	add r6, r1, #0
	str r2, [sp]
	add r2, #0x50
	add r4, r0, #0
	add r7, r0, #0
	sub r6, #0x50
	str r2, [sp]
	sub r4, #0x50
	add r7, #0x50
	mov r5, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _02239E50
	sub r0, r5, #1
	pop {r3, r4, r5, r6, r7, pc}
_02239E50:
	cmp r4, #0x40
	bge _02239E56
	mov r4, #0x40
_02239E56:
	mov r0, #2
	lsl r0, r0, #8
	cmp r7, r0
	ble _02239E60
	add r7, r0, #0
_02239E60:
	cmp r6, #0x20
	bge _02239E66
	mov r6, #0x20
_02239E66:
	mov r1, #0x1e
	ldr r0, [sp]
	lsl r1, r1, #4
	cmp r0, r1
	ble _02239E72
	str r1, [sp]
_02239E72:
	ldr r0, _02239EF4 ; =0x02251380
	mov r2, #0
	ldr r3, [r0]
_02239E78:
	ldr r0, _02239EF8 ; =0x0000020A
	ldrh r1, [r3, r0]
	cmp r1, r6
	blt _02239E96
	ldr r0, [sp]
	cmp r1, r0
	bgt _02239E96
	mov r0, #0x82
	lsl r0, r0, #2
	ldrh r0, [r3, r0]
	cmp r0, r4
	ble _02239E96
	cmp r0, r7
	bge _02239E96
	add r5, r5, #1
_02239E96:
	add r2, r2, #1
	add r3, r3, #6
	cmp r2, #0xfa
	blt _02239E78
	cmp r5, #0
	bne _02239EA8
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_02239EA8:
	bl LCRandom
	add r1, r5, #0
	bl _s32_div_f
	ldr r0, _02239EF4 ; =0x02251380
	mov r3, #0
	ldr r2, [r0]
	mov ip, r1
	add r5, r3, #0
_02239EBC:
	ldr r0, _02239EF8 ; =0x0000020A
	ldrh r1, [r2, r0]
	cmp r1, r6
	blt _02239EE4
	ldr r0, [sp]
	cmp r1, r0
	bgt _02239EE4
	mov r0, #0x82
	lsl r0, r0, #2
	ldrh r0, [r2, r0]
	cmp r0, r4
	ble _02239EE4
	cmp r0, r7
	bge _02239EE4
	mov r0, ip
	cmp r3, r0
	bne _02239EE2
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_02239EE2:
	add r3, r3, #1
_02239EE4:
	add r5, r5, #1
	add r2, r2, #6
	cmp r5, #0xfa
	blt _02239EBC
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02239EF4: .word MOD18_02251380
_02239EF8: .word 0x0000020A
	thumb_func_end MOD18_02239E2C

	thumb_func_start MOD18_02239EFC
MOD18_02239EFC: ; 0x02239EFC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02239F2C ; =0x02251380
	ldr r1, [r0]
	ldr r0, _02239F30 ; =0x000007E4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02239F12
	mov r1, #4
	bl FUN_020021EC
_02239F12:
	ldr r1, _02239F2C ; =0x02251380
	ldr r0, _02239F30 ; =0x000007E4
	ldr r2, [r1]
	mov r3, #0
	str r3, [r2, r0]
	ldr r1, [r1]
	add r0, #0x98
	str r3, [r1, r0]
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}
	nop
_02239F2C: .word MOD18_02251380
_02239F30: .word 0x000007E4
	thumb_func_end MOD18_02239EFC

	thumb_func_start MOD18_02239F34
MOD18_02239F34: ; 0x02239F34
	push {r4, lr}
	add r4, r2, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _02239F84
	bl FUN_02030FE0
	cmp r0, #0
	beq _02239F84
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x13
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r2, _02239F88 ; =0x02251380
	mov r1, #0x9e
	ldr r3, [r2]
	lsl r1, r1, #4
	str r0, [r3, r1]
	ldr r1, [r2]
	ldr r0, _02239F8C ; =MOD18_02239F98
	mov r2, #0
	bl FUN_0200CA44
	ldr r2, _02239F88 ; =0x02251380
	ldr r1, _02239F90 ; =0x0000087C
	ldr r3, [r2]
	str r0, [r3, r1]
	ldr r2, [r2]
	mov r0, #0
	ldr r1, [r2, r1]
	ldr r2, _02239F94 ; =MOD18_02239EFC
	bl MOD18_0223E688
	bl FUN_0204F7E4
_02239F84:
	pop {r4, pc}
	nop
_02239F88: .word MOD18_02251380
_02239F8C: .word MOD18_02239F98
_02239F90: .word 0x0000087C
_02239F94: .word MOD18_02239EFC
	thumb_func_end MOD18_02239F34

	thumb_func_start MOD18_02239F98
MOD18_02239F98: ; 0x02239F98
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _0223A044 ; =0x02251380
	ldr r2, [r0]
	mov r0, #0x9e
	lsl r0, r0, #4
	ldr r1, [r2, r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _02239FEA
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223A03E
	mov r0, #4
	str r0, [sp]
	ldr r0, _0223A044 ; =0x02251380
	ldr r1, _0223A048 ; =0x0224FFE6
	ldr r0, [r0]
	ldr r2, _0223A04C ; =0x000003D9
	ldr r0, [r0]
	mov r3, #0xb
	ldr r0, [r0, #8]
	bl Std_CreateYesNoMenu
	ldr r2, _0223A044 ; =0x02251380
	ldr r1, _0223A050 ; =0x000007E4
	ldr r3, [r2]
	add sp, #8
	str r0, [r3, r1]
	mov r3, #0
	mov r0, #0x9e
	ldr r1, [r2]
	mvn r3, r3
	lsl r0, r0, #4
	str r3, [r1, r0]
	pop {r4, pc}
_02239FEA:
	ldr r0, _0223A050 ; =0x000007E4
	mov r1, #4
	ldr r0, [r2, r0]
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223A03E
	cmp r0, #0
	add r0, sp, #4
	bne _0223A008
	mov r1, #1
	strb r1, [r0]
	b _0223A010
_0223A008:
	mov r1, #0
	strb r1, [r0]
	bl FUN_0204F7FC
_0223A010:
	mov r0, #0x41
	add r1, sp, #4
	bl FUN_020311D0
	ldr r0, _0223A044 ; =0x02251380
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _0223A050 ; =0x000007E4
	str r2, [r1, r0]
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r4, #0
	bl FUN_0200CAB4
	bl MOD18_0223E6A0
	ldr r0, _0223A044 ; =0x02251380
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _0223A054 ; =0x0000087C
	str r2, [r1, r0]
_0223A03E:
	add sp, #8
	pop {r4, pc}
	nop
_0223A044: .word MOD18_02251380
_0223A048: .word MOD18_0224FFE6
_0223A04C: .word 0x000003D9
_0223A050: .word 0x000007E4
_0223A054: .word 0x0000087C
	thumb_func_end MOD18_02239F98

	thumb_func_start MOD18_0223A058
MOD18_0223A058: ; 0x0223A058
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _0223A0DC ; =0x02251380
	add r7, r2, #0
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	str r0, [sp]
	ldr r0, _0223A0DC ; =0x02251380
	lsl r6, r5, #2
	ldr r1, [r0]
	ldr r0, _0223A0E0 ; =0x000007E8
	add r2, r1, r6
	ldr r4, [r2, r0]
	add r0, sp, #4
	strb r5, [r0]
	ldrb r0, [r7]
	cmp r0, #0
	beq _0223A0C4
	cmp r4, #0
	beq _0223A0C4
	ldrb r0, [r4, #4]
	cmp r0, #0xff
	bne _0223A0D6
	mov r0, #0x42
	add r1, sp, #4
	mov r2, #1
	bl FUN_02030BC4
	mov r0, #0xff
	strb r0, [r4, #4]
	ldr r0, _0223A0E4 ; =0x0000FFFF
	strh r0, [r4]
	strh r0, [r4, #2]
	ldrb r1, [r4, #5]
	ldr r0, [sp]
	bl FUN_020265B8
	ldr r1, _0223A0DC ; =0x02251380
	mov r3, #1
	ldr r0, [r1]
	add sp, #8
	add r2, r0, r5
	ldr r0, _0223A0E8 ; =0x00000808
	strb r3, [r2, r0]
	ldr r1, [r1]
	mov r2, #0
	add r1, r1, r6
	sub r0, #0x20
	str r2, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_0223A0C4:
	add r2, r1, r5
	ldr r1, _0223A0E8 ; =0x00000808
	mov r0, #0
	strb r0, [r2, r1]
	ldr r2, _0223A0DC ; =0x02251380
	sub r1, #0x20
	ldr r2, [r2]
	add r2, r2, r6
	str r0, [r2, r1]
_0223A0D6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223A0DC: .word MOD18_02251380
_0223A0E0: .word 0x000007E8
_0223A0E4: .word 0x0000FFFF
_0223A0E8: .word 0x00000808
	thumb_func_end MOD18_0223A058

	thumb_func_start MOD18_0223A0EC
MOD18_0223A0EC: ; 0x0223A0EC
	push {r4, lr}
	add r4, r2, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _0223A108
	bl FUN_0204F7E4
	ldr r0, _0223A118 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD18_0223AC24
_0223A108:
	ldr r0, _0223A118 ; =0x02251380
	mov r2, #1
	ldr r1, [r0]
	ldrb r0, [r4]
	add r1, r1, r0
	ldr r0, _0223A11C ; =0x000008C4
	strb r2, [r1, r0]
	pop {r4, pc}
	.align 2, 0
_0223A118: .word MOD18_02251380
_0223A11C: .word 0x000008C4
	thumb_func_end MOD18_0223A0EC

	thumb_func_start MOD18_0223A120
MOD18_0223A120: ; 0x0223A120
	ldr r1, _0223A130 ; =0x02251380
	mov r2, #0
	ldr r1, [r1]
	add r1, r1, r0
	ldr r0, _0223A134 ; =0x00000808
	strb r2, [r1, r0]
	bx lr
	nop
_0223A130: .word MOD18_02251380
_0223A134: .word 0x00000808
	thumb_func_end MOD18_0223A120

	thumb_func_start MOD18_0223A138
MOD18_0223A138: ; 0x0223A138
	push {r3, lr}
	add r1, sp, #0
	strb r0, [r1]
	ldrb r0, [r2]
	strb r0, [r1, #1]
	ldrb r0, [r2, #1]
	strb r0, [r1, #2]
	mov r0, #0x45
	add r1, sp, #0
	bl FUN_02030C4C
	pop {r3, pc}
	thumb_func_end MOD18_0223A138

	thumb_func_start MOD18_0223A150
MOD18_0223A150: ; 0x0223A150
	mov r0, #2
	bx lr
	thumb_func_end MOD18_0223A150

	thumb_func_start MOD18_0223A154
MOD18_0223A154: ; 0x0223A154
	push {r3, r4, r5, lr}
	add r5, r2, #0
	ldrb r4, [r5]
	bl FUN_02031190
	cmp r4, r0
	beq _0223A17A
	ldr r1, _0223A17C ; =0x02251380
	ldrb r3, [r5, #1]
	ldr r0, [r1]
	add r2, r0, r4
	ldr r0, _0223A180 ; =0x000008CC
	strb r3, [r2, r0]
	ldr r2, [r1]
	ldrb r1, [r5]
	ldrb r3, [r5, #2]
	add r0, #8
	add r1, r2, r1
	strb r3, [r1, r0]
_0223A17A:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223A17C: .word MOD18_02251380
_0223A180: .word 0x000008CC
	thumb_func_end MOD18_0223A154

	thumb_func_start MOD18_0223A184
MOD18_0223A184: ; 0x0223A184
	mov r0, #3
	bx lr
	thumb_func_end MOD18_0223A184

	thumb_func_start MOD18_0223A188
MOD18_0223A188: ; 0x0223A188
	push {r3, r4, r5, lr}
	sub sp, #0xa8
	ldr r5, _0223A2A4 ; =0x02250080
	add r4, r0, #0
	add r3, sp, #0x80
	mov r2, #5
_0223A194:
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0223A194
	add r0, sp, #0x80
	bl GX_SetBanks
	ldr r5, _0223A2A8 ; =0x02250000
	add r3, sp, #0x70
	add r2, r3, #0
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r2, #0
	bl FUN_02016BBC
	ldr r5, _0223A2AC ; =0x02250010
	add r3, sp, #0x54
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
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x1d
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	ldr r5, _0223A2B0 ; =0x0225002C
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
	mov r0, #1
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x1d
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	ldr r5, _0223A2B4 ; =0x02250048
	add r3, sp, #0x1c
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
	mov r0, #2
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x1d
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	ldr r5, _0223A2B8 ; =0x02250064
	add r3, sp, #0
	ldmia r5!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5]
	mov r1, #3
	str r0, [r3]
	add r0, r4, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #3
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x1d
	bl FUN_02017F18
	add r0, r4, #0
	mov r1, #3
	bl FUN_02018744
	mov r0, #4
	mov r1, #0x20
	mov r2, #0
	mov r3, #0x1d
	bl FUN_02017F18
	mov r0, #0
	mov r1, #0x20
	add r2, r0, #0
	mov r3, #0x1d
	bl FUN_02017F18
	add sp, #0xa8
	pop {r3, r4, r5, pc}
	nop
_0223A2A4: .word MOD18_02250080
_0223A2A8: .word MOD18_02250000
_0223A2AC: .word MOD18_02250010
_0223A2B0: .word MOD18_0225002C
_0223A2B4: .word MOD18_02250048
_0223A2B8: .word MOD18_02250064
	thumb_func_end MOD18_0223A188

	thumb_func_start MOD18_0223A2BC
MOD18_0223A2BC: ; 0x0223A2BC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r2, #0
	add r5, r0, #0
	add r6, r1, #0
	add r7, r3, #0
	cmp r4, #0
	beq _0223A2DE
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020130
	b _0223A2EE
_0223A2DE:
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020130
_0223A2EE:
	cmp r7, #0
	beq _0223A30A
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02020130
	ldr r0, _0223A3C8 ; =0x000006A4
	bl FUN_020054C8
	b _0223A33C
_0223A30A:
	cmp r4, #0
	beq _0223A326
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #3
	bl FUN_02020130
	ldr r0, _0223A3CC ; =0x000006A2
	bl FUN_020054C8
	b _0223A33C
_0223A326:
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #4
	bl FUN_02020130
	ldr r0, _0223A3D0 ; =0x000006A3
	bl FUN_020054C8
_0223A33C:
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	add r5, #8
	lsl r0, r5, #0xc
	add r6, #8
	str r0, [sp]
	lsl r0, r6, #0xc
	str r0, [sp, #4]
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
	ldr r0, [sp, #0x20]
	cmp r0, #0
	beq _0223A3BE
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #5
	bl FUN_02020130
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _0223A3C4 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
_0223A3BE:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223A3C4: .word MOD18_02251380
_0223A3C8: .word 0x000006A4
_0223A3CC: .word 0x000006A2
_0223A3D0: .word 0x000006A3
	thumb_func_end MOD18_0223A2BC

	thumb_func_start MOD18_0223A3D4
MOD18_0223A3D4: ; 0x0223A3D4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	mov r1, #0
	add r5, r0, #0
	mov r0, #0x3a
	add r2, r1, #0
	bl FUN_0200433C
	bl MOD18_022396A0
	mov r0, #1
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r2, #5
	mov r0, #3
	mov r1, #0x1d
	lsl r2, r2, #0x10
	bl FUN_0201681C
	mov r0, #0x1d
	bl FUN_02016B94
	add r4, r0, #0
	ldr r0, _0223A4CC ; =0x02251380
	add r1, r4, #0
	ldr r0, [r0]
	str r4, [r0, #4]
	ldr r0, _0223A4D0 ; =MOD18_0223C6CC
	bl Main_SetVBlankIntrCB
	bl MOD18_0223D638
	add r1, r4, #0
	bl MOD18_0224DBB0
	add r0, r4, #0
	bl MOD18_0223A188
	add r0, r4, #0
	mov r1, #0
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #1
	bl FUN_02018744
	add r0, r4, #0
	mov r1, #2
	bl FUN_02018744
	mov r0, #0
	str r0, [sp]
	mov r0, #0x1d
	str r0, [sp, #4]
	ldr r2, _0223A4D4 ; =0x000001E2
	add r0, r4, #0
	mov r1, #3
	mov r3, #0xa
	bl FUN_0200CD68
	mov r0, #0x60
	str r0, [sp]
	mov r0, #0x1d
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x34
	mov r1, #1
	add r3, r2, #0
	bl FUN_02006930
	mov r1, #0
	str r1, [sp]
	str r1, [sp, #4]
	str r1, [sp, #8]
	mov r0, #0x1d
	str r0, [sp, #0xc]
	mov r0, #0x34
	add r2, r4, #0
	add r3, r1, #0
	bl FUN_0200687C
	mov r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	add r6, r0, #0
	str r3, [sp, #8]
	mov r0, #0x1d
	str r0, [sp, #0xc]
	mov r0, #0x34
	mov r1, #2
	add r2, r4, #0
	bl FUN_020068C8
	mov r3, #0x80
	str r3, [sp]
	mov r0, #0x1d
	str r0, [sp, #4]
	mov r0, #0x32
	mov r1, #0x34
	mov r2, #0
	add r3, #0xc0
	bl FUN_02006930
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl MOD18_0223AF48
	add sp, #0x10
	pop {r4, r5, r6, pc}
	nop
_0223A4CC: .word MOD18_02251380
_0223A4D0: .word MOD18_0223C6CC
_0223A4D4: .word 0x000001E2
	thumb_func_end MOD18_0223A3D4

	thumb_func_start MOD18_0223A4D8
MOD18_0223A4D8: ; 0x0223A4D8
	push {r3, lr}
	sub sp, #0x10
	ldr r0, _0223A55C ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223B9BC
	ldr r0, _0223A55C ; =0x02251380
	mov r1, #1
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl FUN_02017CD0
	ldr r0, _0223A55C ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223B480
	mov r0, #1
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x1d
	str r0, [sp, #0xc]
	ldr r2, _0223A55C ; =0x02251380
	mov r0, #0x37
	ldr r2, [r2]
	mov r1, #9
	ldr r2, [r2, #4]
	mov r3, #2
	bl FUN_0200687C
	ldr r0, _0223A55C ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223B6A4
	mov r0, #0
	mov r1, #3
	bl FUN_020178BC
	mov r0, #1
	mov r1, #2
	bl FUN_020178BC
	mov r0, #2
	mov r1, #1
	bl FUN_020178BC
	mov r0, #3
	mov r1, #0
	bl FUN_020178BC
	bl MOD18_0223C37C
	bl MOD18_0223C570
	ldr r0, _0223A55C ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223BB7C
	add sp, #0x10
	pop {r3, pc}
	nop
_0223A55C: .word MOD18_02251380
	thumb_func_end MOD18_0223A4D8

	thumb_func_start MOD18_0223A560
MOD18_0223A560: ; 0x0223A560
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _0223A648 ; =0x02251380
	mov r1, #0
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl FUN_020178A0
	ldr r0, _0223A648 ; =0x02251380
	mov r1, #1
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl FUN_020178A0
	ldr r0, _0223A648 ; =0x02251380
	mov r1, #2
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl FUN_020178A0
	ldr r0, _0223A648 ; =0x02251380
	mov r1, #3
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl FUN_020178A0
	ldr r0, _0223A648 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009C0C
	ldr r0, _0223A648 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x5b
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009C0C
	ldr r0, _0223A648 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009E04
	ldr r0, _0223A648 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009E04
	mov r6, #0
	ldr r7, _0223A648 ; =0x02251380
	add r4, r6, #0
_0223A5D2:
	ldr r0, [r7]
	add r1, r0, r4
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02008E2C
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _0223A5D2
	mov r4, #0
	add r6, r4, #0
_0223A5EC:
	ldr r0, [r5, #0x18]
	cmp r0, #0
	beq _0223A5F8
	bl FreeToHeap
	str r6, [r5, #0x18]
_0223A5F8:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0223A5EC
	ldr r0, _0223A648 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FD58
	bl FUN_02009FA0
	bl FUN_0201D12C
	bl FUN_0201E08C
	mov r0, #0
	add r1, r0, #0
	bl Main_SetVBlankIntrCB
	ldr r0, _0223A648 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl FreeToHeap
	ldr r0, _0223A648 ; =0x02251380
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #4]
	mov r0, #0x1d
	bl FUN_020168D0
	bl MOD18_0223D638
	ldr r1, _0223A648 ; =0x02251380
	ldr r1, [r1]
	ldr r1, [r1]
	ldr r1, [r1, #8]
	bl MOD18_0224DBB0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223A648: .word MOD18_02251380
	thumb_func_end MOD18_0223A560

	thumb_func_start MOD18_0223A64C
MOD18_0223A64C: ; 0x0223A64C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r6, r0, #0
	ldr r0, [r4]
	ldr r5, [r4, #0x10]
	cmp r0, #0x1b
	bls _0223A65E
	b _0223AC10
_0223A65E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223A66A: ; jump table
	.short _0223A6A2 - _0223A66A - 2 ; case 0
	.short _0223A6BE - _0223A66A - 2 ; case 1
	.short _0223A6E6 - _0223A66A - 2 ; case 2
	.short _0223A704 - _0223A66A - 2 ; case 3
	.short _0223A71C - _0223A66A - 2 ; case 4
	.short _0223A72C - _0223A66A - 2 ; case 5
	.short _0223A73A - _0223A66A - 2 ; case 6
	.short _0223A780 - _0223A66A - 2 ; case 7
	.short _0223A79A - _0223A66A - 2 ; case 8
	.short _0223A7AC - _0223A66A - 2 ; case 9
	.short _0223A7DE - _0223A66A - 2 ; case 10
	.short _0223A81E - _0223A66A - 2 ; case 11
	.short _0223A844 - _0223A66A - 2 ; case 12
	.short _0223A87E - _0223A66A - 2 ; case 13
	.short _0223A8A2 - _0223A66A - 2 ; case 14
	.short _0223A8E4 - _0223A66A - 2 ; case 15
	.short _0223A934 - _0223A66A - 2 ; case 16
	.short _0223A958 - _0223A66A - 2 ; case 17
	.short _0223A9A8 - _0223A66A - 2 ; case 18
	.short _0223A9DC - _0223A66A - 2 ; case 19
	.short _0223AA08 - _0223A66A - 2 ; case 20
	.short _0223AA4C - _0223A66A - 2 ; case 21
	.short _0223AAD6 - _0223A66A - 2 ; case 22
	.short _0223AB28 - _0223A66A - 2 ; case 23
	.short _0223AB58 - _0223A66A - 2 ; case 24
	.short _0223AB94 - _0223A66A - 2 ; case 25
	.short _0223ABAC - _0223A66A - 2 ; case 26
	.short _0223ABDC - _0223A66A - 2 ; case 27
_0223A6A2:
	mov r0, #0
	bl MOD18_02247970
	bl MOD18_0223CC80
	bl FUN_0204CC48
	bl MOD18_022451BC
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A6BE:
	ldr r0, [r5, #0x68]
	bl MOD18_0224484C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #2
	mov r1, #0x10
	mov r2, #0x12
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A6E6:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223A7E8
	ldr r0, [r5, #0x68]
	cmp r0, #0
	bne _0223A7E8
	add r0, r5, #0
	bl FUN_02037394
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A704:
	add r0, r5, #0
	bl FUN_0203739C
	cmp r0, #0
	bne _0223A7E8
	bl FUN_02033ED0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A71C:
	add r0, r4, #0
	bl MOD18_0223A3D4
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A72C:
	bl MOD18_0223A4D8
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A73A:
	bl FUN_02033E74
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x1d
	mov r1, #0x11
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineAToggleLayers
	mov r0, #2
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #8
	mov r1, #1
	bl GX_EngineAToggleLayers
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A780:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223A7E8
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, _0223AB00 ; =0x00000621
	bl FUN_020054C8
	mov r0, #8
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A79A:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x14
	ble _0223A7E8
	mov r0, #9
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A7AC:
	bl MOD18_0223D638
	ldr r2, [r4, #0xc]
	mov r1, #0
	bl MOD18_0224DE5C
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x3e
	add r3, r2, #0
	bl MOD18_0224DCD8
	ldr r1, _0223AB04 ; =0x02251380
	add sp, #0xc
	ldr r2, [r1]
	mov r1, #0x9e
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A7DE:
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	cmp r0, #0x50
	bgt _0223A7EA
_0223A7E8:
	b _0223AC10
_0223A7EA:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r5, r0, #0
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r5, #0
	bl FUN_02026620
	cmp r0, #0
	beq _0223A816
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A816:
	mov r0, #0xd
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A81E:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x55
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r1, _0223AB04 ; =0x02251380
	add sp, #0xc
	ldr r2, [r1]
	mov r1, #0x9e
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A844:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x9e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223A922
	ldr r0, _0223AB08 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _0223A86C
	ldr r0, _0223AB0C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0223A922
_0223A86C:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A87E:
	add r0, r4, #0
	bl MOD18_0223C1F0
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223C078
	add r0, r4, #0
	bl MOD18_0223B2D4
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223A8A2:
	add r0, r4, #0
	bl MOD18_0223B2D4
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	ldr r0, [r4, #8]
	sub r0, r0, #1
	str r0, [r4, #8]
	bne _0223A922
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x40
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r1, _0223AB04 ; =0x02251380
	ldr r2, [r1]
	mov r1, #0x9e
	lsl r1, r1, #4
	str r0, [r2, r1]
	ldr r0, _0223AB10 ; =0x000005E3
	bl FUN_020054C8
	mov r0, #0x3c
	str r0, [r4, #0x4c]
	mov r0, #0xf
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A8E4:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	ldr r0, _0223AB04 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x9e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223A922
	ldr r0, [r4, #0x4c]
	sub r0, r0, #1
	str r0, [r4, #0x4c]
	ldr r0, _0223AB08 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _0223A924
	ldr r0, _0223AB0C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _0223A924
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	beq _0223A924
_0223A922:
	b _0223AC10
_0223A924:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #0x10
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A934:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	add r0, r4, #0
	bl MOD18_0223BEE4
	cmp r0, #0
	beq _0223A950
	mov r0, #0x11
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A950:
	mov r0, #0x12
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A958:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	ldr r0, _0223AB04 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x9e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223AA5A
	ldr r0, _0223AB08 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _0223A98A
	ldr r0, _0223AB0C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0223AA5A
_0223A98A:
	add r0, r4, #0
	bl MOD18_0223BF84
	cmp r0, #0
	beq _0223A9A0
	mov r0, #0x3c
	str r0, [r4, #0x4c]
	mov r0, #0xf
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A9A0:
	mov r0, #0x10
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A9A8:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x1d
	mov r1, #0x10
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223A9DC:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	bl FUN_0200E308
	cmp r0, #0
	beq _0223AA5A
	bl FUN_02033ED0
	add r0, r4, #0
	bl MOD18_0223A560
	add r0, r5, #0
	bl FUN_0204649C
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223AA08:
	add r0, r5, #0
	bl FUN_020464A4
	cmp r0, #0
	beq _0223AA5A
	add r0, r5, #0
	bl MOD18_02244824
	str r0, [r5, #0x68]
	bl FUN_02033E74
	bl FUN_0204F7E4
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x11
	mov r2, #0x13
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4]
	add sp, #0xc
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223AA4C:
	mov r0, #0
	bl FUN_0200E394
	bl FUN_0200E308
	cmp r0, #0
	bne _0223AA5C
_0223AA5A:
	b _0223AC10
_0223AA5C:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F45E8
	mov r3, #0x80
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0x32
	mov r1, #0x34
	mov r2, #0
	add r3, #0xc0
	bl FUN_02006930
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r4, #0x10]
	ldr r2, _0223AB14 ; =0x000003D9
	ldr r0, [r0, #8]
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	bl FUN_0204CC9C
	bl MOD18_022451EC
	bl MOD18_0223CC94
	add r1, r4, #0
	mov r0, #0x43
	add r1, #0x50
	bl FUN_020311D0
	bl FUN_0204F7FC
	ldr r0, _0223AB04 ; =0x02251380
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0x22
	lsl r0, r0, #6
	str r2, [r1, r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r6, #0
	bl FUN_0200CAB4
	mov r0, #1
	bl MOD18_02247970
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223AAD6:
	ldr r1, _0223AB04 ; =0x02251380
	ldr r0, _0223AB18 ; =0x000009E8
	ldr r2, [r1]
	mov r3, #1
	strb r3, [r2, r0]
	ldr r2, [r4, #8]
	sub r2, r2, #1
	str r2, [r4, #8]
	bne _0223AAF2
	ldr r1, [r1]
	mov r2, #0x64
	strb r2, [r1, r0]
	mov r0, #0x17
	str r0, [r4]
_0223AAF2:
	ldr r0, _0223AB04 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223C078
	ldr r0, _0223AB04 ; =0x02251380
	b _0223AB1C
	.align 2, 0
_0223AB00: .word 0x00000621
_0223AB04: .word MOD18_02251380
_0223AB08: .word gMain + 0x40
_0223AB0C: .word gMain
_0223AB10: .word 0x000005E3
_0223AB14: .word 0x000003D9
_0223AB18: .word 0x000009E8
_0223AB1C:
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223AB28:
	ldr r0, _0223AC14 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	mov r0, #0xf
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x1d
	mov r1, #2
	str r0, [sp, #8]
	mov r0, #3
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, _0223AC18 ; =0x000006A1
	bl FUN_020054C8
	mov r0, #0x18
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223AB58:
	bl FUN_0200E308
	cmp r0, #0
	beq _0223AB86
	mov r6, #0
	ldr r7, _0223AC14 ; =0x02251380
	add r5, r6, #0
_0223AB66:
	ldr r0, [r7]
	add r1, r0, r5
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #8
	blt _0223AB66
	mov r0, #0x19
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223AB86:
	ldr r0, _0223AC14 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #0x20]
	bl FUN_0201FDEC
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0223AB94:
	mov r0, #1
	add r1, r0, #0
	sub r1, #0x11
	add r2, r1, #0
	mov r3, #7
	str r0, [sp]
	bl FUN_0200A208
	mov r0, #0x1a
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223ABAC:
	mov r0, #0
	bl FUN_0200E388
	mov r0, #0
	bl FUN_0200E394
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x3f
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r1, _0223AC14 ; =0x02251380
	add sp, #0xc
	ldr r2, [r1]
	mov r1, #0x9e
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #0x3c
	str r0, [r4, #0x4c]
	mov r0, #0xf
	str r0, [r4]
	pop {r4, r5, r6, r7, pc}
_0223ABDC:
	ldr r0, _0223AC14 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x9e
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0223AC10
	ldr r0, _0223AC1C ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	bne _0223AC04
	ldr r0, _0223AC20 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0223AC10
_0223AC04:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #0x13
	str r0, [r4]
_0223AC10:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223AC14: .word MOD18_02251380
_0223AC18: .word 0x000006A1
_0223AC1C: .word gMain + 0x40
_0223AC20: .word gMain
	thumb_func_end MOD18_0223A64C

	thumb_func_start MOD18_0223AC24
MOD18_0223AC24: ; 0x0223AC24
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0xb
	bl FUN_02029160
	add r1, r0, #0
	add r0, r5, #0
	add r0, #0x98
	ldr r0, [r0]
	mov r2, #1
	bl FUN_02028AD4
	mov r0, #0xb
	mov r1, #0x54
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x54
	bl MI_CpuFill8
	str r5, [r4, #0x10]
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x1c]
	bl MOD05_021F4608
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205EDBC
	ldr r0, _0223AC78 ; =MOD18_0223A64C
	add r1, r4, #0
	mov r2, #0x64
	bl FUN_0200CA44
	ldr r1, _0223AC7C ; =0x02251380
	ldr r2, [r1]
	mov r1, #0x22
	lsl r1, r1, #6
	str r0, [r2, r1]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223AC78: .word MOD18_0223A64C
_0223AC7C: .word MOD18_02251380
	thumb_func_end MOD18_0223AC24

	thumb_func_start MOD18_0223AC80
MOD18_0223AC80: ; 0x0223AC80
	ldr r0, _0223ACA0 ; =0x02251380
	mov r2, #0
	ldr r3, [r0]
	mov r0, #0x81
	lsl r0, r0, #4
_0223AC8A:
	ldr r1, [r3, r0]
	cmp r1, #0
	bne _0223AC94
	mov r0, #1
	bx lr
_0223AC94:
	add r2, r2, #1
	add r3, #0xc
	cmp r2, #8
	blt _0223AC8A
	mov r0, #0
	bx lr
	.align 2, 0
_0223ACA0: .word MOD18_02251380
	thumb_func_end MOD18_0223AC80

	thumb_func_start MOD18_0223ACA4
MOD18_0223ACA4: ; 0x0223ACA4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	ldr r2, _0223AD10 ; =0x02251380
	mov r3, #0x81
	ldr r2, [r2]
	mov ip, r1
	mov r1, #0
	add r5, r2, #0
	lsl r3, r3, #4
_0223ACB6:
	ldr r4, [r5, r3]
	cmp r4, #0
	bne _0223AD00
	add r4, r0, #0
	mov r3, #0x14
	mul r4, r3
	ldr r3, _0223AD14 ; =0x02250B30
	mov r0, #0xc
	mul r0, r1
	add r5, r3, r4
	mov r3, #0x81
	add r2, r2, r0
	lsl r3, r3, #4
	str r5, [r2, r3]
	ldr r2, _0223AD18 ; =0x02250B3E
	ldrb r6, [r2, r4]
	ldr r4, _0223AD10 ; =0x02251380
	ldr r2, [r4]
	add r5, r2, r0
	add r2, r3, #4
	strb r6, [r5, r2]
	ldr r2, [r4]
	mov r6, ip
	add r5, r2, r0
	add r2, r3, #5
	strb r6, [r5, r2]
	ldr r2, [r4]
	add r5, r2, r0
	add r2, r3, #6
	strb r7, [r5, r2]
	ldr r2, [r4]
	mov r5, #0
	add r0, r2, r0
	add r3, #8
	strb r5, [r0, r3]
	add r0, r1, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223AD00:
	add r1, r1, #1
	add r5, #0xc
	cmp r1, #8
	blt _0223ACB6
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223AD10: .word MOD18_02251380
_0223AD14: .word MOD18_02250B30
_0223AD18: .word MOD18_02250B3C + 2
	thumb_func_end MOD18_0223ACA4

	thumb_func_start MOD18_0223AD1C
MOD18_0223AD1C: ; 0x0223AD1C
	push {r3, r4}
	ldr r3, [r0]
	cmp r3, #0
	bne _0223AD2A
	mov r0, #1
	pop {r3, r4}
	bx lr
_0223AD2A:
	lsr r4, r1, #0x1f
	add r4, r1, r4
	ldrb r0, [r0, #0xc]
	asr r1, r4, #1
	lsr r4, r2, #0x1f
	add r4, r2, r4
	asr r2, r4, #1
	lsr r0, r0, #1
	mul r0, r2
	add r0, r1, r0
	ldrb r0, [r3, r0]
	cmp r0, #0x6f
	beq _0223AD4A
	mov r0, #1
	pop {r3, r4}
	bx lr
_0223AD4A:
	mov r0, #0
	pop {r3, r4}
	bx lr
	thumb_func_end MOD18_0223AD1C

	thumb_func_start MOD18_0223AD50
MOD18_0223AD50: ; 0x0223AD50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	str r0, [sp]
	str r1, [sp, #4]
	add r6, r2, #0
	bl MOD18_0223AC80
	cmp r0, #0
	bne _0223AD68
	add sp, #0x2c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223AD68:
	ldr r0, [sp]
	mov r1, #0x14
	mul r1, r0
	str r1, [sp, #0xc]
	ldr r1, _0223AE74 ; =0x02250B3C
	ldr r0, [sp, #0xc]
	ldrb r0, [r1, r0]
	lsr r1, r0, #1
	ldr r0, [sp, #4]
	add r0, r0, r1
	str r0, [sp, #0x1c]
	ldr r1, _0223AE78 ; =0x02250B3D
	ldr r0, [sp, #0xc]
	ldrb r0, [r1, r0]
	lsr r0, r0, #1
	add r7, r6, r0
	ldr r0, [sp, #0x1c]
	cmp r0, #0xd
	ble _0223AD94
	add sp, #0x2c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223AD94:
	cmp r7, #0xa
	ble _0223AD9E
	add sp, #0x2c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223AD9E:
	ldr r0, [sp, #4]
	str r0, [sp, #0x10]
	add r1, r0, #0
	ldr r0, [sp, #0x1c]
	cmp r1, r0
	bge _0223AE02
	mov r0, #0xd
	mul r0, r6
	str r0, [sp, #0x20]
_0223ADB0:
	add r4, r6, #0
	cmp r6, r7
	bge _0223ADF6
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #4]
	ldr r5, [sp, #0x20]
	sub r0, r1, r0
	lsl r0, r0, #1
	str r0, [sp, #0x14]
_0223ADC2:
	ldr r1, _0223AE7C ; =0x02250B30
	ldr r0, [sp, #0xc]
	sub r2, r4, r6
	add r0, r1, r0
	ldr r1, [sp, #0x14]
	lsl r2, r2, #1
	bl MOD18_0223AD1C
	cmp r0, #0
	beq _0223ADEE
	ldr r0, _0223AE80 ; =0x02251380
	ldr r1, [r0]
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r1, r5, r0
	ldr r0, _0223AE84 ; =0x000008DC
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223ADEE
	add sp, #0x2c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223ADEE:
	add r4, r4, #1
	add r5, #0xd
	cmp r4, r7
	blt _0223ADC2
_0223ADF6:
	ldr r0, [sp, #0x10]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [sp, #0x10]
	cmp r1, r0
	blt _0223ADB0
_0223AE02:
	ldr r0, [sp]
	ldr r1, [sp, #4]
	add r2, r6, #0
	bl MOD18_0223ACA4
	ldr r1, [sp, #4]
	str r1, [sp, #8]
	add r2, r1, #0
	ldr r1, [sp, #0x1c]
	cmp r2, r1
	bge _0223AE6E
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x28]
	mov r0, #0xd
	mul r0, r6
	str r0, [sp, #0x24]
_0223AE24:
	add r5, r6, #0
	cmp r6, r7
	bge _0223AE62
	ldr r1, [sp, #8]
	ldr r0, [sp, #4]
	ldr r4, [sp, #0x24]
	sub r0, r1, r0
	lsl r0, r0, #1
	str r0, [sp, #0x18]
_0223AE36:
	ldr r1, _0223AE7C ; =0x02250B30
	ldr r0, [sp, #0xc]
	sub r2, r5, r6
	add r0, r1, r0
	ldr r1, [sp, #0x18]
	lsl r2, r2, #1
	bl MOD18_0223AD1C
	cmp r0, #0
	beq _0223AE5A
	ldr r0, _0223AE80 ; =0x02251380
	ldr r1, [r0]
	ldr r0, [sp, #8]
	add r0, r0, r1
	add r2, r4, r0
	ldr r1, [sp, #0x28]
	ldr r0, _0223AE84 ; =0x000008DC
	strb r1, [r2, r0]
_0223AE5A:
	add r5, r5, #1
	add r4, #0xd
	cmp r5, r7
	blt _0223AE36
_0223AE62:
	ldr r0, [sp, #8]
	add r1, r0, #1
	ldr r0, [sp, #0x1c]
	str r1, [sp, #8]
	cmp r1, r0
	blt _0223AE24
_0223AE6E:
	mov r0, #1
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223AE74: .word MOD18_02250B3C
_0223AE78: .word MOD18_02250B3C + 1
_0223AE7C: .word MOD18_02250B30
_0223AE80: .word MOD18_02251380
_0223AE84: .word 0x000008DC
	thumb_func_end MOD18_0223AD50

	thumb_func_start MOD18_0223AE88
MOD18_0223AE88: ; 0x0223AE88
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _0223AED0 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	add r6, r0, #0
	bl FUN_02026CC4
	bl FUN_02025C38
	add r4, r0, #0
	add r0, r6, #0
	bl Sav2_Pokedex_get
	bl Pokedex_GetNatDexFlag
	mov r1, #0
	cmp r0, #0
	beq _0223AEB6
	.ifdef DIAMOND
	ldrh r0, [r5, #8]
	.else
	ldrh r0, [r5, #0xa]
	.endif
	b _0223AEB8
_0223AEB6:
	.ifdef DIAMOND
	ldrh r0, [r5, #4]
	.else
	ldrh r0, [r5, #6]
	.endif
_0223AEB8:
	add r0, r1, r0
	cmp r4, #0
	beq _0223AECC
	ldrb r1, [r5, #0xe]
	.ifdef DIAMOND
	cmp r1, #6
	.else
	cmp r1, #7
	.endif
	bne _0223AEC6
	add r0, #0x21
_0223AEC6:
	.ifdef DIAMOND
	cmp r1, #1
	.else
	cmp r1, #2
	.endif
	bne _0223AECC
	add r0, #0x42
_0223AECC:
	pop {r4, r5, r6, pc}
	nop
_0223AED0: .word MOD18_02251380
	thumb_func_end MOD18_0223AE88

	thumb_func_start MOD18_0223AED4
MOD18_0223AED4: ; 0x0223AED4
	push {r4, r5, r6, lr}
	mov r4, #0
	ldr r5, _0223AEF8 ; =0x02250B30
	add r6, r4, #0
_0223AEDC:
	ldrb r0, [r5, #0xe]
	cmp r0, #0x3c
	beq _0223AEF2
	add r0, r5, #0
	bl MOD18_0223AE88
	add r6, r6, #1
	add r4, r4, r0
	add r5, #0x14
	cmp r6, #0x55
	blo _0223AEDC
_0223AEF2:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_0223AEF8: .word MOD18_02250B30
	thumb_func_end MOD18_0223AED4

	thumb_func_start MOD18_0223AEFC
MOD18_0223AEFC: ; 0x0223AEFC
	push {r4, r5, r6, lr}
	ldr r5, _0223AF28 ; =0x02250B30
	add r6, r0, #0
	mov r4, #0
_0223AF04:
	ldrb r0, [r5, #0xe]
	cmp r0, #0x3c
	beq _0223AF20
	add r0, r5, #0
	bl MOD18_0223AE88
	sub r6, r6, r0
	bpl _0223AF18
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_0223AF18:
	add r4, r4, #1
	add r5, #0x14
	cmp r4, #0x55
	blo _0223AF04
_0223AF20:
	bl ErrorHandling
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223AF28: .word MOD18_02250B30
	thumb_func_end MOD18_0223AEFC

	thumb_func_start MOD18_0223AF2C
MOD18_0223AF2C: ; 0x0223AF2C
	mov r0, #0
	ldr r3, _0223AF44 ; =0x02250B30
	add r2, r0, #0
_0223AF32:
	ldrb r1, [r3, #0xe]
	cmp r1, #0x3c
	blo _0223AF3A
	add r0, r0, #1
_0223AF3A:
	add r2, r2, #1
	add r3, #0x14
	cmp r2, #0x55
	blo _0223AF32
	bx lr
	.align 2, 0
_0223AF44: .word MOD18_02250B30
	thumb_func_end MOD18_0223AF2C

	thumb_func_start MOD18_0223AF48
MOD18_0223AF48: ; 0x0223AF48
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x58
	str r0, [sp]
	ldr r0, _0223B1A0 ; =0x02251380
	str r1, [sp, #4]
	ldr r0, [r0]
	str r2, [sp, #8]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	str r0, [sp, #0x38]
	bl MOD18_0223AED4
	str r0, [sp, #0x1c]
	bl MOD18_0223AF2C
	str r0, [sp, #0x28]
	ldr r0, _0223B1A0 ; =0x02251380
	ldr r4, [r0]
	add r5, r4, #0
	add r5, #8
	ldr r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #8]
	ldr r3, [r5, #4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #8]
	str r3, [r5, #4]
	add r0, r3, #0
	mov r1, #0
	mov r2, #3
	mov r3, #0
	bl _ll_mul
	ldr r0, [sp, #8]
	add r1, r1, #2
	str r1, [r0, #0xc]
	ldr r0, [sp, #0x38]
	bl FUN_02026620
	cmp r0, #0
	beq _0223AFB0
	ldr r0, [sp, #8]
	mov r1, #3
	str r1, [r0, #0xc]
_0223AFB0:
	ldr r0, [sp, #8]
	mov r4, #0
	ldr r0, [r0, #0xc]
	cmp r0, #0
	ble _0223B0BA
	add r7, sp, #0x48
	str r4, [sp, #0x20]
_0223AFBE:
	ldr r0, _0223B1A0 ; =0x02251380
	ldr r6, [r0]
	add r5, r6, #0
	add r5, #8
	ldr r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r6, #8]
	ldr r3, [r5, #4]
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [r5, #0x10]
	ldr r1, [r5, #0x14]
	add r0, r0, r2
	str r0, [r6, #8]
	adc r1, r3
	ldr r0, [sp, #0x1c]
	str r1, [r5, #4]
	cmp r0, #0
	bne _0223AFEC
	ldr r1, [r5, #4]
	b _0223AFF8
_0223AFEC:
	ldr r0, [r5, #4]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	mov r1, #0
	bl _ll_mul
_0223AFF8:
	add r0, r1, #0
	bl MOD18_0223AEFC
	mov r1, #0x14
	str r0, [sp, #0x30]
	mul r1, r0
	ldr r0, _0223B1A4 ; =0x02250B30
	add r0, r0, r1
	ldrb r5, [r0, #0xe]
	ldr r0, [sp, #0x38]
	add r1, r5, #0
	bl FUN_02026688
	cmp r0, #0
	beq _0223B0B2
	cmp r5, #0x2c
	blt _0223B042
	cmp r5, #0x3b
	bgt _0223B042
	mov r3, #0
	add r2, r3, #0
	str r5, [r7]
	cmp r4, #0
	ble _0223B03C
	add r6, sp, #0x48
	mov r0, #1
_0223B02C:
	ldr r1, [r6]
	cmp r5, r1
	bne _0223B034
	add r3, r0, #0
_0223B034:
	add r2, r2, #1
	add r6, r6, #4
	cmp r2, r4
	blt _0223B02C
_0223B03C:
	cmp r3, #0
	bne _0223B0B2
	b _0223B046
_0223B042:
	mov r0, #0x1c
	str r0, [r7]
_0223B046:
	ldr r0, _0223B1A0 ; =0x02251380
	ldr r5, [r0]
	add r6, r5, #0
	add r6, #8
	ldr r0, [r6, #8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	add r3, r0, #0
	ldr r0, [r6, #0x10]
	ldr r2, [r6, #0x14]
	add r0, r0, r3
	adc r2, r1
	str r0, [r5, #8]
	str r2, [r6, #4]
	add r0, r2, #0
	mov r1, #0
	mov r2, #0xd
	mov r3, #0
	bl _ll_mul
	add r6, r5, #0
	add r6, #8
	str r1, [sp, #0x18]
	ldr r0, [r6, #8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	add r3, r0, #0
	ldr r0, [r6, #0x10]
	ldr r2, [r6, #0x14]
	add r0, r0, r3
	adc r2, r1
	str r0, [r5, #8]
	str r2, [r6, #4]
	add r0, r2, #0
	mov r1, #0
	mov r2, #0xa
	mov r3, #0
	bl _ll_mul
	add r2, r1, #0
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x18]
	bl MOD18_0223AD50
	cmp r0, #0
	beq _0223B0B2
	add r7, r7, #4
	add r4, r4, #1
_0223B0B2:
	ldr r0, [sp, #8]
	ldr r0, [r0, #0xc]
	cmp r4, r0
	blt _0223AFBE
_0223B0BA:
	ldr r0, [sp, #0x38]
	bl FUN_02026620
	cmp r0, #0
	bne _0223B18E
	mov r0, #0
	str r0, [sp, #0x34]
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x28]
	mov r1, #0x55
	sub r0, r1, r0
	str r0, [sp, #0x24]
	mov r0, #0
	str r0, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
_0223B0DA:
	ldr r0, _0223B1A0 ; =0x02251380
	ldr r6, [r0]
	add r5, r6, #0
	add r5, #8
	ldr r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r6, #8]
	ldr r3, [r5, #4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	str r0, [r6, #8]
	adc r3, r1
	ldr r0, [sp, #0x28]
	str r3, [r5, #4]
	cmp r0, #0
	ldr r0, [r5, #4]
	bne _0223B106
	str r0, [sp, #0x10]
	b _0223B112
_0223B106:
	ldr r1, [sp, #0x3c]
	ldr r2, [sp, #0x28]
	ldr r3, [sp, #0x2c]
	bl _ll_mul
	str r1, [sp, #0x10]
_0223B112:
	ldr r0, _0223B1A0 ; =0x02251380
	ldr r5, [r0]
	add r6, r5, #0
	add r6, #8
	ldr r0, [r6, #8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	ldr r2, [r6, #0x10]
	ldr r3, [r6, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #8]
	ldr r1, [sp, #0x40]
	str r3, [r6, #4]
	add r0, r3, #0
	mov r2, #0xd
	mov r3, #0
	bl _ll_mul
	add r6, r5, #0
	add r6, #8
	add r7, r1, #0
	ldr r0, [r6, #8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [r6, #0x10]
	ldr r1, [r6, #0x14]
	add r0, r0, r2
	adc r1, r3
	str r0, [r5, #8]
	str r1, [r6, #4]
	add r0, r1, #0
	ldr r1, [sp, #0x44]
	mov r2, #0xa
	mov r3, #0
	bl _ll_mul
	add r2, r1, #0
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x24]
	add r0, r1, r0
	add r1, r7, #0
	bl MOD18_0223AD50
	cmp r0, #0
	beq _0223B180
	add r4, r4, #1
_0223B180:
	cmp r4, #0xc
	bgt _0223B18E
	ldr r0, [sp, #0x34]
	add r0, r0, #1
	str r0, [sp, #0x34]
	cmp r0, #0x64
	blt _0223B0DA
_0223B18E:
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r4, #0
	bl MOD18_0223B454
	add sp, #0x58
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223B1A0: .word MOD18_02251380
_0223B1A4: .word MOD18_02250B30
	thumb_func_end MOD18_0223AF48

	thumb_func_start MOD18_0223B1A8
MOD18_0223B1A8: ; 0x0223B1A8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r4, r0, #0
	ldr r0, _0223B2D0 ; =0x02251380
	str r1, [sp, #0x10]
	ldr r1, [r0]
	mov r0, #0x81
	lsl r0, r0, #4
	add r5, r1, r0
	mov r0, #0xc
	add r6, r4, #0
	mul r6, r0
	add r0, r5, r6
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x10]
	mov r1, #1
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	bl FUN_0201886C
	ldr r1, [r5, r6]
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x38]
	ldrb r2, [r1, #0xd]
	ldrb r0, [r0, #5]
	add r6, r4, #0
	lsl r7, r0, #1
	ldr r0, [sp, #0x38]
	ldrb r0, [r0, #6]
	lsl r0, r0, #1
	str r0, [sp, #0x30]
	ldrb r0, [r1, #0xc]
	add r0, r7, r0
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x30]
	add r0, r0, r2
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x18]
	ldr r0, [r0, #0xc]
	cmp r4, r0
	blt _0223B1FC
	mov r6, #4
_0223B1FC:
	cmp r4, r0
	blt _0223B218
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x1d
	str r0, [sp, #4]
	add r3, r6, #3
	ldrh r1, [r1, #0x12]
	mov r0, #0x37
	mov r2, #0
	lsl r3, r3, #5
	bl FUN_02006930
	b _0223B248
_0223B218:
	ldr r5, [sp, #0x18]
	ldrh r1, [r1, #0x12]
	lsl r4, r4, #2
	add r5, #0x28
	mov r0, #0x37
	add r2, r5, r4
	mov r3, #0x1d
	bl FUN_02006C08
	ldr r1, [sp, #0x18]
	add r1, r1, r4
	str r0, [r1, #0x18]
	ldr r0, [r5, r4]
	mov r1, #0x20
	ldr r0, [r0, #0xc]
	bl DC_FlushRange
	ldr r0, [r5, r4]
	add r1, r6, #3
	ldr r0, [r0, #0xc]
	lsl r1, r1, #5
	mov r2, #0x20
	bl GX_LoadBGPltt
_0223B248:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x38]
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x1d
	str r0, [sp, #0xc]
	ldr r1, [r1]
	ldr r2, [sp, #0x10]
	ldrh r1, [r1, #0x10]
	mov r0, #0x37
	mov r3, #1
	bl FUN_0200687C
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x30]
	str r0, [sp, #0x24]
	add r1, r0, #0
	ldr r0, [sp, #0x28]
	cmp r1, r0
	bge _0223B2CA
	add r0, r6, #3
	lsl r1, r0, #0xc
	ldr r0, [sp, #0x14]
	add r6, r0, r1
	lsl r0, r7, #1
	str r0, [sp, #0x3c]
_0223B280:
	ldr r0, [sp, #0x2c]
	add r4, r7, #0
	cmp r7, r0
	bge _0223B2BE
	ldr r0, [sp, #0x24]
	add r0, r0, #4
	lsl r1, r0, #6
	ldr r0, [sp, #0x34]
	add r1, r0, r1
	ldr r0, [sp, #0x3c]
	add r5, r1, r0
	ldr r1, [sp, #0x24]
	ldr r0, [sp, #0x30]
	sub r0, r1, r0
	str r0, [sp, #0x1c]
_0223B29E:
	ldr r0, [sp, #0x38]
	ldr r2, [sp, #0x1c]
	ldr r0, [r0]
	sub r1, r4, r7
	add r6, r6, #1
	bl MOD18_0223AD1C
	cmp r0, #0
	beq _0223B2B4
	sub r0, r6, #1
	strh r0, [r5]
_0223B2B4:
	ldr r0, [sp, #0x2c]
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, r0
	blt _0223B29E
_0223B2BE:
	ldr r0, [sp, #0x24]
	add r1, r0, #1
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x24]
	cmp r1, r0
	blt _0223B280
_0223B2CA:
	ldr r0, [sp, #0x20]
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223B2D0: .word MOD18_02251380
	thumb_func_end MOD18_0223B1A8

	thumb_func_start MOD18_0223B2D4
MOD18_0223B2D4: ; 0x0223B2D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [sp]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	str r0, [sp, #0x10]
_0223B2E6:
	ldr r0, [sp, #0x14]
	ldr r0, [r0, #0x38]
	cmp r0, #1
	bne _0223B3DA
	ldr r0, _0223B440 ; =0x000006A7
	bl FUN_020054C8
	mov r0, #0
	mov r4, #0
	str r4, [sp, #0x18]
	str r0, [sp, #0x20]
	str r0, [sp, #0x24]
_0223B2FE:
	ldr r0, _0223B444 ; =0x02251380
	ldr r5, [r0]
	ldr r0, [sp, #0x10]
	add r6, r5, #0
	add r1, r0, r5
	mov r0, #0x81
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r6, #8
	ldrb r0, [r0, #0xc]
	str r1, [sp, #0xc]
	ldr r1, [r6, #0xc]
	lsl r7, r0, #3
	ldr r0, [r6, #8]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	add r3, r0, #0
	add r2, r1, #0
	ldr r0, [r6, #0x10]
	ldr r1, [r6, #0x14]
	add r0, r0, r3
	adc r1, r2
	str r0, [r5, #8]
	str r1, [r6, #4]
	cmp r7, #0
	ldr r0, [r6, #4]
	bne _0223B33C
	str r0, [sp, #8]
	b _0223B348
_0223B33C:
	ldr r1, [sp, #0x20]
	add r2, r7, #0
	mov r3, #0
	bl _ll_mul
	str r1, [sp, #8]
_0223B348:
	mov r0, #0x81
	ldr r1, [sp, #0xc]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r6, r5, #0
	ldrb r0, [r0, #0xd]
	add r6, #8
	ldr r1, [r6, #0xc]
	lsl r7, r0, #3
	ldr r0, [r6, #8]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	add r3, r0, #0
	add r2, r1, #0
	ldr r0, [r6, #0x10]
	ldr r1, [r6, #0x14]
	add r0, r0, r3
	adc r1, r2
	str r0, [r5, #8]
	str r1, [r6, #4]
	cmp r7, #0
	bne _0223B37C
	ldr r1, [r6, #4]
	b _0223B388
_0223B37C:
	ldr r0, [r6, #4]
	ldr r1, [sp, #0x24]
	add r2, r7, #0
	mov r3, #0
	bl _ll_mul
_0223B388:
	ldr r0, _0223B444 ; =0x02251380
	ldr r3, [sp, #0xc]
	ldr r2, [r0]
	ldr r0, _0223B448 ; =0x00000815
	ldr r5, [sp, #0xc]
	ldrb r0, [r3, r0]
	lsl r3, r0, #4
	ldr r0, [sp, #8]
	add r0, r0, r3
	ldr r3, _0223B44C ; =0x00000816
	lsl r0, r0, #0xc
	ldrb r3, [r5, r3]
	lsl r3, r3, #4
	str r0, [sp, #0x28]
	add r0, r1, r3
	add r0, #0x20
	lsl r0, r0, #0xc
	str r0, [sp, #0x2c]
	mov r0, #0x7f
	add r1, r2, r4
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x18]
	add r1, #8
	bl FUN_02020130
	ldr r0, _0223B444 ; =0x02251380
	ldr r0, [r0]
	add r1, r0, r4
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0x28
	bl FUN_02020044
	ldr r0, [sp, #0x18]
	add r4, r4, #4
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #3
	blt _0223B2FE
_0223B3DA:
	ldr r0, [sp, #0x14]
	add r0, r0, #4
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x10]
	add r0, #0xc
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #4
	bge _0223B3F2
	b _0223B2E6
_0223B3F2:
	mov r5, #0
	ldr r4, _0223B450 ; =0x022511F0
	mov r7, #0x20
	add r6, r5, #0
_0223B3FA:
	ldr r0, [sp]
	ldr r0, [r0, #0x38]
	cmp r0, #0
	beq _0223B430
	ldr r1, [sp]
	ldr r1, [r1, #0x28]
	ldr r3, [r1, #0xc]
	add r1, r4, r0
	sub r1, r1, #1
	ldrb r2, [r1]
	cmp r2, #0xff
	bne _0223B418
	ldr r0, [sp]
	str r6, [r0, #0x38]
	b _0223B430
_0223B418:
	add r1, r0, #1
	ldr r0, [sp]
	cmp r2, #0xfe
	str r1, [r0, #0x38]
	beq _0223B430
	lsl r0, r2, #1
	add r1, r5, #3
	add r0, r3, r0
	lsl r1, r1, #5
	add r2, r7, #0
	bl GX_LoadBGPltt
_0223B430:
	ldr r0, [sp]
	add r5, r5, #1
	add r0, r0, #4
	str r0, [sp]
	cmp r5, #4
	blt _0223B3FA
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223B440: .word 0x000006A7
_0223B444: .word MOD18_02251380
_0223B448: .word 0x00000815
_0223B44C: .word 0x00000816
_0223B450: .word MOD18_022511F0
	thumb_func_end MOD18_0223B2D4

	thumb_func_start MOD18_0223B454
MOD18_0223B454: ; 0x0223B454
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	mov r4, #0
	str r3, [sp]
	ldr r5, _0223B47C ; =0x00000269
	cmp r6, #0
	ble _0223B47A
_0223B464:
	ldr r3, [sp]
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD18_0223B1A8
	lsr r0, r0, #5
	add r4, r4, #1
	add r5, r5, r0
	cmp r4, r6
	blt _0223B464
_0223B47A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223B47C: .word 0x00000269
	thumb_func_end MOD18_0223B454

	thumb_func_start MOD18_0223B480
MOD18_0223B480: ; 0x0223B480
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	mov r0, #0
	str r0, [sp, #0xc]
_0223B488:
	ldr r0, _0223B694 ; =0x02251380
	ldr r4, [r0]
	add r5, r4, #0
	add r5, #8
	ldr r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #8]
	ldr r3, [r5, #4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #8]
	str r3, [r5, #4]
	add r0, r3, #0
	mov r1, #0
	mov r2, #0x15
	mov r3, #0
	bl _ll_mul
	add r5, r4, #0
	add r5, #8
	str r1, [sp, #0x20]
	sub r1, #8
	str r1, [sp, #0x20]
	ldr r0, [r5, #8]
	ldr r1, [r5, #0xc]
	ldr r2, [r4, #8]
	ldr r3, [r5, #4]
	bl _ll_mul
	ldr r2, [r5, #0x10]
	ldr r3, [r5, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r4, #8]
	str r3, [r5, #4]
	add r0, r3, #0
	mov r1, #0
	mov r2, #0x12
	mov r3, #0
	bl _ll_mul
	sub r5, r1, #5
	add r0, r5, #0
	str r0, [sp, #0x14]
	add r0, #8
	add r1, r5, #0
	str r5, [sp, #0x10]
	str r0, [sp, #0x14]
	cmp r1, r0
	bge _0223B548
	add r0, r5, #0
	ldr r3, [sp, #0x20]
	mov r1, #0xd
	add r6, r0, #0
	mul r6, r1
	add r3, #8
_0223B500:
	cmp r5, #0xa
	bge _0223B53E
	cmp r5, #0
	blt _0223B53E
	ldr r4, [sp, #0x20]
	add r0, r4, #0
	cmp r0, r3
	bge _0223B53E
	ldr r0, [sp, #0x10]
	sub r0, r5, r0
	lsl r1, r0, #3
	ldr r0, _0223B698 ; =0x02250AF0
	add r7, r0, r1
_0223B51A:
	cmp r4, #0xd
	bge _0223B538
	cmp r4, #0
	blt _0223B538
	ldr r0, [sp, #0x20]
	sub r0, r4, r0
	ldrb r2, [r7, r0]
	cmp r2, #0
	beq _0223B538
	ldr r0, _0223B694 ; =0x02251380
	ldr r0, [r0]
	add r0, r6, r0
	add r1, r4, r0
	ldr r0, _0223B69C ; =0x0000095E
	strb r2, [r1, r0]
_0223B538:
	add r4, r4, #1
	cmp r4, r3
	blt _0223B51A
_0223B53E:
	ldr r0, [sp, #0x14]
	add r5, r5, #1
	add r6, #0xd
	cmp r5, r0
	blt _0223B500
_0223B548:
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #0xa
	blt _0223B488
	mov r0, #0
	str r0, [sp, #4]
_0223B556:
	ldr r0, _0223B694 ; =0x02251380
	ldr r5, [r0]
	add r4, r5, #0
	add r4, #8
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r4, #4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #8]
	str r3, [r4, #4]
	add r0, r3, #0
	mov r1, #0
	mov r2, #0x12
	mov r3, #0
	bl _ll_mul
	add r6, r5, #0
	add r6, #8
	sub r4, r1, #5
	ldr r0, [r6, #8]
	ldr r1, [r6, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r6, #4]
	bl _ll_mul
	ldr r2, [r6, #0x10]
	ldr r3, [r6, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #8]
	str r3, [r6, #4]
	add r0, r3, #0
	mov r1, #0
	mov r2, #0xf
	mov r3, #0
	bl _ll_mul
	sub r0, r1, #5
	str r0, [sp]
	ldr r3, [sp]
	mov r0, #1
	str r0, [sp, #8]
	add r0, r3, #0
	add r0, r0, #5
	add r1, r3, #0
	str r0, [sp, #0x18]
	cmp r1, r0
	bge _0223B61A
	mov r1, #0xd
	add r0, r3, #0
	mul r1, r0
	ldr r7, _0223B69C ; =0x0000095E
	add r1, r5, r1
	add r0, r4, #5
_0223B5CE:
	cmp r3, #0xa
	bge _0223B610
	cmp r3, #0
	blt _0223B610
	add r5, r4, #0
	cmp r4, r0
	bge _0223B60A
	ldr r2, [sp]
	sub r2, r3, r2
	lsl r6, r2, #3
	ldr r2, _0223B698 ; =0x02250AF0
	add r2, r2, r6
_0223B5E6:
	cmp r5, #0xd
	bge _0223B604
	cmp r5, #0
	blt _0223B604
	sub r6, r5, r4
	ldrb r6, [r2, r6]
	cmp r6, #0
	beq _0223B604
	add r6, r1, r5
	ldrb r6, [r6, r7]
	cmp r6, #4
	bhs _0223B604
	mov r2, #0
	str r2, [sp, #8]
	b _0223B60A
_0223B604:
	add r5, r5, #1
	cmp r5, r0
	blt _0223B5E6
_0223B60A:
	ldr r2, [sp, #8]
	cmp r2, #0
	beq _0223B61A
_0223B610:
	ldr r2, [sp, #0x18]
	add r3, r3, #1
	add r1, #0xd
	cmp r3, r2
	blt _0223B5CE
_0223B61A:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _0223B684
	ldr r0, [sp]
	ldr r1, [sp]
	str r0, [sp, #0x1c]
	add r0, r0, #5
	mov ip, r0
	cmp r1, r0
	bge _0223B684
	ldr r0, [sp]
	mov r1, #0xd
	add r3, r0, #0
	mul r3, r1
	add r6, r4, #5
_0223B638:
	ldr r0, [sp, #0x1c]
	cmp r0, #0xa
	bge _0223B676
	cmp r0, #0
	blt _0223B676
	add r5, r4, #0
	cmp r4, r6
	bge _0223B676
	ldr r1, [sp]
	sub r1, r0, r1
	lsl r0, r1, #2
	add r1, r1, r0
	ldr r0, _0223B6A0 ; =0x02250ABA
	add r7, r0, r1
_0223B654:
	cmp r5, #0xd
	bge _0223B670
	cmp r5, #0
	blt _0223B670
	sub r0, r5, r4
	ldrb r2, [r7, r0]
	cmp r2, #0
	beq _0223B670
	ldr r0, _0223B694 ; =0x02251380
	ldr r0, [r0]
	add r0, r3, r0
	add r1, r5, r0
	ldr r0, _0223B69C ; =0x0000095E
	strb r2, [r1, r0]
_0223B670:
	add r5, r5, #1
	cmp r5, r6
	blt _0223B654
_0223B676:
	ldr r0, [sp, #0x1c]
	mov r1, ip
	add r0, r0, #1
	add r3, #0xd
	str r0, [sp, #0x1c]
	cmp r0, r1
	blt _0223B638
_0223B684:
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #0xf
	bge _0223B690
	b _0223B556
_0223B690:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223B694: .word MOD18_02251380
_0223B698: .word MOD18_02250AF0
_0223B69C: .word 0x0000095E
_0223B6A0: .word MOD18_02250ABA
	thumb_func_end MOD18_0223B480

	thumb_func_start MOD18_0223B6A4
MOD18_0223B6A4: ; 0x0223B6A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r1, #2
	str r0, [sp]
	bl FUN_0201886C
	str r0, [sp, #8]
	mov r2, #0
	mov r0, #4
	mov ip, r2
	str r0, [sp, #4]
_0223B6BA:
	ldr r0, [sp, #4]
	mov r6, #0
	lsl r3, r0, #5
_0223B6C0:
	ldr r0, _0223B728 ; =0x02251380
	lsl r7, r3, #1
	ldr r0, [r0]
	ldr r4, _0223B72C ; =0x00002001
	add r0, r2, r0
	add r1, r6, r0
	ldr r0, _0223B730 ; =0x0000095E
	add r6, r6, #1
	ldrb r0, [r1, r0]
	add r3, r3, #2
	lsl r1, r0, #2
	ldr r0, _0223B734 ; =0x02250AD4
	ldr r1, [r0, r1]
	ldr r0, [sp, #8]
	ldrb r5, [r1]
	add r0, r0, r7
	add r5, r5, r4
	ldr r4, [sp, #8]
	strh r5, [r4, r7]
	ldrb r5, [r1, #1]
	ldr r4, _0223B72C ; =0x00002001
	add r4, r5, r4
	strh r4, [r0, #2]
	ldrb r5, [r1, #2]
	ldr r4, _0223B72C ; =0x00002001
	add r4, r5, r4
	add r5, r0, #0
	add r5, #0x40
	strh r4, [r5]
	ldrb r4, [r1, #3]
	ldr r1, _0223B72C ; =0x00002001
	add r0, #0x42
	add r1, r4, r1
	strh r1, [r0]
	cmp r6, #0xd
	blt _0223B6C0
	ldr r0, [sp, #4]
	add r2, #0xd
	add r0, r0, #2
	str r0, [sp, #4]
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #0xa
	blt _0223B6BA
	ldr r0, [sp]
	mov r1, #2
	bl FUN_02017CD0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_0223B728: .word MOD18_02251380
_0223B72C: .word 0x00002001
_0223B730: .word 0x0000095E
_0223B734: .word MOD18_02250AD4
	thumb_func_end MOD18_0223B6A4

	thumb_func_start MOD18_0223B738
MOD18_0223B738: ; 0x0223B738
	ldr r2, _0223B76C ; =0x02251380
	mov r3, #0xd
	ldr r2, [r2]
	mul r3, r1
	add r1, r2, r3
	add r0, r1, r0
	ldr r1, _0223B770 ; =0x000008DC
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _0223B750
	mov r0, #0
	bx lr
_0223B750:
	sub r3, r0, #1
	mov r0, #0xc
	mul r0, r3
	add r0, r2, r0
	sub r1, #0xc8
	ldrb r0, [r0, r1]
	cmp r0, #0
	beq _0223B768
	cmp r0, #0x3c
	bge _0223B768
	mov r0, #1
	bx lr
_0223B768:
	mov r0, #0
	bx lr
	.align 2, 0
_0223B76C: .word MOD18_02251380
_0223B770: .word 0x000008DC
	thumb_func_end MOD18_0223B738

	thumb_func_start MOD18_0223B774
MOD18_0223B774: ; 0x0223B774
	ldr r2, _0223B7A4 ; =0x02251380
	mov r3, #0xd
	ldr r2, [r2]
	mul r3, r1
	add r1, r2, r3
	add r0, r1, r0
	ldr r1, _0223B7A8 ; =0x000008DC
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _0223B78C
	mov r0, #0
	bx lr
_0223B78C:
	sub r3, r0, #1
	mov r0, #0xc
	mul r0, r3
	add r0, r2, r0
	sub r1, #0xc8
	ldrb r0, [r0, r1]
	cmp r0, #0x3c
	blo _0223B7A0
	mov r0, #1
	bx lr
_0223B7A0:
	mov r0, #0
	bx lr
	.align 2, 0
_0223B7A4: .word MOD18_02251380
_0223B7A8: .word 0x000008DC
	thumb_func_end MOD18_0223B774

	thumb_func_start MOD18_0223B7AC
MOD18_0223B7AC: ; 0x0223B7AC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r2, [sp, #4]
	asr r2, r0, #3
	lsr r2, r2, #0x1c
	add r2, r0, r2
	asr r0, r1, #3
	lsr r0, r0, #0x1c
	add r0, r1, r0
	asr r0, r0, #4
	mov r5, #0
	sub r0, r0, #2
	asr r7, r2, #4
	add r6, r5, #0
	str r3, [sp, #8]
	str r0, [sp, #0xc]
	cmp r7, #0
	blt _0223B7DC
	cmp r7, #0xd
	bge _0223B7DC
	cmp r0, #0
	blt _0223B7DC
	cmp r0, #0xa
	blt _0223B7DE
_0223B7DC:
	b _0223B92A
_0223B7DE:
	add r4, r0, #0
	mov r1, #0xd
	ldr r0, _0223B930 ; =0x02251380
	mul r4, r1
	ldr r1, [r0]
	ldr r0, _0223B934 ; =0x0000095E
	add r0, r1, r0
	add r1, r0, r4
	ldrb r0, [r1, r7]
	cmp r0, #0
	beq _0223B7F8
	sub r0, r0, #1
	strb r0, [r1, r7]
_0223B7F8:
	ldr r0, _0223B930 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223B934 ; =0x0000095E
	add r0, r1, r0
	add r1, r0, r4
	ldrb r0, [r1, r7]
	cmp r0, #0
	beq _0223B80C
	sub r0, r0, #1
	strb r0, [r1, r7]
_0223B80C:
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl MOD18_0223B774
	cmp r0, #0
	beq _0223B82A
	ldr r0, _0223B930 ; =0x02251380
	ldr r0, [r0]
	add r0, r0, r4
	add r1, r0, r7
	ldr r0, _0223B934 ; =0x0000095E
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223B82A
	mov r5, #1
_0223B82A:
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl MOD18_0223B738
	cmp r0, #0
	beq _0223B84E
	ldr r0, _0223B930 ; =0x02251380
	ldr r0, [r0]
	add r0, r0, r4
	add r1, r0, r7
	ldr r0, _0223B934 ; =0x0000095E
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223B84E
	ldr r0, [sp, #8]
	mov r1, #0xf
	mov r6, #1
	str r1, [r0, #0x14]
_0223B84E:
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #4]
	add r1, r1, #2
	lsl r0, r7, #4
	lsl r1, r1, #4
	add r3, r5, #0
	str r6, [sp]
	bl MOD18_0223A2BC
	cmp r5, #0
	bne _0223B92A
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0223B8B6
	ldr r4, _0223B938 ; =0x022511D4
	ldr r5, _0223B93C ; =0x02250860
	mov r3, #0
_0223B870:
	mov r0, #0
	ldrsb r1, [r4, r0]
	ldr r0, [sp, #0xc]
	add r2, r0, r1
	mov r0, #0
	ldrsb r0, [r5, r0]
	add r1, r7, r0
	cmp r2, #0
	blt _0223B8AC
	cmp r2, #0xa
	bge _0223B8AC
	cmp r1, #0
	blt _0223B8AC
	cmp r1, #0xd
	bge _0223B8AC
	ldr r0, _0223B930 ; =0x02251380
	mov r6, #0xd
	ldr r0, [r0]
	mul r6, r2
	add r0, r0, r6
	add r0, r0, r1
	ldr r1, _0223B934 ; =0x0000095E
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _0223B8AC
	ldr r1, _0223B934 ; =0x0000095E
	ldrb r1, [r0, r1]
	sub r2, r1, #1
	ldr r1, _0223B934 ; =0x0000095E
	strb r2, [r0, r1]
_0223B8AC:
	add r3, r3, #1
	add r4, r4, #1
	add r5, r5, #1
	cmp r3, #4
	blt _0223B870
_0223B8B6:
	mov r0, #0
	ldr r2, _0223B940 ; =0x022511EC
	ldr r3, _0223B944 ; =0x022511D8
	mov ip, r0
_0223B8BE:
	mov r0, #0
	ldrsb r1, [r2, r0]
	ldr r0, [sp, #0xc]
	add r0, r0, r1
	mov r1, #0
	ldrsb r1, [r3, r1]
	add r5, r7, r1
	cmp r0, #0
	blt _0223B91C
	cmp r0, #0xa
	bge _0223B91C
	cmp r5, #0
	blt _0223B91C
	cmp r5, #0xd
	bge _0223B91C
	add r4, r0, #0
	ldr r0, _0223B930 ; =0x02251380
	mov r1, #0xd
	ldr r0, [r0]
	mul r4, r1
	add r0, r0, r4
	add r6, r0, r5
	ldr r0, _0223B934 ; =0x0000095E
	ldrb r0, [r6, r0]
	cmp r0, #0
	beq _0223B8FC
	ldr r0, _0223B934 ; =0x0000095E
	ldrb r0, [r6, r0]
	sub r1, r0, #1
	ldr r0, _0223B934 ; =0x0000095E
	strb r1, [r6, r0]
_0223B8FC:
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0223B91C
	ldr r0, _0223B930 ; =0x02251380
	ldr r1, _0223B934 ; =0x0000095E
	ldr r0, [r0]
	add r0, r0, r4
	add r0, r0, r5
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _0223B91C
	ldr r1, _0223B934 ; =0x0000095E
	ldrb r1, [r0, r1]
	sub r4, r1, #1
	ldr r1, _0223B934 ; =0x0000095E
	strb r4, [r0, r1]
_0223B91C:
	mov r0, ip
	add r0, r0, #1
	add r2, r2, #1
	add r3, r3, #1
	mov ip, r0
	cmp r0, #4
	blt _0223B8BE
_0223B92A:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223B930: .word MOD18_02251380
_0223B934: .word 0x0000095E
_0223B938: .word MOD18_022511D4
_0223B93C: .word MOD18_02250860
_0223B940: .word MOD18_022511EC
_0223B944: .word MOD18_022511D8
	thumb_func_end MOD18_0223B7AC

	thumb_func_start MOD18_0223B948
MOD18_0223B948: ; 0x0223B948
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r1, #0
	ldrb r1, [r6, #1]
	str r2, [sp]
	ldrb r2, [r6, #3]
	mov ip, r1
	mov r1, #0
	mov lr, r1
	mov r1, ip
	str r3, [sp, #4]
	cmp r1, r2
	bge _0223B9B6
	mov r1, ip
	cmp r1, r2
	bge _0223B9B6
	mov r1, lr
	str r1, [sp, #8]
	mov r1, ip
	mov r7, #0x3f
	lsl r5, r1, #5
	lsl r7, r7, #0xa
_0223B974:
	ldr r2, [sp]
	ldr r1, [sp, #8]
	add r3, r2, r1
	ldrb r2, [r6]
	ldrb r1, [r6, #2]
	cmp r2, r1
	bge _0223B998
_0223B982:
	add r1, r2, r5
	lsl r1, r1, #1
	ldrh r4, [r0, r1]
	add r2, r2, #1
	and r4, r7
	add r4, r3, r4
	strh r4, [r0, r1]
	ldrb r1, [r6, #2]
	add r3, r3, #1
	cmp r2, r1
	blt _0223B982
_0223B998:
	mov r1, ip
	add r1, r1, #1
	mov ip, r1
	ldr r2, [sp, #8]
	ldr r1, [sp, #4]
	add r5, #0x20
	add r1, r2, r1
	str r1, [sp, #8]
	mov r1, lr
	add r1, r1, #1
	mov lr, r1
	ldrb r2, [r6, #3]
	mov r1, ip
	cmp r1, r2
	blt _0223B974
_0223B9B6:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0223B948

	thumb_func_start MOD18_0223B9BC
MOD18_0223B9BC: ; 0x0223B9BC
	push {r4, lr}
	ldr r3, _0223B9E0 ; =0x02251380
	ldr r2, _0223B9E4 ; =0x000009E6
	ldr r4, [r3]
	mov r1, #1
	strb r1, [r4, r2]
	ldr r3, [r3]
	sub r2, r2, #2
	strb r1, [r3, r2]
	bl FUN_0201886C
	ldr r1, _0223B9E8 ; =0x02250874
	mov r2, #0x30
	mov r3, #0x36
	bl MOD18_0223B948
	pop {r4, pc}
	nop
_0223B9E0: .word MOD18_02251380
_0223B9E4: .word 0x000009E6
_0223B9E8: .word MOD18_02250874
	thumb_func_end MOD18_0223B9BC

	thumb_func_start MOD18_0223B9EC
MOD18_0223B9EC: ; 0x0223B9EC
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r3, #0
	add r5, r0, #0
	cmp r4, #2
	blt _0223BA24
	bne _0223BA36
	cmp r1, #0xd6
	ble _0223BA24
	cmp r1, #0xfc
	bge _0223BA24
	cmp r2, #0x2b
	ble _0223BA1C
	cmp r2, #0x6e
	bge _0223BA1C
	ldr r2, _0223BB40 ; =0x02251380
	ldr r1, _0223BB44 ; =0x000009E6
	ldr r3, [r2]
	mov r0, #0
	strb r0, [r3, r1]
	ldr r2, [r2]
	sub r1, r1, #2
	strb r0, [r2, r1]
	b _0223BA36
_0223BA1C:
	cmp r2, #0x72
	ble _0223BA24
	cmp r2, #0xae
	blt _0223BA26
_0223BA24:
	b _0223BB3C
_0223BA26:
	ldr r2, _0223BB40 ; =0x02251380
	ldr r1, _0223BB44 ; =0x000009E6
	ldr r3, [r2]
	mov r0, #1
	strb r0, [r3, r1]
	ldr r2, [r2]
	sub r1, r1, #2
	strb r0, [r2, r1]
_0223BA36:
	add r0, r5, #0
	mov r1, #1
	bl FUN_0201886C
	ldr r1, _0223BB40 ; =0x02251380
	add r6, r0, #0
	ldr r2, [r1]
	ldr r1, _0223BB44 ; =0x000009E6
	ldrb r1, [r2, r1]
	cmp r1, #0
	beq _0223BA52
	cmp r1, #1
	beq _0223BAC4
	b _0223BB34
_0223BA52:
	cmp r4, #2
	bne _0223BA74
	ldr r1, _0223BB48 ; =0x02250878
	mov r2, #0x18
	mov r3, #0x36
	bl MOD18_0223B948
	ldr r1, _0223BB4C ; =0x02250874
	add r0, r6, #0
	mov r2, #0x24
	mov r3, #0x36
	bl MOD18_0223B948
	ldr r0, _0223BB50 ; =0x000005DC
	bl FUN_020054C8
	b _0223BA82
_0223BA74:
	cmp r4, #3
	bne _0223BA82
	ldr r1, _0223BB48 ; =0x02250878
	mov r2, #0x1e
	mov r3, #0x36
	bl MOD18_0223B948
_0223BA82:
	cmp r4, #2
	bne _0223BB34
	ldr r0, _0223BB40 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #6
	bl FUN_02020130
	ldr r0, _0223BB40 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x3a
	lsl r0, r0, #0xe
	str r0, [sp]
	mov r0, #5
	lsl r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, _0223BB40 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
	b _0223BB34
_0223BAC4:
	cmp r4, #2
	bne _0223BAE6
	ldr r1, _0223BB48 ; =0x02250878
	mov r2, #0x12
	mov r3, #0x36
	bl MOD18_0223B948
	ldr r1, _0223BB4C ; =0x02250874
	add r0, r6, #0
	mov r2, #0x2a
	mov r3, #0x36
	bl MOD18_0223B948
	ldr r0, _0223BB50 ; =0x000005DC
	bl FUN_020054C8
	b _0223BAF4
_0223BAE6:
	cmp r4, #3
	bne _0223BAF4
	ldr r1, _0223BB4C ; =0x02250874
	mov r2, #0x30
	mov r3, #0x36
	bl MOD18_0223B948
_0223BAF4:
	cmp r4, #2
	bne _0223BB34
	ldr r0, _0223BB40 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #7
	bl FUN_02020130
	ldr r0, _0223BB40 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0x3a
	lsl r0, r0, #0xe
	str r0, [sp]
	mov r0, #0x26
	lsl r0, r0, #0xe
	str r0, [sp, #4]
	ldr r0, _0223BB40 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x1f
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
_0223BB34:
	add r0, r5, #0
	mov r1, #1
	bl FUN_02017CD0
_0223BB3C:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223BB40: .word MOD18_02251380
_0223BB44: .word 0x000009E6
_0223BB48: .word MOD18_02250878
_0223BB4C: .word MOD18_02250874
_0223BB50: .word 0x000005DC
	thumb_func_end MOD18_0223B9EC

	thumb_func_start MOD18_0223BB54
MOD18_0223BB54: ; 0x0223BB54
	ldr r1, _0223BB74 ; =0x02251380
	ldr r2, [r1]
	ldr r1, _0223BB78 ; =0x000009E7
	ldrb r2, [r2, r1]
	asr r1, r2, #1
	lsr r1, r1, #0x1e
	add r1, r2, r1
	asr r1, r1, #2
	lsl r1, r1, #2
	add r1, #0x10
	lsl r1, r1, #0xc
	str r1, [r0]
	mov r1, #1
	lsl r1, r1, #0x10
	str r1, [r0, #4]
	bx lr
	.align 2, 0
_0223BB74: .word MOD18_02251380
_0223BB78: .word 0x000009E7
	thumb_func_end MOD18_0223BB54

	thumb_func_start MOD18_0223BB7C
MOD18_0223BB7C: ; 0x0223BB7C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r1, _0223BC44 ; =0x02251380
	str r0, [sp]
	ldr r2, [r1]
	ldr r1, _0223BC48 ; =0x000009E7
	ldrb r4, [r2, r1]
	mov r1, #0
	bl FUN_0201886C
	add r5, r0, #0
	asr r0, r4, #1
	lsr r0, r0, #0x1e
	add r0, r4, r0
	asr r0, r0, #2
	lsl r4, r0, #2
	add r0, sp, #4
	bl MOD18_0223BB54
	add r0, r4, #0
	mov r1, #0x18
	bl _s32_div_f
	ldr r0, _0223BC44 ; =0x02251380
	ldr r2, [r0]
	mov r0, #0x7b
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	asr r2, r1, #1
	lsr r2, r2, #0x1e
	add r2, r1, r2
	asr r2, r2, #2
	mov r1, #6
	sub r1, r1, r2
	bl FUN_02020130
	add r4, #8
	mov r0, #0xd0
	sub r1, r0, r4
	asr r0, r1, #2
	lsr r0, r0, #0x1d
	add r0, r1, r0
	asr r7, r0, #3
	mov r4, #0
	cmp r7, #0
	ble _0223BC38
_0223BBD8:
	mov r0, #0x19
	sub r0, r0, r4
	lsl r6, r0, #1
	add r0, r4, #0
	mov r1, #3
	bl _s32_div_f
	add r0, r1, #0
	mov r1, #0x3f
	ldrh r2, [r5, r6]
	lsl r1, r1, #0xa
	and r1, r2
	add r1, #0xb
	sub r1, r1, r0
	strh r1, [r5, r6]
	mov r1, #0x39
	sub r1, r1, r4
	lsl r1, r1, #1
	mov r2, #0x3f
	ldrh r3, [r5, r1]
	lsl r2, r2, #0xa
	and r2, r3
	add r2, #0x41
	sub r2, r2, r0
	strh r2, [r5, r1]
	mov r1, #0x59
	sub r1, r1, r4
	lsl r1, r1, #1
	mov r2, #0x3f
	ldrh r3, [r5, r1]
	lsl r2, r2, #0xa
	and r2, r3
	add r2, #0x77
	sub r2, r2, r0
	strh r2, [r5, r1]
	mov r1, #0x79
	sub r1, r1, r4
	lsl r1, r1, #1
	mov r2, #0x3f
	ldrh r3, [r5, r1]
	lsl r2, r2, #0xa
	add r4, r4, #1
	and r2, r3
	add r2, #0xad
	sub r0, r2, r0
	strh r0, [r5, r1]
	cmp r4, r7
	blt _0223BBD8
_0223BC38:
	ldr r0, [sp]
	mov r1, #0
	bl FUN_02017CD0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223BC44: .word MOD18_02251380
_0223BC48: .word 0x000009E7
	thumb_func_end MOD18_0223BB7C

	thumb_func_start MOD18_0223BC4C
MOD18_0223BC4C: ; 0x0223BC4C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r5, #0
	str r0, [sp]
	str r5, [sp, #4]
_0223BC56:
	ldr r0, _0223BCF4 ; =0x02251380
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _0223BCF8 ; =0x000008CC
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _0223BCDA
	ldr r0, _0223BCFC ; =0x000008D4
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _0223BCDA
	bl FUN_02031190
	bl FUN_0204E3EC
	add r4, r0, #0
	bl FUN_02031190
	bl FUN_0204E440
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0204E35C
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0204E3A4
	add r1, r4, #0
	sub r1, #0xa
	cmp r7, r1
	ble _0223BCDA
	add r4, #0xa
	cmp r7, r4
	bge _0223BCDA
	add r1, r6, #0
	sub r1, #0xa
	cmp r0, r1
	ble _0223BCDA
	add r6, #0xa
	cmp r0, r6
	bge _0223BCDA
	ldr r0, _0223BCF4 ; =0x02251380
	ldr r1, _0223BCFC ; =0x000008D4
	ldr r0, [r0]
	ldr r3, [sp]
	add r2, r0, r5
	ldr r0, _0223BCF8 ; =0x000008CC
	ldrb r1, [r2, r1]
	ldrb r0, [r2, r0]
	mov r2, #1
	bl MOD18_0223B7AC
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, _0223BCF4 ; =0x02251380
	mov r1, #0xff
	ldr r0, [r0]
	add r2, r0, r5
	ldr r0, _0223BCF8 ; =0x000008CC
	strb r1, [r2, r0]
	ldr r0, _0223BCF4 ; =0x02251380
	ldr r0, [r0]
	add r2, r0, r5
	ldr r0, _0223BCFC ; =0x000008D4
	strb r1, [r2, r0]
_0223BCDA:
	add r5, r5, #1
	cmp r5, #8
	blt _0223BC56
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _0223BCF0
	ldr r0, _0223BCF4 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223B6A4
_0223BCF0:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223BCF4: .word MOD18_02251380
_0223BCF8: .word 0x000008CC
_0223BCFC: .word 0x000008D4
	thumb_func_end MOD18_0223BC4C

	thumb_func_start MOD18_0223BD00
MOD18_0223BD00: ; 0x0223BD00
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	bl MOD18_0223D194
	cmp r0, #0
	beq _0223BD88
	cmp r6, #6
	beq _0223BD1C
	cmp r6, #7
	beq _0223BD1C
	sub r0, r6, #1
	cmp r0, #1
	bhi _0223BD42
_0223BD1C:
	ldr r0, _0223BD8C ; =0x02251380
	ldr r5, [r0]
	add r4, r5, #0
	add r4, #8
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r4, #4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #8]
	mov r0, #0
	str r3, [r4, #4]
	add r4, r0, #1
	b _0223BD6C
_0223BD42:
	ldr r0, _0223BD8C ; =0x02251380
	ldr r5, [r0]
	add r4, r5, #0
	add r4, #8
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r4, #4]
	bl _ll_mul
	ldr r3, [r4, #0x10]
	ldr r2, [r4, #0x14]
	add r0, r3, r0
	adc r2, r1
	str r0, [r5, #8]
	mov r1, #0
	lsr r0, r2, #0x1e
	lsl r1, r1, #2
	orr r1, r0
	str r2, [r4, #4]
	add r4, r1, #1
_0223BD6C:
	sub r0, r6, #6
	cmp r0, #4
	bhi _0223BD74
	add r4, #0xa
_0223BD74:
	ldr r0, _0223BD90 ; =0x000009E7
	mov r1, #0x27
	ldrb r5, [r5, r0]
	add r0, r5, #0
	bl _s32_div_f
	add r4, r4, r0
	cmp r5, #0
	beq _0223BD88
	add r4, r4, #5
_0223BD88:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223BD8C: .word MOD18_02251380
_0223BD90: .word 0x000009E7
	thumb_func_end MOD18_0223BD00

	thumb_func_start MOD18_0223BD94
MOD18_0223BD94: ; 0x0223BD94
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _0223BDDC ; =0x02251380
	add r4, r1, #0
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	ldr r0, _0223BDDC ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD18_0223D194
	cmp r0, #0
	beq _0223BDCC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02249450
	pop {r4, r5, r6, pc}
_0223BDCC:
	add r0, r5, #0
	bl MOD18_02249480
	add r0, r6, #0
	add r1, r5, #0
	bl FUN_02026664
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223BDDC: .word MOD18_02251380
	thumb_func_end MOD18_0223BD94

	thumb_func_start MOD18_0223BDE0
MOD18_0223BDE0: ; 0x0223BDE0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _0223BE24 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r5, r0, #0
	add r0, r4, #0
	bl MOD18_0223D194
	cmp r0, #0
	beq _0223BE10
	add r0, r5, #0
	bl FUN_02026050
	cmp r0, #0x28
	beq _0223BE0C
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223BE0C:
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223BE10:
	add r0, r5, #0
	bl FUN_0202616C
	cmp r0, #0x28
	beq _0223BE1E
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223BE1E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0223BE24: .word MOD18_02251380
	thumb_func_end MOD18_0223BDE0

	thumb_func_start MOD18_0223BE28
MOD18_0223BE28: ; 0x0223BE28
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	mov r0, #1
	mov lr, r0
	ldr r0, [r4, #0xc]
	mov r2, #0
	cmp r0, #0
	ble _0223BE48
	add r3, sp, #0
	mov r1, #1
_0223BE3E:
	stmia r3!, {r1}
	ldr r0, [r4, #0xc]
	add r2, r2, #1
	cmp r2, r0
	blt _0223BE3E
_0223BE48:
	mov r0, #0
	mov ip, r0
	ldr r0, _0223BED4 ; =0x02251380
	mov r6, #0
	ldr r3, [r0]
	add r7, sp, #0
_0223BE54:
	mov r2, #0
_0223BE56:
	ldr r0, _0223BED8 ; =0x000008DC
	add r1, r3, r2
	ldrb r0, [r1, r0]
	ldr r5, [r4, #0xc]
	cmp r0, r5
	bgt _0223BE76
	cmp r0, #0
	beq _0223BE76
	ldr r5, _0223BEDC ; =0x0000095E
	ldrb r1, [r1, r5]
	cmp r1, #0
	beq _0223BE76
	lsl r0, r0, #2
	add r0, r7, r0
	sub r0, r0, #4
	str r6, [r0]
_0223BE76:
	add r2, r2, #1
	cmp r2, #0xd
	blt _0223BE56
	mov r0, ip
	add r0, r0, #1
	add r3, #0xd
	mov ip, r0
	cmp r0, #0xa
	blt _0223BE54
	ldr r0, [r4, #0xc]
	mov r3, #0
	cmp r0, #0
	ble _0223BECC
	add r0, sp, #0
	add r1, r3, #0
	add r2, r4, #0
	mov r7, #1
_0223BE98:
	ldr r5, [r0]
	cmp r5, #0
	bne _0223BEA4
	mov r5, #0
	mov lr, r5
	b _0223BEBE
_0223BEA4:
	ldr r5, _0223BED4 ; =0x02251380
	ldr r5, [r5]
	add r6, r5, r1
	ldr r5, _0223BEE0 ; =0x00000818
	ldrb r5, [r6, r5]
	cmp r5, #0
	bne _0223BEBE
	ldr r5, _0223BED4 ; =0x02251380
	str r7, [r2, #0x38]
	ldr r5, [r5]
	add r6, r5, r1
	ldr r5, _0223BEE0 ; =0x00000818
	strb r7, [r6, r5]
_0223BEBE:
	ldr r5, [r4, #0xc]
	add r3, r3, #1
	add r0, r0, #4
	add r1, #0xc
	add r2, r2, #4
	cmp r3, r5
	blt _0223BE98
_0223BECC:
	mov r0, lr
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223BED4: .word MOD18_02251380
_0223BED8: .word 0x000008DC
_0223BEDC: .word 0x0000095E
_0223BEE0: .word 0x00000818
	thumb_func_end MOD18_0223BE28

	thumb_func_start MOD18_0223BEE4
MOD18_0223BEE4: ; 0x0223BEE4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r1, [r5, #0xc]
	mov r0, #0
	cmp r1, #0
	ble _0223BF74
	ldr r2, _0223BF78 ; =0x02251380
	ldr r3, _0223BF7C ; =0x00000818
	ldr r2, [r2]
	add r6, r2, #0
_0223BEF8:
	ldrb r4, [r6, r3]
	cmp r4, #1
	bne _0223BF6C
	add r4, r0, #0
	mov r1, #0xc
	mul r4, r1
	ldr r0, _0223BF80 ; =0x00000814
	add r1, r2, r4
	ldrb r0, [r1, r0]
	bl MOD18_0223BD00
	str r0, [r5, #0x48]
	bl MOD18_0223D638
	ldr r1, _0223BF78 ; =0x02251380
	ldr r1, [r1]
	add r2, r1, r4
	ldr r1, _0223BF80 ; =0x00000814
	ldrb r1, [r2, r1]
	bl MOD18_0224DDD0
	ldr r0, _0223BF78 ; =0x02251380
	ldr r0, [r0]
	add r1, r0, r4
	ldr r0, _0223BF80 ; =0x00000814
	ldrb r0, [r1, r0]
	bl MOD18_0223D194
	cmp r0, #0
	beq _0223BF44
	mov r4, #0x45
	bl MOD18_0223D638
	ldr r2, [r5, #0x48]
	mov r1, #1
	bl MOD18_0224DEA4
	b _0223BF50
_0223BF44:
	mov r4, #0x11
	bl MOD18_0223D638
	mov r1, #2
	bl MOD18_0224DF54
_0223BF50:
	bl MOD18_0223D638
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r1, _0223BF78 ; =0x02251380
	ldr r2, [r1]
	mov r1, #0x9e
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #1
	pop {r4, r5, r6, pc}
_0223BF6C:
	add r0, r0, #1
	add r6, #0xc
	cmp r0, r1
	blt _0223BEF8
_0223BF74:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223BF78: .word MOD18_02251380
_0223BF7C: .word 0x00000818
_0223BF80: .word 0x00000814
	thumb_func_end MOD18_0223BEE4

	thumb_func_start MOD18_0223BF84
MOD18_0223BF84: ; 0x0223BF84
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, _0223C070 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CB4
	add r7, r0, #0
	ldr r0, _0223C070 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	ldr r5, [r4, #0xc]
	mov r2, #0
	cmp r5, #0
	ble _0223C06A
	ldr r0, _0223C070 ; =0x02251380
	ldr r6, [r0]
	ldr r0, _0223C074 ; =0x00000818
	add r3, r6, #0
_0223BFB2:
	ldrb r1, [r3, r0]
	cmp r1, #1
	bne _0223C062
	mov r0, #0xc
	mul r0, r2
	ldr r1, _0223C074 ; =0x00000818
	mov r3, #0
	add r2, r6, r0
	strb r3, [r2, r1]
	ldr r2, _0223C070 ; =0x02251380
	ldr r2, [r2]
	add r2, r2, r0
	sub r0, r1, #4
	ldrb r5, [r2, r0]
	add r0, r5, #0
	bl MOD18_0223D194
	cmp r0, #0
	beq _0223BFE2
	add r0, r7, #0
	mov r1, #1
	bl FUN_02026A0C
	b _0223C032
_0223BFE2:
	ldr r0, _0223C070 ; =0x02251380
	add r1, r5, #0
	ldr r0, [r0]
	mov r2, #1
	ldr r0, [r0]
	bl FUN_0206151C
	cmp r5, #0x17
	blt _0223BFF8
	cmp r5, #0x1d
	blt _0223C000
_0223BFF8:
	add r0, r5, #0
	sub r0, #0x24
	cmp r0, #1
	bhi _0223C02A
_0223C000:
	add r0, r7, #0
	mov r1, #1
	bl FUN_02026A58
	ldr r0, _0223C070 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	bl FUN_0205F740
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	bl FUN_0205F750
	b _0223C032
_0223C02A:
	add r0, r7, #0
	mov r1, #1
	bl FUN_02026A9C
_0223C032:
	add r0, r5, #0
	bl MOD18_0223BDE0
	cmp r0, #0
	beq _0223C046
	ldr r1, [r4, #0x48]
	add r0, r5, #0
	bl MOD18_0223BD94
	b _0223C06A
_0223C046:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x41
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r1, _0223C070 ; =0x02251380
	ldr r2, [r1]
	mov r1, #0x9e
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223C062:
	add r2, r2, #1
	add r3, #0xc
	cmp r2, r5
	blt _0223BFB2
_0223C06A:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223C070: .word MOD18_02251380
_0223C074: .word 0x00000818
	thumb_func_end MOD18_0223BF84

	thumb_func_start MOD18_0223C078
MOD18_0223C078: ; 0x0223C078
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r0, _0223C178 ; =0x02251380
	ldr r4, [r0]
	ldr r0, _0223C17C ; =0x000009E8
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _0223C174
	sub r0, r0, #1
	ldrb r1, [r4, r0]
	mov r0, #0xc4
	sub r6, r0, r1
	add r0, r6, #0
	mov r1, #0x32
	bl _s32_div_f
	add r7, r0, #0
	ldr r0, _0223C17C ; =0x000009E8
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldr r0, _0223C178 ; =0x02251380
	mov r1, #0xf
	ldr r5, [r0]
	add r0, r6, #0
	bl _s32_div_f
	ldr r1, _0223C17C ; =0x000009E8
	ldrb r2, [r5, r1]
	cmp r2, r0
	ble _0223C0CA
	mov r2, #0
	add r0, r1, #2
	strb r2, [r5, r0]
	ldr r0, _0223C178 ; =0x02251380
	ldr r3, [r0]
	add r0, r1, #2
	ldrsb r2, [r3, r0]
	add r0, r1, #1
	strb r2, [r3, r0]
	b _0223C146
_0223C0CA:
	add r4, r5, #0
	add r4, #8
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r4, #4]
	bl _ll_mul
	ldr r2, [r4, #0x10]
	ldr r3, [r4, #0x14]
	add r0, r2, r0
	adc r3, r1
	str r0, [r5, #8]
	str r3, [r4, #4]
	add r6, r7, #3
	bne _0223C0EE
	ldr r1, [r4, #4]
	b _0223C0FA
_0223C0EE:
	ldr r0, [r4, #4]
	mov r1, #0
	mov r3, #0
	add r2, r6, #0
	bl _ll_mul
_0223C0FA:
	add r2, r7, #3
	lsr r0, r2, #0x1f
	add r0, r2, r0
	asr r7, r0, #1
	ldr r0, _0223C180 ; =0x000009E9
	sub r1, r1, r7
	strb r1, [r5, r0]
	ldr r0, _0223C178 ; =0x02251380
	ldr r5, [r0]
	add r4, r5, #0
	add r4, #8
	ldr r0, [r4, #8]
	ldr r1, [r4, #0xc]
	ldr r2, [r5, #8]
	ldr r3, [r4, #4]
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	add r0, r0, r2
	adc r1, r3
	str r0, [r5, #8]
	str r1, [r4, #4]
	cmp r6, #0
	bne _0223C134
	ldr r1, [r4, #4]
	b _0223C140
_0223C134:
	ldr r0, [r4, #4]
	mov r1, #0
	mov r3, #0
	add r2, r6, #0
	bl _ll_mul
_0223C140:
	ldr r0, _0223C184 ; =0x000009EA
	sub r1, r1, r7
	strb r1, [r5, r0]
_0223C146:
	add r0, sp, #0
	bl MOD18_0223BB54
	ldr r0, _0223C178 ; =0x02251380
	ldr r1, _0223C180 ; =0x000009E9
	ldr r0, [r0]
	ldr r3, [sp]
	ldrsb r2, [r0, r1]
	add r1, r1, #1
	lsl r2, r2, #0xc
	sub r2, r3, r2
	str r2, [sp]
	ldrsb r1, [r0, r1]
	ldr r2, [sp, #4]
	lsl r1, r1, #0xc
	sub r1, r2, r1
	str r1, [sp, #4]
	mov r1, #0x7b
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	add r1, sp, #0
	bl FUN_02020044
_0223C174:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223C178: .word MOD18_02251380
_0223C17C: .word 0x000009E8
_0223C180: .word 0x000009E9
_0223C184: .word 0x000009EA
	thumb_func_end MOD18_0223C078

	thumb_func_start MOD18_0223C188
MOD18_0223C188: ; 0x0223C188
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _0223C1E0 ; =0x02251380
	ldr r4, [r0]
	ldr r0, _0223C1E4 ; =0x000009E8
	ldrb r6, [r4, r0]
	cmp r6, #0
	beq _0223C1DE
	sub r0, r0, #1
	ldrb r1, [r4, r0]
	mov r0, #0xc4
	sub r0, r0, r1
	mov r1, #0xa
	bl _s32_div_f
	cmp r6, r0
	ble _0223C1B0
	ldr r0, _0223C1E4 ; =0x000009E8
	mov r1, #0
	strb r1, [r4, r0]
_0223C1B0:
	ldr r7, _0223C1E0 ; =0x02251380
	mov r4, #0
_0223C1B4:
	ldr r6, [r7]
	ldr r3, _0223C1E8 ; =0x000009E9
	lsl r1, r4, #0x18
	ldrsb r3, [r6, r3]
	add r0, r5, #0
	lsr r1, r1, #0x18
	mov r2, #0
	bl FUN_020179E0
	lsl r1, r4, #0x18
	ldr r6, [r7]
	ldr r3, _0223C1EC ; =0x000009EA
	add r0, r5, #0
	ldrsb r3, [r6, r3]
	lsr r1, r1, #0x18
	mov r2, #3
	bl FUN_020179E0
	add r4, r4, #1
	cmp r4, #3
	blt _0223C1B4
_0223C1DE:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C1E0: .word MOD18_02251380
_0223C1E4: .word 0x000009E8
_0223C1E8: .word 0x000009E9
_0223C1EC: .word 0x000009EA
	thumb_func_end MOD18_0223C188

	thumb_func_start MOD18_0223C1F0
MOD18_0223C1F0: ; 0x0223C1F0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, _0223C338 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r6, r0, #0
	ldr r0, _0223C338 ; =0x02251380
	ldr r2, [r0]
	ldr r0, _0223C33C ; =0x000009E5
	ldrb r1, [r2, r0]
	cmp r1, #1
	bne _0223C216
	mov r1, #0
	strb r1, [r2, r0]
_0223C216:
	ldr r1, _0223C340 ; =gMain + 0x40
	ldrh r0, [r1, #0x20]
	cmp r0, #0
	beq _0223C29A
	ldrh r0, [r1, #0x1c]
	cmp r0, #0xd0
	bhs _0223C28C
	ldrh r1, [r1, #0x1e]
	cmp r1, #0x20
	blo _0223C28C
	add r2, sp, #0
	strb r0, [r2]
	strb r1, [r2, #1]
	ldr r2, _0223C338 ; =0x02251380
	ldr r3, [r2]
	ldr r2, _0223C344 ; =0x000009E4
	ldrb r2, [r3, r2]
	add r3, r5, #0
	bl MOD18_0223B7AC
	ldr r0, _0223C338 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C344 ; =0x000009E4
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223C24E
	mov r4, #4
	b _0223C250
_0223C24E:
	mov r4, #8
_0223C250:
	mov r0, #0x44
	add r1, sp, #0
	bl FUN_020311D0
	ldr r0, _0223C338 ; =0x02251380
	ldr r1, _0223C348 ; =0x000009E7
	ldr r0, [r0]
	ldrb r2, [r0, r1]
	cmp r2, r4
	ble _0223C268
	sub r2, r2, r4
	b _0223C26A
_0223C268:
	mov r2, #0
_0223C26A:
	strb r2, [r0, r1]
	ldr r0, _0223C338 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223B6A4
	ldr r0, _0223C338 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0, #4]
	bl MOD18_0223BB7C
	ldr r0, _0223C338 ; =0x02251380
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _0223C34C ; =0x000009E8
	strb r2, [r1, r0]
	b _0223C29A
_0223C28C:
	cmp r0, #0xd0
	blo _0223C29A
	ldr r0, _0223C338 ; =0x02251380
	mov r2, #2
	ldr r1, [r0]
	ldr r0, _0223C33C ; =0x000009E5
	strb r2, [r1, r0]
_0223C29A:
	ldr r0, [r5, #0x14]
	cmp r0, #0
	beq _0223C2AC
	sub r0, r0, #1
	str r0, [r5, #0x14]
	bne _0223C2AC
	ldr r0, _0223C350 ; =0x000006A5
	bl FUN_020054C8
_0223C2AC:
	ldr r0, _0223C338 ; =0x02251380
	ldr r2, _0223C340 ; =gMain + 0x40
	ldr r3, [r0]
	ldr r4, _0223C33C ; =0x000009E5
	ldr r0, [r3, #4]
	ldrh r1, [r2, #0x1c]
	ldrh r2, [r2, #0x1e]
	ldrb r3, [r3, r4]
	bl MOD18_0223B9EC
	ldr r0, _0223C338 ; =0x02251380
	ldr r2, [r0]
	add r0, r4, #0
	ldrb r1, [r2, r0]
	cmp r1, #2
	blo _0223C2D0
	add r1, r1, #1
	strb r1, [r2, r0]
_0223C2D0:
	add r0, r5, #0
	bl MOD18_0223BC4C
	add r0, r5, #0
	bl MOD18_0223BE28
	cmp r0, #0
	beq _0223C30A
	add r0, r6, #0
	bl FUN_02026634
	ldr r0, _0223C338 ; =0x02251380
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x1e
	bl FUN_0202A170
	mov r0, #0xe
	str r0, [r5]
	mov r0, #0x19
	str r0, [r5, #8]
	mov r0, #1
	add r5, #0x50
	add sp, #4
	strb r0, [r5]
	pop {r3, r4, r5, r6, pc}
_0223C30A:
	ldr r0, _0223C338 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C348 ; =0x000009E7
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223C332
	add r0, r6, #0
	bl FUN_02026634
	add r0, r5, #0
	mov r1, #0
	add r0, #0x50
	strb r1, [r0]
	mov r0, #0x2d
	str r0, [r5, #8]
	mov r0, #0x16
	str r0, [r5]
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0223C332:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223C338: .word MOD18_02251380
_0223C33C: .word 0x000009E5
_0223C340: .word gMain + 0x40
_0223C344: .word 0x000009E4
_0223C348: .word 0x000009E7
_0223C34C: .word 0x000009E8
_0223C350: .word 0x000006A5
	thumb_func_end MOD18_0223C1F0

	thumb_func_start MOD18_0223C354
MOD18_0223C354: ; 0x0223C354
	push {r3, r4}
	ldr r3, _0223C374 ; =0x02251380
	ldr r2, _0223C378 ; =0x000009EB
	ldr r4, [r3]
	ldrb r1, [r4, r2]
	lsl r1, r1, #2
	add r4, r4, r1
	mov r1, #0x57
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r1, [r3]
	ldrb r0, [r1, r2]
	add r0, r0, #1
	strb r0, [r1, r2]
	pop {r3, r4}
	bx lr
	.align 2, 0
_0223C374: .word MOD18_02251380
_0223C378: .word 0x000009EB
	thumb_func_end MOD18_0223C354

	thumb_func_start MOD18_0223C37C
MOD18_0223C37C: ; 0x0223C37C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r0, _0223C568 ; =0x02251380
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _0223C56C ; =0x000009EB
	strb r2, [r1, r0]
	bl FUN_020B0FC0
	mov r0, #0
	str r0, [sp]
	mov r1, #0x7c
	str r1, [sp, #4]
	str r0, [sp, #8]
	mov r3, #0x1f
	str r3, [sp, #0xc]
	mov r2, #0x1d
	str r2, [sp, #0x10]
	add r2, r0, #0
	bl FUN_02009EAC
	bl MOD18_0223C680
	ldr r1, _0223C568 ; =0x02251380
	mov r0, #0x1a
	ldr r1, [r1]
	mov r2, #0x1d
	add r1, #0x24
	bl FUN_02008C9C
	ldr r1, _0223C568 ; =0x02251380
	ldr r2, [r1]
	str r0, [r2, #0x20]
	ldr r0, [r1]
	mov r2, #6
	add r0, #0x24
	mov r1, #0
	lsl r2, r2, #0x12
	bl FUN_02008D24
	mov r4, #0
	mov r7, #0x53
	ldr r6, _0223C568 ; =0x02251380
	add r5, r4, #0
	lsl r7, r7, #2
_0223C3D6:
	mov r0, #2
	add r1, r4, #0
	mov r2, #0x1d
	bl FUN_02008DEC
	ldr r1, [r6]
	add r4, r4, #1
	add r1, r1, r5
	add r5, r5, #4
	str r0, [r1, r7]
	cmp r4, #4
	blt _0223C3D6
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0x1d
	str r0, [sp, #8]
	ldr r0, _0223C568 ; =0x02251380
	mov r2, #6
	ldr r1, [r0]
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x40
	bl FUN_02008F34
	bl MOD18_0223C354
	ldr r0, _0223C568 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C56C ; =0x000009EB
	ldrb r0, [r1, r0]
	sub r0, r0, #1
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009A50
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0x1d
	str r0, [sp, #0xc]
	ldr r0, _0223C568 ; =0x02251380
	mov r2, #7
	ldr r1, [r0]
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0x40
	bl FUN_02008FEC
	bl MOD18_0223C354
	ldr r0, _0223C568 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C56C ; =0x000009EB
	ldrb r0, [r1, r0]
	sub r0, r0, #1
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #0x1d
	str r0, [sp, #8]
	ldr r0, _0223C568 ; =0x02251380
	mov r2, #5
	ldr r1, [r0]
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x40
	bl FUN_020090AC
	bl MOD18_0223C354
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x1d
	str r0, [sp, #8]
	ldr r0, _0223C568 ; =0x02251380
	mov r2, #4
	ldr r1, [r0]
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x40
	bl FUN_020090AC
	bl MOD18_0223C354
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #0x1d
	str r0, [sp, #8]
	ldr r0, _0223C568 ; =0x02251380
	mov r2, #3
	ldr r1, [r0]
	mov r0, #0x53
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x40
	mov r3, #0
	bl FUN_02008F34
	bl MOD18_0223C354
	ldr r0, _0223C568 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C56C ; =0x000009EB
	ldrb r0, [r1, r0]
	sub r0, r0, #1
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009A50
	mov r2, #1
	str r2, [sp]
	str r2, [sp, #4]
	mov r0, #3
	str r0, [sp, #8]
	mov r0, #0x1d
	str r0, [sp, #0xc]
	ldr r0, _0223C568 ; =0x02251380
	mov r3, #0
	ldr r1, [r0]
	mov r0, #0x15
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0x34
	bl FUN_02008FEC
	bl MOD18_0223C354
	ldr r0, _0223C568 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C56C ; =0x000009EB
	ldrb r0, [r1, r0]
	sub r0, r0, #1
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #0x57
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	mov r0, #1
	str r0, [sp]
	mov r2, #2
	str r2, [sp, #4]
	mov r0, #0x1d
	str r0, [sp, #8]
	ldr r0, _0223C568 ; =0x02251380
	mov r3, #0
	ldr r1, [r0]
	mov r0, #0x55
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x40
	bl FUN_020090AC
	bl MOD18_0223C354
	mov r2, #1
	str r2, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #0x1d
	str r0, [sp, #8]
	ldr r0, _0223C568 ; =0x02251380
	mov r3, #0
	ldr r1, [r0]
	mov r0, #0x56
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x40
	bl FUN_020090AC
	bl MOD18_0223C354
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0223C568: .word MOD18_02251380
_0223C56C: .word 0x000009EB
	thumb_func_end MOD18_0223C37C

	thumb_func_start MOD18_0223C570
MOD18_0223C570: ; 0x0223C570
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	mov r7, #0
	str r7, [sp, #0x30]
	str r7, [sp, #0x2c]
_0223C57A:
	ldr r0, _0223C67C ; =0x02251380
	mov r3, #0x53
	ldr r1, [r0]
	mov r0, #0
	str r7, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #2
	ldr r2, [r1, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r1, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r1, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r1, r2]
	add r3, #0x54
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r1, r1, r3
	ldr r0, [sp, #0x30]
	add r2, r7, #0
	add r0, r1, r0
	add r1, r7, #0
	add r3, r7, #0
	bl FUN_02008AA4
	ldr r6, _0223C67C ; =0x02251380
	mov r2, #2
	ldr r1, [r6]
	lsl r2, r2, #0x10
	ldr r0, [r1, #0x20]
	str r0, [sp, #0x34]
	mov r0, #0x1a
	lsl r0, r0, #4
	add r1, r1, r0
	ldr r0, [sp, #0x30]
	str r2, [sp, #0x3c]
	add r0, r1, r0
	str r0, [sp, #0x38]
	mov r0, #6
	lsl r0, r0, #0x10
	str r0, [sp, #0x40]
	lsr r0, r2, #5
	mov r1, #0
	str r1, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x50]
	add r0, sp, #0x34
	strh r1, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x5c]
	mov r0, #0x1d
	str r0, [sp, #0x60]
	mov r0, #0xf
	lsl r0, r0, #0x10
	str r1, [sp, #0x58]
	str r1, [sp, #0x3c]
	str r0, [sp, #0x40]
	cmp r7, #0
	bne _0223C634
	mov r4, #2
	mov r5, #8
_0223C60C:
	add r0, sp, #0x34
	bl FUN_0201FE94
	ldr r1, [r6]
	add r2, r1, r5
	mov r1, #0x7a
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r6]
	add r1, r0, r5
	mov r0, #0x7a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	ble _0223C60C
_0223C634:
	add r0, sp, #0x34
	bl FUN_0201FE94
	ldr r2, _0223C67C ; =0x02251380
	ldr r1, [sp, #0x2c]
	ldr r3, [r2]
	add r3, r3, r1
	mov r1, #0x7a
	lsl r1, r1, #2
	str r0, [r3, r1]
	ldr r2, [r2]
	ldr r0, [sp, #0x2c]
	add r0, r2, r0
	ldr r0, [r0, r1]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [sp, #0x30]
	add r7, r7, #1
	add r0, #0x24
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x2c]
	add r0, r0, #4
	str r0, [sp, #0x2c]
	cmp r7, #2
	blt _0223C57A
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223C67C: .word MOD18_02251380
	thumb_func_end MOD18_0223C570

	thumb_func_start MOD18_0223C680
MOD18_0223C680: ; 0x0223C680
	push {r4, lr}
	sub sp, #0x10
	ldr r4, _0223C6C0 ; =0x0224FFF0
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r1, _0223C6C4 ; =0x00200010
	add r0, r2, #0
	add r2, r1, #0
	bl FUN_0201D060
	mov r0, #0x14
	mov r1, #0x1d
	bl FUN_0201E00C
	bl FUN_0201D168
	bl FUN_0201E0BC
	ldr r1, _0223C6C8 ; =0x00100010
	mov r0, #1
	bl FUN_02008D44
	mov r0, #1
	bl FUN_02008DDC
	add sp, #0x10
	pop {r4, pc}
	nop
_0223C6C0: .word MOD18_0224FFF0
_0223C6C4: .word 0x00200010
_0223C6C8: .word 0x00100010
	thumb_func_end MOD18_0223C680

	thumb_func_start MOD18_0223C6CC
MOD18_0223C6CC: ; 0x0223C6CC
	push {r4, lr}
	add r4, r0, #0
	bl MOD18_0223C188
	add r0, r4, #0
	bl FUN_0201AB60
	bl FUN_0201C30C
	bl FUN_02009F80
	pop {r4, pc}
	thumb_func_end MOD18_0223C6CC

	thumb_func_start MOD18_0223C6E4
MOD18_0223C6E4: ; 0x0223C6E4
	push {r3, lr}
	lsl r0, r0, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	bl MOD18_02239DEC
	cmp r0, #0
	beq _0223C6FA
	mov r0, #1
	pop {r3, pc}
_0223C6FA:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0223C6E4

	thumb_func_start MOD18_0223C700
MOD18_0223C700: ; 0x0223C700
	ldr r1, _0223C718 ; =0x02251380
	ldr r2, [r1]
	cmp r2, #0
	beq _0223C714
	mov r1, #6
	mul r1, r0
	ldr r0, _0223C71C ; =0x00000888
	add r1, r2, r1
	ldrh r0, [r1, r0]
	bx lr
_0223C714:
	mov r0, #0
	bx lr
	.align 2, 0
_0223C718: .word MOD18_02251380
_0223C71C: .word 0x00000888
	thumb_func_end MOD18_0223C700

	thumb_func_start MOD18_0223C720
MOD18_0223C720: ; 0x0223C720
	ldr r1, _0223C738 ; =0x02251380
	ldr r2, [r1]
	cmp r2, #0
	beq _0223C734
	mov r1, #6
	mul r1, r0
	ldr r0, _0223C73C ; =0x0000088A
	add r1, r2, r1
	ldrh r0, [r1, r0]
	bx lr
_0223C734:
	mov r0, #0
	bx lr
	.align 2, 0
_0223C738: .word MOD18_02251380
_0223C73C: .word 0x0000088A
	thumb_func_end MOD18_0223C720

	thumb_func_start MOD18_0223C740
MOD18_0223C740: ; 0x0223C740
	push {r4, lr}
	ldr r1, _0223C76C ; =0x02251380
	ldr r2, [r1]
	cmp r2, #0
	beq _0223C766
	ldr r1, _0223C770 ; =0x00000884
	ldr r4, [r2, r1]
	cmp r4, #0
	beq _0223C766
	ldr r1, _0223C774 ; =0x000005DE
	ldrh r1, [r4, r1]
	add r0, r1, r0
	mov r1, #0x53
	bl _s32_div_f
	mov r0, #6
	mul r0, r1
	ldrh r0, [r4, r0]
	pop {r4, pc}
_0223C766:
	mov r0, #0
	pop {r4, pc}
	nop
_0223C76C: .word MOD18_02251380
_0223C770: .word 0x00000884
_0223C774: .word 0x000005DE
	thumb_func_end MOD18_0223C740

	thumb_func_start MOD18_0223C778
MOD18_0223C778: ; 0x0223C778
	push {r4, lr}
	ldr r1, _0223C7A4 ; =0x02251380
	ldr r2, [r1]
	cmp r2, #0
	beq _0223C7A0
	ldr r1, _0223C7A8 ; =0x00000884
	ldr r4, [r2, r1]
	cmp r4, #0
	beq _0223C7A0
	ldr r1, _0223C7AC ; =0x000005DE
	ldrh r1, [r4, r1]
	add r0, r1, r0
	mov r1, #0x53
	bl _s32_div_f
	mov r0, #6
	mul r0, r1
	add r0, r4, r0
	ldrh r0, [r0, #2]
	pop {r4, pc}
_0223C7A0:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0223C7A4: .word MOD18_02251380
_0223C7A8: .word 0x00000884
_0223C7AC: .word 0x000005DE
	thumb_func_end MOD18_0223C778

	thumb_func_start MOD18_0223C7B0
MOD18_0223C7B0: ; 0x0223C7B0
	push {r4, lr}
	ldr r0, _0223C7D0 ; =0x000005DE
	add r4, r1, #0
	ldrh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, r0]
	ldrh r1, [r4, r0]
	cmp r1, #0x53
	bls _0223C7CE
	add r0, #0x43
	bl FUN_020054C8
	ldr r0, _0223C7D0 ; =0x000005DE
	mov r1, #0
	strh r1, [r4, r0]
_0223C7CE:
	pop {r4, pc}
	.align 2, 0
_0223C7D0: .word 0x000005DE
	thumb_func_end MOD18_0223C7B0

	thumb_func_start MOD18_0223C7D4
MOD18_0223C7D4: ; 0x0223C7D4
	push {r4, lr}
	ldr r0, _0223C834 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C838 ; =0x00000884
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223C7E6
	bl ErrorHandling
_0223C7E6:
	ldr r0, _0223C834 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C83C ; =0x00000878
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223C7F6
	bl ErrorHandling
_0223C7F6:
	mov r1, #0x5e
	mov r0, #0xb
	lsl r1, r1, #4
	bl AllocFromHeapAtEnd
	mov r2, #0x5e
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x47
	bl FUN_020311DC
	ldr r0, _0223C840 ; =0x000005DE
	mov r1, #0x49
	strh r1, [r4, r0]
	ldr r0, _0223C834 ; =0x02251380
	mov r2, #0x64
	ldr r1, [r0]
	ldr r0, _0223C838 ; =0x00000884
	str r4, [r1, r0]
	ldr r0, _0223C844 ; =MOD18_0223C7B0
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _0223C834 ; =0x02251380
	ldr r2, [r1]
	ldr r1, _0223C83C ; =0x00000878
	str r0, [r2, r1]
	pop {r4, pc}
	.align 2, 0
_0223C834: .word MOD18_02251380
_0223C838: .word 0x00000884
_0223C83C: .word 0x00000878
_0223C840: .word 0x000005DE
_0223C844: .word MOD18_0223C7B0
	thumb_func_end MOD18_0223C7D4

	thumb_func_start MOD18_0223C848
MOD18_0223C848: ; 0x0223C848
	push {r3, lr}
	ldr r0, _0223C878 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C87C ; =0x00000878
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223C876
	bl FUN_0200CAB4
	ldr r0, _0223C878 ; =0x02251380
	ldr r1, [r0]
	ldr r0, _0223C880 ; =0x00000884
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, _0223C878 ; =0x02251380
	ldr r0, _0223C87C ; =0x00000878
	ldr r2, [r1]
	mov r3, #0
	str r3, [r2, r0]
	ldr r1, [r1]
	add r0, #0xc
	str r3, [r1, r0]
_0223C876:
	pop {r3, pc}
	.align 2, 0
_0223C878: .word MOD18_02251380
_0223C87C: .word 0x00000878
_0223C880: .word 0x00000884
	thumb_func_end MOD18_0223C848

	thumb_func_start MOD18_0223C884
MOD18_0223C884: ; 0x0223C884
	ldr r1, _0223C894 ; =0x02251380
	mov r2, #1
	ldr r1, [r1]
	add r1, r1, r0
	mov r0, #0x87
	lsl r0, r0, #4
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223C894: .word MOD18_02251380
	thumb_func_end MOD18_0223C884

	thumb_func_start MOD18_0223C898
MOD18_0223C898: ; 0x0223C898
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r5, #0
_0223C89E:
	ldr r0, _0223C908 ; =0x02251380
	ldr r1, [r0]
	mov r0, #0x87
	add r7, r1, r5
	lsl r0, r0, #4
	ldrb r0, [r7, r0]
	sub r4, r0, #1
	cmp r0, #0
	beq _0223C8FE
	mov r0, #0x82
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #6
	mul r0, r4
	add r6, r1, r0
	ldr r0, _0223C90C ; =0x0000FFFF
	add r1, r0, #0
_0223C8C0:
	ldrh r3, [r6]
	cmp r3, r1
	beq _0223C8EE
	ldrh r2, [r6, #2]
	cmp r2, r0
	beq _0223C8EE
	add r0, sp, #0
	strh r3, [r0]
	ldrh r1, [r6, #2]
	strh r1, [r0, #2]
	strb r5, [r0, #4]
	mov r0, #0x48
	add r1, sp, #0
	bl FUN_02030C4C
	ldr r0, _0223C908 ; =0x02251380
	add r2, r4, #3
	ldr r0, [r0]
	add r1, r0, r5
	mov r0, #0x87
	lsl r0, r0, #4
	strb r2, [r1, r0]
	b _0223C8FE
_0223C8EE:
	add r4, r4, #3
	add r6, #0x12
	cmp r4, #0xfa
	blt _0223C8C0
	mov r1, #0x87
	lsl r1, r1, #4
	mov r0, #0
	strb r0, [r7, r1]
_0223C8FE:
	add r5, r5, #1
	cmp r5, #8
	blt _0223C89E
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223C908: .word MOD18_02251380
_0223C90C: .word 0x0000FFFF
	thumb_func_end MOD18_0223C898

	thumb_func_start MOD18_0223C910
MOD18_0223C910: ; 0x0223C910
	push {r3, r4, r5, lr}
	ldr r0, _0223C9A4 ; =0x02251380
	add r5, r2, #0
	ldr r2, [r0]
	cmp r2, #0
	beq _0223C9A0
	ldrb r1, [r5, #4]
	mov r0, #0xf
	add r4, r1, #0
	and r4, r0
	ldr r0, _0223C9A8 ; =0x00000884
	ldr r0, [r2, r0]
	cmp r0, #0
	bne _0223C960
	bl FUN_02031190
	cmp r4, r0
	bne _0223C9A0
	ldrb r0, [r5, #4]
	asr r1, r0, #4
	mov r0, #0xf
	add r3, r1, #0
	and r3, r0
	cmp r3, #0
	ble _0223C9A0
	cmp r3, #8
	bgt _0223C9A0
	ldr r1, _0223C9A4 ; =0x02251380
	add r0, r5, #0
	ldr r2, [r1]
	ldr r1, _0223C9AC ; =0x00000888
	add r4, r2, r1
	sub r1, r3, #1
	mov r2, #6
	add r3, r1, #0
	mul r3, r2
	add r1, r4, r3
	bl MI_CpuCopy8
	pop {r3, r4, r5, pc}
_0223C960:
	bl FUN_02031190
	cmp r4, r0
	bne _0223C9A0
	ldr r0, _0223C9A4 ; =0x02251380
	mov r2, #6
	ldr r1, [r0]
	ldr r0, _0223C9A8 ; =0x00000884
	ldr r4, [r1, r0]
	ldr r1, _0223C9B0 ; =0x000005DC
	add r0, r5, #0
	ldrb r1, [r4, r1]
	add r3, r1, #0
	mul r3, r2
	add r1, r4, r3
	bl MI_CpuCopy8
	ldr r2, _0223C9A4 ; =0x02251380
	ldr r0, _0223C9A8 ; =0x00000884
	ldr r1, [r2]
	ldr r4, [r1, r0]
	ldr r1, _0223C9B0 ; =0x000005DC
	ldrb r3, [r4, r1]
	add r3, r3, #1
	strb r3, [r4, r1]
	ldr r2, [r2]
	ldr r2, [r2, r0]
	ldrb r0, [r2, r1]
	cmp r0, #0xfa
	blo _0223C9A0
	mov r0, #0
	strb r0, [r2, r1]
_0223C9A0:
	pop {r3, r4, r5, pc}
	nop
_0223C9A4: .word MOD18_02251380
_0223C9A8: .word 0x00000884
_0223C9AC: .word 0x00000888
_0223C9B0: .word 0x000005DC
	thumb_func_end MOD18_0223C910

	thumb_func_start MOD18_0223C9B4
MOD18_0223C9B4: ; 0x0223C9B4
	mov r0, #6
	bx lr
	thumb_func_end MOD18_0223C9B4

	thumb_func_start MOD18_0223C9B8
MOD18_0223C9B8: ; 0x0223C9B8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r4, _0223CA6C ; =0x02251380
	mov r5, #0
	add r7, sp, #0
_0223C9C2:
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	beq _0223CA62
	add r0, r5, #0
	bl FUN_0204F6B4
	cmp r0, #0
	ldr r0, [r4]
	beq _0223C9E4
	add r2, r0, r5
	ldr r0, _0223CA70 ; =0x000008B8
	mov r1, #0
	strb r1, [r2, r0]
	b _0223CA62
_0223C9E4:
	ldr r1, _0223CA70 ; =0x000008B8
	add r0, r0, r5
	ldrb r1, [r0, r1]
	cmp r1, #0x1c
	bhs _0223CA62
	ldr r1, _0223CA70 ; =0x000008B8
	ldrb r1, [r0, r1]
	add r2, r1, #1
	ldr r1, _0223CA70 ; =0x000008B8
	strb r2, [r0, r1]
	ldr r0, [r4]
	add r1, r0, r5
	ldr r0, _0223CA70 ; =0x000008B8
	ldrb r0, [r1, r0]
	cmp r0, #0x14
	blo _0223CA62
	add r0, r5, #0
	bl FUN_0204E544
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0204E598
	add r1, r0, #0
	lsl r0, r6, #0x10
	lsl r1, r1, #0x10
	lsr r0, r0, #0x10
	lsr r1, r1, #0x10
	bl MOD18_02239E2C
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0223CA62
	mov r2, #0x82
	ldr r1, [r4]
	lsl r2, r2, #2
	add r3, r1, r2
	mov r2, #6
	mul r2, r0
	add r0, r3, r2
	ldrh r3, [r3, r2]
	ldr r2, _0223CA74 ; =0x0000FFFF
	cmp r3, r2
	beq _0223CA62
	ldrh r3, [r0, #2]
	cmp r3, r2
	beq _0223CA62
	add r2, r1, r5
	ldr r1, _0223CA70 ; =0x000008B8
	ldrb r1, [r2, r1]
	sub r1, #0x13
	lsl r1, r1, #4
	add r1, r5, r1
	strb r1, [r7, #4]
	ldrh r1, [r0]
	strh r1, [r7]
	ldrh r0, [r0, #2]
	add r1, sp, #0
	strh r0, [r7, #2]
	mov r0, #0x48
	bl FUN_02030C4C
_0223CA62:
	add r5, r5, #1
	cmp r5, #8
	blt _0223C9C2
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223CA6C: .word MOD18_02251380
_0223CA70: .word 0x000008B8
_0223CA74: .word 0x0000FFFF
	thumb_func_end MOD18_0223C9B8

	thumb_func_start MOD18_0223CA78
MOD18_0223CA78: ; 0x0223CA78
	push {r3, r4, r5, r6, r7, lr}
	ldr r6, _0223CAC4 ; =0x02251380
	add r5, r0, #0
	ldr r0, [r6]
	cmp r0, #0
	bne _0223CA88
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223CA88:
	mov r4, #0
	add r7, r4, #0
_0223CA8C:
	ldr r0, [r6]
	add r1, r0, r4
	ldr r0, _0223CAC8 ; =0x000008C4
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223CAB8
	add r0, r4, #0
	bl FUN_0202DFA4
	ldr r1, [r6]
	add r3, r5, #0
	add r2, r1, r4
	ldr r1, _0223CAC8 ; =0x000008C4
	strb r7, [r2, r1]
	add r1, r7, #0
	mov r2, #0x69
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223CAB8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223CAB8:
	add r4, r4, #1
	cmp r4, #8
	blt _0223CA8C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223CAC4: .word MOD18_02251380
_0223CAC8: .word 0x000008C4
	thumb_func_end MOD18_0223CA78

	thumb_func_start MOD18_0223CACC
MOD18_0223CACC: ; 0x0223CACC
	push {r3, lr}
	ldr r0, _0223CAE4 ; =0x02251380
	ldr r1, [r0]
	cmp r1, #0
	beq _0223CAE2
	ldr r0, _0223CAE8 ; =0x000008C4
	mov r2, #8
	add r0, r1, r0
	mov r1, #0
	bl MI_CpuFill8
_0223CAE2:
	pop {r3, pc}
	.align 2, 0
_0223CAE4: .word MOD18_02251380
_0223CAE8: .word 0x000008C4
	thumb_func_end MOD18_0223CACC

	thumb_func_start MOD18_0223CAEC
MOD18_0223CAEC: ; 0x0223CAEC
	ldr r1, _0223CB00 ; =0x02251380
	ldr r1, [r1]
	cmp r1, #0
	beq _0223CAFC
	add r1, r1, r0
	ldr r0, _0223CB04 ; =0x00000808
	ldrb r0, [r1, r0]
	bx lr
_0223CAFC:
	mov r0, #0
	bx lr
	.align 2, 0
_0223CB00: .word MOD18_02251380
_0223CB04: .word 0x00000808
	thumb_func_end MOD18_0223CAEC

	thumb_func_start MOD18_0223CB08
MOD18_0223CB08: ; 0x0223CB08
	ldr r1, _0223CB1C ; =0x02251380
	ldr r1, [r1]
	cmp r1, #0
	beq _0223CB18
	add r1, r1, r0
	ldr r0, _0223CB20 ; =0x00000808
	mov r2, #0
	strb r2, [r1, r0]
_0223CB18:
	bx lr
	nop
_0223CB1C: .word MOD18_02251380
_0223CB20: .word 0x00000808
	thumb_func_end MOD18_0223CB08

	thumb_func_start MOD18_0223CB24
MOD18_0223CB24: ; 0x0223CB24
	ldr r0, _0223CB40 ; =0x02251380
	ldr r1, [r0]
	cmp r1, #0
	beq _0223CB3A
	mov r0, #0x22
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223CB3A
	mov r0, #1
	bx lr
_0223CB3A:
	mov r0, #0
	bx lr
	nop
_0223CB40: .word MOD18_02251380
	thumb_func_end MOD18_0223CB24

	thumb_func_start MOD18_0223CB44
MOD18_0223CB44: ; 0x0223CB44
	ldr r2, _0223CB54 ; =0x02251380
	ldr r2, [r2]
	cmp r2, #0
	beq _0223CB52
	add r2, r2, r0
	ldr r0, _0223CB58 ; =0x00000808
	strb r1, [r2, r0]
_0223CB52:
	bx lr
	.align 2, 0
_0223CB54: .word MOD18_02251380
_0223CB58: .word 0x00000808
	thumb_func_end MOD18_0223CB44

	thumb_func_start MOD18_0223CB5C
MOD18_0223CB5C: ; 0x0223CB5C
	ldr r3, _0223CB60 ; =FUN_0204F7FC
	bx r3
	.align 2, 0
_0223CB60: .word FUN_0204F7FC
	thumb_func_end MOD18_0223CB5C

	thumb_func_start MOD18_0223CB64
MOD18_0223CB64: ; 0x0223CB64
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0
	ble _0223CB88
	bl MOD18_0223D638
	mov r1, #0
	add r2, r4, #0
	bl MOD18_0224DEA4
	bl MOD18_0223D638
	ldr r3, _0223CB90 ; =MOD18_0223CB5C
	mov r1, #0x4b
	mov r2, #1
	bl MOD18_0224DCB8
	pop {r4, pc}
_0223CB88:
	bl MOD18_0223CB5C
	pop {r4, pc}
	nop
_0223CB90: .word MOD18_0223CB5C
	thumb_func_end MOD18_0223CB64

	thumb_func_start MOD18_0223CB94
MOD18_0223CB94: ; 0x0223CB94
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	ldr r1, _0223CC20 ; =0x02251384
	ldr r2, [r1]
	cmp r2, #0
	bne _0223CC1E
	ldr r2, _0223CC24 ; =0x000004DC
	str r0, [r1]
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _0223CC20 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223CC28 ; =0x000004C8
	str r4, [r1, r0]
	add r0, r4, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	mov r4, #0
	ldr r7, _0223CC20 ; =0x02251384
	add r6, r0, #0
	add r5, r4, #0
_0223CBC4:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_020264F0
	ldr r1, [r7]
	add r1, r1, r5
	strb r0, [r1, #6]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_020264FC
	ldr r1, [r7]
	strh r0, [r1, r5]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0202651C
	ldr r1, [r7]
	add r1, r1, r5
	strh r0, [r1, #2]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0202653C
	ldr r1, [r7]
	add r1, r1, r5
	strb r0, [r1, #4]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02026548
	ldr r1, [r7]
	add r1, r1, r5
	strb r0, [r1, #5]
	ldr r0, [r7]
	add r0, r0, r5
	ldrb r1, [r0, #6]
	cmp r1, #0
	beq _0223CC16
	bl MOD18_0223CD74
_0223CC16:
	add r4, r4, #1
	add r5, #8
	cmp r4, #0x64
	blt _0223CBC4
_0223CC1E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223CC20: .word MOD18_02251384
_0223CC24: .word 0x000004DC
_0223CC28: .word 0x000004C8
	thumb_func_end MOD18_0223CB94

	thumb_func_start MOD18_0223CC2C
MOD18_0223CC2C: ; 0x0223CC2C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r0, _0223CC70 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223CC74 ; =0x000004C8
	ldr r0, [r1, r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	mov r4, #0
	ldr r7, _0223CC70 ; =0x02251384
	add r6, r0, #0
	add r5, r4, #0
_0223CC48:
	ldr r3, [r7]
	add r2, r4, #0
	add r1, r3, r5
	ldrh r0, [r1, #2]
	str r0, [sp]
	ldrb r0, [r1, #4]
	str r0, [sp, #4]
	ldrb r0, [r1, #5]
	str r0, [sp, #8]
	ldrb r1, [r1, #6]
	ldrh r3, [r3, r5]
	add r0, r6, #0
	bl FUN_0202649C
	add r4, r4, #1
	add r5, #8
	cmp r4, #0x64
	blt _0223CC48
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223CC70: .word MOD18_02251384
_0223CC74: .word 0x000004C8
	thumb_func_end MOD18_0223CC2C

	thumb_func_start MOD18_0223CC78
MOD18_0223CC78: ; 0x0223CC78
	ldr r0, _0223CC7C ; =0x000004DC
	bx lr
	.align 2, 0
_0223CC7C: .word 0x000004DC
	thumb_func_end MOD18_0223CC78

	thumb_func_start MOD18_0223CC80
MOD18_0223CC80: ; 0x0223CC80
	ldr r0, _0223CC8C ; =0x02251384
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _0223CC90 ; =0x000004DA
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223CC8C: .word MOD18_02251384
_0223CC90: .word 0x000004DA
	thumb_func_end MOD18_0223CC80

	thumb_func_start MOD18_0223CC94
MOD18_0223CC94: ; 0x0223CC94
	ldr r0, _0223CCA0 ; =0x02251384
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _0223CCA4 ; =0x000004DA
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223CCA0: .word MOD18_02251384
_0223CCA4: .word 0x000004DA
	thumb_func_end MOD18_0223CC94

	thumb_func_start MOD18_0223CCA8
MOD18_0223CCA8: ; 0x0223CCA8
	push {r3, lr}
	ldr r0, _0223CCC0 ; =0x02251384
	ldr r0, [r0]
	cmp r0, #0
	beq _0223CCBC
	bl FreeToHeap
	ldr r0, _0223CCC0 ; =0x02251384
	mov r1, #0
	str r1, [r0]
_0223CCBC:
	pop {r3, pc}
	nop
_0223CCC0: .word MOD18_02251384
	thumb_func_end MOD18_0223CCA8

	thumb_func_start MOD18_0223CCC4
MOD18_0223CCC4: ; 0x0223CCC4
	push {r3, r4, r5, lr}
	ldr r3, _0223CD34 ; =0x02251384
	ldr r2, _0223CD38 ; =0x000004DA
	ldr r0, [r3]
	ldrb r1, [r0, r2]
	cmp r1, #0
	bne _0223CD32
	sub r1, r2, #6
	ldr r1, [r0, r1]
	add r4, r1, #1
	sub r1, r2, #6
	str r4, [r0, r1]
	ldr r3, [r3]
	add r0, r1, #0
	ldr r1, [r3, r0]
	mov r0, #0x7d
	lsl r0, r0, #4
	cmp r1, r0
	blt _0223CCF0
	mov r1, #0
	sub r0, r2, #6
	str r1, [r3, r0]
_0223CCF0:
	ldr r0, _0223CD34 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223CD3C ; =0x000004D4
	ldr r4, [r1, r0]
	mov r1, #0x14
	add r0, r4, #0
	bl _s32_div_f
	cmp r1, #0xa
	bne _0223CD32
	add r0, r4, #0
	mov r1, #0x14
	bl _s32_div_f
	add r5, r0, #0
	bl MOD18_0223D1B8
	add r4, r0, #0
	add r0, r5, #0
	bl MOD18_0223D1D8
	add r2, r0, #0
	cmp r4, #0
	beq _0223CD32
	cmp r2, #0
	beq _0223CD32
	ldr r0, _0223CD34 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223CD40 ; =0x000004C8
	ldr r0, [r1, r0]
	add r1, r4, #0
	bl MOD05_021E5D0C
_0223CD32:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223CD34: .word MOD18_02251384
_0223CD38: .word 0x000004DA
_0223CD3C: .word 0x000004D4
_0223CD40: .word 0x000004C8
	thumb_func_end MOD18_0223CCC4

	thumb_func_start MOD18_0223CD44
MOD18_0223CD44: ; 0x0223CD44
	push {r3, r4}
	ldr r3, _0223CD70 ; =0x02251384
	lsl r1, r1, #2
	ldr r2, [r3]
	add r4, r2, r1
	mov r2, #0x32
	lsl r2, r2, #4
	ldr r4, [r4, r2]
	cmp r4, #0
	bne _0223CD5E
	mov r0, #0
	pop {r3, r4}
	bx lr
_0223CD5E:
	ldrh r4, [r4]
	strh r4, [r0]
	ldr r3, [r3]
	add r1, r3, r1
	ldr r1, [r1, r2]
	ldrh r1, [r1, #2]
	strh r1, [r0, #2]
	pop {r3, r4}
	bx lr
	.align 2, 0
_0223CD70: .word MOD18_02251384
	thumb_func_end MOD18_0223CD44

	thumb_func_start MOD18_0223CD74
MOD18_0223CD74: ; 0x0223CD74
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r0, [sp]
	ldrh r0, [r0]
	add r1, sp, #4
	strh r0, [r1]
	ldr r0, [sp]
	ldrh r0, [r0, #2]
	strh r0, [r1, #2]
	ldr r1, _0223CDD4 ; =MOD18_0223CD44
	mov r0, #0x64
	bl MOD18_0223DC7C
	add r0, sp, #4
	bl MOD18_0223DC28
	add r4, r0, #0
	cmp r4, #0x64
	blt _0223CD9E
	bl ErrorHandling
_0223CD9E:
	mov r5, #0x63
	cmp r4, #0x63
	bge _0223CDBE
	mov r7, #0xc7
	lsl r7, r7, #2
	ldr r1, _0223CDD8 ; =0x02251384
	lsl r6, r5, #2
	add r0, r7, #4
_0223CDAE:
	ldr r2, [r1]
	sub r5, r5, #1
	add r3, r2, r6
	ldr r2, [r3, r7]
	sub r6, r6, #4
	str r2, [r3, r0]
	cmp r5, r4
	bgt _0223CDAE
_0223CDBE:
	ldr r0, _0223CDD8 ; =0x02251384
	ldr r1, [r0]
	lsl r0, r4, #2
	add r2, r1, r0
	mov r1, #0x32
	ldr r0, [sp]
	lsl r1, r1, #4
	str r0, [r2, r1]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223CDD4: .word MOD18_0223CD44
_0223CDD8: .word MOD18_02251384
	thumb_func_end MOD18_0223CD74

	thumb_func_start MOD18_0223CDDC
MOD18_0223CDDC: ; 0x0223CDDC
	push {r4, r5, r6, lr}
	ldr r0, _0223CE10 ; =0x02251384
	mov r2, #0x32
	ldr r0, [r0]
	lsl r2, r2, #4
	add r0, r0, r2
	mov r1, #0
	lsr r2, r2, #1
	bl MI_CpuFill8
	mov r4, #0
	ldr r6, _0223CE10 ; =0x02251384
	add r5, r4, #0
_0223CDF6:
	ldr r0, [r6]
	add r0, r0, r5
	ldrb r1, [r0, #6]
	cmp r1, #0
	beq _0223CE04
	bl MOD18_0223CD74
_0223CE04:
	add r4, r4, #1
	add r5, #8
	cmp r4, #0x64
	blt _0223CDF6
	pop {r4, r5, r6, pc}
	nop
_0223CE10: .word MOD18_02251384
	thumb_func_end MOD18_0223CDDC

	thumb_func_start MOD18_0223CE14
MOD18_0223CE14: ; 0x0223CE14
	mov r2, #0
_0223CE16:
	ldrb r1, [r0, #6]
	cmp r1, #0
	beq _0223CE26
	add r2, r2, #1
	add r0, #8
	cmp r2, #0x64
	blt _0223CE16
	mov r0, #0
_0223CE26:
	bx lr
	thumb_func_end MOD18_0223CE14

	thumb_func_start MOD18_0223CE28
MOD18_0223CE28: ; 0x0223CE28
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0223CE28

	thumb_func_start MOD18_0223CE2C
MOD18_0223CE2C: ; 0x0223CE2C
	push {r3, lr}
	add r2, sp, #0
	strh r0, [r2]
	strh r1, [r2, #2]
	ldr r1, _0223CE60 ; =MOD18_0223CD44
	mov r0, #0x64
	bl MOD18_0223DC7C
	add r0, sp, #0
	bl MOD18_0223DBBC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0223CE4E
	mov r0, #0
	pop {r3, pc}
_0223CE4E:
	ldr r1, _0223CE64 ; =0x02251384
	lsl r0, r0, #2
	ldr r1, [r1]
	add r1, r1, r0
	mov r0, #0x32
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	pop {r3, pc}
	nop
_0223CE60: .word MOD18_0223CD44
_0223CE64: .word MOD18_02251384
	thumb_func_end MOD18_0223CE2C

	thumb_func_start MOD18_0223CE68
MOD18_0223CE68: ; 0x0223CE68
	push {r3, r4, r5, lr}
	add r4, r2, #0
	bl FUN_02031190
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, r5
	bne _0223CF1C
	bl FUN_0204E4D4
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0204E50C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0223CE2C
	add r4, r0, #0
	beq _0223CF1C
	bl FUN_0204F7E4
	ldrb r2, [r4, #4]
	ldrb r1, [r4, #5]
	ldrb r0, [r4, #6]
	add r1, r2, r1
	bl MOD18_02249450
	cmp r0, #0
	beq _0223CF0E
	ldr r0, _0223CF20 ; =0x02251384
	ldrb r2, [r4, #6]
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _0223CF24 ; =0x000004CC
	strb r2, [r1, r0]
	ldr r0, _0223CF28 ; =0x000005E3
	bl FUN_020054C8
	ldrb r1, [r4, #4]
	ldrb r0, [r4, #5]
	mov r5, #0x63
	add r0, r1, r0
	cmp r0, #0x63
	bge _0223CEC4
	add r5, r0, #0
_0223CEC4:
	bl MOD18_0223D638
	mov r1, #1
	add r2, r5, #0
	bl MOD18_0224DEA4
	bl MOD18_0223D638
	ldrb r2, [r4, #6]
	mov r1, #2
	bl MOD18_0224DF2C
	ldrb r5, [r4, #5]
	ldrb r1, [r4, #4]
	add r0, r5, r1
	cmp r0, #0x63
	ble _0223CEEA
	mov r0, #0x63
	sub r5, r0, r1
_0223CEEA:
	bl MOD18_0223D638
	ldr r3, _0223CF2C ; =MOD18_0223CB64
	mov r1, #0x45
	mov r2, #1
	str r5, [sp]
	bl MOD18_0224DCF0
	bl MOD18_0223D638
	bl MOD18_0224DD10
	add r0, r4, #0
	bl MOD18_0223D0E8
	bl MOD18_0223CC2C
	pop {r3, r4, r5, pc}
_0223CF0E:
	bl MOD18_0223D638
	ldr r3, _0223CF30 ; =MOD18_0223CB5C
	mov r1, #0x53
	mov r2, #1
	bl MOD18_0224DCB8
_0223CF1C:
	pop {r3, r4, r5, pc}
	nop
_0223CF20: .word MOD18_02251384
_0223CF24: .word 0x000004CC
_0223CF28: .word 0x000005E3
_0223CF2C: .word MOD18_0223CB64
_0223CF30: .word MOD18_0223CB5C
	thumb_func_end MOD18_0223CE68

	thumb_func_start MOD18_0223CF34
MOD18_0223CF34: ; 0x0223CF34
	strh r1, [r0, #2]
	mov r1, #0
	strh r1, [r0]
	bx lr
	thumb_func_end MOD18_0223CF34

	thumb_func_start MOD18_0223CF3C
MOD18_0223CF3C: ; 0x0223CF3C
	push {r3, r4, r5, r6}
	ldrh r6, [r0, #2]
	mov r2, #0
	ldrh r3, [r0]
	cmp r6, #0
	blt _0223CF96
	add r5, r2, #0
_0223CF4A:
	sub r4, r3, r5
	cmp r4, #0
	ble _0223CF54
	add r3, r4, #0
	b _0223CF8E
_0223CF54:
	cmp r3, #0
	beq _0223CF5A
	sub r3, r3, #1
_0223CF5A:
	lsl r4, r2, #1
	cmp r3, r4
	bge _0223CF64
	sub r5, r2, r3
	b _0223CF68
_0223CF64:
	add r5, r2, r4
	sub r5, r3, r5
_0223CF68:
	cmp r3, r2
	blt _0223CF7E
	lsl r6, r2, #1
	add r6, r2, r6
	cmp r3, r6
	bge _0223CF78
	sub r3, r4, r3
	b _0223CF7E
_0223CF78:
	lsl r2, r2, #2
	neg r2, r2
	add r3, r2, r3
_0223CF7E:
	strh r3, [r1]
	strh r5, [r1, #2]
	ldrh r1, [r0]
	add r1, r1, #1
	strh r1, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6}
	bx lr
_0223CF8E:
	add r2, r2, #1
	add r5, r5, #4
	cmp r2, r6
	ble _0223CF4A
_0223CF96:
	mov r0, #0
	pop {r3, r4, r5, r6}
	bx lr
	thumb_func_end MOD18_0223CF3C

	thumb_func_start MOD18_0223CF9C
MOD18_0223CF9C: ; 0x0223CF9C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #8]
	add r6, r2, #0
	add r1, sp, #0xc
	add r7, r3, #0
	strh r6, [r1]
	strh r7, [r1, #2]
	ldr r0, [sp]
	strb r5, [r1, #4]
	strb r0, [r1, #6]
	ldr r0, [sp, #8]
	strb r0, [r1, #5]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _0223CFDA
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x54
	add r3, r2, #0
	bl MOD18_0224DCB8
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_0223CFDA:
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_0204D76C
	cmp r0, #0
	beq _0223CFF8
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x37
	add r3, r2, #0
	bl MOD18_0224DCB8
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_0223CFF8:
	ldr r0, _0223D0DC ; =0x02251384
	add r2, r7, #0
	ldr r1, [r0]
	ldr r0, _0223D0E0 ; =0x000004C8
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl FUN_0204A6B4
	cmp r0, #0
	beq _0223D01E
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x3c
	add r3, r2, #0
	bl MOD18_0224DCB8
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_0223D01E:
	add r0, r6, #0
	add r1, r7, #0
	bl MOD18_0223CE2C
	add r4, r0, #0
	add r0, sp, #0xc
	beq _0223D076
	ldrb r1, [r4, #6]
	ldrb r0, [r0, #6]
	cmp r1, r0
	bne _0223D066
	ldrb r0, [r4, #4]
	str r0, [sp, #4]
	cmp r0, r5
	ble _0223D04A
	add r0, r5, #0
	mov r1, #5
	bl _s32_div_f
	ldr r1, [sp, #4]
	add r0, r1, r0
	b _0223D052
_0223D04A:
	mov r1, #5
	bl _s32_div_f
	add r0, r5, r0
_0223D052:
	add r0, r0, #1
	strb r0, [r4, #4]
	ldrb r0, [r4, #4]
	cmp r0, #0x63
	bls _0223D060
	mov r0, #0x63
	strb r0, [r4, #4]
_0223D060:
	mov r0, #1
	str r0, [sp, #8]
	b _0223D07E
_0223D066:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x3b
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0223D07E
_0223D076:
	bl MOD18_0223D14C
	mov r0, #1
	str r0, [sp, #8]
_0223D07E:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _0223D0D8
	bl MOD18_0223D638
	ldr r2, [sp]
	mov r1, #0
	bl MOD18_0224DEF0
	bl MOD18_0223D638
	mov r1, #1
	add r2, r5, #0
	bl MOD18_0224DEA4
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x3a
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, [sp]
	bl MOD18_02249E98
	ldr r0, _0223D0E4 ; =0x00000631
	bl FUN_020054C8
	ldr r0, _0223D0DC ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223D0E0 ; =0x000004C8
	ldr r0, [r1, r0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205EDCC
	ldr r0, _0223D0DC ; =0x02251384
	add r2, r7, #0
	ldr r1, [r0]
	ldr r0, _0223D0E0 ; =0x000004C8
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl MOD05_021E5D0C
_0223D0D8:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223D0DC: .word MOD18_02251384
_0223D0E0: .word 0x000004C8
_0223D0E4: .word 0x00000631
	thumb_func_end MOD18_0223CF9C

	thumb_func_start MOD18_0223D0E8
MOD18_0223D0E8: ; 0x0223D0E8
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _0223D144 ; =0x02251384
	mov r1, #0
	ldr r0, [r0]
	mvn r1, r1
	mov r4, #0
_0223D0F6:
	cmp r0, r6
	bne _0223D0FE
	add r1, r4, #0
	b _0223D106
_0223D0FE:
	add r4, r4, #1
	add r0, #8
	cmp r4, #0x64
	blt _0223D0F6
_0223D106:
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _0223D112
	bl ErrorHandling
_0223D112:
	cmp r4, #0x63
	bge _0223D132
	ldr r7, _0223D144 ; =0x02251384
	lsl r5, r4, #3
_0223D11A:
	add r0, r4, #1
	ldr r1, [r7]
	lsl r0, r0, #3
	add r0, r1, r0
	add r1, r1, r5
	mov r2, #8
	bl MI_CpuCopy8
	add r4, r4, #1
	add r5, #8
	cmp r4, #0x63
	blt _0223D11A
_0223D132:
	ldr r0, _0223D144 ; =0x02251384
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _0223D148 ; =0x0000031E
	strb r2, [r1, r0]
	add r0, r6, #0
	bl MOD18_0223CDDC
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223D144: .word MOD18_02251384
_0223D148: .word 0x0000031E
	thumb_func_end MOD18_0223D0E8

	thumb_func_start MOD18_0223D14C
MOD18_0223D14C: ; 0x0223D14C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, _0223D190 ; =0x02251384
	ldr r0, [r0]
	bl MOD18_0223CE14
	add r5, r0, #0
	bne _0223D178
	ldr r0, _0223D190 ; =0x02251384
	ldr r0, [r0]
	bl MOD18_0223CE28
	bl MOD18_0223D0E8
	ldr r0, _0223D190 ; =0x02251384
	ldr r0, [r0]
	bl MOD18_0223CE14
	add r5, r0, #0
	bne _0223D178
	bl ErrorHandling
_0223D178:
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #8
	bl MI_CpuCopy8
	add r0, r5, #0
	bl MOD18_0223CD74
	bl MOD18_0223CC2C
	pop {r3, r4, r5, pc}
	nop
_0223D190: .word MOD18_02251384
	thumb_func_end MOD18_0223D14C

	thumb_func_start MOD18_0223D194
MOD18_0223D194: ; 0x0223D194
	cmp r0, #0
	beq _0223D1A0
	cmp r0, #0xb
	bge _0223D1A0
	mov r0, #1
	bx lr
_0223D1A0:
	mov r0, #0
	bx lr
	thumb_func_end MOD18_0223D194

	thumb_func_start MOD18_0223D1A4
MOD18_0223D1A4: ; 0x0223D1A4
	push {r3, lr}
	bl MOD18_0223CE2C
	cmp r0, #0
	beq _0223D1B2
	mov r0, #1
	pop {r3, pc}
_0223D1B2:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0223D1A4

	thumb_func_start MOD18_0223D1B8
MOD18_0223D1B8: ; 0x0223D1B8
	ldr r1, _0223D1D4 ; =0x02251384
	ldr r2, [r1]
	cmp r2, #0
	beq _0223D1CE
	lsl r1, r0, #3
	add r0, r2, r1
	ldrb r0, [r0, #6]
	cmp r0, #0
	beq _0223D1CE
	ldrh r0, [r2, r1]
	bx lr
_0223D1CE:
	mov r0, #0
	bx lr
	nop
_0223D1D4: .word MOD18_02251384
	thumb_func_end MOD18_0223D1B8

	thumb_func_start MOD18_0223D1D8
MOD18_0223D1D8: ; 0x0223D1D8
	ldr r1, _0223D1F4 ; =0x02251384
	ldr r1, [r1]
	cmp r1, #0
	beq _0223D1EE
	lsl r0, r0, #3
	add r1, r1, r0
	ldrb r0, [r1, #6]
	cmp r0, #0
	beq _0223D1EE
	ldrh r0, [r1, #2]
	bx lr
_0223D1EE:
	mov r0, #0
	bx lr
	nop
_0223D1F4: .word MOD18_02251384
	thumb_func_end MOD18_0223D1D8

	thumb_func_start MOD18_0223D1F8
MOD18_0223D1F8: ; 0x0223D1F8
	push {r3, r4, r5, r6, r7, lr}
	str r0, [sp]
	ldr r0, _0223D290 ; =0x02251384
	mov r5, #0
	ldr r2, [r0]
	add r6, r5, #0
	add r7, r5, #0
	cmp r2, #0
	bne _0223D20E
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223D20E:
	ldr r0, _0223D294 ; =0x000004CC
	add r4, r5, #0
_0223D212:
	ldrb r1, [r2, r0]
	cmp r1, #0
	beq _0223D26E
	mov r0, #4
	bl ScrStrBufs_new
	add r5, r0, #0
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	ldr r2, _0223D290 ; =0x02251384
	add r6, r0, #0
	ldr r2, [r2]
	add r0, r5, #0
	add r3, r2, r4
	ldr r2, _0223D294 ; =0x000004CC
	mov r1, #2
	ldrb r2, [r3, r2]
	bl BufferUndergroundItemNameWithArticle
	add r0, r5, #0
	mov r1, #2
	bl ScrStrBufs_UpperFirstChar
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	mov r1, #0x5f
	add r2, r6, #0
	bl ReadMsgDataIntoString
	ldr r1, [sp]
	add r0, r5, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	ldr r1, _0223D290 ; =0x02251384
	mov r0, #0
	ldr r1, [r1]
	mov r7, #1
	add r2, r1, r4
	ldr r1, _0223D294 ; =0x000004CC
	strb r0, [r2, r1]
	b _0223D276
_0223D26E:
	add r4, r4, #1
	add r2, r2, #1
	cmp r4, #8
	blt _0223D212
_0223D276:
	cmp r6, #0
	beq _0223D280
	add r0, r6, #0
	bl String_dtor
_0223D280:
	cmp r5, #0
	beq _0223D28A
	add r0, r5, #0
	bl ScrStrBufs_delete
_0223D28A:
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D290: .word MOD18_02251384
_0223D294: .word 0x000004CC
	thumb_func_end MOD18_0223D1F8

	thumb_func_start MOD18_0223D298
MOD18_0223D298: ; 0x0223D298
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	ldr r0, _0223D2E4 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223D2E8 ; =0x000004C8
	ldr r0, [r1, r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r4, r0, #0
	mov r5, #0
_0223D2B0:
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_020264F0
	cmp r0, #0
	beq _0223D2D8
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_020264FC
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_0202651C
	add r1, r0, #0
	add r0, r6, #0
	add r2, r7, #0
	bl MOD18_02239BB0
_0223D2D8:
	add r5, r5, #1
	cmp r5, #0x64
	blt _0223D2B0
	add r0, r5, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223D2E4: .word MOD18_02251384
_0223D2E8: .word 0x000004C8
	thumb_func_end MOD18_0223D298

	thumb_func_start MOD18_0223D2EC
MOD18_0223D2EC: ; 0x0223D2EC
	push {r4, lr}
	add r4, r1, #0
	ldrh r0, [r4, #2]
	add r0, r0, #1
	strh r0, [r4, #2]
	ldrh r0, [r4, #2]
	cmp r0, #0x64
	bls _0223D306
	ldr r0, _0223D308 ; =0x00000621
	bl FUN_020054C8
	mov r0, #0
	strh r0, [r4, #2]
_0223D306:
	pop {r4, pc}
	.align 2, 0
_0223D308: .word 0x00000621
	thumb_func_end MOD18_0223D2EC

	thumb_func_start MOD18_0223D30C
MOD18_0223D30C: ; 0x0223D30C
	push {r4, lr}
	ldr r0, _0223D364 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223D368 ; =0x000004C4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223D31E
	bl ErrorHandling
_0223D31E:
	ldr r0, _0223D364 ; =0x02251384
	ldr r1, [r0]
	mov r0, #0x13
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223D330
	bl ErrorHandling
_0223D330:
	mov r0, #0xb
	mov r1, #4
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r2, #0x64
	ldr r0, _0223D364 ; =0x02251384
	strh r2, [r4, #2]
	ldr r1, [r0]
	ldr r0, _0223D368 ; =0x000004C4
	str r4, [r1, r0]
	ldr r0, _0223D36C ; =MOD18_0223D2EC
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _0223D364 ; =0x02251384
	ldr r2, [r1]
	mov r1, #0x13
	lsl r1, r1, #6
	str r0, [r2, r1]
	pop {r4, pc}
	nop
_0223D364: .word MOD18_02251384
_0223D368: .word 0x000004C4
_0223D36C: .word MOD18_0223D2EC
	thumb_func_end MOD18_0223D30C

	thumb_func_start MOD18_0223D370
MOD18_0223D370: ; 0x0223D370
	push {r3, lr}
	ldr r0, _0223D3A4 ; =0x02251384
	ldr r1, [r0]
	mov r0, #0x13
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223D3A2
	bl FUN_0200CAB4
	ldr r0, _0223D3A4 ; =0x02251384
	ldr r1, [r0]
	ldr r0, _0223D3A8 ; =0x000004C4
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, _0223D3A4 ; =0x02251384
	mov r0, #0x13
	ldr r2, [r1]
	mov r3, #0
	lsl r0, r0, #6
	str r3, [r2, r0]
	ldr r1, [r1]
	add r0, r0, #4
	str r3, [r1, r0]
_0223D3A2:
	pop {r3, pc}
	.align 2, 0
_0223D3A4: .word MOD18_02251384
_0223D3A8: .word 0x000004C4
	thumb_func_end MOD18_0223D370

	thumb_func_start MOD18_0223D3AC
MOD18_0223D3AC: ; 0x0223D3AC
	push {r3, lr}
	ldr r1, _0223D3D8 ; =0x02251384
	ldr r2, [r1]
	cmp r2, #0
	beq _0223D3D2
	ldr r1, _0223D3DC ; =0x000004C4
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _0223D3D2
	ldrh r1, [r1, #2]
	lsr r1, r1, #1
	add r0, r1, r0
	mov r1, #0x64
	bl _s32_div_f
	add r0, r1, #0
	bl MOD18_0223D1B8
	pop {r3, pc}
_0223D3D2:
	mov r0, #0
	pop {r3, pc}
	nop
_0223D3D8: .word MOD18_02251384
_0223D3DC: .word 0x000004C4
	thumb_func_end MOD18_0223D3AC

	thumb_func_start MOD18_0223D3E0
MOD18_0223D3E0: ; 0x0223D3E0
	push {r3, lr}
	ldr r1, _0223D40C ; =0x02251384
	ldr r2, [r1]
	cmp r2, #0
	beq _0223D406
	ldr r1, _0223D410 ; =0x000004C4
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _0223D406
	ldrh r1, [r1, #2]
	lsr r1, r1, #1
	add r0, r1, r0
	mov r1, #0x64
	bl _s32_div_f
	add r0, r1, #0
	bl MOD18_0223D1D8
	pop {r3, pc}
_0223D406:
	mov r0, #0
	pop {r3, pc}
	nop
_0223D40C: .word MOD18_02251384
_0223D410: .word 0x000004C4
	thumb_func_end MOD18_0223D3E0

	thumb_func_start MOD18_0223D414
MOD18_0223D414: ; 0x0223D414
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_PlayerData_GetOptionsAddr
	bl Options_GetTextFrameDelay
	add r4, r0, #0
	ldr r0, _0223D580 ; =0x02251388
	mov r2, #0x15
	str r6, [r0]
	add r0, r6, #0
	mov r1, #0
	lsl r2, r2, #4
	bl MI_CpuFill8
	ldr r2, _0223D580 ; =0x02251388
	mov r3, #0x4d
	ldr r0, [r2]
	lsl r3, r3, #2
	str r5, [r0, #0xc]
	ldr r1, [r2]
	mov r0, #0
	strb r0, [r1, r3]
	ldr r1, [r2]
	strh r0, [r1, #0x1c]
	ldr r1, [r2]
	strh r0, [r1, #0x1e]
	add r1, r3, #0
	ldr r6, [r2]
	add r1, #0x17
	strb r0, [r6, r1]
	add r0, r3, #0
	ldr r1, [r2]
	mov r6, #1
	add r0, #0x13
	strb r6, [r1, r0]
	add r3, #0xc0
	str r3, [sp]
	ldr r0, _0223D584 ; =0x0000023F
	ldr r2, [r5, #8]
	mov r1, #0x21
	add r3, r4, #0
	bl MOD18_0224DAE0
	ldr r1, _0223D580 ; =0x02251388
	add r3, r4, #0
	ldr r2, [r1]
	mov r1, #0x46
	lsl r1, r1, #2
	str r0, [r2, r1]
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223D588 ; =0x00000243
	ldr r2, [r5, #8]
	mov r1, #0x21
	bl MOD18_0224DAE0
	ldr r1, _0223D580 ; =0x02251388
	add r3, r4, #0
	ldr r2, [r1]
	mov r1, #0x47
	lsl r1, r1, #2
	str r0, [r2, r1]
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp]
	ldr r0, _0223D58C ; =0x00000241
	ldr r2, [r5, #8]
	mov r1, #0x21
	bl MOD18_0224DAE0
	ldr r1, _0223D580 ; =0x02251388
	add r3, r4, #0
	ldr r2, [r1]
	mov r1, #0x12
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223D590 ; =0x00000242
	ldr r2, [r5, #8]
	mov r1, #0x21
	bl MOD18_0224DAE0
	ldr r1, _0223D580 ; =0x02251388
	add r3, r4, #0
	ldr r2, [r1]
	mov r1, #0x49
	lsl r1, r1, #2
	str r0, [r2, r1]
	mov r0, #0
	str r0, [sp]
	ldr r0, _0223D594 ; =0x0000023B
	ldr r2, [r5, #8]
	mov r1, #0x21
	bl MOD18_0224DAE0
	ldr r1, _0223D580 ; =0x02251388
	mov r2, #0x4a
	ldr r3, [r1]
	lsl r2, r2, #2
	str r0, [r3, r2]
	mov r0, #0
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r1]
	mov r1, #3
	ldr r0, [r0, #0xc]
	add r2, #0xba
	ldr r0, [r0, #8]
	mov r3, #0xa
	bl FUN_0200CD68
	mov r3, #0x80
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0x32
	mov r1, #0x34
	mov r2, #0
	add r3, #0xc0
	bl FUN_02006930
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, _0223D580 ; =0x02251388
	ldr r2, _0223D598 ; =0x000003D9
	ldr r0, [r0]
	mov r1, #3
	ldr r0, [r0, #0xc]
	mov r3, #0xb
	ldr r0, [r0, #8]
	bl FUN_0200CB00
	mov r3, #0
	ldr r0, _0223D580 ; =0x02251388
	add r4, r3, #0
	mov r2, #0xff
	add r1, r3, #0
_0223D536:
	ldr r5, [r0]
	add r5, r5, r3
	add r5, #0xc2
	strb r2, [r5]
	ldr r5, [r0]
	add r5, r5, r3
	add r5, #0xd2
	strb r2, [r5]
	ldr r5, [r0]
	add r3, r3, #1
	add r5, r5, r4
	add r5, #0xdc
	add r4, r4, #4
	str r1, [r5]
	cmp r3, #8
	blt _0223D536
	ldr r0, _0223D580 ; =0x02251388
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205EDAC
	mov r1, #0
	ldr r0, _0223D59C ; =MOD18_0223E7AC
	add r2, r1, #0
	bl FUN_0200CA44
	ldr r1, _0223D580 ; =0x02251388
	ldr r1, [r1]
	str r0, [r1, #0x14]
	ldr r0, _0223D5A0 ; =MOD18_0223E890
	bl FUN_0202D31C
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223D580: .word MOD18_02251388
_0223D584: .word 0x0000023F
_0223D588: .word 0x00000243
_0223D58C: .word 0x00000241
_0223D590: .word 0x00000242
_0223D594: .word 0x0000023B
_0223D598: .word 0x000003D9
_0223D59C: .word MOD18_0223E7AC
_0223D5A0: .word MOD18_0223E890
	thumb_func_end MOD18_0223D414

	thumb_func_start MOD18_0223D5A4
MOD18_0223D5A4: ; 0x0223D5A4
	push {r4, r5, r6, lr}
	mov r4, #0
	ldr r6, _0223D634 ; =0x02251388
	add r5, r4, #0
_0223D5AC:
	ldr r0, [r6]
	add r0, r0, r5
	add r0, #0xdc
	ldr r0, [r0]
	cmp r0, #0
	beq _0223D5BC
	bl String_dtor
_0223D5BC:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _0223D5AC
	mov r0, #0
	bl FUN_0202D31C
	ldr r0, _0223D634 ; =0x02251388
	ldr r0, [r0]
	ldr r0, [r0, #0x14]
	bl FUN_0200CAB4
	ldr r0, _0223D634 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DB5C
	ldr r0, _0223D634 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DB5C
	ldr r0, _0223D634 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD18_0224DB5C
	ldr r0, _0223D634 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DB5C
	ldr r0, _0223D634 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DB5C
	ldr r0, _0223D634 ; =0x02251388
	mov r2, #0
	ldr r1, [r0]
	ldr r1, [r1, #0xc]
	add r1, #0x8c
	str r2, [r1]
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, _0223D634 ; =0x02251388
	mov r1, #0
	str r1, [r0]
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223D634: .word MOD18_02251388
	thumb_func_end MOD18_0223D5A4

	thumb_func_start MOD18_0223D638
MOD18_0223D638: ; 0x0223D638
	ldr r0, _0223D644 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bx lr
	.align 2, 0
_0223D644: .word MOD18_02251388
	thumb_func_end MOD18_0223D638

	thumb_func_start MOD18_0223D648
MOD18_0223D648: ; 0x0223D648
	ldr r0, _0223D654 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bx lr
	.align 2, 0
_0223D654: .word MOD18_02251388
	thumb_func_end MOD18_0223D648

	thumb_func_start MOD18_0223D658
MOD18_0223D658: ; 0x0223D658
	ldr r0, _0223D664 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bx lr
	.align 2, 0
_0223D664: .word MOD18_02251388
	thumb_func_end MOD18_0223D658

	thumb_func_start MOD18_0223D668
MOD18_0223D668: ; 0x0223D668
	ldr r0, _0223D674 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bx lr
	.align 2, 0
_0223D674: .word MOD18_02251388
	thumb_func_end MOD18_0223D668

	thumb_func_start MOD18_0223D678
MOD18_0223D678: ; 0x0223D678
	ldr r0, _0223D684 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bx lr
	.align 2, 0
_0223D684: .word MOD18_02251388
	thumb_func_end MOD18_0223D678

	thumb_func_start MOD18_0223D688
MOD18_0223D688: ; 0x0223D688
	push {r3, lr}
	ldr r0, _0223D6D4 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DF60
	ldr r0, _0223D6D4 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DF60
	ldr r0, _0223D6D4 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD18_0224DF60
	ldr r0, _0223D6D4 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DF60
	ldr r0, _0223D6D4 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DF60
	pop {r3, pc}
	nop
_0223D6D4: .word MOD18_02251388
	thumb_func_end MOD18_0223D688

	thumb_func_start MOD18_0223D6D8
MOD18_0223D6D8: ; 0x0223D6D8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	cmp r5, #0
	beq _0223D73E
	cmp r6, #0
	beq _0223D73E
	mov r0, #4
	bl ScrStrBufs_new
	add r4, r0, #0
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #0
	add r2, r5, #0
	bl BufferPlayersName
	add r0, r4, #0
	mov r1, #1
	add r2, r6, #0
	bl BufferPlayersName
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	ldr r1, [sp]
	add r2, r7, #0
	bl ReadMsgDataIntoString
	ldr r1, [sp, #4]
	add r0, r4, #0
	add r2, r7, #0
	bl StringExpandPlaceholders
	add r0, r7, #0
	bl String_dtor
	add r0, r4, #0
	bl ScrStrBufs_delete
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223D73E:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0223D6D8

	thumb_func_start MOD18_0223D744
MOD18_0223D744: ; 0x0223D744
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	cmp r5, #0
	beq _0223D79C
	mov r0, #4
	bl ScrStrBufs_new
	add r4, r0, #0
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	add r6, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl BufferPlayersName
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	ldr r1, [sp]
	add r2, r6, #0
	bl ReadMsgDataIntoString
	ldr r1, [sp, #4]
	add r0, r4, #0
	add r2, r6, #0
	bl StringExpandPlaceholders
	add r0, r6, #0
	bl String_dtor
	add r0, r4, #0
	bl ScrStrBufs_delete
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223D79C:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0223D744

	thumb_func_start MOD18_0223D7A4
MOD18_0223D7A4: ; 0x0223D7A4
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, _0223D8A0 ; =0x02251388
	add r6, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _0223D7B4
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223D7B4:
	mov r5, #0
_0223D7B6:
	add r0, r5, #0
	bl FUN_0202DEC0
	cmp r0, #0
	beq _0223D7E2
	add r0, r5, #0
	bl FUN_0202DFA4
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0202DEF4
	add r0, r7, #0
	mov r1, #1
	mov r2, #0x5b
	add r3, r6, #0
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223D7E2
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223D7E2:
	ldr r0, [r4]
	add r0, r0, r5
	add r0, #0xc2
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _0223D820
	add r0, r5, #0
	bl FUN_0202DFA4
	add r7, r0, #0
	ldr r0, [r4]
	add r0, r0, r5
	add r0, #0xc2
	ldrb r0, [r0]
	bl FUN_0202DFA4
	add r1, r0, #0
	ldr r0, [r4]
	add r3, r6, #0
	add r2, r0, r5
	add r2, #0xc2
	mov r0, #0xff
	strb r0, [r2]
	add r0, r7, #0
	mov r2, #0x6f
	bl MOD18_0223D6D8
	cmp r0, #0
	beq _0223D820
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223D820:
	ldr r0, [r4]
	add r0, r0, r5
	add r0, #0xd2
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _0223D84E
	add r0, r5, #0
	bl FUN_0202DFA4
	ldr r1, [r4]
	add r3, r6, #0
	add r2, r1, r5
	add r2, #0xd2
	mov r1, #0xff
	strb r1, [r2]
	mov r1, #0
	mov r2, #0x70
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223D84E
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223D84E:
	ldr r0, [r4]
	ldr r1, _0223D8A4 ; =0x0000013D
	add r2, r0, r5
	ldrb r1, [r2, r1]
	cmp r1, #1
	bne _0223D896
	lsl r4, r5, #2
	add r0, r0, r4
	add r0, #0xdc
	ldr r1, [r0]
	cmp r1, #0
	beq _0223D886
	add r0, r6, #0
	bl StringCopy
	ldr r0, _0223D8A0 ; =0x02251388
	ldr r0, [r0]
	add r0, r0, r4
	add r0, #0xdc
	ldr r0, [r0]
	bl String_dtor
	ldr r0, _0223D8A0 ; =0x02251388
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, r4
	add r0, #0xdc
	str r1, [r0]
_0223D886:
	ldr r0, _0223D8A0 ; =0x02251388
	mov r2, #0
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _0223D8A4 ; =0x0000013D
	strb r2, [r1, r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223D896:
	add r5, r5, #1
	cmp r5, #8
	blt _0223D7B6
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223D8A0: .word MOD18_02251388
_0223D8A4: .word 0x0000013D
	thumb_func_end MOD18_0223D7A4

	thumb_func_start MOD18_0223D8A8
MOD18_0223D8A8: ; 0x0223D8A8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	strh r5, [r0]
	strh r4, [r0, #2]
	ldr r0, _0223D8F0 ; =0x02251388
	add r1, r5, #0
	ldr r0, [r0]
	add r2, r4, #0
	ldr r0, [r0, #0xc]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _0223D8CA
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223D8CA:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0223F764
	cmp r0, #0
	beq _0223D8DA
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223D8DA:
	mov r1, #0
	add r0, sp, #0
	mvn r1, r1
	bl MOD18_0224B04C
	cmp r0, #0xff
	beq _0223D8EC
	mov r0, #1
	pop {r3, r4, r5, pc}
_0223D8EC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223D8F0: .word MOD18_02251388
	thumb_func_end MOD18_0223D8A8

	thumb_func_start MOD18_0223D8F4
MOD18_0223D8F4: ; 0x0223D8F4
	push {r3, lr}
	sub sp, #0x18
	ldr r0, _0223D9D4 ; =0x02251388
	ldr r1, _0223D9D8 ; =0x00000146
	ldr r0, [r0]
	ldrb r2, [r0, r1]
	cmp r2, #0
	beq _0223D912
	sub r1, #0x12
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _0223D912
	add sp, #0x18
	mov r0, #0
	pop {r3, pc}
_0223D912:
	ldr r1, _0223D9DC ; =gMain + 0x40
	ldrh r1, [r1, #0x20]
	cmp r1, #0
	beq _0223D9BA
	mov r1, #0x4d
	mov r2, #0x1e
	lsl r1, r1, #2
	strb r2, [r0, r1]
	ldr r0, _0223D9D4 ; =0x02251388
	add r1, #0x17
	ldr r0, [r0]
	ldrb r0, [r0, r1]
	cmp r0, #0
	bne _0223D9BA
	bl FUN_0204D610
	cmp r0, #0
	beq _0223D9BA
	bl FUN_02031190
	bl FUN_0204D830
	cmp r0, #0
	bne _0223D9BA
	bl FUN_020311F0
	cmp r0, #0
	beq _0223D950
	add sp, #0x18
	mov r0, #0
	pop {r3, pc}
_0223D950:
	bl FUN_02031190
	bl FUN_0204F6B4
	cmp r0, #0
	beq _0223D962
	add sp, #0x18
	mov r0, #0
	pop {r3, pc}
_0223D962:
	ldr r3, _0223D9D4 ; =0x02251388
	ldr r2, _0223D9DC ; =gMain + 0x40
	ldr r3, [r3]
	ldrh r1, [r2, #0x1c]
	ldr r3, [r3, #0xc]
	ldrh r2, [r2, #0x1e]
	add r3, #0x88
	ldr r3, [r3]
	add r0, sp, #0xc
	bl MOD05_021F0318
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x14]
	add r2, sp, #8
	add r3, sp, #4
	bl MOD05_021EF4F8
	ldr r1, [sp, #8]
	add r0, sp, #0
	strh r1, [r0]
	ldr r1, [sp, #4]
	strh r1, [r0, #2]
	ldr r1, _0223D9DC ; =gMain + 0x40
	ldr r0, _0223D9D4 ; =0x02251388
	ldrh r3, [r1, #0x1c]
	ldr r2, [r0]
	strh r3, [r2, #0x18]
	ldrh r2, [r1, #0x1e]
	ldr r1, [r0]
	strh r2, [r1, #0x1a]
	ldr r2, [sp, #8]
	ldr r1, [r0]
	strh r2, [r1, #0x1c]
	ldr r1, [sp, #4]
	ldr r0, [r0]
	mov r2, #4
	strh r1, [r0, #0x1e]
	mov r0, #0x30
	add r1, sp, #0
	bl FUN_02030ADC
	add sp, #0x18
	mov r0, #1
	pop {r3, pc}
_0223D9BA:
	ldr r0, _0223D9D4 ; =0x02251388
	ldr r2, [r0]
	mov r0, #0x4d
	lsl r0, r0, #2
	ldrb r1, [r2, r0]
	cmp r1, #0
	beq _0223D9CC
	sub r1, r1, #1
	strb r1, [r2, r0]
_0223D9CC:
	mov r0, #0
	add sp, #0x18
	pop {r3, pc}
	nop
_0223D9D4: .word MOD18_02251388
_0223D9D8: .word 0x00000146
_0223D9DC: .word gMain + 0x40
	thumb_func_end MOD18_0223D8F4

	thumb_func_start MOD18_0223D9E0
MOD18_0223D9E0: ; 0x0223D9E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r6, r2, #0
	str r0, [sp]
	ldrh r0, [r6]
	str r1, [sp, #4]
	mov r1, #6
	sub r0, r0, #6
	str r0, [sp, #0xc]
	ldrh r0, [r6, #2]
	mov r4, #1
	sub r0, r0, #6
	str r0, [sp, #8]
	add r0, sp, #0x14
	bl MOD18_0223CF34
	add r0, sp, #0x14
	add r1, sp, #0x10
	bl MOD18_0223CF3C
	cmp r0, #0
	beq _0223DA50
_0223DA0C:
	add r1, sp, #0x10
	mov r0, #0
	ldrh r2, [r6]
	ldrsh r0, [r1, r0]
	add r5, r2, r0
	mov r0, #2
	ldrh r2, [r6, #2]
	ldrsh r0, [r1, r0]
	add r7, r2, r0
	ldr r2, [sp, #4]
	add r0, r5, #0
	add r1, r7, #0
	blx r2
	cmp r0, #0
	beq _0223DA44
	ldr r0, [sp, #0xc]
	sub r1, r5, r0
	ldr r0, [sp, #8]
	sub r0, r7, r0
	lsl r0, r0, #4
	add r1, r1, r0
	ldr r0, [sp]
	cmp r4, #8
	strb r1, [r0, r4]
	bne _0223DA42
	add r4, r4, #1
	b _0223DA50
_0223DA42:
	add r4, r4, #1
_0223DA44:
	add r0, sp, #0x14
	add r1, sp, #0x10
	bl MOD18_0223CF3C
	cmp r0, #0
	bne _0223DA0C
_0223DA50:
	add r0, r4, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0223D9E0

	thumb_func_start MOD18_0223DA58
MOD18_0223DA58: ; 0x0223DA58
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	strb r0, [r1]
	ldr r1, _0223DA90 ; =MOD18_0223F764
	add r0, sp, #0
	add r2, r4, #0
	bl MOD18_0223D9E0
	add r2, r0, #0
	mov r0, #0x31
	add r1, sp, #0
	bl FUN_02030BC4
	ldr r1, _0223DA94 ; =MOD18_0223C6E4
	add r0, sp, #0
	add r2, r4, #0
	bl MOD18_0223D9E0
	add r2, r0, #0
	mov r0, #0x32
	add r1, sp, #0
	bl FUN_02030BC4
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_0223DA90: .word MOD18_0223F764
_0223DA94: .word MOD18_0223C6E4
	thumb_func_end MOD18_0223DA58

	thumb_func_start MOD18_0223DA98
MOD18_0223DA98: ; 0x0223DA98
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r2, #0
	bl FUN_0204EB14
	cmp r0, #0
	beq _0223DAC0
	add r0, r5, #0
	bl FUN_0204D830
	cmp r0, #0
	bne _0223DAC0
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0223DA58
_0223DAC0:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0223DA98

	thumb_func_start MOD18_0223DAC4
MOD18_0223DAC4: ; 0x0223DAC4
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _0223DAEE
	ldr r1, _0223DAF0 ; =0x02251388
	add r0, r4, #1
	ldr r1, [r1]
	sub r2, r5, #1
	add r1, #0xfc
	bl MI_CpuCopy8
	ldr r0, _0223DAF0 ; =0x02251388
	sub r2, r5, #1
	ldr r1, [r0]
	mov r0, #0x52
	lsl r0, r0, #2
	strb r2, [r1, r0]
_0223DAEE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0223DAF0: .word MOD18_02251388
	thumb_func_end MOD18_0223DAC4

	thumb_func_start MOD18_0223DAF4
MOD18_0223DAF4: ; 0x0223DAF4
	push {r3, r4, r5, lr}
	sub sp, #0x28
	add r4, r2, #0
	add r5, r1, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _0223DB8E
	ldr r1, _0223DB94 ; =0x02251388
	add r0, r4, #1
	ldr r2, [r1]
	mov r1, #0x41
	lsl r1, r1, #2
	add r1, r2, r1
	sub r2, r5, #1
	bl MI_CpuCopy8
	ldr r2, _0223DB94 ; =0x02251388
	ldr r0, _0223DB98 ; =0x00000149
	ldr r1, [r2]
	sub r3, r5, #1
	strb r3, [r1, r0]
	ldr r2, [r2]
	ldr r1, _0223DB9C ; =MOD18_0223D1A4
	add r0, sp, #0x1c
	add r2, #0x1c
	bl MOD18_0223D9E0
	ldr r1, _0223DB94 ; =0x02251388
	ldr r2, _0223DBA0 ; =0x0000014A
	ldr r3, [r1]
	strb r0, [r3, r2]
	ldr r3, [r1]
	ldrb r0, [r3, r2]
	sub r0, r0, #1
	strb r0, [r3, r2]
	ldr r3, [r1]
	add r1, r2, #0
	add r0, sp, #0x1c
	sub r1, #0x3e
	ldrb r2, [r3, r2]
	add r0, #1
	add r1, r3, r1
	bl MI_CpuCopy8
	ldr r0, _0223DB94 ; =0x02251388
	ldr r3, [r0]
	ldrh r0, [r3, #0x1a]
	str r0, [sp]
	add r0, r3, #0
	add r0, #0xfc
	str r0, [sp, #4]
	mov r0, #0x52
	lsl r0, r0, #2
	ldrb r1, [r3, r0]
	str r1, [sp, #8]
	add r1, r0, #0
	sub r1, #0x44
	add r1, r3, r1
	str r1, [sp, #0xc]
	add r1, r0, #1
	ldrb r1, [r3, r1]
	str r1, [sp, #0x10]
	add r1, r0, #0
	sub r1, #0x3c
	add r1, r3, r1
	str r1, [sp, #0x14]
	add r0, r0, #2
	ldrb r0, [r3, r0]
	str r0, [sp, #0x18]
	ldr r0, [r3, #0xc]
	ldrh r1, [r3, #0x1c]
	ldrh r2, [r3, #0x1e]
	ldrh r3, [r3, #0x18]
	bl MOD18_02243E18
_0223DB8E:
	add sp, #0x28
	pop {r3, r4, r5, pc}
	nop
_0223DB94: .word MOD18_02251388
_0223DB98: .word 0x00000149
_0223DB9C: .word MOD18_0223D1A4
_0223DBA0: .word 0x0000014A
	thumb_func_end MOD18_0223DAF4

	thumb_func_start MOD18_0223DBA4
MOD18_0223DBA4: ; 0x0223DBA4
	cmp r0, #0
	bne _0223DBAE
	mov r0, #0xe1
	lsl r0, r0, #0xc
	bx lr
_0223DBAE:
	ldrh r1, [r0, #2]
	ldrh r2, [r0]
	mov r0, #0xf
	lsl r0, r0, #6
	mul r0, r1
	add r0, r2, r0
	bx lr
	thumb_func_end MOD18_0223DBA4

	thumb_func_start MOD18_0223DBBC
MOD18_0223DBBC: ; 0x0223DBBC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r1, _0223DC24 ; =0x02251388
	mov r4, #0
	ldr r2, [r1]
	mov r1, #0x4b
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	sub r5, r1, #1
	bl MOD18_0223DBA4
	str r0, [sp]
	ldr r0, _0223DC24 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r7, [r1, r0]
	cmp r5, #0
	ble _0223DC04
_0223DBE2:
	add r1, r4, r5
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r6, r0, #1
	add r0, sp, #4
	add r1, r6, #0
	blx r7
	bl MOD18_0223DBA4
	ldr r1, [sp]
	cmp r0, r1
	bge _0223DBFE
	add r4, r6, #1
	b _0223DC00
_0223DBFE:
	add r5, r6, #0
_0223DC00:
	cmp r4, r5
	blt _0223DBE2
_0223DC04:
	add r0, sp, #4
	add r1, r4, #0
	blx r7
	bl MOD18_0223DBA4
	ldr r1, [sp]
	cmp r1, r0
	bne _0223DC1A
	add sp, #8
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223DC1A:
	mov r0, #0
	mvn r0, r0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223DC24: .word MOD18_02251388
	thumb_func_end MOD18_0223DBBC

	thumb_func_start MOD18_0223DC28
MOD18_0223DC28: ; 0x0223DC28
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r1, _0223DC78 ; =0x02251388
	mov r4, #0
	ldr r2, [r1]
	mov r1, #0x4b
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	sub r5, r1, #2
	bl MOD18_0223DBA4
	str r0, [sp]
	ldr r0, _0223DC78 ; =0x02251388
	add r5, r5, #1
	ldr r1, [r0]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r7, [r1, r0]
	cmp r5, #0
	ble _0223DC72
_0223DC50:
	add r1, r4, r5
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r6, r0, #1
	add r0, sp, #4
	add r1, r6, #0
	blx r7
	bl MOD18_0223DBA4
	ldr r1, [sp]
	cmp r0, r1
	bge _0223DC6C
	add r4, r6, #1
	b _0223DC6E
_0223DC6C:
	add r5, r6, #0
_0223DC6E:
	cmp r4, r5
	blt _0223DC50
_0223DC72:
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223DC78: .word MOD18_02251388
	thumb_func_end MOD18_0223DC28

	thumb_func_start MOD18_0223DC7C
MOD18_0223DC7C: ; 0x0223DC7C
	push {r3, r4}
	ldr r3, _0223DC94 ; =0x02251388
	mov r2, #0x45
	ldr r4, [r3]
	lsl r2, r2, #2
	str r1, [r4, r2]
	ldr r1, [r3]
	add r2, #0x18
	str r0, [r1, r2]
	pop {r3, r4}
	bx lr
	nop
_0223DC94: .word MOD18_02251388
	thumb_func_end MOD18_0223DC7C

	thumb_func_start MOD18_0223DC98
MOD18_0223DC98: ; 0x0223DC98
	push {r3, lr}
	bl FUN_02031190
	bl FUN_0204F6B4
	cmp r0, #0
	bne _0223DCB0
	mov r0, #0x1b
	bl FUN_020311DC
	bl FUN_0203086C
_0223DCB0:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0223DC98

	thumb_func_start MOD18_0223DCB4
MOD18_0223DCB4: ; 0x0223DCB4
	ldr r0, _0223DCC8 ; =0x02251388
	ldr r2, [r0]
	ldr r0, _0223DCCC ; =0x00000146
	ldrb r1, [r2, r0]
	cmp r1, #0
	beq _0223DCC4
	sub r1, r1, #1
	strb r1, [r2, r0]
_0223DCC4:
	bx lr
	nop
_0223DCC8: .word MOD18_02251388
_0223DCCC: .word 0x00000146
	thumb_func_end MOD18_0223DCB4

	thumb_func_start MOD18_0223DCD0
MOD18_0223DCD0: ; 0x0223DCD0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, _0223DD6C ; =0x02251388
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r4, r0, #0
	ldr r0, _0223DD6C ; =0x02251388
	ldr r2, [r0]
	ldr r0, _0223DD70 ; =0x00000146
	ldrb r1, [r2, r0]
	cmp r1, #0
	beq _0223DCF8
	sub r0, #0x12
	ldrb r0, [r2, r0]
	cmp r0, #0
	bne _0223DD66
_0223DCF8:
	bl FUN_02031190
	bl FUN_0204F6B4
	cmp r0, #0
	bne _0223DD66
	add r0, r4, #0
	bl FUN_0202623C
	cmp r0, #0x28
	bne _0223DD16
	mov r0, #0x10
	orr r0, r5
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0223DD16:
	bl FUN_02031190
	bl FUN_0204E4D4
	add r4, r0, #0
	bl FUN_02031190
	bl FUN_0204E50C
	add r6, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_0223D1A4
	cmp r0, #0
	beq _0223DD3E
	mov r0, #0x20
	orr r0, r5
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
_0223DD3E:
	mov r0, #0xf
	add r2, r6, #0
	and r2, r0
	lsl r0, r4, #0x1c
	add r1, sp, #0
	lsr r0, r0, #0x18
	strb r5, [r1]
	add r0, r2, r0
	strb r0, [r1, #1]
	mov r0, #0x1c
	add r1, sp, #0
	bl FUN_020311D0
	bl FUN_0203086C
	ldr r0, _0223DD6C ; =0x02251388
	mov r2, #8
	ldr r1, [r0]
	ldr r0, _0223DD70 ; =0x00000146
	strb r2, [r1, r0]
_0223DD66:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0223DD6C: .word MOD18_02251388
_0223DD70: .word 0x00000146
	thumb_func_end MOD18_0223DCD0

	thumb_func_start MOD18_0223DD74
MOD18_0223DD74: ; 0x0223DD74
	mov r0, #2
	bx lr
	thumb_func_end MOD18_0223DD74

	thumb_func_start MOD18_0223DD78
MOD18_0223DD78: ; 0x0223DD78
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r1, sp, #0
	add r6, r2, #0
	strb r5, [r1]
	bl FUN_0204E62C
	add r1, sp, #0
	strh r0, [r1, #2]
	add r0, r5, #0
	bl FUN_0204E664
	add r1, sp, #0
	strh r0, [r1, #4]
	add r0, r5, #0
	bl FUN_0204E544
	ldr r1, _0223DFB0 ; =0x0000FFFF
	cmp r0, r1
	bne _0223DDAE
	add r0, r5, #0
	bl FUN_0204E598
	ldr r1, _0223DFB0 ; =0x0000FFFF
	cmp r0, r1
	beq _0223DE62
_0223DDAE:
	add r0, r5, #0
	bl FUN_0204EB14
	cmp r0, #0
	beq _0223DE62
	add r0, r5, #0
	bl FUN_0204D830
	cmp r0, #0
	bne _0223DE62
	add r1, sp, #0
	ldrh r0, [r1, #2]
	ldrh r1, [r1, #4]
	bl FUN_0204E8B0
	add r4, r0, #0
	cmp r4, #0xff
	bne _0223DDD4
	b _0223DEDA
_0223DDD4:
	bl MOD18_02245F4C
	cmp r0, #0
	bne _0223DE62
	add r0, r4, #0
	bl MOD18_0223CAEC
	cmp r0, #0
	beq _0223DE08
	mov r1, #4
	add r0, sp, #0
	strb r1, [r0, #6]
	strb r4, [r0, #8]
	add r1, sp, #4
	strb r5, [r0, #7]
	mov r0, #0x1e
	add r1, #2
	mov r2, #3
	bl FUN_02030BC4
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DE08:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl FUN_0204F1B0
	cmp r0, #0
	bne _0223DE62
	add r0, r4, #0
	bl FUN_0204D830
	cmp r0, #0
	beq _0223DE58
	add r0, r4, #0
	bl MOD18_0223F8FC
	cmp r0, #0
	bne _0223DE36
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_022409F0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DE36:
	mov r1, #2
	add r0, sp, #0
	strb r1, [r0, #6]
	strb r4, [r0, #8]
	add r1, sp, #4
	strb r5, [r0, #7]
	mov r0, #0x1e
	add r1, #2
	mov r2, #3
	bl FUN_02030BC4
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DE58:
	add r0, r5, #0
	bl FUN_0204EB14
	cmp r0, #0
	bne _0223DE64
_0223DE62:
	b _0223DFAC
_0223DE64:
	add r0, r4, #0
	bl FUN_0204EB14
	cmp r0, #0
	beq _0223DE78
	add r0, r4, #0
	bl FUN_0204F6C8
	cmp r0, #0
	beq _0223DE9A
_0223DE78:
	mov r1, #2
	add r0, sp, #0
	strb r1, [r0, #6]
	strb r4, [r0, #8]
	add r1, sp, #4
	strb r5, [r0, #7]
	mov r0, #0x1e
	add r1, #2
	mov r2, #3
	bl FUN_02030BC4
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DE9A:
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #6]
	strb r4, [r0, #8]
	strb r5, [r0, #7]
	add r0, r4, #0
	bl FUN_0204EB14
	cmp r0, #0
	beq _0223DFAC
	add r1, sp, #4
	mov r0, #0x1e
	add r1, #2
	mov r2, #3
	bl FUN_02030BC4
	cmp r0, #0
	beq _0223DFAC
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add r0, r4, #0
	mov r1, #0
	bl FUN_0204EAD8
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0204E6FC
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DEDA:
	ldrb r2, [r6]
	add r1, sp, #0
	add r0, r5, #0
	add r1, #2
	bl MOD18_0223F50C
	cmp r0, #0
	beq _0223DEF6
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DEF6:
	add r1, sp, #0
	add r0, r5, #0
	add r1, #2
	bl MOD18_022398B4
	cmp r0, #0
	beq _0223DF10
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DF10:
	add r1, sp, #0
	add r0, r5, #0
	add r1, #2
	bl MOD18_0224B09C
	cmp r0, #0
	beq _0223DF2A
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DF2A:
	add r1, sp, #0
	add r0, r5, #0
	add r1, #2
	bl MOD18_022471D0
	cmp r0, #0
	beq _0223DF44
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DF44:
	add r1, sp, #0
	ldrh r0, [r1, #2]
	ldrh r1, [r1, #4]
	bl FUN_0204D76C
	cmp r0, #0
	beq _0223DF74
	add r0, r5, #0
	mov r1, #0xff
	mov r2, #0
	bl FUN_0204F1B0
	cmp r0, #0
	bne _0223DFAC
	mov r0, #0x18
	add r1, sp, #0
	bl FUN_02030C4C
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
_0223DF74:
	ldrb r1, [r6]
	mov r0, #0x20
	tst r0, r1
	beq _0223DFAC
	add r0, r5, #0
	bl FUN_0204F210
	cmp r0, #0
	bne _0223DFAC
	add r2, sp, #0
	ldrh r3, [r2, #4]
	mov r1, #0xf
	ldrb r0, [r6, #1]
	and r3, r1
	ldrh r1, [r2, #2]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x18
	add r1, r3, r1
	cmp r0, r1
	bne _0223DFAC
	mov r0, #0x3f
	add r1, sp, #0
	bl FUN_02030C4C
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
_0223DFAC:
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_0223DFB0: .word 0x0000FFFF
	thumb_func_end MOD18_0223DD78

	thumb_func_start MOD18_0223DFB4
MOD18_0223DFB4: ; 0x0223DFB4
	push {r3, r4, r5, r6, r7, lr}
	bl FUN_02031190
	cmp r0, #0
	bne _0223E00C
	mov r5, #0
	ldr r4, _0223E050 ; =0x02251388
	add r7, r5, #0
	mov r6, #1
_0223DFC6:
	add r0, r5, #0
	bl FUN_0202DFA4
	cmp r0, #0
	beq _0223DFE2
	ldr r0, [r4]
	add r1, r0, r5
	ldr r0, _0223E054 ; =0x00000135
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223DFE2
	add r0, r5, #0
	bl MOD18_02245358
_0223DFE2:
	add r0, r5, #0
	bl FUN_0202DFA4
	cmp r0, #0
	ldr r0, [r4]
	beq _0223DFF6
	add r1, r0, r5
	ldr r0, _0223E054 ; =0x00000135
	strb r6, [r1, r0]
	b _0223DFFC
_0223DFF6:
	add r1, r0, r5
	ldr r0, _0223E054 ; =0x00000135
	strb r7, [r1, r0]
_0223DFFC:
	add r5, r5, #1
	cmp r5, #8
	blt _0223DFC6
	bl MOD18_0223E86C
	add r0, r0, #2
	bl FUN_02032B6C
_0223E00C:
	ldr r0, _0223E050 ; =0x02251388
	ldr r2, [r0]
	ldr r0, _0223E058 ; =0x00000145
	ldrb r1, [r2, r0]
	add r1, r1, #1
	strb r1, [r2, r0]
	bl FUN_02031190
	cmp r0, #0
	bne _0223E02E
	bl FUN_0202DDE8
	cmp r0, #0
	beq _0223E02E
	mov r0, #1
	bl FUN_0204D168
_0223E02E:
	bl MOD18_0223CCC4
	bl MOD18_0223EF74
	bl MOD18_02239DD8
	ldr r0, _0223E050 ; =0x02251388
	ldr r1, [r0]
	ldr r0, _0223E05C ; =0x0000014B
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223E04E
	ldr r0, [r1, #0xc]
	ldr r0, [r0, #8]
	bl MOD18_02241D38
_0223E04E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223E050: .word MOD18_02251388
_0223E054: .word 0x00000135
_0223E058: .word 0x00000145
_0223E05C: .word 0x0000014B
	thumb_func_end MOD18_0223DFB4

	thumb_func_start MOD18_0223E060
MOD18_0223E060: ; 0x0223E060
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _0223E114 ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	bne _0223E110
	mov r1, #0x15
	mov r0, #0xf
	lsl r1, r1, #4
	bl AllocFromHeap
	add r1, r5, #0
	bl MOD18_0223D414
	bl FUN_0204D320
	add r1, r0, #0
	mov r0, #0xf
	bl AllocFromHeap
	add r1, r5, #0
	mov r2, #1
	bl FUN_0204CB20
	bl MOD18_0223ECE4
	add r1, r0, #0
	mov r0, #0xf
	bl AllocFromHeap
	add r1, r5, #0
	bl MOD18_0223E958
	bl MOD18_02245350
	add r1, r0, #0
	mov r0, #0xf
	bl AllocFromHeap
	add r1, r5, #0
	bl MOD18_02244ED0
	bl MOD18_0223CC78
	add r1, r0, #0
	mov r0, #0xf
	bl AllocFromHeap
	add r1, r5, #0
	bl MOD18_0223CB94
	bl MOD18_02239848
	add r1, r0, #0
	mov r0, #0xf
	bl AllocFromHeap
	add r1, r5, #0
	bl MOD18_02239744
	bl MOD18_0224D360
	add r1, r0, #0
	mov r0, #0xf
	bl AllocFromHeap
	add r4, r0, #0
	add r0, r5, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	add r6, r0, #0
	add r0, r5, #0
	bl ScriptEnvironment_GetSav2Ptr
	add r2, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_0224D2F0
	add r0, r5, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl MOD18_022492F8
_0223E110:
	pop {r4, r5, r6, pc}
	nop
_0223E114: .word MOD18_02251388
	thumb_func_end MOD18_0223E060

	thumb_func_start MOD18_0223E118
MOD18_0223E118: ; 0x0223E118
	push {r3, lr}
	ldr r0, _0223E14C ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	beq _0223E148
	bl MOD18_0224D344
	bl MOD18_0223CC80
	bl MOD18_022451BC
	bl MOD18_0223E9BC
	bl FUN_0204CC48
	bl MOD18_02239850
	bl MOD18_0223D688
	ldr r0, _0223E14C ; =0x02251388
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _0223E150 ; =0x0000014B
	strb r2, [r1, r0]
_0223E148:
	pop {r3, pc}
	nop
_0223E14C: .word MOD18_02251388
_0223E150: .word 0x0000014B
	thumb_func_end MOD18_0223E118

	thumb_func_start MOD18_0223E154
MOD18_0223E154: ; 0x0223E154
	push {r3, lr}
	sub sp, #8
	ldr r0, _0223E19C ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	beq _0223E198
	bl FUN_0204CC9C
	bl MOD18_0224D35C
	bl MOD18_0223CC94
	bl MOD18_022451EC
	bl MOD18_0223EA44
	bl MOD18_02239854
	ldr r0, _0223E19C ; =0x02251388
	ldr r2, _0223E1A0 ; =0x0000014B
	ldr r1, [r0]
	mov r3, #0
	strb r3, [r1, r2]
	str r3, [sp]
	mov r1, #4
	str r1, [sp, #4]
	ldr r0, [r0]
	mov r1, #3
	ldr r0, [r0, #0xc]
	add r2, #0x97
	ldr r0, [r0, #8]
	mov r3, #0xa
	bl FUN_0200CD68
_0223E198:
	add sp, #8
	pop {r3, pc}
	.align 2, 0
_0223E19C: .word MOD18_02251388
_0223E1A0: .word 0x0000014B
	thumb_func_end MOD18_0223E154

	thumb_func_start MOD18_0223E1A4
MOD18_0223E1A4: ; 0x0223E1A4
	push {r3, lr}
	ldr r0, _0223E1DC ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	beq _0223E1D8
	ldr r0, [r0, #0xc]
	ldr r0, [r0, #0xc]
	bl FUN_02025C00
	bl MOD18_02245270
	bl MOD18_0223EA78
	mov r0, #1
	bl FUN_0204CCE0
	bl MOD18_0223CCA8
	bl MOD18_02239858
	bl MOD18_02249328
	bl MOD18_0224D324
	bl MOD18_0223D5A4
_0223E1D8:
	pop {r3, pc}
	nop
_0223E1DC: .word MOD18_02251388
	thumb_func_end MOD18_0223E1A4

	thumb_func_start MOD18_0223E1E0
MOD18_0223E1E0: ; 0x0223E1E0
	push {r3, lr}
	ldr r1, _0223E1F8 ; =0x02251388
	ldr r1, [r1]
	cmp r1, #0
	beq _0223E1F6
	bl MOD18_0223EB0C
	bl FUN_0204CDB4
	bl MOD18_022452A4
_0223E1F6:
	pop {r3, pc}
	.align 2, 0
_0223E1F8: .word MOD18_02251388
	thumb_func_end MOD18_0223E1E0

	thumb_func_start MOD18_0223E1FC
MOD18_0223E1FC: ; 0x0223E1FC
	push {r4, lr}
	ldr r1, _0223E2A8 ; =0x02251388
	add r4, r0, #0
	ldr r3, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	ldrb r2, [r3, r1]
	cmp r2, #0
	beq _0223E214
	mov r0, #0
	strb r0, [r3, r1]
	pop {r4, pc}
_0223E214:
	bl MOD18_0223D7A4
	cmp r0, #0
	beq _0223E22A
	ldr r1, _0223E2A8 ; =0x02251388
	mov r0, #1
	ldr r2, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	strb r0, [r2, r1]
	pop {r4, pc}
_0223E22A:
	add r0, r4, #0
	bl MOD18_0223FB3C
	cmp r0, #0
	beq _0223E242
	ldr r1, _0223E2A8 ; =0x02251388
	mov r0, #1
	ldr r2, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	strb r0, [r2, r1]
	pop {r4, pc}
_0223E242:
	add r0, r4, #0
	bl MOD18_0223FC14
	cmp r0, #0
	beq _0223E25A
	ldr r1, _0223E2A8 ; =0x02251388
	mov r0, #1
	ldr r2, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	strb r0, [r2, r1]
	pop {r4, pc}
_0223E25A:
	add r0, r4, #0
	bl MOD18_02246D9C
	cmp r0, #0
	beq _0223E272
	ldr r1, _0223E2A8 ; =0x02251388
	mov r0, #1
	ldr r2, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	strb r0, [r2, r1]
	pop {r4, pc}
_0223E272:
	add r0, r4, #0
	bl MOD18_0223CA78
	cmp r0, #0
	beq _0223E28A
	ldr r1, _0223E2A8 ; =0x02251388
	mov r0, #1
	ldr r2, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	strb r0, [r2, r1]
	pop {r4, pc}
_0223E28A:
	add r0, r4, #0
	bl MOD18_0223D1F8
	cmp r0, #0
	beq _0223E2A2
	ldr r1, _0223E2A8 ; =0x02251388
	mov r0, #1
	ldr r2, [r1]
	mov r1, #0x53
	lsl r1, r1, #2
	strb r0, [r2, r1]
	pop {r4, pc}
_0223E2A2:
	mov r0, #0
	pop {r4, pc}
	nop
_0223E2A8: .word MOD18_02251388
	thumb_func_end MOD18_0223E1FC

	thumb_func_start MOD18_0223E2AC
MOD18_0223E2AC: ; 0x0223E2AC
	push {r3, lr}
	ldr r1, _0223E2C0 ; =0x02251388
	ldr r1, [r1]
	cmp r1, #0
	beq _0223E2BC
	bl MOD18_02246EAC
	pop {r3, pc}
_0223E2BC:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_0223E2C0: .word MOD18_02251388
	thumb_func_end MOD18_0223E2AC

	thumb_func_start MOD18_0223E2C4
MOD18_0223E2C4: ; 0x0223E2C4
	push {r3, lr}
	ldr r0, _0223E2D8 ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	beq _0223E2D4
	bl MOD18_02246ECC
	pop {r3, pc}
_0223E2D4:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_0223E2D8: .word MOD18_02251388
	thumb_func_end MOD18_0223E2C4

	thumb_func_start MOD18_0223E2DC
MOD18_0223E2DC: ; 0x0223E2DC
	push {r3, lr}
	ldr r0, _0223E2F0 ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	beq _0223E2EC
	bl MOD18_02246EF4
	pop {r3, pc}
_0223E2EC:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_0223E2F0: .word MOD18_02251388
	thumb_func_end MOD18_0223E2DC

	thumb_func_start MOD18_0223E2F4
MOD18_0223E2F4: ; 0x0223E2F4
	cmp r0, #0x20
	ble _0223E30A
	cmp r1, #0x40
	ble _0223E30A
	ldr r2, _0223E310 ; =0x000001DF
	cmp r0, r2
	bge _0223E30A
	cmp r1, r2
	bge _0223E30A
	mov r0, #0
	bx lr
_0223E30A:
	mov r0, #1
	bx lr
	nop
_0223E310: .word 0x000001DF
	thumb_func_end MOD18_0223E2F4

	thumb_func_start MOD18_0223E314
MOD18_0223E314: ; 0x0223E314
	push {r3, lr}
	ldr r1, _0223E374 ; =0x02251388
	ldr r2, [r1]
	cmp r2, #0
	beq _0223E36E
	cmp r0, #0x10
	bge _0223E360
	ldr r1, _0223E378 ; =0x00000147
	ldrb r1, [r2, r1]
	cmp r1, #4
	bhi _0223E36E
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223E336: ; jump table
	.short _0223E340 - _0223E336 - 2 ; case 0
	.short _0223E344 - _0223E336 - 2 ; case 1
	.short _0223E34E - _0223E336 - 2 ; case 2
	.short _0223E35A - _0223E336 - 2 ; case 3
	.short _0223E354 - _0223E336 - 2 ; case 4
_0223E340:
	mov r0, #0
	pop {r3, pc}
_0223E344:
	cmp r0, #8
	bge _0223E34E
	bl MOD18_0223C700
	pop {r3, pc}
_0223E34E:
	bl MOD18_0223D3AC
	pop {r3, pc}
_0223E354:
	bl MOD18_02240B28
	pop {r3, pc}
_0223E35A:
	bl MOD18_0223C740
	pop {r3, pc}
_0223E360:
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #0xc]
	bl FUN_02026CA8
	bl FUN_02026C88
	pop {r3, pc}
_0223E36E:
	mov r0, #0
	pop {r3, pc}
	nop
_0223E374: .word MOD18_02251388
_0223E378: .word 0x00000147
	thumb_func_end MOD18_0223E314

	thumb_func_start MOD18_0223E37C
MOD18_0223E37C: ; 0x0223E37C
	push {r3, lr}
	ldr r1, _0223E3DC ; =0x02251388
	ldr r2, [r1]
	cmp r2, #0
	beq _0223E3D6
	cmp r0, #0x10
	bge _0223E3C8
	ldr r1, _0223E3E0 ; =0x00000147
	ldrb r1, [r2, r1]
	cmp r1, #4
	bhi _0223E3D6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223E39E: ; jump table
	.short _0223E3A8 - _0223E39E - 2 ; case 0
	.short _0223E3AC - _0223E39E - 2 ; case 1
	.short _0223E3B6 - _0223E39E - 2 ; case 2
	.short _0223E3C2 - _0223E39E - 2 ; case 3
	.short _0223E3BC - _0223E39E - 2 ; case 4
_0223E3A8:
	mov r0, #0
	pop {r3, pc}
_0223E3AC:
	cmp r0, #8
	bge _0223E3B6
	bl MOD18_0223C720
	pop {r3, pc}
_0223E3B6:
	bl MOD18_0223D3E0
	pop {r3, pc}
_0223E3BC:
	bl MOD18_02240B5C
	pop {r3, pc}
_0223E3C2:
	bl MOD18_0223C778
	pop {r3, pc}
_0223E3C8:
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #0xc]
	bl FUN_02026CA8
	bl FUN_02026C90
	pop {r3, pc}
_0223E3D6:
	mov r0, #0
	pop {r3, pc}
	nop
_0223E3DC: .word MOD18_02251388
_0223E3E0: .word 0x00000147
	thumb_func_end MOD18_0223E37C

	thumb_func_start MOD18_0223E3E4
MOD18_0223E3E4: ; 0x0223E3E4
	push {r3, lr}
	ldr r1, _0223E43C ; =0x02251388
	ldr r2, [r1]
	cmp r2, #0
	beq _0223E438
	cmp r0, #0x10
	bge _0223E424
	ldr r1, _0223E440 ; =0x00000147
	ldrb r1, [r2, r1]
	cmp r1, #4
	bhi _0223E438
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0223E406: ; jump table
	.short _0223E438 - _0223E406 - 2 ; case 0
	.short _0223E410 - _0223E406 - 2 ; case 1
	.short _0223E418 - _0223E406 - 2 ; case 2
	.short _0223E420 - _0223E406 - 2 ; case 3
	.short _0223E41C - _0223E406 - 2 ; case 4
_0223E410:
	cmp r0, #8
	bge _0223E418
	mov r0, #0xc
	pop {r3, pc}
_0223E418:
	mov r0, #9
	pop {r3, pc}
_0223E41C:
	mov r0, #0xb
	pop {r3, pc}
_0223E420:
	mov r0, #0xc
	pop {r3, pc}
_0223E424:
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #0xc]
	bl FUN_02026CA8
	bl FUN_02026CA0
	cmp r0, #0
	beq _0223E438
	mov r0, #3
	pop {r3, pc}
_0223E438:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_0223E43C: .word MOD18_02251388
_0223E440: .word 0x00000147
	thumb_func_end MOD18_0223E3E4

	thumb_func_start MOD18_0223E444
MOD18_0223E444: ; 0x0223E444
	ldr r0, _0223E450 ; =0x02251388
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _0223E454 ; =0x00000147
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223E450: .word MOD18_02251388
_0223E454: .word 0x00000147
	thumb_func_end MOD18_0223E444

	thumb_func_start MOD18_0223E458
MOD18_0223E458: ; 0x0223E458
	ldr r0, _0223E464 ; =0x02251388
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _0223E468 ; =0x00000147
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223E464: .word MOD18_02251388
_0223E468: .word 0x00000147
	thumb_func_end MOD18_0223E458

	thumb_func_start MOD18_0223E46C
MOD18_0223E46C: ; 0x0223E46C
	ldr r0, _0223E478 ; =0x02251388
	mov r2, #2
	ldr r1, [r0]
	ldr r0, _0223E47C ; =0x00000147
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223E478: .word MOD18_02251388
_0223E47C: .word 0x00000147
	thumb_func_end MOD18_0223E46C

	thumb_func_start MOD18_0223E480
MOD18_0223E480: ; 0x0223E480
	ldr r0, _0223E48C ; =0x02251388
	mov r2, #4
	ldr r1, [r0]
	ldr r0, _0223E490 ; =0x00000147
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223E48C: .word MOD18_02251388
_0223E490: .word 0x00000147
	thumb_func_end MOD18_0223E480

	thumb_func_start MOD18_0223E494
MOD18_0223E494: ; 0x0223E494
	ldr r0, _0223E4A0 ; =0x02251388
	mov r2, #3
	ldr r1, [r0]
	ldr r0, _0223E4A4 ; =0x00000147
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223E4A0: .word MOD18_02251388
_0223E4A4: .word 0x00000147
	thumb_func_end MOD18_0223E494

	thumb_func_start MOD18_0223E4A8
MOD18_0223E4A8: ; 0x0223E4A8
	ldr r2, _0223E4B8 ; =0x02251388
	ldr r2, [r2]
	cmp r2, #0
	beq _0223E4B6
	add r0, r2, r0
	add r0, #0xc2
	strb r1, [r0]
_0223E4B6:
	bx lr
	.align 2, 0
_0223E4B8: .word MOD18_02251388
	thumb_func_end MOD18_0223E4A8

	thumb_func_start MOD18_0223E4BC
MOD18_0223E4BC: ; 0x0223E4BC
	ldr r1, _0223E4D0 ; =0x02251388
	ldr r2, [r1]
	cmp r2, #0
	beq _0223E4CC
	add r0, r2, r0
	mov r1, #1
	add r0, #0xd2
	strb r1, [r0]
_0223E4CC:
	bx lr
	nop
_0223E4D0: .word MOD18_02251388
	thumb_func_end MOD18_0223E4BC

	thumb_func_start MOD18_0223E4D4
MOD18_0223E4D4: ; 0x0223E4D4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _0223E550 ; =0x02251388
	ldr r0, [r0]
	cmp r0, #0
	beq _0223E54E
	lsl r4, r5, #2
	add r0, r0, r4
	add r0, #0xdc
	ldr r0, [r0]
	cmp r0, #0
	bne _0223E54E
	mov r0, #0x64
	mov r1, #0xf
	bl String_ctor
	ldr r1, _0223E550 ; =0x02251388
	ldr r1, [r1]
	add r1, r1, r4
	add r1, #0xdc
	str r0, [r1]
	mov r0, #0xb
	bl ScrStrBufs_new
	add r6, r0, #0
	mov r0, #0x64
	mov r1, #0xb
	bl String_ctor
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0202DFA4
	add r2, r0, #0
	add r0, r6, #0
	mov r1, #0
	bl BufferPlayersName
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	mov r1, #0x73
	add r2, r7, #0
	bl ReadMsgDataIntoString
	ldr r1, _0223E550 ; =0x02251388
	add r0, r6, #0
	ldr r1, [r1]
	add r2, r7, #0
	add r1, r1, r4
	add r1, #0xdc
	ldr r1, [r1]
	bl StringExpandPlaceholders
	add r0, r7, #0
	bl String_dtor
	add r0, r6, #0
	bl ScrStrBufs_delete
_0223E54E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223E550: .word MOD18_02251388
	thumb_func_end MOD18_0223E4D4

	thumb_func_start MOD18_0223E554
MOD18_0223E554: ; 0x0223E554
	ldr r1, _0223E564 ; =0x02251388
	mov r2, #1
	ldr r1, [r1]
	add r1, r1, r0
	ldr r0, _0223E568 ; =0x0000013D
	strb r2, [r1, r0]
	bx lr
	nop
_0223E564: .word MOD18_02251388
_0223E568: .word 0x0000013D
	thumb_func_end MOD18_0223E554

	thumb_func_start MOD18_0223E56C
MOD18_0223E56C: ; 0x0223E56C
	ldr r1, _0223E578 ; =0x02251388
	ldr r1, [r1]
	add r1, #0xc0
	strh r0, [r1]
	bx lr
	nop
_0223E578: .word MOD18_02251388
	thumb_func_end MOD18_0223E56C

	thumb_func_start MOD18_0223E57C
MOD18_0223E57C: ; 0x0223E57C
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	ldr r1, _0223E5EC ; =0x02251388
	add r5, r2, #0
	ldr r3, [r1]
	add r1, r3, #0
	add r1, #0xc0
	ldrh r4, [r1]
	cmp r4, #0
	beq _0223E5EA
	mov r1, #0
	add r2, r3, #0
_0223E594:
	ldrh r6, [r2, #0x20]
	cmp r4, r6
	bne _0223E5B0
	ldrh r6, [r2, #0x22]
	cmp r0, r6
	bne _0223E5B0
	lsl r1, r1, #3
	add r0, r3, r1
	strh r7, [r0, #0x24]
	ldr r0, _0223E5EC ; =0x02251388
	ldr r0, [r0]
	add r0, r0, r1
	strh r5, [r0, #0x26]
	pop {r3, r4, r5, r6, r7, pc}
_0223E5B0:
	add r1, r1, #1
	add r2, #8
	cmp r1, #0x14
	blt _0223E594
	mov r6, #0
	add r2, r3, #0
_0223E5BC:
	ldrh r1, [r2, #0x20]
	cmp r1, #0
	bne _0223E5DE
	lsl r1, r6, #3
	add r2, r3, r1
	strh r4, [r2, #0x20]
	ldr r2, _0223E5EC ; =0x02251388
	ldr r3, [r2]
	add r3, r3, r1
	strh r0, [r3, #0x22]
	ldr r0, [r2]
	add r0, r0, r1
	strh r7, [r0, #0x24]
	ldr r0, [r2]
	add r0, r0, r1
	strh r5, [r0, #0x26]
	pop {r3, r4, r5, r6, r7, pc}
_0223E5DE:
	add r6, r6, #1
	add r2, #8
	cmp r6, #0x14
	blt _0223E5BC
	bl ErrorHandling
_0223E5EA:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223E5EC: .word MOD18_02251388
	thumb_func_end MOD18_0223E57C

	thumb_func_start MOD18_0223E5F0
MOD18_0223E5F0: ; 0x0223E5F0
	push {r4, r5}
	ldr r1, _0223E624 ; =0x02251388
	mov r3, #0
	ldr r1, [r1]
	add r2, r1, #0
	add r2, #0xc0
	ldrh r5, [r2]
	add r4, r1, #0
_0223E600:
	ldrh r2, [r4, #0x20]
	cmp r5, r2
	bne _0223E616
	ldrh r2, [r4, #0x22]
	cmp r0, r2
	bne _0223E616
	lsl r0, r3, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x26]
	pop {r4, r5}
	bx lr
_0223E616:
	add r3, r3, #1
	add r4, #8
	cmp r3, #0x14
	blt _0223E600
	mov r0, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
_0223E624: .word MOD18_02251388
	thumb_func_end MOD18_0223E5F0

	thumb_func_start MOD18_0223E628
MOD18_0223E628: ; 0x0223E628
	push {r4, r5}
	ldr r1, _0223E65C ; =0x02251388
	mov r3, #0
	ldr r1, [r1]
	add r2, r1, #0
	add r2, #0xc0
	ldrh r5, [r2]
	add r4, r1, #0
_0223E638:
	ldrh r2, [r4, #0x20]
	cmp r5, r2
	bne _0223E64E
	ldrh r2, [r4, #0x22]
	cmp r0, r2
	bne _0223E64E
	lsl r0, r3, #3
	add r0, r1, r0
	ldrh r0, [r0, #0x24]
	pop {r4, r5}
	bx lr
_0223E64E:
	add r3, r3, #1
	add r4, #8
	cmp r3, #0x14
	blt _0223E638
	mov r0, #0
	pop {r4, r5}
	bx lr
	.align 2, 0
_0223E65C: .word MOD18_02251388
	thumb_func_end MOD18_0223E628

	thumb_func_start MOD18_0223E660
MOD18_0223E660: ; 0x0223E660
	push {r4, lr}
	ldrb r4, [r2]
	bl FUN_02031190
	cmp r4, r0
	bne _0223E680
	ldr r0, _0223E684 ; =0x02251388
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl MOD18_0224D1F8
	mov r0, #0x19
	bl FUN_020311DC
	bl FUN_0204F7E4
_0223E680:
	pop {r4, pc}
	nop
_0223E684: .word MOD18_02251388
	thumb_func_end MOD18_0223E660

	thumb_func_start MOD18_0223E688
MOD18_0223E688: ; 0x0223E688
	push {r3, r4}
	ldr r3, _0223E69C ; =0x02251388
	ldr r4, [r3]
	str r0, [r4]
	ldr r0, [r3]
	str r1, [r0, #4]
	ldr r0, [r3]
	str r2, [r0, #8]
	pop {r3, r4}
	bx lr
	.align 2, 0
_0223E69C: .word MOD18_02251388
	thumb_func_end MOD18_0223E688

	thumb_func_start MOD18_0223E6A0
MOD18_0223E6A0: ; 0x0223E6A0
	ldr r0, _0223E6B4 ; =0x02251388
	mov r2, #0
	ldr r1, [r0]
	str r2, [r1]
	ldr r1, [r0]
	str r2, [r1, #4]
	ldr r0, [r0]
	str r2, [r0, #8]
	bx lr
	nop
_0223E6B4: .word MOD18_02251388
	thumb_func_end MOD18_0223E6A0

	thumb_func_start MOD18_0223E6B8
MOD18_0223E6B8: ; 0x0223E6B8
	push {r4, lr}
	ldr r0, _0223E730 ; =0x02251388
	mov r4, #0
	ldr r2, [r0]
	ldr r0, [r2, #4]
	cmp r0, #0
	beq _0223E6D2
	ldr r1, [r2]
	ldr r2, [r2, #8]
	blx r2
	bl MOD18_0223E6A0
	mov r4, #1
_0223E6D2:
	bl MOD18_0223D688
	ldr r0, _0223E730 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DD94
	ldr r0, _0223E730 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DD94
	ldr r0, _0223E730 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD18_0224DD94
	ldr r0, _0223E730 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DD94
	ldr r0, _0223E730 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DD94
	ldr r0, _0223E730 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DD94
	add r0, r4, #0
	pop {r4, pc}
	nop
_0223E730: .word MOD18_02251388
	thumb_func_end MOD18_0223E6B8

	thumb_func_start MOD18_0223E734
MOD18_0223E734: ; 0x0223E734
	push {r3, r4, r5, lr}
	ldr r2, _0223E7A8 ; =0x02251388
	add r4, r0, #0
	ldr r1, [r2]
	ldr r3, [r1, #4]
	cmp r3, #0
	beq _0223E746
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223E746:
	ldr r3, [r1, #0xc]
	ldr r3, [r3, #0x10]
	cmp r3, #0
	beq _0223E768
	mov r0, #0x13
	lsl r0, r0, #4
	ldr r3, [r1, r0]
	add r3, r3, #1
	str r3, [r1, r0]
	ldr r1, [r2]
	ldr r0, [r1, r0]
	cmp r0, #0x64
	ble _0223E764
	bl ErrorHandling
_0223E764:
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223E768:
	bl FUN_0204D830
	cmp r0, #0
	beq _0223E774
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223E774:
	add r0, r4, #0
	bl FUN_0204E494
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204E4B4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _0223E796
	cmp r4, #0
	beq _0223E796
	mov r0, #0
	pop {r3, r4, r5, pc}
_0223E796:
	ldr r0, _0223E7A8 ; =0x02251388
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0x13
	lsl r0, r0, #4
	str r2, [r1, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0223E7A8: .word MOD18_02251388
	thumb_func_end MOD18_0223E734

	thumb_func_start MOD18_0223E7AC
MOD18_0223E7AC: ; 0x0223E7AC
	push {r3, lr}
	ldr r0, _0223E7F8 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DFA0
	ldr r0, _0223E7F8 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x47
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DFA0
	ldr r0, _0223E7F8 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl MOD18_0224DFA0
	ldr r0, _0223E7F8 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DFA0
	ldr r0, _0223E7F8 ; =0x02251388
	ldr r1, [r0]
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl MOD18_0224DFA0
	pop {r3, pc}
	nop
_0223E7F8: .word MOD18_02251388
	thumb_func_end MOD18_0223E7AC

	thumb_func_start MOD18_0223E7FC
MOD18_0223E7FC: ; 0x0223E7FC
	push {r3, lr}
	sub sp, #8
	bl MOD18_022478C4
	add r1, sp, #0
	strh r0, [r1]
	bl MOD18_022478E0
	add r1, sp, #0
	strh r0, [r1, #2]
	bl MOD18_02247900
	add r1, sp, #0
	strb r0, [r1, #4]
	bl MOD18_0223CB24
	add r1, sp, #0
	strb r0, [r1, #5]
	mov r0, #0x46
	add r1, sp, #0
	bl FUN_020311D0
	add sp, #8
	pop {r3, pc}
	thumb_func_end MOD18_0223E7FC

	thumb_func_start MOD18_0223E82C
MOD18_0223E82C: ; 0x0223E82C
	push {r3, r4, r5, lr}
	add r4, r2, #0
	ldrh r1, [r4]
	add r5, r0, #0
	bl MOD18_0224791C
	ldrh r1, [r4, #2]
	add r0, r5, #0
	bl MOD18_02247938
	ldrb r1, [r4, #4]
	add r0, r5, #0
	bl MOD18_02247954
	ldrb r1, [r4, #5]
	add r0, r5, #0
	bl MOD18_0223CB44
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0223E82C

	thumb_func_start MOD18_0223E854
MOD18_0223E854: ; 0x0223E854
	mov r0, #6
	bx lr
	thumb_func_end MOD18_0223E854

	thumb_func_start MOD18_0223E858
MOD18_0223E858: ; 0x0223E858
	ldr r1, _0223E868 ; =0x02251388
	mov r2, #1
	ldr r1, [r1]
	add r0, r1, r0
	add r0, #0xca
	strb r2, [r0]
	bx lr
	nop
_0223E868: .word MOD18_02251388
	thumb_func_end MOD18_0223E858

	thumb_func_start MOD18_0223E86C
MOD18_0223E86C: ; 0x0223E86C
	ldr r1, _0223E88C ; =0x02251388
	mov r0, #0
	ldr r3, [r1]
	add r2, r0, #0
_0223E874:
	add r1, r3, #0
	add r1, #0xca
	ldrb r1, [r1]
	cmp r1, #0
	beq _0223E880
	add r0, r0, #1
_0223E880:
	add r2, r2, #1
	add r3, r3, #1
	cmp r2, #8
	blt _0223E874
	bx lr
	nop
_0223E88C: .word MOD18_02251388
	thumb_func_end MOD18_0223E86C

	thumb_func_start MOD18_0223E890
MOD18_0223E890: ; 0x0223E890
	ldr r1, _0223E8A0 ; =0x02251388
	ldr r3, _0223E8A4 ; =MOD18_02245358
	ldr r1, [r1]
	mov r2, #0
	add r1, r1, r0
	add r1, #0xca
	strb r2, [r1]
	bx r3
	.align 2, 0
_0223E8A0: .word MOD18_02251388
_0223E8A4: .word MOD18_02245358
	thumb_func_end MOD18_0223E890

	thumb_func_start MOD18_0223E8A8
MOD18_0223E8A8: ; 0x0223E8A8
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _0223E948 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	mov r4, #0
	ldr r7, _0223E948 ; =0x022513A0
	add r6, r0, #0
	add r5, r4, #0
	str r4, [sp]
_0223E8C2:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02026444
	ldr r1, [r7, #4]
	add r2, r1, r5
	mov r1, #0xaa
	lsl r1, r1, #2
	strb r0, [r2, r1]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02026450
	ldr r1, [r7, #4]
	add r2, r1, r5
	mov r1, #0xa9
	lsl r1, r1, #2
	strh r0, [r2, r1]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02026470
	ldr r1, [r7, #4]
	add r2, r1, r5
	ldr r1, _0223E94C ; =0x000002A6
	strh r0, [r2, r1]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_02026490
	ldr r1, [r7, #4]
	add r2, r1, r5
	ldr r1, _0223E950 ; =0x000002A9
	strb r0, [r2, r1]
	ldr r1, [r7, #4]
	ldr r0, _0223E954 ; =0x00000B46
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223E936
	mov r0, #0xaa
	add r2, r1, r5
	lsl r0, r0, #2
	ldrb r3, [r2, r0]
	cmp r3, #0
	beq _0223E936
	ldr r1, _0223E94C ; =0x000002A6
	sub r0, r0, #4
	ldrh r0, [r2, r0]
	ldrh r1, [r2, r1]
	mov r2, #1
	bl MOD18_022402F8
	ldr r2, [r7, #4]
	ldr r1, [sp]
	add r2, r2, r1
	mov r1, #0xc1
	lsl r1, r1, #2
	str r0, [r2, r1]
_0223E936:
	ldr r0, [sp]
	add r4, r4, #1
	add r0, r0, #4
	add r5, r5, #6
	str r0, [sp]
	cmp r4, #0x10
	blt _0223E8C2
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223E948: .word MOD18_022513A0
_0223E94C: .word 0x000002A6
_0223E950: .word 0x000002A9
_0223E954: .word 0x00000B46
	thumb_func_end MOD18_0223E8A8

	thumb_func_start MOD18_0223E958
MOD18_0223E958: ; 0x0223E958
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, _0223E9B0 ; =0x022513A0
	ldr r2, [r1, #4]
	cmp r2, #0
	bne _0223E9AC
	ldr r2, _0223E9B4 ; =0x00000B48
	str r0, [r1, #4]
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _0223E9B0 ; =0x022513A0
	ldr r0, [r0, #4]
	str r4, [r0, #0x40]
	add r0, r4, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	ldr r2, _0223E9B0 ; =0x022513A0
	mov r1, #0xa3
	ldr r3, [r2, #4]
	mov r0, #0
	lsl r1, r1, #2
	str r0, [r3, r1]
	ldr r1, _0223E9B8 ; =0x00000B04
	mov r5, #0xff
_0223E98E:
	ldr r3, [r2, #4]
	add r3, r3, r0
	add r0, r0, #1
	strb r5, [r3, r1]
	cmp r0, #8
	blt _0223E98E
	ldr r0, [r4, #0x20]
	bl MOD05_021F043C
	add r4, #0x88
	str r0, [r4]
	bl MOD18_0223EBF0
	bl MOD18_0223E8A8
_0223E9AC:
	pop {r3, r4, r5, pc}
	nop
_0223E9B0: .word MOD18_022513A0
_0223E9B4: .word 0x00000B48
_0223E9B8: .word 0x00000B04
	thumb_func_end MOD18_0223E958

	thumb_func_start MOD18_0223E9BC
MOD18_0223E9BC: ; 0x0223E9BC
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _0223EA3C ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	add r0, #0x88
	bl MOD05_021F04F8
	bl MOD18_0223ECB8
	bl MOD18_02243FF0
	mov r5, #0
	mov r7, #0xc1
	lsl r7, r7, #2
	ldr r1, _0223EA3C ; =0x022513A0
	add r6, r5, #0
	add r2, r5, #0
	add r0, r7, #0
_0223E9E0:
	ldr r3, [r1, #4]
	add r4, r3, r6
	ldr r3, [r4, r0]
	cmp r3, #0
	beq _0223E9EC
	str r2, [r4, r7]
_0223E9EC:
	add r5, r5, #1
	add r6, r6, #4
	cmp r5, #0x10
	blt _0223E9E0
	ldr r0, _0223EA3C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223EA12
	bl FUN_0200CAB4
	ldr r0, _0223EA3C ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	str r2, [r1, r0]
_0223EA12:
	ldr r0, _0223EA3C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223EA30
	bl FreeToHeap
	ldr r0, _0223EA3C ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r2, [r1, r0]
_0223EA30:
	ldr r0, _0223EA3C ; =0x022513A0
	mov r2, #1
	ldr r1, [r0, #4]
	ldr r0, _0223EA40 ; =0x00000B46
	strb r2, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EA3C: .word MOD18_022513A0
_0223EA40: .word 0x00000B46
	thumb_func_end MOD18_0223E9BC

	thumb_func_start MOD18_0223EA44
MOD18_0223EA44: ; 0x0223EA44
	push {r3, lr}
	ldr r0, _0223EA70 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x20]
	bl MOD05_021F043C
	ldr r1, _0223EA70 ; =0x022513A0
	ldr r2, [r1, #4]
	ldr r2, [r2, #0x40]
	add r2, #0x88
	str r0, [r2]
	ldr r1, [r1, #4]
	ldr r0, _0223EA74 ; =0x00000B46
	mov r2, #0
	strb r2, [r1, r0]
	bl MOD18_0223E8A8
	bl MOD18_0223EBF0
	pop {r3, pc}
	nop
_0223EA70: .word MOD18_022513A0
_0223EA74: .word 0x00000B46
	thumb_func_end MOD18_0223EA44

	thumb_func_start MOD18_0223EA78
MOD18_0223EA78: ; 0x0223EA78
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r6, _0223EB04 ; =0x022513A0
	add r5, r4, #0
	add r7, r4, #0
_0223EA82:
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223EA9E
	bl FUN_02064520
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0xc1
	lsl r0, r0, #2
	str r7, [r1, r0]
_0223EA9E:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x10
	blt _0223EA82
	bl MOD18_02243FF0
	bl MOD18_0223ECB8
	ldr r0, _0223EB04 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	add r0, #0x88
	bl MOD05_021F04F8
	ldr r0, _0223EB04 ; =0x022513A0
	ldr r1, _0223EB08 ; =0x00000B34
	ldr r3, [r0, #4]
	ldrh r2, [r3, r1]
	cmp r2, #0xa
	blo _0223EAD0
	add r1, r1, #2
	ldrb r1, [r3, r1]
	ldr r0, [r3, #0x40]
	bl FUN_02061B0C
_0223EAD0:
	ldr r0, _0223EB04 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223EAE2
	bl FUN_0200CAB4
_0223EAE2:
	ldr r0, _0223EB04 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223EAF4
	bl FreeToHeap
_0223EAF4:
	ldr r0, _0223EB04 ; =0x022513A0
	ldr r0, [r0, #4]
	bl FreeToHeap
	ldr r0, _0223EB04 ; =0x022513A0
	mov r1, #0
	str r1, [r0, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EB04: .word MOD18_022513A0
_0223EB08: .word 0x00000B34
	thumb_func_end MOD18_0223EA78

	thumb_func_start MOD18_0223EB0C
MOD18_0223EB0C: ; 0x0223EB0C
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r6, _0223EB80 ; =0x022513A0
	add r5, r4, #0
	add r7, r4, #0
_0223EB16:
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0xc1
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223EB32
	bl FUN_02064520
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0xc1
	lsl r0, r0, #2
	str r7, [r1, r0]
_0223EB32:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x10
	blt _0223EB16
	bl MOD18_02243FF0
	bl MOD18_0223E8A8
	mov r4, #0
	ldr r2, _0223EB80 ; =0x022513A0
	ldr r0, _0223EB84 ; =0x00000B3C
	add r1, r4, #0
_0223EB4A:
	ldr r3, [r2, #4]
	add r3, r3, r4
	add r4, r4, #1
	strb r1, [r3, r0]
	cmp r4, #8
	blt _0223EB4A
	ldr r0, _0223EB80 ; =0x022513A0
	ldr r2, [r0, #4]
	mov r0, #0xd1
	lsl r0, r0, #2
	add r0, r2, r0
	mov r2, #0x12
	lsl r2, r2, #6
	bl MI_CpuFill8
	ldr r0, _0223EB80 ; =0x022513A0
	mov r2, #3
	ldr r1, [r0, #4]
	ldr r0, _0223EB88 ; =0x000007C4
	lsl r2, r2, #8
	add r0, r1, r0
	mov r1, #0
	bl MI_CpuFill8
	bl MOD18_0223F174
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EB80: .word MOD18_022513A0
_0223EB84: .word 0x00000B3C
_0223EB88: .word 0x000007C4
	thumb_func_end MOD18_0223EB0C

	thumb_func_start MOD18_0223EB8C
MOD18_0223EB8C: ; 0x0223EB8C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0223EBE8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xd1
	lsl r0, r0, #2
	add r2, r1, r0
	lsl r1, r4, #4
	mov r0, #6
	mul r0, r1
	add r1, r2, r0
	mov r2, #0
	add r0, r2, #0
_0223EBA6:
	add r2, r2, #1
	strb r0, [r1, #4]
	add r1, r1, #6
	cmp r2, #0x10
	blt _0223EBA6
	add r0, r4, #0
	bl MOD18_0223EDFC
	ldr r0, _0223EBE8 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r4
	ldr r0, _0223EBEC ; =0x00000B3C
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223EBE6
	add r0, r4, #0
	bl FUN_0204E778
	ldr r1, _0223EBE8 ; =0x022513A0
	add r0, r4, #0
	ldr r1, [r1, #4]
	add r2, r1, r4
	ldr r1, _0223EBEC ; =0x00000B3C
	ldrb r1, [r2, r1]
	bl MOD18_0223FCD4
	ldr r0, _0223EBE8 ; =0x022513A0
	mov r2, #0
	ldr r0, [r0, #4]
	add r1, r0, r4
	ldr r0, _0223EBEC ; =0x00000B3C
	strb r2, [r1, r0]
_0223EBE6:
	pop {r4, pc}
	.align 2, 0
_0223EBE8: .word MOD18_022513A0
_0223EBEC: .word 0x00000B3C
	thumb_func_end MOD18_0223EB8C

	thumb_func_start MOD18_0223EBF0
MOD18_0223EBF0: ; 0x0223EBF0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r4, #0
	mov r7, #6
	ldr r6, _0223ECB4 ; =0x022513A0
	add r5, r4, #0
	lsl r7, r7, #6
_0223EBFE:
	mov r0, #1
	add r1, r4, #0
	mov r2, #4
	bl FUN_02008DEC
	ldr r1, [r6, #4]
	add r4, r4, #1
	add r1, r1, r5
	add r5, r5, #4
	str r0, [r1, r7]
	cmp r4, #4
	blt _0223EBFE
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, _0223ECB4 ; =0x022513A0
	mov r2, #0x11
	ldr r1, [r0, #4]
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_02008F34
	ldr r2, _0223ECB4 ; =0x022513A0
	mov r1, #0x1a
	ldr r3, [r2, #4]
	lsl r1, r1, #4
	str r0, [r3, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, [r2, #4]
	sub r1, #0x1c
	ldr r0, [r0, r1]
	mov r1, #0x32
	mov r2, #0x12
	bl FUN_02008FEC
	ldr r2, _0223ECB4 ; =0x022513A0
	mov r1, #0x69
	ldr r3, [r2, #4]
	lsl r1, r1, #2
	str r0, [r3, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r2, #4]
	sub r1, #0x1c
	ldr r0, [r0, r1]
	mov r1, #0x32
	mov r2, #0x10
	bl FUN_020090AC
	ldr r2, _0223ECB4 ; =0x022513A0
	mov r1, #0x6a
	ldr r3, [r2, #4]
	lsl r1, r1, #2
	str r0, [r3, r1]
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, [r2, #4]
	sub r1, #0x1c
	ldr r0, [r0, r1]
	mov r1, #0x32
	mov r2, #0xf
	bl FUN_020090AC
	ldr r1, _0223ECB4 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0x6b
	lsl r1, r1, #2
	str r0, [r2, r1]
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223ECB4: .word MOD18_022513A0
	thumb_func_end MOD18_0223EBF0

	thumb_func_start MOD18_0223ECB8
MOD18_0223ECB8: ; 0x0223ECB8
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	mov r7, #6
	ldr r6, _0223ECD8 ; =0x022513A0
	add r5, r4, #0
	lsl r7, r7, #6
_0223ECC4:
	ldr r0, [r6, #4]
	add r0, r0, r5
	ldr r0, [r0, r7]
	bl FUN_02008E2C
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _0223ECC4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223ECD8: .word MOD18_022513A0
	thumb_func_end MOD18_0223ECB8

	thumb_func_start MOD18_0223ECDC
MOD18_0223ECDC: ; 0x0223ECDC
	ldr r3, _0223ECE0 ; =FUN_0204F7FC
	bx r3
	.align 2, 0
_0223ECE0: .word FUN_0204F7FC
	thumb_func_end MOD18_0223ECDC

	thumb_func_start MOD18_0223ECE4
MOD18_0223ECE4: ; 0x0223ECE4
	ldr r0, _0223ECE8 ; =0x00000B48
	bx lr
	.align 2, 0
_0223ECE8: .word 0x00000B48
	thumb_func_end MOD18_0223ECE4

	thumb_func_start MOD18_0223ECEC
MOD18_0223ECEC: ; 0x0223ECEC
	mov r0, #0x60
	bx lr
	thumb_func_end MOD18_0223ECEC

	thumb_func_start MOD18_0223ECF0
MOD18_0223ECF0: ; 0x0223ECF0
	push {r3, r4}
	ldr r3, _0223ED1C ; =0x022513A0
	lsl r1, r1, #2
	ldr r2, [r3, #4]
	add r4, r2, r1
	ldr r2, _0223ED20 ; =0x000007C4
	ldr r4, [r4, r2]
	cmp r4, #0
	bne _0223ED08
	mov r0, #0
	pop {r3, r4}
	bx lr
_0223ED08:
	ldrh r4, [r4]
	strh r4, [r0]
	ldr r3, [r3, #4]
	add r1, r3, r1
	ldr r1, [r1, r2]
	ldrh r1, [r1, #2]
	strh r1, [r0, #2]
	pop {r3, r4}
	bx lr
	nop
_0223ED1C: .word MOD18_022513A0
_0223ED20: .word 0x000007C4
	thumb_func_end MOD18_0223ECF0

	thumb_func_start MOD18_0223ED24
MOD18_0223ED24: ; 0x0223ED24
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldrh r1, [r4]
	add r0, sp, #0
	strh r1, [r0]
	ldrh r1, [r4, #2]
	strh r1, [r0, #2]
	ldr r1, _0223ED8C ; =MOD18_0223ECF0
	mov r0, #0xc0
	bl MOD18_0223DC7C
	add r0, sp, #0
	bl MOD18_0223DC28
	cmp r0, #0xc0
	bge _0223ED8A
	ldr r1, _0223ED90 ; =0x022513A0
	mov r3, #0
	ldr r5, [r1, #4]
	ldr r1, _0223ED94 ; =0x000007C4
_0223ED4C:
	ldr r2, [r5, r1]
	cmp r2, r4
	beq _0223ED8A
	add r3, r3, #1
	add r5, r5, #4
	cmp r3, #0xc0
	blt _0223ED4C
	mov r2, #0xbe
	cmp r0, #0xbe
	bgt _0223ED78
	ldr r7, _0223ED90 ; =0x022513A0
	ldr r6, _0223ED98 ; =0x000007C8
	lsl r3, r2, #2
_0223ED66:
	ldr r1, [r7, #4]
	ldr r5, _0223ED94 ; =0x000007C4
	add r1, r1, r3
	ldr r5, [r1, r5]
	sub r2, r2, #1
	str r5, [r1, r6]
	sub r3, r3, #4
	cmp r2, r0
	bge _0223ED66
_0223ED78:
	ldr r1, _0223ED90 ; =0x022513A0
	lsl r3, r0, #2
	ldr r0, [r1, #4]
	add r2, r0, r3
	ldr r0, _0223ED94 ; =0x000007C4
	str r4, [r2, r0]
	ldr r1, [r1, #4]
	add r1, r1, r3
	str r4, [r1, r0]
_0223ED8A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223ED8C: .word MOD18_0223ECF0
_0223ED90: .word MOD18_022513A0
_0223ED94: .word 0x000007C4
_0223ED98: .word 0x000007C8
	thumb_func_end MOD18_0223ED24

	thumb_func_start MOD18_0223ED9C
MOD18_0223ED9C: ; 0x0223ED9C
	push {r3, r4, r5, r6}
	ldr r2, _0223EDF0 ; =0x022513A0
	mov r1, #0
	ldr r5, [r2, #4]
	ldr r2, _0223EDF4 ; =0x000007C4
	mvn r1, r1
	mov r4, #0
_0223EDAA:
	ldr r3, [r5, r2]
	cmp r3, r0
	bne _0223EDB4
	add r1, r4, #0
	b _0223EDBC
_0223EDB4:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xc0
	blt _0223EDAA
_0223EDBC:
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _0223EDEC
	cmp r1, #0xbf
	bge _0223EDE0
	ldr r0, _0223EDF8 ; =0x000007C8
	ldr r3, _0223EDF0 ; =0x022513A0
	lsl r6, r1, #2
	sub r2, r0, #4
_0223EDD0:
	ldr r4, [r3, #4]
	add r1, r1, #1
	add r5, r4, r6
	ldr r4, [r5, r0]
	add r6, r6, #4
	str r4, [r5, r2]
	cmp r1, #0xbf
	blt _0223EDD0
_0223EDE0:
	ldr r0, _0223EDF0 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	mov r0, #0x2b
	lsl r0, r0, #6
	str r2, [r1, r0]
_0223EDEC:
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
_0223EDF0: .word MOD18_022513A0
_0223EDF4: .word 0x000007C4
_0223EDF8: .word 0x000007C8
	thumb_func_end MOD18_0223ED9C

	thumb_func_start MOD18_0223EDFC
MOD18_0223EDFC: ; 0x0223EDFC
	push {r3, r4, r5, r6, r7, lr}
	lsl r5, r0, #4
	ldr r7, _0223EE58 ; =0x022513A0
	mov r6, #0
	add r4, r5, #0
_0223EE06:
	mov r0, #0xd1
	ldr r1, [r7, #4]
	lsl r0, r0, #2
	add r1, r1, r0
	mov r0, #6
	mul r0, r4
	add r0, r1, r0
	bl MOD18_0223ED9C
	add r6, r6, #1
	add r4, r4, #1
	cmp r6, #0x10
	blt _0223EE06
	mov r6, #0
	mov r0, #6
	add r7, r5, #0
	add r4, r6, #0
	mul r7, r0
_0223EE2A:
	ldr r0, _0223EE58 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r7, r0
	add r2, r4, r1
	mov r1, #0xd2
	lsl r1, r1, #2
	ldrb r1, [r2, r1]
	cmp r1, #0
	beq _0223EE4C
	mov r1, #0xd1
	lsl r1, r1, #2
	add r1, r0, r1
	mov r0, #6
	mul r0, r5
	add r0, r1, r0
	bl MOD18_0223ED24
_0223EE4C:
	add r6, r6, #1
	add r4, r4, #6
	add r5, r5, #1
	cmp r6, #0x10
	blt _0223EE2A
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EE58: .word MOD18_022513A0
	thumb_func_end MOD18_0223EDFC

	thumb_func_start MOD18_0223EE5C
MOD18_0223EE5C: ; 0x0223EE5C
	mov r2, #0
_0223EE5E:
	ldrb r1, [r0, #4]
	cmp r1, #0
	beq _0223EE6E
	add r2, r2, #1
	add r0, r0, #6
	cmp r2, #0x10
	blt _0223EE5E
	mov r0, #0
_0223EE6E:
	bx lr
	thumb_func_end MOD18_0223EE5C

	thumb_func_start MOD18_0223EE70
MOD18_0223EE70: ; 0x0223EE70
	mov r2, #0
_0223EE72:
	ldrb r1, [r0, #4]
	cmp r1, #0
	bne _0223EE7C
	add r0, r2, #0
	bx lr
_0223EE7C:
	add r2, r2, #1
	add r0, r0, #6
	cmp r2, #0x10
	blt _0223EE72
	mov r0, #0
	mvn r0, r0
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0223EE70

	thumb_func_start MOD18_0223EE8C
MOD18_0223EE8C: ; 0x0223EE8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r1, _0223EF04 ; =0x022513A0
	ldr r6, [r1, #4]
	mov r1, #0xd1
	lsl r1, r1, #2
	add r1, r6, r1
	sub r0, r0, r1
	mov r1, #6
	bl _u32_div_f
	add r4, r0, #0
	lsr r0, r4, #4
	str r0, [sp, #4]
	add r0, r0, #1
	lsl r0, r0, #4
	str r0, [sp]
	mov r0, #6
	add r5, r4, #0
	mul r5, r0
	mov r0, #0xd2
	mov r2, #0
	add r1, r6, r5
	lsl r0, r0, #2
	strb r2, [r1, r0]
	ldr r0, [sp]
	sub r6, r0, #1
	cmp r4, r6
	bhs _0223EEE8
	ldr r7, _0223EF04 ; =0x022513A0
_0223EEC8:
	mov r0, #0xd1
	ldr r1, [r7, #4]
	lsl r0, r0, #2
	add r1, r1, r0
	add r2, r4, #1
	mov r0, #6
	mul r0, r2
	add r0, r1, r0
	add r1, r1, r5
	mov r2, #6
	bl MI_CpuCopy8
	add r4, r4, #1
	add r5, r5, #6
	cmp r4, r6
	blo _0223EEC8
_0223EEE8:
	ldr r1, _0223EF04 ; =0x022513A0
	mov r2, #6
	ldr r3, [r1, #4]
	ldr r1, [sp]
	mov r0, #0
	mul r2, r1
	ldr r1, _0223EF08 ; =0x00000342
	add r2, r3, r2
	strb r0, [r2, r1]
	ldr r0, [sp, #4]
	bl MOD18_0223EDFC
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EF04: .word MOD18_022513A0
_0223EF08: .word 0x00000342
	thumb_func_end MOD18_0223EE8C

	thumb_func_start MOD18_0223EF0C
MOD18_0223EF0C: ; 0x0223EF0C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _0223EF5C ; =0x022513A0
	add r6, r1, #0
	ldr r0, [r0, #4]
	add r7, r2, #0
	ldr r0, [r0, #0x40]
	add r1, r5, #0
	add r2, r6, #0
	str r3, [sp]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _0223EF2C
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223EF2C:
	add r0, r7, #0
	bl MOD18_0223EE5C
	add r4, r0, #0
	bne _0223EF4A
	add r0, r7, #0
	bl MOD18_02240330
	add r4, r0, #0
	bl MOD18_0223EE8C
	add r0, r4, #0
	bl MOD18_0223EE5C
	add r4, r0, #0
_0223EF4A:
	strh r5, [r4]
	ldr r0, [sp]
	strh r6, [r4, #2]
	strb r0, [r4, #4]
	add r0, r4, #0
	bl MOD18_0223ED24
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223EF5C: .word MOD18_022513A0
	thumb_func_end MOD18_0223EF0C

	thumb_func_start MOD18_0223EF60
MOD18_0223EF60: ; 0x0223EF60
	push {r0, r1, r2, r3}
	push {r3, lr}
	mov r0, #0x20
	add r1, sp, #8
	bl FUN_020311D0
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	thumb_func_end MOD18_0223EF60

	thumb_func_start MOD18_0223EF74
MOD18_0223EF74: ; 0x0223EF74
	ldr r3, _0223EF78 ; =MOD18_02240C8C
	bx r3
	.align 2, 0
_0223EF78: .word MOD18_02240C8C
	thumb_func_end MOD18_0223EF74

	thumb_func_start MOD18_0223EF7C
MOD18_0223EF7C: ; 0x0223EF7C
	ldr r1, _0223EF90 ; =0x022513A0
	ldr r3, _0223EF94 ; =FUN_0203105C
	ldr r2, [r1, #4]
	mov r1, #0xa9
	lsl r1, r1, #2
	add r1, r2, r1
	mov r0, #0x23
	mov r2, #0x60
	bx r3
	nop
_0223EF90: .word MOD18_022513A0
_0223EF94: .word FUN_0203105C
	thumb_func_end MOD18_0223EF7C

	thumb_func_start MOD18_0223EF98
MOD18_0223EF98: ; 0x0223EF98
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r1, _0223F0BC ; =0x022513A0
	add r5, r0, #0
	ldr r1, [r1, #4]
	add r7, r2, #0
	cmp r1, #0
	bne _0223EFAA
	b _0223F0B6
_0223EFAA:
	add r1, sp, #0
	strb r5, [r1, #6]
	mov r2, #3
	strb r2, [r1, #7]
	bl FUN_0204E62C
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0204E664
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0204E544
	ldr r1, _0223F0C0 ; =0x0000FFFF
	cmp r0, r1
	bne _0223EFEC
	add r0, r5, #0
	bl FUN_0204E598
	ldr r1, _0223F0C0 ; =0x0000FFFF
	cmp r0, r1
	bne _0223EFEC
	mov r1, #7
	add r0, sp, #0
	strb r1, [r0, #7]
	mov r0, #0x22
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0223EFEC:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0204E8B0
	cmp r0, #0xff
	beq _0223F00C
	mov r1, #5
	add r0, sp, #0
	strb r1, [r0, #7]
	mov r0, #0x22
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0223F00C:
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0204D76C
	cmp r0, #0
	beq _0223F02C
	mov r1, #5
	add r0, sp, #0
	strb r1, [r0, #7]
	mov r0, #0x22
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0223F02C:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _0223F04C
	mov r1, #4
	add r0, sp, #0
	strb r1, [r0, #7]
	mov r0, #0x22
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0223F04C:
	ldr r0, _0223F0BC ; =0x022513A0
	add r1, r6, #0
	ldr r0, [r0, #4]
	add r2, r4, #0
	ldr r0, [r0, #0x40]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _0223F072
	mov r1, #6
	add r0, sp, #0
	strb r1, [r0, #7]
	mov r0, #0x22
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_0223F072:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_0223D8A8
	cmp r0, #0
	bne _0223F0AC
	ldr r2, _0223F0BC ; =0x022513A0
	add r1, r4, #0
	ldr r3, [r2, #4]
	mov r2, #0xd1
	lsl r2, r2, #2
	add r2, r3, r2
	lsl r4, r5, #4
	mov r3, #6
	mul r3, r4
	add r2, r2, r3
	ldrb r3, [r7]
	add r0, r6, #0
	bl MOD18_0223EF0C
	cmp r0, #0
	beq _0223F0AC
	mov r2, #1
	add r1, sp, #0
	strb r2, [r1, #7]
	add r1, sp, #0
	mov r2, #6
	bl MI_CpuCopy8
_0223F0AC:
	mov r0, #0x22
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
_0223F0B6:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F0BC: .word MOD18_022513A0
_0223F0C0: .word 0x0000FFFF
	thumb_func_end MOD18_0223EF98

	thumb_func_start MOD18_0223F0C4
MOD18_0223F0C4: ; 0x0223F0C4
	mov r0, #8
	bx lr
	thumb_func_end MOD18_0223F0C4

	thumb_func_start MOD18_0223F0C8
MOD18_0223F0C8: ; 0x0223F0C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r0, [sp, #4]
	ldr r0, _0223F16C ; =0x022513A0
	str r1, [sp, #8]
	ldr r0, [r0, #4]
	add r7, r2, #0
	ldr r0, [r0, #0x40]
	add r5, r3, #0
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	str r0, [sp, #0xc]
	cmp r5, #0x40
	blt _0223F0EC
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F0EC:
	ldr r0, _0223F16C ; =0x022513A0
	ldr r2, [r7, #4]
	ldr r1, [r0, #4]
	mov r0, #0xd1
	lsl r0, r0, #2
	add r4, r1, r0
	asr r0, r5, #3
	lsr r0, r0, #0x1c
	add r0, r5, r0
	asr r0, r0, #4
	add r0, #8
	lsl r1, r0, #4
	add r6, r1, #0
	mov r0, #6
	ldr r1, [r7]
	mul r6, r0
	ldr r0, [r7, #8]
	mul r1, r2
	add r0, r0, r1
	str r0, [r7]
	lsr r1, r0, #0x10
	mov r0, #0x1a
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldr r0, _0223F170 ; =0x02250460
	ldrb r7, [r0, r1]
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	bl MOD18_0223D8A8
	cmp r0, #0
	bne _0223F166
	add r0, r4, r6
	bl MOD18_0223EE5C
	cmp r0, #0
	beq _0223F166
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	add r2, r4, r6
	add r3, r7, #0
	bl MOD18_0223EF0C
	cmp r0, #0
	beq _0223F166
	strb r5, [r0, #5]
	ldr r0, [sp, #8]
	ldr r3, [sp, #4]
	str r0, [sp]
	ldr r0, [sp, #0xc]
	add r1, r7, #0
	add r2, r5, #0
	bl FUN_0202630C
	add sp, #0x10
	add r0, r7, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223F166:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223F16C: .word MOD18_022513A0
_0223F170: .word MOD18_02250460
	thumb_func_end MOD18_0223F0C8

	thumb_func_start MOD18_0223F174
MOD18_0223F174: ; 0x0223F174
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _0223F1D8 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r5, r0, #0
	mov r4, #0
_0223F186:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026354
	add r7, r0, #0
	beq _0223F1D0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026370
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_0202639C
	ldr r2, _0223F1D8 ; =0x022513A0
	add r1, r0, #0
	ldr r3, [r2, #4]
	mov r2, #0xd1
	lsl r2, r2, #2
	add r2, r3, r2
	asr r3, r4, #3
	lsr r3, r3, #0x1c
	add r3, r4, r3
	asr r3, r3, #4
	add r3, #8
	add r0, r6, #0
	lsl r6, r3, #4
	mov r3, #6
	mul r3, r6
	add r2, r2, r3
	add r3, r7, #0
	bl MOD18_0223EF0C
	cmp r0, #0
	beq _0223F1D0
	strb r4, [r0, #5]
_0223F1D0:
	add r4, r4, #1
	cmp r4, #0x40
	blt _0223F186
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223F1D8: .word MOD18_022513A0
	thumb_func_end MOD18_0223F174

	thumb_func_start MOD18_0223F1DC
MOD18_0223F1DC: ; 0x0223F1DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	ldr r0, _0223F228 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	mov r4, #0
	add r7, r0, #0
	add r5, r4, #0
_0223F1F4:
	ldr r0, _0223F228 ; =0x022513A0
	mov r1, #0xaa
	ldr r0, [r0, #4]
	mov r3, #0xa9
	add r6, r0, r5
	ldr r0, _0223F22C ; =0x000002A6
	lsl r1, r1, #2
	ldrh r0, [r6, r0]
	lsl r3, r3, #2
	add r2, r4, #0
	str r0, [sp]
	ldr r0, _0223F230 ; =0x000002A9
	ldrb r0, [r6, r0]
	str r0, [sp, #4]
	ldrb r1, [r6, r1]
	ldrh r3, [r6, r3]
	add r0, r7, #0
	bl FUN_020263F4
	add r4, r4, #1
	add r5, r5, #6
	cmp r4, #0x10
	blt _0223F1F4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F228: .word MOD18_022513A0
_0223F22C: .word 0x000002A6
_0223F230: .word 0x000002A9
	thumb_func_end MOD18_0223F1DC

	thumb_func_start MOD18_0223F234
MOD18_0223F234: ; 0x0223F234
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, _0223F2A8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa9
	lsl r0, r0, #2
	add r0, r1, r0
	bl MOD18_0223EE5C
	add r5, r0, #0
	bne _0223F26C
	ldr r0, _0223F2A8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa9
	lsl r0, r0, #2
	add r0, r1, r0
	bl MOD18_02240330
	bl MOD18_0223F2AC
	ldr r0, _0223F2A8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa9
	lsl r0, r0, #2
	add r0, r1, r0
	bl MOD18_0223EE5C
	add r5, r0, #0
_0223F26C:
	ldr r0, _0223F2A8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa9
	lsl r0, r0, #2
	add r0, r1, r0
	bl MOD18_0223EE70
	add r4, r0, #0
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #6
	bl MI_CpuCopy8
	bl MOD18_0223F1DC
	ldrh r0, [r5]
	ldrh r1, [r5, #2]
	ldrb r3, [r5, #4]
	mov r2, #1
	bl MOD18_022402F8
	ldr r1, _0223F2A8 ; =0x022513A0
	ldr r2, [r1, #4]
	lsl r1, r4, #2
	add r2, r2, r1
	mov r1, #0xc1
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r4, r5, r6, pc}
	nop
_0223F2A8: .word MOD18_022513A0
	thumb_func_end MOD18_0223F234

	thumb_func_start MOD18_0223F2AC
MOD18_0223F2AC: ; 0x0223F2AC
	push {r3, r4, r5, r6, r7, lr}
	ldr r2, _0223F358 ; =0x022513A0
	mov r6, #0
	ldr r3, [r2, #4]
	mov r2, #0xa9
	lsl r2, r2, #2
	add r2, r3, r2
	ldrh r3, [r0]
	mvn r6, r6
	mov r1, #0
_0223F2C0:
	ldrh r4, [r2]
	cmp r3, r4
	bne _0223F2D2
	ldrh r5, [r0, #2]
	ldrh r4, [r2, #2]
	cmp r5, r4
	bne _0223F2D2
	add r6, r1, #0
	b _0223F2DA
_0223F2D2:
	add r1, r1, #1
	add r2, r2, #6
	cmp r1, #0x10
	blt _0223F2C0
_0223F2DA:
	mov r0, #0
	mvn r0, r0
	cmp r6, r0
	beq _0223F354
	add r5, r6, #0
	cmp r6, #0xf
	bge _0223F310
	mov r0, #6
	add r4, r6, #0
	ldr r7, _0223F358 ; =0x022513A0
	mul r4, r0
_0223F2F0:
	mov r0, #0xa9
	ldr r1, [r7, #4]
	lsl r0, r0, #2
	add r1, r1, r0
	add r2, r5, #1
	mov r0, #6
	mul r0, r2
	add r0, r1, r0
	add r1, r1, r4
	mov r2, #6
	bl MI_CpuCopy8
	add r5, r5, #1
	add r4, r4, #6
	cmp r5, #0xf
	blt _0223F2F0
_0223F310:
	ldr r1, _0223F358 ; =0x022513A0
	ldr r0, _0223F35C ; =0x00000302
	ldr r2, [r1, #4]
	mov r3, #0
	strb r3, [r2, r0]
	ldr r1, [r1, #4]
	lsl r4, r6, #2
	add r1, r1, r4
	add r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0223F32C
	bl FUN_02064520
_0223F32C:
	cmp r6, #0xf
	bge _0223F348
	mov r0, #0xc2
	lsl r0, r0, #2
	ldr r2, _0223F358 ; =0x022513A0
	sub r1, r0, #4
_0223F338:
	ldr r3, [r2, #4]
	add r6, r6, #1
	add r5, r3, r4
	ldr r3, [r5, r0]
	add r4, r4, #4
	str r3, [r5, r1]
	cmp r6, #0xf
	blt _0223F338
_0223F348:
	ldr r0, _0223F358 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	mov r0, #0xd
	lsl r0, r0, #6
	str r2, [r1, r0]
_0223F354:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F358: .word MOD18_022513A0
_0223F35C: .word 0x00000302
	thumb_func_end MOD18_0223F2AC

	thumb_func_start MOD18_0223F360
MOD18_0223F360: ; 0x0223F360
	push {r4, lr}
	add r4, r2, #0
	bl FUN_02031190
	ldrb r1, [r4, #6]
	cmp r1, r0
	bne _0223F3FA
	bl FUN_0204F7E4
	ldrb r0, [r4, #7]
	cmp r0, #1
	bne _0223F3A4
	add r0, r4, #0
	bl MOD18_0223F234
	ldrb r0, [r4, #4]
	bl MOD18_02249AD8
	bl MOD18_0223D638
	ldrb r1, [r4, #4]
	bl MOD18_0224DDE8
	bl MOD18_0223D638
	ldr r3, _0223F3FC ; =MOD18_0223ECDC
	mov r1, #0x83
	mov r2, #1
	bl MOD18_0224DCB8
	ldr r0, _0223F400 ; =0x00000623
	bl FUN_020054C8
	pop {r4, pc}
_0223F3A4:
	cmp r0, #4
	bne _0223F3B8
	bl MOD18_0223D638
	ldr r3, _0223F3FC ; =MOD18_0223ECDC
	mov r1, #0x49
	mov r2, #1
	bl MOD18_0224DCB8
	pop {r4, pc}
_0223F3B8:
	cmp r0, #5
	bne _0223F3CC
	bl MOD18_0223D638
	ldr r3, _0223F3FC ; =MOD18_0223ECDC
	mov r1, #0x37
	mov r2, #1
	bl MOD18_0224DCB8
	pop {r4, pc}
_0223F3CC:
	cmp r0, #6
	bne _0223F3E0
	bl MOD18_0223D638
	ldr r3, _0223F3FC ; =MOD18_0223ECDC
	mov r1, #0x3c
	mov r2, #1
	bl MOD18_0224DCB8
	pop {r4, pc}
_0223F3E0:
	cmp r0, #7
	bne _0223F3EC
	mov r0, #0
	bl MOD18_0223ECDC
	pop {r4, pc}
_0223F3EC:
	bl MOD18_0223D638
	ldr r3, _0223F3FC ; =MOD18_0223ECDC
	mov r1, #0x3b
	mov r2, #1
	bl MOD18_0224DCB8
_0223F3FA:
	pop {r4, pc}
	.align 2, 0
_0223F3FC: .word MOD18_0223ECDC
_0223F400: .word 0x00000623
	thumb_func_end MOD18_0223F360

	thumb_func_start MOD18_0223F404
MOD18_0223F404: ; 0x0223F404
	ldr r0, _0223F41C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xd1
	lsl r0, r0, #2
	add r3, r1, r0
	ldrh r1, [r2]
	mov r0, #6
	mul r0, r1
	add r0, r3, r0
	ldr r3, _0223F420 ; =MOD18_0223EE8C
	bx r3
	nop
_0223F41C: .word MOD18_022513A0
_0223F420: .word MOD18_0223EE8C
	thumb_func_end MOD18_0223F404

	thumb_func_start MOD18_0223F424
MOD18_0223F424: ; 0x0223F424
	mov r0, #2
	bx lr
	thumb_func_end MOD18_0223F424

	thumb_func_start MOD18_0223F428
MOD18_0223F428: ; 0x0223F428
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	lsl r1, r0, #4
	str r0, [sp]
	mov r0, #6
	add r7, r1, #0
	mul r7, r0
	ldr r0, _0223F4A4 ; =0x022513A0
	add r5, r2, #0
	ldr r1, [r0, #4]
	mov r0, #0xd1
	lsl r0, r0, #2
	add r0, r1, r0
	add r6, r0, r7
	bl FUN_02031190
	cmp r0, #0
	bne _0223F49E
	cmp r4, #0x60
	beq _0223F456
	bl ErrorHandling
_0223F456:
	mov r0, #0
	add r4, r0, #0
_0223F45A:
	add r0, r0, #1
	strb r4, [r6, #4]
	add r6, r6, #6
	cmp r0, #0x10
	blt _0223F45A
_0223F464:
	ldrb r3, [r5, #4]
	cmp r3, #0
	beq _0223F47E
	ldr r2, _0223F4A4 ; =0x022513A0
	ldrh r0, [r5]
	ldr r6, [r2, #4]
	mov r2, #0xd1
	lsl r2, r2, #2
	add r2, r6, r2
	ldrh r1, [r5, #2]
	add r2, r2, r7
	bl MOD18_0223EF0C
_0223F47E:
	add r4, r4, #1
	add r5, r5, #6
	cmp r4, #0x10
	blt _0223F464
	ldr r0, [sp]
	add r1, sp, #4
	strb r0, [r1]
	mov r0, #1
	strb r0, [r1, #1]
	mov r0, #0x24
	add r1, sp, #4
	mov r2, #2
	bl FUN_02030BC4
	bl MOD18_0223FAC4
_0223F49E:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223F4A4: .word MOD18_022513A0
	thumb_func_end MOD18_0223F428

	thumb_func_start MOD18_0223F4A8
MOD18_0223F4A8: ; 0x0223F4A8
	push {r4, lr}
	ldr r0, _0223F4CC ; =0x022513A0
	add r4, r2, #0
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _0223F4C8
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _0223F4C8
	ldr r0, _0223F4CC ; =0x022513A0
	ldrb r2, [r4, #1]
	ldr r1, [r0, #4]
	ldr r0, _0223F4D0 ; =0x00000B45
	strb r2, [r1, r0]
_0223F4C8:
	pop {r4, pc}
	nop
_0223F4CC: .word MOD18_022513A0
_0223F4D0: .word 0x00000B45
	thumb_func_end MOD18_0223F4A8

	thumb_func_start MOD18_0223F4D4
MOD18_0223F4D4: ; 0x0223F4D4
	mov r0, #2
	bx lr
	thumb_func_end MOD18_0223F4D4

	thumb_func_start MOD18_0223F4D8
MOD18_0223F4D8: ; 0x0223F4D8
	ldr r0, _0223F4EC ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _0223F4F0 ; =0x00000B45
	ldrb r0, [r1, r0]
	cmp r0, #1
	bne _0223F4E8
	mov r0, #1
	bx lr
_0223F4E8:
	mov r0, #0
	bx lr
	.align 2, 0
_0223F4EC: .word MOD18_022513A0
_0223F4F0: .word 0x00000B45
	thumb_func_end MOD18_0223F4D8

	thumb_func_start MOD18_0223F4F4
MOD18_0223F4F4: ; 0x0223F4F4
	ldr r0, _0223F500 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _0223F504 ; =0x00000B45
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_0223F500: .word MOD18_022513A0
_0223F504: .word 0x00000B45
	thumb_func_end MOD18_0223F4F4

	thumb_func_start MOD18_0223F508
MOD18_0223F508: ; 0x0223F508
	mov r0, #4
	bx lr
	thumb_func_end MOD18_0223F508

	thumb_func_start MOD18_0223F50C
MOD18_0223F50C: ; 0x0223F50C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	ldr r0, _0223F5C4 ; =0x022513A0
	add r6, r2, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r7, r0, #0
	add r0, r5, #0
	bl FUN_0204E62C
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0204E664
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0223F728
	add r4, r0, #0
	beq _0223F5BE
	add r0, r5, #0
	bl FUN_0204F210
	cmp r0, #0
	beq _0223F54E
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223F54E:
	add r3, sp, #0
	ldrb r2, [r3, #7]
	mov r0, #0xf
	bic r2, r0
	lsl r0, r5, #0x18
	lsr r1, r0, #0x18
	mov r0, #0xf
	and r0, r1
	orr r0, r2
	strb r0, [r3, #7]
	add r0, r4, #0
	bl MOD18_0223F6F8
	add r1, sp, #0
	strb r0, [r1, #6]
	add r0, r4, #0
	add r1, sp, #0
	mov r2, #6
	bl MI_CpuCopy8
	mov r0, #0x10
	tst r0, r6
	add r1, sp, #0
	beq _0223F588
	ldrb r2, [r1, #7]
	mov r0, #0x40
	orr r0, r2
	strb r0, [r1, #7]
	b _0223F596
_0223F588:
	ldrb r2, [r1, #7]
	mov r0, #0x40
	bic r2, r0
	add r0, r4, #0
	strb r2, [r1, #7]
	bl MOD18_0223EE8C
_0223F596:
	add r1, sp, #0
	ldrb r0, [r1, #6]
	cmp r0, #8
	blo _0223F5A6
	ldrb r1, [r1, #5]
	add r0, r7, #0
	bl FUN_020263C8
_0223F5A6:
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	mov r0, #0x33
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223F5BE:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223F5C4: .word MOD18_022513A0
	thumb_func_end MOD18_0223F50C

	thumb_func_start MOD18_0223F5C8
MOD18_0223F5C8: ; 0x0223F5C8
	mov r0, #8
	bx lr
	thumb_func_end MOD18_0223F5C8

	thumb_func_start MOD18_0223F5CC
MOD18_0223F5CC: ; 0x0223F5CC
	push {r3, r4, r5, lr}
	add r4, r2, #0
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r0, #8
	blo _0223F5DE
	bl ErrorHandling
_0223F5DE:
	ldrb r3, [r4, #7]
	lsl r0, r3, #0x19
	lsr r0, r0, #0x1f
	cmp r0, #1
	bne _0223F60A
	bl FUN_02031190
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, r0
	bne _0223F6DC
	bl MOD18_0223D638
	ldr r3, _0223F6E0 ; =MOD18_0223ECDC
	mov r1, #0x4e
	mov r2, #1
	bl MOD18_0224DCB8
	bl FUN_0204F7E4
	pop {r3, r4, r5, pc}
_0223F60A:
	ldr r1, _0223F6E4 ; =0x022513A0
	mov r0, #1
	ldr r2, [r1, #4]
	lsl r1, r3, #0x1c
	lsr r1, r1, #0x1c
	add r2, r2, r1
	ldr r1, _0223F6E8 ; =0x00000B2C
	strb r0, [r2, r1]
	bl FUN_02031190
	ldrb r1, [r4, #6]
	cmp r1, r0
	bne _0223F62E
	add r0, r4, #0
	bl MOD18_0223F2AC
	bl MOD18_0223F1DC
_0223F62E:
	bl FUN_02031190
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, r0
	bne _0223F6DC
	ldrb r0, [r4, #4]
	bl MOD18_022494A0
	cmp r0, #0
	beq _0223F6CA
	bl FUN_02031190
	ldrb r1, [r4, #6]
	cmp r1, r0
	beq _0223F674
	ldr r0, _0223F6E4 ; =0x022513A0
	ldr r2, [r0, #4]
	ldr r0, _0223F6EC ; =0x00000B34
	ldrh r1, [r2, r0]
	cmp r1, #0
	bne _0223F662
	ldrb r1, [r4, #4]
	add r0, r0, #2
	strb r1, [r2, r0]
_0223F662:
	ldr r0, _0223F6E4 ; =0x022513A0
	ldr r1, _0223F6F0 ; =0x0000FFFF
	ldr r3, [r0, #4]
	ldr r0, _0223F6EC ; =0x00000B34
	ldrh r2, [r3, r0]
	cmp r2, r1
	beq _0223F674
	add r1, r2, #1
	strh r1, [r3, r0]
_0223F674:
	ldr r0, _0223F6F4 ; =0x000005E3
	bl FUN_020054C8
	bl MOD18_0223D638
	add r5, r0, #0
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD18_0224DDA0
	bl MOD18_0223D638
	ldrb r2, [r4, #4]
	mov r1, #2
	bl MOD18_0224DF40
	bl MOD18_0223D638
	mov r1, #2
	bl MOD18_0224DF54
	bl MOD18_0223D638
	ldrb r1, [r4, #4]
	bl MOD18_0224DDE8
	bl MOD18_0223D638
	ldr r3, _0223F6E0 ; =MOD18_0223ECDC
	mov r1, #0x12
	mov r2, #1
	bl MOD18_0224DCB8
	bl MOD18_0223D638
	bl MOD18_0224DD10
	b _0223F6D8
_0223F6CA:
	bl MOD18_0223D638
	ldr r3, _0223F6E0 ; =MOD18_0223ECDC
	mov r1, #0x4e
	mov r2, #1
	bl MOD18_0224DCB8
_0223F6D8:
	bl FUN_0204F7E4
_0223F6DC:
	pop {r3, r4, r5, pc}
	nop
_0223F6E0: .word MOD18_0223ECDC
_0223F6E4: .word MOD18_022513A0
_0223F6E8: .word 0x00000B2C
_0223F6EC: .word 0x00000B34
_0223F6F0: .word 0x0000FFFF
_0223F6F4: .word 0x000005E3
	thumb_func_end MOD18_0223F5CC

	thumb_func_start MOD18_0223F6F8
MOD18_0223F6F8: ; 0x0223F6F8
	push {r3, lr}
	ldr r1, _0223F724 ; =0x022513A0
	mov r3, #0
	ldr r2, [r1, #4]
	mov r1, #0xd1
	lsl r1, r1, #2
	add r1, r2, r1
_0223F706:
	cmp r1, r0
	bne _0223F714
	asr r0, r3, #3
	lsr r0, r0, #0x1c
	add r0, r3, r0
	asr r0, r0, #4
	pop {r3, pc}
_0223F714:
	add r3, r3, #1
	add r1, r1, #6
	cmp r3, #0xc0
	blt _0223F706
	bl ErrorHandling
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_0223F724: .word MOD18_022513A0
	thumb_func_end MOD18_0223F6F8

	thumb_func_start MOD18_0223F728
MOD18_0223F728: ; 0x0223F728
	push {r3, lr}
	add r2, sp, #0
	strh r0, [r2]
	strh r1, [r2, #2]
	ldr r1, _0223F758 ; =MOD18_0223ECF0
	mov r0, #0xc0
	bl MOD18_0223DC7C
	add r0, sp, #0
	bl MOD18_0223DBBC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0223F74A
	mov r0, #0
	pop {r3, pc}
_0223F74A:
	ldr r1, _0223F75C ; =0x022513A0
	lsl r0, r0, #2
	ldr r1, [r1, #4]
	add r1, r1, r0
	ldr r0, _0223F760 ; =0x000007C4
	ldr r0, [r1, r0]
	pop {r3, pc}
	.align 2, 0
_0223F758: .word MOD18_0223ECF0
_0223F75C: .word MOD18_022513A0
_0223F760: .word 0x000007C4
	thumb_func_end MOD18_0223F728

	thumb_func_start MOD18_0223F764
MOD18_0223F764: ; 0x0223F764
	push {r3, lr}
	bl MOD18_0223F728
	cmp r0, #0
	beq _0223F772
	mov r0, #1
	pop {r3, pc}
_0223F772:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0223F764

	thumb_func_start MOD18_0223F778
MOD18_0223F778: ; 0x0223F778
	mov r0, #8
	bx lr
	thumb_func_end MOD18_0223F778

	thumb_func_start MOD18_0223F77C
MOD18_0223F77C: ; 0x0223F77C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _0223F850 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r6, r0, #0
	add r0, r4, #0
	bl MOD18_0223CAEC
	cmp r0, #0
	beq _0223F7A0
	add sp, #8
	mov r0, #0
	pop {r4, r5, r6, pc}
_0223F7A0:
	add r0, r4, #0
	bl FUN_0204E544
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204E598
	add r1, r0, #0
	add r0, r5, #0
	bl MOD18_0223F728
	add r5, r0, #0
	bne _0223F7C0
	add sp, #8
	mov r0, #0
	pop {r4, r5, r6, pc}
_0223F7C0:
	ldr r0, _0223F850 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r4
	ldr r0, _0223F854 ; =0x00000B3C
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _0223F7E4
	add r0, r4, #0
	bl FUN_0204E778
	ldr r1, _0223F850 ; =0x022513A0
	add r0, r4, #0
	ldr r1, [r1, #4]
	add r2, r1, r4
	ldr r1, _0223F854 ; =0x00000B3C
	ldrb r1, [r2, r1]
	bl MOD18_0223FCD4
_0223F7E4:
	ldrb r1, [r5, #4]
	add r0, r4, #0
	bl MOD18_0223FCC0
	add r0, sp, #0
	ldrb r2, [r0, #7]
	mov r1, #0x80
	bic r2, r1
	strb r2, [r0, #7]
	ldrb r1, [r0, #7]
	mov r2, #0xf
	bic r1, r2
	lsl r2, r4, #0x18
	lsr r3, r2, #0x18
	mov r2, #0xf
	and r2, r3
	orr r1, r2
	strb r1, [r0, #7]
	add r0, r5, #0
	bl MOD18_0223F6F8
	add r1, sp, #0
	strb r0, [r1, #6]
	add r0, r5, #0
	add r1, sp, #0
	mov r2, #6
	bl MI_CpuCopy8
	add r1, sp, #0
	ldrb r0, [r1, #6]
	cmp r0, #8
	blo _0223F82C
	ldrb r1, [r1, #5]
	add r0, r6, #0
	bl FUN_020263C8
_0223F82C:
	mov r0, #0x25
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	ldr r0, _0223F850 ; =0x022513A0
	ldrb r2, [r5, #4]
	ldr r0, [r0, #4]
	add r1, r0, r4
	ldr r0, _0223F854 ; =0x00000B3C
	strb r2, [r1, r0]
	add r0, r5, #0
	bl MOD18_0223EE8C
	mov r0, #1
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_0223F850: .word MOD18_022513A0
_0223F854: .word 0x00000B3C
	thumb_func_end MOD18_0223F77C

	thumb_func_start MOD18_0223F858
MOD18_0223F858: ; 0x0223F858
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r1, #0
	ldr r1, _0223F8D0 ; =0x022513A0
	add r5, r0, #0
	ldr r1, [r1, #4]
	add r4, r2, #0
	add r2, r1, r5
	ldr r1, _0223F8D4 ; =0x00000B3C
	add r7, r3, #0
	ldrb r1, [r2, r1]
	cmp r1, #0
	beq _0223F876
	bl MOD18_0223FCD4
_0223F876:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0223FCC0
	add r1, sp, #0
	ldrb r3, [r1, #7]
	mov r0, #0xf
	bic r3, r0
	lsl r0, r5, #0x18
	lsr r2, r0, #0x18
	mov r0, #0xf
	and r0, r2
	orr r0, r3
	strb r0, [r1, #7]
	strb r6, [r1, #6]
	ldrb r2, [r1, #7]
	mov r0, #0x80
	orr r0, r2
	strb r0, [r1, #7]
	strb r4, [r1, #4]
	ldr r0, [sp, #0x20]
	strh r7, [r1]
	strh r0, [r1, #2]
	ldrb r0, [r1, #7]
	mov r2, #0x30
	bic r0, r2
	ldr r2, [sp, #0x24]
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1a
	orr r0, r2
	strb r0, [r1, #7]
	mov r0, #0x25
	add r1, sp, #0
	mov r2, #8
	bl FUN_02030BC4
	ldr r0, _0223F8D0 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r5
	ldr r0, _0223F8D4 ; =0x00000B3C
	strb r4, [r1, r0]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223F8D0: .word MOD18_022513A0
_0223F8D4: .word 0x00000B3C
	thumb_func_end MOD18_0223F858

	thumb_func_start MOD18_0223F8D8
MOD18_0223F8D8: ; 0x0223F8D8
	push {r4, lr}
	ldr r1, _0223F8F8 ; =0x022513A0
	add r4, r0, #0
	ldr r1, [r1, #4]
	cmp r1, #0
	beq _0223F8F4
	bl FUN_0204EB14
	cmp r0, #0
	beq _0223F8F4
	add r0, r4, #0
	bl MOD18_0223F77C
	pop {r4, pc}
_0223F8F4:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_0223F8F8: .word MOD18_022513A0
	thumb_func_end MOD18_0223F8D8

	thumb_func_start MOD18_0223F8FC
MOD18_0223F8FC: ; 0x0223F8FC
	ldr r1, _0223F910 ; =0x022513A0
	lsl r0, r0, #3
	ldr r1, [r1, #4]
	add r1, r1, r0
	ldr r0, _0223F914 ; =0x00000ACB
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr
	nop
_0223F910: .word MOD18_022513A0
_0223F914: .word 0x00000ACB
	thumb_func_end MOD18_0223F8FC

	thumb_func_start MOD18_0223F918
MOD18_0223F918: ; 0x0223F918
	push {r4, r5, r6, lr}
	ldr r0, _0223FA60 ; =0x022513A0
	add r4, r2, #0
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _0223F926
	b _0223FA5E
_0223F926:
	ldr r0, [r0, #0x40]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	add r6, r0, #0
	ldr r0, _0223FA64 ; =0x00000622
	bl FUN_020054C8
	ldr r1, _0223FA60 ; =0x022513A0
	add r0, r4, #0
	ldr r2, [r1, #4]
	ldr r1, _0223FA68 ; =0x00000AC4
	add r1, r2, r1
	ldrb r2, [r4, #7]
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x19
	add r1, r1, r2
	mov r2, #8
	bl MI_CpuCopy8
	ldrb r0, [r4, #4]
	sub r0, #0x18
	cmp r0, #3
	bhi _0223F9BC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0223F964: ; jump table
	.short _0223F96C - _0223F964 - 2 ; case 0
	.short _0223F980 - _0223F964 - 2 ; case 1
	.short _0223F994 - _0223F964 - 2 ; case 2
	.short _0223F9A8 - _0223F964 - 2 ; case 3
_0223F96C:
	ldr r1, _0223FA60 ; =0x022513A0
	mov r0, #0x75
	ldr r2, [r1, #4]
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r2, r2, r1
	ldr r1, _0223FA6C ; =0x00000B24
	strb r0, [r2, r1]
	b _0223F9D2
_0223F980:
	ldr r1, _0223FA60 ; =0x022513A0
	mov r0, #0x76
	ldr r2, [r1, #4]
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r2, r2, r1
	ldr r1, _0223FA6C ; =0x00000B24
	strb r0, [r2, r1]
	b _0223F9D2
_0223F994:
	ldr r1, _0223FA60 ; =0x022513A0
	mov r0, #0x77
	ldr r2, [r1, #4]
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r2, r2, r1
	ldr r1, _0223FA6C ; =0x00000B24
	strb r0, [r2, r1]
	b _0223F9D2
_0223F9A8:
	ldr r1, _0223FA60 ; =0x022513A0
	mov r0, #0x78
	ldr r2, [r1, #4]
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r2, r2, r1
	ldr r1, _0223FA6C ; =0x00000B24
	strb r0, [r2, r1]
	b _0223F9D2
_0223F9BC:
	ldr r0, _0223FA60 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _0223FA70 ; =0x00000ACB
	add r0, r1, r0
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r3, r1, #0x19
	ldrb r2, [r0, r3]
	mov r1, #0x40
	orr r1, r2
	strb r1, [r0, r3]
_0223F9D2:
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r5, r0, #0x1c
	bl FUN_02031190
	cmp r5, r0
	bne _0223F9F4
	ldrb r3, [r4, #7]
	ldrb r1, [r4, #4]
	add r0, r5, #0
	lsl r2, r3, #0x18
	lsl r3, r3, #0x1a
	lsr r2, r2, #0x1f
	lsr r3, r3, #0x1e
	bl MOD18_0223FD54
	b _0223F9FC
_0223F9F4:
	ldrb r1, [r4, #4]
	add r0, r5, #0
	bl MOD18_02243F5C
_0223F9FC:
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bl FUN_0204F074
	bl FUN_02031190
	ldrb r1, [r4, #7]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	cmp r1, r0
	bne _0223FA1A
	add r0, r6, #0
	bl FUN_02026B20
_0223FA1A:
	ldrb r5, [r4, #6]
	bl FUN_02031190
	cmp r5, r0
	bne _0223FA5E
	ldrb r0, [r4, #7]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	cmp r5, r0
	beq _0223FA34
	add r0, r6, #0
	bl FUN_02026AE8
_0223FA34:
	ldr r0, _0223FA60 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r5, r0, #0
	bl FUN_0205F760
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x10
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl FUN_0205F770
	add r0, r4, #0
	bl MOD18_0223F2AC
	bl MOD18_0223F1DC
_0223FA5E:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0223FA60: .word MOD18_022513A0
_0223FA64: .word 0x00000622
_0223FA68: .word 0x00000AC4
_0223FA6C: .word 0x00000B24
_0223FA70: .word 0x00000ACB
	thumb_func_end MOD18_0223F918

	thumb_func_start MOD18_0223FA74
MOD18_0223FA74: ; 0x0223FA74
	push {r4, lr}
	ldrb r2, [r2]
	ldr r1, _0223FA9C ; =0x02250230
	lsl r3, r2, #2
	ldr r1, [r1, r3]
	ldr r3, _0223FAA0 ; =0x022513A0
	ldr r3, [r3, #4]
	add r4, r3, r0
	ldr r3, _0223FAA4 ; =0x00000B3C
	ldrb r3, [r4, r3]
	cmp r2, r3
	beq _0223FA94
	mov r0, #1
	bl FUN_020335A4
	pop {r4, pc}
_0223FA94:
	cmp r1, #0
	beq _0223FA9A
	blx r1
_0223FA9A:
	pop {r4, pc}
	.align 2, 0
_0223FA9C: .word MOD18_02250230
_0223FAA0: .word MOD18_022513A0
_0223FAA4: .word 0x00000B3C
	thumb_func_end MOD18_0223FA74

	thumb_func_start MOD18_0223FAA8
MOD18_0223FAA8: ; 0x0223FAA8
	push {r3, r4, r5, lr}
	add r5, r2, #0
	ldrb r4, [r5]
	bl FUN_02031190
	cmp r4, r0
	beq _0223FAC0
	ldrb r1, [r5, #1]
	ldrb r2, [r5, #2]
	add r0, r4, #0
	bl FUN_0204E214
_0223FAC0:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0223FAA8

	thumb_func_start MOD18_0223FAC4
MOD18_0223FAC4: ; 0x0223FAC4
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	mov r0, #0
	add r3, sp, #0
	ldr r1, _0223FB00 ; =0x022513A0
	strb r0, [r3]
	ldr r1, [r1, #4]
	cmp r1, #0
	beq _0223FAFA
	ldr r2, _0223FB04 ; =0x00000B3C
	mov r4, #1
_0223FADA:
	ldrb r5, [r1, r2]
	cmp r5, #0
	beq _0223FAEA
	add r5, r4, #0
	ldrb r6, [r3]
	lsl r5, r0
	orr r5, r6
	strb r5, [r3]
_0223FAEA:
	add r0, r0, #1
	add r1, r1, #1
	cmp r0, #8
	blt _0223FADA
	mov r0, #0x2d
	add r1, sp, #0
	bl FUN_02030C4C
_0223FAFA:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0223FB00: .word MOD18_022513A0
_0223FB04: .word 0x00000B3C
	thumb_func_end MOD18_0223FAC4

	thumb_func_start MOD18_0223FB08
MOD18_0223FB08: ; 0x0223FB08
	push {r4, r5, r6, lr}
	ldr r0, _0223FB34 ; =0x022513A0
	ldrb r5, [r2]
	ldr r1, [r0, #4]
	ldr r0, _0223FB38 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0223FB30
	mov r4, #0
	mov r6, #1
_0223FB1C:
	add r0, r6, #0
	lsl r0, r4
	tst r0, r5
	beq _0223FB2A
	add r0, r4, #0
	bl FUN_0204F074
_0223FB2A:
	add r4, r4, #1
	cmp r4, #8
	blt _0223FB1C
_0223FB30:
	pop {r4, r5, r6, pc}
	nop
_0223FB34: .word MOD18_022513A0
_0223FB38: .word 0x00000B3B
	thumb_func_end MOD18_0223FB08

	thumb_func_start MOD18_0223FB3C
MOD18_0223FB3C: ; 0x0223FB3C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r7, _0223FC04 ; =0x022513A0
	add r6, r0, #0
	ldr r0, [r7, #4]
	cmp r0, #0
	bne _0223FB50
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0223FB50:
	mov r4, #0
	mov r0, #0x40
	add r5, r4, #0
	str r0, [sp, #8]
_0223FB58:
	ldr r1, [r7, #4]
	ldr r0, _0223FC08 ; =0x00000ACB
	add r0, r1, r0
	ldrb r2, [r0, r5]
	lsl r1, r2, #0x19
	lsr r1, r1, #0x1f
	cmp r1, #1
	bne _0223FBB4
	ldr r1, [sp, #8]
	bic r2, r1
	strb r2, [r0, r5]
	ldr r0, [r7, #4]
	add r1, r0, r5
	ldr r0, _0223FC0C ; =0x00000ACA
	ldrb r0, [r1, r0]
	cmp r0, #8
	blo _0223FB94
	add r0, r4, #0
	bl FUN_0202DFA4
	mov r1, #0
	mov r2, #0x63
	add r3, r6, #0
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223FBB4
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223FB94:
	bl FUN_0202DFA4
	str r0, [sp]
	add r0, r4, #0
	bl FUN_0202DFA4
	ldr r1, [sp]
	mov r2, #0x64
	add r3, r6, #0
	bl MOD18_0223D6D8
	cmp r0, #0
	beq _0223FBB4
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223FBB4:
	ldr r0, [r7, #4]
	add r1, r0, r4
	ldr r0, _0223FC10 ; =0x00000B04
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _0223FBF6
	add r0, r4, #0
	bl FUN_0202DFA4
	str r0, [sp, #4]
	ldr r0, [r7, #4]
	add r1, r0, r4
	ldr r0, _0223FC10 ; =0x00000B04
	ldrb r0, [r1, r0]
	bl FUN_0202DFA4
	add r3, r0, #0
	ldr r0, [r7, #4]
	mov r1, #0xff
	add r2, r0, r4
	ldr r0, _0223FC10 ; =0x00000B04
	strb r1, [r2, r0]
	add r1, r3, #0
	ldr r0, [sp, #4]
	mov r2, #0x74
	add r3, r6, #0
	bl MOD18_0223D6D8
	cmp r0, #0
	beq _0223FBF6
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0223FBF6:
	add r4, r4, #1
	add r5, #8
	cmp r4, #8
	blt _0223FB58
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0223FC04: .word MOD18_022513A0
_0223FC08: .word 0x00000ACB
_0223FC0C: .word 0x00000ACA
_0223FC10: .word 0x00000B04
	thumb_func_end MOD18_0223FB3C

	thumb_func_start MOD18_0223FC14
MOD18_0223FC14: ; 0x0223FC14
	push {r3, r4, r5, r6, r7, lr}
	ldr r6, _0223FCB0 ; =0x022513A0
	add r5, r0, #0
	ldr r0, [r6, #4]
	cmp r0, #0
	bne _0223FC24
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0223FC24:
	mov r4, #0
_0223FC26:
	ldr r0, [r6, #4]
	ldr r1, _0223FCB4 ; =0x00000B24
	add r0, r0, r4
	ldrb r7, [r0, r1]
	cmp r7, #0
	beq _0223FC4E
	mov r2, #0
	strb r2, [r0, r1]
	add r0, r4, #0
	bl FUN_0202DFA4
	mov r1, #0
	add r2, r7, #0
	add r3, r5, #0
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223FC4E
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223FC4E:
	ldr r0, [r6, #4]
	ldr r1, _0223FCB8 ; =0x00000B2C
	add r0, r0, r4
	ldrb r1, [r0, r1]
	cmp r1, #1
	bne _0223FC78
	ldr r1, _0223FCB8 ; =0x00000B2C
	mov r2, #0
	strb r2, [r0, r1]
	add r0, r4, #0
	bl FUN_0202DFA4
	mov r1, #0
	mov r2, #0x5a
	add r3, r5, #0
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223FC78
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223FC78:
	ldr r0, [r6, #4]
	add r1, r0, r4
	ldr r0, _0223FCBC ; =0x00000B1C
	ldrb r0, [r1, r0]
	cmp r0, #1
	bne _0223FCA6
	add r0, r4, #0
	bl FUN_0202DFA4
	ldr r1, [r6, #4]
	mov r2, #0
	add r3, r1, r4
	ldr r1, _0223FCBC ; =0x00000B1C
	strb r2, [r3, r1]
	add r1, r2, #0
	mov r2, #0x62
	add r3, r5, #0
	bl MOD18_0223D744
	cmp r0, #0
	beq _0223FCA6
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223FCA6:
	add r4, r4, #1
	cmp r4, #8
	blt _0223FC26
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223FCB0: .word MOD18_022513A0
_0223FCB4: .word 0x00000B24
_0223FCB8: .word 0x00000B2C
_0223FCBC: .word 0x00000B1C
	thumb_func_end MOD18_0223FC14

	thumb_func_start MOD18_0223FCC0
MOD18_0223FCC0: ; 0x0223FCC0
	push {r3, lr}
	lsl r2, r1, #2
	ldr r1, _0223FCD0 ; =0x022501A4
	ldr r1, [r1, r2]
	cmp r1, #0
	beq _0223FCCE
	blx r1
_0223FCCE:
	pop {r3, pc}
	.align 2, 0
_0223FCD0: .word MOD18_022501A4
	thumb_func_end MOD18_0223FCC0

	thumb_func_start MOD18_0223FCD4
MOD18_0223FCD4: ; 0x0223FCD4
	push {r3, lr}
	lsl r2, r1, #2
	ldr r1, _0223FCE4 ; =0x022502BC
	ldr r1, [r1, r2]
	cmp r1, #0
	beq _0223FCE2
	blx r1
_0223FCE2:
	pop {r3, pc}
	.align 2, 0
_0223FCE4: .word MOD18_022502BC
	thumb_func_end MOD18_0223FCD4

	thumb_func_start MOD18_0223FCE8
MOD18_0223FCE8: ; 0x0223FCE8
	push {r4, lr}
	ldr r2, _0223FD44 ; =0x022513A0
	add r4, r0, #0
	ldr r3, [r2, #4]
	ldr r2, _0223FD48 ; =0x00000B3B
	ldrb r2, [r3, r2]
	cmp r2, #0
	beq _0223FD42
	lsl r3, r2, #2
	ldr r2, _0223FD4C ; =0x022503D4
	ldr r2, [r2, r3]
	cmp r2, #0
	beq _0223FD04
	blx r2
_0223FD04:
	bl FUN_02031190
	cmp r0, #0
	beq _0223FD12
	add r0, r4, #0
	bl FUN_0204E778
_0223FD12:
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _0223FD50 ; =0x00000609
	bl FUN_020054C8
	ldr r0, _0223FD44 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	mov r0, #0x2a
	lsl r0, r0, #4
	str r2, [r1, r0]
	add r0, r4, #0
	bl FUN_0204F0A8
	bl MOD18_0223D638
	bl MOD18_0224DD94
	ldr r0, _0223FD44 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _0223FD48 ; =0x00000B3B
	strb r2, [r1, r0]
_0223FD42:
	pop {r4, pc}
	.align 2, 0
_0223FD44: .word MOD18_022513A0
_0223FD48: .word 0x00000B3B
_0223FD4C: .word MOD18_022503D4
_0223FD50: .word 0x00000609
	thumb_func_end MOD18_0223FCE8

	thumb_func_start MOD18_0223FD54
MOD18_0223FD54: ; 0x0223FD54
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #1
	add r5, r0, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD18_0223FCE8
	ldr r0, _0223FD80 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _0223FD84 ; =0x00000B3B
	strb r4, [r1, r0]
	ldr r0, _0223FD88 ; =0x02250118
	lsl r1, r4, #2
	ldr r3, [r0, r1]
	cmp r3, #0
	beq _0223FD7E
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	blx r3
_0223FD7E:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0223FD80: .word MOD18_022513A0
_0223FD84: .word 0x00000B3B
_0223FD88: .word MOD18_02250118
	thumb_func_end MOD18_0223FD54

	thumb_func_start MOD18_0223FD8C
MOD18_0223FD8C: ; 0x0223FD8C
	push {r3, r4, r5, r6, r7, lr}
	bl FUN_0204F610
	add r6, r0, #0
	ldr r0, _0223FDE0 ; =0x022513A0
	add r1, r6, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055304
	bl FUN_02031190
	ldr r1, _0223FDE0 ; =0x022513A0
	lsl r0, r0, #3
	ldr r1, [r1, #4]
	add r1, r1, r0
	ldr r0, _0223FDE4 ; =0x00000AC4
	ldrh r4, [r1, r0]
	bl FUN_02031190
	ldr r1, _0223FDE0 ; =0x022513A0
	lsl r0, r0, #3
	ldr r1, [r1, #4]
	add r1, r1, r0
	ldr r0, _0223FDE8 ; =0x00000AC6
	ldrh r5, [r1, r0]
	add r0, r6, #0
	bl FUN_02059BF4
	add r7, r0, #0
	add r0, r6, #0
	bl FUN_02059C00
	add r2, r0, #0
	mov r0, #0
	add r1, r4, r7
	add r2, r5, r2
	bl FUN_0204D118
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223FDE0: .word MOD18_022513A0
_0223FDE4: .word 0x00000AC4
_0223FDE8: .word 0x00000AC6
	thumb_func_end MOD18_0223FD8C

	thumb_func_start MOD18_0223FDEC
MOD18_0223FDEC: ; 0x0223FDEC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, _0223FE64 ; =0x022513A0
	add r6, r1, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	str r0, [sp]
	ldr r0, _0223FE64 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r7, r0, #0
	add r0, r4, #0
	bl FUN_0204F610
	str r0, [sp, #4]
	bl FUN_02031190
	ldr r1, _0223FE64 ; =0x022513A0
	lsl r0, r0, #3
	ldr r1, [r1, #4]
	add r1, r1, r0
	ldr r0, _0223FE68 ; =0x00000AC4
	ldrh r4, [r1, r0]
	bl FUN_02031190
	ldr r1, _0223FE64 ; =0x022513A0
	lsl r0, r0, #3
	ldr r1, [r1, #4]
	add r1, r1, r0
	ldr r0, _0223FE6C ; =0x00000AC6
	cmp r6, #0
	ldrh r5, [r1, r0]
	bne _0223FE4C
	ldr r0, [sp, #4]
	bl FUN_02059BF4
	add r4, r4, r0
	ldr r0, [sp, #4]
	bl FUN_02059C00
	add r5, r5, r0
_0223FE4C:
	ldr r0, [sp]
	cmp r0, r4
	bne _0223FE5C
	cmp r7, r5
	bne _0223FE5C
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0223FE5C:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0223FE64: .word MOD18_022513A0
_0223FE68: .word 0x00000AC4
_0223FE6C: .word 0x00000AC6
	thumb_func_end MOD18_0223FDEC

	thumb_func_start MOD18_0223FE70
MOD18_0223FE70: ; 0x0223FE70
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	bl FUN_0204E758
	add r0, r4, #0
	mov r1, #0x1e
	bl FUN_0204F63C
	pop {r4, pc}
	thumb_func_end MOD18_0223FE70

	thumb_func_start MOD18_0223FE84
MOD18_0223FE84: ; 0x0223FE84
	push {r4, lr}
	add r4, r0, #0
	mov r1, #1
	bl FUN_0204E758
	add r0, r4, #0
	mov r1, #0x1e
	bl FUN_0204F63C
	pop {r4, pc}
	thumb_func_end MOD18_0223FE84

	thumb_func_start MOD18_0223FE98
MOD18_0223FE98: ; 0x0223FE98
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl FUN_0204E758
	add r0, r4, #0
	bl FUN_0204F660
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0223FE98

	thumb_func_start MOD18_0223FEAC
MOD18_0223FEAC: ; 0x0223FEAC
	ldr r3, _0223FEB4 ; =FUN_0204E758
	mov r1, #2
	bx r3
	nop
_0223FEB4: .word FUN_0204E758
	thumb_func_end MOD18_0223FEAC

	thumb_func_start MOD18_0223FEB8
MOD18_0223FEB8: ; 0x0223FEB8
	ldr r3, _0223FEC0 ; =FUN_0204E758
	mov r1, #2
	bx r3
	nop
_0223FEC0: .word FUN_0204E758
	thumb_func_end MOD18_0223FEB8

	thumb_func_start MOD18_0223FEC4
MOD18_0223FEC4: ; 0x0223FEC4
	push {r4, lr}
	add r4, r0, #0
	mov r1, #3
	bl FUN_0204E758
	add r0, r4, #0
	bl FUN_0204E200
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0223FEC4

	thumb_func_start MOD18_0223FED8
MOD18_0223FED8: ; 0x0223FED8
	ldr r3, _0223FEE0 ; =FUN_0204E178
	mov r1, #0
	add r2, r1, #0
	bx r3
	.align 2, 0
_0223FEE0: .word FUN_0204E178
	thumb_func_end MOD18_0223FED8

	thumb_func_start MOD18_0223FEE4
MOD18_0223FEE4: ; 0x0223FEE4
	ldr r3, _0223FEEC ; =FUN_0204E178
	mov r1, #1
	mov r2, #0
	bx r3
	.align 2, 0
_0223FEEC: .word FUN_0204E178
	thumb_func_end MOD18_0223FEE4

	thumb_func_start MOD18_0223FEF0
MOD18_0223FEF0: ; 0x0223FEF0
	ldr r3, _0223FEF8 ; =FUN_0204E178
	mov r1, #2
	mov r2, #0
	bx r3
	.align 2, 0
_0223FEF8: .word FUN_0204E178
	thumb_func_end MOD18_0223FEF0

	thumb_func_start MOD18_0223FEFC
MOD18_0223FEFC: ; 0x0223FEFC
	ldr r3, _0223FF04 ; =FUN_0204E178
	mov r1, #3
	mov r2, #0
	bx r3
	.align 2, 0
_0223FF04: .word FUN_0204E178
	thumb_func_end MOD18_0223FEFC

	thumb_func_start MOD18_0223FF08
MOD18_0223FF08: ; 0x0223FF08
	ldr r3, _0223FF10 ; =FUN_0204E178
	mov r1, #0
	mov r2, #1
	bx r3
	.align 2, 0
_0223FF10: .word FUN_0204E178
	thumb_func_end MOD18_0223FF08

	thumb_func_start MOD18_0223FF14
MOD18_0223FF14: ; 0x0223FF14
	ldr r3, _0223FF1C ; =FUN_0204E178
	mov r1, #1
	add r2, r1, #0
	bx r3
	.align 2, 0
_0223FF1C: .word FUN_0204E178
	thumb_func_end MOD18_0223FF14

	thumb_func_start MOD18_0223FF20
MOD18_0223FF20: ; 0x0223FF20
	ldr r3, _0223FF28 ; =FUN_0204E178
	mov r1, #2
	mov r2, #1
	bx r3
	.align 2, 0
_0223FF28: .word FUN_0204E178
	thumb_func_end MOD18_0223FF20

	thumb_func_start MOD18_0223FF2C
MOD18_0223FF2C: ; 0x0223FF2C
	ldr r3, _0223FF34 ; =FUN_0204E178
	mov r1, #3
	mov r2, #1
	bx r3
	.align 2, 0
_0223FF34: .word FUN_0204E178
	thumb_func_end MOD18_0223FF2C

	thumb_func_start MOD18_0223FF38
MOD18_0223FF38: ; 0x0223FF38
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0
	bl FUN_0204E758
	add r0, r4, #0
	bl FUN_0204E1E8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0223FF38

	thumb_func_start MOD18_0223FF4C
MOD18_0223FF4C: ; 0x0223FF4C
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0223FF4C

	thumb_func_start MOD18_0223FF50
MOD18_0223FF50: ; 0x0223FF50
	push {r4, lr}
	mov r1, #1
	add r4, r0, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r4, r0
	bne _0223FF68
	mov r0, #1
	bl MOD18_02240EE8
_0223FF68:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0223FF50

	thumb_func_start MOD18_0223FF6C
MOD18_0223FF6C: ; 0x0223FF6C
	push {r4, lr}
	mov r1, #1
	add r4, r0, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r4, r0
	bne _0223FF84
	mov r0, #0
	bl MOD18_02240EE8
_0223FF84:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0223FF6C

	thumb_func_start MOD18_0223FF88
MOD18_0223FF88: ; 0x0223FF88
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _0223FFAC
	ldr r0, _0223FFB0 ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	add r2, r6, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02240334
_0223FFAC:
	pop {r4, r5, r6, pc}
	nop
_0223FFB0: .word MOD18_022513A0
	thumb_func_end MOD18_0223FF88

	thumb_func_start MOD18_0223FFB4
MOD18_0223FFB4: ; 0x0223FFB4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _0223FFD8
	ldr r0, _0223FFDC ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	add r2, r6, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02241738
_0223FFD8:
	pop {r4, r5, r6, pc}
	nop
_0223FFDC: .word MOD18_022513A0
	thumb_func_end MOD18_0223FFB4

	thumb_func_start MOD18_0223FFE0
MOD18_0223FFE0: ; 0x0223FFE0
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _0223FFF4 ; =0x022513A0
	mov r2, #0
	ldr r0, [r0, #4]
	add r3, r2, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_0223FFF4: .word MOD18_022513A0
	thumb_func_end MOD18_0223FFE0

	thumb_func_start MOD18_0223FFF8
MOD18_0223FFF8: ; 0x0223FFF8
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _0224000C ; =0x022513A0
	mov r2, #1
	ldr r0, [r0, #4]
	mov r3, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_0224000C: .word MOD18_022513A0
	thumb_func_end MOD18_0223FFF8

	thumb_func_start MOD18_02240010
MOD18_02240010: ; 0x02240010
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _02240024 ; =0x022513A0
	mov r2, #2
	ldr r0, [r0, #4]
	mov r3, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_02240024: .word MOD18_022513A0
	thumb_func_end MOD18_02240010

	thumb_func_start MOD18_02240028
MOD18_02240028: ; 0x02240028
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _0224003C ; =0x022513A0
	mov r2, #3
	ldr r0, [r0, #4]
	mov r3, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_0224003C: .word MOD18_022513A0
	thumb_func_end MOD18_02240028

	thumb_func_start MOD18_02240040
MOD18_02240040: ; 0x02240040
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _02240054 ; =0x022513A0
	mov r2, #0
	ldr r0, [r0, #4]
	mov r3, #1
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_02240054: .word MOD18_022513A0
	thumb_func_end MOD18_02240040

	thumb_func_start MOD18_02240058
MOD18_02240058: ; 0x02240058
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _0224006C ; =0x022513A0
	mov r2, #1
	ldr r0, [r0, #4]
	add r3, r2, #0
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_0224006C: .word MOD18_022513A0
	thumb_func_end MOD18_02240058

	thumb_func_start MOD18_02240070
MOD18_02240070: ; 0x02240070
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _02240084 ; =0x022513A0
	mov r2, #2
	ldr r0, [r0, #4]
	mov r3, #1
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_02240084: .word MOD18_022513A0
	thumb_func_end MOD18_02240070

	thumb_func_start MOD18_02240088
MOD18_02240088: ; 0x02240088
	push {r3, lr}
	add r1, r0, #0
	ldr r0, _0224009C ; =0x022513A0
	mov r2, #3
	ldr r0, [r0, #4]
	mov r3, #1
	ldr r0, [r0, #0x40]
	bl MOD18_02240210
	pop {r3, pc}
	.align 2, 0
_0224009C: .word MOD18_022513A0
	thumb_func_end MOD18_02240088

	thumb_func_start MOD18_022400A0
MOD18_022400A0: ; 0x022400A0
	push {r4, lr}
	ldr r0, _022400F8 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	add r4, r0, #0
	ldr r0, _022400F8 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r3, r0, #0
	ldr r0, _022400F8 ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	mov r2, #0
	ldr r0, [r0, #0x40]
	bl MOD05_021E5B30
	bl MOD18_0223D638
	ldr r2, _022400F8 ; =0x022513A0
	mov r1, #0
	ldr r3, [r2, #4]
	ldr r2, _022400FC ; =0x00000B3B
	ldrb r2, [r3, r2]
	bl MOD18_0224DF04
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x46
	add r3, r2, #0
	bl MOD18_0224DCD8
	add r4, r0, #0
	mov r0, #0x10
	bl FUN_0204F74C
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0
_022400F8: .word MOD18_022513A0
_022400FC: .word 0x00000B3B
	thumb_func_end MOD18_022400A0

	thumb_func_start MOD18_02240100
MOD18_02240100: ; 0x02240100
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #7
	bhi _02240200
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224011A: ; jump table
	.short _0224012A - _0224011A - 2 ; case 0
	.short _0224013A - _0224011A - 2 ; case 1
	.short _02240152 - _0224011A - 2 ; case 2
	.short _0224015A - _0224011A - 2 ; case 3
	.short _02240172 - _0224011A - 2 ; case 4
	.short _022401CA - _0224011A - 2 ; case 5
	.short _02240200 - _0224011A - 2 ; case 6
	.short _022401D2 - _0224011A - 2 ; case 7
_0224012A:
	bl MOD18_022400A0
	str r0, [r4, #4]
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_0224013A:
	mov r0, #1
	str r0, [sp]
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_02240152:
	add r0, r0, #1
	add sp, #8
	str r0, [r4]
	pop {r3, r4, r5, pc}
_0224015A:
	mov r0, #1
	str r0, [sp]
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #8
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_02240172:
	ldr r0, [r4, #0x14]
	add r0, r0, #1
	str r0, [r4, #0x14]
	cmp r0, #0x1c
	bne _02240190
	ldr r0, _02240204 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02240208 ; =0x00000B3B
	ldrb r1, [r1, r0]
	add r0, sp, #4
	strb r1, [r0]
	mov r0, #0x26
	add r1, sp, #4
	bl FUN_020311D0
_02240190:
	ldr r0, [r4, #0x14]
	cmp r0, #0x1e
	ble _02240200
	mov r0, #0x10
	bl FUN_0204F774
	mov r0, #1
	str r0, [sp]
	sub r1, r0, #5
	mov r2, #0
	add r3, r0, #0
	bl FUN_0200A208
	bl MOD18_0223D638
	bl MOD18_0224DD94
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r2, [r4, #0x18]
	bl FUN_0204E214
	ldr r0, _0224020C ; =0x0000065F
	bl FUN_020054C8
	mov r0, #5
	add sp, #8
	str r0, [r4]
	pop {r3, r4, r5, pc}
_022401CA:
	mov r0, #6
	add sp, #8
	str r0, [r4]
	pop {r3, r4, r5, pc}
_022401D2:
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r2, _02240204 ; =0x022513A0
	mov r0, #0xa3
	ldr r3, [r2, #4]
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r3, r0]
	ldr r2, [r2, #4]
	add r0, #0x10
	str r1, [r2, r0]
	ldr r0, _0224020C ; =0x0000065F
	bl FUN_020054F0
_02240200:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02240204: .word MOD18_022513A0
_02240208: .word 0x00000B3B
_0224020C: .word 0x0000065F
	thumb_func_end MOD18_02240100

	thumb_func_start MOD18_02240210
MOD18_02240210: ; 0x02240210
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #4
	mov r1, #0x1c
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x1c
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _02240268 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224023E
	bl ErrorHandling
_0224023E:
	ldr r0, _02240268 ; =0x022513A0
	mov r2, #0x64
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	str r5, [r4, #8]
	str r6, [r4, #0xc]
	ldr r0, [sp]
	str r7, [r4, #0x10]
	str r0, [r4, #0x18]
	ldr r0, _0224026C ; =MOD18_02240100
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _02240268 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02240268: .word MOD18_022513A0
_0224026C: .word MOD18_02240100
	thumb_func_end MOD18_02240210

	thumb_func_start MOD18_02240270
MOD18_02240270: ; 0x02240270
	push {r3, lr}
	bl FUN_0204E254
	ldr r2, _02240298 ; =0x022513A0
	mov r0, #0xa7
	ldr r1, [r2, #4]
	lsl r0, r0, #2
	ldr r3, [r1, r0]
	cmp r3, #0
	beq _02240294
	mov r1, #7
	str r1, [r3]
	ldr r2, [r2, #4]
	mov r1, #0
	str r1, [r2, r0]
	ldr r0, _0224029C ; =0x0000065F
	bl FUN_020054F0
_02240294:
	pop {r3, pc}
	nop
_02240298: .word MOD18_022513A0
_0224029C: .word 0x0000065F
	thumb_func_end MOD18_02240270

	thumb_func_start MOD18_022402A0
MOD18_022402A0: ; 0x022402A0
	push {r4, lr}
	bl FUN_0204E254
	ldr r0, _022402EC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	cmp r4, #0
	beq _022402EA
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	add r0, r4, #0
	bl FreeToHeap
	ldr r0, _022402EC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	ldr r2, _022402EC ; =0x022513A0
	mov r0, #0xa3
	ldr r3, [r2, #4]
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r3, r0]
	ldr r2, [r2, #4]
	add r0, #0x10
	str r1, [r2, r0]
	ldr r0, _022402F0 ; =0x0000065F
	bl FUN_020054F0
_022402EA:
	pop {r4, pc}
	.align 2, 0
_022402EC: .word MOD18_022513A0
_022402F0: .word 0x0000065F
	thumb_func_end MOD18_022402A0

	thumb_func_start MOD18_022402F4
MOD18_022402F4: ; 0x022402F4
	bx lr
	.align 2, 0
	thumb_func_end MOD18_022402F4

	thumb_func_start MOD18_022402F8
MOD18_022402F8: ; 0x022402F8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r6, r0, #0
	ldr r0, _02240328 ; =0x022513A0
	add r5, r1, #0
	ldr r0, [r0, #4]
	ldr r1, _0224032C ; =0x00000B46
	add r4, r2, #0
	ldrb r1, [r0, r1]
	cmp r1, #0
	bne _02240322
	sub r1, r3, #1
	str r1, [sp]
	ldr r0, [r0, #0x40]
	add r1, r6, #0
	add r2, r5, #0
	add r3, r4, #0
	bl MOD05_021E53B4
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_02240322:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02240328: .word MOD18_022513A0
_0224032C: .word 0x00000B46
	thumb_func_end MOD18_022402F8

	thumb_func_start MOD18_02240330
MOD18_02240330: ; 0x02240330
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02240330

	thumb_func_start MOD18_02240334
MOD18_02240334: ; 0x02240334
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #4
	mov r1, #0x20
	add r7, r2, #0
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x20
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _02240380 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	add r0, r4, #0
	bl MOD18_0224064C
	ldr r0, [r5, #8]
	add r1, r4, #0
	str r0, [r4, #0x10]
	str r5, [r4, #0x14]
	strb r6, [r4, #0x19]
	ldr r0, _02240384 ; =MOD18_02240658
	mov r2, #0x64
	strb r7, [r4, #0x18]
	bl FUN_0200CA44
	ldr r1, _02240380 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240380: .word MOD18_022513A0
_02240384: .word MOD18_02240658
	thumb_func_end MOD18_02240334

	thumb_func_start MOD18_02240388
MOD18_02240388: ; 0x02240388
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	ldr r0, [sp, #0x38]
	str r3, [sp, #4]
	str r0, [sp, #0x38]
	add r0, r2, #0
	sub r0, r5, r0
	add r4, r1, #0
	str r2, [sp]
	bl abs
	str r0, [sp, #0x20]
	ldr r0, [sp, #4]
	sub r0, r0, r4
	bl abs
	ldr r1, [sp]
	mov r7, #0
	cmp r5, r1
	bge _022403B8
	mov r1, #1
	str r1, [sp, #0x1c]
	b _022403BC
_022403B8:
	sub r1, r7, #1
	str r1, [sp, #0x1c]
_022403BC:
	ldr r1, [sp, #4]
	cmp r4, r1
	bge _022403C8
	mov r1, #1
	str r1, [sp, #0x18]
	b _022403CE
_022403C8:
	mov r1, #0
	mvn r1, r1
	str r1, [sp, #0x18]
_022403CE:
	ldr r1, [sp, #0x20]
	cmp r1, r0
	blt _0224040C
	neg r6, r1
	ldr r1, [sp]
	cmp r5, r1
	beq _02240442
	lsl r0, r0, #1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x20]
	lsl r0, r0, #1
	str r0, [sp, #8]
_022403E6:
	ldr r2, [sp, #0x38]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02240564
	add r7, r7, r0
	ldr r0, [sp, #0x1c]
	add r5, r5, r0
	ldr r0, [sp, #0xc]
	add r6, r6, r0
	bmi _02240404
	ldr r0, [sp, #8]
	sub r6, r6, r0
	ldr r0, [sp, #0x18]
	add r4, r4, r0
_02240404:
	ldr r0, [sp]
	cmp r5, r0
	bne _022403E6
	b _02240442
_0224040C:
	ldr r1, [sp, #4]
	neg r6, r0
	cmp r4, r1
	beq _02240442
	ldr r1, [sp, #0x20]
	lsl r0, r0, #1
	lsl r1, r1, #1
	str r1, [sp, #0x14]
	str r0, [sp, #0x10]
_0224041E:
	ldr r2, [sp, #0x38]
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02240564
	add r7, r7, r0
	ldr r0, [sp, #0x18]
	add r4, r4, r0
	ldr r0, [sp, #0x14]
	add r6, r6, r0
	bmi _0224043C
	ldr r0, [sp, #0x10]
	sub r6, r6, r0
	ldr r0, [sp, #0x1c]
	add r5, r5, r0
_0224043C:
	ldr r0, [sp, #4]
	cmp r4, r0
	bne _0224041E
_02240442:
	cmp r7, #0
	beq _02240456
	ldr r0, _0224045C ; =0x00000629
	bl FUN_02005508
	cmp r0, #0
	bne _02240456
	ldr r0, _0224045C ; =0x00000629
	bl FUN_020054C8
_02240456:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0224045C: .word 0x00000629
	thumb_func_end MOD18_02240388

	thumb_func_start MOD18_02240460
MOD18_02240460: ; 0x02240460
	push {r4, lr}
	ldr r0, _022404EC ; =0x022513A0
	ldr r2, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r2, r0]
	cmp r4, #0
	beq _022404E8
	ldrb r0, [r4, #0x19]
	cmp r0, #0
	beq _02240480
	cmp r1, #0
	beq _02240480
	ldrb r0, [r4, #0x18]
	bl MOD18_0223FD8C
_02240480:
	ldr r1, _022404F0 ; =0x04000050
	mov r0, #0
	strh r0, [r1]
	mov r1, #1
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _022404EC ; =0x022513A0
	mov r1, #2
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl FUN_0201886C
	mov r3, #0
	mov r1, #2
	add r2, r3, #0
	lsl r1, r1, #0xa
_022404A4:
	strb r2, [r0, r3]
	add r3, r3, #2
	cmp r3, r1
	blt _022404A4
	mov r0, #2
	mov r1, #3
	bl FUN_020178BC
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _022404EC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, _022404EC ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_022404E8:
	pop {r4, pc}
	nop
_022404EC: .word MOD18_022513A0
_022404F0: .word 0x04000050
	thumb_func_end MOD18_02240460

	thumb_func_start MOD18_022404F4
MOD18_022404F4: ; 0x022404F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r7, r0, #0
	str r1, [sp, #4]
	add r0, r1, #0
	mov r1, #2
	add r6, r2, #0
	mov r4, #0
	bl FUN_0201886C
	add r5, r0, #0
	bne _02240512
	add sp, #8
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
_02240512:
	ldrh r2, [r6, #8]
	ldr r0, _02240560 ; =0x0000FFFF
	cmp r2, r0
	beq _02240532
	ldrh r3, [r6, #0xa]
	cmp r3, r0
	beq _02240532
	str r5, [sp]
	ldrh r0, [r7]
	ldrh r1, [r7, #2]
	bl MOD18_02240388
	ldr r0, [sp, #4]
	mov r1, #2
	bl FUN_02017CD0
_02240532:
	ldrh r0, [r7]
	mov r2, #0
	strh r0, [r6, #8]
	ldrh r0, [r7, #2]
	strh r0, [r6, #0xa]
	mov r0, #2
	lsl r0, r0, #0xa
_02240540:
	ldrb r1, [r5, r2]
	cmp r1, #0
	beq _02240548
	add r4, r4, #1
_02240548:
	add r2, r2, #2
	cmp r2, r0
	blt _02240540
	cmp r4, #0xd
	bge _02240558
	add sp, #8
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02240558:
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240560: .word 0x0000FFFF
	thumb_func_end MOD18_022404F4

	thumb_func_start MOD18_02240564
MOD18_02240564: ; 0x02240564
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r5, r2, #0
	asr r2, r0, #2
	lsr r2, r2, #0x1d
	add r2, r0, r2
	asr r0, r2, #3
	asr r2, r1, #2
	lsr r2, r2, #0x1d
	add r2, r1, r2
	asr r1, r2, #3
	lsl r1, r1, #5
	add r0, r0, r1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x10
	ldr r4, _02240648 ; =0x022500F4
	str r0, [sp, #4]
	add r3, sp, #0xc
	mov r2, #4
_0224058A:
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _0224058A
	ldr r0, [r4]
	mov r1, #2
	str r0, [r3]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	lsl r1, r1, #0xa
	cmp r0, r1
	bls _022405AA
	ldr r0, [sp, #8]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
_022405AA:
	ldr r1, [sp, #4]
	lsr r0, r0, #0x1f
	lsl r2, r1, #0x1a
	sub r2, r2, r0
	mov r1, #0x1a
	ror r2, r1
	add r0, r0, r2
	ldr r6, [sp, #8]
	add r7, sp, #0xc
	str r0, [sp]
_022405BE:
	ldr r1, [r7]
	ldr r0, [sp, #4]
	add r4, r0, r1
	ldr r0, [sp]
	cmp r0, #0x3e
	bne _022405D6
	add r0, r6, #0
	mov r1, #3
	bl _s32_div_f
	cmp r1, #2
	beq _02240638
_022405D6:
	ldr r0, [sp]
	cmp r0, #0
	bne _022405E8
	add r0, r6, #0
	mov r1, #3
	bl _s32_div_f
	cmp r1, #0
	beq _02240638
_022405E8:
	mov r0, #2
	lsl r0, r0, #0xa
	cmp r4, r0
	bge _02240638
	cmp r4, #0
	blt _02240638
	ldrb r0, [r5, r4]
	cmp r0, #0
	beq _02240638
	mov r1, #1
	str r1, [sp, #8]
	cmp r6, #7
	bhi _0224062A
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0224060E: ; jump table
	.short _0224062A - _0224060E - 2 ; case 0
	.short _02240624 - _0224060E - 2 ; case 1
	.short _0224062A - _0224060E - 2 ; case 2
	.short _02240624 - _0224060E - 2 ; case 3
	.short _0224061E - _0224060E - 2 ; case 4
	.short _02240624 - _0224060E - 2 ; case 5
	.short _0224062A - _0224060E - 2 ; case 6
	.short _02240624 - _0224060E - 2 ; case 7
_0224061E:
	add r0, r0, #3
	strb r0, [r5, r4]
	b _0224062E
_02240624:
	add r0, r0, #2
	strb r0, [r5, r4]
	b _0224062E
_0224062A:
	add r0, r0, #1
	strb r0, [r5, r4]
_0224062E:
	ldrb r0, [r5, r4]
	cmp r0, #5
	bls _02240638
	mov r0, #0
	strb r0, [r5, r4]
_02240638:
	add r6, r6, #1
	add r7, r7, #4
	cmp r6, #9
	blo _022405BE
	ldr r0, [sp, #8]
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02240648: .word MOD18_022500F4
	thumb_func_end MOD18_02240564

	thumb_func_start MOD18_0224064C
MOD18_0224064C: ; 0x0224064C
	ldr r1, _02240654 ; =0x0000FFFF
	strh r1, [r0, #8]
	strh r1, [r0, #0xa]
	bx lr
	.align 2, 0
_02240654: .word 0x0000FFFF
	thumb_func_end MOD18_0224064C

	thumb_func_start MOD18_02240658
MOD18_02240658: ; 0x02240658
	push {r3, r4, lr}
	sub sp, #0x1c
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0xc
	bls _02240666
	b _02240880
_02240666:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02240672: ; jump table
	.short _0224068C - _02240672 - 2 ; case 0
	.short _022406A4 - _02240672 - 2 ; case 1
	.short _022406D8 - _02240672 - 2 ; case 2
	.short _022406F6 - _02240672 - 2 ; case 3
	.short _0224079E - _02240672 - 2 ; case 4
	.short _0224079E - _02240672 - 2 ; case 5
	.short _0224079E - _02240672 - 2 ; case 6
	.short _022407DE - _02240672 - 2 ; case 7
	.short _02240836 - _02240672 - 2 ; case 8
	.short _02240842 - _02240672 - 2 ; case 9
	.short _02240880 - _02240672 - 2 ; case 10
	.short _02240850 - _02240672 - 2 ; case 11
	.short _0224086C - _02240672 - 2 ; case 12
_0224068C:
	mov r0, #4
	mov r1, #0
	bl GX_EngineAToggleLayers
	bl MOD18_022400A0
	str r0, [r4, #4]
	ldr r0, [r4]
	add sp, #0x1c
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_022406A4:
	mov r0, #1
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	mov r1, #0
	mov r0, #0x12
	str r1, [sp]
	lsl r0, r0, #4
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x10]
	mov r0, #0x32
	mov r1, #9
	mov r3, #2
	bl FUN_0200687C
	ldr r0, [r4]
	add sp, #0x1c
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_022406D8:
	mov r0, #0x20
	str r0, [sp]
	mov r0, #4
	mov r2, #0
	str r0, [sp, #4]
	mov r0, #0x32
	mov r1, #0xa
	add r3, r2, #0
	bl FUN_02006930
	ldr r0, [r4]
	add sp, #0x1c
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_022406F6:
	mov r0, #1
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	ldr r0, _02240884 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02240888 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0x13
	bne _0224072E
	mov r1, #0
	mov r0, #6
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r2, [r4, #0x10]
	mov r0, #0x32
	mov r1, #8
	mov r3, #2
	bl FUN_020068C8
	b _02240774
_0224072E:
	ldr r1, _0224088C ; =0x022500A8
	add r0, sp, #0x10
	ldrh r2, [r1, #0x10]
	strh r2, [r0, #4]
	ldrh r2, [r1, #0x12]
	strh r2, [r0, #6]
	ldrh r2, [r1, #0x14]
	ldrh r1, [r1, #0x16]
	strh r2, [r0, #8]
	strh r1, [r0, #0xa]
	bl LCRandom
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1e
	sub r1, r1, r2
	mov r0, #0x1e
	ror r1, r0
	add r0, r2, r1
	lsl r1, r0, #0x10
	mov r2, #0
	mov r0, #6
	str r2, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r2, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	lsr r2, r1, #0xf
	add r1, sp, #0x14
	ldrh r1, [r1, r2]
	ldr r2, [r4, #0x10]
	mov r0, #0x32
	mov r3, #2
	bl FUN_020068C8
_02240774:
	mov r0, #0
	mov r1, #3
	bl FUN_020178BC
	mov r0, #1
	mov r1, #2
	bl FUN_020178BC
	mov r0, #2
	mov r1, #1
	bl FUN_020178BC
	mov r0, #3
	mov r1, #0
	bl FUN_020178BC
	ldr r0, [r4]
	add sp, #0x1c
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_0224079E:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0x1e
	ble _02240880
	mov r0, #1
	sub r1, r0, #5
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	mov r0, #4
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #7
	str r0, [r4]
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x4d
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #0
	str r0, [r4, #0x1c]
	ldr r0, _02240890 ; =0x00000661
	bl FUN_020054C8
	add sp, #0x1c
	pop {r3, r4, pc}
_022407DE:
	ldr r1, _02240894 ; =gMain + 0x40
	ldrh r0, [r1, #0x22]
	cmp r0, #0
	beq _02240816
	ldrh r2, [r1, #0x1c]
	add r0, sp, #0x10
	strh r2, [r0]
	ldrh r1, [r1, #0x1e]
	add r2, r4, #0
	strh r1, [r0, #2]
	ldr r1, [r4, #0x10]
	add r0, sp, #0x10
	bl MOD18_022404F4
	cmp r0, #0
	beq _0224081C
	ldrb r0, [r4, #0x19]
	cmp r0, #0
	beq _0224080A
	mov r0, #0xb
	str r0, [r4]
	b _0224081C
_0224080A:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
	b _0224081C
_02240816:
	add r0, r4, #0
	bl MOD18_0224064C
_0224081C:
	ldr r0, [r4, #0x1c]
	cmp r0, #0x3c
	bge _02240880
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0x3c
	bne _02240880
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x1c
	pop {r3, r4, pc}
_02240836:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x1c
	pop {r3, r4, pc}
_02240842:
	bl FUN_02031190
	ldrb r1, [r4, #0x19]
	bl MOD18_02240460
	add sp, #0x1c
	pop {r3, r4, pc}
_02240850:
	mov r0, #0
	strb r0, [r4, #0x19]
	mov r0, #0x10
	bl FUN_0204F774
	ldrb r0, [r4, #0x18]
	bl MOD18_0223FD8C
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #0xc
	add sp, #0x1c
	str r0, [r4]
	pop {r3, r4, pc}
_0224086C:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #8
	ble _02240880
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02240880:
	add sp, #0x1c
	pop {r3, r4, pc}
	.align 2, 0
_02240884: .word MOD18_022513A0
_02240888: .word 0x00000B3B
_0224088C: .word MOD18_022500A8
_02240890: .word 0x00000661
_02240894: .word gMain + 0x40
	thumb_func_end MOD18_02240658

	thumb_func_start MOD18_02240898
MOD18_02240898: ; 0x02240898
	mov r0, #4
	bx lr
	thumb_func_end MOD18_02240898

	thumb_func_start MOD18_0224089C
MOD18_0224089C: ; 0x0224089C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl FUN_0204D830
	cmp r0, #0
	beq _022408E4
	add r0, r4, #0
	bl FUN_0204E778
	ldr r1, _022408F4 ; =0x022513A0
	add r0, r4, #0
	ldr r1, [r1, #4]
	add r2, r1, r4
	ldr r1, _022408F8 ; =0x00000B3C
	ldrb r1, [r2, r1]
	bl MOD18_0223FCD4
	add r0, r4, #0
	bl MOD18_022475F8
	add r1, sp, #0
	strb r0, [r1, #3]
	ldr r0, _022408F4 ; =0x022513A0
	ldr r0, [r0, #4]
	add r2, r0, r4
	ldr r0, _022408F8 ; =0x00000B3C
	ldrb r0, [r2, r0]
	strb r0, [r1]
	strb r4, [r1, #1]
	mov r0, #1
	strb r0, [r1, #2]
	mov r0, #0x2a
	add r1, sp, #0
	bl FUN_02030C4C
_022408E4:
	ldr r0, _022408F4 ; =0x022513A0
	mov r2, #0
	ldr r0, [r0, #4]
	add r1, r0, r4
	ldr r0, _022408F8 ; =0x00000B3C
	strb r2, [r1, r0]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_022408F4: .word MOD18_022513A0
_022408F8: .word 0x00000B3C
	thumb_func_end MOD18_0224089C

	thumb_func_start MOD18_022408FC
MOD18_022408FC: ; 0x022408FC
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0204E778
	ldr r0, _0224093C ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r4
	ldr r0, _02240940 ; =0x00000B3C
	ldrb r1, [r1, r0]
	cmp r1, #0
	beq _02240918
	add r0, r4, #0
	bl MOD18_0223FCD4
_02240918:
	ldr r1, _0224093C ; =0x022513A0
	mov r3, #0
	ldr r0, [r1, #4]
	add r2, r0, r4
	ldr r0, _02240940 ; =0x00000B3C
	strb r3, [r2, r0]
	ldr r1, [r1, #4]
	sub r0, #0x71
	add r3, r1, r0
	lsl r2, r4, #3
	ldrb r1, [r3, r2]
	mov r0, #0x80
	bic r1, r0
	add r0, r4, #0
	strb r1, [r3, r2]
	bl MOD18_022475F8
	pop {r4, pc}
	.align 2, 0
_0224093C: .word MOD18_022513A0
_02240940: .word 0x00000B3C
	thumb_func_end MOD18_022408FC

	thumb_func_start MOD18_02240944
MOD18_02240944: ; 0x02240944
	push {r4, r5, r6, lr}
	add r4, r2, #0
	ldrb r0, [r4, #2]
	ldrb r5, [r4]
	cmp r0, #0
	ldrb r0, [r4, #1]
	beq _02240958
	bl FUN_0204F08C
	b _0224095C
_02240958:
	bl FUN_0204F0A8
_0224095C:
	ldrb r0, [r4, #1]
	bl MOD18_02243FB8
	ldrb r6, [r4, #1]
	bl FUN_02031190
	cmp r6, r0
	bne _02240986
	ldr r0, _022409C0 ; =0x02250348
	lsl r1, r5, #2
	ldr r2, [r0, r1]
	cmp r2, #0
	beq _0224097C
	ldrb r1, [r4, #3]
	add r0, r6, #0
	blx r2
_0224097C:
	ldr r0, _022409C4 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	ldr r0, _022409C8 ; =0x00000B3B
	strb r2, [r1, r0]
_02240986:
	sub r5, #0x18
	cmp r5, #3
	bhi _022409A0
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02240998: ; jump table
	.short _022409AE - _02240998 - 2 ; case 0
	.short _022409AE - _02240998 - 2 ; case 1
	.short _022409AE - _02240998 - 2 ; case 2
	.short _022409AE - _02240998 - 2 ; case 3
_022409A0:
	ldr r0, _022409C4 ; =0x022513A0
	mov r2, #1
	ldr r1, [r0, #4]
	ldrb r0, [r4, #1]
	add r1, r1, r0
	ldr r0, _022409CC ; =0x00000B1C
	strb r2, [r1, r0]
_022409AE:
	bl FUN_02031190
	cmp r0, #0
	beq _022409BC
	ldrb r0, [r4, #1]
	bl FUN_0204E778
_022409BC:
	pop {r4, r5, r6, pc}
	nop
_022409C0: .word MOD18_02250348
_022409C4: .word MOD18_022513A0
_022409C8: .word 0x00000B3B
_022409CC: .word 0x00000B1C
	thumb_func_end MOD18_02240944

	thumb_func_start MOD18_022409D0
MOD18_022409D0: ; 0x022409D0
	push {r3, lr}
	ldr r0, _022409E8 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _022409EC ; =0x00000B3B
	ldrb r0, [r1, r0]
	sub r0, #0xb
	cmp r0, #1
	bhi _022409E6
	ldrb r0, [r2]
	bl MOD18_02241008
_022409E6:
	pop {r3, pc}
	.align 2, 0
_022409E8: .word MOD18_022513A0
_022409EC: .word 0x00000B3B
	thumb_func_end MOD18_022409D0

	thumb_func_start MOD18_022409F0
MOD18_022409F0: ; 0x022409F0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204E778
	ldr r1, _02240A3C ; =0x022513A0
	add r0, r4, #0
	ldr r1, [r1, #4]
	add r2, r1, r4
	ldr r1, _02240A40 ; =0x00000B3C
	ldrb r1, [r2, r1]
	bl MOD18_0223FCD4
	add r1, sp, #0
	strb r4, [r1, #1]
	ldr r0, _02240A3C ; =0x022513A0
	strb r5, [r1]
	ldr r0, [r0, #4]
	add r2, r0, r4
	ldr r0, _02240A40 ; =0x00000B3C
	ldrb r0, [r2, r0]
	strb r0, [r1, #2]
	mov r0, #0x2c
	add r1, sp, #0
	bl FUN_02030C4C
	ldr r0, _02240A3C ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	add r2, r0, r4
	ldr r0, _02240A40 ; =0x00000B3C
	strb r1, [r2, r0]
	add r0, r5, #0
	bl FUN_0204EAD8
	pop {r3, r4, r5, pc}
	nop
_02240A3C: .word MOD18_022513A0
_02240A40: .word 0x00000B3C
	thumb_func_end MOD18_022409F0

	thumb_func_start MOD18_02240A44
MOD18_02240A44: ; 0x02240A44
	push {r3, r4, r5, lr}
	ldr r0, _02240B10 ; =0x022513A0
	add r4, r2, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	add r5, r0, #0
	ldrb r0, [r4, #1]
	bl FUN_0204F08C
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _02240AA6
	add r0, r5, #0
	bl FUN_02026B58
	ldr r0, _02240B10 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x22
	bl FUN_0202A170
	bl FUN_0204F7E4
	bl MOD18_0223D638
	add r5, r0, #0
	ldrb r0, [r4, #1]
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D638
	ldr r3, _02240B14 ; =MOD18_0223ECDC
	mov r1, #0x47
	mov r2, #1
	bl MOD18_0224DCB8
_02240AA6:
	ldrb r0, [r4, #1]
	bl MOD18_02243FB8
	ldrb r5, [r4, #1]
	bl FUN_02031190
	cmp r5, r0
	bne _02240AF2
	ldr r0, _02240B10 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02240B18 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0
	beq _02240AF2
	lsl r1, r0, #2
	ldr r0, _02240B1C ; =0x022503D4
	ldr r2, [r0, r1]
	cmp r2, #0
	beq _02240AD2
	add r0, r5, #0
	mov r1, #0
	blx r2
_02240AD2:
	ldr r1, _02240B10 ; =0x022513A0
	mov r0, #0x2a
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #4
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	ldr r0, _02240B18 ; =0x00000B3B
	strb r3, [r1, r0]
	mov r0, #0x10
	bl FUN_0204F774
	bl MOD18_0223D638
	bl MOD18_0224DD94
_02240AF2:
	bl FUN_02031190
	cmp r0, #0
	beq _02240B00
	ldrb r0, [r4, #1]
	bl FUN_0204E778
_02240B00:
	ldr r0, _02240B10 ; =0x022513A0
	ldrb r2, [r4, #1]
	ldr r1, [r0, #4]
	ldrb r0, [r4]
	add r1, r1, r0
	ldr r0, _02240B20 ; =0x00000B04
	strb r2, [r1, r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02240B10: .word MOD18_022513A0
_02240B14: .word MOD18_0223ECDC
_02240B18: .word 0x00000B3B
_02240B1C: .word MOD18_022503D4
_02240B20: .word 0x00000B04
	thumb_func_end MOD18_02240A44

	thumb_func_start MOD18_02240B24
MOD18_02240B24: ; 0x02240B24
	mov r0, #3
	bx lr
	thumb_func_end MOD18_02240B24

	thumb_func_start MOD18_02240B28
MOD18_02240B28: ; 0x02240B28
	push {r4, lr}
	ldr r1, _02240B58 ; =0x022513A0
	ldr r2, [r1, #4]
	cmp r2, #0
	beq _02240B52
	mov r1, #0xa6
	lsl r1, r1, #2
	ldr r4, [r2, r1]
	cmp r4, #0
	beq _02240B52
	sub r1, #0xb6
	ldrh r1, [r4, r1]
	lsr r1, r1, #1
	add r0, r1, r0
	mov r1, #0x50
	bl _s32_div_f
	mov r0, #6
	mul r0, r1
	ldrh r0, [r4, r0]
	pop {r4, pc}
_02240B52:
	mov r0, #0
	pop {r4, pc}
	nop
_02240B58: .word MOD18_022513A0
	thumb_func_end MOD18_02240B28

	thumb_func_start MOD18_02240B5C
MOD18_02240B5C: ; 0x02240B5C
	push {r4, lr}
	ldr r1, _02240B8C ; =0x022513A0
	ldr r2, [r1, #4]
	cmp r2, #0
	beq _02240B88
	mov r1, #0xa6
	lsl r1, r1, #2
	ldr r4, [r2, r1]
	cmp r4, #0
	beq _02240B88
	sub r1, #0xb6
	ldrh r1, [r4, r1]
	lsr r1, r1, #1
	add r0, r1, r0
	mov r1, #0x50
	bl _s32_div_f
	mov r0, #6
	mul r0, r1
	add r0, r4, r0
	ldrh r0, [r0, #2]
	pop {r4, pc}
_02240B88:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02240B8C: .word MOD18_022513A0
	thumb_func_end MOD18_02240B5C

	thumb_func_start MOD18_02240B90
MOD18_02240B90: ; 0x02240B90
	push {r4, lr}
	ldr r0, _02240BB0 ; =0x000001E2
	add r4, r1, #0
	ldrh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, r0]
	ldrh r0, [r4, r0]
	cmp r0, #0xa0
	bls _02240BAE
	ldr r0, _02240BB4 ; =0x00000621
	bl FUN_020054C8
	ldr r0, _02240BB0 ; =0x000001E2
	mov r1, #0
	strh r1, [r4, r0]
_02240BAE:
	pop {r4, pc}
	.align 2, 0
_02240BB0: .word 0x000001E2
_02240BB4: .word 0x00000621
	thumb_func_end MOD18_02240B90

	thumb_func_start MOD18_02240BB8
MOD18_02240BB8: ; 0x02240BB8
	push {r4, lr}
	ldr r0, _02240C0C ; =0x022513A0
	mov r1, #0xa6
	ldr r2, [r0, #4]
	lsl r1, r1, #2
	ldr r0, [r2, r1]
	cmp r0, #0
	bne _02240C08
	sub r0, r1, #4
	ldr r0, [r2, r0]
	cmp r0, #0
	bne _02240C08
	mov r0, #4
	sub r1, #0xb4
	bl AllocFromHeapAtEnd
	mov r2, #0x79
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x2e
	bl FUN_020311DC
	ldr r0, _02240C0C ; =0x022513A0
	mov r2, #0x64
	ldr r1, [r0, #4]
	mov r0, #0xa6
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _02240C10 ; =MOD18_02240B90
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _02240C0C ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa5
	lsl r1, r1, #2
	str r0, [r2, r1]
_02240C08:
	pop {r4, pc}
	nop
_02240C0C: .word MOD18_022513A0
_02240C10: .word MOD18_02240B90
	thumb_func_end MOD18_02240BB8

	thumb_func_start MOD18_02240C14
MOD18_02240C14: ; 0x02240C14
	push {r3, lr}
	ldr r0, _02240C6C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa5
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02240C68
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02240C70 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	ldr r0, _02240C6C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa5
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	ldr r0, _02240C6C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, _02240C6C ; =0x022513A0
	mov r0, #0xa5
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, r0, #4
	str r3, [r1, r0]
_02240C68:
	pop {r3, pc}
	nop
_02240C6C: .word MOD18_022513A0
_02240C70: .word 0x04000050
	thumb_func_end MOD18_02240C14

	thumb_func_start MOD18_02240C74
MOD18_02240C74: ; 0x02240C74
	ldr r1, _02240C84 ; =0x022513A0
	lsl r0, r0, #1
	ldr r1, [r1, #4]
	mov r2, #1
	add r1, r1, r0
	ldr r0, _02240C88 ; =0x00000B0C
	strh r2, [r1, r0]
	bx lr
	.align 2, 0
_02240C84: .word MOD18_022513A0
_02240C88: .word 0x00000B0C
	thumb_func_end MOD18_02240C74

	thumb_func_start MOD18_02240C8C
MOD18_02240C8C: ; 0x02240C8C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r5, #0
	str r5, [sp]
_02240C94:
	ldr r0, _02240D20 ; =0x022513A0
	ldr r1, _02240D24 ; =0x00000B0C
	ldr r0, [r0, #4]
	add r2, r0, r5
	ldrh r1, [r2, r1]
	sub r4, r1, #1
	cmp r1, #0
	beq _02240D10
	lsl r7, r4, #2
_02240CA6:
	add r1, r0, r7
	ldr r0, _02240D28 ; =0x000007C4
	ldr r6, [r1, r0]
	cmp r6, #0
	beq _02240CEA
	ldrb r0, [r6, #4]
	cmp r0, #0
	beq _02240CEA
	add r0, r6, #0
	bl MOD18_0223F6F8
	ldr r1, [sp]
	cmp r0, r1
	beq _02240CC6
	cmp r0, #8
	blt _02240CEA
_02240CC6:
	ldrh r0, [r6]
	add r1, sp, #4
	strh r0, [r1]
	ldrh r0, [r6, #2]
	strh r0, [r1, #2]
	ldr r0, [sp]
	strb r0, [r1, #4]
	mov r0, #0x2f
	add r1, sp, #4
	bl FUN_02030C4C
	ldr r0, _02240D20 ; =0x022513A0
	add r2, r4, #2
	ldr r0, [r0, #4]
	add r1, r0, r5
	ldr r0, _02240D24 ; =0x00000B0C
	strh r2, [r1, r0]
	b _02240D10
_02240CEA:
	add r4, r4, #1
	add r7, r7, #4
	cmp r4, #0xc0
	blt _02240D00
	ldr r0, _02240D20 ; =0x022513A0
	mov r2, #0
	ldr r0, [r0, #4]
	add r1, r0, r5
	ldr r0, _02240D24 ; =0x00000B0C
	strh r2, [r1, r0]
	b _02240D10
_02240D00:
	ldr r0, _02240D20 ; =0x022513A0
	ldr r1, _02240D24 ; =0x00000B0C
	ldr r0, [r0, #4]
	add r2, r5, r0
	ldrh r1, [r2, r1]
	sub r1, r1, #1
	cmp r4, r1
	bne _02240CA6
_02240D10:
	ldr r0, [sp]
	add r5, r5, #2
	add r0, r0, #1
	str r0, [sp]
	cmp r0, #8
	blt _02240C94
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02240D20: .word MOD18_022513A0
_02240D24: .word 0x00000B0C
_02240D28: .word 0x000007C4
	thumb_func_end MOD18_02240C8C

	thumb_func_start MOD18_02240D2C
MOD18_02240D2C: ; 0x02240D2C
	push {r3, r4, r5, lr}
	ldr r0, _02240D94 ; =0x022513A0
	add r4, r2, #0
	ldr r1, [r0, #4]
	mov r0, #0xa6
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02240D90
	bl FUN_02031190
	ldrb r1, [r4, #4]
	cmp r1, r0
	bne _02240D90
	ldr r0, _02240D94 ; =0x022513A0
	mov r1, #0xa6
	ldr r0, [r0, #4]
	lsl r1, r1, #2
	ldr r5, [r0, r1]
	sub r1, #0xb8
	ldrb r1, [r5, r1]
	mov r2, #6
	add r0, r4, #0
	add r3, r1, #0
	mul r3, r2
	add r1, r5, r3
	bl MI_CpuCopy8
	ldr r2, _02240D94 ; =0x022513A0
	mov r1, #0xa6
	ldr r0, [r2, #4]
	lsl r1, r1, #2
	ldr r4, [r0, r1]
	add r0, r1, #0
	sub r0, #0xb8
	ldrb r0, [r4, r0]
	add r3, r0, #1
	add r0, r1, #0
	sub r0, #0xb8
	strb r3, [r4, r0]
	ldr r0, [r2, #4]
	ldr r2, [r0, r1]
	add r0, r1, #0
	sub r0, #0xb8
	ldrb r0, [r2, r0]
	cmp r0, #0x50
	blo _02240D90
	mov r0, #0
	sub r1, #0xb8
	strb r0, [r2, r1]
_02240D90:
	pop {r3, r4, r5, pc}
	nop
_02240D94: .word MOD18_022513A0
	thumb_func_end MOD18_02240D2C

	thumb_func_start MOD18_02240D98
MOD18_02240D98: ; 0x02240D98
	mov r0, #6
	bx lr
	thumb_func_end MOD18_02240D98

	thumb_func_start MOD18_02240D9C
MOD18_02240D9C: ; 0x02240D9C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02031190
	cmp r4, r0
	bne _02240DC0
	ldr r1, _02240DC4 ; =0x022513A0
	mov r0, #0xa7
	ldr r2, [r1, #4]
	lsl r0, r0, #2
	ldr r3, [r2, r0]
	cmp r3, #0
	beq _02240DC0
	mov r2, #2
	str r2, [r3]
	ldr r1, [r1, #4]
	mov r2, #0
	str r2, [r1, r0]
_02240DC0:
	pop {r4, pc}
	nop
_02240DC4: .word MOD18_022513A0
	thumb_func_end MOD18_02240D9C

	thumb_func_start MOD18_02240DC8
MOD18_02240DC8: ; 0x02240DC8
	push {r3, lr}
	ldr r0, _02240E24 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02240E20
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02240E28 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	bl FUN_020307D0
	ldr r0, _02240E24 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	ldr r0, _02240E24 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, _02240E24 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02240E20:
	pop {r3, pc}
	nop
_02240E24: .word MOD18_022513A0
_02240E28: .word 0x04000050
	thumb_func_end MOD18_02240DC8

	thumb_func_start MOD18_02240E2C
MOD18_02240E2C: ; 0x02240E2C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _02240E42
	cmp r0, #1
	beq _02240EDC
	cmp r0, #2
	beq _02240EA4
	pop {r3, r4, r5, pc}
_02240E42:
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #1
	bne _02240E54
	bl MOD18_022400A0
	str r0, [r4, #4]
	b _02240E7A
_02240E54:
	cmp r0, #2
	bne _02240E68
	mov r0, #1
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	b _02240E7A
_02240E68:
	cmp r0, #4
	bne _02240E7A
	mov r0, #1
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
_02240E7A:
	ldr r0, [r4, #0x10]
	cmp r0, #0x1e
	ble _02240EDC
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #1
	str r0, [r4]
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02240E98
	bl FUN_020307BC
	b _02240E9C
_02240E98:
	bl FUN_020307A8
_02240E9C:
	mov r0, #0x10
	bl FUN_0204F774
	pop {r3, r4, r5, pc}
_02240EA4:
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02240EE0 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	bl FUN_020307D0
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r1, _02240EE4 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02240EDC:
	pop {r3, r4, r5, pc}
	nop
_02240EE0: .word 0x04000050
_02240EE4: .word MOD18_022513A0
	thumb_func_end MOD18_02240E2C

	thumb_func_start MOD18_02240EE8
MOD18_02240EE8: ; 0x02240EE8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #4
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4]
	str r5, [r4, #8]
	str r0, [r4, #0x10]
	ldr r0, _02240F2C ; =0x022513A0
	mov r2, #0x64
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _02240F30 ; =MOD18_02240E2C
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _02240F2C ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	mov r0, #0x10
	bl FUN_0204F74C
	pop {r3, r4, r5, pc}
	.align 2, 0
_02240F2C: .word MOD18_022513A0
_02240F30: .word MOD18_02240E2C
	thumb_func_end MOD18_02240EE8

	thumb_func_start MOD18_02240F34
MOD18_02240F34: ; 0x02240F34
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02031190
	cmp r4, r0
	bne _02240F7E
	ldr r0, _02240F80 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	cmp r4, #0
	beq _02240F7E
	ldr r0, [r1, #0x40]
	mov r1, #0
	ldr r0, [r0, #0x38]
	bl FUN_02055540
	ldr r0, _02240F80 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, _02240F80 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02240F7E:
	pop {r4, pc}
	.align 2, 0
_02240F80: .word MOD18_022513A0
	thumb_func_end MOD18_02240F34

	thumb_func_start MOD18_02240F84
MOD18_02240F84: ; 0x02240F84
	push {r3, r4, r5, lr}
	ldr r0, _02241000 ; =0x022513A0
	add r5, r1, #0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	cmp r4, #0
	beq _02240FFE
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02240FA4
	bl FUN_02064520
	mov r0, #0
	str r0, [r4, #0x14]
_02240FA4:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _02240FB4
	cmp r5, #0
	beq _02240FB4
	ldrb r0, [r4, #0xc]
	bl MOD18_0223FD8C
_02240FB4:
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02241004 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	ldr r0, _02241000 ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055540
	ldr r0, _02241000 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, _02241000 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02240FFE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02241000: .word MOD18_022513A0
_02241004: .word 0x04000050
	thumb_func_end MOD18_02240F84

	thumb_func_start MOD18_02241008
MOD18_02241008: ; 0x02241008
	push {r4, lr}
	add r4, r0, #0
	bl FUN_02031190
	cmp r4, r0
	bne _0224102C
	ldr r0, _02241030 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r1, [r1, r0]
	cmp r1, #0
	beq _0224102C
	mov r0, #0xe
	str r0, [r1]
	ldr r0, _02241034 ; =0x0000060B
	bl FUN_020054C8
_0224102C:
	pop {r4, pc}
	nop
_02241030: .word MOD18_022513A0
_02241034: .word 0x0000060B
	thumb_func_end MOD18_02241008

	thumb_func_start MOD18_02241038
MOD18_02241038: ; 0x02241038
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r3, _02241274 ; =0x022500CC
	add r4, r1, #0
	add r5, r0, #0
	add r2, sp, #4
	mov r1, #0xf
_02241046:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _02241046
	ldr r0, [r4]
	cmp r0, #0xe
	bhi _0224110A
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02241064: ; jump table
	.short _02241082 - _02241064 - 2 ; case 0
	.short _02241096 - _02241064 - 2 ; case 1
	.short _022410AE - _02241064 - 2 ; case 2
	.short _022410B6 - _02241064 - 2 ; case 3
	.short _022410CE - _02241064 - 2 ; case 4
	.short _02241100 - _02241064 - 2 ; case 5
	.short _02241100 - _02241064 - 2 ; case 6
	.short _0224118C - _02241064 - 2 ; case 7
	.short _0224126E - _02241064 - 2 ; case 8
	.short _022411B0 - _02241064 - 2 ; case 9
	.short _0224126E - _02241064 - 2 ; case 10
	.short _022411E0 - _02241064 - 2 ; case 11
	.short _022411FC - _02241064 - 2 ; case 12
	.short _0224126E - _02241064 - 2 ; case 13
	.short _02241222 - _02241064 - 2 ; case 14
_02241082:
	bl MOD18_022400A0
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, pc}
_02241096:
	mov r0, #1
	str r0, [sp]
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, pc}
_022410AE:
	add r0, r0, #1
	add sp, #0x14
	str r0, [r4]
	pop {r4, r5, pc}
_022410B6:
	mov r0, #1
	str r0, [sp]
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	pop {r4, r5, pc}
_022410CE:
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0x3c
	ble _022410E6
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #0x1c]
	pop {r4, r5, pc}
_022410E6:
	ldrb r0, [r4, #0xc]
	mov r1, #1
	bl MOD18_0223FDEC
	cmp r0, #0
	beq _0224110A
	ldr r0, [r4]
	add sp, #0x14
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #0x1c]
	pop {r4, r5, pc}
_02241100:
	ldr r0, [r4, #0x1c]
	add r0, r0, #1
	str r0, [r4, #0x1c]
	cmp r0, #0x1e
	bgt _0224110C
_0224110A:
	b _0224126E
_0224110C:
	mov r0, #0x10
	bl FUN_0204F774
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #7
	str r0, [r4]
	ldr r0, _02241278 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	add r5, r0, #0
	ldr r0, _02241278 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r2, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _02241166
	mov r0, #0x20
	str r0, [sp]
	ldr r0, _02241278 ; =0x022513A0
	add r1, r5, #0
	ldr r0, [r0, #4]
	mov r3, #2
	ldr r0, [r0, #0x40]
	bl MOD05_021E53B4
	str r0, [r4, #0x14]
	ldr r0, _02241278 ; =0x022513A0
	ldr r1, _0224127C ; =0xFFFFE000
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055540
	add sp, #0x14
	pop {r4, r5, pc}
_02241166:
	mov r0, #0x20
	str r0, [sp]
	ldr r0, _02241278 ; =0x022513A0
	add r1, r5, #0
	ldr r0, [r0, #4]
	mov r3, #3
	ldr r0, [r0, #0x40]
	bl MOD05_021E53B4
	str r0, [r4, #0x14]
	ldr r0, _02241278 ; =0x022513A0
	ldr r1, _02241280 ; =0xFFFFD000
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055540
	add sp, #0x14
	pop {r4, r5, pc}
_0224118C:
	ldr r0, _02241278 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	add r5, r0, #0
	ldr r0, [r4, #0x18]
	cmp r0, r5
	beq _022411A6
	ldr r0, _02241284 ; =0x000005EB
	bl FUN_020054C8
_022411A6:
	str r5, [r4, #0x18]
	mov r0, #0
	add sp, #0x14
	str r0, [r4, #0x10]
	pop {r4, r5, pc}
_022411B0:
	ldr r0, _02241278 ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055540
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r1, _02241278 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
	add sp, #0x14
	pop {r4, r5, pc}
_022411E0:
	mov r0, #0
	strb r0, [r4, #0xd]
	mov r0, #0x10
	bl FUN_0204F774
	ldrb r0, [r4, #0xc]
	bl MOD18_0223FD8C
	mov r0, #0
	str r0, [r4, #0x1c]
	mov r0, #0xc
	add sp, #0x14
	str r0, [r4]
	pop {r4, r5, pc}
_022411FC:
	ldr r0, [r4, #0x1c]
	mov r1, #0
	add r0, r0, #1
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #0xc]
	bl MOD18_0223FDEC
	cmp r0, #0
	bne _02241214
	ldr r0, [r4, #0x1c]
	cmp r0, #0x3c
	ble _0224126E
_02241214:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	add sp, #0x14
	str r0, [r4]
	pop {r4, r5, pc}
_02241222:
	ldr r1, [r4, #0x10]
	add r0, sp, #4
	ldrsb r1, [r0, r1]
	mov r0, #9
	mvn r0, r0
	cmp r1, r0
	beq _0224126E
	ldr r0, _02241278 ; =0x022513A0
	lsl r1, r1, #0xc
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055540
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	cmp r0, #5
	bne _0224126E
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02241256
	bl FUN_02064520
	mov r0, #0
	str r0, [r4, #0x14]
_02241256:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _02241264
	mov r0, #0xb
	add sp, #0x14
	str r0, [r4]
	pop {r4, r5, pc}
_02241264:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #9
	str r0, [r4]
_0224126E:
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02241274: .word MOD18_022500CC
_02241278: .word MOD18_022513A0
_0224127C: .word 0xFFFFE000
_02241280: .word 0xFFFFD000
_02241284: .word 0x000005EB
	thumb_func_end MOD18_02241038

	thumb_func_start MOD18_02241288
MOD18_02241288: ; 0x02241288
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #4
	mov r1, #0x24
	add r7, r2, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x24
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4]
	str r5, [r4, #8]
	str r0, [r4, #0x10]
	ldr r0, _022412DC ; =0x022513A0
	strb r6, [r4, #0xd]
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_020552F8
	str r0, [r4, #0x18]
	ldr r0, _022412DC ; =0x022513A0
	strb r7, [r4, #0xc]
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _022412E0 ; =MOD18_02241038
	add r1, r4, #0
	mov r2, #0x64
	bl FUN_0200CA44
	ldr r1, _022412DC ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022412DC: .word MOD18_022513A0
_022412E0: .word MOD18_02241038
	thumb_func_end MOD18_02241288

	thumb_func_start MOD18_022412E4
MOD18_022412E4: ; 0x022412E4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #4
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _02241304
	mov r0, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD18_02241288
_02241304:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_022412E4

	thumb_func_start MOD18_02241308
MOD18_02241308: ; 0x02241308
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #4
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _02241328
	mov r0, #1
	add r1, r4, #0
	add r2, r6, #0
	bl MOD18_02241288
_02241328:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_02241308

	thumb_func_start MOD18_0224132C
MOD18_0224132C: ; 0x0224132C
	push {r4, lr}
	add r4, r0, #0
	bl FUN_0204E778
	add r0, r4, #0
	bl FUN_0204F69C
	pop {r4, pc}
	thumb_func_end MOD18_0224132C

	thumb_func_start MOD18_0224133C
MOD18_0224133C: ; 0x0224133C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #4
	bl FUN_0204E758
	add r0, r4, #0
	mov r1, #0xa
	bl FUN_0204F678
	pop {r4, pc}
	thumb_func_end MOD18_0224133C

	thumb_func_start MOD18_02241350
MOD18_02241350: ; 0x02241350
	push {r4, lr}
	add r4, r0, #0
	mov r1, #4
	bl FUN_0204E758
	add r0, r4, #0
	mov r1, #0x14
	bl FUN_0204F678
	pop {r4, pc}
	thumb_func_end MOD18_02241350

	thumb_func_start MOD18_02241364
MOD18_02241364: ; 0x02241364
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r0, #0
	add r0, sp, #0xc
	bl FUN_020312BC
	mov r0, #0x45
	lsl r0, r0, #2
	ldrb r0, [r7, r0]
	mov r4, #0
	cmp r0, #0
	ble _0224141A
	mov r0, #0
	add r5, r7, #0
	add r6, r7, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
_02241388:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r0, r0, r2
	str r0, [sp, #0xc]
	adc r1, r3
	ldr r0, [sp]
	str r1, [sp, #0x10]
	lsl r2, r0, #8
	lsr r1, r1, #0x18
	add r0, r5, #0
	orr r2, r1
	add r0, #0x48
	strh r2, [r0]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r0, r0, r2
	adc r1, r3
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	add r0, r1, #0
	ldr r1, [sp, #4]
	mov r2, #0xc0
	mov r3, #0
	bl _ll_mul
	add r0, r5, #0
	add r0, #0x4a
	strh r1, [r0]
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x10]
	bl _ll_mul
	add r2, r0, #0
	add r3, r1, #0
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x20]
	add r0, r0, r2
	adc r1, r3
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	add r0, r1, #0
	ldr r1, [sp, #8]
	ldr r2, _02241420 ; =0x0000FFFF
	mov r3, #0
	bl _ll_mul
	mov r0, #0x45
	strh r1, [r6, #8]
	lsl r0, r0, #2
	ldrb r0, [r7, r0]
	add r4, r4, #1
	add r5, r5, #4
	add r6, r6, #2
	cmp r4, r0
	blt _02241388
_0224141A:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_02241420: .word 0x0000FFFF
	thumb_func_end MOD18_02241364

	thumb_func_start MOD18_02241424
MOD18_02241424: ; 0x02241424
	push {r4, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0xc
	bls _02241432
	b _02241698
_02241432:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224143E: ; jump table
	.short _02241458 - _0224143E - 2 ; case 0
	.short _02241472 - _0224143E - 2 ; case 1
	.short _022414BE - _0224143E - 2 ; case 2
	.short _02241500 - _0224143E - 2 ; case 3
	.short _0224154C - _0224143E - 2 ; case 4
	.short _0224158A - _0224143E - 2 ; case 5
	.short _022415C0 - _0224143E - 2 ; case 6
	.short _022415FA - _0224143E - 2 ; case 7
	.short _02241642 - _0224143E - 2 ; case 8
	.short _0224164E - _0224143E - 2 ; case 9
	.short _02241698 - _0224143E - 2 ; case 10
	.short _0224165E - _0224143E - 2 ; case 11
	.short _02241680 - _0224143E - 2 ; case 12
_02241458:
	bl MOD18_022400A0
	str r0, [r4, #4]
	ldr r0, _0224169C ; =0x00000111
	mov r1, #0
	strb r1, [r4, r0]
	bl MOD18_022417B4
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02241472:
	mov r0, #1
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	ldr r0, _022416A0 ; =0x022513A0
	ldr r1, _022416A4 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1d
	bne _02241490
	mov r2, #2
	b _02241492
_02241490:
	mov r2, #0x1c
_02241492:
	mov r3, #0
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x17
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_02008F34
	ldr r1, _022416A0 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022414BE:
	ldr r0, _022416A0 ; =0x022513A0
	ldr r1, _022416A4 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1d
	bne _022414CE
	mov r2, #3
	b _022414D0
_022414CE:
	mov r2, #0x1d
_022414D0:
	mov r3, #0
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #7
	str r1, [sp, #8]
	mov r1, #4
	str r1, [sp, #0xc]
	mov r1, #0x5d
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_02008FEC
	ldr r1, _022416A0 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02241500:
	mov r0, #1
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	ldr r0, _022416A0 ; =0x022513A0
	ldr r1, _022416A4 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1d
	bne _0224151E
	mov r2, #1
	b _02241520
_0224151E:
	mov r2, #0x1b
_02241520:
	mov r3, #0
	str r3, [sp]
	mov r1, #2
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x5e
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _022416A0 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0224154C:
	ldr r0, _022416A0 ; =0x022513A0
	ldr r1, _022416A4 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1d
	bne _0224155C
	mov r2, #0
	b _0224155E
_0224155C:
	mov r2, #0x1a
_0224155E:
	mov r3, #0
	str r3, [sp]
	mov r1, #3
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x5f
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _022416A0 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0224158A:
	ldr r0, _022416A0 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009B78
	ldr r0, _022416A0 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	mov r0, #0x45
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl MOD18_022418DC
	add r0, r4, #0
	bl MOD18_02241364
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022415C0:
	ldr r0, _0224169C ; =0x00000111
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #0x1e
	bls _02241698
	mov r0, #1
	sub r1, r0, #5
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x4c
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #7
	str r0, [r4]
	mov r0, #0x46
	mov r1, #0
	lsl r0, r0, #2
	add sp, #0x10
	str r1, [r4, r0]
	pop {r4, pc}
_022415FA:
	ldr r0, _022416A0 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_02241AD0
	cmp r0, #0
	beq _02241622
	ldr r0, _022416A8 ; =0x00000113
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _02241618
	mov r0, #0xb
	str r0, [r4]
	b _02241622
_02241618:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02241622:
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0x3c
	bge _02241698
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0x3c
	bne _02241698
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r4, pc}
_02241642:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r4, pc}
_0224164E:
	bl FUN_02031190
	ldr r1, _022416A8 ; =0x00000113
	ldrb r1, [r4, r1]
	bl MOD18_022416B0
	add sp, #0x10
	pop {r4, pc}
_0224165E:
	ldr r0, _022416A8 ; =0x00000113
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _022416AC ; =0x00000112
	ldrb r0, [r4, r0]
	bl MOD18_0223FD8C
	ldr r0, _0224169C ; =0x00000111
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #0xc
	add sp, #0x10
	str r0, [r4]
	pop {r4, pc}
_02241680:
	ldr r0, _0224169C ; =0x00000111
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #8
	bls _02241698
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02241698:
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0224169C: .word 0x00000111
_022416A0: .word MOD18_022513A0
_022416A4: .word 0x00000B3B
_022416A8: .word 0x00000113
_022416AC: .word 0x00000112
	thumb_func_end MOD18_02241424

	thumb_func_start MOD18_022416B0
MOD18_022416B0: ; 0x022416B0
	push {r3, r4, lr}
	sub sp, #4
	ldr r0, _02241730 ; =0x022513A0
	ldr r2, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r2, r0]
	cmp r4, #0
	beq _0224172C
	ldr r0, _02241734 ; =0x00000113
	ldrb r2, [r4, r0]
	cmp r2, #0
	beq _022416D6
	cmp r1, #0
	beq _022416D6
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	bl MOD18_0223FD8C
_022416D6:
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	mov r0, #1
	mov r1, #0
	sub r2, r1, #4
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	mov r0, #0x45
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	bl MOD18_02241800
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _02241730 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	ldr r0, _02241730 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, _02241730 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_0224172C:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_02241730: .word MOD18_022513A0
_02241734: .word 0x00000113
	thumb_func_end MOD18_022416B0

	thumb_func_start MOD18_02241738
MOD18_02241738: ; 0x02241738
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x12
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #4
	add r7, r2, #0
	bl AllocFromHeap
	mov r2, #0x12
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _022417A0 ; =0x00000113
	add r1, r0, #0
	strb r6, [r4, r0]
	add r1, #9
	str r5, [r4, r1]
	ldr r1, _022417A4 ; =0x022513A0
	ldr r2, [r1, #4]
	ldr r1, _022417A8 ; =0x00000B3B
	ldrb r1, [r2, r1]
	cmp r1, #0x1d
	bne _02241774
	mov r1, #0x20
	add r0, r1, #0
	add r0, #0xf4
	b _02241778
_02241774:
	mov r1, #0x10
	add r0, r0, #1
_02241778:
	strb r1, [r4, r0]
	ldr r0, _022417AC ; =0x00000112
	mov r2, #0x64
	strb r7, [r4, r0]
	ldr r0, _022417A4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _022417B0 ; =MOD18_02241424
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _022417A4 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022417A0: .word 0x00000113
_022417A4: .word MOD18_022513A0
_022417A8: .word 0x00000B3B
_022417AC: .word 0x00000112
_022417B0: .word MOD18_02241424
	thumb_func_end MOD18_02241738

	thumb_func_start MOD18_022417B4
MOD18_022417B4: ; 0x022417B4
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _022417FC ; =0x022513A0
	mov r0, #0x20
	ldr r1, [r1, #4]
	mov r2, #4
	add r1, #0x48
	bl FUN_02008C9C
	ldr r1, _022417FC ; =0x022513A0
	ldr r2, [r1, #4]
	str r0, [r2, #0x44]
	ldr r0, [r1, #4]
	mov r2, #6
	add r0, #0x48
	mov r1, #0
	lsl r2, r2, #0x12
	bl FUN_02008D24
	mov r4, #0
	mov r7, #0x17
	ldr r6, _022417FC ; =0x022513A0
	add r5, r4, #0
	lsl r7, r7, #4
_022417E2:
	mov r0, #2
	add r1, r4, #0
	mov r2, #4
	bl FUN_02008DEC
	ldr r1, [r6, #4]
	add r4, r4, #1
	add r1, r1, r5
	add r5, r5, #4
	str r0, [r1, r7]
	cmp r4, #4
	blt _022417E2
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022417FC: .word MOD18_022513A0
	thumb_func_end MOD18_022417B4

	thumb_func_start MOD18_02241800
MOD18_02241800: ; 0x02241800
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	mov r4, #0
	cmp r6, #0
	ble _02241834
	ldr r7, _022418D8 ; =0x022513A0
	add r5, r4, #0
_0224180E:
	ldr r0, [r7, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224182C
	bl FUN_0201FFC8
	ldr r0, [r7, #4]
	mov r1, #0
	add r2, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	str r1, [r2, r0]
_0224182C:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r6
	blt _0224180E
_02241834:
	ldr r0, _022418D8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224185C
	bl FUN_02009530
	bl FUN_0201D2AC
	cmp r0, #0
	beq _0224185C
	ldr r0, _022418D8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009C0C
_0224185C:
	ldr r1, _022418D8 ; =0x022513A0
	mov r0, #0x19
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #4
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _0224188C
	bl FUN_02009530
	bl FUN_0201E1B4
	cmp r0, #0
	beq _0224188C
	ldr r0, _022418D8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009E04
_0224188C:
	ldr r6, _022418D8 ; =0x022513A0
	mov r5, #0
	mov r0, #0x65
	ldr r1, [r6, #4]
	lsl r0, r0, #2
	str r5, [r1, r0]
	add r4, r5, #0
	add r7, r5, #0
_0224189C:
	ldr r0, [r6, #4]
	add r1, r0, r4
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022418AE
	bl FUN_02008E2C
_022418AE:
	ldr r0, [r6, #4]
	add r5, r5, #1
	add r1, r0, r4
	mov r0, #0x17
	lsl r0, r0, #4
	add r4, r4, #4
	str r7, [r1, r0]
	cmp r5, #4
	blt _0224189C
	ldr r0, _022418D8 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	cmp r0, #0
	beq _022418CE
	bl FUN_0201FD58
_022418CE:
	ldr r0, _022418D8 ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	str r1, [r0, #0x44]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022418D8: .word MOD18_022513A0
	thumb_func_end MOD18_02241800

	thumb_func_start MOD18_022418DC
MOD18_022418DC: ; 0x022418DC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	add r7, r0, #0
	ldr r0, _022419D4 ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	sub r2, r1, #1
	str r1, [sp]
	str r2, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	mov r3, #0x17
	str r1, [sp, #0x10]
	lsl r3, r3, #4
	ldr r2, [r0, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r0, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r0, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r0, r2]
	add r3, #0x64
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r0, r3
	add r2, r1, #0
	add r3, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	ldr r4, _022419D4 ; =0x022513A0
	mov r6, #0
	ldr r1, [r4, #4]
	ldr r0, [r1, #0x44]
	str r0, [sp, #0x2c]
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x30]
	mov r1, #2
	mov r0, #6
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	lsr r0, r1, #5
	str r1, [sp, #0x34]
	str r6, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r6, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #4
	str r6, [sp, #0x50]
	str r0, [sp, #0x58]
	cmp r7, #0
	ble _022419BE
	add r5, r6, #0
_0224195E:
	mov r0, #0x4b
	lsl r0, r0, #0xe
	str r0, [sp, #0x34]
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	bl FUN_0201FE94
	ldr r1, [r4, #4]
	add r2, r1, r5
	mov r1, #0x7e
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020130
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200BC
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020208
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020238
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, r7
	blt _0224195E
_022419BE:
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_022419D4: .word MOD18_022513A0
	thumb_func_end MOD18_022418DC

	thumb_func_start MOD18_022419D8
MOD18_022419D8: ; 0x022419D8
	push {r4, lr}
	lsl r4, r0, #2
	ldr r0, _02241A00 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r4
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _022419FE
	bl FUN_0201FFC8
	ldr r0, _02241A00 ; =0x022513A0
	mov r2, #0
	ldr r0, [r0, #4]
	add r1, r0, r4
	mov r0, #0x7e
	lsl r0, r0, #2
	str r2, [r1, r0]
_022419FE:
	pop {r4, pc}
	.align 2, 0
_02241A00: .word MOD18_022513A0
	thumb_func_end MOD18_022419D8

	thumb_func_start MOD18_02241A04
MOD18_02241A04: ; 0x02241A04
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r3, r0, #0
	add r0, r1, #0
	lsl r5, r3, #2
	add r1, r0, r5
	add r1, #0x48
	ldrh r1, [r1]
	str r1, [sp]
	add r1, r0, r5
	add r1, #0x4a
	ldrh r7, [r1]
	cmp r2, #0
	bne _02241A30
	add r6, r0, #0
	add r6, #8
	lsl r4, r3, #1
	mov r1, #1
	ldrh r2, [r6, r4]
	lsl r1, r1, #0xa
	add r1, r2, r1
	strh r1, [r6, r4]
_02241A30:
	lsl r1, r3, #1
	add r0, r0, r1
	ldrh r0, [r0, #8]
	mov r2, #0x12
	lsl r2, r2, #0xa
	asr r0, r0, #4
	lsl r6, r0, #1
	ldr r0, _02241AAC ; =FX_SinCosTable_
	lsl r1, r6, #1
	ldrsh r0, [r0, r1]
	mov r3, #0
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsr r4, r2, #0xc
	lsl r0, r1, #0x14
	orr r4, r0
	add r0, r6, #1
	lsl r1, r0, #1
	ldr r0, _02241AAC ; =FX_SinCosTable_
	mov r2, #0xa
	ldrsh r0, [r0, r1]
	lsl r2, r2, #0xa
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	bpl _02241A82
	neg r1, r1
_02241A82:
	ldr r0, _02241AB0 ; =0x022513A0
	ldr r2, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	add r0, r2, r0
	ldr r2, [r0, r5]
	cmp r2, #0
	beq _02241AA8
	ldr r2, [sp]
	lsl r2, r2, #0xc
	add r2, r4, r2
	str r2, [sp, #4]
	lsl r2, r7, #0xc
	add r1, r1, r2
	str r1, [sp, #8]
	ldr r0, [r0, r5]
	add r1, sp, #4
	bl FUN_02020044
_02241AA8:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02241AAC: .word FX_SinCosTable_
_02241AB0: .word MOD18_022513A0
	thumb_func_end MOD18_02241A04

	thumb_func_start MOD18_02241AB4
MOD18_02241AB4: ; 0x02241AB4
	cmp r0, #0
	bne _02241AC4
	ldr r1, _02241AC8 ; =0x022513A0
	mov r0, #0
	ldrsb r2, [r1, r0]
	ldr r1, [r1, #4]
	ldr r0, _02241ACC ; =0x00000B3A
	strb r2, [r1, r0]
_02241AC4:
	bx lr
	nop
_02241AC8: .word MOD18_022513A0
_02241ACC: .word 0x00000B3A
	thumb_func_end MOD18_02241AB4

	thumb_func_start MOD18_02241AD0
MOD18_02241AD0: ; 0x02241AD0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r5, r1, #0
	ldr r1, _02241D20 ; =0x022513A0
	ldr r2, _02241D24 ; =MOD18_02241AB4
	mov r3, #0
	mov r0, #2
	bl FUN_02004928
	ldr r0, _02241D28 ; =0x022513A0
	ldr r2, [r0, #4]
	ldr r0, _02241D2C ; =0x00000B3B
	ldrb r1, [r2, r0]
	cmp r1, #0x1d
	bne _02241AFE
	sub r0, r0, #1
	ldrsb r0, [r2, r0]
	bl abs
	mov r1, #0x21
	bl _s32_div_f
	b _02241B0C
_02241AFE:
	sub r0, r0, #1
	ldrsb r0, [r2, r0]
	bl abs
	mov r1, #0x19
	bl _s32_div_f
_02241B0C:
	mov r1, #0x11
	lsl r1, r1, #4
	ldrb r1, [r5, r1]
	mov r2, #0x7e
	lsl r2, r2, #2
	add r1, r5, r1
	add r1, #0xc8
	strb r0, [r1]
	ldr r0, _02241D28 ; =0x022513A0
	add r1, r2, #0
	mov r4, #0
	ldr r0, [r0, #4]
	sub r1, #0xe4
	b _02241B34
_02241B28:
	lsl r3, r4, #2
	add r3, r0, r3
	ldr r3, [r3, r2]
	cmp r3, #0
	bne _02241B3A
	add r4, r4, #1
_02241B34:
	ldrb r3, [r5, r1]
	cmp r4, r3
	blt _02241B28
_02241B3A:
	mov r0, #0x45
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	cmp r4, r0
	bne _02241B4A
	add sp, #0x18
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02241B4A:
	add r0, r5, #0
	str r0, [sp, #0x10]
	add r0, #0x4a
	add r7, r5, #0
	mov r4, #0
	str r0, [sp, #0x10]
	add r7, #0x48
	b _02241CEE
_02241B5A:
	lsl r2, r4, #2
	add r0, r5, r2
	add r0, #0x48
	ldrh r1, [r0]
	cmp r1, #0
	beq _02241B7C
	mov r0, #1
	lsl r0, r0, #8
	cmp r1, r0
	bhs _02241B7C
	add r0, r5, r2
	add r0, #0x4a
	ldrh r0, [r0]
	cmp r0, #0
	beq _02241B7C
	cmp r0, #0xc0
	blo _02241B84
_02241B7C:
	add r0, r4, #0
	bl MOD18_022419D8
	b _02241CEC
_02241B84:
	mov r0, #0x11
	lsl r0, r0, #4
	ldrb r1, [r5, r0]
	add r0, r5, r4
	add r0, #0xf0
	ldrb r0, [r0]
	sub r0, r1, r0
	bpl _02241B96
	add r0, #0x28
_02241B96:
	add r0, r5, r0
	add r0, #0xc8
	lsl r1, r4, #2
	ldrb r6, [r0]
	add r0, r5, r1
	add r0, #0x48
	add r1, r5, r1
	ldrh r0, [r0]
	add r1, #0x4a
	ldrh r1, [r1]
	sub r0, #0x80
	lsl r0, r0, #0xc
	sub r1, #0x60
	str r0, [sp, #4]
	lsl r0, r1, #0xc
	asr r1, r0, #0x1f
	add r2, r0, #0
	add r3, r1, #0
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02241D30 ; =0x00000000
	adc r1, r2
	lsr r0, r0, #0xc
	lsl r1, r1, #0x14
	str r0, [sp, #8]
	orr r0, r1
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	asr r1, r0, #0x1f
	add r2, r0, #0
	add r3, r1, #0
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02241D30 ; =0x00000000
	adc r1, r2
	lsr r2, r0, #0xc
	lsl r1, r1, #0x14
	ldr r0, [sp, #8]
	orr r2, r1
	add r0, r2, r0
	bl FX_Sqrt
	str r0, [sp, #0xc]
	cmp r6, #0
	bne _02241C2A
	mov r1, #0xa
	lsl r1, r1, #0x10
	bl FX_Div
	mov r2, #0x26
	asr r1, r0, #0x1f
	lsl r2, r2, #0xc
	mov r3, #0
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02241D30 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0xc
	add r0, r5, r4
	add r0, #0xf0
	strb r1, [r0]
	b _02241CE2
_02241C2A:
	lsl r2, r4, #2
	add r0, r5, r2
	add r0, #0x48
	ldrh r1, [r0]
	add r0, r5, r2
	add r0, #0x4a
	ldrh r0, [r0]
	sub r1, #0x80
	sub r0, #0x60
	bne _02241C50
	cmp r1, #0
	ldrh r0, [r7, r2]
	bge _02241C4A
	sub r0, r0, r6
	strh r0, [r7, r2]
	b _02241CE2
_02241C4A:
	add r0, r0, r6
	strh r0, [r7, r2]
	b _02241CE2
_02241C50:
	cmp r1, #0
	bne _02241C70
	cmp r0, #0
	bge _02241C64
	ldr r0, [sp, #0x10]
	ldrh r0, [r0, r2]
	sub r1, r0, r6
	ldr r0, [sp, #0x10]
	strh r1, [r0, r2]
	b _02241CE2
_02241C64:
	ldr r0, [sp, #0x10]
	ldrh r0, [r0, r2]
	add r1, r0, r6
	ldr r0, [sp, #0x10]
	strh r1, [r0, r2]
	b _02241CE2
_02241C70:
	bl FX_Atan2
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	lsl r1, r6, #0xc
	add r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #0x14]
	ldr r2, [sp]
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _02241D34 ; =FX_SinCosTable_
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02241D30 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0xc
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r2, [sp]
	add r1, #0x60
	add r0, #0x4a
	strh r1, [r0]
	ldr r0, [sp, #0x14]
	asr r3, r2, #0x1f
	asr r0, r0, #4
	lsl r0, r0, #1
	add r0, r0, #1
	lsl r1, r0, #1
	ldr r0, _02241D34 ; =FX_SinCosTable_
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02241D30 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0xc
	lsl r0, r4, #2
	add r0, r5, r0
	add r1, #0x80
	add r0, #0x48
	strh r1, [r0]
_02241CE2:
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD18_02241A04
_02241CEC:
	add r4, r4, #1
_02241CEE:
	mov r0, #0x45
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	cmp r4, r0
	bge _02241CFA
	b _02241B5A
_02241CFA:
	mov r0, #0x11
	lsl r0, r0, #4
	ldrb r1, [r5, r0]
	add r1, r1, #1
	strb r1, [r5, r0]
	ldrb r1, [r5, r0]
	cmp r1, #0x28
	blo _02241D0E
	mov r1, #0
	strb r1, [r5, r0]
_02241D0E:
	ldr r0, _02241D28 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	bl FUN_0201FDEC
	mov r0, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02241D20: .word MOD18_022513A0
_02241D24: .word MOD18_02241AB4
_02241D28: .word MOD18_022513A0
_02241D2C: .word 0x00000B3B
_02241D30: .word 0x00000000
_02241D34: .word FX_SinCosTable_
	thumb_func_end MOD18_02241AD0

	thumb_func_start MOD18_02241D38
MOD18_02241D38: ; 0x02241D38
	push {r3, lr}
	ldr r1, _02241D4C ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0x2a
	lsl r1, r1, #4
	ldr r1, [r2, r1]
	cmp r1, #0
	beq _02241D4A
	blx r1
_02241D4A:
	pop {r3, pc}
	.align 2, 0
_02241D4C: .word MOD18_022513A0
	thumb_func_end MOD18_02241D38

	thumb_func_start MOD18_02241D50
MOD18_02241D50: ; 0x02241D50
	ldr r0, _02241D64 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02241D68 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0x17
	bne _02241D60
	mov r0, #0x14
	bx lr
_02241D60:
	mov r0, #7
	bx lr
	.align 2, 0
_02241D64: .word MOD18_022513A0
_02241D68: .word 0x00000B3B
	thumb_func_end MOD18_02241D50

	thumb_func_start MOD18_02241D6C
MOD18_02241D6C: ; 0x02241D6C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	add r5, r0, #0
	mov r0, #0
	str r0, [sp, #0xc]
	add r0, sp, #0x24
	bl FUN_020312BC
	bl MOD18_02241D50
	str r0, [sp, #4]
	ldr r0, _02241F00 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02241F04 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0x17
	bne _02241DB2
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	bl _ll_mul
	ldr r2, [sp, #0x34]
	ldr r3, [sp, #0x38]
	add r0, r2, r0
	adc r3, r1
	mov r1, #0
	str r0, [sp, #0x24]
	lsr r0, r3, #0x1f
	lsl r1, r1, #1
	orr r1, r0
	add r0, r1, #1
	str r3, [sp, #0x28]
	str r0, [sp, #0xc]
_02241DB2:
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	bl _ll_mul
	ldr r2, [sp, #0x34]
	ldr r3, [sp, #0x38]
	add r0, r2, r0
	adc r3, r1
	str r0, [sp, #0x24]
	str r3, [sp, #0x28]
	add r0, r3, #0
	mov r1, #0
	mov r2, #3
	mov r3, #0
	bl _ll_mul
	ldr r0, [sp, #0xc]
	mov r6, #0
	add r0, r0, r1
	add r0, r0, #5
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	cmp r0, #0
	bgt _02241DE8
	b _02241EFA
_02241DE8:
	mov r0, #0
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	str r0, [sp, #0x20]
_02241DF2:
	ldr r0, [sp, #4]
	sub r0, r0, r6
	sub r4, r0, #1
	ldr r0, [sp, #0xc]
	cmp r6, r0
	bge _02241E06
	add r1, r5, r4
	mov r0, #0
	strb r0, [r1, #8]
	b _02241E1A
_02241E06:
	ldr r0, [sp, #8]
	cmp r6, r0
	bge _02241E14
	add r1, r5, r4
	mov r0, #1
	strb r0, [r1, #8]
	b _02241E1A
_02241E14:
	add r1, r5, r4
	mov r0, #2
	strb r0, [r1, #8]
_02241E1A:
	ldrb r0, [r1, #8]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	lsl r1, r0, #2
	ldr r0, _02241F08 ; =0x022500C0
	ldr r0, [r0, r1]
	ldr r1, [sp, #0x30]
	str r0, [sp]
	lsl r7, r0, #1
	mov r0, #0xc0
	sub r0, r0, r7
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	bl _ll_mul
	add r3, r1, #0
	add r2, r0, #0
	ldr r1, [sp, #0x34]
	ldr r0, [sp, #0x38]
	add r1, r1, r2
	adc r0, r3
	str r1, [sp, #0x24]
	mov r1, #1
	lsl r1, r1, #8
	str r0, [sp, #0x28]
	sub r2, r1, r7
	beq _02241E5A
	ldr r1, [sp, #0x14]
	mov r3, #0
	bl _ll_mul
	add r0, r1, #0
_02241E5A:
	lsl r1, r4, #3
	add r7, r5, r1
	ldr r1, [sp]
	add r0, r1, r0
	lsl r0, r0, #0xc
	str r0, [r7, #0x44]
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	bl _ll_mul
	add r2, r0, #0
	ldr r0, [sp, #0x34]
	ldr r3, [sp, #0x38]
	add r0, r0, r2
	str r0, [sp, #0x24]
	adc r3, r1
	ldr r0, [sp, #0x10]
	str r3, [sp, #0x28]
	cmp r0, #0
	beq _02241E94
	ldr r1, [sp, #0x18]
	add r0, r3, #0
	ldr r2, [sp, #0x10]
	mov r3, #0
	bl _ll_mul
	add r3, r1, #0
_02241E94:
	ldr r0, [sp]
	add r0, r0, r3
	lsl r0, r0, #0xc
	str r0, [r7, #0x48]
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	bl _ll_mul
	ldr r3, [sp, #0x34]
	ldr r2, [sp, #0x38]
	add r0, r3, r0
	adc r2, r1
	str r0, [sp, #0x24]
	lsl r0, r4, #1
	add r4, r5, r0
	str r2, [sp, #0x28]
	add r0, r2, #0
	ldr r1, [sp, #0x1c]
	ldr r2, _02241F0C ; =0x0000FFFF
	mov r3, #0
	bl _ll_mul
	strh r1, [r4, #0x1c]
	ldr r0, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	bl _ll_mul
	ldr r2, [sp, #0x34]
	ldr r3, [sp, #0x38]
	add r0, r2, r0
	adc r3, r1
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x20]
	ldr r2, _02241F0C ; =0x0000FFFF
	str r3, [sp, #0x28]
	add r0, r3, #0
	mov r3, #0
	bl _ll_mul
	mov r0, #0x4d
	lsl r0, r0, #2
	strh r1, [r4, r0]
	ldr r0, [sp, #4]
	add r6, r6, #1
	cmp r6, r0
	bge _02241EFA
	b _02241DF2
_02241EFA:
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_02241F00: .word MOD18_022513A0
_02241F04: .word 0x00000B3B
_02241F08: .word MOD18_022500C0
_02241F0C: .word 0x0000FFFF
	thumb_func_end MOD18_02241D6C

	thumb_func_start MOD18_02241F10
MOD18_02241F10: ; 0x02241F10
	push {r4, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0xc
	bls _02241F1E
	b _02242166
_02241F1E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02241F2A: ; jump table
	.short _02241F44 - _02241F2A - 2 ; case 0
	.short _02241F60 - _02241F2A - 2 ; case 1
	.short _02241FA0 - _02241F2A - 2 ; case 2
	.short _02241FD4 - _02241F2A - 2 ; case 3
	.short _02242014 - _02241F2A - 2 ; case 4
	.short _02242044 - _02241F2A - 2 ; case 5
	.short _0224205A - _02241F2A - 2 ; case 6
	.short _0224209A - _02241F2A - 2 ; case 7
	.short _022420FE - _02241F2A - 2 ; case 8
	.short _02242114 - _02241F2A - 2 ; case 9
	.short _02242166 - _02241F2A - 2 ; case 10
	.short _02242128 - _02241F2A - 2 ; case 11
	.short _0224214C - _02241F2A - 2 ; case 12
_02241F44:
	bl MOD18_022400A0
	str r0, [r4, #4]
	mov r0, #0x57
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r4, r0]
	bl MOD18_022417B4
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02241F60:
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, _0224216C ; =0x022513A0
	mov r2, #6
	ldr r1, [r0, #4]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_02008F34
	ldr r1, _0224216C ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #1
	str r0, [sp]
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02241FA0:
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r2, #7
	str r2, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, _0224216C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_02008FEC
	ldr r1, _0224216C ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02241FD4:
	mov r0, #1
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, _0224216C ; =0x022513A0
	mov r2, #5
	ldr r1, [r0, #4]
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _0224216C ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02242014:
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r2, #4
	ldr r0, _0224216C ; =0x022513A0
	str r2, [sp, #8]
	ldr r1, [r0, #4]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _0224216C ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02242044:
	add r0, r4, #0
	bl MOD18_02241D6C
	add r0, r4, #0
	bl MOD18_022421D4
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0224205A:
	mov r0, #0x57
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #0x1e
	bls _02242166
	mov r1, #3
	ldr r0, _02242170 ; =0x0400006C
	mvn r1, r1
	bl GXx_SetMasterBrightness_
	mov r0, #7
	str r0, [r4]
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x4d
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #0x16
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	mov r0, #0x66
	lsl r0, r0, #4
	bl FUN_020054C8
	add sp, #0x10
	pop {r4, pc}
_0224209A:
	mov r0, #7
	str r0, [sp]
	ldr r0, _02242174 ; =0x04000050
	mov r1, #0x10
	mov r2, #1
	mov r3, #0xe
	bl G2x_SetBlendAlpha_
	ldr r0, _0224216C ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_022423B0
	cmp r0, #0
	beq _022420DE
	mov r0, #0x66
	lsl r0, r0, #4
	mov r1, #0
	bl FUN_020054F0
	ldr r0, _02242178 ; =0x0000015E
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _022420D4
	mov r0, #0xb
	str r0, [r4]
	b _022420DE
_022420D4:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_022420DE:
	mov r0, #0x16
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	cmp r1, #0x3c
	bge _02242166
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0x3c
	bne _02242166
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r4, pc}
_022420FE:
	mov r0, #0x66
	lsl r0, r0, #4
	mov r1, #0
	bl FUN_020054F0
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r4, pc}
_02242114:
	mov r0, #0xa
	str r0, [r4]
	bl FUN_02031190
	ldr r1, _02242178 ; =0x0000015E
	ldrb r1, [r4, r1]
	bl MOD18_022425D4
	add sp, #0x10
	pop {r4, pc}
_02242128:
	ldr r0, _02242178 ; =0x0000015E
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _0224217C ; =0x0000015D
	ldrb r0, [r4, r0]
	bl MOD18_0223FD8C
	mov r0, #0x57
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r4, r0]
	mov r0, #0xc
	add sp, #0x10
	str r0, [r4]
	pop {r4, pc}
_0224214C:
	mov r0, #0x57
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #8
	bls _02242166
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02242166:
	add sp, #0x10
	pop {r4, pc}
	nop
_0224216C: .word MOD18_022513A0
_02242170: .word 0x0400006C
_02242174: .word 0x04000050
_02242178: .word 0x0000015E
_0224217C: .word 0x0000015D
	thumb_func_end MOD18_02241F10

	thumb_func_start MOD18_02242180
MOD18_02242180: ; 0x02242180
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x59
	mov r0, #4
	lsl r1, r1, #2
	add r6, r2, #0
	bl AllocFromHeapAtEnd
	mov r2, #0x59
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _022421C4 ; =0x0000015E
	mov r2, #0x64
	strb r5, [r4, r0]
	ldr r0, _022421C8 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _022421CC ; =MOD18_02241F10
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _022421C8 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, _022421D0 ; =0x0000015D
	strb r6, [r4, r0]
	pop {r4, r5, r6, pc}
	.align 2, 0
_022421C4: .word 0x0000015E
_022421C8: .word MOD18_022513A0
_022421CC: .word MOD18_02241F10
_022421D0: .word 0x0000015D
	thumb_func_end MOD18_02242180

	thumb_func_start MOD18_022421D4
MOD18_022421D4: ; 0x022421D4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	str r0, [sp, #0x2c]
	ldr r0, _0224231C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009B78
	ldr r0, _0224231C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	ldr r0, _0224231C ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	mov r3, #0x17
	str r1, [sp]
	sub r2, r1, #1
	str r2, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	lsl r3, r3, #4
	ldr r2, [r0, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r0, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r0, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r0, r2]
	add r3, #0x64
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r0, r3
	add r2, r1, #0
	add r3, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	ldr r0, _0224231C ; =0x022513A0
	mov r4, #0
	ldr r1, [r0, #4]
	ldr r0, [r1, #0x44]
	str r0, [sp, #0x30]
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x34]
	mov r1, #2
	mov r0, #6
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	str r0, [sp, #0x3c]
	lsr r0, r1, #5
	str r1, [sp, #0x38]
	str r4, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	add r0, sp, #0x30
	strh r4, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x58]
	mov r0, #4
	str r4, [sp, #0x54]
	str r0, [sp, #0x5c]
	bl MOD18_02241D50
	cmp r0, #0
	ble _02242308
	add r5, r4, #0
	ldr r6, _0224231C ; =0x022513A0
	add r7, r5, #0
_0224227A:
	mov r0, #0x4b
	lsl r0, r0, #0xe
	str r0, [sp, #0x38]
	str r0, [sp, #0x3c]
	add r0, sp, #0x30
	bl FUN_0201FE94
	ldr r1, [r6, #4]
	add r2, r1, r5
	mov r1, #0x7e
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200EC
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r1, [sp, #0x2c]
	add r1, r1, r4
	ldrb r1, [r1, #8]
	lsl r1, r1, #1
	bl FUN_02020130
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	lsl r1, r7, #0x10
	lsr r1, r1, #0x10
	bl FUN_02020208
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020398
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020238
	add r5, r5, #4
	add r7, r7, #4
	add r4, r4, #1
	bl MOD18_02241D50
	cmp r4, r0
	blt _0224227A
_02242308:
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224231C: .word MOD18_022513A0
	thumb_func_end MOD18_022421D4

	thumb_func_start MOD18_02242320
MOD18_02242320: ; 0x02242320
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _022423A8 ; =0x022513A0
	add r4, r1, #0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	add r1, r1, r0
	lsl r0, r5, #2
	ldr r2, [r1, r0]
	cmp r2, #0
	beq _022423A4
	lsl r2, r5, #3
	add r3, r4, r2
	ldr r2, [r3, #0x44]
	str r2, [sp]
	ldr r2, [r3, #0x48]
	str r2, [sp, #4]
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
	mov r0, #0x4d
	lsl r0, r0, #2
	add r2, r4, r0
	lsl r1, r5, #1
	mov r3, #0x64
	add r4, r5, #0
	mul r4, r3
	mov r3, #0x25
	lsl r3, r3, #4
	ldrh r0, [r2, r1]
	add r3, r4, r3
	add r0, r0, r3
	strh r0, [r2, r1]
	ldrh r0, [r2, r1]
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _022423AC ; =FX_SinCosTable_
	ldrsh r1, [r0, r1]
	mov r0, #1
	lsl r0, r0, #0xc
	add r0, r1, r0
	lsl r0, r0, #0x10
	mov r1, #5
	asr r0, r0, #0x10
	lsl r1, r1, #0xe
	bl FX_Div
	mov r1, #1
	lsl r1, r1, #0xc
	sub r0, r1, r0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _022423A8 ; =0x022513A0
	ldr r1, [r0, #4]
	lsl r0, r5, #2
	add r1, r1, r0
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020064
_022423A4:
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
_022423A8: .word MOD18_022513A0
_022423AC: .word FX_SinCosTable_
	thumb_func_end MOD18_02242320

	thumb_func_start MOD18_022423B0
MOD18_022423B0: ; 0x022423B0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r6, #0
	str r1, [sp]
	add r4, r6, #0
	bl MOD18_02241D50
	cmp r0, #0
	ble _022423E6
	ldr r5, [sp]
_022423C4:
	add r0, r5, #0
	add r0, #0xe4
	ldr r0, [r0]
	cmp r0, #0
	bne _022423D8
	ldr r1, [sp]
	add r0, r4, #0
	bl MOD18_02242320
	b _022423DA
_022423D8:
	add r6, r6, #1
_022423DA:
	add r5, r5, #4
	add r4, r4, #1
	bl MOD18_02241D50
	cmp r4, r0
	blt _022423C4
_022423E6:
	bl MOD18_02241D50
	cmp r6, r0
	bne _022423F4
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022423F4:
	ldr r0, _02242580 ; =gMain + 0x40
	ldrh r0, [r0, #0x20]
	cmp r0, #0
	beq _022424C4
	mov r5, #0
	bl MOD18_02241D50
	cmp r0, #0
	ble _022424C4
	ldr r6, [sp]
	add r4, r6, #0
_0224240A:
	add r0, r6, #0
	add r0, #0xe4
	ldr r0, [r0]
	cmp r0, #0
	bne _022424B6
	ldr r0, _02242580 ; =gMain + 0x40
	ldrh r0, [r0, #0x1e]
	lsl r1, r0, #0xc
	ldr r0, [r4, #0x48]
	sub r0, r1, r0
	str r0, [sp, #0xc]
	asr r7, r0, #0x1f
	ldr r0, _02242580 ; =gMain + 0x40
	ldrh r0, [r0, #0x1c]
	lsl r1, r0, #0xc
	ldr r0, [r4, #0x44]
	sub r0, r1, r0
	asr r1, r0, #0x1f
	add r2, r0, #0
	add r3, r1, #0
	bl _ll_mul
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	str r1, [sp, #8]
	add r1, r7, #0
	add r2, r0, #0
	add r3, r7, #0
	bl _ll_mul
	add r7, r0, #0
	add r3, r1, #0
	mov r0, #2
	ldr r1, [sp, #0x10]
	lsl r0, r0, #0xa
	add r2, r1, r0
	ldr r1, [sp, #8]
	ldr r0, _02242584 ; =0x00000000
	adc r1, r0
	str r1, [sp, #8]
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	mov r0, #2
	lsl r0, r0, #0xa
	ldr r2, _02242584 ; =0x00000000
	add r0, r7, r0
	adc r3, r2
	lsl r2, r3, #0x14
	lsr r0, r0, #0xc
	orr r0, r2
	add r0, r1, r0
	bl FX_Sqrt
	ldr r1, [sp]
	add r1, r1, r5
	ldrb r1, [r1, #8]
	lsl r2, r1, #2
	ldr r1, _02242588 ; =0x022500C0
	ldr r1, [r1, r2]
	lsl r1, r1, #0xc
	cmp r1, r0
	ble _022424B6
	ldr r0, _0224258C ; =0x00000626
	bl FUN_020054C8
	ldr r0, _02242590 ; =0x022513A0
	lsl r4, r5, #2
	ldr r0, [r0, #4]
	add r1, r0, r4
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r1, [sp]
	add r1, r1, r5
	ldrb r1, [r1, #8]
	lsl r1, r1, #1
	add r1, r1, #1
	bl FUN_02020130
	ldr r0, [sp]
	mov r1, #1
	add r0, r0, r4
	add r0, #0xe4
	str r1, [r0]
	b _022424C4
_022424B6:
	add r6, r6, #4
	add r4, #8
	add r5, r5, #1
	bl MOD18_02241D50
	cmp r5, r0
	blt _0224240A
_022424C4:
	mov r6, #0
	bl MOD18_02241D50
	cmp r0, #0
	ble _02242570
	ldr r7, [sp]
	add r4, r7, #0
	add r5, r7, #0
_022424D4:
	add r0, r7, #0
	add r0, #0xe4
	ldr r0, [r0]
	cmp r0, #0
	bne _02242560
	ldrh r0, [r4, #0x1c]
	asr r0, r0, #4
	lsl r1, r0, #2
	ldr r0, _02242594 ; =FX_SinCosTable_
	ldrsh r1, [r0, r1]
	ldr r0, [r5, #0x48]
	sub r0, r0, r1
	str r0, [r5, #0x48]
	ldrh r1, [r4, #0x1c]
	ldr r0, [r5, #0x44]
	asr r1, r1, #4
	lsl r2, r1, #2
	ldr r1, _02242594 ; =FX_SinCosTable_
	add r2, r1, r2
	mov r1, #2
	ldrsh r1, [r2, r1]
	add r0, r0, r1
	str r0, [r5, #0x44]
	ldr r0, [sp]
	add r0, r0, r6
	ldrb r0, [r0, #8]
	lsl r1, r0, #2
	ldr r0, _02242588 ; =0x022500C0
	ldr r1, [r0, r1]
	ldr r0, [r5, #0x48]
	lsl r3, r1, #0xc
	cmp r0, r3
	bge _02242520
	ldrh r2, [r4, #0x1c]
	ldr r0, _02242598 ; =0x0000FFFF
	sub r0, r0, r2
	strh r0, [r4, #0x1c]
	b _02242532
_02242520:
	mov r2, #0xc0
	sub r2, r2, r1
	lsl r2, r2, #0xc
	cmp r0, r2
	blt _02242532
	ldrh r2, [r4, #0x1c]
	ldr r0, _02242598 ; =0x0000FFFF
	sub r0, r0, r2
	strh r0, [r4, #0x1c]
_02242532:
	ldr r0, [r5, #0x44]
	cmp r0, r3
	bge _02242548
	ldrh r1, [r4, #0x1c]
	mov r0, #2
	lsl r0, r0, #0xe
	sub r1, r1, r0
	ldr r0, _02242598 ; =0x0000FFFF
	sub r0, r0, r1
	strh r0, [r4, #0x1c]
	b _02242560
_02242548:
	mov r2, #1
	lsl r2, r2, #8
	sub r1, r2, r1
	lsl r1, r1, #0xc
	cmp r0, r1
	blt _02242560
	ldrh r1, [r4, #0x1c]
	lsl r0, r2, #7
	sub r1, r1, r0
	ldr r0, _02242598 ; =0x0000FFFF
	sub r0, r0, r1
	strh r0, [r4, #0x1c]
_02242560:
	add r7, r7, #4
	add r4, r4, #2
	add r5, #8
	add r6, r6, #1
	bl MOD18_02241D50
	cmp r6, r0
	blt _022424D4
_02242570:
	ldr r0, _02242590 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	bl FUN_0201FDEC
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02242580: .word gMain + 0x40
_02242584: .word 0x00000000
_02242588: .word MOD18_022500C0
_0224258C: .word 0x00000626
_02242590: .word MOD18_022513A0
_02242594: .word FX_SinCosTable_
_02242598: .word 0x0000FFFF
	thumb_func_end MOD18_022423B0

	thumb_func_start MOD18_0224259C
MOD18_0224259C: ; 0x0224259C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _022425C2
	ldr r0, _022425C4 ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	add r2, r6, #0
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_02242180
_022425C2:
	pop {r4, r5, r6, pc}
	.align 2, 0
_022425C4: .word MOD18_022513A0
	thumb_func_end MOD18_0224259C

	thumb_func_start MOD18_022425C8
MOD18_022425C8: ; 0x022425C8
	ldr r3, _022425D0 ; =FUN_0204E758
	mov r1, #2
	bx r3
	nop
_022425D0: .word FUN_0204E758
	thumb_func_end MOD18_022425C8

	thumb_func_start MOD18_022425D4
MOD18_022425D4: ; 0x022425D4
	push {r3, r4, r5, lr}
	ldr r0, _02242658 ; =0x022513A0
	add r5, r1, #0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	cmp r4, #0
	beq _02242656
	mov r0, #0x66
	lsl r0, r0, #4
	mov r1, #0
	bl FUN_020054F0
	ldr r0, _0224265C ; =0x0000015E
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _02242604
	cmp r5, #0
	beq _02242604
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	bl MOD18_0223FD8C
_02242604:
	ldr r1, _02242660 ; =0x04000050
	mov r0, #0
	strh r0, [r1]
	mov r1, #1
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02242664 ; =0x0400006C
	mov r1, #0
	bl GXx_SetMasterBrightness_
	bl MOD18_02241D50
	bl MOD18_02241800
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _02242658 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	ldr r0, _02242658 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FreeToHeap
	ldr r1, _02242658 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02242656:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02242658: .word MOD18_022513A0
_0224265C: .word 0x0000015E
_02242660: .word 0x04000050
_02242664: .word 0x0400006C
	thumb_func_end MOD18_022425D4

	thumb_func_start MOD18_02242668
MOD18_02242668: ; 0x02242668
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	ldr r0, _02242798 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009B78
	ldr r0, _02242798 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	ldr r0, _02242798 ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	mov r3, #0x17
	str r1, [sp]
	sub r2, r1, #1
	str r2, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	lsl r3, r3, #4
	ldr r2, [r0, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r0, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r0, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r0, r2]
	add r3, #0x64
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r0, r3
	add r2, r1, #0
	add r3, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	ldr r4, _02242798 ; =0x022513A0
	mov r6, #0
	ldr r1, [r4, #4]
	mov r7, #0x19
	ldr r0, [r1, #0x44]
	add r5, r6, #0
	str r0, [sp, #0x2c]
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x30]
	mov r1, #2
	mov r0, #6
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	lsr r0, r1, #5
	str r1, [sp, #0x34]
	str r6, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r6, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #4
	str r6, [sp, #0x50]
	str r0, [sp, #0x58]
	lsl r7, r7, #0xe
_02242704:
	add r0, sp, #0x2c
	str r7, [sp, #0x34]
	str r7, [sp, #0x38]
	bl FUN_0201FE94
	ldr r1, [r4, #4]
	add r2, r1, r5
	mov r1, #0x7e
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02020130
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020208
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0xf
	sub r1, r1, r6
	bl FUN_02020310
	ldr r0, [r4, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020238
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #0xf
	blt _02242704
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_02242798: .word MOD18_022513A0
	thumb_func_end MOD18_02242668

	thumb_func_start MOD18_0224279C
MOD18_0224279C: ; 0x0224279C
	push {r4, lr}
	lsl r1, r1, #2
	add r4, r0, r1
	str r2, [r4, #8]
	add r0, r4, #0
	ldr r2, [sp, #8]
	add r0, #0x80
	str r2, [r0]
	str r3, [r4, #0x44]
	ldr r0, [sp, #0xc]
	add r4, #0xbc
	str r0, [r4]
	ldr r0, _022427C8 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r1
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	pop {r4, pc}
	.align 2, 0
_022427C8: .word MOD18_022513A0
	thumb_func_end MOD18_0224279C

	thumb_func_start MOD18_022427CC
MOD18_022427CC: ; 0x022427CC
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	cmp r1, #4
	bhi _022427EC
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022427E2: ; jump table
	.short _02242946 - _022427E2 - 2 ; case 0
	.short _0224290E - _022427E2 - 2 ; case 1
	.short _022428BE - _022427E2 - 2 ; case 2
	.short _02242856 - _022427E2 - 2 ; case 3
	.short _022427EC - _022427E2 - 2 ; case 4
_022427EC:
	mov r0, #2
	mov r2, #0x69
	str r0, [sp]
	sub r0, r0, #6
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xb7
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #0xb
	sub r3, r3, #5
	bl MOD18_0224279C
	mov r0, #1
	mvn r0, r0
	mov r2, #0x8c
	str r0, [sp]
	sub r0, r0, #2
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0x94
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #0xc
	sub r3, #0xf
	bl MOD18_0224279C
	mov r0, #1
	mvn r0, r0
	mov r2, #0x87
	str r0, [sp]
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0x99
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #0xd
	sub r3, #0x14
	bl MOD18_0224279C
	mov r0, #2
	mov r2, #0x78
	str r0, [sp]
	mov r0, #0
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xa8
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #0xe
	sub r3, #0xb
	bl MOD18_0224279C
_02242856:
	mov r0, #3
	mov r2, #0x80
	str r0, [sp]
	sub r0, r0, #7
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xa0
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #7
	sub r3, r3, #5
	bl MOD18_0224279C
	mov r0, #2
	mvn r0, r0
	mov r2, #0x84
	str r0, [sp]
	sub r0, r0, #1
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0x9c
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #8
	sub r3, #0xf
	bl MOD18_0224279C
	mov r0, #1
	mov r2, #0x70
	str r0, [sp]
	sub r0, r0, #3
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xb0
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #9
	bl MOD18_0224279C
	mov r0, #1
	mov r2, #0x73
	str r0, [sp]
	sub r0, r0, #3
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xad
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #0xa
	add r3, r3, #2
	bl MOD18_0224279C
_022428BE:
	mov r0, #2
	mov r2, #0x8c
	str r0, [sp]
	sub r0, r0, #5
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0x94
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #4
	sub r3, #0xa
	bl MOD18_0224279C
	mov r0, #1
	mvn r0, r0
	mov r2, #0x8c
	str r0, [sp]
	sub r0, r0, #1
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0x94
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #5
	sub r3, #0x14
	bl MOD18_0224279C
	mov r0, #0
	mvn r0, r0
	mov r2, #0x6e
	str r0, [sp]
	sub r0, r0, #1
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xb2
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #6
	bl MOD18_0224279C
_0224290E:
	mov r0, #1
	mvn r0, r0
	mov r2, #0x78
	str r0, [sp]
	sub r0, r0, #1
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xa8
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #2
	sub r3, #0x1e
	bl MOD18_0224279C
	mov r0, #1
	mvn r0, r0
	mov r2, #0x64
	str r0, [sp]
	sub r0, r0, #1
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xbc
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #3
	sub r3, #0xa
	bl MOD18_0224279C
_02242946:
	mov r0, #2
	mov r2, #0x80
	str r0, [sp]
	sub r0, r0, #5
	add r3, r2, #0
	str r0, [sp, #4]
	add r3, #0xa0
	ldr r3, [r4, r3]
	add r0, r4, #0
	mov r1, #1
	sub r3, #0x1e
	bl MOD18_0224279C
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD18_022427CC

	thumb_func_start MOD18_02242964
MOD18_02242964: ; 0x02242964
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	mov r7, #0
	add r4, r6, #0
	add r5, r7, #0
_02242970:
	add r0, r4, #0
	add r0, #0x80
	ldr r1, [r0]
	cmp r1, #0
	beq _022429E6
	ldr r0, [r4, #8]
	add r0, r0, r1
	str r0, [r4, #8]
	add r0, r4, #0
	add r0, #0xbc
	ldr r1, [r4, #0x44]
	ldr r0, [r0]
	add r0, r1, r0
	str r0, [r4, #0x44]
	add r0, r4, #0
	add r0, #0xbc
	ldr r1, [r0]
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r0, [r6, r0]
	add r1, r1, r0
	add r0, r4, #0
	add r0, #0xbc
	str r1, [r0]
	ldr r0, [r4, #8]
	lsl r0, r0, #0xc
	str r0, [sp]
	ldr r0, [r4, #0x44]
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	ldr r0, _022429F4 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020044
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r6, r0]
	ldr r1, [r4, #0x44]
	add r0, #0x23
	cmp r1, r0
	ble _022429E6
	ldr r0, _022429F4 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add r1, r4, #0
	add r1, #0x80
	mov r0, #0
	str r0, [r1]
_022429E6:
	add r7, r7, #1
	add r4, r4, #4
	add r5, r5, #4
	cmp r7, #0xf
	blt _02242970
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022429F4: .word MOD18_022513A0
	thumb_func_end MOD18_02242964

	thumb_func_start MOD18_022429F8
MOD18_022429F8: ; 0x022429F8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	ldr r0, _02242D64 ; =0x00000125
	add r4, r1, #0
	ldrb r1, [r4, r0]
	cmp r1, #6
	bhi _02242AFE
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02242A12: ; jump table
	.short _02242A20 - _02242A12 - 2 ; case 0
	.short _02242A68 - _02242A12 - 2 ; case 1
	.short _02242A98 - _02242A12 - 2 ; case 2
	.short _02242B22 - _02242A12 - 2 ; case 3
	.short _02242C30 - _02242A12 - 2 ; case 4
	.short _02242CAA - _02242A12 - 2 ; case 5
	.short _02242E42 - _02242A12 - 2 ; case 6
_02242A20:
	mov r1, #0
	sub r0, r0, #1
	strb r1, [r4, r0]
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	add r5, r0, #0
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r2, r0, #0
	mov r0, #0x20
	str r0, [sp]
	ldr r0, _02242D68 ; =0x022513A0
	add r1, r5, #0
	ldr r0, [r0, #4]
	mov r3, #5
	ldr r0, [r0, #0x40]
	bl MOD05_021E5420
	mov r1, #0x45
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #1
	add r1, #0x11
	strb r0, [r4, r1]
	ldr r0, _02242D6C ; =0x0000065E
	bl FUN_020054C8
	b _02242E6C
_02242A68:
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	add r2, r1, #1
	sub r1, r0, #1
	strb r2, [r4, r1]
	ldrb r1, [r4, r1]
	cmp r1, #0x14
	bls _02242AFE
	mov r1, #2
	strb r1, [r4, r0]
	mov r1, #0
	sub r2, r0, #5
	str r1, [r4, r2]
	add r2, r0, #0
	mov r3, #5
	sub r2, #9
	str r3, [r4, r2]
	ldr r2, _02242D68 ; =0x022513A0
	add r0, #0xd3
	ldr r2, [r2, #4]
	ldr r0, [r2, r0]
	bl FUN_02020130
	b _02242E6C
_02242A98:
	mov r1, #2
	lsl r1, r1, #0x12
	str r1, [sp, #8]
	sub r1, r0, #5
	ldr r1, [r4, r1]
	add r0, #0xd3
	lsl r1, r1, #0xc
	str r1, [sp, #0xc]
	ldr r1, _02242D68 ; =0x022513A0
	ldr r1, [r1, #4]
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_02020044
	ldr r0, _02242D68 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	mov r1, #0x12
	lsl r1, r1, #4
	ldr r2, [r4, r1]
	cmp r2, #0x41
	ble _02242B0E
	mov r2, #3
	add r0, r1, #5
	strb r2, [r4, r0]
	ldr r0, _02242D70 ; =0x0000065D
	bl FUN_020054C8
	ldr r0, _02242D68 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02242D74 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0x15
	bne _02242AEC
	mov r1, #0
	mvn r1, r1
	b _02242AEE
_02242AEC:
	mov r1, #5
_02242AEE:
	mov r0, #0x46
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02242B00
_02242AFE:
	b _02242E6C
_02242B00:
	bl FUN_02064520
	mov r0, #0x45
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _02242E6C
_02242B0E:
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r0, r2, r0
	str r0, [r4, r1]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r2, r0, #3
	sub r0, r1, #4
	str r2, [r4, r0]
	b _02242E6C
_02242B22:
	ldr r1, _02242D78 ; =gMain + 0x40
	ldrh r2, [r1, #0x20]
	cmp r2, #0
	beq _02242BD2
	sub r0, r0, #5
	ldrh r2, [r1, #0x1e]
	ldr r0, [r4, r0]
	sub r0, r2, r0
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	asr r7, r0, #0x1f
	ldrh r0, [r1, #0x1c]
	sub r0, #0x80
	lsl r0, r0, #0xc
	asr r1, r0, #0x1f
	add r2, r0, #0
	add r3, r1, #0
	bl _ll_mul
	add r6, r0, #0
	ldr r0, [sp, #4]
	add r5, r1, #0
	add r1, r7, #0
	add r2, r0, #0
	add r3, r7, #0
	bl _ll_mul
	mov r2, #2
	mov r3, #0
	lsl r2, r2, #0xa
	add r6, r6, r2
	adc r5, r3
	lsl r5, r5, #0x14
	lsr r6, r6, #0xc
	orr r6, r5
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	add r0, r6, r1
	bl FX_Sqrt
	mov r1, #3
	lsl r1, r1, #0x10
	cmp r0, r1
	bge _02242BD2
	mov r0, #0x4b
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, _02242D7C ; =0x00000627
	bl FUN_020054C8
	mov r0, #0x46
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r5, [r4, r0]
	mov r1, #3
	add r0, r5, #0
	bl _s32_div_f
	cmp r1, #2
	bne _02242BD2
	add r0, r5, #0
	mov r1, #3
	bl _s32_div_f
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #2
	add r0, r4, #0
	add r1, r4, r1
	add r0, #0xf8
	add r1, #0xf8
	ldr r0, [r0]
	ldr r1, [r1]
	bl FUN_02009BB8
	mov r0, #0x49
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r4, r0]
	mov r1, #4
	add r0, r0, #1
	strb r1, [r4, r0]
_02242BD2:
	mov r1, #0x46
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	cmp r0, #0xf
	ble _02242BF0
	add r0, r1, #0
	mov r3, #0
	add r0, #0xc
	strb r3, [r4, r0]
	add r0, r1, #0
	mov r2, #5
	add r0, #0xd
	strb r2, [r4, r0]
	add r1, #0x14
	str r3, [r4, r1]
_02242BF0:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02242C0A
	bge _02242C00
	add r1, r1, #1
	str r1, [r4, r0]
_02242C00:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	neg r1, r1
	str r1, [r4, r0]
_02242C0A:
	mov r1, #0x4b
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r0, #0x80
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	add r0, r1, #0
	sub r0, #0xc
	ldr r0, [r4, r0]
	add r1, #0xcc
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, r1]
	add r1, sp, #8
	bl FUN_02020044
	b _02242E6C
_02242C30:
	sub r1, r0, #1
	ldrb r1, [r4, r1]
	cmp r1, #0
	bne _02242C4A
	sub r0, #0xd
	ldr r0, [r4, r0]
	mov r1, #3
	bl _s32_div_f
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_022427CC
_02242C4A:
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD18_02242964
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	cmp r1, #0x14
	bne _02242C6A
	mov r1, #3
	add r0, r0, #1
	strb r1, [r4, r0]
_02242C6A:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _02242C84
	bge _02242C7A
	add r1, r1, #1
	str r1, [r4, r0]
_02242C7A:
	mov r0, #0x4b
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	neg r1, r1
	str r1, [r4, r0]
_02242C84:
	mov r1, #0x4b
	lsl r1, r1, #2
	ldr r0, [r4, r1]
	add r0, #0x80
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	add r0, r1, #0
	sub r0, #0xc
	ldr r0, [r4, r0]
	add r1, #0xcc
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, r1]
	add r1, sp, #8
	bl FUN_02020044
	b _02242E6C
_02242CAA:
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _02242CB4
	b _02242DD2
_02242CB4:
	ldr r0, _02242D80 ; =0x0000062A
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x11
	add r0, #0xf8
	lsl r1, r1, #4
	ldr r0, [r0]
	ldr r1, [r4, r1]
	bl FUN_02009BB8
	mov r7, #1
	mov r5, #4
	mov r6, #0x52
_02242CD0:
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020130
	lsl r0, r6, #0xc
	str r0, [sp, #8]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r2, [r4, r0]
	lsr r1, r7, #0x1f
	lsl r3, r7, #0x1f
	sub r3, r3, r1
	mov r0, #0x1f
	ror r3, r0
	add r2, #0x27
	add r0, r1, r3
	add r0, r2, r0
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_02020044
	ldr r0, _02242D68 ; =0x022513A0
	ldr r0, [r0, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	add r7, r7, #1
	add r5, r5, #4
	add r6, #0xc
	cmp r7, #9
	blt _02242CD0
	ldr r0, _02242D68 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x19
	lsl r0, r0, #0xe
	str r0, [sp, #8]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	add r0, #0x15
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02242D68 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_02020044
	ldr r0, _02242D68 ; =0x022513A0
	b _02242D84
	.align 2, 0
_02242D64: .word 0x00000125
_02242D68: .word MOD18_022513A0
_02242D6C: .word 0x0000065E
_02242D70: .word 0x0000065D
_02242D74: .word 0x00000B3B
_02242D78: .word gMain + 0x40
_02242D7C: .word 0x00000627
_02242D80: .word 0x0000062A
_02242D84:
	ldr r1, [r0, #4]
	mov r0, #0x22
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
	ldr r0, _02242E7C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020130
	mov r0, #0x7a
	lsl r0, r0, #0xc
	str r0, [sp, #8]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _02242E7C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_02020044
	ldr r0, _02242E7C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x89
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200A0
_02242DD2:
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	bl LCRandom
	mov r1, #0xa
	bl _s32_div_f
	add r1, #0x7b
	lsl r0, r1, #0xc
	str r0, [sp, #8]
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	add r0, #0xd8
	lsl r1, r1, #0xc
	str r1, [sp, #0xc]
	ldr r1, _02242E7C ; =0x022513A0
	ldr r1, [r1, #4]
	ldr r0, [r1, r0]
	add r1, sp, #8
	bl FUN_02020044
	mov r0, #0x12
	lsl r0, r0, #4
	ldr r1, [r4, r0]
	mov r2, #0x1d
	add r1, r1, #1
	str r1, [r4, r0]
	add r1, r0, #4
	ldrb r1, [r4, r1]
	lsr r5, r1, #0x1f
	lsl r3, r1, #0x1d
	sub r3, r3, r5
	ror r3, r2
	add r2, r5, r3
	beq _02242E30
	ldr r2, _02242E7C ; =0x022513A0
	lsr r1, r1, #3
	ldr r2, [r2, #4]
	add r0, #0xd8
	ldr r0, [r2, r0]
	add r1, r1, #3
	bl FUN_02020130
_02242E30:
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	cmp r1, #0x4b
	bne _02242E6C
	mov r1, #6
	add r0, r0, #1
	strb r1, [r4, r0]
	b _02242E6C
_02242E42:
	sub r0, #0x11
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02242E56
	bl FUN_02064520
	mov r0, #0x45
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_02242E56:
	ldr r0, _02242E7C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_020200A0
	add sp, #0x14
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02242E6C:
	ldr r0, _02242E7C ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	bl FUN_0201FDEC
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02242E7C: .word MOD18_022513A0
	thumb_func_end MOD18_022429F8

	thumb_func_start MOD18_02242E80
MOD18_02242E80: ; 0x02242E80
	push {r4, r5, lr}
	sub sp, #0x24
	ldr r4, _02242ED4 ; =0x022500DC
	add r3, sp, #0xc
	add r5, r0, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r5, r0]
	sub r4, r1, #1
	cmp r4, #6
	bge _02242ECE
	add r1, r4, #1
	str r1, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	ldr r1, _02242ED8 ; =0x022513A0
	lsl r3, r4, #2
	ldr r2, [r2, r3]
	ldr r1, [r1, #4]
	add r0, #0x4c
	ldr r0, [r1, r0]
	mov r1, #0x32
	mov r3, #0
	bl FUN_02008F34
	add r1, r4, #1
	lsl r1, r1, #2
	add r1, r5, r1
	add r1, #0xf8
	str r0, [r1]
_02242ECE:
	add sp, #0x24
	pop {r4, r5, pc}
	nop
_02242ED4: .word MOD18_022500DC
_02242ED8: .word MOD18_022513A0
	thumb_func_end MOD18_02242E80

	thumb_func_start MOD18_02242EDC
MOD18_02242EDC: ; 0x02242EDC
	push {r3, r4, r5, r6, r7, lr}
	mov r7, #0x17
	ldr r6, _02242F04 ; =0x022513A0
	mov r4, #1
	add r5, r0, #4
	lsl r7, r7, #4
_02242EE8:
	add r0, r5, #0
	add r0, #0xf8
	ldr r1, [r0]
	cmp r1, #0
	beq _02242EFA
	ldr r0, [r6, #4]
	ldr r0, [r0, r7]
	bl FUN_02009490
_02242EFA:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #7
	blt _02242EE8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02242F04: .word MOD18_022513A0
	thumb_func_end MOD18_02242EDC

	thumb_func_start MOD18_02242F08
MOD18_02242F08: ; 0x02242F08
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0xc
	bls _02242F16
	b _0224318E
_02242F16:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02242F22: ; jump table
	.short _02242F3C - _02242F22 - 2 ; case 0
	.short _02242F98 - _02242F22 - 2 ; case 1
	.short _02242FE2 - _02242F22 - 2 ; case 2
	.short _02243018 - _02242F22 - 2 ; case 3
	.short _02243058 - _02242F22 - 2 ; case 4
	.short _0224308A - _02242F22 - 2 ; case 5
	.short _0224309A - _02242F22 - 2 ; case 6
	.short _022430EC - _02242F22 - 2 ; case 7
	.short _02243134 - _02242F22 - 2 ; case 8
	.short _02243140 - _02242F22 - 2 ; case 9
	.short _0224318E - _02242F22 - 2 ; case 10
	.short _02243150 - _02242F22 - 2 ; case 11
	.short _02243174 - _02242F22 - 2 ; case 12
_02242F3C:
	bl MOD18_022400A0
	str r0, [r4, #4]
	mov r0, #0x49
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r4, r0]
	ldr r1, _02243194 ; =0x022513A0
	mov r0, #0x20
	ldr r1, [r1, #4]
	mov r2, #4
	add r1, #0x48
	bl FUN_02008C9C
	ldr r1, _02243194 ; =0x022513A0
	ldr r2, [r1, #4]
	str r0, [r2, #0x44]
	ldr r0, [r1, #4]
	mov r2, #6
	add r0, #0x48
	mov r1, #0
	lsl r2, r2, #0x12
	bl FUN_02008D24
	mov r6, #0
	ldr r7, _02243194 ; =0x022513A0
	add r5, r6, #0
_02242F72:
	mov r0, #8
	add r1, r6, #0
	mov r2, #4
	bl FUN_02008DEC
	ldr r1, [r7, #4]
	add r6, r6, #1
	add r2, r1, r5
	mov r1, #0x17
	lsl r1, r1, #4
	add r5, r5, #4
	str r0, [r2, r1]
	cmp r6, #4
	blt _02242F72
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02242F98:
	mov r0, #1
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, _02243194 ; =0x022513A0
	mov r2, #0x20
	ldr r1, [r0, #4]
	mov r0, #0x17
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_02008F34
	ldr r2, _02243194 ; =0x022513A0
	mov r1, #0x19
	ldr r3, [r2, #4]
	lsl r1, r1, #4
	str r0, [r3, r1]
	ldr r0, [r2, #4]
	add sp, #0x10
	ldr r1, [r0, r1]
	add r0, r4, #0
	add r0, #0xf8
	str r1, [r0]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02242FE2:
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, _02243194 ; =0x022513A0
	mov r2, #0x33
	ldr r1, [r0, #4]
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_02008FEC
	ldr r1, _02243194 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02243018:
	mov r0, #1
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	mov r3, #0
	str r3, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, _02243194 ; =0x022513A0
	mov r2, #0x1f
	ldr r1, [r0, #4]
	mov r0, #0x5e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _02243194 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02243058:
	mov r3, #0
	str r3, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	ldr r0, _02243194 ; =0x022513A0
	mov r2, #0x1e
	ldr r1, [r0, #4]
	mov r0, #0x5f
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _02243194 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224308A:
	add r0, r4, #0
	bl MOD18_02242668
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224309A:
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	add r0, r4, #0
	bl MOD18_02242E80
	mov r1, #0x49
	lsl r1, r1, #2
	ldrb r0, [r4, r1]
	cmp r0, #0x1e
	bls _0224318E
	ldr r0, _02243194 ; =0x022513A0
	ldr r2, [r0, #4]
	ldr r0, _02243198 ; =0x00000B3B
	ldrb r0, [r2, r0]
	cmp r0, #0x14
	bne _022430CE
	add r0, r4, #0
	add r0, #0xf8
	sub r1, #0x24
	ldr r0, [r0]
	ldr r1, [r4, r1]
	bl FUN_02009BB8
_022430CE:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x4d
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #0x4a
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #7
	add sp, #0x10
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022430EC:
	ldr r0, _02243194 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_022429F8
	cmp r0, #0
	beq _02243114
	ldr r0, _0224319C ; =0x00000127
	ldrb r0, [r4, r0]
	cmp r0, #0
	beq _0224310A
	mov r0, #0xb
	str r0, [r4]
	b _02243114
_0224310A:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02243114:
	mov r0, #0x4a
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0x3c
	bge _0224318E
	add r1, r1, #1
	str r1, [r4, r0]
	ldr r0, [r4, r0]
	cmp r0, #0x3c
	bne _0224318E
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02243134:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02243140:
	bl FUN_02031190
	ldr r1, _0224319C ; =0x00000127
	ldrb r1, [r4, r1]
	bl MOD18_0224322C
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02243150:
	ldr r0, _0224319C ; =0x00000127
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _022431A0 ; =0x00000126
	ldrb r0, [r4, r0]
	bl MOD18_0223FD8C
	mov r0, #0x49
	mov r1, #0
	lsl r0, r0, #2
	strb r1, [r4, r0]
	mov r0, #0xc
	add sp, #0x10
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_02243174:
	mov r0, #0x49
	lsl r0, r0, #2
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	ldrb r0, [r4, r0]
	cmp r0, #8
	bls _0224318E
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_0224318E:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02243194: .word MOD18_022513A0
_02243198: .word 0x00000B3B
_0224319C: .word 0x00000127
_022431A0: .word 0x00000126
	thumb_func_end MOD18_02242F08

	thumb_func_start MOD18_022431A4
MOD18_022431A4: ; 0x022431A4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x13
	mov r0, #4
	lsl r1, r1, #4
	add r6, r2, #0
	bl AllocFromHeapAtEnd
	mov r2, #0x13
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _022431E8 ; =0x00000127
	mov r2, #0x64
	strb r5, [r4, r0]
	sub r0, r0, #1
	strb r6, [r4, r0]
	ldr r0, _022431EC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _022431F0 ; =MOD18_02242F08
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _022431EC ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r4, r5, r6, pc}
	.align 2, 0
_022431E8: .word 0x00000127
_022431EC: .word MOD18_022513A0
_022431F0: .word MOD18_02242F08
	thumb_func_end MOD18_022431A4

	thumb_func_start MOD18_022431F4
MOD18_022431F4: ; 0x022431F4
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _0224321A
	ldr r0, _0224321C ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	add r2, r6, #0
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_022431A4
_0224321A:
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224321C: .word MOD18_022513A0
	thumb_func_end MOD18_022431F4

	thumb_func_start MOD18_02243220
MOD18_02243220: ; 0x02243220
	ldr r3, _02243228 ; =FUN_0204E758
	mov r1, #2
	bx r3
	nop
_02243228: .word FUN_0204E758
	thumb_func_end MOD18_02243220

	thumb_func_start MOD18_0224322C
MOD18_0224322C: ; 0x0224322C
	push {r3, r4, r5, lr}
	ldr r0, _022432AC ; =0x022513A0
	add r5, r1, #0
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r1, r0]
	cmp r4, #0
	beq _022432AA
	mov r0, #0x45
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02243254
	bl FUN_02064520
	mov r0, #0x45
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_02243254:
	ldr r0, _022432B0 ; =0x00000127
	ldrb r1, [r4, r0]
	cmp r1, #0
	beq _02243268
	cmp r5, #0
	beq _02243268
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	bl MOD18_0223FD8C
_02243268:
	add r0, r4, #0
	bl MOD18_02242EDC
	mov r0, #0xf
	bl MOD18_02241800
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _022432AC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, _022432AC ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_022432AA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022432AC: .word MOD18_022513A0
_022432B0: .word 0x00000127
	thumb_func_end MOD18_0224322C

	thumb_func_start MOD18_022432B4
MOD18_022432B4: ; 0x022432B4
	push {lr}
	sub sp, #0x5c
	ldr r0, _022433C4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x19
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009B78
	ldr r0, _022433C4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x65
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	ldr r0, _022433C4 ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	mov r3, #0x17
	str r1, [sp]
	sub r2, r1, #1
	str r2, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	lsl r3, r3, #4
	ldr r2, [r0, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r0, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r0, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r0, r2]
	add r3, #0x64
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r0, r3
	add r2, r1, #0
	add r3, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	ldr r0, _022433C4 ; =0x022513A0
	mov r2, #2
	ldr r1, [r0, #4]
	lsl r2, r2, #0x10
	ldr r0, [r1, #0x44]
	str r0, [sp, #0x2c]
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x30]
	mov r0, #6
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	lsr r0, r2, #5
	mov r1, #0
	str r2, [sp, #0x34]
	str r1, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r1, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #4
	str r0, [sp, #0x58]
	lsl r0, r0, #0x11
	str r0, [sp, #0x34]
	mov r0, #0x15
	lsl r0, r0, #0xe
	str r0, [sp, #0x38]
	add r0, sp, #0x2c
	str r1, [sp, #0x50]
	bl FUN_0201FE94
	ldr r2, _022433C4 ; =0x022513A0
	mov r1, #0x7e
	ldr r3, [r2, #4]
	lsl r1, r1, #2
	str r0, [r3, r1]
	ldr r0, [r2, #4]
	ldr r0, [r0, r1]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, _022433C4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020130
	ldr r0, _022433C4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, _022433C4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020208
	ldr r0, _022433C4 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020238
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x5c
	pop {pc}
	nop
_022433C4: .word MOD18_022513A0
	thumb_func_end MOD18_022432B4

	thumb_func_start MOD18_022433C8
MOD18_022433C8: ; 0x022433C8
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0x28
	ldrb r0, [r0]
	mov r4, #0
	cmp r0, #0
	beq _022433E2
	cmp r0, #1
	beq _02243402
	cmp r0, #2
	b _02243512
_022433E2:
	ldr r0, _02243524 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02243528 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0x1f
	bne _022433F2
	mov r0, #4
	b _022433F4
_022433F2:
	mov r0, #2
_022433F4:
	str r0, [r5, #0x20]
	mov r0, #0
	str r0, [r5, #0x24]
	add r0, r5, #0
	mov r1, #1
	add r0, #0x28
	strb r1, [r0]
_02243402:
	ldr r1, _0224352C ; =0x022513A0
	ldr r2, _02243530 ; =MOD18_02241AB4
	mov r0, #2
	mov r3, #0
	bl FUN_02004928
	ldr r0, [r5, #0x14]
	add r0, r0, #1
	str r0, [r5, #0x14]
	ldr r0, _02243524 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02243534 ; =0x00000B3A
	ldrsb r0, [r1, r0]
	bl abs
	add r6, r0, #0
	ldr r0, [r5, #0x14]
	mov r1, #0xa
	bl _s32_div_f
	add r0, r5, r1
	strb r6, [r0, #8]
	mov r1, #0
	b _0224343A
_02243432:
	add r0, r5, r1
	ldrb r0, [r0, #8]
	add r1, r1, #1
	add r4, r4, r0
_0224343A:
	cmp r1, #0xa
	blt _02243432
	mov r0, #0x7d
	lsl r0, r0, #2
	cmp r4, r0
	ble _02243454
	ldr r0, [r5, #0x24]
	add r0, r0, #1
	str r0, [r5, #0x24]
	ldr r0, _02243538 ; =0x00000628
	bl FUN_020054C8
	b _0224345C
_02243454:
	add r0, r5, #0
	mov r1, #0
	add r0, #0x28
	strb r1, [r0]
_0224345C:
	ldr r0, [r5, #0x24]
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #9
	bne _0224346E
	ldr r0, [r5, #0x20]
	sub r0, r0, #1
	str r0, [r5, #0x20]
_0224346E:
	ldr r2, [r5, #0x20]
	cmp r2, #0
	bne _02243480
	mov r0, #2
	add r5, #0x28
	strb r0, [r5]
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02243480:
	ldr r0, _02243524 ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, _02243528 ; =0x00000B3B
	ldrb r0, [r1, r0]
	cmp r0, #0x1f
	bne _022434B0
	cmp r2, #2
	beq _022434A4
	cmp r2, #3
	beq _0224349E
	cmp r2, #4
	bne _022434AA
	mov r4, #1
	lsl r4, r4, #0x1e
	b _022434BE
_0224349E:
	mov r4, #0xff
	lsl r4, r4, #0x16
	b _022434BE
_022434A4:
	mov r4, #0xfe
	lsl r4, r4, #0x16
	b _022434BE
_022434AA:
	mov r4, #0x3f
	lsl r4, r4, #0x18
	b _022434BE
_022434B0:
	cmp r2, #2
	bne _022434BA
	mov r4, #1
	lsl r4, r4, #0x1e
	b _022434BE
_022434BA:
	mov r4, #0xff
	lsl r4, r4, #0x16
_022434BE:
	ldr r0, [r5, #0x24]
	mov r6, #0
	cmp r0, #0
	beq _022434C8
	add r6, r6, #1
_022434C8:
	ldr r0, _0224353C ; =0x45800000
	add r1, r4, #0
	bl _fmul
	bl _ffix
	str r0, [sp]
	ldr r0, _0224353C ; =0x45800000
	add r1, r4, #0
	bl _fmul
	bl _ffix
	str r0, [sp, #4]
	ldr r0, _0224353C ; =0x45800000
	add r1, r4, #0
	bl _fmul
	bl _ffix
	str r0, [sp, #8]
	ldr r0, _02243524 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0
	bl FUN_02020064
	ldr r0, _02243524 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, r6, #0
	bl FUN_02020184
_02243512:
	ldr r0, _02243524 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	bl FUN_0201FDEC
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_02243524: .word MOD18_022513A0
_02243528: .word 0x00000B3B
_0224352C: .word MOD18_022513A0
_02243530: .word MOD18_02241AB4
_02243534: .word 0x00000B3A
_02243538: .word 0x00000628
_0224353C: .word 0x45800000
	thumb_func_end MOD18_022433C8

	thumb_func_start MOD18_02243540
MOD18_02243540: ; 0x02243540
	push {r4, lr}
	sub sp, #0x10
	add r4, r1, #0
	ldr r0, [r4]
	cmp r0, #0xc
	bls _0224354E
	b _02243780
_0224354E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224355A: ; jump table
	.short _02243574 - _0224355A - 2 ; case 0
	.short _0224358C - _0224355A - 2 ; case 1
	.short _022435D8 - _0224355A - 2 ; case 2
	.short _0224360E - _0224355A - 2 ; case 3
	.short _0224365A - _0224355A - 2 ; case 4
	.short _02243698 - _0224355A - 2 ; case 5
	.short _022436A8 - _0224355A - 2 ; case 6
	.short _022436D6 - _0224355A - 2 ; case 7
	.short _0224372C - _0224355A - 2 ; case 8
	.short _02243738 - _0224355A - 2 ; case 9
	.short _02243780 - _0224355A - 2 ; case 10
	.short _02243748 - _0224355A - 2 ; case 11
	.short _0224376C - _0224355A - 2 ; case 12
_02243574:
	bl MOD18_022400A0
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x24]
	bl MOD18_022417B4
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0224358C:
	mov r0, #1
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	ldr r0, _02243784 ; =0x022513A0
	ldr r1, _02243788 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1f
	bne _022435AA
	mov r2, #0x16
	b _022435AC
_022435AA:
	mov r2, #0x19
_022435AC:
	mov r3, #0
	str r3, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x17
	lsl r1, r1, #4
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_02008F34
	ldr r1, _02243784 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x19
	lsl r1, r1, #4
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022435D8:
	mov r3, #0
	str r3, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #7
	str r0, [sp, #8]
	mov r0, #4
	str r0, [sp, #0xc]
	ldr r0, _02243784 ; =0x022513A0
	mov r2, #0x13
	ldr r1, [r0, #4]
	mov r0, #0x5d
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0x32
	bl FUN_02008FEC
	ldr r1, _02243784 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x65
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0224360E:
	mov r0, #1
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	ldr r0, _02243784 ; =0x022513A0
	ldr r1, _02243788 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1f
	bne _0224362C
	mov r2, #0x15
	b _0224362E
_0224362C:
	mov r2, #0x18
_0224362E:
	mov r3, #0
	str r3, [sp]
	mov r1, #2
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x5e
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _02243784 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_0224365A:
	ldr r0, _02243784 ; =0x022513A0
	ldr r1, _02243788 ; =0x00000B3B
	ldr r0, [r0, #4]
	ldrb r1, [r0, r1]
	cmp r1, #0x1f
	bne _0224366A
	mov r2, #0x14
	b _0224366C
_0224366A:
	mov r2, #0x17
_0224366C:
	mov r3, #0
	str r3, [sp]
	mov r1, #3
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x5f
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	mov r1, #0x32
	bl FUN_020090AC
	ldr r1, _02243784 ; =0x022513A0
	add sp, #0x10
	ldr r2, [r1, #4]
	mov r1, #0x67
	lsl r1, r1, #2
	str r0, [r2, r1]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_02243698:
	add r0, r4, #0
	bl MOD18_022432B4
	ldr r0, [r4]
	add sp, #0x10
	add r0, r0, #1
	str r0, [r4]
	pop {r4, pc}
_022436A8:
	ldr r0, [r4, #0x24]
	add r0, r0, #1
	str r0, [r4, #0x24]
	cmp r0, #0x1e
	ble _02243780
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x4c
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r1, #3
	ldr r0, _0224378C ; =0x0400006C
	mvn r1, r1
	bl GXx_SetMasterBrightness_
	mov r0, #7
	str r0, [r4]
	mov r0, #0
	add sp, #0x10
	str r0, [r4, #0x2c]
	pop {r4, pc}
_022436D6:
	mov r0, #7
	str r0, [sp]
	ldr r0, _02243790 ; =0x04000050
	mov r1, #0x10
	mov r2, #1
	mov r3, #0xe
	bl G2x_SetBlendAlpha_
	ldr r0, _02243784 ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_022433C8
	cmp r0, #0
	beq _02243712
	add r0, r4, #0
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #0
	beq _02243708
	mov r0, #0xb
	str r0, [r4]
	b _02243712
_02243708:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02243712:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x3c
	bge _02243780
	add r0, r0, #1
	str r0, [r4, #0x2c]
	cmp r0, #0x3c
	bne _02243780
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r4, pc}
_0224372C:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x10
	pop {r4, pc}
_02243738:
	bl FUN_02031190
	add r4, #0x2a
	ldrb r1, [r4]
	bl MOD18_02243818
	add sp, #0x10
	pop {r4, pc}
_02243748:
	mov r0, #0x10
	bl FUN_0204F774
	add r0, r4, #0
	mov r1, #0
	add r0, #0x2a
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x29
	ldrb r0, [r0]
	bl MOD18_0223FD8C
	mov r0, #0
	str r0, [r4, #0x24]
	mov r0, #0xc
	add sp, #0x10
	str r0, [r4]
	pop {r4, pc}
_0224376C:
	ldr r0, [r4, #0x24]
	add r0, r0, #1
	str r0, [r4, #0x24]
	cmp r0, #8
	ble _02243780
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_02243780:
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_02243784: .word MOD18_022513A0
_02243788: .word 0x00000B3B
_0224378C: .word 0x0400006C
_02243790: .word 0x04000050
	thumb_func_end MOD18_02243540

	thumb_func_start MOD18_02243794
MOD18_02243794: ; 0x02243794
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r0, #4
	mov r1, #0x30
	add r6, r2, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x30
	bl MI_CpuFill8
	add r0, r4, #0
	add r0, #0x2a
	strb r5, [r0]
	add r0, r4, #0
	add r0, #0x29
	strb r6, [r0]
	ldr r0, _022437D8 ; =0x022513A0
	mov r2, #0x64
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _022437DC ; =MOD18_02243540
	add r1, r4, #0
	bl FUN_0200CA44
	ldr r1, _022437D8 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r4, r5, r6, pc}
	.align 2, 0
_022437D8: .word MOD18_022513A0
_022437DC: .word MOD18_02243540
	thumb_func_end MOD18_02243794

	thumb_func_start MOD18_022437E0
MOD18_022437E0: ; 0x022437E0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _02243806
	ldr r0, _02243808 ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	add r2, r6, #0
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_02243794
_02243806:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02243808: .word MOD18_022513A0
	thumb_func_end MOD18_022437E0

	thumb_func_start MOD18_0224380C
MOD18_0224380C: ; 0x0224380C
	ldr r3, _02243814 ; =FUN_0204E758
	mov r1, #2
	bx r3
	nop
_02243814: .word FUN_0204E758
	thumb_func_end MOD18_0224380C

	thumb_func_start MOD18_02243818
MOD18_02243818: ; 0x02243818
	push {r4, lr}
	ldr r0, _0224388C ; =0x022513A0
	ldr r2, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r2, r0]
	cmp r4, #0
	beq _02243888
	add r0, r4, #0
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #0
	beq _02243840
	cmp r1, #0
	beq _02243840
	add r0, r4, #0
	add r0, #0x29
	ldrb r0, [r0]
	bl MOD18_0223FD8C
_02243840:
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02243890 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	mov r0, #1
	bl MOD18_02241800
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _0224388C ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, _0224388C ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02243888:
	pop {r4, pc}
	nop
_0224388C: .word MOD18_022513A0
_02243890: .word 0x04000050
	thumb_func_end MOD18_02243818

	thumb_func_start MOD18_02243894
MOD18_02243894: ; 0x02243894
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldr r1, [r4]
	cmp r1, #0xc
	bhi _022439A0
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022438AC: ; jump table
	.short _022438C6 - _022438AC - 2 ; case 0
	.short _022438DA - _022438AC - 2 ; case 1
	.short _022438F2 - _022438AC - 2 ; case 2
	.short _022438FA - _022438AC - 2 ; case 3
	.short _02243912 - _022438AC - 2 ; case 4
	.short _0224391A - _022438AC - 2 ; case 5
	.short _02243922 - _022438AC - 2 ; case 6
	.short _02243946 - _022438AC - 2 ; case 7
	.short _022439A0 - _022438AC - 2 ; case 8
	.short _02243962 - _022438AC - 2 ; case 9
	.short _022439A0 - _022438AC - 2 ; case 10
	.short _02243970 - _022438AC - 2 ; case 11
	.short _0224398C - _022438AC - 2 ; case 12
_022438C6:
	bl MOD18_022400A0
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0xc]
	ldr r0, [r4]
	add sp, #4
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_022438DA:
	mov r0, #1
	str r0, [sp]
	mov r1, #0xa
	mov r2, #0
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #4
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_022438F2:
	add r0, r1, #1
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_022438FA:
	mov r0, #1
	str r0, [sp]
	mov r1, #0
	mov r2, #0xa
	add r3, r0, #0
	bl FUN_0200A208
	ldr r0, [r4]
	add sp, #4
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, pc}
_02243912:
	add r0, r1, #1
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_0224391A:
	add r0, r1, #1
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_02243922:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #0x1e
	ble _022439A0
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r1, #3
	ldr r0, _022439A4 ; =0x0400006C
	mvn r1, r1
	bl GXx_SetMasterBrightness_
	mov r0, #7
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_02243946:
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _02243954
	mov r0, #0xb
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_02243954:
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_02243962:
	bl FUN_02031190
	ldrb r1, [r4, #0x11]
	bl MOD18_02243A24
	add sp, #4
	pop {r3, r4, pc}
_02243970:
	mov r0, #0x10
	bl FUN_0204F774
	mov r0, #0
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x10]
	bl MOD18_0223FD8C
	mov r0, #0
	str r0, [r4, #0xc]
	mov r0, #0xc
	add sp, #4
	str r0, [r4]
	pop {r3, r4, pc}
_0224398C:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	cmp r0, #8
	ble _022439A0
	mov r0, #0x29
	bl FUN_020311DC
	mov r0, #8
	str r0, [r4]
_022439A0:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_022439A4: .word 0x0400006C
	thumb_func_end MOD18_02243894

	thumb_func_start MOD18_022439A8
MOD18_022439A8: ; 0x022439A8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r0, #4
	mov r1, #0x14
	add r6, r2, #0
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x14
	bl MI_CpuFill8
	strb r5, [r4, #0x11]
	ldr r0, _022439E4 ; =0x022513A0
	strb r6, [r4, #0x10]
	ldr r1, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	str r4, [r1, r0]
	ldr r0, _022439E8 ; =MOD18_02243894
	add r1, r4, #0
	mov r2, #0x64
	bl FUN_0200CA44
	ldr r1, _022439E4 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0xa3
	lsl r1, r1, #2
	str r0, [r2, r1]
	pop {r4, r5, r6, pc}
	.align 2, 0
_022439E4: .word MOD18_022513A0
_022439E8: .word MOD18_02243894
	thumb_func_end MOD18_022439A8

	thumb_func_start MOD18_022439EC
MOD18_022439EC: ; 0x022439EC
	push {r4, r5, r6, lr}
	add r4, r1, #0
	mov r1, #2
	add r5, r0, #0
	add r6, r2, #0
	bl FUN_0204E758
	bl FUN_02031190
	cmp r5, r0
	bne _02243A12
	ldr r0, _02243A14 ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	add r2, r6, #0
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_022439A8
_02243A12:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02243A14: .word MOD18_022513A0
	thumb_func_end MOD18_022439EC

	thumb_func_start MOD18_02243A18
MOD18_02243A18: ; 0x02243A18
	ldr r3, _02243A20 ; =FUN_0204E758
	mov r1, #2
	bx r3
	nop
_02243A20: .word FUN_0204E758
	thumb_func_end MOD18_02243A18

	thumb_func_start MOD18_02243A24
MOD18_02243A24: ; 0x02243A24
	push {r4, lr}
	ldr r0, _02243A88 ; =0x022513A0
	ldr r2, [r0, #4]
	mov r0, #0xa7
	lsl r0, r0, #2
	ldr r4, [r2, r0]
	cmp r4, #0
	beq _02243A86
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _02243A44
	cmp r1, #0
	beq _02243A44
	ldrb r0, [r4, #0x10]
	bl MOD18_0223FD8C
_02243A44:
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	ldr r0, _02243A8C ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	mov r0, #0x10
	bl FUN_0204F774
	ldr r0, _02243A88 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0xa3
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	ldr r1, _02243A88 ; =0x022513A0
	mov r0, #0xa3
	ldr r2, [r1, #4]
	mov r3, #0
	lsl r0, r0, #2
	str r3, [r2, r0]
	ldr r1, [r1, #4]
	add r0, #0x10
	str r3, [r1, r0]
_02243A86:
	pop {r4, pc}
	.align 2, 0
_02243A88: .word MOD18_022513A0
_02243A8C: .word 0x04000050
	thumb_func_end MOD18_02243A24

	thumb_func_start MOD18_02243A90
MOD18_02243A90: ; 0x02243A90
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	ldr r0, [r1, #0x28]
	str r1, [sp, #0x10]
	lsl r0, r0, #0xc
	str r0, [sp, #0x1c]
	add r0, r1, #0
	ldr r0, [r0, #0x2c]
	lsl r0, r0, #0xc
	str r0, [sp, #0x20]
	ldr r0, _02243BBC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0x1c
	bl FUN_02020044
	ldr r0, [sp, #0x10]
	mov r1, #0xa
	ldr r0, [r0, #0x30]
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #0x1c]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	ldr r0, _02243BBC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0x1c
	bl FUN_02020064
	ldr r0, _02243BBC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020398
	mov r1, #0x10
	ldr r3, [sp, #0x10]
	str r1, [sp]
	ldr r4, [r3, #0x30]
	ldr r0, _02243BC0 ; =0x04000050
	lsr r3, r4, #0x1f
	add r3, r4, r3
	asr r3, r3, #1
	mov r2, #1
	sub r3, r1, r3
	bl G2x_SetBlendAlpha_
	mov r0, #0
	ldr r7, [sp, #0x10]
	str r0, [sp, #0xc]
	str r0, [sp, #8]
_02243B06:
	ldr r0, [r7, #0x14]
	mov r4, #0
	cmp r0, #0
	ble _02243B86
	ldr r0, [sp, #8]
	add r5, r4, #0
	lsl r0, r0, #2
	str r0, [sp, #4]
_02243B16:
	ldr r0, [r7, #8]
	ldrb r6, [r0, r4]
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x20]
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1c
	sub r3, r0, #6
	sub r1, r1, r2
	mov r0, #0x1c
	ror r1, r0
	add r0, r2, r1
	add r0, r3, r0
	lsl r1, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x1c]
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x10]
	add r2, sp, #0x14
	ldr r0, [r0, #0x24]
	sub r1, r0, #6
	lsr r0, r6, #4
	add r0, r1, r0
	lsl r1, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x24]
	add r0, sp, #0x1c
	add r1, sp, #0x18
	bl FUN_020BB408
	ldr r0, [sp, #0x18]
	lsl r0, r0, #0xc
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	lsl r0, r0, #0xc
	str r0, [sp, #0x20]
	ldr r0, _02243BBC ; =0x022513A0
	ldr r1, [r0, #4]
	ldr r0, [sp, #4]
	add r0, r0, r1
	add r1, r5, r0
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	add r1, sp, #0x1c
	bl FUN_02020044
	ldr r0, [r7, #0x14]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, r0
	blt _02243B16
_02243B86:
	ldr r0, [sp, #8]
	add r7, r7, #4
	add r0, #8
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #3
	blt _02243B06
	ldr r0, [sp, #0x10]
	ldr r0, [r0, #0x30]
	add r1, r0, #1
	ldr r0, [sp, #0x10]
	cmp r1, #0x14
	str r1, [r0, #0x30]
	ble _02243BAC
	add sp, #0x28
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02243BAC:
	ldr r0, _02243BBC ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	bl FUN_0201FDEC
	mov r0, #0
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02243BBC: .word MOD18_022513A0
_02243BC0: .word 0x04000050
	thumb_func_end MOD18_02243A90

	thumb_func_start MOD18_02243BC4
MOD18_02243BC4: ; 0x02243BC4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x5c
	ldr r0, _02243CFC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009B78
	ldr r0, _02243CFC ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009D68
	ldr r0, _02243CFC ; =0x022513A0
	mov r1, #0
	ldr r0, [r0, #4]
	mov r3, #6
	str r1, [sp]
	sub r2, r1, #1
	str r2, [sp, #4]
	str r2, [sp, #8]
	str r1, [sp, #0xc]
	str r1, [sp, #0x10]
	lsl r3, r3, #6
	ldr r2, [r0, r3]
	str r2, [sp, #0x14]
	add r2, r3, #4
	ldr r2, [r0, r2]
	str r2, [sp, #0x18]
	add r2, r3, #0
	add r2, #8
	ldr r2, [r0, r2]
	str r2, [sp, #0x1c]
	add r2, r3, #0
	add r2, #0xc
	ldr r2, [r0, r2]
	add r3, #0x54
	str r2, [sp, #0x20]
	str r1, [sp, #0x24]
	add r0, r0, r3
	add r2, r1, #0
	add r3, r1, #0
	str r1, [sp, #0x28]
	bl FUN_02008AA4
	ldr r6, _02243CFC ; =0x022513A0
	mov r4, #0
	ldr r1, [r6, #4]
	mov r7, #0x4b
	ldr r0, [r1, #0x44]
	add r5, r4, #0
	str r0, [sp, #0x2c]
	mov r0, #0x75
	lsl r0, r0, #2
	add r0, r1, r0
	str r0, [sp, #0x30]
	mov r1, #2
	mov r0, #6
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	str r0, [sp, #0x38]
	lsr r0, r1, #5
	str r1, [sp, #0x34]
	str r4, [sp, #0x3c]
	str r0, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	add r0, sp, #0x2c
	strh r4, [r0, #0x20]
	mov r0, #1
	str r0, [sp, #0x54]
	mov r0, #4
	str r4, [sp, #0x50]
	str r0, [sp, #0x58]
	lsl r7, r7, #0xe
_02243C60:
	add r0, sp, #0x2c
	str r7, [sp, #0x34]
	str r7, [sp, #0x38]
	bl FUN_0201FE94
	ldr r1, [r6, #4]
	add r2, r1, r5
	mov r1, #0x7e
	lsl r1, r1, #2
	str r0, [r2, r1]
	cmp r4, #0
	bne _02243C9A
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_020200EC
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020130
	b _02243CBE
_02243C9A:
	cmp r4, #9
	ldr r0, [r6, #4]
	bge _02243CB0
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_02020130
	b _02243CBE
_02243CB0:
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #2
	bl FUN_02020130
_02243CBE:
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	bl FUN_02020208
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0x19
	blt _02243C60
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	add sp, #0x5c
	pop {r4, r5, r6, r7, pc}
	nop
_02243CFC: .word MOD18_022513A0
	thumb_func_end MOD18_02243BC4

	thumb_func_start MOD18_02243D00
MOD18_02243D00: ; 0x02243D00
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	str r0, [sp]
	ldr r0, [r7]
	cmp r0, #9
	bhi _02243E06
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02243D18: ; jump table
	.short _02243D2C - _02243D18 - 2 ; case 0
	.short _02243E06 - _02243D18 - 2 ; case 1
	.short _02243E06 - _02243D18 - 2 ; case 2
	.short _02243E06 - _02243D18 - 2 ; case 3
	.short _02243E06 - _02243D18 - 2 ; case 4
	.short _02243D68 - _02243D18 - 2 ; case 5
	.short _02243E06 - _02243D18 - 2 ; case 6
	.short _02243D74 - _02243D18 - 2 ; case 7
	.short _02243E06 - _02243D18 - 2 ; case 8
	.short _02243D8A - _02243D18 - 2 ; case 9
_02243D2C:
	mov r1, #3
	ldr r0, _02243E08 ; =0x0400006C
	mvn r1, r1
	bl GXx_SetMasterBrightness_
	bl FUN_0204F7E4
	ldr r0, _02243E0C ; =0x00000621
	bl FUN_020054C8
	ldr r1, _02243E10 ; =0x022513A0
	mov r0, #0x20
	ldr r1, [r1, #4]
	mov r2, #4
	add r1, #0x48
	bl FUN_02008C9C
	ldr r1, _02243E10 ; =0x022513A0
	ldr r2, [r1, #4]
	str r0, [r2, #0x44]
	ldr r0, [r1, #4]
	mov r2, #6
	add r0, #0x48
	mov r1, #0
	lsl r2, r2, #0x12
	bl FUN_02008D24
	mov r0, #5
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
_02243D68:
	add r0, r7, #0
	bl MOD18_02243BC4
	mov r0, #7
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
_02243D74:
	ldr r0, _02243E10 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x40]
	ldr r0, [r0, #8]
	bl MOD18_02243A90
	cmp r0, #0
	beq _02243E06
	mov r0, #9
	str r0, [r7]
	pop {r3, r4, r5, r6, r7, pc}
_02243D8A:
	ldr r0, _02243E14 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	add r0, #0x1c
	bl GXx_SetMasterBrightness_
	ldr r0, _02243E10 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x1a
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	bl FUN_02009C0C
	ldr r0, _02243E10 ; =0x022513A0
	ldr r1, [r0, #4]
	mov r0, #0x69
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	bl FUN_02009E04
	mov r4, #0
	ldr r6, _02243E10 ; =0x022513A0
	add r5, r4, #0
_02243DB8:
	ldr r0, [r6, #4]
	add r1, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02243DCA
	bl FUN_0201FFC8
_02243DCA:
	ldr r0, [r6, #4]
	mov r1, #0
	add r2, r0, r5
	mov r0, #0x7e
	lsl r0, r0, #2
	add r4, r4, #1
	add r5, r5, #4
	str r1, [r2, r0]
	cmp r4, #0x19
	blt _02243DB8
	ldr r0, _02243E10 ; =0x022513A0
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x44]
	bl FUN_0201FD58
	ldr r0, [sp]
	bl FUN_0200CAB4
	add r0, r7, #0
	bl FreeToHeap
	ldr r0, _02243E10 ; =0x022513A0
	mov r2, #0
	ldr r1, [r0, #4]
	mov r0, #0x29
	lsl r0, r0, #4
	str r2, [r1, r0]
	mov r0, #0x80
	bl FUN_0204F774
_02243E06:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02243E08: .word 0x0400006C
_02243E0C: .word 0x00000621
_02243E10: .word MOD18_022513A0
_02243E14: .word 0x04000050
	thumb_func_end MOD18_02243D00

	thumb_func_start MOD18_02243E18
MOD18_02243E18: ; 0x02243E18
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02243E84 ; =0x022513A0
	add r5, r1, #0
	ldr r1, [r0, #4]
	mov r0, #0x29
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r6, r2, #0
	add r7, r3, #0
	cmp r0, #0
	bne _02243E82
	mov r0, #4
	mov r1, #0x34
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x34
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #0x30]
	str r5, [r4, #0x20]
	str r6, [r4, #0x24]
	ldr r0, [sp, #0x18]
	str r7, [r4, #0x28]
	str r0, [r4, #0x2c]
	ldr r0, [sp, #0x1c]
	add r1, r4, #0
	str r0, [r4, #8]
	ldr r0, [sp, #0x24]
	mov r2, #0x64
	str r0, [r4, #0xc]
	ldr r0, [sp, #0x2c]
	str r0, [r4, #0x10]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x14]
	ldr r0, [sp, #0x28]
	str r0, [r4, #0x18]
	ldr r0, [sp, #0x30]
	str r0, [r4, #0x1c]
	ldr r0, _02243E88 ; =MOD18_02243D00
	bl FUN_0200CA44
	ldr r1, _02243E84 ; =0x022513A0
	ldr r2, [r1, #4]
	mov r1, #0x29
	lsl r1, r1, #4
	str r0, [r2, r1]
	mov r0, #0x80
	bl FUN_0204F74C
_02243E82:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02243E84: .word MOD18_022513A0
_02243E88: .word MOD18_02243D00
	thumb_func_end MOD18_02243E18

	thumb_func_start MOD18_02243E8C
MOD18_02243E8C: ; 0x02243E8C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	ldr r1, _02243F58 ; =0x022513A0
	add r6, r0, #0
	ldr r1, [r1, #4]
	cmp r1, #0
	bne _02243EA6
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}
_02243EA6:
	ldr r5, [r4, #8]
	add r0, r5, #0
	bl FUN_0204F72C
	add r1, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	beq _02243EBE
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _02243EE2
_02243EBE:
	ldr r2, _02243F58 ; =0x022513A0
	lsl r1, r5, #2
	ldr r3, [r2, #4]
	mov r0, #0
	str r0, [r3, r1]
	ldr r2, [r2, #4]
	add r1, r2, r1
	str r0, [r1, #0x20]
	add r0, r6, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0204E254
	pop {r4, r5, r6, pc}
_02243EE2:
	ldr r0, [r4, #0xc]
	cmp r0, #0xe
	bhi _02243F14
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02243EF4: ; jump table
	.short _02243F14 - _02243EF4 - 2 ; case 0
	.short _02243F12 - _02243EF4 - 2 ; case 1
	.short _02243F12 - _02243EF4 - 2 ; case 2
	.short _02243F12 - _02243EF4 - 2 ; case 3
	.short _02243F12 - _02243EF4 - 2 ; case 4
	.short _02243F12 - _02243EF4 - 2 ; case 5
	.short _02243F12 - _02243EF4 - 2 ; case 6
	.short _02243F12 - _02243EF4 - 2 ; case 7
	.short _02243F12 - _02243EF4 - 2 ; case 8
	.short _02243F14 - _02243EF4 - 2 ; case 9
	.short _02243F14 - _02243EF4 - 2 ; case 10
	.short _02243F14 - _02243EF4 - 2 ; case 11
	.short _02243F14 - _02243EF4 - 2 ; case 12
	.short _02243F12 - _02243EF4 - 2 ; case 13
	.short _02243F12 - _02243EF4 - 2 ; case 14
_02243F12:
	pop {r4, r5, r6, pc}
_02243F14:
	ldr r0, [r4, #4]
	add r0, r0, #1
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1d
	str r0, [r4, #4]
	sub r2, r2, r3
	mov r0, #0x1d
	ror r2, r0
	add r0, r3, r2
	bne _02243F54
	cmp r1, #3
	bhi _02243F4E
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02243F38: ; jump table
	.short _02243F40 - _02243F38 - 2 ; case 0
	.short _02243F44 - _02243F38 - 2 ; case 1
	.short _02243F48 - _02243F38 - 2 ; case 2
	.short _02243F4C - _02243F38 - 2 ; case 3
_02243F40:
	mov r1, #3
	b _02243F4E
_02243F44:
	mov r1, #2
	b _02243F4E
_02243F48:
	mov r1, #0
	b _02243F4E
_02243F4C:
	mov r1, #1
_02243F4E:
	add r0, r5, #0
	bl FUN_0204F70C
_02243F54:
	pop {r4, r5, r6, pc}
	nop
_02243F58: .word MOD18_022513A0
	thumb_func_end MOD18_02243E8C

	thumb_func_start MOD18_02243F5C
MOD18_02243F5C: ; 0x02243F5C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _02243FAC ; =0x022513A0
	add r7, r1, #0
	ldr r1, [r0, #4]
	cmp r1, #0
	beq _02243FA8
	ldr r0, _02243FB0 ; =0x00000B46
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _02243FA8
	lsl r5, r6, #2
	ldr r4, [r1, r5]
	cmp r4, #0
	bne _02243FA4
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x10
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _02243FAC ; =0x022513A0
	add r1, r4, #0
	ldr r0, [r0, #4]
	mov r2, #0x64
	str r4, [r0, r5]
	ldr r0, _02243FB4 ; =MOD18_02243E8C
	bl FUN_0200CA44
	ldr r1, _02243FAC ; =0x022513A0
	ldr r1, [r1, #4]
	add r1, r1, r5
	str r0, [r1, #0x20]
_02243FA4:
	str r6, [r4, #8]
	str r7, [r4, #0xc]
_02243FA8:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02243FAC: .word MOD18_022513A0
_02243FB0: .word 0x00000B46
_02243FB4: .word MOD18_02243E8C
	thumb_func_end MOD18_02243F5C

	thumb_func_start MOD18_02243FB8
MOD18_02243FB8: ; 0x02243FB8
	push {r3, r4, r5, lr}
	ldr r1, _02243FEC ; =0x022513A0
	add r5, r0, #0
	ldr r1, [r1, #4]
	lsl r4, r5, #2
	ldr r1, [r1, r4]
	cmp r1, #0
	beq _02243FE8
	bl FUN_0204F0A8
	ldr r0, _02243FEC ; =0x022513A0
	mov r2, #1
	ldr r1, [r0, #4]
	ldr r1, [r1, r4]
	str r2, [r1]
	ldr r1, [r0, #4]
	mov r2, #0
	str r2, [r1, r4]
	ldr r0, [r0, #4]
	add r0, r0, r4
	str r2, [r0, #0x20]
	add r0, r5, #0
	bl FUN_0204E254
_02243FE8:
	pop {r3, r4, r5, pc}
	nop
_02243FEC: .word MOD18_022513A0
	thumb_func_end MOD18_02243FB8

	thumb_func_start MOD18_02243FF0
MOD18_02243FF0: ; 0x02243FF0
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	ldr r4, _02244024 ; =0x022513A0
	add r5, r6, #0
	add r7, r6, #0
_02243FFA:
	ldr r0, [r4, #4]
	add r0, r0, r5
	ldr r0, [r0, #0x20]
	cmp r0, #0
	beq _0224401A
	bl FUN_0200CAB4
	ldr r0, [r4, #4]
	ldr r0, [r0, r5]
	bl FreeToHeap
	ldr r0, [r4, #4]
	add r0, r0, r5
	str r7, [r0, #0x20]
	ldr r0, [r4, #4]
	str r7, [r0, r5]
_0224401A:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #8
	blt _02243FFA
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02244024: .word MOD18_022513A0
	thumb_func_end MOD18_02243FF0

	thumb_func_start MOD18_02244028
MOD18_02244028: ; 0x02244028
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	str r1, [sp]
	add r5, r0, #0
	str r2, [sp, #4]
	add r0, r3, #0
	mov r1, #0x24
	str r3, [sp, #8]
	bl AllocFromHeap
	str r0, [sp, #0xc]
	mov r1, #0
	mov r2, #0x24
	bl MI_CpuFill8
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0xc]
	cmp r1, #0
	str r1, [r0]
	beq _0224409E
	ldr r1, [sp, #0x2c]
	str r1, [r0, #4]
	ldr r1, [sp, #0x30]
	strb r1, [r0, #0x1e]
	ldr r0, [sp, #8]
	bl ListMenuCursorNew
	ldr r1, [sp, #0xc]
	str r0, [r1, #0x10]
	ldr r1, _022440C0 ; =0x0008090F
	bl ListMenuCursorSetColor
	ldr r1, [sp, #8]
	ldr r0, [sp, #0xc]
	strb r1, [r0, #0x1d]
	ldr r1, [sp, #0xc]
	ldrh r0, [r5, #0x10]
	ldrb r1, [r1, #0x1d]
	bl ListMenuItems_ctor
	add r7, r0, #0
	ldrh r0, [r5, #0x10]
	mov r6, #0
	cmp r0, #0
	ble _02244098
	add r4, r6, #0
_02244084:
	ldr r1, [r5]
	add r0, r7, #0
	add r1, r1, r4
	bl ListMenuItems_CopyItem
	ldrh r0, [r5, #0x10]
	add r6, r6, #1
	add r4, #8
	cmp r6, r0
	blt _02244084
_02244098:
	ldr r0, [sp, #0xc]
	str r7, [r5]
	str r7, [r0, #8]
_0224409E:
	ldr r1, [sp]
	ldr r0, [sp, #4]
	add r1, r1, r0
	ldr r0, [sp, #0xc]
	strh r1, [r0, #0x20]
	ldr r1, [sp]
	ldr r2, [sp, #4]
	ldr r3, [sp, #8]
	add r0, r5, #0
	bl ListMenuInit
	ldr r1, [sp, #0xc]
	str r0, [r1, #0xc]
	add r0, r1, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022440C0: .word 0x0008090F
	thumb_func_end MOD18_02244028

	thumb_func_start MOD18_022440C4
MOD18_022440C4: ; 0x022440C4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r2, #0
	add r5, r0, #0
	add r7, r1, #0
	ldrh r1, [r4, #0x14]
	ldrh r0, [r4, #0x16]
	add r0, r1, r0
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	ldr r0, [r4, #0xc]
	mov r1, #3
	bl ListMenuGetTemplateField
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldrh r0, [r4, #0x18]
	cmp r0, r5
	bne _022440F0
	ldrh r0, [r4, #0x1a]
	cmp r0, r7
	beq _0224413A
_022440F0:
	strh r5, [r4, #0x18]
	add r0, r5, r1
	strh r7, [r4, #0x1a]
	cmp r0, r6
	blt _0224413A
	cmp r5, r6
	bhi _0224413A
	ldr r0, [r4, #0xc]
	mov r1, #7
	bl ListMenuGetTemplateField
	str r0, [sp]
	ldr r0, [r4, #0xc]
	mov r1, #9
	bl ListMenuGetTemplateField
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [r4, #0xc]
	mov r1, #8
	bl ListMenuGetTemplateField
	str r0, [sp, #4]
	sub r0, r6, r5
	add r5, r7, #0
	mul r5, r0
	ldr r0, [r4, #0xc]
	mov r1, #0x12
	bl ListMenuGetTemplateField
	ldr r3, [sp, #4]
	add r1, r0, #0
	ldr r0, [r4, #0x10]
	ldr r2, [sp]
	add r3, r5, r3
	bl ListMenuUpdateCursorObj
_0224413A:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_022440C4

	thumb_func_start MOD18_02244140
MOD18_02244140: ; 0x02244140
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	str r0, [sp, #4]
	ldr r0, [r5]
	cmp r0, #0
	beq _0224418A
	ldr r0, [sp, #4]
	mov r1, #2
	bl ListMenuGetTemplateField
	add r7, r0, #0
	add r1, sp, #0xc
	ldr r0, [sp, #4]
	add r1, #2
	add r2, sp, #0xc
	bl ListMenuGetScrollAndRow
	ldrb r0, [r5, #0x1c]
	cmp r0, #0
	bne _0224416E
	b _0224428C
_0224416E:
	add r1, sp, #0xc
	ldrh r0, [r1, #2]
	ldrh r1, [r1]
	add r2, r5, #0
	bl MOD18_022440C4
	ldr r0, _02244310 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _0224418C
	mov r0, #4
	tst r0, r1
	bne _0224418C
_0224418A:
	b _022442CA
_0224418C:
	ldr r0, _02244314 ; =0x000005DC
	bl FUN_020054C8
	add r0, sp, #0xc
	ldrh r1, [r0, #2]
	ldrh r0, [r0]
	add r2, r1, r0
	sub r0, r7, #1
	cmp r0, r2
	bne _022441A8
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_022441A8:
	ldrh r1, [r5, #0x14]
	ldrh r0, [r5, #0x16]
	add r1, r1, r0
	cmp r2, r1
	bne _022441BA
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_022441BA:
	ldr r0, [r5, #4]
	ldr r3, [r5]
	blx r3
	ldrb r1, [r5, #0x1d]
	add r0, r7, #0
	bl ListMenuItems_ctor
	mov r4, #0
	add r6, r4, #0
	str r0, [sp]
	cmp r7, #0
	ble _02244210
_022441D2:
	ldrh r1, [r5, #0x14]
	ldrh r0, [r5, #0x16]
	add r0, r1, r0
	cmp r6, r0
	bne _022441DE
	b _022441EA
_022441DE:
	ldr r2, [r5, #8]
	lsl r1, r4, #3
	ldr r0, [sp]
	add r1, r2, r1
	bl ListMenuItems_CopyItem
_022441EA:
	add r0, sp, #0xc
	ldrh r1, [r0, #2]
	ldrh r0, [r0]
	add r4, r4, #1
	add r0, r1, r0
	cmp r6, r0
	bne _0224420A
	ldrh r2, [r5, #0x14]
	ldrh r1, [r5, #0x16]
	ldr r3, [r5, #8]
	ldr r0, [sp]
	add r1, r2, r1
	lsl r1, r1, #3
	add r1, r3, r1
	bl ListMenuItems_CopyItem
_0224420A:
	add r6, r6, #1
	cmp r6, r7
	blt _022441D2
_02244210:
	ldrb r0, [r5, #0x1e]
	cmp r0, #0
	beq _02244254
	sub r0, r7, #1
	mov r4, #0
	str r0, [sp, #8]
	cmp r0, #0
	ble _02244246
	ldr r6, [sp]
	add r7, r4, #0
_02244224:
	ldr r0, [r5, #4]
	add r1, r4, #0
	bl FUN_02025F0C
	cmp r0, #0
	bne _02244234
	mov r0, #1
	b _02244236
_02244234:
	mov r0, #0
_02244236:
	add r0, r7, r0
	str r0, [r6, #4]
	ldr r0, [sp, #8]
	add r4, r4, #1
	add r7, r7, #2
	add r6, #8
	cmp r4, r0
	blt _02244224
_02244246:
	lsl r0, r4, #1
	add r2, r0, #1
	ldr r0, [sp]
	lsl r1, r4, #3
	add r0, r0, r1
	str r2, [r0, #4]
	b _02244268
_02244254:
	sub r0, r7, #1
	mov r2, #0
	cmp r0, #0
	ble _02244268
	ldr r1, [sp]
_0224425E:
	str r2, [r1, #4]
	add r2, r2, #1
	add r1, #8
	cmp r2, r0
	blt _0224425E
_02244268:
	ldr r0, [r5, #8]
	bl FreeToHeap
	ldr r0, [sp]
	ldr r1, [sp]
	str r0, [r5, #8]
	ldr r0, [sp, #4]
	bl ListMenuGetItemStr
	mov r0, #0
	strb r0, [r5, #0x1c]
	ldr r0, [sp, #4]
	bl RedrawListMenu
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_0224428C:
	ldr r0, _02244310 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #4
	tst r0, r1
	beq _022442CA
	ldr r0, _02244314 ; =0x000005DC
	bl FUN_020054C8
	add r0, sp, #0xc
	ldrh r3, [r0, #2]
	ldrh r1, [r0]
	sub r2, r7, #1
	add r1, r3, r1
	cmp r2, r1
	bne _022442B2
	mov r0, #0
	add sp, #0x10
	mvn r0, r0
	pop {r3, r4, r5, r6, r7, pc}
_022442B2:
	strh r3, [r5, #0x14]
	ldrh r1, [r0]
	add sp, #0x10
	strh r1, [r5, #0x16]
	ldrh r1, [r0, #2]
	strh r1, [r5, #0x18]
	ldrh r0, [r0]
	strh r0, [r5, #0x1a]
	mov r0, #1
	strb r0, [r5, #0x1c]
	sub r0, r0, #2
	pop {r3, r4, r5, r6, r7, pc}
_022442CA:
	ldr r0, [sp, #4]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r1, r5, #0
	ldr r0, [sp, #4]
	add r1, #0x20
	ldrh r6, [r5, #0x20]
	bl ListMenuGetCurrentItemArrayId
	ldrh r0, [r5, #0x20]
	cmp r6, r0
	beq _022442EA
	ldr r0, _02244314 ; =0x000005DC
	bl FUN_020054C8
_022442EA:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _022442FA
	add r0, r0, #1
	cmp r4, r0
	beq _02244308
	b _02244302
_022442FA:
	ldr r0, _02244314 ; =0x000005DC
	bl FUN_020054C8
	b _02244308
_02244302:
	ldr r0, _02244314 ; =0x000005DC
	bl FUN_020054C8
_02244308:
	add r0, r4, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244310: .word gMain
_02244314: .word 0x000005DC
	thumb_func_end MOD18_02244140

	thumb_func_start MOD18_02244318
MOD18_02244318: ; 0x02244318
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl DestroyListMenu
	ldr r0, [r4]
	cmp r0, #0
	beq _02244334
	ldr r0, [r4, #0x10]
	bl DestroyListMenuCursorObj
	ldr r0, [r4, #8]
	bl FreeToHeap
_02244334:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD18_02244318

	thumb_func_start MOD18_0224433C
MOD18_0224433C: ; 0x0224433C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x60
	add r4, r1, #0
	mov r1, #0x6e
	lsl r1, r1, #2
	ldr r2, [r4, r1]
	str r2, [sp, #0x2c]
	ldr r2, _022445E8 ; =0x022513A8
	str r4, [r2]
	ldr r2, [r4]
	cmp r2, #8
	bls _02244356
	b _022445E4
_02244356:
	add r3, r2, r2
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_02244362: ; jump table
	.short _02244374 - _02244362 - 2 ; case 0
	.short _0224439E - _02244362 - 2 ; case 1
	.short _022444A4 - _02244362 - 2 ; case 2
	.short _022444AC - _02244362 - 2 ; case 3
	.short _022444DE - _02244362 - 2 ; case 4
	.short _022444E6 - _02244362 - 2 ; case 5
	.short _02244550 - _02244362 - 2 ; case 6
	.short _0224456C - _02244362 - 2 ; case 7
	.short _022445D8 - _02244362 - 2 ; case 8
_02244374:
	mov r1, #0x39
	lsl r1, r1, #4
	ldr r0, [sp, #0x2c]
	add r1, r4, r1
	bl MOD18_0224486C
	add r1, r4, #0
	add r0, r4, #4
	add r1, #0x44
	bl MOD18_022445EC
	mov r0, #0xeb
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD18_02244B28
	ldr r0, [r4]
	add sp, #0x60
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224439E:
	add r0, r4, #0
	bl MOD18_02244998
	mov r1, #0xfa
	lsl r1, r1, #2
	mov r0, #0
	mov r3, #0xba
	str r1, [sp]
	mvn r0, r0
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	lsl r3, r3, #2
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
	add r3, #0x20
	str r2, [sp, #0x20]
	str r0, [sp, #0x24]
	str r0, [sp, #0x28]
	add r0, r4, r3
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_02008AA4
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	mov r1, #2
	str r0, [sp, #0x30]
	mov r0, #0xc2
	lsl r0, r0, #2
	add r0, r4, r0
	str r0, [sp, #0x34]
	mov r0, #0x12
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	str r0, [sp, #0x3c]
	lsr r0, r1, #5
	mov r6, #0
	mov r7, #0xcb
	str r1, [sp, #0x38]
	str r6, [sp, #0x40]
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	add r0, sp, #0x30
	strh r6, [r0, #0x20]
	mov r0, #2
	str r0, [sp, #0x58]
	mov r0, #4
	str r6, [sp, #0x54]
	str r0, [sp, #0x5c]
	add r5, r4, #0
	lsl r7, r7, #2
_02244422:
	add r0, sp, #0x30
	bl FUN_0201FE94
	mov r1, #0xcb
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	ldr r0, [r5, r7]
	mov r1, #0
	bl FUN_020200A0
	cmp r6, #0
	bne _02244450
	mov r0, #0xcb
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_02020130
_02244450:
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #8
	blt _02244422
	mov r7, #0xd3
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_02244460:
	add r0, sp, #0x30
	bl FUN_0201FE94
	mov r1, #0xd3
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r0, r1, #0
	ldr r0, [r5, r0]
	mov r1, #1
	bl FUN_020200BC
	mov r0, #0xd3
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r1, #0
	bl FUN_020200A0
	ldr r0, [r5, r7]
	mov r1, #2
	bl FUN_02020130
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #0x11
	blt _02244460
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineBToggleLayers
	ldr r0, [r4]
	add sp, #0x60
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022444A4:
	add r0, r2, #1
	add sp, #0x60
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022444AC:
	mov r0, #8
	mov r1, #1
	bl GX_EngineBToggleLayers
	mov r0, #4
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	mov r0, #1
	add r1, r0, #0
	bl GX_EngineBToggleLayers
	mov r0, #4
	mov r1, #0
	bl FUN_02017FE4
	ldr r0, [r4]
	add sp, #0x60
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022444DE:
	add r0, r2, #1
	add sp, #0x60
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022444E6:
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r2, r4, #0
	ldr r0, [r0, #0x38]
	add r1, r4, #4
	add r2, #0x44
	bl MOD18_02244634
	mov r1, #0xcb
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0x44
	add r1, r4, r1
	bl MOD18_022446E8
	add r0, r4, #0
	add r0, #0xa4
	bl MOD18_02244754
	mov r1, #0xd3
	add r0, r4, #0
	lsl r1, r1, #2
	add r0, #0xa4
	add r1, r4, r1
	bl MOD18_0224479C
	mov r3, #0xea
	lsl r3, r3, #2
	add r0, r4, r3
	str r0, [sp]
	add r0, r3, #4
	add r0, r4, r0
	str r0, [sp, #4]
	mov r0, #0x6e
	lsl r0, r0, #2
	add r1, r3, #0
	add r2, r3, #0
	sub r1, #0x18
	sub r2, #8
	sub r3, r3, #4
	ldr r0, [r4, r0]
	add r1, r4, r1
	add r2, r4, r2
	add r3, r4, r3
	bl MOD18_02244A70
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FDEC
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
_02244550:
	mov r0, #0x3a
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0
	beq _022445E4
	ldr r0, [r4]
	add sp, #0x60
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_0224456C:
	mov r0, #0xbe
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02009C0C
	mov r0, #0xbf
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_02009E04
	mov r7, #0xba
	mov r6, #0
	add r5, r4, #0
	lsl r7, r7, #2
_02244588:
	ldr r0, [r5, r7]
	bl FUN_02008E2C
	add r6, r6, #1
	add r5, r5, #4
	cmp r6, #4
	blt _02244588
	mov r0, #0x6f
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl FUN_0201FD58
	mov r0, #0x39
	lsl r0, r0, #4
	add r0, r4, r0
	mov r1, #0
	bl FUN_0200D0E0
	mov r0, #0x39
	lsl r0, r0, #4
	add r0, r4, r0
	bl FUN_02019178
	ldr r0, [sp, #0x2c]
	mov r1, #7
	bl FUN_020178A0
	ldr r0, [sp, #0x2c]
	bl MOD18_02244858
	mov r0, #0xeb
	lsl r0, r0, #2
	add r0, r4, r0
	bl MOD18_02244B7C
	ldr r0, [r4]
	add sp, #0x60
	add r0, r0, #1
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_022445D8:
	sub r1, r1, #4
	ldr r1, [r4, r1]
	mov r2, #0
	str r2, [r1, #0x68]
	bl FUN_0200621C
_022445E4:
	add sp, #0x60
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022445E8: .word MOD18_022513A8
	thumb_func_end MOD18_0224433C

	thumb_func_start MOD18_022445EC
MOD18_022445EC: ; 0x022445EC
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, _02244630 ; =0x022513AC
	add r6, r0, #0
	add r5, r1, #0
	mov r7, #0
_022445F6:
	mov r0, #0
	str r0, [r6]
	str r0, [r6, #4]
	str r0, [r5]
	str r0, [r5, #4]
	str r0, [r5, #8]
	bl LCRandom
	mov r1, #0x7d
	lsl r1, r1, #2
	bl _s32_div_f
	add r1, #0x32
	str r1, [r4]
	bl LCRandom
	mov r1, #0x7d
	lsl r1, r1, #2
	bl _s32_div_f
	add r1, #0x32
	str r1, [r4, #4]
	add r7, r7, #1
	add r6, #8
	add r5, #0xc
	add r4, #8
	cmp r7, #8
	blt _022445F6
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02244630: .word MOD18_022513AC
	thumb_func_end MOD18_022445EC

	thumb_func_start MOD18_02244634
MOD18_02244634: ; 0x02244634
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	str r0, [sp]
	add r4, r2, #0
	mov r7, #0
	add r6, r5, #0
_02244640:
	add r0, r7, #0
	bl FUN_0204E3EC
	str r0, [r6]
	add r0, r7, #0
	bl FUN_0204E440
	str r0, [r6, #4]
	add r7, r7, #1
	add r6, #8
	cmp r7, #8
	blt _02244640
	bl FUN_02030F40
	cmp r0, #0
	beq _022446AA
	bl FUN_02031190
	bl FUN_02030E7C
	cmp r0, #0
	bne _0224467E
	ldr r0, [sp]
	bl FUN_02055320
	str r0, [r5]
	ldr r0, [sp]
	bl FUN_0205532C
	str r0, [r5, #4]
	b _022446AA
_0224467E:
	ldr r7, [r5]
	ldr r6, [r5, #4]
	bl FUN_02031190
	lsl r0, r0, #3
	ldr r0, [r5, r0]
	str r0, [r5]
	bl FUN_02031190
	lsl r0, r0, #3
	add r0, r5, r0
	ldr r0, [r0, #4]
	str r0, [r5, #4]
	bl FUN_02031190
	lsl r0, r0, #3
	str r7, [r5, r0]
	bl FUN_02031190
	lsl r0, r0, #3
	add r0, r5, r0
	str r6, [r0, #4]
_022446AA:
	mov r6, #0
	mov r7, #0x3c
_022446AE:
	ldr r0, [r5]
	ldr r1, [r5, #4]
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _022446CA
	ldr r0, [r5]
	sub r0, #0x20
	str r0, [r4]
	ldr r0, [r5, #4]
	sub r0, #0x40
	str r0, [r4, #4]
	str r7, [r4, #8]
	b _022446DA
_022446CA:
	ldr r1, [r4, #8]
	cmp r1, #0
	beq _022446DA
	ldr r0, [r4]
	cmp r0, #0
	blt _022446DA
	sub r0, r1, #1
	str r0, [r4, #8]
_022446DA:
	add r6, r6, #1
	add r5, #8
	add r4, #0xc
	cmp r6, #8
	blt _022446AE
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_02244634

	thumb_func_start MOD18_022446E8
MOD18_022446E8: ; 0x022446E8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r7, #1
	add r5, r0, #0
	add r4, r1, #0
	mov r6, #0
	lsl r7, r7, #0xc
_022446F6:
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _0224473C
	ldr r1, [r5]
	mov r0, #0x8a
	mul r0, r1
	mov r1, #7
	lsl r1, r1, #6
	bl _s32_div_f
	add r0, #0x3c
	lsl r0, r0, #0xc
	str r0, [sp]
	ldr r0, [r5, #4]
	mov r1, #0x1a
	lsl r0, r0, #7
	lsl r1, r1, #4
	bl _s32_div_f
	add r0, #9
	lsl r1, r0, #0xc
	mov r0, #3
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r7, [sp, #8]
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0
	bl FUN_02020044
	ldr r0, [r4]
	mov r1, #1
	bl FUN_020200A0
	b _02244744
_0224473C:
	ldr r0, [r4]
	mov r1, #0
	bl FUN_020200A0
_02244744:
	add r6, r6, #1
	add r5, #0xc
	add r4, r4, #4
	cmp r6, #8
	blt _022446F6
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_022446E8

	thumb_func_start MOD18_02244754
MOD18_02244754: ; 0x02244754
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r4, #0
_0224475A:
	add r0, r4, #0
	bl MOD18_0223E314
	add r6, r0, #0
	add r0, r4, #0
	bl MOD18_0223E37C
	add r7, r0, #0
	add r0, r4, #0
	bl MOD18_0223E3E4
	str r0, [sp]
	add r0, r6, #0
	add r1, r7, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _0224478A
	sub r6, #0x20
	str r6, [r5]
	sub r7, #0x40
	str r7, [r5, #4]
	ldr r0, [sp]
	b _02244790
_0224478A:
	mov r0, #0
	str r0, [r5]
	str r0, [r5, #4]
_02244790:
	add r4, r4, #1
	str r0, [r5, #8]
	add r5, #0x10
	cmp r4, #0x11
	blt _0224475A
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_02244754

	thumb_func_start MOD18_0224479C
MOD18_0224479C: ; 0x0224479C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	mov r7, #1
	add r5, r0, #0
	add r4, r1, #0
	mov r6, #0
	lsl r7, r7, #0xc
_022447AA:
	ldr r1, [r5]
	cmp r1, #0
	beq _02244808
	mov r0, #0x8a
	mul r0, r1
	mov r1, #7
	lsl r1, r1, #6
	bl _s32_div_f
	add r0, #0x3c
	lsl r0, r0, #0xc
	str r0, [sp]
	ldr r0, [r5, #4]
	mov r1, #0x1a
	lsl r0, r0, #7
	lsl r1, r1, #4
	bl _s32_div_f
	add r0, #9
	lsl r1, r0, #0xc
	mov r0, #3
	lsl r0, r0, #0x12
	add r0, r1, r0
	str r7, [sp, #8]
	str r0, [sp, #4]
	ldr r0, [r4]
	add r1, sp, #0
	bl FUN_02020044
	ldr r1, [r5, #8]
	ldr r0, [r5, #0xc]
	cmp r1, r0
	beq _02244810
	cmp r1, #0
	ldr r0, [r4]
	beq _02244800
	bl FUN_02020130
	ldr r0, [r4]
	mov r1, #1
	bl FUN_020200A0
	b _02244810
_02244800:
	mov r1, #0
	bl FUN_020200A0
	b _02244810
_02244808:
	ldr r0, [r4]
	mov r1, #0
	bl FUN_020200A0
_02244810:
	ldr r0, [r5, #8]
	add r6, r6, #1
	str r0, [r5, #0xc]
	add r5, #0x10
	add r4, r4, #4
	cmp r6, #0x11
	blt _022447AA
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0224479C

	thumb_func_start MOD18_02244824
MOD18_02244824: ; 0x02244824
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0x4e
	mov r2, #4
	ldr r0, _02244848 ; =MOD18_0224433C
	lsl r1, r1, #4
	add r3, r2, #0
	bl FUN_020061E8
	bl FUN_0201B6C8
	mov r1, #0x6d
	lsl r1, r1, #2
	str r4, [r0, r1]
	ldr r2, [r4, #8]
	add r1, r1, #4
	str r2, [r0, r1]
	pop {r4, pc}
	.align 2, 0
_02244848: .word MOD18_0224433C
	thumb_func_end MOD18_02244824

	thumb_func_start MOD18_0224484C
MOD18_0224484C: ; 0x0224484C
	ldr r1, [r0]
	cmp r1, #5
	bne _02244856
	mov r1, #6
	str r1, [r0]
_02244856:
	bx lr
	thumb_func_end MOD18_0224484C

	thumb_func_start MOD18_02244858
MOD18_02244858: ; 0x02244858
	push {r4, lr}
	add r4, r0, #0
	mov r1, #4
	bl FUN_020178A0
	add r0, r4, #0
	mov r1, #5
	bl FUN_020178A0
	pop {r4, pc}
	thumb_func_end MOD18_02244858

	thumb_func_start MOD18_0224486C
MOD18_0224486C: ; 0x0224486C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x64
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #1
	mov r1, #0
	bl FUN_0200E3A0
	add r0, r5, #0
	bl MOD18_02244858
	ldr r6, _0224498C ; =0x022504B4
	add r3, sp, #0x48
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #4
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #1
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r6, _02244990 ; =0x02250498
	add r3, sp, #0x2c
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #5
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #2
	mov r1, #0
	bl GX_EngineBToggleLayers
	ldr r6, _02244994 ; =0x0225047C
	add r3, sp, #0x10
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	mov r1, #7
	str r0, [r3]
	add r0, r5, #0
	mov r3, #0
	bl FUN_02016C18
	mov r0, #8
	mov r1, #0
	bl GX_EngineBToggleLayers
	add r0, r5, #0
	mov r1, #7
	bl FUN_02018744
	mov r0, #0x40
	mov r1, #0
	str r0, [sp]
	mov r2, #4
	mov r0, #0x1c
	add r3, r1, #0
	str r2, [sp, #4]
	bl FUN_02006930
	mov r1, #0
	mov r0, #5
	str r1, [sp]
	lsl r0, r0, #0xa
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r3, #4
	mov r0, #0x1c
	mov r1, #1
	add r2, r5, #0
	str r3, [sp, #0xc]
	bl FUN_0200687C
	mov r1, #0
	mov r0, #6
	str r1, [sp]
	lsl r0, r0, #8
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r3, #4
	mov r0, #0x1c
	mov r1, #2
	add r2, r5, #0
	str r3, [sp, #0xc]
	bl FUN_020068C8
	mov r0, #4
	mov r1, #0
	bl FUN_02054590
	mov r0, #7
	mov r1, #0x20
	mov r2, #0
	mov r3, #4
	bl FUN_02017F18
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #7
	bl FUN_020545B8
	add r0, r4, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r3, #0x80
	str r3, [sp]
	mov r2, #4
	mov r0, #0x32
	mov r1, #0x34
	add r3, #0xc0
	str r2, [sp, #4]
	bl FUN_02006930
	mov r0, #1
	bl FUN_0200E394
	add sp, #0x64
	pop {r3, r4, r5, r6, pc}
	nop
_0224498C: .word MOD18_022504B4
_02244990: .word MOD18_02250498
_02244994: .word MOD18_0225047C
	thumb_func_end MOD18_0224486C

	thumb_func_start MOD18_02244998
MOD18_02244998: ; 0x02244998
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r1, #7
	add r6, r0, #0
	lsl r1, r1, #6
	mov r0, #0x19
	add r1, r6, r1
	mov r2, #4
	bl FUN_02008C9C
	mov r1, #0x6f
	lsl r1, r1, #2
	mov r7, #0xba
	str r0, [r6, r1]
	mov r4, #0
	add r5, r6, #0
	lsl r7, r7, #2
_022449BA:
	mov r0, #1
	add r1, r4, #0
	mov r2, #4
	bl FUN_02008DEC
	str r0, [r5, r7]
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _022449BA
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r2, #4
	mov r0, #0xba
	str r2, [sp, #8]
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	mov r1, #0x1c
	mov r3, #0
	bl FUN_02008F34
	mov r1, #0xbe
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r0, r1, #0
	add r0, #0xf0
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #4
	sub r1, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r6, r1]
	mov r1, #0x1c
	mov r2, #3
	mov r3, #0
	bl FUN_02008FEC
	mov r1, #0xbf
	lsl r1, r1, #2
	str r0, [r6, r1]
	add r0, r1, #0
	add r0, #0xec
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x1c
	mov r2, #5
	mov r3, #0
	bl FUN_020090AC
	mov r1, #3
	lsl r1, r1, #8
	str r0, [r6, r1]
	add r0, r1, #0
	add r0, #0xe8
	str r0, [sp]
	mov r0, #3
	str r0, [sp, #4]
	mov r0, #4
	sub r1, #0xc
	str r0, [sp, #8]
	ldr r0, [r6, r1]
	mov r1, #0x1c
	mov r2, #6
	mov r3, #0
	bl FUN_020090AC
	mov r1, #0xc1
	lsl r1, r1, #2
	str r0, [r6, r1]
	sub r1, #0xc
	ldr r0, [r6, r1]
	bl FUN_02009B04
	mov r0, #0xbf
	lsl r0, r0, #2
	ldr r0, [r6, r0]
	bl FUN_02009D68
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_02244998

	thumb_func_start MOD18_02244A70
MOD18_02244A70: ; 0x02244A70
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r4, [sp, #0x2c]
	str r1, [sp, #0xc]
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	add r7, r2, #0
	add r6, r3, #0
	ldr r5, [sp, #0x28]
	bl MOD18_0223E1FC
	cmp r0, #0
	beq _02244AA6
_02244A8C:
	add r1, r4, #0
	add r1, #0x80
	ldr r1, [r1]
	add r0, r4, #0
	bl MOD18_02244C48
	add r0, r4, #0
	add r0, #0x80
	ldr r0, [r0]
	bl MOD18_0223E1FC
	cmp r0, #0
	bne _02244A8C
_02244AA6:
	ldr r0, [r6]
	cmp r0, #0
	beq _02244AB8
	cmp r0, #1
	beq _02244ADE
	cmp r0, #2
	beq _02244AF8
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02244AB8:
	add r0, r4, #0
	bl MOD18_02244CC8
	add r2, r0, #0
	beq _02244B24
	mov r0, #0x10
	str r0, [sp]
	mov r1, #1
	str r1, [sp, #4]
	mov r3, #0
	ldr r0, [sp, #0xc]
	str r3, [sp, #8]
	bl AddTextPrinterParameterized
	str r0, [r7]
	mov r0, #1
	add sp, #0x10
	str r0, [r6]
	pop {r3, r4, r5, r6, r7, pc}
_02244ADE:
	ldr r0, [r7]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020546C8
	cmp r0, #0
	beq _02244B24
	mov r0, #2
	str r0, [r6]
	mov r0, #0
	add sp, #0x10
	str r0, [r5]
	pop {r3, r4, r5, r6, r7, pc}
_02244AF8:
	add r0, r4, #0
	bl MOD18_02244D04
	cmp r0, #0
	bne _02244B24
	mov r1, #0
	ldr r0, [sp, #0xc]
	mov r2, #2
	add r3, r1, #0
	bl ScrollWindow
	ldr r0, [sp, #0xc]
	bl CopyWindowToVram
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	cmp r0, #8
	blt _02244B24
	mov r0, #0
	str r0, [r5]
	str r0, [r6]
_02244B24:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_02244A70

	thumb_func_start MOD18_02244B28
MOD18_02244B28: ; 0x02244B28
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
	mov r7, #0x64
_02244B32:
	add r0, r7, #0
	mov r1, #4
	bl String_ctor
	add r6, r6, #1
	stmia r4!, {r0}
	cmp r6, #0x20
	blt _02244B32
	add r0, r5, #0
	mov r1, #0
	add r0, #0x8c
	str r1, [r0]
	add r0, r5, #0
	add r0, #0x90
	str r1, [r0]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	add r1, r5, #0
	add r1, #0x80
	str r0, [r1]
	mov r4, #0
	mov r6, #0x50
	mov r7, #4
_02244B64:
	add r0, r6, #0
	add r1, r7, #0
	bl String_ctor
	add r1, r5, #0
	add r1, #0x84
	add r4, r4, #1
	add r5, r5, #4
	str r0, [r1]
	cmp r4, #2
	blt _02244B64
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_02244B28

	thumb_func_start MOD18_02244B7C
MOD18_02244B7C: ; 0x02244B7C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	mov r6, #0
	add r4, r5, #0
_02244B84:
	ldr r0, [r4]
	bl String_dtor
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #0x20
	blt _02244B84
	add r0, r5, #0
	add r0, #0x80
	ldr r0, [r0]
	bl String_dtor
	mov r4, #0
_02244B9E:
	add r0, r5, #0
	add r0, #0x84
	ldr r0, [r0]
	bl String_dtor
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _02244B9E
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_02244B7C

	thumb_func_start MOD18_02244BB4
MOD18_02244BB4: ; 0x02244BB4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	str r1, [sp]
	add r0, r1, #0
	add r1, r5, #0
	add r1, #0x94
	mov r2, #0x50
	bl CopyStringToU16Array
	add r0, r5, #0
	add r0, #0x94
	ldrh r2, [r0]
	mov r4, #0
	ldr r0, _02244C44 ; =0x0000FFFF
	add r1, r4, #0
	cmp r2, r0
	beq _02244BFA
	add r7, r0, #0
	mov r0, #0xe
	add r2, r5, #0
	lsl r0, r0, #0xc
_02244BDE:
	add r3, r2, #0
	add r3, #0x94
	ldrh r3, [r3]
	cmp r3, r0
	bne _02244BEC
	add r4, r4, #1
	add r6, r1, #0
_02244BEC:
	add r2, r2, #2
	add r3, r2, #0
	add r3, #0x94
	ldrh r3, [r3]
	add r1, r1, #1
	cmp r3, r7
	bne _02244BDE
_02244BFA:
	cmp r4, #2
	blt _02244C02
	bl ErrorHandling
_02244C02:
	cmp r4, #0
	bne _02244C14
	add r5, #0x84
	ldr r0, [r5]
	ldr r1, [sp]
	bl StringCopy
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02244C14:
	lsl r0, r6, #1
	add r0, r5, r0
	ldr r1, _02244C44 ; =0x0000FFFF
	add r0, #0x94
	strh r1, [r0]
	add r0, r5, #0
	add r0, #0x84
	add r1, r5, #0
	ldr r0, [r0]
	add r1, #0x94
	bl CopyU16ArrayToString
	add r0, r5, #0
	add r0, #0x88
	add r1, r6, #1
	ldr r0, [r0]
	add r5, #0x94
	lsl r1, r1, #1
	add r1, r5, r1
	bl CopyU16ArrayToString
	mov r0, #2
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02244C44: .word 0x0000FFFF
	thumb_func_end MOD18_02244BB4

	thumb_func_start MOD18_02244C48
MOD18_02244C48: ; 0x02244C48
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl MOD18_02244BB4
	add r6, r0, #0
	add r0, r5, #0
	add r0, #0x8c
	mov r2, #0
	ldr r1, [r0]
	cmp r6, #0
	ble _02244C7C
	add r0, r5, #0
	add r0, #0x90
	ldr r3, [r0]
	add r0, r2, #0
_02244C66:
	add r1, r1, #1
	cmp r1, #0x20
	bne _02244C6E
	add r1, r0, #0
_02244C6E:
	cmp r1, r3
	bne _02244C76
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02244C76:
	add r2, r2, #1
	cmp r2, r6
	blt _02244C66
_02244C7C:
	mov r0, #0
	str r0, [sp]
	cmp r6, #0
	ble _02244CC2
	add r7, r5, #0
	add r4, r5, #0
	add r7, #0x8c
_02244C8A:
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	add r1, r4, #0
	lsl r0, r0, #2
	add r1, #0x84
	ldr r0, [r5, r0]
	ldr r1, [r1]
	bl StringCopy
	ldr r0, [r7]
	add r0, r0, #1
	str r0, [r7]
	add r0, r5, #0
	add r0, #0x8c
	ldr r0, [r0]
	cmp r0, #0x20
	bne _02244CB6
	add r1, r5, #0
	add r1, #0x8c
	mov r0, #0
	str r0, [r1]
_02244CB6:
	ldr r0, [sp]
	add r4, r4, #4
	add r0, r0, #1
	str r0, [sp]
	cmp r0, r6
	blt _02244C8A
_02244CC2:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_02244C48

	thumb_func_start MOD18_02244CC8
MOD18_02244CC8: ; 0x02244CC8
	add r1, r0, #0
	add r2, r0, #0
	add r1, #0x90
	add r2, #0x8c
	ldr r1, [r1]
	ldr r2, [r2]
	cmp r2, r1
	beq _02244CFE
	add r2, r0, #0
	add r2, #0x90
	ldr r2, [r2]
	add r3, r2, #1
	add r2, r0, #0
	add r2, #0x90
	str r3, [r2]
	add r2, r0, #0
	add r2, #0x90
	ldr r2, [r2]
	cmp r2, #0x20
	bne _02244CF8
	add r2, r0, #0
	mov r3, #0
	add r2, #0x90
	str r3, [r2]
_02244CF8:
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bx lr
_02244CFE:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02244CC8

	thumb_func_start MOD18_02244D04
MOD18_02244D04: ; 0x02244D04
	add r1, r0, #0
	add r1, #0x8c
	add r0, #0x90
	ldr r1, [r1]
	ldr r0, [r0]
	cmp r1, r0
	bne _02244D16
	mov r0, #1
	bx lr
_02244D16:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02244D04

	thumb_func_start MOD18_02244D1C
MOD18_02244D1C: ; 0x02244D1C
	mov r0, #0x78
	bx lr
	thumb_func_end MOD18_02244D1C

	thumb_func_start MOD18_02244D20
MOD18_02244D20: ; 0x02244D20
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020312BC
	mov r1, #0
	add r4, #0x18
	add r0, r1, #0
_02244D2E:
	strb r0, [r4, #0xa]
	str r0, [r4, #4]
	add r1, r1, #1
	add r4, #0xc
	cmp r1, #8
	blt _02244D2E
	pop {r4, pc}
	thumb_func_end MOD18_02244D20

	thumb_func_start MOD18_02244D3C
MOD18_02244D3C: ; 0x02244D3C
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02244D3C

	thumb_func_start MOD18_02244D40
MOD18_02244D40: ; 0x02244D40
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	cmp r4, #8
	blt _02244D4E
	bl ErrorHandling
_02244D4E:
	mov r0, #0xc
	add r5, #0x18
	mul r0, r4
	add r0, r5, r0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_02244D40

	thumb_func_start MOD18_02244D58
MOD18_02244D58: ; 0x02244D58
	mov r3, #0
	add r0, #0x18
	add r1, r3, #0
_02244D5E:
	ldr r2, [r0, #4]
	cmp r2, #0
	ble _02244D68
	sub r2, r2, #1
	str r2, [r0, #4]
_02244D68:
	ldr r2, [r0, #4]
	cmp r2, #0
	bne _02244D70
	strb r1, [r0, #0xa]
_02244D70:
	add r3, r3, #1
	add r0, #0xc
	cmp r3, #8
	blt _02244D5E
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02244D58

	thumb_func_start MOD18_02244D7C
MOD18_02244D7C: ; 0x02244D7C
	strb r1, [r0, #0xa]
	lsl r2, r1, #2
	ldr r1, _02244D90 ; =0x02251200
	ldr r1, [r1, r2]
	str r1, [r0, #4]
	ldr r1, _02244D94 ; =0x0225121C
	ldr r1, [r1, r2]
	str r1, [r0]
	bx lr
	nop
_02244D90: .word MOD18_02251200
_02244D94: .word MOD18_0225121C
	thumb_func_end MOD18_02244D7C

	thumb_func_start MOD18_02244D98
MOD18_02244D98: ; 0x02244D98
	ldr r3, _02244D9C ; =MOD18_02244D7C
	bx r3
	.align 2, 0
_02244D9C: .word MOD18_02244D7C
	thumb_func_end MOD18_02244D98

	thumb_func_start MOD18_02244DA0
MOD18_02244DA0: ; 0x02244DA0
	ldrb r0, [r0, #0xa]
	cmp r0, #0
	bne _02244DAA
	mov r0, #1
	bx lr
_02244DAA:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02244DA0

	thumb_func_start MOD18_02244DB0
MOD18_02244DB0: ; 0x02244DB0
	ldrb r0, [r0, #0xa]
	cmp r0, #2
	bne _02244DBA
	mov r0, #0
	bx lr
_02244DBA:
	cmp r0, #5
	bne _02244DC2
	mov r0, #0
	bx lr
_02244DC2:
	cmp r0, #3
	bne _02244DCA
	mov r0, #1
	bx lr
_02244DCA:
	cmp r0, #1
	bne _02244DD2
	mov r0, #1
	bx lr
_02244DD2:
	cmp r0, #4
	bne _02244DDA
	mov r0, #1
	bx lr
_02244DDA:
	cmp r0, #0
	bne _02244DE2
	mov r0, #1
	bx lr
_02244DE2:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD18_02244DB0

	thumb_func_start MOD18_02244DE8
MOD18_02244DE8: ; 0x02244DE8
	push {r4, r5}
	asr r2, r0, #4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	asr r0, r1, #4
	lsr r0, r0, #0x1b
	add r0, r1, r0
	asr r3, r0, #5
	ldr r4, _02244E1C ; =0x02251238
	ldr r5, _02244E20 ; =0x0225124C
	asr r2, r2, #5
	mov r0, #0
_02244E00:
	ldrb r1, [r4]
	cmp r2, r1
	bne _02244E0C
	ldrb r1, [r5]
	cmp r3, r1
	beq _02244E18
_02244E0C:
	add r0, r0, #1
	add r4, r4, #1
	add r5, r5, #1
	cmp r0, #0x11
	blt _02244E00
	mov r0, #0x10
_02244E18:
	pop {r4, r5}
	bx lr
	.align 2, 0
_02244E1C: .word MOD18_02251238
_02244E20: .word MOD18_0225124C
	thumb_func_end MOD18_02244DE8

	thumb_func_start MOD18_02244E24
MOD18_02244E24: ; 0x02244E24
	push {r4, r5}
	sub sp, #8
	ldr r3, _02244E64 ; =0x022504D0
	add r2, sp, #0
	ldrh r4, [r3, #0x1c]
	strh r4, [r2]
	ldrh r4, [r3, #0x1e]
	ldrh r3, [r3, #0x20]
	strh r4, [r2, #2]
	strh r3, [r2, #4]
	ldrh r4, [r2]
	ldrh r5, [r2, #2]
	mov r3, #0
_02244E3E:
	add r2, r4, #0
	add r2, #0x20
	cmp r0, r2
	bne _02244E52
	cmp r1, r5
	bne _02244E52
	add sp, #8
	mov r0, #1
	pop {r4, r5}
	bx lr
_02244E52:
	add r3, r3, #1
	add r4, #0x20
	cmp r3, #8
	blt _02244E3E
	mov r0, #0
	add sp, #8
	pop {r4, r5}
	bx lr
	nop
_02244E64: .word MOD18_022504D0
	thumb_func_end MOD18_02244E24

	thumb_func_start MOD18_02244E68
MOD18_02244E68: ; 0x02244E68
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, _02244EB0 ; =0x022504D0
	add r5, r0, #0
	ldrh r2, [r1, #0x22]
	add r0, sp, #0
	strh r2, [r0]
	ldrh r2, [r1, #0x24]
	ldrh r1, [r1, #0x26]
	strh r2, [r0, #2]
	strh r1, [r0, #4]
	bl FUN_0202EDD8
	cmp r0, #0
	beq _02244E96
	add r0, sp, #0
	ldrh r1, [r0]
	add sp, #8
	strh r1, [r4]
	ldrh r0, [r0, #2]
	strh r0, [r4, #2]
	pop {r3, r4, r5, pc}
_02244E96:
	cmp r5, #0x10
	bne _02244E9C
	mov r5, #0
_02244E9C:
	add r0, sp, #0
	ldrh r2, [r0]
	lsl r1, r5, #5
	add r1, r2, r1
	add r1, #0x20
	strh r1, [r4]
	ldrh r0, [r0, #2]
	strh r0, [r4, #2]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02244EB0: .word MOD18_022504D0
	thumb_func_end MOD18_02244E68

	thumb_func_start MOD18_02244EB4
MOD18_02244EB4: ; 0x02244EB4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031280
	cmp r0, #0
	beq _02244EC4
	mov r5, #0x10
_02244EC4:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02244E68
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_02244EB4

	thumb_func_start MOD18_02244ED0
MOD18_02244ED0: ; 0x02244ED0
	push {r3, r4, r5, r6, r7, lr}
	add r4, r0, #0
	ldr r0, _02245000 ; =0x022513EC
	str r1, [sp]
	ldr r0, [r0]
	cmp r0, #0
	beq _02244EE0
	b _02244FFE
_02244EE0:
	bl FUN_0202595C
	cmp r0, #0x94
	beq _02244EEC
	bl ErrorHandling
_02244EEC:
	ldr r0, _02245000 ; =0x022513EC
	ldr r2, _02245004 ; =0x000013E8
	str r4, [r0]
	add r0, r4, #0
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _02245000 ; =0x022513EC
	ldr r1, [sp]
	ldr r2, [r0]
	mov r7, #0xff
	str r1, [r2]
	mov r1, #0
	add r2, r1, #0
	add r3, r1, #0
_02244F0A:
	ldr r4, [r0]
	ldr r5, _02245008 ; =0x00001284
	add r6, r4, r2
	ldr r4, _0224500C ; =0x00000FFF
	strh r4, [r6, r5]
	ldr r4, [r0]
	add r5, r5, #2
	add r6, r4, r2
	ldr r4, _0224500C ; =0x00000FFF
	strh r4, [r6, r5]
	ldr r4, [r0]
	ldr r5, _02245010 ; =0x000012B4
	add r6, r4, r2
	ldr r4, _0224500C ; =0x00000FFF
	strh r4, [r6, r5]
	ldr r4, [r0]
	add r5, r5, #2
	add r6, r4, r2
	ldr r4, _0224500C ; =0x00000FFF
	add r2, r2, #6
	strh r4, [r6, r5]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _02245014 ; =0x0000136B
	strb r7, [r5, r4]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _02245018 ; =0x00001373
	strb r7, [r5, r4]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _0224501C ; =0x00001363
	strb r7, [r5, r4]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _02245020 ; =0x0000137B
	strb r7, [r5, r4]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _02245024 ; =0x0000134B
	strb r7, [r5, r4]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _02245028 ; =0x00001353
	strb r7, [r5, r4]
	ldr r4, [r0]
	add r5, r4, r1
	ldr r4, _0224502C ; =0x0000135B
	add r1, r1, #1
	strb r7, [r5, r4]
	ldr r4, [r0]
	ldr r5, _02245030 ; =0x000013AC
	add r6, r4, r3
	mov r4, #0x48
	strh r4, [r6, r5]
	ldr r4, [r0]
	ldr r5, _02245034 ; =0x000001B5
	add r6, r4, r3
	ldr r4, _02245038 ; =0x000013BC
	strh r5, [r6, r4]
	ldr r4, [r0]
	mov r5, #1
	add r6, r4, r3
	ldr r4, _0224503C ; =0x000013CC
	add r3, r3, #2
	strh r5, [r6, r4]
	cmp r1, #8
	blt _02244F0A
	mov r5, #0
	ldr r6, _02245000 ; =0x022513EC
	add r4, r5, #0
	mov r7, #0xff
_02244F9A:
	ldr r0, [r6]
	add r0, #0xa
	add r0, r0, r4
	bl FUN_020266D4
	ldr r0, [r6]
	add r4, #0x96
	add r1, r0, r5
	ldr r0, _02245040 ; =0x000012E5
	strb r7, [r1, r0]
	ldr r0, [r6]
	add r1, r0, r5
	ldr r0, _02245044 ; =0x0000133A
	add r5, r5, #1
	strb r7, [r1, r0]
	cmp r5, #0x11
	blt _02244F9A
	ldr r0, _02245000 ; =0x022513EC
	mov r2, #0x22
	ldr r1, [r0]
	ldr r0, _02245048 ; =0x00000A04
	lsl r2, r2, #6
	add r0, r1, r0
	add r1, r7, #0
	bl MI_CpuFill8
	ldr r0, [sp]
	bl MOD18_02245054
	ldr r2, _02245000 ; =0x022513EC
	ldr r0, _0224504C ; =0x000013DC
	ldr r1, [r2]
	mov r3, #0x48
	strh r3, [r1, r0]
	add r1, r0, #2
	ldr r4, _02245034 ; =0x000001B5
	ldr r3, [r2]
	add r0, r0, #4
	strh r4, [r3, r1]
	ldr r1, [r2]
	mov r3, #1
	strb r3, [r1, r0]
	ldr r0, _02245050 ; =MOD18_02246338
	mov r1, #0
	mov r2, #0x64
	bl FUN_0200CA44
	ldr r1, _02245000 ; =0x022513EC
	ldr r1, [r1]
	str r0, [r1, #4]
_02244FFE:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245000: .word MOD18_022513EC
_02245004: .word 0x000013E8
_02245008: .word 0x00001284
_0224500C: .word 0x00000FFF
_02245010: .word 0x000012B4
_02245014: .word 0x0000136B
_02245018: .word 0x00001373
_0224501C: .word 0x00001363
_02245020: .word 0x0000137B
_02245024: .word 0x0000134B
_02245028: .word 0x00001353
_0224502C: .word 0x0000135B
_02245030: .word 0x000013AC
_02245034: .word 0x000001B5
_02245038: .word 0x000013BC
_0224503C: .word 0x000013CC
_02245040: .word 0x000012E5
_02245044: .word 0x0000133A
_02245048: .word 0x00000A04
_0224504C: .word 0x000013DC
_02245050: .word MOD18_02246338
	thumb_func_end MOD18_02244ED0

	thumb_func_start MOD18_02245054
MOD18_02245054: ; 0x02245054
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CA8
	add r4, r0, #0
	bl FUN_02026CC0
	add r6, r0, #0
	ldr r0, [r5, #0xc]
	bl FUN_02029FC8
	bl FUN_0202A1B8
	add r1, r0, #0
	add r0, r6, #0
	bl FUN_020268E8
	ldr r1, _022450B8 ; =0x022513EC
	add r0, r4, #0
	ldr r2, [r1]
	ldr r1, _022450BC ; =0x0000096A
	add r1, r2, r1
	mov r2, #0x94
	bl MI_CpuCopy8
	ldr r1, _022450B8 ; =0x022513EC
	add r0, r4, #0
	ldr r2, [r1]
	ldr r1, _022450C0 ; =0x00001204
	add r1, r2, r1
	bl MOD18_02245128
	ldr r1, _022450B8 ; =0x022513EC
	add r0, r4, #0
	ldr r1, [r1]
	mov r2, #0x94
	add r1, #0xa
	bl MI_CpuCopy8
	ldr r1, _022450B8 ; =0x022513EC
	add r0, r4, #0
	ldr r2, [r1]
	ldr r1, _022450C4 ; =0x00000A04
	add r1, r2, r1
	bl MOD18_02245128
	pop {r4, r5, r6, pc}
	nop
_022450B8: .word MOD18_022513EC
_022450BC: .word 0x0000096A
_022450C0: .word 0x00001204
_022450C4: .word 0x00000A04
	thumb_func_end MOD18_02245054

	thumb_func_start MOD18_022450C8
MOD18_022450C8: ; 0x022450C8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r6, r0, #0
	mov r0, #0
	mov ip, r0
	mov lr, r0
	add r0, r1, #0
	lsl r0, r0, #2
	str r1, [sp]
	str r2, [sp, #4]
	add r3, r3, r0
	mov r7, #1
_022450E0:
	ldr r1, [sp]
	mov r0, ip
	add r0, r1, r0
	cmp r0, #0x20
	bge _02245112
	ldr r1, [sp, #4]
	mov r0, lr
	mov r2, #0
	add r4, r1, r0
_022450F2:
	ldrb r0, [r4]
	cmp r0, #0
	beq _0224510A
	add r1, r6, r2
	cmp r1, #0x20
	bge _0224510A
	add r0, r7, #0
	lsl r0, r1
	ldr r5, [r3]
	mvn r0, r0
	and r0, r5
	str r0, [r3]
_0224510A:
	add r2, r2, #1
	add r4, r4, #1
	cmp r2, #3
	blt _022450F2
_02245112:
	mov r0, lr
	add r0, r0, #3
	mov lr, r0
	mov r0, ip
	add r0, r0, #1
	add r3, r3, #4
	mov ip, r0
	cmp r0, #3
	blt _022450E0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_022450C8

	thumb_func_start MOD18_02245128
MOD18_02245128: ; 0x02245128
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r2, sp, #0x10
	str r1, [sp]
	ldr r3, _022451B4 ; =0x02250508
	add r5, r0, #0
	add r2, #1
	mov r1, #9
_02245138:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _02245138
	ldr r3, _022451B8 ; =0x02250511
	add r2, sp, #8
	mov r1, #9
_0224514A:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	bne _0224514A
	ldr r0, [sp]
	mov r1, #0xff
	mov r2, #0x80
	bl MI_CpuFill8
	mov r4, #0
_02245162:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_020267C4
	str r0, [sp, #4]
	cmp r0, #0
	beq _022451A8
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026810
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026840
	add r6, r0, #0
	cmp r4, #0
	bne _0224518E
	add r2, sp, #0x10
	add r2, #1
	b _0224519E
_0224518E:
	cmp r4, #0x10
	bge _0224519C
	ldr r0, [sp, #4]
	bl FUN_0204CAA0
	add r2, r0, #0
	b _0224519E
_0224519C:
	add r2, sp, #8
_0224519E:
	ldr r3, [sp]
	add r0, r7, #0
	add r1, r6, #0
	bl MOD18_022450C8
_022451A8:
	add r4, r4, #1
	cmp r4, #0x20
	blt _02245162
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_022451B4: .word MOD18_02250508
_022451B8: .word MOD18_02250511
	thumb_func_end MOD18_02245128

	thumb_func_start MOD18_022451BC
MOD18_022451BC: ; 0x022451BC
	push {r3, lr}
	bl MOD18_0224646C
	ldr r0, _022451E4 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _022451D8
	bl FUN_0200CAB4
	ldr r0, _022451E4 ; =0x022513EC
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #4]
_022451D8:
	ldr r0, _022451E4 ; =0x022513EC
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _022451E8 ; =0x000013E4
	strb r2, [r1, r0]
	pop {r3, pc}
	.align 2, 0
_022451E4: .word MOD18_022513EC
_022451E8: .word 0x000013E4
	thumb_func_end MOD18_022451BC

	thumb_func_start MOD18_022451EC
MOD18_022451EC: ; 0x022451EC
	push {r3, r4, r5, r6, r7, lr}
	ldr r1, _0224525C ; =0x022513EC
	ldr r0, _02245260 ; =0x000013E4
	ldr r2, [r1]
	mov r4, #0
	strb r4, [r2, r0]
	ldr r1, [r1]
	add r0, r0, #2
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _0224523E
_02245202:
	add r0, r4, #0
	bl MOD18_02246430
	add r4, r4, #1
	cmp r4, #8
	blt _02245202
	mov r5, #0
	ldr r6, _0224525C ; =0x022513EC
	ldr r7, _02245264 ; =0x00000FFF
	add r4, r5, #0
_02245216:
	ldr r1, [r6]
	ldr r0, _02245268 ; =0x00001284
	add r0, r1, r0
	ldrh r3, [r0, r4]
	add r2, r0, r4
	cmp r3, r7
	beq _02245236
	ldrh r1, [r2, #2]
	ldr r0, _02245264 ; =0x00000FFF
	cmp r1, r0
	beq _02245236
	ldrb r2, [r2, #4]
	add r0, r3, #0
	add r3, r5, #0
	bl MOD18_0224630C
_02245236:
	add r5, r5, #1
	add r4, r4, #6
	cmp r5, #8
	blt _02245216
_0224523E:
	ldr r0, _0224525C ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _02245258
	ldr r0, _0224526C ; =MOD18_02246338
	mov r1, #0
	mov r2, #0x64
	bl FUN_0200CA44
	ldr r1, _0224525C ; =0x022513EC
	ldr r1, [r1]
	str r0, [r1, #4]
_02245258:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224525C: .word MOD18_022513EC
_02245260: .word 0x000013E4
_02245264: .word 0x00000FFF
_02245268: .word 0x00001284
_0224526C: .word MOD18_02246338
	thumb_func_end MOD18_022451EC

	thumb_func_start MOD18_02245270
MOD18_02245270: ; 0x02245270
	push {r3, lr}
	ldr r0, _022452A0 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02245288
	bl FUN_0200CAB4
	ldr r0, _022452A0 ; =0x022513EC
	mov r1, #0
	ldr r0, [r0]
	str r1, [r0, #4]
_02245288:
	bl MOD18_0224646C
	ldr r0, _022452A0 ; =0x022513EC
	ldr r0, [r0]
	cmp r0, #0
	beq _02245298
	bl FreeToHeap
_02245298:
	ldr r0, _022452A0 ; =0x022513EC
	mov r1, #0
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_022452A0: .word MOD18_022513EC
	thumb_func_end MOD18_02245270

	thumb_func_start MOD18_022452A4
MOD18_022452A4: ; 0x022452A4
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r7, _02245308 ; =0x00000FFF
	ldr r6, _0224530C ; =0x022513EC
	str r4, [sp]
	add r5, r4, #0
_022452B0:
	ldr r0, [r6]
	add r0, #0xa
	add r0, r0, r4
	bl FUN_02026714
	ldr r0, [r6]
	add r4, #0x96
	add r1, r0, r5
	ldr r0, _02245310 ; =0x00001284
	strh r7, [r1, r0]
	ldr r0, [r6]
	add r1, r0, r5
	ldr r0, _02245314 ; =0x00001286
	strh r7, [r1, r0]
	ldr r0, [r6]
	add r1, r0, r5
	ldr r0, _02245318 ; =0x000012B4
	strh r7, [r1, r0]
	ldr r0, [r6]
	add r1, r0, r5
	ldr r0, _0224531C ; =0x000012B6
	add r5, r5, #6
	strh r7, [r1, r0]
	ldr r0, [sp]
	add r0, r0, #1
	str r0, [sp]
	cmp r0, #8
	blt _022452B0
	ldr r0, _0224530C ; =0x022513EC
	mov r2, #0x22
	ldr r1, [r0]
	ldr r0, _02245320 ; =0x00000A04
	lsl r2, r2, #6
	add r0, r1, r0
	mov r1, #0xff
	bl MI_CpuFill8
	ldr r0, _0224530C ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD18_02245054
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02245308: .word 0x00000FFF
_0224530C: .word MOD18_022513EC
_02245310: .word 0x00001284
_02245314: .word 0x00001286
_02245318: .word 0x000012B4
_0224531C: .word 0x000012B6
_02245320: .word 0x00000A04
	thumb_func_end MOD18_022452A4

	thumb_func_start MOD18_02245324
MOD18_02245324: ; 0x02245324
	push {r4, r5, r6, lr}
	mov r4, #0
	ldr r6, _0224534C ; =0x022513EC
	add r5, r4, #0
_0224532C:
	ldr r0, [r6]
	add r0, #0xa
	add r0, r0, r5
	bl FUN_020266D4
	add r4, r4, #1
	add r5, #0x96
	cmp r4, #0x11
	blt _0224532C
	ldr r0, _0224534C ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	bl MOD18_02245054
	pop {r4, r5, r6, pc}
	nop
_0224534C: .word MOD18_022513EC
	thumb_func_end MOD18_02245324

	thumb_func_start MOD18_02245350
MOD18_02245350: ; 0x02245350
	ldr r0, _02245354 ; =0x000013E8
	bx lr
	.align 2, 0
_02245354: .word 0x000013E8
	thumb_func_end MOD18_02245350

	thumb_func_start MOD18_02245358
MOD18_02245358: ; 0x02245358
	push {r4, r5}
	ldr r2, _0224539C ; =0x022513EC
	ldr r1, [r2]
	cmp r1, #0
	beq _02245396
	add r4, r1, r0
	ldr r1, _022453A0 ; =0x00001363
	mov r3, #0xff
	strb r3, [r4, r1]
	ldr r4, [r2]
	add r5, r4, r0
	add r4, r1, #0
	add r4, #8
	strb r3, [r5, r4]
	ldr r4, [r2]
	add r5, r4, r0
	add r4, r1, #0
	add r4, #0x10
	strb r3, [r5, r4]
	mov r3, #6
	mul r3, r0
	ldr r4, [r2]
	ldr r0, _022453A4 ; =0x00000FFF
	add r5, r4, r3
	add r4, r1, #0
	sub r4, #0xaf
	strh r0, [r5, r4]
	ldr r2, [r2]
	sub r1, #0xad
	add r2, r2, r3
	strh r0, [r2, r1]
_02245396:
	pop {r4, r5}
	bx lr
	nop
_0224539C: .word MOD18_022513EC
_022453A0: .word 0x00001363
_022453A4: .word 0x00000FFF
	thumb_func_end MOD18_02245358

	thumb_func_start MOD18_022453A8
MOD18_022453A8: ; 0x022453A8
	push {r3, r4, r5, lr}
	ldr r1, _022453D4 ; =0x022513EC
	add r4, r0, #0
	ldr r1, [r1]
	cmp r1, #0
	beq _022453D2
	bl MOD18_02246430
	ldr r1, _022453D4 ; =0x022513EC
	mov r0, #6
	add r5, r4, #0
	mul r5, r0
	ldr r0, [r1]
	ldr r3, _022453D8 ; =0x00000FFF
	add r2, r0, r5
	ldr r0, _022453DC ; =0x00001284
	strh r3, [r2, r0]
	ldr r1, [r1]
	add r0, r0, #2
	add r1, r1, r5
	strh r3, [r1, r0]
_022453D2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022453D4: .word MOD18_022513EC
_022453D8: .word 0x00000FFF
_022453DC: .word 0x00001284
	thumb_func_end MOD18_022453A8

	thumb_func_start MOD18_022453E0
MOD18_022453E0: ; 0x022453E0
	ldr r3, _022453E4 ; =FUN_0204F7FC
	bx r3
	.align 2, 0
_022453E4: .word FUN_0204F7FC
	thumb_func_end MOD18_022453E0

	thumb_func_start MOD18_022453E8
MOD18_022453E8: ; 0x022453E8
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r7, r0, #0
	str r1, [sp]
	add r5, r6, #0
_022453F2:
	ldr r0, _02245434 ; =0x022513EC
	ldr r4, [r0]
	add r4, #0xa
	add r0, r4, r5
	bl FUN_02026CA0
	cmp r0, #0
	beq _02245426
	add r0, r6, #0
	bl FUN_0204E34C
	cmp r0, #0
	beq _02245426
	add r0, r4, r5
	bl FUN_02026C88
	cmp r7, r0
	bne _02245426
	add r0, r4, r5
	bl FUN_02026C90
	ldr r1, [sp]
	cmp r1, r0
	bne _02245426
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
_02245426:
	add r6, r6, #1
	add r5, #0x96
	cmp r6, #8
	blt _022453F2
	mov r0, #0xff
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02245434: .word MOD18_022513EC
	thumb_func_end MOD18_022453E8

	thumb_func_start MOD18_02245438
MOD18_02245438: ; 0x02245438
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r2, #0
	ldrb r4, [r5, #4]
	bl FUN_02031190
	cmp r4, r0
	bne _02245480
	ldr r0, _02245484 ; =0x022513EC
	ldr r1, _02245488 ; =0x000013E4
	ldr r0, [r0]
	ldrb r1, [r0, r1]
	cmp r1, #0
	bne _02245480
	ldrb r1, [r5, #7]
	cmp r1, #0
	str r4, [sp]
	beq _02245470
	ldrb r1, [r5, #5]
	mov r3, #0
	str r1, [sp, #4]
	ldrh r1, [r5]
	ldrh r2, [r5, #2]
	ldr r0, [r0]
	bl MOD18_02245E1C
	add sp, #8
	pop {r3, r4, r5, pc}
_02245470:
	ldrb r1, [r5, #5]
	str r1, [sp, #4]
	ldrh r1, [r5]
	ldrh r2, [r5, #2]
	ldrb r3, [r5, #6]
	ldr r0, [r0]
	bl MOD18_022459E8
_02245480:
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02245484: .word MOD18_022513EC
_02245488: .word 0x000013E4
	thumb_func_end MOD18_02245438

	thumb_func_start MOD18_0224548C
MOD18_0224548C: ; 0x0224548C
	push {r4, lr}
	add r4, r2, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _022454B0
	bl FUN_0204F7E4
	bl MOD18_0223D638
	ldr r3, _022454B4 ; =MOD18_022453E0
	mov r1, #0x58
	mov r2, #1
	bl MOD18_0224DCB8
	bl MOD18_022479A0
_022454B0:
	pop {r4, pc}
	nop
_022454B4: .word MOD18_022453E0
	thumb_func_end MOD18_0224548C

	thumb_func_start MOD18_022454B8
MOD18_022454B8: ; 0x022454B8
	mov r0, #8
	bx lr
	thumb_func_end MOD18_022454B8

	thumb_func_start MOD18_022454BC
MOD18_022454BC: ; 0x022454BC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, sp, #0
	add r4, r2, #0
	strb r5, [r0]
	bl FUN_02031190
	cmp r0, #0
	beq _022454D4
	bl ErrorHandling
	pop {r3, r4, r5, pc}
_022454D4:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _0224550C
	ldrb r0, [r4, #2]
	cmp r0, #0
	ldrb r0, [r4]
	beq _02245502
	add r1, r5, #0
	bl MOD18_02245528
	cmp r0, #0
	bne _02245518
	ldr r0, _0224551C ; =0x022513EC
	mov r2, #0xff
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _02245520 ; =0x0000136B
	strb r2, [r1, r0]
	mov r0, #0x3d
	add r1, sp, #0
	bl FUN_02030C4C
	pop {r3, r4, r5, pc}
_02245502:
	add r1, r5, #0
	mov r2, #0
	bl MOD18_022455D0
	pop {r3, r4, r5, pc}
_0224550C:
	ldr r0, _0224551C ; =0x022513EC
	mov r2, #0xff
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _02245520 ; =0x0000136B
	strb r2, [r1, r0]
_02245518:
	pop {r3, r4, r5, pc}
	nop
_0224551C: .word MOD18_022513EC
_02245520: .word 0x0000136B
	thumb_func_end MOD18_022454BC

	thumb_func_start MOD18_02245524
MOD18_02245524: ; 0x02245524
	mov r0, #3
	bx lr
	thumb_func_end MOD18_02245524

	thumb_func_start MOD18_02245528
MOD18_02245528: ; 0x02245528
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	ldr r0, _022455C4 ; =0x022513EC
	add r6, r1, #0
	ldr r1, [r0]
	mov r0, #0x96
	add r1, #8
	mul r0, r5
	add r0, r1, r0
	str r0, [sp]
	add r0, r0, #2
	bl FUN_02026CA0
	cmp r0, #0
	bne _0224554E
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0224554E:
	mov r0, #0x36
	bl FUN_02031354
	cmp r0, #0
	beq _0224555E
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0224555E:
	ldr r7, _022455C4 ; =0x022513EC
	mov r4, #0
_02245562:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	beq _02245580
	ldr r0, [r7]
	add r1, r0, r4
	ldr r0, _022455C8 ; =0x00001373
	ldrb r0, [r1, r0]
	cmp r5, r0
	bne _02245580
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02245580:
	add r4, r4, #1
	cmp r4, #8
	blt _02245562
	add r0, r5, #0
	add r1, sp, #4
	bl MOD18_02244EB4
	ldr r0, [sp]
	strb r6, [r0, #1]
	add r0, r5, #0
	bl MOD18_02245FC0
	ldr r2, _022455C4 ; =0x022513EC
	lsl r0, r5, #0x18
	ldr r1, [r2]
	lsr r0, r0, #0x18
	add r3, r1, r6
	ldr r1, _022455CC ; =0x0000136B
	strb r0, [r3, r1]
	ldr r2, [r2]
	add r1, #8
	add r2, r2, r6
	strb r0, [r2, r1]
	add r2, sp, #4
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	add r0, r6, #0
	mov r3, #0
	bl FUN_0204E794
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_022455C4: .word MOD18_022513EC
_022455C8: .word 0x00001373
_022455CC: .word 0x0000136B
	thumb_func_end MOD18_02245528

	thumb_func_start MOD18_022455D0
MOD18_022455D0: ; 0x022455D0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r1, sp, #4
	add r4, r0, #0
	str r2, [sp]
	bl MOD18_02244E68
	ldr r0, _0224565C ; =0x022513EC
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _02245660 ; =0x0000136B
	strb r4, [r1, r0]
	bl FUN_02031280
	cmp r0, #0
	beq _02245604
	ldr r0, _0224565C ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _02245664 ; =0x000013DC
	add r1, r0, #2
	ldrh r4, [r2, r0]
	add r0, r0, #4
	ldrh r7, [r2, r1]
	ldrb r6, [r2, r0]
	b _0224561A
_02245604:
	ldr r0, _0224565C ; =0x022513EC
	lsl r1, r5, #1
	ldr r0, [r0]
	add r2, r0, r1
	ldr r1, _02245668 ; =0x000013AC
	add r0, r1, #0
	ldrh r4, [r2, r1]
	add r0, #0x10
	add r1, #0x20
	ldrh r7, [r2, r0]
	ldrh r6, [r2, r1]
_0224561A:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	add r3, r6, #0
	bl FUN_0204E794
	add r0, r6, #0
	bl FUN_02059BF4
	add r4, r4, r0
	add r0, r6, #0
	bl FUN_02059C00
	add r1, sp, #4
	add r0, r7, r0
	strh r4, [r1, #6]
	strh r0, [r1, #8]
	strb r5, [r1, #0xa]
	ldr r0, [sp]
	strb r6, [r1, #0xb]
	strb r0, [r1, #0xc]
	add r1, sp, #8
	mov r0, #0x39
	add r1, #2
	bl FUN_02030C4C
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_0224565C: .word MOD18_022513EC
_02245660: .word 0x0000136B
_02245664: .word 0x000013DC
_02245668: .word 0x000013AC
	thumb_func_end MOD18_022455D0

	thumb_func_start MOD18_0224566C
MOD18_0224566C: ; 0x0224566C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r6, r0, #0
	ldr r0, _022457C8 ; =0x022513EC
	add r7, r1, #0
	ldr r0, [r0]
	str r2, [sp]
	cmp r0, #0
	bne _02245684
	add sp, #0x1c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02245684:
	cmp r6, #0
	beq _0224569A
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	bne _0224569A
	add sp, #0x1c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_0224569A:
	add r0, r6, #0
	bl FUN_0204D830
	cmp r0, #0
	beq _022456AA
	add sp, #0x1c
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_022456AA:
	ldr r0, _022457C8 ; =0x022513EC
	ldr r0, [r0]
	add r1, r0, r6
	ldr r0, _022457CC ; =0x0000136B
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _022456BE
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022456BE:
	ldr r1, [sp]
	add r0, r7, #0
	bl MOD18_022453E8
	cmp r0, #0xff
	beq _02245702
	ldr r1, _022457C8 ; =0x022513EC
	lsl r0, r0, #0x18
	ldr r1, [r1]
	lsr r0, r0, #0x18
	add r2, r1, r6
	ldr r1, _022457CC ; =0x0000136B
	strb r0, [r2, r1]
	mov r1, #1
	add r2, sp, #4
	strb r1, [r2, #7]
	ldr r1, [sp]
	strh r7, [r2]
	strh r1, [r2, #2]
	mov r1, #0
	strb r1, [r2, #6]
	strb r6, [r2, #4]
	strb r0, [r2, #5]
	mov r0, #0x3a
	add r1, sp, #4
	bl FUN_02030C4C
	add r0, r6, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02245702:
	mov r5, #0
	add r4, r5, #0
_02245706:
	ldr r0, _022457C8 ; =0x022513EC
	ldr r0, [r0]
	add r0, #0xa
	add r0, r0, r4
	bl FUN_02026CA0
	cmp r0, #0
	beq _02245766
	add r0, r5, #0
	add r1, sp, #0xc
	bl MOD18_02244E68
	add r0, sp, #4
	ldrh r0, [r0, #8]
	cmp r7, r0
	bne _02245766
	add r0, sp, #4
	ldrh r1, [r0, #0xa]
	ldr r0, [sp]
	cmp r0, r1
	bne _02245766
	ldr r1, _022457C8 ; =0x022513EC
	lsl r0, r5, #0x18
	ldr r1, [r1]
	lsr r0, r0, #0x18
	add r2, r1, r6
	ldr r1, _022457CC ; =0x0000136B
	mov r3, #0
	strb r0, [r2, r1]
	add r2, sp, #4
	strb r3, [r2, #7]
	ldr r1, [sp]
	strh r7, [r2]
	strh r1, [r2, #2]
	strb r3, [r2, #6]
	strb r6, [r2, #4]
	strb r0, [r2, #5]
	mov r0, #0x3a
	add r1, sp, #4
	bl FUN_02030C4C
	add r0, r6, #0
	mov r1, #0
	bl FUN_0204EAD8
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02245766:
	add r5, r5, #1
	add r4, #0x96
	cmp r5, #8
	ble _02245706
	ldr r1, [sp]
	add r0, r7, #0
	bl MOD18_02244E24
	cmp r0, #0
	beq _022457C2
	ldr r0, _022457C8 ; =0x022513EC
	lsl r2, r6, #1
	ldr r1, [r0]
	ldr r4, _022457D0 ; =0x000013AC
	add r0, r1, r2
	ldrh r2, [r0, r4]
	add r3, sp, #4
	strh r2, [r3, #0xe]
	add r2, r4, #0
	add r2, #0x10
	ldrh r2, [r0, r2]
	strh r2, [r3, #0x10]
	add r2, r4, #0
	strb r6, [r3, #0x12]
	add r2, #0x20
	ldrh r0, [r0, r2]
	mov r2, #0
	sub r4, #0x41
	strb r0, [r3, #0x13]
	strb r2, [r3, #0x14]
	add r0, r1, r6
	strb r2, [r0, r4]
	ldrh r1, [r3, #0xe]
	ldrh r2, [r3, #0x10]
	ldrb r3, [r3, #0x13]
	add r0, r6, #0
	bl FUN_0204E794
	add r1, sp, #0x10
	mov r0, #0x39
	add r1, #2
	bl FUN_02030C4C
	add sp, #0x1c
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022457C2:
	mov r0, #0
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022457C8: .word MOD18_022513EC
_022457CC: .word 0x0000136B
_022457D0: .word 0x000013AC
	thumb_func_end MOD18_0224566C

	thumb_func_start MOD18_022457D4
MOD18_022457D4: ; 0x022457D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022457E6
	mov r1, #4
	bl FUN_020021EC
_022457E6:
	add r0, r5, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	bl MOD18_0223E6A0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_022457D4

	thumb_func_start MOD18_022457F8
MOD18_022457F8: ; 0x022457F8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0224580A
	mov r1, #4
	bl FUN_020021EC
_0224580A:
	add r0, r4, #0
	mov r2, #0
	add r1, sp, #0
	strb r2, [r1, #1]
	add r0, #0x2c
	ldrb r0, [r0]
	strb r0, [r1]
	strb r2, [r1, #2]
	mov r0, #0x3b
	add r1, sp, #0
	bl FUN_020311D0
	add r0, r5, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	bl MOD18_0223E6A0
	bl MOD18_022479A0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_022457F8

	thumb_func_start MOD18_02245838
MOD18_02245838: ; 0x02245838
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	mov r5, #0
	ldr r6, [r4]
	cmp r0, #7
	bhi _02245896
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02245856: ; jump table
	.short _02245866 - _02245856 - 2 ; case 0
	.short _0224588A - _02245856 - 2 ; case 1
	.short _022458B0 - _02245856 - 2 ; case 2
	.short _022458D4 - _02245856 - 2 ; case 3
	.short _022458F8 - _02245856 - 2 ; case 4
	.short _0224592A - _02245856 - 2 ; case 5
	.short _0224594E - _02245856 - 2 ; case 6
	.short _02245972 - _02245856 - 2 ; case 7
_02245866:
	bl FUN_0202EDD8
	cmp r0, #0
	beq _02245874
	mov r6, #0x2f
	mov r0, #3
	b _02245878
_02245874:
	mov r6, #0x32
	mov r0, #1
_02245878:
	str r0, [r4, #0xc]
	bl MOD18_0223D638
	mov r2, #0
	add r1, r6, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _022459A0
_0224588A:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	beq _02245898
_02245896:
	b _022459A0
_02245898:
	mov r0, #4
	str r0, [sp]
	ldr r0, [r6, #8]
	ldr r1, _022459E0 ; =0x022504F8
	ldr r2, _022459E4 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #4]
	mov r0, #2
	str r0, [r4, #0xc]
	b _022459A0
_022458B0:
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _022458C6
	add r0, r5, #0
	str r0, [r4, #4]
	mov r0, #7
	str r0, [r4, #0xc]
	b _022459A0
_022458C6:
	sub r1, r5, #1
	cmp r0, r1
	beq _022459A0
	add r0, r5, #0
	str r0, [r4, #4]
	mov r5, #1
	b _022459A0
_022458D4:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022459A0
	mov r0, #4
	str r0, [sp]
	ldr r0, [r6, #8]
	ldr r1, _022459E0 ; =0x022504F8
	ldr r2, _022459E4 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #4]
	mov r0, #4
	str r0, [r4, #0xc]
	b _022459A0
_022458F8:
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _0224591C
	add r0, r5, #0
	str r0, [r4, #4]
	bl MOD18_0223D638
	add r2, r5, #0
	mov r1, #0x30
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #5
	str r0, [r4, #0xc]
	b _022459A0
_0224591C:
	sub r1, r5, #1
	cmp r0, r1
	beq _022459A0
	add r0, r5, #0
	str r0, [r4, #4]
	mov r5, #1
	b _022459A0
_0224592A:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022459A0
	mov r0, #4
	str r0, [sp]
	ldr r0, [r6, #8]
	ldr r1, _022459E0 ; =0x022504F8
	ldr r2, _022459E4 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #4]
	mov r0, #6
	str r0, [r4, #0xc]
	b _022459A0
_0224594E:
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _02245964
	add r0, r5, #0
	str r0, [r4, #4]
	mov r0, #7
	str r0, [r4, #0xc]
	b _022459A0
_02245964:
	sub r1, r5, #1
	cmp r0, r1
	beq _022459A0
	add r0, r5, #0
	str r0, [r4, #4]
	mov r5, #1
	b _022459A0
_02245972:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #1
	add r1, sp, #4
	strb r0, [r1, #1]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	strb r0, [r1]
	add r0, r5, #0
	strb r0, [r1, #2]
	mov r0, #0x3b
	add r1, sp, #4
	bl FUN_020311D0
	add r0, r7, #0
	add r1, r4, #0
	bl MOD18_022457D4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_022459A0:
	bl FUN_0202EDD8
	cmp r0, #0
	bne _022459C4
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	cmp r0, #8
	bhs _022459C4
	bl FUN_02030E7C
	cmp r0, #0
	bne _022459C4
	bl FUN_02031190
	cmp r0, #0
	beq _022459C4
	mov r5, #1
_022459C4:
	cmp r5, #0
	beq _022459DC
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r7, #0
	add r1, r4, #0
	bl MOD18_022457F8
	bl FUN_0204F7FC
_022459DC:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022459E0: .word MOD18_022504F8
_022459E4: .word 0x000003D9
	thumb_func_end MOD18_02245838

	thumb_func_start MOD18_022459E8
MOD18_022459E8: ; 0x022459E8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	bl MOD18_02247984
	mov r0, #4
	mov r1, #0x30
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x30
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x18]
	str r6, [r4, #0x1c]
	add r0, r4, #0
	ldr r1, [sp, #0x18]
	str r7, [r4, #0x20]
	add r0, #0x2b
	strb r1, [r0]
	add r0, r4, #0
	ldr r1, [sp, #0x1c]
	add r0, #0x2c
	strb r1, [r0]
	mov r0, #2
	str r0, [r4, #0x14]
	ldr r0, [sp]
	add r1, r4, #0
	str r0, [r4, #0x24]
	ldr r0, _02245A48 ; =MOD18_02245838
	str r5, [r4]
	mov r2, #0x64
	bl FUN_0200CA44
	str r0, [r4, #8]
	ldr r1, [r4, #8]
	ldr r2, _02245A4C ; =MOD18_022457F8
	add r0, r4, #0
	bl MOD18_0223E688
	bl FUN_0204F7E4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245A48: .word MOD18_02245838
_02245A4C: .word MOD18_022457F8
	thumb_func_end MOD18_022459E8

	thumb_func_start MOD18_02245A50
MOD18_02245A50: ; 0x02245A50
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	add r6, r1, #0
	add r7, r2, #0
	mov r4, #0
	str r3, [sp]
	cmp r0, #0
	bne _02245AA2
	mov r0, #0xb
	mov r1, #0x30
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x30
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x18]
	str r6, [r4, #0x1c]
	add r0, r4, #0
	ldr r1, [sp, #0x18]
	str r7, [r4, #0x20]
	add r0, #0x2b
	strb r1, [r0]
	add r0, r4, #0
	ldr r1, [sp, #0x1c]
	add r0, #0x2c
	strb r1, [r0]
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	cmp r0, #2
	beq _02245A9A
	bl ErrorHandling
_02245A9A:
	mov r0, #2
	str r0, [r4, #0x14]
	ldr r0, [sp]
	str r0, [r4, #0x24]
_02245AA2:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_02245A50

	thumb_func_start MOD18_02245AA8
MOD18_02245AA8: ; 0x02245AA8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	mov r7, #0
	str r0, [sp]
	str r1, [sp, #4]
	add r4, r7, #0
_02245AB4:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	beq _02245B0C
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _02245AD6
	add r0, r4, #0
	bl FUN_0204E544
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_0204E598
	b _02245AE4
_02245AD6:
	add r0, r4, #0
	bl FUN_0204E3EC
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_0204E440
_02245AE4:
	add r5, r0, #0
	ldr r0, _02245B18 ; =0x0000FFFF
	cmp r6, r0
	bne _02245AF0
	cmp r5, r0
	beq _02245B0C
_02245AF0:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _02245B0C
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02244DE8
	ldr r1, [sp]
	cmp r0, r1
	bne _02245B0C
	add r7, r7, #1
_02245B0C:
	add r4, r4, #1
	cmp r4, #8
	blt _02245AB4
	add r0, r7, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245B18: .word 0x0000FFFF
	thumb_func_end MOD18_02245AA8

	thumb_func_start MOD18_02245B1C
MOD18_02245B1C: ; 0x02245B1C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	str r2, [sp, #8]
	add r6, r0, #0
	add r7, r1, #0
	str r3, [sp, #0xc]
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	add r5, r0, #0
	ldr r1, [sp, #0x30]
	mov r0, #2
	bl ListMenuItems_ctor
	add r4, r0, #0
	add r1, r5, #0
	mov r2, #0x26
	mov r3, #0
	bl ListMenuItems_AppendFromMsgData
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x27
	mov r3, #1
	bl ListMenuItems_AppendFromMsgData
	ldr r0, [sp, #0x30]
	mov r1, #1
	str r4, [sp, #0x10]
	bl AllocWindows
	add r1, r0, #0
	str r1, [sp, #0x14]
	mov r0, #0
	add r3, sp, #0x10
	strb r0, [r3, #8]
	mov r0, #1
	strb r0, [r3, #9]
	mov r0, #2
	strb r0, [r3, #0xa]
	ldrb r0, [r3, #0xb]
	mov r2, #0xf
	bic r0, r2
	strb r0, [r3, #0xb]
	ldrb r4, [r3, #0xb]
	mov r0, #0x30
	bic r4, r0
	strb r4, [r3, #0xb]
	ldrb r0, [r3, #0xb]
	bic r0, r2
	strb r0, [r3, #0xb]
	add r0, r6, #0
	add r2, r7, #0
	bl FUN_02019150
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #8]
	ldr r3, [sp, #0xc]
	mov r1, #1
	bl FUN_0200CCA4
	ldr r0, [sp, #0x30]
	mov r2, #0
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	add r0, sp, #0x10
	mov r1, #8
	add r3, r2, #0
	bl FUN_02001C14
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD18_02245B1C

	thumb_func_start MOD18_02245BB4
MOD18_02245BB4: ; 0x02245BB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r4, r1, #0
	add r7, r0, #0
	ldr r0, [r4, #0xc]
	mov r5, #0
	ldr r6, [r4]
	cmp r0, #0xa
	bhi _02245C7A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02245BD2: ; jump table
	.short _02245BE8 - _02245BD2 - 2 ; case 0
	.short _02245C14 - _02245BD2 - 2 ; case 1
	.short _02245C38 - _02245BD2 - 2 ; case 2
	.short _02245C5C - _02245BD2 - 2 ; case 3
	.short _02245C6E - _02245BD2 - 2 ; case 4
	.short _02245C94 - _02245BD2 - 2 ; case 5
	.short _02245CF8 - _02245BD2 - 2 ; case 6
	.short _02245D1C - _02245BD2 - 2 ; case 7
	.short _02245D4E - _02245BD2 - 2 ; case 8
	.short _02245D6C - _02245BD2 - 2 ; case 9
	.short _02245D96 - _02245BD2 - 2 ; case 10
_02245BE8:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x2b
	ldrb r0, [r0]
	cmp r1, r0
	beq _02245BFE
	mov r6, #0x2d
	mov r0, #1
	b _02245C02
_02245BFE:
	mov r6, #0x29
	mov r0, #4
_02245C02:
	str r0, [r4, #0xc]
	bl MOD18_0223D638
	mov r2, #0
	add r1, r6, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _02245DCE
_02245C14:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02245C7A
	mov r0, #4
	str r0, [sp]
	ldr r0, [r6, #8]
	ldr r1, _02245E08 ; =0x022504F8
	ldr r2, _02245E0C ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #4]
	mov r0, #2
	str r0, [r4, #0xc]
	b _02245DCE
_02245C38:
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _02245C4E
	add r0, r5, #0
	str r0, [r4, #4]
	mov r0, #3
	str r0, [r4, #0xc]
	b _02245DCE
_02245C4E:
	sub r1, r5, #1
	cmp r0, r1
	beq _02245C7A
	add r0, r5, #0
	str r0, [r4, #4]
	mov r5, #1
	b _02245DCE
_02245C5C:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02245C7A
	mov r0, #0xa
	str r0, [r4, #0xc]
	b _02245DCE
_02245C6E:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	beq _02245C7C
_02245C7A:
	b _02245DCE
_02245C7C:
	mov r0, #4
	str r0, [sp]
	ldr r0, [r6, #8]
	ldr r1, _02245E08 ; =0x022504F8
	ldr r2, _02245E0C ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #4]
	mov r0, #5
	str r0, [r4, #0xc]
	b _02245DCE
_02245C94:
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _02245CEA
	add r0, r5, #0
	str r0, [r4, #4]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	bl FUN_0204EE9C
	cmp r0, #0
	bne _02245CC2
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r5, #0
	bl MOD18_02245AA8
	cmp r0, #0
	ble _02245CD6
_02245CC2:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x2c
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #3
	str r0, [r4, #0xc]
	b _02245DCE
_02245CD6:
	bl MOD18_0223D638
	add r2, r5, #0
	mov r1, #0x25
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #6
	str r0, [r4, #0xc]
	b _02245DCE
_02245CEA:
	sub r1, r5, #1
	cmp r0, r1
	beq _02245DCE
	add r0, r5, #0
	str r0, [r4, #4]
	mov r5, #1
	b _02245DCE
_02245CF8:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02245DCE
	mov r0, #4
	str r0, [sp]
	ldr r0, [r6, #8]
	ldr r1, _02245E10 ; =0x02250500
	ldr r2, _02245E0C ; =0x000003D9
	mov r3, #0xb
	bl MOD18_02245B1C
	str r0, [r4, #4]
	mov r0, #7
	str r0, [r4, #0xc]
	b _02245DCE
_02245D1C:
	ldr r0, [r4, #4]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _02245D32
	add r0, r5, #0
	str r0, [r4, #4]
	mov r0, #3
	str r0, [r4, #0xc]
	b _02245DCE
_02245D32:
	cmp r0, #1
	bne _02245D40
	add r0, r5, #0
	str r0, [r4, #4]
	mov r0, #8
	str r0, [r4, #0xc]
	b _02245DCE
_02245D40:
	sub r1, r5, #1
	cmp r0, r1
	beq _02245DCE
	add r0, r5, #0
	str r0, [r4, #4]
	mov r5, #1
	b _02245DCE
_02245D4E:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02245DCE
	bl MOD18_0223D638
	bl MOD18_0224DD94
	bl FUN_0204FCF4
	mov r0, #9
	str r0, [r4, #0xc]
	b _02245DCE
_02245D6C:
	bl FUN_0202EDD8
	cmp r0, #0
	beq _02245DCE
	bl FUN_02031190
	cmp r0, #0
	bne _02245DCE
	mov r1, #1
	add r0, sp, #4
	strb r1, [r0]
	mov r0, #0x56
	add r1, sp, #4
	bl FUN_020311D0
	add r0, r7, #0
	add r1, r4, #0
	bl MOD18_022457D4
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_02245D96:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r4, #0
	mov r2, #1
	add r1, sp, #4
	strb r2, [r1, #2]
	add r0, #0x2c
	ldrb r0, [r0]
	strb r0, [r1, #1]
	strb r2, [r1, #3]
	add r1, sp, #4
	mov r0, #0x3b
	add r1, #1
	bl FUN_020311D0
	add r0, r7, #0
	add r1, r4, #0
	bl MOD18_022457D4
	ldr r0, _02245E14 ; =0x022513EC
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _02245E18 ; =0x000012E4
	add sp, #8
	strb r2, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
_02245DCE:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	cmp r0, #0x10
	beq _02245DEC
	bl FUN_0204E34C
	cmp r0, #0
	bne _02245DEC
	ldr r0, [r4, #0xc]
	cmp r0, #8
	beq _02245DEC
	cmp r0, #9
	beq _02245DEC
	mov r5, #1
_02245DEC:
	cmp r5, #0
	beq _02245E04
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r7, #0
	add r1, r4, #0
	bl MOD18_022457F8
	bl FUN_0204F7FC
_02245E04:
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245E08: .word MOD18_022504F8
_02245E0C: .word 0x000003D9
_02245E10: .word MOD18_02250500
_02245E14: .word MOD18_022513EC
_02245E18: .word 0x000012E4
	thumb_func_end MOD18_02245BB4

	thumb_func_start MOD18_02245E1C
MOD18_02245E1C: ; 0x02245E1C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #4
	mov r1, #0x30
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x30
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0x18]
	str r6, [r4, #0x1c]
	add r0, r4, #0
	ldr r1, [sp, #0x18]
	str r7, [r4, #0x20]
	add r0, #0x2b
	strb r1, [r0]
	add r0, r4, #0
	ldr r1, [sp, #0x1c]
	add r0, #0x2c
	strb r1, [r0]
	mov r0, #2
	str r0, [r4, #0x14]
	ldr r0, [sp]
	mov r1, #0
	str r0, [r4, #0x24]
	add r0, r4, #0
	str r5, [r4]
	add r0, #0x29
	strb r1, [r0]
	bl MOD18_02247984
	ldr r0, _02245E84 ; =MOD18_02245BB4
	add r1, r4, #0
	mov r2, #0x64
	bl FUN_0200CA44
	str r0, [r4, #8]
	ldr r1, [r4, #8]
	ldr r2, _02245E88 ; =MOD18_022457F8
	add r0, r4, #0
	bl MOD18_0223E688
	bl FUN_0204F7E4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245E84: .word MOD18_02245BB4
_02245E88: .word MOD18_022457F8
	thumb_func_end MOD18_02245E1C

	thumb_func_start MOD18_02245E8C
MOD18_02245E8C: ; 0x02245E8C
	mov r0, #8
	bx lr
	thumb_func_end MOD18_02245E8C

	thumb_func_start MOD18_02245E90
MOD18_02245E90: ; 0x02245E90
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r0, _02245F10 ; =0x022513EC
	add r4, r2, #0
	ldr r1, [r0]
	ldrb r0, [r4, #4]
	mov r2, #0xff
	add r1, r1, r0
	ldr r0, _02245F14 ; =0x00001363
	strb r2, [r1, r0]
	ldrb r5, [r4, #4]
	bl FUN_02031190
	cmp r5, r0
	bne _02245EFA
	bl MOD18_0224D344
	bl MOD18_02248FC8
	bl MOD18_0223E6B8
	bl FUN_02031190
	mov r1, #0
	bl MOD18_0223FCE8
	mov r0, #0x2b
	bl FUN_020311DC
	ldr r1, _02245F10 ; =0x022513EC
	ldr r0, _02245F18 ; =0x000013E6
	ldr r2, [r1]
	mov r3, #0
	strb r3, [r2, r0]
	ldrb r0, [r4, #4]
	str r0, [sp]
	ldrb r0, [r4, #6]
	str r0, [sp, #4]
	ldr r0, [r1]
	ldrh r1, [r4]
	ldrh r2, [r4, #2]
	ldrb r3, [r4, #5]
	ldr r0, [r0]
	bl MOD18_0224686C
	ldr r0, _02245F10 ; =0x022513EC
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0xa
	lsl r0, r0, #8
	str r2, [r1, r0]
	add sp, #8
	pop {r3, r4, r5, pc}
_02245EFA:
	add r0, r5, #0
	bl MOD18_02243FB8
	ldrb r0, [r4, #4]
	ldrh r1, [r4]
	ldrh r2, [r4, #2]
	ldrb r3, [r4, #5]
	bl FUN_0204E7CC
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02245F10: .word MOD18_022513EC
_02245F14: .word 0x00001363
_02245F18: .word 0x000013E6
	thumb_func_end MOD18_02245E90

	thumb_func_start MOD18_02245F1C
MOD18_02245F1C: ; 0x02245F1C
	ldr r3, _02245F24 ; =FUN_020311DC
	mov r0, #0x38
	bx r3
	nop
_02245F24: .word FUN_020311DC
	thumb_func_end MOD18_02245F1C

	thumb_func_start MOD18_02245F28
MOD18_02245F28: ; 0x02245F28
	push {r3, r4}
	ldr r2, _02245F44 ; =0x022513EC
	mov r4, #0xff
	ldr r1, [r2]
	add r3, r1, r0
	ldr r1, _02245F48 ; =0x0000136B
	strb r4, [r3, r1]
	ldr r2, [r2]
	add r1, #8
	add r0, r2, r0
	strb r4, [r0, r1]
	pop {r3, r4}
	bx lr
	nop
_02245F44: .word MOD18_022513EC
_02245F48: .word 0x0000136B
	thumb_func_end MOD18_02245F28

	thumb_func_start MOD18_02245F4C
MOD18_02245F4C: ; 0x02245F4C
	ldr r1, _02245F68 ; =0x022513EC
	ldr r1, [r1]
	cmp r1, #0
	beq _02245F62
	add r1, r1, r0
	ldr r0, _02245F6C ; =0x0000136B
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _02245F62
	mov r0, #1
	bx lr
_02245F62:
	mov r0, #0
	bx lr
	nop
_02245F68: .word MOD18_022513EC
_02245F6C: .word 0x0000136B
	thumb_func_end MOD18_02245F4C

	thumb_func_start MOD18_02245F70
MOD18_02245F70: ; 0x02245F70
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	ldr r0, _02245F9C ; =0x022513EC
	add r7, r1, #0
	ldr r1, [r0]
	add r5, r3, #0
	mov r0, #0x96
	add r1, #8
	mul r0, r5
	add r4, r1, r0
	beq _02245F9A
	add r0, r2, #0
	bl FUN_0204F610
	add r3, r0, #0
	add r0, r4, #2
	add r1, r6, #0
	add r2, r7, #0
	bl FUN_02026C68
	strb r5, [r4]
_02245F9A:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02245F9C: .word MOD18_022513EC
	thumb_func_end MOD18_02245F70

	thumb_func_start MOD18_02245FA0
MOD18_02245FA0: ; 0x02245FA0
	push {r3, lr}
	bl FUN_02031190
	ldr r1, _02245FB8 ; =0x022513EC
	mov r0, #0x35
	ldr r2, [r1]
	ldr r1, _02245FBC ; =0x00000968
	add r1, r2, r1
	mov r2, #0x96
	bl FUN_0203105C
	pop {r3, pc}
	.align 2, 0
_02245FB8: .word MOD18_022513EC
_02245FBC: .word 0x00000968
	thumb_func_end MOD18_02245FA0

	thumb_func_start MOD18_02245FC0
MOD18_02245FC0: ; 0x02245FC0
	push {r4, lr}
	ldr r1, _02245FDC ; =0x022513EC
	add r4, r0, #0
	ldr r3, [r1]
	mov r2, #0x96
	add r1, r4, #0
	add r3, #8
	mul r1, r2
	mov r0, #0x36
	add r1, r3, r1
	bl FUN_02031000
	pop {r4, pc}
	nop
_02245FDC: .word MOD18_022513EC
	thumb_func_end MOD18_02245FC0

	thumb_func_start MOD18_02245FE0
MOD18_02245FE0: ; 0x02245FE0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	ldr r0, _022460EC ; =0x022513EC
	add r6, r2, #0
	ldr r0, [r0]
	cmp r0, #0
	beq _022460E6
	bl FUN_02031190
	ldrb r1, [r6, #1]
	cmp r1, r0
	bne _02246020
	ldr r0, _022460EC ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _022460F0 ; =0x000012E4
	ldrb r1, [r2, r0]
	cmp r1, #2
	bne _02246020
	mov r1, #0
	strb r1, [r2, r0]
	bl FUN_0204F7FC
	mov r0, #0x38
	bl FUN_020311DC
	mov r0, #0
	bl FUN_0204D168
	bl MOD18_022479A0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_02246020:
	ldr r0, _022460EC ; =0x022513EC
	mov r2, #5
	ldr r1, [r0]
	ldr r0, _022460F0 ; =0x000012E4
	strb r2, [r1, r0]
	ldrb r5, [r6]
	cmp r5, #0x11
	blt _02246034
	bl ErrorHandling
_02246034:
	ldr r0, _022460EC ; =0x022513EC
	mov r2, #0x96
	ldr r4, [r0]
	add r7, r5, #0
	add r4, #8
	mul r7, r2
	add r5, r4, r7
	add r0, r6, #0
	add r1, r5, #0
	bl MI_CpuCopy8
	ldr r2, _022460EC ; =0x022513EC
	ldrb r1, [r5, #1]
	ldr r3, [r2]
	ldrb r0, [r4, r7]
	add r3, r3, r1
	ldr r1, _022460F4 ; =0x00001363
	strb r0, [r3, r1]
	ldrb r3, [r4, r7]
	cmp r3, #0x10
	beq _02246068
	ldrb r0, [r5, #1]
	ldr r2, [r2]
	add r1, #0x18
	add r0, r2, r0
	strb r3, [r0, r1]
_02246068:
	ldrb r0, [r5]
	add r1, sp, #8
	bl MOD18_02244EB4
	ldrb r4, [r5, #1]
	bl FUN_02031190
	cmp r4, r0
	bne _022460D8
	ldr r1, _022460EC ; =0x022513EC
	ldr r0, _022460F8 ; =0x000013E6
	ldr r2, [r1]
	mov r3, #1
	strb r3, [r2, r0]
	ldrb r0, [r5, #1]
	mov r3, #0
	add r2, sp, #8
	str r0, [sp]
	str r3, [sp, #4]
	ldr r0, [r1]
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	ldr r0, [r0]
	sub r2, r2, #1
	bl MOD18_0224686C
	ldr r0, _022460EC ; =0x022513EC
	ldr r1, [r0]
	mov r0, #0xa
	lsl r0, r0, #8
	str r5, [r1, r0]
	add r0, r5, #2
	bl FUN_02026C88
	ldr r1, _022460EC ; =0x022513EC
	ldr r2, [r1]
	ldr r1, _022460FC ; =0x000013DC
	strh r0, [r2, r1]
	add r0, r5, #2
	bl FUN_02026C90
	ldr r1, _022460EC ; =0x022513EC
	ldr r2, [r1]
	ldr r1, _02246100 ; =0x000013DE
	strh r0, [r2, r1]
	add r0, r5, #2
	bl FUN_02026C98
	ldr r1, _022460EC ; =0x022513EC
	ldr r2, [r1]
	ldr r1, _02246104 ; =0x000013E0
	strb r0, [r2, r1]
	bl MOD18_0223E7FC
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
_022460D8:
	add r2, sp, #8
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	add r0, r4, #0
	mov r3, #0
	bl FUN_0204E7CC
_022460E6:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022460EC: .word MOD18_022513EC
_022460F0: .word 0x000012E4
_022460F4: .word 0x00001363
_022460F8: .word 0x000013E6
_022460FC: .word 0x000013DC
_02246100: .word 0x000013DE
_02246104: .word 0x000013E0
	thumb_func_end MOD18_02245FE0

	thumb_func_start MOD18_02246108
MOD18_02246108: ; 0x02246108
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, _02246188 ; =0x022513EC
	ldr r6, [r0]
	cmp r6, #0
	beq _02246186
	mov r3, #0x96
	add r7, r5, #0
	add r6, #8
	mul r7, r3
	add r4, r6, r7
	add r0, r2, #0
	add r1, r4, #0
	add r2, r3, #0
	bl MI_CpuCopy8
	strb r5, [r6, r7]
	ldr r0, _02246188 ; =0x022513EC
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _0224618C ; =0x000013E2
	add r6, r5, #0
	strb r2, [r1, r0]
	mov r0, #6
	mul r6, r0
	add r0, r4, #2
	bl FUN_02026C88
	ldr r1, _02246188 ; =0x022513EC
	ldr r1, [r1]
	add r2, r1, r6
	ldr r1, _02246190 ; =0x000012B4
	strh r0, [r2, r1]
	add r0, r4, #2
	bl FUN_02026C90
	ldr r1, _02246188 ; =0x022513EC
	ldr r1, [r1]
	add r2, r1, r6
	ldr r1, _02246194 ; =0x000012B6
	strh r0, [r2, r1]
	add r0, r4, #2
	bl FUN_02026C98
	ldr r1, _02246188 ; =0x022513EC
	ldr r1, [r1]
	add r2, r1, r6
	ldr r1, _02246198 ; =0x000012B8
	strb r0, [r2, r1]
	bl MOD18_022461CC
	ldr r1, _02246188 ; =0x022513EC
	add r0, r4, #2
	ldr r2, [r1]
	ldr r1, _0224619C ; =0x00000A04
	add r2, r2, r1
	lsl r1, r5, #7
	add r1, r2, r1
	bl MOD18_02245128
	add r0, r5, #0
	bl MOD18_0224784C
_02246186:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02246188: .word MOD18_022513EC
_0224618C: .word 0x000013E2
_02246190: .word 0x000012B4
_02246194: .word 0x000012B6
_02246198: .word 0x000012B8
_0224619C: .word 0x00000A04
	thumb_func_end MOD18_02246108

	thumb_func_start MOD18_022461A0
MOD18_022461A0: ; 0x022461A0
	mov r0, #0x96
	bx lr
	thumb_func_end MOD18_022461A0

	thumb_func_start MOD18_022461A4
MOD18_022461A4: ; 0x022461A4
	ldr r0, _022461B0 ; =0x022513EC
	ldr r1, [r0]
	ldr r0, _022461B4 ; =0x000013E3
	ldrb r0, [r1, r0]
	bx lr
	nop
_022461B0: .word MOD18_022513EC
_022461B4: .word 0x000013E3
	thumb_func_end MOD18_022461A4

	thumb_func_start MOD18_022461B8
MOD18_022461B8: ; 0x022461B8
	ldr r0, _022461C4 ; =0x022513EC
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _022461C8 ; =0x000013E3
	strb r2, [r1, r0]
	bx lr
	.align 2, 0
_022461C4: .word MOD18_022513EC
_022461C8: .word 0x000013E3
	thumb_func_end MOD18_022461B8

	thumb_func_start MOD18_022461CC
MOD18_022461CC: ; 0x022461CC
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	ldr r7, _02246238 ; =0x022513EC
	mov ip, r4
	add r5, r4, #0
_022461D6:
	ldr r0, [r7]
	ldr r1, _0224623C ; =0x000012B4
	add r2, r0, r1
	add r1, r0, r4
	ldrh r6, [r2, r5]
	ldr r0, _02246240 ; =0x0000138B
	add r3, r2, r5
	strb r6, [r1, r0]
	ldrh r0, [r2, r5]
	add r5, r5, #6
	asr r1, r0, #8
	mov r0, #0xf
	add r2, r1, #0
	and r2, r0
	ldrh r0, [r3, #2]
	asr r1, r0, #4
	mov r0, #0xf0
	and r0, r1
	add r2, r2, r0
	ldr r0, [r7]
	add r1, r0, r4
	ldr r0, _02246244 ; =0x0000138C
	strb r2, [r1, r0]
	ldr r0, [r7]
	ldrh r2, [r3, #2]
	add r1, r0, r4
	ldr r0, _02246248 ; =0x0000138D
	strb r2, [r1, r0]
	ldr r1, [r7]
	ldrb r0, [r3, #4]
	add r2, r1, r4
	ldr r1, _0224624C ; =0x0000138E
	add r4, r4, #4
	strb r0, [r2, r1]
	mov r0, ip
	add r0, r0, #1
	mov ip, r0
	cmp r0, #8
	blt _022461D6
	ldr r1, _02246238 ; =0x022513EC
	mov r0, #0x37
	ldr r2, [r1]
	ldr r1, _02246240 ; =0x0000138B
	add r1, r2, r1
	mov r2, #0x20
	bl FUN_02031000
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246238: .word MOD18_022513EC
_0224623C: .word 0x000012B4
_02246240: .word 0x0000138B
_02246244: .word 0x0000138C
_02246248: .word 0x0000138D
_0224624C: .word 0x0000138E
	thumb_func_end MOD18_022461CC

	thumb_func_start MOD18_02246250
MOD18_02246250: ; 0x02246250
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r0, _022462F8 ; =0x022513EC
	str r2, [sp]
	ldr r0, [r0]
	cmp r0, #0
	beq _022462F2
	mov r4, #0
_02246260:
	add r0, r4, #0
	bl MOD18_02246430
	add r4, r4, #1
	cmp r4, #8
	blt _02246260
	mov r5, #0
	add r7, r5, #0
	add r6, r5, #0
	add r4, sp, #4
_02246274:
	ldr r0, _022462F8 ; =0x022513EC
	ldr r1, [r0]
	ldr r0, _022462FC ; =0x00001284
	add r0, r1, r0
	mov ip, r0
	ldr r0, [sp]
	add r2, r0, r5
	ldrb r0, [r0, r5]
	add r5, r5, #4
	strh r0, [r4]
	ldrb r0, [r2, #1]
	ldrh r3, [r4]
	lsl r1, r0, #8
	mov r0, #0xf
	lsl r0, r0, #8
	and r0, r1
	add r0, r3, r0
	strh r0, [r4]
	ldrb r0, [r2, #1]
	lsl r1, r0, #4
	mov r0, #0xf
	lsl r0, r0, #8
	and r0, r1
	strh r0, [r4, #2]
	ldrh r1, [r4, #2]
	ldrb r0, [r2, #2]
	add r0, r1, r0
	strh r0, [r4, #2]
	ldrb r0, [r2, #3]
	strb r0, [r4, #4]
	ldrh r1, [r4]
	ldr r0, _02246300 ; =0x00000FFF
	cmp r1, r0
	beq _022462E0
	add r0, sp, #4
	ldrh r1, [r0, #2]
	ldr r0, _02246300 ; =0x00000FFF
	cmp r1, r0
	beq _022462E0
	mov r1, ip
	add r0, sp, #4
	add r1, r1, r6
	mov r2, #6
	bl MI_CpuCopy8
	add r0, sp, #4
	add r1, sp, #4
	add r2, sp, #4
	ldrh r0, [r0]
	ldrh r1, [r1, #2]
	ldrb r2, [r2, #4]
	add r3, r7, #0
	bl MOD18_0224630C
_022462E0:
	add r7, r7, #1
	add r6, r6, #6
	cmp r7, #8
	blt _02246274
	ldr r0, _022462F8 ; =0x022513EC
	mov r2, #1
	ldr r1, [r0]
	ldr r0, _02246304 ; =0x000013E3
	strb r2, [r1, r0]
_022462F2:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_022462F8: .word MOD18_022513EC
_022462FC: .word 0x00001284
_02246300: .word 0x00000FFF
_02246304: .word 0x000013E3
	thumb_func_end MOD18_02246250

	thumb_func_start MOD18_02246308
MOD18_02246308: ; 0x02246308
	mov r0, #0x20
	bx lr
	thumb_func_end MOD18_02246308

	thumb_func_start MOD18_0224630C
MOD18_0224630C: ; 0x0224630C
	push {r3, r4, r5, r6}
	ldr r5, _02246330 ; =0x022513EC
	ldr r4, [r5]
	add r6, r4, r3
	ldr r4, _02246334 ; =0x0000133A
	strb r2, [r6, r4]
	lsl r2, r3, #1
	ldr r3, [r5]
	add r6, r3, r2
	add r3, r4, #0
	sub r3, #0x44
	strh r0, [r6, r3]
	ldr r0, [r5]
	sub r4, #0x22
	add r0, r0, r2
	strh r1, [r0, r4]
	pop {r3, r4, r5, r6}
	bx lr
	.align 2, 0
_02246330: .word MOD18_022513EC
_02246334: .word 0x0000133A
	thumb_func_end MOD18_0224630C

	thumb_func_start MOD18_02246338
MOD18_02246338: ; 0x02246338
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r0, _02246414 ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _02246418 ; =0x000013E4
	ldrb r1, [r2, r0]
	cmp r1, #0
	bne _0224640E
	add r0, r0, #1
	ldrb r0, [r2, r0]
	cmp r0, #0
	beq _0224640E
	ldr r0, [r2]
	ldr r0, [r0, #0x38]
	cmp r0, #0
	beq _0224640E
	bl FUN_02055320
	add r4, r0, #0
	ldr r0, _02246414 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _0224640E
	mov r5, #0
	add r4, r5, #0
_0224637A:
	cmp r5, #8
	bge _02246394
	add r0, r5, #0
	bl FUN_0202DFA4
	cmp r0, #0
	bne _02246394
	add r0, r5, #0
	bl MOD18_022453A8
	add r0, r5, #0
	bl MOD18_022475F8
_02246394:
	ldr r0, _02246414 ; =0x022513EC
	ldr r1, [r0]
	ldr r0, _0224641C ; =0x0000133A
	add r2, r1, r5
	ldrb r6, [r2, r0]
	cmp r6, #0xff
	beq _02246406
	ldr r3, _02246420 ; =0x000012F6
	add r0, r1, r4
	ldrh r3, [r0, r3]
	str r3, [sp, #8]
	ldr r3, _02246424 ; =0x00001318
	ldrh r7, [r0, r3]
	add r0, r3, #0
	sub r0, #0x33
	ldrb r0, [r2, r0]
	cmp r0, #0xff
	beq _022463C2
	ldr r1, [r1]
	add r1, #0xa0
	ldr r1, [r1]
	bl MOD05_021E7C80
_022463C2:
	ldr r0, [sp, #8]
	ldr r2, _02246428 ; =0x000001AD
	lsl r1, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0xc]
	mov r0, #0
	str r0, [sp, #0x10]
	mov r0, #2
	lsl r1, r7, #0x10
	lsl r0, r0, #0xe
	add r0, r1, r0
	str r0, [sp, #0x14]
	ldr r0, _02246414 ; =0x022513EC
	add r2, r6, r2
	ldr r0, [r0]
	add r3, sp, #0xc
	ldr r1, [r0]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r1, #0x4c]
	str r0, [sp, #4]
	add r0, r1, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r1, #0x2c]
	bl MOD05_021E7FBC
	ldr r1, _02246414 ; =0x022513EC
	ldr r1, [r1]
	add r2, r1, r5
	ldr r1, _0224642C ; =0x000012E5
	strb r0, [r2, r1]
_02246406:
	add r5, r5, #1
	add r4, r4, #2
	cmp r5, #0x11
	blt _0224637A
_0224640E:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246414: .word MOD18_022513EC
_02246418: .word 0x000013E4
_0224641C: .word 0x0000133A
_02246420: .word 0x000012F6
_02246424: .word 0x00001318
_02246428: .word 0x000001AD
_0224642C: .word 0x000012E5
	thumb_func_end MOD18_02246338

	thumb_func_start MOD18_02246430
MOD18_02246430: ; 0x02246430
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02246464 ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _02246468 ; =0x000012E5
	add r1, r2, r4
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _02246460
	ldr r1, [r2]
	add r1, #0xa0
	ldr r1, [r1]
	bl MOD05_021E7C80
	ldr r1, _02246464 ; =0x022513EC
	mov r3, #0xff
	ldr r0, [r1]
	add r2, r0, r4
	ldr r0, _02246468 ; =0x000012E5
	strb r3, [r2, r0]
	ldr r1, [r1]
	add r0, #0x55
	add r1, r1, r4
	strb r3, [r1, r0]
_02246460:
	pop {r4, pc}
	nop
_02246464: .word MOD18_022513EC
_02246468: .word 0x000012E5
	thumb_func_end MOD18_02246430

	thumb_func_start MOD18_0224646C
MOD18_0224646C: ; 0x0224646C
	push {r4, lr}
	ldr r0, _02246488 ; =0x022513EC
	ldr r0, [r0]
	cmp r0, #0
	beq _02246484
	mov r4, #0
_02246478:
	add r0, r4, #0
	bl MOD18_02246430
	add r4, r4, #1
	cmp r4, #0x11
	blt _02246478
_02246484:
	pop {r4, pc}
	nop
_02246488: .word MOD18_022513EC
	thumb_func_end MOD18_0224646C

	thumb_func_start MOD18_0224648C
MOD18_0224648C: ; 0x0224648C
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _022464AA
	cmp r0, #1
	beq _022464B8
	b _022464CA
_022464AA:
	add r0, r5, #0
	bl FUN_02037394
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _022464CA
_022464B8:
	add r0, r5, #0
	bl FUN_0203739C
	cmp r0, #0
	bne _022464CA
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022464CA:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0224648C

	thumb_func_start MOD18_022464D0
MOD18_022464D0: ; 0x022464D0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _022464EE
	cmp r0, #1
	beq _022464FC
	b _0224650E
_022464EE:
	add r0, r5, #0
	bl LoadOverlay_MODULE_05
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	b _0224650E
_022464FC:
	add r0, r5, #0
	bl FUN_020464A4
	cmp r0, #0
	beq _0224650E
	mov r0, #0
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224650E:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_022464D0

	thumb_func_start MOD18_02246514
MOD18_02246514: ; 0x02246514
	push {r4, r5, r6, lr}
	sub sp, #0x20
	add r6, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r6, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0xd
	bhi _02246606
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224653A: ; jump table
	.short _02246556 - _0224653A - 2 ; case 0
	.short _02246580 - _0224653A - 2 ; case 1
	.short _022465B0 - _0224653A - 2 ; case 2
	.short _022465C6 - _0224653A - 2 ; case 3
	.short _022465D8 - _0224653A - 2 ; case 4
	.short _022465FC - _0224653A - 2 ; case 5
	.short _02246610 - _0224653A - 2 ; case 6
	.short _0224663A - _0224653A - 2 ; case 7
	.short _02246802 - _0224653A - 2 ; case 8
	.short _022466DA - _0224653A - 2 ; case 9
	.short _022466F6 - _0224653A - 2 ; case 10
	.short _0224672E - _0224653A - 2 ; case 11
	.short _02246762 - _0224653A - 2 ; case 12
	.short _0224678C - _0224653A - 2 ; case 13
_02246556:
	mov r0, #0
	bl MOD18_02247970
	bl MOD18_02247984
	bl FUN_02030F20
	add r1, r4, #0
	add r1, #0x28
	strb r0, [r1]
	bl FUN_02030FC8
	bl MOD18_0223CC80
	bl FUN_0204FD38
	cmp r0, #0
	beq _02246606
	mov r0, #1
	str r0, [r4, #0xc]
	b _02246848
_02246580:
	bl FUN_0200E31C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #2
	mov r1, #0x10
	mov r2, #0x12
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r5, #0x68]
	bl MOD18_0224484C
	ldr r0, _02246850 ; =0x00000603
	bl FUN_020054C8
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02246848
_022465B0:
	bl FUN_0200E308
	cmp r0, #0
	beq _02246606
	ldr r0, [r5, #0x68]
	cmp r0, #0
	bne _02246606
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02246848
_022465C6:
	add r0, r6, #0
	bl MOD18_0224648C
	cmp r0, #0
	beq _02246606
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02246848
_022465D8:
	ldr r0, [r4, #0x14]
	add r1, sp, #0xc
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x18]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x1c]
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x20]
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x24]
	str r0, [sp, #0x1c]
	add r0, r6, #0
	bl FUN_02049CB0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02246848
_022465FC:
	add r0, r6, #0
	bl MOD18_022464D0
	cmp r0, #0
	bne _02246608
_02246606:
	b _02246848
_02246608:
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02246848
_02246610:
	add r0, r5, #0
	bl MOD18_02244824
	str r0, [r5, #0x68]
	bl FUN_0200E31C
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x11
	mov r2, #0x13
	mov r3, #0
	bl FUN_0200E1D0
	ldr r0, [r4, #0xc]
	add r0, r0, #1
	str r0, [r4, #0xc]
	b _02246848
_0224663A:
	bl FUN_0200E308
	cmp r0, #0
	beq _0224670E
	bl FUN_0202EDD8
	cmp r0, #0
	beq _02246660
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _02246660
	add r0, r4, #0
	mov r1, #0
	add r0, #0x2e
	strb r1, [r0]
	b _02246668
_02246660:
	add r0, r4, #0
	mov r1, #1
	add r0, #0x2e
	strb r1, [r0]
_02246668:
	bl FUN_02030FA8
	bl FUN_0204F7E4
	mov r3, #0x80
	str r3, [sp]
	mov r0, #4
	str r0, [sp, #4]
	mov r0, #0x32
	mov r1, #0x34
	mov r2, #0
	add r3, #0xc0
	bl FUN_02006930
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r5, #8]
	ldr r2, _02246854 ; =0x000003D9
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add r0, r4, #0
	add r0, #0x2d
	ldrb r0, [r0]
	cmp r0, #0
	beq _022466BA
	bl FUN_0204F7D4
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x33
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #8
	str r0, [r4, #0xc]
	b _02246848
_022466BA:
	ldr r0, _02246858 ; =0x022513EC
	ldr r1, [r0]
	ldr r0, _0224685C ; =0x000013E6
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _022466CC
	mov r0, #0xd
	str r0, [r4, #0xc]
	b _02246848
_022466CC:
	add r0, r4, #0
	mov r1, #0
	add r0, #0x29
	strb r1, [r0]
	mov r0, #9
	str r0, [r4, #0xc]
	b _02246848
_022466DA:
	add r0, r4, #0
	add r0, #0x29
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x29
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x29
	strb r1, [r0]
	mov r0, #0xa
	str r0, [r4, #0xc]
	b _02246848
_022466F6:
	add r0, r4, #0
	add r0, #0x29
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x29
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x29
	ldrb r0, [r0]
	cmp r0, #0xa
	bhi _02246710
_0224670E:
	b _02246848
_02246710:
	bl FUN_0202EDD8
	cmp r0, #0
	beq _02246722
	add r0, r4, #0
	add r0, #0x2e
	ldrb r0, [r0]
	cmp r0, #0
	bne _02246728
_02246722:
	mov r0, #0xd
	str r0, [r4, #0xc]
	b _02246848
_02246728:
	mov r0, #0xb
	str r0, [r4, #0xc]
	b _02246848
_0224672E:
	bl FUN_0204FB14
	mov r0, #1
	mov r1, #0x24
	bl FUN_0205AFDC
	add r1, r0, #0
	ldr r0, [r5, #0x38]
	bl FUN_02057260
	mov r0, #1
	bl FUN_0204F6DC
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x44
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _02246860 ; =0x00000604
	bl FUN_020054C8
	mov r0, #0xc
	str r0, [r4, #0xc]
	b _02246848
_02246762:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02246848
	ldr r0, _02246864 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02246848
	mov r0, #0xd
	str r0, [r4, #0xc]
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #0
	bl FUN_0204F6DC
	b _02246848
_0224678C:
	bl FUN_0202EDD8
	cmp r0, #0
	beq _022467A6
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _022467A6
	bl FUN_0204FD24
	b _022467AA
_022467A6:
	bl FUN_0204FDE4
_022467AA:
	bl FUN_0204F7FC
	add r0, r4, #0
	bl FreeToHeap
	bl FUN_0202EDD8
	cmp r0, #0
	beq _022467CE
	ldr r0, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _022467CE
	bl MOD18_0223E444
	b _022467D2
_022467CE:
	bl MOD18_0223E458
_022467D2:
	ldr r0, _02246858 ; =0x022513EC
	ldr r2, _02246868 ; =0x000012E4
	ldr r0, [r0]
	ldrb r1, [r0, r2]
	cmp r1, #4
	bne _022467EC
	ldr r1, _0224685C ; =0x000013E6
	ldrb r1, [r0, r1]
	cmp r1, #0
	beq _022467EC
	mov r1, #6
	strb r1, [r0, r2]
	b _022467F2
_022467EC:
	ldr r1, _02246868 ; =0x000012E4
	mov r2, #0
	strb r2, [r0, r1]
_022467F2:
	bl MOD18_022479A0
	mov r0, #1
	bl MOD18_02247970
	add sp, #0x20
	mov r0, #1
	pop {r4, r5, r6, pc}
_02246802:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224682A
	ldr r0, _02246864 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224682A
	mov r0, #0xd
	str r0, [r4, #0xc]
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add sp, #0x20
	mov r0, #0
	pop {r4, r5, r6, pc}
_0224682A:
	bl FUN_02030F20
	cmp r0, #1
	ble _02246848
	add r0, r4, #0
	add r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	bne _02246848
	mov r0, #0xd
	str r0, [r4, #0xc]
	bl MOD18_0223D638
	bl MOD18_0224DD94
_02246848:
	mov r0, #0
	add sp, #0x20
	pop {r4, r5, r6, pc}
	nop
_02246850: .word 0x00000603
_02246854: .word 0x000003D9
_02246858: .word MOD18_022513EC
_0224685C: .word 0x000013E6
_02246860: .word 0x00000604
_02246864: .word gMain
_02246868: .word 0x000012E4
	thumb_func_end MOD18_02246514

	thumb_func_start MOD18_0224686C
MOD18_0224686C: ; 0x0224686C
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r5, [sp, #0x18]
	add r4, r0, #0
	str r5, [sp]
	str r5, [sp, #4]
	bl MOD18_02245A50
	add r2, r0, #0
	beq _0224688E
	ldr r1, [sp, #0x1c]
	add r0, #0x2d
	strb r1, [r0]
	ldr r1, _02246894 ; =MOD18_02246514
	add r0, r4, #0
	bl FUN_020463CC
_0224688E:
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02246894: .word MOD18_02246514
	thumb_func_end MOD18_0224686C

	thumb_func_start MOD18_02246898
MOD18_02246898: ; 0x02246898
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	str r0, [sp, #4]
	ldr r0, [r4, #0xc]
	mov r7, #0
	ldr r5, [r4]
	cmp r0, #0xa
	bhi _0224692C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022468B6: ; jump table
	.short _022468CC - _022468B6 - 2 ; case 0
	.short _02246914 - _022468B6 - 2 ; case 1
	.short _02246934 - _022468B6 - 2 ; case 2
	.short _02246980 - _022468B6 - 2 ; case 3
	.short _022469C6 - _022468B6 - 2 ; case 4
	.short _022469E0 - _022468B6 - 2 ; case 5
	.short _02246A04 - _022468B6 - 2 ; case 6
	.short _02246A80 - _022468B6 - 2 ; case 7
	.short _02246A80 - _022468B6 - 2 ; case 8
	.short _02246A28 - _022468B6 - 2 ; case 9
	.short _02246A40 - _022468B6 - 2 ; case 10
_022468CC:
	ldr r0, [r5, #0xc]
	bl FUN_02026CA8
	bl FUN_02026CA0
	strb r0, [r4, #0x12]
	bl FUN_0204F7E4
	bl MOD18_0223D638
	mov r1, #0x21
	bl MOD18_0224DDE8
	ldr r0, _02246AD0 ; =0x0000061E
	bl FUN_020054C8
	ldr r0, [r5, #0x38]
	bl FUN_020553A0
	add r1, r7, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD05_021E5E8C
	bl MOD18_0223D638
	add r2, r7, #0
	mov r1, #0x21
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r0, #1
	str r0, [r4, #0xc]
	add r0, r7, #0
	strb r0, [r4, #0x11]
	b _02246A80
_02246914:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224692C
	ldrb r0, [r4, #0x11]
	add r0, r0, #1
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x11]
	cmp r0, #0x1e
	bhi _0224692E
_0224692C:
	b _02246A80
_0224692E:
	mov r0, #2
	str r0, [r4, #0xc]
	b _02246A80
_02246934:
	bl FUN_02031190
	bl FUN_0204E4D4
	add r6, r0, #0
	bl FUN_02031190
	bl FUN_0204E50C
	str r0, [sp, #8]
	ldr r0, [r5, #0x38]
	bl FUN_020552F8
	bl FUN_0204F610
	str r0, [sp, #0xc]
	bl MOD18_0223D638
	add r2, r7, #0
	mov r1, #0x22
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	add r0, r6, #0
	mov r3, #0x10
	bl MOD18_0224630C
	ldr r3, [sp, #8]
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl MOD05_021E5B30
	mov r0, #3
	str r0, [r4, #0xc]
	b _02246A80
_02246980:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02246A80
	bl FUN_02031190
	add r1, r7, #0
	bl MOD18_02245AA8
	cmp r0, #0
	beq _022469A2
	mov r0, #4
	mov r6, #0x39
	str r0, [r4, #0xc]
	b _022469B6
_022469A2:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _022469B0
	mov r0, #5
	mov r6, #0x24
	str r0, [r4, #0xc]
	b _022469B6
_022469B0:
	mov r0, #5
	mov r6, #0x23
	str r0, [r4, #0xc]
_022469B6:
	bl MOD18_0223D638
	mov r2, #0
	add r1, r6, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _02246A80
_022469C6:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02246A80
	ldr r0, _02246AD4 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r1, r0
	beq _02246A80
	add r7, r0, #0
	b _02246A80
_022469E0:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02246A80
	mov r0, #4
	str r0, [sp]
	ldr r0, [r5, #8]
	ldr r1, _02246AD8 ; =0x022504F8
	ldr r2, _02246ADC ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #8]
	mov r0, #6
	str r0, [r4, #0xc]
	b _02246A80
_02246A04:
	ldr r0, [r4, #8]
	mov r1, #4
	bl FUN_020021AC
	cmp r0, #0
	bne _02246A1A
	mov r0, #9
	str r0, [r4, #0xc]
	add r0, r7, #0
	str r0, [r4, #8]
	b _02246A80
_02246A1A:
	sub r1, r7, #1
	cmp r0, r1
	beq _02246A80
	mov r0, #0
	mov r7, #1
	str r0, [r4, #8]
	b _02246A80
_02246A28:
	mov r0, #0x21
	bl MOD18_02249AD8
	bl MOD18_0223D638
	bl MOD18_0224DD94
	bl FUN_0204FCF4
	mov r0, #0xa
	str r0, [r4, #0xc]
	b _02246A80
_02246A40:
	bl FUN_0202EDD8
	cmp r0, #0
	beq _02246A80
	bl FUN_02031190
	cmp r0, #0
	bne _02246A80
	mov r1, #2
	add r0, sp, #0x10
	strb r1, [r0]
	ldrb r1, [r4, #0x12]
	cmp r1, #0
	beq _02246A60
	mov r1, #3
	strb r1, [r0]
_02246A60:
	bl MOD18_02246FB4
	mov r0, #0x56
	add r1, sp, #0x10
	bl FUN_020311D0
	ldr r0, [sp, #4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	bl MOD18_0223E6A0
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_02246A80:
	cmp r7, #0
	beq _02246ACA
	bl MOD18_0223D638
	ldr r3, _02246AE0 ; =MOD18_022453E0
	mov r1, #0x38
	mov r2, #1
	bl MOD18_0224DCB8
	mov r0, #0x10
	bl MOD18_02246430
	bl FUN_02031190
	bl FUN_0204E4D4
	add r6, r0, #0
	bl FUN_02031190
	bl FUN_0204E50C
	add r3, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	mov r2, #0
	bl MOD05_021E5B30
	ldr r0, [sp, #4]
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	bl MOD18_0223E6A0
	bl MOD18_022479A0
_02246ACA:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_02246AD0: .word 0x0000061E
_02246AD4: .word gMain
_02246AD8: .word MOD18_022504F8
_02246ADC: .word 0x000003D9
_02246AE0: .word MOD18_022453E0
	thumb_func_end MOD18_02246898

	thumb_func_start MOD18_02246AE4
MOD18_02246AE4: ; 0x02246AE4
	push {r3, lr}
	mov r1, #0
	add r0, sp, #0
	strb r1, [r0]
	mov r0, #0x56
	add r1, sp, #0
	bl FUN_020311D0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_02246AE4

	thumb_func_start MOD18_02246AF8
MOD18_02246AF8: ; 0x02246AF8
	mov r0, #2
	bx lr
	thumb_func_end MOD18_02246AF8

	thumb_func_start MOD18_02246AFC
MOD18_02246AFC: ; 0x02246AFC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	add r6, r2, #0
	bl FUN_0204E62C
	add r4, r0, #0
	add r0, r7, #0
	bl FUN_0204E664
	add r5, r0, #0
	add r0, r7, #0
	bl FUN_0204E6CC
	str r0, [sp, #4]
	add r0, r7, #0
	bl FUN_0204E544
	add r0, r7, #0
	bl FUN_0204E598
	sub r0, r5, r0
	beq _02246B38
	add r0, r4, #1
	str r0, [sp, #0x10]
	sub r0, r4, #1
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	str r5, [sp]
	b _02246B44
_02246B38:
	add r0, r5, #1
	str r0, [sp, #0xc]
	sub r0, r5, #1
	str r0, [sp]
	str r4, [sp, #0x10]
	str r4, [sp, #8]
_02246B44:
	add r0, sp, #0x14
	strb r7, [r0]
	ldrb r1, [r6]
	cmp r1, #0
	bne _02246B52
	mov r1, #0
	b _02246B54
_02246B52:
	mov r1, #5
_02246B54:
	strb r1, [r0, #1]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_022453E8
	ldrb r1, [r6]
	cmp r1, #0
	bne _02246B68
	cmp r0, #0xff
	bne _02246BFE
_02246B68:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _02246B7C
	mov r1, #6
	add r0, sp, #0x14
	strb r1, [r0, #1]
	b _02246BFE
_02246B7C:
	ldr r0, _02246C0C ; =0x022513EC
	add r1, r4, #0
	ldr r0, [r0]
	add r2, r5, #0
	ldr r0, [r0]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _02246BFE
	ldr r0, _02246C0C ; =0x022513EC
	ldr r1, [sp, #0x10]
	ldr r0, [r0]
	ldr r2, [sp, #0xc]
	ldr r0, [r0]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _02246BFE
	ldr r0, _02246C0C ; =0x022513EC
	ldr r1, [sp, #8]
	ldr r0, [r0]
	ldr r2, [sp]
	ldr r0, [r0]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _02246BFE
	ldrb r0, [r6]
	cmp r0, #0
	bne _02246BC0
	mov r1, #1
	add r0, sp, #0x14
	strb r1, [r0, #1]
	b _02246BFE
_02246BC0:
	ldr r2, [sp, #4]
	add r0, r4, #0
	add r1, r5, #0
	mov r3, #0x10
	bl MOD18_02245F70
	mov r0, #0x10
	add r1, r7, #0
	bl MOD18_02245528
	cmp r0, #0
	beq _02246BFE
	ldrb r0, [r6]
	cmp r0, #1
	beq _02246BE8
	cmp r0, #2
	beq _02246BF8
	cmp r0, #3
	beq _02246BF0
	b _02246BFE
_02246BE8:
	mov r1, #2
	add r0, sp, #0x14
	strb r1, [r0, #1]
	b _02246BFE
_02246BF0:
	mov r1, #3
	add r0, sp, #0x14
	strb r1, [r0, #1]
	b _02246BFE
_02246BF8:
	mov r1, #4
	add r0, sp, #0x14
	strb r1, [r0, #1]
_02246BFE:
	mov r0, #0x57
	add r1, sp, #0x14
	bl FUN_02030C4C
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246C0C: .word MOD18_022513EC
	thumb_func_end MOD18_02246AFC

	thumb_func_start MOD18_02246C10
MOD18_02246C10: ; 0x02246C10
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #0x10
	bl MOD18_02246430
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02246C28
	mov r1, #4
	bl FUN_020021EC
_02246C28:
	add r0, r5, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	bl MOD18_0223E6A0
	bl FUN_0204F7FC
	bl MOD18_022479A0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_02246C10

	thumb_func_start MOD18_02246C44
MOD18_02246C44: ; 0x02246C44
	push {r4, lr}
	bl MOD18_02247984
	mov r0, #4
	mov r1, #0x14
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4, #0xc]
	bl FUN_02031190
	strb r0, [r4, #0x10]
	ldr r0, _02246C88 ; =0x022513EC
	add r1, r4, #0
	ldr r0, [r0]
	mov r2, #0x64
	ldr r0, [r0]
	str r0, [r4]
	ldr r0, _02246C8C ; =MOD18_02246898
	bl FUN_0200CA44
	str r0, [r4, #4]
	ldr r1, [r4, #4]
	ldr r2, _02246C90 ; =MOD18_02246C10
	add r0, r4, #0
	bl MOD18_0223E688
	pop {r4, pc}
	nop
_02246C88: .word MOD18_022513EC
_02246C8C: .word MOD18_02246898
_02246C90: .word MOD18_02246C10
	thumb_func_end MOD18_02246C44

	thumb_func_start MOD18_02246C94
MOD18_02246C94: ; 0x02246C94
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, _02246D94 ; =0x022513EC
	add r5, r2, #0
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	ldrb r4, [r5]
	add r7, r0, #0
	bl FUN_02031190
	cmp r4, r0
	bne _02246D92
	ldrb r0, [r5, #1]
	cmp r0, #0
	bne _02246CD0
	bl FUN_0204F7E4
	bl MOD18_0223D638
	ldr r3, _02246D98 ; =MOD18_022453E0
	mov r1, #0x36
	mov r2, #1
	bl MOD18_0224DCB8
	bl MOD18_022479A0
	pop {r3, r4, r5, r6, r7, pc}
_02246CD0:
	cmp r0, #1
	bne _02246CDA
	bl MOD18_02246C44
	pop {r3, r4, r5, r6, r7, pc}
_02246CDA:
	cmp r0, #6
	bne _02246CF6
	bl FUN_0204F7E4
	bl MOD18_0223D638
	ldr r3, _02246D98 ; =MOD18_022453E0
	mov r1, #0x4a
	mov r2, #1
	bl MOD18_0224DCB8
	bl MOD18_022479A0
	pop {r3, r4, r5, r6, r7, pc}
_02246CF6:
	cmp r0, #5
	bne _02246D16
	bl FUN_0204F7E4
	bl MOD18_0223D638
	ldr r3, _02246D98 ; =MOD18_022453E0
	mov r1, #0x58
	mov r2, #1
	bl MOD18_0224DCB8
	bl FUN_0204FD24
	bl MOD18_022479A0
	pop {r3, r4, r5, r6, r7, pc}
_02246D16:
	add r0, #0xfe
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #2
	bhi _02246D92
	add r0, r4, #0
	bl FUN_0204E4D4
	add r4, r0, #0
	ldrb r0, [r5]
	bl FUN_0204E50C
	add r6, r0, #0
	ldrb r0, [r5]
	bl FUN_0204E69C
	str r0, [sp]
	ldrb r3, [r5]
	ldr r2, [sp]
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_02245F70
	ldr r2, [sp]
	add r0, r4, #0
	add r1, r6, #0
	mov r3, #0x10
	bl MOD18_02245F70
	ldrb r0, [r5, #1]
	cmp r0, #3
	bne _02246D5C
	add r0, r7, #0
	bl FUN_02026C38
_02246D5C:
	ldrb r0, [r5, #1]
	add r0, #0xfd
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _02246D92
	mov r0, #0xb
	bl FUN_0202916C
	add r1, r0, #0
	ldr r0, _02246D94 ; =0x022513EC
	mov r2, #1
	ldr r0, [r0]
	ldr r0, [r0]
	add r0, #0x98
	ldr r0, [r0]
	bl FUN_02028AD4
	ldr r0, _02246D94 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x23
	bl FUN_0202A170
_02246D92:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02246D94: .word MOD18_022513EC
_02246D98: .word MOD18_022453E0
	thumb_func_end MOD18_02246C94

	thumb_func_start MOD18_02246D9C
MOD18_02246D9C: ; 0x02246D9C
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, _02246E98 ; =0x022513EC
	add r6, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	bne _02246DAC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02246DAC:
	mov r5, #0
_02246DAE:
	ldr r0, [r4]
	ldr r1, _02246E9C ; =0x0000137B
	add r0, r0, r5
	ldrb r7, [r0, r1]
	cmp r7, #0xff
	beq _02246DE4
	mov r2, #0xff
	strb r2, [r0, r1]
	cmp r5, r7
	beq _02246DE4
	add r0, r5, #0
	bl FUN_0202DFA4
	str r0, [sp]
	add r0, r7, #0
	bl FUN_0202DFA4
	add r1, r0, #0
	ldr r0, [sp]
	mov r2, #0x68
	add r3, r6, #0
	bl MOD18_0223D6D8
	cmp r0, #0
	beq _02246DE4
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02246DE4:
	ldr r0, [r4]
	add r1, r0, r5
	ldr r0, _02246EA0 ; =0x0000134B
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _02246E22
	add r0, r5, #0
	bl FUN_0202DFA4
	add r7, r0, #0
	ldr r0, [r4]
	add r1, r0, r5
	ldr r0, _02246EA0 ; =0x0000134B
	ldrb r0, [r1, r0]
	bl FUN_0202DFA4
	add r1, r0, #0
	ldr r0, [r4]
	mov r2, #0xff
	add r3, r0, r5
	ldr r0, _02246EA0 ; =0x0000134B
	strb r2, [r3, r0]
	add r0, r7, #0
	mov r2, #0x6c
	add r3, r6, #0
	bl MOD18_0223D6D8
	cmp r0, #0
	beq _02246E22
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02246E22:
	ldr r0, [r4]
	add r1, r0, r5
	ldr r0, _02246EA4 ; =0x0000135B
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _02246E52
	add r0, r5, #0
	bl FUN_0202DFA4
	ldr r2, _02246E98 ; =0x022513EC
	mov r1, #0xff
	ldr r2, [r2]
	add r3, r2, r5
	ldr r2, _02246EA4 ; =0x0000135B
	strb r1, [r3, r2]
	mov r1, #0
	mov r2, #0x6d
	add r3, r6, #0
	bl MOD18_0223D744
	cmp r0, #0
	beq _02246E92
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02246E52:
	ldr r0, _02246EA8 ; =0x00001353
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	beq _02246E8C
	add r0, r5, #0
	bl FUN_0202DFA4
	add r7, r0, #0
	ldr r0, [r4]
	add r1, r0, r5
	ldr r0, _02246EA8 ; =0x00001353
	ldrb r0, [r1, r0]
	bl FUN_0202DFA4
	add r1, r0, #0
	ldr r0, [r4]
	mov r2, #0xff
	add r3, r0, r5
	ldr r0, _02246EA8 ; =0x00001353
	strb r2, [r3, r0]
	add r0, r7, #0
	mov r2, #0x6e
	add r3, r6, #0
	bl MOD18_0223D6D8
	cmp r0, #0
	beq _02246E8C
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02246E8C:
	add r5, r5, #1
	cmp r5, #8
	blt _02246DAE
_02246E92:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02246E98: .word MOD18_022513EC
_02246E9C: .word 0x0000137B
_02246EA0: .word 0x0000134B
_02246EA4: .word 0x0000135B
_02246EA8: .word 0x00001353
	thumb_func_end MOD18_02246D9C

	thumb_func_start MOD18_02246EAC
MOD18_02246EAC: ; 0x02246EAC
	ldr r0, _02246EC8 ; =0x022513EC
	ldr r1, [r0]
	cmp r1, #0
	beq _02246EC2
	mov r0, #0xa
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02246EC2
	add r0, r0, #2
	bx lr
_02246EC2:
	mov r0, #0
	bx lr
	nop
_02246EC8: .word MOD18_022513EC
	thumb_func_end MOD18_02246EAC

	thumb_func_start MOD18_02246ECC
MOD18_02246ECC: ; 0x02246ECC
	ldr r0, _02246EEC ; =0x022513EC
	ldr r1, [r0]
	cmp r1, #0
	beq _02246EE6
	mov r0, #0xa
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02246EE6
	ldrb r1, [r0]
	ldr r0, _02246EF0 ; =0x02251238
	ldrb r0, [r0, r1]
	bx lr
_02246EE6:
	mov r0, #0
	bx lr
	nop
_02246EEC: .word MOD18_022513EC
_02246EF0: .word MOD18_02251238
	thumb_func_end MOD18_02246ECC

	thumb_func_start MOD18_02246EF4
MOD18_02246EF4: ; 0x02246EF4
	ldr r0, _02246F14 ; =0x022513EC
	ldr r1, [r0]
	cmp r1, #0
	beq _02246F0E
	mov r0, #0xa
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	cmp r0, #0
	beq _02246F0E
	ldrb r1, [r0]
	ldr r0, _02246F18 ; =0x0225124C
	ldrb r0, [r0, r1]
	bx lr
_02246F0E:
	mov r0, #0
	bx lr
	nop
_02246F14: .word MOD18_022513EC
_02246F18: .word MOD18_0225124C
	thumb_func_end MOD18_02246EF4

	thumb_func_start MOD18_02246F1C
MOD18_02246F1C: ; 0x02246F1C
	push {r4, r5, r6, r7}
	add r7, r0, #0
	ldr r0, _02246FA4 ; =0x022513EC
	add r5, r1, #0
	ldr r0, [r0]
	mov ip, r0
	cmp r0, #0
	bne _02246F32
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_02246F32:
	cmp r5, #0x40
	blt _02246F3C
	mov r0, #1
	pop {r4, r5, r6, r7}
	bx lr
_02246F3C:
	asr r0, r7, #4
	asr r1, r5, #4
	lsr r0, r0, #0x1b
	lsr r1, r1, #0x1b
	add r0, r7, r0
	add r1, r5, r1
	ldr r3, _02246FA8 ; =0x02251238
	ldr r4, _02246FAC ; =0x0225124C
	asr r0, r0, #5
	asr r1, r1, #5
	mov r2, #0
_02246F52:
	ldrb r6, [r3]
	cmp r0, r6
	bne _02246F92
	ldrb r6, [r4]
	cmp r1, r6
	bne _02246F92
	lsr r4, r7, #0x1f
	lsl r3, r7, #0x1b
	sub r3, r3, r4
	mov r1, #0x1b
	ror r3, r1
	mov r0, #1
	add r4, r4, r3
	add r3, r0, #0
	lsl r3, r4
	lsl r4, r2, #7
	mov r2, ip
	add r2, r2, r4
	lsr r6, r5, #0x1f
	lsl r4, r5, #0x1b
	sub r4, r4, r6
	ror r4, r1
	add r1, r6, r4
	lsl r1, r1, #2
	add r2, r2, r1
	ldr r1, _02246FB0 ; =0x00000A04
	ldr r1, [r2, r1]
	tst r1, r3
	bne _02246F9E
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
_02246F92:
	add r2, r2, #1
	add r3, r3, #1
	add r4, r4, #1
	cmp r2, #0x11
	blt _02246F52
	mov r0, #1
_02246F9E:
	pop {r4, r5, r6, r7}
	bx lr
	nop
_02246FA4: .word MOD18_022513EC
_02246FA8: .word MOD18_02251238
_02246FAC: .word MOD18_0225124C
_02246FB0: .word 0x00000A04
	thumb_func_end MOD18_02246F1C

	thumb_func_start MOD18_02246FB4
MOD18_02246FB4: ; 0x02246FB4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0xb0
	ldr r0, _02247108 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CA8
	str r0, [sp, #0xc]
	ldr r0, _02247108 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r4, r0, #0
	mov r0, #0
	bl FUN_0204E62C
	str r0, [sp, #8]
	mov r0, #0
	bl FUN_0204E664
	str r0, [sp, #4]
	mov r0, #0
	bl FUN_0204E6CC
	str r0, [sp]
	mov r0, #0x10
	str r0, [sp, #0x28]
	mov r0, #0xc
	str r0, [sp, #0x2c]
	ldr r0, _02247108 ; =0x022513EC
	ldr r0, [r0]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205EDD8
	ldr r0, [sp, #0xc]
	bl FUN_020266E0
	add r0, r4, #0
	bl FUN_02025F44
	add r0, sp, #0x10
	bl FUN_020312BC
	mov r4, #0
_0224701C:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	bl _ll_mul
	ldr r2, [sp, #0x20]
	ldr r6, [sp, #0x24]
	add r7, r2, r0
	adc r6, r1
	mov r1, #0
	add r0, r6, #0
	mov r2, #5
	mov r3, #0
	str r7, [sp, #0x10]
	str r6, [sp, #0x14]
	bl _ll_mul
	cmp r1, #2
	bge _0224704A
	lsl r5, r1, #1
	add r5, #0xa
	b _02247050
_0224704A:
	sub r0, r1, #3
	lsl r5, r0, #1
	add r5, #0x12
_02247050:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	add r2, r7, #0
	add r3, r6, #0
	bl _ll_mul
	ldr r2, [sp, #0x20]
	ldr r3, [sp, #0x24]
	add r0, r2, r0
	adc r3, r1
	str r0, [sp, #0x10]
	str r3, [sp, #0x14]
	add r0, r3, #0
	mov r1, #0
	mov r2, #6
	mov r3, #0
	bl _ll_mul
	lsl r6, r1, #1
	add r6, #0xc
	mov r0, #1
	mov r1, #0
	cmp r4, #0
	blt _0224709A
	add r2, sp, #0x28
_02247082:
	ldr r3, [r2]
	cmp r5, r3
	bne _02247092
	ldr r3, [r2, #4]
	cmp r6, r3
	bne _02247092
	mov r0, #0
	b _0224709A
_02247092:
	add r1, r1, #1
	add r2, #8
	cmp r1, r4
	ble _02247082
_0224709A:
	cmp r0, #0
	bne _022470A2
	sub r4, r4, #1
	b _022470BA
_022470A2:
	add r1, r4, #0
	ldr r0, [sp, #0xc]
	add r1, #0x10
	add r2, r5, #0
	add r3, r6, #0
	bl FUN_02026778
	add r1, sp, #0x28
	lsl r0, r4, #3
	add r0, r1, r0
	str r5, [r0, #8]
	str r6, [r0, #0xc]
_022470BA:
	add r4, r4, #1
	cmp r4, #0x10
	blt _0224701C
	ldr r0, _02247108 ; =0x022513EC
	mov r2, #0x22
	ldr r1, [r0]
	ldr r0, _0224710C ; =0x00000A04
	lsl r2, r2, #6
	add r0, r1, r0
	mov r1, #0xff
	bl MI_CpuFill8
	ldr r0, [sp]
	bl FUN_0204F610
	add r3, r0, #0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #8]
	ldr r2, [sp, #4]
	bl FUN_02026C68
	ldr r1, _02247108 ; =0x022513EC
	ldr r0, [sp, #0xc]
	ldr r2, [r1]
	ldr r1, _02247110 ; =0x0000096A
	add r1, r2, r1
	mov r2, #0x94
	bl MI_CpuCopy8
	ldr r1, _02247108 ; =0x022513EC
	ldr r0, [sp, #0xc]
	ldr r2, [r1]
	ldr r1, _02247114 ; =0x00001204
	add r1, r2, r1
	bl MOD18_02245128
	add sp, #0xb0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02247108: .word MOD18_022513EC
_0224710C: .word 0x00000A04
_02247110: .word 0x0000096A
_02247114: .word 0x00001204
	thumb_func_end MOD18_02246FB4

	thumb_func_start MOD18_02247118
MOD18_02247118: ; 0x02247118
	push {r4, lr}
	add r4, r0, #0
	bl MOD18_0223D668
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r4, pc}
	thumb_func_end MOD18_02247118

	thumb_func_start MOD18_0224712C
MOD18_0224712C: ; 0x0224712C
	push {r3, lr}
	bl MOD18_0223D668
	bl MOD18_0224DD94
	pop {r3, pc}
	thumb_func_end MOD18_0224712C

	thumb_func_start MOD18_02247138
MOD18_02247138: ; 0x02247138
	push {r4, lr}
	add r4, r0, #0
	bl MOD18_0223D668
	mov r1, #0
	add r2, r4, #0
	bl MOD18_0224DF18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02247138

	thumb_func_start MOD18_0224714C
MOD18_0224714C: ; 0x0224714C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD18_0223D668
	add r1, r4, #0
	add r2, r5, #0
	bl MOD18_0224DEA4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224714C

	thumb_func_start MOD18_02247160
MOD18_02247160: ; 0x02247160
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	str r1, [sp]
	str r2, [sp, #4]
	mov r4, #0
_0224716C:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_020267C4
	str r0, [sp, #8]
	cmp r0, #0
	beq _022471C4
	cmp r4, #0
	beq _022471C4
	cmp r4, #0x10
	bge _022471C4
	bl FUN_0204CAA0
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026810
	add r7, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026840
	ldr r1, [sp]
	ldr r2, [sp, #4]
	sub r1, r1, r7
	sub r2, r2, r0
	cmp r1, #0
	blt _022471C4
	cmp r1, #2
	bgt _022471C4
	cmp r2, #0
	blt _022471C4
	cmp r2, #2
	bgt _022471C4
	lsl r0, r2, #1
	add r2, r2, r0
	add r0, r6, r1
	ldrb r0, [r2, r0]
	cmp r0, #0
	beq _022471C4
	ldr r0, [sp, #8]
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_022471C4:
	add r4, r4, #1
	cmp r4, #0x20
	blt _0224716C
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD18_02247160

	thumb_func_start MOD18_022471D0
MOD18_022471D0: ; 0x022471D0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	ldrh r4, [r1]
	ldrh r6, [r1, #2]
	add r5, r0, #0
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_02246F1C
	cmp r0, #0
	bne _0224723C
	add r0, sp, #0
	strb r5, [r0]
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_02244DE8
	ldr r1, _02247244 ; =0x022513EC
	mov r3, #0x1b
	ldr r2, [r1]
	mov r1, #0x96
	add r2, #0xa
	mul r1, r0
	add r0, r2, r1
	lsr r2, r4, #0x1f
	lsl r1, r4, #0x1b
	sub r1, r1, r2
	ror r1, r3
	add r1, r2, r1
	lsr r4, r6, #0x1f
	lsl r2, r6, #0x1b
	sub r2, r2, r4
	ror r2, r3
	add r2, r4, r2
	bl MOD18_02247160
	bl FUN_0204CAF0
	add r1, sp, #0
	strb r0, [r1, #1]
	ldrb r0, [r1, #1]
	cmp r0, #0
	beq _0224723C
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	mov r0, #0x3c
	add r1, sp, #0
	bl FUN_02030C4C
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0224723C:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02247244: .word MOD18_022513EC
	thumb_func_end MOD18_022471D0

	thumb_func_start MOD18_02247248
MOD18_02247248: ; 0x02247248
	push {r3, r4, r5, lr}
	ldr r0, _02247274 ; =0x022513EC
	add r5, r2, #0
	ldr r1, [r0]
	mov r0, #0xa
	lsl r0, r0, #8
	ldr r0, [r1, r0]
	add r0, r0, #2
	bl FUN_02026CC0
	add r4, r0, #0
	bl FUN_02031190
	ldrb r1, [r5]
	cmp r1, r0
	bne _02247270
	ldrb r1, [r5, #1]
	add r0, r4, #0
	bl MOD18_0224D79C
_02247270:
	pop {r3, r4, r5, pc}
	nop
_02247274: .word MOD18_022513EC
	thumb_func_end MOD18_02247248

	thumb_func_start MOD18_02247278
MOD18_02247278: ; 0x02247278
	mov r0, #2
	bx lr
	thumb_func_end MOD18_02247278

	thumb_func_start MOD18_0224727C
MOD18_0224727C: ; 0x0224727C
	ldr r2, _0224728C ; =0x022513EC
	ldr r2, [r2]
	cmp r2, #0
	beq _0224728A
	add r2, r2, r0
	ldr r0, _02247290 ; =0x0000134B
	strb r1, [r2, r0]
_0224728A:
	bx lr
	.align 2, 0
_0224728C: .word MOD18_022513EC
_02247290: .word 0x0000134B
	thumb_func_end MOD18_0224727C

	thumb_func_start MOD18_02247294
MOD18_02247294: ; 0x02247294
	ldr r2, _022472A4 ; =0x022513EC
	ldr r2, [r2]
	cmp r2, #0
	beq _022472A2
	add r2, r2, r0
	ldr r0, _022472A8 ; =0x00001353
	strb r1, [r2, r0]
_022472A2:
	bx lr
	.align 2, 0
_022472A4: .word MOD18_022513EC
_022472A8: .word 0x00001353
	thumb_func_end MOD18_02247294

	thumb_func_start MOD18_022472AC
MOD18_022472AC: ; 0x022472AC
	ldr r1, _022472C0 ; =0x022513EC
	ldr r1, [r1]
	cmp r1, #0
	beq _022472BC
	add r1, r1, r0
	ldr r0, _022472C4 ; =0x0000135B
	mov r2, #1
	strb r2, [r1, r0]
_022472BC:
	bx lr
	nop
_022472C0: .word MOD18_022513EC
_022472C4: .word 0x0000135B
	thumb_func_end MOD18_022472AC

	thumb_func_start MOD18_022472C8
MOD18_022472C8: ; 0x022472C8
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	ldr r0, _0224731C ; =0x022513EC
	mov r1, #0
	ldr r0, [r0]
	ldr r0, [r0]
	add r0, #0xa0
	ldr r0, [r0]
	bl MOD05_021E7ED0
	add r1, r0, #0
	add r0, sp, #8
	bl MOD05_021E7EA0
	ldr r1, _0224731C ; =0x022513EC
	mov r0, #0
	ldr r1, [r1]
	ldr r1, [r1]
	add r1, #0xa0
	ldr r1, [r1]
	bl MOD05_021E7C80
	ldr r0, _0224731C ; =0x022513EC
	ldr r2, _02247320 ; =0x0000013D
	ldr r0, [r0]
	ldr r1, [r0]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r1, #0x4c]
	str r0, [sp, #4]
	add r0, r1, #0
	ldrb r3, [r4, #5]
	add r0, #0xa0
	ldr r0, [r0]
	add r2, r3, r2
	ldr r1, [r1, #0x2c]
	add r3, sp, #8
	bl MOD05_021E7FBC
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_0224731C: .word MOD18_022513EC
_02247320: .word 0x0000013D
	thumb_func_end MOD18_022472C8

	thumb_func_start MOD18_02247324
MOD18_02247324: ; 0x02247324
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	bl FreeToHeap
	add r0, r4, #0
	bl FUN_0200CAB4
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02247324

	thumb_func_start MOD18_02247338
MOD18_02247338: ; 0x02247338
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #4
	bhi _02247406
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02247352: ; jump table
	.short _0224735C - _02247352 - 2 ; case 0
	.short _0224737C - _02247352 - 2 ; case 1
	.short _022473AA - _02247352 - 2 ; case 2
	.short _022473DA - _02247352 - 2 ; case 3
	.short _022473F6 - _02247352 - 2 ; case 4
_0224735C:
	bl FUN_0204F7E4
	bl MOD18_0223D648
	mov r2, #0
	mov r1, #7
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224740C ; =0x000005E3
	bl FUN_020054C8
	mov r0, #1
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, pc}
_0224737C:
	bl MOD18_0223D648
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02247406
	ldr r0, _02247410 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02247406
	bl MOD18_0223D648
	ldrb r1, [r4, #5]
	mov r2, #0
	add r3, r2, #0
	add r1, #0xe
	bl MOD18_0224DCB8
	mov r0, #2
	add sp, #0xc
	str r0, [r4]
	pop {r4, r5, pc}
_022473AA:
	bl MOD18_0223D648
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02247406
	ldr r0, _02247410 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _02247406
	add r0, r4, #0
	bl MOD18_022472C8
	mov r0, #4
	str r0, [r4]
	bl MOD18_0223D648
	bl MOD18_0224DD94
	bl FUN_0204F7FC
	add sp, #0xc
	pop {r4, r5, pc}
_022473DA:
	mov r0, #6
	str r0, [sp]
	mov r1, #0
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	add sp, #0xc
	pop {r4, r5, pc}
_022473F6:
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	bl MOD18_0223E6A0
_02247406:
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_0224740C: .word 0x000005E3
_02247410: .word gMain
	thumb_func_end MOD18_02247338

	thumb_func_start MOD18_02247414
MOD18_02247414: ; 0x02247414
	push {r3, lr}
	add r1, sp, #0
	strb r0, [r1]
	ldrb r0, [r2]
	strb r0, [r1, #1]
	mov r0, #0x61
	add r1, sp, #0
	bl FUN_02030C4C
	pop {r3, pc}
	thumb_func_end MOD18_02247414

	thumb_func_start MOD18_02247428
MOD18_02247428: ; 0x02247428
	push {r3, r4, r5, lr}
	add r5, r2, #0
	bl FUN_02031190
	ldrb r1, [r5]
	cmp r1, r0
	bne _02247464
	mov r0, #0xb
	mov r1, #8
	bl AllocFromHeap
	mov r1, #0
	mov r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4]
	ldrb r0, [r5, #1]
	add r1, r4, #0
	mov r2, #0x64
	strb r0, [r4, #5]
	ldr r0, _02247468 ; =MOD18_02247338
	bl FUN_0200CA44
	add r1, r0, #0
	ldr r2, _0224746C ; =MOD18_02247324
	add r0, r4, #0
	bl MOD18_0223E688
_02247464:
	pop {r3, r4, r5, pc}
	nop
_02247468: .word MOD18_02247338
_0224746C: .word MOD18_02247324
	thumb_func_end MOD18_02247428

	thumb_func_start MOD18_02247470
MOD18_02247470: ; 0x02247470
	mov r0, #2
	bx lr
	thumb_func_end MOD18_02247470

	thumb_func_start MOD18_02247474
MOD18_02247474: ; 0x02247474
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r7, r1, #0
	str r2, [sp]
	mov r4, #0
_02247480:
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_020267C4
	str r0, [sp, #4]
	cmp r0, #0
	beq _022474C0
	cmp r4, #0
	beq _022474C0
	cmp r4, #0x10
	bge _022474C0
	bl FUN_0204CAA0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026810
	add r6, r0, #0
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02026840
	ldr r1, [sp]
	sub r2, r7, r6
	sub r0, r1, r0
	cmp r2, #0
	bne _022474C0
	cmp r0, #0
	bne _022474C0
	ldr r0, [sp, #4]
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_022474C0:
	add r4, r4, #1
	cmp r4, #0x20
	blt _02247480
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_02247474

	thumb_func_start MOD18_022474CC
MOD18_022474CC: ; 0x022474CC
	sub r0, #0x38
	cmp r0, #0xf
	bhi _0224753E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_022474DE: ; jump table
	.short _022474FE - _022474DE - 2 ; case 0
	.short _02247502 - _022474DE - 2 ; case 1
	.short _02247506 - _022474DE - 2 ; case 2
	.short _0224750A - _022474DE - 2 ; case 3
	.short _0224750E - _022474DE - 2 ; case 4
	.short _02247512 - _022474DE - 2 ; case 5
	.short _02247516 - _022474DE - 2 ; case 6
	.short _0224751A - _022474DE - 2 ; case 7
	.short _0224751E - _022474DE - 2 ; case 8
	.short _02247522 - _022474DE - 2 ; case 9
	.short _02247526 - _022474DE - 2 ; case 10
	.short _0224752A - _022474DE - 2 ; case 11
	.short _0224752E - _022474DE - 2 ; case 12
	.short _02247532 - _022474DE - 2 ; case 13
	.short _02247536 - _022474DE - 2 ; case 14
	.short _0224753A - _022474DE - 2 ; case 15
_022474FE:
	mov r0, #0xb
	bx lr
_02247502:
	mov r0, #0xc
	bx lr
_02247506:
	mov r0, #0x12
	bx lr
_0224750A:
	mov r0, #0x13
	bx lr
_0224750E:
	mov r0, #0x14
	bx lr
_02247512:
	mov r0, #0x15
	bx lr
_02247516:
	mov r0, #0x16
	bx lr
_0224751A:
	mov r0, #0x17
	bx lr
_0224751E:
	mov r0, #0x18
	bx lr
_02247522:
	mov r0, #0x19
	bx lr
_02247526:
	mov r0, #0x1a
	bx lr
_0224752A:
	mov r0, #0x1b
	bx lr
_0224752E:
	mov r0, #0x1c
	bx lr
_02247532:
	mov r0, #0x1d
	bx lr
_02247536:
	mov r0, #0x1e
	bx lr
_0224753A:
	mov r0, #0x1f
	bx lr
_0224753E:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end MOD18_022474CC

	thumb_func_start MOD18_02247544
MOD18_02247544: ; 0x02247544
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	bl FUN_0204E544
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0204E598
	add r4, r0, #0
	add r0, r5, #0
	bl FUN_0204E6CC
	str r0, [sp, #8]
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _02247572
	add sp, #0xc
	mov r0, #0
	pop {r4, r5, r6, r7, pc}
_02247572:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_02246F1C
	cmp r0, #1
	bne _022475EA
	ldr r0, _022475F0 ; =0x022513EC
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _022475F4 ; =0x00001383
	ldrb r0, [r1, r0]
	cmp r0, #0
	bne _022475EA
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_02244DE8
	ldr r1, _022475F0 ; =0x022513EC
	lsr r3, r6, #0x1f
	ldr r2, [r1]
	mov r1, #0x96
	add r2, #0xa
	mul r1, r0
	add r0, r2, r1
	lsl r2, r6, #0x1b
	sub r2, r2, r3
	mov r1, #0x1b
	ror r2, r1
	add r1, r3, r2
	lsr r3, r4, #0x1f
	lsl r7, r4, #0x1b
	sub r7, r7, r3
	mov r2, #0x1b
	ror r7, r2
	add r2, r3, r7
	bl MOD18_02247474
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl MOD18_022474CC
	add r2, r0, #0
	beq _022475EA
	ldr r1, _022475F0 ; =0x022513EC
	mov r0, #1
	ldr r1, [r1]
	add r3, r1, r5
	ldr r1, _022475F4 ; =0x00001383
	strb r0, [r3, r1]
	ldr r0, [sp, #8]
	str r4, [sp]
	str r0, [sp, #4]
	add r0, r5, #0
	mov r1, #0xff
	add r3, r6, #0
	bl MOD18_0223F858
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_022475EA:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022475F0: .word MOD18_022513EC
_022475F4: .word 0x00001383
	thumb_func_end MOD18_02247544

	thumb_func_start MOD18_022475F8
MOD18_022475F8: ; 0x022475F8
	ldr r1, _0224760C ; =0x022513EC
	ldr r1, [r1]
	cmp r1, #0
	beq _02247608
	add r1, r1, r0
	ldr r0, _02247610 ; =0x00001383
	mov r2, #0
	strb r2, [r1, r0]
_02247608:
	mov r0, #0
	bx lr
	.align 2, 0
_0224760C: .word MOD18_022513EC
_02247610: .word 0x00001383
	thumb_func_end MOD18_022475F8

	thumb_func_start MOD18_02247614
MOD18_02247614: ; 0x02247614
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r0, sp, #4
	mov r1, #0
	mov r2, #8
	bl MI_CpuFill8
	mov r4, #0
	add r5, sp, #4
_02247626:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	beq _022476A2
	add r0, r4, #0
	bl FUN_0204E544
	str r0, [sp]
	add r0, r4, #0
	bl FUN_0204E598
	add r7, r0, #0
	ldr r1, [sp]
	ldr r0, _02247714 ; =0x0000FFFF
	cmp r1, r0
	bne _0224764E
	cmp r7, r0
	beq _022476A2
_0224764E:
	ldr r0, [sp]
	add r1, r7, #0
	bl MOD18_02244DE8
	add r6, r0, #0
	cmp r4, r6
	beq _022476A2
	cmp r6, #0x10
	beq _022476A2
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	bl FUN_02030E7C
	cmp r0, #0
	bne _022476A2
	ldr r0, _02247718 ; =0x022513EC
	ldr r1, _0224771C ; =0x0000136B
	ldr r0, [r0]
	add r0, r0, r4
	ldrb r1, [r0, r1]
	cmp r1, #0xff
	bne _022476A2
	ldr r1, _02247720 ; =0x00001373
	ldrb r0, [r0, r1]
	cmp r0, #0xff
	bne _022476A2
	ldr r0, [sp]
	add r1, r7, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _022476A2
	ldrb r0, [r5]
	cmp r0, #0
	bne _022476A2
	add r0, r6, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD18_022455D0
	mov r0, #1
	strb r0, [r5]
_022476A2:
	add r4, r4, #1
	add r5, r5, #1
	cmp r4, #8
	blt _02247626
	bl FUN_02031190
	ldr r1, _02247718 ; =0x022513EC
	add r4, r0, #0
	ldr r2, [r1]
	ldr r1, _02247724 ; =0x000012E4
	ldrb r1, [r2, r1]
	cmp r1, #6
	bne _0224770E
	bl FUN_0204E544
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_0204E598
	add r5, r0, #0
	ldr r0, _02247714 ; =0x0000FFFF
	cmp r6, r0
	bne _022476D4
	cmp r5, r0
	beq _022476FC
_022476D4:
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _022476FC
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02244DE8
	add r5, sp, #4
	ldrb r1, [r5, r4]
	cmp r1, #0
	bne _022476FC
	add r1, r4, #0
	mov r2, #1
	bl MOD18_022455D0
	mov r0, #1
	strb r0, [r5, r4]
_022476FC:
	add r0, sp, #4
	ldrb r0, [r0, r4]
	cmp r0, #0
	beq _0224770E
	ldr r0, _02247718 ; =0x022513EC
	mov r2, #0
	ldr r1, [r0]
	ldr r0, _02247724 ; =0x000012E4
	strb r2, [r1, r0]
_0224770E:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02247714: .word 0x0000FFFF
_02247718: .word MOD18_022513EC
_0224771C: .word 0x0000136B
_02247720: .word 0x00001373
_02247724: .word 0x000012E4
	thumb_func_end MOD18_02247614

	thumb_func_start MOD18_02247728
MOD18_02247728: ; 0x02247728
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, _022477F8 ; =0x022513EC
	str r1, [sp, #8]
	ldr r0, [r0]
	add r1, r0, r5
	ldr r0, _022477FC ; =0x00001363
	ldrb r0, [r1, r0]
	cmp r0, #0xff
	bne _02247744
	add sp, #0x10
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02247744:
	bl FUN_02031190
	bl FUN_0204E3EC
	add r4, r0, #0
	bl FUN_02031190
	bl FUN_0204E440
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _02247774
	ldr r0, _022477F8 ; =0x022513EC
	mov r2, #0xff
	ldr r0, [r0]
	add sp, #0x10
	add r1, r0, r5
	ldr r0, _022477FC ; =0x00001363
	strb r2, [r1, r0]
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02247774:
	bl MOD18_0224D344
	bl MOD18_02248FC8
	bl MOD18_0223E6B8
	bl FUN_02031190
	mov r1, #0
	bl MOD18_0223FCE8
	ldr r0, _022477F8 ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _02247800 ; =0x000013DC
	add r1, r0, #2
	ldrh r6, [r2, r0]
	add r0, r0, #4
	ldrh r4, [r2, r1]
	ldrb r7, [r2, r0]
	cmp r6, #0
	beq _022477A2
	cmp r4, #0
	bne _022477A6
_022477A2:
	bl ErrorHandling
_022477A6:
	add r0, r7, #0
	bl FUN_02059BF4
	str r0, [sp, #0xc]
	add r0, r7, #0
	bl FUN_02059C00
	add r2, r0, #0
	ldr r0, _022477F8 ; =0x022513EC
	mov r3, #0
	ldr r1, [r0]
	ldr r0, _02247804 ; =0x000013E6
	add r2, r4, r2
	strb r3, [r1, r0]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #8]
	str r5, [sp]
	str r0, [sp, #4]
	ldr r0, _022477F8 ; =0x022513EC
	add r1, r6, r1
	ldr r0, [r0]
	add r3, r7, #0
	ldr r0, [r0]
	bl MOD18_0224686C
	bl FUN_0204FD38
	ldr r1, _022477F8 ; =0x022513EC
	mov r0, #0xa
	ldr r2, [r1]
	mov r3, #0
	lsl r0, r0, #8
	str r3, [r2, r0]
	ldr r0, [r1]
	mov r2, #0xff
	add r1, r0, r5
	ldr r0, _022477FC ; =0x00001363
	strb r2, [r1, r0]
	mov r0, #1
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022477F8: .word MOD18_022513EC
_022477FC: .word 0x00001363
_02247800: .word 0x000013DC
_02247804: .word 0x000013E6
	thumb_func_end MOD18_02247728

	thumb_func_start MOD18_02247808
MOD18_02247808: ; 0x02247808
	push {r3, lr}
	ldr r0, _02247828 ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _0224782C ; =0x000012E4
	ldrb r1, [r2, r0]
	cmp r1, #1
	bne _02247824
	mov r1, #2
	strb r1, [r2, r0]
	bl FUN_0204CF60
	mov r0, #0
	bl MOD18_02245358
_02247824:
	pop {r3, pc}
	nop
_02247828: .word MOD18_022513EC
_0224782C: .word 0x000012E4
	thumb_func_end MOD18_02247808

	thumb_func_start MOD18_02247830
MOD18_02247830: ; 0x02247830
	ldr r0, _02247844 ; =0x022513EC
	ldr r2, [r0]
	ldr r0, _02247848 ; =0x000012E4
	ldrb r1, [r2, r0]
	cmp r1, #5
	bne _02247840
	mov r1, #4
	strb r1, [r2, r0]
_02247840:
	bx lr
	nop
_02247844: .word MOD18_022513EC
_02247848: .word 0x000012E4
	thumb_func_end MOD18_02247830

	thumb_func_start MOD18_0224784C
MOD18_0224784C: ; 0x0224784C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl FUN_0204E5EC
	add r5, r0, #0
	add r0, r6, #0
	bl FUN_0204E60C
	add r4, r0, #0
	ldr r0, _022478BC ; =0x022513EC
	add r1, r5, #0
	ldr r0, [r0]
	add r2, r4, #0
	ldr r0, [r0]
	bl FUN_0204A6B4
	cmp r0, #0
	bne _0224787C
	cmp r6, #0
	beq _022478BA
	bl FUN_0202EDD8
	cmp r0, #0
	bne _022478BA
_0224787C:
	ldr r0, _022478C0 ; =0x0000FFFF
	cmp r5, r0
	bne _02247892
	cmp r4, r0
	bne _02247892
	add r0, r6, #0
	add r1, r6, #0
	mov r2, #1
	bl MOD18_022455D0
	pop {r4, r5, r6, pc}
_02247892:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	bne _022478B0
	ldr r0, _022478BC ; =0x022513EC
	add r1, r5, #0
	ldr r0, [r0]
	add r2, r4, #0
	ldr r0, [r0]
	bl FUN_0204A6B4
	cmp r0, #0
	beq _022478BA
_022478B0:
	add r0, r6, #0
	add r1, r6, #0
	mov r2, #1
	bl MOD18_022455D0
_022478BA:
	pop {r4, r5, r6, pc}
	.align 2, 0
_022478BC: .word MOD18_022513EC
_022478C0: .word 0x0000FFFF
	thumb_func_end MOD18_0224784C

	thumb_func_start MOD18_022478C4
MOD18_022478C4: ; 0x022478C4
	ldr r0, _022478D8 ; =0x022513EC
	ldr r1, [r0]
	cmp r1, #0
	beq _022478D2
	ldr r0, _022478DC ; =0x000013DC
	ldrh r0, [r1, r0]
	bx lr
_022478D2:
	mov r0, #0x48
	bx lr
	nop
_022478D8: .word MOD18_022513EC
_022478DC: .word 0x000013DC
	thumb_func_end MOD18_022478C4

	thumb_func_start MOD18_022478E0
MOD18_022478E0: ; 0x022478E0
	ldr r0, _022478F4 ; =0x022513EC
	ldr r1, [r0]
	cmp r1, #0
	beq _022478EE
	ldr r0, _022478F8 ; =0x000013DE
	ldrh r0, [r1, r0]
	bx lr
_022478EE:
	ldr r0, _022478FC ; =0x000001B5
	bx lr
	nop
_022478F4: .word MOD18_022513EC
_022478F8: .word 0x000013DE
_022478FC: .word 0x000001B5
	thumb_func_end MOD18_022478E0

	thumb_func_start MOD18_02247900
MOD18_02247900: ; 0x02247900
	ldr r0, _02247914 ; =0x022513EC
	ldr r1, [r0]
	cmp r1, #0
	beq _0224790E
	ldr r0, _02247918 ; =0x000013E0
	ldrb r0, [r1, r0]
	bx lr
_0224790E:
	mov r0, #1
	bx lr
	nop
_02247914: .word MOD18_022513EC
_02247918: .word 0x000013E0
	thumb_func_end MOD18_02247900

	thumb_func_start MOD18_0224791C
MOD18_0224791C: ; 0x0224791C
	ldr r2, _02247930 ; =0x022513EC
	ldr r2, [r2]
	cmp r2, #0
	beq _0224792C
	lsl r0, r0, #1
	add r2, r2, r0
	ldr r0, _02247934 ; =0x000013AC
	strh r1, [r2, r0]
_0224792C:
	bx lr
	nop
_02247930: .word MOD18_022513EC
_02247934: .word 0x000013AC
	thumb_func_end MOD18_0224791C

	thumb_func_start MOD18_02247938
MOD18_02247938: ; 0x02247938
	ldr r2, _0224794C ; =0x022513EC
	ldr r2, [r2]
	cmp r2, #0
	beq _02247948
	lsl r0, r0, #1
	add r2, r2, r0
	ldr r0, _02247950 ; =0x000013BC
	strh r1, [r2, r0]
_02247948:
	bx lr
	nop
_0224794C: .word MOD18_022513EC
_02247950: .word 0x000013BC
	thumb_func_end MOD18_02247938

	thumb_func_start MOD18_02247954
MOD18_02247954: ; 0x02247954
	ldr r2, _02247968 ; =0x022513EC
	ldr r2, [r2]
	cmp r2, #0
	beq _02247964
	lsl r0, r0, #1
	add r2, r2, r0
	ldr r0, _0224796C ; =0x000013CC
	strh r1, [r2, r0]
_02247964:
	bx lr
	nop
_02247968: .word MOD18_022513EC
_0224796C: .word 0x000013CC
	thumb_func_end MOD18_02247954

	thumb_func_start MOD18_02247970
MOD18_02247970: ; 0x02247970
	ldr r1, _0224797C ; =0x022513EC
	ldr r2, [r1]
	ldr r1, _02247980 ; =0x000013E5
	strb r0, [r2, r1]
	bx lr
	nop
_0224797C: .word MOD18_022513EC
_02247980: .word 0x000013E5
	thumb_func_end MOD18_02247970

	thumb_func_start MOD18_02247984
MOD18_02247984: ; 0x02247984
	push {r3, lr}
	mov r0, #1
	bl FUN_0202D380
	mov r0, #1
	bl FUN_0202D344
	mov r0, #1
	bl FUN_020318A4
	bl FUN_0202F0B8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_02247984

	thumb_func_start MOD18_022479A0
MOD18_022479A0: ; 0x022479A0
	push {r3, lr}
	mov r0, #0
	bl FUN_0202D380
	mov r0, #0
	bl FUN_0202D344
	mov r0, #0
	bl FUN_020318A4
	bl FUN_0202F0B8
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_022479A0

	thumb_func_start MOD18_022479BC
MOD18_022479BC: ; 0x022479BC
	push {r3, lr}
	ldrh r2, [r0, #0x2c]
	add r0, sp, #0
	strb r2, [r0]
	strb r1, [r0, #1]
	mov r0, #0x4a
	add r1, sp, #0
	bl FUN_020311D0
	pop {r3, pc}
	thumb_func_end MOD18_022479BC

	thumb_func_start MOD18_022479D0
MOD18_022479D0: ; 0x022479D0
	push {r3, lr}
	ldrh r2, [r0, #0x30]
	add r0, sp, #0
	strb r2, [r0]
	strb r1, [r0, #1]
	mov r0, #0x49
	add r1, sp, #0
	bl FUN_020311D0
	pop {r3, pc}
	thumb_func_end MOD18_022479D0

	thumb_func_start MOD18_022479E4
MOD18_022479E4: ; 0x022479E4
	push {r4, lr}
	add r4, r1, #0
	cmp r4, #0x88
	blt _022479FC
	ldrh r0, [r0, #0x30]
	bl FUN_0202DFA4
	bl PlayerProfile_GetTrainerGender
	cmp r0, #1
	bne _022479FC
	add r4, #0x13
_022479FC:
	bl MOD18_0223D638
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r4, pc}
	thumb_func_end MOD18_022479E4

	thumb_func_start MOD18_02247A0C
MOD18_02247A0C: ; 0x02247A0C
	push {r4, lr}
	add r4, r1, #0
	cmp r4, #0x88
	blt _02247A24
	ldrh r0, [r0, #0x2c]
	bl FUN_0202DFA4
	bl PlayerProfile_GetTrainerGender
	cmp r0, #1
	bne _02247A24
	add r4, #0x13
_02247A24:
	bl MOD18_0223D638
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r4, pc}
	thumb_func_end MOD18_02247A0C

	thumb_func_start MOD18_02247A34
MOD18_02247A34: ; 0x02247A34
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #0x21
	mov r1, #0x3c
	add r7, r2, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _02247A98 ; =0x022513F0
	mov r1, #1
	str r4, [r0, #4]
	str r7, [r4, #8]
	str r6, [r4, #0x2c]
	add r0, r4, #0
	strh r5, [r4, #0x30]
	add r0, #0x37
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x38
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x29
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x2a
	strb r1, [r0]
	add r0, r4, #0
	ldrh r1, [r4, #0x30]
	add r0, #0x28
	strb r1, [r0]
	ldr r0, _02247A9C ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	bl MOD18_022479E4
	ldr r0, _02247AA0 ; =MOD18_02248054
	ldr r2, _02247AA4 ; =0x00002710
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02247A98: .word MOD18_022513F0
_02247A9C: .word 0x000005DC
_02247AA0: .word MOD18_02248054
_02247AA4: .word 0x00002710
	thumb_func_end MOD18_02247A34

	thumb_func_start MOD18_02247AA8
MOD18_02247AA8: ; 0x02247AA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #4
	add r1, r0, #0
	bl ListMenuItems_ctor
	str r0, [r5, #0x1c]
	mov r3, #1
	str r3, [sp]
	mov r0, #0xa
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02247B50 ; =0x000002DD
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	add r1, #0xc
	ldr r0, [r0, #8]
	mov r2, #3
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _02247B54 ; =0x000003D9
	add r0, #0xc
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _02247B58 ; =0x0000023F
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	ldr r4, _02247B5C ; =0x02250548
	add r7, r0, #0
	mov r6, #0
_02247AFA:
	ldr r0, [r5, #0x1c]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	add r1, r7, #0
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r4, #8
	cmp r6, #4
	blo _02247AFA
	add r0, r7, #0
	bl DestroyMsgData
	bl MOD18_0224DAD8
	add r1, sp, #0x14
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [r5, #0x1c]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0xc
	str r0, [sp, #0x20]
	mov r3, #4
	add r0, sp, #0x14
	strh r3, [r0, #0x10]
	strh r3, [r0, #0x12]
	strh r1, [r5, #0x3a]
	add r0, sp, #0x14
	add r2, r1, #0
	bl ListMenuInit
	str r0, [r5, #0x20]
	add r5, #0xc
	add r0, r5, #0
	bl CopyWindowToVram
	bl FUN_0204F7E4
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02247B50: .word 0x000002DD
_02247B54: .word 0x000003D9
_02247B58: .word 0x0000023F
_02247B5C: .word MOD18_02250548
	thumb_func_end MOD18_02247AA8

	thumb_func_start MOD18_02247B60
MOD18_02247B60: ; 0x02247B60
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _02247B76
	mov r1, #4
	bl FUN_020021EC
	mov r0, #0
	str r0, [r4, #0x24]
_02247B76:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02247B88
	mov r1, #1
	mvn r1, r1
	bl MOD18_0224ADBC
	bl MOD18_0223E6A0
_02247B88:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247FC0
	ldr r1, [r4, #0x2c]
	cmp r1, #0
	beq _02247B9A
	mov r0, #0
	blx r1
_02247B9A:
	add r0, r4, #0
	bl FreeToHeap
	bl FUN_0204F7FC
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, _02247BB4 ; =0x022513F0
	mov r1, #0
	str r1, [r0, #4]
	pop {r3, r4, r5, pc}
	nop
_02247BB4: .word MOD18_022513F0
	thumb_func_end MOD18_02247B60

	thumb_func_start MOD18_02247BB8
MOD18_02247BB8: ; 0x02247BB8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r5, r0, #0
	mov r0, #4
	add r1, r0, #0
	bl ListMenuItems_ctor
	str r0, [r5, #0x1c]
	mov r3, #1
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02247C88 ; =0x000002AD
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	add r1, #0xc
	ldr r0, [r0, #8]
	mov r2, #3
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _02247C8C ; =0x000003D9
	add r0, #0xc
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _02247C90 ; =0x0000023E
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r6, r0, #0
	mov r4, #0
	add r7, sp, #0x14
_02247C0A:
	bl MTRandom
	mov r1, #0xc
	bl _u32_div_f
	add r2, r1, #0
	mov r1, #0
	cmp r4, #0
	ble _02247C2C
	add r3, r7, #0
_02247C1E:
	ldrb r0, [r3]
	cmp r0, r2
	beq _02247C2C
	add r1, r1, #1
	add r3, r3, #1
	cmp r1, r4
	blt _02247C1E
_02247C2C:
	cmp r1, r4
	bne _02247C3E
	strb r2, [r7, r4]
	ldr r0, [r5, #0x1c]
	add r1, r6, #0
	add r3, r2, #0
	bl ListMenuItems_AppendFromMsgData
	b _02247C40
_02247C3E:
	sub r4, r4, #1
_02247C40:
	add r4, r4, #1
	cmp r4, #4
	blt _02247C0A
	add r0, r6, #0
	bl DestroyMsgData
	ldr r4, _02247C94 ; =0x02250528
	add r3, sp, #0x18
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5, #0x1c]
	mov r1, #0
	str r0, [sp, #0x18]
	add r0, r5, #0
	add r0, #0xc
	str r0, [sp, #0x24]
	add r0, r2, #0
	strh r1, [r5, #0x3a]
	add r2, r1, #0
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x20]
	add r5, #0xc
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02247C88: .word 0x000002AD
_02247C8C: .word 0x000003D9
_02247C90: .word 0x0000023E
_02247C94: .word MOD18_02250528
	thumb_func_end MOD18_02247BB8

	thumb_func_start MOD18_02247C98
MOD18_02247C98: ; 0x02247C98
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x20]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r0, r5, #0
	bl MOD18_02248FEC
	bl FUN_020311F0
	cmp r0, #0
	beq _02247CCC
	add r0, r5, #0
	mov r1, #3
	add r0, #0x37
	strb r1, [r0]
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02247FC0
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02247CCC:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02247CDA
	add r0, r0, #1
	cmp r4, r0
	bne _02247CE0
_02247CDA:
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_02247CE0:
	ldr r0, _02247D18 ; =0x000005DC
	bl FUN_020054C8
	add r0, sp, #0
	strb r4, [r0]
	ldrh r1, [r5, #0x30]
	strb r1, [r0, #1]
	mov r1, #0
	strb r1, [r0, #2]
	mov r0, #0x4f
	add r1, sp, #0
	bl FUN_020311D0
	add r0, r5, #0
	add r0, #0x32
	strb r4, [r0]
	add r0, r5, #0
	mov r1, #0x1e
	add r0, #0x37
	strb r1, [r0]
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02247FC0
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02247D18: .word 0x000005DC
	thumb_func_end MOD18_02247C98

	thumb_func_start MOD18_02247D1C
MOD18_02247D1C: ; 0x02247D1C
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #4
	add r1, r0, #0
	bl ListMenuItems_ctor
	str r0, [r5, #0x1c]
	mov r3, #1
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02247DC8 ; =0x000002AD
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #8]
	add r1, #0xc
	ldr r0, [r0, #8]
	mov r2, #3
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _02247DCC ; =0x000003D9
	add r0, #0xc
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _02247DD0 ; =0x0000023D
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r6, r0, #0
	mov r4, #0
_02247D6C:
	add r2, r5, #0
	add r2, #0x32
	ldrb r2, [r2]
	ldr r0, [r5, #0x1c]
	add r1, r6, #0
	lsl r2, r2, #2
	add r2, r4, r2
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r4, r4, #1
	cmp r4, #4
	blt _02247D6C
	add r0, r6, #0
	bl DestroyMsgData
	ldr r4, _02247DD4 ; =0x02250528
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5, #0x1c]
	mov r1, #0
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0xc
	str r0, [sp, #0x20]
	add r0, r2, #0
	strh r1, [r5, #0x3a]
	add r2, r1, #0
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x20]
	add r5, #0xc
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02247DC8: .word 0x000002AD
_02247DCC: .word 0x000003D9
_02247DD0: .word 0x0000023D
_02247DD4: .word MOD18_02250528
	thumb_func_end MOD18_02247D1C

	thumb_func_start MOD18_02247DD8
MOD18_02247DD8: ; 0x02247DD8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x20]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r0, r5, #0
	bl MOD18_02248FEC
	bl FUN_020311F0
	cmp r0, #0
	beq _02247E0A
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02247FC0
	mov r0, #3
	add r5, #0x37
	strb r0, [r5]
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_02247E0A:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02247E18
	add r0, r0, #1
	cmp r4, r0
	bne _02247E1E
_02247E18:
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_02247E1E:
	ldr r0, _02247E9C ; =0x000005DC
	bl FUN_020054C8
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02247FC0
	add r0, r5, #0
	add r0, #0x32
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r1, r4, r0
	add r0, sp, #0
	strb r1, [r0]
	ldrh r1, [r5, #0x30]
	strb r1, [r0, #1]
	mov r1, #2
	strb r1, [r0, #2]
	mov r0, #0x4f
	add r1, sp, #0
	bl FUN_020311D0
	bl MOD18_0223D638
	add r1, sp, #0
	ldrb r1, [r1]
	bl MOD18_0224DE18
	bl MOD18_0223D638
	add r2, r5, #0
	add r2, #0x33
	ldrb r2, [r2]
	mov r1, #6
	bl MOD18_0224DE30
	add r0, r5, #0
	add r0, #0x33
	ldrb r1, [r0]
	add r0, sp, #0
	ldrb r0, [r0]
	cmp r1, r0
	bne _02247E7E
	add r0, r5, #0
	mov r1, #0x8d
	bl MOD18_022479E4
	b _02247E86
_02247E7E:
	add r0, r5, #0
	mov r1, #0x8c
	bl MOD18_022479E4
_02247E86:
	add r0, r5, #0
	mov r1, #0x24
	add r0, #0x37
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0x1b
	bl MOD18_022479D0
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_02247E9C: .word 0x000005DC
	thumb_func_end MOD18_02247DD8

	thumb_func_start MOD18_02247EA0
MOD18_02247EA0: ; 0x02247EA0
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl MOD18_0223D638
	add r5, r0, #0
	ldrh r0, [r4, #0x30]
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D638
	add r1, r4, #0
	add r1, #0x2a
	ldrb r1, [r1]
	bl MOD18_0224DE44
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0xe
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, [r4, #8]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	bl FUN_02026940
	add r4, #0x2a
	ldrb r0, [r4]
	bl MOD18_022493A4
	ldr r0, _02247EF4 ; =0x000005E3
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	nop
_02247EF4: .word 0x000005E3
	thumb_func_end MOD18_02247EA0

	thumb_func_start MOD18_02247EF8
MOD18_02247EF8: ; 0x02247EF8
	push {r4, lr}
	add r4, r1, #0
	bl MOD18_0223D638
	add r1, r4, #0
	bl MOD18_0224DE44
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0xc
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02247EF8

	thumb_func_start MOD18_02247F18
MOD18_02247F18: ; 0x02247F18
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x24]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02247F5A
	cmp r0, #0
	bne _02247F46
	ldrh r1, [r4, #0x30]
	add r0, r4, #0
	add r0, #0x28
	strb r1, [r0]
	add r1, r4, #0
	mov r0, #0x4d
	add r1, #0x28
	bl FUN_020311D0
	mov r1, #0x15
	b _02247F50
_02247F46:
	add r0, r4, #0
	mov r1, #0xb
	bl MOD18_022479E4
	mov r1, #0xf
_02247F50:
	add r0, r4, #0
	add r0, #0x37
	strb r1, [r0]
	mov r0, #0
	str r0, [r4, #0x24]
_02247F5A:
	pop {r4, pc}
	thumb_func_end MOD18_02247F18

	thumb_func_start MOD18_02247F5C
MOD18_02247F5C: ; 0x02247F5C
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x20]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r0, r5, #0
	bl MOD18_02248FEC
	bl FUN_020311F0
	cmp r0, #0
	beq _02247F7C
	mov r4, #1
	mvn r4, r4
_02247F7C:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02247F8E
	add r0, r0, #1
	cmp r4, r0
	bne _02247FA4
	mov r0, #0
	pop {r4, r5, r6, pc}
_02247F8E:
	ldr r0, _02247FBC ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD18_0224865C
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02247FC0
	b _02247FB6
_02247FA4:
	ldr r0, _02247FBC ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	blx r4
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_02247FC0
_02247FB6:
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_02247FBC: .word 0x000005DC
	thumb_func_end MOD18_02247F5C

	thumb_func_start MOD18_02247FC0
MOD18_02247FC0: ; 0x02247FC0
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #0
	beq _02247FF8
	add r0, r4, #0
	add r0, #0xc
	mov r1, #0
	bl FUN_0200CCF8
	mov r1, #0
	ldr r0, [r4, #0x20]
	add r2, r1, #0
	bl DestroyListMenu
	add r0, r4, #0
	add r0, #0xc
	bl FUN_02019570
	add r0, r4, #0
	add r0, #0xc
	bl FUN_02019178
	ldr r0, [r4, #0x1c]
	bl ListMenuItems_dtor
	mov r0, #0
	str r0, [r4, #0x1c]
_02247FF8:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02247FC0

	thumb_func_start MOD18_02247FFC
MOD18_02247FFC: ; 0x02247FFC
	push {r4, lr}
	add r4, r0, #0
	mov r1, #5
	bl MOD18_022479D0
	add r0, r4, #0
	mov r1, #7
	bl MOD18_022479E4
	mov r0, #5
	add r4, #0x37
	strb r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02247FFC

	thumb_func_start MOD18_02248018
MOD18_02248018: ; 0x02248018
	push {r4, lr}
	mov r1, #0x16
	add r4, r0, #0
	bl MOD18_022479D0
	mov r0, #0x1b
	add r4, #0x37
	strb r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02248018

	thumb_func_start MOD18_0224802C
MOD18_0224802C: ; 0x0224802C
	mov r1, #0x10
	add r0, #0x37
	strb r1, [r0]
	bx lr
	thumb_func_end MOD18_0224802C

	thumb_func_start MOD18_02248034
MOD18_02248034: ; 0x02248034
	ldr r1, _02248048 ; =0x022513F0
	ldr r2, [r1, #4]
	add r2, #0x2a
	strb r0, [r2]
	ldr r0, [r1, #4]
	mov r2, #0x12
	add r0, #0x37
	strb r2, [r0]
	bx lr
	nop
_02248048: .word MOD18_022513F0
	thumb_func_end MOD18_02248034

	thumb_func_start MOD18_0224804C
MOD18_0224804C: ; 0x0224804C
	mov r1, #0xb
	add r0, #0x37
	strb r1, [r0]
	bx lr
	thumb_func_end MOD18_0224804C

	thumb_func_start MOD18_02248054
MOD18_02248054: ; 0x02248054
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x37
	ldrb r0, [r0]
	cmp r0, #0x11
	beq _02248080
	ldrh r0, [r4, #0x30]
	bl FUN_02030E7C
	cmp r0, #0
	bne _02248080
	mov r0, #0
	str r0, [r4, #4]
	bl MOD18_0224D344
	add r0, r4, #0
	mov r1, #4
	add r0, #0x37
	strb r1, [r0]
_02248080:
	add r0, r4, #0
	add r0, #0x37
	ldrb r0, [r0]
	cmp r0, #0x29
	bhi _02248134
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02248096: ; jump table
	.short _022485F6 - _02248096 - 2 ; case 0
	.short _022480EA - _02248096 - 2 ; case 1
	.short _0224810C - _02248096 - 2 ; case 2
	.short _02248116 - _02248096 - 2 ; case 3
	.short _02248116 - _02248096 - 2 ; case 4
	.short _02248128 - _02248096 - 2 ; case 5
	.short _02248174 - _02248096 - 2 ; case 6
	.short _02248186 - _02248096 - 2 ; case 7
	.short _02248162 - _02248096 - 2 ; case 8
	.short _022481A6 - _02248096 - 2 ; case 9
	.short _022485F6 - _02248096 - 2 ; case 10
	.short _022481D8 - _02248096 - 2 ; case 11
	.short _022481FC - _02248096 - 2 ; case 12
	.short _0224821A - _02248096 - 2 ; case 13
	.short _0224822E - _02248096 - 2 ; case 14
	.short _02248240 - _02248096 - 2 ; case 15
	.short _02248262 - _02248096 - 2 ; case 16
	.short _022485F6 - _02248096 - 2 ; case 17
	.short _02248276 - _02248096 - 2 ; case 18
	.short _0224830C - _02248096 - 2 ; case 19
	.short _02248348 - _02248096 - 2 ; case 20
	.short _02248352 - _02248096 - 2 ; case 21
	.short _022483BC - _02248096 - 2 ; case 22
	.short _02248398 - _02248096 - 2 ; case 23
	.short _022483AA - _02248096 - 2 ; case 24
	.short _022483F6 - _02248096 - 2 ; case 25
	.short _02248400 - _02248096 - 2 ; case 26
	.short _02248420 - _02248096 - 2 ; case 27
	.short _02248432 - _02248096 - 2 ; case 28
	.short _0224844E - _02248096 - 2 ; case 29
	.short _02248458 - _02248096 - 2 ; case 30
	.short _02248478 - _02248096 - 2 ; case 31
	.short _0224849A - _02248096 - 2 ; case 32
	.short _022484F4 - _02248096 - 2 ; case 33
	.short _0224851C - _02248096 - 2 ; case 34
	.short _02248538 - _02248096 - 2 ; case 35
	.short _02248542 - _02248096 - 2 ; case 36
	.short _0224856E - _02248096 - 2 ; case 37
	.short _0224858E - _02248096 - 2 ; case 38
	.short _022485AA - _02248096 - 2 ; case 39
	.short _022485C6 - _02248096 - 2 ; case 40
	.short _022485E4 - _02248096 - 2 ; case 41
_022480EA:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248134
	add r0, r4, #0
	bl MOD18_02247AA8
	add r0, r4, #0
	add r0, #0x37
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224810C:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247F5C
	b _022485F6
_02248116:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247B60
	b _022485F6
_02248128:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	beq _02248136
_02248134:
	b _022485F6
_02248136:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #9
	bne _0224814E
	add r0, r4, #0
	mov r1, #9
	add r0, #0x37
	strb r1, [r0]
	ldrh r0, [r4, #0x30]
	bl MOD18_0224D698
_0224814E:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #6
	bne _02248256
	add r0, r4, #0
	mov r1, #6
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248162:
	add r0, r4, #0
	mov r1, #0xf
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #7
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248174:
	add r0, r4, #0
	mov r1, #8
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #7
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248186:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248256
	ldr r0, _022484C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _02248256
	add r0, r4, #0
	mov r1, #4
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022481A6:
	bl MOD18_0224D774
	cmp r0, #0
	beq _02248256
	bl MOD18_0223D638
	bl MOD18_0224DD94
	ldrh r0, [r4, #0x30]
	bl FUN_0202DFA4
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #8]
	ldr r2, _022484C4 ; =MOD18_0224804C
	ldr r0, [r0, #8]
	add r3, r4, #0
	bl MOD18_0224D5CC
	add r0, r4, #0
	mov r1, #0xa
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022481D8:
	ldr r0, [r4, #8]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x20
	bl FUN_0202A170
	bl MOD18_0224D784
	add r0, r4, #0
	mov r1, #9
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0xc
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022481FC:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248256
	add r0, r4, #0
	mov r1, #0xe
	bl MOD18_022479D0
	add r0, r4, #0
	mov r1, #0xd
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224821A:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0xd
	bne _02248256
	add r0, r4, #0
	mov r1, #0xe
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224822E:
	add r0, r4, #0
	mov r1, #0xa
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #1
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248240:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248256
	ldr r0, _022484C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _02248258
_02248256:
	b _022485F6
_02248258:
	add r0, r4, #0
	mov r1, #0xe
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248262:
	ldr r0, _022484C8 ; =MOD18_02248034
	ldr r1, [r4, #8]
	bl MOD18_0224AF28
	str r0, [r4, #4]
	add r0, r4, #0
	mov r1, #0x11
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248276:
	mov r0, #0
	str r0, [r4, #4]
	ldr r0, _022484CC ; =0x022513F0
	ldr r0, [r0, #4]
	add r0, #0x2a
	ldrb r0, [r0]
	cmp r0, #0
	bne _02248298
	add r0, r4, #0
	mov r1, #0xb
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248298:
	ldrh r0, [r4, #0x30]
	bl FUN_0202E068
	cmp r0, #0
	beq _022482B4
	add r0, r4, #0
	mov r1, #0x57
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022482B4:
	ldr r0, [r4, #8]
	ldr r0, [r0, #0xc]
	bl FUN_02025C18
	cmp r0, #0
	bne _022482D2
	add r0, r4, #0
	mov r1, #0x57
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022482D2:
	ldr r0, _022484CC ; =0x022513F0
	ldr r0, [r0, #4]
	add r0, #0x2a
	ldrb r0, [r0]
	bl FUN_0204CB10
	cmp r0, #0
	beq _022482F4
	add r0, r4, #0
	mov r1, #0x56
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022482F4:
	ldr r1, _022484CC ; =0x022513F0
	add r0, r4, #0
	ldr r1, [r1, #4]
	add r1, #0x2a
	ldrb r1, [r1]
	bl MOD18_02247EF8
	add r0, r4, #0
	mov r1, #0x13
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224830C:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224838C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #8]
	ldr r1, _022484D0 ; =0x02250520
	ldr r0, [r0, #8]
	ldr r2, _022484D4 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x24]
	add r0, r4, #0
	mov r1, #0x14
	add r0, #0x37
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #8
	beq _0224838C
	add r0, r4, #0
	mov r1, #1
	add r0, #0x38
	strb r1, [r0]
	b _022485F6
_02248348:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247F18
	b _022485F6
_02248352:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224838C
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x16
	bne _02248370
	add r0, r4, #0
	mov r1, #0x16
	add r0, #0x37
	strb r1, [r0]
_02248370:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x18
	bne _02248382
	add r0, r4, #0
	mov r1, #0x18
	add r0, #0x37
	strb r1, [r0]
_02248382:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x17
	beq _0224838E
_0224838C:
	b _022485F6
_0224838E:
	add r0, r4, #0
	mov r1, #0x17
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248398:
	add r0, r4, #0
	mov r1, #0x1e
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x1a
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022483AA:
	add r0, r4, #0
	mov r1, #0xd
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x1a
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022483BC:
	add r0, r4, #0
	bl MOD18_02247EA0
	ldr r0, [r4, #8]
	ldr r0, [r0, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	bl FUN_0205F720
	add r1, r0, #0
	add r1, r1, #1
	lsl r1, r1, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	bl FUN_0205F730
	ldr r0, [r4, #8]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x1f
	bl FUN_0202A170
	add r0, r4, #0
	mov r1, #0x19
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022483F6:
	add r0, r4, #0
	mov r1, #0x1a
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248400:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224848E
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0xf
	bne _0224848E
	add r0, r4, #0
	mov r1, #0xe
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248420:
	add r0, r4, #0
	mov r1, #0x88
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x1c
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248432:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224848E
	add r0, r4, #0
	bl MOD18_02247BB8
	add r0, r4, #0
	mov r1, #0x1d
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224844E:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247C98
	b _022485F6
_02248458:
	bl MOD18_0223D638
	add r1, r4, #0
	add r1, #0x32
	ldrb r1, [r1]
	bl MOD18_0224DE00
	add r0, r4, #0
	mov r1, #0x89
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x1f
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248478:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224848E
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x20
	beq _02248490
_0224848E:
	b _022485F6
_02248490:
	add r0, r4, #0
	mov r1, #0x20
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224849A:
	add r0, r4, #0
	add r0, #0x33
	ldrb r6, [r0]
	cmp r6, #0x33
	bne _022484D8
	add r0, r4, #0
	mov r1, #0x8b
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0
	add r0, #0x38
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0x21
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
	nop
_022484C0: .word gMain
_022484C4: .word MOD18_0224804C
_022484C8: .word MOD18_02248034
_022484CC: .word MOD18_022513F0
_022484D0: .word MOD18_02250520
_022484D4: .word 0x000003D9
_022484D8:
	bl MOD18_0223D638
	add r1, r6, #0
	bl MOD18_0224DE18
	add r0, r4, #0
	mov r1, #0x8a
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x22
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022484F4:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022485F6
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x2a
	bne _022485F6
	add r0, r4, #0
	mov r1, #0
	add r0, #0x38
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0xe
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224851C:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022485F6
	add r0, r4, #0
	bl MOD18_02247D1C
	add r0, r4, #0
	mov r1, #0x23
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_02248538:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247DD8
	b _022485F6
_02248542:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022485F6
	ldr r0, [r4, #8]
	ldr r0, [r0, #0xc]
	bl FUN_02029FC8
	mov r1, #0x21
	bl FUN_0202A170
	add r0, r4, #0
	mov r1, #0x8e
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x25
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224856E:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022485F6
	ldr r0, _02248658 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _022485F6
	add r0, r4, #0
	mov r1, #0x26
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_0224858E:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x25
	bne _022485F6
	add r0, r4, #0
	mov r1, #0x64
	bl MOD18_022479D0
	add r0, r4, #0
	mov r1, #0x27
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022485AA:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x64
	bne _022485F6
	add r0, r4, #0
	mov r1, #0x96
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #0x28
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022485C6:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022485F6
	add r0, r4, #0
	mov r1, #0x65
	bl MOD18_022479D0
	add r0, r4, #0
	mov r1, #0x29
	add r0, #0x37
	strb r1, [r0]
	b _022485F6
_022485E4:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #0x65
	bne _022485F6
	add r0, r4, #0
	mov r1, #0xe
	add r0, #0x37
	strb r1, [r0]
_022485F6:
	add r0, r4, #0
	add r0, #0x38
	ldrb r0, [r0]
	cmp r0, #8
	bne _02248652
	add r0, r4, #0
	add r0, #0x37
	ldrb r0, [r0]
	cmp r0, #4
	beq _02248652
	cmp r0, #7
	beq _02248652
	ldr r0, [r4, #0x24]
	cmp r0, #0
	beq _0224861E
	mov r1, #4
	bl FUN_020021EC
	mov r0, #0
	str r0, [r4, #0x24]
_0224861E:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0224863C
	mov r1, #1
	mvn r1, r1
	bl MOD18_0224ADBC
	bl MOD18_0223E6A0
	bl MOD18_0223D678
	bl MOD18_0224DD94
	mov r0, #0
	str r0, [r4, #4]
_0224863C:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02247FC0
	add r0, r4, #0
	mov r1, #8
	add r0, #0x37
	strb r1, [r0]
	mov r0, #0
	add r4, #0x38
	strb r0, [r4]
_02248652:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02248658: .word gMain
	thumb_func_end MOD18_02248054

	thumb_func_start MOD18_0224865C
MOD18_0224865C: ; 0x0224865C
	push {r4, lr}
	add r4, r0, #0
	mov r1, #0xf
	bl MOD18_022479E4
	add r0, r4, #0
	mov r1, #8
	bl MOD18_022479D0
	mov r0, #7
	add r4, #0x37
	strb r0, [r4]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224865C

	thumb_func_start MOD18_02248678
MOD18_02248678: ; 0x02248678
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x20]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _022486B6
	cmp r0, #0
	bne _022486A2
	add r0, r4, #0
	mov r1, #9
	bl MOD18_022479BC
	ldrh r0, [r4, #0x2c]
	bl MOD18_0224D698
	mov r1, #0xa
	b _022486AC
_022486A2:
	add r0, r4, #0
	mov r1, #6
	bl MOD18_022479BC
	mov r1, #8
_022486AC:
	add r0, r4, #0
	add r0, #0x34
	strb r1, [r0]
	mov r0, #0
	str r0, [r4, #0x20]
_022486B6:
	pop {r4, pc}
	thumb_func_end MOD18_02248678

	thumb_func_start MOD18_022486B8
MOD18_022486B8: ; 0x022486B8
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x20]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0224873A
	cmp r0, #0
	bne _0224871E
	add r0, r4, #0
	add r0, #0x26
	ldrb r0, [r0]
	bl MOD18_022494B4
	cmp r0, #0
	beq _02248704
	ldr r0, [r4, #4]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CB4
	bl FUN_02026B90
	ldr r0, _0224873C ; =0x000005E3
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0x16
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0x13
	add r0, #0x34
	strb r1, [r0]
	b _02248736
_02248704:
	add r0, r4, #0
	mov r1, #0x17
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0x15
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #0x15
	add r0, #0x34
	strb r1, [r0]
	b _02248736
_0224871E:
	add r0, r4, #0
	mov r1, #0x18
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0x1d
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #0x15
	add r0, #0x34
	strb r1, [r0]
_02248736:
	mov r0, #0
	str r0, [r4, #0x20]
_0224873A:
	pop {r4, pc}
	.align 2, 0
_0224873C: .word 0x000005E3
	thumb_func_end MOD18_022486B8

	thumb_func_start MOD18_02248740
MOD18_02248740: ; 0x02248740
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _02248756
	mov r1, #4
	bl FUN_020021EC
	mov r0, #0
	str r0, [r4, #0x20]
_02248756:
	ldr r1, [r4, #0x28]
	cmp r1, #0
	beq _02248760
	mov r0, #0
	blx r1
_02248760:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02248784
	add r0, r4, #0
	bl FreeToHeap
	bl FUN_0204F7FC
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, _02248780 ; =0x022513F0
	mov r1, #0
	str r1, [r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02248780: .word MOD18_022513F0
	thumb_func_end MOD18_02248740

	thumb_func_start MOD18_02248784
MOD18_02248784: ; 0x02248784
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _022487BC
	add r0, r4, #0
	add r0, #8
	mov r1, #0
	bl FUN_0200CCF8
	mov r1, #0
	ldr r0, [r4, #0x1c]
	add r2, r1, #0
	bl DestroyListMenu
	add r0, r4, #0
	add r0, #8
	bl FUN_02019570
	add r0, r4, #0
	add r0, #8
	bl FUN_02019178
	ldr r0, [r4, #0x18]
	bl ListMenuItems_dtor
	mov r0, #0
	str r0, [r4, #0x18]
_022487BC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02248784

	thumb_func_start MOD18_022487C0
MOD18_022487C0: ; 0x022487C0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl MOD18_0223D638
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r6, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D638
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_022487C0

	thumb_func_start MOD18_022487EC
MOD18_022487EC: ; 0x022487EC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD18_0223D638
	add r4, r0, #0
	ldrh r0, [r5, #0x2c]
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D638
	add r5, #0x26
	ldrb r1, [r5]
	bl MOD18_0224DE44
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x1f
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_022487EC

	thumb_func_start MOD18_02248820
MOD18_02248820: ; 0x02248820
	push {r3, r4, r5, r6, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #5
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x18]
	mov r3, #1
	add r1, r5, #0
	str r3, [sp]
	mov r0, #0x10
	str r0, [sp, #4]
	mov r0, #0xa
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _022488E0 ; =0x0000028D
	add r1, #8
	str r0, [sp, #0x10]
	ldr r0, [r5, #4]
	mov r2, #3
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _022488E4 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _022488E8 ; =0x0000023D
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r6, r0, #0
	mov r4, #0
_02248870:
	add r2, r5, #0
	add r2, #0x2e
	ldrb r2, [r2]
	ldr r0, [r5, #0x18]
	add r1, r6, #0
	lsl r2, r2, #2
	add r2, r4, r2
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r4, r4, #1
	cmp r4, #4
	blt _02248870
	ldr r0, [r5, #0x18]
	add r1, r6, #0
	mov r2, #0x30
	mov r3, #0x33
	bl ListMenuItems_AppendFromMsgData
	add r0, r6, #0
	bl DestroyMsgData
	ldr r4, _022488EC ; =0x02250528
	add r3, sp, #0x14
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [r5, #0x18]
	mov r1, #5
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #8
	str r0, [sp, #0x20]
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	mov r1, #0
	add r0, r2, #0
	strh r1, [r5, #0x36]
	add r2, r1, #0
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x1c]
	add r5, #8
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x34
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
_022488E0: .word 0x0000028D
_022488E4: .word 0x000003D9
_022488E8: .word 0x0000023D
_022488EC: .word MOD18_02250528
	thumb_func_end MOD18_02248820

	thumb_func_start MOD18_022488F0
MOD18_022488F0: ; 0x022488F0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	ldr r0, [r5, #0x1c]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r1, r5, #0
	ldr r0, [r5, #0x1c]
	add r1, #0x36
	ldrh r6, [r5, #0x36]
	bl ListMenuGetCurrentItemArrayId
	ldrh r0, [r5, #0x36]
	cmp r6, r0
	beq _02248916
	ldr r0, _022489C0 ; =0x000005DC
	bl FUN_020054C8
_02248916:
	bl FUN_020311F0
	cmp r0, #0
	beq _02248922
	mov r4, #1
	mvn r4, r4
_02248922:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02248934
	add r0, r0, #1
	cmp r4, r0
	bne _02248936
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02248934:
	mov r4, #0x33
_02248936:
	ldr r0, _022489C0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r7, #0
	add r1, r5, #0
	bl MOD18_02248784
	cmp r4, #0x33
	beq _02248978
	add r0, r5, #0
	add r0, #0x2e
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r1, r4, r0
	add r0, r5, #0
	add r0, #0x2f
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0x1a
	add r0, #0x34
	strb r1, [r0]
	bl MOD18_0223D638
	add r1, r5, #0
	add r1, #0x2f
	ldrb r1, [r1]
	bl MOD18_0224DE18
	add r0, r5, #0
	mov r1, #0x92
	bl MOD18_02247A0C
	b _02248998
_02248978:
	add r0, r5, #0
	mov r1, #0x33
	add r0, #0x2f
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0x10
	add r0, #0x34
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0
	add r0, #0x35
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #0x91
	bl MOD18_02247A0C
_02248998:
	add r0, r5, #0
	add r0, #0x2f
	ldrb r1, [r0]
	add r0, sp, #0
	strb r1, [r0]
	ldrh r1, [r5, #0x2c]
	strb r1, [r0, #1]
	mov r1, #1
	strb r1, [r0, #2]
	mov r0, #0x4f
	add r1, sp, #0
	bl FUN_020311D0
	add r0, r5, #0
	mov r1, #0x20
	bl MOD18_022479BC
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022489C0: .word 0x000005DC
	thumb_func_end MOD18_022488F0

	thumb_func_start MOD18_022489C4
MOD18_022489C4: ; 0x022489C4
	mov r1, #0xc
	add r0, #0x34
	strb r1, [r0]
	bx lr
	thumb_func_end MOD18_022489C4

	thumb_func_start MOD18_022489CC
MOD18_022489CC: ; 0x022489CC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r1, #0
	add r5, r0, #0
	ldrh r0, [r4, #0x2c]
	bl FUN_02030E7C
	cmp r0, #0
	bne _022489EA
	bl MOD18_0224D344
	add r0, r4, #0
	mov r1, #4
	add r0, #0x34
	strb r1, [r0]
_022489EA:
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #0x20
	bls _022489F6
	b _02248DB6
_022489F6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02248A02: ; jump table
	.short _02248DB6 - _02248A02 - 2 ; case 0
	.short _02248DB6 - _02248A02 - 2 ; case 1
	.short _02248A56 - _02248A02 - 2 ; case 2
	.short _02248DB6 - _02248A02 - 2 ; case 3
	.short _02248A44 - _02248A02 - 2 ; case 4
	.short _02248A9C - _02248A02 - 2 ; case 5
	.short _02248AAE - _02248A02 - 2 ; case 6
	.short _02248AD8 - _02248A02 - 2 ; case 7
	.short _02248AE2 - _02248A02 - 2 ; case 8
	.short _02248AF4 - _02248A02 - 2 ; case 9
	.short _02248B14 - _02248A02 - 2 ; case 10
	.short _02248DB6 - _02248A02 - 2 ; case 11
	.short _02248B46 - _02248A02 - 2 ; case 12
	.short _02248B5E - _02248A02 - 2 ; case 13
	.short _02248B7C - _02248A02 - 2 ; case 14
	.short _02248B92 - _02248A02 - 2 ; case 15
	.short _02248BA4 - _02248A02 - 2 ; case 16
	.short _02248BC2 - _02248A02 - 2 ; case 17
	.short _02248BEC - _02248A02 - 2 ; case 18
	.short _02248BF6 - _02248A02 - 2 ; case 19
	.short _02248C06 - _02248A02 - 2 ; case 20
	.short _02248C10 - _02248A02 - 2 ; case 21
	.short _02248C38 - _02248A02 - 2 ; case 22
	.short _02248C50 - _02248A02 - 2 ; case 23
	.short _02248C82 - _02248A02 - 2 ; case 24
	.short _02248CA0 - _02248A02 - 2 ; case 25
	.short _02248CAA - _02248A02 - 2 ; case 26
	.short _02248CD2 - _02248A02 - 2 ; case 27
	.short _02248D1C - _02248A02 - 2 ; case 28
	.short _02248D3A - _02248A02 - 2 ; case 29
	.short _02248D50 - _02248A02 - 2 ; case 30
	.short _02248D74 - _02248A02 - 2 ; case 31
	.short _02248D9C - _02248A02 - 2 ; case 32
_02248A44:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02248740
	b _02248DB6
_02248A56:
	add r0, r4, #0
	mov r1, #0xc
	add r0, #0x2e
	strb r1, [r0]
	ldr r0, _02248D8C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #2
	tst r0, r1
	beq _02248A7A
	add r0, r4, #0
	mov r1, #8
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #8
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248A7A:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #5
	bne _02248A8E
	add r0, r4, #0
	mov r1, #5
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248A8E:
	cmp r0, #0x16
	bne _02248B86
	add r0, r4, #0
	mov r1, #0x16
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248A9C:
	add r0, r4, #0
	mov r1, #0x18
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #6
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248AAE:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248B86
	add r0, r4, #0
	mov r1, #7
	add r0, #0x34
	strb r1, [r0]
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r1, _02248D90 ; =0x02250520
	ldr r0, [r0, #8]
	ldr r2, _02248D94 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x20]
	b _02248DB6
_02248AD8:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02248678
	b _02248DB6
_02248AE2:
	add r0, r4, #0
	mov r1, #0xf
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #9
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248AF4:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248B86
	ldr r0, _02248D8C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _02248B86
	add r0, r4, #0
	mov r1, #4
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248B14:
	bl MOD18_0224D774
	cmp r0, #0
	beq _02248B86
	bl MOD18_0223D638
	bl MOD18_0224DD94
	ldrh r0, [r4, #0x2c]
	bl FUN_0202DFA4
	add r1, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r2, _02248D98 ; =MOD18_022489C4
	ldr r0, [r0, #8]
	add r3, r4, #0
	bl MOD18_0224D5CC
	add r0, r4, #0
	mov r1, #0xb
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248B46:
	bl MOD18_0224D784
	ldrh r1, [r4, #0x2c]
	add r0, r4, #0
	mov r2, #0x1a
	bl MOD18_022487C0
	add r0, r4, #0
	mov r1, #0xd
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248B5E:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248B86
	add r0, r4, #0
	mov r1, #0xd
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0xe
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248B7C:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #0xe
	beq _02248B88
_02248B86:
	b _02248DB6
_02248B88:
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248B92:
	add r0, r4, #0
	mov r1, #0x1b
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #2
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248BA4:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248C8E
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x34
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0x2a
	bl MOD18_022479BC
	b _02248DB6
_02248BC2:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248C8E
	add r0, r4, #0
	mov r1, #0x12
	add r0, #0x34
	strb r1, [r0]
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r1, _02248D90 ; =0x02250520
	ldr r0, [r0, #8]
	ldr r2, _02248D94 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x20]
	b _02248DB6
_02248BEC:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_022486B8
	b _02248DB6
_02248BF6:
	add r0, r4, #0
	bl MOD18_022487EC
	add r0, r4, #0
	mov r1, #0x14
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248C06:
	add r0, r4, #0
	mov r1, #0x15
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248C10:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248C8E
	ldr r0, _02248D8C ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _02248C8E
	add r0, r4, #0
	mov r1, #0xf
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248C38:
	add r0, r4, #0
	mov r1, #0x8f
	bl MOD18_02247A0C
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248C50:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248C8E
	add r0, r4, #0
	add r0, #0x2e
	ldrb r6, [r0]
	cmp r6, #0xc
	beq _02248C8E
	bl MOD18_0223D638
	add r1, r6, #0
	bl MOD18_0224DE00
	add r0, r4, #0
	mov r1, #0x90
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #0x18
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248C82:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	beq _02248C90
_02248C8E:
	b _02248DB6
_02248C90:
	add r0, r4, #0
	bl MOD18_02248820
	add r0, r4, #0
	mov r1, #0x19
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248CA0:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_022488F0
	b _02248DB6
_02248CAA:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248DB6
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #0x1b
	bne _02248DB6
	add r0, r4, #0
	mov r1, #0x25
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0x1b
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248CD2:
	bl MOD18_0223D638
	add r1, r4, #0
	add r1, #0x30
	ldrb r1, [r1]
	bl MOD18_0224DE18
	bl MOD18_0223D638
	add r2, r4, #0
	add r2, #0x2f
	ldrb r2, [r2]
	mov r1, #6
	bl MOD18_0224DE30
	add r0, r4, #0
	add r0, #0x2f
	ldrb r1, [r0]
	add r0, r4, #0
	add r0, #0x30
	ldrb r0, [r0]
	cmp r1, r0
	bne _02248D0A
	add r0, r4, #0
	mov r1, #0x94
	bl MOD18_02247A0C
	b _02248D12
_02248D0A:
	add r0, r4, #0
	mov r1, #0x93
	bl MOD18_02247A0C
_02248D12:
	add r0, r4, #0
	mov r1, #0x1c
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248D1C:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248DB6
	add r0, r4, #0
	mov r1, #0x95
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #0x1d
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248D3A:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248DB6
	add r0, r4, #0
	mov r1, #0x1e
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248D50:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #0x64
	bne _02248DB6
	add r0, r4, #0
	mov r1, #0x64
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0x96
	bl MOD18_02247A0C
	add r0, r4, #0
	mov r1, #0x1f
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
_02248D74:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _02248DB6
	add r0, r4, #0
	mov r1, #0x20
	add r0, #0x34
	strb r1, [r0]
	b _02248DB6
	nop
_02248D8C: .word gMain
_02248D90: .word MOD18_02250520
_02248D94: .word 0x000003D9
_02248D98: .word MOD18_022489C4
_02248D9C:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #0x65
	bne _02248DB6
	add r0, r4, #0
	mov r1, #0x65
	bl MOD18_022479BC
	add r0, r4, #0
	mov r1, #0xf
	add r0, #0x34
	strb r1, [r0]
_02248DB6:
	add r0, r4, #0
	add r0, #0x35
	ldrb r0, [r0]
	cmp r0, #8
	bne _02248DF4
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #4
	beq _02248DF4
	cmp r0, #9
	beq _02248DF4
	ldr r0, [r4, #0x20]
	cmp r0, #0
	beq _02248DDE
	mov r1, #4
	bl FUN_020021EC
	mov r0, #0
	str r0, [r4, #0x20]
_02248DDE:
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_02248784
	add r0, r4, #0
	mov r1, #8
	add r0, #0x34
	strb r1, [r0]
	mov r0, #0
	add r4, #0x35
	strb r0, [r4]
_02248DF4:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD18_022489CC

	thumb_func_start MOD18_02248DF8
MOD18_02248DF8: ; 0x02248DF8
	push {r4, r5, r6, lr}
	ldr r0, _02248E60 ; =0x022513F0
	add r5, r1, #0
	ldr r0, [r0]
	add r6, r2, #0
	cmp r0, #0
	beq _02248E0C
	bl ErrorHandling
	pop {r4, r5, r6, pc}
_02248E0C:
	mov r0, #0x21
	mov r1, #0x38
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x38
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, _02248E60 ; =0x022513F0
	mov r1, #2
	str r4, [r0]
	str r6, [r4, #4]
	add r0, r4, #0
	strh r5, [r4, #0x2c]
	add r0, #0x34
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0
	add r0, #0x35
	strb r1, [r0]
	add r0, r4, #0
	mov r1, #0xc
	add r0, #0x2e
	strb r1, [r0]
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x16
	add r3, r2, #0
	bl MOD18_0224DCB8
	bl FUN_0204FB14
	ldr r0, _02248E64 ; =MOD18_022489CC
	ldr r2, _02248E68 ; =0x00002710
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4]
	pop {r4, r5, r6, pc}
	nop
_02248E60: .word MOD18_022513F0
_02248E64: .word MOD18_022489CC
_02248E68: .word 0x00002710
	thumb_func_end MOD18_02248DF8

	thumb_func_start MOD18_02248E6C
MOD18_02248E6C: ; 0x02248E6C
	ldr r3, _02248E74 ; =FUN_02030C4C
	mov r0, #0x4b
	add r1, r2, #0
	bx r3
	.align 2, 0
_02248E74: .word FUN_02030C4C
	thumb_func_end MOD18_02248E6C

	thumb_func_start MOD18_02248E78
MOD18_02248E78: ; 0x02248E78
	ldr r3, _02248E80 ; =FUN_02030C4C
	mov r0, #0x4c
	add r1, r2, #0
	bx r3
	.align 2, 0
_02248E80: .word FUN_02030C4C
	thumb_func_end MOD18_02248E78

	thumb_func_start MOD18_02248E84
MOD18_02248E84: ; 0x02248E84
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _02248EAE
	ldr r0, _02248EB0 ; =0x022513F0
	ldr r0, [r0]
	cmp r0, #0
	beq _02248EAE
	cmp r5, #2
	beq _02248EA4
	bl ErrorHandling
_02248EA4:
	ldr r0, _02248EB0 ; =0x022513F0
	ldrb r1, [r4, #1]
	ldr r0, [r0]
	add r0, #0x35
	strb r1, [r0]
_02248EAE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02248EB0: .word MOD18_022513F0
	thumb_func_end MOD18_02248E84

	thumb_func_start MOD18_02248EB4
MOD18_02248EB4: ; 0x02248EB4
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _02248EEA
	ldr r0, _02248EEC ; =0x022513F0
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02248EEA
	cmp r5, #2
	beq _02248ED4
	bl ErrorHandling
_02248ED4:
	ldr r0, _02248EEC ; =0x022513F0
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _02248EE0
	bl ErrorHandling
_02248EE0:
	ldr r0, _02248EEC ; =0x022513F0
	ldrb r1, [r4, #1]
	ldr r0, [r0, #4]
	add r0, #0x38
	strb r1, [r0]
_02248EEA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02248EEC: .word MOD18_022513F0
	thumb_func_end MOD18_02248EB4

	thumb_func_start MOD18_02248EF0
MOD18_02248EF0: ; 0x02248EF0
	mov r0, #2
	bx lr
	thumb_func_end MOD18_02248EF0

	thumb_func_start MOD18_02248EF4
MOD18_02248EF4: ; 0x02248EF4
	ldr r3, _02248EFC ; =FUN_02030C4C
	mov r0, #0x4e
	add r1, r2, #0
	bx r3
	.align 2, 0
_02248EFC: .word FUN_02030C4C
	thumb_func_end MOD18_02248EF4

	thumb_func_start MOD18_02248F00
MOD18_02248F00: ; 0x02248F00
	push {r3, r4, r5, lr}
	ldr r0, _02248F70 ; =0x022513F0
	add r5, r2, #0
	ldr r4, [r0]
	bl FUN_02031190
	ldrb r1, [r5]
	cmp r1, r0
	bne _02248F6E
	ldr r0, _02248F70 ; =0x022513F0
	ldr r0, [r0]
	cmp r0, #0
	bne _02248F1E
	bl ErrorHandling
_02248F1E:
	add r0, r4, #0
	add r0, #0x34
	ldrb r0, [r0]
	cmp r0, #2
	beq _02248F38
	add r0, r4, #0
	mov r1, #8
	bl MOD18_022479BC
	mov r0, #8
	add r4, #0x34
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_02248F38:
	ldrb r1, [r5]
	add r0, r4, #0
	add r0, #0x24
	strb r1, [r0]
	add r0, r4, #0
	ldrb r1, [r5, #1]
	add r0, #0x25
	strb r1, [r0]
	add r0, r4, #0
	ldrb r1, [r5, #2]
	add r0, #0x26
	add r4, #0x34
	strb r1, [r0]
	mov r0, #0x11
	strb r0, [r4]
	bl MOD18_0223D638
	ldrb r1, [r5, #2]
	bl MOD18_0224DE44
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x1c
	add r3, r2, #0
	bl MOD18_0224DCB8
_02248F6E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02248F70: .word MOD18_022513F0
	thumb_func_end MOD18_02248F00

	thumb_func_start MOD18_02248F74
MOD18_02248F74: ; 0x02248F74
	mov r0, #3
	bx lr
	thumb_func_end MOD18_02248F74

	thumb_func_start MOD18_02248F78
MOD18_02248F78: ; 0x02248F78
	ldr r3, _02248F80 ; =FUN_02030C4C
	mov r0, #0x50
	add r1, r2, #0
	bx r3
	.align 2, 0
_02248F80: .word FUN_02030C4C
	thumb_func_end MOD18_02248F78

	thumb_func_start MOD18_02248F84
MOD18_02248F84: ; 0x02248F84
	push {r4, r5, r6, lr}
	ldr r0, _02248FC0 ; =0x022513F0
	add r5, r2, #0
	ldr r4, [r0]
	ldr r6, [r0, #4]
	bl FUN_02031190
	ldrb r1, [r5, #1]
	cmp r1, r0
	bne _02248FBE
	ldrb r0, [r5, #2]
	cmp r0, #0
	beq _02248FA8
	cmp r0, #1
	beq _02248FB0
	cmp r0, #2
	beq _02248FB8
	pop {r4, r5, r6, pc}
_02248FA8:
	ldrb r0, [r5]
	add r4, #0x2e
	strb r0, [r4]
	pop {r4, r5, r6, pc}
_02248FB0:
	ldrb r0, [r5]
	add r6, #0x33
	strb r0, [r6]
	pop {r4, r5, r6, pc}
_02248FB8:
	ldrb r0, [r5]
	add r4, #0x30
	strb r0, [r4]
_02248FBE:
	pop {r4, r5, r6, pc}
	.align 2, 0
_02248FC0: .word MOD18_022513F0
	thumb_func_end MOD18_02248F84

	thumb_func_start MOD18_02248FC4
MOD18_02248FC4: ; 0x02248FC4
	mov r0, #3
	bx lr
	thumb_func_end MOD18_02248FC4

	thumb_func_start MOD18_02248FC8
MOD18_02248FC8: ; 0x02248FC8
	push {r3, lr}
	ldr r0, _02248FE8 ; =0x022513F0
	ldr r1, [r0, #4]
	cmp r1, #0
	beq _02248FD8
	ldr r0, [r1]
	bl MOD18_02247B60
_02248FD8:
	ldr r0, _02248FE8 ; =0x022513F0
	ldr r1, [r0]
	cmp r1, #0
	beq _02248FE6
	ldr r0, [r1]
	bl MOD18_02248740
_02248FE6:
	pop {r3, pc}
	.align 2, 0
_02248FE8: .word MOD18_022513F0
	thumb_func_end MOD18_02248FC8

	thumb_func_start MOD18_02248FEC
MOD18_02248FEC: ; 0x02248FEC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r1, r5, #0
	ldr r0, [r5, #0x20]
	add r1, #0x3a
	ldrh r4, [r5, #0x3a]
	bl ListMenuGetCurrentItemArrayId
	ldrh r0, [r5, #0x3a]
	cmp r4, r0
	beq _02249008
	ldr r0, _0224900C ; =0x000005DC
	bl FUN_020054C8
_02249008:
	pop {r3, r4, r5, pc}
	nop
_0224900C: .word 0x000005DC
	thumb_func_end MOD18_02248FEC

	thumb_func_start MOD18_02249010
MOD18_02249010: ; 0x02249010
	push {r4, r5, r6, r7, lr}
	sub sp, #0xb4
	ldr r4, _022491BC ; =0x02250580
	add r3, sp, #0x9c
	str r2, [sp, #0x14]
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, [sp, #0xc]
	add r1, r2, #0
	add r0, #0x74
	mov r2, #8
	mov r3, #0xb
	bl MOD05_021D959C
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #0xe3
	lsl r0, r0, #6
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	mov r1, #0x42
	add r0, #0x74
	mov r2, #9
	mov r3, #0
	bl MOD05_021D967C
	mov r0, #0xe3
	lsl r0, r0, #6
	str r0, [sp]
	ldr r0, [sp, #0xc]
	mov r1, #0x42
	add r0, #0x74
	mov r2, #1
	mov r3, #0
	bl MOD05_021D96F4
	mov r0, #0xe3
	lsl r0, r0, #6
	str r0, [sp]
	ldr r0, [sp, #0xc]
	mov r2, #0
	add r0, #0x74
	mov r1, #0x42
	add r3, r2, #0
	bl MOD05_021D9708
	mov r0, #1
	str r0, [sp]
	mov r0, #0xe3
	lsl r0, r0, #6
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	mov r1, #0x42
	add r0, #0x74
	mov r2, #2
	mov r3, #0
	bl MOD05_021D971C
	ldr r0, [sp, #0xc]
	ldr r1, _022491C0 ; =0x022505F0
	add r0, #0x74
	bl MOD05_021D9820
	mov r2, #0x76
	ldr r1, [sp, #0xc]
	lsl r2, r2, #2
	str r0, [r1, r2]
	add r0, r1, #0
	ldr r0, [r0, r2]
	add r2, #0x60
	ldrh r1, [r1, r2]
	ldr r0, [r0]
	bl MOD18_02249240
	ldr r0, _022491C4 ; =0x000038C1
	mov r1, #0x42
	str r0, [sp]
	ldr r0, [sp, #0xc]
	mov r2, #8
	add r0, #0x74
	mov r3, #0
	bl MOD05_021D96F4
	ldr r0, _022491C4 ; =0x000038C1
	mov r1, #0x42
	str r0, [sp]
	ldr r0, [sp, #0xc]
	mov r2, #7
	add r0, #0x74
	mov r3, #0
	bl MOD05_021D9708
	mov r0, #1
	str r0, [sp]
	ldr r0, _022491C4 ; =0x000038C1
	mov r1, #0x42
	str r0, [sp, #4]
	ldr r0, [sp, #0xc]
	mov r2, #0xa
	add r0, #0x74
	mov r3, #0
	bl MOD05_021D971C
	ldr r0, [sp, #0x14]
	mov r4, #0
	cmp r0, #0
	bls _02249184
	ldr r5, [sp, #0xc]
	ldr r3, _022491C8 ; =0x02250624
	add r7, r4, #0
	add r2, sp, #0x28
	mov r6, #6
_02249102:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r6, r6, #1
	bne _02249102
	ldr r0, [r3]
	ldr r3, _022491CC ; =0x02250574
	str r0, [r2]
	ldmia r3!, {r0, r1}
	add r2, sp, #0x1c
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [sp, #0xc]
	str r0, [sp, #0x18]
	add r0, #0x74
	str r0, [sp, #0x18]
_02249122:
	add r6, sp, #0x28
	add r3, sp, #0x68
	mov r2, #6
_02249128:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02249128
	ldr r0, [r6]
	add r1, sp, #0x68
	str r0, [r3]
	mov r0, #2
	ldrsh r0, [r1, r0]
	add r1, r0, r7
	add r0, sp, #0x68
	strh r1, [r0, #2]
	ldr r0, [sp, #0x10]
	ldrb r1, [r0, r4]
	lsl r0, r1, #1
	add r1, r1, r0
	add r0, sp, #0x68
	strh r1, [r0, #6]
	ldr r0, [sp, #0x18]
	add r1, sp, #0x68
	bl MOD05_021D9820
	mov r1, #0x77
	lsl r1, r1, #2
	add r2, sp, #0x5c
	add r3, sp, #0x1c
	str r0, [r5, r1]
	ldmia r3!, {r0, r1}
	add r6, r2, #0
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r1, r6, #0
	str r0, [r2]
	mov r0, #0x77
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r2, #1
	ldr r0, [r0]
	bl FUN_02020074
	ldr r0, [sp, #0x14]
	add r4, r4, #1
	add r7, #0x18
	add r5, r5, #4
	cmp r4, r0
	blo _02249122
_02249184:
	mov r1, #0x8e
	ldr r0, [sp, #0xc]
	lsl r1, r1, #2
	ldrh r0, [r0, r1]
	sub r1, #0x60
	add r0, r0, #1
	lsl r2, r0, #2
	ldr r0, [sp, #0xc]
	add r0, r0, r2
	ldr r0, [r0, r1]
	mov r1, #2
	ldr r0, [r0]
	mov r2, #1
	bl MOD18_02249270
	ldr r0, [sp, #0x14]
	mov r1, #0x7e
	add r2, r0, #1
	ldr r0, [sp, #0xc]
	lsl r1, r1, #2
	str r2, [r0, r1]
	mov r0, #0x10
	mov r1, #1
	bl GX_EngineAToggleLayers
	add sp, #0xb4
	pop {r4, r5, r6, r7, pc}
	nop
_022491BC: .word MOD18_02250580
_022491C0: .word MOD18_022505F0
_022491C4: .word 0x000038C1
_022491C8: .word MOD18_02250624
_022491CC: .word MOD18_02250574
	thumb_func_end MOD18_02249010

	thumb_func_start MOD18_022491D0
MOD18_022491D0: ; 0x022491D0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r4, #0
	cmp r0, #0
	bls _022491FE
	mov r7, #0x76
	lsl r7, r7, #2
	add r6, r7, #0
	add r6, #0x20
_022491E8:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r7]
	bl FUN_0200C3DC
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r6]
	cmp r4, r0
	blo _022491E8
_022491FE:
	add r5, #0x74
	add r0, r5, #0
	bl MOD05_021D99F8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_022491D0

	thumb_func_start MOD18_02249208
MOD18_02249208: ; 0x02249208
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	mov r4, #0
	cmp r0, #0
	bls _0224923C
	mov r7, #0x76
	lsl r7, r7, #2
	add r6, r7, #0
	add r6, #0x20
_02249220:
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r0, [r0, r7]
	mov r1, #1
	ldr r0, [r0]
	lsl r1, r1, #0xc
	bl FUN_020201E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, r6]
	cmp r4, r0
	blo _02249220
_0224923C:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_02249208

	thumb_func_start MOD18_02249240
MOD18_02249240: ; 0x02249240
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_0202011C
	add r6, r0, #0
	add r3, sp, #0
	ldmia r6!, {r0, r1}
	add r2, r3, #0
	stmia r3!, {r0, r1}
	ldr r0, [r6]
	add r1, r2, #0
	str r0, [r3]
	mov r0, #0x18
	mul r0, r4
	add r0, #0x14
	lsl r0, r0, #0xc
	str r0, [sp, #4]
	add r0, r5, #0
	bl FUN_02020044
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	thumb_func_end MOD18_02249240

	thumb_func_start MOD18_02249270
MOD18_02249270: ; 0x02249270
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	bl FUN_020201DC
	mov r1, #3
	bl _u32_div_f
	add r2, r0, #0
	lsl r1, r2, #1
	add r1, r2, r1
	add r0, r5, #0
	add r1, r4, r1
	bl FUN_02020130
	add r0, r5, #0
	add r1, r6, #0
	bl FUN_0202027C
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_02249270

	thumb_func_start MOD18_0224929C
MOD18_0224929C: ; 0x0224929C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, r1, #1
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #0
	add r4, r2, #0
	ldr r0, [r0]
	add r2, r1, #0
	bl MOD18_02249270
	add r0, r4, #1
	lsl r0, r0, #2
	add r1, r5, r0
	mov r0, #0x76
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	mov r1, #1
	ldr r0, [r0]
	add r2, r1, #0
	bl MOD18_02249270
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224929C

	thumb_func_start MOD18_022492D0
MOD18_022492D0: ; 0x022492D0
	push {r4, lr}
	add r4, r0, #0
	bl FUN_020201DC
	mov r1, #3
	bl _u32_div_f
	cmp r1, #1
	bne _022492F6
	add r0, r4, #0
	bl FUN_02020388
	cmp r0, #0
	bne _022492F6
	add r0, r4, #0
	mov r1, #2
	mov r2, #1
	bl MOD18_02249270
_022492F6:
	pop {r4, pc}
	thumb_func_end MOD18_022492D0

	thumb_func_start MOD18_022492F8
MOD18_022492F8: ; 0x022492F8
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xf
	mov r1, #8
	bl AllocFromHeap
	ldr r1, _02249324 ; =0x022513F8
	mov r2, #8
	str r0, [r1]
	mov r1, #0
	bl MI_CpuFill8
	ldr r0, _02249324 ; =0x022513F8
	mov r2, #0
	ldr r1, [r0]
	strb r2, [r1, #4]
	ldr r1, [r0]
	strb r2, [r1, #5]
	ldr r0, [r0]
	str r4, [r0]
	pop {r4, pc}
	nop
_02249324: .word MOD18_022513F8
	thumb_func_end MOD18_022492F8

	thumb_func_start MOD18_02249328
MOD18_02249328: ; 0x02249328
	ldr r0, _02249330 ; =0x022513F8
	ldr r3, _02249334 ; =FreeToHeap
	ldr r0, [r0]
	bx r3
	.align 2, 0
_02249330: .word MOD18_022513F8
_02249334: .word FreeToHeap
	thumb_func_end MOD18_02249328

	thumb_func_start MOD18_02249338
MOD18_02249338: ; 0x02249338
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl FUN_0202623C
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_02249338

	thumb_func_start MOD18_0224934C
MOD18_0224934C: ; 0x0224934C
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl FUN_02025DB0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0224934C

	thumb_func_start MOD18_02249360
MOD18_02249360: ; 0x02249360
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02025DC8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02249360

	thumb_func_start MOD18_02249378
MOD18_02249378: ; 0x02249378
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl FUN_02025F80
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_02249378

	thumb_func_start MOD18_0224938C
MOD18_0224938C: ; 0x0224938C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02025F98
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224938C

	thumb_func_start MOD18_022493A4
MOD18_022493A4: ; 0x022493A4
	push {r3, lr}
	ldr r1, _022493C4 ; =0x022513F8
	ldr r1, [r1]
	ldrb r1, [r1, #5]
	cmp r1, r0
	beq _022493B4
	bl ErrorHandling
_022493B4:
	ldr r0, _022493C4 ; =0x022513F8
	ldr r1, [r0]
	ldr r0, [r1]
	ldrb r1, [r1, #4]
	bl FUN_02025FA4
	pop {r3, pc}
	nop
_022493C4: .word MOD18_022513F8
	thumb_func_end MOD18_022493A4

	thumb_func_start MOD18_022493C8
MOD18_022493C8: ; 0x022493C8
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl FUN_02026050
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_022493C8

	thumb_func_start MOD18_022493DC
MOD18_022493DC: ; 0x022493DC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02026258
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_022493DC

	thumb_func_start MOD18_022493F4
MOD18_022493F4: ; 0x022493F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02026068
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_022493F4

	thumb_func_start MOD18_0224940C
MOD18_0224940C: ; 0x0224940C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02026074
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224940C

	thumb_func_start MOD18_02249424
MOD18_02249424: ; 0x02249424
	push {r3, lr}
	ldr r0, [r0, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl FUN_0202616C
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_02249424

	thumb_func_start MOD18_02249438
MOD18_02249438: ; 0x02249438
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02026188
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02249438

	thumb_func_start MOD18_02249450
MOD18_02249450: ; 0x02249450
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0xb
	blt _0224945E
	bl ErrorHandling
_0224945E:
	cmp r5, #6
	blt _02249464
	sub r5, r5, #5
_02249464:
	cmp r4, #0x63
	ble _0224946A
	mov r4, #0x63
_0224946A:
	ldr r0, _0224947C ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	add r2, r4, #0
	ldr r0, [r0]
	bl FUN_020260C4
	pop {r3, r4, r5, pc}
	nop
_0224947C: .word MOD18_022513F8
	thumb_func_end MOD18_02249450

	thumb_func_start MOD18_02249480
MOD18_02249480: ; 0x02249480
	push {r4, lr}
	add r4, r0, #0
	cmp r4, #0x3c
	blt _0224948C
	bl ErrorHandling
_0224948C:
	ldr r0, _0224949C ; =0x022513F8
	add r1, r4, #0
	ldr r0, [r0]
	ldr r0, [r0]
	bl FUN_020261C8
	pop {r4, pc}
	nop
_0224949C: .word MOD18_022513F8
	thumb_func_end MOD18_02249480

	thumb_func_start MOD18_022494A0
MOD18_022494A0: ; 0x022494A0
	add r1, r0, #0
	ldr r0, _022494AC ; =0x022513F8
	ldr r3, _022494B0 ; =FUN_02026298
	ldr r0, [r0]
	ldr r0, [r0]
	bx r3
	.align 2, 0
_022494AC: .word MOD18_022513F8
_022494B0: .word FUN_02026298
	thumb_func_end MOD18_022494A0

	thumb_func_start MOD18_022494B4
MOD18_022494B4: ; 0x022494B4
	add r1, r0, #0
	ldr r0, _022494C0 ; =0x022513F8
	ldr r3, _022494C4 ; =FUN_02025FD8
	ldr r0, [r0]
	ldr r0, [r0]
	bx r3
	.align 2, 0
_022494C0: .word MOD18_022513F8
_022494C4: .word FUN_02025FD8
	thumb_func_end MOD18_022494B4

	thumb_func_start MOD18_022494C8
MOD18_022494C8: ; 0x022494C8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _02249534 ; =0x000005FD
	add r6, r1, #0
	bl FUN_020054C8
	mov r0, #2
	bl MOD18_0223E56C
	mov r1, #0x25
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x25
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x7f
	str r6, [r4, #0xc]
	lsl r0, r0, #2
	str r5, [r4, r0]
	mov r1, #0
	add r0, #0x4a
	strb r1, [r4, r0]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x68]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x6c]
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r4, #0x70]
	ldr r0, _02249538 ; =MOD18_02249684
	ldr r2, _0224953C ; =0x00002710
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	ldr r1, [r4, #4]
	ldr r2, _02249540 ; =MOD18_0224AFE8
	add r0, r4, #0
	bl MOD18_0223E688
	pop {r4, r5, r6, pc}
	nop
_02249534: .word 0x000005FD
_02249538: .word MOD18_02249684
_0224953C: .word 0x00002710
_02249540: .word MOD18_0224AFE8
	thumb_func_end MOD18_022494C8

	thumb_func_start MOD18_02249544
MOD18_02249544: ; 0x02249544
	mov r1, #0
	strb r1, [r0]
	mov r1, #1
	strb r1, [r0, #1]
	mov r1, #2
	strb r1, [r0, #2]
	mov r1, #3
	strb r1, [r0, #3]
	mov r1, #4
	strb r1, [r0, #4]
	mov r1, #5
	strb r1, [r0, #5]
	mov r1, #6
	strb r1, [r0, #6]
	mov r0, #7
	bx lr
	thumb_func_end MOD18_02249544

	thumb_func_start MOD18_02249564
MOD18_02249564: ; 0x02249564
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r0, #0
	add r0, sp, #0x18
	bl MOD18_02249544
	mov r0, #7
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r0, #1
	str r0, [sp]
	mov r0, #0xb
	str r0, [sp, #4]
	mov r0, #0x15
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02249674 ; =0x000002E7
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	add r1, #0x10
	ldr r0, [r0, #8]
	mov r2, #3
	mov r3, #0x14
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _02249678 ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	ldr r4, _0224967C ; =0x022505B8
	str r0, [sp, #0x14]
	mov r6, #0
_022495BA:
	cmp r6, #4
	bne _022495E2
	ldr r0, [r5, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	mov r1, #4
	bl PlayerProfile_GetPlayerName_NewString
	add r7, r0, #0
	ldr r0, [r5, #0x40]
	ldr r2, [r4, #4]
	add r1, r7, #0
	bl ListMenuItems_AddItem
	add r0, r7, #0
	bl String_dtor
	b _022495EE
_022495E2:
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x14]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenuItems_AppendFromMsgData
_022495EE:
	add r6, r6, #1
	add r4, #8
	cmp r6, #7
	blo _022495BA
	ldr r0, [r5, #0xc]
	mov r3, #0x8e
	add r0, #0x8c
	ldr r0, [r0]
	lsl r3, r3, #2
	strh r0, [r5, r3]
	ldr r0, [r5, #0x40]
	mov r1, #1
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x24]
	add r0, sp, #0x18
	strb r1, [r0, #0x10]
	strb r1, [r0, #0x11]
	mov r1, #7
	strb r1, [r0, #0x12]
	ldrb r2, [r0, #0x13]
	mov r1, #0xf
	bic r2, r1
	mov r1, #8
	orr r1, r2
	strb r1, [r0, #0x13]
	ldrb r2, [r0, #0x13]
	mov r1, #0x30
	bic r2, r1
	mov r1, #0x10
	orr r1, r2
	strb r1, [r0, #0x13]
	ldrb r2, [r0, #0x13]
	mov r1, #0xc0
	bic r2, r1
	mov r1, #0x40
	orr r1, r2
	strb r1, [r0, #0x13]
	mov r0, #0xb
	str r0, [sp]
	ldr r0, _02249680 ; =0x00000402
	mov r1, #0x1c
	str r0, [sp, #4]
	ldrh r3, [r5, r3]
	add r0, sp, #0x20
	mov r2, #4
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	bl FUN_02001B8C
	str r0, [r5, #0x54]
	mov r0, #0
	str r0, [r5, #0x48]
	add r0, r5, #0
	add r0, #0x10
	bl FUN_02019220
	add r0, r5, #0
	add r1, sp, #0x18
	mov r2, #7
	bl MOD18_02249010
	bl FUN_0204F7E4
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02249674: .word 0x000002E7
_02249678: .word 0x000003D9
_0224967C: .word MOD18_022505B8
_02249680: .word 0x00000402
	thumb_func_end MOD18_02249564

	thumb_func_start MOD18_02249684
MOD18_02249684: ; 0x02249684
	push {r3, r4, r5, lr}
	ldr r2, _022497BC ; =0x00000246
	add r4, r1, #0
	ldrb r2, [r4, r2]
	add r5, r0, #0
	cmp r2, #0x13
	bls _02249694
	b _022497BA
_02249694:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_022496A0: ; jump table
	.short _022496C8 - _022496A0 - 2 ; case 0
	.short _022496D8 - _022496A0 - 2 ; case 1
	.short _022496DE - _022496A0 - 2 ; case 2
	.short _022496F4 - _022496A0 - 2 ; case 3
	.short _022497BA - _022496A0 - 2 ; case 4
	.short _0224970A - _022496A0 - 2 ; case 5
	.short _02249710 - _022496A0 - 2 ; case 6
	.short _02249716 - _022496A0 - 2 ; case 7
	.short _0224971C - _022496A0 - 2 ; case 8
	.short _02249722 - _022496A0 - 2 ; case 9
	.short _022497BA - _022496A0 - 2 ; case 10
	.short _02249728 - _022496A0 - 2 ; case 11
	.short _0224972E - _022496A0 - 2 ; case 12
	.short _02249734 - _022496A0 - 2 ; case 13
	.short _02249762 - _022496A0 - 2 ; case 14
	.short _02249788 - _022496A0 - 2 ; case 15
	.short _022497AA - _022496A0 - 2 ; case 16
	.short _022497B0 - _022496A0 - 2 ; case 17
	.short _022497A4 - _022496A0 - 2 ; case 18
	.short _022497B6 - _022496A0 - 2 ; case 19
_022496C8:
	add r0, r4, #0
	bl MOD18_02249564
	ldr r0, _022497BC ; =0x00000246
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_022496D8:
	bl MOD18_022497C8
	pop {r3, r4, r5, pc}
_022496DE:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223E6A0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD18_0224A8AC
	pop {r3, r4, r5, pc}
_022496F4:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223E6A0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD18_0224A8AC
	pop {r3, r4, r5, pc}
_0224970A:
	bl MOD18_02249CC8
	pop {r3, r4, r5, pc}
_02249710:
	bl MOD18_0224A0EC
	pop {r3, r4, r5, pc}
_02249716:
	bl MOD18_0224A47C
	pop {r3, r4, r5, pc}
_0224971C:
	bl MOD18_0224AC24
	pop {r3, r4, r5, pc}
_02249722:
	bl MOD18_0224AE68
	pop {r3, r4, r5, pc}
_02249728:
	bl MOD18_0224A710
	pop {r3, r4, r5, pc}
_0224972E:
	bl MOD18_0224A74C
	pop {r3, r4, r5, pc}
_02249734:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022497BA
	ldr r0, _022497C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _022497BA
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD18_0224A8AC
	bl MOD18_0223E6A0
	pop {r3, r4, r5, pc}
_02249762:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _022497BA
	ldr r0, _022497C0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _022497BA
	ldr r1, [r4]
	add r0, r4, #0
	blx r1
	ldr r0, _022497C4 ; =0x00000245
	ldrb r1, [r4, r0]
	add r0, r0, #1
	strb r1, [r4, r0]
	pop {r3, r4, r5, pc}
_02249788:
	add r0, r4, #0
	bl MOD18_022498EC
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD18_0224A8AC
	bl MOD18_0223E6A0
	ldr r0, [r4, #0xc]
	bl FUN_02049824
	pop {r3, r4, r5, pc}
_022497A4:
	bl MOD18_02249DB8
	pop {r3, r4, r5, pc}
_022497AA:
	bl MOD18_0224A1C0
	pop {r3, r4, r5, pc}
_022497B0:
	bl MOD18_0224A550
	pop {r3, r4, r5, pc}
_022497B6:
	bl MOD18_0224AD04
_022497BA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_022497BC: .word 0x00000246
_022497C0: .word gMain
_022497C4: .word 0x00000245
	thumb_func_end MOD18_02249684

	thumb_func_start MOD18_022497C8
MOD18_022497C8: ; 0x022497C8
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x54]
	bl FUN_02001E5C
	add r5, r0, #0
	mov r1, #0x5e
	ldr r0, [r4, #0x54]
	lsl r1, r1, #4
	bl FUN_02001D2C
	mov r1, #0x8f
	lsl r1, r1, #2
	str r0, [r4, r1]
	ldr r0, [r4, #0x54]
	bl FUN_02001E5C
	mov r2, #0x8e
	lsl r2, r2, #2
	strh r0, [r4, r2]
	ldrh r1, [r4, r2]
	cmp r5, r1
	beq _0224981A
	sub r2, #0x60
	ldr r0, [r4, r2]
	ldr r0, [r0]
	bl MOD18_02249240
	mov r2, #0x8e
	lsl r2, r2, #2
	ldrh r2, [r4, r2]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0224929C
	mov r0, #0x8e
	lsl r0, r0, #2
	ldrh r1, [r4, r0]
	ldr r0, [r4, #0xc]
	add r0, #0x8c
	str r1, [r0]
_0224981A:
	mov r0, #0x8e
	lsl r0, r0, #2
	ldrh r1, [r4, r0]
	sub r0, #0x60
	add r1, r1, #1
	lsl r1, r1, #2
	add r1, r4, r1
	ldr r0, [r1, r0]
	ldr r0, [r0]
	bl MOD18_022492D0
	bl FUN_020311F0
	cmp r0, #0
	beq _02249842
	mov r1, #1
	mov r0, #0x8f
	mvn r1, r1
	lsl r0, r0, #2
	str r1, [r4, r0]
_02249842:
	mov r1, #0x8f
	lsl r1, r1, #2
	mov r2, #1
	ldr r0, [r4, r1]
	mvn r2, r2
	cmp r0, r2
	beq _02249866
	add r1, r2, #1
	cmp r0, r1
	bne _0224986E
	add r0, r4, #0
	bl MOD18_02249208
	ldr r0, [r4, #0x74]
	bl FUN_0201FDEC
	mov r0, #0
	pop {r3, r4, r5, pc}
_02249866:
	mov r0, #2
	add r1, #0xa
	strb r0, [r4, r1]
	b _022498D6
_0224986E:
	ldr r1, _022498DC ; =MOD18_02249B50
	cmp r0, r1
	beq _02249886
	ldr r1, _022498E0 ; =MOD18_02249F2C
	cmp r0, r1
	beq _02249886
	ldr r1, _022498E4 ; =MOD18_0224AA4C
	cmp r0, r1
	beq _02249886
	ldr r1, _022498E8 ; =MOD18_0224A30C
	cmp r0, r1
	bne _022498AC
_02249886:
	mov r0, #4
	bl FUN_0205EB38
	str r0, [r4, #8]
	mov r1, #0xc8
	mov r2, #0x14
	mov r3, #0x7a
	bl FUN_0205EC48
	mov r1, #0
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r4, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_022498AC:
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022498CC
	add r0, r4, #0
	bl MOD18_022491D0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl FUN_02001C5C
	mov r0, #0x7e
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_022498CC:
	mov r1, #0x8f
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r0, r4, #0
	blx r1
_022498D6:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_022498DC: .word MOD18_02249B50
_022498E0: .word MOD18_02249F2C
_022498E4: .word MOD18_0224AA4C
_022498E8: .word MOD18_0224A30C
	thumb_func_end MOD18_022497C8

	thumb_func_start MOD18_022498EC
MOD18_022498EC: ; 0x022498EC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	beq _02249902
	mov r1, #0
	add r2, r1, #0
	bl MOD18_02244318
	mov r0, #0
	str r0, [r4, #0x4c]
_02249902:
	ldr r0, [r4, #0x48]
	cmp r0, #0
	beq _02249916
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
	mov r0, #0
	str r0, [r4, #0x48]
	b _02249936
_02249916:
	mov r0, #0x7e
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02249936
	add r0, r4, #0
	bl MOD18_022491D0
	ldr r0, [r4, #0x54]
	mov r1, #0
	bl FUN_02001C5C
	mov r0, #0x7e
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
_02249936:
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019048
	cmp r0, #0
	beq _02249968
	add r0, r4, #0
	add r0, #0x10
	mov r1, #1
	bl FUN_0200CCF8
	ldrb r1, [r4, #0x14]
	ldr r0, [r4, #0x10]
	bl FUN_0201AC68
	add r0, r4, #0
	add r0, #0x10
	bl FUN_02019178
	ldr r0, [r4, #0x40]
	bl ListMenuItems_dtor
	add r0, r4, #0
	bl MOD18_0224CBAC
_02249968:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_022498EC

	thumb_func_start MOD18_0224996C
MOD18_0224996C: ; 0x0224996C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r5, r0, #0
	mov r0, #6
	str r0, [sp, #0x1c]
	mov r0, #0x19
	mov r7, #0xb
	str r0, [sp, #0x18]
	cmp r1, #1
	beq _0224998A
	cmp r1, #2
	beq _02249990
	cmp r1, #3
	beq _02249998
	b _022499A2
_0224998A:
	mov r6, #3
	ldr r4, _02249A4C ; =0x02251270
	b _022499A2
_02249990:
	mov r6, #2
	mov r7, #0xd
	ldr r4, _02249A50 ; =0x02251260
	b _022499A2
_02249998:
	mov r0, #0x14
	ldr r4, _02249A54 ; =0x02251288
	mov r6, #3
	str r7, [sp, #0x1c]
	str r0, [sp, #0x18]
_022499A2:
	add r0, r6, #0
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x44]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	ldr r3, [sp, #0x18]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #4]
	lsl r0, r6, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02249A58 ; =0x000002E7
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	lsl r3, r3, #0x18
	ldr r0, [r0, #8]
	add r1, #0x20
	mov r2, #3
	lsr r3, r3, #0x18
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _02249A5C ; =0x000003D9
	add r0, #0x20
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	mov r7, #0
	str r0, [sp, #0x14]
	cmp r6, #0
	ble _02249A0E
_022499FA:
	ldr r0, [r5, #0x44]
	ldr r1, [sp, #0x14]
	ldr r2, [r4]
	ldr r3, [r4, #4]
	bl ListMenuItems_AppendFromMsgData
	add r7, r7, #1
	add r4, #8
	cmp r7, r6
	blt _022499FA
_02249A0E:
	ldr r4, _02249A60 ; =0x02250598
	add r3, sp, #0x20
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	lsl r0, r6, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x20
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	ldr r0, [r5, #0x44]
	mov r1, #0
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r0, #0x20
	str r0, [sp, #0x2c]
	add r0, r2, #0
	add r2, r1, #0
	mov r3, #4
	str r5, [sp, #0x3c]
	bl ListMenuInit
	str r0, [r5, #0x50]
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02249A4C: .word MOD18_02251270
_02249A50: .word MOD18_02251260
_02249A54: .word MOD18_02251288
_02249A58: .word 0x000002E7
_02249A5C: .word 0x000003D9
_02249A60: .word MOD18_02250598
	thumb_func_end MOD18_0224996C

	thumb_func_start MOD18_02249A64
MOD18_02249A64: ; 0x02249A64
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	cmp r0, #0
	beq _02249A8C
	mov r1, #0
	add r2, r1, #0
	bl DestroyListMenu
	add r1, r4, #0
	add r1, #0x24
	ldrb r1, [r1]
	ldr r0, [r4, #0x20]
	bl FUN_0201AC68
	ldr r0, [r4, #0x44]
	bl ListMenuItems_dtor
	mov r0, #0
	str r0, [r4, #0x50]
_02249A8C:
	add r0, r4, #0
	add r0, #0x20
	bl FUN_02019048
	cmp r0, #0
	beq _02249AAA
	add r0, r4, #0
	add r0, #0x20
	mov r1, #1
	bl FUN_0200CCF8
	add r4, #0x20
	add r0, r4, #0
	bl FUN_02019178
_02249AAA:
	pop {r4, pc}
	thumb_func_end MOD18_02249A64

	thumb_func_start MOD18_02249AAC
MOD18_02249AAC: ; 0x02249AAC
	push {r4, lr}
	add r4, r0, #0
	bl MOD18_022498EC
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _02249AC2
	bl FUN_0205EBEC
	mov r0, #0
	str r0, [r4, #8]
_02249AC2:
	ldr r0, _02249AD4 ; =0x00000246
	mov r1, #0
	strb r1, [r4, r0]
	bl MOD18_0223D678
	bl MOD18_0224DD94
	pop {r4, pc}
	nop
_02249AD4: .word 0x00000246
	thumb_func_end MOD18_02249AAC

	thumb_func_start MOD18_02249AD8
MOD18_02249AD8: ; 0x02249AD8
	push {r3, lr}
	ldr r1, _02249AF0 ; =0x022513F8
	ldr r2, [r1]
	ldrb r1, [r2, #5]
	cmp r1, r0
	bne _02249AEC
	ldrb r1, [r2, #4]
	ldr r0, [r2]
	bl FUN_02026264
_02249AEC:
	pop {r3, pc}
	nop
_02249AF0: .word MOD18_022513F8
	thumb_func_end MOD18_02249AD8

	thumb_func_start MOD18_02249AF4
MOD18_02249AF4: ; 0x02249AF4
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	mov r2, #0x81
	add r1, r0, #0
	lsl r2, r2, #2
	ldr r2, [r1, r2]
	add r0, r4, #0
	blx r2
	mov r1, #1
	mvn r1, r1
	cmp r4, r1
	bne _02249B16
	mov r4, #0x44
	b _02249B1A
_02249B16:
	add r4, r0, #0
	add r4, #0x22
_02249B1A:
	bl MOD18_0223D678
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02249AF4

	thumb_func_start MOD18_02249B2C
MOD18_02249B2C: ; 0x02249B2C
	mov r1, #2
	ldr r2, _02249B44 ; =MOD18_02249338
	lsl r1, r1, #8
	str r2, [r0, r1]
	ldr r2, _02249B48 ; =MOD18_022493DC
	add r1, r1, #4
	str r2, [r0, r1]
	mov r1, #0
	ldr r3, _02249B4C ; =MOD18_02249BA8
	str r1, [r0, #0x64]
	bx r3
	nop
_02249B44: .word MOD18_02249338
_02249B48: .word MOD18_022493DC
_02249B4C: .word MOD18_02249BA8
	thumb_func_end MOD18_02249B2C

	thumb_func_start MOD18_02249B50
MOD18_02249B50: ; 0x02249B50
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #8
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r2, _02249B98 ; =MOD18_02249338
	sub r0, #0x30
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, _02249B9C ; =MOD18_022493DC
	sub r0, #0x2c
	str r2, [r4, r0]
	ldr r0, _02249BA0 ; =MOD18_02249AF4
	str r0, [r4, #0x60]
	mov r0, #0
	str r0, [r4, #0x64]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r1, #0x1c
	strh r0, [r4, r1]
	ldr r1, _02249BA4 ; =0x020262BD
	add r0, r4, #0
	bl MOD18_02249BA8
	pop {r4, pc}
	nop
_02249B98: .word MOD18_02249338
_02249B9C: .word MOD18_022493DC
_02249BA0: .word MOD18_02249AF4
_02249BA4: .word FUN_020262BC
	thumb_func_end MOD18_02249B50

	thumb_func_start MOD18_02249BA8
MOD18_02249BA8: ; 0x02249BA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r1, [sp, #0x14]
	mov r1, #0x81
	add r5, r0, #0
	lsl r1, r1, #2
	ldr r7, [r5, r1]
	sub r1, r1, #4
	ldr r1, [r5, r1]
	blx r1
	add r6, r0, #0
	add r0, r5, #0
	bl MOD18_022498EC
	bl MOD18_0223D678
	ldr r1, _02249CB0 ; =0x0000023B
	mov r2, #0
	bl MOD18_0224DB80
	add r0, r6, #1
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _02249CB4 ; =0x00000257
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _02249CB8 ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	bl MOD18_0223D678
	bl MOD18_0224DBB4
	mov r4, #0
	str r0, [sp, #0x18]
	cmp r6, #0
	ble _02249C30
_02249C18:
	add r0, r4, #0
	add r1, r5, #0
	blx r7
	add r2, r0, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r4, r4, #1
	cmp r4, r6
	blt _02249C18
_02249C30:
	mov r2, #0x22
	add r3, r2, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	sub r3, #0x24
	bl ListMenuItems_AppendFromMsgData
	ldr r3, _02249CBC ; =0x02250598
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r6, #1
	add r2, sp, #0x1c
	strh r0, [r2, #0x10]
	mov r1, #6
	strh r1, [r2, #0x12]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x28]
	ldr r0, [r5, #0x60]
	str r0, [sp, #0x20]
	ldr r0, [r5, #0x64]
	str r0, [sp, #0x24]
	str r5, [sp, #0x38]
	ldrh r2, [r2, #0x10]
	add r0, r5, #0
	bl MOD18_0224AFB0
	ldr r0, [sp, #0x14]
	mov r2, #0x23
	str r0, [sp]
	ldr r0, _02249CC0 ; =0x022513F8
	lsl r2, r2, #4
	ldr r0, [r0]
	mov r3, #4
	ldr r0, [r0]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x1c
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl MOD18_02244028
	str r0, [r5, #0x4c]
	ldr r0, _02249CC4 ; =0x00000246
	mov r1, #5
	strb r1, [r5, r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_02249CB0: .word 0x0000023B
_02249CB4: .word 0x00000257
_02249CB8: .word 0x000003D9
_02249CBC: .word MOD18_02250598
_02249CC0: .word MOD18_022513F8
_02249CC4: .word 0x00000246
	thumb_func_end MOD18_02249BA8

	thumb_func_start MOD18_02249CC8
MOD18_02249CC8: ; 0x02249CC8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #8
	bl MOD18_0223E57C
	ldr r0, [r5, #0x4c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r1, sp, #0
	add r2, r0, #0
	ldrh r1, [r1, #2]
	add r0, r5, #0
	mov r3, #6
	bl MOD18_0224B004
	bl FUN_020311F0
	cmp r0, #0
	beq _02249D12
	mov r4, #1
	mvn r4, r4
_02249D12:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _02249D1C
	add r4, r0, #0
_02249D1C:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02249D2E
	add r0, r0, #1
	cmp r4, r0
	bne _02249D36
	mov r0, #0
	pop {r3, r4, r5, pc}
_02249D2E:
	add r0, r5, #0
	bl MOD18_02249AAC
	b _02249DAC
_02249D36:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	ldr r0, _02249DB0 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	strb r4, [r0, #4]
	add r0, r4, #0
	bl MOD18_022493DC
	ldr r1, _02249DB0 ; =0x022513F8
	ldr r2, [r1]
	strb r0, [r2, #5]
	ldr r0, [r1]
	ldrb r0, [r0, #5]
	cmp r0, #0x21
	bne _02249D66
	bl MOD18_02246AE4
	ldr r0, _02249DB4 ; =0x00000246
	mov r1, #3
	strb r1, [r5, r0]
	b _02249D98
_02249D66:
	add r0, r5, #0
	bl MOD18_022498EC
	add r0, r5, #0
	mov r1, #1
	bl MOD18_0224996C
	ldr r0, _02249DB4 ; =0x00000246
	mov r1, #0x12
	strb r1, [r5, r0]
	bl MOD18_0223D638
	ldr r2, _02249DB0 ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DF04
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x81
	add r3, r2, #0
	bl MOD18_0224DCD8
_02249D98:
	mov r1, #0
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r5, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_02249DAC:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_02249DB0: .word MOD18_022513F8
_02249DB4: .word 0x00000246
	thumb_func_end MOD18_02249CC8

	thumb_func_start MOD18_02249DB8
MOD18_02249DB8: ; 0x02249DB8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x50]
	bl ListMenu_ProcessInput
	mov r1, #0x93
	add r4, r0, #0
	lsl r1, r1, #2
	ldrh r6, [r5, r1]
	ldr r0, [r5, #0x50]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	mov r0, #0x93
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r6, r0
	beq _02249DE2
	ldr r0, _02249E80 ; =0x000005DC
	bl FUN_020054C8
_02249DE2:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _02249DF4
	add r0, r0, #1
	cmp r4, r0
	bne _02249E0E
	mov r0, #0
	pop {r4, r5, r6, pc}
_02249DF4:
	ldr r0, _02249E80 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD18_02249A64
	add r0, r5, #0
	bl MOD18_02249B50
	ldr r0, _02249E84 ; =0x00000246
	mov r1, #5
	strb r1, [r5, r0]
	b _02249E7C
_02249E0E:
	add r0, r5, #0
	bl MOD18_02249A64
	cmp r4, #1
	bne _02249E3A
	ldr r0, _02249E88 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	ldrb r0, [r0, #4]
	bl MOD18_022493DC
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl MOD18_0223EF60
	ldr r0, _02249E8C ; =0x00000631
	bl FUN_020054C8
	ldr r0, _02249E84 ; =0x00000246
	mov r1, #3
	strb r1, [r5, r0]
	b _02249E7C
_02249E3A:
	cmp r4, #2
	bne _02249E7C
	ldr r0, _02249E80 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _02249E88 ; =0x022513F8
	ldr r0, [r0]
	ldrb r0, [r0, #5]
	bl MOD18_02249AD8
	bl MOD18_0223D638
	ldr r2, _02249E88 ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DF04
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x82
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _02249E90 ; =MOD18_02249B50
	mov r1, #5
	str r0, [r5]
	ldr r0, _02249E94 ; =0x00000245
	strb r1, [r5, r0]
	mov r1, #0xe
	add r0, r0, #1
	strb r1, [r5, r0]
_02249E7C:
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_02249E80: .word 0x000005DC
_02249E84: .word 0x00000246
_02249E88: .word MOD18_022513F8
_02249E8C: .word 0x00000631
_02249E90: .word MOD18_02249B50
_02249E94: .word 0x00000245
	thumb_func_end MOD18_02249DB8

	thumb_func_start MOD18_02249E98
MOD18_02249E98: ; 0x02249E98
	push {r3, lr}
	ldr r1, _02249EB8 ; =0x022513F8
	ldr r1, [r1]
	ldrb r1, [r1, #5]
	cmp r1, r0
	beq _02249EA8
	bl ErrorHandling
_02249EA8:
	ldr r0, _02249EB8 ; =0x022513F8
	ldr r1, [r0]
	ldr r0, [r1]
	ldrb r1, [r1, #4]
	bl FUN_02026080
	pop {r3, pc}
	nop
_02249EB8: .word MOD18_022513F8
	thumb_func_end MOD18_02249E98

	thumb_func_start MOD18_02249EBC
MOD18_02249EBC: ; 0x02249EBC
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	mov r2, #0x81
	add r1, r0, #0
	lsl r2, r2, #2
	ldr r2, [r1, r2]
	add r0, r4, #0
	blx r2
	mov r1, #1
	mvn r1, r1
	cmp r4, r1
	bne _02249EDE
	mov r4, #0x3d
	b _02249EE2
_02249EDE:
	add r4, r0, #0
	add r4, #0x3e
_02249EE2:
	bl MOD18_0223D678
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_02249EBC

	thumb_func_start MOD18_02249EF4
MOD18_02249EF4: ; 0x02249EF4
	mov r2, #2
	ldr r1, _02249F14 ; =MOD18_022493C8
	lsl r2, r2, #8
	str r1, [r0, r2]
	add r1, r2, #4
	ldr r3, _02249F18 ; =MOD18_022493F4
	add r2, #8
	str r3, [r0, r1]
	ldr r1, _02249F1C ; =MOD18_0224940C
	ldr r3, _02249F20 ; =MOD18_02249F8C
	str r1, [r0, r2]
	ldr r1, _02249F24 ; =MOD18_02249EBC
	str r1, [r0, #0x60]
	ldr r1, _02249F28 ; =FUN_020260EC
	bx r3
	nop
_02249F14: .word MOD18_022493C8
_02249F18: .word MOD18_022493F4
_02249F1C: .word MOD18_0224940C
_02249F20: .word MOD18_02249F8C
_02249F24: .word MOD18_02249EBC
_02249F28: .word FUN_020260EC
	thumb_func_end MOD18_02249EF4

	thumb_func_start MOD18_02249F2C
MOD18_02249F2C: ; 0x02249F2C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #9
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #9
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r2, _02249F78 ; =MOD18_022493C8
	sub r0, #0x30
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, _02249F7C ; =MOD18_022493F4
	sub r0, #0x2c
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, _02249F80 ; =MOD18_0224940C
	sub r0, #0x28
	str r2, [r4, r0]
	ldr r0, _02249F84 ; =MOD18_02249EBC
	str r0, [r4, #0x60]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r1, #0x1c
	strh r0, [r4, r1]
	ldr r1, _02249F88 ; =FUN_020260EC
	add r0, r4, #0
	bl MOD18_02249F8C
	pop {r4, pc}
	nop
_02249F78: .word MOD18_022493C8
_02249F7C: .word MOD18_022493F4
_02249F80: .word MOD18_0224940C
_02249F84: .word MOD18_02249EBC
_02249F88: .word FUN_020260EC
	thumb_func_end MOD18_02249F2C

	thumb_func_start MOD18_02249F8C
MOD18_02249F8C: ; 0x02249F8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	mov r2, #0x81
	add r5, r0, #0
	lsl r2, r2, #2
	str r1, [sp, #0x14]
	ldr r1, [r5, r2]
	str r1, [sp, #0x1c]
	add r1, r2, #4
	ldr r7, [r5, r1]
	sub r1, r2, #4
	ldr r1, [r5, r1]
	blx r1
	add r6, r0, #0
	add r0, r5, #0
	bl MOD18_022498EC
	bl MOD18_0223D678
	ldr r1, _0224A0D4 ; =0x00000239
	mov r2, #0
	bl MOD18_0224DB80
	add r0, r6, #1
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224A0D8 ; =0x00000257
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224A0DC ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	bl MOD18_0223D678
	bl MOD18_0224DBB4
	mov r4, #0
	str r0, [sp, #0x18]
	cmp r6, #0
	ble _0224A058
_0224A002:
	ldr r2, [sp, #0x1c]
	add r0, r4, #0
	add r1, r5, #0
	blx r2
	add r2, r0, #0
	ldr r0, [r5, #0x70]
	mov r1, #2
	bl BufferUndergroundItemName
	add r0, r4, #0
	add r1, r5, #0
	blx r7
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r5, #0x70]
	mov r1, #6
	mov r3, #2
	bl BufferIntegerAsString
	bl MOD18_0223D638
	bl MOD18_0224DBB4
	ldr r2, [r5, #0x6c]
	mov r1, #0x80
	bl ReadMsgDataIntoString
	ldr r0, [r5, #0x70]
	ldr r1, [r5, #0x68]
	ldr r2, [r5, #0x6c]
	bl StringExpandPlaceholders
	ldr r0, [r5, #0x40]
	ldr r1, [r5, #0x68]
	add r2, r4, #0
	bl ListMenuItems_AddItem
	add r4, r4, #1
	cmp r4, r6
	blt _0224A002
_0224A058:
	mov r2, #0x3c
	add r3, r2, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	sub r3, #0x3e
	bl ListMenuItems_AppendFromMsgData
	ldr r3, _0224A0E0 ; =0x02250598
	add r2, sp, #0x20
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r6, #1
	add r2, sp, #0x20
	strh r0, [r2, #0x10]
	mov r1, #6
	strh r1, [r2, #0x12]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x2c]
	ldr r0, [r5, #0x60]
	str r0, [sp, #0x24]
	str r5, [sp, #0x3c]
	ldrh r2, [r2, #0x10]
	add r0, r5, #0
	bl MOD18_0224AFB0
	ldr r0, [sp, #0x14]
	mov r2, #0x23
	str r0, [sp]
	ldr r0, _0224A0E4 ; =0x022513F8
	lsl r2, r2, #4
	ldr r0, [r0]
	mov r3, #4
	ldr r0, [r0]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x20
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl MOD18_02244028
	str r0, [r5, #0x4c]
	ldr r0, _0224A0E8 ; =0x00000246
	mov r1, #6
	strb r1, [r5, r0]
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224A0D4: .word 0x00000239
_0224A0D8: .word 0x00000257
_0224A0DC: .word 0x000003D9
_0224A0E0: .word MOD18_02250598
_0224A0E4: .word MOD18_022513F8
_0224A0E8: .word 0x00000246
	thumb_func_end MOD18_02249F8C

	thumb_func_start MOD18_0224A0EC
MOD18_0224A0EC: ; 0x0224A0EC
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #9
	bl MOD18_0223E57C
	ldr r0, [r5, #0x4c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r1, sp, #0
	add r2, r0, #0
	ldrh r1, [r1, #2]
	add r0, r5, #0
	mov r3, #6
	bl MOD18_0224B004
	bl FUN_020311F0
	cmp r0, #0
	beq _0224A136
	mov r4, #1
	mvn r4, r4
_0224A136:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224A140
	add r4, r0, #0
_0224A140:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224A152
	add r0, r0, #1
	cmp r4, r0
	bne _0224A15A
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224A152:
	add r0, r5, #0
	bl MOD18_02249AAC
	b _0224A1B4
_0224A15A:
	add r0, r5, #0
	bl MOD18_022498EC
	ldr r0, _0224A1B8 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	strb r4, [r0, #4]
	add r0, r4, #0
	bl MOD18_022493F4
	ldr r1, _0224A1B8 ; =0x022513F8
	ldr r1, [r1]
	strb r0, [r1, #5]
	add r0, r5, #0
	mov r1, #1
	bl MOD18_0224996C
	ldr r0, _0224A1BC ; =0x00000246
	mov r1, #0x10
	strb r1, [r5, r0]
	bl MOD18_0223D638
	ldr r2, _0224A1B8 ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DEF0
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x81
	add r3, r2, #0
	bl MOD18_0224DCD8
	mov r1, #0
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r5, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_0224A1B4:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224A1B8: .word MOD18_022513F8
_0224A1BC: .word 0x00000246
	thumb_func_end MOD18_0224A0EC

	thumb_func_start MOD18_0224A1C0
MOD18_0224A1C0: ; 0x0224A1C0
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x50]
	bl ListMenu_ProcessInput
	mov r1, #0x93
	add r4, r0, #0
	lsl r1, r1, #2
	ldrh r6, [r5, r1]
	ldr r0, [r5, #0x50]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	mov r0, #0x93
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r6, r0
	beq _0224A1EA
	ldr r0, _0224A2A0 ; =0x000005DC
	bl FUN_020054C8
_0224A1EA:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224A1FC
	add r0, r0, #1
	cmp r4, r0
	bne _0224A216
	mov r0, #0
	pop {r4, r5, r6, pc}
_0224A1FC:
	ldr r0, _0224A2A0 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD18_02249A64
	add r0, r5, #0
	bl MOD18_02249F2C
	ldr r0, _0224A2A4 ; =0x00000246
	mov r1, #6
	strb r1, [r5, r0]
	b _0224A29C
_0224A216:
	add r0, r5, #0
	bl MOD18_02249A64
	cmp r4, #1
	bne _0224A25A
	bl FUN_02031190
	add r4, r0, #0
	bl FUN_0204E4D4
	add r6, r0, #0
	add r0, r4, #0
	bl FUN_0204E50C
	add r4, r0, #0
	bl MOD18_0223D678
	bl MOD18_0224DD94
	ldr r0, _0224A2A8 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	ldrb r0, [r0, #4]
	bl MOD18_0224940C
	add r1, r0, #0
	ldr r0, _0224A2A8 ; =0x022513F8
	add r2, r6, #0
	ldr r0, [r0]
	add r3, r4, #0
	ldrb r0, [r0, #5]
	bl MOD18_0223CF9C
	b _0224A28C
_0224A25A:
	cmp r4, #2
	bne _0224A28C
	ldr r0, _0224A2A0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224A2A8 ; =0x022513F8
	ldr r0, [r0]
	ldrb r0, [r0, #5]
	bl MOD18_02249E98
	bl MOD18_0223D638
	ldr r2, _0224A2A8 ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DEF0
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x82
	add r3, r2, #0
	bl MOD18_0224DCB8
_0224A28C:
	ldr r0, _0224A2AC ; =MOD18_02249F2C
	mov r1, #6
	str r0, [r5]
	ldr r0, _0224A2B0 ; =0x00000245
	strb r1, [r5, r0]
	mov r1, #0xe
	add r0, r0, #1
	strb r1, [r5, r0]
_0224A29C:
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224A2A0: .word 0x000005DC
_0224A2A4: .word 0x00000246
_0224A2A8: .word MOD18_022513F8
_0224A2AC: .word MOD18_02249F2C
_0224A2B0: .word 0x00000245
	thumb_func_end MOD18_0224A1C0

	thumb_func_start MOD18_0224A2B4
MOD18_0224A2B4: ; 0x0224A2B4
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	mov r2, #0x81
	add r1, r0, #0
	lsl r2, r2, #2
	ldr r2, [r1, r2]
	add r0, r4, #0
	blx r2
	mov r1, #1
	mvn r1, r1
	cmp r4, r1
	bne _0224A2D6
	mov r4, #0x3d
	b _0224A2DA
_0224A2D6:
	add r4, r0, #0
	add r4, #0x3e
_0224A2DA:
	bl MOD18_0223D678
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224A2B4

	thumb_func_start MOD18_0224A2EC
MOD18_0224A2EC: ; 0x0224A2EC
	mov r1, #2
	ldr r2, _0224A300 ; =MOD18_02249424
	lsl r1, r1, #8
	str r2, [r0, r1]
	ldr r2, _0224A304 ; =MOD18_02249438
	add r1, r1, #4
	str r2, [r0, r1]
	ldr r3, _0224A308 ; =MOD18_0224A360
	mov r1, #0
	bx r3
	.align 2, 0
_0224A300: .word MOD18_02249424
_0224A304: .word MOD18_02249438
_0224A308: .word MOD18_0224A360
	thumb_func_end MOD18_0224A2EC

	thumb_func_start MOD18_0224A30C
MOD18_0224A30C: ; 0x0224A30C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xb
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r2, _0224A350 ; =MOD18_02249424
	sub r0, #0x30
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, _0224A354 ; =MOD18_02249438
	sub r0, #0x2c
	str r2, [r4, r0]
	ldr r0, _0224A358 ; =MOD18_0224A2B4
	str r0, [r4, #0x60]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r1, #0x1c
	strh r0, [r4, r1]
	ldr r1, _0224A35C ; =FUN_020261EC
	add r0, r4, #0
	bl MOD18_0224A360
	pop {r4, pc}
	nop
_0224A350: .word MOD18_02249424
_0224A354: .word MOD18_02249438
_0224A358: .word MOD18_0224A2B4
_0224A35C: .word FUN_020261EC
	thumb_func_end MOD18_0224A30C

	thumb_func_start MOD18_0224A360
MOD18_0224A360: ; 0x0224A360
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r1, [sp, #0x14]
	mov r1, #0x81
	add r5, r0, #0
	lsl r1, r1, #2
	ldr r7, [r5, r1]
	sub r1, r1, #4
	ldr r1, [r5, r1]
	blx r1
	add r6, r0, #0
	add r0, r5, #0
	bl MOD18_022498EC
	bl MOD18_0223D678
	ldr r1, _0224A464 ; =0x00000239
	mov r2, #0
	bl MOD18_0224DB80
	add r0, r6, #1
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224A468 ; =0x00000257
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224A46C ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	bl MOD18_0223D678
	bl MOD18_0224DBB4
	mov r4, #0
	str r0, [sp, #0x18]
	cmp r6, #0
	ble _0224A3E8
_0224A3D0:
	add r0, r4, #0
	add r1, r5, #0
	blx r7
	add r2, r0, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r4, r4, #1
	cmp r4, r6
	blt _0224A3D0
_0224A3E8:
	mov r2, #0x3c
	add r3, r2, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	sub r3, #0x3e
	bl ListMenuItems_AppendFromMsgData
	ldr r3, _0224A470 ; =0x02250598
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r6, #1
	add r2, sp, #0x1c
	strh r0, [r2, #0x10]
	mov r1, #6
	strh r1, [r2, #0x12]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x28]
	ldr r0, [r5, #0x60]
	str r0, [sp, #0x20]
	str r5, [sp, #0x38]
	ldrh r2, [r2, #0x10]
	add r0, r5, #0
	bl MOD18_0224AFB0
	ldr r0, [sp, #0x14]
	mov r2, #0x23
	str r0, [sp]
	ldr r0, _0224A474 ; =0x022513F8
	lsl r2, r2, #4
	ldr r0, [r0]
	mov r3, #4
	ldr r0, [r0]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x1c
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl MOD18_02244028
	str r0, [r5, #0x4c]
	ldr r0, _0224A478 ; =0x00000246
	mov r1, #7
	strb r1, [r5, r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	nop
_0224A464: .word 0x00000239
_0224A468: .word 0x00000257
_0224A46C: .word 0x000003D9
_0224A470: .word MOD18_02250598
_0224A474: .word MOD18_022513F8
_0224A478: .word 0x00000246
	thumb_func_end MOD18_0224A360

	thumb_func_start MOD18_0224A47C
MOD18_0224A47C: ; 0x0224A47C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0xb
	bl MOD18_0223E57C
	ldr r0, [r5, #0x4c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r1, sp, #0
	add r2, r0, #0
	ldrh r1, [r1, #2]
	add r0, r5, #0
	mov r3, #6
	bl MOD18_0224B004
	bl FUN_020311F0
	cmp r0, #0
	beq _0224A4C6
	mov r4, #1
	mvn r4, r4
_0224A4C6:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224A4D0
	add r4, r0, #0
_0224A4D0:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224A4E2
	add r0, r0, #1
	cmp r4, r0
	bne _0224A4EA
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224A4E2:
	add r0, r5, #0
	bl MOD18_02249AAC
	b _0224A544
_0224A4EA:
	add r0, r5, #0
	bl MOD18_022498EC
	ldr r0, _0224A548 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	strb r4, [r0, #4]
	add r0, r4, #0
	bl MOD18_02249438
	ldr r1, _0224A548 ; =0x022513F8
	ldr r1, [r1]
	strb r0, [r1, #5]
	add r0, r5, #0
	mov r1, #3
	bl MOD18_0224996C
	bl MOD18_0223D638
	ldr r2, _0224A548 ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DEF0
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x81
	add r3, r2, #0
	bl MOD18_0224DCD8
	ldr r0, _0224A54C ; =0x00000246
	mov r1, #0x11
	strb r1, [r5, r0]
	mov r1, #0
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r5, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_0224A544:
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224A548: .word MOD18_022513F8
_0224A54C: .word 0x00000246
	thumb_func_end MOD18_0224A47C

	thumb_func_start MOD18_0224A550
MOD18_0224A550: ; 0x0224A550
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x50]
	bl ListMenu_ProcessInput
	mov r1, #0x93
	add r4, r0, #0
	lsl r1, r1, #2
	ldrh r6, [r5, r1]
	ldr r0, [r5, #0x50]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	mov r0, #0x93
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r6, r0
	beq _0224A57A
	ldr r0, _0224A694 ; =0x000005DC
	bl FUN_020054C8
_0224A57A:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224A58C
	add r0, r0, #1
	cmp r4, r0
	bne _0224A5A6
	mov r0, #0
	pop {r4, r5, r6, pc}
_0224A58C:
	ldr r0, _0224A694 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD18_02249A64
	add r0, r5, #0
	bl MOD18_0224A30C
	ldr r0, _0224A698 ; =0x00000246
	mov r1, #7
	strb r1, [r5, r0]
	b _0224A68E
_0224A5A6:
	add r0, r5, #0
	bl MOD18_02249A64
	cmp r4, #3
	bne _0224A64A
	ldr r0, _0224A69C ; =0x022513F8
	ldr r0, [r0]
	ldrb r0, [r0, #5]
	bl FUN_02025D48
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0xc]
	bl Sav2_Bag_get
	add r6, r0, #0
	ldr r0, _0224A694 ; =0x000005DC
	bl FUN_020054C8
	lsl r1, r4, #0x10
	add r0, r6, #0
	lsr r1, r1, #0x10
	mov r2, #1
	mov r3, #4
	bl Bag_AddItem
	cmp r0, #0
	beq _0224A62A
	ldr r0, _0224A69C ; =0x022513F8
	ldr r1, [r0]
	ldr r0, [r1]
	ldrb r1, [r1, #4]
	bl FUN_02026194
	bl MOD18_0223D638
	ldr r2, _0224A69C ; =0x022513F8
	mov r1, #0
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DEF0
	ldr r0, _0224A69C ; =0x022513F8
	ldr r0, [r0]
	ldrb r0, [r0, #5]
	add r0, #0xe3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #1
	bhi _0224A61A
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x51
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0224A67E
_0224A61A:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x4f
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0224A67E
_0224A62A:
	bl MOD18_0223D638
	ldr r2, _0224A69C ; =0x022513F8
	mov r1, #0
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DEF0
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x50
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0224A67E
_0224A64A:
	cmp r4, #2
	bne _0224A67E
	ldr r0, _0224A694 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224A69C ; =0x022513F8
	ldr r1, [r0]
	ldr r0, [r1]
	ldrb r1, [r1, #4]
	bl FUN_02026194
	bl MOD18_0223D638
	ldr r2, _0224A69C ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DEF0
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x82
	add r3, r2, #0
	bl MOD18_0224DCB8
_0224A67E:
	ldr r0, _0224A6A0 ; =MOD18_0224A30C
	mov r1, #7
	str r0, [r5]
	ldr r0, _0224A6A4 ; =0x00000245
	strb r1, [r5, r0]
	mov r1, #0xe
	add r0, r0, #1
	strb r1, [r5, r0]
_0224A68E:
	mov r0, #1
	pop {r4, r5, r6, pc}
	nop
_0224A694: .word 0x000005DC
_0224A698: .word 0x00000246
_0224A69C: .word MOD18_022513F8
_0224A6A0: .word MOD18_0224A30C
_0224A6A4: .word 0x00000245
	thumb_func_end MOD18_0224A550

	thumb_func_start MOD18_0224A6A8
MOD18_0224A6A8: ; 0x0224A6A8
	ldr r1, _0224A6B0 ; =0x00000246
	mov r2, #2
	strb r2, [r0, r1]
	bx lr
	.align 2, 0
_0224A6B0: .word 0x00000246
	thumb_func_end MOD18_0224A6A8

	thumb_func_start MOD18_0224A6B4
MOD18_0224A6B4: ; 0x0224A6B4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD18_022498EC
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x38]
	bl FUN_02055320
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x38]
	bl FUN_0205532C
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0223E2F4
	cmp r0, #0
	beq _0224A6F0
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x42
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224A70C ; =0x00000246
	mov r1, #0xd
	strb r1, [r5, r0]
	pop {r3, r4, r5, pc}
_0224A6F0:
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x34
	add r3, r2, #0
	bl MOD18_0224DCB8
	mov r1, #0x8a
	lsl r1, r1, #2
	str r0, [r5, r1]
	mov r0, #0xb
	add r1, #0x1e
	strb r0, [r5, r1]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224A70C: .word 0x00000246
	thumb_func_end MOD18_0224A6B4

	thumb_func_start MOD18_0224A710
MOD18_0224A710: ; 0x0224A710
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224A73C
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0xc]
	ldr r1, _0224A740 ; =0x0225056C
	ldr r0, [r0, #8]
	ldr r2, _0224A744 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x5c]
	ldr r0, _0224A748 ; =0x00000246
	mov r1, #0xc
	strb r1, [r4, r0]
_0224A73C:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0224A740: .word MOD18_0225056C
_0224A744: .word 0x000003D9
_0224A748: .word 0x00000246
	thumb_func_end MOD18_0224A710

	thumb_func_start MOD18_0224A74C
MOD18_0224A74C: ; 0x0224A74C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x5c]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0224A77E
	cmp r0, #0
	bne _0224A76C
	ldr r0, _0224A780 ; =0x00000246
	mov r1, #0xf
	strb r1, [r4, r0]
	b _0224A77A
_0224A76C:
	bl MOD18_0223D638
	bl MOD18_0224DD94
	add r0, r4, #0
	bl MOD18_02249AAC
_0224A77A:
	mov r0, #0
	str r0, [r4, #0x5c]
_0224A77E:
	pop {r4, pc}
	.align 2, 0
_0224A780: .word 0x00000246
	thumb_func_end MOD18_0224A74C

	thumb_func_start MOD18_0224A784
MOD18_0224A784: ; 0x0224A784
	ldr r3, _0224A788 ; =MOD18_02249AAC
	bx r3
	.align 2, 0
_0224A788: .word MOD18_02249AAC
	thumb_func_end MOD18_0224A784

	thumb_func_start MOD18_0224A78C
MOD18_0224A78C: ; 0x0224A78C
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD18_022498EC
	bl MOD18_0224D704
	ldr r0, [r4, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r1, r0, #0
	mov r0, #1
	str r0, [sp]
	ldr r0, [r4, #0xc]
	ldr r2, _0224A7C0 ; =MOD18_0224A784
	ldr r0, [r0, #8]
	add r3, r4, #0
	bl MOD18_0224D5CC
	ldr r0, _0224A7C4 ; =0x00000246
	mov r1, #0xa
	strb r1, [r4, r0]
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0224A7C0: .word MOD18_0224A784
_0224A7C4: .word 0x00000246
	thumb_func_end MOD18_0224A78C

	thumb_func_start MOD18_0224A7C8
MOD18_0224A7C8: ; 0x0224A7C8
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x25
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x25
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x7f
	str r6, [r4, #0xc]
	lsl r0, r0, #2
	str r5, [r4, r0]
	mov r1, #0
	add r0, #0x4a
	strb r1, [r4, r0]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x68]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x6c]
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r4, #0x70]
	bl FUN_0204F7E4
	bl MOD18_0223D648
	mov r1, #0
	add r2, r1, #0
	add r3, r1, #0
	bl MOD18_0224DCB8
	ldr r0, _0224A838 ; =MOD18_0224A914
	ldr r2, _0224A83C ; =0x00002710
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	ldr r1, [r4, #4]
	ldr r2, _0224A840 ; =MOD18_0224AFE8
	add r0, r4, #0
	bl MOD18_0223E688
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224A838: .word MOD18_0224A914
_0224A83C: .word 0x00002710
_0224A840: .word MOD18_0224AFE8
	thumb_func_end MOD18_0224A7C8

	thumb_func_start MOD18_0224A844
MOD18_0224A844: ; 0x0224A844
	push {r3, r4, lr}
	sub sp, #4
	add r4, r0, #0
	bl MOD18_0223D648
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224A870
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0xc]
	ldr r1, _0224A874 ; =0x0225056C
	ldr r0, [r0, #8]
	ldr r2, _0224A878 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x5c]
	ldr r0, _0224A87C ; =0x00000246
	mov r1, #1
	strb r1, [r4, r0]
_0224A870:
	add sp, #4
	pop {r3, r4, pc}
	.align 2, 0
_0224A874: .word MOD18_0225056C
_0224A878: .word 0x000003D9
_0224A87C: .word 0x00000246
	thumb_func_end MOD18_0224A844

	thumb_func_start MOD18_0224A880
MOD18_0224A880: ; 0x0224A880
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x5c]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0224A8A6
	cmp r0, #0
	bne _0224A89C
	mov r1, #3
	b _0224A89E
_0224A89C:
	mov r1, #2
_0224A89E:
	ldr r0, _0224A8A8 ; =0x00000246
	strb r1, [r4, r0]
	mov r0, #0
	str r0, [r4, #0x5c]
_0224A8A6:
	pop {r4, pc}
	.align 2, 0
_0224A8A8: .word 0x00000246
	thumb_func_end MOD18_0224A880

	thumb_func_start MOD18_0224A8AC
MOD18_0224A8AC: ; 0x0224A8AC
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	ldr r0, [r5, #0x5c]
	add r4, r2, #0
	cmp r0, #0
	beq _0224A8C0
	mov r1, #4
	bl FUN_020021EC
_0224A8C0:
	ldr r0, [r5, #0x68]
	bl String_dtor
	ldr r0, [r5, #0x6c]
	bl String_dtor
	ldr r0, [r5, #0x70]
	bl ScrStrBufs_delete
	bl MOD18_0223D648
	bl MOD18_0224DD94
	bl MOD18_0223D638
	bl MOD18_0224DD94
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	cmp r1, #0
	beq _0224A8F0
	mov r0, #0
	blx r1
_0224A8F0:
	mov r0, #0
	str r0, [r5, #4]
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _0224A8FE
	bl FUN_0205EBEC
_0224A8FE:
	add r0, r5, #0
	bl FreeToHeap
	cmp r4, #0
	bne _0224A90C
	bl FUN_0204F7FC
_0224A90C:
	add r0, r6, #0
	bl FUN_0200CAB4
	pop {r4, r5, r6, pc}
	thumb_func_end MOD18_0224A8AC

	thumb_func_start MOD18_0224A914
MOD18_0224A914: ; 0x0224A914
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl FUN_02031190
	bl FUN_0204EE9C
	cmp r0, #0
	bne _0224A932
	ldr r0, _0224A9AC ; =0x00000246
	ldrb r1, [r4, r0]
	cmp r1, #1
	bhi _0224A932
	mov r1, #2
	strb r1, [r4, r0]
_0224A932:
	ldr r0, _0224A9AC ; =0x00000246
	ldrb r0, [r4, r0]
	cmp r0, #4
	bhi _0224A9AA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224A946: ; jump table
	.short _0224A950 - _0224A946 - 2 ; case 0
	.short _0224A958 - _0224A946 - 2 ; case 1
	.short _0224A960 - _0224A946 - 2 ; case 2
	.short _0224A970 - _0224A946 - 2 ; case 3
	.short _0224A98E - _0224A946 - 2 ; case 4
_0224A950:
	add r0, r4, #0
	bl MOD18_0224A844
	pop {r3, r4, r5, pc}
_0224A958:
	add r0, r4, #0
	bl MOD18_0224A880
	pop {r3, r4, r5, pc}
_0224A960:
	bl MOD18_0223E6A0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0
	bl MOD18_0224A8AC
	pop {r3, r4, r5, pc}
_0224A970:
	bl MOD18_0223E6A0
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #1
	bl MOD18_0224A8AC
	mov r1, #0
	add r0, sp, #0
	strb r1, [r0]
	mov r0, #0x54
	add r1, sp, #0
	bl FUN_020311D0
	pop {r3, r4, r5, pc}
_0224A98E:
	bl MOD18_0223D648
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224A9AA
	ldr r0, _0224A9B0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0224A9AA
	ldr r0, _0224A9AC ; =0x00000246
	mov r1, #2
	strb r1, [r4, r0]
_0224A9AA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224A9AC: .word 0x00000246
_0224A9B0: .word gMain
	thumb_func_end MOD18_0224A914

	thumb_func_start MOD18_0224A9B4
MOD18_0224A9B4: ; 0x0224A9B4
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	mov r2, #0x81
	add r1, r0, #0
	lsl r2, r2, #2
	ldr r2, [r1, r2]
	add r0, r4, #0
	blx r2
	mov r1, #1
	mvn r1, r1
	cmp r4, r1
	bne _0224A9D6
	mov r4, #0x8b
	b _0224A9DA
_0224A9D6:
	add r4, r0, #0
	add r4, #0x8a
_0224A9DA:
	bl MOD18_0223D678
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224A9B4

	thumb_func_start MOD18_0224A9EC
MOD18_0224A9EC: ; 0x0224A9EC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x13
	add r5, r0, #0
	bl ListMenuGetTemplateField
	ldr r0, [r0, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r4, #0
	bl FUN_02025F0C
	cmp r0, #0
	bne _0224AA1A
	add r0, r5, #0
	mov r1, #1
	mov r2, #0xf
	mov r3, #2
	bl ListMenuOverrideSetColors
	pop {r3, r4, r5, pc}
_0224AA1A:
	mov r1, #2
	add r0, r5, #0
	mov r2, #0xf
	add r3, r1, #0
	bl ListMenuOverrideSetColors
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224A9EC

	thumb_func_start MOD18_0224AA28
MOD18_0224AA28: ; 0x0224AA28
	mov r1, #2
	ldr r2, _0224AA40 ; =MOD18_02249378
	lsl r1, r1, #8
	str r2, [r0, r1]
	ldr r2, _0224AA44 ; =MOD18_0224938C
	add r1, r1, #4
	str r2, [r0, r1]
	mov r1, #0
	ldr r3, _0224AA48 ; =MOD18_0224AB08
	str r1, [r0, #0x64]
	bx r3
	nop
_0224AA40: .word MOD18_02249378
_0224AA44: .word MOD18_0224938C
_0224AA48: .word MOD18_0224AB08
	thumb_func_end MOD18_0224AA28

	thumb_func_start MOD18_0224AA4C
MOD18_0224AA4C: ; 0x0224AA4C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xa
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xa
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r1, #0
	ldr r2, _0224AA94 ; =MOD18_02249378
	sub r0, #0x30
	str r2, [r4, r0]
	add r0, r1, #0
	ldr r2, _0224AA98 ; =MOD18_0224938C
	sub r0, #0x2c
	str r2, [r4, r0]
	ldr r0, _0224AA9C ; =MOD18_0224A9B4
	str r0, [r4, #0x60]
	mov r0, #0
	str r0, [r4, #0x64]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r1, #0x1c
	strh r0, [r4, r1]
	ldr r1, _0224AAA0 ; =FUN_02025FFC
	add r0, r4, #0
	bl MOD18_0224AB08
	pop {r4, pc}
	nop
_0224AA94: .word MOD18_02249378
_0224AA98: .word MOD18_0224938C
_0224AA9C: .word MOD18_0224A9B4
_0224AAA0: .word FUN_02025FFC
	thumb_func_end MOD18_0224AA4C

	thumb_func_start MOD18_0224AAA4
MOD18_0224AAA4: ; 0x0224AAA4
	mov r1, #2
	ldr r2, _0224AAC0 ; =MOD18_02249378
	lsl r1, r1, #8
	str r2, [r0, r1]
	ldr r2, _0224AAC4 ; =MOD18_0224938C
	add r1, r1, #4
	str r2, [r0, r1]
	ldr r1, _0224AAC8 ; =MOD18_0224A9B4
	ldr r3, _0224AACC ; =MOD18_0224AB08
	str r1, [r0, #0x60]
	mov r1, #0
	str r1, [r0, #0x64]
	ldr r1, _0224AAD0 ; =FUN_02025FFC
	bx r3
	.align 2, 0
_0224AAC0: .word MOD18_02249378
_0224AAC4: .word MOD18_0224938C
_0224AAC8: .word MOD18_0224A9B4
_0224AACC: .word MOD18_0224AB08
_0224AAD0: .word FUN_02025FFC
	thumb_func_end MOD18_0224AAA4

	thumb_func_start MOD18_0224AAD4
MOD18_0224AAD4: ; 0x0224AAD4
	mov r1, #2
	ldr r2, _0224AAF0 ; =MOD18_0224934C
	lsl r1, r1, #8
	str r2, [r0, r1]
	ldr r2, _0224AAF4 ; =MOD18_02249360
	add r1, r1, #4
	str r2, [r0, r1]
	ldr r1, _0224AAF8 ; =MOD18_0224A9B4
	ldr r3, _0224AAFC ; =MOD18_0224AB08
	str r1, [r0, #0x60]
	ldr r1, _0224AB00 ; =MOD18_0224A9EC
	str r1, [r0, #0x64]
	ldr r1, _0224AB04 ; =FUN_02025E20
	bx r3
	.align 2, 0
_0224AAF0: .word MOD18_0224934C
_0224AAF4: .word MOD18_02249360
_0224AAF8: .word MOD18_0224A9B4
_0224AAFC: .word MOD18_0224AB08
_0224AB00: .word MOD18_0224A9EC
_0224AB04: .word FUN_02025E20
	thumb_func_end MOD18_0224AAD4

	thumb_func_start MOD18_0224AB08
MOD18_0224AB08: ; 0x0224AB08
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r1, [sp, #0x14]
	mov r1, #0x81
	add r5, r0, #0
	lsl r1, r1, #2
	ldr r7, [r5, r1]
	sub r1, r1, #4
	ldr r1, [r5, r1]
	blx r1
	add r6, r0, #0
	add r0, r5, #0
	bl MOD18_022498EC
	bl MOD18_0223D678
	ldr r1, _0224AC0C ; =0x00000237
	mov r2, #0
	bl MOD18_0224DB80
	add r0, r6, #1
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224AC10 ; =0x00000257
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224AC14 ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	bl MOD18_0223D678
	bl MOD18_0224DBB4
	mov r4, #0
	str r0, [sp, #0x18]
	cmp r6, #0
	ble _0224AB90
_0224AB78:
	add r0, r4, #0
	add r1, r5, #0
	blx r7
	add r2, r0, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r4, r4, #1
	cmp r4, r6
	blt _0224AB78
_0224AB90:
	mov r2, #0
	ldr r0, [r5, #0x40]
	ldr r1, [sp, #0x18]
	sub r3, r2, #2
	bl ListMenuItems_AppendFromMsgData
	ldr r3, _0224AC18 ; =0x02250598
	add r2, sp, #0x1c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r6, #1
	add r2, sp, #0x1c
	strh r0, [r2, #0x10]
	mov r1, #6
	strh r1, [r2, #0x12]
	ldr r0, [r5, #0x64]
	str r0, [sp, #0x24]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x28]
	ldr r0, [r5, #0x60]
	str r0, [sp, #0x20]
	str r5, [sp, #0x38]
	ldrh r2, [r2, #0x10]
	add r0, r5, #0
	bl MOD18_0224AFB0
	ldr r0, [sp, #0x14]
	mov r2, #0x23
	str r0, [sp]
	ldr r0, _0224AC1C ; =0x022513F8
	lsl r2, r2, #4
	ldr r0, [r0]
	mov r3, #4
	ldr r0, [r0]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x1c
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl MOD18_02244028
	str r0, [r5, #0x4c]
	ldr r0, _0224AC20 ; =0x00000246
	mov r1, #8
	strb r1, [r5, r0]
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224AC0C: .word 0x00000237
_0224AC10: .word 0x00000257
_0224AC14: .word 0x000003D9
_0224AC18: .word MOD18_02250598
_0224AC1C: .word MOD18_022513F8
_0224AC20: .word 0x00000246
	thumb_func_end MOD18_0224AB08

	thumb_func_start MOD18_0224AC24
MOD18_0224AC24: ; 0x0224AC24
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0xa
	bl MOD18_0223E57C
	ldr r0, [r5, #0x4c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r1, sp, #0
	add r2, r0, #0
	ldrh r1, [r1, #2]
	add r0, r5, #0
	mov r3, #6
	bl MOD18_0224B004
	bl FUN_020311F0
	cmp r0, #0
	beq _0224AC6E
	mov r4, #1
	mvn r4, r4
_0224AC6E:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224AC78
	add r4, r0, #0
_0224AC78:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224AC8A
	add r0, r0, #1
	cmp r4, r0
	bne _0224AC98
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224AC8A:
	ldr r0, _0224ACF8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD18_02249AAC
	b _0224ACF2
_0224AC98:
	add r0, r5, #0
	bl MOD18_022498EC
	ldr r0, _0224ACFC ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	strb r4, [r0, #4]
	add r0, r4, #0
	bl MOD18_0224938C
	ldr r1, _0224ACFC ; =0x022513F8
	ldr r1, [r1]
	strb r0, [r1, #5]
	add r0, r5, #0
	mov r1, #2
	bl MOD18_0224996C
	bl MOD18_0223D638
	ldr r2, _0224ACFC ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DF18
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x81
	add r3, r2, #0
	bl MOD18_0224DCD8
	ldr r0, _0224AD00 ; =0x00000246
	mov r1, #0x13
	strb r1, [r5, r0]
	mov r1, #0
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r5, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_0224ACF2:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0224ACF8: .word 0x000005DC
_0224ACFC: .word MOD18_022513F8
_0224AD00: .word 0x00000246
	thumb_func_end MOD18_0224AC24

	thumb_func_start MOD18_0224AD04
MOD18_0224AD04: ; 0x0224AD04
	push {r4, r5, r6, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x50]
	bl ListMenu_ProcessInput
	mov r1, #0x93
	add r4, r0, #0
	lsl r1, r1, #2
	ldrh r6, [r5, r1]
	ldr r0, [r5, #0x50]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	mov r0, #0x93
	lsl r0, r0, #2
	ldrh r0, [r5, r0]
	cmp r6, r0
	beq _0224AD2E
	ldr r0, _0224ADA8 ; =0x000005DC
	bl FUN_020054C8
_0224AD2E:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224AD40
	add r0, r0, #1
	cmp r4, r0
	bne _0224AD5A
	mov r0, #0
	pop {r4, r5, r6, pc}
_0224AD40:
	ldr r0, _0224ADA8 ; =0x000005DC
	bl FUN_020054C8
	add r0, r5, #0
	bl MOD18_02249A64
	add r0, r5, #0
	bl MOD18_0224AA4C
	ldr r0, _0224ADAC ; =0x00000246
	mov r1, #8
	strb r1, [r5, r0]
	b _0224ADA4
_0224AD5A:
	add r0, r5, #0
	bl MOD18_02249A64
	cmp r4, #2
	bne _0224AD94
	ldr r0, _0224ADA8 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224ADB0 ; =0x022513F8
	ldr r1, [r0]
	ldr r0, [r1]
	ldrb r1, [r1, #4]
	bl FUN_02025FA4
	bl MOD18_0223D638
	ldr r2, _0224ADB0 ; =0x022513F8
	mov r1, #2
	ldr r2, [r2]
	ldrb r2, [r2, #5]
	bl MOD18_0224DF18
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x82
	add r3, r2, #0
	bl MOD18_0224DCB8
_0224AD94:
	ldr r0, _0224ADB4 ; =MOD18_0224AA4C
	mov r1, #8
	str r0, [r5]
	ldr r0, _0224ADB8 ; =0x00000245
	strb r1, [r5, r0]
	mov r1, #0xe
	add r0, r0, #1
	strb r1, [r5, r0]
_0224ADA4:
	mov r0, #1
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224ADA8: .word 0x000005DC
_0224ADAC: .word 0x00000246
_0224ADB0: .word MOD18_022513F8
_0224ADB4: .word MOD18_0224AA4C
_0224ADB8: .word 0x00000245
	thumb_func_end MOD18_0224AD04

	thumb_func_start MOD18_0224ADBC
MOD18_0224ADBC: ; 0x0224ADBC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD18_022498EC
	bl MOD18_0223E458
	bl MOD18_0224D344
	bl MOD18_02240C14
	bl MOD18_0223C848
	bl MOD18_0223D370
	mov r0, #0x83
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0224ADE8
	bl MOD18_0224DAA8
_0224ADE8:
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	beq _0224ADF4
	mov r1, #4
	bl FUN_020021EC
_0224ADF4:
	add r0, r5, #0
	bl MOD18_02249A64
	ldr r0, [r5, #8]
	cmp r0, #0
	beq _0224AE04
	bl FUN_0205EBEC
_0224AE04:
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0224AE34
	ldr r0, _0224AE64 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	strb r4, [r0, #4]
	add r0, r4, #0
	bl MOD18_0224938C
	ldr r1, _0224AE64 ; =0x022513F8
	ldr r1, [r1]
	strb r0, [r1, #5]
	mov r1, #0x7f
	lsl r1, r1, #2
	ldr r1, [r5, r1]
	mov r0, #0
	blx r1
	mov r0, #0x7f
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_0224AE34:
	ldr r0, [r5, #0x68]
	cmp r0, #0
	beq _0224AE3E
	bl String_dtor
_0224AE3E:
	ldr r0, [r5, #0x6c]
	cmp r0, #0
	beq _0224AE48
	bl String_dtor
_0224AE48:
	ldr r0, [r5, #0x70]
	cmp r0, #0
	beq _0224AE52
	bl ScrStrBufs_delete
_0224AE52:
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _0224AE5C
	bl FUN_0200CAB4
_0224AE5C:
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224AE64: .word MOD18_022513F8
	thumb_func_end MOD18_0224ADBC

	thumb_func_start MOD18_0224AE68
MOD18_0224AE68: ; 0x0224AE68
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	bl FUN_020311F0
	cmp r0, #0
	beq _0224AE80
	mov r4, #1
	mvn r4, r4
_0224AE80:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224AE8A
	add r4, r0, #0
_0224AE8A:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224AE9C
	add r0, r0, #1
	cmp r4, r0
	bne _0224AEDA
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224AE9C:
	mov r1, #0x7f
	lsl r1, r1, #2
	ldr r0, [r5, r1]
	cmp r0, #0
	beq _0224AEC2
	ldr r0, _0224AF24 ; =0x022513F8
	mov r3, #0
	ldr r2, [r0]
	strb r4, [r2, #4]
	ldr r2, [r0]
	strb r3, [r2, #5]
	ldr r0, [r0]
	ldr r1, [r5, r1]
	ldrb r0, [r0, #5]
	blx r1
	mov r0, #0x7f
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_0224AEC2:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0224ADBC
	bl MOD18_0223E6A0
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224AEDA:
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r0, [r5, r0]
	cmp r0, #0
	beq _0224AF0C
	ldr r0, _0224AF24 ; =0x022513F8
	add r1, r5, #0
	ldr r0, [r0]
	strb r4, [r0, #4]
	add r0, r4, #0
	bl MOD18_0224938C
	ldr r1, _0224AF24 ; =0x022513F8
	ldr r2, [r1]
	strb r0, [r2, #5]
	ldr r0, [r1]
	mov r1, #0x7f
	lsl r1, r1, #2
	ldrb r0, [r0, #5]
	ldr r1, [r5, r1]
	blx r1
	mov r0, #0x7f
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r5, r0]
_0224AF0C:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0224ADBC
	bl MOD18_0223E6A0
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224AF24: .word MOD18_022513F8
	thumb_func_end MOD18_0224AE68

	thumb_func_start MOD18_0224AF28
MOD18_0224AF28: ; 0x0224AF28
	push {r4, r5, r6, lr}
	add r6, r1, #0
	mov r1, #0x25
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x25
	mov r1, #0
	lsl r2, r2, #4
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0x7f
	lsl r0, r0, #2
	str r6, [r4, #0xc]
	add r1, r0, #0
	str r5, [r4, r0]
	mov r2, #0
	add r1, #0x4a
	strb r2, [r4, r1]
	sub r0, r0, #4
	str r2, [r4, r0]
	str r2, [r4, #0x48]
	str r2, [r4, #0x60]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x68]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x6c]
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r4, #0x70]
	add r0, r4, #0
	bl MOD18_0224AA4C
	ldr r0, _0224AFA0 ; =0x00000246
	mov r1, #9
	strb r1, [r4, r0]
	ldr r0, _0224AFA4 ; =MOD18_02249684
	ldr r2, _0224AFA8 ; =0x00002710
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	ldr r1, [r4, #4]
	ldr r2, _0224AFAC ; =MOD18_0224AFE8
	add r0, r4, #0
	bl MOD18_0223E688
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_0224AFA0: .word 0x00000246
_0224AFA4: .word MOD18_02249684
_0224AFA8: .word 0x00002710
_0224AFAC: .word MOD18_0224AFE8
	thumb_func_end MOD18_0224AF28

	thumb_func_start MOD18_0224AFB0
MOD18_0224AFB0: ; 0x0224AFB0
	push {r3, r4}
	mov r3, #0x23
	lsl r3, r3, #4
	ldr r4, [r0, r3]
	add r4, r4, r1
	cmp r4, r2
	blt _0224AFCC
	sub r1, r2, r1
	str r1, [r0, r3]
	ldr r1, [r0, r3]
	cmp r1, #0
	bge _0224AFCC
	mov r1, #0
	str r1, [r0, r3]
_0224AFCC:
	mov r1, #0x8b
	lsl r1, r1, #2
	ldr r3, [r0, r1]
	sub r2, r2, #1
	cmp r3, r2
	blt _0224AFE4
	str r2, [r0, r1]
	ldr r2, [r0, r1]
	cmp r2, #0
	bge _0224AFE4
	mov r2, #0
	str r2, [r0, r1]
_0224AFE4:
	pop {r3, r4}
	bx lr
	thumb_func_end MOD18_0224AFB0

	thumb_func_start MOD18_0224AFE8
MOD18_0224AFE8: ; 0x0224AFE8
	push {r4, lr}
	add r4, r1, #0
	mov r1, #1
	mov r0, #0
	add r2, r1, #0
	bl FUN_0200A274
	mov r1, #1
	add r0, r4, #0
	mvn r1, r1
	bl MOD18_0224ADBC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224AFE8

	thumb_func_start MOD18_0224B004
MOD18_0224B004: ; 0x0224B004
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	add r7, r3, #0
	add r5, r0, #0
	add r4, r1, #0
	cmp r6, r7
	ble _0224B04A
	cmp r4, #0
	ldr r0, [r5, #8]
	beq _0224B022
	mov r1, #0
	mov r2, #1
	bl FUN_0205EC6C
	b _0224B02A
_0224B022:
	mov r1, #0
	add r2, r1, #0
	bl FUN_0205EC6C
_0224B02A:
	add r0, r4, r7
	cmp r6, r0
	ldr r0, [r5, #8]
	beq _0224B03C
	mov r1, #1
	add r2, r1, #0
	bl FUN_0205EC6C
	b _0224B044
_0224B03C:
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_0224B044:
	ldr r0, [r5, #8]
	bl FUN_0205EC18
_0224B04A:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224B004

	thumb_func_start MOD18_0224B04C
MOD18_0224B04C: ; 0x0224B04C
	ldrh r2, [r0]
	ldrh r3, [r0, #2]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	beq _0224B060
	cmp r1, #0
	beq _0224B060
	mov r0, #0xff
	bx lr
_0224B060:
	cmp r3, #0xc
	bne _0224B068
	mov r3, #0
	b _0224B074
_0224B068:
	cmp r3, #0x2c
	bne _0224B070
	mov r3, #8
	b _0224B074
_0224B070:
	mov r0, #0xff
	bx lr
_0224B074:
	add r0, r2, #0
	sub r0, #0xf
	cmp r0, #1
	bhi _0224B080
	mov r0, #0
	bx lr
_0224B080:
	mov r1, #0
_0224B082:
	add r0, r2, #0
	sub r0, #0x2f
	cmp r0, #1
	bhi _0224B08E
	add r0, r1, r3
	bx lr
_0224B08E:
	add r1, r1, #1
	sub r2, #0x20
	cmp r1, #8
	blt _0224B082
	mov r0, #0xff
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224B04C

	thumb_func_start MOD18_0224B09C
MOD18_0224B09C: ; 0x0224B09C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	bl FUN_0204E6CC
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0224B04C
	add r4, r0, #0
	bl FUN_0204E69C
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0224B0BE
	mov r4, #0xff
_0224B0BE:
	cmp r4, #0xff
	beq _0224B118
	add r0, r5, #0
	mov r1, #0
	bl FUN_0204EAD8
	add r0, sp, #0
	strb r4, [r0, #2]
	strb r5, [r0, #1]
	mov r1, #0
	strb r1, [r0, #3]
	cmp r4, r5
	beq _0224B0EA
	add r0, r5, #0
	bl FUN_0204EE9C
	cmp r0, #0
	bne _0224B10A
	mov r1, #1
	add r0, sp, #0
	strb r1, [r0, #3]
	b _0224B10A
_0224B0EA:
	add r0, r5, #0
	bl FUN_0204EE9C
	cmp r0, #0
	beq _0224B10A
	mov r1, #3
	add r0, sp, #0
	strb r1, [r0]
	add r0, r5, #0
	mov r1, #1
	add r2, sp, #0
	mov r3, #0
	bl FUN_0204F0C8
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224B10A:
	add r1, sp, #0
	mov r0, #0x53
	add r1, #1
	bl FUN_02030C4C
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224B118:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224B09C

	thumb_func_start MOD18_0224B11C
MOD18_0224B11C: ; 0x0224B11C
	ldr r3, _0224B124 ; =FUN_0204F774
	mov r0, #0x40
	bx r3
	nop
_0224B124: .word FUN_0204F774
	thumb_func_end MOD18_0224B11C

	thumb_func_start MOD18_0224B128
MOD18_0224B128: ; 0x0224B128
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r4, r3, #0
	bl FUN_02030FE0
	cmp r0, #0
	beq _0224B180
	bl FUN_02031190
	ldrb r1, [r5]
	cmp r1, r0
	bne _0224B180
	bl FUN_02031190
	ldrb r1, [r5, #1]
	cmp r1, r0
	bne _0224B15C
	ldr r0, _0224B184 ; =0x0000060C
	bl FUN_020054C8
	bl FUN_0204F7E4
	add r0, r4, #0
	bl MOD18_0224BD54
	pop {r3, r4, r5, pc}
_0224B15C:
	mov r0, #0x40
	bl FUN_0204F74C
	ldrb r0, [r5, #2]
	cmp r0, #0
	beq _0224B172
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0224BEA4
	pop {r3, r4, r5, pc}
_0224B172:
	bl MOD18_0223D648
	ldr r3, _0224B188 ; =MOD18_0224B11C
	mov r1, #9
	mov r2, #1
	bl MOD18_0224DCB8
_0224B180:
	pop {r3, r4, r5, pc}
	nop
_0224B184: .word 0x0000060C
_0224B188: .word MOD18_0224B11C
	thumb_func_end MOD18_0224B128

	thumb_func_start MOD18_0224B18C
MOD18_0224B18C: ; 0x0224B18C
	mov r0, #3
	bx lr
	thumb_func_end MOD18_0224B18C

	thumb_func_start MOD18_0224B190
MOD18_0224B190: ; 0x0224B190
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r4, r0, #0
	add r1, r5, #0
	bl FUN_02025F98
	add r1, r0, #0
	add r0, r4, #0
	bl FUN_02025D6C
	cmp r0, #0
	beq _0224B1BE
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_02025FA4
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224B1BE:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0224B190

	thumb_func_start MOD18_0224B1C4
MOD18_0224B1C4: ; 0x0224B1C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r1, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r1, r5, #0
	add r4, r0, #0
	bl FUN_02025F0C
	cmp r0, #0
	beq _0224B1E4
	mov r0, #0
	mvn r0, r0
	pop {r3, r4, r5, pc}
_0224B1E4:
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_02025DC8
	bl MOD18_022494B4
	cmp r0, #0
	beq _0224B200
	add r0, r4, #0
	add r1, r5, #0
	bl FUN_02025DD4
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224B200:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224B1C4

	thumb_func_start MOD18_0224B204
MOD18_0224B204: ; 0x0224B204
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224B218
	mov r4, #5
_0224B218:
	bl MOD18_0223D658
	mov r2, #0
	add r1, r4, #6
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, pc}
	thumb_func_end MOD18_0224B204

	thumb_func_start MOD18_0224B228
MOD18_0224B228: ; 0x0224B228
	push {r4, lr}
	add r4, r1, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224B23C
	mov r4, #3
_0224B23C:
	bl MOD18_0223D658
	add r4, #0x2c
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224B228

	thumb_func_start MOD18_0224B250
MOD18_0224B250: ; 0x0224B250
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x48]
	bl ListMenu_ProcessInput
	add r5, r0, #0
	add r1, sp, #0
	ldr r0, [r4, #0x48]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0x17
	bl MOD18_0223E57C
	add r0, r4, #0
	bl MOD18_0224BF84
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bhi _0224B29E
	bhs _0224B2AA
	cmp r5, #4
	bhi _0224B33E
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224B294: ; jump table
	.short _0224B2B8 - _0224B294 - 2 ; case 0
	.short _0224B324 - _0224B294 - 2 ; case 1
	.short _0224B332 - _0224B294 - 2 ; case 2
	.short _0224B316 - _0224B294 - 2 ; case 3
	.short _0224B308 - _0224B294 - 2 ; case 4
_0224B29E:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _0224B33E
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224B2AA:
	ldr r0, _0224B344 ; =0x0000060E
	bl FUN_020054C8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #2
	strb r1, [r4, r0]
	b _0224B33E
_0224B2B8:
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	bl FUN_02025DB0
	cmp r0, #0
	bne _0224B2DE
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x3c
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #0x17
	strb r1, [r4, r0]
	b _0224B33E
_0224B2DE:
	bl FUN_0202EDD8
	cmp r0, #0
	beq _0224B2F2
	bl MOD18_0223E6A0
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #3
	strb r1, [r4, r0]
	b _0224B33E
_0224B2F2:
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x38
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #0x17
	strb r1, [r4, r0]
	b _0224B33E
_0224B308:
	ldr r0, _0224B34C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #8
	strb r1, [r4, r0]
	b _0224B33E
_0224B316:
	ldr r0, _0224B34C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #6
	strb r1, [r4, r0]
	b _0224B33E
_0224B324:
	ldr r0, _0224B34C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #0x11
	strb r1, [r4, r0]
	b _0224B33E
_0224B332:
	ldr r0, _0224B34C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224B348 ; =0x00000246
	mov r1, #0x14
	strb r1, [r4, r0]
_0224B33E:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0224B344: .word 0x0000060E
_0224B348: .word 0x00000246
_0224B34C: .word 0x000005DC
	thumb_func_end MOD18_0224B250

	thumb_func_start MOD18_0224B350
MOD18_0224B350: ; 0x0224B350
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r5, r0, #0
	add r0, r2, #1
	str r0, [sp, #0x18]
	ldr r0, [r5, #0xc]
	add r6, r1, #0
	ldr r0, [r0, #0xc]
	str r3, [sp, #0x14]
	bl FUN_02026CB4
	bl FUN_020269A0
	cmp r0, #3
	bge _0224B374
	ldr r0, [sp, #0x18]
	sub r0, r0, #1
	str r0, [sp, #0x18]
_0224B374:
	add r0, r5, #0
	bl MOD18_022498EC
	ldr r0, [sp, #0x18]
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	str r2, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	ldr r0, [sp, #0x18]
	add r1, r5, #0
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224B45C ; =0x000002F9
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x11
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224B460 ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r2, #0x91
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #4
	bl NewMsgDataFromNarc
	add r7, r0, #0
	ldr r0, [sp, #0x18]
	mov r4, #0
	cmp r0, #0
	ble _0224B3FC
	sub r0, r0, #1
	str r0, [sp, #0x1c]
_0224B3D4:
	ldr r0, [sp, #0x1c]
	cmp r4, r0
	ldr r0, [r5, #0x40]
	bne _0224B3EA
	mov r3, #1
	add r1, r7, #0
	add r2, r6, #5
	mvn r3, r3
	bl ListMenuItems_AppendFromMsgData
	b _0224B3F4
_0224B3EA:
	add r1, r7, #0
	add r2, r6, r4
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
_0224B3F4:
	ldr r0, [sp, #0x18]
	add r4, r4, #1
	cmp r4, r0
	blt _0224B3D4
_0224B3FC:
	add r0, r7, #0
	bl DestroyMsgData
	bl MOD18_0224DAD8
	add r1, sp, #0x20
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [sp, #0x18]
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x20
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _0224B42C
	str r0, [sp, #0x24]
_0224B42C:
	str r5, [sp, #0x3c]
	add r2, sp, #0x20
	ldrh r2, [r2, #0x10]
	ldr r1, [sp, #0x18]
	add r0, r5, #0
	bl MOD18_0224AFB0
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x20
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x48]
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224B45C: .word 0x000002F9
_0224B460: .word 0x000003D9
	thumb_func_end MOD18_0224B350

	thumb_func_start MOD18_0224B464
MOD18_0224B464: ; 0x0224B464
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	add r6, r1, #0
	add r1, r2, #0
	add r1, r1, #1
	str r1, [sp, #0x1c]
	add r5, r0, #0
	str r2, [sp, #0x14]
	str r3, [sp, #0x18]
	bl MOD18_022498EC
	ldr r0, [sp, #0x1c]
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xe
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	add r1, #0x10
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224B558 ; =0x00000219
	mov r3, #0x11
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224B55C ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r2, #0x91
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #4
	bl NewMsgDataFromNarc
	add r7, r0, #0
	ldr r0, [sp, #0x1c]
	mov r4, #0
	cmp r0, #0
	ble _0224B4F8
_0224B4D0:
	ldr r0, [sp, #0x14]
	cmp r4, r0
	ldr r0, [r5, #0x40]
	bne _0224B4E6
	mov r3, #1
	add r1, r7, #0
	add r2, r6, r4
	mvn r3, r3
	bl ListMenuItems_AppendFromMsgData
	b _0224B4F0
_0224B4E6:
	add r1, r7, #0
	add r2, r6, r4
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
_0224B4F0:
	ldr r0, [sp, #0x1c]
	add r4, r4, #1
	cmp r4, r0
	blt _0224B4D0
_0224B4F8:
	add r0, r7, #0
	bl DestroyMsgData
	bl MOD18_0224DAD8
	add r1, sp, #0x20
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [sp, #0x14]
	add r1, sp, #0x20
	add r0, r0, #1
	strh r0, [r1, #0x10]
	ldr r0, [sp, #0x1c]
	strh r0, [r1, #0x12]
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x20]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _0224B528
	str r0, [sp, #0x24]
_0224B528:
	str r5, [sp, #0x3c]
	add r2, sp, #0x20
	ldrh r2, [r2, #0x10]
	ldr r1, [sp, #0x1c]
	add r0, r5, #0
	bl MOD18_0224AFB0
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x20
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x48]
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224B558: .word 0x00000219
_0224B55C: .word 0x000003D9
	thumb_func_end MOD18_0224B464

	thumb_func_start MOD18_0224B560
MOD18_0224B560: ; 0x0224B560
	push {r3, r4, r5, lr}
	add r5, r1, #0
	ldr r0, [r5, #0x48]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r1, sp, #0
	ldr r0, [r5, #0x48]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0x16
	bl MOD18_0223E57C
	add r0, r5, #0
	bl MOD18_0224BF84
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bhi _0224B5A6
	bhs _0224B5B0
	cmp r4, #2
	bhi _0224B600
	cmp r4, #0
	beq _0224B5BE
	cmp r4, #1
	beq _0224B5D4
	cmp r4, #2
	beq _0224B5EA
	b _0224B600
_0224B5A6:
	add r0, r0, #1
	cmp r4, r0
	bne _0224B600
	mov r0, #0
	pop {r3, r4, r5, pc}
_0224B5B0:
	ldr r0, _0224B60C ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224B610 ; =0x00000246
	mov r1, #0
	strb r1, [r5, r0]
	b _0224B606
_0224B5BE:
	bl FUN_0202EDD8
	cmp r0, #0
	ldr r0, _0224B610 ; =0x00000246
	beq _0224B5CE
	mov r1, #0xb
	strb r1, [r5, r0]
	b _0224B606
_0224B5CE:
	mov r1, #0xa
	strb r1, [r5, r0]
	b _0224B606
_0224B5D4:
	bl FUN_0202EDD8
	cmp r0, #0
	ldr r0, _0224B610 ; =0x00000246
	beq _0224B5E4
	mov r1, #0xd
	strb r1, [r5, r0]
	b _0224B606
_0224B5E4:
	mov r1, #0xc
	strb r1, [r5, r0]
	b _0224B606
_0224B5EA:
	bl FUN_0202EDD8
	cmp r0, #0
	ldr r0, _0224B610 ; =0x00000246
	beq _0224B5FA
	mov r1, #0xf
	strb r1, [r5, r0]
	b _0224B606
_0224B5FA:
	mov r1, #0xe
	strb r1, [r5, r0]
	b _0224B606
_0224B600:
	ldr r0, _0224B610 ; =0x00000246
	mov r1, #2
	strb r1, [r5, r0]
_0224B606:
	mov r0, #1
	pop {r3, r4, r5, pc}
	nop
_0224B60C: .word 0x000005DC
_0224B610: .word 0x00000246
	thumb_func_end MOD18_0224B560

	thumb_func_start MOD18_0224B614
MOD18_0224B614: ; 0x0224B614
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #2
	bl MOD18_0223E57C
	ldr r0, [r5, #0x4c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r1, sp, #0
	add r2, r0, #0
	ldrh r1, [r1, #2]
	add r0, r5, #0
	mov r3, #6
	bl MOD18_0224B004
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224B65E
	add r4, r0, #0
_0224B65E:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224B672
	add r0, r0, #1
	cmp r4, r0
	bne _0224B682
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_0224B672:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	ldr r0, _0224B6DC ; =0x00000246
	mov r1, #0
	strb r1, [r5, r0]
	b _0224B6D4
_0224B682:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0224938C
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0224B190
	cmp r0, #0
	beq _0224B6BA
	bl MOD18_0223D658
	add r1, r6, #0
	bl MOD18_0224DE44
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x25
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0224B6C8
_0224B6BA:
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x26
	add r3, r2, #0
	bl MOD18_0224DCB8
_0224B6C8:
	ldr r0, _0224B6DC ; =0x00000246
	mov r1, #0x13
	strb r1, [r5, r0]
	add r0, r5, #0
	bl MOD18_022498EC
_0224B6D4:
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0224B6DC: .word 0x00000246
	thumb_func_end MOD18_0224B614

	thumb_func_start MOD18_0224B6E0
MOD18_0224B6E0: ; 0x0224B6E0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r1, #0
	ldr r0, [r5, #0x4c]
	bl MOD18_02244140
	add r4, r0, #0
	ldr r0, [r5, #0x4c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	add r2, sp, #0
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #6
	bl MOD18_0223E57C
	ldr r0, [r5, #0x4c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r1, sp, #0
	add r2, r0, #0
	ldrh r1, [r1, #2]
	add r0, r5, #0
	mov r3, #6
	bl MOD18_0224B004
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	bne _0224B72A
	add r4, r0, #0
_0224B72A:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224B73E
	add r0, r0, #1
	cmp r4, r0
	bne _0224B74E
	add sp, #4
	mov r0, #0
	pop {r3, r4, r5, r6, pc}
_0224B73E:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	ldr r0, _0224B7D4 ; =0x00000246
	mov r1, #0
	strb r1, [r5, r0]
	b _0224B7B8
_0224B74E:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_02249360
	add r6, r0, #0
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0224B1C4
	cmp r0, #1
	bne _0224B786
	bl MOD18_0223D658
	add r1, r6, #0
	bl MOD18_0224DE44
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x24
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0224B7AC
_0224B786:
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0224B79E
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x37
	add r3, r2, #0
	bl MOD18_0224DCB8
	b _0224B7AC
_0224B79E:
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x27
	add r3, r2, #0
	bl MOD18_0224DCB8
_0224B7AC:
	ldr r0, _0224B7D4 ; =0x00000246
	mov r1, #0x16
	strb r1, [r5, r0]
	add r0, r5, #0
	bl MOD18_022498EC
_0224B7B8:
	mov r1, #0
	ldr r0, [r5, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r5, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
	mov r0, #1
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0224B7D4: .word 0x00000246
	thumb_func_end MOD18_0224B6E0

	thumb_func_start MOD18_0224B7D8
MOD18_0224B7D8: ; 0x0224B7D8
	push {r3, lr}
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224B7FC
	ldr r0, _0224B800 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224B7FC
	bl MOD18_0223D658
	bl MOD18_0224DD94
	mov r0, #1
	pop {r3, pc}
_0224B7FC:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
_0224B800: .word gMain
	thumb_func_end MOD18_0224B7D8

	thumb_func_start MOD18_0224B804
MOD18_0224B804: ; 0x0224B804
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r0, #0
	add r4, r1, #0
	str r0, [sp, #4]
	ldr r0, [r4, #0x38]
	bl FUN_02055320
	lsl r1, r0, #0x10
	mov r0, #0xf
	lsl r0, r0, #0x10
	sub r0, r0, r1
	str r0, [sp]
	ldr r0, [r4, #0x38]
	bl FUN_0205532C
	lsl r1, r0, #0x10
	mov r0, #0x11
	lsl r0, r0, #0x10
	sub r1, r0, r1
	str r1, [sp, #8]
	cmp r5, #0
	bne _0224B83E
	ldr r0, [sp]
	neg r0, r0
	str r0, [sp]
	neg r0, r1
	str r0, [sp, #8]
_0224B83E:
	ldr r1, [r4, #0x20]
	add r0, sp, #0
	bl FUN_0201EF70
	add sp, #0xc
	pop {r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0224B804

	thumb_func_start MOD18_0224B84C
MOD18_0224B84C: ; 0x0224B84C
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	bl FUN_02046528
	add r4, r0, #0
	add r0, r6, #0
	bl FUN_0204652C
	add r5, r0, #0
	ldr r0, [r5]
	cmp r0, #5
	bls _0224B868
	b _0224B970
_0224B868:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224B874: ; jump table
	.short _0224B880 - _0224B874 - 2 ; case 0
	.short _0224B8A4 - _0224B874 - 2 ; case 1
	.short _0224B8D8 - _0224B874 - 2 ; case 2
	.short _0224B8EE - _0224B874 - 2 ; case 3
	.short _0224B912 - _0224B874 - 2 ; case 4
	.short _0224B946 - _0224B874 - 2 ; case 5
_0224B880:
	ldr r0, _0224B978 ; =0x0000060D
	bl FUN_020054C8
	mov r1, #0
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	add r3, r1, #0
	bl FUN_0200E1D0
	mov r0, #1
	str r0, [r5]
	b _0224B970
_0224B8A4:
	bl FUN_0200E308
	cmp r0, #0
	beq _0224B970
	ldr r0, [r4, #0x38]
	mov r1, #0
	bl FUN_0205537C
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224B804
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	mov r1, #0x29
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #2
	str r0, [r5]
	b _0224B970
_0224B8D8:
	bl FUN_0200E308
	cmp r0, #0
	beq _0224B970
	add r0, r4, #0
	add r1, r6, #0
	bl MOD18_0224EA74
	mov r0, #3
	str r0, [r5]
	b _0224B970
_0224B8EE:
	ldr r0, _0224B97C ; =0x0000060E
	bl FUN_020054C8
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r0, #4
	mov r1, #0x28
	str r0, [sp, #8]
	mov r0, #2
	add r2, r1, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #4
	str r0, [r5]
	b _0224B970
_0224B912:
	bl FUN_0200E308
	cmp r0, #0
	beq _0224B970
	ldr r0, [r4, #0x38]
	mov r1, #1
	bl FUN_0205537C
	mov r0, #0
	add r1, r4, #0
	bl MOD18_0224B804
	mov r0, #6
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	mov r1, #4
	str r1, [sp, #8]
	add r1, r0, #0
	add r2, r0, #0
	mov r3, #0
	bl FUN_0200E1D0
	mov r0, #5
	str r0, [r5]
	b _0224B970
_0224B946:
	bl FUN_0200E308
	cmp r0, #0
	beq _0224B970
	add r0, r4, #0
	bl MOD18_02245054
	ldr r0, [r4, #0xc]
	bl SavArray_Flags_get
	bl FUN_0205EDE8
	add r0, r4, #0
	bl MOD18_0224BD54
	add r0, r5, #0
	bl FreeToHeap
	add sp, #0xc
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_0224B970:
	mov r0, #0
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	nop
_0224B978: .word 0x0000060D
_0224B97C: .word 0x0000060E
	thumb_func_end MOD18_0224B84C

	thumb_func_start MOD18_0224B980
MOD18_0224B980: ; 0x0224B980
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x68]
	bl String_dtor
	ldr r0, [r4, #0x6c]
	bl String_dtor
	ldr r0, [r4, #0x70]
	bl ScrStrBufs_delete
	mov r0, #0x7f
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0
	beq _0224B9A6
	mov r0, #0
	blx r1
_0224B9A6:
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0224B9B4
	bl FUN_0205EBEC
	mov r0, #0
	str r0, [r4, #8]
_0224B9B4:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223D658
	bl MOD18_0224DD94
	add r0, r5, #0
	bl FUN_0200CAB4
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224B980

	thumb_func_start MOD18_0224B9D0
MOD18_0224B9D0: ; 0x0224B9D0
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	ldr r2, _0224BD40 ; =0x00000246
	add r4, r1, #0
	ldrb r3, [r4, r2]
	add r6, r0, #0
	cmp r3, #0x17
	bhi _0224BABE
	add r3, r3, r3
	add r3, pc
	ldrh r3, [r3, #6]
	lsl r3, r3, #0x10
	asr r3, r3, #0x10
	add pc, r3
_0224B9EC: ; jump table
	.short _0224BA1C - _0224B9EC - 2 ; case 0
	.short _0224BA54 - _0224B9EC - 2 ; case 1
	.short _0224BA5C - _0224B9EC - 2 ; case 2
	.short _0224BC5C - _0224B9EC - 2 ; case 3
	.short _0224BD3A - _0224B9EC - 2 ; case 4
	.short _0224BD3A - _0224B9EC - 2 ; case 5
	.short _0224BA70 - _0224B9EC - 2 ; case 6
	.short _0224BAB4 - _0224B9EC - 2 ; case 7
	.short _0224BAD8 - _0224B9EC - 2 ; case 8
	.short _0224BB1A - _0224B9EC - 2 ; case 9
	.short _0224BB22 - _0224B9EC - 2 ; case 10
	.short _0224BB56 - _0224B9EC - 2 ; case 11
	.short _0224BB6E - _0224B9EC - 2 ; case 12
	.short _0224BBA2 - _0224B9EC - 2 ; case 13
	.short _0224BBBA - _0224B9EC - 2 ; case 14
	.short _0224BBEE - _0224B9EC - 2 ; case 15
	.short _0224BC06 - _0224B9EC - 2 ; case 16
	.short _0224BC92 - _0224B9EC - 2 ; case 17
	.short _0224BCC2 - _0224B9EC - 2 ; case 18
	.short _0224BCCA - _0224B9EC - 2 ; case 19
	.short _0224BCDE - _0224B9EC - 2 ; case 20
	.short _0224BD0E - _0224B9EC - 2 ; case 21
	.short _0224BD16 - _0224B9EC - 2 ; case 22
	.short _0224BD2A - _0224B9EC - 2 ; case 23
_0224BA1C:
	mov r0, #0x17
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x17
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r1, #0x1a
	strh r0, [r4, r1]
	mov r1, #0
	ldr r3, _0224BD44 ; =MOD18_0224B204
	add r0, r4, #0
	mov r2, #5
	str r1, [sp]
	bl MOD18_0224B350
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #1
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BA54:
	bl MOD18_0224B250
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0224BA5C:
	bl FUN_0204F7FC
	bl MOD18_0223E6A0
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_0224B980
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0224BA70:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223D658
	bl MOD18_0224DD94
	ldr r0, [r4, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl Sav2_PlayerData_GetProfileAddr
	add r5, r0, #0
	ldr r0, [r4, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	mov r3, #0
	str r3, [sp]
	add r2, r0, #0
	ldr r0, [r4, #0xc]
	add r1, r5, #0
	ldr r0, [r0, #8]
	bl MOD18_0224DA00
	mov r1, #0x83
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #7
	add r1, #0x3a
	add sp, #4
	strb r0, [r4, r1]
	pop {r3, r4, r5, r6, pc}
_0224BAB4:
	ldr r0, _0224BD48 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _0224BAC0
_0224BABE:
	b _0224BD3A
_0224BAC0:
	sub r2, #0x3a
	ldr r0, [r4, r2]
	bl MOD18_0224DAA8
	mov r0, #0x83
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, #0x3a
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BAD8:
	bl MOD18_0223D658
	bl MOD18_0224DD94
	mov r0, #0x16
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0x16
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	sub r0, r1, #4
	ldr r0, [r4, r0]
	add r1, #0x1a
	strh r0, [r4, r1]
	mov r0, #1
	str r0, [sp]
	ldr r3, _0224BD4C ; =MOD18_0224B228
	add r0, r4, #0
	mov r1, #0x28
	mov r2, #3
	bl MOD18_0224B464
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #9
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BB1A:
	bl MOD18_0224B560
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0224BB22:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223E494
	bl MOD18_0223C7D4
	mov r0, #1
	sub r1, r0, #7
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x30
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x10
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BB56:
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x39
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x10
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BB6E:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223E46C
	bl MOD18_0223D30C
	mov r0, #1
	sub r1, r0, #7
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x31
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x10
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BBA2:
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x3a
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x10
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BBBA:
	add r0, r4, #0
	bl MOD18_022498EC
	bl MOD18_0223E480
	bl MOD18_02240BB8
	mov r0, #1
	sub r1, r0, #7
	mov r2, #0
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x32
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x10
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BBEE:
	bl MOD18_0223D658
	mov r2, #0
	mov r1, #0x3b
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x10
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BC06:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224BC1C
	ldr r0, _0224BD48 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	bne _0224BC1E
_0224BC1C:
	b _0224BD3A
_0224BC1E:
	mov r0, #1
	mov r1, #0
	sub r2, r1, #6
	add r3, r0, #0
	str r0, [sp]
	bl FUN_0200A208
	bl MOD18_0223D658
	bl MOD18_0224DD94
	bl FUN_0202EDD8
	cmp r0, #0
	beq _0224BC42
	bl MOD18_0223E444
	b _0224BC46
_0224BC42:
	bl MOD18_0223E458
_0224BC46:
	bl MOD18_02240C14
	bl MOD18_0223C848
	bl MOD18_0223D370
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #8
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BC5C:
	ldr r0, [r4, #0xc]
	ldr r0, [r0, #0x10]
	cmp r0, #0
	bne _0224BC86
	mov r0, #0xb
	mov r1, #0xc
	bl AllocFromHeapAtEnd
	mov r1, #0
	mov r2, #0xc
	add r5, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r5]
	str r0, [r5, #4]
	ldr r0, [r4, #0xc]
	ldr r1, _0224BD50 ; =MOD18_0224B84C
	add r2, r5, #0
	bl FUN_020463CC
_0224BC86:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_0224B980
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0224BC92:
	mov r0, #2
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #2
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD18_0224AAA4
	add r0, r4, #0
	mov r1, #0x1c
	bl MOD18_0224CB34
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x12
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BCC2:
	bl MOD18_0224B614
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0224BCCA:
	add r0, r4, #0
	bl MOD18_0224B7D8
	cmp r0, #0
	beq _0224BD3A
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x11
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BCDE:
	mov r0, #6
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #6
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD18_0224AAD4
	add r0, r4, #0
	mov r1, #0x20
	bl MOD18_0224CB34
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x15
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BD0E:
	bl MOD18_0224B6E0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_0224BD16:
	add r0, r4, #0
	bl MOD18_0224B7D8
	cmp r0, #0
	beq _0224BD3A
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0x14
	add sp, #4
	strb r1, [r4, r0]
	pop {r3, r4, r5, r6, pc}
_0224BD2A:
	add r0, r4, #0
	bl MOD18_0224B7D8
	cmp r0, #0
	beq _0224BD3A
	ldr r0, _0224BD40 ; =0x00000246
	mov r1, #0
	strb r1, [r4, r0]
_0224BD3A:
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_0224BD40: .word 0x00000246
_0224BD44: .word MOD18_0224B204
_0224BD48: .word gMain
_0224BD4C: .word MOD18_0224B228
_0224BD50: .word MOD18_0224B84C
	thumb_func_end MOD18_0224B9D0

	thumb_func_start MOD18_0224BD54
MOD18_0224BD54: ; 0x0224BD54
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #1
	bl MOD18_0223E56C
	mov r1, #0x25
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x25
	add r4, r0, #0
	mov r1, #0
	lsl r2, r2, #4
	bl MI_CpuFill8
	str r5, [r4, #0xc]
	bl MOD18_0223D658
	mov r1, #0x91
	lsl r1, r1, #2
	mov r2, #1
	bl MOD18_0224DB80
	ldr r0, _0224BDE4 ; =0x00000246
	mov r1, #0
	strb r1, [r4, r0]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x68]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r4, #0x6c]
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r4, #0x70]
	mov r0, #4
	bl FUN_0205EB38
	str r0, [r4, #8]
	mov r1, #0xc8
	mov r2, #0x14
	mov r3, #0x7a
	bl FUN_0205EC48
	mov r1, #0
	ldr r0, [r4, #8]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r4, #8]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
	ldr r0, _0224BDE8 ; =MOD18_0224B9D0
	ldr r2, _0224BDEC ; =0x00002710
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #4]
	ldr r1, [r4, #4]
	ldr r2, _0224BDF0 ; =MOD18_0224AFE8
	add r0, r4, #0
	bl MOD18_0223E688
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224BDE4: .word 0x00000246
_0224BDE8: .word MOD18_0224B9D0
_0224BDEC: .word 0x00002710
_0224BDF0: .word MOD18_0224AFE8
	thumb_func_end MOD18_0224BD54

	thumb_func_start MOD18_0224BDF4
MOD18_0224BDF4: ; 0x0224BDF4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _0224BE0A
	cmp r0, #1
	beq _0224BE30
	cmp r0, #2
	beq _0224BE68
	pop {r3, r4, r5, pc}
_0224BE0A:
	bl MOD18_0223D638
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224BE78
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #4]
	ldr r1, _0224BE7C ; =0x0225065C
	ldr r0, [r0, #8]
	ldr r2, _0224BE80 ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #8]
	mov r0, #1
	str r0, [r4]
	pop {r3, r4, r5, pc}
_0224BE30:
	ldr r0, [r4, #8]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0224BE78
	cmp r0, #0
	bne _0224BE50
	add r1, r4, #0
	mov r0, #0x59
	add r1, #0xc
	bl FUN_020311D0
	b _0224BE5E
_0224BE50:
	mov r0, #0x40
	bl FUN_0204F774
	bl MOD18_0223D638
	bl MOD18_0224DD94
_0224BE5E:
	mov r0, #2
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	pop {r3, r4, r5, pc}
_0224BE68:
	add r0, r4, #0
	bl FreeToHeap
	bl MOD18_0223E6A0
	add r0, r5, #0
	bl FUN_0200CAB4
_0224BE78:
	pop {r3, r4, r5, pc}
	nop
_0224BE7C: .word MOD18_0225065C
_0224BE80: .word 0x000003D9
	thumb_func_end MOD18_0224BDF4

	thumb_func_start MOD18_0224BE84
MOD18_0224BE84: ; 0x0224BE84
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	beq _0224BE96
	mov r1, #4
	bl FUN_020021EC
_0224BE96:
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224BE84

	thumb_func_start MOD18_0224BEA4
MOD18_0224BEA4: ; 0x0224BEA4
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0x25
	add r6, r0, #0
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x14
	add r4, r0, #0
	bl MI_CpuFill8
	mov r0, #0
	str r0, [r4]
	ldr r0, _0224BF0C ; =MOD18_0224BDF4
	ldr r2, _0224BF10 ; =0x00002710
	str r6, [r4, #4]
	add r1, r4, #0
	bl FUN_0200CA44
	str r0, [r4, #0x10]
	bl MOD18_0223D638
	add r6, r0, #0
	ldrb r0, [r5, #1]
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r6, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D638
	mov r2, #0
	mov r1, #0x43
	add r3, r2, #0
	bl MOD18_0224DCB8
	ldrb r0, [r5]
	ldr r2, _0224BF14 ; =MOD18_0224BE84
	strb r0, [r4, #0xc]
	ldrb r0, [r5, #1]
	strb r0, [r4, #0xd]
	ldrb r0, [r5, #2]
	strb r0, [r4, #0xe]
	ldr r1, [r4, #0x10]
	add r0, r4, #0
	bl MOD18_0223E688
	pop {r4, r5, r6, pc}
	nop
_0224BF0C: .word MOD18_0224BDF4
_0224BF10: .word 0x00002710
_0224BF14: .word MOD18_0224BE84
	thumb_func_end MOD18_0224BEA4

	thumb_func_start MOD18_0224BF18
MOD18_0224BF18: ; 0x0224BF18
	push {r4, lr}
	add r4, r2, #0
	ldrb r0, [r4]
	ldrb r1, [r4, #1]
	bl FUN_0204EEBC
	cmp r0, #0
	beq _0224BF30
	mov r0, #0x5a
	add r1, r4, #0
	bl FUN_02030C4C
_0224BF30:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224BF18

	thumb_func_start MOD18_0224BF34
MOD18_0224BF34: ; 0x0224BF34
	push {r3, r4, r5, lr}
	add r4, r2, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _0224BF6A
	bl MOD18_0223D648
	add r5, r0, #0
	ldrb r0, [r4, #1]
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r5, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D648
	ldr r3, _0224BF7C ; =MOD18_0224B11C
	mov r1, #8
	mov r2, #1
	bl MOD18_0224DCB8
	ldr r0, _0224BF80 ; =0x00000425
	bl FUN_0200521C
_0224BF6A:
	ldrb r0, [r4]
	ldrb r1, [r4, #1]
	bl FUN_0204EEBC
	ldrb r0, [r4]
	ldrb r1, [r4, #1]
	bl MOD18_0224727C
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224BF7C: .word MOD18_0224B11C
_0224BF80: .word 0x00000425
	thumb_func_end MOD18_0224BF34

	thumb_func_start MOD18_0224BF84
MOD18_0224BF84: ; 0x0224BF84
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r1, _0224BFA4 ; =0x0000024A
	ldr r0, [r5, #0x48]
	ldrh r4, [r5, r1]
	add r1, r5, r1
	bl ListMenuGetCurrentItemArrayId
	ldr r0, _0224BFA4 ; =0x0000024A
	ldrh r0, [r5, r0]
	cmp r4, r0
	beq _0224BFA2
	ldr r0, _0224BFA8 ; =0x000005DC
	bl FUN_020054C8
_0224BFA2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224BFA4: .word 0x0000024A
_0224BFA8: .word 0x000005DC
	thumb_func_end MOD18_0224BF84

	thumb_func_start MOD18_0224BFAC
MOD18_0224BFAC: ; 0x0224BFAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	ldr r0, [r6, #0xc]
	add r4, r1, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	bl FUN_02025D40
	add r7, r4, r0
	mov r4, #0
_0224BFC6:
	cmp r4, #0
	bne _0224BFCE
	mov r5, #0x21
	b _0224BFE6
_0224BFCE:
	ldr r0, _0224C09C ; =0x5D588B65
	add r1, r7, #0
	mul r1, r0
	ldr r0, _0224C0A0 ; =0x00269EC3
	add r7, r1, r0
	lsr r1, r7, #0x10
	lsl r0, r1, #5
	add r0, r1, r0
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r5, r0, #1
_0224BFE6:
	mov r0, #0
	cmp r4, #0
	ble _0224C002
	mov r1, #0x21
	add r3, r0, #0
	lsl r1, r1, #4
_0224BFF2:
	add r2, r6, r0
	ldrb r2, [r2, r1]
	cmp r5, r2
	bne _0224BFFC
	add r5, r3, #0
_0224BFFC:
	add r0, r0, #1
	cmp r0, r4
	blt _0224BFF2
_0224C002:
	cmp r5, #0
	bne _0224C00A
	sub r4, r4, #1
	b _0224C092
_0224C00A:
	add r0, r5, #0
	bl MOD18_0224DFFC
	str r0, [sp, #4]
	add r0, r5, #0
	bl MOD18_0224E00C
	str r0, [sp, #8]
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0224C02A
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _0224C02A
	sub r4, r4, #1
	b _0224C092
_0224C02A:
	mov r1, #0x21
	add r0, r6, r4
	lsl r1, r1, #4
	str r0, [sp]
	strb r5, [r0, r1]
	add r0, r5, #0
	bl MOD18_0224DFEC
	ldr r1, _0224C0A4 ; =0x00000215
	ldr r2, [sp]
	strb r0, [r2, r1]
	add r0, r2, #0
	ldrb r0, [r0, r1]
	cmp r0, #6
	bne _0224C064
	ldr r0, _0224C09C ; =0x5D588B65
	add r2, r7, #0
	mul r2, r0
	ldr r0, _0224C0A0 ; =0x00269EC3
	add r7, r2, r0
	lsr r2, r7, #0x10
	lsl r0, r2, #2
	add r0, r2, r0
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r2, r0, #1
	ldr r0, [sp]
	strb r2, [r0, r1]
_0224C064:
	ldr r0, _0224C09C ; =0x5D588B65
	add r1, r7, #0
	mul r1, r0
	ldr r0, _0224C0A0 ; =0x00269EC3
	add r7, r1, r0
	ldr r1, [sp, #8]
	ldr r0, [sp, #4]
	sub r0, r1, r0
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	bne _0224C07E
	lsr r0, r7, #0x10
	b _0224C084
_0224C07E:
	lsr r0, r7, #0x10
	mul r1, r0
	lsr r0, r1, #0x10
_0224C084:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #4]
	add r2, r0, r1
	ldr r1, _0224C0A8 ; =0x0000021A
	ldr r0, [sp]
	strb r2, [r0, r1]
_0224C092:
	add r4, r4, #1
	cmp r4, #5
	blt _0224BFC6
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224C09C: .word 0x5D588B65
_0224C0A0: .word 0x00269EC3
_0224C0A4: .word 0x00000215
_0224C0A8: .word 0x0000021A
	thumb_func_end MOD18_0224BFAC

	thumb_func_start MOD18_0224C0AC
MOD18_0224C0AC: ; 0x0224C0AC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	ldr r0, [r6, #0xc]
	add r4, r1, #0
	bl ScriptEnvironment_GetSav2Ptr
	add r5, r0, #0
	bl FUN_02026CC4
	add r7, r0, #0
	add r0, r5, #0
	bl Sav2_Pokedex_get
	bl Pokedex_GetNatDexFlag
	str r0, [sp, #4]
	add r0, r7, #0
	bl FUN_02025D40
	add r7, r4, r0
	mov r4, #0
_0224C0D8:
	ldr r0, _0224C1B0 ; =0x5D588B65
	add r1, r7, #0
	mul r1, r0
	ldr r0, _0224C1B4 ; =0x00269EC3
	add r7, r1, r0
	lsr r1, r7, #0x10
	mov r0, #0x8a
	mul r0, r1
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r5, r0, #1
	mov r0, #0
	cmp r4, #0
	ble _0224C10C
	mov r1, #0x21
	add r3, r0, #0
	lsl r1, r1, #4
_0224C0FC:
	add r2, r6, r0
	ldrb r2, [r2, r1]
	cmp r5, r2
	bne _0224C106
	add r5, r3, #0
_0224C106:
	add r0, r0, #1
	cmp r0, r4
	blt _0224C0FC
_0224C10C:
	cmp r5, #0
	bne _0224C114
	sub r4, r4, #1
	b _0224C1A6
_0224C114:
	mov r1, #0x21
	add r0, r6, r4
	lsl r1, r1, #4
	str r0, [sp]
	strb r5, [r0, r1]
	add r0, r5, #0
	bl FUN_0204CAB0
	ldr r2, _0224C1B8 ; =0x00000215
	ldr r1, [sp]
	strb r0, [r1, r2]
	ldr r0, [sp, #4]
	cmp r0, #0
	bne _0224C13E
	add r0, r5, #0
	bl FUN_0204CB00
	cmp r0, #1
	bne _0224C13E
	sub r4, r4, #1
	b _0224C1A6
_0224C13E:
	ldr r0, _0224C1B8 ; =0x00000215
	ldr r1, [sp]
	ldrb r1, [r1, r0]
	cmp r1, #0
	bne _0224C14C
	sub r4, r4, #1
	b _0224C1A6
_0224C14C:
	cmp r1, #6
	bne _0224C16C
	ldr r1, _0224C1B0 ; =0x5D588B65
	add r2, r7, #0
	mul r2, r1
	ldr r1, _0224C1B4 ; =0x00269EC3
	add r7, r2, r1
	lsr r2, r7, #0x10
	lsl r1, r2, #2
	add r1, r2, r1
	lsr r1, r1, #0x10
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	add r2, r1, #1
	ldr r1, [sp]
	strb r2, [r1, r0]
_0224C16C:
	add r0, r5, #0
	bl FUN_0204CAC0
	str r0, [sp, #8]
	add r0, r5, #0
	bl FUN_0204CAD0
	ldr r1, _0224C1B0 ; =0x5D588B65
	add r2, r7, #0
	mul r2, r1
	ldr r1, _0224C1B4 ; =0x00269EC3
	add r7, r2, r1
	ldr r1, [sp, #8]
	sub r0, r0, r1
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	bne _0224C192
	lsr r0, r7, #0x10
	b _0224C198
_0224C192:
	lsr r0, r7, #0x10
	mul r1, r0
	lsr r0, r1, #0x10
_0224C198:
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #8]
	add r2, r0, r1
	ldr r1, _0224C1BC ; =0x0000021A
	ldr r0, [sp]
	strb r2, [r0, r1]
_0224C1A6:
	add r4, r4, #1
	cmp r4, #5
	blt _0224C0D8
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224C1B0: .word 0x5D588B65
_0224C1B4: .word 0x00269EC3
_0224C1B8: .word 0x00000215
_0224C1BC: .word 0x0000021A
	thumb_func_end MOD18_0224C0AC

	thumb_func_start MOD18_0224C1C0
MOD18_0224C1C0: ; 0x0224C1C0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0xc]
	add r7, r2, #0
	add r4, r1, #0
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	add r6, r0, #0
	add r0, r7, #0
	add r1, r5, #0
	bl MOD18_022493F4
	ldr r1, _0224C260 ; =0x00000215
	add r2, r5, r4
	ldrb r1, [r2, r1]
	cmp r1, r0
	beq _0224C1EE
	ldr r0, _0224C264 ; =0x0000FFFD
	pop {r3, r4, r5, r6, r7, pc}
_0224C1EE:
	add r0, r7, #0
	add r1, r5, #0
	bl MOD18_0224940C
	ldr r1, _0224C268 ; =0x0000021A
	add r2, r5, r4
	add r3, r0, #0
	ldrb r0, [r2, r1]
	cmp r0, r3
	ble _0224C206
	ldr r0, _0224C26C ; =0x0000FFFB
	pop {r3, r4, r5, r6, r7, pc}
_0224C206:
	add r0, r1, #0
	add r0, #0x2e
	ldrb r0, [r5, r0]
	cmp r0, #1
	bne _0224C21E
	sub r1, #0xa
	ldrb r1, [r2, r1]
	add r0, r6, #0
	bl FUN_02026298
	str r0, [sp]
	b _0224C240
_0224C21E:
	cmp r0, #0
	bne _0224C230
	sub r1, #0xa
	ldrb r1, [r2, r1]
	add r0, r6, #0
	bl FUN_02025FD8
	str r0, [sp]
	b _0224C240
_0224C230:
	cmp r0, #2
	bne _0224C240
	sub r1, #0xa
	ldrb r1, [r2, r1]
	add r0, r6, #0
	bl FUN_020261C8
	str r0, [sp]
_0224C240:
	ldr r0, [sp]
	cmp r0, #0
	beq _0224C250
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_02026080
	b _0224C254
_0224C250:
	ldr r0, _0224C270 ; =0x0000FFFC
	pop {r3, r4, r5, r6, r7, pc}
_0224C254:
	mov r0, #0x21
	add r1, r5, r4
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224C260: .word 0x00000215
_0224C264: .word 0x0000FFFD
_0224C268: .word 0x0000021A
_0224C26C: .word 0x0000FFFB
_0224C270: .word 0x0000FFFC
	thumb_func_end MOD18_0224C1C0

	thumb_func_start MOD18_0224C274
MOD18_0224C274: ; 0x0224C274
	push {r4, r5, lr}
	sub sp, #0x34
	add r5, r0, #0
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r5, r0]
	mov r4, #3
	cmp r0, #2
	bne _0224C288
	mov r4, #2
_0224C288:
	add r0, r5, #0
	bl MOD18_022498EC
	add r0, r4, #0
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	lsl r0, r4, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224C410 ; =0x00000391
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224C414 ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r1, #0x92
	lsl r1, r1, #2
	ldrb r0, [r5, r1]
	cmp r0, #1
	bne _0224C31E
	sub r1, #0x24
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD18_0224BFAC
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	add r1, r0, #0
	ldr r0, [r5, #0x40]
	mov r2, #0xd
	mov r3, #0
	bl ListMenuItems_AppendFromMsgData
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	add r1, r0, #0
	ldr r0, [r5, #0x40]
	mov r2, #0xe
	mov r3, #1
	bl ListMenuItems_AppendFromMsgData
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	mov r2, #0xf
	add r1, r0, #0
	add r3, r2, #0
	ldr r0, [r5, #0x40]
	sub r3, #0x11
	bl ListMenuItems_AppendFromMsgData
	b _0224C396
_0224C31E:
	cmp r0, #0
	bne _0224C36C
	sub r1, #0x24
	ldr r1, [r5, r1]
	add r0, r5, #0
	bl MOD18_0224C0AC
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	add r1, r0, #0
	ldr r0, [r5, #0x40]
	mov r2, #0x10
	mov r3, #0
	bl ListMenuItems_AppendFromMsgData
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	add r1, r0, #0
	ldr r0, [r5, #0x40]
	mov r2, #0x11
	mov r3, #1
	bl ListMenuItems_AppendFromMsgData
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	mov r2, #0x12
	add r1, r0, #0
	add r3, r2, #0
	ldr r0, [r5, #0x40]
	sub r3, #0x14
	bl ListMenuItems_AppendFromMsgData
	b _0224C396
_0224C36C:
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	add r1, r0, #0
	ldr r0, [r5, #0x40]
	mov r2, #0x1c
	mov r3, #0
	bl ListMenuItems_AppendFromMsgData
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	mov r2, #0x16
	add r1, r0, #0
	add r3, r2, #0
	ldr r0, [r5, #0x40]
	sub r3, #0x18
	bl ListMenuItems_AppendFromMsgData
_0224C396:
	bl MOD18_0224DAD8
	add r1, sp, #0x14
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [r5, #0x40]
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x20]
	lsl r0, r4, #0x10
	lsr r1, r0, #0x10
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	mov r0, #0x13
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r5, r1]
	mov r0, #0x13
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r5, r1]
	add r2, sp, #0x14
	ldrh r1, [r2, #0x12]
	ldrh r2, [r2, #0x10]
	add r0, r5, #0
	bl MOD18_0224AFB0
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x14
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x48]
	mov r0, #0x8b
	lsl r0, r0, #2
	ldr r1, [r5, r0]
	add r0, #0x1e
	strh r1, [r5, r0]
	add r0, r5, #0
	add r0, #0x10
	bl CopyWindowToVram
	add r0, r5, #0
	add sp, #0x34
	pop {r4, r5, pc}
	nop
_0224C410: .word 0x00000391
_0224C414: .word 0x000003D9
	thumb_func_end MOD18_0224C274

	thumb_func_start MOD18_0224C418
MOD18_0224C418: ; 0x0224C418
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r1, #0
	mov r1, #0x13
	add r7, r0, #0
	add r6, r2, #0
	bl ListMenuGetTemplateField
	add r4, r0, #0
	cmp r6, #0
	beq _0224C434
	add r0, r7, #0
	bl ListMenuCopyToVram
_0224C434:
	add r0, r4, #0
	add r0, #0x20
	mov r1, #0xf
	bl FillWindowPixelBuffer
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	ldr r1, _0224C504 ; =0x00000247
	ldr r2, [r4, #0x68]
	ldrb r1, [r4, r1]
	add r1, #0x17
	bl ReadMsgDataIntoString
	mov r3, #1
	add r0, r4, #0
	str r3, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r2, [r4, #0x68]
	add r0, #0x20
	bl AddTextPrinterParameterized
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _0224C4C2
	ldr r2, _0224C508 ; =0x00000215
	add r3, r4, r5
	ldrb r2, [r3, r2]
	ldr r0, [r4, #0x70]
	mov r1, #2
	bl BufferUndergroundItemName
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r2, _0224C50C ; =0x0000021A
	add r3, r4, r5
	ldrb r2, [r3, r2]
	ldr r0, [r4, #0x70]
	mov r1, #6
	mov r3, #2
	bl BufferIntegerAsString
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	ldr r2, [r4, #0x68]
	mov r1, #0x19
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x70]
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x68]
	bl StringExpandPlaceholders
	mov r0, #0x11
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x6c]
	add r0, #0x20
	mov r3, #1
	bl AddTextPrinterParameterized
_0224C4C2:
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _0224C4CC
	add r5, r0, #0
_0224C4CC:
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _0224C4E4
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD18_02249AF4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0224C4E4:
	cmp r0, #0
	bne _0224C4F6
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD18_0224A9B4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
_0224C4F6:
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	bl MOD18_0224A2B4
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224C504: .word 0x00000247
_0224C508: .word 0x00000215
_0224C50C: .word 0x0000021A
	thumb_func_end MOD18_0224C418

	thumb_func_start MOD18_0224C510
MOD18_0224C510: ; 0x0224C510
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r6, r1, #0
	mov r1, #0x13
	str r0, [sp, #0xc]
	str r2, [sp, #0x10]
	bl ListMenuGetTemplateField
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	str r0, [sp, #0x2c]
	add r0, r4, #0
	add r0, #0x20
	mov r1, #0xf
	mov r5, #0
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _0224C546
	ldr r0, [sp, #0xc]
	bl ListMenuCopyToVram
_0224C546:
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	bne _0224C550
	b _0224C6C4
_0224C550:
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _0224C5D4
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_022493DC
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x2c]
	bl FUN_02025D40
	mov r1, #0x89
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r1, r1, r0
	ldr r0, [sp, #0x24]
	add r7, r0, r1
	bl MOD18_0224DFEC
	add r5, r0, #0
	cmp r5, #6
	bne _0224C598
	ldr r0, _0224C7B0 ; =0x5D588B65
	add r1, r7, #0
	mul r1, r0
	ldr r0, _0224C7B4 ; =0x00269EC3
	add r7, r1, r0
	lsr r1, r7, #0x10
	lsl r0, r1, #2
	add r0, r1, r0
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r5, r0, #1
_0224C598:
	ldr r0, [sp, #0x24]
	bl MOD18_0224DFFC
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	bl MOD18_0224E00C
	ldr r1, _0224C7B0 ; =0x5D588B65
	add r2, r7, #0
	mul r2, r1
	ldr r1, _0224C7B4 ; =0x00269EC3
	add r1, r2, r1
	ldr r2, [sp, #0x28]
	sub r0, r0, r2
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	bne _0224C5BC
	b _0224C5C2
_0224C5BC:
	lsr r0, r1, #0x10
	add r1, r0, #0
	mul r1, r2
_0224C5C2:
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x28]
	add r1, r0, r1
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r7, r0, #1
	b _0224C6C4
_0224C5D4:
	cmp r0, #0
	bne _0224C652
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_0224938C
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x2c]
	bl FUN_02025D40
	mov r1, #0x89
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r1, r1, r0
	ldr r0, [sp, #0x20]
	add r7, r0, r1
	bl FUN_0204CAB0
	add r5, r0, #0
	cmp r5, #6
	bne _0224C616
	ldr r0, _0224C7B0 ; =0x5D588B65
	add r1, r7, #0
	mul r1, r0
	ldr r0, _0224C7B4 ; =0x00269EC3
	add r7, r1, r0
	lsr r1, r7, #0x10
	lsl r0, r1, #2
	add r0, r1, r0
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r5, r0, #1
_0224C616:
	ldr r0, [sp, #0x20]
	bl FUN_0204CAC0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x20]
	bl FUN_0204CAD0
	ldr r1, _0224C7B0 ; =0x5D588B65
	add r2, r7, #0
	mul r2, r1
	ldr r1, _0224C7B4 ; =0x00269EC3
	add r1, r2, r1
	ldr r2, [sp, #0x14]
	sub r0, r0, r2
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	bne _0224C63A
	b _0224C640
_0224C63A:
	lsr r0, r1, #0x10
	add r1, r0, #0
	mul r1, r2
_0224C640:
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x14]
	add r1, r0, r1
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r7, r0, #1
	b _0224C6C4
_0224C652:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD18_02249438
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x2c]
	bl FUN_02025D40
	mov r1, #0x89
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r1, r1, r0
	ldr r0, [sp, #0x1c]
	add r7, r0, r1
	bl MOD18_0224DFBC
	add r5, r0, #0
	cmp r5, #6
	bne _0224C690
	ldr r0, _0224C7B0 ; =0x5D588B65
	add r1, r7, #0
	mul r1, r0
	ldr r0, _0224C7B4 ; =0x00269EC3
	add r7, r1, r0
	lsr r1, r7, #0x10
	lsl r0, r1, #2
	add r0, r1, r0
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r5, r0, #1
_0224C690:
	ldr r0, [sp, #0x1c]
	bl MOD18_0224DFCC
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	bl MOD18_0224DFDC
	ldr r1, _0224C7B0 ; =0x5D588B65
	add r2, r7, #0
	mul r2, r1
	ldr r1, _0224C7B4 ; =0x00269EC3
	add r1, r2, r1
	ldr r2, [sp, #0x18]
	sub r0, r0, r2
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	bne _0224C6B4
	b _0224C6BA
_0224C6B4:
	lsr r0, r1, #0x10
	add r1, r0, #0
	mul r1, r2
_0224C6BA:
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
	ldr r0, [sp, #0x18]
	add r7, r0, r1
_0224C6C4:
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	ldr r1, _0224C7B8 ; =0x00000247
	ldr r2, [r4, #0x68]
	ldrb r1, [r4, r1]
	add r1, #0x17
	bl ReadMsgDataIntoString
	mov r3, #1
	add r0, r4, #0
	str r3, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r2, [r4, #0x68]
	add r0, #0x20
	bl AddTextPrinterParameterized
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _0224C778
	cmp r5, #0
	beq _0224C74E
	ldr r0, [r4, #0x70]
	mov r1, #2
	add r2, r5, #0
	bl BufferUndergroundItemName
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, [r4, #0x70]
	mov r1, #6
	add r2, r7, #0
	mov r3, #2
	bl BufferIntegerAsString
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	ldr r2, [r4, #0x68]
	mov r1, #0x19
	bl ReadMsgDataIntoString
	ldr r0, [r4, #0x70]
	ldr r1, [r4, #0x6c]
	ldr r2, [r4, #0x68]
	bl StringExpandPlaceholders
	mov r0, #0x11
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x6c]
	add r0, #0x20
	mov r3, #1
	bl AddTextPrinterParameterized
	ldr r0, _0224C7BC ; =0x00000215
	strb r5, [r4, r0]
	add r0, r0, #5
	strb r7, [r4, r0]
	b _0224C778
_0224C74E:
	ldr r0, _0224C7BC ; =0x00000215
	strb r5, [r4, r0]
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	ldr r2, [r4, #0x68]
	mov r1, #0x1a
	bl ReadMsgDataIntoString
	mov r0, #0x11
	str r0, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	add r0, r4, #0
	ldr r2, [r4, #0x68]
	add r0, #0x20
	mov r3, #1
	bl AddTextPrinterParameterized
_0224C778:
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _0224C790
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r1, r6, #0
	bl MOD18_02249AF4
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
_0224C790:
	cmp r0, #0
	bne _0224C7A2
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r1, r6, #0
	bl MOD18_0224A9B4
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
_0224C7A2:
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	add r1, r6, #0
	bl MOD18_0224A2B4
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224C7B0: .word 0x5D588B65
_0224C7B4: .word 0x00269EC3
_0224C7B8: .word 0x00000247
_0224C7BC: .word 0x00000215
	thumb_func_end MOD18_0224C510

	thumb_func_start MOD18_0224C7C0
MOD18_0224C7C0: ; 0x0224C7C0
	cmp r0, #5
	blt _0224C7C8
	mov r0, #0
	bx lr
_0224C7C8:
	add r1, r1, r0
	mov r0, #0x21
	lsl r0, r0, #4
	ldrb r0, [r1, r0]
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224C7C0

	thumb_func_start MOD18_0224C7D4
MOD18_0224C7D4: ; 0x0224C7D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r5, r0, #0
	bl MOD18_022498EC
	mov r0, #6
	mov r1, #4
	bl ListMenuItems_ctor
	str r0, [r5, #0x40]
	mov r2, #3
	add r1, r5, #0
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224C930 ; =0x00000301
	add r1, #0x10
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224C934 ; =0x000003D9
	add r0, #0x10
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r2, #0x92
	lsl r2, r2, #2
	ldrb r0, [r5, r2]
	cmp r0, #1
	bne _0224C83C
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0xd
	mov r3, #4
	bl NewMsgDataFromNarc
	add r6, r0, #0
	bl MOD18_0223D678
	ldr r1, _0224C938 ; =0x0000023B
	mov r2, #0
	bl MOD18_0224DB80
	b _0224C876
_0224C83C:
	cmp r0, #0
	bne _0224C85C
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0x11
	mov r3, #4
	bl NewMsgDataFromNarc
	add r6, r0, #0
	bl MOD18_0223D678
	ldr r1, _0224C93C ; =0x00000237
	mov r2, #0
	bl MOD18_0224DB80
	b _0224C876
_0224C85C:
	mov r0, #0
	mov r1, #0x1a
	sub r2, #0xf
	mov r3, #4
	bl NewMsgDataFromNarc
	add r6, r0, #0
	bl MOD18_0223D678
	ldr r1, _0224C940 ; =0x00000239
	mov r2, #0
	bl MOD18_0224DB80
_0224C876:
	mov r7, #0x21
	mov r4, #0
	lsl r7, r7, #4
_0224C87C:
	add r2, r5, r4
	ldrb r2, [r2, r7]
	ldr r0, [r5, #0x40]
	add r1, r6, #0
	add r3, r4, #0
	bl ListMenuItems_AppendFromMsgData
	add r4, r4, #1
	cmp r4, #5
	blt _0224C87C
	mov r2, #0
	ldr r0, [r5, #0x40]
	add r1, r6, #0
	sub r3, r2, #2
	bl ListMenuItems_AppendFromMsgData
	add r0, r6, #0
	bl DestroyMsgData
	bl MOD18_0224DAD8
	add r1, sp, #0x14
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, [r5, #0x40]
	mov r1, #6
	str r0, [sp, #0x14]
	add r0, r5, #0
	add r0, #0x10
	str r0, [sp, #0x20]
	add r0, sp, #0x14
	strh r1, [r0, #0x10]
	strh r1, [r0, #0x12]
	ldr r0, _0224C944 ; =MOD18_0224C418
	ldr r1, _0224C948 ; =MOD18_0224C7C0
	str r0, [sp, #0x18]
	mov r0, #0x81
	str r5, [sp, #0x30]
	lsl r0, r0, #2
	str r1, [r5, r0]
	add r0, #0x44
	ldrb r0, [r5, r0]
	add r0, #0xd
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r5, r1]
	add r1, #0x18
	ldrb r0, [r5, r1]
	add r0, #0xd
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r5, r1]
	ldr r0, [r5, r1]
	add r1, #0x1e
	strh r0, [r5, r1]
	add r2, sp, #0x14
	ldrh r1, [r2, #0x12]
	ldrh r2, [r2, #0x10]
	add r0, r5, #0
	bl MOD18_0224AFB0
	mov r2, #0x23
	lsl r2, r2, #4
	ldr r1, [r5, r2]
	sub r2, r2, #4
	ldr r2, [r5, r2]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0x14
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	mov r3, #4
	bl ListMenuInit
	str r0, [r5, #0x48]
	add r5, #0x10
	add r0, r5, #0
	bl CopyWindowToVram
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224C930: .word 0x00000301
_0224C934: .word 0x000003D9
_0224C938: .word 0x0000023B
_0224C93C: .word 0x00000237
_0224C940: .word 0x00000239
_0224C944: .word MOD18_0224C418
_0224C948: .word MOD18_0224C7C0
	thumb_func_end MOD18_0224C7D4

	thumb_func_start MOD18_0224C94C
MOD18_0224C94C: ; 0x0224C94C
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x20
	bl FUN_02019048
	cmp r0, #0
	beq _0224C96C
	add r0, r4, #0
	add r0, #0x20
	mov r1, #1
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #0x20
	bl FUN_02019178
_0224C96C:
	add r0, r4, #0
	bl MOD18_022498EC
	pop {r4, pc}
	thumb_func_end MOD18_0224C94C

	thumb_func_start MOD18_0224C974
MOD18_0224C974: ; 0x0224C974
	push {r4, lr}
	mov r2, #0x92
	add r4, r1, #0
	lsl r2, r2, #2
	ldrb r2, [r4, r2]
	cmp r2, #1
	bne _0224C990
	bl MOD18_022493DC
	add r1, r0, #0
	mov r0, #2
	bl MOD18_0224CAB4
	b _0224C9AE
_0224C990:
	cmp r2, #0
	bne _0224C9A2
	bl MOD18_0224938C
	add r1, r0, #0
	mov r0, #2
	bl MOD18_0224CAC8
	b _0224C9AE
_0224C9A2:
	bl MOD18_02249438
	add r1, r0, #0
	mov r0, #2
	bl MOD18_0224CAA0
_0224C9AE:
	ldr r1, _0224C9C0 ; =0x00000215
	mov r0, #4
	ldrb r1, [r4, r1]
	bl MOD18_0224CAA0
	mov r0, #0xa
	bl MOD18_0224CA58
	pop {r4, pc}
	.align 2, 0
_0224C9C0: .word 0x00000215
	thumb_func_end MOD18_0224C974

	thumb_func_start MOD18_0224C9C4
MOD18_0224C9C4: ; 0x0224C9C4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl ScriptEnvironment_GetSav2Ptr
	bl FUN_02026CC4
	ldr r1, _0224CA24 ; =0x00000215
	add r4, r0, #0
	ldrb r0, [r5, r1]
	add r1, r1, #5
	ldrb r1, [r5, r1]
	bl MOD18_02249450
	cmp r0, #0
	beq _0224CA1E
	mov r1, #0x92
	lsl r1, r1, #2
	ldrb r0, [r5, r1]
	cmp r0, #1
	bne _0224C9FA
	sub r1, r1, #4
	ldrb r1, [r5, r1]
	add r0, r4, #0
	bl FUN_02026264
	b _0224CA18
_0224C9FA:
	cmp r0, #0
	bne _0224CA0A
	sub r1, r1, #4
	ldrb r1, [r5, r1]
	add r0, r4, #0
	bl FUN_02025FA4
	b _0224CA18
_0224CA0A:
	cmp r0, #2
	bne _0224CA18
	sub r1, r1, #4
	ldrb r1, [r5, r1]
	add r0, r4, #0
	bl FUN_02026194
_0224CA18:
	ldr r0, _0224CA24 ; =0x00000215
	ldrb r0, [r5, r0]
	pop {r3, r4, r5, pc}
_0224CA1E:
	ldr r0, _0224CA28 ; =0x0000FFFC
	pop {r3, r4, r5, pc}
	nop
_0224CA24: .word 0x00000215
_0224CA28: .word 0x0000FFFC
	thumb_func_end MOD18_0224C9C4

	thumb_func_start MOD18_0224CA2C
MOD18_0224CA2C: ; 0x0224CA2C
	ldr r0, _0224CA30 ; =0x0000FFFE
	bx lr
	.align 2, 0
_0224CA30: .word 0x0000FFFE
	thumb_func_end MOD18_0224CA2C

	thumb_func_start MOD18_0224CA34
MOD18_0224CA34: ; 0x0224CA34
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x68]
	bl String_dtor
	ldr r0, [r4, #0x6c]
	bl String_dtor
	ldr r0, [r4, #0x70]
	bl ScrStrBufs_delete
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224CA34

	thumb_func_start MOD18_0224CA54
MOD18_0224CA54: ; 0x0224CA54
	mov r0, #0
	bx lr
	thumb_func_end MOD18_0224CA54

	thumb_func_start MOD18_0224CA58
MOD18_0224CA58: ; 0x0224CA58
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bl MOD18_0223D658
	ldr r1, _0224CA90 ; =0x00000241
	mov r2, #1
	bl MOD18_0224DB80
	bl MOD18_0223D658
	add r4, r0, #0
	bl FUN_02031190
	bl FUN_0202DFA4
	add r1, r0, #0
	add r0, r4, #0
	bl MOD18_0224DDB8
	bl MOD18_0223D658
	mov r2, #0
	add r1, r5, #0
	add r3, r2, #0
	bl MOD18_0224DCB8
	pop {r3, r4, r5, pc}
	nop
_0224CA90: .word 0x00000241
	thumb_func_end MOD18_0224CA58

	thumb_func_start MOD18_0224CA94
MOD18_0224CA94: ; 0x0224CA94
	push {r3, lr}
	bl MOD18_0223D658
	bl MOD18_0224DD94
	pop {r3, pc}
	thumb_func_end MOD18_0224CA94

	thumb_func_start MOD18_0224CAA0
MOD18_0224CAA0: ; 0x0224CAA0
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD18_0223D658
	add r1, r5, #0
	add r2, r4, #0
	bl MOD18_0224DEF0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224CAA0

	thumb_func_start MOD18_0224CAB4
MOD18_0224CAB4: ; 0x0224CAB4
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD18_0223D658
	add r1, r5, #0
	add r2, r4, #0
	bl MOD18_0224DF04
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224CAB4

	thumb_func_start MOD18_0224CAC8
MOD18_0224CAC8: ; 0x0224CAC8
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl MOD18_0223D658
	add r1, r5, #0
	add r2, r4, #0
	bl MOD18_0224DF18
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224CAC8

	thumb_func_start MOD18_0224CADC
MOD18_0224CADC: ; 0x0224CADC
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	add r0, #0x20
	bl FUN_02019048
	cmp r0, #0
	bne _0224CB1A
	mov r0, #0xc
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r3, #1
	str r3, [sp, #0x10]
	ldr r0, [r4, #0xc]
	add r1, r4, #0
	ldr r0, [r0, #8]
	add r1, #0x20
	mov r2, #3
	bl FUN_02019064
	add r0, r4, #0
	ldr r2, _0224CB30 ; =0x000003D9
	add r0, #0x20
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
_0224CB1A:
	add r0, r4, #0
	add r0, #0x20
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r4, #0x20
	add r0, r4, #0
	bl CopyWindowToVram
	add sp, #0x14
	pop {r3, r4, pc}
	.align 2, 0
_0224CB30: .word 0x000003D9
	thumb_func_end MOD18_0224CADC

	thumb_func_start MOD18_0224CB34
MOD18_0224CB34: ; 0x0224CB34
	push {r4, r5, lr}
	sub sp, #0x14
	mov r3, #1
	add r5, r0, #0
	str r3, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #0x33
	str r0, [sp, #0x10]
	ldr r0, [r5, #0xc]
	add r4, r1, #0
	add r1, r5, #0
	ldr r0, [r0, #8]
	add r1, #0x30
	mov r2, #3
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224CBA8 ; =0x000003D9
	add r0, #0x30
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	add r0, #0x30
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	add r0, #0x30
	bl CopyWindowToVram
	bl MOD18_0223D658
	bl MOD18_0224DBB4
	ldr r2, [r5, #0x68]
	add r1, r4, #0
	bl ReadMsgDataIntoString
	mov r3, #1
	add r0, r5, #0
	str r3, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r1, [sp, #8]
	ldr r2, [r5, #0x68]
	add r0, #0x30
	bl AddTextPrinterParameterized
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_0224CBA8: .word 0x000003D9
	thumb_func_end MOD18_0224CB34

	thumb_func_start MOD18_0224CBAC
MOD18_0224CBAC: ; 0x0224CBAC
	push {r4, lr}
	add r4, r0, #0
	add r0, #0x30
	bl FUN_02019048
	cmp r0, #0
	beq _0224CBCC
	add r0, r4, #0
	add r0, #0x30
	mov r1, #1
	bl FUN_0200CCF8
	add r4, #0x30
	add r0, r4, #0
	bl FUN_02019178
_0224CBCC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224CBAC

	thumb_func_start MOD18_0224CBD0
MOD18_0224CBD0: ; 0x0224CBD0
	push {r3, r4, r5, lr}
	ldr r5, _0224CC00 ; =0x022512A0
	mov r3, #0
_0224CBD6:
	ldrh r4, [r5, #2]
	cmp r0, r4
	bne _0224CBF0
	ldrh r4, [r5, #4]
	cmp r1, r4
	bne _0224CBF0
	mov r0, #6
	add r1, r3, #0
	mul r1, r0
	ldr r0, _0224CC00 ; =0x022512A0
	str r3, [r2]
	ldrh r0, [r0, r1]
	pop {r3, r4, r5, pc}
_0224CBF0:
	add r3, r3, #1
	add r5, r5, #6
	cmp r3, #0x14
	blt _0224CBD6
	bl ErrorHandling
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224CC00: .word MOD18_022512A0
	thumb_func_end MOD18_0224CBD0

	thumb_func_start MOD18_0224CC04
MOD18_0224CC04: ; 0x0224CC04
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	ldr r1, _0224CF50 ; =0x00000246
	add r5, r0, #0
	ldrb r0, [r4, r1]
	cmp r0, #0x13
	bhi _0224CCD6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224CC20: ; jump table
	.short _0224CC48 - _0224CC20 - 2 ; case 0
	.short _0224CC68 - _0224CC20 - 2 ; case 1
	.short _0224CC7E - _0224CC20 - 2 ; case 2
	.short _0224CC8E - _0224CC20 - 2 ; case 3
	.short _0224CD32 - _0224CC20 - 2 ; case 4
	.short _0224CD48 - _0224CC20 - 2 ; case 5
	.short _0224CE38 - _0224CC20 - 2 ; case 6
	.short _0224CE68 - _0224CC20 - 2 ; case 7
	.short _0224CF40 - _0224CC20 - 2 ; case 8
	.short _0224CFA8 - _0224CC20 - 2 ; case 9
	.short _0224CF30 - _0224CC20 - 2 ; case 10
	.short _0224CFCE - _0224CC20 - 2 ; case 11
	.short _0224D046 - _0224CC20 - 2 ; case 12
	.short _0224D0DA - _0224CC20 - 2 ; case 13
	.short _0224D104 - _0224CC20 - 2 ; case 14
	.short _0224D14E - _0224CC20 - 2 ; case 15
	.short _0224D190 - _0224CC20 - 2 ; case 16
	.short _0224D1A0 - _0224CC20 - 2 ; case 17
	.short _0224CDE2 - _0224CC20 - 2 ; case 18
	.short _0224CE20 - _0224CC20 - 2 ; case 19
_0224CC48:
	add r0, r1, #2
	ldrb r0, [r4, r0]
	cmp r0, #2
	bne _0224CC58
	mov r0, #0x1b
	bl MOD18_0224CA58
	b _0224CC5E
_0224CC58:
	mov r0, #0
	bl MOD18_0224CA58
_0224CC5E:
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #1
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CC68:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224CCD6
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #2
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CC7E:
	add r0, r4, #0
	bl MOD18_0224C274
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #3
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CC8E:
	ldr r0, [r4, #0x48]
	bl ListMenu_ProcessInput
	add r5, r0, #0
	add r1, sp, #4
	ldr r0, [r4, #0x48]
	add r1, #2
	add r2, sp, #4
	bl ListMenuGetScrollAndRow
	add r2, sp, #4
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0x13
	bl MOD18_0223E57C
	ldr r1, _0224CF54 ; =0x0000024A
	ldr r0, [r4, #0x48]
	ldrh r6, [r4, r1]
	add r1, r4, r1
	bl ListMenuGetCurrentItemArrayId
	ldr r0, _0224CF54 ; =0x0000024A
	ldrh r0, [r4, r0]
	cmp r6, r0
	beq _0224CCC8
	ldr r0, _0224CF58 ; =0x000005DC
	bl FUN_020054C8
_0224CCC8:
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _0224CCDA
	add r0, r0, #1
	cmp r5, r0
	bne _0224CCD8
_0224CCD6:
	b _0224D1CE
_0224CCD8:
	b _0224CCF2
_0224CCDA:
	ldr r0, _0224CF58 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #0
	bl MOD18_0224C94C
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #0x10
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CCF2:
	mov r1, #0x92
	lsl r1, r1, #2
	ldrb r0, [r4, r1]
	cmp r0, #2
	bne _0224CD0C
	mov r2, #1
	sub r0, r1, #1
	strb r2, [r4, r0]
	mov r2, #0xb
	sub r0, r1, #2
	add sp, #8
	strb r2, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CD0C:
	sub r0, r1, #1
	strb r5, [r4, r0]
	cmp r5, #0
	ldr r0, _0224CF58 ; =0x000005DC
	bne _0224CD24
	bl FUN_020054C8
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #4
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CD24:
	bl FUN_020054C8
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #0xb
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CD32:
	add r0, r4, #0
	bl MOD18_0224CADC
	add r0, r4, #0
	bl MOD18_0224C7D4
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #5
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CD48:
	ldr r0, [r4, #0x48]
	bl ListMenu_ProcessInput
	add r5, r0, #0
	add r1, sp, #4
	ldr r0, [r4, #0x48]
	add r1, #2
	add r2, sp, #4
	bl ListMenuGetScrollAndRow
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	add r2, sp, #4
	ldrh r1, [r2]
	add r0, #0xd
	lsl r0, r0, #0x10
	ldrh r2, [r2, #2]
	lsr r0, r0, #0x10
	bl MOD18_0223E57C
	ldr r1, _0224CF54 ; =0x0000024A
	ldr r0, [r4, #0x48]
	ldrh r6, [r4, r1]
	add r1, r4, r1
	bl ListMenuGetCurrentItemArrayId
	ldr r0, _0224CF54 ; =0x0000024A
	ldrh r0, [r4, r0]
	cmp r6, r0
	beq _0224CD8C
	ldr r0, _0224CF58 ; =0x000005DC
	bl FUN_020054C8
_0224CD8C:
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	bne _0224CD96
	add r5, r0, #0
_0224CD96:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _0224CDA6
	bl MOD18_0223D678
	bl MOD18_0224DD94
_0224CDA6:
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _0224CDB6
	add r0, r0, #1
	cmp r5, r0
	beq _0224CE2C
	b _0224CDCE
_0224CDB6:
	ldr r0, _0224CF58 ; =0x000005DC
	bl FUN_020054C8
	add r0, r4, #0
	mov r1, #1
	bl MOD18_0224C94C
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #2
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CDCE:
	ldr r0, _0224CF58 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #0x12
	strb r1, [r4, r0]
	sub r0, r0, #2
	add sp, #8
	strb r5, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CDE2:
	add r0, r1, #2
	ldrb r0, [r4, r0]
	cmp r0, #1
	bne _0224CDFC
	sub r2, r1, #2
	ldrb r2, [r4, r2]
	sub r1, #0x36
	mov r0, #2
	add r2, r4, r2
	ldrb r1, [r2, r1]
	bl MOD18_0224CAB4
	b _0224CE10
_0224CDFC:
	cmp r0, #0
	bne _0224CE10
	sub r2, r1, #2
	ldrb r2, [r4, r2]
	sub r1, #0x36
	mov r0, #2
	add r2, r4, r2
	ldrb r1, [r2, r1]
	bl MOD18_0224CAC8
_0224CE10:
	mov r0, #1
	bl MOD18_0224CA58
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #0x13
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CE20:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	beq _0224CE2E
_0224CE2C:
	b _0224D1CE
_0224CE2E:
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #6
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CE38:
	mov r0, #0xc
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	mov r0, #0xc
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	add r0, r4, #0
	bl MOD18_02249EF4
	add r0, r4, #0
	mov r1, #0x13
	bl MOD18_0224CB34
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #7
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CE68:
	ldr r0, [r4, #0x4c]
	bl MOD18_02244140
	add r5, r0, #0
	ldr r0, [r4, #0x4c]
	add r1, sp, #4
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #4
	bl ListMenuGetScrollAndRow
	add r2, sp, #4
	ldrh r1, [r2]
	ldrh r2, [r2, #2]
	mov r0, #0xc
	bl MOD18_0223E57C
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	beq _0224CE9A
	bl MOD18_0223D678
	bl MOD18_0224DD94
_0224CE9A:
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _0224CEAA
	add r0, r0, #1
	cmp r5, r0
	beq _0224CF6C
	b _0224CEBA
_0224CEAA:
	add r0, r4, #0
	bl MOD18_0224CBAC
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #4
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CEBA:
	mov r1, #0x91
	lsl r1, r1, #2
	ldrb r1, [r4, r1]
	add r0, r4, #0
	add r2, r5, #0
	bl MOD18_0224C1C0
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl MOD18_0224C94C
	add r0, r4, #0
	bl MOD18_0224CBAC
	ldr r1, _0224CF5C ; =0x0000FFFC
	cmp r5, r1
	bne _0224CEEE
	mov r0, #3
	bl MOD18_0224CA58
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #9
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CEEE:
	add r0, r1, #1
	cmp r5, r0
	bne _0224CF04
	mov r0, #4
	bl MOD18_0224CA58
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #9
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CF04:
	sub r0, r1, #1
	cmp r5, r0
	bne _0224CF1A
	mov r0, #5
	bl MOD18_0224CA58
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #9
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CF1A:
	mov r0, #0x91
	lsl r0, r0, #2
	strb r5, [r4, r0]
	mov r0, #2
	bl MOD18_0224CA58
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #8
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CF30:
	mov r0, #3
	bl MOD18_0224CA58
	ldr r0, _0224CF50 ; =0x00000246
	mov r1, #9
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CF40:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224CF6C
	ldr r0, _0224CF60 ; =gMain
	b _0224CF64
	.align 2, 0
_0224CF50: .word 0x00000246
_0224CF54: .word 0x0000024A
_0224CF58: .word 0x000005DC
_0224CF5C: .word 0x0000FFFC
_0224CF60: .word gMain
_0224CF64:
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	bne _0224CF6E
_0224CF6C:
	b _0224D1CE
_0224CF6E:
	mov r1, #0x92
	lsl r1, r1, #2
	ldrb r0, [r4, r1]
	cmp r0, #1
	bne _0224CF84
	sub r1, r1, #4
	ldrb r1, [r4, r1]
	mov r0, #2
	bl MOD18_0224CAB4
	b _0224CF92
_0224CF84:
	cmp r0, #0
	bne _0224CF92
	sub r1, r1, #4
	ldrb r1, [r4, r1]
	mov r0, #2
	bl MOD18_0224CAC8
_0224CF92:
	mov r0, #6
	bl MOD18_0224CA58
	ldr r0, _0224D1D4 ; =0x000005E3
	bl FUN_020054C8
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #9
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CFA8:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224D0AA
	ldr r0, _0224D1DC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0224D0AA
	mov r0, #8
	bl MOD18_0224CA58
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #2
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224CFCE:
	add r0, r4, #0
	bl MOD18_0224CADC
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	add r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD18_0223E628
	mov r1, #0x8b
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r1, #0x1c
	ldrb r0, [r4, r1]
	add r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD18_0223E5F0
	mov r1, #0x23
	lsl r1, r1, #4
	str r0, [r4, r1]
	ldr r0, _0224D1E0 ; =MOD18_0224C510
	add r1, #0x18
	str r0, [r4, #0x60]
	ldrb r0, [r4, r1]
	cmp r0, #1
	bne _0224D01A
	add r0, r4, #0
	bl MOD18_02249B2C
	add r0, r4, #0
	mov r1, #0x14
	bl MOD18_0224CB34
	b _0224D03C
_0224D01A:
	cmp r0, #0
	bne _0224D02E
	add r0, r4, #0
	bl MOD18_0224AA28
	add r0, r4, #0
	mov r1, #0x15
	bl MOD18_0224CB34
	b _0224D03C
_0224D02E:
	add r0, r4, #0
	bl MOD18_0224A2EC
	add r0, r4, #0
	mov r1, #0x1d
	bl MOD18_0224CB34
_0224D03C:
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #0xc
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224D046:
	ldr r0, [r4, #0x4c]
	bl MOD18_02244140
	add r5, r0, #0
	ldr r0, [r4, #0x4c]
	add r1, sp, #4
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #4
	bl ListMenuGetScrollAndRow
	mov r0, #0x92
	lsl r0, r0, #2
	ldrb r0, [r4, r0]
	add r2, sp, #4
	ldrh r1, [r2]
	add r0, #0x10
	lsl r0, r0, #0x10
	ldrh r2, [r2, #2]
	lsr r0, r0, #0x10
	bl MOD18_0223E57C
	mov r0, #1
	mvn r0, r0
	cmp r5, r0
	beq _0224D082
	add r0, r0, #1
	cmp r5, r0
	beq _0224D0AA
	b _0224D0A2
_0224D082:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	add r0, r4, #0
	mov r1, #1
	bl MOD18_0224C94C
	add r0, r4, #0
	bl MOD18_0224CBAC
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #2
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224D0A2:
	ldr r0, _0224D1E4 ; =0x00000215
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0224D0AC
_0224D0AA:
	b _0224D1CE
_0224D0AC:
	bl MOD18_0223D678
	bl MOD18_0224DD94
	mov r0, #0x91
	lsl r0, r0, #2
	strb r5, [r4, r0]
	add r0, r4, #0
	mov r1, #1
	bl MOD18_0224C94C
	add r0, r4, #0
	bl MOD18_0224CBAC
	add r0, r5, #0
	add r1, r4, #0
	bl MOD18_0224C974
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #0xd
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224D0DA:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224D1CE
	mov r0, #4
	str r0, [sp]
	ldr r0, [r4, #0xc]
	ldr r1, _0224D1E8 ; =0x0225066C
	ldr r0, [r0, #8]
	ldr r2, _0224D1EC ; =0x000003D9
	mov r3, #0xb
	bl Std_CreateYesNoMenu
	str r0, [r4, #0x5c]
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #0xe
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224D104:
	ldr r0, [r4, #0x5c]
	mov r1, #4
	bl FUN_020021AC
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _0224D1CE
	cmp r0, #0
	bne _0224D140
	add r0, r4, #0
	bl MOD18_0224C9C4
	ldr r1, _0224D1F0 ; =0x0000FFFC
	cmp r0, r1
	bne _0224D132
	mov r0, #3
	bl MOD18_0224CA58
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #9
	strb r1, [r4, r0]
	b _0224D146
_0224D132:
	mov r0, #0xb
	bl MOD18_0224CA58
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #0xf
	strb r1, [r4, r0]
	b _0224D146
_0224D140:
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #0x10
	strb r1, [r4, r0]
_0224D146:
	mov r0, #0
	add sp, #8
	str r0, [r4, #0x5c]
	pop {r4, r5, r6, pc}
_0224D14E:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224D1CE
	ldr r0, _0224D1DC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0224D1CE
	bl MOD18_0223D658
	ldr r1, _0224D1F4 ; =0x0000021A
	ldrb r1, [r4, r1]
	bl MOD18_0224DE7C
	ldr r1, _0224D1E4 ; =0x00000215
	mov r0, #2
	ldrb r1, [r4, r1]
	bl MOD18_0224CAA0
	mov r0, #7
	bl MOD18_0224CA58
	ldr r0, _0224D1D4 ; =0x000005E3
	bl FUN_020054C8
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #9
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224D190:
	mov r0, #9
	bl MOD18_0224CA58
	ldr r0, _0224D1D8 ; =0x00000246
	mov r1, #0x11
	add sp, #8
	strb r1, [r4, r0]
	pop {r4, r5, r6, pc}
_0224D1A0:
	bl MOD18_0223D658
	bl MOD18_0224DF88
	cmp r0, #0
	bne _0224D1CE
	ldr r0, _0224D1DC ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #3
	tst r0, r1
	beq _0224D1CE
	bl MOD18_0224CA94
	add r0, r4, #0
	bl MOD18_0224CA34
	bl MOD18_0223E6A0
	add r0, r5, #0
	bl FUN_0200CAB4
	bl FUN_0204F7FC
_0224D1CE:
	add sp, #8
	pop {r4, r5, r6, pc}
	nop
_0224D1D4: .word 0x000005E3
_0224D1D8: .word 0x00000246
_0224D1DC: .word gMain
_0224D1E0: .word MOD18_0224C510
_0224D1E4: .word 0x00000215
_0224D1E8: .word MOD18_0225066C
_0224D1EC: .word 0x000003D9
_0224D1F0: .word 0x0000FFFC
_0224D1F4: .word 0x0000021A
	thumb_func_end MOD18_0224CC04

	thumb_func_start MOD18_0224D1F8
MOD18_0224D1F8: ; 0x0224D1F8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r0, #0
	bl FUN_02031190
	bl FUN_0204E4D4
	str r0, [sp, #8]
	bl FUN_02031190
	bl FUN_0204E50C
	str r0, [sp, #4]
	bl FUN_02031190
	bl FUN_0204E69C
	bl FUN_0204F610
	str r0, [sp]
	ldr r0, [sp, #8]
	ldr r1, [sp, #4]
	add r2, sp, #0xc
	bl MOD18_0224CBD0
	add r5, r0, #0
	add r0, r5, #3
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl MOD18_0223E56C
	mov r1, #0x25
	mov r0, #4
	lsl r1, r1, #4
	bl AllocFromHeap
	mov r2, #0x25
	mov r1, #0
	lsl r2, r2, #4
	add r6, r0, #0
	bl MI_CpuFill8
	mov r0, #0x92
	str r4, [r6, #0xc]
	lsl r0, r0, #2
	strb r5, [r6, r0]
	ldr r1, [sp, #0xc]
	sub r0, #0x24
	str r1, [r6, r0]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r6, #0x68]
	mov r0, #0x64
	mov r1, #4
	bl String_ctor
	str r0, [r6, #0x6c]
	mov r0, #4
	bl ScrStrBufs_new
	str r0, [r6, #0x70]
	ldr r0, _0224D2DC ; =0x00000246
	mov r1, #0
	strb r1, [r6, r0]
	ldr r0, _0224D2E0 ; =0x000005DC
	bl FUN_020054C8
	ldr r0, _0224D2E4 ; =MOD18_0224CC04
	ldr r2, _0224D2E8 ; =0x00002710
	add r1, r6, #0
	bl FUN_0200CA44
	str r0, [r6, #4]
	ldr r1, [r6, #4]
	ldr r2, _0224D2EC ; =MOD18_0224AFE8
	add r0, r6, #0
	bl MOD18_0223E688
	ldr r0, [r6, #0xc]
	bl FUN_02034B64
	add r7, r0, #0
	ldr r0, [r6, #0xc]
	bl FUN_02034B6C
	add r5, r0, #0
	mov r4, #0
	cmp r7, #0
	ble _0224D2D6
_0224D2AE:
	ldrh r1, [r5, #0x18]
	ldr r0, [sp, #8]
	cmp r0, r1
	bne _0224D2CE
	ldrh r1, [r5, #0x1a]
	ldr r0, [sp, #4]
	cmp r0, r1
	bne _0224D2CE
	ldr r0, [r6, #0xc]
	add r1, r4, #0
	ldr r0, [r0, #0x34]
	bl FUN_02058060
	ldr r1, [sp]
	bl FUN_020584AC
_0224D2CE:
	add r4, r4, #1
	add r5, #0x20
	cmp r4, r7
	blt _0224D2AE
_0224D2D6:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224D2DC: .word 0x00000246
_0224D2E0: .word 0x000005DC
_0224D2E4: .word MOD18_0224CC04
_0224D2E8: .word 0x00002710
_0224D2EC: .word MOD18_0224AFE8
	thumb_func_end MOD18_0224D1F8

	thumb_func_start MOD18_0224D2F0
MOD18_0224D2F0: ; 0x0224D2F0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r6, r2, #0
	mov r1, #0
	mov r2, #0x30
	add r5, r0, #0
	bl MI_CpuFill8
	ldr r0, _0224D320 ; =0x022513FC
	str r5, [r0]
	str r6, [r5, #8]
	ldr r0, [r0]
	str r4, [r0, #0xc]
	mov r0, #0xf
	bl FUN_02025964
	ldr r1, _0224D320 ; =0x022513FC
	ldr r2, [r1]
	str r0, [r2, #0x10]
	ldr r0, [r1]
	add r0, #0x14
	bl FUN_020312BC
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224D320: .word MOD18_022513FC
	thumb_func_end MOD18_0224D2F0

	thumb_func_start MOD18_0224D324
MOD18_0224D324: ; 0x0224D324
	push {r3, lr}
	ldr r0, _0224D340 ; =0x022513FC
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	bl FreeToHeap
	ldr r0, _0224D340 ; =0x022513FC
	ldr r0, [r0]
	bl FreeToHeap
	ldr r0, _0224D340 ; =0x022513FC
	mov r1, #0
	str r1, [r0]
	pop {r3, pc}
	.align 2, 0
_0224D340: .word MOD18_022513FC
	thumb_func_end MOD18_0224D324

	thumb_func_start MOD18_0224D344
MOD18_0224D344: ; 0x0224D344
	push {r3, lr}
	ldr r0, _0224D358 ; =0x022513FC
	ldr r1, [r0]
	ldr r0, [r1, #4]
	cmp r0, #0
	beq _0224D356
	ldr r1, [r1]
	bl MOD18_0224D56C
_0224D356:
	pop {r3, pc}
	.align 2, 0
_0224D358: .word MOD18_022513FC
	thumb_func_end MOD18_0224D344

	thumb_func_start MOD18_0224D35C
MOD18_0224D35C: ; 0x0224D35C
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224D35C

	thumb_func_start MOD18_0224D360
MOD18_0224D360: ; 0x0224D360
	mov r0, #0x30
	bx lr
	thumb_func_end MOD18_0224D360

	thumb_func_start MOD18_0224D364
MOD18_0224D364: ; 0x0224D364
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r7, r0, #0
	mov r0, #4
	str r1, [sp, #0xc]
	add r5, r2, #0
	str r3, [sp, #0x10]
	bl ScrStrBufs_new
	str r0, [sp, #0x1c]
	mov r0, #0x1e
	mov r1, #4
	bl String_ctor
	add r4, r0, #0
	mov r0, #0x1e
	mov r1, #4
	bl String_ctor
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	mov r1, #0
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r7, #0
	add r2, r4, #0
	mov r3, #2
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0xc]
	mov r1, #1
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #0x11
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r7, #0
	add r2, r4, #0
	mov r3, #2
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0xc]
	mov r1, #3
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r7, #0
	add r2, r4, #0
	mov r3, #0x39
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0xc]
	mov r1, #2
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r7, #0
	add r2, r4, #0
	mov r3, #0x84
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0xc]
	mov r1, #3
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #0x11
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r7, #0
	add r2, r4, #0
	mov r3, #0x39
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r5, #0
	bl PlayerProfile_GetTrainerID_VisibleHalf
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	mov r1, #6
	mov r3, #5
	bl BufferIntegerAsString
	ldr r0, [sp, #0xc]
	mov r1, #5
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r2, [sp, #0x18]
	add r0, r7, #0
	mov r3, #0x94
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x1c]
	mov r1, #0
	add r2, r5, #0
	bl BufferPlayersName
	ldr r0, [sp, #0xc]
	mov r1, #4
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r2, [sp, #0x18]
	add r0, r7, #0
	mov r3, #0x39
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	bl FUN_020269A0
	add r1, r0, #0
	ldr r0, [sp, #0xc]
	add r1, #0x14
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #0x11
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r7, #0
	add r2, r4, #0
	mov r3, #0x39
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	mov r5, #0
	mov r6, #0x27
_0224D4D0:
	ldr r0, [sp, #0xc]
	add r1, r5, #6
	add r2, r4, #0
	bl ReadMsgDataIntoString
	str r6, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	add r0, r7, #0
	mov r1, #0
	add r2, r4, #0
	mov r3, #2
	bl AddTextPrinterParameterized
	add r5, r5, #1
	add r6, #0x10
	cmp r5, #7
	blt _0224D4D0
	mov r0, #0
	ldr r6, _0224D568 ; =0x02251318
	str r0, [sp, #0x14]
	mov r5, #0x27
_0224D500:
	ldr r0, [sp, #0x10]
	ldr r1, [r6]
	blx r1
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	mov r1, #6
	ldr r0, [sp, #0x1c]
	add r3, r1, #0
	bl BufferIntegerAsString
	ldr r0, [sp, #0xc]
	mov r1, #0xd
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, r4, #0
	bl StringExpandPlaceholders
	str r5, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r2, [sp, #0x18]
	add r0, r7, #0
	mov r1, #0
	mov r3, #0x94
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x14]
	add r6, r6, #4
	add r0, r0, #1
	add r5, #0x10
	str r0, [sp, #0x14]
	cmp r0, #7
	blt _0224D500
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #0x18]
	bl String_dtor
	ldr r0, [sp, #0x1c]
	bl ScrStrBufs_delete
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224D568: .word MOD18_02251318
	thumb_func_end MOD18_0224D364

	thumb_func_start MOD18_0224D56C
MOD18_0224D56C: ; 0x0224D56C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #8
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #8
	bl FUN_02019570
	add r0, r4, #0
	add r0, #8
	bl FUN_02019178
	ldr r1, [r4]
	cmp r1, #0
	beq _0224D596
	ldr r0, [r4, #4]
	blx r1
_0224D596:
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, _0224D5B0 ; =0x022513FC
	mov r2, #0
	ldr r1, [r0]
	str r2, [r1, #4]
	ldr r0, [r0]
	str r2, [r0]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224D5B0: .word MOD18_022513FC
	thumb_func_end MOD18_0224D56C

	thumb_func_start MOD18_0224D5B4
MOD18_0224D5B4: ; 0x0224D5B4
	push {r3, lr}
	ldr r2, _0224D5C8 ; =gMain
	ldr r3, [r2, #0x48]
	mov r2, #3
	tst r2, r3
	beq _0224D5C4
	bl MOD18_0224D56C
_0224D5C4:
	pop {r3, pc}
	nop
_0224D5C8: .word gMain
	thumb_func_end MOD18_0224D5B4

	thumb_func_start MOD18_0224D5CC
MOD18_0224D5CC: ; 0x0224D5CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	str r1, [sp, #0x14]
	mov r0, #4
	mov r1, #0x2c
	add r5, r2, #0
	add r6, r3, #0
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x2c
	bl MI_CpuFill8
	str r5, [r4]
	add r1, r4, #0
	str r6, [r4, #4]
	mov r0, #2
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x13
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, #8
	mov r2, #3
	mov r3, #4
	bl FUN_02019064
	add r0, r4, #0
	ldr r2, _0224D684 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _0224D688 ; =0x00000245
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r5, r0, #0
	add r0, r4, #0
	add r0, #8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x30]
	cmp r0, #0
	beq _0224D644
	ldr r0, _0224D68C ; =0x022513FC
	ldr r0, [r0]
	ldr r3, [r0, #0xc]
	b _0224D64A
_0224D644:
	ldr r0, _0224D68C ; =0x022513FC
	ldr r0, [r0]
	ldr r3, [r0, #0x10]
_0224D64A:
	add r0, r4, #0
	ldr r2, [sp, #0x14]
	add r0, #8
	add r1, r5, #0
	bl MOD18_0224D364
	add r0, r4, #0
	add r0, #8
	bl FUN_02019220
	ldr r0, _0224D690 ; =0x000005FD
	bl FUN_020054C8
	ldr r0, _0224D694 ; =MOD18_0224D5B4
	add r1, r4, #0
	mov r2, #0xa
	bl FUN_0200CA44
	ldr r1, _0224D68C ; =0x022513FC
	ldr r2, [r1]
	str r0, [r2, #4]
	ldr r0, [r1]
	str r4, [r0]
	add r0, r5, #0
	bl DestroyMsgData
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224D684: .word 0x000003D9
_0224D688: .word 0x00000245
_0224D68C: .word MOD18_022513FC
_0224D690: .word 0x000005FD
_0224D694: .word MOD18_0224D5B4
	thumb_func_end MOD18_0224D5CC

	thumb_func_start MOD18_0224D698
MOD18_0224D698: ; 0x0224D698
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	bl FUN_02025960
	add r4, r0, #0
	ldr r0, _0224D6FC ; =0x022513FC
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl FUN_02029FC8
	bl FUN_0202A1B8
	add r6, r0, #0
	mov r0, #4
	add r1, r4, #1
	bl AllocFromHeap
	mov r1, #0
	add r2, r4, #1
	add r5, r0, #0
	bl MI_CpuFill8
	ldr r0, _0224D700 ; =0x000F423F
	strb r7, [r5]
	cmp r6, r0
	blt _0224D6CE
	add r6, r0, #0
_0224D6CE:
	ldr r0, _0224D6FC ; =0x022513FC
	add r1, r6, #0
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_020268E8
	ldr r0, _0224D6FC ; =0x022513FC
	add r1, r5, #1
	ldr r0, [r0]
	add r2, r4, #0
	ldr r0, [r0, #0xc]
	bl MI_CpuCopy8
	mov r0, #0x51
	add r1, r5, #0
	add r2, r4, #1
	bl FUN_02030ADC
	add r0, r5, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0224D6FC: .word MOD18_022513FC
_0224D700: .word 0x000F423F
	thumb_func_end MOD18_0224D698

	thumb_func_start MOD18_0224D704
MOD18_0224D704: ; 0x0224D704
	push {r3, lr}
	ldr r0, _0224D72C ; =0x022513FC
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bl FUN_02029FC8
	bl FUN_0202A1B8
	add r1, r0, #0
	ldr r0, _0224D730 ; =0x000F423F
	cmp r1, r0
	blt _0224D71E
	add r1, r0, #0
_0224D71E:
	ldr r0, _0224D72C ; =0x022513FC
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	bl FUN_020268E8
	pop {r3, pc}
	nop
_0224D72C: .word MOD18_022513FC
_0224D730: .word 0x000F423F
	thumb_func_end MOD18_0224D704

	thumb_func_start MOD18_0224D734
MOD18_0224D734: ; 0x0224D734
	add r3, r1, #0
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, _0224D740 ; =FUN_02030BC4
	mov r0, #0x52
	bx r3
	.align 2, 0
_0224D740: .word FUN_02030BC4
	thumb_func_end MOD18_0224D734

	thumb_func_start MOD18_0224D744
MOD18_0224D744: ; 0x0224D744
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r1, #0
	bl FUN_02031190
	ldrb r1, [r4]
	cmp r1, r0
	bne _0224D76C
	ldr r1, _0224D770 ; =0x022513FC
	add r0, r4, #1
	ldr r1, [r1]
	sub r2, r5, #1
	ldr r1, [r1, #0x10]
	bl MI_CpuCopy8
	ldr r0, _0224D770 ; =0x022513FC
	mov r1, #1
	ldr r0, [r0]
	add r0, #0x2c
	strb r1, [r0]
_0224D76C:
	pop {r3, r4, r5, pc}
	nop
_0224D770: .word MOD18_022513FC
	thumb_func_end MOD18_0224D744

	thumb_func_start MOD18_0224D774
MOD18_0224D774: ; 0x0224D774
	ldr r0, _0224D780 ; =0x022513FC
	ldr r0, [r0]
	add r0, #0x2c
	ldrb r0, [r0]
	bx lr
	nop
_0224D780: .word MOD18_022513FC
	thumb_func_end MOD18_0224D774

	thumb_func_start MOD18_0224D784
MOD18_0224D784: ; 0x0224D784
	ldr r0, _0224D790 ; =0x022513FC
	mov r1, #0
	ldr r0, [r0]
	add r0, #0x2c
	strb r1, [r0]
	bx lr
	.align 2, 0
_0224D790: .word MOD18_022513FC
	thumb_func_end MOD18_0224D784

	thumb_func_start MOD18_0224D794
MOD18_0224D794: ; 0x0224D794
	ldr r3, _0224D798 ; =FUN_0204F7FC
	bx r3
	.align 2, 0
_0224D798: .word FUN_0204F7FC
	thumb_func_end MOD18_0224D794

	thumb_func_start MOD18_0224D79C
MOD18_0224D79C: ; 0x0224D79C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	sub r0, #0x20
	lsl r1, r0, #2
	ldr r0, _0224D808 ; =0x02251318
	cmp r5, #0x20
	ldr r4, [r0, r1]
	bge _0224D7B4
	bl ErrorHandling
_0224D7B4:
	cmp r5, #0x2d
	ble _0224D7BC
	bl ErrorHandling
_0224D7BC:
	bl FUN_0204F7E4
	bl MOD18_0223D658
	ldr r1, _0224D80C ; =0x00000245
	mov r2, #1
	bl MOD18_0224DB80
	mov r0, #4
	bl FUN_02025964
	add r6, r0, #0
	bl FUN_02025960
	add r2, r0, #0
	add r0, r7, #0
	add r1, r6, #0
	bl MI_CpuCopy8
	add r0, r6, #0
	blx r4
	add r4, r0, #0
	add r0, r6, #0
	bl FreeToHeap
	bl MOD18_0223D658
	add r1, r4, #0
	bl MOD18_0224DEC8
	bl MOD18_0223D658
	ldr r3, _0224D810 ; =MOD18_0224D794
	add r1, r5, #0
	mov r2, #1
	bl MOD18_0224DCB8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224D808: .word MOD18_02251318
_0224D80C: .word 0x00000245
_0224D810: .word MOD18_0224D794
	thumb_func_end MOD18_0224D79C

	thumb_func_start MOD18_0224D814
MOD18_0224D814: ; 0x0224D814
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x40]
	str r1, [sp, #0x10]
	str r0, [sp, #0x40]
	mov r0, #4
	add r5, r2, #0
	str r3, [sp, #0x14]
	bl ScrStrBufs_new
	add r7, r0, #0
	mov r0, #0x28
	mov r1, #4
	bl String_ctor
	add r4, r0, #0
	mov r0, #0x28
	mov r1, #4
	bl String_ctor
	add r6, r0, #0
	add r0, r7, #0
	mov r1, #1
	add r2, r5, #0
	bl BufferPlayersName
	ldr r0, [sp, #0x10]
	mov r1, #0xc
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r0, #1
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, [sp, #0xc]
	add r2, r6, #0
	mov r3, #2
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	mov r1, #0xd
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, [sp, #0xc]
	add r2, r4, #0
	mov r3, #2
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x14]
	bl FUN_020269CC
	add r2, r0, #0
	mov r0, #1
	str r0, [sp]
	mov r1, #6
	str r0, [sp, #4]
	add r0, r7, #0
	add r3, r1, #0
	bl BufferIntegerAsString
	ldr r0, [sp, #0x10]
	mov r1, #0xe
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	mov r0, #0x12
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, [sp, #0xc]
	add r2, r6, #0
	mov r3, #0x66
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	mov r1, #0xf
	add r2, r4, #0
	bl ReadMsgDataIntoString
	mov r0, #0x34
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	ldr r0, [sp, #0xc]
	add r2, r4, #0
	mov r3, #2
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	mov r5, #0
	str r5, [sp, #0x20]
_0224D8FA:
	ldr r0, [sp, #0x40]
	ldr r2, [sp, #0x20]
	mov r1, #4
	bl FUN_02025CD8
	str r0, [sp, #0x24]
	cmp r0, #0
	beq _0224D994
	ldr r2, [sp, #0x24]
	add r0, r7, #0
	mov r1, #0
	bl BufferPlayersName
	ldr r0, [sp, #0x10]
	mov r1, #0x10
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	add r0, r5, #0
	str r0, [sp, #0x1c]
	add r0, #0x45
	str r0, [sp, #0x1c]
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	mov r1, #0
	add r2, r6, #0
	mov r3, #2
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x24]
	bl PlayerProfile_GetTrainerID_VisibleHalf
	add r2, r0, #0
	mov r0, #2
	str r0, [sp]
	mov r0, #1
	mov r1, #5
	str r0, [sp, #4]
	add r0, r7, #0
	add r3, r1, #0
	bl BufferIntegerAsString
	ldr r0, [sp, #0x10]
	mov r1, #0x11
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r7, #0
	add r1, r6, #0
	add r2, r4, #0
	bl StringExpandPlaceholders
	ldr r0, [sp, #0x1c]
	mov r1, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r2, r6, #0
	mov r3, #0x66
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x24]
	bl FreeToHeap
	b _0224D9DE
_0224D994:
	ldr r0, [sp, #0x10]
	mov r1, #0x33
	add r2, r4, #0
	bl ReadMsgDataIntoString
	add r0, r5, #0
	str r0, [sp, #0x18]
	add r0, #0x45
	str r0, [sp, #0x18]
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	mov r1, #0
	add r2, r4, #0
	mov r3, #2
	bl AddTextPrinterParameterized
	ldr r0, [sp, #0x10]
	mov r1, #0x34
	add r2, r4, #0
	bl ReadMsgDataIntoString
	ldr r0, [sp, #0x18]
	mov r1, #0
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	ldr r0, [sp, #0xc]
	add r2, r4, #0
	mov r3, #0x66
	bl AddTextPrinterParameterized
_0224D9DE:
	ldr r0, [sp, #0x20]
	add r5, #0x11
	add r0, r0, #1
	str r0, [sp, #0x20]
	cmp r0, #5
	blt _0224D8FA
	add r0, r4, #0
	bl String_dtor
	add r0, r6, #0
	bl String_dtor
	add r0, r7, #0
	bl ScrStrBufs_delete
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224D814

	thumb_func_start MOD18_0224DA00
MOD18_0224DA00: ; 0x0224DA00
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r7, r0, #0
	str r1, [sp, #0x14]
	mov r0, #4
	mov r1, #0x2c
	add r6, r2, #0
	add r4, r3, #0
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x2c
	add r5, r0, #0
	bl MI_CpuFill8
	add r1, r5, #0
	ldr r0, [sp, #0x30]
	str r4, [r5]
	str r0, [r5, #4]
	mov r0, #2
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #0x13
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	mov r0, #1
	str r0, [sp, #0x10]
	add r0, r7, #0
	add r1, #8
	mov r2, #3
	mov r3, #4
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224DA9C ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	mov r2, #0x91
	mov r0, #0
	mov r1, #0x1a
	lsl r2, r2, #2
	mov r3, #4
	bl NewMsgDataFromNarc
	add r4, r0, #0
	add r0, r5, #0
	add r0, #8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	ldr r3, _0224DAA0 ; =0x022513FC
	str r6, [sp]
	ldr r3, [r3]
	ldr r2, [sp, #0x14]
	ldr r3, [r3, #0xc]
	add r0, #8
	add r1, r4, #0
	bl MOD18_0224D814
	ldr r0, _0224DAA4 ; =0x000005FD
	bl FUN_020054C8
	add r0, r5, #0
	add r0, #8
	bl FUN_02019220
	add r0, r4, #0
	bl DestroyMsgData
	add r0, r5, #0
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224DA9C: .word 0x000003D9
_0224DAA0: .word MOD18_022513FC
_0224DAA4: .word 0x000005FD
	thumb_func_end MOD18_0224DA00

	thumb_func_start MOD18_0224DAA8
MOD18_0224DAA8: ; 0x0224DAA8
	push {r4, lr}
	add r4, r0, #0
	add r0, #8
	mov r1, #0
	bl FUN_0200CCF8
	add r0, r4, #0
	add r0, #8
	bl FUN_02019570
	add r0, r4, #0
	add r0, #8
	bl FUN_02019178
	ldr r1, [r4]
	cmp r1, #0
	beq _0224DACE
	ldr r0, [r4, #4]
	blx r1
_0224DACE:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DAA8

	thumb_func_start MOD18_0224DAD8
MOD18_0224DAD8: ; 0x0224DAD8
	ldr r0, _0224DADC ; =0x02250674
	bx lr
	.align 2, 0
_0224DADC: .word MOD18_02250674
	thumb_func_end MOD18_0224DAD8

	thumb_func_start MOD18_0224DAE0
MOD18_0224DAE0: ; 0x0224DAE0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	mov r1, #0x44
	add r7, r2, #0
	str r3, [sp, #4]
	ldr r6, [sp, #0x20]
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x44
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp, #0x20]
	cmp r0, #0
	bne _0224DB08
	mov r6, #0xe6
_0224DB08:
	add r0, r6, #0
	add r1, r5, #0
	bl String_ctor
	str r0, [r4]
	add r0, r6, #0
	add r1, r5, #0
	bl String_ctor
	str r0, [r4, #4]
	add r0, r5, #0
	bl ScrStrBufs_new
	str r0, [r4, #0x28]
	ldr r0, [sp]
	ldr r2, [sp]
	str r0, [r4, #0x2c]
	mov r0, #1
	mov r1, #0x1a
	add r3, r5, #0
	bl NewMsgDataFromNarc
	str r0, [r4, #0x24]
	str r5, [r4, #0x34]
	add r0, r4, #0
	str r7, [r4, #0x18]
	add r0, #8
	bl InitWindow
	ldr r1, [r4, #0x40]
	mov r0, #1
	bic r1, r0
	mov r0, #2
	bic r1, r0
	str r1, [r4, #0x40]
	mov r0, #0
	str r0, [r4, #0x20]
	ldr r0, [sp, #4]
	str r0, [r4, #0x38]
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224DAE0

	thumb_func_start MOD18_0224DB5C
MOD18_0224DB5C: ; 0x0224DB5C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	bl String_dtor
	ldr r0, [r4, #4]
	bl String_dtor
	ldr r0, [r4, #0x28]
	bl ScrStrBufs_delete
	ldr r0, [r4, #0x24]
	bl DestroyMsgData
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD18_0224DB5C

	thumb_func_start MOD18_0224DB80
MOD18_0224DB80: ; 0x0224DB80
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x2c]
	add r4, r1, #0
	add r6, r2, #0
	cmp r0, r4
	beq _0224DBAC
	str r4, [r5, #0x2c]
	ldr r0, [r5, #0x24]
	bl DestroyMsgData
	ldr r3, [r5, #0x34]
	add r0, r6, #0
	mov r1, #0x1a
	add r2, r4, #0
	bl NewMsgDataFromNarc
	str r0, [r5, #0x24]
	cmp r0, #0
	bne _0224DBAC
	bl ErrorHandling
_0224DBAC:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DB80

	thumb_func_start MOD18_0224DBB0
MOD18_0224DBB0: ; 0x0224DBB0
	str r1, [r0, #0x18]
	bx lr
	thumb_func_end MOD18_0224DBB0

	thumb_func_start MOD18_0224DBB4
MOD18_0224DBB4: ; 0x0224DBB4
	ldr r0, [r0, #0x24]
	bx lr
	thumb_func_end MOD18_0224DBB4

	thumb_func_start MOD18_0224DBB8
MOD18_0224DBB8: ; 0x0224DBB8
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x30]
	cmp r0, #8
	bge _0224DBCE
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224DBDE
_0224DBCE:
	ldr r0, _0224DBE0 ; =gMain
	ldr r1, [r0, #0x48]
	mov r0, #1
	tst r0, r1
	beq _0224DBDE
	add r0, r4, #0
	bl MOD18_0224DD94
_0224DBDE:
	pop {r4, pc}
	.align 2, 0
_0224DBE0: .word gMain
	thumb_func_end MOD18_0224DBB8

	thumb_func_start MOD18_0224DBE4
MOD18_0224DBE4: ; 0x0224DBE4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x40]
	ldr r2, [r4]
	lsl r0, r0, #0x1e
	asr r0, r0, #0x1f
	beq _0224DC04
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #4]
	bl StringExpandPlaceholders
	ldr r1, [r4, #0x40]
	mov r0, #2
	ldr r2, [r4, #4]
	bic r1, r0
	str r1, [r4, #0x40]
_0224DC04:
	add r0, r2, #0
	pop {r4, pc}
	thumb_func_end MOD18_0224DBE4

	thumb_func_start MOD18_0224DC08
MOD18_0224DC08: ; 0x0224DC08
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0
	add r6, r2, #0
	add r7, r3, #0
	bl MOD18_0224DD1C
	bl MOD18_0223D688
	add r0, r5, #0
	add r0, #8
	bl FUN_02019048
	cmp r0, #0
	bne _0224DC4C
	mov r0, #0x13
	str r0, [sp]
	mov r0, #0x1b
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, _0224DCAC ; =0x0000012D
	add r1, r5, #0
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x18]
	add r1, #8
	mov r2, #3
	mov r3, #2
	bl FUN_02019064
_0224DC4C:
	add r0, r5, #0
	add r0, #8
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r5, #0
	ldr r2, _0224DCB0 ; =0x000001E2
	add r0, #8
	mov r1, #1
	mov r3, #0xa
	bl FUN_0200D0BC
	cmp r4, #0
	beq _0224DC74
	ldr r0, _0224DCB4 ; =MOD18_0224DBB8
	add r1, r5, #0
	mov r2, #0x64
	bl FUN_0200CA44
	str r0, [r5, #0x20]
_0224DC74:
	ldr r1, [r5, #0x40]
	mov r0, #1
	bic r1, r0
	mov r0, #1
	orr r1, r0
	mov r0, #4
	bic r1, r0
	add r0, r5, #0
	str r1, [r5, #0x40]
	bl MOD18_0224DBE4
	mov r3, #0
	str r3, [sp]
	add r2, r0, #0
	ldr r0, [r5, #0x38]
	mov r1, #1
	str r0, [sp, #4]
	add r0, r5, #0
	str r3, [sp, #8]
	add r0, #8
	bl AddTextPrinterParameterized
	str r0, [r5, #0x30]
	str r6, [r5, #0x1c]
	str r7, [r5, #0x3c]
	ldr r0, [r5, #0x30]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224DCAC: .word 0x0000012D
_0224DCB0: .word 0x000001E2
_0224DCB4: .word MOD18_0224DBB8
	thumb_func_end MOD18_0224DC08

	thumb_func_start MOD18_0224DCB8
MOD18_0224DCB8: ; 0x0224DCB8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	ldr r0, [r5, #0x24]
	ldr r2, [r5]
	add r6, r3, #0
	bl ReadMsgDataIntoString
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD18_0224DC08
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DCB8

	thumb_func_start MOD18_0224DCD8
MOD18_0224DCD8: ; 0x0224DCD8
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r4, [r5, #0x38]
	mov r6, #0
	str r6, [r5, #0x38]
	bl MOD18_0224DCB8
	mov r1, #8
	str r1, [r5, #0x30]
	str r4, [r5, #0x38]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DCD8

	thumb_func_start MOD18_0224DCF0
MOD18_0224DCF0: ; 0x0224DCF0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r2, #0
	ldr r0, [r5, #0x24]
	ldr r2, [r5]
	add r6, r3, #0
	bl ReadMsgDataIntoString
	ldr r3, [sp, #0x10]
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD18_0224DC08
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DCF0

	thumb_func_start MOD18_0224DD10
MOD18_0224DD10: ; 0x0224DD10
	ldr r2, [r0, #0x40]
	mov r1, #4
	orr r1, r2
	str r1, [r0, #0x40]
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224DD10

	thumb_func_start MOD18_0224DD1C
MOD18_0224DD1C: ; 0x0224DD1C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	ldr r1, [r5, #0x40]
	lsl r0, r1, #0x1f
	asr r0, r0, #0x1f
	beq _0224DD92
	mov r0, #1
	bic r1, r0
	str r1, [r5, #0x40]
	ldr r0, [r5, #0x30]
	cmp r0, #8
	bge _0224DD4C
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _0224DD4C
	ldr r0, [r5, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
_0224DD4C:
	cmp r4, #1
	bne _0224DD6C
	add r0, r5, #0
	add r0, #8
	mov r1, #0
	bl FUN_0200D0E0
	add r0, r5, #0
	add r0, #8
	bl FUN_02019570
	add r0, r5, #0
	add r0, #8
	bl FUN_02019178
	b _0224DD76
_0224DD6C:
	add r0, r5, #0
	add r0, #8
	mov r1, #1
	bl FUN_0200D0E0
_0224DD76:
	mov r0, #8
	str r0, [r5, #0x30]
	ldr r0, [r5, #0x20]
	cmp r0, #0
	beq _0224DD88
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r5, #0x20]
_0224DD88:
	ldr r1, [r5, #0x1c]
	cmp r1, #0
	beq _0224DD92
	ldr r0, [r5, #0x3c]
	blx r1
_0224DD92:
	pop {r3, r4, r5, pc}
	thumb_func_end MOD18_0224DD1C

	thumb_func_start MOD18_0224DD94
MOD18_0224DD94: ; 0x0224DD94
	ldr r3, _0224DD9C ; =MOD18_0224DD1C
	mov r1, #1
	bx r3
	nop
_0224DD9C: .word MOD18_0224DD1C
	thumb_func_end MOD18_0224DD94

	thumb_func_start MOD18_0224DDA0
MOD18_0224DDA0: ; 0x0224DDA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #1
	bl BufferPlayersName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DDA0

	thumb_func_start MOD18_0224DDB8
MOD18_0224DDB8: ; 0x0224DDB8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #0
	bl BufferPlayersName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DDB8

	thumb_func_start MOD18_0224DDD0
MOD18_0224DDD0: ; 0x0224DDD0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #2
	bl BufferUndergroundItemNameWithArticle
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DDD0

	thumb_func_start MOD18_0224DDE8
MOD18_0224DDE8: ; 0x0224DDE8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #3
	bl BufferUndergroundTrapName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DDE8

	thumb_func_start MOD18_0224DE00
MOD18_0224DE00: ; 0x0224DE00
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #5
	bl BufferInterviewQuestion
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DE00

	thumb_func_start MOD18_0224DE18
MOD18_0224DE18: ; 0x0224DE18
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #5
	bl BufferInterviewAnswer
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DE18

	thumb_func_start MOD18_0224DE30
MOD18_0224DE30: ; 0x0224DE30
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl BufferInterviewAnswer
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DE30

	thumb_func_start MOD18_0224DE44
MOD18_0224DE44: ; 0x0224DE44
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	add r2, r1, #0
	mov r1, #2
	bl BufferDecorationName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DE44

	thumb_func_start MOD18_0224DE5C
MOD18_0224DE5C: ; 0x0224DE5C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r3, #1
	str r3, [sp, #4]
	ldr r0, [r4, #0x28]
	bl BufferIntegerAsString
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD18_0224DE5C

	thumb_func_start MOD18_0224DE7C
MOD18_0224DE7C: ; 0x0224DE7C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	add r2, r1, #0
	ldr r0, [r4, #0x28]
	mov r1, #6
	mov r3, #2
	bl BufferIntegerAsString
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DE7C

	thumb_func_start MOD18_0224DEA4
MOD18_0224DEA4: ; 0x0224DEA4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	mov r3, #2
	bl BufferIntegerAsString
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DEA4

	thumb_func_start MOD18_0224DEC8
MOD18_0224DEC8: ; 0x0224DEC8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	mov r0, #0
	str r0, [sp]
	mov r0, #1
	add r2, r1, #0
	str r0, [sp, #4]
	mov r1, #6
	ldr r0, [r4, #0x28]
	add r3, r1, #0
	bl BufferIntegerAsString
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DEC8

	thumb_func_start MOD18_0224DEF0
MOD18_0224DEF0: ; 0x0224DEF0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl BufferUndergroundItemName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DEF0

	thumb_func_start MOD18_0224DF04
MOD18_0224DF04: ; 0x0224DF04
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl BufferUndergroundTrapName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DF04

	thumb_func_start MOD18_0224DF18
MOD18_0224DF18: ; 0x0224DF18
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl BufferDecorationName
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DF18

	thumb_func_start MOD18_0224DF2C
MOD18_0224DF2C: ; 0x0224DF2C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl BufferUndergroundItemNameWithArticle
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DF2C

	thumb_func_start MOD18_0224DF40
MOD18_0224DF40: ; 0x0224DF40
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x28]
	bl BufferUndergroundTrapNameWithArticle
	ldr r1, [r4, #0x40]
	mov r0, #2
	orr r0, r1
	str r0, [r4, #0x40]
	pop {r4, pc}
	thumb_func_end MOD18_0224DF40

	thumb_func_start MOD18_0224DF54
MOD18_0224DF54: ; 0x0224DF54
	ldr r3, _0224DF5C ; =ScrStrBufs_UpperFirstChar
	ldr r0, [r0, #0x28]
	bx r3
	nop
_0224DF5C: .word ScrStrBufs_UpperFirstChar
	thumb_func_end MOD18_0224DF54

	thumb_func_start MOD18_0224DF60
MOD18_0224DF60: ; 0x0224DF60
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #8
	bge _0224DF84
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	beq _0224DF84
	ldr r0, [r4, #0x30]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD7C
	mov r0, #8
	str r0, [r4, #0x30]
_0224DF84:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DF60

	thumb_func_start MOD18_0224DF88
MOD18_0224DF88: ; 0x0224DF88
	push {r3, lr}
	ldr r0, [r0, #0x30]
	cmp r0, #8
	bne _0224DF94
	mov r0, #0
	pop {r3, pc}
_0224DF94:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0224DF88

	thumb_func_start MOD18_0224DFA0
MOD18_0224DFA0: ; 0x0224DFA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x30]
	cmp r0, #8
	bge _0224DFBA
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224DFBA
	mov r0, #8
	str r0, [r4, #0x30]
_0224DFBA:
	pop {r4, pc}
	thumb_func_end MOD18_0224DFA0

	thumb_func_start MOD18_0224DFBC
MOD18_0224DFBC: ; 0x0224DFBC
	lsl r1, r0, #1
	add r1, r0, r1
	ldr r0, _0224DFC8 ; =0x02250694
	ldrb r0, [r0, r1]
	bx lr
	nop
_0224DFC8: .word MOD18_02250694
	thumb_func_end MOD18_0224DFBC

	thumb_func_start MOD18_0224DFCC
MOD18_0224DFCC: ; 0x0224DFCC
	lsl r1, r0, #1
	add r1, r0, r1
	ldr r0, _0224DFD8 ; =0x02250695
	ldrb r0, [r0, r1]
	bx lr
	nop
_0224DFD8: .word MOD18_02250695
	thumb_func_end MOD18_0224DFCC

	thumb_func_start MOD18_0224DFDC
MOD18_0224DFDC: ; 0x0224DFDC
	lsl r1, r0, #1
	add r1, r0, r1
	ldr r0, _0224DFE8 ; =0x02250696
	ldrb r0, [r0, r1]
	bx lr
	nop
_0224DFE8: .word MOD18_02250696
	thumb_func_end MOD18_0224DFDC

	thumb_func_start MOD18_0224DFEC
MOD18_0224DFEC: ; 0x0224DFEC
	lsl r1, r0, #1
	add r1, r0, r1
	ldr r0, _0224DFF8 ; =0x02250748
	ldrb r0, [r0, r1]
	bx lr
	nop
_0224DFF8: .word MOD18_02250748
	thumb_func_end MOD18_0224DFEC

	thumb_func_start MOD18_0224DFFC
MOD18_0224DFFC: ; 0x0224DFFC
	lsl r1, r0, #1
	add r1, r0, r1
	ldr r0, _0224E008 ; =0x02250749
	ldrb r0, [r0, r1]
	bx lr
	nop
_0224E008: .word MOD18_02250749
	thumb_func_end MOD18_0224DFFC

	thumb_func_start MOD18_0224E00C
MOD18_0224E00C: ; 0x0224E00C
	lsl r1, r0, #1
	add r1, r0, r1
	ldr r0, _0224E018 ; =0x0225074A
	ldrb r0, [r0, r1]
	bx lr
	nop
_0224E018: .word MOD18_0225074A
	thumb_func_end MOD18_0224E00C

	thumb_func_start MOD18_0224E01C
MOD18_0224E01C: ; 0x0224E01C
	ldr r3, _0224E024 ; =AllocFromHeap
	mov r0, #4
	mov r1, #0x44
	bx r3
	.align 2, 0
_0224E024: .word AllocFromHeap
	thumb_func_end MOD18_0224E01C

	thumb_func_start MOD18_0224E028
MOD18_0224E028: ; 0x0224E028
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	str r1, [r0]
	mov r5, #0
	add r4, #0x38
	strb r5, [r4]
	str r2, [r0, #0x30]
	str r3, [r0, #0x34]
	add r0, #0x40
	strh r5, [r0]
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r1, #8]
	ldr r2, _0224E058 ; =0x000003D9
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_0224E058: .word 0x000003D9
	thumb_func_end MOD18_0224E028

	thumb_func_start MOD18_0224E05C
MOD18_0224E05C: ; 0x0224E05C
	ldr r3, _0224E060 ; =FreeToHeap
	bx r3
	.align 2, 0
_0224E060: .word FreeToHeap
	thumb_func_end MOD18_0224E05C

	thumb_func_start MOD18_0224E064
MOD18_0224E064: ; 0x0224E064
	ldr r0, [r0, #0x3c]
	bx lr
	thumb_func_end MOD18_0224E064

	thumb_func_start MOD18_0224E068
MOD18_0224E068: ; 0x0224E068
	push {r3, lr}
	add r1, r0, #0
	add r1, #0x38
	ldrb r1, [r1]
	cmp r1, #0
	beq _0224E07E
	cmp r1, #1
	beq _0224E084
	cmp r1, #2
	beq _0224E08A
	b _0224E09A
_0224E07E:
	bl MOD18_0224E0CC
	b _0224E09A
_0224E084:
	bl MOD18_0224E210
	b _0224E09A
_0224E08A:
	add r1, r0, #0
	mov r2, #0
	add r1, #0x38
	strb r2, [r1]
	bl MOD18_0224E26C
	mov r0, #1
	pop {r3, pc}
_0224E09A:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0224E068

	thumb_func_start MOD18_0224E0A0
MOD18_0224E0A0: ; 0x0224E0A0
	push {r4, lr}
	sub sp, #0x10
	ldr r3, _0224E0C8 ; =0x022507B0
	add r2, sp, #0
	add r4, r1, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	bl MOD18_0223D668
	lsl r2, r4, #2
	add r1, sp, #0
	ldr r1, [r1, r2]
	mov r2, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	add sp, #0x10
	pop {r4, pc}
	.align 2, 0
_0224E0C8: .word MOD18_022507B0
	thumb_func_end MOD18_0224E0A0

	thumb_func_start MOD18_0224E0CC
MOD18_0224E0CC: ; 0x0224E0CC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r0, #0
	mov r0, #4
	add r1, r0, #0
	bl ListMenuItems_ctor
	str r0, [r5, #0x24]
	mov r2, #3
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224E1F4 ; =0x000002CD
	add r1, r5, #4
	str r0, [sp, #0x10]
	ldr r0, [r5]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	mov r3, #1
	add r1, r5, #0
	str r3, [sp]
	mov r0, #7
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224E1F8 ; =0x000002BF
	add r1, #0x14
	str r0, [sp, #0x10]
	ldr r0, [r5]
	mov r2, #3
	ldr r0, [r0, #8]
	bl FUN_02019064
	ldr r2, _0224E1FC ; =0x000003D9
	add r0, r5, #4
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	ldr r2, _0224E1FC ; =0x000003D9
	add r0, #0x14
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r3, _0224E200 ; =0x022507C0
	add r2, sp, #0x14
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r2, _0224E204 ; =0x00000242
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	add r7, r0, #0
	add r0, r5, #0
	add r0, #0x14
	mov r1, #0xf
	bl FillWindowPixelBuffer
	add r0, r7, #0
	mov r1, #0
	bl NewString_ReadMsgData
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0x14
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r4, #0
	bl String_dtor
	mov r6, #0
	add r4, sp, #0x14
_0224E186:
	ldr r0, [r5, #0x24]
	ldr r2, [r4]
	add r1, r7, #0
	add r3, r6, #0
	bl ListMenuItems_AppendFromMsgData
	add r6, r6, #1
	add r4, r4, #4
	cmp r6, #4
	blt _0224E186
	add r0, r7, #0
	bl DestroyMsgData
	ldr r4, _0224E208 ; =0x022507D0
	add r3, sp, #0x24
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r3, #4
	add r0, sp, #0x14
	strh r3, [r0, #0x20]
	strh r3, [r0, #0x22]
	ldr r0, [r5, #0x24]
	str r0, [sp, #0x24]
	add r0, r5, #4
	str r0, [sp, #0x30]
	ldr r0, _0224E20C ; =MOD18_0224E0A0
	str r0, [sp, #0x28]
	add r0, r2, #0
	ldr r1, [r5, #0x30]
	ldr r2, [r5, #0x34]
	ldrh r1, [r1]
	ldrh r2, [r2]
	bl ListMenuInit
	str r0, [r5, #0x28]
	add r0, r5, #4
	bl CopyWindowToVram
	add r0, r5, #0
	add r0, #0x14
	bl CopyWindowToVram
	mov r0, #1
	add r5, #0x38
	strb r0, [r5]
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_0224E1F4: .word 0x000002CD
_0224E1F8: .word 0x000002BF
_0224E1FC: .word 0x000003D9
_0224E200: .word MOD18_022507C0
_0224E204: .word 0x00000242
_0224E208: .word MOD18_022507D0
_0224E20C: .word MOD18_0224E0A0
	thumb_func_end MOD18_0224E0CC

	thumb_func_start MOD18_0224E210
MOD18_0224E210: ; 0x0224E210
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x28]
	bl ListMenu_ProcessInput
	add r4, r0, #0
	add r0, r5, #0
	bl MOD18_0224E73C
	cmp r4, #3
	bne _0224E22A
	mov r4, #1
	mvn r4, r4
_0224E22A:
	mov r0, #1
	mvn r0, r0
	cmp r4, r0
	beq _0224E23A
	add r0, r0, #1
	cmp r4, r0
	bne _0224E250
	pop {r3, r4, r5, pc}
_0224E23A:
	ldr r0, _0224E268 ; =0x000005DC
	bl FUN_020054C8
	str r4, [r5, #0x3c]
	mov r0, #2
	add r5, #0x38
	strb r0, [r5]
	ldr r0, _0224E268 ; =0x000005DC
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
_0224E250:
	ldr r0, _0224E268 ; =0x000005DC
	bl FUN_020054C8
	str r4, [r5, #0x3c]
	mov r0, #2
	add r5, #0x38
	strb r0, [r5]
	ldr r0, _0224E268 ; =0x000005DC
	bl FUN_020054C8
	pop {r3, r4, r5, pc}
	nop
_0224E268: .word 0x000005DC
	thumb_func_end MOD18_0224E210

	thumb_func_start MOD18_0224E26C
MOD18_0224E26C: ; 0x0224E26C
	push {r4, lr}
	add r4, r0, #0
	bl MOD18_0223D668
	bl MOD18_0224DD94
	add r0, r4, #0
	add r0, #0x14
	mov r1, #1
	bl FUN_0200CCF8
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x30]
	ldr r2, [r4, #0x34]
	bl DestroyListMenu
	add r0, r4, #4
	mov r1, #1
	bl FUN_0200CCF8
	ldrb r1, [r4, #8]
	ldr r0, [r4, #4]
	bl FUN_0201AC68
	add r0, r4, #4
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02019178
	ldr r0, [r4, #0x24]
	bl ListMenuItems_dtor
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224E26C

	thumb_func_start MOD18_0224E2B4
MOD18_0224E2B4: ; 0x0224E2B4
	push {r3, lr}
	mov r2, #1
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	beq _0224E2CC
	add r1, r2, #0
	mov r2, #0xf
	mov r3, #2
	bl ListMenuOverrideSetColors
	pop {r3, pc}
_0224E2CC:
	mov r1, #2
	mov r2, #0xf
	add r3, r1, #0
	bl ListMenuOverrideSetColors
	pop {r3, pc}
	thumb_func_end MOD18_0224E2B4

	thumb_func_start MOD18_0224E2D8
MOD18_0224E2D8: ; 0x0224E2D8
	ldr r3, _0224E2E0 ; =AllocFromHeap
	mov r0, #4
	mov r1, #0x4c
	bx r3
	.align 2, 0
_0224E2E0: .word AllocFromHeap
	thumb_func_end MOD18_0224E2D8

	thumb_func_start MOD18_0224E2E4
MOD18_0224E2E4: ; 0x0224E2E4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r0, #0
	str r1, [r0]
	mov r5, #0
	add r4, #0x42
	strb r5, [r4]
	str r5, [r0, #4]
	str r2, [r0, #0x38]
	str r3, [r0, #0x3c]
	mov r0, #2
	str r0, [sp]
	mov r0, #4
	str r0, [sp, #4]
	ldr r0, [r1, #8]
	ldr r2, _0224E310 ; =0x000003D9
	mov r1, #3
	mov r3, #0xb
	bl FUN_0200CB00
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224E310: .word 0x000003D9
	thumb_func_end MOD18_0224E2E4

	thumb_func_start MOD18_0224E314
MOD18_0224E314: ; 0x0224E314
	add r3, r0, #0
	add r3, #0x40
	strb r1, [r3]
	add r0, #0x41
	strb r2, [r0]
	bx lr
	thumb_func_end MOD18_0224E314

	thumb_func_start MOD18_0224E320
MOD18_0224E320: ; 0x0224E320
	ldr r3, _0224E324 ; =FreeToHeap
	bx r3
	.align 2, 0
_0224E324: .word FreeToHeap
	thumb_func_end MOD18_0224E320

	thumb_func_start MOD18_0224E328
MOD18_0224E328: ; 0x0224E328
	ldr r0, [r0, #0x44]
	bx lr
	thumb_func_end MOD18_0224E328

	thumb_func_start MOD18_0224E32C
MOD18_0224E32C: ; 0x0224E32C
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	add r1, #0x42
	ldrb r1, [r1]
	cmp r1, #0
	beq _0224E344
	cmp r1, #1
	beq _0224E34A
	cmp r1, #2
	beq _0224E350
	b _0224E35E
_0224E344:
	bl MOD18_0224E430
	b _0224E35E
_0224E34A:
	bl MOD18_0224E36C
	b _0224E35E
_0224E350:
	mov r1, #0
	add r4, #0x42
	strb r1, [r4]
	bl MOD18_0224E6A8
	mov r0, #1
	pop {r4, pc}
_0224E35E:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0224E368
	bl FUN_0205EC18
_0224E368:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD18_0224E32C

	thumb_func_start MOD18_0224E36C
MOD18_0224E36C: ; 0x0224E36C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x2c]
	bl MOD18_02244140
	add r6, r0, #0
	ldr r0, [r5, #0x48]
	lsr r4, r6, #1
	cmp r0, r4
	bne _0224E384
	mov r4, #1
	mvn r4, r4
_0224E384:
	ldr r0, [r5, #0x2c]
	add r1, sp, #0
	ldr r0, [r0, #0xc]
	add r1, #2
	add r2, sp, #0
	bl ListMenuGetScrollAndRow
	ldr r0, [r5, #0x2c]
	mov r1, #2
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r7, r0, #0
	ldr r0, [r5, #0x2c]
	mov r1, #3
	ldr r0, [r0, #0xc]
	bl ListMenuGetTemplateField
	add r3, r0, #0
	add r1, sp, #0
	lsl r2, r7, #0x10
	lsl r3, r3, #0x10
	ldrh r1, [r1, #2]
	ldr r0, [r5, #4]
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl MOD18_0224E6F8
	mov r0, #1
	mvn r0, r0
	cmp r6, r0
	beq _0224E3CC
	add r0, r0, #1
	cmp r6, r0
	bne _0224E3DC
	pop {r3, r4, r5, r6, r7, pc}
_0224E3CC:
	str r0, [r5, #0x44]
	mov r0, #2
	add r5, #0x42
	strb r0, [r5]
	ldr r0, _0224E3EC ; =0x000005DC
	bl FUN_020054C8
	pop {r3, r4, r5, r6, r7, pc}
_0224E3DC:
	str r4, [r5, #0x44]
	mov r0, #2
	add r5, #0x42
	strb r0, [r5]
	ldr r0, _0224E3EC ; =0x000005DC
	bl FUN_020054C8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224E3EC: .word 0x000005DC
	thumb_func_end MOD18_0224E36C

	thumb_func_start MOD18_0224E3F0
MOD18_0224E3F0: ; 0x0224E3F0
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	mov r1, #0x13
	bl ListMenuGetTemplateField
	add r6, r0, #0
	add r0, r5, #0
	mov r1, #2
	bl ListMenuGetTemplateField
	lsr r1, r4, #1
	sub r0, r0, #1
	cmp r1, r0
	bne _0224E412
	ldr r4, _0224E42C ; =0x00000116
	b _0224E41C
_0224E412:
	add r0, r6, #0
	bl FUN_02025DC8
	add r4, r0, #0
	add r4, #0x8a
_0224E41C:
	bl MOD18_0223D678
	mov r2, #0
	add r1, r4, #0
	add r3, r2, #0
	bl MOD18_0224DCD8
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224E42C: .word 0x00000116
	thumb_func_end MOD18_0224E3F0

	thumb_func_start MOD18_0224E430
MOD18_0224E430: ; 0x0224E430
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x50
	add r5, r0, #0
	ldr r0, [r5]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r7, r0, #0
	bl FUN_02025DB0
	str r0, [sp, #0x20]
	str r0, [r5, #0x48]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	cmp r0, #7
	ble _0224E454
	mov r0, #7
	str r0, [sp, #0x1c]
_0224E454:
	ldr r0, [sp, #0x20]
	mov r1, #4
	add r0, r0, #1
	bl ListMenuItems_ctor
	str r0, [r5, #0x28]
	mov r2, #3
	str r2, [sp]
	mov r0, #0xc
	str r0, [sp, #4]
	ldr r0, [sp, #0x1c]
	add r1, r5, #0
	lsl r0, r0, #0x19
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224E680 ; =0x00000285
	add r1, #8
	str r0, [sp, #0x10]
	ldr r0, [r5]
	mov r3, #0x13
	ldr r0, [r0, #8]
	bl FUN_02019064
	mov r3, #1
	add r1, r5, #0
	str r3, [sp]
	mov r0, #8
	str r0, [sp, #4]
	mov r0, #4
	str r0, [sp, #8]
	mov r0, #0xd
	str r0, [sp, #0xc]
	ldr r0, _0224E684 ; =0x00000265
	add r1, #0x18
	str r0, [sp, #0x10]
	ldr r0, [r5]
	mov r2, #3
	ldr r0, [r0, #8]
	bl FUN_02019064
	add r0, r5, #0
	ldr r2, _0224E688 ; =0x000003D9
	add r0, #8
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	add r0, r5, #0
	ldr r2, _0224E688 ; =0x000003D9
	add r0, #0x18
	mov r1, #1
	mov r3, #0xb
	bl FUN_0200CCA4
	ldr r2, _0224E68C ; =0x00000237
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [sp, #0x18]
	ldr r2, _0224E690 ; =0x00000242
	mov r0, #0
	mov r1, #0x1a
	mov r3, #4
	bl NewMsgDataFromNarc
	str r0, [sp, #0x24]
	add r0, r5, #0
	add r0, #0x18
	mov r1, #0xf
	bl FillWindowPixelBuffer
	ldr r0, [sp, #0x24]
	mov r1, #9
	bl NewString_ReadMsgData
	str r0, [sp, #0x28]
	ldr r0, [sp, #0x24]
	mov r1, #0xa
	bl NewString_ReadMsgData
	str r0, [sp, #0x2c]
	mov r0, #6
	mov r1, #4
	bl String_ctor
	mov r1, #0
	add r4, r0, #0
	str r1, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	add r0, r5, #0
	ldr r2, [sp, #0x28]
	add r0, #0x18
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	mov r0, #4
	bl ScrStrBufs_new
	mov r1, #1
	str r1, [sp]
	add r2, r5, #0
	str r1, [sp, #4]
	add r2, #0x40
	ldrb r2, [r2]
	mov r1, #0
	mov r3, #2
	add r6, r0, #0
	bl BufferIntegerAsString
	mov r1, #1
	str r1, [sp]
	add r2, r5, #0
	str r1, [sp, #4]
	add r2, #0x41
	ldrb r2, [r2]
	add r0, r6, #0
	mov r3, #2
	bl BufferIntegerAsString
	ldr r2, [sp, #0x2c]
	add r0, r6, #0
	add r1, r4, #0
	bl StringExpandPlaceholders
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0xff
	str r0, [sp, #4]
	mov r1, #0
	add r0, r5, #0
	add r0, #0x18
	add r2, r4, #0
	add r3, r1, #0
	str r1, [sp, #8]
	bl AddTextPrinterParameterized
	add r0, r6, #0
	bl ScrStrBufs_delete
	ldr r0, [sp, #0x28]
	bl String_dtor
	ldr r0, [sp, #0x2c]
	bl String_dtor
	add r0, r4, #0
	bl String_dtor
	ldr r0, [sp, #0x24]
	bl DestroyMsgData
	ldr r0, [sp, #0x20]
	mov r4, #0
	cmp r0, #0
	ble _0224E5CE
	add r6, r4, #0
_0224E598:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02025DC8
	str r0, [sp, #0x14]
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02025F0C
	cmp r0, #0
	bne _0224E5B2
	mov r3, #1
	b _0224E5B4
_0224E5B2:
	mov r3, #0
_0224E5B4:
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	ldr r0, [r5, #0x28]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #0x14]
	add r3, r6, r3
	bl ListMenuItems_AppendFromMsgData
	ldr r0, [sp, #0x20]
	add r4, r4, #1
	add r6, r6, #2
	cmp r4, r0
	blt _0224E598
_0224E5CE:
	lsl r3, r4, #1
	ldr r0, [r5, #0x28]
	ldr r1, [sp, #0x18]
	ldr r2, _0224E694 ; =0x00000115
	add r3, r3, #1
	bl ListMenuItems_AppendFromMsgData
	ldr r0, [sp, #0x18]
	bl DestroyMsgData
	bl MOD18_0223D678
	ldr r1, _0224E68C ; =0x00000237
	mov r2, #0
	bl MOD18_0224DB80
	ldr r4, _0224E698 ; =0x022507D0
	add r3, sp, #0x30
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldr r0, _0224E69C ; =MOD18_0224E2B4
	add r1, sp, #0x30
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x20]
	mov r3, #4
	add r0, r0, #1
	strh r0, [r1, #0x10]
	ldr r0, [sp, #0x1c]
	strh r0, [r1, #0x12]
	ldr r0, [r5, #0x28]
	str r0, [sp, #0x30]
	add r0, r5, #0
	add r0, #8
	str r0, [sp, #0x3c]
	ldr r0, _0224E6A0 ; =MOD18_0224E3F0
	str r7, [sp, #0x4c]
	str r0, [sp, #0x34]
	ldr r0, _0224E6A4 ; =FUN_02025E20
	str r0, [sp]
	str r7, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	add r0, r2, #0
	ldr r1, [r5, #0x38]
	ldr r2, [r5, #0x3c]
	ldrh r1, [r1]
	ldrh r2, [r2]
	bl MOD18_02244028
	str r0, [r5, #0x2c]
	add r0, r5, #0
	add r0, #8
	bl CopyWindowToVram
	add r0, r5, #0
	add r0, #0x18
	bl CopyWindowToVram
	mov r0, #4
	bl FUN_0205EB38
	str r0, [r5, #4]
	mov r1, #0xc8
	mov r2, #0x1a
	mov r3, #0x86
	bl FUN_0205EC48
	mov r1, #0
	ldr r0, [r5, #4]
	add r2, r1, #0
	bl FUN_0205EC6C
	ldr r0, [r5, #4]
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
	mov r0, #1
	add r5, #0x42
	strb r0, [r5]
	add sp, #0x50
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224E680: .word 0x00000285
_0224E684: .word 0x00000265
_0224E688: .word 0x000003D9
_0224E68C: .word 0x00000237
_0224E690: .word 0x00000242
_0224E694: .word 0x00000115
_0224E698: .word MOD18_022507D0
_0224E69C: .word MOD18_0224E2B4
_0224E6A0: .word MOD18_0224E3F0
_0224E6A4: .word FUN_02025E20
	thumb_func_end MOD18_0224E430

	thumb_func_start MOD18_0224E6A8
MOD18_0224E6A8: ; 0x0224E6A8
	push {r4, lr}
	add r4, r0, #0
	bl MOD18_0223D678
	bl MOD18_0224DD94
	add r0, r4, #0
	add r0, #0x18
	mov r1, #1
	bl FUN_0200CCF8
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x38]
	ldr r2, [r4, #0x3c]
	bl MOD18_02244318
	add r0, r4, #0
	add r0, #8
	mov r1, #1
	bl FUN_0200CCF8
	ldrb r1, [r4, #0xc]
	ldr r0, [r4, #8]
	bl FUN_0201AC68
	add r0, r4, #0
	add r0, #8
	bl FUN_02019178
	add r0, r4, #0
	add r0, #0x18
	bl FUN_02019178
	ldr r0, [r4, #0x28]
	bl ListMenuItems_dtor
	ldr r0, [r4, #4]
	bl FUN_0205EBEC
	pop {r4, pc}
	thumb_func_end MOD18_0224E6A8

	thumb_func_start MOD18_0224E6F8
MOD18_0224E6F8: ; 0x0224E6F8
	push {r3, r4, r5, r6, r7, lr}
	add r4, r2, #0
	add r7, r3, #0
	add r6, r0, #0
	add r5, r1, #0
	cmp r4, r7
	bls _0224E738
	cmp r5, #0
	beq _0224E714
	mov r1, #0
	mov r2, #1
	bl FUN_0205EC6C
	b _0224E71C
_0224E714:
	mov r1, #0
	add r2, r1, #0
	bl FUN_0205EC6C
_0224E71C:
	add r0, r5, r7
	cmp r4, r0
	beq _0224E72E
	mov r1, #1
	add r0, r6, #0
	add r2, r1, #0
	bl FUN_0205EC6C
	pop {r3, r4, r5, r6, r7, pc}
_0224E72E:
	add r0, r6, #0
	mov r1, #1
	mov r2, #0
	bl FUN_0205EC6C
_0224E738:
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0224E6F8

	thumb_func_start MOD18_0224E73C
MOD18_0224E73C: ; 0x0224E73C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0x40
	ldrh r4, [r0]
	add r1, r5, #0
	ldr r0, [r5, #0x28]
	add r1, #0x40
	bl ListMenuGetCurrentItemArrayId
	add r5, #0x40
	ldrh r0, [r5]
	cmp r4, r0
	beq _0224E75C
	ldr r0, _0224E760 ; =0x000005DC
	bl FUN_020054C8
_0224E75C:
	pop {r3, r4, r5, pc}
	nop
_0224E760: .word 0x000005DC
	thumb_func_end MOD18_0224E73C

	thumb_func_start MOD18_0224E764
MOD18_0224E764: ; 0x0224E764
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r6, r0, #0
	add r7, r2, #0
	cmp r5, #0
	bne _0224E776
	bl ErrorHandling
_0224E776:
	add r4, r7, #0
	add r4, #0x3c
	add r0, r5, #0
	bl FUN_0204CA80
	str r0, [r4, #0x18]
	add r0, r5, #0
	bl FUN_0204CA90
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x18]
	lsl r1, r0, #0xf
	mov r0, #1
	lsl r0, r0, #0x14
	add r1, r1, r0
	lsr r0, r0, #8
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x1c]
	lsl r1, r0, #0xf
	mov r0, #0xd
	lsl r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp, #0x10]
	add r0, r6, #0
	add r1, r5, #0
	bl MOD18_0224FAEC
	add r2, r0, #0
	mov r0, #0
	str r0, [sp]
	ldr r0, [r6, #0x4c]
	add r3, sp, #8
	str r0, [sp, #4]
	add r0, r6, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r6, #0x2c]
	bl MOD05_021E7FBC
	str r0, [r4, #0x10]
	mov r0, #0x10
	str r0, [r7, #0x3c]
	mov r0, #0xd
	str r0, [r4, #4]
	ldr r0, [r4, #0x18]
	add r0, #0xf
	str r0, [r4, #8]
	ldr r0, [r4, #0x1c]
	add r0, #0xc
	str r0, [r4, #0xc]
	str r5, [r4, #0x14]
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0224E764

	thumb_func_start MOD18_0224E7E4
MOD18_0224E7E4: ; 0x0224E7E4
	add r2, r0, #0
	ldr r3, _0224E7F0 ; =MOD05_021E7C80
	add r2, #0xa0
	add r0, r1, #0
	ldr r1, [r2]
	bx r3
	.align 2, 0
_0224E7F0: .word MOD05_021E7C80
	thumb_func_end MOD18_0224E7E4

	thumb_func_start MOD18_0224E7F4
MOD18_0224E7F4: ; 0x0224E7F4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	mov r1, #0x24
	add r4, r0, #0
	mul r4, r1
	add r0, r5, r4
	ldr r0, [r0, #0x5c]
	cmp r0, #0
	bne _0224E80A
	bl ErrorHandling
_0224E80A:
	add r2, r5, r4
	add r2, #0x60
	add r5, #0x3c
	ldmia r2!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r2!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r2!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r2!, {r0, r1}
	stmia r5!, {r0, r1}
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0224E7F4

	thumb_func_start MOD18_0224E824
MOD18_0224E824: ; 0x0224E824
	push {r4, r5, r6, lr}
	add r5, r0, #0
	bl FUN_02046528
	add r6, r0, #0
	add r0, r5, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #7
	bhi _0224E93C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224E848: ; jump table
	.short _0224E858 - _0224E848 - 2 ; case 0
	.short _0224E8B4 - _0224E848 - 2 ; case 1
	.short _0224E8C0 - _0224E848 - 2 ; case 2
	.short _0224E8CC - _0224E848 - 2 ; case 3
	.short _0224E8D8 - _0224E848 - 2 ; case 4
	.short _0224E8E4 - _0224E848 - 2 ; case 5
	.short _0224E8F0 - _0224E848 - 2 ; case 6
	.short _0224E91A - _0224E848 - 2 ; case 7
_0224E858:
	mov r0, #4
	mov r1, #8
	bl FUN_0201669C
	bl MOD18_0224E01C
	ldr r3, _0224E940 ; =0x00000504
	add r1, r6, #0
	add r2, r3, #0
	str r0, [r4, r3]
	ldr r0, [r4, r3]
	add r2, #0x14
	add r3, #0x18
	add r2, r4, r2
	add r3, r4, r3
	bl MOD18_0224E028
	bl MOD18_0224E2D8
	ldr r3, _0224E944 ; =0x00000508
	add r1, r6, #0
	add r2, r3, #0
	str r0, [r4, r3]
	ldr r0, [r4, r3]
	add r2, #0x12
	add r3, #0x16
	add r2, r4, r2
	add r3, r4, r3
	bl MOD18_0224E2E4
	add r2, r4, #0
	add r0, r6, #0
	add r1, r4, #0
	add r2, #0x5c
	bl MOD18_0224F950
	add r1, r4, #0
	add r0, r6, #0
	add r1, #0x5c
	bl MOD18_0224FA50
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	b _0224E93C
_0224E8B4:
	ldr r1, _0224E948 ; =MOD18_0224E960
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	b _0224E93C
_0224E8C0:
	ldr r1, _0224E94C ; =MOD18_0224EAD4
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	b _0224E93C
_0224E8CC:
	ldr r1, _0224E950 ; =MOD18_0224EDDC
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	b _0224E93C
_0224E8D8:
	ldr r1, _0224E954 ; =MOD18_0224F258
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	b _0224E93C
_0224E8E4:
	ldr r1, _0224E958 ; =MOD18_0224F528
	add r0, r5, #0
	add r2, r4, #0
	bl FUN_0204640C
	b _0224E93C
_0224E8F0:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224E93C
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224E93C
	bl MOD18_0224712C
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	b _0224E93C
_0224E91A:
	ldr r0, _0224E944 ; =0x00000508
	ldr r0, [r4, r0]
	bl MOD18_0224E320
	ldr r0, _0224E940 ; =0x00000504
	ldr r0, [r4, r0]
	bl MOD18_0224E05C
	ldr r0, _0224E95C ; =0x0000050C
	ldr r0, [r4, r0]
	bl MOD05_021D80A4
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #1
	pop {r4, r5, r6, pc}
_0224E93C:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_0224E940: .word 0x00000504
_0224E944: .word 0x00000508
_0224E948: .word MOD18_0224E960
_0224E94C: .word MOD18_0224EAD4
_0224E950: .word MOD18_0224EDDC
_0224E954: .word MOD18_0224F258
_0224E958: .word MOD18_0224F528
_0224E95C: .word 0x0000050C
	thumb_func_end MOD18_0224E824

	thumb_func_start MOD18_0224E960
MOD18_0224E960: ; 0x0224E960
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, _0224EA68 ; =0x00000504
	ldr r0, [r4, r0]
	bl MOD18_0224E068
	cmp r0, #0
	beq _0224EA62
	ldr r0, _0224EA68 ; =0x00000504
	ldr r0, [r4, r0]
	bl MOD18_0224E064
	cmp r0, #0
	beq _0224E994
	cmp r0, #1
	beq _0224EA1C
	cmp r0, #2
	beq _0224EA34
	b _0224EA4C
_0224E994:
	ldr r0, [r5, #0xc]
	bl FUN_02026CC4
	bl FUN_02025DB0
	cmp r0, #0
	bne _0224E9BE
	mov r0, #0x13
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #6
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224E9BE:
	ldr r3, _0224EA6C ; =0x00000521
	ldrb r1, [r4, r3]
	cmp r1, #0xf
	bls _0224E9E2
	mov r0, #0x14
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #6
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224E9E2:
	add r0, r3, #3
	ldrb r2, [r4, r0]
	add r0, r1, #1
	cmp r0, r2
	ble _0224EA08
	mov r0, #0x14
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #6
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224EA08:
	sub r3, #0x19
	ldr r0, [r4, r3]
	bl MOD18_0224E314
	mov r0, #2
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224EA1C:
	ldr r2, _0224EA70 ; =0x000004FC
	mov r0, #0x10
	ldr r2, [r4, r2]
	mov r1, #0xd
	bl MOD18_0224FBDC
	mov r0, #3
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224EA34:
	ldr r2, _0224EA70 ; =0x000004FC
	mov r0, #0x10
	ldr r2, [r4, r2]
	mov r1, #0xd
	bl MOD18_0224FBDC
	mov r0, #4
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224EA4C:
	add r1, r4, #0
	add r0, r5, #0
	add r1, #0x5c
	bl MOD18_0224FAB4
	mov r0, #7
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224EA62:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_0224EA68: .word 0x00000504
_0224EA6C: .word 0x00000521
_0224EA70: .word 0x000004FC
	thumb_func_end MOD18_0224E960

	thumb_func_start MOD18_0224EA74
MOD18_0224EA74: ; 0x0224EA74
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	ldr r1, _0224EAC0 ; =0x00000528
	mov r0, #0xb
	bl AllocFromHeapAtEnd
	ldr r2, _0224EAC0 ; =0x00000528
	add r4, r0, #0
	mov r1, #0
	bl MI_CpuFill8
	mov r0, #0
	add r1, r4, #0
	bl MOD18_0224FB94
	mov r0, #5
	lsl r0, r0, #8
	str r5, [r4, r0]
	ldr r0, [r5, #4]
	ldr r1, _0224EAC4 ; =0x0225081C
	ldr r0, [r0, #4]
	bl MOD05_021D8024
	ldr r1, _0224EAC8 ; =0x0000050C
	str r0, [r4, r1]
	ldr r0, [r4, r1]
	bl MOD05_021D80E4
	ldr r1, _0224EACC ; =0x000004FC
	add r2, r4, #0
	str r0, [r4, r1]
	ldr r1, _0224EAD0 ; =MOD18_0224E824
	add r0, r6, #0
	bl FUN_0204640C
	pop {r4, r5, r6, pc}
	nop
_0224EAC0: .word 0x00000528
_0224EAC4: .word MOD18_0225081C
_0224EAC8: .word 0x0000050C
_0224EACC: .word 0x000004FC
_0224EAD0: .word MOD18_0224E824
	thumb_func_end MOD18_0224EA74

	thumb_func_start MOD18_0224EAD4
MOD18_0224EAD4: ; 0x0224EAD4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	add r4, r0, #0
	bl FUN_02046528
	add r5, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #5
	bhi _0224EB12
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224EAFA: ; jump table
	.short _0224EB06 - _0224EAFA - 2 ; case 0
	.short _0224EB88 - _0224EAFA - 2 ; case 1
	.short _0224EBA2 - _0224EAFA - 2 ; case 2
	.short _0224ED42 - _0224EAFA - 2 ; case 3
	.short _0224ED68 - _0224EAFA - 2 ; case 4
	.short _0224ED96 - _0224EAFA - 2 ; case 5
_0224EB06:
	ldr r0, _0224EDC0 ; =0x00000508
	ldr r0, [r4, r0]
	bl MOD18_0224E32C
	cmp r0, #0
	bne _0224EB14
_0224EB12:
	b _0224EDBA
_0224EB14:
	mov r0, #5
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r6, r0, #0
	ldr r0, _0224EDC0 ; =0x00000508
	ldr r0, [r4, r0]
	bl MOD18_0224E328
	add r7, r0, #0
	mov r0, #1
	mvn r0, r0
	cmp r7, r0
	bne _0224EB42
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x28
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224EB42:
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_02025DC8
	str r0, [sp, #4]
	cmp r0, #0
	beq _0224EB82
	add r0, r6, #0
	add r1, r7, #0
	bl FUN_02025F0C
	cmp r0, #0
	bne _0224EB6C
	ldr r1, [sp, #4]
	add r0, r5, #0
	add r2, r4, #0
	bl MOD18_0224E764
	mov r0, #1
	str r0, [r4, #4]
	b _0224EDBA
_0224EB6C:
	mov r0, #0x15
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #5
	str r0, [r4, #4]
	b _0224EDBA
_0224EB82:
	bl ErrorHandling
	b _0224EDBA
_0224EB88:
	ldr r0, _0224EDC4 ; =0x000004DC
	add r0, r4, r0
	bl MOD18_0224FF00
	ldr r2, _0224EDC4 ; =0x000004DC
	ldr r0, [r4, #0x4c]
	mov r1, #4
	add r2, r4, r2
	bl MOD18_0224FF14
	mov r0, #2
	str r0, [r4, #4]
	b _0224EDBA
_0224EBA2:
	ldr r1, _0224EDC4 ; =0x000004DC
	add r0, r5, #0
	add r1, r4, r1
	bl MOD18_0224FF24
	add r0, r4, #0
	add r1, r5, #0
	add r2, sp, #8
	bl MOD18_0224FD70
	cmp r0, #0
	bne _0224ECAE
	add r3, r4, #0
	add r3, #0x3c
	add r2, sp, #0x18
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, _0224EDC8 ; =gMain
	mov r1, #0x20
	ldr r0, [r0, #0x4c]
	mov r6, #1
	tst r1, r0
	beq _0224EBE8
	ldr r0, _0224EDCC ; =0xFFFF0000
	mov r7, #0
	str r0, [sp]
	ldr r0, [sp, #0x18]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	sub r0, r0, #1
	str r0, [sp, #0x20]
	b _0224EC3A
_0224EBE8:
	mov r1, #0x10
	add r2, r0, #0
	tst r2, r1
	beq _0224EC04
	lsl r0, r1, #0xc
	str r0, [sp]
	ldr r0, [sp, #0x18]
	mov r7, #0
	add r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	b _0224EC3A
_0224EC04:
	mov r1, #0x40
	tst r1, r0
	beq _0224EC1E
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	ldr r7, _0224EDCC ; =0xFFFF0000
	sub r0, r0, #1
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x24]
	sub r0, r0, #1
	str r0, [sp, #0x24]
	b _0224EC3A
_0224EC1E:
	mov r1, #0x80
	tst r0, r1
	beq _0224EC38
	mov r0, #0
	str r0, [sp]
	ldr r0, [sp, #0x1c]
	lsl r7, r1, #9
	add r0, r0, #1
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x24]
	add r0, r0, #1
	str r0, [sp, #0x24]
	b _0224EC3A
_0224EC38:
	mov r6, #0
_0224EC3A:
	cmp r6, #0
	beq _0224EC88
	add r0, sp, #0x18
	bl MOD18_0224F830
	cmp r0, #0
	bne _0224EC88
	add r2, r4, #0
	add r3, sp, #0x18
	add r2, #0x3c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r4, #0x4c]
	bl MOD05_021E7EEC
	add r6, r0, #0
	add r0, sp, #0xc
	add r1, r6, #0
	bl MOD05_021E7EA0
	ldr r1, [sp, #0xc]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	add r1, sp, #0xc
	add r0, r0, r7
	str r0, [sp, #0x14]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0x10]
	add r0, r6, #0
	bl MOD05_021E7EB0
_0224EC88:
	ldr r0, _0224EDC8 ; =gMain
	ldr r2, [r0, #0x48]
	mov r0, #1
	add r1, r2, #0
	tst r1, r0
	beq _0224EC98
	str r0, [sp, #8]
	b _0224ECAE
_0224EC98:
	mov r0, #2
	tst r0, r2
	beq _0224ECAE
	ldr r1, [r4, #0x4c]
	add r0, r5, #0
	bl MOD18_0224E7E4
	mov r0, #0
	add sp, #0x28
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0224ECAE:
	ldr r0, [sp, #8]
	cmp r0, #0
	bne _0224ECB6
	b _0224EDBA
_0224ECB6:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x3c
	add r1, #0x5c
	bl MOD18_0224F770
	cmp r0, #0
	beq _0224ED26
	mov r0, #5
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r6, r0, #0
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x3c
	add r1, #0x5c
	bl MOD18_0224F850
	add r7, r0, #0
	ldr r0, _0224EDC0 ; =0x00000508
	ldr r0, [r4, r0]
	bl MOD18_0224E328
	add r1, r0, #0
	add r0, r6, #0
	add r2, r7, #0
	bl FUN_02025EDC
	ldr r0, _0224EDD0 ; =0x000005FE
	bl FUN_020054C8
	ldr r0, [r4, #0x50]
	bl MOD18_02247138
	mov r0, #0xb
	bl MOD18_02247118
	ldr r1, _0224EDC4 ; =0x000004DC
	str r0, [r4, #8]
	add r0, r5, #0
	add r1, r4, r1
	bl MOD18_0224FF64
	ldr r0, _0224EDD4 ; =0x00000521
	ldrb r1, [r4, r0]
	add r1, r1, #1
	strb r1, [r4, r0]
	mov r1, #0
	sub r0, r0, #1
	strb r1, [r4, r0]
	mov r0, #4
	str r0, [r4, #4]
	b _0224EDBA
_0224ED26:
	ldr r0, _0224EDD8 ; =0x00000602
	bl FUN_020054C8
	mov r0, #0xc
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #3
	str r0, [r4, #4]
	b _0224EDBA
_0224ED42:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224EDBA
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224EDBA
	bl MOD18_0224712C
	mov r0, #2
	str r0, [r4, #4]
	b _0224EDBA
_0224ED68:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224EDBA
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224EDBA
	bl MOD18_0224712C
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x28
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224ED96:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224EDBA
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224EDBA
	bl MOD18_0224712C
	mov r0, #0
	str r0, [r4, #4]
_0224EDBA:
	mov r0, #0
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224EDC0: .word 0x00000508
_0224EDC4: .word 0x000004DC
_0224EDC8: .word gMain
_0224EDCC: .word 0xFFFF0000
_0224EDD0: .word 0x000005FE
_0224EDD4: .word 0x00000521
_0224EDD8: .word 0x00000602
	thumb_func_end MOD18_0224EAD4

	thumb_func_start MOD18_0224EDDC
MOD18_0224EDDC: ; 0x0224EDDC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl FUN_02046528
	add r7, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #6
	bls _0224EDF8
	b _0224F252
_0224EDF8:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224EE04: ; jump table
	.short _0224EE12 - _0224EE04 - 2 ; case 0
	.short _0224EE52 - _0224EE04 - 2 ; case 1
	.short _0224F122 - _0224EE04 - 2 ; case 2
	.short _0224F192 - _0224EE04 - 2 ; case 3
	.short _0224F1BC - _0224EE04 - 2 ; case 4
	.short _0224F1E2 - _0224EE04 - 2 ; case 5
	.short _0224F224 - _0224EE04 - 2 ; case 6
_0224EE12:
	ldr r0, _0224F148 ; =0x000004DC
	add r0, r4, r0
	bl MOD18_0224FF00
	ldr r0, _0224F14C ; =0x000004FC
	ldr r0, [r4, r0]
	bl MOD18_0224FBD4
	ldr r0, _0224F14C ; =0x000004FC
	add r2, r4, #0
	ldr r1, [r4, r0]
	add r2, #0x5c
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x68]
	add r3, sp, #0xc
	bl MOD18_0224F7EC
	cmp r0, #0
	beq _0224EE4C
	ldr r1, [sp, #0xc]
	mov r0, #0x24
	mul r0, r1
	add r0, r4, r0
	ldr r2, _0224F148 ; =0x000004DC
	ldr r0, [r0, #0x70]
	mov r1, #8
	add r2, r4, r2
	bl MOD18_0224FF14
_0224EE4C:
	mov r0, #1
	str r0, [r4, #4]
	b _0224F252
_0224EE52:
	ldr r1, _0224F148 ; =0x000004DC
	mov r0, #1
	str r0, [sp]
	add r0, r7, #0
	add r1, r4, r1
	bl MOD18_0224FF24
	add r0, r4, #0
	add r1, r7, #0
	add r2, sp, #0x10
	bl MOD18_0224FDDC
	ldr r1, _0224F14C ; =0x000004FC
	cmp r0, #0
	ldr r2, [r4, r1]
	ldr r2, [r2, #0x64]
	str r2, [sp, #0x14]
	ldr r2, [r4, r1]
	ldr r2, [r2, #0x64]
	str r2, [sp, #0x1c]
	ldr r2, [r4, r1]
	ldr r2, [r2, #0x68]
	str r2, [sp, #0x18]
	ldr r2, [r4, r1]
	ldr r2, [r2, #0x68]
	str r2, [sp, #0x20]
	ldr r2, [r4, r1]
	ldr r6, [r2, #0x58]
	ldr r5, [r2, #0x60]
	bne _0224EF54
	ldr r0, _0224F150 ; =gMain
	mov r2, #0x20
	ldr r0, [r0, #0x4c]
	tst r2, r0
	beq _0224EEB4
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	sub r6, r6, r0
	ldr r0, [sp, #0x14]
	sub r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	sub r0, r0, #1
	str r0, [sp, #0x1c]
	b _0224EF1E
_0224EEB4:
	mov r2, #0x10
	tst r2, r0
	beq _0224EED6
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	add r6, r6, r0
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	b _0224EF1E
_0224EED6:
	mov r2, #0x40
	tst r2, r0
	beq _0224EEF8
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	sub r5, r5, r0
	ldr r0, [sp, #0x18]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	sub r0, r0, #1
	str r0, [sp, #0x20]
	b _0224EF1E
_0224EEF8:
	mov r2, #0x80
	tst r0, r2
	beq _0224EF1A
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	add r5, r5, r0
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	b _0224EF1E
_0224EF1A:
	mov r0, #0
	str r0, [sp]
_0224EF1E:
	ldr r0, _0224F150 ; =gMain
	mov r1, #1
	ldr r0, [r0, #0x48]
	add r2, r0, #0
	tst r2, r1
	beq _0224EF2E
	str r1, [sp, #0x10]
	b _0224EF54
_0224EF2E:
	mov r1, #2
	tst r0, r1
	beq _0224EF54
	ldr r0, _0224F14C ; =0x000004FC
	ldr r0, [r4, r0]
	bl MOD18_0224FBF8
	ldr r1, _0224F148 ; =0x000004DC
	add r0, r7, #0
	add r1, r4, r1
	bl MOD18_0224FF64
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224EF54:
	ldr r0, [sp]
	cmp r0, #0
	beq _0224EFD6
	add r0, sp, #0x14
	bl MOD18_0224F830
	cmp r0, #0
	bne _0224EFD6
	ldr r0, _0224F14C ; =0x000004FC
	add r3, sp, #8
	ldr r1, [r4, r0]
	str r6, [r1, #0x58]
	ldr r1, [r4, r0]
	str r5, [r1, #0x60]
	ldr r2, [sp, #0x14]
	ldr r1, [r4, r0]
	str r2, [r1, #0x64]
	ldr r2, [sp, #0x18]
	ldr r1, [r4, r0]
	str r2, [r1, #0x68]
	ldr r1, [r4, r0]
	add r2, r4, #0
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x68]
	add r2, #0x5c
	bl MOD18_0224F7EC
	cmp r0, #0
	beq _0224EFC4
	ldr r0, _0224F148 ; =0x000004DC
	add r0, r4, r0
	bl MOD18_0224FF80
	ldr r2, [sp, #8]
	mov r1, #0x24
	mul r1, r2
	add r1, r4, r1
	ldr r1, [r1, #0x70]
	cmp r0, r1
	beq _0224EFD6
	ldr r1, _0224F148 ; =0x000004DC
	add r0, r7, #0
	add r1, r4, r1
	bl MOD18_0224FF64
	ldr r2, _0224F148 ; =0x000004DC
	ldr r1, [sp, #8]
	mov r0, #0x24
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x70]
	mov r1, #8
	add r2, r4, r2
	bl MOD18_0224FF14
	b _0224EFD6
_0224EFC4:
	ldr r1, _0224F148 ; =0x000004DC
	add r0, r7, #0
	add r1, r4, r1
	bl MOD18_0224FF64
	ldr r0, _0224F148 ; =0x000004DC
	add r0, r4, r0
	bl MOD18_0224FF00
_0224EFD6:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _0224F00E
	ldr r0, _0224F14C ; =0x000004FC
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x64]
	cmp r0, #0x20
	blt _0224EFEA
	bl ErrorHandling
_0224EFEA:
	ldr r0, _0224F14C ; =0x000004FC
	ldr r0, [r4, r0]
	ldr r0, [r0, #0x68]
	cmp r0, #0x20
	blt _0224EFF8
	bl ErrorHandling
_0224EFF8:
	ldr r0, _0224F14C ; =0x000004FC
	add r2, r4, #0
	ldr r1, [r4, r0]
	add r2, #0x5c
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x68]
	add r3, sp, #4
	bl MOD18_0224F7EC
	cmp r0, #0
	bne _0224F010
_0224F00E:
	b _0224F252
_0224F010:
	ldr r1, [sp, #4]
	cmp r1, #0
	beq _0224F10C
	mov r0, #0x24
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x74]
	bl MOD18_02247138
	ldr r1, [sp, #4]
	mov r0, #0x24
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x74]
	cmp r0, #6
	bne _0224F09E
	ldr r0, _0224F154 ; =0x00000523
	ldrb r1, [r4, r0]
	cmp r1, #0x10
	bne _0224F04E
	mov r0, #0xf
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #4
	str r0, [r4, #4]
	b _0224F252
_0224F04E:
	sub r0, r0, #1
	ldrb r0, [r4, r0]
	sub r0, r0, #1
	cmp r0, r1
	bge _0224F06E
	mov r0, #0x12
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #4
	str r0, [r4, #4]
	b _0224F252
_0224F06E:
	mov r0, #0x19
	lsl r0, r0, #6
	bl FUN_020054C8
	mov r0, #0xe
	bl MOD18_02247118
	str r0, [r4, #8]
	ldr r0, _0224F158 ; =0x00000522
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0224F08A
	bl ErrorHandling
_0224F08A:
	ldr r0, _0224F158 ; =0x00000522
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	mov r1, #0
	sub r0, r0, #2
	strb r1, [r4, r0]
	mov r0, #2
	str r0, [r4, #4]
	b _0224F0E0
_0224F09E:
	mov r0, #5
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	ldr r0, [r0, #0xc]
	bl FUN_02026CC4
	add r5, r0, #0
	ldr r0, _0224F15C ; =0x000005EB
	bl FUN_020054C8
	ldr r1, [sp, #4]
	add r0, r5, #0
	bl FUN_02025F30
	mov r0, #0xd
	bl MOD18_02247118
	str r0, [r4, #8]
	ldr r0, _0224F160 ; =0x00000521
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0224F0CE
	bl ErrorHandling
_0224F0CE:
	ldr r0, _0224F160 ; =0x00000521
	ldrb r1, [r4, r0]
	sub r1, r1, #1
	strb r1, [r4, r0]
	mov r1, #0
	sub r0, r0, #1
	strb r1, [r4, r0]
	mov r0, #3
	str r0, [r4, #4]
_0224F0E0:
	ldr r2, [sp, #4]
	mov r1, #0x24
	mul r1, r2
	add r1, r4, r1
	ldr r1, [r1, #0x70]
	add r0, r7, #0
	bl MOD18_0224E7E4
	add r1, r4, #0
	ldr r0, [sp, #4]
	add r1, #0x5c
	bl MOD18_0224F8CC
	ldr r0, _0224F14C ; =0x000004FC
	ldr r0, [r4, r0]
	bl MOD18_0224FBF8
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	b _0224F252
_0224F10C:
	mov r0, #0x16
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #4
	str r0, [r4, #4]
	b _0224F252
_0224F122:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F13E
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	bhs _0224F140
_0224F13E:
	b _0224F252
_0224F140:
	bl MOD18_0224712C
	ldr r0, _0224F158 ; =0x00000522
	b _0224F164
	.align 2, 0
_0224F148: .word 0x000004DC
_0224F14C: .word 0x000004FC
_0224F150: .word gMain
_0224F154: .word 0x00000523
_0224F158: .word 0x00000522
_0224F15C: .word 0x000005EB
_0224F160: .word 0x00000521
_0224F164:
	ldrb r1, [r4, r0]
	add r0, r0, #1
	ldrb r0, [r4, r0]
	sub r5, r1, r0
	bpl _0224F172
	bl ErrorHandling
_0224F172:
	cmp r5, #0
	bne _0224F184
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F184:
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #5
	str r0, [r4, #4]
	b _0224F252
_0224F192:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F252
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224F252
	bl MOD18_0224712C
	mov r0, #0
	str r0, [r4, #4]
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F1BC:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F252
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224F252
	bl MOD18_0224712C
	mov r0, #1
	str r0, [r4, #4]
	b _0224F252
_0224F1E2:
	mov r1, #0x52
	lsl r1, r1, #4
	ldrb r2, [r4, r1]
	add r0, r2, #1
	strb r0, [r4, r1]
	cmp r2, #0xa
	blo _0224F252
	add r0, r1, #2
	ldrb r2, [r4, r0]
	add r0, r1, #3
	ldrb r0, [r4, r0]
	mov r1, #0
	sub r5, r2, r0
	add r0, r5, #0
	bl MOD18_0224714C
	cmp r5, #1
	bne _0224F20E
	mov r0, #0x11
	bl MOD18_02247118
	b _0224F214
_0224F20E:
	mov r0, #0x19
	bl MOD18_02247118
_0224F214:
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #6
	str r0, [r4, #4]
	b _0224F252
_0224F224:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F252
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224F252
	bl MOD18_0224712C
	mov r0, #1
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F252:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224EDDC

	thumb_func_start MOD18_0224F258
MOD18_0224F258: ; 0x0224F258
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl FUN_02046528
	add r7, r0, #0
	add r0, r4, #0
	bl FUN_0204652C
	add r5, r0, #0
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _0224F27E
	cmp r0, #1
	beq _0224F2BE
	cmp r0, #2
	bne _0224F27C
	b _0224F4EC
_0224F27C:
	b _0224F510
_0224F27E:
	ldr r0, _0224F518 ; =0x000004DC
	add r0, r5, r0
	bl MOD18_0224FF00
	ldr r0, _0224F51C ; =0x000004FC
	ldr r0, [r5, r0]
	bl MOD18_0224FBD4
	ldr r0, _0224F51C ; =0x000004FC
	add r2, r5, #0
	ldr r1, [r5, r0]
	add r2, #0x5c
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x68]
	add r3, sp, #0xc
	bl MOD18_0224F7EC
	cmp r0, #0
	beq _0224F2B8
	ldr r1, [sp, #0xc]
	mov r0, #0x24
	mul r0, r1
	add r0, r5, r0
	ldr r2, _0224F518 ; =0x000004DC
	ldr r0, [r0, #0x70]
	mov r1, #8
	add r2, r5, r2
	bl MOD18_0224FF14
_0224F2B8:
	mov r0, #1
	str r0, [r5, #4]
	b _0224F510
_0224F2BE:
	ldr r1, _0224F518 ; =0x000004DC
	mov r0, #1
	str r0, [sp]
	add r0, r7, #0
	add r1, r5, r1
	bl MOD18_0224FF24
	add r0, r5, #0
	add r1, r7, #0
	add r2, sp, #0x10
	bl MOD18_0224FE4C
	ldr r1, _0224F51C ; =0x000004FC
	cmp r0, #0
	ldr r2, [r5, r1]
	ldr r2, [r2, #0x64]
	str r2, [sp, #0x14]
	ldr r2, [r5, r1]
	ldr r2, [r2, #0x64]
	str r2, [sp, #0x1c]
	ldr r2, [r5, r1]
	ldr r2, [r2, #0x68]
	str r2, [sp, #0x18]
	ldr r2, [r5, r1]
	ldr r2, [r2, #0x68]
	str r2, [sp, #0x20]
	ldr r2, [r5, r1]
	ldr r6, [r2, #0x58]
	ldr r4, [r2, #0x60]
	bne _0224F3C0
	ldr r0, _0224F520 ; =gMain
	mov r2, #0x20
	ldr r0, [r0, #0x4c]
	tst r2, r0
	beq _0224F320
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	sub r6, r6, r0
	ldr r0, [sp, #0x14]
	sub r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	sub r0, r0, #1
	str r0, [sp, #0x1c]
	b _0224F38A
_0224F320:
	mov r2, #0x10
	tst r2, r0
	beq _0224F342
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	add r6, r6, r0
	ldr r0, [sp, #0x14]
	add r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	add r0, r0, #1
	str r0, [sp, #0x1c]
	b _0224F38A
_0224F342:
	mov r2, #0x40
	tst r2, r0
	beq _0224F364
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	sub r4, r4, r0
	ldr r0, [sp, #0x18]
	sub r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	sub r0, r0, #1
	str r0, [sp, #0x20]
	b _0224F38A
_0224F364:
	mov r2, #0x80
	tst r0, r2
	beq _0224F386
	add r1, #0xe9
	add r0, r1, #0
	bl FUN_020054C8
	mov r0, #1
	lsl r0, r0, #0x10
	add r4, r4, r0
	ldr r0, [sp, #0x18]
	add r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	b _0224F38A
_0224F386:
	mov r0, #0
	str r0, [sp]
_0224F38A:
	ldr r0, _0224F520 ; =gMain
	mov r1, #1
	ldr r0, [r0, #0x48]
	add r2, r0, #0
	tst r2, r1
	beq _0224F39A
	str r1, [sp, #0x10]
	b _0224F3C0
_0224F39A:
	mov r1, #2
	tst r0, r1
	beq _0224F3C0
	ldr r0, _0224F51C ; =0x000004FC
	ldr r0, [r5, r0]
	bl MOD18_0224FBF8
	ldr r1, _0224F518 ; =0x000004DC
	add r0, r7, #0
	add r1, r5, r1
	bl MOD18_0224FF64
	mov r0, #1
	add r1, r5, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F3C0:
	ldr r0, [sp]
	cmp r0, #0
	beq _0224F442
	add r0, sp, #0x14
	bl MOD18_0224F830
	cmp r0, #0
	bne _0224F442
	ldr r0, _0224F51C ; =0x000004FC
	add r3, sp, #8
	ldr r1, [r5, r0]
	str r6, [r1, #0x58]
	ldr r1, [r5, r0]
	str r4, [r1, #0x60]
	ldr r2, [sp, #0x14]
	ldr r1, [r5, r0]
	str r2, [r1, #0x64]
	ldr r2, [sp, #0x18]
	ldr r1, [r5, r0]
	str r2, [r1, #0x68]
	ldr r1, [r5, r0]
	add r2, r5, #0
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x68]
	add r2, #0x5c
	bl MOD18_0224F7EC
	cmp r0, #0
	beq _0224F430
	ldr r0, _0224F518 ; =0x000004DC
	add r0, r5, r0
	bl MOD18_0224FF80
	ldr r2, [sp, #8]
	mov r1, #0x24
	mul r1, r2
	add r1, r5, r1
	ldr r1, [r1, #0x70]
	cmp r0, r1
	beq _0224F442
	ldr r1, _0224F518 ; =0x000004DC
	add r0, r7, #0
	add r1, r5, r1
	bl MOD18_0224FF64
	ldr r2, _0224F518 ; =0x000004DC
	ldr r1, [sp, #8]
	mov r0, #0x24
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x70]
	mov r1, #8
	add r2, r5, r2
	bl MOD18_0224FF14
	b _0224F442
_0224F430:
	ldr r1, _0224F518 ; =0x000004DC
	add r0, r7, #0
	add r1, r5, r1
	bl MOD18_0224FF64
	ldr r0, _0224F518 ; =0x000004DC
	add r0, r5, r0
	bl MOD18_0224FF00
_0224F442:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _0224F510
	ldr r0, _0224F51C ; =0x000004FC
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x64]
	cmp r0, #0x20
	blt _0224F456
	bl ErrorHandling
_0224F456:
	ldr r0, _0224F51C ; =0x000004FC
	ldr r0, [r5, r0]
	ldr r0, [r0, #0x68]
	cmp r0, #0x20
	blt _0224F464
	bl ErrorHandling
_0224F464:
	ldr r0, _0224F51C ; =0x000004FC
	add r2, r5, #0
	ldr r1, [r5, r0]
	add r2, #0x5c
	ldr r0, [r1, #0x64]
	ldr r1, [r1, #0x68]
	add r3, sp, #4
	bl MOD18_0224F7EC
	cmp r0, #0
	beq _0224F510
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _0224F4D6
	mov r1, #0x24
	mul r1, r0
	add r1, r5, r1
	ldr r1, [r1, #0x74]
	cmp r1, #6
	bne _0224F4A2
	mov r0, #0x10
	bl MOD18_02247118
	str r0, [r5, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r5, r0]
	mov r0, #2
	str r0, [r5, #4]
	b _0224F510
_0224F4A2:
	add r1, r5, #0
	bl MOD18_0224E7F4
	ldr r0, [sp, #4]
	add r1, r5, #0
	bl MOD18_0224FB04
	add r1, r5, #0
	ldr r0, [sp, #4]
	add r1, #0x5c
	bl MOD18_0224F8CC
	ldr r0, _0224F524 ; =0x000005EB
	bl FUN_020054C8
	ldr r0, _0224F51C ; =0x000004FC
	ldr r0, [r5, r0]
	bl MOD18_0224FBF8
	mov r0, #5
	add r1, r5, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F4D6:
	mov r0, #0x17
	bl MOD18_02247118
	str r0, [r5, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r5, r0]
	mov r0, #2
	str r0, [r5, #4]
	b _0224F510
_0224F4EC:
	ldr r0, [r5, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F510
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r5, r0]
	add r1, r2, #1
	strb r1, [r5, r0]
	cmp r2, #0x1e
	blo _0224F510
	bl MOD18_0224712C
	mov r0, #1
	str r0, [r5, #4]
_0224F510:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0224F518: .word 0x000004DC
_0224F51C: .word 0x000004FC
_0224F520: .word gMain
_0224F524: .word 0x000005EB
	thumb_func_end MOD18_0224F258

	thumb_func_start MOD18_0224F528
MOD18_0224F528: ; 0x0224F528
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r4, r0, #0
	bl FUN_02046528
	str r0, [sp]
	add r0, r4, #0
	bl FUN_0204652C
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #3
	bls _0224F544
	b _0224F750
_0224F544:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0224F550: ; jump table
	.short _0224F558 - _0224F550 - 2 ; case 0
	.short _0224F572 - _0224F550 - 2 ; case 1
	.short _0224F6FC - _0224F550 - 2 ; case 2
	.short _0224F722 - _0224F550 - 2 ; case 3
_0224F558:
	ldr r0, _0224F758 ; =0x000004DC
	add r0, r4, r0
	bl MOD18_0224FF00
	ldr r2, _0224F758 ; =0x000004DC
	ldr r0, [r4, #0x4c]
	mov r1, #4
	add r2, r4, r2
	bl MOD18_0224FF14
	mov r0, #1
	str r0, [r4, #4]
	b _0224F750
_0224F572:
	ldr r1, _0224F758 ; =0x000004DC
	ldr r0, [sp]
	add r1, r4, r1
	bl MOD18_0224FF24
	ldr r1, [sp]
	add r0, r4, #0
	add r2, sp, #4
	bl MOD18_0224FE94
	cmp r0, #0
	beq _0224F58C
	b _0224F692
_0224F58C:
	add r3, r4, #0
	add r3, #0x3c
	add r2, sp, #0x14
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, _0224F75C ; =gMain
	mov r1, #0x20
	ldr r0, [r0, #0x4c]
	mov r6, #1
	tst r1, r0
	beq _0224F5B8
	ldr r0, [sp, #0x14]
	ldr r7, _0224F760 ; =0xFFFF0000
	sub r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	mov r5, #0
	sub r0, r0, #1
	str r0, [sp, #0x1c]
	b _0224F604
_0224F5B8:
	mov r1, #0x10
	add r2, r0, #0
	tst r2, r1
	beq _0224F5D2
	ldr r0, [sp, #0x14]
	lsl r7, r1, #0xc
	add r0, r0, #1
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	mov r5, #0
	add r0, r0, #1
	str r0, [sp, #0x1c]
	b _0224F604
_0224F5D2:
	mov r1, #0x40
	tst r1, r0
	beq _0224F5EA
	ldr r0, [sp, #0x18]
	mov r7, #0
	sub r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	ldr r5, _0224F760 ; =0xFFFF0000
	sub r0, r0, #1
	str r0, [sp, #0x20]
	b _0224F604
_0224F5EA:
	mov r1, #0x80
	tst r0, r1
	beq _0224F602
	ldr r0, [sp, #0x18]
	mov r7, #0
	add r0, r0, #1
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x20]
	lsl r5, r1, #9
	add r0, r0, #1
	str r0, [sp, #0x20]
	b _0224F604
_0224F602:
	mov r6, #0
_0224F604:
	cmp r6, #0
	beq _0224F650
	add r0, sp, #0x14
	bl MOD18_0224F830
	cmp r0, #0
	bne _0224F650
	add r2, r4, #0
	add r3, sp, #0x14
	add r2, #0x3c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [sp]
	ldr r1, [r4, #0x4c]
	add r0, #0xa0
	ldr r0, [r0]
	bl MOD05_021E7EEC
	add r6, r0, #0
	add r0, sp, #8
	add r1, r6, #0
	bl MOD05_021E7EA0
	ldr r0, [sp, #8]
	add r1, sp, #8
	add r0, r0, r7
	str r0, [sp, #8]
	ldr r0, [sp, #0x10]
	add r0, r0, r5
	str r0, [sp, #0x10]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	add r0, r6, #0
	bl MOD05_021E7EB0
_0224F650:
	ldr r0, _0224F75C ; =gMain
	ldr r2, [r0, #0x48]
	mov r0, #1
	add r1, r2, #0
	tst r1, r0
	beq _0224F660
	str r0, [sp, #4]
	b _0224F692
_0224F660:
	mov r0, #2
	tst r0, r2
	beq _0224F692
	add r0, r4, #0
	add r2, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x1c
	add r2, #0x5c
	bl MOD18_0224F890
	add r0, r4, #0
	bl MOD18_0224FB64
	ldr r1, _0224F758 ; =0x000004DC
	ldr r0, [sp]
	add r1, r4, r1
	bl MOD18_0224FF64
	mov r0, #4
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F692:
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _0224F750
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0x3c
	add r1, #0x5c
	bl MOD18_0224F770
	cmp r0, #0
	beq _0224F6E0
	add r0, r4, #0
	add r2, r4, #0
	ldr r1, [r4, #0xc]
	add r0, #0x3c
	add r2, #0x5c
	bl MOD18_0224F890
	ldr r0, _0224F764 ; =0x000005FE
	bl FUN_020054C8
	ldr r2, _0224F768 ; =0x000004FC
	ldr r0, [r4, #0x3c]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, r2]
	bl MOD18_0224FBDC
	ldr r1, _0224F758 ; =0x000004DC
	ldr r0, [sp]
	add r1, r4, r1
	bl MOD18_0224FF64
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #3
	str r0, [r4, #4]
	b _0224F750
_0224F6E0:
	ldr r0, _0224F76C ; =0x00000602
	bl FUN_020054C8
	mov r0, #0xc
	bl MOD18_02247118
	str r0, [r4, #8]
	mov r0, #0x52
	mov r1, #0
	lsl r0, r0, #4
	strb r1, [r4, r0]
	mov r0, #2
	str r0, [r4, #4]
	b _0224F750
_0224F6FC:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F750
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224F750
	bl MOD18_0224712C
	mov r0, #1
	str r0, [r4, #4]
	b _0224F750
_0224F722:
	ldr r0, [r4, #8]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0
	bne _0224F750
	mov r0, #0x52
	lsl r0, r0, #4
	ldrb r2, [r4, r0]
	add r1, r2, #1
	strb r1, [r4, r0]
	cmp r2, #0x1e
	blo _0224F750
	bl MOD18_0224712C
	mov r0, #4
	add r1, r4, #0
	bl MOD18_0224FB94
	add sp, #0x24
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_0224F750:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0224F758: .word 0x000004DC
_0224F75C: .word gMain
_0224F760: .word 0xFFFF0000
_0224F764: .word 0x000005FE
_0224F768: .word 0x000004FC
_0224F76C: .word 0x00000602
	thumb_func_end MOD18_0224F528

	thumb_func_start MOD18_0224F770
MOD18_0224F770: ; 0x0224F770
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r1, #0
	add r7, r0, #0
	mov r6, #0
	add r4, r5, #0
_0224F77C:
	ldr r0, [r5]
	cmp r0, #1
	bne _0224F794
	add r0, r4, #4
	add r1, r7, #0
	bl MOD18_0224F908
	cmp r0, #0
	beq _0224F794
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224F794:
	add r6, r6, #1
	add r5, #0x24
	add r4, #0x24
	cmp r6, #0x20
	blt _0224F77C
	ldr r4, _0224F7E4 ; =0x0225080C
	add r3, sp, #0x10
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r7, #0
	add r1, r2, #0
	bl MOD18_0224F908
	cmp r0, #0
	beq _0224F7BE
	add sp, #0x20
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0224F7BE:
	ldr r4, _0224F7E8 ; =0x022507FC
	add r3, sp, #0
	add r2, r3, #0
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r3!, {r0, r1}
	add r0, r7, #0
	add r1, r2, #0
	bl MOD18_0224F908
	cmp r0, #0
	bne _0224F7DE
	add sp, #0x20
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224F7DE:
	mov r0, #0
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0224F7E4: .word MOD18_0225080C
_0224F7E8: .word MOD18_022507FC
	thumb_func_end MOD18_0224F770

	thumb_func_start MOD18_0224F7EC
MOD18_0224F7EC: ; 0x0224F7EC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r2, #0
	add r7, r0, #0
	str r1, [sp]
	str r3, [sp, #4]
	mov r6, #0
	add r4, r5, #0
_0224F7FC:
	ldr r0, [r5]
	cmp r0, #1
	bne _0224F81A
	ldr r2, [sp]
	add r0, r4, #4
	add r1, r7, #0
	bl MOD18_0224F930
	cmp r0, #0
	beq _0224F81A
	ldr r0, [sp, #4]
	add sp, #8
	str r6, [r0]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0224F81A:
	add r6, r6, #1
	add r5, #0x24
	add r4, #0x24
	cmp r6, #0x20
	blt _0224F7FC
	ldr r0, [sp, #4]
	mov r1, #0x20
	str r1, [r0]
	mov r0, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224F7EC

	thumb_func_start MOD18_0224F830
MOD18_0224F830: ; 0x0224F830
	ldr r1, [r0]
	cmp r1, #0xa
	blt _0224F84C
	ldr r1, [r0, #8]
	cmp r1, #0x15
	bgt _0224F84C
	ldr r1, [r0, #4]
	cmp r1, #0xc
	blt _0224F84C
	ldr r0, [r0, #0xc]
	cmp r0, #0x17
	bgt _0224F84C
	mov r0, #0
	bx lr
_0224F84C:
	mov r0, #1
	bx lr
	thumb_func_end MOD18_0224F830

	thumb_func_start MOD18_0224F850
MOD18_0224F850: ; 0x0224F850
	push {r4, lr}
	add r3, r0, #0
	mov r2, #0
	add r4, r1, #0
_0224F858:
	ldr r0, [r4]
	cmp r0, #0
	bne _0224F880
	mov r0, #0x24
	add r4, r2, #0
	mul r4, r0
	mov r0, #1
	str r0, [r1, r4]
	add r0, r1, r4
	add r4, r0, #4
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	add r0, r2, #0
	pop {r4, pc}
_0224F880:
	add r2, r2, #1
	add r4, #0x24
	cmp r2, #0x20
	blt _0224F858
	bl ErrorHandling
	mov r0, #0
	pop {r4, pc}
	thumb_func_end MOD18_0224F850

	thumb_func_start MOD18_0224F890
MOD18_0224F890: ; 0x0224F890
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	add r4, r2, #0
	cmp r7, #0x20
	blt _0224F8A0
	bl ErrorHandling
_0224F8A0:
	mov r0, #0x24
	add r6, r7, #0
	mul r6, r0
	ldr r0, [r4, r6]
	cmp r0, #0
	beq _0224F8B0
	bl ErrorHandling
_0224F8B0:
	mov r0, #1
	str r0, [r4, r6]
	add r0, r4, r6
	add r2, r0, #4
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r2!, {r0, r1}
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0224F890

	thumb_func_start MOD18_0224F8CC
MOD18_0224F8CC: ; 0x0224F8CC
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	cmp r5, #0x20
	blt _0224F8DA
	bl ErrorHandling
_0224F8DA:
	cmp r5, #0
	bne _0224F8E2
	bl ErrorHandling
_0224F8E2:
	mov r0, #0x24
	add r6, r5, #0
	mul r6, r0
	ldr r0, [r4, r6]
	cmp r0, #0
	bne _0224F8F2
	bl ErrorHandling
_0224F8F2:
	mov r1, #0
	add r0, r4, r6
	str r1, [r0, #0x14]
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x10]
	str r1, [r0, #0x18]
	str r1, [r4, r6]
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_0224F8CC

	thumb_func_start MOD18_0224F908
MOD18_0224F908: ; 0x0224F908
	ldr r3, [r0]
	ldr r2, [r1, #8]
	cmp r3, r2
	bgt _0224F92C
	ldr r3, [r1]
	ldr r2, [r0, #8]
	cmp r3, r2
	bgt _0224F92C
	ldr r3, [r0, #4]
	ldr r2, [r1, #0xc]
	cmp r3, r2
	bgt _0224F92C
	ldr r1, [r1, #4]
	ldr r0, [r0, #0xc]
	cmp r1, r0
	bgt _0224F92C
	mov r0, #1
	bx lr
_0224F92C:
	mov r0, #0
	bx lr
	thumb_func_end MOD18_0224F908

	thumb_func_start MOD18_0224F930
MOD18_0224F930: ; 0x0224F930
	ldr r3, [r0]
	cmp r3, r1
	bgt _0224F94C
	ldr r3, [r0, #8]
	cmp r1, r3
	bgt _0224F94C
	ldr r1, [r0, #4]
	cmp r1, r2
	bgt _0224F94C
	ldr r0, [r0, #0xc]
	cmp r2, r0
	bgt _0224F94C
	mov r0, #1
	bx lr
_0224F94C:
	mov r0, #0
	bx lr
	thumb_func_end MOD18_0224F930

	thumb_func_start MOD18_0224F950
MOD18_0224F950: ; 0x0224F950
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	ldr r0, [r0, #0xc]
	add r6, r1, #0
	str r2, [sp, #4]
	bl FUN_02026CA8
	ldr r1, _0224F9E4 ; =0x00000521
	mov r2, #0
	strb r2, [r6, r1]
	add r1, r1, #1
	add r7, r0, #0
	strb r2, [r6, r1]
	bl FUN_02026874
	ldr r1, _0224F9E8 ; =0x00000523
	strb r0, [r6, r1]
	add r0, r7, #0
	bl FUN_020268A0
	ldr r1, _0224F9EC ; =0x00000524
	mov r4, #0
	strb r0, [r6, r1]
_0224F97E:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_020267C4
	add r5, r0, #0
	beq _0224F9DA
	cmp r5, #6
	bne _0224F99A
	ldr r0, _0224F9F0 ; =0x00000522
	ldrb r0, [r6, r0]
	add r1, r0, #1
	ldr r0, _0224F9F0 ; =0x00000522
	strb r1, [r6, r0]
	b _0224F9B8
_0224F99A:
	cmp r5, #1
	beq _0224F9B8
	cmp r5, #2
	beq _0224F9B8
	cmp r5, #3
	beq _0224F9B8
	cmp r5, #4
	beq _0224F9B8
	cmp r5, #5
	beq _0224F9B8
	ldr r0, _0224F9E4 ; =0x00000521
	ldrb r0, [r6, r0]
	add r1, r0, #1
	ldr r0, _0224F9E4 ; =0x00000521
	strb r1, [r6, r0]
_0224F9B8:
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02026810
	str r0, [sp, #8]
	add r0, r7, #0
	add r1, r4, #0
	bl FUN_02026840
	add r3, r0, #0
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	str r0, [sp]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD18_0224F9F4
_0224F9DA:
	add r4, r4, #1
	cmp r4, #0x20
	blt _0224F97E
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0224F9E4: .word 0x00000521
_0224F9E8: .word 0x00000523
_0224F9EC: .word 0x00000524
_0224F9F0: .word 0x00000522
	thumb_func_end MOD18_0224F950

	thumb_func_start MOD18_0224F9F4
MOD18_0224F9F4: ; 0x0224F9F4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r0, #0
	mov r0, #0
	add r5, r2, #0
	add r6, r3, #0
	str r0, [sp, #0x14]
	add r0, r1, #0
	str r1, [sp]
	ldr r4, [sp, #0x38]
	str r0, [sp, #0x18]
	str r5, [sp, #4]
	str r6, [sp, #8]
	bl FUN_0204CA80
	str r0, [sp, #0x1c]
	ldr r0, [sp]
	bl FUN_0204CA90
	str r0, [sp, #0x20]
	sub r0, r0, #1
	add r0, r6, r0
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x10]
	sub r1, r1, #1
	add r1, r5, r1
	mov r0, #0x24
	add r2, r7, #0
	mul r2, r0
	add r0, r4, r2
	add r5, sp, #4
	add r3, r0, #4
	str r1, [sp, #0xc]
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	ldmia r5!, {r0, r1}
	stmia r3!, {r0, r1}
	mov r0, #1
	str r0, [r4, r2]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD18_0224F9F4

	thumb_func_start MOD18_0224FA50
MOD18_0224FA50: ; 0x0224FA50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r0, #0xa0
	ldr r0, [r0]
	add r4, r1, #0
	bl MOD05_021E7C1C
	mov r7, #1
	mov r6, #0
	lsl r7, r7, #0xc
_0224FA66:
	ldr r0, [r4]
	cmp r0, #0
	beq _0224FAA8
	ldr r1, [r4, #0x18]
	add r0, r5, #0
	bl MOD18_0224FAEC
	add r2, r0, #0
	ldr r0, [r4, #4]
	ldr r3, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	lsl r0, r0, #0x10
	lsl r3, r3, #0xf
	add r0, r0, r3
	str r0, [sp, #8]
	ldr r0, [r4, #8]
	lsl r1, r1, #0xf
	lsl r0, r0, #0x10
	add r0, r0, r1
	str r0, [sp, #0x10]
	str r7, [sp, #0xc]
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5, #0x4c]
	add r3, sp, #8
	str r0, [sp, #4]
	add r0, r5, #0
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r5, #0x2c]
	bl MOD05_021E7FBC
	str r0, [r4, #0x14]
_0224FAA8:
	add r6, r6, #1
	add r4, #0x24
	cmp r6, #0x20
	blt _0224FA66
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224FA50

	thumb_func_start MOD18_0224FAB4
MOD18_0224FAB4: ; 0x0224FAB4
	push {r3, r4, r5, r6, r7, lr}
	ldr r0, [r0, #0xc]
	add r5, r1, #0
	bl FUN_02026CA8
	mov r4, #0
	add r6, r0, #0
	add r7, r4, #0
_0224FAC4:
	ldr r0, [r5]
	cmp r0, #1
	bne _0224FAD2
	ldr r2, [r5, #0x18]
	ldr r3, [r5, #4]
	ldr r0, [r5, #8]
	b _0224FAD8
_0224FAD2:
	add r2, r7, #0
	add r3, r7, #0
	add r0, r7, #0
_0224FAD8:
	str r0, [sp]
	add r0, r6, #0
	add r1, r4, #0
	bl FUN_0202671C
	add r4, r4, #1
	add r5, #0x24
	cmp r4, #0x20
	blt _0224FAC4
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD18_0224FAB4

	thumb_func_start MOD18_0224FAEC
MOD18_0224FAEC: ; 0x0224FAEC
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bne _0224FAF8
	bl ErrorHandling
_0224FAF8:
	ldr r0, [r5, #0x2c]
	add r1, r4, #0
	bl MOD05_021F4CD4
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD18_0224FAEC

	thumb_func_start MOD18_0224FB04
MOD18_0224FB04: ; 0x0224FB04
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r6, r0, #0
	mov r0, #0x24
	add r4, r6, #0
	add r5, r1, #0
	mul r4, r0
	add r0, r5, r4
	ldr r0, [r0, #0x5c]
	cmp r0, #0
	bne _0224FB1E
	bl ErrorHandling
_0224FB1E:
	add r0, r5, #0
	add r0, #0x60
	add r4, r0, r4
	mov r0, #5
	lsl r0, r0, #8
	ldr r0, [r5, r0]
	ldr r1, [r4, #0x10]
	add r0, #0xa0
	ldr r0, [r0]
	bl MOD05_021E7EEC
	add r1, r0, #0
	add r0, sp, #0
	bl MOD05_021E7EA0
	add r3, sp, #0
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0x10
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	str r6, [r5, #0xc]
	add r5, #0x1c
	ldmia r4!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r4!, {r0, r1}
	stmia r5!, {r0, r1}
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD18_0224FB04

	thumb_func_start MOD18_0224FB64
MOD18_0224FB64: ; 0x0224FB64
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0xc]
	mov r0, #0x24
	mul r0, r1
	add r0, r4, r0
	ldr r0, [r0, #0x5c]
	cmp r0, #0
	bne _0224FB7A
	bl ErrorHandling
_0224FB7A:
	mov r0, #5
	lsl r0, r0, #8
	ldr r0, [r4, r0]
	ldr r1, [r4, #0x2c]
	add r0, #0xa0
	ldr r0, [r0]
	bl MOD05_021E7EEC
	add r4, #0x10
	add r1, r4, #0
	bl MOD05_021E7EB0
	pop {r4, pc}
	thumb_func_end MOD18_0224FB64

	thumb_func_start MOD18_0224FB94
MOD18_0224FB94: ; 0x0224FB94
	str r0, [r1]
	mov r0, #0
	str r0, [r1, #4]
	bx lr
	thumb_func_end MOD18_0224FB94

	thumb_func_start MOD18_0224FB9C
MOD18_0224FB9C: ; 0x0224FB9C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, #0x54
	str r0, [sp]
	ldr r1, _0224FBC4 ; =0x02251350
	mov r0, #4
	add r2, r4, #0
	add r3, sp, #4
	bl FUN_0201B21C
	mov r0, #0
	str r0, [r4, #0x58]
	str r0, [r4, #0x5c]
	str r0, [r4, #0x60]
	str r0, [r4, #0x64]
	str r0, [r4, #0x68]
	str r0, [r4, #0x6c]
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_0224FBC4: .word MOD18_02251350
	thumb_func_end MOD18_0224FB9C

	thumb_func_start MOD18_0224FBC8
MOD18_0224FBC8: ; 0x0224FBC8
	ldr r3, _0224FBD0 ; =FreeToHeap
	ldr r0, [r0, #0x54]
	bx r3
	nop
_0224FBD0: .word FreeToHeap
	thumb_func_end MOD18_0224FBC8

	thumb_func_start MOD18_0224FBD4
MOD18_0224FBD4: ; 0x0224FBD4
	mov r1, #1
	str r1, [r0, #0x6c]
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224FBD4

	thumb_func_start MOD18_0224FBDC
MOD18_0224FBDC: ; 0x0224FBDC
	str r0, [r2, #0x64]
	lsl r3, r0, #0x10
	mov r0, #2
	lsl r0, r0, #0xe
	str r1, [r2, #0x68]
	add r3, r3, r0
	str r3, [r2, #0x58]
	lsr r3, r0, #3
	lsl r1, r1, #0x10
	str r3, [r2, #0x5c]
	add r0, r1, r0
	str r0, [r2, #0x60]
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224FBDC

	thumb_func_start MOD18_0224FBF8
MOD18_0224FBF8: ; 0x0224FBF8
	mov r1, #0
	str r1, [r0, #0x6c]
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224FBF8

	thumb_func_start MOD18_0224FC00
MOD18_0224FC00: ; 0x0224FC00
	ldr r3, _0224FC14 ; =0x0000FFFF
	cmp r0, r3
	beq _0224FC08
	str r0, [r2]
_0224FC08:
	ldr r0, _0224FC14 ; =0x0000FFFF
	cmp r1, r0
	beq _0224FC10
	str r1, [r2, #4]
_0224FC10:
	bx lr
	nop
_0224FC14: .word 0x0000FFFF
	thumb_func_end MOD18_0224FC00

	thumb_func_start MOD18_0224FC18
MOD18_0224FC18: ; 0x0224FC18
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	str r0, [sp]
	add r0, #0x88
	ldr r1, _0224FCD4 ; =gMain + 0x40
	ldr r6, [r0]
	ldrh r0, [r1, #0x1c]
	ldrh r1, [r1, #0x1e]
	add r4, r2, #0
	bl MOD18_0224FC00
	ldr r1, [r4]
	ldr r2, [r4, #4]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #8
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	add r3, r6, #0
	bl MOD05_021F0318
	ldr r1, [sp, #8]
	mov r3, #0x1b
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	ldr r1, [sp, #0x10]
	str r0, [sp, #4]
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r7, r0, #0x10
	ldr r0, [sp, #4]
	ldr r1, [sp, #4]
	lsr r0, r0, #0x1f
	lsl r1, r1, #0x1b
	sub r1, r1, r0
	ror r1, r3
	add r2, r0, r1
	lsr r1, r7, #0x1f
	lsl r0, r7, #0x1b
	sub r0, r0, r1
	ror r0, r3
	ldr r6, [r5, #0x18]
	ldr r4, [r5, #0x1c]
	add r0, r1, r0
	sub r1, r6, #1
	add r1, r2, r1
	str r1, [sp, #0x1c]
	sub r1, r4, #1
	str r0, [sp, #0x18]
	add r0, r0, r1
	str r0, [sp, #0x20]
	add r0, sp, #0x14
	str r2, [sp, #0x14]
	bl MOD18_0224F830
	cmp r0, #0
	bne _0224FCCE
	add r3, sp, #0x14
	add r2, r5, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [sp, #4]
	lsl r1, r7, #0x10
	lsl r2, r0, #0x10
	lsl r0, r6, #0xf
	str r2, [sp, #8]
	add r0, r2, r0
	str r0, [sp, #8]
	lsl r0, r4, #0xf
	str r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [sp, #0x10]
	mov r0, #1
	lsl r0, r0, #0xc
	str r0, [sp, #0xc]
	ldr r0, [sp]
	ldr r1, [r5, #0x10]
	add r0, #0xa0
	str r0, [sp]
	ldr r0, [r0]
	bl MOD05_021E7EEC
	add r1, sp, #8
	bl MOD05_021E7EB0
_0224FCCE:
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0224FCD4: .word gMain + 0x40
	thumb_func_end MOD18_0224FC18

	thumb_func_start MOD18_0224FCD8
MOD18_0224FCD8: ; 0x0224FCD8
	push {r3, r4, r5, r6, lr}
	sub sp, #0x1c
	add r4, r1, #0
	add r0, #0x88
	ldr r1, _0224FD6C ; =gMain + 0x40
	ldr r5, [r0]
	ldrh r0, [r1, #0x1c]
	add r6, r2, #0
	ldrh r1, [r1, #0x1e]
	add r2, r4, #0
	bl MOD18_0224FC00
	ldr r1, [r4]
	ldr r2, [r4, #4]
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, sp, #0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	add r3, r5, #0
	bl MOD05_021F0318
	ldr r1, [sp]
	mov r2, #0x1b
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	ldr r1, [sp, #8]
	asr r4, r0, #0x10
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r5, r0, #0x10
	lsr r1, r4, #0x1f
	lsl r0, r4, #0x1b
	sub r0, r0, r1
	ror r0, r2
	add r0, r1, r0
	lsr r3, r5, #0x1f
	lsl r1, r5, #0x1b
	sub r1, r1, r3
	ror r1, r2
	add r1, r3, r1
	str r0, [sp, #0xc]
	str r0, [sp, #0x14]
	add r0, sp, #0xc
	str r1, [sp, #0x10]
	str r1, [sp, #0x18]
	bl MOD18_0224F830
	cmp r0, #0
	bne _0224FD66
	mov r0, #2
	lsl r1, r4, #0x10
	lsl r0, r0, #0xe
	add r1, r1, r0
	str r1, [sp]
	lsl r1, r5, #0x10
	add r1, r1, r0
	lsr r0, r0, #3
	add r2, r6, #0
	add r3, sp, #0
	str r1, [sp, #8]
	str r0, [sp, #4]
	ldmia r3!, {r0, r1}
	add r2, #0x58
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	str r4, [r6, #0x64]
	str r5, [r6, #0x68]
_0224FD66:
	add sp, #0x1c
	pop {r3, r4, r5, r6, pc}
	nop
_0224FD6C: .word gMain + 0x40
	thumb_func_end MOD18_0224FCD8

	thumb_func_start MOD18_0224FD70
MOD18_0224FD70: ; 0x0224FD70
	push {r3, r4, r5, lr}
	add r3, r0, #0
	mov r0, #0
	ldr r4, _0224FDD0 ; =gMain + 0x40
	str r0, [r2]
	ldrh r5, [r4, #0x20]
	cmp r5, #0
	beq _0224FDA0
	ldr r0, _0224FDD4 ; =gMain
	ldr r0, [r0, #0x44]
	cmp r0, #0
	bne _0224FD9C
	ldr r2, _0224FDD8 ; =0x000004F8
	mov r0, #1
	str r0, [r3, r2]
	add r0, r1, #0
	add r1, r3, #0
	sub r2, #8
	add r1, #0x3c
	add r2, r3, r2
	bl MOD18_0224FC18
_0224FD9C:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224FDA0:
	ldrh r4, [r4, #0x22]
	cmp r4, #0
	beq _0224FDC0
	ldr r2, _0224FDD8 ; =0x000004F8
	ldr r0, [r3, r2]
	cmp r0, #0
	beq _0224FDBC
	add r0, r1, #0
	add r1, r3, #0
	sub r2, #8
	add r1, #0x3c
	add r2, r3, r2
	bl MOD18_0224FC18
_0224FDBC:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224FDC0:
	ldr r1, _0224FDD8 ; =0x000004F8
	ldr r4, [r3, r1]
	cmp r4, #0
	beq _0224FDCE
	str r0, [r3, r1]
	mov r1, #1
	str r1, [r2]
_0224FDCE:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224FDD0: .word gMain + 0x40
_0224FDD4: .word gMain
_0224FDD8: .word 0x000004F8
	thumb_func_end MOD18_0224FD70

	thumb_func_start MOD18_0224FDDC
MOD18_0224FDDC: ; 0x0224FDDC
	push {r3, r4, r5, lr}
	add r3, r0, #0
	mov r0, #0
	ldr r4, _0224FE40 ; =gMain + 0x40
	str r0, [r2]
	ldrh r5, [r4, #0x20]
	cmp r5, #0
	beq _0224FE0E
	ldr r0, _0224FE44 ; =gMain
	ldr r0, [r0, #0x44]
	cmp r0, #0
	bne _0224FE0A
	ldr r2, _0224FE48 ; =0x000004F8
	mov r0, #1
	str r0, [r3, r2]
	add r0, r1, #0
	add r1, r2, #0
	add r2, r2, #4
	sub r1, #8
	ldr r2, [r3, r2]
	add r1, r3, r1
	bl MOD18_0224FCD8
_0224FE0A:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224FE0E:
	ldrh r4, [r4, #0x22]
	cmp r4, #0
	beq _0224FE30
	ldr r2, _0224FE48 ; =0x000004F8
	ldr r0, [r3, r2]
	cmp r0, #0
	beq _0224FE2C
	add r0, r1, #0
	add r1, r2, #0
	add r2, r2, #4
	sub r1, #8
	ldr r2, [r3, r2]
	add r1, r3, r1
	bl MOD18_0224FCD8
_0224FE2C:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224FE30:
	ldr r1, _0224FE48 ; =0x000004F8
	ldr r4, [r3, r1]
	cmp r4, #0
	beq _0224FE3E
	str r0, [r3, r1]
	mov r1, #1
	str r1, [r2]
_0224FE3E:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224FE40: .word gMain + 0x40
_0224FE44: .word gMain
_0224FE48: .word 0x000004F8
	thumb_func_end MOD18_0224FDDC

	thumb_func_start MOD18_0224FE4C
MOD18_0224FE4C: ; 0x0224FE4C
	push {r4, lr}
	add r3, r0, #0
	mov r0, #0
	ldr r4, _0224FE88 ; =gMain + 0x40
	str r0, [r2]
	ldrh r4, [r4, #0x20]
	cmp r4, #0
	beq _0224FE80
	ldr r0, _0224FE8C ; =gMain
	ldr r0, [r0, #0x44]
	cmp r0, #0
	bne _0224FE7C
	ldr r4, _0224FE90 ; =0x000004F8
	mov r0, #1
	str r0, [r3, r4]
	str r0, [r2]
	add r0, r1, #0
	add r1, r4, #0
	add r2, r4, #4
	sub r1, #8
	ldr r2, [r3, r2]
	add r1, r3, r1
	bl MOD18_0224FCD8
_0224FE7C:
	mov r0, #1
	pop {r4, pc}
_0224FE80:
	ldr r1, _0224FE90 ; =0x000004F8
	str r0, [r3, r1]
	pop {r4, pc}
	nop
_0224FE88: .word gMain + 0x40
_0224FE8C: .word gMain
_0224FE90: .word 0x000004F8
	thumb_func_end MOD18_0224FE4C

	thumb_func_start MOD18_0224FE94
MOD18_0224FE94: ; 0x0224FE94
	push {r3, r4, r5, lr}
	add r3, r0, #0
	mov r0, #0
	ldr r4, _0224FEF4 ; =gMain + 0x40
	str r0, [r2]
	ldrh r5, [r4, #0x20]
	cmp r5, #0
	beq _0224FEC4
	ldr r0, _0224FEF8 ; =gMain
	ldr r0, [r0, #0x44]
	cmp r0, #0
	bne _0224FEC0
	ldr r2, _0224FEFC ; =0x000004F8
	mov r0, #1
	str r0, [r3, r2]
	add r0, r1, #0
	add r1, r3, #0
	sub r2, #8
	add r1, #0x3c
	add r2, r3, r2
	bl MOD18_0224FC18
_0224FEC0:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224FEC4:
	ldrh r4, [r4, #0x22]
	cmp r4, #0
	beq _0224FEE4
	ldr r2, _0224FEFC ; =0x000004F8
	ldr r0, [r3, r2]
	cmp r0, #0
	beq _0224FEE0
	add r0, r1, #0
	add r1, r3, #0
	sub r2, #8
	add r1, #0x3c
	add r2, r3, r2
	bl MOD18_0224FC18
_0224FEE0:
	mov r0, #1
	pop {r3, r4, r5, pc}
_0224FEE4:
	ldr r1, _0224FEFC ; =0x000004F8
	ldr r4, [r3, r1]
	cmp r4, #0
	beq _0224FEF2
	str r0, [r3, r1]
	mov r1, #1
	str r1, [r2]
_0224FEF2:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0224FEF4: .word gMain + 0x40
_0224FEF8: .word gMain
_0224FEFC: .word 0x000004F8
	thumb_func_end MOD18_0224FE94

	thumb_func_start MOD18_0224FF00
MOD18_0224FF00: ; 0x0224FF00
	mov r2, #0
	str r2, [r0, #4]
	ldr r1, _0224FF10 ; =0x0000FFFF
	str r2, [r0, #8]
	str r1, [r0]
	str r2, [r0, #0xc]
	str r2, [r0, #0x10]
	bx lr
	.align 2, 0
_0224FF10: .word 0x0000FFFF
	thumb_func_end MOD18_0224FF00

	thumb_func_start MOD18_0224FF14
MOD18_0224FF14: ; 0x0224FF14
	mov r3, #0
	str r3, [r2, #4]
	str r1, [r2, #8]
	str r0, [r2]
	str r3, [r2, #0xc]
	mov r0, #1
	str r0, [r2, #0x10]
	bx lr
	thumb_func_end MOD18_0224FF14

	thumb_func_start MOD18_0224FF24
MOD18_0224FF24: ; 0x0224FF24
	push {r4, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x10]
	cmp r1, #0
	beq _0224FF60
	ldr r1, [r4, #4]
	add r2, r1, #1
	str r2, [r4, #4]
	ldr r1, [r4, #8]
	cmp r2, r1
	blt _0224FF60
	mov r1, #0
	str r1, [r4, #4]
	ldr r1, [r4, #0xc]
	add r0, #0xa0
	add r1, r1, #1
	lsr r3, r1, #0x1f
	lsl r2, r1, #0x1f
	sub r2, r2, r3
	mov r1, #0x1f
	ror r2, r1
	add r1, r3, r2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r1, [r4]
	bl MOD05_021E7EEC
	ldr r1, [r4, #0xc]
	bl MOD05_021E7EC0
_0224FF60:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD18_0224FF24

	thumb_func_start MOD18_0224FF64
MOD18_0224FF64: ; 0x0224FF64
	push {r3, lr}
	ldr r2, [r1, #0x10]
	cmp r2, #0
	beq _0224FF7C
	add r0, #0xa0
	ldr r0, [r0]
	ldr r1, [r1]
	bl MOD05_021E7EEC
	mov r1, #0
	bl MOD05_021E7EC0
_0224FF7C:
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD18_0224FF64

	thumb_func_start MOD18_0224FF80
MOD18_0224FF80: ; 0x0224FF80
	ldr r0, [r0]
	bx lr
	thumb_func_end MOD18_0224FF80

	thumb_func_start MOD18_0224FF84
MOD18_0224FF84: ; 0x0224FF84
	ldr r3, _0224FF8C ; =MOD18_0224FB9C
	add r0, r2, #0
	bx r3
	nop
_0224FF8C: .word MOD18_0224FB9C
	thumb_func_end MOD18_0224FF84

	thumb_func_start MOD18_0224FF90
MOD18_0224FF90: ; 0x0224FF90
	bx lr
	.align 2, 0
	thumb_func_end MOD18_0224FF90

	thumb_func_start MOD18_0224FF94
MOD18_0224FF94: ; 0x0224FF94
	ldr r3, _0224FF9C ; =MOD18_0224FBC8
	add r0, r2, #0
	bx r3
	nop
_0224FF9C: .word MOD18_0224FBC8
	thumb_func_end MOD18_0224FF94

	thumb_func_start MOD18_0224FFA0
MOD18_0224FFA0: ; 0x0224FFA0
	push {r3, r4, r5, lr}
	sub sp, #0x30
	ldr r0, [r2, #0x6c]
	cmp r0, #0
	beq _0224FFD6
	ldr r5, _0224FFDC ; =0x02250834
	add r4, sp, #0xc
	mov r3, #4
_0224FFB0:
	ldmia r5!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r3, r3, #1
	bne _0224FFB0
	ldr r0, [r5]
	ldr r5, _0224FFE0 ; =0x022507F0
	str r0, [r4]
	add r4, sp, #0
	ldmia r5!, {r0, r1}
	add r3, r4, #0
	stmia r4!, {r0, r1}
	ldr r0, [r5]
	str r0, [r4]
	add r0, r2, #0
	add r2, #0x58
	add r1, r2, #0
	add r2, sp, #0xc
	bl FUN_0201B26C
_0224FFD6:
	add sp, #0x30
	pop {r3, r4, r5, pc}
	nop
_0224FFDC: .word MOD18_02250834
_0224FFE0: .word MOD18_022507F0
	thumb_func_end MOD18_0224FFA0

	.rodata
	.global MOD18_0224FFE4
MOD18_0224FFE4: ; 0x0224FFE4
	.byte 0x08, 0x05

	.global MOD18_0224FFE6
MOD18_0224FFE6: ; 0x0224FFE6
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03, 0x00, 0x00

	.global MOD18_0224FFF0
MOD18_0224FFF0: ; 0x0224FFF0
	.byte 0x14, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00

	.global MOD18_02250000
MOD18_02250000: ; 0x02250000
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250010
MOD18_02250010: ; 0x02250010
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x18, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_0225002C
MOD18_0225002C: ; 0x0225002C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x1A, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250048
MOD18_02250048: ; 0x02250048
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x1C, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250064
MOD18_02250064: ; 0x02250064
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x1F, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250080
MOD18_02250080: ; 0x02250080
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00

	.global MOD18_022500A8
MOD18_022500A8: ; 0x022500A8
	.byte 0x00, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00
	.byte 0x0B, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x0E, 0x00

	.global MOD18_022500C0
MOD18_022500C0: ; 0x022500C0
	.byte 0x20, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00

	.global MOD18_022500CC
MOD18_022500CC: ; 0x022500CC
	.byte 0xFF, 0x03, 0x07, 0x0B, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x09, 0x07, 0x05, 0x03, 0x01, 0xF6, 0x00

	.global MOD18_022500DC
MOD18_022500DC: ; 0x022500DC
	.byte 0x23, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00
	.byte 0x2F, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00

	.global MOD18_022500F4
MOD18_022500F4: ; 0x022500F4
	.byte 0xBE, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xC2, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00
	.byte 0x42, 0x00, 0x00, 0x00

	.global MOD18_02250118
MOD18_02250118: ; 0x02250118
	.word 0x00000000, MOD18_0223FFE0, MOD18_02240028, MOD18_0223FFF8
	.word MOD18_02240010, MOD18_02240040, MOD18_02240088, MOD18_02240058
	.word MOD18_02240070, 0x00000000, 0x00000000, MOD18_022412E4
	.word MOD18_02241308, MOD18_0223FF50, MOD18_0223FF6C, 0x00000000
	.word 0x00000000, 0x00000000, MOD18_0223FF88, MOD18_0223FF88
	.word MOD18_022431F4, MOD18_022431F4, MOD18_0224259C, MOD18_0224259C
	.word MOD18_022439EC, MOD18_022439EC, MOD18_022439EC, MOD18_022439EC
	.word MOD18_0223FFB4, MOD18_0223FFB4, MOD18_022437E0, MOD18_022437E0
	.word 0x00000000, MOD18_022402F4, 0x00000000

	.global MOD18_022501A4
MOD18_022501A4: ; 0x022501A4
	.word 0x00000000, MOD18_0223FEC4, MOD18_0223FEC4, MOD18_0223FEC4
	.word MOD18_0223FEC4, MOD18_0223FEC4, MOD18_0223FEC4, MOD18_0223FEC4
	.word MOD18_0223FEC4, 0x00000000, 0x00000000, MOD18_0224133C
	.word MOD18_02241350, MOD18_0223FE70, MOD18_0223FE84, 0x00000000
	.word 0x00000000, 0x00000000, MOD18_0223FEAC, MOD18_0223FEAC
	.word MOD18_02243220, MOD18_02243220, MOD18_022425C8, MOD18_022425C8
	.word MOD18_02243A18, MOD18_02243A18, MOD18_02243A18, MOD18_02243A18
	.word MOD18_0223FEB8, MOD18_0223FEB8, MOD18_0224380C, MOD18_0224380C
	.word 0x00000000, MOD18_0223FF4C, 0x00000000

	.global MOD18_02250230
MOD18_02250230: ; 0x02250230
	.word 0x00000000, MOD18_0223FED8, MOD18_0223FEFC, MOD18_0223FEE4
	.word MOD18_0223FEF0, MOD18_0223FF08, MOD18_0223FF2C, MOD18_0223FF14
	.word MOD18_0223FF20, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000

	.global MOD18_022502BC
MOD18_022502BC: ; 0x022502BC
	.word 0x00000000, MOD18_0223FF38, MOD18_0223FF38, MOD18_0223FF38
	.word MOD18_0223FF38, MOD18_0223FF38, MOD18_0223FF38, MOD18_0223FF38
	.word MOD18_0223FF38, 0x00000000, 0x00000000, MOD18_0224132C
	.word MOD18_0224132C, MOD18_0223FE98, MOD18_0223FE98, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000000, 0x00000000

	.global MOD18_02250348
MOD18_02250348: ; 0x02250348
	.word 0x00000000, MOD18_02240270, MOD18_02240270, MOD18_02240270
	.word MOD18_02240270, MOD18_02240270, MOD18_02240270, MOD18_02240270
	.word MOD18_02240270, 0x00000000, 0x00000000, MOD18_02240F34
	.word MOD18_02240F34, MOD18_02240D9C, MOD18_02240D9C, 0x00000000
	.word 0x00000000, 0x00000000, MOD18_02240460, MOD18_02240460
	.word MOD18_0224322C, MOD18_0224322C, MOD18_022425D4, MOD18_022425D4
	.word MOD18_02243A24, MOD18_02243A24, MOD18_02243A24, MOD18_02243A24
	.word MOD18_022416B0, MOD18_022416B0, MOD18_02243818, MOD18_02243818
	.word 0x00000000, 0x00000000, 0x00000000

	.global MOD18_022503D4
MOD18_022503D4: ; 0x022503D4
	.word 0x00000000, MOD18_022402A0, MOD18_022402A0, MOD18_022402A0
	.word MOD18_022402A0, MOD18_022402A0, MOD18_022402A0, MOD18_022402A0
	.word MOD18_022402A0, 0x00000000, 0x00000000, MOD18_02240F84
	.word MOD18_02240F84, MOD18_02240DC8, MOD18_02240DC8, 0x00000000
	.word 0x00000000, 0x00000000, MOD18_02240460, MOD18_02240460
	.word MOD18_0224322C, MOD18_0224322C, MOD18_022425D4, MOD18_022425D4
	.word MOD18_02243A24, MOD18_02243A24, MOD18_02243A24, MOD18_02243A24
	.word MOD18_022416B0, MOD18_022416B0, MOD18_02243818, MOD18_02243818
	.word 0x00000000, 0x00000000, 0x00000000

	.global MOD18_02250460
MOD18_02250460: ; 0x02250460
	.byte 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x0B, 0x0C, 0x0D, 0x0E, 0x12, 0x13, 0x17, 0x1D
	.byte 0x18, 0x19, 0x1A, 0x1B, 0x1E, 0x1F, 0x14, 0x15, 0x16, 0x1C, 0x00, 0x00

	.global MOD18_0225047C
MOD18_0225047C: ; 0x0225047C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250498
MOD18_02250498: ; 0x02250498
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0F, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_022504B4
MOD18_022504B4: ; 0x022504B4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_022504D0
MOD18_022504D0: ; 0x022504D0
	.byte 0x0C, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00
	.byte 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x18, 0x00
	.byte 0x00, 0x00, 0x0F, 0x00, 0x18, 0x00, 0x00, 0x00

	.global MOD18_022504F8
MOD18_022504F8: ; 0x022504F8
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global MOD18_02250500
MOD18_02250500: ; 0x02250500
	.byte 0x03, 0x10, 0x0D, 0x0F, 0x04, 0x0D, 0xEF, 0x02

	.global MOD18_02250508
MOD18_02250508: ; 0x02250508
	.byte 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250511
MOD18_02250511: ; 0x02250511
	.byte 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00

	.global MOD18_02250520
MOD18_02250520: ; 0x02250520
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global MOD18_02250528
MOD18_02250528: ; 0x02250528
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250548
MOD18_02250548: ; 0x02250548
	.word 0x03, MOD18_02247FFC
	.word 0x04, MOD18_02248018
	.word 0x05, MOD18_0224802C
	.word 0x06, MOD18_0224865C
	.word 0x04

	.global MOD18_0225056C
MOD18_0225056C: ; 0x0225056C
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global MOD18_02250574
MOD18_02250574: ; 0x02250574
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD18_02250580
MOD18_02250580: ; 0x02250580
	.byte 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250598
MOD18_02250598: ; 0x02250598
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x14, 0x00, 0x14, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_022505B8
MOD18_022505B8: ; 0x022505B8
	.word 0x00000079, MOD18_02249B50, 0x0000007A, MOD18_02249F2C
	.word 0x0000007B, MOD18_0224AA4C, 0x0000007C, MOD18_0224A30C
	.word 0x0000007D, MOD18_0224A78C, 0x0000007E, MOD18_0224A6B4
	.word 0x0000007F, MOD18_0224A6A8

	.global MOD18_022505F0
MOD18_022505F0: ; 0x022505F0
	.byte 0xCC, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xC0, 0x38, 0x00, 0x00, 0xC0, 0x38, 0x00, 0x00, 0xC0, 0x38, 0x00, 0x00
	.byte 0xC0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250624
MOD18_02250624: ; 0x02250624
	.byte 0xAE, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xC1, 0x38, 0x00, 0x00, 0xC0, 0x38, 0x00, 0x00, 0xC1, 0x38, 0x00, 0x00
	.byte 0xC1, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00

	.global MOD18_0225065C
MOD18_0225065C: ; 0x0225065C
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00

	.global MOD18_0225066C
MOD18_0225066C: ; 0x0225066C
	.byte 0x03, 0x19, 0x0D, 0x06, 0x04, 0x0D, 0x15, 0x03

	.global MOD18_02250674
MOD18_02250674: ; 0x02250674
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02250694
MOD18_02250694: ; 0x02250694
	.byte 0x00

	.global MOD18_02250695
MOD18_02250695: ; 0x02250695
	.byte 0x00

	.global MOD18_02250696
MOD18_02250696: ; 0x02250696
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02
	.byte 0x0F, 0x14, 0x01, 0x32, 0x3C, 0x03, 0x19, 0x23, 0x02, 0x23, 0x2D, 0x02, 0x19, 0x23, 0x03, 0x19
	.byte 0x23, 0x01, 0x19, 0x23, 0x02, 0x19, 0x23, 0x03, 0x19, 0x23, 0x04, 0x19, 0x23, 0x05, 0x19, 0x23
	.byte 0x04, 0x00, 0x00, 0x04, 0x1E, 0x32, 0x05, 0x1E, 0x32, 0x04, 0x1E, 0x32, 0x05, 0x1E, 0x32, 0x01
	.byte 0x1E, 0x32, 0x02, 0x19, 0x23, 0x02, 0x05, 0x0A, 0x02, 0x28, 0x32, 0x03, 0x14, 0x19, 0x04, 0x14
	.byte 0x19, 0x01, 0x14, 0x19, 0x05, 0x14, 0x19, 0x03, 0x05, 0x0A, 0x04, 0x1E, 0x32, 0x05, 0x1E, 0x32
	.byte 0x02, 0x28, 0x32, 0x01, 0x28, 0x32, 0x02, 0x23, 0x28, 0x01, 0x23, 0x28, 0x03, 0x28, 0x32, 0x04
	.byte 0x28, 0x32, 0x03, 0x46, 0x50, 0x04, 0x46, 0x50, 0x01, 0x46, 0x50, 0x05, 0x46, 0x50, 0x04, 0x46
	.byte 0x50, 0x01, 0x46, 0x50, 0x02, 0x46, 0x50, 0x05, 0x46, 0x50, 0x04, 0x46, 0x50, 0x02, 0x46, 0x50
	.byte 0x05, 0x46, 0x50, 0x01, 0x46, 0x50, 0x02, 0x46, 0x50, 0x03, 0x46, 0x50, 0x03, 0x46, 0x50, 0x01
	.byte 0x46, 0x50

	.global MOD18_02250748
MOD18_02250748: ; 0x02250748
	.byte 0x00

	.global MOD18_02250749
MOD18_02250749: ; 0x02250749
	.byte 0x00

	.global MOD18_0225074A
MOD18_0225074A: ; 0x0225074A
	.byte 0x00, 0x04, 0x03, 0x06, 0x03, 0x03, 0x06, 0x04, 0x03, 0x06, 0x03, 0x03, 0x06, 0x04, 0x0C, 0x0F
	.byte 0x03, 0x0C, 0x0F, 0x04, 0x0C, 0x0F, 0x03, 0x0C, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	.byte 0x03, 0x06, 0x01, 0x0C, 0x0F, 0x02, 0x0A, 0x0C, 0x02, 0x0A, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0x07, 0x03, 0x0C, 0x10, 0x04, 0x03, 0x06, 0x04, 0x08, 0x0F
	.byte 0x04, 0x05, 0x07, 0x04, 0x0C, 0x10, 0x02, 0x05, 0x09, 0x02, 0x05, 0x09, 0x02, 0x05, 0x09, 0x02
	.byte 0x05, 0x09, 0x05, 0x0F, 0x13, 0x05, 0x1E, 0x28, 0x03, 0x05, 0x09, 0x03, 0x14, 0x1E, 0x00, 0x00
	.byte 0x00, 0x06, 0x0F, 0x14, 0x00, 0x00

	.global MOD18_022507B0
MOD18_022507B0: ; 0x022507B0
	.byte 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00

	.global MOD18_022507C0
MOD18_022507C0: ; 0x022507C0
	.byte 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00

	.global MOD18_022507D0
MOD18_022507D0: ; 0x022507D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x04, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_022507F0
MOD18_022507F0: ; 0x022507F0
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00

	.global MOD18_022507FC
MOD18_022507FC: ; 0x022507FC
	.byte 0x0F, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00

	.global MOD18_0225080C
MOD18_0225080C: ; 0x0225080C
	.byte 0x0F, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00

	.global MOD18_0225081C
MOD18_0225081C: ; 0x0225081C
	.word 0x00000000, 0x00000070, MOD18_0224FF84, MOD18_0224FF94
	.word MOD18_0224FF90, MOD18_0224FFA0

	.global MOD18_02250834
MOD18_02250834: ; 0x02250834
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.data
	.global MOD18_02250860
MOD18_02250860: ; 0x02250860
	.byte 0x01, 0xFF, 0xFF, 0x01

	.global MOD18_02250864
MOD18_02250864: ; 0x02250864
	.byte 0x04, 0x05, 0x14, 0x15

	.global MOD18_02250868
MOD18_02250868: ; 0x02250868
	.byte 0x06, 0x07, 0x16, 0x17

	.global MOD18_0225086C
MOD18_0225086C: ; 0x0225086C
	.byte 0x0E, 0x0F, 0x1E, 0x1F

	.global MOD18_02250870
MOD18_02250870: ; 0x02250870
	.byte 0x78, 0x6F, 0x78, 0x78

	.global MOD18_02250874
MOD18_02250874: ; 0x02250874
	.byte 0x1A, 0x0F, 0x20, 0x17

	.global MOD18_02250878
MOD18_02250878: ; 0x02250878
	.byte 0x1A, 0x06, 0x20, 0x0E

	.global MOD18_0225087C
MOD18_0225087C: ; 0x0225087C
	.byte 0x78, 0x78, 0x78, 0x6F, 0x78, 0x6F

	.global MOD18_02250882
MOD18_02250882: ; 0x02250882
	.byte 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x78

	.global MOD18_02250888
MOD18_02250888: ; 0x02250888
	.byte 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_0225088E
MOD18_0225088E: ; 0x0225088E
	.byte 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78

	.global MOD18_02250894
MOD18_02250894: ; 0x02250894
	.byte 0x78, 0x6F, 0x78, 0x78
	.byte 0x6F, 0x78

	.global MOD18_0225089A
MOD18_0225089A: ; 0x0225089A
	.byte 0x78, 0x6F, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022508A0
MOD18_022508A0: ; 0x022508A0
	.byte 0x6F, 0x78, 0x6F, 0x78, 0x78, 0x78

	.global MOD18_022508A6
MOD18_022508A6: ; 0x022508A6
	.byte 0x6F, 0x78
	.byte 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022508AC
MOD18_022508AC: ; 0x022508AC
	.byte 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78

	.global MOD18_022508B4
MOD18_022508B4: ; 0x022508B4
	.byte 0x6F, 0x78, 0x78, 0x78
	.byte 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022508BC
MOD18_022508BC: ; 0x022508BC
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022508C5
MOD18_022508C5: ; 0x022508C5
	.byte 0x6F, 0x78, 0x78
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022508CE
MOD18_022508CE: ; 0x022508CE
	.byte 0x6F, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78

	.global MOD18_022508D7
MOD18_022508D7: ; 0x022508D7
	.byte 0x6F
	.byte 0x78, 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x6F

	.global MOD18_022508E0
MOD18_022508E0: ; 0x022508E0
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78
	.byte 0x78

	.global MOD18_022508E9
MOD18_022508E9: ; 0x022508E9
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022508F2
MOD18_022508F2: ; 0x022508F2
	.byte 0x78, 0x6F, 0x78, 0x6F, 0x78, 0x78
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x78

	.global MOD18_022508FE
MOD18_022508FE: ; 0x022508FE
	.byte 0x78, 0x78, 0x78, 0x00, 0x78, 0x78, 0x78, 0x00, 0x78, 0x6F
	.byte 0x78, 0x00

	.global MOD18_0225090A
MOD18_0225090A: ; 0x0225090A
	.byte 0x6F, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x6F

	.global MOD18_02250916
MOD18_02250916: ; 0x02250916
	.byte 0x6F, 0x78
	.byte 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x6F

	.global MOD18_02250922
MOD18_02250922: ; 0x02250922
	.byte 0x78, 0x6F, 0x78, 0x6F, 0x78, 0x78
	.byte 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78

	.global MOD18_0225092E
MOD18_0225092E: ; 0x0225092E
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78
	.byte 0x6F, 0x78

	.global MOD18_0225093A
MOD18_0225093A: ; 0x0225093A
	.byte 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78
	.byte 0x78, 0x78

	.global MOD18_0225094A
MOD18_0225094A: ; 0x0225094A
	.byte 0x6F, 0x6F, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x78
	.byte 0x6F, 0x6F

	.global MOD18_0225095A
MOD18_0225095A: ; 0x0225095A
	.byte 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78
	.byte 0x78, 0x6F

	.global MOD18_0225096A
MOD18_0225096A: ; 0x0225096A
	.byte 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78
	.byte 0x78, 0x78

	.global MOD18_0225097A
MOD18_0225097A: ; 0x0225097A
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78
	.byte 0x78, 0x6F

	.global MOD18_0225098A
MOD18_0225098A: ; 0x0225098A
	.byte 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78
	.byte 0x78, 0x6F

	.global MOD18_0225099A
MOD18_0225099A: ; 0x0225099A
	.byte 0x78, 0x6F, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78
	.byte 0x6F, 0x78

	.global MOD18_022509AA
MOD18_022509AA: ; 0x022509AA
	.byte 0x6F, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F
	.byte 0x6F, 0x78

	.global MOD18_022509BA
MOD18_022509BA: ; 0x022509BA
	.byte 0x78, 0x78, 0x78, 0x6F, 0x78, 0x6F, 0x6F, 0x78, 0x6F, 0x6F, 0x78, 0x6F, 0x6F, 0x78
	.byte 0x6F, 0x78, 0x78, 0x78

	.global MOD18_022509CC
MOD18_022509CC: ; 0x022509CC
	.byte 0x78, 0x6F, 0x6F, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78
	.byte 0x78, 0x6F, 0x6F, 0x6F, 0x6F, 0x78

	.global MOD18_022509DE
MOD18_022509DE: ; 0x022509DE
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_022509F2
MOD18_022509F2: ; 0x022509F2
	.byte 0x6F, 0x6F, 0x78, 0x78, 0x6F, 0x78
	.byte 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x6F, 0x6F

	.global MOD18_02250A06
MOD18_02250A06: ; 0x02250A06
	.byte 0x78, 0x78
	.byte 0x6F, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78
	.byte 0x78, 0x78

	.global MOD18_02250A1A
MOD18_02250A1A: ; 0x02250A1A
	.byte 0x6F, 0x6F, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78
	.byte 0x78, 0x6F, 0x78, 0x78, 0x6F, 0x6F

	.global MOD18_02250A2E
MOD18_02250A2E: ; 0x02250A2E
	.byte 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F
	.byte 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x6F, 0x78, 0x78

	.global MOD18_02250A42
MOD18_02250A42: ; 0x02250A42
	.byte 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x6F
	.byte 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_02250A56
MOD18_02250A56: ; 0x02250A56
	.byte 0x78, 0x78
	.byte 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x6F, 0x6F, 0x6F
	.byte 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x6F

	.global MOD18_02250A6F
MOD18_02250A6F: ; 0x02250A6F
	.byte 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78
	.byte 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x6F

	.global MOD18_02250A88
MOD18_02250A88: ; 0x02250A88
	.byte 0x6F, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x6F, 0x6F, 0x6F, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78
	.byte 0x78, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78, 0x78, 0x78

	.global MOD18_02250AA1
MOD18_02250AA1: ; 0x02250AA1
	.byte 0x6F, 0x78, 0x78, 0x78, 0x6F, 0x78, 0x78
	.byte 0x78, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x78, 0x78, 0x6F, 0x6F, 0x78, 0x78, 0x78
	.byte 0x6F, 0x6F

	.global MOD18_02250ABA
MOD18_02250ABA: ; 0x02250ABA
	.byte 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06
	.byte 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00

	.global MOD18_02250AD4
MOD18_02250AD4: ; 0x02250AD4
	.word MOD18_0225086C, MOD18_022511DC, MOD18_022511E8, MOD18_02250868
	.word MOD18_02250864, MOD18_022511E0, MOD18_022511E4

	.global MOD18_02250AF0
MOD18_02250AF0: ; 0x02250AF0
	.byte 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00
	.byte 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00
	.byte 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00
	.byte 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00

	.global MOD18_02250B30
MOD18_02250B30: ; 0x02250B30
	.byte 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x16, 0x00, 0x1B, 0x00, 0x14, 0x00

	.global MOD18_02250B3C
MOD18_02250B3C: ; 0x02250B3C
	.byte 0x04, 0x04, 0x01, 0x00, 0x39, 0x00, 0x37, 0x00
	.word 0x00000000
	.byte 0x16, 0x00, 0x1E, 0x00, 0x14, 0x00, 0x1B, 0x00

	.byte 0x04, 0x04, 0x02, 0x00, 0x67, 0x00, 0x65, 0x00
	.word 0x00000000
	.byte 0xA6, 0x00, 0xC0, 0x00, 0x7A, 0x00, 0x96, 0x00

	.byte 0x04, 0x04, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00
	.word 0x00000000
	.byte 0xC0, 0x00, 0xA6, 0x00, 0x96, 0x00, 0x7A, 0x00

	.byte 0x04, 0x04, 0x04, 0x00, 0x05, 0x00, 0x03, 0x00
	.word 0x00000000
	.byte 0x96, 0x00, 0x96, 0x00, 0x6A, 0x00, 0x6A, 0x00

	.byte 0x04, 0x04, 0x05, 0x00, 0x3F, 0x00, 0x3D, 0x00
	.word 0x00000000
	.byte 0x0F, 0x00, 0x0D, 0x00, 0x0D, 0x00, 0x0A, 0x00

	.byte 0x06, 0x06, 0x06, 0x00, 0x38, 0x00, 0x37, 0x00
	.word 0x00000000
	.byte 0x0D, 0x00, 0x0F, 0x00, 0x0A, 0x00, 0x0D, 0x00

	.byte 0x06, 0x06, 0x07, 0x00, 0x66, 0x00, 0x65, 0x00
	.word 0x00000000
	.byte 0x53, 0x00, 0x60, 0x00, 0x3D, 0x00, 0x4B, 0x00

	.byte 0x06, 0x06, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00
	.word 0x00000000
	.byte 0x60, 0x00, 0x53, 0x00, 0x4B, 0x00, 0x3D, 0x00

	.byte 0x06, 0x06, 0x09, 0x00, 0x04, 0x00, 0x03, 0x00
	.word 0x00000000
	.byte 0x4B, 0x00, 0x4B, 0x00, 0x35, 0x00, 0x35, 0x00

	.byte 0x06, 0x06, 0x0A, 0x00, 0x3E, 0x00, 0x3D, 0x00
	.word 0x00000000
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.byte 0x06, 0x06, 0x0B, 0x00, 0x3B, 0x00, 0x3C, 0x00
	.word 0x00000000
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00

	.byte 0x08, 0x08, 0x0C, 0x00, 0x2F, 0x00, 0x30, 0x00
	.word MOD18_022508CE
	.byte 0x04, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x03, 0x00

	.byte 0x06, 0x06, 0x0D, 0x00, 0x6A, 0x00, 0x6B, 0x00
	.word MOD18_022508D7
	.byte 0x02, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x0A, 0x00

	.byte 0x06, 0x06, 0x0E, 0x00, 0x68, 0x00, 0x69, 0x00
	.word MOD18_022508B4
	.byte 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x08, 0x00

	.byte 0x08, 0x04, 0x0F, 0x00, 0x42, 0x00, 0x43, 0x00
	.word MOD18_022508AC
	.byte 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x07, 0x00

	.byte 0x04, 0x08, 0x0F, 0x00, 0x44, 0x00, 0x43, 0x00
	.word 0x00000000
	.byte 0x04, 0x00, 0x04, 0x00, 0x14, 0x00, 0x14, 0x00

	.byte 0x04, 0x04, 0x10, 0x00, 0x12, 0x00, 0x13, 0x00
	.word MOD18_022508C5
	.byte 0x04, 0x00, 0x01, 0x00, 0x1E, 0x00, 0x05, 0x00

	.byte 0x06, 0x06, 0x11, 0x00, 0x2D, 0x00, 0x2E, 0x00
	.word 0x00000000
	.byte 0x04, 0x00, 0x04, 0x00, 0x14, 0x00, 0x14, 0x00

	.byte 0x08, 0x04, 0x12, 0x00, 0x32, 0x00, 0x33, 0x00
	.word 0x00000000
	.byte 0x04, 0x00, 0x01, 0x00, 0x1E, 0x00, 0x05, 0x00

	.byte 0x06, 0x06, 0x13, 0x00, 0x18, 0x00, 0x19, 0x00
	.word MOD18_022508BC
	.byte 0x01, 0x00, 0x04, 0x00, 0x05, 0x00, 0x1E, 0x00

	.byte 0x06, 0x06, 0x14, 0x00, 0x40, 0x00, 0x41, 0x00
	.word MOD18_02250916
	.byte 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x0F, 0x00

	.byte 0x06, 0x08, 0x15, 0x00, 0x60, 0x00, 0x61, 0x00
	.word MOD18_0225090A
	.byte 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x0F, 0x00

	.byte 0x08, 0x06, 0x15, 0x00, 0x62, 0x00, 0x61, 0x00
	.word MOD18_0225098A
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x08, 0x08, 0x17, 0x00, 0x29, 0x00, 0x31, 0x00
	.word MOD18_0225093A
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x08, 0x08, 0x17, 0x00, 0x2C, 0x00, 0x31, 0x00
	.word MOD18_0225098A
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x08, 0x08, 0x17, 0x00, 0x2A, 0x00, 0x31, 0x00
	.word MOD18_0225093A
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x08, 0x08, 0x17, 0x00, 0x2B, 0x00, 0x31, 0x00
	.word MOD18_022509DE
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0D, 0x00

	.byte 0x0A, 0x08, 0x18, 0x00, 0x3A, 0x00, 0x31, 0x00
	.word MOD18_022509F2
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x08, 0x0A, 0x19, 0x00, 0x6D, 0x00, 0x31, 0x00
	.word MOD18_02250A06
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x0A, 0x08, 0x19, 0x00, 0x70, 0x00, 0x31, 0x00
	.word MOD18_02250A1A
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x08, 0x0A, 0x19, 0x00, 0x6E, 0x00, 0x31, 0x00
	.word MOD18_02250A2E
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00

	.byte 0x0A, 0x08, 0x19, 0x00, 0x6F, 0x00, 0x31, 0x00
	.word MOD18_02250A56
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00

	.byte 0x0A, 0x0A, 0x1A, 0x00, 0x45, 0x00, 0x31, 0x00
	.word MOD18_02250A6F
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00

	.byte 0x0A, 0x0A, 0x1A, 0x00, 0x48, 0x00, 0x31, 0x00
	.word MOD18_02250A88
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00

	.byte 0x0A, 0x0A, 0x1A, 0x00, 0x46, 0x00, 0x31, 0x00
	.word MOD18_02250AA1
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00

	.byte 0x0A, 0x0A, 0x1A, 0x00, 0x47, 0x00, 0x31, 0x00
	.word MOD18_0225095A
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00

	.byte 0x08, 0x08, 0x1B, 0x00, 0x34, 0x00, 0x35, 0x00
	.word MOD18_0225096A
	.byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00

	.byte 0x08, 0x08, 0x1B, 0x00, 0x36, 0x00, 0x35, 0x00
	.word MOD18_022509BA
	.byte 0x01, 0x00, 0x01, 0x00, 0x05, 0x00, 0x05, 0x00

	.byte 0x06, 0x0C, 0x1C, 0x00, 0x0A, 0x00, 0x0B, 0x00
	.word MOD18_022509CC
	.byte 0x01, 0x00, 0x01, 0x00, 0x05, 0x00, 0x05, 0x00

	.byte 0x0C, 0x06, 0x1C, 0x00, 0x0C, 0x00, 0x0B, 0x00
	.word MOD18_022508D7
	.byte 0x0A, 0x00, 0x0A, 0x00, 0x0A, 0x00, 0x0A, 0x00

	.byte 0x06, 0x06, 0x1D, 0x00, 0x11, 0x00, 0x0F, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00

	.byte 0x06, 0x06, 0x1E, 0x00, 0x10, 0x00, 0x0F, 0x00
	.word MOD18_022508E0
	.byte 0x0A, 0x00, 0x0F, 0x00, 0x0C, 0x00, 0x16, 0x00

	.byte 0x06, 0x06, 0x1F, 0x00, 0x58, 0x00, 0x4F, 0x00
	.word MOD18_022508E9
	.byte 0x0F, 0x00, 0x0A, 0x00, 0x19, 0x00, 0x0F, 0x00

	.byte 0x06, 0x06, 0x20, 0x00, 0x4B, 0x00, 0x5D, 0x00
	.word MOD18_02250922
	.byte 0x0F, 0x00, 0x0A, 0x00, 0x16, 0x00, 0x0C, 0x00

	.byte 0x08, 0x06, 0x21, 0x00, 0x5F, 0x00, 0x5C, 0x00
	.word MOD18_0225092E
	.byte 0x0A, 0x00, 0x0F, 0x00, 0x0C, 0x00, 0x16, 0x00

	.byte 0x08, 0x06, 0x22, 0x00, 0x51, 0x00, 0x59, 0x00
	.word MOD18_02250870
	.byte 0x21, 0x00, 0x21, 0x00, 0x1E, 0x00, 0x1E, 0x00

	.byte 0x04, 0x04, 0x23, 0x00, 0x14, 0x00, 0x15, 0x00
	.word MOD18_02250A42
	.byte 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0C, 0x00

	.byte 0x0A, 0x08, 0x24, 0x00, 0x6C, 0x00, 0x31, 0x00
	.word MOD18_0225097A
	.byte 0x19, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00

	.byte 0x08, 0x08, 0x25, 0x00, 0x73, 0x00, 0x31, 0x00
	.word MOD18_0225099A
	.byte 0x01, 0x00, 0x01, 0x00, 0x05, 0x00, 0x02, 0x00

	.byte 0x08, 0x08, 0x26, 0x00, 0x49, 0x00, 0x4A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x05, 0x00

	.byte 0x06, 0x06, 0x27, 0x00, 0x06, 0x00, 0x07, 0x00
	.word MOD18_022509AA
	.byte 0x02, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x05, 0x00

	.byte 0x08, 0x08, 0x28, 0x00, 0x0D, 0x00, 0x0E, 0x00
	.word MOD18_0225094A
	.byte 0x01, 0x00, 0x02, 0x00, 0x05, 0x00, 0x0B, 0x00

	.byte 0x08, 0x08, 0x29, 0x00, 0x63, 0x00, 0x64, 0x00
	.word MOD18_022508F2
	.byte 0x02, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x05, 0x00

	.byte 0x08, 0x06, 0x2A, 0x00, 0x16, 0x00, 0x17, 0x00
	.word MOD18_022508FE
	.byte 0x01, 0x00, 0x02, 0x00, 0x05, 0x00, 0x0B, 0x00

	.byte 0x06, 0x06, 0x2B, 0x00, 0x71, 0x00, 0x72, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x2C, 0x00, 0x56, 0x00, 0x4F, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x2D, 0x00, 0x56, 0x00, 0x5D, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x2E, 0x00, 0x56, 0x00, 0x5C, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x2F, 0x00, 0x56, 0x00, 0x59, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x30, 0x00, 0x56, 0x00, 0x54, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x31, 0x00, 0x56, 0x00, 0x50, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x32, 0x00, 0x56, 0x00, 0x57, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x33, 0x00, 0x56, 0x00, 0x53, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x34, 0x00, 0x56, 0x00, 0x5B, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x35, 0x00, 0x56, 0x00, 0x5E, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x36, 0x00, 0x56, 0x00, 0x4C, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x37, 0x00, 0x56, 0x00, 0x5A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x38, 0x00, 0x56, 0x00, 0x52, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x39, 0x00, 0x56, 0x00, 0x4E, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x3A, 0x00, 0x56, 0x00, 0x4D, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x06, 0x3B, 0x00, 0x56, 0x00, 0x55, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x02, 0x3C, 0x00, 0x1B, 0x00, 0x1A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x02, 0x08, 0x3C, 0x00, 0x1C, 0x00, 0x1A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x04, 0x04, 0x3D, 0x00, 0x1D, 0x00, 0x1A, 0x00
	.word MOD18_0225087C
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x06, 0x04, 0x3E, 0x00, 0x1E, 0x00, 0x1A, 0x00
	.word MOD18_02250882
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x04, 0x06, 0x3E, 0x00, 0x21, 0x00, 0x1A, 0x00
	.word MOD18_022508A0
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x06, 0x04, 0x3E, 0x00, 0x1F, 0x00, 0x1A, 0x00
	.word MOD18_0225089A
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x04, 0x06, 0x3E, 0x00, 0x20, 0x00, 0x1A, 0x00
	.word MOD18_0225088E
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x06, 0x04, 0x3F, 0x00, 0x22, 0x00, 0x1A, 0x00
	.word MOD18_022508A6
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x04, 0x06, 0x3F, 0x00, 0x23, 0x00, 0x1A, 0x00
	.word MOD18_02250888
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x06, 0x04, 0x40, 0x00, 0x24, 0x00, 0x1A, 0x00
	.word MOD18_02250894
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x04, 0x06, 0x40, 0x00, 0x25, 0x00, 0x1A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x06, 0x06, 0x41, 0x00, 0x26, 0x00, 0x1A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x04, 0x08, 0x42, 0x00, 0x27, 0x00, 0x1A, 0x00
	.word 0x00000000
	.byte 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00

	.byte 0x08, 0x04, 0x42, 0x00, 0x28, 0x00, 0x1A, 0x00

	.global MOD18_022511D4
MOD18_022511D4: ; 0x022511D4
	.byte 0x01, 0xFF, 0x01, 0xFF

	.global MOD18_022511D8
MOD18_022511D8: ; 0x022511D8
	.byte 0x00, 0x00, 0xFF, 0x01

	.global MOD18_022511DC
MOD18_022511DC: ; 0x022511DC
	.byte 0x0A, 0x0B, 0x1A, 0x1B

	.global MOD18_022511E0
MOD18_022511E0: ; 0x022511E0
	.byte 0x02, 0x03, 0x12, 0x13

	.global MOD18_022511E4
MOD18_022511E4: ; 0x022511E4
	.byte 0x00, 0x01, 0x10, 0x11

	.global MOD18_022511E8
MOD18_022511E8: ; 0x022511E8
	.byte 0x08, 0x09, 0x18, 0x19

	.global MOD18_022511EC
MOD18_022511EC: ; 0x022511EC
	.byte 0x01, 0xFF, 0x00, 0x00

	.global MOD18_022511F0
MOD18_022511F0: ; 0x022511F0
	.byte 0x20, 0xFE, 0x40, 0xFE, 0x20, 0xFE, 0x00, 0xFE, 0x20, 0xFE, 0x40, 0xFE, 0x20, 0xFE, 0x00, 0xFF

	.global MOD18_02251200
MOD18_02251200: ; 0x02251200
	.byte 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

	.global MOD18_0225121C
MOD18_0225121C: ; 0x0225121C
	.byte 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD18_02251238
MOD18_02251238: ; 0x02251238
	.byte 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD18_0225124C
MOD18_0225124C: ; 0x0225124C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD18_02251260
MOD18_02251260: ; 0x02251260
	.byte 0x84, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD18_02251270
MOD18_02251270: ; 0x02251270
	.byte 0x86, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x85, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD18_02251288
MOD18_02251288: ; 0x02251288
	.byte 0x87, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x85, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF

	.global MOD18_022512A0
MOD18_022512A0: ; 0x022512A0
	.byte 0x00, 0x00, 0x48, 0x00, 0x68, 0x00, 0x00, 0x00, 0xA8, 0x01, 0x57, 0x00, 0x00, 0x00, 0xC8, 0x00
	.byte 0xB9, 0x00, 0x00, 0x00, 0x4F, 0x01, 0x08, 0x01, 0x00, 0x00, 0xAF, 0x00, 0x17, 0x01, 0x00, 0x00
	.byte 0xA8, 0x01, 0xB7, 0x01, 0x00, 0x00, 0x57, 0x00, 0xC8, 0x01, 0x00, 0x00, 0x37, 0x01, 0x66, 0x01
	.byte 0x01, 0x00, 0xE8, 0x00, 0x57, 0x00, 0x01, 0x00, 0x48, 0x01, 0x97, 0x00, 0x01, 0x00, 0xE8, 0x00
	.byte 0xD7, 0x00, 0x01, 0x00, 0xE8, 0x00, 0x2A, 0x01, 0x01, 0x00, 0x17, 0x01, 0x48, 0x01, 0x01, 0x00
	.byte 0x17, 0x01, 0xC8, 0x01, 0x01, 0x00, 0xB7, 0x00, 0x88, 0x01, 0x01, 0x00, 0x17, 0x01, 0xF5, 0x00
	.byte 0x02, 0x00, 0x28, 0x00, 0xD7, 0x01, 0x02, 0x00, 0xD7, 0x01, 0x48, 0x00, 0x02, 0x00, 0xD7, 0x01
	.byte 0xD7, 0x01, 0x02, 0x00, 0x28, 0x00, 0x48, 0x00

	.global MOD18_02251318
MOD18_02251318: ; 0x02251318
	.word FUN_020268CC, FUN_02026900, FUN_02026938, FUN_020269CC
	.word FUN_02026A04, FUN_02026A50, FUN_02026AE0, FUN_02026B18
	.word FUN_02026B50, FUN_02026B88, FUN_02026BC0, FUN_02026BF8
	.word FUN_02026C30, FUN_020269CC

	.global MOD18_02251350
MOD18_02251350: ; 0x02251350
	.asciz "data/ug_base_cur.nsbmd"
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.bss
	.global MOD18_02251380
MOD18_02251380: ; 0x02251380
	.space 0x4

	.global MOD18_02251384
MOD18_02251384: ; 0x02251384
	.space 0x4

	.global MOD18_02251388
MOD18_02251388: ; 0x02251388
	.space 0x18

	.global MOD18_022513A0
MOD18_022513A0: ; 0x022513A0
	.space 0x8

	.global MOD18_022513A8
MOD18_022513A8: ; 0x022513A8
	.space 0x4

	.global MOD18_022513AC
MOD18_022513AC: ; 0x022513AC
	.space 0x40

	.global MOD18_022513EC
MOD18_022513EC: ; 0x022513EC
	.space 0x4

	.global MOD18_022513F0
MOD18_022513F0: ; 0x022513F0
	.space 0x8

	.global MOD18_022513F8
MOD18_022513F8: ; 0x022513F8
	.space 0x4

	.global MOD18_022513FC
MOD18_022513FC: ; 0x022513FC
	.space 0x4

