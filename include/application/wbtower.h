//============================================================================================
/**
 * @file	wbtower.h
 * @bfief	WIFIバトルタワー接続画面
 * @author	Akito Mori
 * @date	06.05.15
 */
//============================================================================================
#ifndef _WBTOWER_H_
#define _WBTOWER_H_

#include <dwc.h>
#include "savedata/system_data.h"
#include "savedata/b_tower.h"
#include "savedata/config.h"
#include "wbtower_def.h"

//============================================================================================
//	定義
//============================================================================================

// プロセス定義データ
extern PROC_RESULT WBTowerProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WBTowerProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WBTowerProc_End ( PROC * proc, int * seq );


// 接続モード
enum{
	WIFI_BTOWER_MODE_DOWNLOAD=0,			// ルームデータダウンロード
	WIFI_BTOWER_MODE_UPLOAD,				// 結果ダウンロード
	WIFI_BTOWER_MODE_LEADER,				// リーダーデータダウンロード
};


// ポインタ参照だけできるWIFIバトルタワーワーク構造体
typedef struct WBTOWER_WORK WBTOWER_WORK;	


typedef struct{
	BTLTOWER_SCOREWORK	*btowerscore;		// バトルタワー成績データ
	BTLTOWER_WIFI_DATA	*wifitowerdata;		// WIFIバトルタワーデータポインタ
	SYSTEMDATA			*systemdata;		// システムセーブデータ（DPWライブラリ用ともだちコードを保存）
	SAVEDATA			*savedata;			// セーブデータポインタ
	CONFIG				*config;			// コンフィグ構造体
	DWCUserData			*MyUserData;		// 認証済みのDWCUSERデータしかこないはず
	int					mode;				// WIFIバトルタワー接続モード
	int					profileId;			// GameSpyプロファイルID
	int					result;				// 繋いだ結果を入れて返す
	int					connect;			// 初回ＧＳＩＤを取得した（1:取得してきた 0:もう持ってる)
}WBTOWER_PARAM;

#endif	/* _WBTOWER_H_ */