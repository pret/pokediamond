//==============================================================================
/**
 * @file	we_233.s
 * @brief	���Ă݂Ȃ�			233
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ATEMINAGE
	
// =============================================================================
//
//
//	�����Ă݂Ȃ�			233
//
//
// =============================================================================
WEST_ATEMINAGE:
	LOAD_PARTICLE_DROP	0,W_233_SPA
		
	FUNC_CALL		WEST_SP_WE_233, 0,0,0,0,0,0,0,0,0
	SE_REPEAT_L		SEQ_SE_DP_W233,22,3
	
	WAIT	66

	ADD_PARTICLE 	0,W_233_033_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_233_033_BALL_BURN,	EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_030
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WAIT_FLAG
	
	SEQEND
