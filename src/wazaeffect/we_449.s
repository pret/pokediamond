//==============================================================================
/**
 * @file	we_001.s
 * @brief	�͂���
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	���͂���
//
//
// =============================================================================
WEST_449:
	
	LOAD_PARTICLE_DROP	0,W_449_SPA
		
	///< �t�F�[�h�C��
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 15, WE_PAL_WHITE,
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_449_449_SABAKI_DUST,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_449_449_SABAKI_BLACKBALL1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_449_449_SABAKI_FIRE,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_449_449_SABAKI_BALL,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_449_449_SABAKI_BLACKBALL2,	EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_W460
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_R			SEQ_SE_DP_W082B
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	

	///< �t�F�[�h�A�E�g
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 15, 0, WE_PAL_WHITE,
	WAIT_FLAG
		
	SEQEND

