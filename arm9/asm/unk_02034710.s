	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02034710
FUN_02034710: ; 0x02034710
	push {r3, lr}
	ldr r1, _02034720 ; =0x0000022F
	cmp r0, r1
	blo _0203471E
	bl ErrorHandling
	mov r0, #0x3
_0203471E:
	pop {r3, pc}
	.balign 4
_02034720: .word 0x0000022F

	thumb_func_start FUN_02034724
FUN_02034724: ; 0x02034724
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034734 ; =0x020EEDBC
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034734: .word 0x020EEDBC

	thumb_func_start FUN_02034738
FUN_02034738: ; 0x02034738
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034748 ; =0x020EEDBD
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034748: .word 0x020EEDBD

	thumb_func_start FUN_0203474C
FUN_0203474C: ; 0x0203474C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _0203476C ; =0x020EEDBE
	ldrh r0, [r0, r1]
	cmp r0, #0x16
	bne _02034768
	ldr r1, _02034770 ; =0x020ECAC0
	ldrb r1, [r1, #0x0]
	cmp r1, #0xb
	bne _02034768
	mov r0, #0x17
_02034768:
	pop {r3, pc}
	nop
_0203476C: .word 0x020EEDBE
_02034770: .word 0x020ECAC0

	thumb_func_start FUN_02034774
FUN_02034774: ; 0x02034774
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034784 ; =0x020EEDC4
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034784: .word 0x020EEDC4

	thumb_func_start FUN_02034788
FUN_02034788: ; 0x02034788
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034798 ; =0x020EEDC0
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034798: .word 0x020EEDC0

	thumb_func_start FUN_0203479C
FUN_0203479C: ; 0x0203479C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347AC ; =0x020EEDC2
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020347AC: .word 0x020EEDC2

	thumb_func_start FUN_020347B0
FUN_020347B0: ; 0x020347B0
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347C0 ; =0x020EEDC6
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020347C0: .word 0x020EEDC6

	thumb_func_start FUN_020347C4
FUN_020347C4: ; 0x020347C4
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347D4 ; =0x020EEDC8
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020347D4: .word 0x020EEDC8

	thumb_func_start FUN_020347D8
FUN_020347D8: ; 0x020347D8
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020347F4 ; =0x020EEDCA
	ldrh r1, [r0, r1]
	ldr r0, _020347F8 ; =0x0000FFFF
	cmp r1, r0
	beq _020347F0
	mov r0, #0x1
	pop {r3, pc}
_020347F0:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4
_020347F4: .word 0x020EEDCA
_020347F8: .word 0x0000FFFF

	thumb_func_start FUN_020347FC
FUN_020347FC: ; 0x020347FC
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _0203480C ; =0x020EEDCA
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0203480C: .word 0x020EEDCA

	thumb_func_start FUN_02034810
FUN_02034810: ; 0x02034810
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034820 ; =0x020EEDCC
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034820: .word 0x020EEDCC

	thumb_func_start FUN_02034824
FUN_02034824: ; 0x02034824
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034834 ; =0x020EEDCE
	ldrh r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034834: .word 0x020EEDCE

	thumb_func_start FUN_02034838
FUN_02034838: ; 0x02034838
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034848 ; =0x020EEDD0
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_02034848: .word 0x020EEDD0

	thumb_func_start FUN_0203484C
FUN_0203484C: ; 0x0203484C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _0203485C ; =0x020EEDD1
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0203485C: .word 0x020EEDD1

	thumb_func_start FUN_02034860
FUN_02034860: ; 0x02034860
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034878 ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	pop {r3, pc}
	nop
_02034878: .word 0x020EEDBC

	thumb_func_start FUN_0203487C
FUN_0203487C: ; 0x0203487C
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _02034894 ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	pop {r3, pc}
	nop
_02034894: .word 0x020EEDBC

	thumb_func_start FUN_02034898
FUN_02034898: ; 0x02034898
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020348B0 ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	pop {r3, pc}
	nop
_020348B0: .word 0x020EEDBC

	thumb_func_start FUN_020348B4
FUN_020348B4: ; 0x020348B4
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020348CC ; =0x020EEDBC
	add r0, r0, r1
	ldrb r0, [r0, #0x17]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	pop {r3, pc}
	nop
_020348CC: .word 0x020EEDBC

	thumb_func_start FUN_020348D0
FUN_020348D0: ; 0x020348D0
	push {r3, lr}
	bl FUN_02034710
	mov r1, #0x18
	mul r1, r0
	ldr r0, _020348E0 ; =0x020EEDD2
	ldrb r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_020348E0: .word 0x020EEDD2

	thumb_func_start FUN_020348E4
FUN_020348E4: ; 0x020348E4
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02034898
	cmp r0, #0x0
	bne _020348F4
	mov r0, #0x0
	pop {r4, pc}
_020348F4:
	add r0, r4, #0x0
	bl FUN_020348D0
	cmp r0, #0x1
	beq _02034902
	mov r0, #0x1
	pop {r4, pc}
_02034902:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034908
FUN_02034908: ; 0x02034908
	push {r3, lr}
	bl FUN_0203474C
	cmp r0, #0x0
	bne _02034916
	mov r0, #0x1
	pop {r3, pc}
_02034916:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_0203491C
FUN_0203491C: ; 0x0203491C
	push {r3, lr}
	bl FUN_020348D0
	cmp r0, #0x5
	bne _0203492A
	mov r0, #0x1
	pop {r3, pc}
_0203492A:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02034930
FUN_02034930: ; 0x02034930
	push {r3, lr}
	bl FUN_020348D0
	cmp r0, #0x3
	bne _0203493E
	mov r0, #0x1
	pop {r3, pc}
_0203493E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02034944
FUN_02034944: ; 0x02034944
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020348D0
	cmp r0, #0x4
	beq _0203495A
	add r0, r4, #0x0
	bl FUN_020348D0
	cmp r0, #0x5
	bne _0203495E
_0203495A:
	mov r0, #0x1
	pop {r4, pc}
_0203495E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034964
FUN_02034964: ; 0x02034964
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020348D0
	cmp r0, #0x1
	beq _0203497A
	add r0, r4, #0x0
	bl FUN_020348D0
	cmp r0, #0x2
	bne _0203497E
_0203497A:
	mov r0, #0x1
	pop {r4, pc}
_0203497E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02034984
FUN_02034984: ; 0x02034984
	push {r3, lr}
	bl FUN_0203491C
	cmp r0, #0x0
	beq _02034992
	mov r0, #0x1
	pop {r3, pc}
_02034992:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02034998
FUN_02034998: ; 0x02034998
	ldr r1, _020349A8 ; =0x000001D2
	cmp r0, r1
	bne _020349A2
	mov r0, #0x1
	bx lr
_020349A2:
	mov r0, #0x0
	bx lr
	nop
_020349A8: .word 0x000001D2

	thumb_func_start FUN_020349AC
FUN_020349AC: ; 0x020349AC
	cmp r0, #0xdb
	bne _020349B4
	mov r0, #0x1
	bx lr
_020349B4:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020349B8
FUN_020349B8: ; 0x020349B8
	ldr r1, _020349C8 ; =0x0000011F
	cmp r0, r1
	bne _020349C2
	mov r0, #0x1
	bx lr
_020349C2:
	mov r0, #0x0
	bx lr
	nop
_020349C8: .word 0x0000011F

	thumb_func_start FUN_020349CC
FUN_020349CC: ; 0x020349CC
	cmp r0, #0xfd
	bne _020349D4
	mov r0, #0x1
	bx lr
_020349D4:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020349D8
FUN_020349D8: ; 0x020349D8
	cmp r0, #0xdc
	bne _020349E0
	mov r0, #0x1
	bx lr
_020349E0:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020349E4
FUN_020349E4: ; 0x020349E4
	ldr r3, _02034A00 ; =0x020EED54
	mov r2, #0x0
_020349E8:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _020349F2
	mov r0, #0x1
	bx lr
_020349F2:
	add r2, r2, #0x1
	add r3, r3, #0x2
	cmp r2, #0x12
	blo _020349E8
	mov r0, #0x0
	bx lr
	nop
_02034A00: .word 0x020EED54

	thumb_func_start FUN_02034A04
FUN_02034A04: ; 0x02034A04
	ldr r3, _02034A24 ; =0x020EED78
	mov r2, #0x0
_02034A08:
	ldrh r1, [r3, #0x0]
	cmp r0, r1
	bne _02034A18
	add r0, r2, #0x1
	lsl r1, r0, #0x1
	ldr r0, _02034A24 ; =0x020EED78
	ldrh r0, [r0, r1]
	bx lr
_02034A18:
	add r2, r2, #0x2
	add r3, r3, #0x4
	cmp r2, #0x22
	blo _02034A08
	mov r0, #0x0
	bx lr
	.balign 4
_02034A24: .word 0x020EED78
