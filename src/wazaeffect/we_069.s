//==============================================================================
/**
 * @file	we_069.s
 * @brief	ちきゅうなげ			69
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TIKYUUNAGE
	
// =============================================================================
//
//
//	■ちきゅうなげ			69
//
//
// =============================================================================
WEST_TIKYUUNAGE:
	LOAD_PARTICLE_DROP	0,W_069_SPA

	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  16 + 10
	HAIKEI_CHG		BG_ID_069, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE

	HAIKEI_CHG_WAIT
	SE_C			SEQ_SE_DP_W327

	WAIT			5


	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  12 + 10
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  6 + 5
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  4 + 3
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  2 + 2
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  0
	
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  -6 - 0
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  -10 - 3
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  -16 - 5
	WAIT			5
	HAIKEI_PARA_CHG	WEDEF_GP_INDEX_SPEED_Y,  -24 - 10

	SE_R			SEQ_SE_DP_W070

	ADD_PARTICLE 	0,W_069_069_EARTH_BURN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_069_069_EARTH_HIT, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_069_069_EARTH_BURN2, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_S_WAIT, SHAKE_NUM_LONG2,  WE_TOOL_E1 | WE_TOOL_SSP,

	/// ゆらしいれてみたが・・・
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 5, 1, 3, 0
	WAIT			10

	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  -34
	HAIKEI_RECOVER	BG_ID_069, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP
	
	SE_R			SEQ_SE_DP_W088
	HAIKEI_CHG_WAIT
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	
	SEQEND
