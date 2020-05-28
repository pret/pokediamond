//============================================================================================
/**
 * @file	plist_snd_def.h
 * @brief	ポケモンリスト画面SE定義
 * @author	Hiroyuki Nakamura
 * @date	2006.04.06
 */
//============================================================================================
#include "system/snd_tool.h"

#define	PLIST_SE_CURSOR		( SEQ_SE_DP_SELECT )	// カーソル移動
#define	PLIST_SE_ENTER		( SEQ_SE_DP_SELECT )	// 決定
#define	PLIST_SE_CANCEL		( SEQ_SE_DP_SELECT )	// キャンセル

#define	PLIST_SE_ERROR		( SEQ_SE_DP_CUSTOM06 )	// エラー

//#define	PLIST_SE_MV_OUT	( SEQ_SE_DP_SYU02 )			// 並び替え・外へ
#define	PLIST_SE_MV_OUT		( SEQ_SE_DP_POKELIST_001 )	// 並び替え・外へ

//#define	PLIST_SE_MV_IN	( SEQ_SE_DP_SYU02 )			// 並び替え・中へ
#define	PLIST_SE_MV_IN		( SEQ_SE_DP_POKELIST_001 )	// 並び替え・中へ

#define	PLIST_SE_TP_BALL	( SEQ_SE_DP_BUTTON9 )	// 下画面ボタンタッチ
