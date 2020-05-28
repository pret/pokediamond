//============================================================================================
/**
 * @file	pmsi_sound_def.h
 * @bfief	ボックス画面サウンドナンバー定義
 * @author	taya
 * @date	06.02.15
 */
//============================================================================================

#ifndef __PMSI_SOUND_DEF_H__
#define __PMSI_SOUND_DEF_H__

#include "system\snd_tool.h"


#define  SOUND_MOVE_CURSOR		(SEQ_SE_DP_SELECT)		// カーソル移動

//#define  SOUND_DECIDE			(SEQ_SE_DP_DECIDE)		// 決定音
#define  SOUND_DECIDE			(SEQ_SE_DP_SELECT)		// 決定音

//#define  SOUND_CANCEL			(SEQ_SE_DP_DECIDE)		// キャンセル音
#define  SOUND_CANCEL			(SEQ_SE_DP_SELECT)		// キャンセル音

#define  SOUND_CHANGE_SENTENCE	(SEQ_SE_DP_SELECT)		// 文章変更

//#define  SOUND_CHANGE_CATEGORY	(SEQ_SE_DP_DECIDE)	// カテゴリ変更
#define  SOUND_CHANGE_CATEGORY	(SEQ_SE_DP_BUTTON9)		// カテゴリ変更

//#define  SOUND_DISABLE_CATEGORY	(SEQ_SE_DP_WALL_HIT)// 無効なカテゴリ選択
#define  SOUND_DISABLE_CATEGORY	(SEQ_SE_DP_CUSTOM06)	// 無効なカテゴリ選択

//#define  SOUND_DISABLE_BUTTON	(SEQ_SE_DP_WALL_HIT)	// 無効なボタンタッチ
#define  SOUND_DISABLE_BUTTON	(SEQ_SE_DP_CUSTOM06)	// 無効なボタンタッチ

#endif
