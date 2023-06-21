	.include "asm/macros.inc"
	.include "global.inc"

	.extern gSystem

	.text

	thumb_func_start sub_020208B8
sub_020208B8: ; 0x020208B8
	push {r4-r7}
	ldrb r3, [r0, #0x0]
	mov r4, #0x0
	cmp r3, #0xff
	beq _020208FA
_020208C2:
	ldrb r7, [r0, #0x2]
	ldrb r3, [r0, #0x3]
	ldrb r5, [r0, #0x0]
	sub r6, r1, r7
	sub r3, r3, r7
	cmp r6, r3
	bhs _020208D4
	mov r6, #0x1
	b _020208D6
_020208D4:
	mov r6, #0x0
_020208D6:
	ldrb r7, [r0, #0x1]
	sub r3, r2, r5
	sub r5, r7, r5
	cmp r3, r5
	bhs _020208E4
	mov r3, #0x1
	b _020208E6
_020208E4:
	mov r3, #0x0
_020208E6:
	tst r3, r6
	beq _020208F0
	add r0, r4, #0x0
	pop {r4-r7}
	bx lr
_020208F0:
	add r0, r0, #0x4
	ldrb r3, [r0, #0x0]
	add r4, r4, #0x1
	cmp r3, #0xff
	bne _020208C2
_020208FA:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start sub_02020904
sub_02020904: ; 0x02020904
	push {r3-r4}
	ldrb r3, [r0, #0x1]
	sub r4, r3, r1
	ldrb r1, [r0, #0x2]
	sub r3, r1, r2
	ldrb r2, [r0, #0x3]
	add r1, r4, #0x0
	add r0, r3, #0x0
	mul r1, r4
	mul r0, r3
	add r1, r1, r0
	add r0, r2, #0x0
	mul r0, r2
	cmp r1, r0
	bhs _02020928
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_02020928:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start sub_02020930
sub_02020930: ; 0x02020930
	push {r4-r5}
	ldrb r5, [r0, #0x2]
	ldrb r3, [r0, #0x0]
	sub r4, r1, r5
	ldrb r1, [r0, #0x3]
	sub r1, r1, r5
	cmp r4, r1
	bhs _02020944
	mov r4, #0x1
	b _02020946
_02020944:
	mov r4, #0x0
_02020946:
	ldrb r0, [r0, #0x1]
	sub r1, r2, r3
	sub r0, r0, r3
	cmp r1, r0
	bhs _02020954
	mov r0, #0x1
	b _02020956
_02020954:
	mov r0, #0x0
_02020956:
	tst r0, r4
	beq _02020960
	mov r0, #0x1
	pop {r4-r5}
	bx lr
_02020960:
	mov r0, #0x0
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start sub_02020968
sub_02020968: ; 0x02020968
	push {r3, lr}
	ldr r2, _02020984 ; =gSystem + 0x40
	ldrh r1, [r2, #0x22]
	cmp r1, #0x0
	beq _0202097C
	ldrh r1, [r2, #0x1c]
	ldrh r2, [r2, #0x1e]
	bl sub_020208B8
	pop {r3, pc}
_0202097C:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
	nop
_02020984: .word gSystem + 0x40

	thumb_func_start sub_02020988
sub_02020988: ; 0x02020988
	push {r3, lr}
	ldr r2, _020209A4 ; =gSystem + 0x40
	ldrh r1, [r2, #0x20]
	cmp r1, #0x0
	beq _0202099C
	ldrh r1, [r2, #0x1c]
	ldrh r2, [r2, #0x1e]
	bl sub_020208B8
	pop {r3, pc}
_0202099C:
	mov r0, #0x0
	mvn r0, r0
	pop {r3, pc}
	nop
_020209A4: .word gSystem + 0x40

	thumb_func_start sub_020209A8
sub_020209A8: ; 0x020209A8
	push {r3-r7, lr}
	ldr r7, _020209F0 ; =gSystem + 0x40
	add r5, r0, #0x0
	ldrh r0, [r7, #0x22]
	cmp r0, #0x0
	beq _020209EA
	mov r6, #0x0
	add r4, r5, #0x0
_020209B8:
	ldrb r0, [r5, #0x0]
	cmp r0, #0xfe
	bne _020209D0
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl sub_02020904
	cmp r0, #0x0
	beq _020209E2
	add r0, r6, #0x0
	pop {r3-r7, pc}
_020209D0:
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl sub_02020930
	cmp r0, #0x0
	beq _020209E2
	add r0, r6, #0x0
	pop {r3-r7, pc}
_020209E2:
	add r5, r5, #0x4
	add r4, r4, #0x4
	add r6, r6, #0x1
	b _020209B8
_020209EA:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
	.balign 4
_020209F0: .word gSystem + 0x40

	thumb_func_start sub_020209F4
sub_020209F4: ; 0x020209F4
	push {r3-r7, lr}
	ldr r7, _02020A3C ; =gSystem + 0x40
	add r5, r0, #0x0
	ldrh r0, [r7, #0x20]
	cmp r0, #0x0
	beq _02020A36
	mov r6, #0x0
	add r4, r5, #0x0
_02020A04:
	ldrb r0, [r5, #0x0]
	cmp r0, #0xfe
	bne _02020A1C
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl sub_02020904
	cmp r0, #0x0
	beq _02020A2E
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02020A1C:
	ldrh r1, [r7, #0x1c]
	ldrh r2, [r7, #0x1e]
	add r0, r4, #0x0
	bl sub_02020930
	cmp r0, #0x0
	beq _02020A2E
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02020A2E:
	add r5, r5, #0x4
	add r4, r4, #0x4
	add r6, r6, #0x1
	b _02020A04
_02020A36:
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r7, pc}
	.balign 4
_02020A3C: .word gSystem + 0x40

	thumb_func_start sub_02020A40
sub_02020A40: ; 0x02020A40
	push {r3, lr}
	ldr r2, _02020A68 ; =gSystem + 0x40
	ldrh r1, [r2, #0x22]
	cmp r1, #0x0
	beq _02020A62
	ldrb r1, [r0, #0x0]
	cmp r1, #0xfe
	ldrh r1, [r2, #0x1c]
	bne _02020A5A
	ldrh r2, [r2, #0x1e]
	bl sub_02020904
	pop {r3, pc}
_02020A5A:
	ldrh r2, [r2, #0x1e]
	bl sub_02020930
	pop {r3, pc}
_02020A62:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02020A68: .word gSystem + 0x40

	thumb_func_start sub_02020A6C
sub_02020A6C: ; 0x02020A6C
	push {r3, lr}
	ldr r2, _02020A94 ; =gSystem + 0x40
	ldrh r1, [r2, #0x20]
	cmp r1, #0x0
	beq _02020A8E
	ldrb r1, [r0, #0x0]
	cmp r1, #0xfe
	ldrh r1, [r2, #0x1c]
	bne _02020A86
	ldrh r2, [r2, #0x1e]
	bl sub_02020904
	pop {r3, pc}
_02020A86:
	ldrh r2, [r2, #0x1e]
	bl sub_02020930
	pop {r3, pc}
_02020A8E:
	mov r0, #0x0
	pop {r3, pc}
	nop
_02020A94: .word gSystem + 0x40

	thumb_func_start sub_02020A98
sub_02020A98: ; 0x02020A98
	ldr r0, _02020AA0 ; =gSystem + 0x40
	ldrh r0, [r0, #0x22]
	bx lr
	nop
_02020AA0: .word gSystem + 0x40

	thumb_func_start sub_02020AA4
sub_02020AA4: ; 0x02020AA4
	ldr r0, _02020AAC ; =gSystem + 0x40
	ldrh r0, [r0, #0x20]
	bx lr
	nop
_02020AAC: .word gSystem + 0x40

	thumb_func_start sub_02020AB0
sub_02020AB0: ; 0x02020AB0
	ldr r2, _02020AC8 ; =gSystem + 0x40
	ldrh r3, [r2, #0x22]
	cmp r3, #0x0
	beq _02020AC4
	ldrh r3, [r2, #0x1c]
	str r3, [r0, #0x0]
	ldrh r0, [r2, #0x1e]
	str r0, [r1, #0x0]
	mov r0, #0x1
	bx lr
_02020AC4:
	mov r0, #0x0
	bx lr
	.balign 4
_02020AC8: .word gSystem + 0x40

	thumb_func_start sub_02020ACC
sub_02020ACC: ; 0x02020ACC
	ldr r2, _02020AE4 ; =gSystem + 0x40
	ldrh r3, [r2, #0x20]
	cmp r3, #0x0
	beq _02020AE0
	ldrh r3, [r2, #0x1c]
	str r3, [r0, #0x0]
	ldrh r0, [r2, #0x1e]
	str r0, [r1, #0x0]
	mov r0, #0x1
	bx lr
_02020AE0:
	mov r0, #0x0
	bx lr
	.balign 4
_02020AE4: .word gSystem + 0x40

	thumb_func_start sub_02020AE8
sub_02020AE8: ; 0x02020AE8
	push {r3, lr}
	ldrb r3, [r0, #0x0]
	cmp r3, #0xfe
	bne _02020AF6
	bl sub_02020904
	pop {r3, pc}
_02020AF6:
	bl sub_02020930
	pop {r3, pc}
