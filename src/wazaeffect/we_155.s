//==============================================================================
/**
 * @file	we_155.s
 * @brief	ホネブーメラン			155
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HONEBUUMERAN
	
// =============================================================================
//
//
//	■ホネブーメラン			155
//
//
// =============================================================================
#define BONE_RES_NO			(0)
#define BONE_RES_NUM		(1)
#define BONE_ACT_NUM		(1)

#define WE155_SHAKE_WIDTH	( 4 )
#define WE155_SHAKE_NUM		( 1 )
#define WE155_SHAKE_SYNC	( 1 )

WEST_HONEBUUMERAN:

	LOAD_PARTICLE_DROP	0,W_001_SPA
	
	///<初期化処理　読み込み処理
	CATS_RES_INIT		BONE_RES_NO, BONE_ACT_NUM, BONE_RES_NUM, BONE_RES_NUM, BONE_RES_NUM, BONE_RES_NUM, 0, 0
	CATS_CAHR_RES_LOAD	BONE_RES_NO, EFFECT_155_NCGR_BIN
	CATS_PLTT_RES_LOAD	BONE_RES_NO, EFFECT_155_NCLR, 1
	CATS_CELL_RES_LOAD	BONE_RES_NO, EFFECT_155_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	BONE_RES_NO, EFFECT_155_NANR_BIN
	
	///<動作
	CATS_ACT_ADD		BONE_RES_NO, WEST_CSP_WE_155, EFFECT_155_NCGR_BIN, EFFECT_155_NCLR, EFFECT_155_NCER_BIN, EFFECT_155_NANR_BIN, 0, 0, 0,0,
	//SE_L			SEQ_SE_DP_W233

	// ヒットマーク　
	WAIT	5
	SE_FLOW_LR		SEQ_SE_DP_HURU
	WAIT	5
	ADD_PARTICLE 	0,W_001_001_HIT_MARK, EMTFUNC_DEFENCE_POS
	SE_R			SEQ_SE_DP_030

	// ふるえさせる
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE155_SHAKE_WIDTH, 0,WE155_SHAKE_SYNC, WE155_SHAKE_NUM, WE_TOOL_E1 | WE_TOOL_SSP, 0, 0
	

	// 骨をとる音
	WAIT 8
	SE_L			SEQ_SE_DP_W091
	
	WAIT_PARTICLE
	WAIT_FLAG

	///<破棄処理
	CATS_RES_FREE		BONE_RES_NO

	EXIT_PARTICLE	0,
	
	SEQEND
