/**
 *	@file	fld_ranking.h
 *	@brief	フィールド　ランキング画面描画処理
 *	@author	Miyuki Iwasawa
 *	@date	06.06.06
 */

#ifndef __H_FLD_RANKING_H__
#define __H_FLD_RANKING_H__

///呼び出しモード設定
#define RANKING_GLB_BTL		(0)	///<グローバルバトル
#define RANKING_GLB_POKE	(1)	///<グローバルポケモン
#define RANKING_GLB_CONTEST	(2)	///<グローバルコンテスト
#define RANKING_GRP_BTL		(3)	///<グループバトル
#define RANKING_GRP_POKE	(4)	///<グループポケモン
#define RANKING_GRP_CONTEST	(5)	///<グループコンテスト



//============================================================================================
//
//	ここから下はプログラムでのみ参照する定義
//
//======================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_

#undef	GLOBAL
#ifdef __FLD_RANKING_H_GLOBAL
#define GLOBAL /***/
#else
#define GLOBAL extern	
#endif

//--------------------------------------------------------------
/**
 * @brief	ランキング画面サブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		移動方向
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_RankingViewCall( GMEVENT_CONTROL *event,u16 mode);



#endif	//__ASM_NO_DEF_

#endif	//__H_FLD_RANKING_H__

