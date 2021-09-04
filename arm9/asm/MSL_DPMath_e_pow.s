	.include "asm/macros.inc"
	.include "global.inc"

	.rodata

	.global UNK_02104744
UNK_02104744: ; 0x02104744
	.word 0x00000000, 0x00000000
	.word 0x40000000, 0x3FE2B803
	.size UNK_02104744,.-UNK_02104744

	.global UNK_02104754
UNK_02104754: ; 0x02104754
	.word 0x00000000, 0x3FF00000
	.word 0x00000000, 0x3FF80000
	.size UNK_02104754,.-UNK_02104754

	.global UNK_02104764
UNK_02104764: ; 0x02104764
	.word 0x00000000, 0x00000000
	.word 0x43CFD006, 0x3E4CFDEB
	.size UNK_02104764,.-UNK_02104764

	.text

	arm_func_start __ieee754_pow
__ieee754_pow: ; 0x020E708C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x80
	ldr r8, [sp, #0xb4]
	ldr r6, [sp, #0xac]
	ldr r0, [sp, #0xb0]
	bic r9, r8, #0x80000000
	orrs r1, r9, r0
	ldr r7, [sp, #0xa8]
	bic r4, r6, #0x80000000
	addeq sp, sp, #0x80
	moveq r0, #0x0
	ldreq r1, _020E7638 ; =0x3FF00000
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r1, _020E763C ; =0x7FF00000
	cmp r4, r1
	bgt _020E70FC
	bne _020E70E4
	cmp r7, #0x0
	bne _020E70FC
_020E70E4:
	ldr r1, _020E763C ; =0x7FF00000
	cmp r9, r1
	bgt _020E70FC
	bne _020E7120
	cmp r0, #0x0
	beq _020E7120
_020E70FC:
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	ldr r2, [sp, #0xb0]
	ldr r3, [sp, #0xb4]
	bl _dadd
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7120:
	cmp r6, #0x0
	mov r5, #0x0
	bge _020E7188
	ldr r1, _020E7640 ; =0x43400000
	cmp r9, r1
	movge r5, #0x2
	bge _020E7188
	sub r1, r1, #0x3500000
	cmp r9, r1
	blt _020E7188
	ldr r1, _020E7644 ; =0xFFFFFC01
	add r1, r1, r9, asr #0x14
	cmp r1, #0x14
	ble _020E7170
	rsb r2, r1, #0x34
	mov r1, r0, lsr r2
	cmp r0, r1, lsl r2
	andeq r1, r1, #0x1
	rsbeq r5, r1, #0x2
	b _020E7188
_020E7170:
	cmp r0, #0x0
	rsbeq r2, r1, #0x14
	moveq r1, r9, asr r2
	cmpeq r9, r1, lsl r2
	andeq r1, r1, #0x1
	rsbeq r5, r1, #0x2
_020E7188:
	cmp r0, #0x0
	bne _020E72E4
	ldr r1, _020E763C ; =0x7FF00000
	cmp r9, r1
	bne _020E723C
	add r0, r4, #0x100000
	add r0, r0, #0xc0000000
	orrs r0, r0, r7
	bne _020E71D0
	ldr r0, [sp, #0xb0]
	ldr r1, [sp, #0xb4]
	mov r2, r0
	mov r3, r1
	bl _dsub
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E71D0:
	sub r0, r1, #0x40000000
	cmp r4, r0
	blt _020E7200
	cmp r8, #0x0
	ldrge r0, [sp, #0xb0]
	ldrge r1, [sp, #0xb4]
	movlt r0, #0x0
	add sp, sp, #0x80
	movlt r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7200:
	cmp r8, #0x0
	mov r0, #0x0
	addge sp, sp, #0x80
	movge r1, r0
	ldmgeia sp!, {r3-r11,lr}
	addge sp, sp, #0x10
	bxge lr
	ldr r2, [sp, #0xb0]
	ldr r3, [sp, #0xb4]
	mov r1, r0
	bl _dsub
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E723C:
	sub r0, r1, #0x40000000
	cmp r9, r0
	bne _020E7288
	cmp r8, #0x0
	ldrge r0, [sp, #0xa8]
	ldrge r1, [sp, #0xac]
	addge sp, sp, #0x80
	ldmgeia sp!, {r3-r11,lr}
	addge sp, sp, #0x10
	bxge lr
	ldr r2, [sp, #0xa8]
	ldr r3, [sp, #0xac]
	sub r1, r1, #0x40000000
	mov r0, #0x0
	bl _ddiv
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7288:
	cmp r8, #0x40000000
	bne _020E72B4
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	mov r2, r0
	mov r3, r1
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E72B4:
	ldr r0, _020E7648 ; =0x3FE00000
	cmp r8, r0
	bne _020E72E4
	cmp r6, #0x0
	blt _020E72E4
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	bl _dsqrt
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E72E4:
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	bl fabs
	str r0, [sp, #0x70]
	str r1, [sp, #0x74]
	cmp r7, #0x0
	bne _020E73E8
	ldr r0, _020E763C ; =0x7FF00000
	cmp r4, r0
	cmpne r4, #0x0
	subne r0, r0, #0x40000000
	cmpne r4, r0
	bne _020E73E8
	ldr r2, [sp, #0x70]
	ldr r3, [sp, #0x74]
	str r2, [sp, #0x78]
	str r3, [sp, #0x7c]
	cmp r8, #0x0
	bge _020E7344
	ldr r1, _020E7638 ; =0x3FF00000
	mov r0, #0x0
	bl _ddiv
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
_020E7344:
	cmp r6, #0x0
	bge _020E73D0
	add r0, r4, #0x100000
	add r0, r0, #0xc0000000
	orrs r0, r0, r5
	bne _020E73AC
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r0
	mov r3, r1
	bl _dsub
	mov r4, r0
	mov r5, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r0
	mov r3, r1
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r5
	bl _ddiv
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
	b _020E73D0
_020E73AC:
	cmp r5, #0x1
	bne _020E73D0
	mov r0, #0x0
	ldr r2, [sp, #0x78]
	ldr r3, [sp, #0x7c]
	mov r1, r0
	bl _dsub
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
_020E73D0:
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E73E8:
	mov r0, r6, asr #0x1f
	add r7, r0, #0x1
	orrs r0, r7, r5
	bne _020E7420
	ldr r0, _020E764C ; =__float_nan
	ldr r1, _020E7650 ; =errno
	ldr r0, [r0, #0x0]
	mov r2, #0x21
	str r2, [r1, #0x0]
	bl _f2d
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7420:
	ldr r3, _020E7654 ; =0x41E00000
	cmp r9, r3
	ble _020E7724
	add r0, r3, #0x2100000
	cmp r9, r0
	ble _020E7490
	ldr r1, _020E7658 ; =0x3FEFFFFF
	cmp r4, r1
	bgt _020E7464
	cmp r8, #0x0
	mov r0, #0x0
	addlt r1, r1, #0x40000001
	add sp, sp, #0x80
	movge r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7464:
	add r0, r1, #0x1
	cmp r4, r0
	blt _020E7490
	cmp r8, #0x0
	mov r0, #0x0
	addgt r1, r1, #0x40000001
	add sp, sp, #0x80
	movle r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7490:
	ldr r2, _020E7658 ; =0x3FEFFFFF
	cmp r4, r2
	bge _020E74BC
	cmp r8, #0x0
	mov r0, #0x0
	addlt r1, r2, #0x40000001
	add sp, sp, #0x80
	movge r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E74BC:
	add r0, r2, #0x1
	cmp r4, r0
	ble _020E74E8
	cmp r8, #0x0
	mov r0, #0x0
	addgt r1, r2, #0x40000001
	add sp, sp, #0x80
	movle r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E74E8:
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	add r3, r2, #0x1
	mov r2, #0x0
	bl _dsub
	mov r2, r0
	mov r3, r1
	str r0, [sp, #0x50]
	str r1, [sp, #0x54]
	bl _dmul
	mov r6, r1
	mov r4, r0
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	ldr r1, _020E765C ; =0x3FD00000
	mov r0, #0x0
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7660 ; =0x55555555
	sub r1, r0, #0x15800000
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, #0x0
	ldr r1, _020E7648 ; =0x3FE00000
	bl _dsub
	mov r2, r0
	mov r0, r4
	mov r3, r1
	mov r1, r6
	bl _dmul
	mov r6, r0
	mov r8, r1
	mov r0, #0x60000000
	ldr r1, _020E7664 ; =0x3FF71547
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dmul
	mov r4, r0
	mov r9, r1
	ldr r0, _020E7668 ; =0xF85DDF44
	ldr r1, _020E766C ; =0x3E54AE0B
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dmul
	mov r11, r0
	mov r10, r1
	ldr r0, _020E7670 ; =0x652B82FE
	ldr r1, _020E7664 ; =0x3FF71547
	mov r2, r6
	mov r3, r8
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r11
	mov r1, r10
	bl _dsub
	mov r6, r0
	mov r8, r1
	mov r0, r4
	mov r1, r9
	mov r2, r6
	mov r3, r8
	bl _dadd
	mov r2, r4
	mov r3, r9
	str r1, [sp, #0x5c]
	mov r0, #0x0
	str r0, [sp, #0x58]
	bl _dsub
	mov r2, r0
	mov r0, r6
	mov r3, r1
	mov r1, r8
	bl _dsub
	mov r4, r0
	mov r8, r1
	b _020E7C80
	.balign 4
_020E7638: .word 0x3FF00000
_020E763C: .word 0x7FF00000
_020E7640: .word 0x43400000
_020E7644: .word 0xFFFFFC01
_020E7648: .word 0x3FE00000
_020E764C: .word __float_nan
_020E7650: .word errno
_020E7654: .word 0x41E00000
_020E7658: .word 0x3FEFFFFF
_020E765C: .word 0x3FD00000
_020E7660: .word 0x55555555
_020E7664: .word 0x3FF71547
_020E7668: .word 0xF85DDF44
_020E766C: .word 0x3E54AE0B
_020E7670: .word 0x652B82FE
_020E7674: .word 0x0003988E
_020E7678: .word 0x000BB67A
_020E767C: .word UNK_02104754
_020E7680: .word 0x4A454EEF
_020E7684: .word 0x3FCA7E28
_020E7688: .word 0x93C9DB65
_020E768C: .word 0x3FCD864A
_020E7690: .word 0xA91D4101
_020E7694: .word 0x3FD17460
_020E7698: .word 0x518F264D
_020E769C: .word 0x3FD55555
_020E76A0: .word 0xDB6FABFF
_020E76A4: .word 0x3FDB6DB6
_020E76A8: .word 0x33333303
_020E76AC: .word 0x3FE33333
_020E76B0: .word 0x40080000
_020E76B4: .word 0x3FEEC709
_020E76B8: .word 0x145B01F5
_020E76BC: .word 0xBE3E2FE0
_020E76C0: .word 0xDC3A03FD
_020E76C4: .word UNK_02104764
_020E76C8: .word UNK_02104744
_020E76CC: .word 0x40900000
_020E76D0: .word 0x8800759C
_020E76D4: .word 0x7E37E43C
_020E76D8: .word 0x3C971547
_020E76DC: .word 0x3F6F3400
_020E76E0: .word 0xC2F8F359
_020E76E4: .word 0x01A56E1F
_020E76E8: .word 0x3FE62E43
_020E76EC: .word 0xFEFA39EF
_020E76F0: .word 0x3FE62E42
_020E76F4: .word 0x0CA86C39
_020E76F8: .word 0xBE205C61
_020E76FC: .word 0x72BEA4D0
_020E7700: .word 0x3E663769
_020E7704: .word 0xC5D26BF1
_020E7708: .word 0xBEBBBD41
_020E770C: .word 0xAF25DE2C
_020E7710: .word 0x3F11566A
_020E7714: .word 0x16BEBD93
_020E7718: .word 0xBF66C16C
_020E771C: .word 0x5555553E
_020E7720: .word 0x3FC55555
_020E7724:
	cmp r4, #0x100000
	mov r6, #0x0
	bge _020E7754
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	mov r2, r6
	add r3, r3, #0x1600000
	bl _dmul
	mov r4, r1
	str r0, [sp, #0x70]
	str r4, [sp, #0x74]
	sub r6, r6, #0x35
_020E7754:
	ldr r0, _020E7644 ; =0xFFFFFC01
	ldr r1, _020E7674 ; =0x0003988E
	and r2, r4, r0, lsr #0xc
	add r0, r0, r4, asr #0x14
	orr r9, r2, #0xff00000
	cmp r2, r1
	add r6, r6, r0
	orr r9, r9, #0x30000000
	movle r8, #0x0
	ble _020E7794
	ldr r0, _020E7678 ; =0x000BB67A
	cmp r2, r0
	movlt r8, #0x1
	addge r6, r6, #0x1
	subge r9, r9, #0x100000
	movge r8, #0x0
_020E7794:
	ldr r2, _020E767C ; =UNK_02104754
	ldr r0, [sp, #0x70]
	add r1, r2, r8, lsl #0x3
	ldr r3, [r1, #0x4]
	ldr r2, [r2, r8, lsl #0x3]
	mov r1, r9
	str r9, [sp, #0x74]
	bl _dsub
	ldr r2, _020E767C ; =UNK_02104754
	mov r10, r0
	add r3, r2, r8, lsl #0x3
	mov r4, r1
	ldr r0, [sp, #0x70]
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	mov r1, r9
	bl _dadd
	mov r3, r1
	mov r2, r0
	ldr r1, _020E7638 ; =0x3FF00000
	mov r0, #0x0
	bl _ddiv
	str r1, [sp, #0x24]
	mov r11, r0
	ldr r3, [sp, #0x24]
	mov r0, r10
	mov r1, r4
	mov r2, r11
	bl _dmul
	mov r2, r9, asr #0x1
	orr r2, r2, #0x20000000
	mov r9, r1
	add r2, r2, #0x80000
	add r1, r2, r8, lsl #0x12
	ldr r2, _020E767C ; =UNK_02104754
	str r0, [sp, #0x28]
	add r3, r2, r8, lsl #0x3
	mov r0, #0x0
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	str r9, [sp, #0x4c]
	str r1, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x40]
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	bl _dsub
	str r0, [sp, #0x2c]
	str r1, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	mov r1, r9
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r10
	mov r1, r4
	bl _dsub
	mov r10, r0
	mov r4, r1
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	mov r1, r9
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r10
	mov r1, r4
	bl _dsub
	mov r3, r1
	mov r2, r0
	ldr r1, [sp, #0x24]
	mov r0, r11
	bl _dmul
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x14]
	mov r1, r9
	mov r2, r0
	mov r3, r9
	bl _dmul
	mov r4, r0
	mov r10, r1
	mov r2, r4
	mov r3, r10
	bl _dmul
	str r0, [sp, #0x34]
	mov r11, r1
	ldr r0, _020E7680 ; =0x4A454EEF
	ldr r1, _020E7684 ; =0x3FCA7E28
	mov r2, r4
	mov r3, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7688 ; =0x93C9DB65
	ldr r1, _020E768C ; =0x3FCD864A
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7690 ; =0xA91D4101
	ldr r1, _020E7694 ; =0x3FD17460
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7698 ; =0x518F264D
	ldr r1, _020E769C ; =0x3FD55555
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76A0 ; =0xDB6FABFF
	ldr r1, _020E76A4 ; =0x3FDB6DB6
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76A8 ; =0x33333303
	ldr r1, _020E76AC ; =0x3FE33333
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x34]
	mov r1, r11
	bl _dmul
	mov r4, r0
	mov r10, r1
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x28]
	mov r1, r9
	mov r3, r9
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x14]
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dadd
	mov r4, r0
	ldr r0, [sp, #0x48]
	mov r10, r1
	mov r1, r9
	mov r2, r0
	mov r3, r1
	bl _dmul
	str r1, [sp, #0xc]
	mov r11, r0
	ldr r1, _020E76B0 ; =0x40080000
	ldr r3, [sp, #0xc]
	mov r0, #0x0
	mov r2, r11
	bl _dadd
	mov r2, r4
	mov r3, r10
	bl _dadd
	mov r0, #0x0
	ldr r3, _020E76B0 ; =0x40080000
	mov r2, r0
	str r1, [sp, #0x44]
	str r0, [sp, #0x40]
	bl _dsub
	ldr r3, [sp, #0xc]
	mov r2, r11
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dsub
	str r0, [sp, #0x38]
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	mov r1, r9
	bl _dmul
	mov r4, r0
	mov r10, r1
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	bl _dmul
	str r0, [sp, #0x3c]
	mov r11, r1
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x28]
	mov r3, r9
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x3c]
	mov r1, r11
	bl _dadd
	mov r9, r0
	mov r11, r1
	mov r0, r4
	mov r1, r10
	mov r2, r9
	mov r3, r11
	bl _dadd
	mov r0, #0x0
	mov r2, r4
	mov r3, r10
	str r1, [sp, #0x6c]
	str r0, [sp, #0x68]
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r9
	mov r1, r11
	bl _dsub
	mov r10, r1
	mov r11, r0
	ldr r1, _020E76B4 ; =0x3FEEC709
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	mov r0, #0xe0000000
	bl _dmul
	mov r4, r0
	mov r9, r1
	ldr r0, _020E76B8 ; =0x145B01F5
	ldr r1, _020E76BC ; =0xBE3E2FE0
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	bl _dmul
	mov r2, r11
	mov r3, r10
	mov r11, r0
	mov r10, r1
	ldr r0, _020E76C0 ; =0xDC3A03FD
	ldr r1, _020E76B4 ; =0x3FEEC709
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r11
	mov r1, r10
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76C4 ; =UNK_02104764
	add r1, r0, r8, lsl #0x3
	ldr r0, [r0, r8, lsl #0x3]
	ldr r1, [r1, #0x4]
	bl _dadd
	mov r11, r0
	mov r10, r1
	mov r0, r6
	bl _dflt
	str r0, [sp, #0x50]
	str r1, [sp, #0x54]
	mov r0, r4
	mov r1, r9
	mov r2, r11
	mov r3, r10
	bl _dadd
	ldr r2, _020E76C8 ; =UNK_02104744
	add r3, r2, r8, lsl #0x3
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dadd
	str r1, [sp, #0x5c]
	mov r0, #0x0
	str r0, [sp, #0x58]
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dsub
	ldr r2, _020E76C8 ; =UNK_02104744
	add r3, r2, r8, lsl #0x3
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	bl _dsub
	mov r2, r4
	mov r3, r9
	bl _dsub
	mov r2, r0
	mov r0, r11
	mov r3, r1
	mov r1, r10
	bl _dsub
	mov r4, r0
	mov r8, r1
_020E7C80:
	sub r0, r5, #0x1
	ldr r1, [sp, #0xb4]
	orrs r0, r7, r0
	ldr r5, _020E7638 ; =0x3FF00000
	mov r2, #0x0
	ldr r0, [sp, #0xb0]
	mov r3, r1
	mov r6, #0x0
	subeq r5, r5, #0x80000000
	str r1, [sp, #0x64]
	str r2, [sp, #0x60]
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x58]
	ldr r1, [sp, #0x5c]
	bl _dmul
	mov r7, r0
	mov r9, r1
	ldr r0, [sp, #0xb0]
	ldr r1, [sp, #0xb4]
	mov r2, r4
	mov r3, r8
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r9
	bl _dadd
	mov r7, r0
	mov r8, r1
	ldr r0, [sp, #0x60]
	ldr r1, [sp, #0x64]
	ldr r2, [sp, #0x58]
	ldr r3, [sp, #0x5c]
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r8
	str r2, [sp, #0x68]
	str r3, [sp, #0x6c]
	bl _dadd
	mov r9, r1
	ldr r2, _020E76CC ; =0x40900000
	str r0, [sp, #0x78]
	str r9, [sp, #0x7c]
	cmp r9, r2
	blt _020E7E0C
	add r1, r9, #0xf700000
	add r1, r1, #0xb0000000
	orrs r0, r1, r0
	beq _020E7D8C
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7D8C:
	ldr r0, _020E7670 ; =0x652B82FE
	ldr r1, _020E76D8 ; =0x3C971547
	mov r2, r7
	mov r3, r8
	bl _dadd
	mov r4, r0
	mov r10, r1
	ldr r0, [sp, #0x78]
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	mov r1, r9
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dgr
	bls _020E7EC0
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7E0C:
	bic r3, r9, #0x80000000
	add r2, r2, #0xcc00
	cmp r3, r2
	blt _020E7EC0
	ldr r2, _020E76DC ; =0x3F6F3400
	add r2, r9, r2
	orrs r2, r2, r0
	beq _020E7E64
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7E64:
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r8
	bl _dleq
	bhi _020E7EC0
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7EC0:
	ldr r0, _020E7644 ; =0xFFFFFC01
	bic r3, r9, #0x80000000
	ldr r1, _020E7648 ; =0x3FE00000
	add r2, r0, r3, asr #0x14
	cmp r3, r1
	mov r4, #0x0
	ble _020E7F3C
	mov r1, #0x100000
	add r2, r2, #0x1
	add r2, r9, r1, asr r2
	bic r3, r2, #0x80000000
	add r0, r0, r3, asr #0x14
	sub r3, r1, #0x1
	mvn r3, r3, asr r0
	sub r1, r1, #0x1
	and r1, r2, r1
	and r2, r2, r3
	str r2, [sp, #0x54]
	str r4, [sp, #0x50]
	orr r1, r1, #0x100000
	rsb r0, r0, #0x14
	mov r4, r1, asr r0
	cmp r9, #0x0
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x6c]
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	rsblt r4, r4, #0x0
	bl _dsub
	str r0, [sp, #0x68]
	str r1, [sp, #0x6c]
_020E7F3C:
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	mov r0, r7
	mov r1, r8
	bl _dadd
	mov r3, r1
	mov r0, #0x0
	ldr r1, _020E76E8 ; =0x3FE62E43
	mov r2, r0
	str r3, [sp, #0x54]
	str r0, [sp, #0x50]
	bl _dmul
	mov r9, r0
	mov r10, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	bl _dsub
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r8
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76EC ; =0xFEFA39EF
	ldr r1, _020E76F0 ; =0x3FE62E42
	bl _dmul
	mov r7, r0
	mov r8, r1
	ldr r0, _020E76F4 ; =0x0CA86C39
	ldr r1, _020E76F8 ; =0xBE205C61
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r8
	bl _dadd
	mov r7, r0
	mov r8, r1
	mov r0, r9
	mov r1, r10
	mov r2, r7
	mov r3, r8
	bl _dadd
	mov r2, r9
	mov r3, r10
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r8
	bl _dsub
	mov r8, r0
	mov r9, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r0
	mov r3, r1
	bl _dmul
	mov r2, r0
	str r2, [sp, #0x50]
	mov r3, r1
	str r3, [sp, #0x54]
	ldr r0, _020E76FC ; =0x72BEA4D0
	ldr r1, _020E7700 ; =0x3E663769
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7704 ; =0xC5D26BF1
	ldr r1, _020E7708 ; =0xBEBBBD41
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E770C ; =0xAF25DE2C
	ldr r1, _020E7710 ; =0x3F11566A
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7714 ; =0x16BEBD93
	ldr r1, _020E7718 ; =0xBF66C16C
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E771C ; =0x5555553E
	ldr r1, _020E7720 ; =0x3FC55555
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	bl _dsub
	mov r2, r0
	str r2, [sp, #0x58]
	mov r3, r1
	str r3, [sp, #0x5c]
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	bl _dmul
	mov r7, r0
	mov r10, r1
	ldr r0, [sp, #0x58]
	ldr r1, [sp, #0x5c]
	mov r2, #0x0
	mov r3, #0x40000000
	bl _dsub
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r10
	bl _ddiv
	mov r7, r0
	mov r10, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r8
	mov r3, r9
	bl _dmul
	mov r2, r0
	mov r0, r8
	mov r3, r1
	mov r1, r9
	bl _dadd
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r10
	bl _dsub
	ldr r2, [sp, #0x78]
	ldr r3, [sp, #0x7c]
	bl _dsub
	mov r3, r1
	mov r2, r0
	ldr r1, _020E7638 ; =0x3FF00000
	mov r0, #0x0
	bl _dsub
	add r3, r1, r4, lsl #0x14
	mov r2, r3, asr #0x14
	str r0, [sp, #0x78]
	cmp r2, #0x0
	str r1, [sp, #0x7c]
	addgt r0, sp, #0x78
	strgt r3, [r0, #0x4]
	bgt _020E81F0
	mov r2, r4
	bl scalbn
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
_020E81F0:
	ldr r2, [sp, #0x78]
	ldr r3, [sp, #0x7c]
	mov r0, r6
	mov r1, r5
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	arm_func_end __ieee754_pow

	exception __ieee754_pow, 4488, UNK_020EC738

	.section .exception,8

	.global UNK_020EC738
UNK_020EC738: ; 0x020EC738
	.byte 0x20, 0xFF, 0x01, 0xB8
	.balign 8
