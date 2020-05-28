//==============================================================================
/**
 * @file	we_312.s
 * @brief	�A���}�Z���s�[			312
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AROMASERAPII
	
// =============================================================================
//
//
//	���A���}�Z���s�[			312
//
//
// =============================================================================
WEST_AROMASERAPII:
	
	LOAD_PARTICLE_DROP	0,W_312_SPA
	
	///< �w�i�A�j��
	ADD_PARTICLE 	0,W_312_312_AROMA_BALL,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_312_312_HANABIRA,	 EMTFUNC_DEFENCE_POS

	///< �t�F�[�hIN
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 8, WE_PAL_GREEN_2,
	WAIT_FLAG
	
	SE_C			SEQ_SE_DP_W080
	WAIT			60
	SE_L			SEQ_SE_DP_W234

	///< �t�F�[�hOUT
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 8, 0, WE_PAL_GREEN_2,
	WAIT_FLAG

	SE_WAITPLAY_L	SEQ_SE_DP_REAPOKE,23

	///< �񕜃A�j��
	ADD_PARTICLE 	0,W_312_312_KIRA_BURN, 	 EMTFUNC_AT_SIDE
	ADD_PARTICLE 	0,W_312_312_CIRCLE_BURN, EMTFUNC_AT_SIDE
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M2, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
