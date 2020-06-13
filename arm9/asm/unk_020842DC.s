    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020842DC
FUN_020842DC: ; 0x020842DC
	push {r3-r7, lr}
	sub sp, #0x18
	str r1, [sp, #0x4]
	add r6, r0, #0x0
	add r7, r2, #0x0
	ldr r0, [sp, #0x4]
	mov r1, #0x0
	add r2, r3, #0x0
	bl FUN_0206E710
	mov r1, #0xe
	add r4, r0, #0x0
	bl FUN_0206E7DC
	cmp r0, #0x1
	beq _02084308
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x0
	pop {r3-r7, pc}
_02084308:
	add r0, r6, #0x0
	mov r1, #0x9f
	mov r2, #0x0
	bl GetMonData
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084332
	mov r0, #0x7
	tst r0, r5
	beq _02084332
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084332:
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084350
	mov r0, #0x88
	tst r0, r5
	beq _02084350
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084350:
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208436E
	mov r0, #0x10
	tst r0, r5
	beq _0208436E
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208436E:
	add r0, r4, #0x0
	mov r1, #0x12
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208438C
	mov r0, #0x20
	tst r0, r5
	beq _0208438C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208438C:
	add r0, r4, #0x0
	mov r1, #0x13
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020843AA
	mov r0, #0x40
	tst r0, r5
	beq _020843AA
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020843AA:
	add r0, r6, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	add r5, r0, #0x0
	add r0, r4, #0x0
	mov r1, #0x17
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _020843CE
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020843EA
_020843CE:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _020843EA
	cmp r5, #0x0
	bne _02084414
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020843EA:
	add r0, r4, #0x0
	mov r1, #0x26
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084414
	cmp r5, #0x0
	beq _02084414
	add r0, r6, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	cmp r5, r0
	bhs _02084414
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084414:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208443A
	add r0, r6, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x64
	bhs _0208443A
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208443A:
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084464
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r1, r6, #0x0
	mov r2, #0x3
	bl FUN_02069168
	cmp r0, #0x0
	beq _02084464
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084464:
	add r0, r4, #0x0
	mov r1, #0x22
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _0208447C
	add r0, r4, #0x0
	mov r1, #0x23
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020844B2
_0208447C:
	add r1, r7, #0x0
	add r0, r6, #0x0
	add r1, #0x3e
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x3
	bhs _020844B2
	add r1, r7, #0x0
	add r0, r6, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x0
	bl FUN_0206AB30
	cmp r0, #0x5
	blo _020844B2
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020844B2:
	add r0, r4, #0x0
	mov r1, #0x24
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020844D6
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_02084DF0
	cmp r0, #0x1
	bne _020844D6
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020844D6:
	add r0, r4, #0x0
	mov r1, #0x25
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084502
	mov r5, #0x0
_020844E4:
	add r0, r6, #0x0
	add r1, r5, #0x0
	bl FUN_02084DF0
	cmp r0, #0x1
	bne _020844FC
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020844FC:
	add r5, r5, #0x1
	cmp r5, #0x4
	blt _020844E4
_02084502:
	add r0, r6, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl GetMonData
	add r5, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x14]
	add r0, r6, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x10]
	add r0, r6, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0xc]
	add r0, r6, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl GetMonData
	add r7, r0, #0x0
	add r0, r6, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	mov r1, #0x49
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _020845C6
	add r0, r4, #0x0
	mov r1, #0x27
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020845C6
	add r0, r4, #0x0
	mov r1, #0x30
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _0208459C
	cmp r5, #0x64
	bge _020845C6
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _020845C6
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208459C:
	bge _020845C6
	cmp r5, #0x0
	ble _020845AE
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020845AE:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _020845C6
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020845C6:
	add r0, r4, #0x0
	mov r1, #0x28
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084632
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02084606
	ldr r0, [sp, #0x14]
	cmp r0, #0x64
	bge _02084632
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _02084632
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084606:
	bge _02084632
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	ble _0208461A
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208461A:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _02084632
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084632:
	add r0, r4, #0x0
	mov r1, #0x29
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020846A0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02084674
	ldr r0, [sp, #0x10]
	cmp r0, #0x64
	bge _020846A0
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _020846A0
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084674:
	bge _020846A0
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	ble _02084688
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084688:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _020846A0
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020846A0:
	add r0, r4, #0x0
	mov r1, #0x2a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208470E
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _020846E2
	ldr r0, [sp, #0xc]
	cmp r0, #0x64
	bge _0208470E
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _0208470E
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020846E2:
	bge _0208470E
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	ble _020846F6
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020846F6:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _0208470E
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208470E:
	add r0, r4, #0x0
	mov r1, #0x2b
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208477C
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02084750
	ldr r0, [sp, #0x8]
	cmp r0, #0x64
	bge _0208477C
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _0208477C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084750:
	bge _0208477C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ble _02084764
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_02084764:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _0208477C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_0208477C:
	add r0, r4, #0x0
	mov r1, #0x2c
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020847E6
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _020847BC
	cmp r7, #0x64
	bge _020847E6
	ldr r0, [sp, #0x14]
	add r1, r5, r0
	ldr r0, [sp, #0x10]
	add r1, r0, r1
	ldr r0, [sp, #0xc]
	add r1, r0, r1
	ldr r0, [sp, #0x8]
	add r0, r0, r1
	add r1, r7, r0
	ldr r0, _020847F4 ; =0x000001FE
	cmp r1, r0
	bge _020847E6
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020847BC:
	bge _020847E6
	cmp r7, #0x0
	ble _020847CE
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020847CE:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_02085000
	cmp r0, #0x1
	bne _020847E6
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x18
	mov r0, #0x1
	pop {r3-r7, pc}
_020847E6:
	add r0, r4, #0x0
	bl FreeToHeap
	mov r0, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_020847F4: .word 0x000001FE

	thumb_func_start FUN_020847F8
FUN_020847F8: ; 0x020847F8
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r1, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0206B9B0
	ldr r3, [sp, #0x10]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_020842DC
	pop {r3-r5, pc}

	thumb_func_start FUN_02084810
FUN_02084810: ; 0x02084810
	push {r3-r7, lr}
	sub sp, #0x70
	add r5, r0, #0x0
	ldr r0, [sp, #0x88]
	str r2, [sp, #0x4]
	str r0, [sp, #0x88]
	add r0, r1, #0x0
	ldr r2, [sp, #0x88]
	mov r1, #0x0
	str r3, [sp, #0x8]
	bl FUN_0206E710
	mov r1, #0xe
	add r4, r0, #0x0
	bl FUN_0206E7DC
	cmp r0, #0x1
	beq _02084840
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x70
	mov r0, #0x0
	pop {r3-r7, pc}
_02084840:
	mov r6, #0x0
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, r6, #0x0
	add r7, r6, #0x0
	bl GetMonData
	str r0, [sp, #0x50]
	str r0, [sp, #0x54]
	add r0, r4, #0x0
	mov r1, #0xf
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084868
	ldr r1, [sp, #0x54]
	mov r0, #0x7
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_02084868:
	add r0, r4, #0x0
	mov r1, #0x10
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208487E
	ldr r1, [sp, #0x54]
	ldr r0, _02084A28 ; =0xFFFFF077
	mov r7, #0x1
	and r0, r1
	str r0, [sp, #0x54]
_0208487E:
	add r0, r4, #0x0
	mov r1, #0x11
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084894
	ldr r1, [sp, #0x54]
	mov r0, #0x10
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_02084894:
	add r0, r4, #0x0
	mov r1, #0x12
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020848AA
	ldr r1, [sp, #0x54]
	mov r0, #0x20
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_020848AA:
	add r0, r4, #0x0
	mov r1, #0x13
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020848C0
	ldr r1, [sp, #0x54]
	mov r0, #0x40
	bic r1, r0
	str r1, [sp, #0x54]
	mov r7, #0x1
_020848C0:
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x54]
	cmp r1, r0
	beq _020848D4
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x54
	bl SetMonData
	mov r6, #0x1
_020848D4:
	add r0, r5, #0x0
	mov r1, #0xa2
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x54]
	add r0, r4, #0x0
	mov r1, #0x17
	bl FUN_0206E7DC
	cmp r0, #0x0
	bne _02084904
	add r0, r4, #0x0
	mov r1, #0x18
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084930
_02084904:
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084930
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	bne _0208492C
	add r0, r4, #0x0
	mov r1, #0x36
	bl FUN_0206E7DC
	add r3, r0, #0x0
	ldr r1, [sp, #0x50]
	ldr r2, [sp, #0x54]
	add r0, r5, #0x0
	bl FUN_02084F68
	mov r6, #0x1
_0208492C:
	mov r7, #0x1
	b _0208495C
_02084930:
	add r0, r4, #0x0
	mov r1, #0x26
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208495C
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x54]
	cmp r1, r0
	bge _0208495A
	add r0, r4, #0x0
	mov r1, #0x36
	bl FUN_0206E7DC
	add r3, r0, #0x0
	ldr r1, [sp, #0x50]
	ldr r2, [sp, #0x54]
	add r0, r5, #0x0
	bl FUN_02084F68
	mov r6, #0x1
_0208495A:
	mov r7, #0x1
_0208495C:
	add r0, r5, #0x0
	mov r1, #0xa0
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x58]
	add r0, r4, #0x0
	mov r1, #0x19
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020849B4
	ldr r0, [sp, #0x58]
	cmp r0, #0x64
	bge _020849B2
	add r0, r5, #0x0
	bl CalcMonExpToNextLevelEncrypted
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x8
	bl AddMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	bne _020849B0
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	add r2, r0, #0x0
	ldr r3, [sp, #0x54]
	ldr r1, [sp, #0x50]
	add r0, r5, #0x0
	sub r3, r2, r3
	str r2, [sp, #0x5c]
	bl FUN_02084F68
_020849B0:
	mov r6, #0x1
_020849B2:
	mov r7, #0x1
_020849B4:
	add r0, r4, #0x0
	mov r1, #0x1a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020849C2
	mov r7, #0x1
_020849C2:
	add r0, r4, #0x0
	mov r1, #0x22
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _020849E2
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	mov r2, #0x1
	bl FUN_02084EC0
	cmp r0, #0x1
	bne _020849DE
	mov r6, #0x1
_020849DE:
	mov r7, #0x1
	b _02084A00
_020849E2:
	add r0, r4, #0x0
	mov r1, #0x23
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084A00
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	mov r2, #0x3
	bl FUN_02084EC0
	cmp r0, #0x1
	bne _020849FE
	mov r6, #0x1
_020849FE:
	mov r7, #0x1
_02084A00:
	add r0, r4, #0x0
	mov r1, #0x24
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084A2C
	add r0, r4, #0x0
	mov r1, #0x37
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r1, [sp, #0x4]
	add r0, r5, #0x0
	bl FUN_02084E40
	cmp r0, #0x1
	bne _02084A24
	mov r6, #0x1
_02084A24:
	mov r7, #0x1
	b _02084A66
	.balign 4
_02084A28: .word 0xFFFFF077
_02084A2C:
	add r0, r4, #0x0
	mov r1, #0x25
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084A66
	mov r0, #0x0
	str r0, [sp, #0x50]
	cmp r0, #0x4
	bge _02084A64
	mov r7, #0x37
_02084A42:
	add r0, r4, #0x0
	add r1, r7, #0x0
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r1, [sp, #0x50]
	add r0, r5, #0x0
	bl FUN_02084E40
	cmp r0, #0x1
	bne _02084A5A
	mov r6, #0x1
_02084A5A:
	ldr r0, [sp, #0x50]
	add r0, r0, #0x1
	str r0, [sp, #0x50]
	cmp r0, #0x4
	blt _02084A42
_02084A64:
	mov r7, #0x1
_02084A66:
	add r0, r5, #0x0
	mov r1, #0xd
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xe
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x54]
	add r0, r5, #0x0
	mov r1, #0xf
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x58]
	add r0, r5, #0x0
	mov r1, #0x10
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x5c]
	add r0, r5, #0x0
	mov r1, #0x11
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x60]
	add r0, r5, #0x0
	mov r1, #0x12
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x64]
	add r0, r5, #0x0
	mov r1, #0x5
	mov r2, #0x0
	bl GetMonData
	mov r1, #0x49
	lsl r1, r1, #0x2
	cmp r0, r1
	beq _02084B20
	add r0, r4, #0x0
	mov r1, #0x27
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084B20
	add r0, r4, #0x0
	mov r1, #0x30
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x54]
	str r1, [sp, #0x10]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0xc]
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x14]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x10]
	ldr r0, [sp, #0x50]
	add r1, r1, r2
	ldr r2, [sp, #0xc]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084B18
	str r0, [sp, #0x50]
	add r0, r5, #0x0
	mov r1, #0xd
	add r2, sp, #0x50
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	mov r6, #0x1
_02084B18:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084B20
	mov r7, #0x1
_02084B20:
	add r0, r4, #0x0
	mov r1, #0x28
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084B80
	add r0, r4, #0x0
	mov r1, #0x31
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x1c]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0x18]
	str r1, [sp, #0x20]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x20]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x1c]
	ldr r0, [sp, #0x54]
	add r1, r1, r2
	ldr r2, [sp, #0x18]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084B78
	str r0, [sp, #0x54]
	add r0, r5, #0x0
	mov r1, #0xe
	add r2, sp, #0x54
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	mov r6, #0x1
_02084B78:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084B80
	mov r7, #0x1
_02084B80:
	add r0, r4, #0x0
	mov r1, #0x29
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084BE0
	add r0, r4, #0x0
	mov r1, #0x32
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x28]
	ldr r1, [sp, #0x5c]
	str r0, [sp, #0x24]
	str r1, [sp, #0x2c]
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x2c]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x58]
	add r1, r1, r2
	ldr r2, [sp, #0x24]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084BD8
	str r0, [sp, #0x58]
	add r0, r5, #0x0
	mov r1, #0xf
	add r2, sp, #0x58
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	mov r6, #0x1
_02084BD8:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084BE0
	mov r7, #0x1
_02084BE0:
	add r0, r4, #0x0
	mov r1, #0x2a
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084C40
	add r0, r4, #0x0
	mov r1, #0x33
	bl FUN_0206E7DC
	ldr r1, [sp, #0x60]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x34]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x30]
	str r1, [sp, #0x38]
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x38]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x34]
	ldr r0, [sp, #0x5c]
	add r1, r1, r2
	ldr r2, [sp, #0x30]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084C38
	str r0, [sp, #0x5c]
	add r0, r5, #0x0
	mov r1, #0x10
	add r2, sp, #0x5c
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	mov r6, #0x1
_02084C38:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084C40
	mov r7, #0x1
_02084C40:
	add r0, r4, #0x0
	mov r1, #0x2b
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084CA0
	add r0, r4, #0x0
	mov r1, #0x34
	bl FUN_0206E7DC
	ldr r1, [sp, #0x5c]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x40]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x3c]
	str r1, [sp, #0x44]
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r2, r2, r1
	ldr r1, [sp, #0x44]
	ldr r3, [sp, #0x64]
	add r2, r1, r2
	ldr r1, [sp, #0x40]
	ldr r0, [sp, #0x60]
	add r1, r1, r2
	ldr r2, [sp, #0x3c]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084C98
	str r0, [sp, #0x60]
	add r0, r5, #0x0
	mov r1, #0x11
	add r2, sp, #0x60
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	mov r6, #0x1
_02084C98:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084CA0
	mov r7, #0x1
_02084CA0:
	add r0, r4, #0x0
	mov r1, #0x2c
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084D00
	add r0, r4, #0x0
	mov r1, #0x35
	bl FUN_0206E7DC
	ldr r1, [sp, #0x5c]
	ldr r2, [sp, #0x50]
	str r1, [sp, #0x4c]
	ldr r1, [sp, #0x58]
	str r0, [sp, #0x48]
	mov r12, r1
	ldr r1, [sp, #0x54]
	str r0, [sp, #0x6c]
	add r1, r2, r1
	mov r2, r12
	add r2, r2, r1
	ldr r1, [sp, #0x4c]
	ldr r3, [sp, #0x60]
	add r1, r1, r2
	ldr r0, [sp, #0x64]
	ldr r2, [sp, #0x48]
	add r1, r3, r1
	bl FUN_02084FA8
	mov r1, #0x0
	mvn r1, r1
	str r0, [sp, #0x68]
	cmp r0, r1
	beq _02084CF8
	str r0, [sp, #0x64]
	add r0, r5, #0x0
	mov r1, #0x12
	add r2, sp, #0x64
	bl SetMonData
	add r0, r5, #0x0
	bl CalcMonLevelAndStats
	mov r6, #0x1
_02084CF8:
	ldr r0, [sp, #0x6c]
	cmp r0, #0x0
	ble _02084D00
	mov r7, #0x1
_02084D00:
	cmp r6, #0x0
	bne _02084D14
	cmp r7, #0x1
	bne _02084D14
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x70
	mov r0, #0x0
	pop {r3-r7, pc}
_02084D14:
	add r0, r5, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x50]
	cmp r0, #0x64
	bge _02084D54
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084DC2
	add r0, r4, #0x0
	mov r1, #0x38
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r0, [sp, #0x88]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x50]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0208508C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x70
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02084D54:
	blt _02084D8A
	cmp r0, #0xc8
	bge _02084D8A
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084DC2
	add r0, r4, #0x0
	mov r1, #0x39
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r0, [sp, #0x88]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x50]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0208508C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x70
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02084D8A:
	cmp r0, #0xc8
	blt _02084DC2
	cmp r0, #0xff
	bgt _02084DC2
	add r0, r4, #0x0
	mov r1, #0x2f
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02084DC2
	add r0, r4, #0x0
	mov r1, #0x3a
	bl FUN_0206E7DC
	add r2, r0, #0x0
	ldr r0, [sp, #0x88]
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x50]
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0208508C
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x70
	add r0, r6, #0x0
	pop {r3-r7, pc}
_02084DC2:
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r6, #0x0
	add sp, #0x70
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02084DD0
FUN_02084DD0: ; 0x02084DD0
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r1, r2, #0x0
	add r4, r3, #0x0
	bl FUN_0206B9B0
	ldr r1, [sp, #0x14]
	add r3, sp, #0x0
	str r1, [sp, #0x0]
	ldrh r3, [r3, #0x10]
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02084810
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02084DF0
FUN_02084DF0: ; 0x02084DF0
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r1, #0x36
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	bne _02084E08
	mov r0, #0x0
	pop {r3-r7, pc}
_02084E08:
	add r1, r6, #0x0
	add r0, r5, #0x0
	add r1, #0x3a
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	add r6, #0x3e
	lsr r4, r0, #0x18
	add r0, r5, #0x0
	add r1, r6, #0x0
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	add r0, r7, #0x0
	bl FUN_0206AB30
	cmp r4, r0
	bhs _02084E36
	mov r0, #0x1
	b _02084E38
_02084E36:
	mov r0, #0x0
_02084E38:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02084E40
FUN_02084E40: ; 0x02084E40
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r1, #0x0
	add r4, r2, #0x0
	add r1, #0x36
	mov r2, #0x0
	add r6, r0, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r7, r0, #0x10
	bne _02084E5E
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r7, pc}
_02084E5E:
	add r0, r5, #0x0
	str r0, [sp, #0x0]
	add r0, #0x3a
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	mov r2, #0x0
	bl GetMonData
	add r1, sp, #0x4
	strb r0, [r1, #0x0]
	add r5, #0x3e
	add r0, r6, #0x0
	add r1, r5, #0x0
	mov r2, #0x0
	bl GetMonData
	add r1, r0, #0x0
	lsl r1, r1, #0x18
	add r0, r7, #0x0
	lsr r1, r1, #0x18
	bl FUN_0206AB30
	add r1, sp, #0x4
	ldrb r2, [r1, #0x0]
	cmp r2, r0
	bhs _02084EB8
	cmp r4, #0x7f
	bne _02084E9C
	strb r0, [r1, #0x0]
	b _02084EA8
_02084E9C:
	add r2, r2, r4
	strb r2, [r1, #0x0]
	ldrb r2, [r1, #0x0]
	cmp r2, r0
	bls _02084EA8
	strb r0, [r1, #0x0]
_02084EA8:
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	add r2, sp, #0x4
	bl SetMonData
	add sp, #0x8
	mov r0, #0x1
	pop {r3-r7, pc}
_02084EB8:
	mov r0, #0x0
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02084EC0
FUN_02084EC0: ; 0x02084EC0
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r2, #0x0
	add r4, r1, #0x0
	str r1, [sp, #0x0]
	add r1, #0x3e
	mov r2, #0x0
	add r5, r0, #0x0
	str r1, [sp, #0x0]
	bl GetMonData
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	ldrb r0, [r1, #0x0]
	cmp r0, #0x3
	bne _02084EE6
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02084EE6:
	add r1, r4, #0x0
	add r0, r5, #0x0
	add r1, #0x36
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r1, #0x0
	str r0, [sp, #0x4]
	bl FUN_0206AB30
	cmp r0, #0x5
	bhs _02084F08
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02084F08:
	add r4, #0x3a
	add r0, r5, #0x0
	add r1, r4, #0x0
	mov r2, #0x0
	bl GetMonData
	add r1, sp, #0x8
	strb r0, [r1, #0x1]
	ldrb r1, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_0206AB30
	add r7, r0, #0x0
	add r0, sp, #0x8
	ldrb r0, [r0, #0x0]
	add r0, r0, r6
	cmp r0, #0x3
	bls _02084F30
	mov r0, #0x3
	b _02084F34
_02084F30:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
_02084F34:
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	ldrb r1, [r1, #0x0]
	ldr r0, [sp, #0x4]
	bl FUN_0206AB30
	add r1, sp, #0x8
	ldrb r2, [r1, #0x1]
	add r0, r2, r0
	sub r0, r0, r7
	strb r0, [r1, #0x1]
	ldr r1, [sp, #0x0]
	add r0, r5, #0x0
	add r2, sp, #0x8
	bl SetMonData
	add r2, sp, #0x8
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, #0x1
	bl SetMonData
	mov r0, #0x1
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_02084F68
FUN_02084F68: ; 0x02084F68
	push {r0-r3}
	push {r3, lr}
	cmp r2, #0x1
	bne _02084F74
	mov r3, #0x1
	b _02084F8A
_02084F74:
	cmp r3, #0xff
	bne _02084F7C
	add r3, r2, #0x0
	b _02084F8A
_02084F7C:
	cmp r3, #0xfe
	bne _02084F84
	lsr r3, r2, #0x1
	b _02084F8A
_02084F84:
	cmp r3, #0xfd
	bne _02084F8A
	lsr r3, r2, #0x2
_02084F8A:
	ldr r1, [sp, #0xc]
	add r1, r1, r3
	cmp r1, r2
	bls _02084F96
	str r2, [sp, #0xc]
	b _02084F98
_02084F96:
	str r1, [sp, #0xc]
_02084F98:
	mov r1, #0xa2
	add r2, sp, #0xc
	bl SetMonData
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_02084FA8
FUN_02084FA8: ; 0x02084FA8
	push {r3-r4}
	cmp r0, #0x0
	bne _02084FBA
	cmp r2, #0x0
	bge _02084FBA
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
_02084FBA:
	cmp r0, #0x64
	blt _02084FCA
	cmp r2, #0x0
	ble _02084FCA
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
_02084FCA:
	ldr r3, _02084FFC ; =0x000001FE
	add r4, r0, r1
	cmp r4, r3
	blt _02084FDE
	cmp r2, #0x0
	ble _02084FDE
	mov r0, #0x0
	mvn r0, r0
	pop {r3-r4}
	bx lr
_02084FDE:
	add r0, r0, r2
	cmp r0, #0x64
	ble _02084FE8
	mov r0, #0x64
	b _02084FEE
_02084FE8:
	cmp r0, #0x0
	bge _02084FEE
	mov r0, #0x0
_02084FEE:
	ldr r2, _02084FFC ; =0x000001FE
	add r3, r0, r1
	cmp r3, r2
	ble _02084FF8
	sub r0, r2, r1
_02084FF8:
	pop {r3-r4}
	bx lr
	.balign 4
_02084FFC: .word 0x000001FE

	thumb_func_start FUN_02085000
FUN_02085000: ; 0x02085000
	push {r4, lr}
	add r4, r1, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0xff
	blt _02085014
	mov r0, #0x0
	pop {r4, pc}
_02085014:
	cmp r0, #0x64
	bge _02085038
	add r0, r4, #0x0
	mov r1, #0x2d
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02085034
	add r0, r4, #0x0
	mov r1, #0x38
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02085034
	mov r0, #0x1
	pop {r4, pc}
_02085034:
	mov r0, #0x0
	pop {r4, pc}
_02085038:
	blt _0208505E
	cmp r0, #0xc8
	bge _0208505E
	add r0, r4, #0x0
	mov r1, #0x2e
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _0208505A
	add r0, r4, #0x0
	mov r1, #0x39
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _0208505A
	mov r0, #0x1
	pop {r4, pc}
_0208505A:
	mov r0, #0x0
	pop {r4, pc}
_0208505E:
	cmp r0, #0xc8
	blt _02085086
	cmp r0, #0xff
	bge _02085086
	add r0, r4, #0x0
	mov r1, #0x2f
	bl FUN_0206E7DC
	cmp r0, #0x0
	beq _02085082
	add r0, r4, #0x0
	mov r1, #0x3a
	bl FUN_0206E7DC
	cmp r0, #0x0
	ble _02085082
	mov r0, #0x1
	pop {r4, pc}
_02085082:
	mov r0, #0x0
	pop {r4, pc}
_02085086:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0208508C
FUN_0208508C: ; 0x0208508C
	push {r0-r3}
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r3, #0x0
	cmp r4, #0xff
	bne _020850AA
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	ble _020850AA
	mov r0, #0x0
	pop {r4-r6}
	pop {r3}
	add sp, #0x10
	bx r3
_020850AA:
	cmp r4, #0x0
	bne _020850BE
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bge _020850BE
	mov r0, #0x0
	pop {r4-r6}
	pop {r3}
	add sp, #0x10
	bx r3
_020850BE:
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	ble _02085114
	add r0, r5, #0x0
	mov r1, #0x6
	mov r2, #0x0
	bl GetMonData
	lsl r0, r0, #0x10
	ldr r2, [sp, #0x20]
	lsr r0, r0, #0x10
	mov r1, #0x1
	bl FUN_0206E7B8
	cmp r0, #0x34
	bne _020850EC
	ldr r1, [sp, #0x18]
	mov r0, #0x96
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	str r0, [sp, #0x18]
_020850EC:
	add r0, r5, #0x0
	mov r1, #0x9a
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0xb
	bne _02085100
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
_02085100:
	add r0, r5, #0x0
	mov r1, #0x97
	mov r2, #0x0
	bl GetMonData
	cmp r6, r0
	bne _02085114
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
_02085114:
	ldr r0, [sp, #0x18]
	add r0, r0, r4
	str r0, [sp, #0x18]
	cmp r0, #0xff
	ble _02085122
	mov r0, #0xff
	str r0, [sp, #0x18]
_02085122:
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	bge _0208512C
	mov r0, #0x0
	str r0, [sp, #0x18]
_0208512C:
	add r0, r5, #0x0
	mov r1, #0x9
	add r2, sp, #0x18
	bl SetMonData
	mov r0, #0x1
	pop {r4-r6}
	pop {r3}
	add sp, #0x10
	bx r3

	thumb_func_start FUN_02085140
FUN_02085140: ; 0x02085140
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	bl FUN_0206B9AC
	mov r7, #0x0
	str r0, [sp, #0x4]
	cmp r0, #0x0
	ble _020851B4
	mov r6, #0x7f
_02085154:
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	bl FUN_0206B9B0
	mov r1, #0xab
	mov r2, #0x0
	add r5, r0, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _020851AC
	add r0, r5, #0x0
	mov r1, #0xa3
	mov r2, #0x0
	bl GetMonData
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0xa2
	add r2, sp, #0x8
	bl SetMonData
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x9f
	add r2, sp, #0x8
	bl SetMonData
	mov r4, #0x0
_02085190:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02084DF0
	cmp r0, #0x1
	bne _020851A6
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02084E40
_020851A6:
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _02085190
_020851AC:
	ldr r0, [sp, #0x4]
	add r7, r7, #0x1
	cmp r7, r0
	blt _02085154
_020851B4:
	add sp, #0xc
	pop {r4-r7, pc}
