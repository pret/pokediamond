    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FF2FC
	.extern UNK_020FDDF0
	.extern UNK_020FE17C

	.text

	thumb_func_start FUN_02088F0C
FUN_02088F0C: ; 0x02088F0C
	push {r4-r6, lr}
	add r5, r1, #0x0
	ldr r1, _02088F44 ; =0x0000195C
	add r6, r0, #0x0
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r6, #0x0
	str r5, [r4, #0x0]
	bl FUN_020139D8
	str r0, [r4, #0x4]
	mov r3, #0x0
	ldr r0, _02088F48 ; =0x0000189E
	add r2, r3, #0x0
_02088F2A:
	add r1, r4, r3
	add r3, r3, #0x1
	strb r2, [r1, r0]
	cmp r3, #0xbb
	blt _02088F2A
	add r0, r4, #0x0
	bl FUN_02088F60
	add r0, r4, #0x0
	bl FUN_020891D0
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
_02088F44: .word 0x0000195C
_02088F48: .word 0x0000189E

	thumb_func_start FUN_02088F4C
FUN_02088F4C: ; 0x02088F4C
	push {r4, lr}
	add r4, r0, #0x0
	beq _02088F5E
	ldr r0, [r4, #0x4]
	bl FUN_02013A10
	add r0, r4, #0x0
	bl FUN_02016A18
_02088F5E:
	pop {r4, pc}

	thumb_func_start FUN_02088F60
FUN_02088F60: ; 0x02088F60
	push {r4-r7, lr}
	sub sp, #0xc
	mov r4, #0x0
	str r0, [sp, #0x0]
	add r7, r0, #0x0
	str r0, [sp, #0x8]
	add r0, #0x68
	ldr r5, _02088F9C ; =UNK_020FE17C
	str r4, [sp, #0x4]
	str r0, [sp, #0x8]
_02088F74:
	ldr r3, [sp, #0x8]
	str r4, [r7, #0x38]
	lsl r6, r4, #0x1
	add r3, r3, r6
	ldr r0, [sp, #0x0]
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	ldr r6, [r5, #0x0]
	blx r6
	str r0, [r7, #0x8]
	add r4, r4, r0
	ldr r0, [sp, #0x4]
	add r7, r7, #0x4
	add r0, r0, #0x1
	add r5, #0xc
	str r0, [sp, #0x4]
	cmp r0, #0xc
	blt _02088F74
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02088F9C: .word UNK_020FE17C

	thumb_func_start FUN_02088FA0
FUN_02088FA0: ; 0x02088FA0
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	str r2, [sp, #0x4]
	add r5, r1, #0x0
	add r4, r3, #0x0
	mov r6, #0x0
	bl FUN_02085418
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x4]
	add r7, r6, #0x0
	cmp r0, #0x0
	bls _02088FF6
_02088FBE:
	ldrh r1, [r5, #0x0]
	ldr r0, [sp, #0x8]
	bl FUN_020245F0
	cmp r0, #0x0
	beq _02088FEC
	ldrh r3, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r2, #0x7
	lsr r1, r3, #0x3
	add r1, r0, r1
	ldr r0, _02088FFC ; =0x0000189E
	and r3, r2
	mov r2, #0x1
	ldrb r0, [r1, r0]
	lsl r2, r3
	orr r2, r0
	ldr r0, _02088FFC ; =0x0000189E
	add r6, r6, #0x1
	strb r2, [r1, r0]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
_02088FEC:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r5, r5, #0x2
	cmp r7, r0
	blo _02088FBE
_02088FF6:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02088FFC: .word 0x0000189E

	thumb_func_start FUN_02089000
FUN_02089000: ; 0x02089000
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02085420
	cmp r0, #0x0
	beq _02089046
	mov r2, #0x0
	cmp r7, #0x0
	bls _02089042
_0208901A:
	ldrh r6, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r3, #0x7
	lsr r1, r6, #0x3
	add r1, r0, r1
	ldr r0, _0208904C ; =0x0000189E
	and r6, r3
	mov r3, #0x1
	ldrb r0, [r1, r0]
	lsl r3, r6
	orr r3, r0
	ldr r0, _0208904C ; =0x0000189E
	add r2, r2, #0x1
	strb r3, [r1, r0]
	ldrh r0, [r5, #0x0]
	add r5, r5, #0x2
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
	cmp r2, r7
	blo _0208901A
_02089042:
	add r0, r7, #0x0
	pop {r3-r7, pc}
_02089046:
	mov r0, #0x0
	pop {r3-r7, pc}
	nop
_0208904C: .word 0x0000189E

	thumb_func_start FUN_02089050
FUN_02089050: ; 0x02089050
	push {r3-r7, lr}
	sub sp, #0x10
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	add r4, r3, #0x0
	bl FUN_0208541C
	str r0, [sp, #0xc]
	ldr r0, _020890BC ; =0x00000189
	mov r1, #0x0
	bl FUN_02013A9C
	str r0, [sp, #0x8]
	mov r7, #0x0
	ldr r0, [sp, #0x4]
	add r6, r7, #0x0
	cmp r0, #0x0
	bls _020890B4
_02089078:
	ldrh r2, [r5, #0x0]
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	sub r1, r2, r1
	bl FUN_02013B68
	cmp r0, #0x0
	beq _020890AA
	ldrh r3, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r2, #0x7
	lsr r1, r3, #0x3
	add r1, r0, r1
	ldr r0, _020890C0 ; =0x0000189E
	and r3, r2
	mov r2, #0x1
	ldrb r0, [r1, r0]
	lsl r2, r3
	orr r2, r0
	ldr r0, _020890C0 ; =0x0000189E
	add r6, r6, #0x1
	strb r2, [r1, r0]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
_020890AA:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	add r5, r5, #0x2
	cmp r7, r0
	blo _02089078
_020890B4:
	add r0, r6, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	nop
_020890BC: .word 0x00000189
_020890C0: .word 0x0000189E

	thumb_func_start FUN_020890C4
FUN_020890C4: ; 0x020890C4
	push {r4-r7, lr}
	sub sp, #0x14
	str r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	add r5, r1, #0x0
	str r2, [sp, #0x4]
	add r4, r3, #0x0
	bl FUN_0208541C
	str r0, [sp, #0x10]
	ldr r0, _02089144 ; =0x00000186
	mov r1, #0x0
	bl FUN_02013A9C
	add r6, r0, #0x0
	add r0, r6, #0x5
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #0xc]
	mov r7, #0x0
	ldr r0, [sp, #0x4]
	str r7, [sp, #0x8]
	cmp r0, #0x0
	bls _0208913C
_020890F4:
	ldrh r1, [r5, #0x0]
	cmp r1, r6
	blo _0208910C
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bhi _0208910C
	ldr r0, [sp, #0x10]
	sub r1, r1, r6
	bl FUN_02013C0C
	cmp r0, #0x0
	beq _0208912E
_0208910C:
	ldrh r3, [r5, #0x0]
	ldr r0, [sp, #0x0]
	mov r2, #0x7
	lsr r1, r3, #0x3
	add r1, r0, r1
	ldr r0, _02089148 ; =0x0000189E
	and r3, r2
	mov r2, #0x1
	ldrb r0, [r1, r0]
	lsl r2, r3
	orr r2, r0
	ldr r0, _02089148 ; =0x0000189E
	add r7, r7, #0x1
	strb r2, [r1, r0]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x0]
	add r4, r4, #0x2
_0208912E:
	ldr r0, [sp, #0x8]
	add r5, r5, #0x2
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x8]
	cmp r1, r0
	blo _020890F4
_0208913C:
	add r0, r7, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02089144: .word 0x00000186
_02089148: .word 0x0000189E

	thumb_func_start FUN_0208914C
FUN_0208914C: ; 0x0208914C
	push {r3-r7, lr}
	add r6, r0, #0x0
	mov r0, #0x0
	mov lr, r2
	mov r12, r0
	mov r0, lr
	add r4, r1, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	bls _020891C2
_02089160:
	ldrh r2, [r4, #0x0]
	ldr r0, _020891C8 ; =0x0000FFFE
	cmp r2, r0
	bne _02089196
	add r0, r4, #0x2
	add r4, r4, #0x4
	ldrh r2, [r0, #0x0]
	ldrh r0, [r4, #0x0]
	cmp r2, #0x0
	strh r0, [r7, #0x0]
	beq _020891B6
_02089176:
	ldrh r5, [r4, #0x0]
	mov r3, #0x7
	add r4, r4, #0x2
	lsr r0, r5, #0x3
	add r1, r6, r0
	ldr r0, _020891CC ; =0x0000189E
	and r5, r3
	mov r3, #0x1
	ldrb r0, [r1, r0]
	lsl r3, r5
	orr r3, r0
	ldr r0, _020891CC ; =0x0000189E
	sub r2, r2, #0x1
	strb r3, [r1, r0]
	bne _02089176
	b _020891B6
_02089196:
	lsr r0, r2, #0x3
	ldr r1, _020891CC ; =0x0000189E
	add r0, r6, r0
	ldrb r3, [r0, r1]
	mov r1, #0x7
	mov r5, #0x1
	and r1, r2
	add r2, r5, #0x0
	lsl r2, r1
	ldr r1, _020891CC ; =0x0000189E
	orr r2, r3
	strb r2, [r0, r1]
	ldrh r0, [r4, #0x0]
	add r4, r4, #0x2
	strh r0, [r7, #0x0]
	add r7, r7, #0x2
_020891B6:
	mov r0, r12
	add r1, r0, #0x1
	mov r0, lr
	mov r12, r1
	cmp r1, r0
	blo _02089160
_020891C2:
	mov r0, lr
	pop {r3-r7, pc}
	nop
_020891C8: .word 0x0000FFFE
_020891CC: .word 0x0000189E

	thumb_func_start FUN_020891D0
FUN_020891D0: ; 0x020891D0
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r4, #0x0
	ldr r6, _0208920C ; =UNK_020FDDF0
	str r4, [sp, #0x0]
	add r5, r7, #0x0
_020891DC:
	ldr r0, _02089210 ; =0x00000C84
	mov r2, #0xcf
	str r4, [r5, r0]
	lsl r2, r2, #0x4
	ldr r1, [r6, #0x0]
	add r0, r7, #0x0
	add r2, r7, r2
	add r3, r4, #0x0
	bl FUN_02089218
	ldr r1, _02089214 ; =0x00000C18
	add r6, r6, #0x4
	str r0, [r5, r1]
	add r0, r1, #0x0
	ldr r0, [r5, r0]
	add r5, r5, #0x4
	add r4, r4, r0
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, #0x1b
	blo _020891DC
	pop {r3-r7, pc}
	nop
_0208920C: .word UNK_020FDDF0
_02089210: .word 0x00000C84
_02089214: .word 0x00000C18

	thumb_func_start FUN_02089218
FUN_02089218: ; 0x02089218
	push {r3-r7, lr}
	add r7, r1, #0x0
	add r6, r0, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x0
	mov r12, r0
	ldrh r2, [r7, #0x0]
	ldr r0, _020892B8 ; =0x0000FFFF
	mov lr, r3
	cmp r2, r0
	beq _020892B4
_0208922E:
	ldr r0, _020892BC ; =0x0000FFFE
	cmp r2, r0
	bne _02089280
	add r0, r7, #0x2
	ldrh r5, [r0, #0x0]
	add r7, r7, #0x4
	mov r3, #0x0
	cmp r5, #0x0
	bls _0208927A
	add r4, r7, #0x0
_02089242:
	ldrh r2, [r4, #0x0]
	mov r0, #0x7
	mov r1, #0x1
	and r0, r2
	lsl r1, r0
	lsr r0, r2, #0x3
	add r2, r6, r0
	ldr r0, _020892C0 ; =0x0000189E
	ldrb r0, [r2, r0]
	tst r0, r1
	beq _02089272
	lsl r0, r3, #0x1
	ldrh r1, [r7, r0]
	mov r0, lr
	lsl r2, r0, #0x1
	mov r0, lr
	add r0, r0, #0x1
	mov lr, r0
	ldr r0, [sp, #0x0]
	strh r1, [r0, r2]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	b _0208927A
_02089272:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, r5
	blo _02089242
_0208927A:
	lsl r0, r5, #0x1
	add r7, r7, r0
	b _020892AC
_02089280:
	mov r1, #0x1
	mov r0, #0x7
	and r0, r2
	add r3, r1, #0x0
	lsl r3, r0
	lsr r0, r2, #0x3
	add r1, r6, r0
	ldr r0, _020892C0 ; =0x0000189E
	ldrb r0, [r1, r0]
	tst r0, r3
	beq _020892AA
	mov r1, lr
	add r1, r1, #0x1
	mov r0, lr
	mov lr, r1
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x1
	strh r2, [r1, r0]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
_020892AA:
	add r7, r7, #0x2
_020892AC:
	ldrh r2, [r7, #0x0]
	ldr r0, _020892B8 ; =0x0000FFFF
	cmp r2, r0
	bne _0208922E
_020892B4:
	mov r0, r12
	pop {r3-r7, pc}
	.balign 4
_020892B8: .word 0x0000FFFF
_020892BC: .word 0x0000FFFE
_020892C0: .word 0x0000189E

	thumb_func_start FUN_020892C4
FUN_020892C4: ; 0x020892C4
	lsl r1, r1, #0x2
	add r0, r0, r1
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_020892CC
FUN_020892CC: ; 0x020892CC
	push {r4, lr}
	add r4, r0, #0x0
	lsl r1, r1, #0x2
	add r1, r4, r1
	ldr r1, [r1, #0x38]
	ldr r0, [r4, #0x4]
	add r1, r1, r2
	lsl r1, r1, #0x1
	add r1, r4, r1
	add r1, #0x68
	ldrh r1, [r1, #0x0]
	add r2, r3, #0x0
	bl FUN_02013A30
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020892EC
FUN_020892EC: ; 0x020892EC
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r1, [r1, #0x38]
	add r1, r1, r2
	lsl r1, r1, #0x1
	add r0, r0, r1
	add r0, #0x68
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02089300
FUN_02089300: ; 0x02089300
	lsl r1, r1, #0x2
	add r1, r0, r1
	ldr r0, _0208930C ; =0x00000C18
	ldr r0, [r1, r0]
	bx lr
	nop
_0208930C: .word 0x00000C18

	thumb_func_start FUN_02089310
FUN_02089310: ; 0x02089310
	push {r4-r6, lr}
	add r4, r3, #0x0
	add r5, r0, #0x0
	lsl r3, r1, #0x2
	add r6, r5, r3
	ldr r3, _02089334 ; =0x00000C18
	ldr r3, [r6, r3]
	cmp r3, #0x0
	beq _02089330
	bl FUN_02089338
	add r1, r0, #0x0
	ldr r0, [r5, #0x4]
	add r2, r4, #0x0
	bl FUN_02013A30
_02089330:
	pop {r4-r6, pc}
	nop
_02089334: .word 0x00000C18

	thumb_func_start FUN_02089338
FUN_02089338: ; 0x02089338
	push {r3-r4}
	lsl r1, r1, #0x2
	ldr r3, _02089360 ; =0x00000C18
	add r4, r0, r1
	ldr r1, [r4, r3]
	cmp r1, #0x0
	beq _0208935A
	add r1, r3, #0x0
	add r1, #0x6c
	ldr r1, [r4, r1]
	add r3, #0xd8
	add r1, r2, r1
	lsl r1, r1, #0x1
	add r0, r0, r1
	ldrh r0, [r0, r3]
	pop {r3-r4}
	bx lr
_0208935A:
	ldr r0, _02089364 ; =0x0000FFFF
	pop {r3-r4}
	bx lr
	.balign 4
_02089360: .word 0x00000C18
_02089364: .word 0x0000FFFF

	thumb_func_start FUN_02089368
FUN_02089368: ; 0x02089368
	push {r3-r6}
	mov r1, #0x0
	ldr r2, _0208938C ; =UNK_020FF2FC
	ldr r5, _02089390 ; =UNK_020FE17C
	add r0, r1, #0x0
	mov r3, #0xc
_02089374:
	ldrb r4, [r2, #0x0]
	add r1, r1, #0x1
	add r2, r2, #0x1
	add r6, r4, #0x0
	mul r6, r3
	add r4, r5, r6
	ldr r4, [r4, #0x8]
	add r0, r0, r4
	cmp r1, #0x5
	blo _02089374
	pop {r3-r6}
	bx lr
	.balign 4
_0208938C: .word UNK_020FF2FC
_02089390: .word UNK_020FE17C

	thumb_func_start FUN_02089394
FUN_02089394: ; 0x02089394
	push {r4-r7}
	mov r2, #0x0
	ldr r3, _020893D8 ; =UNK_020FF2FC
	add r1, r2, #0x0
_0208939C:
	ldrb r5, [r3, #0x0]
	mov r4, #0xc
	add r6, r5, #0x0
	mul r6, r4
	ldr r4, _020893DC ; =UNK_020FE17C
	add r5, r4, r6
	ldr r7, [r5, #0x8]
	mov r6, #0x0
	ldr r4, [r5, #0x4]
	cmp r7, #0x0
	ble _020893C8
_020893B2:
	ldrh r5, [r4, #0x0]
	cmp r0, r5
	bne _020893BE
	add r0, r2, #0x0
	pop {r4-r7}
	bx lr
_020893BE:
	add r6, r6, #0x1
	add r2, r2, #0x1
	add r4, r4, #0x2
	cmp r6, r7
	blt _020893B2
_020893C8:
	add r1, r1, #0x1
	add r3, r3, #0x1
	cmp r1, #0x5
	blo _0208939C
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4
_020893D8: .word UNK_020FF2FC
_020893DC: .word UNK_020FE17C
