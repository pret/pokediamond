//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_snd_def.h
 *	@brief		図鑑音定義
 *	@author		tomoya takahashi
 *	@data		2006.02.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SND_DEF_H__
#define __ZKN_SND_DEF_H__

#include "include/system/snd_tool.h"

#undef GLOBAL
#ifdef	__ZKN_SND_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_SND_SHUTTER				( SEQ_SE_DP_BUTTON01 )		// シャッター開閉

#define ZKN_SND_SELECT_MOVE_ONE		( SEQ_SE_DP_DENSI06 )		// 選択移動(下画面にタッチも含む)
#define ZKN_SND_SLIDE				( SEQ_SE_DP_DENSI06 )		// スライド音

#define ZKN_SND_SEARCH				( SEQ_SE_DP_Z_SEARCH )		// 検索音

#define ZKN_SND_SWITCH				( SEQ_SE_DP_KATI )			// 鳴き声画面のスイッチ
#define ZKN_SND_DIAL				( SEQ_SE_DP_KATI )			// ダイアル音

#define ZKN_SND_SELECT				( SEQ_SE_DP_DECIDE )		// 決定音
#define ZKN_SND_CANCEL				( SEQ_SE_DP_DECIDE )		// キャンセル
#define ZKN_SND_BUTTON				( SEQ_SE_DP_DECIDE )		// ボタンにタッチ

#undef	GLOBAL
#endif		// __ZKN_SND_DEF_H__

