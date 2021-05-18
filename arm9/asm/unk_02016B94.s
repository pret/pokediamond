    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata
	.text































	thumb_func_start FUN_0201949C
FUN_0201949C: ; 0x0201949C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_020192D4
	add r0, r4, #0x0
	bl FUN_02019548
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_020194C8
FUN_020194C8: ; 0x020194C8
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020192D4
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	add r0, r4, #0x0
	bl FUN_02019548
	pop {r4, pc}

	thumb_func_start FUN_020194E0
FUN_020194E0: ; 0x020194E0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02019358
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x11
	str r0, [sp, #0x0]
	ldrb r5, [r4, #0x7]
	ldrb r3, [r4, #0x8]
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	mul r3, r5
	ldr r2, [r4, #0xc]
	lsl r3, r3, #0x6
	bl FUN_02017E14
	pop {r3-r5, pc}

	thumb_func_start FUN_0201951C
FUN_0201951C: ; 0x0201951C
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_02019358
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	ldrh r0, [r4, #0xa]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x11
	str r0, [sp, #0x0]
	ldrb r5, [r4, #0x7]
	ldrb r3, [r4, #0x8]
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	mul r3, r5
	ldr r2, [r4, #0xc]
	lsl r3, r3, #0x6
	bl FUN_02017E14
	pop {r3-r5, pc}

	thumb_func_start FUN_02019548
FUN_02019548: ; 0x02019548
	push {r3-r5, lr}
	add r3, r0, #0x0
	ldrh r2, [r3, #0xa]
	ldrb r1, [r3, #0x4]
	mov r4, #0x2c
	lsl r2, r2, #0x11
	ldr r0, [r3, #0x0]
	lsr r2, r2, #0x11
	str r2, [sp, #0x0]
	mul r4, r1
	add r4, r0, r4
	ldr r2, [r3, #0xc]
	ldrb r5, [r3, #0x7]
	ldrb r3, [r3, #0x8]
	ldrb r4, [r4, #0x1f]
	mul r3, r5
	mul r3, r4
	bl FUN_02017E14
	pop {r3-r5, pc}

	thumb_func_start FUN_02019570
FUN_02019570: ; 0x02019570
	push {r3, lr}
	ldrb r2, [r0, #0x4]
	mov r1, #0x2c
	ldr r3, [r0, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _02019588 ; =UNK_020EDB50
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_02019588: .word UNK_020EDB50

	thumb_func_start FUN_0201958C
FUN_0201958C: ; 0x0201958C
	push {r3, lr}
	ldrb r2, [r0, #0x4]
	mov r1, #0x2c
	ldr r3, [r0, #0x0]
	mul r1, r2
	add r1, r3, r1
	ldrb r1, [r1, #0x1c]
	lsl r2, r1, #0x2
	ldr r1, _020195A4 ; =UNK_020EDB44
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.balign 4
_020195A4: .word UNK_020EDB44

	thumb_func_start FUN_020195A8
FUN_020195A8: ; 0x020195A8
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_020193B4
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_020195D0
FUN_020195D0: ; 0x020195D0
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_020193B4
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020195E4
FUN_020195E4: ; 0x020195E4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl FUN_02019444
	ldrb r1, [r4, #0x4]
	mov r0, #0x2c
	add r2, r1, #0x0
	mul r2, r0
	ldr r0, [r4, #0x0]
	add r3, r0, r2
	ldr r2, [r3, #0x10]
	str r2, [sp, #0x0]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_02017CE8
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_0201960C
FUN_0201960C: ; 0x0201960C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02019444
	ldrb r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl FUN_0201AC68
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02019620
FUN_02019620: ; 0x02019620
	push {r3-r5, lr}
	add r4, r0, #0x0
	ldrb r2, [r4, #0x4]
	mov r0, #0x2c
	ldr r3, [r4, #0x0]
	mul r0, r2
	add r0, r3, r0
	ldrb r2, [r0, #0x1f]
	cmp r2, #0x20
	bne _0201963C
	lsl r0, r1, #0x4
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
_0201963C:
	lsl r3, r1, #0x18
	lsl r0, r1, #0x10
	orr r0, r3
	lsl r5, r1, #0x8
	orr r0, r5
	orr r0, r1
	ldr r1, [r4, #0xc]
	ldrb r3, [r4, #0x8]
	ldrb r4, [r4, #0x7]
	mul r2, r4
	mul r2, r3
	bl MIi_CpuClearFast
	pop {r3-r5, pc}

	thumb_func_start FUN_02019658
FUN_02019658: ; 0x02019658
	push {r4-r5, lr}
	sub sp, #0x1c
	add r4, sp, #0x18
	ldrh r5, [r4, #0x10]
	str r5, [sp, #0x0]
	ldrh r5, [r4, #0x14]
	str r5, [sp, #0x4]
	ldrh r5, [r4, #0x18]
	str r5, [sp, #0x8]
	ldrh r5, [r4, #0x1c]
	str r5, [sp, #0xc]
	ldrh r5, [r4, #0x20]
	str r5, [sp, #0x10]
	ldrh r4, [r4, #0x24]
	str r4, [sp, #0x14]
	mov r4, #0x0
	str r4, [sp, #0x18]
	bl FUN_02019684
	add sp, #0x1c
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_02019684
FUN_02019684: ; 0x02019684
	push {r4-r5, lr}
	sub sp, #0x24
	str r1, [sp, #0x1c]
	add r4, sp, #0x20
	ldrh r5, [r4, #0x10]
	add r1, sp, #0x14
	strh r5, [r1, #0xc]
	ldrh r5, [r4, #0x14]
	strh r5, [r1, #0xe]
	ldr r5, [r0, #0xc]
	str r5, [sp, #0x14]
	ldrb r5, [r0, #0x7]
	lsl r5, r5, #0x3
	strh r5, [r1, #0x4]
	ldrb r5, [r0, #0x8]
	lsl r5, r5, #0x3
	strh r5, [r1, #0x6]
	ldrb r5, [r0, #0x4]
	ldr r1, [r0, #0x0]
	mov r0, #0x2c
	mul r0, r5
	add r0, r1, r0
	ldrb r0, [r0, #0x1e]
	add r1, sp, #0x14
	cmp r0, #0x0
	ldrh r0, [r4, #0x18]
	bne _020196D6
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x1c]
	str r0, [sp, #0x4]
	ldrh r0, [r4, #0x20]
	str r0, [sp, #0x8]
	ldrh r0, [r4, #0x24]
	str r0, [sp, #0xc]
	ldrh r0, [r4, #0x28]
	str r0, [sp, #0x10]
	add r0, sp, #0x1c
	bl FUN_02018A60
	add sp, #0x24
	pop {r4-r5, pc}
_020196D6:
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x1c]
	str r0, [sp, #0x4]
	ldrh r0, [r4, #0x20]
	str r0, [sp, #0x8]
	ldrh r0, [r4, #0x24]
	str r0, [sp, #0xc]
	ldrh r0, [r4, #0x28]
	str r0, [sp, #0x10]
	add r0, sp, #0x1c
	bl FUN_02018CA0
	add sp, #0x24
	pop {r4-r5, pc}
	.balign 4

	thumb_func_start FUN_020196F4
FUN_020196F4: ; 0x020196F4
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r1, #0x0
	ldr r1, [r0, #0xc]
	add r4, r2, #0x0
	str r1, [sp, #0x8]
	ldrb r1, [r0, #0x7]
	add r2, r3, #0x0
	lsl r3, r1, #0x3
	add r1, sp, #0x8
	strh r3, [r1, #0x4]
	ldrb r3, [r0, #0x8]
	lsl r3, r3, #0x3
	strh r3, [r1, #0x6]
	ldrb r3, [r0, #0x4]
	ldr r1, [r0, #0x0]
	mov r0, #0x2c
	mul r0, r3
	add r0, r1, r0
	ldrb r0, [r0, #0x1e]
	add r3, sp, #0x10
	cmp r0, #0x0
	bne _02019736
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x10]
	add r0, sp, #0x8
	bl FUN_02018E88
	add sp, #0x10
	pop {r3-r5, pc}
_02019736:
	ldrh r0, [r3, #0x14]
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x10]
	add r0, sp, #0x8
	bl FUN_02018F4C
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0201974C
FUN_0201974C: ; 0x0201974C
	push {r4-r7, lr}
	sub sp, #0x1fc
	sub sp, #0x118
	add r5, r0, #0x0
	ldr r0, [sp, #0x330]
	str r1, [sp, #0x0]
	str r0, [sp, #0x330]
	add r1, sp, #0x318
	ldrh r1, [r1, #0x10]
	ldr r0, [r5, #0xc]
	str r1, [sp, #0x5c]
	ldrb r1, [r5, #0x7]
	str r0, [sp, #0x278]
	ldrb r0, [r5, #0x8]
	lsl r1, r1, #0x13
	lsr r4, r1, #0x10
	ldr r1, [sp, #0x5c]
	lsl r0, r0, #0x13
	sub r1, r4, r1
	lsr r0, r0, #0x10
	str r4, [sp, #0x58]
	str r1, [sp, #0x8]
	cmp r1, r2
	blt _0201977E
	str r2, [sp, #0x8]
_0201977E:
	add r1, sp, #0x318
	ldrh r1, [r1, #0x14]
	sub r0, r0, r1
	str r1, [sp, #0x48]
	str r0, [sp, #0x4]
	cmp r0, r3
	blt _0201978E
	str r3, [sp, #0x4]
_0201978E:
	ldr r0, [sp, #0x8]
	mov r4, #0x0
	cmp r0, #0x8
	ble _0201979E
	mov r0, #0x1
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_0201979E:
	ldr r0, [sp, #0x4]
	cmp r0, #0x8
	ble _020197AC
	mov r0, #0x2
	orr r0, r4
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
_020197AC:
	ldrh r0, [r5, #0xa]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x1f
	beq _020197B8
	bl FUN_0201A12C
_020197B8:
	cmp r4, #0x3
	bls _020197C0
	bl FUN_0201A8BC
_020197C0:
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020197CC: ; jump table (using 16-bit offset)
	.short _020197D4 - _020197CC - 2; case 0
	.short _020198D6 - _020197CC - 2; case 1
	.short _02019AE6 - _020197CC - 2; case 2
	.short _02019D06 - _020197CC - 2; case 3
_020197D4:
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x70]
	mov r0, #0x0
	str r0, [sp, #0x274]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bgt _020197EA
	bl FUN_0201A8BC
_020197EA:
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x6c]
_020197F6:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x70]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x26c]
	ldr r0, [sp, #0x274]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x270]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _020198AA
	ble _020198AA
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x6c]
	lsl r5, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x68]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	ldr r5, [sp, #0x6c]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x64]
	str r0, [sp, #0x60]
_02019848:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019B68 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x68]
	str r5, [sp, #0x27c]
	add r0, r5, r0
	ldr r5, [sp, #0x26c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _0201989C
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x280]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x284]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x284]
	and r6, r5
	ldr r5, [sp, #0x280]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x270]
	cmp r0, #0x0
	beq _0201989C
	ldr r6, [sp, #0x27c]
	ldr r0, [sp, #0x64]
	add r6, r6, r0
	ldr r0, [sp, #0x60]
	strb r5, [r0, r6]
_0201989C:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019848
_020198AA:
	ldr r0, [sp, #0x270]
	cmp r0, #0x0
	beq _020198B8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _020198BE
_020198B8:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_020198BE:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x274]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x274]
	cmp r1, r0
	blt _020197F6
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_020198D6:
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x25c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x264]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x54]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x84]
	mov r0, #0x0
	str r0, [sp, #0x268]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _020199D2
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x80]
_02019902:
	ldr r0, [sp, #0x25c]
	ldr r1, [sp, #0x84]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x258]
	ldr r0, [sp, #0x268]
	ldr r6, [sp, #0x80]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x260]
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x264]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x264]
	str r6, [sp, #0x7c]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	ldr r5, [sp, #0x80]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x78]
	str r0, [sp, #0x74]
_0201994C:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019B68 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x7c]
	str r5, [sp, #0x288]
	add r0, r5, r0
	ldr r5, [sp, #0x258]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _020199A0
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x28c]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x290]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x290]
	and r6, r5
	ldr r5, [sp, #0x28c]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x260]
	cmp r0, #0x0
	beq _020199A0
	ldr r6, [sp, #0x288]
	ldr r0, [sp, #0x78]
	add r6, r6, r0
	ldr r0, [sp, #0x74]
	strb r5, [r0, r6]
_020199A0:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _0201994C
	ldr r0, [sp, #0x260]
	cmp r0, #0x0
	beq _020199BA
	ldr r0, [sp, #0x264]
	add r0, r0, #0x2
	str r0, [sp, #0x264]
	b _020199C0
_020199BA:
	ldr r0, [sp, #0x264]
	add r0, r0, #0x1
	str r0, [sp, #0x264]
_020199C0:
	ldr r0, [sp, #0x25c]
	add r0, r0, #0x4
	str r0, [sp, #0x25c]
	ldr r0, [sp, #0x268]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x268]
	cmp r1, r0
	blt _02019902
_020199D2:
	ldr r0, [sp, #0x0]
	add r0, #0x20
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x54]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x98]
	mov r0, #0x0
	str r0, [sp, #0x254]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bgt _020199EE
	bl FUN_0201A8BC
_020199EE:
	ldr r0, [sp, #0x5c]
	mov r1, #0x7
	add r0, #0x8
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x94]
_02019A00:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x98]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x24c]
	ldr r0, [sp, #0x254]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x250]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x294]
	sub r0, #0x8
	str r0, [sp, #0x294]
	cmp r0, #0x0
	ble _02019ABA
	ble _02019ABA
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x94]
	lsl r5, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x90]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	ldr r5, [sp, #0x94]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0x8c]
	str r0, [sp, #0x88]
_02019A58:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019B68 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0x90]
	str r5, [sp, #0x298]
	add r0, r5, r0
	ldr r5, [sp, #0x24c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019AAC
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x29c]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2a0]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2a0]
	and r6, r5
	ldr r5, [sp, #0x29c]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x250]
	cmp r0, #0x0
	beq _02019AAC
	ldr r6, [sp, #0x298]
	ldr r0, [sp, #0x8c]
	add r6, r6, r0
	ldr r0, [sp, #0x88]
	strb r5, [r0, r6]
_02019AAC:
	ldr r0, [sp, #0x294]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019A58
_02019ABA:
	ldr r0, [sp, #0x250]
	cmp r0, #0x0
	beq _02019AC8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _02019ACE
_02019AC8:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019ACE:
	ldr r0, [sp, #0x0]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x254]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x254]
	cmp r1, r0
	blt _02019A00
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_02019AE6:
	ldr r0, [sp, #0x0]
	mov r1, #0x7
	str r0, [sp, #0x23c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x244]
	mov r0, #0x0
	str r0, [sp, #0x248]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xa8]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x40]
_02019B06:
	ldr r0, [sp, #0x23c]
	ldr r1, [sp, #0xa8]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x238]
	ldr r0, [sp, #0x248]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x240]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _02019BC2
	ble _02019BC2
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x244]
	ldr r6, [sp, #0x40]
	lsl r5, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x244]
	str r6, [sp, #0xa4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019B68 ; =0x00003FE0
	ldr r5, [sp, #0x40]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xa0]
	str r0, [sp, #0x9c]
_02019B58:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019B68 ; =0x00003FE0
	b _02019B6C
	nop
_02019B68: .word 0x00003FE0
_02019B6C:
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xa4]
	str r5, [sp, #0x2a4]
	add r0, r5, r0
	ldr r5, [sp, #0x238]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019BB4
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2a8]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2ac]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2ac]
	and r6, r5
	ldr r5, [sp, #0x2a8]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x240]
	cmp r0, #0x0
	beq _02019BB4
	ldr r6, [sp, #0x2a4]
	ldr r0, [sp, #0xa0]
	add r6, r6, r0
	ldr r0, [sp, #0x9c]
	strb r5, [r0, r6]
_02019BB4:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019B58
_02019BC2:
	ldr r0, [sp, #0x240]
	cmp r0, #0x0
	beq _02019BD0
	ldr r0, [sp, #0x244]
	add r0, r0, #0x2
	str r0, [sp, #0x244]
	b _02019BD6
_02019BD0:
	ldr r0, [sp, #0x244]
	add r0, r0, #0x1
	str r0, [sp, #0x244]
_02019BD6:
	ldr r0, [sp, #0x23c]
	add r0, r0, #0x4
	str r0, [sp, #0x23c]
	ldr r0, [sp, #0x248]
	add r0, r0, #0x1
	str r0, [sp, #0x248]
	cmp r0, #0x8
	blt _02019B06
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r0, #0x40
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x48]
	mov r1, #0x1
	add r0, #0x8
	str r0, [sp, #0x48]
_02019BF6:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _02019C04
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019C04:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _02019BF6
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xb8]
	mov r0, #0x0
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	bgt _02019C24
	bl FUN_0201A8BC
_02019C24:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0xb8]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x230]
	ldr r0, [sp, #0x20]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x234]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	cmp r0, #0x0
	ble _02019CD8
	ble _02019CD8
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x40]
	lsl r5, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xb4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	ldr r5, [sp, #0x40]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xb0]
	str r0, [sp, #0xac]
_02019C76:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019F88 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xb4]
	str r5, [sp, #0x2b0]
	add r0, r5, r0
	ldr r5, [sp, #0x230]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019CCA
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2b4]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2b8]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2b8]
	and r6, r5
	ldr r5, [sp, #0x2b4]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x234]
	cmp r0, #0x0
	beq _02019CCA
	ldr r6, [sp, #0x2b0]
	ldr r0, [sp, #0xb0]
	add r6, r6, r0
	ldr r0, [sp, #0xac]
	strb r5, [r0, r6]
_02019CCA:
	ldr r0, [sp, #0x8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019C76
_02019CD8:
	ldr r0, [sp, #0x234]
	cmp r0, #0x0
	beq _02019CE6
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _02019CEC
_02019CE6:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_02019CEC:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x20]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x20]
	cmp r0, r1
	blt _02019C24
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
_02019D06:
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x220]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x228]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x22c]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x38]
_02019D2A:
	ldr r0, [sp, #0x220]
	ldr r1, [sp, #0x3c]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x21c]
	ldr r0, [sp, #0x22c]
	ldr r6, [sp, #0x38]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x224]
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x228]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x228]
	str r6, [sp, #0xc4]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	str r3, [sp, #0x34]
	add r4, r1, #0x0
	str r5, [sp, #0xc0]
	str r0, [sp, #0xbc]
_02019D76:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019F88 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xc4]
	str r5, [sp, #0x2bc]
	add r0, r5, r0
	ldr r5, [sp, #0x21c]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019DCA
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2c0]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2c4]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2c4]
	and r6, r5
	ldr r5, [sp, #0x2c0]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x224]
	cmp r0, #0x0
	beq _02019DCA
	ldr r6, [sp, #0x2bc]
	ldr r0, [sp, #0xc0]
	add r6, r6, r0
	ldr r0, [sp, #0xbc]
	strb r5, [r0, r6]
_02019DCA:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _02019D76
	ldr r0, [sp, #0x224]
	cmp r0, #0x0
	beq _02019DE4
	ldr r0, [sp, #0x228]
	add r0, r0, #0x2
	str r0, [sp, #0x228]
	b _02019DEA
_02019DE4:
	ldr r0, [sp, #0x228]
	add r0, r0, #0x1
	str r0, [sp, #0x228]
_02019DEA:
	ldr r0, [sp, #0x220]
	add r0, r0, #0x4
	str r0, [sp, #0x220]
	ldr r0, [sp, #0x22c]
	add r0, r0, #0x1
	str r0, [sp, #0x22c]
	cmp r0, #0x8
	blt _02019D2A
	ldr r0, [sp, #0x0]
	str r0, [sp, #0x20c]
	add r0, #0x20
	str r0, [sp, #0x20c]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x214]
	mov r0, #0x0
	str r0, [sp, #0x218]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0xd4]
	add r0, #0x8
	str r0, [sp, #0xd4]
_02019E12:
	ldr r0, [sp, #0x20c]
	ldr r1, [sp, #0x3c]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0xd4]
	str r0, [sp, #0x208]
	ldr r0, [sp, #0x218]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x210]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x2c8]
	sub r0, #0x8
	str r0, [sp, #0x2c8]
	cmp r0, #0x0
	ble _02019ECC
	ble _02019ECC
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x214]
	ldr r6, [sp, #0x38]
	lsl r5, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x214]
	str r6, [sp, #0xd0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xcc]
	str r0, [sp, #0xc8]
_02019E6A:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019F88 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xd0]
	str r5, [sp, #0x2cc]
	add r0, r5, r0
	ldr r5, [sp, #0x208]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019EBE
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2d0]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2d4]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2d4]
	and r6, r5
	ldr r5, [sp, #0x2d0]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x210]
	cmp r0, #0x0
	beq _02019EBE
	ldr r6, [sp, #0x2cc]
	ldr r0, [sp, #0xcc]
	add r6, r6, r0
	ldr r0, [sp, #0xc8]
	strb r5, [r0, r6]
_02019EBE:
	ldr r0, [sp, #0x2c8]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _02019E6A
_02019ECC:
	ldr r0, [sp, #0x210]
	cmp r0, #0x0
	beq _02019EDA
	ldr r0, [sp, #0x214]
	add r0, r0, #0x2
	str r0, [sp, #0x214]
	b _02019EE0
_02019EDA:
	ldr r0, [sp, #0x214]
	add r0, r0, #0x1
	str r0, [sp, #0x214]
_02019EE0:
	ldr r0, [sp, #0x20c]
	add r0, r0, #0x4
	str r0, [sp, #0x20c]
	ldr r0, [sp, #0x218]
	add r0, r0, #0x1
	str r0, [sp, #0x218]
	cmp r0, #0x8
	blt _02019E12
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	str r0, [sp, #0x1fc]
	add r0, #0x40
	str r0, [sp, #0x1fc]
	ldr r0, [sp, #0x48]
	mov r1, #0x1
	add r0, #0x8
	str r0, [sp, #0x48]
	str r0, [sp, #0x204]
_02019F04:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _02019F12
	ldr r0, [sp, #0x204]
	add r0, r0, #0x1
	str r0, [sp, #0x204]
_02019F12:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _02019F04
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	str r0, [sp, #0x50]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xe4]
	mov r0, #0x0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A008
_02019F30:
	ldr r0, [sp, #0x1fc]
	ldr r1, [sp, #0xe4]
	ldr r0, [r0, #0x0]
	ldr r6, [sp, #0x38]
	str r0, [sp, #0x1f8]
	ldr r0, [sp, #0x1c]
	ldr r2, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x200]
	ldr r0, [sp, #0x204]
	mov r1, #0x0
	lsl r5, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x204]
	str r6, [sp, #0xe0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _02019F88 ; =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	ldr r3, [sp, #0x34]
	add r4, r1, #0x0
	str r5, [sp, #0xdc]
	str r0, [sp, #0xd8]
_02019F78:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _02019F88 ; =0x00003FE0
	b _02019F8C
	nop
_02019F88: .word 0x00003FE0
_02019F8C:
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xe0]
	str r5, [sp, #0x2d8]
	add r0, r5, r0
	ldr r5, [sp, #0x1f8]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _02019FD4
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2dc]
	ldrb r5, [r0, r7]
	str r5, [sp, #0x2e0]
	mov r5, #0xf0
	asr r5, r6
	ldr r6, [sp, #0x2e0]
	and r6, r5
	ldr r5, [sp, #0x2dc]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x200]
	cmp r0, #0x0
	beq _02019FD4
	ldr r6, [sp, #0x2d8]
	ldr r0, [sp, #0xdc]
	add r6, r6, r0
	ldr r0, [sp, #0xd8]
	strb r5, [r0, r6]
_02019FD4:
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, #0x8
	blt _02019F78
	ldr r0, [sp, #0x200]
	cmp r0, #0x0
	beq _02019FEE
	ldr r0, [sp, #0x204]
	add r0, r0, #0x2
	str r0, [sp, #0x204]
	b _02019FF4
_02019FEE:
	ldr r0, [sp, #0x204]
	add r0, r0, #0x1
	str r0, [sp, #0x204]
_02019FF4:
	ldr r0, [sp, #0x1fc]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x1fc]
	ldr r0, [sp, #0x1c]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1c]
	cmp r0, r1
	blt _02019F30
_0201A008:
	ldr r0, [sp, #0x0]
	mov r2, #0x0
	add r0, #0x60
	str r0, [sp, #0x0]
	mov r1, #0x1
_0201A012:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _0201A020
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A020:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _0201A012
	ldr r0, [sp, #0x50]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0xf4]
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	bgt _0201A03E
	bl FUN_0201A8BC
_0201A03E:
	ldr r0, [sp, #0x5c]
	add r0, #0x8
	str r0, [sp, #0x5c]
_0201A044:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0xf4]
	ldr r0, [r0, #0x0]
	ldr r2, [sp, #0x5c]
	str r0, [sp, #0x1f0]
	ldr r0, [sp, #0x18]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1f4]
	ldr r0, [sp, #0x8]
	mov r1, #0x0
	str r0, [sp, #0x2e4]
	sub r0, #0x8
	str r0, [sp, #0x2e4]
	cmp r0, #0x0
	ble _0201A0FE
	ble _0201A0FE
	add r0, r2, #0x0
	lsl r3, r0, #0x2
	ldr r0, [sp, #0x48]
	ldr r6, [sp, #0x38]
	lsl r5, r0, #0x2
	ldr r0, _0201A3A8 ; =0x00003FE0
	add r7, r5, #0x0
	and r0, r5
	mul r6, r0
	mov r0, #0x1c
	and r7, r0
	ldr r0, [sp, #0x48]
	str r6, [sp, #0xf0]
	add r0, r0, #0x1
	lsl r6, r0, #0x2
	ldr r0, _0201A3A8 ; =0x00003FE0
	ldr r5, [sp, #0x38]
	and r0, r6
	mul r5, r0
	mov r0, #0x1c
	and r0, r6
	add r4, r1, #0x0
	str r5, [sp, #0xec]
	str r0, [sp, #0xe8]
_0201A09C:
	asr r5, r2, #0x1
	mov r0, #0x3
	and r5, r0
	ldr r0, [sp, #0x278]
	add r0, r0, r5
	ldr r5, _0201A3A8 ; =0x00003FE0
	and r5, r3
	add r5, r0, r5
	ldr r0, [sp, #0xf0]
	str r5, [sp, #0x2e8]
	add r0, r5, r0
	ldr r5, [sp, #0x1f0]
	add r6, r5, #0x0
	lsr r6, r4
	mov r5, #0xf
	and r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	beq _0201A0F0
	lsl r6, r2, #0x1f
	lsr r6, r6, #0x1d
	lsl r5, r6
	str r5, [sp, #0x2ec]
	ldrb r5, [r0, r7]
	mov r12, r5
	mov r5, #0xf0
	asr r5, r6
	mov r6, r12
	and r6, r5
	ldr r5, [sp, #0x2ec]
	orr r5, r6
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	strb r5, [r0, r7]
	ldr r0, [sp, #0x1f4]
	cmp r0, #0x0
	beq _0201A0F0
	ldr r6, [sp, #0x2e8]
	ldr r0, [sp, #0xec]
	add r6, r6, r0
	ldr r0, [sp, #0xe8]
	strb r5, [r0, r6]
_0201A0F0:
	ldr r0, [sp, #0x2e4]
	add r1, r1, #0x1
	add r4, r4, #0x4
	add r3, r3, #0x4
	add r2, r2, #0x1
	cmp r1, r0
	blt _0201A09C
_0201A0FE:
	ldr r0, [sp, #0x1f4]
	cmp r0, #0x0
	beq _0201A10C
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A112
_0201A10C:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A112:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x4
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	cmp r0, r1
	blt _0201A044
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}

	thumb_func_start FUN_0201A12C
FUN_0201A12C: ; 0x0201A12C
	lsl r1, r2, #0x2
	mul r1, r3
	ldr r3, [r5, #0x0]
	ldrb r2, [r5, #0x9]
	ldr r0, [sp, #0x0]
	ldr r3, [r3, #0x0]
	lsl r1, r1, #0x3
	bl FUN_02018848
	str r0, [sp, #0x1ec]
	cmp r4, #0x3
	bhi _0201A21E
	add r0, r4, r4
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0201A150: ; jump table (using 16-bit offset)
	.short _0201A158 - _0201A150 - 2; case 0
	.short _0201A220 - _0201A150 - 2; case 1
	.short _0201A3CA - _0201A150 - 2; case 2
	.short _0201A56E - _0201A150 - 2; case 3
_0201A158:
	ldr r0, [sp, #0x330]
	ldr r7, [sp, #0x1ec]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x10c]
	mov r0, #0x0
	str r0, [sp, #0x1e8]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A21E
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x108]
_0201A178:
	ldr r1, [sp, #0x10c]
	ldr r0, [sp, #0x1e8]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x310]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A1FC
	ble _0201A1FC
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x108]
	lsl r1, r0, #0x3
	ldr r0, _0201A3AC ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x100]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x104]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A3AC ; =0x00007FC0
	ldr r2, [sp, #0x108]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0xfc]
	str r0, [sp, #0xf8]
_0201A1C4:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A3AC ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x104]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A1F0
	ldr r0, [sp, #0x100]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x310]
	cmp r0, #0x0
	beq _0201A1F0
	ldr r0, [sp, #0xfc]
	add r2, r3, r0
	ldr r0, [sp, #0xf8]
	strb r1, [r0, r2]
_0201A1F0:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A1C4
_0201A1FC:
	ldr r0, [sp, #0x310]
	cmp r0, #0x0
	beq _0201A20A
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A210
_0201A20A:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A210:
	ldr r0, [sp, #0x1e8]
	add r7, #0x8
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1e8]
	cmp r1, r0
	blt _0201A178
_0201A21E:
	b _0201A8B6
_0201A220:
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	str r0, [sp, #0x1e0]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x124]
	mov r0, #0x0
	str r0, [sp, #0x1e4]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A2E6
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x120]
_0201A24A:
	ldr r1, [sp, #0x124]
	ldr r0, [sp, #0x1e4]
	ldr r5, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x30c]
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1e0]
	ldr r2, [sp, #0x120]
	lsl r1, r0, #0x3
	ldr r0, _0201A3AC ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x118]
	ldr r0, [sp, #0x1e0]
	str r2, [sp, #0x11c]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A3AC ; =0x00007FC0
	ldr r2, [sp, #0x120]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	mov r4, #0x0
	str r2, [sp, #0x114]
	str r0, [sp, #0x110]
_0201A28E:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A3AC ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x11c]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A2BA
	ldr r0, [sp, #0x118]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x30c]
	cmp r0, #0x0
	beq _0201A2BA
	ldr r0, [sp, #0x114]
	add r2, r3, r0
	ldr r0, [sp, #0x110]
	strb r1, [r0, r2]
_0201A2BA:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A28E
	ldr r0, [sp, #0x30c]
	cmp r0, #0x0
	beq _0201A2D2
	ldr r0, [sp, #0x1e0]
	add r0, r0, #0x2
	str r0, [sp, #0x1e0]
	b _0201A2D8
_0201A2D2:
	ldr r0, [sp, #0x1e0]
	add r0, r0, #0x1
	str r0, [sp, #0x1e0]
_0201A2D8:
	ldr r0, [sp, #0x1e4]
	add r7, #0x8
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1e4]
	cmp r1, r0
	blt _0201A24A
_0201A2E6:
	ldr r0, [sp, #0x1ec]
	str r0, [sp, #0x308]
	add r0, #0x40
	str r0, [sp, #0x308]
	ldr r0, [sp, #0x4c]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x13c]
	mov r0, #0x0
	str r0, [sp, #0x1dc]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ble _0201A3C8
	ldr r0, [sp, #0x5c]
	mov r1, #0x7
	add r0, #0x8
	str r0, [sp, #0x5c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x138]
_0201A312:
	ldr r1, [sp, #0x13c]
	ldr r0, [sp, #0x1dc]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1d8]
	ldr r5, [sp, #0x5c]
	cmp r7, #0x0
	ble _0201A398
	ble _0201A398
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x138]
	lsl r1, r0, #0x3
	ldr r0, _0201A3AC ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x130]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x134]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A3AC ; =0x00007FC0
	ldr r2, [sp, #0x138]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x12c]
	str r0, [sp, #0x128]
_0201A360:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A3AC ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x134]
	add r2, r3, r0
	ldr r0, [sp, #0x308]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A38E
	ldr r0, [sp, #0x130]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1d8]
	cmp r0, #0x0
	beq _0201A38E
	ldr r0, [sp, #0x12c]
	add r2, r3, r0
	ldr r0, [sp, #0x128]
	strb r1, [r0, r2]
_0201A38E:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A360
_0201A398:
	ldr r0, [sp, #0x1d8]
	cmp r0, #0x0
	beq _0201A3B0
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A3B6
	nop
_0201A3A8: .word 0x00003FE0
_0201A3AC: .word 0x00007FC0
_0201A3B0:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A3B6:
	ldr r0, [sp, #0x308]
	add r0, #0x8
	str r0, [sp, #0x308]
	ldr r0, [sp, #0x1dc]
	add r1, r0, #0x1
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x1dc]
	cmp r1, r0
	blt _0201A312
_0201A3C8:
	b _0201A8B6
_0201A3CA:
	ldr r0, [sp, #0x48]
	mov r1, #0x7
	str r0, [sp, #0x1d0]
	mov r0, #0x0
	str r0, [sp, #0x1d4]
	ldr r0, [sp, #0x330]
	ldr r7, [sp, #0x1ec]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x150]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x30]
_0201A3E8:
	ldr r1, [sp, #0x150]
	ldr r0, [sp, #0x1d4]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x304]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A46C
	ble _0201A46C
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1d0]
	ldr r2, [sp, #0x30]
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x148]
	ldr r0, [sp, #0x1d0]
	str r2, [sp, #0x14c]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	ldr r2, [sp, #0x30]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x144]
	str r0, [sp, #0x140]
_0201A434:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A748 ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x14c]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A460
	ldr r0, [sp, #0x148]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x304]
	cmp r0, #0x0
	beq _0201A460
	ldr r0, [sp, #0x144]
	add r2, r3, r0
	ldr r0, [sp, #0x140]
	strb r1, [r0, r2]
_0201A460:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A434
_0201A46C:
	ldr r0, [sp, #0x304]
	cmp r0, #0x0
	beq _0201A47A
	ldr r0, [sp, #0x1d0]
	add r0, r0, #0x2
	str r0, [sp, #0x1d0]
	b _0201A480
_0201A47A:
	ldr r0, [sp, #0x1d0]
	add r0, r0, #0x1
	str r0, [sp, #0x1d0]
_0201A480:
	ldr r0, [sp, #0x1d4]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1d4]
	cmp r0, #0x8
	blt _0201A3E8
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	add r0, #0x8
	str r0, [sp, #0x48]
	add r7, #0x80
	mov r0, #0x0
	mov r2, #0x1
_0201A49A:
	ldr r1, [sp, #0x330]
	asr r1, r0
	tst r1, r2
	beq _0201A4A8
	ldr r1, [sp, #0x48]
	add r1, r1, #0x1
	str r1, [sp, #0x48]
_0201A4A8:
	add r0, r0, #0x1
	cmp r0, #0x8
	blt _0201A49A
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x164]
	mov r0, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A56C
_0201A4C4:
	ldr r1, [sp, #0x164]
	ldr r0, [sp, #0x14]
	mov r4, #0x0
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x300]
	ldr r0, [sp, #0x8]
	ldr r5, [sp, #0x5c]
	cmp r0, #0x0
	ble _0201A548
	ble _0201A548
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x30]
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x15c]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x160]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	ldr r2, [sp, #0x30]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x158]
	str r0, [sp, #0x154]
_0201A510:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A748 ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x160]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A53C
	ldr r0, [sp, #0x15c]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x300]
	cmp r0, #0x0
	beq _0201A53C
	ldr r0, [sp, #0x158]
	add r2, r3, r0
	ldr r0, [sp, #0x154]
	strb r1, [r0, r2]
_0201A53C:
	ldr r0, [sp, #0x8]
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r0
	blt _0201A510
_0201A548:
	ldr r0, [sp, #0x300]
	cmp r0, #0x0
	beq _0201A556
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A55C
_0201A556:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A55C:
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x1
	sub r1, #0x8
	add r7, #0x8
	str r0, [sp, #0x14]
	cmp r0, r1
	blt _0201A4C4
_0201A56C:
	b _0201A8B6
_0201A56E:
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	str r0, [sp, #0x1c8]
	ldr r0, [sp, #0x330]
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	mov r0, #0x0
	str r0, [sp, #0x1cc]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2c]
	ldr r0, [sp, #0x58]
	mov r1, #0x7
	and r1, r0
	add r0, r0, r1
	asr r0, r0, #0x3
	str r0, [sp, #0x28]
_0201A590:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1cc]
	ldr r5, [sp, #0x5c]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2fc]
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1c8]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x170]
	ldr r0, [sp, #0x1c8]
	str r2, [sp, #0x174]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	mov r4, #0x0
	str r6, [sp, #0x24]
	str r2, [sp, #0x16c]
	str r0, [sp, #0x168]
_0201A5D6:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A748 ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x174]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A602
	ldr r0, [sp, #0x170]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x2fc]
	cmp r0, #0x0
	beq _0201A602
	ldr r0, [sp, #0x16c]
	add r2, r3, r0
	ldr r0, [sp, #0x168]
	strb r1, [r0, r2]
_0201A602:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A5D6
	ldr r0, [sp, #0x2fc]
	cmp r0, #0x0
	beq _0201A61A
	ldr r0, [sp, #0x1c8]
	add r0, r0, #0x2
	str r0, [sp, #0x1c8]
	b _0201A620
_0201A61A:
	ldr r0, [sp, #0x1c8]
	add r0, r0, #0x1
	str r0, [sp, #0x1c8]
_0201A620:
	ldr r0, [sp, #0x1cc]
	add r7, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0x1cc]
	cmp r0, #0x8
	blt _0201A590
	ldr r0, [sp, #0x1ec]
	str r0, [sp, #0x2f8]
	add r0, #0x40
	str r0, [sp, #0x2f8]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x1c0]
	mov r0, #0x0
	str r0, [sp, #0x1c4]
	ldr r0, [sp, #0x5c]
	str r0, [sp, #0x188]
	add r0, #0x8
	str r0, [sp, #0x188]
_0201A644:
	ldr r1, [sp, #0x2c]
	ldr r0, [sp, #0x1c4]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1bc]
	ldr r5, [sp, #0x188]
	cmp r7, #0x0
	ble _0201A6CA
	ble _0201A6CA
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x1c0]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x180]
	ldr r0, [sp, #0x1c0]
	str r2, [sp, #0x184]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x17c]
	str r0, [sp, #0x178]
_0201A692:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A748 ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x184]
	add r2, r3, r0
	ldr r0, [sp, #0x2f8]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A6C0
	ldr r0, [sp, #0x180]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1bc]
	cmp r0, #0x0
	beq _0201A6C0
	ldr r0, [sp, #0x17c]
	add r2, r3, r0
	ldr r0, [sp, #0x178]
	strb r1, [r0, r2]
_0201A6C0:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A692
_0201A6CA:
	ldr r0, [sp, #0x1bc]
	cmp r0, #0x0
	beq _0201A6D8
	ldr r0, [sp, #0x1c0]
	add r0, r0, #0x2
	str r0, [sp, #0x1c0]
	b _0201A6DE
_0201A6D8:
	ldr r0, [sp, #0x1c0]
	add r0, r0, #0x1
	str r0, [sp, #0x1c0]
_0201A6DE:
	ldr r0, [sp, #0x2f8]
	add r0, #0x8
	str r0, [sp, #0x2f8]
	ldr r0, [sp, #0x1c4]
	add r0, r0, #0x1
	str r0, [sp, #0x1c4]
	cmp r0, #0x8
	blt _0201A644
	ldr r0, [sp, #0x48]
	ldr r7, [sp, #0x1ec]
	add r0, #0x8
	add r7, #0x80
	str r0, [sp, #0x48]
	str r0, [sp, #0x1b8]
	mov r0, #0x0
	mov r2, #0x1
_0201A6FE:
	ldr r1, [sp, #0x330]
	asr r1, r0
	tst r1, r2
	beq _0201A70C
	ldr r1, [sp, #0x1b8]
	add r1, r1, #0x1
	str r1, [sp, #0x1b8]
_0201A70C:
	add r0, r0, #0x1
	cmp r0, #0x8
	blt _0201A6FE
	ldr r0, [sp, #0x330]
	asr r0, r0, #0x8
	str r0, [sp, #0x44]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x19c]
	mov r0, #0x0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A7CE
_0201A72A:
	ldr r1, [sp, #0x19c]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x28]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x2f4]
	ldr r0, [sp, #0x1b8]
	mov r3, #0x38
	lsl r1, r0, #0x3
	ldr r0, _0201A748 ; =0x00007FC0
	b _0201A74C
	nop
_0201A748: .word 0x00007FC0
_0201A74C:
	ldr r5, [sp, #0x5c]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x194]
	ldr r0, [sp, #0x1b8]
	str r2, [sp, #0x198]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A8C4 ; =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	ldr r6, [sp, #0x24]
	mov r4, #0x0
	str r2, [sp, #0x190]
	str r0, [sp, #0x18c]
_0201A774:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A8C4 ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x198]
	ldrb r1, [r7, r4]
	add r2, r3, r0
	cmp r1, #0x0
	beq _0201A7A0
	ldr r0, [sp, #0x194]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x2f4]
	cmp r0, #0x0
	beq _0201A7A0
	ldr r0, [sp, #0x190]
	add r2, r3, r0
	ldr r0, [sp, #0x18c]
	strb r1, [r0, r2]
_0201A7A0:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, #0x8
	blt _0201A774
	ldr r0, [sp, #0x2f4]
	cmp r0, #0x0
	beq _0201A7B8
	ldr r0, [sp, #0x1b8]
	add r0, r0, #0x2
	str r0, [sp, #0x1b8]
	b _0201A7BE
_0201A7B8:
	ldr r0, [sp, #0x1b8]
	add r0, r0, #0x1
	str r0, [sp, #0x1b8]
_0201A7BE:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x4]
	add r0, r0, #0x1
	sub r1, #0x8
	add r7, #0x8
	str r0, [sp, #0x10]
	cmp r0, r1
	blt _0201A72A
_0201A7CE:
	ldr r0, [sp, #0x1ec]
	mov r2, #0x0
	str r0, [sp, #0x2f0]
	add r0, #0xc0
	str r0, [sp, #0x2f0]
	mov r1, #0x1
_0201A7DA:
	ldr r0, [sp, #0x330]
	asr r0, r2
	tst r0, r1
	beq _0201A7E8
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A7E8:
	add r2, r2, #0x1
	cmp r2, #0x8
	blt _0201A7DA
	ldr r0, [sp, #0x44]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x1b0]
	mov r0, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	sub r0, #0x8
	cmp r0, #0x0
	ble _0201A8B6
	ldr r0, [sp, #0x5c]
	add r0, #0x8
	str r0, [sp, #0x5c]
_0201A808:
	ldr r1, [sp, #0x1b0]
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x8]
	asr r1, r0
	mov r0, #0x1
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	sub r7, #0x8
	mov r4, #0x0
	str r0, [sp, #0x1b4]
	ldr r5, [sp, #0x5c]
	cmp r7, #0x0
	ble _0201A88E
	ble _0201A88E
	add r0, r5, #0x0
	lsl r6, r0, #0x3
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x28]
	lsl r1, r0, #0x3
	ldr r0, _0201A8C4 ; =0x00007FC0
	mov r3, #0x38
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r0, [sp, #0x1a8]
	ldr r0, [sp, #0x48]
	str r2, [sp, #0x1ac]
	add r0, r0, #0x1
	lsl r1, r0, #0x3
	ldr r0, _0201A8C4 ; =0x00007FC0
	ldr r2, [sp, #0x28]
	and r0, r1
	mul r2, r0
	add r0, r1, #0x0
	and r0, r3
	str r2, [sp, #0x1a4]
	str r0, [sp, #0x1a0]
_0201A856:
	mov r0, #0x7
	add r1, r5, #0x0
	and r1, r0
	ldr r0, [sp, #0x278]
	add r1, r0, r1
	ldr r0, _0201A8C4 ; =0x00007FC0
	and r0, r6
	add r3, r1, r0
	ldr r0, [sp, #0x1ac]
	add r2, r3, r0
	ldr r0, [sp, #0x2f0]
	ldrb r1, [r0, r4]
	cmp r1, #0x0
	beq _0201A884
	ldr r0, [sp, #0x1a8]
	strb r1, [r2, r0]
	ldr r0, [sp, #0x1b4]
	cmp r0, #0x0
	beq _0201A884
	ldr r0, [sp, #0x1a4]
	add r2, r3, r0
	ldr r0, [sp, #0x1a0]
	strb r1, [r0, r2]
_0201A884:
	add r4, r4, #0x1
	add r6, #0x8
	add r5, r5, #0x1
	cmp r4, r7
	blt _0201A856
_0201A88E:
	ldr r0, [sp, #0x1b4]
	cmp r0, #0x0
	beq _0201A89C
	ldr r0, [sp, #0x48]
	add r0, r0, #0x2
	str r0, [sp, #0x48]
	b _0201A8A2
_0201A89C:
	ldr r0, [sp, #0x48]
	add r0, r0, #0x1
	str r0, [sp, #0x48]
_0201A8A2:
	ldr r0, [sp, #0x2f0]
	ldr r1, [sp, #0x4]
	add r0, #0x8
	str r0, [sp, #0x2f0]
	ldr r0, [sp, #0xc]
	sub r1, #0x8
	add r0, r0, #0x1
	str r0, [sp, #0xc]
	cmp r0, r1
	blt _0201A808
_0201A8B6:
	ldr r0, [sp, #0x1ec]
	bl FreeToHeap

	thumb_func_start FUN_0201A8BC
FUN_0201A8BC: ; 0x0201A8BC
	add sp, #0x1fc
	add sp, #0x118
	pop {r4-r7, pc}
	nop
_0201A8C4: .word 0x00007FC0

	thumb_func_start FUN_0201A8C8
FUN_0201A8C8: ; 0x0201A8C8
	push {r4-r6, lr}
	ldrb r6, [r0, #0x4]
	mov r5, #0x2c
	ldr r4, [r0, #0x0]
	mul r5, r6
	add r4, r4, r5
	ldrb r4, [r4, #0x1e]
	cmp r4, #0x0
	bne _0201A8E0
	bl FUN_0201A8E8
	pop {r4-r6, pc}
_0201A8E0:
	bl FUN_0201A9D4
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0201A8E8
FUN_0201A8E8: ; 0x0201A8E8
	push {r3-r7, lr}
	sub sp, #0x10
	add r6, r3, #0x0
	add r4, r0, #0x0
	add r0, r1, #0x0
	lsl r3, r6, #0x18
	lsl r1, r6, #0x10
	str r2, [sp, #0x0]
	orr r1, r3
	lsl r5, r6, #0x8
	orr r1, r5
	orr r1, r6
	str r1, [sp, #0x4]
	ldrb r1, [r4, #0x7]
	ldrb r3, [r4, #0x8]
	ldr r2, [r4, #0xc]
	str r1, [sp, #0x8]
	mul r1, r3
	lsl r1, r1, #0x5
	str r1, [sp, #0xc]
	cmp r0, #0x3
	bhi _0201A9CE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0201A920: ; jump table (using 16-bit offset)
	.short _0201A928 - _0201A920 - 2; case 0
	.short _0201A976 - _0201A920 - 2; case 1
	.short _0201A9CE - _0201A920 - 2; case 2
	.short _0201A9CE - _0201A920 - 2; case 3
_0201A928:
	add r0, r1, #0x0
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201A9CE
	mov r0, #0x7
	mov lr, r0
_0201A934:
	ldr r3, [sp, #0x0]
	mov r4, #0x0
	add r5, r7, #0x0
_0201A93A:
	mov r0, #0x7
	add r6, r3, #0x0
	and r6, r0
	add r1, r3, #0x0
	mov r0, lr
	bic r1, r0
	ldr r0, [sp, #0x8]
	mul r1, r0
	add r0, r6, #0x0
	orr r0, r1
	lsl r0, r0, #0x2
	add r1, r7, r0
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bge _0201A95C
	ldr r0, [r2, r1]
	b _0201A95E
_0201A95C:
	ldr r0, [sp, #0x4]
_0201A95E:
	add r4, r4, #0x1
	str r0, [r2, r5]
	add r3, r3, #0x1
	add r5, r5, #0x4
	cmp r4, #0x8
	blt _0201A93A
	ldr r0, [sp, #0xc]
	add r7, #0x20
	cmp r7, r0
	blt _0201A934
	add sp, #0x10
	pop {r3-r7, pc}
_0201A976:
	add r0, r1, #0x0
	sub r0, r0, #0x4
	add r2, r2, r0
	add r0, r1, #0x0
	mov r7, #0x0
	cmp r0, #0x0
	ble _0201A9CE
	mov r0, #0x7
	mov r12, r0
_0201A988:
	ldr r4, [sp, #0x0]
	mov r5, #0x0
	add r3, r7, #0x0
_0201A98E:
	mov r0, #0x7
	add r6, r4, #0x0
	and r6, r0
	add r1, r4, #0x0
	mov r0, r12
	bic r1, r0
	ldr r0, [sp, #0x8]
	mul r1, r0
	add r0, r6, #0x0
	orr r0, r1
	lsl r0, r0, #0x2
	add r1, r7, r0
	ldr r0, [sp, #0xc]
	cmp r1, r0
	bge _0201A9B6
	sub r0, r2, r1
	ldr r1, [r0, #0x0]
	sub r0, r2, r3
	str r1, [r0, #0x0]
	b _0201A9BC
_0201A9B6:
	ldr r0, [sp, #0x4]
	sub r1, r2, r3
	str r0, [r1, #0x0]
_0201A9BC:
	add r5, r5, #0x1
	add r4, r4, #0x1
	add r3, r3, #0x4
	cmp r5, #0x8
	blt _0201A98E
	ldr r0, [sp, #0xc]
	add r7, #0x20
	cmp r7, r0
	blt _0201A988
_0201A9CE:
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201A9D4
FUN_0201A9D4: ; 0x0201A9D4
	push {r3-r7, lr}
	sub sp, #0x20
	add r6, r3, #0x0
	add r4, r0, #0x0
	str r2, [sp, #0x0]
	lsl r2, r6, #0x18
	lsl r0, r6, #0x10
	orr r0, r2
	ldrb r2, [r4, #0x7]
	ldr r3, [r4, #0xc]
	lsl r5, r6, #0x8
	orr r0, r5
	ldrb r4, [r4, #0x8]
	str r2, [sp, #0x10]
	orr r0, r6
	mul r2, r4
	lsl r2, r2, #0x6
	str r2, [sp, #0x1c]
	cmp r1, #0x3
	bls _0201A9FE
	b _0201AB04
_0201A9FE:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201AA0A: ; jump table (using 16-bit offset)
	.short _0201AA12 - _0201AA0A - 2; case 0
	.short _0201AA80 - _0201AA0A - 2; case 1
	.short _0201AB04 - _0201AA0A - 2; case 2
	.short _0201AB04 - _0201AA0A - 2; case 3
_0201AA12:
	mov r1, #0x0
	str r1, [sp, #0xc]
	add r1, r2, #0x0
	cmp r1, #0x0
	ble _0201AB04
	add r1, r1, #0x4
	str r1, [sp, #0x14]
	mov r1, #0x7
	mov lr, r1
_0201AA24:
	ldr r4, [sp, #0x0]
	ldr r5, [sp, #0xc]
	mov r7, #0x0
_0201AA2A:
	mov r1, #0x7
	add r6, r4, #0x0
	and r6, r1
	add r2, r4, #0x0
	mov r1, lr
	bic r2, r1
	ldr r1, [sp, #0x10]
	mul r2, r1
	add r1, r6, #0x0
	orr r1, r2
	lsl r2, r1, #0x3
	ldr r1, [sp, #0xc]
	add r1, r1, r2
	ldr r2, [sp, #0x1c]
	cmp r1, r2
	bge _0201AA50
	ldr r2, [r3, r1]
	str r2, [r3, r5]
	b _0201AA52
_0201AA50:
	str r0, [r3, r5]
_0201AA52:
	add r2, r1, #0x4
	ldr r1, [sp, #0x14]
	cmp r2, r1
	bge _0201AA62
	ldr r2, [r3, r2]
	add r1, r5, #0x4
	str r2, [r3, r1]
	b _0201AA66
_0201AA62:
	add r1, r5, #0x4
	str r0, [r3, r1]
_0201AA66:
	add r7, r7, #0x1
	add r4, r4, #0x1
	add r5, #0x8
	cmp r7, #0x8
	blt _0201AA2A
	ldr r2, [sp, #0xc]
	ldr r1, [sp, #0x1c]
	add r2, #0x40
	str r2, [sp, #0xc]
	cmp r2, r1
	blt _0201AA24
	add sp, #0x20
	pop {r3-r7, pc}
_0201AA80:
	add r1, r2, #0x0
	sub r1, #0x8
	add r3, r3, r1
	mov r1, #0x0
	str r1, [sp, #0x8]
	add r1, r2, #0x0
	cmp r1, #0x0
	ble _0201AB04
_0201AA90:
	mov r1, #0x0
	str r1, [sp, #0x4]
	ldr r1, [sp, #0x1c]
	ldr r5, [sp, #0x0]
	sub r1, r1, #0x4
	str r1, [sp, #0x18]
	mov r1, #0x7
	ldr r4, [sp, #0x8]
	mov r12, r1
_0201AAA2:
	mov r1, #0x7
	add r6, r5, #0x0
	and r6, r1
	add r2, r5, #0x0
	mov r1, r12
	bic r2, r1
	ldr r1, [sp, #0x10]
	mul r2, r1
	add r1, r6, #0x0
	orr r1, r2
	lsl r2, r1, #0x3
	ldr r1, [sp, #0x8]
	add r6, r1, r2
	ldr r1, [sp, #0x1c]
	cmp r6, r1
	bge _0201AACC
	sub r1, r3, r6
	ldr r2, [r1, #0x0]
	sub r1, r3, r4
	str r2, [r1, #0x0]
	b _0201AAD0
_0201AACC:
	sub r1, r3, r4
	str r0, [r1, #0x0]
_0201AAD0:
	ldr r1, [sp, #0x18]
	sub r2, r6, #0x4
	cmp r2, r1
	bge _0201AAE4
	sub r1, r3, r2
	sub r2, r4, #0x4
	ldr r1, [r1, #0x0]
	sub r2, r3, r2
	str r1, [r2, #0x0]
	b _0201AAEA
_0201AAE4:
	sub r1, r4, #0x4
	sub r1, r3, r1
	str r0, [r1, #0x0]
_0201AAEA:
	ldr r1, [sp, #0x4]
	add r5, r5, #0x1
	add r1, r1, #0x1
	add r4, #0x8
	str r1, [sp, #0x4]
	cmp r1, #0x8
	blt _0201AAA2
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0x1c]
	add r2, #0x40
	str r2, [sp, #0x8]
	cmp r2, r1
	blt _0201AA90
_0201AB04:
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_0201AB08
FUN_0201AB08: ; 0x0201AB08
	ldrb r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_0201AB0C
FUN_0201AB0C: ; 0x0201AB0C
	ldrb r0, [r0, #0x7]
	bx lr

	thumb_func_start FUN_0201AB10
FUN_0201AB10: ; 0x0201AB10
	ldrb r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0201AB14
FUN_0201AB14: ; 0x0201AB14
	ldrb r0, [r0, #0x5]
	bx lr

	thumb_func_start FUN_0201AB18
FUN_0201AB18: ; 0x0201AB18
	ldrb r0, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0201AB1C
FUN_0201AB1C: ; 0x0201AB1C
	strb r1, [r0, #0x5]
	bx lr

	thumb_func_start FUN_0201AB20
FUN_0201AB20: ; 0x0201AB20
	strb r1, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0201AB24
FUN_0201AB24: ; 0x0201AB24
	strb r1, [r0, #0x9]
	bx lr

	thumb_func_start FUN_0201AB28
FUN_0201AB28: ; 0x0201AB28
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_020161A4
	add r1, sp, #0x0
	str r0, [r4, #0x0]
	bl FUN_020B0030
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_0201AB44
FUN_0201AB44: ; 0x0201AB44
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl FUN_020161A4
	add r1, sp, #0x0
	str r0, [r4, #0x0]
	bl FUN_020B0138
	ldr r0, [sp, #0x0]
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start FUN_0201AB60
FUN_0201AB60: ; 0x0201AB60
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_0201AC78
	add r0, r4, #0x0
	bl FUN_0201AB78
	mov r0, #0x0
	strh r0, [r4, #0x4]
	strh r0, [r4, #0x6]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201AB78
FUN_0201AB78: ; 0x0201AB78
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r1, [r4, #0x6]
	mov r0, #0x1
	tst r0, r1
	beq _0201AB92
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x8]
	ldr r3, [r4, #0xc]
	mov r0, #0x0
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AB92:
	ldrh r1, [r4, #0x6]
	mov r0, #0x2
	tst r0, r1
	beq _0201ABA8
	ldr r2, [r4, #0x3c]
	ldr r1, [r4, #0x34]
	ldr r3, [r4, #0x38]
	mov r0, #0x1
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201ABA8:
	ldrh r1, [r4, #0x6]
	mov r0, #0x4
	tst r0, r1
	beq _0201ABBE
	ldr r2, [r4, #0x68]
	ldr r1, [r4, #0x60]
	ldr r3, [r4, #0x64]
	mov r0, #0x2
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201ABBE:
	ldrh r1, [r4, #0x6]
	mov r0, #0x8
	tst r0, r1
	beq _0201ABE0
	add r2, r4, #0x0
	add r1, r4, #0x0
	add r2, #0x94
	add r3, r4, #0x0
	add r1, #0x8c
	ldr r2, [r2, #0x0]
	add r3, #0x90
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x3
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201ABE0:
	ldrh r1, [r4, #0x6]
	mov r0, #0x10
	tst r0, r1
	beq _0201AC02
	add r2, r4, #0x0
	add r1, r4, #0x0
	add r2, #0xc0
	add r3, r4, #0x0
	add r1, #0xb8
	ldr r2, [r2, #0x0]
	add r3, #0xbc
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x4
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC02:
	ldrh r1, [r4, #0x6]
	mov r0, #0x20
	tst r0, r1
	beq _0201AC24
	add r2, r4, #0x0
	add r1, r4, #0x0
	add r2, #0xec
	add r3, r4, #0x0
	add r1, #0xe4
	ldr r2, [r2, #0x0]
	add r3, #0xe8
	ldr r1, [r1, #0x0]
	ldr r3, [r3, #0x0]
	mov r0, #0x5
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC24:
	ldrh r0, [r4, #0x6]
	mov r3, #0x40
	tst r0, r3
	beq _0201AC44
	add r2, r3, #0x0
	add r1, r3, #0x0
	add r2, #0xd8
	add r1, #0xd0
	ldr r2, [r4, r2]
	add r3, #0xd4
	ldr r1, [r4, r1]
	ldr r3, [r4, r3]
	mov r0, #0x6
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC44:
	ldrh r0, [r4, #0x6]
	mov r3, #0x80
	tst r0, r3
	beq _0201AC64
	add r2, r3, #0x0
	add r1, r3, #0x0
	add r2, #0xc4
	add r1, #0xbc
	ldr r2, [r4, r2]
	add r3, #0xc0
	ldr r1, [r4, r1]
	ldr r3, [r4, r3]
	mov r0, #0x7
	lsl r2, r2, #0x1
	bl FUN_02017D68
_0201AC64:
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201AC68
FUN_0201AC68: ; 0x0201AC68
	ldrh r3, [r0, #0x6]
	mov r2, #0x1
	lsl r2, r1
	add r1, r3, #0x0
	orr r1, r2
	strh r1, [r0, #0x6]
	bx lr
	.balign 4

	thumb_func_start FUN_0201AC78
FUN_0201AC78: ; 0x0201AC78
	push {r4, lr}
	sub sp, #0x48
	add r4, r0, #0x0
	ldrh r1, [r4, #0x4]
	mov r0, #0x1
	tst r0, r1
	beq _0201AC9E
	ldr r1, [r4, #0x14]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	ldr r1, [r4, #0x18]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEB4 ; =0x04000010
	str r1, [r0, #0x0]
_0201AC9E:
	ldrh r1, [r4, #0x4]
	mov r0, #0x2
	tst r0, r1
	beq _0201ACBE
	ldr r1, [r4, #0x40]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	ldr r1, [r4, #0x44]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEB8 ; =0x04000014
	str r1, [r0, #0x0]
_0201ACBE:
	ldrh r1, [r4, #0x4]
	mov r0, #0x4
	tst r0, r1
	beq _0201AD1E
	add r0, r4, #0x0
	add r0, #0x74
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201ACEA
	ldr r1, [r4, #0x6c]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	ldr r1, [r4, #0x70]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEBC ; =0x04000018
	str r1, [r0, #0x0]
	b _0201AD1E
_0201ACEA:
	mov r0, #0x2
	str r0, [sp, #0x0]
	add r1, r4, #0x0
	add r1, #0x78
	add r3, r4, #0x0
	add r3, #0x80
	ldrh r1, [r1, #0x0]
	ldr r2, [r4, #0x7c]
	ldr r3, [r3, #0x0]
	add r0, sp, #0x38
	bl MTX22_2DAffine
	ldr r0, [r4, #0x6c]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x70]
	add r3, r4, #0x0
	str r0, [sp, #0x4]
	add r2, #0x84
	add r3, #0x88
	ldr r0, _0201AEC0 ; =0x04000020
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	add r1, sp, #0x38
	bl G2x_SetBGyAffine_
_0201AD1E:
	ldrh r1, [r4, #0x4]
	mov r0, #0x8
	tst r0, r1
	beq _0201AD8E
	add r0, r4, #0x0
	add r0, #0xa0
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201AD4E
	add r0, r4, #0x0
	add r2, r4, #0x0
	add r0, #0x98
	add r2, #0x9c
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _0201AEB0 ; =0x000001FF
	lsl r2, r2, #0x10
	and r0, r1
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AEC4 ; =0x0400001C
	str r1, [r0, #0x0]
	b _0201AD8E
_0201AD4E:
	mov r0, #0x2
	add r1, r4, #0x0
	str r0, [sp, #0x0]
	add r1, #0xa4
	add r2, r4, #0x0
	add r3, r4, #0x0
	add r2, #0xa8
	add r3, #0xac
	ldrh r1, [r1, #0x0]
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	add r0, sp, #0x28
	bl MTX22_2DAffine
	add r0, r4, #0x0
	add r0, #0x98
	ldr r0, [r0, #0x0]
	add r2, r4, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	add r0, #0x9c
	ldr r0, [r0, #0x0]
	add r3, r4, #0x0
	str r0, [sp, #0x4]
	add r2, #0xb0
	add r3, #0xb4
	ldr r0, _0201AEC8 ; =0x04000030
	ldr r2, [r2, #0x0]
	ldr r3, [r3, #0x0]
	add r1, sp, #0x28
	bl G2x_SetBGyAffine_
_0201AD8E:
	ldrh r1, [r4, #0x4]
	mov r0, #0x10
	tst r0, r1
	beq _0201ADB2
	add r0, r4, #0x0
	add r2, r4, #0x0
	add r0, #0xc4
	add r2, #0xc8
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _0201AEB0 ; =0x000001FF
	lsl r2, r2, #0x10
	and r0, r1
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AECC ; =0x04001010
	str r1, [r0, #0x0]
_0201ADB2:
	ldrh r1, [r4, #0x4]
	mov r0, #0x20
	tst r0, r1
	beq _0201ADD6
	add r0, r4, #0x0
	add r2, r4, #0x0
	add r0, #0xf0
	add r2, #0xf4
	ldr r2, [r2, #0x0]
	ldr r0, [r0, #0x0]
	ldr r1, _0201AEB0 ; =0x000001FF
	lsl r2, r2, #0x10
	and r0, r1
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AED0 ; =0x04001014
	str r1, [r0, #0x0]
_0201ADD6:
	ldrh r0, [r4, #0x4]
	mov r3, #0x40
	tst r0, r3
	beq _0201AE3E
	add r0, r3, #0x0
	add r0, #0xe4
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0201AE04
	ldr r1, _0201AEB0 ; =0x000001FF
	add r3, #0xdc
	add r2, r1, #0x0
	sub r2, #0xdf
	ldr r0, [r4, r3]
	ldr r2, [r4, r2]
	and r0, r1
	lsl r2, r2, #0x10
	lsl r1, r1, #0x10
	and r1, r2
	orr r1, r0
	ldr r0, _0201AED4 ; =0x04001018
	str r1, [r0, #0x0]
	b _0201AE3E
_0201AE04:
	mov r0, #0x2
	add r1, r3, #0x0
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r1, #0xe8
	add r2, #0xec
	add r3, #0xf0
	ldrh r1, [r4, r1]
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r0, sp, #0x18
	bl MTX22_2DAffine
	mov r3, #0x47
	lsl r3, r3, #0x2
	ldr r0, [r4, r3]
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r0, r3, #0x4
	ldr r0, [r4, r0]
	add r2, #0x18
	str r0, [sp, #0x4]
	add r3, #0x1c
	ldr r0, _0201AED8 ; =0x04001020
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r1, sp, #0x18
	bl G2x_SetBGyAffine_
_0201AE3E:
	ldrh r0, [r4, #0x4]
	mov r3, #0x80
	tst r0, r3
	beq _0201AEAC
	add r0, r3, #0x0
	add r0, #0xd0
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0201AE72
	add r3, #0xc8
	ldr r1, [r4, r3]
	ldr r0, _0201AEB0 ; =0x000001FF
	add r2, r1, #0x0
	add r1, r0, #0x0
	sub r1, #0xb3
	ldr r1, [r4, r1]
	and r2, r0
	lsl r1, r1, #0x10
	lsl r0, r0, #0x10
	and r0, r1
	add r1, r2, #0x0
	orr r1, r0
	ldr r0, _0201AEDC ; =0x0400101C
	add sp, #0x48
	str r1, [r0, #0x0]
	pop {r4, pc}
_0201AE72:
	mov r0, #0x2
	add r1, r3, #0x0
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r1, #0xd4
	add r2, #0xd8
	add r3, #0xdc
	ldrh r1, [r4, r1]
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r0, sp, #0x8
	bl MTX22_2DAffine
	mov r3, #0x52
	lsl r3, r3, #0x2
	ldr r0, [r4, r3]
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r0, r3, #0x4
	ldr r0, [r4, r0]
	add r2, #0x18
	str r0, [sp, #0x4]
	add r3, #0x1c
	ldr r0, _0201AEE0 ; =0x04001030
	ldr r2, [r4, r2]
	ldr r3, [r4, r3]
	add r1, sp, #0x8
	bl G2x_SetBGyAffine_
_0201AEAC:
	add sp, #0x48
	pop {r4, pc}
	.balign 4
_0201AEB0: .word 0x000001FF
_0201AEB4: .word 0x04000010
_0201AEB8: .word 0x04000014
_0201AEBC: .word 0x04000018
_0201AEC0: .word 0x04000020
_0201AEC4: .word 0x0400001C
_0201AEC8: .word 0x04000030
_0201AECC: .word 0x04001010
_0201AED0: .word 0x04001014
_0201AED4: .word 0x04001018
_0201AED8: .word 0x04001020
_0201AEDC: .word 0x0400101C
_0201AEE0: .word 0x04001030

	thumb_func_start FUN_0201AEE4
FUN_0201AEE4: ; 0x0201AEE4
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_02017B8C
	mov r0, #0x1
	ldrh r1, [r5, #0x4]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201AF08
FUN_0201AF08: ; 0x0201AF08
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_0201AF2C
	mov r0, #0x1
	ldrh r1, [r5, #0x4]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201AF2C
FUN_0201AF2C: ; 0x0201AF2C
	cmp r1, #0x0
	beq _0201AF3A
	cmp r1, #0x1
	beq _0201AF3E
	cmp r1, #0x2
	beq _0201AF46
	bx lr
_0201AF3A:
	strh r2, [r0, #0x18]
	bx lr
_0201AF3E:
	ldrh r1, [r0, #0x18]
	add r1, r1, r2
	strh r1, [r0, #0x18]
	bx lr
_0201AF46:
	ldrh r1, [r0, #0x18]
	sub r1, r1, r2
	strh r1, [r0, #0x18]
	bx lr
	.balign 4

	thumb_func_start FUN_0201AF50
FUN_0201AF50: ; 0x0201AF50
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x0
	mov r0, #0x2c
	add r1, #0x8
	mul r0, r4
	add r0, r1, r0
	add r1, r2, #0x0
	add r2, r3, #0x0
	bl FUN_0201AF74
	mov r0, #0x1
	ldrh r1, [r5, #0x4]
	lsl r0, r4
	orr r0, r1
	strh r0, [r5, #0x4]
	pop {r3-r5, pc}

	thumb_func_start FUN_0201AF74
FUN_0201AF74: ; 0x0201AF74
	sub r1, #0x9
	cmp r1, #0x5
	bhi _0201AFB8
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0201AF86: ; jump table (using 16-bit offset)
	.short _0201AF92 - _0201AF86 - 2; case 0
	.short _0201AF96 - _0201AF86 - 2; case 1
	.short _0201AF9E - _0201AF86 - 2; case 2
	.short _0201AFA6 - _0201AF86 - 2; case 3
	.short _0201AFAA - _0201AF86 - 2; case 4
	.short _0201AFB2 - _0201AF86 - 2; case 5
_0201AF92:
	str r2, [r0, #0x24]
	bx lr
_0201AF96:
	ldr r1, [r0, #0x24]
	add r1, r1, r2
	str r1, [r0, #0x24]
	bx lr
_0201AF9E:
	ldr r1, [r0, #0x24]
	sub r1, r1, r2
	str r1, [r0, #0x24]
	bx lr
_0201AFA6:
	str r2, [r0, #0x28]
	bx lr
_0201AFAA:
	ldr r1, [r0, #0x28]
	add r1, r1, r2
	str r1, [r0, #0x28]
	bx lr
_0201AFB2:
	ldr r1, [r0, #0x28]
	sub r1, r1, r2
	str r1, [r0, #0x28]
_0201AFB8:
	bx lr
	.balign 4

	thumb_func_start FUN_0201AFBC
FUN_0201AFBC: ; 0x0201AFBC
	push {r4-r7, lr}
	sub sp, #0x1c
	str r1, [sp, #0x0]
	add r7, r0, #0x0
	str r2, [sp, #0x4]
	ldr r0, [sp, #0x30]
	str r3, [sp, #0x8]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x0]
	add r4, r7, #0x0
	mov r1, #0x2c
	add r5, r0, #0x0
	mul r5, r1
	add r4, #0x8
	ldr r0, [r4, r5]
	cmp r0, #0x0
	bne _0201AFE4
	add sp, #0x1c
	mov r0, #0x0
	pop {r4-r7, pc}
_0201AFE4:
	ldr r0, [sp, #0x4]
	ldr r1, [sp, #0x8]
	add r2, r7, r5
	lsl r0, r0, #0x15
	lsl r1, r1, #0x15
	ldrb r2, [r2, #0x1d]
	lsr r0, r0, #0x18
	lsr r1, r1, #0x18
	bl FUN_02017FFC
	add r6, r0, #0x0
	ldr r0, [sp, #0x0]
	bl FUN_020187B0
	str r0, [sp, #0x18]
	ldr r1, [sp, #0x4]
	mov r0, #0x7
	and r1, r0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x8]
	and r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add r1, r7, r5
	str r0, [sp, #0x10]
	ldrb r0, [r1, #0x1e]
	cmp r0, #0x0
	bne _0201B096
	ldr r0, [r4, r5]
	mov r1, #0x40
	str r0, [sp, #0xc]
	ldr r0, [r7, #0x0]
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	lsl r0, r6, #0x1
	ldr r1, [sp, #0xc]
	mov r12, r0
	ldrh r0, [r1, r0]
	mov r3, #0x0
	mov r6, #0xf
	lsl r0, r0, #0x16
	lsr r1, r0, #0x11
	ldr r0, [sp, #0x18]
	add r2, r0, r1
_0201B042:
	ldrb r5, [r2, r3]
	lsl r0, r3, #0x1
	add r1, r4, r0
	and r5, r6
	strb r5, [r4, r0]
	ldrb r0, [r2, r3]
	asr r0, r0, #0x4
	strb r0, [r1, #0x1]
	add r0, r3, #0x1
	lsl r0, r0, #0x18
	lsr r3, r0, #0x18
	cmp r3, #0x20
	blo _0201B042
	ldr r2, [sp, #0xc]
	mov r1, r12
	ldrh r1, [r2, r1]
	add r0, r7, #0x0
	asr r2, r1, #0xa
	mov r1, #0x3
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r4, #0x0
	bl FUN_0201B118
	ldr r0, [sp, #0x10]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	ldrb r5, [r4, r0]
	add r0, r4, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x30]
	ldrh r2, [r0, #0x0]
	mov r0, #0x1
	add r1, r0, #0x0
	lsl r1, r5
	tst r1, r2
	beq _0201B10C
	add sp, #0x1c
	pop {r4-r7, pc}
_0201B096:
	ldrb r0, [r1, #0x1c]
	cmp r0, #0x1
	beq _0201B0E0
	ldr r0, [r7, #0x0]
	ldr r4, [r4, r5]
	mov r1, #0x40
	bl AllocFromHeapAtEnd
	lsl r6, r6, #0x1
	ldrh r1, [r4, r6]
	add r5, r0, #0x0
	lsl r1, r1, #0x16
	lsr r2, r1, #0x10
	ldr r1, [sp, #0x18]
	add r1, r1, r2
	mov r2, #0x40
	bl memcpy
	ldrh r1, [r4, r6]
	add r0, r7, #0x0
	asr r2, r1, #0xa
	mov r1, #0x3
	and r1, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r5, #0x0
	bl FUN_0201B118
	ldr r0, [sp, #0x10]
	lsl r1, r0, #0x3
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	ldrb r4, [r5, r0]
	add r0, r5, #0x0
	bl FreeToHeap
	b _0201B0F4
_0201B0E0:
	ldr r1, [r4, r5]
	ldr r0, [sp, #0x10]
	ldrb r1, [r1, r6]
	lsl r0, r0, #0x3
	lsl r2, r1, #0x6
	ldr r1, [sp, #0x14]
	add r1, r1, r2
	add r1, r0, r1
	ldr r0, [sp, #0x18]
	ldrb r4, [r0, r1]
_0201B0F4:
	ldr r0, [sp, #0x30]
	ldrh r2, [r0, #0x0]
	lsl r0, r2, #0x18
	lsr r1, r0, #0x18
	ldr r0, _0201B114 ; =0x0000FFFF
_0201B0FE:
	cmp r2, r0
	beq _0201B10C
	cmp r4, r1
	bne _0201B0FE
	add sp, #0x1c
	mov r0, #0x1
	pop {r4-r7, pc}
_0201B10C:
	mov r0, #0x0
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_0201B114: .word 0x0000FFFF

	thumb_func_start FUN_0201B118
FUN_0201B118: ; 0x0201B118
	push {r3-r7, lr}
	str r1, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r7, r2, #0x0
	cmp r1, #0x0
	beq _0201B1A4
	ldr r0, [r0, #0x0]
	mov r1, #0x40
	bl AllocFromHeapAtEnd
	add r4, r0, #0x0
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	tst r0, r1
	beq _0201B166
	mov r0, #0x0
	mov r5, #0x7
_0201B13A:
	lsl r3, r0, #0x3
	add r2, r7, r3
	mov r1, #0x0
	add r3, r4, r3
_0201B142:
	sub r6, r5, r1
	ldrb r6, [r2, r6]
	strb r6, [r3, r1]
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	cmp r1, #0x8
	blo _0201B142
	add r0, r0, #0x1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x8
	blo _0201B13A
	add r0, r7, #0x0
	add r1, r4, #0x0
	mov r2, #0x40
	bl memcpy
_0201B166:
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	tst r0, r1
	beq _0201B19E
	mov r5, #0x0
	mov r6, #0x7
_0201B172:
	lsl r0, r5, #0x3
	add r3, r4, r0
	sub r0, r6, r5
	lsl r0, r0, #0x3
	add r2, r7, r0
	mov r1, #0x8
_0201B17E:
	ldrb r0, [r2, #0x0]
	add r2, r2, #0x1
	strb r0, [r3, #0x0]
	add r3, r3, #0x1
	sub r1, r1, #0x1
	bne _0201B17E
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x8
	blo _0201B172
	add r0, r7, #0x0
	add r1, r4, #0x0
	mov r2, #0x40
	bl memcpy
_0201B19E:
	add r0, r4, #0x0
	bl FreeToHeap
_0201B1A4:
	pop {r3-r7, pc}
	.balign 4
