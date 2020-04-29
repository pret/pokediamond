    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start G3B_End
G3B_End: ; 0x020C75AC
	ldr r1, [r0, #0x0]
	mov r2, #0x41
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_Begin
G3B_Begin: ; 0x020C75D0
	ldr r2, [r0, #0x0]
	mov r3, #0x40
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_LightColor
G3B_LightColor: ; 0x020C7600
	ldr r3, [r0, #0x0]
	mov r12, #0x33
	str r12, [r3, #0x0]
	ldr r3, [r0, #0x4]
	orr r1, r2, r1, lsl #0x1e
	str r1, [r3, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_LightVector
G3B_LightVector: ; 0x020C7634
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr ip, _020C7694 ; =0x000003FF
	ldrsh r4, [sp, #0x10]
	ldr lr, [r0, #0x0]
	mov r5, #0x32
	str r5, [lr, #0x0]
	and lr, r12, r2, asr #0x3
	and r2, r12, r3, asr #0x3
	and r3, r12, r4, asr #0x3
	orr r2, lr, r2, lsl #0xa
	orr r3, r2, r3, lsl #0x14
	ldr r2, [r0, #0x4]
	orr r1, r3, r1, lsl #0x1e
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C7694: .word 0x000003FF

	arm_func_start G3B_MaterialColorSpecEmi
G3B_MaterialColorSpecEmi: ; 0x020C7698
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	mov lr, #0x31
	cmp r3, #0x0
	movne r3, #0x1
	str lr, [r12, #0x0]
	orr r2, r1, r2, lsl #0x10
	moveq r3, #0x0
	ldr r1, [r0, #0x4]
	orr r2, r2, r3, lsl #0xf
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G3B_MaterialColorDiffAmb
G3B_MaterialColorDiffAmb: ; 0x020C76EC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	mov lr, #0x30
	cmp r3, #0x0
	movne r3, #0x1
	str lr, [r12, #0x0]
	orr r2, r1, r2, lsl #0x10
	moveq r3, #0x0
	ldr r1, [r0, #0x4]
	orr r2, r2, r3, lsl #0xf
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G3B_PolygonAttr
G3B_PolygonAttr: ; 0x020C7740
	orr r1, r1, r2, lsl #0x4
	ldr r2, [r0, #0x0]
	mov r12, #0x29
	str r12, [r2, #0x0]
	ldr r2, [sp, #0x8]
	orr r1, r1, r3, lsl #0x6
	ldr r3, [sp, #0x0]
	orr r1, r2, r1
	ldr r12, [sp, #0x4]
	orr r2, r1, r3, lsl #0x18
	ldr r1, [r0, #0x4]
	orr r2, r2, r12, lsl #0x10
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_Vtx
G3B_Vtx: ; 0x020C7790
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x0]
	mov lr, #0x23
	str lr, [r12, #0x0]
	mov r1, r1, lsl #0x10
	mov r2, r2, lsl #0x10
	mov lr, r1, lsr #0x10
	mov r12, r2, lsr #0x10
	mov r1, r3, lsl #0x10
	ldr r2, [r0, #0x4]
	orr r3, lr, r12, lsl #0x10
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	mov r1, r1, lsr #0x10
	str r1, [r2, #0x4]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x8
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start G3B_Normal
G3B_Normal: ; 0x020C77F4
	stmdb sp!, {r4,lr}
	ldr ip, _020C7844 ; =0x000003FF
	ldr lr, [r0, #0x0]
	mov r4, #0x21
	str r4, [lr, #0x0]
	and lr, r12, r1, asr #0x3
	and r1, r12, r2, asr #0x3
	and r3, r12, r3, asr #0x3
	orr r2, lr, r1, lsl #0xa
	ldr r1, [r0, #0x4]
	orr r2, r2, r3, lsl #0x14
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C7844: .word 0x000003FF

	arm_func_start G3B_Color
G3B_Color: ; 0x020C7848
	ldr r2, [r0, #0x0]
	mov r3, #0x20
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_LoadMtx44
G3B_LoadMtx44: ; 0x020C7878
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl G3BS_LoadMtx44
	ldr r0, [r4, #0x4]
	add r0, r0, #0x40
	str r0, [r4, #0x0]
	ldr r0, [r4, #0x0]
	add r0, r0, #0x4
	str r0, [r4, #0x4]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start G3B_PopMtx
G3B_PopMtx: ; 0x020C78A4
	ldr r2, [r0, #0x0]
	mov r3, #0x12
	str r3, [r2, #0x0]
	ldr r2, [r0, #0x4]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3B_PushMtx
G3B_PushMtx: ; 0x020C78D4
	ldr r1, [r0, #0x0]
	mov r2, #0x11
	str r2, [r1, #0x0]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x0]
	add r1, r1, #0x4
	str r1, [r0, #0x4]
	bx lr

	arm_func_start G3BS_LoadMtx44
G3BS_LoadMtx44: ; 0x020C78F8
	mov r3, r0
	ldr r0, [r3, #0x0]
	mov r2, #0x16
	str r2, [r0, #0x0]
	mov r0, r1
	ldr ip, _020C7918 ; =MI_Copy64B
	ldr r1, [r3, #0x4]
	bx r12
	.balign 4
_020C7918: .word MI_Copy64B
