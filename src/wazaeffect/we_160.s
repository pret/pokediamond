//==============================================================================
/**
 * @file	we_160.s
 * @brief	�e�N�X�`���[			160
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TEKUSUTYAA
	
// =============================================================================
//
//
//	���e�N�X�`���[			160
//
//
// =============================================================================
WEST_TEKUSUTYAA:
	
	LOAD_PARTICLE_DROP	0,W_160_SPA
	ADD_PARTICLE 	0,W_160_160_TEX_DUST, EMTFUNC_ATTACK_POS

	SE_REPEAT_L		SEQ_SE_DP_W112,2,4

	SE_WAITPLAY_L	SEQ_SE_DP_351,42

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
