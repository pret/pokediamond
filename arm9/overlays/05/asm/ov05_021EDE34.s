	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021EDE34
ov05_021EDE34: ; 0x021EDE34
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r1, #0
	add r1, r6, #0
	bl _s32_div_f
	add r4, r1, #0
	add r0, r5, #0
	add r1, r6, #0
	bl _s32_div_f
	cmp r4, r1
	bne _021EDE52
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EDE52:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021EDE58
ov05_021EDE58: ; 0x021EDE58
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r1, #0
	add r1, r6, #0
	bl _s32_div_f
	add r4, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl _s32_div_f
	cmp r4, r0
	bne _021EDE76
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EDE76:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021EDE7C
ov05_021EDE7C: ; 0x021EDE7C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	mov r0, #0x30
	add r4, r1, #0
	mul r4, r0
	add r1, r5, r4
	ldr r0, [r1, #0x14]
	cmp r0, #0
	beq _021EDE94
	ldr r0, [r1, #0xc]
	bl ov05_021EF8F8
_021EDE94:
	add r1, r5, r4
	ldr r0, [r1, #0x18]
	cmp r0, #0
	beq _021EDEA2
	ldr r0, [r1, #0x10]
	bl ov05_021F4444
_021EDEA2:
	mov r1, #1
	add r0, r5, r4
	str r1, [r0, #0x28]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021EDEAC
ov05_021EDEAC: ; 0x021EDEAC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021EDEBC
	ldr r0, [r4, #8]
	bl ov05_021EF8F8
_021EDEBC:
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _021EDEC8
	ldr r0, [r4, #0xc]
	bl ov05_021F4444
_021EDEC8:
	mov r0, #0
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start ov05_021EDED0
ov05_021EDED0: ; 0x021EDED0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r2, #0
	asr r2, r0, #4
	lsr r2, r2, #0x1b
	add r2, r0, r2
	asr r7, r2, #5
	asr r2, r1, #4
	lsr r2, r2, #0x1b
	add r2, r1, r2
	asr r6, r2, #5
	ldr r2, [sp, #0x18]
	str r3, [sp]
	ldr r4, [sp, #0x1c]
	bl ov05_021EEE08
	ldr r1, [sp, #0x18]
	bl ov05_021EF620
	add r1, r6, #0
	mul r1, r5
	add r1, r7, r1
	cmp r0, #3
	bhi _021EDFB6
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EDF0A: ; jump table
	.short _021EDF12 - _021EDF0A - 2 ; case 0
	.short _021EDF38 - _021EDF0A - 2 ; case 1
	.short _021EDF60 - _021EDF0A - 2 ; case 2
	.short _021EDF8A - _021EDF0A - 2 ; case 3
_021EDF12:
	sub r2, r1, r5
	str r1, [r4, #0xc]
	sub r0, r2, #1
	str r0, [r4]
	str r2, [r4, #4]
	sub r0, r1, #1
	str r0, [r4, #8]
	sub r0, r7, #1
	bpl _021EDF2C
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	str r0, [r4, #8]
_021EDF2C:
	sub r0, r6, #1
	bpl _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #4]
	pop {r3, r4, r5, r6, r7, pc}
_021EDF38:
	str r1, [r4, #8]
	sub r0, r1, r5
	str r0, [r4]
	add r0, r0, #1
	str r0, [r4, #4]
	add r0, r1, #1
	str r0, [r4, #0xc]
	add r0, r7, #1
	cmp r0, r5
	blt _021EDF54
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #4]
	str r0, [r4, #0xc]
_021EDF54:
	sub r0, r6, #1
	bpl _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021EDF60:
	str r1, [r4, #4]
	sub r0, r1, #1
	add r1, r1, r5
	str r0, [r4]
	sub r0, r1, #1
	str r0, [r4, #8]
	str r1, [r4, #0xc]
	sub r0, r7, #1
	bpl _021EDF7A
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	str r0, [r4, #8]
_021EDF7A:
	ldr r0, [sp]
	add r1, r6, #1
	cmp r1, r0
	ble _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #0xc]
	pop {r3, r4, r5, r6, r7, pc}
_021EDF8A:
	str r1, [r4]
	add r0, r1, #1
	str r0, [r4, #4]
	add r0, r1, r5
	str r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #0xc]
	add r0, r7, #1
	cmp r0, r5
	blt _021EDFA6
	mov r0, #0
	mvn r0, r0
	str r0, [r4, #4]
	str r0, [r4, #0xc]
_021EDFA6:
	ldr r0, [sp]
	add r1, r6, #1
	cmp r1, r0
	ble _021EDFBA
	mov r0, #0
	mvn r0, r0
	str r0, [r4]
	pop {r3, r4, r5, r6, r7, pc}
_021EDFB6:
	bl GF_AssertFail
_021EDFBA:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EDFBC
ov05_021EDFBC: ; 0x021EDFBC
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r5, r0, #0
	sub r7, r6, #1
_021EDFC4:
	ldr r1, _021EE03C ; =0x0000086C
	mov r0, #4
	bl AllocFromHeap
	lsl r4, r6, #2
	add r1, r5, r4
	add r1, #0x90
	str r0, [r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r2, [r0]
	ldr r0, _021EE040 ; =0x00000864
	mov r1, #0
	str r1, [r2, r0]
	add r2, r5, r4
	add r2, #0x90
	ldr r3, [r2]
	ldr r2, _021EE044 ; =0x00000854
	ldr r1, [r5]
	add r0, r6, #0
	add r2, r3, r2
	bl ov05_021F3C60
	add r2, r5, r4
	add r2, #0x90
	ldr r3, [r2]
	ldr r2, _021EE048 ; =0x00000858
	ldr r1, [r5]
	add r0, r6, #0
	add r2, r3, r2
	bl ov05_021F3C68
	mov r0, #4
	bl ov05_021E7C00
	add r1, r5, r4
	add r1, #0x90
	ldr r2, [r1]
	ldr r1, _021EE04C ; =0x00000868
	str r0, [r2, r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #0x86
	lsl r0, r0, #4
	str r7, [r1, r0]
	add r1, r5, r4
	add r1, #0x90
	mov r2, #2
	ldr r1, [r1]
	add r0, r7, #0
	lsl r2, r2, #0xa
	bl MIi_CpuClearFast
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EDFC4
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EE03C: .word 0x0000086C
_021EE040: .word 0x00000864
_021EE044: .word 0x00000854
_021EE048: .word 0x00000858
_021EE04C: .word 0x00000868

	thumb_func_start ov05_021EE050
ov05_021EE050: ; 0x021EE050
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #0
	add r5, r0, #0
	add r7, r6, #0
_021EE058:
	ldr r1, _021EE0B0 ; =0x0000086C
	mov r0, #4
	bl AllocFromHeap
	lsl r4, r6, #2
	add r1, r5, r4
	add r1, #0x90
	str r0, [r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EE0B4 ; =0x00000864
	add r2, r5, r4
	str r7, [r1, r0]
	add r2, #0x90
	ldr r3, [r2]
	ldr r2, _021EE0B8 ; =0x00000854
	ldr r1, [r5]
	add r0, r6, #0
	add r2, r3, r2
	bl ov05_021F3C60
	mov r0, #4
	bl ov05_021E7C00
	add r1, r5, r4
	add r1, #0x90
	ldr r2, [r1]
	ldr r1, _021EE0BC ; =0x00000868
	str r0, [r2, r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r2, [r0]
	mov r1, #0
	mov r0, #0x86
	mvn r1, r1
	lsl r0, r0, #4
	str r1, [r2, r0]
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EE058
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EE0B0: .word 0x0000086C
_021EE0B4: .word 0x00000864
_021EE0B8: .word 0x00000854
_021EE0BC: .word 0x00000868

	thumb_func_start ov05_021EE0C0
ov05_021EE0C0: ; 0x021EE0C0
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	cmp r6, #0
	beq _021EE0E6
	mov r0, #4
	mov r1, #0x10
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	add r0, r6, #0
	add r1, r7, #0
	mov r2, #0
	mov r3, #0x10
	str r4, [sp]
	bl NARC_ReadFromMember
	b _021EE0FC
_021EE0E6:
	bl GF_AssertFail
	mov r0, #0x10
	str r0, [sp]
	mov r0, #0x43
	add r1, r7, #0
	mov r2, #4
	mov r3, #0
	bl AllocAtEndAndReadFromNarcMemberByIdPair
	add r4, r0, #0
_021EE0FC:
	ldr r0, [r4]
	str r0, [r5]
	ldr r0, [r4, #4]
	str r0, [r5, #0xc]
	ldr r0, [r4, #8]
	str r0, [r5, #4]
	ldr r0, [r4, #0xc]
	str r0, [r5, #8]
	add r0, r4, #0
	bl FreeToHeap
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EE114
ov05_021EE114: ; 0x021EE114
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	ldr r4, [sp, #0x40]
	lsl r7, r0, #2
	add r0, r4, r7
	ldr r0, [r0, #0x18]
	str r1, [sp, #0xc]
	ldr r5, [sp, #0x3c]
	cmp r0, #0
	blt _021EE1D0
	ldr r1, [sp, #0x38]
	mul r1, r3
	cmp r0, r1
	bge _021EE1D0
	add r1, r2, #0
	bl GetMapData
	add r1, r0, #0
	ldr r0, _021EE1D4 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE1D0
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0x10
	bl ov05_021EE0C0
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, r7]
	bl NARC_ReadFile
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	ldr r3, _021EE1D8 ; =0x00000868
	str r0, [sp]
	add r0, r5, #0
	ldr r6, [r4, r7]
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0xc]
	ldr r3, [r6, r3]
	bl ov05_021E7CD8
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	ldr r0, [sp, #0xc]
	ldr r6, [r4, r7]
	bl ov05_021F4C74
	ldr r3, _021EE1DC ; =0x00000864
	str r0, [sp]
	add r0, r6, r3
	add r2, r3, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #8]
	add r0, r5, #0
	add r0, #0xf8
	sub r2, #0x64
	sub r3, #0x10
	ldr r0, [r0]
	ldr r1, [sp, #0x14]
	add r2, r6, r2
	add r3, r6, r3
	bl ov05_021EFA00
	str r0, [r4, #8]
	ldr r0, [r4, #0x14]
	add r3, r4, #0
	add r0, r0, #1
	str r0, [r4, #0x14]
	ldr r2, [r4, r7]
	ldr r6, _021EE1E0 ; =0x00000858
	add r5, #0xf8
	add r0, r2, r6
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r5]
	add r5, r6, #4
	ldr r1, [sp, #0x18]
	ldr r2, [r2, r5]
	add r3, #0x14
	bl ov05_021F43E4
	str r0, [r4, #0xc]
_021EE1D0:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EE1D4: .word 0x0000FFFF
_021EE1D8: .word 0x00000868
_021EE1DC: .word 0x00000864
_021EE1E0: .word 0x00000858

	thumb_func_start ov05_021EE1E4
ov05_021EE1E4: ; 0x021EE1E4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x30
	str r1, [sp, #0xc]
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, _021EE294 ; =0x00000828
	lsl r7, r0, #2
	add r3, sp
	ldr r4, [r3, #0x18]
	ldr r5, [r3, #0x14]
	add r0, r4, r7
	ldr r0, [r0, #0x18]
	cmp r0, #0
	blt _021EE286
	ldr r3, [r3, #0x10]
	mul r3, r2
	cmp r0, r3
	bge _021EE286
	bl GetMapData
	add r1, r0, #0
	ldr r0, _021EE298 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE286
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0x10
	bl ov05_021EE0C0
	add r0, r5, #0
	add r0, #0xf8
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0xa
	add r2, sp, #0x20
	bl NARC_ReadFile
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	ldr r3, _021EE29C ; =0x00000868
	str r0, [sp]
	add r0, r5, #0
	ldr r6, [r4, r7]
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0xc]
	ldr r3, [r6, r3]
	bl ov05_021E7CD8
	ldr r0, [r4, #0x10]
	add r0, r0, #1
	str r0, [r4, #0x10]
	ldr r0, [sp, #0xc]
	ldr r6, [r4, r7]
	bl ov05_021F4C74
	ldr r3, _021EE2A0 ; =0x00000864
	str r0, [sp]
	add r0, r6, r3
	add r2, r3, #0
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x10
	str r0, [sp, #8]
	add r5, #0xf8
	sub r2, #0x64
	sub r3, #0x10
	ldr r0, [r5]
	ldr r1, [sp, #0x14]
	add r2, r6, r2
	add r3, r6, r3
	bl ov05_021EFA00
	str r0, [r4, #8]
_021EE286:
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EE294: .word 0x00000828
_021EE298: .word 0x0000FFFF
_021EE29C: .word 0x00000868
_021EE2A0: .word 0x00000864

	thumb_func_start ov05_021EE2A4
ov05_021EE2A4: ; 0x021EE2A4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r1, #0
	str r0, [sp, #4]
	str r2, [sp, #8]
	ldr r7, [sp, #0x3c]
	add r1, r0, #0
	bmi _021EE37A
	ldr r2, [sp, #0x30]
	ldr r1, [sp, #0x34]
	add r5, r2, #0
	mul r5, r1
	add r1, r0, #0
	cmp r1, r5
	bge _021EE37A
	add r1, r3, #0
	bl GetMapData
	add r1, r0, #0
	ldr r0, _021EE380 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE37A
	add r0, r7, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0xc
	bl ov05_021EE0C0
	lsl r5, r4, #2
	add r4, r7, #0
	add r0, r7, #0
	add r4, #0x90
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0xc]
	ldr r2, [r4, r5]
	bl NARC_ReadFile
	add r0, r7, #0
	add r0, #0xf0
	ldr r0, [r0]
	ldr r3, _021EE384 ; =0x00000868
	str r0, [sp]
	add r0, r7, #0
	ldr r6, [r4, r5]
	add r0, #0xf8
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #8]
	ldr r3, [r6, r3]
	bl ov05_021E7CD8
	ldr r6, [r4, r5]
	ldr r0, [sp, #8]
	bl ov05_021F4C74
	str r0, [sp]
	add r0, r7, #0
	mov r3, #2
	add r0, #0xf8
	lsl r3, r3, #0xa
	add r2, r6, r3
	add r3, #0x54
	ldr r0, [r0]
	ldr r1, [sp, #0x10]
	add r3, r6, r3
	bl ov05_021EFA40
	ldr r1, [sp, #0x38]
	cmp r1, #1
	bne _021EE336
	bl ov05_021DB5EC
_021EE336:
	ldr r6, _021EE388 ; =0x00000864
	ldr r0, [r4, r5]
	mov r1, #1
	str r1, [r0, r6]
	add r2, r6, #0
	add r0, r7, #0
	add r0, #0xf8
	ldr r3, [r4, r5]
	sub r2, #8
	sub r6, #0xc
	ldr r2, [r3, r2]
	ldr r0, [r0]
	ldr r1, [sp, #0x14]
	ldr r3, [r3, r6]
	bl ov05_021F4344
	mov r2, #0x86
	ldr r1, [r4, r5]
	ldr r0, [sp, #4]
	lsl r2, r2, #4
	str r0, [r1, r2]
	add r0, r7, #0
	add r0, #0xfc
	ldr r3, [r0]
	cmp r3, #0
	beq _021EE37A
	mov r0, #1
	lsl r0, r0, #8
	ldr r4, [r4, r5]
	add r2, #8
	ldr r0, [r7, r0]
	ldr r1, [sp, #4]
	ldr r2, [r4, r2]
	blx r3
_021EE37A:
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_021EE380: .word 0x0000FFFF
_021EE384: .word 0x00000868
_021EE388: .word 0x00000864

	thumb_func_start ov05_021EE38C
ov05_021EE38C: ; 0x021EE38C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x1fc
	sub sp, #0x2c
	str r2, [sp, #8]
	ldr r2, _021EE44C ; =0x00000820
	add r4, r1, #0
	add r2, sp
	str r0, [sp, #4]
	ldr r5, [r2, #0x1c]
	add r1, r0, #0
	bmi _021EE43E
	ldr r6, [r2, #0x10]
	ldr r1, [r2, #0x14]
	add r2, r6, #0
	mul r2, r1
	add r1, r0, #0
	cmp r1, r2
	bge _021EE43E
	add r1, r3, #0
	bl GetMapData
	add r1, r0, #0
	ldr r0, _021EE450 ; =0x0000FFFF
	cmp r1, r0
	beq _021EE43E
	add r0, r5, #0
	add r0, #0xf8
	ldr r0, [r0]
	add r2, sp, #0xc
	bl ov05_021EE0C0
	add r0, r5, #0
	add r0, #0xf8
	mov r1, #2
	ldr r0, [r0]
	lsl r1, r1, #0xa
	add r2, sp, #0x1c
	bl NARC_ReadFile
	add r0, r5, #0
	add r0, #0xf0
	ldr r0, [r0]
	add r7, r5, #0
	str r0, [sp]
	add r0, r5, #0
	add r0, #0xf8
	lsl r4, r4, #2
	add r7, #0x90
	ldr r6, [r7, r4]
	ldr r3, _021EE454 ; =0x00000868
	ldr r0, [r0]
	ldr r1, [sp, #0x18]
	ldr r2, [sp, #8]
	ldr r3, [r6, r3]
	bl ov05_021E7CD8
	ldr r0, [sp, #8]
	ldr r6, [r7, r4]
	bl ov05_021F4C74
	mov r3, #2
	str r0, [sp]
	add r5, #0xf8
	lsl r3, r3, #0xa
	add r2, r6, r3
	add r3, #0x54
	ldr r0, [r5]
	ldr r1, [sp, #0x10]
	add r3, r6, r3
	bl ov05_021EFA40
	ldr r1, _021EE44C ; =0x00000820
	add r1, sp
	ldr r1, [r1, #0x18]
	cmp r1, #1
	bne _021EE42E
	bl ov05_021DB5EC
_021EE42E:
	ldr r1, [r7, r4]
	ldr r0, _021EE458 ; =0x00000864
	mov r2, #1
	str r2, [r1, r0]
	sub r1, r0, #4
	ldr r2, [r7, r4]
	ldr r0, [sp, #4]
	str r0, [r2, r1]
_021EE43E:
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x1fc
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_021EE44C: .word 0x00000820
_021EE450: .word 0x0000FFFF
_021EE454: .word 0x00000868
_021EE458: .word 0x00000864

	thumb_func_start ov05_021EE45C
ov05_021EE45C: ; 0x021EE45C
	ldr r1, [r0]
	cmp r1, #0
	bne _021EE46C
	ldr r0, [r0, #4]
	cmp r0, #0
	bne _021EE46C
	mov r0, #1
	bx lr
_021EE46C:
	mov r0, #0
	bx lr

	thumb_func_start ov05_021EE470
ov05_021EE470: ; 0x021EE470
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	str r3, [sp]
	add r0, sp, #0x10
	add r7, r1, #0
	ldrb r1, [r0, #0x14]
	mov r0, #0x30
	str r2, [sp, #8]
	add r5, r1, #0
	mul r5, r0
	add r0, r4, #0
	str r0, [sp, #4]
	add r0, #0x2c
	str r0, [sp, #4]
	ldr r0, [r0, r5]
	cmp r0, #0
	beq _021EE498
	bl GF_AssertFail
_021EE498:
	ldr r0, [sp, #4]
	mov r1, #1
	str r1, [r0, r5]
	add r0, sp, #0x10
	add r5, r4, r5
	add r1, r5, #0
	ldrb r2, [r0, #0x18]
	add r1, #0x30
	add r3, r4, #0
	strb r2, [r1]
	add r2, r5, #0
	ldr r1, [sp, #8]
	str r7, [r5, #0x1c]
	str r1, [r5, #0x20]
	ldr r1, [sp]
	add r2, #0x24
	strb r1, [r2]
	add r1, r5, #0
	ldrb r0, [r0, #0x10]
	add r1, #0x25
	add r3, #0x90
	strb r0, [r1]
	ldr r1, [sp]
	mov r6, #0
	lsl r2, r1, #2
	ldr r1, [r3, r2]
	str r1, [r5, #4]
	lsl r1, r0, #2
	ldr r0, [r3, r1]
	str r0, [r5, #8]
	add r0, r5, #0
	add r0, #0x26
	strb r6, [r0]
	add r0, r6, #0
	str r0, [r5, #0x28]
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EE4F0
	add r5, r4, #0
	add r5, #0xb4
	add r0, r6, #0
	str r0, [r5]
_021EE4F0:
	ldr r0, [r3, r2]
	mov r2, #0x86
	lsl r2, r2, #4
	str r7, [r0, r2]
	ldr r1, [r3, r1]
	ldr r0, [sp, #8]
	str r0, [r1, r2]
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0xa0
	strb r1, [r0]
	add r0, r4, #0
	add r0, #0xa1
	ldrb r0, [r0]
	add r4, #0xa1
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	strb r0, [r4]
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EE52C
ov05_021EE52C: ; 0x021EE52C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r0, r5, #0
	add r0, #0xa2
	ldrb r1, [r0]
	mov r0, #0x30
	add r4, r5, #0
	add r2, r5, #4
	mul r0, r1
	add r4, #0xcc
	add r6, r2, r0
	ldr r0, [r4, #0x20]
	cmp r0, #1
	bne _021EE572
	ldr r0, [r4, #0x18]
	cmp r0, #0
	beq _021EE5D0
	ldr r0, [r4, #0x14]
	ldr r1, [r0]
	ldr r0, [r4, #0x10]
	ldr r0, [r0]
	cmp r1, r0
	ble _021EE560
	bl GF_AssertFail
_021EE560:
	ldr r0, [r4, #0x10]
	ldr r1, [r0]
	ldr r0, [r4, #0x14]
	ldr r0, [r0]
	sub r1, r1, r0
	mov r0, #1
	lsl r0, r0, #0x10
	cmp r1, r0
	bge _021EE574
_021EE572:
	b _021EE6B0
_021EE574:
	ldr r1, [r4, #0xc]
	add r2, sp, #0x10
	ldr r0, [r1]
	ldr r1, [r1, #8]
	add r3, sp, #0xc
	bl ov05_021EF4F8
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0xc]
	add r2, r5, #0
	bl ov05_021EF2AC
	ldr r3, [r4, #0xc]
	add r2, r4, #0
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	str r0, [r2]
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE5B2
	mov r0, #1
	bl sub_020336A0
	cmp r0, #0
	bne _021EE692
_021EE5B2:
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE5C6
	bl GF_AssertFail
_021EE5C6:
	mov r0, #0
	str r0, [r4, #0x18]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	b _021EE6B0
_021EE5D0:
	ldr r2, [r4, #0xc]
	ldr r3, [r4]
	ldr r7, [r2]
	cmp r3, r7
	beq _021EE5E8
	ldr r1, [r4, #8]
	ldr r0, [r2, #8]
	cmp r1, r0
	beq _021EE5E8
	bl GF_AssertFail
	b _021EE6B0
_021EE5E8:
	cmp r3, r7
	bne _021EE5F4
	ldr r1, [r4, #8]
	ldr r0, [r2, #8]
	cmp r1, r0
	beq _021EE6B0
_021EE5F4:
	mov r3, #1
	str r3, [r4, #0x18]
	ldr r2, [r4, #0xc]
	ldr r0, [r4]
	ldr r1, [r2]
	cmp r0, r1
	beq _021EE648
	cmp r0, r1
	ble _021EE612
	str r4, [r4, #0x10]
	ldr r0, [r4, #0xc]
	str r0, [r4, #0x14]
	mov r0, #3
	strb r0, [r4, #0x1c]
	b _021EE618
_021EE612:
	str r2, [r4, #0x10]
	str r4, [r4, #0x14]
	strb r3, [r4, #0x1c]
_021EE618:
	ldr r0, [r4]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE632
	mov r0, #1
	bl sub_020336A0
	cmp r0, #0
	bne _021EE692
_021EE632:
	ldr r0, [r4]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE6A8
	bl GF_AssertFail
	b _021EE6A8
_021EE648:
	add r1, r5, #0
	add r1, #0xd8
	add r0, r5, #0
	ldr r1, [r1]
	add r0, #0xd4
	ldr r0, [r0]
	ldr r1, [r1, #8]
	cmp r0, r1
	ble _021EE66A
	add r0, r4, #0
	add r0, #8
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	add r0, #8
	str r0, [r4, #0x14]
	mov r0, #4
	b _021EE676
_021EE66A:
	add r2, #8
	add r0, r4, #0
	str r2, [r4, #0x10]
	add r0, #8
	str r0, [r4, #0x14]
	mov r0, #2
_021EE676:
	strb r0, [r4, #0x1c]
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE694
	mov r0, #1
	bl sub_020336A0
	cmp r0, #0
	beq _021EE694
_021EE692:
	b _021EE8C2
_021EE694:
	ldr r0, [r4, #8]
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x11
	sub r1, r1, r2
	mov r0, #0x11
	ror r1, r0
	add r0, r2, r1
	beq _021EE6A8
	bl GF_AssertFail
_021EE6A8:
	ldrb r0, [r4, #0x1c]
	add r1, r5, #0
	bl ov05_021EF458
_021EE6B0:
	add r0, r5, #0
	add r0, #0xb4
	ldr r0, [r0]
	cmp r0, #3
	bls _021EE6BC
	b _021EE818
_021EE6BC:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EE6C8: ; jump table
	.short _021EE6D0 - _021EE6C8 - 2 ; case 0
	.short _021EE726 - _021EE6C8 - 2 ; case 1
	.short _021EE818 - _021EE6C8 - 2 ; case 2
	.short _021EE804 - _021EE6C8 - 2 ; case 3
_021EE6D0:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	add r1, r6, r0
	add r1, #0x20
	ldrb r1, [r1]
	lsl r1, r1, #2
	add r1, r5, r1
	add r1, #0x80
	ldr r1, [r1]
	cmp r1, #1
	beq _021EE710
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r4, r5, #0
	str r1, [sp]
	str r5, [sp, #4]
	str r6, [sp, #8]
	add r4, #0xf4
	add r1, r5, #0
	add r2, r5, #0
	add r3, r5, #0
	ldr r4, [r4]
	add r1, #0xb8
	add r2, #0xbc
	add r3, #0xc0
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	ldr r4, [r4, #4]
	blx r4
_021EE710:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	add r6, #0x22
	mov r1, #1
	add r0, r0, #1
	strb r0, [r6]
	add r0, r5, #0
	add r0, #0xb4
	str r1, [r0]
	b _021EE818
_021EE726:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	sub r0, r0, #1
	add r0, r6, r0
	add r0, #0x20
	ldrb r0, [r0]
	lsl r0, r0, #2
	add r0, r5, r0
	add r0, #0x80
	ldr r0, [r0]
	cmp r0, #1
	bne _021EE75E
	add r0, r6, #0
	bl ov05_021EDEAC
	add r1, r6, #0
	add r1, #0x22
	ldrb r1, [r1]
	mov r0, #0
	sub r1, r1, #1
	add r1, r6, r1
	add r1, #0x20
	ldrb r1, [r1]
	lsl r1, r1, #2
	add r1, r5, r1
	add r1, #0x80
	str r0, [r1]
_021EE75E:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	cmp r0, #2
	bhi _021EE818
	add r0, r6, #0
	add r0, #0x10
	bl ov05_021EE45C
	cmp r0, #1
	bne _021EE818
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	cmp r0, #2
	blo _021EE784
	mov r0, #1
	str r0, [r6, #0x24]
	b _021EE78C
_021EE784:
	add r0, r5, #0
	mov r1, #0
	add r0, #0xb4
	str r1, [r0]
_021EE78C:
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	sub r0, r0, #1
	lsl r0, r0, #2
	ldr r2, [r6, r0]
	ldr r0, _021EE8C8 ; =0x00000864
	ldr r1, [r2, r0]
	cmp r1, #1
	bne _021EE7C4
	sub r0, #0x10
	ldr r0, [r2, r0]
	bl NNS_G3dGetMdlSet
	add r7, r0, #0
	ldrh r0, [r7, #0xe]
	add r0, r7, r0
	ldr r4, [r0, #0xc]
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl ov05_021F4CA8
	cmp r0, #1
	bne _021EE7C4
	add r0, r7, r4
	bl ov05_021DB5EC
_021EE7C4:
	add r0, r5, #0
	add r0, #0xfc
	ldr r3, [r0]
	cmp r3, #0
	beq _021EE818
	add r0, r6, #0
	add r0, #0x22
	ldrb r0, [r0]
	mov r2, #0x86
	lsl r2, r2, #4
	sub r0, r0, #1
	lsl r0, r0, #2
	ldr r4, [r6, r0]
	ldr r1, [r4, r2]
	cmp r1, #0
	blt _021EE818
	add r0, r5, #0
	add r6, r5, #0
	add r0, #0xc0
	add r6, #0xc4
	ldr r0, [r0]
	ldr r6, [r6]
	mul r6, r0
	cmp r1, r6
	bge _021EE818
	mov r0, #1
	lsl r0, r0, #8
	add r2, #8
	ldr r0, [r5, r0]
	ldr r2, [r4, r2]
	blx r3
	b _021EE818
_021EE804:
	add r6, #0x10
	add r0, r6, #0
	bl ov05_021EE45C
	cmp r0, #1
	bne _021EE818
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa0
	strb r1, [r0]
_021EE818:
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EE83A
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa2
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa1
	strb r1, [r0]
	mov r0, #2
	add r5, #0xb4
	add sp, #0x14
	str r0, [r5]
	pop {r4, r5, r6, r7, pc}
_021EE83A:
	add r0, r5, #0
	bl ov05_021EF0F0
	cmp r0, #1
	bne _021EE8C2
	add r0, r5, #0
	add r0, #0xa2
	ldrb r1, [r0]
	mov r0, #0x30
	mov r2, #0
	mul r0, r1
	add r0, r5, r0
	str r2, [r0, #0x2c]
	add r0, r5, #0
	bl ov05_021EF100
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	sub r1, r0, #1
	add r0, r5, #0
	add r0, #0xa0
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa2
	ldrb r0, [r0]
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r5, #0
	add r1, r2, r1
	add r0, #0xa2
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	beq _021EE890
	mov r1, #0
	b _021EE8A0
_021EE890:
	add r0, r5, #0
	mov r1, #0
	add r0, #0xa2
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa1
	strb r1, [r0]
	mov r1, #2
_021EE8A0:
	add r0, r5, #0
	add r0, #0xb4
	str r1, [r0]
	ldr r0, [r5, #0x6c]
	cmp r0, #1
	bne _021EE8C2
	mov r0, #0
	str r0, [r5, #0x6c]
	add r0, r5, #0
	add r0, #0x70
	ldrb r0, [r0]
	add r1, r5, #0
	bl ov05_021EF118
	add r0, r5, #0
	bl ov05_021EF094
_021EE8C2:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_021EE8C8: .word 0x00000864

	thumb_func_start ov05_021EE8CC
ov05_021EE8CC: ; 0x021EE8CC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	ldr r4, [sp, #0x34]
	str r2, [sp, #0x10]
	add r7, r0, #0
	ldr r0, [r4, #0x6c]
	add r5, r3, #0
	str r1, [sp, #0xc]
	ldr r6, [sp, #0x30]
	cmp r0, #1
	bne _021EE8E6
	bl GF_AssertFail
_021EE8E6:
	add r0, r6, #0
	add r1, r4, #0
	add r2, sp, #0x14
	bl ov05_021EEF9C
	cmp r0, #1
	bne _021EE964
	add r1, sp, #0x14
	ldrb r1, [r1]
	add r0, r4, #0
	bl ov05_021EDE7C
	add r0, r4, #0
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #2
	blo _021EE948
	mov r0, #1
	str r0, [r4, #0x6c]
	ldr r0, [sp, #0xc]
	str r7, [r4, #0x74]
	str r0, [r4, #0x78]
	add r1, r4, #0
	ldr r0, [sp, #0x10]
	add r1, #0x7c
	strb r0, [r1]
	add r0, r4, #0
	add r0, #0x7d
	strb r5, [r0]
	ldr r0, [sp, #0x10]
	add r2, r4, #0
	add r2, #0x90
	lsl r1, r0, #2
	ldr r0, [r2, r1]
	str r0, [r4, #0x64]
	lsl r0, r5, #2
	ldr r3, [r2, r0]
	str r3, [r4, #0x68]
	add r4, #0x70
	strb r6, [r4]
	ldr r3, [r2, r1]
	mov r1, #0x86
	lsl r1, r1, #4
	str r7, [r3, r1]
	ldr r2, [r2, r0]
	ldr r0, [sp, #0xc]
	add sp, #0x18
	str r0, [r2, r1]
	pop {r3, r4, r5, r6, r7, pc}
_021EE948:
	add r0, r4, #0
	str r5, [sp]
	add r0, #0xa1
	ldrb r0, [r0]
	ldr r2, [sp, #0xc]
	add r1, r7, #0
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r3, [sp, #0x10]
	add r0, r4, #0
	bl ov05_021EE470
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
_021EE964:
	add r0, r4, #0
	str r5, [sp]
	add r0, #0xa1
	ldrb r0, [r0]
	ldr r2, [sp, #0xc]
	add r1, r7, #0
	str r0, [sp, #4]
	str r6, [sp, #8]
	ldr r3, [sp, #0x10]
	add r0, r4, #0
	bl ov05_021EE470
	cmp r0, #1
	beq _021EE984
	bl GF_AssertFail
_021EE984:
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EE988
ov05_021EE988: ; 0x021EE988
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r4, r6, #0
	lsl r5, r0, #2
	add r4, #0x90
	ldr r1, [r4, r5]
	ldr r0, _021EE9CC ; =0x00000864
	mov r2, #0
	str r2, [r1, r0]
	ldr r1, [r4, r5]
	sub r0, #8
	ldr r0, [r1, r0]
	bl ov05_021F43CC
	ldr r1, [r4, r5]
	ldr r0, _021EE9D0 ; =0x00000868
	ldr r0, [r1, r0]
	bl ov05_021E7C1C
	mov r0, #0
	mov r2, #0x86
	ldr r1, [r4, r5]
	mvn r0, r0
	lsl r2, r2, #4
	str r0, [r1, r2]
	ldr r1, [r4, r5]
	sub r2, #0x60
	bl MIi_CpuClearFast
	add r0, r6, r5
	mov r1, #1
	add r0, #0x80
	str r1, [r0]
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021EE9CC: .word 0x00000864
_021EE9D0: .word 0x00000868

	thumb_func_start ov05_021EE9D4
ov05_021EE9D4: ; 0x021EE9D4
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r1, #0
	add r1, r4, #0
	add r6, r0, #0
	add r7, r2, #0
	str r3, [sp]
	bl ov05_021EE988
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EE988
	add r4, #0x90
	lsl r1, r6, #2
	lsl r5, r5, #2
	lsl r2, r7, #2
	ldr r0, [r4, r1]
	ldr r3, [r4, r5]
	ldr r6, [r4, r2]
	str r6, [r4, r1]
	ldr r1, [sp]
	lsl r6, r1, #2
	ldr r1, [r4, r6]
	str r1, [r4, r5]
	str r0, [r4, r2]
	str r3, [r4, r6]
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EEA0C
ov05_021EEA0C: ; 0x021EEA0C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r1, [sp, #8]
	add r7, r0, #0
	ldr r0, [sp, #8]
	add r6, r2, #0
	cmp r0, #4
	bls _021EEA1E
	b _021EED32
_021EEA1E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EEA2A: ; jump table
	.short _021EED32 - _021EEA2A - 2 ; case 0
	.short _021EEBA4 - _021EEA2A - 2 ; case 1
	.short _021EEC80 - _021EEA2A - 2 ; case 2
	.short _021EEAD2 - _021EEA2A - 2 ; case 3
	.short _021EEA34 - _021EEA2A - 2 ; case 4
_021EEA34:
	mov r0, #2
	mov r1, #3
	mov r2, #0
	mov r3, #1
	str r6, [sp]
	bl ov05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #2
	bne _021EEA7E
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #1
	sub r5, r7, r2
	str r0, [sp, #0x10]
	mov r0, #0
	sub r4, r5, #1
	str r0, [sp, #0xc]
	cmp r5, #0
	bge _021EEA68
	sub r5, r0, #1
	add r4, r5, #0
	b _021EEAB4
_021EEA68:
	cmp r4, #0
	blt _021EEA78
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EEAB4
_021EEA78:
	mov r4, #0
	mvn r4, r4
	b _021EEAB4
_021EEA7E:
	cmp r0, #3
	bne _021EEAB0
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #0
	sub r5, r7, r2
	str r0, [sp, #0x10]
	mov r0, #1
	add r4, r5, #1
	str r0, [sp, #0xc]
	cmp r5, #0
	bge _021EEA9E
	sub r5, r0, #2
	add r4, r5, #0
	b _021EEAB4
_021EEA9E:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EEAB4
	mov r4, #0
	mvn r4, r4
	b _021EEAB4
_021EEAB0:
	bl GF_AssertFail
_021EEAB4:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl ov05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EEAD2:
	mov r0, #1
	mov r1, #3
	mov r2, #0
	mov r3, #2
	str r6, [sp]
	bl ov05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #1
	bne _021EEB30
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	sub r5, r7, #1
	sub r0, r7, r2
	sub r4, r0, #1
	mov r0, #2
	str r0, [sp, #0x10]
	mov r0, #0
	str r0, [sp, #0xc]
	cmp r5, #0
	blt _021EEB0E
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EEB14
_021EEB0E:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEB14:
	cmp r4, #0
	blt _021EEB2A
	add r2, r6, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE34
	cmp r0, #0
	bne _021EEB86
_021EEB2A:
	mov r4, #0
	mvn r4, r4
	b _021EEB86
_021EEB30:
	cmp r0, #3
	bne _021EEB82
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	sub r5, r7, #1
	add r0, r7, r2
	sub r4, r0, #1
	mov r0, #0
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0xc]
	cmp r5, #0
	blt _021EEB58
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EEB5E
_021EEB58:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEB5E:
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r4
	ble _021EEB7C
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE34
	cmp r0, #0
	bne _021EEB86
_021EEB7C:
	mov r4, #0
	mvn r4, r4
	b _021EEB86
_021EEB82:
	bl GF_AssertFail
_021EEB86:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl ov05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EEBA4:
	mov r0, #0
	mov r1, #2
	mov r2, #1
	mov r3, #3
	str r6, [sp]
	bl ov05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EEC12
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r5, r7, #1
	sub r0, r7, r2
	add r4, r0, #1
	mov r0, #3
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r5
	ble _021EEBE8
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EEBEE
_021EEBE8:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEBEE:
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r4
	ble _021EEC0C
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE34
	cmp r0, #0
	bne _021EEC62
_021EEC0C:
	mov r4, #0
	mvn r4, r4
	b _021EEC62
_021EEC12:
	cmp r0, #2
	bne _021EEC62
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	add r5, r7, #1
	add r0, r7, r2
	add r4, r0, #1
	mov r0, #1
	str r0, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r2
	cmp r0, r5
	ble _021EEC42
	add r0, r5, #0
	add r1, r7, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EEC48
_021EEC42:
	mov r5, #0
	mvn r5, r5
	add r4, r5, #0
_021EEC48:
	cmp r4, #0
	blt _021EEC5E
	add r2, r6, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE34
	cmp r0, #0
	bne _021EEC62
_021EEC5E:
	mov r4, #0
	mvn r4, r4
_021EEC62:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl ov05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EEC80:
	mov r0, #0
	mov r1, #1
	mov r2, #2
	mov r3, #3
	str r6, [sp]
	bl ov05_021EE9D4
	add r0, r6, #0
	add r0, #0xad
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EECD0
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #3
	str r0, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r5, r7, r2
	mul r0, r2
	sub r4, r5, #1
	cmp r0, r5
	bgt _021EECBE
	ldr r0, [sp, #0xc]
	sub r5, r0, #3
	add r4, r5, #0
	b _021EED14
_021EECBE:
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EED14
	mov r4, #0
	mvn r4, r4
	b _021EED14
_021EECD0:
	cmp r0, #1
	bne _021EED10
	add r0, r6, #0
	add r0, #0xc0
	ldr r2, [r0]
	mov r0, #2
	str r0, [sp, #0x10]
	mov r0, #3
	str r0, [sp, #0xc]
	add r0, r6, #0
	add r0, #0xc4
	ldr r0, [r0]
	add r5, r7, r2
	mul r0, r2
	add r4, r5, #1
	cmp r0, r5
	bgt _021EECFA
	ldr r0, [sp, #0xc]
	sub r5, r0, #4
	add r4, r5, #0
	b _021EED14
_021EECFA:
	cmp r0, r4
	ble _021EED0A
	add r0, r5, #0
	add r1, r4, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EED14
_021EED0A:
	mov r4, #0
	mvn r4, r4
	b _021EED14
_021EED10:
	bl GF_AssertFail
_021EED14:
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #8]
	lsl r2, r2, #0x18
	str r0, [sp]
	lsl r3, r3, #0x18
	add r0, r5, #0
	add r1, r4, #0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	str r6, [sp, #4]
	bl ov05_021EE8CC
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
_021EED32:
	bl GF_AssertFail
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EED3C
ov05_021EED3C: ; 0x021EED3C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	add r5, r1, #0
	add r4, r5, #0
	lsl r6, r0, #2
	mov r0, #0x86
	add r3, sp, #0x38
	mov r1, #0
	str r1, [r3]
	str r1, [r3, #4]
	str r2, [sp, #4]
	add r2, r5, #0
	add r4, #0x90
	str r1, [r3, #8]
	add r2, #0xbc
	ldr r1, [r4, r6]
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	ldr r2, [r2]
	bl ov05_021EF300
	ldr r1, [r4, r6]
	ldr r0, _021EEDD4 ; =0x00000864
	ldr r0, [r1, r0]
	cmp r0, #1
	bne _021EEDA6
	ldr r3, _021EEDD8 ; =ov05_021F8B14
	add r2, sp, #0x2c
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	ldr r3, _021EEDDC ; =ov05_021F8B20
	str r0, [r2]
	add r2, sp, #8
	mov r7, #4
_021EED88:
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	sub r7, r7, #1
	bne _021EED88
	ldr r0, [r3]
	add r3, sp, #0x2c
	str r0, [r2]
	mov r0, #2
	ldr r1, [r4, r6]
	lsl r0, r0, #0xa
	add r0, r1, r0
	add r1, sp, #0x38
	add r2, sp, #8
	bl sub_0201B26C
_021EEDA6:
	ldr r4, [r4, r6]
	ldr r0, _021EEDD4 ; =0x00000864
	ldr r0, [r4, r0]
	cmp r0, #1
	bne _021EEDCE
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl ov05_021F4CA8
	add r2, r0, #0
	ldr r0, _021EEDE0 ; =0x00000868
	add r5, #0xb8
	ldr r0, [r4, r0]
	ldr r3, [sp, #4]
	str r0, [sp]
	ldr r1, [r5]
	add r0, sp, #0x38
	bl ov05_021E7DD8
_021EEDCE:
	add sp, #0x44
	pop {r4, r5, r6, r7, pc}
	nop
_021EEDD4: .word 0x00000864
_021EEDD8: .word ov05_021F8B14
_021EEDDC: .word ov05_021F8B20
_021EEDE0: .word 0x00000868

	thumb_func_start ov05_021EEDE4
ov05_021EEDE4: ; 0x021EEDE4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	add r5, r1, #0
	add r6, r0, #0
	add r1, r7, #0
	bl _u32_div_f
	add r4, r1, #0
	add r0, r6, #0
	add r1, r7, #0
	bl _u32_div_f
	lsr r0, r0, #5
	add r1, r0, #0
	lsr r2, r4, #5
	mul r1, r5
	add r0, r2, r1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EEE08
ov05_021EEE08: ; 0x021EEE08
	mul r2, r1
	add r0, r0, r2
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EEE10
ov05_021EEE10: ; 0x021EEE10
	push {r3, r4, r5, r6, r7, lr}
	add r7, r2, #0
	add r5, r1, #0
	add r6, r0, #0
	add r1, r7, #0
	bl _u32_div_f
	add r4, r1, #0
	add r0, r6, #0
	add r1, r7, #0
	bl _u32_div_f
	lsr r0, r0, #5
	add r1, r0, #0
	lsr r2, r4, #5
	mul r1, r5
	add r0, r2, r1
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EEE34
ov05_021EEE34: ; 0x021EEE34
	push {r3, lr}
	cmp r0, #0
	bne _021EEE3E
	mov r0, #3
	pop {r3, pc}
_021EEE3E:
	cmp r0, #1
	bne _021EEE46
	mov r0, #2
	pop {r3, pc}
_021EEE46:
	cmp r0, #2
	bne _021EEE4E
	mov r0, #1
	pop {r3, pc}
_021EEE4E:
	cmp r0, #3
	bne _021EEE56
	mov r0, #0
	pop {r3, pc}
_021EEE56:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021EEE60
ov05_021EEE60: ; 0x021EEE60
	push {r3, r4, r5, lr}
	add r5, r2, #0
	add r4, r3, #0
	cmp r0, #4
	bhi _021EEEC0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EEE76: ; jump table
	.short _021EEEC0 - _021EEE76 - 2 ; case 0
	.short _021EEE80 - _021EEE76 - 2 ; case 1
	.short _021EEE96 - _021EEE76 - 2 ; case 2
	.short _021EEEA4 - _021EEE76 - 2 ; case 3
	.short _021EEEB8 - _021EEE76 - 2 ; case 4
_021EEE80:
	add r0, r4, #0
	add r1, r5, #0
	bl _s32_div_f
	add r0, r1, #1
	cmp r0, r5
	blt _021EEE92
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEE92:
	add r0, r4, #1
	pop {r3, r4, r5, pc}
_021EEE96:
	lsl r1, r1, #5
	add r0, r4, r5
	mul r1, r5
	cmp r0, r1
	blt _021EEEC6
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEEA4:
	add r0, r4, #0
	add r1, r5, #0
	bl _s32_div_f
	sub r0, r1, #1
	bpl _021EEEB4
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEEB4:
	sub r0, r4, #1
	pop {r3, r4, r5, pc}
_021EEEB8:
	sub r0, r4, r5
	bpl _021EEEC6
	add r0, r4, #0
	pop {r3, r4, r5, pc}
_021EEEC0:
	bl GF_AssertFail
	mov r0, #0
_021EEEC6:
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021EEEC8
ov05_021EEEC8: ; 0x021EEEC8
	cmp r0, #4
	bhi _021EEF00
	add r2, r0, r0
	add r2, pc
	ldrh r2, [r2, #6]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add pc, r2
_021EEED8: ; jump table
	.short _021EEF00 - _021EEED8 - 2 ; case 0
	.short _021EEEFA - _021EEED8 - 2 ; case 1
	.short _021EEEEA - _021EEED8 - 2 ; case 2
	.short _021EEEF2 - _021EEED8 - 2 ; case 3
	.short _021EEEE2 - _021EEED8 - 2 ; case 4
_021EEEE2:
	sub r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021EEEEA:
	add r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021EEEF2:
	sub r0, r1, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr
_021EEEFA:
	add r0, r1, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
_021EEF00:
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EEF04
ov05_021EEF04: ; 0x021EEF04
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	bl ov05_021EEEC8
	cmp r5, r0
	bge _021EEF36
	sub r0, r0, r5
	cmp r0, #1
	bne _021EEF22
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF22:
	cmp r0, #2
	bne _021EEF30
	ldrb r0, [r4]
	sub r0, r0, #2
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF30:
	bl GF_AssertFail
	b _021EEF62
_021EEF36:
	cmp r5, r0
	ble _021EEF5E
	sub r0, r5, r0
	cmp r0, #1
	bne _021EEF4A
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF4A:
	cmp r0, #2
	bne _021EEF58
	ldrb r0, [r4]
	add r0, r0, #2
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	b _021EEF62
_021EEF58:
	bl GF_AssertFail
	b _021EEF62
_021EEF5E:
	bl GF_AssertFail
_021EEF62:
	strb r6, [r4]
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start ov05_021EEF68
ov05_021EEF68: ; 0x021EEF68
	push {r3, lr}
	cmp r0, #4
	bhi _021EEF94
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EEF7A: ; jump table
	.short _021EEF94 - _021EEF7A - 2 ; case 0
	.short _021EEF8C - _021EEF7A - 2 ; case 1
	.short _021EEF88 - _021EEF7A - 2 ; case 2
	.short _021EEF90 - _021EEF7A - 2 ; case 3
	.short _021EEF84 - _021EEF7A - 2 ; case 4
_021EEF84:
	mov r0, #2
	pop {r3, pc}
_021EEF88:
	mov r0, #4
	pop {r3, pc}
_021EEF8C:
	mov r0, #3
	pop {r3, pc}
_021EEF90:
	mov r0, #1
	pop {r3, pc}
_021EEF94:
	bl GF_AssertFail
	mov r0, #0
	pop {r3, pc}

	thumb_func_start ov05_021EEF9C
ov05_021EEF9C: ; 0x021EEF9C
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	mov r4, #0
_021EEFA6:
	ldr r0, [r5, #0x2c]
	cmp r0, #1
	bne _021EEFC2
	add r0, r6, #0
	bl ov05_021EEF68
	add r1, r5, #0
	add r1, #0x30
	ldrb r1, [r1]
	cmp r1, r0
	bne _021EEFC2
	strb r4, [r7]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_021EEFC2:
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #2
	blt _021EEFA6
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EEFD0
ov05_021EEFD0: ; 0x021EEFD0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r0, #0xa1
	ldrb r1, [r0]
	mov r0, #0x30
	add r4, r5, #0
	mul r0, r1
	add r0, r5, r0
	ldr r0, [r0, #0x2c]
	add r4, #0x64
	cmp r0, #0
	beq _021EEFEC
	bl GF_AssertFail
_021EEFEC:
	add r1, r5, #0
	add r1, #0xa1
	ldrb r2, [r1]
	mov r1, #0x30
	mov r0, #1
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	add r3, r5, #0
	str r0, [r2, #0x2c]
	add r3, #0xa1
	ldrb r3, [r3]
	ldrb r2, [r4, #0xc]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	add r3, #0x30
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldr r2, [r4, #0x10]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	str r2, [r3, #0x1c]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldr r2, [r4, #0x14]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	str r2, [r3, #0x20]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldrb r2, [r4, #0x18]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	add r3, #0x24
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldrb r2, [r4, #0x19]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	add r3, #0x25
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	ldr r2, [r4]
	add r6, r3, #0
	mul r6, r1
	add r3, r5, r6
	str r2, [r3, #4]
	add r2, r5, #0
	add r2, #0xa1
	ldrb r2, [r2]
	ldr r4, [r4, #4]
	add r3, r2, #0
	mul r3, r1
	add r2, r5, r3
	add r3, r5, #0
	str r4, [r2, #8]
	add r3, #0xa1
	ldrb r3, [r3]
	mov r2, #0
	add r4, r3, #0
	mul r4, r1
	add r3, r5, r4
	add r3, #0x26
	strb r2, [r3]
	add r3, r5, #0
	add r3, #0xa1
	ldrb r3, [r3]
	mul r1, r3
	add r1, r5, r1
	str r2, [r1, #0x28]
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021EF094
ov05_021EF094: ; 0x021EF094
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r4, r5, #0
	add r4, #0x64
	cmp r0, #2
	blo _021EF0A8
	bl GF_AssertFail
_021EF0A8:
	add r0, r5, #0
	bl ov05_021EEFD0
	cmp r0, #1
	beq _021EF0B6
	bl GF_AssertFail
_021EF0B6:
	mov r0, #0x86
	ldr r2, [r4, #0x10]
	ldr r1, [r4]
	lsl r0, r0, #4
	str r2, [r1, r0]
	ldr r2, [r4, #0x14]
	ldr r1, [r4, #4]
	str r2, [r1, r0]
	add r0, r5, #0
	add r0, #0xa0
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r5, #0
	add r0, #0xa0
	strb r1, [r0]
	add r0, r5, #0
	add r0, #0xa1
	ldrb r0, [r0]
	add r5, #0xa1
	add r0, r0, #1
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1f
	sub r1, r1, r2
	mov r0, #0x1f
	ror r1, r0
	add r0, r2, r1
	strb r0, [r5]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF0F0
ov05_021EF0F0: ; 0x021EF0F0
	add r1, r0, #0
	add r1, #0xa2
	ldrb r2, [r1]
	mov r1, #0x30
	mul r1, r2
	add r0, r0, r1
	ldr r0, [r0, #0x28]
	bx lr

	thumb_func_start ov05_021EF100
ov05_021EF100: ; 0x021EF100
	mov r3, #0
	add r2, r3, #0
_021EF104:
	lsl r1, r3, #2
	add r1, r0, r1
	add r1, #0x80
	str r2, [r1]
	add r1, r3, #1
	lsl r1, r1, #0x18
	lsr r3, r1, #0x18
	cmp r3, #4
	blo _021EF104
	bx lr

	thumb_func_start ov05_021EF118
ov05_021EF118: ; 0x021EF118
	cmp r0, #4
	bhi _021EF168
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EF128: ; jump table
	.short _021EF168 - _021EF128 - 2 ; case 0
	.short _021EF140 - _021EF128 - 2 ; case 1
	.short _021EF14E - _021EF128 - 2 ; case 2
	.short _021EF15C - _021EF128 - 2 ; case 3
	.short _021EF132 - _021EF128 - 2 ; case 4
_021EF132:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x88
	str r2, [r0]
	add r1, #0x8c
	str r2, [r1]
	bx lr
_021EF140:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x80
	str r2, [r0]
	add r1, #0x88
	str r2, [r1]
	bx lr
_021EF14E:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x80
	str r2, [r0]
	add r1, #0x84
	str r2, [r1]
	bx lr
_021EF15C:
	add r0, r1, #0
	mov r2, #1
	add r0, #0x84
	str r2, [r0]
	add r1, #0x8c
	str r2, [r1]
_021EF168:
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EF16C
ov05_021EF16C: ; 0x021EF16C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r3, #0
	add r6, r1, #0
	add r7, r2, #0
	bl ov05_021EDFBC
	add r2, r5, #0
	add r3, r5, #0
	str r4, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	add r2, #0xc0
	add r3, #0xc4
	ldr r2, [r2]
	ldr r3, [r3]
	add r0, r6, #0
	add r1, r7, #0
	bl ov05_021EDED0
	mov r6, #0
	add r7, sp, #0x10
_021EF19A:
	lsl r4, r6, #2
	bl ov05_021F4328
	add r1, r5, r4
	add r1, #0x90
	ldr r2, [r1]
	ldr r1, _021EF1F8 ; =0x0000085C
	str r0, [r2, r1]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF1F8 ; =0x0000085C
	ldr r0, [r1, r0]
	bl ov05_021F4454
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl ov05_021F4CA8
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r5, #0
	str r1, [sp]
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r3, r5, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	add r2, #0xb8
	add r3, #0xbc
	ldr r0, [r7, r4]
	ldr r2, [r2]
	ldr r3, [r3]
	add r1, r6, #0
	bl ov05_021EE2A4
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EF19A
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF1F8: .word 0x0000085C

	thumb_func_start ov05_021EF1FC
ov05_021EF1FC: ; 0x021EF1FC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r0, #0
	add r4, r3, #0
	add r6, r1, #0
	add r7, r2, #0
	bl ov05_021EE050
	add r2, r5, #0
	add r3, r5, #0
	str r4, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	add r2, #0xc0
	add r3, #0xc4
	ldr r2, [r2]
	ldr r3, [r3]
	add r0, r6, #0
	add r1, r7, #0
	bl ov05_021EDED0
	mov r4, #0
	add r7, r4, #0
_021EF22A:
	lsl r6, r4, #2
	add r0, r5, r6
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF278 ; =0x0000085C
	str r7, [r1, r0]
	add r0, r5, #0
	add r0, #0xb8
	ldr r0, [r0]
	bl ov05_021F4CA8
	add r1, r5, #0
	add r1, #0xc0
	ldr r1, [r1]
	add r2, r5, #0
	str r1, [sp]
	add r1, r5, #0
	add r1, #0xc4
	ldr r1, [r1]
	add r3, r5, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r5, [sp, #0xc]
	add r0, sp, #0x10
	add r2, #0xb8
	add r3, #0xbc
	ldr r0, [r0, r6]
	ldr r2, [r2]
	ldr r3, [r3]
	add r1, r4, #0
	bl ov05_021EE38C
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021EF22A
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF278: .word 0x0000085C

	thumb_func_start ov05_021EF27C
ov05_021EF27C: ; 0x021EF27C
	push {r4, lr}
	add r1, r0, #0
	mov r3, #0
	add r1, #0xa2
	strb r3, [r1]
	add r1, r0, #0
	add r1, #0xa1
	strb r3, [r1]
	add r1, r0, #0
	add r1, #0xa0
	strb r3, [r1]
	add r4, r0, #0
	add r2, r3, #0
	mov r1, #1
_021EF298:
	str r2, [r4, #0x2c]
	str r1, [r4, #0x28]
	add r3, r3, #1
	add r4, #0x30
	cmp r3, #2
	blt _021EF298
	bl ov05_021EF100
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF2AC
ov05_021EF2AC: ; 0x021EF2AC
	push {r4, lr}
	add r4, r2, #0
	add r2, #0xc8
	ldr r2, [r2]
	bl ov05_021EEE08
	add r1, r4, #0
	add r1, #0xa8
	str r0, [r1]
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa8
	add r1, #0xc8
	ldr r0, [r0]
	ldr r1, [r1]
	bl ov05_021EF620
	add r1, r4, #0
	add r1, #0xad
	strb r0, [r1]
	add r0, r4, #0
	add r0, #0xad
	ldrb r0, [r0]
	bl ov05_021EEE34
	add r1, r4, #0
	add r1, #0xac
	strb r0, [r1]
	add r0, r4, #0
	add r1, r4, #0
	add r2, r4, #0
	add r0, #0xa8
	add r1, #0xc0
	add r2, #0xc8
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	bl ov05_021EEE10
	add r4, #0xa4
	str r0, [r4]
	pop {r4, pc}

	thumb_func_start ov05_021EF300
ov05_021EF300: ; 0x021EF300
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r2, #0
	mov r2, #1
	add r5, r3, #0
	lsl r2, r2, #0x14
	str r2, [r5]
	str r2, [r5, #8]
	mov r2, #0
	add r4, r0, #0
	mvn r2, r2
	str r1, [sp, #4]
	cmp r4, r2
	beq _021EF362
	bl _s32_div_f
	lsl r0, r1, #0x10
	lsr r6, r0, #0x10
	ldr r1, [sp, #4]
	add r0, r4, #0
	bl _s32_div_f
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	add r0, r7, #0
	bl MapMatrix_GetWidth
	str r0, [sp, #8]
	add r0, r7, #0
	bl MapMatrix_GetMatrixID
	add r1, r0, #0
	ldr r0, [sp, #8]
	add r2, r6, #0
	str r0, [sp]
	add r0, r7, #0
	add r3, r4, #0
	bl MapMatrix_GetMapAltitude
	lsl r0, r0, #0xf
	str r0, [r5, #4]
	ldr r1, [r5]
	lsl r0, r6, #0x15
	add r0, r1, r0
	str r0, [r5]
	ldr r1, [r5, #8]
	lsl r0, r4, #0x15
	add r0, r1, r0
	str r0, [r5, #8]
_021EF362:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF368
ov05_021EF368: ; 0x021EF368
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	str r1, [sp]
	mov r1, #0x41
	add r5, r0, #0
	mov r0, #4
	lsl r1, r1, #2
	str r2, [sp, #4]
	add r6, r3, #0
	bl AllocFromHeap
	mov r2, #0x41
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl MI_CpuFill8
	cmp r6, #0
	bne _021EF39A
	add r0, r4, #0
	ldr r1, _021EF42C ; =ov05_021F8B04
	add r0, #0xf4
	str r1, [r0]
	mov r7, #1
	b _021EF3AE
_021EF39A:
	cmp r6, #1
	bne _021EF3AA
	add r0, r4, #0
	ldr r1, _021EF430 ; =ov05_021F8B0C
	add r0, #0xf4
	str r1, [r0]
	mov r7, #0
	b _021EF3AE
_021EF3AA:
	bl GF_AssertFail
_021EF3AE:
	add r0, r7, #0
	bl ov05_021F3BC0
	str r0, [r4]
	add r1, r4, #0
	ldr r0, [sp]
	add r1, #0xb8
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xbc
	str r5, [r0]
	add r0, r5, #0
	bl MapMatrix_GetWidth
	add r1, r4, #0
	add r1, #0xc0
	str r0, [r1]
	add r0, r5, #0
	bl MapMatrix_GetHeight
	add r1, r4, #0
	add r1, #0xc4
	str r0, [r1]
	add r0, r4, #0
	add r0, #0xc0
	ldr r0, [r0]
	lsl r1, r0, #5
	add r0, r4, #0
	add r0, #0xc8
	str r1, [r0]
	add r1, r4, #0
	ldr r0, [sp, #4]
	add r1, #0xf0
	str r0, [r1]
	add r0, r4, #0
	mov r1, #1
	add r0, #0xec
	str r1, [r0]
	add r0, r4, #0
	bl ov05_021EF27C
	add r0, r4, #0
	mov r1, #0
	add r0, #0xb0
	str r1, [r0]
	add r0, r4, #0
	mov r1, #2
	add r0, #0xb4
	str r1, [r0]
	mov r0, #0x43
	mov r1, #4
	bl NARC_New
	add r1, r4, #0
	add r1, #0xf8
	str r0, [r1]
	add r0, r4, #0
	mov r1, #0
	add r0, #0xfc
	str r1, [r0]
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF42C: .word ov05_021F8B04
_021EF430: .word ov05_021F8B0C

	thumb_func_start ov05_021EF434
ov05_021EF434: ; 0x021EF434
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r5, #0
	add r6, #0xf4
	add r3, r5, #0
	ldr r6, [r6]
	add r3, #0xc8
	ldr r3, [r3]
	ldr r6, [r6]
	add r4, r1, #0
	add r7, r2, #0
	blx r6
	add r0, r4, #0
	add r1, r7, #0
	add r2, r5, #0
	bl ov05_021EF2AC
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021EF458
ov05_021EF458: ; 0x021EF458
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r2, r5, #0
	add r3, r5, #0
	add r1, #0xc4
	add r2, #0xc8
	add r3, #0xa8
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	add r6, r0, #0
	bl ov05_021EEE60
	add r1, r5, #0
	add r2, r5, #0
	add r1, #0xc0
	add r2, #0xc8
	ldr r1, [r1]
	ldr r2, [r2]
	add r7, r0, #0
	bl ov05_021EEDE4
	add r1, r5, #0
	add r1, #0xc8
	add r4, r0, #0
	ldr r1, [r1]
	add r0, r7, #0
	bl ov05_021EF620
	add r1, r5, #0
	add r1, #0xa4
	ldr r1, [r1]
	cmp r1, r4
	bne _021EF4C0
	add r1, r5, #0
	add r1, #0xad
	ldrb r1, [r1]
	cmp r1, r0
	beq _021EF4C0
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	bl ov05_021EEA0C
	add r1, r5, #0
	add r1, #0xad
	add r5, #0xac
	ldrb r1, [r1]
	add r0, r6, #0
	add r2, r5, #0
	bl ov05_021EEF04
_021EF4C0:
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF4C4
ov05_021EF4C4: ; 0x021EF4C4
	push {r3, r4, r5, r6, r7, lr}
	mov r4, #0
	add r5, r0, #0
	add r6, r1, #0
	sub r7, r4, #1
_021EF4CE:
	lsl r0, r4, #2
	add r0, r5, r0
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #0x86
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	cmp r0, r7
	beq _021EF4EA
	add r0, r4, #0
	add r1, r5, #0
	add r2, r6, #0
	bl ov05_021EED3C
_021EF4EA:
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #4
	blo _021EF4CE
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF4F8
ov05_021EF4F8: ; 0x021EF4F8
	push {r3, r4}
	asr r4, r0, #0xf
	lsr r4, r4, #0x10
	add r4, r0, r4
	asr r0, r4, #0x10
	str r0, [r2]
	asr r0, r1, #0xf
	lsr r0, r0, #0x10
	add r0, r1, r0
	asr r0, r0, #0x10
	str r0, [r3]
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EF514
ov05_021EF514: ; 0x021EF514
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	bl ClearFileCache
	bl NNS_GfdResetLnkTexVramState
	bl NNS_GfdResetLnkPlttVramState
	mov r4, #0
	add r6, r5, #4
	mov r7, #0x30
_021EF52A:
	add r0, r4, #0
	mul r0, r7
	add r0, r6, r0
	bl ov05_021EDEAC
	add r0, r4, #1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #2
	blo _021EF52A
	mov r6, #0
	add r7, r6, #0
_021EF542:
	lsl r4, r6, #2
	add r0, r5, r4
	add r0, #0x90
	ldr r2, [r0]
	ldr r0, _021EF59C ; =0x00000864
	mov r1, #0
	str r1, [r2, r0]
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF5A0 ; =0x0000085C
	ldr r0, [r1, r0]
	bl ov05_021F43C0
	add r0, r5, r4
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF5A4 ; =0x00000868
	ldr r0, [r1, r0]
	bl ov05_021E7C14
	add r0, r5, r4
	add r0, #0x90
	ldr r0, [r0]
	bl FreeToHeap
	add r0, r5, r4
	add r0, #0x90
	str r7, [r0]
	add r0, r6, #1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #4
	blo _021EF542
	add r0, r5, #0
	mov r1, #3
	add r0, #0xb4
	str r1, [r0]
	add r0, r5, #0
	mov r1, #1
	add r0, #0xb0
	str r1, [r0]
	add r5, #0xec
	str r7, [r5]
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
_021EF59C: .word 0x00000864
_021EF5A0: .word 0x0000085C
_021EF5A4: .word 0x00000868

	thumb_func_start ov05_021EF5A8
ov05_021EF5A8: ; 0x021EF5A8
	push {r4, lr}
	add r4, r0, #0
	add r0, #0xf8
	ldr r0, [r0]
	bl NARC_Delete
	ldr r0, [r4]
	bl ov05_021F3C30
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF5C4
ov05_021EF5C4: ; 0x021EF5C4
	add r1, r0, #0
	add r1, #0xb0
	ldr r1, [r1]
	cmp r1, #1
	bne _021EF5DA
	add r0, #0xa0
	ldrb r0, [r0]
	cmp r0, #0
	bne _021EF5DA
	mov r0, #1
	bx lr
_021EF5DA:
	mov r0, #0
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EF5E0
ov05_021EF5E0: ; 0x021EF5E0
	push {r4, r5}
	add r5, r0, #0
	add r4, r1, #0
	add r2, r4, #0
	add r3, r5, #0
	ldmia r3!, {r0, r1}
	add r2, #0xcc
	stmia r2!, {r0, r1}
	ldr r0, [r3]
	add r4, #0xd8
	str r0, [r2]
	str r5, [r4]
	pop {r4, r5}
	bx lr

	thumb_func_start ov05_021EF5FC
ov05_021EF5FC: ; 0x021EF5FC
	mov r1, #0
	add r0, #0xd8
	str r1, [r0]
	bx lr

	thumb_func_start ov05_021EF604
ov05_021EF604: ; 0x021EF604
	lsl r0, r0, #2
	add r0, r1, r0
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF614 ; =0x00000868
	ldr r0, [r1, r0]
	str r0, [r2]
	bx lr
	.balign 4, 0
_021EF614: .word 0x00000868

	thumb_func_start ov05_021EF618
ov05_021EF618: ; 0x021EF618
	add r0, #0xac
	ldrb r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EF620
ov05_021EF620: ; 0x021EF620
	push {r4, lr}
	add r4, r0, #0
	bl _u32_div_f
	lsr r2, r0, #0x1f
	lsl r1, r0, #0x1b
	sub r1, r1, r2
	mov r0, #0x1b
	ror r1, r0
	mov r0, #0x1f
	and r0, r4
	add r1, r2, r1
	cmp r0, #0x10
	bge _021EF648
	cmp r1, #0x10
	bge _021EF644
	mov r0, #0
	pop {r4, pc}
_021EF644:
	mov r0, #2
	pop {r4, pc}
_021EF648:
	cmp r1, #0x10
	bge _021EF650
	mov r0, #1
	pop {r4, pc}
_021EF650:
	mov r0, #3
	pop {r4, pc}

	thumb_func_start ov05_021EF654
ov05_021EF654: ; 0x021EF654
	push {r3, r4, r5, lr}
	add r4, r2, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	cmp r0, r5
	bne _021EF66A
	add r4, #0xac
	ldrb r0, [r4]
	pop {r3, r4, r5, pc}
_021EF66A:
	mov r0, #0
	mvn r0, r0
	cmp r5, r0
	bne _021EF676
	bl GF_AssertFail
_021EF676:
	add r0, r4, #0
	add r0, #0xac
	ldrb r1, [r0]
	cmp r1, #3
	bls _021EF682
	b _021EF820
_021EF682:
	add r0, r1, r1
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EF68E: ; jump table
	.short _021EF696 - _021EF68E - 2 ; case 0
	.short _021EF6F8 - _021EF68E - 2 ; case 1
	.short _021EF75C - _021EF68E - 2 ; case 2
	.short _021EF7BE - _021EF68E - 2 ; case 3
_021EF696:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r5, r0
	cmp r2, r3
	bne _021EF6B0
	add r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF6B0:
	cmp r3, #1
	bne _021EF6CA
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	beq _021EF6CA
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF6CA:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa4
	add r1, #0xc0
	ldr r2, [r1]
	ldr r0, [r0]
	add r3, r2, #1
	sub r1, r5, r0
	cmp r3, r1
	bne _021EF6F4
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EF6F4
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF6F4:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF6F8:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r5, r0
	cmp r2, r3
	bne _021EF712
	add r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF712:
	sub r1, r0, r5
	cmp r1, #1
	bne _021EF72E
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	beq _021EF72E
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF72E:
	add r0, r4, #0
	add r1, r4, #0
	add r0, #0xa4
	add r1, #0xc0
	ldr r2, [r1]
	ldr r0, [r0]
	sub r3, r2, #1
	sub r1, r5, r0
	cmp r3, r1
	bne _021EF758
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EF758
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF758:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF75C:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r0, r5
	cmp r2, r3
	bne _021EF776
	sub r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF776:
	sub r1, r2, #1
	cmp r1, r3
	bne _021EF792
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EF792
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF792:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	sub r1, r5, r0
	cmp r1, #1
	bne _021EF7BA
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	beq _021EF7BA
	add r4, #0xac
	ldrb r0, [r4]
	add r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF7BA:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF7BE:
	add r0, r4, #0
	add r0, #0xa4
	add r2, r4, #0
	ldr r0, [r0]
	add r2, #0xc0
	ldr r2, [r2]
	sub r3, r0, r5
	cmp r2, r3
	bne _021EF7D8
	sub r0, r1, #2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF7D8:
	add r1, r2, #1
	cmp r1, r3
	bne _021EF7F4
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	bne _021EF7F4
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #3
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF7F4:
	add r0, r4, #0
	add r0, #0xa4
	ldr r0, [r0]
	sub r1, r0, r5
	cmp r1, #1
	bne _021EF81C
	add r2, r4, #0
	add r2, #0xc0
	ldr r2, [r2]
	add r1, r5, #0
	bl ov05_021EDE58
	cmp r0, #0
	beq _021EF81C
	add r4, #0xac
	ldrb r0, [r4]
	sub r0, r0, #1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, r4, r5, pc}
_021EF81C:
	mov r0, #4
	pop {r3, r4, r5, pc}
_021EF820:
	mov r0, #4
	pop {r3, r4, r5, pc}

	thumb_func_start ov05_021EF824
ov05_021EF824: ; 0x021EF824
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r4, r0, #0
	cmp r5, #4
	blo _021EF832
	bl GF_AssertFail
_021EF832:
	lsl r0, r5, #2
	add r0, r4, r0
	add r0, #0x90
	ldr r1, [r0]
	mov r0, #0x86
	lsl r0, r0, #4
	ldr r0, [r1, r0]
	pop {r3, r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF844
ov05_021EF844: ; 0x021EF844
	push {r3, r4, r5, r6, r7, lr}
	add r6, r2, #0
	asr r2, r6, #4
	add r5, r0, #0
	lsr r2, r2, #0x1b
	add r2, r6, r2
	add r4, r1, #0
	add r0, #0xc0
	ldr r1, [r0]
	asr r0, r4, #4
	lsr r0, r0, #0x1b
	add r0, r4, r0
	asr r2, r2, #5
	str r3, [sp]
	add r3, r2, #0
	asr r0, r0, #5
	mul r3, r1
	add r7, r0, r3
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r1
	cmp r7, r0
	blo _021EF882
	mov r0, #1
	bl sub_020336A0
	cmp r0, #0
	beq _021EF882
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EF882:
	add r0, r5, #0
	add r0, #0xc0
	ldr r1, [r0]
	add r0, r5, #0
	add r0, #0xc4
	ldr r0, [r0]
	mul r0, r1
	cmp r7, r0
	blo _021EF898
	bl GF_AssertFail
_021EF898:
	add r0, r5, #0
	add r0, #0xc8
	ldr r1, [r0]
	add r0, r6, #0
	mul r0, r1
	add r0, r4, r0
	bl ov05_021EF620
	add r1, r0, #0
	add r0, r7, #0
	add r2, r5, #0
	bl ov05_021EF654
	ldr r1, [sp]
	cmp r1, #0
	beq _021EF8BA
	strb r0, [r1]
_021EF8BA:
	cmp r0, #3
	bls _021EF8C2
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_021EF8C2:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0

	thumb_func_start ov05_021EF8C8
ov05_021EF8C8: ; 0x021EF8C8
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0x90
	ldr r1, [r0]
	ldr r0, _021EF8D8 ; =0x0000085C
	ldr r0, [r1, r0]
	bx lr
	nop
_021EF8D8: .word 0x0000085C

	thumb_func_start ov05_021EF8DC
ov05_021EF8DC: ; 0x021EF8DC
	lsl r1, r1, #2
	add r0, r0, r1
	add r0, #0x90
	ldr r0, [r0]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EF8E8
ov05_021EF8E8: ; 0x021EF8E8
	add r3, r0, #0
	add r3, #0xfc
	str r1, [r3]
	mov r1, #1
	lsl r1, r1, #8
	str r2, [r0, r1]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021EF8F8
ov05_021EF8F8: ; 0x021EF8F8
	push {r3, lr}
	bl sub_0201B6C8
	mov r1, #1
	str r1, [r0, #0x1c]
	pop {r3, pc}

	thumb_func_start ov05_021EF904
ov05_021EF904: ; 0x021EF904
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	bne _021EF914
	mov r0, #5
	strb r0, [r4, #0x14]
_021EF914:
	ldrb r0, [r4, #0x14]
	cmp r0, #5
	bhi _021EF9FE
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021EF926: ; jump table
	.short _021EF932 - _021EF926 - 2 ; case 0
	.short _021EF962 - _021EF926 - 2 ; case 1
	.short _021EF998 - _021EF926 - 2 ; case 2
	.short _021EF9B6 - _021EF926 - 2 ; case 3
	.short _021EF9FE - _021EF926 - 2 ; case 4
	.short _021EF9EC - _021EF926 - 2 ; case 5
_021EF932:
	mov r0, #0
	str r0, [r4, #0x24]
	mov r0, #0xe
	ldr r5, [r4, #4]
	lsl r0, r0, #0xc
	cmp r5, r0
	bgt _021EF944
	mov r0, #2
	b _021EF948
_021EF944:
	add r5, r0, #0
	mov r0, #1
_021EF948:
	strb r0, [r4, #0x14]
	ldr r2, [r4, #0xc]
	ldr r0, [r4]
	ldr r3, [r2]
	ldr r2, [r4, #0x24]
	add r1, r5, #0
	add r2, r3, r2
	bl NARC_ReadFile
	ldr r0, [r4, #0x24]
	add r0, r0, r5
	str r0, [r4, #0x24]
	pop {r4, r5, r6, pc}
_021EF962:
	ldr r2, [r4, #0x24]
	ldr r0, [r4, #4]
	sub r5, r0, r2
	mov r0, #0xe
	lsl r0, r0, #0xc
	cmp r5, r0
	ble _021EF976
	add r5, r0, #0
	mov r6, #0
	b _021EF978
_021EF976:
	mov r6, #1
_021EF978:
	ldr r3, [r4, #0xc]
	ldr r0, [r4]
	ldr r3, [r3]
	add r1, r5, #0
	add r2, r3, r2
	bl NARC_ReadFile
	cmp r6, #0
	beq _021EF990
	mov r0, #2
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_021EF990:
	ldr r0, [r4, #0x24]
	add r0, r0, r5
	str r0, [r4, #0x24]
	pop {r4, r5, r6, pc}
_021EF998:
	ldr r0, [r4, #0x10]
	cmp r0, #0
	beq _021EF9B0
	bl sub_0201B254
	cmp r0, #1
	bne _021EF9B0
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	ldr r0, [r0]
	bl sub_0201B3A8
_021EF9B0:
	mov r0, #3
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_021EF9B6:
	ldr r0, [r4, #0xc]
	ldr r0, [r0]
	bl NNS_G3dGetMdlSet
	add r5, r0, #0
	ldrb r0, [r5, #9]
	cmp r0, #1
	beq _021EF9CA
	bl GF_AssertFail
_021EF9CA:
	ldrh r0, [r5, #0xe]
	add r0, r5, r0
	ldr r0, [r0, #0xc]
	add r5, r5, r0
	bne _021EF9D8
	bl GF_AssertFail
_021EF9D8:
	ldr r0, [r4, #8]
	add r1, r5, #0
	bl NNS_G3dRenderObjInit
	ldr r0, [r4, #0x18]
	mov r1, #1
	str r1, [r0]
	mov r0, #5
	strb r0, [r4, #0x14]
	pop {r4, r5, r6, pc}
_021EF9EC:
	ldr r0, [r4, #0x20]
	mov r1, #0
	str r1, [r0]
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl sub_0200CAB4
_021EF9FE:
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021EFA00
ov05_021EFA00: ; 0x021EFA00
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r4, r1, #0
	mov r0, #4

	thumb_func_start ov05_021EFA08
ov05_021EFA08: ; 0x021EFA08
	mov r1, #0x28
	add r6, r2, #0
	add r7, r3, #0
	bl AllocFromHeapAtEnd
	add r1, r0, #0
	str r5, [r1]
	str r4, [r1, #4]
	str r6, [r1, #8]
	ldr r0, [sp, #0x18]
	str r7, [r1, #0xc]
	str r0, [r1, #0x10]
	mov r2, #0
	ldr r0, [sp, #0x1c]
	strb r2, [r1, #0x14]
	str r0, [r1, #0x18]
	str r2, [r0]
	ldr r0, [sp, #0x20]
	str r0, [r1, #0x20]
	str r2, [r1, #0x1c]
	ldr r0, _021EFA3C ; =ov05_021EF904
	mov r2, #1
	bl sub_0200CA44
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021EFA3C: .word ov05_021EF904

	thumb_func_start ov05_021EFA40
ov05_021EFA40: ; 0x021EFA40
	push {r3, r4, r5, lr}
	add r4, r3, #0
	add r5, r2, #0
	ldr r2, [r4]
	bl NARC_ReadFile
	ldr r0, [sp, #0x10]
	cmp r0, #0
	beq _021EFA6A
	bl sub_0201B254
	cmp r0, #1
	bne _021EFA6A
	ldr r0, [r4]
	ldr r1, [sp, #0x10]
	bl sub_0201B3A8
	cmp r0, #0
	bne _021EFA6A
	bl GF_AssertFail
_021EFA6A:
	ldr r0, [r4]
	bl NNS_G3dGetMdlSet
	ldrb r0, [r0, #9]
	cmp r0, #1
	beq _021EFA7A
	bl GF_AssertFail
_021EFA7A:
	ldr r0, [r4]
	bl NNS_G3dGetMdlSet
	ldrh r1, [r0, #0xe]
	add r1, r0, r1
	ldr r1, [r1, #0xc]
	add r4, r0, r1
	bne _021EFA8E
	bl GF_AssertFail
_021EFA8E:
	add r0, r5, #0
	add r1, r4, #0
	bl NNS_G3dRenderObjInit
	add r0, r4, #0
	pop {r3, r4, r5, pc}
	.balign 4, 0

	.section .rodata

	.global ov05_021F8B04
ov05_021F8B04: ; 0x021F8B04
	.word ov05_021EF16C, ov05_021EE114

	.global ov05_021F8B0C
ov05_021F8B0C: ; 0x021F8B0C
	.word ov05_021EF1FC, ov05_021EE1E4

	.global ov05_021F8B14
ov05_021F8B14: ; 0x021F8B14
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
	.byte 0x00, 0x10, 0x00, 0x00

	.global ov05_021F8B20
ov05_021F8B20: ; 0x021F8B20
	.byte 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
