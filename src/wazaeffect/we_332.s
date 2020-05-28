//==============================================================================
/**
 * @file	we_332.s
 * @brief	�΂߂�����			332
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TUBAMEGAESI
	
// =============================================================================
//
//
//	���΂߂�����			332
//
//
// =============================================================================
WEST_TUBAMEGAESI:
	LOAD_PARTICLE_DROP	0,W_332_SPA
	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,
	POKEOAM_RES_LOAD	1,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 8, WE_PAL_BLACK
	WAIT			15
	SE_R			SEQ_SE_DP_W013B
	SE_WAITPLAY_R	SEQ_SE_DP_W013,10

	// �`��J�n
	POKEOAM_DROP	WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP	WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,
	PT_DROP_EX		WEDEF_DROP_M2, WEDEF_DROP_M2,

	FUNC_CALL		WEST_SP_WE_098, 0,0,0,0,0,0,0,0,0

	ADD_PARTICLE 	0,W_332_332_LINE1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_332_332_LINE2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_332_332_LINE3, EMTFUNC_DEFENCE_POS

	ADD_PARTICLE 	0,W_332_332_BALL_BURN, EMTFUNC_DEFENCE_POS
	
	WAIT			10
	POKE_OAM_ENABLE	WEDEF_POKE_CAP_ID_EX, 0,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_RES_FREE
	PT_DROP_RESET_EX

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 8, 0, WE_PAL_BLACK
	WAIT_FLAG	
	
	SEQEND
