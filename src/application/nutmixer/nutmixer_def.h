/**
 *	@file	nutmixer_def.h
 *	@brief	ナッツミキサー　定数定義
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_NUTMIXER_DEF_H__
#define __H_NUTMIXER_DEF_H__

///プレイモード定義
#define NUTMIXER_PLAY_LOCAL	(0)
#define NUTMIXER_PLAY_COMM	(1)

///メンバー数定義
#define NUTMIXER_MEMBER_MAX	(4)

///通信同期待ち　アンバー
typedef enum{
	SYNCHROID_NONE,				///<通信同期ナシ
	SYNCHROID_BAG_END,			///<バック終了待ち
	SYNCHROID_GAME_START,		///<ゲーム開始
	SYNCHROID_GAME_END,			///<ゲーム終了
};

#ifdef PM_DEBUG
///< AUTOミキサー処理
//#define DEBUG_NUTMIXER_AUTO	
#endif


#endif	//__H_NUTMIXER_DEF_H__
