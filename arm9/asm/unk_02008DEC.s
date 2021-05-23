    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02008DEC
FUN_02008DEC: ; 0x02008DEC
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	str r2, [sp, #0x0]
	add r0, r2, #0x0
	mov r1, #0x14
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	bl FUN_02020C44
	str r0, [r4, #0x0]
	mov r0, #0xc
	add r7, r5, #0x0
	mul r7, r0
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl AllocFromHeap
	mov r1, #0x0
	add r2, r7, #0x0
	str r0, [r4, #0x4]
	bl memset
	str r5, [r4, #0x8]
	mov r0, #0x0
	str r0, [r4, #0xc]
	str r6, [r4, #0x10]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02008E2C
FUN_02008E2C: ; 0x02008E2C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02008E36
	bl ErrorHandling
_02008E36:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02008E40
	bl ErrorHandling
_02008E40:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	bne _02008E4A
	bl ErrorHandling
_02008E4A:
	add r0, r4, #0x0
	bl FUN_020094C4
	ldr r0, [r4, #0x0]
	bl FUN_02020C90
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start FUN_02008E6C
FUN_02008E6C: ; 0x02008E6C
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r5, #0x0
	bne _02008E80
	bl ErrorHandling
_02008E80:
	cmp r4, #0x0
	bne _02008E88
	bl ErrorHandling
_02008E88:
	ldr r0, [r4, #0x4]
	cmp r0, r6
	bgt _02008E92
	bl ErrorHandling
_02008E92:
	ldr r1, [r5, #0x10]
	ldr r0, [r4, #0x8]
	cmp r1, r0
	beq _02008E9E
	bl ErrorHandling
_02008E9E:
	add r0, r5, #0x0
	bl FUN_020097D0
	str r0, [sp, #0x1c]
	cmp r0, #0x0
	bne _02008EAE
	bl ErrorHandling
_02008EAE:
	ldrb r0, [r4, #0xc]
	cmp r0, #0x0
	bne _02008EEA
	ldr r2, [r4, #0x0]
	mov r0, #0x4c
	add r1, r6, #0x0
	mul r1, r0
	add r6, r2, r1
	ldr r1, [r2, r1]
	add r0, r5, #0x0
	bl FUN_0200945C
	cmp r0, #0x1
	beq _02008ECE
	bl ErrorHandling
_02008ECE:
	ldr r0, [r6, #0x44]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x0]
	ldr r0, [r6, #0x48]
	add r2, r6, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	str r0, [sp, #0x8]
	str r7, [sp, #0xc]
	ldr r3, [r6, #0x0]
	add r0, r5, #0x0
	bl FUN_0200994C
	b _02008F28
_02008EEA:
	mov r0, #0x18
	ldr r1, [r4, #0x0]
	mul r0, r6
	add r6, r1, r0
	ldr r1, [r6, #0xc]
	add r0, r5, #0x0
	bl FUN_0200945C
	cmp r0, #0x1
	beq _02008F02
	bl ErrorHandling
_02008F02:
	ldr r0, [r6, #0x8]
	ldr r1, [sp, #0x1c]
	str r0, [sp, #0x0]
	ldr r0, [r6, #0xc]
	str r0, [sp, #0x4]
	ldr r0, [r6, #0x10]
	str r0, [sp, #0x8]
	ldr r0, [r6, #0x14]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x8]
	str r0, [sp, #0x10]
	str r7, [sp, #0x14]
	mov r0, #0x0
	str r0, [sp, #0x18]
	ldr r2, [r6, #0x0]
	ldr r3, [r6, #0x4]
	add r0, r5, #0x0
	bl FUN_02009978
_02008F28:
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x1c]
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02008F34
FUN_02008F34: ; 0x02008F34
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _02008F48
	bl ErrorHandling
_02008F48:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _02008F52
	bl ErrorHandling
_02008F52:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _02008F60
	bl ErrorHandling
_02008F60:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	mov r1, #0x0
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x40]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02009978
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02008F90
FUN_02008F90: ; 0x02008F90
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _02008FA4
	bl ErrorHandling
_02008FA4:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _02008FAE
	bl ErrorHandling
_02008FAE:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _02008FBC
	bl ErrorHandling
_02008FBC:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x40]
	add r1, r6, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x44]
	add r2, r7, #0x0
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_02009978
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02008FEC
FUN_02008FEC: ; 0x02008FEC
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _02009000
	bl ErrorHandling
_02009000:
	ldr r0, [r5, #0x10]
	cmp r0, #0x1
	beq _0200900A
	bl ErrorHandling
_0200900A:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _02009018
	bl ErrorHandling
_02009018:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r1, r6, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x44]
	add r2, r7, #0x0
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_02009978
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200904C
FUN_0200904C: ; 0x0200904C
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _02009060
	bl ErrorHandling
_02009060:
	ldr r0, [r5, #0x10]
	cmp r0, #0x1
	beq _0200906A
	bl ErrorHandling
_0200906A:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _02009078
	bl ErrorHandling
_02009078:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r1, r6, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x44]
	add r2, r7, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_02009978
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020090AC
FUN_020090AC: ; 0x020090AC
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _020090C0
	bl ErrorHandling
_020090C0:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _020090CE
	bl ErrorHandling
_020090CE:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	ldr r0, [sp, #0x3c]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x40]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02009978
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_020090FC
FUN_020090FC: ; 0x020090FC
	push {r4-r7, lr}
	sub sp, #0x24
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x1c]
	str r3, [sp, #0x20]
	cmp r5, #0x0
	bne _02009110
	bl ErrorHandling
_02009110:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _0200911A
	bl ErrorHandling
_0200911A:
	cmp r4, #0x0
	bne _02009122
	bl ErrorHandling
_02009122:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _0200912C
	bl ErrorHandling
_0200912C:
	add r0, r4, #0x0
	bl FUN_02009530
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020095E4
	add r7, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02009490
	ldr r0, [sp, #0x38]
	mov r1, #0x0
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	str r7, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x3c]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02009978
	add sp, #0x24
	pop {r4-r7, pc}

	thumb_func_start FUN_02009168
FUN_02009168: ; 0x02009168
	push {r3-r7, lr}
	sub sp, #0x28
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x1c]
	str r3, [sp, #0x20]
	cmp r5, #0x0
	bne _0200917C
	bl ErrorHandling
_0200917C:
	ldr r0, [r5, #0x10]
	cmp r0, #0x1
	beq _02009186
	bl ErrorHandling
_02009186:
	cmp r4, #0x0
	bne _0200918E
	bl ErrorHandling
_0200918E:
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	beq _02009198
	bl ErrorHandling
_02009198:
	add r0, r4, #0x0
	bl FUN_02009530
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_020095E4
	add r7, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02009610
	str r0, [sp, #0x24]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02009490
	ldr r0, [sp, #0x40]
	ldr r2, [sp, #0x1c]
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	ldr r0, [sp, #0x24]
	str r7, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x44]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02009978
	add sp, #0x28
	pop {r3-r7, pc}

	thumb_func_start FUN_020091E0
FUN_020091E0: ; 0x020091E0
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _020091F4
	bl ErrorHandling
_020091F4:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _020091FE
	bl ErrorHandling
_020091FE:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _0200920C
	bl ErrorHandling
_0200920C:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	mov r1, #0x0
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x40]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020099B0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0200923C
FUN_0200923C: ; 0x0200923C
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _02009250
	bl ErrorHandling
_02009250:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	beq _0200925A
	bl ErrorHandling
_0200925A:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _02009268
	bl ErrorHandling
_02009268:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x40]
	add r1, r6, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x44]
	add r2, r7, #0x0
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_020099B0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_02009298
FUN_02009298: ; 0x02009298
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _020092AC
	bl ErrorHandling
_020092AC:
	ldr r0, [r5, #0x10]
	cmp r0, #0x1
	beq _020092B6
	bl ErrorHandling
_020092B6:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _020092C4
	bl ErrorHandling
_020092C4:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r1, r6, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x44]
	add r2, r7, #0x0
	str r0, [sp, #0x14]
	mov r0, #0x0
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_020099B0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020092F8
FUN_020092F8: ; 0x020092F8
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _0200930C
	bl ErrorHandling
_0200930C:
	ldr r0, [r5, #0x10]
	cmp r0, #0x1
	beq _02009316
	bl ErrorHandling
_02009316:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _02009324
	bl ErrorHandling
_02009324:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x3c]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x40]
	add r1, r6, #0x0
	str r0, [sp, #0xc]
	mov r0, #0x1
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x44]
	add r2, r7, #0x0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x48]
	str r0, [sp, #0x18]
	add r0, r5, #0x0
	bl FUN_020099B0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02009358
FUN_02009358: ; 0x02009358
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r4, r3, #0x0
	str r2, [sp, #0x1c]
	cmp r5, #0x0
	bne _0200936C
	bl ErrorHandling
_0200936C:
	add r0, r5, #0x0
	bl FUN_020097D0
	add r6, r0, #0x0
	bne _0200937A
	bl ErrorHandling
_0200937A:
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x0
	str r1, [sp, #0x8]
	ldr r0, [sp, #0x3c]
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x40]
	ldr r3, [sp, #0x1c]
	str r0, [sp, #0x14]
	str r1, [sp, #0x18]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020099B0
	ldr r0, [r5, #0xc]
	add r0, r0, #0x1
	str r0, [r5, #0xc]
	add r0, r6, #0x0
	add sp, #0x20
	pop {r3-r7, pc}

	thumb_func_start FUN_020093A8
FUN_020093A8: ; 0x020093A8
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r5, #0x0
	bne _020093BC
	bl ErrorHandling
_020093BC:
	cmp r4, #0x0
	bne _020093C4
	bl ErrorHandling
_020093C4:
	str r6, [sp, #0x0]
	str r7, [sp, #0x4]
	ldr r3, [r4, #0x4]
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl FUN_020093DC
	ldr r0, [r4, #0x4]
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020093DC
FUN_020093DC: ; 0x020093DC
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	add r5, r2, #0x0
	ldr r0, [sp, #0x24]
	add r7, r5, r3
	str r1, [sp, #0x4]
	ldr r4, [sp, #0x20]
	str r0, [sp, #0x24]
	cmp r5, r7
	bge _02009420
	add r6, r4, #0x0
	add r6, #0x8
_020093F6:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	ldr r3, [sp, #0x24]
	add r2, r5, #0x0
	bl FUN_02008E6C
	cmp r4, #0x0
	beq _0200941A
	ldr r2, [r4, #0x8]
	ldr r1, [r4, #0x4]
	cmp r1, r2
	ble _0200941A
	ldr r1, [r4, #0x0]
	lsl r2, r2, #0x2
	str r0, [r1, r2]
	ldr r0, [r6, #0x0]
	add r0, r0, #0x1
	str r0, [r6, #0x0]
_0200941A:
	add r5, r5, #0x1
	cmp r5, r7
	blt _020093F6
_02009420:
	add sp, #0x8
	pop {r3-r7, pc}

	thumb_func_start FUN_02009424
FUN_02009424: ; 0x02009424
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0xc
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	lsl r1, r5, #0x2
	bl AllocFromHeap
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02009448
FUN_02009448: ; 0x02009448
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0200945C
FUN_0200945C: ; 0x0200945C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0200946A
	bl ErrorHandling
_0200946A:
	ldr r0, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02020CB0
	pop {r3-r5, pc}

	thumb_func_start FUN_02009474
FUN_02009474: ; 0x02009474
	push {r4, lr}
	add r4, r0, #0x0
	bne _0200947E
	bl ErrorHandling
_0200947E:
	add r0, r4, #0x0
	bl FUN_02009920
	ldr r0, [r4, #0x0]
	mov r1, #0x0
	bl FUN_02020E1C
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02009490
FUN_02009490: ; 0x02009490
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0200949E
	bl ErrorHandling
_0200949E:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _020094A8
	bl ErrorHandling
_020094A8:
	add r0, r4, #0x0
	bl FUN_02009920
	ldr r0, [r5, #0x0]
	ldr r1, [r4, #0x0]
	bl FUN_02020D68
	mov r0, #0x0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	sub r0, r0, #0x1
	str r0, [r5, #0xc]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020094C4
FUN_020094C4: ; 0x020094C4
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	mov r6, #0x0
	cmp r0, #0x0
	ble _020094EC
	add r4, r6, #0x0
_020094D2:
	ldr r1, [r5, #0x4]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	beq _020094E2
	add r0, r5, #0x0
	add r1, r1, r4
	bl FUN_02009490
_020094E2:
	ldr r0, [r5, #0x8]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _020094D2
_020094EC:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020094F0
FUN_020094F0: ; 0x020094F0
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r7, r1, #0x0
	cmp r5, #0x0
	bne _020094FE
	bl ErrorHandling
_020094FE:
	ldr r0, [r5, #0x8]
	mov r6, #0x0
	cmp r0, #0x0
	ble _0200952C
	add r4, r6, #0x0
_02009508:
	ldr r0, [r5, #0x4]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009522
	bl FUN_02020E38
	cmp r0, r7
	bne _02009522
	mov r0, #0xc
	ldr r1, [r5, #0x4]
	mul r0, r6
	add r0, r1, r0
	pop {r3-r7, pc}
_02009522:
	ldr r0, [r5, #0x8]
	add r6, r6, #0x1
	add r4, #0xc
	cmp r6, r0
	blt _02009508
_0200952C:
	mov r0, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02009530
FUN_02009530: ; 0x02009530
	push {r4, lr}
	add r4, r0, #0x0
	bne _0200953A
	bl ErrorHandling
_0200953A:
	ldr r0, [r4, #0x0]
	bl FUN_02020E38
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02009544
FUN_02009544: ; 0x02009544
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02009552
	bl ErrorHandling
_02009552:
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_0200955C
FUN_0200955C: ; 0x0200955C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	beq _0200956A
	bl ErrorHandling
_0200956A:
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_02009574
FUN_02009574: ; 0x02009574
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x2
	beq _02009582
	bl ErrorHandling
_02009582:
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_0200958C
FUN_0200958C: ; 0x0200958C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	beq _0200959A
	bl ErrorHandling
_0200959A:
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020095A4
FUN_020095A4: ; 0x020095A4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x4
	beq _020095B2
	bl ErrorHandling
_020095B2:
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020095BC
FUN_020095BC: ; 0x020095BC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x5
	beq _020095CA
	bl ErrorHandling
_020095CA:
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x0]
	pop {r4, pc}

	thumb_func_start FUN_020095D4
FUN_020095D4: ; 0x020095D4
	push {r4, lr}
	add r4, r0, #0x0
	bne _020095DE
	bl ErrorHandling
_020095DE:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020095E4
FUN_020095E4: ; 0x020095E4
	push {r4, lr}
	add r4, r0, #0x0
	bne _020095EE
	bl ErrorHandling
_020095EE:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	bne _020095FE
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x4]
	pop {r4, pc}
_020095FE:
	cmp r0, #0x1
	bne _0200960C
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x4]
	pop {r4, pc}
_0200960C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02009610
FUN_02009610: ; 0x02009610
	push {r4, lr}
	add r4, r0, #0x0
	bne _0200961A
	bl ErrorHandling
_0200961A:
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _0200962A
	add r0, r4, #0x0
	bl FUN_02009934
	ldr r0, [r0, #0x8]
	pop {r4, pc}
_0200962A:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02009630
FUN_02009630: ; 0x02009630
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0200963E
	bl ErrorHandling
_0200963E:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _0200964C
	add r0, r5, #0x0
	bl FUN_02009934
	str r4, [r0, #0x4]
_0200964C:
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _0200965A
	add r0, r5, #0x0
	bl FUN_02009934
	str r4, [r0, #0x4]
_0200965A:
	pop {r3-r5, pc}

	thumb_func_start FUN_0200965C
FUN_0200965C: ; 0x0200965C
	mov r0, #0x10
	bx lr

	thumb_func_start FUN_02009660
FUN_02009660: ; 0x02009660
	lsl r1, r1, #0x4
	add r0, r0, r1
	bx lr
	.balign 4

	thumb_func_start FUN_02009668
FUN_02009668: ; 0x02009668
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x0
	bne _02009678
	bl ErrorHandling
_02009678:
	ldr r0, [r5, #0x0]
	str r0, [r4, #0x8]
	mov r0, #0x1
	strb r0, [r4, #0xc]
	add r0, r5, #0x4
	bl FUN_020099E8
	add r2, r0, #0x0
	str r0, [r4, #0x4]
	cmp r2, #0x0
	ble _0200969A
	mov r1, #0x18
	add r0, r6, #0x0
	mul r1, r2
	bl AllocFromHeap
	b _0200969C
_0200969A:
	mov r0, #0x0
_0200969C:
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020096B0
	ldr r3, [r4, #0x4]
	mov r2, #0x18
	add r1, r5, #0x4
	mul r2, r3
	bl memcpy
_020096B0:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020096B4
FUN_020096B4: ; 0x020096B4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020096C2
	bl FreeToHeap
_020096C2:
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020096CC
FUN_020096CC: ; 0x020096CC
	push {r4, lr}
	add r4, r0, #0x0
	bne _020096D6
	bl ErrorHandling
_020096D6:
	ldr r0, [r4, #0x4]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020096DC
FUN_020096DC: ; 0x020096DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020096EA
	bl ErrorHandling
_020096EA:
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bgt _020096F4
	bl ErrorHandling
_020096F4:
	ldrb r0, [r5, #0xc]
	ldr r1, [r5, #0x0]
	cmp r0, #0x0
	bne _02009704
	mov r0, #0x4c
	mul r0, r4
	ldr r0, [r1, r0]
	pop {r3-r5, pc}
_02009704:
	mov r0, #0x18
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0xc]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02009710
FUN_02009710: ; 0x02009710
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0200971E
	bl ErrorHandling
_0200971E:
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bgt _02009728
	bl ErrorHandling
_02009728:
	ldrb r0, [r5, #0xc]
	cmp r0, #0x1
	bne _02009738
	mov r0, #0x18
	ldr r1, [r5, #0x0]
	mul r0, r4
	add r0, r1, r0
	ldr r6, [r0, #0x4]
_02009738:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0200973C
FUN_0200973C: ; 0x0200973C
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _0200974A
	bl ErrorHandling
_0200974A:
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bgt _02009754
	bl ErrorHandling
_02009754:
	ldrb r0, [r5, #0xc]
	cmp r0, #0x1
	bne _02009764
	mov r0, #0x18
	ldr r1, [r5, #0x0]
	mul r0, r4
	add r0, r1, r0
	ldr r6, [r0, #0x8]
_02009764:
	add r0, r6, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02009768
FUN_02009768: ; 0x02009768
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02009776
	bl ErrorHandling
_02009776:
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bgt _02009780
	bl ErrorHandling
_02009780:
	ldrb r0, [r5, #0xc]
	ldr r1, [r5, #0x0]
	cmp r0, #0x0
	bne _02009792
	mov r0, #0x4c
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0x44]
	pop {r3-r5, pc}
_02009792:
	mov r0, #0x18
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0x10]
	pop {r3-r5, pc}

	thumb_func_start FUN_0200979C
FUN_0200979C: ; 0x0200979C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _020097AA
	bl ErrorHandling
_020097AA:
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bgt _020097B4
	bl ErrorHandling
_020097B4:
	ldrb r0, [r5, #0xc]
	ldr r1, [r5, #0x0]
	cmp r0, #0x0
	bne _020097C6
	mov r0, #0x4c
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0x48]
	pop {r3-r5, pc}
_020097C6:
	mov r0, #0x18
	mul r0, r4
	add r0, r1, r0
	ldr r0, [r0, #0x14]
	pop {r3-r5, pc}

	thumb_func_start FUN_020097D0
FUN_020097D0: ; 0x020097D0
	push {r3-r4}
	ldr r4, [r0, #0x8]
	mov r1, #0x0
	cmp r4, #0x0
	ble _020097F6
	ldr r3, [r0, #0x4]
	add r2, r3, #0x0
_020097DE:
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _020097EE
	mov r0, #0xc
	mul r0, r1
	add r0, r3, r0
	pop {r3-r4}
	bx lr
_020097EE:
	add r1, r1, #0x1
	add r2, #0xc
	cmp r1, r4
	blt _020097DE
_020097F6:
	mov r0, #0x0
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_020097FC
FUN_020097FC: ; 0x020097FC
	push {r3-r7, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x0]
	ldr r5, [sp, #0x18]
	bl FUN_02020E0C
	cmp r6, #0x5
	bhi _0200986A
	add r1, r6, r6
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0200981E: ; jump table (using 16-bit offset)
	.short _0200982A - _0200981E - 2; case 0
	.short _02009836 - _0200981E - 2; case 1
	.short _02009844 - _0200981E - 2; case 2
	.short _0200984E - _0200981E - 2; case 3
	.short _02009858 - _0200981E - 2; case 4
	.short _02009862 - _0200981E - 2; case 5
_0200982A:
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0200986C
	str r0, [r4, #0x8]
	pop {r3-r7, pc}
_02009836:
	ldr r2, [sp, #0x0]
	add r1, r7, #0x0
	add r3, r5, #0x0
	bl FUN_0200988C
	str r0, [r4, #0x8]
	pop {r3-r7, pc}
_02009844:
	add r1, r5, #0x0
	bl FUN_020098B0
	str r0, [r4, #0x8]
	pop {r3-r7, pc}
_0200984E:
	add r1, r5, #0x0
	bl FUN_020098CC
	str r0, [r4, #0x8]
	pop {r3-r7, pc}
_02009858:
	add r1, r5, #0x0
	bl FUN_020098E8
	str r0, [r4, #0x8]
	pop {r3-r7, pc}
_02009862:
	add r1, r5, #0x0
	bl FUN_02009904
	str r0, [r4, #0x8]
_0200986A:
	pop {r3-r7, pc}

	thumb_func_start FUN_0200986C
FUN_0200986C: ; 0x0200986C
	push {r4-r6, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x8
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedCharacterData
	str r5, [r4, #0x4]
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0200988C
FUN_0200988C: ; 0x0200988C
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0xc
	add r6, r2, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedPaletteData
	str r5, [r4, #0x4]
	str r6, [r4, #0x8]
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020098B0
FUN_020098B0: ; 0x020098B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedCellBank
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020098CC
FUN_020098CC: ; 0x020098CC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedAnimBank
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020098E8
FUN_020098E8: ; 0x020098E8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedMultiCellBank
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02009904
FUN_02009904: ; 0x02009904
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x4
	bl AllocFromHeap
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl NNS_G2dGetUnpackedMCAnimBank
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02009920
FUN_02009920: ; 0x02009920
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0200992E
	bl FreeToHeap
_0200992E:
	mov r0, #0x0
	str r0, [r4, #0x8]
	pop {r4, pc}

	thumb_func_start FUN_02009934
FUN_02009934: ; 0x02009934
	push {r4, lr}
	add r4, r0, #0x0
	bne _0200993E
	bl ErrorHandling
_0200993E:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _02009948
	bl ErrorHandling
_02009948:
	ldr r0, [r4, #0x8]
	pop {r4, pc}

	thumb_func_start FUN_0200994C
FUN_0200994C: ; 0x0200994C
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	add r1, r2, #0x0
	add r2, r3, #0x0
	ldr r0, [r0, #0x0]
	ldr r3, [sp, #0x1c]
	bl FUN_02020D10
	str r0, [r4, #0x0]
	ldr r1, [sp, #0x18]
	ldr r0, [sp, #0x1c]
	str r1, [r4, #0x4]
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	add r0, r4, #0x0
	bl FUN_020097FC
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4

	thumb_func_start FUN_02009978
FUN_02009978: ; 0x02009978
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x28]
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r0, r2, #0x0
	add r1, r3, #0x0
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x24]
	bl UncompressFromNarc
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x14]
	bl FUN_02020CD4
	str r0, [r4, #0x0]
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x24]
	str r1, [r4, #0x4]
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r4, #0x0
	bl FUN_020097FC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020099B0
FUN_020099B0: ; 0x020099B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x28]
	add r4, r1, #0x0
	str r0, [sp, #0x0]
	add r0, r2, #0x0
	add r1, r3, #0x0
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x24]
	bl FUN_02009A04
	add r1, r0, #0x0
	ldr r0, [r5, #0x0]
	ldr r2, [sp, #0x14]
	bl FUN_02020CD4
	str r0, [r4, #0x0]
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #0x24]
	str r1, [r4, #0x4]
	str r0, [sp, #0x0]
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	add r0, r4, #0x0
	bl FUN_020097FC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020099E8
FUN_020099E8: ; 0x020099E8
	mov r3, #0x0
	ldr r2, [r0, #0x0]
	sub r1, r3, #0x2
	cmp r2, r1
	beq _020099FE
	sub r1, r3, #0x2
_020099F4:
	add r0, #0x18
	ldr r2, [r0, #0x0]
	add r3, r3, #0x1
	cmp r2, r1
	bne _020099F4
_020099FE:
	add r0, r3, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02009A04
FUN_02009A04: ; 0x02009A04
	push {r4-r6, lr}
	add r6, r3, #0x0
	add r5, r2, #0x0
	add r2, r6, #0x0
	bl NARC_AllocAndReadWholeMember
	add r4, r0, #0x0
	beq _02009A4A
	cmp r5, #0x0
	beq _02009A4A
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _02009A2A
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	lsr r1, r1, #0x8
	bl AllocFromHeap
	b _02009A34
_02009A2A:
	ldr r1, [r4, #0x0]
	add r0, r6, #0x0
	lsr r1, r1, #0x8
	bl AllocFromHeapAtEnd
_02009A34:
	add r5, r0, #0x0
	cmp r5, #0x0
	beq _02009A48
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl MI_UncompressLZ8
	add r0, r4, #0x0
	bl FreeToHeap
_02009A48:
	add r4, r5, #0x0
_02009A4A:
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02009A50
FUN_02009A50: ; 0x02009A50
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bne _02009A5C
	bl ErrorHandling
_02009A5C:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009A6A
	bl ErrorHandling
_02009A6A:
	add r0, r4, #0x0
	bl FUN_02009544
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020095E4
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02009530
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	add r0, sp, #0x0
	bl FUN_0201D1F8
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02009A90
FUN_02009A90: ; 0x02009A90
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _02009A9A
	bl ErrorHandling
_02009A9A:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02009AC2
	add r4, r6, #0x0
_02009AA4:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009AB8
	bl FUN_02009A50
	cmp r0, #0x0
	bne _02009AB8
	bl ErrorHandling
_02009AB8:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02009AA4
_02009AC2:
	pop {r4-r6, pc}

	thumb_func_start FUN_02009AC4
FUN_02009AC4: ; 0x02009AC4
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bne _02009AD0
	bl ErrorHandling
_02009AD0:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009ADE
	bl ErrorHandling
_02009ADE:
	add r0, r4, #0x0
	bl FUN_02009544
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020095E4
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02009530
	str r0, [sp, #0x8]
	mov r0, #0x0
	str r0, [sp, #0xc]
	add r0, sp, #0x0
	bl FUN_0201D250
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02009B04
FUN_02009B04: ; 0x02009B04
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bne _02009B10
	bl ErrorHandling
_02009B10:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009B1E
	bl ErrorHandling
_02009B1E:
	add r0, r4, #0x0
	bl FUN_02009544
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020095E4
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02009530
	str r0, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	add r0, sp, #0x0
	bl FUN_0201D1F8
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02009B44
FUN_02009B44: ; 0x02009B44
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _02009B4E
	bl ErrorHandling
_02009B4E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02009B76
	add r4, r6, #0x0
_02009B58:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009B6C
	bl FUN_02009B04
	cmp r0, #0x0
	bne _02009B6C
	bl ErrorHandling
_02009B6C:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02009B58
_02009B76:
	pop {r4-r6, pc}

	thumb_func_start FUN_02009B78
FUN_02009B78: ; 0x02009B78
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bne _02009B84
	bl ErrorHandling
_02009B84:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009B92
	bl ErrorHandling
_02009B92:
	add r0, r4, #0x0
	bl FUN_02009544
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020095E4
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02009530
	str r0, [sp, #0x8]
	mov r0, #0x1
	str r0, [sp, #0xc]
	add r0, sp, #0x0
	bl FUN_0201D250
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02009BB8
FUN_02009BB8: ; 0x02009BB8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _02009BC6
	bl ErrorHandling
_02009BC6:
	cmp r5, #0x0
	bne _02009BCE
	bl ErrorHandling
_02009BCE:
	add r0, r4, #0x0
	bl FUN_02009530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02009544
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0201D2DC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02009BE8
FUN_02009BE8: ; 0x02009BE8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bne _02009BF2
	bl ErrorHandling
_02009BF2:
	add r0, r5, #0x0
	bl FUN_02009530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02009544
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0201D2DC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02009C0C
FUN_02009C0C: ; 0x02009C0C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02009C16
	bl ErrorHandling
_02009C16:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009C24
	bl ErrorHandling
_02009C24:
	add r0, r4, #0x0
	bl FUN_02009530
	bl FUN_0201D324
	pop {r4, pc}

	thumb_func_start FUN_02009C30
FUN_02009C30: ; 0x02009C30
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _02009C3A
	bl ErrorHandling
_02009C3A:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02009C5A
	add r4, r6, #0x0
_02009C44:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009C50
	bl FUN_02009C0C
_02009C50:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02009C44
_02009C5A:
	pop {r4-r6, pc}

	thumb_func_start FUN_02009C5C
FUN_02009C5C: ; 0x02009C5C
	push {r4, lr}
	add r4, r0, #0x0
	bne _02009C66
	bl ErrorHandling
_02009C66:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009C74
	bl ErrorHandling
_02009C74:
	add r0, r4, #0x0
	bl FUN_02009530
	bl FUN_0201D3B0
	pop {r4, pc}

	thumb_func_start FUN_02009C80
FUN_02009C80: ; 0x02009C80
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r5, r1, #0x0
	cmp r4, #0x0
	bne _02009C8E
	bl ErrorHandling
_02009C8E:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x0
	beq _02009C9C
	bl ErrorHandling
_02009C9C:
	cmp r5, #0x0
	bne _02009CA4
	bl ErrorHandling
_02009CA4:
	add r0, r5, #0x0
	bl FUN_020095D4
	cmp r0, #0x2
	beq _02009CB2
	bl ErrorHandling
_02009CB2:
	add r0, r4, #0x0
	bl FUN_02009530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_02009574
	add r1, r0, #0x0
	ldr r1, [r1, #0xc]
	add r0, r4, #0x0
	ldr r1, [r1, #0x0]
	bl FUN_0201D3D4
	cmp r0, #0x0
	bne _02009CDA
	add r0, r4, #0x0
	bl FUN_0201D3B0
	bl FUN_0201D458
_02009CDA:
	pop {r3-r5, pc}

	thumb_func_start FUN_02009CDC
FUN_02009CDC: ; 0x02009CDC
	push {r4, lr}
	add r4, r0, #0x0
	bne _02009CE6
	bl ErrorHandling
_02009CE6:
	add r0, r4, #0x0
	bl FUN_0201D4F0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02009CF0
FUN_02009CF0: ; 0x02009CF0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bne _02009CFC
	bl ErrorHandling
_02009CFC:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x1
	beq _02009D0A
	bl ErrorHandling
_02009D0A:
	add r0, r4, #0x0
	bl FUN_0200955C
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020095E4
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02009530
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02009610
	str r0, [sp, #0x8]
	add r0, sp, #0x0
	bl FUN_0201E0E4
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02009D34
FUN_02009D34: ; 0x02009D34
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _02009D3E
	bl ErrorHandling
_02009D3E:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02009D66
	add r4, r6, #0x0
_02009D48:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009D5C
	bl FUN_02009CF0
	cmp r0, #0x0
	bne _02009D5C
	bl ErrorHandling
_02009D5C:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02009D48
_02009D66:
	pop {r4-r6, pc}

	thumb_func_start FUN_02009D68
FUN_02009D68: ; 0x02009D68
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	bne _02009D74
	bl ErrorHandling
_02009D74:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x1
	beq _02009D82
	bl ErrorHandling
_02009D82:
	add r0, r4, #0x0
	bl FUN_0200955C
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_020095E4
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	bl FUN_02009530
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	bl FUN_02009610
	str r0, [sp, #0x8]
	add r0, sp, #0x0
	bl FUN_0201E128
	add sp, #0x10
	pop {r4, pc}

	thumb_func_start FUN_02009DAC
FUN_02009DAC: ; 0x02009DAC
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _02009DB6
	bl ErrorHandling
_02009DB6:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02009DDE
	add r4, r6, #0x0
_02009DC0:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009DD4
	bl FUN_02009D68
	cmp r0, #0x0
	bne _02009DD4
	bl ErrorHandling
_02009DD4:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02009DC0
_02009DDE:
	pop {r4-r6, pc}

	thumb_func_start FUN_02009DE0
FUN_02009DE0: ; 0x02009DE0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bne _02009DEA
	bl ErrorHandling
_02009DEA:
	add r0, r5, #0x0
	bl FUN_02009530
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0200955C
	add r1, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0201E168
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02009E04
FUN_02009E04: ; 0x02009E04
	push {r4, lr}
	add r4, r0, #0x0
	bne _02009E0E
	bl ErrorHandling
_02009E0E:
	add r0, r4, #0x0
	bl FUN_020095D4
	cmp r0, #0x1
	beq _02009E1C
	bl ErrorHandling
_02009E1C:
	add r0, r4, #0x0
	bl FUN_02009530
	bl FUN_0201E1C8
	pop {r4, pc}

	thumb_func_start FUN_02009E28
FUN_02009E28: ; 0x02009E28
	push {r4-r6, lr}
	add r5, r0, #0x0
	bne _02009E32
	bl ErrorHandling
_02009E32:
	ldr r0, [r5, #0x4]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02009E52
	add r4, r6, #0x0
_02009E3C:
	ldr r0, [r5, #0x0]
	ldr r0, [r0, r4]
	cmp r0, #0x0
	beq _02009E48
	bl FUN_02009E04
_02009E48:
	ldr r0, [r5, #0x4]
	add r6, r6, #0x1
	add r4, r4, #0x4
	cmp r6, r0
	blt _02009E3C
_02009E52:
	pop {r4-r6, pc}

	thumb_func_start FUN_02009E54
FUN_02009E54: ; 0x02009E54
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02009E62
	bl ErrorHandling
_02009E62:
	add r0, r5, #0x0
	bl FUN_020095D4
	cmp r0, #0x1
	beq _02009E70
	bl ErrorHandling
_02009E70:
	add r0, r5, #0x0
	bl FUN_02009530
	cmp r4, #0x0
	beq _02009E82
	add r1, r4, #0x0
	bl FUN_0201E258
	pop {r3-r5, pc}
_02009E82:
	bl FUN_0201E230
	pop {r3-r5, pc}

	thumb_func_start FUN_02009E88
FUN_02009E88: ; 0x02009E88
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x0
	bl FUN_02009E54
	add r1, r4, #0x0
	bl NNS_G2dGetImagePaletteLocation
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	beq _02009EA8
	asr r1, r0, #0x4
	lsr r1, r1, #0x1b
	add r1, r0, r1
	asr r0, r1, #0x5
_02009EA8:
	pop {r4, pc}
	.balign 4
