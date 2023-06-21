	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021DBEF4
ov05_021DBEF4: ; 0x021DBEF4
	push {r3, lr}
	mov r1, #0x42
	mov r0, #4
	lsl r1, r1, #2
	bl AllocFromHeap
	cmp r0, #0
	beq _021DBF1E
	mov r2, #0
	add r3, r0, #0
	add r1, r2, #0
_021DBF0A:
	strh r1, [r3, #0x14]
	strh r1, [r3, #0x16]
	str r1, [r3]
	str r1, [r3, #8]
	str r1, [r3, #0x10]
	str r1, [r3, #0xc]
	add r2, r2, #1
	add r3, #0x18
	cmp r2, #0xb
	blt _021DBF0A
_021DBF1E:
	pop {r3, pc}

	thumb_func_start ov05_021DBF20
ov05_021DBF20: ; 0x021DBF20
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	ldr r5, _021DBF4C ; =ov05_021FD290
	add r7, r0, #0
	str r1, [sp]
	add r4, r6, #0
_021DBF2C:
	ldr r1, [sp]
	ldr r2, [r5]
	add r0, r7, #0
	add r3, r4, #0
	bl ov05_021DBF50
	cmp r0, #0
	blt _021DBF3E
	add r6, r6, #1
_021DBF3E:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #0xb
	blt _021DBF2C
	add r0, r6, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DBF4C: .word ov05_021FD290

	thumb_func_start ov05_021DBF50
ov05_021DBF50: ; 0x021DBF50
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r6, r0, #0
	add r7, r1, #0
	str r2, [sp]
	str r3, [sp, #4]
	cmp r6, #0
	bne _021DBF68
	mov r0, #0
	add sp, #0x34
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_021DBF68:
	mov r4, #0
	add r1, r6, #0
_021DBF6C:
	ldr r0, [r1, #0xc]
	cmp r0, #0
	beq _021DBF7A
	add r4, r4, #1
	add r1, #0x18
	cmp r4, #0xb
	blt _021DBF6C
_021DBF7A:
	cmp r4, #0xb
	beq _021DBF82
	cmp r7, #0
	bne _021DBF8A
_021DBF82:
	mov r0, #0
	add sp, #0x34
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_021DBF8A:
	mov r0, #0x18
	add r5, r4, #0
	mul r5, r0
	ldr r1, [sp]
	add r0, r7, #0
	bl sub_0201C578
	str r0, [r6, r5]
	ldr r0, [r6, r5]
	cmp r0, #0
	bne _021DBFA8
	mov r0, #0
	add sp, #0x34
	mvn r0, r0
	pop {r4, r5, r6, r7, pc}
_021DBFA8:
	ldr r1, [sp]
	add r0, r7, #0
	bl sub_0201C5FC
	add r1, r6, r5
	str r0, [r1, #4]
	ldr r1, _021DBFF4 ; =ov05_021FD2BC
	ldr r2, [sp, #4]
	add r0, sp, #0xc
	bl sprintf
	add r7, r6, #0
	add r7, #0x10
	mov r0, #4
	add r1, sp, #0xc
	bl AllocAndReadFile
	str r0, [r7, r5]
	add r0, r6, #0
	str r0, [sp, #8]
	add r0, #0xc
	str r0, [sp, #8]
	ldr r0, [r7, r5]
	mov r1, #4
	bl OpenFileCached
	ldr r1, [sp, #8]
	str r0, [r1, r5]
	add r0, r1, #0
	ldr r0, [r0, r5]
	bl NNS_G3dGetTex
	add r1, r6, r5
	str r0, [r1, #8]
	add r0, r4, #0
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
_021DBFF4: .word ov05_021FD2BC

	thumb_func_start ov05_021DBFF8
ov05_021DBFF8: ; 0x021DBFF8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	beq _021DC064
	mov r4, #0
	ldr r7, _021DC068 ; =0x0000FFFF
	add r6, r4, #0
_021DC004:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	beq _021DC05C
	ldr r1, [r5, #0x10]
	cmp r1, #0
	beq _021DC05C
	ldrh r0, [r5, #0x14]
	lsl r0, r0, #2
	add r0, r1, r0
	ldrh r1, [r0, #0x22]
	ldrh r0, [r5, #0x16]
	cmp r1, r0
	bhi _021DC058
	strh r6, [r5, #0x16]
	ldrh r0, [r5, #0x14]
	add r0, r0, #1
	strh r0, [r5, #0x14]
	ldrh r0, [r5, #0x14]
	ldr r1, [r5, #0x10]
	lsl r0, r0, #2
	add r0, r1, r0
	ldrh r0, [r0, #0x20]
	cmp r0, r7
	bne _021DC036
	strh r6, [r5, #0x14]
_021DC036:
	ldrh r2, [r5, #0x14]
	ldr r1, [r5, #0x10]
	ldr r0, [r5, #8]
	lsl r2, r2, #2
	add r1, r1, r2
	ldrh r1, [r1, #0x20]
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	bl sub_0201C50C
	add r2, r0, #0
	ldr r1, [r5]
	ldr r3, [r5, #4]
	mov r0, #0
	bl sub_0201C2C8
	b _021DC05C
_021DC058:
	add r0, r0, #1
	strh r0, [r5, #0x16]
_021DC05C:
	add r4, r4, #1
	add r5, #0x18
	cmp r4, #0xb
	blt _021DC004
_021DC064:
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021DC068: .word 0x0000FFFF

	thumb_func_start ov05_021DC06C
ov05_021DC06C: ; 0x021DC06C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	beq _021DC092
	add r6, r5, #0
	mov r0, #0x18
	add r4, r1, #0
	mul r4, r0
	add r6, #0x10
	ldr r0, [r6, r4]
	cmp r0, #0
	beq _021DC08A
	bl FreeToHeap
	mov r0, #0
	str r0, [r6, r4]
_021DC08A:
	mov r1, #0
	add r0, r5, r4
	strh r1, [r0, #0x14]
	strh r1, [r0, #0x16]
_021DC092:
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021DC094
ov05_021DC094: ; 0x021DC094
	push {r3, r4, r5, lr}
	add r5, r0, #0
	beq _021DC0AA
	mov r4, #0
_021DC09C:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021DC06C
	add r4, r4, #1
	cmp r4, #0xb
	blt _021DC09C
_021DC0AA:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021DC0AC
ov05_021DC0AC: ; 0x021DC0AC
	push {r3, lr}
	cmp r0, #0
	beq _021DC0B6
	bl FreeToHeap
_021DC0B6:
	pop {r3, pc}

	.section .data

	.balign 4
	.global ov05_021FD228
ov05_021FD228: ; 0x021FD228
	.asciz "sea"

	.balign 4
	.global ov05_021FD22C
ov05_021FD22C: ; 0x021FD22C
	.asciz "rhana"

	.balign 4
	.global ov05_021FD234
ov05_021FD234: ; 0x021FD234
	.asciz "hamabe"

	.balign 4
	.global ov05_021FD23C
ov05_021FD23C: ; 0x021FD23C
	.asciz "asasea"

	.balign 4
	.global ov05_021FD244
ov05_021FD244: ; 0x021FD244
	.asciz "lakep.1"

	.balign 4
	.global ov05_021FD24C
ov05_021FD24C: ; 0x021FD24C
	.asciz "dun_sea"

	.balign 4
	.global ov05_021FD254
ov05_021FD254: ; 0x021FD254
	.asciz "t3_fl_p.1"

	.balign 4
	.global ov05_021FD260
ov05_021FD260: ; 0x021FD260
	.asciz "t3_fl_r.1"

	.balign 4
	.global ov05_021FD26C
ov05_021FD26C: ; 0x021FD26C
	.asciz "t3_fl_y.1"

	.balign 4
	.global ov05_021FD278
ov05_021FD278: ; 0x021FD278
	.asciz "asahamabe"

	.balign 4
	.global ov05_021FD284
ov05_021FD284: ; 0x021FD284
	.asciz "t3_fl_b.1"

	.balign 4
	.global ov05_021FD290
ov05_021FD290: ; 0x021FD290
	.word ov05_021FD228, ov05_021FD22C, ov05_021FD23C, ov05_021FD234
	.word ov05_021FD278, ov05_021FD284, ov05_021FD254, ov05_021FD260
	.word ov05_021FD26C, ov05_021FD24C, ov05_021FD244

	.global ov05_021FD2BC
ov05_021FD2BC: ; 0x021FD2BC
	.asciz "data/fld_anime%d.bin"
