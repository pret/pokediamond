	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global helper_threads_priority
helper_threads_priority: ; 0x02106218
	.byte 0x10, 0x00, 0x00, 0x00

	.global mac_broadcast
mac_broadcast: ; 0x0210621C
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00

	.global UNK_02106224
UNK_02106224: ; 0x02106224
	.asciz "NintendoDS"

	.balign 4, 0
	.global UNK_02106230
UNK_02106230: ; 0x02106230
	.byte 0xAA, 0xAA, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .bss

	.global wfailed
wfailed: ; 0x021C8EA8
	.space 0x4

	.global ip_conflict
ip_conflict: ; 0x021C8EAC
	.space 0x4

	.global mymss
mymss: ; 0x021C8EB0
	.space 0x4

	.global UNK_021C8EB4
UNK_021C8EB4: ; 0x021C8EB4
	.space 0x4

	.global ipid
ipid: ; 0x021C8EB8
	.space 0x4

	.global eport
eport: ; 0x021C8EBC
	.space 0x4

	.global CPSNoIpReason
CPSNoIpReason: ; 0x021C8EC0
	.space 0x4

	.global mode
mode: ; 0x021C8EC4
	.space 0x4

	.global CPSiAlloc
CPSiAlloc: ; 0x021C8EC8
	.space 0x4

	.global dhcp_callback
dhcp_callback: ; 0x021C8ECC
	.space 0x4

	.global CPSNetMask
CPSNetMask: ; 0x021C8ED0
	.space 0x4

	.global CPSDhcpServerIp
CPSDhcpServerIp: ; 0x021C8ED4
	.space 0x4

	.global yield_wait
yield_wait: ; 0x021C8ED8
	.space 0x4

	.global wlan_putpnt
wlan_putpnt: ; 0x021C8EDC
	.space 0x4

	.global CPSGatewayIp
CPSGatewayIp: ; 0x021C8EE0
	.space 0x4

	.global wlan_getpnt
wlan_getpnt: ; 0x021C8EE4
	.space 0x4

	.global offered_myip
offered_myip: ; 0x021C8EE8
	.space 0x4

	.global UNK_021C8EEC
UNK_021C8EEC: ; 0x021C8EEC
	.space 0x4

	.global scavenger_callback
scavenger_callback: ; 0x021C8EF0
	.space 0x4

	.global CPSiFree
CPSiFree: ; 0x021C8EF4
	.space 0x4

	.global scavenger_force_exit
scavenger_force_exit: ; 0x021C8EF8
	.space 0x4

	.global link_is_on
link_is_on: ; 0x021C8EFC
	.space 0x4

	.global lease_time
lease_time: ; 0x021C8F00
	.space 0x4

	.global CPSMyIp
CPSMyIp: ; 0x021C8F04
	.space 0x4

	.global receiver_thread
receiver_thread: ; 0x021C8F08
	.space 0x4

	.global wlan_buf
wlan_buf: ; 0x021C8F0C
	.space 0x4

	.global wlan_buflen
wlan_buflen: ; 0x021C8F10
	.space 0x4

	.global CPSMyMac
CPSMyMac: ; 0x021C8F14
	.space 0x8

	.global CPSDnsIp
CPSDnsIp: ; 0x021C8F1C
	.space 0x8

	.global CPSiRand32ctx
CPSiRand32ctx: ; 0x021C8F24
	.space 0x18

	.global tmpbuf
tmpbuf: ; 0x021C8F3C
	.space 0x3C

	.global arpcache
arpcache: ; 0x021C8F78
	.space 0x60

	.global scavenger_soc
scavenger_soc: ; 0x021C8FD8
	.space 0x64

	.global tmpsoc
tmpsoc: ; 0x021C903C
	.space 0x64

	.global scavenger_thread
scavenger_thread: ; 0x021C90A0
	.space 0xc0

	.global tcpip_thread
tcpip_thread: ; 0x021C9160
	.space 0xc0

	.global scavenger_sndbuf
scavenger_sndbuf: ; 0x021C9220
	.space 0x180

	.global scavenger_rcvbuf
scavenger_rcvbuf: ; 0x021C93A0
	.space 0x180

	.global fragtable
fragtable: ; 0x021C9520
	.space 0x1c0

	.global scavenger_stack
scavenger_stack: ; 0x021C96E0
	.space 0x800

	.global tcpip_stack
tcpip_stack: ; 0x021C9EE0
	.space 0x800

	.text

	arm_func_start CPS_Resolve
