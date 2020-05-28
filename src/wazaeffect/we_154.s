//==============================================================================
/**
 * @file	we_154.s
 * @brief	�݂���Ђ�����			154
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MIDAREHIKKAKI
	
// =============================================================================
//
//
//	���݂���Ђ�����			154
//
//
// =============================================================================
WEST_MIDAREHIKKAKI:
	
	LOAD_PARTICLE_DROP	0,W_154_SPA
	LOAD_PARTICLE_DROP	1,W_001_SPA	
	ADD_PARTICLE 	0,W_154_154_MHIKKAKI_LINE1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_154_154_MHIKKAKI_LINE2, EMTFUNC_DEFENCE_POS
	
	SE_REPEAT_R		SEQ_SE_DP_W010,8,2
	
	///< ���
	WAIT			3	
	ADD_PARTICLE 	1,W_001_001_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	1,W_001_001_BALL_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*2,  WE_TOOL_E1 | WE_TOOL_SSP,


	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
