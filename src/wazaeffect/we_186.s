//==============================================================================
/**
 * @file	we_186.s
 * @brief	�Ă񂵂̃L�b�X			186
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TENSINOKISSU
	
// =============================================================================
//
//
//	���Ă񂵂̃L�b�X			186
//
//
// =============================================================================
WEST_TENSINOKISSU:
	LOAD_PARTICLE_DROP	0,W_186_SPA
	ADD_PARTICLE 	0,W_186_186_TENSI_ANG,	EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_041

	WAIT			10
	
	SE_WAITPLAY_R	SEQ_SE_DP_W213,65
	ADD_PARTICLE 	0,W_186_186_TENSI_HART, EMTFUNC_DEFENCE_POS

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
