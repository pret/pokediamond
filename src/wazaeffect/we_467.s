//==============================================================================
/**
 * @file	we_001.s
 * @brief	はたく
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	■はたく
//
//
// =============================================================================
WEST_Hataku:
	LOAD_PARTICLE_DROP	0, W_467_SPA
	
	TURN_CHK	TURN_1, TURN_2

	SEQEND

TURN_1:	
	SE_L			SEQ_SE_DP_W467
	
	/// ブリンク
	FUNC_CALL		WEST_SP_WE_T03, 2, 5, 0,
	
	WAIT			2
	
	///< 終わる世界
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 1	
	
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 1
	
	WAIT			15
	
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 0
	
	WAIT_FLAG

	SEQEND

TURN_2:
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 1	
	
	SE_R			SEQ_SE_DP_186
	WAIT_FLAG

	///< 間隔あけてダメージ
	WAIT			20	
	SE_R			SEQ_SE_DP_W007
	
	ADD_PARTICLE 	0, W_467_467_SHADOW_BURN01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0, W_467_467_SHADOW_HIT01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0, W_467_467_KEMURI_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_B_X, 0, SHAKE_B_WAIT, SHAKE_B_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT			5
	SE_WAITPLAY_R	SEQ_SE_DP_W109,8
	SE_WAITPLAY_R	SEQ_SE_DP_W109,13
	
	///< ブリンク復帰
	FUNC_CALL		WEST_SP_WE_T03, 2, 5, 0,
	
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 0

	WAIT_FLAG
	
	SEQEND
