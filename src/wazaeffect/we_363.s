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

	.global		WEST_363
	
// =============================================================================
//
//
//	��������̂߂���
//
//
// =============================================================================
WEST_363:

	LOAD_PARTICLE_DROP	0,W_363_SPA
	ADD_PARTICLE 	0,W_363_363_DAICHI_BALL,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_363_363_DAICHI_BALL2,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_363_363_DAICHI_RING,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_363_363_DAICHI_RING2,	EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W363
	SE_WAITPLAY_L	SEQ_SE_DP_REAPOKE,40

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND

