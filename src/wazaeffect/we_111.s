//==============================================================================
/**
 * @file	we_111.s
 * @brief	�܂邭�Ȃ�			111
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MARUKUNARU
	
// =============================================================================
//
//
//	���܂邭�Ȃ�			111
//
//
// =============================================================================
WEST_MARUKUNARU:
	
	LOAD_PARTICLE_DROP	0,W_111_SPA
	ADD_PARTICLE 	0,W_111_BALL_BIG,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_111_RING_TURN02,	EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W161
	//SE_WAITPLAY_L	SEQ_SE_DP_141,10
	SE_WAITPLAY_L	SEQ_SE_DP_166,10

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
