	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start NitroMain
NitroMain: ; 0x02000C54
	push {r3-r7, lr}
	bl sub_02016014
	bl sub_02016148
	bl sub_020163BC
	mov r0, #0x0
	bl sub_02016438
	ldr r0, _02000DD0 ; =0x02106FA0
	mov r1, #0x0
	blx sub_020D50D8
	bl sub_02022294
	bl sub_0201259C
	bl sub_02000DF4
	bl sub_02002C14
	mov r0, #0x0
	mov r1, #0x3
	bl sub_02002C50
	mov r0, #0x1
	mov r1, #0x3
	bl sub_02002C50
	mov r0, #0x3
	add r1, r0, #0x0
	bl sub_02002C50
	mov r1, #0x0
	ldr r0, _02000DD4 ; =0x02106FA0
	mvn r1, r1
	str r1, [r0, #0x18]
	bl sub_0202254C
	ldr r1, _02000DD4 ; =0x02106FA0
	str r0, [r1, #0x20]
	bl sub_02029EF8
	add r4, r0, #0x0
	ldr r0, _02000DD4 ; =0x02106FA0
	ldr r0, [r0, #0x20]
	bl sub_02023900
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl sub_02003B98
	bl sub_02020AFC
	mov r0, #0x3
	bl sub_020337E8
	cmp r0, #0x3
	bne _02000CD4
	mov r0, #0x3
	mov r1, #0x0
	bl sub_02034188
_02000CD4:
	ldr r0, _02000DD4 ; =0x02106FA0
	ldr r0, [r0, #0x20]
	bl sub_020227FC
	cmp r0, #0x0
	bne _02000CE8
	mov r0, #0x0
	bl sub_02089D90
	b _02000D1A
_02000CE8:
	ldr r0, _02000DD8 ; =0x027FFC20
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _02000CF6
	cmp r0, #0x1
	beq _02000D06
	b _02000D16
_02000CF6:
	ldr r0, _02000DD4 ; =0x02106FA0
	mov r1, #0x0
	str r1, [r0, #0x1c]
	ldr r0, _02000DDC ; =0x0000003F
	ldr r1, _02000DE0 ; =0x021DBE18
	bl sub_02000E7C
	b _02000D1A
_02000D06:
	ldr r0, _02000DD4 ; =0x02106FA0
	mov r1, #0x1
	str r1, [r0, #0x1c]
	ldr r0, _02000DE4 ; =0x00000034
	ldr r1, _02000DE8 ; =0x021D76C8
	bl sub_02000E7C
	b _02000D1A
_02000D16:
	bl sub_02020C2C
_02000D1A:
	ldr r0, _02000DEC ; =0x021C48B8
	mov r1, #0x1
	str r1, [r0, #0x6c]
	mov r1, #0x0
	str r1, [r0, #0x30]
	bl sub_02000FA4
	bl sub_0200A2AC
	bl sub_02015E30
	mov r1, #0x0
	ldr r0, _02000DD4 ; =0x02106FA0
	mov r7, #0xc3
	ldr r6, _02000DF0 ; =0x021C4918
	ldr r4, _02000DEC ; =0x021C48B8
	str r1, [r0, #0x4]
	add r5, r1, #0x0
	lsl r7, r7, #0x2
_02000D40:
	bl sub_02000EE8
	bl sub_02000FE8
	bl sub_02016464
	mov r0, #0xc3
	ldr r1, [r4, #0x38]
	lsl r0, r0, #0x2
	and r0, r1
	cmp r0, r7
	bne _02000D64
	ldrb r0, [r6, #0x8]
	cmp r0, #0x0
	bne _02000D64
	mov r0, #0x0
	bl sub_02000F18
_02000D64:
	bl sub_0202FB80
	cmp r0, #0x0
	beq _02000D90
	bl sub_02000E0C
	ldr r0, [r4, #0x18]
	bl sub_0201B5CC
	ldr r0, [r4, #0x24]
	bl sub_0201B5CC
	ldr r0, [r4, #0x30]
	cmp r0, #0x0
	bne _02000D90
	mov r0, #0x1
	add r1, r0, #0x0
	blx sub_020C9C0C
	ldr r0, [r4, #0x2c]
	add r0, r0, #0x1
	str r0, [r4, #0x2c]
_02000D90:
	bl sub_020125D4
	bl sub_02015E60
	bl sub_020222C4
	ldr r0, [r4, #0x24]
	bl sub_0201B5CC
	mov r0, #0x1
	add r1, r0, #0x0
	blx sub_020C9C0C
	ldr r0, [r4, #0x2c]
	add r0, r0, #0x1
	str r0, [r4, #0x2c]
	str r5, [r4, #0x30]
	bl sub_0200A318
	bl sub_0200E2D8
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02000DC4
	ldr r0, [r4, #0x4]
	blx r1
_02000DC4:
	bl sub_02003C10
	ldr r0, [r4, #0x20]
	bl sub_0201B5CC
	b _02000D40
	.balign 4
_02000DD0: .word 0x02106FA0
_02000DD4: .word 0x02106FA0
_02000DD8: .word 0x027FFC20
_02000DDC: .word 0x0000003F
_02000DE0: .word 0x021DBE18
_02000DE4: .word 0x00000034
_02000DE8: .word 0x021D76C8
_02000DEC: .word 0x021C48B8
_02000DF0: .word 0x021C4918
