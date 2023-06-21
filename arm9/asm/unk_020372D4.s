	.include "asm/macros.inc"
	.include "global.inc"

	.extern gSystem

	.section .bss

	.global UNK_021C5A08
UNK_021C5A08: ; 0x021C5A08
	.space 0x4

	.text

	thumb_func_start sub_020372D4
sub_020372D4: ; 0x020372D4
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl OverlayManager_GetField18
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl sub_02037400
	ldr r1, _02037300 ; =UNK_021C5A08
	str r0, [r1, #0x0]
	ldr r1, [r4, #0x4]
	cmp r1, #0x0
	beq _020372F4
	bl sub_02048FC8
	b _020372F8
_020372F4:
	bl sub_02048EC8
_020372F8:
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4
_02037300: .word UNK_021C5A08

	thumb_func_start sub_02037304
sub_02037304: ; 0x02037304
	push {r3, lr}
	bl sub_02037400
	ldr r1, _02037318 ; =UNK_021C5A08
	str r0, [r1, #0x0]
	bl sub_02048D90
	mov r0, #0x1
	pop {r3, pc}
	nop
_02037318: .word UNK_021C5A08

	thumb_func_start sub_0203731C
sub_0203731C: ; 0x0203731C
	push {r3, lr}
	bl OverlayManager_GetData
	bl sub_02037524
	cmp r0, #0x0
	beq _0203732E
	mov r0, #0x1
	pop {r3, pc}
_0203732E:
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start sub_02037334
sub_02037334: ; 0x02037334
	push {r3, lr}
	bl sub_020374B0
	ldr r0, _02037348 ; =SDK_OVERLAY_MODULE_63_ID
	ldr r1, _0203734C ; =MOD63_021DBAB8
	bl RegisterMainOverlay
	mov r0, #0x1
	pop {r3, pc}
	nop
_02037348: .word SDK_OVERLAY_MODULE_63_ID
_0203734C: .word MOD63_021DBAB8

	thumb_func_start LoadOverlay_MODULE_05
LoadOverlay_MODULE_05: ; 0x02037350
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _02037360
	bl GF_AssertFail
_02037360:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0203736C
	bl GF_AssertFail
_0203736C:
	ldr r0, _0203738C ; =SDK_OVERLAY_MODULE_05_ID
	mov r1, #0x2
	bl HandleLoadOverlay
	mov r1, #0x0
	str r1, [r4, #0x64]
	ldr r0, [r4, #0x0]
	mov r2, #0xb
	str r1, [r0, #0x8]
	ldr r0, _02037390 ; =UNK05_021F64C8
	add r1, r4, #0x0
	bl OverlayManager_New
	ldr r1, [r4, #0x0]
	str r0, [r1, #0x0]
	pop {r4, pc}
	.balign 4
_0203738C: .word SDK_OVERLAY_MODULE_05_ID
_02037390: .word UNK05_021F64C8

	thumb_func_start sub_02037394
sub_02037394: ; 0x02037394
	mov r1, #0x0
	str r1, [r0, #0x64]
	bx lr
	.balign 4

	thumb_func_start sub_0203739C
sub_0203739C: ; 0x0203739C
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020373A8
	mov r0, #0x1
	bx lr
_020373A8:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020373AC
sub_020373AC: ; 0x020373AC
	ldr r1, [r0, #0x0]
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020373BE
	ldr r0, [r0, #0x64]
	cmp r0, #0x0
	beq _020373BE
	mov r0, #0x1
	bx lr
_020373BE:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start sub_020373C4
sub_020373C4: ; 0x020373C4
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	beq _020373D0
	mov r0, #0x1
	bx lr
_020373D0:
	mov r0, #0x0
	bx lr

	thumb_func_start sub_020373D4
sub_020373D4: ; 0x020373D4
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	add r4, r1, #0x0
	ldr r0, [r0, #0x4]
	add r6, r2, #0x0
	cmp r0, #0x0
	beq _020373E8
	bl GF_AssertFail
_020373E8:
	add r0, r5, #0x0
	bl sub_02037394
	add r0, r4, #0x0
	add r1, r6, #0x0
	mov r2, #0xb
	bl OverlayManager_New
	ldr r1, [r5, #0x0]
	str r0, [r1, #0x4]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_02037400
sub_02037400: ; 0x02037400
	push {r3-r5, lr}
	mov r2, #0x7
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0xb
	lsl r2, r2, #0xe
	bl CreateHeap
	mov r1, #0x20
	mov r0, #0x3
	lsl r2, r1, #0x9
	bl CreateHeap
	mov r2, #0x3
	mov r0, #0x0
	mov r1, #0x5b
	lsl r2, r2, #0x8
	bl CreateHeap
	add r0, r5, #0x0
	mov r1, #0xb8
	mov r2, #0xb
	bl OverlayManager_CreateAndGetData
	mov r1, #0x0
	mov r2, #0xb8
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0xb
	mov r1, #0x10
	bl AllocFromHeap
	str r0, [r4, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x4]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0x8]
	ldr r0, [r4, #0x0]
	str r1, [r0, #0xc]
	add r0, r5, #0x0
	bl OverlayManager_GetField18
	ldr r0, [r0, #0x8]
	str r0, [r4, #0xc]
	mov r0, #0x0
	str r0, [r4, #0x10]
	ldr r0, [r4, #0xc]
	bl Save_LocalFieldData_Get
	bl sub_02034DC0
	str r0, [r4, #0x1c]
	bl MapMatrix_New
	str r0, [r4, #0x28]
	add r0, r4, #0x0
	mov r1, #0xb
	bl sub_02034A28
	mov r0, #0xb
	bl sub_0206F164
	add r1, r4, #0x0
	add r1, #0x94
	str r0, [r1, #0x0]
	mov r0, #0xb
	bl sub_0205DD18
	add r1, r4, #0x0
	add r1, #0x90
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl sub_0205DD40
	mov r0, #0xb
	bl sub_0208A300
	add r1, r4, #0x0
	add r1, #0xb0
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start sub_020374B0
sub_020374B0: ; 0x020374B0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl OverlayManager_GetData
	add r4, r0, #0x0
	ldr r0, [r4, #0x28]
	bl MapMatrix_Free
	add r0, r4, #0x0
	bl sub_02034A48
	add r0, r4, #0x0
	add r0, #0x94
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	add r0, #0x90
	ldr r0, [r0, #0x0]
	bl sub_0205DD38
	add r0, r4, #0x0
	add r0, #0xb0
	ldr r0, [r0, #0x0]
	bl sub_0208A320
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	add r0, r5, #0x0
	bl OverlayManager_FreeData
	mov r0, #0x5b
	bl DestroyHeap
	mov r0, #0xb
	bl DestroyHeap
	mov r0, #0x20
	bl DestroyHeap
	pop {r3-r5, pc}

	thumb_func_start sub_02037504
sub_02037504: ; 0x02037504
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02037520
	bl OverlayManager_Run
	cmp r0, #0x0
	beq _02037520
	ldr r0, [r4, #0x0]
	bl OverlayManager_Delete
	mov r0, #0x0
	str r0, [r4, #0x0]
_02037520:
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02037524
sub_02037524: ; 0x02037524
	push {r4, lr}
	add r4, r0, #0x0
	bl sub_02037594
	add r0, r4, #0x0
	bl sub_02046420
	cmp r0, #0x1
	bne _02037546
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _02037546
	mov r1, #0x0
	add r0, r4, #0x0
	add r2, r1, #0x0
	bl MOD05_021EFA9C
_02037546:
	ldr r0, [r4, #0x0]
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02037562
	bl sub_02037504
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0203756E
	ldr r0, _02037590 ; =SDK_OVERLAY_MODULE_05_ID
	bl UnloadOverlayByID
	b _0203756E
_02037562:
	ldr r1, [r0, #0x4]
	cmp r1, #0x0
	beq _0203756E
	add r0, r0, #0x4
	bl sub_02037504
_0203756E:
	ldr r1, [r4, #0x0]
	ldr r0, [r1, #0xc]
	cmp r0, #0x0
	beq _0203758C
	ldr r0, [r4, #0x10]
	cmp r0, #0x0
	bne _0203758C
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0203758C
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	bne _0203758C
	mov r0, #0x1
	pop {r4, pc}
_0203758C:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_02037590: .word SDK_OVERLAY_MODULE_05_ID

	thumb_func_start sub_02037594
sub_02037594: ; 0x02037594
	push {r3-r5, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	mov r5, #0x0
	ldr r1, [r1, #0x8]
	cmp r1, #0x0
	bne _020375B4
	ldr r1, [r4, #0x64]
	cmp r1, #0x0
	beq _020375B4
	bl sub_0204646C
	cmp r0, #0x0
	bne _020375B4
	mov r5, #0x1
_020375B4:
	cmp r5, #0x0
	beq _020375D4
	ldr r0, [r4, #0x38]
	bl sub_02055A38
	ldr r3, _02037758 ; =gSystem
	add r0, sp, #0x8
	ldr r2, [r3, #0x48]
	ldr r3, [r3, #0x44]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	add r1, r4, #0x0
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl MOD05_021D8164
_020375D4:
	ldr r0, [r4, #0x1c]
	ldr r2, [r4, #0x6c]
	ldr r1, [r0, #0x0]
	ldr r0, _0203775C ; =0x00000146
	cmp r1, r0
	bne _020375E2
	mov r2, #0x0
_020375E2:
	cmp r2, #0x4
	bhi _020376E2
	add r0, r2, r2
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020375F2: ; jump table (using 16-bit offset)
	.short _020376E2 - _020375F2 - 2; case 0
	.short _020375FC - _020375F2 - 2; case 1
	.short _02037646 - _020375F2 - 2; case 2
	.short _0203761C - _020375F2 - 2; case 3
	.short _02037672 - _020375F2 - 2; case 4
_020375FC:
	cmp r5, #0x0
	beq _02037610
	bl sub_0204E2FC
	cmp r0, #0x0
	beq _02037610
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D85FC
_02037610:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_0204D6C0
	add sp, #0x10
	pop {r3-r5, pc}
_0203761C:
	cmp r5, #0x0
	beq _0203763A
	bl sub_0204E2FC
	cmp r0, #0x0
	beq _02037638
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD04_021D865C
	cmp r0, #0x1
	bne _0203763A
	mov r5, #0x0
	b _0203763A
_02037638:
	mov r5, #0x0
_0203763A:
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl sub_0204D6C0
	add sp, #0x10
	pop {r3-r5, pc}
_02037646:
	cmp r5, #0x0
	bne _0203764C
	b _02037754
_0203764C:
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D8758
	cmp r0, #0x1
	beq _02037754
	add r3, sp, #0x8
	ldrh r0, [r3, #0x6]
	mov r2, #0x0
	str r0, [sp, #0x0]
	str r2, [sp, #0x4]
	ldrh r3, [r3, #0x4]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x24]
	sub r2, r2, #0x1
	bl sub_020557F4
	add sp, #0x10
	pop {r3-r5, pc}
_02037672:
	cmp r5, #0x0
	beq _02037754
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D8820
	cmp r0, #0x1
	bne _020376A6
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
	add r0, r4, #0x0
	mov r1, #0x4
	bl MOD05_021E81BC
	ldr r0, [r4, #0x38]
	bl MOD05_021E7138
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl MOD05_021EFA9C
	add sp, #0x10
	pop {r3-r5, pc}
_020376A6:
	ldr r0, _02037758 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _020376B8
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
_020376B8:
	mov r5, #0x0
	bl sub_02037790
	cmp r0, #0x0
	beq _020376C8
	bl MOD20_02252534
	add r5, r0, #0x0
_020376C8:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x6]
	mov r2, #0x0
	mvn r2, r2
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x4]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x24]
	bl sub_020557F4
	add sp, #0x10
	pop {r3-r5, pc}
_020376E2:
	cmp r5, #0x0
	beq _02037754
	add r0, sp, #0x8
	add r1, r4, #0x0
	bl MOD05_021D8320
	cmp r0, #0x1
	bne _0203771C
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
	add r0, r4, #0x0
	mov r1, #0x4
	bl MOD05_021E81BC
	ldr r0, [r4, #0x38]
	bl sub_02055B14
	ldr r0, [r4, #0x38]
	bl MOD05_021E7138
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl MOD05_021EFA9C
	add sp, #0x10
	pop {r3-r5, pc}
_0203771C:
	ldr r0, _02037758 ; =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _0203772E
	ldr r0, [r4, #0x4]
	ldr r0, [r0, #0x8]
	bl MOD05_021E32F0
_0203772E:
	mov r5, #0x0
	bl sub_02037790
	cmp r0, #0x0
	beq _0203773E
	bl MOD20_02252534
	add r5, r0, #0x0
_0203773E:
	add r3, sp, #0x8
	ldrh r0, [r3, #0x6]
	mov r2, #0x0
	mvn r2, r2
	str r0, [sp, #0x0]
	str r5, [sp, #0x4]
	ldrh r3, [r3, #0x4]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x24]
	bl sub_020557F4
_02037754:
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_02037758: .word gSystem
_0203775C: .word 0x00000146

	thumb_func_start sub_02037760
sub_02037760: ; 0x02037760
	ldr r0, _02037770 ; =UNK_021C5A08
	ldr r3, _02037774 ; =sub_02030FC8
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x8]
	bx r3
	nop
_02037770: .word UNK_021C5A08
_02037774: .word sub_02030FC8

	thumb_func_start sub_02037778
sub_02037778: ; 0x02037778
	ldr r0, _02037788 ; =UNK_021C5A08
	ldr r3, _0203778C ; =sub_02030FA8
	ldr r0, [r0, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x8]
	bx r3
	nop
_02037788: .word UNK_021C5A08
_0203778C: .word sub_02030FA8

	thumb_func_start sub_02037790
sub_02037790: ; 0x02037790
	ldr r0, _020377A4 ; =UNK_021C5A08
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _0203779E
	mov r0, #0x0
	bx lr
_0203779E:
	ldr r0, [r0, #0x14]
	bx lr
	nop
_020377A4: .word UNK_021C5A08

	thumb_func_start sub_020377A8
sub_020377A8: ; 0x020377A8
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start ScriptEnvironment_GetSavePtr
ScriptEnvironment_GetSavePtr: ; 0x020377AC
	ldr r0, [r0, #0xc]
	bx lr
