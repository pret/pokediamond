//==============================================================================
/**
 * @file	we_064.s
 * @brief	��			64
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TUTUKU

// =============================================================================
//
//
//	����			64
//
//
// =============================================================================
// ��]�p�x
#define ROTA_NUM_S ((360*0xffff) / 360)
#define ROTA_NUM_E ((350*0xffff) / 360)
#define ROTA_SYNC	(2)

WEST_TUTUKU:

	LOAD_PARTICLE_DROP	0,W_064_SPA
	
	FUNC_CALL		WEST_SP_POKEROTA_00, 3, ROTA_NUM_S, ROTA_NUM_E, ROTA_SYNC,0,0,0,0,0

	WAIT			2
	ADD_PARTICLE 	0,W_064_064_TUTUKU_HIT, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_064_064_BALL_BURN,	EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W030
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WAIT_FLAG	///< TCB�I���҂�
	
	SEQEND
