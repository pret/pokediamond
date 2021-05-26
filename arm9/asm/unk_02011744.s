    .include "asm/macros.inc"
    .include "global.inc"

	.extern FX_SinCosTable_

	.section .rodata

	.global UNK_020ED398
UNK_020ED398: ; 0x020ED398
	.byte 0x08, 0x08
	.byte 0x08, 0x04
	.byte 0x04, 0x08
	.byte 0x04, 0x04
	.byte 0x04, 0x02
	.byte 0x04, 0x01
	.byte 0x02, 0x04
	.byte 0x02, 0x02
	.byte 0x02, 0x01
	.byte 0x01, 0x04
	.byte 0x01, 0x02
	.byte 0x01, 0x01

	.text

	thumb_func_start FUN_02011744
FUN_02011744: ; 0x02011744
	push {r4-r7, lr}
	sub sp, #0xc
	add r7, r1, #0x0
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x68
	bl AllocFromHeap
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0201175E
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl AllocFromHeap
	ldr r1, [sp, #0x8]
	cmp r0, #0x0
	str r0, [r1, #0x60]
	bne _020117A4
	bl GF_AssertFail
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
	bl GF_AssertFail
_020117C6:
	mov r4, #0x0
	add r5, r6, #0x0
_020117CA:
	ldr r0, [r5, #0x0]
	bl FreeToHeap
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0xc
	blt _020117CA
	ldr r0, [r6, #0x60]
	bl FreeToHeap
	add r0, r6, #0x0
	bl FreeToHeap
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020117E8
FUN_020117E8: ; 0x020117E8
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	bne _020117F4
	bl GF_AssertFail
_020117F4:
	ldr r0, [r5, #0x0]
	bl FUN_02011BA0
	add r4, r0, #0x0
	bne _02011802
	bl GF_AssertFail
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
	bl AllocFromHeapAtEnd
	add r7, r0, #0x0
	mov r1, #0xc
	ldr r0, [r5, #0x2c]
	mul r1, r6
	bl AllocFromHeap
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
	bl FreeToHeap
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
	bl GF_AssertFail
_0201187A:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02011884
	bl GF_AssertFail
_02011884:
	add r0, r4, #0x0
	bl FUN_02011F00
	ldr r0, [r4, #0x0]
	bl FreeToHeap
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
_020119B4:
	cmp r4, #0x0
	bne _020119BC
	bl GF_AssertFail
_020119BC:
	cmp r6, #0x0
	bne _020119C4
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
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
	bl GF_AssertFail
_02011B42:
	ldrb r2, [r6, #0x8]
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x20]
	add r0, r1, r0
	cmp r2, r0
	bge _02011B52
	bl GF_AssertFail
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
	ldr r6, _02011CA0 ; =UNK_020ED398 + 1
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
	bl GF_AssertFail
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
	ldr r0, _02011CA0 ; =UNK_020ED398 + 1
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
_02011CA0: .word UNK_020ED398 + 1

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
	bl GF_AssertFail
_02011CB8:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02011CC2
	bl GF_AssertFail
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
	bl NNS_G2dInitImageProxy
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
	ldr r0, _02011E48 ; =UNK_020ED398 + 1
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
	bl AllocFromHeapAtEnd
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
	bl FreeToHeap
	ldr r0, [sp, #0x2c]
	add r0, r0, r4
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02011E44: .word UNK_020ED398
_02011E48: .word UNK_020ED398 + 1
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
	bl GF_AssertFail
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
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	bne _02011FBC
	bl GF_AssertFail
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
	bl GF_AssertFail
_02011FD2:
	add r0, r4, #0x0
	bl FreeToHeap
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
