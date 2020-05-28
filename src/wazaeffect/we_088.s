//==============================================================================
/**
 * @file	we_088.s
 * @brief	���킨�Ƃ�			88
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IWAOTOSI
	
// =============================================================================
//
//
//	�����킨�Ƃ�			88
//
//
// =============================================================================
WEST_IWAOTOSI:
	
	LOAD_PARTICLE_DROP	0,W_088_SPA
	ADD_PARTICLE 	0,W_088_088_IWA_DOWN01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_088_088_IWA_DOWN02, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_088_088_IWA_BURN,	EMTFUNC_DEFENCE_POS

	WAIT			12
	SE_R			SEQ_SE_DP_W088
	WAIT			8
	
	SE_R			SEQ_SE_DP_W070
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, SHAKE_S_Y, SHAKE_M_WAIT, SHAKE_NUM_LONG2,  WE_TOOL_E1 | WE_TOOL_SSP,
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
