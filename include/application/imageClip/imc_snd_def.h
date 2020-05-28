//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_snd_def.h
 *	@brief		サウンド定数	
 *	@author		tomoya takahashi
 *	@data		2005.10.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_SND_DEF_H__
#define __IMC_SND_DEF_H__

#include "system/snd_play.h"
#include "system/snd_tool.h"

#undef GLOBAL
#ifdef	__IMC_SND_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//#define IMC_SE_RET_BUTTON_ON	(SEQ_SE_DP_SELECT)			// 切り替えボタンを押した音
//#define IMC_SE_RET_BUTTON_ON	(SEQ_SE_DP_TARARARAN)		// 切り替えボタンを押した音
#define IMC_SE_RET_BUTTON_ON	(SEQ_SE_DP_MAZYO3)			// 切り替えボタンを押した音

//#define IMC_SE_BG_CHANGE		(SEQ_SE_DP_SELECT)			// 背景が変わったときの音
#define IMC_SE_BG_CHANGE		(SEQ_SE_DP_SYARAAN)			// 背景が変わったときの音

//#define IMC_SE_BUTTON_ON		(SEQ_SE_DP_SELECT)			// ボタンを押した音
#define IMC_SE_BUTTON_ON		(SEQ_SE_DP_PASO)			// ボタンを押した音

//#define IMC_SE_HAVE_SAMETHING	(SEQ_SE_DP_SELECT)			// 左ボックスで何か選択した音
//#define IMC_SE_HAVE_SAMETHING	(SEQ_SE_DP_DECIDE2)			// 左ボックスで何か選択した音
#define IMC_SE_HAVE_SAMETHING	(SEQ_SE_DP_BOX02)			// 左ボックスで何か選択した音

//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_SELECT)		// 左ボックスで放した音
//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_PIKO2)		// 左ボックスで放した音
//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_BUTTON3)		// 左ボックスで放した音
//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_DECIDE2)		// 左ボックスで放した音
#define IMC_SE_TAKE_OFF				(SEQ_SE_DP_BOX02)		// 左ボックスで放した音

//#define IMC_SE_RET_LBOX			(SEQ_SE_DP_SELECT)		// 範囲がでアクセサリを放して左ボックスにアクセサリが戻るときの音
//#define IMC_SE_RET_LBOX			(SEQ_SE_DP_DANSA9)		// 範囲がでアクセサリを放して左ボックスにアクセサリが戻るときの音
//#define IMC_SE_RET_LBOX			(SEQ_SE_DP_BEYON)		// 範囲がでアクセサリを放して左ボックスにアクセサリが戻るときの音
#define IMC_SE_RET_LBOX			(SEQ_SE_DP_HYUN2)			// 範囲がでアクセサリを放して左ボックスにアクセサリが戻るときの音

//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_DENSI02)		// 右ボックスにおいたとき
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_DENSI05)		// 右ボックスにおいたとき
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_PIKO)		// 右ボックスにおいたとき
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_BUTTON3)		// 右ボックスにおいたとき
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_DECIDE2)		// 右ボックスにおいたとき
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_IMC_001)		// 右ボックスにおいたとき
#define IMC_SE_ON_RBOX				(SEQ_SE_DP_BOX01)		// 右ボックスにおいたとき

//#define IMC_SE_BUTTON_ENDON		(SEQ_SE_DP_PASO)		// 終わるボタンを押した音
#define IMC_SE_BUTTON_ENDON			(SEQ_SE_DP_PIRORIRO)	// 終わるボタンを押した音

//下画面の共通「はい、いいえ」になったので未使用
//#define IMC_SE_RET_BUTTON_FINISH	(SEQ_SE_DP_TARARARAN)	// 最終決定を押した音
#define IMC_SE_RET_BUTTON_FINISH	(SEQ_SE_DP_MAZYO)		// 最終決定を押した音


/////////////////////////////////////
// コンテスト
#define IMC_SE_CON_10COUNT			(SEQ_SE_DP_HYUN2)		// ラスト１０カウント
#define IMC_SE_CON_FINISH			(SEQ_SE_DP_MAZYO)		// 終～了～

#define IMC_SE_CON_DOOR_CLOSE		(SEQ_SE_DP_CON_017)	// ドア閉まり音
#define IMC_SE_CON_START			(SEQ_SE_DP_CON_016)		// クリップ開始音



#undef	GLOBAL
#endif		// __IMC_SND_DEF_H__

