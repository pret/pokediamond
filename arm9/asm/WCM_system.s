	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global WCM_Bssid_Any
WCM_Bssid_Any: ; 0x020FF590
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00

	.global WCM_Essid_Any
WCM_Essid_Any: ; 0x020FF598
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

	.bss

	.global wcmw
wcmw: ; 0x021CA86C
	.space 0x4

	.text

	arm_func_start WcmCountBits
WcmCountBits: ; 0x020A5A4C
	mov r1, r0
	mov r0, #0x0
	mov r3, #0x1
_020A5A58:
	clz r2, r1
	rsbs r2, r2, #0x1f
	bxcc lr
	bic r1, r1, r3, lsl r2
	add r0, r0, #0x1
	b _020A5A58

	arm_func_start WcmCountLeadingZero
WcmCountLeadingZero: ; 0x020A5A70
	clz r0, r0
	bx lr

	arm_func_start WcmWcmbReset
WcmWcmbReset: ; 0x020A5A78
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020A5D80
	ldr r2, _020A5DA8 ; =wcmw
	mov r0, #0x0
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26b]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x82]
	ldr r3, [r2, #0x0]
	add r1, r3, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0xd
	addls pc, pc, r1, lsl #0x2
	b _020A5D4C
_020A5AC4: ; jump table
	b _020A5D4C ; case 0
	b _020A5D4C ; case 1
	b _020A5D4C ; case 2
	b _020A5D4C ; case 3
	b _020A5D4C ; case 4
	b _020A5AFC ; case 5
	b _020A5AFC ; case 6
	b _020A5B24 ; case 7
	b _020A5B4C ; case 8
	b _020A5C74 ; case 9
	b _020A5CA4 ; case 10
	b _020A5D4C ; case 11
	b _020A5C74 ; case 12
	b _020A5CD4 ; case 13
_020A5AFC:
	mov r0, #0x3
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A5DAC ; =0x000008F5
	mov r2, r1
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5B24:
	mov r0, #0x3
	bl WcmSetPhase
	mov r0, #0x0
	ldr r3, _020A5DB0 ; =0x000008FB
	mov r1, r0
	mov r2, r0
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5B4C:
	add r1, r3, #0x2200
	ldrh r4, [r1, #0xf8]
	strh r0, [r1, #0xf8]
	cmp r4, #0x12
	bne _020A5C44
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2100
	ldrh r3, [r1, #0x70]
	and r12, r3, #0x24
	cmp r12, #0x24
	beq _020A5C44
	orr r3, r3, #0x24
	strh r3, [r1, #0x70]
	ldr r2, [r2, #0x0]
	add r1, r2, #0x2000
	ldr r3, [r1, #0x264]
	and r1, r3, #0xc0000
	cmp r1, #0xc0000
	moveq r0, #0x1
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	and r1, r3, #0x30000
	cmp r1, #0x30000
	movne r3, #0x1
	add r1, r2, #0x2140
	ldr r0, _020A5DB4 ; =WcmWmcbConnect
	moveq r3, #0x0
	mov r2, #0x0
	str r12, [sp, #0x0]
	bl WM_StartConnectEx
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5C14
	cmp r0, #0x8
	bne _020A5C14
	mov r0, #0xc
	bl WcmSetPhase
	ldr r0, _020A5DA8 ; =wcmw
	ldr r3, _020A5DB8 ; =0x0000091C
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C14:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A5DA8 ; =wcmw
	ldr r3, _020A5DBC ; =0x00000925
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C44:
	mov r0, #0x3
	bl WcmSetPhase
	ldr r0, _020A5DA8 ; =wcmw
	ldr r3, _020A5DC0 ; =0x0000092D
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C74:
	mov r0, #0x3
	bl WcmSetPhase
	ldr r0, _020A5DA8 ; =wcmw
	ldr r3, _020A5DC4 ; =0x00000935
	ldr r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r1, #0x2140
	mov r2, #0x1
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5CA4:
	mov r0, #0x3
	bl WcmSetPhase
	ldr r1, _020A5DA8 ; =wcmw
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A5DC8 ; =0x0000093C
	mov r2, r0
	add r1, r1, #0x2140
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5CD4:
	ldr r0, _020A5DCC ; =WcmWmcbCommon
	bl WM_PowerOff
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5D24
	cmp r0, #0x8
	bne _020A5D24
	mov r0, #0xc
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A5DD0 ; =0x0000094A
	mov r2, r1
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D24:
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A5DD4 ; =0x00000953
	mov r2, r1
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D4C:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A5DA8 ; =wcmw
	ldr r3, _020A5DD8 ; =0x00000959
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	mov r1, #0x0
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D80:
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	mov r2, r1
	mov r0, #0x7
	mov r3, #0x960
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A5DA8: .word wcmw
_020A5DAC: .word 0x000008F5
_020A5DB0: .word 0x000008FB
_020A5DB4: .word WcmWmcbConnect
_020A5DB8: .word 0x0000091C
_020A5DBC: .word 0x00000925
_020A5DC0: .word 0x0000092D
_020A5DC4: .word 0x00000935
_020A5DC8: .word 0x0000093C
_020A5DCC: .word WcmWmcbCommon
_020A5DD0: .word 0x0000094A
_020A5DD4: .word 0x00000953
_020A5DD8: .word 0x00000959

	arm_func_start WcmWmcbEndDCF
WcmWmcbEndDCF: ; 0x020A5DDC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A5EF4
_020A5DF4: ; jump table
	b _020A5E08 ; case 0
	b _020A5EDC ; case 1
	b _020A5EF4 ; case 2
	b _020A5EDC ; case 3
	b _020A5EF4 ; case 4
_020A5E08:
	ldr r0, _020A5F24 ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A5E38
	mov r0, #0xa
	bl WcmSetPhase
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5E38:
	ldr r0, _020A5F28 ; =WcmWmcbDisconnect
	mov r1, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5E94
	cmp r0, #0x8
	bne _020A5EAC
	mov r0, #0xc
	bl WcmSetPhase
	ldr r0, _020A5F24 ; =wcmw
	ldr r3, _020A5F2C ; =0x000008B4
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5E94:
	mov r0, #0xa
	bl WcmSetPhase
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EAC:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r1, _020A5F24 ; =wcmw
	mov r0, #0x7
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r1, r1, #0x2140
	mov r3, #0x8c0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EDC:
	mov r0, #0xa
	bl WcmSetPhase
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EF4:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A5F24 ; =wcmw
	ldr r3, _020A5F30 ; =0x000008D3
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A5F24: .word wcmw
_020A5F28: .word WcmWmcbDisconnect
_020A5F2C: .word 0x000008B4
_020A5F30: .word 0x000008D3

	arm_func_start WcmWmcbStartDCF
WcmWmcbStartDCF: ; 0x020A5F34
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _020A5F50
	cmp r0, #0x4
	b _020A601C
_020A5F50:
	ldrh r0, [r4, #0x4]
	cmp r0, #0xe
	beq _020A5F68
	cmp r0, #0xf
	beq _020A5FC0
	b _020A5FF0
_020A5F68:
	ldr r0, _020A6048 ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A5F94
	mov r0, #0x8
	bl WcmSetPhase
	bl WcmWmReset
	ldmia sp!, {r4,lr}
	bx lr
_020A5F94:
	mov r0, #0x9
	bl WcmSetPhase
	ldr r1, _020A6048 ; =wcmw
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A604C ; =0x00000872
	mov r2, r0
	add r1, r1, #0x2140
	bl WcmNotify
	ldmia sp!, {r4,lr}
	bx lr
_020A5FC0:
	ldr r0, [r4, #0x8]
	ldrh r0, [r0, #0xe]
	mov r0, r0, asr #0x8
	and r0, r0, #0xff
	bl WCMi_ShelterRssi
	ldr r0, [r4, #0x8]
	mov r1, #0x620
	bl DC_InvalidateRange
	ldr r0, [r4, #0x8]
	bl WCMi_CpsifRecvCallback
	ldmia sp!, {r4,lr}
	bx lr
_020A5FF0:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A6048 ; =wcmw
	ldrh r2, [r4, #0x4]
	ldr r0, [r0, #0x0]
	ldr r3, _020A6050 ; =0x00000881
	add r1, r0, #0x2140
	mov r0, #0x7
	bl WcmNotify
	ldmia sp!, {r4,lr}
	bx lr
_020A601C:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A6048 ; =wcmw
	ldr r3, _020A6054 ; =0x0000088C
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A6048: .word wcmw
_020A604C: .word 0x00000872
_020A6050: .word 0x00000881
_020A6054: .word 0x0000088C

	arm_func_start WcmWmcbDisconnect
WcmWmcbDisconnect: ; 0x020A6058
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6108
_020A6070: ; jump table
	b _020A6084 ; case 0
	b _020A60F0 ; case 1
	b _020A6108 ; case 2
	b _020A60F0 ; case 3
	b _020A6108 ; case 4
_020A6084:
	ldr r0, _020A6138 ; =wcmw
	ldr r1, [r0, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A60B4
	mov r0, #0xa
	bl WcmSetPhase
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A60B4:
	add r1, r1, #0x2200
	mov r2, #0x0
	mov r0, #0x3
	strh r2, [r1, #0x82]
	bl WcmSetPhase
	ldr r1, _020A6138 ; =wcmw
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A613C ; =0x0000083D
	mov r2, r0
	add r1, r1, #0x2140
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A60F0:
	mov r0, #0xa
	bl WcmSetPhase
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6108:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A6138 ; =wcmw
	ldr r3, _020A6140 ; =0x0000084F
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6138: .word wcmw
_020A613C: .word 0x0000083D
_020A6140: .word 0x0000084F

	arm_func_start WcmWmcbConnect
WcmWmcbConnect: ; 0x020A6144
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r0, [r4, #0x2]
	cmp r0, #0xc
	addls pc, pc, r0, lsl #0x2
	b _020A638C
_020A615C: ; jump table
	b _020A6190 ; case 0
	b _020A6364 ; case 1
	b _020A638C ; case 2
	b _020A638C ; case 3
	b _020A638C ; case 4
	b _020A638C ; case 5
	b _020A6378 ; case 6
	b _020A638C ; case 7
	b _020A638C ; case 8
	b _020A638C ; case 9
	b _020A638C ; case 10
	b _020A6378 ; case 11
	b _020A6378 ; case 12
_020A6190:
	ldrh r0, [r4, #0x8]
	cmp r0, #0x9
	bgt _020A61D0
	cmp r0, #0x0
	addge pc, pc, r0, lsl #0x2
	b _020A6338 ; case 0
	b _020A6338 ; case 1
	b _020A6338 ; case 2
	b _020A6338 ; case 3
	b _020A6338 ; case 4
	b _020A6338 ; case 5
	b _020A6338 ; case 6
	b _020A63B0 ; case 7
	b _020A6258 ; case 8
	b _020A61E0 ; case 9
	b _020A61E0 ; case 10
_020A61D0:
	cmp r0, #0x1a
	ldmeqia sp!, {r4,lr}
	bxeq lr
	b _020A6338
_020A61E0:
	ldr r1, _020A63B8 ; =wcmw
	ldr r2, [r1, #0x0]
	add r0, r2, #0x2000
	ldr r0, [r0, #0x260]
	sub r0, r0, #0x8
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A63B0
_020A6200: ; jump table
	b _020A6220 ; case 0
	b _020A6230 ; case 1
	b _020A6214 ; case 2
	b _020A63B0 ; case 3
	b _020A624C ; case 4
_020A6214:
	add r0, r2, #0x2200
	mov r1, #0x0
	strh r1, [r0, #0x82]
_020A6220:
	mov r0, #0xc
	bl WcmSetPhase
	ldmia sp!, {r4,lr}
	bx lr
_020A6230:
	add r0, r2, #0x2200
	mov r2, #0x0
	strh r2, [r0, #0x82]
	ldr r0, [r1, #0x0]
	mov r1, #0x6
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
_020A624C:
	bl WcmWmReset
	ldmia sp!, {r4,lr}
	bx lr
_020A6258:
	ldr r1, _020A63B8 ; =wcmw
	ldr r3, [r1, #0x0]
	add r0, r3, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A6284
	mov r0, #0x8
	bl WcmSetPhase
	bl WcmWmReset
	ldmia sp!, {r4,lr}
	bx lr
_020A6284:
	ldrh r2, [r4, #0xa]
	cmp r2, #0x1
	blo _020A632C
	ldr r0, _020A63BC ; =0x000007D7
	cmp r2, r0
	bhi _020A632C
	add r0, r3, #0x2200
	strh r2, [r0, #0x82]
	ldr r1, [r1, #0x0]
	ldr r0, _020A63C0 ; =WcmWmcbStartDCF
	add r1, r1, #0x1500
	mov r2, #0x620
	bl WM_StartDCF
	cmp r0, #0x2
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A6300
	cmp r0, #0x8
	bne _020A6300
	mov r0, #0xc
	bl WcmSetPhase
	ldr r0, _020A63B8 ; =wcmw
	ldr r3, _020A63C4 ; =0x000007ED
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
	ldmia sp!, {r4,lr}
	bx lr
_020A6300:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A63B8 ; =wcmw
	ldr r3, _020A63C8 ; =0x000007F6
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
	ldmia sp!, {r4,lr}
	bx lr
_020A632C:
	bl WcmWmReset
	ldmia sp!, {r4,lr}
	bx lr
_020A6338:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A63B8 ; =wcmw
	ldrh r2, [r4, #0x8]
	ldr r0, [r0, #0x0]
	ldr r3, _020A63CC ; =0x00000804
	add r1, r0, #0x2140
	mov r0, #0x7
	bl WcmNotify
	ldmia sp!, {r4,lr}
	bx lr
_020A6364:
	ldr r0, _020A63B8 ; =wcmw
	ldrh r1, [r4, #0xe]
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0xf8]
_020A6378:
	mov r0, #0x8
	bl WcmSetPhase
	bl WcmWmReset
	ldmia sp!, {r4,lr}
	bx lr
_020A638C:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A63B8 ; =wcmw
	ldr r3, _020A63D0 ; =0x0000081B
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl WcmNotify
_020A63B0:
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A63B8: .word wcmw
_020A63BC: .word 0x000007D7
_020A63C0: .word WcmWmcbStartDCF
_020A63C4: .word 0x000007ED
_020A63C8: .word 0x000007F6
_020A63CC: .word 0x00000804
_020A63D0: .word 0x0000081B

	arm_func_start WcmWmcbEndScan
WcmWmcbEndScan: ; 0x020A63D4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6438
_020A63EC: ; jump table
	b _020A6400 ; case 0
	b _020A6428 ; case 1
	b _020A6438 ; case 2
	b _020A6438 ; case 3
	b _020A6438 ; case 4
_020A6400:
	mov r0, #0x3
	bl WcmSetPhase
	mov r0, #0x0
	ldr r3, _020A6460 ; =0x00000783
	mov r1, r0
	mov r2, r0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6428:
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6438:
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A6464 ; =0x00000793
	mov r2, r1
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6460: .word 0x00000783
_020A6464: .word 0x00000793

	arm_func_start WcmWmcbScanEx
WcmWmcbScanEx: ; 0x020A6468
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldrh r0, [r5, #0x2]
	mov r4, #0x14
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6714
_020A6488: ; jump table
	b _020A649C ; case 0
	b _020A6704 ; case 1
	b _020A6714 ; case 2
	b _020A6714 ; case 3
	b _020A6714 ; case 4
_020A649C:
	ldr r0, _020A673C ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x5
	bne _020A64D0
	mov r0, #0x6
	bl WcmSetPhase
	mov r0, #0x0
	ldr r3, _020A6740 ; =0x00000704
	mov r1, r0
	mov r2, r0
	bl WcmNotify
_020A64D0:
	ldr r1, _020A673C ; =wcmw
	ldr r2, [r1, #0x0]
	add r0, r2, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x6
	beq _020A64FC
	cmp r0, #0x7
	beq _020A6674
	cmp r0, #0xd
	beq _020A6684
	b _020A6694
_020A64FC:
	add r0, r2, #0x2200
	mov r2, #0x7
	strh r2, [r0, #0x80]
	ldrh r0, [r5, #0x8]
	cmp r0, #0x5
	bne _020A6588
	ldr r0, [r1, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldrh r0, [r5, #0xe]
	mov r4, #0x0
	cmp r0, #0x0
	ble _020A6588
	ldr r8, _020A6744 ; =0x0000071A
	mov r6, r4
	mov r7, #0x7
_020A6548:
	add r0, r5, r4, lsl #0x1
	add r2, r5, r4, lsl #0x2
	ldrh r1, [r0, #0x50]
	ldr r0, [r2, #0x10]
	bl WCMi_EntryApList
	str r8, [sp, #0x0]
	add r0, r5, r4, lsl #0x2
	ldr r2, [r0, #0x10]
	mov r0, r7
	mov r1, r6
	mov r3, r5
	bl WcmNotifyEx
	ldrh r0, [r5, #0xe]
	add r4, r4, #0x1
	cmp r4, r0
	blt _020A6548
_020A6588:
	ldr r0, _020A673C ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r1, [r0, #0x264]
	and r0, r1, #0xc00000
	cmp r0, #0xc00000
	bne _020A65F4
	ldr r0, _020A6748 ; =0x00003FFE
	and r0, r1, r0
	bl WcmCountBits
	movs r1, r0
	beq _020A65F4
	ldr r0, _020A673C ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r6, [r0, #0x284]
	mov r0, r6
	bl _u32_div_f
	cmp r1, #0x0
	bne _020A65F4
	ldr r4, _020A674C ; =0x00000728
	mov r1, #0x0
	mov r2, r6
	mov r3, r1
	mov r0, #0x8
	str r4, [sp, #0x0]
	bl WcmNotifyEx
_020A65F4:
	ldrh r0, [r5, #0xa]
	bl WcmCountLeadingZero
	rsb r0, r0, #0x20
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl WcmGetNextScanChannel
	ldr r1, _020A673C ; =wcmw
	mov r2, #0x1
	mov r2, r2, lsl r0
	ldr r0, [r1, #0x0]
	mov r2, r2, asr #0x1
	add r0, r0, #0x2200
	strh r2, [r0, #0x8e]
	ldr r0, [r1, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldr r3, _020A673C ; =wcmw
	ldr r2, _020A6750 ; =0x00002288
	ldr r1, [r3, #0x0]
	ldr r0, _020A6754 ; =WcmWmcbScanEx
	add r1, r1, #0x2000
	ldr r4, [r1, #0x284]
	add r4, r4, #0x1
	str r4, [r1, #0x284]
	ldr r1, [r3, #0x0]
	add r1, r1, r2
	bl WM_StartScanEx
	mov r4, r0
	b _020A6694
_020A6674:
	ldr r0, _020A6758 ; =WcmWmcbEndScan
	bl WM_EndScan
	mov r4, r0
	b _020A6694
_020A6684:
	bl WcmWmReset
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6694:
	cmp r4, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r4, #0x3
	beq _020A66DC
	cmp r4, #0x8
	bne _020A66DC
	mov r0, #0xc
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A675C ; =0x00000753
	mov r2, r1
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A66DC:
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A6760 ; =0x0000075C
	mov r2, r1
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6704:
	bl WcmWmReset
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6714:
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A6764 ; =0x0000076D
	mov r2, r1
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A673C: .word wcmw
_020A6740: .word 0x00000704
_020A6744: .word 0x0000071A
_020A6748: .word 0x00003FFE
_020A674C: .word 0x00000728
_020A6750: .word 0x00002288
_020A6754: .word WcmWmcbScanEx
_020A6758: .word WcmWmcbEndScan
_020A675C: .word 0x00000753
_020A6760: .word 0x0000075C
_020A6764: .word 0x0000076D

	arm_func_start WcmWmcbCommon
WcmWmcbCommon: ; 0x020A6768
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x2]
	mov r2, #0x14
	cmp r1, #0x4
	addls pc, pc, r1, lsl #0x2
	b _020A6A0C
_020A6784: ; jump table
	b _020A6798 ; case 0
	b _020A69CC ; case 1
	b _020A6A0C ; case 2
	b _020A6A0C ; case 3
	b _020A6A0C ; case 4
_020A6798:
	ldrh r0, [r0, #0x0]
	cmp r0, #0x19
	bgt _020A67D4
	cmp r0, #0x19
	bge _020A68B4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020A692C
_020A67B8: ; jump table
	b _020A692C ; case 0
	b _020A692C ; case 1
	b _020A692C ; case 2
	b _020A67F4 ; case 3
	b _020A6804 ; case 4
	b _020A6868 ; case 5
	b _020A6890 ; case 6
_020A67D4:
	cmp r0, #0x1d
	bgt _020A67E8
	cmp r0, #0x1d
	beq _020A68A0
	b _020A692C
_020A67E8:
	cmp r0, #0x27
	beq _020A68DC
	b _020A692C
_020A67F4:
	ldr r0, _020A6A4C ; =WcmWmcbCommon
	bl WM_PowerOn
	mov r2, r0
	b _020A692C
_020A6804:
	bl WM_Finish
	cmp r0, #0x0
	beq _020A6818
	cmp r0, #0x4
	b _020A6840
_020A6818:
	mov r0, #0x1
	bl WcmSetPhase
	mov r0, #0x0
	ldr r3, _020A6A50 ; =0x00000663
	mov r1, r0
	mov r2, r0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6840:
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	ldr r3, _020A6A54 ; =0x0000066C
	mov r2, r1
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6868:
	mov r0, #0x3
	bl WcmSetPhase
	mov r0, #0x0
	ldr r3, _020A6A58 ; =0x00000673
	mov r1, r0
	mov r2, r0
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6890:
	ldr r0, _020A6A4C ; =WcmWmcbCommon
	bl WM_Disable
	mov r2, r0
	b _020A692C
_020A68A0:
	ldr r0, _020A6A4C ; =WcmWmcbCommon
	mov r1, #0x0
	bl WM_SetBeaconIndication
	mov r2, r0
	b _020A692C
_020A68B4:
	ldr r1, _020A6A5C ; =wcmw
	ldr r0, _020A6A4C ; =WcmWmcbCommon
	ldr r3, [r1, #0x0]
	add r2, r3, #0x2000
	ldrb r1, [r2, #0x250]
	ldrb r2, [r2, #0x251]
	add r3, r3, #0x2200
	bl WM_SetWEPKeyEx
	mov r2, r0
	b _020A692C
_020A68DC:
	ldr r0, _020A6A5C ; =wcmw
	ldr r2, [r0, #0x0]
	add r0, r2, #0x2000
	ldr r1, [r0, #0x264]
	and r0, r1, #0xc0000
	cmp r0, #0xc0000
	moveq r0, #0x1
	movne r0, #0x0
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	and r1, r1, #0x30000
	cmp r1, #0x30000
	movne r3, #0x1
	add r1, r2, #0x2140
	ldr r0, _020A6A60 ; =WcmWmcbConnect
	moveq r3, #0x0
	mov r2, #0x0
	str r12, [sp, #0x0]
	bl WM_StartConnectEx
	mov r2, r0
_020A692C:
	cmp r2, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r2, #0x3
	beq _020A698C
	cmp r2, #0x8
	bne _020A698C
	mov r0, #0xc
	bl WcmSetPhase
	ldr r0, _020A6A5C ; =wcmw
	ldr r3, _020A6A64 ; =0x000006AF
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A698C:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A6A5C ; =wcmw
	ldr r3, _020A6A68 ; =0x000006B8
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A69CC:
	mov r0, #0xc
	bl WcmSetPhase
	ldr r0, _020A6A5C ; =wcmw
	ldr r3, _020A6A6C ; =0x000006DE
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x1
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6A0C:
	mov r0, #0xb
	bl WcmSetPhase
	ldr r0, _020A6A5C ; =wcmw
	ldr r3, _020A6A70 ; =0x000006E8
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x7
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6A4C: .word WcmWmcbCommon
_020A6A50: .word 0x00000663
_020A6A54: .word 0x0000066C
_020A6A58: .word 0x00000673
_020A6A5C: .word wcmw
_020A6A60: .word WcmWmcbConnect
_020A6A64: .word 0x000006AF
_020A6A68: .word 0x000006B8
_020A6A6C: .word 0x000006DE
_020A6A70: .word 0x000006E8

	arm_func_start WcmWmcbIndication
WcmWmcbIndication: ; 0x020A6A74
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x2]
	cmp r1, #0x8
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r1, [r0, #0x4]
	cmp r1, #0x16
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r0, [r0, #0x6]
	cmp r0, #0x25
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A6B24 ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	sub r0, r0, #0x8
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6B18
_020A6AD8: ; jump table
	b _020A6AEC ; case 0
	b _020A6B00 ; case 1
	b _020A6B10 ; case 2
	b _020A6B18 ; case 3
	b _020A6B00 ; case 4
_020A6AEC:
	mov r0, #0xc
	bl WcmSetPhase
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6B00:
	bl WcmWmReset
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6B10:
	mov r0, #0xc
	bl WcmSetPhase
_020A6B18:
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6B24: .word wcmw

	arm_func_start WcmWmReset
WcmWmReset: ; 0x020A6B28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020A6B98 ; =wcmw
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2000
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A6B9C ; =WcmWcmbReset
	mov r2, #0x1
	strb r2, [r1, #0x26b]
	bl WM_Reset
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	mov r0, #0xb
	bl WcmSetPhase
	mov r1, #0x0
	mov r2, r1
	mov r0, #0x7
	mov r3, #0x610
	bl WcmNotify
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6B98: .word wcmw
_020A6B9C: .word WcmWcmbReset

	arm_func_start WcmKeepAliveAlarm
WcmKeepAliveAlarm: ; 0x020A6BA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl WCMi_CpsifSendNullPacket
	bl WCMi_ResetKeepAliveAlarm
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start WCMi_ResetKeepAliveAlarm
WCMi_ResetKeepAliveAlarm: ; 0x020A6BBC
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	bl OS_DisableInterrupts
	ldr r2, _020A6C28 ; =wcmw
	ldr r1, _020A6C2C ; =0x000022CC
	ldr r2, [r2, #0x0]
	mov r4, r0
	add r0, r2, r1
	bl OS_CancelAlarm
	ldr r0, _020A6C28 ; =wcmw
	ldr r12, [r0, #0x0]
	add r0, r12, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A6C14
	ldr r0, _020A6C2C ; =0x000022CC
	ldr r1, _020A6C30 ; =0x022F5341
	mov r2, #0x0
	ldr r3, _020A6C34 ; =WcmKeepAliveAlarm
	add r0, r12, r0
	str r2, [sp, #0x0]
	bl OS_SetAlarm
_020A6C14:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A6C28: .word wcmw
_020A6C2C: .word 0x000022CC
_020A6C30: .word 0x022F5341
_020A6C34: .word WcmKeepAliveAlarm

	arm_func_start WcmSetPhase
WcmSetPhase:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020A6CD0 ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A6C78
	cmp r5, #0x9
	beq _020A6C78
	ldr r0, _020A6CD4 ; =0x000022CC
	add r0, r1, r0
	bl OS_CancelAlarm
_020A6C78:
	ldr r0, _020A6CD0 ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0xb
	strne r5, [r0, #0x260]
	cmp r5, #0x9
	bne _020A6CBC
	mov r2, #0x0
	ldr r0, _020A6CD0 ; =wcmw
	str r2, [sp, #0x0]
	ldr r5, [r0, #0x0]
	ldr r0, _020A6CD4 ; =0x000022CC
	ldr r1, _020A6CD8 ; =0x022F5341
	ldr r3, _020A6CDC ; =WcmKeepAliveAlarm
	add r0, r5, r0
	bl OS_SetAlarm
_020A6CBC:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6CD0: .word wcmw
_020A6CD4: .word 0x000022CC
_020A6CD8: .word 0x022F5341
_020A6CDC: .word WcmKeepAliveAlarm

	arm_func_start WcmNotifyEx
WcmNotifyEx: ; 0x020A6CE0
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr ip, _020A6D38 ; =wcmw
	ldr r12, [r12, #0x0]
	add r12, r12, #0x2000
	ldr lr, [r12, #0x27c]
	cmp lr, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {lr}
	bxeq lr
	ldr lr, [sp, #0x18]
	strh r0, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	str lr, [sp, #0xc]
	strh r1, [sp, #0x2]
	ldr r1, [r12, #0x27c]
	add r0, sp, #0x0
	blx r1
	add sp, sp, #0x14
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6D38: .word wcmw

	arm_func_start WcmNotify
WcmNotify: ; 0x020A6D3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr ip, _020A6D88 ; =wcmw
	mov r5, r0
	ldr r0, [r12, #0x0]
	mov r4, r1
	add r1, r0, #0x2200
	ldrsh r0, [r1, #0x80]
	mov r12, #0x0
	mov lr, r2
	strh r12, [r1, #0x80]
	str r3, [sp, #0x0]
	mov r1, r5
	mov r2, r4
	mov r3, lr
	bl WcmNotifyEx
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6D88: .word wcmw

	arm_func_start WcmGetNextScanChannel
WcmGetNextScanChannel: ; 0x020A6D8C
	stmdb sp!, {r4-r6,lr}
	ldr r1, _020A6E24 ; =wcmw
	mov r2, r0
	ldr r1, [r1, #0x0]
	mov r3, #0x0
	add r1, r1, #0x2000
	ldr r1, [r1, #0x264]
	mov r6, #0x1
	ldr r5, _020A6E28 ; =0x4EC4EC4F
	ldr r4, _020A6E2C ; =0x0000000D
_020A6DB4:
	smull r12, lr, r5, r2
	mov lr, lr, asr #0x2
	mov r12, r2, lsr #0x1f
	add lr, r12, lr
	smull r12, lr, r4, lr
	sub lr, r2, r12
	add r12, lr, #0x1
	mov r12, r6, lsl r12
	ands r12, r1, r12
	bne _020A6DEC
	add r3, r3, #0x1
	cmp r3, #0xd
	add r2, r2, #0x1
	blt _020A6DB4
_020A6DEC:
	ldr r1, _020A6E28 ; =0x4EC4EC4F
	add r3, r0, r3
	smull r0, r4, r1, r3
	mov r4, r4, asr #0x2
	mov r0, r3, lsr #0x1f
	ldr r2, _020A6E2C ; =0x0000000D
	add r4, r0, r4
	smull r0, r1, r2, r4
	sub r4, r3, r0
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A6E24: .word wcmw
_020A6E28: .word 0x4EC4EC4F
_020A6E2C: .word 0x0000000D

	arm_func_start WcmInitOption
WcmInitOption: ; 0x020A6E30
	ldr r0, _020A6E48 ; =wcmw
	ldr r1, _020A6E4C ; =0x00AAA082
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x264]
	bx lr
	.balign 4
_020A6E48: .word wcmw
_020A6E4C: .word 0x00AAA082

	arm_func_start WcmEditScanExParam
WcmEditScanExParam: ; 0x020A6E50
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r0, r2
	mov r4, r1
	bl WCM_UpdateOption
	ldr r2, _020A6FF4 ; =wcmw
	mov r3, #0x400
	ldr r1, [r2, #0x0]
	mov r0, #0x0
	add r12, r1, #0x1500
	add r1, r1, #0x2000
	str r12, [r1, #0x288]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r3, [r1, #0x8c]
	bl WcmGetNextScanChannel
	ldr r1, _020A6FF4 ; =wcmw
	mov r2, #0x1
	mov r2, r2, lsl r0
	ldr r0, [r1, #0x0]
	mov r2, r2, asr #0x1
	add r0, r0, #0x2200
	strh r2, [r0, #0x8e]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2200
	ldrh r0, [r0, #0x68]
	cmp r0, #0x0
	bne _020A6EC8
	bl WM_GetDispersionScanPeriod
_020A6EC8:
	ldr r2, _020A6FF4 ; =wcmw
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x90]
	ldr r1, [r2, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x264]
	and r0, r0, #0x300000
	cmp r0, #0x300000
	movne r2, #0x1
	moveq r2, #0x0
	add r0, r1, #0x2200
	strh r2, [r0, #0x98]
	cmp r5, #0x0
	bne _020A6F24
	ldr r0, _020A6FF4 ; =wcmw
	ldr r1, _020A6FF8 ; =0x00002292
	ldr r2, [r0, #0x0]
	ldr r0, _020A6FFC ; =WCM_Bssid_Any
	add r1, r2, r1
	mov r2, #0x6
	bl MI_CpuCopy8
	b _020A6F40
_020A6F24:
	ldr r0, _020A6FF4 ; =wcmw
	ldr r1, _020A6FF8 ; =0x00002292
	ldr r2, [r0, #0x0]
	mov r0, r5
	add r1, r2, r1
	mov r2, #0x6
	bl MI_CpuCopy8
_020A6F40:
	cmp r4, #0x0
	beq _020A6F54
	ldr r0, _020A7000 ; =WCM_Essid_Any
	cmp r4, r0
	bne _020A6F88
_020A6F54:
	ldr r0, _020A6FF4 ; =wcmw
	ldr r1, _020A7004 ; =0x0000229C
	ldr r2, [r0, #0x0]
	ldr r0, _020A7000 ; =WCM_Essid_Any
	add r1, r2, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, _020A6FF4 ; =wcmw
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x9a]
	b _020A6FD4
_020A6F88:
	ldr r0, _020A6FF4 ; =wcmw
	ldr r1, _020A7004 ; =0x0000229C
	ldr r2, [r0, #0x0]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r1, #0x0
_020A6FA8:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020A6FC4
	add r1, r1, #0x1
	cmp r1, #0x20
	add r4, r4, #0x1
	blt _020A6FA8
_020A6FC4:
	ldr r0, _020A6FF4 ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x9a]
_020A6FD4:
	ldr r0, _020A6FF4 ; =wcmw
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x284]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6FF4: .word wcmw
_020A6FF8: .word 0x00002292
_020A6FFC: .word WCM_Bssid_Any
_020A7000: .word WCM_Essid_Any
_020A7004: .word 0x0000229C

	arm_func_start WcmConfigure
WcmConfigure: ; 0x020A7008
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	bne _020A705C
	ldr r1, _020A7134 ; =wcmw
	mov r3, #0x3
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2000
	str r3, [r0, #0x26c]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x278]
	b _020A7118
_020A705C:
	ldr r1, _020A7134 ; =wcmw
	ldr r2, [r5, #0x0]
	ldr r0, [r1, #0x0]
	and r2, r2, #0x3
	add r0, r0, #0x2000
	str r2, [r0, #0x26c]
	ldr r3, [r5, #0x4]
	ldr r0, [r5, #0x8]
	and r2, r3, #0x3
	rsb r2, r2, #0x4
	and r2, r2, #0x3
	add r2, r2, #0xc
	cmp r2, r0
	bls _020A70B4
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	b _020A7104
_020A70B4:
	ldr r0, [r1, #0x0]
	add r2, r3, #0x3
	bic r2, r2, #0x3
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r2, [r5, #0x4]
	ldr r0, [r1, #0x0]
	and r2, r2, #0x3
	rsb r2, r2, #0x4
	ldr r3, [r5, #0x8]
	and r2, r2, #0x3
	sub r2, r3, r2
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	add r2, r0, #0x2000
	ldr r0, [r2, #0x270]
	ldr r2, [r2, #0x274]
	bl MI_CpuFill8
_020A7104:
	ldr r0, _020A7134 ; =wcmw
	ldr r1, [r5, #0xc]
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x278]
_020A7118:
	ldr r0, _020A7134 ; =wcmw
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r4, [r0, #0x27c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A7134: .word wcmw

	arm_func_start WCMi_GetSystemWork
WCMi_GetSystemWork:
	ldr r0, _020A7144 ; =wcmw
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020A7144: .word wcmw

	arm_func_start WCM_UpdateOption
WCM_UpdateOption: ; 0x020A7148
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020A71EC ; =wcmw
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r3, r1, #0x2000
	cmp r1, #0x0
	ldr r4, [r3, #0x264]
	bne _020A7188
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7188:
	ands r3, r5, #0x8000
	beq _020A71A4
	ldr r3, _020A71F0 ; =0x00003FFE
	orr r2, r2, r3
	ands r3, r5, r3
	ldreq r3, _020A71F4 ; =0x0000A082
	orreq r5, r5, r3
_020A71A4:
	ands r3, r5, #0x20000
	orrne r2, r2, #0x10000
	ands r3, r5, #0x80000
	orrne r2, r2, #0x40000
	ands r3, r5, #0x200000
	orrne r2, r2, #0x100000
	ands r3, r5, #0x800000
	orrne r2, r2, #0x400000
	mvn r2, r2
	and r2, r4, r2
	orr r2, r5, r2
	add r1, r1, #0x2000
	str r2, [r1, #0x264]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A71EC: .word wcmw
_020A71F0: .word 0x00003FFE
_020A71F4: .word 0x0000A082

	arm_func_start WCM_GetPhase
WCM_GetPhase: ; 0x020A71F8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A7228 ; =wcmw
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	addne r1, r1, #0x2000
	ldrne r4, [r1, #0x260]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A7228: .word wcmw

	arm_func_start WCM_TerminateAsync
WCM_TerminateAsync: ; 0x020A722C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020A747C ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7260
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7260:
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0xd
	addls pc, pc, r2, lsl #0x2
	b _020A7308
_020A7274: ; jump table
	b _020A7308 ; case 0
	b _020A72C0 ; case 1
	b _020A7308 ; case 2
	b _020A7320 ; case 3
	b _020A7308 ; case 4
	b _020A7308 ; case 5
	b _020A72D4 ; case 6
	b _020A7308 ; case 7
	b _020A7308 ; case 8
	b _020A7320 ; case 9
	b _020A7308 ; case 10
	b _020A7308 ; case 11
	b _020A7320 ; case 12
	b _020A72AC ; case 13
_020A72AC:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A72C0:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A72D4:
	mov r0, #0xd
	bl WcmSetPhase
	ldr r1, _020A747C ; =wcmw
	mov r0, r4
	ldr r1, [r1, #0x0]
	mov r2, #0x9
	add r1, r1, #0x2200
	strh r2, [r1, #0x80]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x3
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7308:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7320:
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x1
	bne _020A734C
	mov r0, #0xd
	bl WcmSetPhase
	ldr r0, _020A747C ; =wcmw
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7464
_020A734C:
	bl WMi_GetStatusAddress
	mov r5, r0
	mov r1, #0x2
	bl DC_InvalidateRange
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020A737C
	cmp r0, #0x1
	beq _020A73BC
	cmp r0, #0x2
	beq _020A73C8
	b _020A73D4
_020A737C:
	bl WM_Finish
	cmp r0, #0x0
	bne _020A73F0
	mov r0, #0x1
	bl WcmSetPhase
	ldr r1, _020A747C ; =wcmw
	mov r0, r4
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r1, r1, #0x2200
	strh r2, [r1, #0x80]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A73BC:
	ldr r0, _020A7480 ; =WcmWmcbCommon
	bl WM_Disable
	b _020A73F0
_020A73C8:
	ldr r0, _020A7480 ; =WcmWmcbCommon
	bl WM_PowerOff
	b _020A73F0
_020A73D4:
	ldr r1, _020A747C ; =wcmw
	ldr r0, _020A7484 ; =WcmWcmbReset
	ldr r1, [r1, #0x0]
	mov r2, #0x1
	add r1, r1, #0x2000
	strb r2, [r1, #0x26b]
	bl WM_Reset
_020A73F0:
	cmp r0, #0x2
	beq _020A740C
	cmp r0, #0x3
	beq _020A7444
	cmp r0, #0x8
	beq _020A742C
	b _020A7444
_020A740C:
	mov r0, #0xd
	bl WcmSetPhase
	ldr r0, _020A747C ; =wcmw
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7464
_020A742C:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7444:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7464:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A747C: .word wcmw
_020A7480: .word WcmWmcbCommon
_020A7484: .word WcmWcmbReset

	arm_func_start WCM_DisconnectAsync
WCM_DisconnectAsync: ; 0x020A7488
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A75B8 ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A74B4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A74B4:
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x3
	beq _020A74E4
	cmp r2, #0x9
	beq _020A7504
	cmp r2, #0xa
	bne _020A74F4
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A74E4:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A74F4:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7504:
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x1
	bne _020A7530
	mov r0, #0xa
	bl WcmSetPhase
	ldr r0, _020A75B8 ; =wcmw
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A75A4
_020A7530:
	ldr r0, _020A75BC ; =WcmWmcbEndDCF
	bl WM_EndDCF
	cmp r0, #0x2
	beq _020A7554
	cmp r0, #0x3
	beq _020A7588
	cmp r0, #0x8
	beq _020A7574
	b _020A7588
_020A7554:
	mov r0, #0xa
	bl WcmSetPhase
	ldr r0, _020A75B8 ; =wcmw
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A75A4
_020A7574:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4,lr}
	bx lr
_020A7588:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4,lr}
	bx lr
_020A75A4:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A75B8: .word wcmw
_020A75BC: .word WcmWmcbEndDCF

	arm_func_start WCM_ConnectAsync
WCM_ConnectAsync: ; 0x020A75C0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r2, _020A7814 ; =wcmw
	mov r4, r0
	ldr r12, [r2, #0x0]
	cmp r12, #0x0
	bne _020A7600
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7600:
	add r1, r12, #0x2000
	ldr r3, [r1, #0x260]
	cmp r3, #0x3
	beq _020A7624
	cmp r3, #0x8
	beq _020A7734
	cmp r3, #0x9
	beq _020A7748
	b _020A775C
_020A7624:
	cmp r7, #0x0
	bne _020A7640
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7640:
	ldrh r3, [r7, #0x3c]
	cmp r3, #0x0
	beq _020A7660
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7660:
	cmp r6, #0x0
	beq _020A76E8
	ldrb r3, [r6, #0x0]
	cmp r3, #0x4
	bhs _020A7680
	ldrb r0, [r6, #0x1]
	cmp r0, #0x4
	blo _020A7698
_020A7680:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7698:
	strb r3, [r1, #0x250]
	ldr r0, [r2, #0x0]
	ldrb r1, [r6, #0x1]
	add r0, r0, #0x2000
	strb r1, [r0, #0x251]
	ldr r1, [r2, #0x0]
	add r0, r1, #0x2000
	ldrb r0, [r0, #0x250]
	cmp r0, #0x0
	bne _020A76D4
	add r0, r1, #0x2200
	mov r1, #0x0
	mov r2, #0x50
	bl MI_CpuFill8
	b _020A76F8
_020A76D4:
	add r0, r6, #0x2
	add r1, r1, #0x2200
	mov r2, #0x50
	bl MI_CpuCopy8
	b _020A76F8
_020A76E8:
	add r0, r12, #0x2200
	mov r1, #0x0
	mov r2, #0x52
	bl MI_CpuFill8
_020A76F8:
	ldr r1, _020A7814 ; =wcmw
	mov r0, r7
	ldr r1, [r1, #0x0]
	mov r2, #0xc0
	add r1, r1, #0x2140
	bl MI_CpuCopy8
	ldr r1, _020A7814 ; =wcmw
	mov r0, r5
	ldr r1, [r1, #0x0]
	add r1, r1, #0x2100
	ldrh r2, [r1, #0x6e]
	orr r2, r2, #0x3
	strh r2, [r1, #0x70]
	bl WCM_UpdateOption
	b _020A7770
_020A7734:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7748:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A775C:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7770:
	ldr r1, _020A7818 ; =0x0000FFFF
	ldr r0, _020A781C ; =WcmWmcbCommon
	mov r3, r1
	mov r2, #0x50
	str r1, [sp, #0x0]
	bl WM_SetLifeTime
	cmp r0, #0x2
	beq _020A77A4
	cmp r0, #0x3
	beq _020A77DC
	cmp r0, #0x8
	beq _020A77C4
	b _020A77DC
_020A77A4:
	mov r0, #0x8
	bl WcmSetPhase
	ldr r0, _020A7814 ; =wcmw
	mov r1, #0x5
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A77FC
_020A77C4:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A77DC:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A77FC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A7814: .word wcmw
_020A7818: .word 0x0000FFFF
_020A781C: .word WcmWmcbCommon

	arm_func_start WCM_EndSearchAsync
WCM_EndSearchAsync: ; 0x020A7820
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A78D4 ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A784C
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A784C:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x3
	beq _020A78A0
	cmp r1, #0x6
	beq _020A7870
	cmp r1, #0x7
	beq _020A7890
	b _020A78B0
_020A7870:
	mov r0, #0x7
	bl WcmSetPhase
	ldr r0, _020A78D4 ; =wcmw
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A78C0
_020A7890:
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A78A0:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A78B0:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A78C0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A78D4: .word wcmw

	arm_func_start WCM_BeginSearchAsync
WCM_BeginSearchAsync: ; 0x020A78D8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r1, _020A7A84 ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7918
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7918:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x3
	beq _020A79A0
	cmp r1, #0x5
	beq _020A793C
	cmp r1, #0x6
	beq _020A7964
	b _020A798C
_020A793C:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl WcmEditScanExParam
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7964:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl WcmEditScanExParam
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A798C:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A79A0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl WcmEditScanExParam
	ldr r0, _020A7A84 ; =wcmw
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldr r3, _020A7A84 ; =wcmw
	ldr r2, _020A7A88 ; =0x00002288
	ldr r1, [r3, #0x0]
	ldr r0, _020A7A8C ; =WcmWmcbScanEx
	add r1, r1, #0x2000
	ldr r5, [r1, #0x284]
	add r5, r5, #0x1
	str r5, [r1, #0x284]
	ldr r1, [r3, #0x0]
	add r1, r1, r2
	bl WM_StartScanEx
	cmp r0, #0x2
	beq _020A7A14
	cmp r0, #0x3
	beq _020A7A4C
	cmp r0, #0x8
	beq _020A7A34
	b _020A7A4C
_020A7A14:
	mov r0, #0x5
	bl WcmSetPhase
	ldr r0, _020A7A84 ; =wcmw
	mov r1, #0x3
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7A6C
_020A7A34:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7A4C:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7A6C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A7A84: .word wcmw
_020A7A88: .word 0x00002288
_020A7A8C: .word WcmWmcbScanEx

	arm_func_start WCM_SearchAsync
WCM_SearchAsync: ; 0x020A7A90
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	beq _020A7AA8
	cmp r1, #0x0
	bne _020A7AB8
_020A7AA8:
	bl WCM_EndSearchAsync
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A7AB8:
	bl WCM_BeginSearchAsync
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start WCM_CleanupAsync
WCM_CleanupAsync: ; 0x020A7AC8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A7BCC ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7AF4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7AF4:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7B24
	cmp r1, #0x3
	beq _020A7B44
	cmp r1, #0x4
	bne _020A7B34
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A7B24:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A7B34:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7B44:
	ldr r0, _020A7BD0 ; =WcmWmcbCommon
	bl WM_PowerOff
	cmp r0, #0x2
	beq _020A7B68
	cmp r0, #0x3
	beq _020A7B9C
	cmp r0, #0x8
	beq _020A7B88
	b _020A7B9C
_020A7B68:
	mov r0, #0x4
	bl WcmSetPhase
	ldr r0, _020A7BCC ; =wcmw
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7BB8
_020A7B88:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4,lr}
	bx lr
_020A7B9C:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4,lr}
	bx lr
_020A7BB8:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A7BCC: .word wcmw
_020A7BD0: .word WcmWmcbCommon

	arm_func_start WCM_StartupAsync
WCM_StartupAsync: ; 0x020A7BD4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, _020A7E00 ; =wcmw
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7C08
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C08:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7C2C
	cmp r1, #0x2
	beq _020A7C3C
	cmp r1, #0x3
	beq _020A7C4C
	b _020A7C5C
_020A7C2C:
	mov r0, r6
	mov r1, r5
	bl WcmConfigure
	b _020A7C6C
_020A7C3C:
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C4C:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C5C:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C6C:
	ldr r0, _020A7E00 ; =wcmw
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2000
	ldr r1, [r1, #0x26c]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl WM_Init
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020A7CE0
_020A7C94: ; jump table
	b _020A7CFC ; case 0
	b _020A7CE0 ; case 1
	b _020A7CE0 ; case 2
	b _020A7CB0 ; case 3
	b _020A7CCC ; case 4
	b _020A7CE0 ; case 5
	b _020A7CE0 ; case 6
_020A7CB0:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CCC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CE0:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CFC:
	bl WM_GetAllowedChannel
	cmp r0, #0x0
	bne _020A7D44
	bl WM_Finish
	cmp r0, #0x0
	beq _020A7D30
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D30:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D44:
	ldr r0, _020A7E04 ; =WcmWmcbIndication
	bl WM_SetIndCallback
	cmp r0, #0x0
	beq _020A7D70
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D70:
	ldr r0, _020A7E08 ; =WcmWmcbCommon
	bl WM_Enable
	cmp r0, #0x2
	beq _020A7D94
	cmp r0, #0x3
	beq _020A7DD0
	cmp r0, #0x8
	beq _020A7DB4
	b _020A7DD0
_020A7D94:
	mov r0, #0x2
	bl WcmSetPhase
	ldr r0, _020A7E00 ; =wcmw
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7DEC
_020A7DB4:
	mov r0, #0xc
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7DD0:
	mov r0, #0xb
	bl WcmSetPhase
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7DEC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A7E00: .word wcmw
_020A7E04: .word WcmWmcbIndication
_020A7E08: .word WcmWmcbCommon

	arm_func_start WCM_Finish
WCM_Finish: ; 0x020A7E0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r2, _020A7E7C ; =wcmw
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020A7E3C
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020A7E3C:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7E60
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020A7E60:
	mov r1, #0x0
	str r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A7E7C: .word wcmw

	arm_func_start WCM_Init
WCM_Init: ; 0x020A7E80
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r2, _020A7FA8 ; =wcmw
	mov r4, r0
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020A7EB4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EB4:
	cmp r6, #0x0
	bne _020A7ECC
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7ECC:
	ands r1, r6, #0x1f
	beq _020A7EE4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EE4:
	cmp r5, #0x2300
	bhs _020A7EFC
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EFC:
	str r6, [r2, #0x0]
	add r0, r6, #0x2000
	mov r1, #0x1
	str r1, [r0, #0x260]
	ldr r1, [r2, #0x0]
	mov r0, #0x0
	add r1, r1, #0x2200
	strh r0, [r1, #0x80]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x68]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26a]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26b]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x82]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0xf8]
	bl WcmInitOption
	bl WCMi_InitCpsif
	bl OS_IsTickAvailable
	cmp r0, #0x0
	bne _020A7F70
	bl OS_InitTick
_020A7F70:
	bl OS_IsAlarmAvailable
	cmp r0, #0x0
	bne _020A7F80
	bl OS_InitAlarm
_020A7F80:
	ldr r1, _020A7FA8 ; =wcmw
	ldr r0, _020A7FAC ; =0x000022CC
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	bl OS_CreateAlarm
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A7FA8: .word wcmw
_020A7FAC: .word 0x000022CC
