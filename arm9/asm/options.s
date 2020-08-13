	.include "asm/macros.inc"
    .include "global.inc"

	.extern gMain

	.text

	thumb_func_start FUN_02024F30
FUN_02024F30: ; 0x02024F30
	push {r4, lr}
	mov r1, #0x2
	bl AllocFromHeap
	add r4, r0, #0x0
	bl Options_init
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02024F44
FUN_02024F44: ; 0x02024F44
	ldr r3, _02024F4C ; =MI_CpuCopy8
	mov r2, #0x2
	bx r3
	nop
_02024F4C: .word MI_CpuCopy8

	thumb_func_start Options_init
Options_init: ; 0x02024F50
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl MI_CpuFill8
	ldrh r1, [r4, #0x0]
	mov r0, #0xf
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	mov r0, #0x30
	bic r1, r0
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	mov r0, #0x40
	bic r1, r0
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	mov r0, #0x80
	bic r1, r0
	strh r1, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r0, _02024F94 ; =0xFFFFFCFF
	and r0, r1
	strh r0, [r4, #0x0]
	ldrh r1, [r4, #0x0]
	ldr r0, _02024F98 ; =0xFFFF83FF
	and r0, r1
	strh r0, [r4, #0x0]
	pop {r4, pc}
	nop
_02024F94: .word 0xFFFFFCFF
_02024F98: .word 0xFFFF83FF

	thumb_func_start FUN_02024F9C
FUN_02024F9C: ; 0x02024F9C
	push {r3, lr}
	cmp r0, #0x0
	beq _02024FAC
	bl LoadPlayerDataAddress
	bl FUN_02025064
	add r1, r0, #0x0
_02024FAC:
	cmp r1, #0x0
	beq _02024FCA
	cmp r1, #0x1
	beq _02024FBA
	cmp r1, #0x2
	beq _02024FC2
	b _02024FCA
_02024FBA:
	ldr r0, _02024FD4 ; =gMain
	mov r1, #0x1
	str r1, [r0, #0x34]
	pop {r3, pc}
_02024FC2:
	ldr r0, _02024FD4 ; =gMain
	mov r1, #0x3
	str r1, [r0, #0x34]
	pop {r3, pc}
_02024FCA:
	ldr r0, _02024FD4 ; =gMain
	mov r1, #0x0
	str r1, [r0, #0x34]
	pop {r3, pc}
	nop
_02024FD4: .word gMain

	thumb_func_start FUN_02024FD8
FUN_02024FD8: ; 0x02024FD8
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	bx lr

	thumb_func_start FUN_02024FE0
FUN_02024FE0: ; 0x02024FE0
	ldrh r3, [r0, #0x0]
	mov r2, #0xf
	lsl r1, r1, #0x10
	bic r3, r2
	lsr r2, r1, #0x10
	mov r1, #0xf
	and r1, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02024FF4
FUN_02024FF4: ; 0x02024FF4
	push {r3, lr}
	bl FUN_02024FD8
	cmp r0, #0x0
	bne _02025002
	mov r0, #0x8
	pop {r3, pc}
_02025002:
	cmp r0, #0x1
	bne _0202500A
	mov r0, #0x4
	pop {r3, pc}
_0202500A:
	mov r0, #0x1
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02025010
FUN_02025010: ; 0x02025010
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1e
	bx lr

	thumb_func_start FUN_02025018
FUN_02025018: ; 0x02025018
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1e
	ldrh r3, [r0, #0x0]
	mov r2, #0x30
	lsr r1, r1, #0x1a
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_0202502C
FUN_0202502C: ; 0x0202502C
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02025034
FUN_02025034: ; 0x02025034
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	ldrh r3, [r0, #0x0]
	mov r2, #0x80
	lsr r1, r1, #0x18
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025048
FUN_02025048: ; 0x02025048
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1f
	bx lr

	thumb_func_start FUN_02025050
FUN_02025050: ; 0x02025050
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	ldrh r3, [r0, #0x0]
	mov r2, #0x40
	lsr r1, r1, #0x19
	bic r3, r2
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02025064
FUN_02025064: ; 0x02025064
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1e
	bx lr

	thumb_func_start FUN_0202506C
FUN_0202506C: ; 0x0202506C
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1e
	ldrh r3, [r0, #0x0]
	ldr r2, _02025080 ; =0xFFFFFCFF
	lsr r1, r1, #0x16
	and r2, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	bx lr
	.balign 4
_02025080: .word 0xFFFFFCFF

	thumb_func_start FUN_02025084
FUN_02025084: ; 0x02025084
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1b
	bx lr

	thumb_func_start FUN_0202508C
FUN_0202508C: ; 0x0202508C
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1b
	ldrh r3, [r0, #0x0]
	ldr r2, _020250A0 ; =0xFFFF83FF
	lsr r1, r1, #0x11
	and r2, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	bx lr
	.balign 4
_020250A0: .word 0xFFFF83FF
