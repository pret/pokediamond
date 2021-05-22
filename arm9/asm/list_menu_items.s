    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ListMenuItems_ctor
ListMenuItems_ctor: ; 0x02012838
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r1, r5, #0x1
	add r0, r4, #0x0
	lsl r1, r1, #0x3
	bl AllocFromHeap
	cmp r0, #0x0
	beq _0201286E
	mov r2, #0x0
	cmp r5, #0x0
	bls _02012862
	add r3, r0, #0x0
	add r1, r2, #0x0
_02012856:
	str r1, [r3, #0x0]
	str r1, [r3, #0x4]
	add r2, r2, #0x1
	add r3, #0x8
	cmp r2, r5
	blo _02012856
_02012862:
	mov r1, #0x0
	lsl r2, r2, #0x3
	mvn r1, r1
	str r1, [r0, r2]
	add r1, r0, r2
	str r4, [r1, #0x4]
_0201286E:
	pop {r3-r5, pc}

	thumb_func_start ListMenuItems_dtor
ListMenuItems_dtor: ; 0x02012870
	push {r4, lr}
	add r4, r0, #0x0
	bl ListMenuItems_DestroyMenuStrings
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start ListMenuItems_AppendFromMsgData
ListMenuItems_AppendFromMsgData: ; 0x02012880
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r1, sp, #0x0
	add r7, r2, #0x0
	add r5, r3, #0x0
	bl ListMenuItems_NewItem
	add r4, r0, #0x0
	beq _0201289E
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl NewString_ReadMsgData
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
_0201289E:
	pop {r3-r7, pc}

	thumb_func_start ListMenuItems_AddItem
ListMenuItems_AddItem: ; 0x020128A0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r1, #0x0
	add r1, sp, #0x0
	add r5, r2, #0x0
	bl ListMenuItems_NewItem
	add r4, r0, #0x0
	beq _020128BE
	ldr r1, [sp, #0x0]
	add r0, r6, #0x0
	bl StringDup
	str r0, [r4, #0x0]
	str r5, [r4, #0x4]
_020128BE:
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start ListMenuItems_CopyItem
ListMenuItems_CopyItem: ; 0x020128C4
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r1, #0x0
	add r1, sp, #0x0
	bl ListMenuItems_NewItem
	cmp r0, #0x0
	beq _020128DC
	ldr r1, [r4, #0x0]
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x4]
	str r1, [r0, #0x4]
_020128DC:
	add sp, #0x4
	pop {r3-r4, pc}

	thumb_func_start ListMenuItems_NewItem
ListMenuItems_NewItem: ; 0x020128E0
	push {r4, lr}
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _02012900
	mov r2, #0x0
	mvn r2, r2
_020128EC:
	cmp r3, r2
	bne _020128F8
	bl ErrorHandling
	mov r0, #0x0
	pop {r4, pc}
_020128F8:
	add r0, #0x8
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	bne _020128EC
_02012900:
	mov r2, #0x0
	mvn r2, r2
	add r4, r0, #0x0
	cmp r3, r2
	beq _02012912
_0201290A:
	add r0, #0x8
	ldr r3, [r0, #0x0]
	cmp r3, r2
	bne _0201290A
_02012912:
	ldr r0, [r0, #0x4]
	str r0, [r1, #0x0]
	add r0, r4, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start ListMenuItems_DestroyMenuStrings
ListMenuItems_DestroyMenuStrings: ; 0x0201291C
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	ldr r1, [r5, #0x0]
	mvn r0, r0
	cmp r1, r0
	beq _02012942
	mov r4, #0x0
	add r6, r0, #0x0
_0201292E:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02012942
	bl String_dtor
	str r4, [r5, #0x0]
	add r5, #0x8
	ldr r0, [r5, #0x0]
	cmp r0, r6
	bne _0201292E
_02012942:
	pop {r4-r6, pc}
