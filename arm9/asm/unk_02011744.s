    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020ED438
	.extern UNK_020ED4B2
	.extern UNK_020ED398
	.extern UNK_020ED498
	.extern UNK_020ED4CC
	.extern UNK_020ED399
	.extern UNK_020ED4A4
	.extern UNK_020ED3C8
	.extern UNK_020FFA38
	.extern UNK_021C4828
	.extern UNK_020ED3B8
	.extern UNK_021C4818
	.extern UNK_021C4808
	.extern UNK_020ED3B0
	.extern UNK_020ED3D8

	.text

	thumb_func_start FUN_02011744
FUN_02011744: ; 0x02011744
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r1, #0x0
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x68
	bl FUN_02016998
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0201175E
	bl ErrorHandling
_0201175E:
	ldr r4, [sp, #0x8]
	ldr r5, [sp, #0x8]
	mov r6, #0x0
	add r4, #0x30
_02011766:
	mov r0, #0x23
	add r1, r6, #0x0
	mov r2, #0x0
	add r3, r4, #0x0
	str r7, [sp, #0x0]
	bl FUN_02006C30
	str r0, [r5, #0x0]
	cmp r0, #0x0
	bne _0201177E
	bl ErrorHandling
_0201177E:
	add r6, r6, #0x1
	add r4, r4, #0x4
	add r5, r5, #0x4
	cmp r6, #0xc
	blt _02011766
	ldr r0, [sp, #0x4]
	mov r1, #0x14
	add r4, r0, #0x0
	mul r4, r1
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_02016998
	ldr r1, [sp, #0x8]
	cmp r0, #0x0
	str r0, [r1, #0x60]
	bne _020117A4
	bl ErrorHandling
_020117A4:
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x8]
	add r2, r4, #0x0
	str r1, [r0, #0x64]
	ldr r0, [r0, #0x60]
	mov r1, #0x0
	bl memset
	ldr r0, [sp, #0x8]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020117BC
FUN_020117BC: ; 0x020117BC
	push {r4-r6, lr}
	add r6, r0, #0x0
	bne _020117C6
	bl ErrorHandling
_020117C6:
	mov r4, #0x0
	add r5, r6, #0x0
_020117CA:
	ldr r0, [r5, #0x0]
	bl FUN_02016A18
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0xc
	blt _020117CA
	ldr r0, [r6, #0x60]
	bl FUN_02016A18
	add r0, r6, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020117E8
FUN_020117E8: ; 0x020117E8
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	bne _020117F4
	bl ErrorHandling
_020117F4:
	ldr r0, [r5, #0x0]
	bl FUN_02011BA0
	add r4, r0, #0x0
	bne _02011802
	bl ErrorHandling
_02011802:
	ldr r0, [r5, #0x10]
	add r3, sp, #0x8
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x18]
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x1c]
	str r0, [r4, #0x10]
	str r3, [sp, #0x14]
	str r3, [sp, #0x18]
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x2c]
	ldrb r0, [r1, #0x7]
	ldrb r1, [r1, #0x8]
	bl FUN_02011CA4
	add r6, r0, #0x0
	mov r1, #0x24
	ldr r0, [r5, #0x2c]
	mul r1, r6
	bl FUN_020169D8
	add r7, r0, #0x0
	mov r1, #0xc
	ldr r0, [r5, #0x2c]
	mul r1, r6
	bl FUN_02016998
	str r0, [r4, #0x0]
	str r6, [r4, #0x4]
	ldr r0, [r5, #0x28]
	add r1, sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x2c]
	add r2, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x4]
	ldr r3, [r5, #0x14]
	bl FUN_02011D2C
	add r0, r5, #0x0
	add r1, sp, #0x8
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl FUN_02011EAC
	add r0, r7, #0x0
	bl FUN_02016A18
	add r0, sp, #0x8
	bl FUN_02011FDC
	add r0, r4, #0x0
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02011870
FUN_02011870: ; 0x02011870
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201187A
	bl ErrorHandling
_0201187A:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02011884
	bl ErrorHandling
_02011884:
	add r0, r4, #0x0
	bl FUN_02011F00
	ldr r0, [r4, #0x0]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02011B90
	pop {r4, pc}

	thumb_func_start FUN_02011898
FUN_02011898: ; 0x02011898
	push {r4-r5, lr}
	sub sp, #0x14
	add r3, sp, #0x0
	add r5, r0, #0x0
	str r3, [sp, #0xc]
	str r3, [sp, #0x10]
	add r4, r1, #0x0
	ldrb r0, [r5, #0x7]
	ldrb r1, [r5, #0x8]
	bl FUN_02011CA4
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl FUN_02011E58
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl FUN_02011FDC
	add r0, r4, #0x0
	add sp, #0x14
	pop {r4-r5, pc}

	thumb_func_start FUN_020118C4
FUN_020118C4: ; 0x020118C4
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r7, r2, #0x0
	str r1, [sp, #0x0]
	cmp r5, #0x0
	bne _020118D6
	bl ErrorHandling
_020118D6:
	ldr r0, [sp, #0x0]
	str r0, [r5, #0xc]
	str r7, [r5, #0x10]
	lsl r0, r0, #0xc
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x8]
	lsl r7, r7, #0xc
	cmp r0, #0x0
	beq _020118F8
	bl FUN_0202011C
	ldr r2, [r0, #0x0]
	ldr r1, [sp, #0x0]
	ldr r0, [r0, #0x4]
	add r1, r1, r2
	str r1, [sp, #0x0]
	add r7, r7, r0
_020118F8:
	mov r6, #0x0
	str r6, [sp, #0xc]
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	ble _02011932
	add r4, r6, #0x0
_02011904:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	lsl r1, r0, #0xc
	ldr r0, [sp, #0x0]
	add r0, r0, r1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, sp, #0x4
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	add r0, r7, r0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02020044
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011904
_02011932:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011938
FUN_02011938: ; 0x02011938
	push {r3-r7, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	bne _02011944
	bl ErrorHandling
_02011944:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _0201199E
	ldr r1, [r5, #0xc]
	lsl r1, r1, #0xc
	str r1, [sp, #0x0]
	ldr r1, [r5, #0x10]
	lsl r7, r1, #0xc
	bl FUN_0202011C
	ldr r2, [r0, #0x0]
	ldr r0, [r0, #0x4]
	mov r6, #0x0
	ldr r1, [sp, #0x0]
	str r6, [sp, #0xc]
	add r7, r7, r0
	add r1, r1, r2
	ldr r0, [r5, #0x4]
	str r1, [sp, #0x0]
	cmp r0, #0x0
	ble _0201199E
	add r4, r6, #0x0
_02011970:
	ldr r0, [r5, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x4]
	lsl r1, r0, #0xc
	ldr r0, [sp, #0x0]
	add r0, r0, r1
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	add r1, sp, #0x4
	add r0, r0, r4
	ldr r0, [r0, #0x8]
	lsl r0, r0, #0xc
	add r0, r7, r0
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	bl FUN_02020044
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011970
_0201199E:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020119A4
FUN_020119A4: ; 0x020119A4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r5, #0x0
	bne _020119B4
	bl ErrorHandling
_020119B4:
	cmp r4, #0x0
	bne _020119BC
	bl ErrorHandling
_020119BC:
	cmp r6, #0x0
	bne _020119C4
	bl ErrorHandling
_020119C4:
	ldr r0, [r5, #0xc]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x10]
	str r0, [r6, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020119D0
FUN_020119D0: ; 0x020119D0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _020119DE
	bl ErrorHandling
_020119DE:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _020119FC
	add r4, r6, #0x0
_020119E8:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_020200A0
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _020119E8
_020119FC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A00
FUN_02011A00: ; 0x02011A00
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A0E
	bl ErrorHandling
_02011A0E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011A2C
	add r4, r6, #0x0
_02011A18:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020238
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011A18
_02011A2C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A30
FUN_02011A30: ; 0x02011A30
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A3E
	bl ErrorHandling
_02011A3E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011A5C
	add r4, r6, #0x0
_02011A48:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020310
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011A48
_02011A5C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A60
FUN_02011A60: ; 0x02011A60
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A6E
	bl ErrorHandling
_02011A6E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011A8C
	add r4, r6, #0x0
_02011A78:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020248
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011A78
_02011A8C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011A90
FUN_02011A90: ; 0x02011A90
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011A9E
	bl ErrorHandling
_02011A9E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011ABC
	add r4, r6, #0x0
_02011AA8:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_020202A8
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011AA8
_02011ABC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011AC0
FUN_02011AC0: ; 0x02011AC0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011ACE
	bl ErrorHandling
_02011ACE:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011AEC
	add r4, r6, #0x0
_02011AD8:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_020202DC
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011AD8
_02011AEC:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011AF0
FUN_02011AF0: ; 0x02011AF0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _02011AFE
	bl ErrorHandling
_02011AFE:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011B1C
	add r4, r6, #0x0
_02011B08:
	ldr r0, [r5, #0x0]
	add r1, r7, #0x0
	ldr r0, [r0, r4]
	bl FUN_02020398
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011B08
_02011B1C:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02011B20
FUN_02011B20: ; 0x02011B20
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	ldr r0, [sp, #0x20]
	add r7, r1, #0x0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	ldrb r1, [r6, #0x7]
	str r0, [sp, #0x24]
	add r0, r3, #0x0
	add r0, r7, r0
	str r2, [sp, #0x0]
	str r3, [sp, #0x4]
	cmp r1, r0
	bge _02011B42
	bl ErrorHandling
_02011B42:
	ldrb r2, [r6, #0x8]
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r0, r1, r0
	cmp r2, r0
	bge _02011B52
	bl ErrorHandling
_02011B52:
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	cmp r0, #0x0
	ble _02011B8A
	lsl r0, r7, #0x5
	add r5, r4, #0x0
	str r0, [sp, #0x8]
_02011B60:
	ldrb r1, [r6, #0x7]
	ldr r0, [sp, #0x20]
	add r2, r1, #0x0
	add r0, r4, r0
	mul r2, r0
	ldr r0, [sp, #0x4]
	lsl r1, r5, #0x5
	add r2, r2, r0
	ldr r0, [sp, #0x24]
	lsl r2, r2, #0x5
	add r0, r0, r1
	ldr r1, [r6, #0xc]
	add r1, r1, r2
	ldr r2, [sp, #0x8]
	bl memcpy
	ldr r0, [sp, #0x0]
	add r4, r4, #0x1
	add r5, r5, r7
	cmp r4, r0
	blt _02011B60
_02011B8A:
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02011B90
FUN_02011B90: ; 0x02011B90
	mov r2, #0x14
	mov r1, #0x0
_02011B94:
	strb r1, [r0, #0x0]
	add r0, r0, #0x1
	sub r2, r2, #0x1
	bne _02011B94
	bx lr
	.balign 4

	thumb_func_start FUN_02011BA0
FUN_02011BA0: ; 0x02011BA0
	ldr r1, [r0, #0x64]
	mov r2, #0x0
	cmp r1, #0x0
	ble _02011BC4
	ldr r3, [r0, #0x60]
_02011BAA:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	bne _02011BBA
	ldr r1, [r0, #0x60]
	mov r0, #0x14
	mul r0, r2
	add r0, r1, r0
	bx lr
_02011BBA:
	ldr r1, [r0, #0x64]
	add r2, r2, #0x1
	add r3, #0x14
	cmp r2, r1
	blt _02011BAA
_02011BC4:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_02011BC8
FUN_02011BC8: ; 0x02011BC8
	push {r3-r4}
	ldr r4, _02011BF0 ; =UNK_020ED398
	mov r3, #0x0
_02011BCE:
	ldrb r2, [r4, #0x0]
	cmp r2, r0
	bgt _02011BE0
	ldrb r2, [r4, #0x1]
	cmp r2, r1
	bgt _02011BE0
	add r0, r3, #0x0
	pop {r3-r4}
	bx lr
_02011BE0:
	add r3, r3, #0x1
	add r4, r4, #0x2
	cmp r3, #0xc
	blt _02011BCE
	mov r0, #0xc
	pop {r3-r4}
	bx lr
	nop
_02011BF0: .word UNK_020ED398

	thumb_func_start FUN_02011BF4
FUN_02011BF4: ; 0x02011BF4
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	bl FUN_02011FAC
	ldr r1, [r6, #0x10]
	add r4, r0, #0x0
	bl FUN_02011FF4
	ldr r0, [r5, #0x8]
	ldr r1, [r5, #0xc]
	bl FUN_02011BC8
	str r0, [r4, #0x8]
	ldr r0, [r5, #0x4]
	ldr r1, _02011C9C ; =UNK_020ED398
	str r0, [r4, #0x0]
	ldr r0, [r5, #0x0]
	ldr r6, _02011CA0 ; =UNK_020ED399
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x8]
	ldr r2, [r5, #0x8]
	lsl r3, r0, #0x1
	ldrb r0, [r1, r3]
	ldrb r3, [r6, r3]
	sub r2, r2, r0
	ldr r0, [r5, #0xc]
	sub r6, r0, r3
	cmp r2, #0x0
	ble _02011C5C
	str r0, [r5, #0x1c]
	str r2, [r5, #0x18]
	ldr r0, [r5, #0x0]
	str r0, [r5, #0x10]
	ldr r2, [r4, #0x8]
	ldr r0, [r5, #0x4]
	lsl r2, r2, #0x1
	ldrb r1, [r1, r2]
	add r0, r0, r1
	str r0, [r5, #0x14]
	add r0, r5, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02011C54
	bl ErrorHandling
_02011C54:
	add r0, r5, #0x0
	mov r1, #0x1
	add r0, #0x20
	strb r1, [r0, #0x0]
_02011C5C:
	cmp r6, #0x0
	ble _02011C72
	ldr r0, [r4, #0x8]
	ldr r2, [r5, #0x0]
	lsl r1, r0, #0x1
	ldr r0, _02011CA0 ; =UNK_020ED399
	ldrb r0, [r0, r1]
	add r0, r2, r0
	str r0, [r5, #0x0]
	str r6, [r5, #0xc]
	b _02011C96
_02011C72:
	add r0, r5, #0x0
	add r0, #0x20
	ldrb r0, [r0, #0x0]
	cmp r0, #0x1
	bne _02011C92
	add r3, r5, #0x0
	add r3, #0x10
	add r2, r5, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r0, #0x0
	add r5, #0x20
	strb r0, [r5, #0x0]
	b _02011C96
_02011C92:
	mov r0, #0x1
	pop {r4-r6, pc}
_02011C96:
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_02011C9C: .word UNK_020ED398
_02011CA0: .word UNK_020ED399

	thumb_func_start FUN_02011CA4
FUN_02011CA4: ; 0x02011CA4
	push {r3-r7, lr}
	sub sp, #0x38
	add r7, r0, #0x0
	str r1, [sp, #0x0]
	add r5, r2, #0x0
	add r6, r3, #0x0
	cmp r7, #0x0
	bne _02011CB8
	bl ErrorHandling
_02011CB8:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02011CC2
	bl ErrorHandling
_02011CC2:
	ldr r0, [sp, #0x0]
	mov r4, #0x0
	str r0, [sp, #0x10]
	str r4, [sp, #0x4]
	str r4, [sp, #0x8]
	str r7, [sp, #0xc]
	add r0, sp, #0x24
	strb r4, [r0, #0x0]
	ldr r0, [sp, #0x0]
	str r4, [sp, #0x2c]
	str r7, [sp, #0x30]
	cmp r0, #0x0
	beq _02011D20
	add r7, sp, #0x4
_02011CDE:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x0]
	bl FUN_02011BC8
	lsl r1, r0, #0x1
	ldr r0, _02011D28 ; =UNK_020ED398
	add r0, r0, r1
	ldrb r0, [r0, #0x1]
	ldr r1, [sp, #0x4]
	add r1, r1, r0
	str r1, [sp, #0x28]
	ldr r1, [sp, #0x10]
	sub r1, r1, r0
	str r1, [sp, #0x34]
	str r0, [sp, #0x10]
_02011CFC:
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r4, r4, #0x1
	bl FUN_02011BF4
	cmp r0, #0x0
	beq _02011CFC
	add r3, sp, #0x28
	add r2, sp, #0x4
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02011CDE
_02011D20:
	add r0, r4, #0x0
	add sp, #0x38
	pop {r3-r7, pc}
	nop
_02011D28: .word UNK_020ED398

	thumb_func_start FUN_02011D2C
FUN_02011D2C: ; 0x02011D2C
	push {r4-r7, lr}
	sub sp, #0x1c
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x30]
	str r1, [sp, #0x14]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x34]
	add r5, r2, #0x0
	str r0, [sp, #0x34]
	ldr r0, [sp, #0x30]
	add r6, r3, #0x0
	cmp r0, #0x1
	bne _02011D4E
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	b _02011D52
_02011D4E:
	ldr r0, _02011D98 ; =0x04001000
	ldr r1, [r0, #0x0]
_02011D52:
	ldr r0, _02011D9C ; =0x00300010
	add r7, r1, #0x0
	and r7, r0
	add r0, r7, #0x0
	bl FUN_0201DED0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	ldr r4, [r0, #0xc]
	cmp r4, r0
	beq _02011D92
_02011D68:
	add r0, r5, #0x0
	bl FUN_020B1A24
	str r7, [sp, #0x0]
	ldr r0, [sp, #0x30]
	str r6, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x34]
	ldr r3, [sp, #0x18]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x10]
	add r1, r4, #0x0
	add r2, r5, #0x0
	bl FUN_02011DA0
	add r6, r0, #0x0
	ldr r4, [r4, #0xc]
	ldr r0, [sp, #0x14]
	add r5, #0x24
	cmp r4, r0
	bne _02011D68
_02011D92:
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02011D98: .word 0x04001000
_02011D9C: .word 0x00300010

	thumb_func_start FUN_02011DA0
FUN_02011DA0: ; 0x02011DA0
	push {r4-r7, lr}
	sub sp, #0x14
	add r6, r1, #0x0
	str r0, [sp, #0x8]
	ldr r0, [r6, #0x8]
	add r5, r2, #0x0
	lsl r1, r0, #0x1
	ldr r0, _02011E44 ; =UNK_020ED398
	ldrb r0, [r0, r1]
	str r0, [sp, #0x10]
	ldr r0, _02011E48 ; =UNK_020ED399
	ldrb r0, [r0, r1]
	ldr r1, [sp, #0x10]
	add r4, r1, #0x0
	mul r4, r0
	str r0, [sp, #0xc]
	cmp r4, r3
	bge _02011DC6
	add r4, r3, #0x0
_02011DC6:
	lsl r4, r4, #0x5
	ldr r0, [sp, #0x34]
	add r1, r4, #0x0
	bl FUN_020169D8
	add r7, r0, #0x0
	ldr r0, [r6, #0x4]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r3, [r6, #0x0]
	bl FUN_02011B20
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl DC_FlushRange
	ldr r0, [sp, #0x30]
	cmp r0, #0x1
	bne _02011E08
	ldr r6, [sp, #0x2c]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl GX_LoadOBJ
	mov r0, #0x1
	str r6, [r5, #0x4]
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	b _02011E1A
_02011E08:
	ldr r6, [sp, #0x2c]
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl GXS_LoadOBJ
	ldr r0, _02011E4C ; =0x04001000
	str r6, [r5, #0x8]
	ldr r1, [r0, #0x0]
_02011E1A:
	ldr r0, _02011E50 ; =0x00300010
	and r0, r1
	str r0, [r5, #0x20]
	ldr r0, _02011E54 ; =0x0000FFFF
	str r0, [r5, #0xc]
	str r0, [r5, #0x10]
	mov r0, #0x3
	str r0, [r5, #0x14]
	mov r0, #0x0
	str r0, [r5, #0x18]
	mov r0, #0x1
	str r0, [r5, #0x1c]
	ldr r0, [sp, #0x28]
	str r0, [r5, #0x20]
	add r0, r7, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x2c]
	add r0, r0, r4
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02011E44: .word UNK_020ED398
_02011E48: .word UNK_020ED399
_02011E4C: .word 0x04001000
_02011E50: .word 0x00300010
_02011E54: .word 0x0000FFFF

	thumb_func_start FUN_02011E58
FUN_02011E58: ; 0x02011E58
	push {r3-r7, lr}
	add r4, r0, #0x0
	cmp r1, #0x1
	bne _02011E68
	mov r0, #0x1
	lsl r0, r0, #0x1a
	ldr r1, [r0, #0x0]
	b _02011E6C
_02011E68:
	ldr r0, _02011EA0 ; =0x04001000
	ldr r1, [r0, #0x0]
_02011E6C:
	ldr r0, _02011EA4 ; =0x00300010
	and r0, r1
	bl FUN_0201DED0
	ldr r2, [r4, #0xc]
	mov r3, #0x0
	cmp r2, r4
	beq _02011E9A
	ldr r1, _02011EA8 ; =UNK_020ED398
_02011E7E:
	ldr r5, [r2, #0x8]
	lsl r5, r5, #0x1
	add r7, r1, r5
	ldrb r6, [r1, r5]
	ldrb r5, [r7, #0x1]
	mul r5, r6
	cmp r5, r0
	bge _02011E90
	add r5, r0, #0x0
_02011E90:
	ldr r2, [r2, #0xc]
	lsl r5, r5, #0x5
	add r3, r3, r5
	cmp r2, r4
	bne _02011E7E
_02011E9A:
	add r0, r3, #0x0
	pop {r3-r7, pc}
	nop
_02011EA0: .word 0x04001000
_02011EA4: .word 0x00300010
_02011EA8: .word UNK_020ED398

	thumb_func_start FUN_02011EAC
FUN_02011EAC: ; 0x02011EAC
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r0, r1, #0x0
	ldr r4, [r0, #0xc]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, r0
	beq _02011EFC
	mov r5, #0x0
_02011EC2:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r7, #0x0
	bl FUN_02011F24
	ldr r1, [r6, #0x0]
	str r0, [r1, r5]
	ldr r0, [r6, #0x0]
	ldr r0, [r0, r5]
	cmp r0, #0x0
	bne _02011EDC
	bl ErrorHandling
_02011EDC:
	ldr r0, [r4, #0x0]
	add r7, #0x24
	lsl r1, r0, #0x3
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x4]
	lsl r1, r0, #0x3
	ldr r0, [r6, #0x0]
	add r0, r0, r5
	str r1, [r0, #0x8]
	ldr r4, [r4, #0xc]
	ldr r0, [sp, #0x4]
	add r5, #0xc
	cmp r4, r0
	bne _02011EC2
_02011EFC:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02011F00
FUN_02011F00: ; 0x02011F00
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02011F20
	add r4, r6, #0x0
_02011F0E:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	bl FUN_0201FFC8
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02011F0E
_02011F20:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02011F24
FUN_02011F24: ; 0x02011F24
	push {r4-r5, lr}
	sub sp, #0x44
	add r5, r0, #0x0
	mov r0, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	add r4, r1, #0x0
	ldr r1, [r5, #0xc]
	str r1, [sp, #0x8]
	ldr r1, [r4, #0x8]
	ldr r2, [r5, #0x0]
	lsl r1, r1, #0x2
	add r1, r2, r1
	ldr r1, [r1, #0x30]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r2, [r5, #0x20]
	add r1, sp, #0x20
	strb r2, [r1, #0x0]
	ldr r1, [r5, #0x8]
	str r1, [sp, #0x24]
	add r1, sp, #0x0
	str r1, [sp, #0x28]
	ldr r1, [r5, #0x24]
	str r1, [sp, #0x38]
	ldr r1, [r5, #0x28]
	str r1, [sp, #0x3c]
	ldr r1, [r5, #0x2c]
	str r1, [sp, #0x40]
	str r0, [sp, #0x2c]
	str r0, [sp, #0x30]
	str r0, [sp, #0x34]
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _02011F80
	bl FUN_0202011C
	add r3, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, sp, #0x2c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
_02011F80:
	ldr r1, [r4, #0x0]
	ldr r2, [r5, #0x18]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldr r0, [sp, #0x2c]
	lsl r1, r1, #0xc
	add r0, r0, r1
	str r0, [sp, #0x2c]
	ldr r1, [r4, #0x4]
	ldr r2, [r5, #0x1c]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldr r0, [sp, #0x30]
	lsl r1, r1, #0xc
	add r0, r0, r1
	str r0, [sp, #0x30]
	add r0, sp, #0x24
	bl FUN_0201FF84
	add sp, #0x44
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02011FAC
FUN_02011FAC: ; 0x02011FAC
	push {r4, lr}
	mov r1, #0x14
	bl FUN_020169D8
	add r4, r0, #0x0
	bne _02011FBC
	bl ErrorHandling
_02011FBC:
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02011FC8
FUN_02011FC8: ; 0x02011FC8
	push {r4, lr}
	add r4, r0, #0x0
	bne _02011FD2
	bl ErrorHandling
_02011FD2:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02011FDC
FUN_02011FDC: ; 0x02011FDC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0xc]
	cmp r0, r5
	beq _02011FF2
_02011FE6:
	ldr r4, [r0, #0xc]
	bl FUN_02011FC8
	add r0, r4, #0x0
	cmp r4, r5
	bne _02011FE6
_02011FF2:
	pop {r3-r5, pc}

	thumb_func_start FUN_02011FF4
FUN_02011FF4: ; 0x02011FF4
	ldr r2, [r1, #0xc]
	str r2, [r0, #0xc]
	str r1, [r0, #0x10]
	ldr r2, [r1, #0xc]
	str r0, [r2, #0x10]
	str r0, [r1, #0xc]
	bx lr
	.balign 4

	thumb_func_start FUN_02012004
FUN_02012004: ; 0x02012004
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r6, [sp, #0x20]
	str r1, [sp, #0x4]
	add r5, r2, #0x0
	add r4, r3, #0x0
	str r0, [sp, #0x24]
	mov r7, #0x0
_02012018:
	ldr r1, [r4, #0x0]
	ldr r0, [sp, #0x4]
	ldr r2, [r5, #0x0]
	add r0, r0, r1
	ldr r1, [sp, #0x0]
	add r1, r1, r2
	add r2, r6, #0x0
	bl memcpy
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x24]
	add r7, r7, #0x1
	add r0, r1, r0
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, r6
	str r0, [r4, #0x0]
	cmp r7, #0x8
	blt _02012018
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02012044
FUN_02012044: ; 0x02012044
	push {r4-r6, lr}
	add r5, r3, #0x0
	bl LoadFromNarc_2
	add r4, r0, #0x0
	bne _02012054
	bl ErrorHandling
_02012054:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020B0088
	add r6, r0, #0x0
	cmp r5, #0x0
	bne _02012066
	bl ErrorHandling
_02012066:
	cmp r6, #0x0
	bne _0201206E
	bl ErrorHandling
_0201206E:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02012078
FUN_02012078: ; 0x02012078
	push {r4-r7, lr}
	sub sp, #0x2c
	ldr r4, [sp, #0x40]
	str r0, [sp, #0x8]
	add r6, r0, r2
	ldrh r0, [r4, #0x2]
	str r1, [sp, #0xc]
	add r5, r3, #0x0
	cmp r0, r6
	bge _02012090
	bl ErrorHandling
_02012090:
	ldr r0, [sp, #0xc]
	ldrh r1, [r4, #0x0]
	add r0, r0, r5
	str r0, [sp, #0x14]
	cmp r1, r0
	bge _020120A0
	bl ErrorHandling
_020120A0:
	ldr r0, [r4, #0x14]
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x1c]
	ldrh r0, [r4, #0x2]
	lsl r7, r0, #0x2
	ldr r0, [sp, #0xc]
	add r1, r0, #0x0
	mul r1, r7
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x18]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x18]
	str r1, [sp, #0x10]
	add r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bge _0201210A
_020120CC:
	ldr r4, [sp, #0x8]
	add r0, r4, #0x0
	cmp r0, r6
	bge _020120F8
	ldr r0, [sp, #0x18]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x10]
	add r5, r0, r1
_020120DC:
	str r5, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x1c]
	add r2, sp, #0x28
	add r3, sp, #0x24
	str r7, [sp, #0x4]
	bl FUN_02012004
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _020120DC
_020120F8:
	ldr r0, [sp, #0x18]
	add r0, r0, r7
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	add r1, r0, #0x1
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	cmp r1, r0
	blt _020120CC
_0201210A:
	add sp, #0x2c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02012110
FUN_02012110: ; 0x02012110
	push {r4-r5}
	sub sp, #0x8
	ldr r2, _02012148 ; =UNK_020ED3B0
	add r1, sp, #0x0
	ldr r3, [r2, #0x0]
	ldr r2, [r2, #0x4]
	str r3, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r2, _0201214C ; =0x000001EF
	mov r5, #0x0
	add r3, r2, #0x0
_02012126:
	ldr r4, [r1, #0x0]
	cmp r4, r3
	beq _02012140
	cmp r4, r0
	bne _02012138
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02012138:
	add r5, r5, #0x1
	add r1, r1, #0x4
	cmp r5, r2
	blt _02012126
_02012140:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r5}
	bx lr
	.balign 4
_02012148: .word UNK_020ED3B0
_0201214C: .word 0x000001EF

	thumb_func_start FUN_02012150
FUN_02012150: ; 0x02012150
	push {r3-r4, lr}
	sub sp, #0xc
	add r4, r3, #0x0
	mov r3, #0x0
	str r3, [sp, #0x8]
	add r3, sp, #0x8
	bl FUN_02012044
	ldr r0, [sp, #0x8]
	ldr r0, [r0, #0x14]
	bl FUN_02008A74
	ldr r0, [sp, #0x34]
	bl FUN_02012110
	ldr r1, [sp, #0x30]
	cmp r1, #0x2
	bne _02012184
	cmp r0, #0x1
	bne _02012184
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x28]
	ldr r0, [r0, #0x14]
	ldr r2, [sp, #0x2c]
	bl FUN_02008904
_02012184:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x18]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x24]
	ldr r2, [sp, #0x1c]
	str r0, [sp, #0x4]
	ldr r3, [sp, #0x20]
	add r0, r4, #0x0
	bl FUN_02012078
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0201219C
FUN_0201219C: ; 0x0201219C
	push {r4-r7, lr}
	sub sp, #0x24
	add r7, r1, #0x0
	add r5, r2, #0x0
	ldr r2, [sp, #0x3c]
	ldr r1, [sp, #0x40]
	add r6, r0, #0x0
	mul r1, r2
	add r0, r5, #0x0
	lsl r1, r1, #0x5
	str r3, [sp, #0x20]
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0x38]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x3c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x40]
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x44]
	str r4, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4c]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x50]
	str r0, [sp, #0x1c]
	add r0, r6, #0x0
	bl FUN_02012150
	add r0, r4, #0x0
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_020121E8
FUN_020121E8: ; 0x020121E8
	push {r3-r7, lr}
	sub sp, #0x30
	str r3, [sp, #0x8]
	ldr r3, [sp, #0x48]
	str r3, [sp, #0x48]
	mov r3, #0x0
	str r3, [sp, #0x2c]
	bl LoadFromNarc_2
	str r0, [sp, #0x20]
	cmp r0, #0x0
	bne _02012204
	bl ErrorHandling
_02012204:
	ldr r0, [sp, #0x20]
	add r1, sp, #0x2c
	bl FUN_020B0088
	cmp r0, #0x0
	bne _02012214
	bl ErrorHandling
_02012214:
	ldr r1, [sp, #0x4c]
	ldr r0, [sp, #0x8]
	add r6, r0, r1
	ldr r0, [sp, #0x2c]
	ldrh r0, [r0, #0x2]
	cmp r0, r6
	bge _02012226
	bl ErrorHandling
_02012226:
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x48]
	add r0, r0, r1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x2c]
	ldrh r1, [r0, #0x0]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bge _0201223C
	bl ErrorHandling
_0201223C:
	ldr r0, [sp, #0x2c]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x1c]
	bl FUN_02008A74
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x2c]
	ldrh r0, [r0, #0x2]
	lsl r7, r0, #0x2
	ldr r0, [sp, #0x48]
	add r1, r0, #0x0
	mul r1, r7
	ldr r0, [sp, #0x8]
	str r1, [sp, #0x14]
	lsl r1, r0, #0x2
	ldr r0, [sp, #0x14]
	str r1, [sp, #0xc]
	add r0, r1, r0
	str r0, [sp, #0x28]
	mov r0, #0x0
	str r0, [sp, #0x24]
	ldr r1, [sp, #0x48]
	ldr r0, [sp, #0x10]
	cmp r1, r0
	bge _020122AE
_02012270:
	ldr r4, [sp, #0x8]
	add r0, r4, #0x0
	cmp r0, r6
	bge _0201229C
	ldr r0, [sp, #0x14]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0xc]
	add r5, r0, r1
_02012280:
	str r5, [sp, #0x28]
	mov r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x1c]
	ldr r1, [sp, #0x18]
	add r2, sp, #0x28
	add r3, sp, #0x24
	str r7, [sp, #0x4]
	bl FUN_02012004
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, r6
	blt _02012280
_0201229C:
	ldr r0, [sp, #0x14]
	add r0, r0, r7
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x48]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x48]
	cmp r1, r0
	blt _02012270
_020122AE:
	ldr r0, [sp, #0x20]
	bl FUN_02016A18
	add sp, #0x30
	pop {r3-r7, pc}

	thumb_func_start FUN_020122B8
FUN_020122B8: ; 0x020122B8
	push {r4-r7, lr}
	sub sp, #0x14
	add r7, r1, #0x0
	add r5, r2, #0x0
	ldr r2, [sp, #0x2c]
	ldr r1, [sp, #0x30]
	add r6, r0, #0x0
	mul r1, r2
	add r0, r5, #0x0
	lsl r1, r1, #0x5
	str r3, [sp, #0x10]
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [sp, #0x28]
	ldr r3, [sp, #0x10]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x2c]
	add r1, r7, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x30]
	add r2, r5, #0x0
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	str r4, [sp, #0xc]
	bl FUN_020121E8
	add r0, r4, #0x0
	add sp, #0x14
	pop {r4-r7, pc}

	thumb_func_start FUN_020122F4
FUN_020122F4: ; 0x020122F4
	push {r3-r7, lr}
	sub sp, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x38]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x4]
	str r0, [sp, #0x14]
	add r0, r2, #0x0
	add r7, r0, r1
	ldr r1, [sp, #0x3c]
	add r0, r3, #0x0
	add r0, r0, r1
	add r1, r3, #0x0
	str r3, [sp, #0x8]
	ldr r5, [sp, #0x40]
	str r0, [sp, #0x10]
	cmp r1, r0
	bge _0201236C
	add r0, r3, #0x0
	lsl r0, r0, #0x5
	str r0, [sp, #0xc]
	add r0, r2, #0x0
	lsl r0, r0, #0x5
	str r0, [sp, #0x1c]
_02012328:
	ldr r6, [sp, #0x4]
	add r0, r6, #0x0
	cmp r0, r7
	bge _0201235A
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0xc]
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [sp, #0x1c]
	add r4, r0, r2
_0201233C:
	ldr r1, [r5, #0x0]
	ldr r0, [sp, #0x14]
	mov r2, #0x20
	add r0, r0, r1
	ldr r1, [sp, #0x18]
	add r1, r1, r4
	bl memcpy
	ldr r0, [r5, #0x0]
	add r6, r6, #0x1
	add r0, #0x20
	str r0, [r5, #0x0]
	add r4, #0x20
	cmp r6, r7
	blt _0201233C
_0201235A:
	ldr r0, [sp, #0xc]
	add r0, #0x20
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r1, r0, #0x1
	ldr r0, [sp, #0x10]
	str r1, [sp, #0x8]
	cmp r1, r0
	blt _02012328
_0201236C:
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02012370
FUN_02012370: ; 0x02012370
	push {r3-r4, lr}
	sub sp, #0x14
	add r4, r2, #0x0
	ldr r2, [r4, #0x8]
	str r2, [sp, #0x0]
	ldr r2, [r4, #0xc]
	str r2, [sp, #0x4]
	ldr r2, [sp, #0x20]
	str r3, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r2, [sp, #0x24]
	str r2, [sp, #0x10]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x4]
	bl FUN_020122F4
	add sp, #0x14
	pop {r3-r4, pc}

	thumb_func_start FUN_02012394
FUN_02012394: ; 0x02012394
	push {r4-r7, lr}
	sub sp, #0x7c
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x9c]
	mov r12, r3
	add r5, r2, #0x0
	ldr r6, [sp, #0x94]
	ldr r7, [sp, #0x98]
	ldr r3, _020123FC ; =UNK_020ED3D8
	str r1, [sp, #0x10]
	str r0, [sp, #0x9c]
	add r2, sp, #0x1c
	mov r4, #0xc
_020123AE:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r4, r4, #0x1
	bne _020123AE
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x90]
	ldr r1, [sp, #0x10]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xc]
	add r2, r5, #0x0
	mov r3, r12
	str r7, [sp, #0x8]
	bl FUN_020122B8
	str r0, [sp, #0x14]
	mov r4, #0x0
	add r5, sp, #0x1c
_020123D4:
	ldr r0, [sp, #0x14]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x9c]
	add r2, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r3, sp, #0x18
	bl FUN_02012370
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x6
	blt _020123D4
	ldr r0, [sp, #0x14]
	bl FUN_02016A18
	add sp, #0x7c
	pop {r4-r7, pc}
	nop
_020123FC: .word UNK_020ED3D8

	thumb_func_start FUN_02012400
FUN_02012400: ; 0x02012400
	push {r4, lr}
	sub sp, #0x10
	ldr r4, [r3, #0x4]
	str r4, [sp, #0x0]
	ldr r4, [r3, #0x8]
	str r4, [sp, #0x4]
	ldr r4, [r3, #0xc]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x18]
	str r4, [sp, #0xc]
	ldr r3, [r3, #0x0]
	bl FUN_02012394
	add sp, #0x10
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012420
FUN_02012420: ; 0x02012420
	push {r4-r7, lr}
	sub sp, #0x14
	ldr r4, _02012448 ; =UNK_020ED3B8
	add r5, r3, #0x0
	add r3, sp, #0x4
	add r7, r0, #0x0
	mov r12, r1
	add r6, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r7, #0x0
	mov r1, r12
	add r3, r6, #0x0
	str r5, [sp, #0x0]
	bl FUN_02012400
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02012448: .word UNK_020ED3B8

	thumb_func_start FUN_0201244C
FUN_0201244C: ; 0x0201244C
	push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x32
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r0, r7, #0x0
	lsl r1, r1, #0x6
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	add r3, r4, #0x0
	bl FUN_02012420
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02012470
FUN_02012470: ; 0x02012470
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r7, #0x0
	mov r1, #0x20
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl LoadFromNarc_2
	add r1, sp, #0x0
	add r5, r0, #0x0
	bl FUN_020B0138
	cmp r0, #0x1
	beq _0201249C
	bl ErrorHandling
_0201249C:
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	mov r2, #0x20
	bl MIi_CpuCopy16
	add r0, r5, #0x0
	bl FUN_02016A18
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020124B4
FUN_020124B4: ; 0x020124B4
	push {r4-r7, lr}
	sub sp, #0x8c
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0xac]
	mov r12, r3
	add r5, r2, #0x0
	ldr r6, [sp, #0xa4]
	ldr r7, [sp, #0xa8]
	ldr r3, _0201252C ; =UNK_020ED438
	str r1, [sp, #0x20]
	str r0, [sp, #0xac]
	add r2, sp, #0x2c
	mov r4, #0xc
_020124CE:
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	sub r4, r4, #0x1
	bne _020124CE
	mov r0, #0x0
	str r0, [sp, #0x28]
	ldr r0, [sp, #0xa0]
	ldr r1, [sp, #0x20]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0xb0]
	str r7, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0xb4]
	add r2, r5, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xb8]
	mov r3, r12
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xbc]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	bl FUN_0201219C
	str r0, [sp, #0x24]
	mov r4, #0x0
	add r5, sp, #0x2c
_02012504:
	ldr r0, [sp, #0x24]
	add r1, r7, #0x0
	str r0, [sp, #0x0]
	ldr r0, [sp, #0xac]
	add r2, r5, #0x0
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r3, sp, #0x28
	bl FUN_02012370
	add r4, r4, #0x1
	add r5, #0x10
	cmp r4, #0x6
	blt _02012504
	ldr r0, [sp, #0x24]
	bl FUN_02016A18
	add sp, #0x8c
	pop {r4-r7, pc}
	nop
_0201252C: .word UNK_020ED438

	thumb_func_start FUN_02012530
FUN_02012530: ; 0x02012530
	push {r4, lr}
	sub sp, #0x20
	ldr r4, [r3, #0x4]
	str r4, [sp, #0x0]
	ldr r4, [r3, #0x8]
	str r4, [sp, #0x4]
	ldr r4, [r3, #0xc]
	str r4, [sp, #0x8]
	ldr r4, [sp, #0x28]
	str r4, [sp, #0xc]
	ldr r4, [sp, #0x2c]
	str r4, [sp, #0x10]
	ldr r4, [sp, #0x30]
	str r4, [sp, #0x14]
	ldr r4, [sp, #0x34]
	str r4, [sp, #0x18]
	ldr r4, [sp, #0x38]
	str r4, [sp, #0x1c]
	ldr r3, [r3, #0x0]
	bl FUN_020124B4
	add sp, #0x20
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012560
FUN_02012560: ; 0x02012560
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r4, _02012598 ; =UNK_020ED3C8
	add r5, r3, #0x0
	add r3, sp, #0x14
	add r7, r0, #0x0
	mov r12, r1
	add r6, r3, #0x0
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [sp, #0x38]
	str r5, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	mov r1, r12
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r3, r6, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x10]
	add r0, r7, #0x0
	bl FUN_02012530
	add sp, #0x24
	pop {r4-r7, pc}
	.balign 4
_02012598: .word UNK_020ED3C8

	thumb_func_start FUN_0201259C
FUN_0201259C: ; 0x0201259C
	push {r3, lr}
	bl RTC_Init
	ldr r3, _020125CC ; =UNK_021C4808
	mov r0, #0x0
	add r2, r3, #0x0
	add r1, r0, #0x0
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r1, _020125D0 ; =UNK_021C4808
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	str r0, [r1, #0x8]
	add r0, r3, #0x0
	bl FUN_02012634
	pop {r3, pc}
	.balign 4
_020125CC: .word UNK_021C4808
_020125D0: .word UNK_021C4808

	thumb_func_start FUN_020125D4
FUN_020125D4: ; 0x020125D4
	push {r3, lr}
	ldr r0, _020125F4 ; =UNK_021C4808
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	bne _020125F2
	ldr r1, [r0, #0x8]
	add r1, r1, #0x1
	str r1, [r0, #0x8]
	cmp r1, #0xa
	ble _020125F2
	mov r1, #0x0
	str r1, [r0, #0x8]
	ldr r0, _020125F8 ; =UNK_021C4808
	bl FUN_02012634
_020125F2:
	pop {r3, pc}
	.balign 4
_020125F4: .word UNK_021C4808
_020125F8: .word UNK_021C4808

	thumb_func_start FUN_020125FC
FUN_020125FC: ; 0x020125FC
	push {r4, lr}
	add r4, r1, #0x0
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _0201260A
	bl ErrorHandling
_0201260A:
	add r3, r4, #0x0
	mov r0, #0x1
	add r2, r4, #0x0
	add r3, #0x2c
	str r0, [r4, #0x0]
	ldmia r3!, {r0-r1}
	add r2, #0x10
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	add r3, r4, #0x0
	add r3, #0x3c
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	pop {r4, pc}

	thumb_func_start FUN_02012634
FUN_02012634: ; 0x02012634
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x1
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	add r1, r4, #0x0
	ldr r2, _02012658 ; =FUN_020125FC
	add r0, #0x2c
	add r1, #0x3c
	add r3, r4, #0x0
	bl RTC_GetDateTimeAsync
	str r0, [r4, #0xc]
	cmp r0, #0x0
	beq _02012656
	bl ErrorHandling
_02012656:
	pop {r4, pc}
	.balign 4
_02012658: .word FUN_020125FC

	thumb_func_start FUN_0201265C
FUN_0201265C: ; 0x0201265C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _02012684 ; =UNK_021C4808
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _0201266E
	bl ErrorHandling
_0201266E:
	ldr r2, _02012688 ; =UNK_021C4818
	ldmia r2!, {r0-r1}
	stmia r5!, {r0-r1}
	ldmia r2!, {r0-r1}
	ldr r2, _0201268C ; =UNK_021C4828
	stmia r5!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r5, pc}
	.balign 4
_02012684: .word UNK_021C4808
_02012688: .word UNK_021C4818
_0201268C: .word UNK_021C4828

	thumb_func_start FUN_02012690
FUN_02012690: ; 0x02012690
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020126AC ; =UNK_021C4808
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020126A0
	bl ErrorHandling
_020126A0:
	ldr r2, _020126B0 ; =UNK_021C4828
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4
_020126AC: .word UNK_021C4808
_020126B0: .word UNK_021C4828

	thumb_func_start FUN_020126B4
FUN_020126B4: ; 0x020126B4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _020126D0 ; =UNK_021C4808
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	beq _020126C4
	bl ErrorHandling
_020126C4:
	ldr r2, _020126D4 ; =UNK_021C4818
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	ldmia r2!, {r0-r1}
	stmia r4!, {r0-r1}
	pop {r4, pc}
	.balign 4
_020126D0: .word UNK_021C4808
_020126D4: .word UNK_021C4818

	thumb_func_start FUN_020126D8
FUN_020126D8: ; 0x020126D8
	push {r3-r4}
	ldr r4, _020126F8 ; =UNK_021C4828
	mov r0, #0x3c
	ldr r1, [r4, #0x4]
	ldr r3, [r4, #0x8]
	add r2, r1, #0x0
	mul r2, r0
	mov r0, #0xe1
	ldr r1, [r4, #0x0]
	lsl r0, r0, #0x4
	mul r0, r1
	add r0, r2, r0
	add r0, r3, r0
	pop {r3-r4}
	bx lr
	nop
_020126F8: .word UNK_021C4828

	thumb_func_start FUN_020126FC
FUN_020126FC: ; 0x020126FC
	ldr r3, _02012704 ; =RTC_ConvertDateTimeToSecond
	ldr r0, _02012708 ; =UNK_021C4818
	ldr r1, _0201270C ; =UNK_021C4828
	bx r3
	.balign 4
_02012704: .word RTC_ConvertDateTimeToSecond
_02012708: .word UNK_021C4818
_0201270C: .word UNK_021C4828

	thumb_func_start FUN_02012710
FUN_02012710: ; 0x02012710
	push {r4-r6, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	ldr r2, [r5, #0x4]
	ldr r0, _02012778 ; =UNK_020ED4B2
	lsl r1, r2, #0x1
	ldrh r0, [r0, r1]
	ldr r3, [r5, #0x8]
	add r4, r3, r0
	cmp r2, #0x3
	blo _02012752
	ldr r6, [r5, #0x0]
	mov r0, #0x1e
	lsr r2, r6, #0x1f
	lsl r1, r6, #0x1e
	sub r1, r1, r2
	ror r1, r0
	add r0, r2, r1
	bne _02012742
	add r0, r6, #0x0
	mov r1, #0x64
	bl _s32_div_f
	cmp r1, #0x0
	bne _02012750
_02012742:
	mov r1, #0x19
	add r0, r6, #0x0
	lsl r1, r1, #0x4
	bl _s32_div_f
	cmp r1, #0x0
	bne _02012752
_02012750:
	add r4, r4, #0x1
_02012752:
	add r6, r5, #0x0
	add r3, sp, #0x0
	add r2, r3, #0x0
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r6!, {r0-r1}
	stmia r3!, {r0-r1}
	mov r0, #0x1
	str r0, [sp, #0x4]
	str r0, [sp, #0x8]
	add r0, r2, #0x0
	bl RTC_ConvertDateToDay
	add r0, r5, #0x0
	bl RTC_ConvertDateToDay
	add r0, r4, #0x0
	add sp, #0x10
	pop {r4-r6, pc}
	.balign 4
_02012778: .word UNK_020ED4B2

	thumb_func_start FUN_0201277C
FUN_0201277C: ; 0x0201277C
	push {r3, lr}
	bl FUN_02012794
	cmp r0, #0x3
	beq _0201278A
	cmp r0, #0x4
	bne _0201278E
_0201278A:
	mov r0, #0x1
	pop {r3, pc}
_0201278E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02012794
FUN_02012794: ; 0x02012794
	push {lr}
	sub sp, #0xc
	add r0, sp, #0x0
	bl FUN_02012690
	ldr r0, [sp, #0x0]
	bl FUN_020127A8
	add sp, #0xc
	pop {pc}

	thumb_func_start FUN_020127A8
FUN_020127A8: ; 0x020127A8
	push {r4, lr}
	add r4, r0, #0x0
	bmi _020127B2
	cmp r4, #0x18
	blt _020127B6
_020127B2:
	bl ErrorHandling
_020127B6:
	ldr r0, _020127BC ; =UNK_020ED4CC
	ldrb r0, [r0, r4]
	pop {r4, pc}
	.balign 4
_020127BC: .word UNK_020ED4CC

	thumb_func_start FUN_020127C0
FUN_020127C0: ; 0x020127C0
	push {r4-r7, lr}
	sub sp, #0x24
	add r6, r3, #0x0
	ldr r3, _0201282C ; =UNK_020ED4A4
	add r4, r0, #0x0
	add r7, r1, #0x0
	add r5, r2, #0x0
	add r2, sp, #0x14
	ldmia r3!, {r0-r1}
	str r2, [sp, #0x0]
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r3, _02012830 ; =UNK_020ED498
	add r2, sp, #0x8
	ldmia r3!, {r0-r1}
	str r2, [sp, #0x4]
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	ldr r1, [sp, #0x4]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x0]
	bl RTC_ConvertDateTimeToSecond
	add r2, r1, #0x0
	add r3, r0, #0x0
	mov r1, #0x0
	ldr r0, _02012834 ; =0xBC19137F
	eor r1, r2
	eor r0, r3
	orr r0, r1
	beq _02012804
	bl ErrorHandling
_02012804:
	sub r0, r4, r5
	mov r12, r7
	mov r0, r12
	sbc r0, r6
	bge _02012818
	sub r0, r5, r4
	sbc r6, r7
	add sp, #0x24
	add r1, r6, #0x0
	pop {r4-r7, pc}
_02012818:
	ldr r0, _02012834 ; =0xBC19137F
	mov r1, #0x0
	sub r0, r0, r4
	sbc r1, r7
	add r0, r5, r0
	adc r6, r1
	add r1, r6, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0201282C: .word UNK_020ED4A4
_02012830: .word UNK_020ED498
_02012834: .word 0xBC19137F

	thumb_func_start FUN_02012838
FUN_02012838: ; 0x02012838
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x3
	bl FUN_02016998
	cmp r0, #0x0
	beq _0201286E
	mov r2, #0x0
	cmp r5, #0x0
	bls _02012862
	add r3, r0, #0x0
	add r1, r2, #0x0
_02012856:
	str r1, [r3, #0x0]
	str r1, [r3, #0x4]
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, r5
	blo _02012856
_02012862:
	mov r1, #0x0
	lsl r2, r2, #0x3
	mvn r1, r1
	str r1, [r0, r2]
	add r1, r0, r2
	str r4, [r1, #0x4]
_0201286E:
	pop {r3-r5, pc}

	thumb_func_start FUN_02012870
FUN_02012870: ; 0x02012870
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201291C
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}

	thumb_func_start FUN_02012880
FUN_02012880: ; 0x02012880
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r1, sp, #0x0
	add r7, r2, #0x0
	add r5, r3, #0x0
	bl FUN_020128E0
	add r4, r0, #0x0
	beq _0201289E
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_0200A914
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
_0201289E:
	pop {r3-r7, pc}

	thumb_func_start FUN_020128A0
FUN_020128A0: ; 0x020128A0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r1, #0x0
	add r1, sp, #0x0
	add r5, r2, #0x0
	bl FUN_020128E0
	add r4, r0, #0x0
	beq _020128BE
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl FUN_02021ACC
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
_020128BE:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_020128C4
FUN_020128C4: ; 0x020128C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	add r1, sp, #0x0
	bl FUN_020128E0
	cmp r0, #0x0
	beq _020128DC
	ldr r1, [r4, #0x0]
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x4]
	str r1, [r0, #0x4]
_020128DC:
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020128E0
FUN_020128E0: ; 0x020128E0
	push {r4, lr}
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _02012900
	mov r2, #0x0
	mvn r2, r2
_020128EC:
	cmp r3, r2
	bne _020128F8
	bl ErrorHandling
	mov r0, #0x0
	pop {r4, pc}
_020128F8:
	add r0, #0x8
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	bne _020128EC
_02012900:
	mov r2, #0x0
	mvn r2, r2
	add r4, r0, #0x0
	cmp r3, r2
	beq _02012912
_0201290A:
	add r0, #0x8
	ldr r3, [r0, #0x0]
	cmp r3, r2
	bne _0201290A
_02012912:
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201291C
FUN_0201291C: ; 0x0201291C
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	ldr r1, [r5, #0x0]
	mvn r0, r0
	cmp r1, r0
	beq _02012942
	mov r4, #0x0
	add r6, r0, #0x0
_0201292E:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02012942
	bl FUN_02021A20
	str r4, [r5, #0x0]
	add r5, #0x8
	ldr r0, [r5, #0x0]
	cmp r0, r6
	bne _0201292E
_02012942:
	pop {r4-r6, pc}

	thumb_func_start FUN_02012944
FUN_02012944: ; 0x02012944
	push {r3-r5, lr}
	add r5, r1, #0x0
	mov r1, #0xc
	add r4, r2, #0x0
	bl FUN_02016998
	mov r1, #0x0
	strb r1, [r0, #0x0]
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x2]
	strb r1, [r0, #0x3]
	strb r1, [r0, #0x4]
	strb r1, [r0, #0x5]
	strb r1, [r0, #0x6]
	strb r1, [r0, #0x7]
	strb r1, [r0, #0x8]
	strb r1, [r0, #0x9]
	strb r1, [r0, #0xa]
	strb r1, [r0, #0xb]
	mov r1, #0x1
	strb r1, [r0, #0x9]
	str r5, [r0, #0x0]
	str r4, [r0, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_02012974
FUN_02012974: ; 0x02012974
	push {r4, lr}
	add r4, r0, #0x0
	bne _0201297E
	bl ErrorHandling
_0201297E:
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012988
FUN_02012988: ; 0x02012988
	push {r4, lr}
	add r4, r0, #0x0
	bne _02012992
	bl ErrorHandling
_02012992:
	ldrb r0, [r4, #0x8]
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201299C
FUN_0201299C: ; 0x0201299C
	push {r4, lr}
	add r4, r0, #0x0
	bne _020129A6
	bl ErrorHandling
_020129A6:
	ldrb r1, [r4, #0x8]
	mov r0, #0x1
	eor r0, r1
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020129B4
FUN_020129B4: ; 0x020129B4
	cmp r0, #0x0
	beq _020129C6
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _020129C6
	ldrb r2, [r0, #0x8]
	mov r1, #0x1
	eor r1, r2
	strb r1, [r0, #0x8]
_020129C6:
	bx lr

	thumb_func_start FUN_020129C8
FUN_020129C8: ; 0x020129C8
	push {r3, lr}
	mov r0, #0x0
	bl MI_StopDma
	mov r0, #0x0
	bl MI_WaitDma
	pop {r3, pc}

	thumb_func_start FUN_020129D8
FUN_020129D8: ; 0x020129D8
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r4, r2, #0x0
	cmp r3, #0x1
	bne _020129F2
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl MI_HBlankDmaCopy32
	pop {r4-r6, pc}
_020129F2:
	mov r0, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	add r3, r4, #0x0
	bl MI_HBlankDmaCopy16
	pop {r4-r6, pc}

	thumb_func_start FUN_02012A00
FUN_02012A00: ; 0x02012A00
	push {r3-r5, lr}
	ldr r1, _02012A2C ; =0x0000079C
	add r5, r0, #0x0
	bl FUN_02016998
	ldr r2, _02012A2C ; =0x0000079C
	mov r1, #0x0
	add r4, r0, #0x0
	bl memset
	mov r2, #0x3
	lsl r2, r2, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r4, r2
	bl FUN_02012944
	mov r1, #0x6
	lsl r1, r1, #0x8
	str r0, [r4, r1]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02012A2C: .word 0x0000079C

	thumb_func_start FUN_02012A30
FUN_02012A30: ; 0x02012A30
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r5, #0x0
	bne _02012A42
	bl ErrorHandling
_02012A42:
	ldr r0, _02012AB0 ; =0x00000604
	ldr r0, [r5, r0]
	cmp r0, #0x0
	beq _02012A4E
	bl ErrorHandling
_02012A4E:
	ldr r0, _02012AB4 ; =0x0000078C
	mov r2, #0x0
	strb r4, [r5, r0]
	add r1, r0, #0x1
	strb r6, [r5, r1]
	add r1, r0, #0x0
	add r1, #0xc
	strh r2, [r5, r1]
	add r2, sp, #0x8
	mov r1, #0x14
	ldrsh r2, [r2, r1]
	add r1, r0, #0x0
	add r1, #0xe
	strh r2, [r5, r1]
	add r1, r0, #0x4
	ldr r2, [sp, #0x20]
	add r0, #0x8
	str r2, [r5, r1]
	ldr r1, [sp, #0x24]
	ldr r3, [sp, #0x18]
	str r1, [r5, r0]
	ldr r0, _02012AB8 ; =0x0000060C
	mov r1, #0xc0
	add r0, r5, r0
	add r2, r7, #0x0
	bl FUN_02012B88
	ldr r0, _02012ABC ; =FUN_02012BE4
	ldr r2, [sp, #0x28]
	add r1, r5, #0x0
	bl FUN_0200CA44
	ldr r1, _02012AB0 ; =0x00000604
	mov r2, #0x3
	str r0, [r5, r1]
	ldr r0, _02012AC0 ; =0x00000794
	add r1, r5, #0x0
	ldr r0, [r5, r0]
	lsl r2, r2, #0x8
	bl MIi_CpuClear32
	ldr r0, _02012AC0 ; =0x00000794
	mov r2, #0x3
	lsl r2, r2, #0x8
	ldr r0, [r5, r0]
	add r1, r5, r2
	bl MIi_CpuClear32
	pop {r3-r7, pc}
	.balign 4
_02012AB0: .word 0x00000604
_02012AB4: .word 0x0000078C
_02012AB8: .word 0x0000060C
_02012ABC: .word FUN_02012BE4
_02012AC0: .word 0x00000794

	thumb_func_start FUN_02012AC4
FUN_02012AC4: ; 0x02012AC4
	push {r4, lr}
	add r4, r0, #0x0
	bne _02012ACE
	bl ErrorHandling
_02012ACE:
	ldr r0, _02012AF8 ; =0x00000604
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02012AF4
	bl FUN_0200CAB4
	ldr r0, _02012AF8 ; =0x00000604
	mov r1, #0x0
	str r1, [r4, r0]
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_02012988
	ldr r1, _02012AFC ; =0x00000794
	mov r2, #0x3
	ldr r1, [r4, r1]
	lsl r2, r2, #0x8
	bl memset
_02012AF4:
	pop {r4, pc}
	nop
_02012AF8: .word 0x00000604
_02012AFC: .word 0x00000794

	thumb_func_start FUN_02012B00
FUN_02012B00: ; 0x02012B00
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02012AC4
	bl FUN_02012C90
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl FUN_02012974
	add r0, r4, #0x0
	bl FUN_02016A18
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02012B20
FUN_02012B20: ; 0x02012B20
	mov r1, #0x6
	lsl r1, r1, #0x8
	ldr r3, _02012B2C ; =FUN_02012988
	ldr r0, [r0, r1]
	bx r3
	nop
_02012B2C: .word FUN_02012988

	thumb_func_start FUN_02012B30
FUN_02012B30: ; 0x02012B30
	push {r4, lr}
	add r4, r0, #0x0
	beq _02012B5E
	ldr r0, _02012B60 ; =0x00000604
	ldr r1, [r4, r0]
	cmp r1, #0x0
	beq _02012B5E
	sub r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FUN_020129B4
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl FUN_02012988
	add r1, r0, #0x0
	ldr r0, _02012B64 ; =0x00000794
	mov r2, #0x3
	ldr r0, [r4, r0]
	lsl r2, r2, #0x8
	bl MIi_CpuClear32
_02012B5E:
	pop {r4, pc}
	.balign 4
_02012B60: .word 0x00000604
_02012B64: .word 0x00000794

	thumb_func_start FUN_02012B68
FUN_02012B68: ; 0x02012B68
	push {r4, lr}
	add r4, r0, #0x0
	beq _02012B80
	ldr r0, _02012B84 ; =0x00000604
	ldr r0, [r4, r0]
	cmp r0, #0x0
	beq _02012B80
	bl FUN_02012C90
	add r0, r4, #0x0
	bl FUN_02012C98
_02012B80:
	pop {r4, pc}
	nop
_02012B84: .word 0x00000604

	thumb_func_start FUN_02012B88
FUN_02012B88: ; 0x02012B88
	push {r4-r7, lr}
	sub sp, #0xc
	mov r4, #0x0
	add r7, r1, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	str r2, [sp, #0x0]
	cmp r7, #0x0
	bls _02012BD6
	asr r0, r3, #0x1f
	str r3, [sp, #0x4]
	str r0, [sp, #0x8]
_02012BA0:
	asr r0, r4, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02012BDC ; =UNK_020FFA38
	ldr r2, [sp, #0x4]
	ldrsh r0, [r0, r1]
	ldr r3, [sp, #0x8]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _02012BE0 ; =0x00000000
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	asr r0, r0, #0xc
	strh r0, [r5, #0x0]
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r0, r4, r0
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r5, r5, #0x2
	cmp r6, r7
	blo _02012BA0
_02012BD6:
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02012BDC: .word UNK_020FFA38
_02012BE0: .word 0x00000000

	thumb_func_start FUN_02012BE4
FUN_02012BE4: ; 0x02012BE4
	push {r3-r7, lr}
	mov r0, #0x6
	add r6, r1, #0x0
	lsl r0, r0, #0x8
	ldr r0, [r6, r0]
	bl FUN_02012988
	add r5, r0, #0x0
	ldr r0, _02012C80 ; =0x00000798
	mov r1, #0x64
	ldrsh r0, [r6, r0]
	bl _s32_div_f
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	ldr r0, _02012C84 ; =0x0000078C
	ldrb r4, [r6, r0]
	add r0, r0, #0x1
	ldrb r0, [r6, r0]
	cmp r4, r0
	bgt _02012C4C
	lsl r0, r4, #0x2
	add r5, r5, r0
_02012C12:
	ldr r2, [r5, #0x0]
	lsl r0, r2, #0x10
	asr r7, r0, #0x10
	lsl r0, r3, #0x1
	add r1, r6, r0
	ldr r0, _02012C88 ; =0x0000060C
	ldrsh r0, [r1, r0]
	add r0, r7, r0
	lsl r0, r0, #0x10
	asr r1, r0, #0x10
	lsr r0, r2, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	lsr r1, r1, #0x10
	orr r0, r1
	stmia r5!, {r0}
	add r0, r3, #0x1
	mov r1, #0xc0
	bl _s32_div_f
	lsl r0, r1, #0x18
	lsr r3, r0, #0x18
	ldr r0, _02012C8C ; =0x0000078D
	add r4, r4, #0x1
	ldrb r0, [r6, r0]
	cmp r4, r0
	ble _02012C12
_02012C4C:
	ldr r1, _02012C80 ; =0x00000798
	add r0, r1, #0x2
	ldrsh r2, [r6, r1]
	ldrsh r0, [r6, r0]
	add r4, r6, r1
	add r0, r2, r0
	strh r0, [r4, #0x0]
	ldrsh r0, [r6, r1]
	mov r1, #0x4b
	lsl r1, r1, #0x8
	cmp r0, r1
	blt _02012C70
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	bl _s32_div_f
	strh r1, [r4, #0x0]
	pop {r3-r7, pc}
_02012C70:
	cmp r0, #0x0
	bge _02012C7C
	mov r0, #0x0
	ldrsh r0, [r4, r0]
	add r0, r0, r1
	strh r0, [r4, #0x0]
_02012C7C:
	pop {r3-r7, pc}
	nop
_02012C80: .word 0x00000798
_02012C84: .word 0x0000078C
_02012C88: .word 0x0000060C
_02012C8C: .word 0x0000078D

	thumb_func_start FUN_02012C90
FUN_02012C90: ; 0x02012C90
	ldr r3, _02012C94 ; =FUN_020129C8
	bx r3
	.balign 4
_02012C94: .word FUN_020129C8

	thumb_func_start FUN_02012C98
FUN_02012C98: ; 0x02012C98
	push {r3-r5, lr}
	add r4, r0, #0x0
	bne _02012CA2
	bl ErrorHandling
_02012CA2:
	mov r0, #0x6
	lsl r0, r0, #0x8
	ldr r0, [r4, r0]
	bl FUN_0201299C
	mov r1, #0x3
	lsl r1, r1, #0x8
	add r5, r0, #0x0
	bl DC_FlushRange
	mov r1, #0x79
	lsl r1, r1, #0x4
	ldr r1, [r4, r1]
	add r0, r5, #0x0
	mov r2, #0x4
	mov r3, #0x1
	bl FUN_020129D8
	pop {r3-r5, pc}
