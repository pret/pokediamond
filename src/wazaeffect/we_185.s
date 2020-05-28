//==============================================================================
/**
 * @file	we_185.s
 * @brief	だましうち			185
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DAMASIUTI
	
// =============================================================================
//
//
//	■だましうち			185
//
//
// =============================================================================

#define WE185_SHAKE_WIDTH	( 4 )
#define WE185_SHAKE_NUM		( 1 )
#define WE185_SHAKE_SYNC	( 1 )//*/

WEST_DAMASIUTI:
	// 背景変更
	LOAD_PARTICLE_DROP	0,W_185_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	SE_L			SEQ_SE_DP_061
	
	// ポケモンOAM準備
	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	0,
	// 描画開始
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,
	
	FUNC_CALL	WEST_SP_WE_185, 0, 0
	
	WAIT	32
	PT_DROP_RESET_EX

	ADD_PARTICLE 	0,W_185_185_DAMASI_HIT,  EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_185_185_DAMASI_BALL, EMTFUNC_DEFENCE_POS
	SE_R			SEQ_SE_DP_030

	// ふるえさせる
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE185_SHAKE_WIDTH, 0,WE185_SHAKE_SYNC, WE185_SHAKE_NUM, WE_TOOL_E1 | WE_TOOL_SSP, 0, 0
	
	WAIT			15
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WAIT_FLAG
	
	// ポケモンOAM破棄
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	PT_DROP_RESET_EX
	
	// 背景戻す
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	
	SEQEND
