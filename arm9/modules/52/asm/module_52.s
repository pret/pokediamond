	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD52_021D74E0
MOD52_021D74E0: ; 0x021D74E0
	push {r3, lr}
	mov r2, #2
	mov r0, #3
	mov r1, #0x4d
	lsl r2, r2, #0x10
	bl FUN_0201681C
	bl FUN_02000FA4
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD52_021D74E0

	thumb_func_start MOD52_021D74F8
MOD52_021D74F8: ; 0x021D74F8
	push {r3, lr}
	bl FUN_0200628C
	ldr r1, [r0, #8]
	mov r0, #0x4d
	bl MOD52_021D769C
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD52_021D74F8

	thumb_func_start MOD52_021D750C
MOD52_021D750C: ; 0x021D750C
	push {r3, lr}
	mov r0, #0x4d
	bl FUN_020168D0
	mov r0, #0
	ldr r1, _021D7524 ; =0x020FD144
	mvn r0, r0
	bl FUN_02000E7C
	mov r0, #1
	pop {r3, pc}
	nop
_021D7524: .word 0x020FD144
	thumb_func_end MOD52_021D750C

	thumb_func_start MOD52_021D7528
MOD52_021D7528: ; 0x021D7528
	push {r3, lr}
	mov r2, #2
	mov r0, #3
	mov r1, #0x4d
	lsl r2, r2, #0x10
	bl FUN_0201681C
	bl FUN_02000FA4
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD52_021D7528

	thumb_func_start MOD52_021D7540
MOD52_021D7540: ; 0x021D7540
	push {r4, lr}
	bl FUN_0200628C
	ldr r4, [r0, #8]
	mov r0, #0x4d
	add r1, r4, #0
	mov r2, #1
	bl MOD52_021D7604
	add r0, r4, #0
	bl FUN_02023918
	bl FUN_02015E3C
	mov r0, #1
	pop {r4, pc}
	thumb_func_end MOD52_021D7540

	thumb_func_start MOD52_021D7560
MOD52_021D7560: ; 0x021D7560
	push {r3, lr}
	mov r0, #0x4d
	bl FUN_020168D0
	mov r0, #0
	ldr r1, _021D7578 ; =0x020F2B7C
	mvn r0, r0
	bl FUN_02000E7C
	mov r0, #1
	pop {r3, pc}
	nop
_021D7578: .word 0x020F2B7C
	thumb_func_end MOD52_021D7560

	thumb_func_start MOD52_021D757C
MOD52_021D757C: ; 0x021D757C
	push {r3, lr}
	mov r2, #2
	mov r0, #3
	mov r1, #0x4d
	lsl r2, r2, #0x10
	bl FUN_0201681C
	bl FUN_02000FA4
	mov r0, #1
	pop {r3, pc}
	.align 2, 0
	thumb_func_end MOD52_021D757C

	thumb_func_start MOD52_021D7594
MOD52_021D7594: ; 0x021D7594
	push {r3, r4, r5, lr}
	bl FUN_0200628C
	ldr r4, [r0, #8]
	add r0, r4, #0
	bl FUN_02023788
	add r5, r0, #0
	mov r0, #0x4d
	add r1, r4, #0
	bl MOD52_021D7688
	add r0, r4, #0
	mov r1, #0
	bl FUN_02024F9C
	add r0, r5, #0
	bl FUN_020237CC
	cmp r0, #0
	beq _021D75C8
	add r0, r5, #0
	bl FUN_020237FC
	cmp r0, #0
	bne _021D75D8
_021D75C8:
	add r0, r4, #0
	bl FUN_02023794
	bl FUN_020238A4
	add r0, r5, #0
	bl FUN_020237A0
_021D75D8:
	add r0, r4, #0
	bl FUN_02023918
	bl FUN_02015E3C
	mov r0, #1
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD52_021D7594

	thumb_func_start MOD52_021D75E8
MOD52_021D75E8: ; 0x021D75E8
	push {r3, lr}
	mov r0, #0x4d
	bl FUN_020168D0
	mov r0, #0
	ldr r1, _021D7600 ; =0x020F2B8C
	mvn r0, r0
	bl FUN_02000E7C
	mov r0, #1
	pop {r3, pc}
	nop
_021D7600: .word 0x020F2B8C
	thumb_func_end MOD52_021D75E8

	thumb_func_start MOD52_021D7604
MOD52_021D7604: ; 0x021D7604
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	add r6, r2, #0
	bl FUN_02023788
	bl FUN_020237A0
	add r0, r5, #0
	bl FUN_02023794
	bl FUN_02023840
	add r0, r5, #0
	bl FUN_0202881C
	add r4, r0, #0
	bl FUN_0201BA60
	add r2, r0, #0
	add r0, r4, #0
	mov r1, #1
	bl FUN_02028788
	add r0, r5, #0
	bl FUN_0206007C
	add r0, r5, #0
	bl FUN_020238F4
	add r4, r0, #0
	bl FUN_0201BA60
	add r7, r0, #0
	cmp r6, #0
	beq _021D7656
	add r0, r4, #0
	add r1, r7, #0
	bl FUN_020239B8
_021D7656:
	add r0, r4, #0
	bl FUN_020239CC
	add r1, r0, #0
	add r0, r7, #0
	mov r2, #0
	bl FUN_02053678
	add r1, r0, #0
	lsl r1, r1, #0x18
	add r0, r4, #0
	lsr r1, r1, #0x18
	bl FUN_02023A2C
	add r0, r5, #0
	bl FUN_02024ECC
	ldr r1, [sp]
	ldr r2, _021D7684 ; =0x021D76F8
	mov r3, #0x76
	bl FUN_020250C4
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_021D7684: .word 0x021D76F8
	thumb_func_end MOD52_021D7604

	thumb_func_start MOD52_021D7688
MOD52_021D7688: ; 0x021D7688
	push {r3, lr}
	add r0, r1, #0
	bl FUN_020226FC
	cmp r0, #0
	bne _021D769A
	mov r0, #0
	bl OS_ResetSystem
_021D769A:
	pop {r3, pc}
	thumb_func_end MOD52_021D7688

	thumb_func_start MOD52_021D769C
MOD52_021D769C: ; 0x021D769C
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl FUN_020227DC
	add r0, r4, #0
	bl FUN_020377E0
	add r0, r4, #0
	bl FUN_020238F4
	ldr r1, _021D76C4 ; =0x00000BB8
	bl FUN_02023A14
	add r0, r4, #0
	bl FUN_020462AC
	bl FUN_0205ECD4
	pop {r4, pc}
	.align 2, 0
_021D76C4: .word 0x00000BB8
	thumb_func_end MOD52_021D769C

	.section .rodata
	; 0x021D76C8
	.incbin "baserom.nds", 0x299BE8, 0x208
