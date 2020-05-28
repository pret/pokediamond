//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_snd_def.h
 *	@brief		まぜまぜ音
 *	@author		tomoya takahashi
 *	@data		2006.06.06
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_SND_DEF_H__
#define __NMIX_GAME_SND_DEF_H__

#include "system/snd_play.h"
#include "system/snd_tool.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_SND_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


// スープ状態
#define NMIXGAME_SE_SOOP_ROTA		(SEQ_SE_DP_NM01)			// スープかき混ぜ
#define NMIXGAME_SE_SOOP_KOBORE		(SEQ_SE_DP_NM02)			// スープこぼれ
#define NMIXGAME_SE_SOOP_KOGE		(SEQ_SE_DP_NM03)			// スープこげる音

// クリーム状態
//#define NMIXGAME_SE_CREAM_ROTA	(SEQ_SE_DP_NM04)			// クリームかき混ぜ
#define NMIXGAME_SE_CREAM_ROTA		(SEQ_SE_DP_NM04_2)			// クリームかき混ぜ
#define NMIXGAME_SE_CREAM_KOBORE	(SEQ_SE_DP_NM05)			// クリームこぼれ
#define NMIXGAME_SE_CREAM_KOGE		(SEQ_SE_DP_NM03)			// クリームこげる音

// そぼろ状態
//#define NMIXGAME_SE_SOBORO_ROTA	(SEQ_SE_DP_NM07)			// そぼろかき混ぜ
#define NMIXGAME_SE_SOBORO_ROTA		(SEQ_SE_DP_NM07_2)			// そぼろかき混ぜ
#define NMIXGAME_SE_SOBORO_KOGE		(SEQ_SE_DP_NM08)			// そぼろこげる音

// その他の音
#define NMIXGAME_SE_NUTS_SOOP_IN	(SEQ_SE_DP_NM09)			// 木の実スープイン
#define NMIXGAME_SE_COUNT_DOWN		(SEQ_SE_DP_NM10)			// カウントダウン
#define NMIXGAME_SE_GAME_START		(SEQ_SE_DP_NM10_2)			// 開始音
#define NMIXGAME_SE_GAME_KIRAKIRA	(SEQ_SE_DP_NM11)			// キラキラエフェクト音
//#define NMIXGAME_SE_GAME_ROTAWAY_ON	(SEQ_SE_DP_NM12)		// 回転方向変更音
#define NMIXGAME_SE_GAME_ROTAWAY_ON	(SEQ_SE_DP_NM12_2)			// 回転方向変更音
#define NMIXGAME_SE_GAME_END		(SEQ_SE_DP_NM13)			// 終了音
#define NMIXGAME_SE_GAME_RESULT_ON	(SEQ_SE_DP_NM14)			// 結果表示テキストが出るときに出す音




#undef	GLOBAL
#endif		// __NMIX_GAME_SND_DEF_H__

