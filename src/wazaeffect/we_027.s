//==============================================================================
/**
 * @file	we_027.s
 * @brief	まわしげり			27
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MAWASIGERI
	
// =============================================================================
//
//
//	■まわしげり			27
//
//
// =============================================================================
#define WE098_SHAKE_W_X	(2)		// ふり幅
#define WE098_SHAKE_NUM	(1)		// ふる回数
#define WE098_SHAKE_SYNC (1)	// シンク数
WEST_MAWASIGERI:

	LOAD_PARTICLE_DROP	0,W_027_SPA

	// ポケモンOAM準備
	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,
	POKEOAM_RES_LOAD	1,

	// 描画開始
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,

	FUNC_CALL		WEST_SP_WE_098, 0,0,0,0,0,0,0,0,0
	ADD_PARTICLE 	0,W_027_FOOT_TURN01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_027_RING_TURN01,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,	
	//SE_R			SEQ_SE_DP_030
	//SE_WAITPLAY_R	SEQ_SE_DP_050,10
	SE_R			SEQ_SE_DP_050
	WAIT 20

	// ポケモンOAM破棄 PTアタックでOAMのままだとヒットマークが出ない･･･。
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	PT_DROP_RESET_EX
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE098_SHAKE_W_X, 0,WE098_SHAKE_SYNC, WE098_SHAKE_NUM, WE_TOOL_E1 | WE_TOOL_SSP, 0, 0
	ADD_PARTICLE 	0,W_027_001_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_027_001_BALL_BURN,	EMTFUNC_DEFENCE_POS
	SE_R			SEQ_SE_DP_030

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WAIT_FLAG	///<TCB待ち

	SEQEND
