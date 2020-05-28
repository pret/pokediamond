/**
 *	@file	nutmixer_sys.h
 *	@brief	ナッツミキサー　ローカルヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_NUTMIXER_SYS_H__
#define __H_NUTMIXER_SYS_H__

#include "nutmixer_def.h"

typedef struct _NUTMIXER_WORK{
	int	heapID;		///<ヒープID
	u16	mem_num;	///<メンバー数
	u16	comm_f:8;	///<ローカルか通信か(通信ならTRUE)
	u16	endseq_f:4;	///<メイン終了フラグ
	u16	view_f:4;	///<描画関数呼び出しフラグ

	int	itemno;	///<選んだ木の実ナンバー
	BAG_CURSOR* bag_cursor;	// バッグカーソル位置記憶領域
	
	NUTMIXER_PARAM* param;	///<引継ぎパラメータ
	int		m_seq;		///<メインコマンドシーケンス
	void*	app_wk;		///<サブアプリワーク
	PROC	*proc;		///<プロセス

	// ゲームから続けるか取得用
	BOOL game_next;		///< TRUEゲームを続ける FALSE終わる

}NUTMIXER_WORK;

//メインコマンド関数型
typedef int (*NMIXER_MFUNC)(struct _NUTMIXER_WORK* mp,void* wk,int* seq);

///メインシーケンス定義
typedef enum{
 NMSEQ_BAG_MAIN,
 NMSEQ_GAME_CALL,
 NMSEQ_GAME_WAIT,
 NMSEQ_GAME_END,
 NMSEQ_MAIN_END,	///<終了
 NMSEQ_MAX,
};

//------------------------------------------------------------------
/**
 * @brief	サブプロセス呼び出し処理
 * @param	proc	サブプロセスポインタを保持するワークへのポインタ
 */
//------------------------------------------------------------------
extern BOOL NutMixerProcCall(PROC ** proc);

#endif	//__H_NUTMIXER_SYS_H__

