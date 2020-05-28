//==============================================================================
/**
 * @file	we_012.s
 * @brief	�n�T�~�M���`��			12
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HASAMIGIROTIN
	
// =============================================================================
//
//
//	���n�T�~�M���`��			12
//
//
// =============================================================================
WEST_HASAMIGIROTIN:
	
	LOAD_PARTICLE_DROP	0,W_012_SPA

	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,

	ADD_PARTICLE 	0,W_012_012_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_012_012_BALL_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_012_012_CUT_L01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_012_012_CUT_R01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_012_012_CUT_L02,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_012_012_CUT_R02,	EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W011
	
	WAIT			20
	//SE_R			SEQ_SE_DP_W013
	SE_R			SEQ_SE_DP_W462
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
		
	SEQEND