CPS_Resolve: ; 0x0209AB80
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	ldr r6, _0209ACC0 ; =CPSiRand32ctx
	mov r9, #0x0
	ldr r11, [r6, #0x8]
	ldr r2, [r6, #0x0]
	ldr r1, [r6, #0x4]
	umull r5, r4, r11, r2
	mla r4, r11, r1, r4
	ldr r10, [r6, #0xc]
	ldr r3, [r6, #0x10]
	mla r4, r10, r2, r4
	adds r5, r3, r5
	ldr r1, [r6, #0x14]
	umull r8, r7, r11, r5
	adc r4, r1, r4
	mla r7, r11, r4, r7
	mla r7, r10, r5, r7
	mov r2, r9, lsl #0x10
	adds r8, r3, r8
	str r5, [r6, #0x0]
	adc r5, r1, r7
	mov r3, r9, lsl #0x10
	orr r2, r2, r4, lsr #0x10
	str r4, [r6, #0x4]
	orr r3, r3, r5, lsr #0x10
	add r1, sp, #0x4
	mov r10, r0
	strh r2, [sp, #0x8]
	str r8, [r6, #0x0]
	str r5, [r6, #0x4]
	strh r3, [sp, #0xa]
	bl rawip
	cmp r0, #0x0
	ldrne r0, [sp, #0x4]
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	mov r0, #0x1
	ldr r6, _0209ACC4 ; =CPSDnsIp
	strb r0, [sp, #0x0]
	strb r0, [sp, #0x1]
	add r5, sp, #0x8
	mov r4, r9
	mov r11, r9
_0209AC34:
	mov r8, r11
	add r7, sp, #0x0
_0209AC3C:
	ldrb r0, [r7, #0x0]
	cmp r0, #0x0
	beq _0209AC80
	mov r0, r8, lsl #0x1
	ldrh r2, [r5, r0]
	ldr r1, [r6, r8, lsl #0x2]
	mov r0, r10
	bl resolve_sub
	str r0, [sp, #0x4]
	cmp r0, #0x0
	beq _0209AC74
	mvn r1, #0x0
	cmp r0, r1
	bne _0209AC9C
_0209AC74:
	mvn r1, #0x0
	cmp r0, r1
	streqb r4, [r7, #0x0]
_0209AC80:
	add r8, r8, #0x1
	cmp r8, #0x2
	add r7, r7, #0x1
	blt _0209AC3C
	add r9, r9, #0x1
	cmp r9, #0x3
	blt _0209AC34
_0209AC9C:
	ldr r1, [sp, #0x4]
	mvn r0, #0x0
	cmp r1, r0
	moveq r0, #0x0
	streq r0, [sp, #0x4]
	ldr r0, [sp, #0x4]
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209ACC0: .word CPSiRand32ctx
_0209ACC4: .word CPSDnsIp

	arm_func_start resolve_sub
resolve_sub: ; 0x0209ACC8
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	movs r5, r1
	mov r6, r0
	mov r4, r2
	addeq sp, sp, #0x8
	mvneq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl CPS_SocUse
	bl CPS_SocDatagramMode
	mov r2, r5
	mov r0, #0x0
	mov r1, #0x35
	bl CPS_SocPingMode
	mov r0, r6
	mov r2, r4
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r1, #0x1
	bl resolve_common
	mov r4, r0
	bl CPS_SocRelease
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start rawip
rawip:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r6, #0x0
	mov r8, r0
	mov r7, r1
	mov r5, r6
	add r4, sp, #0x0
_0209AD50:
	mov r0, r8
	mov r1, r4
	mov r6, r6, lsl #0x8
	bl strtol10
	ldr r2, [sp, #0x0]
	cmp r8, r2
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r8, r2
	cmp r0, #0xff
	bhi _0209ADB0
	cmp r5, #0x3
	beq _0209AD9C
	ldrb r1, [r2, #0x0]
	add r8, r2, #0x1
	cmp r1, #0x2e
	bne _0209ADB0
_0209AD9C:
	cmp r5, #0x3
	bne _0209ADC0
	ldrb r1, [r8, #0x0]
	cmp r1, #0x0
	beq _0209ADC0
_0209ADB0:
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209ADC0:
	add r5, r5, #0x1
	cmp r5, #0x4
	orr r6, r6, r0
	blt _0209AD50
	str r6, [r7, #0x0]
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start strtol10
strtol10: ; 0x0209ADE4
	str r0, [r1, #0x0]
	mov r12, #0x0
	mov r2, #0xa
_0209ADF0:
	ldrb r3, [r0, #0x0]
	sub r3, r3, #0x30
	and r3, r3, #0xff
	cmp r3, #0x9
	mlals r12, r2, r12, r3
	addls r0, r0, #0x1
	strls r0, [r1, #0x0]
	bls _0209ADF0
	mov r0, r12
	bx lr

	arm_func_start resolve_common
resolve_common: ; 0x0209AE18
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4c
	mov r9, r2
	mov r2, r9, asr #0x8
	mov r10, r1
	orr r1, r2, r9, lsl #0x8
	strh r1, [sp, #0x10]
	cmp r10, #0x20
	mov r5, #0x0
	movne r1, #0x1
	strneh r1, [sp, #0x12]
	ldreq r1, _0209B0C8 ; =0x00001001
	strh r5, [sp, #0x16]
	streqh r1, [sp, #0x12]
	mov r1, #0x100
	strh r1, [sp, #0x14]
	add r1, sp, #0x1c
	strh r5, [sp, #0x18]
	strh r5, [sp, #0x1a]
	str r5, [sp, #0xc]
	ldrb r6, [r0], #0x1
	str r3, [sp, #0x0]
	ldr r8, [sp, #0x70]
	add r2, r1, #0x1
	cmp r6, #0x0
	beq _0209AED8
	add r4, sp, #0x10
_0209AE84:
	cmp r6, #0x2e
	beq _0209AEB8
	sub r3, r2, r4
	cmp r3, #0x3c
	addge sp, sp, #0x4c
	mvnge r0, #0x0
	ldmgeia sp!, {r4-r11,lr}
	bxge lr
	strb r6, [r2], #0x1
	ldr r3, [sp, #0xc]
	add r3, r3, #0x1
	str r3, [sp, #0xc]
	b _0209AECC
_0209AEB8:
	ldr r3, [sp, #0xc]
	strb r3, [r1, #0x0]
	mov r1, r2
	str r5, [sp, #0xc]
	add r2, r2, #0x1
_0209AECC:
	ldrb r6, [r0], #0x1
	cmp r6, #0x0
	bne _0209AE84
_0209AED8:
	ldr r0, [sp, #0xc]
	mov r3, #0x0
	strb r0, [r1, #0x0]
	strb r3, [r2, #0x0]
	mov r0, r10, lsr #0x8
	strb r0, [r2, #0x1]
	strb r10, [r2, #0x2]
	strb r3, [r2, #0x3]
	mov r3, #0x1
	add r0, sp, #0x10
	add r1, r2, #0x5
	sub r1, r1, r0
	strb r3, [r2, #0x4]
	bl CPS_SocWrite
	mov r6, #0x0
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	mov r0, #0x2
	str r0, [sp, #0x8]
	mov r0, #0x1
	orr r5, r5, r1, lsl #0x10
	str r0, [sp, #0x4]
	mvn r11, #0x0
	b _0209B084
_0209AF38:
	bl CPS_SocGetLength
	cmp r0, #0x0
	bne _0209AF4C
	bl OS_YieldThread__
	b _0209B084
_0209AF4C:
	add r0, sp, #0xc
	bl CPS_SocRead
	ldr r1, [sp, #0xc]
	cmp r1, #0xc
	bls _0209B07C
	ldrh r3, [r0, #0x0]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r9, r2, lsr #0x10
	bne _0209B07C
	ldrb r2, [r0, #0x3]
	and r2, r2, #0xf
	cmp r2, #0x3
	moveq r6, r11
	beq _0209B07C
	cmp r2, #0x0
	bne _0209B07C
	ldrb r2, [r0, #0x4]
	add r4, r0, r1
	ldrb r1, [r0, #0x5]
	add r0, r0, #0xc
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	movs r1, r1, lsr #0x10
	sub r7, r1, #0x1
	beq _0209AFCC
_0209AFB8:
	bl dns_skipname
	cmp r7, #0x0
	add r0, r0, #0x4
	sub r7, r7, #0x1
	bne _0209AFB8
_0209AFCC:
	cmp r0, r4
	bhs _0209B07C
_0209AFD4:
	bl dns_skipname
	ldrb r7, [r0, #0x8]
	ldrb r1, [r0, #0x9]
	ldrb r3, [r0, #0x0]
	ldrb r2, [r0, #0x1]
	orr r1, r1, r7, lsl #0x8
	mov r1, r1, lsl #0x10
	orr r3, r2, r3, lsl #0x8
	mov r2, r1, lsr #0x10
	mov r1, r3, lsl #0x10
	cmp r10, r1, lsr #0x10
	bne _0209B06C
	cmp r10, #0xc
	beq _0209B04C
	add r1, r0, #0x6
	add r3, r1, r2
	add r4, r0, #0x8
	ldrb r1, [r1, r2]
	ldrb r0, [r3, #0x1]
	add r3, r4, r2
	ldrb r2, [r4, r2]
	orr r0, r0, r1, lsl #0x8
	ldrb r1, [r3, #0x1]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	orr r0, r1, r2, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r6, r1, r0, lsr #0x10
	b _0209B07C
_0209B04C:
	cmp r2, r8
	ldrhi r6, [sp, #0x8]
	bhi _0209B07C
	ldr r1, [sp, #0x0]
	add r0, r0, #0xa
	bl MI_CpuCopy8
	ldr r6, [sp, #0x4]
	b _0209B07C
_0209B06C:
	add r1, r2, #0xa
	add r0, r0, r1
	cmp r0, r4
	blo _0209AFD4
_0209B07C:
	ldr r0, [sp, #0xc]
	bl CPS_SocConsume
_0209B084:
	ldr r0, _0209B0CC ; =link_is_on
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209B0B8
	cmp r6, #0x0
	bne _0209B0B8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	blt _0209AF38
_0209B0B8:
	mov r0, r6
	add sp, sp, #0x4c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209B0C8: .word 0x00001001
_0209B0CC: .word link_is_on

	arm_func_start dns_skipname
dns_skipname:
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	bxeq lr
_0209B0DC:
	and r1, r2, #0xc0
	cmp r1, #0xc0
	addeq r0, r0, #0x1
	bxeq lr
	add r0, r0, r2
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	bne _0209B0DC
	bx lr

	arm_func_start dhcp_release_server
dhcp_release_server: ; 0x0209B100
	stmdb sp!, {r4,lr}
	bl CPS_SocUse
	bl CPS_SocDatagramMode
	ldr r1, _0209B168 ; =CPSDhcpServerIp
	mov r0, #0x44
	ldr r2, [r1, #0x0]
	mov r1, #0x43
	bl CPS_SocPingMode
	ldr r4, _0209B16C ; =scavenger_sndbuf + 0x2A
	mov r1, #0x7
	mov r0, r4
	mov r2, #0x0
	bl dhcp_setcommon
	mov r1, #0xff
	add r2, r0, #0x1
	strb r1, [r0, #0x0]
	mov r0, #0x0
	mov r1, #0x12c
	sub r3, r2, r4
	bl pad_mem
	sub r1, r0, r4
	mov r0, r4
	bl CPS_SocWrite
	bl CPS_SocRelease
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209B168: .word CPSDhcpServerIp
_0209B16C: .word scavenger_sndbuf + 0x2A

	arm_func_start dhcp_request_server
dhcp_request_server:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r5, r0
	bl CPS_SocUse
	bl CPS_SocDatagramMode
	cmp r4, #0x1
	bne _0209B1A8
	ldr r1, _0209B28C ; =CPSDhcpServerIp
	mov r0, #0x44
	ldr r2, [r1, #0x0]
	mov r1, #0x43
	bl CPS_SocPingMode
	b _0209B1B8
_0209B1A8:
	mov r0, #0x44
	mov r1, #0x43
	mvn r2, #0x0
	bl CPS_SocPingMode
_0209B1B8:
	mov r6, #0x0
_0209B1BC:
	mov r0, r4
	bl dhcp_send_request
	mov r1, r6
	bl dhcp_analyze_response
	movs r7, r0
	bne _0209B1E0
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _0209B1BC
_0209B1E0:
	bl CPS_SocRelease
	cmp r7, #0x2
	bne _0209B224
	ldr r0, _0209B290 ; =lease_time
	mov r1, #0x3
	ldr r3, [r0, #0x0]
	ldr r2, _0209B294 ; =UNK_021C8EEC
	mov r3, r3, lsr #0x1
	str r3, [r5, #0x0]
	ldr r3, [r0, #0x0]
	add sp, sp, #0x4
	mul r1, r3, r1
	mov r1, r1, lsr #0x3
	str r1, [r2, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209B224:
	ldr r1, _0209B294 ; =UNK_021C8EEC
	cmp r4, #0x1
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x1
	str r0, [r1, #0x0]
	str r0, [r5, #0x0]
	beq _0209B24C
	cmp r4, #0x2
	beq _0209B270
	b _0209B27C
_0209B24C:
	cmp r0, #0x3c
	bhs _0209B27C
	mov r2, #0x1
	ldr r0, _0209B290 ; =lease_time
	str r2, [r5, #0x0]
	ldr r0, [r0, #0x0]
	mov r0, r0, lsr #0x3
	str r0, [r1, #0x0]
	b _0209B27C
_0209B270:
	cmp r0, #0x3c
	movcc r0, #0x1
	strcc r0, [r5, #0x0]
_0209B27C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209B28C: .word CPSDhcpServerIp
_0209B290: .word lease_time
_0209B294: .word UNK_021C8EEC

	arm_func_start dhcp_discover_server
dhcp_discover_server:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl CPS_SocUse
	bl CPS_SocDatagramMode
	mov r0, #0x44
	mov r1, #0x43
	mvn r2, #0x0
	bl CPS_SocPingMode
	mov r4, #0x0
_0209B2BC:
	bl dhcp_send_discover
	mov r1, r4
	bl dhcp_analyze_response
	mov r5, r0
	cmp r5, #0x1
	beq _0209B2E0
	add r4, r4, #0x1
	cmp r4, #0x4
	blt _0209B2BC
_0209B2E0:
	bl CPS_SocRelease
	cmp r5, #0x1
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start dhcp_analyze_response
dhcp_analyze_response: ; 0x0209B2FC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	add r2, r1, #0x1
	mov r1, #0xf
	mul r1, r2, r1
	str r1, [sp, #0x8]
	str r0, [sp, #0x0]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x4]
	orr r0, r0, r1, lsl #0x10
	mov r4, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x3
	mov r9, r4
	ldr r5, _0209B698 ; =CPSDnsIp
	mov r7, #0x2
	mov r8, #0x1
	ldr fp, _0209B69C ; =CPSGatewayIp
	ldr r6, _0209B6A0 ; =CPSNetMask
	str r0, [sp, #0xc]
	b _0209B64C
_0209B354:
	bl CPS_SocGetLength
	cmp r0, #0x0
	bne _0209B368
	bl OS_YieldThread__
	b _0209B64C
_0209B368:
	add r0, sp, #0x10
	bl CPS_SocRead
	mov r10, r0
	ldr r0, [sp, #0x10]
	cmp r0, #0xf0
	bls _0209B644
	ldrb r0, [r10, #0x0]
	cmp r0, #0x2
	bne _0209B644
	ldrh r1, [r10, #0x6]
	ldrh r2, [r10, #0x4]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r1, r0, lsl #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	orr r1, r0, r1, lsr #0x10
	ldr r0, [sp, #0x0]
	cmp r0, r1
	bne _0209B644
	ldr r1, _0209B6A4 ; =CPSMyMac
	add r0, r10, #0x1c
	bl maccmp
	cmp r0, #0x0
	bne _0209B644
	ldrb r3, [r10, #0x10]
	ldrb r0, [r10, #0x11]
	ldrb r2, [r10, #0x12]
	ldrb r1, [r10, #0x13]
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	orr r1, r1, r2, lsl #0x8
	mov r0, r0, lsr #0x10
	mov r2, r0, lsl #0x10
	mov r0, r1, lsl #0x10
	orr r0, r2, r0, lsr #0x10
	ldrb r2, [r10, #0xec]
	ldr r1, [sp, #0x10]
	ldr r4, [sp, #0xc]
	add r1, r10, r1
	cmp r2, #0x63
	bne _0209B644
	ldrb r2, [r10, #0xed]
	cmp r2, #0x82
	bne _0209B644
	ldrb r2, [r10, #0xee]
	cmp r2, #0x53
	bne _0209B644
	add r2, r10, #0xf0
	ldrb r3, [r10, #0xef]
	cmp r3, #0x63
	bne _0209B644
	b _0209B630
_0209B448:
	cmp r3, #0x0
	beq _0209B630
	cmp r3, #0x33
	bgt _0209B48C
	cmp r3, #0x33
	bge _0209B588
	cmp r3, #0x6
	bgt _0209B624
	cmp r3, #0x1
	blt _0209B624
	cmp r3, #0x1
	beq _0209B4AC
	cmp r3, #0x3
	beq _0209B4E0
	cmp r3, #0x6
	beq _0209B514
	b _0209B624
_0209B48C:
	cmp r3, #0x35
	bgt _0209B4A0
	cmp r3, #0x35
	beq _0209B5C0
	b _0209B624
_0209B4A0:
	cmp r3, #0x36
	beq _0209B5F0
	b _0209B624
_0209B4AC:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r6, #0x0]
	b _0209B624
_0209B4E0:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r11, #0x0]
	b _0209B624
_0209B514:
	ldrb r3, [r2, #0x0]
	cmp r3, #0x8
	strcc r9, [r5, #0x4]
	blo _0209B554
	ldrb lr, [r2, #0x5]
	ldrb r12, [r2, #0x6]
	ldrb r10, [r2, #0x7]
	ldrb r3, [r2, #0x8]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r5, #0x4]
_0209B554:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r3, r10, r3, lsr #0x10
	str r3, [r5, #0x0]
	b _0209B624
_0209B588:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r10, r10, r3, lsr #0x10
	ldr r3, _0209B6A8 ; =lease_time
	str r10, [r3, #0x0]
	b _0209B624
_0209B5C0:
	ldrb r3, [r2, #0x1]
	cmp r3, #0x2
	beq _0209B5E0
	cmp r3, #0x5
	ldreq r3, _0209B6AC ; =CPSMyIp
	moveq r4, r7
	streq r0, [r3, #0x0]
	b _0209B624
_0209B5E0:
	ldr r3, _0209B6B0 ; =offered_myip
	mov r4, r8
	str r0, [r3, #0x0]
	b _0209B624
_0209B5F0:
	ldrb lr, [r2, #0x1]
	ldrb r12, [r2, #0x2]
	ldrb r10, [r2, #0x3]
	ldrb r3, [r2, #0x4]
	orr r12, r12, lr, lsl #0x8
	mov r12, r12, lsl #0x10
	orr r3, r3, r10, lsl #0x8
	mov r10, r12, lsr #0x10
	mov r10, r10, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r10, r10, r3, lsr #0x10
	ldr r3, _0209B6B4 ; =CPSDhcpServerIp
	str r10, [r3, #0x0]
_0209B624:
	ldrb r3, [r2, #0x0]
	add r3, r3, #0x1
	add r2, r2, r3
_0209B630:
	cmp r2, r1
	bhs _0209B644
	ldrb r3, [r2], #0x1
	cmp r3, #0xff
	bne _0209B448
_0209B644:
	ldr r0, [sp, #0x10]
	bl CPS_SocConsume
_0209B64C:
	ldr r0, _0209B6B8 ; =link_is_on
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209B688
	cmp r4, #0x0
	bne _0209B688
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x4]
	orr r2, r2, r1, lsl #0x10
	sub r1, r2, r0
	ldr r0, [sp, #0x8]
	cmp r1, r0
	blt _0209B354
_0209B688:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209B698: .word CPSDnsIp
_0209B69C: .word CPSGatewayIp
_0209B6A0: .word CPSNetMask
_0209B6A4: .word CPSMyMac
_0209B6A8: .word lease_time
_0209B6AC: .word CPSMyIp
_0209B6B0: .word offered_myip
_0209B6B4: .word CPSDhcpServerIp
_0209B6B8: .word link_is_on

	arm_func_start dhcp_send_request
dhcp_send_request: ; 0x0209B6BC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, _0209B7CC ; =scavenger_sndbuf + 0x2A
	mov r5, r0
	add r2, sp, #0x0
	mov r0, r4
	mov r1, #0x3
	bl dhcp_setcommon
	mov r12, r0
	cmp r5, #0x0
	bne _0209B790
	mov r0, #0x32
	strb r0, [r12, #0x0]
	mov r0, #0x4
	ldr r3, _0209B7D0 ; =offered_myip
	strb r0, [r12, #0x1]
	ldr r1, [r3, #0x0]
	mov lr, #0x36
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #0x8
	strb r1, [r12, #0x2]
	ldr r1, [r3, #0x0]
	ldr r2, _0209B7D4 ; =CPSDhcpServerIp
	mov r1, r1, lsr #0x10
	strb r1, [r12, #0x3]
	ldr r1, [r3, #0x0]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #0x8
	strb r1, [r12, #0x4]
	ldr r1, [r3, #0x0]
	strb r1, [r12, #0x5]
	strb lr, [r12, #0x6]
	strb r0, [r12, #0x7]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x8]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsr #0x10
	strb r0, [r12, #0x9]
	ldr r0, [r2, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0xa]
	ldr r0, [r2, #0x0]
	strb r0, [r12, #0xb]
	add r12, r12, #0xc
_0209B790:
	add r2, r12, #0x1
	mov lr, #0xff
	sub r3, r2, r4
	mov r0, #0x0
	mov r1, #0x12c
	strb lr, [r12, #0x0]
	bl pad_mem
	mov r1, r0
	mov r0, r4
	sub r1, r1, r4
	bl CPS_SocWrite
	ldr r0, [sp, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209B7CC: .word scavenger_sndbuf + 0x2A
_0209B7D0: .word offered_myip
_0209B7D4: .word CPSDhcpServerIp

	arm_func_start dhcp_send_discover
dhcp_send_discover: ; 0x0209B7D8
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r4, _0209B898 ; =scavenger_sndbuf + 0x2A
	add r2, sp, #0x0
	mov r0, r4
	mov r1, #0x1
	bl dhcp_setcommon
	ldr r1, _0209B89C ; =offered_myip
	mov r12, r0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _0209B85C
	mov r0, #0x32
	strb r0, [r12, #0x0]
	mov r0, #0x4
	strb r0, [r12, #0x1]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x2]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsr #0x10
	strb r0, [r12, #0x3]
	ldr r0, [r1, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #0x8
	strb r0, [r12, #0x4]
	ldr r0, [r1, #0x0]
	strb r0, [r12, #0x5]
	add r12, r12, #0x6
_0209B85C:
	add r2, r12, #0x1
	mov lr, #0xff
	sub r3, r2, r4
	mov r0, #0x0
	mov r1, #0x12c
	strb lr, [r12, #0x0]
	bl pad_mem
	mov r1, r0
	mov r0, r4
	sub r1, r1, r4
	bl CPS_SocWrite
	ldr r0, [sp, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209B898: .word scavenger_sndbuf + 0x2A
_0209B89C: .word offered_myip

	arm_func_start pad_mem
pad_mem: ; 0x0209B8A0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r12, r0
	mov r5, r2
	cmp r3, r1
	bhs _0209B8D0
	sub r4, r1, r3
	mov r0, r5
	mov r1, r12
	mov r2, r4
	bl MI_CpuFill8
	add r5, r5, r4
_0209B8D0:
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start dhcp_setcommon
dhcp_setcommon: ; 0x0209B8E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r1, #0x0
	mov r2, #0xec
	mov r6, r0
	bl MI_CpuFill8
	ldr r0, _0209BA5C ; =0x00000101
	mov r1, #0x6
	strh r0, [r6, #0x0]
	ldr r0, _0209BA60 ; =CPSiRand32ctx
	strb r1, [r6, #0x2]
	ldr r3, [r0, #0x8]
	ldr r2, [r0, #0x0]
	ldr r1, [r0, #0x4]
	umull lr, r12, r3, r2
	mla r12, r3, r1, r12
	ldr r1, [r0, #0xc]
	ldr r7, [r0, #0x10]
	mla r12, r1, r2, r12
	adds r3, r7, lr
	ldr r1, [r0, #0x14]
	str r3, [r0, #0x0]
	adc r1, r1, r12
	str r1, [r0, #0x4]
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	cmp r4, #0x0
	mov r2, r3, asr #0x8
	mov r0, r1, lsl #0x10
	strne r1, [r4, #0x0]
	mov r1, r0, lsr #0x10
	orr r2, r2, r3, lsl #0x8
	mov r0, r1, asr #0x8
	strh r2, [r6, #0x4]
	orr r0, r0, r1, lsl #0x8
	strh r0, [r6, #0x6]
	ldr r2, _0209BA64 ; =CPSMyIp
	ldr r0, _0209BA68 ; =CPSMyMac
	ldr r1, [r2, #0x0]
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	strh r1, [r6, #0xc]
	ldr r2, [r2, #0x0]
	add r1, r6, #0x1c
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
	mov r2, r3, asr #0x8
	orr r3, r2, r3, lsl #0x8
	mov r2, #0x6
	strh r3, [r6, #0xe]
	bl MI_CpuCopy8
	ldr r0, _0209BA6C ; =0x00008263
	ldr r1, _0209BA70 ; =0x00006353
	strh r0, [r6, #0xec]
	strh r1, [r6, #0xee]
	ldr r0, _0209BA74 ; =0x00000135
	mov r1, #0x7
	strh r0, [r6, #0xf0]
	strb r5, [r6, #0xf2]
	mov r0, #0x3d
	strb r0, [r6, #0xf3]
	strb r1, [r6, #0xf4]
	mov r3, #0x1
	ldr r0, _0209BA68 ; =CPSMyMac
	add r1, r6, #0xf6
	mov r2, #0x6
	strb r3, [r6, #0xf5]
	bl MI_CpuCopy8
	mov r1, #0xc
	strb r1, [r6, #0xfc]
	mov r2, #0xa
	ldr r0, _0209BA78 ; =UNK_02106224
	add r1, r6, #0xfe
	strb r2, [r6, #0xfd]
	bl MI_CpuCopy8
	mov r1, #0x37
	strb r1, [r6, #0x108]
	mov r2, #0x3
	ldr r0, _0209BA7C ; =0x0000010D
	strb r2, [r6, #0x109]
	mov r1, #0x1
	strb r1, [r6, #0x10a]
	strb r2, [r6, #0x10b]
	mov r1, #0x6
	strb r1, [r6, #0x10c]
	add r0, r6, r0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209BA5C: .word 0x00000101
_0209BA60: .word CPSiRand32ctx
_0209BA64: .word CPSMyIp
_0209BA68: .word CPSMyMac
_0209BA6C: .word 0x00008263
_0209BA70: .word 0x00006353
_0209BA74: .word 0x00000135
_0209BA78: .word UNK_02106224
_0209BA7C: .word 0x0000010D

	arm_func_start scavenger
scavenger: ; 0x0209BA80
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x54
	ldr r3, _0209BE40 ; =scavenger_force_exit
	mov r1, #0x0
	ldr r0, _0209BE44 ; =scavenger_soc
	mov r2, #0x64
	str r1, [r3, #0x0]
	bl MI_CpuFill8
	ldr r0, _0209BE44 ; =scavenger_soc
	mov r3, #0x180
	ldr r2, _0209BE48 ; =scavenger_rcvbuf
	ldr r1, _0209BE4C ; =scavenger_sndbuf
	str r3, [r0, #0x3c]
	str r2, [r0, #0x40]
	str r3, [r0, #0x48]
	str r1, [r0, #0x4c]
	bl CPS_SocRegister
	mov r11, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	str r0, [sp, #0x4c]
	mov r1, r0
	ldr r0, _0209BE50 ; =CPSNoIpReason
	ldr r5, [sp, #0x0]
	str r1, [r0, #0x0]
	mov r0, #0x2
	str r0, [sp, #0x10]
	mov r0, r5
	str r0, [sp, #0x34]
	str r0, [sp, #0x3c]
	mov r0, #0x3
	str r0, [sp, #0x1c]
	mov r0, r5
	str r0, [sp, #0x30]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	str r0, [sp, #0xc]
	mov r0, #0x69
	str r0, [sp, #0x44]
	mov r0, #0x3e8
	mov r6, r11
	mov r4, r11
	mov r10, r11
	str r11, [sp, #0x14]
	str r11, [sp, #0x18]
	str r11, [sp, #0x38]
	str r11, [sp, #0x2c]
	str r11, [sp, #0x40]
	str r11, [sp, #0x48]
	str r0, [sp, #0x8]
_0209BB50:
	ldr r0, [sp, #0x8]
	bl OS_Sleep
	ldr r0, _0209BE40 ; =scavenger_force_exit
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0209BE14
	bl OS_GetTick
	mov r9, r0, lsr #0x10
	ldr r0, _0209BE54 ; =link_is_on
	orr r9, r9, r1, lsl #0x10
	ldr r0, [r0, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209BC8C
	ldr r0, [sp, #0x4c]
	subs r0, r0, #0x1
	str r0, [sp, #0x4c]
	bne _0209BCA4
	ldr r0, _0209BE58 ; =mode
	ldr r0, [r0, #0x0]
	ands r0, r0, #0x1
	beq _0209BBBC
	cmp r11, #0x0
	bne _0209BCA4
	bl set_fixed_ip
	ldr r11, [sp, #0xc]
	b _0209BCA4
_0209BBBC:
	cmp r11, #0x3
	addls pc, pc, r11, lsl #0x2
	b _0209BCA4
_0209BBC8: ; jump table
	b _0209BBD8 ; case 0
	b _0209BC28 ; case 1
	b _0209BC4C ; case 2
	b _0209BCA4 ; case 3
_0209BBD8:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrne r1, [sp, #0x10]
	ldrne r0, _0209BE50 ; =CPSNoIpReason
	strne r1, [r0, #0x0]
	ldrne r0, [sp, #0x14]
	strne r0, [sp, #0x4]
	bl dhcp_discover_server
	cmp r0, #0x0
	beq _0209BC14
	ldr r1, [sp, #0x18]
	add r0, sp, #0x4c
	bl dhcp_request_server
	cmp r0, #0x0
	bne _0209BC20
_0209BC14:
	bl set_fixed_ip
	ldr r11, [sp, #0x1c]
	b _0209BCA4
_0209BC20:
	ldr r11, [sp, #0x20]
	b _0209BCA4
_0209BC28:
	ldr r1, [sp, #0x24]
	add r0, sp, #0x4c
	bl dhcp_request_server
	cmp r0, #0x0
	bne _0209BCA4
	ldr r0, [sp, #0x4c]
	cmp r0, #0x3c
	ldrcc r11, [sp, #0x10]
	b _0209BCA4
_0209BC4C:
	ldr r1, [sp, #0x10]
	add r0, sp, #0x4c
	bl dhcp_request_server
	cmp r0, #0x0
	ldrne r11, [sp, #0x28]
	bne _0209BCA4
	ldr r0, [sp, #0x4c]
	cmp r0, #0x3c
	bhs _0209BCA4
	ldr r0, [sp, #0x1c]
	bl reset_network_vars
	ldr r0, [sp, #0x30]
	ldr r11, [sp, #0x2c]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x0]
	b _0209BCA4
_0209BC8C:
	ldr r0, [sp, #0x34]
	bl reset_network_vars
	ldr r0, [sp, #0x3c]
	ldr r11, [sp, #0x38]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x0]
_0209BCA4:
	ldr r1, [sp, #0x40]
	ldr r0, _0209BE5C ; =arpcache
_0209BCAC:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _0209BCD4
	ldrh r2, [r0, #0xa]
	sub r2, r9, r2
	mov r2, r2, lsl #0x10
	mov r3, r2, asr #0x10
	ldr r2, _0209BE60 ; =0x000003BD
	cmp r3, r2
	strgt r6, [r0, #0x0]
_0209BCD4:
	add r0, r0, #0xc
	add r1, r1, #0x1
	cmp r1, #0x8
	blt _0209BCAC
	ldr r0, _0209BE64 ; =CPSGatewayIp
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209BD10
	ldr r1, [sp, #0x0]
	subs r1, r1, #0x1
	str r1, [sp, #0x0]
	bne _0209BD10
	bl send_arprequest
	ldr r0, [sp, #0x44]
	str r0, [sp, #0x0]
_0209BD10:
	ldr r0, _0209BE68 ; =OSi_ThreadInfo
	ldr r7, [r0, #0x8]
	cmp r7, #0x0
	beq _0209BDAC
_0209BD20:
	ldr r0, [r7, #0xa4]
	cmp r0, #0x0
	beq _0209BDA0
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0209BDA0
	ldrb r2, [r0, #0x8]
	cmp r2, #0x3
	bne _0209BD6C
	ldr r1, [r0, #0x10]
	sub r1, r9, r1
	cmp r1, #0x27
	ble _0209BD6C
	strb r5, [r0, #0x8]
	ldrh r1, [r0, #0x1a]
	strh r1, [r0, #0x18]
	ldr r1, [r0, #0x20]
	str r1, [r0, #0x1c]
	b _0209BDA0
_0209BD6C:
	cmp r2, #0x2
	bne _0209BDA0
	ldr r1, [r0, #0x10]
	sub r1, r9, r1
	cmp r1, #0x27
	ble _0209BDA0
	ldr r1, [r0, #0x4]
	cmp r1, #0x1
	bne _0209BDA0
	strb r4, [r0, #0x8]
	str r4, [r0, #0x4]
	ldr r0, [r0, #0x0]
	bl OS_WakeupThreadDirect
_0209BDA0:
	ldr r7, [r7, #0x68]
	cmp r7, #0x0
	bne _0209BD20
_0209BDAC:
	ldr r7, [sp, #0x48]
	ldr r8, _0209BE6C ; =fragtable
_0209BDB4:
	ldrh r0, [r8, #0x4]
	cmp r0, #0x0
	beq _0209BDE4
	ldr r0, [r8, #0x2c]
	sub r0, r9, r0
	cmp r0, #0xef
	ble _0209BDE4
	ldr r1, _0209BE70 ; =CPSiFree
	ldr r0, [r8, #0x34]
	ldr r1, [r1, #0x0]
	blx r1
	strh r10, [r8, #0x4]
_0209BDE4:
	add r8, r8, #0x38
	add r7, r7, #0x1
	cmp r7, #0x8
	blt _0209BDB4
	mov r0, r9
	bl CPSi_SslPeriodical
	ldr r0, _0209BE74 ; =scavenger_callback
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209BB50
	blx r0
	b _0209BB50
_0209BE14:
	ldr r0, _0209BE58 ; =mode
	ldr r0, [r0, #0x0]
	ands r0, r0, #0x1
	bne _0209BE30
	cmp r11, #0x3
	beq _0209BE30
	bl dhcp_release_server
_0209BE30:
	bl CPS_SocUnRegister
	add sp, sp, #0x54
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209BE40: .word scavenger_force_exit
_0209BE44: .word scavenger_soc
_0209BE48: .word scavenger_rcvbuf
_0209BE4C: .word scavenger_sndbuf
_0209BE50: .word CPSNoIpReason
_0209BE54: .word link_is_on
_0209BE58: .word mode
_0209BE5C: .word arpcache
_0209BE60: .word 0x000003BD
_0209BE64: .word CPSGatewayIp
_0209BE68: .word OSi_ThreadInfo
_0209BE6C: .word fragtable
_0209BE70: .word CPSiFree
_0209BE74: .word scavenger_callback

	arm_func_start set_fixed_ip
set_fixed_ip: ; 0x0209BE78
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r0, _0209BF3C ; =dhcp_callback
	ldr r0, [r0, #0x0]
	blx r0
	ldr r0, _0209BF40 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl send_arprequest
	mov r0, #0x64
	bl OS_Sleep
	ldr r0, _0209BF40 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	bl send_arprequest
	bl OS_GetTick
	mov r4, r0, lsr #0x10
	orr r4, r4, r1, lsl #0x10
	ldr r6, _0209BF44 ; =ip_conflict
	mov r7, #0x64
	ldr r5, _0209BF48 ; =link_is_on
	b _0209BF00
_0209BED8:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x0
	beq _0209BEF8
	mov r0, #0x4
	bl reset_network_vars
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209BEF8:
	mov r0, r7
	bl OS_Sleep
_0209BF00:
	ldr r0, [r5, #0x0]
	blx r0
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r4
	cmp r0, #0x17
	blt _0209BED8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209BF3C: .word dhcp_callback
_0209BF40: .word CPSMyIp
_0209BF44: .word ip_conflict
_0209BF48: .word link_is_on

	arm_func_start CPS_SocGetChar
CPS_SocGetChar: ; 0x0209BF4C
	stmdb sp!, {r4,lr}
	ldr r0, _0209BF98 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r4, #0x60]
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r2, #0x0
	ldr r0, [r4, #0x5c]
	mov r3, r2
	bl CPSi_SocWrite2
	mov r0, #0x0
	str r0, [r4, #0x60]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209BF98: .word OSi_ThreadInfo

	arm_func_start CPS_SocGetLength
CPS_SocGetLength:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209C02C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	beq _0209C01C
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209BFD4
	bl CPSi_SslGetLength
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209BFD4:
	ldr r1, [r0, #0x44]
	cmp r1, #0x0
	bne _0209BFFC
	ldrb r0, [r0, #0x8]
	cmp r0, #0x4
	beq _0209BFFC
	add r0, r0, #0xf6
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209C00C
_0209BFFC:
	add sp, sp, #0x4
	mov r0, r1
	ldmia sp!, {lr}
	bx lr
_0209C00C:
	add sp, sp, #0x4
	mvn r0, #0x0
	ldmia sp!, {lr}
	bx lr
_0209C01C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C02C: .word OSi_ThreadInfo

	arm_func_start CPS_SocWrite
CPS_SocWrite:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r3, _0209C0E4 ; =OSi_ThreadInfo
	mov r2, r0
	ldr r4, [r3, #0x4]
	mov r3, r1
	ldr r5, [r4, #0xa4]
	cmp r5, #0x0
	beq _0209C0D4
	ldr r4, [r5, #0x60]
	cmp r4, #0x0
	beq _0209C0BC
	ldr r0, [r5, #0x5c]
	mov r1, r4
	bl CPSi_SocWrite2
	ldr r1, [r5, #0x60]
	mov r4, r0
	cmp r4, r1
	movcs r0, #0x0
	strcs r0, [r5, #0x60]
	addcs sp, sp, #0x4
	subcs r0, r4, r1
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	ldr r0, [r5, #0x5c]
	sub r2, r1, r4
	add r1, r0, r4
	bl memmove
	ldr r1, [r5, #0x60]
	add sp, sp, #0x4
	sub r1, r1, r4
	mov r0, #0x0
	str r1, [r5, #0x60]
	ldmia sp!, {r4-r5,lr}
	bx lr
_0209C0BC:
	mov r2, #0x0
	mov r3, r2
	bl CPSi_SocWrite2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_0209C0D4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209C0E4: .word OSi_ThreadInfo

	arm_func_start CPSi_SocWrite2
CPSi_SocWrite2:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _0209C1CC ; =OSi_ThreadInfo
	mov r7, r1
	ldr r12, [r12, #0x4]
	mov r6, r2
	ldr r4, [r12, #0xa4]
	mov r5, r3
	cmp r4, #0x0
	beq _0209C1BC
	ldrb r12, [r4, #0x8]
	cmp r12, #0xa
	bne _0209C14C
	cmp r7, #0x0
	beq _0209C12C
	mov r2, r4
	bl send_udp
_0209C12C:
	cmp r5, #0x0
	beq _0209C144
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl send_udp
_0209C144:
	add r0, r7, r5
	b _0209C1A4
_0209C14C:
	cmp r12, #0xb
	bne _0209C184
	cmp r7, #0x0
	beq _0209C164
	mov r2, r4
	bl send_ping
_0209C164:
	cmp r5, #0x0
	beq _0209C17C
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl send_ping
_0209C17C:
	add r0, r7, r5
	b _0209C1A4
_0209C184:
	ldrb r12, [r4, #0x9]
	cmp r12, #0x0
	beq _0209C19C
	str r4, [sp, #0x0]
	bl CPSi_SslWrite2
	b _0209C1A4
_0209C19C:
	str r4, [sp, #0x0]
	bl CPSi_TcpWrite2Raw
_0209C1A4:
	ldr r1, _0209C1D0 ; =wfailed
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0209C1BC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209C1CC: .word OSi_ThreadInfo
_0209C1D0: .word wfailed

	arm_func_start CPSi_TcpWrite2Raw
CPSi_TcpWrite2Raw:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	mov r4, #0x0
	mov r10, r0
	ldr r8, [sp, #0x40]
	mov r0, r4
	str r4, [sp, #0xc]
	mov r9, r1
	mov r11, r2
	str r3, [sp, #0x8]
	mov r6, r4
	str r0, [r8, #0x34]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x10]
	orr r0, r0, r1, lsl #0x10
	str r0, [sp, #0x10]
	mov r0, r6
	str r0, [sp, #0x18]
	mov r0, #0x1
	ldr r4, _0209C3EC ; =link_is_on
	str r0, [sp, #0x14]
	b _0209C39C
_0209C230:
	ldr r7, [r8, #0x28]
	ldr r3, [sp, #0x8]
	str r8, [sp, #0x0]
	mov r0, r10
	mov r1, r9
	mov r2, r11
	str r6, [sp, #0x4]
	bl tcp_write_do2
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	orr r5, r5, r1, lsl #0x10
_0209C25C:
	bl OS_YieldThread__
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C2B8
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C2B8
	ldr r1, [r8, #0x28]
	ldr r0, [r8, #0x30]
	cmp r1, r0
	beq _0209C2B8
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	bge _0209C2B8
	cmp r6, #0x0
	beq _0209C25C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	beq _0209C25C
_0209C2B8:
	ldr r0, [r8, #0x30]
	subs r7, r0, r7
	ldr r0, [sp, #0xc]
	add r0, r0, r7
	str r0, [sp, #0xc]
	beq _0209C2E4
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	str r0, [sp, #0x10]
	orr r0, r0, r1, lsl #0x10
	str r0, [sp, #0x10]
_0209C2E4:
	ldr r0, [r8, #0x30]
	str r0, [r8, #0x28]
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C36C
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	bne _0209C36C
	cmp r7, #0x0
	bne _0209C36C
	cmp r6, #0x0
	bne _0209C370
	bl OS_GetTick
	mov r5, r0, lsr #0x10
	orr r5, r5, r1, lsl #0x10
	b _0209C334
_0209C324:
	bl OS_YieldThread__
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	bne _0209C35C
_0209C334:
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C35C
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r5
	cmp r0, #0xf
	blt _0209C324
_0209C35C:
	ldrh r0, [r8, #0x2c]
	cmp r0, #0x0
	ldreq r6, [sp, #0x14]
	b _0209C370
_0209C36C:
	ldr r6, [sp, #0x18]
_0209C370:
	cmp r7, r9
	addcc r10, r10, r7
	subcc r9, r9, r7
	blo _0209C39C
	sub r1, r7, r9
	add r10, r11, r1
	ldr r0, [sp, #0x8]
	ldr r11, [sp, #0x18]
	sub r9, r0, r1
	mov r0, r11
	str r0, [sp, #0x8]
_0209C39C:
	ldr r0, [r4, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C3DC
	cmp r9, #0x0
	beq _0209C3DC
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	bne _0209C3DC
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x10]
	orr r2, r2, r1, lsl #0x10
	sub r0, r2, r0
	cmp r0, #0x9f
	blt _0209C230
_0209C3DC:
	ldr r0, [sp, #0xc]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209C3EC: .word link_is_on

	arm_func_start tcp_write_do2
tcp_write_do2: ; 0x0209C3F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r4, r3
	ldr r2, [sp, #0x10]
	ldr r3, [sp, #0x14]
	bl tcp_write_do
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [sp, #0x10]
	mov r0, r5
	mov r1, r4
	mov r3, #0x0
	bl tcp_write_do
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start tcp_write_do
tcp_write_do:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r8, r2
	ldr r11, [r8, #0x34]
	mov r10, r0
	movs r0, r3
	mov r0, r11, lsl #0x1
	movne r6, #0x1
	add r5, r0, #0x4
	mov r0, #0x18
	str r3, [sp, #0x4]
	mov r9, r1
	ldreqh r6, [r8, #0x2c]
	mov r4, #0x0
	str r0, [sp, #0x8]
	b _0209C504
_0209C48C:
	ldr r0, _0209C528 ; =mymss
	ldrh r7, [r8, #0x2e]
	ldrh r0, [r0, #0x0]
	ldr r1, [r8, #0x34]
	cmp r7, r6
	movcs r7, r6
	cmp r0, r7
	movcc r7, r0
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	biceq r7, r7, #0x1
	cmp r9, r7
	sub r0, r1, r11
	movcc r7, r9
	adds r0, r5, r0
	moveq r7, r4
	mov r11, r1
	sub r5, r0, #0x1
	cmp r7, #0x0
	beq _0209C518
	ldr r3, [sp, #0x8]
	mov r0, r10
	mov r1, r7
	mov r2, r8
	str r4, [sp, #0x0]
	sub r6, r6, r7
	bl send_tcp
	bl OS_YieldThread
	add r10, r10, r7
	sub r9, r9, r7
_0209C504:
	cmp r9, #0x0
	beq _0209C518
	ldrb r0, [r8, #0x8]
	cmp r0, #0x4
	beq _0209C48C
_0209C518:
	mov r0, r7
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209C528: .word mymss

	arm_func_start CPS_SocConsume
CPS_SocConsume: ; 0x0209C52C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209C57C ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r2, [r1, #0x9]
	cmp r2, #0x0
	beq _0209C56C
	bl CPSi_SslConsume
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C56C:
	bl CPSi_SocConsumeRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C57C: .word OSi_ThreadInfo

	arm_func_start CPSi_SocConsumeRaw
CPSi_SocConsumeRaw:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r7, r0
	bl OS_DisableInterrupts
	ldr r2, [r4, #0x44]
	ldr r1, [r4, #0x3c]
	mov r6, r0
	cmp r2, r1
	mov r5, #0x0
	bne _0209C5B4
	cmp r7, #0x0
	movne r5, #0x1
_0209C5B4:
	cmp r7, r2
	movcs r0, #0x0
	strcs r0, [r4, #0x44]
	bhs _0209C5D8
	ldr r0, [r4, #0x40]
	sub r2, r2, r7
	add r1, r0, r7
	str r2, [r4, #0x44]
	bl memmove
_0209C5D8:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldrb r0, [r4, #0x8]
	cmp r0, #0xa
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r0, #0xb
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	beq _0209C620
	cmp r5, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
_0209C620:
	mov r0, r4
	mov r1, #0x1b
	bl tck_send_ack
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start CPS_SocRead
CPS_SocRead:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209C6BC ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	beq _0209C6A4
	ldrb r2, [r1, #0x8]
	add r2, r2, #0xf6
	and r2, r2, #0xff
	cmp r2, #0x1
	bhi _0209C678
	bl udp_read_raw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C678:
	ldrb r2, [r1, #0x9]
	cmp r2, #0x0
	beq _0209C694
	bl CPSi_SslRead
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C694:
	bl CPSi_TcpReadRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C6A4:
	mov r1, #0x0
	str r1, [r0, #0x0]
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C6BC: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpReadRaw
CPSi_TcpReadRaw: ; 0x0209C6C0
	stmdb sp!, {r4-r8,lr}
	mov r4, r1
	ldr r1, [r4, #0x44]
	mov r5, r0
	cmp r1, #0x0
	bne _0209C728
	ldrb r0, [r4, #0x8]
	cmp r0, #0x4
	bne _0209C728
	bl OS_DisableInterrupts
	mov r8, r0
	mov r7, #0x2
	mov r6, #0x0
	b _0209C704
_0209C6F8:
	mov r0, r6
	str r7, [r4, #0x4]
	bl OS_SleepThread
_0209C704:
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209C71C
	ldrb r0, [r4, #0x8]
	cmp r0, #0x4
	beq _0209C6F8
_0209C71C:
	mov r0, r8
	bl OS_RestoreInterrupts
	b _0209C72C
_0209C728:
	bl OS_YieldThread
_0209C72C:
	ldr r0, [r4, #0x44]
	str r0, [r5, #0x0]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	ldrne r0, [r4, #0x40]
	moveq r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start udp_read_raw
udp_read_raw: ; 0x0209C74C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r1
	mov r9, r0
	bl OS_DisableInterrupts
	ldr r7, [r8, #0x44]
	mov r6, r0
	cmp r7, #0x0
	bne _0209C790
	mov r5, #0x3
	mov r4, #0x0
_0209C778:
	mov r0, r4
	str r5, [r8, #0x4]
	bl OS_SleepThread
	ldr r7, [r8, #0x44]
	cmp r7, #0x0
	beq _0209C778
_0209C790:
	mov r0, r6
	bl OS_RestoreInterrupts
	str r7, [r9, #0x0]
	ldr r0, [r8, #0x40]
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start CPS_TcpClose
CPS_TcpClose: ; 0x0209C7AC
	stmdb sp!, {r4-r6,lr}
	ldr r0, _0209C838 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrb r0, [r4, #0x9]
	cmp r0, #0x0
	beq _0209C7DC
	mov r0, r4
	bl CPSi_SslClose
_0209C7DC:
	bl OS_GetTick
	mov r6, r0, lsr #0x10
	orr r6, r6, r1, lsl #0x10
	ldr r5, _0209C83C ; =link_is_on
	b _0209C7F4
_0209C7F0:
	bl OS_YieldThread__
_0209C7F4:
	ldr r0, [r5, #0x0]
	blx r0
	cmp r0, #0x0
	beq _0209C828
	ldrb r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0209C828
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	sub r0, r0, r6
	cmp r0, #0x27
	blt _0209C7F0
_0209C828:
	mov r0, #0x0
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209C838: .word OSi_ThreadInfo
_0209C83C: .word link_is_on

	arm_func_start CPS_TcpShutdown
CPS_TcpShutdown:
	stmdb sp!, {r4,lr}
	ldr r0, _0209C880 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r4, [r0, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrb r0, [r4, #0x9]
	cmp r0, #0x0
	beq _0209C870
	mov r0, r4
	bl CPSi_SslShutdown
_0209C870:
	mov r0, r4
	bl CPSi_TcpShutdownRaw
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209C880: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpShutdownRaw
CPSi_TcpShutdownRaw: ; 0x0209C884
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_YieldThread
	ldrb r1, [r4, #0x8]
	add r0, r1, #0xfd
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209C8C0
	mov r0, r4
	mov r1, #0x19
	bl tck_send_finack
	mov r0, #0x7
	strb r0, [r4, #0x8]
	ldmia sp!, {r4,lr}
	bx lr
_0209C8C0:
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	mov r1, #0x1a
	bl tck_send_ack
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start CPS_SocWho
CPS_SocWho: ; 0x0209C8E0
	ldr r2, _0209C930 ; =OSi_ThreadInfo
	ldr r2, [r2, #0x4]
	ldr r3, [r2, #0xa4]
	cmp r3, #0x0
	beq _0209C928
	ldrb r2, [r3, #0x8]
	cmp r2, #0x4
	beq _0209C908
	cmp r2, #0xa
	bne _0209C928
_0209C908:
	cmp r0, #0x0
	ldrneh r2, [r3, #0x18]
	strneh r2, [r0, #0x0]
	cmp r1, #0x0
	ldrne r0, [r3, #0x14]
	strne r0, [r1, #0x0]
	ldr r0, [r3, #0x1c]
	bx lr
_0209C928:
	mov r0, #0x0
	bx lr
	.balign 4
_0209C930: .word OSi_ThreadInfo

	arm_func_start CPS_TcpConnect
CPS_TcpConnect: ; 0x0209C934
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209C98C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	beq _0209C97C
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209C96C
	bl CPSi_SslConnect
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C96C:
	bl CPSi_TcpConnectRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209C97C:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209C98C: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpConnectRaw
CPSi_TcpConnectRaw:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	bl get_seqno
	mov r8, r0
	mov r9, #0x0
	mov r11, r9
	mov r4, #0x1
	mov r6, #0x2
	mov r5, #0x18
_0209C9B8:
	str r8, [r10, #0x28]
	strb r6, [r10, #0x8]
	bl OS_GetTick
	mov r2, r0, lsr #0x10
	orr r2, r2, r1, lsl #0x10
	str r2, [r10, #0x10]
	mov r0, r10
	mov r1, r6
	mov r2, r5
	bl tcp_send_handshake
	bl OS_DisableInterrupts
	mov r7, r0
	ldr r0, _0209CA50 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209CA04
	mov r0, r11
	str r4, [r10, #0x4]
	bl OS_SleepThread
_0209CA04:
	mov r0, r7
	bl OS_RestoreInterrupts
	ldrb r0, [r10, #0x8]
	cmp r0, #0x4
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r0, _0209CA50 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0209CA40
	add r9, r9, #0x1
	cmp r9, #0x3
	blo _0209C9B8
_0209CA40:
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209CA50: .word CPSMyIp

	arm_func_start CPS_TcpListen
CPS_TcpListen: ; 0x0209CA54
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _0209CAA4 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r0, [r0, #0xa4]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrb r1, [r0, #0x9]
	cmp r1, #0x0
	beq _0209CA94
	bl CPSi_SslListen
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209CA94:
	bl CPSi_TcpListenRaw
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209CAA4: .word OSi_ThreadInfo

	arm_func_start CPS_SetUdpCallback
CPS_SetUdpCallback:
	ldr r1, _0209CAC0 ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	cmp r1, #0x0
	strne r0, [r1, #0x38]
	bx lr
	.balign 4
_0209CAC0: .word OSi_ThreadInfo

	arm_func_start CPSi_TcpListenRaw
CPSi_TcpListenRaw: ; 0x0209CAC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl get_seqno
	str r0, [r5, #0x28]
	mov r0, #0x1
	strb r0, [r5, #0x8]
	bl OS_DisableInterrupts
	mov r4, r0
	mov r1, #0x1
	mov r0, #0x0
	str r1, [r5, #0x4]
	bl OS_SleepThread
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start CPS_SocDup
CPS_SocDup: ; 0x0209CB0C
	ldr r1, _0209CB20 ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	ldr r1, [r1, #0xa4]
	str r1, [r0, #0xa4]
	bx lr
	.balign 4
_0209CB20: .word OSi_ThreadInfo

	arm_func_start CPS_SocRelease
CPS_SocRelease: ; 0x0209CB24
	ldr r0, _0209CB40 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
	bx lr
	.balign 4
_0209CB40: .word OSi_ThreadInfo

	arm_func_start CPS_SocUse
CPS_SocUse: ; 0x0209CB44
	ldr r0, _0209CB74 ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	bxeq lr
	str r0, [r1, #0x0]
	mov r0, #0x0
	strb r0, [r1, #0x8]
	str r0, [r1, #0x44]
	str r0, [r1, #0x60]
	str r0, [r1, #0x38]
	bx lr
	.balign 4
_0209CB74: .word OSi_ThreadInfo

	arm_func_start CPS_SocPingMode
CPS_SocPingMode: ; 0x0209CB78
	stmdb sp!, {r4,lr}
	ldr r3, _0209CBDC ; =OSi_ThreadInfo
	ldr r3, [r3, #0x4]
	ldr r4, [r3, #0xa4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r3, _0209CBE0 ; =0x7F000001
	cmp r2, r3
	ldreq r2, _0209CBE4 ; =CPSMyIp
	ldreq r2, [r2, #0x0]
	cmp r0, #0x0
	strh r1, [r4, #0x1a]
	ldrh r1, [r4, #0x1a]
	strh r1, [r4, #0x18]
	str r2, [r4, #0x20]
	ldr r1, [r4, #0x20]
	str r1, [r4, #0x1c]
	strneh r0, [r4, #0xa]
	ldmneia sp!, {r4,lr}
	bxne lr
	bl CPS_SocGetEport
	strh r0, [r4, #0xa]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209CBDC: .word OSi_ThreadInfo
_0209CBE0: .word 0x7F000001
_0209CBE4: .word CPSMyIp

	arm_func_start CPS_SocDatagramMode
CPS_SocDatagramMode: ; 0x0209CBE8
	ldr r0, _0209CC0C ; =OSi_ThreadInfo
	ldr r0, [r0, #0x4]
	ldr r1, [r0, #0xa4]
	cmp r1, #0x0
	movne r0, #0xa
	strneb r0, [r1, #0x8]
	movne r0, #0x0
	strne r0, [r1, #0x44]
	bx lr
	.balign 4
_0209CC0C: .word OSi_ThreadInfo

	arm_func_start CPS_SocUnRegister
CPS_SocUnRegister: ; 0x0209CC10
	ldr r0, _0209CC24 ; =OSi_ThreadInfo
	mov r1, #0x0
	ldr r0, [r0, #0x4]
	str r1, [r0, #0xa4]
	bx lr
	.balign 4
_0209CC24: .word OSi_ThreadInfo

	arm_func_start CPS_SocRegister
CPS_SocRegister: ; 0x0209CC28
	ldr r1, _0209CC38 ; =OSi_ThreadInfo
	ldr r1, [r1, #0x4]
	str r0, [r1, #0xa4]
	bx lr
	.balign 4
_0209CC38: .word OSi_ThreadInfo

	arm_func_start get_seqno
get_seqno: ; 0x0209CC3C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _0209CC88 ; =CPSiRand32ctx
	ldr r3, [r1, #0x8]
	ldr r2, [r1, #0x0]
	ldr r0, [r1, #0x4]
	umull lr, r12, r3, r2
	mla r12, r3, r0, r12
	ldr r0, [r1, #0xc]
	ldr r3, [r1, #0x10]
	mla r12, r0, r2, r12
	adds r2, r3, lr
	ldr r0, [r1, #0x14]
	str r2, [r1, #0x0]
	adc r0, r0, r12
	str r0, [r1, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209CC88: .word CPSiRand32ctx

	arm_func_start CPS_SocGetEport
CPS_SocGetEport: ; 0x0209CC8C
	stmdb sp!, {r4-r8,lr}
	ldr r0, _0209CD30 ; =OSi_ThreadInfo
	ldr r6, [r0, #0x8]
	ldr r2, _0209CD34 ; =eport
	mov r4, #0x400
	mov r3, #0x1
	mov r5, #0x0
	ldr r1, _0209CD38 ; =0x00001388
_0209CCAC:
	ldrh r12, [r2, #0x0]
	mov r0, r5
	add r12, r12, #0x1
	strh r12, [r2, #0x0]
	ldrh r12, [r2, #0x0]
	cmp r12, #0x400
	blo _0209CCD0
	cmp r12, r1
	blo _0209CCD4
_0209CCD0:
	strh r4, [r2, #0x0]
_0209CCD4:
	mov r8, r6
	cmp r6, #0x0
	beq _0209CD18
	ldrh r7, [r2, #0x0]
_0209CCE4:
	ldr lr, [r8, #0xa4]
	cmp lr, #0x0
	beq _0209CD0C
	ldr r12, [lr, #0x0]
	cmp r12, #0x0
	beq _0209CD0C
	ldrh r12, [lr, #0xa]
	cmp r12, r7
	moveq r0, r3
	beq _0209CD18
_0209CD0C:
	ldr r8, [r8, #0x68]
	cmp r8, #0x0
	bne _0209CCE4
_0209CD18:
	cmp r0, #0x0
	bne _0209CCAC
	ldr r0, _0209CD34 ; =eport
	ldrh r0, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209CD30: .word OSi_ThreadInfo
_0209CD34: .word eport
_0209CD38: .word 0x00001388

	arm_func_start tcpip
tcpip: ; 0x0209CD3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r5, _0209CDAC ; =0x00000806
	add r4, sp, #0x0
_0209CD4C:
	mov r0, r4
	bl receive_packet
	ldr r3, [sp, #0x0]
	cmp r3, #0x22
	bls _0209CDA4
	ldrh r2, [r0, #0xc]
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	cmp r1, #0x800
	beq _0209CD88
	cmp r1, r5
	beq _0209CD98
	b _0209CDA4
_0209CD88:
	add r0, r0, #0xe
	sub r1, r3, #0xe
	bl dispatch_ip
	b _0209CDA4
_0209CD98:
	add r0, r0, #0xe
	sub r1, r3, #0xe
	bl dispatch_arp
_0209CDA4:
	bl throw_packet
	b _0209CD4C
	.balign 4
_0209CDAC: .word 0x00000806

	arm_func_start dispatch_ip
dispatch_ip: ; 0x0209CDB0
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldrh r12, [r4, #0xc]
	ldrh r6, [r4, #0x10]
	ldrh r2, [r4, #0xe]
	ldrh r0, [r4, #0x12]
	mov r5, r6, asr #0x8
	mov r3, r12, asr #0x8
	orr r5, r5, r6, lsl #0x8
	orr r12, r3, r12, lsl #0x8
	mov r3, r5, lsl #0x10
	mov r5, r0, asr #0x8
	mov r12, r12, lsl #0x10
	mov lr, r2, asr #0x8
	mov r6, r3, lsr #0x10
	orr r0, r5, r0, lsl #0x8
	mov r3, r12, lsr #0x10
	orr r2, lr, r2, lsl #0x8
	mov r5, r6, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r0, r5, r0, lsr #0x10
	orr r2, r3, r2, lsr #0x10
	mov r5, r1
	cmp r0, r2
	beq _0209CEF0
	bl ip_isme
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r1, [r4, #0x2]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r5, r0, lsr #0x10
	addcc sp, sp, #0x8
	ldmccia sp!, {r4-r6,lr}
	bxcc lr
	ldrb r1, [r4, #0x0]
	mov r0, r4
	and r1, r1, #0xf
	mov r1, r1, lsl #0x2
	bl calc_checksum
	ldr r1, _0209CFA0 ; =0x0000FFFF
	cmp r0, r1
	addne sp, sp, #0x8
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrh r2, [r4, #0x10]
	ldrh r12, [r4, #0x12]
	ldr r1, _0209CFA4 ; =CPSMyIp
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	ldr r1, [r1, #0x0]
	orr r0, r2, r0, lsr #0x10
	cmp r1, r0
	bne _0209CEF0
	ldrh r2, [r4, #0xc]
	ldrh r12, [r4, #0xe]
	sub r0, r4, #0x8
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	mov r2, #0x1
	bl reg_arprequest
_0209CEF0:
	add r1, sp, #0x0
	mov r0, r4
	bl check_frag
	movs r4, r0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r2, [r4, #0x2]
	ldrb r3, [r4, #0x0]
	ldrb r12, [r4, #0x9]
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	and r3, r3, #0xf
	mov r2, r1, lsr #0x10
	cmp r12, #0x11
	add r1, r4, r3, lsl #0x2
	sub r2, r2, r3, lsl #0x2
	bne _0209CF44
	bl dispatch_udp
	b _0209CF70
_0209CF44:
	ldr r3, _0209CFA4 ; =CPSMyIp
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	beq _0209CF70
	cmp r12, #0x1
	bne _0209CF64
	bl dispatch_icmp
	b _0209CF70
_0209CF64:
	cmp r12, #0x6
	bne _0209CF70
	bl dispatch_tcp
_0209CF70:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r1, _0209CFA8 ; =CPSiFree
	sub r0, r4, #0xe
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209CFA0: .word 0x0000FFFF
_0209CFA4: .word CPSMyIp
_0209CFA8: .word CPSiFree

	arm_func_start check_frag
check_frag: ; 0x0209CFAC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r6, #0x0
	mov r10, r0
	str r6, [r1, #0x0]
	ldrh r3, [r10, #0x6]
	str r1, [sp, #0x0]
	ldr r2, _0209D2A4 ; =0x00003FFF
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [sp, #0x4]
	ands r1, r1, r2
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r1, [r10, #0xc]
	ldrh r3, [r10, #0xe]
	ldrb r4, [r10, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	and r3, r4, #0xf
	ldrh r9, [r10, #0x4]
	mov r2, r2, lsl #0x10
	mov r1, r0, lsl #0x10
	ldr r5, _0209D2A8 ; =fragtable
	mov r0, r6
	mov r7, r3, lsl #0x2
	orr r4, r2, r1, lsr #0x10
_0209D034:
	ldrh r2, [r5, #0x4]
	cmp r2, #0x0
	beq _0209D058
	ldr r1, [r5, #0x0]
	cmp r1, r4
	bne _0209D058
	ldrh r1, [r5, #0x6]
	cmp r1, r9
	beq _0209D078
_0209D058:
	cmp r2, #0x0
	bne _0209D068
	cmp r6, #0x0
	moveq r6, r5
_0209D068:
	add r0, r0, #0x1
	cmp r0, #0x8
	add r5, r5, #0x38
	blo _0209D034
_0209D078:
	ldrh r2, [r10, #0x2]
	cmp r0, #0x8
	ldr r1, _0209D2AC ; =0x00001FFF
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	ldr r0, [sp, #0x4]
	and r8, r0, r1
	sub r0, r2, r7
	str r0, [sp, #0x8]
	mov r0, r8, lsl #0x3
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x8]
	add r11, r0, r8, lsl #0x3
	bne _0209D150
	cmp r6, #0x0
	beq _0209D0C8
	cmp r11, #0x1000
	bls _0209D0D8
_0209D0C8:
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209D0D8:
	ldr r1, _0209D2B0 ; =CPSiAlloc
	ldr r0, _0209D2B4 ; =0x0000100E
	ldr r1, [r1, #0x0]
	add r0, r7, r0
	mov r5, r6
	blx r1
	str r0, [r6, #0x34]
	ldr r0, [r6, #0x34]
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r4, [r6, #0x0]
	strh r9, [r6, #0x6]
	mov r0, #0x0
	strh r0, [r6, #0x8]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r6, #0x2c]
	ldr r1, [r6, #0x34]
	mov r0, r10
	add r1, r1, #0xe
	add r1, r1, r7
	str r1, [r6, #0x30]
	ldr r1, [r6, #0x34]
	mov r2, r7
	add r1, r1, #0xe
	bl MI_CpuCopy8
_0209D150:
	ldrh r0, [r5, #0x4]
	cmp r0, #0x8
	beq _0209D164
	cmp r11, #0x1000
	bls _0209D18C
_0209D164:
	mov r0, #0x0
	strh r0, [r5, #0x4]
	ldr r1, _0209D2B8 ; =CPSiFree
	ldr r0, [r5, #0x34]
	ldr r1, [r1, #0x0]
	blx r1
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_0209D18C:
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x8]
	add r0, r0, #0x7
	add r1, r8, r0, lsr #0x3
	ldr r0, [sp, #0x4]
	ands r0, r0, #0x2000
	streqh r11, [r5, #0xa]
	streqh r1, [r5, #0x8]
	ldrh r3, [r5, #0x4]
	add r0, r10, r7
	add r3, r5, r3, lsl #0x1
	strh r8, [r3, #0xc]
	ldrh r3, [r5, #0x4]
	add r3, r5, r3, lsl #0x1
	strh r1, [r3, #0x1c]
	ldrh r1, [r5, #0x4]
	add r1, r1, #0x1
	strh r1, [r5, #0x4]
	ldr r3, [r5, #0x30]
	ldr r1, [sp, #0xc]
	add r1, r3, r1
	bl MI_CpuCopy8
	ldrh r6, [r5, #0x8]
	cmp r6, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r7, [r5, #0x4]
	mov r3, #0x0
	mov r4, r3
	cmp r7, #0x0
	bls _0209D244
	mov r0, r3
_0209D214:
	add r2, r5, r4, lsl #0x1
	ldrh r1, [r2, #0xc]
	cmp r1, r3
	bhi _0209D238
	ldrh r1, [r2, #0x1c]
	cmp r3, r1
	movcc r3, r1
	movcc r4, r0
	blo _0209D23C
_0209D238:
	add r4, r4, #0x1
_0209D23C:
	cmp r4, r7
	blo _0209D214
_0209D244:
	cmp r3, r6
	addcc sp, sp, #0x14
	movcc r0, #0x0
	ldmccia sp!, {r4-r11,lr}
	bxcc lr
	ldr r0, [r5, #0x34]
	ldrh r3, [r5, #0xa]
	ldrb r1, [r0, #0xe]
	add r0, r0, #0xe
	mov r2, #0x0
	and r1, r1, #0xf
	add r1, r3, r1, lsl #0x2
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r1, r3, asr #0x8
	orr r1, r1, r3, lsl #0x8
	strh r1, [r0, #0x2]
	strh r2, [r5, #0x4]
	ldr r1, [sp, #0x0]
	mov r2, #0x1
	str r2, [r1, #0x0]
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209D2A4: .word 0x00003FFF
_0209D2A8: .word fragtable
_0209D2AC: .word 0x00001FFF
_0209D2B0: .word CPSiAlloc
_0209D2B4: .word 0x0000100E
_0209D2B8: .word CPSiFree

	arm_func_start dispatch_udp
dispatch_udp: ; 0x0209D2BC
	stmdb sp!, {r4-r8,lr}
	mov r6, r1
	ldrh r1, [r6, #0x6]
	mov r7, r0
	mov r5, r2
	cmp r1, #0x0
	beq _0209D2F8
	mov r0, r6
	mov r1, r5
	mov r2, r7
	mov r3, #0x11
	bl check_tcpudpsum
	cmp r0, #0x0
	ldmneia sp!, {r4-r8,lr}
	bxne lr
_0209D2F8:
	bl OS_DisableInterrupts
	ldr r1, _0209D4D4 ; =OSi_ThreadInfo
	mov r8, r0
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0209D4C4
	mvn r12, #0x0
_0209D314:
	ldr r4, [r2, #0xa4]
	cmp r4, #0x0
	beq _0209D4B8
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _0209D4B8
	ldrb r0, [r4, #0x8]
	cmp r0, #0xa
	bne _0209D4B8
	ldrh r3, [r6, #0x2]
	ldrh r1, [r4, #0xa]
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r1, r0, lsr #0x10
	bne _0209D4B8
	ldrh r3, [r4, #0x18]
	cmp r3, #0x0
	beq _0209D378
	ldrh r1, [r6, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	cmp r3, r0, lsr #0x10
	bne _0209D4B8
_0209D378:
	ldr r1, [r4, #0x1c]
	cmp r1, #0x0
	beq _0209D3C0
	cmp r1, r12
	beq _0209D3C0
	ldrh lr, [r7, #0xc]
	ldrh r0, [r7, #0xe]
	mov r3, lr, asr #0x8
	orr r3, r3, lr, lsl #0x8
	mov r3, r3, lsl #0x10
	mov lr, r0, asr #0x8
	mov r3, r3, lsr #0x10
	orr r0, lr, r0, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r3, r0, lsr #0x10
	cmp r1, r0
	bne _0209D4B8
_0209D3C0:
	ldrh r1, [r7, #0x10]
	ldrh r3, [r7, #0x12]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x1c]
	cmp r0, #0x0
	bne _0209D43C
	ldrh r1, [r7, #0xc]
	ldrh r3, [r7, #0xe]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	str r0, [r4, #0x1c]
	ldrh r1, [r6, #0x0]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r4, #0x18]
_0209D43C:
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209D4C4
	ldr r1, [r4, #0x3c]
	sub r0, r5, #0x8
	cmp r0, r1
	strhi r1, [r4, #0x44]
	strls r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	add r0, r6, #0x8
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bne _0209D48C
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	b _0209D4C4
_0209D48C:
	ldr r3, [r4, #0x38]
	cmp r3, #0x0
	beq _0209D4C4
	ldr r0, [r4, #0x40]
	ldr r1, [r4, #0x44]
	mov r2, r4
	blx r3
	cmp r0, #0x0
	movne r0, #0x0
	strne r0, [r4, #0x44]
	b _0209D4C4
_0209D4B8:
	ldr r2, [r2, #0x68]
	cmp r2, #0x0
	bne _0209D314
_0209D4C4:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209D4D4: .word OSi_ThreadInfo

	arm_func_start dispatch_tcp
dispatch_tcp:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	mov r0, r5
	mov r1, r4
	mov r2, r6
	mov r3, #0x6
	bl check_tcpudpsum
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldrb r0, [r5, #0xc]
	ldrb r2, [r5, #0xd]
	and r1, r0, #0xf0
	mov r0, r1, asr #0x1
	add r0, r1, r0, lsr #0x1e
	and r1, r2, #0x17
	cmp r1, #0x10
	sub r4, r4, r0, asr #0x2
	bgt _0209D558
	cmp r1, #0x10
	bge _0209D5C4
	cmp r1, #0x2
	bgt _0209D5F4
	cmp r1, #0x1
	blt _0209D5F4
	cmp r1, #0x1
	beq _0209D5DC
	cmp r1, #0x2
	beq _0209D57C
	b _0209D5F4
_0209D558:
	cmp r1, #0x12
	bgt _0209D5F4
	cmp r1, #0x11
	blt _0209D5F4
	cmp r1, #0x11
	beq _0209D5C4
	cmp r1, #0x12
	beq _0209D5A0
	b _0209D5F4
_0209D57C:
	ands r0, r2, #0x28
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl dt_syn
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5A0:
	ands r0, r2, #0x28
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl dt_synack
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5C4:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl dt_ack
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5DC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl dt_fin
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D5F4:
	ands r0, r2, #0x4
	beq _0209D610
	mov r0, r6
	mov r1, r5
	bl dt_rst
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209D610:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl tcp_send_rst
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start dt_rst
dt_rst: ; 0x0209D62C
	stmdb sp!, {r4,lr}
	bl find_socket
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_YieldThread
	mov r1, #0x0
	strb r1, [r4, #0x8]
	ldr r0, [r4, #0x4]
	sub r0, r0, #0x1
	cmp r0, #0x1
	ldmhiia sp!, {r4,lr}
	bxhi lr
	str r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start dt_fin
dt_fin: ; 0x0209D674
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl find_socket
	movs r4, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrb r1, [r4, #0x8]
	cmp r1, #0x4
	beq _0209D72C
	cmp r1, #0x7
	beq _0209D6BC
	cmp r1, #0x8
	beq _0209D6E4
	b _0209D754
_0209D6BC:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl tck_send_ack
	mov r0, #0x9
	add sp, sp, #0x4
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D6E4:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl tck_send_ack
	mov r1, #0x0
	strb r1, [r4, #0x8]
	ldr r0, [r4, #0x4]
	cmp r0, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	str r1, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D72C:
	ldr r2, [r4, #0x24]
	mov r1, #0x0
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl tck_send_finack
	mov r0, #0x6
	add sp, sp, #0x4
	strb r0, [r4, #0x8]
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209D754:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, #0x0
	bl tcp_send_rst
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start dt_ack
dt_ack: ; 0x0209D774
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl find_socket
	movs r5, r0
	bne _0209D7B4
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, #0x0
	bl tcp_send_rst
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_0209D7B4:
	ldrh r3, [r7, #0x8]
	ldrh r1, [r7, #0xa]
	ldrb r4, [r7, #0xd]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r1, asr #0x8
	mov r2, r2, lsr #0x10
	orr r1, r3, r1, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	str r1, [r5, #0x30]
	ldrh r9, [r7, #0x4]
	ldrh r1, [r7, #0x6]
	ldrb r3, [r5, #0x8]
	mov r2, r9, asr #0x8
	orr r2, r2, r9, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r9, r1, asr #0x8
	mov r2, r2, lsr #0x10
	orr r1, r9, r1, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	cmp r3, #0x4
	orr r2, r2, r1, lsr #0x10
	bne _0209D840
	ldr r1, [r5, #0x24]
	cmp r1, r2
	beq _0209D840
	mov r1, #0x0
	bl tck_send_ack
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_0209D840:
	ldrh r1, [r7, #0xe]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r5, #0x2c]
	ldrb r0, [r5, #0x8]
	cmp r0, #0x9
	addls pc, pc, r0, lsl #0x2
	b _0209DA70
_0209D860: ; jump table
	b _0209D888 ; case 0
	b _0209DA70 ; case 1
	b _0209D888 ; case 2
	b _0209D8A0 ; case 3
	b _0209D8CC ; case 4
	b _0209DA70 ; case 5
	b _0209DA4C ; case 6
	b _0209D9D8 ; case 7
	b _0209D9D8 ; case 8
	b _0209DA4C ; case 9
_0209D888:
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, #0x0
	bl tcp_send_rst
	b _0209DA8C
_0209D8A0:
	mov r0, #0x4
	strb r0, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _0209D8C4
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
_0209D8C4:
	cmp r6, #0x0
	beq _0209DA8C
_0209D8CC:
	ldr r0, [r5, #0x34]
	add r0, r0, #0x1
	str r0, [r5, #0x34]
	ldr r1, [r5, #0x3c]
	ldr r0, [r5, #0x44]
	sub r0, r1, r0
	cmp r6, r0
	movhi r9, #0x0
	movhi r6, r0
	movls r9, #0x1
	cmp r6, #0x0
	beq _0209D968
	bl OS_DisableInterrupts
	ldrb r1, [r7, #0xc]
	ldr r12, [r5, #0x40]
	ldr r3, [r5, #0x44]
	and r2, r1, #0xf0
	mov r1, r2, asr #0x1
	add r1, r2, r1, lsr #0x1e
	mov r8, r0
	mov r2, r6
	add r0, r7, r1, asr #0x2
	add r1, r12, r3
	bl MI_CpuCopy8
	ldr r1, [r5, #0x44]
	mov r0, r8
	add r1, r1, r6
	str r1, [r5, #0x44]
	ldr r1, [r5, #0x24]
	add r1, r1, r6
	str r1, [r5, #0x24]
	bl OS_RestoreInterrupts
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209D968
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
_0209D968:
	cmp r9, #0x0
	beq _0209D9C0
	ands r0, r4, #0x1
	beq _0209D9C0
	mov r0, #0x6
	strb r0, [r5, #0x8]
	ldr r1, [r5, #0x24]
	mov r0, r5
	add r2, r1, #0x1
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl tck_send_finack
	cmp r6, #0x0
	bne _0209DA8C
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209D9C0:
	cmp r6, #0x0
	beq _0209DA8C
	mov r0, r5
	mov r1, #0x0
	bl tck_send_ack
	b _0209DA8C
_0209D9D8:
	ands r0, r4, #0x1
	beq _0209DA20
	ldr r1, [r5, #0x24]
	add r0, r6, #0x1
	add r2, r1, r0
	mov r0, r5
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl tck_send_ack
	mov r1, #0x0
	strb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209DA20:
	cmp r6, #0x0
	beq _0209DA40
	ldr r1, [r5, #0x24]
	mov r0, r5
	add r2, r1, r6
	mov r1, #0x0
	str r2, [r5, #0x24]
	bl tck_send_ack
_0209DA40:
	mov r0, #0x8
	strb r0, [r5, #0x8]
	b _0209DA8C
_0209DA4C:
	mov r1, #0x0
	strb r1, [r5, #0x8]
	ldr r0, [r5, #0x4]
	cmp r0, #0x2
	bne _0209DA8C
	str r1, [r5, #0x4]
	ldr r0, [r5, #0x0]
	bl OS_WakeupThreadDirect
	b _0209DA8C
_0209DA70:
	ands r0, r4, #0x1
	ldrne r0, [r5, #0x24]
	mov r1, #0x0
	addne r0, r0, #0x1
	strne r0, [r5, #0x24]
	mov r0, r5
	bl tck_send_ack
_0209DA8C:
	bl OS_YieldThread
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start dt_synack
dt_synack: ; 0x0209DA9C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r5, r1
	mov r6, r2
	bl find_socket
	movs r4, r0
	beq _0209DAC8
	ldrb r0, [r4, #0x8]
	cmp r0, #0x2
	beq _0209DAE8
_0209DAC8:
	mov r0, r7
	mov r1, r5
	mov r2, r6
	mov r3, #0x0
	bl tcp_send_rst
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209DAE8:
	bl OS_YieldThread
	ldrh r2, [r5, #0x4]
	ldrh r12, [r5, #0x6]
	mov r0, r5
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r12, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r12, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r2, r1, lsr #0x10
	add r1, r1, #0x1
	str r1, [r4, #0x24]
	ldrh r3, [r5, #0x8]
	ldrh lr, [r5, #0xa]
	mov r1, r4
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, lr, asr #0x8
	mov r12, r2, lsr #0x10
	orr r2, r3, lr, lsl #0x8
	mov r3, r12, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	str r2, [r4, #0x30]
	ldrh r3, [r5, #0xe]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	strh r2, [r4, #0x2c]
	bl parse_mss
	mov r0, r4
	mov r1, #0x0
	bl tck_send_ack
	mov r0, #0x4
	strb r0, [r4, #0x8]
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start dt_syn
dt_syn: ; 0x0209DBB0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldrh r12, [r4, #0x10]
	ldrh r7, [r4, #0xc]
	ldrh r3, [r4, #0x12]
	mov r5, r12, asr #0x8
	mov r6, r7, asr #0x8
	orr r5, r5, r12, lsl #0x8
	orr r6, r6, r7, lsl #0x8
	mov r12, r6, lsl #0x10
	ldrh r0, [r4, #0xe]
	mov lr, r5, lsl #0x10
	mov r5, r3, asr #0x8
	mov r6, r0, asr #0x8
	mov r7, r12, lsr #0x10
	orr r0, r6, r0, lsl #0x8
	orr r3, r5, r3, lsl #0x8
	mov r12, lr, lsr #0x10
	mov r6, r7, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r5, r12, lsl #0x10
	mov r3, r3, lsl #0x10
	mov r7, r1
	orr r1, r5, r3, lsr #0x10
	orr r0, r6, r0, lsr #0x10
	mov r5, r2
	bl valid_IP
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, r7
	mov r2, r5
	bl find_specific_socket
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	mov r0, r4
	mov r1, r7
	bl check_listener
	movs r2, r0
	beq _0209DC7C
	mov r0, r4
	mov r1, r7
	bl dt_syn_LISTEN
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209DC7C:
	bl OS_YieldThread
	mov r0, r4
	mov r1, r7
	bl check_listener
	movs r2, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r4
	mov r1, r7
	bl dt_syn_LISTEN
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start find_specific_socket
find_specific_socket:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl find_socket
	movs r2, r0
	beq _0209DD38
	ldrb r0, [r2, #0x8]
	cmp r0, #0x1
	bne _0209DCEC
	mov r0, r6
	mov r1, r5
	bl dt_syn_LISTEN
	b _0209DD2C
_0209DCEC:
	add r0, r0, #0xfd
	and r0, r0, #0xff
	cmp r0, #0x1
	bhi _0209DD18
	ldr r1, [r2, #0x28]
	mov r0, r6
	sub r3, r1, #0x1
	mov r1, r5
	str r3, [r2, #0x28]
	bl dt_syn_LISTEN
	b _0209DD2C
_0209DD18:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl tcp_send_rst
_0209DD2C:
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209DD38:
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start dt_syn_LISTEN
dt_syn_LISTEN: ; 0x0209DD44
	stmdb sp!, {r4-r6,lr}
	mov r4, r2
	mov r2, #0x3
	mov r6, r0
	mov r5, r1
	strb r2, [r4, #0x8]
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	str r0, [r4, #0x10]
	ldrh r2, [r6, #0x10]
	ldrh r3, [r6, #0x12]
	mov r0, r5
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r1, r1, lsr #0x10
	mov r3, r1, lsl #0x10
	mov r1, r2, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	str r1, [r4, #0x14]
	ldrh r3, [r5, #0x0]
	mov r1, r4
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	strh r2, [r4, #0x18]
	ldrh r3, [r6, #0xc]
	ldrh r6, [r6, #0xe]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r6, asr #0x8
	orr r3, r3, r6, lsl #0x8
	mov r2, r2, lsr #0x10
	mov r6, r2, lsl #0x10
	mov r2, r3, lsl #0x10
	orr r2, r6, r2, lsr #0x10
	str r2, [r4, #0x1c]
	ldrh r3, [r5, #0x4]
	ldrh r6, [r5, #0x6]
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	mov r3, r6, asr #0x8
	mov r5, r2, lsr #0x10
	orr r2, r3, r6, lsl #0x8
	mov r3, r5, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	add r2, r2, #0x1
	str r2, [r4, #0x24]
	bl parse_mss
	mov r0, r4
	mov r1, #0x12
	mov r2, #0x0
	bl tcp_send_handshake
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start tcp_send_rst
tcp_send_rst: ; 0x0209DE34
	stmdb sp!, {r4-r8,lr}
	ldr r4, _0209DF6C ; =tmpsoc
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r0, r4
	mov r1, #0x0
	mov r2, #0x64
	mov r5, r3
	bl MI_CpuFill8
	ldrh r2, [r7, #0x2]
	mov r1, r4
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0xa]
	ldrh r2, [r7, #0x0]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0x18]
	ldrh r2, [r8, #0xc]
	ldrh r8, [r8, #0xe]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r2, r8, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r2, r8, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r2, r0, lsr #0x10
	str r0, [r1, #0x1c]
	ldrb r0, [r7, #0xd]
	ands r0, r0, #0x10
	beq _0209DF04
	ldrh r2, [r7, #0x8]
	ldrh r6, [r7, #0xa]
	mov r0, r4
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	mov r1, r1, lsl #0x10
	mov r2, r6, asr #0x8
	mov r3, r1, lsr #0x10
	orr r1, r2, r6, lsl #0x8
	mov r2, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r3, r2, r1, lsr #0x10
	mov r2, r5
	mov r1, #0x4
	str r3, [r4, #0x28]
	bl tcp_send_handshake
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209DF04:
	mov r0, #0x0
	str r0, [r4, #0x28]
	ldrh r1, [r7, #0x4]
	ldrh r3, [r7, #0x6]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r3, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, r3, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	add r0, r6, r0
	str r0, [r4, #0x24]
	ldrb r0, [r7, #0xd]
	mov r2, r5
	mov r1, #0x14
	ands r0, r0, #0x3
	ldrne r0, [r4, #0x24]
	addne r0, r0, #0x1
	strne r0, [r4, #0x24]
	mov r0, r4
	bl tcp_send_handshake
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209DF6C: .word tmpsoc

	arm_func_start tck_send_finack
tck_send_finack:
	ldr ip, _0209DF80 ; =tcp_send_handshake
	mov r2, r1
	mov r1, #0x11
	bx r12
	.balign 4
_0209DF80: .word tcp_send_handshake

	arm_func_start tck_send_ack
tck_send_ack: ; 0x0209DF84
	ldr ip, _0209DF94 ; =tcp_send_handshake
	mov r2, r1
	mov r1, #0x10
	bx r12
	.balign 4
_0209DF94: .word tcp_send_handshake

	arm_func_start tcp_send_handshake
tcp_send_handshake: ; 0x0209DF98
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r6, r0
	ldr r0, [r6, #0x1c]
	mov r5, r1
	mov r4, r2
	bl no_need_inq
	cmp r0, #0x0
	bne _0209DFD0
	ldr r0, _0209E00C ; =OSi_ThreadInfo
	ldr r1, _0209E010 ; =tcpip_thread
	ldr r0, [r0, #0x4]
	cmp r0, r1
	beq _0209DFF4
_0209DFD0:
	mov r0, #0x0
	mov r1, r0
	mov r2, r6
	mov r3, r5
	str r4, [sp, #0x0]
	bl send_tcp
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209DFF4:
	ldr r0, [r6, #0x1c]
	bl get_targetip
	bl send_arprequest
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209E00C: .word OSi_ThreadInfo
_0209E010: .word tcpip_thread

	arm_func_start no_need_inq
no_need_inq:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl get_targetip
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x1
	ldmeqia sp!, {lr}
	bxeq lr
	bl inq_arpcache
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start parse_mss
parse_mss: ; 0x0209E044
	mov r2, #0x218
	strh r2, [r1, #0x2e]
	ldrb r2, [r0, #0xc]
	add r3, r0, #0x14
	and r2, r2, #0xf0
	mov r0, r2, asr #0x1
	add r0, r2, r0, lsr #0x1e
	mov r0, r0, asr #0x2
	subs r0, r0, #0x14
	sub r12, r0, #0x1
	bxeq lr
_0209E070:
	ldrb r0, [r3], #0x1
	cmp r0, #0x0
	bxeq lr
	cmp r0, #0x1
	beq _0209E0B8
	cmp r0, #0x2
	bne _0209E0A8
	ldrb r2, [r3, #0x1]
	ldrb r0, [r3, #0x2]
	add r3, r3, #0x3
	sub r12, r12, #0x3
	orr r0, r0, r2, lsl #0x8
	strh r0, [r1, #0x2e]
	b _0209E0B8
_0209E0A8:
	ldrb r0, [r3, #0x0]
	sub r0, r0, #0x1
	sub r12, r12, r0
	add r3, r3, r0
_0209E0B8:
	cmp r12, #0x0
	sub r12, r12, #0x1
	bne _0209E070
	bx lr

	arm_func_start find_socket
find_socket: ; 0x0209E0C8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r2, _0209E140 ; =OSi_ThreadInfo
	mov r7, r0
	ldr r4, [r2, #0x8]
	mov r6, r1
	cmp r4, #0x0
	beq _0209E130
_0209E0E8:
	ldr r5, [r4, #0xa4]
	cmp r5, #0x0
	beq _0209E124
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0209E124
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl check_socket
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, r5
	ldmneia sp!, {r4-r7,lr}
	bxne lr
_0209E124:
	ldr r4, [r4, #0x68]
	cmp r4, #0x0
	bne _0209E0E8
_0209E130:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E140: .word OSi_ThreadInfo

	arm_func_start check_socket
check_socket:
	stmdb sp!, {r4-r6,lr}
	ldrb r4, [r2, #0x8]
	mov r12, #0x0
	mov r3, r12
	mov r6, r12
	mov r5, r12
	cmp r4, #0xa
	beq _0209E16C
	cmp r4, #0xb
	movne r5, #0x1
_0209E16C:
	cmp r5, #0x0
	beq _0209E190
	ldrh lr, [r1, #0x2]
	ldrh r5, [r2, #0xa]
	mov r4, lr, asr #0x8
	orr r4, r4, lr, lsl #0x8
	mov lr, r4, lsl #0x10
	cmp r5, lr, lsr #0x10
	moveq r6, #0x1
_0209E190:
	cmp r6, #0x0
	beq _0209E1B4
	ldrh r4, [r1, #0x0]
	ldrh lr, [r2, #0x18]
	mov r1, r4, asr #0x8
	orr r1, r1, r4, lsl #0x8
	mov r1, r1, lsl #0x10
	cmp lr, r1, lsr #0x10
	moveq r3, #0x1
_0209E1B4:
	cmp r3, #0x0
	beq _0209E1F4
	ldrh r1, [r0, #0xc]
	ldrh lr, [r0, #0xe]
	ldr r3, [r2, #0x1c]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, lr, asr #0x8
	mov r2, r0, lsr #0x10
	orr r0, r1, lr, lsl #0x8
	mov r1, r2, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	cmp r3, r0
	moveq r12, #0x1
_0209E1F4:
	mov r0, r12
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start check_listener
check_listener: ; 0x0209E200
	stmdb sp!, {r4-r6,lr}
	ldr r2, _0209E2DC ; =OSi_ThreadInfo
	ldr r3, [r2, #0x8]
	cmp r3, #0x0
	beq _0209E2D0
_0209E214:
	ldr r12, [r3, #0xa4]
	cmp r12, #0x0
	beq _0209E2C4
	ldr r2, [r12, #0x0]
	cmp r2, #0x0
	beq _0209E2C4
	ldrb r2, [r12, #0x8]
	cmp r2, #0x1
	bne _0209E2C4
	ldrh r5, [r1, #0x2]
	ldrh r4, [r12, #0xa]
	mov r2, r5, asr #0x8
	orr r2, r2, r5, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r4, r2, lsr #0x10
	bne _0209E2C4
	ldrh r5, [r12, #0x18]
	cmp r5, #0x0
	beq _0209E278
	ldrh r4, [r1, #0x0]
	mov r2, r4, asr #0x8
	orr r2, r2, r4, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r5, r2, lsr #0x10
	bne _0209E2C4
_0209E278:
	ldr r2, [r12, #0x1c]
	cmp r2, #0x0
	beq _0209E2B8
	ldrh r5, [r0, #0xc]
	ldrh r6, [r0, #0xe]
	mov r4, r5, asr #0x8
	orr r4, r4, r5, lsl #0x8
	mov lr, r4, lsl #0x10
	mov r4, r6, asr #0x8
	mov lr, lr, lsr #0x10
	orr r4, r4, r6, lsl #0x8
	mov r5, lr, lsl #0x10
	mov lr, r4, lsl #0x10
	orr r4, r5, lr, lsr #0x10
	cmp r2, r4
	bne _0209E2C4
_0209E2B8:
	mov r0, r12
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209E2C4:
	ldr r3, [r3, #0x68]
	cmp r3, #0x0
	bne _0209E214
_0209E2D0:
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209E2DC: .word OSi_ThreadInfo

	arm_func_start dispatch_icmp
dispatch_icmp: ; 0x0209E2E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r4, r2
	mov r6, r0
	mov r0, r5
	mov r1, r4
	bl calc_checksum
	ldr r1, _0209E3D8 ; =0x0000FFFF
	cmp r0, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r12, [r6, #0x10]
	ldrh r7, [r6, #0xc]
	ldrh r0, [r6, #0xe]
	ldrh r1, [r6, #0x12]
	mov r3, r7, asr #0x8
	mov lr, r0, asr #0x8
	orr r0, lr, r0, lsl #0x8
	mov r2, r12, asr #0x8
	orr r7, r3, r7, lsl #0x8
	orr r3, r2, r12, lsl #0x8
	mov r2, r7, lsl #0x10
	mov r12, r1, asr #0x8
	orr r1, r12, r1, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r7, r2, lsr #0x10
	mov r2, r3, lsr #0x10
	mov r3, r7, lsl #0x10
	mov r0, r0, lsl #0x10
	mov r2, r2, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r0, r3, r0, lsr #0x10
	orr r1, r2, r1, lsr #0x10
	bl valid_IP
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrb r0, [r5, #0x0]
	cmp r0, #0x0
	beq _0209E3A0
	cmp r0, #0x8
	beq _0209E3BC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E3A0:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl process_icmp_reply
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E3BC:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl reply_icmp
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E3D8: .word 0x0000FFFF

	arm_func_start valid_IP
valid_IP:
	cmp r0, #0x0
	beq _0209E404
	mvn r2, #0x0
	cmp r0, r2
	beq _0209E404
	cmp r1, #0x0
	beq _0209E404
	cmp r1, r2
	movne r0, #0x1
	bxne lr
_0209E404:
	mov r0, #0x0
	bx lr

	arm_func_start process_icmp_reply
process_icmp_reply: ; 0x0209E40C
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r1, _0209E520 ; =OSi_ThreadInfo
	mov r8, r0
	ldr r2, [r1, #0x8]
	cmp r2, #0x0
	beq _0209E510
_0209E434:
	ldr r4, [r2, #0xa4]
	cmp r4, #0x0
	beq _0209E504
	ldr r3, [r4, #0x0]
	cmp r3, #0x0
	beq _0209E504
	ldrb r0, [r4, #0x8]
	cmp r0, #0xb
	bne _0209E504
	ldrh r1, [r6, #0x4]
	mov r0, r3, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, r1
	bne _0209E504
	ldrh r1, [r4, #0xa]
	ldrh r0, [r6, #0x6]
	cmp r1, r0
	bne _0209E504
	ldr r0, [r4, #0x44]
	cmp r0, #0x0
	bne _0209E504
	ldrh r12, [r7, #0xc]
	ldrh r1, [r7, #0xe]
	ldr r0, [r4, #0x1c]
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r12, r1, asr #0x8
	mov r3, r3, lsr #0x10
	orr r1, r12, r1, lsl #0x8
	mov r3, r3, lsl #0x10
	mov r1, r1, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	cmp r0, r1
	bne _0209E504
	ldr r1, [r4, #0x3c]
	sub r0, r5, #0x8
	cmp r0, r1
	strhi r1, [r4, #0x44]
	strls r0, [r4, #0x44]
	ldr r1, [r4, #0x40]
	ldr r2, [r4, #0x44]
	add r0, r6, #0x8
	bl MI_CpuCopy8
	ldr r0, [r4, #0x4]
	cmp r0, #0x3
	bne _0209E510
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r0, [r4, #0x0]
	bl OS_WakeupThreadDirect
	b _0209E510
_0209E504:
	ldr r2, [r2, #0x68]
	cmp r2, #0x0
	bne _0209E434
_0209E510:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209E520: .word OSi_ThreadInfo

	arm_func_start reply_icmp
reply_icmp: ; 0x0209E524
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldrh r3, [r6, #0xc]
	ldrh r4, [r6, #0xe]
	mov r5, r1
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r4, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r1, r4, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r0, r1, r0, lsr #0x10
	mov r4, r2
	bl get_targetip
	movs r7, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	bl inq_arpcache
	cmp r0, #0x0
	bne _0209E598
	mov r0, r7
	bl send_arprequest
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E598:
	mov r2, #0x0
	strb r2, [r5, #0x0]
	mov r0, r5
	mov r1, r4
	strh r2, [r5, #0x2]
	bl calc_checksum
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r5, #0x2]
	ldrh r1, [r6, #0xc]
	ldrh r6, [r6, #0xe]
	mov r2, #0x0
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r1, r6, asr #0x8
	mov r3, r0, lsr #0x10
	orr r0, r1, r6, lsl #0x8
	mov r1, r3, lsl #0x10
	mov r0, r0, lsl #0x10
	orr r6, r1, r0, lsr #0x10
	mov r0, r5
	mov r1, r4
	mov r3, r2
	str r6, [sp, #0x0]
	mov r4, #0x1
	str r4, [sp, #0x4]
	bl send_ip
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start dispatch_arp
dispatch_arp: ; 0x0209E614
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	cmp r1, #0x1c
	mov r6, r0
	addcc sp, sp, #0x4
	ldmccia sp!, {r4-r7,lr}
	bxcc lr
	ldr r1, _0209E7BC ; =CPSMyMac
	add r0, r6, #0x8
	bl maccmp
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _0209E7C0 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldrh r0, [r6, #0x0]
	cmp r0, #0x100
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r0, [r6, #0x2]
	cmp r0, #0x8
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r1, [r6, #0x4]
	ldr r0, _0209E7C4 ; =0x00000406
	cmp r1, r0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r1, [r6, #0x6]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	cmp r4, #0x1
	beq _0209E6D0
	cmp r4, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
_0209E6D0:
	ldrh r1, [r6, #0xe]
	ldrh r5, [r6, #0x10]
	ldr r2, _0209E7C0 ; =CPSMyIp
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r1, r5, asr #0x8
	orr r0, r1, r5, lsl #0x8
	mov r1, r0, lsl #0x10
	mov r3, r3, lsl #0x10
	orr r1, r3, r1, lsr #0x10
	ldr r0, [r2, #0x0]
	ldrh r3, [r6, #0x18]
	ldrh lr, [r6, #0x1a]
	cmp r1, r0
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	moveq r5, #0x1
	mov r3, lr, asr #0x8
	mov r12, r2, lsr #0x10
	orr r2, r3, lr, lsl #0x8
	mov r3, r12, lsl #0x10
	mov r2, r2, lsl #0x10
	orr r2, r3, r2, lsr #0x10
	movne r5, #0x0
	cmp r0, r2
	moveq r7, #0x1
	movne r7, #0x0
	cmp r5, #0x0
	bne _0209E75C
	mov r2, r7
	add r0, r6, #0x8
	bl reg_arprequest
_0209E75C:
	cmp r4, #0x1
	bne _0209E780
	cmp r7, #0x0
	beq _0209E780
	mov r0, r6
	bl reply_arp
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209E780:
	cmp r4, #0x2
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	cmp r5, #0x0
	ldrne r0, _0209E7C8 ; =ip_conflict
	movne r1, #0x1
	strneb r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209E7BC: .word CPSMyMac
_0209E7C0: .word CPSMyIp
_0209E7C4: .word 0x00000406
_0209E7C8: .word ip_conflict

	arm_func_start reply_arp
reply_arp: ; 0x0209E7CC
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r3, #0x200
	add r0, r4, #0x8
	add r1, r4, #0x12
	mov r2, #0xa
	strh r3, [r4, #0x6]
	bl MI_CpuCopy8
	ldr r0, _0209E870 ; =CPSMyMac
	add r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r3, _0209E874 ; =CPSMyIp
	add r0, r4, #0x12
	ldr r2, [r3, #0x0]
	sub r1, r4, #0xe
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r12, r2, lsr #0x10
	mov r2, r12, asr #0x8
	orr r2, r2, r12, lsl #0x8
	strh r2, [r4, #0xe]
	ldr r3, [r3, #0x0]
	mov r2, #0x6
	mov r3, r3, lsl #0x10
	mov r12, r3, lsr #0x10
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	strh r3, [r4, #0x10]
	bl MI_CpuCopy8
	ldr r0, _0209E870 ; =CPSMyMac
	sub r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	sub r0, r4, #0xe
	mov r1, #0x2a
	mov r2, #0x0
	mov r3, r2
	bl send_packet
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209E870: .word CPSMyMac
_0209E874: .word CPSMyIp

	arm_func_start send_tcp
send_tcp: ; 0x0209E878
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r7, r2
	ldrb r2, [r7, #0x8]
	mov r9, r0
	mov r8, r1
	cmp r2, #0x0
	mov r6, r3
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, _0209EAEC ; =OSi_ThreadInfo
	ldr r3, _0209EAF0 ; =CPSMyIp
	ldr r1, _0209EAF4 ; =tcpip_thread
	ldr r0, [r0, #0x4]
	ldr r12, [r3, #0x0]
	cmp r0, r1
	ldreq r4, _0209EAF8 ; =tmpbuf + 0x22
	ldrne r0, [r7, #0x4c]
	addne r4, r0, #0x22
	ands r0, r6, #0x2
	movne r5, #0x18
	moveq r5, #0x14
	add r1, r5, r8
	mov r2, r1, lsl #0x10
	mov r1, r12, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r12, r1, lsr #0x10
	mov r1, r12, asr #0x8
	orr r1, r1, r12, lsl #0x8
	strh r1, [r4, #-0xc]
	ldr r1, [r3, #0x0]
	mov r12, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0xa]
	ldr r1, [r7, #0x1c]
	mov r3, r12, asr #0x8
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r1, r2, asr #0x8
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0x8]
	ldr r1, [r7, #0x1c]
	mov r2, r5, lsr #0x2
	mov r1, r1, lsl #0x10
	mov lr, r1, lsr #0x10
	mov r1, lr, asr #0x8
	orr r1, r1, lr, lsl #0x8
	strh r1, [r4, #-0x6]
	mov r1, #0x600
	strh r1, [r4, #-0x4]
	orr r1, r3, r12, lsl #0x8
	strh r1, [r4, #-0x2]
	ldrh r12, [r7, #0xa]
	cmp r0, #0x0
	mov r2, r2, lsl #0x4
	mov r3, r12, asr #0x8
	orr r3, r3, r12, lsl #0x8
	strh r3, [r4, #0x0]
	ldrh r3, [r7, #0x18]
	mov r1, #0x0
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x2]
	ldr r0, [r7, #0x28]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x4]
	ldr r0, [r7, #0x28]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x6]
	ldr r0, [r7, #0x24]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0x8]
	ldr r0, [r7, #0x24]
	mov r0, r0, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [r4, #0xa]
	strb r2, [r4, #0xc]
	strb r6, [r4, #0xd]
	ldr r2, [r7, #0x3c]
	ldr r0, [r7, #0x44]
	sub r0, r2, r0
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r4, #0xe]
	strh r1, [r4, #0x10]
	strh r1, [r4, #0x12]
	beq _0209EA64
	ldr r1, _0209EAFC ; =mymss
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x2040000
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [r4, #0x14]
	ldrh r0, [r1, #0x0]
	add r0, r0, #0x2040000
	mov r0, r0, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	strh r0, [r4, #0x16]
_0209EA64:
	sub r0, r4, #0xc
	add r1, r5, #0xc
	mov r2, #0x0
	bl calc_checksum_do
	mov r2, r0
	mov r0, r9
	mov r1, r8
	bl calc_checksum_do
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl invert_checksum
	mov r3, r0, asr #0x8
	orr r0, r3, r0, lsl #0x8
	strh r0, [r4, #0x10]
	mov r0, r4
	ldr r4, [r7, #0x1c]
	mov r3, #0x6
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r1, r5
	mov r2, r9
	mov r3, r8
	bl send_ip
	ands r0, r6, #0x3
	ldr r0, [r7, #0x28]
	add r1, r7, #0x28
	add r0, r0, r8
	str r0, [r7, #0x28]
	ldrne r0, [r1, #0x0]
	addne r0, r0, #0x1
	strne r0, [r1, #0x0]
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209EAEC: .word OSi_ThreadInfo
_0209EAF0: .word CPSMyIp
_0209EAF4: .word tcpip_thread
_0209EAF8: .word tmpbuf + 0x22
_0209EAFC: .word mymss

	arm_func_start send_udp
send_udp:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r7, _0209EC3C ; =CPSMyIp
	mov r5, r2
	ldr r2, [r7, #0x0]
	mov r6, r1
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	ldr r3, [r5, #0x4c]
	mov r1, r2, asr #0x8
	add r4, r3, #0x22
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #-0xc]
	ldr r1, [r7, #0x0]
	add r2, r6, #0x8
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r1, r1, r7, lsl #0x8
	strh r1, [r4, #-0xa]
	ldr r1, [r5, #0x1c]
	mov r2, r2, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r1, r1, r7, lsl #0x8
	strh r1, [r4, #-0x8]
	ldr r1, [r5, #0x1c]
	mov r2, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r7, r1, lsr #0x10
	mov r1, r7, asr #0x8
	orr r7, r1, r7, lsl #0x8
	mov r1, r2, asr #0x8
	strh r7, [r4, #-0x6]
	mov r7, #0x1100
	strh r7, [r4, #-0x4]
	orr r1, r1, r2, lsl #0x8
	strh r1, [r4, #0x4]
	ldrh r1, [r4, #0x4]
	mov r7, r0
	sub r0, r4, #0xc
	strh r1, [r4, #-0x2]
	ldrh lr, [r5, #0x18]
	mov r2, #0x0
	mov r1, #0x14
	mov r12, lr, asr #0x8
	orr r12, r12, lr, lsl #0x8
	strh r12, [r4, #0x2]
	ldrh lr, [r5, #0xa]
	mov r12, lr, asr #0x8
	orr r12, r12, lr, lsl #0x8
	strh r12, [r3, #0x22]
	strh r2, [r4, #0x6]
	bl calc_checksum_do
	mov r2, r0
	mov r0, r7
	mov r1, r6
	bl calc_checksum_do
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl invert_checksum
	mov r2, r7
	mov r3, r6
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r4, #0x6]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	str r1, [sp, #0x0]
	mov r1, #0x11
	str r1, [sp, #0x4]
	mov r1, #0x8
	bl send_ip
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209EC3C: .word CPSMyIp

	arm_func_start send_ping
send_ping:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r5, r2
	ldr r3, [r5, #0x4c]
	mov r6, r1
	mov r1, #0x8
	ldr r2, _0209ECF4 ; =OSi_ThreadInfo
	strh r1, [r3, #0x22]
	ldr r2, [r2, #0x4]
	add r4, r3, #0x22
	strh r2, [r4, #0x4]
	mov r2, #0x0
	ldr r3, _0209ECF8 ; =UNK_021C8EB4
	strh r2, [r4, #0x2]
	ldrh lr, [r3, #0x0]
	mov r7, r0
	mov r0, r4
	strh lr, [r5, #0xa]
	ldrh r12, [r3, #0x0]
	add r12, r12, #0x1
	strh r12, [r3, #0x0]
	strh lr, [r4, #0x6]
	bl calc_checksum_do
	mov r2, r0
	mov r0, r7
	mov r1, r6
	bl calc_checksum_do
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl invert_checksum
	mov r2, r7
	mov r3, r6
	mov r1, r0, asr #0x8
	orr r0, r1, r0, lsl #0x8
	strh r0, [r4, #0x2]
	ldr r1, [r5, #0x1c]
	mov r0, r4
	str r1, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r1, #0x8
	bl send_ip
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209ECF4: .word OSi_ThreadInfo
_0209ECF8: .word UNK_021C8EB4

	arm_func_start send_ip
send_ip: ; 0x0209ECFC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r0
	mov r0, #0x45
	strb r0, [r10, #-0x14]
	mov r5, #0x0
	ldr r0, _0209EF0C ; =ipid
	strb r5, [r10, #-0x13]
	ldrh r7, [r0, #0x0]
	ldr r6, [sp, #0x30]
	ldrb r4, [sp, #0x34]
	add r7, r7, #0x1
	strh r7, [r0, #0x0]
	ldrh r9, [r0, #0x0]
	mov r0, r6, lsr #0x10
	mov r7, #0x80
	mov r8, r9, asr #0x8
	orr r8, r8, r9, lsl #0x8
	strh r8, [r10, #-0x10]
	strb r7, [r10, #-0xc]
	ldr r7, _0209EF10 ; =CPSMyIp
	strb r4, [r10, #-0xb]
	ldr r8, [r7, #0x0]
	mov r4, r0, lsl #0x10
	mov r0, r8, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r8, r0, lsr #0x10
	mov r0, r8, asr #0x8
	orr r0, r0, r8, lsl #0x8
	strh r0, [r10, #-0x8]
	ldr r0, [r7, #0x0]
	mov r8, r4, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	mov r4, r7, asr #0x8
	mov r0, r6, lsl #0x10
	orr r9, r4, r7, lsl #0x8
	mov r7, r8, asr #0x8
	mov r4, r0, lsr #0x10
	mov r0, r4, asr #0x8
	strh r9, [r10, #-0x6]
	orr r7, r7, r8, lsl #0x8
	ldr fp, _0209EF14 ; =0x000005C8
	mov r9, r1
	strh r7, [r10, #-0x4]
	orr r0, r0, r4, lsl #0x8
	mov r8, r2
	mov r7, r3
	strh r0, [r10, #-0x2]
	cmp r9, r11
	bls _0209EE74
	mov r4, r10
	cmp r9, r11
	bls _0209EE14
	str r5, [sp, #0x8]
_0209EDD8:
	ldr r1, [sp, #0x8]
	mov r0, r10
	mov r2, r4
	mov r3, r11
	str r6, [sp, #0x0]
	orr r12, r5, #0x2000
	str r12, [sp, #0x4]
	bl send_ip_frag
	add r0, r5, #0xb9
	sub r9, r9, r11
	mov r0, r0, lsl #0x10
	cmp r9, r11
	add r4, r4, r11
	mov r5, r0, lsr #0x10
	bhi _0209EDD8
_0209EE14:
	cmp r9, #0x0
	beq _0209EE74
	cmp r7, #0x0
	beq _0209EE48
	mov r0, r10
	mov r2, r4
	mov r3, r9
	str r6, [sp, #0x0]
	orr r4, r5, #0x2000
	mov r1, #0x0
	str r4, [sp, #0x4]
	bl send_ip_frag
	b _0209EE64
_0209EE48:
	str r6, [sp, #0x0]
	mov r0, r10
	mov r2, r4
	mov r3, r9
	mov r1, #0x0
	str r5, [sp, #0x4]
	bl send_ip_frag
_0209EE64:
	add r0, r5, r9, lsr #0x3
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	mov r9, #0x0
_0209EE74:
	ldr r0, _0209EF14 ; =0x000005C8
	add r1, r9, r7
	cmp r1, r0
	bls _0209EED4
	mov r11, #0x0
_0209EE88:
	ldr r0, _0209EF14 ; =0x000005C8
	mov r1, r9
	sub r4, r0, r9
	mov r0, r10
	mov r2, r8
	mov r3, r4
	str r6, [sp, #0x0]
	orr r9, r5, #0x2000
	str r9, [sp, #0x4]
	bl send_ip_frag
	add r0, r5, #0xb9
	mov r1, r0, lsl #0x10
	ldr r0, _0209EF14 ; =0x000005C8
	sub r7, r7, r4
	mov r9, r11
	cmp r7, r0
	add r8, r8, r4
	mov r5, r1, lsr #0x10
	bhi _0209EE88
_0209EED4:
	adds r0, r9, r7
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	str r6, [sp, #0x0]
	mov r0, r10
	mov r1, r9
	mov r2, r8
	mov r3, r7
	str r5, [sp, #0x4]
	bl send_ip_frag
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209EF0C: .word ipid
_0209EF10: .word CPSMyIp
_0209EF14: .word 0x000005C8

	arm_func_start send_ip_frag
send_ip_frag: ; 0x0209EF18
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r1
	mov r5, r3
	add r1, r7, #0x14
	add r1, r1, r5
	ldr r3, [sp, #0x24]
	mov r1, r1, lsl #0x10
	mov r4, r1, lsr #0x10
	mov r1, r3, lsl #0x10
	mov r3, r4, asr #0x8
	mov r1, r1, lsr #0x10
	mov r8, r0
	orr r3, r3, r4, lsl #0x8
	mov r0, r1, asr #0x8
	strh r3, [r8, #-0x12]
	orr r0, r0, r1, lsl #0x8
	strh r0, [r8, #-0xe]
	mov r3, #0x0
	sub r0, r8, #0x14
	mov r1, #0x14
	mov r6, r2
	strh r3, [r8, #-0xa]
	ldr r4, [sp, #0x20]
	bl calc_checksum
	mov r2, r0, asr #0x8
	ldr r1, _0209F040 ; =0x7F000001
	orr r0, r2, r0, lsl #0x8
	strh r0, [r8, #-0xa]
	cmp r4, r1
	beq _0209EFC4
	ldr r0, _0209F044 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r4, r0
	beq _0209EFC4
	mov r2, r6
	mov r3, r5
	str r4, [sp, #0x0]
	mov r12, #0x800
	sub r0, r8, #0x14
	add r1, r7, #0x14
	str r12, [sp, #0x4]
	bl send_ether
_0209EFC4:
	ldr r0, _0209F040 ; =0x7F000001
	cmp r4, r0
	beq _0209EFF8
	ldr r0, _0209F044 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r4, r0
	beq _0209EFF8
	mov r0, r4
	bl is_multicast
	cmp r0, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
_0209EFF8:
	ldr r0, _0209F048 ; =UNK_02106230
	sub r1, r8, #0x1c
	mov r2, #0x8
	bl MI_CpuCopy8
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _0209F04C ; =CPSMyMac
	str r6, [sp, #0x0]
	mov r1, r0
	str r5, [sp, #0x4]
	sub r2, r8, #0x1c
	add r3, r7, #0x1c
	bl put_in_buffer
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F040: .word 0x7F000001
_0209F044: .word CPSMyIp
_0209F048: .word UNK_02106230
_0209F04C: .word CPSMyMac

	arm_func_start send_ether
send_ether: ; 0x0209F050
	stmdb sp!, {r4-r8,lr}
	ldrh r5, [sp, #0x1c]
	ldr r4, [sp, #0x18]
	mov r8, r0
	mov r0, r5, asr #0x8
	orr r12, r0, r5, lsl #0x8
	mov r0, r4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	strh r12, [r8, #-0x2]
	bl is_multicast
	cmp r0, #0x0
	bne _0209F0CC
	mov r0, r4
	bl get_targetip
	movs r4, r0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	bl inq_arpcache
	cmp r0, #0x0
	bne _0209F0B0
	mov r0, r4
	bl arprequest
_0209F0B0:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	sub r1, r8, #0xe
	mov r2, #0x6
	bl MI_CpuCopy8
	b _0209F0FC
_0209F0CC:
	mov r0, #0x1
	strb r0, [r8, #-0xe]
	mov r1, #0x0
	mov r0, r4, lsr #0x10
	strb r1, [r8, #-0xd]
	mov r1, #0x5e
	strb r1, [r8, #-0xc]
	and r0, r0, #0x7f
	strb r0, [r8, #-0xb]
	mov r0, r4, lsr #0x8
	strb r0, [r8, #-0xa]
	strb r4, [r8, #-0x9]
_0209F0FC:
	ldr r0, _0209F128 ; =CPSMyMac
	sub r1, r8, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r2, r6
	mov r3, r5
	sub r0, r8, #0xe
	add r1, r7, #0xe
	bl send_packet
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F128: .word CPSMyMac

	arm_func_start reg_arprequest
reg_arprequest: ; 0x0209F12C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _0209F29C ; =0x7F000001
	mov r6, r1
	cmp r6, r3
	mov r7, r0
	mov r4, r2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _0209F2A0 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r6, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	bl ip_islocal
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r6
	bl is_multicast
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	bl OS_GetTick
	mov r0, r0, lsr #0x10
	orr r0, r0, r1, lsl #0x10
	mov r0, r0, lsl #0x10
	ldr r1, _0209F2A4 ; =arpcache
	mov r5, r0, lsr #0x10
	mov r2, #0x0
_0209F1B8:
	ldr r0, [r1, #0x0]
	cmp r6, r0
	bne _0209F1F8
	mov r0, #0xc
	mul r4, r2, r0
	ldr r0, _0209F2A4 ; =arpcache
	ldr r3, _0209F2A8 ; =arpcache+10
	add r1, r0, r4
	mov r0, r7
	add r1, r1, #0x4
	mov r2, #0x6
	strh r5, [r3, r4]
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_0209F1F8:
	add r2, r2, #0x1
	cmp r2, #0x8
	add r1, r1, #0xc
	blo _0209F1B8
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r12, #0x0
	ldr r4, _0209F2A4 ; =arpcache
	mov r0, r12
	mov r3, r12
_0209F228:
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	moveq r0, r3
	beq _0209F264
	ldrh r1, [r4, #0xa]
	add r4, r4, #0xc
	sub r1, r5, r1
	mov r1, r1, lsl #0x10
	mov r2, r1, asr #0x10
	cmp r2, r12
	movgt r0, r3
	add r3, r3, #0x1
	movgt r12, r1, lsr #0x10
	cmp r3, #0x8
	blo _0209F228
_0209F264:
	mov r1, #0xc
	mul r4, r0, r1
	ldr r3, _0209F2A4 ; =arpcache
	mov r0, r7
	add r1, r3, r4
	add r1, r1, #0x4
	mov r2, #0x6
	str r6, [r3, r4]
	bl MI_CpuCopy8
	ldr r0, _0209F2A8 ; =arpcache+10
	strh r5, [r0, r4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209F29C: .word 0x7F000001
_0209F2A0: .word CPSMyIp
_0209F2A4: .word arpcache
_0209F2A8: .word arpcache+10

	arm_func_start arprequest
arprequest:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, #0x0
	ldr r4, _0209F334 ; =CPSMyIp
	mov r6, r8
	mov r5, #0x64
_0209F2C8:
	mov r0, r9
	bl send_arprequest
	mov r7, r6
_0209F2D4:
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r5
	bl OS_Sleep
	mov r0, r9
	bl inq_arpcache
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	add r7, r7, #0x1
	cmp r7, #0x14
	blo _0209F2D4
	add r8, r8, #0x1
	cmp r8, #0x8
	blo _0209F2C8
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209F334: .word CPSMyIp

	arm_func_start send_arprequest
send_arprequest: ; 0x0209F338
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x30
	mov r4, r0
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x2a
	bl MI_CpuFill8
	add r0, sp, #0x0
	mov r1, #0xff
	mov r2, #0x6
	bl MI_CpuFill8
	ldr r0, _0209F428 ; =CPSMyMac
	add r1, sp, #0x6
	mov r2, #0x6
	bl MI_CpuCopy8
	mov r0, #0x1
	ldr r1, _0209F42C ; =0x00000608
	strb r0, [sp, #0xf]
	strh r1, [sp, #0xc]
	strb r0, [sp, #0x15]
	mov r0, #0x8
	ldr r1, _0209F430 ; =0x00000406
	strb r0, [sp, #0x10]
	strh r1, [sp, #0x12]
	ldr r0, _0209F428 ; =CPSMyMac
	add r1, sp, #0x16
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r0, _0209F434 ; =CPSMyIp
	mov r1, r4, lsr #0x10
	ldr r3, [r0, #0x0]
	mov r0, r1, lsl #0x10
	mov r2, r0, lsr #0x10
	mov r0, r4, lsl #0x10
	mov r1, r0, lsr #0x10
	mov r0, r3, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	mov r0, r3, lsl #0x10
	mov r3, r0, lsr #0x10
	mov r0, r4, asr #0x8
	orr r0, r0, r4, lsl #0x8
	strh r0, [sp, #0x1c]
	mov r0, r3, asr #0x8
	orr r0, r0, r3, lsl #0x8
	strh r0, [sp, #0x1e]
	mov r0, r2, asr #0x8
	orr r0, r0, r2, lsl #0x8
	strh r0, [sp, #0x26]
	mov r0, r1, asr #0x8
	orr r0, r0, r1, lsl #0x8
	mov r2, #0x0
	strh r0, [sp, #0x28]
	add r0, sp, #0x0
	mov r1, #0x2a
	mov r3, r2
	bl send_packet
	add sp, sp, #0x30
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209F428: .word CPSMyMac
_0209F42C: .word 0x00000608
_0209F430: .word 0x00000406
_0209F434: .word CPSMyIp

	arm_func_start inq_arpcache
inq_arpcache:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	bl OS_DisableInterrupts
	ldr r1, _0209F504 ; =0x7F000001
	mov r4, r0
	cmp r7, r1
	mov r5, #0x0
	beq _0209F46C
	ldr r0, _0209F508 ; =CPSMyIp
	ldr r0, [r0, #0x0]
	cmp r7, r0
	bne _0209F474
_0209F46C:
	ldr r5, _0209F50C ; =CPSMyMac
	b _0209F4EC
_0209F474:
	mov r0, r7
	bl is_broadcast
	cmp r0, #0x0
	bne _0209F494
	mov r0, r7
	bl is_multicast
	cmp r0, #0x0
	beq _0209F49C
_0209F494:
	ldr r5, _0209F510 ; =mac_broadcast
	b _0209F4EC
_0209F49C:
	ldr r1, _0209F514 ; =arpcache
	mov r6, r5
_0209F4A4:
	ldr r0, [r1, #0x0]
	cmp r7, r0
	bne _0209F4DC
	bl OS_GetTick
	mov r2, #0xc
	mul r3, r6, r2
	ldr r2, _0209F514 ; =arpcache
	mov r5, r0, lsr #0x10
	add r0, r2, r3
	ldr r2, _0209F518 ; =arpcache+10
	orr r5, r5, r1, lsl #0x10
	strh r5, [r2, r3]
	add r5, r0, #0x4
	b _0209F4EC
_0209F4DC:
	add r6, r6, #0x1
	cmp r6, #0x8
	add r1, r1, #0xc
	blo _0209F4A4
_0209F4EC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_0209F504: .word 0x7F000001
_0209F508: .word CPSMyIp
_0209F50C: .word CPSMyMac
_0209F510: .word mac_broadcast
_0209F514: .word arpcache
_0209F518: .word arpcache+10

	arm_func_start throw_packet
throw_packet: ; 0x0209F51C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r2, _0209F570 ; =wlan_getpnt
	ldr r1, _0209F574 ; =wlan_buf
	ldr lr, [r2, #0x0]
	ldr r12, [r1, #0x0]
	ldr r3, [r2, #0x0]
	ldr r1, _0209F578 ; =wlan_buflen
	ldrh r3, [r12, r3]
	add r3, lr, r3
	str r3, [r2, #0x0]
	ldr r3, [r2, #0x0]
	ldr r1, [r1, #0x0]
	cmp r3, r1
	movcs r1, #0x0
	strcs r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209F570: .word wlan_getpnt
_0209F574: .word wlan_buf
_0209F578: .word wlan_buflen

	arm_func_start receive_packet
receive_packet: ; 0x0209F57C
	stmdb sp!, {r4-r10,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	ldr sl, _0209F644 ; =wlan_getpnt
	ldr sb, _0209F648 ; =wlan_putpnt
	ldr r2, [r10, #0x0]
	ldr r1, [r9, #0x0]
	mov r5, r0
	cmp r2, r1
	bne _0209F5D4
	ldr r8, _0209F64C ; =OSi_ThreadInfo
	ldr r7, _0209F650 ; =receiver_thread
	mov r4, #0x0
_0209F5B0:
	ldr r1, [r8, #0x4]
	mov r0, r4
	str r1, [r7, #0x0]
	bl OS_SleepThread
	str r4, [r7, #0x0]
	ldr r1, [r10, #0x0]
	ldr r0, [r9, #0x0]
	cmp r1, r0
	beq _0209F5B0
_0209F5D4:
	mov r0, r5
	bl OS_RestoreInterrupts
	ldr r0, _0209F654 ; =wlan_buf
	ldr r5, [r0, #0x0]
	ldr r0, _0209F644 ; =wlan_getpnt
	ldr r1, _0209F658 ; =wlan_buflen
	mov r3, #0x0
_0209F5F0:
	ldr r4, [r1, #0x0]
	ldr r2, [r0, #0x0]
	sub r2, r4, r2
	cmp r2, #0x2
	strcc r3, [r0, #0x0]
	ldr r2, [r0, #0x0]
	ldrh r2, [r5, r2]
	cmp r2, #0x0
	streq r3, [r0, #0x0]
	cmp r2, #0x0
	beq _0209F5F0
	sub r0, r2, #0x2
	ldr r1, _0209F654 ; =wlan_buf
	str r0, [r6, #0x0]
	ldr r0, _0209F644 ; =wlan_getpnt
	ldr r1, [r1, #0x0]
	ldr r0, [r0, #0x0]
	add r0, r1, r0
	add r0, r0, #0x2
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_0209F644: .word wlan_getpnt
_0209F648: .word wlan_putpnt
_0209F64C: .word OSi_ThreadInfo
_0209F650: .word receiver_thread
_0209F654: .word wlan_buf
_0209F658: .word wlan_buflen

	arm_func_start CPSi_RecvCallbackFunc
CPSi_RecvCallbackFunc: ; 0x0209F65C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r12, [sp, #0x4]
	bl put_in_buffer
	ldr r0, _0209F6BC ; =receiver_thread
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0xc
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [r0, #0x0]
	bl OS_IsThreadTerminated
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _0209F6BC ; =receiver_thread
	ldr r0, [r0, #0x0]
	bl OS_WakeupThreadDirect
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209F6BC: .word receiver_thread

	arm_func_start put_in_buffer
put_in_buffer: ; 0x0209F6C0
	stmdb sp!, {r4-r8,lr}
	ldr r4, _0209F918 ; =wlan_buf
	mov r7, r0
	ldr r0, [r4, #0x0]
	mov r6, r2
	mov r5, r3
	cmp r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r2, _0209F91C ; =wlan_buflen
	ldr r2, [r2, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r2, [sp, #0x1c]
	add r2, r5, r2
	cmp r2, #0x8
	ldmccia sp!, {r4-r8,lr}
	bxcc lr
	ldr r3, _0209F920 ; =0x000005E4
	cmp r2, r3
	ldmhiia sp!, {r4-r8,lr}
	bxhi lr
	ldr r3, _0209F924 ; =UNK_02106230
	ldrb r8, [r6, #0x0]
	ldrb r4, [r3, #0x0]
	cmp r8, r4
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r8, [r6, #0x1]
	ldrb r4, [r3, #0x1]
	cmp r8, r4
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r4, [r6, #0x2]
	ldrb r3, [r3, #0x2]
	cmp r4, r3
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r3, [r6, #0x6]
	cmp r3, #0x8
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldrb r3, [r6, #0x7]
	cmp r3, #0x0
	beq _0209F784
	cmp r3, #0x6
	ldmneia sp!, {r4-r8,lr}
	bxne lr
_0209F784:
	ldr r4, _0209F928 ; =wlan_putpnt
	add r2, r2, #0x9
	bic r2, r2, #0x1
	ldr lr, [r4, #0x0]
	mov r3, r2, lsl #0x10
	ldr ip, _0209F92C ; =wlan_getpnt
	ldr r8, [r4, #0x0]
	ldr r4, [r12, #0x0]
	mov r2, r3, lsr #0x10
	cmp r8, r4
	add r4, lr, r3, lsr #0x10
	bhs _0209F7C4
	ldr r3, [r12, #0x0]
	cmp r3, r4
	ldmlsia sp!, {r4-r8,lr}
	bxls lr
_0209F7C4:
	ldr r3, _0209F91C ; =wlan_buflen
	ldr r8, [r3, #0x0]
	cmp r4, r8
	bne _0209F7F0
	ldr r3, _0209F92C ; =wlan_getpnt
	mov r4, #0x0
	ldr r3, [r3, #0x0]
	cmp r3, #0x0
	bne _0209F814
	ldmia sp!, {r4-r8,lr}
	bx lr
_0209F7F0:
	ldr r3, [r3, #0x0]
	cmp r4, r3
	bls _0209F814
	ldr r3, _0209F92C ; =wlan_getpnt
	mov r4, r2
	ldr r3, [r3, #0x0]
	cmp r3, r2
	ldmlsia sp!, {r4-r8,lr}
	bxls lr
_0209F814:
	ldr ip, _0209F928 ; =wlan_putpnt
	ldr r3, _0209F91C ; =wlan_buflen
	ldr lr, [r12, #0x0]
	ldr r8, [r3, #0x0]
	add lr, lr, r2
	cmp lr, r8
	bls _0209F858
	ldr r8, [r3, #0x0]
	ldr r3, [r12, #0x0]
	sub r3, r8, r3
	cmp r3, #0x2
	ldrcs r3, [r12, #0x0]
	movcs r8, #0x0
	strcsh r8, [r0, r3]
	ldr r0, _0209F928 ; =wlan_putpnt
	mov r3, #0x0
	str r3, [r0, #0x0]
_0209F858:
	ldr ip, _0209F918 ; =wlan_buf
	ldr r3, _0209F928 ; =wlan_putpnt
	ldr r8, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mov r0, r1
	strh r2, [r8, lr]
	ldr r12, [r12, #0x0]
	ldr r1, [r3, #0x0]
	mov r2, #0x6
	add r1, r12, r1
	add r1, r1, #0x2
	bl MI_CpuCopy8
	ldr r1, _0209F918 ; =wlan_buf
	ldr r0, _0209F928 ; =wlan_putpnt
	ldr r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	mov r0, r7
	add r1, r2, r1
	add r1, r1, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r1, _0209F918 ; =wlan_buf
	ldr r0, _0209F928 ; =wlan_putpnt
	ldr r2, [r1, #0x0]
	ldr r1, [r0, #0x0]
	add r0, r6, #0x6
	add r1, r2, r1
	add r1, r1, #0xe
	sub r2, r5, #0x6
	bl MI_CpuCopy8
	ldr r0, [sp, #0x18]
	cmp r0, #0x0
	beq _0209F908
	ldr r2, [sp, #0x1c]
	cmp r2, #0x0
	beq _0209F908
	ldr r3, _0209F918 ; =wlan_buf
	ldr r1, _0209F928 ; =wlan_putpnt
	ldr r3, [r3, #0x0]
	ldr r1, [r1, #0x0]
	add r1, r3, r1
	add r1, r1, #0x8
	add r1, r1, r5
	bl MI_CpuCopy8
_0209F908:
	ldr r0, _0209F928 ; =wlan_putpnt
	str r4, [r0, #0x0]
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209F918: .word wlan_buf
_0209F91C: .word wlan_buflen
_0209F920: .word 0x000005E4
_0209F924: .word UNK_02106230
_0209F928: .word wlan_putpnt
_0209F92C: .word wlan_getpnt

	arm_func_start send_packet
send_packet: ; 0x0209F930
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	add r1, r6, r5
	mov r4, r3
	cmp r1, r2
	beq _0209F958
	mov r0, r2
	mov r2, r4
	bl MI_CpuCopy8
_0209F958:
	ldr r0, _0209F998 ; =UNK_02106230
	add r1, r6, #0x6
	mov r2, #0x6
	bl MI_CpuCopy8
	add r2, r5, r4
	mov r0, r6
	add r1, r6, #0x6
	sub r2, r2, #0x6
	bl WCM_SendDCFData
	cmp r0, #0x0
	movlt r1, #0x1
	ldr r0, _0209F99C ; =wfailed
	movge r1, #0x0
	strb r1, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209F998: .word UNK_02106230
_0209F99C: .word wfailed

	arm_func_start maccmp
maccmp:
	mov r12, #0x0
_0209F9A4:
	ldrh r3, [r0], #0x2
	ldrh r2, [r1], #0x2
	cmp r3, r2
	movne r0, #0x1
	bxne lr
	add r12, r12, #0x1
	cmp r12, #0x3
	blt _0209F9A4
	mov r0, #0x0
	bx lr

	arm_func_start ip_isme
ip_isme:
	stmdb sp!, {r4-r6,lr}
	ldr r1, _0209FA4C ; =CPSMyIp
	mov r5, #0x1
	ldr r1, [r1, #0x0]
	mov r6, r0
	mov r4, r5
	mov r2, r5
	mov r0, r5
	cmp r1, #0x0
	beq _0209F9FC
	cmp r6, r1
	movne r0, #0x0
_0209F9FC:
	cmp r0, #0x0
	bne _0209FA10
	ldr r0, _0209FA50 ; =0x7F000001
	cmp r6, r0
	movne r2, #0x0
_0209FA10:
	cmp r2, #0x0
	bne _0209FA28
	mov r0, r6
	bl is_broadcast
	cmp r0, #0x0
	moveq r4, #0x0
_0209FA28:
	cmp r4, #0x0
	bne _0209FA40
	mov r0, r6
	bl is_multicast
	cmp r0, #0x0
	moveq r5, #0x0
_0209FA40:
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209FA4C: .word CPSMyIp
_0209FA50: .word 0x7F000001

	arm_func_start is_multicast
is_multicast:
	and r0, r0, #0xf0000000
	cmp r0, #0xe0000000
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start is_broadcast
is_broadcast:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, #0x0
	bl ip_islocal
	cmp r0, #0x0
	beq _0209FA9C
	ldr r0, _0209FAAC ; =CPSNetMask
	ldr r0, [r0, #0x0]
	mvn r1, r0
	and r0, r1, r5
	cmp r1, r0
	moveq r4, #0x1
_0209FA9C:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FAAC: .word CPSNetMask

	arm_func_start get_targetip
get_targetip:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl ip_islocal
	cmp r0, #0x0
	ldreq r0, _0209FAD4 ; =CPSGatewayIp
	ldreq r4, [r0, #0x0]
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209FAD4: .word CPSGatewayIp

	arm_func_start ip_islocal
ip_islocal:
	mvn r1, #0x0
	cmp r0, r1
	mov r12, #0x1
	beq _0209FB14
	ldr r1, _0209FB1C ; =0x7F000001 127.0.0.1
	cmp r0, r1
	beq _0209FB14
	ldr r2, _0209FB20 ; =CPSNetMask
	ldr r1, _0209FB24 ; =CPSMyIp
	ldr r3, [r2, #0x0]
	ldr r1, [r1, #0x0]
	and r2, r0, r3
	and r0, r1, r3
	cmp r2, r0
	movne r12, #0x0
_0209FB14:
	mov r0, r12
	bx lr
	.balign 4
_0209FB1C: .word 0x7F000001
_0209FB20: .word CPSNetMask
_0209FB24: .word CPSMyIp

	arm_func_start check_tcpudpsum
check_tcpudpsum:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r2
	mov r2, r3
	mov r5, r1
	bl calc_checksum_do
	mov r2, r0
	add r0, r4, #0xc
	mov r1, #0x8
	bl calc_checksum_do
	add r1, r0, r5
	ands r0, r1, #0x10000
	ldrne r0, _0209FB80 ; =0x0000FFFF
	addne r1, r1, #0x1
	andne r1, r1, r0
	ldr r0, _0209FB80 ; =0x0000FFFF
	cmp r1, r0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FB80: .word 0x0000FFFF

	arm_func_start calc_checksum
calc_checksum: ; 0x0209FB84
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	bl calc_checksum_do
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl invert_checksum
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start invert_checksum
invert_checksum: ; 0x0209FBAC
	ldr r1, _0209FBC4 ; =0x0000FFFF
	eor r0, r0, r1
	mov r0, r0, lsl #0x10
	movs r0, r0, lsr #0x10
	moveq r0, r1
	bx lr
	.balign 4
_0209FBC4: .word 0x0000FFFF

	arm_func_start calc_checksum_do
calc_checksum_do: ; 0x0209FBC8
	ands r3, r0, #0x1
	beq _0209FC00
	cmp r1, #0x1
	bls _0209FC54
_0209FBD8:
	ldrb r12, [r0, #0x0]
	ldrb r3, [r0, #0x1]
	sub r1, r1, #0x2
	cmp r1, #0x1
	orr r3, r3, r12, lsl #0x8
	mov r3, r3, lsl #0x10
	add r2, r2, r3, lsr #0x10
	add r0, r0, #0x2
	bhi _0209FBD8
	b _0209FC54
_0209FC00:
	mov r2, r2, lsl #0x10
	mov r3, r2, lsr #0x10
	mov r2, r3, asr #0x8
	orr r2, r2, r3, lsl #0x8
	mov r2, r2, lsl #0x10
	cmp r1, #0x1
	mov r2, r2, lsr #0x10
	bls _0209FC38
_0209FC20:
	ldrh r3, [r0, #0x0]
	sub r1, r1, #0x2
	cmp r1, #0x1
	add r2, r2, r3
	add r0, r0, #0x2
	bhi _0209FC20
_0209FC38:
	ldr r3, _0209FC7C ; =0x00FF00FF
	ldr ip, _0209FC80 ; =0xFF00FF00
	and r3, r3, r2, lsr #0x8
	and r2, r12, r2, lsl #0x8
	orr r3, r3, r2
	mov r2, r3, lsr #0x10
	orr r2, r2, r3, lsl #0x10
_0209FC54:
	cmp r1, #0x0
	ldrneb r0, [r0, #0x0]
	addne r2, r2, r0, lsl #0x8
	ldr r0, _0209FC84 ; =0x0000FFFF
	and r0, r2, r0
	add r0, r0, r2, lsr #0x10
	add r0, r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.balign 4
_0209FC7C: .word 0x00FF00FF
_0209FC80: .word 0xFF00FF00
_0209FC84: .word 0x0000FFFF

	arm_func_start CPS_SetThreadPriority
CPS_SetThreadPriority: ; 0x0209FC88
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r2, _0209FCB8 ; =helper_threads_priority
	ldr r0, _0209FCBC ; =tcpip_thread
	mov r1, r4
	str r4, [r2, #0x0]
	bl OS_SetThreadPriority
	ldr r0, _0209FCC0 ; =scavenger_thread
	mov r1, r4
	bl OS_SetThreadPriority
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209FCB8: .word helper_threads_priority
_0209FCBC: .word tcpip_thread
_0209FCC0: .word scavenger_thread

	arm_func_start CPS_Cleanup
CPS_Cleanup:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl CPS_CalmDown
	ldr r0, _0209FD10 ; =scavenger_thread
	bl OS_JoinThread
	ldr r0, _0209FD14 ; =tcpip_thread
	bl OS_DestroyThread
	ldr r1, _0209FD18 ; =receiver_thread
	mov r0, #0x0
	str r0, [r1, #0x0]
	bl reset_network_vars
	ldr r1, _0209FD1C ; =wlan_buf
	mov r2, #0x0
	ldr r0, _0209FD20 ; =wlan_buflen
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209FD10: .word scavenger_thread
_0209FD14: .word tcpip_thread
_0209FD18: .word receiver_thread
_0209FD1C: .word wlan_buf
_0209FD20: .word wlan_buflen

	arm_func_start CPS_SetScavengerCallback
CPS_SetScavengerCallback: ; 0x0209FD24
	ldr r1, _0209FD30 ; =scavenger_callback
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_0209FD30: .word scavenger_callback

	arm_func_start CPS_CalmDown
CPS_CalmDown:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	ldr r0, _0209FD8C ; =scavenger_thread
	bl OS_IsThreadTerminated
	movs r4, r0
	bne _0209FD74
	ldr r1, _0209FD90 ; =scavenger_force_exit
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _0209FD74
	ldr r0, _0209FD8C ; =scavenger_thread
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_WakeupThreadDirect
_0209FD74:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209FD8C: .word scavenger_thread
_0209FD90: .word scavenger_force_exit

	.extern _SDK_UbiquitousCPS

	arm_func_start CPS_Startup
CPS_Startup: ; 0x0209FD94
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldr r0, _0209FFD4 ; =_SDK_UbiquitousCPS
	bl OSi_ReferSymbol
	ldr r12, [r4, #0x14]
	ldr r6, [r4, #0x18]
	mov r1, #0x0
	cmp r6, r1
	cmpeq r12, r1
	beq _0209FDEC
	ldr r0, _0209FFD8 ; =CPSiRand32ctx
	ldr r5, _0209FFDC ; =0x6C078965
	ldr r3, _0209FFE0 ; =0x5D588B65
	ldr r2, _0209FFE4 ; =0x00269EC3
	str r12, [r0, #0x0]
	str r6, [r0, #0x4]
	str r5, [r0, #0x8]
	str r3, [r0, #0xc]
	str r2, [r0, #0x10]
	str r1, [r0, #0x14]
	b _0209FE1C
_0209FDEC:
	bl OS_GetTick
	ldr r2, _0209FFD8 ; =CPSiRand32ctx
	ldr ip, _0209FFDC ; =0x6C078965
	ldr r6, _0209FFE0 ; =0x5D588B65
	ldr r5, _0209FFE4 ; =0x00269EC3
	mov r3, #0x0
	str r0, [r2, #0x0]
	str r1, [r2, #0x4]
	str r12, [r2, #0x8]
	str r6, [r2, #0xc]
	str r5, [r2, #0x10]
	str r3, [r2, #0x14]
_0209FE1C:
	ldr r2, [r4, #0x4]
	cmp r2, #0x0
	beq _0209FE4C
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _0209FE4C
	ldr r1, _0209FFE8 ; =CPSiAlloc
	ldr r0, _0209FFEC ; =CPSiFree
	str r2, [r1, #0x0]
	ldr r1, [r4, #0x8]
	str r1, [r0, #0x0]
	b _0209FE60
_0209FE4C:
	ldr r2, _0209FFF0 ; =empty_func
	ldr r1, _0209FFE8 ; =CPSiAlloc
	ldr r0, _0209FFEC ; =CPSiFree
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
_0209FE60:
	ldr r1, [r4, #0x0]
	ldr r0, _0209FFF4 ; =mode
	ldr ip, _0209FFD8 ; =CPSiRand32ctx
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x24]
	ldr r3, [r12, #0x8]
	cmp r1, #0x0
	ldrne r0, _0209FFF8 ; =mymss
	strneh r1, [r0, #0x0]
	ldreq r1, _0209FFFC ; =0x000005B4
	ldreq r0, _0209FFF8 ; =mymss
	streqh r1, [r0, #0x0]
	ldr r2, [r4, #0x28]
	ldr r1, _020A0000 ; =offered_myip
	ldr r0, _020A0004 ; =yield_wait
	str r2, [r1, #0x0]
	ldr r1, [r4, #0x2c]
	ldr r2, [r12, #0x0]
	str r1, [r0, #0x0]
	ldr r1, [r4, #0xc]
	umull lr, r5, r3, r2
	cmp r1, #0x0
	ldrne r0, _020A0008 ; =dhcp_callback
	strne r1, [r0, #0x0]
	ldreq r1, _0209FFF0 ; =empty_func
	ldreq r0, _020A0008 ; =dhcp_callback
	streq r1, [r0, #0x0]
	ldr r1, [r4, #0x10]
	cmp r1, #0x0
	ldrne r0, _020A000C ; =link_is_on
	strne r1, [r0, #0x0]
	ldreq r1, _020A0010 ; =default_link_is_on
	ldreq r0, _020A000C ; =link_is_on
	streq r1, [r0, #0x0]
	ldr r1, [r12, #0x4]
	ldr r0, _020A0014 ; =0x00000F88
	mla r5, r3, r1, r5
	ldr r1, [r12, #0xc]
	ldr r3, [r12, #0x10]
	mla r5, r1, r2, r5
	adds r2, r3, lr
	ldr r1, [r12, #0x14]
	mov r3, #0x0
	adc r1, r1, r5
	umull lr, r5, r1, r0
	mla r5, r1, r3, r5
	mla r5, r3, r0, r5
	ldr r6, [r4, #0x1c]
	ldr r0, _020A0018 ; =wlan_buf
	ldr lr, _020A001C ; =wlan_buflen
	str r6, [r0, #0x0]
	ldr r4, [r4, #0x20]
	ldr r0, _020A0020 ; =wlan_getpnt
	str r4, [lr, #0x0]
	str r3, [r0, #0x0]
	ldr lr, _020A0024 ; =wlan_putpnt
	ldr r4, _020A0028 ; =eport
	add r5, r5, #0x400
	ldr r0, _020A002C ; =CPSMyMac
	str r3, [lr, #0x0]
	str r2, [r12, #0x0]
	str r1, [r12, #0x4]
	strh r5, [r4, #0x0]
	bl OS_GetMacAddress
	ldr r0, _020A0030 ; =ip_conflict
	mov r2, #0x0
	strb r2, [r0, #0x0]
	mov r1, #0x800
	str r1, [sp, #0x0]
	ldr r0, _020A0034 ; =helper_threads_priority
	ldr r1, _020A0038 ; =tcpip
	ldr r4, [r0, #0x0]
	ldr r0, _020A003C ; =tcpip_thread
	ldr r3, _020A0040 ; =tcpip_stack+0x800
	str r4, [sp, #0x4]
	bl OS_CreateThread
	mov r1, #0x800
	ldr r0, _020A0034 ; =helper_threads_priority
	str r1, [sp, #0x0]
	ldr r1, [r0, #0x0]
	ldr r0, _020A0044 ; =scavenger_thread
	str r1, [sp, #0x4]
	ldr r1, _020A0048 ; =scavenger
	ldr r3, _020A004C ; =scavenger_stack+0x800
	mov r2, #0x0
	bl OS_CreateThread
	ldr r0, _020A003C ; =tcpip_thread
	bl OS_WakeupThreadDirect
	ldr r0, _020A0044 ; =scavenger_thread
	bl OS_WakeupThreadDirect
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_0209FFD4: .word _SDK_UbiquitousCPS
_0209FFD8: .word CPSiRand32ctx
_0209FFDC: .word 0x6C078965
_0209FFE0: .word 0x5D588B65
_0209FFE4: .word 0x00269EC3
_0209FFE8: .word CPSiAlloc
_0209FFEC: .word CPSiFree
_0209FFF0: .word empty_func
_0209FFF4: .word mode
_0209FFF8: .word mymss
_0209FFFC: .word 0x000005B4
_020A0000: .word offered_myip
_020A0004: .word yield_wait
_020A0008: .word dhcp_callback
_020A000C: .word link_is_on
_020A0010: .word default_link_is_on
_020A0014: .word 0x00000F88
_020A0018: .word wlan_buf
_020A001C: .word wlan_buflen
_020A0020: .word wlan_getpnt
_020A0024: .word wlan_putpnt
_020A0028: .word eport
_020A002C: .word CPSMyMac
_020A0030: .word ip_conflict
_020A0034: .word helper_threads_priority
_020A0038: .word tcpip
_020A003C: .word tcpip_thread
_020A0040: .word tcpip_stack+0x800
_020A0044: .word scavenger_thread
_020A0048: .word scavenger
_020A004C: .word scavenger_stack+0x800

	arm_func_start default_link_is_on
default_link_is_on: ; 0x020A0050
	mov r0, #0x1
	bx lr

	arm_func_start empty_func
empty_func: ; 0x020A0058
	bx lr

	arm_func_start OS_YieldThread__
OS_YieldThread__:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020A0094 ; =yield_wait
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020A0084
	bl OS_YieldThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A0084:
	bl OS_Sleep
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A0094: .word yield_wait

	arm_func_start reset_network_vars
reset_network_vars: ; 0x020A0098
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r1, _020A01B8 ; =CPSMyIp
	ldr r5, _020A01BC ; =CPSNoIpReason
	ldr r1, [r1, #0x0]
	ldr r3, _020A01C0 ; =CPSDnsIp
	cmp r1, #0x0
	mov r1, #0x0
	movne r6, #0x1
	ldr ip, _020A01C4 ; =CPSNetMask
	ldr r2, _020A01C8 ; =CPSDhcpServerIp
	moveq r6, #0x0
	ldr lr, _020A01B8 ; =CPSMyIp
	ldr r4, _020A01CC ; =CPSGatewayIp
	cmp r6, #0x0
	str r1, [r12, #0x0]
	str r1, [r3, #0x0]
	str r1, [r3, #0x4]
	str r1, [r2, #0x0]
	addeq sp, sp, #0x4
	str r0, [r5, #0x0]
	str r1, [lr, #0x0]
	str r1, [r4, #0x0]
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, _020A01D0 ; =arpcache
	mov r2, #0x60
	bl MI_CpuFill8
	ldr r0, _020A01D4 ; =OSi_ThreadInfo
	ldr r5, [r0, #0x8]
	cmp r5, #0x0
	beq _020A016C
	mov r4, #0x0
_020A011C:
	ldr r1, [r5, #0xa4]
	cmp r1, #0x0
	beq _020A0160
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	beq _020A0160
	ldrb r0, [r1, #0x8]
	cmp r0, #0xa
	beq _020A0148
	cmp r0, #0xb
	strneb r4, [r1, #0x8]
_020A0148:
	ldr r0, [r1, #0x4]
	cmp r0, #0x0
	beq _020A0160
	str r4, [r1, #0x4]
	ldr r0, [r1, #0x0]
	bl OS_WakeupThreadDirect
_020A0160:
	ldr r5, [r5, #0x68]
	cmp r5, #0x0
	bne _020A011C
_020A016C:
	ldr r6, _020A01D8 ; =fragtable
	mov r7, #0x0
	ldr r4, _020A01DC ; =CPSiFree
	mov r5, r7
_020A017C:
	ldrh r0, [r6, #0x4]
	cmp r0, #0x0
	beq _020A0198
	ldr r0, [r6, #0x34]
	ldr r1, [r4, #0x0]
	blx r1
	strh r5, [r6, #0x4]
_020A0198:
	add r7, r7, #0x1
	cmp r7, #0x8
	add r6, r6, #0x38
	blt _020A017C
	bl CPSi_SslCleanup
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A01B8: .word CPSMyIp
_020A01BC: .word CPSNoIpReason
_020A01C0: .word CPSDnsIp
_020A01C4: .word CPSNetMask
_020A01C8: .word CPSDhcpServerIp
_020A01CC: .word CPSGatewayIp
_020A01D0: .word arpcache
_020A01D4: .word OSi_ThreadInfo
_020A01D8: .word fragtable
_020A01DC: .word CPSiFree
