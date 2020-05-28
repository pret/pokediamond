//=============================================================================
/**
 * @file	ug_snd_def.h
 * @brief	地下用サウンド定義置き換えファイル
 * @author	Katsumi Ohno
 * @date    2006.3.28
 */
//=============================================================================

#ifndef __UG_SND_DEF_H__
#define __UG_SND_DEF_H__

#include "system/snd_tool.h"


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define UG_SE_HOLE_IN			(SEQ_SE_DP_KAIDAN2)		// 穴に入った
#define UG_SE_CLOSE_DOOR		(SEQ_SE_DP_DOOR)		// ドアを閉める
//#define UG_SE_RADAR_USE		(SEQ_SE_DP_UG_006)		// レーダー使っている時 ???でてないか？
#define UG_SE_SMOG_ANIM			(SEQ_SE_DP_UG_008)		// 煙を出す時

//-----------------------------------------------------------------------------
//	化石掘り
//-----------------------------------------------------------------------------
#define UG_SE_PICK				(SEQ_SE_DP_UG_002)		//ピッケルたたき
#define UG_SE_HUMMER			(SEQ_SE_DP_UG_003)		//ハンマーたたき
#define UG_SE_HARD_ROCK			(SEQ_SE_DP_UG_004)		//硬い石たたき
#define UG_SE_FIND_FOSSIL		(SEQ_SE_DP_KIRAKIRA3)	//化石見つけ

//#define UG_SE_DIG_FOSSIL		(SEQ_SE_DP_KIRAKIRA)	//化石完全に見つけ
#define UG_SE_DIG_FOSSIL		(SEQ_SE_DP_KIRAKIRA4)	//化石完全に見つけ

#define UG_SE_BLOKEN_WALL		(SEQ_SE_DP_UG_001)		//壁壊れ
#define UG_SE_TOUCH_BUTTON		(SEQ_SE_DP_SELECT)		//ピッケル、ハンマー切り替えボタン

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define UG_SE_RADAR				(SEQ_SE_DP_UG_005)		//レーダー
#define UG_SE_RADAR_ECHO		(SEQ_SE_DP_UG_006)		//エコー
#define UG_SE_SMOKE				(SEQ_SE_DP_UG_008)		//煙、罠を仕掛ける
#define UG_SE_ALARM				(SEQ_SE_DP_UG_007)		//アラーム
#define UG_SE_DRILL				(SEQ_SE_DP_DORIRU)		//ドリル

#define UG_SE_BURY				(SEQ_SE_DP_SUTYA)		// ものを埋めた時

//#define UG_SE_FLAG_DELIVERY	(SEQ_SE_DP_UG_020)		// ハタを運んだ
#define UG_SE_FLAG_DELIVERY		(SEQ_SE_DP_UG_027)		// ハタを運んだ

#define UG_SE_FLAG_CONQUER		(SEQ_SE_DP_UG_021)		// はた奪った  ＋　とりかえした
#define UG_SE_FLAG_STEAL		(SEQ_SE_DP_CARD10)		// はた奪われた

#define UGT_SE_BUBBLE			(SEQ_SE_DP_UG_022)		// あわ
#define UGT_SE_HUMMER			(SEQ_SE_DP_UG_023)		// いわこわし
#define UGT_SE_BLOKEN			(SEQ_SE_DP_UG_026)		// いわこわれた
#define UGT_SE_SMOG				(SEQ_SE_DP_UG_025)		// けむりふき
#define UGT_SE_FIER				(SEQ_SE_DP_UG_024)		// 火が揺れている
#define UGT_SE_TRAPEND			(SEQ_SE_DP_WIN_OPEN2)	// 罠解除

//-----------------------------------------------------------------------------
//	ME
//-----------------------------------------------------------------------------
#define UG_SE_FANFA				(SEQ_SE_DP_PIRORIRO2)   // 地下の共通ファンファーレ
#define UG_SE_FIND				(UG_SE_FANFA)			// 物を見つけた時(ME)
#define UG_SE_SEND_GOODS		(UG_SE_FANFA)			// 物をあげた時(ME)
#define UG_SE_LEVELUP_FLAG		(UG_SE_FANFA)			// ファンファーレ
#define UG_SE_FOSSIL_CLEAR		(UG_SE_FANFA)            // 全部掘り出した


#endif  //__UG_SND_DEF_H__
