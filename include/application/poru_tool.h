/**
 *	@file	poru_tool.h
 *	@brief	ポルトツール
 *	@author	Miyuki Iwasawa
 *	@date	06.03.14
 */

#ifndef __H_PORU_TOOL_H__
#define __H_PORU_TOOL_H__

#include "savedata/savedata_def.h"
#include "savedata/poruto_util.h"
#include "savedata/mystatus.h"
#include "system/gamedata.h"
#include "itemtool/myitem.h"
#include "poketool/pokeparty.h"
#include "application/p_status.h"
#include "application/pokelist.h"

typedef enum{
 PORU_FAVOLITE_SUKI,	///<好き
 PORU_FAVOLITE_KIRAI,	///<キライ
 PORU_FAVOLITE_NRM,		///<普通
}PORU_FAVOLITE;

///ポルトデータリスト構造
typedef struct _PORU_LIST{
	u8	id;			///データID
	u8	level;		///<ポルトのレベル
	u8	flavor;		///<ポルトの種類
	u8	taste;		///<なめらかさ

	union{
		struct{
		u8	spicy:1;	///<持っている味
		u8	astr:1;
		u8	sweet:1;
		u8	bitter:1;
		u8	sour:1;
		u8	view:1;	///<描画フラグ
		u8	del:1;		///<削除フラグ
		u8	valid:1;	///<有効/無効フラグ
		};
		u8 flags;
	};
	u8	myid;
	u8	prev;
	u8	next;

//	STRBUF	*lvbuf;
}PORU_LIST;

///ポルト呼び出しワーク
typedef struct _PORUTO_PARAM{
	u8		porunum;	///<呼び出し時のポルトの数
	u8		selID;
	u8		ret_mode;	///<リターン値
	u8		ret_view;	///<リターンviewモード
	u16		listPos;	///<初期リストポジション
	u16		curPos;		///<初期カーソルポジション
	
	PORUTO_BLOCK* poruSave;	///<ポルトセーブデータ
	MYSTATUS	*mySave;	///<ステータス
	POKEPARTY	*ppSave;	///<ポケパーティ
	MYITEM		*itemSave;	///<アイテム
	CONFIG		*configSave;	///<コンフィグ

	PORU_LIST	list[PORUTO_STOCK_MAX];	///<操作データ列
}PORUTO_PARAM;

///オーバーレイプロセス外部参照宣言
extern const PROC_DATA PorutoSysProcData;

/**
 *	@brief	ポルトシステム呼び出しワークデータ作成
 *
 *	＊必ず PorutoSys_ReleaseCallWork()関数で解放すること！
 */
extern PORUTO_PARAM* PorutoSys_CreateCallWork(SAVEDATA* savedata,int heapID);

/**
 *	@brief	ポルトケース呼び出しワークを解放する
 */
extern void PorutoSys_ReleaseCallWork(PORUTO_PARAM* pp);

/**
 *	@brief	ポルトデータと性格からそのポルトを好きか嫌いか返す
 */
extern PORU_FAVOLITE PoruSys_IsFavolite(PORUTO_DATA *dat,u8 seikaku);

/**
 *	@brief	ポルトパラメータをポケモンパラメータにPushする
 */
extern void PoruSys_PoruPara2Poke(PORUTO_DATA* dat,POKEMON_PARAM* poke);

/**
 *	@brief	性格からどの味が好きか嫌いか返す
 *
 *	@param	ポケモンの性格No
 *	@param	mode	PORU_FAVOLITE_SUKI:好きな味タイプを返す
 *					PORU_FAVOLITE_KIRAI:キライな味タイプを返す
 *
 *	@retval	PORUTO_FTYPE_SPICY	辛い
 *	@retval	PORUTO_FTYPE_ASTR	しぶい
 *	@retval	PORUTO_FTYPE_SWEET	あまい
 *	@retval	PORUTO_FTYPE_BITTER	苦い
 *	@retval	PORUTO_FTYPE_SOUR	すっぱい
 *	@retval	PORUTO_FTYPE_MIX	好き嫌いがない
 */
extern u8	PoruSys_GetFavolite(u8 seikaku,PORU_FAVOLITE mode);



#endif	//__H_PORU_TOOL_H__

