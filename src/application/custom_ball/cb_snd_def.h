//==============================================================================
/**
 * @file	cb_snd_def.h
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.05.08(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "system/snd_tool.h"

/*

	Snd_SePlay

 */

enum {
	
	CB_SE_POP		= SEQ_SE_DP_BOX02,				///< シールが出した
	CB_SE_DROP		= SEQ_SE_DP_BOX01,				///< シールを置いた
	
	CB_SE_TOUCH		= SEQ_SE_DP_BUTTON9,			///< タッチ
	
	CB_SE_LIMIT		= SEQ_SE_DP_CUSTOM06,			///< もう置けない(8枚置いた)
	CB_SE_NONE		= SEQ_SE_DP_CUSTOM06,			///< 残り0枚
	
	CB_SE_PLAY		= SEQ_SE_DP_DECIDE,				///< 再生ボタン
	CB_SE_UP		= SEQ_SE_DP_CUSTOM02,			///< ↑
	CB_SE_DOWN		= SEQ_SE_DP_CUSTOM02,			///< ↓
	CB_SE_DEC_S		= SEQ_SE_DP_SELECT,				///< 決定
	CB_SE_DEC		= SEQ_SE_DP_PIRORIRO,			///< 決定
	CB_SE_CAN		= SEQ_SE_DP_DECIDE,				///< キャンセル
	
	CB_SE_BOMB		= SEQ_SE_DP_CUSTOM05,			///< ボールボワン
	
	CB_SE_CURSOR	= SEQ_SE_DP_SELECT,
	
};

