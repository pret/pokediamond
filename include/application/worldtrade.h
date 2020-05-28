//============================================================================================
/**
 * @file	world_trade.h
 * @bfief	世界交換処理
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
#ifndef _WORLD_TRADE_H_
#define _WORLD_TRADE_H_

#include "savedata/worldtrade_data.h"
#include "savedata/wifihistory.h"
#include "savedata/mystatus.h"
#include "savedata/config.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"
#include "savedata/record.h"
#include "savedata/system_data.h"
#include "itemtool/myitem.h"


//============================================================================================
//	定義
//============================================================================================

// プロセス定義データ
extern PROC_RESULT WorldTradeProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WorldTradeProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WorldTradeProc_End ( PROC * proc, int * seq );

// ポインタ参照だけできる世界交換ワーク構造体
typedef struct WORLDTRADE_WORK WORLDTRADE_WORK;	


typedef struct{
	WORLDTRADE_DATA *worldtrade_data;	// 世界交換データ
	SYSTEMDATA		*systemdata;		// システムセーブデータ（DPWライブラリ用ともだちコードを保存）
	POKEPARTY       *myparty;			// 手持ちポケモン
	BOX_DATA        *mybox;				// ボックスデータ
	ZUKAN_WORK      *zukanwork;			// 図鑑データ
	WIFI_LIST		*wifilist;			// ともだち手帳
	WIFI_HISTORY	*wifihistory;		// 地球儀データ
	MYSTATUS		*mystatus;			// トレーナー情報
	SAVEDATA		*savedata;			// セーブデータポインタ
	CONFIG			*config;			// コンフィグ構造体
	RECORD			*record;			// レコードコーナーポインタ
	FNOTE_DATA		*fnote;				// 冒険ノートポインタ
	MYITEM			*myitem;			// アイテムポケットポインタ
	int				zukanmode;			// 図鑑モード（シンオウ・全国)
	int				profileId;			// GameSpyプロファイルID
	int				contestflag;		// コンテスト見えてるかフラグ
	int				connect;			// 初回ＧＳＩＤを取得した（1:取得してきた 0:もう持ってる)

}WORLDTRADE_PARAM;

#endif