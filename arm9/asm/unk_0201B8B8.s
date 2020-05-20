	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0201B8B8
FUN_0201B8B8: ; 0x0201B8B8
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0201B8DC ; =0x0000FFFE
	cmp r1, r0
	beq _0201B8C8
	bl ErrorHandling
_0201B8C8:
	ldrh r1, [r4, #0x0]
	ldr r0, _0201B8DC ; =0x0000FFFE
	cmp r1, r0
	bne _0201B8D8
	ldrh r0, [r4, #0x4]
	add r1, r4, #0x6
	lsl r0, r0, #0x1
	add r4, r1, r0
_0201B8D8:
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4
_0201B8DC: .word 0x0000FFFE

	thumb_func_start FUN_0201B8E0
FUN_0201B8E0: ; 0x0201B8E0
	push {r4, lr}
	add r4, r0, #0x0
	ldrh r1, [r4, #0x0]
	ldr r0, _0201B8F4 ; =0x0000FFFE
	cmp r1, r0
	beq _0201B8F0
	bl ErrorHandling
_0201B8F0:
	ldrh r0, [r4, #0x2]
	pop {r4, pc}
	.balign 4
_0201B8F4: .word 0x0000FFFE

	thumb_func_start FUN_0201B8F8
FUN_0201B8F8: ; 0x0201B8F8
	push {r3, lr}
	bl FUN_0201B8E0
	mov r1, #0xff
	lsl r1, r1, #0x8
	and r1, r0
	mov r0, #0x1
	lsl r0, r0, #0x8
	cmp r1, r0
	bne _0201B910
	mov r0, #0x1
	pop {r3, pc}
_0201B910:
	mov r0, #0x0
	pop {r3, pc}

	thumb_func_start FUN_0201B914
FUN_0201B914: ; 0x0201B914
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	ldrh r1, [r5, #0x0]
	ldr r0, _0201B938 ; =0x0000FFFE
	cmp r1, r0
	beq _0201B926
	bl ErrorHandling
_0201B926:
	ldrh r0, [r5, #0x4]
	cmp r4, r0
	blo _0201B930
	bl ErrorHandling
_0201B930:
	lsl r0, r4, #0x1
	add r0, r5, r0
	ldrh r0, [r0, #0x6]
	pop {r3-r5, pc}
	.balign 4
_0201B938: .word 0x0000FFFE
