//==============================================================================
/**
 * @file	we_064.s
 * @brief	つつく			64
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TUTUKU

// =============================================================================
//
//
//	■つつく			64
//
//
// =============================================================================
// 回転角度
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
	
	WAIT_FLAG	///< TCB終了待ち
	
	SEQEND
