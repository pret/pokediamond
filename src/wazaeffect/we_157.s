//==============================================================================
/**
 * @file	we_157.s
 * @brief	����Ȃ���			157
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IWANADARE
	
// =============================================================================
//
//
//	������Ȃ���			157
//
//
// =============================================================================
WEST_IWANADARE:
	
	LOAD_PARTICLE_DROP	0,W_157_SPA
	ADD_PARTICLE 	0,W_157_IWA_NADARE01, EMTFUNC_DF_SIDE
	ADD_PARTICLE 	0,W_157_IWA_NADARE02, EMTFUNC_DF_SIDE
	ADD_PARTICLE 	0,W_157_IWA_NADARE03, EMTFUNC_DF_SIDE

	WAIT			10
	SE_REPEAT_R		SEQ_SE_DP_W088,1,20
	
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E2 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
