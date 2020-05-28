//==============================================================================
/**
 * @file	we_314.s
 * @brief	�G�A�J�b�^�[			314
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_EAKATTAA
	
// =============================================================================
//
//
//	���G�A�J�b�^�[			314
//
//
// =============================================================================
WEST_EAKATTAA:
	
	LOAD_PARTICLE_DROP	0,W_314_SPA
	ADD_PARTICLE 	0,W_314_314_AIR_BEAM,	EMTFUNC_DF_SIDE
	ADD_PARTICLE 	0,W_314_314_AIR_SLASH,	EMTFUNC_DF_SIDE

	WAIT			10
	SE_REPEAT_C		SEQ_SE_DP_W104,2,6
	WAIT			5	
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 2, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 2, 1, 2,  WE_TOOL_E2 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_W015

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
