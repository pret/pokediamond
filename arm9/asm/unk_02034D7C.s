	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02034D7C
sub_02034D7C: ; 0x02034D7C
	mov r0, #0xa0
	bx lr

	thumb_func_start sub_02034D80
sub_02034D80: ; 0x02034D80
	mov r0, #0x5
	lsl r0, r0, #0xa
	bx lr
	.balign 4

	thumb_func_start sub_02034D88
sub_02034D88: ; 0x02034D88
	ldr r3, _02034D94 ; =MIi_CpuClear32
	mov r2, #0x5
	add r1, r0, #0x0
	mov r0, #0x0
	lsl r2, r2, #0xa
	bx r3
	.balign 4
_02034D94: .word MIi_CpuClear32

	thumb_func_start sub_02034D98
sub_02034D98: ; 0x02034D98
	push {r4, lr}
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0xa0
	bl memset
	add r0, r4, #0x0
	add r0, #0x6c
	bl sub_0204ADE0
	add r0, r4, #0x0
	add r0, #0x8c
	bl PlayerSaveData_Init
	bl GetMomSpawnId
	add r4, #0x68
	strh r0, [r4, #0x0]
	pop {r4, pc}
	.balign 4

	thumb_func_start sub_02034DC0
sub_02034DC0: ; 0x02034DC0
	bx lr
	.balign 4

	thumb_func_start sub_02034DC4
sub_02034DC4: ; 0x02034DC4
	add r0, #0x14
	bx lr

	thumb_func_start sub_02034DC8
sub_02034DC8: ; 0x02034DC8
	add r0, #0x28
	bx lr

	thumb_func_start LocalFieldData_GetSpecialSpawnWarpPtr
LocalFieldData_GetSpecialSpawnWarpPtr: ; 0x02034DCC
	add r0, #0x50
	bx lr

	thumb_func_start LocalFieldData_GetDynamicWarp
LocalFieldData_GetDynamicWarp: ; 0x02034DD0
	add r0, #0x3c
	bx lr

	thumb_func_start LocalFieldData_SetDynamicWarp
LocalFieldData_SetDynamicWarp: ; 0x02034DD4
	add r3, r1, #0x0
	add r2, r0, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x3c
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start sub_02034DE8
sub_02034DE8: ; 0x02034DE8
	add r0, #0x64
	bx lr

	thumb_func_start LocalFieldData_GetWeatherType
LocalFieldData_GetWeatherType: ; 0x02034DEC
	add r0, #0x66
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start LocalFieldData_SetWeatherType
LocalFieldData_SetWeatherType: ; 0x02034DF4
	add r0, #0x66
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start LocalFieldData_GetBlackoutSpawn
LocalFieldData_GetBlackoutSpawn: ; 0x02034DFC
	add r0, #0x68
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start LocalFieldData_SetBlackoutSpawn
LocalFieldData_SetBlackoutSpawn: ; 0x02034E04
	add r0, #0x68
	strh r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02034E0C
sub_02034E0C: ; 0x02034E0C
	add r0, #0x6c
	bx lr

	thumb_func_start sub_02034E10
sub_02034E10: ; 0x02034E10
	add r0, #0x6a
	ldrb r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02034E18
sub_02034E18: ; 0x02034E18
	add r0, #0x6a
	strb r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start sub_02034E20
sub_02034E20: ; 0x02034E20
	add r0, #0x8c
	bx lr

	thumb_func_start LocalFieldData_GetSafariBallsCounter
LocalFieldData_GetSafariBallsCounter: ; 0x02034E24
	add r0, #0x98
	bx lr

	thumb_func_start LocalFieldData_GetSafariStepsCounter
LocalFieldData_GetSafariStepsCounter: ; 0x02034E28
	add r0, #0x96
	bx lr

	thumb_func_start sub_02034E2C
sub_02034E2C: ; 0x02034E2C
	add r0, #0x94
	bx lr

	thumb_func_start Save_LocalFieldData_Get
Save_LocalFieldData_Get: ; 0x02034E30
	ldr r3, _02034E38 ; =SaveArray_Get
	mov r1, #0x6
	bx r3
	nop
_02034E38: .word SaveArray_Get

	thumb_func_start Save_MapObjects_Get
Save_MapObjects_Get: ; 0x02034E3C
	ldr r3, _02034E44 ; =SaveArray_Get
	mov r1, #0xb
	bx r3
	nop
_02034E44: .word SaveArray_Get

	thumb_func_start FieldSystem_SyncMapObjectsToSave
FieldSystem_SyncMapObjectsToSave: ; 0x02034E48
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl Save_MapObjects_Get
	add r2, r0, #0x0
	ldr r1, [r4, #0x34]
	add r0, r4, #0x0
	mov r3, #0x40
	bl FieldSystem_SyncMapObjectsToSaveEx
	pop {r4, pc}

	thumb_func_start sub_02034E60
sub_02034E60: ; 0x02034E60
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0xc]
	bl Save_MapObjects_Get
	add r1, r0, #0x0
	ldr r0, [r4, #0x34]
	mov r2, #0x40
	bl MapObjectManager_RestoreFromSave
	pop {r4, pc}
	.balign 4
