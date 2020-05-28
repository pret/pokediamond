	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global cAdpcmIndexTable2
cAdpcmIndexTable2: ; 0x020FF5B8
	.byte 0xFF, 0x01, 0xFF, 0x01

	.global cAdpcmIndexTable3
cAdpcmIndexTable3: ; 0x020FF5BC
	.byte 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x01, 0x02

	.global cAdpcmIndexTable4
cAdpcmIndexTable4: ; 0x020FF5C4
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x04, 0x06, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x04, 0x06, 0x08

	.global cAdpcmStepSizeTable
cAdpcmStepSizeTable: ; 0x020FF5D4
	.short 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E
	.short 0x0010, 0x0011, 0x0013, 0x0015, 0x0017, 0x0019, 0x001C, 0x001F
	.short 0x0022, 0x0025, 0x0029, 0x002D, 0x0032, 0x0037, 0x003C, 0x0042
	.short 0x0049, 0x0050, 0x0058, 0x0061, 0x006B, 0x0076, 0x0082, 0x008F
	.short 0x009D, 0x00AD, 0x00BE, 0x00D1, 0x00E6, 0x00FD, 0x0117, 0x0133
	.short 0x0151, 0x0173, 0x0198, 0x01C1, 0x01EE, 0x0220, 0x0256, 0x0292
	.short 0x02D4, 0x031C, 0x036C, 0x03C3, 0x0424, 0x048E, 0x0502, 0x0583
	.short 0x0610, 0x06AB, 0x0756, 0x0812, 0x08E0, 0x09C3, 0x0ABD, 0x0BD0
	.short 0x0CFF, 0x0E4C, 0x0FBA, 0x114C, 0x1307, 0x14EE, 0x1706, 0x1954
	.short 0x1BDC, 0x1EA5, 0x21B6, 0x2515, 0x28CA, 0x2CDF, 0x315B, 0x364B
	.short 0x3BB9, 0x41B2, 0x4844, 0x4F7E, 0x5771, 0x602F, 0x69CE, 0x7462
	.short 0x7FFF, 0x0000

	.global sCodecInfo
sCodecInfo: ; 0x020FF688
	.byte 0x08, 0x00
	.byte 0x08, 0x00
	.byte 0x02, 0x04
	.byte 0x03, 0x04
	.byte 0x04, 0x04

	.balign 4, 0
	.global UNK_020FF694
UNK_020FF694: ; 0x020FF694
	.byte 0x01, 0x00, 0x00
	.byte 0x01, 0x01, 0x00
	.byte 0x01, 0x01, 0x01
	.byte 0x01, 0x01, 0x02
	.byte 0x01, 0x02, 0x02
	.byte 0x02, 0x02, 0x02
	.byte 0x02, 0x02, 0x03

	.balign 4, 0
	.global UNK_020FF6AC
UNK_020FF6AC: ; 0x020FF6AC
	.byte 0x01, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF6B4
UNK_020FF6B4: ; 0x020FF6B4
	.byte 0x07, 0x0C, 0x02, 0x03, 0x09, 0x02, 0x00, 0x00

	.global UNK_020FF6BC
UNK_020FF6BC: ; 0x020FF6BC
	.byte 0x04, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0x02, 0x00, 0x00, 0x00, 0xFF, 0x00
	.byte 0xFE, 0x05, 0x05, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0x05, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF

	.balign 4, 0
	.global UNK_020FF700
UNK_020FF700: ; 0x020FF700
	.byte 0xFE, 0xFE, 0xFE, 0x03, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0xFE, 0xFD, 0xFF, 0x02, 0x00, 0x00, 0x00, 0xFF, 0x00
	.byte 0xFE, 0xFE, 0xFE, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0x00, 0xFE, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0xFE, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFE, 0xFE, 0xFE, 0xFD, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF

	.balign 4, 0
	.global UNK_020FF744
UNK_020FF744: ; 0x020FF744
	.byte 0x01, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0xFE, 0xFE
	.byte 0xFE, 0xFE, 0x05, 0xFE, 0xFE, 0xFE, 0x00, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0xFE, 0x05, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x02, 0x00, 0x00, 0x00, 0xFE, 0x00
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0xFE

	.balign 4, 0
	.global UNK_020FF788
UNK_020FF788: ; 0x020FF788
	.byte 0xFE, 0xFE, 0xFE, 0x01, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0xFE, 0xFE
	.byte 0xFE, 0x05, 0x05, 0xFE, 0xFF, 0xFE, 0x00, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0xFE, 0x05, 0xFE, 0xFE, 0xFF, 0xFE, 0x00, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFE, 0x00, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFE, 0x00
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0xFE

	.section .data

	.global UNK_0210646C
UNK_0210646C: ; 0x0210646C
	.word 1

	.global UNK_02106470
UNK_02106470: ; 0x02106470
	.word 0x0000003F
	.word 0x0000007F
	.word 0x000000FF
	.word 0x000001FF
	.word 0x000003FF
	.word 0x000007FF
	.word 0x00000FFF
	.word 0x00001FFF

	.global UNK_02106490
UNK_02106490: ; 0x02106490
	; u64
	.word 15709687, 0

	.global UNK_02106498
UNK_02106498: ; 0x02106498
	.word 0x00000000, 0x00000000, 0x0000000F, 0x000003FC

	.global UNK_021064A8
UNK_021064A8: ; 0x021064A8
	.short 0xE9FB, 0x403D, 0xC7BC, 0x2CD1, 0xD02A, 0x037C, 0x08F0, 0xF593

	.bss

	.global UNK_021CA8B0
UNK_021CA8B0: ; 0x021CA8B0
	.space 0x4

	.global sBitmap
sBitmap: ; 0x021CA8B4
	.space 0x4

	.global UNK_021CA8B8
UNK_021CA8B8: ; 0x021CA8B8
	.space 0x4

	.global UNK_021CA8BC
UNK_021CA8BC: ; 0x021CA8BC
	.space 0x4

	.global UNK_021CA8C0
UNK_021CA8C0: ; 0x021CA8C0
	.space 0x4

	.global UNK_021CA8C4
UNK_021CA8C4: ; 0x021CA8C4
	.space 0x4

	.global UNK_021CA8C8
UNK_021CA8C8: ; 0x021CA8C8
	.space 0x4

	.global UNK_021CA8CC
UNK_021CA8CC: ; 0x021CA8CC
	.space 0x4

	.global sNumStream
sNumStream: ; 0x021CA8D0
	.space 0x4

	.global UNK_021CA8D4
UNK_021CA8D4: ; 0x021CA8D4
	.space 0x4

	.global UNK_021CA8D8
UNK_021CA8D8: ; 0x021CA8D8
	.space 0x4

	.global UNK_021CA8DC
UNK_021CA8DC: ; 0x021CA8DC
	.space 0xc

	.global sStream
sStream: ; 0x021CA8E8
	.space 0x1bc

	.global UNK_021CAAA4
UNK_021CAAA4: ; 0x021CAAA4
	.space 0x45c

	.global UNK_021CAF00
UNK_021CAF00: ; 0x021CAF00
	.space 0x8d8

	.global UNK_021CB7D8
UNK_021CB7D8: ; 0x021CB7D8
	.space 0x4

	.global UNK_021CB7DC
UNK_021CB7DC: ; 0x021CB7DC
	.space 0x4

	.global UNK_021CB7E0
UNK_021CB7E0: ; 0x021CB7E0
	.space 0xc

	.global UNK_021CB7EC
UNK_021CB7EC: ; 0x021CB7EC
	.space 0x4

	.global UNK_021CB7F0
UNK_021CB7F0: ; 0x021CB7F0
	.space 0xc

	.global sCount
sCount: ; 0x021CB7FC
	.space 0xc

	.global UNK_021CB808
UNK_021CB808: ; 0x021CB808
	.space 0xc

	.global UNK_021CB814
UNK_021CB814: ; 0x021CB814
	.space 0x4

	.global UNK_021CB818
UNK_021CB818: ; 0x021CB818
	.space 0x4

	.global UNK_021CB81C
UNK_021CB81C: ; 0x021CB81C
	.space 0x8

	.global UNK_021CB824
UNK_021CB824: ; 0x021CB824
	.space 0x14

	.global UNK_021CB838
UNK_021CB838: ; 0x021CB838
	.space 0x18

	.global UNK_021CB850
UNK_021CB850: ; 0x021CB850
	.space 0x18

	.global UNK_021CB868
UNK_021CB868: ; 0x021CB868
	.space 0x4

	.global UNK_021CB86C
UNK_021CB86C: ; 0x021CB86C
	.space 0x4

	.global UNK_021CB870
UNK_021CB870: ; 0x021CB870
	.space 0x4

	.global UNK_021CB874
UNK_021CB874: ; 0x021CB874
	.space 0x4

	.global UNK_021CB878
UNK_021CB878: ; 0x021CB878
	.space 0x4

	.global UNK_021CB87C
UNK_021CB87C: ; 0x021CB87C
	.space 0x4

	.global UNK_021CB880
UNK_021CB880: ; 0x021CB880
	.space 0x10

	.global UNK_021CB890
UNK_021CB890: ; 0x021CB890
	.space 0x4

	.global UNK_021CB894
UNK_021CB894: ; 0x021CB894
	.space 0x4

	.global UNK_021CB898
UNK_021CB898: ; 0x021CB898
	.space 0x4

	.global UNK_021CB89C
UNK_021CB89C: ; 0x021CB89C
	.space 0x4

	.global UNK_021CB8A0
UNK_021CB8A0: ; 0x021CB8A0
	.space 0x4

	.global UNK_021CB8A4
UNK_021CB8A4: ; 0x021CB8A4
	.space 0x18

	.global UNK_021CB8BC
UNK_021CB8BC: ; 0x021CB8BC
	.space 0x18

	.global UNK_021CB8D4
UNK_021CB8D4: ; 0x021CB8D4
	.space 0x440

	.global UNK_021CBD14
UNK_021CBD14: ; 0x021CBD14
	.space 0x1000

	.global UNK_021CCD14
UNK_021CCD14: ; 0x021CCD14
	.space 0x4

	.global sRecvPerFrame
sRecvPerFrame: ; 0x021CCD18
	.space 0x4

	.global initialized
initialized: ; 0x021CCD1C
	.space 0x4

	.global __vct
__vct: ; 0x021CCD20
	.space 0x18

	.text

; libvct.a:adpcm.o

	arm_func_start vct_encode_adpcm
