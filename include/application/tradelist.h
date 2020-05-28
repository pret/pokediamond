//============================================================================================
/**
 * @file	tradelist.h
 * @bfief	ポケモン交換リスト画面
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================
#ifndef _TRADELIST_H_
#define _TRADELIST_H_


//============================================================================================
//	定数定義
//============================================================================================
#include "savedata/friendlist.h"
#include "savedata/wifihistory.h"
#include "savedata/config.h"
#include "savedata/zukanwork.h"
#include "savedata/fnote_mem.h"
#include "savedata/record.h"


#define TRADELIST_END_FINISH  ( 0 )				// 交換をやめて終了した
#define TRADELIST_END_DEMO    ( 1 )				// 交換を成立させてデモにいく

// 交換リストに行くときに渡すパラメータ構造体
typedef struct {
	FIELDSYS_WORK *fsys;
	MYSTATUS      *mystatus;
	POKEPARTY     *myparty;
	FRIEND_LIST   *friendlist;
	SAVEDATA      *savedata;
	WIFI_HISTORY  *wifihistory;
	CONFIG		  *config;			// コンフィグ構造体
	FNOTE_DATA	  *fnote;			// 冒険ノートポインタ
	RECORD		  *record;			// レコードポインタ
	ZUKAN_WORK    *zukanwork;		// 図鑑データ
	int			  result;			// 交換リストからの返り値 
									// TRADELIST_END_FINISH = 交換をやめた
									// TRADELIST_END_DEMO   = 交換デモへ
	int			  exchangepos;		// 交換したポケモンの位置

	int			  zukanmode;		// 図鑑モード（シンオウ・全国)
	int			  times;

	// デモ画面用パラメータ（ポインタ受け渡しではなく、実体用領域を確保してあるのでコピーする）
	MYSTATUS*			result_partner;
	POKEMON_PARAM*		result_sendPoke;
	POKEMON_PARAM*		result_recvPoke;

}TRADELIST_PARAM;



typedef struct TRADELIST_WORK TRADELIST_WORK;	// ポケモン交換画面ワーク構造体（ポインタ参照だけできる）


extern PROC_RESULT TradeListProc_Init( PROC * proc, int * seq );
extern PROC_RESULT TradeListProc_Main( PROC * proc, int * seq );
extern PROC_RESULT TradeListProc_End( PROC * proc, int * seq );



#endif //_TRADELIST_DEF_H_
