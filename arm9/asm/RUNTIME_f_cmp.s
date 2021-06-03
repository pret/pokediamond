	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _dgr
_dgr: ; 0x020EABA4
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EAC18
	cmn r12, r3, lsl #0x1
	bhs _020EAC2C
_020EABB8:
	orrs r12, r3, r1
	bmi _020EABE8
	cmp r1, r3
	cmpeq r0, r2
	movhi r0, #0x1
	movls r0, #0x0
	bx lr
_020EABD4:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EABE8:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bxeq lr
	cmp r3, r1
	cmpeq r2, r0
	movhi r0, #0x1
	movls r0, #0x0
	bx lr
_020EAC18:
	bne _020EABD4
	cmp r0, #0x0
	bhi _020EABD4
	cmn r12, r3, lsl #0x1
	blo _020EABB8
_020EAC2C:
	bne _020EABD4
	cmp r2, #0x0
	bhi _020EABD4
	b _020EABB8

	arm_func_start _dleq
_dleq: ; 0x020EAC3C
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EACBC
	cmn r12, r3, lsl #0x1
	bhs _020EACD0
_020EAC50:
	orrs r12, r3, r1
	bmi _020EAC84
	cmp r1, r3
	cmpeq r0, r2
	movls r0, #0x1
	movhi r0, #0x0
	bx lr
_020EAC6C:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAC84:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x1
	bne _020EACA8
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	orr r12, r12, #0x40000000
	msr cpsr_f, r12
	bxeq lr
_020EACA8:
	cmp r3, r1
	cmpeq r2, r0
	movls r0, #0x1
	movhi r0, #0x0
	bx lr
_020EACBC:
	bne _020EAC6C
	cmp r0, #0x0
	bhi _020EAC6C
	cmn r12, r3, lsl #0x1
	blo _020EAC50
_020EACD0:
	bne _020EAC6C
	cmp r2, #0x0
	bhi _020EAC6C
	b _020EAC50

	arm_func_start _dls
_dls: ; 0x020EACE0
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EAD58
	cmn r12, r3, lsl #0x1
	bhs _020EAD6C
_020EACF4:
	orrs r12, r3, r1
	bmi _020EAD24
	cmp r1, r3
	cmpeq r0, r2
	movcc r0, #0x1
	movcs r0, #0x0
	bx lr
_020EAD10:
	mov r0, #0x0
	mrs r12, cpsr
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAD24:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x0
	bne _020EAD44
	mrs r12, cpsr
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bxeq lr
_020EAD44:
	cmp r3, r1
	cmpeq r2, r0
	movcc r0, #0x1
	movcs r0, #0x0
	bx lr
_020EAD58:
	bne _020EAD10
	cmp r0, #0x0
	bhi _020EAD10
	cmn r12, r3, lsl #0x1
	blo _020EACF4
_020EAD6C:
	bne _020EAD10
	cmp r2, #0x0
	bhi _020EAD10
	b _020EACF4

	arm_func_start _deq
_deq: ; 0x020EAD7C
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EADE4
	cmn r12, r3, lsl #0x1
	bhs _020EADF8
_020EAD90:
	orrs r12, r3, r1
	bmi _020EADC0
	cmp r1, r3
	cmpeq r0, r2
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
_020EADAC:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EADC0:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x1
	bxeq lr
	cmp r3, r1
	cmpeq r2, r0
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
_020EADE4:
	bne _020EADAC
	cmp r0, #0x0
	bhi _020EADAC
	cmn r12, r3, lsl #0x1
	blo _020EAD90
_020EADF8:
	bne _020EADAC
	cmp r2, #0x0
	bhi _020EADAC
	b _020EAD90

	arm_func_start _dneq
_dneq: ; 0x020EAE08
	mov r12, #0x200000
	cmn r12, r1, lsl #0x1
	bhs _020EAE70
	cmn r12, r3, lsl #0x1
	bhs _020EAE84
_020EAE1C:
	orrs r12, r3, r1
	bmi _020EAE4C
	cmp r1, r3
	cmpeq r0, r2
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
_020EAE38:
	mov r0, #0x1
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EAE4C:
	orr r12, r0, r12, lsl #0x1
	orrs r12, r12, r2
	moveq r0, #0x0
	bxeq lr
	cmp r3, r1
	cmpeq r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	bx lr
_020EAE70:
	bne _020EAE38
	cmp r0, #0x0
	bhi _020EAE38
	cmn r12, r3, lsl #0x1
	blo _020EAE1C
_020EAE84:
	bne _020EAE38
	cmp r2, #0x0
	bhi _020EAE38
	b _020EAE1C

	arm_func_start _fgeq
_fgeq: ; 0x020EAE94
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAEDC
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movge r0, #0x1
	movlt r0, #0x0
	mrs r12, cpsr
	biclt r12, r12, #0x20000000
	orrge r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAEDC:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _fgr
_fgr: ; 0x020EAEF0
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAF38
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movgt r0, #0x1
	movle r0, #0x0
	mrs r12, cpsr
	bicle r12, r12, #0x20000000
	orrgt r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAF38:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _fleq
_fleq: ; 0x020EAF4C
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAF9C
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movle r0, #0x1
	movgt r0, #0x0
	mrs r12, cpsr
	orrgt r12, r12, #0x20000000
	bicgt r12, r12, #0x40000000
	bicle r12, r12, #0x20000000
	orrle r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EAF9C:
	mov r0, #0x0
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _fls
_fls: ; 0x020EAFB4
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	cmpcs r3, r1, lsl #0x1
	blo _020EAFFC
	cmp r0, #0x0
	bicmi r0, r0, #0x80000000
	rsbmi r0, r0, #0x0
	cmp r1, #0x0
	bicmi r1, r1, #0x80000000
	rsbmi r1, r1, #0x0
	cmp r0, r1
	movlt r0, #0x1
	movge r0, #0x0
	mrs r12, cpsr
	orrge r12, r12, #0x20000000
	biclt r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr
_020EAFFC:
	mov r0, #0x0
	mrs r12, cpsr
	orr r12, r12, #0x20000000
	msr cpsr_f, r12
	bx lr

	arm_func_start _feq
_feq: ; 0x020EB010
	mov r3, #0xff000000
	cmp r3, r0, lsl #0x1
	blo _020EB064
	cmp r3, r1, lsl #0x1
	blo _020EB064
	orr r3, r0, r1
	movs r3, r3, lsl #0x1
	moveq r0, #0x0
	bne _020EB044
	mrs r12, cpsr
	orr r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EB044:
	cmp r0, r1
	movne r0, #0x1
	moveq r0, #0x0
	mrs r12, cpsr
	bicne r12, r12, #0x40000000
	orreq r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
_020EB064:
	mov r0, #0x1
	mrs r12, cpsr
	bic r12, r12, #0x40000000
	msr cpsr_f, r12
	bx lr