vct_encode_adpcm: ; 0x020A8BC8
	stmdb sp!, {r4,lr}
	ldrsh r4, [r3, #0x0]
	ldr r12, [sp, #0x8]
	mov lr, #0x0
	strh r4, [r0, #0x0]
	ldrb r4, [r3, #0x2]
	cmp r12, #0x2
	strb r4, [r0, #0x2]
	strb lr, [r0, #0x3]
	beq _020A8C04
	cmp r12, #0x3
	beq _020A8C10
	cmp r12, #0x4
	beq _020A8C1C
	ldmia sp!, {r4,pc}
_020A8C04:
	add r0, r0, #0x4
	bl vct_encode_adpcm_16
	ldmia sp!, {r4,pc}
_020A8C10:
	add r0, r0, #0x4
	bl vct_encode_adpcm_24
	ldmia sp!, {r4,pc}
_020A8C1C:
	add r0, r0, #0x4
	bl vct_encode_adpcm_32
	ldmia sp!, {r4,pc}

	arm_func_start vct_decode_adpcm
vct_decode_adpcm: ; 0x020A8C28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrsh r12, [r0, #0x0]
	cmp r3, #0x2
	strh r12, [sp, #0x0]
	ldrb r12, [r0, #0x2]
	strb r12, [sp, #0x2]
	beq _020A8C60
	cmp r3, #0x3
	beq _020A8C78
	cmp r3, #0x4
	beq _020A8C90
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020A8C60:
	add r3, sp, #0x0
	add r0, r0, #0x4
	sub r2, r2, #0x4
	bl vct_decode_adpcm_16
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020A8C78:
	add r3, sp, #0x0
	add r0, r0, #0x4
	sub r2, r2, #0x4
	bl vct_decode_adpcm_24
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020A8C90:
	add r3, sp, #0x0
	add r0, r0, #0x4
	sub r2, r2, #0x4
	bl vct_decode_adpcm_32
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start vct_encode_adpcm_16
vct_encode_adpcm_16: ; 0x020A8CA8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x3c
	movs r2, r2, lsr #0x2
	str r2, [sp, #0x4]
	mov r2, #0x0
	str r2, [sp, #0x0]
	addeq sp, sp, #0x3c
	ldmeqia sp!, {r4-r11,pc}
	mov r5, #0x8000
	ldr fp, _020A8F4C ; =cAdpcmStepSizeTable
	ldr r4, _020A8F50 ; =0x00007FFF
	str r2, [sp, #0x8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	rsb r5, r5, #0x0
	mov r6, #0x2
	mov lr, #0x58
	str r2, [sp, #0x1c]
	str r2, [sp, #0x20]
	str r2, [sp, #0x24]
	str r2, [sp, #0x28]
	str r2, [sp, #0x2c]
	str r2, [sp, #0x30]
	str r2, [sp, #0x34]
_020A8D10:
	ldrb r9, [r3, #0x2]
	ldrsh r2, [r3, #0x0]
	ldrsh r7, [r1, #0x0]
	mov r10, r9, lsl #0x1
	ldrsh r10, [r11, r10]
	subs r8, r7, r2
	movmi r7, r6
	ldrpl r7, [sp, #0x8]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x1
	ands r8, r7, #0x1
	ldreq r10, [sp, #0xc]
	ands r8, r7, #0x2
	rsbne r10, r10, #0x0
	mov r8, #0x8000
	add r2, r2, r10
	rsb r8, r8, #0x0
	cmp r2, r8
	ldr r8, _020A8F54 ; =cAdpcmIndexTable2
	movlt r2, r5
	cmp r2, r4
	ldrsb r8, [r8, r7]
	movgt r2, r4
	adds r9, r9, r8
	ldrmi r9, [sp, #0x10]
	bmi _020A8D84
	cmp r9, #0x58
	movgt r9, lr
_020A8D84:
	strh r2, [r3, #0x0]
	strb r9, [r3, #0x2]
	ldrb r10, [r3, #0x2]
	and r2, r7, #0xff
	ldrsh r7, [r3, #0x0]
	ldrsh r8, [r1, #0x2]
	mov r12, r10, lsl #0x1
	ldrsh r12, [r11, r12]
	subs r9, r8, r7
	movmi r8, r6
	ldrpl r8, [sp, #0x14]
	rsbmi r9, r9, #0x0
	cmp r9, r12
	orrge r8, r8, #0x1
	ands r9, r8, #0x1
	ldreq r12, [sp, #0x18]
	ands r9, r8, #0x2
	rsbne r12, r12, #0x0
	mov r9, #0x8000
	add r7, r7, r12
	rsb r9, r9, #0x0
	cmp r7, r9
	ldr sb, _020A8F54 ; =cAdpcmIndexTable2
	movlt r7, r5
	cmp r7, r4
	ldrsb r9, [r9, r8]
	movgt r7, r4
	adds r10, r10, r9
	ldrmi r10, [sp, #0x1c]
	bmi _020A8E04
	cmp r10, #0x58
	movgt r10, lr
_020A8E04:
	strh r7, [r3, #0x0]
	strb r10, [r3, #0x2]
	and r7, r8, #0xff
	orr r2, r2, r7, lsl #0x2
	ldrb r10, [r3, #0x2]
	ldrsh r7, [r3, #0x0]
	ldrsh r8, [r1, #0x4]
	mov r12, r10, lsl #0x1
	ldrsh r12, [r11, r12]
	subs r9, r8, r7
	movmi r8, r6
	ldrpl r8, [sp, #0x20]
	rsbmi r9, r9, #0x0
	cmp r9, r12
	orrge r8, r8, #0x1
	ands r9, r8, #0x1
	ldreq r12, [sp, #0x24]
	ands r9, r8, #0x2
	rsbne r12, r12, #0x0
	mov r9, #0x8000
	add r7, r7, r12
	rsb r9, r9, #0x0
	cmp r7, r9
	ldr sb, _020A8F54 ; =cAdpcmIndexTable2
	movlt r7, r5
	cmp r7, r4
	ldrsb r9, [r9, r8]
	movgt r7, r4
	and r2, r2, #0xff
	adds r10, r10, r9
	ldrmi r10, [sp, #0x28]
	bmi _020A8E8C
	cmp r10, #0x58
	movgt r10, lr
_020A8E8C:
	strh r7, [r3, #0x0]
	strb r10, [r3, #0x2]
	and r7, r8, #0xff
	orr r2, r2, r7, lsl #0x4
	ldrb r10, [r3, #0x2]
	ldrsh r8, [r1, #0x6]
	ldrsh r7, [r3, #0x0]
	mov r12, r10, lsl #0x1
	ldrsh r12, [r11, r12]
	subs r9, r8, r7
	movmi r8, r6
	ldrpl r8, [sp, #0x2c]
	rsbmi r9, r9, #0x0
	cmp r9, r12
	orrge r8, r8, #0x1
	ands r9, r8, #0x1
	ldreq r12, [sp, #0x30]
	ands r9, r8, #0x2
	rsbne r12, r12, #0x0
	mov r9, #0x8000
	add r7, r7, r12
	rsb r9, r9, #0x0
	cmp r7, r9
	ldr sb, _020A8F54 ; =cAdpcmIndexTable2
	movlt r7, r5
	cmp r7, r4
	ldrsb r9, [r9, r8]
	movgt r7, r4
	and r2, r2, #0xff
	adds r10, r10, r9
	add r1, r1, #0x8
	ldrmi r10, [sp, #0x34]
	bmi _020A8F18
	cmp r10, #0x58
	movgt r10, lr
_020A8F18:
	strh r7, [r3, #0x0]
	and r7, r8, #0xff
	strb r10, [r3, #0x2]
	orr r2, r2, r7, lsl #0x6
	strb r2, [r0], #0x1
	ldr r2, [sp, #0x0]
	add r7, r2, #0x1
	ldr r2, [sp, #0x4]
	str r7, [sp, #0x0]
	cmp r7, r2
	blo _020A8D10
	add sp, sp, #0x3c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A8F4C: .word cAdpcmStepSizeTable
_020A8F50: .word 0x00007FFF
_020A8F54: .word cAdpcmIndexTable2

	arm_func_start vct_decode_adpcm_16
vct_decode_adpcm_16: ; 0x020A8F58
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	cmp r2, #0x0
	addls sp, sp, #0x34
	mov r12, #0x0
	ldmlsia sp!, {r4-r11,pc}
	mov r4, #0x8000
	rsb r6, r4, #0x0
	ldr r5, _020A91CC ; =0x00007FFF
	ldr fp, _020A91D0 ; =cAdpcmStepSizeTable
	str r12, [sp, #0x0]
	str r12, [sp, #0x8]
	str r12, [sp, #0xc]
	str r12, [sp, #0x14]
	str r12, [sp, #0x18]
	mov r4, #0x58
	str r12, [sp, #0x20]
	str r12, [sp, #0x24]
	str r12, [sp, #0x2c]
_020A8FA4:
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0x0]
	ands lr, r10, #0x2
	str lr, [sp, #0x4]
	beq _020A8FE8
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A8FF4
_020A8FE8:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A8FF4:
	ldr r7, _020A91D4 ; =cAdpcmIndexTable2
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x8]
	bmi _020A9010
	cmp r8, #0x58
	movgt r8, r4
_020A9010:
	mov r7, r9, lsl #0x10
	mov r7, r7, asr #0x10
	strh r7, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r7, [r1, #0x0]
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	mov r7, r7, asr #0x2
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0xc]
	ands lr, r10, #0x2
	str lr, [sp, #0x10]
	beq _020A906C
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A9078
_020A906C:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A9078:
	ldr r7, _020A91D4 ; =cAdpcmIndexTable2
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x14]
	bmi _020A9094
	cmp r8, #0x58
	movgt r8, r4
_020A9094:
	mov r7, r9, lsl #0x10
	mov r7, r7, asr #0x10
	strh r7, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r7, [r1, #0x2]
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	mov r7, r7, asr #0x4
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0x18]
	ands lr, r10, #0x2
	str lr, [sp, #0x1c]
	beq _020A90F0
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A90FC
_020A90F0:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A90FC:
	ldr r7, _020A91D4 ; =cAdpcmIndexTable2
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x20]
	bmi _020A9118
	cmp r8, #0x58
	movgt r8, r4
_020A9118:
	mov r7, r9, lsl #0x10
	mov r7, r7, asr #0x10
	strh r7, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r7, [r1, #0x4]
	ldrb r7, [r0, #0x0]
	ldrb r8, [r3, #0x2]
	ldrsh r9, [r3, #0x0]
	mov r7, r7, asr #0x6
	and r10, r7, #0x3
	ands r7, r10, #0x1
	mov r7, r8, lsl #0x1
	ldrsh r7, [r11, r7]
	ldreq r7, [sp, #0x24]
	ands lr, r10, #0x2
	str lr, [sp, #0x28]
	beq _020A9174
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r6
	b _020A9180
_020A9174:
	add r9, r9, r7
	cmp r9, r5
	movgt r9, r5
_020A9180:
	ldr r7, _020A91D4 ; =cAdpcmIndexTable2
	ldrsb r7, [r7, r10]
	adds r8, r8, r7
	ldrmi r8, [sp, #0x2c]
	bmi _020A919C
	cmp r8, #0x58
	movgt r8, r4
_020A919C:
	mov r7, r9, lsl #0x10
	mov r9, r7, asr #0x10
	strh r9, [r3, #0x0]
	strb r8, [r3, #0x2]
	add r12, r12, #0x1
	strh r9, [r1, #0x6]
	add r1, r1, #0x8
	add r0, r0, #0x1
	cmp r12, r2
	blo _020A8FA4
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A91CC: .word 0x00007FFF
_020A91D0: .word cAdpcmStepSizeTable
_020A91D4: .word cAdpcmIndexTable2

	arm_func_start vct_encode_adpcm_24
vct_encode_adpcm_24: ; 0x020A91D8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	movs r2, r2, lsr #0x3
	str r2, [sp, #0x4]
	mov r2, #0x0
	str r2, [sp, #0x0]
	addeq sp, sp, #0x54
	ldmeqia sp!, {r4-r11,pc}
	ldr r5, [sp, #0x0]
	mov r4, #0x8000
	rsb lr, r4, #0x0
	ldr ip, _020A97D0 ; =0x00007FFF
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	str r2, [sp, #0x1c]
	str r2, [sp, #0x20]
	mov r4, #0x4
	mov r2, #0x58
	str r5, [sp, #0x24]
	str r5, [sp, #0x28]
	str r5, [sp, #0x2c]
	str r5, [sp, #0x30]
	str r5, [sp, #0x34]
	str r5, [sp, #0x38]
	str r5, [sp, #0x3c]
	str r5, [sp, #0x40]
	str r5, [sp, #0x44]
	str r5, [sp, #0x48]
	str r5, [sp, #0x4c]
_020A9250:
	ldrsh r8, [r3, #0x0]
	ldrsh r6, [r1, #0x0]
	ldrb r5, [r3, #0x2]
	subs r7, r6, r8
	movmi r10, r4
	ldr r6, _020A97D4 ; =cAdpcmStepSizeTable
	mov r9, r5, lsl #0x1
	ldrsh r6, [r6, r9]
	ldrpl r10, [sp, #0x10]
	rsbmi r7, r7, #0x0
	cmp r7, r6
	orrge r10, r10, #0x2
	subge r7, r7, r6
	mov r9, r6, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x2
	mov r7, r6, asr #0x2
	addne r7, r7, r6
	ands r6, r10, #0x1
	addne r7, r7, r9
	ands r6, r10, #0x4
	rsbne r7, r7, #0x0
	add r6, r8, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r6, r7
	ldr r7, _020A97D8 ; =cAdpcmIndexTable3
	movlt r6, lr
	cmp r6, r12
	ldrsb r7, [r7, r10]
	movgt r6, r12
	adds r5, r5, r7
	ldrmi r5, [sp, #0x14]
	bmi _020A92E4
	cmp r5, #0x58
	movgt r5, r2
_020A92E4:
	strh r6, [r3, #0x0]
	strb r5, [r3, #0x2]
	and r5, r10, #0xff
	mov r5, r5, lsl #0x5
	and r10, r5, #0xff
	ldrb r8, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r5, [r1, #0x2]
	mov r9, r8, lsl #0x1
	subs r7, r5, r11
	ldr r5, _020A97D4 ; =cAdpcmStepSizeTable
	movmi r6, r4
	ldrsh r9, [r5, r9]
	ldrpl r6, [sp, #0x18]
	rsbmi r7, r7, #0x0
	cmp r7, r9
	orrge r6, r6, #0x2
	subge r7, r7, r9
	mov r5, r9, asr #0x1
	cmp r7, r5
	orrge r6, r6, #0x1
	ands r7, r6, #0x2
	mov r7, r9, asr #0x2
	addne r7, r7, r9
	ands r9, r6, #0x1
	addne r7, r7, r5
	ands r5, r6, #0x4
	rsbne r7, r7, #0x0
	add r5, r11, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r5, r7
	ldr r7, _020A97D8 ; =cAdpcmIndexTable3
	movlt r5, lr
	cmp r5, r12
	ldrsb r7, [r7, r6]
	movgt r5, r12
	adds r8, r8, r7
	ldrmi r8, [sp, #0x1c]
	bmi _020A938C
	cmp r8, #0x58
	movgt r8, r2
_020A938C:
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	and r5, r6, #0xff
	orr r5, r10, r5, lsl #0x2
	and r10, r5, #0xff
	ldrb r8, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r5, [r1, #0x4]
	mov r9, r8, lsl #0x1
	subs r7, r5, r11
	ldr r5, _020A97D4 ; =cAdpcmStepSizeTable
	movmi r6, r4
	ldrsh r9, [r5, r9]
	ldrpl r6, [sp, #0x20]
	rsbmi r7, r7, #0x0
	cmp r7, r9
	orrge r6, r6, #0x2
	subge r7, r7, r9
	mov r5, r9, asr #0x1
	cmp r7, r5
	orrge r6, r6, #0x1
	ands r7, r6, #0x2
	mov r7, r9, asr #0x2
	addne r7, r7, r9
	ands r9, r6, #0x1
	addne r7, r7, r5
	ands r5, r6, #0x4
	rsbne r7, r7, #0x0
	add r5, r11, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r5, r7
	ldr r7, _020A97D8 ; =cAdpcmIndexTable3
	movlt r5, lr
	cmp r5, r12
	ldrsb r7, [r7, r6]
	movgt r5, r12
	adds r8, r8, r7
	ldrmi r8, [sp, #0x24]
	bmi _020A9434
	cmp r8, #0x58
	movgt r8, r2
_020A9434:
	strh r5, [r3, #0x0]
	and r5, r6, #0xff
	str r5, [sp, #0x8]
	strb r8, [r3, #0x2]
	orr r5, r10, r5, asr #0x1
	strb r5, [r0, #0x0]
	ldrb r5, [r3, #0x2]
	ldrsh r8, [r3, #0x0]
	ldrsh r6, [r1, #0x6]
	mov r9, r5, lsl #0x1
	subs r7, r6, r8
	ldr r6, _020A97D4 ; =cAdpcmStepSizeTable
	movmi r10, r4
	ldrsh r6, [r6, r9]
	ldrpl r10, [sp, #0x28]
	rsbmi r7, r7, #0x0
	cmp r7, r6
	orrge r10, r10, #0x2
	subge r7, r7, r6
	mov r9, r6, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x2
	mov r7, r6, asr #0x2
	addne r7, r7, r6
	ands r6, r10, #0x1
	addne r7, r7, r9
	ands r6, r10, #0x4
	rsbne r7, r7, #0x0
	add r6, r8, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r6, r7
	ldr r7, _020A97D8 ; =cAdpcmIndexTable3
	movlt r6, lr
	cmp r6, r12
	ldrsb r7, [r7, r10]
	movgt r6, r12
	adds r5, r5, r7
	ldrmi r5, [sp, #0x2c]
	bmi _020A94E0
	cmp r5, #0x58
	movgt r5, r2
_020A94E0:
	strh r6, [r3, #0x0]
	strb r5, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r6, [r1, #0x8]
	ldrb r9, [r3, #0x2]
	and r5, r10, #0xff
	subs r8, r6, r11
	movmi r7, r4
	ldr r6, _020A97D4 ; =cAdpcmStepSizeTable
	mov r10, r9, lsl #0x1
	ldrsh r10, [r6, r10]
	ldrpl r7, [sp, #0x30]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x2
	subge r8, r8, r10
	mov r6, r10, asr #0x1
	cmp r8, r6
	orrge r7, r7, #0x1
	ands r8, r7, #0x2
	mov r8, r10, asr #0x2
	addne r8, r8, r10
	ands r10, r7, #0x1
	addne r8, r8, r6
	ands r6, r7, #0x4
	rsbne r8, r8, #0x0
	add r6, r11, r8
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r6, r8
	ldr r8, _020A97D8 ; =cAdpcmIndexTable3
	movlt r6, lr
	mov r5, r5, lsl #0x4
	cmp r6, r12
	ldrsb r8, [r8, r7]
	movgt r6, r12
	and r5, r5, #0xff
	adds r9, r9, r8
	ldrmi r9, [sp, #0x34]
	bmi _020A9588
	cmp r9, #0x58
	movgt r9, r2
_020A9588:
	strh r6, [r3, #0x0]
	strb r9, [r3, #0x2]
	and r6, r7, #0xff
	orr r5, r5, r6, lsl #0x1
	ldrb r9, [r3, #0x2]
	ldrsh r11, [r3, #0x0]
	ldrsh r6, [r1, #0xa]
	mov r10, r9, lsl #0x1
	and r5, r5, #0xff
	subs r8, r6, r11
	ldr r6, _020A97D4 ; =cAdpcmStepSizeTable
	movmi r7, r4
	ldrsh r10, [r6, r10]
	ldrpl r7, [sp, #0x38]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x2
	subge r8, r8, r10
	mov r6, r10, asr #0x1
	cmp r8, r6
	orrge r7, r7, #0x1
	ands r8, r7, #0x2
	mov r8, r10, asr #0x2
	addne r8, r8, r10
	ands r10, r7, #0x1
	addne r8, r8, r6
	ands r6, r7, #0x4
	rsbne r8, r8, #0x0
	add r6, r11, r8
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r6, r8
	ldr r8, _020A97D8 ; =cAdpcmIndexTable3
	movlt r6, lr
	cmp r6, r12
	ldrsb r8, [r8, r7]
	movgt r6, r12
	adds r9, r9, r8
	ldrmi r9, [sp, #0x3c]
	bmi _020A9630
	cmp r9, #0x58
	movgt r9, r2
_020A9630:
	ldr r8, [sp, #0x8]
	strh r6, [r3, #0x0]
	orr r8, r5, r8, lsl #0x7
	and r5, r7, #0xff
	str r5, [sp, #0xc]
	strb r9, [r3, #0x2]
	orr r5, r8, r5, asr #0x2
	strb r5, [r0, #0x1]
	ldrb r5, [r3, #0x2]
	ldrsh r8, [r3, #0x0]
	ldrsh r6, [r1, #0xc]
	mov r9, r5, lsl #0x1
	subs r7, r6, r8
	ldr r6, _020A97D4 ; =cAdpcmStepSizeTable
	movmi r10, r4
	ldrsh r6, [r6, r9]
	ldrpl r10, [sp, #0x40]
	rsbmi r7, r7, #0x0
	cmp r7, r6
	orrge r10, r10, #0x2
	subge r7, r7, r6
	mov r9, r6, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x2
	mov r7, r6, asr #0x2
	addne r7, r7, r6
	ands r6, r10, #0x1
	addne r7, r7, r9
	ands r6, r10, #0x4
	rsbne r7, r7, #0x0
	add r6, r8, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r6, r7
	ldr r7, _020A97D8 ; =cAdpcmIndexTable3
	movlt r6, lr
	cmp r6, r12
	ldrsb r7, [r7, r10]
	movgt r6, r12
	adds r5, r5, r7
	ldrmi r5, [sp, #0x44]
	bmi _020A96E4
	cmp r5, #0x58
	movgt r5, r2
_020A96E4:
	strh r6, [r3, #0x0]
	strb r5, [r3, #0x2]
	and r5, r10, #0xff
	mov r5, r5, lsl #0x3
	and r11, r5, #0xff
	ldrsh r6, [r1, #0xe]
	ldrsh r5, [r3, #0x0]
	ldrb r9, [r3, #0x2]
	add r1, r1, #0x10
	subs r8, r6, r5
	movmi r7, r4
	ldr r6, _020A97D4 ; =cAdpcmStepSizeTable
	mov r10, r9, lsl #0x1
	ldrsh r10, [r6, r10]
	ldrpl r7, [sp, #0x48]
	rsbmi r8, r8, #0x0
	cmp r8, r10
	orrge r7, r7, #0x2
	subge r8, r8, r10
	mov r6, r10, asr #0x1
	cmp r8, r6
	orrge r7, r7, #0x1
	ands r8, r7, #0x2
	mov r8, r10, asr #0x2
	addne r8, r8, r10
	ands r10, r7, #0x1
	addne r8, r8, r6
	ands r6, r7, #0x4
	rsbne r8, r8, #0x0
	mov r6, #0x8000
	add r5, r5, r8
	rsb r6, r6, #0x0
	cmp r5, r6
	ldr r6, _020A97D8 ; =cAdpcmIndexTable3
	movlt r5, lr
	cmp r5, r12
	ldrsb r6, [r6, r7]
	movgt r5, r12
	adds r9, r9, r6
	ldrmi r9, [sp, #0x4c]
	bmi _020A9790
	cmp r9, #0x58
	movgt r9, r2
_020A9790:
	strh r5, [r3, #0x0]
	and r5, r7, #0xff
	orr r6, r11, r5
	ldr r5, [sp, #0xc]
	strb r9, [r3, #0x2]
	orr r5, r6, r5, lsl #0x6
	strb r5, [r0, #0x2]
	ldr r5, [sp, #0x0]
	add r0, r0, #0x3
	add r6, r5, #0x1
	ldr r5, [sp, #0x4]
	str r6, [sp, #0x0]
	cmp r6, r5
	blo _020A9250
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A97D0: .word 0x00007FFF
_020A97D4: .word cAdpcmStepSizeTable
_020A97D8: .word cAdpcmIndexTable3

	arm_func_start vct_decode_adpcm_24
vct_decode_adpcm_24: ; 0x020A97DC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	ldr r5, _020A9D08 ; =0xAAAAAAAB
	mov r4, #0x0
	str r4, [sp, #0x0]
	umull r5, r4, r2, r5
	str r4, [sp, #0xc]
	movs r2, r4, lsr #0x1
	str r2, [sp, #0xc]
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r11,pc}
	ldr r2, [sp, #0x0]
	mov r4, #0x8000
	ldr lr, _020A9D0C ; =0x00007FFF
	str r2, [sp, #0x18]
	str r2, [sp, #0x24]
	str r2, [sp, #0x2c]
	str r2, [sp, #0x34]
	str r2, [sp, #0x3c]
	rsb r4, r4, #0x0
	mov r12, #0x58
	str r2, [sp, #0x40]
	str r2, [sp, #0x44]
	str r2, [sp, #0x48]
_020A983C:
	ldrb r8, [r3, #0x2]
	ldr r5, _020A9D10 ; =cAdpcmStepSizeTable
	ldrb r6, [r0, #0x0]
	mov r7, r8, lsl #0x1
	ldrsh r5, [r5, r7]
	ldrb r11, [r0, #0x1]
	ldrb r2, [r0, #0x2]
	str r5, [sp, #0x4]
	mov r5, r6, asr #0x5
	ands r7, r5, #0x2
	ldr r7, [sp, #0x4]
	ldrne r10, [sp, #0x4]
	mov r7, r7, asr #0x2
	addne r7, r7, r10
	ands r10, r5, #0x1
	str r10, [sp, #0x10]
	ldrne r10, [sp, #0x4]
	ldrsh r9, [r3, #0x0]
	addne r7, r7, r10, asr #0x1
	ands r10, r5, #0x4
	str r10, [sp, #0x14]
	beq _020A98AC
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r4
	b _020A98B8
_020A98AC:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A98B8:
	ldr r7, _020A9D14 ; =cAdpcmIndexTable3
	ldrsb r5, [r7, r5]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x18]
	bmi _020A98D4
	cmp r8, #0x58
	movgt r8, r12
_020A98D4:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x0]
	ldrb r8, [r3, #0x2]
	mov r5, r6, asr #0x2
	ands r7, r5, #0x2
	ldr r7, _020A9D10 ; =cAdpcmStepSizeTable
	mov r10, r8, lsl #0x1
	ldrsh r7, [r7, r10]
	ldrsh r9, [r3, #0x0]
	str r7, [sp, #0x8]
	ldrne r10, [sp, #0x8]
	mov r7, r7, asr #0x2
	addne r7, r7, r10
	ands r10, r5, #0x1
	str r10, [sp, #0x1c]
	ldrne r10, [sp, #0x8]
	addne r7, r7, r10, asr #0x1
	ands r10, r5, #0x4
	str r10, [sp, #0x20]
	beq _020A9948
	sub r9, r9, r7
	mov r7, #0x8000
	rsb r7, r7, #0x0
	cmp r9, r7
	movlt r9, r4
	b _020A9954
_020A9948:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A9954:
	and r7, r5, #0x7
	ldr r5, _020A9D14 ; =cAdpcmIndexTable3
	ldrsb r5, [r5, r7]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x24]
	bmi _020A9974
	cmp r8, #0x58
	movgt r8, r12
_020A9974:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	mov r6, r6, lsl #0x1
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x2]
	and r6, r6, #0x7
	orr r6, r6, r11, asr #0x7
	ldrb r8, [r3, #0x2]
	ands r5, r6, #0x2
	ldr r5, _020A9D10 ; =cAdpcmStepSizeTable
	mov r7, r8, lsl #0x1
	ldrsh r10, [r5, r7]
	ldrsh r9, [r3, #0x0]
	mov r7, r10, asr #0x2
	addne r7, r7, r10
	ands r5, r6, #0x1
	str r5, [sp, #0x28]
	addne r7, r7, r10, asr #0x1
	ands r5, r6, #0x4
	beq _020A99E0
	mov r5, #0x8000
	sub r9, r9, r7
	rsb r5, r5, #0x0
	cmp r9, r5
	movlt r9, r4
	b _020A99EC
_020A99E0:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A99EC:
	ldr r5, _020A9D14 ; =cAdpcmIndexTable3
	ldrsb r5, [r5, r6]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x2c]
	bmi _020A9A08
	cmp r8, #0x58
	movgt r8, r12
_020A9A08:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x4]
	ldrb r8, [r3, #0x2]
	mov r6, r11, asr #0x4
	ands r5, r6, #0x2
	ldr r5, _020A9D10 ; =cAdpcmStepSizeTable
	mov r7, r8, lsl #0x1
	ldrsh r10, [r5, r7]
	ldrsh r9, [r3, #0x0]
	mov r7, r10, asr #0x2
	addne r7, r7, r10
	ands r5, r6, #0x1
	str r5, [sp, #0x30]
	addne r7, r7, r10, asr #0x1
	ands r5, r6, #0x4
	beq _020A9A6C
	mov r5, #0x8000
	sub r9, r9, r7
	rsb r5, r5, #0x0
	cmp r9, r5
	movlt r9, r4
	b _020A9A78
_020A9A6C:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A9A78:
	ldr r5, _020A9D14 ; =cAdpcmIndexTable3
	and r6, r6, #0x7
	ldrsb r5, [r5, r6]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x34]
	bmi _020A9A98
	cmp r8, #0x58
	movgt r8, r12
_020A9A98:
	mov r5, r9, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r5, [r1, #0x6]
	ldrb r8, [r3, #0x2]
	mov r6, r11, asr #0x1
	ands r5, r6, #0x2
	ldr r5, _020A9D10 ; =cAdpcmStepSizeTable
	mov r7, r8, lsl #0x1
	ldrsh r10, [r5, r7]
	ldrsh r9, [r3, #0x0]
	mov r7, r10, asr #0x2
	addne r7, r7, r10
	ands r5, r6, #0x1
	str r5, [sp, #0x38]
	addne r7, r7, r10, asr #0x1
	ands r5, r6, #0x4
	beq _020A9AFC
	mov r5, #0x8000
	sub r9, r9, r7
	rsb r5, r5, #0x0
	cmp r9, r5
	movlt r9, r4
	b _020A9B08
_020A9AFC:
	add r9, r9, r7
	cmp r9, lr
	movgt r9, lr
_020A9B08:
	ldr r5, _020A9D14 ; =cAdpcmIndexTable3
	and r6, r6, #0x7
	ldrsb r5, [r5, r6]
	adds r8, r8, r5
	ldrmi r8, [sp, #0x3c]
	bmi _020A9B28
	cmp r8, #0x58
	movgt r8, r12
_020A9B28:
	mov r5, r9, lsl #0x10
	mov r6, r5, asr #0x10
	mov r5, r11, lsl #0x2
	and r5, r5, #0x7
	strh r6, [r3, #0x0]
	strb r8, [r3, #0x2]
	strh r6, [r1, #0x8]
	orr r5, r5, r2, asr #0x6
	ands r6, r5, #0x2
	ldrb r6, [r3, #0x2]
	ldr r8, _020A9D10 ; =cAdpcmStepSizeTable
	ldrsh r7, [r3, #0x0]
	mov r9, r6, lsl #0x1
	ldrsh r10, [r8, r9]
	mov r9, r10, asr #0x2
	addne r9, r9, r10
	ands r8, r5, #0x1
	addne r9, r9, r10, asr #0x1
	ands r8, r5, #0x4
	beq _020A9B90
	mov r8, #0x8000
	sub r7, r7, r9
	rsb r8, r8, #0x0
	cmp r7, r8
	movlt r7, r4
	b _020A9B9C
_020A9B90:
	add r7, r7, r9
	cmp r7, lr
	movgt r7, lr
_020A9B9C:
	ldr r8, _020A9D14 ; =cAdpcmIndexTable3
	ldrsb r5, [r8, r5]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x40]
	bmi _020A9BB8
	cmp r6, #0x58
	movgt r6, r12
_020A9BB8:
	mov r5, r7, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r6, [r3, #0x2]
	strh r5, [r1, #0xa]
	ldrb r6, [r3, #0x2]
	mov r5, r2, asr #0x3
	ands r8, r5, #0x2
	ldr r8, _020A9D10 ; =cAdpcmStepSizeTable
	mov r9, r6, lsl #0x1
	ldrsh r10, [r8, r9]
	ldrsh r7, [r3, #0x0]
	mov r9, r10, asr #0x2
	addne r9, r9, r10
	ands r8, r5, #0x1
	addne r9, r9, r10, asr #0x1
	ands r8, r5, #0x4
	beq _020A9C18
	mov r8, #0x8000
	sub r7, r7, r9
	rsb r8, r8, #0x0
	cmp r7, r8
	movlt r7, r4
	b _020A9C24
_020A9C18:
	add r7, r7, r9
	cmp r7, lr
	movgt r7, lr
_020A9C24:
	and r8, r5, #0x7
	ldr r5, _020A9D14 ; =cAdpcmIndexTable3
	ldrsb r5, [r5, r8]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x44]
	bmi _020A9C44
	cmp r6, #0x58
	movgt r6, r12
_020A9C44:
	mov r5, r7, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r6, [r3, #0x2]
	strh r5, [r1, #0xc]
	ands r5, r2, #0x2
	ldrb r5, [r3, #0x2]
	ldr r7, _020A9D10 ; =cAdpcmStepSizeTable
	ldrsh r6, [r3, #0x0]
	mov r8, r5, lsl #0x1
	ldrsh r9, [r7, r8]
	mov r8, r9, asr #0x2
	addne r8, r8, r9
	ands r7, r2, #0x1
	addne r8, r8, r9, asr #0x1
	ands r7, r2, #0x4
	beq _020A9CA0
	mov r7, #0x8000
	sub r6, r6, r8
	rsb r7, r7, #0x0
	cmp r6, r7
	movlt r6, r4
	b _020A9CAC
_020A9CA0:
	add r6, r6, r8
	cmp r6, lr
	movgt r6, lr
_020A9CAC:
	and r7, r2, #0x7
	ldr r2, _020A9D14 ; =cAdpcmIndexTable3
	ldrsb r2, [r2, r7]
	adds r5, r5, r2
	ldrmi r5, [sp, #0x48]
	bmi _020A9CCC
	cmp r5, #0x58
	movgt r5, r12
_020A9CCC:
	mov r2, r6, lsl #0x10
	mov r2, r2, asr #0x10
	strh r2, [r3, #0x0]
	strb r5, [r3, #0x2]
	strh r2, [r1, #0xe]
	ldr r2, [sp, #0x0]
	add r0, r0, #0x3
	add r5, r2, #0x1
	ldr r2, [sp, #0xc]
	add r1, r1, #0x10
	str r5, [sp, #0x0]
	cmp r5, r2
	blo _020A983C
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A9D08: .word 0xAAAAAAAB
_020A9D0C: .word 0x00007FFF
_020A9D10: .word cAdpcmStepSizeTable
_020A9D14: .word cAdpcmIndexTable3

	arm_func_start vct_encode_adpcm_32
vct_encode_adpcm_32: ; 0x020A9D18
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	movs r2, r2, lsr #0x1
	str r2, [sp, #0x4]
	mov r2, #0x0
	str r2, [sp, #0x0]
	addeq sp, sp, #0x1c
	ldmeqia sp!, {r4-r11,pc}
	mov r4, #0x8000
	rsb r5, r4, #0x0
	ldr fp, _020A9F04 ; =0x00007FFF
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r2, [sp, #0x14]
	str r2, [sp, #0x18]
	mov r6, #0x8
	mov r4, #0x58
_020A9D5C:
	ldrb r2, [r3, #0x2]
	ldrsh r8, [r3, #0x0]
	ldrsh r7, [r1, #0x0]
	ldr sb, _020A9F08 ; =cAdpcmStepSizeTable
	mov r12, r2, lsl #0x1
	subs r7, r7, r8
	ldrsh r12, [r9, r12]
	movmi r10, r6
	ldrpl r10, [sp, #0xc]
	rsbmi r7, r7, #0x0
	cmp r7, r12
	orrge r10, r10, #0x4
	subge r7, r7, r12
	mov lr, r12, asr #0x1
	cmp r7, lr
	orrge r10, r10, #0x2
	subge r7, r7, lr
	mov r9, r12, asr #0x2
	cmp r7, r9
	orrge r10, r10, #0x1
	ands r7, r10, #0x4
	mov r7, r12, asr #0x3
	addne r7, r7, r12
	ands r12, r10, #0x2
	addne r7, r7, lr
	ands r12, r10, #0x1
	addne r7, r7, r9
	ands r9, r10, #0x8
	rsbne r7, r7, #0x0
	add r7, r8, r7
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r7, r8
	ldr r8, _020A9F0C ; =cAdpcmIndexTable4
	movlt r7, r5
	cmp r7, r11
	ldrsb r8, [r8, r10]
	movgt r7, r11
	adds r2, r2, r8
	ldrmi r2, [sp, #0x10]
	bmi _020A9E08
	cmp r2, #0x58
	movgt r2, r4
_020A9E08:
	strh r7, [r3, #0x0]
	strb r2, [r3, #0x2]
	ldrsh r2, [r3, #0x0]
	ldrsh r8, [r1, #0x2]
	and lr, r10, #0xff
	str r2, [sp, #0x8]
	ldrb r2, [r3, #0x2]
	ldr r7, [sp, #0x8]
	add r1, r1, #0x4
	subs r7, r8, r7
	movmi r10, r6
	ldr r8, _020A9F08 ; =cAdpcmStepSizeTable
	mov r9, r2, lsl #0x1
	ldrsh r12, [r8, r9]
	ldrpl r10, [sp, #0x14]
	rsbmi r7, r7, #0x0
	cmp r7, r12
	orrge r10, r10, #0x4
	subge r7, r7, r12
	mov r9, r12, asr #0x1
	cmp r7, r9
	orrge r10, r10, #0x2
	subge r7, r7, r9
	mov r8, r12, asr #0x2
	cmp r7, r8
	orrge r10, r10, #0x1
	ands r7, r10, #0x4
	mov r7, r12, asr #0x3
	addne r7, r7, r12
	ands r12, r10, #0x2
	addne r7, r7, r9
	ands r9, r10, #0x1
	addne r7, r7, r8
	ands r8, r10, #0x8
	ldr r8, [sp, #0x8]
	rsbne r7, r7, #0x0
	add r7, r8, r7
	mov r8, #0x8000
	rsb r8, r8, #0x0
	cmp r7, r8
	ldr r8, _020A9F0C ; =cAdpcmIndexTable4
	movlt r7, r5
	cmp r7, r11
	ldrsb r8, [r8, r10]
	movgt r7, r11
	adds r2, r2, r8
	ldrmi r2, [sp, #0x18]
	bmi _020A9ED0
	cmp r2, #0x58
	movgt r2, r4
_020A9ED0:
	strh r7, [r3, #0x0]
	strb r2, [r3, #0x2]
	and r2, r10, #0xff
	orr r2, lr, r2, lsl #0x4
	strb r2, [r0], #0x1
	ldr r2, [sp, #0x0]
	add r7, r2, #0x1
	ldr r2, [sp, #0x4]
	str r7, [sp, #0x0]
	cmp r7, r2
	blo _020A9D5C
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020A9F04: .word 0x00007FFF
_020A9F08: .word cAdpcmStepSizeTable
_020A9F0C: .word cAdpcmIndexTable4

	arm_func_start vct_decode_adpcm_32
vct_decode_adpcm_32: ; 0x020A9F10
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	cmp r2, #0x0
	addls sp, sp, #0x1c
	mov r12, #0x0
	ldmlsia sp!, {r4-r11,pc}
	mov r4, #0x8000
	ldr fp, _020AA098 ; =0x00007FFF
	str r12, [sp, #0x8]
	str r12, [sp, #0x14]
	rsb r4, r4, #0x0
	mov lr, #0x58
_020A9F40:
	ldrb r5, [r0, #0x0]
	ldrb r6, [r3, #0x2]
	ldrsh r7, [r3, #0x0]
	and r9, r5, #0xf
	ldr r5, _020AA09C ; =cAdpcmStepSizeTable
	mov r8, r6, lsl #0x1
	ldrsh r8, [r5, r8]
	ands r5, r9, #0x4
	mov r5, r8, asr #0x3
	addne r5, r5, r8
	ands r10, r9, #0x2
	str r10, [sp, #0x0]
	addne r5, r5, r8, asr #0x1
	ands r10, r9, #0x1
	addne r5, r5, r8, asr #0x2
	str r10, [sp, #0x4]
	ands r8, r9, #0x8
	beq _020A9FA0
	sub r7, r7, r5
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r7, r5
	movlt r7, r4
	b _020A9FAC
_020A9FA0:
	add r7, r7, r5
	cmp r7, r11
	movgt r7, r11
_020A9FAC:
	ldr r5, _020AA0A0 ; =cAdpcmIndexTable4
	ldrsb r5, [r5, r9]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x8]
	bmi _020A9FC8
	cmp r6, #0x58
	movgt r6, lr
_020A9FC8:
	mov r5, r7, lsl #0x10
	mov r5, r5, asr #0x10
	strh r5, [r3, #0x0]
	strb r6, [r3, #0x2]
	strh r5, [r1, #0x0]
	ldrb r5, [r0, #0x0]
	ldrb r6, [r3, #0x2]
	ldrsh r7, [r3, #0x0]
	mov r5, r5, asr #0x4
	and r9, r5, #0xf
	ldr r5, _020AA09C ; =cAdpcmStepSizeTable
	mov r8, r6, lsl #0x1
	ldrsh r8, [r5, r8]
	ands r5, r9, #0x4
	mov r5, r8, asr #0x3
	addne r5, r5, r8
	ands r10, r9, #0x2
	str r10, [sp, #0xc]
	addne r5, r5, r8, asr #0x1
	ands r10, r9, #0x1
	addne r5, r5, r8, asr #0x2
	str r10, [sp, #0x10]
	ands r8, r9, #0x8
	beq _020AA040
	sub r7, r7, r5
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r7, r5
	movlt r7, r4
	b _020AA04C
_020AA040:
	add r7, r7, r5
	cmp r7, r11
	movgt r7, r11
_020AA04C:
	ldr r5, _020AA0A0 ; =cAdpcmIndexTable4
	ldrsb r5, [r5, r9]
	adds r6, r6, r5
	ldrmi r6, [sp, #0x14]
	bmi _020AA068
	cmp r6, #0x58
	movgt r6, lr
_020AA068:
	mov r5, r7, lsl #0x10
	mov r7, r5, asr #0x10
	strh r7, [r3, #0x0]
	strb r6, [r3, #0x2]
	add r12, r12, #0x1
	strh r7, [r1, #0x2]
	cmp r12, r2
	add r1, r1, #0x4
	add r0, r0, #0x1
	blo _020A9F40
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AA098: .word 0x00007FFF
_020AA09C: .word cAdpcmStepSizeTable
_020AA0A0: .word cAdpcmIndexTable4

; libvct.a:audio.o

	arm_func_start vct_flush_send_buffer
vct_flush_send_buffer:
	stmdb sp!, {r4-r8,lr}
	ldr r0, _020AA1B4 ; =sNumStream
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4-r8,pc}
	ldr r1, _020AA1B8 ; =UNK_021CAF00
	ldr r0, [r1, #0x8c8]
	cmp r0, #0x0
	bne _020AA0FC
	bl FUN_020AA4C0
	ldr r1, _020AA1B8 ; =UNK_021CAF00
	cmp r0, #0x0
	str r0, [r1, #0x8c8]
	beq _020AA0F4
	ldr r0, _020AA1BC ; =UNK_021CA8C8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4-r8,pc}
_020AA0F4:
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
_020AA0FC:
	ldr r0, _020AA1C0 ; =__vct
	mov r5, #0x1
	ldr r0, [r0, #0x10]
	cmp r0, #0x2
	bne _020AA130
	ldr r3, [r1, #0x8d4]
	ldr r2, _020AA1C4 ; =UNK_020FF694
	mov r0, #0x3
	mla r0, r3, r0, r2
	ldr r3, [r1, #0x8d0]
	add r2, r3, #0x1
	ldrb r5, [r3, r0]
	str r2, [r1, #0x8d0]
_020AA130:
	mov r4, #0x0
	ldr r7, _020AA1B8 ; =UNK_021CAF00
	mov r8, #0x80000000
	ldr r6, _020AA1C8 ; =UNK_021CA8BC
	b _020AA1A4
_020AA144:
	ldr r1, [r7, #0x8cc]
	mov r2, r1
	clz r2, r2
	cmp r2, #0x20
	beq _020AA1AC
	mvn r0, r8, lsr r2
	and r3, r1, r0
	rsb r0, r2, #0x1f
	ldr r1, [r7, #0x8c8]
	ldr r2, [r6, #0x0]
	str r3, [r7, #0x8cc]
	and r0, r0, #0xff
	bl MOD04_021EAE90
	ldr r0, [r7, #0x8cc]
	cmp r0, #0x0
	bne _020AA1A0
	ldr r1, [r7, #0x8c0]
	mov r0, #0x0
	add r1, r1, #0x1
	str r1, [r7, #0x8c0]
	str r0, [r7, #0x8c8]
	str r0, [r7, #0x8cc]
	b _020AA1AC
_020AA1A0:
	add r4, r4, #0x1
_020AA1A4:
	cmp r4, r5
	blt _020AA144
_020AA1AC:
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AA1B4: .word sNumStream
_020AA1B8: .word UNK_021CAF00
_020AA1BC: .word UNK_021CA8C8
_020AA1C0: .word __vct
_020AA1C4: .word UNK_020FF694
_020AA1C8: .word UNK_021CA8BC

	arm_func_start vct_decode_audio_buffer
vct_decode_audio_buffer: ; 0x020AA1CC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	bl FUN_020AB154
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldrb r5, [r0, #0x11]
	mov r0, r5
	bl FUN_020AB144
	mov r6, r0
	cmp r6, #0x0
	mov r7, #0x0
	ble _020AA294
_020AA204:
	mov r0, r5
	bl FUN_020AB10C
	mov r4, r0
	ldr r3, [r4, #0xc]
	cmp r3, #0x2
	blt _020AA230
	ldr r0, [r4, #0x474]
	ldr r2, [r4, #0x14]
	add r1, r4, #0x1c
	bl vct_decode_adpcm
	b _020AA25C
_020AA230:
	cmp r3, #0x1
	bne _020AA24C
	ldr r0, [r4, #0x474]
	ldr r2, [r4, #0x14]
	add r1, r4, #0x1c
	bl FUN_020AB328
	b _020AA25C
_020AA24C:
	ldr r0, [r4, #0x474]
	ldr r2, [r4, #0x14]
	add r1, r4, #0x1c
	bl FUN_020AB2C0
_020AA25C:
	add r1, r4, #0x1c
	mov r0, r4
	str r1, [r4, #0x474]
	bl FUN_020AB088
	ldrb r1, [r4, #0x11]
	mov r0, r4
	bl FUN_020AB500
	cmp r0, #0x0
	bge _020AA288
	mov r0, r4
	bl vct_free_packet_buffer
_020AA288:
	add r7, r7, #0x1
	cmp r7, r6
	blt _020AA204
_020AA294:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start vct_handle_audio
vct_handle_audio: ; 0x020AA2A0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r4, _020AA4A8 ; =sNumStream
	mov r10, r0
	ldr r0, [r4, #0x0]
	ldr r7, [sp, #0x28]
	cmp r0, #0x0
	mov r5, #0x0
	mov r9, r1
	mov r8, r2
	mov r11, r3
	addeq sp, sp, #0x4
	moveq r0, r5
	ldmeqia sp!, {r4-r11,pc}
	ldr r1, _020AA4AC ; =sStream
	mov r2, r5
_020AA2E0:
	ldr r0, [r1, #0x38]
	cmp r10, r0
	ldreq r1, _020AA4AC ; =sStream
	moveq r0, #0x94
	mlaeq r5, r2, r0, r1
	beq _020AA308
	add r2, r2, #0x1
	cmp r2, #0x3
	add r1, r1, #0x94
	blo _020AA2E0
_020AA308:
	cmp r5, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
	ldrb r0, [r9, #0x4]
	cmp r0, #0x41
	bne _020AA344
	ldrh r2, [r9, #0x6]
	mov r0, #0x0
	mov r1, #0x1
	str r2, [r5, #0x30]
	str r0, [r5, #0x4c]
	add sp, sp, #0x4
	str r1, [r5, #0x6c]
	ldmia sp!, {r4-r11,pc}
_020AA344:
	cmp r0, #0x40
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r11,pc}
	ldrb r0, [r9, #0x5]
	and r4, r0, #0x7f
	cmp r4, #0x5
	addge sp, sp, #0x4
	str r4, [r5, #0x24]
	movge r0, #0x0
	ldmgeia sp!, {r4-r11,pc}
	ldr r1, _020AA4B0 ; =sCodecInfo+1
	ldr r0, _020AA4B4 ; =sCodecInfo
	ldrb r2, [r1, r4, lsl #0x1]
	ldrb r1, [r0, r4, lsl #0x1]
	mov r0, #0x44
	mla r0, r1, r0, r2
	add r0, r0, #0xc
	cmp r8, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r11,pc}
	cmp r10, #0x0
	movne r0, #0x1
	movne r1, r0, lsl r10
	ldr r0, _020AA4B8 ; =sBitmap
	moveq r1, #0x1
	ldr r0, [r0, #0x0]
	ands r0, r0, r1
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
	bl vct_alloc_packet_buffer
	movs r6, r0
	bne _020AA40C
	ldr r0, [r5, #0x34]
	bl vct_flush_audio_queue
	ldr r0, [r5, #0x34]
	bl FUN_020AB234
	bl vct_alloc_packet_buffer
	movs r6, r0
	bne _020AA3FC
	bl FUN_020AB630
	bl FUN_020AB1E4
	bl vct_alloc_packet_buffer
	mov r6, r0
_020AA3FC:
	cmp r6, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,pc}
_020AA40C:
	ldr r0, _020AA4BC ; =0x0000045C
	sub r2, r8, #0xc
	add r0, r6, r0
	sub r1, r0, r2
	add r0, r9, #0xc
	str r1, [sp, #0x0]
	bl MI_CpuCopy8
	ldr r0, [r5, #0x34]
	sub r1, r8, #0xc
	strb r0, [r6, #0x11]
	ldr r0, [sp, #0x0]
	str r4, [r6, #0xc]
	str r0, [r6, #0x474]
	str r1, [r6, #0x14]
	str r11, [r6, #0x464]
	str r7, [r6, #0x468]
	strb r10, [r6, #0x10]
	ldrb r2, [r9, #0x5]
	mov r0, r5
	mov r1, r6
	and r2, r2, #0x80
	str r2, [r6, #0x45c]
	ldr r2, [r9, #0x8]
	str r2, [r6, #0x460]
	ldrh r2, [r9, #0x6]
	str r2, [r6, #0x18]
	bl vct_calc_jitter_and_skew
	cmp r0, #0x0
	bne _020AA494
	mov r0, r6
	bl vct_free_packet_buffer
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020AA494:
	mov r0, r6
	bl vct_insert_decoder
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AA4A8: .word sNumStream
_020AA4AC: .word sStream
_020AA4B0: .word sCodecInfo+1
_020AA4B4: .word sCodecInfo
_020AA4B8: .word sBitmap
_020AA4BC: .word 0x0000045C

	arm_func_start FUN_020AA4C0
FUN_020AA4C0: ; 0x020AA4C0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r0, _020AA728 ; =UNK_021CAF00
	ldr r1, _020AA72C ; =UNK_021CA8CC
	ldr r3, [r0, #0x8c4]
	ldr r2, [r0, #0x8c0]
	ldr r5, [r1, #0x0]
	sub r1, r3, r2
	cmp r1, #0x1
	subhi r1, r3, #0x1
	strhi r1, [r0, #0x8c0]
	movhi r1, #0x1
	cmp r1, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	ldr r0, _020AA728 ; =UNK_021CAF00
	ldr r0, [r0, #0x8c0]
	ands r0, r0, #0x1
	movne r1, #0x0
	moveq r1, #0x460
	ldr r0, _020AA728 ; =UNK_021CAF00
	cmp r5, #0x2
	add r8, r0, r1
	ldr r1, _020AA730 ; =UNK_021CA8D4
	add r7, r8, #0xc
	addge r7, r7, #0x4
	ldr r1, [r1, #0x0]
	mov r0, r7
	bl FUN_020AD500
	ldr r2, _020AA734 ; =0x040002B0
	mov r3, #0x0
	ldr r1, _020AA738 ; =0x040002B8
	mov r6, r0
	strh r3, [r2, #0x0]
	str r6, [r1, #0x0]
_020AA550:
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x8000
	bne _020AA550
	ldr r0, _020AA73C ; =UNK_021CA8C8
	ldr r1, _020AA740 ; =0x040002B4
	ldr r0, [r0, #0x0]
	ldr r4, [r1, #0x0]
	cmp r0, #0x0
	beq _020AA588
	ldr r1, _020AA730 ; =UNK_021CA8D4
	mov r0, r7
	ldr r1, [r1, #0x0]
	mov r2, r4
	bl FUN_020AD1CC
_020AA588:
	ldr r0, _020AA744 ; =UNK_0210646C
	strb r5, [r8, #0x5]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020AA5FC
	mov r0, r6
	mov r1, r4
	mov r2, #0x0
	bl FUN_020ACF38
	ldr r1, _020AA748 ; =UNK_021CA8D8
	cmp r0, #0x0
	str r0, [r1, #0x0]
	beq _020AA5D4
	cmp r0, #0x1
	beq _020AA5F0
	cmp r0, #0x3
	moveq r0, #0x41
	streqb r0, [r8, #0x4]
	b _020AA5FC
_020AA5D4:
	ldr r1, _020AA728 ; =UNK_021CAF00
	add sp, sp, #0x8
	ldr r2, [r1, #0x8c0]
	mov r0, #0x0
	add r2, r2, #0x1
	str r2, [r1, #0x8c0]
	ldmia sp!, {r4-r8,pc}
_020AA5F0:
	ldrb r0, [r8, #0x5]
	orr r0, r0, #0x80
	strb r0, [r8, #0x5]
_020AA5FC:
	ldr r0, _020AA744 ; =UNK_0210646C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020AA62C
	ldr r0, _020AA74C ; =UNK_021CA8B8
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldrneb r2, [r8, #0x5]
	movne r1, #0x0
	orrne r2, r2, #0x80
	strneb r2, [r8, #0x5]
	strne r1, [r0, #0x0]
_020AA62C:
	ldr r0, _020AA750 ; =UNK_021CA8C4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldrneb r2, [r8, #0x5]
	movne r1, #0x0
	orrne r2, r2, #0x80
	strneb r2, [r8, #0x5]
	strne r1, [r0, #0x0]
	cmp r5, #0x2
	blt _020AA690
	ldrb r0, [r8, #0x5]
	ldr r3, _020AA754 ; =UNK_021CA8C0
	ands r0, r0, #0x80
	ldrne r0, _020AA754 ; =UNK_021CA8C0
	movne r1, #0x0
	strneh r1, [r0, #0x0]
	strneb r1, [r0, #0x2]
	ldr r0, _020AA730 ; =UNK_021CA8D4
	str r5, [sp, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, r7
	sub r0, r7, #0x4
	mov r2, r2, lsr #0x1
	bl vct_encode_adpcm
	b _020AA6D4
_020AA690:
	cmp r5, #0x1
	bne _020AA6B4
	ldr r1, _020AA730 ; =UNK_021CA8D4
	mov r0, r7
	ldr r2, [r1, #0x0]
	mov r1, r7
	mov r2, r2, lsr #0x1
	bl FUN_020AB37C
	b _020AA6D4
_020AA6B4:
	cmp r5, #0x0
	bne _020AA6D4
	ldr r1, _020AA730 ; =UNK_021CA8D4
	mov r0, r7
	ldr r2, [r1, #0x0]
	mov r1, r7
	mov r2, r2, lsr #0x1
	bl FUN_020AB2FC
_020AA6D4:
	ldr r0, _020AA758 ; =__vct
	ldr r1, _020AA75C ; =sBitmap
	ldrb r0, [r0, #0x0]
	mov r2, #0x1
	ldr r3, [r1, #0x0]
	mvn r0, r2, lsl r0
	ldr r1, _020AA728 ; =UNK_021CAF00
	and r0, r3, r0
	str r3, [r1, #0x8cc]
	str r0, [r1, #0x8cc]
	bl MATH_CountPopulation
	sub r0, r0, #0x1
	ldr r1, _020AA728 ; =UNK_021CAF00
	cmp r0, #0x7
	str r0, [r1, #0x8d4]
	movgt r0, #0x0
	movle r2, #0x0
	movle r0, r8
	strle r2, [r1, #0x8d0]
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AA728: .word UNK_021CAF00
_020AA72C: .word UNK_021CA8CC
_020AA730: .word UNK_021CA8D4
_020AA734: .word 0x040002B0
_020AA738: .word 0x040002B8
_020AA73C: .word UNK_021CA8C8
_020AA740: .word 0x040002B4
_020AA744: .word UNK_0210646C
_020AA748: .word UNK_021CA8D8
_020AA74C: .word UNK_021CA8B8
_020AA750: .word UNK_021CA8C4
_020AA754: .word UNK_021CA8C0
_020AA758: .word __vct
_020AA75C: .word sBitmap

	arm_func_start FUN_020AA760
FUN_020AA760: ; 0x020AA760
	ldr r1, _020AA76C ; =UNK_021CA8C8
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020AA76C: .word UNK_021CA8C8

	arm_func_start FUN_020AA770
FUN_020AA770: ; 0x020AA770
	stmdb sp!, {r4,lr}
	ldr r1, _020AA798 ; =UNK_0210646C
	mov r4, r0
	str r4, [r1, #0x0]
	bl FUN_020AD170
	cmp r4, #0x0
	ldreq r0, _020AA79C ; =UNK_021CA8B8
	moveq r1, #0x1
	streq r1, [r0, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_020AA798: .word UNK_0210646C
_020AA79C: .word UNK_021CA8B8

	arm_func_start FUN_020AA7A0
FUN_020AA7A0: ; 0x020AA7A0
	cmp r0, #0x5
	movge r0, #0x0
	bxge lr
	ldr r1, _020AA80C ; =__vct
	ldr r1, [r1, #0x10]
	cmp r1, #0x1
	beq _020AA7C8
	cmp r0, #0x1
	movls r0, #0x0
	bxls lr
_020AA7C8:
	ldr r2, _020AA810 ; =sCodecInfo+1
	ldr r1, _020AA814 ; =sCodecInfo
	ldrb r12, [r2, r0, lsl #0x1]
	ldrb r3, [r1, r0, lsl #0x1]
	mov r1, #0x44
	ldr r2, _020AA818 ; =UNK_021CA8CC
	mla r12, r3, r1, r12
	str r0, [r2, #0x0]
	ldr r1, _020AA81C ; =UNK_021CA8BC
	add r3, r12, #0xc
	ldr r0, _020AA820 ; =UNK_021CA8C0
	mov r2, #0x0
	str r3, [r1, #0x0]
	strh r2, [r0, #0x0]
	strb r2, [r0, #0x2]
	mov r0, #0x1
	bx lr
	.balign 4
_020AA80C: .word __vct
_020AA810: .word sCodecInfo+1
_020AA814: .word sCodecInfo
_020AA818: .word UNK_021CA8CC
_020AA81C: .word UNK_021CA8BC
_020AA820: .word UNK_021CA8C0

	arm_func_start FUN_020AA824
FUN_020AA824: ; 0x020AA824
	stmdb sp!, {r4-r10,lr}
	movs r5, r2
	mov r7, r0
	movne r0, #0x0
	strne r0, [r5, #0x0]
	ldr r0, _020AA958 ; =UNK_021CA8D4
	mov r6, r1
	ldr r0, [r0, #0x0]
	mov r4, #0x0
	cmp r6, r0
	bne _020AA920
	ldr r8, _020AA95C ; =sNumStream
	ldr r0, [r8, #0x0]
	cmp r0, #0x0
	beq _020AA920
	mov r9, r4
	cmp r0, #0x0
	bls _020AA89C
_020AA86C:
	mov r0, r7
	mov r1, r6
	mov r2, r9
	mov r3, r5
	bl FUN_020AA968
	cmp r0, #0x1
	moveq r4, #0x1
	beq _020AA89C
	ldr r0, [r8, #0x0]
	add r9, r9, #0x1
	cmp r9, r0
	blo _020AA86C
_020AA89C:
	cmp r4, #0x0
	beq _020AA90C
	ldr r8, _020AA95C ; =sNumStream
	add r10, r9, #0x1
	ldr r0, [r8, #0x0]
	cmp r10, r0
	moveq r4, #0x1
	beq _020AA934
	cmp r10, r0
	bhs _020AA934
	ldr sb, _020AA960 ; =UNK_021CAAA4
_020AA8C8:
	mov r0, r9
	mov r1, r6
	mov r2, r10
	mov r3, r5
	bl FUN_020AA968
	cmp r0, #0x1
	bne _020AA8F8
	mov r0, r7
	mov r1, r9
	mov r2, r7
	mov r3, r6
	bl vct_mix_audio
_020AA8F8:
	ldr r0, [r8, #0x0]
	add r10, r10, #0x1
	cmp r10, r0
	blo _020AA8C8
	b _020AA934
_020AA90C:
	mov r1, r7
	mov r2, r6
	mov r0, #0x0
	bl MIi_CpuClearFast
	b _020AA934
_020AA920:
	mov r1, r7
	mov r2, r6
	mov r0, #0x0
	bl MIi_CpuClearFast
	mov r4, #0x0
_020AA934:
	ldr r0, _020AA964 ; =UNK_021CA8C8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020AA950
	mov r0, r7
	mov r1, r6
	bl FUN_020AD45C
_020AA950:
	mov r0, r4
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020AA958: .word UNK_021CA8D4
_020AA95C: .word sNumStream
_020AA960: .word UNK_021CAAA4
_020AA964: .word UNK_021CA8C8

	arm_func_start FUN_020AA968
FUN_020AA968: ; 0x020AA968
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r4, _020AABD4 ; =sStream
	mov r10, r2
	mov r2, #0x94
	mla r6, r10, r2, r4
	str r0, [sp, #0x0]
	mov r0, r10
	str r1, [sp, #0x4]
	str r3, [sp, #0x8]
	mov r5, #0x1
	bl FUN_020AB434
	movs r8, r0
	beq _020AABB0
	mov r11, #0x0
_020AA9A4:
	bl OS_GetTick
	mov r4, r0
	mov r0, r10
	mov r9, r1
	bl vct_top_audio_queue
	movs r7, r0
	beq _020AAB98
	mov r0, #0x34
	adds r2, r4, r0
	ldr r8, [r7, #0x46c]
	ldr r3, [r7, #0x470]
	mov r1, #0x0
	adc r0, r9, #0x0
	cmp r3, r0
	cmpeq r8, r2
	bls _020AAA68
	ldr r0, [r7, #0x45c]
	cmp r0, #0x0
	bne _020AAA5C
	ldr r0, [r6, #0x3c]
	cmp r0, #0x0
	beq _020AAA5C
	ldr r0, [r6, #0x20]
	ldr r1, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [r6, #0x20]
	ldr r0, [r6, #0x3c]
	ldr r2, [sp, #0x4]
	ldr r0, [r0, #0x474]
	bl MIi_CpuCopyFast
	ldr r0, [r6, #0x3c]
	bl vct_free_packet_buffer
	mov r0, #0x0
	str r0, [r6, #0x3c]
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020AAA50
	ldrb r1, [r7, #0x10]
	ldr r2, [r0, #0x0]
	mov r0, #0x1
	orr r1, r2, r0, lsl r1
	ldr r0, [sp, #0x8]
	str r1, [r0, #0x0]
_020AAA50:
	add sp, sp, #0xc
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020AAA5C:
	add sp, sp, #0xc
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020AAA68:
	ldr r0, _020AABD8 ; =0x00008B4C
	adds r2, r8, r0
	adc r0, r3, r1
	cmp r9, r0
	cmpeq r4, r2
	bls _020AAAA8
	ldr r2, [r7, #0x18]
	mov r0, r6
	mov r1, r7
	str r2, [r6, #0x58]
	bl FUN_020ABC0C
	mov r8, r0
	mov r0, r10
	bl vct_top_audio_queue
	mov r5, r11
	b _020AABA8
_020AAAA8:
	ldr r1, [r6, #0x58]
	ldr r2, [r7, #0x18]
	add r0, r1, #0x1
	cmp r0, r2
	beq _020AAAE0
	cmp r1, #0x0
	beq _020AAAE0
	cmp r1, r2
	bhi _020AAAE0
	ldr r0, [r7, #0x45c]
	cmp r0, #0x0
	ldreq r0, [r6, #0x14]
	addeq r0, r0, #0x1
	streq r0, [r6, #0x14]
_020AAAE0:
	ldr r0, [r7, #0x18]
	cmp r5, #0x0
	str r0, [r6, #0x58]
	beq _020AAB24
	ldr r0, [r6, #0x70]
	cmp r0, #0x0
	beq _020AAB24
	mov r0, r6
	mov r1, r7
	bl FUN_020ABC0C
	mov r8, r0
	mov r0, r10
	bl vct_top_audio_queue
	ldr r0, [r6, #0x70]
	sub r0, r0, #0x1
	str r0, [r6, #0x70]
	b _020AABA8
_020AAB24:
	ldr r1, [r7, #0x464]
	ldr r0, [r6, #0x28]
	subs r2, r4, r1
	str r2, [r6, #0x28]
	ldr r1, [r6, #0x28]
	sub r0, r2, r0
	sub r0, r0, r1
	add r0, r1, r0, lsr #0x4
	str r0, [r6, #0x2c]
	str r0, [r6, #0x0]
	ldr r0, [r7, #0x474]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	bl MIi_CpuCopyFast
	mov r0, r6
	mov r1, r7
	bl FUN_020ABC0C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020AAB8C
	ldrb r1, [r7, #0x10]
	ldr r2, [r0, #0x0]
	mov r0, #0x1
	orr r1, r2, r0, lsl r1
	ldr r0, [sp, #0x8]
	str r1, [r0, #0x0]
_020AAB8C:
	add sp, sp, #0xc
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020AAB98:
	add sp, sp, #0xc
	str r8, [r6, #0x8]
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020AABA8:
	cmp r8, #0x0
	bne _020AA9A4
_020AABB0:
	ldr r0, [r6, #0x3c]
	cmp r0, #0x0
	beq _020AABC8
	bl vct_free_packet_buffer
	mov r0, #0x0
	str r0, [r6, #0x3c]
_020AABC8:
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AABD4: .word sStream
_020AABD8: .word 0x00008B4C

	arm_func_start FUN_020AABDC
FUN_020AABDC: ; 0x020AABDC
	stmdb sp!, {r4,lr}
	ldr r3, _020AACE0 ; =UNK_021CA8D4
	mov r2, r1
	ldr r1, [r3, #0x0]
	mov r12, #0x0
	cmp r2, r1
	movne r0, r12
	ldmneia sp!, {r4,pc}
	ldr r1, _020AACE4 ; =sNumStream
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	moveq r0, r12
	ldmeqia sp!, {r4,pc}
	mov lr, r12
	cmp r4, #0x0
	bls _020AAC48
	ldr r3, _020AACE8 ; =UNK_021CA8DC
_020AAC20:
	ldr r1, [r3, lr, lsl #0x2]
	cmp r1, #0x0
	beq _020AAC3C
	ldr r1, [r1, #0xc]
	cmp r1, #0x2
	moveq r12, #0x1
	beq _020AAC48
_020AAC3C:
	add lr, lr, #0x1
	cmp lr, r4
	blo _020AAC20
_020AAC48:
	cmp r12, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r1, _020AACEC ; =UNK_021CAF00
	ldr r4, _020AACEC ; =UNK_021CAF00
	ldr r1, [r1, #0x8c4]
	ldr r3, _020AACF0 ; =0x5F564354
	ands r1, r1, #0x1
	movne r12, #0x0
	moveq r12, #0x460
	str r3, [r4, r12]
	ldr r1, _020AACF4 ; =UNK_021CA8CC
	add r4, r4, r12
	ldr r1, [r1, #0x0]
	cmp r1, #0x2
	blt _020AAC94
	add r1, r4, #0x10
	bl MIi_CpuCopyFast
	b _020AAC9C
_020AAC94:
	add r1, r4, #0xc
	bl MIi_CpuCopyFast
_020AAC9C:
	mov r1, #0x40
	ldr r0, _020AACF8 ; =UNK_021CA8B0
	strb r1, [r4, #0x4]
	ldrh r2, [r0, #0x0]
	add r1, r2, #0x1
	strh r1, [r0, #0x0]
	strh r2, [r4, #0x6]
	bl OS_GetTick
	mov r0, r0, lsr #0x6
	orr r0, r0, r1, lsl #0x1a
	ldr r1, _020AACEC ; =UNK_021CAF00
	str r0, [r4, #0x8]
	ldr r2, [r1, #0x8c4]
	mov r0, #0x1
	add r2, r2, #0x1
	str r2, [r1, #0x8c4]
	ldmia sp!, {r4,pc}
	.balign 4
_020AACE0: .word UNK_021CA8D4
_020AACE4: .word sNumStream
_020AACE8: .word UNK_021CA8DC
_020AACEC: .word UNK_021CAF00
_020AACF0: .word 0x5F564354
_020AACF4: .word UNK_021CA8CC
_020AACF8: .word UNK_021CA8B0

	arm_func_start FUN_020AACFC
FUN_020AACFC: ; 0x020AACFC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, #0x0
	ldr ip, _020AADB8 ; =UNK_021CA8DC
_020AAD10:
	ldr r0, [r12, r4, lsl #0x2]
	mov lr, r4, lsl #0x2
	cmp r0, r5
	bne _020AAD74
	ldr r1, _020AADBC ; =sStream
	mov r0, #0x94
	mla r0, r4, r0, r1
	ldr r1, _020AADC0 ; =sNumStream
	mov r3, #0x0
	ldr r2, [r1, #0x0]
	str r3, [r12, lr]
	sub r2, r2, #0x1
	str r2, [r1, #0x0]
	bl FUN_020ABC40
	mov r0, r4
	bl vct_flush_audio_queue
	mov r0, r4
	bl FUN_020AB234
	ldr r0, _020AADC4 ; =sBitmap
	ldr r1, [r5, #0x8]
	ldr r2, [r0, #0x0]
	mvn r1, r1
	and r1, r2, r1
	str r1, [r0, #0x0]
	b _020AAD80
_020AAD74:
	add r4, r4, #0x1
	cmp r4, #0x3
	blo _020AAD10
_020AAD80:
	ldr r0, _020AADC0 ; =sNumStream
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
	ldr r0, _020AADC8 ; =UNK_021CA8C4
	mov r1, #0x1
	str r1, [r0, #0x0]
	bl FUN_020AD170
	ldr r0, _020AADC4 ; =sBitmap
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AADB8: .word UNK_021CA8DC
_020AADBC: .word sStream
_020AADC0: .word sNumStream
_020AADC4: .word sBitmap
_020AADC8: .word UNK_021CA8C4

	arm_func_start FUN_020AADCC
FUN_020AADCC: ; 0x020AADCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	ldr r0, _020AAF24 ; =sNumStream
	ldr r0, [r0, #0x0]
	cmp r0, #0x3
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	ldr r0, [r5, #0xc]
	cmp r0, #0x2
	beq _020AAE18
	cmp r0, #0x3
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r5,pc}
_020AAE18:
	ldr r1, _020AAF28 ; =UNK_021CA8DC
	mov r2, #0x0
_020AAE20:
	ldr r0, [r1, r2, lsl #0x2]
	cmp r0, r5
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,pc}
	add r2, r2, #0x1
	cmp r2, #0x3
	blo _020AAE20
	ldr r1, _020AAF28 ; =UNK_021CA8DC
	mov r4, #0x0
_020AAE48:
	ldr r0, [r1, r4, lsl #0x2]
	mov r2, r4, lsl #0x2
	cmp r0, #0x0
	streq r5, [r1, r2]
	beq _020AAE68
	add r4, r4, #0x1
	cmp r4, #0x3
	blo _020AAE48
_020AAE68:
	ldr r0, _020AAF24 ; =sNumStream
	ldr r1, _020AAF2C ; =sBitmap
	ldr r3, [r0, #0x0]
	ldr r2, _020AAF30 ; =sStream
	add r3, r3, #0x1
	str r3, [r0, #0x0]
	mov r0, #0x94
	ldr r12, [r1, #0x0]
	ldr r3, [r5, #0x8]
	mla r0, r4, r0, r2
	orr r2, r12, r3
	str r2, [r1, #0x0]
	ldrb r2, [r5, #0x5]
	mov r1, r4
	bl FUN_020ABC6C
	mov r0, r4
	bl FUN_020AB714
	ldr r0, [r5, #0xc]
	cmp r0, #0x2
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r5,pc}
	ldr r0, _020AAF24 ; =sNumStream
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _020AAF18
	bl FUN_020AD170
	bl OS_GetTickLo
	ldr r4, _020AAF34 ; =UNK_021CA8B0
	ldr r3, _020AAF38 ; =UNK_021CA8C0
	mov r12, #0x0
	ldr r1, _020AAF3C ; =UNK_021CAF00
	ldr r2, _020AAF40 ; =UNK_021CA8C4
	mov r5, #0x1
	strh r0, [r4, #0x0]
	strh r12, [r3, #0x0]
	strb r12, [r3, #0x2]
	str r5, [r2, #0x0]
	str r12, [r1, #0x8c0]
	str r12, [r1, #0x8c4]
	str r12, [r1, #0x8cc]
	str r12, [r1, #0x8c8]
	str r12, [r1, #0x8d0]
	str r12, [r1, #0x8d4]
_020AAF18:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AAF24: .word sNumStream
_020AAF28: .word UNK_021CA8DC
_020AAF2C: .word sBitmap
_020AAF30: .word sStream
_020AAF34: .word UNK_021CA8B0
_020AAF38: .word UNK_021CA8C0
_020AAF3C: .word UNK_021CAF00
_020AAF40: .word UNK_021CA8C4

	arm_func_start vct_finish_audio
vct_finish_audio: ; 0x020AAF44
	ldr r0, _020AAF54 ; =sNumStream
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020AAF54: .word sNumStream

	arm_func_start FUN_020AAF58
FUN_020AAF58:
	stmdb sp!, {r4-r8,lr}
	bl OS_GetTickLo
	ldr r1, _020AB054 ; =__vct
	ldr ip, _020AB058 ; =UNK_021CA8B0
	ldr r4, [r1, #0x10]
	strh r0, [r12, #0x0]
	cmp r4, #0x1
	ldreq r0, _020AB05C ; =UNK_021CA8CC
	mov r5, #0x0
	ldr r1, _020AB060 ; =sBitmap
	streq r5, [r0, #0x0]
	str r5, [r1, #0x0]
	ldr r2, _020AB064 ; =sNumStream
	ldrne r0, _020AB05C ; =UNK_021CA8CC
	movne r1, #0x4
	strne r1, [r0, #0x0]
	str r5, [r2, #0x0]
	ldr r0, _020AB05C ; =UNK_021CA8CC
	ldr r3, _020AB068 ; =UNK_0210646C
	ldr r2, [r0, #0x0]
	mov r6, #0x1
	ldr r1, _020AB06C ; =sCodecInfo+1
	str r6, [r3, #0x0]
	ldr r0, _020AB070 ; =sCodecInfo
	ldrb r3, [r1, r2, lsl #0x1]
	ldrb r1, [r0, r2, lsl #0x1]
	mov r0, #0x44
	ldr r2, _020AB074 ; =UNK_021CA8D4
	mla r0, r1, r0, r3
	add r4, r0, #0xc
	ldr r1, _020AB078 ; =UNK_021CA8BC
	mov r5, #0x440
	ldr r0, _020AB07C ; =UNK_021CAF00
	mov r3, #0x0
	str r5, [r2, #0x0]
	str r4, [r1, #0x0]
	str r3, [r0, #0x8c0]
	str r3, [r0, #0x8c4]
	str r3, [r0, #0x8cc]
	str r3, [r0, #0x8c8]
	str r3, [r0, #0x8d0]
	str r3, [r0, #0x8d4]
	bl FUN_020ACF10
	mov r8, #0x0
	ldr r7, _020AB080 ; =sStream
	ldr r5, _020AB084 ; =UNK_021CA8DC
	mov r6, r8
	mvn r4, #0x0
_020AB018:
	mov r0, r8
	str r6, [r5, r8, lsl #0x2]
	bl FUN_020AB714
	mov r0, r7
	mov r1, r8
	mov r2, r4
	bl FUN_020ABC6C
	add r8, r8, #0x1
	cmp r8, #0x3
	add r7, r7, #0x94
	blo _020AB018
	bl FUN_020AB284
	bl FUN_020AD474
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020AB054: .word __vct
_020AB058: .word UNK_021CA8B0
_020AB05C: .word UNK_021CA8CC
_020AB060: .word sBitmap
_020AB064: .word sNumStream
_020AB068: .word UNK_0210646C
_020AB06C: .word sCodecInfo+1
_020AB070: .word sCodecInfo
_020AB074: .word UNK_021CA8D4
_020AB078: .word UNK_021CA8BC
_020AB07C: .word UNK_021CAF00
_020AB080: .word sStream
_020AB084: .word UNK_021CA8DC

	arm_func_start FUN_020AB088
FUN_020AB088: ; 0x020AB088
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	ldrne r1, [r0, #0x8]
	strne r1, [r2, #0x8]
	bne _020AB0B4
	ldr r2, [r0, #0x8]
	ldr r1, _020AB100 ; =UNK_021CB7D8
	cmp r2, #0x0
	str r2, [r1, #0x0]
	movne r1, #0x0
	strne r1, [r2, #0x4]
_020AB0B4:
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	ldrne r1, [r0, #0x4]
	strne r1, [r2, #0x4]
	bne _020AB0E0
	ldr r2, [r0, #0x4]
	ldr r1, _020AB104 ; =UNK_021CB7DC
	cmp r2, #0x0
	str r2, [r1, #0x0]
	movne r1, #0x0
	strne r1, [r2, #0x8]
_020AB0E0:
	ldrb r2, [r0, #0x11]
	ldr r3, _020AB108 ; =UNK_021CB7E0
	ldr r1, [r3, r2, lsl #0x2]
	sub r1, r1, #0x1
	str r1, [r3, r2, lsl #0x2]
	ldrb r0, [r0, #0x11]
	ldr r0, [r3, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB100: .word UNK_021CB7D8
_020AB104: .word UNK_021CB7DC
_020AB108: .word UNK_021CB7E0

	arm_func_start FUN_020AB10C
FUN_020AB10C: ; 0x020AB10C
	ldr r1, _020AB140 ; =UNK_021CB7D8
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020AB138
_020AB11C:
	ldrb r1, [r2, #0x11]
	cmp r1, r0
	moveq r0, r2
	bxeq lr
	ldr r2, [r2, #0x8]
	cmp r2, #0x0
	bne _020AB11C
_020AB138:
	mov r0, #0x0
	bx lr
	.balign 4
_020AB140: .word UNK_021CB7D8

	arm_func_start FUN_020AB144
FUN_020AB144: ; 0x020AB144
	ldr r1, _020AB150 ; =UNK_021CB7E0
	ldr r0, [r1, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB150: .word UNK_021CB7E0

	arm_func_start FUN_020AB154
FUN_020AB154:
	ldr r0, _020AB160 ; =UNK_021CB7D8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020AB160: .word UNK_021CB7D8

	arm_func_start vct_insert_decoder
vct_insert_decoder: ; 0x020AB164
	ldr r2, _020AB1D8 ; =UNK_021CB7D8
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020AB198
	str r0, [r2, #0x0]
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldr r3, [r2, #0x0]
	ldr r1, _020AB1DC ; =UNK_021CB7DC
	str r12, [r3, #0x8]
	ldr r2, [r2, #0x0]
	str r2, [r1, #0x0]
	b _020AB1B8
_020AB198:
	ldr r1, _020AB1DC ; =UNK_021CB7DC
	mov r2, #0x0
	ldr r3, [r1, #0x0]
	str r3, [r0, #0x4]
	str r2, [r0, #0x8]
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x8]
	str r0, [r1, #0x0]
_020AB1B8:
	ldrb r2, [r0, #0x11]
	ldr r3, _020AB1E0 ; =UNK_021CB7E0
	ldr r1, [r3, r2, lsl #0x2]
	add r1, r1, #0x1
	str r1, [r3, r2, lsl #0x2]
	ldrb r0, [r0, #0x11]
	ldr r0, [r3, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB1D8: .word UNK_021CB7D8
_020AB1DC: .word UNK_021CB7DC
_020AB1E0: .word UNK_021CB7E0

	arm_func_start FUN_020AB1E4
FUN_020AB1E4: ; 0x020AB1E4
	stmdb sp!, {r4,lr}
	ldr r0, _020AB22C ; =UNK_021CB7D8
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	beq _020AB20C
_020AB1F8:
	mov r0, r4
	ldr r4, [r4, #0x8]
	bl vct_free_packet_buffer
	cmp r4, #0x0
	bne _020AB1F8
_020AB20C:
	mov r2, #0x0
	ldr r0, _020AB230 ; =UNK_021CB7E0
	mov r1, r2
_020AB218:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020AB218
	ldmia sp!, {r4,pc}
	.balign 4
_020AB22C: .word UNK_021CB7D8
_020AB230: .word UNK_021CB7E0

	arm_func_start FUN_020AB234
FUN_020AB234: ; 0x020AB234
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_020AB10C
	movs r4, r0
	beq _020AB26C
_020AB24C:
	mov r0, r4
	bl FUN_020AB088
	mov r0, r4
	bl vct_free_packet_buffer
	mov r0, r5
	bl FUN_020AB10C
	movs r4, r0
	bne _020AB24C
_020AB26C:
	ldr r0, _020AB280 ; =UNK_021CB7E0
	mov r1, #0x0
	str r1, [r0, r5, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AB280: .word UNK_021CB7E0

	arm_func_start FUN_020AB284
FUN_020AB284: ; 0x020AB284
	ldr r1, _020AB2B4 ; =UNK_021CB7DC
	mov r2, #0x0
	ldr r0, _020AB2B8 ; =UNK_021CB7D8
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r0, _020AB2BC ; =UNK_021CB7E0
	mov r1, r2
_020AB2A0:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x3
	blt _020AB2A0
	bx lr
	.balign 4
_020AB2B4: .word UNK_021CB7DC
_020AB2B8: .word UNK_021CB7D8
_020AB2BC: .word UNK_021CB7E0

	arm_func_start FUN_020AB2C0
FUN_020AB2C0: ; 0x020AB2C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	addls sp, sp, #0x4
	mov lr, #0x0
	ldmlsia sp!, {pc}
_020AB2D8:
	ldrsb r12, [r0, lr]
	mov r3, lr, lsl #0x1
	add lr, lr, #0x1
	mov r12, r12, lsl #0x8
	strh r12, [r1, r3]
	cmp lr, r2
	blo _020AB2D8
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AB2FC
FUN_020AB2FC: ; 0x020AB2FC
	cmp r2, #0x0
	mov r12, #0x0
	bxls lr
_020AB308:
	mov r3, r12, lsl #0x1
	ldrsh r3, [r1, r3]
	mov r3, r3, asr #0x8
	strb r3, [r0, r12]
	add r12, r12, #0x1
	cmp r12, r2
	blo _020AB308
	bx lr

	arm_func_start FUN_020AB328
FUN_020AB328: ; 0x020AB328
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	cmp r2, #0x0
	ldmlsia sp!, {r4,pc}
_020AB338:
	ldrb r3, [r0, r4]
	mvn lr, r3
	and r3, lr, #0xf
	mov r12, r3, lsl #0x3
	and r3, lr, #0x70
	add r12, r12, #0x84
	mov r3, r3, asr #0x4
	mov r12, r12, lsl r3
	ands r3, lr, #0x80
	rsbne r12, r12, #0x84
	mov r3, r4, lsl #0x1
	subeq r12, r12, #0x84
	add r4, r4, #0x1
	strh r12, [r1, r3]
	cmp r4, r2
	blo _020AB338
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AB37C
FUN_020AB37C: ; 0x020AB37C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov r8, #0x0
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r11,pc}
	mov r12, r8
	mov lr, #0xff
	mov r4, #0x7f
	mov r3, #0x8
_020AB3A4:
	mov r5, r8, lsl #0x1
	ldrsh r5, [r1, r5]
	ldr fp, _020AB42C ; =UNK_02106470
	movs r7, r5, asr #0x2
	movmi r6, r4
	ldr r5, _020AB430 ; =0x00001FDF
	rsbmi r7, r7, #0x0
	movpl r6, lr
	cmp r7, r5
	movgt r7, r5
	mov r5, r12
	add r10, r7, #0x21
_020AB3D4:
	ldr r9, [r11], #0x4
	cmp r10, r9
	ble _020AB3F0
	add r5, r5, #0x1
	cmp r5, #0x8
	blt _020AB3D4
	mov r5, r3
_020AB3F0:
	cmp r5, #0x8
	eorge r5, r6, #0x7f
	bge _020AB414
	add r9, r7, #0x21
	add r7, r5, #0x1
	mov r7, r9, asr r7
	and r7, r7, #0xf
	orr r5, r7, r5, lsl #0x4
	eor r5, r5, r6
_020AB414:
	strb r5, [r0, r8]
	add r8, r8, #0x1
	cmp r8, r2
	blo _020AB3A4
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AB42C: .word UNK_02106470
_020AB430: .word 0x00001FDF

	arm_func_start FUN_020AB434
FUN_020AB434: ; 0x020AB434
	ldr r1, _020AB440 ; =sCount
	ldr r0, [r1, r0, lsl #0x2]
	bx lr
	.balign 4
_020AB440: .word sCount

	arm_func_start vct_pop_audio_queue
vct_pop_audio_queue: ; 0x020AB444
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r3, _020AB4AC ; =UNK_021CB7F0
	ldr r1, _020AB4B0 ; =UNK_021CB7EC
	ldr r2, [r3, r4, lsl #0x2]
	str r0, [r1, #0x0]
	cmp r2, #0x0
	mov r12, r4, lsl #0x2
	beq _020AB494
	ldr r1, _020AB4B4 ; =sCount
	ldr r2, [r2, #0x8]
	ldr r0, [r1, r12]
	sub r0, r0, #0x1
	str r0, [r1, r12]
	str r2, [r3, r12]
	ldr r1, [r3, r12]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x4]
_020AB494:
	ldr r0, _020AB4B0 ; =UNK_021CB7EC
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020AB4B4 ; =sCount
	ldr r0, [r0, r4, lsl #0x2]
	ldmia sp!, {r4,pc}
	.balign 4
_020AB4AC: .word UNK_021CB7F0
_020AB4B0: .word UNK_021CB7EC
_020AB4B4: .word sCount

	arm_func_start vct_top_audio_queue
vct_top_audio_queue: ; 0x020AB4B8
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r2, _020AB4F8 ; =UNK_021CB7F0
	ldr r1, _020AB4FC ; =UNK_021CB7EC
	ldr r2, [r2, r4, lsl #0x2]
	str r0, [r1, #0x0]
	cmp r2, #0x0
	beq _020AB4EC
	bl OS_RestoreInterrupts
	ldr r0, _020AB4F8 ; =UNK_021CB7F0
	ldr r0, [r0, r4, lsl #0x2]
	ldmia sp!, {r4,pc}
_020AB4EC:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020AB4F8: .word UNK_021CB7F0
_020AB4FC: .word UNK_021CB7EC

	arm_func_start FUN_020AB500
FUN_020AB500:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	addeq sp, sp, #0x4
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	cmp r4, #0x3
	addcs sp, sp, #0x4
	mvncs r0, #0x0
	ldmcsia sp!, {r4-r5,pc}
	bl OS_DisableInterrupts
	ldr r3, _020AB620 ; =UNK_021CB7F0
	ldr r1, _020AB624 ; =UNK_021CB7EC
	ldr r2, [r3, r4, lsl #0x2]
	str r0, [r1, #0x0]
	cmp r2, #0x0
	mov r12, r4, lsl #0x2
	bne _020AB574
	str r5, [r3, r12]
	ldr r0, [r3, r12]
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r3, r12]
	ldr r0, _020AB628 ; =UNK_021CB808
	str r2, [r1, #0x8]
	ldr r1, [r3, r12]
	str r1, [r0, r12]
	b _020AB5F4
_020AB574:
	ldr r0, _020AB628 ; =UNK_021CB808
	ldr r3, [r0, r12]
	cmp r3, #0x0
	beq _020AB5D4
	ldr r1, [r5, #0x18]
_020AB588:
	ldr r0, [r3, #0x18]
	cmp r0, r1
	bhs _020AB5C8
	str r3, [r5, #0x4]
	ldr r0, [r3, #0x8]
	ldr r1, _020AB628 ; =UNK_021CB808
	str r0, [r5, #0x8]
	str r5, [r3, #0x8]
	ldr r0, [r5, #0x8]
	mov r2, r4, lsl #0x2
	cmp r0, #0x0
	strne r5, [r0, #0x4]
	ldr r0, [r1, r4, lsl #0x2]
	cmp r3, r0
	streq r5, [r1, r2]
	b _020AB5F4
_020AB5C8:
	ldr r3, [r3, #0x4]
	cmp r3, #0x0
	bne _020AB588
_020AB5D4:
	mov r0, #0x0
	ldr r1, _020AB620 ; =UNK_021CB7F0
	str r0, [r5, #0x4]
	ldr r0, [r1, r4, lsl #0x2]
	str r0, [r5, #0x8]
	ldr r0, [r1, r4, lsl #0x2]
	str r5, [r0, #0x4]
	str r5, [r1, r4, lsl #0x2]
_020AB5F4:
	ldr r2, _020AB62C ; =sCount
	ldr r0, _020AB624 ; =UNK_021CB7EC
	ldr r1, [r2, r4, lsl #0x2]
	add r1, r1, #0x1
	str r1, [r2, r4, lsl #0x2]
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020AB62C ; =sCount
	ldr r0, [r0, r4, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AB620: .word UNK_021CB7F0
_020AB624: .word UNK_021CB7EC
_020AB628: .word UNK_021CB808
_020AB62C: .word sCount

	arm_func_start FUN_020AB630
FUN_020AB630: ; 0x020AB630
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r7, #0x0
	ldr r1, _020AB6B8 ; =UNK_021CB7EC
	mov r4, r7
	mov r9, r7
	str r0, [r1, #0x0]
	ldr r5, _020AB6BC ; =UNK_021CB7F0
	ldr r8, _020AB6C0 ; =sCount
	b _020AB69C
_020AB65C:
	ldr r0, [r5, r7, lsl #0x2]
	mov r6, r7, lsl #0x2
	cmp r0, #0x0
	beq _020AB694
_020AB66C:
	ldr r0, [r5, r6]
	ldr r1, [r0, #0x8]
	str r1, [r5, r6]
	ldr r1, [r5, r6]
	cmp r1, #0x0
	strne r4, [r1, #0x4]
	bl vct_free_packet_buffer
	ldr r0, [r5, r6]
	cmp r0, #0x0
	bne _020AB66C
_020AB694:
	str r9, [r8, r7, lsl #0x2]
	add r7, r7, #0x1
_020AB69C:
	cmp r7, #0x3
	blt _020AB65C
	ldr r0, _020AB6B8 ; =UNK_021CB7EC
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020AB6B8: .word UNK_021CB7EC
_020AB6BC: .word UNK_021CB7F0
_020AB6C0: .word sCount

	arm_func_start vct_flush_audio_queue
vct_flush_audio_queue: ; 0x020AB6C4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl vct_top_audio_queue
	movs r4, r0
	beq _020AB6FC
_020AB6DC:
	mov r0, r5
	bl vct_pop_audio_queue
	mov r0, r4
	bl vct_free_packet_buffer
	mov r0, r5
	bl vct_top_audio_queue
	movs r4, r0
	bne _020AB6DC
_020AB6FC:
	ldr r0, _020AB710 ; =sCount
	mov r1, #0x0
	str r1, [r0, r5, lsl #0x2]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AB710: .word sCount

	arm_func_start FUN_020AB714
FUN_020AB714: ; 0x020AB714
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020AB750 ; =UNK_021CB7EC
	ldr r3, _020AB754 ; =UNK_021CB808
	mov lr, #0x0
	str lr, [r3, r4, lsl #0x2]
	ldr r2, _020AB758 ; =sCount
	ldr r12, [r3, r4, lsl #0x2]
	ldr r3, _020AB75C ; =UNK_021CB7F0
	str r0, [r1, #0x0]
	str r12, [r3, r4, lsl #0x2]
	str lr, [r2, r4, lsl #0x2]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,pc}
	.balign 4
_020AB750: .word UNK_021CB7EC
_020AB754: .word UNK_021CB808
_020AB758: .word sCount
_020AB75C: .word UNK_021CB7F0

	arm_func_start vct_calc_jitter_and_skew
vct_calc_jitter_and_skew:
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r2, [r7, #0x5c]
	mov r6, r1
	cmp r2, #0x0
	mov r4, #0x0
	beq _020AB790
	ldr r1, [r6, #0x18]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl FUN_020ABBEC
	b _020AB820
_020AB790:
	ldr r2, [r6, #0x18]
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	bl FUN_020ABB1C
	cmp r0, #0x0
	ldreq r1, [r7, #0x14]
	moveq r0, r4
	addeq r1, r1, #0x1
	streq r1, [r7, #0x14]
	ldmeqia sp!, {r4-r8,pc}
	ldr r0, [r6, #0x18]
	str r0, [r7, #0x10]
	ldr r2, [r6, #0x18]
	ldr r1, [r7, #0x54]
	cmp r1, r2
	ldreq r1, [r7, #0x14]
	moveq r0, r4
	addeq r1, r1, #0x1
	streq r1, [r7, #0x14]
	ldmeqia sp!, {r4-r8,pc}
	add r0, r1, #0x1
	cmp r0, r2
	beq _020AB820
	ldr r0, [r6, #0x45c]
	cmp r0, #0x0
	bne _020AB820
	subs r0, r2, r1
	rsbmi r0, r0, #0x0
	cmp r0, #0x64
	strgt r2, [r7, #0x54]
	movgt r0, #0x0
	ldmgtia sp!, {r4-r8,pc}
	cmp r1, r2
	ldrhi r0, [r7, #0x1c]
	addhi r0, r0, #0x1
	strhi r0, [r7, #0x1c]
_020AB820:
	ldr r0, [r6, #0x18]
	str r0, [r7, #0x54]
	ldr r0, [r7, #0x4c]
	cmp r0, #0x0
	bne _020AB858
	ldr r1, [r6, #0x460]
	ldr r0, _020ABAF4 ; =0x00000464
	str r1, [r7, #0x4c]
	add r1, r6, r0
	add r0, r7, #0x44
	ldmia r1, {r2-r3}
	stmia r0, {r2-r3}
	mov r0, #0x0
	str r0, [r7, #0x6c]
_020AB858:
	ldr r3, [r6, #0x460]
	ldr r1, [r7, #0x4c]
	ldr r2, [r6, #0x464]
	ldr r0, [r7, #0x44]
	sub r1, r3, r1
	ldr r3, [r7, #0x80]
	mov r1, r1, lsl #0x6
	subs r0, r2, r0
	subs r5, r1, r0
	cmp r3, #0x0
	mov r0, #0x0
	beq _020AB894
	ldr r2, [r6, #0x45c]
	cmp r2, #0x0
	beq _020AB89C
_020AB894:
	str r5, [r7, #0x80]
	b _020AB918
_020AB89C:
	str r5, [r7, #0x80]
	subs r2, r5, r3
	ldr r8, [r7, #0x7c]
	ldr r3, _020ABAF8 ; =0x00008B18
	ldr ip, _020ABAFC ; =0x0000CC8D
	add r3, r8, r3
	mov r8, r3, lsl #0x1
	rsbmi r2, r2, #0x0
	mov r3, r8, asr #0x1f
	adds r8, r8, r12
	mov r12, r2, asr #0x1f
	adc r3, r3, #0x0
	cmp r12, r3
	cmpeq r2, r8
	bls _020AB8F4
	ldr lr, _020ABB00 ; =0x75CA82CB
	mov r3, r2, lsr #0x1f
	smull r12, r8, lr, r2
	mov r8, r8, asr #0xe
	add r8, r3, r8
	add r3, r8, #0x2
	str r3, [r7, #0x84]
_020AB8F4:
	ldr r3, [r7, #0x84]
	cmp r3, #0x0
	bgt _020AB918
	ldr r3, [r7, #0x7c]
	sub r2, r2, r3
	add r2, r3, r2, asr #0x4
	str r2, [r7, #0x7c]
	ldr r2, [r7, #0x7c]
	str r2, [r7, #0x18]
_020AB918:
	ldr r3, [r7, #0x44]
	ldr r12, [r7, #0x4]
	ldr r2, [r7, #0x48]
	adds r1, r1, r3
	adc r0, r0, r2
	adds r1, r12, r1
	str r1, [r6, #0x46c]
	adc r0, r0, #0x0
	str r0, [r6, #0x470]
	bl OS_GetTick
	ldr r12, [r6, #0x46c]
	ldr r2, _020ABAF8 ; =0x00008B18
	ldr lr, [r6, #0x470]
	adds r6, r12, r2
	adc r3, lr, #0x0
	cmp r3, r1
	mov r3, #0x0
	cmpeq r6, r0
	movcc r0, r3
	ldmccia sp!, {r4-r8,pc}
	ldr r6, _020ABB04 ; =0x0007FD88
	adds r6, r0, r6
	adc r0, r1, r3
	cmp lr, r0
	cmpeq r12, r6
	movhi r0, r3
	ldmhiia sp!, {r4-r8,pc}
	ldr r0, [r7, #0x84]
	cmp r0, #0x0
	bgt _020ABAE0
	ldr r1, [r7, #0x7c]
	mov r0, #0x3
	mul lr, r1, r0
	ldr r6, _020ABB00 ; =0x75CA82CB
	ldr r12, [r7, #0x8c]
	smull r1, r0, r6, lr
	mov r0, r0, asr #0xe
	mov r1, lr, lsr #0x1f
	cmp lr, r12
	add r0, r1, r0
	bls _020AB9EC
	ldr r1, _020ABB08 ; =0x000134DF
	add r6, r0, #0x1
	mla r12, r6, r2, r1
	str r12, [r7, #0x8c]
	mla r1, r0, r2, r1
	ldr r2, [r7, #0x8c]
	ldr r0, _020ABB0C ; =0xFFFF2F5C
	add r0, r2, r0
	str r0, [r7, #0x88]
	str r1, [r7, #0x4]
	str r3, [r7, #0x90]
	b _020ABA50
_020AB9EC:
	ldr r1, [r7, #0x88]
	cmp lr, r1
	bge _020ABA50
	ldr r1, [r7, #0x90]
	add r1, r1, #0x1
	str r1, [r7, #0x90]
	ldr r1, [r7, #0x90]
	cmp r1, #0x46
	bls _020ABA50
	ldr r1, _020ABB08 ; =0x000134DF
	add r12, r0, #0x1
	mla lr, r12, r2, r1
	ldr r6, _020ABB10 ; =0xFFFFBA74
	str lr, [r7, #0x8c]
	mla r1, r0, r2, r6
	str r1, [r7, #0x88]
	ldr r1, [r7, #0x88]
	ldr r2, _020ABB08 ; =0x000134DF
	cmp r1, #0x0
	ldr r1, _020ABAF8 ; =0x00008B18
	strlt r3, [r7, #0x88]
	mla r1, r0, r1, r2
	mov r3, #0x0
	str r1, [r7, #0x4]
	str r3, [r7, #0x90]
_020ABA50:
	ldr r1, [r7, #0x4]
	ldr r0, _020ABB14 ; =0x00068520
	cmp r1, r0
	strhi r0, [r7, #0x4]
	ldr r0, [r7, #0x6c]
	cmp r0, #0x10
	addcc r0, r0, #0x1
	strcc r0, [r7, #0x6c]
	strcc r5, [r7, #0x74]
	strcc r5, [r7, #0x78]
	blo _020ABA98
	ldr r1, [r7, #0x74]
	mov r0, #0x1f
	mla r2, r1, r0, r5
	mov r0, r2, asr #0x4
	add r0, r2, r0, lsr #0x1b
	mov r0, r0, asr #0x5
	str r0, [r7, #0x74]
_020ABA98:
	ldr r2, [r7, #0x78]
	ldr r1, [r7, #0x74]
	ldr r0, _020ABB18 ; =0x00008701
	sub r1, r2, r1
	str r1, [r7, #0xc]
	ldr r1, [r7, #0xc]
	cmp r1, r0
	mvn r0, #0x8700
	movgt r4, #0x1
	cmp r1, r0
	ldrlt r0, [r7, #0x70]
	mvnlt r4, #0x0
	addlt r0, r0, #0x1
	strlt r0, [r7, #0x70]
	cmp r4, #0x0
	movne r0, #0x0
	strne r0, [r7, #0x6c]
	strne r0, [r7, #0x4c]
_020ABAE0:
	ldr r1, [r7, #0x84]
	mov r0, #0x1
	sub r1, r1, #0x1
	str r1, [r7, #0x84]
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020ABAF4: .word 0x00000464
_020ABAF8: .word 0x00008B18
_020ABAFC: .word 0x0000CC8D
_020ABB00: .word 0x75CA82CB
_020ABB04: .word 0x0007FD88
_020ABB08: .word 0x000134DF
_020ABB0C: .word 0xFFFF2F5C
_020ABB10: .word 0xFFFFBA74
_020ABB14: .word 0x00068520
_020ABB18: .word 0x00008701

	arm_func_start FUN_020ABB1C
FUN_020ABB1C:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldrh r12, [r6, #0x68]
	mov r4, r2
	ldr r3, _020ABBE4 ; =0x00000BB8
	sub r2, r4, r12
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r5, r1
	cmp r2, r3
	bhs _020ABB60
	cmp r4, r12
	ldrcc r0, [r6, #0x60]
	addcc r0, r0, #0x10000
	strcc r0, [r6, #0x60]
	strh r4, [r6, #0x68]
	b _020ABBD0
_020ABB60:
	ldr r1, _020ABBE8 ; =0x0000FF9C
	cmp r2, r1
	bhi _020ABBAC
	ldr r1, [r6, #0x64]
	cmp r4, r1
	bne _020ABB94
	mov r1, r4
	bl FUN_020ABBEC
	sub r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r6, #0x54]
	b _020ABBD0
_020ABB94:
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r6, #0x64]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
_020ABBAC:
	ldr r2, [r6, #0x60]
	ldr r0, [r6, #0x54]
	add r2, r4, r2
	add r0, r0, r1
	cmp r2, r0
	subhi r0, r2, #0x10000
	strhi r0, [r5, #0x18]
	movhi r0, #0x1
	ldmhiia sp!, {r4-r6,pc}
_020ABBD0:
	ldr r1, [r6, #0x60]
	mov r0, #0x1
	add r1, r4, r1
	str r1, [r5, #0x18]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ABBE4: .word 0x00000BB8
_020ABBE8: .word 0x0000FF9C

	arm_func_start FUN_020ABBEC
FUN_020ABBEC: ; 0x020ABBEC
	ldr r2, _020ABC08 ; =0x00010001
	strh r1, [r0, #0x68]
	str r2, [r0, #0x64]
	mov r1, #0x0
	str r1, [r0, #0x60]
	str r1, [r0, #0x5c]
	bx lr
	.balign 4
_020ABC08: .word 0x00010001

	arm_func_start FUN_020ABC0C
FUN_020ABC0C: ; 0x020ABC0C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x3c]
	mov r4, r1
	cmp r0, #0x0
	beq _020ABC2C
	bl vct_free_packet_buffer
_020ABC2C:
	str r4, [r5, #0x3c]
	ldr r0, [r5, #0x34]
	bl vct_pop_audio_queue
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start FUN_020ABC40
FUN_020ABC40: ; 0x020ABC40
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x3c]
	cmp r0, #0x0
	beq _020ABC60
	bl vct_free_packet_buffer
	mov r0, #0x0
	str r0, [r4, #0x3c]
_020ABC60:
	mvn r0, #0x0
	str r0, [r4, #0x38]
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020ABC6C
FUN_020ABC6C: ; 0x020ABC6C
	stmdb sp!, {r4-r6,lr}
	mov r5, r1
	mov r4, r2
	mov r1, #0x0
	mov r2, #0x28
	mov r6, r0
	bl MI_CpuFill8
	ldr r0, _020ABCF4 ; =0x000134DF
	mov r1, #0x0
	str r0, [r6, #0x4]
	str r1, [r6, #0x28]
	str r1, [r6, #0x2c]
	str r5, [r6, #0x34]
	str r4, [r6, #0x38]
	str r1, [r6, #0x7c]
	str r1, [r6, #0x80]
	str r1, [r6, #0x84]
	str r1, [r6, #0x88]
	str r0, [r6, #0x8c]
	str r1, [r6, #0x90]
	str r1, [r6, #0x4c]
	str r1, [r6, #0x44]
	str r1, [r6, #0x48]
	str r1, [r6, #0x6c]
	str r1, [r6, #0x70]
	str r1, [r6, #0x50]
	str r1, [r6, #0x54]
	str r1, [r6, #0x58]
	mov r0, #0x1
	str r0, [r6, #0x5c]
	str r1, [r6, #0x3c]
	str r1, [r6, #0x40]
	str r1, [r6, #0x30]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ABCF4: .word 0x000134DF

	arm_func_start FUN_020ABCF8
FUN_020ABCF8: ; 0x020ABCF8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020ABE34 ; =__vct
	ldr r2, [r3, #0x10]
	cmp r2, #0x2
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {pc}
	ldrb r12, [r3, #0x1]
	ldrb r2, [r0, #0x8]
	cmp r12, r2
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {pc}
	ldrb r2, [r0, #0xa]
	cmp r2, #0x0
	beq _020ABD48
	cmp r2, #0x1
	beq _020ABDA4
	b _020ABE1C
_020ABD48:
	ldr r0, _020ABE38 ; =UNK_021CB824
	ldr r2, [r0, #0x2c]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x38]
	cmp r0, #0x5
	beq _020ABD74
	cmp r0, #0x2
	bne _020ABD80
_020ABD74:
	mov r0, #0x9
	str r0, [r1, #0x0]
	b _020ABD88
_020ABD80:
	mov r0, #0x5
	str r0, [r1, #0x0]
_020ABD88:
	ldr r0, _020ABE38 ; =UNK_021CB824
	mov r3, #0x0
	ldr r2, _020ABE3C ; =UNK_021CB850
	str r3, [r0, #0x2c]
	str r3, [r0, #0x38]
	str r2, [r1, #0x4]
	b _020ABE28
_020ABDA4:
	ldr r2, _020ABE38 ; =UNK_021CB824
	mov lr, #0x2
	str lr, [r2, #0x2c]
	ldrb r12, [r0, #0xb]
	ldrb r3, [r3, #0x0]
	cmp r12, r3
	bne _020ABDD8
	str lr, [r2, #0x38]
	mov r3, #0x7
	str r3, [r1, #0x0]
	ldr r3, [r0, #0xc]
	str r3, [r2, #0x34]
	b _020ABE04
_020ABDD8:
	mov r3, #0x3
	str r3, [r2, #0x38]
	mov r2, #0x6
	str r2, [r1, #0x0]
	ldrb r3, [r0, #0xb]
	cmp r3, #0x0
	movne r2, #0x1
	movne r3, r2, lsl r3
	ldr r2, _020ABE38 ; =UNK_021CB824
	moveq r3, #0x1
	str r3, [r2, #0x34]
_020ABE04:
	ldrb r3, [r0, #0xb]
	ldr r0, _020ABE38 ; =UNK_021CB824
	ldr r2, _020ABE3C ; =UNK_021CB850
	strb r3, [r0, #0x31]
	str r2, [r1, #0x4]
	b _020ABE28
_020ABE1C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020ABE28:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ABE34: .word __vct
_020ABE38: .word UNK_021CB824
_020ABE3C: .word UNK_021CB850

	arm_func_start FUN_020ABE40
FUN_020ABE40: ; 0x020ABE40
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x4]
	mov r4, r1
	cmp r0, #0xff
	bne _020ABE70
	ldrb r0, [r5, #0x6]
	cmp r0, #0x4
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
_020ABE70:
	ldrb r0, [r5, #0x8]
	bl FUN_020AC1E8
	cmp r0, #0x0
	beq _020ABEA4
	mov r1, #0x2
	str r1, [r4, #0x0]
	str r0, [r4, #0x4]
	mov r2, #0x0
	str r2, [r0, #0x0]
	bl FUN_020AC708
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,pc}
_020ABEA4:
	ldrb r1, [r5, #0x8]
	ldr r0, _020ABEC8 ; =UNK_021CB838
	bl FUN_020AC5A4
	ldr r0, _020ABEC8 ; =UNK_021CB838
	mov r1, #0x2
	bl FUN_020AC708
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020ABEC8: .word UNK_021CB838

	arm_func_start FUN_020ABECC
FUN_020ABECC: ; 0x020ABECC
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020AC070 ; =UNK_021CB824
	mov r6, r0
	ldr r0, [r2, #0x2c]
	mov r5, r1
	cmp r0, #0x2
	bne _020ABF84
	ldrb r1, [r2, #0x30]
	ldrb r0, [r6, #0x8]
	cmp r1, r0
	bne _020ABF74
	ldr r0, _020AC074 ; =UNK_021CB850
	mov r1, r6
	bl FUN_020AC350
	mov r4, r0
	mvn r0, #0x2
	cmp r4, r0
	beq _020ABF48
	mvn r0, #0x1
	cmp r4, r0
	beq _020ABF30
	mvn r0, #0x0
	cmp r4, r0
	beq _020ABF48
	b _020ABF50
_020ABF30:
	mov r0, #0xc
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r5, #0x4]
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
_020ABF48:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
_020ABF50:
	ldr r1, _020AC074 ; =UNK_021CB850
	mov r0, r6
	bl FUN_020AC4A0
	ldr r1, _020AC074 ; =UNK_021CB850
	str r0, [r5, #0x0]
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x4]
	str r4, [r0, #0xc]
	b _020AC028
_020ABF74:
	mov r0, #0x1
	bl FUN_020AC5E8
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
_020ABF84:
	ldrb r12, [r6, #0x8]
	cmp r12, #0x0
	movne r0, #0x1
	movne r1, r0, lsl r12
	ldr r0, _020AC078 ; =UNK_021CB818
	moveq r1, #0x1
	ldr r0, [r0, #0x0]
	ands r0, r0, r1
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, _020AC070 ; =UNK_021CB824
	mov r4, #0x2
	mov r3, #0x0
	ldr r0, _020AC074 ; =UNK_021CB850
	mov r1, r6
	strb r12, [r2, #0x30]
	str r4, [r2, #0x2c]
	str r3, [r2, #0x38]
	bl FUN_020AC350
	mov r4, r0
	mvn r0, #0x2
	cmp r4, r0
	beq _020ABFF8
	mvn r0, #0x1
	cmp r4, r0
	beq _020ABFF8
	mvn r0, #0x0
	cmp r4, r0
	bne _020AC008
_020ABFF8:
	ldr r1, _020AC070 ; =UNK_021CB824
	mov r0, #0x0
	str r0, [r1, #0x2c]
	ldmia sp!, {r4-r6,pc}
_020AC008:
	ldr r1, _020AC074 ; =UNK_021CB850
	mov r0, r6
	bl FUN_020AC4A0
	ldr r1, _020AC074 ; =UNK_021CB850
	str r0, [r5, #0x0]
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x4]
	str r4, [r0, #0xc]
_020AC028:
	ldr r0, [r5, #0x0]
	cmp r0, #0xa
	bne _020AC050
	mov r0, #0x1
	bl FUN_020AC5E8
	bl OS_GetTick
	ldr r2, _020AC07C ; =UNK_021CB81C
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	b _020AC068
_020AC050:
	mov r0, #0x0
	bl FUN_020AC5E8
	ldr r0, _020AC07C ; =UNK_021CB81C
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
_020AC068:
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020AC070: .word UNK_021CB824
_020AC074: .word UNK_021CB850
_020AC078: .word UNK_021CB818
_020AC07C: .word UNK_021CB81C

	arm_func_start FUN_020AC080
FUN_020AC080: ; 0x020AC080
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	ldrb r2, [r6, #0x4]
	mov r5, r1
	cmp r2, #0xff
	bne _020AC0C4
	ldrb r2, [r6, #0x6]
	cmp r2, #0x4
	bne _020AC0B4
	bl FUN_020ABCF8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
_020AC0B4:
	cmp r2, #0x3
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
_020AC0C4:
	ldrb r0, [r6, #0x8]
	bl FUN_020AC1E8
	movs r4, r0
	beq _020AC154
	mov r1, r6
	bl FUN_020AC350
	mov r7, r0
	mvn r0, #0x1
	cmp r7, r0
	beq _020AC104
	mvn r0, #0x0
	cmp r7, r0
	bne _020AC124
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC104:
	mov r0, #0xc
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	add sp, sp, #0x4
	str r4, [r5, #0x4]
	mov r0, #0x1
	ldmia sp!, {r4-r7,pc}
_020AC124:
	mov r0, r6
	mov r1, r4
	bl FUN_020AC4A0
	str r0, [r5, #0x0]
	str r4, [r5, #0x4]
	str r7, [r4, #0xc]
	ldr r0, [r5, #0x0]
	add sp, sp, #0x4
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC154:
	ldrb r0, [r6, #0x8]
	bl FUN_020AC790
	movs r7, r0
	bne _020AC188
	ldrb r1, [r6, #0x8]
	ldr r0, _020AC1E4 ; =UNK_021CB838
	bl FUN_020AC5A4
	ldr r0, _020AC1E4 ; =UNK_021CB838
	mov r1, #0x3
	bl FUN_020AC708
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC188:
	mov r1, r6
	bl FUN_020AC350
	mov r4, r0
	add r0, r4, #0x2
	cmp r0, #0x1
	bhi _020AC1B4
	mov r0, r7
	bl FUN_020ACC84
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AC1B4:
	mov r0, r6
	mov r1, r7
	bl FUN_020AC4A0
	str r0, [r5, #0x0]
	str r7, [r5, #0x4]
	str r4, [r7, #0xc]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AC1E4: .word UNK_021CB838

	arm_func_start FUN_020AC1E8
FUN_020AC1E8:
	ldr r1, _020AC25C ; =__vct
	ldr r2, _020AC260 ; =UNK_021CB824
	ldr r1, [r1, #0x10]
	ldr r3, [r2, #0x4]
	cmp r1, #0x2
	bne _020AC224
	ldr r1, [r2, #0x2c]
	cmp r1, #0x0
	beq _020AC21C
	ldrb r1, [r2, #0x30]
	cmp r1, r0
	ldreq r0, _020AC264 ; =UNK_021CB850
	bxeq lr
_020AC21C:
	mov r0, #0x0
	bx lr
_020AC224:
	cmp r3, #0x0
	beq _020AC254
_020AC22C:
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	beq _020AC248
	ldrb r1, [r3, #0x4]
	cmp r1, r0
	moveq r0, r3
	bxeq lr
_020AC248:
	ldr r3, [r3, #0x14]
	cmp r3, #0x0
	bne _020AC22C
_020AC254:
	mov r0, #0x0
	bx lr
	.balign 4
_020AC25C: .word __vct
_020AC260: .word UNK_021CB824
_020AC264: .word UNK_021CB850

	arm_func_start FUN_020AC268
FUN_020AC268:
	ldrb r2, [r1, #0x4]
	ldrb r12, [r1, #0x6]
	cmp r2, #0x0
	addeq r12, r12, #0x5
	cmp r12, #0x0
	blt _020AC288
	cmp r12, #0xb
	blt _020AC28C
_020AC288:
	mvn r12, #0x0
_020AC28C:
	cmp r12, #0x0
	mvnlt r0, #0x0
	bxlt lr
	ldr r1, _020AC2F8 ; =__vct
	ldr r1, [r1, #0x10]
	cmp r1, #0x1
	ldrne r3, [r0, #0xc]
	ldrne r2, _020AC2FC ; =UNK_020FF788
	movne r1, #0xb
	mlane r1, r3, r1, r2
	ldrnesb r2, [r12, r1]
	bne _020AC2D0
	ldr r3, [r0, #0xc]
	ldr r2, _020AC300 ; =UNK_020FF744
	mov r1, #0xb
	mla r1, r3, r1, r2
	ldrsb r2, [r12, r1]
_020AC2D0:
	mvn r1, #0x0
	cmp r2, r1
	moveq r0, #0x1
	bxeq lr
	mvn r1, #0x1
	cmp r2, r1
	moveq r0, #0x0
	strne r2, [r0, #0xc]
	movne r0, #0x1
	bx lr
	.balign 4
_020AC2F8: .word __vct
_020AC2FC: .word UNK_020FF788
_020AC300: .word UNK_020FF744

	arm_func_start FUN_020AC304
FUN_020AC304:
	ldr r1, _020AC34C ; =UNK_021CB824
	ldr r2, [r1, #0x4]
	cmp r2, #0x0
	beq _020AC344
_020AC314:
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020AC338
	ldr r1, [r2, #0xc]
	cmp r1, #0x2
	bne _020AC338
	cmp r0, r2
	movne r0, #0x0
	bxne lr
_020AC338:
	ldr r2, [r2, #0x14]
	cmp r2, #0x0
	bne _020AC314
_020AC344:
	mov r0, #0x1
	bx lr
	.balign 4
_020AC34C: .word UNK_021CB824

	arm_func_start FUN_020AC350
FUN_020AC350: ; 0x020AC350
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldrb r2, [r1, #0x4]
	ldrb r3, [r1, #0x6]
	mov r4, r0
	cmp r2, #0x0
	addeq r3, r3, #0x5
	cmp r3, #0x0
	blt _020AC37C
	cmp r3, #0xb
	blt _020AC380
_020AC37C:
	mvn r3, #0x0
_020AC380:
	cmp r3, #0x0
	addlt sp, sp, #0x4
	mvnlt r0, #0x0
	ldmltia sp!, {r4-r5,pc}
	ldr r0, _020AC44C ; =__vct
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	ldrne r2, [r4, #0xc]
	ldrne r1, _020AC450 ; =UNK_020FF700
	movne r0, #0xb
	mlane r0, r2, r0, r1
	ldrnesb r5, [r3, r0]
	bne _020AC3C8
	ldr r2, [r4, #0xc]
	ldr r1, _020AC454 ; =UNK_020FF6BC
	mov r0, #0xb
	mla r0, r2, r0, r1
	ldrsb r5, [r3, r0]
_020AC3C8:
	mvn r0, #0x2
	cmp r5, r0
	beq _020AC41C
	mvn r0, #0x1
	cmp r5, r0
	beq _020AC3F8
	mvn r0, #0x0
	cmp r5, r0
	bne _020AC440
	add sp, sp, #0x4
	mov r0, r5
	ldmia sp!, {r4-r5,pc}
_020AC3F8:
	mov r0, r4
	mov r1, #0x1
	bl FUN_020AC708
	mov r1, #0x0
	str r1, [r4, #0xc]
	add sp, sp, #0x4
	mov r0, r5
	str r1, [r4, #0x0]
	ldmia sp!, {r4-r5,pc}
_020AC41C:
	mov r0, r4
	mov r1, #0x3
	bl FUN_020AC708
	mov r1, #0x0
	str r1, [r4, #0xc]
	add sp, sp, #0x4
	mov r0, r5
	str r1, [r4, #0x0]
	ldmia sp!, {r4-r5,pc}
_020AC440:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AC44C: .word __vct
_020AC450: .word UNK_020FF700
_020AC454: .word UNK_020FF6BC

	arm_func_start FUN_020AC458
FUN_020AC458:
	ldr ip, _020AC498 ; =0x5F564354
	mov r3, #0x10
	str r12, [r1, #0x0]
	strb r3, [r1, #0x5]
	ldr r3, _020AC49C ; =__vct
	strb r2, [r1, #0x6]
	ldrb r2, [r3, #0x0]
	strb r2, [r1, #0x8]
	ldrb r2, [r0, #0x4]
	mov r0, #0x0
	strb r2, [r1, #0x9]
	strb r0, [r1, #0xa]
	ldrb r2, [r3, #0x0]
	strb r2, [r1, #0xb]
	str r0, [r1, #0xc]
	bx lr
	.balign 4
_020AC498: .word 0x5F564354
_020AC49C: .word __vct

	arm_func_start FUN_020AC4A0
FUN_020AC4A0:
	ldrb r2, [r0, #0xb]
	strb r2, [r1, #0x5]
	ldrb r2, [r0, #0x4]
	cmp r2, #0xff
	bne _020AC4E8
	ldrb r2, [r0, #0x6]
	cmp r2, #0x0
	bne _020AC4D8
	ldrb r3, [r1, #0x4]
	cmp r3, #0x0
	movne r2, #0x1
	movne r2, r2, lsl r3
	moveq r2, #0x1
	str r2, [r1, #0x8]
_020AC4D8:
	ldrb r1, [r0, #0x6]
	ldr r0, _020AC54C ; =UNK_020FF6AC
	ldrb r0, [r0, r1]
	bx lr
_020AC4E8:
	cmp r2, #0x0
	bne _020AC544
	ldrb r2, [r0, #0x6]
	cmp r2, #0x0
	bne _020AC538
	ldr r0, [r1, #0xc]
	cmp r0, #0x1
	bne _020AC528
	ldrb r2, [r1, #0x4]
	cmp r2, #0x0
	movne r0, #0x1
	movne r0, r0, lsl r2
	moveq r0, #0x1
	str r0, [r1, #0x8]
	mov r0, #0x7
	bx lr
_020AC528:
	cmp r0, #0x5
	moveq r0, #0x9
	movne r0, #0xc
	bx lr
_020AC538:
	ldr r0, _020AC550 ; =UNK_020FF6B4
	ldrb r0, [r0, r2]
	bx lr
_020AC544:
	mov r0, #0xc
	bx lr
	.balign 4
_020AC54C: .word UNK_020FF6AC
_020AC550: .word UNK_020FF6B4

	arm_func_start FUN_020AC554
FUN_020AC554:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrb r2, [r1, #0x4]
	cmp r2, #0xff
	bne _020AC57C
	ldrb r2, [r1, #0x6]
	cmp r2, #0x4
	bne _020AC57C
	bl FUN_020AC628
	b _020AC598
_020AC57C:
	ldrb r0, [r0, #0x4]
	mov r2, #0x10
	bl MOD04_021EB044
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
_020AC598:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start FUN_020AC5A4
FUN_020AC5A4: ; 0x020AC5A4
	mov r12, r0
	mov r3, #0x6
	mov r2, #0x0
_020AC5B0:
	strb r2, [r12], #0x1
	strb r2, [r12], #0x1
	strb r2, [r12], #0x1
	strb r2, [r12], #0x1
	subs r3, r3, #0x1
	bne _020AC5B0
	ldr r2, _020AC5E4 ; =__vct
	mov r3, #0x0
	ldr r2, [r2, #0x10]
	str r2, [r0, #0x0]
	str r3, [r0, #0xc]
	strb r1, [r0, #0x4]
	bx lr
	.balign 4
_020AC5E4: .word __vct

	arm_func_start FUN_020AC5E8
FUN_020AC5E8:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	mov r4, r0
	mov r3, #0xff
	ldr r0, _020AC624 ; =UNK_021CB850
	add r1, sp, #0x0
	mov r2, #0x4
	strb r3, [sp, #0x4]
	bl FUN_020AC458
	ldr r0, _020AC624 ; =UNK_021CB850
	add r1, sp, #0x0
	strb r4, [sp, #0xa]
	bl FUN_020AC628
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}
	.balign 4
_020AC624: .word UNK_021CB850

	arm_func_start FUN_020AC628
FUN_020AC628: ; 0x020AC628
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r11, r0
	mov r10, r1
	mov r9, #0x0
	bl FUN_020AC6E4
	ldr r4, _020AC6DC ; =__vct
	ldr r5, _020AC6E0 ; =UNK_021CB818
	mov r8, r9
	mov r7, #0x1
	mov r6, #0x10
_020AC654:
	cmp r8, #0x0
	movne r1, r7, lsl r8
	ldr r0, [r5, #0x0]
	moveq r1, r7
	ands r0, r0, r1
	beq _020AC694
	ldrb r0, [r4, #0x0]
	cmp r8, r0
	beq _020AC694
	mov r0, r8
	mov r1, r10
	mov r2, r6
	strb r8, [r10, #0x9]
	bl MOD04_021EB044
	cmp r0, #0x0
	addne r9, r9, #0x1
_020AC694:
	add r0, r8, #0x1
	and r8, r0, #0xff
	cmp r8, #0x20
	blo _020AC654
	ldrb r0, [r10, #0xa]
	cmp r0, #0x1
	ldreq r0, _020AC6E0 ; =UNK_021CB818
	ldreq r0, [r0, #0x0]
	streq r0, [r11, #0x8]
	beq _020AC6C8
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r11, #0x8]
_020AC6C8:
	cmp r9, #0x0
	mvneq r0, #0x3
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AC6DC: .word __vct
_020AC6E0: .word UNK_021CB818

	arm_func_start FUN_020AC6E4
FUN_020AC6E4: ; 0x020AC6E4
	ldrb r2, [r1, #0xa]
	cmp r2, #0x1
	ldreqb r2, [r0, #0x4]
	ldreq r0, _020AC704 ; =UNK_021CB818
	streqb r2, [r1, #0xb]
	ldreq r0, [r0, #0x0]
	streq r0, [r1, #0xc]
	bx lr
	.balign 4
_020AC704: .word UNK_021CB818

	arm_func_start FUN_020AC708
FUN_020AC708:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	add r2, sp, #0x0
	mov r3, #0x10
	mov r4, r0
	bl FUN_020ACAE0
	cmp r0, #0x0
	addne sp, sp, #0x10
	ldmneia sp!, {r4,pc}
	add r1, sp, #0x0
	mov r0, r4
	bl FUN_020AC554
	cmp r0, #0x0
	movne r0, #0x0
	mvneq r0, #0x3
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AC74C
FUN_020AC74C: ; 0x020AC74C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x10
	add r2, sp, #0x0
	mov r3, #0x10
	mov r4, r0
	bl FUN_020ACBD0
	cmp r0, #0x0
	addne sp, sp, #0x10
	ldmneia sp!, {r4,pc}
	add r1, sp, #0x0
	mov r0, r4
	bl FUN_020AC554
	cmp r0, #0x0
	movne r0, #0x0
	mvneq r0, #0x3
	add sp, sp, #0x10
	ldmia sp!, {r4,pc}

	arm_func_start FUN_020AC790
FUN_020AC790: ; 0x020AC790
	stmdb sp!, {r4,lr}
	mov r1, r0
	cmp r1, #0x20
	movcs r0, #0x0
	ldmcsia sp!, {r4,pc}
	ldr r0, _020AC7F4 ; =__vct
	ldrb r0, [r0, #0x0]
	cmp r1, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r2, _020AC7F8 ; =UNK_021CB824
	ldr r4, [r2, #0x0]
	cmp r4, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r3, [r4, #0x14]
	mov r0, r4
	str r3, [r2, #0x0]
	bl FUN_020AC5A4
	ldr r1, _020AC7F8 ; =UNK_021CB824
	mov r0, r4
	ldr r2, [r1, #0x4]
	str r2, [r4, #0x14]
	str r4, [r1, #0x4]
	ldmia sp!, {r4,pc}
	.balign 4
_020AC7F4: .word __vct
_020AC7F8: .word UNK_021CB824

	arm_func_start vct_handle_ssp
vct_handle_ssp:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x10
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {pc}
	ldrb r2, [r1, #0x8]
	cmp r2, r0
	bne _020AC834
	ldr r0, _020AC894 ; =__vct
	ldrb r12, [r1, #0x9]
	ldrb r2, [r0, #0x0]
	cmp r12, r2
	beq _020AC840
_020AC834:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020AC840:
	ldrb r2, [r1, #0x5]
	cmp r2, #0x10
	beq _020AC860
	mov r0, r1
	mov r1, r3
	bl FUN_020ABE40
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020AC860:
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	bne _020AC880
	mov r0, r1
	mov r1, r3
	bl FUN_020AC080
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020AC880:
	mov r0, r1
	mov r1, r3
	bl FUN_020ABECC
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AC894: .word __vct

	arm_func_start vct_check_timeout
vct_check_timeout: ; 0x020AC898
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_GetTick
	ldr r2, _020AC950 ; =__vct
	ldr r3, [r2, #0x10]
	cmp r3, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
	ldr r2, [r2, #0xc]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r3, _020AC954 ; =UNK_021CB81C
	mov r12, #0x0
	ldr r5, [r3, #0x4]
	ldr r4, [r3, #0x0]
	cmp r5, r12
	cmpeq r4, r12
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r2, _020AC958 ; =UNK_02106490
	subs r4, r0, r4
	ldr lr, [r2, #0x0]
	ldr r0, [r2, #0x4]
	sbc r1, r1, r5
	cmp r1, r0
	cmpeq r4, lr
	addls sp, sp, #0x4
	ldmlsia sp!, {r4-r5,pc}
	ldr r1, _020AC95C ; =UNK_021CB824
	mov r0, r12
	str r12, [r3, #0x0]
	str r12, [r3, #0x4]
	str r12, [r1, #0x2c]
	str r12, [r1, #0x38]
	bl FUN_020AC5E8
	ldr r1, _020AC950 ; =__vct
	ldr r0, _020AC95C ; =UNK_021CB824
	ldr r3, [r1, #0x8]
	ldrb r0, [r0, #0x30]
	ldr r12, [r1, #0x4]
	ldr r2, _020AC960 ; =UNK_021CB850
	mov r1, #0x9
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020AC950: .word __vct
_020AC954: .word UNK_021CB81C
_020AC958: .word UNK_02106490
_020AC95C: .word UNK_021CB824
_020AC960: .word UNK_021CB850

	arm_func_start vct_finish_ssp
vct_finish_ssp: ; 0x020AC964
	ldr r0, _020AC978 ; =UNK_021CB824
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020AC978: .word UNK_021CB824

	arm_func_start FUN_020AC97C
FUN_020AC97C:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020AC9A8
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _020AC9A8
	cmp r1, #0x8
	bls _020AC9B4
_020AC9A8:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,pc}
_020AC9B4:
	ldr r1, _020ACA8C ; =UNK_021CB824
	mov r2, #0x18
	str r0, [r1, #0x0]
	ldr r3, [r4, #0x4]
	mov r1, #0x0
	mul r2, r3, r2
	bl MI_CpuFill8
	ldr r0, _020ACA90 ; =UNK_021CB850
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	ldr r0, _020ACA94 ; =UNK_021CB838
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	ldr r12, [r4, #0x4]
	mov lr, #0x0
	subs r0, r12, #0x1
	beq _020ACA34
	ldr r1, _020ACA8C ; =UNK_021CB824
	mov r5, lr
	mov r0, #0x18
_020ACA0C:
	ldr r2, [r1, #0x0]
	add lr, lr, #0x1
	mla r3, lr, r0, r2
	add r2, r2, r5
	str r3, [r2, #0x14]
	ldr r12, [r4, #0x4]
	add r5, r5, #0x18
	sub r2, r12, #0x1
	cmp lr, r2
	blo _020ACA0C
_020ACA34:
	ldr r3, _020ACA8C ; =UNK_021CB824
	mov r0, #0x18
	ldr r1, [r3, #0x0]
	mov r5, #0x0
	mla r0, r12, r0, r1
	str r5, [r0, #-0x4]
	ldr r2, _020ACA98 ; =UNK_021CB818
	ldr r1, _020ACA9C ; =UNK_021CB814
	ldr r0, _020ACAA0 ; =__vct
	ldr lr, _020ACAA4 ; =OS_GetTick
	ldr ip, _020ACAA8 ; =0x5D588B65
	ldr r4, _020ACAAC ; =0x00269EC3
	str r5, [r3, #0x4]
	str r5, [r2, #0x0]
	str r5, [r1, #0x0]
	str r5, [r0, #0x14]
	str lr, [r3, #0x8]
	str r12, [r3, #0xc]
	str r4, [r3, #0x10]
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020ACA8C: .word UNK_021CB824
_020ACA90: .word UNK_021CB850
_020ACA94: .word UNK_021CB838
_020ACA98: .word UNK_021CB818
_020ACA9C: .word UNK_021CB814
_020ACAA0: .word __vct
_020ACAA4: .word OS_GetTick
_020ACAA8: .word 0x5D588B65
_020ACAAC: .word 0x00269EC3

	arm_func_start FUN_020ACAB0
FUN_020ACAB0: ; 0x020ACAB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020ACADC ; =__vct
	ldr r2, [r2, #0x10]
	cmp r2, #0x2
	addeq sp, sp, #0x4
	mvneq r0, #0x2
	ldmeqia sp!, {pc}
	bl FUN_020AC708
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACADC: .word __vct

	arm_func_start FUN_020ACAE0
FUN_020ACAE0:
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r6, r1
	mov r4, r2
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	cmp r3, #0x10
	mvncc r0, #0x0
	ldmccia sp!, {r4-r6,pc}
	cmp r6, #0x0
	blt _020ACB14
	cmp r6, #0x6
	blt _020ACB1C
_020ACB14:
	mvn r0, #0x2
	ldmia sp!, {r4-r6,pc}
_020ACB1C:
	mov r3, #0x0
	mov r1, r4
	and r2, r6, #0xff
	strb r3, [r4, #0x4]
	bl FUN_020AC458
	cmp r6, #0x0
	bne _020ACB80
	ldr r0, _020ACB9C ; =__vct
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	bne _020ACB68
	ldr r0, [r5, #0xc]
	cmp r0, #0x4
	bne _020ACB68
	mov r0, r5
	bl FUN_020AC304
	cmp r0, #0x0
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
_020ACB68:
	ldrb r1, [r5, #0x4]
	cmp r1, #0x0
	movne r0, #0x1
	movne r0, r0, lsl r1
	moveq r0, #0x1
	str r0, [r5, #0x8]
_020ACB80:
	mov r0, r5
	mov r1, r4
	bl FUN_020AC268
	cmp r0, #0x0
	mvneq r0, #0x2
	movne r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ACB9C: .word __vct

	arm_func_start FUN_020ACBA0
FUN_020ACBA0: ; 0x020ACBA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020ACBCC ; =__vct
	ldr r2, [r2, #0x10]
	cmp r2, #0x2
	addeq sp, sp, #0x4
	mvneq r0, #0x2
	ldmeqia sp!, {pc}
	bl FUN_020AC74C
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACBCC: .word __vct

	arm_func_start FUN_020ACBD0
FUN_020ACBD0:
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r4, r1
	mov r6, r2
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	cmp r3, #0x10
	mvncc r0, #0x0
	ldmccia sp!, {r4-r6,pc}
	ldr r1, _020ACC80 ; =__vct
	ldr r1, [r1, #0xc]
	cmp r1, #0x1
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
	cmp r4, #0x0
	blt _020ACC18
	cmp r4, #0x5
	blt _020ACC20
_020ACC18:
	mvn r0, #0x2
	ldmia sp!, {r4-r6,pc}
_020ACC20:
	mov r3, #0xff
	mov r1, r6
	and r2, r4, #0xff
	strb r3, [r6, #0x4]
	bl FUN_020AC458
	mov r0, r5
	mov r1, r6
	bl FUN_020AC268
	cmp r0, #0x0
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
	ldr r0, _020ACC80 ; =__vct
	ldr r0, [r0, #0x10]
	cmp r0, #0x1
	bne _020ACC78
	cmp r4, #0x0
	bne _020ACC78
	mov r0, r5
	bl FUN_020AC304
	cmp r0, #0x0
	mvneq r0, #0x2
	ldmeqia sp!, {r4-r6,pc}
_020ACC78:
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020ACC80: .word __vct

	arm_func_start FUN_020ACC84
FUN_020ACC84: ; 0x020ACC84
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020ACD48 ; =UNK_021CB824
	cmp r0, #0x0
	mov lr, #0x0
	addeq sp, sp, #0x4
	ldr r12, [r2, #0x4]
	moveq r0, lr
	ldmeqia sp!, {pc}
	ldr r1, _020ACD4C ; =__vct
	ldr r1, [r1, #0x10]
	cmp r1, #0x2
	bne _020ACCD0
	ldr r1, _020ACD50 ; =UNK_021CB850
	add sp, sp, #0x4
	cmp r0, r1
	streq lr, [r2, #0x2c]
	mov r0, #0x1
	ldmia sp!, {pc}
_020ACCD0:
	cmp r12, #0x0
	beq _020ACD3C
_020ACCD8:
	cmp r12, r0
	bne _020ACD2C
	mov r3, #0x0
	str r3, [r0, #0x0]
	cmp lr, #0x0
	ldrne r1, [r0, #0x14]
	strne r1, [lr, #0x14]
	bne _020ACD10
	ldr r2, [r12, #0x14]
	cmp r2, #0x0
	ldrne r1, _020ACD48 ; =UNK_021CB824
	strne r2, [r1, #0x4]
	ldreq r1, _020ACD48 ; =UNK_021CB824
	streq r3, [r1, #0x4]
_020ACD10:
	ldr r1, _020ACD48 ; =UNK_021CB824
	add sp, sp, #0x4
	ldr r2, [r1, #0x0]
	str r2, [r0, #0x14]
	str r0, [r1, #0x0]
	mov r0, #0x1
	ldmia sp!, {pc}
_020ACD2C:
	mov lr, r12
	ldr r12, [r12, #0x14]
	cmp r12, #0x0
	bne _020ACCD8
_020ACD3C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACD48: .word UNK_021CB824
_020ACD4C: .word __vct
_020ACD50: .word UNK_021CB850

	arm_func_start FUN_020ACD54
FUN_020ACD54: ; 0x020ACD54
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020ACD8C ; =__vct
	ldr r1, [r1, #0x10]
	cmp r1, #0x0
	beq _020ACD74
	cmp r1, #0x2
	bne _020ACD80
_020ACD74:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {pc}
_020ACD80:
	bl FUN_020AC790
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020ACD8C: .word __vct

	arm_func_start vct_free_packet_buffer
vct_free_packet_buffer:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020ACDC0 ; =UNK_021CB86C
	ldr r2, _020ACDC4 ; =UNK_021CB868
	ldr r3, [r1, #0x0]
	str r0, [r2, #0x0]
	str r3, [r4, #0x0]
	ldr r0, [r2, #0x0]
	str r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,pc}
	.balign 4
_020ACDC0: .word UNK_021CB86C
_020ACDC4: .word UNK_021CB868

	arm_func_start vct_alloc_packet_buffer
vct_alloc_packet_buffer: ; 0x020ACDC8
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	bl OS_DisableInterrupts
	ldr r1, _020ACE08 ; =UNK_021CB86C
	ldr r2, _020ACE0C ; =UNK_021CB868
	ldr r3, [r1, #0x0]
	str r0, [r2, #0x0]
	cmp r3, #0x0
	ldrne r0, [r3, #0x0]
	movne r4, r3
	strne r0, [r1, #0x0]
	ldr r0, _020ACE0C ; =UNK_021CB868
	ldr r0, [r0, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,pc}
	.balign 4
_020ACE08: .word UNK_021CB86C
_020ACE0C: .word UNK_021CB868

	arm_func_start vct_cleanup_packet_buffer
vct_cleanup_packet_buffer:
	ldr r1, _020ACE28 ; =UNK_021CB86C
	mov r2, #0x0
	ldr r0, _020ACE2C ; =UNK_021CB870
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	bx lr
	.balign 4
_020ACE28: .word UNK_021CB86C
_020ACE2C: .word UNK_021CB870

	arm_func_start FUN_020ACE30
FUN_020ACE30:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r3, _020ACF00 ; =0xE525982B
	mov r2, r1
	umull r1, r4, r2, r3
	ldr r1, _020ACF04 ; =UNK_021CB870
	mov r4, r4, lsr #0xa
	str r0, [r1, #0x0]
	cmp r4, #0x4
	blo _020ACE60
	cmp r4, #0x48
	bls _020ACE6C
_020ACE60:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,pc}
_020ACE6C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	ands r3, r0, #0x1f
	movne r0, #0x0
	strne r0, [r1, #0x0]
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,pc}
	mov r1, r0
	mov r0, #0x0
	bl MIi_CpuClearFast
	subs r12, r4, #0x1
	mov r5, #0x0
	beq _020ACED0
	ldr r1, _020ACF04 ; =UNK_021CB870
	ldr r0, _020ACF08 ; =0x00000478
	mov lr, r5
_020ACEB4:
	ldr r3, [r1, #0x0]
	add r5, r5, #0x1
	mla r2, r5, r0, r3
	str r2, [r3, lr]
	cmp r5, r12
	add lr, lr, r0
	blo _020ACEB4
_020ACED0:
	ldr r1, _020ACF04 ; =UNK_021CB870
	ldr r0, _020ACF08 ; =0x00000478
	ldr r2, [r1, #0x0]
	mov r3, #0x0
	mla r0, r4, r0, r2
	str r3, [r0, #-0x478]
	ldr r2, [r1, #0x0]
	ldr r1, _020ACF0C ; =UNK_021CB86C
	mov r0, #0x1
	str r2, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020ACF00: .word 0xE525982B
_020ACF04: .word UNK_021CB870
_020ACF08: .word 0x00000478
_020ACF0C: .word UNK_021CB86C

	arm_func_start FUN_020ACF10
FUN_020ACF10: ; 0x020ACF10
	mov r2, #0xf
	mov r0, #0x44
	mul r1, r2, r0
	ldr r0, _020ACF30 ; =UNK_02106498
	ldr ip, _020ACF34 ; =FUN_020AD170
	str r2, [r0, #0x8]
	str r1, [r0, #0xc]
	bx r12
	.balign 4
_020ACF30: .word UNK_02106498
_020ACF34: .word FUN_020AD170

	arm_func_start FUN_020ACF38
FUN_020ACF38: ; 0x020ACF38
	stmdb sp!, {r4,lr}
	ldr r3, _020AD124 ; =UNK_02106498
	mov r12, r1, lsr #0x8
	str r12, [r3, #0x4]
	cmp r2, #0x0
	strneb r12, [r2, #0x0]
	ldr r2, _020AD124 ; =UNK_02106498
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	bne _020AD05C
	mov r4, #0x0
	mov r12, r4
	ldr r3, _020AD128 ; =UNK_021CB880
_020ACF6C:
	ldr r2, [r3, r12, lsl #0x2]
	add r12, r12, #0x1
	cmp r12, #0x4
	add r4, r4, r2
	blt _020ACF6C
	ldr ip, _020AD12C ; =0x040002B0
	mov r3, #0x0
	ldr r2, _020AD130 ; =0x040002B8
	strh r3, [r12, #0x0]
	mov r3, r4, lsr #0x2
	str r3, [r2, #0x0]
_020ACF98:
	ldrh r2, [r12, #0x0]
	ands r2, r2, #0x8000
	bne _020ACF98
	ldr r2, _020AD134 ; =0x040002B4
	cmp r1, #0x0
	ldr r2, [r2, #0x0]
	beq _020AD038
	cmp r1, r2, lsl #0x1
	blo _020AD038
	mov r4, #0x0
	mov r3, r4
	ldr r2, _020AD128 ; =UNK_021CB880
_020ACFC8:
	ldr r1, [r2, r3, lsl #0x2]
	add r3, r3, #0x1
	cmp r3, #0x4
	add r4, r4, r1
	blo _020ACFC8
	ldr r3, _020AD12C ; =0x040002B0
	mov r2, #0x0
	ldr r1, _020AD130 ; =0x040002B8
	strh r2, [r3, #0x0]
	mov r2, r4, lsr #0x2
	str r2, [r1, #0x0]
_020ACFF4:
	ldrh r1, [r3, #0x0]
	ands r1, r1, #0x8000
	bne _020ACFF4
	ldr r2, _020AD134 ; =0x040002B4
	mov r1, #0x3
	ldr r2, [r2, #0x0]
	ldr r3, _020AD138 ; =UNK_021CB874
	mul r1, r2, r1
	mov lr, r1, lsr #0x1
	ldr r2, _020AD13C ; =UNK_021CB878
	mov r12, #0x0
	ldr r1, _020AD124 ; =UNK_02106498
	mov r4, #0x1
	str lr, [r3, #0x0]
	str r12, [r2, #0x0]
	str r4, [r1, #0x0]
	b _020AD03C
_020AD038:
	mov r4, #0x0
_020AD03C:
	ldr r1, _020AD13C ; =UNK_021CB878
	ldr r3, _020AD128 ; =UNK_021CB880
	ldr r12, [r1, #0x0]
	add r2, r12, #0x1
	and r2, r2, #0x3
	str r0, [r3, r12, lsl #0x2]
	str r2, [r1, #0x0]
	b _020AD11C
_020AD05C:
	ldr r1, _020AD13C ; =UNK_021CB878
	mov lr, #0x0
	ldr r12, [r1, #0x0]
	ldr r3, _020AD128 ; =UNK_021CB880
	add r2, r12, #0x1
	and r2, r2, #0x3
	mov r4, lr
	str r0, [r3, r12, lsl #0x2]
	str r2, [r1, #0x0]
_020AD080:
	ldr r0, [r3, r4, lsl #0x2]
	add r4, r4, #0x1
	cmp r4, #0x4
	add lr, lr, r0
	blt _020AD080
	ldr r2, _020AD12C ; =0x040002B0
	mov r1, #0x0
	ldr r0, _020AD130 ; =0x040002B8
	strh r1, [r2, #0x0]
	mov r1, lr, lsr #0x2
	str r1, [r0, #0x0]
_020AD0AC:
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x8000
	bne _020AD0AC
	ldr r1, _020AD134 ; =0x040002B4
	ldr r0, _020AD138 ; =UNK_021CB874
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	cmp r1, r0
	bhi _020AD10C
	ldr r2, _020AD140 ; =UNK_021CB87C
	ldr r1, _020AD124 ; =UNK_02106498
	ldr r3, [r2, #0x0]
	ldr r0, [r1, #0x8]
	add r3, r3, #0x1
	str r3, [r2, #0x0]
	cmp r3, r0
	ble _020AD118
	ldr r0, _020AD13C ; =UNK_021CB878
	mov r3, #0x0
	str r3, [r0, #0x0]
	str r3, [r1, #0x0]
	str r3, [r2, #0x0]
	mov r0, #0x3
	ldmia sp!, {r4,pc}
_020AD10C:
	ldr r0, _020AD140 ; =UNK_021CB87C
	mov r1, #0x0
	str r1, [r0, #0x0]
_020AD118:
	mov r4, #0x2
_020AD11C:
	mov r0, r4
	ldmia sp!, {r4,pc}
	.balign 4
_020AD124: .word UNK_02106498
_020AD128: .word UNK_021CB880
_020AD12C: .word 0x040002B0
_020AD130: .word 0x040002B8
_020AD134: .word 0x040002B4
_020AD138: .word UNK_021CB874
_020AD13C: .word UNK_021CB878
_020AD140: .word UNK_021CB87C

	arm_func_start FUN_020AD144
FUN_020AD144: ; 0x020AD144
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	movs r1, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, _020AD16C ; =UNK_02106498
	mov r2, #0x10
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD16C: .word UNK_02106498

	arm_func_start FUN_020AD170
FUN_020AD170:
	ldr r0, _020AD1B8 ; =UNK_021CB880
	mov r2, #0x0
	mov r1, #0x1000000
_020AD17C:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x4
	blt _020AD17C
	ldr r3, _020AD1BC ; =UNK_021CB878
	mov r12, #0x0
	ldr r1, _020AD1C0 ; =UNK_02106498
	ldr r2, _020AD1C4 ; =UNK_021CB874
	ldr r0, _020AD1C8 ; =UNK_021CB87C
	str r12, [r3, #0x0]
	str r12, [r2, #0x0]
	str r12, [r1, #0x0]
	str r12, [r1, #0x4]
	str r12, [r0, #0x0]
	bx lr
	.balign 4
_020AD1B8: .word UNK_021CB880
_020AD1BC: .word UNK_021CB878
_020AD1C0: .word UNK_02106498
_020AD1C4: .word UNK_021CB874
_020AD1C8: .word UNK_021CB87C

	arm_func_start FUN_020AD1CC
FUN_020AD1CC: ; 0x020AD1CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, r1
	mov r3, r2
	ldr r1, _020AD1F0 ; =UNK_021CB8D4
	mov r2, r12
	bl FUN_020AD1F4
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD1F0: .word UNK_021CB8D4

	arm_func_start FUN_020AD1F4
FUN_020AD1F4: ; 0x020AD1F4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r4, #0x0
	str r4, [sp, #0x0]
	str r4, [sp, #0x4]
	mov r9, r4
	movs r8, r2, lsr #0x1
	beq _020AD330
	mov r4, #0xc0000000
	ldr ip, _020AD420 ; =UNK_021CB8BC
	ldr r2, _020AD424 ; =UNK_021CB8A4
	str r4, [sp, #0xc]
_020AD224:
	ldr r4, _020AD428 ; =UNK_021CB894
	ldr lr, [r2, #0x10]
	ldr r7, [r4, #0x0]
	mov r4, r9, lsl #0x1
	ldrsh r10, [r1, r4]
	ldr r4, _020AD42C ; =UNK_021CB898
	mov r5, r7, lsl #0x1
	ldr r6, [r4, #0x0]
	ldr r4, _020AD430 ; =UNK_021CBD14
	ldr r11, [r2, #0x14]
	strh r10, [r4, r5]
	ldr r10, [r12, #0x10]
	mov r5, r6, lsl #0x1
	ldrsh r5, [r4, r5]
	ldr r4, [r12, #0x14]
	mul lr, r10, lr
	str r10, [sp, #0x8]
	str r10, [r12, #0x14]
	mla r10, r4, r11, lr
	ldr r4, [r12, #0xc]
	ldr r11, [r2, #0xc]
	str r4, [r12, #0x10]
	mla r10, r4, r11, r10
	ldr r4, [r12, #0x8]
	ldr r11, [r2, #0x8]
	str r4, [r12, #0xc]
	mla r10, r4, r11, r10
	ldr r4, [r12, #0x4]
	ldr r11, [r2, #0x4]
	str r4, [r12, #0x8]
	mla r10, r4, r11, r10
	ldr r4, [r2, #0x0]
	str r5, [r12, #0x0]
	mla r4, r5, r4, r10
	str r5, [r12, #0x4]
	ldr r5, _020AD434 ; =0x3FFF8000
	cmp r4, r5
	movgt r4, r5
	bgt _020AD2C8
	cmp r4, #0xc0000000
	ldrlt r4, [sp, #0xc]
_020AD2C8:
	ldr r5, _020AD438 ; =0x000007FF
	add r7, r7, #0x1
	and r7, r7, r5
	ldr r5, _020AD428 ; =UNK_021CB894
	add r6, r6, #0x1
	str r7, [r5, #0x0]
	ldr r5, _020AD438 ; =0x000007FF
	mov r7, r9, lsl #0x1
	and r6, r6, r5
	ldr r5, _020AD42C ; =UNK_021CB898
	mov r4, r4, asr #0xf
	str r6, [r5, #0x0]
	strh r4, [r1, r7]
	ldrsh r6, [r1, r7]
	ldrsh r4, [r0, r7]
	add r9, r9, #0x1
	mul r5, r6, r6
	strh r4, [r1, r7]
	ldr r4, [sp, #0x0]
	adds r4, r4, r5
	str r4, [sp, #0x0]
	ldr r4, [sp, #0x4]
	adc r4, r4, r5, asr #0x1f
	str r4, [sp, #0x4]
	cmp r9, r8
	blo _020AD224
_020AD330:
	ldr r5, _020AD43C ; =0x04000280
	mov r1, #0x1
	strh r1, [r5, #0x0]
	ldr r4, _020AD440 ; =0x04000290
	ldr r1, [sp, #0x0]
	ldr r2, _020AD444 ; =0x04000298
	str r1, [r4, #0x0]
	ldr r1, [sp, #0x4]
	str r1, [r4, #0x4]
	str r8, [r2, #0x0]
	mov r1, #0x0
	str r1, [r2, #0x4]
_020AD360:
	ldrh r1, [r5, #0x0]
	ands r1, r1, #0x8000
	bne _020AD360
	ldr r1, _020AD448 ; =0x040002A0
	ldr r2, _020AD44C ; =0x040002B0
	ldr r5, [r1, #0x0]
	mov r4, #0x0
	ldr r1, _020AD450 ; =0x040002B8
	strh r4, [r2, #0x0]
	str r5, [r1, #0x0]
_020AD388:
	ldrh r1, [r2, #0x0]
	ands r1, r1, #0x8000
	bne _020AD388
	ldr r2, _020AD454 ; =0x040002B4
	mov r1, #0x3
	ldr r4, [r2, #0x0]
	mov r2, r3, lsl #0x1
	mul r1, r4, r1
	cmp r2, r1
	ldrhi r0, _020AD458 ; =UNK_021CB890
	movhi r1, #0x0
	strhih r1, [r0, #0x0]
	addhi sp, sp, #0x14
	ldmhiia sp!, {r4-r11,pc}
	cmp r3, r4
	ldrlo r1, _020AD458 ; =UNK_021CB890
	movcc r2, #0x4
	strcch r2, [r1, #0x0]
	ldr r1, _020AD458 ; =UNK_021CB890
	mov r3, #0x0
	ldrsh r2, [r1, #0x0]
	cmp r2, #0x4
	addlt r2, r2, #0x1
	strlth r2, [r1, #0x0]
	cmp r8, #0x0
	addls sp, sp, #0x14
	ldmlsia sp!, {r4-r11,pc}
	ldr r1, _020AD458 ; =UNK_021CB890
	ldrsh r4, [r1, #0x0]
_020AD3FC:
	mov r2, r3, lsl #0x1
	ldrsh r1, [r0, r2]
	add r3, r3, #0x1
	cmp r3, r8
	mov r1, r1, asr r4
	strh r1, [r0, r2]
	blo _020AD3FC
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AD420: .word UNK_021CB8BC
_020AD424: .word UNK_021CB8A4
_020AD428: .word UNK_021CB894
_020AD42C: .word UNK_021CB898
_020AD430: .word UNK_021CBD14
_020AD434: .word 0x3FFF8000
_020AD438: .word 0x000007FF
_020AD43C: .word 0x04000280
_020AD440: .word 0x04000290
_020AD444: .word 0x04000298
_020AD448: .word 0x040002A0
_020AD44C: .word 0x040002B0
_020AD450: .word 0x040002B8
_020AD454: .word 0x040002B4
_020AD458: .word UNK_021CB890

	arm_func_start FUN_020AD45C
FUN_020AD45C: ; 0x020AD45C
	ldr ip, _020AD46C ; =MIi_CpuCopyFast
	mov r2, r1
	ldr r1, _020AD470 ; =UNK_021CB8D4
	bx r12
	.balign 4
_020AD46C: .word MIi_CpuCopyFast
_020AD470: .word UNK_021CB8D4

	arm_func_start FUN_020AD474
FUN_020AD474: ; 0x020AD474
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020AD4E4 ; =UNK_021CB894
	mov r3, #0x0
	ldr r2, _020AD4E8 ; =0x0000019D
	ldr r0, _020AD4EC ; =UNK_021CB898
	ldr lr, _020AD4F0 ; =UNK_021064A8
	str r3, [r1, #0x0]
	str r2, [r0, #0x0]
	ldr r0, _020AD4F4 ; =UNK_021CBD14
	mov r12, r3
_020AD4A0:
	mov r1, r3, lsl #0x1
	add r3, r3, #0x1
	strh r12, [r0, r1]
	cmp r3, #0x800
	blt _020AD4A0
	ldr r2, _020AD4F8 ; =UNK_021CB8BC
	ldr r0, _020AD4FC ; =UNK_021CB8A4
	mov r3, #0x0
_020AD4C0:
	str r3, [r2, r12, lsl #0x2]
	mov r1, r12, lsl #0x1
	ldrsh r1, [lr, r1]
	str r1, [r0, r12, lsl #0x2]
	add r12, r12, #0x1
	cmp r12, #0x6
	blt _020AD4C0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD4E4: .word UNK_021CB894
_020AD4E8: .word 0x0000019D
_020AD4EC: .word UNK_021CB898
_020AD4F0: .word UNK_021064A8
_020AD4F4: .word UNK_021CBD14
_020AD4F8: .word UNK_021CB8BC
_020AD4FC: .word UNK_021CB8A4

	arm_func_start FUN_020AD500
FUN_020AD500: ; 0x020AD500
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldrsh r2, [r0, #0x0]
	ldr r6, _020AD5FC ; =0x00000E9F
	ldr sb, _020AD600 ; =UNK_021CB89C
	ldr r8, _020AD604 ; =UNK_021CB8A0
	smulbb r10, r2, r6
	ldr r3, [r9, #0x0]
	ldr r2, [r8, #0x0]
	ldr r7, _020AD608 ; =0x00000D3E
	add r3, r10, r3
	mla r5, r2, r7, r3
	mov r3, r5, asr #0xc
	mul r4, r3, r3
	str r5, [r8, #0x0]
	rsb r2, r10, #0x0
	mov r12, r1, lsr #0x1
	str r3, [r8, #0x0]
	str r2, [r9, #0x0]
	cmp r12, #0x1
	mov lr, r4, asr #0x1f
	mov r5, #0x1
	bls _020AD5AC
_020AD55C:
	mov r2, r5, lsl #0x1
	ldrsh r10, [r0, r2]
	ldr r3, [r8, #0x0]
	add r2, r0, r5, lsl #0x1
	strh r3, [r2, #-0x2]
	smulbb r11, r10, r6
	ldr r2, [r9, #0x0]
	rsb r10, r11, #0x0
	add r2, r11, r2
	mla r2, r3, r7, r2
	mov r3, r2, asr #0xc
	mul r11, r3, r3
	str r2, [r8, #0x0]
	adds r4, r4, r11
	str r10, [r9, #0x0]
	add r5, r5, #0x1
	adc lr, lr, r11, asr #0x1f
	str r3, [r8, #0x0]
	cmp r5, r12
	blo _020AD55C
_020AD5AC:
	bic r1, r1, #0x1
	add r0, r0, r1
	ldr r2, _020AD60C ; =0x04000280
	strh r3, [r0, #-0x2]
	mov r0, #0x1
	ldr r1, _020AD610 ; =0x04000290
	strh r0, [r2, #0x0]
	str r4, [r1, #0x0]
	ldr r0, _020AD614 ; =0x04000298
	str lr, [r1, #0x4]
	str r12, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
_020AD5E0:
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x8000
	bne _020AD5E0
	ldr r0, _020AD618 ; =0x040002A0
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020AD5FC: .word 0x00000E9F
_020AD600: .word UNK_021CB89C
_020AD604: .word UNK_021CB8A0
_020AD608: .word 0x00000D3E
_020AD60C: .word 0x04000280
_020AD610: .word 0x04000290
_020AD614: .word 0x04000298
_020AD618: .word 0x040002A0

; libvct.a:mixer.o

	arm_func_start vct_mix_audio
vct_mix_audio:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs lr, r3, lsr #0x1
	mov r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	mov r3, #0x8000
	ldr ip, _020AD720 ; =0x00007FFF
	rsb r3, r3, #0x0
_020AD640:
	mov r5, r4, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD664
	cmp r6, r3
	movlt r6, r3
_020AD664:
	mov r5, r4, lsl #0x1
	add r7, r4, #0x1
	strh r6, [r2, r5]
	mov r5, r7, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD694
	cmp r6, r3
	movlt r6, r3
_020AD694:
	mov r5, r7, lsl #0x1
	add r7, r4, #0x2
	strh r6, [r2, r5]
	mov r5, r7, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD6CC
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r6, r5
	movlt r6, r3
_020AD6CC:
	mov r5, r7, lsl #0x1
	add r7, r4, #0x3
	strh r6, [r2, r5]
	mov r5, r7, lsl #0x1
	ldrsh r6, [r0, r5]
	ldrsh r5, [r1, r5]
	add r6, r6, r5
	cmp r6, r12
	movgt r6, r12
	bgt _020AD704
	mov r5, #0x8000
	rsb r5, r5, #0x0
	cmp r6, r5
	movlt r6, r3
_020AD704:
	mov r5, r7, lsl #0x1
	add r4, r4, #0x4
	strh r6, [r2, r5]
	cmp r4, lr
	blo _020AD640
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AD720: .word 0x00007FFF

; libvct.a:vct_main.o

	arm_func_start VCTi_HandleData
VCTi_HandleData:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r6, r1
	mov r7, r0
	mov r5, r2
	mov r4, r3
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldr r1, [r6, #0x0]
	ldr r0, _020AD824 ; =0x5F564354
	cmp r1, r0
	addne sp, sp, #0x4
	movne r0, #0x2
	ldmneia sp!, {r4-r7,pc}
	ldr r0, _020AD828 ; =__vct
	ldr r0, [r0, #0x10]
	cmp r0, #0x0
	beq _020AD780
	ldr r0, _020AD82C ; =initialized
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020AD78C
_020AD780:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AD78C:
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	bl OS_GetTick
	ldrb r3, [r6, #0x4]
	and r2, r3, #0xf0
	cmp r2, #0x40
	bne _020AD7E0
	ldr r2, _020AD830 ; =sRecvPerFrame
	mov r3, r0
	ldr r4, [r2, #0x0]
	mov r0, r7
	add r4, r4, #0x1
	str r4, [r2, #0x0]
	str r1, [sp, #0x0]
	mov r1, r6
	mov r2, r5
	bl vct_handle_audio
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AD7E0:
	cmp r3, #0x0
	beq _020AD7F0
	cmp r3, #0xff
	bne _020AD818
_020AD7F0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	bl vct_handle_ssp
	cmp r0, #0x0
	movne r0, #0x1
	add sp, sp, #0x4
	moveq r0, #0x0
	ldmia sp!, {r4-r7,pc}
_020AD818:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020AD824: .word 0x5F564354
_020AD828: .word __vct
_020AD82C: .word initialized
_020AD830: .word sRecvPerFrame

	arm_func_start VCT_HandleData
VCT_HandleData: ; 0x020AD834
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	add r3, sp, #0x0
	mov r4, r0
	bl VCTi_HandleData
	cmp r0, #0x0
	beq _020AD898
	cmp r0, #0x1
	beq _020AD864
	cmp r0, #0x2
	beq _020AD88C
	b _020AD898
_020AD864:
	ldr r0, _020AD8A4 ; =__vct
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r3, [r0, #0x8]
	ldr r12, [r0, #0x4]
	mov r0, r4
	blx r12
	add sp, sp, #0x8
	mov r0, #0x1
	ldmia sp!, {r4,pc}
_020AD88C:
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AD898:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020AD8A4: .word __vct

	arm_func_start VCT_Main
VCT_Main: ; 0x020AD8A8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020AD8FC ; =initialized
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, _020AD900 ; =UNK_021CCD14
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	ands r0, r1, #0xf
	bne _020AD8E0
	bl vct_check_timeout
_020AD8E0:
	bl vct_flush_send_buffer
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	bl vct_decode_audio_buffer
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD8FC: .word initialized
_020AD900: .word UNK_021CCD14 ; count$7906

	arm_func_start VCT_Cleanup
VCT_Cleanup: ; 0x020AD904
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl vct_finish_audio
	bl vct_finish_ssp
	bl vct_cleanup_packet_buffer
	ldr r1, _020AD934 ; =__vct
	mov r2, #0x0
	ldr r0, _020AD938 ; =initialized
	str r2, [r1, #0x10]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_020AD934: .word __vct
_020AD938: .word initialized

	.extern _SDK_AbiossolibVCT

	arm_func_start VCT_Init
VCT_Init: ; 0x020AD93C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020ADA78 ; =_SDK_AbiossolibVCT
	bl OSi_ReferSymbol
	cmp r4, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, _020ADA7C ; =initialized
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	movne r0, #0x1
	ldmneia sp!, {r4,pc}
	ldr r0, [r4, #0x8]
	cmp r0, #0x1
	beq _020AD98C
	cmp r0, #0x2
	beq _020AD98C
	cmp r0, #0x3
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
_020AD98C:
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r2, [r4, #0x10]
	cmp r2, #0x0
	beq _020AD9B4
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	bne _020AD9BC
_020AD9B4:
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020AD9BC:
	mov r1, r2, lsr #0x1f
	rsb r0, r1, r2, lsl #0x1b
	adds r0, r1, r0, ror #0x1b
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldr r0, _020ADA80 ; =__vct
	mov r1, #0x0
	mov r2, #0x18
	bl MI_CpuFill8
	ldr r2, [r4, #0x18]
	ldr r1, _020ADA80 ; =__vct
	mov r0, #0x0
	str r2, [r1, #0x4]
	ldr r2, [r4, #0x1c]
	str r2, [r1, #0x8]
	ldr r2, [r4, #0x8]
	str r0, [r1, #0xc]
	str r2, [r1, #0x10]
	ldrb r2, [r4, #0xc]
	cmp r2, #0x20
	ldmcsia sp!, {r4,pc}
	strb r2, [r1, #0x0]
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	bl FUN_020ACE30
	cmp r0, #0x0
	bne _020ADA34
	bl vct_cleanup_packet_buffer
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020ADA34:
	mov r0, r4
	bl FUN_020AC97C
	cmp r0, #0x0
	bne _020ADA50
	bl vct_cleanup_packet_buffer
	mov r0, #0x0
	ldmia sp!, {r4,pc}
_020ADA50:
	bl FUN_020AAF58
	cmp r0, #0x0
	ldrne r1, _020ADA7C ; =initialized
	movne r0, #0x1
	strne r0, [r1, #0x0]
	ldmneia sp!, {r4,pc}
	bl vct_finish_ssp
	bl vct_cleanup_packet_buffer
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	.balign 4
_020ADA78: .word _SDK_AbiossolibVCT
_020ADA7C: .word initialized
_020ADA80: .word __vct

; ???
